///////////////////////////////////////////////////////////////////
///    File: CAFEMObj.hpp                                       ///
///    Created: J. Zhu March 3, 2005                            ///
///                                                             ///
///    Purpose: EM class to hold information for EM clusters    ///
///                                                             ///
///////////////////////////////////////////////////////////////////

#ifndef CAFEMOBJ_HPP
#define CAFEMOBJ_HPP

#include "cafe/Event.hpp"
#include "tmb_tree/TMBEMCluster.hpp"
#include "tmb_tree/TMBL1CalTower.hpp"
#include "tmb_tree/TMBL2GblEM.hpp"
#include "tmb_tree/TMBL3Ele.hpp"
#include "wmass_util/EMClusterPosCorr.hpp"
#include "kinem_util/AnglesUtil.hpp"

#include <iostream>
#include <vector>

class CAFEMObj {
  
 public:
  CAFEMObj(TMBEMCluster* p);
  virtual ~CAFEMObj();

  friend bool ComparePt(const CAFEMObj* emobj1, const CAFEMObj* emobj2);
  friend bool ComparePtElec(const CAFEMObj* emobj1, const CAFEMObj* emobj2);

  bool IsEM() const;
  bool IsCC(float DetEtaCC) const;
  bool IsEC(float DetEtaEC1, float DetEtaEC2) const;
  bool IsCCFid(float DetEtaCC, bool trkphi=true) const;
  bool IsECFid(float DetEtaEC1, float DetEtaEC2) const;
  bool IsCCECFid(float DetEtaCC, float DetEtaEC1, float DetEtaEC2, bool trkphi=true) const;
  bool PassEMFracIso(float EMFracCut, float IsoCut) const;
  bool PassEMFrac(float EMFracCut) const;
  bool PassIso(float IsoCut) const;
  bool PassHMx(float HMx7Cut, float HMx8Cut) const;
  float PhiMod() const;
  bool is_in_TrkPhiFid() const;                // track phi fiducial cut
  float TrkPhiMod() const;                     // track phi at DCA
  float TrkPhiEM3Mod(double trkphiEM3) const;  // track phi extrapolated to EM3
  int EMPhiModRegion() const;
  int TrkPhiModRegion() const;
  int TrkPhiEM3ModRegion(double trkphiEM3) const;
  int PhiModule() const;
  void SetTrkPhiEM3(Double_t trkphiem3)  {_trkphiem3 = trkphiem3;}  ;
  void SetTrkEtaEM3(Double_t trketaem3)  {_trketaem3 = trketaem3;}  ;

  // extrapolate the track to EM3 and calculate extrapolated phi
  // if no track match, just return 9999.  
  double trkPhiEM3(EMClusterPosCorr *emclusposcorr, int solenoid_polarity, Float_t Chi2Cut=0.01, bool isGeantMC=false) const;

  // extrapolate the track to EM3 and calculate extrapolated eta
  // if no track match, just return 1e10.  
  double trkEtaEM3(EMClusterPosCorr *emclusposcorr, int solenoid_polarity, Float_t Chi2Cut=0.01, bool isGeantMC=false) const;

  // 0 for 0<=|eta|<0.2, 1 for 0.2<=|eta|<0.4, 2 for 0.4<=|eta|<0.6, 3 for 0.6<=|eta|<0.8, 4 for 0.8<=|eta| 
  int EtaRegion_CC(float DetEtaCC) const; 
  // 0 and 14 for |eta|>1.3 and 1-13 for |eta|<1.3
  int FineEtaRegion_CC(float DetEtaCC) const; 
  // 0 for 0<=|deteta|<0.2, 1 for 0.2<=|deteta|<0.4, 2 for 0.4<=|deteta|<0.6, 3 for 0.6<=|deteta|<0.8, 4 for 0.8<=|deteta| 
  int DetEtaRegion_CC(float DetEtaCC) const; 
  // matched spatial track must have at least one SMT hit and pT>10 GeV
  bool has_good_spatial_track_match(Float_t Chi2Cut=0.01,Bool_t require_smt=kTRUE, Float_t track_pt_low=10.,Bool_t require_smtEC=kFALSE) const; 
  // calculate energy with cone 0.2<R<0.4 which mainly comes from underlying event contribution
  // where E_core means energy within R<0.2 and E_cone means energy within R<0.4
  // iso = (E_cone-E_core)/E_core and E_core = uncorrE()
  double energy_core_cone_FromIso() const; 

  // all vector information can be accessed from TMBLorentzVector
  // will not provide duplicate functions here
  TMBLorentzVector lorentzvector() const;
  TVector3 vect3() const;
  TVector2 vect2() const;

  // find the vector of the raw electron energy using electron cell information
  TVector2 getRawElecVectorFromCells(float thevert[3], float* SETcontrib=0);

  // recalculate px, py, eta, phi for new primary vertex
  void UpdateForNewVertex(float vertex_old[3], float vertex_new[3]);

  void print() const;

  // trigger functions
  int PassL1Trig(const char *name, double DeltaR_Cut, std::vector<const TMBL1CalTower*>& l1cal_vec, std::vector<const TMBL1Cal2bEM*>& l1cal2b_vec) const;
  int PassL2Trig(const char *name, double DeltaR_Cut, std::vector<const TMBL2GblEM*>& l2cal_vec) const;
  bool PassL3Trig(const char *name, double DeltaR_Cut, std::vector<const TMBL3Ele*>& l3cal_vec) const;
  bool PassL1L2L3Trig(const char *name, double DeltaR_Cut, std::vector<const TMBL1CalTower*>& l1cal_vec, std::vector<const TMBL1Cal2bEM*>& l1cal2b_vec, 
		      std::vector<const TMBL2GblEM*>& l2cal_vec, std::vector<const TMBL3Ele*>& l3cal_vec) const;
  bool PassTrigCMB(int triglist_flag, double DeltaR_Cut, std::vector<const TMBL1CalTower*>& l1cal_vec, std::vector<const TMBL1Cal2bEM*>& l1cal2b_vec, 
		   std::vector<const TMBL2GblEM*>& l2cal_vec, std::vector<const TMBL3Ele*>& l3cal_vec) const;
  
  //CEM(1, *)
  int PassL1_CEM(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL1CalTower*>& l1cal_vec) const;
  //CEM(2,*) symmetric
  bool PassL1_CEM2(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL1CalTower*>& l1cal_vec) const;
  //CEM(1,*) CEM(2,*) asymmetric
  bool PassL1_CEM3(double DeltaR_Cut, double Et_Cut1, double Et_Cut2, std::vector<const TMBL1CalTower*>& l1cal_vec) const;
  //CSWEM(1,*) RunIIb
  int PassL1_CSWEM(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL1Cal2bEM*>& l1cal_vec) const;
  //Hengne -- withEt, CSWEM(1,*) RunIIb
  int PassL1_CSWEM_withEt(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL1Cal2bEM*>& l1cal_vec, double& Et) const;

  //EM(1, *)
  int PassL2_EM(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL2GblEM*>& l2cal_vec) const;

  //Hengne -- withEt, EM(1, *)
  int PassL2_EM_withEt(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL2GblEM*>& l2cal_vec, double& Et) const;

  //EM(2, *)
  bool PassL2_2EM(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL2GblEM*>& l2cal_vec) const;
  //EM(1, *, *)
  int PassL2_EM_Iso(double DeltaR_Cut, double Et_Cut, double Iso_Cut, std::vector<const TMBL2GblEM*>& l2cal_vec) const;
  //Hengne -- withEt, EM(1, *, *)
  int PassL2_EM_Iso_withEt(double DeltaR_Cut, double Et_Cut, double Iso_Cut, std::vector<const TMBL2GblEM*>& l2cal_vec, double& Et) const;

  //EM(1,*,*)
  int CAFEMObj::PassL2_EM_lhood(double DeltaR_Cut, double Et_Cut, double lhood_Cut, std::vector<const TMBL2GblEM*>& l2cal_vec) const;
  //Hengne -- withEt, EM(1,*,*)
  int CAFEMObj::PassL2_EM_lhood_withEt(double DeltaR_Cut, double Et_Cut, double lhood_Cut, std::vector<const TMBL2GblEM*>& l2cal_vec, double& Et) const;
  

  //ELE_LOOSE_SH_T
  bool PassL3_ELE_LOOSE_SH_T(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL3Ele*>& l3cal_vec) const;
  //ELE_LOOSE
  bool PassL3_ELE_LOOSE(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL3Ele*>& l3cal_vec) const;
  //ELE_NLV_SHT
  bool PassL3_ELE_NLV_SHT(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL3Ele*>& l3cal_vec) const;
  //Hengne -- withEt, ELE_NLV_SHT
  bool PassL3_ELE_NLV_SHT_withEt(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL3Ele*>& l3cal_vec, double& Et) const;
  //ELE_NLV_SH
  bool PassL3_ELE_NLV_SH(double DeltaR_Cut, double Et_Cut, std::vector<const TMBL3Ele*>& l3cal_vec) const;

  // get pointer to EM cluster
  const TMBEMCluster* getEMCluster() const {return _tmbemcluster_ptr;}

  // basic functions
  Double_t Px() const {return _tmbemcluster_ptr->Px();}
  Double_t Py() const {return _tmbemcluster_ptr->Py();}
  Double_t Pz() const {return _tmbemcluster_ptr->Pz();}
  Double_t Pt() const {return _tmbemcluster_ptr->Pt();}
  Double_t E() const {return _tmbemcluster_ptr->E();}
  Double_t Theta() const {return _tmbemcluster_ptr->Theta();}
  Double_t Phi() const {return _tmbemcluster_ptr->Phi();}
  Double_t Eta() const {return _tmbemcluster_ptr->Eta();}
  void SetPtEtaPhiE(Double_t Pt, Double_t Eta, Double_t Phi, Double_t E) {_tmbemcluster_ptr->SetPtEtaPhiE(Pt, Eta, Phi, E);}

  Float_t       uncorrE()  const  {return _tmbemcluster_ptr->uncorrE();}
  Float_t       charge()   const  {return _tmbemcluster_ptr->charge();}
  Int_t         id()       const  {return _tmbemcluster_ptr->id();}
  Float_t       iso()      const  {return _tmbemcluster_ptr->iso();}
  Float_t       EMScalarEt() const {return _tmbemcluster_ptr->EMScalarEt();}
  Float_t       emfrac()      const        {return _tmbemcluster_ptr->emfrac();}
  Float_t       HA()          const        {return _tmbemcluster_ptr->HA();}
  Float_t       HMx7()        const        {return _tmbemcluster_ptr->HMx7();}
  Float_t       HMx8()        const        {return _tmbemcluster_ptr->HMx8();}
  Float_t       Excess()      const        {return _tmbemcluster_ptr->Excess();}
  const TMBTrack*      GetChargedTrack() const    {return _tmbemcluster_ptr->GetChargedTrack();}
  const TMBVertex*     GetVertex()       const    {return _tmbemcluster_ptr->GetVertex();}

  const TMBCaloCell*  GetCaloCell(UInt_t icell) const   { return _tmbemcluster_ptr->GetCaloCell(icell);   }
  UInt_t         ncells() const { return _tmbemcluster_ptr->ncells();}

  Bool_t       is_in_phi_fiducial()    const        {return _tmbemcluster_ptr->is_in_phi_fiducial();}
  Bool_t       is_in_eta_fiducial()    const        {return _tmbemcluster_ptr->is_in_eta_fiducial();}
  Bool_t       is_in_fiducial()        const        {return _tmbemcluster_ptr->is_in_fiducial();}
  Float_t      CalE()                  const        {return _tmbemcluster_ptr->CalE();}
  Float_t      CalPhi()                const        {return _tmbemcluster_ptr->CalPhi();}
  Float_t      TrkPhiEM3()             const        {
    if (_trkphiem3<0.0 || _trkphiem3>(2*TMath::Pi())){
      std::cout<<"Message from wmass_util/wmass_util/CAFEMObj.hpp :"<<std::endl;
      std::cout<<" _trkphiem3="<<_trkphiem3<<" has not been set to a meaningful value. "<<std::endl;
      std::cout<<" It should be within [0.0, 2*TMath::Pi()] "<<std::endl;
      std::cout<<"               exiting(1)...                     "<<std::endl;
      std::cout<<"end of Message from wmass_util/wmass_util/CAFEMObj.hpp"<<std::endl;
      exit(1);
    } 
    else return _trkphiem3;
  }
  Float_t      TrkEtaEM3()             const        {return _trketaem3; }

  Float_t      CalEta()                const        {return _tmbemcluster_ptr->CalEta();}
  Float_t      CalEt()                 const        {
    double CalTheta = 2.0*atan(exp(-CalEta()));
    return (CalE() * sin(CalTheta));
  }
  Float_t floorE(Int_t nfloor) const {return _tmbemcluster_ptr->floorE(nfloor);}
  Float_t floorX(Int_t nfloor) const {return _tmbemcluster_ptr->floorX(nfloor);}
  Float_t floorY(Int_t nfloor) const {return _tmbemcluster_ptr->floorY(nfloor);}
  Float_t floorZ(Int_t nfloor) const {return _tmbemcluster_ptr->floorZ(nfloor);}
  
  Float_t      CalDetectorPhi()        const        {return _tmbemcluster_ptr->CalDetectorPhi();}
  Float_t      CalDetectorEta()        const        {return _tmbemcluster_ptr->CalDetectorEta();}
  Float_t      Lhood8()                const        {return _tmbemcluster_ptr->Lhood8();}
  Float_t      LhoodCps()              const        { return _tmbemcluster_ptr->LhoodCps(); }
  Float_t      Lhood3()                const        { return _tmbemcluster_ptr->Lhood3(); }
  Float_t      Lhood4Iso()             const        { return _tmbemcluster_ptr->Lhood4Iso(); }
  Float_t      Lhood4EOP()             const        { return _tmbemcluster_ptr->Lhood4EOP(); }
  
  Float_t      track_match_chi2prob()  const        {return _tmbemcluster_ptr->track_match_chi2prob();}
  Float_t      track_match_spatialchi2prob()  const {return _tmbemcluster_ptr->track_match_spatialchi2prob();}
  Bool_t       has_track_match(Float_t Chi2Cut=0.01)  const   {return _tmbemcluster_ptr->has_track_match(Chi2Cut);}
  Bool_t       has_spatial_track_match(Float_t Chi2Cut=0.01) const {return _tmbemcluster_ptr->has_spatial_track_match(Chi2Cut);}
  const TMBTrack*     getPtrChp()       const        {return _tmbemcluster_ptr->getPtrChp();}
  Int_t        nChPart()               const         {return _tmbemcluster_ptr->nChPart();}
  const TMBTrack*     GetChPart(Int_t itr)    const    {return _tmbemcluster_ptr->GetChPart(itr);}
  Float_t      track_match_chi2prob(Int_t itr) const   {return _tmbemcluster_ptr->track_match_chi2prob(itr);}
  Float_t      track_match_spatialchi2prob(Int_t itr) const {return _tmbemcluster_ptr->track_match_spatialchi2prob(itr);}

  const TMBTrack* getPtrSpatialChp() const {
    return _tmbemcluster_ptr->getPtrChpSpatial();
  }
  
  Float_t      TrkPhi() const {
    if (getPtrSpatialChp()!=NULL) return getPtrSpatialChp()->Phi();
    else return -1.0;
  }
    
private:
  TMBEMCluster* _tmbemcluster_ptr;
  Double_t _trkphiem3;
  Double_t _trketaem3;
  
public:
  ClassDef(CAFEMObj, 0);
};

inline bool CAFEMObj::IsEM() const {return (TMath::Abs(id())==10 || TMath::Abs(id())==11); }

inline bool CAFEMObj::PassEMFracIso(float EMFracCut, float IsoCut) const {
  return ((emfrac()>EMFracCut) && (iso()<IsoCut));
}

inline bool CAFEMObj::PassEMFrac(float EMFracCut) const {
  return (emfrac()>EMFracCut);
}

inline bool CAFEMObj::PassIso(float IsoCut) const {
  return (iso()<IsoCut);
}

inline bool CAFEMObj::PassHMx(float HMx7Cut, float HMx8Cut) const {
  bool passHMx = false;
  if(fabs(CalDetectorEta())<1.3 && HMx7()<HMx7Cut) passHMx = true;
  else if (fabs(CalDetectorEta())>=1.3 && HMx8()<HMx8Cut) passHMx = true;
  return passHMx;
}

inline bool CAFEMObj::IsCC(float DetEtaCC) const {
  return (fabs(CalDetectorEta())<DetEtaCC); 
}

inline bool CAFEMObj::IsEC(float DetEtaEC1, float DetEtaEC2) const {
  return ( fabs(CalDetectorEta())>DetEtaEC1 && fabs(CalDetectorEta())<DetEtaEC2 ); 
}

inline bool CAFEMObj::IsCCFid(float DetEtaCC, bool trkphi) const {
  bool isfid=false;
  if (trkphi)
     return (IsCC(DetEtaCC) && is_in_TrkPhiFid());
  else
    return (IsCC(DetEtaCC) && is_in_fiducial());
}

// 0 for 0<=|eta|<0.2, 1 for 0.2<=|eta|<0.4, 2 for 0.4<=|eta|<0.6, 3 for 0.6<=|eta|<0.8, 4 for 0.8<=|eta| 
inline int CAFEMObj::EtaRegion_CC(float DetEtaCC) const {  
  int region = -1;
  if(IsCCFid(DetEtaCC)) {
    double abseta = fabs(Eta());
    if(abseta<0.2) region = 0;
    else if (abseta<0.4) region = 1;
    else if (abseta<0.6) region = 2;
    else if (abseta<0.8) region = 3;
    else region = 4;
  }
  return region;
}

// 0 and 14 for |eta|>1.3, 1-13 for |eta|<1.3
inline int CAFEMObj::FineEtaRegion_CC(float DetEtaCC) const {  
  int region = -1;
  if(IsCCFid(DetEtaCC)) {
    double eta = Eta();

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

// 0 for 0<=|eta|<0.2, 1 for 0.2<=|eta|<0.4, 2 for 0.4<=|eta|<0.6, 3 for 0.6<=|eta|<0.8, 4 for 0.8<=|eta| 
inline int CAFEMObj::DetEtaRegion_CC(float DetEtaCC) const {  
  int region = -1;
  if(IsCCFid(DetEtaCC)) {
    double absdeteta = fabs(CalDetectorEta());
    if(absdeteta<0.2) region = 0;
    else if (absdeteta<0.4) region = 1;
    else if (absdeteta<0.6) region = 2;
    else if (absdeteta<0.8) region = 3;

    else region = 4;
  }
  return region;
}
inline bool CAFEMObj::IsECFid(float DetEtaEC1, float DetEtaEC2) const {
  return (IsEC(DetEtaEC1, DetEtaEC2) && is_in_fiducial());
}

inline bool CAFEMObj::IsCCECFid(float DetEtaCC, float DetEtaEC1, float DetEtaEC2, bool trkphi) const {
  return (IsCCFid(DetEtaCC,trkphi) || IsECFid(DetEtaEC1, DetEtaEC2));
}

inline float CAFEMObj::PhiMod() const {
  return (fmod(16.*CalDetectorPhi()/3.1415926, 1.0));
}

inline float CAFEMObj::TrkPhiMod() const {
  return (fmod(16.*TrkPhi()/3.1415926, 1.0));
}

inline float CAFEMObj::TrkPhiEM3Mod(double trkphiEM3) const {
  return (fmod(16.*trkphiEM3/3.1415926, 1.0));
}
// phimod regions defined as 0 for [0.0,0.1], 1 for (0.1,0.2], 2 for (0.2,0.3], 3 for (0.3,0.4] and 4 for (0.4,0.5]
// they are folded so that 0.9 to 1.0 is the same as 0.0 to 0.1. 
inline int CAFEMObj::EMPhiModRegion() const {  
  int region = -1;
  if ((PhiMod()>=0.0 && PhiMod()<=0.1) || (PhiMod()>0.9 && PhiMod()<=1.0)) region = 0;
  else if ((PhiMod()>0.1 && PhiMod()<=0.2) || (PhiMod()>0.8 && PhiMod()<=0.9)) region = 1;
  else if ((PhiMod()>0.2 && PhiMod()<=0.3) || (PhiMod()>0.7 && PhiMod()<=0.8)) region = 2;
  else if ((PhiMod()>0.3 && PhiMod()<=0.4) || (PhiMod()>0.6 && PhiMod()<=0.7)) region = 3;
  else if ((PhiMod()>0.4 && PhiMod()<=0.5) || (PhiMod()>0.5 && PhiMod()<=0.6)) region = 4;
  
  return region;
}

// phimod (track phi at DCA) regions defined as 0 for [0.0,0.1], 1 for (0.1,0.2], 2 for (0.2,0.3], 3 for (0.3,0.4] and 4 for (0.4,0.5]
// they are folded so that 0.9 to 1.0 is the same as 0.0 to 0.1. 
inline int CAFEMObj::TrkPhiModRegion() const {  
  int region = -1;
  if ((TrkPhiMod()>=0.0 && TrkPhiMod()<=0.1) || (TrkPhiMod()>0.9 && TrkPhiMod()<=1.0)) region = 0;
  else if ((TrkPhiMod()>0.1 && TrkPhiMod()<=0.2) || (TrkPhiMod()>0.8 && TrkPhiMod()<=0.9)) region = 1;
  else if ((TrkPhiMod()>0.2 && TrkPhiMod()<=0.3) || (TrkPhiMod()>0.7 && TrkPhiMod()<=0.8)) region = 2;
  else if ((TrkPhiMod()>0.3 && TrkPhiMod()<=0.4) || (TrkPhiMod()>0.6 && TrkPhiMod()<=0.7)) region = 3;
  else if ((TrkPhiMod()>0.4 && TrkPhiMod()<=0.5) || (TrkPhiMod()>0.5 && TrkPhiMod()<=0.6)) region = 4;
  
  return region;
}

// phimod regions (track phi at EM3) defined as 0 for [0.0,0.1], 1 for (0.1,0.2], 2 for (0.2,0.3], 3 for (0.3,0.4] and 4 for (0.4,0.5]
// they are folded so that 0.9 to 1.0 is the same as 0.0 to 0.1. 
inline int CAFEMObj::TrkPhiEM3ModRegion(double trkphiEM3) const {  
  int region = -1;
  double PhiEM3Mod = TrkPhiEM3Mod(trkphiEM3);
  if ((PhiEM3Mod>=0.0 && PhiEM3Mod<=0.1) || (PhiEM3Mod>0.9 && PhiEM3Mod<=1.0)) region = 0;
  else if ((PhiEM3Mod>0.1 && PhiEM3Mod<=0.2) || (PhiEM3Mod>0.8 && PhiEM3Mod<=0.9)) region = 1;
  else if ((PhiEM3Mod>0.2 && PhiEM3Mod<=0.3) || (PhiEM3Mod>0.7 && PhiEM3Mod<=0.8)) region = 2;
  else if ((PhiEM3Mod>0.3 && PhiEM3Mod<=0.4) || (PhiEM3Mod>0.6 && PhiEM3Mod<=0.7)) region = 3;
  else if ((PhiEM3Mod>0.4 && PhiEM3Mod<=0.5) || (PhiEM3Mod>0.5 && PhiEM3Mod<=0.6)) region = 4;
  
  return region;
}

inline int CAFEMObj::PhiModule() const {
  return ((int)(CalDetectorPhi()/(3.1415926/16.)));
}

inline TMBLorentzVector CAFEMObj::lorentzvector() const {
  TMBLorentzVector lv(Px(), Py(), Pz(), E());
  return lv;
}

inline TVector3 CAFEMObj::vect3() const {
  TVector3 vect(Px(), Py(), Pz());
  return vect;
}

inline TVector2 CAFEMObj::vect2() const {
  TVector2 vect(Px(), Py());
  return vect;
}

inline void CAFEMObj::print() const {
  std::cout<<"id="<<id()<<",pT="<<Pt()<<",eta="<<Eta()<<",phi="<<Phi()
           <<",deteta="<<CalDetectorEta()<<",detphi="<<CalDetectorPhi()
	   <<",emfrac="<<emfrac()<<",iso="<<iso()<<",hm7="<<HMx7()
	   <<",hm8="<<HMx8()<<std::endl;
}

// good spatial track match, at least one SMT hit and pT>10 GeV
// this only applies for electrons in CC region
inline bool CAFEMObj::has_good_spatial_track_match(Float_t Chi2Cut, Bool_t require_smt, Float_t track_pt_low, Bool_t require_smtEC) const {
  bool good_track = false;
  if(_tmbemcluster_ptr->has_spatial_track_match(Chi2Cut)) {
    const TMBTrack *tmp_track = _tmbemcluster_ptr->getPtrChpSpatial();
    // for EC region, require spatial only track
    if(tmp_track!=NULL) {
      if(fabs(_tmbemcluster_ptr->CalDetectorEta())>1.3) {  // for CC region, require good spatial only track
	if (require_smtEC){
	  if (tmp_track->nsmt()>0) good_track = true;
	} else
	  good_track = true;  
      } else {  // for CC region, require good spatial only track
	if (require_smt){
	  if(tmp_track->Pt()>track_pt_low && tmp_track->nsmt()>0) good_track = true; //  && tmp_track->nsmt()>0)
	}	  
	else
	  if(tmp_track->Pt()>track_pt_low) good_track = true;  
      }
    }
  }
  return good_track;
}

// calculate energy with cone 0.2<R<0.4 which mainly comes from underlying event contribution
// where E_core means energy within R<0.2 and E_cone means energy within R<0.4
// iso = (E_cone-E_core)/E_core and E_core = uncorrE()
inline double CAFEMObj::energy_core_cone_FromIso() const {
  return (_tmbemcluster_ptr->uncorrE()*_tmbemcluster_ptr->iso());
}

#endif // CAFEMOBJ_HPP
