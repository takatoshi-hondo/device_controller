#include <commandInterface.hpp>
#include "../devc.hpp"

#define COMMAND_CLASS SetBinaryMap
#define COMMAND_NAME "setbinarymap"

class COMMAND_CLASS : public Command<Devc> {
public:
  COMMAND_CLASS() : Command( COMMAND_NAME ){
  }
  string commandFunc( Devc *ptr , list<string> args ){
    ptr->loadBinaryMap( args.front() );
    return "";
  }
};

extern "C"{
  void *command_register( void ){
    static COMMAND_CLASS cmd;
    return (void *)&cmd;
  }
}
