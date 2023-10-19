#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXSIZE 1024
// client lab4 TCP
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
    server_addr.sin_port = htons(9999);                  
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    int retval = connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (retval == -1)
    {
        perror("Connection error");
        exit(1);
    }

    while (1)
    {
        printf("Options:\n1. Registration Number\n2. Name of the Student\n3. Subject Code\nEnter your choice (0 to exit): ");
        int choice;
        scanf("%d", &choice);

        if (choice == 0)
        {
            break;
        }

        send(client_sock, &choice, sizeof(int), 0);

        char response[MAXSIZE];
        recv(client_sock, response, sizeof(response), 0);
        printf("\nServer Response:\n%s\n\n", response);
    }

    close(client_sock);
    return 0;
}
