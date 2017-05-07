#include "binarymap.hpp"
#include <fstream>
#include <sstream>
#include <cstring>

#define clr		cerr << "\033[2J" //clear
#define location(x,y)	cerr << "\033[" << x << ";" << y << "H"  //move cursor

DevcBinaryMap::DevcBinaryMap(){
}

void DevcBinaryMap::loadBinaryMap( string filename ){
  ifstream ifs( filename.c_str() );
  string   buf;
  BinaryMap tmp;
  
  tmp.totalssize = 0;
  tmp.totalrsize = 0;
  
  while( getline( ifs , buf ) ){
    string       name , mode , bms , bmr;
    stringstream ss( buf );
    getline( ss , name , ':' );
    getline( ss , mode , ':' );
    getline( ss , bms , ':' );
    getline( ss , bmr , ':' );
    memcpy(&tmp.mode[0],mode.c_str(),4);

    stringstream ss_send( bms );
    string       tmp1 , tmp2 , tmp3;
    while( getline( ss_send , tmp1 , ',' ) ){
      getline( ss_send , tmp2 , ',' );
      getline( ss_send , tmp3 , ',' );
      tmp.sendvarname.push_back( tmp1 );
      tmp.sendsize.push_back( stod(tmp2) );
      tmp.svalperad.push_back( stoi(tmp3) );
      svar[tmp1] = 0.0;
      tmp.totalssize += stod(tmp2);
    }

    stringstream ss_recv( bmr );
    while( getline( ss_recv , tmp1 , ',' ) ){
      getline( ss_recv , tmp2 , ',' );
      getline( ss_recv , tmp3 , ',' );
      tmp.recvvarname.push_back( tmp1 );
      tmp.recvsize.push_back( stod(tmp2) );
      tmp.rvalperad.push_back( stoi(tmp3) );
      rvar[tmp1] = 0.0;
      tmp.totalrsize += stod(tmp2);
    }
    
    bmap[name] = tmp;
  }
}

void DevcBinaryMap::switchBinaryMap( DevcDevice *dev , string bmapid ){
  dev->switchBinaryMap( bmapid );
  dev->setRecieveDataSize( bmap[bmapid].totalrsize );
  dev->setSendDataSize( bmap[bmapid].totalssize );
  dev->setCommunicationMode( bmap[bmapid].mode );
}

void DevcBinaryMap::parseBinary( DevcDevice *dev ){
  char     *rbuf , *sbuf;
  int       ptr;
  string    bmapid;
  BinaryMap m;
  list<string>::iterator it_name;
  list<int>::iterator    it_size;
  list<double>::iterator it_conv;

  bmapid = dev->currentBinaryMap();
  m = bmap[bmapid];
  rbuf   = new char[m.totalrsize];
  sbuf   = new char[m.totalssize];

  it_name = m.sendvarname.begin();
  it_size = m.sendsize.begin();
  it_conv = m.svalperad.begin();

  ptr = 0;
  while( it_name != m.sendvarname.end() ){
    if( *it_size == 1 ){
      char tmp;
      tmp = (char)(svar[*it_name]/(*it_conv));
      memcpy( &sbuf[ptr] , &tmp , *it_size );
    }else if( *it_size == 2 ){
      short tmp;
      tmp = (short)(svar[*it_name]/(*it_conv));
      memcpy( &sbuf[ptr] , &tmp , *it_size );
    }else if( *it_size == 4 ){
      int tmp;
      tmp = (int)(svar[*it_name]/(*it_conv));
      memcpy( &sbuf[ptr] , &tmp , *it_size );
    }else if( *it_size == 8 ){
      long tmp;
      tmp = (long)(svar[*it_name]/(*it_conv));
      memcpy( &sbuf[ptr] , &tmp , *it_size );
    }
    ptr += *it_size;
    ++it_name;
    ++it_size;
    ++it_conv;
  }
  dev->setSendData( sbuf );
  
  dev->getRecieveData( rbuf );
  it_name = m.recvvarname.begin();
  it_size = m.recvsize.begin();
  it_conv = m.rvalperad.begin();

  ptr = 0;
  while( it_name != m.recvvarname.end() ){
    if( *it_size == 1 ){
      char tmp;
      memcpy( &tmp , &rbuf[ptr] , *it_size );
      rvar[*it_name] = (double)tmp*(*it_conv);
    }else if( *it_size == 2 ){
      short tmp;
      memcpy( &tmp , &rbuf[ptr] , *it_size );
      rvar[*it_name] = (double)tmp*(*it_conv);
    }else if( *it_size == 4 ){
      int tmp;
      memcpy( &tmp , &rbuf[ptr] , *it_size );
      rvar[*it_name] = (double)tmp*(*it_conv);
    }else if( *it_size == 8 ){
      long tmp;
      memcpy( &tmp , &rbuf[ptr] , *it_size );
      rvar[*it_name] = (double)tmp*(*it_conv);
    }
    ptr += *it_size;
    ++it_name;
    ++it_size;
    ++it_conv;
  }
  
  delete [] rbuf;
  delete [] sbuf;
}

double DevcBinaryMap::getVariable( string varname ){
  return svar[varname];
}

void DevcBinaryMap::setVariable( string varname , double val ){
  rvar[varname] = val;
}

void DevcBinaryMap::getRawBuffer( DevcDevice *dev , char *buf ){
  dev->getRecieveData( buf );
}

void DevcBinaryMap::setRawBuffer( DevcDevice *dev , char *buf ){
  dev->setSendData( buf );
}

void DevcBinaryMap::printVariable( void ){
  int cnt = 0;

  clr;
  location(0,0);
  
  cerr << "########## Send ###########" << endl;
  for( auto it = svar.begin() ; it != svar.end() ; ++it ){
    cerr << it->first << ": " << it->second << "\t";
    cnt++;
    if( cnt == 7 ){
      cnt = 0;
      cerr << endl;
    }
  }
  cerr << endl;
  cerr << "######### Recieve ##########" << endl;
  for( auto it = rvar.begin() ; it != rvar.end() ; ++it ){
    cerr << it->first << ": " << it->second << "\t";
    cnt++;
    if( cnt == 7 ){
      cnt = 0;
      cerr << endl;
    }
  }
}





