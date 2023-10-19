#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>

int main()
{
    int sfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;
    char buff[1000];
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd < 0)
    {
        printf("Error in socket creation\n");
        exit(1); // Use a non-zero exit code to indicate an error.
    }
    else
    {
        printf("Socket created successfully\n");
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(3388);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    clilen = sizeof(servaddr);
    while (1)
    {
        char filename[100];
        char buff[100];
        printf("\nEnter the filename: ");
        scanf("%s", filename);
        sendto(sfd, filename, sizeof(filename), 0, (struct sockaddr *)&servaddr, clilen);
        recvfrom(sfd, buff, sizeof(buff), 0, (struct sockaddr *)&servaddr, &clilen);
        if (strcmp(buff, "File not found") == 0)
        {
            printf("File not found\n");
            close(sfd);
            exit(1); // Use a non-zero exit code to indicate an error.
        }
        else
        {
            printf("File found\n");
            printf("\n1.Search\n2.Replace\n3.Reorder\n4.Exit\n");
            int choice;
            printf("Enter your choice: ");
            scanf("%d", &choice);
            sendto(sfd, &choice, sizeof(choice), 0, (struct sockaddr *)&servaddr, clilen);
            if (choice == 1)
            {
                char search[100];
                printf("Enter the string to be searched: ");
                scanf("%s", search);
                sendto(sfd, search, sizeof(search), 0, (struct sockaddr *)&servaddr, clilen);
                int occurences = 0;
                recvfrom(sfd, &occurences, sizeof(occurences), 0, (struct sockaddr *)&servaddr, &clilen);
                printf("Occurences: %d\n", occurences);
            }
            else if (choice == 2)
            {
                char search[100];
                printf("Enter the string to be searched: ");
                scanf("%s", search);
                sendto(sfd, search, sizeof(search), 0, (struct sockaddr *)&servaddr, clilen);
                char replace[100];
                printf("Enter the string to be replaced: ");
                scanf("%s", replace);
                sendto(sfd, replace, sizeof(replace), 0, (struct sockaddr *)&servaddr, clilen);
                char result[100];
                recvfrom(sfd, result, sizeof(result), 0, (struct sockaddr *)&servaddr, &clilen);
                printf(result);
            }
            else if (choice == 3)
            {
                char result[100];
                recvfrom(sfd, result, sizeof(result), 0, (struct sockaddr *)&servaddr, &clilen);
                printf(result);
            }
            else if (choice == 4)
            {
                close(sfd);
                exit(0);
            }
        }
    }
    close(sfd);
    return 0;
}
