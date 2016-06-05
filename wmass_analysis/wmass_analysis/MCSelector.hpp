///////////////////////////////////////////////////////////////////
///    File: MCSelector.hpp                                     ///
///    Created: A. Yurkewicz July 25, 2005                      ///
///                                                             ///
///    Purpose: code used to select MC objects                  ///
///                                                             ///
///////////////////////////////////////////////////////////////////
#ifndef MCSELECTOR_HPP
#define MCSELECTOR_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "cafe/Event.hpp"
#include "tmb_tree/TMBMCpart.hpp"

// sort mc objects according to pT
static bool CompareMCPt(const TMBMCpart* mcobj1, const TMBMCpart* mcobj2) {
  return (mcobj1->Pt() > mcobj2->Pt());
}

class MCSelector:public cafe::Processor {
  
 public:
  
  MCSelector(const char *name);
  virtual ~MCSelector();
  
  // extract MC info
  void extract(cafe::Event& event);

  // delete useless pointers
  void cleanObjects();

  // FSR accessors
  float LeadFSR_ET();
  float LeadFSR_dR();
  float LeadFSR_x();
  float TrailFSR_ET();
  float TrailFSR_dR();
  float TrailFSR_x();
  int FSR_nPhot();
 
  // some WZ true information
  double TrueWZPt();
  double TrueWZPhi(); // 0 to 2Pi
  double TrueWZMass();

 private:
  // debug level
  int _debugLevel;
  
  // pT cut
  double _MC_ElecPtCut;

  // do we need to find the leading FSR photon ?
  bool _selectLeadingFSR;

  //whether to merge electron and photons
  bool _addFSR;
  //whether to compute recoil from MC particles (it's slow)
  bool _computeMCRecoil;

  // special Z->nu+nu MC sample
  bool _MCStudy_ZNuNu;

  // Hacked to single electron MC
  bool _HackedBypass;

  std::vector<TMBMCpart *> _good_mc_emobjs;    // EM objects after merge
  std::vector<TMBMCpart *> _raw_mc_electrons;  // EM objects before merge
  std::vector<TMBMCpart *> _raw_mc_photons;    // Photons before merge
  std::vector<TMBMCpart *> _unmerged_mc_photons; // Unmerged Photons
  std::vector<TMBMCpart *> _good_mc_muons;     
  std::vector<TMBMCpart *> _good_mc_neutrinos; // Neutrinos from Z->nu+nu (needed by ZNuNuAnalysis)
  TMBMCpart *_WZ;                              // for W or Z boson
  TMBMCpart * _mc_recoil;                     

  float _LeadFSR_ET;
  float _LeadFSR_dR;
  float _LeadFSR_x;
  float _TrailFSR_ET;
  float _TrailFSR_dR;
  float _TrailFSR_x;
  int _FSR_nPhot;

  cafe::Variables _MCEventInfo_vars;

 public:
  ClassDef(MCSelector, 0);
};

#endif // MCSELECTOR_HPP
