#include <TFile.h>
#include <TH1.h>
#include <TMath.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include <iostream>

void EfficiencyPhiPlot(){

   TCanvas *c1 = new TCanvas("c1","c1",800,800);
  //.x /home/jholzbau/rootlogon.C
  // TH1::SetDefaultSumw2();
  // TH1::Sumw2();

   TFile f ("/prj_root/5007/wz2_write/jenny/cafe_MC_lumibin_p26test_new_wenu/cafe_MC_lumiall_run2b34_wen.root");
 TH1D *hp225 = (TH1D*)f.Get("WCand_Hist/WCandElecPhi_Spatial_Match_0");

 TFile f2 ("/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_phi1_MC_20120601_153537/pythia_wen_run2b34_phi1_MC.root");
 TH1D *htp225 = (TH1D*)f2.Get("default/hWcandElecPhi_CC");

 // hp225->Divide(hp225, htp225,1.0,1.0,"B");

  hp225->SetMarkerSize(1);
  htp225->SetMarkerSize(1);
  // hp225->Scale(htp225->Integral()/hp225->Integral());//scale to "mc"
  hp225->Draw("lp");
  htp225->SetMarkerColor(kRed);
  htp225->SetLineColor(kRed);
  htp225->Scale(hp225->Integral()/htp225->Integral());//scale to "data"
  htp225->Draw("lp same");

gPad->Update();
c1->Update();
c1->Print("PlotPhi.eps");
c1->Print("PlotPhi.gif");


 hp225->Divide(hp225, htp225,1.0,1.0,"B");

 hp225->SetMarkerSize(1);
 htp225->SetMarkerSize(1);
 hp225->Draw("lp");
 

gPad->Update();
c1->Update();
c1->Print("PlotEffPhi.eps");
c1->Print("PlotEffPhi.gif");

c1->Print("PlotEffPhi.C");

}
