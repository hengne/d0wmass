#ifndef MUSELECTOR_HPP
#define MuSELECTOR_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "cafe/Event.hpp"
#include "wmass_util/CAFMuon.hpp"

class MuSelector:public cafe::Processor {
  
 public:
  
  MuSelector(const char *name);
  virtual ~MuSelector();
  
  // extract good EM clusters
  void extract(cafe::Event& event);
  
  // recalculate EM cluster properties for different primary vertex
  void applyCorrection(cafe::Event& event, float vtx_old[3], float vtx_new[3]);
 
  // put pointers to event
  void putPointers(cafe::Event& event);
 
  // clean up useless pointers from last event
  // should be called at the beginning of extract
  void cleanObjects();
 
  std::vector<CAFMuon*> getGoodMuons() const;
 
 private:

  // debug level 
  int _debugLevel;

  //
  // vector of pointers to selected EM objects
  // NOTE: NEED TO DELETE THEM TO AVOID MEMORY LEAK
  //

  // good muons
  std::vector<CAFMuon*> _good_muons;

  cafe::Variables _muon_vars;

 public:
  ClassDef(MuSelector, 0);
};

inline std::vector<CAFMuon*> MuSelector::getGoodMuons() const {return _good_muons;}

#endif
