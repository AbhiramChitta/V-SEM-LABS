#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define MAXSIZE 1024
// Lab4 tcp server
int main()
{
    char buff[MAXSIZE];
    int sockfd, newsockfd, retval;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Socket creation error");
        exit(1);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(1235); // Use a different port number
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    memset(serveraddr.sin_zero,'\0',sizeof(serveraddr));
    retval = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (retval == -1)
    {
        perror("Binding error");
        exit(1);
    }

    retval = listen(sockfd, 10);
    if(retval<0){
        perror("listening error\n");
        exit(1);
    }
    printf("listening...\n");
    addr_size = sizeof(clientaddr);

    printf("hello");
    char username[10];
    char password[10];       
    int afd=accept(sockfd,(struct sockaddr *)&clientaddr,&addr_size);
    if(afd<0)
    {
        printf("connection not established");
    }
    printf("connection established");
    int recv1=recv(afd,username,sizeof(username),0);
    if(recv1<0)
    {
        printf("message not received");
    }
    recv(afd,password,sizeof(password),0);
    printf("%s",username);
    printf("%s",password);

}