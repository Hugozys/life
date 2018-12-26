#include "help.hpp"
#include <ncurses.h>
#include <set>
using std::set;
Help::Help(){
  mesg_.push_back("The Game of Life, also known simply as Life, is a cellular automation. It is a zero-player game, which means that the evolution");
  mesg_.push_back("of cells is determined by its initial state, requiring no further input.                      ");
  mesg_.push_back("This is a simple program which simulates the celluar automation via classic rules:            ");
  mesg_.push_back("");
  mesg_.push_back("1. Any live cell with fewer than two live neighbors dies, as if by underpopulation.           ");//4
  mesg_.push_back("2. Any live cell with two or three live neighbors lives on to the next generation.            ");//5
  mesg_.push_back("3. Any live cell with more than three live neighbors dies, as if by overpopulation.           ");//6
  mesg_.push_back("4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.");//7
  mesg_.push_back("");
  mesg_.push_back("For more information, you can visit https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life            ");  
  mesg_.push_back("This program offers a simple text user interface for you to interact with the program.               ");
  mesg_.push_back("");
  mesg_.push_back("Menu Options");//12
  mesg_.push_back("");
  mesg_.push_back("- Random Configuration: The program will initialize cells randomly and start simulation automatically");
  mesg_.push_back("- Craft Your Own: You can use your mouse to click on the place where you want to change the state of");
  mesg_.push_back("the cell. Once you are satisfied, press ENTER To start simulation                                   ");
  mesg_.push_back("");
  mesg_.push_back("Keystrokes");//18
  mesg_.push_back("");
  mesg_.push_back("The following keystrokes work at anytime:");
  mesg_.push_back("");
  mesg_.push_back("b - go back to the menu");
  mesg_.push_back("q - quit the game");
  mesg_.push_back("");
  mesg_.push_back("The following keystrokes work during simulation:");
  mesg_.push_back("p - pause the simulation (press p again to resume)");
}

bool Help::IsCustomized(int i){
  set<int> temp = {4,5,6,7,12,18};
  if (temp.count(i)){
    return true;
  }
  return false;
}

void Help::Show(){
  int start_y;
  start_y = (LINES - mesg_.size())/2;
  for (size_t i = 0; i < mesg_.size(); ++i){
    if (IsCustomized(i)){
      mvaddstr(start_y,(COLS-mesg_[i].size())/2, mesg_[i].c_str());
    }
    else{
      mvaddstr(start_y, 0 , mesg_[i].c_str());
    }
    ++start_y;
  }
  refresh();
}
