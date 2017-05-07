#include <commandInterface.hpp>
#include "../devc.hpp"

#define COMMAND_CLASS SwitchBinaryMap
#define COMMAND_NAME "switchbinarymap"

class COMMAND_CLASS : public Command<Devc> {
public:
  COMMAND_CLASS() : Command( COMMAND_NAME ){
  }
  string commandFunc( Devc *ptr , list<string> args ){
    ptr->switchBinaryMap( stoi(getarg(0,args)) , getarg(1,args) );
    return "";
  }
};

extern "C"{
  void *command_register( void ){
    static COMMAND_CLASS cmd;
    return (void *)&cmd;
  }
}
