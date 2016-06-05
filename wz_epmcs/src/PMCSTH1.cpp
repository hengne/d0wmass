#include "PMCSTH1.hpp"
#include "TMath.h"
#include "TRandom.h"
#include <iostream>
ClassImp(PMCSTH1);
//______________________________________________________________________________
PMCSTH1::PMCSTH1(): TH1D()
{
   // Constructor.

//    fDimension = 1;
//    SetBinsLength(3);
//    if (fgDefaultSumw2) Sumw2();
  ;
}

//______________________________________________________________________________
PMCSTH1::PMCSTH1(const char *name,const char *title,Int_t nbins,Double_t xlow,Double_t xup)
:TH1D(name,title,nbins,xlow,xup)
{
   //
   //    Create a 1-Dim histogram with fix bins of type double
   //    =====================================================
   //           (see TH1::TH1 for explanation of parameters)
   //
  //  fDimension = 1;
  //  TArrayD::Set(fNcells);

//    if (xlow >= xup) SetBuffer(fgBufferSize);
//    if (fgDefaultSumw2) Sumw2();
   ;
}

//______________________________________________________________________________
PMCSTH1::PMCSTH1(const char *name,const char *title,Int_t nbins,const Float_t *xbins)
: TH1D(name,title,nbins,xbins)
{
   //
   //    Create a 1-Dim histogram with variable bins of type double
   //    =====================================================
   //           (see TH1::TH1 for explanation of parameters)
   //
  //   fDimension = 1;
  // TArrayD::Set(fNcells);
  // if (fgDefaultSumw2) Sumw2();
  ;
}

//______________________________________________________________________________
PMCSTH1::PMCSTH1(const char *name,const char *title,Int_t nbins,const Double_t *xbins)
  : TH1D(name,title,nbins,xbins)
{
   //
   //    Create a 1-Dim histogram with variable bins of type double
   //    =====================================================
   //           (see TH1::TH1 for explanation of parameters)
   //
  //  fDimension = 1;
  // TArrayD::Set(fNcells);
  // if (fgDefaultSumw2) Sumw2();
  ;
}

//______________________________________________________________________________
PMCSTH1::PMCSTH1(const TVectorD &v)
: TH1D(v)
{
  ;
}

//______________________________________________________________________________
PMCSTH1::~PMCSTH1()
{
   // Destructor.
}

//_____________________________________________________________________________
PMCSTH1::PMCSTH1(const PMCSTH1 &h1d) : TH1D(h1d)
{
   // Constructor.

   ((PMCSTH1&)h1d).Copy(*this);
}
//_____________________________________________________________________________
PMCSTH1::PMCSTH1(TH1D &h1d) : TH1D(h1d)
{
   // Constructor.

   ((PMCSTH1&)h1d).Copy(*this);
}


Double_t PMCSTH1::GetRandom(double extrndm) const
{
   // return a random number distributed according the histogram bin contents.
   // This function checks if the bins integral exists. If not, the integral
   // is evaluated, normalized to one.
   // The integral is automatically recomputed if the number of entries
   // is not the same then when the integral was computed.
   // NB Only valid for 1-d histograms. Use GetRandom2 or 3 otherwise.

   if (fDimension > 1) {
      Error("GetRandom","Function only valid for 1-d histograms");
      return 0;
   }
   Int_t nbinsx = GetNbinsX();
   Double_t integral;
   if (fIntegral) {
      if (fIntegral[nbinsx+1] != fEntries) integral = ((TH1*)this)->ComputeIntegral();
   } else {
      integral = ((TH1*)this)->ComputeIntegral();
      if (integral == 0 || fIntegral == 0) return 0;
   }
   Double_t r1 =extrndm;
   if (!r1)
     r1 = gRandom->Rndm();
   //   std::cout  << "r1 = " << r1<< std::endl;
   Int_t ibin = TMath::BinarySearch(nbinsx,fIntegral,r1);
   Double_t x = GetBinLowEdge(ibin+1);
   if (r1 > fIntegral[ibin]) x +=
      GetBinWidth(ibin+1)*(r1-fIntegral[ibin])/(fIntegral[ibin+1] - fIntegral[ibin]);
   return x;
}
