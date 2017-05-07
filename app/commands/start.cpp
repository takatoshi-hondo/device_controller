#include <commandInterface.hpp>
#include "../devc.hpp"

#define COMMAND_CLASS PluginStart
#define COMMAND_NAME "start"

class COMMAND_CLASS : public Command<Devc> {
public:
  COMMAND_CLASS() : Command( COMMAND_NAME ){
  }
  string commandFunc( Devc *ptr , list<string> args ){
    string cmdname = args.front();
    args.pop_front();
    ptr->addRTCommand( (*cmdlist)[cmdname] , args );
    return cmdname;
  }
};

extern "C"{
  void *command_register( void ){
    static COMMAND_CLASS cmd;
    return (void *)&cmd;
  }
}
