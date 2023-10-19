#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#define myport 1290
int main()
{
	int sockfd;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0){
	printf("\nsocket creation error");
	}
	printf("\nsocket created");
	struct sockaddr_in client,server;
	server.sin_family=AF_INET;
	server.sin_port=htons(myport);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(&(server.sin_zero),'\0',sizeof(server.sin_zero));
	bind(sockfd,(struct sockaddr *)&server,sizeof(struct sockaddr));
	//printf("\nWaiting to receive message");
	char buffer[20];
	int size=sizeof(struct sockaddr);
	int len=0,i,j;
	while(1)
	{
	recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&size);
	if(strcmp(buffer,"halt")==0){
	close(sockfd);
	exit(1);
	}
	len=strlen(buffer);
	int a=0,e=0,i=0,o=0,u=0;
	for(int i=0;i<len;i++){
	switch(buffer[i]){
	case 'a': 
	case 'A': a++;break;
	case 'e': 
	case 'E': e++;break;
	case 'o': 
	case 'O': o++;break;
	case 'i': 
	case 'I': i++;break;
	case 'u': 
	case 'U': u++;break;
	}
	}
	int isPalindrome = 1;  // Assume it's a palindrome initially

    	for (int i = 0, j = len - 1; i < j; i++, j--) {
        if (buffer[i] != buffer[j]) {
            isPalindrome = 0;  // It's not a palindrome
            break;
        	}
    	}
	char result[20];
	if(isPalindrome){
	strcpy(result,"\npalindrome");}
	else{strcpy(result,"\nnot palindrome");}
	sendto(sockfd,result,sizeof(result),0,(struct sockaddr*)& client, size);
	sendto(sockfd,&len,sizeof(len),0,(struct sockaddr*)& client, size);
	sendto(sockfd,&a,sizeof(a),0,(struct sockaddr*)& client, size);
	sendto(sockfd,&e,sizeof(e),0,(struct sockaddr*)& client, size);
	sendto(sockfd,&i,sizeof(i),0,(struct sockaddr*)& client, size);
	sendto(sockfd,&o,sizeof(o),0,(struct sockaddr*)& client, size);
	sendto(sockfd,&u,sizeof(u),0,(struct sockaddr*)& client, size);
	}
	close(sockfd);
	return 0;
}
