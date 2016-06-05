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
const char *TreeName1 = "tree;1";
//const char *TreeName1 = "w;1";
//const char *TreeName1 = "tree;1";
//const char *TreeName1 = "wgen;1";
//const char *TreeName2 = "wgen;1";
const char *TreeName2 = "binary_tuple;1";
//**********************************************************

void EfficiencyTreePlot(){
  gROOT->ProcessLine(".x /home/jholzbau/rootlogon.C");
   TCanvas *c1 = new TCanvas("c1","c1",800,800);
  //.x /home/jholzbau/rootlogon.C
   TH1::SetDefaultSumw2();
  // TH1::Sumw2();
   /**
   //TString rootfile1 = "/prj_root/5007/wz2_write/jenny/cafe_allefftest/cafe_allefftest_run2b34.root";
   // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_20120621_102447/test.root";
   // TString rootfile2 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetest_20120621_102447/test.root";
   //  TString rootfile2 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_20120625_102758/pythia_wen_run2b34_treetestnoeff_WTree3.root";

   // TString rootfile1 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_big/cafe_alleff_big_run34.root";

   //TString rootfile1 = "/prj_root/5007/wz2_write/jenny/cafe_effall_lumitest/boringtestbig/run34.root";
   **/
    TString rootfile1 = "/prj_root/5007/wz2_write/jenny/cafe_effall_lumitest/boring3big/run3.root";//WMASS_MC_RUN2B4_wen_ovl_1340737351_boring3_20120626140336-13253712.d0cabsrv1.fnal.gov/result.root";//run4.root";

   // TString rootfile1 = "/prj_root/5007/wz2_write/jenny/new_run34_boringandalleff/boring3/boring3_run3.root";//with tick number stored

   // TString rootfile1 = "/prj_root/5007/wz2_write/jenny/cafe_alleff_boring3_run12dq/cafe_alleff_boring3_run12dq.root";
   /**
   //  /prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_allcuteff_default_20120711_115437/pythia_wen_run2b34_treetestnoeff_allcuteff_default.root

    //if use file below, need lumigen
   // TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_nozvtxcut_novtxsmear_20120709_154157/pythia_wen_run2b34_treetestnoeff_nozvtxcut_novtxsmear.root";//"/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_nozvtxcut_20120709_154157/pythia_wen_run2b34_treetestnoeff_nozvtxcut.root";

   // TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_20120625_102758/pythia_wen_run2b34_treetestnoeff_WTree3.root";
    
   //TString rootfile1 = "/prj_root/5007/wz2_write/jenny/pythia_wen_run2b34_treetestnoeff_20120625_110145/pythia_wen_run2b34_treetestnoeff_WTree3.root";
    // TString rootfile2 = "/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_tree/wz_epmcs/src/DATA/MBZBLibrary/binary_library_MC_Run2b34.root";

    // TString rootfile2 = "/prj_root/3103/wz2_write/ddboline/RunIIb34/DATA/MBZBLibrary/binary_library_MC_Run2b34.root";
    **/
    TString rootfile2 = "/work/yantze-clued0/ddboline/mbzb_p20.17.02/binary_library_MCZB_nodq_Run2b3.root";
     // TString rootfile2 = "/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_tree/wz_epmcs/src/DATA/MBZBLibrary/binary_library_newOVL_shot1.root";

 // TH1D *htp225 = (TH1D*)f2.Get("default/hWcandElecPhi_CC");


  Double_t xmin = -3;
  Double_t xmax = 15;
  Int_t nbin = 100;

     TH1D *t = new TH1D("top", "top",  nbin, xmin, xmax);
     TH1D *b = new TH1D("bottom", "bottom",  nbin, xmin, xmax);

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
 int check = 0;
 for (int i = 0; i < nentries; i++){//nentries; i++){
   tree1->GetEntry(i);
    t->Fill(tree1->GetLeaf("lumi")->GetValue(0));
    if (tree1->GetLeaf("lumi")->GetValue(0) < 0) {
      check++;
      cout<<tree1->GetLeaf("lumi")->GetValue(0)<<endl;
    }
   //t->Fill(tree1->GetLeaf("set")->GetValue(0));
 }
 cout<<"check "<<check<<endl;
 for (int j = 0; j < nentries2; j++){
   tree2->GetEntry(j);
   //  if(tree->GetLeaf("lumi")->GetValue(0) >= 0 && tree->GetLeaf("lumi")->GetValue(0) < 12){
   // b->Fill(tree2->GetLeaf("lumi")->GetValue(0));
    b->Fill(tree2->GetLeaf("InstLum")->GetValue(0));
   //b->Fill(tree2->GetLeaf("set")->GetValue(0));
 }

 // t->Divide(t, b,1.0,1.0,"B");

  t->SetMarkerSize(1);
  b->SetMarkerSize(1);
  // t->Scale(b->Integral()/t->Integral());//scale to "mc"
  t->Draw("pe");
  b->SetMarkerColor(kRed);
  b->SetLineColor(kRed);
  b->Scale(t->Integral()/b->Integral());//scale to "data"
  b->Draw("pe same");

gPad->Update();
c1->Update();
c1->Print("PlotVarlumicheckNODQ_run3.eps");
c1->Print("PlotVarlumicheckNODQ_run3.gif");

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
c2->Print("PlotChilumicheckNODQ_run3.eps");
c2->Print("PlotChilumicheckNODQ_run3.gif");

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
c3->Print("PlotEfflumicheckDQ.eps");
c3->Print("PlotEfflumicheckDQ.gif");
c3->Print("PlotEfflumicheckDQ.C");

**/
}
