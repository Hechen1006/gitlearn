#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define APORT 8888

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
	socketfd=socket(AF_INET,SOCK_STREAM,0);
	if(socketfd==-1)
	{
		printf("socket!\n");
		exit(1);
	}
    if(bind(socketfd,(struct sockaddr *)&addr,serverlen)==-1)
    {
        printf("bind\n");
        exit(1);
    }
    
    return 0;
}
