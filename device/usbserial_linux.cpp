#include "devc_device.hpp"
#include <sstream>

#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <cstdlib>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

class DevcUSBSerialLinux : public DevcDevice{
private:
  string devname , bdr;
  int    fd;
  struct termios oldtio , newtio;
public:
  DevcUSBSerialLinux(){
    cur_status = STATUS_NC;
  }
  void setDeviceConf( list<string> conf ){
    devname = conf.front();
    conf.pop_front();
    bdr     = conf.front();
  }
  void openDevice( void ){
    fd = open( devname.c_str() , O_RDWR | O_NOCTTY );
    if( fd < 0 ){
      cur_status = STATUS_OPENFAIL;
    }else{
      tcgetattr( fd , &oldtio );
      newtio = oldtio;
      newtio.c_cflag = CS8 | CLOCAL | CREAD;
      cfsetspeed( &newtio , (speed_t)atoi(bdr.c_str()) );
      newtio.c_iflag = IGNPAR;
      newtio.c_oflag = 0;
      newtio.c_lflag = 0;
      newtio.c_cc[VTIME] = 30;
      newtio.c_cc[VMIN]  = 0;
      tcflush( fd , TCIFLUSH );
      tcsetattr( fd , TCSANOW , &newtio );
      cur_status = STATUS_CONNECTED;
    }
  }
  void readData( void ){
    int ret;
    ret = read( fd , rbuf , rsize );
    if( ret < rsize ){
      cur_status = STATUS_READERROR;
    }
  }
  void sendData( void ){
    int ret;
    ret = write( fd , sbuf , ssize );
    if( ret < ssize ){
      cur_status = STATUS_WRITEERROR;
    }
  }
  void closeDevice( void ){
    close( fd );
    cur_status = STATUS_NC;
  }
};

extern "C"{
  void *device_register( void ){
    static DevcUSBSerialLinux dev;
    return (void *)&dev;
  }
}
