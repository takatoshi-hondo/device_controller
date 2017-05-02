#ifndef __BINARY_CONF_HPP__
#define __BINARY_CONF_HPP__

#include <map>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

typedef struct{
  string varname;
  int    dsize;
  double ad2val;
}BinaryConf;

class BinaryConfigurator{
private:
  BinaryConf bconf;
  
};

#endif
