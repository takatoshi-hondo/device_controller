#include "devc.hpp"
#include <fstream>
#include <thread>

class LC{
private:
  void       **handle;
  int          sonum = 0;
  list<string> cmdname;
public:
  LC( CommandManager<Devc> *cm ){
    registerfunc rf;
    ifstream     ifs( "commands/.extcommand" );
    string       buf;
    list<string> solist;
    int i;
    while( getline( ifs , buf ) ){
      solist.push_back( (string)"commands/" + buf );
      sonum++;
    }
    handle = new void*[sonum];
    for( i = 0 ; i < sonum ; i++ ){
      cerr << "[LC] Loading command " << solist.front() << endl;
      handle[i] = dlopen( solist.front().c_str() , RTLD_LAZY );
      if( handle[i] != NULL ){
	rf = (registerfunc)dlsym( handle[i] , "command_register" );
	cmdname.push_back( ((Command<Devc>*)rf())->getCommandName() );
	cm->addCommand( (Command<Devc>*)rf() );
      }else{
	cerr << dlerror() << endl;
      }
      solist.pop_front();
    }
  }
  ~LC(){
    int i;
    cerr << "Destructing class LC" << endl;
    for( i = 0 ; i < sonum ; i++ ){
      cerr << "[LC] Destructing command " << cmdname.front() << endl;
      cmdname.pop_front();
      dlclose( handle[i] );
    }
    delete [] handle;
  }
};

void defaultSignalHandler( int a ){}

int main( int ac , char **av ){
  StdinReciever        r_stdin( "device controller >> " );
  FileReciever         r_file( "devc.rc" ); //should be command line option
  StdoutSender         s_stdout;
  Devc                 devc;
  CommandManager<Devc> cm( &r_file , &s_stdout , &devc );
  CommandManager<Devc> cm2( &r_stdin , &s_stdout , &devc );
  Params<Devc>         cmd_param;
  LC                   lc( &cm );
  thread               rt_th( rt_thread_task , &devc , false ); //should be command line option
  //thread               nonrt_th( nonrt_thread_task , &devc , &cm2 );
  bool                 first = true;

  cm.addCommand( &cmd_param );
  try{
    while( 1 ){
      if( r_file.isEOF() && first ){
	r_file.close();
	cm.resetReciever( &r_stdin );
	first = false;
      }
      cm.exeCommand();
    }
  }catch( int e ){
    devc.rtThreadExit();
    rt_th.detach();
    //nonrt_th.detach();
  }
}
