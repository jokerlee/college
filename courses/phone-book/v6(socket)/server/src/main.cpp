#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include <pthread.h>

#include "client_process.h"
#define SERVER_PORT 20000 // define the defualt connect port id
#define LENGTH_OF_LISTEN_QUEUE 10 //length of listen queue in server
#define BUFFER_SIZE 255
#define WELCOME_MESSAGE "welcome to connect the server. "
#define MAXFD 20 //max number of connected user
 
int client_number = 0;

void* client_thread(void * sockfd)
{
    char buf[BUFFER_SIZE];
    
    client_number ++;

	ClientProcess client;
    client.run((int)sockfd);
    close((int)sockfd);

    client_number --;
    return NULL;
}

int main(int argc, char **argv)
{
    int servfd, clifd;
    struct sockaddr_in servaddr, cliaddr; 
    pthread_t tid;

    if ((servfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        printf("Create socket error!\n");
        exit(1);
    }
    printf("Initial socket...\n");

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);


    if (bind(servfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
    {
        printf("Bind to port %d failure!\n",SERVER_PORT);
        exit(1);
    }
     
    if (listen(servfd,LENGTH_OF_LISTEN_QUEUE) < 0)
    {
        printf("Call listen failure!\n");
        exit(1);
    }
    printf("Listening port %d\n", SERVER_PORT);

    while (1)
    {//server loop will nerver exit unless any body kill the process
        char buf[BUFFER_SIZE];
        long timestamp;
        socklen_t length = sizeof(cliaddr);
        clifd = accept(servfd,(struct sockaddr*)&cliaddr,&length);

        if (clifd < 0)
        {
            printf("Error comes when call accept!\n");
            break;
        }
        
        if (client_number == MAXFD-1)
        {
            //too many connections
        }

        printf("Connection from client, IP:%s, Port:%d\n",
                inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
        pthread_create(&tid, NULL, &client_thread, (void*)clifd);
        sleep(0.5);

    }//exit
    close(servfd);

    return 0;

}


