#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXSIZE 1024
// Lab4 tcp server
int main()
{
    char buff[MAXSIZE];
    int sockfd, newsockfd, retval;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Socket creation error");
        exit(1);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(9999); // Use a different port number
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    retval = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (retval == -1)
    {
        perror("Binding error");
        exit(1);
    }

    retval = listen(sockfd, 10);
    if (retval == 0)
    {
        printf("Server listening...\n");
    }
    else
    {
        perror("Listening error");
        exit(1);
    }

    addr_size = sizeof(clientaddr);

    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &addr_size);
        if (newsockfd < 0)
        {
            perror("Acceptance error");
            exit(1);
        }

        int choice;
        recv(newsockfd, &choice, sizeof(int), 0);

        switch (choice)
        {
        case 1:
            // Handle registration number request
            {
                char name[MAXSIZE];
                char address[MAXSIZE];
                int pid = getpid();

                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Residential Address: ");
                scanf("%s", address);

                char response[MAXSIZE];
                snprintf(response, sizeof(response), "Name: %s\nResidential Address: %s\nPID: %d", name, address, pid);

                send(newsockfd, response, sizeof(response), 0);
            }
            break;
        case 2:
            // Handle student name request
            {
                char dept[MAXSIZE];
                char semester[MAXSIZE];
                char section[MAXSIZE];
                char courses[MAXSIZE];
                int pid = getpid();

                printf("Enter Department: ");
                scanf("%s", dept);
                printf("Enter Semester: ");
                scanf("%s", semester);
                printf("Enter Section: ");
                scanf("%s", section);
                printf("Enter Courses Registered: ");
                scanf("%s", courses);

                char response[MAXSIZE];
                snprintf(response, sizeof(response), "Department: %s\nSemester: %s\nSection: %s\nCourses Registered: %s\nPID: %d", dept, semester, section, courses, pid);

                send(newsockfd, response, sizeof(response), 0);
            }
            break;
        case 3:
            // Handle subject code request
            {
                char subjectCode[MAXSIZE];
                int pid = getpid();

                printf("Enter Subject Code: ");
                scanf("%s", subjectCode);

                // Implement logic to fetch marks for a subject based on subject code
                // Assuming marks are fetched based on the subject code
                char marks[] = "Subject Code: CSE101\nMarks Obtained: 95";

                send(newsockfd, marks, sizeof(marks), 0);
            }
            break;
        }

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}
