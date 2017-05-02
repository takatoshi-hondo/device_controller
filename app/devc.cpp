#include "devc.hpp"

Devc::Devc( int mdn ){
  int i;
  max_device_num = mdn;
  devs     = new Devc*[max_device_num];
  dlhander = new void*[max_device_num];
  for( i = 0 ; i < max_device_num ; i++ ){
    devs[i]     = NULL;
    dlhander[i] = NULL;
  }
  current_device_num = 0;
}

void Devc::createNewDevice( string soname ){
  registerfunc rf;
  dlhandler[current_device_num] = dlopen( soname.c_str() , RTLD_LAZY );
  rf = dlsym( dlhandler[current_device_num] , "device_register" );
  devs[current_device_num] = rf();
  devs[current_device_num]->setDeviceID( current_device_num );
  current_device_num++;
}


