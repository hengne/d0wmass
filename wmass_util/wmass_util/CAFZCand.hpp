///////////////////////////////////////////////////////////////////
///    File: CAFZCabd.hpp                                       ///
///    Created: J. Zhu March 3, 2005                            ///
///                                                             ///
///    Purpose: Z candidates                                    ///
///                                                             ///
///////////////////////////////////////////////////////////////////

#ifndef CAFZCAND_HPP
#define CAFZCAND_HPP

#include "wmass_util/CAFEMObj.hpp"
#include "wmass_util/CAFTrack.hpp"
#include "wmass_util/CAFMet.hpp"
#include "tmb_tree/TMBLorentzVector.hpp"
#include "cafe/Event.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include <TVector2.h>

#include <iostream>

class CAFZCand{
 
 public:
  CAFZCand();
  CAFZCand(const CAFEMObj *emobj0, const CAFEMObj *emobj1);
  CAFZCand(const CAFEMObj *emobj0, const CAFEMObj *emobj1, const CAFMet* met, float* vtx=0, bool metIsRaw=false);
  CAFZCand(const CAFEMObj *emobj0, const CAFTrack *trk1);
  CAFZCand(const CAFTrack *trk0, const CAFTrack *trk1);
  virtual ~CAFZCand();

  const CAFEMObj *EM(int nEM) {return _EM[nEM];}
  const CAFTrack *Trk(int nTrk) {return _Trk[nTrk];}

  void print() const;
 
  double E()  const;
  double Px() const;
  double Py() const;
  double Pz() const;
  double Pt() const;  
  double At() const;
  double Al() const;
  double Eta() const;  
  double Phi() const;  
  double Mass() const;
  double Mass_Cal() const; // Z mass calculated using calorimeter eta, not using any track information
  double f_CCCC() const;
  double f_CCEC() const;
  double f_ECEC() const;
  TMBLorentzVector lorentzvector() const;
 
  int Type(double DetEtaCC, double DetEtaEC1, double DetEtaEC2) const; // 0 for CCCC, 1 for CCEC, 2 for ECEC, 3 for other
  int NumTracks() const; // # of tracks (spatial+E/p)
  int NumSpatialTracks() const; // # of spatial tracks
  int NumGoodSpatialTracks(bool require_smt=false) const; // # of good spatial tracks

  // the two electrons are divided into different physics and detector eta categories
  int EtaCategory(double EtaCC) const;
  int DetEtaCategory(double DetEtaCC) const;
  int EMPhiModCategory() const;
  int TrkPhiModCategory() const;                                           // track phi at DCA
  int TrkPhiEM3ModCategory(double trkphiEM3_1, double trkphiEM3_2) const;  // track phi at EM3

  // the z divided into f categories
  int FzCategory(double fz) const;        // for 6 bins from 1 to 2.2
  int FzCategoryFine(double fz) const;    // for 24 bins from 1 to 2.2
  
  bool In_ZPeak(double MassCut1, double MassCut2) const;
  
  double Angle_EM_EM() const;
  TVector2 Eta_Direction() const; // bisector of the two electrons (eta axis)
  TVector2 Xi_Direction() const; // xi direction

  TVector2 GetRecoil(); //get the vector of the recoil jet
  double MagRecoil(); //magnitude of the recoil jet
  double Eta_Balance(); //calculate eta balance
  double Xi_Balance(); //calculate xi balance
  double pee_eta(); //Z pT along eta direction
  double pee_xi(); //Z pT along xi direction
  double recoil_eta(); //recoil along eta direction
  double recoil_xi(); //recoil along xi direction
  TVector2 GetConsistentMET(); // ... and the MET vector that goes with it

 private:

  void SetA(const CAFEMObj *em0, const CAFEMObj *em1);
  void SetA(const CAFEMObj *em0, const CAFTrack *trk1);
  void SetA(const CAFTrack *trk0, const CAFTrack *trk1);
  void SetA(TVector2& e1, TVector2& e2);

  const CAFEMObj *_EM[2];
  const CAFTrack *_Trk[2];
  
  double _E;
  double _Px;
  double _Py;
  double _Pz;
  double _Pt;
  double _At;
  double _Al;
  double _Mass;
  TVector2 _recoil;

  TVector2 _consistentMET;
 
 public:
  ClassDef(CAFZCand, 0);
};

inline double CAFZCand::E() const {return _E;}
inline double CAFZCand::Px() const {return _Px;}
inline double CAFZCand::Py() const {return _Py;}
inline double CAFZCand::Pz() const {return _Pz;}
inline double CAFZCand::Pt() const {return _Pt;}
inline double CAFZCand::At() const {return _At;}
inline double CAFZCand::Al() const {return _Al;}
inline double CAFZCand::Eta() const {return kinem::eta(_Px,_Py,_Pz);}
inline double CAFZCand::Phi() const {return kinem::phi(_Px,_Py);}
inline double CAFZCand::Mass() const {return _Mass;}

inline double CAFZCand::Angle_EM_EM() const {
  TLorentzVector vect_em1 = _EM[0]->lorentzvector();
  TVector3 vect_em2 = _EM[1]->vect3();
  return (vect_em1.Angle(vect_em2)); 
}

// eta categary
inline int CAFZCand::EtaCategory(double EtaCC) const {
  int eta_category = -1;
  
  // electron eta region: 0 for 0<=|eta|<0.2, 1 for 0.2<=|eta|<0.4, 2 for 0.4<=|eta|<0.6, 3 for 0.6<=|eta|<0.8, 4 for 0.8<=|eta|
  int eta_elec[2];
  eta_elec[0] = _EM[0]->EtaRegion_CC(EtaCC);
  eta_elec[1] = _EM[1]->EtaRegion_CC(EtaCC);

  if(eta_elec[0] > -1 && eta_elec[1] > -1) {
    // Z eta category is defined as: 0 for 00 (two electron eta regions), 1 for 01, 
    // 2 for 02, 3 for 03, 4 for 04, 5 for 11, 6 for 12
    // 7 for 13, 8 for 14, 9 for 22, 10 for 23, 11 for 24, 
    // 12 for 33, 13 for 34, 14 for 44
    if(eta_elec[0]==0 && eta_elec[1]==0) eta_category = 0;
    else if ((eta_elec[0]==0 && eta_elec[1]==1) || (eta_elec[0]==1 && eta_elec[1]==0)) eta_category = 1;
    else if ((eta_elec[0]==0 && eta_elec[1]==2) || (eta_elec[0]==2 && eta_elec[1]==0)) eta_category = 2;
    else if ((eta_elec[0]==0 && eta_elec[1]==3) || (eta_elec[0]==3 && eta_elec[1]==0)) eta_category = 3;
    else if ((eta_elec[0]==0 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==0)) eta_category = 4;
    else if (eta_elec[0]==1 && eta_elec[1]==1) eta_category = 5;
    else if ((eta_elec[0]==1 && eta_elec[1]==2) || (eta_elec[0]==2 && eta_elec[1]==1)) eta_category = 6;
    else if ((eta_elec[0]==1 && eta_elec[1]==3) || (eta_elec[0]==3 && eta_elec[1]==1)) eta_category = 7;
    else if ((eta_elec[0]==1 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==1)) eta_category = 8;
    else if (eta_elec[0]==2 && eta_elec[1]==2) eta_category = 9;
    else if ((eta_elec[0]==2 && eta_elec[1]==3) || (eta_elec[0]==3 && eta_elec[1]==2)) eta_category = 10;
    else if ((eta_elec[0]==2 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==2)) eta_category = 11;
    else if (eta_elec[0]==3 && eta_elec[1]==3) eta_category = 12;
    else if ((eta_elec[0]==3 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==3)) eta_category = 13;
    else eta_category = 14;
  }
 
  return eta_category;
}

inline int CAFZCand::DetEtaCategory(double DetEtaCC) const {
  int eta_category = -1;
  
  // electron eta region: 0 for 0<=|eta|<0.2, 1 for 0.2<=|eta|<0.4, 2 for 0.4<=|eta|<0.6, 3 for 0.6<=|eta|<0.8, 4 for 0.8<=|eta|
  int eta_elec[2];
  eta_elec[0] = _EM[0]->DetEtaRegion_CC(DetEtaCC);
  eta_elec[1] = _EM[1]->DetEtaRegion_CC(DetEtaCC);

  if(eta_elec[0] > -1 && eta_elec[1] > -1) {
    // Z eta category is defined as: 0 for 00 (two electron eta regions), 1 for 01, 
    // 2 for 02, 3 for 03, 4 for 04, 5 for 11, 6 for 12
    // 7 for 13, 8 for 14, 9 for 22, 10 for 23, 11 for 24, 
    // 12 for 33, 13 for 34, 14 for 44
    if(eta_elec[0]==0 && eta_elec[1]==0) eta_category = 0;
    else if ((eta_elec[0]==0 && eta_elec[1]==1) || (eta_elec[0]==1 && eta_elec[1]==0)) eta_category = 1;
    else if ((eta_elec[0]==0 && eta_elec[1]==2) || (eta_elec[0]==2 && eta_elec[1]==0)) eta_category = 2;
    else if ((eta_elec[0]==0 && eta_elec[1]==3) || (eta_elec[0]==3 && eta_elec[1]==0)) eta_category = 3;
    else if ((eta_elec[0]==0 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==0)) eta_category = 4;
    else if (eta_elec[0]==1 && eta_elec[1]==1) eta_category = 5;
    else if ((eta_elec[0]==1 && eta_elec[1]==2) || (eta_elec[0]==2 && eta_elec[1]==1)) eta_category = 6;
    else if ((eta_elec[0]==1 && eta_elec[1]==3) || (eta_elec[0]==3 && eta_elec[1]==1)) eta_category = 7;
    else if ((eta_elec[0]==1 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==1)) eta_category = 8;
    else if (eta_elec[0]==2 && eta_elec[1]==2) eta_category = 9;
    else if ((eta_elec[0]==2 && eta_elec[1]==3) || (eta_elec[0]==3 && eta_elec[1]==2)) eta_category = 10;
    else if ((eta_elec[0]==2 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==2)) eta_category = 11;
    else if (eta_elec[0]==3 && eta_elec[1]==3) eta_category = 12;
    else if ((eta_elec[0]==3 && eta_elec[1]==4) || (eta_elec[0]==4 && eta_elec[1]==3)) eta_category = 13;
    else eta_category = 14;
  }
 
  return eta_category;
}

inline int CAFZCand::EMPhiModCategory() const {
  int phimod_category = -1;
  
  // phimod regions defined as 0 for [0.0,0.1], 1 for (0.1,0.2], 2 for (0.2,0.3], 3 for (0.3,0.4] and 4 for (0.4,0.5]
  // they are folded so that 0.9 to 1.0 is the same as 0.0 to 0.1. 
  int phimod_elec[2]; 
  phimod_elec[0] = _EM[0]->EMPhiModRegion();  
  phimod_elec[1] = _EM[1]->EMPhiModRegion();  
  
  if(phimod_elec[0] > -1 && phimod_elec[1] > -1) {
    // Z phimod category is defined as: 0 for 00 (two electron phimod regions), 1 for 01, 
    // 2 for 02, 3 for 03, 4 for 04, 5 for 11, 6 for 12
    // 7 for 13, 8 for 14, 9 for 22, 10 for 23, 11 for 24, 
    // 12 for 33, 13 for 34, 14 for 44
    if(phimod_elec[0]==0 && phimod_elec[1]==0) phimod_category = 0;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==1) || (phimod_elec[0]==1 && phimod_elec[1]==0)) phimod_category = 1;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==2) || (phimod_elec[0]==2 && phimod_elec[1]==0)) phimod_category = 2;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==0)) phimod_category = 3;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==0)) phimod_category = 4;
    else if (phimod_elec[0]==1 && phimod_elec[1]==1) phimod_category = 5;
    else if ((phimod_elec[0]==1 && phimod_elec[1]==2) || (phimod_elec[0]==2 && phimod_elec[1]==1)) phimod_category = 6;
    else if ((phimod_elec[0]==1 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==1)) phimod_category = 7;
    else if ((phimod_elec[0]==1 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==1)) phimod_category = 8;
    else if (phimod_elec[0]==2 && phimod_elec[1]==2) phimod_category = 9;
    else if ((phimod_elec[0]==2 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==2)) phimod_category = 10;
    else if ((phimod_elec[0]==2 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==2)) phimod_category = 11;
    else if (phimod_elec[0]==3 && phimod_elec[1]==3) phimod_category = 12;
    else if ((phimod_elec[0]==3 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==3)) phimod_category = 13;
    else phimod_category = 14;
  }
 
  return phimod_category;
}

// track phi at EM3
inline int CAFZCand::TrkPhiEM3ModCategory(double trkphiEM3_1, double trkphiEM3_2) const {
  int phimod_category = -1;
  
  // phimod regions defined as 0 for [0.0,0.1], 1 for (0.1,0.2], 2 for (0.2,0.3], 3 for (0.3,0.4] and 4 for (0.4,0.5]
  // they are folded so that 0.9 to 1.0 is the same as 0.0 to 0.1. 
  int phimod_elec[2]; 
  phimod_elec[0] = _EM[0]->TrkPhiEM3ModRegion(trkphiEM3_1);  
  phimod_elec[1] = _EM[1]->TrkPhiEM3ModRegion(trkphiEM3_2);  
  
  if(phimod_elec[0] > -1 && phimod_elec[1] > -1) {
    // Z phimod category is defined as: 0 for 00 (two electron phimod regions), 1 for 01, 
    // 2 for 02, 3 for 03, 4 for 04, 5 for 11, 6 for 12
    // 7 for 13, 8 for 14, 9 for 22, 10 for 23, 11 for 24, 
    // 12 for 33, 13 for 34, 14 for 44
    if(phimod_elec[0]==0 && phimod_elec[1]==0) phimod_category = 0;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==1) || (phimod_elec[0]==1 && phimod_elec[1]==0)) phimod_category = 1;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==2) || (phimod_elec[0]==2 && phimod_elec[1]==0)) phimod_category = 2;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==0)) phimod_category = 3;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==0)) phimod_category = 4;
    else if (phimod_elec[0]==1 && phimod_elec[1]==1) phimod_category = 5;
    else if ((phimod_elec[0]==1 && phimod_elec[1]==2) || (phimod_elec[0]==2 && phimod_elec[1]==1)) phimod_category = 6;
    else if ((phimod_elec[0]==1 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==1)) phimod_category = 7;
    else if ((phimod_elec[0]==1 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==1)) phimod_category = 8;
    else if (phimod_elec[0]==2 && phimod_elec[1]==2) phimod_category = 9;
    else if ((phimod_elec[0]==2 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==2)) phimod_category = 10;
    else if ((phimod_elec[0]==2 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==2)) phimod_category = 11;
    else if (phimod_elec[0]==3 && phimod_elec[1]==3) phimod_category = 12;
    else if ((phimod_elec[0]==3 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==3)) phimod_category = 13;
    else phimod_category = 14;
  }
 
  return phimod_category;
}

// track phi at DCA
inline int CAFZCand::TrkPhiModCategory() const {
  int phimod_category = -1;
  
  // phimod regions defined as 0 for [0.0,0.1], 1 for (0.1,0.2], 2 for (0.2,0.3], 3 for (0.3,0.4] and 4 for (0.4,0.5]
  // they are folded so that 0.9 to 1.0 is the same as 0.0 to 0.1. 
  int phimod_elec[2]; 
  phimod_elec[0] = _EM[0]->TrkPhiModRegion();  
  phimod_elec[1] = _EM[1]->TrkPhiModRegion();  
  
  if(phimod_elec[0] > -1 && phimod_elec[1] > -1) {
    // Z phimod category is defined as: 0 for 00 (two electron phimod regions), 1 for 01, 
    // 2 for 02, 3 for 03, 4 for 04, 5 for 11, 6 for 12
    // 7 for 13, 8 for 14, 9 for 22, 10 for 23, 11 for 24, 
    // 12 for 33, 13 for 34, 14 for 44
    if(phimod_elec[0]==0 && phimod_elec[1]==0) phimod_category = 0;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==1) || (phimod_elec[0]==1 && phimod_elec[1]==0)) phimod_category = 1;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==2) || (phimod_elec[0]==2 && phimod_elec[1]==0)) phimod_category = 2;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==0)) phimod_category = 3;
    else if ((phimod_elec[0]==0 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==0)) phimod_category = 4;
    else if (phimod_elec[0]==1 && phimod_elec[1]==1) phimod_category = 5;
    else if ((phimod_elec[0]==1 && phimod_elec[1]==2) || (phimod_elec[0]==2 && phimod_elec[1]==1)) phimod_category = 6;
    else if ((phimod_elec[0]==1 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==1)) phimod_category = 7;
    else if ((phimod_elec[0]==1 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==1)) phimod_category = 8;
    else if (phimod_elec[0]==2 && phimod_elec[1]==2) phimod_category = 9;
    else if ((phimod_elec[0]==2 && phimod_elec[1]==3) || (phimod_elec[0]==3 && phimod_elec[1]==2)) phimod_category = 10;
    else if ((phimod_elec[0]==2 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==2)) phimod_category = 11;
    else if (phimod_elec[0]==3 && phimod_elec[1]==3) phimod_category = 12;
    else if ((phimod_elec[0]==3 && phimod_elec[1]==4) || (phimod_elec[0]==4 && phimod_elec[1]==3)) phimod_category = 13;
    else phimod_category = 14;
  }
 
  return phimod_category;
}

inline int CAFZCand::FzCategory(double fz) const {
  int fz_category = -1;
  if ((fz>=1.0) && (fz<1.2)) fz_category=0;
  else if ((fz>=1.2) && (fz<1.4)) fz_category=1;
  else if ((fz>=1.4) && (fz<1.6)) fz_category=2;
  else if ((fz>=1.6) && (fz<1.8)) fz_category=3;
  else if ((fz>=1.8) && (fz<2.0)) fz_category=4;
  else if ((fz>=2.0) && (fz<2.2)) fz_category=5;
  return fz_category;
}

inline int CAFZCand::FzCategoryFine(double fz) const {
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

// Z mass calculated using calorimeter eta and phi, not using track information at all
inline double CAFZCand::Mass_Cal() const {
  double CalTheta0 = 2.0*atan(exp(-_EM[0]->CalEta()));
  double CalPhi0 = _EM[0]->CalPhi();
  double CalE0 = _EM[0]->CalE();
  double CalPx0 = CalE0 * sin(CalTheta0) * cos(CalPhi0);
  double CalPy0 = CalE0 * sin(CalTheta0) * sin(CalPhi0);
  double CalPz0 = CalE0 * cos(CalTheta0);
  
  double CalTheta1 = 2.0*atan(exp(-_EM[1]->CalEta()));
  double CalPhi1 = _EM[1]->CalPhi();
  double CalE1 = _EM[1]->CalE();
  double CalPx1 = CalE1 * sin(CalTheta1) * cos(CalPhi1);
  double CalPy1 = CalE1 * sin(CalTheta1) * sin(CalPhi1);
  double CalPz1 = CalE1 * cos(CalTheta1);
 
  double mass = (CalE0+CalE1)*(CalE0+CalE1)-(CalPx0+CalPx1)*(CalPx0+CalPx1)-
                (CalPy0+CalPy1)*(CalPy0+CalPy1)-(CalPz0+CalPz1)*(CalPz0+CalPz1);
  if(mass<0.) mass = 0.;
  return (sqrt(mass));
}

inline bool CAFZCand::In_ZPeak(double MassCut1, double MassCut2) const {
  return ( (Mass()>MassCut1) && (Mass()<MassCut2) );
}

inline void CAFZCand::print() const {
std::cout<<"Z candidate pT="<<Pt()<<",mass="<<Mass()<<",px="<<_Px<<",py="<<_Py<<",pz="<<_Pz<<std::endl;
}


#endif // CAFZCAND_HPP
