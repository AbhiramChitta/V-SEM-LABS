#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char nums[100];
    char chars[100];
    int sock;
    struct sockaddr_in server;
    char buf[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(3425);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connection error");
        exit(1);
    }

    while (1)
    {
        printf("Enter a string (or 'exit' to quit): ");
        fgets(buf, sizeof(buf), stdin);

        if (strcmp(buf, "exit\n") == 0)
        {
            break; // Exit the loop if the user types 'exit'
        }

        if (send(sock, buf, strlen(buf), 0) < 0)
        {
            perror("Sending error");
            exit(1);
        }

        memset(buf, 0, sizeof(buf));
    }

    close(sock);
    return 0;
}
