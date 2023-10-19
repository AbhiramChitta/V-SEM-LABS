#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // TCP server code
    int sockfd, newsockfd, portno, clilen, n;
    char buffer[256];
    struct sockaddr_in server, client;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error opening socket");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000);
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Error on binding");
        exit(1);
    }
    if (listen(sockfd, 5) < 0)
    {
        perror("Error on listening");
        exit(1);
    }
    clilen = sizeof(client);
    newsockfd = accept(sockfd, (struct sockaddr *)&client, &clilen);
    if (newsockfd < 0)
    {
        perror("Error on accept");
        exit(1);
    }
    while (1)
    {
        bzero(buffer, 256);
        n = recv(newsockfd, buffer, 255, 0);
        if (n < 0)
        {
            perror("Error on reading");
            exit(1);
        }
        printf("Client: %s\n", buffer);
        int i = strcmp("Bye\n", buffer);
        if (i == 0)
            break;

        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        n = send(newsockfd, buffer, strlen(buffer), 0);
        if (n < 0)
        {
            perror("Error on writing");
            exit(1);
        }
        i = strcmp("Bye\n", buffer);
        if (i == 0)
            break;
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
