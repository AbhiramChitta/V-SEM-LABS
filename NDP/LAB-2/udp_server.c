#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>

void reorderString(char *str)
{
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++)
    {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[1000];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}

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
    if (bind(sfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Error in binding\n");
        exit(1); // Use a non-zero exit code to indicate an error.
    }
    else
    {
        printf("Binded successfully\n");
    }
    clilen = sizeof(cliaddr);
    while (1)
    {
        char filename[100];
        recvfrom(sfd, filename, sizeof(filename), 0, (struct sockaddr *)&cliaddr, &clilen);
        printf("Filename received: %s\n", filename);
        FILE *fp = fopen(filename, "r");
        FILE *tmpfile;
        if (fp == NULL)
        {
            sendto(sfd, "File not found", sizeof("File not found"), 0, (struct sockaddr *)&cliaddr, clilen);
            fclose(fp);
            exit(1); // Use a non-zero exit code to indicate an error.
        }
        else
        {
            sendto(sfd, "File found", sizeof("File found"), 0, (struct sockaddr *)&cliaddr, clilen);
            fclose(fp);
            int choice;
            recvfrom(sfd, &choice, sizeof(choice), 0, (struct sockaddr *)&cliaddr, &clilen);
            if (choice == 1)
            {
                fp = fopen(filename, "r");
                char search[100];
                recvfrom(sfd, search, sizeof(search), 0, (struct sockaddr *)&cliaddr, &clilen);
                char line[100];
                int occurrences = 0;
                while (fgets(line, sizeof(line), fp))
                {
                    char *ptr = line;
                    while ((ptr = strstr(ptr, search)))
                    {
                        occurrences++;
                        ptr++;
                    }
                }
                fclose(fp);
                sendto(sfd, &occurrences, sizeof(occurrences), 0, (struct sockaddr *)&cliaddr, clilen);
            }
            else if (choice == 2)
            {
                char search[100];
                char replace[100];
                recvfrom(sfd, search, sizeof(search), 0, (struct sockaddr *)&cliaddr, &clilen);
                recvfrom(sfd, replace, sizeof(replace), 0, (struct sockaddr *)&cliaddr, &clilen);
                printf("Replacing %s with %s\n", search, replace);
                fp = fopen(filename, "r");
                char line[100];
                tmpfile = fopen("temp.txt", "w");
                while (fgets(line, sizeof(line), fp))
                {
                    replaceAll(line, search, replace);
                    fputs(line, tmpfile);
                }
                fclose(fp);
                fclose(tmpfile);
                remove(filename);
                rename("temp.txt", filename);
                sendto(sfd, "Replaced", sizeof("Replaced"), 0, (struct sockaddr *)&cliaddr, clilen);
            }
            else if (choice == 3)
            {
                char line[100];
                tmpfile = fopen("temp.txt", "w");
                fp = fopen(filename, "r");
                while (fgets(line, sizeof(line), fp))
                {
                    reorderString(line);
                    fputs(line, tmpfile);
                }
                fclose(fp);
                fclose(tmpfile);
                remove(filename);
                rename("temp.txt", filename);
                sendto(sfd, "Reordered", sizeof("Reordered"), 0, (struct sockaddr *)&cliaddr, clilen);
            }
        }
    }
    close(sfd);
    return 0;
}
