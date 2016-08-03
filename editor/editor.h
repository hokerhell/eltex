#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <curses.h>
#include <signal.h>
#include <sys/ioctl.h>
WINDOW *create_newwin(int , int , int , int );
void destroy_win(WINDOW *);
void sig_winch(int);
void opendir(WINDOW*,WINDOW*,char*, int, char**);
void input();
void save(WINDOW*, char*);
int len(int);
