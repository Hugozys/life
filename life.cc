#include <cstdlib>
#include "parser.hpp"
#include "exception.hpp"
#include "board.hpp"

int main(int argc, char ** argv){
  Parser ps;
  try{
    ps.ReadOptions(argc,argv);
  }
  catch(const ValidHelp & e){
    ps.PrintHelpMessage();
    return (EXIT_SUCCESS);
  }
  catch (const InvalidHelp & e){
    std::cout<<e.what();
    return (EXIT_SUCCESS);
  }
  
  Board bd;
  bd.RunSimulate();
  return (EXIT_SUCCESS);
}
