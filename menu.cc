#include "menu.hpp"

void Menu::CreateNewWindow(){
  menu_win_.reset(newwin(10,60,2*LINES/5,(COLS-60)/2));
}

void Menu::Show(){
  set_menu_win(menu_.get(), menu_win_.get());
  set_menu_sub(menu_.get(),derwin(menu_win_.get(),6,58,3,1));
  set_menu_mark(menu_.get(), " * ");
  box(menu_win_.get(), 0, 0);
  post_menu(menu_.get());
  wrefresh(menu_win_.get());
}

void Menu::Hide(){
  wclear(menu_win_.get());
  wrefresh(menu_win_.get());
}
