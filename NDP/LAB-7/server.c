#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>

// #define myport 8080

int main(){
    int myport;
    printf("Enter port number : ");
    scanf("%d",&myport);
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("[-]socket creation error\n");
        exit(1);
    }
    struct sockaddr_in server_addr ,client_addr;
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(myport);
    memset(server_addr.sin_zero,'\0',sizeof(server_addr));

    socklen_t len ;
    len = sizeof(client_addr);

    int b = bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(b<0){
        perror("[-]socket binding error\n");
        exit(1);
    }
    int l = listen(sockfd,10);
    if(l<0){
        perror("[-]server listening error\n");
        exit(1);
    }
    printf("[+]Listening...\n");
    while(1){
        int afd = accept(sockfd,(struct sockaddr *)&client_addr,&len);
        if(afd<0){
        perror("[-]socket accepting error\n");
        exit(1);
        }
        printf("[+]Connection established\n");

    }
}