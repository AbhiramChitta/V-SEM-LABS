#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5353
#define MAX_BUFFER_SIZE 1024


struct DNSRecord {
    char domain[256];
    char ip[16];
};

// Simulated DNS database
struct DNSRecord database[] = {
    {"example.com", "192.168.1.1"},
    {"google.com", "8.8.8.8"},
    {"yahoo.com", "8.8.4.4"},
  
};

int main() {
    int sockfd, new_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[MAX_BUFFER_SIZE];

   
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        exit(1);
    }

    if (listen(sockfd, 10) == 0) {
        printf("Listening...\n");
    } else {
        perror("Listening failed");
        exit(1);
    }

    addr_size = sizeof(client_addr);
    new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_size);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recv(new_sockfd, buffer, sizeof(buffer), 0);

        char* domain = buffer;
        char* ip = NULL;
        for (int i = 0; i < sizeof(database) / sizeof(database[0]); i++) {
            if (strcmp(domain, database[i].domain) == 0) {
                ip = database[i].ip;
                break;
            }
        }

        if (ip != NULL) {
            send(new_sockfd, ip, strlen(ip), 0);
            printf("Resolved %s to %s\n", domain, ip);
        } else {
            char not_found[] = "Domain not found";
            send(new_sockfd, not_found, strlen(not_found), 0);
            printf("Domain %s not found\n", domain);
        }
    }

    close(new_sockfd);
    close(sockfd);

    return 0;
}
