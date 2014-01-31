#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#include "cmd_interface.h"

#define LENGTH_OF_LISTEN_QUEUE 10
#define BUFFER_SIZE 1024 
#define PORT 20000

bool is_quit = false;

void * service_thread(void * sockfd)
{
    char buf[BUFFER_SIZE];
    int ret;
    
    CmdInterface::Instance().run((int)sockfd);

    close((int)sockfd);
    is_quit = true;
    return NULL;
}

int main(int argc, char **argv)
{
    int connfd, snd, slenth;
    struct sockaddr_in server;
    struct hostent * hp;
    pthread_t tid;
    char hostname[] = "127.0.0.1";

    if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Cannot create socket.\n");
        exit(1);
    }
    
    if ((hp = gethostbyname(hostname)) == NULL)
    {
        printf("Cannot get server's ip.\n");
        exit(0);
    }
    printf("Socket have been created sunccessfully.\n");
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htons(INADDR_ANY);

    if (connect(connfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Cannot connect to server.\n");
        exit(1);
    }
    printf("Connection established.\n");
    
    pthread_create(&tid, NULL, &service_thread, (void*)connfd); 

    while (true)
    {
        sleep(1);
        if (is_quit)
            break;
    }

    close(connfd);

    return 0;

}

