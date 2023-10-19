#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#define MAX 100
#define myport 1234
int main()
{
    char msg[MAX],buff1[50];
    char buff2[25]="";
    char buff3[25]="";
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);	//socket creation
	struct sockaddr_in	server_addr, c_addr;
	int afd,pid,n;
    int c_addr_len;
	//feeding values into the socket address structure
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(myport);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset( server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero) );

	bind( sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr) );

	//ready for listening
	listen(sockfd, 2);
	printf("The server is ready for listening.\n");
printf("%s",buff3);    int i=0;
    while(i<2)
    {
        c_addr_len=sizeof(c_addr);
        afd = accept(sockfd, (struct sockaddr *) & c_addr, &c_addr_len);
        pid=fork();
        if(pid==0)
        {
                n=recv(afd,msg,MAX,0);
                if(n<=0)
                {
                    close(afd);
                    break;
                }
                printf("Received: %s\n",msg);
                if(i==0)
                {
                    strcat(buff2,msg);
                    printf("%s",buff2);
                }
                else
                {
                    strcat(buff3,msg);
                    printf("%s",buff3);
                }
            //exit(0);
        }
        i++;
    }
    FILE *fp;
    char buff[15];
    printf("Enter filename:");
    scanf("%s",buff);
    fp=fopen(buff,"r");
    fgets(buff1,sizeof(buff1),fp);
    printf("%s",buff1);
}
