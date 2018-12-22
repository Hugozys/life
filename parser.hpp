#ifndef _PARSER__HPP
#define _PARSER__HPP
#include <iostream>
class Parser{
public:
  Parser()=default;
  void PrintHelpMessage(){  std::cout<<"Welcome to a simple game of life simulator"<<std::endl;}
  void ReadOptions(int argc, char ** argv);
  void RunSimulate();
};

#endif
