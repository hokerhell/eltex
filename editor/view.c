#include "editor.h"

WINDOW *create_newwin(int height, int width, int starty, int startx)
{  WINDOW *local_win;

   local_win = newwin(height, width, starty, startx);
   wrefresh(local_win); 
   return local_win;
}

void destroy_win(WINDOW *local_win)
{  
   wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
   wrefresh(local_win);
   delwin(local_win);
}

void sig_winch(int signo)
{
   struct winsize size;
   ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
   resizeterm(size.ws_row, size.ws_col);
}

void opendir(WINDOW *my_win, WINDOW *wnd,char str[100],int argc, char *argv[])
{
   echo();
   int fd, y=1,x=1,res;
   char ch;
   my_win = create_newwin(3, 50,((LINES - 3) / 2),((COLS - 50) / 2));
   box(my_win, 0 , 0); 
   mvwprintw(my_win,1,1,"tape directory:");
   wrefresh(my_win);
   move(((LINES - 3) / 2)+1,((COLS - 50) / 2)+16);
         if(argc != 0)
            str=argv[1];
         else 
            getstr(str);
   if((fd = open(str,O_CREAT | O_RDWR , S_IRWXO))==-1){
      perror("can't open file ");
      exit(1);
   }
   werase(my_win); 
   wrefresh(my_win);
   while((res = read(fd,&ch,1)) > 0)
   {
      if (ch == '\n')
      {
         y++;
         x=1;
         continue;
      }
      mvwprintw(wnd,y,x++,"%c",ch); 
      wrefresh(wnd);   
   }
   close(fd);
}
void input(WINDOW *wnd)
{  
   int row=1,col=1,c;            
   curs_set(1);
   while(1)
   {  
      move (row,col);
      c = getch ();
      switch (c) 
      {
         case KEY_LEFT:
            if (col > 1) col--;
            else flash ();
            break;
         case KEY_DOWN:
            if (row < LINES - 5) row++;
            else flash ();
            break;
         case KEY_UP:
            if (row > 1) row--;
            else flash ();
            break;
         case KEY_RIGHT:
            if (col < COLS - 2) col++;
            else flash ();
            break;
         case KEY_BACKSPACE:
            if(col>1)
            {
               mvwprintw(wnd,row,--col,"%c",' ');
               wrefresh (wnd);
            }
            else flash();         
            break;
            box(wnd, 0 , 0);
         case KEY_DL:
            deleteln ();
            box(wnd, 0 , 0);
            break;
         default:
            if(c==KEY_F(3)) goto DONE;

            if(col < COLS - 1)
               mvwinsch(wnd, row, ++col-1, c);
            else{
               col=0;
               row++;
               mvwinsch(wnd, row, ++col, c);    
               }     
            box(wnd,0,0);
            wrefresh (wnd);
            
            break;
      }   
   }
   DONE:
   refresh();
};
void save(WINDOW *wnd, char str[100])
{
   int fd,l,n,i,nwritten;
   char ch[1];
   if((fd = open( str, O_RDWR))==-1)
   {
      perror("can't open file1");
      exit(1);
   }
   for (l = 1; l < LINES - 4; l++) 
   {
      n = len(l);
      for (i = 1; i < n; i++)
      {
         ch[0]=mvwinch(wnd,l,i);
         if ((nwritten = write(fd,ch,1)==-1))
         {
            perror("can't write file2");
            exit(1);
         }
      }
      ch[0]='\n';
         if ((nwritten = write(fd,ch,1)==-1))
         {
            perror("can't write file3");
            exit(1);
         }
   }
   close(fd);
};

int len (int lineno)
{
   int linelen = COLS - 1;
   while (linelen >= 0 && mvinch (lineno, linelen) == ' ')
   {
      linelen--;
      return linelen + 1;
   }
};