#include "menu.hpp"
#include "exception.hpp"
#include <glog/logging.h>
void Menu::CreateNewWindow(){
  menu_win_.reset(newwin(10,60,2*LINES/5,(COLS-60)/2));
  keypad(menu_win_.get(),TRUE);
  set_menu_win(menu_.get(), menu_win_.get());
  set_menu_sub(menu_.get(),derwin(menu_win_.get(),6,58,3,1));
  set_menu_mark(menu_.get(), " * ");
}

void Menu::UserInteract(){
  int c = wgetch(menu_win_.get());
  LOG(INFO)<<"User press: "<<c;
  switch(c){
  case KEY_DOWN:
    menu_driver(menu_.get(), REQ_DOWN_ITEM);
    break;
  case KEY_UP:
    menu_driver(menu_.get(), REQ_UP_ITEM);
    break;
  case 10:
    {
      ITEM * curr = current_item(menu_.get());
      if (curr == p_chs_[0]){
	throw Random();
      }
      else if(curr == p_chs_[1]){
	throw Craft();
      }
      else if (curr == p_chs_[2]){
	throw Help();
      }
      else if(curr == p_chs_[3]){
	throw Quit();
      }
    }
  default:
    break;
  }
  wrefresh(menu_win_.get());
}

void Menu::ShowTitle(){
  mvaddstr(LINES/5,(COLS-static_cast<int>(title_.size()))/2, title_.c_str());
  mvaddstr(2*LINES/5+11, (COLS-static_cast<int>(inst_.size()))/2, inst_.c_str());
  refresh();
}
void Menu::Show(){
  ShowTitle();
  box(menu_win_.get(), 0, 0);
  post_menu(menu_.get());
  wrefresh(menu_win_.get());
}

void Menu::Hide(){
  unpost_menu(menu_.get());
  wclear(menu_win_.get());
}
