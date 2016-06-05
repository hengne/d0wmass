#include <TApplication.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <strstream>
#include "TRandom.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TH1.h"

using namespace std;

typedef TF1* TF1ptr;
typedef TH1D* TH1Dptr;

double fitf(double *x, double *par){
  double arg=0;
  double fitval;
  if(x[0]<par[0])
    fitval=par[2];
  else
    fitval=par[2]*(1-par[1]*(x[0]-par[0]));

  return fitval;
}
double fitf4(double *x, double *par){
  double arg=0;
  double fitval;
  if(x[0]<par[0])
    fitval=par[2]*(1-par[3]*(par[0]-x[0]));
  else
    fitval=par[2]*(1-par[1]*(x[0]-par[0]));

  return fitval;
}

const double low_y=0.6, high_y=1.;

// Declare functions to fit... each vector has 3 components: p0 floating, p0 to the Z truth value and p0 as run IIa

TF1ptr func_tagprobe[4];
TF1ptr func_tagprobe_utcut[3];
TF1ptr func_tagprobe_ptcut[3];
TF1ptr func_tagprobe_vtxcut[3];
TF1ptr func_tagprobe_2em[3];
TF1ptr func_tagprobe_phifiducial[3];
TF1ptr func_tagprobe_trkpresel[3];
TF1ptr func_tagprobe_ccectag[3];
TF1ptr func_tagprobe_ectag[3];
TF1ptr func_tagprobe_etratio[4];
TF1ptr func_tagprobe_runiia[3];
TF1ptr func_tagprobe_instlumi[18];
TF1ptr func_truth[4];
TF1ptr func_truth_utcut[3];
TF1ptr func_truth_ptcut[3];
TF1ptr func_truth_vtxcut[3];
TF1ptr func_truth_2em[3];
TF1ptr func_truth_phifiducial[3];
TF1ptr func_truth_trkpresel[3];
TF1ptr func_truth_ccectag[3];
TF1ptr func_truth_ectag[3];
TF1ptr func_truth_etratio[4];
TF1ptr func_truth_runiia[3];
TF1ptr func_truth_instlumi[18];

// Behavior of the fit with other parameters
TH1D* slope_vs_lumi_truth = new TH1D("slope_vs_lumi_truth", "slope vs lumi - truth method", 18, 0., 9.);
TH1D* slope_vs_lumi_tagprobe = new TH1D("slope_vs_lumi_tagprobe", "slope vs lumi - tag and probe method", 18, 0., 9.);
TH1D* eff_vs_lumi_truth = new TH1D("eff_vs_lumi_truth", "efficiency vs lumi - truth", 18, 0., 9.);
TH1D* eff_vs_lumi_tagprobe = new TH1D("eff_vs_lumi_tagprobe", "efficiency vs lumi - tag and probe", 18, 0., 9.);

// Luminosity profiles
TH1D *InstlumiIIa = new TH1D("Instlumi_IIa", "Luminosity Run IIA", 250, 0., 10.);
TH1D *InstlumiIIb = new TH1D("Instlumi_IIb", "Luminosity Run IIB", 250, 0., 10.);


TH1Dptr tagprobe[4];
TH1Dptr tagprobe_utcut[3];
TH1Dptr tagprobe_ptcut[3];
TH1Dptr tagprobe_vtxcut[3];
TH1Dptr tagprobe_2em[3];
TH1Dptr tagprobe_phifiducial[3];
TH1Dptr tagprobe_trkpresel[3];
TH1Dptr tagprobe_ccectag[3];
TH1Dptr tagprobe_ectag[3];
TH1Dptr tagprobe_etratio[4];
TH1Dptr tagprobe_runiia[3];
TH1Dptr tagprobe_instlumi[18];
TH1Dptr truth[4];
TH1Dptr truth_utcut[3];
TH1Dptr truth_ptcut[3];
TH1Dptr truth_vtxcut[3];
TH1Dptr truth_2em[3];
TH1Dptr truth_phifiducial[3];
TH1Dptr truth_trkpresel[3];
TH1Dptr truth_ccectag[3];
TH1Dptr truth_ectag[3];
TH1Dptr truth_etratio[4];
TH1Dptr truth_runiia[3];
TH1Dptr truth_instlumi[18];


// gROOT -> ProcessLine(".L error_ellipse.cpp+");
// gROOT -> ProcessLine(".L draw_ellipse.cpp+");

void upara_eff_fullMC() {

// The value found for the kink point in RunIIa
const float p0_runiia = 1.473;

// Load Hobbs' macro and setup environment
  gStyle->SetOptStat(10);
  gStyle->SetOptFit(11111);


  func_tagprobe[0] = new TF1("tagprobe_p0_floating", fitf4, -15, 15, 4);
  func_tagprobe[0]->FixParameter(3,0.);
  func_tagprobe[1] = new TF1("tagprobe_p0_truth", fitf, -15, 15, 3);
  func_tagprobe[2] = new TF1("tagprobe_p0_runiia", fitf, -15, 15, 3);
  func_tagprobe[2]->FixParameter(0,p0_runiia);
  func_tagprobe[3] = new TF1("tagprobe_4par", fitf4, -15, 15, 4);

func_tagprobe_utcut[0] = new TF1("tagprobe_utcut_p0_floating", fitf, -15, 15, 3);
func_tagprobe_utcut[1] = new TF1("tagprobe_utcut_p0_truth", fitf, -15, 15, 3);
func_tagprobe_utcut[2] = new TF1("tagprobe_utcut_p0_runiia", fitf, -15, 15, 3);
func_tagprobe_utcut[2]->FixParameter(0,p0_runiia);

func_tagprobe_ptcut[0] = new TF1("tagprobe_ptcut_p0_floating", fitf, -15, 15, 3);
func_tagprobe_ptcut[1] = new TF1("tagprobe_ptcut_p0_truth", fitf, -15, 15, 3);
func_tagprobe_ptcut[2] = new TF1("tagprobe_ptcut_p0_runiia", fitf, -15, 15, 3);
func_tagprobe_ptcut[2]->FixParameter(0,p0_runiia);

func_tagprobe_vtxcut[0] = new TF1("tagprobe_vtxcut_p0_floating", fitf, -15, 15, 3);
func_tagprobe_vtxcut[1] = new TF1("tagprobe_vtxcut_p0_truth", fitf, -15, 15, 3);
func_tagprobe_vtxcut[2] = new TF1("tagprobe_vtxcut_p0_runiia", fitf, -15, 15, 3);
func_tagprobe_vtxcut[2]->FixParameter(0,p0_runiia);

func_tagprobe_2em[0] = new TF1("tagprobe_2em_p0_floating", fitf, -15, 15, 3);
func_tagprobe_2em[1] = new TF1("tagprobe_2em_p0_truth", fitf, -15, 15, 3);
func_tagprobe_2em[2] = new TF1("tagprobe_2em_p0_runiia", fitf, -15, 15, 3);
func_tagprobe_2em[2]->FixParameter(0,p0_runiia);

func_tagprobe_phifiducial[0] = new TF1("tagprobe_phifiducial_p0_floating", fitf, -15, 15, 3);
func_tagprobe_phifiducial[1] = new TF1("tagprobe_phifiducial_p0_truth", fitf, -15, 15, 3);
func_tagprobe_phifiducial[2] = new TF1("tagprobe_phifiducial_p0_runiia", fitf, -15, 15, 3);
func_tagprobe_phifiducial[2]->FixParameter(0,p0_runiia);

func_tagprobe_trkpresel[0] = new TF1("tagprobe_trkpresel_p0_floating", fitf, -15, 15, 3);
func_tagprobe_trkpresel[1] = new TF1("tagprobe_trkpresel_p0_truth", fitf, -15, 15, 3);
func_tagprobe_trkpresel[2] = new TF1("tagprobe_trkpresel_p0_runiia", fitf, -15, 15, 3);
func_tagprobe_trkpresel[2]->FixParameter(0,p0_runiia);

func_tagprobe_ccectag[0] = new TF1("tagprobe_ccectag_p0_floating", fitf, -15, 15, 3);
func_tagprobe_ccectag[1] = new TF1("tagprobe_ccectag_p0_truth", fitf, -15, 15, 3);
func_tagprobe_ccectag[2] = new TF1("tagprobe_ccectag_p0_runiia", fitf, -15, 15, 3);
func_tagprobe_ccectag[2]->FixParameter(0,p0_runiia);

func_tagprobe_ectag[0] = new TF1("tagprobe_ectag_p0_floating", fitf, -15, 15, 3);
func_tagprobe_ectag[1] = new TF1("tagprobe_ectag_p0_truth", fitf, -15, 15, 3);
func_tagprobe_ectag[2] = new TF1("tagprobe_ectag_p0_runiia", fitf, -15, 15, 3);
func_tagprobe_ectag[2]->FixParameter(0,p0_runiia);

 func_tagprobe_etratio[0] = new TF1("tagprobe_etratio_p0_floating", fitf4, -0.5, 0.5, 4);
 func_tagprobe_etratio[0]->FixParameter(3,0.);
 func_tagprobe_etratio[1] = new TF1("tagprobe_etratio_p0_truth", fitf, -0.5, 0.5, 3);
 func_tagprobe_etratio[2] = new TF1("tagprobe_etratio_p0_runiia", fitf, -0.5, 0.5, 3);
 func_tagprobe_etratio[2]->FixParameter(0,p0_runiia);
 func_tagprobe_etratio[3] = new TF1("tagprobe_etratio_4par", fitf4, -0.5, 0.5, 4);

func_tagprobe_runiia[0] = new TF1("tagprobe_runiia_p0_floating", fitf, -10, 10, 3);
func_tagprobe_runiia[1] = new TF1("tagprobe_runiia_p0_truth", fitf, -10, 10, 3);
func_tagprobe_runiia[2] = new TF1("tagprobe_runiia_p0_runiia", fitf, -10, 10, 3);
func_tagprobe_runiia[2]->FixParameter(0,p0_runiia);

      TString name="tagprobe_lumi_";
      for(int i=0; i<18; i++) {
            func_tagprobe_instlumi[i] = new TF1(name+i, fitf, -15, 15, 3);
      }


      func_truth[0] = new TF1("truth_p0_floating", fitf4, -15, 15, 4);
      func_truth[0]->FixParameter(3,0.);
      func_truth[1] = new TF1("truth_p0_truth", fitf, -15, 15, 3);
      func_truth[2] = new TF1("truth_p0_runiia", fitf, -15, 15, 3);
      func_truth[2]->FixParameter(0,p0_runiia);
      func_truth[0] = new TF1("truth_p0_4par", fitf4, -15, 15, 4);

func_truth_utcut[0] = new TF1("truth_utcut_p0_floating", fitf, -15, 15, 3);
func_truth_utcut[1] = new TF1("truth_utcut_p0_truth", fitf, -15, 15, 3);
func_truth_utcut[2] = new TF1("truth_utcut_p0_runiia", fitf, -15, 15, 3);
func_truth_utcut[2]->FixParameter(0,p0_runiia);

func_truth_ptcut[0] = new TF1("truth_ptcut_p0_floating", fitf, -15, 15, 3);
func_truth_ptcut[1] = new TF1("truth_ptcut_p0_truth", fitf, -15, 15, 3);
func_truth_ptcut[2] = new TF1("truth_ptcut_p0_runiia", fitf, -15, 15, 3);
func_truth_ptcut[2]->FixParameter(0,p0_runiia);

func_truth_vtxcut[0] = new TF1("truth_vtxcut_p0_floating", fitf, -15, 15, 3);
func_truth_vtxcut[1] = new TF1("truth_vtxcut_p0_truth", fitf, -15, 15, 3);
func_truth_vtxcut[2] = new TF1("truth_vtxcut_p0_runiia", fitf, -15, 15, 3);
func_truth_vtxcut[2]->FixParameter(0,p0_runiia);

func_truth_2em[0] = new TF1("truth_2em_p0_floating", fitf, -15, 15, 3);
func_truth_2em[1] = new TF1("truth_2em_p0_truth", fitf, -15, 15, 3);
func_truth_2em[2] = new TF1("truth_2em_p0_runiia", fitf, -15, 15, 3);
func_truth_2em[2]->FixParameter(0,p0_runiia);

func_truth_phifiducial[0] = new TF1("truth_phifiducial_p0_floating", fitf, -15, 15, 3);
func_truth_phifiducial[1] = new TF1("truth_phifiducial_p0_truth", fitf, -15, 15, 3);
func_truth_phifiducial[2] = new TF1("truth_phifiducial_p0_runiia", fitf, -15, 15, 3);
func_truth_phifiducial[2]->FixParameter(0,p0_runiia);

func_truth_trkpresel[0] = new TF1("truth_trkpresel_p0_floating", fitf, -15, 15, 3);
func_truth_trkpresel[1] = new TF1("truth_trkpresel_p0_truth", fitf, -15, 15, 3);
func_truth_trkpresel[2] = new TF1("truth_trkpresel_p0_runiia", fitf, -15, 15, 3);
func_truth_trkpresel[2]->FixParameter(0,p0_runiia);

func_truth_ccectag[0] = new TF1("truth_ccectag_p0_floating", fitf, -15, 15, 3);
func_truth_ccectag[1] = new TF1("truth_ccectag_p0_truth", fitf, -15, 15, 3);
func_truth_ccectag[2] = new TF1("truth_ccectag_p0_runiia", fitf, -15, 15, 3);
func_truth_ccectag[2]->FixParameter(0,p0_runiia);

func_truth_ectag[0] = new TF1("truth_ectag_p0_floating", fitf, -15, 15, 3);
func_truth_ectag[1] = new TF1("truth_ectag_p0_truth", fitf, -15, 15, 3);
func_truth_ectag[2] = new TF1("truth_ectag_p0_runiia", fitf, -15, 15, 3);
func_truth_ectag[2]->FixParameter(0,p0_runiia);

 func_truth_etratio[0] = new TF1("truth_etratio_p0_floating", fitf4, -0.5, 0.5, 4);
 func_truth_etratio[0]->FixParameter(3,0.);
 func_truth_etratio[1] = new TF1("truth_etratio_p0_truth", fitf, -0.5, 0.5, 3);
 func_truth_etratio[2] = new TF1("truth_etratio_p0_runiia", fitf, -0.5, 0.5, 3);
 func_truth_etratio[2]->FixParameter(0,p0_runiia);
 func_truth_etratio[3] = new TF1("truth_etratio_4par", fitf4, -0.5, 0.5, 4);

func_truth_runiia[0] = new TF1("truth_runiia_p0_floating", fitf, -10, 10, 3);
func_truth_runiia[1] = new TF1("truth_runiia_p0_truth", fitf, -10, 10, 3);
func_truth_runiia[2] = new TF1("truth_runiia_p0_runiia", fitf, -10, 10, 3);
func_truth_runiia[2]->FixParameter(0,p0_runiia);

      TString name="truth_lumi_";
      for(int i=0; i<18; i++) {
            func_truth_instlumi[i] = new TF1(name+i, fitf, -15, 15, 3);
      }

// Open input and output file
      TFile *f0= new TFile("result_geant.root");
      TFile *f1 = new TFile("uparaeff_plots.root", "recreate");

      if(f0->cd("ZCand_Hist")){
	f0->cd();

/////////////// Get IIa luminosity profile //////////////
      InstlumiIIa->Sumw2();
      FILE* stream = fopen("Library_ZB_more_weighted_IIa.txt", "r");
      float a1, a2, a3, lumi, fl1, fl2, fl3;
      
      while (!feof(stream)){
           fscanf(stream, "%f %f %f %f %f %f %f", &a1, &a2, &lumi, &a3, &fl1, &fl2, &fl3);
           InstlumiIIa->Fill(lumi);   
      }
      fclose(stream);

      FILE* stream = fopen("ZMC_overlay_events.txt", "r");

      while (!feof(stream)) {
           fscanf(stream, "%f %f %f", &a1, &a2, &lumi);
           InstlumiIIb->Fill(lumi);
      }
      fclose(stream);

      double scale_a = 1/InstlumiIIa->Integral();
      InstlumiIIa->Scale(scale_a);

      double scale_b = 1/InstlumiIIb->Integral();
      InstlumiIIb->Scale(scale_b);

/////////////////////////////////////////////////////////////

//Tag and Probe

//Make the efficiency calculation
      tagprobe[0] = eff_hists_1D("ZCandUPara_Denominator_Tagprobe","ZCandUPara_Numerator_Tagprobe",f0);
      tagprobe_utcut[0] = eff_hists_1D("ZCandUPara_Denominator_UtCut_Tagprobe","ZCandUPara_Numerator_UtCut_Tagprobe",f0);
      tagprobe_ptcut[0] = eff_hists_1D("ZCandUPara_Denominator_PtCut_Tagprobe","ZCandUPara_Numerator_PtCut_Tagprobe",f0);
      tagprobe_vtxcut[0] = eff_hists_1D("ZCandUPara_Denominator_VtxCut_Tagprobe","ZCandUPara_Numerator_VtxCut_Tagprobe",f0);
      tagprobe_2em[0] = eff_hists_1D("ZCandUPara_Denominator_2EM_Tagprobe","ZCandUPara_Numerator_2EM_Tagprobe",f0);
      tagprobe_phifiducial[0] = eff_hists_1D("ZCandUPara_Denominator_phifiducial_Tagprobe","ZCandUPara_Numerator_phifiducial_Tagprobe",f0);
      tagprobe_trkpresel[0] = eff_hists_1D("ZCandUPara_Denominator_trkpresel_Tagprobe","ZCandUPara_Numerator_trkpresel_Tagprobe",f0);
      tagprobe_ccectag[0] = eff_hists_1D("ZCandUPara_Denominator_CCECtag_Tagprobe","ZCandUPara_Numerator_CCECtag_Tagprobe",f0);
      tagprobe_ectag[0] = eff_hists_1D("ZCandUPara_Denominator_ECtag_Tagprobe","ZCandUPara_Numerator_ECtag_Tagprobe",f0);
      tagprobe_etratio[0] = eff_hists_1D("ZCandUParaETRatio_Denominator_Tagprobe","ZCandUParaETRatio_Numerator_Tagprobe",f0);

// Do the reweighting with RunIIa luminosity profile
      TH2D* tagprobe_upara_vs_lumi = eff_hists_2D("ZCandUPara_V_instlumi_Denominator_Tagprobe","ZCandUPara_V_instlumi_Numerator_Tagprobe",f0);
      Double_t sum, errsum2;
      tagprobe_runiia[0] = new TH1D("tagprobe_runiia","tagprobe_runiia",120,-30.,30.);
      for(Int_t i=0; i<tagprobe_upara_vs_lumi->GetNbinsX(); i++){
          sum=0;
          errsum2=0;      
          for(Int_t j=0; j<tagprobe_upara_vs_lumi->GetNbinsY(); j++){
               sum += tagprobe_upara_vs_lumi->GetBinContent(i+1,j+1)*InstlumiIIa->GetBinContent(j+1);
               errsum2 += pow(tagprobe_upara_vs_lumi->GetBinContent(i+1,j+1)*InstlumiIIa->GetBinError(j+1),2)+pow(tagprobe_upara_vs_lumi->GetBinError(i+1,j+1)*InstlumiIIa->GetBinContent(j+1),2);
          }
          tagprobe_runiia[0]->SetBinContent(i+1,sum);
          tagprobe_runiia[0]->SetBinError(i+1,sqrt(errsum2));
      }

// Do the luminosity study
      TString denom="ZCandUPara_Denominator_instlumi_";
      TString num="ZCandUPara_Numerator_instlumi_";
      for(int i=0; i<18; i++) {
           tagprobe_instlumi[i] = eff_hists_1D(denom+i+"_Tagprobe", num+i+"_Tagprobe",f0);
           tagprobe_instlumi[i]->Fit(func_tagprobe_instlumi[i], "R");
           slope_vs_lumi_tagprobe->SetBinContent(i+1,func_tagprobe_instlumi[i]->GetParameter(1));
           slope_vs_lumi_tagprobe->SetBinError(i+1,func_tagprobe_instlumi[i]->GetParError(1));
           eff_vs_lumi_tagprobe->SetBinContent(i+1,func_tagprobe_instlumi[i]->GetParameter(2));
           eff_vs_lumi_tagprobe->SetBinError(i+1,func_tagprobe_instlumi[i]->GetParError(2));
      }


// Truth method

//Make the efficiency calculation
      truth[0] = eff_hists_1D("ZCandUPara_Denominator_Truth","ZCandUPara_Numerator_Truth",f0);
      truth_utcut[0] = eff_hists_1D("ZCandUPara_Denominator_UtCut_Truth","ZCandUPara_Numerator_UtCut_Truth",f0);
      truth_ptcut[0] = eff_hists_1D("ZCandUPara_Denominator_PtCut_Truth","ZCandUPara_Numerator_PtCut_Truth",f0);
      truth_vtxcut[0] = eff_hists_1D("ZCandUPara_Denominator_VtxCut_Truth","ZCandUPara_Numerator_VtxCut_Truth",f0);
      truth_2em[0] = eff_hists_1D("ZCandUPara_Denominator_2EM_Truth","ZCandUPara_Numerator_2EM_Truth",f0);
      truth_phifiducial[0] = eff_hists_1D("ZCandUPara_Denominator_phifiducial_Truth","ZCandUPara_Numerator_phifiducial_Truth",f0);
      truth_trkpresel[0] = eff_hists_1D("ZCandUPara_Denominator_trkpresel_Truth","ZCandUPara_Numerator_trkpresel_Truth",f0);
      truth_ccectag[0] = eff_hists_1D("ZCandUPara_Denominator_CCECtag_Truth","ZCandUPara_Numerator_CCECtag_Truth",f0);
      truth_ectag[0] = eff_hists_1D("ZCandUPara_Denominator_ECtag_Truth","ZCandUPara_Numerator_ECtag_Truth",f0);
      truth_etratio[0] = eff_hists_1D("ZCandUParaETRatio_Denominator_Truth","ZCandUParaETRatio_Numerator_Truth",f0);

// Do the reweighting with RunIIa luminosity profile
      TH2D* truth_upara_vs_lumi = eff_hists_2D("ZCandUPara_V_instlumi_Denominator_Truth","ZCandUPara_V_instlumi_Numerator_Truth",f0);
      Double_t sum, errsum2;
      truth_runiia[0] = new TH1D("truth_runiia","truth_runiia",120,-30.,30.);
      for(Int_t i=0; i<truth_upara_vs_lumi->GetNbinsX(); i++){
          sum=0;
          errsum2=0;      
          for(Int_t j=0; j<truth_upara_vs_lumi->GetNbinsY(); j++){
               sum += truth_upara_vs_lumi->GetBinContent(i+1,j+1)*InstlumiIIa->GetBinContent(j+1);
               errsum2 += pow(truth_upara_vs_lumi->GetBinContent(i+1,j+1)*InstlumiIIa->GetBinError(j+1),2)+pow(truth_upara_vs_lumi->GetBinError(i+1,j+1)*InstlumiIIa->GetBinContent(j+1),2);
          }
          truth_runiia[0]->SetBinContent(i+1,sum);
          truth_runiia[0]->SetBinError(i+1,sqrt(errsum2));
      }

// Do the luminosity study
      TString denom="ZCandUPara_Denominator_instlumi_";
      TString num="ZCandUPara_Numerator_instlumi_";
      for(int i=0; i<18; i++) {
           truth_instlumi[i] = eff_hists_1D(denom+i+"_Truth", num+i+"_Truth",f0);
           truth_instlumi[i]->Fit(func_truth_instlumi[i], "R");
           slope_vs_lumi_truth->SetBinContent(i+1,func_truth_instlumi[i]->GetParameter(1));
           slope_vs_lumi_truth->SetBinError(i+1,func_truth_instlumi[i]->GetParError(1));
           eff_vs_lumi_truth->SetBinContent(i+1,func_truth_instlumi[i]->GetParameter(2));
           eff_vs_lumi_truth->SetBinError(i+1,func_truth_instlumi[i]->GetParError(2));
      }


// Now, do the fitting and write
      
      f1->cd();

      truth[0]->Fit(func_truth[0],"R");
      const p0_truth = func_truth[0]->GetParameter(0);

      FitWrite4(truth,func_truth,p0_truth,f1,"truth_method");
      FitWrite(truth_utcut,func_truth_utcut,p0_truth,f1,"truth_method_utcut");
      FitWrite(truth_ptcut,func_truth_ptcut,p0_truth,f1,"truth_method_ptcut");
      FitWrite(truth_vtxcut,func_truth_vtxcut,p0_truth,f1,"truth_method_vtxcut");
      FitWrite(truth_2em,func_truth_2em,p0_truth,f1,"truth_method_2em");
      FitWrite(truth_phifiducial,func_truth_phifiducial,p0_truth,f1,"truth_method_phifiducial");
      FitWrite(truth_trkpresel,func_truth_trkpresel,p0_truth,f1,"truth_method_trkpresel");
      FitWrite(truth_ccectag,func_truth_ccectag,p0_truth,f1,"truth_method_ccectag");
      FitWrite(truth_ectag,func_truth_ectag,p0_truth,f1,"truth_method_ectag");
      FitWrite4(truth_etratio,func_truth_etratio,p0_truth,f1,"truth_method_etratio");
      FitWrite(truth_runiia,func_truth_runiia,p0_truth,f1,"truth_method_runiia");

      slope_vs_lumi_truth->Fit("pol1","","",1,6);   
      slope_vs_lumi_truth->Write("slope_vs_lumi_truth");   
      eff_vs_lumi_truth->Fit("pol1","","",1,6);
      eff_vs_lumi_truth->Write("eff_vs_lumi_truth");
      
      tagprobe[0]->Fit(func_tagprobe[0],"R");
      double cov[3][3];
      gMinuit->mnemat(&cov[0][0],3);

      FitWrite4(tagprobe,func_tagprobe,p0_truth,f1,"tagprobe_method");
      FitWrite(tagprobe_utcut,func_tagprobe_utcut,p0_truth,f1,"tagprobe_method_utcut");
      FitWrite(tagprobe_ptcut,func_tagprobe_ptcut,p0_truth,f1,"tagprobe_method_ptcut");
      FitWrite(tagprobe_vtxcut,func_tagprobe_vtxcut,p0_truth,f1,"tagprobe_method_vtxcut");
      FitWrite(tagprobe_2em,func_tagprobe_2em,p0_truth,f1,"tagprobe_method_2em");
      FitWrite(tagprobe_phifiducial,func_tagprobe_phifiducial,p0_truth,f1,"tagprobe_method_phifiducial");
      FitWrite(tagprobe_trkpresel,func_tagprobe_trkpresel,p0_truth,f1,"tagprobe_method_trkpresel");
      FitWrite(tagprobe_ccectag,func_tagprobe_ccectag,p0_truth,f1,"tagprobe_method_ccectag");
      FitWrite(tagprobe_ectag,func_tagprobe_ectag,p0_truth,f1,"tagprobe_method_ectag");
      FitWrite4(tagprobe_etratio,func_tagprobe_etratio,p0_truth,f1,"tagprobe_method_etratio");
      FitWrite(tagprobe_runiia,func_tagprobe_runiia,p0_truth,f1,"tagprobe_method_runiia");

      slope_vs_lumi_tagprobe->Fit("pol1","","",1,6);   
      slope_vs_lumi_tagprobe->Write("slope_vs_lumi_tagprobe");   
      eff_vs_lumi_tagprobe->Fit("pol1","","",1,6);
      eff_vs_lumi_tagprobe->Write("eff_vs_lumi_tagprobe");

// Some extra stuff
      InstlumiIIa->Write();
      InstlumiIIb->Write();      
      cout << "draw_ellipse(1., " << func_tagprobe[0]->GetParameter(1) << ", " << func_tagprobe[0]->GetParameter(2) << ", " << cov[1][1] << ", " << cov[2][2] << ", " << cov[1][2]/sqrt(cov[1][1]*cov[2][2]) << ")" << endl;      cout << "**************************************************" << endl;
      }


// W u|| eff - Still not changed: just renamed the histograms

      if(f0->cd("WCand_Hist")){
      char name_nomatch_w[60];
      char name_match_w[60];
      sprintf(name_nomatch_w, "%s","WCandUPara_noIsoHMxCut");
      sprintf(name_match_w, "%s","WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut");
      TH1D *h1_w=(TH1D *) gROOT->FindObject(name_nomatch_w);
      TH1D *h2_w=(TH1D *) gROOT->FindObject(name_match_w);
      TH1D *eff_upara_w=h2_w->Clone();
      TF1* truth_func_w = new TF1("truth_func_w", fitf, -15, 15, 3);
      TF1* truth_func_w_4par = new TF1("truth_func_w_4par", fitf4, -15, 15, 4);
      if(h1_w && h2_w) {
           eff_upara_w->Reset();
           eff_bino(h2_w, h1_w, eff_upara_w);
      }
      TH1D *eff_upara_w_4par = eff_upara_w->Clone();
      eff_upara_w->Fit("truth_func_w", "R");
      eff_upara_w_4par->Fit("truth_func_w_4par", "R");

      sprintf(name_nomatch_w, "%s","WCandUParaETRatio_noIsoHMxCut");
      sprintf(name_match_w, "%s","WCandUParaETRatio_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut");
      h1_w=(TH1D *) gROOT->FindObject(name_nomatch_w);
      h2_w=(TH1D *) gROOT->FindObject(name_match_w);
      TH1D *eff_upara_wETRatio=h2_w->Clone();
      TF1* truth_func_w_ETRatio = new TF1("truth_func_w_ETRatio", fitf, -0.5, 0.5, 3);
      TF1* truth_func_w_ETRatio_4par = new TF1("truth_func_w_ETRatio_4par", fitf4, -0.5, 0.5, 4);
      if(h1_w && h2_w) {
           eff_upara_wETRatio->Reset();
           eff_bino(h2_w, h1_w, eff_upara_wETRatio);
      }
      TH1D *eff_upara_wETRatio_4par = eff_upara_wETRatio->Clone();
      eff_upara_wETRatio->Fit("truth_func_w_ETRatio", "R");
      eff_upara_wETRatio_4par->Fit("truth_func_w_ETRatio_4par", "R");

      f1->cd();
      eff_upara_w->Write("eff_wupara_truth");
      eff_upara_w_4par->Write("eff_wupara_4par_truth");
      eff_upara_wETRatio->Write("eff_wuparaETRatio_truth");
      eff_upara_wETRatio_4par->Write("eff_wuparaETRatio_4par_truth");
      }
// Close and make table
      f0->Close();
      f1->Close();
      //      gROOT->Reset();
      //      gROOT->ProcessLine(".x upara_hists.C");


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



void eff_bino_2D(TH2D *hist1, TH2D *hist2, TH2D & *eff_hist_2D){
     for(Int_t i=0; i<hist1->GetNbinsY(); i++){ 
          for(Int_t j=0; j<hist1->GetNbinsX(); j++){
               Double_t upara=hist1->GetXaxis()->GetBinCenter(j+1);
               Double_t etrans=hist1->GetYaxis()->GetBinCenter(i+1);
               Double_t content1=hist1->GetBinContent(j+1,i+1);
               Double_t content2=hist2->GetBinContent(j+1,i+1);

               if(content2 > 0.){
                    Double_t p=content1/content2;
                    Double_t error=sqrt(p*(1-p)/content2);

                    if(error==0.) error=1/content2;

                    eff_hist_2D->Fill(upara, etrans, p);
                    eff_hist_2D->SetBinError(j+1, i+1, error);
               }
          }
     }
}

TH1D* eff_hists_1D(TString denominator, TString numerator, TFile *Zfile, TString dir = "ZCand_Hist"){
       Zfile->cd(dir);
       TH1D *temp_1=((TH1D *) gROOT->FindObject(denominator));
       TH1D *temp_2=((TH1D *) gROOT->FindObject(numerator));
       TH1D *outhist=temp_2->Clone();
       outhist->Reset();
       if (temp_1 && temp_2) eff_bino(temp_2, temp_1, outhist);
       else cout << "Couldn't find " << denominator << " or " << numerator << endl;
       return outhist;
}

TH2D* eff_hists_2D(TString denominator, TString numerator, TFile *Zfile, TString dir = "ZCand_Hist"){
       Zfile->cd(dir);
       TH2D *temp_1=((TH2D *) gROOT->FindObject(denominator));
       TH2D *temp_2=((TH2D *) gROOT->FindObject(numerator));
       if (!temp_2) { cout << "No hist" << endl; }
       TH2D *outhist=temp_2->Clone();
       outhist->Reset();
       eff_bino_2D(temp_2, temp_1, outhist);
       return outhist;
}

void FitWrite(TH1Dptr hists[], TF1ptr funcs[], double truth, TFile* Out, TString name) {
     Out->cd();
     hists[0]->Fit(funcs[0],"R");
     hists[1] = (TH1Dptr) hists[0]->Clone();
     hists[2] = (TH1Dptr) hists[0]->Clone();
     funcs[1]->FixParameter(0,truth);
     hists[1]->Fit(funcs[1],"R");
     hists[2]->Fit(funcs[2],"R");
     hists[0]->Write(name);
     hists[1]->Write(name+"_p0_fixed_to_truth");
     hists[2]->Write(name+"_p0_fixed_to_runiia");
}

void FitWrite4(TH1Dptr hists[], TF1ptr funcs[], double truth, TFile* Out, TString name) {
     Out->cd();
     funcs[0]->FixParameter(3,0.);
     hists[0]->Fit(funcs[0],"R");
     hists[1] = (TH1Dptr) hists[0]->Clone();
     hists[2] = (TH1Dptr) hists[0]->Clone();
     hists[3] = (TH1Dptr) hists[0]->Clone();     
     funcs[1]->FixParameter(0,truth);
     hists[1]->Fit(funcs[1],"R");
     hists[2]->Fit(funcs[2],"R");
     hists[3]->Fit(funcs[3],"R");
     hists[0]->Write(name);
     hists[1]->Write(name+"_p0_fixed_to_truth");
     hists[2]->Write(name+"_p0_fixed_to_runiia");
     hists[3]->Write(name+"_4par");
}
