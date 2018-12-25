#ifndef _BOARD__HPP
#define _BOARD__HPP
#define WIDTH  1
#define HEIGHT 2
#include <vector>
#include <memory>
#include <ncurses.h>
#include <cstdlib>
#include "menu.hpp"
using std::vector;

class Board{
  bool CellLiveOrDead(int dead_num, int live_num, bool status);
  bool GetCellNewStatus(int my_i, int my_j);
  void Fill();
  void DrawCell(int y, int x);
  void ShowMenu();
public:
  void SetEnv();
  void InitCells();
  void InitColor();
  void Calculate();
  void Update();
  
public:
  Board():menu(){}
  void Run();
  
private:
  vector<vector<bool>> prev;
  vector<vector<bool>> now;
  Menu menu;
  bool is_over_;
  int max_y_;
  int max_x_;
};

#endif
