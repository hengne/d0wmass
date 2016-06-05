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

void EfficiencyTreePlotSETweight1Dnewfit(){

  gROOT->ProcessLine(".x /home/jholzbau/rootlogon.C");

  TString var = "ptset1D";

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  TH1::SetDefaultSumw2();

  //test files
  //  TString rootfile1 = "/prj_root/5007/wz2_write/jenny/seteffgood/pythia_wen_run2b34_treetestnoeff_allcuteff_default_20120712_142246/testWTree3.root";
  // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/seteffgood/cafe_alleff_test_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy/cafe_alleff_test_ueff5_withdq_withvtxcut_onevtx_check222_mcstudysetstudy_run34.root";
 
   //run12 files
  //TString rootfile1 = "/prj_root/5007/wz2_write/jenny/seteffgood/pythia_wen_run2b34_treetestnoeff_allcuteff_default_run12_20120718_163832/test.root";
  // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/seteffgood/new_run12_alleff_zbset/new_run12_alleff_zbset.root";

   //run3 files
   TString rootfile1 = "/prj_root/5007/wz2_write/jenny/seteffgood/pythia_wen_run2b3_treetestnoeff_allcuteff_default_20120801_153809/test.root"; 
   TString rootfile2 = "/prj_root/5007/wz2_write/jenny/seteffgood/new_run34_boringandalleff/ueff5_withdq_onevtx_200files_vtxcut_nostudy2/ueff5_withdq_onevtx_200files_vtxcut_nostudy2_run3.root";


 Double_t xmin = 0;
 Double_t xmax = 400;
 Double_t xmax2 = 150;
 Int_t nbin = 50;

  TH1D *wpt1xx = new TH1D("wpt1xx", "wpt1xx",  nbin, xmin, xmax2);
  TH1D *wpt2xx = new TH1D("wpt2xx", "wpt2xx",  nbin, xmin, xmax2);

  TH1D *wset1xx = new TH1D("wset1xx", "wset1xx",  nbin, xmin, xmax);
  TH1D *wset2xx = new TH1D("wset2xx", "wset2xx",  nbin, xmin, xmax);
  
  TH1D *wpttestt = new TH1D("wpttestt", "wpttestt",  nbin, xmin, xmax2);
  TH1D *wpttestr = new TH1D("wpttestr", "wpttestr",  nbin, xmin, xmax2);
  TH1D *wsettestt = new TH1D("wsettestt", "wsettestt",  nbin, xmin, xmax);
  TH1D *wsettestr = new TH1D("wsettestr", "wsettestr",  nbin, xmin, xmax);
  TH1D *wpt2xxr = new TH1D("wpt2xxr", "wpt2xxr",  nbin, xmin, xmax2);
  TH1D *wset2xxr = new TH1D("wset2xxr", "wset2xxr",  nbin, xmin, xmax);

  TH1D *wpt1xxlumi1 = new TH1D("wpt1xxlumi1", "wpt1xxlumi1",  nbin, xmin, xmax2);
  TH1D *wpt2xxlumi1 = new TH1D("wpt2xxlumi1", "wpt2xxlumi1",  nbin, xmin, xmax2);
  TH1D *wset1xxlumi1 = new TH1D("wset1xxlumi1", "wset1xxlumi1",  nbin, xmin, xmax);
  TH1D *wset2xxlumi1 = new TH1D("wset2xxlumi1", "wset2xxlumi1",  nbin, xmin, xmax); 
 
  TH1D *wpt1xxlumi2 = new TH1D("wpt1xxlumi2", "wpt1xxlumi2",  nbin, xmin, xmax2);
  TH1D *wpt2xxlumi2 = new TH1D("wpt2xxlumi2", "wpt2xxlumi2",  nbin, xmin, xmax2);
  TH1D *wset1xxlumi2 = new TH1D("wset1xxlumi2", "wset1xxlumi2",  nbin, xmin, xmax);
  TH1D *wset2xxlumi2 = new TH1D("wset2xxlumi2", "wset2xxlumi2",  nbin, xmin, xmax);

  TH1D *wpt1xxlumi3 = new TH1D("wpt1xxlumi3", "wpt1xxlumi3",  nbin, xmin, xmax2);
  TH1D *wpt2xxlumi3 = new TH1D("wpt2xxlumi3", "wpt2xxlumi3",  nbin, xmin, xmax2);
  TH1D *wset1xxlumi3 = new TH1D("wset1xxlumi3", "wset1xxlumi3",  nbin, xmin, xmax);
  TH1D *wset2xxlumi3 = new TH1D("wset2xxlumi3", "wset2xxlumi3",  nbin, xmin, xmax);

  TH1D *wpt1xxlumi4 = new TH1D("wpt1xxlumi4", "wpt1xxlumi4",  nbin, xmin, xmax2);
  TH1D *wpt2xxlumi4 = new TH1D("wpt2xxlumi4", "wpt2xxlumi4",  nbin, xmin, xmax2);
  TH1D *wset1xxlumi4 = new TH1D("wset1xxlumi4", "wset1xxlumi4",  nbin, xmin, xmax);
  TH1D *wset2xxlumi4 = new TH1D("wset2xxlumi4", "wset2xxlumi4",  nbin, xmin, xmax);

  TH1D *wpt1xxupara1 = new TH1D("wpt1xxupara1", "wpt1xxupara1",  nbin, xmin, xmax2);
  TH1D *wpt2xxupara1 = new TH1D("wpt2xxupara1", "wpt2xxupara1",  nbin, xmin, xmax2);
  TH1D *wset1xxupara1 = new TH1D("wset1xxupara1", "wset1xxupara1",  nbin, xmin, xmax);
  TH1D *wset2xxupara1 = new TH1D("wset2xxupara1", "wset2xxupara1",  nbin, xmin, xmax); 
 
  TH1D *wpt1xxupara2 = new TH1D("wpt1xxupara2", "wpt1xxupara2",  nbin, xmin, xmax2);
  TH1D *wpt2xxupara2 = new TH1D("wpt2xxupara2", "wpt2xxupara2",  nbin, xmin, xmax2);
  TH1D *wset1xxupara2 = new TH1D("wset1xxupara2", "wset1xxupara2",  nbin, xmin, xmax);
  TH1D *wset2xxupara2 = new TH1D("wset2xxupara2", "wset2xxupara2",  nbin, xmin, xmax);


 TH1D *wpt1xxdeteta1 = new TH1D("wpt1xxdeteta1", "wpt1xxdeteta1",  nbin, xmin, xmax2);
  TH1D *wpt2xxdeteta1 = new TH1D("wpt2xxdeteta1", "wpt2xxdeteta1",  nbin, xmin, xmax2);
  TH1D *wset1xxdeteta1 = new TH1D("wset1xxdeteta1", "wset1xxdeteta1",  nbin, xmin, xmax);
  TH1D *wset2xxdeteta1 = new TH1D("wset2xxdeteta1", "wset2xxdeteta1",  nbin, xmin, xmax); 
 
  TH1D *wpt1xxdeteta2 = new TH1D("wpt1xxdeteta2", "wpt1xxdeteta2",  nbin, xmin, xmax2);
  TH1D *wpt2xxdeteta2 = new TH1D("wpt2xxdeteta2", "wpt2xxdeteta2",  nbin, xmin, xmax2);
  TH1D *wset1xxdeteta2 = new TH1D("wset1xxdeteta2", "wset1xxdeteta2",  nbin, xmin, xmax);
  TH1D *wset2xxdeteta2 = new TH1D("wset2xxdeteta2", "wset2xxdeteta2",  nbin, xmin, xmax);

  TH1D *wpt1xxdeteta3 = new TH1D("wpt1xxdeteta3", "wpt1xxdeteta3",  nbin, xmin, xmax2);
  TH1D *wpt2xxdeteta3 = new TH1D("wpt2xxdeteta3", "wpt2xxdeteta3",  nbin, xmin, xmax2);
  TH1D *wset1xxdeteta3 = new TH1D("wset1xxdeteta3", "wset1xxdeteta3",  nbin, xmin, xmax);
  TH1D *wset2xxdeteta3 = new TH1D("wset2xxdeteta3", "wset2xxdeteta3",  nbin, xmin, xmax);

  TH1D *wpt1xxdeteta4 = new TH1D("wpt1xxdeteta4", "wpt1xxdeteta4",  nbin, xmin, xmax2);
  TH1D *wpt2xxdeteta4 = new TH1D("wpt2xxdeteta4", "wpt2xxdeteta4",  nbin, xmin, xmax2);
  TH1D *wset1xxdeteta4 = new TH1D("wset1xxdeteta4", "wset1xxdeteta4",  nbin, xmin, xmax);
  TH1D *wset2xxdeteta4 = new TH1D("wset2xxdeteta4", "wset2xxdeteta4",  nbin, xmin, xmax);

  TH1D *wpt1xxdeteta5 = new TH1D("wpt1xxdeteta5", "wpt1xxdeteta5",  nbin, xmin, xmax2);
  TH1D *wpt2xxdeteta5 = new TH1D("wpt2xxdeteta5", "wpt2xxdeteta5",  nbin, xmin, xmax2);
  TH1D *wset1xxdeteta5 = new TH1D("wset1xxdeteta5", "wset1xxdeteta5",  nbin, xmin, xmax);
  TH1D *wset2xxdeteta5 = new TH1D("wset2xxdeteta5", "wset2xxdeteta5",  nbin, xmin, xmax);

 TH1D *wpt1xxpt1 = new TH1D("wpt1xxpt1", "wpt1xxpt1",  nbin, xmin, xmax2);
  TH1D *wpt2xxpt1 = new TH1D("wpt2xxpt1", "wpt2xxpt1",  nbin, xmin, xmax2);
  TH1D *wset1xxpt1 = new TH1D("wset1xxpt1", "wset1xxpt1",  nbin, xmin, xmax);
  TH1D *wset2xxpt1 = new TH1D("wset2xxpt1", "wset2xxpt1",  nbin, xmin, xmax); 
 
  TH1D *wpt1xxpt2 = new TH1D("wpt1xxpt2", "wpt1xxpt2",  nbin, xmin, xmax2);
  TH1D *wpt2xxpt2 = new TH1D("wpt2xxpt2", "wpt2xxpt2",  nbin, xmin, xmax2);
  TH1D *wset1xxpt2 = new TH1D("wset1xxpt2", "wset1xxpt2",  nbin, xmin, xmax);
  TH1D *wset2xxpt2 = new TH1D("wset2xxpt2", "wset2xxpt2",  nbin, xmin, xmax);

  TH1D *wpt1xxpt3 = new TH1D("wpt1xxpt3", "wpt1xxpt3",  nbin, xmin, xmax2);
  TH1D *wpt2xxpt3 = new TH1D("wpt2xxpt3", "wpt2xxpt3",  nbin, xmin, xmax2);
  TH1D *wset1xxpt3 = new TH1D("wset1xxpt3", "wset1xxpt3",  nbin, xmin, xmax);
  TH1D *wset2xxpt3 = new TH1D("wset2xxpt3", "wset2xxpt3",  nbin, xmin, xmax);

  TH1D *wpt1xxpt4 = new TH1D("wpt1xxpt4", "wpt1xxpt4",  nbin, xmin, xmax2);
  TH1D *wpt2xxpt4 = new TH1D("wpt2xxpt4", "wpt2xxpt4",  nbin, xmin, xmax2);
  TH1D *wset1xxpt4 = new TH1D("wset1xxpt4", "wset1xxpt4",  nbin, xmin, xmax);
  TH1D *wset2xxpt4 = new TH1D("wset2xxpt4", "wset2xxpt4",  nbin, xmin, xmax);

  TH1D *wpt1xxpt5 = new TH1D("wpt1xxpt5", "wpt1xxpt5",  nbin, xmin, xmax2);
  TH1D *wpt2xxpt5 = new TH1D("wpt2xxpt5", "wpt2xxpt5",  nbin, xmin, xmax2);
  TH1D *wset1xxpt5 = new TH1D("wset1xxpt5", "wset1xxpt5",  nbin, xmin, xmax);
  TH1D *wset2xxpt5 = new TH1D("wset2xxpt5", "wset2xxpt5",  nbin, xmin, xmax);

  TH1D *wpt1xxpt6 = new TH1D("wpt1xxpt6", "wpt1xxpt6",  nbin, xmin, xmax2);
  TH1D *wpt2xxpt6 = new TH1D("wpt2xxpt6", "wpt2xxpt6",  nbin, xmin, xmax2);
  TH1D *wset1xxpt6 = new TH1D("wset1xxpt6", "wset1xxpt6",  nbin, xmin, xmax);
  TH1D *wset2xxpt6 = new TH1D("wset2xxpt6", "wset2xxpt6",  nbin, xmin, xmax);

  //-----------------------------------------------------------------------------

  xmin = 0;
  xmax = 7;
  nbin = 20;
  TH1D *wsetpt1xx = new TH1D("wsetpt1xx", "wsetpt1xx",  nbin, xmin, xmax);
  TH1D *wsetpt2xx = new TH1D("wsetpt2xx", "wsetpt2xx",  nbin, xmin, xmax);

  TH1D *wsetptcafet = new TH1D("wsetptcafet", "wsetptcafet",  nbin, xmin, xmax);
  TH1D *wsetptcafer = new TH1D("wsetptcafer", "wsetptcafer",  nbin, xmin, xmax);
  TH1D *wsetptpmcst = new TH1D("wsetpt2pmcst", "wsetpt2pmcst",  nbin, xmin, xmax);
  TH1D *wsetptpmcsr = new TH1D("wsetpt2pmcsr", "wsetpt2pmcsr",  nbin, xmin, xmax);


  TH1D *t = new TH1D("top", "top",  nbin, xmin, xmax);
  TH1D *tcut = new TH1D("topcut", "topcut",  nbin, xmin, xmax);

  TH1D *wsetpt1xxlumi1 = new TH1D("wsetpt1xxlumi1", "wsetpt1xxlumi1",  nbin, xmin, xmax);
  TH1D *wsetpt2xxlumi1 = new TH1D("wsetpt2xxlumi1", "wsetpt2xxlumi1",  nbin, xmin, xmax);

  TH1D *wsetpt1xxlumi2 = new TH1D("wsetpt1xxlumi2", "wsetpt1xxlumi2",  nbin, xmin, xmax);
  TH1D *wsetpt2xxlumi2 = new TH1D("wsetpt2xxlumi2", "wsetpt2xxlumi2",  nbin, xmin, xmax);

  TH1D *wsetpt1xxlumi3 = new TH1D("wsetpt1xxlumi3", "wsetpt1xxlumi3",  nbin, xmin, xmax);
  TH1D *wsetpt2xxlumi3 = new TH1D("wsetpt2xxlumi3", "wsetpt2xxlumi3",  nbin, xmin, xmax);

  TH1D *wsetpt1xxlumi4 = new TH1D("wsetpt1xxlumi4", "wsetpt1xxlumi4",  nbin, xmin, xmax);
  TH1D *wsetpt2xxlumi4 = new TH1D("wsetpt2xxlumi4", "wsetpt2xxlumi4",  nbin, xmin, xmax);


  TH1D *wsetpt1xxupara1 = new TH1D("wsetpt1xxupara1", "wsetpt1xxupara1",  nbin, xmin, xmax);
  TH1D *wsetpt2xxupara1 = new TH1D("wsetpt2xxupara1", "wsetpt2xxupara1",  nbin, xmin, xmax);

  TH1D *wsetpt1xxupara2 = new TH1D("wsetpt1xxupara2", "wsetpt1xxupara2",  nbin, xmin, xmax);
  TH1D *wsetpt2xxupara2 = new TH1D("wsetpt2xxupara2", "wsetpt2xxupara2",  nbin, xmin, xmax);

  TH1D *wsetpt1xxdeteta1 = new TH1D("wsetpt1xxdeteta1", "wsetpt1xxdeteta1",  nbin, xmin, xmax);
  TH1D *wsetpt2xxdeteta1 = new TH1D("wsetpt2xxdeteta1", "wsetpt2xxdeteta1",  nbin, xmin, xmax);

  TH1D *wsetpt1xxdeteta2 = new TH1D("wsetpt1xxdeteta2", "wsetpt1xxdeteta2",  nbin, xmin, xmax);
  TH1D *wsetpt2xxdeteta2 = new TH1D("wsetpt2xxdeteta2", "wsetpt2xxdeteta2",  nbin, xmin, xmax);

  TH1D *wsetpt1xxdeteta3 = new TH1D("wsetpt1xxdeteta3", "wsetpt1xxdeteta3",  nbin, xmin, xmax);
  TH1D *wsetpt2xxdeteta3 = new TH1D("wsetpt2xxdeteta3", "wsetpt2xxdeteta3",  nbin, xmin, xmax);

  TH1D *wsetpt1xxdeteta4 = new TH1D("wsetpt1xxdeteta4", "wsetpt1xxdeteta4",  nbin, xmin, xmax);
  TH1D *wsetpt2xxdeteta4 = new TH1D("wsetpt2xxdeteta4", "wsetpt2xxdeteta4",  nbin, xmin, xmax);

  TH1D *wsetpt1xxdeteta5 = new TH1D("wsetpt1xxdeteta5", "wsetpt1xxdeteta5",  nbin, xmin, xmax);
  TH1D *wsetpt2xxdeteta5 = new TH1D("wsetpt2xxdeteta5", "wsetpt2xxdeteta5",  nbin, xmin, xmax);

  TH1D *wsetpt1xxpt1 = new TH1D("wsetpt1xxpt1", "wsetpt1xxpt1",  nbin, xmin, xmax);
  TH1D *wsetpt2xxpt1 = new TH1D("wsetpt2xxpt1", "wsetpt2xxpt1",  nbin, xmin, xmax);

  TH1D *wsetpt1xxpt2 = new TH1D("wsetpt1xxpt2", "wsetpt1xxpt2",  nbin, xmin, xmax);
  TH1D *wsetpt2xxpt2 = new TH1D("wsetpt2xxpt2", "wsetpt2xxpt2",  nbin, xmin, xmax);

  TH1D *wsetpt1xxpt3 = new TH1D("wsetpt1xxpt3", "wsetpt1xxpt3",  nbin, xmin, xmax);
  TH1D *wsetpt2xxpt3 = new TH1D("wsetpt2xxpt3", "wsetpt2xxpt3",  nbin, xmin, xmax);

  TH1D *wsetpt1xxpt4 = new TH1D("wsetpt1xxpt4", "wsetpt1xxpt4",  nbin, xmin, xmax);
  TH1D *wsetpt2xxpt4 = new TH1D("wsetpt2xxpt4", "wsetpt2xxpt4",  nbin, xmin, xmax);

  TH1D *wsetpt1xxpt5 = new TH1D("wsetpt1xxpt5", "wsetpt1xxpt5",  nbin, xmin, xmax);
  TH1D *wsetpt2xxpt5 = new TH1D("wsetpt2xxpt5", "wsetpt2xxpt5",  nbin, xmin, xmax);

  TH1D *wsetpt1xxpt6 = new TH1D("wsetpt1xxpt6", "wsetpt1xxpt6",  nbin, xmin, xmax);
  TH1D *wsetpt2xxpt6 = new TH1D("wsetpt2xxpt6", "wsetpt2xxpt6",  nbin, xmin, xmax);

  //-----------------------------------------------------------------------------
 TH1D *wlumi1 = new TH1D("wlumi1", "wlumi1",  nbin, xmin, xmax);
 TH1D *wlumi2 = new TH1D("wlumi2", "wlumi2",  nbin, xmin, xmax);
 TH1D *wlumi3 = new TH1D("wlumi3", "wlumi3",  nbin, xmin, xmax);
 TH1D *wlumi4 = new TH1D("wlumi4", "wlumi4",  nbin, xmin, xmax);
  
 TH1D *wlumi1cut = new TH1D("wlumi1cut", "wlumi1cut",  nbin, xmin, xmax);
 TH1D *wlumi2cut = new TH1D("wlumi2cut", "wlumi2cut",  nbin, xmin, xmax);
 TH1D *wlumi3cut = new TH1D("wlumi3cut", "wlumi3cut",  nbin, xmin, xmax);
 TH1D *wlumi4cut = new TH1D("wlumi4cut", "wlumi4cut",  nbin, xmin, xmax);

 TH1D *wupara1 = new TH1D("wupara1", "wupara1",  nbin, xmin, xmax);
 TH1D *wupara2 = new TH1D("wupara2", "wupara2",  nbin, xmin, xmax);
 TH1D *wupara1cut = new TH1D("wupara1cut", "wupara1cut",  nbin, xmin, xmax);
 TH1D *wupara2cut = new TH1D("wupara2cut", "wupara2cut",  nbin, xmin, xmax);

 TH1D *wdeteta1 = new TH1D("wdeteta1", "wdeteta1",  nbin, xmin, xmax);
 TH1D *wdeteta2 = new TH1D("wdeteta2", "wdeteta2",  nbin, xmin, xmax);
 TH1D *wdeteta3 = new TH1D("wdeteta3", "wdeteta3",  nbin, xmin, xmax);
 TH1D *wdeteta4 = new TH1D("wdeteta4", "wdeteta4",  nbin, xmin, xmax);
 TH1D *wdeteta5 = new TH1D("wdeteta5", "wdeteta5",  nbin, xmin, xmax);
  
 TH1D *wdeteta1cut = new TH1D("wdeteta1cut", "wdeteta1cut",  nbin, xmin, xmax);
 TH1D *wdeteta2cut = new TH1D("wdeteta2cut", "wdeteta2cut",  nbin, xmin, xmax);
 TH1D *wdeteta3cut = new TH1D("wdeteta3cut", "wdeteta3cut",  nbin, xmin, xmax);
 TH1D *wdeteta4cut = new TH1D("wdeteta4cut", "wdeteta4cut",  nbin, xmin, xmax);
 TH1D *wdeteta5cut = new TH1D("wdeteta5cut", "wdeteta5cut",  nbin, xmin, xmax);

 TH1D *wpt1 = new TH1D("wpt1", "wpt1",  nbin, xmin, xmax);
 TH1D *wpt2 = new TH1D("wpt2", "wpt2",  nbin, xmin, xmax);
 TH1D *wpt3 = new TH1D("wpt3", "wpt3",  nbin, xmin, xmax);
 TH1D *wpt4 = new TH1D("wpt4", "wpt4",  nbin, xmin, xmax);
 TH1D *wpt5 = new TH1D("wpt5", "wpt5",  nbin, xmin, xmax);
 TH1D *wpt6 = new TH1D("wpt6", "wpt6",  nbin, xmin, xmax);
  
 TH1D *wpt1cut = new TH1D("wpt1cut", "wpt1cut",  nbin, xmin, xmax);
 TH1D *wpt2cut = new TH1D("wpt2cut", "wpt2cut",  nbin, xmin, xmax);
 TH1D *wpt3cut = new TH1D("wpt3cut", "wpt3cut",  nbin, xmin, xmax);
 TH1D *wpt4cut = new TH1D("wpt4cut", "wpt4cut",  nbin, xmin, xmax);
 TH1D *wpt5cut = new TH1D("wpt5cut", "wpt5cut",  nbin, xmin, xmax);
 TH1D *wpt6cut = new TH1D("wpt6cut", "wpt6cut",  nbin, xmin, xmax);



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
 
 //in Cafe, set study uses fsr merged cone objects (even though called raw there).  So we use eptftrue
 for (int i = 0; i < nentries; i++){
   tree1->GetEntry(i);
   //if(tree1->GetLeaf("ccgen")->GetValue(0) == 1  && tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25){
     //t->Fill(tree1->GetLeaf(var)->GetValue(0));//setZBgen")->GetValue(0));
   
   // if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("cut2")->GetValue(0) == 1 &&tree1->GetLeaf("passesEMIDEff")->GetValue(0) == 1 && tree1->GetLeaf("passesPreselEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrkEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrigEff")->GetValue(0) == 1 ){// && tree1->GetLeaf("passesUParaCorrection")->GetValue(0) == 1){// && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){

   if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("met")->GetValue(0) > 25 && tree1->GetLeaf("wut")->GetValue(0) < 15  && tree1->GetLeaf("mt")->GetValue(0) < 200 && tree1->GetLeaf("mt")->GetValue(0) > 50 ){
     // if(tree1->GetLeaf("passesAllEffs")->GetValue(0) == 1){//includes AddOnEff, no SET EFF

       if(tree1->GetLeaf("passesEMIDEff")->GetValue(0) == 1 && tree1->GetLeaf("passesPreselEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrkEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrigEff")->GetValue(0) == 1 ){// && tree1->GetLeaf("passesUParaCorrection")->GetValue(0) == 1){// && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){

       wpt1xx->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
       wset1xx->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
       wsetpt1xx->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));


       //    if(tree1->GetLeaf("upara")->GetValue(0)  < 0 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.2 && 
       // if(tree1->GetLeaf("pt")->GetValue(0)  >= 45 && tree1->GetLeaf("pt")->GetValue(0)  < 50 && tree1->GetLeaf("upara")->GetValue(0)  > 0){
       if(tree1->GetLeaf("lumi")->GetValue(0)  < 2){
	 wpt1xxlumi1->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxlumi1->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxlumi1->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
       }else if(tree1->GetLeaf("lumi")->GetValue(0)  >= 2 && tree1->GetLeaf("lumi")->GetValue(0)  < 4){
	 wpt1xxlumi2->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxlumi2->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxlumi2->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
	 
       }else if(tree1->GetLeaf("lumi")->GetValue(0)  >= 4 && tree1->GetLeaf("lumi")->GetValue(0)  < 6){
	 wpt1xxlumi3->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxlumi3->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxlumi3->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
	 
       } else if(tree1->GetLeaf("lumi")->GetValue(0)  >= 6){
	 wpt1xxlumi4->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxlumi4->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxlumi4->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
     }

       //   }
       // if(tree1->GetLeaf("upara")->GetValue(0)  < 0){//missing cafe upara
	 wpt1xxupara1->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxupara1->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxupara1->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
	 // }else {
	 wpt1xxupara2->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxupara2->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxupara2->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
	 
	 //}

	 if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.2){
	 wpt1xxdeteta1->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxdeteta1->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxdeteta1->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
 
      }else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.2 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.4){
	 wpt1xxdeteta2->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxdeteta2->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxdeteta2->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
	 
       }else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.4 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.6){
	 wpt1xxdeteta3->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxdeteta3->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxdeteta3->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
       
       }else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.6 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.8){
	 wpt1xxdeteta4->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxdeteta4->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxdeteta4->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));

       } else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.8){
	 wpt1xxdeteta5->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxdeteta5->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxdeteta5->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
     }


      if(tree1->GetLeaf("pt")->GetValue(0)  < 30){
	 wpt1xxpt1->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxpt1->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxpt1->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
       }else if(tree1->GetLeaf("pt")->GetValue(0)  >= 30 && tree1->GetLeaf("pt")->GetValue(0)  < 35){
	 wpt1xxpt2->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxpt2->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxpt2->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
	 
       }else if(tree1->GetLeaf("pt")->GetValue(0)  >= 35 && tree1->GetLeaf("pt")->GetValue(0)  < 40){
	 wpt1xxpt3->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxpt3->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxpt3->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
       
       }else if(tree1->GetLeaf("pt")->GetValue(0)  >= 40 && tree1->GetLeaf("pt")->GetValue(0)  < 45){
	 wpt1xxpt4->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxpt4->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxpt4->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
  
      }else if(tree1->GetLeaf("pt")->GetValue(0)  >= 45 && tree1->GetLeaf("pt")->GetValue(0)  < 50){
	 wpt1xxpt5->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxpt5->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxpt5->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));

       } else if(tree1->GetLeaf("pt")->GetValue(0)  >= 50){
	 wpt1xxpt6->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0));//setZBgen")->GetValue(0));
	 wset1xxpt6->Fill(tree1->GetLeaf("setZBgen")->GetValue(0));
	 wsetpt1xxpt6->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0));
     }

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

   if(passCC[0] == 1 && (ept[0] > 25 ) && tree2->GetLeaf("passCutUt")->GetValue(0) == 1 && tree2->GetLeaf("met")->GetValue(0) > 25 && tree2->GetLeaf("passCutWMt")->GetValue(0) == 1 ){
 if(passEmf[0] == 1 && passIso[0] == 1  && passTrkPhiFid[0] == 1  && passCalEtaFid[0] == 1 &&  passTkMatch[0] == 1 && passHMx[0] == 1 ){

       wpt2xx->Fill(eptftrue[0]);
       wset2xx->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
       wpt2xxr->Fill(ept[0]);
       wset2xxr->Fill(tree2->GetLeaf("set")->GetValue(0));//setZB
       wsetpt2xx->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
   
       wsetptcafet->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       wsetptcafer->Fill(tree2->GetLeaf("set")->GetValue(0)/ept[0]);


       //  if(tree2->GetLeaf("upara")->GetValue(0)  < 0 && fabs(edeteta[0])  < 0.2 && 
       // if(ept[0]  >= 45 && ept[0]  < 50 && tree2->GetLeaf("upara")->GetValue(0)  > 0){
       if(tree2->GetLeaf("lumi")->GetValue(0)  < 2){
	 wpt2xxlumi1->Fill(eptftrue[0]);
	 wset2xxlumi1->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxlumi1->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }else if(tree2->GetLeaf("lumi")->GetValue(0)  >= 2 && tree2->GetLeaf("lumi")->GetValue(0)  < 4){
	 wpt2xxlumi2->Fill(eptftrue[0]);
	 wset2xxlumi2->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxlumi2->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }else if(tree2->GetLeaf("lumi")->GetValue(0)  >= 4 && tree2->GetLeaf("lumi")->GetValue(0)  < 6){
	 wpt2xxlumi3->Fill(eptftrue[0]);
	 wset2xxlumi3->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxlumi3->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       } else if(tree2->GetLeaf("lumi")->GetValue(0)  >= 6){
	 wpt2xxlumi4->Fill(eptftrue[0]);
	 wset2xxlumi4->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxlumi4->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }
       //  }

       //  if(tree2->GetLeaf("upara")->GetValue(0)  < 0){//missing cafe upara
	 wpt2xxupara1->Fill(eptftrue[0]);
	 wset2xxupara1->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxupara1->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
	 // }else {
	 wpt2xxupara2->Fill(eptftrue[0]);
	 wset2xxupara2->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxupara2->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
	 // }

       if(fabs(edeteta[0])  < 0.2){
	 wpt2xxdeteta1->Fill(eptftrue[0]);
	 wset2xxdeteta1->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxdeteta1->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }else if(fabs(edeteta[0])  >= 0.2 && fabs(edeteta[0])  < 0.4){
	 wpt2xxdeteta2->Fill(eptftrue[0]);
	 wset2xxdeteta2->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxdeteta2->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }else if(fabs(edeteta[0])  >= 0.4 && fabs(edeteta[0])  < 0.6){
	 wpt2xxdeteta3->Fill(eptftrue[0]);
	 wset2xxdeteta3->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxdeteta3->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
      }else if(fabs(edeteta[0])  >= 0.6 && fabs(edeteta[0])  < 0.8){
	 wpt2xxdeteta4->Fill(eptftrue[0]);
	 wset2xxdeteta4->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxdeteta4->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       } else if(fabs(edeteta[0])  >= 0.8){
	 wpt2xxdeteta5->Fill(eptftrue[0]);
	 wset2xxdeteta5->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxdeteta5->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }

       if(ept[0]  < 30){
	 wpt2xxpt1->Fill(eptftrue[0]);
	 wset2xxpt1->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxpt1->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }else if(ept[0]  >= 30 && ept[0]  < 35){
	 wpt2xxpt2->Fill(eptftrue[0]);
	 wset2xxpt2->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxpt2->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }else if(ept[0]  >= 35 && ept[0]  < 40){
	 wpt2xxpt3->Fill(eptftrue[0]);
	 wset2xxpt3->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxpt3->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
      }else if(ept[0]  >= 40 && ept[0]  < 45){
	 wpt2xxpt4->Fill(eptftrue[0]);
	 wset2xxpt4->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxpt4->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }else if(ept[0]  >= 45 && ept[0]  < 50){
	 wpt2xxpt5->Fill(eptftrue[0]);
	 wset2xxpt5->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxpt5->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       } else if(ept[0]  >= 50){
	 wpt2xxpt6->Fill(eptftrue[0]);
	 wset2xxpt6->Fill(tree2->GetLeaf("setZB")->GetValue(0));//setZB
	 wsetpt2xxpt6->Fill(tree2->GetLeaf("setZB")->GetValue(0)/eptftrue[0]);
       }


     }
  }
 }

 cout<<"SCALE "<<(double) wsetpt2xx->Integral()<<"  "<<wsetpt1xx->Integral()<<"  "<<(double) wsetpt2xx->Integral()/wsetpt1xx->Integral()<<endl;
 
 wsetpt1xx->Scale((double) wsetpt2xx->Integral()/wsetpt1xx->Integral());
  wsetpt2xx->Divide(wsetpt2xx, wsetpt1xx,1.0,1.0,"B");
 wsetpt2xx->Draw("pe");

 wsetpt1xxlumi1->Scale(wsetpt2xxlumi1->Integral()/wsetpt1xxlumi1->Integral());
 wsetpt2xxlumi1->Divide(wsetpt2xxlumi1, wsetpt1xxlumi1,1.0,1.0,"B");

 wsetpt1xxlumi2->Scale(wsetpt2xxlumi2->Integral()/wsetpt1xxlumi2->Integral());
 wsetpt2xxlumi2->Divide(wsetpt2xxlumi2, wsetpt1xxlumi2,1.0,1.0,"B");

 wsetpt1xxlumi3->Scale(wsetpt2xxlumi3->Integral()/wsetpt1xxlumi3->Integral());
 wsetpt2xxlumi3->Divide(wsetpt2xxlumi3, wsetpt1xxlumi3,1.0,1.0,"B");

 wsetpt1xxlumi4->Scale(wsetpt2xxlumi4->Integral()/wsetpt1xxlumi4->Integral());
 wsetpt2xxlumi4->Divide(wsetpt2xxlumi4, wsetpt1xxlumi4,1.0,1.0,"B");

wsetpt2xxlumi1->SetLineColor(kOrange);
wsetpt2xxlumi2->SetLineColor(kRed);
wsetpt2xxlumi3->SetLineColor(kGreen);
wsetpt2xxlumi4->SetLineColor(kBlue);

//wsetpt2xxlumi1->Draw("pe same");
//wsetpt2xxlumi2->Draw("pe same");
//wsetpt2xxlumi3->Draw("pe same");
//wsetpt2xxlumi4->Draw("pe same");

 c1->Update();
 c1->Print("PlotSETPTWeight_"+var+".eps");
 c1->Print("PlotSETPTWeight_"+var+".gif");

wsetpt1xxupara1->Scale(wsetpt2xxupara1->Integral()/wsetpt1xxupara1->Integral());
 wsetpt2xxupara1->Divide(wsetpt2xxupara1, wsetpt1xxupara1,1.0,1.0,"B");

 wsetpt1xxupara2->Scale(wsetpt2xxupara2->Integral()/wsetpt1xxupara2->Integral());
 wsetpt2xxupara2->Divide(wsetpt2xxupara2, wsetpt1xxupara2,1.0,1.0,"B");

wsetpt1xxdeteta1->Scale(wsetpt2xxdeteta1->Integral()/wsetpt1xxdeteta1->Integral());
 wsetpt2xxdeteta1->Divide(wsetpt2xxdeteta1, wsetpt1xxdeteta1,1.0,1.0,"B");

 wsetpt1xxdeteta2->Scale(wsetpt2xxdeteta2->Integral()/wsetpt1xxdeteta2->Integral());
 wsetpt2xxdeteta2->Divide(wsetpt2xxdeteta2, wsetpt1xxdeteta2,1.0,1.0,"B");

 wsetpt1xxdeteta3->Scale(wsetpt2xxdeteta3->Integral()/wsetpt1xxdeteta3->Integral());
 wsetpt2xxdeteta3->Divide(wsetpt2xxdeteta3, wsetpt1xxdeteta3,1.0,1.0,"B");

 wsetpt1xxdeteta4->Scale(wsetpt2xxdeteta4->Integral()/wsetpt1xxdeteta4->Integral());
 wsetpt2xxdeteta4->Divide(wsetpt2xxdeteta4, wsetpt1xxdeteta4,1.0,1.0,"B");

 wsetpt1xxdeteta5->Scale(wsetpt2xxdeteta5->Integral()/wsetpt1xxdeteta5->Integral());
 wsetpt2xxdeteta5->Divide(wsetpt2xxdeteta5, wsetpt1xxdeteta5,1.0,1.0,"B");

wsetpt1xxpt1->Scale(wsetpt2xxpt1->Integral()/wsetpt1xxpt1->Integral());
 wsetpt2xxpt1->Divide(wsetpt2xxpt1, wsetpt1xxpt1,1.0,1.0,"B");

 wsetpt1xxpt2->Scale(wsetpt2xxpt2->Integral()/wsetpt1xxpt2->Integral());
 wsetpt2xxpt2->Divide(wsetpt2xxpt2, wsetpt1xxpt2,1.0,1.0,"B");

 wsetpt1xxpt3->Scale(wsetpt2xxpt3->Integral()/wsetpt1xxpt3->Integral());
 wsetpt2xxpt3->Divide(wsetpt2xxpt3, wsetpt1xxpt3,1.0,1.0,"B");

 wsetpt1xxpt4->Scale(wsetpt2xxpt4->Integral()/wsetpt1xxpt4->Integral());
 wsetpt2xxpt4->Divide(wsetpt2xxpt4, wsetpt1xxpt4,1.0,1.0,"B");

 wsetpt1xxpt5->Scale(wsetpt2xxpt5->Integral()/wsetpt1xxpt5->Integral());
 wsetpt2xxpt5->Divide(wsetpt2xxpt5, wsetpt1xxpt5,1.0,1.0,"B");

 wsetpt1xxpt6->Scale(wsetpt2xxpt6->Integral()/wsetpt1xxpt6->Integral());
 wsetpt2xxpt6->Divide(wsetpt2xxpt6, wsetpt1xxpt6,1.0,1.0,"B");


 //now, redraw the pt/set distribution but reweighted via the 2d histogram
 
 
 for (int i = 0; i < nentries; i++){
   tree1->GetEntry(i);
   // if(tree1->GetLeaf("ccgen")->GetValue(0) == 1  && tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25){
   if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("met")->GetValue(0) > 25 && tree1->GetLeaf("wut")->GetValue(0) < 15  && tree1->GetLeaf("mt")->GetValue(0) < 200 && tree1->GetLeaf("mt")->GetValue(0) > 50 ){
     //     t->Fill(tree1->GetLeaf("pt")->GetValue(0)/tree1->GetLeaf("set")->GetValue(0));//setZBgen")->GetValue(0));
     
     // if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("cut2")->GetValue(0) == 1 &&tree1->GetLeaf("passesEMIDEff")->GetValue(0) == 1 && tree1->GetLeaf("passesPreselEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrkEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrigEff")->GetValue(0) == 1  ){//&& tree1->GetLeaf("passesUParaCorrection")->GetValue(0) == 1 && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){

     //     if(tree1->GetLeaf("passesAllEffs")->GetValue(0) == 1 ){//includes AddOnEff, no SET EFF
if(tree1->GetLeaf("passesEMIDEff")->GetValue(0) == 1 && tree1->GetLeaf("passesPreselEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrkEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrigEff")->GetValue(0) == 1 ){// && tree1->GetLeaf("passesUParaCorrection")->GetValue(0) == 1){// && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){

   t->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));//setZBgen")->GetValue(0)); //without weight
    tcut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xx->GetBinContent(wsetpt2xx->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );//setZBgen")->GetValue(0)); //with weight
   

  // t->Fill(tree1->GetLeaf("set")->GetValue(0)/20);//setZBgen")->GetValue(0)); //without weight
  // tcut->Fill(tree1->GetLeaf("set")->GetValue(0)/20, wsetpt2xx->GetBinContent(wsetpt2xx->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );//setZBgen")->GetValue(0)); //with weight
   
       
       wpttestt->Fill(tree1->GetLeaf("wfsr_ptgen")->GetValue(0), wsetpt2xx->GetBinContent(wsetpt2xx->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
       wpttestr->Fill(tree1->GetLeaf("pt")->GetValue(0), wsetpt2xx->GetBinContent(wsetpt2xx->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
       wsettestt->Fill(tree1->GetLeaf("setZBgen")->GetValue(0), wsetpt2xx->GetBinContent(wsetpt2xx->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
       wsettestr->Fill(tree1->GetLeaf("set")->GetValue(0), wsetpt2xx->GetBinContent(wsetpt2xx->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );

       // wsetptpmcst->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0), wsetpt2xx->GetBinContent(wsetpt2xx->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
       //  wsetptpmcsr->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xx->GetBinContent(wsetpt2xx->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
 
       // if(tree1->GetLeaf("upara")->GetValue(0)  < 0 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.2 && 
       // if(tree1->GetLeaf("pt")->GetValue(0)  >= 45 && tree1->GetLeaf("pt")->GetValue(0)  < 50 && tree1->GetLeaf("upara")->GetValue(0)  > 0){
	 if(tree1->GetLeaf("lumi")->GetValue(0)  < 2) wlumi1->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(tree1->GetLeaf("lumi")->GetValue(0)  >= 2 && tree1->GetLeaf("lumi")->GetValue(0)  < 4) wlumi2->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(tree1->GetLeaf("lumi")->GetValue(0)  >= 4 && tree1->GetLeaf("lumi")->GetValue(0)  < 6) wlumi3->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(tree1->GetLeaf("lumi")->GetValue(0)  >= 6) wlumi4->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));

	 if(tree1->GetLeaf("lumi")->GetValue(0)  < 2) wlumi1cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxlumi1->GetBinContent(wsetpt2xxlumi1->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(tree1->GetLeaf("lumi")->GetValue(0)  >= 2 && tree1->GetLeaf("lumi")->GetValue(0)  < 4) wlumi2cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxlumi2->GetBinContent(wsetpt2xxlumi2->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(tree1->GetLeaf("lumi")->GetValue(0)  >= 4 && tree1->GetLeaf("lumi")->GetValue(0)  < 6) wlumi3cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxlumi3->GetBinContent(wsetpt2xxlumi3->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(tree1->GetLeaf("lumi")->GetValue(0)  >= 6) wlumi4cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxlumi4->GetBinContent(wsetpt2xxlumi4->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );

	 // }
	 if(tree1->GetLeaf("upara")->GetValue(0)  < 0) wupara1->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else wupara2->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 if(tree1->GetLeaf("upara")->GetValue(0)  < 0) wupara1cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxupara1->GetBinContent(wsetpt2xxupara1->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else wupara2cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxupara2->GetBinContent(wsetpt2xxupara2->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );


	 if(tree1->GetLeaf("pt")->GetValue(0)  < 30) wpt1->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(tree1->GetLeaf("pt")->GetValue(0)  >= 30 && tree1->GetLeaf("pt")->GetValue(0)  < 35) wpt2->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(tree1->GetLeaf("pt")->GetValue(0)  >= 35 && tree1->GetLeaf("pt")->GetValue(0)  < 40) wpt3->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(tree1->GetLeaf("pt")->GetValue(0)  >= 40 && tree1->GetLeaf("pt")->GetValue(0)  < 45) wpt4->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(tree1->GetLeaf("pt")->GetValue(0)  >= 45 && tree1->GetLeaf("pt")->GetValue(0)  < 50) wpt5->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(tree1->GetLeaf("pt")->GetValue(0)  >= 50) wpt6->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));

	 if(tree1->GetLeaf("pt")->GetValue(0)  < 30) wpt1cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxpt1->GetBinContent(wsetpt2xxpt1->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(tree1->GetLeaf("pt")->GetValue(0)  >= 30 && tree1->GetLeaf("pt")->GetValue(0)  < 35) wpt2cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxpt2->GetBinContent(wsetpt2xxpt2->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(tree1->GetLeaf("pt")->GetValue(0)  >= 35 && tree1->GetLeaf("pt")->GetValue(0)  < 40) wpt3cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxpt3->GetBinContent(wsetpt2xxpt3->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(tree1->GetLeaf("pt")->GetValue(0)  >= 40 && tree1->GetLeaf("pt")->GetValue(0)  < 45) wpt4cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxpt4->GetBinContent(wsetpt2xxpt4->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(tree1->GetLeaf("pt")->GetValue(0)  >= 45 && tree1->GetLeaf("pt")->GetValue(0)  < 50) wpt5cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxpt5->GetBinContent(wsetpt2xxpt5->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(tree1->GetLeaf("pt")->GetValue(0)  >= 50) wpt6cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxpt6->GetBinContent(wsetpt2xxpt6->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );

	 if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.2) wdeteta1->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.2 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.4) wdeteta2->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.4 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.6) wdeteta3->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.6 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.8) wdeteta4->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));
	 else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.8) wdeteta5->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0));

	 if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.2) wdeteta1cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxdeteta1->GetBinContent(wsetpt2xxdeteta1->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.2 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.4) wdeteta2cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxdeteta2->GetBinContent(wsetpt2xxdeteta2->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.4 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.6) wdeteta3cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxdeteta3->GetBinContent(wsetpt2xxdeteta3->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.6 && fabs(tree1->GetLeaf("deteta")->GetValue(0))  < 0.8) wdeteta4cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxdeteta4->GetBinContent(wsetpt2xxdeteta4->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );
	 else if(fabs(tree1->GetLeaf("deteta")->GetValue(0))  >= 0.8) wdeteta5cut->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), wsetpt2xxdeteta5->GetBinContent(wsetpt2xxdeteta5->GetXaxis()->FindBin(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0))) );



     }
   }
 }
 TCanvas *c2 = new TCanvas("c2","c2",800,800);
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
c2->Update();
 c2->Print("PlotSETPTPMCS_"+var+".eps");
 c2->Print("PlotSETPTPMCS_"+var+".gif");

 TCanvas *c3 = new TCanvas("c3","c3",800,800);

t->Divide(tcut, t,1.0,1.0,"B");
 t->SetMaximum(2.0);
 t->SetMinimum(0.0);
  t->SetMarkerSize(1);
  t->Draw("pe");

gPad->Update();
c3->Update();


  //xmin, xmax, numpar  range only used if R option specified in fit
//TF1 *func = new TF1("func",fitf,0,7,3);
 TF1 *func = new TF1("func",fitf,0,7,5);
// TF1 *func = new TF1("func",fitf,0,7,10);
 func->SetLineColor(kRed);
 // -2.729  13.8452  -29.9368  24.1911  0  
 func->SetParameter(0, 1);
  func->SetParameter(1, -0.1);
  func->SetParameter(2, 0.01);
    func->SetParameter(3, -0.001);
   func->SetParameter(4, 0);


 t->Fit("func", "+");
gPad->Update();
c3->Update();
c3->Print("PlotSETPTEffcutnocut_"+var+".eps");
c3->Print("PlotSETPTEffcutnocut_"+var+".gif");

//using the efficiency as a weight now, not the weight from step 1.
 for (int i = 0; i < nentries; i++){
   tree1->GetEntry(i);
   // if(tree1->GetLeaf("ccgen")->GetValue(0) == 1  && tree1->GetLeaf("wfsr_ptgen")->GetValue(0) > 25){
   if(tree1->GetLeaf("cc")->GetValue(0) == 1  && tree1->GetLeaf("pt")->GetValue(0) > 25 && tree1->GetLeaf("met")->GetValue(0) > 25 && tree1->GetLeaf("wut")->GetValue(0) < 15  && tree1->GetLeaf("mt")->GetValue(0) < 200 && tree1->GetLeaf("mt")->GetValue(0) > 50 ){
     //     if(tree1->GetLeaf("passesAllEffs")->GetValue(0) == 1 ){//includes AddOnEff, no SET EFF
if(tree1->GetLeaf("passesEMIDEff")->GetValue(0) == 1 && tree1->GetLeaf("passesPreselEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrkEff")->GetValue(0) == 1 && tree1->GetLeaf("passesTrigEff")->GetValue(0) == 1 ){// && tree1->GetLeaf("passesUParaCorrection")->GetValue(0) == 1){// && tree1->GetLeaf("passesSETEff")->GetValue(0) == 1 ){

       wsetptpmcst->Fill(tree1->GetLeaf("setZBgen")->GetValue(0)/tree1->GetLeaf("wfsr_ptgen")->GetValue(0), t->GetBinContent(t->GetXaxis()->FindBin(tree1->GetLeaf("setZB")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0))) );
       wsetptpmcsr->Fill(tree1->GetLeaf("set")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0), t->GetBinContent(t->GetXaxis()->FindBin(tree1->GetLeaf("setZB")->GetValue(0)/tree1->GetLeaf("pt")->GetValue(0))) );

     }
   }
 }



 TCanvas *c44 = new TCanvas("c44","c44",800,800);
 wsetptpmcst->Scale( wsetptcafet->Integral()/ wsetptpmcst->Integral());
 wsetptpmcst->Draw();
 wsetptcafet->SetMarkerColor(kRed);
 wsetptcafet->SetLineColor(kRed);
 wsetptcafet->Draw("same");
c44->Update();

 c44->Print("PlotSETPTPMCS_TruthVarAfterWeight_"+var+".eps");
 c44->Print("PlotSETPTPMCS_TruthVarAfterWeight_"+var+".gif");

 TCanvas *c55 = new TCanvas("c55","c55",800,800);
 wsetptpmcsr->Scale( wsetptcafer->Integral()/ wsetptpmcsr->Integral());
 wsetptpmcsr->Draw();
 wsetptcafer->SetMarkerColor(kRed);
 wsetptcafer->SetLineColor(kRed);
 wsetptcafer->Draw("same");
c55->Update();

c55->Print("PlotSETPTPMCS_RecoVarAfterWeight_"+var+".eps");
 c55->Print("PlotSETPTPMCS_RecoVarAfterWeight_"+var+".gif");

/**
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
**/
 TCanvas *c8 = new TCanvas("c8","c8",800,800);

wlumi1->SetLineColor(kOrange);
wlumi2->SetLineColor(kRed);
wlumi3->SetLineColor(kGreen);
wlumi4->SetLineColor(kBlue);

 wlumi1->Divide(wlumi1cut, wlumi1,1.0,1.0,"B");
 wlumi1->SetMaximum(2.0);
 wlumi1->SetMinimum(0.0);
 wlumi1->SetMarkerSize(1);

 // TF1 *funclumi1 = new TF1("funclumi1",fitf,0,7,3);
  TF1 *funclumi1 = new TF1("funclumi1",fitf,0,7,5);
 funclumi1->SetLineColor(kOrange);
 funclumi1->SetParameter(0, 1.);
 funclumi1->SetParameter(1, -0.1);
 funclumi1->SetParameter(2, 0.01);
    funclumi1->SetParameter(3, -0.001);
  funclumi1->SetParameter(4, 0);

 wlumi1->Fit("funclumi1", "+");


 wlumi2->Divide(wlumi2cut, wlumi2,1.0,1.0,"B");
 wlumi2->SetMaximum(2.0);
 wlumi2->SetMinimum(0.0);
 wlumi2->SetMarkerSize(1);
 //TF1 *funclumi2 = new TF1("funclumi2",fitf,0,7,3);
  TF1 *funclumi2 = new TF1("funclumi2",fitf,0,7,5);
 funclumi2->SetLineColor(kRed);
 funclumi2->SetParameter(0, 1.0);
 funclumi2->SetParameter(1, -0.1);
 funclumi2->SetParameter(2, 0.01);
  funclumi2->SetParameter(3, -0.001);
 funclumi2->SetParameter(4, 0);

 wlumi2->Fit("funclumi2", "+");
 
 wlumi3->Divide(wlumi3cut, wlumi3,1.0,1.0,"B");
 wlumi3->SetMaximum(2.0);
 wlumi3->SetMinimum(0.0);
 wlumi3->SetMarkerSize(1);
 //TF1 *funclumi3 = new TF1("funclumi3",fitf,0,7,3);
  TF1 *funclumi3 = new TF1("funclumi3",fitf,0,7,5);
 funclumi3->SetLineColor(kGreen);
 funclumi3->SetParameter(0, 1.0);
 funclumi3->SetParameter(1, -0.1);
 funclumi3->SetParameter(2, 0.01);
  funclumi3->SetParameter(3, -0.001);
 funclumi3->SetParameter(4, 0);

 wlumi3->Fit("funclumi3", "+");
 
 wlumi4->Divide(wlumi4cut, wlumi4,1.0,1.0,"B");
 wlumi4->SetMaximum(2.0);
 wlumi4->SetMinimum(0.0);
 wlumi4->SetMarkerSize(1);
 //TF1 *funclumi4 = new TF1("funclumi4",fitf,0,7,3);
  TF1 *funclumi4 = new TF1("funclumi4",fitf,0,7,5);
 funclumi4->SetLineColor(kBlue);
 funclumi4->SetParameter(0, 1.0);
 funclumi4->SetParameter(1, -0.1);
 funclumi4->SetParameter(2, 0.01);
  funclumi4->SetParameter(3, -0.001);
 funclumi4->SetParameter(4, 0);

 wlumi4->Fit("funclumi4", "+");
 
 wlumi1->Draw("pe");
 wlumi2->Draw("pe same");
 wlumi3->Draw("pe same");
 wlumi4->Draw("pe same");

 c8->Update();

c8->Print("PlotSETPTEffcutnocut_lumi_"+var+".eps");
c8->Print("PlotSETPTEffcutnocut_lumi_"+var+".gif");

 /**
 TCanvas *c9 = new TCanvas("c9","c9",800,800);

wupara1->SetLineColor(kRed);
wupara2->SetLineColor(kBlue);

 wupara1->Divide(wupara1cut, wupara1,1.0,1.0,"B");
 wupara1->SetMaximum(2.0);
 wupara1->SetMinimum(0.0);
 wupara1->SetMarkerSize(1);
 wupara1->Draw("pe");

 wupara2->Divide(wupara2cut, wupara2,1.0,1.0,"B");
 wupara2->SetMaximum(2.0);
 wupara2->SetMinimum(0.0);
 wupara2->SetMarkerSize(1);
 wupara2->Draw("pe same");

 c9->Update();

 TCanvas *c10 = new TCanvas("c10","c10",800,800);

wpt1->SetLineColor(kOrange);
wpt2->SetLineColor(kRed);
wpt3->SetLineColor(kGreen);
wpt4->SetLineColor(kAzure);
wpt5->SetLineColor(kBlue);
wpt6->SetLineColor(kBlack);

 wpt1->Divide(wpt1cut, wpt1,1.0,1.0,"B");
 wpt1->SetMaximum(2.0);
 wpt1->SetMinimum(0.0);
 wpt1->SetMarkerSize(1);
 wpt1->Draw("pe");

 wpt2->Divide(wpt2cut, wpt2,1.0,1.0,"B");
 wpt2->SetMaximum(2.0);
 wpt2->SetMinimum(0.0);
 wpt2->SetMarkerSize(1);
 wpt2->Draw("pe same");

 wpt3->Divide(wpt3cut, wpt3,1.0,1.0,"B");
 wpt3->SetMaximum(2.0);
 wpt3->SetMinimum(0.0);
 wpt3->SetMarkerSize(1);
 wpt3->Draw("pe same");

 wpt4->Divide(wpt4cut, wpt4,1.0,1.0,"B");
 wpt4->SetMaximum(2.0);
 wpt4->SetMinimum(0.0);
 wpt4->SetMarkerSize(1);
 wpt4->Draw("pe same");

 wpt5->Divide(wpt5cut, wpt5,1.0,1.0,"B");
 wpt5->SetMaximum(2.0);
 wpt5->SetMinimum(0.0);
 wpt5->SetMarkerSize(1);
 wpt5->Draw("pe same");

 wpt6->Divide(wpt6cut, wpt6,1.0,1.0,"B");
 wpt6->SetMaximum(2.0);
 wpt6->SetMinimum(0.0);
 wpt6->SetMarkerSize(1);
 wpt6->Draw("pe same");



 c10->Update();


 TCanvas *c11 = new TCanvas("c11","c11",800,800);

wdeteta1->SetLineColor(kOrange);
wdeteta2->SetLineColor(kRed);
wdeteta3->SetLineColor(kGreen);
wdeteta4->SetLineColor(kBlue);
wdeteta5->SetLineColor(kBlack);

 wdeteta1->Divide(wdeteta1cut, wdeteta1,1.0,1.0,"B");
 wdeteta1->SetMaximum(2.0);
 wdeteta1->SetMinimum(0.0);
 wdeteta1->SetMarkerSize(1);
 wdeteta1->Draw("pe");

 wdeteta2->Divide(wdeteta2cut, wdeteta2,1.0,1.0,"B");
 wdeteta2->SetMaximum(2.0);
 wdeteta2->SetMinimum(0.0);
 wdeteta2->SetMarkerSize(1);
 wdeteta2->Draw("pe same");

 wdeteta3->Divide(wdeteta3cut, wdeteta3,1.0,1.0,"B");
 wdeteta3->SetMaximum(2.0);
 wdeteta3->SetMinimum(0.0);
 wdeteta3->SetMarkerSize(1);
 wdeteta3->Draw("pe same");

 wdeteta4->Divide(wdeteta4cut, wdeteta4,1.0,1.0,"B");
 wdeteta4->SetMaximum(2.0);
 wdeteta4->SetMinimum(0.0);
 wdeteta4->SetMarkerSize(1);
 wdeteta4->Draw("pe same");

 wdeteta5->Divide(wdeteta5cut, wdeteta5,1.0,1.0,"B");
 wdeteta5->SetMaximum(2.0);
 wdeteta5->SetMinimum(0.0);
 wdeteta5->SetMarkerSize(1);
 wdeteta5->Draw("pe same");


 c11->Update();
 **/
}
//This method uses HENGNE's format for parameter order, unlike trigger efficiency macro (/work/rebel-clued0/jenny/workshop/cafe_p21.21.00/plotmacros/EfficiencyTreePlot.C)
 Double_t fitf(Double_t *v, Double_t *par)
   {
     //  return (par[0] + par[1]*v[0] + par[2]*v[0]*v[0] + par[3]*v[0]*v[0]*v[0] + par[4]*v[0]*v[0]*v[0]*v[0]);//*(par[5] + par[6]*v[0] + par[7]*v[0]*v[0] + par[8]*v[0]*v[0]*v[0] + par[9]*v[0]*v[0]*v[0]*v[0]);

 return (par[0] + par[1]*v[0] + par[2]*v[0]*v[0] + par[3]*v[0]*v[0]*v[0] + par[4]*v[0]*v[0]*v[0]*v[0]);

     // return 0.5 * par[2] * (1. + TMath::Erf((v[0]-par[0])/(sqrt(2)*par[1])))*(1. + TMath::Erf((v[0]-par[4])/(sqrt(2)*par[3])));

     //return 0.5 * par[2] * (1. + TMath::Erf((v[0]-par[0])/(sqrt(2)*par[1])))*( par[3]*v[0] + par[4]*v[0]*v[0] );

     // return 0.5 * par[2] * (1. + TMath::Erf((v[0]-par[0])/(sqrt(2)*par[1])));

     //return 0.5 * (par[0] + par[5]*v[0] + par[6]*v[0]*v[0]) * (1. + TMath::Erf((v[0]-par[1])/(sqrt(2)*par[2])))*(1. + TMath::Erf((v[0]-par[3])/(sqrt(2)*par[4])));

   }
