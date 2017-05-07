#include "devc_device.hpp"
#include <cstring>

DevcDevice::DevcDevice(){
  int i;
  rbuf = NULL;
  sbuf = NULL;
  for( i = 0 ; i < 4 ; i++ ){
    mode[i] = 'D';
  }
  status[STATUS_NC]         = "Not connected";
  status[STATUS_OPENFAIL]   = "Open failed";
  status[STATUS_CONNECTED]  = "Connected";
  status[STATUS_READERROR]  = "Read error";
  status[STATUS_WRITEERROR] = "Write error";
  current_binarymap         = "NULL";
}

void DevcDevice::setDeviceID( int _id ){
  id = _id;
}

void DevcDevice::setRecieveDataSize( int _rsize ){
  rsize = _rsize;
  if( !rbuf ){
    delete [] rbuf;
  }
  rbuf = new char[rsize];
}

void DevcDevice::setSendDataSize( int _ssize ){
  ssize = _ssize;
  if( !sbuf ){
    delete [] sbuf;
  }
  sbuf = new char[ssize];
}

void DevcDevice::setCommunicationMode( char *cmode ){
  int i;
  for( i = 0 ; i < 4 ; i++ ){
    mode[i] = cmode[i];
  }
}

void DevcDevice::commWithDevice( void ){
  int i;
  for( i = 0 ; i < 2 ; i++ ){
    if( mode[i*2] == MODE_RECIEVE && mode[i*2+1] != MODE_DISABLE ){
      readData();
    }else if( mode[i*2] == MODE_SEND && mode[i*2+1] != MODE_DISABLE ){
      sendData();
    }
    if( mode[i*2+1] == MODE_ONECE ){
      mode[i*2+1] = MODE_DISABLE;
    }
  }
}

string DevcDevice::getCurrentStatus( void ){
  return status[cur_status];
}

char *DevcDevice::getCurrentMode( void ){
  return mode;
}

int DevcDevice::getCurrentRecvSize( void ){
  return rsize;
}

int DevcDevice::getCurrentSendSize( void ){
  return ssize;
}

int DevcDevice::getDeviceID( void ){
  return id;
}

int DevcDevice::getRecieveData( char *dst ){
  memcpy( dst , rbuf , rsize );
  return rsize;
}

void DevcDevice::setSendData( char *src ){
  memcpy( sbuf , src , ssize );
}

void DevcDevice::switchBinaryMap( string bmap ){
  current_binarymap = bmap;
}

string DevcDevice::currentBinaryMap( void ){
  return current_binarymap;
}
