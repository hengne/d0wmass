#ifndef UPARAMC_HPP
#define UPARAMC_HPP

#include "cafe/Processor.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"
#include <map>
#include <utility>
class TMBCellContainer;
class TTree;
class TBranch;



class uParaMCAnalysis : public cafe::Processor {

 public:
  uParaMCAnalysis(const char *name);
  void begin();
  void GetRawEnergy(const int ieta,const  int iphi, const TMBCellContainer * fCells, const double coshElecEta, double &energy, double &et, double &EMenergy, double &EMet, double &FHenergy, double &FHet);
  Double_t Feng_cone(const int elec_ieta, const int elec_iphi,const TMBCellContainer * fCells );
  Double_t Junjie_cone(const int elec_ieta, const int elec_iphi,const TMBCellContainer * fCells );
  bool processEvent(cafe::Event& event);
  void finish();

  ClassDef(uParaMCAnalysis, 0);
  
 private:
  // debug level
  int _debugLevel;
  
  // MC studies
  bool _MCStudy;

  // electron eta cuts
  float _DetEtaCC, _DetEtaEC1, _DetEtaEC2,  _ElecPtCut;
  
  // Z boson mass, pT cuts
  float _ZMassCut1, _ZMassCut2, _ZUtCut;

  // W boson transverse mass, Ut cut
  float _WMetCut, _WMtCut1, _WMtCut2, _WUtCut;

  //require SMT hit for track match     
  bool _require_smt, _StudyW, _StudyZ ;

  // number of spatial track matching requirement
  int _NumZSpatialTrk;

  bool _dorawCellsRecoil;
  bool _no_overlay;
  TTree *_tuple;
  TTree *_tuple2;

  Float_t _elec_E[2], _elec_uncorrE[2], _elec_deteta[2], _elec_detphi[2], _fcone[2], _jcone[2], _econe[2];
  Int_t _eventNum, _runNum, _elec_ieta[2], _elec_iphi[2], _nVtx, _ZBeventNum, _ZBrunNum, _nelec;
//   Int_t nCells1, nCells2;
//   Float_t Cell_E1[120];
//   Float_t Cell_ieta1[120];
//   Float_t Cells_iphi1[120];
//   Float_t Cells_iphilayer1[120];
  
//   Float_t Cell_E2[120];
//   Float_t Cell_ieta2[120];
//   Float_t Cells_iphi2[120];
//   Float_t Cells_iphilayer2[120];
  
  

  Int_t _eventNum2, _runNum2, _elec_ieta2[2], _elec_iphi2[2],_ZBeventNum2, _ZBrunNum2, _nelec2 ; 
  Float_t _elec_E_diff[2], _elec_E2[2];
  TBranch *_beventNum;
  TBranch *_brunNum;
  TBranch *_bZBeventNum;
  TBranch *_bZBrunNum;
  TBranch *_bieta;
  TBranch *_biphi;
  TBranch *_becone;
  TBranch *_bjcone;
  TBranch *_bfcone;
  TBranch *_bdeteta;
  TBranch *_bdetphi;
  TBranch *_belecE ;
  TBranch *_bnelec ;
  TBranch *_belecuncorrE ;
  std::map<std::pair<int, int> , int >  _ZBLibraryMap;
  std::map<std::pair<int, int> ,int >  _MCLibraryMap;
  std::pair<int, int> _ZBevent;
  std::pair<int, int> _MCevent;
  Int_t _ntotal;
  Int_t _nfail1;
  Int_t _nfail2;
  Int_t _nfail3;
  Int_t _nfail4;

  // histograms
  hist_files _histos;
};
#endif
