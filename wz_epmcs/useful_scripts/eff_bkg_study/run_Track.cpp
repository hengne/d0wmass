#include "Fitter.hpp"

void run_Track(){
  gROOT->LoadMacro("Fitter.cpp");

  // mass range
  double xmin = 50., xmax = 130.;

  // data
  TFile *data=new TFile("result_data_50_130.root");
  gDirectory->cd("Eff_Hist");

  const Int_t NVtx = 6;
  const Int_t NEta = 15;

  // get histogram before and after cut
  TH1D *before[NVtx][NEta], *after[NVtx][NEta];

  char name[50];
  for(int ivtx=0; ivtx<6; ivtx++) {
    for(int ieta=0; ieta<15; ieta++) {
      sprintf(name, "ZMass_vs_Eta_Before_Trk_CC_Vtx_%d_%d", ivtx, ieta);
      before[ivtx][ieta] = (TH1D *)gROOT->FindObject(name);

      sprintf(name, "ZMass_vs_Eta_After_Trk_CC_Vtx_%d_%d", ivtx, ieta);
      after[ivtx][ieta] = (TH1D *)gROOT->FindObject(name);
    }
  }

  // signal
  TFile *mc = new TFile("pmcs.root");
  gDirectory->cd("smeared");

  // get signal histogram
  TH1D *Sig_before[NVtx][NEta], *Sig_after[NVtx][NEta];
  for(int ivtx=0; ivtx<6; ivtx++) {
    for(int ieta=0; ieta<15; ieta++) {
      sprintf(name, "smeared_ZMass_vs_Eta_Before_Trk_CC_Vtx_%d_%d", ivtx, ieta);
      Sig_before[ivtx][ieta] = (TH1D *)gROOT->FindObject(name);

      sprintf(name, "smeared_ZMass_vs_Eta_After_Trk_CC_Vtx_%d_%d", ivtx, ieta);
      Sig_after[ivtx][ieta] = (TH1D *)gROOT->FindObject(name);
    }
  }

  // 1D mass histogram
  Int_t Sig_NBins = before[0][0]->GetNbinsX();
  Double_t Sig_Axis_XMin = before[0][0]->GetXaxis()->GetXmin();
  Double_t Sig_Axis_XMax = before[0][0]->GetXaxis()->GetXmax();

  // create a background histogram from the function
  TF1 *func = new TF1("func", "[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x", 0, 150);
  func -> SetParameter(0, -28900.202091);
  func -> SetParameter(1, 1544.304929);
  func -> SetParameter(2, -31.665620);
  func -> SetParameter(3, 0.317247);
  func -> SetParameter(4, -0.001565);
  func -> SetParameter(5, 0.000003054);

  TH1D *QCDBkg_before[NVtx][NEta], *QCDBkg_after[NVtx][NEta];
  for(int ihist=0; ihist<NVtx; ihist++) {
    for(int jhist=0; jhist<NEta; jhist++) {
      sprintf(name, "%s%d%s%d", "QCDBkg_before_", ihist, "_", jhist);
      QCDBkg_before[ihist][jhist] = new TH1D(name, name, Sig_NBins, Sig_Axis_XMin, Sig_Axis_XMax);

      sprintf(name, "%s%d%s%d", "QCDBkg_after_", ihist, "_", jhist);
      QCDBkg_after[ihist][jhist] = new TH1D(name, name, Sig_NBins, Sig_Axis_XMin, Sig_Axis_XMax);
    }
  }
  
  for(int ihist=0; ihist<NVtx; ihist++) {
    for(int jhist=0; jhist<NEta; jhist++) {

      for(int i=1; i<=QCDBkg_before[0][0]->GetNbinsX(); i++) {
	double center = QCDBkg_before[0][0]->GetBinCenter(i);
	
	if(center>xmin && center<xmax) {
	  double bin_min = QCDBkg_before[0][0]->GetBinLowEdge(i);
	  double bin_max = bin_min + QCDBkg_before[0][0]->GetBinWidth(i);	
	  double integral = func->Integral(bin_min, bin_max);
	  
	  QCDBkg_before[ihist][jhist] -> SetBinContent(i, integral);
	  QCDBkg_before[ihist][jhist] -> SetBinError(i, TMath::Sqrt(integral));
	  QCDBkg_after[ihist][jhist] -> SetBinContent(i, integral);
	  QCDBkg_after[ihist][jhist] -> SetBinError(i, TMath::Sqrt(integral));
	}
	
      } // for all bins
    }
  } // for all QCD background histograms

  //
  // fitter
  //
  Fitter fitter;
  for(int ivtx=0; ivtx<NVtx; ivtx++) {    
    for(int ieta=0; ieta<NEta; ieta++) {    

      if(before[ivtx][ieta]->Integral()>0. && Sig_before[ivtx][ieta]->Integral()>0.) {
	cout<<"Before For histogram "<<ivtx<<" "<<ieta<<endl;

	fitter.Update(before[ivtx][ieta], Sig_before[ivtx][ieta], QCDBkg_before[ivtx][ieta], xmin, xmax);
	fitter.FitMass();
	fitter.Compare();      
	//	fitter.GetDataSignalBkg(data_entry_before[i], mc_entry_before[i], bkg_entry_before[i]);
      }
      
      if(after[ivtx][ieta]->Integral()>0. && Sig_after[ivtx][ieta]->Integral()>0.) {

	cout<<"After For histogram "<<ivtx<<" "<<ieta<<endl;

	fitter.Update(after[ivtx][ieta], Sig_after[ivtx][ieta], QCDBkg_after[ivtx][ieta], xmin, xmax);
	fitter.FitMass();
	fitter.Compare();      
	//	fitter.GetDataSignalBkg(data_entry_after[i], mc_entry_after[i], bkg_entry_after[i]);
      }
    }
  } // for each histogram

}
