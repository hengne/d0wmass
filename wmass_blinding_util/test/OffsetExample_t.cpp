#include "wmass_blinding_util/OffsetExample.hpp"

#include <iostream>

using namespace std;

int main() {

  cout<<"Instantiate example offset ..."<<endl;
  OffsetExample ex;

  cout<<"Retrieving offset:"<<endl;
  double offs=ex.CalculateBlindedMassFromTrueMass(0);
  cout<<"  "<<offs<<endl;

  cout<<"Comparing to expectation:"<<endl;
  double expect=-0.57396996859461069107;
  cout<<" difference: ";
  cout.precision(25);
  cout<<fabs(offs-expect)<<endl;
  if (fabs(offs-expect)<1e-19) {
    cout<<" OK."<<endl;
    return 0;
  } else {
    cout<<" Failure: "<<offs<<" "<<expect<<endl;
    return 1;
  }

}
