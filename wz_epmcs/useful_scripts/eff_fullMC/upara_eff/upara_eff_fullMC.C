#include <TApplication.h>
#include <fstream>
#include <iostream>
#include <strstream>
#include "TRandom.h"
#include "TH1D.h";
#include "TGraph.h";

using namespace std;

double fitf(double *x, double *par){
  double arg=0;
  double fitval;
  if(x[0]<par[0])
    fitval=par[2];
  else
    fitval=par[2]*(1-par[1]*(x[0]-par[0]));

  return fitval;
}

TF1* func1=new TF1("func1", fitf, -15,15,3);
TF1* func_etabin=new TF1("func_etabin", fitf, -15,15,3);
TF1* func_tagprobe=new TF1("func_tagprobe", fitf, -15,15,3);
TF1* func_etabin_tagprobe=new TF1("func_etabin_tagprobe", fitf, -15,15,3);
TF1* func2=new TF1("func2", fitf, -15,15,3);
TF1* func_etabin_w=new TF1("func_etabin_w", fitf, -15,15,3);
TH1D *slope_vs_eta=new TH1D("slope_vs_eta","slope vs eta", 62, -3.1, 3.1);
TH1D *slope_vs_eta_tagprobe=new TH1D("slope_vs_eta_tagprobe","slope vs eta for tag-probe", 62, -3.1, 3.1);
TH1D *slope_vs_eta_w=new TH1D("slope_vs_eta_w","slope vs eta for W", 62, -3.1, 3.1);

TH1D *zupara_eff_mctruth_etabin[26];
TH1D *zupara_eff_tagprobe_etabin[26];
TH1D *wupara_eff_mctruth_etabin[26];

const double low_y=0.6, high_y=1.;
const int rebin=1;
void upara_eff_fullMC() {
  gROOT -> ProcessLine(".x /home/guojun/style_junjie.C");
  //gStyle->SetOptStat(1);
  gStyle->SetOptFit(1);


  TFile *f0= new TFile("/work/thanagar-clued0/guojun/efficiency_pT/outputs/for_analysis_20080608/result_zee_upara_ccecgoodspatialtag_vtx40_20081001.root");

  gDirectory->cd("ZCand_Hist");
  
  //// Z u||: truth method
  char name_nomatch[60];
  char name_match[60];


  sprintf(name_nomatch, "%s","ZCandUPara_notrkmatch_UPara");
  sprintf(name_match, "%s","ZCandUPara_trkmatch_UPara");

  ////scale to W
//   sprintf(name_nomatch, "%s","ZCandUPara_notrkmatch_UPara_ScaleToW");
//   sprintf(name_match, "%s","ZCandUPara_trkmatch_UPara_ScaleToW");

  TH1D *h1=(TH1D *) gROOT->FindObject(name_nomatch);
  TH1D *h2=(TH1D *) gROOT->FindObject(name_match);

  h1->Rebin(rebin);
  h2->Rebin(rebin);

  TH1D *eff_upara=h2->Clone();
  eff_upara->Reset();
  eff_bino(h2, h1, eff_upara);


  ////Z u||: tag-and-probe
  char name_nomatch2[60];
  char name_match2[60];

  sprintf(name_nomatch2, "%s","ZCandUPara_WithoutIsoHMxCut_trkmatch");
  sprintf(name_match2, "%s","ZCandUPara_WithIsoHMxCut_trkmatch");

  ////sclae to W
//   sprintf(name_nomatch2, "%s","ZCandUPara_WithoutIsoHMxCut_trkmatch_ScaleToW");
//   sprintf(name_match2, "%s","ZCandUPara_WithIsoHMxCut_trkmatch_ScaleToW");

  TH1D *h1_2=(TH1D *) gROOT->FindObject(name_nomatch2);
  TH1D *h2_2=(TH1D *) gROOT->FindObject(name_match2);

  h1_2->Rebin(rebin);
  h2_2->Rebin(rebin);

  TH1D *eff_upara_2=h2_2->Clone();
  eff_upara_2->Reset();
  eff_bino(h2_2, h1_2, eff_upara_2);


  ////W u|| eff
  TFile *f0= new TFile("/work/thanagar-clued0/guojun/efficiency_pT/outputs/for_analysis_20080608/result_wenu_upara_goodspatial_vtx40_20081008.root");

  gDirectory->cd("WCand_Hist");
  
  char name_nomatch_w[60];
  char name_match_w[60];

  sprintf(name_nomatch_w, "%s","WCandUPara_noIsoHMxCut");
  sprintf(name_match_w, "%s","WCandUPara_WithIsoHMxCut_trkmatch");

  TH1D *h1_w=(TH1D *) gROOT->FindObject(name_nomatch_w);
  TH1D *h2_w=(TH1D *) gROOT->FindObject(name_match_w);

  TH1D *eff_upara_w=h2_w->Clone();
  eff_upara_w->Reset();
  eff_bino(h2_w, h1_w, eff_upara_w);



  double p0_fixed;

  TString name_title="U_{||}(GeV)";

  /////////Draw plots  
  TCanvas *canv=new TCanvas;
  canv->Divide(1,1);
  canv->cd(1);
  //  func1->FixParameter(0, 1.473);
  eff_upara->Fit(func1,"R");
  eff_upara->SetAxisRange(low_y, high_y, "Y");
  eff_upara->GetXaxis()->SetTitle(name_title);
  eff_upara->Draw();
  p0_fixed=func1->GetParameter(0);


  TCanvas *canv_2=new TCanvas;
  canv_2->Divide(1,1);
  canv_2->cd(1);
  // func_tagprobe->FixParameter(0, p0_fixed);
  //func_tagprobe->FixParameter(0, 1.456);
  eff_upara_2->Fit(func_tagprobe,"R");
  eff_upara_2->SetAxisRange(low_y, high_y, "Y");
  eff_upara_2->GetXaxis()->SetTitle(name_title);
  eff_upara_2->Draw();
  
  
  TCanvas *canv_w=new TCanvas;
  canv_w->Divide(1,1);
  canv_w->cd(1);
  //func2->FixParameter(0, p0_fixed);
  eff_upara_w->Fit(func2,"R");
  eff_upara_w->SetAxisRange(low_y, high_y, "Y");
  eff_upara_w->GetXaxis()->SetTitle(name_title);
  eff_upara_w->Draw();


  TFile *file1 = new TFile("uparaeff_plots.root", "recreate");
  
  eff_upara->Write("eff_zupara_truth");
  eff_upara_2->Write("eff_zupara_tagprobe");
  eff_upara_w->Write("eff_wupara_truth");
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
