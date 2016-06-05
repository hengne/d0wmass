#ifndef RATIO_MAKER
#define RATIO_MAKER
#include "TH1D.h"
#include "TH2D.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TString.h"


class RatioMaker{
 public:
  RatioMaker::RatioMaker(TFile *Ratiofile, Float_t start, Float_t step, Int_t nstep);
  ~RatioMaker();
  std::vector<TDirectory *> RatioMaker::GetRatioHistos(const char * dirname);
  std::vector<TDirectory *> RatioMaker::MakeRatioHistos(std::vector<TDirectory*>& Zdir, TDirectory* Wdir, char * dirname);
  
 private:
  void  RatioMaker::ScaledRatio(TH1D *whist, TH1D*  zhist);
  void  RatioMaker::Scaled2DRatio(TH2D *whist, TH2D*  zhist);
  TFile * _outfile;
  Float_t _start;
  Float_t _step;
  Int_t _nstep;
};

#endif //    
