#ifndef WORK_EVTREWEIGHT_HH
#define WORK_EVTREWEIGHT_HH
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "tmb_tree/TMBJet.hpp"

#include <TH1.h>
#include <TH2.h>
#include <TF1.h>

class histo_Handle;

class evtReweightManager  {
  
public:
  evtReweightManager() {;} 
  evtReweightManager(cafe::Config config); 
  ~evtReweightManager(); 

  double ZPtReweight(double m, double zpT, double rapidity);
  double PreselEffReweight(CAFEMObj* emobj); 
  double EMIDEffReweight(CAFEMObj* emobj); 
  double TrkEffReweight(CAFEMObj* emobj, double vtx); 
  double KFactor(double mass);   // DY K factor vs mass

 private:
  
  // Z pT and rapidity reweight
  TH2D *_ZPt_Y_factor;

  //
  // scale factor for efficiency reweighting
  //
  // detector eta dependence for preselection efficiency
  TH1D *_deteta_Presel_factor_CC, *_deteta_Presel_factor_EC;

  // detector eta dependence for EMID efficiency
  TH1D *_deteta_EMID_factor_CC, *_deteta_EMID_factor_EC;

  // detector eta and phi dependence for track matching efficiency (only for CC)
  TH2D *_eta_vtx_TrkMatch_factor; 
};


#endif
