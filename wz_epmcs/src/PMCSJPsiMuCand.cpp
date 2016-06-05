#include "PMCSJPsiMuCand.hpp"
#include "AnglesUtil.hpp"

#include <iostream>
using namespace std;

PMCSJPsiMuCand::PMCSJPsiMuCand(PMCSMuon mu1, PMCSMuon mu2) {
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

PMCSJPsiMuCand::~PMCSJPsiMuCand() {
}

// return invariant mass
double PMCSJPsiMuCand::mass() const {
  double mass = _pE*_pE-_ppx*_ppx-_ppy*_ppy-_ppz*_ppz;
  if(mass>0.) mass = sqrt(mass);
  else mass = 0.;
  return mass;
}

//return the pointer to the first muon
PMCSMuon PMCSJPsiMuCand::GetMuon1() const {return _mu1;}

//return the pointer to the second muon
PMCSMuon PMCSJPsiMuCand::GetMuon2() const {return _mu2;}

