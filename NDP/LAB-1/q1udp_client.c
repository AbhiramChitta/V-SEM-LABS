#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#define myport 1290
int main()
{
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(myport);
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(client.sin_zero,'\0',sizeof(client.sin_zero));
	char buffer[20];
	int a=0,e=0,i=0,o=0,u=0;
	int result[15];
	int size=sizeof(struct sockaddr);
	int len;
	while(1){
	printf("Enter string");
	scanf("%s",buffer);
	if(strcmp(buffer,"halt")==0){
	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client,size);
	printf("closing socket");
	close(sockfd);
	exit(1);
	}
	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client,size);
	recvfrom(sockfd,result,sizeof(result),0,(struct sockaddr *)&client,&size);
	recvfrom(sockfd,&len,sizeof(len),0,(struct sockaddr *)&client,&size);
	recvfrom(sockfd,&a,sizeof(a),0,(struct sockaddr *)&client,&size);
	recvfrom(sockfd,&e,sizeof(e),0,(struct sockaddr *)&client,&size);
	recvfrom(sockfd,&i,sizeof(i),0,(struct sockaddr *)&client,&size);
	recvfrom(sockfd,&o,sizeof(o),0,(struct sockaddr *)&client,&size);
	recvfrom(sockfd,&u,sizeof(u),0,(struct sockaddr *)&client,&size);
	printf("Size of the string = %d\n", len);
	printf("%s\n",result);
	printf("Vowels count:\n");
	printf("A = %d\n", a);
	printf("E = %d\n", e);
	printf("I = %d\n", i);
	printf("O = %d\n", o);
	printf("U = %d\n", u);
	}
	return 0;
	}
		
		
