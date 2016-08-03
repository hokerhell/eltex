#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void main()
{
	int fd[2];
	pid_t pid;
	char resstring[14]; 
	pipe(fd);
	pid = fork(); 
	if (pid == 0) 
	{
		close(fd[1]);
		read(fd[0], resstring, 14);
		printf("%s\n",resstring);
		close(fd[0]);
		printf("Child exit\n");		
	}
	else 
	{
		close(fd[0]);
		write(fd[1], "Hello, world!", 14);
		close(fd[1]);
		printf("Parent exit\n");
	};
}	