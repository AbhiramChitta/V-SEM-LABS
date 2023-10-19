#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // TCP client code
    int sockfd, portno, n;
    struct sockaddr_in server;
    char buffer[256];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Error in connection\n");
        exit(0);
    }
    while (1)
    {
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        n = send(sockfd, buffer, strlen(buffer), 0);
        if (n < 0)
        {
            printf("Error in writing\n");
            exit(0);
        }
        bzero(buffer, 256);
        n = recv(sockfd, buffer, 255, 0);
        if (n < 0)
        {
            printf("Error in reading\n");
            exit(0);
        }
        printf("Server: %s\n", buffer);
        int i = strcmp("Bye\n", buffer);
        if (i == 0)
            break;
    }
    close(sockfd);
    return 0;
}
