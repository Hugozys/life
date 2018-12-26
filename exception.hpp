#ifndef _EXCEPTION__HPP
#define _EXCEPTION__HPP
#include <exception>
#include <iostream>

class ValidHelp: public std::exception{};
class InvalidHelp: public std::exception{
public:
  virtual const char * what() const noexcept{
    return "Please use ./life --help or -h to see usage of the game.\n";
  }
};
class NoOptions: public std::exception{};
class NoColor: public std::exception{};
class Quit: public std::exception{};
class Craft: public std::exception{};
class Random: public std::exception{};
class Help: public std::exception{};
class GoMenu: public std::exception{};
#endif
