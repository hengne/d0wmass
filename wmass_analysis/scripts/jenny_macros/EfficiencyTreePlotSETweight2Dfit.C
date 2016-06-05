#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TF1.h>
#include <TProfile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
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
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include "TGraph.h"
#include <TF1.h>
//**********************************************************
//Change this line if your TTree has a different name
//const char *TreeName1 = "tree;1";
const char *TreeName1 = "w;1";
const char *TreeName2 = "tree;1";
//const char *TreeName1 = "wgen;1";
//const char *TreeName2 = "w;1";
//const char *TreeName2 = "binary_tuple;1";
//**********************************************************

Double_t fitf(Double_t *v, Double_t *par);

void EfficiencyTreePlotSETweight2Dfit(){

  gROOT->ProcessLine(".x /home/jholzbau/rootlogon.C");

  TString var = "ptset2D";

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  TH1::SetDefaultSumw2();

  // TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_allcuteff_default_20120712_142246/testWTree3.root";
  //  TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy/test.root"; //includes SETZB, small test

  //  TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_test_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy/cafe_alleff_test_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy_run34.root";
 //  TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_new_ueff4_withdq_withvtxcut_onevtx_500files/cafe_alleff_new_ueff4_withdq_withvtxcut_onevtx_500files_run34.root";

   //run3 files
   TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b3_treetestnoeff_allcuteff_default_20120801_153809/test.root"; 
   TString rootfile2 = "/prj_root/5007/wz2_write/jenny/new_run34_boringandalleff/ueff5_withdq_onevtx_200files_vtxcut_nostudy2/ueff5_withdq_onevtx_200files_vtxcut_nostudy2_run3.root";



 Double_t xmin = 0;
 Double_t xmax = 400;
 Double_t xmax2 = 150;
 Int_t nbin = 50;

  TH1D *wpt1 = new TH1D("wpt1", "wpt1",  nbin, xmin, xmax2);
  TH1D *wpt2 = new TH1D("wpt2", "wpt2",  nbin, xmin, xmax2);

  TH1D *wset1 = new TH1D("wset1", "wset1",  nbin, xmin, xmax);
  TH1D *wset2 = new TH1D("wset2", "wset2",  nbin, xmin, xmax);
  
  TH1D *wpttestt = new TH1D("wpttestt", "wpttestt",  nbin, xmin, xmax2);
  TH1D *wpttestr = new TH1D("wpttestr", "wpttestr",  nbin, xmin, xmax2);
  TH1D *wsettestt = new TH1D("wsettestt", "wsettestt",  nbin, xmin, xmax);
  TH1D *wsettestr = new TH1D("wsettestr", "wsettestr",  nbin, xmin, xmax);
  TH1D *wpt2r = new TH1D("wpt2r", "wpt2r",  nbin, xmin, xmax2);
  TH1D *wset2r = new TH1D("wset2r", "wset2r",  nbin, xmin, xmax);

  Double_t ymin = 20;
  Double_t ymax = 100;
 TH2D *wsetpt1 = new TH2D("wsetpt1", "wsetpt1",  nbin, xmin, xmax,  nbin, ymin, ymax);
  TH2D *wsetpt2 = new TH2D("wsetpt2", "wsetpt2",  nbin, xmin, xmax,  nbin, ymin, ymax);

  xmin = 0;
  xmax = 7;
  nbin = 200;
  // TH1D *wsetpt1 = new TH1D("wsetpt1", "wsetpt1",  nbin, xmin, xmax);
  // TH1D *wsetpt2 = new TH1D("wsetpt2", "wsetpt2",  nbin, xmin, xmax);

  TH1D *t = new TH1D("top", "top",  nbin, xmin, xmax);
  //  TH1D *b = new TH1D("bottom", "bottom",  nbin, xmin, xmax);
  TH1D *tcut = new TH1D("topcut", "topcut",  nbin, xmin, xmax);
  //  TH1D *bcut = new TH1D("bottomcut", "bottomcut",  nbin, xmin, xmax);
  
  //TH1D *t = new TH1D("top", "top",  100, 0, 150);
  //TH1D *b = new TH1D("bottom", "bottom",  100, 0, 150);
  
  TTree *tree1(0);
  TFile *input1(0);
  TTree *tree2(0);
  TFile *input2(0);
  

 if (!gSystem->AccessPathName( rootfile1 )) {
   cout << "accessing " << rootfile1 << endl;
   input1 = TFile::Open( rootfile1 );
 } 
 else{
   cout<< "problem accessing "<<rootfile1<< endl;
   exit(0);
 }

 tree1 = (TTree*)input1->Get(TreeName1);

 int nentries = tree1->GetEntries();
 cout<<nentries<<" in tree"<<endl;

if (!gSystem->AccessPathName( rootfile2 )) {
   cout << "accessing " << rootfile2 << endl;
   input2 = TFile::Open( rootfile2 );
 } 
 else{
   cout<< "problem accessing "<<rootfile2<< endl;
   exit(0);
 }

 tree2 = (TTree*)input2->Get(TreeName2);

 int nentries2 = tree2->GetEntries();
 cout<<nentries2<<" in tree"<<endl;

 // if(nentries > 1000000) nentries = 1000000;
 // if(nentries2 > 1000000) nentries2 = 1000000;
 
 bool passCC[10];
 bool passCCTrue[10];
bool passEmf[10];
bool passIso[10];
bool passHMx[10];
bool passCalEtaFid[10];
bool passTrkPhiFid[10];
bool passTkMatch[10];
double ept[10];
double epttrue[10];
double eptftrue[10];

 tree2->SetBranchAddress("passCC", passCC);
 tree2->SetBranchAddress("passCCTrue", passCCTrue);
 tree2->SetBranchAddress("passEmf", passEmf);
 tree2->SetBranchAddress("passIso", passIso);
 tree2->SetBranchAddress("passHMx", passHMx);
 tree2->SetBranchAddress("passCalEtaFid", passCalEtaFid);
 tree2->SetBranchAddress("passTrkPhiFid", passTrkPhiFid);
 tree2->SetBranchAddress("passTkMatch", passTkMatch);
 tree2->SetBranchAddress("ept", ept);
 tree2->SetBranchAddress("epttrue", epttrue);
 tree2->SetBranchAddress("eptftrue", eptftrue);
 
 //in Cafe, set study uses fsr merged cone objects (even though called raw there).  So we use eptftrue
 for (int i = 0; i < nentries; i++){
   tree1->GetEntry(i);
   //if(tree1->GetLeaf("ccgen")->GetValue(0) == 1  && tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25){
     //t->Fill(tree1->GetLeaf(var)->GetValue(0));//setZBgen")->GetValue(0));
   
   // if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("cut2")->GetValue(0) == 1 &&tree1->GetLeaf("passesEMIDEff")->GetValue(0) == 1 && tree1->GetLeaf("passesPreselEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrkEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrigEff")->GetValue(0) == 1 ){// && tree1->GetLeaf("passesUParaCorrection")->GetValue(0) == 1){// && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){

   if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("met")->GetValue(0) > 25 && tree1->GetLeaf("wut")->GetValue(0) < 15  && tree1->GetLeaf("mt")->GetValue(0) < 200 && tree1->GetLeaf("mt")->GetValue(0) > 50 ){
     if(tree1->GetLeaf("passesAllEffs")->GetValue(0) == 1){//includes AddOnEff, no SET EFF

       wpt1->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
       wset1->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
     
       wsetpt1->Fill(tree1->GetLeaf("setZBgen")->GetValue(0), tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
       // cout<<tree1->GetLeaf(var)->GetValue(0)<<endl;
     }
      }
 }
 
 for (int j = 0; j < nentries2; j++){
   tree2->GetEntry(j);
   
   // if(passCCTrue[0] == 1 && (eptftrue[0] > 25 || (cafevar == "eptftrue" && varvec[0] > 25))){
     //b->Fill(eptftrue[0]);//setZB
     //if(cafeelvec) b->Fill(varvec[0]);
     //else b->Fill(tree2->GetLeaf(cafevar)->GetValue(0));//setZB

   // if(passCC[0] == 1 && (ept[0] > 25 || (cafevar == "ept" && varvec[0] > 25))  && passEmf[0] == 1 && passIso[0] == 1  && passTrkPhiFid[0] == 1  && passCalEtaFid[0] == 1 &&  passTkMatch[0] == 1 && passHMx[0] == 1 && tree2->GetLeaf("passCutUt")->GetValue(0) == 1 && tree2->GetLeaf("met")->GetValue(0) > 25  && tree2->GetLeaf("passCutWMt")->GetValue(0) == 1 ){//passMET doesn't work, is 0  tree2->GetLeaf("passCutUt")->GetValue(0) == 1 && tree2->GetLeaf("ut")->GetValue(0) < 15 

  if(passCC[0] == 1 && (ept[0] > 25 ) && tree2->GetLeaf("passCutUt")->GetValue(0) == 1 && tree2->GetLeaf("met")->GetValue(0) > 25  && tree2->GetLeaf("passCutWMt")->GetValue(0) == 1 ){
 if(passEmf[0] == 1 && passIso[0] == 1  && passTrkPhiFid[0] == 1  && passCalEtaFid[0] == 1 &&  passTkMatch[0] == 1 && passHMx[0] == 1 ){

       wpt2->Fill(eptftrue[0]);
       wset2->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
       wpt2r->Fill(ept[0]);
       wset2r->Fill(tree2->GetLeaf("set")->GetValue(0));//setZB
     
       wsetpt2->Fill(tree2->GetLeaf("setZB")->GetValue(0), eptftrue[0]);
     }
  }
 }

wsetpt1->Scale(wsetpt2->Integral()/wsetpt1->Integral());
 wsetpt2->Divide(wsetpt2, wsetpt1,1.0,1.0,"B");
 wsetpt2->Draw("box");
 c1->Update();
 c1->Print("PlotSETPTWeight_"+var+".eps");
 c1->Print("PlotSETPTWeight_"+var+".gif");

 //now, redraw the pt/set distribution but reweighted via the 2d histogram

 
 for (int i = 0; i < nentries; i++){
   tree1->GetEntry(i);
   // if(tree1->GetLeaf("ccgen")->GetValue(0) == 1  && tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25){
   if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("met")->GetValue(0) > 25 && tree1->GetLeaf("wut")->GetValue(0) < 15  && tree1->GetLeaf("mt")->GetValue(0) < 200 && tree1->GetLeaf("mt")->GetValue(0) > 50 ){
     //     t->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));//setZBgen")->GetValue(0));
     
     // if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("cut2")->GetValue(0) == 1 &&tree1->GetLeaf("passesEMIDEff")->GetValue(0) == 1 && tree1->GetLeaf("passesPreselEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrkEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrigEff")->GetValue(0) == 1  ){//&& tree1->GetLeaf("passesUParaCorrection")->GetValue(0) == 1 && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){

     if(tree1->GetLeaf("passesAllEffs")->GetValue(0) == 1 ){//includes AddOnEff, no SET EFF

       t->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));//setZBgen")->GetValue(0)); //without weight
       //tcut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));//setZBgen")->GetValue(0)); //without weight
       tcut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2->GetBinContent(wsetpt2->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)), wsetpt2->GetYaxis()->FindBin(tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
       // cout<<tree1->GetLeaf(var)->GetValue(0)<<endl;
       
       wpttestt->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0), wsetpt2->GetBinContent(wsetpt2->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)), wsetpt2->GetYaxis()->FindBin(tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
       wpttestr->Fill(tree1->GetLeaf("pt")->GetValue(0), wsetpt2->GetBinContent(wsetpt2->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)), wsetpt2->GetYaxis()->FindBin(tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
       wsettestt->Fill(tree1->GetLeaf("setZBgen")->GetValue(0), wsetpt2->GetBinContent(wsetpt2->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)), wsetpt2->GetYaxis()->FindBin(tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
       wsettestr->Fill(tree1->GetLeaf("set")->GetValue(0), wsetpt2->GetBinContent(wsetpt2->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)), wsetpt2->GetYaxis()->FindBin(tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );

     }
   }
 }


 /** 
 t->SetMarkerSize(1);
  b->SetMarkerSize(1);
  //// t->Scale(b->Integral()/t->Integral());//scale to "mc"
  t->Draw("pe");
   b->SetMarkerColor(kRed);
   b->SetLineColor(kRed);
   b->Scale(t->Integral()/b->Integral());//scale to "data"
   b->Draw("pe same");
c1->Update();
 c1->Print("PlotSETPTNoCut_"+var+".eps");
 c1->Print("PlotSETPTNoCut_"+var+".gif");

 TCanvas *c2 = new TCanvas("c2","c2",800,800);
 tcut->SetMarkerSize(1);
  bcut->SetMarkerSize(1);
  //// t->Scale(b->Integral()/t->Integral());//scale to "mc"
  tcut->Draw("pe");
   bcut->SetMarkerColor(kRed);
   bcut->SetLineColor(kRed);
   bcut->Scale(tcut->Integral()/bcut->Integral());//scale to "data"
   bcut->Draw("pe same");
c2->Update();
c2->Print("PlotSETPTCut_"+var+".eps");
c2->Print("PlotSETPTCut_"+var+".gif");
 
 **/
 t->SetMarkerSize(1);
  tcut->SetMarkerSize(1);
  //// t->Scale(tcut->Integral()/t->Integral());//scale to "mc"
  t->Draw("pe");
   tcut->SetMarkerColor(kRed);
   tcut->SetLineColor(kRed);
   // t->Scale(b->Integral()/t->Integral());
   // tcut->Scale(bcut->Integral()/tcut->Integral());
   //   // tcut->Scale(t->Integral()/tcut->Integral());//scale to "data"
   tcut->Draw("pe same");
c1->Update();
 c1->Print("PlotSETPTPMCS_"+var+".eps");
 c1->Print("PlotSETPTPMCS_"+var+".gif");
 /**
 TCanvas *c2 = new TCanvas("c2","c2",800,800);
 b->SetMarkerSize(1);
  bcut->SetMarkerSize(1);
  //// t->Scale(b->Integral()/t->Integral());//scale to "mc"
  b->Draw("pe");
   bcut->SetMarkerColor(kRed);
   bcut->SetLineColor(kRed);
   // bcut->Scale(b->Integral()/bcut->Integral());//scale to "data"
   bcut->Draw("pe same");
c2->Update();
c2->Print("PlotSETPTCAFE_"+var+".eps");
c2->Print("PlotSETPTCAFE_"+var+".gif");
  **/
 TCanvas *c3 = new TCanvas("c3","c3",800,800);

 /**
 t->Divide(t, b,1.0,1.0,"B");
 tcut->Divide(tcut, bcut,1.0,1.0,"B");

 t->SetMaximum(2.0);
 t->SetMinimum(0.0);
 tcut->SetMaximum(2.0);
 tcut->SetMinimum(0.0);

  t->SetMarkerSize(1);
  tcut->SetMarkerSize(1);
  //// t->Scale(b->Integral()/t->Integral());//scale to "mc"
  t->Draw("pe");
  //  b->SetMarkerColor(kRed);
  // b->SetLineColor(kRed);
  // b->Scale(t->Integral()/b->Integral());//scale to "data"
  // b->Draw("pe same");
  tcut->SetMarkerColor(kRed);
  tcut->SetLineColor(kRed);
  tcut->Draw("pe same");

gPad->Update();
c3->Update();

c3->Print("PlotSETPTEff_"+var+".eps");
c3->Print("PlotSETPTEff_"+var+".gif");
**/

t->Divide(tcut, t,1.0,1.0,"B");
 t->SetMaximum(2.0);
 t->SetMinimum(0.0);
  t->SetMarkerSize(1);
  t->Draw("pe");

  /**
 b->Divide(bcut, b,1.0,1.0,"B");
 b->SetMaximum(2.0);
 b->SetMinimum(0.0);
  b->SetMarkerSize(1);
  b->SetMarkerColor(kRed);
  b->SetLineColor(kRed);
  b->Draw("pe same");
  **/

gPad->Update();
c3->Update();

  //xmin, xmax, numpar  range only used if R option specified in fit
//TF1 *func = new TF1("func",fitf,0,7,3);
// TF1 *func = new TF1("func",fitf,0,7,10);
 TF1 *func = new TF1("func",fitf,0,7,5);
 func->SetLineColor(kRed);
 // -2.729  13.8452  -29.9368  24.1911  0  
 func->SetParameter(0, 1);
  func->SetParameter(1, -0.1);
  func->SetParameter(2, 0.01);
    func->SetParameter(3, -0.001);
   func->SetParameter(4, 0);

   // func->SetParameter(5, 0.5);
   //  func->SetParameter(6, 1);
   //  func->SetParameter(7, 1);
   //  func->SetParameter(8, 1);
   //  func->SetParameter(9, 0);


 t->Fit("func", "+");
gPad->Update();
c3->Update();
c3->Print("PlotSETPTEffcutnocut_"+var+".eps");
c3->Print("PlotSETPTEffcutnocut_"+var+".gif");

/**
 TCanvas *c4 = new TCanvas("c4","c4",800,800);
 wpttestt->Scale(wpt2->Integral()/wpttestt->Integral());
 wpttestt->Draw();
 wpt2->SetMarkerColor(kRed);
 wpt2->SetLineColor(kRed);
 wpt2->Draw("same");

 c4->Update();

 TCanvas *c5 = new TCanvas("c5","c5",800,800);
 wpttestr->Scale(wpt2r->Integral()/wpttestr->Integral());
 wpttestr->Draw();
 wpt2r->SetMarkerColor(kRed);
 wpt2r->SetLineColor(kRed);
 wpt2r->Draw("same");

 c5->Update();

 TCanvas *c6 = new TCanvas("c6","c6",800,800);
 wsettestt->Scale(wset2->Integral()/wsettestt->Integral());
 wsettestt->Draw();
 wset2->SetMarkerColor(kRed);
 wset2->SetLineColor(kRed);
 wset2->Draw("same");

 c6->Update();

 TCanvas *c7 = new TCanvas("c7","c7",800,800);
 wsettestr->Scale(wset2r->Integral()/wsettestr->Integral());
 wsettestr->Draw();
 wset2r->SetMarkerColor(kRed);
 wset2r->SetLineColor(kRed);
 wset2r->Draw("same");

 c7->Update();
**/

/**
  TCanvas *c2 = new TCanvas("c2","c2",800,800);

  
  // histograms for chi2
  TH1 *histo_chi2;
  
  TH1F *temp_chi2 = new TH1F("temp_chi2", "", t->GetNbinsX(), t->GetXaxis()->GetXmin(), t->GetXaxis()->GetXmax());
  TProfile *h2 = dynamic_cast<TProfile *>(t);
  
  if(h2 != 0) {
    histo_chi2 = (TH1F *)temp_chi2->Clone();
    histo_chi2->SetName("test");
    histo_chi2->Reset();
  } else {
    histo_chi2 = (TH1F *)t->Clone();
    histo_chi2->SetName("test");
    histo_chi2->Reset();
  }
  
  if(t->GetNbinsX() != b->GetNbinsX()) {
    cout<<"**** Chi2 calculation: Different number of bins! ***"<<endl;
    return;
  }

  Int_t NBin = 0; //number of bins used to calculate chi2
  Double_t chisq = 0;
  Double_t delta;
  Double_t n1,n2;
  Double_t error1, error2;

  // do not need to normalize histograms
  for (Int_t i=0;i<t->GetNbinsX(); i++) {
    double center = t->GetXaxis()->GetBinCenter(i+1);
    if((center >= xmin) && (center <= xmax)) {
      n1 = t->GetBinContent(i+1);
      n2 = b->GetBinContent(i+1);
      error1=t->GetBinError(i+1);
      error2=b->GetBinError(i+1);
      if(fabs(n1)<0.001) error1 = 1.;  // if no entries for data, assign the error to 1

      // only look at entries where fast MC distribution have some entries
      if(fabs(n2)>0.){
        NBin ++;
        delta = n1-n2;
        chisq += delta*delta/(error1*error1+error2*error2);
	cout<<center<<"  "<<n1<<"  "<<error1<<"  "<<n2<<"  "<<error2<<"  "<<delta<<"  "<<delta/sqrt(error1*error1+error2*error2)<<endl;
        histo_chi2->SetBinContent(i+1, delta/sqrt(error1*error1+error2*error2));
        histo_chi2->SetBinError(i+1, 1);
      } else {
        histo_chi2->SetBinContent(i+1, 0.);
        histo_chi2->SetBinError(i+1, 1);
      }
    } // for given range
  }//loop over all bins
  histo_chi2->SetMarkerStyle(8);
  histo_chi2->SetMarkerSize(0.5);
  histo_chi2->SetMarkerColor(2);
  histo_chi2->SetLineColor(1);

  char name[150]; 
  sprintf(name, "#chi distribution");

  histo_chi2->SetTitle(name);

  histo_chi2->Draw("pe ");

gPad->Update();
c2->Update();
c2->Print("PlotChiset.eps");
c2->Print("PlotChiset.gif");
**/
/**

  TCanvas *c3 = new TCanvas("c3","c3",800,800);
 t->Divide(t, b,1.0,1.0,"B");
 t->SetMarkerSize(1);
 b->SetMarkerSize(1);
 t->SetMarkerStyle(20);
 b->SetMarkerStyle(20);
 t->Draw("pe");
 

gPad->Update();
c3->Update();
c3->Print("PlotEffset.eps");
c3->Print("PlotEffset.gif");
c3->Print("PlotEffset.C");

**/
}

 /**
 wpt1->Scale(wpt2->Integral()/wpt1->Integral());

 wset1->Scale(wset2->Integral()/wset1->Integral());
 wpt2->Divide(wpt2, wpt1,1.0,1.0,"B");
 wset2->Divide(wset2, wset1,1.0,1.0,"B");
 
 wpt2->SetMarkerSize(1);
 wset2->SetMarkerSize(1);
 //// wpt2->Scale(wset2->Integral()/wpt2->Integral());//scale to "mc"
 wpt2->Draw("pe");
 wset2->SetMarkerColor(kRed);
 wset2->SetLineColor(kRed);
 // wset2->Scale(wpt2->Integral()/wset2->Integral());//scale to "data"
 wset2->Draw("pe same");
 c1->Update();
 **/

 Double_t fitf(Double_t *v, Double_t *par)
   {
      return (par[0] + par[1]*v[0] + par[2]*v[0]*v[0] + par[3]*v[0]*v[0]*v[0] + par[4]*v[0]*v[0]*v[0]*v[0]);//*(par[5] + par[6]*v[0] + par[7]*v[0]*v[0] + par[8]*v[0]*v[0]*v[0] + par[9]*v[0]*v[0]*v[0]*v[0]);
     // return 0.5 * par[2] * (1. + TMath::Erf((v[0]-par[0])/(sqrt(2)*par[1])))*(1. + TMath::Erf((v[0]-par[4])/(sqrt(2)*par[3])));

     //return 0.5 * par[2] * (1. + TMath::Erf((v[0]-par[0])/(sqrt(2)*par[1])))*( par[3]*v[0] + par[4]*v[0]*v[0] );

     //return 0.5 * par[2] * (1. + TMath::Erf((v[0]-par[0])/(sqrt(2)*par[1])));

     //return 0.5 * (par[0] + par[5]*v[0] + par[6]*v[0]*v[0]) * (1. + TMath::Erf((v[0]-par[1])/(sqrt(2)*par[2])))*(1. + TMath::Erf((v[0]-par[3])/(sqrt(2)*par[4])));

   }
