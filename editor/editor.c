#include "editor.h"
int main(int argc, char **argv)
{	 
	WINDOW *my_win;
	WINDOW *wnd;
	WINDOW *subwnd;
	int ch;	
	char str[100];
	initscr(); 
	keypad(stdscr, TRUE);	
	refresh();
	cbreak();
	noecho();
	curs_set(0);
	mvprintw (LINES-2, 1, "OPEN F1, SAVE F2, EDIT F3,  QUIT F4");
	wnd = create_newwin(LINES-3, COLS, 0, 0);
	subwnd = create_newwin(3, COLS, LINES-3, 0);
	box(wnd, 0 , 0);    
	box(subwnd, 0 , 0); 
  	wrefresh(wnd);
	wrefresh(subwnd);  
	signal(SIGWINCH, sig_winch);
	if(argc!=0) opendir(my_win,wnd,str,argc,argv);
	while((ch = getch())!=KEY_F(4))
	{	
		switch(ch)
		{	
			case KEY_F(1):
				opendir(my_win,wnd,str,argc,argv);
				break;
			case KEY_F(2):
				save(wnd,str);
				break;
			case KEY_F(3):
				input(wnd);
		}
		noecho();
		curs_set(0);

	}
	delwin(subwnd);
	delwin(wnd);
	delwin(my_win);
	refresh();
	endwin();
	exit(EXIT_SUCCESS);
}