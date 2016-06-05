#include <iostream>
#include <vector>
#include "wmass_util/CAFWCand.hpp"

using namespace std;
  
CAFWCand::CAFWCand() {
  _met=0;
}

CAFWCand::CAFWCand(const CAFWCand& other) {
  _em=other._em;
  if (other._met) {
    _met = new CAFMet(other._met->metx(), other._met->mety(), other._met->met(), other._met->scalarEt());
  } else {
    _met=0;
  }

  _Px=other._Px;
  _Py=other._Py;
  _Pt=other._Pt;

  _recoil=other._recoil;
  _consistentMET=other._consistentMET;
}

CAFWCand::~CAFWCand() {
  //if (_met) delete _met;
}

// define W candidate with one EM object and missingEt 
CAFWCand::CAFWCand(const CAFEMObj *em, const CAFMet *met, float* vtx, bool metIsRaw) {
  _em = em;

  TVector2 em_vect(em->Px(), em->Py());
  TVector2 met_vect(met->metx(), met->mety());
  double scalarEt=met->scalarEt();
  if(vtx) {
    em_vect = ((CAFEMObj *)(em))->getRawElecVectorFromCells(vtx);

    double Ex_EMObj_corr = em->Px();
    double Ey_EMObj_corr = em->Py();

    double Ex_EMObj_raw = em->uncorrE()*sin(em->Theta())*cos(em->Phi());
    double Ey_EMObj_raw = em->uncorrE()*sin(em->Theta())*sin(em->Phi());

    if (!metIsRaw) {
      // invert what we have done in make_EMCorr in MetSelector to have raw MET without EM corrections
      // I will convert EM corrected MET back to raw MET
      met_vect.Set(met->metx() -(Ex_EMObj_raw-Ex_EMObj_corr), met->mety() -(Ey_EMObj_raw-Ey_EMObj_corr));
    } else {
      met_vect.Set(met->metx(),met->mety());
      scalarEt += (em->E()/em->uncorrE()-1.)*em->EMScalarEt();
    }
  }
  _recoil = -1. *(em_vect + met_vect);  // set recoil vector to -(em+met)

  TVector2 dummy(em->Px(),em->Py());
  _consistentMET = -1. * (_recoil + dummy);

  _met = new CAFMet(_consistentMET.X(), _consistentMET.Y(), _consistentMET.Mod(), scalarEt);

  _Px = em->Px() + _met->metx();
  _Py = em->Py() + _met->mety();
  _Pt = sqrt(_Px*_Px + _Py*_Py);

}//end constructor

// 0 for CC, 1 for EC, 2 for other
int CAFWCand::Type(double DetEtaCC, double DetEtaEC1, double DetEtaEC2) const {
  int type = -1;
  if(_em->IsCC(DetEtaCC)) type = 0;
  else if (_em->IsEC(DetEtaEC1, DetEtaEC2)) type = 1;
  else type = 2;
  return type;
}

ClassImp(CAFWCand)
