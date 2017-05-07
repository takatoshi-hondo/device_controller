#ifndef __DEVC_BINARY_MAP_HPP__
#define __DEVC_BINARY_MAP_HPP__

#include "../device/devc_device.hpp"
#include <map>
#include <list>

using namespace std;

typedef struct{
  char         mode[4];
  list<string> sendvarname , recvvarname;
  list<int>    sendsize    , recvsize;
  list<double> svalperad   , rvalperad;
  int          totalssize  , totalrsize;
}BinaryMap;

class DevcBinaryMap {
private:
  map<string,BinaryMap> bmap;
  map<string,double>    svar , rvar;
public:
  DevcBinaryMap();
  void loadBinaryMap( string );
  void switchBinaryMap( DevcDevice * , string );
  void parseBinary( DevcDevice * );
  double getVariable( string );
  void   setVariable( string , double );
  void   printVariable( void );
  void getRawBuffer( DevcDevice * , char * );
  void setRawBuffer( DevcDevice * , char * );
};

#endif
