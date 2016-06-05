#include "Fitter.hpp"

void run_Presel(){
  gROOT->LoadMacro("Fitter.cpp");

  // mass range
  double xmin = 50., xmax = 130.;

  // data
  TFile *data=new TFile("result_data_50_130.root");
  gDirectory->cd("Eff_Hist");

  const Int_t NBins = 31;
  const Int_t NBins_1D = 60;

  // get histogram before cut
  TH2D *before = (TH2D *)gROOT->FindObject("ZMass_vs_DetEta_Before_Presel_CC");
  TH2D *after = (TH2D *)gROOT->FindObject("ZMass_vs_DetEta_After_Presel_CC");

  Int_t NBins_X = before->GetNbinsX();
  Double_t Axis_XMin = before->GetXaxis()->GetXmin();
  Double_t Axis_XMax = before->GetXaxis()->GetXmax();

  if(NBins_X != NBins) {
    cout<<"NBins="<<NBins<<" while NBins_X="<<NBins_X<<" make sure they are the same"<<endl;
    exit;
  }

  Int_t NBins_Y = before->GetNbinsY();
  Double_t Axis_YMin = before->GetYaxis()->GetXmin();
  Double_t Axis_YMax = before->GetYaxis()->GetXmax();

  cout<<"HMx bin "<<NBins_X<<" from "<<Axis_XMin<<" to "<<Axis_XMax<<endl;
  cout<<"Mass bin "<<NBins_Y<<" from "<<Axis_YMin<<" to "<<Axis_YMax<<endl;

  // 1D histogram
  TH1D *before_mass[NBins], *after_mass[NBins], *diff_mass[NBins];
  double variable[NBins], variable_err[NBins];

  char name[50];
  for (int xbin = 0; xbin < NBins_X; xbin ++){
    sprintf(name, "%s%d", "before_", xbin);
    before_mass[xbin] = new TH1D(name, name, NBins_Y, Axis_YMin, Axis_YMax);
    sprintf(name, "%s%d", "after_", xbin);
    after_mass[xbin] = new TH1D(name, name, NBins_Y, Axis_YMin, Axis_YMax);
    sprintf(name, "%s%d", "diff_", xbin);
    diff_mass[xbin] = new TH1D(name, name, NBins_Y, Axis_YMin, Axis_YMax);

    variable[xbin] = before->GetXaxis()->GetBinCenter(xbin);
    variable_err[xbin] = 0.;

    for(int ybin=0; ybin < NBins_Y; ybin ++) {
      before_mass[xbin] -> SetBinContent(ybin, before->GetBinContent(xbin, ybin));
      after_mass[xbin] -> SetBinContent(ybin, after->GetBinContent(xbin, ybin));
      diff_mass[xbin] -> SetBinContent(ybin, before->GetBinContent(xbin, ybin)-after->GetBinContent(xbin, ybin));
    }
  }

  // signal
  TFile *mc = new TFile("pmcs.root");
  gDirectory->cd("smeared");
  TH2D *Sig_All = (TH2D *)gROOT->FindObject("smeared_ZMass_vs_DetEta_Before_Presel_CC");
  TH1D *Sig_before[NBins], *Sig_after[NBins];

  Int_t Sig_NBins_X = Sig_All->GetNbinsX();
  Double_t Sig_Axis_XMin = Sig_All->GetXaxis()->GetXmin();
  Double_t Sig_Axis_XMax = Sig_All->GetXaxis()->GetXmax();
  Int_t Sig_NBins_Y = before->GetNbinsY();
  Double_t Sig_Axis_YMin = before->GetYaxis()->GetXmin();
  Double_t Sig_Axis_YMax = before->GetYaxis()->GetXmax();

  if((NBins_X != Sig_NBins_X) || (NBins_Y != Sig_NBins_Y) || 
     (Axis_XMin != Sig_Axis_XMin) || (Axis_YMin != Sig_Axis_YMin) || 
     (Axis_XMax != Sig_Axis_XMax) || (Axis_YMax != Sig_Axis_YMax)) {
    cout<<"Different bin size between data and MC signal histogram, will exit now"<<endl;
    exit;
  }
  
  for (int xbin = 0; xbin < Sig_NBins_X; xbin ++){
    sprintf(name, "%s%d", "Sig_before_", xbin);
    Sig_before[xbin] = new TH1D(name, name, Sig_NBins_Y, Sig_Axis_YMin, Sig_Axis_YMax);
    sprintf(name, "%s%d", "Sig_after_", xbin);
    Sig_after[xbin] = new TH1D(name, name, Sig_NBins_Y, Sig_Axis_YMin, Sig_Axis_YMax);
    
    for(int ybin=0; ybin < Sig_NBins_Y; ybin ++) {
      Sig_before[xbin] -> SetBinContent(ybin, Sig_All->GetBinContent(xbin, ybin));
      Sig_after[xbin] -> SetBinContent(ybin, Sig_All->GetBinContent(xbin, ybin));
    }
  }

  cout<<"Sig HMx bin "<<Sig_NBins_X<<" from "<<Sig_Axis_XMin<<" to "<<Sig_Axis_XMax<<endl;
  cout<<"Sig Mass bin "<<Sig_NBins_Y<<" from "<<Sig_Axis_YMin<<" to "<<Sig_Axis_YMax<<endl;

  //
  // create a background histogram from the function
  //
  TF1 *func = new TF1("func", "[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x", Axis_YMin, Axis_YMax);
  func -> SetParameter(0, -28900.202091);
  func -> SetParameter(1, 1544.304929);
  func -> SetParameter(2, -31.665620);
  func -> SetParameter(3, 0.317247);
  func -> SetParameter(4, -0.001565);
  func -> SetParameter(5, 0.000003054);

  TH1D *QCDBkg_before[NBins], *QCDBkg_after[NBins];
  for(int ihist=0; ihist<NBins; ihist++) {
    sprintf(name, "%s%d", "QCDBkg_before_", ihist);
    QCDBkg_before[ihist] = new TH1D(name, name, Sig_NBins_Y, Sig_Axis_YMin, Sig_Axis_YMax);
    
    sprintf(name, "%s%d", "QCDBkg_after_", ihist);
    QCDBkg_after[ihist] = new TH1D(name, name, Sig_NBins_Y, Sig_Axis_YMin, Sig_Axis_YMax);
  }
  
  for(int ihist=0; ihist<NBins; ihist++) {
    for(int i=1; i<=QCDBkg_before[0]->GetNbinsX(); i++) {
      double center = QCDBkg_before[0]->GetBinCenter(i);
      
      if(center>xmin && center<xmax) {
	double bin_min = QCDBkg_before[0]->GetBinLowEdge(i);
	double bin_max = bin_min + QCDBkg_before[0]->GetBinWidth(i);	
	double integral = func->Integral(bin_min, bin_max);
	
	QCDBkg_before[ihist] -> SetBinContent(i, integral);
	QCDBkg_before[ihist] -> SetBinError(i, TMath::Sqrt(integral));
	QCDBkg_after[ihist] -> SetBinContent(i, integral);
	QCDBkg_after[ihist] -> SetBinError(i, TMath::Sqrt(integral));
      }
      
    } // for all bins
  } // for all QCD background histograms
  
  //
  // fitter
  //
  Fitter fitter;
  double diff_data[NBins], diff_mc[NBins], diff_bkg[NBins], diff_mc_err[NBins];
  double data_entry_after[NBins], mc_entry_after[NBins], bkg_entry_after[NBins], mc_err_after[NBins]; 
  double eff[NBins], eff_err[NBins], eff_withBkg[NBins], eff_err_withBkg[NBins];
  
  for(int i=0; i<NBins; i++) {
    if(after_mass[i]->Integral()>2.) {
      fitter.Update(after_mass[i], Sig_after[i], QCDBkg_after[i], xmin, xmax);
      fitter.FitMass();
      fitter.Compare();
      fitter.GetDataSignalBkg(data_entry_after[i], mc_entry_after[i], bkg_entry_after[i], mc_err_after[i]);
    }
    
    if(diff_mass[i]->Integral()>2.) {
      // no matter for signal and background shape here
      fitter.Update(diff_mass[i], Sig_before[i], QCDBkg_before[i], xmin, xmax);
      fitter.FitMass();
      fitter.Compare();
      fitter.GetDataSignalBkg(diff_data[i], diff_mc[i], diff_bkg[i], diff_mc_err[i]);
    }
    
  } // for each histogram
  
  // plot efficiency
  TCanvas *eff_canvas = new TCanvas("eff_canvas","gerrors2",200,10,700,500);
  for(int i=0; i<NBins; i++) {
    if((mc_entry_after[i]+diff_mc[i])>1.) {  // at least one entry
      eff[i] = mc_entry_after[i]/(mc_entry_after[i]+diff_mc[i]);
      eff_err[i] = sqrt(mc_entry_after[i]*mc_entry_after[i]*diff_mc_err[i]*diff_mc_err[i] +
                        diff_mc[i]*diff_mc[i]*mc_err_after[i]*mc_err_after[i])/((diff_mc[i]+mc_entry_after[i])*(diff_mc[i]+mc_entry_after[i]));
      
      eff_withBkg[i] = data_entry_after[i]/(data_entry_after[i]+diff_data[i]);
      eff_err_withBkg[i] = sqrt(data_entry_after[i]*diff_data[i]*(data_entry_after[i]+diff_data[i]))/((data_entry_after[i]+diff_data[i])*(data_entry_after[i]+diff_data[i]));
    }
  }

  // draw a frame to define the range
  TH1F *hr = eff_canvas->DrawFrame(-3., 0, 3. ,1.5);
  hr->SetXTitle("X title");
  hr->SetYTitle("Eff");
  eff_canvas->GetFrame()->SetBorderSize(12);
  
  TGraphErrors *ge = new TGraphErrors(NBins, variable, eff, variable_err, eff_err);
  ge -> SetMarkerColor(kRed);
  ge -> Draw("P");

  TGraphErrors *ge2 = new TGraphErrors(NBins, variable, eff_withBkg, variable_err, eff_err_withBkg);
  ge2 -> SetMarkerColor(kBlue);
  ge2 -> Draw("P");

  //  TGraphErrors *ge3 = new TGraphErrors(NBins_1D, variable_1D, eff_1D, variable_err_1D, eff_err_1D);
  //  ge3 -> Draw("P");

  //  eff_canvas->Update();
}
