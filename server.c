#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define aport 9999

int main()
{
	int sockfd,clientfd;
	struct sockaddr_in addr, client_addr;
	int client_len;
	//socket initialization
	sockfd=socket(PF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	addr.sin_family=PF_INET;
	addr.sin_port=htons(aport);
	addr.sin_addr.s_addr=inet_addr("192.168.130.98");
	memset(&addr.sin_zero,0,sizeof(addr.sin_zero));
	//bind
	if(bind(sockfd,(struct sockaddr*) &addr,sizeof(struct sockaddr))==-1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		if(listen(sockfd,5)==-1)
		{
			perror("listen");
			exit(EXIT_FAILURE);
		}
		client_len=sizeof(struct sockaddr);
		clientfd=accept(sockfd,(struct sockaddr *)&client_addr,&client_len);
		if(clientfd==-1)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		else
		{
			break;
		}
	}
	char rdbuffer[50],wtbuffer[50];
	char str[50]="hello from server!\0";
	strcpy(wtbuffer,str);
	//for(int i=0;i<10;i++)
		//printf("%d\n",*(wtbuffer+i));
	if(write(clientfd,wtbuffer,sizeof(wtbuffer))==-1)
	{
		perror("wirite");
		exit(EXIT_FAILURE);
	}
	/*
	if(read(sockfd,rdbuffer,sizeof(wtbuffer))==-1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("rcv from client: %s",rdbuffer);
	}
	*/
	close(clientfd);
	close(sockfd);
	return 0;
}
