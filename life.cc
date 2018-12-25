#include <cstdlib>
#include <glog/logging.h>
#include "parser.hpp"
#include "exception.hpp"
#include "board.hpp"

int main(int argc, char ** argv){
  google::SetLogDestination(google::GLOG_INFO,"./log" );
  google::InitGoogleLogging(argv[0]);
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
  try{
    bd.SetEnv();
  }
  catch (const NoColor & e){
    std::cout<<"Your terminal doesn't support color.\n"<<std::endl;
    return (EXIT_SUCCESS);
  }
  bd.Run();
  endwin();
  return (EXIT_SUCCESS);
}
