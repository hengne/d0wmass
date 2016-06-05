///////////////////////////////////////////////////////////////////
///    File: VtxSelector.hpp                                    ///
///    Created: J. Zhu March 3, 2005                            ///
///                                                             ///
///    Purpose: code used to extract event vertex and           ///
///             track vertex from electrons                     ///
///                                                             ///
///////////////////////////////////////////////////////////////////
#ifndef VTXSELECTOR_HPP
#define VTXSELECTOR_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "cafe/Event.hpp"
#include "wmass_util/CAFEMObj.hpp"

#include <map>

class VtxSelector:public cafe::Processor {

 public:
  
  VtxSelector(const char *name);
  virtual ~VtxSelector();
  
  // extract event vertex and track vertex from electrons
  void extract(cafe::Event& event, const std::vector<CAFEMObj*>& emobjs, int& nvtx);
  
  // get event vertex
  void EventVertex(float event_vertex[3]);

  // get track vertex
  void TrackVertex(float track_vertex[3]);

  // put pointers to event
  void putPointers(cafe::Event& event);

 private:
 
  // debug level
  int _debugLevel;

  // event vertex
  float _event_vertex[3];

  // track vertex from electrons
  float _track_vertex[3];
  
  cafe::Variables _global_vars;
  cafe::Variables _PV_vars;

 public:
  ClassDef(VtxSelector, 0);
};

inline void VtxSelector::EventVertex(float event_vertex[3]) {
  event_vertex[0] = _event_vertex[0];
  event_vertex[1] = _event_vertex[1];
  event_vertex[2] = _event_vertex[2];
}

inline void VtxSelector::TrackVertex(float track_vertex[3]) {
  track_vertex[0] = _track_vertex[0];
  track_vertex[1] = _track_vertex[1];
  track_vertex[2] = _track_vertex[2];
}

#endif // VTXSELECTOR_HPP
