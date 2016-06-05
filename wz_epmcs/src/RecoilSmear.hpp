#ifndef INC_RECOILSMEAR
#define INC_RECOILSMEAR

#include "PMCSRecoil.hpp"
#include "PMCSEMObj.hpp"
#include "PParameterReader.hpp"
#include "hist_files.hpp"
#include "ZRecoilMethod_Util.hpp"
#include "HardRecoil_Manager.hpp"

#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include "TRandom3.h"
#include "TFile.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include <vector>

#include <iostream>

class MySETFunction;
class RecoilSmear {
  
 public:

  //constructor and read in smearing parameters
  RecoilSmear(TString parameter_filename, hist_files &_histos, TRandom3* dummy);

  //destructor
  ~RecoilSmear(){
     if (_ftblib) _ftblib->Close();
   }

  // smear hard component + soft component 
  PMCSRecoil SmearRecoil(PMCSRecoil &gen, TRandom3* dummy);

  // smear hard component
  void SmearHardRecoil_Method_A(double raw_recoil_pT, double raw_recoil_phi, 
				double scale_HAD, double offset_HAD, 
				double phi_smear_true_recoil_A, double phi_smear_true_recoil_B,
				double constant_HAD, double sampling_HAD, 
				TRandom3 *dummy, double& smear_recoil_pT, double& smear_recoil_phi);
  void SmearHardRecoil_Method_B(double raw_recoil_pT, double raw_recoil_phi, 
				double Relscale_HAD_bifurcate_A, double Relscale_HAD_bifurcate_B, double Relscale_HAD_bifurcate_Tau,
				double Relsampling_HAD_bifurcate_A, double Relsampling_HAD_bifurcate_B, double Relconst_HAD_bifurcate, 
				double Reltrans_HAD_RelRespTrans, double Reltrans_HAD_RelResnTrans, double Reltrans_HAD_RelTauTrans,
				double Relphi_HAD_bifurcate_A, double Relphi_HAD_bifurcate_B, double RelconstPhi_HAD_bifurcate,
				TRandom3 *dummy, double& smear_recoil_pT, double& smear_recoil_phi, double& smear_SET,
				double pt_resol_external=-1.0,                // effective only when skip_Znunu_randomization=TRUE
				double delta_phi_external=-1.0,               // effective only when skip_Znunu_randomization=TRUE
				double znunu_SET_Hard_external=-1.0,          // effective only when skip_Znunu_randomization=TRUE
				double znunu_SET_Hard_expected_external=-1.0, // effective only when skip_Znunu_randomization=TRUE
				bool skip_Znunu_randomization=false,
				bool skip_Znunu_fudging=false,
				int EtFlowFudge=0,
				double instlum=-1);
  void SmearHardRecoil_Method_D(double raw_recoil_pT, double raw_recoil_phi, 
				double Relscale_HAD_bifurcate_A, double Relscale_HAD_bifurcate_B, double Relscale_HAD_bifurcate_Tau,
				double Relsampling_HAD_bifurcate_A, double Relsampling_HAD_bifurcate_B, double Relconst_HAD_bifurcate, 
				double Reltrans_HAD_RelRespTrans, double Reltrans_HAD_RelResnTrans, double Reltrans_HAD_RelTauTrans,
				double Relphi_HAD_bifurcate_A, double Relphi_HAD_bifurcate_B, double RelconstPhi_HAD_bifurcate,
				TRandom3 *dummy, double& smear_recoil_pT, double& smear_recoil_phi, double& smear_SET,
				double pt_resol_external=-1.0,                // effective only when skip_Znunu_randomization=TRUE
				double delta_phi_external=-1.0,               // effective only when skip_Znunu_randomization=TRUE
				double znunu_SET_Hard_external=-1.0,          // effective only when skip_Znunu_randomization=TRUE
				double znunu_SET_Hard_expected_external=-1.0, // effective only when skip_Znunu_randomization=TRUE
				bool skip_Znunu_randomization=false,
				bool skip_Znunu_fudging=false,
				int EtFlowFudge=0,
				double instlum=-1);

  // retrive recoil vectors (inlucding generator and intermediate steps)
  // from the last call of SmearHardRecoil_Method_B
  void GetLastHardRecoil_Method_B(double *gen_pt=NULL,
				  double *gen_phi=NULL,
				  double *znunu_pt=NULL,
				  double *znunu_phi=NULL,
				  double *smear_pt=NULL,
				  double *smear_phi=NULL);

  // retrive SET (inlucding intermediate steps)
  // from the last call of SmearHardRecoil_Method_B
  void GetLastHardScalarEt_Method_B(double *znunu_SET_Hard=NULL,
				    double *znunu_SET_Hard_expected=NULL,
				    double *smear_SET_Hard=NULL);

  void SmearHardRecoil_Method_C(double raw_recoil_pT, double raw_recoil_phi, 
				double scale_HAD_A, double scale_HAD_B, double scale_HAD_C, 
				double phi_smear_true_recoil_A, double phi_smear_true_recoil_B, 
				double constant_HAD, double sampling_HAD, 
				TRandom3 *dummy, double& smear_recoil_pT, double& smear_recoil_phi);
  
  // smear soft component
  void SmearSoftRecoil_Method_A(double underlying, double alpha_mb,
				TRandom3 *dummy, double& smear_Metx, double& smear_Mety);
  void SmearSoftRecoil_Method_B(TH2F *hmetxmety, double alpha_mb,
				TRandom3 *dummy, double& smear_Metx, double& smear_Mety);
  void SmearSoftRecoil_Method_C(double luminosity, double alpha_mb,
				TRandom3 *dummy, double& smear_Metx, double& smear_Mety);
  void SmearSoftRecoil_Method_D(double alpha_mb, double alpha_zb, TRandom3 *dummy, 
				double& smear_Metx_From_MB, double& smear_Mety_From_MB, 
				double& smear_Metx_From_ZB, double& smear_Mety_From_ZB, 	
				double& smear_Metx, double& smear_Mety,
				double* trueHardPhi=0, double alpha_mb_trans=1);
  
  void fillSmearHistograms(PMCSRecoil &gen, PMCSRecoil &smear);

  // a simple function to randomly get an event from the zerobias library (not minbias library)
  // and assign the run number, instantaneous luminosity for that zerobias event
  // as the run number, instantaneous luminosity for the PMCS event
  // I also keep an index in order to find which event is used
  void setRunNoInstLumiMBZBEvtIndex(TRandom3 *dummy);

  void setRunNoInstLumiMBZBEvtIndex(int runNo, double instLumi, int MBEvtIndex, int ZBEvtIndex);

  // get run number and instantaneous luminosity from PMCS event
  void getRunNoInstLumiMBZBEvtIndex(int &runNo, double &instLumi, int &MBEvtIndex, int &ZBEvtIndex) const;

  // get run number event_number and instantaneous luminosity from PMCS event
  void getRunNoEvtNoInstLumiMBZBEvtIndex(int &runNo, int &evtNo, double &instLumi, int &MBEvtIndex, int &ZBEvtIndex) const;

  // energies under electron(s) window are already included in electron energy smearing
  // need to subtract them from recoil system
  // apply uparallel corrections for both W and Z events
  // option == 0 for Z and option == 1 for W
  void applyUparaCorrection(std::vector<PMCSEMObj> &emobjs, PMCSRecoil &recoil_smear_beforeUparaCorr,
			    PMCSRecoil &recoil_smear_afterUparaCorr, int option);


  void ApplyTopBottomAsym(double& recoilx, double& recoily);
  void ApplyTopBottomAsym_B(double& recoilx, double& recoily, bool save=true);
  //RCLSA
  void GetLastTopBottomAsym_B(double& recoilx, double& recoily);
  double getTBdmetx() const { if (_last_tb_exists) return _last_tbdmetx; else return 0.;}
  double getTBdmety() const { if (_last_tb_exists) return _last_tbdmety; else return 0.;}
  double recoilx_beforeTB() const {return _recoilx_beforeTB;}  // only used for MomentumSmearOption=0
  double recoily_beforeTB() const {return _recoily_beforeTB;} // only used for MomentumSmearOption=0
  double scale_HAD() const {return _scale_HAD;}  // only used for MomentumSmearOption=0
  double offset_HAD() const {return _offset_HAD;} // only used for MomentumSmearOption=0
  double scale_HAD_bifurcate_A() const {return _scale_HAD_bifurcate_A;} // only used for MomentumSmearOption=1
  double scale_HAD_bifurcate_B() const {return _scale_HAD_bifurcate_B;} // only used for MomentumSmearOption=1
  double scale_HAD_bifurcate_Tau() const {return _scale_HAD_bifurcate_Tau;} // only used for MomentumSmearOption=1
  double Relsampling_HAD_bifurcate_A() const {return _Relsampling_HAD_bifurcate_A;} 
  double Relsampling_HAD_bifurcate_B() const {return _Relsampling_HAD_bifurcate_B;}
  double Relconst_HAD_bifurcate() const {return _Relconst_HAD_bifurcate;}
  double Reltrans_HAD_bifurcate_RelRespTrans() const {return _RelRespTrans;}
  double Reltrans_HAD_bifurcate_RelResnTrans() const {return _RelResnTrans;}
  double Reltrans_HAD_bifurcate_RelTauTrans() const {return _RelTauTrans;}
  double Relphi_HAD_bifurcate_A() const {return _Relphi_HAD_bifurcate_A;}
  double Relphi_HAD_bifurcate_B() const {return _Relphi_HAD_bifurcate_B;}
  double RelconstPhi_HAD_bifurcate() const {return _RelconstPhi_HAD_bifurcate;}
  double scale_HAD_A() const {return _scale_HAD_A;} // only used for MomentumSmearOption=2
  double scale_HAD_B() const {return _scale_HAD_B;} // only used for MomentumSmearOption=2
  double scale_HAD_C() const {return _scale_HAD_C;} // only used for MomentumSmearOption=2
  double sampling_HAD() const {return _sampling_HAD;} // used for MomentumSmearOption=0,2,3
  double constant_HAD() const {return _constant_HAD;} // used for MomentumSmearOption=0,2,3
  double phi_smear_true_recoil_A() const {return _phi_smear_true_recoil_A;} // used for MomentumSmearOption=0,2,3
  double phi_smear_true_recoil_B() const {return _phi_smear_true_recoil_B;} // used for MomentumSmearOption=0,2,3
  double alpha_mb_overlay() const {return _alpha_mb_overlay;} // only used for _METSmearOption=0, 1, 2
  double alpha_mb() const {return _alpha_mb;} // only used for _METSmearOption=3
  double alpha_zb() const {return _alpha_zb;} // only used for _METSmearOption=3
  double alpha_mb_trans() const {return _alpha_mb_trans;} // only used for _METSmearOption=3
  int    EtFlowFudge() const { return _EtFlowFudge; }

  // set smearing parameters for hard component smearing
  void SetHardSmearingParameters_MethodA(double scale_HAD, double offset_HAD, 
					 double phi_smear_true_recoil_A, double phi_smear_true_recoil_B, 
					 double constant_HAD, double sampling_HAD);
  void SetHardSmearingParameters_MethodB(double scale_HAD_bifurcate_A, double scale_HAD_bifurcate_B, double scale_HAD_bifurcate_Tau, 
                                         double Relsampling_HAD_bifurcate_A, double Relsampling_HAD_bifurcate_B, double Relconst_HAD_bifurcate,
					 double Reltrans_HAD_RelRespTrans, double Reltrans_HAD_RelResnTrans, double Reltrans_HAD_RelTauTrans,
                                         double Relphi_HAD_bifurcate_A, double Relphi_HAD_bifurcate_B, double RelconstPhi_HAD_bifurcate);
  void SetHardSmearingParameters_MethodC(double scale_HAD_A, double scale_HAD_B, double scale_HAD_C, 
					 double phi_smear_true_recoil_A, double phi_smear_true_recoil_B,
					 double constant_HAD, double sampling_HAD);

  // set smearing parameters for soft component smearing
  void SetSoftSmearingParameters_MethodA(double underlying, double alpha_mb);
  void SetSoftSmearingParameters_MethodB(double alpha_mb);
  void SetSoftSmearingParameters_MethodC(double alpha_mb);
  void SetSoftSmearingParameters_MethodD(double alpha_mb, double alpha_zb, double alpha_mb_trans=1);

  // if using recoil library method, this option inputs the luminsity generated in pmcsana.cpp
  void InputLuminosity(double theLumi);
 
  // get recoil from hard component and soft component separately 
  double recoilX_HardComponent() const {return _recoilX_HardComponent;}
  double recoilY_HardComponent() const {return _recoilY_HardComponent;}
  double recoilX_SoftComponent() const {return _recoilX_SoftComponent;}
  double recoilY_SoftComponent() const {return _recoilY_SoftComponent;}

  // more functions
  int METSmear_Option() const {return _METSmear_Option;}
  int Momentum_SmearOption_HAD() const {return _Momentum_SmearOption_HAD;}

  // using recoil pT from Z file
  bool read_recoil_file() const {return _read_recoil_file;}
  TH1F * RunNoHist() const {return zrecoilmethod->RunNo_WZ;}
  TH1F * InstLumiHist() const {return zrecoilmethod->InstLumi_WZ;}

  // get Met MB
  TVector2 GetMet_MB() const;

  // get Met ZB
  TVector2 GetMet_ZB() const;

  // get scalar Et for MB overlay
  double scalarEt_MB() const;

  // get scalar Et for ZB overlay
  double scalarEt_ZB() const;

  // get scalar Et of ZB without _scale_zb scale
  double scalarEt_ZB_NoScale() const;

  // get scalar Et from hard component
  double scalarEt_hard();

  // get scalar Et lost to electron cone
  inline double scalarEt_cone(){ return _ScalarEt_cone;}

  // get total scalar Et
  double scalarEt();

  // dump overlay ZB runNo and evtNo
  void DumpEvtID() const;

  int GetEvtIDrun() const;
  int GetEvtIDevent() const;

  void SetTBAsymmParameters(double alpha, double beta);
  void GetTBAsymmParameters(double& alpha, double& beta);

  double GetMB_MetX() const { return _MB_MetX; }
  double GetMB_MetY() const { return _MB_MetY; }
  
  int GetNPV_ZB() { return _NumPV; }
  int GetTickNum_ZB() { return _TickNum; }
  int GetTimeLastL1Accept_ZB() { return _TimeLastL1Accept; }
   double GetLumi() const {return _instLumi;}

 private:

  HardRecoil_Manager* hard_recoil;

  double _MB_MetX, _MB_MetY;
  bool _run3bool, _run4bool;

  // run number and instantaneous luminosity for overlaid zerobias and minbias events
  int _runNo, _evtNo, _ZBEvtIndex, _MBEvtIndex;
  int _NumPV , _TickNum , _TimeLastL1Accept;
  double _instLumi;
  double _instLumi_Z;
 
  // zpt and chosen recoil
  double _gen_Z_pT;
  double _chosen_recoil;

  // hadronic momentum smearing option
  int _Momentum_SmearOption_HAD; 
 
  // hadronic momentum scale
  double _scale_HAD, _offset_HAD;                         // for _Momentum_SmearOption_HAD==0
  double _scale_HAD_bifurcate_A, _scale_HAD_bifurcate_B, _scale_HAD_bifurcate_Tau;  // for _Momentum_SmearOption_HAD==1
  double _Relsampling_HAD_bifurcate_A, _Relsampling_HAD_bifurcate_B, _Relconst_HAD_bifurcate;
  double _Relphi_HAD_bifurcate_A, _Relphi_HAD_bifurcate_B, _RelconstPhi_HAD_bifurcate;
  double _RelRespTrans, _RelResnTrans, _RelTauTrans;
  int _EtFlowFudge;
  double _Hard_Recoil_from_Znunu_pT, _Hard_Recoil_from_Znunu_phi; // from last SmearHardRecoil_Method_B
  double _Hard_Recoil_generated_pT, _Hard_Recoil_generated_phi; // from last SmearHardRecoil_Method_B
  double _Hard_Recoil_smeared_pT, _Hard_Recoil_smeared_phi; // from last SmearHardRecoil_Method_B
  double _scale_HAD_A, _scale_HAD_B, _scale_HAD_C;        // for _Momentum_SmearOption_HAD==2
  bool   _Hard_Recoil_exists; // has SmearHardRecoil_Method_B been called already ?

  // hadronic calorimeter sampling and constant terms
  double _sampling_HAD, _constant_HAD;

  // true recoil direction smearing
  double _phi_smear_true_recoil_A;
  double _phi_smear_true_recoil_B;
  
  // missing Et smearing option
  int _METSmear_Option;
  
  // METx vs METy distribution from data
  TH2F *_hmetxmety;
 
  // minbias and zerobias library files
  TString _mbLibrary, _zbLibrary;
  std::vector<string> _zbLibraryvec;
 
  // scaling factor eflect the difference between underlying event contribution below electron window 
  // and the real minbias events, only used for METSmear_Option == 0, 1, 2
  double _alpha_mb_overlay;

  // # of minimum bias events and zero bias events to overlay, only used for METSmear_Option == 3
  double _alpha_mb, _alpha_zb;
  double _alpha_mb_trans;

  // Luminosity dependent smearing
  Bool_t Use_RecoilSmear_LumiDep;
  Bool_t Use_EtFlowFudge_LumiDep;
  std::vector<Int_t> RecoilSmear_LumiBins;
  std::vector<Double_t> Scale_HAD_bifurcate_A_LumiDep;
  std::vector<Double_t> Scale_HAD_bifurcate_B_LumiDep;
  std::vector<Double_t> Scale_HAD_bifurcate_Tau_LumiDep;
  std::vector<Double_t> Relsampling_HAD_bifurcate_A_LumiDep;
  std::vector<Double_t> Relsampling_HAD_bifurcate_B_LumiDep;
  std::vector<Int_t> EtFlowFudge_LumiDep;
  Bool_t Use_alpha_mb_LumiDep;
  std::vector<Int_t> alpha_mb_LumiBins;
  std::vector<Double_t> alpha_mb_LumiDep;

  // For propagation of uncertainty
  Bool_t WMass_Recoil_Templates_Shift;
  Int_t WMass_Recoil_Templates_Varying_Eigenvector;
  Int_t WMass_Recoil_Templates_Varying_Lumi_Bin;
  Double_t WMass_Recoil_Templates_Varying_Amplitude;
  std::vector<Double_t> Scale_Cov_Matrix_1;
  std::vector<Double_t> Scale_Cov_Matrix_2;
  std::vector<Double_t> Scale_Cov_Matrix_3;
  std::vector<Double_t> Resolution_Cov_Matrix_1;
  std::vector<Double_t> Resolution_Cov_Matrix_2;

  // fudge factor for "SET response"
  double _alpha_SETresponse;
  int    _SETresponse_Model;
  MySETFunction *_setfunction;  

  // Data file for Mikolaj's SET model
  TString _SETmodelDatafile;

  //Data Member for Storage of SET Lost to electron cone/s
  double _ScalarEt_cone;

  //Smeared recoil before TB effect
  double _recoilx_beforeTB, _recoily_beforeTB;


  // smeared recoil from hard component and soft component
  double _recoilX_HardComponent, _recoilY_HardComponent;
  double _recoilX_SoftComponent, _recoilY_SoftComponent;

  // smeared SET contribution from hard recoil
  double _Hard_SET_smeared;
  double _Hard_SET_expected_from_Znunu;    // expectation value from Z->nunu model
  double _Hard_SET_from_Znunu;             // smeared value from Z->nunu model
  //   double _Hard_SET_RelScale;          // latest relative scale for SET "fudging"
  //   double _Hard_SET_RelResol;          // latest relative resolution for SET "fudging"
  double _Hard_SET_Relscale_bifurcate_A;   // latest SET fudging parameter
  double _Hard_SET_Relscale_bifurcate_B;   // latest SET fudging parameter
  double _Hard_SET_Relsampling_bifurcate_A;// latest SET fudging parameter
  double _Hard_SET_Relsampling_bifurcate_B;// latest SET fudging parameter
  bool   _Hard_SET_exists;                 // has been wz_utils::Scalar_Et() called already ?

  // chosen scalar Et for recoil method 
  double _scalarEt_chosen;

  // Underlying event contribtuion to met measurement
  double _underlying;
  
  //pointer to histo_files to write histograms
  hist_files *_histos;
  bool _makeCheckSmearingPlots;

  // store metx and mety information from ascii files provided by Jan
  // also the run number, instantaneous luminosity for zerobias events
  bool _zbLibrary_is_binary;
  bool _mbLibrary_is_binary;
  double *_MBmetx, *_MBmety, *_MBset, *_ZBmetx, *_ZBmety, *_ZBset;
  int *_ZBrunNo, *_ZBevtNo;
  int *_ZBNumPV , *_ZBTickNum , *_ZBTimeLastL1Accept;
  double *_ZBinstLumi;
  int _liblines1, _liblines2;
  // read measured Z recoil file and add this to the Z or W signal
  bool _read_recoil_file;
  bool _IsRecoilpTBinningSmeared;
  bool _isCConly;
  
  int _num_recoil_pT_bins;
  std::vector<double> _recoil_pT_bin_edges;
  std::vector<double> _course_pT_bin_edges;
  std::vector<double> _Lumi_bin_edges;

  ZRecoilMethod_Util *zrecoilmethod;
  TString _recoilRootFileName;

  // photons with pT > pT_cut and well separated from electrons
  // will be treated as separate EM clusters, electron energy smearing will be applied
  // and also be used in the final missing Et calculation
  bool _merge_fsr_photons_met;
  double _minimum_pT_cut;

  int _NumLumiBins;
  std::vector<double> _instlumi_bins, _Factors_Lw_Lmb, _metx_mean, _mety_mean, _metx_sigma, _mety_sigma;
  std::vector<TF1> metx_res_vect, mety_res_vect;
  double _TB_alpha;
  double _TB_beta;
  bool   _TBmodel_patrice;

  // set parameters for TopBottom Asymmetry
  bool _Top_Bottom_Effect_Correction;
  bool _Top_Bottom_Apply_Last;
  
  //Apply Recoil Phi asymmetry to Hard Recoil Only
  bool _TBPhi_response_Hard_Only;

  //Apply Recoil Phi asymmetry to Soft Recoil Only
  bool _TBPhi_response_Soft_Only;

  // TB Asym correction option
  int _TB_Correction_Option; // 1: Sahal's  2: Hengne's
  
  // Parameters for TB_Correction_Option==2
  std::string _TB_Library;
  TFile* _ftblib;
  std::map<std::string, TH2D*> _tblib;
  
  // RCLSA: Saves state for template generation
  bool _Top_Bottom_exists[5][10][10]; 
  double _tbdmetx[5][10][10], _tbdmety[5][10][10]; 
  bool _last_tb_exists;
  double _last_tbdmetx, _last_tbdmety;
  bool _pedanticRandomRecoil;

};
inline void RecoilSmear::SetTBAsymmParameters(double alpha, double beta){_TB_alpha = alpha; _TB_beta = beta;}
inline void RecoilSmear::GetTBAsymmParameters(double& alpha, double& beta) {alpha = _TB_alpha; beta = _TB_beta;}

inline void RecoilSmear::InputLuminosity(double theLumi) {_instLumi_Z = theLumi;}


// set smearing parameters for hard component smearing
inline void RecoilSmear::SetHardSmearingParameters_MethodA(double scale_HAD, double offset_HAD, 
							   double phi_smear_true_recoil_A, double phi_smear_true_recoil_B, 
							   double constant_HAD, double sampling_HAD) {
  _scale_HAD = scale_HAD;
  _offset_HAD = offset_HAD;
  _phi_smear_true_recoil_A = phi_smear_true_recoil_A;
  _phi_smear_true_recoil_B = phi_smear_true_recoil_B;
  _constant_HAD = constant_HAD;
  _sampling_HAD = sampling_HAD;
}

inline void RecoilSmear::SetHardSmearingParameters_MethodB(double scale_HAD_bifurcate_A, double scale_HAD_bifurcate_B, double scale_HAD_bifurcate_Tau,
							   double Relsampling_HAD_bifurcate_A, double Relsampling_HAD_bifurcate_B, double Relconst_HAD_bifurcate,
							   double Reltrans_HAD_RelRespTrans, double Reltrans_HAD_RelResnTrans, double Reltrans_HAD_RelTauTrans,
							   double Relphi_HAD_bifurcate_A, double Relphi_HAD_bifurcate_B, double RelconstPhi_HAD_bifurcate) {
  // change current fudging paramters for hard recoil jet
  _scale_HAD_bifurcate_A = scale_HAD_bifurcate_A;
  _scale_HAD_bifurcate_B = scale_HAD_bifurcate_B;
  _scale_HAD_bifurcate_Tau = scale_HAD_bifurcate_Tau;
  _Relsampling_HAD_bifurcate_A = Relsampling_HAD_bifurcate_A;
  _Relsampling_HAD_bifurcate_B = Relsampling_HAD_bifurcate_B;
  _Relconst_HAD_bifurcate = Relconst_HAD_bifurcate;
  _RelRespTrans = Reltrans_HAD_RelRespTrans;
  _RelResnTrans = Reltrans_HAD_RelResnTrans;
  _RelTauTrans = Reltrans_HAD_RelTauTrans;
  _Relphi_HAD_bifurcate_A = Relphi_HAD_bifurcate_A;
  _Relphi_HAD_bifurcate_B = Relphi_HAD_bifurcate_B;
  _RelconstPhi_HAD_bifurcate = RelconstPhi_HAD_bifurcate;
  // change current fudging parameters for SET
  _Hard_SET_Relscale_bifurcate_A = scale_HAD_bifurcate_A;
  _Hard_SET_Relscale_bifurcate_B = scale_HAD_bifurcate_B;
  _Hard_SET_Relsampling_bifurcate_A = Relsampling_HAD_bifurcate_A;
  _Hard_SET_Relsampling_bifurcate_B = Relsampling_HAD_bifurcate_B;
}

inline void RecoilSmear::SetHardSmearingParameters_MethodC(double scale_HAD_A, double scale_HAD_B, double scale_HAD_C, 
						    double phi_smear_true_recoil_A, double phi_smear_true_recoil_B, 
						    double constant_HAD, double sampling_HAD) {
  _scale_HAD_A = scale_HAD_A;
  _scale_HAD_B = scale_HAD_B;
  _scale_HAD_C = scale_HAD_C;
  _phi_smear_true_recoil_A = phi_smear_true_recoil_A;
  _phi_smear_true_recoil_B = phi_smear_true_recoil_B;
  _constant_HAD = constant_HAD;
  _sampling_HAD = sampling_HAD;
}

// set smearing parameters for soft component smearing  void SetSoftSmearingParameters_MethodA(double underlying, double alpha_mb);
inline void RecoilSmear::SetSoftSmearingParameters_MethodB(double alpha_mb) {_alpha_mb_overlay = alpha_mb;}
inline void RecoilSmear::SetSoftSmearingParameters_MethodC(double alpha_mb) {_alpha_mb_overlay = alpha_mb;}
inline void RecoilSmear::SetSoftSmearingParameters_MethodD(double alpha_mb, double alpha_zb, double alpha_mb_trans) {
  _alpha_mb = alpha_mb;
  _alpha_zb = alpha_zb;
  _alpha_mb_trans = alpha_mb_trans;
}

// set and get the run number, instantaneous luminosity for PMCS event
// and also keep the index for the zerobias event so that we can access metx, mety information later
inline void RecoilSmear::setRunNoInstLumiMBZBEvtIndex(TRandom3 *dummy) {
  if(_METSmear_Option==3) {
    _MBEvtIndex = static_cast<int>(dummy->Rndm() * _liblines1);
    _ZBEvtIndex = static_cast<int>(dummy->Rndm() * _liblines2);
    _runNo = _ZBrunNo[_ZBEvtIndex];
    _evtNo = _ZBevtNo[_ZBEvtIndex];
    _NumPV = _ZBNumPV[_ZBEvtIndex];
    _TickNum = _ZBTickNum[_ZBEvtIndex];
    _TimeLastL1Accept = _ZBTimeLastL1Accept[_ZBEvtIndex];
    _instLumi = _ZBinstLumi[_ZBEvtIndex];
  } else {
    _MBEvtIndex = -1;
    _ZBEvtIndex = -1;
    _runNo = 0;
    _evtNo=0;
    _NumPV=0;
    _TickNum=0;
    _TimeLastL1Accept = 0;
    _instLumi = 0.;
  }
//   //////////////////////////////// DEBUG
//   //
//   std::cout << "setRunNoInstLumiMBZBEvtIndex(RND): _MBEvtIndex= " << _MBEvtIndex 
// 	    << ", ZBEvtIndex=" << _ZBEvtIndex << std::endl;
//   //
//   //////////////////////////////// DEBUG
}

// set the run number, instantaneous luminosity for PMCS event
// and the index for the zerobias event so that we can access metx, mety information later
inline void RecoilSmear::setRunNoInstLumiMBZBEvtIndex(int runNo, double instLumi, int MBEvtIndex, int ZBEvtIndex) {
    _MBEvtIndex = MBEvtIndex;
    _ZBEvtIndex = ZBEvtIndex;
    _runNo = runNo;
    _instLumi = instLumi;
//     //////////////////////////////// DEBUG
//     //
//     std::cout << "setRunNoInstLumiMBZBEvtIndex(EXTERNAL): _MBEvtIndex= " << _MBEvtIndex 
// 	      << ", ZBEvtIndex=" << _ZBEvtIndex << std::endl;
//     //
//     //////////////////////////////// DEBUG
}

inline void RecoilSmear::getRunNoInstLumiMBZBEvtIndex(int &runNo, double &instLumi, int &MBEvtIndex, int &ZBEvtIndex) const {
  if(_METSmear_Option==3) {
    runNo = _runNo;
    instLumi = _instLumi;
    ZBEvtIndex = _ZBEvtIndex;
    MBEvtIndex = _MBEvtIndex;
  } else {
    runNo = 0;
    instLumi = 0.;
    ZBEvtIndex = -1;
    MBEvtIndex = -1;
  }
}


inline void RecoilSmear::getRunNoEvtNoInstLumiMBZBEvtIndex(int &runNo, int &evtNo, double &instLumi, int &MBEvtIndex, int &ZBEvtIndex) const {
  if(_METSmear_Option==3) {
    runNo = _runNo;
    evtNo = _evtNo;
    instLumi = _instLumi;
    ZBEvtIndex = _ZBEvtIndex;
    MBEvtIndex = _MBEvtIndex;
  } else {
    runNo = 0;
    evtNo=0;
    instLumi = 0.;
    ZBEvtIndex = -1;
    MBEvtIndex = -1;
  }
}


// dump overlay ZB event runNo and evtNo
inline void RecoilSmear::DumpEvtID() const {
  std::cout<<"JAN retain "<<_ZBrunNo[_ZBEvtIndex]<<" "<<_ZBevtNo[_ZBEvtIndex]<<std::endl;
}

inline int RecoilSmear::GetEvtIDrun() const {
  return _ZBrunNo[_ZBEvtIndex];
}

inline int RecoilSmear::GetEvtIDevent() const {
  return _ZBevtNo[_ZBEvtIndex];
}
                                                                             
#endif
