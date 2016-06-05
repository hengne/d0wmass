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

const int num_bins=16;
//double bins[18]={0.,25.,26.,28.,30.,32.,34.,36.,38.,40.,42.,44.,46.,48.,50.,55.,60., 100.};
double bins[17]={0.,25.,28.,30.,32.,34.,36.,38.,40.,42.,44.,46.,48.,50.,55.,60., 100.};

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

//TH2F *ratio_eta_v_pT = new TH2F("ratio_eta_v_pT", "ratio: eta v pT", 100, 0., 100., 31., -3.1, 3.1);
TH2F *ratio_eta_v_pT = new TH2F("ratio_eta_v_pT", "ratio: eta v pT", num_bins, bins, 31., -3.1, 3.1);
TH2F *ZMass_V_Pt=new TH2F("ZMass_V_Pt","ZMass_V_Pt", num_bins,bins,150, 0., 150.);

TF1 *erf= new TF1("erf","0.5*[2]*(1+TMath::Erf((x-[0])/(sqrt(2)*[1])))",0., 100.);
TF1 *logf= new TF1("logf","[0]+[1]*log(x) + [2]*x", 25., 100.);
TF1 *expf= new TF1("expf","[0]+[1]*exp(-x)",0., 100.);

const double xmin_fit=60.,, xmax_fit=120.;
TF1 *func = new TF1("func","landau", xmin_fit, xmax_fit);

double xmin = 50., xmax = 130.;

const double limit1=60., limit2=70., limit3=110., limit4=120.;

void pTeff_tagprobe_data_bkgdfit() {
  gROOT -> ProcessLine(".x /home/guojun/style_junjie.C");
  gStyle->SetOptFit(1);

  gROOT->LoadMacro("Fitter.cpp");
 

  TFile *f0= new TFile("/work/thanagar-clued0/guojun/efficiency_pT/outputs/for_analysis_20081217/result_eff_goodspatialccectag_forSETpTEff_newskim_20090128.root");

  gDirectory->cd("Eff_Hist");

  const double low_x=20., high_x=100.;
  const double low_y=0.5, high_y=1. ;
  double x_min=50, x_max=90.;
  int low_bin, high_bin;

  eff_data_all=new TH1D("eff_data_all", "eff data all", num_bins, bins);

  char name_bkgd_all[60];
  sprintf(name_bkgd_all, "%s","EMZMass_V_Pt_Bkgd_Etabin");
  char name_data_all[60];
  sprintf(name_data_all, "%s","EMZMass_V_Pt_EM_Probe_Trk_All_Etabin");
  char name_match_data_all[60];
  sprintf(name_match_data_all, "%s","EMZMass_V_Pt_EM_Probe_Trk_Matched_Etabin");
  
  TH2D *h1_data_all_2d=(TH2D *) gROOT->FindObject(name_match_data_all);
  TH2D *h2_data_all_2d=(TH2D *) gROOT->FindObject(name_data_all);
  TH2D *h_bkgd_all_2d=(TH2D *) gROOT->FindObject(name_bkgd_all);


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
      bkgd_tmp_all[j]->Rebin(2); 
      bkgd_before_tmp_all[j]->Rebin(2); 
      bkgd_after_tmp_all[j]->Rebin(2); 
      zee_tmp_all[j]->Rebin(2);
      zee_spatial_tmp_all[j]->Rebin(2);
      zee_diff_tmp_all[j]->Rebin(2);
    }



  for(int i=0; i<15; i++){
    char eff_name[60], eff_title[60];
    sprintf(eff_name, "%s%d", "eff_data_",i);
    sprintf(eff_title, "%s%d", "efficiency data MC",i);

    eff_data[i]=new TH1D(eff_name, eff_title, num_bins, bins);

    char name_bkgd[60];
    sprintf(name_bkgd, "%s","EMZMass_V_Pt_Bkgd_Etabin");
    //    sprintf(name_bkgd, "%s%d","EMZMass_V_Pt_Bkgd_Etabin_",i);
    char name_data[60];
    sprintf(name_data, "%s%d","EMZMass_V_Pt_EM_Probe_Trk_All_Etabin_",i);
    char name_match_data[60];
    sprintf(name_match_data, "%s%d","EMZMass_V_Pt_EM_Probe_Trk_Matched_Etabin_",i);

    TH2D *h1_data_2d=(TH2D *) gROOT->FindObject(name_match_data);
    TH2D *h2_data_2d=(TH2D *) gROOT->FindObject(name_data);
    TH2D *h_bkgd_2d=(TH2D *) gROOT->FindObject(name_bkgd);

    TH2D *bkgd_tmp_2d=ZMass_V_Pt->Clone();
    TH2D *zee_tmp_2d=ZMass_V_Pt->Clone();
    TH2D *zee_spatial_tmp_2d=ZMass_V_Pt->Clone();

    
    bkgd_tmp_2d->Reset();
    zee_tmp_2d->Reset();
    zee_spatial_tmp_2d->Reset();
    
    for(int j=0;j<h_bkgd_2d->GetNbinsX();j++){
      for(int k=0;k<h_bkgd_2d->GetNbinsY();k++){
	bkgd_tmp_2d->Fill(h_bkgd_2d->GetXaxis()->GetBinCenter(j+1),h_bkgd_2d->GetYaxis()->GetBinCenter(k+1),h_bkgd_2d->GetBinContent(j+1,k+1));
	zee_tmp_2d->Fill(h2_data_2d->GetXaxis()->GetBinCenter(j+1),h2_data_2d->GetYaxis()->GetBinCenter(k+1),h2_data_2d->GetBinContent(j+1,k+1));
	zee_spatial_tmp_2d->Fill(h1_data_2d->GetXaxis()->GetBinCenter(j+1),h1_data_2d->GetYaxis()->GetBinCenter(k+1),h1_data_2d->GetBinContent(j+1,k+1));
      }
    }



    TH1D *ZMass=(TH1D *) ZMass_V_Pt->ProjectionY();

    for(int j=0;j<num_bins;j++){
      bkgd_tmp[i][j]=(TH1D *) ZMass->Clone();
      bkgd_before_tmp[i][j]=(TH1D *) ZMass->Clone();
      bkgd_after_tmp[i][j]=(TH1D *) ZMass->Clone();
      zee_tmp[i][j]=(TH1D *) ZMass->Clone();
      zee_spatial_tmp[i][j]=(TH1D *) ZMass->Clone();
      zee_diff_tmp[i][j]=(TH1D *) ZMass->Clone();


      bkgd_tmp[i][j]->Reset();
      bkgd_before_tmp[i][j]->Reset();
      bkgd_after_tmp[i][j]->Reset();
      zee_tmp[i][j]->Reset();
      zee_spatial_tmp[i][j]->Reset();    
      zee_diff_tmp[i][j]->Reset();    
    }

    for(int j=0;j<bkgd_tmp_2d->GetNbinsX();j++){
      for(int k=0;k<bkgd_tmp_2d->GetNbinsY();k++){

	bkgd_tmp[i][j]->Fill(bkgd_tmp_2d->GetYaxis()->GetBinCenter(k+1),bkgd_tmp_2d->GetBinContent(j+1,k+1));
	bkgd_before_tmp[i][j]->Fill(bkgd_tmp_2d->GetYaxis()->GetBinCenter(k+1),bkgd_tmp_2d->GetBinContent(j+1,k+1));
	bkgd_after_tmp[i][j]->Fill(bkgd_tmp_2d->GetYaxis()->GetBinCenter(k+1),bkgd_tmp_2d->GetBinContent(j+1,k+1));
	zee_tmp[i][j]->Fill(zee_tmp_2d->GetYaxis()->GetBinCenter(k+1),zee_tmp_2d->GetBinContent(j+1,k+1));
	zee_spatial_tmp[i][j]->Fill(zee_spatial_tmp_2d->GetYaxis()->GetBinCenter(k+1),zee_spatial_tmp_2d->GetBinContent(j+1,k+1));
	zee_diff_tmp[i][j]->Fill(zee_tmp_2d->GetYaxis()->GetBinCenter(k+1),zee_tmp_2d->GetBinContent(j+1,k+1) - zee_spatial_tmp_2d->GetBinContent(j+1,k+1));
      }
      bkgd_tmp[i][j]->Rebin(2); 
      bkgd_before_tmp[i][j]->Rebin(2); 
      bkgd_after_tmp[i][j]->Rebin(2); 
      zee_tmp[i][j]->Rebin(2);
      zee_spatial_tmp[i][j]->Rebin(2);
      zee_diff_tmp[i][j]->Rebin(2);
    }
  }
  

  TFile *f1= new TFile("/work/thanagar-clued0/guojun/runscripts_generator/epmcs_20081222/wz_epmcs/src/result_zee_forsignalshape_ccectag_CCvtxfromfullMC_forSETpTEff_weighted_22.6M.root");  

  gDirectory->cd("smeared");
    

  char name_signal_before_all[60], name_signal_after_all[60];
  sprintf(name_signal_before_all, "%s","smeared_ZMass_vs_Pt_Before_Trk_CC");
  sprintf(name_signal_after_all, "%s","smeared_ZMass_vs_Pt_After_Trk_CC");
  
  TH2D *h_signal_before_all_2d=(TH2D *) gROOT->FindObject(name_signal_before_all);
  TH2D *h_signal_after_all_2d=(TH2D *) gROOT->FindObject(name_signal_after_all);
  
  TH2D *signal_before_tmp_all_2d=ZMass_V_Pt->Clone();
  TH2D *signal_after_tmp_all_2d=ZMass_V_Pt->Clone();
  
  signal_before_tmp_all_2d->Reset();
  signal_after_tmp_all_2d->Reset();
  
  for(int j=0;j<h_bkgd_2d->GetNbinsX();j++){
    for(int k=0;k<h_bkgd_2d->GetNbinsY();k++){
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
      signal_before_tmp_all[j]->Rebin(2);
      signal_after_tmp_all[j]->Rebin(2);
    }



  TCanvas *ctemp=new TCanvas;
  int npad = 1;
  ctemp->Divide(1,1); 
  ctemp->cd(npad); 

  Fitter fitter;
  for(int ipt=1; ipt<num_bins; ipt++){   
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


/////start to deal with each eta bin
  for(int i=0; i<15; i++){
    char name_signal_before[60], name_signal_after[60];
    sprintf(name_signal_before, "%s%d","smeared_ZMass_vs_Pt_Before_Trk_CC_Etabin_",i);
    sprintf(name_signal_after, "%s%d","smeared_ZMass_vs_Pt_After_Trk_CC_Etabin_",i);

    TH2D *h_signal_before_2d=(TH2D *) gROOT->FindObject(name_signal_before);
    TH2D *h_signal_after_2d=(TH2D *) gROOT->FindObject(name_signal_after);

    TH2D *signal_before_tmp_2d=ZMass_V_Pt->Clone();
    TH2D *signal_after_tmp_2d=ZMass_V_Pt->Clone();
    
    signal_before_tmp_2d->Reset();
    signal_after_tmp_2d->Reset();

    char eff_fast_name[60], eff_fast_title[60];
    sprintf(eff_fast_name, "%s%d", "eff_fast_data_",i);
    sprintf(eff_fast_title, "%s%d", "eff_fasticiency data MC",i);

    eff_fast[i]=new TH1D(eff_fast_name, eff_fast_title, num_bins, bins);
    
    for(int j=0;j<h_bkgd_2d->GetNbinsX();j++){
      for(int k=0;k<h_bkgd_2d->GetNbinsY();k++){
	int bin_new=signal_before_tmp_2d->FindBin(h_signal_before_2d->GetXaxis()->GetBinCenter(j+1),h_signal_before_2d->GetYaxis()->GetBinCenter(k+1));

	double err_before_old=signal_before_tmp_2d->GetBinError(bin_new);
	double err_before_input=h_signal_before_2d->GetBinError(j+1,k+1);
	double err_before_new=sqrt(err_before_old*err_before_old + err_before_input*err_before_input);

	double err_after_old=signal_after_tmp_2d->GetBinError(bin_new);
	double err_after_input=h_signal_after_2d->GetBinError(j+1,k+1);
	double err_after_new=sqrt(err_after_old*err_after_old + err_after_input*err_after_input);

	signal_before_tmp_2d->Fill(h_signal_before_2d->GetXaxis()->GetBinCenter(j+1),h_signal_before_2d->GetYaxis()->GetBinCenter(k+1),h_signal_before_2d->GetBinContent(j+1,k+1));
	signal_before_tmp_2d->SetBinError(bin_new, err_before_new);
// 	cout<<"err_new="<<err_new<<endl;
// 	cout<<"err_newcheck="<<signal_before_tmp_2d->GetBinError(bin_new)<<endl;
// 	cout<<"content_newcheck="<<signal_before_tmp_2d->GetBinContent(bin_new)<<endl;
	signal_after_tmp_2d->Fill(h_signal_after_2d->GetXaxis()->GetBinCenter(j+1),h_signal_after_2d->GetYaxis()->GetBinCenter(k+1),h_signal_after_2d->GetBinContent(j+1,k+1));
	signal_after_tmp_2d->SetBinError(bin_new, err_after_new);
      }
    }

    TH1D *ZMass=(TH1D *) ZMass_V_Pt->ProjectionY();
    
    for(int j=0;j<num_bins;j++){
      signal_before_tmp[i][j]=(TH1D *) ZMass->Clone();          
      signal_before_tmp[i][j]->Reset();
      signal_after_tmp[i][j]=(TH1D *) ZMass->Clone();          
      signal_after_tmp[i][j]->Reset();
      signal_diff_tmp[i][j]=(TH1D *) ZMass->Clone();          
      signal_diff_tmp[i][j]->Reset();

      signal_before_tmp_fast[i][j]=(TH1D *) ZMass->Clone();          
      signal_before_tmp_fast[i][j]->Reset();
      signal_after_tmp_fast[i][j]=(TH1D *) ZMass->Clone();          
      signal_after_tmp_fast[i][j]->Reset();
    }

    for(int j=0;j<signal_before_tmp_2d->GetNbinsX();j++){
      for(int k=0;k<signal_before_tmp_2d->GetNbinsY();k++){
	double err_before_old=signal_before_tmp[i][j]->GetBinError(k+1);
	double err_before_input=signal_before_tmp_2d->GetBinError(j+1,k+1);
	double err_before_new=sqrt(err_before_old*err_before_old + err_before_input*err_before_input);

	double err_after_old=signal_after_tmp[i][j]->GetBinError(k+1);
	double err_after_input=signal_after_tmp_2d->GetBinError(j+1,k+1);
	double err_after_new=sqrt(err_after_old*err_after_old + err_after_input*err_after_input);


	signal_before_tmp[i][j]->Fill(signal_before_tmp_2d->GetYaxis()->GetBinCenter(k+1),signal_before_tmp_2d->GetBinContent(j+1,k+1));
	signal_after_tmp[i][j]->Fill(signal_after_tmp_2d->GetYaxis()->GetBinCenter(k+1),signal_after_tmp_2d->GetBinContent(j+1,k+1));
	signal_before_tmp[i][j]->SetBinError(k+1, err_before_new);
	signal_after_tmp[i][j]->SetBinError(k+1, err_after_new);

	//	signal_diff_tmp[i][j]->Fill(signal_after_tmp_2d->GetYaxis()->GetBinCenter(k+1),signal_before_tmp_2d->GetBinContent(j+1,k+1) - signal_after_tmp_2d->GetBinContent(j+1,k+1));

	signal_before_tmp_fast[i][j]->Fill(signal_before_tmp_2d->GetYaxis()->GetBinCenter(k+1),signal_before_tmp_2d->GetBinContent(j+1,k+1));
	signal_after_tmp_fast[i][j]->Fill(signal_after_tmp_2d->GetYaxis()->GetBinCenter(k+1),signal_after_tmp_2d->GetBinContent(j+1,k+1));
	signal_before_tmp_fast[i][j]->SetBinError(k+1, err_before_new);
	signal_after_tmp_fast[i][j]->SetBinError(k+1, err_after_new);
      }
      signal_before_tmp[i][j]->Rebin(2);
      signal_after_tmp[i][j]->Rebin(2);
      signal_before_tmp_fast[i][j]->Rebin(2);
      signal_after_tmp_fast[i][j]->Rebin(2);
    }
  }


  ////Start fitting using the tail region

 
  for(int ieta=0; ieta<15; ieta++){ 
  //  for(int ieta=3; ieta<3; ieta++){ 
    for(int ipt=1; ipt<num_bins; ipt++){   
    //for(int ipt=7; ipt<7; ipt++){   

      double eff_tmp=1, efferr_tmp=0.;
      //      TH1D *test=(TH1D *)signal_before_tmp[ieta][ipt]->Clone();
      //      if(zee_tmp[ieta][ipt]->Integral()>0. && signal_before_tmp[ieta][ipt]->Integral()>0. && bkgd_before_tmp[ieta][ipt]->Integral()>0.) {
      if(zee_diff_tmp[ieta][ipt]->Integral()>1. && signal_before_tmp[ieta][ipt]->Integral()>1. && bkgd_before_tmp[ieta][ipt]->Integral()>1.) {
	//fitter.Update(zee_tmp[ieta][ipt], signal_before_tmp[ieta][ipt], bkgd_before_tmp[ieta][ipt], xmin, xmax);
	//fitter.Update(test, signal_before_tmp[ieta][ipt], bkgd_before_tmp[ieta][ipt], xmin, xmax);
	fitter.Update(zee_diff_tmp[ieta][ipt], signal_before_tmp[ieta][ipt], bkgd_before_tmp[ieta][ipt], xmin, xmax);
 	fitter.FitMass();
	fitter.Compare(ctemp);   
	//fitter.Compare();   
	fitter.GetDataSignalBkg(data_entry_before[ieta][ipt], mc_entry_before[ieta][ipt], bkg_entry_before[ieta][ipt], mc_error_before[ieta][ipt], chisq1[ieta][ipt]);
	//fitter.GetDataSignalBkg(data_entry_before[ieta][ipt], mc_entry_before[ieta][ipt], bkg_entry_before[ieta][ipt], mc_error_before[ieta][ipt]);
	//	cout<<"mass before="<<signal_before_tmp[ieta][ipt]->Integral()<<endl;
      }

      if(zee_spatial_tmp[ieta][ipt]->Integral()>0. && signal_after_tmp[ieta][ipt]->Integral()>0. && bkgd_after_tmp[ieta][ipt]->Integral()>0.) {
 	fitter.Update(zee_spatial_tmp[ieta][ipt], signal_after_tmp[ieta][ipt], bkgd_after_tmp[ieta][ipt], xmin, xmax);
	fitter.FitMass();
	fitter.Compare(ctemp);   
	//fitter.Compare();   
	fitter.GetDataSignalBkg(data_entry_after[ieta][ipt], mc_entry_after[ieta][ipt], bkg_entry_after[ieta][ipt], mc_error_after[ieta][ipt], chisq2[ieta][ipt]);
	//fitter.GetDataSignalBkg(data_entry_after[ieta][ipt], mc_entry_after[ieta][ipt], bkg_entry_after[ieta][ipt], mc_error_after[ieta][ipt]);
	//	cout<<"mass after="<<signal_after_tmp[ieta][ipt]->Integral()<<endl;
      }
      
      int bin_low=signal_before_tmp[ieta][ipt]->FindBin(limit2);
      int bin_high=signal_before_tmp[ieta][ipt]->FindBin(limit3);

      cout<<"mc_entry_before[ieta][ipt]="<<mc_entry_before[ieta][ipt]<<endl;
      cout<<"mc_error_before[ieta][ipt]="<<mc_error_before[ieta][ipt]<<endl;
      cout<<"mc_entry_after[ieta][ipt]="<<mc_entry_after[ieta][ipt]<<endl;
      cout<<"mc_error_after[ieta][ipt]="<<mc_error_after[ieta][ipt]<<endl;

      if(mc_entry_before[ieta][ipt]>1.&&  mc_entry_after[ieta][ipt]>1.) {       
	// 	eff_tmp=events_after/events_before;
	// 	if(events_after==0) eff_tmp=1./events_before;
	//	efferr_tmp=sqrt((D_after*(1-D_after/D_before) + B_after*(1-B_after/B_before))/((D_before-B_before)*(D_before-B_before)));

	//       	eff_tmp= mc_entry_after[ieta][ipt]/mc_entry_before[ieta][ipt];	
	//	efferr_tmp=sqrt(eff_tmp*(1-eff_tmp)/mc_entry_before[ieta][ipt]);

	eff_tmp= mc_entry_after[ieta][ipt]/(mc_entry_before[ieta][ipt] + mc_entry_after[ieta][ipt]);	
	//	efferr_tmp=sqrt(eff_tmp*(1-eff_tmp)/(mc_entry_before[ieta][ipt] + mc_entry_after[ieta][ipt]));


	efferr_tmp=sqrt(mc_entry_before[ieta][ipt]*mc_entry_before[ieta][ipt]*mc_error_after[ieta][ipt]*mc_error_after[ieta][ipt]+ mc_entry_after[ieta][ipt]*mc_entry_after[ieta][ipt]*mc_error_before[ieta][ipt]*mc_error_before[ieta][ipt])/(mc_entry_before[ieta][ipt]+mc_entry_after[ieta][ipt])/(mc_entry_before[ieta][ipt]+mc_entry_after[ieta][ipt]);

	cout<<"efferr_tmp="<<efferr_tmp<<endl;
      }
      
      if(eff_tmp>1){
	eff_tmp=1.;
	efferr_tmp=1.;
      }

      eff_data[ieta]->Fill(eff_data[ieta]->GetXaxis()->GetBinCenter(ipt+1), eff_tmp);
      eff_data[ieta]->SetBinError(ipt+1, efferr_tmp);


      ////now calculate the efficiency in fast MC
      double sum_before=signal_before_tmp_fast[ieta][ipt]->Integral(bin_low, bin_high);
      double sum_after=signal_after_tmp_fast[ieta][ipt]->Integral(bin_low, bin_high);
      double eff_weighted=sum_after/sum_before;
      
      double sumerr_before_weighted=0.;
      get_weighted_error(signal_before_tmp_fast[ieta][ipt], limit2, limit3, sumerr_before_weighted);
//       cout<<"sum_before="<<sum_before<<endl;
//       cout<<"sum_after="<<sum_after<<endl;
//       cout<<"sumerr_before_weighted="<<sumerr_before_weighted<<endl;
      double efferr_weighted=sqrt(eff_weighted*(1-eff_weighted))*sumerr_before_weighted/sum_before;
      
      eff_fast[ieta]->Fill(eff_fast[ieta]->GetXaxis()->GetBinCenter(ipt+1), eff_weighted);
      eff_fast[ieta]->SetBinError(ipt+1, efferr_weighted);
      
    }
  }



  TFile *file1 = new TFile("eff_plots.root", "recreate");
  TString name_plot;
  name_plot+="eff_data";
  


  ////Draw plots
  TCanvas *canv= new TCanvas;
  canv->Divide(4,4);

  TCanvas *canv2= new TCanvas;
  canv2->Divide(4,4);

  for(int i=0; i<15; i++){
    canv->cd(i+1);

    // bkgd_before_tmp[i][1]->Draw();
    
//     signal_before_tmp[i][1]->Draw("pe");
//     signal_after_tmp[i][1]->SetLineColor(2);
//     signal_after_tmp[i][1]->Draw("pe&same");
    // zee_spatial_tmp[i][8]->Draw("pe");

  
  
    eff_data[i]->SetAxisRange(low_x,high_x,"X");
    eff_data[i]->SetAxisRange(low_y,high_y,"Y");
    eff_data[i]->SetLabelSize(0.08, "X");
    eff_data[i]->SetLabelSize(0.08, "y");
    eff_data[i]->Draw();




    //eff_fast[i]->Scale(scale);
    //    eff_fast[i]->Scale(1.05);
    eff_fast[i]->SetLineColor(2);
    eff_fast[i]->SetLabelSize(0.08, "X");
    eff_fast[i]->SetLabelSize(0.08, "y");
    eff_fast[i]->Draw("same");
    //eff_fast[i]->Draw();

    eff_data[i]->Sumw2();
    eff_fast[i]->Sumw2();
    ratio[i]=(TH1D *)eff_data[i]->Clone();
    //    ratio[i]->Divide(eff_fast[i]);
    ratio[i]->Reset();
    divide_plots(eff_data[i], eff_fast[i], ratio[i]);
    ratio[i]->Scale(0.8);

    ////Fill 2D ratio plot
    for(int j=0; j<ratio[i]->GetNbinsX(); j++){
      double bin_cont=ratio[i]->GetBinContent(j+1);
      double bin_err=ratio[i]->GetBinError(j+1);
      ratio_eta_v_pT->SetBinContent(j+1,i+9,bin_cont);
      ratio_eta_v_pT->SetBinError(j+1,i+9,bin_err);
    }

    canv2->cd(i+1);
    ratio[i]->SetLabelSize(0.08, "X");
    ratio[i]->SetLabelSize(0.08, "y");
    ratio[i]->SetAxisRange(low_x,high_x,"X");
    ratio[i]->SetAxisRange(0.75,1.2,"Y");
    //  ratio[i]->Fit("func_cheby", "R");
    erf->SetParameters(20.,4.,1.);
    erf->SetParLimits(0, 0., 20.);
    ratio[i]->Draw();


    TString name_eff_data="eff_data_";
    name_eff_data+=i;
    eff_data[i]->Write(name_eff_data);

    TString name_eff_fast="eff_fast_";
    name_eff_fast+=i;
    eff_fast[i]->Write(name_eff_fast);


    TString name_ratio="ratio_";
    name_ratio+=i;
    ratio[i]->Write(name_ratio);
    
  }


  TCanvas *canv3= new TCanvas;
  canv3->Divide(1,1);
  canv3->cd(1);
  
  eff_data_all->Draw();
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
