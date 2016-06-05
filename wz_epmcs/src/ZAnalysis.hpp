#ifndef INC_ZANALYSIS
#define INC_ZANALYSIS

#include "PMCSEvent.hpp"
#include "EMSmear.hpp"
#include "EfficiencySmear.hpp"
#include "RecoilSmear.hpp"
#include "SETefficiencySmear_base.hpp"
#include "hist_files.hpp"
#include "PMCSZCand.hpp"
#include "PMCSVtx.hpp"

#include "TRandom3.h"
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <assert.h>
#include "TProfile.h"

class ZAnalysis {

 public:

  // Constructor/Destructor
  ZAnalysis(TString parameter_filename,TRandom3* dummy);
  ~ZAnalysis();

  void ReadParameters(TString parameter_filename);  
  std::vector<double> BreitWignerReweight(PMCSEvent& pmcsevent);
  Int_t passesUParaEff(PMCSEMObj& emobj, 
		       double upara, 
		       TRandom3 *dummy,
                       int otherpass_flag=2, 
		       double *external_upara_rnd=NULL);
  Int_t passesUParaEff(PMCSZCand& zcand, 
		       TRandom3 *dummy, 
		       double *external_upara_rnd1=NULL,
		       double *external_upara_rnd2=NULL);
  Int_t passesAllNonUParaEffs(PMCSEMObj& emobj1, 
			      PMCSEMObj& emobj2, 
			      PMCSVtx& vtx_gen, 
			      TRandom3 *dummy, 
			      double TrigVer,
			      double* externalRndm=0);
  Int_t passesAllEffs(PMCSZCand& zcand , 
		      PMCSVtx& vtx_gen, 
		      TRandom3 *dummy, 
		      double TrigVer);  
  bool passesEMCuts(vector<PMCSEMObj>& emobjs_smear, 
		    PMCSVtx& vtx_gen,
		    TRandom3 *dummy, 
		    int *Ncuts_OUT=NULL,
		    double *Trigger_Version_OUT=NULL,    // reads back Trigger_Version (0..1)
		    int *passAllNonUParaEffs_OUT=NULL,   // reads back passesAllNonUParaEffs() result
		    bool doNotEnforceMassCut=false,
		    double* externalRndm=0);
  bool passesRecoilCuts(vector<PMCSEMObj>& emobjs_smear,
			PMCSRecoil& recoil_smear,
			PMCSMet& met_smear,
			TRandom3 *dummy, 
			int *Ncuts_OUT=NULL,              // reads back the number of cuts passed
			bool *passUParaEffs_OUT=NULL,     // reads back passesUParaEffs() result
			bool skip_passUParaEffs=false,    // allow to skip U_parallel eff. corr. [TESTING ONLY!]
			double *external_upara_rnd1=NULL, // use one or both random numbers while calling
			double *external_upara_rnd2=NULL, // passesUParaEff() for individual electrons
			double *external_SET_rnd=NULL);   // used for SET efficiency
  void analyzeEvent(PMCSEvent& event, 
		    TRandom3 *dummy);
  void jobSummary(TRandom3 *dummy, long numEvents=0);
  void fillZCandHistograms(PMCSZCand &zcand, 
			   PMCSVtx &vtx_gen, 
			   std::string prefix, 
			   double evtweight,
			   int truephimodcat);
  void fillZCandRecoilHistograms(double ZpT_gen, double zphi_gen,
             double ptee_gen , double dphi_ee_gen , double zmass_gen , double deta_ee_gen ,
				 std::vector<PMCSEMObj> &emobjs_smear, std::vector<PMCSEMObj> &emobjs_gen,
				 std::vector<PMCSEMObj> &emobjs_raw_gen, PMCSRecoil &recoil_gen, 
				 PMCSZCand &zcand, 
				 std::string prefix, 
				 double evtweight, 
				 TRandom3 *dummy);
  void fillMCZHistograms(PMCSParticle &MCZ, 
			 std::string prefix, 
			 double evtweight);
  void fillTemplateRecoilHistograms(std::vector<PMCSEMObj>& emobjs_smear,
				    PMCSRecoil& recoil_gen,
				    PMCSVtx& vtx_gen,
				    TRandom3 *dummy,
				    std::string prefix,
				    double evtweight,
				    PMCSEvent& pmcsevent,
				    double *external_upara_rnd1=NULL, // use one or both random numbers while calling
				    double *external_upara_rnd2=NULL, // passesUParaEff() for individual electrons
				    double *external_SET_rnd=NULL);   // used for SET efficiency
  void TruthEffStudies(std::vector<PMCSEMObj>& emobjs_smear,
                          PMCSVtx& vtx_gen,
                          PMCSRecoil& recoil_smear,
                          PMCSMet& met_smear,
                          TRandom3* dummy);
  void TagProbeEffStudies(std::vector<PMCSEMObj>& emobjs_smear, 
			  PMCSVtx& vtx_gen, 
			  PMCSRecoil& recoil_smear, 
			  PMCSMet& met_smear, 
			  TRandom3* dummy, double evtweight);
  void TagProbeEffBIASESStudies(std::vector<PMCSEMObj>& emobjs_smear, 
			  PMCSVtx& vtx_gen, 
			  PMCSRecoil& recoil_smear, 
			  PMCSMet& met_smear, 
			  TRandom3* dummy, double evtweight);

  //
  // functions used to determine smearing parameters
  //
  void energyScaleStudy(std::vector<PMCSEMObj> &emobjs_gen, 
			PMCSVtx &vtx, 
			std::vector<PMCSEMObj> &emobjs_smear, 
			PMCSMet &met_smear, PMCSRecoil &recoil_smear,
			TRandom3 *dummy, 
			double evtweight);
  void energyScaleStudyJan(std::vector<PMCSEMObj> &emobjs_gen,
			   PMCSVtx &vtx,
			   std::vector<PMCSEMObj> &emobjs_smear,
			   PMCSMet &met_smear, PMCSRecoil &recoil_smear,
			   TRandom3 *dummy,
			    double *external_upara_rnd1, double *external_upara_rnd2, double *external_SET_rnd,
				double evtweight,
				double *externalRndmo=0);
  void energyResolutionStudy(std::vector<PMCSEMObj> &emobjs_gen, 
			     PMCSVtx &vtx, 
			     std::vector<PMCSEMObj> &emobjs_smear, 
			     PMCSMet &met_smear, 
			     TRandom3 *dummy,
			     double evtweight);
  void energyResolutionStudyJan(std::vector<PMCSEMObj> &emobjs_gen,
				PMCSVtx &vtx,
				std::vector<PMCSEMObj> &emobjs_smear,
				PMCSMet &met_smear, PMCSRecoil &recoil_smear,
				TRandom3 *dummy, double *external_upara_rnd1, double *external_upara_rnd2, double *external_SET_rnd,
				double evtweight,
				double *externalRndmo=0);

  //the following function is made following the logic of energyResolutionStudyJan(...)
  //same function can be used for making PeakShift parameter templates
  void MakeCrystalBallParameterTemplates(std::vector<PMCSEMObj> &emobjs_gen,
				PMCSVtx &vtx,
				std::vector<PMCSEMObj> &emobjs_smear,
				PMCSMet &met_smear, PMCSRecoil &recoil_smear,
				TRandom3 *dummy,
				double evtweight,
				double *externalRndmo=0);

  // RCLSA: Recoil Smearing Template Generator
  void ZHadronicRecoilBifurcateStudy(vector<PMCSEMObj> &emobjs_orig, 
				     PMCSRecoil &recoil_gen, 
				     PMCSVtx &vtx_gen,
				     TRandom3 *dummy, 
				     double evtweight,
				     double luminosity,
				     double *external_upara_rnd1=NULL,
				     double *external_upara_rnd2=NULL,
				     double *external_SET_rnd=NULL,
 				     double **external_elec_window=NULL,
				     double *extrndm_duparaeff=NULL,
				     double *externalRndm=NULL);

  void ZHadronicRecoilBifurcateProcess();

  void TransZHadronicRecoilBifurcateStudy(vector<PMCSEMObj> &emobjs_orig, 
				     PMCSRecoil &recoil_gen, 
				     PMCSVtx &vtx_gen,
				     TRandom3 *dummy, 
				     double evtweight,
				     double luminosity,
				     double *external_upara_rnd1=NULL,
				     double *external_upara_rnd2=NULL,
				     double *external_SET_rnd=NULL,
 				     double **external_elec_window=NULL,
				     double *extrndm_duparaeff=NULL,
				     double *externalRndm=NULL);

  void TransZHadronicRecoilBifurcateProcess();

  void HadronicMomentumScaleStudy(vector<PMCSEMObj> &emobjs_smear, 
				  PMCSRecoil &recoil_gen, 
				  PMCSVtx &vtx_gen,
				  TRandom3 *dummy, 
				  std::string prefix, 
				  double evtweight,
				  double *external_upara_rnd1=NULL, // use one or both random numbers while calling
				  double *external_upara_rnd2=NULL, // passesUParaEff() for individual electrons
				  double *external_SET_rnd=NULL);   // used for SET efficiency
  void HadronicMomentumResolutionStudy(std::vector<PMCSEMObj> &emobjs_smear, 
				       PMCSRecoil &recoil_gen, 
				       PMCSVtx &vtx_gen,
				       TRandom3 *dummy, 
				       std::string prefix, 
				       double evtweight,
				       double *external_upara_rnd1=NULL, // use one or both random numbers while calling
				       double *external_upara_rnd2=NULL, // passesUParaEff() for individual electrons
				       double *external_SET_rnd=NULL);   // used for SET efficiency
  void HadronicMomentumScaleBifurcateStudy(std::vector<PMCSEMObj> &emobjs_smear, 
					   PMCSRecoil &recoil_gen, 
					   PMCSVtx &vtx_gen,
					   TRandom3 *dummy, 
					   std::string prefix, 
					   double evtweight,
					   double *external_upara_rnd1=NULL, // use one or both random numbers while calling
					   double *external_upara_rnd2=NULL, // passesUParaEff() for individual electrons
					   double *external_SET_rnd=NULL);   // used for SET efficiency
  void HadronicMomentumScale2BifurcateStudy(std::vector<PMCSEMObj> &emobjs_smear, 
					    PMCSRecoil &recoil_gen, 
					    PMCSVtx &vtx_gen,
					    TRandom3 *dummy, 
					    std::string prefix, 
					    double evtweight,
					    double *external_upara_rnd1=NULL, // use one or both random numbers while calling
					    double *external_upara_rnd2=NULL, // passesUParaEff() for individual electrons
					    double *external_SET_rnd=NULL);   // used for SET efficiency
  void HadronicMomentumResolutionBifurcateStudy(std::vector<PMCSEMObj> &emobjs_smear, 
						PMCSRecoil &recoil_gen, 
						PMCSVtx &vtx_gen,
						TRandom3 *dummy, 
						std::string prefix, 
						double evtweight,
						double *external_upara_rnd1=NULL, // use one or both random numbers while calling
						double *external_upara_rnd2=NULL, // passesUParaEff() for individual electrons
						double *external_SET_rnd=NULL);   // used for SET efficiency
  void HadronicMomentumResolution2BifurcateStudy(std::vector<PMCSEMObj> &emobjs_smear, 
						 PMCSRecoil &recoil_gen, 
						 PMCSVtx &vtx_gen,
						 TRandom3 *dummy, 
						 std::string prefix, 
						 double evtweight,
						 double *external_upara_rnd1=NULL, // use one or both random numbers while calling
						 double *external_upara_rnd2=NULL, // passesUParaEff() for individual electrons
				    double *external_SET_rnd=NULL);   // used for SET efficiency
  void HadronicMomentumResolution3BifurcateStudy(std::vector<PMCSEMObj> &emobjs_smear, 
						 PMCSRecoil &recoil_gen, 
						 PMCSVtx &vtx_gen,
						 TRandom3 *dummy, 
						 std::string prefix, 
						 double evtweight,
						 double *external_upara_rnd1=NULL, // use one or both random numbers while calling
						 double *external_upara_rnd2=NULL, // passesUParaEff() for individual electrons
				    double *external_SET_rnd=NULL);   // used for SET efficiency
  void HadronicPhiSmearingBifurcateStudy(std::vector<PMCSEMObj> &emobjs_smear, 
					 PMCSRecoil &recoil_gen, 
					 PMCSVtx &vtx_gen,
					 TRandom3 *dummy, 
					 std::string prefix, 
					 double evtweight,
					 double *external_upara_rnd1=NULL, // use one or both random numbers while calling
					 double *external_upara_rnd2=NULL, // passesUParaEff() for individual electrons
					 double *external_SET_rnd=NULL);   // used for SET efficiency
  void fillZFitFile(double event_weight, 
		    double gen_mass, 
		    PMCSZCand &zcand, 
		    std::vector<PMCSEMObj> &emobjs_gen, 
		    double recoilX_orig, 
		    double recoilY_orig, 
		    double metXFromMB, 
		    double metYFromMB, 
		    double TrigVer, 
		    Int_t effs, 
                    double luminosity,
		    double vtxZ,
		    double scalaret);
  //
  // function for Jan's detector study
  //
  void fillDetectorStudyFile(double event_weight, double luminosity,
			     const PMCSParticle& genZ, 
			     const PMCSZCand& zcand,
			     const std::vector<PMCSEMObj>& emobjs_gen, 
			     const std::vector<PMCSEMObj>& emobjs_smear,
			     const PMCSMet& met_gen, 
			     const PMCSMet& met_smear,
			     const PMCSRecoil& recoil_gen, 
			     const PMCSRecoil& recoil_smear,
			     const PMCSVtx& vtx_gen);
  //
  // return pointeris to different smearing functions
  //

  void  TBStudy(vector<PMCSEMObj>& emobjs_orig,  PMCSRecoil recoil_smear, TRandom3 *dummy, double *external_upara_rnd1, double *external_upara_rnd2, double *external_SET_rnd, double evtweight, double luminosity, PMCSVtx& vtx_gen,double * externalRndmo );

  void momentumScaleStudy(vector<PMCSEMObj> &emobjs_gen,  vector<PMCSEMObj> &emobjs_smear,TRandom3 *dummy, double evtweight);
  
  void radLengthStudy(vector<PMCSEMObj> &emobjs_gen,  vector<PMCSEMObj> &emobjs_smear,TRandom3 *dummy, double evtweight);

  bool filltree2(PMCSZCand& zcand, Double_t vz, Double_t zScalarEt, Int_t runNum, Int_t eventNum, double weight, int type);

  EMSmear *getEMSmear() const {return _emsmear;}
  EfficiencySmear *getEfficiencySmear() const {return _efficiencysmear;}
  RecoilSmear *getRecoilSmear() const {return _recoilsmear;}
  SETefficiencySmear_base *getSETefficiencySmear() const {return _SETefficiencysmear;}
  //
  // public methods for MINUIT mode
  //
  bool MINUIT_skipPreselection();
  double MINUIT_calc_chi2( double raw_scale_HAD_bifurcate_A,
			   double raw_scale_HAD_bifurcate_B,
			   double raw_scale_HAD_bifurcate_Tau,
			   double raw_Relsampling_HAD_bifurcate_A,
			   double raw_Relsampling_HAD_bifurcate_B,
			   double raw_Relconst_HAD_bifurcate,
			   double raw_Reltrans_HAD_RelRespTrans,
			   double raw_Reltrans_HAD_RelResnTrans, 
			   double raw_Reltrans_HAD_RelTauTrans,
			   double raw_Relphi_HAD_bifurcate_A,
			   double raw_Relphi_HAD_bifurcate_B,
			   double raw_RelconstPhi_HAD_bifurcate,
			   double raw_alpha_mb,
			   double raw_alpha_zb );

private:


  // Make U_par control plot AND DO NOT PERFORM ANY ANALYSIS                                                                                          
  bool _makeU_parControlPlot;
  bool _makeU_parControlPlot_RequestBothPtCut; // if request both elec. pass PT cuts before filling any plots? 

  void MakeU_parControlPlot(std::vector<PMCSEMObj>& emobjs_smear,
                            PMCSRecoil& recoil_smear,
                            PMCSMet& met_smear,
                            PMCSVtx& vtx_gen,
                            double evtweight,
                            TRandom3 *dummy);

  // output file name
  TString _zeefilename;

  // Apply TB correction
  bool _Top_Bottom_Effect_Correction;
  
  // TB Correction Option 
  int _TB_Correction_Option;

  //Apply Recoil Phi asymmetry after UPara corrections
  bool _Top_Bottom_Apply_Last;


  //Apply Recoil Phi asymmetry to Hard Recoil Only
  bool _TBPhi_response_Hard_Only;

  //Apply Recoil Phi asymmetry to Soft Recoil Only
  bool _TBPhi_response_Soft_Only;
 
  //option to make ROOT file containing info for Z fit
  bool _makeROOTfile_for_ZFIT;
  bool _makegenROOTfile_for_ZFIT;

  //option to make ASCII file for detector studies
  bool _makeASCIIfile_for_detector;
  std::fstream* _theASCIIfile;

  // switches for ASCII printouts that can be used for more detailed studies (outside the
  // framework of wz_epmcs) of electron ID efficiency and electron energy resonse
  bool _makeASCIIfile_LumiEff;
  bool _makeASCIIfile_Eresponse;

  //should we make Z generator-level plots?
  bool _makeZGenPlots;

  // debug and Event counter
  bool _debug;
  int _ntotal ;

  // use tag-probe method to study efficiencies
  bool _StudyEfficiencies;
  bool _StudyEfficiencyBIASES;

  //
  bool _StudyEfficienciesTruth;
  int _TruthMode;

  bool _phimodcut, _StudyPhiMod, _ApplyTrkPhiModCut;

  bool _etaImbalance_perbincuts;
  std::vector<float> _EtaImbalanceCutLow;
  std::vector<float> _EtaImbalanceCutHigh;
  bool _InvertetaImbalance_perbincuts;
  
  // EMSmear, EfficiencySmear, RecoilSmear
  EMSmear *_emsmear;
  EfficiencySmear *_efficiencysmear;
  RecoilSmear *_recoilsmear;
  SETefficiencySmear_base *_SETefficiencysmear;

  // Efficiency correction
  bool _ZtrigEffCorrection, _ZpreselEffCorrection, _ZIDEffCorrection, _ZElecPhiEffCorrection, _ZElecPhiEffCorrectionUseDetPhi;

  //Trigger version tracker;
  int _TrigSelector;

  // for pT-dependent efficiencies
  bool _eff_ratios_Z_includeECtag;

  // # of electrons with track matching
  int _NZTrkMatch;
  int _NZpreselTrkMatch;

  // Apply AddOnEff for Zee
  bool _ApplyAddOnEff_Zee;

  // track pT cut
  double _trkpTCut;

  // electron and Z boson Ut cut
  double _CutEPT1_lo,_CutEPT1_hi,_CutEPT2_lo,_CutEPT2_hi;
  double _CutZUT, _CutZUT_lower;
  double _CutZPT, _CutZPT_lower;
  double _CutZPhi, _CutZPhi_lower;
  double _CutZScalarEt, _CutZScalarEt_lower;

  // eta cut
  double _CutEtaCC, _CutEtaEC1, _CutEtaEC2;

  // z mass cut
  double _ZMassCut1, _ZMassCut2;

  // for reweighting
  bool _zmass_reweight, _zmass_elecpt_reweight;
  double _zmass_default, _zwidth_default;
  double _zmass_step;

  // uparallel correction
  bool _UseUparaOverPte;
  bool _UseCosUphi;
  bool _ZUparaCorrection;
  
  //uparallel efficiency correction
  bool _PlotUparaOverPte;
  bool _PlotCosUphi;
  bool _ZUparaEffCorrection;
  int _UparaEffCorrOption;
  std::vector<double> _ZUparaEffParameters;
  double _Z_u0_CC, _Z_s_CC, _Z_u0_EC, _Z_s_EC;
  double _Z_u0pte_CC, _Z_u1pte_CC, _Z_spte_CC, _Z_u0pte_EC, _Z_spte_EC;
  double _Z_u0phi_CC, _Z_u1phi_CC, _Z_sphi_CC, _Z_u0phi_EC, _Z_sphi_EC;

  bool _ZUparaEffCorrHengne;
  int _ZUparaEffCorrHengneOption;
  TH1D* _ZUparaEffCorrHengne_hUParaUPerpEFRT;
  TH1D* _ZUparaEffCorrHengne_hUTUPhiEFRT;
  std::vector<double> _ZUparaEffCorrHengne_Opt2Pars;

  // FSR photons in cracks
  bool _ZsimuFSRcracks;
  float _ZsimuFSRcracksWidth;

  // vary cut values and check the consistency of W mass
  bool _consistency_check, _invert_cut;
  TString _cut_under_study;
  int _runNo_lowcut, _runNo_highcut;
  float _InstLumi_lowcut, _InstLumi_highcut, _ScalarEt_lowcut, _ScalarEt_highcut, _UPara_lowcut, _UPara_highcut, _ElecEta_cut, _ElecDetEta_lowcut, _ElecDetEta_highcut, _ElecPhiMod_cut, _ElecPt_lowcut, _ElecPt_highcut, _ElecPhi_lowcut, _ElecPhi_highcut, _RecoilPhi_lowcut, _RecoilPhi_highcut;
  int _DetEtaCateg_cut;

  // SET efficiency
  bool _ZSETEffCorrection;
  bool _ZSETEffCorrLumiSplit;
  std::vector<float> _ZSETEffCorrLumiSplit_Bins;
  std::vector<float> _ZSETEffCorrLumiSplit_NormCCCC;
  std::vector<float> _ZSETEffCorrLumiSplit_NormCCEC;
  std::vector<float> _ZSETEffCorrLumiSplit_NormECEC;
  bool _ZSETEffCorrScaled;
  float _ZSETEffCorrScale;
  bool _ZSETEffCorrRelative;
  bool _ZSETEffCorrInterpolate;
  std::vector<float> _ZSETEffCorrParametersCCCC;
  std::vector<float> _ZSETEffCorrParametersCCEC;
  std::vector<float> _ZSETEffCorrParametersECEC;
  //
  int _ZSETEffCorrPTEupara;
  int _ZSETEffCorrPTEpert;
  //
  std::vector<float> _ZSETEffCorrPTEpertBase;
  std::vector<float> _ZSETEffCorrPTEpertA;
  std::vector<float> _ZSETEffCorrPTEpertB;
  std::vector<float> _ZSETEffCorrPTEpertC;
  std::vector<float> _ZSETEffCorrPTEpertD;
  std::vector<float> _ZSETEffCorrPTEpertE;
  std::vector<float> _ZSETEffCorrPTEpertF;
  std::vector<float> _ZSETEffCorrPTEpertG;
  std::vector<float> _ZSETEffCorrPTEpertH;
  std::vector<float> _ZSETEffCorrPTEpertNorm;
  std::vector< std::vector< std::vector<float> > > _ZSETEffCorrDataRatioParameters;
  std::vector< std::vector< std::vector<float> > > _ZSETEffCorrDataRatioParameters2;
  std::vector< std::vector<float> > _ZSETEffDataHackParameters;
  std::vector<float> _ZSETEffCorrDataRatioPTFit;
  std::vector<float> _ZSETEffCorrDataRatioLumiFit;
  //
  float _ZSETEffCorrPTEpertRelGlobNorm;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertBase;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertA;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertB;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertD;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertE;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertF;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertG;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertH;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertNorm;
  std::vector<float> _ZSETEffCorrEPTEparamsNorm_CommonMultiplier;
  //
  int _useHack;
  bool _useLumiBins;
  //
  std::vector<float> _ZSETEffCorrPTEpertBase_EC;
  std::vector<float> _ZSETEffCorrPTEpertA_EC;
  std::vector<float> _ZSETEffCorrPTEpertB_EC;
  std::vector<float> _ZSETEffCorrPTEpertC_EC;
  std::vector<float> _ZSETEffCorrPTEpertD_EC;
  std::vector<float> _ZSETEffCorrPTEpertE_EC;
  std::vector<float> _ZSETEffCorrPTEpertF_EC;
  std::vector<float> _ZSETEffCorrPTEpertG_EC;
  std::vector<float> _ZSETEffCorrPTEpertH_EC;
  std::vector<float> _ZSETEffCorrPTEpertNorm_EC;
  //
  float _ZSETEffCorrPTEpertRelGlobNorm_EC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertBase_EC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertA_EC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertB_EC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertC_EC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertD_EC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertE_EC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertF_EC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertG_EC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertH_EC;
  std::vector< std::vector<float> > _ZSETEffCorrEPTEpertNorm_EC;

  // write out Z boson recoil pT into a text file
  bool _make_recoil_file;
  std::fstream* _RecoilPtASCIIfile;

  // write out table of average energy-leakage outside electron cone (for the recoil library method)
  bool _MakeEleakTable;
  int _NleakBins;
  double _overallLeakSum;
  int _overallLeakCount;
  double *_LeakSum, *_LeakCount;



  // determine Top Bottom Asymmetry
  bool _TBStudy;
  double _tbalpha_center;
  double _tbbeta_center;
  double _tbalpha_step;
  double _tbbeta_step;
  int _Bins_TBStudy;
  
  // determine EC Track Smearing parameters
  bool _momentumScaleStudy;
  int _Bins_CCMSStudy;
  double _CCMScenterA;
  double _CCMSstepA;
  double _CCMScenterB;
  double _CCMSstepB;
  double _CCMScenterC;
  double _CCMSstepC;

  // determine EC Track Smearing parameters
  int _Bins_ECMSStudy;
  double _ECMScenterA;
  double _ECMSstepA;
  double _ECMScenterB;
  double _ECMSstepB;
  double _ECMScenterC;
  double _ECMSstepC;
  bool _study_AB;

  // determine track rad length;
  bool _radLengthStudy;
  int _Bins_radLengthStudy_CC;
  double _radLengthcenter_CC;
  double _radLengthstep_CC;

  // determine track rad length;
  bool _radLengthStudy_EC;
  int _Bins_radLengthStudy_EC;
  double _radLengthcenter_EC;
  double _radLengthstep_EC;

  //  use fresh random numbers to evaluate UParaEffs
  bool _pedanticRandomRecoil;
  bool _pedanticRandomEM;

  // determine electron energy scale
  bool _EnergyScaleStudy;
  bool _EnergyScaleStudyJan;
  bool _EnergyScaleStudyJanPedantic;
  bool _StudyCCScale;
  double _scale_center;
  double _offset_center;
  double _scale_step;
  double _offset_step;
  int _Bins_ScaleStudy;

  // determine electron energy resolution
  bool _EnergyResolutionStudy;
  bool _EnergyResolutionStudyJan;
  bool _EnergyResolutionStudyJanPedantic;
  bool _StudyCCResolution;
  bool _SkipSampling;
  bool _SkipConstant;
  double _sampling_center;
  double _constant_center;
  double _sampling_step;
  double _constant_step;
  int _Bins_ResolutionStudy;
  TH1D **_hZBLibBin0_etabinz;
  double _enoise_center;
  double _enoise_step;
  bool _SkipeNoise;

  // determine Crystal Ball parameters for electron energy resolution near phi-cracks
  // (
  //  same functionality can be used to determine peak shift parameters near phi-cracks
  //  in that case "alpha" would really mean "PeakShift" --
  //  corresponding piece of code exists in void EMSmear::SmearEnergy(double energy,...),
  //  and can be turned on if needed, currently it is commented out
  // ) 
  bool _MakeCrackCBtemplates         ;
  double _CrackCB_alphaOffset_center ;
  double _CrackCB_alphaSlope_center  ;
  double _CrackCB_alphaOffset_step   ;
  double _CrackCB_alphaSlope_step    ;
  int _Bins_MakeCrackCBtemplates     ;

  // RCLSA: (Trans) Recoil Smearing Template Variables 
  double***** trans_eta_imbalance_x;
  double***** trans_eta_imbalance_x2;
  double***** trans_evt_weight;
  double***** trans_evt_weight_2;
  bool _TransZHadronicRecoilBifurcateStudy;
  std::vector<int> _TransZRecoilBifurcateBins;
  std::vector<double> _TransZRecoilBifurcateStep;
  struct TransZRecoilBifurcateOutputStruct {
    int zpt;
    double eta_imbalance_mean;
    double eta_imbalance_rms;
    double resptrans;
    double resntrans;
    double tautrans;
    double alpha_mb_trans;
    double evt_weight;
    double evt_weight_2;
  } TransZRecoilBifurcateOutputData;


  // RCLSA: Recoil Smearing Template Variables 
  double********* eta_imbalance_x;

 double********* eta_imbalance_x_1;
 double********* eta_imbalance_x_2;
 double********* eta_imbalance_x_3;
 double********* eta_imbalance_x_4;
 double********* eta_imbalance_x_5;
 double********* eta_imbalance_x_6;
 double********* eta_imbalance_x_7;
 double********* eta_imbalance_x_8;
 double********* eta_imbalance_x_9;
 double********* eta_imbalance_x_10;

 double********* eta_imbalance_x_1_evtsq;
 double********* eta_imbalance_x_2_evtsq;
 double********* eta_imbalance_x_3_evtsq;
 double********* eta_imbalance_x_4_evtsq;
 double********* eta_imbalance_x_5_evtsq;
 double********* eta_imbalance_x_6_evtsq;
 double********* eta_imbalance_x_7_evtsq;
 double********* eta_imbalance_x_8_evtsq;
 double********* eta_imbalance_x_9_evtsq;
 double********* eta_imbalance_x_10_evtsq;

  double********* eta_imbalance_x2;
  double********* delta_phi_x;
  double********* delta_phi_x2;
  double********* evt_weight;
  double********* evt_weight_2;
  TTree* ZRecoilBifurcateOutputTree; 
  TFile* ZRecoilBifurcateFile;
  TString _ZRecoilBifurcateFile;
  bool _ZHadronicRecoilBifurcateStudy;
  bool _ZRecoilEtaCuts;
  int _ZRecoilDebugLevel;
  std::vector<double> _ZRecoilEtaCutLow;
  std::vector<double> _ZRecoilEtaCutHigh;
  std::vector<int> _ZRecoilBifurcateBins;
  std::vector<double> _ZRecoilBifurcateStep;
  struct ZRecoilBifurcateOutputStruct {
    int zpt;
    double eta_imbalance_mean;
    double eta_imbalance_rms;
    double delta_phi_mean;
    double delta_phi_rms;
    double scale_a;
    double scale_b;
    double tau_had;
    double resolution_a;
    double resolution_b;
    double alpha_mb;
    double phi_a;
    double phi_b;
    double evt_weight;
    double evt_weight_2;
    double eta_imbalance_bin1;
    double eta_imbalance_bin2;
    double eta_imbalance_bin3;
    double eta_imbalance_bin4;
    double eta_imbalance_bin5;
    double eta_imbalance_bin6;
    double eta_imbalance_bin7;
    double eta_imbalance_bin8;
    double eta_imbalance_bin9;
    double eta_imbalance_bin10;

    double eta_imbalance_evtsq_bin1;
    double eta_imbalance_evtsq_bin2;
    double eta_imbalance_evtsq_bin3;
    double eta_imbalance_evtsq_bin4;
    double eta_imbalance_evtsq_bin5;
    double eta_imbalance_evtsq_bin6;
    double eta_imbalance_evtsq_bin7;
    double eta_imbalance_evtsq_bin8;
    double eta_imbalance_evtsq_bin9;
    double eta_imbalance_evtsq_bin10;

  } ZRecoilBifurcateOutputData;


  // determine hadronic momentum scale
  bool _HadronicMomentumScaleStudy;
  double _scale_HAD_A_center;
  double _scale_HAD_B_center;
  double _scale_HAD_A_step;
  double _scale_HAD_B_step;
  int _Bins_HadronicScaleStudy;

  // determine hadronic momentum sampling and # of minbias events to overlay
  bool _HadronicMomentumResolutionStudy;
  double _sampling_HAD_center;
  double _alpha_mb_center;
  double _sampling_HAD_step;
  double _alpha_mb_step;
  int _Bins_HadronicResolutionStudy;

  // determine hadronic momentum scale for bifurcate method
  bool _HadronicMomentumScaleBifurcateStudy;
  double _scale_HAD_bifurcate_A_center;
  double _scale_HAD_bifurcate_B_center;
  double _scale_HAD_bifurcate_A_step;
  double _scale_HAD_bifurcate_B_step;
  int _Bins_HadronicScaleBifurcateStudy;

  // determine hadronic momentum scale for bifurcate method
  bool _HadronicMomentumScale2BifurcateStudy;
  double _scale_HAD_bifurcate2_A_center;
  double _scale_HAD_bifurcate2_B_center;
  double _scale_HAD_bifurcate2_Tau_center;
  double _scale_HAD_bifurcate2_A_step;
  double _scale_HAD_bifurcate2_B_step;
  double _scale_HAD_bifurcate2_Tau_step;
  int _Bins_HadronicScale2BifurcateStudy;

  // determine hadronic momentum resolution for bifurcate method (for hard component only)
  bool _HadronicMomentumResolutionBifurcateStudy;
  double _Relsampling_HAD_bifurcate_A_center;
  double _Relsampling_HAD_bifurcate_B_center;
  double _Relsampling_HAD_bifurcate_A_step;
  double _Relsampling_HAD_bifurcate_B_step;
  int _Bins_HadronicResolutionBifurcateStudy;

  // determine hadronic momentum resolution for bifurcate method (for hard and soft components)
  bool _HadronicMomentumResolution2BifurcateStudy;
  double _Relsampling_HAD_bifurcate2_A_center;
  double _alpha_mb2_center;
  double _Relsampling_HAD_bifurcate2_A_step;
  double _alpha_mb2_step;
  int _Bins_HadronicResolution2BifurcateStudy;

  // determine hadronic momentum resolution for bifurcate method (for hard and soft components)
  bool _HadronicMomentumResolution3BifurcateStudy;
  double _Relsampling_HAD_bifurcate3_A_center;
  double _Relsampling_HAD_bifurcate3_B_center;
  double _alpha_mb3_center;
  double _Relsampling_HAD_bifurcate3_A_step;
  double _Relsampling_HAD_bifurcate3_B_step;
  double _alpha_mb3_step;
  int _Bins_HadronicResolution3BifurcateStudy;

  // determine hadronic momentum scale for bifurcate method
  bool _HadronicPhiSmearingBifurcateStudy;
  double _Relphi_HAD_bifurcate_A_center;
  double _Relphi_HAD_bifurcate_B_center;
  double _Relphi_HAD_bifurcate_A_step;
  double _Relphi_HAD_bifurcate_B_step;
  int _Bins_HadronicPhiSmearingBifurcateStudy;

  // pre-selected events for 7-dim MINUIT fit
  bool _HadronicMomentum_AllAtOnce_BifurcateStudy;
  TString _Zminuit_ProgressReport_FileName;        // name of the text file with MINUIT progress history
  TString _Zminuit_EventBuffer_FileName;           // name of the binary file with pre-selected events
  FILE *_Zminuit_EventBuffer_File;                 // pointer to a binary file stream
  int _Zminuit_EventBuffer_Nevts;                  // number of pre-selected events to reprocess
  TString _Zminuit_Reference_FileName;             // name of the ROOT filr with reference histograms
  TString _Zminuit_Reference_Dir;                  // reference ROOT file directory
  TString _Zminuit_Reference_Prefix_Phi;           // reference histogram name (prefix) for Phi Resolution
  TString _Zminuit_Reference_Prefix_EtaImbalance;  // reference histogram name (prefix) for Eta Imbalance
  TString _Zminuit_Reference_Prefix_XiImbalance;   // reference histogram name (prefix) for Xi Imbalance
  int _Zminuit_ChiSquare_Method;                   // method of calculating a total CHI**2
  bool _Zminuit_Skip_Znunu_Randomization;          // skip randomizing the hard recoil from Z->nunu MC in every event?
  bool _Zminuit_Skip_Event_Preselection;           // skip event pre-selection and use an existing event buffer file?
  bool _Zminuit_Skip_UParaEfficiency;              // skip passesUParaEff() during MINUIT reporcessing part?
  bool _Zminuit_Skip_UParaEfficiency_Randomization;// skip randomizing U_parallel corr. eff. during MINUIT reporcessing part?
  bool _Zminuit_Skip_Event_Reprocessing;           // stop after event preselection and skip MINUIT part? 
  bool _Zminuit_UseRAM;                            // store all pre-selected events in RAM memory?
  char *_Zminuit_RAMBuffer;                        // a memory buffer used when Zminuit_UseRAM=TRUE
  int _Zminuit_RAMBuffer_Nevts;                    // a number of events stored in this memory buffer
  int _Zminuit_RAMBuffer_Ready;                    // will be set to TRUE once all events are transferred from a file to RAM
  TRandom3 *_Zminuit_TRandom3;                     // pointer to current RND generator
  int _Zminuit_Npar;                               // total number of declared parameters
  double _Zminuit_START_Relscale_A;
  double _Zminuit_START_Relscale_B;
  double _Zminuit_START_Relsampling_A;
  double _Zminuit_START_Relsampling_B;
  double _Zminuit_START_Relphi_A;
  double _Zminuit_START_Relphi_B;
  double _Zminuit_START_Alpha_MB;
  bool _Zminuit_RANGE_Unlimited; // if TRUE, then all parameters with RangeMin=RangeMax will be treated as fixed
                                 // and all remaining parameters with RangeMin<RangeMax will be floating but unlimited.
  std::vector<bool>   _Zminuit_ParIsFixed;
  std::vector<double> _Zminuit_ParStepSize;
  std::vector<double> _Zminuit_RANGE_Relscale_A;
  std::vector<double> _Zminuit_RANGE_Relscale_B;
  std::vector<double> _Zminuit_RANGE_Relsampling_A;
  std::vector<double> _Zminuit_RANGE_Relsampling_B;
  std::vector<double> _Zminuit_RANGE_Relphi_A;
  std::vector<double> _Zminuit_RANGE_Relphi_B;
  std::vector<double> _Zminuit_RANGE_Alpha_MB;
  double _Zminuit_STEP_Relscale_A;
  double _Zminuit_STEP_Relscale_B;
  double _Zminuit_STEP_Relsampling_A;
  double _Zminuit_STEP_Relsampling_B;
  double _Zminuit_STEP_Relphi_A;
  double _Zminuit_STEP_Relphi_B;
  double _Zminuit_STEP_Alpha_MB;

  bool   _Zminuit_do_SCAN;            // perform scan of a single parameter ?
  int    _Zminuit_do_SCAN_IPAR;       // parameter to be scanned: 0=RelScaleA, 1=RelScaleB, ...
  int    _Zminuit_do_SCAN_NSTEPS;     // number of steps for the scan (>=2)
  bool   _Zminuit_do_SEEK;            // perform random seek inside the hypercube?
  bool   _Zminuit_do_SEEK_RndStart;   // use a random starting point rather than START value?
  int    _Zminuit_do_SEEK_NITER;      // approximate number of steps for this random seek
  int    _Zminuit_do_SEEK_NEVENTS;    // max. number of events to be used during this random seek
  bool   _Zminuit_do_SIMPLEX;         // use SIMPLEX method? 
  int    _Zminuit_do_SIMPLEX_NITER;   // approximate number of steps for the SIMPLEX method
  double _Zminuit_do_SIMPLEX_TOLER;   // tolerance parameter of the SIMPLEX method
  bool   _Zminuit_do_MINIMIZE;        // use MINIMIZE (MIGRAD+SIMPLEX) method?
  int    _Zminuit_do_MINIMIZE_NITER;  // approximate number of steps for the MINIMIZE method
  double _Zminuit_do_MINIMIZE_TOLER;  // tolerance parameter of the MINIMIZE method
  double _Zminuit_do_MINIMIZE_EPS;    // (machine) precision for FCN
  bool   _Zminuit_do_MINOS;           // call MINOS after MIGRAD?
  int    _Zminuit_do_MINOS_NITER;     // approximate number of steps for MINOS
  bool   _Zminuit_UseGradient;        // also compute derivatives at each MINUIT step?
  bool   _Zminuit_UseFittedMeanWidth; // use fitted or plain means and widths of imbalance distributions? 
  bool   _Zminuit_UseAbsDeltaPhiImbal;// use |Phi(Recoil)-Phi(Z)| or Phi(Recoil)-Phi(Z) for phi-imbalance?
  bool   _Zminuit_UseMasterSlaveMode; // split CHI2 calculation into N jobs ?
  int    _Zminuit_MasterSlave_Njobs;  // total number of jobs
  int    _Zminuit_MasterSlave_Job;    // this job number (1=master)
  TString _Zminuit_MasterSlave_REQ;   // master's request file
  TString _Zminuit_MasterSlave_ACK_prefix;   // slave's acknowledge file
  TString _Zminuit_MasterSlave_START; // master's request file
  TString _Zminuit_MasterSlave_QUIT;  // master's quit file
  TString _Zminuit_MasterSlave_DONE_prefix;  // slave's acknowledge file
  TString _Zminuit_MasterSlave_RESULT_prefix;// slave's rootuple file
public:  
  //
  // public methods for MINUIT mode
  //
  inline bool MINUIT_UseGradient() { return _Zminuit_UseGradient; }
  inline bool MINUIT_ParIsFixed(int ipar) { return _Zminuit_ParIsFixed.at(ipar); }
  inline double MINUIT_ParStepSize(int ipar) { return _Zminuit_ParStepSize.at(ipar); }
  inline int MINUIT_getNpar() { return _Zminuit_Npar; }
  inline int getTrigSelector() { return _TrigSelector; }
private:
  //
  // private methods for MINUIT mode
  //
  void MINUIT_reprocess(int maxevts, TRandom3 *dummy);
  TRandom3 *MINUIT_getTRandom3();
  void MINUIT_setTRandom3(TRandom3 *dummy);
  void MINUIT_setNevts(int nevts);
  inline void MINUIT_setNpar(int npar) { _Zminuit_Npar=npar; }
  int MINUIT_getNevts();
  void MINUIT_getClassPointer(ZAnalysis* &ptr); 
  int MINUIT_WriteRAM(char *buffer,
		      std::vector<PMCSEMObj> &emobjs_smear, 
		      PMCSRecoil &recoil_gen, 
		      PMCSVtx &vtx_gen, 
		      double &evtweight,
		      double &luminosity, 
		      int &runno, 
		      int &zbindex, 
		      int &mbindex, 
		      double &pt_resol, 
		      double &delta_phi,
		      double &upara_rnd1,
		      double &upara_rnd2,
		      double &SET_rnd, 
		      double &znunu_SET_Hard, 
		      double &znunu_SET_Hard_expected,
                      double &given_tbdmetx,
                      double &given_tbdmety);
  int MINUIT_ReadRAM(char *buffer,
		     std::vector<PMCSEMObj> &emobjs_smear, 
		     PMCSRecoil &recoil_gen, 
		     PMCSVtx &vtx_gen, 
		     double &evtweight,
		     double &luminosity, 
		     int &runno, 
		     int &zbindex, 
		     int &mbindex, 
		     double &pt_resol, 
		     double &delta_phi,
		     double &upara_rnd1,
		     double &upara_rnd2,
		     double &SET_rnd, 
		     double &znunu_SET_Hard, 
		     double &znunu_SET_Hard_expected,
                     double &given_tbdmetx,
                     double &given_tbdmety);
  int MINUIT_WriteFile(std::vector<PMCSEMObj> &emobjs_smear, 
		       PMCSRecoil &recoil_gen, 
		       PMCSVtx &vtx_gen, 
		       double &evtweight,
		       double &luminosity, 
		       int &runno, 
		       int &zbindex, 
		       int &mbindex, 
		       double &pt_resol, 
		       double &delta_phi,
		       double &upara_rnd1,
		       double &upara_rnd2,
		       double &SET_rnd, 
		       double &znunu_SET_Hard, 
		       double &znunu_SET_Hard_expected,
		       double &given_tbdmetx,
		       double &given_tbdmety);
  int MINUIT_ReadFile(std::vector<PMCSEMObj> &emobjs_smear, 
		      PMCSRecoil &recoil_gen, 
		      PMCSVtx &vtx_gen, 
		      double &evtweight,
		      double &luminosity, 
		      int &runno, 
		      int &zbindex, 
		      int &mbindex, 
		      double &pt_resol, 
		      double &delta_phi,
		      double &upara_rnd1,
		      double &upara_rnd2,
		      double &SET_rnd, 
		      double &znunu_SET_Hard, 
		      double &znunu_SET_Hard_expected,
                      double &given_tbdmetx,
                      double &given_tbdmety);

  // do template histograms for hadronic studies
  enum HadronicTemplateType { _NONE_ = 0,
			      _MOMENTUM_SCALE_,
			      _MOMENTUM_RESOLUTION_,
			      _MOMENTUM_SCALE_BIFURCATE_,
			      _MOMENTUM_SCALE_BIFURCATE2_,
			      _MOMENTUM_RESOLUTION_BIFURCATE_,
			      _MOMENTUM_RESOLUTION_BIFURCATE2_,
			      _MOMENTUM_RESOLUTION_BIFURCATE3_,
			      _PHI_SMEARING_BIFURCATE_,
                              _MOMENTUM_ALL_AT_ONCE_BIFURCATE_}
    _HadronicTemplateNumber;

  //study fz
  bool _doFzStudy;

  //Overlay event List
  Bool_t _MakeOverlayEventList;

  Int_t _ZBrunNum;
  Int_t _ZBevtNum;

  // ZB runNum evtNum tree
  bool _FillZBRunNumTree;
  TFile* _ZBRunNumFile;
  TTree* _ZBRunNumTree;

       // write out information into a different  tree
  bool _createRootTree2;
  TFile *_roottupleFile2;
  TTree *_tree2;

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
  Int_t tree2em_trk_prob[2];
  Int_t tree2em_trk_probtight[2];
  Int_t tree2em_trk_set[2];
  Int_t tree2em_trk_upara[2];
  Int_t tree2em_nsmt[2];
  Float_t tree2em_trk_pt[2];
  Int_t tree2em_hmX[2];
  Int_t tree2em_trk_trig[2];
  Float_t tree2_weight;
  Int_t tree2_passesnonuparaeff;
  Int_t tree2_type;
  Float_t tree2_vtxz;
  Float_t tree2em_trkphiem3[2];

  Int_t tree2em_trk_presel[2];
  Int_t tree2em_trk_addon[2];
  Int_t tree2em_cc[2];
  Int_t tree2em_fid[2];

  // Histograms
  hist_files _histos;
  hist_files _histoszbif;

  TFile *Zfitfile;
  TTree *Zfittree;
  struct zfit_struct {
    Double_t mass_Z_gen;
    Double_t mass_Z_smear;

    Double_t elec_E[2];
    Double_t elec_px[2];
    Double_t elec_py[2];
    Double_t elec_pz[2];
    Double_t elec_deteta[2];
    Double_t elec_id[2];

    Double_t gen_elec_E[2];
    Double_t gen_elec_px[2];
    Double_t gen_elec_py[2];
    Double_t gen_elec_pz[2];

    Double_t event_weight;
    Double_t RecoilX_gen;
    Double_t RecoilY_gen;
    Double_t metX_FromMB;
    Double_t metY_FromMB;

    Double_t met_x;
    Double_t met_y;
    
    Double_t Trig_Ver;
    Double_t RecoilX;
    Double_t RecoilY;

    Double_t effFlag;
    Double_t lumi;
    Double_t elec_upara[2];
    Double_t elec_leakage[2];
    Double_t elec_ZBdiff[2];
    Double_t elec_peta[2];
    Double_t vtxZ;
    Double_t elec_detphi[2];
    Double_t ScalarEt;
  } zfit_data;

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
  
  const static bool use_old_ascii_files = false;
};

#endif // INC_ZANALYSIS
