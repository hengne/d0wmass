#ifndef INC_PMCSZCAND
#define INC_PMCSZCAND

#include "PMCSParticle.hpp"
#include "PMCSEMObj.hpp"
#include "PMCSRecoil.hpp"
#include "PMCSMet.hpp"

#include <math.h>
#include "TVector2.h"

class PMCSZCand {
 public:
  PMCSZCand(PMCSEMObj &emobj1, PMCSEMObj &emobj2, PMCSRecoil &recoil, PMCSMet &met);
  PMCSZCand(PMCSEMObj &emobj1, PMCSEMObj &emobj2);
  ~PMCSZCand();

  int Type(double CutEtaCC, double CutEtaEC1, double CutEtaEC2, bool phimodcut=true, bool trkphimodcut = true) const; //0 for CCCC, 1 for CCEC, 2 for ECEC
  double mass() const; //invariant mass
  double trkcalmass(int cal) const;
  double ppt() const;
  double ppx() const;
  double ppy() const;
  double ppz() const;
  double pE() const;
  double eta() const;
  double phi() const;
  double rapidity() const;
  double GetMt1() const;
  double GetMt2() const;

  double pat() const;
  double pal() const;

  void Print() const;

  // pee and recoil vectors in eta and xi directions
  double p_ee() const;
  double p_ee2() const;
  double recoil() const;
  double recoil2() const;
  double response() const;
  double MagRecoil() const;

  double Angle_EM_EM() const; //angle between two electrons
  double DeltaEta_EM_EM() const; //delta_eta between two electrons
  double DeltaPhi_EM_EM() const; //delta_phi between two electrons
  double DeltaR_EM_EM()const ; //delta_R between two electrons
  double DeltaPhi_EM_Recoil(int emidx) const;  // delta phi between EM and recoil
  double DeltaPhi_EM_Met(int emidx) const;  // delta phi between EM and MET
  double DeltaPhi_Z_Recoil(bool fold=true) const; // delta phi between Z pT and recoil
  double DeltaPhi_Z_Met() const; // delta phi between Z pT and met
  double DeltaPhi_Recoil_Met() const; // delta phi between recoil and MET

  TVector2 Eta_Direction() const; //bisector of two electrons (eta axis)
  TVector2 Xi_Direction() const; //xi axis

  // the two electrons are divided into different physics eta and detector eta categories
  int EtaCategory(double eta1, double eta2, double DetEtaCC, bool phimodcut=true, bool trkphimodcut=true) const;
  int DetEtaCategory(double deteta1, double deteta2, double DetEtaCC, bool phimodcut=true, bool trkphimodcut=true) const;
  // the z divided into phimod categories
  int PhiModCategory(bool trkphimodcut=true) const;
  // the z divided into f categories
  int FzCategory(double fz) const;      // for 6 bins from 1 to 2.2
  int FzCategoryFine(double fz) const;  // for 24 bins from 1 to 2.2
  
  TVector2 GetRecoilVec() const; //get the vector of the recoil jet
  double UPara1() const; //calculate u_para (the projection of the recoil along electron direction)
  double UPara2() const; //calculate u_para (the projection of the recoil along electron direction)
  double UPerp1() const; //calculate u_perp 
  double UPerp2() const; //calculate u_perp 
  double Eta_Balance(double hadronic_response) const; //calculate eta balance
  double Xi_Balance(double hadronic_response) const; //calculate xi balance
  double Eta_ImBalance() const; //calculate eta imbalance
  double Xi_ImBalance() const; //calculate xi imbalance

  //some functions used for determining electron energy scale
  double f_CCCC() const;  //return f value for CC-CC candidates
  double f_CCEC() const;  //return f value for CC-EC candidates
  double f_ECEC() const;  //return f value for EC-EC candidates

  // get some interesting variables in one function
  void getProperties(double& mass, double& zpt) const;

  PMCSEMObj GetElec1() const;
  PMCSEMObj GetElec2() const;
  PMCSRecoil GetRecoil() const;
  PMCSMet GetMet() const;

  // update Recoil and MET information 
  void SetMetRecoil(PMCSRecoil &recoil, PMCSMet &met);

 private:

  void SetA(PMCSEMObj &elec1, PMCSEMObj &elec2);

  double _ppx;
  double _ppy;
  double _ppz;
  double _ppt;
  double _pE;
  double _eta;
  double _phi;

  double _pat;
  double _pal;

  PMCSEMObj _elec1;
  PMCSEMObj _elec2;
  PMCSRecoil _recoil;
  PMCSMet _met;
};

inline double PMCSZCand::pE() const {return _pE;}
inline double PMCSZCand::ppx() const {return _ppx;}
inline double PMCSZCand::ppy() const {return _ppy;}
inline double PMCSZCand::ppz() const {return _ppz;}
inline double PMCSZCand::ppt() const {return _ppt;}
inline double PMCSZCand::eta() const {return _eta;}
inline double PMCSZCand::phi() const {return _phi;}
inline double PMCSZCand::rapidity() const {return (0.5*log((_pE+_ppz)/(_pE-_ppz)));}
inline void PMCSZCand::getProperties(double& zmass, double& zpt) const {
  zmass = mass();
  zpt = ppt();
}

inline double PMCSZCand::pat() const {return _pat;}
inline double PMCSZCand::pal() const {return _pal;}

inline int PMCSZCand::EtaCategory(double eta1, double eta2, double DetEtaCC, bool phimodcut, bool trkphimodcut) const {
  int eta_category = -1;
  int eta_elec[2];
  eta_elec[0] = _elec1.EtaRegion_CC(eta1, DetEtaCC, phimodcut, trkphimodcut);
  eta_elec[1] = _elec2.EtaRegion_CC(eta2, DetEtaCC, phimodcut, trkphimodcut);

  if(eta_elec[0]>-1 && eta_elec[1]>-1) {
    if(eta_elec[0]==0 && eta_elec[1]==0) eta_category=0;
    else if((eta_elec[0]==0 && eta_elec[1]==1) || (eta_elec[0]==1 && eta_elec[1]==0)) eta_category=1; 
    else if((eta_elec[0]==0 && eta_elec[1]==2) || (eta_elec[0]==2 && eta_elec[1]==0)) eta_category=2; 
    else if((eta_elec[0]==0 && eta_elec[1]==3) || (eta_elec[0]==3 && eta_elec[1]==0)) eta_category=3; 
    else if((eta_elec[0]==0 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==0)) eta_category=4; 
    else if(eta_elec[0]==1 && eta_elec[1]==1) eta_category=5; 
    else if((eta_elec[0]==1 && eta_elec[1]==2) || (eta_elec[0]==2 && eta_elec[1]==1)) eta_category=6; 
    else if((eta_elec[0]==1 && eta_elec[1]==3) || (eta_elec[0]==3 && eta_elec[1]==1)) eta_category=7; 
    else if((eta_elec[0]==1 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==1)) eta_category=8; 
    else if(eta_elec[0]==2 && eta_elec[1]==2) eta_category=9; 
    else if((eta_elec[0]==2 && eta_elec[1]==3) || (eta_elec[0]==3 && eta_elec[1]==2)) eta_category=10; 
    else if((eta_elec[0]==2 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==2)) eta_category=11; 
    else if(eta_elec[0]==3 && eta_elec[1]==3) eta_category=12; 
    else if((eta_elec[0]==3 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==3)) eta_category=13; 
    else eta_category=14; 
  }
  return eta_category;
}

inline int PMCSZCand::DetEtaCategory(double deteta1, double deteta2, double DetEtaCC, bool phimodcut, bool trkphimodcut) const {
  int deteta_category = -1;
  int deteta_elec[2];
  deteta_elec[0] = _elec1.DetEtaRegion_CC(deteta1, DetEtaCC, phimodcut, trkphimodcut);
  deteta_elec[1] = _elec2.DetEtaRegion_CC(deteta2, DetEtaCC, phimodcut, trkphimodcut);

  if(deteta_elec[0]>-1 && deteta_elec[1]>-1) {
    if(deteta_elec[0]==0 && deteta_elec[1]==0) deteta_category=0;
    else if((deteta_elec[0]==0 && deteta_elec[1]==1) || (deteta_elec[0]==1 && deteta_elec[1]==0)) deteta_category=1;
    else if((deteta_elec[0]==0 && deteta_elec[1]==2) || (deteta_elec[0]==2 && deteta_elec[1]==0)) deteta_category=2;
    else if((deteta_elec[0]==0 && deteta_elec[1]==3) || (deteta_elec[0]==3 && deteta_elec[1]==0)) deteta_category=3;
    else if((deteta_elec[0]==0 && deteta_elec[1]==4) || (deteta_elec[0]==4 && deteta_elec[1]==0)) deteta_category=4;
    else if(deteta_elec[0]==1 && deteta_elec[1]==1) deteta_category=5;
    else if((deteta_elec[0]==1 && deteta_elec[1]==2) || (deteta_elec[0]==2 && deteta_elec[1]==1)) deteta_category=6;
    else if((deteta_elec[0]==1 && deteta_elec[1]==3) || (deteta_elec[0]==3 && deteta_elec[1]==1)) deteta_category=7;
    else if((deteta_elec[0]==1 && deteta_elec[1]==4) || (deteta_elec[0]==4 && deteta_elec[1]==1)) deteta_category=8;
    else if(deteta_elec[0]==2 && deteta_elec[1]==2) deteta_category=9;
    else if((deteta_elec[0]==2 && deteta_elec[1]==3) || (deteta_elec[0]==3 && deteta_elec[1]==2)) deteta_category=10;
    else if((deteta_elec[0]==2 && deteta_elec[1]==4) || (deteta_elec[0]==4 && deteta_elec[1]==2)) deteta_category=11;
    else if(deteta_elec[0]==3 && deteta_elec[1]==3) deteta_category=12;
    else if((deteta_elec[0]==3 && deteta_elec[1]==4) || (deteta_elec[0]==4 && deteta_elec[1]==3)) deteta_category=13;
    else deteta_category=14;
  }
  return deteta_category;
}


inline int PMCSZCand::PhiModCategory(bool trkphimodcut) const {
  // phimod regions defined as 0 for [0.0,0.1], 1 for (0.1,0.2], 2 for (0.2,0.3], 3 for (0.3,0.4] and 4 for (0.4,0.5]
  // they are folded so that 0.9 to 1.0 is the same as 0.0 to 0.1. 

  int phimod_category = -1;
  int phimod_elec[2];
  phimod_elec[0] = _elec1.PhiModRegion(trkphimodcut);
  phimod_elec[1] = _elec2.PhiModRegion(trkphimodcut);

  if(phimod_elec[0]>-1 && phimod_elec[1]>-1) {
    // Z phimod category is defined as: 0 for 00 (two electron phimod regions), 1 for 01, 
    // 2 for 02, 3 for 03, 4 for 04, 5 for 11, 6 for 12
    // 7 for 13, 8 for 14, 9 for 22, 10 for 23, 11 for 24, 
    // 12 for 33, 13 for 34, 14 for 44
    if(phimod_elec[0]==0 && phimod_elec[1]==0) phimod_category=0;
    else if((phimod_elec[0]==0 && phimod_elec[1]==1) || (phimod_elec[0]==1 && phimod_elec[1]==0)) phimod_category=1; 
    else if((phimod_elec[0]==0 && phimod_elec[1]==2) || (phimod_elec[0]==2 && phimod_elec[1]==0)) phimod_category=2; 
    else if((phimod_elec[0]==0 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==0)) phimod_category=3; 
    else if((phimod_elec[0]==0 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==0)) phimod_category=4; 
    else if(phimod_elec[0]==1 && phimod_elec[1]==1) phimod_category=5; 
    else if((phimod_elec[0]==1 && phimod_elec[1]==2) || (phimod_elec[0]==2 && phimod_elec[1]==1)) phimod_category=6; 
    else if((phimod_elec[0]==1 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==1)) phimod_category=7; 
    else if((phimod_elec[0]==1 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==1)) phimod_category=8; 
    else if(phimod_elec[0]==2 && phimod_elec[1]==2) phimod_category=9; 
    else if((phimod_elec[0]==2 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==2)) phimod_category=10; 
    else if((phimod_elec[0]==2 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==2)) phimod_category=11; 
    else if(phimod_elec[0]==3 && phimod_elec[1]==3) phimod_category=12; 
    else if((phimod_elec[0]==3 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==3)) phimod_category=13; 
    else phimod_category=14; 
  }
  return phimod_category;
}

inline int PMCSZCand::FzCategoryFine(double fz) const {
  int fz_category = -1;
  if ((fz>=1.0) && (fz<1.05)) fz_category=0;
  else if ((fz>=1.05) && (fz<1.10)) fz_category=1;
  else if ((fz>=1.10) && (fz<1.15)) fz_category=2;
  else if ((fz>=1.15) && (fz<1.20)) fz_category=3;
  else if ((fz>=1.20) && (fz<1.25)) fz_category=4;
  else if ((fz>=1.25) && (fz<1.30)) fz_category=5;
  else if ((fz>=1.30) && (fz<1.35)) fz_category=6;
  else if ((fz>=1.35) && (fz<1.40)) fz_category=7;
  else if ((fz>=1.40) && (fz<1.45)) fz_category=8;
  else if ((fz>=1.45) && (fz<1.50)) fz_category=9;
  else if ((fz>=1.50) && (fz<1.55)) fz_category=10;
  else if ((fz>=1.55) && (fz<1.60)) fz_category=11;
  else if ((fz>=1.60) && (fz<1.65)) fz_category=12;
  else if ((fz>=1.65) && (fz<1.70)) fz_category=13;
  else if ((fz>=1.70) && (fz<1.75)) fz_category=14;
  else if ((fz>=1.75) && (fz<1.80)) fz_category=15;
  else if ((fz>=1.80) && (fz<1.85)) fz_category=16;
  else if ((fz>=1.85) && (fz<1.90)) fz_category=17;
  else if ((fz>=1.90) && (fz<1.95)) fz_category=18;
  else if ((fz>=1.95) && (fz<2.00)) fz_category=19;
  else if ((fz>=2.00) && (fz<2.05)) fz_category=20;
  else if ((fz>=2.05) && (fz<2.10)) fz_category=21;
  else if ((fz>=2.10) && (fz<2.15)) fz_category=22;
  else if ((fz>=2.15) && (fz<2.20)) fz_category=23;
  return fz_category;
}

inline int PMCSZCand::FzCategory(double fz) const {
  int fz_category = -1;
  if ((fz>=1.0) && (fz<1.2)) fz_category=0;
  else if ((fz>=1.2) && (fz<1.4)) fz_category=1;
  else if ((fz>=1.4) && (fz<1.6)) fz_category=2;
  else if ((fz>=1.6) && (fz<1.8)) fz_category=3;
  else if ((fz>=1.8) && (fz<2.0)) fz_category=4;
  else if ((fz>=2.0) && (fz<2.20)) fz_category=5;
  return fz_category;
}

inline void PMCSZCand::Print() const {
  std::cout<<"(pE="<<_pE<<",pT="<<_ppt<<",px="<<_ppx<<",py="<<_ppy<<",pz="<<_ppz<<")"<<std::endl;
}
    
#endif  //INC_PMCSZCAND
