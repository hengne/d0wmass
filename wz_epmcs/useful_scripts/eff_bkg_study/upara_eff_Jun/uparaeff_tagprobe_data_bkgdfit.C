#include <TApplication.h>
#include <fstream>
#include <iostream>
#include <strstream>
#include "TRandom.h"
#include "TH1D.h";
#include "TGraph.h";
#include "TMath.h";
#include "Fitter.hpp";

using namespace std;

const int num_bins=30;
double bins[num_bins+1];
//double bins[18]={0.,25.,26.,28.,30.,32.,34.,36.,38.,40.,42.,44.,46.,48.,50.,55.,60., 100.};
//double bins[17]={0.,25.,28.,30.,32.,34.,36.,38.,40.,42.,44.,46.,48.,50.,55.,60., 100.};
//double bins[18]={0.,25.,26.,27.,28.,29.,30.,31.,32.,33.,34.,35.,36.,37.,38.,39.,40.,41.,42.,43.,44.,45.,46.,47.,48.,49.,50.,51.,55.,60.,100.};
TH1D *eff_data[15];
TH1D *eff_fast[15];
TH1D *ratio[15];

TH1D *eff_data_all;

TH1D *bkgd_tmp[15][num_bins];
TH1D *bkgd_before_tmp[15][num_bins];
TH1D *bkgd_after_tmp[15][num_bins];
TH1D *zee_tmp[15][num_bins];
TH1D *zee_spatial_tmp[15][num_bins];
TH1D *zee_diff_tmp[15][num_bins];
TH1D *signal_before_tmp[15][num_bins];
TH1D *signal_after_tmp[15][num_bins];
TH1D *signal_diff_tmp[15][num_bins];

TH1D *bkgd_tmp_all[num_bins], *bkgd_before_tmp_all[num_bins], *bkgd_after_tmp_all[num_bins];
TH1D *zee_tmp_all[num_bins], *zee_spatial_tmp_all[num_bins], *zee_diff_tmp_all[num_bins];
TH1D *signal_diff_tmp_all[num_bins], *signal_before_tmp_all[num_bins], *signal_after_tmp_all[num_bins];

TH1D *signal_before_tmp_fast[15][num_bins];
TH1D *signal_after_tmp_fast[15][num_bins];

double data_entry_before_all[num_bins], mc_entry_before_all[num_bins], bkg_entry_before_all[num_bins], mc_error_before_all[num_bins];
double data_entry_after_all[num_bins], mc_entry_after_all[num_bins], bkg_entry_after_all[num_bins], mc_error_after_all[num_bins];
double chisq1_all[num_bins], chisq2_all[num_bins];

double data_entry_before[15][num_bins], mc_entry_before[15][num_bins], bkg_entry_before[15][num_bins], mc_error_before[15][num_bins];
double data_entry_after[15][num_bins], mc_entry_after[15][num_bins], bkg_entry_after[15][num_bins], mc_error_after[15][num_bins];
double chisq1[15][num_bins], chisq2[15][num_bins];


double fitf(double *x, double *par){
  double arg=0;
  double fitval;
  if(x[0]<par[0])
    fitval=par[2];
  else
    fitval=par[2]*(1-par[1]*(x[0]-par[0]));

  return fitval;
}
TF1* func_tagprobe=new TF1("func_tagprobe", fitf, -15,15,3);

TF1 *erf= new TF1("erf","0.5*[2]*(1+TMath::Erf((x-[0])/(sqrt(2)*[1])))",0., 100.);
TF1 *logf= new TF1("logf","[0]+[1]*log(x) + [2]*x", 25., 100.);
TF1 *expf= new TF1("expf","[0]+[1]*exp(-x)",0., 100.);

const double xmin_fit=60.,, xmax_fit=120.;
TF1 *func = new TF1("func","landau", xmin_fit, xmax_fit);

double xmin = 50., xmax = 130.;

//Chebyshev *cheby=new Chebyshev(erf, 25., 100.);

Double_t cheby(Double_t *x, Double_t *par) {
  if(x[0]<60.){
    fitval=par[0] + par[1]*x[0] + par[2]*(2*x[0]*x[0]-1) + par[3]*(4*x[0]*x[0]*x[0]-3*x[0]) +
      par[4]*(8*x[0]*x[0]*x[0]*x[0]-8*x[0]*x[0]+1);
  }
  else{
    fitval=par[0] + par[1]*60. + par[2]*(2*60.*60.-1) + par[3]*(4*60.*60.*60.-3*60.) +
      par[4]*(8*60.*60.*60.*60.-8*60.*60.+1);
  }
  return fitval;
}

TF1 *func_cheby= new TF1("func_cheby", cheby, 25., 100., 5);

Double_t logfunc(Double_t *x, Double_t *par) {
  if(x[0]<600.){
    fitval=par[0] + par[1]*log(x[0])/* + par[2]*x[0]*/;
  }
  else{
    fitval=par[0] + par[1]*log(60.)/* + par[2]*60.*/;
  }
  return fitval;
}

TF1 *func_log= new TF1("func_log", logfunc, 25., 100., 2);

double p0[15], p1[15], p2[15], p3[15], p4[15];

const double limit1=60., limit2=70., limit3=110., limit4=120.;

const int factor_rebin=4;

void uparaeff_tagprobe_data_bkgdfit() {
  gROOT -> ProcessLine(".x /home/guojun/style_junjie.C");
  gStyle->SetOptFit(1);
  
  gROOT->LoadMacro("Fitter.cpp");
  
  for(int i=0; i<num_bins+1; i++){
    bins[i]=-30.+ 60.*i/num_bins;
  }
  TH2F *ZMass_V_Pt=new TH2F("ZMass_V_Pt","ZMass_V_Pt", num_bins,bins,150, 0., 150.);
  
  TFile *f0= new TFile("/work/thanagar-clued0/guojun/efficiency_pT/outputs/for_analysis_20081217/result_zupara_goodspatialcctag_newskim_20090226.root");
  
  gDirectory->cd("ZCand_Hist");
  
  const double low_x=20., high_x=100.;
  const double low_y=0.5, high_y=1. ;
  double x_min=50, x_max=90.;
  int low_bin, high_bin;
  
  eff_data_all=new TH1D("eff_data_all", "eff data all", num_bins, bins);
  
  char name_bkgd_all[60];
  sprintf(name_bkgd_all, "%s","ZCandMass_V_UPara_Bkgd");
  //sprintf(name_bkgd_all, "%s","ZCandMass_V_UPara_Bkgd_ScaleToW");
  char name_data_all[60];
  sprintf(name_data_all, "%s","ZCandMass_V_UPara_WithoutIsoHMxCut");
  //sprintf(name_data_all, "%s","ZCandMass_V_UPara_WithoutIsoHMxCut_ScaleToW");
  char name_match_data_all[60];
  sprintf(name_match_data_all, "%s","ZCandMass_V_UPara_WithIsoHMxCut_trkmatch");
  //sprintf(name_match_data_all, "%s","ZCandMass_V_UPara_WithIsoHMxCut_trkmatch_ScaleToW");
  
  TH2D *h1_data_all_2d=(TH2D *) gROOT->FindObject(name_match_data_all);
  TH2D *h2_data_all_2d=(TH2D *) gROOT->FindObject(name_data_all);
  TH2D *h_bkgd_all_2d=(TH2D *) gROOT->FindObject(name_bkgd_all);
  
//   h1_data_all_2d->RebinX(factor_rebin);
//   h2_data_all_2d->RebinX(factor_rebin);
//   h_bkgd_all_2d->RebinX(factor_rebin);
  
  TH2D *bkgd_tmp_all_2d=ZMass_V_Pt->Clone();
  TH2D *zee_tmp_all_2d=ZMass_V_Pt->Clone();
  TH2D *zee_spatial_tmp_all_2d=ZMass_V_Pt->Clone();
  
  
  bkgd_tmp_all_2d->Reset();
  zee_tmp_all_2d->Reset();
  zee_spatial_tmp_all_2d->Reset();
  
  for(int j=0;j<h_bkgd_all_2d->GetNbinsX();j++){
    for(int k=0;k<h_bkgd_all_2d->GetNbinsY();k++){
      bkgd_tmp_all_2d->Fill(h_bkgd_all_2d->GetXaxis()->GetBinCenter(j+1),h_bkgd_all_2d->GetYaxis()->GetBinCenter(k+1),h_bkgd_all_2d->GetBinContent(j+1,k+1));
      zee_tmp_all_2d->Fill(h2_data_all_2d->GetXaxis()->GetBinCenter(j+1),h2_data_all_2d->GetYaxis()->GetBinCenter(k+1),h2_data_all_2d->GetBinContent(j+1,k+1));
      zee_spatial_tmp_all_2d->Fill(h1_data_all_2d->GetXaxis()->GetBinCenter(j+1),h1_data_all_2d->GetYaxis()->GetBinCenter(k+1),h1_data_all_2d->GetBinContent(j+1,k+1));
    }
  }
  
  TH1D *ZMass_all=(TH1D *) ZMass_V_Pt->ProjectionY();
  
  for(int j=0;j<num_bins;j++){
    bkgd_tmp_all[j]=(TH1D *) ZMass_all->Clone();
    bkgd_before_tmp_all[j]=(TH1D *) ZMass_all->Clone();
    bkgd_after_tmp_all[j]=(TH1D *) ZMass_all->Clone();
    zee_tmp_all[j]=(TH1D *) ZMass_all->Clone();
    zee_spatial_tmp_all[j]=(TH1D *) ZMass_all->Clone();
    zee_diff_tmp_all[j]=(TH1D *) ZMass_all->Clone();
    

    bkgd_tmp_all[j]->Reset();
    bkgd_before_tmp_all[j]->Reset();
    bkgd_after_tmp_all[j]->Reset();
    zee_tmp_all[j]->Reset();
    zee_spatial_tmp_all[j]->Reset();    
    zee_diff_tmp_all[j]->Reset();    
  }
  
  for(int j=0;j<bkgd_tmp_all_2d->GetNbinsX();j++){
    for(int k=0;k<bkgd_tmp_all_2d->GetNbinsY();k++){
      
      bkgd_tmp_all[j]->Fill(bkgd_tmp_all_2d->GetYaxis()->GetBinCenter(k+1),bkgd_tmp_all_2d->GetBinContent(j+1,k+1));
      bkgd_before_tmp_all[j]->Fill(bkgd_tmp_all_2d->GetYaxis()->GetBinCenter(k+1),bkgd_tmp_all_2d->GetBinContent(j+1,k+1));
      bkgd_after_tmp_all[j]->Fill(bkgd_tmp_all_2d->GetYaxis()->GetBinCenter(k+1),bkgd_tmp_all_2d->GetBinContent(j+1,k+1));
      zee_tmp_all[j]->Fill(zee_tmp_all_2d->GetYaxis()->GetBinCenter(k+1),zee_tmp_all_2d->GetBinContent(j+1,k+1));
      zee_spatial_tmp_all[j]->Fill(zee_spatial_tmp_all_2d->GetYaxis()->GetBinCenter(k+1),zee_spatial_tmp_all_2d->GetBinContent(j+1,k+1));
      zee_diff_tmp_all[j]->Fill(zee_tmp_all_2d->GetYaxis()->GetBinCenter(k+1),zee_tmp_all_2d->GetBinContent(j+1,k+1) - zee_spatial_tmp_all_2d->GetBinContent(j+1,k+1));
    }
//     bkgd_tmp_all[j]->Rebin(2); 
//     bkgd_before_tmp_all[j]->Rebin(2); 
//     bkgd_after_tmp_all[j]->Rebin(2); 
//     zee_tmp_all[j]->Rebin(2);
//     zee_spatial_tmp_all[j]->Rebin(2);
//     zee_diff_tmp_all[j]->Rebin(2);
  }
  
  
  
  
  TFile *f1= new TFile("/work/thanagar-clued0/guojun/runscripts_generator/epmcs_20081222/wz_epmcs/src/result_zee_forsignalshape_cctag_CCvtxfromfullMC_foruparaeff_weighted_22.6M.root");  
  gDirectory->cd("smeared");
    

  char name_signal_before_all[60], name_signal_after_all[60];
  sprintf(name_signal_before_all, "%s","smeared_ZMass_vs_UPara_Before_CC");
  //sprintf(name_signal_before_all, "%s","smeared_ZMass_vs_UPara_Before_CC_ScaleToW");
  sprintf(name_signal_after_all, "%s","smeared_ZMass_vs_UPara_After_CC");
  //sprintf(name_signal_after_all, "%s","smeared_ZMass_vs_UPara_After_CC_ScaleToW");
  
  TH2D *h_signal_before_all_2d=(TH2D *) gROOT->FindObject(name_signal_before_all);
  TH2D *h_signal_after_all_2d=(TH2D *) gROOT->FindObject(name_signal_after_all);

//   h_signal_before_all_2d->RebinX(factor_rebin);
//   h_signal_after_all_2d->RebinX(factor_rebin);
  
  TH2D *signal_before_tmp_all_2d=ZMass_V_Pt->Clone();
  TH2D *signal_after_tmp_all_2d=ZMass_V_Pt->Clone();
  
  signal_before_tmp_all_2d->Reset();
  signal_after_tmp_all_2d->Reset();
  
  for(int j=0;j<h_bkgd_all_2d->GetNbinsX();j++){
    for(int k=0;k<h_bkgd_all_2d->GetNbinsY();k++){
      int bin_new=signal_before_tmp_all_2d->FindBin(h_signal_before_all_2d->GetXaxis()->GetBinCenter(j+1),h_signal_before_all_2d->GetYaxis()->GetBinCenter(k+1));
      
      double err_before_old=signal_before_tmp_all_2d->GetBinError(bin_new);
      double err_before_input=h_signal_before_all_2d->GetBinError(j+1,k+1);
      double err_before_new=sqrt(err_before_old*err_before_old + err_before_input*err_before_input);
      
      double err_after_old=signal_after_tmp_all_2d->GetBinError(bin_new);
      double err_after_input=h_signal_after_all_2d->GetBinError(j+1,k+1);
      double err_after_new=sqrt(err_after_old*err_after_old + err_after_input*err_after_input);
      
      signal_before_tmp_all_2d->Fill(h_signal_before_all_2d->GetXaxis()->GetBinCenter(j+1),h_signal_before_all_2d->GetYaxis()->GetBinCenter(k+1),h_signal_before_all_2d->GetBinContent(j+1,k+1));
      signal_before_tmp_all_2d->SetBinError(bin_new, err_before_new);
      signal_after_tmp_all_2d->Fill(h_signal_after_all_2d->GetXaxis()->GetBinCenter(j+1),h_signal_after_all_2d->GetYaxis()->GetBinCenter(k+1),h_signal_after_all_2d->GetBinContent(j+1,k+1));
      signal_after_tmp_all_2d->SetBinError(bin_new, err_after_new);
    }
  }
  

    TH1D *ZMass_all=(TH1D *) ZMass_V_Pt->ProjectionY();
    
    for(int j=0;j<num_bins;j++){
      signal_before_tmp_all[j]=(TH1D *) ZMass_all->Clone();          
      signal_before_tmp_all[j]->Reset();
      signal_after_tmp_all[j]=(TH1D *) ZMass_all->Clone();          
      signal_after_tmp_all[j]->Reset();
      signal_diff_tmp_all[j]=(TH1D *) ZMass_all->Clone();          
      signal_diff_tmp_all[j]->Reset();
    }

    for(int j=0;j<signal_before_tmp_all_2d->GetNbinsX();j++){
      for(int k=0;k<signal_before_tmp_all_2d->GetNbinsY();k++){
	double err_before_old=signal_before_tmp_all[j]->GetBinError(k+1);
	double err_before_input=signal_before_tmp_all_2d->GetBinError(j+1,k+1);
	double err_before_new=sqrt(err_before_old*err_before_old + err_before_input*err_before_input);

	double err_after_old=signal_after_tmp_all[j]->GetBinError(k+1);
	double err_after_input=signal_after_tmp_all_2d->GetBinError(j+1,k+1);
	double err_after_new=sqrt(err_after_old*err_after_old + err_after_input*err_after_input);


	signal_before_tmp_all[j]->Fill(signal_before_tmp_all_2d->GetYaxis()->GetBinCenter(k+1),signal_before_tmp_all_2d->GetBinContent(j+1,k+1));
	signal_after_tmp_all[j]->Fill(signal_after_tmp_all_2d->GetYaxis()->GetBinCenter(k+1),signal_after_tmp_all_2d->GetBinContent(j+1,k+1));
	signal_before_tmp_all[j]->SetBinError(k+1, err_before_new);
	signal_after_tmp_all[j]->SetBinError(k+1, err_after_new);
      }
//       signal_before_tmp_all[j]->Rebin(2);
//       signal_after_tmp_all[j]->Rebin(2);
    }



  TCanvas *ctemp=new TCanvas;
  int npad = 1;
  ctemp->Divide(1,1); 
  ctemp->cd(npad); 

  Fitter fitter;
  for(int ipt=0; ipt<num_bins; ipt++){   
    //for(int ipt=1; ipt<2; ipt++){   
    
    double eff_tmp_all=1, efferr_tmp_all=0.;
    if(zee_diff_tmp_all[ipt]->Integral()>1. && signal_before_tmp_all[ipt]->Integral()>1. && bkgd_before_tmp_all[ipt]->Integral()>1.) {
      fitter.Update(zee_diff_tmp_all[ipt], signal_before_tmp_all[ipt], bkgd_before_tmp_all[ipt], xmin, xmax);
      fitter.FitMass();
      fitter.Compare(ctemp);   
      fitter.GetDataSignalBkg(data_entry_before_all[ipt], mc_entry_before_all[ipt], bkg_entry_before_all[ipt], mc_error_before_all[ipt], chisq1_all[ipt]);
    }
    
    if(zee_spatial_tmp_all[ipt]->Integral()>0. && signal_after_tmp_all[ipt]->Integral()>0. && bkgd_after_tmp_all[ipt]->Integral()>0.) {
      fitter.Update(zee_spatial_tmp_all[ipt], signal_after_tmp_all[ipt], bkgd_after_tmp_all[ipt], xmin, xmax);
      fitter.FitMass();
      fitter.Compare(ctemp);   
      fitter.GetDataSignalBkg(data_entry_after_all[ipt], mc_entry_after_all[ipt], bkg_entry_after_all[ipt], mc_error_after_all[ipt], chisq2_all[ipt]);
    }
      
    int bin_low=signal_before_tmp_all[ipt]->FindBin(limit2);
    int bin_high=signal_before_tmp_all[ipt]->FindBin(limit3);
    
    if(mc_entry_before_all[ipt]>1.&&  mc_entry_after_all[ipt]>1.) {       
	eff_tmp_all= mc_entry_after_all[ipt]/(mc_entry_before_all[ipt] + mc_entry_after_all[ipt]);	
	efferr_tmp_all=sqrt(mc_entry_before_all[ipt]*mc_entry_before_all[ipt]*mc_error_after_all[ipt]*mc_error_after_all[ipt]+ mc_entry_after_all[ipt]*mc_entry_after_all[ipt]*mc_error_before_all[ipt]*mc_error_before_all[ipt])/(mc_entry_before_all[ipt]+mc_entry_after_all[ipt])/(mc_entry_before_all[ipt]+mc_entry_after_all[ipt]);
	
	cout<<"efferr_tmp_all="<<efferr_tmp_all<<endl;
      }
      
      if(eff_tmp_all>1){
	eff_tmp_all=1.;
	efferr_tmp_all=1.;
      }

      eff_data_all->Fill(eff_data_all->GetXaxis()->GetBinCenter(ipt+1), eff_tmp_all);
      eff_data_all->SetBinError(ipt+1, efferr_tmp_all);
  }


/////end all-events


  TFile *file1 = new TFile("eff_plots.root", "recreate");
  TString name_plot;
  name_plot+="eff_data";
  

  ////Draw plots
  TCanvas *canv3= new TCanvas;
  canv3->Divide(1,1);
  canv3->cd(1);
  
  //  bkgd_tmp_all_2d->Draw();
  //  bkgd_tmp_all[4]->Draw();
  eff_data_all->Draw();
  eff_data_all->Fit(func_tagprobe,"R");
  eff_data_all->Write("eff_data_all");
//   //  Eff2->Draw("same");


}

void eff_bino(TH1D *hist1, TH1D *hist2,  TH1D & *eff_hist ){

  for(int i=0; i<hist1->GetNbinsX(); i++){
    double x_coor=hist1->GetXaxis()->GetBinCenter(i+1);
    double content1=hist1->GetBinContent(i+1);
    double content2=hist2->GetBinContent(i+1);
    
    if(content2 > 0.){
      double p=content1/content2;
      double error=sqrt(p*(1-p)/content2);

      if(error==0.) error=1/content2;

      eff_hist->Fill(x_coor, p);
      eff_hist->SetBinError(i+1, error);
    }
  }
}

void divide_plots(TH1D *hist1, TH1D *hist2,  TH1D & *eff_hist ){

  for(int i=0; i<hist1->GetNbinsX(); i++){
    double x_coor=hist1->GetXaxis()->GetBinCenter(i+1);
    double content1=hist1->GetBinContent(i+1);
    double content2=hist2->GetBinContent(i+1);

    double err1=hist1->GetBinError(i+1);
    double err2=hist2->GetBinError(i+1);
    
    if(content1 > 0. && content2 > 0.){
      double p=content1/content2;
      //double error=fabs((err1*content2-err2*content1)/(content2*content2));
      double error=p*sqrt(err1*err1/(content1*content1)+err2*err2/(content2*content2));      

      eff_hist->Fill(x_coor, p);
      eff_hist->SetBinError(i+1, error);
    }
  }
}


void get_weighted_error(TH1 *hist, double low_cut, double high_cut, double & error_weighted){
  int bin_low=hist->FindBin(low_cut);
  int bin_high=hist->FindBin(high_cut);

  double sum_error=0.;
  for(int i=0; i<hist->GetNbinsX(); i++){
    if(hist->GetBinCenter(i+1)>low_cut && hist->GetBinCenter(i+1)<high_cut){
      sum_error+=(hist->GetBinError(i+1))*(hist->GetBinError(i+1));
    }
  }

  error_weighted=sqrt(sum_error);

}
