#include "PMCSEMObj.hpp"
#include "AnglesUtil.hpp"
#include "PCalTools.hpp"
#include <iostream>

using namespace std;

//PMCSEMObj::PMCSEMObj(const PMCSParticle p):PMCSParticle(p) {;}

// simple constructor
PMCSEMObj::PMCSEMObj(double ppid, double pE, double peta, double pphi, int index, double vtxz) {
  _ppid = ppid;
  SetEnergyEtaPhi(pE, peta, pphi, false);

  // the default track pT is set to be exactly the same as raw pT
  // this may not be true when electron and photon are merged
  _trkpT = pE * sin(kinem::theta(peta));

  // set detector eta, phi and physics eta, phi to be the same now
  // assume that EM objects coming from the origin
  _deteta = peta;
  _detphi = pphi;
  _deteta_global = peta;
  _detphi_global = pphi;

  _FSRxInCone = 0;
  _FSRnInCone = 0;
  // energies under electron window
  _RawpTUnderElecWindow = 0.;
  // uparallel correction without ZSUP effects included
  _UParaCorr = 0.;
  // ZSUP effects on calrimeter cell energy and real electron energy
  _Delta_ZSUP = 0.;
  // energy leakage out of the electron cone
  _EnergyLeakage = 0.;

  _IamLostInAcrack = false;

  _Index = index;
  _trueE = -10.;
  _truePt = -10.;
  _trueEta = -10.;
  _vtxz = vtxz;

}

// simple constructor (add track pT)
PMCSEMObj::PMCSEMObj(double ppid, double pE, double peta, double pphi, double trkpT, int index,double vtxz) {
  _ppid = ppid;

  // track pT, used for E/p study
  _trkpT = trkpT;

  // set detector eta, phi and physics eta, phi to be the same now
  // assume that EM objects coming from the origin
  _deteta = peta;
  _detphi = pphi;
  _deteta_global = peta;
  _detphi_global = pphi;

  _FSRxInCone = 0;
  _FSRnInCone = 0;
  // energies under electron window
  _RawpTUnderElecWindow = 0.;
  // uparallel correction without ZSUP effects included
  _UParaCorr = 0.;
  // ZSUP effects on calrimeter cell energy and real electron energy
  _Delta_ZSUP = 0.;
  // energy leakage out of the electron cone
  _EnergyLeakage = 0.;

  _IamLostInAcrack = false;

  _Index = index;
  _trueE = -10.;
  _truePt = -10.;
  _trueEta = -10.;
  _vtxz = vtxz;
  SetEnergyEtaPhi(pE, peta, pphi, false, true);
}

PMCSEMObj::~PMCSEMObj() {
}

// set Energy, eta, phi
void PMCSEMObj::SetEnergyEtaPhi(double pE, double peta, double pphi, bool ApplyTrkPhiModEfficiency, bool useTrkPt) {
  _pE = pE;
  _peta = peta;
  _pphi = pphi;
  bool ispositron = ((_ppid==-11) || (_ppid==-12));
         
//   bool outside_phi_crack=true;
//   if (ApplyTrkPhiModEfficiency){
//     float phimod=fmod(_trkphiem3+0.1,TMath::Pi()/16.);
//     outside_phi_crack=((phimod<0.1-0.02) || (phimod>0.1+0.02));
//   }
//   if (!outside_phi_crack) _IamLostInAcrack = true;
  
  double theta = 2.*atan(exp(-peta));
  _ppt = pE*sin(theta);
  _ppx = _ppt*cos(pphi);
  _ppy = _ppt*sin(pphi);
  _ppz = pE*cos(theta);

  double pt_for_extrap = _ppt;
  if (useTrkPt) pt_for_extrap = _trkpT;

  if(_ppid!=22) _trkphiem3 =  PCalTools::Phi_Magnetic_Field(_vtxz, _peta, _pphi, 
  					      pt_for_extrap, ispositron); 
}

// set detector eta and phi in global coordinate system
void PMCSEMObj::SetDetEtaDetPhiGlobal(PMCSVtx& vtx) {
  //extrapolate electron from the primary vertex to EM3
  double deteta = PCalTools::eta_em_extrap(vtx.vtxz(), _peta);

  //consider the kick due to the magnetic field

  double detphi = _pphi;
  bool ispositron = ((_ppid==-11) || (_ppid==-12));
  if(_ppid!=22) detphi = PCalTools::Phi_Magnetic_Field((double)(vtx.vtxz()), _peta, _pphi, 
  					      _ppt, ispositron);

  SetDetEtaDetPhiGlobal(deteta, detphi);
}

// set detector eta and phi in calorimeter local coordinate system
void PMCSEMObj::SetDetEtaDetPhi(PMCSVtx& vtx) {  
  //extrapolate electron from the primary vertex to EM3
  double deteta = PCalTools::eta_extrap_Local(vtx.vtxz(), _peta);
  
  //consider the kick due to the magnetic field
  bool ispositron = ((_ppid==-11) || (_ppid==-12));
  double detphi = PCalTools::Phi_Magnetic_Field((double)(vtx.vtxz()), _peta, _pphi, 
  					       _ppt, ispositron);
  SetDetEtaDetPhi(deteta, detphi);
}

// Set electron detector eta, phi in global coordinate system
void PMCSEMObj::SetDetEtaDetPhiGlobal(double deteta_global, double detphi_global) {
  _deteta_global = deteta_global;
  _detphi_global = detphi_global;
}

// Set electron detector eta, phi in calorimeter local coordinate system
void PMCSEMObj::SetDetEtaDetPhi(double deteta, double detphi) {
  _deteta = deteta;
  _detphi = detphi;
}

bool PMCSEMObj::passesFiducial(const TVector3 calpos) {
  return (PCalTools::is_in_eta_fiducial(calpos) && PCalTools::is_in_phi_fiducial(calpos));
return true;
}

bool PMCSEMObj::passesGeometric(const TVector3 calpos, const double low, const double high) {
  return ((fabs(calpos.Eta()) >= low) && (fabs(calpos.Eta()) <= high));
}

// determine deteta region
bool PMCSEMObj::passesGeometric(double low, double high) {
  return (fabs(_deteta) >= low) && (fabs(_deteta) <= high);
}

