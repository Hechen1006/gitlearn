/*
 * @Author: hechen
 * @Date: 2021-07-12 08:41:05
 * @LastEditors: hechen
 * @LastEditTime: 2021-07-12 15:37:03
 * @Description: file content
 */
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define APORT 9999

int main()
{
	fd_set conn;//established fd set;
	int socketfd;
	struct sockaddr_in addr;
	addr.sin_family=PF_INET;
	addr.sin_addr.s_addr=inet_addr("192.168.1.2");
	addr.sin_port=htons(APORT);
	memset(&(addr.sin_zero),0,sizeof(addr.sin_zero));
	int serverlen=sizeof(addr);
	socketfd=socket(PF_INET,SOCK_STREAM,0);
	if(socketfd==-1)
	{
		printf("socket!\n");
		exit(1);
    }
    bind(socketfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(socketfd, 5);
    fd_set clientset;
    FD_ZERO(&clientset);
    FD_SET(socketfd, &clientset);
    while(1)
    {
        int result = select(FD_SETSIZE, &clientset, (fd_set *)0, (fd_set *)0, (struct timeval *)0);//block until rcv socket
        if(result<0)
        {
            printf("select\n");
            exit(1);
        }
    //selected
        for (int fdindex = 0; fdindex < FD_SETSIZE;fdindex++)
        {
            if(FD_ISSET(fdindex,&clientset))
            {
                //fdindex is added
                if(fdindex==socketfd)//server socket, establish socket connection withe client
                {
                    struct sockaddr_in clientaddr;
                    int clientaddrlen = sizeof(clientaddr);
                    int clientfd=accept(socketfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
                    FD_SET(clientfd, &clientset);
                }
                else// client socket, operate client request
                {
                    char readbuff[20];
                    if(read(fdindex, readbuff, sizeof(readbuff))==-1)
                    {
                        printf("read!\n");
                        exit(1);
                    }
                    else
                    {
                        printf("%s\n", readbuff);
                        //client request end, close fd and clear it from set
                        close(fdindex);
                        FD_CLR(fdindex, &clientset);
                    }
                }
            }
        }
    }
    return 0;
}
