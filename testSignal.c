#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handleSig(int sign)
{
	printf("ctrl c\n");
	exit(1);
}

int main()
{
	signal(SIGINT,handleSig);
	while(1);
	return 0;
}
