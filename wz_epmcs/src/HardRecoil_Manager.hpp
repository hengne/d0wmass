#ifndef __HardRecoil_Manager_hpp__
#define __HardRecoil_Manager_hpp__

#include "PParameterReader.hpp"
#include "TH2rclsa.h"
#include "PMCSRecoil.hpp"

#include "TMath.h"
#include "TRandom3.h"
#include "TF1.h"
#include "TH1D.h"

#include <vector>

class HardRecoil_Manager {

  int ptnbins;
  std::vector<double> ptbins;
  std::vector<TH2rclsa*> resp_pdf;
  std::vector<TH2rclsa*> resp_zbset_pdf;
  std::vector<TH2rclsa*> set_ut_pdf;
  TH2rclsa* phi_pdf;

  TH1D* etflow_binned3;
  TH1D* etflow_binned4;  

   std::vector<TH2rclsa*> resp_pdf0;
  std::vector<TH2rclsa*> resp_zbset_pdf0;

  std::vector<TH2rclsa*> resp_pdf1;
  std::vector<TH2rclsa*> resp_zbset_pdf1;
 
  std::vector<TH2rclsa*> resp_pdf2;
  std::vector<TH2rclsa*> resp_zbset_pdf2; 

  std::vector<TH2rclsa*> resp_pdf3;
  std::vector<TH2rclsa*> resp_zbset_pdf3;
 
  std::vector<TH2rclsa*> resp_pdf4;
  std::vector<TH2rclsa*> resp_zbset_pdf4;
 
  std::vector<TH2rclsa*> resp_pdf5;
  std::vector<TH2rclsa*> resp_zbset_pdf5;

  std::vector<TH2rclsa*> resp_zbset_pdf6;

  int ptnbinsset;
  std::vector<double> ptbinsset;


  int  luminbins;
  std::vector<double> lumibins;
  int  dphinbins;
  std::vector<double> dphibins;
  
  int  zphirespnbins; 
  std::vector<double> zphirespbins;
  
  std::vector<double> zphirespA;
  std::vector<double> zphirespB;
  std::vector<double> zphirespC;
  std::vector<double> zphirespD;
  std::vector<double> zphirespMean;
  
  bool run3bool, run4bool;
  bool flipped;
  bool zbsetmodel;
  
  double response, expected;
  double deltaPhi;
  double set, set_expected;

  PMCSRecoil znunu_recoil;
  PMCSRecoil smeared_recoil;
  

public:
  
  HardRecoil_Manager();
  HardRecoil_Manager(const char* parameter_filename);
  ~HardRecoil_Manager();
  void FlipRecoil(double truepT, double truePhi, double ZBset, double lumi, TRandom* dummy = 0);

  void SmearRecoil(double truepT, double truePhi, double ZBset, double lumi,
		   double Relscale_HAD_bifurcate_A = 1.0, 
		   double Relscale_HAD_bifurcate_B = 0.0,
		   double Relscale_HAD_bifurcate_Tau = 4.0,
		   double Relsampling_HAD_bifurcate_A = 1.0, 
		   double Relsampling_HAD_bifurcate_B = 0.0,
		   double Reltrans_HAD_RelRespTrans = 1.0, 
		   double Reltrans_HAD_RelResnTrans = 1.0, 
		   double Reltrans_HAD_RelTauTrans = 1.0,
		   double Relphi_HAD_bifurcate_A = 1.0, 
		   double Relphi_HAD_bifurcate_B = 0.0,
		   int EtFlowCorrection = 0,
		   bool use_external_information = false,
		   double external_resolution = 0.0,
		   double external_deltaphi = 0.0);

  double applyEtFlow(int option, double truePt, double lumi, double sm_phi, double RelResp = 1.0);

  PMCSRecoil GetZnunuRecoil() const { return znunu_recoil; }
  PMCSRecoil GetSmearedRecoil() const { return smeared_recoil; }
  double GetPtResolution() const { return (1.-response); }
  double GetDeltaPhi() const { return deltaPhi; }
  double GetSET() const { return set; }
  double GetSETexpected() const { return set_expected; }

  bool isFlipped() const { return flipped; }
  void unflip() { flipped = false; }

};

#endif 
