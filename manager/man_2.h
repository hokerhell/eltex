#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>	
#include <ncurses.h>
typedef struct  
{
	char dir[100];
	char list[400][200];
}base;
typedef struct 
{
	char what[100];
	char to[100];
}form;
int count;
WINDOW *create_newwin(int, int, int, int);
void initdir(base*, DIR*, struct dirent*);
void view(WINDOW*, base*);
void loaddir(base*,int, DIR*,struct dirent*);
void prevdir(base*, DIR*, struct dirent*);
void openfile(char*);
void editfile(char*);
void copyfile(base*,int, base*);
void *pthreadcopy(void*);