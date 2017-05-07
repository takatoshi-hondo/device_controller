#include <commandInterface.hpp>
#include "../devc.hpp"

#define COMMAND_CLASS Nullc
#define COMMAND_NAME "nullc"

class COMMAND_CLASS : public Command<Devc> {
public:
  COMMAND_CLASS() : Command( COMMAND_NAME ){
  }
  string commandFunc( Devc *ptr , list<string> args ){
    return "This is command template";
  }
};

extern "C"{
  void *command_register( void ){
    static COMMAND_CLASS cmd;
    return (void *)&cmd;
  }
}
