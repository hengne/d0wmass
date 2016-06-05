#ifndef EffANALYSIS_HPP
#define EffANALYSIS_HPP

#include "cafe/Processor.hpp"
#include "wmass_util/CAFZCand.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"


#include <string>
#include <vector>

class EffAnalysis : public cafe::Processor {
 public:
  EffAnalysis(const char *name);
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();
  
  void TriggerEff(cafe::Event& event);
  void PreSelectionEff(cafe::Event& event);
  void LooseTrackMatchEff(cafe::Event& event);
  void HMxEff(cafe::Event& event);
  void TrackMatchEff(cafe::Event& event);
  void MCEff(cafe::Event& event);
  void pTDependenceEff(cafe::Event& event);
  void LumiEff(cafe::Event& event);
  ClassDef(EffAnalysis, 0);

 private:
   // debug level
   int _debugLevel;

   // truth mode
   int _truthMode;

   // some switches to control "details" in the different Tag&Probe analyses -- probably want to introduce more of these
   bool _TPhmx_DoTheTrackFirst;
   bool _TPtrk_IncludeECtag;
   bool _TPtrk_TrigMatchOnTag_not_on_EitherObject;
   bool _TPtrk_DoTheStepByStepThing;
   bool _useTrackFiducial;
  
   // Z boson mass
   float _ZMassCut1, _ZMassCut2;
  
   float _ZUtCut;

   // MC study
   bool _MCStudy;

   // detector eta cuts
   float _DetEtaCC, _DetEtaEC1, _DetEtaEC2;

   // emfrac, isolation and hmatrix cuts, electron pT cut
   float _EMFracCut, _IsoCut, _HM7Cut, _HM8Cut, _ElecPtCut;

   // trigger names for v8-10, v11, v12, v13, v14, v15 and v16
   std::vector<std::string> _trignames[8];

   // track isolation requirements
   float _coneSize_Trk, _sumPtCut_Trk;

   bool _DropTriggerObjectMatchRequirement;

   double _InstLumi_lowcut, _InstLumi_highcut;
   
   EMClusterPosCorr *_emclusposcorr;

   // do raw cells for recoil
   bool _dorawCellsRecoil;
   bool _useConsistentMET;

   // histograms
   hist_files _histos;

  TTree *_tree3;

  Int_t tree3_run;  				
  Int_t tree3_evt;  				
  Int_t tree3_triglist;
  Float_t tree3_lumi;			 
  Float_t tree3_mee;			  
  Float_t tree3_probe_pt;  			  
  Int_t tree3_probe_chg;  			  
  Float_t tree3_probe_eta;  
  Int_t tree3_probe_trackmatch25;
  Int_t tree3_probe_trackmatch27;
  Float_t tree3_tag_pt;  			  
  Int_t tree3_tag_chg;  			  
  Float_t tree3_tag_eta;  
  Int_t tree3_tag_trackmatch25;
  Int_t tree3_tag_trackmatch27;
  Int_t tree3_pass_27;
  Int_t tree3_pass_25;

};

#endif
