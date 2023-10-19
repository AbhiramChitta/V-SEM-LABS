#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#define MAX 100
#define myport 1234
int main()
{
	//create assign  listen accept operate reply
    char buff[MAX];
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{	printf("socket creation error");
		exit(0);
	}
	struct sockaddr_in c_addr;
	c_addr.sin_port = htons(myport);
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(c_addr.sin_zero, '\0', sizeof(c_addr.sin_zero));

	int size = sizeof(struct sockaddr);
	if(connect(sockfd, (struct sockaddr*) &c_addr, sizeof(c_addr))<0)
    {

        printf("%s",buff);
        perror("Error Connecting");
        exit(1);
    }
    strcpy(buff,"Technology");
    send(sockfd,buff,sizeof(buff),0);
    close(sockfd);
}
