#include <commandInterface.hpp>
#include "../devc.hpp"

#define COMMAND_CLASS DevMode
#define COMMAND_NAME "devmode"

class COMMAND_CLASS : public Command<Devc> {
public:
  COMMAND_CLASS() : Command( COMMAND_NAME ){
  }
  string commandFunc( Devc *ptr , list<string> args ){
    string status;
    status = ptr->getDevices()[stoi(getarg(0,args))]->getCurrentMode();
    return status;
  }
};

extern "C"{
  void *command_register( void ){
    static COMMAND_CLASS cmd;
    return (void *)&cmd;
  }
}
