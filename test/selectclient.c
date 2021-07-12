/*
 * @Author: hechen
 * @Date: 2021-07-12 14:53:01
 * @LastEditors: hechen
 * @LastEditTime: 2021-07-12 15:20:12
 * @Description: file content
 */
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
    addr.sin_addr.s_addr=inet_addr("192.168.1.2");
	memset(&(addr.sin_zero),0,sizeof(addr.sin_zero));
	ret=connect(sockfd, (struct sockaddr *) &addr,  sizeof(struct sockaddr));
	if(ret==-1)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	char wtbuffer[20]="hello from client!\n";
    if(write(sockfd,wtbuffer,sizeof(wtbuffer))==-1)
    {
        printf("fail");
        perror("write");
        exit(EXIT_FAILURE);
    }
	close(sockfd);
	return 0;
}

