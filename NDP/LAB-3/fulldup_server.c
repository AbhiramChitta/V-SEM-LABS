#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int s, ns, r, x, recb, sntb;
    printf("\nEnter port number: ");
    scanf("%d", &x);
    socklen_t len;
    struct sockaddr_in server, client;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        printf("\nSocket creation error");
        exit(1);
    }
    printf("\nSocket created");

    server.sin_family = AF_INET;
    server.sin_port = htons(x);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    r = bind(s, (struct sockaddr *)&server, sizeof(server));
    if (r == -1)
    {
        printf("\nBinding error");
        close(s);
        exit(1);
    }
    printf("\nBinding successful");

    r = listen(s, 1);
    if (r == -1)
    {
        printf("\nListening error");
        close(s);
        exit(1);
    }
    printf("\nSocket listening");

    len = sizeof(client);
    ns = accept(s, (struct sockaddr *)&client, &len);
    if (ns == -1)
    {
        printf("\nAccept error");
        close(s);
        exit(1);
    }
    printf("\nConnection accepted");

    pid_t p;
    p = fork();
    if (p < 0)
    {
        printf("\nFork error");
        close(ns);
        close(s);
        exit(1);
    }

    if (p == 0)
    { // Child process for receiving messages
        char msg[100];
        while (1)
        {
            recb = recv(ns, msg, sizeof(msg), 0);
            if (recb == -1)
            {
                printf("\nReceive error");
                close(ns);
                close(s);
                exit(1);
            }
            if (recb == 0)
            {
                printf("\nConnection closed by client");
                break;
            }
            printf("\nClient: %s", msg);
        }
        close(ns);
    }
    else
    { // Parent process for sending messages
        char msg[100];
        while (1)
        {
            printf("\nServer: ");
            fgets(msg, sizeof(msg), stdin);
            sntb = send(ns, msg, sizeof(msg), 0);
            if (sntb == -1)
            {
                printf("\nSend error");
                close(ns);
                close(s);
                exit(1);
            }
        }
        close(ns);
        close(s);
    }

    return 0;
}
