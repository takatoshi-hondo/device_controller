#include <commandInterface.hpp>
#include "../devc.hpp"

#define COMMAND_CLASS PrintVar
#define COMMAND_NAME "printvar"

class COMMAND_CLASS : public Command<Devc> {
private:
  bool first;
  int  skip , cnt = 0;
public:
  COMMAND_CLASS() : Command( COMMAND_NAME ){
    first = true;
  }
  string commandFunc( Devc *ptr , list<string> args ){
    if( first = true ){
      if( args.empty() ){
	skip = 1;
      }else{
	skip = stoi(args.front());
	if( skip <= 0 ){
	  skip = 1;
	}
	first = false;
      }
    }
    if( cnt%skip == 0 ){
      ptr->getBinaryMap()->printVariable();
    }
    cnt++;
    return "";
  }
};

extern "C"{
  void *command_register( void ){
    static COMMAND_CLASS cmd;
    return (void *)&cmd;
  }
}
