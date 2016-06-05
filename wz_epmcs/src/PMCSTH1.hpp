#ifndef PMCS_TH1
#define PMCS_TH1

#ifndef ROOT_TH1
#include "TH1D.h"
#endif
#include <TROOT.h>

class PMCSTH1 : public TH1D {
  
public:
  PMCSTH1();
  PMCSTH1(const char *name,const char *title,Int_t nbinsx,Double_t xlow,Double_t xup);
  PMCSTH1(const char *name,const char *title,Int_t nbinsx,const Float_t  *xbins);
  PMCSTH1(const char *name,const char *title,Int_t nbinsx,const Double_t *xbins);
    PMCSTH1(const TVectorD &v);
    PMCSTH1(const PMCSTH1 &h1d);
    PMCSTH1(TH1D &h1d);
  virtual ~PMCSTH1();
  Double_t GetRandom(Double_t extrndm=0) const;
  ClassDef(PMCSTH1,1);  //1-Dim histograms (one double per channe   
  
};
#endif
