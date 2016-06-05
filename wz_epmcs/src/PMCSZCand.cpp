#include "PMCSZCand.hpp"
#include "AnglesUtil.hpp"

#include <iostream>
using namespace std;

PMCSZCand::PMCSZCand(PMCSEMObj &elec1, PMCSEMObj &elec2, PMCSRecoil &recoil, PMCSMet &met) {
  _ppx = elec1.ppx() + elec2.ppx();
  _ppy = elec1.ppy() + elec2.ppy();
  _ppz = elec1.ppz() + elec2.ppz();
  _ppt = sqrt(_ppx*_ppx + _ppy*_ppy);
  _pE = elec1.pE() + elec2.pE();
  _eta = kinem::eta(_ppx, _ppy, _ppz);
  _phi = kinem::phi(_ppx, _ppy);

  _elec1 = elec1;
  _elec2 = elec2;
  _recoil = recoil;
  _met = met;

  SetA(elec1,elec2);
}

PMCSZCand::PMCSZCand(PMCSEMObj &elec1, PMCSEMObj &elec2) {
  _ppx = elec1.ppx() + elec2.ppx();
  _ppy = elec1.ppy() + elec2.ppy();
  _ppz = elec1.ppz() + elec2.ppz();
  _ppt = sqrt(_ppx*_ppx + _ppy*_ppy);
  _pE = elec1.pE() + elec2.pE();
  _eta = kinem::eta(_ppx, _ppy, _ppz);
  _phi = kinem::phi(_ppx, _ppy);

  _elec1 = elec1;
  _elec2 = elec2;

  SetA(elec1,elec2);
}

PMCSZCand::~PMCSZCand() {
}

void PMCSZCand::SetA(PMCSEMObj &elec1, PMCSEMObj &elec2) {

  // First we need to calculate the thrust axis
  //
  TVector2 e1(elec1.ppx(),elec1.ppy());
  TVector2 e2(elec2.ppx(),elec2.ppy());

  // Calculate the two phi angles
  double phi1=e1.Phi();
  double phi2=e2.Phi();

  // Order in phi
  if (phi1<phi2) {
    TVector2 dummy=e1;
    e1=e2;
    e2=dummy;
    double dummy2=phi1;
    phi1=phi2;
    phi2=dummy2;
  }

  // Calculate lengths as well
  double len1=e1.Mod();
  double len2=e2.Mod();

  // Good old Newton
  //
  // initial guess
  TVector2 bisector=(e1.Unit()+e2.Unit()).Unit();
  double alpha=bisector.Phi()-TMath::Pi()/2.;
  double alphaBackup=alpha;
  int nIt=0;
  // iterate
  double oldAlpha=9999.;
  while (fabs(alpha-oldAlpha)>0.000001) {
    oldAlpha=alpha;
    double f=len2*sin(phi2-oldAlpha)+len1*sin(oldAlpha-phi1);
    double fp=-len2*cos(phi2-oldAlpha)+len1*cos(oldAlpha-phi1);
    alpha=oldAlpha-f/fp;
    nIt++;
    if (nIt>1000) {
      cout<<"Newton did not converge in search for thrust axis"<<endl;
      alpha=alphaBackup;
      break;
    }
  }

  // Build unit vector
  TVector2 r;
  r.SetMagPhi(1.,alpha);
  TVector2 rPerp=r.Rotate(TMath::Pi()/2.);

  // Checks
  if (fabs(e1*rPerp-e2*rPerp)>0.001) {
    cout<<"Looks like Newton was imprecise in calculation of thrust axis: "<<e1*rPerp<<" "<<e2*rPerp<<endl;
  }

  // now we can do the projections
  TVector2 Z=e1+e2;
  _pat=Z*rPerp;
  _pal=Z*r;
}

// update Recoil and MET information 
void PMCSZCand::SetMetRecoil(PMCSRecoil &recoil, PMCSMet &met) {
  _recoil = recoil;
  _met = met;
}

// return invariant mass
double PMCSZCand::mass() const {
  double mass = _pE*_pE-_ppx*_ppx-_ppy*_ppy-_ppz*_ppz;
  if(mass>0.) mass = sqrt(mass);
  else mass = 0.;
  return mass;
}

//return Z type: 0 for CCCC, 1 for CCEC, 2 for ECEC
//-1 for all other cases
int PMCSZCand::Type(double CutEtaCC, double CutEtaEC1, double CutEtaEC2, bool phimodcut, bool trkphimodcut) const {
  int type=-1;
  if(this->GetElec1().IsCC(CutEtaCC, phimodcut, trkphimodcut) && this->GetElec2().IsCC(CutEtaCC, phimodcut, trkphimodcut))
    type = 0;
  if((this->GetElec1().IsCC(CutEtaCC, phimodcut, trkphimodcut) && this->GetElec2().IsEC(CutEtaEC1, CutEtaEC2)) || 
     (this->GetElec1().IsEC(CutEtaEC1, CutEtaEC2) && this->GetElec2().IsCC(CutEtaCC, phimodcut, trkphimodcut)) )                  
    type = 1;
  if(this->GetElec1().IsEC(CutEtaEC1, CutEtaEC2) && this->GetElec2().IsEC(CutEtaEC1, CutEtaEC2))         
    type = 2;

  return type;
}

//return the open angle between two electrons
double PMCSZCand::Angle_EM_EM() const {
  double angle = 99.;

  TLorentzVector vec_em1 = _elec1.GetLorentzVect();
  TVector3 vec_em2 = _elec2.GetVect3();
  angle = vec_em1.Angle(vec_em2);
  return angle;
}

//return delta phi between EM and recoil
double PMCSZCand::DeltaPhi_EM_Recoil(int emidx) const {
  TVector2 em_vect;
  if(emidx==0) em_vect.Set(_elec1.ppx(), _elec1.ppy());
  else em_vect.Set(_elec2.ppx(), _elec2.ppy());

  TVector2 recoil_vect(_recoil.Recoilx(), _recoil.Recoily());
  return fabs(em_vect.DeltaPhi(recoil_vect));
}

//return delta phi between EM and met 
double PMCSZCand::DeltaPhi_EM_Met(int emidx) const {
  TVector2 em_vect;
  if(emidx==0) em_vect.Set(_elec1.ppx(), _elec1.ppy());
  else em_vect.Set(_elec2.ppx(), _elec2.ppy());

  TVector2 met_vect(_met.metx(), _met.mety());
  return fabs(em_vect.DeltaPhi(met_vect));
}

//return delta phi between Z and recoil 
double PMCSZCand::DeltaPhi_Z_Recoil(bool fold) const {
  TVector2 z_vect(_elec1.ppx()+_elec2.ppx(), _elec1.ppy()+_elec2.ppy());
  TVector2 recoil_vect(_recoil.Recoilx(), _recoil.Recoily());
  if (fold) {
    return fabs(z_vect.DeltaPhi(recoil_vect)); //RCLSA: Changed here!
  } else {
    return z_vect.DeltaPhi(recoil_vect);
  }
}

//return delta phi between Z and met
double PMCSZCand::DeltaPhi_Z_Met() const {
  TVector2 z_vect(_elec1.ppx()+_elec2.ppx(), _elec1.ppy()+_elec2.ppy());
  TVector2 met_vect(_met.metx(), _met.mety());
  return fabs(z_vect.DeltaPhi(met_vect));
}

//return delta phi between recoil and met
double PMCSZCand::DeltaPhi_Recoil_Met() const {
  TVector2 met_vect(_met.metx(), _met.mety());
  TVector2 recoil_vect(_recoil.Recoilx(), _recoil.Recoily());
  return fabs(recoil_vect.DeltaPhi(met_vect));
}

//return the bisector direction of two electrons
TVector2 PMCSZCand::Eta_Direction() const {
  TVector2 elec1_vec(this->GetElec1().ppx(), this->GetElec1().ppy());
  TVector2 elec2_vec(this->GetElec2().ppx(), this->GetElec2().ppy());
  
  TVector2 bisector_vec = (elec1_vec.Unit() + elec2_vec.Unit()).Unit();
  return bisector_vec;
}

//return xi direction
TVector2 PMCSZCand::Xi_Direction() const {
  return(this->Eta_Direction().Rotate(TMath::Pi()/2.));
}

//return TVector2 of the recoil jet
TVector2 PMCSZCand::GetRecoilVec() const {
  return (TVector2(_recoil.Recoilx(), _recoil.Recoily()));
}

double PMCSZCand::UPara1() const {
  TVector2 elec_vec(_elec1.ppx(), _elec1.ppy());
  return (this->GetRecoilVec() * elec_vec.Unit());
}

double PMCSZCand::UPerp1() const {
  TVector2 elec_vec(_elec1.ppx(), _elec1.ppy());
  return (this->GetRecoilVec() * elec_vec.Unit().Rotate(TMath::Pi()/2.));
}

double PMCSZCand::UPara2() const {
  TVector2 elec_vec(_elec2.ppx(), _elec2.ppy());
  return (this->GetRecoilVec() * elec_vec.Unit());
}

double PMCSZCand::UPerp2() const {
  TVector2 elec_vec(_elec2.ppx(), _elec2.ppy());
  return (this->GetRecoilVec() * elec_vec.Unit().Rotate(TMath::Pi()/2.));
}

double PMCSZCand::MagRecoil() const {
  return sqrt(_recoil.Recoilx()*_recoil.Recoilx()+_recoil.Recoily()*_recoil.Recoily());
}

double PMCSZCand::p_ee() const {
  TVector2 z_vec(this->ppx(), this->ppy());
  TVector2 eta_direction = this->Eta_Direction();

  return z_vec * eta_direction;
}

double PMCSZCand::p_ee2() const {
  TVector2 z_vec(this->ppx(), this->ppy());
  TVector2 xi_direction = this->Xi_Direction();

  return z_vec * xi_direction;
}

double PMCSZCand::recoil() const {
  return GetRecoilVec() * this->Eta_Direction();
}

double PMCSZCand::recoil2() const {
  return GetRecoilVec() * this->Xi_Direction();
}

double PMCSZCand::response() const {

  double ut_proj_pt = 
  -(this->ppx()+GetMet().metx())*(this->ppx())-(this->ppy()+GetMet().mety())*(this->ppy());
  double response = fabs(ut_proj_pt/(ppt()*ppt()));
  return response;
}

//return eta balance
double PMCSZCand::Eta_Balance(double hadronic_response) const {
  TVector2 recoil_vec = GetRecoilVec();
  TVector2 z_vec(this->ppx(), this->ppy());
  TVector2 eta_direction = this->Eta_Direction();

  double p_ee = z_vec * eta_direction;
  double recoil = recoil_vec * eta_direction;
  return (p_ee + recoil/hadronic_response);
}

//return eta imbalance
double PMCSZCand::Eta_ImBalance() const {
  TVector2 recoil_vec = GetRecoilVec();
  TVector2 z_vec(this->ppx(), this->ppy());
  TVector2 eta_direction = this->Eta_Direction();

  double p_ee = z_vec * eta_direction;
  double recoil = recoil_vec * eta_direction;
  return (p_ee + recoil);
}

//return xi balance
double PMCSZCand::Xi_Balance(double hadronic_response) const {
  TVector2 recoil_vec = GetRecoilVec();
  TVector2 z_vec(this->ppx(), this->ppy());
  TVector2 xi_direction = this->Xi_Direction();

  double p_ee = z_vec * xi_direction;
  double recoil = recoil_vec * xi_direction;
  return (p_ee + recoil/hadronic_response);
}

//return xi imbalance
double PMCSZCand::Xi_ImBalance() const {
  TVector2 recoil_vec = GetRecoilVec();
  TVector2 z_vec(this->ppx(), this->ppy());
  TVector2 xi_direction = this->Xi_Direction();

  double p_ee = z_vec * xi_direction;
  double recoil = recoil_vec * xi_direction;
  return (p_ee + recoil);
}

//return the eta between two electrons
double PMCSZCand::DeltaEta_EM_EM() const {
  return (_elec1.eta() - _elec2.eta());
}

//return the phi between two electrons
double PMCSZCand::DeltaPhi_EM_EM() const {
  return ( kinem::delta_phi(_elec1.phi(), _elec2.phi()) );
}

//return the R distance between two electrons
double PMCSZCand::DeltaR_EM_EM() const {
  return (sqrt(this->DeltaEta_EM_EM()*this->DeltaEta_EM_EM() +
               this->DeltaPhi_EM_EM()*this->DeltaPhi_EM_EM() ));
}

//return f value for CC-CC events
double PMCSZCand::f_CCCC() const {
  double angle_em = this->Angle_EM_EM();
  double f = 2*(_elec1.pE()+_elec2.pE()) * sin(angle_em/2.) * sin(angle_em/2.)/this->mass();
  return f;
}

//return f value for EC-EC events
double PMCSZCand::f_ECEC() const {
  double angle_em = this->Angle_EM_EM();
  double f = 2*(_elec1.pE()+_elec2.pE()) * sin(angle_em/2.) * sin(angle_em/2.)/this->mass();
  return f;
}

//return trkcal mass
double PMCSZCand::trkcalmass(int cal) const {
  double trkpt1 = _elec1.trkpT();
  double trktheta1 = _elec1.theta();
  double trketa1 = _elec1.peta();
  double trkphi1 = _elec1.pphi();

  double pEtrk1 = trkpt1  / sin(trktheta1) ;
  double pxtrk1 = trkpt1 * cos(trkphi1);
  double pytrk1 = trkpt1 * sin(trkphi1);
  double pztrk1 =  pEtrk1 * cos(trktheta1);
  
  double trkpt2 = _elec2.trkpT();
  double trktheta2 = _elec2.theta();
  double trketa2 = _elec2.peta();
  double trkphi2 = _elec2.pphi();

  double pEtrk2 = trkpt2  / sin(trktheta2) ;
  double pxtrk2 = trkpt2 * cos(trkphi2);
  double pytrk2 = trkpt2 * sin(trkphi2);
  double pztrk2 =  pEtrk2 * cos(trktheta2);
  

  double zcandmass2  = pow(_elec2.pE() + pEtrk1,2) - pow(_elec2.ppx() + pxtrk1,2) - pow(_elec2.ppy() + pytrk1,2) - pow(_elec2.ppz() + pztrk1,2);
  double zcandmass1  = pow(_elec1.pE() + pEtrk2,2) - pow(_elec1.ppx() + pxtrk2,2) - pow(_elec1.ppy() + pytrk2,2) - pow(_elec1.ppz() + pztrk2,2);
  
  if (zcandmass1 < 0.)
    zcandmass1 = 0;
  if (zcandmass2 < 0.)
    zcandmass2 = 0;
  
  zcandmass1 = sqrt(zcandmass1);
  
  zcandmass2 = sqrt(zcandmass2);
  if (cal==1)
    return zcandmass1;
  if (cal==2)
    return zcandmass2;
}


//return f value for CC-EC events
double PMCSZCand::f_CCEC() const {
  double f=0.;
  double angle_em = this->Angle_EM_EM();
  if( fabs(this->GetElec1().deteta())<1.3 )  f = _elec1.pE() * (1-cos(angle_em))/this->mass();
  else f = _elec2.pE() * (1-cos(angle_em))/this->mass();
  return f;
}

//return the pointer to the first electron
PMCSEMObj PMCSZCand::GetElec1() const {return _elec1;}

//return the pointer to the second electron
PMCSEMObj PMCSZCand::GetElec2() const {return _elec2;}

//return recoil
PMCSRecoil PMCSZCand::GetRecoil() const {return _recoil;}

//return met
PMCSMet PMCSZCand::GetMet() const {return _met;}
//calculate the transverse mass

double PMCSZCand::GetMt2() const {
  PMCSMet fakemet(-_recoil.Recoilx()-_elec2.ppx(), -_recoil.Recoily()-_elec2.ppy());
  double tmass = sqrt(2.*_elec2.ppt()*fakemet.met()*( 1.-cos(kinem::delta_phi(_elec2.phi(),fakemet.metphi()))));
  return tmass;
}

//calculate the transverse mass
double PMCSZCand::GetMt1() const {
  PMCSMet fakemet(-_recoil.Recoilx()+_elec1.ppx(), -_recoil.Recoily()-_elec1.ppy());
  double tmass = sqrt(2.*_elec1.ppt()*fakemet.met()*( 1.-cos(kinem::delta_phi(_elec1.phi(),fakemet.metphi()))));
  return tmass;
}
