#ifndef ptools_hpp
#define ptools_hpp

#include "TMath.h"

namespace PTools{

  static double mass(double E1, double px1, double py1,double pz1,
		     double E2, double px2, double py2,double pz2){
    double m2=(E1+E2)*(E1+E2)-(px1+px2)*(px1+px2)-(py1+py2)*(py1+py2)-(pz1+pz2)*(pz1+pz2);
    return (m2>=0)? sqrt(m2): 0;
  }
  
  static double EfficiencyError(double a,double b){
    return TMath::Sqrt(a*(b-a)/b/b/b);
  }  

  static Double_t thetaToEta(Double_t theta){
    return -1.0 * TMath::Log( TMath::Tan(theta/2) );
  }

  static Double_t etaToTheta(Double_t eta){
    return 2.0 * TMath::ATan(TMath::Exp(-eta));
  }
  
  static void fixPhi(Double_t &phi){
    phi = phi>0 ? phi : phi+2*TMath::Pi();
  }

  static void fixPhi(Float_t &phi){
    phi = phi>0 ? phi : phi+2*TMath::Pi();
  }

}

#endif
