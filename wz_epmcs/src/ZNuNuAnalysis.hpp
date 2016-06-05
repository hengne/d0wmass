#ifndef INC_ZNUNUANALYSIS
#define INC_ZNUNUANALYSIS

#include "PMCSEvent.hpp"
#include "hist_files.hpp"
#include "RecoilSmear.hpp"

#include "TH1.h"
#include "TH2.h"
#include "TRandom3.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include <vector>
#include <string>

class ZNuNuAnalysis {

 public:

  // Constructor/Destructor
  ZNuNuAnalysis(TString parameter_filename, TRandom3* dummy);
  ~ZNuNuAnalysis();

  void ReadParameters(TString parameter_filename);  
  void analyzeEvent(PMCSEvent& event, int nLooseNus, int nGoodNus, TRandom3 *dummy);
  void jobSummary();

  RecoilSmear *getRecoilSmear() const {return _recoilsmear;}

 private:
  // output file name
  TString _znunufilename;

  // debug and Event counter
  bool _debug;

  bool _dumpRecoilInfo;                // dump measured hadronic recoil and generated Z info to an ASCII file
  std::fstream *_znunu_out_recoil_txt; // write out: measured recoil and generated Z to a text file

  // Neutrinos cuts
  int _NuLoose_nMin;
  double _NuLoose_EtaMax;
  double _NuLoose_PtMin;
  int _NuTight_nMin;
  double _NuTight_EtaMax;
  double _NuTight_PtMin;

  // Ut cuts
  double _UtCutMin;
  double _UtCutMax;

  // Scalar Et cuts
  double _SETCutMin;
  double _SETCutMax;

  // recoil smear
  RecoilSmear *_recoilsmear;

  // random number
  TRandom3 *_random;

  // Histograms
  hist_files _histos;
};

#endif // INC_ZNUNUANALYSIS
