//
// Author: Rafael Lopes de Sa
// Date: 19/Mar/2012
//
// The EC reconstruction is different from the CC one.
// Let's see if I can get it right

#include "cafe/Processor.hpp"
#include "cafe/Event.hpp"

#include "wmass_util/CAFEMObj.hpp"
#include "tmb_tree/TMBCaloCell.hpp"

#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TTreeIndex.h"
#include "TVector2.h"

using namespace std;
using namespace cafe;


class FSRAnalysis : public cafe::Processor {

public:

  FSRAnalysis(const char* name);
  bool processEvent(cafe::Event& event);
  void finish();

  Double_t GetSET(Event& event, Float_t vtx[3], CAFEMObj* _emobj = 0);
  TVector2 GetSubtractedRecoil(Event& event,
			       Int_t zbncells, Int_t* zbieta, Int_t* zbiphi, Int_t* zblayer, Double_t* zbenergy, Bool_t* zbnormal,
			       Int_t mergedncells, Int_t* mergedieta, Int_t* mergediphi, Int_t* mergedlayer,
			       TMBCellContainer* ElectronCells,
			       Float_t vtx[3], Double_t& SET);
    
  ClassDef(FSRAnalysis, 1);

private:

  // debug level
  Int_t _debugLevel;
  
  // MC studies
  Bool_t _MCStudy;

  // Which run? Merged first!
  Bool_t _MergedRun;
  Bool_t _ZBoverlay;

  // Merged file name
  TString _MergedFileName;
  TString _FSRFileName;

  // Tree for FSR Study
  TFile* _FSRFile;
  TFile* _MergedFile;
  TTree* _FSRTree;
  TTree* _MergedTree;
  TTreeIndex* _MergedIndex;

  // The matched event/run numbers
  Int_t _EventNum, _RunNum; 
  Int_t _ZBEventNum, _ZBRunNum;
 
  Int_t _NTrueEl, _NTruePh, _NTrueNu;
  Int_t _NMergedTrueEl, _NMergedRecoEl;
  Int_t _NRecoEl, _NRecoPh;

  Double_t _TrueE[10], _TruePx[10], _TruePy[10], _TruePz[10];
  Double_t _RecoE[10], _RecoPx[10], _RecoPy[10], _RecoPz[10];
  Double_t _MergedTrueE[10], _MergedTruePx[10], _MergedTruePy[10], _MergedTruePz[10];
  Double_t _MergedRecoE[10], _MergedRecoPx[10], _MergedRecoPy[10], _MergedRecoPz[10];
  Double_t _TruePhE[10], _TruePhPx[10], _TruePhPy[10], _TruePhPz[10];
  Double_t _TrueNuE[10], _TrueNuPx[10], _TrueNuPy[10], _TrueNuPz[10];

  
  // The recoil cells
  Bool_t _ZBnormal[50000];
  Int_t _ZBieta[50000];
  Int_t _ZBiphi[50000];
  Int_t _ZBlayer[50000];
  Double_t _ZBenergy[50000];
  Int_t _ZBncells;

  Int_t _Merged_ieta[10][120];
  Int_t _Merged_iphi[10][120];
  Int_t _Merged_layer[10][120];
  Int_t _Merged_ncells[10];

  // Where and how it hits
  Double_t _RecoDetEta[10];
  Double_t _RecoUncorrE[10];
  Double_t _RecoDetPhi[10];
  Double_t _RecoFloor1[10];
  Double_t _RecoFloor2[10];
  Double_t _RecoFloor3[10];
  Double_t _RecoFloor4[10];
  Double_t _RecoFloor5[10];

  Double_t _MergedRecoDetEta[10];
  Double_t _MergedRecoUncorrE[10];
  Double_t _MergedRecoDetPhi[10];
  Double_t _MergedRecoFloor1[10];
  Double_t _MergedRecoFloor2[10];
  Double_t _MergedRecoFloor3[10];
  Double_t _MergedRecoFloor4[10];
  Double_t _MergedRecoFloor5[10];

  //electron track info
  Double_t _MergedTrackPt[10];
  Double_t _MergedTrackSMT[10];
  Double_t _MergedTrackCFT[10];
  Double_t _MergedTrackSpatialChi2[10];

  Double_t _TrackPt[10];
  Double_t _TrackSMT[10];
  Double_t _TrackCFT[10];
  Double_t _TrackSpatialChi2[10];

  // Good electron cuts
  Float_t _ElecPtCut, _DetEtaCC, _DetEtaEC1, _DetEtaEC2;
  Float_t _EMFracCut, _IsoCut, _HM7Cut, _HM8Cut;
  
  // MC Vertex
  Float_t _mcvtx[3];

  Double_t _SET[10], _MergedSET[10];
  Double_t _lumi;
  
  Bool_t _isPassEmFracIso[10]; // emobjs[ielec]->PassEMFracIso(_EMFracCut,_IsoCut);
  Bool_t _isPassHmx[10]; // emobjs[ielec]->PassHMx(_HM7Cut,_HM8Cut);
  Bool_t _isPassSpatialMatchLoose[10]; // emobjs[ielec]->has_spatial_track_match(-0.5);
  Bool_t _isPassCCFid[10]; // emobjs[ielec]->IsCCFid(_DetEtaCC);
  Bool_t _isPassSpatialMatchTight[10]; // emobjs[ielec]->has_good_spatial_track_match(0.01,_require_smt,10.,kFALSE);

  Bool_t _isPassEmFracIsoMerged[10]; // emobjs[ielec]->PassEMFracIso(_EMFracCut,_IsoCut);
  Bool_t _isPassHmxMerged[10]; // emobjs[ielec]->PassHMx(_HM7Cut,_HM8Cut);
  Bool_t _isPassSpatialMatchLooseMerged[10]; // emobjs[ielec]->has_spatial_track_match(-0.5);
  Bool_t _isPassCCFidMerged[10]; // emobjs[ielec]->IsCCFid(_DetEtaCC);
  Bool_t _isPassSpatialMatchTightMerged[10]; // emobjs[ielec]->has_good_spatial_track_match(0.01,_require_smt,10.,kFALSE);

  Double_t _RecoPhUPx[10][10], _RecoPhUPy[10][10];

  // Require SMT hit for track match     
  Bool_t _require_smt;
  Bool_t _require_smtEC;

  // Kill SCA list
  std::vector< std::vector<int> > _killcells;
  std::vector< std::vector<int> >::iterator _killcells_it;

  void initKillList();
  Bool_t isBadSCA(Int_t ZBrunNum, Int_t ieta, Int_t iphi);

  TMBCellContainer* _ElectronCells[10];
};
