#ifndef _BOARD__HPP
#define _BOARD__HPP
#define WIDTH  1
#define HEIGHT 2
#include <vector>
#include <memory>
#include "cell.hpp"
#include <ncurses.h>
using std::vector;

class Board{
  class Cell{
  public:
    Cell(int y, int x):p_win_(newwin(HEIGHT,WIDTH,y,x)),alive_(false){}
    Cell()=default;
  private:
    std::unique_ptr<WINDOW> p_win_;
    bool alive_;
  };
  void InitWindows();
public:
  void RunSimulate();
  
private:
  vector<vector<Cell>> layout_;
  int width_;
  int height_;
};

#endif
