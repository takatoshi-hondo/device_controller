#include "devc.hpp"
#include <fstream>
#include <unistd.h>

Devc::Devc(){
  current_device_num = 0;
  devs = NULL;
  dlhandler = NULL;
  th_exit = false;
}

Devc::Devc( int mdn ){
  setDeviceNum( mdn );
}

void Devc::addRTCommand( Command<Devc> *cmd , list<string> args ){
  rtcommands.push_back( cmd );
  cmd->commandFunc( this , args );
}

void Devc::removeRTCommand( Command<Devc> *cmd ){
  rtcommands.remove( cmd );
}

void Devc::execRTCommands( void ){
  list<Command<Devc>* >::iterator it = rtcommands.begin();
  list<string> nullargs;
  if( !rtcommands.empty() ){
    while( it != rtcommands.end() ){
      (*it)->commandFunc( this , nullargs );
      ++it;
    }
  }
}

void Devc::setDeviceNum( int mdn ){
  int i;
  if( devs == NULL ){
    max_device_num = mdn;
    devs      = new DevcDevice*[max_device_num];
    dlhandler = new void*[max_device_num];
    for( i = 0 ; i < max_device_num ; i++ ){
      devs[i]      = NULL;
      dlhandler[i] = NULL;
    }
    current_device_num = 0;
  }
}

void Devc::createNewDevice( string soname ){
  registerfunc rf;
  if( current_device_num < max_device_num ){
    dlhandler[current_device_num] = dlopen( soname.c_str() , RTLD_LAZY );
    if( dlhandler[current_device_num] != NULL ){
      rf = (registerfunc)dlsym( dlhandler[current_device_num] , "device_register" );
      devs[current_device_num] = (DevcDevice*)rf();
      devs[current_device_num]->setDeviceID( current_device_num );
      current_device_num++;
    }else{
      cerr << dlerror() << endl;
    }
  }
}

void Devc::setCommConf( int id , int rsize , int ssize , char *mode ){
  devs[id]->setRecieveDataSize( rsize );
  devs[id]->setSendDataSize( ssize );
  devs[id]->setCommunicationMode( mode );
}

void Devc::setDeviceConf( int id ,  list<string> params ){
  devs[id]->setDeviceConf( params );
}

void Devc::loadBinaryMap( string fname ){
  bmap.loadBinaryMap( fname );
}

void Devc::switchBinaryMap( int id , string mname ){
  bmap.switchBinaryMap( devs[id] , mname );
}

void Devc::setRawBuffer( int id , char *buf ){
  bmap.setRawBuffer( devs[id] , buf );
}

void Devc::getRawBuffer( int id , char *buf ){
  bmap.getRawBuffer( devs[id] , buf );
}

void Devc::openDevice( int id ){
  devs[id]->openDevice();
}

DevcDevice **Devc::getDevices( void ){
  return devs;
}

DevcBinaryMap *Devc::getBinaryMap( void ){
  return &bmap;
}

void Devc::openDevice( void ){
  int i;
  for( i = 0 ; i < current_device_num ; i++ ){
    devs[i]->openDevice();
  }
}

void Devc::mainLoop( void ){
  int i;
  for( i = 0 ; i < current_device_num ; i++ ){
    devs[i]->commWithDevice();
  }
  for( i = 0 ; i < current_device_num ; i++ ){
    if( devs[i]->currentBinaryMap() != "NULL" ){
      bmap.parseBinary( devs[i] );
    }
  }
}

void Devc::closeDevice( int id ){
  devs[id]->closeDevice();
}

void Devc::closeDevice( void ){
  int i;
  for( i = 0 ; i < current_device_num ; i++ ){
    devs[i]->closeDevice();
  }
}

void Devc::rtThreadExit( void ){
  th_exit = true;
}

bool Devc::threadExit( void ){
  return th_exit;
}

Devc::~Devc(){
  int i;
  cerr << "Destructing class Devc" << endl;
  for( i = 0 ; i < current_device_num ; i++ ){
    dlclose( dlhandler[i] );
  }
  if( devs != NULL ){
    delete [] devs;
  }
  if( dlhandler != NULL ){
    delete [] dlhandler;
  }
}

void rt_thread_task( Devc *devc , bool blocking ){
  sigset_t         ss;
  int              signo;

  while( 1 ){
    if( devc->threadExit() ){
      break;
    }
    if( !blocking ){
      usleep(10000);
    }
    devc->execRTCommands();
    devc->mainLoop();
  }
}

void nonrt_thread_task( Devc *devc , CommandManager<Devc> *cm ){
  try{
    while( 1 ){
      if( devc->threadExit() ){
	break;
      }
    }
    //cm->exeCommand();
  }catch( int e ){
  }
}
