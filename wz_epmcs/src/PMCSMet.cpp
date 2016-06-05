#include "PMCSMet.hpp"
#include <TMath.h>

// default constructor
PMCSMet::PMCSMet() {
  _metx = _mety = _met = _metphi = _scalarEt = 0.;  
}

// simple constructor
PMCSMet::PMCSMet(double met_x, double met_y) {
  _metx = met_x;
  _mety = met_y;
  _met = sqrt(met_x*met_x + met_y*met_y);

  _metphi = atan2(met_y, met_x);
  _metphi = (_metphi>=0)? _metphi : TMath::TwoPi()+_metphi;
}

// complete constructor
PMCSMet::PMCSMet(double metx, double mety, double met,
                 double metphi, double scalarEt) {
  _metx = metx;
  _mety = mety;
  _met = met;
  _metphi = metphi;
  _scalarEt = scalarEt;
}

// constructor from EMObjects and Recoil system
PMCSMet::PMCSMet(std::vector<PMCSEMObj> &emobjs, PMCSRecoil &recoil) {
  double metx_sum=0., mety_sum=0.;

  for(int iem=0; iem<emobjs.size(); iem++) { //MAYBE need to add electron pT>5 GeV cut here 
    metx_sum += emobjs[iem].ppx();
    mety_sum += emobjs[iem].ppy();
  }
  
  metx_sum += recoil.Recoilx();
  mety_sum += recoil.Recoily();
  
  // use momentum conservation to get the smeared Missing Energy
  SetMet(-metx_sum, -mety_sum);
}

// set metx, mety
void PMCSMet::SetMet(double met_x, double met_y) {
  _metx = met_x;
  _mety = met_y;
  _met = sqrt(met_x*met_x + met_y*met_y);

  _metphi = atan2(met_y, met_x);
  _metphi = (_metphi>=0)? _metphi : TMath::TwoPi()+_metphi;
}
