/* ================================================
 *   Name: jdsh v3 (with IO redirection support) 
 *   Author : Jackaldire, jokerleee@gmail.com
 *   Lisence : GPLv3
 *   Date : Jan 30 2009
 * ================================================*/



#include "jdsh_v3.h"

char prompt[LINE_MAX + 1];

char line[LINE_MAX + 1];

void free_proc()
{
    size_t i;
    for (i = 0; proc.args[i]; ++i) {
        free(proc.args[i]);
        proc.args[i] = NULL;
    }
    for (i = 0; proc.rdinfo[i]; ++i) {
        free(proc.rdinfo[i]);
        proc.rdinfo[i] = NULL;
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
    if (!strcmp(args[0], "cd")) {
        if (args[1] == NULL)
            args[1] = getenv("HOME");
        CHKERR(chdir(args[1]), "cd");
    } else if (!strcmp(args[0], "exit")) {
        exit(0);
    } else return 0;

    return 1;
}

int parse_command()
{
    char c;
    char fin = 0; /* flag to end the loop */
    char rd = 0; /* flag to indicate io redirect parse mode */
    char esc = 0; /* escape charactor */
    size_t cnt = 0; /* counter of arguments */
    size_t rcnt = 0; /* counter of io redirect command */
    size_t idx = 0; /* counter for line array */
    
    memset((void *)&proc, 0, sizeof(struct process));
    bzero(line, LINE_MAX + 1);
    
    pr_prompt();
    do {
        c = fgetc(stdin);
        esc = (c == '\\');
        if (esc == 1) { /* last charactor is escape charactor '\' */
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
            case ' ': case '\t': case '\n':
                line[idx] = '\0';
                if (strlen(line) > 0) {
                    idx = 0;
                    if (rd) {
                        strcpy(proc.rdinfo[rcnt++]->dst, line);
                        rd = 0;
                    }
                    else proc.args[cnt++] = strdup(line);
                }
                if (c == '\n') fin = 1;
                break;
            case '&':
                proc.bg = 1;
                break;
            case '>': case '<':
                if (rd) { /* case for ">>" */
                    if (c == '>' && !proc.rdinfo[rcnt]->in)
                        proc.rdinfo[rcnt]->pending = 1; 
                    else return -1;
                } else {
                    if (idx > 1) {
                        line[idx] = '\0';
                        idx = 0;
                        proc.args[cnt++] = strdup(line);
                    }
                    /* create a new io redirection */
                    proc.rdinfo[rcnt] = malloc(sizeof(struct redir_info));
                    memset(proc.rdinfo[rcnt], 0, sizeof(struct redir_info));

                    proc.rdinfo[rcnt]->in = (c == '<');
                    proc.rdinfo[rcnt]->src = (c == '>'); // 1>xxx 0<xxx
                    if (idx == 1 && isdigit(line[idx-1]))
                        proc.rdinfo[rcnt]->src = line[--idx] - '0';
                    rd = 1; // set rd flag
                }
                break;
            default:
                line[idx++] = c;
            }
        }
    } while (!fin);
    
    proc.args[cnt] = NULL;
    proc.rdinfo[rcnt] = NULL;
    return 0;
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
    /* change cwd to $HOME */
    CHKERR(chdir(getenv("HOME")), "chdir");

    /* handle SIGINT */
    struct sigaction act;
    CHKERR(sigaction(SIGINT, NULL, &act), "sigaction");
    act.sa_handler = sig_int;
    CHKERR(sigaction(SIGINT, &act, NULL), "sigaction");
    
    /* ignore SIGQUIT and SIGTSTP */
    CHKERR(signal(SIGQUIT, SIG_IGN), "signal");
    CHKERR(signal(SIGTSTP, SIG_IGN), "signal");
}

void redirect_io(struct redir_info * rds[])
{
    size_t i;
    int fd;
    int flags;
    mode_t mode;

    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    for (i = 0; rds[i] != NULL; ++i) {
        mode = flags = 0;
        
        flags |= (rds[i]->in ? O_RDONLY : O_WRONLY | O_CREAT);
        if (!rds[i]->in)
            flags |= (rds[i]->pending ? O_APPEND : O_TRUNC);
        
        /*fprintf(stderr, "src=%d, dst=%s, %d, %d\n", 
                rds[i]->src, rds[i]->dst, rds[i]->in, rds[i]->pending);*/
        CHKERR((fd = open(rds[i]->dst, flags, mode)), "open");
        CHKERR(close(rds[i]->src), "close");
        CHKERR(dup(fd), "dup");
        CHKERR(close(fd), "close");
    }
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
        if (parse_command()) {
            puts("jdsh: parse error.");
            continue;
        }
        
        if (proc.args[0] == NULL) /* blanks */
            continue;
        
        if (check_builtins(proc.args)) 
            continue;

        pid = fork(); 
        CHKERR(pid, "fork");
        //setpgid(pid, 0);
        if (pid == 0) {
            CHKERR(signal(SIGQUIT, SIG_DFL), "signal");
            CHKERR(signal(SIGTSTP, SIG_DFL), "signal");
            
            redirect_io(proc.rdinfo);

            r = execvp(proc.args[0], proc.args);
            CHKERR(r, proc.args[0]);
            fflush(stdout);
        } else {
            if (!proc.bg) {
                wait(&status);
                pr_exit(proc.args[0], status, (pid_t)0);
            } else {
                //waitpid(pid, &status, WNOHANG); alternative
                CHKERR(sigaction(SIGCHLD, NULL, &act), "sigaction");
                act.sa_sigaction = sig_bg_exit;
                act.sa_flags = SA_SIGINFO | SA_NOCLDSTOP | SA_RESETHAND;
                CHKERR(sigaction(SIGCHLD, &act, NULL), "sigaction");
            }
            usleep(1e5); /* this is a work around */
        }
        
        free_proc();
    }
    return 0;
}

