#include "cafe/Config.hpp"
#include "cafe/Event.hpp"

#include "wmass_analysis/WAnalysis.hpp"
#include "wmass_analysis/histograms.hpp"
#include "TLorentzVector.h"
#include "wmass_util/WZ_Utils.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/CAFTrack.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "TROOT.h"
#include <TFile.h>

#include <iostream>
#include <fstream>

using namespace std;
using namespace cafe;

//setup material simulation
const double radiation_length = 0.010;
const int bin_radiation_length = 10;
const double y_min = 0.0005;
const int bin_y = 50;
const double k = 0.03;



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


WAnalysis::WAnalysis(const char *name)
  : Processor(name)
{


   et = new TTree("et","electron-track tree");

   et->Branch("entry", &entry, "entry/I");
   et->Branch("run", &run, "run/I");
   et->Branch("evt", &evt, "evt/I");
   et->Branch("lumi", &lumi, "lumi/F");
   et->Branch("vtxz", &vtxz, "vtxz/F");
   et->Branch("evtmet", &evtmet, "evtmet/F");
   et->Branch("evtset", &evtset, "evtset/F");

   et->Branch("wcandut", &wcandut, "wcandut/F");
   et->Branch("wcandupara", &wcandupara, "wcandupara/F");
   et->Branch("wcandutphi", &wcandutphi, "wcandutphi/F");

   et->Branch("wcandmt", &wcandmt, "wcandmt/F");

   et->Branch("t_pt",    &t_pt,    "t_pt/F");
   et->Branch("t_e",     &t_e,     "t_e/F");
   et->Branch("t_eta",   &t_eta,   "t_eta/F");
   et->Branch("t_deta",   &t_deta,   "t_deta/F");
   et->Branch("t_phi",   &t_phi,   "t_phi/F");
   et->Branch("t_charge", &t_charge, "t_charge/I");


   et->Branch("e_pt",    &e_pt,    "e_pt/F");
   et->Branch("e_e",     &e_e,     "e_e/F");
   et->Branch("e_eta",   &e_eta,   "e_eta/F");
   et->Branch("e_deta",   &e_deta,   "e_deta/F");
   et->Branch("e_phi",   &e_phi,   "e_phi/F");
   et->Branch("e_phimod",   &e_phimod,   "e_phimod/F");
   et->Branch("e_charge", &e_charge, "e_charge/F");
   et->Branch("e_goodspmtch", &e_goodspmtch, "e_goodspmtch/I");
   et->Branch("e_id", &e_id, "e_id/I");

   et->Branch("e_n", &e_n, "e_n/I");
   et->Branch("t_n", &t_n, "t_n/I");
   et->Branch("j_n", &j_n, "j_n/I");

   et->Branch("j_pt",    &j_pt,    "j_pt/F");
   et->Branch("j_e",     &j_e,     "j_e/F");
   et->Branch("j_eta",   &j_eta,   "j_eta/F");
   et->Branch("j_deta",   &j_deta,   "j_deta/F");
   et->Branch("j_phi",   &j_phi,   "j_phi/F");

   et->Branch("j_trks", &j_trks, "j_trks/I");
   et->Branch("j_n90", &j_n90, "j_n90/I");

   et->Branch("j_emf",   &j_emf,   "j_emf/F");
   et->Branch("j_chf",   &j_chf,   "j_chf/F");
   et->Branch("j_hcr",   &j_hcr,   "j_hcr/F");


   et->Branch("t_nsmt", &t_nsmt, "t_nsmt/I");
   et->Branch("t_z", &t_z	 , "t_z/F");
   et->Branch("t_chisq", &t_chisq, "t_chisq/F");

   et->Branch("et_m", &et_m	   , "et_m/F");
   et->Branch("et_deltaphi", &et_deltaphi, "et_deltaphi/F");
   et->Branch("ej_m", &ej_m	   , "ej_m/F");
   et->Branch("ej_deltaphi", &ej_deltaphi, "ej_deltaphi/F");

   entry=0;





  Config config(name);
  
  // debug level
  _debugLevel = config.get("debugLevel", 0);

  // initialize EM cluster position correction
  _emclusposcorr = new EMClusterPosCorr(config);
  
  // require smt hit for track match
  _require_smt = config.get("RequireSMT", kTRUE);
  
  // study uparallel efficiency
  _uParaEffStudy = config.get("uParaEffStudy", false);
  _Nu_CC = config.get("Nu_CC", false);
  _Nu_EC = config.get("Nu_EC", false);

  // electron detector eta cuts
  _DetEtaCC = config.get("DetEtaCC", 1.1);
  _DetEtaEC1 = config.get("DetEtaEC1", 1.5);
  _DetEtaEC2 = config.get("DetEtaEC2", 2.3);
       
  // W Mt and pT cuts
  _WMetCut = config.get("WMetCut", 25.);
  _WMtCut1 = config.get("WMtCut1", 50.);
  _WMtCut2 = config.get("WMtCut2", 200.);
  _WUtCut = config.get("WUtCut", 999.);
  _WUtCut_lower = config.get("WUtCut_lower", 999.);

  // do MC study
  _MCStudy = config.get("MCStudy", false);
  _MakeOverlayEventList = config.get("MakeOverlayEventList", false);
  std::cout << " _MakeOverlayEventList " << "   " << _MakeOverlayEventList << std::endl;
  
  // study scalar Et (only works for full MC since need the overlay ZB event)
  // the location of ZB library is currently hardcoded as
  // need to copy file from /rooms/wmass/MC/MBZBLibrary/Library_Unsup_zerobias_p17_10_00MC_set1_RemoveBadEventsDQProcessor_Met20_FarmAdjustMissingAndTripple_KillEvtDQ_KillFlagsFromZB.txt to the current directory
  _ScalarEtStudy = config.get("ScalarEtStudy", false);

  // create scalar Et map (runNo, evtNo, scalarEt)
  _scalarEtMaps.clear();
  if(_MCStudy && _ScalarEtStudy) {
    cout<<"Need to read file Library_Unsup_zerobias_p17_10_00MC_set1_RemoveBadEventsDQProcessor_Met20_FarmAdjustMissingAndTripple_KillEvtDQ_KillFlagsFromZB.txt from the current directory, make sure it is there !!!"<<endl;

    // read ZB library file
    ifstream inFile1("Library_Unsup_zerobias_p17_10_00MC_set1_RemoveBadEventsDQProcessor_Met20_FarmAdjustMissingAndTripple_KillEvtDQ_KillFlagsFromZB.txt", ios::in);
    
    int liblines1 = 0;
    while(!inFile1.eof()) {
      int runNo = 0, evtNo = 0, nVtx = 0;
      double instlumi = 0., scalarEt = 0., metx = 0., mety = 0.;
      inFile1 >> runNo >> evtNo >> instlumi >> nVtx >> scalarEt >> metx >> mety;
      if(inFile1.eof()) break;
      
      TwoInteger RunEvtIndex(runNo, evtNo);
      _scalarEtMaps.insert(pair<TwoInteger, double>(RunEvtIndex, scalarEt));
      
      liblines1++;
    }
    cout << "Read " << liblines1 << " lines from zerobias file" << endl;
    inFile1.close();
  }

  // dump W events that really come from Z
  _dump_W_ZeeBkg = config.get("dump_W_ZeeBkg", false);

  // Z -> ee background study
  _ZEEbkgStudy = config.get("ZEEbkgStudy", false);
  _ZEEbkgStudyTruth = config.get("ZEEbkgStudyTruth", false);

  _dorawCellsRecoil = config.get("dorawCellsRecoil", true);
  _useConsistentMET = config.get("useConsistentMET", true);

  // MC Smearing parameters
  _A = config.get("A_Resolution", 0.);
  _B = config.get("B_Resolution", 0.);
  _C = config.get("C_Scale", 1.);
  _CNonLinear = config.get("C_Scale_NonLinear", 0.);
  _eta_Resolution = config.get("eta_Resolution", 0.);
  _phi_Resolution = config.get("phi_Resolution", 0.);

  _alpha = config.get("Scale", 1.);
  _beta = config.get("Offset", 0.);
  _sampling = config.get("Sampling", 0.21);
  _noise = config.get("Noise", 0.29);
  _constant = config.get("Constant", 0.);

  // make recoil file for Matt's method
  _makeRecoilFile = config.get("makeRecoilFile", false);
  if(_makeRecoilFile) {
    // make recoil file for Matt's studeis, do not apply W uT cut
    _WUtCut = 100000.;
    _useUnCorrRecoil = config.get("useUnCorrRecoil", false);
    _useConstantCorrRecoil = config.get("useConstantCorrRecoil", false);
    _useParameterizedCorrRecoil = config.get("useParameterizedCorrRecoil", false);
    _useParamConeCorrRecoil = config.get("useParamConeCorrRecoil", false);
    _dumpElecInfo = config.get("dumpElecInfo", false);
    
    _recoil_file_txt = new std::fstream("recoil_file_wenu.txt",std::ios::out);
    
    gROOT->ProcessLine(TString(".x UParaCorrPerTower.C"));
    _UparaCorr_CC_Hist = (TH1F *)gROOT->FindObject("UParaCorrPerTower");
  }

  // make text file for efficiency studies
  _makeEfficStudyFile = config.get("makeEfficStudyFile", false);
  if(_makeEfficStudyFile){
    _WUtCut = 100000.;
    _effic_study_txt = new std::fstream("efficiencystudy_file_wenu.txt",std::ios::out);
  }

  // File for background studies
  if (_ZEEbkgStudy) {
    _bkg_file_txt = new std::fstream("bkg_file_wenu.txt",std::ios::out);
  }

  // study E/p
  _StudyEOverP = config.get("StudyEOverP", false);

  // vary cut values and check the consistency of W mass
  _consistency_check = config.get("consistency_check", false);
  _invert_cut = config.get("invert_cut", false);
  _cut_under_study = config.get("cut_under_study", "");
  _runNo_cut = config.get("runNo_cut", 0);
  _InstLumi_lowcut  = config.get("InstLumi_lowcut", 100.);
  _InstLumi_highcut = config.get("InstLumi_highcut", 100.);
//  _ScalarEt_cut = config.get("ScalarEt_cut", 0.);
  _UPara_lowcut = config.get("UPara_lowcut", 0.);
  _UPara_highcut = config.get("UPara_highcut", 0.);
  _ElecEta_cut = config.get("ElecEta_cut", 0.);
  _ElecDetEta_cut = config.get("ElecDetEta_cut", 0.);
  _ElecPhiMod_cut = config.get("ElecPhiMod_cut", 0.);
  _ElecPt_lowcut = config.get("ElecPt_lowcut", 0.);
  _ElecPt_highcut = config.get("ElecPt_highcut", 0.);

  // random number generator
  _random = new TRandom3(0);
  gRandom = _random;
  
  // add histograms
  _histos.add(WCand_Hist);
  _histos.add(WCand_Hist_Profile);
  _histos.add(WCand_Hist_2D);
  _histos.add(WCand_Hist_3D);

  // for CC/EC and all regions, without track matching requirement
  _histos.clone("WCandVtx", 2);
  _histos.clone("WCandPhi", 2);
  _histos.clone("WCandInstLumi", 2);
  _histos.clone("WCandScalarEt_V_Lumi",2);
  _histos.clone("WCandScalarEt_V_Lumi2D",2);
  _histos.clone("WCandScalarEt", 2);
  _histos.clone("WCandSqrtScalarEt", 2);
  _histos.clone("WCandElecPt", 2);
  _histos.clone("WCandElecPx", 2);
  _histos.clone("WCandElecPy", 2);
  _histos.clone("WCandElecTrkPt", 2);
  _histos.clone("WCandMet", 2);
  _histos.clone("WCandMetx", 2);
  _histos.clone("WCandMety", 2);
  _histos.clone("WCandMetPhi", 2);
  _histos.clone("WCandMt", 2);
  _histos.clone("WCandPt", 2);
  _histos.clone("WCandElecEta", 2);
  _histos.clone("WCandElecDetEta", 2);
  _histos.clone("WCandElecPhi", 2);
  _histos.clone("WCandElecDetPhi", 2);
  _histos.clone("WCandElecPhiTrkAtDCA", 2);
  _histos.clone("WCandElecPhiTrkAtEM3", 2);
  _histos.clone("WCandElecDetPhiCALO", 2);
  _histos.clone("WCandUPara", 2);
  _histos.clone("WCandUPerp", 2);
  _histos.clone("WCandUt", 2);
  _histos.clone("WCandElecRecPhi", 2);
  _histos.clone("WCandElecMetPhi", 2);
  _histos.clone("WCandElecPtUpara1", 2);
  _histos.clone("WCandElecPtUpara2", 2);
  _histos.clone("WCandMetUpara1", 2);
  _histos.clone("WCandMetUpara2", 2);
  _histos.clone("WCandMtUpara1", 2);
  _histos.clone("WCandMtUpara2", 2);
  _histos.clone("WCandWPtUpara1", 2);
  _histos.clone("WCandWPtUpara2", 2);
  _histos.clone("WCandRecoilPt", 2);
  _histos.clone("WCandRecoilPx", 2);
  _histos.clone("WCandRecoilPy", 2);
  _histos.clone("WCandRecoilPhi", 2);
  _histos.clone("WCandElecMetDeltaPhi", 2);
  _histos.clone("WCandElecRecoilDeltaPhi", 2);
  _histos.clone("WCandMetRecoilDeltaPhi", 2);
  _histos.clone("WCandElecTrkPtOvE", 2);
  _histos.clone("WCandElec_TrkPhiEM3Mod", 2);
  
  _histos.clone("WCandElecPt_Width", 2);
  _histos.clone("WCandElecPt_Tail_Width", 2);
  _histos.clone("WCandMet_Width", 2);
  _histos.clone("WCandMet_Tail_Width", 2);
  _histos.clone("WCandMt_Width", 2);
  _histos.clone("WCandMt_Tail_Width", 2);
  _histos.clone("WCandPt_Width", 2);
  _histos.clone("WCandPt_Tail_Width", 2);
  _histos.clone("WCandElecPt_Spatial_Match_Width", 2);
  _histos.clone("WCandElecPt_Spatial_Match_Tail_Width", 2);
  _histos.clone("WCandMet_Spatial_Match_Width", 2);
  _histos.clone("WCandMet_Spatial_Match_Tail_Width", 2);
  _histos.clone("WCandMt_Spatial_Match_Width", 2);
  _histos.clone("WCandMt_Spatial_Match_Tail_Width", 2);
  _histos.clone("WCandPt_Spatial_Match_Width", 2);
  _histos.clone("WCandPt_Spatial_Match_Tail_Width", 2);

  _histos.clone("WCandMt_UtBin", 3);
  _histos.clone("WCandWPtUpara", 2);
  _histos.clone("WCandMtUpara", 2);
  _histos.clone("WCandElecPtUpara", 2);
  _histos.clone("WCandMetUpara", 2);
  
  // electron pT for different eta regions
  _histos.clone("WCandMt_EtaBin_CC", 15);
  _histos.clone("WCandElecPt_EtaBin_CC", 15);
  _histos.clone("WCandMet_EtaBin_CC", 15);
  _histos.clone("WCandMt_Spatial_Match_EtaBin_CC", 15);
  _histos.clone("WCandElecPt_Spatial_Match_EtaBin_CC", 15);
  _histos.clone("WCandMet_Spatial_Match_EtaBin_CC", 15);
  _histos.clone("WCandMCElecPt_EtaBin_CC", 15);
  _histos.clone("WCandMCElecPtDiff_EtaBin_CC", 15);
  _histos.clone("WCandMCElecPt_Spatial_Match_EtaBin_CC", 15);
  _histos.clone("WCandMCElecPtDiff_Spatial_Match_EtaBin_CC", 15);

  _histos.clone("WCandMt_EtaBin_CC_Tail", 15);
  _histos.clone("WCandMt_Spatial_Match_EtaBin_CC_Tail", 15);
  _histos.clone("WCandElecPt_EtaBin_CC_Tail", 15);
  _histos.clone("WCandElecPt_Spatial_Match_EtaBin_CC_Tail", 15);
  _histos.clone("WCandMet_EtaBin_CC_Tail", 15);
  _histos.clone("WCandMet_Spatial_Match_EtaBin_CC_Tail", 15);
  _histos.clone("WCandMCElecPt_EtaBin_CC_Tail", 15);
  _histos.clone("WCandMCElecPtDiff_EtaBin_CC_Tail", 15);
  _histos.clone("WCandMCElecPt_Spatial_Match_EtaBin_CC_Tail", 15);
  _histos.clone("WCandMCElecPtDiff_Spatial_Match_EtaBin_CC_Tail", 15);
  _histos.clone("WCandMCElecPt_EtaBin_CC_NoCuts", 15);

  // for CC/EC and all regions, with track matching requirement (Spatial)
  _histos.clone("WCandVtx_Spatial_Match", 2);
  _histos.clone("WCandPhi_Spatial_Match", 2);
  _histos.clone("WCandInstLumi_Spatial_Match", 2);
  _histos.clone("WCandScalarEt_Spatial_Match", 2);
  _histos.clone("WCandSqrtScalarEt_Spatial_Match", 2);
  _histos.clone("WCandElecPt_Spatial_Match", 2);
  _histos.clone("WCandElecPx_Spatial_Match", 2);
  _histos.clone("WCandElecPy_Spatial_Match", 2);
  _histos.clone("WCandElecTrkPt_Spatial_Match", 2);
  _histos.clone("WCandMet_Spatial_Match", 2);
  _histos.clone("WCandMetx_Spatial_Match", 2);
  _histos.clone("WCandMety_Spatial_Match", 2);
  _histos.clone("WCandMetPhi_Spatial_Match", 2);
  _histos.clone("WCandMt_Spatial_Match", 2);
  _histos.clone("WCandPt_Spatial_Match", 2);
  _histos.clone("WCandElecEta_Spatial_Match", 2);
  _histos.clone("WCandElecDetEta_Spatial_Match", 2);
  _histos.clone("WCandElecPhi_Spatial_Match", 2);
  _histos.clone("WCandElecDetPhi_Spatial_Match", 2);
  _histos.clone("WCandElecPhiTrkAtDCA_Spatial_Match", 2);
  _histos.clone("WCandElecPhiTrkAtEM3_Spatial_Match", 2);
  _histos.clone("WCandElecDetPhiCALO_Spatial_Match", 2);
  _histos.clone("WCandUPara_Spatial_Match", 2);
  _histos.clone("WCandUPerp_Spatial_Match", 2);
  _histos.clone("WCandUt_Spatial_Match", 2);
  _histos.clone("WCandElecRecPhi_Spatial_Match", 2);
  _histos.clone("WCandElecMetPhi_Spatial_Match", 2);
  _histos.clone("WCandElecPtUpara1_Spatial_Match", 2);
  _histos.clone("WCandElecPtUpara2_Spatial_Match", 2);
  _histos.clone("WCandMetUpara1_Spatial_Match", 2);
  _histos.clone("WCandMetUpara2_Spatial_Match", 2);
  _histos.clone("WCandMtUpara1_Spatial_Match", 2);
  _histos.clone("WCandMtUpara2_Spatial_Match", 2);
  _histos.clone("WCandWPtUpara1_Spatial_Match", 2);
  _histos.clone("WCandWPtUpara2_Spatial_Match", 2);
  _histos.clone("WCandRecoilPt_Spatial_Match", 2);
  _histos.clone("WCandRecoilPx_Spatial_Match", 2);
  _histos.clone("WCandRecoilPy_Spatial_Match", 2);
  _histos.clone("WCandRecoilPhi_Spatial_Match", 2);
  _histos.clone("WCandElecMetDeltaPhi_Spatial_Match", 2);
  _histos.clone("WCandElecRecoilDeltaPhi_Spatial_Match", 2);
  _histos.clone("WCandMetRecoilDeltaPhi_Spatial_Match", 2);
  _histos.clone("WCandMt_UtBin_Spatial_Match", 3);
  //
  _histos.clone("WCandScalarEtVElecPt_Spatial_Match", 2);
  _histos.clone("WCandElecTrkPtOvE_Spatial_Match", 2);
  _histos.clone("WCandElec_TrkPhiEM3Mod_Spatial_Match", 2);
  

  // for CC events, divided into different Pt regions
  _histos.clone("WCandMt_RecoilBin", 10);
  _histos.clone("WCandElecPt_RecoilBin", 10);
  _histos.clone("WCandMet_RecoilBin", 10);
  _histos.clone("WCandElecMetDeltaPhi_RecoilBin", 10);
  _histos.clone("WCandElecRecoilDeltaPhi_RecoilBin", 10);
  _histos.clone("WCandMetRecoilDeltaPhi_RecoilBin", 10);
  _histos.clone("WCandRecoilPhi_RecoilBin", 10);
  _histos.clone("WCandUPara_RecoilBin", 10);
  _histos.clone("WCandUPerp_RecoilBin", 10);
  _histos.clone("WCandVtx_RecoilBin", 10);
  _histos.clone("WCandPhi_RecoilBin", 10);
  _histos.clone("WCandInstLumi_RecoilBin", 10);
  _histos.clone("WCandScalarEt_RecoilBin", 10);

  //for Background Study
  _histos.clone("WCandMt_vs_DetEta", 6);
  _histos.clone("WCandElecPt_vs_DetEta", 6);
  _histos.clone("WCandMet_vs_DetEta", 6);
  _histos.clone("WCandMt_vs_DetEta_Spatial_Match", 6);
  _histos.clone("WCandElecPt_vs_DetEta_Spatial_Match", 6);
  _histos.clone("WCandMet_vs_DetEta_Spatial_Match", 6);

  // for E/p
  // this produces too many histograms, so I provide an option here
  if(_StudyEOverP) {
    _histos.clone("WCandEOverP_Positron_PosSolPol_Eta", 22);
    _histos.clone("WCandEOverP_Positron_NegSolPol_Eta", 22);
    _histos.clone("WCandEOverP_Electron_PosSolPol_Eta", 22);
    _histos.clone("WCandEOverP_Electron_NegSolPol_Eta", 22);
    
    _histos.clone("WCandEOverP_Positron_PosSolPol_DetEta", 22);
    _histos.clone("WCandEOverP_Positron_NegSolPol_DetEta", 22);
    _histos.clone("WCandEOverP_Electron_PosSolPol_DetEta", 22);
    _histos.clone("WCandEOverP_Electron_NegSolPol_DetEta", 22);
    
    _histos.clone("WCandEOverP_Positron_PosSolPol_Phi", 32);
    _histos.clone("WCandEOverP_Positron_NegSolPol_Phi", 32);
    _histos.clone("WCandEOverP_Electron_PosSolPol_Phi", 32);
    _histos.clone("WCandEOverP_Electron_NegSolPol_Phi", 32);

    _histos.clone("WCandEOverP_Mod", 32);
    _histos.clone("WCandEOverP_TrkMod", 32);
    _histos.clone("WCandRawEOverP_Mod", 32);
    _histos.clone("WCandRawEOverP_TrkMod", 32);
    _histos.clone("WCandEOverP_V_ElecPhiMod", 32);
    _histos.clone("WCandEOverP_V_ElecTrkPhiMod", 32);
    _histos.clone("WCandRawEOverP_V_ElecPhiMod", 32);
    _histos.clone("WCandRawEOverP_V_ElecTrkPhiMod", 32);

    // it turns out that just taking the mean value of E/p between 0.9 and 1.3
    // is not very helpful, we need to fit the E/p distribution with Landau convoluted
    // with Gaussian distribution to find peak position
    _histos.clone("WCandEOverP_CalPhiModPosition", 40);
    _histos.clone("WCandRawEOverP_CalPhiModPosition", 40);

    _histos.clone("WCandEOverP_TrkPhiModPosition", 40);
    _histos.clone("WCandEOverP_TrkPhiModPosition_Elec", 40);
    _histos.clone("WCandEOverP_TrkPhiModPosition_Posi", 40);
    _histos.clone("WCandRawEOverP_TrkPhiModPosition", 40);

    _histos.clone("WCandEOverP_TrkPhiModEM3Position", 40);
    _histos.clone("WCandEOverP_TrkPhiModEM3Position_Elec", 40);
    _histos.clone("WCandEOverP_TrkPhiModEM3Position_Posi", 40);
    _histos.clone("WCandRawEOverP_TrkPhiModEM3Position", 40);

    // Phi Module (CC)
    _histos.clone("WCandElecPt_Mod", 32);
    _histos.clone("WCandMet_Mod", 32);
    _histos.clone("WCandMt_Mod", 32);
    _histos.clone("WCandPt_Mod", 32);
  }

  // study uparallel efficiency
  if(_uParaEffStudy) {
    _WUtCut = 100000.;
    _histos.add(WCandUPara_Hist);
    _histos.add(WCandUPara_Hist_Profile);
    _histos.add(WCandUPara_Hist_2D);

    // for CC
    _histos.clone("WCandUPara_notrkmatch_UPara", 18);
    _histos.clone("WCandUPara_trkmatch_UPara", 18);
    _histos.clone("WCandUPara_notrkmatch_PassJet_UPara", 18);
    _histos.clone("WCandUPara_trkmatch_PassJet_UPara", 18);

    _histos.clone("WCandIsoVsHMx7_notrkmatch_UPara", 18);
    _histos.clone("WCandIsoVsHMx7_trkmatch_noTrkPtCut_noSMTHitCut_UPara", 18);
    _histos.clone("WCandIsoVsHMx7_trkmatch_noSMTHitCut_UPara", 18);
    _histos.clone("WCandIsoVsHMx7_trkmatch_noTrkPtCut_UPara", 18);
    _histos.clone("WCandIsoVsHMx7_trkmatch_UPara", 18);

    _histos.clone("WCandIsoVsHMx7_notrkmatch_PassJet_UPara", 18);
    _histos.clone("WCandIsoVsHMx7_trkmatch_noTrkPtCut_noSMTHitCut_PassJet_UPara", 18);
    _histos.clone("WCandIsoVsHMx7_trkmatch_noSMTHitCut_PassJet_UPara", 18);
    _histos.clone("WCandIsoVsHMx7_trkmatch_noTrkPtCut_PassJet_UPara", 18);
    _histos.clone("WCandIsoVsHMx7_trkmatch_PassJet_UPara", 18);

    _histos.clone("WCandUPara_WithIsoHMxCut", 18);
    _histos.clone("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut", 18);
    _histos.clone("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut", 18);
    _histos.clone("WCandUPara_WithIsoHMxCut_trkmatch_noTrkPtCut", 18);
    _histos.clone("WCandUPara_WithIsoHMxCut_trkmatch", 18);
    _histos.clone("WCandUPara_WithGoodSpatialMatch", 18);
    _histos.clone("WCandUPara_WithGoodSpatialMatch_IsoHMxCut", 18);
    _histos.clone("WCandUPara_WithSpatialMatch", 18);
    _histos.clone("WCandUPara_WithSpatialMatch_IsoHMxCut", 18);
    
    // for EC
    _histos.clone("WCandUPara_notrkmatch_UPara_EC", 18);
    _histos.clone("WCandUPara_trkmatch_UPara_EC", 18);
    _histos.clone("WCandUPara_notrkmatch_PassJet_UPara_EC", 18);
    _histos.clone("WCandUPara_trkmatch_PassJet_UPara_EC", 18);

    _histos.clone("WCandIsoVsHMx8_notrkmatch_UPara_EC", 18);
    _histos.clone("WCandIsoVsHMx8_trkmatch_noTrkPtCut_noSMTHitCut_UPara_EC", 18);
    _histos.clone("WCandIsoVsHMx8_trkmatch_noSMTHitCut_UPara_EC", 18);
    _histos.clone("WCandIsoVsHMx8_trkmatch_noTrkPtCut_UPara_EC", 18);
    _histos.clone("WCandIsoVsHMx8_trkmatch_UPara_EC", 18);

    _histos.clone("WCandIsoVsHMx8_notrkmatch_PassJet_UPara_EC", 18);
    _histos.clone("WCandIsoVsHMx8_trkmatch_noTrkPtCut_noSMTHitCut_PassJet_UPara_EC", 18);
    _histos.clone("WCandIsoVsHMx8_trkmatch_noSMTHitCut_PassJet_UPara_EC", 18);
    _histos.clone("WCandIsoVsHMx8_trkmatch_noTrkPtCut_PassJet_UPara_EC", 18);
    _histos.clone("WCandIsoVsHMx8_trkmatch_PassJet_UPara_EC", 18);

    _histos.clone("WCandUPara_WithIsoHMxCut_EC", 18);
    _histos.clone("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut_EC", 18);
    _histos.clone("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_EC", 18);
    _histos.clone("WCandUPara_WithIsoHMxCut_trkmatch_noTrkPtCut_EC", 18);
    _histos.clone("WCandUPara_WithIsoHMxCut_trkmatch_EC", 18);
    _histos.clone("WCandUPara_WithGoodSpatialMatch_EC", 18);
    _histos.clone("WCandUPara_WithGoodSpatialMatch_IsoHMxCut_EC", 18);
    _histos.clone("WCandUPara_WithSpatialMatch_EC", 18);
    _histos.clone("WCandUPara_WithSpatialMatch_IsoHMxCut_EC", 18);
  }

  // initialize event counters
  _events_fail_trigger_requirements = 0;

  // create a text file to write out w candidate run number and event number
  if(!_MCStudy) _wenu_out_txt = new fstream("wenu_run_event_number.txt", std::ios::out);
}

bool WAnalysis::processEvent(Event& event)
{
  _BM.ExamineEvent(&event);

  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");
  vector<CAFEMObj*> emobjs;
  CAFMet met; 
  CAFMet rawmet;
  int solpol = -999;  
  double instlumi = 0.;
  float vtx_x, vtx_y, vtx_z;
  int triglist_flag = -1;
  int runNo, evtNo;

  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;
  
  HighestPhotonPt=0;
  SecondHighestPhotonPt=0;
  
  std::vector<TMBMCpart *> unmerged_mc_photons;
  std::vector<CAFEMObj*> passed_iso;
  std::vector<CAFEMObj*> passed_HMX;
  std::vector<CAFEMObj*> passed_iso_HMX;

  isPhot=false;
  
  if( event.get("unmerged photons", unmerged_mc_photons) ){
    if(unmerged_mc_photons.size()>0) isPhot=true;;
  
    for (vector<TMBMCpart*>::iterator it2 = unmerged_mc_photons.begin(); it2!= unmerged_mc_photons.end(); ++it2) {
      double mpT = (*it2)->Pt();
      if(mpT>HighestPhotonPt){
	SecondHighestPhotonPt = HighestPhotonPt;
	HighestPhotonPt=mpT;
      }
      else if(mpT>SecondHighestPhotonPt){
	SecondHighestPhotonPt =	mpT;
      }
    }
  }

  // check generator electron pT distributions for different eta regions
  bool genElec_In_CC = false;   // generator level electron in CC fiducial region
  std::vector<TMBMCpart *> raw_emobjs_gen;
  if(_MCStudy) {
    if(event.get("em mc objects", raw_emobjs_gen)) {
      if(raw_emobjs_gen.size()>0) {

	//
	// extrapolate generator level electrons to EM3 use true primary vertex
	//
	double mc_vtx_z = vtx_z;
	cafe::Collection<TMBMCvtx> mc_vtxs = event.getMCVertices();
	if(mc_vtxs.size()>0) mc_vtx_z = mc_vtxs[0].z();
	
	// extrapolated particle phi at EM3
	double DetPhiEM3_gen, DetEtaEM3_gen;
	wz_utils::simple_extrap(mc_vtx_z, raw_emobjs_gen[0]->Eta(), raw_emobjs_gen[0]->Phi(), DetEtaEM3_gen, DetPhiEM3_gen);
	double detphiMod = fmod(16.*DetPhiEM3_gen/3.1415926, 1.0);

	if(fabs(DetEtaEM3_gen)<1.05 && detphiMod>0.1 && detphiMod<0.9) { // truth electron in CC fiducial region

	  genElec_In_CC = true;

	  int FineEtaRegion_CC_gen = -1;
	  double eta = raw_emobjs_gen[0]->Eta();
	  if(eta<-1.3) FineEtaRegion_CC_gen = 0;
	  else if (eta<-1.1) FineEtaRegion_CC_gen = 1;
	  else if (eta<-0.9) FineEtaRegion_CC_gen = 2;
	  else if (eta<-0.7) FineEtaRegion_CC_gen = 3;
	  else if (eta<-0.5) FineEtaRegion_CC_gen = 4;
	  else if (eta<-0.3) FineEtaRegion_CC_gen = 5;
	  else if (eta<-0.1) FineEtaRegion_CC_gen = 6;
	  else if (eta<0.1) FineEtaRegion_CC_gen = 7;
	  else if (eta<0.3) FineEtaRegion_CC_gen = 8;
	  else if (eta<0.5) FineEtaRegion_CC_gen = 9;
	  else if (eta<0.7) FineEtaRegion_CC_gen = 10;
	  else if (eta<0.9) FineEtaRegion_CC_gen = 11;
	  else if (eta<1.1) FineEtaRegion_CC_gen = 12;
	  else if (eta<1.3) FineEtaRegion_CC_gen = 13;
	  else FineEtaRegion_CC_gen = 14;
	  char sn_FineEtaRegion_CC_gen[10];   sprintf(sn_FineEtaRegion_CC_gen, "%d", FineEtaRegion_CC_gen);

	  _histos.Fill1D(TString("WCandMCElecPt_EtaBin_CC_NoCuts_")+sn_FineEtaRegion_CC_gen, raw_emobjs_gen[0]->Pt());
	}
      }  
    } // get photon-merged electrons    
  }

  //
  // find the scalar Et for this full MC event
  //
  double ScalarEt_ZB_Overlay = 0.; // scalar Et for the overlay ZB event, only works for full MC
  double elecPtOverScalarEt_ZB_Overlay = 0.; // elec pT/scalar Et for the overlay ZB event, only works for full MC
  
  if(_MCStudy && _ScalarEtStudy) {
    int runNo_ZB = event.getMCEventInfo()->overlayrun();
    int evtNo_ZB = event.getMCEventInfo()->overlayevtid();
    
    TwoInteger RunEvtIndex(runNo_ZB, evtNo_ZB);
    map<TwoInteger, double>::iterator it = _scalarEtMaps.find(RunEvtIndex);
    if(it != _scalarEtMaps.end()) {
      ScalarEt_ZB_Overlay = it->second;
      if(raw_emobjs_gen.size()>0) elecPtOverScalarEt_ZB_Overlay = raw_emobjs_gen[0]->Pt()/it->second;
    }

    if(genElec_In_CC) {
      if(raw_emobjs_gen[0]->Pt()>25.) {
	_histos.Fill1D("WCandScalarEt_NoCuts", ScalarEt_ZB_Overlay);
	_histos.Fill1D("WCandElecPtOverScalarEt_NoCuts", elecPtOverScalarEt_ZB_Overlay);
	_histos.Fill1D("WCandMCElecPt_NoCuts", raw_emobjs_gen[0]->Pt());
      }
    } // generator level electron in CC
  }    

  // get the pointers from event
  if( event.get("Good EMObjs", emobjs) && event.get("EMCorr Met", met) && 
      event.get("Raw Met", rawmet) &&
      event.get("L1CalTowers", l1cal_vec) && event.get("L1Cal2bTowers", l1cal2b_vec) && 
      event.get("L2GblEMs", l2cal_vec) && 
      event.get("L3Eles", l3cal_vec) && event.get("triglist flag", triglist_flag) &&
      event.get("run number", runNo) && event.get("event number", evtNo) && 
      event.get("InstLumi", instlumi) && event.get("solenoid polarity", solpol) && 
      event.get("Best primary vertexX", vtx_x) && 
      event.get("Best primary vertexY", vtx_y) && event.get("Best primary vertexZ", vtx_z)) {
 
   
    // change solpol from 0/1 to -1/1
    int polarity = 2*solpol -1;

    // primary vertex
    float v_z = vtx_z;
    char bins_Vtx[10];
    int bin_Vtx_number;
    bin_Vtx_number=int((v_z+60.)/20.);
    sprintf(bins_Vtx, "%d", bin_Vtx_number);    

    // primary vertex
    float vtx[3] = {vtx_x, vtx_y, vtx_z};

    // this is only used for MC analysis
    bool WCCCand = false;
 
    // construct W candidate
    CAFWCand wcand;
    CAFEMObj *emobj = 0;
    double wScalarET = 0.;
    if (emobjs.size()>=1) {
      emobj = emobjs[0];
      if(_dorawCellsRecoil) {
	if (_useConsistentMET) {
	  wcand = CAFWCand(emobj, &rawmet, vtx, true);
	} else {
	  wcand = CAFWCand(emobj, &met, vtx);
	}
      } else {
	wcand = CAFWCand(emobj, &met);
      }
      if (_useConsistentMET) {
	TVector2 consistMET=wcand.GetConsistentMET();
	double dummySET=met.scalarEt();
        wScalarET = dummySET;
	met.SetMet(consistMET.X(),consistMET.Y(),consistMET.Mod(),dummySET);
      }
    }

    //
    // check scalar Et efficiency for different selection cut
    //
    if(_MCStudy && _ScalarEtStudy) {      
      if(genElec_In_CC) {
	if(raw_emobjs_gen[0]->Pt()>25.) {
	  if(emobjs.size()>=1) { // at least one EM object
	    _histos.Fill1D("WCandScalarEt_Cut1", ScalarEt_ZB_Overlay);
	    _histos.Fill1D("WCandElecPtOverScalarEt_Cut1", elecPtOverScalarEt_ZB_Overlay);
	    _histos.Fill1D("WCandMCElecPt_Cut1", raw_emobjs_gen[0]->Pt());

	    if(emobjs[0]->has_good_spatial_track_match()) {
	      _histos.Fill1D("WCandScalarEt_Cut2", ScalarEt_ZB_Overlay);
	      _histos.Fill1D("WCandElecPtOverScalarEt_Cut2", elecPtOverScalarEt_ZB_Overlay);
	      _histos.Fill1D("WCandMCElecPt_Cut2", raw_emobjs_gen[0]->Pt());

	      if(met.met()>_WMetCut) { // met Cut
		_histos.Fill1D("WCandScalarEt_Cut3", ScalarEt_ZB_Overlay);
		_histos.Fill1D("WCandElecPtOverScalarEt_Cut3", elecPtOverScalarEt_ZB_Overlay);
		_histos.Fill1D("WCandMCElecPt_Cut3", raw_emobjs_gen[0]->Pt());

		if(wcand.Mt()>_WMtCut1 && wcand.Mt()<_WMtCut2) {
		  _histos.Fill1D("WCandScalarEt_Cut4", ScalarEt_ZB_Overlay);
		  _histos.Fill1D("WCandElecPtOverScalarEt_Cut4", elecPtOverScalarEt_ZB_Overlay);
		  _histos.Fill1D("WCandMCElecPt_Cut4", raw_emobjs_gen[0]->Pt());
  
		  if(wcand.MagRecoil()<_WUtCut && wcand.MagRecoil()>_WUtCut_lower) {
		    _histos.Fill1D("WCandScalarEt_Cut5", ScalarEt_ZB_Overlay);
		    _histos.Fill1D("WCandElecPtOverScalarEt_Cut5", elecPtOverScalarEt_ZB_Overlay);		    
		    _histos.Fill1D("WCandMCElecPt_Cut5", raw_emobjs_gen[0]->Pt());
		  } // recoil pT cut
		} // WMt Cut
	      } // met cut
	    } // good track match
	  } // at least one EM object
	}
      } // generator level electron in CC
    }    

    //***********************************************************************
    // main studies
    //***********************************************************************

	if( emobjs.size()>=1 && (met.met())>_WMetCut) {


      // write useful information to a text file
      // ****************************************************
      // **********EM selection requirements are loosed *****
      // ****************************************************
      // W candidate type, 0 for CC, 1 for EC
      int type = wcand.Type(_DetEtaCC, _DetEtaEC1, _DetEtaEC2);
      if(type==0) WCCCand = true;
      char sn[10];  sprintf(sn,"%d", type);
      
      if(_makeEfficStudyFile) {
        if(type == 0) {
	  makeEfficStudyFile(event, emobjs, raw_emobjs_gen, instlumi, type, wScalarET);
	}
      }

      // write out possible W candidate runNo, evtNo to a text file
      if(!_MCStudy) (*_wenu_out_txt) << runNo << " " << evtNo << endl;
      
      // need to access all tracks to load track branch to allow partial read
      // otherwise I will get totally different result
      //get tracks from the event
      cafe::Collection<TMBTrack> trks = event.getTracks();
      
      const TMBTrack *track_spatial = NULL;
      
      // the electron must pass trigger requirement
      // for GEANT MC, we do not need to check trigger efficiency
      bool pass_trigger = false;
      if(_MCStudy) pass_trigger = true;
      else pass_trigger = emobj->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec);
      if(!pass_trigger) _events_fail_trigger_requirements ++;

      if(_debugLevel>=5) wcand.print();

      // if we want to dump Z bkg out of W data (one EM cluster with back-to-back high pT isolated track)
      bool ZEvent = false;

      if(_dump_W_ZeeBkg) {
	// require no high pT isolated track back-to-back with the electron
	bool EM_Track_backtoback = false;

	//entry = -555;
	run = -555;
	evt = -555;
	lumi = -555;
	vtxz = -555;
	evtmet = -555;
	evtset = -555;
	wcandut = -555;
	wcandupara = -555;
	wcandmt = -555;
	wcandutphi = -555;

	e_n = -555;
	e_pt = -555;
	e_e = -555;
	e_eta = -555;
	e_deta = -555;
	e_phi = -555;
	e_charge = -555;
	e_goodspmtch = -555;
	e_id = -555;
	e_phimod = -555;

	j_n = -555;
	j_pt = -555;
	j_e = -555;
	j_eta = -555;
	j_deta = -555;
	j_phi = -555;
	j_trks = -555;
	j_n90 = -555;

	j_emf = -555;
	j_chf = -555;
	j_hcr = -555;

	t_n = -555;
	t_pt = -555;
	t_e = -555;
	t_eta = -555;
	t_deta = -555;
	t_phi = -555;
	t_charge = -555;

	t_nsmt = -555;
	t_z = -555;
	t_chisq = -555;

	ej_deltaphi = -555;
	ej_m = -555;
	et_deltaphi = -555;
	et_m = -555;

    bool found_JET=false;
    bool found_isolated_track=false;

	entry++;
	run=event.getGlobal()->runno();
	evt=event.getGlobal()->evtno();
	lumi=instlumi*36.0;
	vtxz=vtx_z;
	evtmet = met.met();
	evtset = met.scalarEt();
    wcandut = wcand.MagRecoil();
    wcandmt = wcand.Mt();   
    wcandupara = wcand.UPara();  
    wcandutphi = (wcand.GetRecoil()).Phi();
	if(emobj->has_good_spatial_track_match()) e_goodspmtch=1;

    e_id=emobj->id();
	e_pt=emobj->Pt();
	e_e=emobj->E();
	e_eta=emobj->Eta();
	e_deta=emobj->CalDetectorEta();
	e_phi=emobj->Phi();

	double tmp_WElecPhiTrkAtEM3 = emobj->TrkPhiEM3();
    e_phimod = fmod(16.*tmp_WElecPhiTrkAtEM3/3.1415926, 1.0);

	e_charge=emobj->charge();
	e_n=emobjs.size();//without good spatial match requirement


	/*
	# cuts used in FakeAnalysis
	# definition of good jets
	myname.jetN90Cut:             1             # jet N90
	myname.jetpTCut:              20            # jet pT
	myname.jetEMFracCut1:         0.05          # jet EMFraction Cut1
	myname.jetEMFracCut2:         0.95          # jet EMFraction Cut2
	myname.jetCHFracCut:          0.4           # jet CHFraction Cut
	myname.jetHCRatioCut:         10.           # jet HCRatio Cut
	myname.jetTracks:             1             # jet tracks Cut

	myname.DetEtaCC_Jet:          0.8           # detector coverage for good jet
	myname.DetEtaEC1_Jet:         1.5           # detector coverage for good jet
	myname.DetEtaEC2_Jet:         2.5           # detector coverage for good jet

	myname.Angle_Jet_EM_Cut:      0.25          # angle seperation betwen EM and Jet
	myname.DPhi_Jet_EM_Cut:       2.8           # phi seperation between EM and Jet

    if( (fabs(deta)<_DetEtaCC_Jet) || ((fabs(deta)>_DetEtaEC1_Jet) && (fabs(deta)<_DetEtaEC2_Jet)) ) {
      if( (jetN90>_jetN90Cut) && (jetEMFrac>_jetEMFracCut1) && (jetEMFrac<_jetEMFracCut2) &&
	  (jetCHFrac<_jetCHFracCut) && (jetHCRatio<_jetHCRatioCut) && (jetTrack>=_jetTrackCut) )
	good = true;
 

	*/

	// access Jet information	 
	cafe::Collection<TMBJet> jets = event.getJCCB();
    j_n = 0;
	if(jets.size() > 0) {
      for(Collection<TMBJet>::iterator iter = jets.begin(); iter != jets.end(); ++iter) { 
        ej_deltaphi=kinem::delta_phi(e_phi, (*iter).Phi());
        if(ej_deltaphi > 2.5) {
          j_n++;
		  j_n90  = (*iter).n90(); 
		  j_pt   = (*iter).Pt();	 
		  j_emf  = (*iter).emf();
		  j_chf  = (*iter).chf();
		  j_hcr  = (*iter).hotcellratio();
		  j_trks = (*iter).Ntr(); 
		  j_eta  = (*iter).Eta();
		  j_phi  = (*iter).Phi();
		  j_deta = (*iter).deta();
 		  j_e = (*iter).E();
	      TLorentzVector vect_jet((*iter).Px(), (*iter).Py(),(*iter).Pz(),(*iter).E());
	      TLorentzVector vect_emobj(emobj->Px(),emobj->Py(),emobj->Pz(),emobj->E());
	      TLorentzVector vect_Z=vect_jet+vect_emobj;
          ej_m=vect_Z.M();
          found_JET = true;
        }//if(ej_deltaphi > 2.5)
      }// for(Collection<TMBJet>
	}//if(jets.size() > 0)

    t_n=0;
	vector<CAFTrack *> isolatedTrks;
	if(event.get("Good Tracks", isolatedTrks)) {
	  for(int itrk=0; itrk<isolatedTrks.size(); itrk++) {
          et_deltaphi=kinem::delta_phi(emobj->Phi(), isolatedTrks[itrk]->Phi());
	      if(et_deltaphi > 2.5) {
             EM_Track_backtoback=true;
             t_n++;
			 t_pt=isolatedTrks[itrk]->Pt();
			 t_e=isolatedTrks[itrk]->E();
			 t_eta=isolatedTrks[itrk]->Eta();
			 t_phi=isolatedTrks[itrk]->Phi();
			 t_deta=isolatedTrks[itrk]->TrackDetEta(polarity, _MCStudy);
			 t_nsmt 	 =   isolatedTrks[itrk]->nsmt() ;
			 t_z	  = 	 isolatedTrks[itrk]->z()   ; 
			 t_chisq	  =  isolatedTrks[itrk]->getChi2Ndf();
			 t_charge=isolatedTrks[itrk]->charge();

	    	 TLorentzVector vect_trk(isolatedTrks[itrk]->Px(),isolatedTrks[itrk]->Py(),isolatedTrks[itrk]->Pz(),isolatedTrks[itrk]->E());
	    	 TLorentzVector vect_emobj(emobj->Px(),emobj->Py(),emobj->Pz(),emobj->E());
	    	 TLorentzVector vect_Z=vect_trk+vect_emobj;

        	 et_m=vect_Z.M();
             et->Fill();
             found_isolated_track = true;

        }
	  }
	}

    if(found_isolated_track == false && found_JET == true) et->Fill();
	
	if(EM_Track_backtoback) ZEvent = true;
    }// if(_dump_W_ZeeBkg) {


    //---- next piece is for TESTING purposes
    //---- remove when passed test ----------
  
    //**************************************
    //************** NOW PUT SAME _dump_W_ZeeBkg code as in the default WAnalysis
    //**only ZEvent already declared************************************

      // if we want to dump Z bkg out of W data (one EM cluster with back-to-back high pT isolated track)
      ZEvent = false;

      if(_dump_W_ZeeBkg) {
	// require no high pT isolated track back-to-back with the electron
	bool EM_Track_backtoback = false;
	
	// get all isolated tracks
	vector<CAFTrack *> isolatedTrks;
	if(event.get("Good Tracks", isolatedTrks)) {
	  for(int itrk=0; itrk<isolatedTrks.size(); itrk++) {
	    double em_trk_phidiff = kinem::delta_phi(emobj->Phi(), isolatedTrks[itrk]->Phi());
	    if(em_trk_phidiff > 2.5 && // back to back with the EM cluster
	       fabs(isolatedTrks[itrk]->TrackDetEta(polarity, _MCStudy))>1.1 &&  // track in ICR 
	       fabs(isolatedTrks[itrk]->TrackDetEta(polarity, _MCStudy))<1.5 &&
	       fabs(isolatedTrks[itrk]->z()-vtx_z)<1. &&  // vertex close to each other 
	       (isolatedTrks[itrk]->charge())*(emobj->charge())<0.) { // opposite charge
	      
	      TLorentzVector vect_trk(isolatedTrks[itrk]->Px(),isolatedTrks[itrk]->Py(),isolatedTrks[itrk]->Pz(),isolatedTrks[itrk]->E());
	      TLorentzVector vect_emobj(emobj->Px(),emobj->Py(),emobj->Pz(),emobj->E());
	      TLorentzVector vect_Z=vect_trk+vect_emobj;
	      
	      // invariant mass
	      if(vect_Z.M()>70. && vect_Z.M()<110.)   EM_Track_backtoback = true;
	    }
	  }
	}
	
	if(EM_Track_backtoback) ZEvent = true;
    }// if(_dump_W_ZeeBkg) {
    //**************  END OF ********
    //************** NOW PUT SAME _dump_W_ZeeBkg code as in the default WAnalysis
    //**************************************



      // if we do not want to dump ZeeBkg, will make keepEvent always true
      // but if we want to dump ZeeBkg, only make keepEvent true for Zee bkg
      bool keepEvent = false;
      if(_dump_W_ZeeBkg) {
	if(ZEvent) keepEvent = true;
      } 
      else keepEvent = true;

      ////// this is present in "tree only" version keepEvent=false; // only need the tree


      // make W boson Ut cut and Mt cut
      if(wcand.MagRecoil()<_WUtCut && wcand.MagRecoil()> _WUtCut_lower && wcand.Mt()>_WMtCut1 && wcand.Mt()<_WMtCut2 && pass_trigger && keepEvent) {

	// get pointer to matched track (good spatial track match)
	bool good_spatial_track_match = emobj->has_good_spatial_track_match(0.01,_require_smt);
	if(good_spatial_track_match) track_spatial = emobj->getPtrSpatialChp();
	
	// make recoil file for Matt's studies
	if(_makeRecoilFile) {
	  if(type == 0) makeRecoilFile(event, emobjs, instlumi, type, wScalarET);
	}

	double WElecPt = emobj->Pt();
	double WElecPx = emobj->Px();
	double WElecPy = emobj->Py();
	double WMet = met.met();
	double WMetx = met.metx();
	double WMety = met.mety();
	double WMetPhi = met.metphi();
	double WMt = wcand.Mt();
	double WPt = wcand.Pt();
	double WPhi = (wcand.vect2()).Phi();
	double WElecEta = emobj->Eta();
	double WElecDetEta = emobj->CalDetectorEta();
	double WElecPhiTrkAtDCA = emobj->Phi();
	double WElecPhiTrkAtEM3 = emobj->TrkPhiEM3();
	double WElecDetPhiCALO = emobj->CalDetectorPhi();
	double WElecPhiMod = fmod(16.*WElecDetPhiCALO/3.1415926, 1.0);
    double WElecTrkPhiModEM3 = fmod(16.*WElecPhiTrkAtEM3/3.1415926, 1.0);
	double UPara = wcand.UPara();
	double UPerp = wcand.UPerp();
	double UT = sqrt(UPara*UPara + UPerp*UPerp);
	double DPhi_EM_Met = fabs(wcand.DeltaPhi_EM_Met());
	double DPhi_EM_Recoil = fabs(wcand.DeltaPhi_EM_Recoil());
	double WRecoilPt = wcand.MagRecoil();
	double WRecoilPx = (wcand.GetRecoil()).Px();
	double WRecoilPy = (wcand.GetRecoil()).Py();
	double WRecoilPhi = (wcand.GetRecoil()).Phi();
	TVector2 met_vect(WMetx, WMety);

	// calculate scalarEt and remove two electrons contribution
	double WScalarEt = 0;
	if (!_dorawCellsRecoil) {
	  WScalarEt = met.scalarEt();
	  double ScalarEt_EMObjs = emobj->EMScalarEt()*emobj->E()/emobj->uncorrE();
	  WScalarEt -= ScalarEt_EMObjs;
	} else {
	  WScalarEt = rawmet.scalarEt();
	  float cntrib1=0;
	  emobj->getRawElecVectorFromCells(vtx,&cntrib1);
	  double ScalarEt_EMObjs = cntrib1;
	  WScalarEt -= ScalarEt_EMObjs;
	}

//         // now we can do some systematic studies by varying the cuts
// 	if(_consistency_check) {
// 	  bool passCut_under_study =  wz_utils::passCut(_cut_under_study, _invert_cut, 
// 							runNo, _runNo_cut, 
// 							instlumi, _InstLumi_lowcut, _InstLumi_highcut, 
// 							WScalarEt, _ScalarEt_cut,
// 							WElecEta, _ElecEta_cut,
// 							WElecDetEta, _ElecDetEta_cut,
// 							WElecTrkPhiModEM3, _ElecPhiMod_cut,
//                             UPara, _UPara_lowcut, _UPara_highcut,
// 							WElecPt, _ElecPt_lowcut, _ElecPt_highcut);
// 	  if(!passCut_under_study) return false;
// 	}

	// find the phimod for each electron, mod_phi is only meaningful for CC electron
	int mod_phi = emobj->PhiModule();
	char sn_mod[10];   sprintf(sn_mod, "%d", mod_phi);

	// if we want to study uparallel efficiency for CC/EC electrons with track match
	if((type==0 || type==1) && _uParaEffStudy) uParaEfficiencyStudies(event, wcand);

	// check Electron pT, MET, Mt, W PT for each CC module
	if(type == 0) {
	  _histos.Fill1D(TString("WCandElecPt_Mod_")+sn_mod, WElecPt);
	  _histos.Fill1D(TString("WCandMet_Mod_")+sn_mod, WMet);
	  _histos.Fill1D(TString("WCandMt_Mod_")+sn_mod, WMt);
	  _histos.Fill1D(TString("WCandPt_Mod_")+sn_mod, WPt);

	  if(UT<5.)
	    _histos.Fill1D("WCandMt_UtBin_0", WMt);
	  if(UT>5. && UT<10.)
	    _histos.Fill1D("WCandMt_UtBin_1", WMt);
	  if(UT>10. && UT<15.)
	    _histos.Fill1D("WCandMt_UtBin_2", WMt);
	}

	// fill 3D histograms
	if(type == 0) {
	  _histos.Fill3D("WCandInstLumiVDetEtaPt", WElecDetEta, WElecPt, instlumi);
	  _histos.Fill3D("WCandScalarEtVDetEtaPt", WElecDetEta, WElecPt, WScalarEt);
	  _histos.Fill3D("WCandSqrtScalarEtVDetEtaPt", WElecDetEta, WElecPt, sqrt(WScalarEt));
	  _histos.Fill3D("WCandVtxVDetEtaPt", WElecDetEta, WElecPt, vtx_z);
	  _histos.Fill3D("WCandPhiVDetEtaPt", WElecDetEta, WElecPt, WPhi);
	  _histos.Fill3D("WCandElecPtVDetEtaPt", WElecDetEta, WElecPt, WElecPt);
	  _histos.Fill3D("WCandMetVDetEtaPt", WElecDetEta, WElecPt, WMet);
	  _histos.Fill3D("WCandMetxVDetEtaPt", WElecDetEta, WElecPt, WMetx);
	  _histos.Fill3D("WCandMetyVDetEtaPt", WElecDetEta, WElecPt, WMety);
	  _histos.Fill3D("WCandMetPhiVDetEtaPt", WElecDetEta, WElecPt, WMetPhi);
	  _histos.Fill3D("WCandMtVDetEtaPt", WElecDetEta, WElecPt, WMt);
	  _histos.Fill3D("WCandPtVDetEtaPt", WElecDetEta, WElecPt, WPt);
	  _histos.Fill3D("WCandElecPxVDetEtaPt", WElecDetEta, WElecPt, WElecPx);
	  _histos.Fill3D("WCandElecPyVDetEtaPt", WElecDetEta, WElecPt, WElecPy);
	  _histos.Fill3D("WCandElecEtaVDetEtaPt", WElecDetEta, WElecPt, WElecEta);
	  _histos.Fill3D("WCandElecDetEtaVDetEtaPt", WElecDetEta, WElecPt, WElecDetEta);
	  _histos.Fill3D("WCandElecPhiVDetEtaPt", WElecDetEta, WElecPt, WElecPhiTrkAtDCA);
	  _histos.Fill3D("WCandElecDetPhiVDetEtaPt", WElecDetEta, WElecPt, WElecDetPhiCALO);
	  _histos.Fill3D("WCandUParaVDetEtaPt", WElecDetEta, WElecPt, UPara);
	  _histos.Fill3D("WCandUPerpVDetEtaPt", WElecDetEta, WElecPt, UPerp);
	  _histos.Fill3D("WCandUtVDetEtaPt", WElecDetEta, WElecPt, UT);
	  _histos.Fill3D("WCandRecoilPtVDetEtaPt", WElecDetEta, WElecPt, WRecoilPt);
	  _histos.Fill3D("WCandRecoilPxVDetEtaPt", WElecDetEta, WElecPt, WRecoilPx);
	  _histos.Fill3D("WCandRecoilPyVDetEtaPt", WElecDetEta, WElecPt, WRecoilPy);
	  _histos.Fill3D("WCandRecoilPhiVDetEtaPt", WElecDetEta, WElecPt, WRecoilPhi);
	  _histos.Fill3D("WCandElecMetDeltaPhiVDetEtaPt", WElecDetEta, WElecPt, wcand.DeltaPhi_EM_Met());
	  _histos.Fill3D("WCandElecRecoilDeltaPhiVDetEtaPt", WElecDetEta, WElecPt, wcand.DeltaPhi_EM_Recoil());
	  _histos.Fill3D("WCandMetRecoilDeltaPhiVDetEtaPt", WElecDetEta, WElecPt, fabs(met_vect.DeltaPhi(wcand.GetRecoil())));

	  _histos.Fill3D("WCandMtVDetEtaPt_Width", WElecDetEta, WElecPt, WMt);
	  _histos.Fill3D("WCandElecPtVDetEtaPt_Width", WElecDetEta, WElecPt, WElecPt);
	  _histos.Fill3D("WCandMetVDetEtaPt_Width", WElecDetEta, WElecPt, WMet);
	  _histos.Fill3D("WCandPtVDetEtaPt_Width", WElecDetEta, WElecPt, WPt);
	  
	  // for upara<0 and upara>0
	  if (UPara < 0) {
	    _histos.Fill3D("WCandElecPtUpara1VDetEtaPt", WElecDetEta, WElecPt, WElecPt);
	    _histos.Fill3D("WCandMetUpara1VDetEtaPt", WElecDetEta, WElecPt, WMet);
	    _histos.Fill3D("WCandMtUpara1VDetEtaPt", WElecDetEta, WElecPt, WMt);
	    _histos.Fill3D("WCandWPtUpara1VDetEtaPt", WElecDetEta, WElecPt, WPt);
	  } else {
	    _histos.Fill3D("WCandElecPtUpara2VDetEtaPt", WElecDetEta, WElecPt, WElecPt);
	    _histos.Fill3D("WCandMetUpara2VDetEtaPt", WElecDetEta, WElecPt, WMet);
	    _histos.Fill3D("WCandMtUpara2VDetEtaPt", WElecDetEta, WElecPt, WMt);
	    _histos.Fill3D("WCandWPtUpara2VDetEtaPt", WElecDetEta, WElecPt, WPt);
	  }

	  // for three uT ranges
	  if(UT<5.) _histos.Fill3D("WCandMtVDetEtaPt_UtBin_0", WElecDetEta, WElecPt, WMt);
	  if(UT>5. && UT<10.) _histos.Fill3D("WCandMtVDetEtaPt_UtBin_1", WElecDetEta, WElecPt, WMt);
	  if(UT>10. && UT<15.) _histos.Fill3D("WCandMtVDetEtaPt_UtBin_2", WElecDetEta, WElecPt, WMt);
	  
	  // spatial track match
	  if(good_spatial_track_match && (track_spatial!=NULL)) {
	    _histos.Fill3D("WCandInstLumiVDetEtaPt_Match", WElecDetEta, WElecPt, instlumi);
	    _histos.Fill3D("WCandScalarEtVDetEtaPt_Match", WElecDetEta, WElecPt, WScalarEt);
	    _histos.Fill3D("WCandSqrtScalarEtVDetEtaPt_Match", WElecDetEta, WElecPt, sqrt(WScalarEt));
	    _histos.Fill3D("WCandVtxVDetEtaPt_Match", WElecDetEta, WElecPt, vtx_z);
	    _histos.Fill3D("WCandPhiVDetEtaPt_Match", WElecDetEta, WElecPt, WPhi);
	    _histos.Fill3D("WCandElecPtVDetEtaPt_Match", WElecDetEta, WElecPt, WElecPt);
	    _histos.Fill3D("WCandMetVDetEtaPt_Match", WElecDetEta, WElecPt, WMet);
	    _histos.Fill3D("WCandMetxVDetEtaPt_Match", WElecDetEta, WElecPt, WMetx);
	    _histos.Fill3D("WCandMetyVDetEtaPt_Match", WElecDetEta, WElecPt, WMety);
	    _histos.Fill3D("WCandMetPhiVDetEtaPt_Match", WElecDetEta, WElecPt, WMetPhi);
	    _histos.Fill3D("WCandMtVDetEtaPt_Match", WElecDetEta, WElecPt, WMt);
	    _histos.Fill3D("WCandPtVDetEtaPt_Match", WElecDetEta, WElecPt, WPt);
	    _histos.Fill3D("WCandElecPxVDetEtaPt_Match", WElecDetEta, WElecPt, WElecPx);
	    _histos.Fill3D("WCandElecPyVDetEtaPt_Match", WElecDetEta, WElecPt, WElecPy);
	    _histos.Fill3D("WCandElecEtaVDetEtaPt_Match", WElecDetEta, WElecPt, WElecEta);
	    _histos.Fill3D("WCandElecDetEtaVDetEtaPt_Match", WElecDetEta, WElecPt, WElecDetEta);
	    _histos.Fill3D("WCandElecPhiVDetEtaPt_Match", WElecDetEta, WElecPt, WElecPhiTrkAtDCA);
	    _histos.Fill3D("WCandElecDetPhiVDetEtaPt_Match", WElecDetEta, WElecPt, WElecDetPhiCALO);
	    _histos.Fill3D("WCandUParaVDetEtaPt_Match", WElecDetEta, WElecPt, UPara);
	    _histos.Fill3D("WCandUPerpVDetEtaPt_Match", WElecDetEta, WElecPt, UPerp);
	    _histos.Fill3D("WCandUtVDetEtaPt_Match", WElecDetEta, WElecPt, UT);
	    _histos.Fill3D("WCandRecoilPtVDetEtaPt_Match", WElecDetEta, WElecPt, WRecoilPt);
	    _histos.Fill3D("WCandRecoilPxVDetEtaPt_Match", WElecDetEta, WElecPt, WRecoilPx);
	    _histos.Fill3D("WCandRecoilPyVDetEtaPt_Match", WElecDetEta, WElecPt, WRecoilPy);
	    _histos.Fill3D("WCandRecoilPhiVDetEtaPt_Match", WElecDetEta, WElecPt, WRecoilPhi);
	    _histos.Fill3D("WCandElecMetDeltaPhiVDetEtaPt_Match", WElecDetEta, WElecPt, wcand.DeltaPhi_EM_Met());
	    _histos.Fill3D("WCandElecRecoilDeltaPhiVDetEtaPt_Match", WElecDetEta, WElecPt, wcand.DeltaPhi_EM_Recoil());
	    _histos.Fill3D("WCandMetRecoilDeltaPhiVDetEtaPt_Match", WElecDetEta, WElecPt, fabs(met_vect.DeltaPhi(wcand.GetRecoil())));
	    
	    _histos.Fill3D("WCandMtVDetEtaPt_Match_Width", WElecDetEta, WElecPt, WMt);
	    _histos.Fill3D("WCandElecPtVDetEtaPt_Match_Width", WElecDetEta, WElecPt, WElecPt);
	    _histos.Fill3D("WCandMetVDetEtaPt_Match_Width", WElecDetEta, WElecPt, WMet);
	    _histos.Fill3D("WCandPtVDetEtaPt_Match_Width", WElecDetEta, WElecPt, WPt);
	    
	    // for upara<0 and upara>0
	    if (UPara < 0) {
	      _histos.Fill3D("WCandElecPtUpara1VDetEtaPt_Match", WElecDetEta, WElecPt, WElecPt);
	      _histos.Fill3D("WCandMetUpara1VDetEtaPt_Match", WElecDetEta, WElecPt, WMet);
	      _histos.Fill3D("WCandMtUpara1VDetEtaPt_Match", WElecDetEta, WElecPt, WMt);
	      _histos.Fill3D("WCandWPtUpara1VDetEtaPt_Match", WElecDetEta, WElecPt, WPt);
	    } else {
	      _histos.Fill3D("WCandElecPtUpara2VDetEtaPt_Match", WElecDetEta, WElecPt, WElecPt);
	      _histos.Fill3D("WCandMetUpara2VDetEtaPt_Match", WElecDetEta, WElecPt, WMet);
	      _histos.Fill3D("WCandMtUpara2VDetEtaPt_Match", WElecDetEta, WElecPt, WMt);
	      _histos.Fill3D("WCandWPtUpara2VDetEtaPt_Match", WElecDetEta, WElecPt, WPt);
	    }
	    
	    // for three uT ranges
	    if(UT<5.) _histos.Fill3D("WCandMtVDetEtaPt_Match_UtBin_0", WElecDetEta, WElecPt, WMt);
	    if(UT>5. && UT<10.) _histos.Fill3D("WCandMtVDetEtaPt_Match_UtBin_1", WElecDetEta, WElecPt, WMt);
	    if(UT>10. && UT<15.) _histos.Fill3D("WCandMtVDetEtaPt_Match_UtBin_2", WElecDetEta, WElecPt, WMt);  
	  } // spatial track match
	} // for CC W events

	// fill electron pT spectrum for different eta regions (only for CC events)
	if(type==0) {
	  int FineEtaRegion_CC = emobj->FineEtaRegion_CC(_DetEtaCC);
	  char sn_FineEtaRegion_CC[10];   sprintf(sn_FineEtaRegion_CC, "%d", FineEtaRegion_CC);

	  _histos.Fill1D(TString("WCandElecPt_EtaBin_CC_")+sn_FineEtaRegion_CC, WElecPt);
	  _histos.Fill1D(TString("WCandMet_EtaBin_CC_")+sn_FineEtaRegion_CC, WMet);
	  _histos.Fill1D(TString("WCandMt_EtaBin_CC_")+sn_FineEtaRegion_CC, WMt);

	  if(good_spatial_track_match && (track_spatial!=NULL)) {
	    _histos.Fill1D(TString("WCandElecPt_Spatial_Match_EtaBin_CC_")+sn_FineEtaRegion_CC, WElecPt);
	    _histos.Fill1D(TString("WCandMet_Spatial_Match_EtaBin_CC_")+sn_FineEtaRegion_CC, WMet);
	    _histos.Fill1D(TString("WCandMt_Spatial_Match_EtaBin_CC_")+sn_FineEtaRegion_CC, WMt);
	  }

	  if(WMt>100.) {
	    _histos.Fill1D(TString("WCandElecPt_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, WElecPt);
	    _histos.Fill1D(TString("WCandMet_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, WMet);
	    _histos.Fill1D(TString("WCandMt_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, WMt);
	    if(good_spatial_track_match && (track_spatial!=NULL)) {
	      _histos.Fill1D(TString("WCandElecPt_Spatial_Match_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, WElecPt);
	      _histos.Fill1D(TString("WCandMet_Spatial_Match_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, WMet);
	      _histos.Fill1D(TString("WCandMt_Spatial_Match_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, WMt);
	    }
	  }

	  // MC study
	  if(_MCStudy) {
	    std::vector<TMBMCpart *> raw_mc_electrons;
	    if(event.get("em mc objects", raw_mc_electrons)) {   // photon-merged electrons
	      _histos.Fill1D(TString("WCandMCElecPt_EtaBin_CC_")+sn_FineEtaRegion_CC, raw_mc_electrons[0]->Pt());
	      
	      if(good_spatial_track_match && (track_spatial!=NULL)) 
		_histos.Fill1D(TString("WCandMCElecPt_Spatial_Match_EtaBin_CC_")+sn_FineEtaRegion_CC, raw_mc_electrons[0]->Pt());

	      if(WMt>100.) {
		_histos.Fill1D(TString("WCandMCElecPt_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, raw_mc_electrons[0]->Pt());
		if(good_spatial_track_match && (track_spatial!=NULL)) 
		  _histos.Fill1D(TString("WCandMCElecPt_Spatial_Match_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, raw_mc_electrons[0]->Pt());
	      }

	      //
	      // check reco-truth electron pT difference
	      //
	      if(kinem::delta_R(emobj->Eta(), emobj->Phi(), raw_mc_electrons[0]->Eta(), raw_mc_electrons[0]->Phi())<0.3) { // find smear-truth matched electron
		double pt_diff = WElecPt - raw_mc_electrons[0]->Pt();

		_histos.Fill1D(TString("WCandMCElecPtDiff_EtaBin_CC_")+sn_FineEtaRegion_CC, pt_diff);
		if(good_spatial_track_match && (track_spatial!=NULL)) 
		  _histos.Fill1D(TString("WCandMCElecPtDiff_Spatial_Match_EtaBin_CC_")+sn_FineEtaRegion_CC, pt_diff);

		if(WMt>100.) {
		  _histos.Fill1D(TString("WCandMCElecPtDiff_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, pt_diff);
		  if(good_spatial_track_match && (track_spatial!=NULL)) 
		    _histos.Fill1D(TString("WCandMCElecPtDiff_Spatial_Match_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, pt_diff);
		} // tail region
	      }

	    } // get MC particles
	  } // MC study
	}
	
	// without track match requirement
	_histos.Fill1D("WCandInstLumi", instlumi);
	_histos.Fill2D("WCandNCaloCellsVInstLumi",cells->NumCells()- emobjs[0]->getEMCluster()->ncells(),instlumi );
	_histos.Fill1D("WCandNCaloCells",cells->NumCells()-emobjs[0]->getEMCluster()->ncells() );

      
	if(_MCStudy && _MakeOverlayEventList) {
	  int ZBRunno = event.getMCEventInfo()->overlayrun();
	  int ZBEvtno = event.getMCEventInfo()->overlayevtid();
	  
	  std::ofstream olistfile("W_MC_overlay_events.txt",ios::app);
	  olistfile << ZBRunno << "  " << ZBEvtno << std::endl;
	  olistfile.close();
	}
	

        _histos.Fill1D("WCandScalarEt", WScalarEt);
        _histos.Fill1D("WCandSqrtScalarEt", sqrt(WScalarEt));
	_histos.Fill1D("WCandVtx", vtx_z);
	_histos.Fill1D("WCandPhi", WPhi);
	_histos.Fill1D("WCandElecPt", WElecPt);
	if (track_spatial!=NULL){
	  _histos.Fill1D("WCandElecTrkPt_Spatial_Match", track_spatial->Pt());
	  _histos.Fill1D("WCandElecTrkPtOvE_Spatial_Match", track_spatial->Pt()/WElecPt );
	}
	_histos.Fill1D("WCandElec_TrkPhiEM3Mod",fmod(16.*WElecPhiTrkAtEM3/3.1415926, 1.0));
	_histos.Fill1D("WCandMet", WMet);
	_histos.Fill1D("WCandMetx", WMetx);
	_histos.Fill1D("WCandMety", WMety);
	_histos.Fill1D("WCandMetPhi", WMetPhi);
	_histos.Fill1D("WCandMt", WMt);
	_histos.Fill1D("WCandPt", WPt);
	_histos.Fill1D("WCandElecPx", WElecPx);
	_histos.Fill1D("WCandElecPy", WElecPy);
	_histos.Fill1D("WCandElecEta", WElecEta);
	_histos.Fill1D("WCandElecDetEta", WElecDetEta);
 	_histos.Fill1D("WCandElecPhi", WElecPhiTrkAtDCA);//keep this histogram for bkwd compatibility
 	_histos.Fill1D("WCandElecDetPhi", WElecDetPhiCALO);//keep this histogram for bkwd compatibility
	_histos.Fill1D("WCandElecPhiTrkAtDCA", WElecPhiTrkAtDCA);
	_histos.Fill1D("WCandElecPhiTrkAtEM3", WElecPhiTrkAtEM3);
	_histos.Fill1D("WCandElecDetPhiCALO", WElecDetPhiCALO);
	_histos.Fill1D("WCandUPara", UPara);
	_histos.Fill1D("WCandUPerp", UPerp);
	_histos.Fill1D("WCandUt", UT);
	_histos.Fill1D("WCandElecMetPhi", DPhi_EM_Met);
	_histos.Fill1D("WCandElecRecPhi", DPhi_EM_Recoil);
	_histos.Fill1D("WCandRecoilPt", WRecoilPt);
	_histos.Fill1D("WCandRecoilPx", WRecoilPx);
	_histos.Fill1D("WCandRecoilPy", WRecoilPy);
	_histos.Fill1D("WCandRecoilPhi", WRecoilPhi);
	_histos.Fill1D("WCandElecMetDeltaPhi", wcand.DeltaPhi_EM_Met());
	_histos.Fill1D("WCandElecRecoilDeltaPhi", wcand.DeltaPhi_EM_Recoil());
	_histos.Fill1D("WCandMetRecoilDeltaPhi", fabs(met_vect.DeltaPhi(wcand.GetRecoil())));
	
	_histos.Fill1D(TString("WCandInstLumi_")+sn, instlumi);	
	_histos.Fill1D(TString("WCandScalarEt_")+sn, WScalarEt);
        _histos.Fill1D(TString("WCandSqrtScalarEt_")+sn, sqrt(WScalarEt));
	_histos.Fill1D(TString("WCandVtx_")+sn, vtx_z);
	_histos.Fill1D(TString("WCandPhi_")+sn, WPhi);
	_histos.Fill1D(TString("WCandElecPt_")+sn, WElecPt);
	_histos.Fill1D(TString("WCandMet_")+sn, WMet);
	_histos.Fill1D(TString("WCandMetx_")+sn, WMetx);
	_histos.Fill1D(TString("WCandMety_")+sn, WMety);
	_histos.Fill1D(TString("WCandMetPhi_")+sn, WMetPhi);
	_histos.Fill1D(TString("WCandMt_")+sn, WMt);
	_histos.Fill1D(TString("WCandPt_")+sn, WPt);
	_histos.Fill1D(TString("WCandElecPx_")+sn, WElecPx);
	_histos.Fill1D(TString("WCandElecPy_")+sn, WElecPy);
	_histos.Fill1D(TString("WCandElecEta_")+sn, WElecEta);
	_histos.Fill1D(TString("WCandElecDetEta_")+sn, WElecDetEta);
 	_histos.Fill1D(TString("WCandElecPhi_")+sn, WElecPhiTrkAtDCA);//keep this histogram for bkwd compatibility
 	_histos.Fill1D(TString("WCandElecDetPhi_")+sn, WElecDetPhiCALO);//keep this histogram for bkwd compatibility
	_histos.Fill1D(TString("WCandElecPhiTrkAtDCA_")+sn, WElecPhiTrkAtDCA);
	_histos.Fill1D(TString("WCandElecPhiTrkAtEM3_")+sn, WElecPhiTrkAtEM3);
	_histos.Fill1D(TString("WCandElecDetPhiCALO_")+sn, WElecDetPhiCALO);
	_histos.Fill1D(TString("WCandUPara_")+sn, UPara);
	_histos.Fill1D(TString("WCandUPerp_")+sn, UPerp);
	_histos.Fill1D(TString("WCandUt_")+sn, UT);
	_histos.Fill1D(TString("WCandElecMetPhi_")+sn, DPhi_EM_Met);
	_histos.Fill1D(TString("WCandElecRecPhi_")+sn, DPhi_EM_Recoil);
	_histos.Fill1D(TString("WCandRecoilPt_")+sn, WRecoilPt);
	_histos.Fill1D(TString("WCandRecoilPx_")+sn, WRecoilPx);
	_histos.Fill1D(TString("WCandRecoilPy_")+sn, WRecoilPy);
	_histos.Fill1D(TString("WCandRecoilPhi_")+sn, WRecoilPhi);
	_histos.Fill1D(TString("WCandElecMetDeltaPhi_")+sn, wcand.DeltaPhi_EM_Met());
	_histos.Fill1D(TString("WCandElecRecoilDeltaPhi_")+sn, wcand.DeltaPhi_EM_Recoil());
	_histos.Fill1D(TString("WCandMetRecoilDeltaPhi_")+sn, fabs(met_vect.DeltaPhi(wcand.GetRecoil())));

        // for W width measurement
	if(WMt>50. && WMt<200.) {
           _histos.Fill1D("WCandElecPt_Width", WElecPt);
           _histos.Fill1D("WCandMet_Width", WMet);
           _histos.Fill1D("WCandMt_Width", WMt);
           _histos.Fill1D("WCandPt_Width", WPt);
	
           _histos.Fill1D(TString("WCandElecPt_Width_")+sn, WElecPt);
           _histos.Fill1D(TString("WCandMet_Width_")+sn, WMet);
           _histos.Fill1D(TString("WCandMt_Width_")+sn, WMt);
           _histos.Fill1D(TString("WCandPt_Width_")+sn, WPt);
           
           // for tail region
           if(WMt>100. && WMt<200.) {
             _histos.Fill1D("WCandElecPt_Tail_Width", WElecPt);
             _histos.Fill1D("WCandMet_Tail_Width", WMet);
             _histos.Fill1D("WCandMt_Tail_Width", WMt);
             _histos.Fill1D("WCandPt_Tail_Width", WPt);
	
             _histos.Fill1D(TString("WCandElecPt_Tail_Width_")+sn, WElecPt);
             _histos.Fill1D(TString("WCandMet_Tail_Width_")+sn, WMet);
             _histos.Fill1D(TString("WCandMt_Tail_Width_")+sn, WMt);
             _histos.Fill1D(TString("WCandPt_Tail_Width_")+sn, WPt);
           }
        }

	if (UPara < 0) {
	  _histos.Fill1D("WCandElecPtUpara1", WElecPt);
	  _histos.Fill1D("WCandMetUpara1", WMet);
	  _histos.Fill1D("WCandMtUpara1", WMt);
	  _histos.Fill1D("WCandWPtUpara1", WPt);
	  
	  _histos.Fill1D(TString("WCandElecPtUpara1_")+sn, WElecPt);
	  _histos.Fill1D(TString("WCandMetUpara1_")+sn, WMet);
	  _histos.Fill1D(TString("WCandMtUpara1_")+sn, WMt);
	  _histos.Fill1D(TString("WCandWPtUpara1_")+sn, WPt);
	} else {
	  _histos.Fill1D("WCandElecPtUpara2", WElecPt);
	  _histos.Fill1D("WCandMetUpara2", WMet);
	  _histos.Fill1D("WCandMtUpara2", WMt);
	  _histos.Fill1D("WCandWPtUpara2", WPt);
	  
	  _histos.Fill1D(TString("WCandElecPtUpara2_")+sn, WElecPt);
	  _histos.Fill1D(TString("WCandMetUpara2_")+sn, WMet);
	  _histos.Fill1D(TString("WCandMtUpara2_")+sn, WMt);
	  _histos.Fill1D(TString("WCandWPtUpara2_")+sn, WPt);
	}
        
	if(type==0){
	  _histos.Fill2D(TString("WCandMt_vs_DetEta_")+bins_Vtx,WElecDetEta, WMt);
	  _histos.Fill2D(TString("WCandElecPt_vs_DetEta_")+bins_Vtx,WElecDetEta, WElecPt);
	  _histos.Fill2D(TString("WCandMet_vs_DetEta_")+bins_Vtx,WElecDetEta, WMet);
	}

        // Mt, electron pT, Met and WPt vs electron detector eta (used for matrix method)
        _histos.Fill2D("WCandMtVElecDetEta", WElecDetEta, WMt);
        _histos.Fill2D("WCandElecPtVElecDetEta", WElecDetEta, WElecPt);
        _histos.Fill2D("WCandMetVElecDetEta", WElecDetEta, WMet);
        _histos.Fill2D("WCandPtVElecDetEta", WElecDetEta, WPt);
	
	// require the electron must have a spatial matched track with at least one SMT hit and pT>10GeV
        // if you use partial read mode, sometimes track_spatial = NULL even we require good_spatial_track_match 
	if(good_spatial_track_match && (track_spatial!=NULL)) {
	  _histos.Fill1D("WCandInstLumi_Spatial_Match", instlumi);
	  _histos.FillProfile(string("WCandScalarEt_V_Lumi_")+sn, instlumi,WScalarEt);
	  _histos.Fill2D(string("WCandScalarEt_V_Lumi2D_")+sn, instlumi,WScalarEt);
	  _histos.Fill1D("WCandScalarEt_Spatial_Match", WScalarEt);
	  _histos.Fill1D("WCandSqrtScalarEt_Spatial_Match", sqrt(WScalarEt));
	  _histos.Fill2D("WCandScalarEtVElecPt_Spatial_Match", WElecPt, WScalarEt);
	  _histos.Fill1D("WCandVtx_Spatial_Match", vtx_z);
	  _histos.Fill1D("WCandPhi_Spatial_Match", WPhi);
	  _histos.Fill1D("WCandElecPt_Spatial_Match", WElecPt);
	  _histos.Fill1D("WCandElecTrkPt_Spatial_Match", track_spatial->Pt());
	  _histos.Fill1D("WCandElecTrkPtOvE_Spatial_Match", track_spatial->Pt()/WElecPt );
	  _histos.Fill1D("WCandElec_TrkPhiEM3Mod_Spatial_Match",fmod(16.*WElecPhiTrkAtEM3/3.1415926, 1.0));
	  _histos.Fill1D("WCandMet_Spatial_Match", WMet);
	  _histos.Fill1D("WCandMetx_Spatial_Match", WMetx);
	  _histos.Fill1D("WCandMety_Spatial_Match", WMety);
	  _histos.Fill1D("WCandMetPhi_Spatial_Match", WMetPhi);
	  _histos.Fill1D("WCandMt_Spatial_Match", WMt);
	  _histos.Fill1D("WCandPt_Spatial_Match", WPt);
	  _histos.Fill1D("WCandElecPx_Spatial_Match", WElecPx);
	  _histos.Fill1D("WCandElecPy_Spatial_Match", WElecPy);
	  _histos.Fill1D("WCandElecEta_Spatial_Match", WElecEta);
	  _histos.Fill1D("WCandElecDetEta_Spatial_Match", WElecDetEta);
 	  _histos.Fill1D("WCandElecPhi_Spatial_Match", WElecPhiTrkAtDCA);//keep this histogram for bkwd compatibility
 	  _histos.Fill1D("WCandElecDetPhi_Spatial_Match", WElecDetPhiCALO);//keep this histogram for bkwd compatibility
	  _histos.Fill1D("WCandElecPhiTrkAtDCA_Spatial_Match", WElecPhiTrkAtDCA);
	  _histos.Fill1D("WCandElecPhiTrkAtEM3_Spatial_Match", WElecPhiTrkAtEM3);
	  _histos.Fill1D("WCandElecDetPhiCALO_Spatial_Match", WElecDetPhiCALO);
	  _histos.Fill1D("WCandUPara_Spatial_Match", UPara);
	  _histos.Fill1D("WCandUPerp_Spatial_Match", UPerp);
	  _histos.Fill1D("WCandUt_Spatial_Match", UT);
	  _histos.Fill1D("WCandElecMetPhi_Spatial_Match", DPhi_EM_Met);
	  _histos.Fill1D("WCandElecRecPhi_Spatial_Match", DPhi_EM_Recoil);
	  _histos.Fill1D("WCandRecoilPt_Spatial_Match", WRecoilPt);
	  _histos.Fill1D("WCandRecoilPx_Spatial_Match", WRecoilPx);
	  _histos.Fill1D("WCandRecoilPy_Spatial_Match", WRecoilPy);
	  _histos.Fill1D("WCandRecoilPhi_Spatial_Match", WRecoilPhi);
	  _histos.Fill1D("WCandElecMetDeltaPhi_Spatial_Match", wcand.DeltaPhi_EM_Met());
	  _histos.Fill1D("WCandElecRecoilDeltaPhi_Spatial_Match", wcand.DeltaPhi_EM_Recoil());
	  _histos.Fill1D("WCandMetRecoilDeltaPhi_Spatial_Match", fabs(met_vect.DeltaPhi(wcand.GetRecoil())));
	  

	  _histos.Fill1D(TString("WCandInstLumi_Spatial_Match_")+sn, instlumi);
	  _histos.Fill1D(TString("WCandScalarEt_Spatial_Match_")+sn, WScalarEt);
	  _histos.Fill1D(TString("WCandSqrtScalarEt_Spatial_Match_")+sn, sqrt(WScalarEt));
	  _histos.Fill2D(TString("WCandScalarEtVElecPt_Spatial_Match_")+sn, WElecPt, WScalarEt);
	  _histos.Fill1D(TString("WCandVtx_Spatial_Match_")+sn, vtx_z);
	  _histos.Fill1D(TString("WCandPhi_Spatial_Match_")+sn, WPhi);
	  _histos.Fill1D(TString("WCandElecPt_Spatial_Match_")+sn, WElecPt);
	  _histos.Fill1D(TString("WCandElecTrkPt_Spatial_Match_")+sn, track_spatial->Pt());
	  _histos.Fill1D(TString("WCandElecTrkPtOvE_Spatial_Match_")+sn, track_spatial->Pt()/WElecPt );
	  _histos.Fill1D(TString("WCandElec_TrkPhiEM3Mod_Spatial_Match_")+sn,fmod(16.*WElecPhiTrkAtEM3/3.1415926, 1.0));
	  _histos.Fill1D(TString("WCandMet_Spatial_Match_")+sn, WMet);
	  _histos.Fill1D(TString("WCandMetx_Spatial_Match_")+sn, WMetx);
	  _histos.Fill1D(TString("WCandMety_Spatial_Match_")+sn, WMety);
	  _histos.Fill1D(TString("WCandMetPhi_Spatial_Match_")+sn, WMetPhi);
	  _histos.Fill1D(TString("WCandMt_Spatial_Match_")+sn, WMt);
	  _histos.Fill1D(TString("WCandPt_Spatial_Match_")+sn, WPt);	  
	  _histos.Fill1D(TString("WCandElecPx_Spatial_Match_")+sn, WElecPx);
	  _histos.Fill1D(TString("WCandElecPy_Spatial_Match_")+sn, WElecPy);
	  _histos.Fill1D(TString("WCandElecEta_Spatial_Match_")+sn, WElecEta);
	  _histos.Fill1D(TString("WCandElecDetEta_Spatial_Match_")+sn, WElecDetEta);
 	  _histos.Fill1D(TString("WCandElecPhi_Spatial_Match_")+sn,    WElecPhiTrkAtDCA);//keep this histogram for bkwd compatibility
 	  _histos.Fill1D(TString("WCandElecDetPhi_Spatial_Match_")+sn, WElecDetPhiCALO);//keep this histogram for bkwd compatibility 	   
	  _histos.Fill1D(TString("WCandElecPhiTrkAtDCA_Spatial_Match_")+sn, WElecPhiTrkAtDCA);
	  _histos.Fill1D(TString("WCandElecPhiTrkAtEM3_Spatial_Match_")+sn, WElecPhiTrkAtEM3);
	  _histos.Fill1D(TString("WCandElecDetPhiCALO_Spatial_Match_")+sn, WElecDetPhiCALO);	  
	  _histos.Fill1D(TString("WCandUPara_Spatial_Match_")+sn, UPara);
	  _histos.Fill1D(TString("WCandUPerp_Spatial_Match_")+sn, UPerp);
	  _histos.Fill1D(TString("WCandUt_Spatial_Match_")+sn, UT);
	  _histos.Fill1D(TString("WCandElecMetPhi_Spatial_Match_")+sn, DPhi_EM_Met);
	  _histos.Fill1D(TString("WCandElecRecPhi_Spatial_Match_")+sn, DPhi_EM_Recoil);
	  _histos.Fill1D(TString("WCandRecoilPt_Spatial_Match_")+sn, WRecoilPt);
	  _histos.Fill1D(TString("WCandRecoilPx_Spatial_Match_")+sn, WRecoilPx);
	  _histos.Fill1D(TString("WCandRecoilPy_Spatial_Match_")+sn, WRecoilPy);
	  _histos.Fill1D(TString("WCandRecoilPhi_Spatial_Match_")+sn, WRecoilPhi);
	  _histos.Fill1D(TString("WCandElecMetDeltaPhi_Spatial_Match_")+sn, wcand.DeltaPhi_EM_Met());
	  _histos.Fill1D(TString("WCandElecRecoilDeltaPhi_Spatial_Match_")+sn, wcand.DeltaPhi_EM_Recoil());
	  _histos.Fill1D(TString("WCandMetRecoilDeltaPhi_Spatial_Match_")+sn, fabs(met_vect.DeltaPhi(wcand.GetRecoil())));
	 
          // for W width measurement
	  if(WMt>50. && WMt<200.) {
             _histos.Fill1D("WCandElecPt_Spatial_Match_Width", WElecPt);
             _histos.Fill1D("WCandMet_Spatial_Match_Width", WMet);
             _histos.Fill1D("WCandMt_Spatial_Match_Width", WMt);
             _histos.Fill1D("WCandPt_Spatial_Match_Width", WPt);
	
             _histos.Fill1D(TString("WCandElecPt_Spatial_Match_Width_")+sn, WElecPt);
             _histos.Fill1D(TString("WCandMet_Spatial_Match_Width_")+sn, WMet);
             _histos.Fill1D(TString("WCandMt_Spatial_Match_Width_")+sn, WMt);
             _histos.Fill1D(TString("WCandPt_Spatial_Match_Width_")+sn, WPt);
	  
             // for tail region
             if(WMt>100. && WMt<200.) {
               _histos.Fill1D("WCandElecPt_Spatial_Match_Tail_Width", WElecPt);
               _histos.Fill1D("WCandMet_Spatial_Match_Tail_Width", WMet);
               _histos.Fill1D("WCandMt_Spatial_Match_Tail_Width", WMt);
               _histos.Fill1D("WCandPt_Spatial_Match_Tail_Width", WPt);
	
               _histos.Fill1D(TString("WCandElecPt_Spatial_Match_Tail_Width_")+sn, WElecPt);
               _histos.Fill1D(TString("WCandMet_Spatial_Match_Tail_Width_")+sn, WMet);
               _histos.Fill1D(TString("WCandMt_Spatial_Match_Tail_Width_")+sn, WMt);
               _histos.Fill1D(TString("WCandPt_Spatial_Match_Tail_Width_")+sn, WPt);
             }
          }

	  if (_ZEEbkgStudyTruth&&(type==0)) {
	    TMBMCpart* jZ=0;
            TMBMCpart* jE1=0;
            TMBMCpart* jE2=0;
            //
	    cafe::Collection<TMBMCpart> mc = event.getMCParticles();
            for (cafe::Collection<TMBMCpart>::iterator it = mc.begin(); it!= mc.end(); ++it) {
              const TMBMCpart* daParent=0;
              if (it->getPMCvtx()) {
                if (it->getPMCvtx()->nparents()) {
                  daParent=it->getPMCvtx()->getParent(0);
                }
              }
              if (abs(it->pdgid())==23) {
                if (!jZ) jZ=&(*it);
              }
              if ((abs(it->pdgid())==11)&&daParent) {
                if (abs(daParent->pdgid())==23) {
                  if (!jE1) {
                    jE1=&(*it);
                  } else if (!jE2) {
                    jE2=&(*it);
                  }
                }
              }
	    }
	    //
	    cout<<"GREPME "<<runNo<<" "<<evtNo<<" "<<instlumi<<" "<<WScalarEt<<" "
                <<wcand.Pt()<<" "<<wcand.vect2().Phi()<<" "<<wcand.GetRecoil().Mod()<<" "<<wcand.GetRecoil().Phi()<<" "
                <<emobjs[0]->Pt()<<" "<<emobjs[0]->Eta()<<" "<<emobjs[0]->Phi()<<" "
                <<jZ->Pt()<<" "<<jZ->Eta()<<" "<<jZ->Phi()<<" "
                <<jE1->Pt()<<" "<<jE1->Eta()<<" "<<jE1->Phi()<<" "
                <<jE2->Pt()<<" "<<jE2->Eta()<<" "<<jE2->Phi()<<endl;
	  }

	  if (_ZEEbkgStudy&&(type==0)) {
	    (*_bkg_file_txt)<<runNo<<" "<<evtNo<<" "<<instlumi<<" "<<WScalarEt<<" "
                            <<wcand.Pt()<<" "<<wcand.vect2().Phi()<<" "<<wcand.GetRecoil().Mod()<<" "<<wcand.GetRecoil().Phi()<<" "
                            <<emobjs[0]->Pt()<<" "<<emobjs[0]->Eta()<<" "<<emobjs[0]->Phi()<<" ";
            if (emobjs[0]->getPtrChp()) {
              (*_bkg_file_txt)<<emobjs[0]->getPtrChp()->charge()<<endl;
            } else {
              (*_bkg_file_txt)<<"-2"<<endl;
            }
            (*_bkg_file_txt)<<vtx_x<<" "<<vtx_y<<" "<<vtx_z<<endl;
	    cafe::Collection<TMBTrack> trks = event.getTracks();
            (*_bkg_file_txt)<<trks.size()<<endl;
            for (cafe::Collection<TMBTrack>::iterator it = trks.begin(); it!= trks.end(); ++it) {
              (*_bkg_file_txt)
                <<it->Pt()<<" "<<it->Eta()<<" "<<it->Phi()<<" "
                <<it->charge()<<" "<<it->rdca()<<" "<<it->z()<<" "<<it->nhit()<<" "<<it->ncft()<<" "<<it->nsmt()<<" "<<it->hitmask(0)<<" "<<it->hitmask(1)<<" "<<it->hitmask(2)<<endl;
              const TMBIsoTrack* isotrk=it->getIsoTrk();
              if (!isotrk) {
                (*_bkg_file_txt)<<"0"<<endl;
              } else {
                (*_bkg_file_txt)<<"1"<<endl;
                for (Int_t i=0; i<14; i++) {
                  (*_bkg_file_txt)<<isotrk->e_mtc(i);
                  if (i<13) (*_bkg_file_txt)<<" ";
                  else (*_bkg_file_txt)<<endl;
                }
                (*_bkg_file_txt)<<isotrk->e33(0)<<" "<<isotrk->e33(1)<<" "<<isotrk->e33(2)<<endl;
                (*_bkg_file_txt)<<isotrk->e55(0)<<" "<<isotrk->e55(1)<<" "<<isotrk->e55(2)<<endl;
              }
            }

	  }

	  if(type==0){
	    _histos.Fill2D(TString("WCandMt_vs_DetEta_Spatial_Match_")+bins_Vtx,WElecDetEta, WMt);
	    _histos.Fill2D(TString("WCandElecPt_vs_DetEta_Spatial_Match_")+bins_Vtx,WElecDetEta, WElecPt);
	    _histos.Fill2D(TString("WCandMet_vs_DetEta_Spatial_Match_")+bins_Vtx,WElecDetEta, WMet);

	    if(UT<5.)
	      _histos.Fill1D("WCandMt_UtBin_Spatial_Match_0", WMt);
	    if(UT>5. && UT<10.)
	      _histos.Fill1D("WCandMt_UtBin_Spatial_Match_1", WMt);
	    if(UT>10. && UT<15.)
	      _histos.Fill1D("WCandMt_UtBin_Spatial_Match_2", WMt);	    
	  }

          // Mt, electron pT and Met vs electron detector eta
          _histos.Fill2D("WCandMtVElecDetEta_Spatial_Match", WElecDetEta, WMt);
          _histos.Fill2D("WCandElecPtVElecDetEta_Spatial_Match", WElecDetEta, WElecPt);
          _histos.Fill2D("WCandMetVElecDetEta_Spatial_Match", WElecDetEta, WMet);
          _histos.Fill2D("WCandPtVElecDetEta_Spatial_Match", WElecDetEta, WPt);
 
	  if (UPara < 0) {
	    _histos.Fill1D("WCandElecPtUpara1_Spatial_Match", WElecPt);
	    _histos.Fill1D("WCandMetUpara1_Spatial_Match", WMet);
	    _histos.Fill1D("WCandMtUpara1_Spatial_Match", WMt);
	    _histos.Fill1D("WCandWPtUpara1_Spatial_Match", WPt);

	    _histos.Fill1D(TString("WCandElecPtUpara1_Spatial_Match_")+sn, WElecPt);
	    _histos.Fill1D(TString("WCandMetUpara1_Spatial_Match_")+sn, WMet);
	    _histos.Fill1D(TString("WCandMtUpara1_Spatial_Match_")+sn, WMt);
	    _histos.Fill1D(TString("WCandWPtUpara1_Spatial_Match_")+sn, WPt);
	  } else {
	    _histos.Fill1D("WCandElecPtUpara2_Spatial_Match", WElecPt);
	    _histos.Fill1D("WCandMetUpara2_Spatial_Match", WMet);
	    _histos.Fill1D("WCandMtUpara2_Spatial_Match", WMt);
	    _histos.Fill1D("WCandWPtUpara2_Spatial_Match", WPt);

	    _histos.Fill1D(TString("WCandElecPtUpara2_Spatial_Match_")+sn, WElecPt);
	    _histos.Fill1D(TString("WCandMetUpara2_Spatial_Match_")+sn, WMet);
	    _histos.Fill1D(TString("WCandMtUpara2_Spatial_Match_")+sn, WMt);
	    _histos.Fill1D(TString("WCandWPtUpara2_Spatial_Match_")+sn, WPt);
	  }
	  
	  _histos.Fill2D("WCandElecPt_V_Upara", WElecPt,UPara);	  
	  _histos.FillProfile("WCandWPtUpara", WPt, UPara);
	  _histos.FillProfile("WCandElecPtUpara", WElecPt, UPara);
	  _histos.FillProfile("WCandMetUpara", WMet, UPara);
	  _histos.FillProfile("WCandMtUpara", WMt, UPara);

	  _histos.FillProfile(TString("WCandWPtUpara_")+sn, WPt, UPara);
	  _histos.FillProfile(TString("WCandElecPtUpara_")+sn, WElecPt, UPara);
	  _histos.FillProfile(TString("WCandMetUpara_")+sn, WMet, UPara);
	  _histos.FillProfile(TString("WCandMtUpara_")+sn, WMt, UPara);

	  // fill variables for different recoil pT regions
	  // with good spatial track matching requirement
	  if(type == 0) {
	    int bin = wz_utils::pTee_Eta_Bin(WPt);
	    char recoilPt_bin_sn[10]; sprintf(recoilPt_bin_sn, "%d", bin);

	    if(bin >= 0) {
	      _histos.Fill1D(string("WCandMt_RecoilBin_")+recoilPt_bin_sn, WMt);
	      _histos.Fill1D(string("WCandElecPt_RecoilBin_")+recoilPt_bin_sn, WElecPt);
	      _histos.Fill1D(string("WCandMet_RecoilBin_")+recoilPt_bin_sn, WMet);
	      _histos.Fill1D(TString("WCandElecMetDeltaPhi_RecoilBin_")+recoilPt_bin_sn, wcand.DeltaPhi_EM_Met());
	      _histos.Fill1D(TString("WCandElecRecoilDeltaPhi_RecoilBin_")+recoilPt_bin_sn, wcand.DeltaPhi_EM_Recoil());
	      _histos.Fill1D(TString("WCandMetRecoilDeltaPhi_RecoilBin_")+recoilPt_bin_sn, met_vect.DeltaPhi(wcand.GetRecoil()));	      	      
	      _histos.Fill1D(string("WCandRecoilPhi_RecoilBin_")+recoilPt_bin_sn, WRecoilPhi);
	      _histos.Fill1D(string("WCandUPara_RecoilBin_")+recoilPt_bin_sn, UPara);
	      _histos.Fill1D(string("WCandUPerp_RecoilBin_")+recoilPt_bin_sn, UPerp);
	      _histos.Fill1D(string("WCandVtx_RecoilBin_")+recoilPt_bin_sn, vtx_z);
	      _histos.Fill1D(string("WCandPhi_RecoilBin_")+recoilPt_bin_sn, WPhi);
	      _histos.Fill1D(string("WCandInstLumi_RecoilBin_")+recoilPt_bin_sn, instlumi);
	      _histos.Fill1D(string("WCandWScalarEt_RecoilBin_")+recoilPt_bin_sn, WScalarEt);
	    }
	    
	  } // type==0
	  
	  // E/P studies for CC region and StudyEOverP and spatial track match
	  if(_StudyEOverP && type==0) EOverPStudies(emobj, polarity);
	} // good spatial track match

      }// pass WUt cut
    } // pass EM, MET cuts
    
    // do some MC studies for CC W candidate
    if(_MCStudy && WCCCand) MCStudies(event);
    
  } // get pointers to EM and MET selector
  
  return true;   
}

//
// E/P studies for CC electrons with good spatial track match
//
void WAnalysis::EOverPStudies(const CAFEMObj* emobj, int solpol) {
  const TMBTrack *track_spatial = emobj->getPtrSpatialChp();

  int nsmt = track_spatial->nsmt();
  int ncft = track_spatial->ncft();
  double chi2 = track_spatial->getChi2Ndf();

  // add more requirement on the track to remove QCD background
  if(nsmt>1 && ncft>8 && chi2<3.3) {
    
    // find the phimod for each electron, mod_phi is only meaningful for CC electron
    int mod_phi = emobj->PhiModule();
    if(mod_phi>31) mod_phi = 31;
    char sn_mod[10];   sprintf(sn_mod, "%d", mod_phi);

    // track phi
    double TrkPhi = track_spatial->Phi();
    int mod_trkphi = (int)(16*TrkPhi/3.1415926);
    if(mod_trkphi>31) mod_trkphi = 31;
    char sn_trkmod[10]; sprintf(sn_trkmod, "%d", mod_trkphi);
    
    double WElecPt = emobj->Pt();
    double WElecEta = emobj->Eta();
    double WElecDetEta = emobj->CalDetectorEta();
    double WElecPhiTrkAtDCA = emobj->Phi();
    double WElecDetPhiCALO = emobj->CalDetectorPhi();	

    double WElecPhiMod = fmod(16.*WElecDetPhiCALO/3.1415926, 1.0);
    double WElecTrkPhiMod = fmod(16.*TrkPhi/3.1415926, 1.0);

    // extrapolate track to EM3 layer
    double WElecPhiTrkAtEM3 = emobj->TrkPhiEM3();
    double WElecTrkPhiModEM3 = fmod(16.*WElecPhiTrkAtEM3/3.1415926, 1.0);
    
    // calculate E/p
    double EOverP = WElecPt/track_spatial->Pt();
    double RawEOverP = EOverP * emobj->uncorrE()/emobj->E();
    
    _histos.Fill1D("WCandEOverP", EOverP);	  
    _histos.Fill1D("WCandRawEOverP", RawEOverP);	  
    _histos.Fill1D(TString("WCandEOverP_Mod_")+sn_mod, EOverP);
    _histos.Fill1D(TString("WCandEOverP_TrkMod_")+sn_trkmod, EOverP);
    _histos.Fill1D(TString("WCandRawEOverP_Mod_")+sn_mod, RawEOverP);
    _histos.Fill1D(TString("WCandRawEOverP_TrkMod_")+sn_trkmod, RawEOverP);
    
    // get physics eta bins
    int eta_bin = -1;
    if(WElecEta<-1.) eta_bin = 0;
    else if(WElecEta>=1.) eta_bin = 21;
    else {
      double tmp = WElecEta + 1.;
      eta_bin = (int)(floor(tmp/0.1)+1);
    }
    char etaBinChar[10];   sprintf(etaBinChar, "%d", eta_bin);
    
    // get detector eta bins
    int deteta_bin = -1;
    if(WElecDetEta<-1.) deteta_bin = 0;
    else if(WElecDetEta>=1.) deteta_bin = 21;
    else {
      double tmp = WElecDetEta + 1.;
      deteta_bin = (int)(floor(tmp/0.1)+1);
    }	      
    char detetaBinChar[10];  sprintf(detetaBinChar, "%d", deteta_bin);
    
    // get physics phi bins
    int phi_bin = -1;
    phi_bin = (int)(floor(WElecPhiTrkAtDCA/0.2));

    if(phi_bin>31) phi_bin = 31;	      
    char phiBinChar[10];  sprintf(phiBinChar, "%d", phi_bin);
    
    if(track_spatial->charge() == -1) {
      if(solpol == 1) {
	_histos.Fill1D("WCandEOverP_Electron_PosSolPol", EOverP);
	_histos.Fill1D("WCandEt_Electron_PosSolPol", WElecPt);
	_histos.Fill1D("WCandPt_Electron_PosSolPol", track_spatial->Pt());
	_histos.Fill1D(string("WCandEOverP_Electron_PosSolPol_Eta_")+etaBinChar, EOverP);
	_histos.Fill1D(string("WCandEOverP_Electron_PosSolPol_DetEta_")+detetaBinChar, EOverP);
	_histos.Fill1D(string("WCandEOverP_Electron_PosSolPol_Phi_")+phiBinChar, EOverP);
	
	_histos.FillProfile("WCandEOverP_V_TrkPhi_Electron_PosSolPol", track_spatial->Phi(), EOverP);
	_histos.FillProfile("WCandEOverP_V_EMPhi_Electron_PosSolPol", emobj->CalPhi(), EOverP);
	_histos.FillProfile("WCandEOverP_V_EMEta_Electron_PosSolPol", WElecEta, EOverP);
      } else if(solpol == -1) {
	_histos.Fill1D("WCandEOverP_Electron_NegSolPol", EOverP);
	_histos.Fill1D("WCandEt_Electron_NegSolPol", WElecPt);
	_histos.Fill1D("WCandPt_Electron_NegSolPol", track_spatial->Pt());
	_histos.Fill1D(string("WCandEOverP_Electron_NegSolPol_Eta_")+etaBinChar, EOverP);
	_histos.Fill1D(string("WCandEOverP_Electron_NegSolPol_DetEta_")+detetaBinChar, EOverP);
	_histos.Fill1D(string("WCandEOverP_Electron_NegSolPol_Phi_")+phiBinChar, EOverP);
	
	_histos.FillProfile("WCandEOverP_V_TrkPhi_Electron_NegSolPol", track_spatial->Phi(), EOverP);
	_histos.FillProfile("WCandEOverP_V_EMPhi_Electron_NegSolPol", emobj->CalPhi(), EOverP);
	_histos.FillProfile("WCandEOverP_V_EMEta_Electron_NegSolPol", WElecEta, EOverP);
      }
    } else if (track_spatial->charge() == 1) {
      if(solpol == 1) {
	_histos.Fill1D("WCandEOverP_Positron_PosSolPol", EOverP);
	_histos.Fill1D("WCandEt_Positron_PosSolPol", WElecPt);
	_histos.Fill1D("WCandPt_Positron_PosSolPol", track_spatial->Pt());
	_histos.Fill1D(string("WCandEOverP_Positron_PosSolPol_Eta_")+etaBinChar, EOverP);
	_histos.Fill1D(string("WCandEOverP_Positron_PosSolPol_DetEta_")+detetaBinChar, EOverP);
	_histos.Fill1D(string("WCandEOverP_Positron_PosSolPol_Phi_")+phiBinChar, EOverP);
	
	_histos.FillProfile("WCandEOverP_V_TrkPhi_Positron_PosSolPol", track_spatial->Phi(), EOverP);
	_histos.FillProfile("WCandEOverP_V_EMPhi_Positron_PosSolPol", emobj->CalPhi(), EOverP);
	_histos.FillProfile("WCandEOverP_V_EMEta_Positron_PosSolPol", WElecEta, EOverP);
      } else if (solpol == -1) {
	_histos.Fill1D("WCandEOverP_Positron_NegSolPol", EOverP);
	_histos.Fill1D("WCandEt_Positron_NegSolPol", WElecPt);
	_histos.Fill1D("WCandPt_Positron_NegSolPol", track_spatial->Pt());
	_histos.Fill1D(string("WCandEOverP_Positron_NegSolPol_Eta_")+etaBinChar, EOverP);
	_histos.Fill1D(string("WCandEOverP_Positron_NegSolPol_DetEta_")+detetaBinChar, EOverP);
	_histos.Fill1D(string("WCandEOverP_Positron_NegSolPol_Phi_")+phiBinChar, EOverP);
	
	_histos.FillProfile("WCandEOverP_V_TrkPhi_Positron_NegSolPol", track_spatial->Phi(), EOverP);
	_histos.FillProfile("WCandEOverP_V_EMPhi_Positron_NegSolPol", emobj->CalPhi(), EOverP);
	_histos.FillProfile("WCandEOverP_V_EMEta_Positron_NegSolPol", WElecEta, EOverP);
      }
    }

    // calorimeter phi mod position
    int calphimodPosition_bin = -1;
    if(calphimodPosition_bin>39) calphimodPosition_bin = 39;
    calphimodPosition_bin = (int)(WElecPhiMod/(1/40.));
    char sn_CalPhiModPosition[10];   sprintf(sn_CalPhiModPosition, "%d", calphimodPosition_bin);
    
    // track phimod at DCA
    int trkphimodPosition_bin = -1;
    trkphimodPosition_bin = (int)(WElecTrkPhiMod/(1/40.));
    if(trkphimodPosition_bin>39) trkphimodPosition_bin = 39;
    char sn_TrkPhiModPosition[10];   sprintf(sn_TrkPhiModPosition, "%d", trkphimodPosition_bin);

    // track phimod at EM3
    int trkphimodEM3Position_bin = -1;
    trkphimodEM3Position_bin = (int)(WElecTrkPhiModEM3/(1/40.));
    if(trkphimodEM3Position_bin>39) trkphimodEM3Position_bin = 39;
    char sn_TrkPhiModEM3Position[10];   sprintf(sn_TrkPhiModEM3Position, "%d", trkphimodEM3Position_bin);

    // check phimod for electron and positron
    _histos.Fill1D("WCandElecEMPhiMod", WElecPhiMod);
    _histos.Fill1D("WCandElecTrkPhiMod", WElecTrkPhiMod);
    _histos.Fill1D("WCandElecTrkPhiModEM3", WElecTrkPhiModEM3);
    if(track_spatial->charge()==1) {
      _histos.Fill1D("WCandElecEMPhiMod_Posi", WElecPhiMod);
      _histos.Fill1D("WCandElecTrkPhiMod_Posi", WElecTrkPhiMod);
      _histos.Fill1D("WCandElecTrkPhiModEM3_Posi", WElecTrkPhiModEM3);
    }  
    if(track_spatial->charge()==-1) {
      _histos.Fill1D("WCandElecEMPhiMod_Elec", WElecPhiMod);
      _histos.Fill1D("WCandElecTrkPhiMod_Elec", WElecTrkPhiMod);
      _histos.Fill1D("WCandElecTrkPhiModEM3_Elec", WElecTrkPhiModEM3);
    }  
    if((track_spatial->charge()*solpol)==1) {
      _histos.Fill1D("WCandElecEMPhiMod_Posi_QSolpol", WElecPhiMod);
      _histos.Fill1D("WCandElecTrkPhiMod_Posi_QSolpol", WElecTrkPhiMod);
      _histos.Fill1D("WCandElecTrkPhiModEM3_Posi_QSolpol", WElecTrkPhiModEM3);
    }  
    if((track_spatial->charge()*solpol)==-1) {
      _histos.Fill1D("WCandElecEMPhiMod_Elec_QSolpol", WElecPhiMod);
      _histos.Fill1D("WCandElecTrkPhiMod_Elec_QSolpol", WElecTrkPhiMod);
      _histos.Fill1D("WCandElecTrkPhiModEM3_Elec_QSolpol", WElecTrkPhiModEM3);
    }  

    // for forward polarity
    if(solpol==1) {
      if(track_spatial->charge()==1) {
	_histos.Fill1D("WCandElecTrkPhiMod_Posi_PosSolpol", WElecTrkPhiMod);
	_histos.Fill1D("WCandElecTrkPhiModEM3_Posi_PosSolpol", WElecTrkPhiModEM3);
      } 
      if(track_spatial->charge()==-1) {
	_histos.Fill1D("WCandElecTrkPhiMod_Elec_PosSolpol", WElecTrkPhiMod);
	_histos.Fill1D("WCandElecTrkPhiModEM3_Elec_PosSolpol", WElecTrkPhiModEM3);
      } 
    }

    // for backward polarity
    if(solpol==-1) {
      if(track_spatial->charge()==1) {
	_histos.Fill1D("WCandElecTrkPhiMod_Posi_NegSolpol", WElecTrkPhiMod);
	_histos.Fill1D("WCandElecTrkPhiModEM3_Posi_NegSolpol", WElecTrkPhiModEM3);
      } 
      if(track_spatial->charge()==-1) {
	_histos.Fill1D("WCandElecTrkPhiMod_Elec_NegSolpol", WElecTrkPhiMod);
	_histos.Fill1D("WCandElecTrkPhiModEM3_Elec_NegSolpol", WElecTrkPhiModEM3);
      } 
    }


    ///////////////////////////////////////////////////////////////////////////
    _histos.Fill1D(TString("WCandEOverP_CalPhiModPosition_")+sn_CalPhiModPosition, EOverP);
    _histos.Fill1D(TString("WCandRawEOverP_CalPhiModPosition_")+sn_CalPhiModPosition, RawEOverP);
    _histos.Fill1D(TString("WCandEOverP_TrkPhiModPosition_")+sn_TrkPhiModPosition, EOverP);
    _histos.Fill1D(TString("WCandRawEOverP_TrkPhiModPosition_")+sn_TrkPhiModPosition, RawEOverP);
    _histos.Fill1D(TString("WCandEOverP_TrkPhiModEM3Position_")+sn_TrkPhiModEM3Position, EOverP);
    _histos.Fill1D(TString("WCandRawEOverP_TrkPhiModEM3Position_")+sn_TrkPhiModEM3Position, RawEOverP);

    if(track_spatial->charge()==-1) {
      _histos.Fill1D(TString("WCandEOverP_TrkPhiModPosition_Elec_")+sn_TrkPhiModPosition, EOverP);
      _histos.Fill1D(TString("WCandEOverP_TrkPhiModEM3Position_Elec_")+sn_TrkPhiModEM3Position, EOverP);
    }

    if(track_spatial->charge()==1) {
      _histos.Fill1D(TString("WCandEOverP_TrkPhiModPosition_Posi_")+sn_TrkPhiModPosition, EOverP);
      _histos.Fill1D(TString("WCandEOverP_TrkPhiModEM3Position_Posi_")+sn_TrkPhiModEM3Position, EOverP);
    }
     
    // check E/p for other variables
    if(EOverP>0.9 && EOverP<1.3) {
      // check E/p vs electron calorimeter Et
      _histos.FillProfile("WCandEOverP_V_Et", emobj->CalEt(), EOverP);
      
      // check E/p for electron and positron
      // calorimeter is blind to charge, so this distribution is useful for 
      // checking bias on momentum measurement  	      
      if(track_spatial->charge() == -1) {
	_histos.FillProfile("WCandEOverP_V_TrkPhi_Electron", track_spatial->Phi(), EOverP);
	_histos.FillProfile("WCandEOverP_V_EMPhi_Electron", emobj->CalPhi(), EOverP);
      } else if (track_spatial->charge() == 1) {
	_histos.FillProfile("WCandEOverP_V_TrkPhi_Positron", track_spatial->Phi(), EOverP);
	_histos.FillProfile("WCandEOverP_V_EMPhi_Positron", emobj->CalPhi(), EOverP);
      }
      
      // check E/p vs physics eta to see the effect on amount of material
      // transversed by the electron and also check geometry correction
      _histos.FillProfile("WCandEOverP_V_ElecEta", WElecEta, EOverP);
      _histos.FillProfile("WCandEOverP_V_ElecDetEta", WElecDetEta, EOverP);
      _histos.FillProfile("WCandEOverP_V_ElecPhi", WElecPhiTrkAtDCA, EOverP);
      _histos.FillProfile("WCandEOverP_V_ElecDetPhi", WElecDetPhiCALO, EOverP);
      _histos.FillProfile("WCandEOverP_V_ElecPhiMod", WElecPhiMod, EOverP);
      _histos.FillProfile("WCandEOverP_V_ElecTrkPhiMod", WElecTrkPhiMod, EOverP);

      _histos.FillProfile(TString("WCandEOverP_V_ElecPhiMod_")+sn_mod, WElecPhiMod, EOverP);
      _histos.FillProfile(TString("WCandEOverP_V_ElecTrkPhiMod_")+sn_trkmod, WElecTrkPhiMod, EOverP);
    } //EOverP>0.9 and EOverP<1.3
    
    // for Raw E/p
    if(RawEOverP>0.9 && RawEOverP<1.3) {
      _histos.FillProfile("WCandRawEOverP_V_ElecEta", WElecEta, RawEOverP);
      _histos.FillProfile("WCandRawEOverP_V_ElecDetEta", WElecDetEta, RawEOverP);
      _histos.FillProfile("WCandRawEOverP_V_ElecPhi", WElecPhiTrkAtDCA, RawEOverP);
      _histos.FillProfile("WCandRawEOverP_V_ElecDetPhi", WElecDetPhiCALO, RawEOverP);
      _histos.FillProfile("WCandRawEOverP_V_ElecPhiMod", WElecPhiMod, RawEOverP);
      _histos.FillProfile("WCandRawEOverP_V_ElecTrkPhiMod", WElecTrkPhiMod, RawEOverP);
      
      _histos.FillProfile(TString("WCandRawEOverP_V_ElecPhiMod_")+sn_mod, WElecPhiMod, RawEOverP);
      _histos.FillProfile(TString("WCandRawEOverP_V_ElecTrkPhiMod_")+sn_trkmod, WElecTrkPhiMod, RawEOverP);
    } //for Raw E/p
  } // tight track requirement
}

//
// here I will smear generator-level electrons to get E/p distribution
//
void WAnalysis::MCStudies(cafe::Event& event) {

  std::vector<TMBMCpart *> _raw_mc_electrons;
  std::vector<TMBMCpart *> _raw_mc_photons;

  if ( event.get("raw mc electrons", _raw_mc_electrons) && event.get("raw mc photons", _raw_mc_photons) ) {    
    if(_raw_mc_electrons.size()>0){
      // random numbers
      double randN1 = _random->Gaus(0., 1.);
      double randN2 = _random->Gaus(0., 1.);
      double randN3 = _random->Gaus(0., 1.);
      
      // raw electron pT
      double raw_pT = _raw_mc_electrons[0]->Pt();
      
      // smear electron (may need to merge photons)
      double merged_Px = _raw_mc_electrons[0]->Px();
      double merged_Py = _raw_mc_electrons[0]->Py();
      double merged_Pz = _raw_mc_electrons[0]->Pz();
      double merged_E = _raw_mc_electrons[0]->E();
      
      double elec_eta = _raw_mc_electrons[0]->Eta();
      double elec_phi = _raw_mc_electrons[0]->Phi();

      for(int ipho=0; ipho<_raw_mc_photons.size(); ipho++) {
	if (kinem::delta_R(elec_eta, elec_phi, _raw_mc_photons[ipho]->Eta(), _raw_mc_photons[ipho]->Phi()) < 0.2) {
	  merged_Px += _raw_mc_photons[ipho]->Px();
	  merged_Py += _raw_mc_photons[ipho]->Py();
	  merged_Pz += _raw_mc_photons[ipho]->Pz();
	  merged_E += _raw_mc_photons[ipho]->E();
	}
      } // merge photons
      
      TLorentzVector elec_vec(merged_Px, merged_Py, merged_Pz, merged_E);
      double merged_pT = elec_vec.Pt();
      double merged_Eta = elec_vec.Eta();	  
      
      // check E/P for merging electron and photons
      if(merged_pT>25.) _histos.Fill1D("WMCEOverP_Merge", merged_pT/raw_pT);
      
      merged_E = _alpha*merged_E + _beta;      
      double reso_cal = sqrt(_constant*_constant + _sampling*_sampling/merged_E + _noise*_noise/(merged_E*merged_E));	  
      merged_Eta = merged_Eta * (1. + randN1*_eta_Resolution);
      double merged_Theta = 2.0*atan(exp(-merged_Eta));
      
      // smear electron
      double E_Smear = merged_E * (1. + randN2*reso_cal);
      double ET_Smear = E_Smear * sin(merged_Theta);
      
      if(ET_Smear>25.) _histos.Fill1D("WMCEOverP_CalSmear", ET_Smear/raw_pT);
      
      // smear track for test purpose
      double reso_trk = sqrt(_A*_A*raw_pT*raw_pT + _B*_B);
      double InvpT_Smear_tmp = 1/(_C*raw_pT) + _CNonLinear * pow((1/raw_pT - 0.0246),2);      
      double pT_Smear_tmp = 1/(InvpT_Smear_tmp*(1+randN3*reso_trk)); // need to times C
      if(ET_Smear>25.) _histos.Fill1D("WMCEOverP_CalTrkSmear", ET_Smear/pT_Smear_tmp);
      
      // add bremsstrahlung simulation, electron will travel through SMT + CFT layers
      double elec_energy = 1.;
      
      for(int i=0; i<bin_radiation_length; i++) {
	double proba[50];
	double elec_energy_fraction;
	double proba_total;
	
	wz_utils::brem_simulation(radiation_length, y_min, bin_y, k, proba, proba_total, elec_energy_fraction, _random);
	elec_energy = elec_energy * elec_energy_fraction;
      } //travel through materials
      
      //remaining electron pT after it travels through material
      raw_pT *= elec_energy;
      if(ET_Smear>25.) _histos.Fill1D("WMCEOverP_CalBremSmear", ET_Smear/raw_pT);

      double InvpT_Smear = 1/(_C*raw_pT) + _CNonLinear * pow((1/raw_pT - 0.0246),2);      
      double pT_Smear = 1/(InvpT_Smear*(1+randN3*reso_trk)); // need to times C
      if(ET_Smear>25.) {
	_histos.Fill1D("WMCEOverP", ET_Smear/pT_Smear);
	_histos.Fill1D("WMCElecTrkPt_Smear", pT_Smear);
      }

      if((ET_Smear/pT_Smear>0.9) && (ET_Smear/pT_Smear<1.3))_histos.FillProfile("WMCEOverP_V_Et", ET_Smear, ET_Smear/pT_Smear);
      
    }//at least one MC electron
  }// get pointer
}

// make recoil file for Matt's studies
void WAnalysis::makeRecoilFile(cafe::Event& event, vector<CAFEMObj*> emobjs, double instlumi, int type, double scalarEt) {
  
  float vtx_x, vtx_y, vtx_z;
  if(event.get("Best primary vertexX", vtx_x) && event.get("Best primary vertexY", vtx_y) && event.get("Best primary vertexZ", vtx_z)) {    
    
    CAFMet raw_met;
    if (event.get("Raw Met", raw_met)) {
      float thevert[3] = {vtx_x, vtx_y, vtx_z};
      
      // calculate raw electron vector using cell information
      TVector2 elecvect = emobjs[0]->getRawElecVectorFromCells(thevert);
      
      // raw met
      TVector2 raw_met_vect(raw_met.metx(), raw_met.mety());
      
      // uncorrected recoil vector
      TVector2 recoil_vector_uncorr = -1*(raw_met_vect+elecvect);

      // calculate uparallel for the electron
      double upara_elec = recoil_vector_uncorr * (emobjs[0]->vect2()).Unit();
      double upara_elec_nocut = recoil_vector_uncorr * (emobjs[0]->vect2()).Unit();

      if(upara_elec < -15.) upara_elec = -15.;
      if(upara_elec > 15.) upara_elec = 15.;
      
      double a0=0.004433, a1=0.003575, a2=0.01056, a3=-0.00061, a4=-0.004008;
      double uparaCorr_elec_L0 = (a0 + a1/10.*upara_elec + a2/100.*upara_elec*upara_elec +
				  a3/1000.*upara_elec*upara_elec*upara_elec +
				  a4/10000.*upara_elec*upara_elec*upara_elec*upara_elec);
      
      double uparaCorr_elec_mean= (_UparaCorr_CC_Hist->GetRandom()) - (_UparaCorr_CC_Hist->GetMean());
      double uparaCorr_elec = 13*(uparaCorr_elec_mean + uparaCorr_elec_L0 + (0.002543)*instlumi);
      
      // add back uparallel corrections from the two electrons
      TVector2 recoil_vector_const_corr = recoil_vector_uncorr + 0.13*(emobjs[0]->vect2()).Unit();
      TVector2 recoil_vector_param_corr = recoil_vector_uncorr + uparaCorr_elec*(emobjs[0]->vect2()).Unit();
      TVector2 recoil_vector_pcone_corr = recoil_vector_uncorr - (uparaCorr_elec-.08)*(emobjs[0]->vect2()).Unit();

      // smeared or measured W pX and pY
      double Wpx_smear = emobjs[0]->Px() + raw_met.metx();
      double Wpy_smear = emobjs[0]->Py() + raw_met.mety();

      // generator W pX and pY, for data, they will be equal to measured pX and pY
      double Wpx_gen = Wpx_smear;
      double Wpy_gen = Wpy_smear;
      if(_MCStudy) {
        TMBMCpart * _WZ;
        if(event.get("WZ boson object", _WZ)) {
          Wpx_gen = _WZ->Px();
          Wpy_gen = _WZ->Py();
        }
      }

      int runno;
      event.get("run number", runno);

      double evtweight = 1.;
      (*_recoil_file_txt) << Wpx_gen << " " << Wpy_gen << " " << Wpx_smear << " " << Wpy_smear << " ";

      if(_useUnCorrRecoil) (*_recoil_file_txt) << recoil_vector_uncorr.X() << " " << recoil_vector_uncorr.Y() << " ";
      if(_useConstantCorrRecoil) (*_recoil_file_txt) << recoil_vector_const_corr.X() << " " << recoil_vector_const_corr.Y() << " ";
      if(_useParameterizedCorrRecoil) (*_recoil_file_txt) << recoil_vector_param_corr.X() << " " << recoil_vector_param_corr.Y() << " ";
      if(_useParamConeCorrRecoil) (*_recoil_file_txt) << recoil_vector_pcone_corr.X() << " " << recoil_vector_pcone_corr.Y() << " ";
      (*_recoil_file_txt) <<scalarEt << " " <<upara_elec_nocut<<" "<<0<<" "<<emobjs[0]->Pt()<<" "<<0<<" "<<runno<<" ";
      (*_recoil_file_txt) << instlumi << " " << 90.0 << " " << type << " ";
      (*_recoil_file_txt) << evtweight;
      
      if(isPhot) (*_recoil_file_txt) << " " << isPhot << " " << HighestPhotonPt << " " << 0 << " " << SecondHighestPhotonPt << " " << 0;
      else (*_recoil_file_txt) << " " << isPhot << " 0 " << "0 " << "0 " << "0";
      
      int has_track_match = 0;
          if(emobjs[0]->has_good_spatial_track_match(0.01,_require_smt)) has_track_match = 1;

      if(_dumpElecInfo) (*_recoil_file_txt) << " " << emobjs[0]->Pt() << " " << emobjs[0]->Eta() << " " << emobjs[0]->Phi() << " " << emobjs[0]->CalDetectorEta() << " "
                                            << emobjs[0]->HMx7() << " " << emobjs[0]->HMx8() << " " << emobjs[0]->emfrac()
                                            << " " << emobjs[0]->iso() << " " << has_track_match
                                            << " " << raw_met.metx() << " " << raw_met.mety();
      (*_recoil_file_txt) << endl;

    }// get raw Met
  } // primary vertex
}

// write out useful information for W studies
// electron requirements are loosen
void WAnalysis::makeEfficStudyFile(cafe::Event& event, vector<CAFEMObj*> emobjs, std::vector<TMBMCpart *> raw_emobjs_gen, double instlumi, int type, double scalarEt) {

  float vtx_x, vtx_y, vtx_z;
  if(event.get("Best primary vertexX", vtx_x) && event.get("Best primary vertexY", vtx_y) && event.get("Best primary vertexZ", vtx_z)) {    
    
    CAFMet raw_met;
    if (event.get("Raw Met", raw_met)) {
      float thevert[3] = {vtx_x, vtx_y, vtx_z};
      
      // calculate raw electron vector using cell information
      TVector2 elecvect = emobjs[0]->getRawElecVectorFromCells(thevert);
      
      // raw met
      TVector2 raw_met_vect(raw_met.metx(), raw_met.mety());
      
      // uncorrected recoil vector
      TVector2 recoil_vector_uncorr = -1*(raw_met_vect+elecvect);

      // calculate uparallel for the electron
      double upara_elec = recoil_vector_uncorr * (emobjs[0]->vect2()).Unit();

      // smeared or measured W pX and pY
      double Wpx_smear = emobjs[0]->Px() + raw_met.metx();
      double Wpy_smear = emobjs[0]->Py() + raw_met.mety();

      // generator W pX and pY, for data, they will be equal to measured pX and pY
      double Wpx_gen = Wpx_smear;
      double Wpy_gen = Wpy_smear;
      if(_MCStudy) {
        TMBMCpart * _WZ;
        if(event.get("WZ boson object", _WZ)) {
          Wpx_gen = _WZ->Px();
          Wpy_gen = _WZ->Py();
        }
      }

      double epT_gen=0, eEta_gen=0., ePhi_gen=0.;
      if(_MCStudy) {
	epT_gen = raw_emobjs_gen[0]->Pt();
	eEta_gen = raw_emobjs_gen[0]->Eta();
	ePhi_gen = raw_emobjs_gen[0]->Phi();
      }

      int has_track_match = 0;
      if(emobjs[0]->has_good_spatial_track_match()) has_track_match = 1;
      
      const TMBTrack *tmp_track = emobjs[0]->getPtrSpatialChp();
      double trackpT = 0;
      if(has_track_match) trackpT = tmp_track->Pt();

      int Runno = event.getGlobal()->runno();
      int Evtno = event.getGlobal()->evtno();

      int ZBRunno = 0;
      int ZBEvtno = 0;
      if(_MCStudy) {
	ZBRunno = event.getMCEventInfo()->overlayrun();
	ZBEvtno = event.getMCEventInfo()->overlayevtid();
      }

      double evtweight = 1.;
      (*_effic_study_txt) << Runno << " " << Evtno<< " " << ZBRunno << " " << ZBEvtno << " "
			  << Wpx_gen << " " << Wpy_gen << " " << Wpx_smear << " " << Wpy_smear << " "
			  << recoil_vector_uncorr.X() << " " << recoil_vector_uncorr.Y() << " "
			  << epT_gen << " " << eEta_gen << " " << ePhi_gen << " " << emobjs[0]->Pt() << " " << emobjs[0]->Eta() << " " 
			  << emobjs[0]->Phi() << " " << emobjs[0]->CalDetectorEta() << " " << emobjs[0]->CalDetectorPhi() << " " << emobjs[0]->HMx7() 
			  << " " << emobjs[0]->HMx8() << " " << emobjs[0]->emfrac() << " " << emobjs[0]->iso() 
			  << " " << has_track_match << " " << trackpT << " " << raw_met.metx() << " " << raw_met.mety() 
			  << " " << scalarEt << " " << type << " " << vtx_z;
      (*_effic_study_txt) << endl;


    }// get raw Met
  } // primary vertex
}

// study uparallel efficiency
// note no iso and hmatrix requirements for emobj here
void WAnalysis::uParaEfficiencyStudies(Event& event, CAFWCand& wcand) {
  double UPara = wcand.UPara();
  double UPerp = wcand.UPerp();
  double UT = sqrt(UPara*UPara + UPerp*UPerp);

  TVector2 recoil_vect = wcand.GetRecoil();

  double recoilPt = recoil_vect.Mod();
  double recoilAng = wcand.DeltaPhi_EM_Recoil();
  double recoilCos = TMath::Cos(recoilAng);

  const CAFEMObj *emobj = wcand.EM();
  double emIso = emobj->iso();
  double HMx7 = emobj->HMx7();
  double HMx8 = emobj->HMx8();
  TVector3 em_vect = emobj->vect3();    
  double Etrans = emobj->Pt();

  // access Jet information    
  cafe::Collection<TMBJet> jets = event.getJCCB();
  
  bool passJetRequirements = true;
  if(jets.size() > 0) {
    for(Collection<TMBJet>::iterator iter = jets.begin(); iter != jets.end(); ++iter) {	
      TVector3 jet_vect( (*iter).Px(), (*iter).Py(), (*iter).Pz() );
      double dphi_jet_em = em_vect.DeltaPhi(jet_vect);
      if((fabs(dphi_jet_em) > 2.8)&&(iter->Pt()>10.)) passJetRequirements=false;
    }
  } // require no jet with pT>10 GeV and back-to-back in phi with the electron to remove em+jet background

  bool good_spatial_track_match = emobj->has_good_spatial_track_match(0.01,kTRUE,0.);
  bool spatial_track_match = emobj->has_spatial_track_match();
  
  int uParaBin = wz_utils::UParaBins(UPara);
  char UPara_type[10];  sprintf(UPara_type,"%d", uParaBin);       

  // in CC or EC
  //bool InCC = fabs(emobj->CalDetectorEta())<1.1;
  // RCLSA: Do not use trk phi fiducial, but still apply fiducial cuts.
  bool InCC = emobj->IsCCFid(1.1,false);
  //
  // for full MC events
  // check neutrino in CC or EC to measure the bias due to tag-probe method using Zee events
  //
  bool InCC_Nu = false, InEC_Nu = false;
  if(_MCStudy) {

    std::vector<TMBMCpart *> good_mc_neutrinos;
    event.get("mc neutrinos", good_mc_neutrinos);
    
    float zvtx = -1.;
    event.get("Best primary vertexZ", zvtx);
    
    double nu_deteta = -9999.;
    for(int inu=0; inu<good_mc_neutrinos.size(); inu++) {
      TVector3 v;
      double phi = good_mc_neutrinos[inu]->Phi();
      double eta = good_mc_neutrinos[inu]->Eta();
      double theta = 2.0*atan(exp(-eta));
      double ztmp = zvtx + 91.9/TMath::Tan(theta);
      
      if( TMath::Abs(ztmp) >= 140. ){ // in EC
	(eta>=0) ? v.SetZ(179.) : v.SetZ(-182.8);
	
	v.SetX( (v.Z()-zvtx) * TMath::Tan(theta) * TMath::Cos(phi));
	v.SetY( (v.Z()-zvtx) * TMath::Tan(theta) * TMath::Sin(phi));
      }
      else{ // in CC
	v.SetZ(ztmp);
	v.SetX( 91.9 * TMath::Cos(phi));
	v.SetY( 91.9 * TMath::Sin(phi));
      }
      
      nu_deteta = 0.5*log((v.Mag() + v.Z()) / (v.Mag() - v.Z()));
    } // loop over neutrino

    // determine neutrino in CC or EC
    if(_Nu_CC || _Nu_EC) {
      if(_Nu_CC) {
	InCC_Nu = fabs(nu_deteta)<1.1;
	InEC_Nu = true;
      }
      if(_Nu_EC) {
	InCC_Nu = true;
	InEC_Nu = fabs(nu_deteta)<2.5 && fabs(nu_deteta)>1.5;;
      }
    }
    else {
      InCC_Nu = true;
      InEC_Nu = true;
    }
  } // MC study

  bool elec_CC = false;
  if(!_MCStudy) elec_CC = InCC;
  else elec_CC = InCC && InCC_Nu && InEC_Nu;

  if(elec_CC) {   // electron in CC 
    //
    // method used for real data
    // first require track matching and check hmx and isolation requirement vs upara
    // then require iso and hmx, and check track matching vs upara
    //
// RCLSA: Here is the numerator
      _histos.Fill1D("WCandUPara_noIsoHMxCut", UPara);
      _histos.Fill1D("WCandUParaETRatio_noIsoHMxCut", UPara/Etrans);
      _histos.Fill2D("WCandUPara_V_CosPhi_Denominator", UPara, recoilCos); 
      _histos.Fill2D("WCandU_V_CosPhi_Denominator", recoilPt, recoilCos); 
    if(emobj->PassEMFracIso(0.9, 0.15) && emobj->HMx7()<12.) {
//      _histos.Fill1D((string("WCandUPara_WithIsoHMxCut_")+UPara_type).c_str(), UPara);
      _histos.Fill1D("WCandUPara_WithIsoHMxCut", UPara);
      
      if(good_spatial_track_match) {
	const TMBTrack *tmp_track = emobj->getPtrSpatialChp();
//	_histos.Fill1D((string("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut_")+UPara_type).c_str(), UPara);
// RCLSA: Here is the denominator
	_histos.Fill1D("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut", UPara);
	_histos.Fill1D("WCandUParaETRatio_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut", UPara/Etrans);
	_histos.Fill2D("WCandUPara_V_CosPhi_Numerator", UPara, recoilCos); 
	_histos.Fill2D("WCandU_V_CosPhi_Numerator", recoilPt, recoilCos); 
	
	if(tmp_track->Pt()>10.) {
//	  _histos.Fill1D((string("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_")+UPara_type).c_str(), UPara);
	  _histos.Fill1D("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut", UPara);
	}
	if(tmp_track->nsmt()>0) {
//	  _histos.Fill1D((string("WCandUPara_WithIsoHMxCut_trkmatch_noTrkPtCut_")+UPara_type).c_str(), UPara);
	  _histos.Fill1D("WCandUPara_WithIsoHMxCut_trkmatch_noTrkPtCut", UPara);
	}
	if(good_spatial_track_match) {
//	  _histos.Fill1D((string("WCandUPara_WithIsoHMxCut_trkmatch_")+UPara_type).c_str(), UPara);
	  _histos.Fill1D("WCandUPara_WithIsoHMxCut_trkmatch", UPara);
	}
      }
    }
    
    if(good_spatial_track_match) {
//      _histos.Fill1D((string("WCandUPara_WithGoodSpatialMatch_")+UPara_type).c_str(), UPara);
      _histos.Fill1D("WCandUPara_WithGoodSpatialMatch", UPara);
      
      if(emobj->PassEMFracIso(0.9, 0.15) && emobj->HMx7()<12.) {
//	_histos.Fill1D((string("WCandUPara_WithGoodSpatialMatch_IsoHMxCut_")+UPara_type).c_str(), UPara);
	_histos.Fill1D("WCandUPara_WithGoodSpatialMatch_IsoHMxCut", UPara);
      }
    }
    
    if(spatial_track_match) {
//      _histos.Fill1D((string("WCandUPara_WithSpatialMatch_")+UPara_type).c_str(), UPara);
      _histos.Fill1D("WCandUPara_WithSpatialMatch", UPara);
      
      if(emobj->PassEMFracIso(0.9, 0.15) && emobj->HMx7()<12.) {
//	_histos.Fill1D((string("WCandUPara_WithSpatialMatch_IsoHMxCut_")+UPara_type).c_str(), UPara);
	_histos.Fill1D("WCandUPara_WithSpatialMatch_IsoHMxCut", UPara);
      }
    }
    
    //
    // the following method only works for full MC, no background considered below
    //
//    _histos.Fill2D("WCandIsoVsHMx7_notrkmatch_UPara", HMx7, emIso);
//    _histos.Fill2D((string("WCandIsoVsHMx7_notrkmatch_UPara_")+UPara_type).c_str(), HMx7, emIso);
    
    if(passJetRequirements) {
//      _histos.Fill2D("WCandIsoVsHMx7_notrkmatch_PassJet_UPara", HMx7, emIso);
//      _histos.Fill2D((string("WCandIsoVsHMx7_notrkmatch_PassJet_UPara_")+UPara_type).c_str(), HMx7, emIso);
      
//      _histos.Fill2D("WCandIsoVsHMx7_notrkmatch_PassJet_UPara", HMx7, emIso);
//      _histos.Fill2D((string("WCandIsoVsHMx7_notrkmatch_PassJet_UPara_")+UPara_type).c_str(), HMx7, emIso);
    }
    
    _histos.Fill1D("WCandUPara_notrkmatch_UPara", UPara);
//    _histos.Fill1D((string("WCandUPara_notrkmatch_UPara_")+UPara_type).c_str(), UPara);
    
    if(spatial_track_match) {
//      _histos.Fill2D("WCandHMx7VsUPara_trkmatch_noTrkPtCut_noSMTHitCut_UPara", UPara, HMx7);
//      _histos.Fill2D((string("WCandHMx7VsUPara_trkmatch_noTrkPtCut_noSMTHitCut_UPara_")+UPara_type).c_str(), UPara, HMx7);
      
      _histos.Fill1D("WCandUPara_trkmatch_UPara", UPara);
//      _histos.Fill1D((string("WCandUPara_trkmatch_UPara_")+UPara_type).c_str(), UPara);
      
      const TMBTrack *tmp_track = emobj->getPtrSpatialChp();
      
//      _histos.Fill2D((string("WCandIsoVsHMx7_trkmatch_noTrkPtCut_noSMTHitCut_UPara_")+UPara_type).c_str(), HMx7, emIso);
//      if(tmp_track->Pt()>10.) _histos.Fill2D((string("WCandIsoVsHMx7_trkmatch_noSMTHitCut_UPara_")+UPara_type).c_str(), HMx7, emIso);
//      if(tmp_track->nsmt()>0) _histos.Fill2D((string("WCandIsoVsHMx7_trkmatch_noTrkPtCut_UPara_")+UPara_type).c_str(), HMx7, emIso);
//      if(good_spatial_track_match) _histos.Fill2D((string("WCandIsoVsHMx7_trkmatch_UPara_")+UPara_type).c_str(), HMx7, emIso);
      
//      _histos.Fill2D("WCandIsoVsHMx7_trkmatch_noTrkPtCut_noSMTHitCut_UPara", HMx7, emIso);
//      if(tmp_track->Pt()>10.) _histos.Fill2D("WCandIsoVsHMx7_trkmatch_noSMTHitCut_UPara", HMx7, emIso);
//      if(tmp_track->nsmt()>0) _histos.Fill2D("WCandIsoVsHMx7_trkmatch_noTrkPtCut_UPara", HMx7, emIso);
//      if(good_spatial_track_match) _histos.Fill2D("WCandIsoVsHMx7_trkmatch_UPara", HMx7, emIso);
      
      if(passJetRequirements) {
	_histos.Fill1D("WCandUPara_trkmatch_PassJet_UPara", UPara);
//	_histos.Fill1D((string("WCandUPara_trkmatch_PassJet_UPara_")+UPara_type).c_str(), UPara);
	
//	_histos.Fill2D((string("WCandIsoVsHMx7_trkmatch_noTrkPtCut_noSMTHitCut_PassJet_UPara_")+UPara_type).c_str(), HMx7, emIso);
//	if(tmp_track->Pt()>10.) _histos.Fill2D((string("WCandIsoVsHMx7_trkmatch_noSMTHitCut_PassJet_UPara_")+UPara_type).c_str(), HMx7, emIso);
//	if(tmp_track->nsmt()>0) _histos.Fill2D((string("WCandIsoVsHMx7_trkmatch_noTrkPtCut_PassJet_UPara_")+UPara_type).c_str(), HMx7, emIso);
//	if(good_spatial_track_match) _histos.Fill2D((string("WCandIsoVsHMx7_trkmatch_PassJet_UPara_")+UPara_type).c_str(), HMx7, emIso);
	
	_histos.Fill2D("WCandIsoVsHMx7_trkmatch_noTrkPtCut_noSMTHitCut_PassJet_UPara", HMx7, emIso);
//	if(tmp_track->Pt()>10.) _histos.Fill2D("WCandIsoVsHMx7_trkmatch_noSMTHitCut_PassJet_UPara", HMx7, emIso);
//	if(tmp_track->nsmt()>0) _histos.Fill2D("WCandIsoVsHMx7_trkmatch_noTrkPtCut_PassJet_UPara", HMx7, emIso);
//	if(good_spatial_track_match) _histos.Fill2D("WCandIsoVsHMx7_trkmatch_PassJet_UPara", HMx7, emIso);
      }
      
    }// spatial track
  } else {  // electron in EC
    //
    // method used for real data
    // first require track matching and check hmx and isolation requirement vs upara
    // then require iso and hmx, and check track matching vs upara
    //
    if(emobj->PassEMFracIso(0.9, 0.15) && emobj->HMx8()<20.) {
//      _histos.Fill1D((string("WCandUPara_WithIsoHMxCut_EC_")+UPara_type).c_str(), UPara);
      _histos.Fill1D("WCandUPara_WithIsoHMxCut_EC", UPara);
      
      if(spatial_track_match) {
	const TMBTrack *tmp_track = emobj->getPtrSpatialChp();
//	_histos.Fill1D((string("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut_EC_")+UPara_type).c_str(), UPara);
	_histos.Fill1D("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut_EC", UPara);
	
	if(tmp_track->Pt()>10.) {
//	  _histos.Fill1D((string("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_EC_")+UPara_type).c_str(), UPara);
	  _histos.Fill1D("WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_EC", UPara);
	}
	if(tmp_track->nsmt()>0) {
//	  _histos.Fill1D((string("WCandUPara_WithIsoHMxCut_trkmatch_noTrkPtCut_EC_")+UPara_type).c_str(), UPara);
	  _histos.Fill1D("WCandUPara_WithIsoHMxCut_trkmatch_noTrkPtCut_EC", UPara);
	}
	if(good_spatial_track_match) {
//	  _histos.Fill1D((string("WCandUPara_WithIsoHMxCut_trkmatch_EC_")+UPara_type).c_str(), UPara);
	  _histos.Fill1D("WCandUPara_WithIsoHMxCut_trkmatch_EC", UPara);
	}
      }
    }
    
    if(good_spatial_track_match) {
//      _histos.Fill1D((string("WCandUPara_WithGoodSpatialMatch_EC_")+UPara_type).c_str(), UPara);
      _histos.Fill1D("WCandUPara_WithGoodSpatialMatch_EC", UPara);
      
      if(emobj->PassEMFracIso(0.9, 0.15) && emobj->HMx8()<20.) {
//	_histos.Fill1D((string("WCandUPara_WithGoodSpatialMatch_IsoHMxCut_EC_")+UPara_type).c_str(), UPara);
	_histos.Fill1D("WCandUPara_WithGoodSpatialMatch_IsoHMxCut_EC", UPara);
      }
    }
    
    if(spatial_track_match) {
//      _histos.Fill1D((string("WCandUPara_WithSpatialMatch_EC_")+UPara_type).c_str(), UPara);
      _histos.Fill1D("WCandUPara_WithSpatialMatch_EC", UPara);
      
      if(emobj->PassEMFracIso(0.9, 0.15) && emobj->HMx8()<20.) {
//	_histos.Fill1D((string("WCandUPara_WithSpatialMatch_IsoHMxCut_EC_")+UPara_type).c_str(), UPara);
	_histos.Fill1D("WCandUPara_WithSpatialMatch_IsoHMxCut_EC", UPara);
      }
    }
    
    //
    // the following method only works for full MC, no background considered below
    //
//    _histos.Fill2D("WCandIsoVsHMx8_notrkmatch_UPara_EC", HMx8, emIso);
//    _histos.Fill2D((string("WCandIsoVsHMx8_notrkmatch_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
    
    if(passJetRequirements) {
//      _histos.Fill2D("WCandIsoVsHMx8_notrkmatch_PassJet_UPara_EC", HMx8, emIso);
//      _histos.Fill2D((string("WCandIsoVsHMx8_notrkmatch_PassJet_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
      
//      _histos.Fill2D("WCandIsoVsHMx8_notrkmatch_PassJet_UPara_EC", HMx8, emIso);
//      _histos.Fill2D((string("WCandIsoVsHMx8_notrkmatch_PassJet_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
    }
    
    _histos.Fill1D("WCandUPara_notrkmatch_UPara_EC", UPara);
//    _histos.Fill1D((string("WCandUPara_notrkmatch_UPara_EC_")+UPara_type).c_str(), UPara);
    
    if(spatial_track_match) {
 //     _histos.Fill2D("WCandHMx8VsUPara_trkmatch_noTrkPtCut_noSMTHitCut_UPara_EC", UPara, HMx8);
//      _histos.Fill2D((string("WCandHMx8VsUPara_trkmatch_noTrkPtCut_noSMTHitCut_UPara_EC_")+UPara_type).c_str(), UPara, HMx8);
      
      _histos.Fill1D("WCandUPara_trkmatch_UPara_EC", UPara);
//      _histos.Fill1D((string("WCandUPara_trkmatch_UPara_EC_")+UPara_type).c_str(), UPara);
      
      const TMBTrack *tmp_track = emobj->getPtrSpatialChp();
      
//      _histos.Fill2D((string("WCandIsoVsHMx8_trkmatch_noTrkPtCut_noSMTHitCut_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
//      if(tmp_track->Pt()>10.) _histos.Fill2D((string("WCandIsoVsHMx8_trkmatch_noSMTHitCut_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
//      if(tmp_track->nsmt()>0) _histos.Fill2D((string("WCandIsoVsHMx8_trkmatch_noTrkPtCut_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
//      if(good_spatial_track_match) _histos.Fill2D((string("WCandIsoVsHMx8_trkmatch_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
      
//      _histos.Fill2D("WCandIsoVsHMx8_trkmatch_noTrkPtCut_noSMTHitCut_UPara_EC", HMx8, emIso);
//      if(tmp_track->Pt()>10.) _histos.Fill2D("WCandIsoVsHMx8_trkmatch_noSMTHitCut_UPara_EC", HMx8, emIso);
//      if(tmp_track->nsmt()>0) _histos.Fill2D("WCandIsoVsHMx8_trkmatch_noTrkPtCut_UPara_EC", HMx8, emIso);
//      if(good_spatial_track_match) _histos.Fill2D("WCandIsoVsHMx8_trkmatch_UPara_EC", HMx8, emIso);
      
      if(passJetRequirements) {
	_histos.Fill1D("WCandUPara_trkmatch_PassJet_UPara_EC", UPara);
//	_histos.Fill1D((string("WCandUPara_trkmatch_PassJet_UPara_EC_")+UPara_type).c_str(), UPara);
	
//	_histos.Fill2D((string("WCandIsoVsHMx8_trkmatch_noTrkPtCut_noSMTHitCut_PassJet_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
//	if(tmp_track->Pt()>10.) _histos.Fill2D((string("WCandIsoVsHMx8_trkmatch_noSMTHitCut_PassJet_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
//	if(tmp_track->nsmt()>0) _histos.Fill2D((string("WCandIsoVsHMx8_trkmatch_noTrkPtCut_PassJet_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
//	if(good_spatial_track_match) _histos.Fill2D((string("WCandIsoVsHMx8_trkmatch_PassJet_UPara_EC_")+UPara_type).c_str(), HMx8, emIso);
	
//	_histos.Fill2D("WCandIsoVsHMx8_trkmatch_noTrkPtCut_noSMTHitCut_PassJet_UPara_EC", HMx8, emIso);
//	if(tmp_track->Pt()>10.) _histos.Fill2D("WCandIsoVsHMx8_trkmatch_noSMTHitCut_PassJet_UPara_EC", HMx8, emIso);
//	if(tmp_track->nsmt()>0) _histos.Fill2D("WCandIsoVsHMx8_trkmatch_noTrkPtCut_PassJet_UPara_EC", HMx8, emIso);
//	if(good_spatial_track_match) _histos.Fill2D("WCandIsoVsHMx8_trkmatch_PassJet_UPara_EC", HMx8, emIso);
      }
    } // spatial track match  
  } // electron in CC or EC
}

void WAnalysis::begin() {}

void WAnalysis::finish()
{
  if(!_MCStudy) _wenu_out_txt->close();
  if(_makeRecoilFile) _recoil_file_txt->close();
  if(_ZEEbkgStudy) _bkg_file_txt->close();

  TFile *file = histfiles::initializeTFile( this );
  if(file==NULL) return;
  string directory_name("WCand_Hist");
  file->mkdir(directory_name.c_str());
  _histos.save(file, directory_name);
  _BM.WriteVerdict(file);

  et->Write();

  file->Close();

  if(_events_fail_trigger_requirements>0) 
    cout<<"WARNING: # of W canidates where the electron does not pass trigger requirement is "<<_events_fail_trigger_requirements<<endl;
}

ClassImp(WAnalysis)
