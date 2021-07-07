#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
	int sockfd;
	struct sockaddr_in addr;
	//socket initialization
	sockfd=socket(PF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	addr.sin_family=PF_INET;
	addr.sin_port=htons(9999);
	addr.sin_addr.s_addr=inet_addr("192.168.130.98");
	memset(&addr.sin_zero,0,sizeof(addr.sin_zero));
	//bind
	if(bind(sockfd,(struct sockaddr*) &addr,sizeof(struct sockaddr))==-1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	close(sockfd);
	return 0;
}
