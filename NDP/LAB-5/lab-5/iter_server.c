#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 5

// Function to check if two strings are anagrams
int areAnagrams(const char *str1, const char *str2)
{
    int count[256] = {0};

    // If lengths are not equal, they can't be anagrams
    if (strlen(str1) != strlen(str2))
        return 0;

    // Count characters in str1
    for (int i = 0; str1[i] && str2[i]; i++)
    {
        count[str1[i]]++;
        count[str2[i]]--;
    }

    // If all character counts are 0, they are anagrams
    for (int i = 0; i < 256; i++)
    {
        if (count[i] != 0)
            return 0;
    }

    return 1;
}

int main()
{
    int server_socket, client_socket, client_count = 0;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    pid_t pid;
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Error in socket creation");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error in binding");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) == 0)
        printf("Server listening on port %d...\n", PORT);
    else
    {
        perror("Error in listening");
        exit(1);
    }

    while (1)
    {
        addr_size = sizeof(client_addr);
        // Accept a new connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);

        // Prompt the client for two strings
        if ((pid = fork()) == 0)
        {
            close(server_socket);

            printf("Enter the first string: ");
            char str1[100], str2[100];
            recv(client_socket, str1, sizeof(str1), 0);
            printf("Enter the second string: ");
            recv(client_socket, str2, sizeof(str2), 0);

            // Check if the strings are anagrams and send the result to the client
            int result = areAnagrams(str1, str2);
            char result_message[100];
            if (result)
                strcpy(result_message, "The strings are anagrams.");
            else
                strcpy(result_message, "The strings are not anagrams.");

            send(client_socket, result_message, sizeof(result_message), 0);
            close(client_socket);
            exit(0);
        }

        // Close the client socket
        close(client_socket);
    }

    return 0;
}
