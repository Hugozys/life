#include <ncurses.h>

WINDOW * create_newwin(int height, int width, int starty, int startx);

void destory_win(WINDOW * todelete);



int main(void){
  WINDOW * my_win;
  int startx, starty, width, height;
  int ch;
  initscr();
  printw("LINES: %d\n",LINES);
  printw("COLS: %d\n",COLS);
  cbreak();
  //raw();
  keypad(stdscr, TRUE);
  height = 3;
  width = 10;
  starty = (LINES - height)/2;
  startx = (COLS - width)/2;
  printw("Press F1 to exit");
  refresh();
  my_win = create_newwin(height, width, starty, startx);
  while ((ch = getch()) != KEY_F(1)){
    switch(ch){
    case KEY_LEFT:
      destory_win(my_win);
      my_win = create_newwin(height,width,starty,--startx);
      break;
    case KEY_RIGHT:
      destory_win(my_win);
      my_win = create_newwin(height,width,starty,++startx);
      break;
    case KEY_UP:
      destory_win(my_win);
      my_win = create_newwin(height,width,--starty,startx);
      break;
    case KEY_DOWN:
      destory_win(my_win);
      my_win = create_newwin(height,width,++starty,startx);
      break;
    }
  }
  endwin();
  return 0;
}
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);
  box(local_win, 0 , 0);
  /* 0, 0 gives default characters
   * for the vertical and horizontal
   * lines
   */
  wrefresh(local_win);
  /* Show that box
   */
  return local_win;
}


void destory_win(WINDOW * local_win){
  wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  wrefresh(local_win);
  delwin(local_win);
}