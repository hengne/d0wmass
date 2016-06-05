#include "TROOT.h"
#include "TF2jan.h"
#include <iostream>
#include <cassert>

using namespace std;

TF2jan::TF2jan() : TF2() {
  fExpectations=0;
}

TF2jan::TF2jan(const char *name, const char *formula, Double_t xmin, Double_t xmax,
	       Double_t ymin, Double_t ymax) 
  : TF2(name,formula,xmin,xmax,ymin,ymax)
{
  fExpectations=0;
}

TF2jan::TF2jan(const char *name, void *fcn, Double_t xmin, Double_t xmax, 
	       Double_t ymin, Double_t ymax, Int_t npar)
  : TF2(name,fcn,xmin,xmax,ymin,ymax,npar)
{
  fExpectations=0;
}

TF2jan::TF2jan(const char *name, Double_t (*fcn)(Double_t *, Double_t *), 
	       Double_t xmin, Double_t xmax, Double_t ymin, Double_t ymax, Int_t npar) 
  : TF2(name,fcn,xmin,xmax,ymin,ymax,npar)
{
  fExpectations=0;
}

TF2jan::TF2jan(const TF2jan &f2) 
  : TF2()
{
  ((TF2jan&)f2).Copy(*this); 
}

TF2jan::~TF2jan() {
  if (fExpectations) delete[] fExpectations; 
}

void TF2jan::DumpIntegralTable() {

  if (!fIntegral) return;
  cout<<"Dumping integral grid: "<<fNpy<<" "<<fNpx<<endl;
  Int_t i,j,cell;
  cell=0;
  for (j=0;j<fNpy;j++) {
    for (i=0;i<fNpx;i++) {
      cout<<fIntegral[cell+1]<<endl;
      cell++;
    }
  }

}

void TF2jan::InitialiseExpectations() {

  // already done ?
  if (fExpectations) return;

  // are the integrals initialised ?
  if (!fIntegral) {
    Double_t x,y;
    GetRandom2(x,y);
  }

  // reserve space
  fExpectations=new Double_t[fNpy];

  // loop over all y bins and calculate expectations
  Double_t dx=(fXmax-fXmin)/fNpx;
  for (Int_t iYbin=0; iYbin<fNpy; iYbin++) {
    // calculate expectation value
    Double_t expect=0;
    Double_t sumofW=0;
    for (Int_t i=0; i<fNpx; i++) {
      Int_t theInd=iYbin*fNpx+i;
      Double_t thePos=fXmin+i*dx+0.5*dx;
      Double_t W=(fIntegral[theInd+1]-fIntegral[theInd]);
      expect+=(thePos*W);
      sumofW+=W;
    }
    expect/=sumofW;
    fExpectations[iYbin]=expect;
  }

}

Double_t TF2jan::getMeanInX(Double_t y) {

  // are the pre-chewed values ready ?
  if (!fExpectations) InitialiseExpectations();

  // figure out bin in y
  assert(y>=fYmin);
  assert(y<=fYmax);
  Double_t dy=(fYmax-fYmin)/fNpy;
  Double_t ypos=(y-fYmin)/dy;
  Int_t iYbin=(Int_t)ypos;

  // retrieve expectation value
  return fExpectations[iYbin];

}


