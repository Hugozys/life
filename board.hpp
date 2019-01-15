#ifndef _BOARD__HPP
#define _BOARD__HPP
#include <vector>
#include <memory>
#include <ncurses.h>
#include <cstdlib>
#include "menu.hpp"
#include "help.hpp"
using std::vector;

class Board{
  bool CellLiveOrDead(int dead_num, int live_num, bool status);
  bool GetCellNewStatus(int my_i, int my_j);
  void Fill(bool manual);
  void DrawCell(int y, int x);
  void GoToMenu();
  void GoToHelp();
  void GoToSim(bool manual);
  void OnEvent(bool manual);
  void EventDriven();
  void ContSim();
  void ManualConfig();
  void Pause();
  void PollInput();
  
public:
  void SetEnv();
  void InitCells(bool manual);
  void InitColor();
  void Calculate();
  void Update();
  
public:
  Board():restart_(true),cur_stat_(MENU),window_(nullptr, &delwin){}
  ~Board(){endwin();}
  void Run();
  
private:
  enum STAT{MENU,SIM_CRAFT,SIM_RANDOM,HELP};
  vector<vector<bool>> prev_;
  vector<vector<bool>> now_;
  Menu menu_;
  Help help_;
  bool restart_;
  //int max_y_;
  //int max_x_;
  int min_y_;
  int min_x_;
  MEVENT event_;
  STAT cur_stat_;
  std::unique_ptr<WINDOW, decltype(&delwin)> window_;
};

#endif
