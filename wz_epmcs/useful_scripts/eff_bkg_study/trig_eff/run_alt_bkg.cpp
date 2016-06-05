#include "Fitter.hpp"


void run_alt_bkg(){
  gROOT->LoadMacro("Fitter.cpp");
  TPostScript *myps = new TPostScript("trig_bkgnd_2_ccec_v14.ps",111);
  // mass range
  double xmin = 50., xmax = 130.;
  
  // data
  TFile *data=new TFile("result_bkg.root");
  //gDirectory->cd("Eff_Hist");
  gDirectory->cd("ZCand_Hist");
  
  const Int_t NBins = 100;
  // get histogram before cut
  //TH2D *before = (TH2D *)gROOT->FindObject("Pt_InvMass_EM_Probe_Trig_All_CCCC");
  //TH2D *after = (TH2D *)gROOT->FindObject("Pt_InvMass_EM_Probe_Trig_Matched_CCCC");
  TH2D *bkgnd = (TH2D *)gROOT->FindObject("ZCandElecPt_V_Mass_1");
  bkgnd->RebinX(3);  //elecpt
  bkgnd->RebinY(4); //mass

  //before->RebinX();
  //after->RebinX();
  
  Int_t NBins_X = bkgnd->GetNbinsX();
  Double_t Axis_XMin = bkgnd->GetXaxis()->GetXmin();
  Double_t Axis_XMax = bkgnd->GetXaxis()->GetXmax();
  
  if(NBins_X != NBins) {
    cout<<"NBins="<<NBins<<" while NBins_X="<<NBins_X<<" make sure they are the same"<<endl;
    exit;
  }
  
  Int_t NBins_Y = bkgnd->GetNbinsY();
  Double_t Axis_YMin = bkgnd->GetYaxis()->GetXmin();
  Double_t Axis_YMax = bkgnd->GetYaxis()->GetXmax();
  cout<<"Mass bin "<<NBins_Y<<" from "<<Axis_YMin<<" to "<<Axis_YMax<<endl;
  
  // 1D histogram
  TH1D *before_mass[NBins], *after_mass[NBins], *diff_mass[NBins], *bkgnd_mass[NBins];
  double variable[NBins], variable_err[NBins];
 
  /*
  TF1 *func = new TF1("func", "[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x", Axis_YMin, Axis_YMax);
  func -> SetParameter(0, -28900.202091);
  func -> SetParameter(1, 1544.304929);
  func -> SetParameter(2, -31.665620);
  func -> SetParameter(3, 0.317247);
  func -> SetParameter(4, -0.001565);
  func -> SetParameter(5, 0.000003054);
  */
  TF1 *func = new TF1("func", "landau", Axis_YMin, Axis_YMax);

  TCanvas *ctemp;
  int npad = 1;
  char name[50];
  for (int xbin = 0; xbin < NBins_X; xbin ++){
    if (!(xbin%6)) {
      myps->NewPage();
      ctemp = new TCanvas("ctemp","ctemp",600,800);
      ctemp->Divide(2,3); 
      npad = 1;
    }
    ctemp->cd(npad); 
    npad++;

    sprintf(name, "%s%d", "bkgnd_", xbin);
    bkgnd_mass[xbin] = new TH1D(name, name, NBins_Y, Axis_YMin, Axis_YMax);
    /*sprintf(name, "%s%d", "before_", xbin);
    before_mass[xbin] = new TH1D(name, name, NBins_Y, Axis_YMin, Axis_YMax);
    sprintf(name, "%s%d", "after_", xbin);
    after_mass[xbin] = new TH1D(name, name, NBins_Y, Axis_YMin, Axis_YMax);
    sprintf(name, "%s%d", "diff_", xbin);
    diff_mass[xbin] =  new TH1D(name, name, NBins_Y, Axis_YMin, Axis_YMax);
    
    variable[xbin] = before->GetXaxis()->GetBinCenter(xbin);
    variable_err[xbin] = 0.;
    */
    for(int ybin=0; ybin < NBins_Y; ybin ++) {
      bkgnd_mass[xbin] -> SetBinContent(ybin, bkgnd->GetBinContent(xbin, ybin));
      /*before_mass[xbin] -> SetBinContent(ybin, before->GetBinContent(xbin, ybin));
      after_mass[xbin] -> SetBinContent(ybin, after->GetBinContent(xbin, ybin));
      diff_mass[xbin]-> SetBinContent(ybin, (before->GetBinContent(xbin, ybin) - after->GetBinContent(xbin, ybin)) );*/
    }
    bkgnd_mass[xbin]->Sumw2();
    bkgnd_mass[xbin]->Draw("pe");
    if (bkgnd_mass[xbin]->Integral()>30){
      bkgnd_mass[xbin]->Fit(func);
    }
    ctemp->Update();
  }

myps->Close();
return 
}

  // signal
  TFile *mc = new TFile("signal.root");
  gDirectory->cd("smeared");

  TH2D *sig2 = (TH2D *)gROOT->FindObject("smeared_hZcandMass_V_ElecPt_CCCC");
  //sig2->RebinY();
  
  Int_t NBins_X = sig2->GetNbinsY();
  Double_t Axis_XMin = sig2->GetYaxis()->GetXmin();
  Double_t Axis_XMax = sig2->GetYaxis()->GetXmax();

  if(NBins_X != NBins) {
    cout<<"NBins="<<NBins<<" while NBins_X="<<NBins_X<<" make sure they are the same"<<endl;
    exit;
  }
   
  Int_t NBins_Y = sig2->GetNbinsX();
  Double_t Axis_YMin = sig2->GetXaxis()->GetXmin();
  Double_t Axis_YMax = sig2->GetXaxis()->GetXmax();
  cout<<"Mass bin "<<NBins_Y<<" from "<<Axis_YMin<<" to "<<Axis_YMax<<endl;
  
  // 1D histogram
  TH1D *Sig_All[NBins]; 
  double variable[NBins], variable_err[NBins];
  TH1D *QCDBkg_All[NBins];
  
  char name[50];

  for (int xbin = 0; xbin < NBins_X; xbin ++){
    sprintf(name, "%s%d", "sig_", xbin);
    Sig_All[xbin] = new TH1D(name, name, NBins_Y, Axis_YMin, Axis_YMax);
    
    variable[xbin] = sig2->GetYaxis()->GetBinCenter(xbin);
    variable_err[xbin] = 0.;
    
    for(int ybin=0; ybin < NBins_Y; ybin ++) {
      Sig_All[xbin] -> SetBinContent(ybin, sig2->GetBinContent(ybin,xbin));
    }
    
  

    TF1 *func = new TF1("func", "[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x", Axis_YMin, Axis_YMax);
    func -> SetParameter(0, -28900.202091);
    func -> SetParameter(1, 1544.304929);
    func -> SetParameter(2, -31.665620);
    func -> SetParameter(3, 0.317247);
    func -> SetParameter(4, -0.001565);
    func -> SetParameter(5, 0.000003054);
    QCDBkg_All[xbin] = (TH1D *)Sig_All[xbin]->Clone();
    for(int i=1; i<=QCDBkg_All[xbin]->GetNbinsX(); i++) {
      double center = QCDBkg_All[xbin]->GetBinCenter(i);
      
      QCDBkg_All[xbin] -> SetBinContent(i, 0);
      QCDBkg_All[xbin] -> SetBinError(i, 0);
      
      if(center>xmin && center<xmax) {
	double bin_min = QCDBkg_All[xbin]->GetBinLowEdge(i);
	double bin_max = bin_min + QCDBkg_All[xbin]->GetBinWidth(i);
	
	double integral = func->Integral(bin_min, bin_max);
	QCDBkg_All[xbin] -> SetBinContent(i, integral);
	QCDBkg_All[xbin] -> SetBinError(i, TMath::Sqrt(integral));
      }
      
    } // for all bins
    
  }

  //TH1D *Sig_All = (TH1D *)gROOT->FindObject("smeared_hZcandMass_CCCC");

  //
  // fitter
  //
  Fitter fitter;
  double data_entry_before[NBins], mc_entry_before[NBins], bkg_entry_before[NBins], mc_error_before[NBins];
  double data_entry_after[NBins], mc_entry_after[NBins], bkg_entry_after[NBins], mc_error_after[NBins];
  double eff[NBins], eff_err[NBins];
  
  TCanvas *ctemp;
  int npad = 1;
  for(int i=0; i<NBins_X; i++) {  
    if (!(i%2)) {
      myps->NewPage();
      ctemp = new TCanvas("ctemp","ctemp",600,800);
      ctemp->Divide(2,2); 
      npad = 1;
    }
    cout<<"=================================Starting number "<<i<<" =============================="<<endl;
    ctemp->cd(npad); 
    // before becomes diff
    cout<<diff_mass[i]->Integral()<<" "<< Sig_All[i]->Integral()<<" "<<QCDBkg_All[i]->Integral()<<endl;
    if(diff_mass[i]->Integral()>2. && Sig_All[i]->Integral()>0. && QCDBkg_All[i]->Integral()>0.) {
      cout<<"b mass "<<diff_mass[i]->Integral()<<endl;
      fitter.Update(diff_mass[i], Sig_All[i], QCDBkg_All[i], xmin, xmax);
      fitter.FitMass();
      fitter.Compare(ctemp);    
      //myps->NewPage();
      fitter.GetDataSignalBkg(data_entry_before[i], mc_entry_before[i], bkg_entry_before[i], mc_error_before[i]);
    } else {
      diff_mass[i]->SetTitle("no fit");
      diff_mass[i]->Draw("pe");
      //Sig_All[i]->Scale(before_mass[i]->Integral()/Sig_All[i]->Integral());
      Sig_All[i]->SetLineColor(kRed);
      Sig_All[i]->SetTitle("no fit");
      Sig_All[i]->Draw("hist && same");
      data_entry_before[i]=0.;
      mc_entry_before[i]=0.;
      bkg_entry_before[i]=0.;
      mc_error_before[i]=0.;
      
    }
    npad++;
    ctemp->cd(npad);
    //Sig_All[i]->Scale(100);
    cout<<"-------------------------------------------------------------------------------------here i am"<<endl;
    cout<<after_mass[i]->Integral()<<" "<< Sig_All[i]->Integral()<<" "<<QCDBkg_All[i]->Integral()<<endl;
    if(after_mass[i]->Integral()>2. && Sig_All[i]->Integral()>0. && QCDBkg_All[i]->Integral()>0.) {
      cout<<"-------------------------------------------------------------------------------------here i am 2"<<endl;
      fitter.Update(after_mass[i], Sig_All[i], QCDBkg_All[i], xmin, xmax);
      fitter.FitMass();
      //ctemp->cd(npad);
      fitter.Compare(ctemp);
      //myps->NewPage();
      fitter.GetDataSignalBkg(data_entry_after[i], mc_entry_after[i], bkg_entry_after[i], mc_error_after[i]);
    } else {
      cout<<"-------------------------------------------------------------------------------------here i am 3"<<endl;
      after_mass[i]->SetTitle("no fit");
      after_mass[i]->Draw("pe");
      //Sig_All[i]->Scale(after_mass[i]->Integral()/Sig_All[i]->Integral());
      Sig_All[i]->SetLineColor(kRed);
      Sig_All[i]->SetTitle("no fit");
      Sig_All[i]->Draw("hist && same");
      data_entry_after[i]=0.;
      mc_entry_after[i]=0.;
      bkg_entry_after[i]=0.;
      mc_error_after[i]=0.;
      
    }
    npad++;

  } // for each histogram

  // plot efficiency
  TCanvas *eff_canvas = new TCanvas("eff","eff",600,800);


  eff_canvas->Divide(1,2);
  eff_canvas->cd(1);


  for(int i=0; i<NBins; i++) {
    if(mc_entry_before[i]>1.&&  mc_entry_after[i]>1.) {  // at least >one entry
      
      eff[i] = mc_entry_after[i]/(mc_entry_before[i]+mc_entry_after[i]);
      eff_err[i] = sqrt(mc_entry_before[i]*mc_entry_before[i]*mc_error_after[i]*mc_error_after[i]+ mc_entry_after[i]*mc_entry_after[i]*mc_error_before[i]*mc_error_before[i])/(mc_entry_before[i]+mc_entry_after[i])/(mc_entry_before[i]+mc_entry_after[i]);
      cout<<"what "<<i << " b "<<mc_entry_before[i]<<" a "<<mc_entry_after[i]<<" eff i "<<eff[i]<<" err i "<<eff_err[i] << " be "<<mc_error_before[i]<<" ae "<<mc_error_after[i]<<endl;    
      
    } else {
      eff[i] = 0;
      eff_err[i] = 0.1;
    }
  }

  
  TF1 *efffit2 = new TF1("efffit2","0.5 * [2] * (1. + TMath::Erf((x-[0])/(sqrt(2)*[1]))) + 0.* (1. + TMath::Erf((x-[4])/(sqrt(2)*[3])))",15,48 );
  efffit2->SetParameters(23.,2.0,0.4,2.0,20.);
  TGraphErrors *ge = new TGraphErrors(NBins, variable, eff, variable_err, eff_err);
  ge->GetXaxis()->SetRangeUser(10,70);
  ge->SetMarkerColor(kRed);
  ge->SetMarkerSize(2);
  ge->SetLineColor(kRed);
  ge->Fit("efffit2","RME");
  ge -> Draw("AP");
  
  eff_canvas->Update();

  eff_canvas->cd(2);

  for(int i=0; i<NBins; i++) {
    if(data_entry_before[i]>1. && data_entry_after[i]>1.) {// at least one entry
      cout<<"what 2 "<<data_entry_before[i]<<" "<<data_entry_after[i]<< " "<<i<<endl;
      eff[i] = data_entry_after[i]/(data_entry_before[i]+data_entry_after[i]);
      eff_err[i] = sqrt(data_entry_before[i]*data_entry_before[i]*mc_error_after[i]*mc_error_after[i]
			+ data_entry_after[i]*data_entry_after[i]*mc_error_before[i]*mc_error_before[i])
	/(data_entry_before[i]+data_entry_after[i])/(data_entry_before[i]+data_entry_after[i]);
    } else {
      eff[i] = 0;
      eff_err[i] = 0.1;
    }
  }
  
  TGraphErrors *de = new TGraphErrors(NBins, variable, eff, variable_err, eff_err);
  de->GetXaxis()->SetRangeUser(10,70);
  de->SetMarkerColor(kRed);
  de->SetMarkerSize(2);
  de->SetLineColor(kRed);
  de->Fit("efffit2","RME");
  de -> Draw("AP");
  
  eff_canvas->Update();


  myps->Close();
}

