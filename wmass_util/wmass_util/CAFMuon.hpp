#ifndef CAFMUON_HPP
#define CAFMUON_HPP

#include "cafe/Event.hpp"
#include "tmb_tree/TMBMuon.hpp"

#include <iostream>

class CAFMuon {
  
 public:
  CAFMuon(TMBMuon* p);
  virtual ~CAFMuon();

  friend bool ComparePt(const CAFMuon* mu1, const CAFMuon* mu2);

  // get muon
  const TMBMuon* getMuon() {return _tmbmuon_ptr;}

  // basic functions
  Double_t Px() const {return _tmbmuon_ptr->Px();}
  Double_t Py() const {return _tmbmuon_ptr->Py();}
  Double_t Pz() const {return _tmbmuon_ptr->Pz();}
  Double_t Pt() const {return _tmbmuon_ptr->Pt();}
  Double_t E() const {return _tmbmuon_ptr->E();}
  Double_t Theta() const {return _tmbmuon_ptr->Theta();}
  Double_t Phi() const {return _tmbmuon_ptr->Phi();}
  Double_t Eta() const {return _tmbmuon_ptr->Eta();}

  Int_t       charge()  const {return _tmbmuon_ptr->charge();}

  // muon system info:
  Int_t       nhit()                    const {return _tmbmuon_ptr->nhit();}
  Int_t       ndeck()                   const {return _tmbmuon_ptr->ndeck();}
  Int_t       region()                  const {return _tmbmuon_ptr->region();}
  Int_t       octant()                  const {return _tmbmuon_ptr->octant();}
  Float_t     chisqloc()                const {return _tmbmuon_ptr->chisqloc();}
  Float_t     sctimeA()                 const {return _tmbmuon_ptr->sctimeA();}
  Float_t     sctimeB()                 const {return _tmbmuon_ptr->sctimeB();}
  Float_t     sctimeC()                 const {return _tmbmuon_ptr->sctimeC();}
  Float_t     xA()                      const {return _tmbmuon_ptr->xA();}
  Float_t     yA()                      const {return _tmbmuon_ptr->yA();}
  Float_t     zA()                      const {return _tmbmuon_ptr->zA();}
  Float_t     bdl()                     const {return _tmbmuon_ptr->bdl();}

  // matching info:
  Int_t       nseg()                    const {return _tmbmuon_ptr->nseg();}
  Int_t       ndof()                    const {return _tmbmuon_ptr->ndof();}
  Float_t     deltaPhi()                const {return _tmbmuon_ptr->deltaPhi();}
  Float_t     deltaEta()                const {return _tmbmuon_ptr->deltaEta();}
  Float_t     deltaDrift()              const {return _tmbmuon_ptr->deltaDrift();}
  Float_t     chisq()                   const {return _tmbmuon_ptr->chisq();}
  Float_t     zAtPca()                  const {return _tmbmuon_ptr->zAtPca();}
  Float_t     impPar()                  const {return _tmbmuon_ptr->impPar();}
  Float_t     impParSig()               const {return _tmbmuon_ptr->impParSig();}
  Float_t     err_impPar()              const {return _tmbmuon_ptr->err_impPar();}
  Float_t     err_zAtPca()              const {return _tmbmuon_ptr->err_zAtPca();}
  Float_t     dca()                     const {return _tmbmuon_ptr->dca();}
  Float_t     detectorEta()             const {return _tmbmuon_ptr->detectorEta();}
  TMBTrack*   GetChargedTrack()         const {return _tmbmuon_ptr->GetChargedTrack();}
  TMBVertex*  GetVertex()               const {return _tmbmuon_ptr->GetVertex();}

  // MTC info:
  Int_t       calnLayer()               const {return _tmbmuon_ptr->calnLayer();}
  Int_t       nmtc()                    const {return _tmbmuon_ptr->nmtc();}
  Float_t     etrack_best()             const {return _tmbmuon_ptr->etrack_best();}
  Float_t     caleSig()                 const {return _tmbmuon_ptr->caleSig();}
  Float_t     calEta()                  const {return _tmbmuon_ptr->calEta();}
  Float_t     calPhi()                  const {return _tmbmuon_ptr->calPhi();}
  Float_t     eloss()                   const {return _tmbmuon_ptr->eloss();}

  // Isolation info:
  Int_t       nTrk5()                   const {return _tmbmuon_ptr->nTrk5();}
  Float_t     EInCone1()                const {return _tmbmuon_ptr->EInCone1();}
  Float_t     EInCone15()               const {return _tmbmuon_ptr->EInCone15();}
  Float_t     EInCone2()                const {return _tmbmuon_ptr->EInCone2();}
  Float_t     EInCone4()                const {return _tmbmuon_ptr->EInCone4();}
  Float_t     EInCone6()                const {return _tmbmuon_ptr->EInCone6();}
  Float_t     drJet5()                  const {return _tmbmuon_ptr->drJet5();}
  Float_t     etTrkCone5()              const {return _tmbmuon_ptr->etTrkCone5();}
  Float_t     etHalo()                  const {return _tmbmuon_ptr->etHalo();}

  // Flags:
  Int_t       isLoose()                 const { return _tmbmuon_ptr->isLoose();}
  Int_t       isMedium()                const { return _tmbmuon_ptr->isMedium();}
  Int_t       isTight()                 const {return _tmbmuon_ptr->isTight();}
  Int_t       hasLocal()                const {return _tmbmuon_ptr->hasLocal();}
  Int_t       hasCentral()              const {return _tmbmuon_ptr->hasCentral();}
  Int_t       hasCal()                  const {return _tmbmuon_ptr->hasCal();}
  Int_t       isMuonEventOK()           const {return _tmbmuon_ptr->isMuonEventOK();}
  Int_t       isCosmic()                const {return _tmbmuon_ptr->isCosmic();}
  Int_t       isCosmicT()               const {return _tmbmuon_ptr->isCosmicT();}

 private:
   TMBMuon* _tmbmuon_ptr;
  
 public:
  ClassDef(CAFMuon, 0);
};

#endif
