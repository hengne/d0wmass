#ifndef INC_EFFICIENCYCORRECTION
#define INC_EFFICIENCYCORRECTION


#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TString.h"
#include <vector>
#include <map>

class EfficiencyCorrection {
  
public:
  
  //constructor and read in smearing parameters
  EfficiencyCorrection(const char *name);

  //destructor
  ~EfficiencyCorrection();

  // Efficiencies
  
  Double_t FullEfficiencyCorrection(Double_t TrigVer, Double_t pt_orig_e, Double_t pt_orig_nu, Double_t pt_new_e, Double_t deteta_e, Double_t deteta_nu, Double_t peta_e, Double_t peta_nu,Double_t detphi_nu,  Double_t upara_e, Double_t upara_nu);
 
private:
  //Functions
  Double_t TrigEffCorrection(Double_t TrigVer, Double_t pt_orig, Double_t pt_new);
  Double_t EMIDEffCorrection(Double_t eta, Double_t pt_orig, Double_t pt_new);
  Double_t passesEMIDEff(Double_t eta, Double_t pt);
  Double_t TrkEffCorrection(Double_t eta, Double_t pt_orig, Double_t pt_new);
  Double_t passesPhiCrackEff(Double_t detphi, Double_t deteta);
  Double_t passesPreselEff(Double_t deteta);
  Double_t EfficiencyCorrection::WpassesUParaEff(Double_t upara, Double_t deteta, Double_t peta );
  Double_t EfficiencyCorrection::ZpassesUParaEff(Double_t upara, Double_t deteta);
  int PhyEtaRegion_CC(double eta);
  
  //DataMembers
  TH1F *_hPhiCrackEff;
  TH1F *_hEMIDEff; // vs detector eta
  TH1F *_hPreselEff; // vs detector eta
 
  // simulate pT dependence of all selection efficiencies
  bool _simulate_pT_dependence;
  std::vector<float> _CCideff_pTphyEta_ParameterA, _CCideff_pTphyEta_ParameterB;
  std::vector<float> _CCtrkeff_pTphyEta_ParameterA, _CCtrkeff_pTphyEta_ParameterB;
  
  Bool_t _correctE;
  Bool_t _correctNu;
  Bool_t _CorrectPreselEff;
  Bool_t _CorrectEMIDEff;
  Bool_t _CorrectTrkEff;
  Bool_t _CorrectTriggerEff;
  Bool_t _ApplyPhiModEfficiency;
  std::map<const char*,std::vector<Double_t> > _TriggerParams; //!
  std::vector<const char*> _TriggerNames;//!

  std::vector<float> _ZUparaEffParameters;
  double _Z_u0_CC, _Z_s_CC, _Z_u0_EC, _Z_s_EC;
  bool _WUparaEffCorrection;
  bool _ZUparaEffCorrection;
  int _UparaEffCorrOption;
  int _WUparaEffCorrOption;
  std::vector<float> _WUparaEffParameters;
  double _W_u0_CC, _W_s_CC, _W_u0_EC, _W_s_EC, _W_seta_CC ;
  Double_t _etaCC;
  bool _debugLevel;
};

#endif













