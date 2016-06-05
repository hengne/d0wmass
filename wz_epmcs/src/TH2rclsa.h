#ifndef __TH2rclsa__
#define __TH2rclsa__

#include "TH2.h"
#include "TObject.h"
#include "TRandom3.h"

class TH2rclsa : public TH2D { 

 protected:

  Double_t* fYMaxima;
  Double_t* fYExpectations;
  Double_t** fYIntegrals;

  Double_t* fXMaxima;
  Double_t* fXExpectations;
  Double_t** fXIntegrals;

 public:
  
  TH2rclsa();
  TH2rclsa(const char *name,const char *title,Int_t nbinsx,Double_t xlow,Double_t xup
       ,Int_t nbinsy,Double_t ylow,Double_t yup);
  TH2rclsa(const char *name,const char *title,Int_t nbinsx,const Double_t *xbins
       ,Int_t nbinsy,Double_t ylow,Double_t yup);
  TH2rclsa(const char *name,const char *title,Int_t nbinsx,Double_t xlow,Double_t xup
       ,Int_t nbinsy,const Double_t *ybins);
  TH2rclsa(const char *name,const char *title,Int_t nbinsx,const Double_t *xbins
       ,Int_t nbinsy,const Double_t *ybins);
  TH2rclsa(const char *name,const char *title,Int_t nbinsx,const Float_t  *xbins
       ,Int_t nbinsy,const Float_t  *ybins);
  TH2rclsa(const TH2rclsa &h2);
  TH2rclsa(const TH2 &h2);
  virtual ~TH2rclsa();
  
  Double_t getRandomInX(Double_t y, TRandom* dummy=0);
  Double_t getMeanInX(Double_t y);
  Double_t getMaximumInX(Double_t y);

  Double_t getRandomInY(Double_t x, TRandom* dummy=0);
  Double_t getMeanInY(Double_t x);
  Double_t getMaximumInY(Double_t x);

  void ComputeXIntegral();
  void ComputeXMaximum();

  void ComputeYIntegral();
  void ComputeYMaximum();

  void DumpTables();

  Double_t* GetXMaxima() const;
  Double_t* GetXExpectations() const;
  Double_t** GetXIntegrals() const;

  Double_t* GetYMaxima() const;
  Double_t* GetYExpectations() const;
  Double_t** GetYIntegrals() const;

  void GetRandom2(Double_t &x, Double_t &y, TRandom* dummy=0);

  ClassDef (TH2rclsa,0);
};

#endif

