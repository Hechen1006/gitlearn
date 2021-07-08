#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define APORT 9999
int main()
{
	int sockfd;
	int ret;
	struct sockaddr_in addr;
	sockfd=socket(PF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	addr.sin_family = PF_INET;
	addr.sin_port = htons(APORT);
	addr.sin_addr.s_addr=inet_addr("192.168.130.98");
	memset(&(addr.sin_zero),0,sizeof(addr.sin_zero));
	ret=connect(sockfd, (struct sockaddr *) &addr,  sizeof(struct sockaddr));
	if(ret==-1)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	char rdbuffer[50],wtbuffer[50];
	char str[50]="hello from client!";
	if(read(sockfd,rdbuffer,50)==-1)
	{
		printf("fail");
		perror("read");
		exit(EXIT_FAILURE);
	}
	else
	{
		//for(int i=0;i<10;i++)
		printf("rcv from server: %s",rdbuffer);
		//printf("%d\n",*(rdbuffer+i));
	}
	/*
	strcpy(wtbuffer,str);
	if(write(sockfd,wtbuffer,sizeof(wtbuffer))==-1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
	*/	
	close(sockfd);
	return 0;
}

