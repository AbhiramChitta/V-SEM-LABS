#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define MAXSIZE 1024
int main()
{
    int client_sock;
    struct sockaddr_in server_addr;

    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0)
    {
        perror("Socket creation error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1235);                  
    server_addr.sin_addr.s_addr = INADDR_ANY; 

    int retval = connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (retval == -1)
    {
        perror("Connection error");
        exit(1);
    }

    char username[10];
    char password[10];
    printf("\nLOGIN\nEnter Username: ");
    scanf("%s",username);
    printf("\nPassword: ");
    scanf("%s",password);
    send(client_sock,username,sizeof(username),0);
    send(client_sock,password,sizeof(password),0);
    
}