#ifndef _MENU__HPP
#define _MENU__HPP
#include <string>
#include <vector>
#include <memory>
#include <menu.h>
#include <ncurses.h>
using std::vector;
using std::string;

class Menu{ //3 in total
 public:
  Menu():choices_(),p_chs_(4, nullptr),menu_win_(nullptr,&delwin),menu_(nullptr,&free_menu){
    const char * choices[] = {
      "Random Configuration",
      "Craft Your Own",
      "Exit",
      NULL
    };
    for (int i = 0; i < 4; ++i){
      choices_.push_back(std::unique_ptr<ITEM,decltype(&free_item)>(new_item(choices[i],choices[i]),&free_item));
      p_chs_[i] = choices_[i].get();
    }
    menu_.reset(new_menu(p_chs_.data()));
  }
  void Show();
  void CreateNewWindow();
  void Hide();
 private:
  vector<std::unique_ptr<ITEM, decltype(&free_item)>> choices_;
  vector<ITEM *> p_chs_;
  std::unique_ptr<WINDOW, decltype(&delwin)> menu_win_;
  std::unique_ptr<MENU,decltype(&free_menu)> menu_;
};



#endif
