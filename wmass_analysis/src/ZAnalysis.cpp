#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_analysis/ZAnalysis.hpp"
#include "wmass_analysis/histograms.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "wmass_util/WZ_Utils.hpp"
#include "tmb_tree/TMBCaloCell.hpp"
#include "wmass_util/CaloGeometryManager.hpp"
#include "tmb_tree/TMBMCvtx.hpp"
#include "TROOT.h"
#include <TFile.h>

#include "TLorentzVector.h"

#include <iostream>
#include <iomanip>

#define CC_XSHIFT  -0.33
#define CC_YSHIFT  -0.46
#define CC_ZSHIFT  -3.2

#define EC_3Z_NORTH -182.8
#define EC_XSHIFT_NORTH 0.38
#define EC_YSHIFT_NORTH 0.00

#define EC_3Z_SOUTH      179.
#define EC_XSHIFT_SOUTH  0.0
#define EC_YSHIFT_SOUTH  0.0

#define CC_3R   91.9
#define EC_3Z   178.9

#define EC_R_MAX  85.0
#define CC_Z_MAX  115.0

const double B_field = 2.;

using namespace std;
using namespace cafe;

ZAnalysis::ZAnalysis(const char *name)
  : Processor(name)
{
  cout << "ZAnalysis: Started" << endl;
  Config config(name);
  cout << "ZAnalysis: Config(name) passed OK" << endl;

  // debug level
  _debugLevel = config.get("debugLevel", 0);

  // em cluster position correction
  _emclusposcorr = new EMClusterPosCorr(config);

  // MC study
  _MCStudy = config.get("MCStudy", false);
  _MakeOverlayEventList = config.get("MakeOverlayEventList", false);
  _smearingStudy = config.get("smearingStudy",false);

  // do ZB event studies
  _doZBevent = config.get("doZBevent", false);

  // study phi crack efficiency
  _PhiCrackEffStudy = config.get("PhiCrackEffStudy", false);

  // EMF study
  _performEMFstudy = config.get("performEMFstudy", false);
  if (_performEMFstudy) {
    _EMFstudySimulateRelGains = config.get("EMFstudySimulateRelGains", false);
    _EMFstudyRelGainEM1 = config.get("EMFstudyRelGainEM1", 1.0);
    _EMFstudyRelGainEM2 = config.get("EMFstudyRelGainEM2", 1.0);
    _EMFstudyRelGainEM3 = config.get("EMFstudyRelGainEM3", 1.0);
    _EMFstudyRelGainEM4 = config.get("EMFstudyRelGainEM4", 1.0);
    _EMFstudyRelGainFH1 = config.get("EMFstudyRelGainFH1", 1.0);
    _EMFstudyLumiBinStarts = config.getVFloat("EMFstudyLumiBinStarts");
    _EMFstudyNLumiBins = _EMFstudyLumiBinStarts.size();
  }

  // switches for ASCII printouts that can be used for more detailed studies (outside the
  // framework of wmass_analysis) of electron ID efficiency and electron energy resonse
  _dump_LumiEff = config.get("dump_LumiEff", false);
  _dump_Eresponse = config.get("dump_Eresponse", false);

  // EM Eta cuts
  _DetEtaCC = config.get("DetEtaCC", 1.1);
  _DetEtaEC1 = config.get("DetEtaEC1", 1.5);
  _DetEtaEC2 = config.get("DetEtaEC2", 2.3);

  // spatial track matching requirement
  _NumZSpatialTrk = config.get("NumZSpatialTrk", 1);


  // require smt hit for track match
  _require_smt = config.get("RequireSMT", kTRUE);
  
  _TrkPhiFiducial = config.get("UseTrkPhiFiducial", kTRUE);


  // Z boson mass, pT cuts
  _ZMassCut1 = config.get("ZMassCut1", 70.);
  _ZMassCut2 = config.get("ZMassCut2", 110.);
  _ZUtCut = config.get("ZUtCut", 999.);
  _ZUtCut_lower = config.get("ZUtCut_lower", 0.);
  _ZPtCut = config.get("ZPtCut", 999.);
  _ZPtCut_lower = config.get("ZPtCut_lower", 0.);
  _ZPhiCut = config.get("ZPhiCut", 999.);
  _ZPhiCut_lower = config.get("ZPhiCut_lower", 0.);

  //we have already made a low cut on both electrons in the EM selector
  _ElecPtCut1_lo = config.get("ElecPtCut1_Lo", 25.);
  _ElecPtCut2_lo = config.get("ElecPtCut2_Lo", 25.);
  _ElecPtCut1_hi = config.get("ElecPtCut1_Hi", 1000.);
  _ElecPtCut2_hi = config.get("ElecPtCut2_Hi", 1000.);

  _ZScalarEtCut = config.get("ZScalarEtCut", 99999.);
  _ZScalarEtCut_lower = config.get("ZScalarEtCut_lower", 0.);

  _etaImbalance_perbincuts  = config.get("etaImbalance_perbincuts", kFALSE);
  _InvertetaImbalance_perbincuts  = config.get("InvertetaImbalance_perbincuts", kFALSE);
  _EtaImbalanceCutLow = config.getVFloat("EtaImbalanceCutLow");
  _EtaImbalanceCutHigh = config.getVFloat("EtaImbalanceCutHigh");

  // study QCD background
  // drop spatial track matching requirements
  // for fZ histograms, also make no track matching requirements
  _QCDBkgStudy = config.get("QCDBkgStudy", false);
  if(_QCDBkgStudy) {
    _NumZSpatialTrk = 0;
    _TrkPhiFiducial = false;
    _ZMassCut1 = 50.;
    _ZMassCut2 = 130.;
   }

  // study SM backgrounds
  _SMBkgStudy = config.get("SMBkgStudy", false);
  if(_SMBkgStudy) _evtReweightManager = new evtReweightManager(config);

  // get sampling term, noise term
  _alpha = config.get("Scale", 1.);
  _beta = config.get("Offset", 0.);
  _sampling = config.get("Sampling", 0.21);
  _noise = config.get("Noise", 0.29);
  _constant = config.get("Constant", 0.);
  _sampling1 = config.get("Sampling1", 10.164);
  _sampling2 = config.get("Sampling2", 0.122); 
  _samplingexp0 = config.get("SamplingExp0", 1.35193);  
  _samplingexp1 = config.get("SamplingExp1", 2.09564); 
  _samplingexp2 = config.get("SamplingExp2", 6.98578); 

  _eta_Resolution  = config.get("eta_Resolution", 0.);
  _phi_Resolution  = config.get("phi_Resolution", 0.);
  _doRatioMethod = config.get("doRatioMethod", false);
  _dorawCellsRecoil = config.get("dorawCellsRecoil", true);
  _useConsistentMET = config.get("useConsistentMET", true);

  // make recoil file for Matt's method
  _makeRecoilFile = config.get("makeRecoilFile", false);
  if(_makeRecoilFile) {
    _useUnCorrRecoil = config.get("useUnCorrRecoil", false);
    _useConstantCorrRecoil = config.get("useConstantCorrRecoil", false);
    _useParameterizedCorrRecoil = config.get("useParameterizedCorrRecoil", false);
    _useParamConeCorrRecoil = config.get("useParamConeCorrRecoil", false);

    _dumpElecInfo = config.get("dumpElecInfo", false);

    gROOT->ProcessLine(TString(".x UParaCorrPerTower.C"));
    _UparaCorr_CC_Hist = (TH1F *)gROOT->FindObject("UParaCorrPerTower");
    TDirectory * curdir = gDirectory;
    _RecoilFile = new TFile( "recoil_file_zee.root","recreate");
    _RecoilTree = new TTree( "RecoilTree" , "RecoilTree" );
    std::string recoil_block = "pTZ_gen_x/D:pTZ_gen_y/D:pTZ_smear_x/D:pTZ_smear_y/D:recoil_x/D:recoil_y/D:recoil_uncorr_x/D:recoil_uncorr_y/D:recoil_constcorr_x/D:recoil_constcorr_y/D:recoil_paramcorr_x/D:recoil_paramcorr_y/D:recoil_paramconecorr_x/D:recoil_paramconecorr_y/D:scalarET/D:upara_e1/D:upara_e2/D:pT_e1/D:pT_e2/D:eta_e1/D:eta_e2/D:runno/I:lumi/D:MZ/D:type/I:eventweight/D:isFSR/I:photpT1/D:photpT2/D";
    _RecoilTree->Branch( "RecoilData" , &recoil_data.pTZ_gen_x , recoil_block.c_str() );
    curdir->cd();
  }

  // make text file for efficiency studies
  _makeEfficStudyFile = config.get("makeEfficStudyFile", false);
  if(_makeEfficStudyFile){
    _ZUtCut = 100000.;
    _ZPtCut = 100000.;
    _effic_study_txt = new std::fstream("efficiencystudy_file_zee.txt",std::ios::out);
  }
  
  // vary cut values and check the consistency of W mass
  _consistency_check = config.get("consistency_check", false);
  _invert_cut = config.get("invert_cut", false);
  _cut_under_study = config.get("cut_under_study", "");
  _runNo_lowcut = config.get("runNo_lowcut", 0);
  _runNo_highcut = config.get("runNo_highcut", 0);
  _InstLumi_lowcut  = config.get("InstLumi_lowcut", 100.);
  _InstLumi_highcut = config.get("InstLumi_highcut", 100.);
  _ScalarEt_lowcut = config.get("ScalarEt_lowcut", 0.);
  _ScalarEt_highcut = config.get("ScalarEt_highcut", 0.);
  _UPara_lowcut = config.get("UPara_lowcut", 0.);
  _UPara_highcut = config.get("UPara_highcut", 0.);
  _ElecEta_cut = config.get("ElecEta_cut", 0.);
  _ElecDetEta_lowcut = config.get("ElecDetEta_lowcut", 0.);
  _ElecDetEta_highcut = config.get("ElecDetEta_highcut", 0.);
  _ElecPhiMod_cut = config.get("ElecPhiMod_cut", 0.);
  _ElecPt_lowcut = config.get("ElecPt_lowcut", 0.);
  _ElecPt_highcut = config.get("ElecPt_highcut", 0.);
  _ElecPhi_lowcut = config.get("ElecPhi_lowcut", 0.);
  _ElecPhi_highcut = config.get("ElecPhi_highcut", 0.);
  _RecoilPhi_lowcut = config.get("RecoilPhi_lowcut", 0.);
  _RecoilPhi_highcut = config.get("RecoilPhi_highcut", 0.);
  _tickNo_lowcut = config.get("TickNum_lowcut",0);
  _tickNo_highcut = config.get("TickNum_highcut",160);
  _ZPTee_lowcut    = config.get("ZPTee_lowcut", 0.);
  _ZPTee_highcut   = config.get("ZPTee_highcut", 0.);
  _DetEtaCateg_cut = config.get("DetEtaCateg_cut", 0);
  _DropTriggerObjectMatchRequirement = config.get("DropTriggerObjectMatchRequirement", false);

  // study uparallel efficiency
  _uParaEffStudy = config.get("uParaEffStudy", false);
  if(_uParaEffStudy) {
    _ZUtCut = 100000.;
    _ZUtCut_lower = 0.;
    _ZPtCut = 100000.;
    _ZPtCut_lower = 0.;
    _NumZSpatialTrk = 0;
    _ZMassCut1 = 50.;
    _ZMassCut2 = 130.;

    _histos.add(ZCandUPara_Hist);
    _histos.add(ZCandUPara_Hist_2D);
      
  }

  // Study track match efficiency
  _trkMatchEffStudy = config.get("trkMatchEffStudy", false);
  _fiducialForwardElectron = config.get("fiducialForwardElectron", false);
  if (_trkMatchEffStudy){
    cout << "Performing Track Match Eff Study" << endl;
    _histos.add(ZCandTrkMatch_Hist);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_eta", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_caleta", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_pT", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_upara", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_eta", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_caleta", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_pT", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_upara", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_eta", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_caleta", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_pT", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_upara", 6);

    _histos.add(ZCandTrkMatch_Hist_2D);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_eta_pT", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_eta_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_caleta_pT", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_etam_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_etap_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_etam_etap", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_etap_etam", 6);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_upara_pz", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_eta_pT", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_caleta_pT", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_etam_etap", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_etap_etam", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_upara_pz", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_eta_pT", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_eta_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_caleta_pT", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_etam_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_etap_vtxz", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_etam_etap", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_etap_etam", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_upara_pz", 6);

    _histos.add(ZCandTrkMatch_Coarse_Hist_2D);
    _histos.clone("ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse", 6);
    _histos.clone("ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse", 6);
    _histos.clone("ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse", 6);


  }
  
  if (_trkMatchEffStudy && _MCStudy) {
    cout << "Performing -- True -- Track Match Eff Study" << endl;
    _histos.add(ZCandTrueTrkMatch_Hist);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_eta", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_caleta", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_pT", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_upara", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_eta", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_pT", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_upara", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_eta", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_caleta", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_pT", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_upara", 6);

    _histos.add(ZCandTrueTrkMatch_Hist_2D);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam", 6);
    _histos.clone("ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam", 6);
    _histos.clone("ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_eta_pT", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_eta_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam", 6);
    _histos.clone("ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz", 6);

  }

  // initialize random number generator
  _random = new TRandom3(0);
  gRandom = _random;
  
  // histograms
  _mc_histos.add(Z_MC_Hist);
  _mc_histos.add(Z_MC_Hist_2D);
  _mc_histos.add(Z_MC_Hist_Profile);
  _mc_histos.add(MC_RECOIL_Hist);
  _mc_histos.add(ZCand_Hist_2D_varbin);
  _histos.add(ZCand_Hist);
  _histos.add(ZCand_Hist_2D);
  _histos.add(ZCand_Hist_Profile);
  _histos.add(ZCand_Hist_2D_varbin);

  // For ZB event studies
  if (_MCStudy && _doZBevent) _histos.add(ZCand_ZBevent_Hist);

  // histograms for different regions
  // 0 for CCCC, 1 for CCEC, 2 for ECEC
  _histos.clone("ZCandElecE", 3);
  _histos.clone("ZCandElecPx", 3);
  _histos.clone("ZCandElecPy", 3);
  _histos.clone("ZCandElecPz", 3);
  _histos.clone("ZCandElec0Px", 3);
  _histos.clone("ZCandElec0Py", 3);
  _histos.clone("ZCandElec0Pz", 3);
  _histos.clone("ZCandElec1Px", 3);
  _histos.clone("ZCandElec1Py", 3);
  _histos.clone("ZCandElec1Pz", 3);
  _histos.clone("ZCandElecPt", 3);
  _histos.clone("ZCandElecPt_Upara", 6);
  _histos.clone("ZCandElec0Pt", 3);
  _histos.clone("ZCandElec1Pt", 3);
  _histos.clone("ZCandDiffElecPt", 3);
  _histos.clone("ZCandDiffElec0Pt", 3);
  _histos.clone("ZCandDiffElec1Pt", 3);
  _histos.clone("ZCandElecGenPt", 3);
  _histos.clone("ZCandElecGen0Pt", 3);
  _histos.clone("ZCandElecGen1Pt", 3);
  _histos.clone("ZCandElecRawGenPt", 3);
  _histos.clone("ZCandElecRawGen0Pt", 3);
  _histos.clone("ZCandElecRawGen1Pt", 3);

  _histos.clone("ZCandElec0E", 3);
  _histos.clone("ZCandElec1E", 3);
  _histos.clone("ZCandDiffElecE", 3);
  _histos.clone("ZCandDiffElec0E", 3);
  _histos.clone("ZCandDiffElec1E", 3);
  _histos.clone("ZCandElecGenE", 3);
  _histos.clone("ZCandElecGen0E", 3);
  _histos.clone("ZCandElecGen1E", 3);
  _histos.clone("ZCandElecRawGenE", 3);
  _histos.clone("ZCandElecRawGen0E", 3);
  _histos.clone("ZCandElecRawGen1E", 3);

  _histos.clone("ZCandElecPt_V_Mass", 3);
  _histos.clone("ZCandElecTrkPt", 3);
  _histos.clone("ZCandElecTrkPtTight", 3);
  _histos.clone("ZCandElecTrkCalMass", 3);
  _histos.clone("ZCandElecTrkPtOvETight", 3);
  _histos.clone("ZCandElecTrkPtOvE", 3);
  _histos.clone("ZCandElecTrkPhiEM3", 3);
  _histos.clone("ZCandElecTrkPhiEM3Mod", 3);
  _histos.clone("ZCandElecEta", 3);
  _histos.clone("ZCandElecDetEta", 3);
  _histos.clone("ZCandElecPhi", 3);
  _histos.clone("ZCandElecDetPhi", 3);
  _histos.clone("ZCandElecPhiTrkAtDCA", 3);
  _histos.clone("ZCandElecPhiTrkAtEM3", 3);
  _histos.clone("ZCandElecDetPhiCALO", 3);
  _histos.clone("ZCandPt", 3);
 _histos.clone("ZCandPx", 3);
 _histos.clone("ZCandPy", 3);
 _histos.clone("ZCandPz", 3);
  _histos.clone("ZCandAt", 3);
  _histos.clone("ZCandAl", 3);
  _histos.clone("ZCandMCPt", 3);
  _histos.clone("ZCandMCPtDiff", 3);
  _histos.clone("ZCandMCPtDiff_bin", 10);
  _histos.clone("ZCandMCPtDiff_genZPt_bin", 10);
  _histos.clone("ZCandMCPhiDiff", 3);
  _histos.clone("ZCandMCPhiDiff_bin", 10);
  _histos.clone("ZCandMass_bin", 10);
  _histos.clone("ZCandDiffMass_bin", 10);
  _histos.clone("ZCandElecPt_bin", 10);
  _histos.clone("ZCandElec0Pt_bin", 10);
  _histos.clone("ZCandElec1Pt_bin", 10);
  _histos.clone("ZCandDiffElecPt_bin", 10);
  _histos.clone("ZCandDiffElec0Pt_bin", 10);
  _histos.clone("ZCandDiffElec1Pt_bin", 10);
  _histos.clone("ZCandElecGenPt_bin", 10);
  _histos.clone("ZCandElecGen0Pt_bin", 10);
  _histos.clone("ZCandElecGen1Pt_bin", 10);
  _histos.clone("ZCandElecRawGenPt_bin", 10);
  _histos.clone("ZCandElecRawGen0Pt_bin", 10);
  _histos.clone("ZCandElecRawGen1Pt_bin", 10);

  _histos.clone("ZCandElecE_bin", 10);
  _histos.clone("ZCandElec0E_bin", 10);
  _histos.clone("ZCandElec1E_bin", 10);
  _histos.clone("ZCandDiffElecE_bin", 10);
  _histos.clone("ZCandDiffElec0E_bin", 10);
  _histos.clone("ZCandDiffElec1E_bin", 10);
  _histos.clone("ZCandElecGenE_bin", 10);
  _histos.clone("ZCandElecGen0E_bin", 10);
  _histos.clone("ZCandElecGen1E_bin", 10);
  _histos.clone("ZCandElecRawGenE_bin", 10);
  _histos.clone("ZCandElecRawGen0E_bin", 10);
  _histos.clone("ZCandElecRawGen1E_bin", 10);

  _histos.clone("ZCandCosDeltaPhi_EM1_EM2_bin", 10);  
  _histos.clone("ZCandDiffCosDeltaPhi_EM1_EM2_bin", 10);
  _histos.clone("ZCandDeltaEta_EM1_EM2_bin", 10);
  _histos.clone("ZCandDiffDeltaEta_EM1_EM2_bin", 10);
  _histos.clone("ZCandEta", 3);
  _histos.clone("ZCandPhi", 3);
  _histos.clone("ZCandMass", 3);  // Z mass calculated using cal+track information
  _histos.clone("ZCandDiffMass", 3);  // 
  _histos.clone("ZCandEMTrkMass", 3);
  _histos.clone("ZCandMass_TwoTrks", 3);
  _histos.clone("ZCandElecPt_TwoTrks_Both", 3);
  _histos.clone("ZCandElecPt_TwoTrks_Elec1", 3);
  _histos.clone("ZCandElecPt_TwoTrks_Elec2", 3);
  _histos.clone("ZCandMass_TwoTrks_Category",15);
  _histos.clone("ZCandElecPt_TwoTrks_Category",15);
  _histos.clone("ZCandTrksMass", 3);
  _histos.clone("ZCandMass_Cal", 3); // Z mass caluclated using cal information only
  _histos.clone("ZCandMass_Trks_Cal", 3);
  _histos.clone("ZCandMass_CCCC_Trks_Cal", 3);
  _histos.clone("ZCandMass_CCEC_Trks_Cal", 3);
  _histos.clone("ZCandMass_ECEC_Trks_Cal", 3);
  _histos.clone("ZCandRecoilPt", 3);
  _histos.clone("ZCandRecoilPhi", 3);
  _histos.clone("ZCandRecoilPx", 3);
  _histos.clone("ZCandRecoilPy", 3);
  _histos.clone("ZCandMet", 3);
  _histos.clone("ZCandMetPhi", 3);
  _histos.clone("ZCandMetX", 3);
  _histos.clone("ZCandMetY", 3);
  _histos.clone("ZCandEtaBalance", 3);
  _histos.clone("ZCandXiBalance", 3);
  _histos.clone("ZCandEtaImBalance", 3);
  _histos.clone("ZCandXiImBalance", 3);
  _histos.clone("ZCandInstLumi", 3);
  _histos.clone("ZCandScalarEt_V_Lumi",3);
  _histos.clone("ZCandScalarEt_V_Lumi2D",3);
  _histos.clone("ZCandVtx", 3);
  _histos.clone("ZCandNPV", 3);
  _histos.clone("ZCandTick", 3);
  _histos.clone("ZCandDeltaPhi_EM_Recoil", 3);
  _histos.clone("ZCandDeltaPhi_EM_Met", 3);
  _histos.clone("ZCandCosDeltaPhi_EM1_EM2", 3);
  _histos.clone("ZCandDiffCosDeltaPhi_EM1_EM2", 3);
  _histos.clone("ZCandPee_eta", 3);
  _histos.clone("ZCandPee_gen", 3);
  _histos.clone("ZCandDeltaPhi_EM1_EM2_Zpt_2pi_varbin", 3);
  _histos.clone("ZCandDeltaPhi_EM1_EM2", 3);
  _histos.clone("ZCandDeltaEta_EM1_EM2", 3);
  _histos.clone("ZCandDiffDeltaEta_EM1_EM2", 3);
  _histos.clone("ZCandDeltaPhi_Z_Recoil", 3);
  _histos.clone("ZCandDeltaPhi_Z_Met", 3);
  _histos.clone("ZCandElecUPara", 3);
  _histos.clone("ZCandElecUPerp", 3);
  _histos.clone("ZCandScalarEt", 3);
  _histos.clone("ZCandSqrtScalarEt", 3);
  _histos.clone("ZCandScalarEt_ZPtBin", 10);
  _histos.clone("ZCandSqrtScalarEt_ZPtBin", 10);
  _histos.clone("ZCandScalarEt_genZPt_bin", 10);
  _histos.clone("ZCandSqrtScalarEt_genZPt_bin", 10);

  // fz categories
  _histos.clone("ZcandElecPt_fz", 24);
  _histos.clone("ZcandElecE_fz", 24);
  _histos.clone("ZcandElecEta_fz", 24);
  _histos.clone("ZcandElecDetEta_fz", 24);
  _histos.clone("ZcandMass_CCCC_fz", 24);
  _histos.clone("ZcandMass_CCCC_fz_Coarse", 6);
  _histos.clone("ZcandElecPt_fz_Coarse", 6);      
  _histos.clone("ZcandElecE_fz_Coarse",   6);     
  _histos.clone("ZcandElecEta_fz_Coarse", 6);     
  _histos.clone("ZcandElecDetEta_fz_Coarse", 6); 

  // mass distributions for o track, 1 track and 2 tracks
  _histos.clone("ZCandMass_Trks", 3);
  _histos.clone("ZCandMass_CCCC_Trks", 3);
  _histos.clone("ZCandMass_CCEC_Trks", 3);
  _histos.clone("ZCandMass_ECEC_Trks", 3);
  _histos.clone("ZCandMass_V_fZ_CCCC", 3);
  _histos.clone("ZCandMass_V_fZ_CCEC", 3);
  _histos.clone("ZCandMass_V_fZ_ECEC", 3);
  _histos.clone("ZCandMass_V_fZ_CCCC_pro", 3);
  _histos.clone("ZCandMass_V_fZ_CCEC_pro", 3);
  _histos.clone("ZCandMass_V_fZ_ECEC_pro", 3);
  _histos.clone("ZCandfZ_CCCC", 3);
  _histos.clone("ZCandfZ_CCEC", 3);
  _histos.clone("ZCandfZ_ECEC", 3);
  _histos.clone("ZCandMass_vs_DetEta_CCCC_Trks", 3);
  _histos.clone("ZCandMass_vs_Eta____CCCC_Trks", 3);
  _histos.clone("ZCandMass_vs_Pt_____CCCC_Trks", 3);

  // Z mass in different trigger list and different eta, deteta regions
  // require two track matches
  // trigger categories according to D0 note 5374
  _histos.clone("ZCandMass_CCCC_TrigCategory", 10);
  _histos.clone("ZCandMass_CCCC_EtaCategory", 15);
  _histos.clone("ZCandMass_CCCC_DetEtaCategory", 15);
  _histos.clone("ZCandMass_CCCC_PhiModCategory", 15);
  _histos.clone("ZCandMass_CCCC_TrkPhiModCategory", 15);
  _histos.clone("ZCandMass_CCCC_TrkPhiEM3ModCategory", 15);
  _histos.clone("ZCandMass_CCCC_EM3PhiEM3ModCategory", 15);

  // for recoil system
  _histos.clone("ZCandEtaPeeRecoil", 3);
  _histos.clone("ZCandXiPeeRecoil", 3);
  _histos.clone("ZCandEtaPeeBalance", 3);
  _histos.clone("ZCandXiPeeBalance", 3);
  _histos.clone("ZCandEtaPeeImBalance", 3);
  _histos.clone("ZCandXiPeeImBalance", 3);
  _histos.clone("ZCandKappaUE", 3);
  _histos.clone("ZCandPt_V_HadResponse", 3);

  // eta/xi (im)balance, recoil and met for different pee bins
  _histos.clone("ZCandEtaBalance_bin", 10);
  _histos.clone("ZCandEtaImBalance_bin", 10);
  _histos.clone("ZCandXiBalance_bin", 10);
  _histos.clone("ZCandXiImBalance_bin", 10);
  _histos.clone("ZCandEtaImBalance_ZPt_Projected_bin", 10);
  _histos.clone("ZCandXiImBalance_ZPt_Projected_bin", 10);
  _histos.clone("ZCandEtaImBalance_genZPt_bin", 10);
  _histos.clone("ZCandXiImBalance_genZPt_bin", 10);
  _histos.clone("ZCandPt_Projected_bin", 10);
  _histos.clone("ZCandPee_eta_bin", 10);

  _histos.clone("ZCandNewEtaBalance_bin", 10);
  _histos.clone("ZCandNewXiBalance_bin", 10);
  _histos.clone("ZCandNewEtaBalance_ZPt_Projected_bin", 10);
  _histos.clone("ZCandNewXiBalance_ZPt_Projected_bin", 10);
  _histos.clone("ZCandNewEtaBalance_genZPt_bin", 10);
  _histos.clone("ZCandNewXiBalance_genZPt_bin", 10);

  _histos.clone("ZCandPt_bin", 10);
  _histos.clone("ZCandPhi_bin", 10);
  _histos.clone("ZCandRecoilPt_bin", 10);
  _histos.clone("ZCandRecoilPhi_bin", 10);
  _histos.clone("ZCandRecoilPt_ZPt_Projected_bin", 10);
  _histos.clone("ZCandRecoilPhi_ZPt_Projected_bin", 10);

  _histos.clone("ZCandRecoilPt_genZPt_bin", 10);
  _histos.clone("ZCandRecoilPhi_genZPt_bin", 10);
  _histos.clone("ZCandRecoilPx_bin", 10);
  _histos.clone("ZCandRecoilPy_bin", 10);
  _histos.clone("ZCandMet_bin", 10);
  _histos.clone("ZCandMetPhi_bin", 10);
  _histos.clone("ZCandMetX_bin", 10);
  _histos.clone("ZCandMetY_bin", 10);
  _histos.clone("ZCandDeltaPhi_Z_Recoil_bin", 10);
  _histos.clone("ZCandDeltaPhi_Z_Met_bin", 10);
  _histos.clone("ZCandDeltaPhi_EM1_EM2_bin", 10);

  // for E/P distribution
  _histos.clone("ZCandEOverP_Mod", 32);
  _histos.clone("ZCandRawEOverP_Mod", 32);
  _histos.clone("ZCandEOverP_V_ElecPhiMod", 32);
  _histos.clone("ZCandRawEOverP_V_ElecPhiMod", 32);

  // for phi crack efficiency
  if(_PhiCrackEffStudy) {
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pro_pTBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pro_EtaBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pTBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_EtaBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_pTBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_EtaBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_gen_pTBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_gen_EtaBin", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin_PassPtTrkMatch", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin_PassPtTrkMatch", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin_PassPtTrkMatch", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin_PassPtTrkMatch", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin_PassPt", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin_PassPt", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin_PassPt", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin_PassPt", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin_PassTrkMatch", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin_PassTrkMatch", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin_PassTrkMatch", 4);
    _histos.clone("ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin_PassTrkMatch", 4);

    _histos.clone("ZCandEMTrkMass_PhiMod", 50);  
  }


  if (_MCStudy && _doZBevent) {
    _histos.clone("ZCandScalarEt_ZB", 3);
  }

  // for EMF study
  if (_performEMFstudy) {
    _emf_histos.add(EMFstudy_Hist);
    //
    _emf_histos.clone("E1emf",6);
    _emf_histos.clone("E2emf",6);
    _emf_histos.clone("Eemf",6);
    //
    _emf_histos.cloneArray("EemfB",6,5);
    for (int ii=1; ii<6; ii++) {
      for (int i=0; i<5; i++) {
        TString n("EemfB_"); n+=ii; n+="_"; n+=i;
        _emf_histos.clone(n,_EMFstudyNLumiBins);
      }
    }
    //
    _emf_histos.clone("massK",15);
    _emf_histos.clone("InstLumZeeK",15);
    _emf_histos.clone("pTK",15);
    _emf_histos.clone("E1pTK",15);
    _emf_histos.clone("E2pTK",15);
    _emf_histos.clone("E1EK",15);
    _emf_histos.clone("E2EK",15);
    _emf_histos.clone("E1physetaK",15);
    _emf_histos.clone("E2physetaK",15);
    _emf_histos.clone("E1detetaK",15);
    _emf_histos.clone("E2detetaK",15);
    //
    _emf_histos.cloneArray("E1emfK",6,15);
    _emf_histos.cloneArray("E2emfK",6,15);
    _emf_histos.cloneArray("EemfK",6,15);
    //
    _emf_histos.clone("massKD",15);
    _emf_histos.clone("InstLumZeeKD",15);
    _emf_histos.clone("pTKD",15);
    _emf_histos.clone("E1pTKD",15);
    _emf_histos.clone("E2pTKD",15);
    _emf_histos.clone("E1EKD",15);
    _emf_histos.clone("E2EKD",15);
    _emf_histos.clone("E1physetaKD",15);
    _emf_histos.clone("E2physetaKD",15);
    _emf_histos.clone("E1detetaKD",15);
    _emf_histos.clone("E2detetaKD",15);
    //
    _emf_histos.cloneArray("E1emfKD",6,15);
    _emf_histos.cloneArray("E2emfKD",6,15);
    _emf_histos.cloneArray("EemfKD",6,15);
    //
    //
    _emf_histos.clone("mass",_EMFstudyNLumiBins);
    _emf_histos.clone("pT",_EMFstudyNLumiBins);
    _emf_histos.clone("RunNumZee",_EMFstudyNLumiBins);
    _emf_histos.clone("InstLumZee",_EMFstudyNLumiBins);
    _emf_histos.clone("nVtxZee",_EMFstudyNLumiBins);
    _emf_histos.clone("E1pT",_EMFstudyNLumiBins);
    _emf_histos.clone("E2pT",_EMFstudyNLumiBins);
    _emf_histos.clone("E1E",_EMFstudyNLumiBins);
    _emf_histos.clone("E2E",_EMFstudyNLumiBins);
    _emf_histos.clone("E1physeta",_EMFstudyNLumiBins);
    _emf_histos.clone("E2physeta",_EMFstudyNLumiBins);
    _emf_histos.clone("E1deteta",_EMFstudyNLumiBins);
    _emf_histos.clone("E2deteta",_EMFstudyNLumiBins);
    //
    _emf_histos.cloneArray("E1emf",6,_EMFstudyNLumiBins);
    _emf_histos.cloneArray("E2emf",6,_EMFstudyNLumiBins);
    _emf_histos.cloneArray("Eemf",6,_EMFstudyNLumiBins);
    //
    for (int i=0; i<15; i++) {
      TString n("massK_"); n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="InstLumZeeK_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="pTK_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E1pTK_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E2pTK_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E1EK_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E2EK_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E1physetaK_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E2physetaK_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E1detetaK_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E2detetaK_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      //
      for (int ii=1; ii<6; ii++) {
        n="E1emfK_"; n+=ii; n+="_"; n+=i;
        _emf_histos.clone(n,_EMFstudyNLumiBins);
        n="E2emfK_"; n+=ii; n+="_"; n+=i;
        _emf_histos.clone(n,_EMFstudyNLumiBins);
        n="EemfK_"; n+=ii; n+="_"; n+=i;
        _emf_histos.clone(n,_EMFstudyNLumiBins);
      }
    }
    //
    for (int i=0; i<15; i++) {
      TString n("massKD_"); n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="InstLumZeeKD_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="pTKD_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E1pTKD_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E2pTKD_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E1EKD_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E2EKD_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E1physetaKD_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E2physetaKD_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E1detetaKD_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="E2detetaKD_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      //
      for (int ii=1; ii<6; ii++) {
        n="E1emfKD_"; n+=ii; n+="_"; n+=i;
        _emf_histos.clone(n,_EMFstudyNLumiBins);
        n="E2emfKD_"; n+=ii; n+="_"; n+=i;
        _emf_histos.clone(n,_EMFstudyNLumiBins);
        n="EemfKD_"; n+=ii; n+="_"; n+=i;
        _emf_histos.clone(n,_EMFstudyNLumiBins);
      }
    }
    //
    //
    _emf_histos.clone("ECE1emf",6);
    _emf_histos.clone("ECE2emf",6);
    _emf_histos.clone("ECEemf",6);
    //
    _emf_histos.clone("ECmassB",30);
    _emf_histos.clone("ECInstLumZeeB",30);
    _emf_histos.clone("ECpTB",30);
    _emf_histos.clone("ECE1pTB",30);
    _emf_histos.clone("ECE2pTB",30);
    _emf_histos.clone("ECE1EB",30);
    _emf_histos.clone("ECE2EB",30);
    _emf_histos.clone("ECE1physetaB",30);
    _emf_histos.clone("ECE2physetaB",30);
    _emf_histos.clone("ECE1detetaB",30);
    _emf_histos.clone("ECE2detetaB",30);
    //
    _emf_histos.cloneArray("ECE1emfB",6,30);
    _emf_histos.cloneArray("ECE2emfB",6,30);
    _emf_histos.cloneArray("ECEemfB",6,30);
    //
    //
    _emf_histos.clone("ECmass",_EMFstudyNLumiBins);
    _emf_histos.clone("ECpT",_EMFstudyNLumiBins);
    _emf_histos.clone("ECRunNumZee",_EMFstudyNLumiBins);
    _emf_histos.clone("ECInstLumZee",_EMFstudyNLumiBins);
    _emf_histos.clone("ECnVtxZee",_EMFstudyNLumiBins);
    _emf_histos.clone("ECE1pT",_EMFstudyNLumiBins);
    _emf_histos.clone("ECE2pT",_EMFstudyNLumiBins);
    _emf_histos.clone("ECE1E",_EMFstudyNLumiBins);
    _emf_histos.clone("ECE2E",_EMFstudyNLumiBins);
    _emf_histos.clone("ECE1physeta",_EMFstudyNLumiBins);
    _emf_histos.clone("ECE2physeta",_EMFstudyNLumiBins);
    _emf_histos.clone("ECE1deteta",_EMFstudyNLumiBins);
    _emf_histos.clone("ECE2deteta",_EMFstudyNLumiBins);
    //
    _emf_histos.cloneArray("ECE1emf",6,_EMFstudyNLumiBins);
    _emf_histos.cloneArray("ECE2emf",6,_EMFstudyNLumiBins);
    _emf_histos.cloneArray("ECEemf",6,_EMFstudyNLumiBins);
    //
    for (int i=0; i<30; i++) {
      TString n("ECmassB_"); n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="ECInstLumZeeB_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="ECpTB_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="ECE1pTB_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="ECE2pTB_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="ECE1EB_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="ECE2EB_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="ECE1physetaB_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="ECE2physetaB_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="ECE1detetaB_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      n="ECE2detetaB_"; n+=i;
      _emf_histos.clone(n,_EMFstudyNLumiBins);
      //
      for (int ii=1; ii<6; ii++) {
        n="ECE1emfB_"; n+=ii; n+="_"; n+=i;
        _emf_histos.clone(n,_EMFstudyNLumiBins);
        n="ECE2emfB_"; n+=ii; n+="_"; n+=i;
        _emf_histos.clone(n,_EMFstudyNLumiBins);
        n="ECEemfB_"; n+=ii; n+="_"; n+=i;
        _emf_histos.clone(n,_EMFstudyNLumiBins);
      }
    }
  }

  // for MC
  if (_smearingStudy){
    _mc_histos.clone("ZElectronSmearPt_CCCC_2trks_TruePtBin",20);
    _mc_histos.clone("ZElectronSmearE_CCCC_2trks_TrueEBin",20);
    _mc_histos.clone("ZElectronSmearE_CCCC_2trks_TrueE_Thetabin",4);
    _mc_histos.clone("ZElectronSmearE_CCCC_2trks_TrueE_Thetabin_0",20);
    _mc_histos.clone("ZElectronSmearE_CCCC_2trks_TrueE_Thetabin_1",20);
    _mc_histos.clone("ZElectronSmearE_CCCC_2trks_TrueE_Thetabin_2",20);
    _mc_histos.clone("ZElectronSmearE_CCCC_2trks_TrueE_Thetabin_3",20);
  }
  _mc_histos.clone("MC_RECOIL_Pt_V_RECO_RECOIL_pt",30);
  _mc_histos.clone("MC_RECOIL_Pt_V_RECO_RECOIL_pt_response",30);
  if (_smearingStudy){
    _mc_histos.clone("ZRecoilSmearPt_TruePtBin",20);
     _mc_histos.clone("ZRecoilSmearPhi_TruePtBin",20);
     _mc_histos.clone("ZRecoilSmearE_TrueEBin",20);
   }

  _mc_histos.clone("ZMC_RECO_deltaeta",3);
  _mc_histos.clone("ZMC_RECO_deltaphi",3);
  _mc_histos.clone("ZMC_RECO_deltapx",3);
  _mc_histos.clone("ZMC_RECO_deltapy",3);
  _mc_histos.clone("ZMC_RECO_deltapz",3);
  _mc_histos.clone("ZMC_RECO_deltaPt",3);
  _mc_histos.clone("ZMC_RECO_deltaMass",3);
  _mc_histos.clone("ZMC_RECO_deltaZPt",3);

  _mc_histos.clone("ZMCElecE", 3);
  _mc_histos.clone("ZMCElecE_V_ZRECOElecE", 3);
  _mc_histos.clone("ZMCElecE_V_ZRECOElecE_0", 10);
  _mc_histos.clone("ZMCElecE_V_ZRECOElecE_1", 10);
  _mc_histos.clone("ZMCElecE_V_ZRECOElecE_2", 10);

  _mc_histos.clone("ZMCElecPt_V_ZRECOElecPt", 3);
  _mc_histos.clone("ZMCElecEta_V_ZRECOElecEta", 3);
  _mc_histos.clone("ZMCElecPhi_V_ZRECOElecPhi", 3);

  _mc_histos.clone("ZMCElecE_V_ZRECOElecE_prof", 3);
  _mc_histos.clone("ZMCElecPt_V_ZRECOElecPt_prof", 3);
  _mc_histos.clone("ZMCElecPt_V_ZRECOElecPt_prof2", 3);
  _mc_histos.clone("ZMC_RECO_deltaR", 3);

  // get cuts for RECO electrons for hadronic recoil transverse energy flow studies 
  _ElecLoose_nMin   = config.get("ZCand2Trks_EtFlow_ElecLoose_nMin",   2);       // require >=2 loose electrons
  _ElecLoose_EtaMax = config.get("ZCand2Trks_EtFlow_ElecLoose_EtaMax", 1000.0);  // no cut
  _ElecLoose_PtMin  = config.get("ZCand2Trks_EtFlow_ElecLoose_PtMin",  0.0);     // no cut
  _ElecTight_nMin   = config.get("ZCand2Trks_EtFlow_ElecTight_nMin",   0);       // no cut
  _ElecTight_EtaMax = config.get("ZCand2Trks_EtFlow_ElecTight_EtaMax", 1000.0);  // no cut
  _ElecTight_PtMin  = config.get("ZCand2Trks_EtFlow_ElecTight_PtMin",  0.0);     // no cut
  if(( _ElecTight_PtMin < _ElecLoose_PtMin ) || ( _ElecTight_EtaMax > _ElecLoose_EtaMax )) {
    cerr << "ZAnalysis: Wrong specification of Loose and Tight cuts!!!" << endl
	 << "                      pT(Loose e)>=" << _ElecLoose_PtMin << " GeV, |eta(Loose e)|<" << _ElecLoose_EtaMax << endl
	 << "                      pT(Tight e)>=" << _ElecTight_PtMin << " GeV, |eta(Tight e)|<" << _ElecTight_EtaMax << endl;
    throw;
  }
  /////////// cout << "ZAnalysis: Loose/Thight elec config OK" << endl;

  _do_RecoilEtFlow_studies = config.get("ZCand2Trks_EtFlow_studies", false);
  cout << "ZAnalysis: ZCand2Trks_EtFlow_studies OK" << endl;

  _RecoilEtFlow_studies_TowCut = config.get("ZCand2Trks_EtFlow_studies_TowCut", 99999.);

  _dumpRecoilInfo = config.get("ZCand2Trks_dumpRecoilInfo", false);
  cout << "ZAnalysis: ZCand2Trks_dumpRecoilInfo OK" << endl;

  //  if((_do_RecoilEtFlow_studies || _dumpRecoilInfo) && !_MCStudy) {                                                                                                    
  //   cerr << "ZAnalysis: MCStudy parameter must be set to 'true' whenever ET-flow studies and/or" << endl                                                               
  //        << "           dumping the events with generator/reco recoil information is requested!!!" << endl                                                             
  //        << "           MCStudy                   = " << _MCStudy << endl                                                                                              
  //        << "           ZCand2Trks_EtFlow_studies = " << _do_RecoilEtFlow_studies << endl                                                                              
  //        << "           ZCand2Trks_dumpRecoilInfo = " << _dumpRecoilInfo << endl;                                                                                      
  if(_dumpRecoilInfo && !_MCStudy) {
    cerr << "ZAnalysis: MCStudy parameter must be set to 'true' if dumping" << endl
         << "           generator and reco recoil information is requested!!!" << endl
         << "           MCStudy                   = " << _MCStudy << endl
         << "           ZCand2Trks_dumpRecoilInfo = " << _dumpRecoilInfo << endl;
    throw;
  }

  string _EtFlow_fname = config.get("ZCand2Trks_EtFlow_studies_inputfile", " ");
  cout << "ZAnalysis: ZCand2Trks_EtFlow_studies_inputfile OK" << endl;

  if(_do_RecoilEtFlow_studies && _EtFlow_fname==" ") {

    cerr << "ZAnalysis: ET-flow studies are enabled, but the input file with relative response" << endl
	 << "           per PHI towers is missiing!!!" << endl
	 << "           MCStudy                             = " << _MCStudy << endl
	 << "           ZCand2Trks_EtFlow_studies           = " << _do_RecoilEtFlow_studies << endl
	 << "           ZCand2Trks_EtFlow_studies_inputfile = " << _EtFlow_fname << endl;
    throw;
  }
  for(int iphi=-31; iphi<=32; iphi++) _RelResponse_scale[iphi]=1.0;
  cout << "ZAnalysis: _RelResponse_scale[iphi] init to 1 OK" << endl;

  fstream *_EtFlow_input=new fstream(_EtFlow_fname.c_str(), std::ios::in);
  cout << "ZAnalysis: _EtFlow_input open OK" << endl;

  while( _EtFlow_input->good() ) {
    int    iphi=0;
    double resp=-1;
    /////////// cout << "ZAnalysis: _EtFlow_input->good() loop OK" << endl;
    (*_EtFlow_input) >> iphi >> resp;
    if(iphi>=-31 && iphi<=32 && resp>=0.0) _RelResponse_scale[iphi]=resp;
  };
  _EtFlow_input->close();
  cout << "ZAnalysis: _EtFlow_input->close() OK" << endl;

  // hadronic recoil transverse energy flow studies (wrt direction of the true MC recoil)
  if(_do_RecoilEtFlow_studies) {
    _EtFlow_histos.add(ZCand2Trks_EtFlow_Hist);        // 1d histograms
    _EtFlow_histos.add(ZCand2Trks_EtFlow_Profile);     // profiles
    _EtFlow_histos.add(ZCand2Trks_EtFlow_Profile_2D);     // profiles
    _EtFlow_histos.add(ZCand2Trks_EtFlow_Profile_VarX);// profiles
    const int nbins_cuts=_EtFlow_histos.tprofile("ZCand2Trks_EtFlow_genZPt_V_genZPt")->GetNbinsX(); 
    cout << "ZAnalysis: clone - begin" << endl;

    // clone some histograms
    const string histname[]={ 
      "ZCand2Trks_EtFlow_genZPt",
      "ZCand2Trks_EtFlow_recoZPt",
      "ZCand2Trks_EtFlow_genUt",
      "ZCand2Trks_EtFlow_recoUt",
      "ZCand2Trks_EtFlow_recoRecoilPhi",
      "ZCand2Trks_EtFlow_recoRecoilResp",
      "ZCand2Trks_EtFlow_recoRecoilRespPrj",
      "ZCand2Trks_EtFlow_DPhi_recoUt_genZPt",
      "ZCand2Trks_EtFlow_DPhi_recoUt_recoZPt",
      "ZCand2Trks_EtFlow_DPhi_CellsUt_recoUt",
      //      "ZCand2Trks_EtFlow_DPhi_CellsScaledUt_recoUt",
      "ZCand2Trks_EtFlow_recoUt_V_DPhi_recoUt_genZPt",
      "ZCand2Trks_EtFlow_recoUt_V_DPhi_recoUt_recoZPt",
      "ZCand2Trks_EtFlow_CellsUt",
      //      "ZCand2Trks_EtFlow_CellsScaledUt",
      "ZCand2Trks_EtFlow_CellsRecoilPhi",
      //      "ZCand2Trks_EtFlow_CellsScaledRecoilPhi",
      "ZCand2Trks_EtFlow_CellsRecoilResp",
      //      "ZCand2Trks_EtFlow_CellsScaledRecoilResp",
      "ZCand2Trks_EtFlow_CellsRecoilRespPrj",
      //      "ZCand2Trks_EtFlow_CellsScaledRecoilRespPrj",
      "ZCand2Trks_EtFlow_CellsUt_V_DPhi_CellsUt_genZPt",
      //      "ZCand2Trks_EtFlow_CellsScaledUt_V_DPhi_CellsScaledUt_genZPt",
      "ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_recoZPt",
      //      "ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_recoZPt",
      "ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_genZPt"
      //,
      //      "ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_genZPt"
    };
    const int nhist=sizeof(histname)/sizeof(string);
    for(int ihist=0;ihist<nhist;ihist++) {
      _EtFlow_histos.clone(histname[ihist].c_str(), nbins_cuts, "_genZPt_bin" );
      _EtFlow_histos.clone(histname[ihist].c_str(), nbins_cuts, "_bin" );
    }
    cout << "ZAnalysis: clone - OK" << endl;
  }

  // dump measured hadronic recoil and generated Z info to an ASCII file
  string _dumpRecoilFile = config.get("ZCand2Trks_dumpRecoilFile", "zee_recoil_dump.txt");
  _zee_out_recoil_txt=0;
  if(_dumpRecoilInfo) _zee_out_recoil_txt = new fstream(_dumpRecoilFile.c_str(), std::ios::out);
  if(_zee_out_recoil_txt) {
    _zee_out_recoil_txt->flags( ios::right | ios::scientific );
    (*_zee_out_recoil_txt) << setw(9)  << "#  Run.No" 
			   << setw(9)  << "Evt.No" 
			   << setw(16) << "gen.Z.Px" 
			   << setw(16) << "gen.Z.Py" 
			   << setw(16) << "gen.Z.Pz" 
			   << setw(16) << "gen.Z.E" 
			   << setw(16) << "gen.rec.Px" 
			   << setw(16) << "gen.rec.Py" 
			   << setw(16) << "gen.rec.Pz" 
			   << setw(16) << "gen.rec.E" 
			   << setw(16) << "rec.Px" 
			   << setw(16) << "rec.Py" 
			   << setw(16) << "SET(noEM)" 
			   << setw(16) << "Tot.SET" << endl;
  }

  // initialize event counters
  _events_fail_trigger_requirements = 0;

  // create a text file to write out z candidate run number and event number
  if(!_MCStudy) _zee_out_txt = new fstream("zee_run_event_number.txt", std::ios::out);
  if (_doRatioMethod){
    _ratiomethod = new CAFRatioMethod(name);
    std::cout << " Done with CAFRatio Init " << std::endl;
  }

  // write out root tree
  _createRootTree = config.get("createRootTree", false);
  if(_createRootTree) {
    _roottupleFile = new TFile("ZRootTree.root", "recreate");
    _tree = new TTree("ZTree", "");
  
    _tree->Branch("nem", &_nem, "nem/I");
    _tree->Branch("em_e", &em_e[0], "em_e[2]/F");
    _tree->Branch("em_rawe", &em_rawe[0], "em_rawe[2]/F");
    _tree->Branch("em_pt", &em_pt[0], "em_pt[2]/F");
    _tree->Branch("em_eta", &em_eta[0], "em_eta[2]/F");
    _tree->Branch("em_deteta", &em_deteta[0], "em_deteta[2]/F");
    _tree->Branch("em_phi", &em_phi[0], "em_phi[2]/F");
    _tree->Branch("em_detphi", &em_detphi[0], "em_detphi[2]/F");
    _tree->Branch("em_trkpt", &em_trkpt[0], "em_trkpt[2]/F");
    _tree->Branch("em_trkphi", &em_trkphi[0], "em_trkphi[2]/F");
    _tree->Branch("em_trkphiEM3", &em_trkphiEM3[0], "em_trkphiEM3[2]/F");
    _tree->Branch("em_hm8", &em_hm8[0], "em_hm8[2]/F");
    _tree->Branch("em_hm7", &em_hm7[0], "em_hm7[2]/F");
  }

  _createRootTree2 = config.get("createRootTree2", false);
  if(_createRootTree2) {
    _roottupleFile2 = new TFile("ZRootTree2.root", "recreate");
    _tree2 = new TTree("ZTree2", "");
    _tree2->Branch("ZBrunNum", &tree2_ZBrunnum, "ZBrunNum/I");
    _tree2->Branch("ZBeventNum", &tree2_ZBeventnum, "ZBeventNum/I");
    _tree2->Branch("runNum", &tree2_runnum, "runNum/I");
    _tree2->Branch("eventNum", &tree2_eventnum, "eventNum/I");
    _tree2->Branch("Mz", &tree2_Mz, "Mz/F");
    _tree2->Branch("Ptz", &tree2_Ptz, "Ptz/F");
    _tree2->Branch("Luminosity", &tree2_lumi, "Luminosity/F");
    _tree2->Branch("ScalarEt", &tree2_set, "ScalarEt/F");
    _tree2->Branch("ZUt", &tree2_ZUt, "ZUt/F");
    _tree2->Branch("em_e", &tree2em_e[0], "em_e[2]/F");
    _tree2->Branch("em_pt", &tree2em_pt[0], "em_pt[2]/F");
    _tree2->Branch("em_eta", &tree2em_eta[0], "em_eta[2]/F");
    _tree2->Branch("em_phi", &tree2em_phi[0], "em_phi[2]/F");
    _tree2->Branch("em_deteta", &tree2em_deteta[0], "em_deteta[2]/F");
    _tree2->Branch("em_detphi", &tree2em_detphi[0], "em_detphi[2]/F");
    _tree2->Branch("em_upara", &tree2em_upara[0], "em_upara[2]/F");
    _tree2->Branch("em_trk_prob", &tree2em_trk_prob[0], "em_trk_prob[2]/F");
    _tree2->Branch("em_trk_nsmt", &tree2em_nsmt[0], "em_trk_nsmt[2]/I");
    _tree2->Branch("em_trk_pt", &tree2em_trk_pt[0], "em_trk_pt[2]/F");
    _tree2->Branch("weight", &tree2_weight, "weight/F");

  }
   

  _fillztree = config.get("fillztree", false);
  if(_fillztree) {
    _tree3 = new TTree("z", "");
    _tree3->Branch("run", &tree3_run, "run/I");
    _tree3->Branch("evt",  &tree3_evt,   "evt/I");
    _tree3->Branch("lumi", &tree3_lumi, "lumi/F");
    _tree3->Branch("trigflg", &tree3_trigflg, "trigflg/I");
    _tree3->Branch("passtrig", &tree3_passtrig[0], "passtrig[2]/I");
    _tree3->Branch("passtrig5", &tree3_passtrig5[0], "passtrig5[2]/I");
    _tree3->Branch("passtrig6", &tree3_passtrig6[0], "passtrig6[2]/I");
    _tree3->Branch("passtrig7", &tree3_passtrig7[0], "passtrig7[2]/I");

    _tree3->Branch("passL1", &tree3_passl1[0], "passL1[2]/I");
    _tree3->Branch("passL2EM22", &tree3_passl2em22[0], "passL2EM22[2]/I");
    _tree3->Branch("passL2EM25", &tree3_passl2em25[0], "passL2EM25[2]/I");
    _tree3->Branch("passL2ISO", &tree3_passl2iso[0], "passL2ISO[2]/I");
    _tree3->Branch("passL2LH", &tree3_passl2lh[0], "passL2LH[2]/I");
    _tree3->Branch("passL3SHT25", &tree3_passl3sht25[0], "passL3SHT25[2]/I");
    _tree3->Branch("passL3SHT27", &tree3_passl3sht27[0], "passL3SHT27[2]/I");

    _tree3->Branch("L1Et", &tree3_l1Et[0], "L1Et[2]/D");
    _tree3->Branch("L2EM22Et", &tree3_l2em22Et[0], "L2EM22Et[2]/D");
    _tree3->Branch("L2EM25Et", &tree3_l2em25Et[0], "L2EM25Et[2]/D");
    _tree3->Branch("L2ISOEt", &tree3_l2isoEt[0], "L2ISOEt[2]/D");
    _tree3->Branch("L2LHEt", &tree3_l2lhEt[0], "L2LHEt[2]/D");
    _tree3->Branch("L3SHT25Et", &tree3_l3sht25Et[0], "L3SHT25Et[2]/D");
    _tree3->Branch("L3SHT27Et", &tree3_l3sht27Et[0], "L3SHT27Et[2]/D");
 
    _tree3->Branch("type", &tree3_type, "type/I");
    _tree3->Branch("cut", &tree3_cut, "cut/I");

    _tree3->Branch("mee", &tree3_mee, "mee/F");
    _tree3->Branch("ptee", &tree3_ptee, "ptee/F");
    _tree3->Branch("set", &tree3_set, "set/F");
    _tree3->Branch("met", &tree3_met, "met/F");
    _tree3->Branch("zut", &tree3_zut, "zut/F");
    _tree3->Branch("zphi", &tree3_zphi, "zphi/F");
    _tree3->Branch("metphi", &tree3_metphi, "mephit/F");
    _tree3->Branch("zutphi", &tree3_zutphi, "zutphi/F");
    _tree3->Branch("metdelphi", &tree3_metdelphi, "metdelphi/F");
    _tree3->Branch("zutdelphi", &tree3_zutdelphi, "zutdelphi/F");
    _tree3->Branch("vtxz", &tree3_vtxz, "vtxz/F");
    _tree3->Branch("vtxtruez", &tree3_vtxtruez, "vtxtruez/F");
    _tree3->Branch("e", &tree3_e[0], "e[2]/F");
    _tree3->Branch("pt", &tree3_pt[0], "pt[2]/F");
    _tree3->Branch("chg", &tree3_chg[0], "chg[2]/F");
    _tree3->Branch("upara", &tree3_upara[0], "upara[2]/F");
    _tree3->Branch("caloriphi", &tree3_caloriphi[0], "caloriphi[2]/F");
    _tree3->Branch("trkphidca", &tree3_trkphidca[0], "trkphidca[2]/F");
    _tree3->Branch("trkphiem3", &tree3_trkphiem3[0], "trkphiem3[2]/F");
    _tree3->Branch("hm7", &tree3_hm7[0], "hm7[2]/F");
    _tree3->Branch("hm8", &tree3_hm8[0], "hm8[2]/F");
    _tree3->Branch("emf", &tree3_emf[0], "emf[2]/F");
    _tree3->Branch("iso", &tree3_iso[0], "iso[2]/F");
    _tree3->Branch("cc", &tree3_cc[0], "cc[2]/I");
    _tree3->Branch("eta", &tree3_eta[0], "eta[2]/F");
    _tree3->Branch("deteta", &tree3_deteta[0], "deteta[2]/F"); 
    _tree3->Branch("ccphifidcal", &tree3_ccphifidcal[0], "ccphifidcal[2]/I");
    _tree3->Branch("ccphifidtrk", &tree3_ccphifidtrk[0], "ccphifidtrk[2]/I");
    _tree3->Branch("phifidcal", &tree3_phifidcal[0], "phifidcal[2]/I");
    _tree3->Branch("phifidtrk", &tree3_phifidtrk[0], "phifidtrk[2]/I");
    _tree3->Branch("trkspat", &tree3_trkspat[0], "trkspat[2]/I");
    _tree3->Branch("trkgood", &tree3_trkgood[0], "trkgood[2]/I");
    _tree3->Branch("trkprob", &tree3_trkprob[0],  "trkprob[2]/F");
    _tree3->Branch("trknsmt", &tree3_trknsmt[0],  "trknsmt[2]/I");
    _tree3->Branch("trkpt",   &tree3_trkpt[0]  ,  "trkpt[2]/F");

    _tree3->Branch("id",   &tree3_id[0]  ,  "id[2]/I");
    _tree3->Branch("etafid",   &tree3_etafid[0]  ,  "etafid[2]/I");
    _tree3->Branch("ccetafid",   &tree3_ccetafid[0]  ,  "ccetafid[2]/I");
    _tree3->Branch("fid",   &tree3_fid[0]  ,  "fid[2]/I");
    _tree3->Branch("ccfid",   &tree3_ccfid[0]  ,  "ccfid[2]/I");

    tree3_run=tree3_evt=tree3_trigflg=tree3_type=tree3_cut=-555;
    tree3_lumi=tree3_mee=tree3_ptee=tree3_zphi=-555.;
    tree3_set=tree3_met=tree3_zut=tree3_metphi=tree3_zutphi=-555.;
    tree3_metdelphi=tree3_zutdelphi=tree3_vtxz=tree3_vtxtruez=-555.;
    tree3_chg[0]=-555.; 
    tree3_passtrig5[0]=tree3_passtrig6[0]=tree3_passtrig7[0]=-555; 
    tree3_e[0]=tree3_pt[0]=tree3_upara[0]=tree3_chg[0]=-555.;           
    
    tree3_caloriphi[0]=tree3_trkphidca[0]=tree3_trkphiem3[0]=-555.;
    tree3_eta[0]=tree3_deteta[0]=tree3_hm7[0]=tree3_hm8[0]=-555.;
    tree3_emf[0]=tree3_iso[0]=-555.;
    tree3_cc[0]=tree3_ccphifidcal[0]=tree3_ccphifidtrk[0]=-555;
    tree3_phifidcal[0]=tree3_phifidtrk[0]=-555;
    tree3_trkspat[0]=tree3_trkgood[0]=tree3_trknsmt[0]=-555;
    tree3_trkprob[0]=-555.;
    tree3_trkpt[0]=tree3_e[1]=tree3_pt[1]=tree3_upara[1]=tree3_chg[1]=-555.;
    tree3_passtrig5[0]=tree3_passtrig6[0]=tree3_passtrig7[1]=-555;
    tree3_id[0]=-555;
    tree3_etafid[0]=tree3_ccetafid[0]=tree3_fid[0]=tree3_ccfid[0]=-555;
    
    tree3_caloriphi[1]=tree3_trkphidca[1]=tree3_trkphiem3[1]=-555.;
    tree3_eta[1]=tree3_deteta[1]=tree3_hm7[1]=tree3_hm8[1]=-555.;
    tree3_emf[1]=tree3_iso[1]=-555.;
    tree3_cc[1]=tree3_ccphifidcal[1]=tree3_ccphifidtrk[1]=-555;
    tree3_phifidcal[1]=tree3_phifidtrk[1]=-555;
    tree3_trkspat[1]=tree3_trkgood[1]=tree3_trknsmt[1]=-555;
    tree3_trkprob[1]=-555.;
    tree3_trkpt[1]=-555.;
    
    tree3_passl1[0]=tree3_passl2em22[0]=tree3_passl2em25[0]=tree3_passl2iso[0]=tree3_passl2lh[0]=tree3_passl3sht25[0]=tree3_passl3sht27[0]=-555;
    tree3_passl1[1]=tree3_passl2em22[1]=tree3_passl2em25[1]=tree3_passl2iso[1]=tree3_passl2lh[1]=tree3_passl3sht25[1]=tree3_passl3sht27[1]=-555;
    tree3_l1Et[0]=tree3_l2em22Et[0]=tree3_l2em25Et[0]=tree3_l2isoEt[0]=tree3_l2lhEt[0]=tree3_l3sht25Et[0]=tree3_l3sht27Et[0]=-555.;
    tree3_l1Et[1]=tree3_l2em22Et[1]=tree3_l2em25Et[0]=tree3_l2isoEt[1]=tree3_l2lhEt[1]=tree3_l3sht25Et[1]=tree3_l3sht27Et[1]=-555.;
    tree3_id[1]=-555;
    tree3_etafid[1]=tree3_ccetafid[1]=tree3_fid[1]=tree3_ccfid[1]=-555;
    
  }



  cout << "ZAnalysis: Ended OK" << endl;
}

// study phi crack efficiency
void ZAnalysis::PhiCrackEffStudy(cafe::Event& event, vector<CAFEMObj*> emobjs) {

  int polarity = (int)(event.getGlobal()->solpol());
  polarity = 2*polarity-1;
  
  // different numbers for data and full MC
  // we found that using 21cm for both data and full MC, the phi difference between electrons and 
  // positrons match with each other
  double corr_EM3 = 21.;
  if(_MCStudy) corr_EM3 = 21.;
  
  vector<CAFTrack *> good_trks;
  if(event.get("Good Tracks", good_trks)) {     
    
    // 
    // method based on generator level information
    //
    float vtx_z = 0.;
    if(_MCStudy && event.get("Best primary vertexZ", vtx_z)) {      
      std::vector<TMBMCpart *> raw_mc_electrons;
      if(event.get("raw mc electrons", raw_mc_electrons)) {
	
	// also add tag requirement
	for(int em=0; em<emobjs.size(); em++) {
	  if(emobjs[em]->Pt()>25. && emobjs[em]->emfrac()>0.9 && emobjs[em]->iso()<0.15 && emobjs[em]->HMx7()<12. && 
	     fabs(emobjs[em]->CalDetectorEta())<1. && emobjs[em]->has_good_spatial_track_match()) {       
	    
	    for(int ielec=0; ielec<raw_mc_electrons.size(); ielec++) {
	      int charge = 0;
	      if(raw_mc_electrons[ielec]->pdgid()==11) charge = -1;
	      else charge = 1;
	      
	      double pT_gen = raw_mc_electrons[ielec]->Pt();
	      // we have to extrapolate generator-level electron to EM3, here we used the true pT
              // while for track extrapolation, we use reconstructed pT
              // if we still 21 cm, the phi difference between electrons and positrons 
	      // do not match with each other 
	      double phiCorr = (22./CC_3R*polarity*charge)/pT_gen;	      
	      double phiGbl = raw_mc_electrons[ielec]->Phi() + phiCorr;
	      double trk_theta = kinem::theta(raw_mc_electrons[ielec]->Eta());
	      
	      //
	      // use true primary vertex
	      //
	      double mc_vtx_z = vtx_z;
	      cafe::Collection<TMBMCvtx> mc_vtxs = event.getMCVertices();
	      if(mc_vtxs.size()>0) mc_vtx_z = mc_vtxs[0].z();
	      
	      double zem3 = mc_vtx_z + CC_3R/tan(trk_theta);
	      
	      double det_x, det_y, det_theta, det_r;
	      if(zem3 > 125.){  // pos EC
		double trk_r = fabs((EC_3Z_SOUTH-mc_vtx_z)*tan(trk_theta));
		det_x = trk_r*cos(phiGbl) - EC_XSHIFT_SOUTH;
		det_y = trk_r*sin(phiGbl) - EC_YSHIFT_SOUTH;
		det_r = sqrt(det_x*det_x +det_y*det_y);
		det_theta = atan2(det_r, EC_3Z);
	      } else if(zem3 > -125.) { // CC
		det_x = CC_3R*cos(phiGbl) - CC_XSHIFT;
		det_y = CC_3R*sin(phiGbl) - CC_YSHIFT;
		det_r = sqrt(det_x*det_x +det_y*det_y);
		det_theta = atan2(det_r, zem3-CC_ZSHIFT);
	      } else { // neg EC
		double trk_r = fabs((EC_3Z_NORTH-mc_vtx_z)*tan(trk_theta));
		det_x = trk_r*cos(phiGbl) - EC_XSHIFT_NORTH;
		det_y = trk_r*sin(phiGbl) - EC_YSHIFT_NORTH;
		det_r = sqrt(det_x*det_x +det_y*det_y);
		det_theta = atan2(det_r, -EC_3Z);
	      }
	      
	      // extrapolated particle phi at EM3    
	      double DetPhiEM3_gen = kinem::phi(det_x, det_y);
	      double DetEtaEM3_gen = -log(tan(det_theta/2.));
	    
              //  
	      // generator phimodule
              //
	      int phimodule_gen = (int)(16.*DetPhiEM3_gen/(TMath::Pi()));
	      double phimod_gen = fmod(16.*DetPhiEM3_gen/TMath::Pi(), 1.0);
	      
	      // calculate tag and generator level electron separation cut
	      double deltaR_Tag_EM_gen = kinem::delta_R(emobjs[em]->Eta(), emobjs[em]->TrkPhiEM3(), 
							raw_mc_electrons[ielec]->Eta(), raw_mc_electrons[ielec]->Phi());
	      
	      // extrapolated position in CC
	      // and not tag electron
	      if(fabs(DetEtaEM3_gen) < 1. && pT_gen > 10. && deltaR_Tag_EM_gen > 2.) {
		
		// note here we care about the tag EM and generator level electron mass
		double Z_Px = raw_mc_electrons[ielec]->Px() + emobjs[em]->Px();
		double Z_Py = raw_mc_electrons[ielec]->Py() + emobjs[em]->Py();
		double Z_Pz = raw_mc_electrons[ielec]->Pz() + emobjs[em]->Pz();
		double Z_E = raw_mc_electrons[ielec]->E() + emobjs[em]->E();
		double mass = Z_E*Z_E - Z_Px*Z_Px - Z_Py*Z_Py - Z_Pz*Z_Pz;
		if(mass<0.) mass = 0.;
		mass = sqrt(mass);

		// require mass cut, similar to tag-probe method
		if(mass>75. && mass<105.) {  		      
		  _histos.Fill1D("ZCandTrkPhiMod_gen", phimod_gen);
		  
		  // now need to loop over the rest of EM clusters to find matched EM clusters
		  // not the tag electron		  
		  for(int iem=0; iem<emobjs.size(); iem++) {	  
		    
		    // EM phimodule
		    int phimodule_EM = (int)(emobjs[iem]->TrkPhiEM3()/(TMath::Pi()/16.));		  
		    		    
		    double deltaR_Probe_EM_trk = kinem::delta_R(emobjs[iem]->CalDetectorEta(), emobjs[iem]->TrkPhiEM3(), 
								DetEtaEM3_gen, DetPhiEM3_gen);
		    
		    //
		    // require the extrapolated track and the EM cluster within one module
		    // currently commented out
		    //if(deltaR_Probe_EM_trk<0.15 && (phimodule_gen == phimodule_EM)) {
		    
		    if(emobjs[iem]->emfrac()>0.9 && emobjs[iem]->iso()<0.15 && fabs(emobjs[iem]->CalDetectorEta())<1.) {
		      if(deltaR_Probe_EM_trk < 0.15) {
			double em_detphi = emobjs[iem]->TrkPhiEM3();
			double em_phimod = fmod(16.*em_detphi/TMath::Pi(), 1.0);
			double em_trk_phidiff = em_detphi - DetPhiEM3_gen;
                        // have to consider the case where the extrapolated particle and the EM cluster
                        // are in two different calorimeter modules
                        // should calculate the phi difference first and then divided by 2Pi/32
			//double em_trk_diff = em_phimod - phimod_gen;
			double em_trk_diff = em_trk_phidiff/(TMath::Pi()/16.);

                        double em_eta = emobjs[iem]->Eta();
		        double em_pT = emobjs[iem]->Pt();
	
  		        int eta_region = -1;
  		        if(fabs(em_eta)<0.25) eta_region = 0;
		        else if(fabs(em_eta)<0.5) eta_region = 1;
		        else if(fabs(em_eta)<0.75) eta_region = 2;
		        else eta_region = 3;
		        char eta_bin[10];
		        sprintf(eta_bin, "%d", eta_region);
		      
		        int pT_region = -1;
		        if(em_pT<35.) pT_region = 0;
		        else if(em_pT<40.) pT_region = 1;
		        else if(em_pT<45.) pT_region = 2;
		        else pT_region = 3;
		        char pT_bin[10];
		        sprintf(pT_bin, "%d", pT_region);

                        _histos.Fill1D(string("ZCandCalTrkDeltaPhi_gen_pTBin_")+pT_bin, em_trk_diff);
		        _histos.Fill1D(string("ZCandCalTrkDeltaPhi_gen_EtaBin_")+eta_bin, em_trk_diff);
		      
		        _histos.FillProfile("ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pro", phimod_gen, em_trk_diff);
		        _histos.FillProfile(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pro_pTBin_")+pT_bin, phimod_gen, em_trk_diff);
		        _histos.FillProfile(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pro_EtaBin_")+eta_bin, phimod_gen, em_trk_diff);
		      
		        _histos.Fill2D("ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen", phimod_gen, em_trk_diff);
		        _histos.Fill2D(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pTBin_")+pT_bin, phimod_gen, em_trk_diff);
		        _histos.Fill2D(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_EtaBin_")+eta_bin, phimod_gen, em_trk_diff);       

			// check for positive and negative charge and polarity
			if(charge == 1) {
			  _histos.Fill1D("ZCandEMTrkPhiDiff_gen_Positron", em_trk_phidiff);
			  _histos.Fill1D("ZCandEMTrkPhiModDiff_gen_Positron", em_trk_diff);
			  
			  if(polarity==1) {
			    _histos.Fill1D("ZCandEMTrkPhiDiff_gen_Positron_PosSolpol", em_trk_phidiff);
			    _histos.Fill1D("ZCandEMTrkPhiModDiff_gen_Positron_PosSolpol", em_trk_diff);
			  } else if(polarity==-1) {
			    _histos.Fill1D("ZCandEMTrkPhiDiff_gen_Positron_NegSolpol", em_trk_phidiff);
			    _histos.Fill1D("ZCandEMTrkPhiModDiff_gen_Positron_NegSolpol", em_trk_diff);
			  }
			} else if (charge == -1) {
			  _histos.Fill1D("ZCandEMTrkPhiDiff_gen_Electron", em_trk_phidiff);
			  _histos.Fill1D("ZCandEMTrkPhiModDiff_gen_Electron", em_trk_diff);
			  
			  if(polarity==1) {
			    _histos.Fill1D("ZCandEMTrkPhiDiff_gen_Electron_PosSolpol", em_trk_phidiff);
			    _histos.Fill1D("ZCandEMTrkPhiModDiff_gen_Electron_PosSolpol", em_trk_diff);
			  } else if(polarity==-1) {
			    _histos.Fill1D("ZCandEMTrkPhiDiff_gen_Electron_NegSolpol", em_trk_phidiff);
			    _histos.Fill1D("ZCandEMTrkPhiModDiff_gen_Electron_NegSolpol", em_trk_diff);
			  }
			}
			
			// check PhiCrack eff	     
			_histos.Fill1D("ZCandTrkPhiMod_gen_afterPhiFiducial", phimod_gen);
		      } // EM-track match
		    } // invariant mass cut
		  } 
		} // loop over reconstructed EMs
		
	      } // in CC
	    } // loop over each electron    	
	  } // add tag requirement
	} // loop over all EM clusters
      } // get raw electrons     
    } // for MC study
    
    //
    // method used on real data
    //
    // use one good EM as the tag and use the track as the probe
    // loop over all probe EM particles
    //    
    for(int em=0; em<emobjs.size(); em++) {
      if(emobjs[em]->Pt()>25. && emobjs[em]->emfrac()>0.9 && emobjs[em]->iso()<0.15 && emobjs[em]->HMx7()<12. && 
	 fabs(emobjs[em]->CalDetectorEta())<1. && emobjs[em]->has_good_spatial_track_match()) {       
	
	// loop over all isolated tracks
	for(int itrk=0; itrk<good_trks.size(); itrk++) {
	  double trk_phi = good_trks[itrk]->Phi();
	  double trk_eta = good_trks[itrk]->Eta();
	  double trk_pT = good_trks[itrk]->Pt();
	  int nsmt = good_trks[itrk]->nsmt();
	  int ncft = good_trks[itrk]->ncft();
	  double chindof = good_trks[itrk]->getChi2Ndf();

	  // make the good track is not the track assoicated with the tag electron
	  double deltaR_Tag_EM_trk = kinem::delta_R(emobjs[em]->Eta(), emobjs[em]->Phi(), trk_eta, trk_phi);
	  if(trk_pT>15.&& nsmt>0 && ncft>8 && chindof<3.3) _histos.Fill1D("ZCandEMTrkDeltaR", deltaR_Tag_EM_trk);

	  //if(deltaR_Tag_EM_trk>2. && trk_pT>10.) {
	  if(deltaR_Tag_EM_trk>2. && trk_pT>15. && nsmt>0 && ncft>8 && chindof<3.3) {
	    // now will extrapolate the track to EM3 layer
	    // have to use track pT for the extrapolation, no EM cluster pT available here
	    double trk_deteta = good_trks[itrk]->TrackDetEta(polarity, _MCStudy);
	    double trk_detphi = good_trks[itrk]->TrackDetPhi(polarity, _MCStudy);

	    double trk_phimod = fmod(16.*trk_detphi/TMath::Pi(), 1.0);
	    double trk_phimod2 = fmod(16.*trk_phi/TMath::Pi(), 1.0);
	   
            double trk_Px = good_trks[itrk]->Px();
            double trk_Py = good_trks[itrk]->Py();
            double trk_Pz = good_trks[itrk]->Pz();
            double trk_P = good_trks[itrk]->E();

            double Z_Px = trk_Px + emobjs[em]->Px();
            double Z_Py = trk_Py + emobjs[em]->Py();
            double Z_Pz = trk_Pz + emobjs[em]->Pz();
            double Z_E = trk_P + emobjs[em]->E();
            double mass = Z_E*Z_E - Z_Px*Z_Px - Z_Py*Z_Py - Z_Pz*Z_Pz;
            if(mass<0.) mass = 0.;
            mass = sqrt(mass);

	    if(fabs(trk_deteta)<1.) _histos.Fill1D("ZCandEMTrkMass_PhiMod", mass);

	    // extrapolated track in CC region
	    // and require EM-track mass to be certain region in order to reduce backgrounds  
	    if(fabs(trk_deteta)<1. && mass>75. && mass<105.) {
	      _histos.Fill1D("ZCandTrkPhiMod", trk_phimod);

	      // EM-track invariant mass for each track phimod bin
	      int trk_phimod_bin_num = (int)(trk_phimod/0.004);
	      if(trk_phimod_bin_num>49) trk_phimod_bin_num=49;
	      char trk_phimod_num_bin[10];
	      sprintf(trk_phimod_num_bin, "%d", trk_phimod_bin_num);
	      _histos.Fill1D(string("ZCandEMTrkMass_PhiMod_")+trk_phimod_num_bin, mass);

	      // track phimodule
	      int phimodule_trk = (int)(trk_detphi/(TMath::Pi()/16.));
	      
	      // now need to loop over the rest of EM clusters to find matched EM clusters
	      // not the tag electron
	      for(int iem=0; iem<emobjs.size(); iem++) {

		// EM phimodule
		int phimodule_EM = (int)(emobjs[iem]->CalDetectorPhi()/(TMath::Pi()/16.));

		if(emobjs[iem]->emfrac()>0.9 && emobjs[iem]->iso()<0.15 && fabs(emobjs[iem]->CalDetectorEta())<1.) {		 
		  double deltaR_Probe_EM_trk = kinem::delta_R(emobjs[iem]->CalDetectorEta(), 
							      emobjs[iem]->CalDetectorPhi(), trk_deteta, trk_detphi);		

		  int charge = (int)(good_trks[itrk]->charge());

		  // require the extrapolated track and the EM cluster within one module
		  // currently commented out
		  //if(deltaR_Probe_EM_trk<0.15 && (phimodule_trk == phimodule_EM)) {
		  if(deltaR_Probe_EM_trk < 0.15) {
		    double em_deteta = emobjs[iem]->CalDetectorEta();
		    double em_detphi = emobjs[iem]->CalDetectorPhi();
		    double em_eta = emobjs[iem]->Eta();
		    double em_pT = emobjs[iem]->Pt();
		    double em_phimod = fmod(16.*em_detphi/TMath::Pi(), 1.0);
		    double em_trk_phidiff = em_detphi - trk_detphi;
                    // have to consider the case where the extrapolated track and the EM cluster
                    // are in two different calorimeter modules
                    // should calculate the phi difference first and then divided by 2Pi/32
		    //double em_trk_diff = em_phimod - trk_phimod;
		    double em_trk_diff = em_trk_phidiff/(TMath::Pi()/16.);  

		    double trk_phidca = good_trks[itrk]->phid();
		    double trk_phimoddca = fmod(16.*trk_phidca/TMath::Pi(), 1.0);
		    //double em_trkdca_phidiff = em_detphi - trk_phidca;
		    double em_trkdca_phidiff = em_detphi - trk_detphi;
		    //double em_trkdca_diff = em_phimod - trk_phimoddca;
		    double em_trkdca_diff = em_trkdca_diff/(TMath::Pi()/16.);

		    // check for positive and negative charge and polarity
		    // EM phi and track phi at DCA
		    if(charge==1) {
		      _histos.Fill1D("ZCandEMTrkPhiDCADiff_Positron", em_trkdca_phidiff);
		      _histos.Fill1D("ZCandEMTrkPhiDCAModDiff_Positron", em_trkdca_diff);

		      if(polarity==1) {
			_histos.Fill1D("ZCandEMTrkPhiDCADiff_Positron_PosSolpol", em_trkdca_phidiff);
			_histos.Fill1D("ZCandEMTrkPhiDCAModDiff_Positron_PosSolpol", em_trkdca_diff);
		      } else if(polarity==-1) {
			_histos.Fill1D("ZCandEMTrkPhiDCADiff_Positron_NegSolpol", em_trkdca_phidiff);
			_histos.Fill1D("ZCandEMTrkPhiDCAModDiff_Positron_NegSolpol", em_trkdca_diff);
		      }
		    } else if(charge==-1) {
		      _histos.Fill1D("ZCandEMTrkPhiDCADiff_Electron", em_trkdca_phidiff);
		      _histos.Fill1D("ZCandEMTrkPhiDCAModDiff_Electron", em_trkdca_diff);

		      if(polarity==1) {
			_histos.Fill1D("ZCandEMTrkPhiDCADiff_Electron_PosSolpol", em_trkdca_phidiff);
			_histos.Fill1D("ZCandEMTrkPhiDCAModDiff_Electron_PosSolpol", em_trkdca_diff);
		      } else if(polarity==-1) {
			_histos.Fill1D("ZCandEMTrkPhiDCADiff_Electron_NegSolpol", em_trkdca_phidiff);
			_histos.Fill1D("ZCandEMTrkPhiDCAModDiff_Electron_NegSolpol", em_trkdca_diff);
		      }
		    }

		    // check for positive and negative charge and polarity
		    // EM phi and extrapolated track phi at EM3
		    // for positron and electron
		    if(charge == 1) {
		      _histos.Fill1D("ZCandEMTrkPhiDiff_Positron", em_trk_phidiff);
		      _histos.Fill1D("ZCandEMTrkPhiModDiff_Positron", em_trk_diff);

		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhi_Positron", trk_detphi, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVEMPhi_Positron", em_detphi, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCA_Positron", trk_phidca, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiMod_Positron", trk_phimod, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVEMPhiMod_Positron", em_phimod, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCAMod_Positron", trk_phimoddca, em_trk_diff);

		      if(polarity==1) {
			_histos.Fill1D("ZCandEMTrkPhiDiff_Positron_PosSolpol", em_trk_phidiff);
			_histos.Fill1D("ZCandEMTrkPhiModDiff_Positron_PosSolpol", em_trk_diff);

			_histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhi_Positron_PosSolpol", trk_detphi, em_trk_diff);
			_histos.FillProfile("ZCandEMTrkPhiDiffVEMPhi_Positron_PosSolpol", em_detphi, em_trk_diff);
			_histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCA_Positron_PosSolpol", trk_phidca, em_trk_diff);
			_histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiMod_Positron_PosSolpol", trk_phimod, em_trk_diff);
			_histos.FillProfile("ZCandEMTrkPhiDiffVEMPhiMod_Positron_PosSolpol", em_phimod, em_trk_diff);
			_histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCAMod_Positron_PosSolpol", trk_phimoddca, em_trk_diff);
		      } else if(polarity==-1) {
			_histos.Fill1D("ZCandEMTrkPhiDiff_Positron_NegSolpol", em_trk_phidiff);
			_histos.Fill1D("ZCandEMTrkPhiModDiff_Positron_NegSolpol", em_trk_diff);
			
			_histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhi_Positron_NegSolpol", trk_detphi, em_trk_diff);
			_histos.FillProfile("ZCandEMTrkPhiDiffVEMPhi_Positron_NegSolpol", em_detphi, em_trk_diff);
			_histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCA_Positron_NegSolpol", trk_phidca, em_trk_diff);
			_histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiMod_Positron_NegSolpol", trk_phimod, em_trk_diff);
			_histos.FillProfile("ZCandEMTrkPhiDiffVEMPhiMod_Positron_NegSolpol", em_phimod, em_trk_diff);
			_histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCAMod_Positron_NegSolpol", trk_phimoddca, em_trk_diff);
		      }
		    } else if (charge == -1) {
		      _histos.Fill1D("ZCandEMTrkPhiDiff_Electron", em_trk_phidiff);
		      _histos.Fill1D("ZCandEMTrkPhiModDiff_Electron", em_trk_diff);

		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhi_Electron", trk_detphi, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVEMPhi_Electron", em_detphi, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCA_Electron", trk_phidca, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiMod_Electron", trk_phimod, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVEMPhiMod_Electron", em_phimod, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCAMod_Electron", trk_phimoddca, em_trk_diff);

		      if(polarity==1) {
			_histos.Fill1D("ZCandEMTrkPhiDiff_Electron_PosSolpol", em_trk_phidiff);
			_histos.Fill1D("ZCandEMTrkPhiModDiff_Electron_PosSolpol", em_trk_diff);

		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhi_Electron_PosSolpol", trk_detphi, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVEMPhi_Electron_PosSolpol", em_detphi, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCA_Electron_PosSolpol", trk_phidca, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiMod_Electron_PosSolpol", trk_phimod, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVEMPhiMod_Electron_PosSolpol", em_phimod, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCAMod_Electron_PosSolpol", trk_phimoddca, em_trk_diff);
		      } else if(polarity==-1) {
			_histos.Fill1D("ZCandEMTrkPhiDiff_Electron_NegSolpol", em_trk_phidiff);
			_histos.Fill1D("ZCandEMTrkPhiModDiff_Electron_NegSolpol", em_trk_diff);

		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhi_Electron_NegSolpol", trk_detphi, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVEMPhi_Electron_NegSolpol", em_detphi, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCA_Electron_NegSolpol", trk_phidca, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiMod_Electron_NegSolpol", trk_phimod, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVEMPhiMod_Electron_NegSolpol", em_phimod, em_trk_diff);
		      _histos.FillProfile("ZCandEMTrkPhiDiffVTrkPhiDCAMod_Electron_NegSolpol", trk_phimoddca, em_trk_diff);
		      }
		    }
		    
		    _histos.Fill1D("ZCandElecPhiMod", em_phimod);
		    _histos.Fill1D("ZCandCalTrkDeltaPhi", em_trk_diff);
		    _histos.Fill1D("ZCandTrkPhiMod_afterPhiFiducial", trk_phimod);
		    
		    int eta_region = -1;
		    if(fabs(em_eta)<0.25) eta_region = 0;
		    else if(fabs(em_eta)<0.5) eta_region = 1;
		    else if(fabs(em_eta)<0.75) eta_region = 2;
		    else eta_region = 3;
		    char eta_bin[10];
		    sprintf(eta_bin, "%d", eta_region);
		      
		    int pT_region = -1;
		    if(em_pT<35.) pT_region = 0;
		    else if(em_pT<40.) pT_region = 1;
		    else if(em_pT<45.) pT_region = 2;
		    else pT_region = 3;
		    char pT_bin[10];
		    sprintf(pT_bin, "%d", pT_region);

		    _histos.FillProfile("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro", trk_phimod, em_trk_diff);
		    _histos.FillProfile(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin_")+pT_bin, trk_phimod, em_trk_diff);
		    _histos.FillProfile(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin_")+eta_bin, trk_phimod, em_trk_diff);

		    _histos.Fill2D("ZCandCalTrkDeltaPhi_V_ElecPhiMod", trk_phimod, em_trk_diff);
		    _histos.Fill2D(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin_")+pT_bin, trk_phimod, em_trk_diff);
		    _histos.Fill2D(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin_")+eta_bin, trk_phimod, em_trk_diff);     
  
                    // pass pT cut
                    if(emobjs[iem]->Pt()>25.) {
		      _histos.FillProfile("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_PassPt", trk_phimod, em_trk_diff);
		      _histos.FillProfile(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin_PassPt_")+pT_bin, trk_phimod, em_trk_diff);
		      _histos.FillProfile(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin_PassPt_")+eta_bin, trk_phimod, em_trk_diff);
		      
		      _histos.Fill2D("ZCandCalTrkDeltaPhi_V_ElecPhiMod_PassPt", trk_phimod, em_trk_diff);
		      _histos.Fill2D(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin_PassPt_")+pT_bin, trk_phimod, em_trk_diff);
		      _histos.Fill2D(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin_PassPt_")+eta_bin, trk_phimod, em_trk_diff);       
                    }

                    // pass spatial track match 
                    if(emobjs[iem]->has_good_spatial_track_match()) {
		      _histos.FillProfile("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_PassTrkMatch", trk_phimod, em_trk_diff);
		      _histos.FillProfile(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin_PassTrkMatch_")+pT_bin, trk_phimod, em_trk_diff);
		      _histos.FillProfile(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin_PassTrkMatch_")+eta_bin, trk_phimod, em_trk_diff);
		      
		      _histos.Fill2D("ZCandCalTrkDeltaPhi_V_ElecPhiMod_PassTrkMatch", trk_phimod, em_trk_diff);
		      _histos.Fill2D(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin_PassTrkMatch_")+pT_bin, trk_phimod, em_trk_diff);
		      _histos.Fill2D(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin_PassTrkMatch_")+eta_bin, trk_phimod, em_trk_diff);       
                    }

		    // tight EM cluster requirement
		    if(emobjs[iem]->Pt()>25. && emobjs[iem]->has_good_spatial_track_match()) {		    		      
		      _histos.Fill1D("ZCandElecPhiMod_PtCut", em_phimod);
		      _histos.Fill1D("ZCandCalTrkDeltaPhi_PtCut", em_trk_diff);
		      _histos.Fill1D("ZCandTrkPhiMod_afterPhiFiducial_PtCut", trk_phimod);
		      
		      
		      _histos.Fill1D(string("ZCandCalTrkDeltaPhi_pTBin_")+pT_bin, em_trk_diff);
		      _histos.Fill1D(string("ZCandCalTrkDeltaPhi_EtaBin_")+eta_bin, em_trk_diff);
		      
		      _histos.FillProfile("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_PassPtTrkMatch", trk_phimod, em_trk_diff);
		      _histos.FillProfile(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin_PassPtTrkMatch_")+pT_bin, trk_phimod, em_trk_diff);
		      _histos.FillProfile(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin_PassPtTrkMatch_")+eta_bin, trk_phimod, em_trk_diff);
		      
		      _histos.Fill2D("ZCandCalTrkDeltaPhi_V_ElecPhiMod_PassPtTrkMatch", trk_phimod, em_trk_diff);
		      _histos.Fill2D(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin_PassPtTrkMatch_")+pT_bin, trk_phimod, em_trk_diff);
		      _histos.Fill2D(string("ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin_PassPtTrkMatch_")+eta_bin, trk_phimod, em_trk_diff);       
		    }
		  } // track and probe electron close to each other
		}
	      } // loop over the rest of EM clusters to find matched EM clusters
	    } // extrapolated track in CC region
	  } // track and EM are far away from each other
	} // loop over the tracks
      } // good tag electron
    } // loop over each em object
  } // get good isolated tracks
}

// study phi crack efficiency
// need to run this on 2EMHighpT sample, assume all tracks are coming from Z->ee events
void ZAnalysis::PhiCrackEffStudyUsingTracks(cafe::Event& event, vector<CAFEMObj*> emobjs) {
  
  vector<CAFTrack *> good_trks;
  if(event.get("Good Tracks", good_trks)) {
    int polarity = (int)(event.getGlobal()->solpol());
    polarity = 2*polarity-1;

    if(good_trks.size()>=2) {
      TLorentzVector trk1_vect(good_trks[0]->Px(), good_trks[0]->Py(), good_trks[0]->Pz(), good_trks[0]->E());
      TLorentzVector trk2_vect(good_trks[1]->Px(), good_trks[1]->Py(), good_trks[1]->Pz(), good_trks[1]->E());
      double Mass_trks = (trk1_vect+trk2_vect).M();
      double deltaPhi_trks = trk1_vect.DeltaPhi(trk2_vect);

      // here we assume all tracks are from Z->ee events
      // Z->mumu events will also be included, so we should run this on 2EMhighpT sample
      // add mass and delta Phi requirements for two tracks
      if(Mass_trks>75. && Mass_trks<105. && fabs(deltaPhi_trks)>2.8) {
	
	for(int itrk=0; itrk<good_trks.size(); itrk++) {
	  double trk_phi = good_trks[itrk]->Phi();
	  double trk_eta = good_trks[itrk]->Eta();
	  double trk_pT = good_trks[itrk]->Pt();
	  
	  // assume isolated track with pT>15 GeV only comes from Z decays
	  if(trk_pT>15.) {
	    // now will extrapolate the track to EM3 layer
	    // have to use track pT for the extrapolation, no EM cluster pT available here
	    double trk_deteta = good_trks[itrk]->TrackDetEta(polarity);
	    double trk_detphi = good_trks[itrk]->TrackDetPhi(polarity);

	    double trk_phimod = fmod(16.*trk_detphi/3.1415926, 1.0);
	    double trk_phimod2 = fmod(16.*trk_phi/3.1415926, 1.0);
	    
	    if(fabs(trk_deteta)<1.) {
	      _histos.Fill1D("ZCandTrkPhiMod2", trk_phimod);
	      
	      // loop over all EM clusters to find matched EM clusters
	      for(int iem=0; iem<emobjs.size(); iem++) {
		if(emobjs[iem]->emfrac()>0.9 && emobjs[iem]->iso()<0.2 && fabs(emobjs[iem]->CalDetectorEta())<1.) {		 
		  
		  double deltaR_Probe_EM_trk = kinem::delta_R(emobjs[iem]->Eta(), emobjs[iem]->Phi(), trk_eta, trk_phi);		
		  if(deltaR_Probe_EM_trk<0.2) {
		    double em_deteta = emobjs[iem]->CalDetectorEta();
		    double em_detphi = emobjs[iem]->CalDetectorPhi();
		    double em_eta = emobjs[iem]->Eta();
		    double em_pT = emobjs[iem]->Pt();
		    double em_phimod = fmod(16.*em_detphi/3.1415926, 1.0);
		    double em_trk_diff = em_phimod - trk_phimod;
		    
		    _histos.Fill1D("ZCandElecPhiMod2", em_phimod);
		    _histos.Fill1D("ZCandCalTrkDeltaPhi2", em_trk_diff);
		    _histos.Fill1D("ZCandTrkPhiMod2_afterPhiFiducial", trk_phimod);
		    
		    _histos.FillProfile("ZCandCalTrkDeltaPhi_V_ElecPhiMod2_pro", trk_phimod, em_trk_diff);
		    _histos.Fill2D("ZCandCalTrkDeltaPhi_V_ElecPhiMod2", trk_phimod, em_trk_diff);
		    
		    // tight EM cluster requirement
		    if(emobjs[iem]->Pt()>25. && emobjs[iem]->has_good_spatial_track_match()) {		    		      
		      _histos.Fill1D("ZCandElecPhiMod2_PtCut", em_phimod);
		      _histos.Fill1D("ZCandCalTrkDeltaPhi2_PtCut", em_trk_diff);
		      _histos.Fill1D("ZCandTrkPhiMod2_afterPhiFiducial_PtCut", trk_phimod);
		    } // tight EM requirement
		  } // pass emfrac and iso
		} // track and probe electron close to each other
	      } // loop over the rest of EM clusters to find matched EM clusters
	    } // extrapolated track in CC region
	  } //track pT>15 GeV 
	} // loop over all tracks
      } // mass and deltaPhi requirements for two tracks
    } // at least two isolated tracks
  } // get good isolated tracks
}

// process 
bool ZAnalysis::processEvent(cafe::Event& event) {

 
  ////---- to skip events above certain PYTHIA-level Z mass --
  ////---- comment out the piece below
  //TMBMCpart* _mc_Zboson=NULL;  
  //int intermediate_boson_ID=-55555;
  //float intermediate_boson_mass=10000.;
  //if(_MCStudy && event.get("WZ boson object", _mc_Zboson)) {
  //   intermediate_boson_ID=_mc_Zboson->pdgid();
  //   intermediate_boson_mass=_mc_Zboson->M();
  //   //cout<<"BOSONID"<<intermediate_boson_ID<<endl;
  //   //cout<<"BOSONMASS "<<intermediate_boson_mass<<endl;
  //}
  //if (intermediate_boson_ID==23 && intermediate_boson_mass>70.) return false;


  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");

  vector<CAFEMObj*> emobjs;
  vector<CAFEMObj*> probe_emobjs;

  CAFMet met;
  CAFMet rawmet;
  double instlumi;
  int runNo, evtNo, tickNo;

  float vtx_x, vtx_y, vtx_z;
  int NPV = -1;
  int triglist_flag = -1;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;

  HighestPhotonPt=0;
  SecondHighestPhotonPt=0;

  std::vector<TMBMCpart *> unmerged_mc_photons;
  isPhot=false;

  if(_MCStudy) {
    if( event.get("unmerged photons", unmerged_mc_photons) ){
      if(unmerged_mc_photons.size()>0) isPhot=true;;
      for (vector<TMBMCpart*>::iterator it2 = unmerged_mc_photons.begin(); it2!= unmerged_mc_photons.end(); ++it2) {
        double mpT = (*it2)->Pt();
        if(mpT>HighestPhotonPt){
          SecondHighestPhotonPt = HighestPhotonPt;
          HighestPhotonPt=mpT;
        }
        else if(mpT>SecondHighestPhotonPt){
          SecondHighestPhotonPt = mpT;
        }
      }
    }
  }

  // study Phi crack efficiency
  if(_PhiCrackEffStudy) {
    if (event.get("Probe EMObjs", probe_emobjs)) {
      PhiCrackEffStudy(event, probe_emobjs);
      PhiCrackEffStudyUsingTracks(event, probe_emobjs);
    }
  }

  int solpol = -999;
  if (event.get("Good EMObjs", emobjs) && event.get("EMCorr Met", met) && 
      event.get("Raw Met", rawmet) &&
      event.get("L1CalTowers", l1cal_vec)  && event.get("L1Cal2bTowers", l1cal2b_vec) && 
      event.get("L2GblEMs", l2cal_vec) && 
      event.get("L3Eles", l3cal_vec) && event.get("triglist flag", triglist_flag) &&
      event.get("run number", runNo) && event.get("event number", evtNo) &&
      event.get("tick number", tickNo) &&
      event.get("InstLumi", instlumi) && event.get("Best primary vertexX", vtx_x) && 
      event.get("Best primary vertexY", vtx_y) && event.get("Best primary vertexZ", vtx_z) &&
      event.get("Number of primary verticies" , NPV) &&
      event.get("solenoid polarity", solpol)) {


    if (_MCStudy && _doZBevent)
      if (!event.get("ZBevent HKset", _ZBSET)) return false;

     // fill generator-level Z pT distribution
     TMBMCpart *ZBoson=NULL;
     if(_MCStudy) {
       if(event.get("WZ boson object", ZBoson)) {
         _histos.Fill1D("ZCandpT_gen", ZBoson->Pt());
       } // get Z boson
     }

     // convert polarity from 0/1 to -1/1
     int polarity = 2*solpol - 1;

     // Selection to study efficiencies. Only ask for probe objects
     // This is basically a simpler version of the one below
     if (event.get("Probe EMObjs", probe_emobjs)) {
      if(probe_emobjs.size() >= 2 && _trkMatchEffStudy) {

       int tagnum = emobjs.size();
       bool pass_trigger[tagnum];
       if(_MCStudy || _DropTriggerObjectMatchRequirement) {
	 for (int iem=0; iem<tagnum; iem++)
	   pass_trigger[iem] = true;
       }
       else {
	 for (int iem=0; iem<tagnum; iem++)
	   pass_trigger[iem] = emobjs[iem]->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec);
       }
       float vtx[3] = {vtx_x, vtx_y, vtx_z};
       // Tag and probe method
       trkMatchEfficiencyStudies(event, emobjs, probe_emobjs, rawmet, vtx, pass_trigger);
       
       if(_MCStudy)
	 // Truth method
	 trueTrkMatchEfficiencyStudies(event, probe_emobjs, rawmet, vtx);

      }
     }

     // at least two EM Objects
     if(emobjs.size() >= 2) {
       // write out possible Z candidate runNo, evtNo to a text file
       if(!_MCStudy) (*_zee_out_txt) << runNo << " " << evtNo << endl;

       // need to access all tracks to load track branch to allow partial read
       // otherwise I will get totally different result
       //get tracks from the event
       cafe::Collection<TMBTrack> trks = event.getTracks();

       // at least one electron passes trigger requirement
       // for GEANT MC, we do not need to check trigger efficiency
       bool pass_trigger = false;
       if(_MCStudy || _DropTriggerObjectMatchRequirement) pass_trigger = true;
       else pass_trigger = emobjs[0]->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec) ||
                           emobjs[1]->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec); 	
       if(!pass_trigger) _events_fail_trigger_requirements ++; 	 
        // construct Z candidates
       float vtx[3] = {vtx_x, vtx_y, vtx_z};
       CAFZCand zcand;
       if(_dorawCellsRecoil) {
         if (_useConsistentMET) {
           zcand = CAFZCand(emobjs[0], emobjs[1], &rawmet, vtx, true);
         } else {
           zcand = CAFZCand(emobjs[0], emobjs[1], &met, vtx);
         }
       } else {
         zcand = CAFZCand(emobjs[0], emobjs[1], &met);
       }

       if (_useConsistentMET) {
         TVector2 consistMET=zcand.GetConsistentMET();
         double dummySET=met.scalarEt();
         met.SetMet(consistMET.X(),consistMET.Y(),consistMET.Mod(),dummySET);
       }

       if(_debugLevel >= 5)  zcand.print();

       // MOVED FROM LATER IN THE CODE /////////////////////////////////////////////////////////////
       // calculate scalarEt and remove contribution due to two electrons
       double zScalarEt = 0;
       double ScalarEt_Evt = 0;
       if (!_dorawCellsRecoil) {
         ScalarEt_Evt = met.scalarEt();
         double ScalarEt_EMObjs = emobjs[0]->EMScalarEt()*emobjs[0]->E()/emobjs[0]->uncorrE() +
                                  emobjs[1]->EMScalarEt()*emobjs[1]->E()/emobjs[1]->uncorrE();
         zScalarEt = ScalarEt_Evt - ScalarEt_EMObjs;
       } else {
         ScalarEt_Evt = rawmet.scalarEt();
         float cntrib1=0;
         float cntrib2=0;
         emobjs[0]->getRawElecVectorFromCells(vtx,&cntrib1);
         emobjs[1]->getRawElecVectorFromCells(vtx,&cntrib2);
         double ScalarEt_EMObjs = cntrib1 + cntrib2;
         zScalarEt = ScalarEt_Evt - ScalarEt_EMObjs;
       }
       //
       // for different Z type, 0 for CCCC, 1 for CCEC, 2 for ECEC
       int type = zcand.Type(_DetEtaCC, _DetEtaEC1, _DetEtaEC2);
       char sn[10];
       sprintf(sn, "%d", type);
       std::vector<TMBMCpart *> raw_emobjs_gen , real_raw_emobjs_gen;
       if(_MCStudy) {
         if(event.get("em mc objects", raw_emobjs_gen)) {
         }
         if(event.get("raw mc electrons", real_raw_emobjs_gen)) {
         }
       }
	
       // write out information for some efficiency studies
       if(_makeEfficStudyFile) {
         if(type < 2) makeEfficStudyFile(event, emobjs, raw_emobjs_gen, instlumi, type, zScalarEt);
       }

       // Num of matched tracks for Z candidate     
       int NumGoodSpatialTrks = zcand.NumGoodSpatialTracks(_require_smt);
       char num_spatial_trks[10];
       sprintf(num_spatial_trks, "%d", NumGoodSpatialTrks);		  

       // disable reco uT cut when making recoil file for Matt's method
       // or making recoil file for Mikolaj's method 
       // or doing Mikolaj's recoil ET-flow studies
       if(_makeRecoilFile || _dumpRecoilInfo || _do_RecoilEtFlow_studies ) {
         _ZUtCut = 1000000.;
         _ZUtCut_lower = 0.;
         _ZPtCut = 1000000.;
         _ZPtCut_lower = 0.;
       }
	
       double mass = zcand.Mass();   // mass calculated using cal+tracker information
       double recoilPt = zcand.MagRecoil();
 
       // also fill a version of the mass plot without any cut on mass - useful for bkg fitting
       if(recoilPt < _ZUtCut && recoilPt >= _ZUtCut_lower &&
          NumGoodSpatialTrks >= _NumZSpatialTrk &&
          pass_trigger && type>=0 && (instlumi > _InstLumi_lowcut) && (instlumi < _InstLumi_highcut)) {
         // generator-level Z boson pT after selection
         // measure acc*eff dependence on Z boson pT
         if(_MCStudy && ZBoson) {
           _histos.Fill1D("ZCandpT_gen_selected", ZBoson->Pt());
           if(type==0) _histos.Fill1D("ZCandpT_gen_selected_CCCC", ZBoson->Pt());
           if(type==1) _histos.Fill1D("ZCandpT_gen_selected_CCEC", ZBoson->Pt());
           if(type==2) _histos.Fill1D("ZCandpT_gen_selected_ECEC", ZBoson->Pt());
         }

         // write out root tuple for some special studies
         if(_createRootTree) {
           clear_ems();
           get_ems(emobjs, polarity);
           _tree->Fill();
         }

         _histos.Fill1D("ZCandMassWide", mass, 1.);
         if(type==0) {
           _histos.Fill1D("ZCandMassWide_CCCC_Trks", mass, 1.);
         } else if(type==1) {
           _histos.Fill1D("ZCandMassWide_CCEC_Trks", mass, 1.);
         } else if(type==2) {
           _histos.Fill1D("ZCandMassWide_ECEC_Trks", mass, 1.);  
         }
       }
       // make Z boson Ut cut and at least one electron has spatial track match with at least one SMT hit and pT>10 GeV
	
       Float_t EtaImBalanceForCut = zcand.pee_eta() +  zcand.recoil_eta();

       Int_t cut = (recoilPt < _ZUtCut && recoilPt >= _ZUtCut_lower &&
                    NumGoodSpatialTrks >= _NumZSpatialTrk && 
                    pass_trigger && type>=0 && 
                    mass>_ZMassCut1 && mass<_ZMassCut2 &&
                    zcand.EM(0)->Pt()>_ElecPtCut1_lo &&  zcand.EM(1)->Pt()>_ElecPtCut2_lo &&
                    zcand.EM(0)->Pt()<_ElecPtCut1_hi &&  zcand.EM(1)->Pt()<_ElecPtCut2_hi &&
                    zScalarEt>_ZScalarEtCut_lower && zScalarEt<_ZScalarEtCut);

       if (_fillztree){
         if (_MCStudy){
           tree3_passtrig[0] = 1;
           tree3_passtrig[1] = 1;
           tree3_passtrig5[0] = 1;
           tree3_passtrig5[1] = 1;
           tree3_passtrig6[0] = 1;
           tree3_passtrig6[1] = 1;
           tree3_passtrig7[0] = 1;
           tree3_passtrig7[1] = 1;

	   TMBMCpart* WZ;
	   event.get("WZ boson object", WZ);
	   tree3_vtxtruez = WZ->getDMCvtx()->z();

         }
         else{
           for (int kelec=0; kelec<2; kelec++){
             tree3_passtrig[kelec] = zcand.EM(kelec)->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec);
             tree3_passtrig5[kelec] = zcand.EM(kelec)->PassTrigCMB(5, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec);
             tree3_passtrig6[kelec] = zcand.EM(kelec)->PassTrigCMB(6, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec);
             tree3_passtrig7[kelec] = zcand.EM(kelec)->PassTrigCMB(7, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec);
             tree3_passl1[kelec] = zcand.EM(kelec)->PassL1_CSWEM_withEt(0.4, 19., l1cal2b_vec, tree3_l1Et[kelec]);
             tree3_passl2em22[kelec] = zcand.EM(kelec)->PassL2_EM_withEt(0.4, 22., l2cal_vec, tree3_l2em22Et[kelec]);
             tree3_passl2em25[kelec] = zcand.EM(kelec)->PassL2_EM_withEt(0.4, 25., l2cal_vec, tree3_l2em25Et[kelec]);
             tree3_passl2iso[kelec] = zcand.EM(kelec)->PassL2_EM_Iso_withEt(0.4, 19., 0.2, l2cal_vec, tree3_l2isoEt[kelec]);
             tree3_passl2lh[kelec] = zcand.EM(kelec)->PassL2_EM_lhood_withEt(0.4, 19., 0.4, l2cal_vec, tree3_l2lhEt[kelec]);
             tree3_passl3sht25[kelec] = zcand.EM(kelec)->PassL3_ELE_NLV_SHT_withEt(0.4, 25., l3cal_vec, tree3_l3sht25Et[kelec]);
             tree3_passl3sht27[kelec] = zcand.EM(kelec)->PassL3_ELE_NLV_SHT_withEt(0.4, 27., l3cal_vec, tree3_l3sht27Et[kelec]);

	   }
	   tree3_vtxtruez =-999;
         }

         filltree3(type, vtx_z, zcand, met, zScalarEt, instlumi, triglist_flag, cut, runNo, evtNo);
       }

       if(recoilPt < _ZUtCut && recoilPt >= _ZUtCut_lower &&
          zcand.Pt() < _ZPtCut && zcand.Pt() >= _ZPtCut_lower &&  
	  zcand.Phi() < _ZPhiCut && zcand.Phi() >= _ZPhiCut_lower &&
          NumGoodSpatialTrks >= _NumZSpatialTrk && 
          pass_trigger && type>=0 && 
          mass>_ZMassCut1 && mass<_ZMassCut2 &&
          zcand.EM(0)->Pt()>_ElecPtCut1_lo &&  zcand.EM(1)->Pt()>_ElecPtCut2_lo &&
          zcand.EM(0)->Pt()<_ElecPtCut1_hi &&  zcand.EM(1)->Pt()<_ElecPtCut2_hi &&
          zScalarEt>_ZScalarEtCut_lower && zScalarEt<_ZScalarEtCut){
         // Z candidate
         if (_etaImbalance_perbincuts) {
           Int_t pTeeEtaCutBin = wz_utils::pTee_Eta_Bin(zcand.Pt());
           if (pTeeEtaCutBin < 0){
             if (!_InvertetaImbalance_perbincuts){
               return false;
             }
           }

           if (!_InvertetaImbalance_perbincuts){
             if (!((EtaImBalanceForCut < _EtaImbalanceCutHigh.at(pTeeEtaCutBin) ) && (EtaImBalanceForCut >  _EtaImbalanceCutLow.at(pTeeEtaCutBin) ))){
               return false;
             }
           }
           else if (pTeeEtaCutBin>-1){
             if ((EtaImBalanceForCut < _EtaImbalanceCutHigh.at(pTeeEtaCutBin) ) && (EtaImBalanceForCut >  _EtaImbalanceCutLow.at(pTeeEtaCutBin) )){
               return false;
             }
           }
         }
	
         double mass_cal = zcand.Mass_Cal(); // mass calculated using cal information only
         double zPt = zcand.Pt();
         double zAt = zcand.At();
         double zAl = zcand.Al();
         double zPx = zcand.Px();
         double zPy = zcand.Py();
	 double zPz = zcand.Pz();
         double zEta = zcand.Eta();
         double zPhi = zcand.Phi();
         double zMet = met.met();
         double zMetx = met.metx();
         double zMety = met.mety();
         double zMetPhi = met.metphi();
         double recoilPhi = zcand.GetRecoil().Phi();
         double recoilPx = zcand.GetRecoil().Px();
         double recoilPy = zcand.GetRecoil().Py();
         TVector2 recoil_vect(recoilPx, recoilPy);
         TVector2 met_vect(zMetx, zMety);
         TVector2 z_vect(zPx, zPy);
         double phi_Z_Recoil = fabs(z_vect.DeltaPhi(recoil_vect));
         double phi_Z_met = fabs(z_vect.DeltaPhi(met_vect));

         if (type==0 && _createRootTree2){
           if (_MCStudy){
             filltree2(zcand, recoilPt, zScalarEt, instlumi,event.getGlobal(_global_vars)->runno(), event.getGlobal(_global_vars)->evtno(),runNo,evtNo);
           }
           else{
             filltree2(zcand, recoilPt, zScalarEt, instlumi,0,0,runNo, evtNo);
           }
         }

         // now we can do some systematic studies by varying the cuts
         if(_consistency_check) {
           const CAFEMObj *emobj1 = zcand.EM(0);
           double ZElecPt1 = emobj1->Pt();
           double ZElecEta1 = emobj1->Eta();
	   double ZElecPhi1 = emobj1->Phi();
           double ZElecDetEta1 = emobj1->CalDetectorEta();
           double ZElecPhiMod1 = fmod(16.*emobj1->TrkPhiEM3()/TMath::Pi(), 1.0);
           TVector2 em1_vect(emobj1->Px(), emobj1->Py());
           double UPara1 = recoil_vect * (em1_vect.Unit());
           const CAFEMObj *emobj2 = zcand.EM(1);
           double ZElecPt2 = emobj2->Pt();
           double ZElecEta2 = emobj2->Eta();
	   double ZElecPhi2 = emobj2->Phi();
           double ZElecDetEta2 = emobj2->CalDetectorEta();
           double ZElecPhiMod2 = fmod(16.*emobj2->TrkPhiEM3()/TMath::Pi(), 1.0);
           TVector2 em2_vect(emobj2->Px(), emobj2->Py());
           double UPara2 = recoil_vect * (em2_vect.Unit());
           double ZPTee = zcand.Pt();

           bool passCut_under_study_elec1 =  wz_utils::passCut(_cut_under_study, _invert_cut,
							                                   runNo, _runNo_lowcut, _runNo_highcut,
							       tickNo, _tickNo_lowcut, _tickNo_highcut,
                                                               instlumi, _InstLumi_lowcut, _InstLumi_highcut,
                                                               zScalarEt, _ScalarEt_lowcut, _ScalarEt_highcut,
                                                               ZElecEta1, _ElecEta_cut,
                                                               ZElecDetEta1, _ElecDetEta_lowcut, _ElecDetEta_highcut,
                                                               ZElecPhiMod1, _ElecPhiMod_cut,
                                                               UPara1, _UPara_lowcut, _UPara_highcut,
                                                               ZElecPt1, _ElecPt_lowcut, _ElecPt_highcut,
							       ZElecPhi1, _ElecPhi_lowcut, _ElecPhi_highcut,
							       recoilPhi, _RecoilPhi_lowcut, _RecoilPhi_highcut,
                                   ZPTee, _ZPTee_lowcut, _ZPTee_highcut);

           bool passCut_under_study_elec2 =  wz_utils::passCut(_cut_under_study, _invert_cut,
							                                   runNo, _runNo_lowcut, _runNo_highcut,
							       tickNo, _tickNo_lowcut, _tickNo_highcut,
                                                               instlumi, _InstLumi_lowcut, _InstLumi_highcut,
                                                               zScalarEt, _ScalarEt_lowcut, _ScalarEt_highcut,
                                                               ZElecEta2, _ElecEta_cut,
                                                               ZElecDetEta2, _ElecDetEta_lowcut, _ElecDetEta_highcut,
                                                               ZElecPhiMod2, _ElecPhiMod_cut,
                                                               UPara2, _UPara_lowcut, _UPara_highcut,
                                                               ZElecPt2, _ElecPt_lowcut, _ElecPt_highcut,
							       ZElecPhi2, _ElecPhi_lowcut, _ElecPhi_highcut,
							       recoilPhi, _RecoilPhi_lowcut, _RecoilPhi_highcut,
                                   ZPTee, _ZPTee_lowcut, _ZPTee_highcut);
           // for runNo, instlumi, zScalarEt, will check the value twice, it does not matter 
           // since they are global variables for one event
           // require at least one electron passes the cut
           if(!(passCut_under_study_elec1 || passCut_under_study_elec2)) return false;

	   if (_cut_under_study.Contains("DetEtaCateg_cut")) {
	     if (zcand.DetEtaCategory(_DetEtaCC) != _DetEtaCateg_cut) return false;
	   }

         }
	
         double mc_zPt(0), mc_zMass(0), mc_zRapidity(0), mc_zphi(0);
         double mc_pte1(0) , mc_pte2(0) , mc_cosdphiee(0) , mc_detaee(0) , mc_ptee(0);
         double mc_Ee1(0) , mc_Ee2(0);
         double mc_raw_pte1(0) , mc_raw_pte2(0);
         double mc_raw_Ee1(0) , mc_raw_Ee2(0);
         TMBMCpart *_Z=NULL;
         if(_MCStudy && event.get("WZ boson object", _Z) && real_raw_emobjs_gen.size() >= 2 ) {
           mc_zPt = _Z->Pt();
           mc_zMass = _Z->M();
           mc_zRapidity = _Z->Rapidity();
           mc_zphi = _Z->Phi();
           mc_pte1 = real_raw_emobjs_gen[0]->Pt();
           mc_pte2 = real_raw_emobjs_gen[1]->Pt();
           mc_raw_pte1 = real_raw_emobjs_gen[0]->Pt();
           mc_raw_pte2 = real_raw_emobjs_gen[1]->Pt();
           mc_Ee1 = real_raw_emobjs_gen[0]->E();
           mc_Ee2 = real_raw_emobjs_gen[1]->E();
           mc_raw_Ee1 = real_raw_emobjs_gen[0]->E();
           mc_raw_Ee2 = real_raw_emobjs_gen[1]->E();
           if( fabs( TVector2::Phi_mpi_pi( zcand.EM(0)->Phi() - real_raw_emobjs_gen[0]->Phi() ) ) > fabs( TVector2::Phi_mpi_pi( zcand.EM(0)->Phi() - real_raw_emobjs_gen[1]->Phi() ) ) )
           {
             mc_pte1 = real_raw_emobjs_gen[1]->Pt();
             mc_pte2 = real_raw_emobjs_gen[0]->Pt();
             mc_Ee1 = real_raw_emobjs_gen[1]->E();
             mc_Ee2 = real_raw_emobjs_gen[0]->E();
           }
           mc_ptee = ( *real_raw_emobjs_gen[0] + *real_raw_emobjs_gen[1] ).Pt();
           mc_cosdphiee = cos( real_raw_emobjs_gen[0]->DeltaPhi( *real_raw_emobjs_gen[1] ) );
           mc_detaee = real_raw_emobjs_gen[0]->Eta() - real_raw_emobjs_gen[1]->Eta();
         }
         
         // protection : when process over Wenu, _Z will not be NULL, but real_raw_emobjs_gen.size() is less than 2
         if ( _Z && _Z->abspdgid() != 23 ) _Z=NULL;

         if (_doRatioMethod){
           if (type ==0 || type == 1) {
             int electronSelector = (emobjs[0]->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec)
                                     *emobjs[0]->has_good_spatial_track_match());
             electronSelector += 2*(emobjs[1]->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)
                                    *emobjs[1]->has_good_spatial_track_match());
             if (_MCStudy || _DropTriggerObjectMatchRequirement){
               electronSelector =emobjs[0]->has_good_spatial_track_match();
               electronSelector += 2*(emobjs[1]->has_good_spatial_track_match());
             }
             _ratiomethod->Analyze(zcand, met, triglist_flag, instlumi ,recoil_vect, electronSelector);
           }
         }
	
         double evtweight = 1.;
         // if we want to study SM backgrounds such as W+X, Z->tautau events
         // we need to do event reweight to get the difference between data and full MC
         if(_SMBkgStudy && _Z) {
           evtweight *= _evtReweightManager->ZPtReweight(mc_zMass, mc_zPt, mc_zRapidity);  	
           evtweight *= _evtReweightManager->KFactor(mc_zMass);
           evtweight *= _evtReweightManager->PreselEffReweight(emobjs[0]);
           evtweight *= _evtReweightManager->PreselEffReweight(emobjs[1]);
           evtweight *= _evtReweightManager->EMIDEffReweight(emobjs[0]);
           evtweight *= _evtReweightManager->EMIDEffReweight(emobjs[1]);

           if(emobjs[0]->has_good_spatial_track_match()) evtweight *= _evtReweightManager->TrkEffReweight(emobjs[0], vtx_z);
           if(emobjs[1]->has_good_spatial_track_match()) evtweight *= _evtReweightManager->TrkEffReweight(emobjs[1], vtx_z);	
         } // SM background study

         // study uparallel efficiency using tag-probe method
         if((type==0 || type==1) && _uParaEffStudy) uParaEfficiencyStudies(event, emobjs, recoil_vect, instlumi, vtx_z, zcand);
         // make recoil file for Matt's method
         if(_makeRecoilFile) {
           if(type ==0 || type == 1) {
             makeRecoilFile(event, emobjs, instlumi, type, zScalarEt);
           } // CC-CC or CC-EC
         } // makeRecoilFile
      
         // properties for Z bosons	  
         _histos.Fill1D("ZCandMass", mass, evtweight);
         _histos.Fill1D("ZCandMass_Cal", mass_cal, evtweight);
         _histos.Fill1D("ZCandPt", zPt, evtweight);
	 _histos.Fill1D("ZCandPx", zPx, evtweight);
	 _histos.Fill1D("ZCandPy", zPy, evtweight);
	 _histos.Fill1D("ZCandPz", zPz, evtweight);
         _histos.Fill1D("ZCandAt", zAt, evtweight);
         _histos.Fill1D("ZCandAl", zAl, evtweight);
         if(_Z) {
           _histos.Fill1D("ZCandMCPt", mc_zPt, evtweight);
           _histos.Fill1D("ZCandMCPtDiff", mc_zPt-zPt, evtweight);
//            _histos.Fill1D("ZCandMCPtDiff", mc_ptee-zPt, evtweight);
//           cout << " mc_zphi " << mc_zphi << " zPhi " << zPhi << endl;
           _histos.Fill1D("ZCandMCPhiDiff", TVector2::Phi_mpi_pi(mc_zphi-zPhi), evtweight);
           _histos.Fill1D("ZCandDiffElecPt",  zcand.EM(0)->Pt() - mc_pte1 , evtweight);
           _histos.Fill1D("ZCandDiffElecPt",  zcand.EM(1)->Pt() - mc_pte2 , evtweight);
           _histos.Fill1D("ZCandDiffElec0Pt",  zcand.EM(0)->Pt() - mc_pte1 , evtweight);
           _histos.Fill1D("ZCandDiffElec1Pt",  zcand.EM(1)->Pt() - mc_pte2 , evtweight);
           _histos.Fill1D("ZCandElecGenPt",  mc_pte1 , evtweight);
           _histos.Fill1D("ZCandElecGenPt",  mc_pte2 , evtweight);
           _histos.Fill1D("ZCandElecGen0Pt",  mc_pte1 , evtweight);
           _histos.Fill1D("ZCandElecGen1Pt",  mc_pte2 , evtweight);
           _histos.Fill1D("ZCandElecRawGenPt",  mc_raw_pte1 , evtweight);
           _histos.Fill1D("ZCandElecRawGenPt",  mc_raw_pte2 , evtweight);
           _histos.Fill1D("ZCandElecRawGen0Pt",  mc_raw_pte1 , evtweight);
           _histos.Fill1D("ZCandElecRawGen1Pt",  mc_raw_pte2 , evtweight);
           _histos.Fill1D(string("ZCandDiffElecPt_")+sn,  zcand.EM(0)->Pt() - mc_pte1 , evtweight);
           _histos.Fill1D(string("ZCandDiffElecPt_")+sn,  zcand.EM(1)->Pt() - mc_pte2 , evtweight);
           _histos.Fill1D(string("ZCandDiffElec0Pt_")+sn,  zcand.EM(0)->Pt() - mc_pte1 , evtweight);
           _histos.Fill1D(string("ZCandDiffElec1Pt_")+sn,  zcand.EM(1)->Pt() - mc_pte2 , evtweight);
           _histos.Fill1D(string("ZCandElecGenPt_")+sn,  mc_pte1 , evtweight);
           _histos.Fill1D(string("ZCandElecGenPt_")+sn,  mc_pte2 , evtweight);
           _histos.Fill1D(string("ZCandElecGen0Pt_")+sn,  mc_pte1 , evtweight);
           _histos.Fill1D(string("ZCandElecGen1Pt_")+sn,  mc_pte2 , evtweight);
           _histos.Fill1D(string("ZCandElecRawGenPt_")+sn,  mc_raw_pte1 , evtweight);
           _histos.Fill1D(string("ZCandElecRawGenPt_")+sn,  mc_raw_pte2 , evtweight);
           _histos.Fill1D(string("ZCandElecRawGen0Pt_")+sn,  mc_raw_pte1 , evtweight);
           _histos.Fill1D(string("ZCandElecRawGen1Pt_")+sn,  mc_raw_pte2 , evtweight);

           _histos.Fill1D("ZCandDiffElecE",  zcand.EM(0)->E() - mc_Ee1 , evtweight);
           _histos.Fill1D("ZCandDiffElecE",  zcand.EM(1)->E() - mc_Ee2 , evtweight);
           _histos.Fill1D("ZCandDiffElec0E",  zcand.EM(0)->E() - mc_Ee1 , evtweight);
           _histos.Fill1D("ZCandDiffElec1E",  zcand.EM(1)->E() - mc_Ee2 , evtweight);
           _histos.Fill1D("ZCandElecGenE",  mc_Ee1 , evtweight);
           _histos.Fill1D("ZCandElecGenE",  mc_Ee2 , evtweight);
           _histos.Fill1D("ZCandElecGen0E",  mc_Ee1 , evtweight);
           _histos.Fill1D("ZCandElecGen1E",  mc_Ee2 , evtweight);
           _histos.Fill1D("ZCandElecRawGenE",  mc_raw_Ee1 , evtweight);
           _histos.Fill1D("ZCandElecRawGenE",  mc_raw_Ee2 , evtweight);
           _histos.Fill1D("ZCandElecRawGen0E",  mc_raw_Ee1 , evtweight);
           _histos.Fill1D("ZCandElecRawGen1E",  mc_raw_Ee2 , evtweight);
           _histos.Fill1D(string("ZCandDiffElecE_")+sn,  zcand.EM(0)->E() - mc_Ee1 , evtweight);
           _histos.Fill1D(string("ZCandDiffElecE_")+sn,  zcand.EM(1)->E() - mc_Ee2 , evtweight);
           _histos.Fill1D(string("ZCandDiffElec0E_")+sn,  zcand.EM(0)->E() - mc_Ee1 , evtweight);
           _histos.Fill1D(string("ZCandDiffElec1E_")+sn,  zcand.EM(1)->E() - mc_Ee2 , evtweight);
           _histos.Fill1D(string("ZCandElecGenE_")+sn,  mc_Ee1 , evtweight);
           _histos.Fill1D(string("ZCandElecGenE_")+sn,  mc_Ee2 , evtweight);
           _histos.Fill1D(string("ZCandElecGen0E_")+sn,  mc_Ee1 , evtweight);
           _histos.Fill1D(string("ZCandElecGen1E_")+sn,  mc_Ee2 , evtweight);
           _histos.Fill1D(string("ZCandElecRawGenE_")+sn,  mc_raw_Ee1 , evtweight);
           _histos.Fill1D(string("ZCandElecRawGenE_")+sn,  mc_raw_Ee2 , evtweight);
           _histos.Fill1D(string("ZCandElecRawGen0E_")+sn,  mc_raw_Ee1 , evtweight);
           _histos.Fill1D(string("ZCandElecRawGen1E_")+sn,  mc_raw_Ee2 , evtweight);

           _histos.Fill1D("ZCandDiffMass", mass - mc_zMass, evtweight);
           _histos.Fill1D(string("ZCandDiffMass_")+sn, mass - mc_zMass, evtweight);

         }

	 if (_MCStudy && _doZBevent) {
           _histos.Fill1D("ZCandScalarEt_ZB", _ZBSET, evtweight);
	   _histos.Fill1D(TString("ZCandScalarEt_ZB_")+sn, _ZBSET, evtweight);
         }
         _histos.Fill1D("ZCandEta", zEta, evtweight);
         _histos.Fill1D("ZCandPhi", zPhi, evtweight);
         _histos.Fill1D("ZCandMet", zMet, evtweight);
         _histos.Fill1D("ZCandMetPhi", zMetPhi, evtweight);
         _histos.Fill1D("ZCandMetX", zMetx, evtweight);
         _histos.Fill1D("ZCandMetY", zMety, evtweight);
         _histos.Fill1D("ZCandRecoilPt", recoilPt, evtweight);
         _histos.Fill1D("ZCandRecoilPhi", recoilPhi, evtweight);
         _histos.Fill1D("ZCandRecoilPx", recoilPx, evtweight);
         _histos.Fill1D("ZCandRecoilPy", recoilPy, evtweight);
         _histos.Fill1D("ZCandInstLumi", instlumi, evtweight);
         _histos.Fill2D("ZCandNCaloCellsVInstLumi",cells->NumCells()- emobjs[0]->getEMCluster()->ncells() - emobjs[1]->getEMCluster()->ncells() ,instlumi );
         _histos.Fill1D("ZCandNCaloCells",cells->NumCells() - emobjs[0]->getEMCluster()->ncells() - emobjs[1]->getEMCluster()->ncells());
         if(_MCStudy && _MakeOverlayEventList) {
           int ZBRunno = event.getMCEventInfo()->overlayrun();
           int ZBEvtno = event.getMCEventInfo()->overlayevtid();
      
           std::ofstream olistfile("ZMC_overlay_events.txt",ios::app);
           olistfile << ZBRunno << "  " << ZBEvtno << std::endl;
           olistfile.close();
         }
         _histos.Fill1D("ZCandVtx", vtx_z, evtweight);
         _histos.Fill1D("ZCandNPV", NPV, evtweight);
         _histos.Fill1D("ZCandTick", tickNo, evtweight);
         _histos.Fill1D("ZCandDeltaPhi_Z_Recoil", phi_Z_Recoil, evtweight);
         _histos.Fill1D("ZCandDeltaPhi_Z_Met", phi_Z_met, evtweight);
         _histos.Fill1D("ZCandScalarEt", zScalarEt, evtweight);
         _histos.Fill1D("ZCandSqrtScalarEt", sqrt(zScalarEt), evtweight);
         _histos.Fill1D(string("ZCandMass_")+sn, mass, evtweight);
         _histos.Fill1D(string("ZCandMass_Cal_")+sn, mass_cal, evtweight);
         _histos.Fill1D(string("ZCandPt_")+sn, zPt, evtweight);
	 _histos.Fill1D(string("ZCandPx_")+sn, zPx, evtweight);
	 _histos.Fill1D(string("ZCandPy_")+sn, zPy, evtweight);
	 _histos.Fill1D(string("ZCandPz_")+sn, zPz, evtweight);
         _histos.Fill1D(string("ZCandAt_")+sn, zAt, evtweight);
         _histos.Fill1D(string("ZCandAl_")+sn, zAl, evtweight);
         _histos.Fill1D(string("ZCandEta_")+sn, zEta, evtweight);
         _histos.Fill1D(string("ZCandPhi_")+sn, zPhi, evtweight);
         _histos.Fill1D(string("ZCandMet_")+sn, zMet, evtweight);
         _histos.Fill1D(string("ZCandMetPhi_")+sn, zMetPhi, evtweight);
         _histos.Fill1D(string("ZCandMetX_")+sn, zMetx, evtweight);
         _histos.Fill1D(string("ZCandMetY_")+sn, zMety, evtweight);
         _histos.Fill1D(string("ZCandRecoilPt_")+sn, recoilPt, evtweight);
         _histos.Fill1D(string("ZCandRecoilPhi_")+sn, recoilPhi, evtweight);
         _histos.Fill1D(string("ZCandRecoilPx_")+sn, recoilPx, evtweight);
         _histos.Fill1D(string("ZCandRecoilPy_")+sn, recoilPy, evtweight);
         _histos.Fill1D(string("ZCandInstLumi_")+sn, instlumi, evtweight);
         _histos.FillProfile(string("ZCandScalarEt_V_Lumi_")+sn, instlumi,zScalarEt, evtweight);
         _histos.Fill2D(string("ZCandScalarEt_V_Lumi2D_")+sn, instlumi,zScalarEt, evtweight);    
         _histos.Fill1D(string("ZCandVtx_")+sn, vtx_z, evtweight);
         _histos.Fill1D(string("ZCandNPV_")+sn, NPV, evtweight);
         _histos.Fill1D(string("ZCandTick_")+sn, tickNo, evtweight);
         _histos.Fill1D(string("ZCandDeltaPhi_Z_Recoil_")+sn, phi_Z_Recoil, evtweight);
         _histos.Fill1D(string("ZCandDeltaPhi_Z_Met_")+sn, phi_Z_met, evtweight);
         _histos.Fill1D(string("ZCandScalarEt_")+sn, zScalarEt, evtweight);
         _histos.Fill1D(string("ZCandSqrtScalarEt_")+sn, sqrt(zScalarEt), evtweight);
         //for finding mass with one em, one trk 
         const TMBTrack* trk0 = zcand.EM(0)->getPtrSpatialChp();
         const TMBTrack* trk1 = zcand.EM(1)->getPtrSpatialChp();
         double mass_em_trk = 0.;
         if (trk0 != NULL) {
           mass_em_trk = pow((trk0->E()+zcand.EM(1)->E()), 2) - pow((trk0->Px()+zcand.EM(1)->Px()), 2) -
                         pow((trk0->Py()+zcand.EM(1)->Py()), 2) - pow((trk0->Pz()+zcand.EM(1)->Pz()), 2);
           if(mass_em_trk>0.) mass_em_trk = sqrt(mass_em_trk);
           else mass_em_trk=0.;
         } else if (trk1 != NULL) {
           mass_em_trk = pow((trk1->E()+zcand.EM(0)->E()), 2) - pow((trk1->Px()+zcand.EM(0)->Px()), 2) -
                         pow((trk1->Py()+zcand.EM(0)->Py()), 2) - pow((trk1->Pz()+zcand.EM(0)->Pz()), 2);
           if(mass_em_trk>0.) mass_em_trk = sqrt(mass_em_trk);
           else mass_em_trk=0.;
         }
         _histos.Fill1D("ZCandEMTrkMass", mass_em_trk, evtweight);
         _histos.Fill1D(string("ZCandEMTrkMass_")+sn, mass_em_trk, evtweight);
       
         int bin_zpT = wz_utils::pTee_Eta_Bin(zPt);
         char zpT_bin_sn[10]; sprintf(zpT_bin_sn, "%d", bin_zpT);
         if(type==0) {
           _histos.Fill1D(string("ZCandScalarEt_ZPtBin_")+zpT_bin_sn, zScalarEt, evtweight);
           _histos.Fill1D(string("ZCandSqrtScalarEt_ZPtBin_")+zpT_bin_sn, sqrt(zScalarEt), evtweight);
         }

         if(_Z) {
           _histos.Fill1D(string("ZCandMCPt_")+sn, mc_zPt, evtweight);
           _histos.Fill1D(string("ZCandMCPtDiff_")+sn, mc_zPt-zPt, evtweight);
//            _histos.Fill1D(string("ZCandMCPtDiff_")+sn, mc_ptee-zPt, evtweight);
//            cout << " mc_zphi " << mc_zphi << " zPhi " << zPhi << endl;
           _histos.Fill1D(string("ZCandMCPhiDiff_")+sn, TVector2::Phi_mpi_pi(mc_zphi-zPhi), evtweight);
           int bin_zpT_gen = wz_utils::pTee_Eta_Bin(mc_zPt);
           char zpT_gen_bin_sn[10]; sprintf(zpT_gen_bin_sn, "%d", bin_zpT_gen);
           if(type==0) {
             _histos.Fill1D(string("ZCandScalarEt_genZPt_bin_")+zpT_gen_bin_sn, zScalarEt, evtweight);
             _histos.Fill1D(string("ZCandSqrtScalarEt_genZPt_bin_")+zpT_gen_bin_sn, sqrt(zScalarEt), evtweight);
           }
         }

         // check CCCC Z mass with two track matches for different trigger, deteta and eta categories
         if(type==0 && NumGoodSpatialTrks >= 2) {
           double trkphiEM3_1 = zcand.EM(0)->TrkPhiEM3();
           double trkphiEM3_2 = zcand.EM(1)->TrkPhiEM3();
           double emphiEM3_1 = zcand.EM(0)->CalDetectorPhi();
           double emphiEM3_2 = zcand.EM(1)->CalDetectorPhi();
           int Z_etaCategory = zcand.EtaCategory(_DetEtaCC);
           int Z_detetaCategory = zcand.DetEtaCategory(_DetEtaCC);
           int Z_triggerCategory = wz_utils::TriggerCategory(runNo);
           int Z_phimodCategory = zcand.EMPhiModCategory();
           int Z_trkphimodCategory = zcand.TrkPhiModCategory();
           int Z_trkphiEM3modCategory = zcand.TrkPhiEM3ModCategory(trkphiEM3_1, trkphiEM3_2);
           int Z_emphiEM3modCategory = zcand.TrkPhiEM3ModCategory(emphiEM3_1, emphiEM3_2);
           char Z_etaCategory_sn[10]; sprintf(Z_etaCategory_sn, "%d", Z_etaCategory);
           char Z_detetaCategory_sn[10]; sprintf(Z_detetaCategory_sn, "%d", Z_detetaCategory);
           char Z_triggerCategory_sn[10]; sprintf(Z_triggerCategory_sn, "%d", Z_triggerCategory);
           char Z_phimodCategory_sn[10]; sprintf(Z_phimodCategory_sn, "%d", Z_phimodCategory);
           char Z_trkphimodCategory_sn[10]; sprintf(Z_trkphimodCategory_sn, "%d", Z_trkphimodCategory);
           char Z_trkphiEM3modCategory_sn[10]; sprintf(Z_trkphiEM3modCategory_sn, "%d", Z_trkphiEM3modCategory);
           char Z_emphiEM3modCategory_sn[10]; sprintf(Z_emphiEM3modCategory_sn, "%d", Z_emphiEM3modCategory);
           double trkphimod1 = fmod(trkphiEM3_1*16/TMath::Pi(),1.0);
           double trkphimod2 = fmod(trkphiEM3_2*16/TMath::Pi(),1.0);

           _histos.Fill1D(string("ZCandMass_CCCC_TrkPhiEM3Mod"),trkphimod1, evtweight);
           _histos.Fill1D(string("ZCandMass_CCCC_TrkPhiEM3Mod"),trkphimod2, evtweight);

           double phimod1 = fmod(emphiEM3_1*16/TMath::Pi(),1.0);
           double phimod2 = fmod(emphiEM3_2*16/TMath::Pi(),1.0);

           _histos.Fill1D(string("ZCandMass_CCCC_PhiMod"),phimod1 , evtweight);
           _histos.Fill1D(string("ZCandMass_CCCC_PhiMod"),phimod2 , evtweight);

           if(Z_etaCategory>-1) _histos.Fill1D(string("ZCandMass_CCCC_EtaCategory_")+Z_etaCategory_sn, mass, evtweight);
           if(Z_detetaCategory>-1) _histos.Fill1D(string("ZCandMass_CCCC_DetEtaCategory_")+Z_detetaCategory_sn, mass, evtweight);
           if(Z_triggerCategory>-1) _histos.Fill1D(string("ZCandMass_CCCC_TrigCategory_")+Z_triggerCategory_sn, mass, evtweight);
           if(Z_phimodCategory>-1) _histos.Fill1D(string("ZCandMass_CCCC_PhiModCategory_")+Z_phimodCategory_sn, mass, evtweight);
           if(Z_trkphimodCategory>-1) _histos.Fill1D(string("ZCandMass_CCCC_TrkPhiModCategory_")+Z_trkphimodCategory_sn, mass, evtweight);
           if(Z_trkphiEM3modCategory>-1) _histos.Fill1D(string("ZCandMass_CCCC_TrkPhiEM3ModCategory_")+Z_trkphiEM3modCategory_sn, mass, evtweight);
           if(Z_emphiEM3modCategory>-1) _histos.Fill1D(string("ZCandMass_CCCC_EMPhiEM3ModCategory_")+Z_emphiEM3modCategory_sn, mass, evtweight);
         }

         //####################################################### 	 
         // fill some histograms for electron quantities
         //#######################################################
         for(int iem=0; iem<2; iem++) {
           const CAFEMObj *emobj = zcand.EM(iem);
           double emEnergy = emobj->E();
           double emUncorrEnergy = emobj->uncorrE();
           double emPt = emobj->Pt();
           double emCalEt = emobj->CalEt();
           double emEta = emobj->Eta();
           double emCalDetEta = emobj->CalDetectorEta();
           double emCalPhi = emobj->CalPhi();
           double ElecPhiTrkAtDCA = emobj->Phi();
           double ElecPhiTrkAtEM3 = emobj->TrkPhiEM3();
           double ElecDetPhiCALO = emobj->CalDetectorPhi();

           double emPx = emobj->Px();
           double emPy = emobj->Py();
           double emPz = emobj->Pz();

           TVector2 em_vect(emPx, emPy);
           double phi_em_Recoil = fabs(em_vect.DeltaPhi(recoil_vect));
           double phi_em_met = fabs(em_vect.DeltaPhi(met_vect));
           double upara = recoil_vect * (em_vect.Unit());
           double uperp = recoil_vect * (em_vect.Unit().Rotate(TMath::Pi()/2.));
          
           _histos.Fill1D("ZCandElecE", emEnergy, evtweight);
	   _histos.Fill1D("ZCandElecPx", emPx, evtweight);
           _histos.Fill1D("ZCandElecPy", emPy, evtweight);
           _histos.Fill1D("ZCandElecPz", emPz, evtweight);
           _histos.Fill1D("ZCandElecPt", emPt, evtweight);
	   if( iem==0 ) _histos.Fill1D("ZCandElec0Px", emPx, evtweight);
           if( iem==1 ) _histos.Fill1D("ZCandElec1Px", emPx, evtweight);
	   if( iem==0 ) _histos.Fill1D("ZCandElec0Py", emPy, evtweight);
           if( iem==1 ) _histos.Fill1D("ZCandElec1Py", emPy, evtweight);
	   if( iem==0 ) _histos.Fill1D("ZCandElec0Pz", emPz, evtweight);
           if( iem==1 ) _histos.Fill1D("ZCandElec1Pz", emPz, evtweight);
	   if( iem==0 ) _histos.Fill1D("ZCandElec0Pt", emPt, evtweight);
           if( iem==1 ) _histos.Fill1D("ZCandElec1Pt", emPt, evtweight);
           if( iem==0 ) _histos.Fill1D("ZCandElec0E", emEnergy, evtweight);
           if( iem==1 ) _histos.Fill1D("ZCandElec1E", emEnergy, evtweight);
           _histos.Fill1D("ZCandElecEta", emEta, evtweight);
           _histos.Fill1D("ZCandElecDetEta", emCalDetEta, evtweight);
           _histos.Fill1D("ZCandElecPhi", ElecPhiTrkAtDCA, evtweight);
           _histos.Fill1D("ZCandElecDetPhi", ElecDetPhiCALO, evtweight);
           _histos.Fill1D("ZCandElecPhiTrkAtDCA",ElecPhiTrkAtDCA, evtweight);
           _histos.Fill1D("ZCandElecPhiTrkAtEM3", ElecPhiTrkAtEM3, evtweight);
           _histos.Fill1D("ZCandElecDetPhiCALO", ElecDetPhiCALO, evtweight);
           _histos.Fill1D("ZCandElecTrkPhiEM3", ElecPhiTrkAtEM3, evtweight);  
           _histos.Fill1D("ZCandElecTrkPhiEM3Mod", fmod(ElecPhiTrkAtEM3*16/TMath::Pi(),1.0), evtweight);
           _histos.Fill1D("ZCandDeltaPhi_EM_Recoil", phi_em_Recoil, evtweight);
           _histos.Fill1D("ZCandDeltaPhi_EM_Met", phi_em_met, evtweight);
           _histos.Fill1D("ZCandElecUPara", upara, evtweight);
           _histos.Fill1D("ZCandElecUPerp", uperp, evtweight);

           // for different detector region
           _histos.Fill1D(string("ZCandElecE_")+sn, emEnergy, evtweight);
           _histos.Fill1D(string("ZCandElecPx_")+sn, emPx, evtweight);
           _histos.Fill1D(string("ZCandElecPy_")+sn, emPy, evtweight);
           _histos.Fill1D(string("ZCandElecPz_")+sn, emPz, evtweight);
           _histos.Fill1D(string("ZCandElecPt_")+sn, emPt, evtweight);
	   if( iem==0 ) _histos.Fill1D(string("ZCandElec0Px_")+sn, emPx, evtweight);
           if( iem==1 ) _histos.Fill1D(string("ZCandElec1Px_")+sn, emPx, evtweight);
	   if( iem==0 ) _histos.Fill1D(string("ZCandElec0Py_")+sn, emPy, evtweight);
           if( iem==1 ) _histos.Fill1D(string("ZCandElec1Py_")+sn, emPy, evtweight);
	   if( iem==0 ) _histos.Fill1D(string("ZCandElec0Pz_")+sn, emPz, evtweight);
           if( iem==1 ) _histos.Fill1D(string("ZCandElec1Pz_")+sn, emPz, evtweight);
           if( iem==0 ) _histos.Fill1D(string("ZCandElec0Pt_")+sn, emPt, evtweight);
           if( iem==1 ) _histos.Fill1D(string("ZCandElec1Pt_")+sn, emPt, evtweight);
           if( iem==0 ) _histos.Fill1D(string("ZCandElec0E_")+sn, emEnergy, evtweight);
           if( iem==1 ) _histos.Fill1D(string("ZCandElec1E_")+sn, emEnergy, evtweight);
           _histos.Fill1D(string("ZCandElecEta_")+sn, emEta, evtweight);
           _histos.Fill1D(string("ZCandElecDetEta_")+sn, emCalDetEta, evtweight);
           _histos.Fill1D(string("ZCandElecPhi_")+sn, ElecPhiTrkAtDCA, evtweight);
           _histos.Fill1D(string("ZCandElecDetPhi_")+sn, ElecDetPhiCALO, evtweight);
           _histos.Fill1D(string("ZCandElecPhiTrkAtDCA_")+sn, ElecPhiTrkAtDCA, evtweight);
           _histos.Fill1D(string("ZCandElecPhiTrkAtEM3_")+sn, ElecPhiTrkAtEM3, evtweight);
           _histos.Fill1D(string("ZCandElecDetPhiCALO_")+sn,  ElecDetPhiCALO, evtweight);
           _histos.Fill1D(string("ZCandElecTrkPhiEM3_")+sn, ElecPhiTrkAtEM3, evtweight);
           _histos.Fill1D(string("ZCandElecTrkPhiEM3Mod_")+sn, fmod(ElecPhiTrkAtEM3*16/TMath::Pi(),1.0), evtweight);
           _histos.Fill1D(string("ZCandDeltaPhi_EM_Recoil_")+sn, phi_em_Recoil, evtweight);
           _histos.Fill1D(string("ZCandDeltaPhi_EM_Met_")+sn, phi_em_met, evtweight);
           _histos.Fill1D(string("ZCandElecUPara_")+sn, upara, evtweight);
           _histos.Fill1D(string("ZCandElecUPerp_")+sn, uperp, evtweight);
           _histos.Fill2D(string("ZCandElecPt_V_Mass_")+sn, emPt, mass, evtweight);

           // fill energy around 0.2<R<0.4 for all CC-CC EM clusters
           if(type == 0) {
             _histos.Fill1D("ZCandElecEnergyCoreCone", emobj->energy_core_cone_FromIso(), evtweight);
             _histos.Fill1D("ZCandElecPtCoreCone", emobj->energy_core_cone_FromIso()*sin(emobj->Theta()), evtweight);
             _histos.FillProfile("ZCandElecEnergyCoreConeVDetEta", emCalDetEta, emobj->energy_core_cone_FromIso(), evtweight);
             _histos.FillProfile("ZCandElecPtCoreConeVDetEta", emCalDetEta, emobj->energy_core_cone_FromIso()*sin(emobj->Theta()), evtweight);	  
           }

           if(emobj->has_good_spatial_track_match()){
             const TMBTrack* track_spatial = emobj->getPtrSpatialChp();
             if(track_spatial==NULL) continue;
             TMBTrack *t_spatial = new TMBTrack(*track_spatial);
             double TrkPt = track_spatial->Pt();
             int iiem = 0;
             if (iiem==iem) iiem=1;
             const CAFEMObj *opposite_emobj = zcand.EM(iiem);
             CAFTrack ct_spatial(t_spatial);
             CAFZCand localzcand(opposite_emobj, &ct_spatial);
             double zcandmass = localzcand.Mass();
             double opp_deteta = opposite_emobj->CalDetectorEta();

             if (zcandmass > 70. && zcandmass < 110) {
               _histos.Fill1D(string("ZCandElecTrkPtOvETight"),(TrkPt / emPt) , evtweight);
               _histos.Fill1D(string("ZCandElecTrkPtOvETight_")+sn,(TrkPt / emPt) , evtweight);
               _histos.Fill1D(string("ZCandElecTrkCalMass"), zcandmass, evtweight);
               _histos.Fill1D(string("ZCandElecTrkCalMass_")+sn , zcandmass, evtweight);
               _histos.Fill1D(string("ZCandElecTrkPtTight"), TrkPt, evtweight);
               _histos.Fill1D(string("ZCandElecTrkPtTight_")+sn, TrkPt, evtweight);

               if( abs( opp_deteta) < 1.05){
                 if( abs(emCalDetEta) > 1.5 && abs(emCalDetEta) < 2.3 ) {
                   _histos.Fill1D(string("ZCandElecTrkCalMass_CC_EC"), zcandmass, evtweight);
                 }
               }
             }

             _histos.Fill1D(string("ZCandElecTrkPtOvE"),(TrkPt / emPt) , evtweight);
             _histos.Fill1D(string("ZCandElecTrkPtOvE_")+sn,(TrkPt / emPt) , evtweight);
             _histos.Fill1D(string("ZCandElecTrkPtOvE_All_DetEta"),emCalDetEta, evtweight);
             _histos.Fill1D(string("ZCandElecTrkPtOvE_All_DetEta_")+sn,emCalDetEta, evtweight);		
           }
	  
           // check E/p distribution for electros have good spatial track match
           if(emobj->has_good_spatial_track_match()) {
             const TMBTrack* track_spatial = emobj->getPtrSpatialChp();
             // double check to make sure track is not NULL (happens for MC events even if emobj->has_good_spatial_track_match()==true)
             if(track_spatial==NULL) continue;

             double TrkPt = track_spatial->Pt();
             double TrkPhi = track_spatial->Phi();	    
             _histos.Fill1D("ZCandElecTrkPt", TrkPt, evtweight);
             _histos.Fill1D(string("ZCandElecTrkPt_")+sn, TrkPt, evtweight);
                 
             if(emobj->IsCC(_DetEtaCC)) {
               // find the phimod for each electron
               // mod_phi is only meaningful for CC electron
               int mod_phi = emobj->PhiModule();
               char sn_mod[10];
               sprintf(sn_mod, "%d", mod_phi);

               double EOverP = emPt/TrkPt;
               double RawEOverP = EOverP * emUncorrEnergy/emEnergy;
               double ZElecPhiMod = fmod(16.*ElecPhiTrkAtEM3/3.1415926, 1.0);

               _histos.Fill1D("ZCandEOverP", EOverP, evtweight);
               _histos.Fill1D("ZCandRawEOverP", RawEOverP, evtweight);
               _histos.Fill1D(TString("ZCandEOverP_Mod_")+sn_mod, EOverP, evtweight);
               _histos.Fill1D(TString("ZCandRawEOverP_Mod_")+sn_mod, RawEOverP, evtweight);
               _histos.Fill2D(TString("ZCandElecEnergy_V_Eta"), emEnergy, emEta, evtweight);

               // check E/p for other variables
               if(EOverP>0.9 && EOverP<1.3) {
                 // check E/p vs electron calorimeter Et
                 _histos.FillProfile("ZCandEOverP_V_Et", emCalEt, EOverP, evtweight);

                 // check E/p for electron and positron
                 // calorimeter is blind to charge, so this distribution is useful for 
                 // checking bias on momentum measurement  
                 if(track_spatial->charge() == -1) {
                   _histos.FillProfile("ZCandEOverP_V_TrkPhi_Electron", TrkPhi, EOverP, evtweight);
                   _histos.FillProfile("ZCandEOverP_V_EMPhi_Electron", emCalPhi, EOverP, evtweight);
                 } else if (track_spatial->charge() == 1) {
                   _histos.FillProfile("ZCandEOverP_V_TrkPhi_Positron", TrkPhi, EOverP, evtweight);
                   _histos.FillProfile("ZCandEOverP_V_EMPhi_Positron", emCalPhi, EOverP, evtweight);
                 }

                 // check E/p vs physics eta to see the effect on amount of material
                 // transversed by the electron and also check geometry correction
                 _histos.FillProfile("ZCandEOverP_V_ElecEta", emEta, EOverP, evtweight);
                 _histos.FillProfile("ZCandEOverP_V_ElecDetEta", emCalDetEta, EOverP, evtweight);
                 _histos.FillProfile("ZCandEOverP_V_ElecPhi", emCalPhi, EOverP, evtweight);
                 _histos.FillProfile("ZCandEOverP_V_ElecDetPhi", ElecDetPhiCALO, EOverP, evtweight);
                 _histos.FillProfile("ZCandEOverP_V_ElecPhiMod", ZElecPhiMod, EOverP, evtweight);
               } //EOverP>0.9 and EOverP<1.3

               // for Raw E/p
               if(RawEOverP>0.9 && RawEOverP<1.3) {
                 _histos.FillProfile("ZCandRawEOverP_V_ElecEta", emEta, RawEOverP, evtweight);
                 _histos.FillProfile("ZCandRawEOverP_V_ElecDetEta", emCalDetEta, RawEOverP, evtweight);
                 _histos.FillProfile("ZCandRawEOverP_V_ElecPhi",    ElecPhiTrkAtDCA, RawEOverP, evtweight);
                 _histos.FillProfile("ZCandRawEOverP_V_ElecDetPhi", ElecDetPhiCALO, RawEOverP, evtweight);
                 _histos.FillProfile("ZCandRawEOverP_V_ElecPhiMod", ZElecPhiMod, RawEOverP, evtweight);

                 // fill E/p vs phiMod for each module
                 int mod_phi = emobj->PhiModule();
                 char sn_mod[10];
                 sprintf(sn_mod, "%d", mod_phi);
                 _histos.FillProfile(TString("ZCandEOverP_V_ElecPhiMod_")+sn_mod, ZElecPhiMod, EOverP, evtweight);
                 _histos.FillProfile(TString("ZCandRawEOverP_V_ElecPhiMod_")+sn_mod, ZElecPhiMod, RawEOverP, evtweight);
               } //for Raw E/p

               //fz studies:
               //fz categories:
               int z_fz_category_coarse= zcand.FzCategory( zcand.f_CCCC());
               char z_fz_category_coarse_char[10];
               sprintf(z_fz_category_coarse_char, "%d", z_fz_category_coarse);

               int z_fz_category= zcand.FzCategoryFine( zcand.f_CCCC());
               char z_fz_category_char[10];
               sprintf(z_fz_category_char, "%d", z_fz_category);

               int NumGoodSpatialTrks_requirement = 2;
               if(_QCDBkgStudy) NumGoodSpatialTrks_requirement = 0;
               if((z_fz_category>-1) &&(NumGoodSpatialTrks>=NumGoodSpatialTrks_requirement) &&(type == 0)) {  //only study cccc 2 trk z elec
                 if (iem==0){ //only do this once per Z
                   _histos.Fill1D(string("ZcandMass_CCCC_fz_")+z_fz_category_char, mass, evtweight);
                   _histos.Fill1D(string("ZcandMass_CCCC_fz_Coarse_")+z_fz_category_coarse_char, mass, evtweight);
                 }
                 _histos.Fill1D(string("ZcandElecPt_fz_")+z_fz_category_char, emPt, evtweight);
                 _histos.Fill1D(string("ZcandElecE_fz_")+z_fz_category_char, emEnergy, evtweight);
                 _histos.Fill1D(string("ZcandElecEta_fz_")+z_fz_category_char,emEta, evtweight);
                 _histos.Fill1D(((string("ZcandElecDetEta_fz_")+z_fz_category_char)).c_str(), emCalDetEta, evtweight);
             
                 _histos.Fill1D(string("ZcandElecPt_fz_Coarse_")+z_fz_category_coarse_char, emPt, evtweight);
                 _histos.Fill1D(string("ZcandElecE_fz_Coarse_")+z_fz_category_coarse_char, emEnergy, evtweight);
                 _histos.Fill1D(string("ZcandElecEta_fz_Coarse_")+z_fz_category_coarse_char,emEta, evtweight);
                 _histos.Fill1D(((string("ZcandElecDetEta_fz_Coarse_")+z_fz_category_coarse_char)).c_str(), emCalDetEta, evtweight);
               }// for fz
             }// CC electron only
           }//spatial track match
         } //loop over reco electron
      	
          double em1Px = zcand.EM(0)->Px();
          double em1Py = zcand.EM(0)->Py();
          double em2Px = zcand.EM(1)->Px();
          double em2Py = zcand.EM(1)->Py();

          TVector2 em1_vect(em1Px, em1Py);
          TVector2 em2_vect(em2Px, em2Py);

	  //Jenny modified to do fabs(deltaphi) like others, and to be consistent with PMCS which uses fabs(deltaphi) 4/9/13
	  double phi_em1_em2 = fabs(em1_vect.DeltaPhi( em2_vect ));
	  //double phi_em1_em2 = em1_vect.DeltaPhi( em2_vect );
          
	  double eta_em1_em2 = zcand.EM(0)->Eta() - zcand.EM(1)->Eta();
         
	  double dphi_em1_em2_2pi = zcand.EM(1)->Phi() - zcand.EM(0)->Phi();
	  dphi_em1_em2_2pi = dphi_em1_em2_2pi < 0 ? dphi_em1_em2_2pi + TMath::TwoPi() : dphi_em1_em2_2pi;
	 
	  // Only look at events with two spatial track matched electrons
	  // if(NumGoodSpatialTrks == 2) {
	  _histos.Fill2D("ZCandDeltaPhi_EM1_EM2_Zpt_2pi_varbin", dphi_em1_em2_2pi, zcand.Pt(), evtweight);
	  _histos.Fill2D(string("ZCandDeltaPhi_EM1_EM2_Zpt_2pi_varbin_")+sn, dphi_em1_em2_2pi, zcand.Pt(), evtweight);
	  //to run with luminosity bins, also uncomment histograms.hpp lines
	  //if(instlumi < 2) _histos.Fill2D("ZCandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi02_varbin", dphi_em1_em2_2pi, zcand.Pt(), evtweight);
	  //if(instlumi >= 2 && instlumi < 4) _histos.Fill2D("ZCandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi24_varbin", dphi_em1_em2_2pi, zcand.Pt(), evtweight);
	  // if(instlumi >= 4 && instlumi < 6)  _histos.Fill2D("ZCandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi46_varbin", dphi_em1_em2_2pi, zcand.Pt(), evtweight);
	  // if(instlumi >= 6)  _histos.Fill2D("ZCandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi6999_varbin", dphi_em1_em2_2pi, zcand.Pt(), evtweight);
	  
	  _histos.Fill1D("ZCandPee_eta", zcand.pee_eta(), evtweight);
	  _histos.Fill1D(string("ZCandPee_eta_")+sn, zcand.pee_eta(), evtweight);

	  _histos.Fill1D("ZCandDeltaPhi_EM1_EM2", dphi_em1_em2_2pi, evtweight);
	  _histos.Fill1D(string("ZCandDeltaPhi_EM1_EM2_")+sn, dphi_em1_em2_2pi, evtweight);

         _histos.Fill1D("ZCandCosDeltaPhi_EM1_EM2", cos(phi_em1_em2), evtweight);
         _histos.Fill1D(string("ZCandCosDeltaPhi_EM1_EM2_")+sn, cos(phi_em1_em2), evtweight);
         
         _histos.Fill1D("ZCandDiffCosDeltaPhi_EM1_EM2", cos(phi_em1_em2) - mc_cosdphiee , evtweight);
         _histos.Fill1D(string("ZCandDiffCosDeltaPhi_EM1_EM2_")+sn, cos(phi_em1_em2) - mc_cosdphiee , evtweight);

         _histos.Fill1D("ZCandDeltaEta_EM1_EM2", eta_em1_em2, evtweight);
         _histos.Fill1D(string("ZCandDeltaEta_EM1_EM2_")+sn, eta_em1_em2, evtweight);
         
         _histos.Fill1D("ZCandDiffDeltaEta_EM1_EM2", eta_em1_em2 - mc_detaee , evtweight);
         _histos.Fill1D(string("ZCandDiffDeltaEta_EM1_EM2_")+sn, eta_em1_em2 - mc_detaee , evtweight);

         // fill mass for 0 track, 1 track and 2 tracks
         // also fill mass calculated using calorimeter information only 
         _histos.Fill1D("ZCandMass_Trks", mass, evtweight);
         _histos.Fill1D("ZCandMass_Trks_Cal", mass_cal, evtweight);
         _histos.Fill1D(string("ZCandMass_Trks_")+num_spatial_trks, mass, evtweight);
         _histos.Fill1D(string("ZCandMass_Trks_Cal_")+num_spatial_trks, mass_cal, evtweight);

         if(type==0) {
           _histos.Fill1D("ZCandMass_CCCC_Trks", mass, evtweight);
           _histos.Fill1D("ZCandMass_CCCC_Trks_Cal", mass_cal, evtweight);
           _histos.Fill1D(string("ZCandMass_CCCC_Trks_")+num_spatial_trks, mass, evtweight);
           _histos.Fill1D(string("ZCandMass_CCCC_Trks_Cal_")+num_spatial_trks, mass_cal, evtweight);

           _histos.Fill2D(string("ZCandMass_vs_DetEta_CCCC_Trks_")+num_spatial_trks, zcand.EM(0)->CalDetectorEta(), mass, evtweight);
           _histos.Fill2D(string("ZCandMass_vs_Eta____CCCC_Trks_")+num_spatial_trks, zcand.EM(0)->Eta(), mass, evtweight);
           _histos.Fill2D(string("ZCandMass_vs_Pt_____CCCC_Trks_")+num_spatial_trks, zcand.EM(0)->Pt() , mass, evtweight);

           _histos.Fill2D(string("ZCandMass_vs_DetEta_CCCC_Trks_")+num_spatial_trks, zcand.EM(1)->CalDetectorEta(), mass, evtweight);
           _histos.Fill2D(string("ZCandMass_vs_Eta____CCCC_Trks_")+num_spatial_trks, zcand.EM(1)->Eta(), mass, evtweight);
           _histos.Fill2D(string("ZCandMass_vs_Pt_____CCCC_Trks_")+num_spatial_trks, zcand.EM(1)->Pt() , mass, evtweight);

           double fZ_CCCC = zcand.f_CCCC();
           _histos.Fill1D(string("ZCandfZ_CCCC_")+num_spatial_trks, fZ_CCCC, evtweight);
           _histos.Fill2D(string("ZCandMass_V_fZ_CCCC_")+num_spatial_trks, fZ_CCCC, mass, evtweight);
           _histos.FillProfile(string("ZCandMass_V_fZ_CCCC_pro_")+num_spatial_trks, fZ_CCCC, mass, evtweight);
         } else if(type==1) {
           _histos.Fill1D("ZCandMass_CCEC_Trks", mass, evtweight);
           _histos.Fill1D("ZCandMass_CCEC_Trks_Cal", mass_cal, evtweight);
           _histos.Fill1D(string("ZCandMass_CCEC_Trks_")+num_spatial_trks, mass, evtweight);
           _histos.Fill1D(string("ZCandMass_CCEC_Trks_Cal_")+num_spatial_trks, mass_cal, evtweight);
           double fZ_CCEC = zcand.f_CCEC();
           _histos.Fill1D(string("ZCandfZ_CCEC_")+num_spatial_trks, fZ_CCEC, evtweight);
           _histos.Fill2D(string("ZCandMass_V_fZ_CCEC_")+num_spatial_trks, fZ_CCEC, mass, evtweight);
           _histos.FillProfile(string("ZCandMass_V_fZ_CCEC_pro_")+num_spatial_trks, fZ_CCEC, mass, evtweight);
         } else if(type==2) {
           _histos.Fill1D("ZCandMass_ECEC_Trks", mass, evtweight);
           _histos.Fill1D("ZCandMass_ECEC_Trks_Cal", mass_cal, evtweight);
           _histos.Fill1D(string("ZCandMass_ECEC_Trks_")+num_spatial_trks, mass, evtweight);
           _histos.Fill1D(string("ZCandMass_ECEC_Trks_Cal_")+num_spatial_trks, mass_cal, evtweight);
           double fZ_ECEC = zcand.f_ECEC();
           _histos.Fill1D(string("ZCandfZ_ECEC_")+num_spatial_trks, fZ_ECEC, evtweight);
           _histos.Fill2D(string("ZCandMass_V_fZ_ECEC_")+num_spatial_trks, fZ_ECEC, mass, evtweight);
           _histos.FillProfile(string("ZCandMass_V_fZ_ECEC_pro_")+num_spatial_trks, fZ_ECEC, mass, evtweight);
         }
	
         // Only look at events with two spatial track matched electrons
         if(NumGoodSpatialTrks == 2) {
           _histos.Fill1D("ZCandMass_TwoTrks", mass, evtweight);
           _histos.Fill1D(string("ZCandMass_TwoTrks_")+sn, mass, evtweight);
           _histos.Fill1D(string("ZCandElecPt_TwoTrks_Both_")+sn, zcand.EM(0)->Pt(), evtweight);
           _histos.Fill1D(string("ZCandElecPt_TwoTrks_Both_")+sn, zcand.EM(1)->Pt(), evtweight);
           _histos.Fill1D(string("ZCandElecPt_TwoTrks_Elec1_")+sn, zcand.EM(0)->Pt(), evtweight);
           _histos.Fill1D(string("ZCandElecPt_TwoTrks_Elec2_")+sn, zcand.EM(1)->Pt(), evtweight);
            // divide electrons into different eta categories and check Z mass for each category
           int z_elec_eta_category = zcand.EtaCategory(_DetEtaCC);
           char z_elec_eta_category_char[10];
           sprintf(z_elec_eta_category_char, "%d", z_elec_eta_category);
           if(z_elec_eta_category>-1) {
             _histos.Fill1D(string("ZCandMass_TwoTrks_Category_")+z_elec_eta_category_char, mass, evtweight);
             _histos.Fill1D(string("ZCandElecPt_TwoTrks_Category_")+z_elec_eta_category_char, zcand.EM(0)->Pt(), evtweight);
             _histos.Fill1D(string("ZCandElecPt_TwoTrks_Category_")+z_elec_eta_category_char, zcand.EM(1)->Pt(), evtweight);
           }

           // find Z mass calculated from two tracks
           const TMBTrack* trk1 = zcand.EM(0)->getPtrSpatialChp();
           const TMBTrack* trk2 = zcand.EM(1)->getPtrSpatialChp();

           if(trk1 != NULL && trk2 != NULL) {
             if(trk1->nsmt()>=1 && trk1->ncft()>=8 && trk2->nsmt()>=1 && trk2->ncft()>=8) {
               double mass_trks = pow((trk1->E()+trk2->E()), 2) - pow((trk1->Px()+trk2->Px()), 2) -
                                  pow((trk1->Py()+trk2->Py()), 2) - pow((trk1->Pz()+trk2->Pz()), 2);
               if(mass_trks>0.) mass_trks = sqrt(mass_trks);
               else mass_trks=0.;

               _histos.Fill1D("ZCandTrksMass", mass_trks, evtweight);
               _histos.Fill1D(string("ZCandTrksMass_")+sn, mass_trks, evtweight);
             }
           }
         } // two spatial-track match
	
         //########################################################
         // recoil system
         //########################################################
         double pee_eta = zcand.pee_eta();
         double pee_xi = zcand.pee_xi();
         double recoil_eta = zcand.recoil_eta();
         double recoil_xi = zcand.recoil_xi();
         double eta_imbalance = pee_eta + recoil_eta;
         double xi_imbalance = pee_xi + recoil_xi;

         // define eta-balance and xi-balance using fix hadronic scale and a+blog(pT) model
         double eta_balance = pee_eta + recoil_eta/0.507;
         double xi_balance = pee_xi + recoil_xi/0.507;

         double response_log = 0.455 + 0.053 * TMath::Log(zPt);
         double eta_balance_new = pee_eta + recoil_eta/response_log;
         double xi_balance_new = pee_xi + recoil_xi/response_log;
                    
         //determine kappa and the contribution of underlying events together
         //pow(|pT_Z + MET|, 2) and pow(P_ee, 2)
         double m3_1 = pee_eta*pee_eta + pee_xi*pee_xi;
         double m3_2 = (zPx+zMetx)*(zPx+zMetx) + (zPy+zMety)*(zPy+zMety);
                   
         //calculate the response as R = |u_t . ^hat(q_t)| / q_t
         //get the project of the recoil jet on Z boson direction
         double ut_proj_pt2 = -(zPx+zMetx)*zPx - (zPy+zMety)*zPy;
         //get the response
         double response = fabs(ut_proj_pt2/(zPt*zPt));
                   
         //##################################################
         // Mikolaj's Recoil ET-flow studies
         // Fill ET-flow per PHI tower histograms and/or 
         // dump generator/reco recoil information to a text
         // file. Only look at events with exactly two
         // spatial track matched electrons.
         //##################################################
         if(NumGoodSpatialTrks == 2 &&      // exactly 2 track matches
            type == 0 &&                    // CC-CC electron topology
            ((_MCStudy && _dumpRecoilInfo) || _do_RecoilEtFlow_studies) ) {
           EtFlowStudy(event, zcand, emobjs, vtx, zScalarEt, ScalarEt_Evt);
         }
                    
         //##################################################
         // check recoil system modelling using Z events 
         //##################################################
         if(type==0 && NumGoodSpatialTrks>=2) { 

           // divide events into different smeared pT_ee bins    
           int bin = wz_utils::pTee_Eta_Bin(zcand.Pt());
           char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);
         
           // divide into Z pT bins, projected along eta axis
           int ZPt_Projected_bin = wz_utils::pTee_Eta_Bin(pee_eta);
           char ZpT_Projected_bin_sn[10]; sprintf(ZpT_Projected_bin_sn, "%d", ZPt_Projected_bin);

           // binned in smeared Z pT
           if(bin >= 0) {
             _histos.Fill1D(string("ZCandEtaBalance_bin_")+pee_bin_sn, eta_balance, evtweight);
             _histos.Fill1D(string("ZCandXiBalance_bin_")+pee_bin_sn, xi_balance, evtweight);  	  
             _histos.Fill1D(string("ZCandEtaImBalance_bin_")+pee_bin_sn, eta_imbalance, evtweight);
             _histos.Fill1D(string("ZCandXiImBalance_bin_")+pee_bin_sn, xi_imbalance, evtweight);  	  
             _histos.Fill1D(string("ZCandNewEtaBalance_bin_")+pee_bin_sn, eta_balance_new, evtweight);
             _histos.Fill1D(string("ZCandNewXiBalance_bin_")+pee_bin_sn, xi_balance_new, evtweight);
             _histos.Fill1D(string("ZCandPt_bin_")+pee_bin_sn, zcand.Pt(), evtweight);
             _histos.Fill1D(string("ZCandPhi_bin_")+pee_bin_sn, zcand.Phi(), evtweight);
             if(_Z) {
               _histos.Fill1D(string("ZCandMCPtDiff_bin_")+pee_bin_sn, mc_zPt-zcand.Pt(), evtweight);
//                _histos.Fill1D(string("ZCandMCPtDiff_bin_")+pee_bin_sn, mc_ptee-zcand.Pt(), evtweight);
//                cout << " mc_zphi " << mc_zphi << " zPhi " << zcand.Phi() << endl;
               _histos.Fill1D(string("ZCandMCPhiDiff_bin_")+pee_bin_sn, TVector2::Phi_mpi_pi(mc_zphi-zcand.Phi()), evtweight);
               _histos.Fill1D(string("ZCandMass_bin_")+pee_bin_sn, mass, evtweight);
               _histos.Fill1D(string("ZCandDiffMass_bin_")+pee_bin_sn, mass - mc_zMass, evtweight);
               _histos.Fill1D(string("ZCandElecPt_bin_")+pee_bin_sn, zcand.EM(0)->Pt(), evtweight);
               _histos.Fill1D(string("ZCandElecPt_bin_")+pee_bin_sn, zcand.EM(1)->Pt(), evtweight);
               _histos.Fill1D(string("ZCandElec0Pt_bin_")+pee_bin_sn, zcand.EM(0)->Pt(), evtweight);
               _histos.Fill1D(string("ZCandElec1Pt_bin_")+pee_bin_sn, zcand.EM(1)->Pt(), evtweight);
               _histos.Fill1D(string("ZCandDiffElecPt_bin_")+pee_bin_sn, zcand.EM(0)->Pt() - mc_pte1 , evtweight);
               _histos.Fill1D(string("ZCandDiffElecPt_bin_")+pee_bin_sn, zcand.EM(1)->Pt() - mc_pte2 , evtweight);
               _histos.Fill1D(string("ZCandDiffElec0Pt_bin_")+pee_bin_sn, zcand.EM(0)->Pt() - mc_pte1 , evtweight);
               _histos.Fill1D(string("ZCandDiffElec1Pt_bin_")+pee_bin_sn, zcand.EM(1)->Pt() - mc_pte2 , evtweight);
               _histos.Fill1D(string("ZCandElecGenPt_bin_")+pee_bin_sn, mc_pte1 , evtweight);
               _histos.Fill1D(string("ZCandElecGenPt_bin_")+pee_bin_sn, mc_pte2 , evtweight);
               _histos.Fill1D(string("ZCandElecGen0Pt_bin_")+pee_bin_sn, mc_pte1 , evtweight);
               _histos.Fill1D(string("ZCandElecGen1Pt_bin_")+pee_bin_sn, mc_pte2 , evtweight);
               _histos.Fill1D(string("ZCandElecRawGenPt_bin_")+pee_bin_sn, mc_raw_pte1 , evtweight);
               _histos.Fill1D(string("ZCandElecRawGenPt_bin_")+pee_bin_sn, mc_raw_pte2 , evtweight);
               _histos.Fill1D(string("ZCandElecRawGen0Pt_bin_")+pee_bin_sn, mc_raw_pte1 , evtweight);
               _histos.Fill1D(string("ZCandElecRawGen1Pt_bin_")+pee_bin_sn, mc_raw_pte2 , evtweight);

               _histos.Fill1D(string("ZCandElecE_bin_")+pee_bin_sn, zcand.EM(0)->E(), evtweight);
               _histos.Fill1D(string("ZCandElecE_bin_")+pee_bin_sn, zcand.EM(1)->E(), evtweight);
               _histos.Fill1D(string("ZCandElec0E_bin_")+pee_bin_sn, zcand.EM(0)->E(), evtweight);
               _histos.Fill1D(string("ZCandElec1E_bin_")+pee_bin_sn, zcand.EM(1)->E(), evtweight);
               _histos.Fill1D(string("ZCandDiffElecE_bin_")+pee_bin_sn, zcand.EM(0)->E() - mc_Ee1 , evtweight);
               _histos.Fill1D(string("ZCandDiffElecE_bin_")+pee_bin_sn, zcand.EM(1)->E() - mc_Ee2 , evtweight);
               _histos.Fill1D(string("ZCandDiffElec0E_bin_")+pee_bin_sn, zcand.EM(0)->E() - mc_Ee1 , evtweight);
               _histos.Fill1D(string("ZCandDiffElec1E_bin_")+pee_bin_sn, zcand.EM(1)->E() - mc_Ee2 , evtweight);
               _histos.Fill1D(string("ZCandElecGenE_bin_")+pee_bin_sn, mc_Ee1 , evtweight);
               _histos.Fill1D(string("ZCandElecGenE_bin_")+pee_bin_sn, mc_Ee2 , evtweight);
               _histos.Fill1D(string("ZCandElecGen0E_bin_")+pee_bin_sn, mc_Ee1 , evtweight);
               _histos.Fill1D(string("ZCandElecGen1E_bin_")+pee_bin_sn, mc_Ee2 , evtweight);
               _histos.Fill1D(string("ZCandElecRawGenE_bin_")+pee_bin_sn, mc_raw_Ee1 , evtweight);
               _histos.Fill1D(string("ZCandElecRawGenE_bin_")+pee_bin_sn, mc_raw_Ee2 , evtweight);
               _histos.Fill1D(string("ZCandElecRawGen0E_bin_")+pee_bin_sn, mc_raw_Ee1 , evtweight);
               _histos.Fill1D(string("ZCandElecRawGen1E_bin_")+pee_bin_sn, mc_raw_Ee2 , evtweight);

               double em1Px = zcand.EM(0)->Px();
               double em1Py = zcand.EM(0)->Py();
               double em2Px = zcand.EM(1)->Px();
               double em2Py = zcand.EM(1)->Py();

               TVector2 em1_vect(em1Px, em1Py);
               TVector2 em2_vect(em2Px, em2Py);

               double phi_em1_em2 = fabs(em1_vect.DeltaPhi( em2_vect ));
               double eta_em1_em2 = zcand.EM(0)->Eta() - zcand.EM(1)->Eta();

               _histos.Fill1D(string("ZCandCosDeltaPhi_EM1_EM2_bin_")+pee_bin_sn, cos(phi_em1_em2) , evtweight);
               _histos.Fill1D(string("ZCandDiffCosDeltaPhi_EM1_EM2_bin_")+pee_bin_sn, cos(phi_em1_em2) - mc_cosdphiee , evtweight);
               _histos.Fill1D(string("ZCandDeltaEta_EM1_EM2_bin_")+pee_bin_sn, eta_em1_em2 , evtweight);
               _histos.Fill1D(string("ZCandDiffDeltaEta_EM1_EM2_bin_")+pee_bin_sn, eta_em1_em2 - mc_detaee , evtweight);
             }
             _histos.Fill1D(string("ZCandRecoilPt_bin_")+pee_bin_sn, recoilPt, evtweight);
             _histos.Fill1D(string("ZCandRecoilPhi_bin_")+pee_bin_sn, recoilPhi, evtweight);
                   
             _histos.Fill1D(string("ZCandRecoilPx_bin_")+pee_bin_sn, recoilPx, evtweight);
             _histos.Fill1D(string("ZCandRecoilPy_bin_")+pee_bin_sn, recoilPy, evtweight);
             _histos.Fill1D(string("ZCandMet_bin_")+pee_bin_sn, zMet, evtweight);
             _histos.Fill1D(string("ZCandMetPhi_bin_")+pee_bin_sn, zMetPhi, evtweight);
             _histos.Fill1D(string("ZCandMetX_bin_")+pee_bin_sn, zMetx, evtweight);
             _histos.Fill1D(string("ZCandMetY_bin_")+pee_bin_sn, zMety, evtweight);
             _histos.Fill1D(string("ZCandRecoil_CCCC_2trks") ,zcand.MagRecoil(), evtweight);
             _histos.Fill1D(string("ZCandDeltaPhi_Z_Recoil_bin_")+pee_bin_sn, phi_Z_Recoil, evtweight);
             _histos.Fill1D(string("ZCandDeltaPhi_Z_Met_bin_")+pee_bin_sn, phi_Z_met, evtweight);
             _histos.Fill1D(string("ZCandDeltaPhi_EM1_EM2_bin_")+pee_bin_sn, phi_em1_em2, evtweight);
           }

           // binned in smeared Z pT projected along eta axis
           if (ZPt_Projected_bin >= 0) {
             _histos.Fill1D(string("ZCandEtaImBalance_ZPt_Projected_bin_")+ZpT_Projected_bin_sn, eta_imbalance, evtweight);
             _histos.Fill1D(string("ZCandXiImBalance_ZPt_Projected_bin_")+ZpT_Projected_bin_sn, xi_imbalance, evtweight);
             _histos.Fill1D(string("ZCandNewEtaBalance_ZPt_Projected_bin_")+ZpT_Projected_bin_sn, eta_balance_new, evtweight);
             _histos.Fill1D(string("ZCandNewXiBalance_ZPt_Projected_bin_")+ZpT_Projected_bin_sn, xi_balance_new, evtweight);
             _histos.Fill1D(string("ZCandRecoilPt_ZPt_Projected_bin_")+ZpT_Projected_bin_sn, recoilPt, evtweight);
             _histos.Fill1D(string("ZCandRecoilPhi_ZPt_Projected_bin_")+ZpT_Projected_bin_sn, recoilPhi, evtweight);
             _histos.Fill1D(string("ZCandPt_Projected_bin_")+ZpT_Projected_bin_sn, pee_eta, evtweight);
           }
	   
	   if (bin >= 0) {
             _histos.Fill1D(string("ZCandPee_eta_bin_")+pee_bin_sn, pee_eta, evtweight);
	   }
	   
	   double recoilPx = zcand.GetRecoil().Px();
	   double recoilPy = zcand.GetRecoil().Py();
	   TVector2 recoil_vect(recoilPx, recoilPy);
	   double emPx = zcand.EM(0)->Px();
	   double emPy = zcand.EM(0)->Py();
	   TVector2 em_vect(emPx, emPy);
	   double upara = recoil_vect * (em_vect.Unit());
           double uperp = recoil_vect * (em_vect.Unit().Rotate(TMath::Pi()/2.));
	   //
	   double emPx2 = zcand.EM(1)->Px();
	   double emPy2 = zcand.EM(1)->Py();
	   TVector2 em_vect2(emPx2, emPy2);
	   double upara2 = recoil_vect * (em_vect2.Unit());
           double uperp2 = recoil_vect * (em_vect2.Unit().Rotate(TMath::Pi()/2.));

	   if (_dump_LumiEff) {
	     cout<<"Lumi1 "<<event.getMCEventInfo()->overlayrun()<<" "<<event.getMCEventInfo()->overlayevtid()<<" "
		 <<event.getMCEventInfo()->overlaylumblk()<<" "<<instlumi<<" "<<zScalarEt<<" "
		 <<zcand.EM(0)->Pt()<<" "<<zcand.EM(0)->CalDetectorEta()<<" "<<zcand.EM(0)->Eta()<<" "<<upara<<" "<<recoilPt<<endl;
	     cout<<"Lumi2 "<<event.getMCEventInfo()->overlayrun()<<" "<<event.getMCEventInfo()->overlayevtid()<<" "
		 <<event.getMCEventInfo()->overlaylumblk()<<" "<<instlumi<<" "<<zScalarEt<<" "
		 <<zcand.EM(1)->Pt()<<" "<<zcand.EM(1)->CalDetectorEta()<<" "<<zcand.EM(1)->Eta()<<" "<<upara2<<" "<<recoilPt<<endl;
	   }

	   int juparabin = -1;
	   if (upara>-15 && upara<15) {
	     juparabin=(int)((upara+15)/5);
	     char juparabin_sn[10]; sprintf(juparabin_sn, "%d", juparabin);
	     _histos.Fill1D(string("ZCandElecPt_Upara_")+juparabin_sn, zcand.EM(0)->Pt(), evtweight);
	   }
	   if (upara2>-15 && upara2<15) {
	     juparabin=(int)((upara2+15)/5);
	     char juparabin_sn[10]; sprintf(juparabin_sn, "%d", juparabin);
	     _histos.Fill1D(string("ZCandElecPt_Upara_")+juparabin_sn, zcand.EM(1)->Pt(), evtweight);
	   }

           if (_dump_Eresponse && !_MCStudy) {
             cout<<"Eresponse1 "<<runNo<<" "<<evtNo<<" "
                 <<" "<<instlumi<<" "<<zScalarEt<<" "
                 <<zcand.EM(0)->Pt()<<" "<<zcand.EM(0)->Px() << " " <<zcand.EM(0)->Py() << " " << zcand.EM(0)->Pz() << " "
                 <<zcand.EM(0)->E()<<" "<<zcand.EM(0)->CalDetectorEta()<<" "<<zcand.EM(0)->Eta()<<" "
                 <<recoilPt<< " " << upara << " " << uperp << " "
                 <<recoilPx << " " << recoilPy << " " << zcand.EM(0)->TrkPhiEM3() << " " << zcand.EM(0)->CalDetectorPhi() << " "
                 <<zcand.EM(0)->charge() << endl;
             cout<<"Eresponse2 "<<runNo<<" "<<evtNo<<" "
                 <<" "<<instlumi<<" "<<zScalarEt<<" "
                 <<zcand.EM(1)->Pt()<<" "<<zcand.EM(1)->Px() << " " <<zcand.EM(1)->Py() << " " << zcand.EM(1)->Pz() << " "
                 <<zcand.EM(1)->E()<<" "<<zcand.EM(1)->CalDetectorEta()<<" "<<zcand.EM(1)->Eta()<<" "
                 <<recoilPt<< " " << upara2 << " " << uperp2 << " "
                 <<recoilPx << " " << recoilPy << " " << zcand.EM(1)->TrkPhiEM3() << " " << zcand.EM(1)->CalDetectorPhi() << " "
                 <<zcand.EM(1)->charge() << endl;
           }

           if (_dump_Eresponse && _MCStudy)  {
             TMBMCpart* jWZ=NULL;
             std::vector<TMBMCpart *> j_raw_mc_electrons;
             std::vector<TMBMCpart *> h_em_mc_objects;

             if ( event.get("WZ boson object", jWZ) && event.get("raw mc electrons", j_raw_mc_electrons) &&event.get("em mc objects", h_em_mc_objects)) {
               if (jWZ->abspdgid() == 23){
                 int indTrue1=0;
                 int indTrue2=1;
                 double DRS1=
                    kinem::delta_R(zcand.EM(0)->Eta(),zcand.EM(0)->Phi(),j_raw_mc_electrons[0]->Eta(),j_raw_mc_electrons[0]->Phi())+
                    kinem::delta_R(zcand.EM(1)->Eta(),zcand.EM(1)->Phi(),j_raw_mc_electrons[1]->Eta(),j_raw_mc_electrons[1]->Phi());
                 double DRS2=
                    kinem::delta_R(zcand.EM(0)->Eta(),zcand.EM(0)->Phi(),j_raw_mc_electrons[1]->Eta(),j_raw_mc_electrons[1]->Phi())+
                    kinem::delta_R(zcand.EM(1)->Eta(),zcand.EM(1)->Phi(),j_raw_mc_electrons[0]->Eta(),j_raw_mc_electrons[0]->Phi());
                 if (DRS2<DRS1) {
                   indTrue1=1;
                   indTrue2=0;
                 }
                 int ind2True1=0;
                 int ind2True2=1;
                 DRS1=
                    kinem::delta_R(zcand.EM(0)->Eta(),zcand.EM(0)->Phi(),h_em_mc_objects[0]->Eta(),h_em_mc_objects[0]->Phi())+
                    kinem::delta_R(zcand.EM(1)->Eta(),zcand.EM(1)->Phi(),h_em_mc_objects[1]->Eta(),h_em_mc_objects[1]->Phi());
                 DRS2=
                    kinem::delta_R(zcand.EM(0)->Eta(),zcand.EM(0)->Phi(),h_em_mc_objects[1]->Eta(),h_em_mc_objects[1]->Phi())+
                    kinem::delta_R(zcand.EM(1)->Eta(),zcand.EM(1)->Phi(),h_em_mc_objects[0]->Eta(),h_em_mc_objects[0]->Phi());
                 if (DRS2<DRS1) {
                   ind2True1=1;
                   ind2True2=0;
                 }
                 cout<<"Eresponse1 "<<event.getMCEventInfo()->overlayrun()<<" "<<event.getMCEventInfo()->overlayevtid()<<" "
                     <<event.getMCEventInfo()->overlaylumblk()<<" "<<instlumi<<" "<<zScalarEt<<" "
                     <<zcand.EM(0)->Pt()<<" "<<zcand.EM(0)->E()<<" "<<zcand.EM(0)->CalDetectorEta()<<" "<<zcand.EM(0)->Eta()<<" "
                     <<j_raw_mc_electrons[indTrue1]->E()<<" "<<j_raw_mc_electrons[indTrue1]->Px()<<" "<<j_raw_mc_electrons[indTrue1]->Py()<<" "<<jWZ->Pt()<<" "
                     <<upara<<" "<<recoilPt<< " " << -jWZ->Px() << " " << -jWZ->Py() << " " << -jWZ->Pz() << " " << uperp << " "
                     << recoilPx << " " << recoilPy << " " << zcand.Eta_Direction().Phi() << " "
                     <<zcand.EM(0)->Px() << " " <<zcand.EM(0)->Py() << " " << zcand.EM(0)->TrkPhiEM3() << " " << zcand.EM(0)->CalDetectorPhi() << " "
                     <<zcand.EM(0)->charge() << " " << j_raw_mc_electrons[indTrue1]->Pz() << " "
                     <<h_em_mc_objects[ind2True1]->E()<<" "<<h_em_mc_objects[ind2True1]->Px()<<" "<<h_em_mc_objects[ind2True1]->Py()<<" "<<h_em_mc_objects[ind2True1]->Pz()<<" "
                     <<endl;

                 cout<<"Eresponse2 "<<event.getMCEventInfo()->overlayrun()<<" "<<event.getMCEventInfo()->overlayevtid()<<" "
                     <<event.getMCEventInfo()->overlaylumblk()<<" "<<instlumi<<" "<<zScalarEt<<" "
                     <<zcand.EM(1)->Pt()<<" "<<zcand.EM(1)->E()<<" "<<zcand.EM(1)->CalDetectorEta()<<" "<<zcand.EM(1)->Eta()<<" "
                     <<j_raw_mc_electrons[indTrue2]->E()<<" "<<j_raw_mc_electrons[indTrue2]->Px()<<" "<<j_raw_mc_electrons[indTrue2]->Py()<<" "<<jWZ->Pt()<<" "
                     <<upara2<<" "<<recoilPt<< " " << -jWZ->Px() << " " << -jWZ->Py() << " " << -jWZ->Pz() << " " << uperp2 << " "
                     << recoilPx << " " << recoilPy << " " << zcand.Eta_Direction().Phi() << " "
                     <<zcand.EM(1)->Px() << " " <<zcand.EM(1)->Py() << " " << zcand.EM(1)->TrkPhiEM3() << " " << zcand.EM(1)->CalDetectorPhi() << " "
                     <<zcand.EM(1)->charge() << " " << j_raw_mc_electrons[indTrue2]->Pz() << " "
                     <<h_em_mc_objects[ind2True2]->E()<<" "<<h_em_mc_objects[ind2True2]->Px()<<" "<<h_em_mc_objects[ind2True2]->Py()<<" "<<h_em_mc_objects[ind2True2]->Pz()<<" "

                     <<endl;
               }
             }
           }


           // divide into generator Z pT bins, not projected along eta axis
           if(_MCStudy && _Z) {
             int genZPt_bin = wz_utils::pTee_Eta_Bin(mc_zPt);
             char genZpT_bin_sn[10]; sprintf(genZpT_bin_sn, "%d", genZPt_bin);

             // binned in generator Z pT
             if(genZPt_bin >= 0) {
               _histos.Fill1D(string("ZCandEtaImBalance_genZPt_bin_")+genZpT_bin_sn, eta_imbalance, evtweight);
               _histos.Fill1D(string("ZCandXiImBalance_genZPt_bin_")+genZpT_bin_sn, xi_imbalance, evtweight);
               _histos.Fill1D(string("ZCandNewEtaBalance_genZPt_bin_")+genZpT_bin_sn, eta_balance_new, evtweight);
               _histos.Fill1D(string("ZCandNewXiBalance_genZPt_bin_")+genZpT_bin_sn, xi_balance_new, evtweight);
               _histos.Fill1D(string("ZCandRecoilPt_genZPt_bin_")+genZpT_bin_sn, recoilPt, evtweight);
               _histos.Fill1D(string("ZCandRecoilPhi_genZPt_bin_")+genZpT_bin_sn, recoilPhi, evtweight);
               _histos.Fill1D(string("ZCandMCPtDiff_genZPt_bin_")+genZpT_bin_sn, mc_zPt-zcand.Pt(), evtweight);
             }
           }
         } // CC-CC and with two track match

         _histos.Fill1D("ZCandEtaBalance", eta_balance, evtweight);
         _histos.Fill1D("ZCandXiBalance", xi_balance, evtweight);
         _histos.Fill1D("ZCandEtaImBalance", eta_imbalance, evtweight);
         _histos.Fill1D("ZCandXiImBalance", xi_imbalance, evtweight);
         _histos.FillProfile("ZCandEtaPeeRecoil", pee_eta, recoil_eta, evtweight);
         _histos.FillProfile("ZCandXiPeeRecoil", pee_xi, recoil_xi, evtweight);
         _histos.FillProfile("ZCandEtaPeeBalance", pee_eta, eta_balance, evtweight);
         _histos.FillProfile("ZCandXiPeeBalance", pee_xi, xi_balance, evtweight);
         _histos.FillProfile("ZCandEtaPeeImBalance", pee_eta, eta_imbalance, evtweight);
         _histos.FillProfile("ZCandXiPeeImBalance", pee_xi, xi_imbalance, evtweight);
         _histos.FillProfile("ZCandKappaUE", m3_1, m3_2, evtweight);
         _histos.FillProfile("ZCandPt_V_HadResponse", zPt, response, evtweight);
                   
         // fill histograms for different types
         _histos.Fill1D(string("ZCandEtaBalance_")+sn, eta_balance, evtweight);
         _histos.Fill1D(string("ZCandXiBalance_")+sn, xi_balance, evtweight);
         _histos.Fill1D(string("ZCandEtaImBalance_")+sn, eta_imbalance, evtweight);
         _histos.Fill1D(string("ZCandXiImBalance_")+sn, xi_imbalance, evtweight);
         _histos.FillProfile(string("ZCandEtaPeeRecoil_")+sn, pee_eta, recoil_eta, evtweight);
         _histos.FillProfile(string("ZCandXiPeeRecoil_")+sn, pee_xi, recoil_xi, evtweight);
         _histos.FillProfile(string("ZCandEtaPeeBalance_")+sn, pee_eta, eta_balance, evtweight);
         _histos.FillProfile(string("ZCandXiPeeBalance_")+sn, pee_xi, xi_balance, evtweight);
         _histos.FillProfile(string("ZCandEtaPeeImBalance_")+sn, pee_eta, eta_imbalance, evtweight);
         _histos.FillProfile(string("ZCandXiPeeImBalance_")+sn, pee_xi, xi_imbalance, evtweight);
         _histos.FillProfile(string("ZCandKappaUE_")+sn, m3_1, m3_2, evtweight);
         _histos.FillProfile(string("ZCandPt_V_HadResponse_")+sn, zPt, response, evtweight);
                   
       } // recoil pT cut,  NumGoodSpatialTrks >= _NumZSpatialTrk, mass range, etc. 
      
       //##################################################
       // some MC studies
       //##################################################
       if(_MCStudy) MCStudies(event, emobjs, zcand);
      
       //##################################################
       // EMF study
       //##################################################
       if(_performEMFstudy) {
         int NumSpatialTrks = zcand.NumGoodSpatialTracks();
         if(recoilPt < _ZUtCut && recoilPt >= _ZUtCut_lower &&
            NumSpatialTrks > 1 && pass_trigger) {
           EMFStudy(event,zcand);
         }
       }
     } // at least two electrons
  } // get pointers to interesting variables ( event.get("Good EMObjs" , etc
  
  return true;   

}//bool ZAnalysis::processEvent(cafe::Event& event) {

void ZAnalysis::uParaEfficiencyStudies(Event& event, std::vector<CAFEMObj*> emobjs, TVector2 recoil_vect, double instlumi, double zvtx,  CAFZCand& zcand) {

// Declare variables (and only interested in the |zvtx|)
     vector<CAFEMObj*> probeEMs;
     event.get("Good EMObjs", probeEMs);
     int runNo, evtNo;
     int nDenominator = 0;
     int nNumerator = 0;
     event.get("run number", runNo);
     event.get("event number", evtNo);
     //     cout << "RunNo = " << runNo << " EvtNo = " << evtNo << endl;
     zvtx = fabs(zvtx);
     const CAFEMObj *emobj;
     const CAFEMObj *emobj_probe;

  ////Get background shape
  vector<CAFEMObj*> v_it_bkgd;
  for (int iprobe=0; iprobe<probeEMs.size(); iprobe++) {
    if(probeEMs[iprobe]->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2) && probeEMs[iprobe]->Pt()>25.&& probeEMs[iprobe]->PassEMFracIso(0.9, 0.15)) {
      if((fabs(probeEMs[iprobe]->CalDetectorEta())<1.05 && probeEMs[iprobe]->HMx7() > 30.)
	 || (fabs(probeEMs[iprobe]->CalDetectorEta())>1.5 && fabs(probeEMs[iprobe]->CalDetectorEta())<2.3 && probeEMs[iprobe]->HMx8() > 30.)){
	v_it_bkgd.push_back(probeEMs[iprobe]);

	//	  cout<<"find background"<<endl;
      }
      //      }
    } // electron quality cuts
  } // loop over all probe electrons  
  
  //if(v_it_bkgd.size() >= 2 && (fabs(v_it_bkgd[0]->CalDetectorEta())<1.05 || fabs(v_it_bkgd[1]->CalDetectorEta())<1.05)){//CC or EC tag
  if(v_it_bkgd.size() >= 2 && fabs(v_it_bkgd[0]->CalDetectorEta())<1.05 && fabs(v_it_bkgd[1]->CalDetectorEta())<1.05){//only CC tag
    TLorentzVector v_bkgd1(v_it_bkgd[0]->Px(), v_it_bkgd[0]->Py(), v_it_bkgd[0]->Pz(), v_it_bkgd[0]->E());
    TLorentzVector v_bkgd2(v_it_bkgd[1]->Px(), v_it_bkgd[1]->Py(), v_it_bkgd[1]->Pz(), v_it_bkgd[1]->E());
    TLorentzVector v_Bkgd = v_bkgd1 + v_bkgd2;

    for(int i=0; i<2; i++){
      TVector2 probe_bkgd_vect(v_it_bkgd[i]->Px(), v_it_bkgd[i]->Py());
      double UPara_bkgd = recoil_vect * probe_bkgd_vect.Unit();
      _histos.Fill2D("ZCandMass_V_UPara_Bkgd", UPara_bkgd, v_Bkgd.M());
      _histos.Fill2D("ZCandMass_V_UPara_Bkgd_ScaleToW", UPara_bkgd*80.419/91.188, v_Bkgd.M());
    }
  }
 

// Tag and Probe Method

// Run over tag electron
     for(int iem=0; iem<emobjs.size(); ++iem){
          emobj = emobjs[iem];	
    
//    
// Denominator (minimum requirements). Tag electron with: HMx7<12 , HMx8<20, Iso<0.15, EMFrac>0.9 
// Modification: not asking for any track preselection, nor tight nor loose. Strange, but... whatever.
// Remember to use trk_presel FALSE in the configuration file, otherwise this is useless.
//
//        if(!emobj->has_spatial_track_match() || !emobj->PassHMx(12., 20.) || !emobj->PassEMFracIso(0.9, 0.15)) continue;

          if(!emobj->PassHMx(12., 20.) || !emobj->PassEMFracIso(0.9, 0.15)) continue;

// Study the dependence with the region of the Tag electron. The standard analysis is with only CC Tag. Note that we use false to force cluster fiducial cut, not track
	       bool CCtag = emobj->IsCCFid(_DetEtaCC,false);
               bool CCECtag = emobj->IsCCECFid(_DetEtaCC,_DetEtaEC1,_DetEtaEC2);
               bool ECtag = emobj->IsECFid(_DetEtaEC1, _DetEtaEC2);

// Study the dependence with the pT track match. This is, in principle, modelled independently in the EPMCS

// ZHU's modification
	       bool tag_good_spatial_track_match = emobj->has_good_spatial_track_match(0.01,kTRUE,0.);

// Run over probe electron
          for(int iem_probe=0; iem_probe<probeEMs.size(); ++iem_probe){
	       emobj_probe = probeEMs[iem_probe];
	       CAFZCand zcand(emobj, emobj_probe);

// Had to separate, same as above
	       bool probe_good_spatial_track_match = emobj_probe->has_good_spatial_track_match(0.01,kTRUE,0.);

// Denominator (minimum requirement). 70 GeV < Invariant Mass < 110 GeV and probe in the CC. Again, cluster fiducial cut
	       float mass = zcand.Mass();
               if( (mass<70.) || (mass>110.) ) continue;
               bool CCprobe = emobj_probe->IsCCFid(_DetEtaCC,false);


// Calculate U||
	       TVector2 probe_elec_vect(emobj_probe->Px(), emobj_probe->Py());
	       double UPara = recoil_vect * probe_elec_vect.Unit();
	       int uParaBin = wz_utils::UParaBins(UPara);
	       double Etrans = probe_elec_vect.Mod();


	       double recoilPt = recoil_vect.Mod();
               double recoilAng = TMath::Abs(recoil_vect.Phi()-probe_elec_vect.Phi());
	       if (recoilAng > TMath::Pi()) {
		 recoilAng = TMath::TwoPi()-recoilAng;
	       }
	       double recoilCos = TMath::Cos(recoilAng);

// Fill denominator histograms
               if(CCtag && CCprobe && tag_good_spatial_track_match) {
  		    nDenominator++;
                    _histos.Fill1D("ZCandUPara_Denominator_Tagprobe", UPara);
                    _histos.Fill2D("ZCandUPara_V_CosPhi_Denominator_Tagprobe", UPara, recoilCos);
                    _histos.Fill2D("ZCandU_V_CosPhi_Denominator_Tagprobe", recoilPt, recoilCos);
                    if (instlumi < 0.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_0_Tagprobe", UPara);
                    else if (instlumi < 1.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_1_Tagprobe", UPara);
                    else if (instlumi < 1.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_2_Tagprobe", UPara);
                    else if (instlumi < 2.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_3_Tagprobe", UPara);
                    else if (instlumi < 2.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_4_Tagprobe", UPara);
                    else if (instlumi < 3.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_5_Tagprobe", UPara);
                    else if (instlumi < 3.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_6_Tagprobe", UPara);
                    else if (instlumi < 4.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_7_Tagprobe", UPara);
                    else if (instlumi < 4.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_8_Tagprobe", UPara);
                    else if (instlumi < 5.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_9_Tagprobe", UPara);
                    else if (instlumi < 5.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_10_Tagprobe", UPara);
                    else if (instlumi < 6.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_11_Tagprobe", UPara);
                    else if (instlumi < 6.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_12_Tagprobe", UPara);
                    else if (instlumi < 7.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_13_Tagprobe", UPara);
                    else if (instlumi < 7.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_14_Tagprobe", UPara);
                    else if (instlumi < 8.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_15_Tagprobe", UPara);
                    else if (instlumi < 8.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_16_Tagprobe", UPara);
                    else _histos.Fill1D("ZCandUPara_Denominator_instlumi_17_Tagprobe", UPara);
                    _histos.Fill2D("ZCandUPara_V_instlumi_Denominator_Tagprobe", UPara, instlumi);
                    _histos.Fill1D("ZCandUParaETRatio_Denominator_Tagprobe", UPara/Etrans);
                    
               }
               if(CCtag && CCprobe && recoilPt<15 && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_Denominator_UtCut_Tagprobe", UPara);
               if(CCtag && CCprobe && emobj->has_good_spatial_track_match(0.01,kTRUE,10.)) _histos.Fill1D("ZCandUPara_Denominator_PtCut_Tagprobe", UPara);
               if(CCtag && emobj_probe->IsCCFid(_DetEtaCC,true) && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_Denominator_phifiducial_Tagprobe", UPara);
               if(CCtag && CCprobe && tag_good_spatial_track_match && emobj_probe->has_good_spatial_track_match(-0.5,kFALSE,0)) _histos.Fill1D("ZCandUPara_Denominator_trkpresel_Tagprobe", UPara);
               if(CCtag && CCprobe && zvtx<40 && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_Denominator_VtxCut_Tagprobe", UPara);
               if(CCtag && CCprobe && emobjs.size()==2 && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_Denominator_2EM_Tagprobe", UPara);
               if(CCECtag) _histos.Fill1D("ZCandUPara_Denominator_CCECtag_Tagprobe", UPara);
               if(ECtag) _histos.Fill1D("ZCandUPara_Denominator_ECtag_Tagprobe", UPara);
                  
               // old histograms... kept for the part with data
               if(CCtag && CCprobe && tag_good_spatial_track_match) { 
                    _histos.Fill2D("ZCandMass_V_UPara_WithoutIsoHMxCut", UPara, mass);
	            _histos.Fill1D("ZCandUPara_WithoutIsoHMxCut_trkmatch", UPara);
               }
               
// Numerator cuts (minimum requirements). Probe electron: HMx7<7, Iso<0.15, EMFrac>0.9, SMT Hit (good spatial track match).       
	       if(!emobj_probe->PassHMx(12., 20.) || !emobj_probe->PassEMFracIso(0.9, 0.15) || !probe_good_spatial_track_match) continue;

// Fill numerator histograms
               if(CCtag && CCprobe && tag_good_spatial_track_match) {
                    nNumerator++;
                    _histos.Fill1D("ZCandUPara_Numerator_Tagprobe", UPara);
                    _histos.Fill2D("ZCandUPara_V_CosPhi_Numerator_Tagprobe", UPara, recoilCos);
                    _histos.Fill2D("ZCandU_V_CosPhi_Numerator_Tagprobe", recoilCos, recoilCos);
                    if (instlumi < 0.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_0_Tagprobe", UPara);
                    else if (instlumi < 1.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_1_Tagprobe", UPara);
                    else if (instlumi < 1.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_2_Tagprobe", UPara);
                    else if (instlumi < 2.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_3_Tagprobe", UPara);
                    else if (instlumi < 2.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_4_Tagprobe", UPara);
                    else if (instlumi < 3.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_5_Tagprobe", UPara);
                    else if (instlumi < 3.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_6_Tagprobe", UPara);
                    else if (instlumi < 4.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_7_Tagprobe", UPara);
                    else if (instlumi < 4.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_8_Tagprobe", UPara);
                    else if (instlumi < 5.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_9_Tagprobe", UPara);
                    else if (instlumi < 5.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_10_Tagprobe", UPara);
                    else if (instlumi < 6.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_11_Tagprobe", UPara);
                    else if (instlumi < 6.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_12_Tagprobe", UPara);
                    else if (instlumi < 7.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_13_Tagprobe", UPara);
                    else if (instlumi < 7.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_14_Tagprobe", UPara);
                    else if (instlumi < 8.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_15_Tagprobe", UPara);
                    else if (instlumi < 8.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_16_Tagprobe", UPara);
                    else _histos.Fill1D("ZCandUPara_Numerator_instlumi_17_Tagprobe", UPara);
                    _histos.Fill2D("ZCandUPara_V_instlumi_Numerator_Tagprobe", UPara, instlumi);
                    _histos.Fill1D("ZCandUParaETRatio_Numerator_Tagprobe", UPara/Etrans);
                    
               }
               if(CCtag && CCprobe && recoilPt<15 && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_Numerator_UtCut_Tagprobe", UPara);
               if(CCtag && CCprobe && emobj->has_good_spatial_track_match(0.01,kTRUE,10.) && emobj_probe->has_good_spatial_track_match(0.01,kTRUE,10.)) _histos.Fill1D("ZCandUPara_Numerator_PtCut_Tagprobe", UPara);
               if(CCtag && emobj_probe->IsCCFid(_DetEtaCC,true) && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_Numerator_phifiducial_Tagprobe", UPara);
               if(CCtag && CCprobe && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_Numerator_trkpresel_Tagprobe", UPara);
               if(CCtag && CCprobe && tag_good_spatial_track_match && zvtx<40) _histos.Fill1D("ZCandUPara_Numerator_VtxCut_Tagprobe", UPara);
               if(CCtag && CCprobe && tag_good_spatial_track_match && emobjs.size()==2) _histos.Fill1D("ZCandUPara_Numerator_2EM_Tagprobe", UPara);
               if(CCECtag) _histos.Fill1D("ZCandUPara_Numerator_CCECtag_Tagprobe", UPara);
               if(ECtag) _histos.Fill1D("ZCandUPara_Numerator_ECtag_Tagprobe", UPara);
                  
               // old histograms... kept for the part with data
               if(CCtag && CCprobe && tag_good_spatial_track_match) { 
                    _histos.Fill2D("ZCandMass_V_UPara_WithIsoHMxCut_trkmatch", UPara, mass);
	            _histos.Fill1D("ZCandUPara_WithIsoHMxCut_trkmatch", UPara);
               }
                  
          } // probe electron       
     } // tag electron

     //     cout << "   nDenominator = " << nDenominator << endl;
     //     cout << "   nNumerator = " << nNumerator << endl;

// Truth Method: work only for GEANT samples
     
// Run over first EM object electron
     for(int iem=0; iem<emobjs.size(); ++iem){
          emobj = emobjs[iem];	
    
// Truth method: no denominator cuts    

// Study the dependence with the region of the Tag electron. The standard analysis is with only CC Tag. Use false to force cluster fiducial cut
               bool CCtag = emobj->IsCCFid(_DetEtaCC,false);
               bool CCECtag = emobj->IsCCECFid(_DetEtaCC,_DetEtaEC1,_DetEtaEC2);
               bool ECtag = emobj->IsECFid(_DetEtaEC1, _DetEtaEC2);

// Study the dependence with the pT track match. This is, in principle, modelled independently in the EPMCS
	       bool tag_good_spatial_track_match = emobj->has_good_spatial_track_match(0.01,kTRUE,0.);
          
// Run over second electron
          for(int iem_probe=0; iem_probe<probeEMs.size(); ++iem_probe){
	       emobj_probe = probeEMs[iem_probe];
	       CAFZCand zcand(emobj, emobj_probe);

// 70 GeV < Invariant Mass < 110 GeV
	       float mass = zcand.Mass();
               if( (mass<70.) || (mass>110.) ) continue; 
               bool CCprobe = emobj_probe->IsCCFid(_DetEtaCC,false);

// Had to separate
	       bool probe_good_spatial_track_match = emobj_probe->has_good_spatial_track_match(0.01,kTRUE,0.);

// Calculate U||
	       TVector2 probe_elec_vect(emobj_probe->Px(), emobj_probe->Py());
	       double UPara = recoil_vect * probe_elec_vect.Unit();
	       int uParaBin = wz_utils::UParaBins(UPara);
	       double Etrans = probe_elec_vect.Mod();

	       double recoilPt = recoil_vect.Mod();
               double recoilAng = TMath::Abs(recoil_vect.Phi()-probe_elec_vect.Phi());
	       if (recoilAng > TMath::Pi()) {
		 recoilAng = TMath::TwoPi()-recoilAng;
	       }
	       double recoilCos = TMath::Cos(recoilAng);
               
// Fill denominator histograms
               if(CCtag && CCprobe && tag_good_spatial_track_match) {
                    _histos.Fill1D("ZCandUPara_Denominator_Truth", UPara);
                    _histos.Fill2D("ZCandUPara_V_CosPhi_Denominator_Truth", UPara, recoilCos);
                    _histos.Fill2D("ZCandU_V_CosPhi_Denominator_Truth", recoilPt, recoilCos);
                    if (instlumi < 0.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_0_Truth", UPara);
                    else if (instlumi < 1.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_1_Truth", UPara);
                    else if (instlumi < 1.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_2_Truth", UPara);
                    else if (instlumi < 2.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_3_Truth", UPara);
                    else if (instlumi < 2.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_4_Truth", UPara);
                    else if (instlumi < 3.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_5_Truth", UPara);
                    else if (instlumi < 3.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_6_Truth", UPara);
                    else if (instlumi < 4.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_7_Truth", UPara);
                    else if (instlumi < 4.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_8_Truth", UPara);
                    else if (instlumi < 5.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_9_Truth", UPara);
                    else if (instlumi < 5.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_10_Truth", UPara);
                    else if (instlumi < 6.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_11_Truth", UPara);
                    else if (instlumi < 6.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_12_Truth", UPara);
                    else if (instlumi < 7.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_13_Truth", UPara);
                    else if (instlumi < 7.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_14_Truth", UPara);
                    else if (instlumi < 8.) _histos.Fill1D("ZCandUPara_Denominator_instlumi_15_Truth", UPara);
                    else if (instlumi < 8.5) _histos.Fill1D("ZCandUPara_Denominator_instlumi_16_Truth", UPara);
                    else _histos.Fill1D("ZCandUPara_Denominator_instlumi_17_Truth", UPara);
                    _histos.Fill2D("ZCandUPara_V_instlumi_Denominator_Truth", UPara, instlumi);
                    _histos.Fill1D("ZCandUParaETRatio_Denominator_Truth", UPara/Etrans);
                    
               }
               if(CCtag && CCprobe && tag_good_spatial_track_match && recoilPt<15) _histos.Fill1D("ZCandUPara_Denominator_UtCut_Truth", UPara);
               if(CCtag && CCprobe && emobj->has_good_spatial_track_match(0.01,kTRUE,10.)) _histos.Fill1D("ZCandUPara_Denominator_PtCut_Truth", UPara);
               if(CCtag && emobj_probe->IsCCFid(_DetEtaCC,true) && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_Denominator_phifiducial_Truth", UPara);
               if(CCtag && CCprobe && tag_good_spatial_track_match && emobj_probe->has_good_spatial_track_match(-0.5,kFALSE,0)) _histos.Fill1D("ZCandUPara_Denominator_trkpresel_Truth", UPara);
               if(CCtag && CCprobe && tag_good_spatial_track_match && zvtx<40) _histos.Fill1D("ZCandUPara_Denominator_VtxCut_Truth", UPara);
               if(CCtag && CCprobe && tag_good_spatial_track_match && emobjs.size()==2) _histos.Fill1D("ZCandUPara_Denominator_2EM_Truth", UPara);
               if(CCECtag) _histos.Fill1D("ZCandUPara_Denominator_CCECtag_Truth", UPara);
               if(ECtag) _histos.Fill1D("ZCandUPara_Denominator_ECtag_Truth", UPara);
                  
               // old histograms... kept for compatibility
               if(CCtag && CCprobe && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_notrkmatch_UPara", UPara);
               
// Numerator cuts (minimum requirements). Probe electron: HMx7<7, Iso<0.15, EMFrac>0.9, SMT hit, in CC       
	       if(!emobj_probe->PassHMx(12., 20.) || !emobj_probe->PassEMFracIso(0.9, 0.15) || !probe_good_spatial_track_match) continue;


// Fill numerator histograms
               if(CCtag && CCprobe && tag_good_spatial_track_match) {
                    _histos.Fill1D("ZCandUPara_Numerator_Truth", UPara);
                    _histos.Fill2D("ZCandUPara_V_CosPhi_Numerator_Truth", UPara, recoilCos);
                    _histos.Fill2D("ZCandU_V_CosPhi_Numerator_Truth", recoilPt, recoilCos);
                    if (instlumi < 0.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_0_Truth", UPara);
                    else if (instlumi < 1.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_1_Truth", UPara);
                    else if (instlumi < 1.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_2_Truth", UPara);
                    else if (instlumi < 2.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_3_Truth", UPara);
                    else if (instlumi < 2.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_4_Truth", UPara);
                    else if (instlumi < 3.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_5_Truth", UPara);
                    else if (instlumi < 3.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_6_Truth", UPara);
                    else if (instlumi < 4.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_7_Truth", UPara);
                    else if (instlumi < 4.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_8_Truth", UPara);
                    else if (instlumi < 5.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_9_Truth", UPara);
                    else if (instlumi < 5.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_10_Truth", UPara);
                    else if (instlumi < 6.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_11_Truth", UPara);
                    else if (instlumi < 6.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_12_Truth", UPara);
                    else if (instlumi < 7.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_13_Truth", UPara);
                    else if (instlumi < 7.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_14_Truth", UPara);
                    else if (instlumi < 8.) _histos.Fill1D("ZCandUPara_Numerator_instlumi_15_Truth", UPara);
                    else if (instlumi < 8.5) _histos.Fill1D("ZCandUPara_Numerator_instlumi_16_Truth", UPara);
                    else _histos.Fill1D("ZCandUPara_Numerator_instlumi_17_Truth", UPara);
                    _histos.Fill2D("ZCandUPara_V_instlumi_Numerator", UPara, instlumi);
                    _histos.Fill1D("ZCandUParaETRatio_Numerator_Truth", UPara/Etrans);
                    
               }
               if(CCtag && CCprobe && tag_good_spatial_track_match && recoilPt<15) _histos.Fill1D("ZCandUPara_Numerator_UtCut_Truth", UPara);
               if(CCtag && CCprobe && emobj->has_good_spatial_track_match(0.01,kTRUE,10.) && emobj_probe->has_good_spatial_track_match(0.01,kTRUE,10.)) _histos.Fill1D("ZCandUPara_Numerator_PtCut_Truth", UPara);
               if(CCtag && emobj_probe->IsCCFid(_DetEtaCC,true) && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_Numerator_phifiducial_Truth", UPara);
               if(CCtag && CCprobe && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_Numerator_trkpresel_Truth", UPara);
               if(CCtag && CCprobe && tag_good_spatial_track_match && zvtx<40) _histos.Fill1D("ZCandUPara_Numerator_VtxCut_Truth", UPara);
               if(CCtag && CCprobe && tag_good_spatial_track_match && emobjs.size()==2) _histos.Fill1D("ZCandUPara_Numerator_2EM_Truth", UPara);
               if(CCECtag) _histos.Fill1D("ZCandUPara_Numerator_CCECtag_Truth", UPara);
               if(ECtag) _histos.Fill1D("ZCandUPara_Numerator_ECtag_Truth", UPara);
                  
               // old histograms... kept for compatibility
               if(CCtag && CCprobe && tag_good_spatial_track_match) _histos.Fill1D("ZCandUPara_trkmatch_UPara", UPara);
                  
          } // first electron       
     } // second electron
}


// for MC studies
void ZAnalysis::MCStudies(cafe::Event& event, vector<CAFEMObj*>& emobjs, CAFZCand& zcand) {
  
  std::vector<TMBMCpart *> _good_mc_emobjs;
  TMBMCpart * _WZ;
  TMBMCpart * _mc_Recoil;
  CAFMet met;
      
  float vtx_x, vtx_y, vtx_z;

  if (event.get("em mc objects", _good_mc_emobjs) && event.get("WZ boson object", _WZ) &&
      event.get("mc recoil object", _mc_Recoil) && event.get("EMCorr Met", met) &&
      event.get("Best primary vertexX", vtx_x) &&
      event.get("Best primary vertexY", vtx_y) && event.get("Best primary vertexZ", vtx_z)) {

    // protection
    if (_WZ &&_WZ->abspdgid() != 23 ) return ;

    // primary vertex information
    float vtx[3] = {vtx_x, vtx_y, vtx_z};
	  
    _mc_histos.Fill1D("MC_RECOIL_RECO_deltapx",zcand.Px() - _mc_Recoil->Px());
    _mc_histos.Fill1D("MC_RECOIL_RECO_deltapy",zcand.Py() - _mc_Recoil->Py());
    _mc_histos.Fill1D("MC_RECOIL_RECO_deltapt",zcand.Pt() - _mc_Recoil->Pt());
    
    _mc_histos.Fill1D("MC_RECOIL_RECO_deltaeta",zcand.Eta() - _mc_Recoil->Eta());
    _mc_histos.Fill1D("MC_RECOIL_RECO_deltaphi",kinem::delta_phi(zcand.Phi(), _mc_Recoil->Phi()));
    
    _mc_histos.Fill1D("ZMC_RECO_deltaMass", _WZ->Mag() - zcand.Mass());
    _mc_histos.Fill1D("ZMC_RECO_deltaZPt", _WZ->Pt() - zcand.Pt());
        
    // for different Z type, 0 for CCCC, 1 for CCEC, 2 for ECEC
    int type = zcand.Type(_DetEtaCC, _DetEtaEC1, _DetEtaEC2);
    char snum[10];
    sprintf(snum, "%d", type);

    _mc_histos.Fill1D(string("ZMC_RECO_deltaMass_")+snum, _WZ->Mag() - zcand.Mass());
    _mc_histos.Fill1D(string("ZMC_RECO_deltaZPt_")+snum, _WZ->Pt() - zcand.Pt());
    
    _mc_histos.Fill1D("ZMCMass", _WZ->Mag());
    _mc_histos.Fill1D("ZMCPt", _WZ->Pt());
    
    _mc_histos.Fill1D("MC_RECOIL_Px", _mc_Recoil->Px());
    _mc_histos.Fill1D("MC_RECOIL_Py", _mc_Recoil->Py());
    _mc_histos.Fill1D("MC_RECOIL_Pt", _mc_Recoil->Pt());
    _mc_histos.Fill1D("MC_RECOIL_Eta",_mc_Recoil->Eta());
    _mc_histos.Fill1D("MC_RECOIL_Phi",_mc_Recoil->Phi());
    
    _mc_histos.Fill2D("MC_RECOIL_Pt_V_RECO_RECOIL_pt", _mc_Recoil->Pt(), zcand.MagRecoil() );
    _mc_histos.Fill2D("MC_RECOIL_Pt_V_RECO_RECOIL_pt_response", _mc_Recoil->Pt(), zcand.MagRecoil()/_mc_Recoil->Pt() );
    
    if (_smearingStudy){
      //bin in 10 eta bins
      int htab = int(5.0*_mc_Recoil->Eta()); //10 bins in eta (study all eta region)
      if (_mc_Recoil->Eta()<0.0){
	htab+=14;
      } else {
	htab+=15; 
      }
      if ((htab)<0) htab=0;
      if ((htab)>29) htab=29;
      char hes[10];
      sprintf(hes, "%d", htab);
      _mc_histos.Fill2D(string("MC_RECOIL_Pt_V_RECO_RECOIL_pt_")+hes
			,_mc_Recoil->Pt(), zcand.MagRecoil() );
      _mc_histos.Fill2D(string("MC_RECOIL_Pt_V_RECO_RECOIL_pt_response_")+hes
			,_mc_Recoil->Pt(), zcand.MagRecoil()/_mc_Recoil->Pt() );
    
      //
      //fill MC smearing histograms:
      //Hadronic resolution first:
      //pt 
      int ptbin = int((_mc_Recoil->Pt())/5.0);
      if (ptbin >= 20) ptbin=20; 
      char sptbin[10];
      sprintf(sptbin, "%d", ptbin);
      double ptres = (_mc_Recoil->Pt() - zcand.MagRecoil())/_mc_Recoil->Pt();
      _mc_histos.Fill1D(string("ZRecoilSmearPt_TruePtBin_")+sptbin, ptres);
      //and phi resolution as function of pt
      double phires = kinem::signed_delta_phi(_mc_Recoil->Phi(),zcand.GetRecoil().Phi());
      _mc_histos.Fill1D(string("ZRecoilSmearPhi_TruePtBin_")+sptbin, phires);
      //E
      int ebin = int((_mc_Recoil->E())/5.0);
      if (ebin >= 20) ebin=20; 
      char sebin[10];
      sprintf(sebin, "%d", ebin);
      double eres = (_mc_Recoil->E() - zcand.MagRecoil())/_mc_Recoil->E();
      _mc_histos.Fill1D(string("ZRecoilSmearE_TrueEBin_")+sebin, eres);
             
    }// smearing stydy

    _mc_histos.Fill1D("MC_RECOIL_MCZ_deltapx",_WZ->Px() - _mc_Recoil->Px());
    _mc_histos.Fill1D("MC_RECOIL_MCZ_deltapy",_WZ->Py() - _mc_Recoil->Py());
    _mc_histos.Fill1D("MC_RECOIL_MCZ_deltapt",_WZ->Pt() - _mc_Recoil->Pt());
    _mc_histos.Fill1D("MC_RECOIL_MCZ_deltaeta",_WZ->Eta() - _mc_Recoil->Eta());
    _mc_histos.Fill1D("MC_RECOIL_MCZ_deltaphi",kinem::delta_phi(_WZ->Phi(), _mc_Recoil->Phi()));
    
    // fill some basic particle kinematic variables
    if(_good_mc_emobjs.size()>=2) {      
      if(_WZ) {
	// fill histograms for all good Z candidates
	for(int iem=0; iem<2; iem++) {
	  _mc_histos.Fill1D("ZMCElecE", _good_mc_emobjs[iem]->E());
	  _mc_histos.Fill1D("ZMCElecPt", _good_mc_emobjs[iem]->Pt());
	  _mc_histos.Fill1D("ZMCElecEta",  _good_mc_emobjs[iem]->Eta());
	  _mc_histos.Fill1D("ZMCElecPhi", _good_mc_emobjs[iem]->Phi());
	}
	_mc_histos.Fill1D("ZMCdeltaR", kinem::delta_R(_good_mc_emobjs[0]->Eta(), _good_mc_emobjs[0]->Phi(),
						      _good_mc_emobjs[1]->Eta(), _good_mc_emobjs[1]->Phi()));
      }// find Z boson
    } // at least two mc emobjs 

    // Look at Z candidate    
    if(emobjs.size()>=2) {

      CAFZCand zcand;
      if(_dorawCellsRecoil) zcand = CAFZCand(emobjs[0], emobjs[1], &met, vtx);
      else zcand = CAFZCand(emobjs[0], emobjs[1], &met);

      int type = zcand.Type(_DetEtaCC, _DetEtaEC1, _DetEtaEC2);
      
      char sn[10];
      sprintf(sn, "%d", type);
      for(int iem=0; iem<2; iem++) {
	if (zcand.Mass() > 70 && zcand.Mass() < 110 && _good_mc_emobjs.size() >= 2 && zcand.NumGoodSpatialTracks()>0 ) {
	  _mc_histos.Fill1D(string("ZMCElecE_")+sn, _good_mc_emobjs[iem]->E());
	  bool elec_match = false;
	  for(int jem=0; jem<2; jem++) {
	    double dR = kinem::delta_R(zcand.EM(iem)->Eta(), zcand.EM(iem)->Phi(), 
				       _good_mc_emobjs[jem]->Eta(), _good_mc_emobjs[jem]->Phi());
	    
	    _mc_histos.Fill1D(string("ZMC_RECO_deltaR_")+sn, dR);
	    _mc_histos.Fill1D("ZMC_RECO_deltaR", dR);

	    _mc_histos.Fill1D("ZMC_RECO_deltaeta", _good_mc_emobjs[jem]->Eta()- zcand.EM(iem)->Eta());
	    _mc_histos.Fill1D("ZMC_RECO_deltaphi", kinem::delta_phi(_good_mc_emobjs[jem]->Phi(),zcand.EM(iem)->TrkPhiEM3()));
	    _mc_histos.Fill1D("ZMC_RECO_deltapx", _good_mc_emobjs[jem]->Px()- zcand.EM(iem)->Px());
	    _mc_histos.Fill1D("ZMC_RECO_deltapy", _good_mc_emobjs[jem]->Py()- zcand.EM(iem)->Py());
	    _mc_histos.Fill1D("ZMC_RECO_deltapz", _good_mc_emobjs[jem]->Pz()- zcand.EM(iem)->Pz());
	    _mc_histos.Fill1D("ZMC_RECO_deltaPt", _good_mc_emobjs[jem]->Pt()- zcand.EM(iem)->Pt());

	    if (dR < 0.2 && (zcand.NumGoodSpatialTracks()==2) && !elec_match) {
	      elec_match = true;
	      _mc_histos.Fill1D(string("ZMC_RECO_deltaeta_")+sn, _good_mc_emobjs[jem]->Eta()- zcand.EM(iem)->Eta());
	      _mc_histos.Fill1D(string("ZMC_RECO_deltaphi_")+sn, kinem::delta_phi(_good_mc_emobjs[jem]->Phi(),zcand.EM(iem)->TrkPhiEM3()));
	      _mc_histos.Fill1D(string("ZMC_RECO_deltapx_")+sn, _good_mc_emobjs[jem]->Px()- zcand.EM(iem)->Px());
	      _mc_histos.Fill1D(string("ZMC_RECO_deltapy_")+sn, _good_mc_emobjs[jem]->Py()- zcand.EM(iem)->Py());
	      _mc_histos.Fill1D(string("ZMC_RECO_deltapz_")+sn, _good_mc_emobjs[jem]->Pz()- zcand.EM(iem)->Pz());
	      _mc_histos.Fill1D(string("ZMC_RECO_deltaPt_")+sn, _good_mc_emobjs[jem]->Pt()- zcand.EM(iem)->Pt());
	      
	      _mc_histos.FillProfile(string("ZMCElecE_V_ZRECOElecE_prof_")+sn, (zcand.EM(iem))->E(), _good_mc_emobjs[jem]->E());
	      _mc_histos.FillProfile(string("ZMCElecPt_V_ZRECOElecPt_prof_")+sn, (zcand.EM(iem))->Pt(), _good_mc_emobjs[jem]->Pt());
	      _mc_histos.FillProfile(string("ZMCElecPt_V_ZRECOElecPt_prof2_")+sn, (zcand.EM(iem))->Pt(), _good_mc_emobjs[jem]->Pt());
	      _mc_histos.Fill2D(string("ZMCElecE_V_ZRECOElecE_")+sn, _good_mc_emobjs[jem]->E(), (zcand.EM(iem)->E()) );
	      _mc_histos.Fill2D(string("ZMCElecPt_V_ZRECOElecPt_")+sn, _good_mc_emobjs[jem]->Pt(), (zcand.EM(iem)->Pt()));
	      _mc_histos.Fill2D(string("ZMCElecEta_V_ZRECOElecEta_")+sn, _good_mc_emobjs[jem]->Eta(), (zcand.EM(iem)->Eta()));
	      _mc_histos.Fill2D(string("ZMCElecPhi_V_ZRECOElecPhi_")+sn, _good_mc_emobjs[jem]->Phi(), (zcand.EM(iem)->TrkPhiEM3()));
	      
	      if (_smearingStudy){
		//bin in 10 eta bins
		int etab = int(5.0*_good_mc_emobjs[jem]->Eta()); //10 bins in eta (study CC region)
		if (_good_mc_emobjs[jem]->Eta()<0.0){
		  etab+=4;
		} else {
		  etab+=5; 
		}
		if ((etab)<0) etab=0;
		if ((etab)>9) etab=9;
		char es[10];
		sprintf(es, "%d", etab);
		_mc_histos.Fill2D(string("ZMCElecE_V_ZRECOElecE_")+sn+string("_")+es
				  ,_good_mc_emobjs[jem]->E(),(zcand.EM(iem)->E()));
	      }

	      _mc_histos.FillProfile("ZMCElecE_V_ZRECOElecE_prof", (zcand.EM(iem))->E(), _good_mc_emobjs[jem]->E());
	      _mc_histos.FillProfile("ZMCElecPt_V_ZRECOElecPt_prof", (zcand.EM(iem))->Pt(), _good_mc_emobjs[jem]->Pt());
	      _mc_histos.FillProfile("ZMCElecPt_V_ZRECOElecPt_prof2", (zcand.EM(iem))->Pt(), _good_mc_emobjs[jem]->Pt());
	      _mc_histos.Fill2D("ZMCElecE_V_ZRECOElecE",  _good_mc_emobjs[jem]->E(),(zcand.EM(iem))->E());
	      _mc_histos.Fill2D("ZMCElecPt_V_ZRECOElecPt",  _good_mc_emobjs[jem]->Pt(), (zcand.EM(iem))->Pt());
	      _mc_histos.Fill2D("ZMCElecEta_V_ZRECOElecEta",  _good_mc_emobjs[jem]->Eta(), (zcand.EM(iem))->Eta());
	      _mc_histos.Fill2D("ZMCElecPhi_V_ZRECOElecPhi",  _good_mc_emobjs[jem]->Phi(), (zcand.EM(iem))->TrkPhiEM3());
	      
	      if (_smearingStudy){
		//fill MC smearing histograms:
		if (type == 0) {  //CCCC ONLY:
		  //Electron resolution first:
		  //pt electron
		  int ptbin = int((_good_mc_emobjs[jem]->Pt())/5.0);
		  if (ptbin >= 20) ptbin=20; 
		  char sptbin[10];
		  sprintf(sptbin, "%d", ptbin);
		  double ptres = (_good_mc_emobjs[jem]->Pt() - zcand.EM(iem)->Pt())/_good_mc_emobjs[jem]->Pt();
		  _mc_histos.Fill1D(string("ZElectronSmearPt_CCCC_2trks_TruePtBin_")+sptbin, ptres);
		  //E electron
		  int ebin = int((_good_mc_emobjs[jem]->E())/5.0);
		  if (ebin >= 20) ebin=20; 
		  char sebin[10];
		  sprintf(sebin, "%d", ebin);

		  double trueE =_good_mc_emobjs[jem]->E();
		  double scaleE = _alpha*trueE+_beta;
		  double trueTh =_good_mc_emobjs[jem]->Theta();
		  //cout<<"true theta "<<trueTh<<" true eta "<<_good_mc_emobjs[jem]->Eta()<<endl;
		  double eres = (trueE - zcand.EM(iem)->E())/trueE;
		  _mc_histos.Fill1D(string("ZElectronSmearE_CCCC_2trks_TrueEBin_")+sebin, eres);
		  
		  // really old: double Sampling_CC = 0.15;
		  double sampling1 = _sampling1; //10.164
		  double sampling2 = _sampling2; //0.122
		  
		  double samplingexp0 = _samplingexp0; // 1.35193
		  double samplingexp1 = _samplingexp1; // 2.09564
		  double samplingexp2 = _samplingexp2; // 6.98578 
		  
		  //double sampling_exp = 1.2; //old
		  double sampling_exp = _samplingexp0 - _samplingexp1/trueE - _samplingexp2/(trueE*trueE);
		  double constant = _constant; //0.04
		  double noise = _noise; //0.29
	      
		  double truesampling = (sampling1 + sampling2/sqrt(trueE))*exp(sampling_exp/sin(trueTh))/exp(sampling_exp);
		  double trueres = sqrt(constant*constant*trueE*trueE + truesampling*truesampling*trueE + noise*noise);
		  	      
		  _mc_histos.FillProfile("ZElectronAvgModelRes_CCCC_2trks_TrueEBin", trueE, trueres/trueE);
		  _mc_histos.Fill2D("ZElectronAvgModelRes_CCCC_2trks_2D", trueE, trueres/trueE);
		  //now bin in true E and true theta of electron
		  int thbin = int((sin(_good_mc_emobjs[jem]->Theta()))/0.10) - 6;
		  if (thbin >= 4) thbin=4;
		  if (thbin < 0) thbin=0;
		  //int ethbin = ebin*4 + thbin;
		  char sthbin[10];
		  sprintf(sthbin, "%d", thbin);
		  _mc_histos.Fill1D(string("ZElectronSmearE_CCCC_2trks_TrueE_Thetabin_")+sthbin+string("_")+sebin, eres);
	      
		  //check smearing with jan's function
		}//CCCC only
	      }//smearing study 
	      
	    }//match reco to mc electrons
	  }//loop over mc electrons
	}//check if have 2 mc electrons
      } //loop over reco electron

      //
      // Measure electron energy scale and energy resolution for CC region
      //
      if(_good_mc_emobjs.size()>=2 && (type==0)) {
        double mc_pT[2], mc_E[2], E_Smear[2], pT_Smear[2], pX_Smear[2], pY_Smear[2], pZ_Smear[2];
        double mc_Eta[2], mc_Phi[2], mc_Theta[2];
        for(int imc=0; imc<2; imc++) {
          mc_pT[imc] = _good_mc_emobjs[imc]->Pt();
          mc_E[imc] = _alpha*_good_mc_emobjs[imc]->E()+_beta;
          mc_Eta[imc] = _good_mc_emobjs[imc]->Eta();
          mc_Phi[imc] = _good_mc_emobjs[imc]->Phi();
	  mc_Theta[imc] = 2.0*atan(exp(-mc_Eta[imc]));
	  double newsampling = (0.164 + 0.122/sqrt(mc_E[imc]))*exp(1.2/sin(mc_Theta[imc]))/exp(1.2);
	  
          double reso = sqrt(_constant*_constant*mc_E[imc]*mc_E[imc] + _sampling*_sampling*mc_E[imc] + _noise*_noise);
          double randN1 = _random->Gaus(0., 1.);
          double randN2 = _random->Gaus(0., 1.);
          double randN3 = _random->Gaus(0., 1.);
          
	  mc_Eta[imc] = mc_Eta[imc] * (1. + randN1*_eta_Resolution);
          mc_Phi[imc] = mc_Phi[imc] * (1. + randN2*_phi_Resolution);
          mc_Theta[imc] = 2.0*atan(exp(-mc_Eta[imc]));
	  
          E_Smear[imc] = mc_E[imc]  + randN3*reso;
          pT_Smear[imc] = E_Smear[imc] * sin(mc_Theta[imc]);
          pX_Smear[imc] = E_Smear[imc] * sin(mc_Theta[imc]) * cos(mc_Phi[imc]);
          pY_Smear[imc] = E_Smear[imc] * sin(mc_Theta[imc]) * sin(mc_Phi[imc]);
          pZ_Smear[imc] = E_Smear[imc] * cos(mc_Theta[imc]);
	  
          if(pT_Smear[imc]>25.) {
	    _mc_histos.FillProfile("ZMCElecPt_V_ZSmearElecPt", _good_mc_emobjs[imc]->Pt(), pT_Smear[imc]);
	    _mc_histos.FillProfile("ZMCElecE_V_ZSmearElecE", _good_mc_emobjs[imc]->E(), E_Smear[imc]);
	    if (zcand.NumGoodSpatialTracks()==2){ 
	      _mc_histos.Fill2D("ZMCElecESmear_V_ZRecoElecE_CCCC_2",E_Smear[imc], emobjs[imc]->E());
	    }
	    _mc_histos.Fill1D("ZMCElecPtSmear", pT_Smear[imc]);
	    //check with geant result:
	    if (zcand.NumGoodSpatialTracks()==2){ 
	      _histos.Fill2D("ZCandElecEnergyVTruth_CCCC_2trks",_good_mc_emobjs[imc]->E(),emobjs[imc]->E());
	    }
          } // good electrons
        }

	if(pT_Smear[0]>25. && pT_Smear[1]>25.) {
          double mass_smear = sqrt( (E_Smear[0]+E_Smear[1])*(E_Smear[0]+E_Smear[1]) -
                                    (pX_Smear[0]+pX_Smear[1])*(pX_Smear[0]+pX_Smear[1]) -
                                    (pY_Smear[0]+pY_Smear[1])*(pY_Smear[0]+pY_Smear[1]) -
                                    (pZ_Smear[0]+pZ_Smear[1])*(pZ_Smear[0]+pZ_Smear[1]) );
	  
          double pT_Z_smear = sqrt( (pX_Smear[0]+pX_Smear[1])*(pX_Smear[0]+pX_Smear[1]) +
                                    (pY_Smear[0]+pY_Smear[1])*(pY_Smear[0]+pY_Smear[1]) );
	  
	  _mc_histos.Fill1D("ZMCMassSmear", mass_smear);
	  _mc_histos.Fill1D("ZMCPtSmear", pT_Z_smear);
        } // good mc electrons
      } // two CC electrons for E/P study

    } // at least two EM objects
  }//get pointers

}

// EMF study
void ZAnalysis::EMFStudy(cafe::Event& event, CAFZCand& zcand) {


  // lumi and lumi bin
  double instlumi;
  event.get("InstLumi", instlumi);
  instlumi*=36;
  int theLumiBin=-1;
  for (int i=0; i<_EMFstudyNLumiBins; i++) {
    if (instlumi>_EMFstudyLumiBinStarts[i]) {
      theLumiBin=i;
    } else {
      break;
    }
  }

  double mass = zcand.Mass();
  if ((mass>EMFstudyWindowLow)&&(mass<EMFstudyWindowHigh)) {
    // CCCC or CCEC ?
    int type = zcand.Type(_DetEtaCC, _DetEtaEC1, _DetEtaEC2);
    if (type==0) {
      // categorise
      int kateg=zcand.EtaCategory(_DetEtaCC);
      assert((kateg>=0)||(kateg<=14));
      int kategD=zcand.DetEtaCategory(_DetEtaCC);
      assert((kategD>=0)||(kategD<=14));
      int bin1=zcand.EM(0)->DetEtaRegion_CC(_DetEtaCC);
      int bin2=zcand.EM(1)->DetEtaRegion_CC(_DetEtaCC);
      //
      double zPt = zcand.Pt();
      int runNo;
      event.get("run number", runNo);
      Collection<TMBPrimaryVertex> vert=event.getPrimaryVertices();
      const TMBEMCluster* E1=zcand.EM(0)->getEMCluster();
      const TMBEMCluster* E2=zcand.EM(1)->getEMCluster();
      _emf_histos.Fill1D("mass", mass);
      _emf_histos.Fill1D(TString("mass_")+=theLumiBin, mass);
      _emf_histos.Fill1D("pT", zPt);
      _emf_histos.Fill1D(TString("pT_")+=theLumiBin, zPt);
      _emf_histos.Fill1D("RunNumZee", runNo);
      _emf_histos.Fill1D(TString("RunNumZee_")+=theLumiBin, runNo);
      _emf_histos.Fill1D("InstLumZee", instlumi);
      _emf_histos.Fill1D(TString("InstLumZee_")+=theLumiBin, instlumi);
      _emf_histos.Fill1D("nVtxZee", vert.size());
      _emf_histos.Fill1D(TString("nVtxZee_")+=theLumiBin, vert.size());
      _emf_histos.Fill1D("E1pT", E1->Pt());
      _emf_histos.Fill1D(TString("E1pT_")+=theLumiBin, E1->Pt());
      _emf_histos.Fill1D("E2pT", E2->Pt());
      _emf_histos.Fill1D(TString("E2pT_")+=theLumiBin, E2->Pt());
      _emf_histos.Fill1D("E1E", E1->E());
      _emf_histos.Fill1D(TString("E1E_")+=theLumiBin, E1->E());
      _emf_histos.Fill1D("E2E", E2->E());
      _emf_histos.Fill1D(TString("E2E_")+=theLumiBin, E2->E());
      _emf_histos.Fill1D("E1physeta", E1->Eta());
      _emf_histos.Fill1D(TString("E1physeta_")+=theLumiBin, E1->Eta());
      _emf_histos.Fill1D("E2physeta", E2->Eta());
      _emf_histos.Fill1D(TString("E2physeta_")+=theLumiBin, E2->Eta());
      _emf_histos.Fill1D("E1deteta", E1->CalDetectorEta());
      _emf_histos.Fill1D(TString("E1deteta_")+=theLumiBin, E1->CalDetectorEta());
      _emf_histos.Fill1D("E2deteta", E2->CalDetectorEta());
      _emf_histos.Fill1D(TString("E2deteta_")+=theLumiBin, E2->CalDetectorEta());
      //
      double E1eraw=E1->floorE(1)+E1->floorE(2)+E1->floorE(3)+
        E1->floorE(4)+E1->floorE(5);
      double E1emf[6];
      for (int i=1; i<=5; i++) E1emf[i]=E1->floorE(i)/E1eraw;
      double E2eraw=E2->floorE(1)+E2->floorE(2)+E2->floorE(3)+
        E2->floorE(4)+E2->floorE(5);
      double E2emf[6];
      for (int i=1; i<=5; i++) E2emf[i]=E2->floorE(i)/E2eraw;
      if (_EMFstudySimulateRelGains) {
        E1emf[1]*=_EMFstudyRelGainEM1; E2emf[1]*=_EMFstudyRelGainEM1;
        E1emf[2]*=_EMFstudyRelGainEM2; E2emf[2]*=_EMFstudyRelGainEM2;
        E1emf[3]*=_EMFstudyRelGainEM3; E2emf[3]*=_EMFstudyRelGainEM3;
        E1emf[4]*=_EMFstudyRelGainEM4; E2emf[4]*=_EMFstudyRelGainEM4;
        E1emf[5]*=_EMFstudyRelGainFH1; E2emf[5]*=_EMFstudyRelGainFH1;
      }
      TString n;
      for (int i=1; i<=5; i++) {
        n="E1emf_"; n+=i;
        _emf_histos.Fill1D(n, E1emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1emf[i]);
        n="E2emf_"; n+=i;
        _emf_histos.Fill1D(n, E2emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E2emf[i]);
        n="Eemf_"; n+=i;
        _emf_histos.Fill1D(n, E1emf[i]);
        _emf_histos.Fill1D(n, E2emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1emf[i]);
        _emf_histos.Fill1D(n, E2emf[i]);
        //
        n="EemfB_"; n+=i; n+="_"; n+=bin1;
        _emf_histos.Fill1D(n, E1emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1emf[i]);
        n="EemfB_"; n+=i; n+="_"; n+=bin2;
        _emf_histos.Fill1D(n, E2emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E2emf[i]);
      }
      // categorised - phys eta
      n="massK_"; n+=kateg;
      _emf_histos.Fill1D(n, mass);
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, mass);
      n="InstLumZeeK_"; n+=kateg;
      _emf_histos.Fill1D(n, instlumi);
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, instlumi);
      n="pTK_"; n+=kateg;
      _emf_histos.Fill1D(n, zPt);
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, zPt);
      n="E1pTK_"; n+=kateg;
      _emf_histos.Fill1D(n, E1->Pt());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E1->Pt());
      n="E2pTK_"; n+=kateg;
      _emf_histos.Fill1D(n, E2->Pt());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E2->Pt());
      n="E1EK_"; n+=kateg;
      _emf_histos.Fill1D(n, E1->E());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E1->E());
      n="E2EK_"; n+=kateg;
      _emf_histos.Fill1D(n, E2->E());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E2->E());
      n="E1physetaK_"; n+=kateg;
      _emf_histos.Fill1D(n, E1->Eta());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E1->Eta());
      n="E2physetaK_"; n+=kateg;
      _emf_histos.Fill1D(n, E2->Eta());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E2->Eta());
      n="E1detetaK_"; n+=kateg;
      _emf_histos.Fill1D(n, E1->CalDetectorEta());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E1->CalDetectorEta());
      n="E2detetaK_"; n+=kateg;
      _emf_histos.Fill1D(n, E2->CalDetectorEta());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E2->CalDetectorEta());
      //
      for (int i=1; i<=5; i++) {
        n="E1emfK_"; n+=i; n+="_"; n+=kateg;
        _emf_histos.Fill1D(n, E1emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1emf[i]);
        n="E2emfK_"; n+=i; n+="_"; n+=kateg;
        _emf_histos.Fill1D(n, E2emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E2emf[i]);
        n="EemfK_"; n+=i; n+="_"; n+=kateg;
        _emf_histos.Fill1D(n, E1emf[i]);
        _emf_histos.Fill1D(n, E2emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1emf[i]);
        _emf_histos.Fill1D(n, E2emf[i]);
      }
      // categorised - det eta
      n="massKD_"; n+=kategD;
      _emf_histos.Fill1D(n, mass);
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, mass);
      n="InstLumZeeKD_"; n+=kategD;
      _emf_histos.Fill1D(n, instlumi);
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, instlumi);
      n="pTKD_"; n+=kategD;
      _emf_histos.Fill1D(n, zPt);
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, zPt);
      n="E1pTKD_"; n+=kategD;
      _emf_histos.Fill1D(n, E1->Pt());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E1->Pt());
      n="E2pTKD_"; n+=kategD;
      _emf_histos.Fill1D(n, E2->Pt());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E2->Pt());
      n="E1EKD_"; n+=kategD;
      _emf_histos.Fill1D(n, E1->E());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E1->E());
      n="E2EKD_"; n+=kategD;
      _emf_histos.Fill1D(n, E2->E());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E2->E());
      n="E1physetaKD_"; n+=kategD;
      _emf_histos.Fill1D(n, E1->Eta());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E1->Eta());
      n="E2physetaKD_"; n+=kategD;
      _emf_histos.Fill1D(n, E2->Eta());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E2->Eta());
      n="E1detetaKD_"; n+=kategD;
      _emf_histos.Fill1D(n, E1->CalDetectorEta());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E1->CalDetectorEta());
      n="E2detetaKD_"; n+=kategD;
      _emf_histos.Fill1D(n, E2->CalDetectorEta());
      n+="_"; n+=theLumiBin;
      _emf_histos.Fill1D(n, E2->CalDetectorEta());
      //
      for (int i=1; i<=5; i++) {
        n="E1emfKD_"; n+=i; n+="_"; n+=kategD;
        _emf_histos.Fill1D(n, E1emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1emf[i]);
        n="E2emfKD_"; n+=i; n+="_"; n+=kategD;
        _emf_histos.Fill1D(n, E2emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E2emf[i]);
        n="EemfKD_"; n+=i; n+="_"; n+=kategD;
        _emf_histos.Fill1D(n, E1emf[i]);
        _emf_histos.Fill1D(n, E2emf[i]);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1emf[i]);
        _emf_histos.Fill1D(n, E2emf[i]);
      }
    } else if (type==1) {
      // Convention: let E1 be the CC leg
      const CAFEMObj* e1;
      const CAFEMObj* e2;
      if (zcand.EM(0)->IsCC(_DetEtaCC)) {
        e1=zcand.EM(0);
        e2=zcand.EM(1);
      } else {
        e1=zcand.EM(1);
        e2=zcand.EM(0);
      }
      // bin
      int bin=(int)((fabs(e2->CalDetectorEta())-1.5)/0.1);
      if (bin<0) bin=-1;
      if (bin>14) bin=-1;
      if (bin>=0) {
        if (e2->CalDetectorEta()<0) bin+=15;
      }
      //
      if (bin>=0) {
        double zPt = zcand.Pt();
        int runNo;
        event.get("run number", runNo);
        Collection<TMBPrimaryVertex> vert=event.getPrimaryVertices();
        const TMBEMCluster* E1=e1->getEMCluster();
        const TMBEMCluster* E2=e2->getEMCluster();
        _emf_histos.Fill1D("ECmass", mass);
        _emf_histos.Fill1D(TString("ECmass_")+=theLumiBin, mass);
        _emf_histos.Fill1D("ECpT", zPt);
        _emf_histos.Fill1D(TString("ECpT_")+=theLumiBin, zPt);
        _emf_histos.Fill1D("ECRunNumZee", runNo);
        _emf_histos.Fill1D(TString("ECRunNumZee_")+=theLumiBin, runNo);
        _emf_histos.Fill1D("ECInstLumZee", instlumi);
        _emf_histos.Fill1D(TString("ECInstLumZee_")+=theLumiBin, instlumi);
        _emf_histos.Fill1D("ECnVtxZee", vert.size());
        _emf_histos.Fill1D(TString("ECnVtxZee_")+=theLumiBin, vert.size());
        _emf_histos.Fill1D("ECE1pT", E1->Pt());
        _emf_histos.Fill1D(TString("ECE1pT_")+=theLumiBin, E1->Pt());
        _emf_histos.Fill1D("ECE2pT", E2->Pt());
        _emf_histos.Fill1D(TString("ECE2pT_")+=theLumiBin, E2->Pt());
        _emf_histos.Fill1D("ECE1E", E1->E());
        _emf_histos.Fill1D(TString("ECE1E_")+=theLumiBin, E1->E());
        _emf_histos.Fill1D("ECE2E", E2->E());
        _emf_histos.Fill1D(TString("ECE2E_")+=theLumiBin, E2->E());
        _emf_histos.Fill1D("ECE1physeta", E1->Eta());
        _emf_histos.Fill1D(TString("ECE1physeta_")+=theLumiBin, E1->Eta());
        _emf_histos.Fill1D("ECE2physeta", E2->Eta());
        _emf_histos.Fill1D(TString("ECE2physeta_")+=theLumiBin, E2->Eta());
        _emf_histos.Fill1D("ECE1deteta", E1->CalDetectorEta());
        _emf_histos.Fill1D(TString("ECE1deteta_")+=theLumiBin, E1->CalDetectorEta());
        _emf_histos.Fill1D("ECE2deteta", E2->CalDetectorEta());
        _emf_histos.Fill1D(TString("ECE2deteta_")+=theLumiBin, E2->CalDetectorEta());
        //
        double E1eraw=E1->floorE(1)+E1->floorE(2)+E1->floorE(3)+
          E1->floorE(4)+E1->floorE(5);
        double E1emf[6];
        for (int i=1; i<=5; i++) E1emf[i]=E1->floorE(i)/E1eraw;
        double E2eraw=E2->floorE(1)+E2->floorE(2)+E2->floorE(3)+
          E2->floorE(4)+E2->floorE(5);
        double E2emf[6];
        for (int i=1; i<=5; i++) E2emf[i]=E2->floorE(i)/E2eraw;
        if (_EMFstudySimulateRelGains) {
          E1emf[1]*=_EMFstudyRelGainEM1;
          E1emf[2]*=_EMFstudyRelGainEM2;
          E1emf[3]*=_EMFstudyRelGainEM3;
          E1emf[4]*=_EMFstudyRelGainEM4;
          E1emf[5]*=_EMFstudyRelGainFH1;
        }
        TString n;
        for (int i=1; i<=5; i++) {
          n="ECE1emf_"; n+=i;
          _emf_histos.Fill1D(n, E1emf[i]);
          n+="_"; n+=theLumiBin;
          _emf_histos.Fill1D(n, E1emf[i]);
          n="ECE2emf_"; n+=i;
          _emf_histos.Fill1D(n, E2emf[i]);
          n+="_"; n+=theLumiBin;
          _emf_histos.Fill1D(n, E2emf[i]);
          n="ECEemf_"; n+=i;
          _emf_histos.Fill1D(n, E1emf[i]);
          _emf_histos.Fill1D(n, E2emf[i]);
          n+="_"; n+=theLumiBin;
          _emf_histos.Fill1D(n, E1emf[i]);
          _emf_histos.Fill1D(n, E2emf[i]);
        }
        // binned
        n="ECmassB_"; n+=bin;
        _emf_histos.Fill1D(n, mass);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, mass);
        n="ECInstLumZeeB_"; n+=bin;
        _emf_histos.Fill1D(n, instlumi);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, instlumi);
        n="ECpTB_"; n+=bin;
        _emf_histos.Fill1D(n, zPt);
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, zPt);
        n="ECE1pTB_"; n+=bin;
        _emf_histos.Fill1D(n, E1->Pt());
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1->Pt());
        n="ECE2pTB_"; n+=bin;
        _emf_histos.Fill1D(n, E2->Pt());
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E2->Pt());
        n="ECE1EB_"; n+=bin;
        _emf_histos.Fill1D(n, E1->E());
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1->E());
        n="ECE2EB_"; n+=bin;
        _emf_histos.Fill1D(n, E2->E());
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E2->E());
        n="ECE1physetaB_"; n+=bin;
        _emf_histos.Fill1D(n, E1->Eta());
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1->Eta());
        n="ECE2physetaB_"; n+=bin;
        _emf_histos.Fill1D(n, E2->Eta());
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E2->Eta());
        n="ECE1detetaB_"; n+=bin;
        _emf_histos.Fill1D(n, E1->CalDetectorEta());
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E1->CalDetectorEta());
        n="ECE2detetaB_"; n+=bin;
        _emf_histos.Fill1D(n, E2->CalDetectorEta());
        n+="_"; n+=theLumiBin;
        _emf_histos.Fill1D(n, E2->CalDetectorEta());
        //
        for (int i=1; i<=5; i++) {
          n="ECE1emfB_"; n+=i; n+="_"; n+=bin;
          _emf_histos.Fill1D(n, E1emf[i]);
          n+="_"; n+=theLumiBin;
          _emf_histos.Fill1D(n, E1emf[i]);
          n="ECE2emfB_"; n+=i; n+="_"; n+=bin;
          _emf_histos.Fill1D(n, E2emf[i]);
          n+="_"; n+=theLumiBin;
          _emf_histos.Fill1D(n, E2emf[i]);
          n="ECEemfB_"; n+=i; n+="_"; n+=bin;
          _emf_histos.Fill1D(n, E1emf[i]);
          _emf_histos.Fill1D(n, E2emf[i]);
          n+="_"; n+=theLumiBin;
          _emf_histos.Fill1D(n, E1emf[i]);
          _emf_histos.Fill1D(n, E2emf[i]);
        }
      }
    }
  }

}

// make recoil file for Matt's studies
void ZAnalysis::makeRecoilFile(cafe::Event& event, vector<CAFEMObj*> emobjs, double instlumi, int type, double scalarEt) {

  float vtx_x, vtx_y, vtx_z;
  if(event.get("Best primary vertexX", vtx_x) && event.get("Best primary vertexY", vtx_y) && event.get("Best primary vertexZ", vtx_z)) {
    CAFMet raw_met;
    TVector2 elecvect[2];
    if (event.get("Raw Met", raw_met)) {
      float thevert[3] = {vtx_x, vtx_y, vtx_z};

      // calculate raw electron vector using cell information
      for(int iem=0; iem<2; iem++) elecvect[iem] = emobjs[iem]->getRawElecVectorFromCells(thevert);
      
      // raw met
      TVector2 raw_met_vect(raw_met.metx(), raw_met.mety());
      
      // uncorrected recoil vector
      TVector2 recoil_vector_uncorr = -1*(raw_met_vect + elecvect[0] + elecvect[1]);
      
      // calculate uparallel for both electrons
      double upara_elec[2], uparaCorr_elec[2];
      double upara_elec_nocut[2];
      for(int iem=0; iem<2; iem++) {
	upara_elec[iem] = recoil_vector_uncorr * (emobjs[iem]->vect2()).Unit();
        upara_elec_nocut[iem] = recoil_vector_uncorr * (emobjs[iem]->vect2()).Unit();		
	
        if(upara_elec[iem] < -15.) upara_elec[iem] = -15.;
	if(upara_elec[iem] > 15.) upara_elec[iem] = 15.;

	double a0=0.004433, a1=0.003575, a2=0.01056, a3=-0.00061, a4=-0.004008;
	double uparaCorr_elec_L0 = (a0 + a1/10.*upara_elec[iem] + a2/100.*upara_elec[iem]*upara_elec[iem] + 
				    a3/1000.*upara_elec[iem]*upara_elec[iem]*upara_elec[iem] + 
				    a4/10000.*upara_elec[iem]*upara_elec[iem]*upara_elec[iem]*upara_elec[iem]);
	
	double uparaCorr_elec_mean= (_UparaCorr_CC_Hist->GetRandom()) - (_UparaCorr_CC_Hist->GetMean());
	uparaCorr_elec[iem] = 13*(uparaCorr_elec_mean + uparaCorr_elec_L0 + (0.002543)*instlumi);
      } // loop over two electrons
      
      // add back uparallel corrections from the two electrons
      TVector2 recoil_vector_const_corr = recoil_vector_uncorr + 0.13*(emobjs[0]->vect2()).Unit() + 0.13*(emobjs[1]->vect2()).Unit();
      TVector2 recoil_vector_param_corr = recoil_vector_uncorr + uparaCorr_elec[0]*(emobjs[0]->vect2()).Unit() + uparaCorr_elec[1]*(emobjs[1]->vect2()).Unit();
      TVector2 recoil_vector_pcone_corr = recoil_vector_uncorr + (uparaCorr_elec[0]-.08)*(emobjs[0]->vect2()).Unit() 
	+ (uparaCorr_elec[1]-.08)*(emobjs[1]->vect2()).Unit();
      
      // smeared or measured Z pX and pY
      double Zpx_smear = emobjs[0]->Px() + emobjs[1]->Px();
      double Zpy_smear = emobjs[0]->Py() + emobjs[1]->Py();

      // generator Z pX and pY, for data, they will be equal to measured pX and pY 
      double Zpx_gen = Zpx_smear;
      double Zpy_gen = Zpy_smear;
      if(_MCStudy) {
	TMBMCpart * _WZ;
	if(event.get("WZ boson object", _WZ)) {
	  Zpx_gen = _WZ->Px();
	  Zpy_gen = _WZ->Py();
	}  
      }

      float vtx[3] = {vtx_x, vtx_y, vtx_z};
      double Zmass_smeared;
      CAFMet met;
      CAFMet rawmet;
      
       if ( event.get("EMCorr Met", met) &&  event.get("Raw Met", rawmet) ){
	CAFZCand zcand;
	if(_dorawCellsRecoil) {
	  if (_useConsistentMET) {
	    zcand = CAFZCand(emobjs[0], emobjs[1], &rawmet, vtx, true);
	  } else {
	    zcand = CAFZCand(emobjs[0], emobjs[1], &met, vtx);
	  }
	} else {
	  zcand = CAFZCand(emobjs[0], emobjs[1], &met);
	}
    	Zmass_smeared = zcand.Mass();  
      }
      else{
	Zmass_smeared = -555.;
      }

      int runno;
      event.get("run number", runno);

      double evtweight = 1.;
      recoil_data.pTZ_gen_x = Zpx_gen ; recoil_data.pTZ_gen_y = Zpy_gen ;
      recoil_data.pTZ_smear_x = Zpx_smear ; recoil_data.pTZ_smear_y = Zpy_smear ;
      recoil_data.recoil_x = recoil_vector_pcone_corr.X() ; recoil_data.recoil_y = recoil_vector_pcone_corr.Y() ;
      recoil_data.recoil_uncorr_x = recoil_vector_uncorr.X() ; recoil_data.recoil_uncorr_y = recoil_vector_uncorr.Y() ;
      recoil_data.recoil_constcorr_x = recoil_vector_const_corr.X() ; recoil_data.recoil_constcorr_y = recoil_vector_const_corr.Y() ;
      recoil_data.recoil_paramcorr_x = recoil_vector_param_corr.X() ; recoil_data.recoil_paramcorr_y = recoil_vector_param_corr.Y() ;
      recoil_data.recoil_paramconecorr_x = recoil_vector_pcone_corr.X() ; recoil_data.recoil_paramconecorr_y = recoil_vector_pcone_corr.Y() ;
      recoil_data.scalarET = scalarEt ;
      recoil_data.upara_e1 = upara_elec_nocut[0] ; recoil_data.upara_e2 = upara_elec_nocut[1] ;
      recoil_data.pT_e1 = emobjs[0]->Pt() ; recoil_data.pT_e2 = emobjs[1]->Pt() ;
      recoil_data.eta_e1 = emobjs[0]->CalDetectorEta() ; recoil_data.eta_e2 = emobjs[1]->CalDetectorEta() ;
      recoil_data.runno = runno ; recoil_data.lumi = instlumi ; recoil_data.MZ = Zmass_smeared ;
      recoil_data.type = type ; recoil_data.eventweight = evtweight;
      recoil_data.isFSR = isPhot ;
      if(isPhot) {
        recoil_data.photpT1 = HighestPhotonPt ;
        recoil_data.photpT2 = SecondHighestPhotonPt ;
      }
      else {
        recoil_data.photpT1 = 0 ;
        recoil_data.photpT2 = 0 ;
      }
      
      _RecoilTree->Fill();

      int has_track_match[2] = {0, 0};
      if(emobjs[0]->has_good_spatial_track_match()) has_track_match[0] = 1;
      if(emobjs[1]->has_good_spatial_track_match()) has_track_match[1] = 1;

    }// get raw Met
  } // primary vertex
}
// make recoil file for Matt's studies

// write event information into a text file for efficiency analysis studies
void ZAnalysis::makeEfficStudyFile(cafe::Event& event, vector<CAFEMObj*> emobjs, std::vector<TMBMCpart *> raw_emobjs_gen, double instlumi, int type, double scalarEt) {
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

      // smeared or measured Z pX and pY
      double Zpx_smear = emobjs[0]->Px() + raw_met.metx();
      double Zpy_smear = emobjs[0]->Py() + raw_met.mety();

      // generator Z pX and pY, for data, they will be equal to measured pX and pY
      double Zpx_gen = Zpx_smear;
      double Zpy_gen = Zpy_smear;
      if(_MCStudy) {
        TMBMCpart * _WZ;
        if(event.get("WZ boson object", _WZ)) {
          Zpx_gen = _WZ->Px();
          Zpy_gen = _WZ->Py();
        }
      }

      double epT_gen=0, eEta_gen=0., ePhi_gen=0.;
      double epT_gen2=0, eEta_gen2=0., ePhi_gen2=0.;
      if(_MCStudy && raw_emobjs_gen.size()>=2) {
	epT_gen = raw_emobjs_gen[0]->Pt();
	eEta_gen = raw_emobjs_gen[0]->Eta();
	ePhi_gen = raw_emobjs_gen[0]->Phi();

	epT_gen2 = raw_emobjs_gen[1]->Pt();
	eEta_gen2 = raw_emobjs_gen[1]->Eta();
	ePhi_gen2 = raw_emobjs_gen[1]->Phi();
      }

      int has_track_match = 0;
      if(emobjs[0]->has_good_spatial_track_match()) has_track_match = 1;
 
      int has_track_match2 = 0;
      if(emobjs[1]->has_good_spatial_track_match()) has_track_match2 = 1;
     
      const TMBTrack *tmp_track = emobjs[0]->getPtrSpatialChp();
      double trackpT = 0 ;
      if(has_track_match) trackpT = tmp_track->Pt();
      
      const TMBTrack *tmp_track2 = emobjs[1]->getPtrSpatialChp();
      double trackpT2 = 0;
      if(has_track_match2) trackpT2 = tmp_track2->Pt();
      
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
			  << Zpx_gen << " " << Zpy_gen << " " << Zpx_smear << " " << Zpy_smear << " "
			  << recoil_vector_uncorr.X() << " " << recoil_vector_uncorr.Y() << " "

			  << epT_gen << " " << eEta_gen << " " << ePhi_gen << " " << emobjs[0]->Pt() << " " << emobjs[0]->Eta() << " " 
			  << emobjs[0]->Phi() << " " << emobjs[0]->CalDetectorEta() << " " << emobjs[0]->CalDetectorPhi() << " " << emobjs[0]->HMx7() 
			  << " " << emobjs[0]->HMx8() << " " << emobjs[0]->emfrac() << " " << emobjs[0]->iso() 
			  << " " << has_track_match << " " << trackpT << " " 

			  << epT_gen2 << " " << eEta_gen2 << " " << ePhi_gen2 << " " << emobjs[1]->Pt() << " " << emobjs[1]->Eta() << " " 
			  << emobjs[1]->Phi() << " " << emobjs[1]->CalDetectorEta() << " " << emobjs[1]->CalDetectorPhi() << " " << emobjs[1]->HMx7() 
			  << " " << emobjs[1]->HMx8() << " " << emobjs[1]->emfrac() << " " << emobjs[1]->iso() 
			  << " " << has_track_match2 << " " << trackpT2 << " " 

			  << raw_met.metx() << " " << raw_met.mety() 
			  << " " << scalarEt << " " << type << " " << vtx_z;
      (*_effic_study_txt) << endl;


    }// get raw Met
  } // primary vertex
}

/////////////////////////////////////////////////////////////
//
// Fill ET-flow histograms for the recoil system.
// Uses direction of the Z candidate (Full MC, DATA)
// and direction of the generated Z (Full MC only).
// Also dumps GENERATOR Z boson & Recoil 4-momentum and 
// RECO Recoil transverse momentum to a text file (Full MC only). 
// 
void ZAnalysis::EtFlowStudy(cafe::Event& event,       // to access calorimeter cells
			    CAFZCand& zcand,          // to access RECO Z properties
			    vector<CAFEMObj*> emobjs, // to access EM clusters' calorimter cells
			    float vtx[3],             // to compute ET from raw cells
			    double ScalarEt_noEM,     // for recoil dump file 
			    double ScalarEt_Evt ) {   // for recoil dump file
  TMBMCpart* _mc_Z;                        // we need MC Z boson to determine PT(Z) bin for histograms
  TMBMCpart* _mc_Recoil;                   // we need MC Recoil direction for ET-flow histograms
  std::vector<TMBMCpart *> _mc_electrons;  // we need MC electrons to perform kinematical cuts 

  bool kinem_cuts_ok = false;
    
  if( _MCStudy &&
      event.get("em mc objects", _mc_electrons) &&
      event.get("WZ boson object", _mc_Z) &&
      event.get("mc recoil object", _mc_Recoil) ) {
    // # of good true MC electrons
    int nTightElectrons = 0; 
    int nLooseElectrons = 0;
    // check generator level electrons from Z
    for (std::vector<TMBMCpart *>::iterator it = _mc_electrons.begin(); 
	 it!= _mc_electrons.end(); ++it) {
      if( fabs((*it)->Eta())<_ElecLoose_EtaMax && (*it)->Pt()>_ElecLoose_PtMin) nLooseElectrons++;
      if( fabs((*it)->Eta())<_ElecTight_EtaMax && (*it)->Pt()>_ElecTight_PtMin) nTightElectrons++;
    }
    if(nLooseElectrons>=_ElecLoose_nMin &&
       nTightElectrons>=_ElecTight_nMin    ) kinem_cuts_ok=true;
  } else if (!_MCStudy) {
    kinem_cuts_ok=true;
    /*
    // # of good RECO electrons
    int nTightElectrons = 0; 
    int nLooseElectrons = 0;
    // check reco level electrons from Z
    for (std::vector<CAFEMObj *>::iterator it = emobjs.begin(); 
	 it!= emobjs.end(); ++it) {
      if( fabs((*it)->Eta())<_ElecLoose_EtaMax && (*it)->Pt()>_ElecLoose_PtMin) nLooseElectrons++;
      if( fabs((*it)->Eta())<_ElecTight_EtaMax && (*it)->Pt()>_ElecTight_PtMin) nTightElectrons++;
    }
    if(nLooseElectrons>=_ElecLoose_nMin &&
       nTightElectrons>=_ElecTight_nMin    ) kinem_cuts_ok=true;
    */
  }
  if(!kinem_cuts_ok) return; 

  // RECO Z candidate & Recoil  
  double zPt = zcand.Pt();
  double zPhi = zcand.Phi();
  double recoilPt = zcand.GetRecoil().Mod();
  double recoilPx = zcand.GetRecoil().Px();
  double recoilPy = zcand.GetRecoil().Py();
  double recoilPhi = zcand.GetRecoil().Phi();
  double phi_Z_Recoil = kinem::delta_phi(zPhi,recoilPhi);

  TVector2 zVect(zcand.Px(),zcand.Py());
  double PredRecoilPhi=zVect.Rotate(TMath::Pi()).Phi();

  ////////////////////////////////////////////////////////////////////
  // do Mikolaj's recoil ET-flow studies for Z events with w 2 spatial 
  // track matches
  ////////////////////////////////////////////////////////////////////
  if(_do_RecoilEtFlow_studies) {

    // determine the bin number for a given reco PT(Z) to fill the right histograms
    const int bin_smear  = _EtFlow_histos.tprofile("ZCand2Trks_EtFlow_recoZPt_V_recoZPt")
      ->FindBin(zPt)-1;                                                                  // reco
    const int nbin_smear = _EtFlow_histos.tprofile("ZCand2Trks_EtFlow_recoZPt_V_recoZPt")
      ->GetNbinsX();                                                                     // reco
    bool binsmear_ok = (bin_smear>=0 && bin_smear<nbin_smear);
    //
    // This part is common for MC and data.
    //
    // now recompute the recoil momentum from the cells, exclude 2 EM clusters
    // - raw_calcells_Recoil vector should be in principle same as the RECO one (it's computed as a cross-check)
    // - raw_calcells_Recoil_scaled vector is from rescaled cells and should be different that that from RECO
    TVector2 raw_calcells_Recoil_wrtRECOaxis(0., 0.);           // recoil transverse momentum from cells
    TVector2 raw_calcells_Recoil_wrtRECOaxis_scaled(0., 0.);    // recoil transverse momentum from cells (rescaled)
    TVector2 raw_calcells_Recoil_wrtRECOaxis_xcheck(0., 0.);    // recoil transverse momentum from cells (alternative)
    map<int,double> Et_flow_wrtRECOaxis;                        // average ET per PHI-tower in an event
    map<int,double> Et_flow_wrtRECOaxis_scaled;                 // average ET per PHI-tower in an event (rescaled cells)
    map<int,double>::iterator it;

    wz_utils::calc_Et_per_tower(event, emobjs, PredRecoilPhi, vtx, 
				_RelResponse_scale,
				raw_calcells_Recoil_wrtRECOaxis, raw_calcells_Recoil_wrtRECOaxis_scaled, raw_calcells_Recoil_wrtRECOaxis_xcheck,
				Et_flow_wrtRECOaxis, Et_flow_wrtRECOaxis_scaled);

    double recoilPt_cells          = raw_calcells_Recoil_wrtRECOaxis.Mod();
    double recoilPt_cells_scaled   = raw_calcells_Recoil_wrtRECOaxis_scaled.Mod();
    double recoilPt_cells_xcheck   = raw_calcells_Recoil_wrtRECOaxis_xcheck.Mod();
    double recoilPhi_cells         = kinem::phi(raw_calcells_Recoil_wrtRECOaxis.Px(), raw_calcells_Recoil_wrtRECOaxis.Py());
    double recoilPhi_cells_scaled  = kinem::phi(raw_calcells_Recoil_wrtRECOaxis_scaled.Px(), raw_calcells_Recoil_wrtRECOaxis_scaled.Py());
    double recoilPhi_cells_xcheck  = kinem::phi(raw_calcells_Recoil_wrtRECOaxis_xcheck.Px(), raw_calcells_Recoil_wrtRECOaxis_xcheck.Py());
    double phi_Recoil_Recoil_cells = kinem::delta_phi(raw_calcells_Recoil_wrtRECOaxis.Phi(),recoilPhi);
    double phi_Recoil_Recoil_cells_xcheck= kinem::delta_phi(raw_calcells_Recoil_wrtRECOaxis_xcheck.Phi(),recoilPhi);

    // Fill histograms based on RECO recoil only -- all events
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_recoZPt",
			  zPt);                                                          // reco
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_recoUt", 
			  recoilPt);                                                     // reco
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_recoRecoilPhi",
			  recoilPhi);                                                    // reco
    _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_recoZPt_V_recoZPt",
			       zPt, zPt);                                                // reco
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_DPhi_recoUt_recoZPt", 
			  phi_Z_Recoil);                                                 // reco-reco
    _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_recoUt_V_DPhi_recoUt_recoZPt",
			       phi_Z_Recoil, recoilPt);	                                 // reco-reco
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_CellsUt",
			  recoilPt_cells);                                               // cells
    /*
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_CellsScaledUt",
                          recoilPt_cells_scaled);                                        // cells(scaled)
    */
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_CellsRecoilPhi",
			  recoilPhi_cells);                                              // cells
    /*
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_CellsScaledRecoilPhi",
                          recoilPhi_cells_scaled);                                       // cells(scaled)
    */
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_DPhi_CellsUt_recoUt",
 		          phi_Recoil_Recoil_cells);                                      // cells-reco
    /*
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_DPhi_CellsScaledUt_recoUt",
			  phi_Recoil_Recoil_cells_scaled);                               // cells(scaled)-reco
    _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_DPhi_XCHECKrecoUt_recoUt",
			  phi_Recoil_Recoil_cells_xcheck);                               // cells(reco xcheck)-reco
    */

    // Fill histograms related to ET FLOW of RECO recoil only -- all events
    for(int delta_iphi=-31; delta_iphi<=32; delta_iphi++) {
      if (Et_flow_wrtRECOaxis[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	_EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_recoZPt",       
				   delta_iphi, Et_flow_wrtRECOaxis[delta_iphi]);         // cells-reco
      }
      /*
      if (Et_flow_wrtRECOaxis_scaled[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
        _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_recoZPt",
                                   delta_iphi, Et_flow_wrtRECOaxis_scaled[delta_iphi]);  // cells(scaled)-reco
      }
      */
    }    
    // Fill histograms related to ET FLOW of RECO recoil only -- all events
    for(int delta_iphi=-31; delta_iphi<=32; delta_iphi++) {
      if (Et_flow_wrtRECOaxis[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	_EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_recoZPt",       
				   delta_iphi, Et_flow_wrtRECOaxis[delta_iphi]);         // cells-reco
      }
      /*
      if (Et_flow_wrtRECOaxis_scaled[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
        _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_recoZPt",
                                   delta_iphi, Et_flow_wrtRECOaxis_scaled[delta_iphi]);  // cells(scaled)-reco
      }
      */
    }    
    // individual reco PT(Z) bins
    if(binsmear_ok) {

      char sn[10];
      sprintf(sn, "_bin_%d", bin_smear);

      // individual reco PT(Z) bins

      // Fill histograms based on RECO recoil only -- per bin
      _EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_recoZPt")+sn,
			    zPt);                                                        // reco
      _EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_recoUt")+sn, 
			    recoilPt);                                                   // reco
      _EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_recoRecoilPhi")+sn,
			    recoilPhi);                                                  // reco
      _EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_DPhi_recoUt_recoZPt")+sn, 
			    phi_Z_Recoil);                                               // reco-reco
      _EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_recoUt_V_DPhi_recoUt_recoZPt")+sn,
				 phi_Z_Recoil, recoilPt);	                          // reco-reco
      
      // Fill histograms related to ET FLOW -- per bin
      _EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsUt")+sn,
			    recoilPt_cells);                                             // cells
      /*
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsScaledUt")+sn,
	recoilPt_cells_scaled);                                      // cells(scaled)
      */
      _EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsRecoilPhi")+sn,
			    recoilPhi_cells);                                            // cells
      /*
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsScaledRecoilPhi")+sn,
	recoilPhi_cells_scaled);                                     // cells(scaled)
      */
      _EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_DPhi_CellsUt_recoUt")+sn,  
			    phi_Recoil_Recoil_cells);                                     // cells-reco
      /*
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_DPhi_CellsScaledUt_recoUt")+sn,
	phi_Recoil_Recoil_cells_scaled);                              // cells(scaled)-reco
      */

      // Fill histograms related to ET FLOW -- per bin
      for(int delta_iphi=-31; delta_iphi<=32; delta_iphi++) {
	if (Et_flow_wrtRECOaxis[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	  _EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_recoZPt")+sn,
				     delta_iphi, Et_flow_wrtRECOaxis[delta_iphi]);        // cells-reco
	}
        /*
        if (Et_flow_wrtRECOaxis_scaled[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	  _EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_recoZPt")+sn,
		 		     delta_iphi, Et_flow_wrtRECOaxis_scaled[delta_iphi]); // cells(scaled)-reco
        }
        */
      }
    }

    if(_MCStudy) {
      // MC - RECO observables
      double zPt_true  = _mc_Z->Pt();
      double zPhi_true = kinem::phi(_mc_Z->Px(),_mc_Z->Py());
      double recoilPx_true = _mc_Recoil->Px();
      double recoilPy_true = _mc_Recoil->Py();
      double recoilPt_true = _mc_Recoil->Pt();
      double recoilPhi_true = kinem::phi(recoilPx_true, recoilPy_true);
    
      double recoilPtResp    = recoilPt/recoilPt_true;
      double recoilPtRespPrj = (recoilPx_true*recoilPx + recoilPy_true*recoilPy)/recoilPt_true/recoilPt_true;
      
      double phi_trueZ_Recoil = kinem::delta_phi(recoilPhi,zPhi_true);                         // reco-gen
      double phi_trueZ_trueRecoil = kinem::delta_phi(recoilPhi_true,zPhi_true);                // gen-gen
      
      // now recompute the recoil momentum from the cells, exclude 2 EM clusters
      // - raw_calcells_Recoil vector should be in principle same as the RECO one (it's computed as a cross-check)
      // - raw_calcells_Recoil_scaled vector is from rescaled cells and should be different that that from RECO
      TVector2 raw_calcells_Recoil(0., 0.);           // recoil transverse momentum from cells
      TVector2 raw_calcells_Recoil_scaled(0., 0.);    // recoil transverse momentum from cells (rescaled)
      TVector2 raw_calcells_Recoil_xcheck(0., 0.);    // recoil transverse momentum from cells (alternative)
      map<int,double> Et_flow;                        // average ET per PHI-tower in an event
      map<int,double> Et_flow_scaled;                 // average ET per PHI-tower in an event (rescaled cells)
      map<int,double>::iterator it;

      wz_utils::calc_Et_per_tower(event, emobjs, recoilPhi_true, vtx, 
				  _RelResponse_scale,
				  raw_calcells_Recoil, raw_calcells_Recoil_scaled, raw_calcells_Recoil_xcheck,
				  Et_flow, Et_flow_scaled);

      double recoilPt_cells                = raw_calcells_Recoil.Mod();
      double recoilPt_cells_scaled         = raw_calcells_Recoil_scaled.Mod();
      double recoilPtResp_cells            = recoilPt_cells/recoilPt_true;
      double recoilPtResp_cells_scaled     = recoilPt_cells_scaled/recoilPt_true;
      
      double recoilPtRespPrj_cells         = (recoilPx_true*raw_calcells_Recoil.Px() + 
					      recoilPy_true*raw_calcells_Recoil.Py())/recoilPt_true/recoilPt_true;
      double recoilPtRespPrj_cells_scaled  = (recoilPx_true*raw_calcells_Recoil_scaled.Px() + 
					      recoilPy_true*raw_calcells_Recoil_scaled.Py())/recoilPt_true/recoilPt_true;
      double recoilPtRespPrj_cells_xcheck  = (recoilPx_true*raw_calcells_Recoil_xcheck.Px() + 
					      recoilPy_true*raw_calcells_Recoil_xcheck.Py())/recoilPt_true/recoilPt_true;
      
      double recoilPhi_cells         = kinem::phi(raw_calcells_Recoil.Px(), raw_calcells_Recoil.Py());
      double recoilPhi_cells_scaled  = kinem::phi(raw_calcells_Recoil_scaled.Px(), raw_calcells_Recoil_scaled.Py());
      double recoilPhi_cells_xcheck  = kinem::phi(raw_calcells_Recoil_xcheck.Px(), raw_calcells_Recoil_xcheck.Py());
      
      double phi_trueZ_Recoil_cells        = kinem::delta_phi(raw_calcells_Recoil.Phi(),zPhi_true);
      double phi_trueZ_Recoil_cells_scaled = kinem::delta_phi(raw_calcells_Recoil_scaled.Phi(),zPhi_true);
      double phi_Recoil_Recoil_cells       = kinem::delta_phi(raw_calcells_Recoil.Phi(),recoilPhi);
      double phi_Recoil_Recoil_cells_scaled= kinem::delta_phi(raw_calcells_Recoil_scaled.Phi(),recoilPhi);
      double phi_Recoil_Recoil_cells_xcheck= kinem::delta_phi(raw_calcells_Recoil_xcheck.Phi(),recoilPhi);

      // Fill histograms based on MC / RECO recoil -- all events
      _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_genZPt", 
			    zPt_true);                                                     // gen
      _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_genUt", 
			    recoilPt_true);                                                // gen
      _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_genZPt_V_genZPt",  
				 zPt_true, zPt_true);                                      // gen
      _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_recoRecoilResp", 
			    recoilPtResp);                                                 // gen-reco
      _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_recoRecoilRespPrj", 
			    recoilPtRespPrj);                                              // gen-reco
      _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_recoRecoilResp_V_genZPt", 
				 zPt_true, recoilPtResp);                                  // gen
      _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_recoRecoilResp_V_recoZPt",
				 zPt, recoilPtResp);                                       // reco
      if ((zPt_true<35 && recoilPt<50) || (recoilPt<100)) {
	_EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_recoRecoilRespPrj_V_genZPt", 
				   zPt_true, recoilPtRespPrj);                             // gen
	_EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_recoRecoilRespPrj_V_recoZPt",
				   zPt, recoilPtRespPrj);                                  // reco
      }
      _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_DPhi_recoUt_genZPt",  
			    phi_trueZ_Recoil);                                             // reco-gen
      _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_recoUt_V_DPhi_recoUt_genZPt",
				 phi_trueZ_Recoil, recoilPt);	                           // reco-gen 
      
      // Fill histograms related to ET FLOW -- all events
      _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_CellsRecoilResp",
			    recoilPtResp_cells);                                           // cells
      /*
      _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_CellsScaledRecoilResp",
			    recoilPtResp_cells_scaled);                                    // cells(scaled)
      */
      _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_CellsRecoilRespPrj",
			    recoilPtRespPrj_cells);                                        // cells
      /*
      _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_CellsScaledRecoilRespPrj",
			    recoilPtRespPrj_cells_scaled);                                 // cells(scaled)
      _EtFlow_histos.Fill1D("ZCand2Trks_EtFlow_XCHECKrecoRecoilRespPrj",
			    recoilPtRespPrj_cells_xcheck);                          // gen-cells(reco xcheck)
      */
      _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_CellsUt_V_DPhi_CellsUt_genZPt",
				 phi_trueZ_Recoil_cells, recoilPt_cells);	            // cells-gen    
      /*
      _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_CellsScaledUt_V_DPhi_CellsScaledUt_genZPt",
				 phi_trueZ_Recoil_cells_scaled, recoilPt_cells_scaled);    // cells(scaled)-gen
      */
      for(int delta_iphi=-31; delta_iphi<=32; delta_iphi++) {
	if (Et_flow[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	  _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_genZPt",       
				     delta_iphi, Et_flow[delta_iphi]);                     // cells-gen
	  _EtFlow_histos.FillProfile2D("ZCand2Trks_EtFlow_AveEt_V_iphi_V_genZPt", delta_iphi, zPt_true, Et_flow[delta_iphi]);

	}
	/* 
        if (Et_flow_scaled[delta_iphi]<_RecoilEtFlow_studies_TowCut)
	  _EtFlow_histos.FillProfile("ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_genZPt",
				     delta_iphi, Et_flow_scaled[delta_iphi]);              // cells(scaled)-gen
	*/
      }      
      char sn[10];

      // determine the bin number for a given true PT(Z) to fill the right histograms
      const int bin_gen  = _EtFlow_histos.tprofile("ZCand2Trks_EtFlow_genZPt_V_genZPt")
	->FindBin(zPt_true)-1;                                                             // gen
      const int nbin_gen = _EtFlow_histos.tprofile("ZCand2Trks_EtFlow_genZPt_V_genZPt")
	->GetNbinsX();                                                                     // gen
      bool bingen_ok = (bin_gen>=0 && bin_gen<nbin_gen);

      // individual true PT(Z) bins
      if(bingen_ok) {

	sprintf(sn, "_genZPt_bin_%d", bin_gen);
	
	// Fill histograms based on MC / RECO recoil -- per bin
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_genZPt")+sn, 
			      zPt_true);                                                   // gen
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_recoZPt")+sn,
			      zPt);                                                        // reco
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_genUt")+sn, 
			      recoilPt_true);                                              // gen
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_recoUt")+sn, 
			      recoilPt);                                                   // reco
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_recoRecoilPhi")+sn,
			      recoilPhi);                                                  // reco
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_recoRecoilResp")+sn, 
			      recoilPtResp);                                               // gen-reco
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_recoRecoilRespPrj")+sn, 
			      recoilPtRespPrj);                                            // gen-reco
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_DPhi_recoUt_genZPt")+sn,  
			      phi_trueZ_Recoil);                                           // reco-gen
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_DPhi_recoUt_recoZPt")+sn, 
			      phi_Z_Recoil);                                               // reco-reco
	_EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_recoUt_V_DPhi_recoUt_genZPt")+sn,
				   phi_trueZ_Recoil, recoilPt);	                          // reco-gen 
	_EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_recoUt_V_DPhi_recoUt_recoZPt")+sn,
				   phi_Z_Recoil, recoilPt);	                          // reco-reco
	
	// Fill histograms related to ET FLOW -- per bin
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsUt")+sn,
			      recoilPt_cells);                                             // cells
	/*
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsScaledUt")+sn,
			      recoilPt_cells_scaled);                                      // cells(scaled)
	*/
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsRecoilPhi")+sn,
			      recoilPhi_cells);                                            // cells
	/*
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsScaledRecoilPhi")+sn,
			      recoilPhi_cells_scaled);                                     // cells(scaled)
	*/
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsRecoilResp")+sn,
			      recoilPtResp_cells);                                          // cells
	/*
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsScaledRecoilResp")+sn,
			      recoilPtResp_cells_scaled);                                   // cells(scaled)
	*/
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsRecoilRespPrj")+sn,
			      recoilPtRespPrj_cells);                                       // cells
	/*
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsScaledRecoilRespPrj")+sn,
			      recoilPtRespPrj_cells_scaled);                                // cells(scaled)
	*/
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_DPhi_CellsUt_recoUt")+sn,  
			      phi_Recoil_Recoil_cells);                                     // cells-reco
	/*
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_DPhi_CellsScaledUt_recoUt")+sn,
			      phi_Recoil_Recoil_cells_scaled);                              // cells(scaled)-reco
	*/
	_EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_CellsUt_V_DPhi_CellsUt_genZPt")+sn,
				   phi_trueZ_Recoil_cells, recoilPt_cells);                 // cells-gen    
	/*
	_EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_CellsScaledUt_V_DPhi_CellsScaledUt_genZPt")+sn,
				   phi_trueZ_Recoil_cells_scaled, recoilPt_cells_scaled);   // cells(scaled)-gen
	*/
	for(int delta_iphi=-31; delta_iphi<=32; delta_iphi++) {
	  if (Et_flow[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	    _EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_genZPt")+sn,
				       delta_iphi, Et_flow[delta_iphi]);                    // cells-gen
	  }
	  /*
          if (Et_flow_scaled[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	    _EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_genZPt")+sn,
		  		       delta_iphi, Et_flow_scaled[delta_iphi]);             // cells(scaled)-gen
          }
	  */
	}
	for(int delta_iphi=-31; delta_iphi<=32; delta_iphi++) {
	  if (Et_flow_wrtRECOaxis[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	    _EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_recoZPt")+sn,
				       delta_iphi, Et_flow_wrtRECOaxis[delta_iphi]);        // cells-gen
	  }
	  /*
          if (Et_flow_wrtRECOaxis_scaled[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	    _EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_recoZPt")+sn,
		  		       delta_iphi, Et_flow_wrtRECOaxis_scaled[delta_iphi]); // cells(scaled)-gen
          }
	  */
	}
      }

      // individual reco PT(Z) bins
      if(binsmear_ok) {

	sprintf(sn, "_bin_%d", bin_smear);

	// Fill histograms based on MC / RECO recoil -- per bin
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_genZPt")+sn, 
			      zPt_true);                                                   // gen
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_genUt")+sn, 
			      recoilPt_true);                                              // gen
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_recoRecoilResp")+sn, 
			      recoilPtResp);                                               // gen-reco
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_recoRecoilRespPrj")+sn, 
			      recoilPtRespPrj);                                            // gen-reco
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_DPhi_recoUt_genZPt")+sn,  
			      phi_trueZ_Recoil);                                           // reco-gen
	_EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_recoUt_V_DPhi_recoUt_genZPt")+sn,
				   phi_trueZ_Recoil, recoilPt);	                          // reco-gen 
	
	// Fill histograms related to ET FLOW -- per bin
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsRecoilResp")+sn,
			      recoilPtResp_cells);                                          // cells
	/*
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsScaledRecoilResp")+sn,
			      recoilPtResp_cells_scaled);                                   // cells(scaled)
	*/
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsRecoilRespPrj")+sn,
			      recoilPtRespPrj_cells);                                       // cells
	/*
	_EtFlow_histos.Fill1D(string("ZCand2Trks_EtFlow_CellsScaledRecoilRespPrj")+sn,
			      recoilPtRespPrj_cells_scaled);                                // cells(scaled)
	*/
	_EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_CellsUt_V_DPhi_CellsUt_genZPt")+sn,
				   phi_trueZ_Recoil_cells, recoilPt_cells);                 // cells-gen    
	/*
	_EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_CellsScaledUt_V_DPhi_CellsScaledUt_genZPt")+sn,
				   phi_trueZ_Recoil_cells_scaled, recoilPt_cells_scaled);   // cells(scaled)-gen
	*/
	for(int delta_iphi=-31; delta_iphi<=32; delta_iphi++) {
	  if (Et_flow[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	    _EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_genZPt")+sn,
				       delta_iphi, Et_flow[delta_iphi]);                    // cells-gen                
	  }
	  /*
	  if (Et_flow_scaled[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	    _EtFlow_histos.FillProfile(string("ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_genZPt")+sn,
				       delta_iphi, Et_flow_scaled[delta_iphi]);             // cells(scaled)-gen
          }
	  */
	}
      }
    } // end of MC studies
  } // end of Mikolaj's recoil ET-flow studies (data)
  
  // Dump measured recoil and generated Z to an ascii file
  // for events that passed kinematical cuts on 2 EM objects
  if(_MCStudy && _dumpRecoilInfo && _zee_out_recoil_txt) {
    int runNo, evtNo;
    if( event.get("run number", runNo) && event.get("event number", evtNo) ) {
      (*_zee_out_recoil_txt) << setw(8)  << runNo << " " 
			     << setw(8)  << evtNo << " " 
			     << setw(15) << setprecision(8) << _mc_Z->Px() << " " 
			     << setw(15) << setprecision(8) << _mc_Z->Py() << " " 
			     << setw(15) << setprecision(8) << _mc_Z->Pz() << " " 
			     << setw(15) << setprecision(8) << _mc_Z->E()  << " " 
			     << setw(15) << setprecision(8) << _mc_Recoil->Px() << " " 
			     << setw(15) << setprecision(8) << _mc_Recoil->Py() << " " 
			     << setw(15) << setprecision(8) << _mc_Recoil->Pz() << " " 
			     << setw(15) << setprecision(8) << _mc_Recoil->E()  << " " 
			     << setw(15) << setprecision(8) << recoilPx         << " " 
			     << setw(15) << setprecision(8) << recoilPy         << " " 
			     << setw(15) << setprecision(8) << ScalarEt_noEM    << " " 
			     << setw(15) << setprecision(8) << ScalarEt_Evt     << endl;
    }
  } 
}
 
// clear EM objects
void ZAnalysis::clear_ems(){
  _nem = 0;
  for(int iem=0; iem<2; iem++) {
    em_e[iem] = -1;
    em_rawe[iem] = -1;
    em_eta[iem] = -99.;
    em_deteta[iem] = -99.;
    em_phi[iem] = -99.;
    em_detphi[iem] = -99.;
    em_trkpt[iem] = -1.;
    em_trkphi[iem] = -99.;
    em_hm7[iem] = 99.;
    em_hm8[iem] = 99.;
  }
}

// get EM object information
bool ZAnalysis::get_ems(vector<CAFEMObj*> EMs, int solpol) {
  _nem = 2;
  for(int iem=0; iem<2; iem++) {
     em_e[iem] = EMs[iem]->E();
     em_rawe[iem] = EMs[iem]->uncorrE();
     em_pt[iem] = EMs[iem]->Pt();
     em_eta[iem] = EMs[iem]->Eta();
     em_deteta[iem] = EMs[iem]->CalDetectorEta();
     em_phi[iem] = EMs[iem]->Phi();
     em_detphi[iem] = EMs[iem]->CalDetectorPhi();
     em_hm8[iem] = EMs[iem]->HMx8();
     em_hm7[iem] = EMs[iem]->HMx7();
     if(EMs[iem]->has_spatial_track_match()) {
       em_trkpt[iem] = EMs[iem]->getPtrSpatialChp()->Pt();
       em_trkphi[iem] = EMs[iem]->getPtrSpatialChp()->Phi();
       em_trkphiEM3[iem] = EMs[iem]->TrkPhiEM3();
     }
  }
  return true;
}



void ZAnalysis::filltree3(Int_t type, Float_t vz, CAFZCand& zcand, CAFMet& met, Float_t set, 
Float_t lumi, int trig_flag, Int_t cut,  Int_t runNum, Int_t eventNum) {

  tree3_run=runNum; 	 
  tree3_evt=eventNum; 
  tree3_lumi=lumi;   

  tree3_trigflg=trig_flag;
  tree3_type=type;
  tree3_vtxz=vz;

  tree3_cut=cut;

  tree3_mee = zcand.Mass();
  tree3_ptee = zcand.Pt();
  tree3_set = set;
  tree3_zphi = zcand.Phi();
  tree3_zut = zcand.MagRecoil();
  tree3_met = met.met();
  tree3_metphi = met.metphi();

  tree3_zutphi = zcand.GetRecoil().Phi() ; 

  double zPx = zcand.Px();
  double zPy = zcand.Py();		  
  double zMetx = met.metx();
  double zMety = met.mety();
  double recoilPx = zcand.GetRecoil().Px();
  double recoilPy = zcand.GetRecoil().Py();

  TVector2 recoil_vect(recoilPx, recoilPy);
  TVector2 met_vect(zMetx, zMety);
  TVector2 z_vect(zPx, zPy);
  tree3_zutdelphi = fabs(z_vect.DeltaPhi(recoil_vect));
  tree3_metdelphi = fabs(z_vect.DeltaPhi(met_vect));

  const CAFEMObj *localemobj;
  for (Int_t i = 0; i < 2; ++i){
    localemobj = zcand.EM(i);
    tree3_e[i]= localemobj->E();
    tree3_pt[i]= localemobj->Pt();
    tree3_chg[i] = localemobj->charge();
    double emPx = localemobj->Px();
    double emPy = localemobj->Py();
    TVector2 em_vect(emPx, emPy);
    
    tree3_upara[i] = recoil_vect * (em_vect.Unit());	
    tree3_caloriphi[i] = localemobj->CalDetectorPhi();
    tree3_trkphidca[i] = localemobj->Phi();
    tree3_trkphiem3[i] = localemobj->TrkPhiEM3();  
    tree3_eta[i] = localemobj->Eta();
    tree3_deteta[i] = localemobj->CalDetectorEta();
    tree3_hm7[i] = localemobj->HMx7() ;			  
    tree3_hm8[i] = localemobj->HMx8() ;			  
    tree3_emf[i] = localemobj->emfrac();
    tree3_iso[i] = localemobj->iso()  ;		
    tree3_cc[i] = localemobj->IsCC(1.05); 
    tree3_ccphifidcal[i] = tree3_cc[i] && (localemobj->is_in_phi_fiducial()); 
    tree3_ccphifidtrk[i] = tree3_cc[i] && (localemobj->is_in_TrkPhiFid());  
    tree3_phifidcal[i] = localemobj->is_in_phi_fiducial();
    tree3_phifidtrk[i] = localemobj->is_in_TrkPhiFid();
    tree3_trkspat[i] = localemobj->has_spatial_track_match(-0.5) ;	   
    tree3_trkgood[i] = localemobj->has_good_spatial_track_match();

    tree3_id[i] = localemobj->id();
    tree3_etafid[i] = localemobj->is_in_eta_fiducial();
    tree3_ccetafid[i] =  tree3_cc[i] && localemobj->is_in_eta_fiducial();
    tree3_fid[i] = localemobj->is_in_fiducial();
    tree3_ccfid[i] = tree3_cc[i] && localemobj->is_in_fiducial();

    //changed localemobj->GetChargedTrack() to localemobj->getPtrSpatialChp() Jenny 10-17-12
    if (tree3_trkspat[i]==1 && (localemobj->getPtrSpatialChp()) ){
      tree3_trkprob[i]= localemobj->track_match_spatialchi2prob();
      tree3_trknsmt[i]= localemobj->getPtrSpatialChp()->nsmt();
      tree3_trkpt[i]= localemobj->getPtrSpatialChp()->Pt() ;
      //if(localemobj->GetChargedTrack()->nsmt() !=  localemobj->getPtrSpatialChp()->nsmt()){
      //  cout<<localemobj->GetChargedTrack()->nsmt()<<"  "<<localemobj->getPtrSpatialChp()->nsmt()<<endl;  
      //}
       //cout<<localemobj->getPtrSpatialChp()->nsmt()<<endl;
    }
    else{
      tree3_trkprob[i]=-37;
      tree3_trknsmt[i]=-37;
      tree3_trkpt[i]=-37;
    }
  }  
  _tree3->Fill();
}


bool ZAnalysis::filltree2(CAFZCand& zcand, Double_t recoilPt, Double_t zScalarEt, Double_t instlumi, Int_t runNum, Int_t eventNum, Int_t ZBrunNum, Int_t ZBeventNum) {
  tree2_ZBrunnum = ZBrunNum;
  tree2_ZBeventnum = ZBeventNum;
  tree2_runnum = runNum;
  tree2_eventnum = eventNum;
  tree2_Mz = zcand.Mass();
  tree2_Ptz = zcand.Pt();
  tree2_lumi = instlumi;
  tree2_set = zScalarEt;
  tree2_ZUt = recoilPt;
  tree2_weight = 1.;
  const CAFEMObj *localemobj;
  for (Int_t y = 0; y < 2; ++y){
    localemobj = zcand.EM(y);
    tree2em_e[y]= localemobj->E();
    tree2em_pt[y]= localemobj->Pt();
    tree2em_eta[y]= localemobj->Eta();
    tree2em_phi[y]= localemobj->Phi();
    tree2em_deteta[y]= localemobj->CalDetectorEta();
    tree2em_detphi[y]= localemobj->CalDetectorPhi();
    tree2em_upara[y]= 0.;
    tree2em_trk_prob[y]= localemobj->track_match_spatialchi2prob();
    if ((tree2em_trk_prob[y] > -0.5) && (localemobj->GetChargedTrack())){
      tree2em_nsmt[y]= localemobj->GetChargedTrack()->nsmt();
      tree2em_trk_pt[y]= localemobj->GetChargedTrack()->Pt() ;
    }
    else{
      tree2em_nsmt[y] =0;
      tree2em_trk_pt[y]=0.;
    }
    
  }
  _tree2->Fill();
  return true;
}

  
void ZAnalysis::begin() {}

void ZAnalysis::finish() {
  if(!_MCStudy) _zee_out_txt->close();
  
  if(_createRootTree) {
    _roottupleFile->Write("", TObject::kOverwrite);
    if(!_tree) delete _tree;
    if(!_roottupleFile) delete _roottupleFile;
  }

  if(_createRootTree2) {
    _roottupleFile2->Write("", TObject::kOverwrite);
    //if(!_tree2) delete _tree2;
    //if(!_roottupleFile2) delete _roottupleFile2;
    _roottupleFile2->Close();
  }

  if(_makeRecoilFile) {
    _RecoilFile->Write();
  }

  TFile *file = histfiles::initializeTFile( this );
  if(file==NULL) return;
  if(_fillztree) _tree3->Write();

  string directory_name("ZCand_Hist");
  file->mkdir(directory_name.c_str());
  _histos.save(file, directory_name);

  if(_doRatioMethod)
    _ratiomethod->terminate(file, "ZWMass");
  
  string directory_name_2("WZ_MC_Hist");
  file->mkdir(directory_name_2.c_str());
  _mc_histos.save(file, directory_name_2);

  if (_performEMFstudy) {
    string directory_name_3("ZCand_EMFstudy");
    file->mkdir(directory_name_3.c_str());
    _emf_histos.save(file, directory_name_3);
  }

  if(_do_RecoilEtFlow_studies) {
    string directory_name_4("ZCand2Trks_EtFlow_Hist");
    file->mkdir(directory_name_4.c_str());
    _EtFlow_histos.save(file, directory_name_4);
  }
  file->Close();

  if(_dumpRecoilInfo && _zee_out_recoil_txt) _zee_out_recoil_txt->close();

  if(_events_fail_trigger_requirements>0) 
    cout<<"WARNING: # of Z candidates where both electrons failed the trigger requirements is: "<<_events_fail_trigger_requirements<<endl; 
  if (_doRatioMethod)
    delete _ratiomethod;
}

ClassImp(ZAnalysis)
