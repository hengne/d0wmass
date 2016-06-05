#ifndef INC_ZMUANALYSIS
#define INC_ZMUANALYSIS

#include "PMCSEvent.hpp"
#include "MuSmear.hpp"
#include "hist_files.hpp"
#include "PMCSZMuCand.hpp"

#include "TH1.h"
#include "TH2.h"
#include "TRandom3.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include <vector>
#include <string>

class ZMuAnalysis {

 public:

  // Constructor/Destructor
  ZMuAnalysis(TString parameter_filename);
  ~ZMuAnalysis();

  void ReadParameters(TString parameter_filename);  
  void analyzeEvent(PMCSEvent& event, TRandom3 *dummy);
  void momentumScaleStudy(PMCSEvent& event, TRandom3 *dummy);
  void jobSummary();

 private:
  // output file name
  TString _zmumufilename;

  // debug and Event counter
  bool _debug;
  int _ntotal ;

  // event weight
  bool _reweight;

  // MuSmear
  MuSmear *_musmear;

  // parameters
  double _CutMuPT;

  // Histograms
  hist_files _histos;

  // study momentum scale
  bool _momentumScaleStudy;

  // step size for A, B, C
  double _step_A, _step_B, _step_C;
};

#endif // INC_ZMUANALYSIS
