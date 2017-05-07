#ifndef __DEVC_HPP__
#define __DEVC_HPP__

#include "../device/devc_device.hpp"
#include "binarymap.hpp"
#include <dlfcn.h>
#include <commandInterface.hpp>

typedef void *(*registerfunc)( void );

class Devc{
private:
  DevcDevice          **devs;
  DevcBinaryMap         bmap;
  void                **dlhandler;
  int                   max_device_num , current_device_num;
  bool                  th_exit;
  list<Command<Devc>* > rtcommands;
public:
  Devc();
  Devc( int );
  void addRTCommand( Command<Devc>* , list<string> );
  void removeRTCommand( Command<Devc>* );
  void execRTCommands( void );

  void setDeviceNum( int );
  void createNewDevice( string );
  void setCommConf( int , int , int , char * );
  void setDeviceConf( int , list<string> );
  
  void loadBinaryMap( string );
  void switchBinaryMap( int , string );
  void setRawBuffer( int , char * );
  void getRawBuffer( int , char * );

  DevcDevice   **getDevices( void );
  DevcBinaryMap *getBinaryMap( void );
  
  void openDevice( int );
  void openDevice( void );
  void mainLoop( void );
  void closeDevice( int );
  void closeDevice( void );
  void rtThreadExit( void );
  bool threadExit( void );
  ~Devc();
};

void rt_thread_task( Devc * );

#endif
