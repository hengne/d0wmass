
#include <iostream>
#include <sstream>

#include "Fitter.hpp"

void ChiSquare(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
Double_t _chisquare;
TH1 *_hdata, *_hsig, *_hbkg, *_hbkg_up, *_hbkg_down;
Double_t _xmin, _xmax, _step;
Double_t _W1, _W2, _W1min, _W1max, _W2min, _W2max, _W1err, _W2err;

Fitter::Fitter() {}

// and the functions
void Fitter::Update(TH1 *hdata, TH1 *hsig, TH1 *hbkg, double xmin, double xmax, double step) {
  _hdata = hdata;
  _hsig = hsig;
  _hbkg = hbkg;

  if (xmax > xmin) {
    _xmin = xmin;
    _xmax = xmax;
  } else {
    _xmin = hist->GetXaxis()->GetXmin();
    _xmax = hist->GetXaxis()->GetXmax();
  }

  // setup global variables
  _step = step;
  _W1min = _W2min = 0.;
  _W1 = _W1min + _step;
  _W2 = _W2min + _step;

  cout<<"hdata, hsig="<<_hdata->GetName()<<" "<<_hsig->GetName()<<endl;
  cout<<"hsig, hbkg="<<_hsig->Integral()<<" "<<_hbkg->Integral()<<endl;

  double data_entry = _hdata -> Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  double sig_entry = _hsig->Integral(_hsig->GetXaxis()->FindBin(_xmin), _hsig->GetXaxis()->FindBin(_xmax));  
  double bkg_entry = _hbkg->Integral(_hbkg->GetXaxis()->FindBin(_xmin), _hbkg->GetXaxis()->FindBin(_xmax));  

  _W1max = data_entry/sig_entry;
  _W2max = data_entry/bkg_entry;

  // check # of bins
  if ((_hdata->GetNbinsX() != _hsig->GetNbinsX()) || 
      (_hdata->GetNbinsX() != _hbkg->GetNbinsX())) {
    cout<<"Data bin = "<<_hdata->GetNbinsX()<<" sig bin = "<<_hsig->GetNbinsX()<<" bkg bin = "<<_hbkg->GetNbinsX()<<endl;
    std::cerr << "Different bin size"<<endl;
    exit(1);
  }
  
} // function

Fitter::~Fitter() {
  /*
    delete *_hdata;
    delete *_hsig;
    delete *_hbkg;
  */
}

void Fitter::FitMass() {
  Double_t minvalue = MinuitFit();
  cout<<"----------------------------------------"<<endl;
  cout<<"Minimum value "<<minvalue<<endl;
  cout<<"----------------------------------------"<<endl;
}
 
void Fitter::Compare() {
  TCanvas *c = new TCanvas();
  _hdata -> SetMarkerColor(2);
  _hdata -> SetMarkerSize(0.6);
  _hdata -> Draw("pe");

  _hsig -> Scale(_W1);
  _hbkg -> Scale(_W2);

  _hbkg_up = (TH1D *)_hbkg->Clone();
  _hbkg_down = (TH1D *)_hbkg->Clone();

  double entries_data = _hdata->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  double entries_bkg = _hbkg->Integral(_hbkg->GetXaxis()->FindBin(_xmin), _hbkg->GetXaxis()->FindBin(_xmax));  
  double entries_mc = entries_data - entries_bkg;

  cout<<"Bkg fraction between ["<<_xmin<<", "<<_xmax<<"] GeV = "<<entries_bkg/entries_data<<endl;

  // error for bkg fraction
  double mcerr = _W1err*entries_mc/_W1;
  double entries_bkg_up = entries_bkg + mcerr;
  double entries_bkg_down = entries_bkg - mcerr;
  _hbkg_up -> Scale(entries_bkg_up/entries_bkg);
  _hbkg_down -> Scale(entries_bkg_down/entries_bkg);

  cout<<"Bkg = "<<entries_bkg<<" +- "<<mcerr<<endl;

  TH1D *sig_bkg = (TH1D *)(_hsig->Clone());
  for(int i=1; i<=sig_bkg->GetNbinsX(); i++) {
    sig_bkg -> SetBinContent(i, 0);
    sig_bkg -> SetBinError(i, 0);
    
    double center = _hsig->GetBinCenter(i);    
    if(center>_xmin && center<_xmax) {
      double entry = _hsig->GetBinContent(i) + _hbkg->GetBinContent(i);
      
      sig_bkg -> SetBinContent(i, entry);
      sig_bkg -> SetBinError(i, sqrt(entry));
    }
    
  }

  //  _hbkg -> SetFillColor(3);
  //  _hbkg_up -> SetFillColor(2);
  //  _hbkg_down -> SetFillColor(4);
  _hbkg_up -> Draw("hist && same");
  _hbkg -> Draw("hist && same");
  _hbkg_down -> Draw("hist && same");

  sig_bkg -> SetLineColor(4);
  sig_bkg -> SetLineWidth(2);
  sig_bkg -> SetMarkerColor(4);
  sig_bkg -> SetMarkerSize(0.6);
  sig_bkg -> Draw("hist && same");
  c->Update();  

  char *name_file = _hdata->GetName();
  string aaa = name_file;
  string eps_file_name = aaa+".eps";
  c->Print(eps_file_name.c_str());

  delete c;

  //  _hsig -> Scale(1/_W1);
  //  _hbkg -> Scale(1/_W2);

}

void Fitter::GetDataSignalBkg(double &data, double &mc, double &bkg, double& mcerr) {
  data = _hdata -> Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  bkg = _hbkg->Integral(_hbkg->GetXaxis()->FindBin(_xmin), _hbkg->GetXaxis()->FindBin(_xmax));  
  mc = data-bkg;
  mcerr = _W1err*mc/_W1;
  cout<<"Data, signal, bkg, mcerr = "<<data<<" "<<mc<<" "<<bkg<<" "<<mcerr<<endl;
}

Double_t Fitter::MinuitFit() {
  TMinuit *gMinuit = new TMinuit(1);
  gMinuit->SetFCN(ChiSquare);
  
  //settings 
  Double_t arglist[6];
  Int_t ierflg = 0;
  
  // Set starting values and step sizes for parameters
  gMinuit->mnparm(0, "Sig", _W1, _step, _W1min, _W1max,ierflg);
  
  // Now ready for minimization step
  gMinuit->mnexcm("MIGRAD", arglist ,0,ierflg);
  
  // Print results
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  gMinuit->mnstat(amin, edm, errdef, nvpar, nparx, icstat);
  gMinuit->mnprin(3, amin);

  // error for signal fraction
  for(int i=0; i<1; i++) {
    gMinuit -> GetParameter(i, _W1, _W1err);
    cout<<"Parameter fit  "<<i<<" value "<<_W1<<" err "<<_W1err<<endl;
  }
  
  delete gMinuit;
  
  return amin;
}

void ChiSquare(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag) {
  Double_t chisq = 0;
  Double_t delta;
  Double_t n1,n2,n3,error;
  
  double entries_data = _hdata->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  double entries_mc = _hsig->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  double entries_bkg = _hbkg->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  
  // let bkg+signal = data
  double bkg_scale = (entries_data - par[0]*entries_mc)/entries_bkg;
  //  cout<<"For sig scale "<<par[0]<<" bkg scale "<<bkg_scale<<endl;

  for(int i=0; i<_hdata->GetNbinsX(); i++) {
    double center = _hdata->GetBinCenter(i+1);

    if(center>_xmin && center<_xmax) {
      n1=_hsig->GetBinContent(i+1);
      n2=_hbkg->GetBinContent(i+1);
      n3=_hdata->GetBinContent(i+1);
      error=_hdata->GetBinError(i+1);

      if(error==0) error=1.;
      delta  = (n1*par[0]+n2*bkg_scale-n3)/error;
      chisq += delta*delta;
    }
  }  // loop over all bins
   
  _W1 = par[0];
  _W2 = bkg_scale;

  _chisquare = chisq;

  f = chisq;
  return;
}
