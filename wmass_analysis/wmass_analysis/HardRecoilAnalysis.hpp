// Author: Rafael Lopes de Sa
// Date: 8/May/2012
//

#include "cafe/Processor.hpp"
#include "cafe/Event.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "tmb_tree/TMBCaloCell.hpp"

#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TTreeIndex.h"

#include <vector>

using namespace std;
using namespace cafe;

class HardRecoilAnalysis : public cafe::Processor {

public:

  HardRecoilAnalysis(const char* name);
  bool processEvent(cafe::Event& event);
  void finish();

  TVector2 GetSubtractedRecoil(Event& event, Int_t zbncells, Int_t* zbieta, Int_t* zbiphi, Int_t* zblayer, Double_t* zbenergy, Bool_t* zbnormal, Float_t vtx[3], Double_t& SET, Bool_t subtract = true);
  TVector2 GetRecoil(Event& event, Int_t zbncells, Int_t* zbieta, Int_t* zbiphi, Int_t* zblayer, Double_t* zbenergy, Bool_t* zbnormal, Float_t vtx[3], Double_t& SET);

  Bool_t isBadSCA(Int_t ZBrunNum, Int_t ieta, Int_t iphi);

  ClassDef(HardRecoilAnalysis, 1);

private:

  // debug level
  Int_t _debugLevel;
  
  // MC studies
  Bool_t _MCStudy;

  // ZB file name
  TString _ZBrunList;
  TString _ZBfileName;
  Bool_t _ZBrun;

  // Tree for HardRecoil Study
  TFile* _HardRecoilFile; 
  TTree* _HardRecoilTree;

  TFile* _ZBFile; 
  TTree* _ZBTree; // To write
  TFile* _ZBLibraryFile[120]; // Library
  TTree* _ZBLibrary[120]; // Library
  Int_t _numZBLib;

  // The matched event/run numbers
  Int_t _eventNum, _runNum, _ZBeventNum, _ZBrunNum;

  Double_t _Ztruepx, _Ztruepy, _Ztruepz, _ZtrueE;
  Double_t _utruepx, _utruepy, _utruepz, _utrueE;
  Double_t _urecopx, _urecopy, _urecopT, _urecophi;
  Double_t _uzbpx, _uzbpy, _uzbpT, _uzbphi;
  Double_t _ubothpx, _ubothpy, _ubothpT, _ubothphi;
  
  // SET and luminosity
  Double_t _lumi;
  Double_t _SET;
  Double_t _ZBSET;
  Double_t _bothSET;
  Double_t _tickNum;

  // Cut variables
  Int_t   _NuLoose_nMin;
  Double_t _NuLoose_EtaMax;               
  Double_t _NuLoose_PtMin;
  Int_t   _NuTight_nMin;
  Double_t _NuTight_EtaMax;
  Double_t _NuTight_PtMin;
  Double_t _UtCutMax;
  Double_t _UtCutMin;
  Double_t _PtCutMax;
  Double_t _PtCutMin;
  Double_t _SETCutMax;
  Double_t _SETCutMin;
  Double_t _LumiCutMax;
  Double_t _LumiCutMin;

  Bool_t _ZBnormal[50000];
  Int_t _ZBieta[50000];
  Int_t _ZBiphi[50000];
  Int_t _ZBlayer[50000];
  Double_t _ZBenergy[50000];
  Int_t _ZBncells;

  Bool_t _useMCvertex;

  std::vector< std::vector<int> > _killcells;
  std::vector< std::vector<int> >::iterator _killcells_it;

  void initKillList();
  
};
