#ifndef FITTER_HPP
#define FITTER_HPP

#include "TROOT.h"
#include "TH1.h"
#include "TF1.h"
#include "TMath.h"
#include "TMinuit.h"

#include <string>

class Fitter {
public:
  
  // xmin and xmax is the range over which the fitting
  // function is to be defined. To make things easier, 
  // if xmax == xmin, the ranges are set to match those
  // of the histogram.
  Fitter();
  void Update(TH1 *hdata, TH1 *hsig, TH1 *hbkg, double xmin, double xmax, double step=0.0001);
  virtual ~Fitter();
  void FitMass();
  void MinuitFit();
  void Compare();
  void GetDataSignalBkg(double &data, double &mc, double &bkg, double& mcerr);

private:

};

#endif
