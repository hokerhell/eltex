#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define NAMEDPIPE_NAME "/home/hoke/pipe/pipe"
#define BUFSIZE	50
void main()
{
	int fd;
	char str[100];
	mkfifo(NAMEDPIPE_NAME, 0777);
	fd = open(NAMEDPIPE_NAME, O_RDWR);	
	while(1)
	{
		printf("type some string\n");
		scanf("%s",str);
		write(fd,str,100);
	};
}