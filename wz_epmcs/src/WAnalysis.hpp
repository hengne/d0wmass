#ifndef INC_WANALYSIS
#define INC_WANALYSIS

#include "PMCSEvent.hpp"
#include "EMSmear.hpp"
#include "EfficiencySmear.hpp"
#include "RecoilSmear.hpp"
#include "SETefficiencySmear_base.hpp"
#include "hist_files.hpp"
#include "PMCSWCand.hpp"

#include "TH1.h"
#include "TH2.h"
#include "TRandom3.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include <vector>

class WAnalysis {
  
 public:
  
  // Constructor/Destructor
  WAnalysis(TString parameter_filename, TRandom3* dummy);
  ~WAnalysis();

  void ReadParameters(TString parameter_filename);
  bool passesAllEffs(PMCSWCand& wcand, PMCSVtx& vtx_gen, TRandom3 *dummy, double TrigVer, bool neverUseTrack);
  void analyzeEvent(PMCSEvent& pmcsevent, TRandom3 *dummy);
  void jobSummary();
  
  std::vector<double> BreitWignerReweightMass(PMCSEvent& pmcsevent);
  std::vector<double> BreitWignerReweightWidth(PMCSEvent& pmcsevent);

  void fillWFitFile(double event_weight, double gen_mass, PMCSWCand &wcand, PMCSMet &met_gen, std::vector<PMCSEMObj> &emobjs_gen, double gen_boson_pz, PMCSEMObj &nu, double TrigVer,double recoilX_orig, double recoilY_orig, double luminosity, double vtxZ , double pdfreweights[45], PMCSEvent& pmcsevent, double SET, std::vector<PMCSEMObj>& emobjs_smear);

  // return pointeris to different smearing functions
  EMSmear *getEMSmear() const {return _emsmear;}
  EfficiencySmear *getEfficiencySmear() const {return _efficiencysmear;}
  RecoilSmear *getRecoilSmear() const {return _recoilsmear;}
  SETefficiencySmear_base *getSETefficiencySmear() const {return _SETefficiencysmear;}
  inline int getTrigSelector() { return _TrigSelector; }
 private:

  // Make U_par control plot AND DO NOT PERFORM ANY ANALYSIS
  bool _makeU_parControlPlot;

  void MakeU_parControlPlot(std::vector<PMCSEMObj>& emobjs_smear,
                                       PMCSRecoil& recoil_smear,
                                       PMCSMet& met_smear,
                                       PMCSVtx& vtx_gen,
                                       double evtweight,
                                       TRandom3 *dummy);
  
  // debug and Event counter
  bool _debug;
  int _ntotal;
  int _ngoodWCand;
  int _ngoodWCandCC;
  int _ngoodWCandEC;

  // EMSmear, EfficiencySmear, RecoilSmear
  EMSmear *_emsmear;
  RecoilSmear *_recoilsmear;
  EfficiencySmear *_efficiencysmear;
  SETefficiencySmear_base *_SETefficiencysmear;
  int _useHack;
  bool _useLumiBins;
  // output file name
  TString _wenfilename;

  //option to make ROOT file containing info for Z fit
  bool _makeROOTfile_for_WFIT;
  bool _makegenROOTfile_for_WFIT;

  // switches for ASCII printouts that can be used for more detailed studies (outside the
  // framework of wz_epmcs) of electron ID efficiency and electron energy resonse
  bool _makeASCIIfile_LumiEff;
  bool _makeASCIIfile_Eresponse;

  //for singularity variable
  bool _doSingVariableStudy;
  bool _doSVgeneratorstudy;
 
  // for reweighting
  bool _wmass_reweight, _wwidth_reweight;
  double _wmass_default, _wwidth_default;
  double _wmass_step, _wwidth_step;

  // for pdf reweighting
  bool _doPdfReweight;

  // eta cut
  double _CutEtaCC, _CutEtaEC1, _CutEtaEC2;

  // track pT cut
  double _trkpTCut;

  //phimod based on track
  bool _ApplyTrkPhiModCut;

  // True cuts on W boson variables
  double _CutTrueWPtLo, _CutTrueWPtHi, _CutTrueWPhiLo, _CutTrueWPhiHi;
  double _CutTrueWMassLo, _CutTrueWMassHi;

  // electron pT, MET and W boson Ut cut
  double _CutEPT, _CutMET, _CutWUT, _CutWUT_lower, _WMtCut1, _WMtCut2,_CutWScalarEt_lower, _CutWScalarEt;

  // Efficiency correction
  bool _WtrigEffCorrection, _WpreselEffCorrection, _WIDEffCorrection, _WtrkEffCorrection, _WElecPhiEffCorrection, _WElecPhiEffCorrectionUseDetPhi;

  // ZB Selector for triggers turned 'On'
  int _TrigSelector;

  // Apply AddOnEff for Wenu
  bool _ApplyAddOnEff_Wen;

  // Histograms
  hist_files _histos;  

  // Uparallel Correction
  bool _UseUparaOverPte;
  bool _UseCosUphi;
  bool _WUparaCorrection;

  // Uparallel Efficency Correction
  bool _PlotUparaOverPte;
  bool _PlotCosUphi;
  bool _WUparaEffCorrection;
  int _UparaEffCorrOption;
  std::vector<double> _WUparaEffParameters;
  double _W_u0_CC, _W_s_CC, _W_u0_EC, _W_s_EC,_W_seta_CC;
  bool _WUparaEffLumiDep;
  std::vector<float> _WUparaEffLumiDep_Bins;
  std::vector<float> _WUparaEffLumiDep_Slopes;
  double _W_u0pte_CC, _W_u1pte_CC, _W_spte_CC, _W_u0pte_EC, _W_spte_EC;
  double _W_u0phi_CC, _W_u1phi_CC, _W_sphi_CC, _W_u0phi_EC, _W_sphi_EC;
  bool _WUparaEffCorrectionPert;
  bool _WUparaEffCorrectionPertInterpolate;
  bool _Wpert_lumidep;
  float _Wpert_u0_CC;
  std::vector<float> _Wpert_lumibins;
  std::vector<float> _Wpert_s_CC[10];
  bool _WUparaEffCorrectionPertInterpolate2;
  bool _WpertG_lumidep;
  float _WpertG_u0_CC;
  std::vector<float> _WpertG_lumibins;
  std::vector<float> _WpertG_p_CC[10], _WpertG_s_CC[10], _WpertG_pm_CC[10], _WpertG_sm_CC[10];
  bool _WUparaEffCorrectionCDPPert;
  float _WCDPpert_u0_CC;
  std::vector<float> _WCDPpert_p_CC, _WCDPpert_s_CC;

  bool _WUparaEffCorrHengne;
  int _WUparaEffCorrHengneOption;
  TH1D* _WUparaEffCorrHengne_hUParaUPerpEFRT;
  TH1D* _WUparaEffCorrHengne_hUTUPhiEFRT;
  std::vector<double> _WUparaEffCorrHengne_3GausPars; 

  // for pT-dependent efficiencies
  bool _eff_ratios_W_includeECtag;

  // FSR photons in cracks
  bool _WsimuFSRcracks;
  float _WsimuFSRcracksWidth;

  // SET efficiency
  bool _WSETEffCorrection;
  bool _WSETEffCorrLumiSplit;
  std::vector<float> _WSETEffCorrLumiSplit_Bins;
  std::vector<float> _WSETEffCorrLumiSplit_Norm;
  bool _WSETEffCorrPedantic;
  std::vector<float> _WSETEffCorrPedanticPar;
  bool _WSETEffCorrScaled;
  float _WSETEffCorrScale;
  bool _WSETEffCorrRelative;
  bool _WSETEffCorrInterpolate;
  std::vector<float> _WSETEffCorrParameters;
  //
  int _WSETEffCorrPTEupara;
  int _WSETEffCorrPTEpert;
  std::vector<float> _WSETEffCorrPTEpertBase;
  std::vector<float> _WSETEffCorrPTEpertA;
  std::vector<float> _WSETEffCorrPTEpertB;
  std::vector<float> _WSETEffCorrPTEpertC;
  std::vector<float> _WSETEffCorrPTEpertD;
  std::vector<float> _WSETEffCorrPTEpertE;
  std::vector<float> _WSETEffCorrPTEpertF;
  std::vector<float> _WSETEffCorrPTEpertG;
  std::vector<float> _WSETEffCorrPTEpertH;
  std::vector<float> _WSETEffCorrPTEpertNorm;
  float _WSETEffCorrPTEpertRelGlobNorm;
  std::vector< std::vector< std::vector<float> > >_WSETEffCorrDataRatioParameters;
  std::vector< std::vector< std::vector<float> > >_WSETEffCorrDataRatioParameters2;
  std::vector< std::vector<float> > _WSETEffDataHackParameters;
  std::vector<float> _WSETEffCorrDataRatioPTFit;
  std::vector<float> _WSETEffCorrDataRatioLumiFit;
  //
  std::vector< std::vector<float> > _WSETEffCorrEPTEpertBase;
  std::vector< std::vector<float> > _WSETEffCorrEPTEpertA;
  std::vector< std::vector<float> > _WSETEffCorrEPTEpertB;
  std::vector< std::vector<float> > _WSETEffCorrEPTEpertC;
  std::vector< std::vector<float> > _WSETEffCorrEPTEpertD;
  std::vector< std::vector<float> > _WSETEffCorrEPTEpertE;
  std::vector< std::vector<float> > _WSETEffCorrEPTEpertF;
  std::vector< std::vector<float> > _WSETEffCorrEPTEpertG;
  std::vector< std::vector<float> > _WSETEffCorrEPTEpertH;
  std::vector< std::vector<float> > _WSETEffCorrEPTEpertNorm;

  // UT reweighting for sensitivity studies
  bool _UTreweighting;
  std::vector<float> _UTreweightingWT;

  // vary cut values and check the consistency of W mass
  bool _consistency_check, _invert_cut;
  TString _cut_under_study;
  int _runNo_lowcut, _runNo_highcut;
  float _InstLumi_lowcut, _InstLumi_highcut, _ScalarEt_lowcut, _ScalarEt_highcut, _UPara_lowcut, _UPara_highcut, _ElecEta_cut, _ElecDetEta_lowcut, _ElecDetEta_highcut, _ElecPhiMod_cut, _ElecPt_lowcut, _ElecPt_highcut, _ElecPhi_lowcut, _ElecPhi_highcut, _RecoilPhi_lowcut, _RecoilPhi_highcut;

  // write out table of average energy-leakage outside electron cone (for the recoil library method)
  bool _MakeEleakTable;
  int _NleakBins;
  double *_LeakSum, *_LeakCount;

  // photons with pT>5 GeV will be treated as EM clusters and 
  // included in final missing Et calculation
  bool _merge_fsr_photons_met;
  Int_t _ZBrunNum;
  TFile *Wfitfile;
  TTree *Wfittree;

  struct wfit_struct {
    Double_t mass_W_gen;
    Double_t tranmass_W_smear;

    Double_t elec_E;
    Double_t elec_px;
    Double_t elec_py;
    Double_t elec_pz;
    Double_t elec_deteta;
    Double_t elec_id;

    Double_t met_x;
    Double_t met_y;

    Double_t gen_W_E;
    Double_t gen_W_px;
    Double_t gen_W_py;
    Double_t gen_W_pz;

    Double_t gen_elec_E;
    Double_t gen_elec_px;
    Double_t gen_elec_py;
    Double_t gen_elec_pz;

    Double_t gen_nu_x;
    Double_t gen_nu_y;
    Double_t gen_nu_z;
    
    Double_t nu_px;
    Double_t nu_py;
    Double_t nu_pz;
    Double_t nu_deteta;
    Double_t nu_E;

    Double_t Trig_Ver;
    Double_t RecoilX;
    Double_t RecoilY;
    Double_t RecoilX_gen;
    Double_t RecoilY_gen;

    Double_t event_weight;
    
    Double_t elec_upara;
    Double_t elec_leakage;
    Double_t nu_upara;
    Double_t nu_leakage;
    Double_t elec_ZBdiff;
    Double_t nu_ZBdiff;
    Double_t lumi;
    Double_t elec_peta;
    Double_t nu_peta;
    Double_t mass_W_smear;
    Double_t vtxZ;

    Int_t nInConePh;
    Double_t xInConePh;

    Double_t SET;
    Double_t OutConePh_px;
    Double_t OutConePh_py;
    Double_t OutConePh_pz;
    Double_t OutConePh_E;

    Double_t pdfweights[45];
    Double_t massweights[100];
  } wfit_data;
}; 

#endif // INC_WANALYSIS
