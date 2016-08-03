#include "pipe.h"
int pipedes[2];
void func1 (char * argv[])
{
	char *argvs[] = { 0, NULL };
	argvs[0]=argv[1];
	dup2 (pipedes[1], 1);
	close (pipedes[0]);
	execvp (argvs[0], argvs);
};
void func2 (char * argv[])
{
	char *argvs[] = { 0, NULL };
	argvs[0]=argv[2];
	dup2 (pipedes[0], 0);
	close (pipedes[1]);
	execvp (argvs[0], argvs);
};
int main (int argc, char * argv[])
{
	pid_t pid;
	pipe(pipedes);
	if (pid=fork() == 0)
	func1 (argv);
	else
	func2 (argv);
	close (pipedes[0]);
	close (pipedes[1]);
	return 0;
}