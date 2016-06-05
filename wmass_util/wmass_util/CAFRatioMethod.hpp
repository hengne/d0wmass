#ifndef RMETHOD_HPP
#define RMETHOD_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <TVector2.h>
#include "tmb_tree/TMBTrack.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"
class TH1D;
class TH2D;
class TH1F;
class TF1;
class TDirectory;
class CAFZCand;
class CAFMet;
class TFile;
class CAFEMObj;
class CAFTrack;
class CAFMet;
class EfficiencyCorrection;
class RatioMaker;
using std::string;
class CAFRatioMethod {
public:
  CAFRatioMethod(const char *name);
  virtual ~CAFRatioMethod();
  void CAFRatioMethod::Analyze(CAFZCand &ZCand, CAFMet &met, int Triglist, Double_t instlumi ,TVector2 recoil_vect, Int_t Selector);
  void terminate(TFile* root_file, string directory_name="", bool debug=false);
  ClassDef(CAFRatioMethod, 0);
  
private:
  int CAFRatioMethod::MakeW(const CAFEMObj *elec1, const CAFEMObj *elec2, const TMBTrack*trk1, const TMBTrack* trk2, Double_t instlumi,TVector2 &recoil_vect, CAFMet &met,int  Trigger_flag);
  void Init();
 
  int _debugLevel;  
  Double_t _Mz;
  std::vector<Double_t> _Mw; //!
  std::vector<TF1*> _weightfunc;
  std::vector<TF1*> _ptfunc;
  
  Bool_t _ELCorr;
  Bool_t _DoPositive;
  Bool_t _DoNegative;
  Bool_t _MixCharge;
  Bool_t _smooth_reweight;
  Bool_t _UParaCorr;

  Double_t  _PtCut;
  Double_t  _METCut;
  Double_t  _etaCC;
  Double_t  _etaECLow;
  Double_t  _etaECHigh;
  Double_t  _ZMassCutHigh;
  Double_t  _WMassCutHigh;
  Double_t  _MtCutHigh;
  Double_t  _ZMassCutLow;
  Double_t  _WMassCutLow;
  Double_t _MtCutLow;
  Int_t    _npoints;
  Double_t _BosonPtCut;
  
  Double_t _alpha;
  Double_t _beta;
  Double_t _betaW;
  Double_t _sigma;
  Double_t _Mw_smooth;
  
  Double_t _Delta_ZSUP_CC;
  Double_t _Delta_ZSUP_EC;
  
  //real electron energy that is outside of the electron cone
  Double_t _EnergyLeakage_CC;
  Double_t _EnergyLeakage_EC;
  TH1F* _hEt_ThirteenTowers[13][13]; 
  TF1* _fc5;
  


  

  std::vector<TH1D*> pt_ratio;//!
  std::vector<TH1D*> m_ratio;//!
  std::vector<TH2D*> y_ratio;//!
  std::vector<TH2D*> y_ratio2;//!
  
  
  std::vector<TDirectory *> _reweightDir_m;//!
  std::vector<TDirectory *> _reweightDir_pt;//!
  std::vector<TDirectory *> _reweightDir_y;//!
  EfficiencyCorrection *_effcor; //!
  RatioMaker *_RMaker;
  TFile *Ratiofile2;
  std::vector<hist_files*> _histos;
  
};

#endif
