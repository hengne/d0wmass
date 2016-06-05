#ifndef __TF2jan__
#define __TF2jan__

#include "TF2.h"

class TF2jan : public TF2 { 

 protected:

  Double_t* fExpectations;     //![fNpy]

 public:

  TF2jan();
  TF2jan(const char *name, const char *formula, Double_t xmin=0, Double_t xmax=1,
	 Double_t ymin=0, Double_t ymax=1);
  TF2jan(const char *name, void *fcn, Double_t xmin=0, Double_t xmax=1, 
	 Double_t ymin=0, Double_t ymax=1, Int_t npar=0);
  TF2jan(const char *name, Double_t (*fcn)(Double_t *, Double_t *), 
	 Double_t xmin=0, Double_t xmax=1, Double_t ymin=0, Double_t ymax=1, Int_t npar=0);
  TF2jan(const TF2jan &f2);
  ~TF2jan();
  void DumpIntegralTable();
  void InitialiseExpectations();
  Double_t getMeanInX(Double_t y);

};

#endif

