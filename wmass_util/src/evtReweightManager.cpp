/////////////////////////////////////////////////////////////////////////////
////
////   Purpose   : event reweight for full MC events
////               Z pT reweight, and also efficiency reweight
////
/////////////////////////////////////////////////////////////////////////////
#include "cafe/Event.hpp"
#include <TROOT.h>
#include "wmass_util/evtReweightManager.hpp" 

using namespace std; 
using namespace cafe;
using namespace kinem;

evtReweightManager::evtReweightManager(Config config) {
  // parameters or histograms for Z pT reweight
  const string ZPtRatioHist = string("ZPtReweightHistName").c_str();
  string temp = config.get(ZPtRatioHist, "wmass_analysis/config/Data_FullMC_Reweight/Resbos_Pythia_ZPt_Y_Ratio.C");
  string temp2 = string(".x ") + temp;
  gROOT->ProcessLine(temp2.c_str());

  // note that this histogram is rapidity vs log10(pT)
  _ZPt_Y_factor = (TH2D *)gROOT->FindObject("_h_zypt");

  // detector eta dependence for preselection efficiency
  const string PreselRatioHist_CC = string("PreselReweightHistName_CC").c_str();
  temp = config.get(PreselRatioHist_CC, "wmass_analysis/config/Data_FullMC_Reweight/PreID_CC_a_DetEta_scale_factor.cpp");
  temp2 = string(".x ") + temp;
  gROOT->ProcessLine(temp2.c_str());
  _deteta_Presel_factor_CC = (TH1D *)gROOT->FindObject("PreID_CC_a_DetEta_scale_factor");

  const string PreselRatioHist_EC = string("PreselReweightHistName_EC").c_str();
  temp = config.get(PreselRatioHist_EC, "wmass_analysis/config/Data_FullMC_Reweight/PreID_EC_a_DetEta_scale_factor.cpp");
  temp2 = string(".x ") + temp;
  gROOT->ProcessLine(temp2.c_str());
  _deteta_Presel_factor_EC = (TH1D *)gROOT->FindObject("PreID_EC_a_DetEta_scale_factor");

  // detector eta dependence for EMID efficiency
  const string EMIDRatioHist_CC = string("EMIDReweightHistName_CC").c_str();
  temp = config.get(EMIDRatioHist_CC, "wmass_analysis/config/Data_FullMC_Reweight/EMID_CC_a_DetEta_scale_factor.cpp");
  temp2 = string(".x ") + temp;
  gROOT->ProcessLine(temp2.c_str());
  _deteta_EMID_factor_CC = (TH1D *)gROOT->FindObject("EMID_CC_a_DetEta_scale_factor");

  const string EMIDRatioHist_EC = string("EMIDReweightHistName_EC").c_str();
  temp = config.get(EMIDRatioHist_EC, "wmass_analysis/config/Data_FullMC_Reweight/EMID_EC_a_DetEta_scale_factor.cpp");
  temp2 = string(".x ") + temp;
  gROOT->ProcessLine(temp2.c_str());
  _deteta_EMID_factor_EC = (TH1D *)gROOT->FindObject("EMID_EC_a_DetEta_scale_factor");

  // detector eta and phi dependence for track matching efficiency (only for CC)
  const string TrkMatchRatioHist = string("TrkMatchReweightHistName").c_str();
  temp = config.get(TrkMatchRatioHist, "wmass_analysis/config/Data_FullMC_Reweight/EMTRK_10_a_phyEta_vtxz_scale_factor.cpp");
  temp2 = string(".x ") + temp;
  gROOT->ProcessLine(temp2.c_str());
  _eta_vtx_TrkMatch_factor = (TH2D *)gROOT->FindObject("EMTRK_10_a_phyEta_vtxz_scale_factor");
}

evtReweightManager::~evtReweightManager() {
}

double evtReweightManager::ZPtReweight(double m, double ZpT, double rapidity) {
  double f = 1.;

  // use histogram determined from Resbos/Pythia
  double logZpT = TMath::Log10(ZpT);
  Int_t bin = _ZPt_Y_factor->FindBin(rapidity, logZpT);
  f = _ZPt_Y_factor->GetBinContent(bin);

  return f;
}

double evtReweightManager::PreselEffReweight(CAFEMObj *emobj) {
  double f = 1.;

  Int_t bin = -999;
  double deteta = emobj->CalDetectorEta();
  if(fabs(deteta)<1.1) {
    Int_t bin = _deteta_Presel_factor_CC->FindBin(deteta);
    f = _deteta_Presel_factor_CC -> GetBinContent(bin);
  } else {
    Int_t bin = _deteta_Presel_factor_EC->FindBin(deteta);
    f = _deteta_Presel_factor_EC -> GetBinContent(bin);
  }

  return f;
}

double evtReweightManager::EMIDEffReweight(CAFEMObj *emobj) {
  double f = 1.;

  Int_t bin = -999;
  double deteta = emobj->CalDetectorEta();
  if(fabs(deteta)<1.1) {
    Int_t bin = _deteta_EMID_factor_CC->FindBin(deteta);
    f = _deteta_EMID_factor_CC -> GetBinContent(bin);
  } else {
    Int_t bin = _deteta_EMID_factor_EC->FindBin(deteta);
    f = _deteta_EMID_factor_EC -> GetBinContent(bin);
  }

  return f;
}

// only applied on CC electron
double evtReweightManager::TrkEffReweight(CAFEMObj *emobj, double vtx) {
  double f = 1.;
 
  double eta = emobj->Eta();
  double deteta = emobj->CalDetectorEta();
  double detphi = emobj->CalDetectorPhi();
  if(fabs(deteta)<1.1) {
    Int_t bin = _eta_vtx_TrkMatch_factor -> FindBin(eta, vtx);
    f = _eta_vtx_TrkMatch_factor->GetBinContent(bin);
  }
  
  return f;
}

// from Thomas Nunnemann's webpage (NNLO(NLO PDF)/LO(LO PDF)) based on CTEQ6L1/M
// http://www-clued0.fnal.gov/~nunne/cross-sections/dy_cross-sections.html
double evtReweightManager::KFactor(double mass) {
  double kfactor = 1.;

  // Thomas told me that the K-factors have been calculated for 
  // a fixed value of di-lepton mass, that means the best would 
  // be to interpolate between the points. 
  /*
  if(mass<10.)  kfactor = 1.25;
  else if(mass<20.) kfactor = 1.24;
  else if(mass<30.) kfactor = 1.26;
  else if(mass<40.) kfactor = 1.28;
  else if(mass<50.) kfactor = 1.30;
  else if(mass<75.) kfactor = 1.34;
  else if(mass<91.12) kfactor = 1.36;
  else if(mass<100.) kfactor = 1.37;
  else if(mass<150.) kfactor = 1.40;
  else if(mass<200.) kfactor = 1.41;
  else if(mass<250.) kfactor = 1.41;
  else if(mass<300.) kfactor = 1.41;
  else if(mass<400.) kfactor = 1.40;
  else if(mass<500.) kfactor = 1.39;
  else if(mass<600.) kfactor = 1.38;
  else if(mass<700.) kfactor = 1.37;
  else if(mass<800.) kfactor = 1.37;
  else if(mass<900.) kfactor = 1.37;
  else kfactor = 1.37;
  */

  double log10_mass = TMath::Log10(mass);
  kfactor = 0.496135 + 3.192614*log10_mass - 4.763325*pow(log10_mass, 2) +
            3.152890*pow(log10_mass, 3) - 0.923884*pow(log10_mass, 4) +
            0.094118*pow(log10_mass, 5) + 0.001376*pow(log10_mass, 6);
  if(mass>700.) kfactor = 1.37;   // let kfactor be constant above 700 GeV

  return kfactor;
}
