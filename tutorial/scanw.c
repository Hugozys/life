#include <ncurses.h>
#include <string.h>
int main(void){
  char mesg[]="Enter a string: ";
  char str[80];
  int row,col;
  /* ncurses.h includes stdio.h */
  /* message to be appeared on the screen */
  /* to store the number of rows and *
   * the number of colums of the screen */
  initscr();
  /* start the curses mode */
  getmaxyx(stdscr,row,col);
  /* get the number of rows and columns */
  mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
  /* print the message at the center of the screen */
  getstr(str);
  mvprintw(LINES-2, 0, "You Entered: %s", str);
  getch();
  endwin();
  return 0;
}
