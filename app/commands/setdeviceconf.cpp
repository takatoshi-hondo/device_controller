#include <commandInterface.hpp>
#include "../devc.hpp"

#define COMMAND_CLASS SetDeviceConf
#define COMMAND_NAME "setdeviceconf"

class COMMAND_CLASS : public Command<Devc> {
public:
  COMMAND_CLASS() : Command( COMMAND_NAME ){
  }
  string commandFunc( Devc *ptr , list<string> args ){
    int id = stoi(getarg(0,args));
    args.pop_front();
    ptr->setDeviceConf( id , args );
    return "";
  }
};

extern "C"{
  void *command_register( void ){
    static COMMAND_CLASS cmd;
    return (void *)&cmd;
  }
}
