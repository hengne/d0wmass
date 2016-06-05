///////////////////////////////////////////////////////////////////
///    File: EMSelector.hpp                                     ///
///    Created: J. Zhu March 3, 2005                            ///
///                                                             ///
///    Purpose: code used to select good EM candidates          ///
///                                                             ///
///////////////////////////////////////////////////////////////////
#ifndef EMSELECTOR_HPP
#define EMSELECTOR_HPP

#include "cafe/Processor.hpp"
#include "cafe/Event.hpp"
#include "wmass_util/CAFEMObj.hpp"

class EMSelector:public cafe::Processor {
  
 public:
  
  EMSelector(const char *name);
  virtual ~EMSelector();
  
  // extract good EM clusters
  void extract(cafe::Event& event);
  
  // recalculate EM cluster properties for different primary vertex
  void applyCorrection(cafe::Event& event, float vtx_old[3], float vtx_new[3]);

  // put pointers to event
  void putPointers(cafe::Event& event);
  
  // clean up useless pointers from last event
  // should be called at the beginning of extract
  void cleanObjects();
  
  std::vector<CAFEMObj*> getProbeEMObjs() const;
  std::vector<CAFEMObj*> getGoodEMObjs() const;
  
 private:
  // debug level
  int _debugLevel;
  
  // study phimod
  bool _studyPhiMod;

  //MC Study
  bool _MCStudy;

  //Use Track Phi for Fiducial cuts.
  bool _useTrackFiducial;

  //Only Use electron with Type==11
  bool _preselTrk;
 
  // study uparallel efficiency
  bool _uParaEffStudy;

  // which collection of cafe EM objects ?
  bool _nonStdEMobjs;
  std::string _nameEMobjs;

  // detector eta cut
  float _DetEtaCC, _DetEtaEC1, _DetEtaEC2;
  
  // pT cuts
  float _ElecPtCut, _ElecPtCut_Probe;

  // emfrac, isolation and hmatrix cuts
  float _EMFracCut, _IsoCut, _HM7Cut, _HM8Cut;

  // truth match ?
  bool _truthMatchEMs;

  // study QCD background
  bool _QCDBkgStudy;
  float _InvertHM7Cut, _InvertHM8Cut;

  bool _makeEfficStudyFile;

  bool _goodsameasprobe;
  
  //
  // vector of pointers to selected EM objects
  // NOTE: NEED TO DELETE THEM TO AVOID MEMORY LEAK
  //
  
  // good EM clusters
  std::vector<CAFEMObj*> _good_emobjs;
  
  // probe EM clusters
  std::vector<CAFEMObj*> _probe_emobjs;
 
  bool TrackPhiFiducial(CAFEMObj* emobj, cafe::Event& event);
  EMClusterPosCorr *_emclusposcorr;

  
 public:
  ClassDef(EMSelector, 0);
};

inline std::vector<CAFEMObj*> EMSelector::getProbeEMObjs() const {return _probe_emobjs;}
inline std::vector<CAFEMObj*> EMSelector::getGoodEMObjs() const {return _good_emobjs;}

#endif // EMSELECTOR_HPP
