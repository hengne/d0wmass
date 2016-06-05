#include <iostream>
#include <sstream>

#include "Fitter.hpp"

void ChiSquare(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
Double_t _chisquare;
TH1 *_hdata, *_hsig, *_hbkg;
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
  _W1max=_hdata->Integral()/_hsig->Integral();
  _W2max=_hdata->Integral()/_hbkg->Integral();

  // check # of bins
  if ((_hdata->GetNbinsX() != _hsig->GetNbinsX()) || 
      (_hdata->GetNbinsX() != _hbkg->GetNbinsX())) {
    std::cerr << "Different bin size"<<endl;
    exit(1);
  }

  
  
} // function

Fitter::~Fitter() {
  //myps.Close();
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
 
void Fitter::Compare(TCanvas *ctemp) {
  
  //TCanvas *c = new TCanvas();
  _hdata -> SetMarkerColor(2);
  _hdata -> SetMarkerSize(0.6);
  _hdata -> Draw("pe");


  _hsig -> Scale(_W1);
  cout<<"w1 "<<_W1<<" w1 err "<<_W1err<<" w2 "<<_W2<<" w2 err "<<_W2err<<endl;

  TH1D *pbkg = (TH1D *)(_hbkg->Clone("pbkg"));
  TH1D *mbkg = (TH1D *)(_hbkg->Clone("mbkg"));
  
  _hbkg -> Scale(_W2);
  
  double entries_sig = _hsig->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  double entries_data = _hdata->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  double entries_bkg = _hbkg->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));  
  cout<<"Bkg fraction between ["<<_xmin<<", "<<_xmax<<"] GeV = "<<entries_bkg/entries_data<<endl;
  cout<<"entries data "<<entries_data<<" entries bkg "<<entries_bkg<<" entries sig mc "<< entries_sig<<endl;

  TH1D *sig_bkg = (TH1D *)(_hsig->Clone());
  for(int i=1; i<=sig_bkg->GetNbinsX(); i++) {
    sig_bkg -> SetBinContent(i, 0);
    sig_bkg -> SetBinError(i, 0);
    
    double center = _hsig->GetBinCenter(i);    
    if(center>60. && center<120.) {
      double entry = _hsig->GetBinContent(i) + _hbkg->GetBinContent(i);
      
      sig_bkg -> SetBinContent(i, entry);
      sig_bkg -> SetBinError(i, sqrt(entry));
    }
    
  }
  
  pbkg -> Scale((_W2+_W2err));
  pbkg -> SetFillColor(kBlue);
  pbkg -> Draw("hist && same");

  _hbkg -> SetFillColor(kGreen);
  _hbkg -> Draw("hist && same");

  mbkg -> Scale((_W2-_W2err));
  mbkg -> SetFillColor(kRed);
  mbkg -> Draw("hist && same");

  sig_bkg -> SetMarkerColor(4);
  sig_bkg -> SetMarkerSize(0.6);
  sig_bkg -> SetLineColor(kRed);
  sig_bkg -> Draw("hist && same");
  
  ctemp->Update();

  char *name_file = _hdata->GetName();
  string aaa = name_file;
  string eps_file_name = aaa+".eps";
  //c->Print(eps_file_name.c_str());
  
  //delete c;
}

void Fitter::GetDataSignalBkg(double &data, double &mc, double &bkg, double &mcerr) {
  data = _hdata -> Integral(_hdata->GetXaxis()->FindBin(70), _hdata->GetXaxis()->FindBin(110));
  bkg = _hbkg->Integral(_hdata->GetXaxis()->FindBin(70), _hdata->GetXaxis()->FindBin(110));  
  mc = data-bkg;
  if (_W1>0.0000000001){
    mcerr = _W1err*mc/_W1;
  } else {
    mcerr = 1000*_W1err;  //over estimates in general
  }
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
  //gMinuit->mnparm(0, "Sig", _W1, _step,0,0,ierflg);
  
  // Now ready for minimization step
  gMinuit->mnexcm("MIGRAD", arglist ,0,ierflg);
  
  // Print results
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  gMinuit->mnstat(amin, edm, errdef, nvpar, nparx, icstat);
  gMinuit->mnprin(3, amin);
  
  //gMinuit->mnexcm("MINOS", arglist ,0,ierflg);
  for(int i=0; i<1; i++)
    {
      gMinuit -> GetParameter(i, _W1, _W1err);
      cout<<"Parameter fit  "<<i<<" value "<<_W1<<" err "<<_W1err<<endl;
    }
  
  delete gMinuit;
  
  //calculate bkg error:
  double entries_mc = _hsig->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  double entries_bkg = _hbkg->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  _W2err = _W1err*entries_mc/entries_bkg;

  return amin;
}

void ChiSquare(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag) {
  Double_t chisq = 0;
  Double_t delta;
  Double_t n1,n2,n3,error1,error2,error3;
  
  double entries_data = _hdata->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  double entries_mc = _hsig->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  double entries_bkg = _hbkg->Integral(_hdata->GetXaxis()->FindBin(_xmin), _hdata->GetXaxis()->FindBin(_xmax));
  
  // let bkg+signal = data
  cout<<" entries data "<< entries_data<<" par0 "<<par[0]<<" entires mc "<<entries_mc<<" entries bkg "<<entries_bkg<< endl;
  double bkg_scale = (entries_data - par[0]*entries_mc)/entries_bkg;

  cout<<"For signal scale "<<par[0]<<" bkg scale "<<bkg_scale<<endl;

  for(int i=0; i<_hdata->GetNbinsX(); i++) {
    double center = _hdata->GetBinCenter(i+1);

    if(center>_xmin && center<_xmax) {
      n1=_hsig->GetBinContent(i+1);
      n2=_hbkg->GetBinContent(i+1);
      n3=_hdata->GetBinContent(i+1);
      error1=_hsig->GetBinError(i+1);
      error2=_hbkg->GetBinError(i+1);      
      error3=_hdata->GetBinError(i+1);
            
      //T = the signal plus background we are comparing to data. 
      double T = (n1*par[0]+n2*bkg_scale);
      // we need the error in T. 
      // it is the sqrt(err(S)2 + err(B)2)
      // err(S) is the error on the number of scaled signal events
      // it is the error on the orgional number of events multiplied by the scale w1. 
      double errorS = error1*par[0];
      // err(B) is the error on the number of scaled background events
      // it is the error on the orgional number of background events multiplied by the scale w2. 
      // but w2 is a derived quantity from w1 and the n1, n2, n3. it has an uncertainty too. 
      // the w2 error is complicated. we neglect correlations. 
      double w2err = sqrt( error1*error1*par[0]*par[0]/n2/n2 + error2*error2*(n3-par[0]*n1)*(n3-par[0]*n1)/n2/n2/n2/n2 + error3*error3/n2/n2 ); //+ correlations
      // then we can write err(B) as 
      double errorB = sqrt(bkg_scale*bkg_scale*error2*error2 +  n2*n2*w2err*w2err);
      // again we have ignored correlations.
      // finally err(T) is
      double errorT = sqrt(errorS*errorS + errorB*errorB);
      
      if(error3==0) error3=1.;
      delta  = (T-n3)/sqrt(error3*error3+errorT*errorT);
      chisq += delta*delta;
    }
  }  // loop over all bins
  
  
  _W1 = par[0];
  _W2 = bkg_scale;

  _chisquare = chisq;

  f = chisq;
  return;
}
