////////////////////////////////////////////////////////////////////
///    File: ObjSelector.hpp                                     ///
///    Created: J. Zhu March 3, 2005                             ///
///                                                              ///
///    Purpose:                                                  ///
///             (1) code used to loop over events and            ///
///             select interesting objects that satify           ///
///             some selection requirements                      ///
///             (2) make electron energy correction,             ///
///             vertex selection and MET calculation             ///
///             for new primary vertex                           ///
///                                                              ///
///                                                              ///
////////////////////////////////////////////////////////////////////
#ifndef OBJSELECTOR_HPP
#define OBJSELECTOR_HPP

#include "cafe/Processor.hpp"
#include "wmass_analysis/TrigObjSelector.hpp"
#include "wmass_analysis/EMSelector.hpp"
#include "wmass_analysis/MuSelector.hpp"
#include "wmass_analysis/TrkSelector.hpp"
#include "wmass_analysis/MetSelector.hpp"
#include "wmass_analysis/VtxSelector.hpp"
#include "wmass_analysis/MCSelector.hpp"
#include <map>

class ObjSelector : public cafe::Processor {
  
 public:
  ObjSelector(const char *name);
  ~ObjSelector();
  
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();

  ClassDef(ObjSelector, 0);
  
 private:

  void initialiseKillList();
  std::map<std::pair<int,int>,int> consultKillList(int run);

  // debug level
  int _debugLevel;

  // muon channel
  bool _doMuon;

  // to extract trigger objects or not
  bool _extractTriggerObjects;

  TrigObjSelector* _trigobjselector;
  EMSelector*      _emselector;
  MuSelector*      _muselector;
  TrkSelector*     _trkselector;
  MetSelector*     _metselector;
  VtxSelector*     _vtxselector;
  MCSelector*      _mcselector;

  // do MC studies
  bool _MCStudy;
  bool _dump_mctruth;
  bool _MCStudy_ZNuNu; // enables MET calculation w/o good EM objects
  bool _useMCvertex;   // substitute best vtx from d0reco with true MC vertex

  // primary vertex cut
  float _VtxCut;       // upper cut on |PVz| (or true MC) in cm
  int   _NumVtxCut;    // minimal number of reconstructed vertices in an event

  // revertexing
  bool _ReVertexing;
  float _PV_displaced_Limit;

  // exclude "SCA failures" from recoil calculation
  bool _excludeSCAfailures;
  std::map<std::pair<int,int>,std::pair<int,int> > _SCAkillList;

  // FSR cuts
  bool _cutOnLeadingFSR;
  float _LeadingFSR_ETmin;
  float _LeadingFSR_ETmax;
  float _LeadingFSR_dRmin;
  float _LeadingFSR_dRmax;
  float _LeadingFSR_xmin;
  float _LeadingFSR_xmax;
  bool _cutOnTrailingFSR;
  float _TrailingFSR_ETmin;
  float _TrailingFSR_ETmax;
  bool _cutOnFSRnPhot;
  int _FSR_nPhot_min;
  int _FSR_nPhot_max;

  // W truth cuts.
  bool _cutOnTrueWZPt; 
  float _TrueWZPtCut_Lo;
  float _TrueWZPtCut_Hi;
  bool _cutOnTrueWZPhi;
  float _TrueWZPhiCut_Lo;
  float _TrueWZPhiCut_Hi;
  bool _cutOnTrueWZMass;
  float _TrueWZMassCut_Lo;
  float _TrueWZMassCut_Hi;

  // event counter
  int _events;
  int _events_fail_vtxcut;
  int _events_fail_FSRcut;
  
};

#endif
