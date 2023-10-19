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
    printf("[+]Socket created successfully\n");
    struct sockaddr_in client_addr;
    client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(myport);
    memset(client_addr.sin_zero,'\0',sizeof(client_addr));

    int conn = connect(sockfd,(struct sockaddr * )&client_addr,sizeof(client_addr));
    if(conn<0){
        perror("[-]socket conection error\n");
        exit(1);
    }
    printf("[+]Socket connected successfully\n");
    char username[99];
    char pass[22];
    printf("                 ~Welcome to Union Bank of India~\n");
    // while(1){
    //     printf("Login to bank account :")
    // }
    
}