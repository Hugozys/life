#ifndef _PARSER__HPP
#define _PARSER__HPP
#include <iostream>
class Parser{
public:
  Parser()=default;
  void PrintHelpMessage();
  void ReadOptions(int argc, char ** argv);
};

#endif
