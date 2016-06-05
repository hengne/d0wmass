#ifndef INC_EFFICIENCYSMEAR
#define INC_EFFICIENCYSMEAR

#include "PMCSEMObj.hpp"
#include "PMCSVtx.hpp"
#include "PParameterReader.hpp"
#include "hist_files.hpp"

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TString.h"
#include "TRandom3.h"
#include "TSpline.h"
#include <vector>
#include <map>

class EfficiencySmear {
  
 public:

  //constructor and read in smearing parameters
  EfficiencySmear(TString parameter_filename, hist_files &_histos, bool includeECtag);

  //destructor
  ~EfficiencySmear(){;}

  // Efficiencies

  bool passesTriggerEff(PMCSEMObj part, TRandom3 *dummy, double TrigVer, Int_t runNum, double* externalRndm=0, int force_trigger=0);
  bool passesPreselEff(PMCSEMObj part, TRandom3 *dummy, double* externalRndm=0, PMCSVtx *vtx=0, double* externalRndtrk=0, bool neverUseTrack=false);
  bool passesEMIDEff(PMCSEMObj part, TRandom3 *dummy, double* externalRndm=0);
  bool passesTrkEff(PMCSEMObj part, PMCSVtx vtx, TRandom3 *dummy, double* externalRndm=0);
  bool passesLooseTrkEff(PMCSEMObj part, PMCSVtx *vtx, TRandom3 *dummy, double* externalRndm=0);
  //
  bool passesClusPtEff(PMCSEMObj part, TRandom3 *dummy, double* externalRndm=0);
  bool passesElecPhiEff(PMCSEMObj part, TRandom3 *dummy, bool useDetPhi=false, double* externalRndm=0);

  bool passesAddOnEff(PMCSEMObj part, bool isW, TRandom3 *dummy, int otherpass_flag=2, double* externalRndm=0);
 

  //return type of triger used.
  int TriggerType(Int_t runNo);
  int run_has_triggers( int runNo ) { return _trigger_map[runNo].size(); }

  Double_t ApplyRecoilReweight(Double_t DPhi, Double_t zPt, Double_t luminosity=0.0);

  // Set run number
  void SetRunNumber(double runnumber);

  // Get run number
  double theRunNumber() const;
 
private:
  bool _run3bool, _run4bool;
  int _middlerunnumber;

  TH1F *_hPhiCrackEff;
  TH1F *_hEMIDEff; // vs detector eta
  TH1F *_hPreselEff; // vs detector eta
  TH2F *_hTrkEffRun3;    // vs physics eta and Z vertex
  TH2F *_hTrkEffRun4;    // vs physics eta and Z vertex
  bool _ApplyTrackMatchEfficiency;
  bool _DoEtaHack;
  TString _EtaHackFile;
  TH1F *_hEtaHack;
  bool _ApplyLooseTrackMatchEfficiency;
  TH2F *_hTrkEff_EC; // vs physics eta and Z vertex - for EC electrons this time
  bool _simulateTrkVtxDepEC;
  TH1F *_hTrkEff_deteta; // vs detector eta 
  TH3F *_hlooseTrkEffRun3;    // vs physics eta and Z vertex
  TH3F *_hlooseTrkEffRun4;    // vs physics eta and Z vertex
  TH2F *_hlooseTrkEff_EC; // vs physics eta and Z vertex - for EC electrons this time
  bool _simulatelooseTrkVtxDepEC;
  TH1F *_hlooseTrkEff_deteta; // vs detector eta 
  TH1F *_hTrigEff_V8_10, *_hTrigEff_V11, *_hTrigEff_V12, *_hTrigEff_V13, *_hTrigEff_V14, *_hTrigEff_V15, *_hTrigEff_V16, *_hTrigEff_V16h; // vs pT 
  double _TrigFrac_ListOne, _TrigFrac_ListTwo, _TrigFrac_ListThree, _TrigFrac_ListFour, _TrigFrac_ListFive, _TrigFrac_ListSix ;
  double _TrigFrac_V8_10, _TrigFrac_V11, _TrigFrac_V12, _TrigFrac_V13, _TrigFrac_V14;   // fraction of integrated luminositywith different trigger lists
  TH1F *_RatioDataToPMCS;
  TH1F *_RatioDataToPMCSRun4;

  TSpline3 *s2ElecPt_triggerEff_0_0_run2b3, *s2ElecPt_triggerEff_0_1_run2b3, *s2ElecPt_triggerEff_1_0_run2b3;
  TSpline3 *s2ElecPt_triggerEff_0_0_run2b4, *s2ElecPt_triggerEff_0_1_run2b4, *s2ElecPt_triggerEff_1_0_run2b4;

  Bool_t _applyDPhiReweight;
  TString _DPhiReweightFile;
  TH2F* _DPhiReweightHist;
  Bool_t _applyDPhiZPtReweight;
  TString _DPhiZPtReweightFile;
  TH2F* _DPhiZPtReweightHist;
  Bool_t _applyReweightPerLumi;
  TString _DPhiZPtReweightFile0;
  TString _DPhiZPtReweightFile2;
  TString _DPhiZPtReweightFile4;
  TString _DPhiZPtReweightFile6;
  TH2F* _DPhiZPtReweightHist0;
  TH2F* _DPhiZPtReweightHist2;
  TH2F* _DPhiZPtReweightHist4;
  TH2F* _DPhiZPtReweightHist6;

  // simulate pT dependence of all selection efficiencies
  bool _simulate_pT_dependence;
  std::vector<double> _CCideff_pTphyEta_ParameterA, _CCideff_pTphyEta_ParameterB;
  std::vector<double> _CCtrkeff_pTphyEta_ParameterA, _CCtrkeff_pTphyEta_ParameterB;
  //
  std::vector<double> _CCcluseff_pTphyEta_ParameterA, _CCcluseff_pTphyEta_ParameterB;

  // trigger efficiency smearing option
  // 0: using histograms  1: using parameterizations
  int _TrigEff_Smear_Option;

 
  // trigger efficiency parameterization
  std::vector<double> _TrigEff_P0, _TrigEff_P1, _TrigEff_P2, _TrigEff_P3, _TrigEff_P4;
 std::vector<double> _TrigEff_P0_lumi02, _TrigEff_P1_lumi02, _TrigEff_P2_lumi02, _TrigEff_P3_lumi02, _TrigEff_P4_lumi02;
 std::vector<double> _TrigEff_P0_lumi24, _TrigEff_P1_lumi24, _TrigEff_P2_lumi24, _TrigEff_P3_lumi24, _TrigEff_P4_lumi24;
 std::vector<double> _TrigEff_P0_lumi46, _TrigEff_P1_lumi46, _TrigEff_P2_lumi46, _TrigEff_P3_lumi46, _TrigEff_P4_lumi46;
 std::vector<double> _TrigEff_P0_lumi6999, _TrigEff_P1_lumi6999, _TrigEff_P2_lumi6999, _TrigEff_P3_lumi6999, _TrigEff_P4_lumi6999;

  std::vector<double> _TrigEff_P0_lumi02_run3,_TrigEff_P1_lumi02_run3,_TrigEff_P2_lumi02_run3,_TrigEff_P3_lumi02_run3,_TrigEff_P4_lumi02_run3;
 std::vector<double> _TrigEff_P0_lumi24_run3,_TrigEff_P1_lumi24_run3,_TrigEff_P2_lumi24_run3,_TrigEff_P3_lumi24_run3,_TrigEff_P4_lumi24_run3;
 std::vector<double> _TrigEff_P0_lumi46_run3,_TrigEff_P1_lumi46_run3,_TrigEff_P2_lumi46_run3,_TrigEff_P3_lumi46_run3,_TrigEff_P4_lumi46_run3;
 std::vector<double> _TrigEff_P0_lumi6999_run3,_TrigEff_P1_lumi6999_run3,_TrigEff_P2_lumi6999_run3,_TrigEff_P3_lumi6999_run3,_TrigEff_P4_lumi6999_run3;


  std::vector<double> _TrigEff_P0_lumi02_run4,_TrigEff_P1_lumi02_run4,_TrigEff_P2_lumi02_run4,_TrigEff_P3_lumi02_run4,_TrigEff_P4_lumi02_run4;
 std::vector<double> _TrigEff_P0_lumi24_run4,_TrigEff_P1_lumi24_run4,_TrigEff_P2_lumi24_run4,_TrigEff_P3_lumi24_run4,_TrigEff_P4_lumi24_run4;
 std::vector<double> _TrigEff_P0_lumi46_run4,_TrigEff_P1_lumi46_run4,_TrigEff_P2_lumi46_run4,_TrigEff_P3_lumi46_run4,_TrigEff_P4_lumi46_run4;
 std::vector<double> _TrigEff_P0_lumi6999_run4,_TrigEff_P1_lumi6999_run4,_TrigEff_P2_lumi6999_run4,_TrigEff_P3_lumi6999_run4,_TrigEff_P4_lumi6999_run4;

  // trigger efficiency parameterization for option 5
  std::vector<double> _TrigEff_P0_lumi03_run3,_TrigEff_P1_lumi03_run3,_TrigEff_P2_lumi03_run3,_TrigEff_P3_lumi03_run3,_TrigEff_P4_lumi03_run3,_TrigEff_P5_lumi03_run3;
 std::vector<double> _TrigEff_P0_lumi3999_run3,_TrigEff_P1_lumi3999_run3,_TrigEff_P2_lumi3999_run3,_TrigEff_P3_lumi3999_run3,_TrigEff_P4_lumi3999_run3,_TrigEff_P5_lumi3999_run3;

  std::vector<double> _TrigEff_P0_lumi03_run4,_TrigEff_P1_lumi03_run4,_TrigEff_P2_lumi03_run4,_TrigEff_P3_lumi03_run4,_TrigEff_P4_lumi03_run4,_TrigEff_P5_lumi03_run4;
 std::vector<double> _TrigEff_P0_lumi3999_run4,_TrigEff_P1_lumi3999_run4,_TrigEff_P2_lumi3999_run4,_TrigEff_P3_lumi3999_run4,_TrigEff_P4_lumi3999_run4,_TrigEff_P5_lumi3999_run4;



  // use the following switch to control whether you want to study systematic uncertainty 
  // due to trigger efficiency (only when TrigEff_Smear_Option == 1)
  bool _Study_TrigEff_Systematics;

  // apply loose track match to presel EMOBJS
  bool _applypreseltrkmatch;

  // trigger efficiency uncertainty
  std::vector<double> _TrigEff_P0_Uncertainty, _TrigEff_P1_Uncertainty, _TrigEff_P2_Uncertainty, _TrigEff_P3_Uncertainty, _TrigEff_P4_Uncertainty;

  // for corrections to pT-dependent efficiencies, determined using Tag&Probe
  bool _includeECtag;
  //
  bool _apply_HMxeff_ratio;
  bool _apply_TRKeff_ratio;
  int _eff_ratios_function;
  //
  std::vector<double> _CCtrkeffratio_pTphyEta_ParameterA, _CCtrkeffratio_pTphyEta_ParameterB, _CCtrkeffratio_pTphyEta_ParameterC, _CCtrkeffratio_pTphyEta_ParameterD, _CCtrkeffratio_pTphyEta_ParameterE;
  std::vector<double> _CChmxeffratio_pTphyEta_ParameterA, _CChmxeffratio_pTphyEta_ParameterB, _CChmxeffratio_pTphyEta_ParameterC, _CChmxeffratio_pTphyEta_ParameterD, _CChmxeffratio_pTphyEta_ParameterE;

  // pointer to histo_files to write histograms
  hist_files *_histos;
  bool _makeCheckSmearingPlots;
  std::map<int, std::vector<std::string> > _trigger_map;

 double _runNumber;

  // parameters for AddOnEff

  // for Wenu
  bool _ApplyAddOnEff_Wen;

  bool _AddOnEff_Wen_TEPT_On;
  std::vector<double> _AddOnEff_Wen_TEPT_Pars;

  bool _AddOnEff_Wen_DetEta_On;
  TH1D* _AddOnEff_Wen_DetEta_Pars;

  bool _AddOnEff_Wen_SET_On; 
  std::vector<double> _AddOnEff_Wen_SET_Pars;

  // for Zee
  bool _ApplyAddOnEff_Zee;

  bool _AddOnEff_Zee_TEPT_On;
  std::vector<double> _AddOnEff_Zee_TEPT_Pars;

  bool _AddOnEff_Zee_DetEta_On;
  TH1D* _AddOnEff_Zee_DetEta_Pars;

  bool _AddOnEff_Zee_CorrelTEPT_On;
  std::vector<double>_AddOnEff_Zee_CorrelTEPT_DontKnowPars;
  std::vector<double>_AddOnEff_Zee_CorrelTEPT_OnePassPars;
  std::vector<double>_AddOnEff_Zee_CorrelTEPT_OneNotPassPars;
  
  bool _AddOnEff_Zee_SET_On;
  std::vector<double> _AddOnEff_Zee_SET_Pars;
  

};
inline void EfficiencySmear::SetRunNumber(double runnumber) {_runNumber = runnumber;}
#endif
