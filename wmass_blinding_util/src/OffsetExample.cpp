#include "wmass_blinding_util/OffsetExample.hpp"

#include <iostream>

using namespace std;

OffsetExample::OffsetExample() : OffsetMass("BaBar est une jolie manip.",-1,1){
  // As it turns out, this blinding string and range produce the following
  // offset:
  //
  //   (blinded mass) = (true mass) - 5.73969968594610691e-01
}

OffsetExample::~OffsetExample() {
}

