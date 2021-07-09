#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/un.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	int sockfd;
	sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	struct sockaddr_un addr_UNIX;
	int len_UNIX;
	memset(&addr_UNIX,0,sizeof(addr_UNIX));
	addr_UNIX.sun_family=AF_LOCAL;
	char path[50]="./testpath";
	strcpy(addr_UNIX.sun_path,path);
	addr_UNIX.sun_path[0]='\0';
	int errornum=bind(sockfd,(struct sockaddr*)&addr_UNIX,len_UNIX);
	if(error==-1)
	{
		perror("bind");
		exit(1);
	}
	close(sock_UNIX);
	unlink(path);
	return 0;
}
