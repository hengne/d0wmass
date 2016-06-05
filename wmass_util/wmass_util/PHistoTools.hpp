#ifndef phistotools_hpp
#define phistotools_hpp

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TRandom3.h"
#include <cmath> 
#include <iostream>
 
class PHistoTools {
  
 protected:
  PHistoTools();  
  ~PHistoTools();
  
 public:
  
  static Bool_t getBinValues(TH3F *h, Double_t x, Double_t y, Double_t z, 
			     Double_t &val, Double_t &err){
    TAxis *xa = h->GetXaxis();
    TAxis *ya = h->GetYaxis();
    TAxis *za = h->GetZaxis();
    
    Int_t bin = h->FindBin(x,y,z);
    val = h->GetBinContent(bin);
    err = h->GetBinError(bin);
    
    return kTRUE;
  };
  
  static Bool_t getBinValues(TH2F *h, Double_t x, Double_t y, Double_t &val, Double_t &err){
    TAxis *xa = h->GetXaxis();
    TAxis *ya = h->GetYaxis();
    
    Int_t bin = h->FindBin(x,y);
    val = h->GetBinContent(bin);
    err = h->GetBinError(bin);
    
    return kTRUE;
  };

  static Bool_t getBinValues(TH1D *h, Double_t x, Double_t &val, Double_t &err){
    TAxis *xa = h->GetXaxis();

    if( x < xa->GetXmin() || x > xa->GetXmax() ) {
      std::cout << "Over/Underflow for " << h->GetName() << " (min,max)="
		<< xa->GetXmin() << "," << xa->GetXmax() 
		<< " val=" << x << std::endl;
      return kFALSE;
    }

    Int_t bin = h->FindBin(x);
    val = h->GetBinContent(bin);
    err = h->GetBinError(bin);
    
    return kTRUE;
  };
  
  static Bool_t getBinValues(TH1F *h, Double_t x, Double_t &val, Double_t &err){
    TAxis *xa = h->GetXaxis();
    
    if( x < xa->GetXmin() || x > xa->GetXmax() ) {
      return kFALSE;
    }
    
    Int_t bin = h->FindBin(x);
    val = h->GetBinContent(bin);
    err = h->GetBinError(bin);
    
    return kTRUE;
  };
  
  
  static void smearByError(TH1F *h, TRandom3 *r){
    //smear each bin's content by its error. assume gaussian
    
    if(!h) return;
    
    Int_t nx = h->GetNbinsX();
    
    for(int i=1;i<=nx;i++){
      Int_t gbin=h->GetBin(i,0,0);
      Double_t v=h->GetBinContent(gbin);
      v += r->Gaus(0,h->GetBinError(gbin));
      h->SetBinContent(gbin,v);
    }
  };
  
  static void smearByError(TH2F *h, TRandom3 *r){
    //smear each bin's content by its error. assume gaussian
    
    if(!h) return;
    
    Int_t nx = h->GetNbinsX();
    Int_t ny = h->GetNbinsY();
    
    for(int i=1;i<=nx;i++){
      for(int k=1;k<=ny;k++){
	Int_t gbin=h->GetBin(i,k,0);
	Double_t v=h->GetBinContent(gbin);
	v += r->Gaus(0,h->GetBinError(gbin));
	h->SetBinContent(gbin,v);
      }
    }
  };
  
  static void smearByError(TH3F *h, TRandom3 *r){
    //smear each bin's content by its error. assume gaussian
    
    if(!h) return;
    
    Int_t nx = h->GetNbinsX();
    Int_t ny = h->GetNbinsY();
    Int_t nz = h->GetNbinsZ();
    
    for(int i=1;i<=nx;i++){
      for(int k=1;k<=ny;k++){
        for(int z=1;z<=nz;z++){
	  Int_t gbin=h->GetBin(i,k,z);
          Double_t v=h->GetBinContent(gbin);
	  v += r->Gaus(0,h->GetBinError(gbin));
	  h->SetBinContent(gbin,v);
        }
      }
    }    
  };
  
  static void applyFunc(TH1F *h, char *form){
    
    if(!h) return;
    
    TF1 func("apfunc",form,h->GetMinimum(),h->GetMaximum());
    
    Int_t nx = h->GetNbinsX();
    
    for(int i=1;i<=nx;i++){
      Int_t gbin=h->GetBin(i,0,0);
      h->SetBinContent(gbin,func.Eval(h->GetBinContent(gbin)));
      //h->SetBinError(gbin,func.Eval(h->GetBinError(gbin)));
    }
  };
  
  static double getMeanY(TH1F *hist1d){
    return hist1d->Integral(1,hist1d->GetNbinsX())/hist1d->GetNbinsX();
  };
  
  static double getRmsY(TH1F *hist1d){
    int nbins = hist1d->GetNbinsX();
    double mean = hist1d->Integral(1,nbins)/nbins;
    double sum2 = 0;
    for (int i = 1; i <= nbins; i++)
      sum2+= (hist1d->GetBinContent(i) - mean)*(hist1d->GetBinContent(i) - mean);
    return sqrt(sum2/nbins);
  };
  
};
#endif
