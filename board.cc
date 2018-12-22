#include "board.hpp"

void Board::InitCells(){
  
}
void Board::InitWindows(){
  initscr();
  if (has_colors() == FALSE){
    endwin();
    throw NoColor();
  }
  cbreak();
  keypad(stdscr,TRUE);
  noecho();
  refresh();
  InitCells();
}

void Board::RunSimulate(){
  InitWindows();
  


}
