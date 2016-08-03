int fd, nwritten,count;
	char buffer[100], text[100];
	printf("type some sting\n");
	scanf("%s",buffer);
	count = strlen(buffer);
	if((fd = open( "./new_file",O_CREAT | O_RDWR , S_IRWXO))==-1){
		perror("can't open file ");
		exit(1);
	}
	if ((nwritten = write(fd,buffer,count))==-1){
        perror("can't write file");
        exit(1);
	}
    else
        printf("Wrote %d bytes to file\n",nwritten);
	close(fd);
	
    close(fd);
    if((fd = open( "./new_file", O_RDWR))==-1){
		perror("can't open file ");
		exit(1);
	}	
	if((nwritten = read(fd,text,100))!=-1){
		 printf("%s\n",text);
	}
	else {	
		perror("can't open file ");
		exit(1);
	}
	close(fd);
	unlink("./new_file");
	/*int argc;
    char **argv;
    {
        FILE *fd;
        char linebuf[BUFSIZ];
        int line;
		if (argc != 2) {
        	fprintf (stderr, "Вызов: %s файл\n", argv [0]);
        	exit (1);
        }
		fd = fopen (argv [1], "r");
        if (fd == NULL) {
        	perror (argv [1]);
        	exit (1);
        }
		//signal (SIGINT,goto DONE);

        initscr ();
        noecho ();
        cbreak ();
        nonl ();
        idlok (stdscr, TRUE);

        while (1) {
        	move (0, 0);
            for (line = 0; line < LINES; line++) {
            	if (!fgets (linebuf, sizeof linebuf, fd)) {
                clrtobot ();
                goto DONE;
              	}
            	move (line, 0);
             	printw ("%s", linebuf);
            }
            refresh ();
            if (getch == 'q') goto DONE;
          }
        }
		DONE:
        
        	move (LINES - 1, 0);
        	clrtoeol ();
        	refresh ();
        	endwin ();
        	exit (1);**/
void sig_winch(int signo)
{
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}
void main()
{	
	WINDOW * wnd;
	WINDOW * subwnd;
	initscr();
	signal(SIGWINCH, sig_winch);
	cbreak();
	curs_set(0);
	start_color();
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	wnd = newwin(LINES, COLS, 0, 0);
	wattron(wnd, COLOR_PAIR(1));
	box(wnd, '|', '-');
	subwnd = derwin(wnd, 3, COLS, LINES-3, 0);
	box(subwnd, '|', '-');
	mvprintw (LINES-2, 1, "SAVE CTR-W, SEARCH CTR-E, QUIT CTR-Q");
	wrefresh(subwnd);
	wrefresh(wnd);
	DONE:
	delwin(subwnd);
	delwin(wnd);
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS);
}