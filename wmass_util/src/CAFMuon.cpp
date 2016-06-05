#include "wmass_util/CAFMuon.hpp"

using namespace std;

// constructor
CAFMuon::CAFMuon(TMBMuon* p) {
  _tmbmuon_ptr = p;
}
  
// destructor
CAFMuon::~CAFMuon() {}

// sort emobjects according to pT
bool ComparePt(const CAFMuon* mu1, const CAFMuon* mu2) {
  return (mu1->Pt()>mu2->Pt());
}

ClassImp(CAFMuon)
