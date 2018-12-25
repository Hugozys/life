#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
  "Choice 1",
  "Choice 2",
  "Choice 3",
  "Choice 4",
  "Exit",
};
int n_choices = sizeof(choices)/sizeof(char*);
void print_menu(WINDOW *menu_win, int highlight);
void report_choice(int mouse_x, int mouse_y, int *p_choice);

int main(void){
  WINDOW * menu_win;
  MEVENT event;
  int highlight = 1;
  int choice = 0;
  int c;
  initscr();
  clear();
  noecho();
  cbreak();
  startx = (80 - WIDTH)/2;
  starty = (24 - HEIGHT)/2;
  menu_win = newwin(HEIGHT,WIDTH, starty, startx);
  wprintw(menu_win, "\e[?1002h");
  keypad(menu_win, TRUE);
  printf("\e[?1002h");
  fflush(stdout);
  mvprintw(0,0, "User arrow keys to go up and down, Press Enter to select a choice");
  refresh();
  print_menu(menu_win, highlight);
  mousemask(ALL_MOUSE_EVENTS,NULL);
  while(1){
    c = wgetch(menu_win);
      switch(c){
      case KEY_MOUSE:
	if(getmouse(&event) == OK){
	  if (event.bstate & REPORT_MOUSE_POSITION){
	    mvprintw(22,1,"Mouse position: %d, %d.",event.x, event.y);
	    refresh();
	    //c = wgetch(menu_win);
	    //report_choice(event.x + 1, event.y + 1, &choice);
	    //print_menu(menu_win,choice);
	  }
	  
	}
	break;
      }
    }
 end:
    endwin();
    return 0;
}

void print_menu(WINDOW *menu_win, int highlight){
  int x, y, i;
  x = 2;
  y = 2;
  box(menu_win, 0,0);
  for (i = 0; i < n_choices; ++i){
    if (highlight == i + 1){
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y,x,"%s",choices[i]);
      wattroff(menu_win,A_REVERSE);
    }
    else{
      mvwprintw(menu_win,y,x,"%s",choices[i]);
    }
    ++y;
  }
  wrefresh(menu_win);
}

void report_choice(int mouse_x, int mouse_y, int *p_choice){
  int i, j, choice;
  i = startx + 2;
  j = starty + 3;
  for (choice = 0; choice < n_choices; ++choice){
    if (mouse_y == j + choice && mouse_x >= i && mouse_x <=i + strlen(choices[choice])){
      if (choice == n_choices - 1)
	*p_choice = -1;
      else
	*p_choice = choice + 1;
      break;
    }
  }
}
