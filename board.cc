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
    mvwaddch(window_.get(),y+1,x+1, ' ' | A_REVERSE);
  }
  else{
    mvwaddch(window_.get(),y+1,x+1, ' ');
  }
}

void Board::Fill(bool manual){
  srand(time(NULL));
  //LOG(INFO)<<"max_y_: "<<max_y_<<"max_y_:"<<min_y_;
  prev_ = now_ = vector<vector<bool>>(LINES - 2 - 2, vector<bool>(COLS - 4 - 2,false));
  if(!manual){
    for (size_t i = 0; i < prev_.size(); ++i){
      for (size_t j = 0; j < prev_[0].size(); ++j){      
	if (rand() % 5 == 0) prev_[i][j] = true;
      }
    }
  }
}

void Board::InitCells(bool manual){
  Fill(manual);
  for (size_t i = 0; i < prev_.size(); ++i){
    for (size_t j = 0; j < prev_[0].size(); ++j){      
      DrawCell(i,j);
    }
  }
  wrefresh(window_.get());
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
  int r_sz = static_cast<int>(prev_.size());
  int c_sz = static_cast<int>(prev_[0].size());
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
#ifdef LOGGER
  LOG(INFO)<<"Calculate Next Evolution...";
#endif
  for (size_t i = 0; i < prev_.size(); ++i){
    for (size_t j = 0; j < prev_[0].size(); ++j){
      now_[i][j] = GetCellNewStatus(i,j);
    }
  }
}

void Board::Update(){
  for (size_t i = 0; i < prev_.size(); ++i){
    for (size_t j = 0; j < prev_[0].size(); ++j){
      prev_[i][j] = now_[i][j];
      DrawCell(i,j);
    }
  }
  wrefresh(window_.get());
}

void Board::SetEnv(){
  initscr();
  curs_set(0);
  window_ = std::unique_ptr<WINDOW, decltype(&delwin)>(newwin(LINES - 2, COLS - 4, 1,2),&delwin);
  getbegyx(window_.get(),min_y_,min_x_);
  if (has_colors() == FALSE){
    throw NoColor();
  }
  cbreak();
  keypad(stdscr,TRUE);
  keypad(window_.get(),TRUE);
  noecho();
  refresh();
  mousemask(BUTTON1_CLICKED,NULL);
}


void Board::GoToMenu(){
  clear();
  wclear(window_.get());
  menu_.Show();
  while(true){
    menu_.UserInteract();
  } 
}

void Board::ManualConfig(){
  int real_y, real_x;
  while(true){
    int ch = getch();
    switch(ch){
    case KEY_MOUSE:
      if(getmouse(&event_) == OK && (event_.bstate & BUTTON1_CLICKED)){
	real_y = event_.y - min_y_ - 1; //vector is from 0 to k
	real_x = event_.x - min_x_ - 1; //but it should correspond to 1 to k + 1 in coordinate 
	if (real_y < 0 || real_x < 0) break;
	prev_[real_y][real_x] = !prev_[real_y][real_x];
	DrawCell(real_y, real_x);
	wrefresh(window_.get());
      }
      break;
    case 10:
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


void Board::Pause(){
  int ch;
  while(true){
    ch = wgetch(window_.get());
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
  ch = wgetch(window_.get());
  switch(ch){
  case 'p':
    nocbreak();
    Pause();
    break;
  case 'b':
    nocbreak();
    throw GoMenu();
  case 'q':
    throw Quit();
  default:
    break;
  }
}
void Board::ContSim(){
  //wtimeout(window_.get(),0);
  while(true){
    Calculate();
    Update();
    halfdelay(1);
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
    //InitColor();
    clear();
    wclear(window_.get());
    wrefresh(window_.get());
    refresh();
  }
  box(window_.get(),0,0);
  wrefresh(window_.get());
  refresh();
  OnEvent(manual);  
}

void Board::GoToHelp(){
  int ch;
  menu_.Hide();
  clear();
  refresh();
  help_.Show();
  while(true){
    ch = getch();
    switch(ch){
    case 'q':
      throw Quit();
    case 'b':
      throw GoMenu();
    default:
      break;
    }
  }
}  
void Board::EventDriven(){
  switch(cur_stat_){
  case MENU:
    GoToMenu();
    break;
  case HELP:
    GoToHelp();
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
#ifdef LOGGER
  LOG(INFO)<<"Start running...";
#endif
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
    catch (const GoHelp & e){
      cur_stat_ = HELP;
    }
    catch (const Quit & e){
      break;
    }
  }
}
