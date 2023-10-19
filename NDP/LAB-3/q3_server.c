#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Sort character array
void sort(char *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int sock, nsock;
    struct sockaddr_in server, client;
    char buf[1024];
    pid_t pid;
    socklen_t clilen;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(3425);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Binding error");
        exit(1);
    }
    if (listen(sock, 1) < 0)
    {
        perror("Listening error");
        exit(1);
    }
    clilen = sizeof(client);
    nsock = accept(sock, (struct sockaddr *)&client, &clilen);
    if (nsock < 0)
    {
        perror("Accepting error");
        exit(1);
    }
    while (1)
    {
        recv(nsock, buf, sizeof(buf), 0);
        if (strcmp(buf, "exit\n") == 0)
        {
            close(nsock);
            close(sock);
            break;
        }
        else
        {
            pid = fork();
            if (pid == 0)
            {
                char nums[100];
                int nums_count = 0;
                for (int i = 0; i < strlen(buf); i++)
                {
                    if (buf[i] >= '0' && buf[i] <= '9')
                    {
                        nums[nums_count] = buf[i];
                        nums_count++;
                    }
                }
                nums[nums_count] = '\0';
                sort(nums, nums_count);
                printf("Sorted numbers: %s\n", nums);
                exit(0);
            }
            else if (pid > 0)
            {
                char chars[100];
                int chars_count = 0;
                for (int i = 0; i < strlen(buf); i++)
                {
                    if ((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= 'A' && buf[i] <= 'Z'))
                    {
                        chars[chars_count] = buf[i];
                        chars_count++;
                    }
                }
                chars[chars_count] = '\0';
                sort(chars, chars_count);
                printf("Sorted characters: %s\n", chars);
                wait(NULL);
            }
            else
            {
                perror("Fork error");
                exit(1);
            }
        }
    }

    return 0;
}
