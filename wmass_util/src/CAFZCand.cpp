#include <iostream>
#include <vector>
#include "wmass_util/CAFZCand.hpp"

using namespace std;
  
CAFZCand::CAFZCand() {}
CAFZCand::~CAFZCand() {}

// define Z candidate with two EM objects
CAFZCand::CAFZCand(const CAFEMObj *em0, const CAFEMObj *em1) {
  _EM[0] = em0;
  _EM[1] = em1;

  _E = em0->E() + em1->E();
  _Px = em0->Px() + em1->Px();
  _Py = em0->Py() + em1->Py();
  _Pz = em0->Pz() + em1->Pz();
  _Pt = sqrt(_Px*_Px + _Py*_Py);

  // invariant mass
  _Mass = _E*_E-_Pt*_Pt-_Pz*_Pz;
  if(_Mass<0.) _Mass=0.;
  _Mass = sqrt(_Mass);
 
  _recoil.Set(0., 0.);  // set the recoil vector to (0, 0) in default
  _consistentMET.Set(0., 0.);

  // Wyatt's novel variable
  SetA(em0,em1);

}//end constructor

// define Z candidate with one EM object and one track
CAFZCand::CAFZCand(const CAFEMObj *em0, const CAFTrack *trk1) {
  _EM[0] = em0;
  _Trk[1] = trk1;

  _E = em0->E() + trk1->E();
  _Px = em0->Px() + trk1->Px();
  _Py = em0->Py() + trk1->Py();
  _Pz = em0->Pz() + trk1->Pz();
  _Pt = sqrt(_Px*_Px + _Py*_Py);

  // invariant mass
  _Mass = _E*_E-_Pt*_Pt-_Pz*_Pz;
  if(_Mass<0.) _Mass=0.;
  _Mass = sqrt(_Mass);

  _recoil.Set(0., 0.);  // set the recoil vector to (0, 0) in default
  _consistentMET.Set(0., 0.);

  // Wyatt's novel variable
  SetA(em0,trk1);

}//end constructor

// define Z candidate with two EM tracks
CAFZCand::CAFZCand(const CAFTrack *trk0, const CAFTrack *trk1) {
  _Trk[0] = trk0;
  _Trk[1] = trk1;

  _E = trk0->E() + trk1->E();
  _Px = trk0->Px() + trk1->Px();
  _Py = trk0->Py() + trk1->Py();
  _Pz = trk0->Pz() + trk1->Pz();
  _Pt = sqrt(_Px*_Px + _Py*_Py);

  // invariant mass
  _Mass = _E*_E-_Pt*_Pt-_Pz*_Pz;
  if(_Mass<0.) _Mass=0.;
  _Mass = sqrt(_Mass);

  _recoil.Set(0., 0.);  // set the recoil vector to (0, 0) in default
  _consistentMET.Set(0., 0.);

  // Wyatt's novel variable
  SetA(trk0,trk1);

}//end constructor

// define Z candidate with two EM objects and met
CAFZCand::CAFZCand(const CAFEMObj *em0, const CAFEMObj *em1, const CAFMet *met, float* vtx, bool metIsRaw) {
  _EM[0] = em0;
  _EM[1] = em1;

  _E = em0->E() + em1->E();
  _Px = em0->Px() + em1->Px();
  _Py = em0->Py() + em1->Py();
  _Pz = em0->Pz() + em1->Pz();
  _Pt = sqrt(_Px*_Px + _Py*_Py);

  // invariant mass
  _Mass = _E*_E-_Pt*_Pt-_Pz*_Pz;
  if(_Mass<0.) _Mass=0.;
  _Mass = sqrt(_Mass);

  TVector2 met_vec(met->metx(), met->mety());
  TVector2 z_vec(_Px, _Py);
  if(vtx) {
    // I need to convert const CAFEMObj* into CAFEMObj* in order to access the varibles
    TVector2 em0_cells_raw = ((CAFEMObj *)(em0))->getRawElecVectorFromCells(vtx); 
    TVector2 em1_cells_raw = ((CAFEMObj *)(em1))->getRawElecVectorFromCells(vtx);
    z_vec = em0_cells_raw + em1_cells_raw;  

    if (!metIsRaw) {
      // I will convert EM corrected MET back to raw MET
      double Ex_EMObjs_corr = _Px;
      double Ey_EMObjs_corr = _Py;
      double Ex_EMObjs_raw = em0->uncorrE()*sin(em0->Theta())*cos(em0->Phi()) + 
	em1->uncorrE()*sin(em1->Theta())*cos(em1->Phi());
      double Ey_EMObjs_raw = em0->uncorrE()*sin(em0->Theta())*sin(em0->Phi()) + 
	em1->uncorrE()*sin(em1->Theta())*sin(em1->Phi());

      // invert what we have done in make_EMCorr in MetSelector to have raw MET without EM corrections
      met_vec.Set(met->metx() -(Ex_EMObjs_raw-Ex_EMObjs_corr), met->mety() -(Ey_EMObjs_raw-Ey_EMObjs_corr));
    } else {
      met_vec.Set(met->metx(),met->mety());
    }
  } 
      
  _recoil = -1. * (met_vec + z_vec);  // set recoil vector

  TVector2 dummy(_Px,_Py);
  _consistentMET = -1. * (_recoil + dummy);

  // Wyatt's novel variable
  SetA(em0,em1);

}//end constructor

// Interface methods for Wyatt's variable
void CAFZCand::SetA(const CAFEMObj *em0, const CAFEMObj *em1) {
  TVector2 e1(em0->Px(),em0->Py());
  TVector2 e2(em1->Px(),em1->Py());
  SetA(e1,e2);
}

void CAFZCand::SetA(const CAFEMObj *em0, const CAFTrack *trk1) {
  TVector2 e1(em0->Px(),em0->Py());
  TVector2 e2(trk1->Px(),trk1->Py());
  SetA(e1,e2);
}

void CAFZCand::SetA(const CAFTrack *trk0, const CAFTrack *trk1) {
  TVector2 e1(trk0->Px(),trk0->Py());
  TVector2 e2(trk1->Px(),trk1->Py());
  SetA(e1,e2);
}

// The actual calculation of Wyatt's variable
void CAFZCand::SetA(TVector2& e1, TVector2& e2) {

  // First we need to calculate the thrust axis
  //

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
  _At=Z*rPerp;
  _Al=Z*r;

}


// Lorentz vector
TMBLorentzVector CAFZCand::lorentzvector() const {
  TMBLorentzVector lv(_Px, _Py, _Pz, _E);
  return lv;
}

// 0 for CCCC, 1 for CCEC, 2 for ECEC, 3 for other
int CAFZCand::Type(double DetEtaCC, double DetEtaEC1, double DetEtaEC2) const {
  int type = -1;
  if( _EM[0]->IsCC(DetEtaCC) && _EM[1]->IsCC(DetEtaCC) ) type = 0;
  else if ( (_EM[0]->IsCC(DetEtaCC) && _EM[1]->IsEC(DetEtaEC1, DetEtaEC2)) || 
            (_EM[1]->IsCC(DetEtaCC) && _EM[0]->IsEC(DetEtaEC1, DetEtaEC2)) ) type = 1;
  else if ( _EM[0]->IsEC(DetEtaEC1, DetEtaEC2) && _EM[1]->IsEC(DetEtaEC1, DetEtaEC2) ) type = 2;
  else type = 3;

  return type;
}

// # of tracks
int CAFZCand::NumTracks() const {
  int NTrks = 0;
  if(_EM[0]->has_track_match() && _EM[1]->has_track_match()) NTrks = 2;
  else if (_EM[0]->has_track_match() || _EM[1]->has_track_match()) NTrks = 1;
  return NTrks;
}

// # of spatial tracks
int CAFZCand::NumSpatialTracks() const {
  int NTrks = 0;
  if(_EM[0]->has_spatial_track_match() && _EM[1]->has_spatial_track_match()) NTrks = 2;
  else if (_EM[0]->has_spatial_track_match() || _EM[1]->has_spatial_track_match()) NTrks = 1;
  return NTrks;
}

// # of GOOD spatial tracks
int CAFZCand::NumGoodSpatialTracks(bool require_smt) const {
  int NTrks = 0;
  if(_EM[0]->has_good_spatial_track_match(0.01,require_smt) && _EM[1]->has_good_spatial_track_match(0.01,require_smt)) NTrks = 2;
  else if (_EM[0]->has_good_spatial_track_match(0.01,require_smt) || _EM[1]->has_good_spatial_track_match(0.01,require_smt)) NTrks = 1;
  return NTrks;
}

//return TVector2 of the recoil jet
TVector2 CAFZCand::GetRecoil() {
  return _recoil;
}

TVector2 CAFZCand::GetConsistentMET() {
  return _consistentMET;
}

//return the magnitude of the recoil jet
double CAFZCand::MagRecoil() {
  return ( sqrt(_recoil.Px()*_recoil.Px() + _recoil.Py()*_recoil.Py()) );
}

// bisector direction of the two electrons
TVector2 CAFZCand::Eta_Direction() const {
  TVector2 vect_elec1 = _EM[0]->vect2();
  TVector2 vect_elec2 = _EM[1]->vect2();
  
  TVector2 bisector_vec = (vect_elec1.Unit()+vect_elec2.Unit()).Unit();
  return bisector_vec;
}

// xi direction
TVector2 CAFZCand::Xi_Direction() const {
  return( (this->Eta_Direction()).Rotate(TMath::Pi()/2.) );
}

// p_ee over eta and xi direction
double CAFZCand::pee_eta() {
  TVector2 z_vec(_Px, _Py);
  TVector2 eta_direction = Eta_Direction();
  return z_vec * eta_direction;
}

double CAFZCand::pee_xi() {
  TVector2 z_vec(_Px, _Py);
  TVector2 xi_direction = Xi_Direction();
  return z_vec * xi_direction;
}

// recoil over eta and xi direction
double CAFZCand::recoil_eta() {
  TVector2 eta_direction = Eta_Direction();
  return _recoil * eta_direction;
}

double CAFZCand::recoil_xi() {
  TVector2 xi_direction = Xi_Direction();
  return _recoil * xi_direction;
}

//return eta balance
double CAFZCand::Eta_Balance() {
  return (pee_eta() + recoil_eta());
}

//return xi balance
double CAFZCand::Xi_Balance() {
  return (pee_xi() + recoil_xi());
}

//return f value for CC-CC events
double CAFZCand::f_CCCC() const {
  double angle_em = this->Angle_EM_EM();
  double f = 2*_E * sin(angle_em/2.) * sin(angle_em/2.)/_Mass;
  return f;
}

//return f value for EC-EC events
double CAFZCand::f_ECEC() const {
  double angle_em = this->Angle_EM_EM();
  double f = 2*_E * sin(angle_em/2.) * sin(angle_em/2.)/_Mass;
  return f;
}

//return f value for CC-EC events
double CAFZCand::f_CCEC() const {
  double f=0.;
  double angle_em = this->Angle_EM_EM();
  if( fabs(_EM[0]->CalDetectorEta())<1.3 )  f = _EM[0]->E() * (1-cos(angle_em))/_Mass;
  else f = _EM[1]->E() * (1-cos(angle_em))/_Mass;
  return f;
}

ClassImp(CAFZCand)
