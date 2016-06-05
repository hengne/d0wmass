#ifndef ZNUNUANALYSIS_HPP
#define ZNUNUANALYSIS_HPP

#include "cafe/Processor.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"
#include "wmass_analysis/MetSelector.hpp"
#include "wmass_analysis/MCSelector.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

class ZNuNuAnalysis : public cafe::Processor {
 public:
  ZNuNuAnalysis(const char *name);
  ~ZNuNuAnalysis();
  void begin();
  void finish();
  bool processEvent(cafe::Event& event);
  void EtFlowStudy(cafe::Event& event, float vtx[3]);
  CAFMet CalculateSNSubtrMet(cafe::Event& event, float vtx[3]);
  
  ClassDef(ZNuNuAnalysis, 0);
  
 private:
  
  // histograms
  hist_files _histos;
  
  // debug level
  int _debugLevel;
  
  // needed to force to instantinate MCSelector in ObjSelector
  // NOTE: both _MCStudy and _MCStudy_ZNuNu have to be 'true'
  //       in order to run ZNuNuAnalysis processor.
  //       Otherwise it will complain during initialization.
  bool _MCStudy;

  // hadronic recoil ET flow studies 
  //  
  bool _dumpRecoilInfo;                // dump measured hadronic recoil and generated Z info to an ASCII file
  bool _do_RecoilEtFlow_studies;       // perform ET flow studies (it will slow down the code!)
  float _RecoilEtFlow_studies_TowCut;  // max. tower ET taken into account in ET flow studies
  std::fstream *_znunu_out_recoil_txt; // write out: measured recoil and generated Z to a text file
  int   _NuLoose_nMin;                 // min. number of the RECO Loose neutrinos
  float _NuLoose_EtaMax;               // max. RECO detector |eta| of a Loose neutrino
  float _NuLoose_PtMin;                // min. RECO pT of a Loose neutrino
  int   _NuTight_nMin;                 // min. number of the RECO Tight neutrinos
  float _NuTight_EtaMax;               // max. RECO detector |eta| of a Tight neutrino
  float _NuTight_PtMin;                // min. RECO pT of a Tight neutrino
  bool  _MCStudy_ZNuNu;                // instructs ObjSelector to pass events without 2 good EM objects
  float _UtCutMax;                     // upper cut on recoil's UT  in an event (i.e. raw MET in this case)
  float _UtCutMin;                     // lower cut on recoil's UT  in an event (i.e. raw MET in this case)
  float _SETCutMax;                    // upper cut on SET in an event
  float _SETCutMin;                    // lower cut on SET in an event
  float _LumiCutMax;                   // upper cut on lumi in an event
  float _LumiCutMin;                   // lower cut on lumi in an event
  map<int,double> _RelResponse_scale;  // for rescaling average ET per PHI tower
  hist_files _EtFlow_histos;

  // Per-event "single neutrino subtraction"
  //
  bool _SubtractSingleNeutrinos;
  TString _SNdirectory;
  // Single neutrino metadata
  std::map<std::pair<int,int>,std::pair<int,int> > _SNmetadata;
  // Buffer for single neutrino event
  Int_t _SNrun;
  Int_t _SNevent;
  Int_t _SNn;
  Int_t _SNieta[50000];
  Int_t _SNiphi[50000];
  Int_t _SNlayer[50000];
  Float_t _SNe[50000];

};

#endif
