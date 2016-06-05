/////////////////////////////////////////////////////////////////
///    File: CosmicMuAnalysis.hpp                             ///
///    Created:   Sep-08-2005 by Junjie Zhu                   ///
///    Purpose: study tracker eta and phi resolution using    ///
///             cosmic muons                                  ///
///                                                           ///
/////////////////////////////////////////////////////////////////

#ifndef COSMICMUANALYSIS_HPP
#define COSMICMUANALYSIS_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"
#include "TRandom3.h"

class CosmicMuAnalysis : public cafe::Processor {
 public:
  CosmicMuAnalysis(const char *name);
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();
  
  ClassDef(CosmicMuAnalysis, 0);
  
 private:
  
  // histograms
  hist_files _histos;
  
  int _NumCosmicCand;

  TRandom3 *_rand;
  cafe::Variables _global_vars;
};

#endif
