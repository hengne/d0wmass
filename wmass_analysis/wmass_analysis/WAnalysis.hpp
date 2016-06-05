#ifndef WANALYSIS_HPP
#define WANALYSIS_HPP

#include "cafe/Processor.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/CAFWCand.hpp"
#include "wmass_blinding_util/BlindingManagerData.hpp"
#include "wmass_util/EMClusterPosCorr.hpp"
#include "TRandom3.h"
#include <fstream>
#include <iostream>
#include <map>

typedef std::pair<int, int> TwoInteger;   // used to define runNo and evtNo
  
class WAnalysis : public cafe::Processor {
  
 public:
  WAnalysis(const char *name);
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();
  void EOverPStudies(const CAFEMObj* emobj, int solpol);
  void MCStudies(cafe::Event& event);
  void uParaEfficiencyStudies(cafe::Event& event, CAFWCand& wcand);
  void makeRecoilFile(cafe::Event& event, std::vector<CAFEMObj*> emobjs, double instlumi, int type, double scalarEt);
  void makeEfficStudyFile(cafe::Event& event, vector<CAFEMObj*> emobjs, std::vector<TMBMCpart *> raw_emobjs_gen, double instlumi, int type, double scalarEt);
  void filltree3(Int_t type, Float_t vz, CAFWCand& zcand, CAFMet& met, Float_t set,  Float_t lumi, bool trigger, Int_t cut,  Int_t runNum, Int_t eventNum);

  ClassDef(WAnalysis, 0);
  
 private:

  // FSR photon information for recoil file
  double HighestPhotonPt;
  double SecondHighestPhotonPt;

  bool isPhot;

  // write out possible Wenu candidate run number, event number to a text file
  std::fstream *_wenu_out_txt;
    
  // debug level
  int _debugLevel;

  // study uparallel efficiency
  bool _uParaEffStudy;

  // electron detector eta cuts
  float _DetEtaCC, _DetEtaEC1, _DetEtaEC2;

  // W boson transverse mass, Ut cut
  float _WMetCut, _WUtCut_lower, _WMtCut1, _WMtCut2, _WUtCut;

  // if we want to fill histograms for W events that are really from Z
  bool _dump_W_ZeeBkg;

  // switches for ASCII printouts that can be used for more detailed studies (outside the 
  // framework of wmass_analysis) of electron ID efficiency and electron energy resonse 
  bool _dump_LumiEff;
  bool _dump_Eresponse;

  // study E/p
  bool _StudyEOverP;

  //include singularity variable in plots
  bool _doSingVariableStudy;
  double _wmass_defaultSV;

  // MC studies
  bool _MCStudy;
  bool _MakeOverlayEventList;

  // ZB event studies
  Bool_t _doZBevent;
  Float_t _ZBSET;

  // write out efficiency analysis file
  bool _makeEfficStudyFile;
  std::fstream* _effic_study_txt;
  
  // study scalar Et (only works for full MC)
  bool _ScalarEtStudy;
  std::map<TwoInteger,double> _scalarEtMaps;   // scalar Et for a given ZB event (runNo, evtNo)

  // Z -> ee background study
  bool _ZEEbkgStudy;
  bool _ZEEbkgStudyTruth;

  // do raw cells for recoil
  bool _dorawCellsRecoil;
  bool _useConsistentMET;

  // smearing parameters
  double _A, _B, _C, _CNonLinear, _eta_Resolution, _phi_Resolution;
  double _alpha, _beta, _sampling, _constant, _noise;

  // random number generator
  TRandom3 *_random;
  
  // histograms
  hist_files _histos;

  // make recoil file for Matt's method
  bool _makeRecoilFile, _useUnCorrRecoil, _useConstantCorrRecoil, _useParameterizedCorrRecoil, _dumpElecInfo, _useParamConeCorrRecoil ;
  TH1F* _UparaCorr_CC_Hist;

 //phimod fiducial cut based on trk     
  bool _TrkPhiFiducial;

  // require neutrino in CC or EC to study uparallel bias measured from Zee events
  bool _Nu_CC, _Nu_EC;
  
  // write out electron and recoil information to a text file
  std::fstream* _recoil_file_txt;

  // write out file for background studies
  std::fstream* _bkg_file_txt;

  // event counters
  int _events_fail_trigger_requirements;

  // blinding manager
  BlindingManagerData _BM;

  // EM cluster position correction
  EMClusterPosCorr *_emclusposcorr;

  //require SMT hit for track match	
  bool _require_smt;

  // vary cut values and check the consistency of W mass
  bool _consistency_check, _invert_cut;
  TString _cut_under_study;
  int _runNo_lowcut, _runNo_highcut, _tickNo_lowcut, _tickNo_highcut;
  double _InstLumi_lowcut, _InstLumi_highcut, _ScalarEt_lowcut, _ScalarEt_highcut, _UPara_lowcut, _UPara_highcut, _ElecEta_cut, _ElecDetEta_lowcut, _ElecDetEta_highcut, _ElecPhiMod_cut, _ElecPt_lowcut, _ElecPt_highcut, _ElecPhi_lowcut, _ElecPhi_highcut, _RecoilPhi_lowcut, _RecoilPhi_highcut;
  bool _DropTriggerObjectMatchRequirement;

  bool _fillwtree;
  TTree *_tree3;

  Int_t tree3_run;  				
  Int_t tree3_evt;  				
  Int_t tree3_trig; 			
  Float_t tree3_lumi;			  

  Int_t   tree3_type;
  Int_t   tree3_cut;
  Float_t tree3_mt;			  
  Float_t tree3_ptw;			  
  Float_t tree3_set;			  
  Float_t tree3_met;			  
  Float_t tree3_wut;			  
  Float_t tree3_metphi; 		  
  Float_t tree3_wutphi; 		  
  Float_t tree3_metdelphi;     
  Float_t tree3_wutdelphi;     
  Float_t tree3_vtxz;				
  Float_t tree3_e;				   
  Float_t tree3_pt;  			  
  Float_t tree3_upara;		  
  Float_t tree3_caloriphi;  
  Float_t tree3_trkphidca;  
  Float_t tree3_trkphiem3;  
  Float_t tree3_eta;  
  Float_t tree3_deteta;  
  Float_t tree3_hm7; 			 
  Float_t tree3_hm8; 			 
  Float_t tree3_iso; 
  Float_t tree3_emf;
  Float_t tree3_phifidcal;
  Float_t tree3_phifidtrk;
  Int_t tree3_cc;  
  Int_t tree3_ccphifidcal;  
  Int_t tree3_ccphifidtrk;  
  Int_t tree3_trkspat;	   
  Int_t tree3_trkgood;
  Float_t tree3_trkprob;  
  Int_t tree3_trknsmt;  
  Float_t tree3_trkpt;  

  Int_t tree3_id;
  Int_t tree3_etafid;
  Int_t tree3_ccetafid;
  Int_t tree3_fid;
  Int_t tree3_ccfid;  


 
  
  Int_t entry;
  Int_t run;
  Int_t evt;
  Float_t lumi;
  Float_t vtxz;
  Float_t evtmet;
  Float_t evtset;
  Float_t wcandut;
  Float_t wcandmt;
  Float_t wcandupara;
  Float_t wcandutphi;

  Int_t e_n;
  Float_t e_pt;
  Float_t e_e;
  Float_t e_eta;
  Float_t e_deta;
  Float_t e_phi;
  Float_t e_charge;
  Int_t e_goodspmtch;
  Int_t e_id;
  Float_t e_phimod;

  Int_t j_n;
  Int_t j_n90; 
  Float_t j_pt; 
  Float_t j_e; 
  Float_t j_emf; 
  Float_t j_chf; 
  Float_t j_hcr; 
  Int_t j_trks;
  Float_t j_phi; 
  Float_t j_eta; 
  Float_t j_deta;

  Int_t t_n;
  Float_t t_pt;
  Float_t t_e;
  Float_t t_eta;
  Float_t t_deta;
  Float_t t_phi;
  Int_t t_charge;

  Int_t t_nsmt;
  Float_t t_z;//at dca
  Float_t t_chisq;


  Float_t ej_deltaphi;
  Float_t ej_m;
  Float_t et_deltaphi;
  Float_t et_m;


  TTree *et;


  TFile * _RecoilFile;
  TTree * _RecoilTree;

  struct recoil_struct {
    double pTZ_gen_x , pTZ_gen_y;
    double pTZ_smear_x , pTZ_smear_y;
    double recoil_x , recoil_y;
    double recoil_uncorr_x , recoil_uncorr_y;
    double recoil_constcorr_x , recoil_constcorr_y;
    double recoil_paramcorr_x , recoil_paramcorr_y;
    double recoil_paramconecorr_x , recoil_paramconecorr_y;
    double scalarET;
    double upara_e1 , upara_e2;
    double pT_e1 , pT_e2;
    double eta_e1 , eta_e2;
    int runno;
    double lumi;
    double MZ;
    int type;
    double eventweight;
    int isFSR;
    double photpT1;
    double photpT2;
  } recoil_data;
};

#endif
