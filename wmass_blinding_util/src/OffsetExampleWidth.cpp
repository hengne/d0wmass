#include "wmass_blinding_util/OffsetExampleWidth.hpp"

#include <iostream>

using namespace std;

OffsetExampleWidth::OffsetExampleWidth() : OffsetWidth("Et si on retournait sur BaBar ?",-0.4,0.4){
  // As it turns out, this blinding string and range produce the following
  // offset:
  //
  //   (blinded width) = (true width) - 2.66838262602686893e-01
}

OffsetExampleWidth::~OffsetExampleWidth() {
}

