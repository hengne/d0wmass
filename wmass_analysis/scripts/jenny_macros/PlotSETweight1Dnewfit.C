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
double GetEff (int lumi, double setoverpt);

void PlotSETweight1Dnewfit(){

  gROOT->ProcessLine(".x /home/jholzbau/rootlogon.C");

  TString var = "ptset1D";

  TH1::SetDefaultSumw2();

  //test files
  //   TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_allcuteff_default_20120712_142246/testWTree3.root";
  //  TString rootfile2 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_test_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy/cafe_alleff_test_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy_run34.root";
 
   //run12 files
  //TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_allcuteff_default_run12_20120718_163832/test.root";
  // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/new_run12_alleff_zbset/new_run12_alleff_zbset.root";

   //run3 files
   TString rootfile1 = "/prj_root/5007/wz2_write/jenny/seteffgood/pythia_wen_run2b3_treetestnoeff_allcuteff_default_20120801_153809/test.root"; 
   TString rootfile2 = "/prj_root/5007/wz2_write/jenny/seteffgood/new_run34_boringandalleff/ueff5_withdq_onevtx_200files_vtxcut_nostudy2/ueff5_withdq_onevtx_200files_vtxcut_nostudy2_run3.root";


 Double_t xmin = 0;
 Double_t xmax = 400;
 Double_t xmax2 = 150;
 Int_t nbin = 50;

 TH1D *wpttestt = new TH1D("wpttestt", "wpttestt",  nbin, xmin, xmax2);
 TH1D *wpttestr = new TH1D("wpttestr", "wpttestr",  nbin, xmin, xmax2);
 TH1D *wsettestt = new TH1D("wsettestt", "wsettestt",  nbin, xmin, xmax);
 TH1D *wsettestr = new TH1D("wsettestr", "wsettestr",  nbin, xmin, xmax);

 TH1D *wpt2xxr = new TH1D("wpt2xxr", "wpt2xxr",  nbin, xmin, xmax2);
 TH1D *wset2xxr = new TH1D("wset2xxr", "wset2xxr",  nbin, xmin, xmax);
 TH1D *wpt2xx = new TH1D("wpt2xx", "wpt2xx",  nbin, xmin, xmax2);
 TH1D *wset2xx = new TH1D("wset2xx", "wset2xx",  nbin, xmin, xmax);

 xmin = 0;
 xmax = 7;
 nbin = 200;
 
 TH1D *t = new TH1D("top", "top",  nbin, xmin, xmax);
 TH1D *tcut = new TH1D("topcut", "topcut",  nbin, xmin, xmax);
 TH1D *tgen = new TH1D("topgen", "topgen",  nbin, xmin, xmax);
 TH1D *tcutgen = new TH1D("topcutgen", "topcutgen",  nbin, xmin, xmax);

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
double edeteta[10];
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
 tree2->SetBranchAddress("edeteta", edeteta);
 tree2->SetBranchAddress("epttrue", epttrue);
 tree2->SetBranchAddress("eptftrue", eptftrue);
  
 for (int j = 0; j < nentries2; j++){
   tree2->GetEntry(j);

   if(passCC[0] == 1 && (ept[0] > 25 ) && tree2->GetLeaf("passCutUt")->GetValue(0) == 1 && tree2->GetLeaf("met")->GetValue(0) > 25 && tree2->GetLeaf("passCutWMt")->GetValue(0) == 1 ){
 if(passEmf[0] == 1 && passIso[0] == 1  && passTrkPhiFid[0] == 1  && passCalEtaFid[0] == 1 &&  passTkMatch[0] == 1 && passHMx[0] == 1 ){

       wpt2xx->Fill(eptftrue[0]);
       wset2xx->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
       wpt2xxr->Fill(ept[0]);
       wset2xxr->Fill(tree2->GetLeaf("set")->GetValue(0));//setZB
       t->Fill(tree2->GetLeaf("set")->GetValue(0)/ept[0]);
       tgen->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }
  }
 }

 for (int i = 0; i < nentries; i++){
   tree1->GetEntry(i);
   if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("met")->GetValue(0) > 25 && tree1->GetLeaf("wut")->GetValue(0) < 15  && tree1->GetLeaf("mt")->GetValue(0) < 200 && tree1->GetLeaf("mt")->GetValue(0) > 50 ){
     // if(tree1->GetLeaf("passesAllEffs")->GetValue(0) == 1 ){//includes AddOnEff, no SET EFF
     if(tree1->GetLeaf("passesEMIDEff")->GetValue(0) == 1 && tree1->GetLeaf("passesPreselEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrkEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrigEff")->GetValue(0) == 1 ){// && tree1->GetLeaf("passesUParaCorrection")->GetValue(0) == 1){// && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){
       
       // t->Fill(tree1->GetLeaf("pt")->GetValue(0)/tree1->GetLeaf("set")->GetValue(0));//setZBgen")->GetValue(0)); //without weight
       
       tcutgen->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0), GetEff ((int) tree1->GetLeaf("lumigen")->GetValue(0), tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0)));

      tcut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), GetEff ((int) tree1->GetLeaf("lumigen")->GetValue(0), tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0)));
       
       wpttestt->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0), GetEff ((int) tree1->GetLeaf("lumigen")->GetValue(0), tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0)));
       wpttestr->Fill(tree1->GetLeaf("pt")->GetValue(0), GetEff ((int) tree1->GetLeaf("lumigen")->GetValue(0), tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0)));
       wsettestt->Fill(tree1->GetLeaf("setZBgen")->GetValue(0), GetEff ((int) tree1->GetLeaf("lumigen")->GetValue(0), tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0)));
       wsettestr->Fill(tree1->GetLeaf("set")->GetValue(0), GetEff ((int) tree1->GetLeaf("lumigen")->GetValue(0), tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0)));

     }
   }
 }
 TCanvas *c2 = new TCanvas("c2","c2",800,800);
 tcutgen->Scale(tgen->Integral()/tcutgen->Integral());
 tcutgen->Draw();
 tgen->SetMarkerColor(kRed);
 tgen->SetLineColor(kRed);
 tgen->Draw("same");

 c2->Update();
 c2->Print("PlotSETPTPMCS_TruthVarAfterFIT_"+var+".eps");
 c2->Print("PlotSETPTPMCS_TruthVarAfterFIT_"+var+".gif");

 TCanvas *c3 = new TCanvas("c3","c3",800,800);
 tcut->Scale(t->Integral()/tcut->Integral());
 tcut->Draw();
 t->SetMarkerColor(kRed);
 t->SetLineColor(kRed);
 t->Draw("same");

 c3->Update();
 c3->Print("PlotSETPTPMCS_RecoVarAfterFIT_"+var+".eps");
 c3->Print("PlotSETPTPMCS_RecoVarAfterFIT_"+var+".gif");

 TCanvas *c4 = new TCanvas("c4","c4",800,800);
 wpttestt->Scale(wpt2xx->Integral()/wpttestt->Integral());
 wpttestt->Draw();
 wpt2xx->SetMarkerColor(kRed);
 wpt2xx->SetLineColor(kRed);
 wpt2xx->Draw("same");

 c4->Update();

 TCanvas *c5 = new TCanvas("c5","c5",800,800);
 wpttestr->Scale(wpt2xxr->Integral()/wpttestr->Integral());
 wpttestr->Draw();
 wpt2xxr->SetMarkerColor(kRed);
 wpt2xxr->SetLineColor(kRed);
 wpt2xxr->Draw("same");

 c5->Update();

 TCanvas *c6 = new TCanvas("c6","c6",800,800);
 wsettestt->Scale(wset2xx->Integral()/wsettestt->Integral());
 wsettestt->Draw();
 wset2xx->SetMarkerColor(kRed);
 wset2xx->SetLineColor(kRed);
 wset2xx->Draw("same");

 c6->Update();

 TCanvas *c7 = new TCanvas("c7","c7",800,800);
 wsettestr->Scale(wset2xxr->Integral()/wsettestr->Integral());
 wsettestr->Draw();
 wset2xxr->SetMarkerColor(kRed);
 wset2xxr->SetLineColor(kRed);
 wset2xxr->Draw("same");

 c7->Update();

}
double GetEff (int lumi, double setoverpt){
  double eff = 0;
  double par0 = 0;
  double par1 = 0;
  double par2 = 0;
  double par3 = 0;
  double par4 = 0;
  /**
  par0 = 1.14448;
  par1 = -0.103830;
  par2 = 0.0451008;
  par3 = -0.0106998;
  par4 = 0.000748485;
  **/
 par0 = 1.13363;
  par1 = -0.0884468;
  par2 = 0.0377727;
  par3 = -0.00927218;
  par4 = 0.000652768;

  lumi = lumi + 0;
  /**
 if(lumi < 2){
  par0 = 1.13712;
  par1 = -0.107732;
  par2 = 0.0319787;
  par3 = -0.00746396;
  par4 = 0.000451814;

 }else if(lumi >= 2 && lumi < 4){
  par0 = 1.07278;
  par1 = -0.0216144;
  par2 = 0.00380564;
  par3 = -0.00266845;
  par4 = 0.000234566;

 }else if(lumi >= 4 && lumi < 6){
  par0 = 1.09246;
  par1 = -0.0674452;
  par2 = 0.0399800;
  par3 = -0.0103403;
  par4 = 0.000725726;

 } else if (lumi >= 6){
  par0 = 1.02352;
  par1 = 0.115659;
  par2 =  -0.0402273;
  par3 =  0.00256644;
  par4 = 0.0000227340;

 }
  **/

 //setoverpt = 1;
 //eff = 1;// 0.5 * par2 * (1. + TMath::Erf((setoverpt-par0)/(sqrt(2)*par1)));
  //  cout<<setoverpt<<"  "<<eff<<endl;
 eff =  par0 + par1*setoverpt + par2*setoverpt*setoverpt + par3*setoverpt*setoverpt*setoverpt + par4*setoverpt*setoverpt*setoverpt*setoverpt;

  return eff;
}
/**
//redone run3 all, closer starting parameters
  EXT PARAMETER                                   STEP         FIRST
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
   1  p0           1.13363e+00   6.41769e-03   5.40555e-07   1.38019e-07
   2  p1          -8.84468e-02   9.59140e-03   1.52634e-07   2.90950e-08
   3  p2           3.77727e-02   4.90135e-03   4.36358e-08  -1.47936e-06
   4  p3          -9.27218e-03   1.02854e-03   1.11085e-08  -8.79503e-06
   5  p4           6.52768e-04   7.48921e-05   2.42845e-09  -2.01156e-05


  TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b3_treetestnoeff_allcuteff_default_20120801_153809/test.root"; 
   TString rootfile2 = "/prj_root/5007/wz2_write/jenny/new_run34_boringandalleff/ueff5_withdq_onevtx_200files_vtxcut_nostudy2/ueff5_withdq_onevtx_200files_vtxcut_nostudy2_run3.root";
run3, all then by lumi bin (all, 0-2, 2-4, 4-6, 6+):
 FCN=22.7199 FROM MIGRAD    STATUS=CONVERGED     178 CALLS         179 TOTAL
                     EDM=2.42355e-15    STRATEGY= 1      ERROR MATRIX ACCURATE
  EXT PARAMETER                                   STEP         FIRST
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
   1  p0           1.14448e+00   6.78171e-03   7.01066e-07  -4.14559e-05
   2  p1          -1.03830e-01   1.00715e-02   2.23732e-07  -1.35570e-04
   3  p2           4.51008e-02   5.10541e-03   6.39668e-08  -3.10885e-04
   4  p3          -1.06998e-02   1.06194e-03   1.61529e-08   2.22143e-04
   5  p4           7.48485e-04   7.67078e-05   3.48788e-09   1.02954e-02
 FCN=94.8159 FROM MIGRAD    STATUS=CONVERGED     139 CALLS         140 TOTAL
                     EDM=4.88782e-09    STRATEGY= 1      ERROR MATRIX ACCURATE
  EXT PARAMETER                                   STEP         FIRST
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
   1  p0           1.13712e+00   1.52000e-02   3.54829e-06  -5.52040e-02
   2  p1          -1.07732e-01   2.79632e-02   1.76358e-06  -1.48961e-01
   3  p2           3.19787e-02   1.73810e-02   7.70631e-07  -4.66778e-01
   4  p3          -7.46396e-03   4.23580e-03   2.58282e-07  -1.75229e+00
   5  p4           4.51814e-04   3.43317e-04   6.01404e-08  -7.78022e+00
 FCN=25.2144 FROM MIGRAD    STATUS=CONVERGED     163 CALLS         164 TOTAL
                     EDM=5.03942e-12    STRATEGY= 1      ERROR MATRIX ACCURATE
  EXT PARAMETER                                   STEP         FIRST
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
   1  p0           1.07278e+00   7.91665e-03   9.12296e-07   6.48005e-03
   2  p1          -2.16144e-02   1.27893e-02   3.38046e-07   1.47145e-02
   3  p2           3.80564e-03   6.96264e-03   1.11765e-07   3.02868e-02
   4  p3          -2.66845e-03   1.53527e-03   3.17088e-08   3.50069e-02
   5  p4           2.34566e-04   1.16422e-04   7.30187e-09  -1.73300e-01
 FCN=32.7713 FROM MIGRAD    STATUS=CONVERGED     195 CALLS         196 TOTAL
                     EDM=6.36207e-11    STRATEGY= 1      ERR MATRIX NOT POS-DEF
  EXT PARAMETER                APPROXIMATE        STEP         FIRST
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
   1  p0           1.09246e+00   1.35477e-03   5.20924e-07  -7.13558e-02
   2  p1          -6.74452e-02   4.83973e-04   1.17597e-07  -2.69835e-01
   3  p2           3.99800e-02   1.30177e-04   3.08991e-08  -1.02746e+00
   4  p3          -1.03403e-02   3.41248e-05   8.06613e-09  -3.96115e+00
   5  p4           7.25726e-04   5.67302e-06   2.07892e-09  -1.50717e+01
 FCN=27.5828 FROM MIGRAD    STATUS=CONVERGED     188 CALLS         189 TOTAL
                     EDM=6.47154e-17    STRATEGY= 1      ERR MATRIX NOT POS-DEF
  EXT PARAMETER                APPROXIMATE        STEP         FIRST
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
   1  p0           1.02352e+00   6.24316e-03   2.75663e-06  -1.12769e-07
   2  p1           1.15659e-01   2.80078e-03   6.59674e-07   9.29009e-07
   3  p2          -4.02273e-02   6.32948e-04   1.46309e-07   3.88517e-06
   4  p3           2.56644e-03   1.37213e-04   3.02338e-08  -5.49350e-05
   5  p4           2.27340e-05   1.60412e-05   5.79860e-09   1.43981e-04
**/
