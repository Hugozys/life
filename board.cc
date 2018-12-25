#include <glog/logging.h>
#include "board.hpp"
#include "exception.hpp"
#include <unistd.h>


void Board::InitColor(){
  start_color();
  init_color(COLOR_WHITE,999,999,999);
  init_color(COLOR_BLACK,10,10,10);
  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  bkgd(COLOR_PAIR(1));
}

void Board::DrawCell(int y, int x){
  if(prev[y][x]){
    mvaddch(y,x, ACS_DIAMOND);
  }
  else{
    mvaddch(y,x, ' ');
  }
}

void Board::Fill(){
  srand(time(NULL));
  prev = now = vector<vector<bool>>(max_y_+1, vector<bool>(max_x_+1,false));
  for (int i = 0; i <= max_y_; ++i){
    for (int j = 0; j <= max_x_; ++j){      
      if (rand() % 10 == 0) prev[i][j] = true;
    }
  }
}
void Board::InitCells(){
  Fill();
  for (int i = 0; i <= max_y_; ++i){
    for (int j = 0; j <= max_x_; ++j){      
      DrawCell(i,j);
    }
  }
}


bool Board::CellLiveOrDead(int dead_num, int live_num, bool status){
  if (status){
    if(live_num > 3 || live_num < 2){
       return false;
    }
    else{
      return true;
    }
  }
  else if (live_num == 3) return true;
  return status;
}

bool Board::GetCellNewStatus(int my_i, int my_j){
  int r_sz = max_y_ + 1;
  int c_sz = max_x_ + 1;
  int dead_num = 0;
  int live_num = 0;
  int neighs[8][2] = {{0,1},{0,-1},{1,0},{-1,0},{-1,-1},{1,1},{-1,1},{1,-1}};
  for (int i = 0; i < 8; ++i){
    int n_i = (my_i + neighs[i][0] + r_sz) % r_sz;
    int n_j = (my_j + neighs[i][1] + c_sz) % c_sz;
    if (prev[n_i][n_j]){
      ++live_num;
    }
    else{
      ++dead_num;
    }
  }
  return CellLiveOrDead(dead_num,live_num,prev[my_i][my_j]);
}

void Board::Calculate(){
  LOG(INFO)<<"Calculate Next Evolution...";
  for (int i = 0; i <= max_y_; ++i){
    for (int j = 0; j <= max_x_; ++j){
      now[i][j] = GetCellNewStatus(i,j);
    }
  }
}

void Board::Update(){
  for (int i = 0; i <= max_y_; ++i){
    for (int j = 0; j <= max_x_; ++j){
      prev[i][j] = now[i][j];
      DrawCell(i,j);
    }
  }
  refresh();
}

void Board::SetEnv(){
  initscr();
  curs_set(0);
  getmaxyx(stdscr,max_y_,max_x_);
  if (has_colors() == FALSE){
    //endwin();
    //throw NoColor();
  }
  cbreak();
  keypad(stdscr,TRUE);
  noecho();
  refresh();
}


void Board::Run(){
  LOG(INFO)<<"Start running...";
  menu.CreateNewWindow();
  menu.Show();
  getch();
  menu.Hide();
  getch();
  menu.Show();
  getch();
  InitColor();
  InitCells();
  refresh();
  
  /*
  while (!is_over_){
    LOG(INFO)<<"Simulate hasn't been over..";
    Calculate();
    Update();
    int itpt = getch();
  }
  */
}

//#endif
