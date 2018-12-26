#ifndef _HELP__HPP
#define _HELP__HPP
#include <vector>
#include <string>
using std::vector;
using std::string;

class Help{
  bool IsCustomized(int i);
public:
  void Show();
  Help(); 
private:
  vector<string> mesg_;
  vector<int> st_x_;
};


#endif
