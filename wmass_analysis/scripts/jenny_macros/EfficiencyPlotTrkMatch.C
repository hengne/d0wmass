#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include <iostream>


void EfficiencyPlotTrkMatch(){

  //should be tree output from wmass program, maybe this would work better?
  //cafe wmass_analysis/config/cafe_runIIb.config.runIIb Input: ../WMASSskimRUN2B_3and4_caftrees_2EM___from_EMinclusive_PASS5_fix_84_of_84.root

   TCanvas *c1 = new TCanvas("c1","c1",800,800);
  //.x /home/jholzbau/rootlogon.C
  // TH1::SetDefaultSumw2();
  // TH1::Sumw2();
 // TFile f ("/work/olemiss-clued0/jenny/workshop/cafe_p21.21.00/result.root");
 
// TH1D *hp225 = (TH1D*)f.Get("Eff_Hist/EMEta_EM_Probe_Trk_Matched_0");
//TH1D *htp225 = (TH1D*)f.Get("Eff_Hist/EMEta_EM_Probe_Spatial_Trk_Matched_0");
 //hp225->Draw("TEXT");

   //loose_EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_Eta_CC

 TFile f ("/prj_root/5007/wz2_write/jenny/cafe_trkmatch2/cafe_trkmatch2_run34.root");
 TFile f ("/prj_root/5007/wz2_write/jenny/trkmatch3/cafe_trkmatch3_run34.root");

  TH2D *htp225 = (TH2D*)f.Get("Eff_Hist/EMEta_EM_Probe_Trk_All_Vtx_Eta_EC");
   TH2D *hp225 = (TH2D*)f.Get("Eff_Hist/EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_Eta_EC");

  hp225->Divide(hp225, htp225,1.0,1.0,"B");

 hp225->SetMarkerSize(1);
 hp225->SetMarkerStyle(20);
 hp225->SetMarkerColor(kBlack);
   hp225->Draw("BOX");


gPad->Update();
c1->Update();

c1->Print("PlotTrkMatchHist.eps");
c1->Print("PlotTrkMatchHist.gif");
c1->Print("PlotTrkMatchHist.C");
}
