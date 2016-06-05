///////////////////////////////////////////////////////////////////
///    File: CAFTrack.hpp                                       ///
///    Created: J. Zhu March 3, 2005                            ///
///                                                             ///
///    Purpose: Track class to hold information for tracks      ///
///                                                             ///
///////////////////////////////////////////////////////////////////

#ifndef CAFTRACK_HPP
#define CAFTRACK_HPP

#include "cafe/Event.hpp"
#include "cafe/Variables.hpp"

#include "tmb_tree/TMBTrack.hpp"
#include "TVector2.h"
#include "TVector3.h"
#include <iostream>
#include <vector>

class CAFTrack {
  
 public:
  CAFTrack(TMBTrack* p);
  virtual ~CAFTrack();

  // get track
  const TMBTrack* getTrack() {return _tmbtrack_ptr;}

  friend bool ComparePt(const CAFTrack* track1, const CAFTrack* track2);
  
  TVector2 vect2() const;
  TVector3 vect3() const;

  // extrapolate track to EM3
  float TrackDetEta(int polarity, bool isGeantMC=false) const;
  float TrackDetPhi(int polarity, bool isGeantMC=false) const;
  
  // extrapolated track deteta and detphi must be in calorimeter fiducial region, only used to measure preselection efficiency
  bool IsCCECFid(float trk_deteta, float trk_detphi, float DetEtaCC, float DetEtaEC1, float DetEtaEC2) const;

  // update track parameters for new primary vertex
  void UpdateForNewVertex(float vertex_old[3], float vertex_new[3]);
  
  // isolated track
  bool IsIsolatedTrack(cafe::Event& event, float coneSize, float sumPtCut);

  void print() const;
  
  // basic functions
  Double_t Px() const {return _tmbtrack_ptr->Px();}
  Double_t Py() const {return _tmbtrack_ptr->Py();}
  Double_t Pz() const {return _tmbtrack_ptr->Pz();}
  Double_t Pt() const {return _tmbtrack_ptr->Pt();}
  Double_t E() const {return _tmbtrack_ptr->E();}
  Double_t Theta() const {return _tmbtrack_ptr->Theta();}
  Double_t Phi() const {return _tmbtrack_ptr->Phi();}
  Double_t Eta() const {return _tmbtrack_ptr->Eta();}

  Double_t xdca() const {return _tmbtrack_ptr->xdca();}
  Double_t ydca() const {return _tmbtrack_ptr->ydca();}

  Int_t nhit() const {return _tmbtrack_ptr->nhit();}
  Int_t ncft() const {return _tmbtrack_ptr->ncft();}
  Int_t nsmt() const {return _tmbtrack_ptr->nsmt();}

  Int_t charge() const {return _tmbtrack_ptr->charge();}
  Double_t rdca() const {return _tmbtrack_ptr->rdca();}        // R at dca.
  Double_t z() const {return _tmbtrack_ptr->z();}              // Z at dca.
  Double_t phid() const {return _tmbtrack_ptr->phid();}
  Double_t tlm() const {return _tmbtrack_ptr->tlm();}
  Double_t qpt() const {return _tmbtrack_ptr->qpt();}

  Double_t getChi2Ndf() const {return _tmbtrack_ptr->getChi2Ndf();}
  const Double_t* trpars() const {return _tmbtrack_ptr->trpars();}
  Double_t trpars(Int_t i) const {return _tmbtrack_ptr->trpars(i);}

  void SetPtEtaPhiE(Double_t Pt, Double_t Eta, Double_t Phi, Double_t E) {
   _tmbtrack_ptr->SetPtEtaPhiE(Pt, Eta, Phi, E);}

 private:
  TMBTrack *_tmbtrack_ptr;  

  cafe::Variables _trk_vars;

 public:
  ClassDef(CAFTrack, 0);
};

inline TVector2 CAFTrack::vect2() const {
  TVector2 vect(Px(), Py());
  return vect;
}

inline TVector3 CAFTrack::vect3() const {
  TVector3 vect(Px(), Py(), Pz());
  return vect;
}

inline void CAFTrack::print() const {
  std::cout<<"CAFTrack pT="<<Pt()<<",eta="<<Eta()<<",phi="<<Phi()<<std::endl;
}

#endif // CAFTRACK_HPP
