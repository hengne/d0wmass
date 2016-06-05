///////////////////////////////////////////////////////////////////
///    File: CAFWCabd.hpp                                       ///
///    Created: J. Zhu March 3, 2005                            ///
///                                                             ///
///    Purpose: W candidates                                    ///
///                                                             ///
///////////////////////////////////////////////////////////////////

#ifndef CAFWCAND_HPP
#define CAFWCAND_HPP

#include "wmass_util/CAFEMObj.hpp"
#include "wmass_util/CAFTrack.hpp"
#include "wmass_util/CAFMet.hpp"
#include "cafe/Event.hpp"
#include "TVector2.h"

#include <iostream>

class CAFWCand{
 
 public:
  CAFWCand();
  CAFWCand(const CAFEMObj *em, const CAFMet* met, float* vtx=0, bool metIsRaw=false);
  CAFWCand(const CAFWCand& other);   // unfortunately need to maintain copy constructor by hand
  virtual ~CAFWCand();

  const CAFEMObj* EM() {return _em;}
  const CAFMet* Met() {return _met;}
  
  void print() const;
 
  double Px() const;
  double Py() const;
  double Pt() const;  
  double Mt() const;
  TVector2 vect2() const;
  double DeltaPhi_EM_Met() const;
  double DeltaPhi_EM_Recoil() const;
  double UPara() const;
  double UPerp() const;
  double MagRecoil() const;
 
  int Type(double DetEtaCC, double DetEtaEC1, double DetEtaEC2) const; // 0 for CC, 1 for EC, 2 for other

  // return the TVector2 of the recoil system
  TVector2 GetRecoil() const;

  // ... and the MET TVector2 that goes with it
  TVector2 GetConsistentMET() const;

 private:
  const CAFEMObj* _em;
  const CAFMet* _met;

  double _Px;
  double _Py;
  double _Pt;
  
  TVector2 _recoil;
  TVector2 _consistentMET;

 public:
  ClassDef(CAFWCand, 0);
};

inline double CAFWCand::Px() const {return _Px;}
inline double CAFWCand::Py() const {return _Py;}
inline double CAFWCand::Pt() const {return _Pt;}

inline TVector2 CAFWCand::vect2() const {
  TVector2 vect(_Px, _Py);
  return vect;
}

inline double CAFWCand::MagRecoil() const {
  return sqrt(_Px*_Px+_Py*_Py);
}

// recoil system is actually back-to-back with the W boson
inline TVector2 CAFWCand::GetRecoil() const {
  TVector2 vect(-_Px, -_Py);
  return vect;
}

inline TVector2 CAFWCand::GetConsistentMET() const {
  return _consistentMET;
}

inline double CAFWCand::DeltaPhi_EM_Met() const {
  return (kinem::delta_phi(_em->Phi(), _met->metphi()));
}

inline double CAFWCand::DeltaPhi_EM_Recoil() const {
  return (kinem::delta_phi(_em->Phi(), (this->GetRecoil()).Phi()));
}

inline double CAFWCand::UPara() const {
  TVector2 vect_elec(_em->Px(), _em->Py());
  return ( this->GetRecoil() * vect_elec.Unit() );
}

inline double CAFWCand::UPerp() const {
  TVector2 vect_elec(_em->Px(), _em->Py());
  TVector2 perp_direction = vect_elec.Rotate(TMath::Pi()/2.);
  return ( this->GetRecoil() * perp_direction.Unit() );
}

// transverse mass 
inline double CAFWCand::Mt() const {
 double dphi = kinem::delta_phi(_em->Phi(), _met->metphi());
 double tmass = sqrt(2.0*_em->Pt()*_met->met()*(1-cos(dphi)));
 return tmass;
}

inline void CAFWCand::print() const {
  std::cout<<"W candidate pT="<<_Pt<<",Mt="<<Mt()<<",px="<<_Px<<",py="<<_Py<<std::endl;
}

#endif // CAFWCAND_HPP
