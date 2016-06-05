///////////////////////////////////////////////////////////////////
///    File: TrkSelector.hpp                                    ///
///    Created: J. Zhu March 3, 2005                            ///
///                                                             ///
///    Purpose: code used to select good tracks                 ///
///                                                             ///
///////////////////////////////////////////////////////////////////
#ifndef TRKSELECTOR_HPP
#define TRKSELECTOR_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "cafe/Event.hpp"
#include "wmass_util/CAFTrack.hpp"

class TrkSelector:public cafe::Processor {
  
 public:
  
  TrkSelector(const char *name);
  virtual ~TrkSelector();
  
  // extract good tracks
  void extract(cafe::Event& event);
  
  // recalculate track properties for different primary vertex
  void applyCorrection(cafe::Event& event, float vtx_old[3], float vtx_new[3]);

  // put pointers to event
  void putPointers(cafe::Event& event);
  
  // clean useless pointers from last event
  void cleanObjects();

  std::vector<CAFTrack *> getGoodTrks() const;
  
 private:
 
  // debug level
  int _debugLevel;

  // track pT cut
  float _PtCut_Trk;

  // whether track isolated
  bool _TrkIsolated;

  // track isolation requirement
  float _coneSize_Trk, _sumPtCut_Trk;

  // good tracks  
  std::vector<CAFTrack *> _good_trks;

  cafe::Variables _trk_vars;
  
 public:
  ClassDef(TrkSelector, 0);
};

inline std::vector<CAFTrack *> TrkSelector::getGoodTrks() const {return _good_trks;}

#endif // TRKSELECTOR_HPP
