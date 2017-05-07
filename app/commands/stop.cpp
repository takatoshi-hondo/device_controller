#include <commandInterface.hpp>
#include "../devc.hpp"

#define COMMAND_CLASS PluginStop
#define COMMAND_NAME "stop"

class COMMAND_CLASS : public Command<Devc> {
public:
  COMMAND_CLASS() : Command( COMMAND_NAME ){
  }
  string commandFunc( Devc *ptr , list<string> args ){
    string cmdname = args.front();
    args.pop_front();
    ptr->removeRTCommand( (*cmdlist)[cmdname] );
    return cmdname;
  }
};

extern "C"{
  void *command_register( void ){
    static COMMAND_CLASS cmd;
    return (void *)&cmd;
  }
}
