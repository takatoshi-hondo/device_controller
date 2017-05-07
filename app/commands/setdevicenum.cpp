#include <commandInterface.hpp>
#include "../devc.hpp"

#define COMMAND_CLASS SetDeviceNum
#define COMMAND_NAME "setdevicenum"

class COMMAND_CLASS : public Command<Devc> {
public:
  COMMAND_CLASS() : Command( COMMAND_NAME ){
  }
  string commandFunc( Devc *ptr , list<string> args ){
    int n = stoi(getarg(0,args));
    ptr->setDeviceNum(n);
    return tostr(n);
  }
};

extern "C"{
  void *command_register( void ){
    static COMMAND_CLASS cmd;
    return (void *)&cmd;
  }
}
