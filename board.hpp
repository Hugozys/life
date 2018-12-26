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
  void Fill(bool manual);
  void DrawCell(int y, int x);
  void GoToMenu();
  void GoToSim(bool manual);
  void OnEvent(bool manual);
  void EventDriven();
  void ContSim();
  void ManualConfig();
public:
  void SetEnv();
  void InitCells(bool manual);
  void InitColor();
  void Calculate();
  void Update();
  
public:
  Board():restart_(true),cur_stat_(MENU){}
  ~Board(){
    endwin();
  }
  void Run();
  
private:
  enum STAT{MENU,SIM_CRAFT,SIM_RANDOM};
  vector<vector<bool>> prev_;
  vector<vector<bool>> now_;
  Menu menu_;
  bool restart_;
  int max_y_;
  int max_x_;
  MEVENT event_;
  STAT cur_stat_;
  
};

#endif
