#ifndef ZMUANALYSIS_HPP
#define ZMUANALYSIS_HPP

#include "cafe/Processor.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"
#include "wmass_util/CAFMuon.hpp"
#include "TRandom3.h"
#include <vector>

class ZMuAnalysis : public cafe::Processor {
 public:
  ZMuAnalysis(const char *name);
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();
  void MCStudies(cafe::Event& event, std::vector<CAFMuon*>& muons);
  
  void GetRegion(double cut1, double cut2, double cut3, double cut4,
		 double cut5, double cut6, double cut7, double cut8,
		 double cut9, double value, int& region);
  
  ClassDef(ZMuAnalysis, 0);
  
 private:
  
  // histograms
  hist_files _histos;
  
  int _NumZCand;

  // MC studies
  bool _MCStudy;

  // random number
  TRandom3 *_random;
  
  // muon smearing parameters
  double _A;
  double _B;
  double _C;
  double _CNonLinear;
  double _eta_Resolution;
  double _phi_Resolution;
};

#endif
