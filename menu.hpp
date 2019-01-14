#ifndef _MENU__HPP
#define _MENU__HPP
#include <string>
#include <vector>
#include <memory>
#include <menu.h>
#include <ncurses.h>
using std::vector;
using std::string;

class Menu{ //4 in total
  void ShowTitle();
public:
  void InitMenu();
  Menu():menu_win_(nullptr,&delwin),choices_(),p_chs_(5, nullptr),menu_(nullptr,&free_menu),title_("Conway's Game of Life Simulator"),inst_("Use up, down arrow and Enter key to select the mode"){}
  void Show();
  void CreateNewWindow();
  void Hide();
  void UserInteract();
  ~Menu()=default;
 private:
  std::unique_ptr<WINDOW, decltype(&delwin)> menu_win_;
  vector<std::unique_ptr<ITEM, decltype(&free_item)>> choices_;
  vector<ITEM *> p_chs_;
  std::unique_ptr<MENU,decltype(&free_menu)> menu_;
  string title_;
  string inst_;
};



#endif
