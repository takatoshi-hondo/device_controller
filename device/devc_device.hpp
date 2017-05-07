#ifndef __DEVC_DEVICE_HPP__
#define __DEVC_DEVICE_HPP__

#include <iostream>
#include <cstdio>
#include <string>
#include <list>

using namespace std;

class DevcDevice{
protected:
  int     rsize , ssize , id , cur_status;
  char    mode[4];
  char   *rbuf , *sbuf;
private:
  string  status[5];
  string  current_binarymap;
public:
  const static char MODE_RECIEVE    = 'R';
  const static char MODE_SEND       = 'S';
  const static char MODE_CONTINUOUS = 'C';
  const static char MODE_ONECE      = 'O';
  const static char MODE_DISABLE    = 'D';

  const static int  STATUS_NC         = 0;
  const static int  STATUS_OPENFAIL   = 1;
  const static int  STATUS_CONNECTED  = 2;
  const static int  STATUS_READERROR  = 3;
  const static int  STATUS_WRITEERROR = 4;
  DevcDevice();
  void setDeviceID( int );
  void setRecieveDataSize( int );
  void setSendDataSize( int );
  void setCommunicationMode( char * );
  void commWithDevice( void );
  string getCurrentStatus( void );
  char  *getCurrentMode( void );
  int    getCurrentRecvSize( void );
  int    getCurrentSendSize( void );
  int    getDeviceID( void );
  int    getRecieveData( char * );
  void   setSendData( char * );
  void   switchBinaryMap( string );
  string currentBinaryMap( void );
  virtual void setDeviceConf( list<string> ) = 0;
  virtual void openDevice( void )                  = 0;
  virtual void readData( void )                    = 0;
  virtual void sendData( void )                    = 0;
  virtual void closeDevice( void )                 = 0;
};

#endif
