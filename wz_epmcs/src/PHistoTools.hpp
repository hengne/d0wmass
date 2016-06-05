#ifndef phistotools_hpp
#define phistotools_hpp

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TRandom3.h"

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

    if( x < xa->GetXmin() || x > xa->GetXmax() ||  y < ya->GetXmin() || y > ya->GetXmax() ||  z < za->GetXmin() || z > za->GetXmax()) {
      return kFALSE;
    }    

    Int_t bin = h->FindBin(x,y,z);
    val = h->GetBinContent(bin);
    err = h->GetBinError(bin);
    
    return kTRUE;
  };
 
  static Bool_t getBinValues(TH3D *h, Double_t x, Double_t y, Double_t z,
                             Double_t &val, Double_t &err){
    TAxis *xa = h->GetXaxis();
    TAxis *ya = h->GetYaxis();
    TAxis *za = h->GetZaxis();

    if( x < xa->GetXmin() || x > xa->GetXmax() ||  y < ya->GetXmin() || y > ya->GetXmax() ||  z < za->GetXmin() || z > za->GetXmax()) {
      return kFALSE;
    }

    Int_t bin = h->FindBin(x,y,z);
    val = h->GetBinContent(bin);
    err = h->GetBinError(bin);

    return kTRUE;
  };
 static Bool_t getBinValues(TH3F *h, Double_t x, Double_t y, Double_t z,
                             Double_t &val, Double_t &err, bool acceptOverflows=false){
    TAxis *xa = h->GetXaxis();
    TAxis *ya = h->GetYaxis();
    TAxis *za = h->GetZaxis();

 if (!acceptOverflows) {
    if( x < xa->GetXmin() || x > xa->GetXmax() ||  y < ya->GetXmin() || y > ya->GetXmax() ||  z < za->GetXmin() || z > za->GetXmax()) {
      return kFALSE;
    }
 }
    Int_t bin = h->FindBin(x,y,z);
    val = h->GetBinContent(bin);
    err = h->GetBinError(bin);

    return kTRUE;
  };
 
  static Bool_t getBinValues(TH2F *h, Double_t x, Double_t y, Double_t &val, Double_t &err, bool acceptOverflows=false){
    TAxis *xa = h->GetXaxis();
    TAxis *ya = h->GetYaxis();

    if (!acceptOverflows) {
      if( x < xa->GetXmin() || x > xa->GetXmax() ||  y < ya->GetXmin() || y > ya->GetXmax() ) {
	return kFALSE;
      }
    }

    Int_t bin = h->FindBin(x,y);
    val = h->GetBinContent(bin);
    err = h->GetBinError(bin);
    
    return kTRUE;
  };

  static Bool_t getBinValues(TH2D *h, Double_t x, Double_t y, Double_t &val, Double_t &err, bool acceptOverflows=false){
    TAxis *xa = h->GetXaxis();
    TAxis *ya = h->GetYaxis();

    if (!acceptOverflows) {
      if( x < xa->GetXmin() || x > xa->GetXmax() ||  y < ya->GetXmin() || y > ya->GetXmax() ) {
	return kFALSE;
      }
    }

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

  static void smearByError(TH1D *h, TRandom3 *r){
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
  

  static void smearByError(TH2D *h, TRandom3 *r){
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
 
  static void smearByError(TH3D *h, TRandom3 *r){
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
static Double_t Interpolate(TH3 *hist, Double_t x, Double_t y, Double_t z)
{
  //This method is copied from ROOT source code and modified to use variable names in PMCS code.

   // Given a point P(x,y,z), Interpolate approximates the value via trilinear interpolation
   // based on the 8 nearest bin center points ( corner of the cube surronding the points) 
   // The Algorithm is described in http://en.wikipedia.org/wiki/Trilinear_interpolation
   // The given values (x,y,z) must be between first bin center and  last bin center for each coordinate: 
   //
   //   fXAxis.GetBinCenter(1) < x  < fXaxis.GetBinCenter(nbinX)     AND
   //   fYAxis.GetBinCenter(1) < y  < fYaxis.GetBinCenter(nbinY)     AND
   //   fZAxis.GetBinCenter(1) < z  < fZaxis.GetBinCenter(nbinZ) 

  Int_t ubx = hist->GetXaxis()->FindBin(x);
   if ( x < hist->GetXaxis()->GetBinCenter(ubx) ) ubx -= 1;
   Int_t obx = ubx + 1;

   Int_t uby = hist->GetYaxis()->FindBin(y);
   if ( y < hist->GetYaxis()->GetBinCenter(uby) ) uby -= 1;
   Int_t oby = uby + 1;

   Int_t ubz = hist->GetZaxis()->FindBin(z);
   if ( z < hist->GetZaxis()->GetBinCenter(ubz) ) ubz -= 1;
   Int_t obz = ubz + 1;


//    if ( IsBinUnderflow(GetBin(ubx, uby, ubz)) ||
//         IsBinOverflow (GetBin(obx, oby, obz)) ) {
   if (ubx <=0 || uby <=0 || ubz <= 0 ||
       obx > hist->GetXaxis()->GetNbins() || oby > hist->GetYaxis()->GetNbins() || obz > hist->GetZaxis()->GetNbins() ) {
     //  cout<<"Cannot interpolate outside histogram domain."<<endl;
      return 0;
   }

   Double_t xw = hist->GetXaxis()->GetBinCenter(obx) - hist->GetXaxis()->GetBinCenter(ubx);
   Double_t yw = hist->GetYaxis()->GetBinCenter(oby) - hist->GetYaxis()->GetBinCenter(uby);
   Double_t zw = hist->GetZaxis()->GetBinCenter(obz) - hist->GetZaxis()->GetBinCenter(ubz);

   Double_t xd = (x - hist->GetXaxis()->GetBinCenter(ubx)) / xw;
   Double_t yd = (y - hist->GetYaxis()->GetBinCenter(uby)) / yw;
   Double_t zd = (z - hist->GetZaxis()->GetBinCenter(ubz)) / zw;


   Double_t v[] = { hist->GetBinContent( ubx, uby, ubz ), hist->GetBinContent( ubx, uby, obz ),
                    hist->GetBinContent( ubx, oby, ubz ), hist->GetBinContent( ubx, oby, obz ),
                    hist->GetBinContent( obx, uby, ubz ), hist->GetBinContent( obx, uby, obz ),
                    hist->GetBinContent( obx, oby, ubz ), hist->GetBinContent( obx, oby, obz ) };


   Double_t i1 = v[0] * (1 - zd) + v[1] * zd;
   Double_t i2 = v[2] * (1 - zd) + v[3] * zd;
   Double_t j1 = v[4] * (1 - zd) + v[5] * zd;
   Double_t j2 = v[6] * (1 - zd) + v[7] * zd;


   Double_t w1 = i1 * (1 - yd) + i2 * yd;
   Double_t w2 = j1 * (1 - yd) + j2 * yd;


   Double_t result = w1 * (1 - xd) + w2 * xd;
 
   return result;
};

  
};
#endif
