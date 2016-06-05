#include "PMCSWCand.hpp"
#include "AnglesUtil.hpp"

#include <iostream>
using namespace std;

PMCSWCand::PMCSWCand(PMCSEMObj &elec, PMCSRecoil &recoil, PMCSMet &met) {
  _ppx = elec.ppx() + met.metx();
  _ppy = elec.ppy() + met.mety();
  _ppt = sqrt(_ppx*_ppx + _ppy*_ppy);
  
  _elec = elec;
  _recoil = recoil;
  _met = met;
}

PMCSWCand::~PMCSWCand() {
}

//return W type: 0 for CC, 1 for EC
int PMCSWCand::Type(double CutEtaCC, double CutEtaEC1, double CutEtaEC2, bool trkphimodcut) const {
  int type=-1;
  if(this->GetElec().IsCC(CutEtaCC, true, trkphimodcut))   type = 0;
  if(this->GetElec().IsEC(CutEtaEC1, CutEtaEC2))   type = 1;
  return type;
}

TVector2 PMCSWCand::GetRecoilVec() const {
  return (TVector2(_recoil.Recoilx(), _recoil.Recoily()));
}

double PMCSWCand::MagRecoil() const {
  return sqrt(_recoil.Recoilx()*_recoil.Recoilx()+_recoil.Recoily()*_recoil.Recoily());
}

//calculate the transverse mass
double PMCSWCand::TMass() const {
  double tmass = sqrt(2.*_elec.ppt()*_met.met()*( 1.-cos(this->DeltaPhi_EM_MET()) ) );
  return tmass;
}

//calculate delta_phi between electron and MET
double PMCSWCand::DeltaPhi_EM_MET() const {
  double phi_em = _elec.phi();
  double phi_met = _met.metphi();
  return (kinem::delta_phi(phi_em, phi_met));
}

//calculate delta_phi between electron and recoil jet
double PMCSWCand::DeltaPhi_EM_Recoil() const {
  double phi_em = _elec.phi();
  double phi_recoil = GetRecoilVec().Phi();
  return (kinem::delta_phi(phi_em, phi_recoil));
}

//calculate upara
double PMCSWCand::UPara() const {
  TVector2 elec_vec(_elec.ppx(), _elec.ppy());
  return (this->GetRecoilVec() * elec_vec.Unit());
}

//calculate uperp
double PMCSWCand::UPerp() const {
  TVector2 elec_vec(_elec.ppx(), _elec.ppy());
  TVector2 perp_direction = elec_vec.Rotate(TMath::Pi()/2);
  return (this->GetRecoilVec() * perp_direction.Unit());
}

//calculate ut
double PMCSWCand::UT() const {
  return (sqrt(this->UPara()*this->UPara() + this->UPerp()*this->UPerp()));
}

PMCSEMObj PMCSWCand::GetElec() const {return _elec;}
PMCSRecoil PMCSWCand::GetRecoil() const {return _recoil;}
PMCSMet PMCSWCand::GetMet() const {return _met;}
