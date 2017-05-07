#include <commandInterface.hpp>
#include "../devc.hpp"

#define COMMAND_CLASS CreateNewDevice
#define COMMAND_NAME "createnewdevice"

class COMMAND_CLASS : public Command<Devc> {
public:
  COMMAND_CLASS() : Command( COMMAND_NAME ){
  }
  string commandFunc( Devc *ptr , list<string> args ){
    string soname = getarg(0,args);
    ptr->createNewDevice( soname );
    return "";
  }
};

extern "C"{
  void *command_register( void ){
    static COMMAND_CLASS cmd;
    return (void *)&cmd;
  }
}
