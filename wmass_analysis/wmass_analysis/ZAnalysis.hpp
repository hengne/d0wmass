#ifndef ZANALYSIS_HPP
#define ZANALYSIS_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "wmass_util/CAFZCand.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"
#include "wmass_util/evtReweightManager.hpp"
#include "wmass_util/CAFRatioMethod.hpp"
#include "wmass_util/EMClusterPosCorr.hpp"

#include "TRandom3.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <TVector2.h>

class ZAnalysis : public cafe::Processor {
public:
  ZAnalysis(const char *name);
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();
  void MCStudies(cafe::Event& event, std::vector<CAFEMObj*>& emobjs, CAFZCand& zcand);
  void makeRecoilFile(cafe::Event& event, std::vector<CAFEMObj*> emobjs, double instlumi, int type, double scalarEt);
  void makeEfficStudyFile(cafe::Event& event, vector<CAFEMObj*> emobjs, std::vector<TMBMCpart *> raw_emobjs_gen, double instlumi, int type, double scalarEt);

  void PhiCrackEffStudy(cafe::Event& event, std::vector<CAFEMObj*> emobjs);
  void PhiCrackEffStudyUsingTracks(cafe::Event& event, std::vector<CAFEMObj*> emobjs);
  void uParaEfficiencyStudies(cafe::Event& event, std::vector<CAFEMObj*> emobjs, TVector2 recoil_vect, double instlumi, double zvtx, CAFZCand& zcand);
  void trkMatchEfficiencyStudies(cafe::Event& event, std::vector<CAFEMObj*> emobjs, std::vector<CAFEMObj*> probe_emobjs, 
				 CAFMet &rawmet, float vtx[3], bool *pass_trigger);
  void trueTrkMatchEfficiencyStudies(cafe::Event& event, std::vector<CAFEMObj*> probe_emobjs, 
				     CAFMet &rawmet, float vtx[3]);

  void EMFStudy(cafe::Event& event, CAFZCand& zcand);
  void EtFlowStudy(cafe::Event& event,
		   CAFZCand& zcand,
		   vector<CAFEMObj*> emobjs,
		   float vtx[3], double ScalarEt_noEM, double ScalarEt_Evt );
  void clear_ems();
  bool get_ems(std::vector<CAFEMObj*> EMs, int polarity);
  bool filltree2(CAFZCand& zcand, Double_t recoilPt, Double_t zScalarEt, Double_t instlumi, Int_t runNum, Int_t eventNum,Int_t ZBrunNum, Int_t ZBeventNum );
  void filltree3(Int_t type, Float_t vz, CAFZCand& zcand, CAFMet& met, Float_t set, Float_t lumi, int trig_flag, Int_t cut, Int_t runNum, Int_t eventNum);


  
  ClassDef(ZAnalysis, 1);

 private:

  // photon pT variables used for making a recoil file
  double HighestPhotonPt;
  double SecondHighestPhotonPt;
  bool isPhot;

  // write out possible Zee candidate run number, event number to a text file
  std::fstream *_zee_out_txt;

  // debug level
  int _debugLevel;
  
  // electron eta cuts
  float _DetEtaCC, _DetEtaEC1, _DetEtaEC2;

  // number of spatial track matching requirement
  int _NumZSpatialTrk;
 
  //require SMT hit for track match     
  bool _require_smt;

 //phimod fiducial cut based on trk     
  bool _TrkPhiFiducial;
 
  // Z boson mass, pT cuts
  float _ZMassCut1, _ZMassCut2, _ZUtCut, _ZUtCut_lower, _ZPtCut, _ZPtCut_lower, _ZPhiCut, _ZPhiCut_lower;
  float _ZScalarEtCut, _ZScalarEtCut_lower;
  double _ElecPtCut1_lo, _ElecPtCut2_lo, _ElecPtCut1_hi, _ElecPtCut2_hi;

  // sampling terms etc
  double _alpha, _beta, _sampling, _constant, _noise, _eta_Resolution, _phi_Resolution;
  double _sampling1, _sampling2, _samplingexp0, _samplingexp1, _samplingexp2;
  // random number generator
  TRandom3 *_random;

  //EtaImbalance cuts in pt bins
  bool _etaImbalance_perbincuts;
  std::vector<float> _EtaImbalanceCutLow;
  std::vector<float> _EtaImbalanceCutHigh;
  bool _InvertetaImbalance_perbincuts;
  
  // do MC studies
  bool _MCStudy;
  bool _MakeOverlayEventList;
  bool _smearingStudy;

  // ZB event studies
  Bool_t _doZBevent;
  Float_t _ZBSET;

  // write out efficiency analysis file
  bool _makeEfficStudyFile;
  std::fstream* _effic_study_txt;
  
  //Ratio Method
  bool _doRatioMethod;
  CAFRatioMethod *_ratiomethod;
  
  // do raw cells for recoil
  bool _dorawCellsRecoil;
  bool _useConsistentMET;

  // study Phi crack efficiency
  bool _PhiCrackEffStudy;

  // study uparallel efficiency
  bool _uParaEffStudy;
  
  // study track match efficiency
  bool _trkMatchEffStudy;
  bool _fiducialForwardElectron;

  // EMF study
  bool _performEMFstudy;
  bool _EMFstudySimulateRelGains;	 
  float _EMFstudyRelGainEM1;	 
  float _EMFstudyRelGainEM2;	 
  float _EMFstudyRelGainEM3;	 
  float _EMFstudyRelGainEM4;	 
  float _EMFstudyRelGainFH1;	 
  int _EMFstudyNLumiBins;	 
  std::vector<float> _EMFstudyLumiBinStarts;  
  hist_files _emf_histos;

  // switches for ASCII printouts that can be used for more detailed studies (outside the
  // framework of wmass_analysis) of electron ID efficiency and electron energy resonse
  bool _dump_LumiEff;
  bool _dump_Eresponse;

  // histograms
  hist_files _histos;
  hist_files _mc_histos;

  // make recoil file for Matt's method
  bool _makeRecoilFile, _useUnCorrRecoil, _useConstantCorrRecoil, _useParameterizedCorrRecoil, _dumpElecInfo,  _useParamConeCorrRecoil;
  TH1F* _UparaCorr_CC_Hist;

  // write out electron and recoil information to a text file
  std::fstream* _recoil_file_txt;

  cafe::Variables _global_vars;

  // event counters
  int _events_fail_trigger_requirements;

  // study QCD background
  bool _QCDBkgStudy;

  // use pythia full MC events to study SM backgrounds
  // Need to do event reweighting to reflect efficiency differences between data and full MC
  // energy smearing not needed for the full MC events generated on the farm
  bool _SMBkgStudy;
  evtReweightManager *_evtReweightManager;

  // write out information into a tree
  bool _createRootTree;
  TFile *_roottupleFile;
  TTree *_tree;

  Int_t _nem;
  Float_t em_e[2];
  Float_t em_rawe[2];
  Float_t em_pt[2];
  Float_t em_eta[2];
  Float_t em_deteta[2];
  Float_t em_phi[2];
  Float_t em_detphi[2];
  Float_t em_trkpt[2];
  Float_t em_trkphi[2];
  Float_t em_trkphiEM3[2];
  Float_t em_hm7[2];
  Float_t em_hm8[2];


  // write out information into a different  tree
  bool _createRootTree2;
  TFile *_roottupleFile2;
  TTree *_tree2;

  Int_t tree2_runnum;
  Int_t tree2_eventnum;
  Int_t tree2_ZBrunnum;
  Int_t tree2_ZBeventnum;
  Float_t tree2_Mz;
  Float_t tree2_Ptz;
  Float_t tree2_lumi;
  Float_t tree2_set;
  Float_t tree2_ZUt;
  Float_t tree2em_e[2];
  Float_t tree2em_pt[2];
  Float_t tree2em_eta[2];
  Float_t tree2em_phi[2];
  Float_t tree2em_deteta[2];
  Float_t tree2em_detphi[2];
  Float_t tree2em_upara[2];
  Float_t tree2em_trk_prob[2];
  Int_t tree2em_nsmt[2];
  Float_t tree2em_trk_pt[2];
  Float_t tree2_weight;

  bool _fillztree;
  TTree *_tree3;

  Int_t tree3_run;  				
  Int_t tree3_evt;  				
  Int_t tree3_trigflg;
  Int_t   tree3_passtrig[2];
  Int_t   tree3_passtrig5[2];
  Int_t   tree3_passtrig6[2];
  Int_t   tree3_passtrig7[2];	
  Float_t tree3_lumi;			 
  Int_t   tree3_passl1[2], tree3_passl2em22[2], tree3_passl2em25[2], tree3_passl2iso[2], tree3_passl2lh[2], tree3_passl3sht25[2], tree3_passl3sht27[2];
  Double_t   tree3_l1Et[2], tree3_l2em22Et[2], tree3_l2em25Et[2], tree3_l2isoEt[2], tree3_l2lhEt[2], tree3_l3sht25Et[2], tree3_l3sht27Et[2]; 

  Int_t  tree3_id[2];
  Int_t    tree3_etafid[2];
  Int_t    tree3_ccetafid[2];
  Int_t    tree3_fid[2];
  Int_t    tree3_ccfid[2];

  Int_t   tree3_type;
  Int_t   tree3_cut;
  Float_t tree3_mee;			  
  Float_t tree3_ptee;			  
  Float_t tree3_set;			  
  Float_t tree3_met;			  
  Float_t tree3_zut;			  
  Float_t tree3_zphi;			  
  Float_t tree3_metphi; 		  
  Float_t tree3_zutphi; 		  
  Float_t tree3_metdelphi;     
  Float_t tree3_zutdelphi;     
  Float_t tree3_vtxz;	
  Float_t tree3_vtxtruez;
  Float_t tree3_e[2];				   
  Float_t tree3_pt[2];  			  
  Float_t tree3_chg[2];  			  
  Float_t tree3_upara[2];		  
  Float_t tree3_caloriphi[2];  
  Float_t tree3_trkphidca[2];  
  Float_t tree3_trkphiem3[2];  
  Float_t tree3_eta[2];  
  Float_t tree3_deteta[2];  
  Float_t tree3_hm7[2]; 			 
  Float_t tree3_hm8[2]; 			 
  Float_t tree3_emf[2];
  Float_t tree3_iso[2]; 
  Int_t tree3_cc[2];  
  Int_t tree3_ccphifidcal[2];  
  Int_t tree3_ccphifidtrk[2];  
  Int_t tree3_phifidcal[2];
  Int_t tree3_phifidtrk[2];
  Int_t tree3_trkspat[2];	   
  Int_t tree3_trkgood[2];
  Float_t tree3_trkprob[2];  
  Int_t tree3_trknsmt[2];  
  Float_t tree3_trkpt[2];  	   
  
  
  // EM cluster position correction
  EMClusterPosCorr *_emclusposcorr;

  // vary cut values and check the consistency of W mass
  bool _consistency_check, _invert_cut;
  TString _cut_under_study;
  int _runNo_lowcut, _runNo_highcut, _tickNo_lowcut, _tickNo_highcut;
  double _InstLumi_lowcut, _InstLumi_highcut, _ScalarEt_lowcut, _ScalarEt_highcut, _UPara_lowcut, _UPara_highcut, _ElecEta_cut, _ElecDetEta_lowcut, _ElecDetEta_highcut, _ElecPhiMod_cut, _ElecPt_lowcut, _ElecPt_highcut, _ElecPhi_lowcut, _ElecPhi_highcut, _RecoilPhi_lowcut, _RecoilPhi_highcut , _ZPTee_lowcut, _ZPTee_highcut;
  int _DetEtaCateg_cut;
  bool _DropTriggerObjectMatchRequirement;

  // hadronic recoil ET flow studies 
  //  
  bool _dumpRecoilInfo;              // dump measured hadronic recoil and generated Z info to an ASCII file
  bool _do_RecoilEtFlow_studies;     // perform ET flow studies (it will slow down the code!)
  float _RecoilEtFlow_studies_TowCut;// max. tower ET taken into account in ET flow studies
  std::fstream *_zee_out_recoil_txt; // write out: measured recoil and generated Z to a text file
  int   _ElecLoose_nMin;             // min. number of the RECO Loose electrons 
  float _ElecLoose_EtaMax;           // max. RECO detector |eta| of a Loose electron 
  float _ElecLoose_PtMin;            // min. RECO pT of a Loose electron
  int   _ElecTight_nMin;             // min. number of the RECO Tight electrons       
  float _ElecTight_EtaMax;           // max. RECO detector |eta| of a Tight electron 
  float _ElecTight_PtMin;            // min. RECO pT of a Tight electron
  map<int,double> _RelResponse_scale;// for rescaling average ET per PHI tower
  hist_files _EtFlow_histos;

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
