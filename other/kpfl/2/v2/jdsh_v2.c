/* ================================================
 *   Name: jdsh v2 
 *   Author : Jackaldire, jokerleee@gmail.com
 *   Lisence : GPLv3
 *   Date : Jan 30 2009
 * ================================================*/

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LINE_MAX 8192

 
#define ARG_MAX 1024
#define ARG_NR_MAX 32
#define TASK_MAX 32

#define CHKERR(ret, msg) if (ret < 0) {\
        fprintf(stderr, "ERROR : \"%s\", %s\n", \
                msg, strerror(errno)); \
        exit(-1);   \
    } 

static char * built_ins[] = {"cd", "exit"};

void pr_exit(const char * name, int status, pid_t pid);

struct process {
    char * args[ARG_NR_MAX + 1];
    char bg;
}proc;


char prompt[LINE_MAX + 1];

char line[LINE_MAX + 1];


void free_proc()
{
    size_t i = 0;
    for ( ; proc.args[i]; ++i) {
        free(proc.args[i]);
        proc.args[i] = NULL;
    }
}

void pr_prompt(void)
{
    /*prompt format: "[user@host pwd]$ " */
    char host[LINE_MAX + 1],
         pwd[LINE_MAX + 1];
    size_t len;
    
    gethostname(host, LINE_MAX);
    
    getcwd(pwd, LINE_MAX);
    len = strlen(getenv("HOME"));
    /* replace $HOME with '~' */
    if (!strncmp(getenv("HOME"), pwd, len)) {
        pwd[0] = '~';
        memmove(pwd + 1, pwd + len, len);
    }
    sprintf(prompt, "[%s@%s %s]$ ", getenv("LOGNAME"), host, pwd);
    printf("%s", prompt);
}

static void sig_bg_exit(int signo, siginfo_t * info, void * ctxt)
{
    pr_exit("", info->si_status, info->si_pid);
    fflush(stdout);
}

static void sig_int(int signo)
{
    putchar('\n');
    pr_prompt();
    fflush(stdout);
}

int check_builtins(char * args[])
{
    int ret;
    if (!strcmp(args[0], "cd")) {
        if (args[1] == NULL)
            args[1] = getenv("HOME");
        ret = chdir(args[1]);
        CHKERR(ret, "cd");
    } else if (!strcmp(args[0], "exit")) {
        exit(0);
    } else return 0;

    return 1;
}

void parse_command()
{
    char c;
    char esc = 0;
    size_t cnt = 0;
    size_t idx = 0;
    
    memset((void *)&proc, 0, sizeof(struct process));
    bzero(line, LINE_MAX + 1);
    
    pr_prompt();

    c = fgetc(stdin);
    esc = (c == '\\');
    while (c != '\n') {
        if (esc == 1) { // escape charactor '\'
            c = fgetc(stdin);
            switch (c) {
            case '\n':
                putchar('>');
                break;
            default:
                line[idx++] = c;
            }
        } else {
            switch (c) {
            case ' ': case '\t':
                line[idx] = '\0';
                if (strlen(line) > 0) {
                    idx = 0;
                    proc.args[cnt++] = strdup(line);
                }
                break;
            case '&':
                proc.bg = 1;
                break;
            default:
                line[idx++] = c;
            }
        }
        c = fgetc(stdin);
        esc = (c == '\\');
    }
    line[idx] = '\0';
    if (strlen(line) > 0) 
        proc.args[cnt++] = strdup(line);
    
    proc.args[cnt] = NULL;

}

void pr_exit(const char * name, int status, pid_t pid)
{
    char id[LINE_MAX + 1];
    if (pid == 0) strcpy(id, name);
    else sprintf(id, "[%u]", pid);

    if (WIFEXITED(status)) // exit normally
        if (pid) printf("%s finished\n", id);
        else return;
    else if (WIFSIGNALED(status))
        fprintf(stderr, "%s exit abnormally, signal %d caught%s.\n",
                id, WTERMSIG(status),
#ifdef WCOREDUMP
            WCOREDUMP(status) ? " (core file generated)" : "");
#else
            "");
#endif
    else if (WIFSTOPPED(status))
        fprintf(stderr, "child stopped, signal %d caught.",
                WSTOPSIG(status));
}

void shell_initial()
{
    chdir(getenv("HOME"));

    /* handle SIGINT */
    struct sigaction act;
    sigaction(SIGINT, NULL, &act);
    act.sa_handler = sig_int;
    sigaction(SIGINT, &act, NULL);

    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}


int main(int argc, char * argv[])
{
    char c;
    size_t idx;
    int r;
    int status;
    pid_t pid;
    struct sigaction act;
    
    shell_initial();
    
    for ( ; ; ) {
        idx = 0;
         
        fflush(stdout);
        parse_command();
        
        if (proc.args[0] == NULL) /* blanks */
            continue;
        
        if (check_builtins(proc.args)) 
            continue;

        pid = fork(); 
        CHKERR(pid, "fork");
        //setpgid(pid, 0);
        if (pid == 0) {
            signal(SIGQUIT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);

            r = execvp(proc.args[0], proc.args);
            CHKERR(r, proc.args[0]);
            fflush(stdout);
        } else {
            if (!proc.bg) {
                wait(&status);
                pr_exit(proc.args[0], status, (pid_t)0);
            } else {
                //waitpid(pid, &status, WNOHANG); alternative
                sigaction(SIGCHLD, NULL, &act);
                act.sa_sigaction = sig_bg_exit;
                act.sa_flags = SA_SIGINFO | SA_NOCLDSTOP | SA_RESETHAND;
                sigaction(SIGCHLD, &act, NULL);
            }
            usleep(1e5); /* this is a work around */
        }
        
        free_proc();
    }
    return 0;
}

