#ifndef INC_JPSIMUANALYSIS
#define INC_JPSIMUANALYSIS

#include "PMCSEvent.hpp"
#include "MuSmear.hpp"
#include "hist_files.hpp"
#include "PMCSJPsiMuCand.hpp"

#include "TH1.h"
#include "TH2.h"
#include "TRandom3.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include <vector>
#include <string>

class JPsiMuAnalysis {

 public:

  // Constructor/Destructor
  JPsiMuAnalysis(TString parameter_filename);
  ~JPsiMuAnalysis();

  void ReadParameters(TString parameter_filename);  
  void analyzeEvent(PMCSEvent& event, TRandom3 *dummy);
  void momentumScaleStudy(PMCSEvent& event, TRandom3 *dummy, double evtweight);
  void jobSummary();

 private:
  // output file name
  TString _jpsimumufilename;

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

  // Data/MC J/Psi pT, eta ratio
  TH2F *_pT_eta_ratio;

  // step size for A, B, C
  double _step_A, _step_B, _step_C;
};

#endif // INC_JPSIMUANALYSIS
