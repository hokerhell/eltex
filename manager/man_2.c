#include "man_2.h"
void main()
{
	WINDOW *right_wnd;
	WINDOW *left_wnd;
	WINDOW *sub_wnd;
	base right;
	base left;
	sprintf(right.dir, "%s","/");
	sprintf(left.dir, "%s","/");
	bool k=TRUE;
	int ch;
	int y=1,x=1;
	DIR *dir;
	struct dirent *entry;
	initscr();
	start_color();
	keypad(stdscr, TRUE);		
	refresh();
	noecho();
	curs_set(1);
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	init_pair(2,COLOR_BLUE, COLOR_GREEN);
	right_wnd = create_newwin(LINES-3, COLS/2, 0, 0);
	left_wnd = create_newwin(LINES-3, COLS/2+1, 0, COLS/2);
	sub_wnd = create_newwin(3, COLS, LINES-3, 0);
	mvwprintw(sub_wnd,1,1,"Esc - EXIT | Tab - SWITCH WINDOW | -> OPEN | <- CLOSE | F2 - COPY");
	wrefresh(sub_wnd);
	move(1,1);
	wbkgd(right_wnd,COLOR_PAIR(2));
	initdir(&left, dir, entry);
	view(left_wnd, &left);
	initdir(&right, dir, entry);
	view(right_wnd, &right);
	while((ch = getch())!=0x1b)
	{	
		switch (ch) 
		{	
			case 0x09:
				if (k !=FALSE)
				{	
					x=1;
					y=COLS/2+1;
					wbkgd(left_wnd,COLOR_PAIR(2));
					wbkgd(right_wnd,COLOR_PAIR(1));	
					k=FALSE;
				}
				else
				{	
					x=1;
					y=1;
					wbkgd(right_wnd,COLOR_PAIR(2));
					wbkgd(left_wnd,COLOR_PAIR(1));	
					k=TRUE;
				}
				break;
			case KEY_DOWN:
				if (x < LINES - 4) x++;
				break;
			case KEY_UP:
				if (x > 1) x--;
				break;
			case KEY_RIGHT:
				if (k==TRUE)
				{
					loaddir(&right,x,dir, entry);
					view(right_wnd, &right);	
				}
				else 
				{
					loaddir(&left,x,dir, entry);
					view(left_wnd, &left);
				}
				break;
			case KEY_LEFT:
				if (k==TRUE)
				{	
					prevdir(&right, dir, entry);
					view(right_wnd, &right);	
				}
				else 
				{	
					prevdir(&left, dir, entry);
					view(left_wnd, &left);
				}
				break;
			case KEY_F(2):	
				if (k==TRUE)
				{	
					copyfile(&right, x, &left);


				}
				else 
				{	
					copyfile(&left, x, &right);
				}
		}
		move(x,y);
		wrefresh(left_wnd);
		wrefresh(right_wnd);
	}	
	delwin(right_wnd);
	delwin(left_wnd);
	delwin(sub_wnd);
	echo();	
	endwin();
	closedir(dir);
}