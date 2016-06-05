#ifndef INC_EMSMEAR
#define INC_EMSMEAR

#include "PMCSEMObj.hpp"
#include "PParameterReader.hpp"
#include "hist_files.hpp"

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF2.h"
#include "TGraphErrors.h"
#include "TString.h"
#include <string>
#include "TRandom3.h"
#include "TROOT.h"
#include <vector>
#include <algorithm>
#include "TProfile2D.h"

class pmcsZBFunction;
class EMSmear {

 public:

  struct JSmearPars {
    double sampling_exp0;
    double sampling_exp1;
    double sampling_exp2;
    double sampling1;
    double sampling2;
  };

  struct CrackCBPars {
    double CrackCB_crlimit;
    double CrackCB_n;
    double CrackCB_alphaOffset;
    double CrackCB_alphaSlope;
    double CrackCB_PeakShiftOffset;
    double CrackCB_PeakShiftSlope;
  };

  
 public:

  //constructor: read in parameters
  EMSmear(TString parameter_filename, hist_files &_histos);

  // destructor 
  // FIXME: posted by Hengne. 
  // A lot of objects are initialized using "new", but no cleanup in the destructor. 
  ~EMSmear(){;}

  // Set CC Scale and Offset with dependence of Lumi and UPara
  void SetScaleOffsetDepCC(double lumi, double upara);

  // Set CC Scale and Offset back after called SetScaleOffsetDepCC()
  void ResetScaleOffsetCC();

  // return if require Lumi and/or UPara dependent CC scale and offset
  bool doCCscale_dep() const; 
  // the model for lumi-dependence of scale and offset
  int doCCscale_lumidep() const;
  double CCscale_lumidepFP_p0_q0() const;
  double CCscale_lumidepFP_p0_q1() const;
  double CCscale_lumidepFP_p2_q0() const;
  double CCscale_lumidepFP_p2_q1() const;
  double CCscale_lumidepFP_typical() const;
  //
  bool CCscale_DetEtaAdjust() const;
  std::vector<double> CCscale_DetEtaAdjust_factors() const;

  // Set luminosity
  void SetLuminosity(double luminosity);

  // Get luminosity
  double theLumi() const;

 // Set run number
  void SetRunNumber(double runnumber);

  // Get run number
  double theRunNumber() const;


  // Set Recoil vector
  void SetRecoilVec(TVector2 RecoilVec);

  // smear PMCSEMObject
  PMCSEMObj SmearEMObj(PMCSEMObj& emobj, TRandom3 *dummy);

  // smear a list of PMCSEMObjects
  std::vector<PMCSEMObj> SmearEMObjs(std::vector<PMCSEMObj>& emobjs, TRandom3 *dummy);

  // simulate electron energy response vs track PhiMod
  void SimulateEnergyResponseVsTrackPhiMod(PMCSEMObj part_smear, double& new_energy);
 
  // smear electron energy, eta, phi (physics and detector)
  // Only this function can simulate energies below electron window
  PMCSEMObj Smear(PMCSEMObj& part_gen,
		  double etares_phy, double phires_phy,
		  double etares_det, double phires_det,
		  double scale, double offset, double nonlinearity, double zelec_avept,
		  double sampling, double constant, double noise, 
                  double sampling1, double sampling2, double sampling_exp0, double sampling_exp1, double sampling_exp2, 
		  bool needCBtailAndPeakShift,
                  TRandom3 *dummy);

  // this is the basic smearing function, and the rest Smear functions just call this one
  // but no simulation of energies below electron window
  void Smear(double energy_gen, double energy_gen_wfsr, double eta_gen, double phi_gen,
	     double deteta_gen, double detphi_gen,
	     double etares_phy, double phires_phy,
	     double etares_det, double phires_det,
	     double scale, double offset, double nonlinearity, double zelec_avept,
	     double sampling, double constant, double noise, 
	     double sampling1, double sampling2, double sampling_exp0, double sampling_exp1, double sampling_exp2,
	     bool needCBtailAndPeakShift,
	     TRandom3 *dummy, double &phyeta_smeared, double &phyphi_smeared,
	     double &deteta_smeared, double &detphi_smeared, double &energy_smeared, bool &lost, double id, double vtxz);

  // use scale, offset, sampling etc defined by EMSmear class
  // but no simulation of energies below electron window
  void Smear(double energy_gen, double eta_gen, double phi_gen, double deteta_gen, double detphi_gen, 
	     TRandom3 *dummy, double &phyeta_smeared, double &phyphi_smeared,
	     double &deteta_smeared, double &detphi_smeared, double &energy_smeared, bool& lost, double id, double vtxz);
  
  // smear electron physics eta, phi
  void SmearPhysEtaPhi(PMCSEMObj& part_gen, double etares_phy, double phires_phy,
		       TRandom3 *dummy, double& phyeta_smeared, double& phyphi_smeared);
  void SmearPhysEtaPhi(double eta_gen, double phi_gen, double etares_phy, double phires_phy, TRandom3 *dummy, 
		       double& phyeta_smeared, double& phyphi_smeared);
  
  // smear electron detector eta, phi
  void SmearDetEtaPhi(PMCSEMObj& part_gen, double etares_det, double phires_det,
		      TRandom3 *dummy, double& deteta_smeared, double& detphi_smeared, bool &lost);
  void SmearDetEtaPhi(double deteta_gen, double detphi_gen, double etares_det, double phires_det,
		      TRandom3 *dummy, double& deteta_smeared, double& detphi_smeared, bool &lost, double id);

  // smear electron energy
  // but no simulation of energies below electron window
  void SmearEnergy(double energy, double eta, double phi, double phimod, double deteta,
		   double scale, double offset, 
		   double nonlinearity, double zelec_avept, 
		   double sampling, double constant, double noise, 
                   double sampling1, double sampling2, double sampling_exp0, double sampling_exp1, double sampling_exp2, bool needCBtailAndPeakShift,
                   TRandom3 *dummy, double& energy_smeared, double *extnRndm=0);

  // smear electron track pT
  void SmearTrkpT(PMCSEMObj& part_gen, TRandom3 *dummy, double &A, double &B, double &C, double &radlength);
  void SmearTrkpT(double trkpT_brem, TRandom3 *dummy, double& pT_Smear,double &A, double &B, double &C, double &radlength, double &BremFraction, double &proba_total, bool dobrem=true, double externalrndm=0., double externalrndm2[10]=NULL);

  // whether we want to do enegies below electron window studies
  void Set_EnergySim_ElecWindow(bool do_EnergySim_ElecWindow);

  // smear photon energy, no resolution yet, just response
  // this response is different than the photon response during electron and photon merging
  // due to zero-suppression effect
  void SmearPhotonEnergy(double energy_gen, double eta_gen, TRandom3 *dummy, double& energy_smeared);

  // simulate energies under electron window (only used for CC region)
  int SmearEnergyUnderElecWindow(PMCSEMObj& part, TRandom3 *dummy,  bool isW=false, Double_t *extrndm=0, Double_t *extrndm_duparaeff=0);
  // for energy scale and energy offset studies, I turned off the energies under electron window simulation first,
  // and then add the corrections
  void CorrectEnergyUnderElecWindow(double ElecEnergy, double ElecEta, double rawpTUnderElecWindow, double energyDiffElecWithWithoutZBOverlay, double &corrElecEnergy);

  // set smearing parameters, particulary useful when trying to 
  // derive energy scale and energy resolution parameters
  void SetCCSmearParameters(double etares_phy_cc, double phires_phy_cc, double etares_det_cc, double phires_det_cc, 
			    double scale_cc, double offset_cc, 
			    double nonlinearity_cc, double zelec_avept_cc,
			    double sampling_cc, double constant_cc, double noise_cc,
                            double sampling_cc1, double sampling_cc2, double sampling_ccexp0, double sampling_ccexp1, double sampling_ccexp2);

  void SetECSmearParameters(double etares_phy_ec, double phires_phy_ec, double etares_det_ec, double phires_det_ec, 
			    double scale_ec, double offset_ec, 
			    double nonlinearity_ec, double zelec_avept_ec,
			    double sampling_ec, double constant_ec, double noise_ec,
                            double sampling_ec1, double sampling_ec2, double sampling_ecexp0, double sampling_ecexp1, double sampling_ecexp2);

  // set electron energy scale parameters
  void SetCCScaleSmearParameters(double scale_cc, double offset_cc);
  void SetECScaleSmearParameters(double scale_ec, double offset_ec);

  // set electron energy resolution parameters
  void SetCCResolutionSmearParameters(double sampling_cc, double constant_cc, double noise_cc);
  void SetECResolutionSmearParameters(double sampling_ec, double constant_ec, double noise_ec);

  // this function is need for making templates
  // for tuning parameters of the Crystal Ball function that 
  // descrbies the degradation of electron energy resolution 
  // (or peak shift parameters that describe degradation of energy response)
  //  near phi-cracks
  void SetCrystalBallParameters(double CrackCB_crlimit, double CrackCB_n, double CrackCB_alphaOffset, double CrackCB_alphaSlope, double CrackCB_PeakShiftOffset, double CrackCB_PeakShiftSlope);
  
  //set tracking parameters
  void SetCCTrkResolutionSmearParameters(double A, double B, double C, double radiationlength);
  void SetECTrkResolutionSmearParameters(double A, double B, double C, double radiationlength);

  // return smearing parameters
  double EtaRes_Phy_CC() const;
  double PhiRes_Phy_CC() const;
  double EtaRes_Det_CC() const;
  double PhiRes_Det_CC() const;
  double Scale_CC() const;
  double Offset_CC() const;
  double Sampling_CC() const;
  double Constant_CC() const;
  double electronicNoiseFactor() const;
  double Noise_CC() const;
  double Energy_Nonlinearity_CC() const;
  double ZElec_AvePt_CC() const;
  double energyDiffElec() const; 
  double TrkA_CC() const;
  double TrkB_CC() const;
  double TrkC_CC() const;
  double TrkRadLength_CC() const;
  
  double TrkA_EC() const;
  double TrkB_EC() const;
  double TrkC_EC() const;
  double TrkRadLength_EC() const;

  JSmearPars JSmearing_CC() const;
  CrackCBPars CrackCB_CC() const;

  double EtaRes_Phy_EC() const;
  double PhiRes_Phy_EC() const;
  double EtaRes_Det_EC() const;
  double PhiRes_Det_EC() const;
  double Scale_EC() const;
  double Offset_EC() const;
  double Sampling_EC() const;
  double Constant_EC() const;
  double Noise_EC() const;
  double Energy_Nonlinearity_EC() const;
  double ZElec_AvePt_EC() const;
  JSmearPars JSmearing_EC() const;

  void fillSmearHistograms(PMCSEMObj &gen, PMCSEMObj &smear);
  inline TH1D**  getZBLibBin0Pointer(void) {return _hZBLibBin0_etabinz;}

  // simple PhiMod response correction function
  void SimpleEMRespCorrVsPhiMod(double energy_gen, double& energy_smeared, double track_phi_em3);

  // Hengne's (PhiMod, Etrue) Energy correction 
  void PhiModErespCorrHengne(PMCSEMObj& part);
 
  // Hengne's method for Phys and Det eta/phi smearing
  void SmearPhysEtaPhiHengne(double eta_gen, double phi_gen,
                             double etares_phy, double phires_phy, TRandom3 *dummy,
                             double& phyeta_smeared, double& phyphi_smeared, double ppid);

  void SmearDetEtaPhiHengne(double deteta_gen, double track_phi_em3, double etares_det, double phires_det, TRandom3 *dummy,
                                   double& deteta_smeared, double& detphi_smeared );

  void PhiModEffHengne(double energy_gen_wfsr, double track_phi_em3, TRandom3 *dummy, double& detphi_smeared, bool& lost ); 


 private:

  // helper functions for _ResolutionSmear_Option==3
  double jansmear_new(double nX0, double etap, double e) const;
  double janfunc(double params[4], double etap, double e) const;

  bool _run3bool, _run4bool;
  int _middlerunnumber;

  // data members
  int _ResolutionSmear_Option;  
  double _etares_phy_CC, _phires_phy_CC, _etares_det_CC, _phires_det_CC;
  double _etares_phy_EC, _phires_phy_EC, _etares_det_EC, _phires_det_EC;
  double _scale_CC, _offset_CC, _scale_EC, _offset_EC;
  double _scale_CC0, _offset_CC0; // a double copy of _scale_CC and _offset_CC
  double _sampling_CC, _noise_CC, _constant_CC;
  double _sampling_EC, _noise_EC, _constant_EC;
  double _Energy_Nonlinearity_CC, _ZElec_AvePt_CC;
  double _Energy_Nonlinearity_EC, _ZElec_AvePt_EC;
  double _Sampling_CC1, _Sampling_CC2, _Sampling_CCexp0, _Sampling_CCexp1, _Sampling_CCexp2;
  double _Sampling_EC1, _Sampling_EC2, _Sampling_ECexp0, _Sampling_ECexp1, _Sampling_ECexp2;

  // luminosity and Recoil vector
  double _luminosity;
  double _runNumber;
  TVector2 _RecoilVec;

  // lumi- and/or upara- dependent scale and offset in CC ?
  int _doCCscale_lumidep;
  bool _doCCscale_uparadep;
  double _theLumi;
 
  // for "model 1" of lumi dependence
  std::vector<double> _CCscale_lumidep_lumibins;
  std::vector<double> _CCscale_lumidep_scale;
  std::vector<double> _CCscale_lumidep_offset;
  std::vector<double> _CCscale_lumidep_scale_run3;
  std::vector<double> _CCscale_lumidep_offset_run3;
  std::vector<double> _CCscale_lumidep_scale_run4;
  std::vector<double> _CCscale_lumidep_offset_run4;
  std::vector<double> _CCscaleUT30_lumidep_scale;
  std::vector<double> _CCscaleUT30_lumidep_offset;
  // for "model 2" of lumi dependence (the first principles model)
  double _CCscale_lumidepFP_p0_q0;
  double _CCscale_lumidepFP_p0_q1;
  double _CCscale_lumidepFP_p2_q0;
  double _CCscale_lumidepFP_p2_q1;
  double _CCscale_lumidepFP_typical;
  //
  bool _CCscale_DetEtaAdjust;
  std::vector<double> _CCscale_DetEtaAdjust_factors;
  // for upara dependence
  double _CCscaleUT15_uparadep_scale, _CCscaleUT15_uparadep_offset;
  double _CCscaleUT30_uparadep_scale, _CCscaleUT30_uparadep_offset;

  // phi hack ?
  bool _doPhiHack;
  std::vector<double> _PhiHack_bins;
  std::vector<double> _PhiHack_corr;

  // use Crystall Ball response function in CC ??
  bool _CrackCBsim;
  double _CrackCB_crlimit;
  double _CrackCB_n;
  double _CrackCB_alphaOffset;
  double _CrackCB_alphaSlope;
  double _CrackCB_PeakShiftOffset;
  double _CrackCB_PeakShiftSlope;
  // use simple PhiMod-dependent EM response correction in CC ??
  bool _Use_Simple_EMrespCorr_vs_PhiMod;
  TString _Simple_EMrespCorr_vs_PhiMod_filename;
  TH1D* _Simple_EMrespCorr_vs_PhiMod;

  // simulate the response of electron vs track phi mod in CC
  bool _simulate_elecResponse_V_TrkPhiMod;
  TString _elecEOverP_V_TrkPhiMod_FileName;   // ET/pT vs track phimod, assuming pT is uniform vs track phimod
  double _average_EOverP;
  TH1F *_elecEOverP_V_TrkPhiMod;   // ET/pT vs track phimod, assuming pT is uniform vs track phimod
  
  bool _ApplyPhiModCorrection, _ApplyPhiModEfficiency;
  bool _ApplyTrkPhiModEfficiency;
  TH1F *_hPhiCrackEff;
  TH2F *_hPhiModShift;
  TH1D **_hPhiModShiftSlice;

  hist_files *_histos;
  bool _makeCheckSmearingPlots;

  bool _UParaCorrRunIIb;
  TH1F *_hEt_ThirteenTowers[22][13];
  TH1D *_hZBLibBin0_etabinz[11];
  TH1D *_hZBLibBin0_etabinw[11];
  double _electronicNoiseFactor;

  double _UParaCorrFudge;
  
  // whether we want to apply simulation of energies below electron window
  // take the energy difference between single energy electron without and with non-zero-suppressed ZB overlay
  // (offline zero-suppression applied for both samples), and parameterize the energy difference as a function
  // of underlying event energy below electron window. In PMCS, we first read the underlying event below electron
  // window from UParaCorr_CC_Hist file, and then use the parameterization to get the corrected energy, to do   
  // it this way, UE and zero-suppression effect are combined together
  bool  _EnergySim_ElecWindow;
  int _EnergySim_ElecWindowOption;

  double _EnergySim_ElecWindowFudge;

  // only used for EnergySim_ElecWindowOption = 1
  std::vector<double>  _P0_EnergyDiff_Electron_With_Without_ZBOverlay;
  std::vector<double>  _P1_EnergyDiff_Electron_With_Without_ZBOverlay;
  std::vector<double>  _P2_EnergyDiff_Electron_With_Without_ZBOverlay;
  std::vector<double> _EnergyDiff_FirstBin;
  std::vector<pmcsZBFunction*> _EnergyDiffFunctionw;
  std::vector<double> _EnergyDiff_Model2_FirstBinw;
  std::vector<pmcsZBFunction*> _EnergyDiffFunctionz;
  std::vector<double> _EnergyDiff_Model2_FirstBinz;

  // for EnergySim_ElecWindowOption = 4
  std::vector<double> _dUPlusSETBins, _dUPlusLumiBins, _dUPlusEtaBins;
  std::vector<double> _dUZeroSETBins, _dUZeroLumiBins, _dUZeroEtaBins, _dUZeroPtBins;
  std::vector< std::vector< std::vector< std::vector<double> > > > _duplus_par_vec, _duzero_par_vec;

  // for EnergySim_ElecWindowOption = 5
  int _CAEPSmoothdUPlus, _CAEPSmoothdUZero;
  std::vector<double> _CAEPdUPlusEtaBins, _CAEPdUPlusPtBins, _CAEPdUPlusUParaBins, _CAEPdUPlusLumiBins, _CAEPdUPlusSETBins;
  std::vector<double> _CAEPdUZeroEtaBins, _CAEPdUZeroPtBins, _CAEPdUZeroUParaBins, _CAEPdUZeroLumiBins, _CAEPdUZeroSETBins;
  std::vector< std::vector< std::vector< std::vector< std::vector<double*> > > > > _caep_duplus_par_vec, _caep_duzero_par_vec;

  // for EnergySim_ElecWindowOption = 6 , (those in  EnergySim_ElecWindowOption = 5 are also useful for 6 )
  std::vector<double> _CAEPdUPlusEtaBins2, _CAEPdUPlusPtBins2, _CAEPdUPlusUParaBins2, _CAEPdUPlusLumiBins2, _CAEPdUPlusSETBins2;
  std::vector<double> _CAEPdUZeroEtaBins2, _CAEPdUZeroPtBins2, _CAEPdUZeroUParaBins2, _CAEPdUZeroLumiBins2, _CAEPdUZeroSETBins2;
  std::vector< std::vector< std::vector< std::vector< std::vector<double*> > > > > _caep_duplus_par_vec2, _caep_duzero_par_vec2;


 
  // parameters used in Run Ia method
  //   double _UE_ElecWindow_true;
  //   double _NumTowers_EMCluster;
  //   double _ZSUP_UE;
  //   double _ZSUP_Elec;
  //
  int _UParaCorrOption;
  int _ZSUPCorrOption;
  double _UParaCorr_CC;
  double _UParaCorr_EC;
  double _UParaCorr_CC_V_Lumi_Slope;
  double _Delta_ZSUP_CC;
  double _Delta_ZSUP_EC;
  int _ENERGY_OUTCONE_MODEL_Elec_CC;
  double _ENERGY_OUTCONE_Elec_CC;
  TH1D* _ENERGY_OUTCONE_JanModel_Elec_CC[14];
  double _ENERGY_OUTCONE_JanModel_Elec_Fudge_CC;
  TH1D* _ENERGY_OUTCONE_JanModel_Elec_CCfsr[14];
  double _ENERGY_OUTCONE_JanModel_Elec_Fudge_CCfsr;
  double _ENERGY_OUTCONE_Elec_EC;
  double _ZSUP_CC_Elec_NoMBOverlay;
  double _energyDiffElec;

  std::vector< double > eleak_model5_ptbins;
  std::vector< double > eleak_model5_etabins;
  std::vector< double > eleak_model5_setbins;
  std::vector< double > eleak_model5_Xbins;
  std::vector< std::vector< std::vector< TH1D* > > > eleak_model5_leakageDistribution;
  std::vector< std::vector< std::vector< std::vector< TH1D* > > > > eleak_model5_leakageDistributionFSR;
  std::vector< TProfile2D* > eleak_model5_leakageProbability;
  std::vector< TProfile2D* > eleak_model5_leakageProbabilityFSR;
  Double_t eleak_model5_vetoFudge;
  Double_t eleak_model5_FSRFudge;
  Bool_t eleak_model5_interpolate;

  // uparallel correction histogram and dependence on luminosity
  TH1F *_UparaCorr_CC_Hist, *_UParaCorr_CC_V_Lumi_Hist;
 
  // uparallel correction dependence on uparallel itself
  std::vector<double> _UParaCorr_CC_V_UPara_Parameters;

  // dUParaEff for UPara Correction:
  bool _Apply_dUParaEff;
  int _dUParaEff_Option;
  bool _dUParaEffUsedEPara;
  bool _dUParaEffUseTruePT;

  // parameters for dUParaEff_Option = 0
  bool _dUParaEff_Smooth_Eff;
  int _dUParaEff_Nbins_W;
  std::vector<double> _dUParaEff_Bin_Min_W;
  std::vector<double> _dUParaEff_Bin_Max_W;
  std::vector<double> _dUParaEff_Mean_Pt_W;
  std::vector<double> _dUParaEff_Zero_dUPara_W;
  std::vector<double> _dUParaEff_Func_Par0_W;
  std::vector<double> _dUParaEff_Func_Par1_W;
  int _dUParaEff_Nbins_Z;
  std::vector<double> _dUParaEff_Bin_Min_Z;
  std::vector<double> _dUParaEff_Bin_Max_Z;
  std::vector<double> _dUParaEff_Mean_Pt_Z;
  std::vector<double> _dUParaEff_Zero_dUPara_Z;
  std::vector<double> _dUParaEff_Func_Par0_Z;
  std::vector<double> _dUParaEff_Func_Par1_Z;
  double Get_dUParaEff(double dupara, double elecpt, bool isW);

  // parameters for dUParaEff_Option = 1
  int _dUParaEff_Option1_NEtaBins;
  int _dUParaEff_Option1_NPTBins;
  std::vector<double> _dUParaEff_Option1_EtaBins;
  std::vector<double> _dUParaEff_Option1_PTBins;
  std::vector< std::vector<double*> > _dUParaEff_Option1_Pars;
  double Get_dUParaEff1(double dupara, double elecpt, double eta);

  // parameters for dUParaEff_Option = 2
  int _dUParaEff_Option2_NEtaBins;
  int _dUParaEff_Option2_NEtaBins2;
  int _dUParaEff_Option2_NPTBins;
  int _dUParaEff_Option2_NPTBins2;
  std::vector<double> _dUParaEff_Option2_EtaBins;
  std::vector<double> _dUParaEff_Option2_EtaBins2;
  std::vector<double> _dUParaEff_Option2_PTBins;
  std::vector<double> _dUParaEff_Option2_PTBins2;
  std::vector< std::vector<double*> > _dUParaEff_Option2_Pars;
  std::vector< std::vector<double*> > _dUParaEff_Option2_Pars2;
  double Get_dUParaEff2(double dupara, double elecpt, double eta);

  // parameters for dUParaEff_Option = 6
  TFile* _dUParaEff_Option6_UseHists_ParFile;
  vector<double> _dUParaEff_Option6_UseHists_UPerpBins;
  vector<double> _dUParaEff_Option6_UseHists_SETBins;
  vector<double> _dUParaEff_Option6_UseHists_UParaBins;
  vector<double> _dUParaEff_Option6_UseHists_EtaBins;
  vector<double> _dUParaEff_Option6_UseHists_PTBins;
  int _dUParaEff_Option6_UseHists_NUPerpBins;
  int _dUParaEff_Option6_UseHists_NSETBins;
  int _dUParaEff_Option6_UseHists_NUParaBins;
  int _dUParaEff_Option6_UseHists_NEtaBins;
  int _dUParaEff_Option6_UseHists_NPTBins;
  vector<TH1D*> _dUParaEff_Option6_UseHists_hist_PT_vec;
  vector< vector<TH1D*> > _dUParaEff_Option6_UseHists_hist_EtaPT_vec;
  vector< vector< vector<TH1D*> > > _dUParaEff_Option6_UseHists_hist_UParaEtaPT_vec;
  vector< vector< vector< vector<TH1D*> > > > _dUParaEff_Option6_UseHists_hist_SETUParaEtaPT_vec;
  vector< vector< vector< vector< vector<TH1D*> > > > > _dUParaEff_Option6_UseHists_hist_UPerpSETUParaEtaPT_vec;

  // also for dUParaEff_Option = 6, but double it for 2b4
  TFile* _dUParaEff_Option6_UseHists_ParFile2;
  vector<double> _dUParaEff_Option6_UseHists_UPerpBins2;
  vector<double> _dUParaEff_Option6_UseHists_SETBins2;
  vector<double> _dUParaEff_Option6_UseHists_UParaBins2;
  vector<double> _dUParaEff_Option6_UseHists_EtaBins2;
  vector<double> _dUParaEff_Option6_UseHists_PTBins2;
  int _dUParaEff_Option6_UseHists_NUPerpBins2;
  int _dUParaEff_Option6_UseHists_NSETBins2;
  int _dUParaEff_Option6_UseHists_NUParaBins2;
  int _dUParaEff_Option6_UseHists_NEtaBins2;
  int _dUParaEff_Option6_UseHists_NPTBins2;
  vector<TH1D*> _dUParaEff_Option6_UseHists_hist_PT_vec2;
  vector< vector<TH1D*> > _dUParaEff_Option6_UseHists_hist_EtaPT_vec2;
  vector< vector< vector<TH1D*> > > _dUParaEff_Option6_UseHists_hist_UParaEtaPT_vec2;
  vector< vector< vector< vector<TH1D*> > > > _dUParaEff_Option6_UseHists_hist_SETUParaEtaPT_vec2;
  vector< vector< vector< vector< vector<TH1D*> > > > > _dUParaEff_Option6_UseHists_hist_UPerpSETUParaEtaPT_vec2;

  bool EMSmear::SetdUParaEffParsModel6UseHists(PParameterReader& parm);
  double EMSmear::Get_dUParaEff6_UseHists(double dupara, double elecpt);
  void EMSmear::Get_dUParaEff6_UseHistsInit(double elecpt, double eta, double upara, double set, double uperp);

  // parameters for _UParaCorrOption==3
  int _OptionOfUParaCorrOption3;
  bool _UParaCorrOption3_dUParaLibUsedEPara;
  TF2* _dUParaMeanFunction;
  TProfile2D* _dUParaMeanProfile;
  TH3D* _dUParaMeanProfile3D;
  TH3D* _dUParaZeroFraction3D;
  TH3D* _dUParaMeanProfile3DEta[11];
  TH3D* _dUParaZeroFraction3DEta[11];
  TH3D* _dUParaMeanProfile3D2Eta[15][15];
  TH3D* _dUParaMeanProfile3D2Eta2[15][15];
  TH3D* _dUParaZeroFraction3D2Eta[15][15];
  TH3D* _dUParaZeroFraction3D2Eta2[15][15];
  TH3D* _dUParaMeanProfile3D2EtaUPerp[15][15][10];
  TH3D* _dUParaZeroFraction3D2EtaUPerp[15][15][10];
  TH3D* _dUParaMeanProfile3D2EtaUPerp2[15][15][10];
  TH3D* _dUParaZeroFraction3D2EtaUPerp2[15][15][10];

  TH3D* _dUParaSmearHist3D;
  TH3D* _dUParaSmearHist3D2;
  TH1D* _dUParaSmearHist1DAll;
  TH1D* _dUParaSmearHist1DAll2;
  TH1D* _dUParaSmearHist1D[30][30];
  TH1D* _dUParaSmearHist1D2[30][30];
  TH3D* _dUParaSmearHist3DLumi[5];
  TH3D* _dUParaSmearHist3DLumi2[5];
  TH1D* _dUParaSmearHist1DLumiAll[5];
  TH1D* _dUParaSmearHist1DLumiAll2[5];
  TH1D* _dUParaSmearHist1DLumi[5][30][30];
  TH1D* _dUParaSmearHist1DLumi2[5][30][30];


  TH1D* _hist_UPerpSETUParaEtaPT;
  TH1D* _hist_SETUParaEtaPT;
  TH1D* _hist_UParaEtaPT;
  TH1D* _hist_EtaPT;
  TH1D* _hist_PT;


  // zero-suppression effect dependence on electron detector eta
  std::vector<double> _ZSUP_CC_V_ElecEta_Parameters;

  // parameters used for smearing electron track pT
  bool _SmearTrkpT;
  double _A_CC, _B_CC, _C_CC;
  double _TrackRadLength_CC;
  double _A_EC, _B_EC, _C_EC;
  double _TrackRadLength_EC;
  bool _bremSim;

  // Smear Phys Eta Phys Phi using Hengne's histograms
  bool _SmearEtaPhiHengne;
  bool _ApplyPhiModEffHengne;
  TH1D* _hPhyPhiResoPos;
  TH1D* _hPhyPhiResoEle;
  TH1D* _hEmfIsoHMxEffVsPhiMod;
  TH2D* _hTkMatchEffVsPhiModVsEtrue; 

  // Hengne's PhiMod:Etrue Energy correction
  bool _ApplyPhiModErespCorrHengne;
  TH2D* _hErespPhiModEtrue;
  // if we also want to apply electron energy scale on the delta E correction of electron window
  bool _ApplyScaleOnDeltaE;
}
;
inline void EMSmear::SetLuminosity(double luminosity) {_luminosity = luminosity;}
inline double EMSmear::theLumi() const {return _theLumi;}
inline void EMSmear::SetRunNumber(double runnumber) {_runNumber = runnumber;}
inline double EMSmear::theRunNumber() const {return _runNumber;}
inline void EMSmear::SetRecoilVec(TVector2 RecoilVec) {_RecoilVec = RecoilVec;}

inline void EMSmear::ResetScaleOffsetCC() { _scale_CC = _scale_CC0; _offset_CC = _offset_CC0; }
inline bool EMSmear::doCCscale_dep() const {return _doCCscale_lumidep||_doCCscale_uparadep;}
inline int EMSmear::doCCscale_lumidep() const {return _doCCscale_lumidep;}
inline double EMSmear::CCscale_lumidepFP_p0_q0() const {return _CCscale_lumidepFP_p0_q0;}
inline double EMSmear::CCscale_lumidepFP_p0_q1() const {return _CCscale_lumidepFP_p0_q1;}
inline double EMSmear::CCscale_lumidepFP_p2_q0() const {return _CCscale_lumidepFP_p2_q0;}
inline double EMSmear::CCscale_lumidepFP_p2_q1() const {return _CCscale_lumidepFP_p2_q1;}
inline double EMSmear::CCscale_lumidepFP_typical() const {return _CCscale_lumidepFP_typical;}
//
inline bool EMSmear::CCscale_DetEtaAdjust() const {return _CCscale_DetEtaAdjust;}
inline std::vector<double> EMSmear::CCscale_DetEtaAdjust_factors() const {return _CCscale_DetEtaAdjust_factors;}

inline double EMSmear::EtaRes_Phy_CC() const {return _etares_phy_CC;}
inline double EMSmear::PhiRes_Phy_CC() const {return _phires_phy_CC;}
inline double EMSmear::EtaRes_Det_CC() const {return _etares_det_CC;}
inline double EMSmear::PhiRes_Det_CC() const {return _phires_det_CC;}
inline double EMSmear::Scale_CC() const {return _scale_CC;}
inline double EMSmear::Offset_CC() const {return _offset_CC;}
inline double EMSmear::Sampling_CC() const {return _sampling_CC;}
inline double EMSmear::Constant_CC() const {return _constant_CC;}
inline double EMSmear::Noise_CC() const {return _noise_CC;}
inline double EMSmear::Energy_Nonlinearity_CC() const {return _Energy_Nonlinearity_CC;}
inline double EMSmear::ZElec_AvePt_CC() const {return _ZElec_AvePt_CC;}
inline double EMSmear::energyDiffElec() const {return _energyDiffElec;}
inline double EMSmear::electronicNoiseFactor() const {return _electronicNoiseFactor;}

inline double EMSmear::TrkA_CC() const {return _A_CC;}
inline double EMSmear::TrkB_CC() const {return _B_CC;}
inline double EMSmear::TrkC_CC() const {return _C_CC;}
inline double EMSmear::TrkRadLength_CC() const {return _TrackRadLength_CC;}

inline double EMSmear::TrkA_EC() const {return _A_EC;}
inline double EMSmear::TrkB_EC() const {return _B_EC;}
inline double EMSmear::TrkC_EC() const {return _C_EC;}
inline double EMSmear::TrkRadLength_EC() const {return _TrackRadLength_EC;}

inline EMSmear::JSmearPars EMSmear::JSmearing_CC() const {
  struct JSmearPars r;
  r.sampling_exp0=_Sampling_CCexp0;
  r.sampling_exp1=_Sampling_CCexp1;
  r.sampling_exp2=_Sampling_CCexp2;
  r.sampling1=_Sampling_CC1;
  r.sampling2=_Sampling_CC2;
  return r;
}

inline EMSmear::CrackCBPars EMSmear::CrackCB_CC() const {
  struct CrackCBPars r;
  r.CrackCB_crlimit	    =_CrackCB_crlimit	 ;
  r.CrackCB_n			=_CrackCB_n 	  	 ;
  r.CrackCB_alphaOffset =_CrackCB_alphaOffset;
  r.CrackCB_alphaSlope  =_CrackCB_alphaSlope ;
  r.CrackCB_PeakShiftOffset	=_CrackCB_PeakShiftOffset ;
  r.CrackCB_PeakShiftSlope	=_CrackCB_PeakShiftSlope  ;
  return r;
}

inline double EMSmear::EtaRes_Phy_EC() const {return _etares_phy_EC;}
inline double EMSmear::PhiRes_Phy_EC() const {return _phires_phy_EC;}
inline double EMSmear::EtaRes_Det_EC() const {return _etares_det_EC;}
inline double EMSmear::PhiRes_Det_EC() const {return _phires_det_EC;}
inline double EMSmear::Scale_EC() const {return _scale_EC;}
inline double EMSmear::Offset_EC() const {return _offset_EC;}
inline double EMSmear::Sampling_EC() const {return _sampling_EC;}
inline double EMSmear::Constant_EC() const {return _constant_EC;}
inline double EMSmear::Noise_EC() const {return _noise_EC;}
inline double EMSmear::Energy_Nonlinearity_EC() const {return _Energy_Nonlinearity_EC;}
inline double EMSmear::ZElec_AvePt_EC() const {return _ZElec_AvePt_EC;}
inline EMSmear::JSmearPars EMSmear::JSmearing_EC() const {
  struct JSmearPars r;
  r.sampling_exp0=_Sampling_ECexp0;
  r.sampling_exp1=_Sampling_ECexp1;
  r.sampling_exp2=_Sampling_ECexp2;
  r.sampling1=_Sampling_EC1;
  r.sampling2=_Sampling_EC2;
  return r;
}
  
// whether we want to do enegies below electron window studies
inline void EMSmear::Set_EnergySim_ElecWindow(bool do_EnergySim_ElecWindow) {_EnergySim_ElecWindow = do_EnergySim_ElecWindow;}

inline void EMSmear::SetCCScaleSmearParameters(double scale_cc, double offset_cc) {
  _scale_CC = scale_cc;
  _offset_CC = offset_cc;
}

inline void EMSmear::SetCCTrkResolutionSmearParameters(double A, double B, double C, double radiationlength){
  _A_CC = A;
  _B_CC = B;
  _C_CC = C;
  _TrackRadLength_CC = radiationlength;
}

inline void EMSmear::SetECTrkResolutionSmearParameters(double A, double B, double C, double radiationlength){
  _A_EC = A;
  _B_EC = B;
  _C_EC = C;
   _TrackRadLength_CC = radiationlength;
}

inline void EMSmear::SetECScaleSmearParameters(double scale_ec, double offset_ec) {
  _scale_EC = scale_ec;
  _offset_EC = offset_ec;
}

inline void EMSmear::SetCCResolutionSmearParameters(double sampling_cc, double constant_cc, double noise_cc) {
  _sampling_CC = sampling_cc;
  _constant_CC = constant_cc;
  _noise_CC = noise_cc;
}

inline void EMSmear::SetECResolutionSmearParameters(double sampling_ec, double constant_ec, double noise_ec) {
  _sampling_EC = sampling_ec;
  _constant_EC = constant_ec;
  _noise_EC = noise_ec;
}

inline void EMSmear::SetCrystalBallParameters(double CrackCB_crlimit, double CrackCB_n, double CrackCB_alphaOffset, double CrackCB_alphaSlope, double CrackCB_PeakShiftOffset, double CrackCB_PeakShiftSlope) {
  _CrackCB_crlimit     = CrackCB_crlimit;
  _CrackCB_n           = CrackCB_n;
  _CrackCB_alphaOffset = CrackCB_alphaOffset;
  _CrackCB_alphaSlope  = CrackCB_alphaSlope;
  _CrackCB_PeakShiftOffset  = CrackCB_PeakShiftOffset;
  _CrackCB_PeakShiftSlope   = CrackCB_PeakShiftSlope;
}

#endif
