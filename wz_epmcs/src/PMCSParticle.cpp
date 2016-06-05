#include "PMCSParticle.hpp"

#include <iostream>

using namespace std;

// default constructor
PMCSParticle::PMCSParticle() {
  _ppid = 0;
  _pE = 999.;
  _peta = 999.;
  _pphi = 999.;
  _ppt = 999.;
  _ppx = 999.;
  _ppy = 999.;
  _ppz = 999.;
}

// simple constructor
// not PMCSParticle(ppid, pE, peta, pphi) 
// since WZ boson pT is not pE*sin(theta)
PMCSParticle::PMCSParticle(double ppid, double pE, 
			   double peta, double pphi, 
			   double ppx, double ppy, double ppz) {
  _ppid = ppid;
  _pE = pE;
  _peta = peta;
  _pphi = pphi;
  _ppx = ppx;
  _ppy = ppy;
  _ppz = ppz;
  _ppt = sqrt(ppx*ppx+ppy*ppy);
}

// complete constructor
PMCSParticle::PMCSParticle(double pE, double peta, double pphi, double ppid,
			   double ppt, double ppx, double ppy, double ppz) {
  
  _pE = pE;
  _peta = peta;
  _pphi = pphi;
  _ppid = ppid;
  _ppt = ppt;
  _ppx = ppx;
  _ppy = ppy;
  _ppz = ppz;
}

void PMCSParticle::SetpTEtaPhi(double pT, double peta, double pphi) {
  _ppt = pT;
  double theta = 2.*atan(exp(-peta));
  _pE = pT/sin(theta);
  _ppx = pT * cos(pphi);
  _ppy = pT * sin(pphi);
  _ppz = _pE * cos(theta);
}

bool PMCSParticle::IsW() const {return((int)(fabs(this->ppid()))==24);}
bool PMCSParticle::IsZ() const {return((int)(this->ppid())==23);}
bool PMCSParticle::IsElectron() const {return((int)(fabs(this->ppid()))==11);}
bool PMCSParticle::IsPhoton() const {return((int)(fabs(this->ppid()))==10);}

double PMCSParticle::Mass() const{
  double mass = _pE*_pE-_ppx*_ppx-_ppy*_ppy-_ppz*_ppz;
  if(mass<0.) mass = 0.;
  return(sqrt(mass));
}

bool ComparePt(const PMCSParticle part1, const PMCSParticle part2) {
  return part1.ppt() > part2.ppt();
}

bool CompareE(const PMCSParticle part1, const PMCSParticle part2) {
  return part1.pE() > part2.pE();
}
