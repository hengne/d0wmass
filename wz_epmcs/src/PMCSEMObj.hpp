#ifndef INC_PMCSEMOBJ
#define INC_PMCSEMOBJ

#include "PMCSParticle.hpp"
#include "PMCSVtx.hpp"

#include "TH2.h"
#include "TVector3.h"

#include <iostream>

class PMCSEMObj:public PMCSParticle {

 friend class EMSmear;
  
 public:
  PMCSEMObj() {;}
  
  // simple constructor
  PMCSEMObj(double ppid, double pE, double peta, double pphi, int index=-1, double vtxz=0.);
  
  // Need to keep trk pT information since the electron may merged with photons 
  // thus track pT and Et will be different
  PMCSEMObj(double ppid, double pE, double peta, double pphi, double trkpT, int index=-1, double vtxz=0.);

  ~PMCSEMObj();

  void Print() const;

  void SetEnergyEtaPhi(double pE, double peta, double pphi, bool ApplyTrkPhiModEfficiency=false, bool useTrkPt=false);
  void SetDetEtaDetPhi(PMCSVtx& vtx);
  void SetDetEtaDetPhiGlobal(PMCSVtx& vtx);
  void SetDetEtaDetPhi(double deteta, double detphi);
  void SetDetEtaDetPhiGlobal(double deteta_global, double detphi_global);
  void SetTrkpT(double trkpT);
  void SetFSRxInCone(double FSRxInCone);
  void SetFSRnInCone(int FSRnInCone);
  void SetEMCorrFactor(double EMCorrFactor);
  void SetRawpTUnderElecWindow(double rawpTUnderElecWindow); 
  void SetUParaCorr(double UParaCorr);
  void SetDeltaZSUP(double Delta_ZSUP);
  void SetEnergyLeakage(double EnergyLeakage);
  void SetUPara(double UPara);
  void SetUPerp(double UPerp);
  void SetLumi(double lumi);
  void SetScalarEt(double ScalarEt);
  void SetEnergyDiffElecWithWithoutZBOverlay(double energy_diff);
  void SetLostInAcrack(bool lost=true);
  void SetVtxZ(double vtxz);
  void SetBremFrac(double BremFraction);

  double deteta() const;
  double detphi() const;
  double deteta_global() const;
  double detphi_global() const;
  double trkpT() const;
  double FSRxInCone() const;
  int FSRnInCone() const;

  // raw true Energy with FSR merged, but without FSR efficiency and response model applied
  void SetEnergyGenWFSR(double energy_gen_wfsr);
  double GetEnergyGenWFSR() const;

  // raw pT under electron window, this comes from underlying event, noise and pileup contributions
  double RawpTUnderElecWindow() const; 
  // uparallel correction, no ZSUP effects included
  double UParaCorr() const;
  // ZSUP effects: on calorimeter cell energy measurement and on real electron energy measurement
  double Delta_ZSUP() const;
  // energy leakage out of the electron cone  
  double EnergyLeakage() const;
  // luminosity of this event, used for energies below electron window correction
  double getLumi() const;
  // ScalarEt of this event, used for energies below electron window correction
  double getScalarEt() const;
  // uparallel for this electron, used for energies below electron window correction
  double getUPara() const;
  // UPerp for this electron
  double getUPerp() const;
  // get energy difference between single energy electron sample with and without ZB overlay
  // this is only meaningful when EnergySim_ElecWindowOption = 1
  double getEnergyDiffElecWithWithoutZBOverlay() const;

  // return most interesting variables in one function
  void getProperties(double& pT, double& eta, double& phi, double& deteta, double& detphi) const;

  bool IsCC(double EtaCC, bool phimodcut=true, bool ApplyTrkPhiModEfficiency=true) const;
  bool IsEC(double EtaEC1, double EtaEC2) const;

  bool IsLostInAcrack() const;

  // Get Unique identifier
  int getIndex() const;
  double getTrueE() const;
  double getTruePt() const;
  double getTrueEta() const;
  double trkphiem3() const;
  double getvtxz() const;
  double getbremfrac() const;
  int EtaRegion_CC(double eta, double DetEtaCC, bool phimodcut=true, bool ApplyTrkPhiModEfficiency=true) const; // 0 for 0<|eta|<0.2, 1 for 0.2<|eta|<0.4, 2 for 0.4<|eta|<0.6, 3 for 0.6<|eta|<0.8 and 4 for |eta|>0.8
  int FineEtaRegion_CC(double eta, double DetEtaCC, bool phimodcut=true, bool ApplyTrkPhiModEfficiency=true) const; // 0, 14 for |eta|>1.3, 1-14 for |eta|<1.3
  int DetEtaRegion_CC(double deteta, double DetEtaCC, bool phimodcut=true, bool ApplyTrkPhiModEfficiency=true) const;

  double PhiMod(bool ApplyTrkPhiModEfficiency=true) const;
  int PhiModRegion(bool ApplyTrkPhiModEfficiency=true) const; 

  // Geometry   
  bool passesFiducial(const TVector3 calpos);
  bool passesGeometric(const TVector3 calpos, const double low, const double high);
  bool passesGeometric(double low, double high);

  int GetPID() const;
  
 private:
  void SetTrueE(double trueE);
  void SetTruePt(double truePt);
  void SetTrueEta(double trueEta);

 private:
  
  double _deteta; //detector eta in calorimeter local coordinate system
  double _detphi; //detector phi in calorimeter local coordinate system
  double _deteta_global; //detector eta in global coordinate system
  double _detphi_global; //detector phi in global coordinate system
  double _trkpT;
  double _FSRxInCone;  // generator-level energy fraction taken away by in-cone FSR
  int _FSRnInCone;  // number of in-cone FSR
  double _RawpTUnderElecWindow;  // energies below electron window, including uparallel correction, zsup effects and energy leakage
  double _UParaCorr;  // uparallel correction, no ZSUP effects included
  double _Delta_ZSUP; // ZSUP effects: on calorimeter cell energy measurement and on real electron energy measurement
  double _EnergyLeakage; // energy leakage out of the electron cone
  double _Lumi;  // luminosity for this event, used for energies below electron window corrections
  double _UPara; // UPara for this electron, used for energies below electron window corrections
  double _UPerp; // UPerp for this electron
  double _ScalarEt; // scalarEt for this event, used for energies below electron window corrections
  double _energyDiffElecWithWithoutZBOverlay; // energy difference between single energy electron sample with and without ZB overlay
  bool _IamLostInAcrack;
  int _Index;     // unique identifier for emobjs 
  double _trueE;  // for smeared EM objects, explicitely keep copy of true energy
  double _truePt;  // for smeared EM objects, explicitely keep copy of true energy
  double _trueEta;  // for smeared EM objects, explicitely keep copy of true energy
  double _trkphiem3; // trkphi extrapolated to EM3
  double _vtxz; // Vtx Z position
  double _bremfraction; // Fraction of energy lost by track by brem.

  double _energy_gen_wfsr; // energy gen with FSR merged but without FSR efficiency and response model applied

};

inline void PMCSEMObj::SetTrkpT(double trkpT) {_trkpT = trkpT;}
inline void PMCSEMObj::SetFSRxInCone(double FSRxInCone) {_FSRxInCone = FSRxInCone;}
inline void PMCSEMObj::SetFSRnInCone(int FSRnInCone) {_FSRnInCone = FSRnInCone;}
inline double PMCSEMObj::deteta() const {return _deteta;}
inline double PMCSEMObj::detphi() const {return _detphi;}
inline double PMCSEMObj::deteta_global() const {return _deteta_global;}
inline double PMCSEMObj::detphi_global() const {return _detphi_global;}
inline double PMCSEMObj::trkpT() const {return _trkpT;}
inline double PMCSEMObj::FSRxInCone() const {return _FSRxInCone;}
inline int PMCSEMObj::FSRnInCone() const {return _FSRnInCone;}
inline double PMCSEMObj::UParaCorr() const {return _UParaCorr;}
inline double PMCSEMObj::EnergyLeakage() const {return _EnergyLeakage;}
inline double PMCSEMObj::getUPara() const {return _UPara;}
inline double PMCSEMObj::getUPerp() const {return _UPerp;}
inline double PMCSEMObj::getLumi() const {return _Lumi;}
inline double PMCSEMObj::getScalarEt() const {return _ScalarEt;}
inline double PMCSEMObj::getEnergyDiffElecWithWithoutZBOverlay() const {return _energyDiffElecWithWithoutZBOverlay;}
inline int PMCSEMObj::getIndex() const {return _Index;}
inline double PMCSEMObj::getTrueE() const {return _trueE;}
inline double PMCSEMObj::getTruePt() const {return _truePt;}
inline double PMCSEMObj::getTrueEta() const {return _trueEta;}
inline double PMCSEMObj::trkphiem3() const {return _trkphiem3;}
inline double PMCSEMObj::getvtxz() const {return _vtxz;}
inline double PMCSEMObj::getbremfrac() const {return _bremfraction;}

inline void PMCSEMObj::SetEnergyGenWFSR(double energy_gen_wfsr) { _energy_gen_wfsr = energy_gen_wfsr; }
inline double PMCSEMObj::GetEnergyGenWFSR() const {return _energy_gen_wfsr;}

inline double PMCSEMObj::RawpTUnderElecWindow() const {return _RawpTUnderElecWindow;} 
inline void PMCSEMObj::SetRawpTUnderElecWindow(double RawpTUnderElecWindow) {_RawpTUnderElecWindow = RawpTUnderElecWindow;} 
inline void PMCSEMObj::SetUParaCorr(double UParaCorr) {_UParaCorr = UParaCorr;}
inline void PMCSEMObj::SetDeltaZSUP(double Delta_ZSUP) {_Delta_ZSUP = Delta_ZSUP;}
inline void PMCSEMObj::SetEnergyLeakage(double EnergyLeakage) {_EnergyLeakage = EnergyLeakage;}
inline void PMCSEMObj::SetUPara(double UPara) {_UPara = UPara;}
inline void PMCSEMObj::SetUPerp(double UPerp) {_UPerp = UPerp;}
inline void PMCSEMObj::SetLumi(double Lumi) {_Lumi = Lumi;}
inline void PMCSEMObj::SetScalarEt(double ScalarEt) {_ScalarEt = ScalarEt;}
inline void PMCSEMObj::SetEnergyDiffElecWithWithoutZBOverlay(double energyDiffElecWithWithoutZBOverlay) {_energyDiffElecWithWithoutZBOverlay = energyDiffElecWithWithoutZBOverlay;}
inline void PMCSEMObj::SetLostInAcrack(bool lost) {_IamLostInAcrack = lost;}

inline void PMCSEMObj::SetVtxZ(double vtxz) {_vtxz = vtxz;}

inline void PMCSEMObj::SetBremFrac(double BremFraction){_bremfraction = BremFraction ;}
inline void PMCSEMObj::getProperties(double& pT, double& eta, double& phi, double& deteta, double& detphi) const {
  pT = _ppt;
  eta = _peta;
  phi = _pphi;
  deteta = _deteta;
  detphi = _detphi;
}

inline int PMCSEMObj::EtaRegion_CC(double eta, double DetEtaCC, bool phimodcut, bool ApplyTrkPhiModEfficiency) const {
  int region = -1;
  if(this->IsCC(DetEtaCC, phimodcut,ApplyTrkPhiModEfficiency)) {
    double abseta = fabs(eta);
    if(abseta<0.2) region = 0;
    else if(abseta<0.4) region = 1;
    else if(abseta<0.6) region = 2;
    else if(abseta<0.8) region = 3;
    else region = 4;
  } 
   return region;
}

inline int PMCSEMObj::FineEtaRegion_CC(double eta, double DetEtaCC, bool phimodcut, bool ApplyTrkPhiModEfficiency) const {
  int region = -1;
  if(this->IsCC(DetEtaCC, phimodcut,ApplyTrkPhiModEfficiency)) {
     if(eta<-1.3) region = 0;
     else if (eta<-1.1) region = 1;
     else if (eta<-0.9) region = 2;
     else if (eta<-0.7) region = 3;
     else if (eta<-0.5) region = 4;
     else if (eta<-0.3) region = 5;
     else if (eta<-0.1) region = 6;
     else if (eta<0.1) region = 7;
     else if (eta<0.3) region = 8;
     else if (eta<0.5) region = 9;
     else if (eta<0.7) region = 10;
     else if (eta<0.9) region = 11;
     else if (eta<1.1) region = 12;
     else if (eta<1.3) region = 13;
     else region = 14;
  } 
   return region;
}

inline int PMCSEMObj::DetEtaRegion_CC(double deteta, double DetEtaCC, bool phimodcut, bool ApplyTrkPhiModEfficiency) const {
  int region = -1;
  if(this->IsCC(DetEtaCC, phimodcut,ApplyTrkPhiModEfficiency)) {
    double absdeteta = fabs(deteta);
    if(absdeteta<0.2) region = 0;
    else if(absdeteta<0.4) region = 1;
    else if(absdeteta<0.6) region = 2;
    else if(absdeteta<0.8) region = 3;
    else region = 4;
  }
  return region;
}

inline double PMCSEMObj::PhiMod(bool ApplyTrkPhiModEfficiency) const {
  if (ApplyTrkPhiModEfficiency)
    return fmod(_trkphiem3*16./TMath::Pi(), 1.0);
  return fmod(_detphi*16./TMath::Pi(), 1.0);
}

inline int PMCSEMObj::PhiModRegion(bool ApplyTrkPhiModEfficiency) const {
  int region = -1;
  if ((PhiMod(ApplyTrkPhiModEfficiency)>=0.0 && PhiMod(ApplyTrkPhiModEfficiency)<=0.1) || (PhiMod()>0.9 && PhiMod()<=1.0)) region = 0;
  else if ((PhiMod(ApplyTrkPhiModEfficiency)>0.1 && PhiMod(ApplyTrkPhiModEfficiency)<=0.2) || (PhiMod(ApplyTrkPhiModEfficiency)>0.8 && PhiMod(ApplyTrkPhiModEfficiency)<=0.9)) region = 1;
  else if ((PhiMod(ApplyTrkPhiModEfficiency)>0.2 && PhiMod(ApplyTrkPhiModEfficiency)<=0.3) || (PhiMod(ApplyTrkPhiModEfficiency)>0.7 && PhiMod(ApplyTrkPhiModEfficiency)<=0.8)) region = 2;
  else if ((PhiMod(ApplyTrkPhiModEfficiency)>0.3 && PhiMod(ApplyTrkPhiModEfficiency)<=0.4) || (PhiMod(ApplyTrkPhiModEfficiency)>0.6 && PhiMod(ApplyTrkPhiModEfficiency)<=0.7)) region = 3;
  else if ((PhiMod(ApplyTrkPhiModEfficiency)>0.4 && PhiMod(ApplyTrkPhiModEfficiency)<=0.5) || (PhiMod(ApplyTrkPhiModEfficiency)>0.5 && PhiMod(ApplyTrkPhiModEfficiency)<=0.6)) region = 4;
  
  return region;
}

inline bool PMCSEMObj::IsCC(double EtaCC, bool phimodcut, bool ApplyTrkPhiModEfficiency) const { 
  bool isCC=false;
  // use exactly the same code for phi fiducial as /d0dist/dist/packages/em_util/devel/src/Fiducial_Cuts.cpp
  double PHI_CRACK_WIDTH=0.02;
  if(phimodcut) {
    double phimod = fmod(_detphi+0.1, TMath::Pi()/16.);
    if (ApplyTrkPhiModEfficiency)
      phimod = fmod(_trkphiem3+0.1, TMath::Pi()/16.);
    if ( (fabs(_deteta)<EtaCC) && ( (phimod<0.1-PHI_CRACK_WIDTH) || (phimod>0.1+PHI_CRACK_WIDTH) ) )  isCC = true;    
  } else {
    if (fabs(_deteta)<EtaCC) isCC = true;
  }
  return isCC;
}
inline bool PMCSEMObj::IsEC(double EtaEC1, double EtaEC2) const {return ( (fabs(_deteta)>EtaEC1) && (fabs(_deteta)<EtaEC2) );}

inline bool PMCSEMObj::IsLostInAcrack() const {return _IamLostInAcrack;}

inline void PMCSEMObj::Print() const {std::cout<<"(pid="<<_ppid<<",pE="<<_pE<<",pT="<<_ppt
					 <<",eta="<<_peta<<",phi="<<_pphi
                                         <<",deteta="<<_deteta<<",detphi="<<_detphi<<")"<<std::endl;
              			std::cout<<"(px="<<_ppx<<",py="<<_ppy<<",_pz="<<_ppz<<")"<<std::endl;}

inline void PMCSEMObj::SetTrueE(double trueE) {_trueE = trueE;}
inline void PMCSEMObj::SetTruePt(double truePt) {_truePt = truePt;}
inline void PMCSEMObj::SetTrueEta(double trueEta) {_trueEta = trueEta;}
inline int PMCSEMObj::GetPID() const { return (int) _ppid; }
#endif
