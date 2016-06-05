#ifndef JPSIMUANALYSIS_HPP
#define JPSIMUANALYSIS_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"

class JPsiMuAnalysis : public cafe::Processor {
public:
    JPsiMuAnalysis(const char *name);
    void begin();
    bool processEvent(cafe::Event& event);
    void finish();
    void GetRegion(double cut1, double cut2, double cut3, double cut4, 
                   double cut5, double cut6, double cut7, double cut8,
                   double cut9, double value, int& region);

  ClassDef(JPsiMuAnalysis, 0);

 private:
  
  // histograms
  hist_files _histos;

  int _NumJPsiCand;

  cafe::Variables _global_vars;
};

#endif
