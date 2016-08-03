#include "man_2.h"
WINDOW *create_newwin(int height, int width, int starty, int startx)
{ 
	WINDOW *wnd;
	wnd = newwin(height, width, starty, startx);
	wbkgd(wnd, COLOR_PAIR(1));
	box(wnd,0,0);
	wrefresh(wnd); 
	return wnd;
};
void initdir(base *full, DIR* dir,struct dirent *entry)
{	
	dir = opendir(full->dir);
	int i;
	static int *c_ptr=&count;
	chdir(full->dir);
	i=0;
	while ( (entry = readdir(dir)) != NULL)
		sprintf(full->list[i++], "%s",entry->d_name);
	*c_ptr=i;
};
void view(WINDOW* wnd, base *full)
{	
	int x=1,i=0;
	static int *c_ptr=&count;
	wclear(wnd);
	mvwprintw(wnd,30,30,"%d",*c_ptr);
	while((x < LINES-3)&&(i<*c_ptr))
		mvwprintw(wnd,x++,1,"%s",full->list[i++]); 	
	wrefresh(wnd);
};
void loaddir(base *full,int x, DIR* dir,struct dirent *entry)
{	
	int i;
	static int *c_ptr=&count;
	struct stat buff;
	stat(full->list[x-1], &buff);
	switch(buff.st_mode & S_IFMT)
	{
		case S_IFDIR:
			dir =opendir(full->dir);
			chdir(full->list[x-1]);
			getcwd(full->dir,100);
			dir = opendir(full->dir);
			i=0;
			while ((entry = readdir(dir)) != NULL)
				sprintf(full->list[i++], "%s",entry->d_name);
			*c_ptr=i;
			closedir(dir);
			break;
		/*default:
			if(buff.st_mode & S_IXUSR || buff.st_mode & S_IXGRP || buff.st_mode & S_IXOTH)
			{
				openfile(full->list[x-1]);
				initscr();
			} 
			else 
			{
				editfile(full->list[x-1]);
				initscr();
			}
		break;*/
	};
};
void prevdir(base *full,DIR* dir,struct dirent *entry)
{	
	int i;
	static int *c_ptr=&count;
	chdir("..");
	getcwd(full->dir,100);
	dir = opendir(full->dir);
	i=0;
	while ((entry = readdir(dir)) != NULL)
		sprintf(full->list[i++], "%s",entry->d_name);
	*c_ptr=i;
};
void openfile(char *file)
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		execl(file, file, (char*)NULL);
	}
	else
	{
		endwin();
		wait(0);
	}			
};
void editfile(char *file)
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		execlp("/home/hoke/editor/editor", "editor", file, (char*)NULL);
	}
	else 
	{
		endwin();
		wait(0);
	}
};
void copyfile(base *right, int x, base *left)
{
	form my_base;
	sprintf(my_base.what,"%s",right->list[x-1]);
	sprintf(my_base.to,"%s",left->dir);
	pthread_t pth;
	struct stat from_stat;
	if(stat(right->list[x-1], &from_stat) < -1)
		return;
	if((from_stat.st_mode & S_IFMT) == S_IFDIR)
		return;
	pthread_create(&pth, NULL, pthreadcopy,&my_base);
	pthread_join(pth,0);
};
void *pthreadcopy(void *arg)
{
	WINDOW *win = create_newwin(3, 100,((LINES - 3) / 2),((COLS - 50) / 2)-20);
	wrefresh(win);
	form *my_base=(form *) arg;
	int fd1, fd2,i,k, progress=0;
	char *des, *src, buf[100];
	sprintf(buf,"%s",my_base->what);
	struct stat from_stat;
	stat(buf,&from_stat);
	fd1=open(buf,O_RDONLY);
	chdir(my_base->to);
	fd2=open(buf,O_CREAT|O_RDWR, S_IRWXU | S_IRWXG | S_IROTH);
	ftruncate(fd2,from_stat.st_size);
	src = mmap(NULL,from_stat.st_size,PROT_READ,MAP_SHARED,fd1,0);
	des = mmap(NULL,from_stat.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd2,0);
	for (i=0;i<from_stat.st_size;i++)
	{
		des[i] = src[i];
		k = (i * 100)/from_stat.st_size;
		mvwprintw(win,1,k,"|");
		wrefresh(win);
	}
	wclear(win);
	wrefresh(win);
	munmap(src,from_stat.st_size);
	munmap(des,from_stat.st_size);
	close(fd1);
	close(fd2);
};
