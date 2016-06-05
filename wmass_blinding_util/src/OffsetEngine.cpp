#include "wmass_blinding_util/OffsetEngine.hpp"

#include <string>
#include <iostream>
#include <cassert>

#include <math.h>

using namespace std;

OffsetEngine::OffsetEngine() {
  _phrase[0]='\0';
  _theMin=1;
  _theMax=-1;
  _seed=0;
  _offset=pow(3.141,17);
}

OffsetEngine::OffsetEngine(char* phrase, double theMin, double theMax) {

  int l = strlen(phrase);
  if (l<5) {
    cout<<"Blinding string too short - aborting."<<endl;
    assert(0);
  }
  if (l>999) {
    cout<<"Blinding string too long - aborting."<<endl;
    assert(0);
  }
  if (theMin>=theMax) {
    cout<<"Inconsistent offset boundaries - aborting."<<endl;
    assert(0);
  }

  strcpy(_phrase,phrase);
  _theMin=theMin;
  _theMax=theMax;

  _seed=0;
  UInt_t k;
  for (int i=0; i<l; i++) {
    k=(UInt_t)(_phrase[i]);
    k=k<<(8*(i%4));
    _seed+=k;
  }

  TRandom3 r(_seed);
  _offset=_theMin+r.Rndm()*(_theMax-_theMin);

}


OffsetEngine::~OffsetEngine() {
}


double OffsetEngine::daOffset() {
  if (_phrase[0]=='\0') {
    cout<<"Asked for uninitialised offset - aborting."<<endl;
    assert(0);
  }
  return _offset;
}



