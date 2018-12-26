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
  if(prev_[y][x]){
    mvaddch(y,x, ACS_BLOCK);
  }
  else{
    mvaddch(y,x, ' ');
  }
}

void Board::Fill(bool manual){
  srand(time(NULL));
  prev_ = now_ = vector<vector<bool>>(max_y_+1, vector<bool>(max_x_+1,false));
  if(!manual){
    for (int i = 0; i <= max_y_; ++i){
      for (int j = 0; j <= max_x_; ++j){      
	if (rand() % 10 == 0) prev_[i][j] = true;
      }
    }
  }
}
void Board::InitCells(bool manual){
  Fill(manual);
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
    if (prev_[n_i][n_j]){
      ++live_num;
    }
    else{
      ++dead_num;
    }
  }
  return CellLiveOrDead(dead_num,live_num,prev_[my_i][my_j]);
}

void Board::Calculate(){
  LOG(INFO)<<"Calculate Next Evolution...";
  for (int i = 0; i <= max_y_; ++i){
    for (int j = 0; j <= max_x_; ++j){
      now_[i][j] = GetCellNewStatus(i,j);
    }
  }
}

void Board::Update(){
  for (int i = 0; i <= max_y_; ++i){
    for (int j = 0; j <= max_x_; ++j){
      prev_[i][j] = now_[i][j];
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
    throw NoColor();
  }
  cbreak();
  keypad(stdscr,TRUE);
  noecho();
  refresh();
  mousemask(BUTTON1_CLICKED,NULL);
}


void Board::GoToMenu(){
  clear();
  menu_.Show();
  while(true){
    menu_.UserInteract();
  } 
}

void Board::ManualConfig(){
  while(true){
    int ch = getch();
    switch(ch){
    case KEY_MOUSE:
      if(getmouse(&event_) == OK && (event_.bstate & BUTTON1_CLICKED)){
	prev_[event_.y][event_.x] = !prev_[event_.y][event_.x];
	DrawCell(event_.y,event_.x);
	refresh();
      }
      break;
    case 10:
      return;
    case 'q':
      throw GoMenu();
    default:
      break;
    }
  }
}


void Board::Pause(){
  timeout(-1);
  int ch;
  while(true){
    ch = getch();
    switch(ch){
    case 'p':
      return;
    case 'b':
      throw GoMenu();
    case 'q':
      throw Quit();
    default:
      break;
    }
  }
}

void Board::PollInput(){
  int ch;
  ch = getch();
  switch(ch){
  case 'p':
    Pause();
    timeout(0);
    break;
  case 'b':
    timeout(-1);
    throw GoMenu();
  case 'q':
    throw Quit();
  default:
    break;
  }
}
void Board::ContSim(){
  timeout(0);
  while(true){
    Calculate();
    Update();
    PollInput();
  }
}

void Board::OnEvent(bool manual){
  InitCells(manual);
  if (manual){
    ManualConfig();
  }
  ContSim();
}

void Board::GoToSim(bool manual){
  if (restart_){
    restart_ = false;
    menu_.Hide();
    InitColor();
    clear();
    refresh();
  }
  OnEvent(manual);  
}

void Board::EventDriven(){
  switch(cur_stat_){
  case MENU:
    GoToMenu();
    break;
  case SIM_CRAFT:
    GoToSim(true);
    break;
  case SIM_RANDOM:
    GoToSim(false);
    break;
  }
}

void Board::Run(){
  LOG(INFO)<<"Start running...";
  menu_.CreateNewWindow();
  while (true){
    try{
      EventDriven();
    }
    catch(const Random & e){
      cur_stat_ = SIM_RANDOM;
    }
    catch(const Craft & e){
      cur_stat_ = SIM_CRAFT;
    }
    catch (const GoMenu & e){
      cur_stat_ = MENU;
    }
    catch (const Quit & e){
      break;
    }
  }
}
