/* ================================================
 *   Name: jdsh v4 (with IO redirection support) 
 *   Author : Jackaldire, jokerleee@gmail.com
 *   Lisence : GPLv3
 *   Date : Jan 30 2009
 * ================================================*/



#include "jdsh_v4.h"


static struct task tasks[TASK_MAX];

char line[LINE_MAX + 1];


void free_task(struct task * t)
{
    size_t i;
    for (i = 0; t->pipeline[i]; ++i) {
        free_proc(t->pipeline[i]);
        free(t->pipeline[i]);
        t->pipeline[i] = NULL;
    }
}

void free_proc(struct process * p)
{
    size_t i;
    for (i = 0; p->args[i]; ++i) {
        free(p->args[i]);
        p->args[i] = NULL;
    }
    for (i = 0; p->rdinfo[i]; ++i) {
        free(p->rdinfo[i]);
        p->rdinfo[i] = NULL;
    }
}

void pr_prompt(void)
{
    /*prompt format: "[user@host pwd]$ " */
    char prompt[LINE_MAX + 1],
         host[LINE_MAX + 1],
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
    check_proc_status("", info->si_status, info->si_pid);
    fflush(stdout);
}

static void sig_int(int signo)
{
    putchar('\n');
    //ungetc('\n', stdin);
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


int build_task(struct task * t)
{
    size_t i;

    parse_command(t->pipeline[0]);
    
    for (i = 0; t->pipeline[i]; ++i)
        if (t->pipeline[i]->bg) {
            t->bg = 1;
            break;
        }

    t->p_cnt = i; 
    t->pipeline[i] = NULL;
}

int parse_command(struct process * p)
{
    char c;
    char fin = 0; /* flag to end the loop */
    char rd = 0; /* flag to indicate io redirect parse mode */
    char esc = 0; /* escape charactor */
    size_t cnt = 0; /* counter of arguments */
    size_t rcnt = 0; /* counter of io redirect command */
    size_t idx = 0; /* counter for line array */
    
    p = calloc(1, sizeof(struct process));
    bzero(line, LINE_MAX + 1);
 
    pr_prompt();
    do {
        c = fgetc(stdin);
        esc = (c == '\\');
        if (esc == 1) { /* escape charactor '\' */
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
             /* '|' and '\n' both indicate the end of a command */
            case '|': parse_command(p + 1);
            case '\n': fin = 1;
            case ' ':
            case '\t':
                if (idx > 0) {
                    line[idx] = '\0';
                    idx = 0;
                    if (rd) {
                        strcpy(p->rdinfo[rcnt++]->dst, line);
                        rd = 0;
                    }
                    else p->args[cnt++] = strdup(line);
                }
                break;
            
            case '&':
                p->bg = 1;
                break;
            
            case '>':
            case '<':
                if (rd) { /* case for ">>" */
                    if (c == '>' && !p->rdinfo[rcnt]->in)
                        p->rdinfo[rcnt]->pending = 1; 
                    else return -1;
                } else {
                    if (idx > 1) {
                        line[idx] = '\0';
                        idx = 0;
                        p->args[cnt++] = strdup(line);
                    }
                    /* create a new io redirection */
                    p->rdinfo[rcnt] = alloc(sizeof(struct redir_info));

                    p->rdinfo[rcnt]->in = (c == '<');
                    p->rdinfo[rcnt]->src = (c == '>'); // 1>xxx 0<xxx
                    if (idx == 1 && isdigit(line[idx-1]))
                        p->rdinfo[rcnt]->src = line[--idx] - '0';
                    rd = 1; // set rd flag
                }
                break;
            default:
                line[idx++] = c;
            }
        }
    } while (!fin);
    
    p->args[cnt] = NULL;
    p->rdinfo[rcnt] = NULL;
    return 0;
}

int check_proc_status(const char * name, int status, pid_t pid)
{
    char id[LINE_MAX + 1];
    if (pid == 0) strcpy(id, name);
    else sprintf(id, "[%u]", pid);

    if (WIFEXITED(status)) // exit normally
        if (pid) printf("%s finished\n", id);
        else return 0;
    else if (WIFSIGNALED(status))
        fprintf(stderr, "%s exit abnormally, signal %d caught%s.\n",
                id, WTERMSIG(status),
#ifdef WCOREDUMP
            WCOREDUMP(status) ? " (core file generated)" : "");
#else
            "");
#endif
    else if (WIFSTOPPED(status)) {
        fprintf(stderr, "child stopped, signal %d caught.\n",
                WSTOPSIG(status));
        return 1;
    } else return 1;
    
    return 0;
}

void shell_initial()
{
    /* change cwd to $HOME */
    CHKERR(chdir(getenv("HOME")), "chdir");

    /* handle SIGINT */
    signal(SIGINT, sig_int);
    
    /* ignore SIGQUIT and SIGTSTP */
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    
}

void redirect_io(struct redir_info * rds[])
{
    size_t i;
    int fd;
    int flags;
    mode_t mode;
    umask(0775);
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

int execute_task(struct task * t)
{
    pid_t pid;
    int r;
    int status;
    struct sigaction act;
    
    CHKERR((pid = fork()), "fork");
    
    if (pid == 0) {
        /* set backgroud task to a new process group */
        size_t idx = 0;
        int fd[2] = {0, 0}; 
        while(t->p_cnt - idx > 1) {

            pipe(fd);
            CHKERR((pid = fork()), "fork");
            
            if (pid == 0) {
                if (proc->bg)
                    setpgid(0, 0);
                
                if (check_builtin(t->pipeline[idx]->args))
                    return 0;

                CHKERR(signal(SIGQUIT, SIG_DFL), "signal");
                CHKERR(signal(SIGTSTP, SIG_DFL), "signal");
        
                redirect_io(proc->rdinfo);
                
                dup2(fd[1], STDOUT_FILENO); 
                close(fd[0]);
                close(fd[1]);

                r = execvp(proc->args[0], proc->args);
                CHKERR(r, proc->args[0]);
            }
        }

        r = execvp(proc->args[0], proc->args);
        CHKERR(r, proc->args[0]);

    } else {
        if (!proc->bg) {
            do wait(&status);
            while (check_proc_status(proc->args[0], status, (pid_t)0));
        } else {
            setpgid(pid, 0);
            //waitpid(pid, &status, WNOHANG);
            sigaction(SIGCHLD, NULL, &act);
            act.sa_sigaction = sig_bg_exit;
            act.sa_flags = SA_SIGINFO | SA_NOCLDSTOP | SA_RESETHAND;
            sigaction(SIGCHLD, &act, NULL);
        }
        usleep(5e4); /* this is a work around */
    }
}

int execute_command()
{

}


int main(int argc, char * argv[])
{
    char c;
    size_t idx;
    pid_t pid;
    
    shell_initial();
    
    for (idx = 0 ; ; ) {
         
        fflush(stdout);
        tasks[idx].id = idx; 
        if (build_task(&tasks[idx])) {
            puts("jdsh: parse error.");
            continue;
        }
        
        if (tasks.pipeline == NULL) /* blanks */
            continue;
        
        execute_command(&tasks[idx]);
    }
    return 0;
}

