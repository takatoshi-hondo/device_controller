#ifndef __DEVC_HPP__
#define __DEVC_HPP__

#include "../../device/devc_device.hpp"
#include <dlfcn.h>

typedef void *(*registerfunc)( void );

class Devc{
private:
  DevcDevice **devs;
  vold       **dlhandler;
  int          max_device_num , current_device_num;
public:
  Devc( int );
  void createNewDevice( string );
};

#endif
