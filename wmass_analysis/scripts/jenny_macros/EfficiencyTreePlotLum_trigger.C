#include <vector>
#include <string>
#include "TH1.h"
#include "TFile.h"
#include "TMath.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TTree.h"
#include "TStyle.h"
#include <TLeaf.h>
#include <TBranch.h> 
#include "THStack.h"
#include <iomanip>
#include "TROOT.h"
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>


//**********************************************************
//Change this line if your TTree has a different name
const char *TreeName = "ztrigeff;1";
//**********************************************************

Double_t fitf(Double_t *v, Double_t *par);

void EfficiencyTreePlotLum(){

  //should be tree output from wmass program, maybe this would work better?
  //cafe wmass_analysis/config/cafe_runIIb.config.runIIb Input: ../WMASSskimRUN2B_3and4_caftrees_2EM___from_EMinclusive_PASS5_fix_84_of_84.root

  TString rootfile = "/prj_root/5007/wz2_write/jenny/NewEff_lumi_tree/neweff_pass56_lumitree.root";

   TH1::SetDefaultSumw2();
   TCanvas *c1 = new TCanvas("c1","c1",800,800);
  //.x /home/jholzbau/rootlogon.C
  // TH1::SetDefaultSumw2();
  // TH1::Sumw2();
 Int_t nentries = 999;
 TTree *tree(0);
 TFile *input1(0);

 if (!gSystem->AccessPathName( rootfile )) {
   cout << "accessing " << rootfile << endl;
   input1 = TFile::Open( rootfile );
 } 
 else{
   cout<< "problem accessing "<<rootfile<< endl;
   exit(0);
 }

 tree = (TTree*)input1->Get(TreeName);
 nentries = tree->GetEntries();
 cout<<nentries<<" in tree"<<endl;
 /**`
  Int_t run;  				
  Int_t evt;  				
  Int_t triglist;
  Float_t lumi;			 
  Float_t mee;			  
  Float_t probe_pt;  			  
  Int_t probe_chg;  			  
  Float_t probe_eta;  
  Int_t probe_trackmatch25;
  Int_t probe_trackmatch27;
  Float_t tag_pt;  			  
  Int_t tag_chg;  			  
  Float_t tag_eta;  
  Int_t tag_trackmatch25;
  Int_t tag_trackmatch27;
  Int_t pass_27;
  Int_t pass_25;
**/
 TH1F *htp225 = new TH1F("Pt_EM_Probe_Trig_v16_25","Pt_EM_Probe_Trig_v16_25", 100, 0, 12);
 TH1F *htp227 = new TH1F("Pt_EM_Probe_Trig_v16_25","Pt_EM_Probe_Trig_v16_27_7", 100, 0, 12);
 TH1F *htp227c = new TH1F("Pt_EM_Probe_Trig_v16_25","Pt_EM_Probe_Trig_v16_27", 100, 0, 12);

 TH1F *hp225 = new TH1F("Pt_EM_Probe_Trig_TT_v16_25","Pt_EM_Probe_Trig_TT_v16_25", 100, 0, 12);
 TH1F *hp227 = new TH1F("Pt_EM_Probe_Trig_TT_v16_25","Pt_EM_Probe_Trig_TT_v16_27_7", 100, 0, 12);
 TH1F *hp227c = new TH1F("Pt_EM_Probe_Trig_TT_v16_25","Pt_EM_Probe_Trig_TT_v16_27", 100, 0, 12);

 for (int i = 0; i < nentries; i++){
   tree->GetEntry(i);
   if(tree->GetLeaf("lumi")->GetValue(0) >= 0 && tree->GetLeaf("lumi")->GetValue(0) < 12){
     //   bkgdvar.push_back((float)tree->GetLeaf(var)->GetValue(0));
     if(tree->GetLeaf("pass_25")->GetValue(0) == 1 && tree->GetLeaf("triglist")->GetValue(0) == 6 && tree->GetLeaf("tag_trackmatch25")->GetValue(0) == 1){
       htp225->Fill((float)tree->GetLeaf("lumi")->GetValue(0));
       if(tree->GetLeaf("probe_trackmatch25")->GetValue(0) == 1){
	 hp225->Fill((float)tree->GetLeaf("lumi")->GetValue(0));
       }
     }
     
     if(tree->GetLeaf("pass_27")->GetValue(0) == 1 && tree->GetLeaf("triglist")->GetValue(0) == 7 && tree->GetLeaf("tag_trackmatch27")->GetValue(0) == 1){
       htp227->Fill((float)tree->GetLeaf("lumi")->GetValue(0));
       if(tree->GetLeaf("probe_trackmatch27")->GetValue(0) == 1){
	 hp227->Fill((float)tree->GetLeaf("lumi")->GetValue(0));
       }
     }
     if(tree->GetLeaf("pass_27")->GetValue(0) == 1 && tree->GetLeaf("triglist")->GetValue(0) == 6 && tree->GetLeaf("tag_trackmatch27")->GetValue(0) == 1){
       htp227c->Fill((float)tree->GetLeaf("lumi")->GetValue(0));
       if(tree->GetLeaf("probe_trackmatch27")->GetValue(0) == 1){
	 hp227c->Fill((float)tree->GetLeaf("lumi")->GetValue(0));
       }
     }
   }else{
     cout<<tree->GetLeaf("lumi")->GetValue(0)<<endl;
   }

 }
 //   examples: if h1 is an existing TH1F histogram with 100 bins
 //     Double_t xbins[25] = {...} array of low-edges (xbins[25] is the upper edge of last bin
 //     h1->Rebin(24,"hnew",xbins);  //creates a new variable bin size histogram hnew

 //because weights are re-set during bin merger, the uncertainties are wrong for this way of merging bins!!!
						    //by refilling histo with (bin center, old bin content)
 
 Double_t xbins[8] = {0,2,4,5,6,7,8,12};
 //Double_t xbins[3] = {0,7,12};
 TH1F *hp25 =  (TH1F*) hp225->Rebin(7, "hp25", xbins);
 TH1F *hp27 =  (TH1F*) hp227->Rebin(7, "hp27", xbins);
 TH1F *hp27c =  (TH1F*) hp227c->Rebin(7, "hp27c", xbins);

 TH1F *htp25 =  (TH1F*) htp225->Rebin(7, "htp25", xbins);
 TH1F *htp27 =  (TH1F*) htp227->Rebin(7, "htp27", xbins);
 TH1F *htp27c =  (TH1F*) htp227c->Rebin(7, "htp27c", xbins);


  hp225 = hp25;
  hp227 = hp27;
  hp227c = hp27c;
  
  htp225 = htp25;
  htp227 = htp27;
  htp227c = htp27c;
 

  //h_efficiency = h_after_selection
  //h_efficiency.Divide(h_after_selection,h_before_selection,1.0,1.0,"B")
  
  // hp225->Divide(htp225);
  // hp227->Divide(htp227);
  //hp227c->Divide(htp227c);

  hp225->Divide(hp225, htp225,1.0,1.0,"B");

  hp227->Divide(hp227, htp227,1.0,1.0,"B");
  hp227c->Divide(hp227c, htp227c,1.0,1.0,"B");

 hp225->SetMarkerSize(1);
 hp227->SetMarkerSize(1);
 hp227c->SetMarkerSize(1);
 hp225->SetMarkerStyle(20);
 hp227->SetMarkerStyle(20);
 hp227c->SetMarkerStyle(20);
 hp225->SetMarkerColor(kBlack);
 hp227->SetMarkerColor(kRed);
 hp227c->SetMarkerColor(kGreen);


 hp227->SetLineColor(kRed);
 hp227c->SetLineColor(kGreen);

TLegend *legend = new TLegend(0.40,0.3,0.75,0.5);
 legend->SetBorderSize(0);
  legend->SetFillColor(0);
legend->AddEntry(hp225,"25GeV, triglist6", "lp");
legend->AddEntry(hp227c,"27GeV, triglist6", "lp");
legend->AddEntry(hp227,"27GeV, triglist7", "lp");


  hp225->Draw("pe");
  hp227->Draw("SAME pe");
  hp227c->Draw("SAME pe");
  legend->Draw("SAME");
  
  //xmin, xmax, numpar  range only used if R option specified in fit
  TF1 *func = new TF1("func",fitf,0,7,2);
  TF1 *func2 = new TF1("func2",fitf,0,100, 2);
 TF1 *func3 = new TF1("func3",fitf,0,7,2);

  func->SetLineColor(kBlack);

  //# Turn-on curve parameterization: 0.5 * eff_p2 * (1. + TMath::Erf((pT-eff_p0)/(sqrt(2)*eff_p1)))*(1. + TMath::Erf((pT-eff_p4)/(sqrt(2)*eff_p3)))
  //# below are Hengne's new trigger eff parameters
  //TrigEff_P0:   23.61, 20.74, 23.74, 24.91, 24.4146, 24.5361, 26.5549
  //TrigEff_P1:   2.208, 0.5023, 1.266, 1.61, 0.974658, 0.784704, 0.975321
  //TrigEff_P2:   2.273, 0.4874, 1.261, 2.306, 0.4981099, 0.496889, 0.492516
  //TrigEff_P3:   1795, 23.65, 635.7, 970.5, 14.6902, 21.647, 13.0815
  //TrigEff_P4:   1455, -7.366, 222, 821.8, -2.12041, -15.0317, 9.483 

  func->SetParameter(0, 1);
  func->SetParameter(1, 0);

  func2->SetParameter(0, 1);
  func2->SetParameter(1, 0);

  func3->SetParameter(0, 1);
  func3->SetParameter(1, 0);

  // func->SetParameters(500,hp225->GetMean(),hp225->GetRMS());
  //func->SetParNames("Constant","Mean_value","Sigma");
  hp225->Fit("func", "+");

c1->Print("PlotLumiEff25_lumi012.eps");
c1->Print("PlotLumiEff25_lumi012.gif");

  func2->SetLineColor(kRed);
 hp227->Fit("func2", "+");


c1->Print("PlotLumiEff27_lumi012.eps");
c1->Print("PlotLumiEff27_lumi012.gif");

  func3->SetLineColor(kGreen);
 hp227c->Fit("func3", "+");

  // hp225->Fit("pol2");
  
//c1->Update();
gPad->Update();
c1->Update();
c1->Print("PlotLumiEff27c_lumi012.eps");
c1->Print("PlotLumiEff27c_lumi012.gif");

  hp225->Draw("pe");
  hp227->Draw("SAME pe");
  hp227c->Draw("SAME pe");
  legend->Draw("SAME");

c1->Print("PlotLumiEffAll_lumi012.eps");
c1->Print("PlotLumiEffAll_lumi012.gif");

// htp227->Draw();
//gPad->Update();
//c1->Update();

  //  c1->Print("PlotEff_2b34.eps");
  //  c1->Print("PlotEff_2b34.gif");

  //c1->Print("PlotEffPt_2b34.eps");
  // c1->Print("PlotEffPt_2b34.gif");
  // c1->Print("PlotEffLumi_2b4.eps");
  // c1->Print("PlotEffLumi_2b4.gif");

  
// input1->Close();
}
 Double_t fitf(Double_t *v, Double_t *par)
   {
     return par[0] + par[1]*v[0];// + par[2]*v[0]*v[0];
     //return 0.5 * par[0] * (1. + TMath::Erf((v[0]-par[1])/(sqrt(2)*par[2])))*(1. + TMath::Erf((v[0]-par[3])/(sqrt(2)*par[4])));
     // return 0.5 * par[0] * (1. + TMath::Erf((v[0]-par[1])/(sqrt(2)*par[2])));//*(1. + TMath::Erf((v[0]-par[3])/(sqrt(2)*par[4])));

     //return 0.5 * (par[0] + par[5]*v[0] + par[6]*v[0]*v[0]) * (1. + TMath::Erf((v[0]-par[1])/(sqrt(2)*par[2])))*(1. + TMath::Erf((v[0]-par[3])/(sqrt(2)*par[4])));

   }
/**
EY: TH1D      Pt_EM_Probe_Trig_Matched_v15_0;1        Pt_EM_Probe_Trig_Matched_v15_0
 KEY: TH1D      Pt_EM_Probe_Trig_Matched_v16_25;1       Pt_EM_Probe_Trig_Matched_v16_25
 KEY: TH1D      Pt_EM_Probe_Trig_Matched_v16_25_0;1     Pt_EM_Probe_Trig_Matched_v16_25_0
 KEY: TH1D      Pt_EM_Probe_Trig_Matched_v16_27;1       Pt_EM_Probe_Trig_Matched_v16_27
 KEY: TH1D      Pt_EM_Probe_Trig_Matched_v16_27_0;1     Pt_EM_Probe_Trig_Matched_v16_27_0
 KEY: TH1D      Pt_EM_Probe_Trig_Matched_v16_Both;1     Pt_EM_Probe_Trig_Matched_v16_Both
 KEY: TH1D      Pt_EM_Probe_Trig_Matched_v16_Both_0;1   Pt_EM_Probe_Trig_Matched_v16_Both_0
 KEY: TH1D      Pt_EM_Probe_Trig_v15;1  Pt_EM_Probe_Trig_v15
 KEY: TH1D      Pt_EM_Probe_Trig_v15_0;1        Pt_EM_Probe_Trig_v15_0
 KEY: TH1D      Pt_EM_Probe_Trig_v16_25;1       Pt_EM_Probe_Trig_v16_25
 KEY: TH1D      Pt_EM_Probe_Trig_v16_25_0;1     Pt_EM_Probe_Trig_v16_25_0
 KEY: TH1D      Pt_EM_Probe_Trig_v16_27;1       Pt_EM_Probe_Trig_v16_27
 KEY: TH1D      Pt_EM_Probe_Trig_v16_27_0;1     Pt_EM_Probe_Trig_v16_27_0

void rebins() {
// example of script to rebin a 1-d histogram grouping:
//   2 bins together upto 50
//   5 bins together upto 80
//  10 bins together upto 100
//   TF1 f1("f1","0.1/x",0,100);
//   TH1F *h1 = new TH1F("h1","original histo",100,0,100);
  //  h1->FillRandom("f1",3000);
 
   Int_t bin = 1;
   Double_t bins[80];
   Int_t nbins = 0;
   TAxis *xaxis = h1->GetXaxis();
   while (bin <100) {
      bins[nbins] = xaxis->GetBinLowEdge(bin);
      nbins++;
      if (bin < 50)      bin += 2;
      else if (bin < 80) bin += 5;
      else               bin += 10;
   }             
   bins[nbins] = xaxis->GetBinUpEdge(100);
   
   TH1F *h2 = new TH1F("h2","rebinned histo",nbins,bins);
   for (bin=1;bin<100;bin++) {
      h2->Fill(xaxis->GetBinCenter(bin),h1->GetBinContent(bin));
   }
   TCanvas *c1 = new TCanvas("c1","c1",600,800);
   c1->Divide(1,2);
   c1->cd(1);
   h1->Draw();
   c1->cd(2);
   h2->Draw();
}   
**/
