#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include <iostream>

Double_t fitf(Double_t *v, Double_t *par);

void EfficiencyPlotTrkMatchPt(){

  //should be tree output from wmass program, maybe this would work better?
  //cafe wmass_analysis/config/cafe_runIIb.config.runIIb Input: ../WMASSskimRUN2B_3and4_caftrees_2EM___from_EMinclusive_PASS5_fix_84_of_84.root

   TCanvas *c1 = new TCanvas("c1","c1",800,800);
  //.x /home/jholzbau/rootlogon.C
  // TH1::SetDefaultSumw2();
  // TH1::Sumw2();

 TFile f ("/prj_root/5007/wz2_write/jenny/trkmatchpt/cafe_wenu_run34.root");

   TH1D *htp0 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_0");
   TH1D *hp0 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_0");
   
  TH1D *htp1 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_1");
   TH1D *hp1 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_1");

  TH1D *htp2 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_2");
   TH1D *hp2 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_2");

  TH1D *htp3 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_3");
   TH1D *hp3 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_3");

  TH1D *htp4 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_4");
   TH1D *hp4 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_4");

  TH1D *htp5 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_5");
   TH1D *hp5 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_5");

  TH1D *htp6 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_6");
   TH1D *hp6 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_6");

  TH1D *htp7 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_7");
   TH1D *hp7 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_7");

  TH1D *htp8 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_8");
   TH1D *hp8 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_8");

  TH1D *htp9 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_9");
   TH1D *hp9 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_9");

  TH1D *htp10 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_10");
   TH1D *hp10 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_10");

  TH1D *htp11 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_11");
   TH1D *hp11 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_11");

  TH1D *htp12 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_12");
   TH1D *hp12 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_12");

  TH1D *htp13 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_13");
   TH1D *hp13 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_13");

 TH1D *htp14 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_EtaBin_CC_14");
   TH1D *hp14 = (TH1D*)f.Get("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_14");



 TF1 *func0 = new TF1("fit0",fitf,25,100,3, "R");
 TF1 *func1 = new TF1("fit1",fitf,25,100,3, "R");
 TF1 *func2 = new TF1("fit2",fitf,25,100,3, "R");
 TF1 *func3 = new TF1("fit3",fitf,25,100,3, "R");
 TF1 *func4 = new TF1("fit4",fitf,25,100,3, "R");
 TF1 *func5 = new TF1("fit5",fitf,25,100,3, "R");

 TF1 *func6 = new TF1("fit6",fitf,25,100,3, "R");
 TF1 *func7 = new TF1("fit7",fitf,25,100,3, "R");
 TF1 *func8 = new TF1("fit8",fitf,25,100,3, "R");
 TF1 *func9 = new TF1("fit9",fitf,25,100,3, "R");
 TF1 *func10 = new TF1("fit10",fitf,25,100,3, "R");
 TF1 *func11 = new TF1("fit11",fitf,25,100,3, "R");
 TF1 *func12 = new TF1("fit12",fitf,25,100,3, "R");
 TF1 *func13 = new TF1("fit13",fitf,25,100,3, "R");
 TF1 *func14 = new TF1("fit14",fitf,25,100,3, "R");

  func0->SetParameter(0, 0.8);
  func0->SetParameter(1, 0.01);

  func1->SetParameter(0, 0.8);
  func1->SetParameter(1, 0.01);

  func2->SetParameter(0, 0.8);
  func2->SetParameter(1, 0.01);

  func3->SetParameter(0, 0.8);
  func3->SetParameter(1, 0.01);

  func4->SetParameter(0, 0.8);
  func4->SetParameter(1, 0.01);

  func5->SetParameter(0, 0.8);
  func5->SetParameter(1, 0.01);

  func6->SetParameter(0, 0.8);
  func6->SetParameter(1, 0.01);
  
  func7->SetParameter(0, 0.8);
  func7->SetParameter(1, 0.01);
  
  func8->SetParameter(0, 0.8);
  func8->SetParameter(1, 0.01);
  
  func9->SetParameter(0, 0.8);
  func9->SetParameter(1, 0.01);
  
  func10->SetParameter(0, 0.8);
  func10->SetParameter(1, 0.01);
  
  func11->SetParameter(0, 0.8);
  func11->SetParameter(1, 0.01);
  
  func12->SetParameter(0, 0.8);
  func12->SetParameter(1, 0.01);
  
  func13->SetParameter(0, 0.8);
  func13->SetParameter(1, 0.01);
  
  func14->SetParameter(0, 0.8);
  func14->SetParameter(1, 0.01);


  //int bin = 5;
  // for (int bin = 0; bin < 14; bin++){
  //char sn_bin[10];   sprintf(sn_bin, "%i", bin);
  // htp225 = (TH1D*)f.Get(TString("WCand_Hist/WCandElecPt_EtaBin_CC_")+sn_bin);
  // hp225 = (TH1D*)f.Get(TString("WCand_Hist/WCandElecPt_Spatial_Match_EtaBin_CC_")+sn_bin);
   
   hp0->Divide(hp0, htp0,1.0,1.0,"B");
   hp1->Divide(hp1, htp1,1.0,1.0,"B");
   hp2->Divide(hp2, htp2,1.0,1.0,"B");
   hp3->Divide(hp3, htp3,1.0,1.0,"B");
   hp4->Divide(hp4, htp4,1.0,1.0,"B");
   hp5->Divide(hp5, htp5,1.0,1.0,"B");
 hp6->Divide(hp6, htp6,1.0,1.0,"B");
 hp7->Divide(hp7, htp7,1.0,1.0,"B");
 hp8->Divide(hp8, htp8,1.0,1.0,"B");
 hp9->Divide(hp9, htp9,1.0,1.0,"B");
 hp10->Divide(hp10, htp10,1.0,1.0,"B");
 hp11->Divide(hp11, htp11,1.0,1.0,"B");
 hp12->Divide(hp12, htp12,1.0,1.0,"B");
 hp13->Divide(hp13, htp13,1.0,1.0,"B");
 hp14->Divide(hp14, htp14,1.0,1.0,"B");

   //run first to get these numbers, then put into fitf function
 //  cout<<hp225->GetBinContent(hp225->FindBin(45))<<endl;
   func0->FixParameter(2,hp0->GetBinContent(hp0->FindBin(45)) );
   func1->FixParameter(2,hp1->GetBinContent(hp1->FindBin(45)) );
   func2->FixParameter(2,hp2->GetBinContent(hp2->FindBin(45)) );
   func3->FixParameter(2,hp3->GetBinContent(hp3->FindBin(45)) );
   func4->FixParameter(2,hp4->GetBinContent(hp4->FindBin(45)) );
   func5->FixParameter(2,hp5->GetBinContent(hp5->FindBin(45)) );
   func6->FixParameter(2,hp6->GetBinContent(hp6->FindBin(45)) );
   func7->FixParameter(2,hp7->GetBinContent(hp7->FindBin(45)) );
   func8->FixParameter(2,hp8->GetBinContent(hp8->FindBin(45)) );
   func9->FixParameter(2,hp9->GetBinContent(hp9->FindBin(45)) );
   func10->FixParameter(2,hp10->GetBinContent(hp10->FindBin(45)) );
   func11->FixParameter(2,hp11->GetBinContent(hp11->FindBin(45)) );
   func12->FixParameter(2,hp12->GetBinContent(hp12->FindBin(45)) );
   func13->FixParameter(2,hp13->GetBinContent(hp13->FindBin(45)) );
   func14->FixParameter(2,hp14->GetBinContent(hp14->FindBin(45)) );

   hp0->Scale(0.98/hp0->GetBinContent(hp0->FindBin(45)));
   hp1->Scale(0.98/hp1->GetBinContent(hp1->FindBin(45)));
   hp2->Scale(0.98/hp2->GetBinContent(hp2->FindBin(45)));
   hp3->Scale(0.98/hp3->GetBinContent(hp3->FindBin(45)));
   hp4->Scale(0.98/hp4->GetBinContent(hp4->FindBin(45)));
   hp5->Scale(0.98/hp5->GetBinContent(hp5->FindBin(45)));
   hp6->Scale(0.98/hp6->GetBinContent(hp6->FindBin(45)));
   hp7->Scale(0.98/hp7->GetBinContent(hp7->FindBin(45)));
   hp8->Scale(0.98/hp8->GetBinContent(hp8->FindBin(45)));
   hp9->Scale(0.98/hp9->GetBinContent(hp9->FindBin(45)));
   hp10->Scale(0.98/hp10->GetBinContent(hp10->FindBin(45)));
   hp11->Scale(0.98/hp11->GetBinContent(hp11->FindBin(45)));
   hp12->Scale(0.98/hp12->GetBinContent(hp12->FindBin(45)));
   hp13->Scale(0.98/hp13->GetBinContent(hp13->FindBin(45)));
   hp14->Scale(0.98/hp14->GetBinContent(hp14->FindBin(45)));
  
 /**
   hp225->SetMarkerSize(1);
   hp225->SetMarkerStyle(20);
   hp225->SetMarkerColor(bin);
   if (bin == 0) hp225->Draw("lp");
   else  hp225->Draw("lp SAME");
   **/
   //}
 func0->SetLineColor(1);
 func1->SetLineColor(2);
 func2->SetLineColor(3);
 func3->SetLineColor(4);
 func4->SetLineColor(5);
 func5->SetLineColor(6);
 func6->SetLineColor(7);
 func7->SetLineColor(8);
 func8->SetLineColor(9);
 func9->SetLineColor(16);
 func10->SetLineColor(11);
 func11->SetLineColor(12);
 func12->SetLineColor(13);
 func13->SetLineColor(40);
 func14->SetLineColor(30);

  hp0->Fit("fit0", "+");
  hp1->Fit("fit1", "+");
  hp2->Fit("fit2", "+");
  hp3->Fit("fit3", "+");
  hp4->Fit("fit4", "+");
  hp5->Fit("fit5", "+");
  hp6->Fit("fit6", "+");
  hp7->Fit("fit7", "+");
  hp8->Fit("fit8", "+");
  hp9->Fit("fit9", "+");
  hp10->Fit("fit10", "+");
  hp11->Fit("fit11", "+");
  hp12->Fit("fit12", "+");
  hp13->Fit("fit13", "+");
  hp14->Fit("fit14", "+");


  //not sure if scale should be down here or not (param before or after scale- effsmear seems like it should be here)
  //hp225->Scale(0.98/hp225->GetBinContent(hp225->FindBin(45)));

  func0->Draw("lp");
  func1->Draw("lp SAME");
  func2->Draw("lp SAME");
  func3->Draw("lp SAME");
  func4->Draw("lp SAME");
  func5->Draw("lp SAME");
  func6->Draw("lp SAME");
  func7->Draw("lp SAME");
  func8->Draw("lp SAME");
  func9->Draw("lp SAME");
  func10->Draw("lp SAME");
  func11->Draw("lp SAME");
  func12->Draw("lp SAME");
  func13->Draw("lp SAME");
  func14->Draw("lp SAME");

TLegend *legend = new TLegend(0.40,0.3,0.75,0.5);
 legend->SetBorderSize(0);
  legend->SetFillColor(0);
legend->AddEntry(func0,"#eta<-1.3", "lp");
legend->AddEntry(func1,"-1.3<#eta<-1.1", "lp");
legend->AddEntry(func2,"-1.1<#eta<-0.9", "lp");
legend->AddEntry(func3,"-0.9<#eta<-0.7", "lp");
legend->AddEntry(func4,"-0.7<#eta<-0.5", "lp");
legend->AddEntry(func5,"-0.5<#eta<-0.3", "lp");
legend->AddEntry(func6,"-0.3<#eta<-0.1", "lp");
legend->AddEntry(func7,"-0.1<#eta<0.1", "lp");
legend->AddEntry(func8,"0.1<#eta<0.3", "lp");
legend->AddEntry(func9,"0.3<#eta<0.5", "lp");
legend->AddEntry(func10,"0.5<#eta<0.7", "lp");
legend->AddEntry(func11,"0.7<#eta<0.9", "lp");
legend->AddEntry(func12,"0.9<#eta<1.1", "lp");
legend->AddEntry(func13,"1.1<#eta<1.3", "lp");
legend->AddEntry(func14,"#eta>1.3", "lp");

 legend->Draw();

 gPad->Update();
c1->Update();

c1->Print("PlotTrkMatchHistPt.eps");
c1->Print("PlotTrkMatchHistPt.gif");
c1->Print("PlotTrkMatchHistPt.C");
}

 Double_t fitf(Double_t *v, Double_t *par)
   {
     /**
	From EfficiencySmear.cpp
	if(_simulate_pT_dependence && fabs(part.deteta())<1.1) {   // for CC region and _simulate_pT_dependence = true
	int eta_region = wz_utils::PhyEtaRegion_CC(part.eta());    
	// make sure we have 98% efficiency for pT=45 GeV for each eta region
	// this is just kind of normalization to avoid double counting inefficiencies
	double eff_45 = _CCtrkeff_pTphyEta_ParameterA[eta_region] + _CCtrkeff_pTphyEta_ParameterB[eta_region] * TMath::Log(45.);
	pT_dependence = ( _CCtrkeff_pTphyEta_ParameterA[eta_region] + _CCtrkeff_pTphyEta_ParameterB[eta_region] * TMath::Log(part.ppt()) ) * 0.98/eff_45;
     **/

     return ( par[0] + par[1] * TMath::Log(v[0]) )*0.98/par[2];

   }
