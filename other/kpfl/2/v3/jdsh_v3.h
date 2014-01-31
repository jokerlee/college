/* ================================================
 *   Name: jdsh v3 header
 *   Author : Jackaldire, jokerleee@gmail.com
 *   Lisence : GPLv3
 *   Date : Jan 30 2009
 * ================================================*/
#ifndef _JDSH_V3_INCLUDE_
#define _JDSH_V3_INCLUDE_

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>
#include <ctype.h>

#define LINE_MAX 8192

 
#define ARG_MAX 1024
#define ARG_NR_MAX 32
#define TASK_MAX 32

#define CHKERR(ret, msg) if (ret < 0) {\
        fprintf(stderr, "ERROR : \"%s\", %s\n", \
                msg, strerror(errno)); \
        exit(-1);   \
    } 

/* struct to record io redirect infos */
struct redir_info {
    char in;
    int src;
    char dst[LINE_MAX + 1];
    char pending;
};

struct process {
    char * args[ARG_NR_MAX + 1];
    char bg;
    struct redir_info * rdinfo[ARG_NR_MAX + 1];
    char * out;
}proc;



void pr_exit(const char * name, int status, pid_t pid);
void free_proc();
void pr_prompt(void);
void pr_exit(const char * name, int status, pid_t pid);
static void sig_bg_exit(int signo, siginfo_t * info, void * ctxt);
static void sig_int(int signo);
int check_builtins(char * args[]);
int parse_command(void);
void shell_initial(void);


#endif
