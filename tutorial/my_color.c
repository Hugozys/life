#include <ncurses.h>
#include <stdlib.h>
#define WIDTH 2
#define HEIGHT 1
int main(void){
  int startx, starty;
  int ch;
  initscr();
  if (has_colors() == FALSE){
    endwin();
    printf("Your terminal doesn't support color!\n");
    return (EXIT_FAILURE);
  }
  cbreak();
  keypad(stdscr,TRUE);
  noecho();
  WINDOW * new_win;
  starty = (LINES - HEIGHT)/2;
  startx = (COLS - WIDTH)/2;
  printw("Press F1 to exit");
  //printw("starty: %d, startx: %d",starty, startx);
  refresh();
  new_win = newwin(HEIGHT,WIDTH,starty, startx);
  //box(new_win, 0,0);
  start_color();
  init_color(COLOR_BLACK, 0,0,0);
  init_color(COLOR_WHITE,999,999,999);
  init_pair(1, COLOR_BLACK,COLOR_WHITE);
  init_pair(2, COLOR_WHITE,COLOR_BLACK);
  wrefresh(new_win);
  int color_num = 1;
  while((ch = getch()) != KEY_F(1)){
    wbkgd(new_win,' ' | COLOR_PAIR(color_num));
    wrefresh(new_win);
    color_num = (color_num) % 2 + 1;
  }
  endwin();
  return (EXIT_SUCCESS);
}
