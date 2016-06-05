#include "TROOT.h"
#include "TH2rclsa.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TAxis.h"
#include <iostream>
#include <cassert>

#if !defined(__CINT__)
  ClassImp(TH2rclsa);
#endif

using namespace std;

Double_t* fXExpectations;     //![fNpx]
Double_t** fXIntegrals;

Double_t* fYExpectations;     //![fNpy]
Double_t** fYIntegrals;

TH2rclsa::TH2rclsa() : TH2D() {
  fXExpectations = 0;
  fXIntegrals = 0;
  fXMaxima = 0;
  fYExpectations = 0;
  fYIntegrals = 0;
  fYMaxima = 0;
}

TH2rclsa::TH2rclsa(const char *name,const char *title,Int_t nbinsx,Double_t xlow,Double_t xup
		   ,Int_t nbinsy,Double_t ylow,Double_t yup)  
  : TH2D(name,title,nbinsx,xlow,xup,nbinsy,ylow,yup) 
{
  fXExpectations = 0;
  fXIntegrals = 0;
  fXMaxima = 0;
  fYExpectations = 0;
  fYIntegrals = 0;
  fYMaxima = 0;
}

TH2rclsa::TH2rclsa(const char *name,const char *title,Int_t nbinsx,const Double_t *xbins
		   ,Int_t nbinsy,Double_t ylow,Double_t yup)
  : TH2D(name,title,nbinsx,xbins,nbinsy,ylow,yup)
{
  fXExpectations = 0;
  fXIntegrals = 0;
  fXMaxima = 0;
  fYExpectations = 0;
  fYIntegrals = 0;
  fYMaxima = 0;
}

TH2rclsa::TH2rclsa(const char *name,const char *title,Int_t nbinsx,Double_t xlow,Double_t xup
		   ,Int_t nbinsy,const Double_t *ybins)
  : TH2D(name,title,nbinsx,xlow,xup,nbinsy,ybins)
{
  fXExpectations = 0;
  fXIntegrals = 0;
  fXMaxima = 0;
  fYExpectations = 0;
  fYIntegrals = 0;
  fYMaxima = 0;
}

TH2rclsa::TH2rclsa(const char *name,const char *title,Int_t nbinsx,const Double_t *xbins
		   ,Int_t nbinsy,const Double_t *ybins)
  : TH2D(name,title,nbinsx,xbins,nbinsy,ybins)
{
  fXExpectations = 0;
  fXIntegrals = 0;
  fXMaxima = 0;
  fYExpectations = 0;
  fYIntegrals = 0;
  fYMaxima = 0;
}

TH2rclsa::TH2rclsa(const char *name,const char *title,Int_t nbinsx,const Float_t  *xbins
		   ,Int_t nbinsy,const Float_t  *ybins)
  : TH2D(name,title,nbinsx,xbins,nbinsy,ybins)
{
  fXExpectations = 0;
  fXIntegrals = 0;
  fXMaxima = 0;
  fYExpectations = 0;
  fYIntegrals = 0;
  fYMaxima = 0;
}

TH2rclsa::TH2rclsa(const TH2rclsa &h2) 
{
  ((TH2rclsa&)h2).Copy(*this);
  fXExpectations = 0;
  fXIntegrals = 0;
  fXMaxima = 0;
  fYExpectations = 0;
  fYIntegrals = 0;
  fYMaxima = 0;
}

TH2rclsa::TH2rclsa(const TH2 &h2) 
{
  ((TH2&)h2).Copy(*this);
  fXExpectations = 0;
  fXIntegrals = 0;
  fXMaxima = 0;
  fYExpectations = 0;
  fYIntegrals = 0;
  fYMaxima = 0;
}

TH2rclsa::~TH2rclsa() {

  if (fXMaxima) delete[] fXMaxima;
  if (fXExpectations) delete[] fXExpectations;
  if (fXIntegrals) {
    for (int i=0; i<GetNbinsX()+2; i++) {
      if (fXIntegrals[i]) delete[] fXIntegrals[i];
    }
    delete[] fXIntegrals;
  }

  if (fYMaxima) delete[] fYMaxima;
  if (fYExpectations) delete[] fYExpectations;
  if (fYIntegrals) {
    for (int i=0; i<GetNbinsY()+2; i++) {
      if (fYIntegrals[i]) delete[] fYIntegrals[i];
    }
    delete[] fYIntegrals;
  }

}

void TH2rclsa::ComputeXMaximum() {

  Int_t nbinsx = GetNbinsX();
  Int_t nbinsy = GetNbinsY();
  fXMaxima = new Double_t[nbinsx+2];

  Int_t binx, biny;

  Int_t yfirst  = fYaxis.GetFirst();
  Int_t ylast   = fYaxis.GetLast();

  for (binx = 1; binx <= nbinsx; binx++) {
    Double_t maximum = 0., value;
    for (biny = 1; biny <= nbinsy; biny++) {
      value = GetBinContent(binx, biny);
      if (value > maximum) maximum = value;
    }
    fXMaxima[binx] = maximum;
  }

}

void TH2rclsa::ComputeYMaximum() {

  Int_t nbinsx = GetNbinsX();
  Int_t nbinsy = GetNbinsY();
  fYMaxima = new Double_t[nbinsy+2];

  Int_t binx, biny;

  Int_t xfirst  = fXaxis.GetFirst();
  Int_t xlast   = fXaxis.GetLast();

  for (biny = 1; biny <= nbinsy; biny++) {
    Double_t maximum = 0., value;
    for (binx = 1; binx <= nbinsx; binx++) {
      value = GetBinContent(binx, biny);
      if (value > maximum) maximum = value;
    }
    fYMaxima[biny] = maximum;
  }

}

void TH2rclsa::ComputeXIntegral() {

  Int_t nbinsx, nbinsy;
  Double_t xy;
  
  nbinsx = GetNbinsX();
  nbinsy = GetNbinsY();

  fXExpectations = new Double_t[nbinsx+2];
  fXIntegrals = new Double_t*[nbinsx+2];
  for (int i=0; i<nbinsx+2; i++) fXIntegrals[i] = new Double_t[nbinsy+2];

  for (Int_t i=1; i<=nbinsx; i++) {
    fXIntegrals[i][0] = 0.0;
    xy = 0.0;
    for (Int_t j=1; j<=nbinsy; j++) {
      fXIntegrals[i][j] = fXIntegrals[i][j-1] + GetBinContent(i,j);
      xy += fYaxis.GetBinCenter(j) * GetBinContent(i,j);
    }
    fXIntegrals[i][nbinsy+1] = fEntries;
    fXExpectations[i] = xy;
  }
  for (Int_t i=1; i<=nbinsx; i++) {
    if (fXIntegrals[i][nbinsy] == 0) {
      fXIntegrals[i][nbinsy+1] = 0.;
      fXExpectations[i] = 0.;
    } else {
      fXExpectations[i] /= fXIntegrals[i][nbinsy];
      for (Int_t j=1; j<=nbinsy; j++) {
	fXIntegrals[i][j] /= fXIntegrals[i][nbinsy];
      }
    }
  }
}

void TH2rclsa::ComputeYIntegral() {


  Int_t nbinsx, nbinsy;
  Double_t xy;
  
  nbinsx = GetNbinsX();
  nbinsy = GetNbinsY();

  fYExpectations = new Double_t[nbinsy+2];
  fYIntegrals = new Double_t*[nbinsy+2];
  for (int i=0; i<nbinsy+2; i++) fYIntegrals[i] = new Double_t[nbinsx+2];

  for (Int_t i=1; i<=nbinsy; i++) {
    fYIntegrals[i][0] = 0.0;
    xy = 0.0;
    for (Int_t j=1; j<=nbinsx; j++) {
      fYIntegrals[i][j] = fYIntegrals[i][j-1] + GetBinContent(j,i);
      xy += fXaxis.GetBinCenter(j) * GetBinContent(j,i);
    }
    fYIntegrals[i][nbinsx+1] = fEntries;
    fYExpectations[i] = xy;
  }
  for (Int_t i=1; i<=nbinsy; i++) {
    if (fYIntegrals[i][nbinsx] == 0) {
      fYIntegrals[i][nbinsx+1] = 0.;
      fYExpectations[i] = 0.;
    } else {
      fYExpectations[i] /= fYIntegrals[i][nbinsx];
      for (Int_t j=1; j<=nbinsx; j++) {
	fYIntegrals[i][j] /= fYIntegrals[i][nbinsx];
      }
    }
  }
}

Double_t TH2rclsa::getMaximumInX(Double_t y) {

  Int_t bin, nbinsy;
  nbinsy = GetNbinsY();

  if (y < fYaxis.GetBinLowEdge(1)) {
    bin = 1;
  } else if (y > fYaxis.GetBinUpEdge(nbinsy)) {
    bin = nbinsy;
  } else {
    bin = fYaxis.FindBin(y);
  }

  if (!fYMaxima) ComputeYMaximum();
  return fYMaxima[bin];

}

Double_t TH2rclsa::getMaximumInY(Double_t x) {

  Int_t bin, nbinsx;
  nbinsx = GetNbinsX();

  if (x < fXaxis.GetBinLowEdge(1)) {
    bin = 1;
  } else if (x > fXaxis.GetBinUpEdge(nbinsx)) {
    bin = nbinsx;
  } else {
    bin = fXaxis.FindBin(x);
  }

  if (!fXMaxima) ComputeXMaximum();
  return fXMaxima[bin];

}

Double_t TH2rclsa::getMeanInX(Double_t y) {

  Int_t bin, nbinsy;
  nbinsy = GetNbinsY();

  if (y < fYaxis.GetBinLowEdge(1)) {
    bin = 1;
  } else if (y > fYaxis.GetBinUpEdge(nbinsy)) {
    bin = nbinsy;
  } else {
    bin = fYaxis.FindBin(y);
  }

  if (!fYExpectations) ComputeYIntegral();
  return fYExpectations[bin];

}

Double_t TH2rclsa::getMeanInY(Double_t x) {

  Int_t bin, nbinsx;
  nbinsx = GetNbinsX();

  if (x < fXaxis.GetBinLowEdge(1)) {
    bin = 1;
  } else if (x > fXaxis.GetBinUpEdge(nbinsx)) {
    bin = nbinsx;
  } else {
    bin = fXaxis.FindBin(x);
  }

  if (!fXExpectations) ComputeXIntegral();
  return fXExpectations[bin];

}

Double_t TH2rclsa::getRandomInX(Double_t y, TRandom* dummy/*=0*/) {

  if (!dummy) dummy = gRandom;

  Int_t xbin, ybin, nbinsx, nbinsy;
  nbinsx = GetNbinsX();
  nbinsy = GetNbinsY();

  if (y < fYaxis.GetBinLowEdge(1)) {
    ybin = 1;
  } else if (y > fYaxis.GetBinUpEdge(nbinsy)) {
    ybin = nbinsy;
  } else {
    ybin = fYaxis.FindBin(y);
  }

  if (!fYIntegrals) ComputeYIntegral();
  if (fYIntegrals[ybin][nbinsx+1] != fEntries) return 0;

  Double_t r1 = dummy->Rndm();
  xbin = TMath::BinarySearch(nbinsx,fYIntegrals[ybin],r1);
  Double_t x = fXaxis.GetBinLowEdge(xbin+1);
  if (r1 > fYIntegrals[ybin][xbin]) 
    x += fXaxis.GetBinWidth(xbin+1)*(r1-fYIntegrals[ybin][xbin])/(fYIntegrals[ybin][xbin+1] - fYIntegrals[ybin][xbin]);
  return x;

}

Double_t TH2rclsa::getRandomInY(Double_t x, TRandom* dummy/*=0*/) {

  if (!dummy) dummy = gRandom;

  Int_t xbin, ybin, nbinsx, nbinsy;
  nbinsx = GetNbinsX();
  nbinsy = GetNbinsY();

  if (x < fXaxis.GetBinLowEdge(1)) {
    xbin = 1;
  } else if (x > fXaxis.GetBinUpEdge(nbinsx)) {
    xbin = nbinsx;
  } else {
    xbin = fXaxis.FindBin(x);
  }

  if (!fXIntegrals) ComputeXIntegral();
  if (fXIntegrals[xbin][nbinsy+1] != fEntries) return 0;

  Double_t r1 = dummy->Rndm();
  ybin = TMath::BinarySearch(nbinsy,fXIntegrals[xbin],r1);
  Double_t y = fYaxis.GetBinLowEdge(ybin+1);
  if (r1 > fXIntegrals[xbin][ybin]) 
    y += fYaxis.GetBinWidth(ybin+1)*(r1-fXIntegrals[xbin][ybin])/(fXIntegrals[xbin][ybin+1] - fXIntegrals[xbin][ybin]);
  return y;

}

Double_t* TH2rclsa::GetXMaxima() const { return fXMaxima; }
Double_t* TH2rclsa::GetXExpectations() const { return fXExpectations; }
Double_t** TH2rclsa::GetXIntegrals() const { return fXIntegrals; }

Double_t* TH2rclsa::GetYMaxima() const { return fYMaxima; }
Double_t* TH2rclsa::GetYExpectations() const { return fYExpectations; }
Double_t** TH2rclsa::GetYIntegrals() const { return fYIntegrals; }

void TH2rclsa::DumpTables() {

  if (fYMaxima) {
    cout << " -- Maxima -- " << endl;
    for (Int_t i=1; i<=GetNbinsY(); i++)
      cout << i << " " << fYMaxima[i] << endl;
  }
  if (fYExpectations) {
    cout << " -- Expectations -- " << endl;
    for (Int_t i=1; i<=GetNbinsY(); i++)
      cout << i << " " << fYExpectations[i] << endl;
  }
  if (fYIntegrals) {
    cout << " -- Integrals -- " << endl;
    for (Int_t i=1; i<=GetNbinsY(); i++) {
      cout << i << " ";
      for (Int_t j=1; j<=GetNbinsX(); j++)
        cout << fYIntegrals[i][j] << " ";
      cout << endl;
    }
  }

}

void TH2rclsa::GetRandom2(Double_t &x, Double_t &y, TRandom* dummy/*=0*/) {
  // return 2 random numbers along axis x and y distributed according
  // the cellcontents of a 2-dim histogram

  if (!dummy) dummy = gRandom;
  Int_t nbinsx = GetNbinsX();
  Int_t nbinsy = GetNbinsY();
  Int_t nbins  = nbinsx*nbinsy;
  Double_t integral;
  if (fIntegral) {
    if (fIntegral[nbins+1] != fEntries) integral = ComputeIntegral();
  } else {
    integral = ComputeIntegral();
    if (integral == 0 || fIntegral == 0) return;
  }
  Double_t r1 = dummy->Rndm();
  Int_t ibin = TMath::BinarySearch(nbins,fIntegral,(Double_t) r1);
  Int_t biny = ibin/nbinsx;
  Int_t binx = ibin - nbinsx*biny;
  x = fXaxis.GetBinLowEdge(binx+1);
  if (r1 > fIntegral[ibin]) x +=
    fXaxis.GetBinWidth(binx+1)*(r1-fIntegral[ibin])/(fIntegral[ibin+1] - fIntegral[ibin]);
  y = fYaxis.GetBinLowEdge(biny+1) + fYaxis.GetBinWidth(biny+1)*dummy->Rndm();

}

std::ostream& operator<<(std::ostream& os, const TH2rclsa& h2) {
  
  Double_t* fYMaxima = h2.GetYMaxima();
  Double_t* fYExpectations = h2.GetYExpectations();
  Double_t** fYIntegrals = h2.GetYIntegrals();
  
  if (fYMaxima) {
    os << " -- Maxima -- " << endl;
    for (Int_t i=1; i<=h2.GetNbinsY(); i++) 
      os << i << " " << fYMaxima[i] << endl;
  }
  if (fYExpectations) {
    os << " -- Expectations -- " << endl;
    for (Int_t i=1; i<=h2.GetNbinsY(); i++) 
      os << i << " " << fYExpectations[i] << endl;
  }
  if (fYIntegrals) {
    os << " -- Integrals -- " << endl;
    for (Int_t i=1; i<=h2.GetNbinsY(); i++) {
      os << i << " ";
      for (Int_t j=1; j<=h2.GetNbinsX(); j++) 
	os << fYIntegrals[i][j] << " ";
      os << endl;
    }
  }

  return os;

}
