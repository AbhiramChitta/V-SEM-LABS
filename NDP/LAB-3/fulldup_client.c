#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int s, r, recb, sntb;
    int x;
    printf("Enter the port number: ");
    scanf("%d", &x);
    socklen_t len;
    struct sockaddr_in server;
    char buff[100];

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        printf("\nSocket creation error");
        exit(1);
    }
    printf("\nSocket created");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(x);

    r = connect(s, (struct sockaddr *)&server, sizeof(server));
    if (r == -1)
    {
        printf("\nConnection error");
        close(s);
        exit(1);
    }
    printf("\nSocket connected");

    pid_t p = fork();
    if (p < 0)
    {
        printf("\nFork error");
        close(s);
        exit(1);
    }

    if (p == 0)
    { // Child process for sending messages
        char msg[100];
        while (1)
        {
            printf("\nClient: ");
            fgets(msg, sizeof(msg), stdin);
            sntb = send(s, msg, sizeof(msg), 0);
            if (sntb == -1)
            {
                printf("\nSend error");
                close(s);
                exit(1);
            }
        }
    }
    else
    { // Parent process for receiving messages
        char msg[100];
        while (1)
        {
            recb = recv(s, msg, sizeof(msg), 0);
            if (recb == -1)
            {
                printf("\nReceive error");
                close(s);
                exit(1);
            }
            if (recb == 0)
            {
                printf("\nConnection closed by server");
                break;
            }
            printf("\nServer: %s", msg);
        }
        close(s);
    }

    return 0;
}
