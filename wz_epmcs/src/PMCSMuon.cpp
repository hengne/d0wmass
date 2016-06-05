#include "PMCSMuon.hpp"

using namespace std;

// simple constructor
PMCSMuon::PMCSMuon(double ppid, double pE, double peta, double pphi) {
  _ppid = ppid;
  SetEnergyEtaPhi(pE, peta, pphi);
}

PMCSMuon::~PMCSMuon() {
}

// set Energy, eta, phi
void PMCSMuon::SetEnergyEtaPhi(double pE, double peta, double pphi) {
  _pE = pE;
  _peta = peta;
  _pphi = pphi;

  double theta = 2.*atan(exp(-peta));
  _ppt = pE*sin(theta);
  _ppx = _ppt*cos(pphi);
  _ppy = _ppt*sin(pphi);
  _ppz = pE*cos(theta);
}
