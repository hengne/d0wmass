#ifndef SinglePhotonAnalysis_HPP
#define SinglePhotonAnalysis_HPP

#include "cafe/Processor.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"
#include <vector>
#include <fstream>

class SinglePhotonAnalysis : public cafe::Processor {
 public:
  SinglePhotonAnalysis(const char *name);
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();
  void CaloCellPos(const int& ieta, const int& iphi, const int& ilyr, double cell_pos[3]);
  ClassDef(SinglePhotonAnalysis, 0);
  
 private:
  //debug level
  int _debugLevel;
  // histograms
  std::ofstream cellinfo;
  hist_files _histos;
  int _processed_events;
};

#endif
