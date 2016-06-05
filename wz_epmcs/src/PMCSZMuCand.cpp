#include "PMCSZMuCand.hpp"
#include "AnglesUtil.hpp"

#include <iostream>
using namespace std;

PMCSZMuCand::PMCSZMuCand(PMCSMuon mu1, PMCSMuon mu2) {
  _ppx = mu1.ppx() + mu2.ppx();
  _ppy = mu1.ppy() + mu2.ppy();
  _ppz = mu1.ppz() + mu2.ppz();
  _ppt = sqrt(_ppx*_ppx + _ppy*_ppy);
  _pE = mu1.pE() + mu2.pE();
  _eta = kinem::eta(_ppx, _ppy, _ppz);
  _phi = kinem::phi(_ppx, _ppy);

  _mu1 = mu1;
  _mu2 = mu2;
}

PMCSZMuCand::~PMCSZMuCand() {
}

// return invariant mass
double PMCSZMuCand::mass() const {
  double mass = _pE*_pE-_ppx*_ppx-_ppy*_ppy-_ppz*_ppz;
  if(mass>0.) mass = sqrt(mass);
  else mass = 0.;
  return mass;
}

//return the pointer to the first muon
PMCSMuon PMCSZMuCand::GetMuon1() const {return _mu1;}

//return the pointer to the second muon
PMCSMuon PMCSZMuCand::GetMuon2() const {return _mu2;}

