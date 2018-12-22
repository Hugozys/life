#include <getopt.h>
#include "parser.hpp"
#include "exception.hpp"

void Parser::ReadOptions(int argc, char ** argv){
  const char * OPTSTR = "h";
  option LONGOPTS[] = {
    {"help", no_argument, 0, 'h'},
    {0,0,0,0}
  };
  int longopts = -1;
  bool valid_help = false;
  bool cont = true;
  while(cont){
    int result = getopt_long(argc,argv,OPTSTR,LONGOPTS, &longopts);
    switch (result){
    case 'h':
      valid_help = true;
      break;
    case -1:  //no options found
      cont = false;
      if (valid_help){ //if we had a valid help
	throw ValidHelp();
      }
      break;
    case '?': //unrecognized options
    default: //help couldn't have argument
      throw InvalidHelp();
      
    }
  }
  //throw NoOptions();
}
