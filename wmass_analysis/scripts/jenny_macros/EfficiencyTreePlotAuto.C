#include <TFile.h>
#include <TH1.h>
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

//**********************************************************
//Change this line if your TTree has a different name
//const char *TreeName1 = "tree;1";
const char *TreeName1 = "w;1";
const char *TreeName2 = "tree;1";
//const char *TreeName1 = "wgen;1";
//const char *TreeName2 = "w;1";
//const char *TreeName2 = "binary_tuple;1";
//**********************************************************
void PlotEff(TString var, TString cafevar, Double_t xmin, Double_t xmax, Int_t nbin, bool cafeelvec);

void EfficiencyTreePlotAuto(){

  gROOT->ProcessLine(".x /home/jholzbau/rootlogon.C");
  //.x /home/jholzbau/rootlogon.C
  // TH1::Sumw2();
  //TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_allcuteff_default_20120712_142246/testWTree3.root";
  // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_check/cafe_alleff_check_run34.root";
  // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_ueff4_withdq_withvtxcut_onevtx_big/test.root";
  
  // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy/test.root"; //includes SETZB, small test
  //  PlotEff("lumi", "lumi", -3, 15, 50, false);
  // PlotEff("setZB", "setZB", 0, 200, 100, false);
  PlotEff("wfsr_ptgen", "eptftrue", 25, 60, 20, true);
 PlotEff("deteta", "edeteta", -1.1, 1.1, 11, true);
  /** 
  PlotEff("deteta", "edeteta", -1.1, 1.1, 11, true);
  PlotEff("upara", "upara", -30, 30, 50, true);
  
  PlotEff("detetagen", "edetetatrue", -1.5, 1.5, 50, true);
  //  PlotEff("deteta", "edeteta", -1.5, 1.5, 50, true);
  //  PlotEff("wfsr_ptgen", "eptftrue", 0, 75, 50, true);
  PlotEff("pt", "ept", 0, 100, 50, true);
  // PlotEff("upara", "upara", 0, 20, 50, true);
  PlotEff("lumi", "lumi", 0, 15, 50, false);
  PlotEff("setZB", "setZB", 0, 200, 100, false);
  PlotEff("wut", "ut", 0, 20, 50, false);
  PlotEff("set", "set", 0, 200, 100, false);
  // PlotEff("eta", "eeta", -3, 3, 50, true);
  PlotEff("eta", "eeta", -1.5, 1.5, 50, true);
  **/

  //doesn't exist in cafe uEventAnalysis tree// PlotEff("upara", "upara", 0, 150, 50, false);
   //doesn't exist in pmcs tree in old version// PlotEff("deteta", "edeteta", -3, 3, 50, true);//check name
   //need a special run for vtx.  need multiple files and also different vector index (2)

}
void PlotEff(TString var, TString cafevar, Double_t xmin, Double_t xmax, Int_t nbin, bool cafeelvec){
  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  TH1::SetDefaultSumw2();

 //---------------------------------------------------
  //early test files
  //  //  TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_allcuteff_default_20120712_142246/testWTree3.root";
  // //  //  TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy/test.root"; //includes SETZB, small test
    // TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_allcuteff_default_20120718_141821/test.root"; //corrected deteta, still with vtx cut

  //  //    TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_test_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy/cafe_alleff_test_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy_run34.root"; //MCSTUDY2
  //  // //  TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_new_ueff4_withdq_withvtxcut_onevtx_500files/cafe_alleff_new_ueff4_withdq_withvtxcut_onevtx_500files_run34.root";
  //  TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_eff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy_500files_novtxx_nostudy2_missingfiles/cafe_alleff_eff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy_500files_novtxx_nostudy2_missingfiles.root"; //MCSTUDY

  //---------------------------------------------------
  //run1+2 (** = recently used)
  //TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_allcuteff_default_novtxcut_run12_20120718_163835/test.root";
  // ** 
TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_allcuteff_default_run12_20120718_163832/test.root";
  //    TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_allcuteff_default_novtxcut_run12_20120718_163835/test.root";

// TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_new2/cafe_alleff_new2_ueff5_withdq_onevtx_50files_novtx_run12.root";
  //  TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_new2/cafe_alleff_new2_ueff5_withdq_onevtx_50files_vtxcut_nostudy2_run12.root";
   //   TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_new2/cafe_alleff_new2_ueff5_withdq_onevtx_50files_novtx_run12.root";


 //   **   TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_new500runs/ueff5_withdq_onevtx_500files_vtxcut/cafe_alleff_new500runs_ueff5_withdq_onevtx_500files_vtxcut.root";
 TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_ueff5_withdq_onevtx_200files_vtxcut_run12_PUBVERSION/cafe_alleff_ueff5_withdq_onevtx_200files_vtxcut_run12_PUBVERSION.root"; //new file with publication version of run1+2, v2011-09-30 dq_defs version
  //   ** 
  //TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_new500runs/ueff5_withdq_onevtx_500files_vtxcut_nostudy2/cafe_alleff_new500runs_ueff5_withdq_onevtx_500files_vtxcut_nostudy2.root";//very different than first one, seems to have diff selections applied???

 //   ** TString rootfile2 = "/prj_root/5007/wz2_write/jenny/new_run12_alleff_zbset/new_run12_alleff_zbset.root";

  // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_new500runs/ueff5_withdq_onevtx_500files_novtx/cafe_alleff_new500runs_ueff5_withdq_onevtx_500files_novtx.root";
 // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_new500runs/ueff5_withdq_onevtx_500files_novtxcut_nostudy2/cafe_alleff_new500runs_eff5_withdq_onevtx_500files_novtxcut_nostudy2.root";

     int run34 = 12;
     TString runvar = "run12";
//---------------------------------------------------
//run3 or 4

// TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b3_treetestnoeff_allcuteff_default_20120801_153809/test.root"; 
//  TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b4_treetestnoeff_allcuteff_default_20120801_153809/test.root"; 

 //need no mcstudy2 files for upara...!!!!
 // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/new_run34_boringandalleff/ueff5_withdq_onevtx_200files_vtxcut_nostudy2/ueff5_withdq_onevtx_200files_vtxcut_nostudy2_run3.root";

 // int run34 = 3;
     // TString runvar = "run3";
 //---------------------------------------------------

  TH1D *t = new TH1D("top", "top",  nbin, xmin, xmax);
  TH1D *b = new TH1D("bottom", "bottom",  nbin, xmin, xmax);
  TH1D *tcut = new TH1D("topcut", "topcut",  nbin, xmin, xmax);
  TH1D *bcut = new TH1D("bottomcut", "bottomcut",  nbin, xmin, xmax);
  t->GetXaxis()->SetTitle(var);
  b->GetXaxis()->SetTitle(var);
  tcut->GetXaxis()->SetTitle(var);
  bcut->GetXaxis()->SetTitle(var);
  
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
bool passTkMatchLoose[10];
double ept[10];
double epttrue[10];
double eptftrue[10];
double varvec[10];
double eetaftrue[10];
double edeteta[10];
double edetetatrue[10];

 tree2->SetBranchAddress("passCC", passCC);
 tree2->SetBranchAddress("passCCTrue", passCCTrue);
 tree2->SetBranchAddress("passEmf", passEmf);
 tree2->SetBranchAddress("passIso", passIso);
 tree2->SetBranchAddress("passHMx", passHMx);
 tree2->SetBranchAddress("passCalEtaFid", passCalEtaFid);
 tree2->SetBranchAddress("passTrkPhiFid", passTrkPhiFid);
 tree2->SetBranchAddress("passTkMatch", passTkMatch);
 tree2->SetBranchAddress("passTkMatchLoose", passTkMatchLoose);
 tree2->SetBranchAddress("ept", ept);
 tree2->SetBranchAddress("epttrue", epttrue);
 tree2->SetBranchAddress("eptftrue", eptftrue);
 tree2->SetBranchAddress("edeteta", edeteta);
 tree2->SetBranchAddress("edetetatrue", edetetatrue);
 tree2->SetBranchAddress("eetaftrue", eetaftrue);
 tree2->SetBranchAddress(cafevar, varvec);
 
 //in Cafe, set study uses fsr merged cone objects (even though called raw there).  So we use eptftrue

 int countp1 = 0;
 int countp2 = 0;
 int countc1 = 0;
 int countc2 = 0;
 double _runNumber = 0;

 for (int i = 0; i < nentries; i++){
   tree1->GetEntry(i);
   //if(tree1->GetLeaf("cc")->GetValue(0) == 1 ){
   //  if(tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25){//was ccgen
   //  if(tree1->GetLeaf("pt")->GetValue(0) > 25){
   //  if(tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25 ){//&& fabs(tree1->GetLeaf("deteta")->GetValue(0)) < 1.05){
   _runNumber = tree1->GetLeaf("rungen")->GetValue(0);
   if( (run34 == 3 && _runNumber < 263000) || (run34 == 4 && _runNumber > 263000) || (run34 == 1) || (run34 == 2) || (run34 == 12) ){//run2b3 is below 263000 and run 2b4 is higher than 264000

     if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("met")->GetValue(0) > 25 && tree1->GetLeaf("wut")->GetValue(0) < 15  && tree1->GetLeaf("mt")->GetValue(0) < 200 && tree1->GetLeaf("mt")->GetValue(0) > 50 ){//&& tree1->GetLeaf("cut")->GetValue(0) == 1){
   //  if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25){// && tree1->GetLeaf("met")->GetValue(0) > 25 && tree1->GetLeaf("wut")->GetValue(0) < 15  && tree1->GetLeaf("mt")->GetValue(0) < 200 && tree1->GetLeaf("mt")->GetValue(0) > 50 ){

     
     //   if(tree1->GetLeaf("ccgen")->GetValue(0) == 1  && tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25 && tree1->GetLeaf("wutgen")->GetValue(0) < 15  ){//&& tree1->GetLeaf("mtgen")->GetValue(0) < 200 && tree1->GetLeaf("mtgen")->GetValue(0) > 50 ){
     
     //if(tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25){
     t->Fill(tree1->GetLeaf(var)->GetValue(0));//setZBgen")->GetValue(0));
     countp1++;
     //      if(tree1->GetLeaf("passesEMIDEff")->GetValue(0) == 1 && tree1->GetLeaf("passesPreselEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrkEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrigEff")->GetValue(0) == 1 && tree1->GetLeaf("passesUParaCorrection")->GetValue(0) == 1 && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){
       if(tree1->GetLeaf("passesAllEffs")->GetValue(0) == 1 && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){//includes AddOnEff
     // if(tree1->GetLeaf("passesEMIDEff")->GetValue(0) == 1 && tree1->GetLeaf("passesPreselEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrkEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrigEff")->GetValue(0) == 1){// && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){

     //if(tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25 && tree1->GetLeaf("wutgen")->GetValue(0) < 15  ){
     // if(tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25 && fabs(tree1->GetLeaf("detetagen")->GetValue(0)) < 1.05){
     //  if(tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("wut")->GetValue(0) < 15  && tree1->GetLeaf("met")->GetValue(0) > 25  ){// && tree1->GetLeaf("mt")->GetValue(0) < 200 && tree1->GetLeaf("mt")->GetValue(0) > 50 ){
       tcut->Fill(tree1->GetLeaf(var)->GetValue(0));//setZBgen")->GetValue(0));
       countp2++;
       // cout<<tree1->GetLeaf(var)->GetValue(0)<<endl;
    }
   }
   }
   // }
 }
 
 for (int j = 0; j < nentries2; j++){
   tree2->GetEntry(j);
    // if((eptftrue[0] > 25 || (cafevar == "eptftrue" && varvec[0] > 25)) ){//&& fabs(edeteta[0]) < 1.05){//was CCTrue
    if(passCC[0] == 1 && (ept[0] > 25 || (cafevar == "ept" && varvec[0] > 25)) && tree2->GetLeaf("passCutUt")->GetValue(0) == 1 && tree2->GetLeaf("met")->GetValue(0) > 25  && tree2->GetLeaf("passCutWMt")->GetValue(0) == 1 ){

      //ept or passCC must include the electron ID selection as well, && passEmf[0] == 1   && passTrkPhiFid[0] == 1  && passCalEtaFid[0] == 1 && passIso[0] == 1 && passHMx[0] == 1, since efficiency plot is the same with or without these in first if statement.  So, cut == passTkMatch[0]...
      //apparently putting  passTkMatchLoose[0] == 1 in the first if statement doesn't matter either...

      if(cafeelvec) b->Fill(varvec[0]);
     else b->Fill(tree2->GetLeaf(cafevar)->GetValue(0));//setZB
     countc1++;

        if(passEmf[0] == 1 && passIso[0] == 1  && passTrkPhiFid[0] == 1  && passCalEtaFid[0] == 1 &&  passTkMatch[0] == 1 && passHMx[0] == 1 ){//passMET doesn't work, is 0  tree2->GetLeaf("passCutUt")->GetValue(0) == 1 && tree2->GetLeaf("ut")->GetValue(0) < 15 
     // if((eptftrue[0] > 25 || (cafevar == "eptftrue" && varvec[0] > 25)) && tree2->GetLeaf("uttrue")->GetValue(0) < 15){
     // if(fabs(edetetatrue[0]) < 1.05 && (eptftrue[0] > 25 || (cafevar == "eptftrue" && varvec[0] > 25))){//was CCTrue
     // if((ept[0] > 25 || (cafevar == "ept" && varvec[0] > 25))&& tree2->GetLeaf("ut")->GetValue(0) < 15 && tree2->GetLeaf("met")->GetValue(0) > 25){//  && tree2->GetLeaf("passCutWMt")->GetValue(0) == 1  ) {
       if(cafeelvec) bcut->Fill(varvec[0]);
       else bcut->Fill(tree2->GetLeaf(cafevar)->GetValue(0));//setZB
       countc2++;
       
     }
   }
     // }
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
 c1->Print("PlotNoCut_"+var+".eps");
 c1->Print("PlotNoCut_"+var+".gif");

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
c2->Print("PlotCut_"+var+".eps");
c2->Print("PlotCut_"+var+".gif");
 **/
 t->SetMarkerSize(1);
  tcut->SetMarkerSize(1);
  //// t->Scale(tcut->Integral()/t->Integral());//scale to "mc"
  t->Draw("pe");
   tcut->SetMarkerColor(kRed);
   tcut->SetLineColor(kRed);

   //if just want to look at shape agreement, uncomment two lines below
   //in each case, pmcs (t) is scaled to the cafe (b) histograms
   t->Scale((double) countc1/(double) countp1);
   tcut->Scale((double) countc2/(double) countp2);
   // t->Scale(b->Integral()/t->Integral());
   //tcut->Scale(bcut->Integral()/tcut->Integral());
   cout<<b->Integral()<<"  "<<countc1<<"  "<<t->Integral()<<"  "<<countp1<<"  "<<bcut->Integral()<<"  "<<countc2<<"  "<<tcut->Integral()<<"  "<<countp2<<endl;
   //cout<<countc1/countp1<<"  "<<b->Integral()/t->Integral()<<"  "<<countc2/countp2<<"  "<<bcut->Integral()/tcut->Integral()<<endl;
   //   // tcut->Scale(t->Integral()/tcut->Integral());//scale to "data"
   tcut->Draw("pe same");
c1->Update();
 c1->Print("PlotPMCS_"+var+"_"+runvar+".eps");
 c1->Print("PlotPMCS_"+var+"_"+runvar+".gif");

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
c2->Print("PlotCAFE_"+var+"_"+runvar+".eps");
c2->Print("PlotCAFE_"+var+"_"+runvar+".gif");

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

c3->Print("PlotEff_"+var+".eps");
c3->Print("PlotEff_"+var+".gif");
 **/


 
t->Divide(tcut, t,1.0,1.0,"B");
 b->Divide(bcut, b,1.0,1.0,"B");

  t->SetMaximum(1.0);
  t->SetMinimum(0.7);
  b->SetMaximum(1.0);
  b->SetMinimum(0.7);

  t->SetMarkerSize(1);
  b->SetMarkerSize(1);
  //// t->Scale(b->Integral()/t->Integral());//scale to "mc"
  t->Draw("pe");
  //  b->SetMarkerColor(kRed);
  // b->SetLineColor(kRed);
  // b->Scale(t->Integral()/b->Integral());//scale to "data"
  // b->Draw("pe same");
  b->SetMarkerColor(kRed);
  b->SetLineColor(kRed);
  b->SetLineStyle(2);
  b->Draw("le same");

gPad->Update();
c3->Update();

c3->Print("PlotEffcutnocut_"+var+"_"+runvar+".eps");
c3->Print("PlotEffcutnocut_"+var+"_"+runvar+".gif");
 
 
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
