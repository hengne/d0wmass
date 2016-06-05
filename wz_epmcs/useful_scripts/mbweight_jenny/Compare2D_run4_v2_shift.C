#include"TFile.h"
#include"TTree.h"
#include"TH1.h"
#include"TF1.h"
#include"TH2D.h"
#include"TROOT.h"
#include"TStyle.h"
#include"TChain.h"
#include"TCanvas.h"
#include<stdlib.h>
#include<iostream>
#include"TMath.h"
#include<cmath>
#include"TVector2.h"
#include"TLorentzVector.h"
#include"TRandom3.h"
#include"TLegend.h"
#include "TSystem.h"
#include <TProfile.h>
#include <TProfile2D.h>
// g++ `root-config --libs` `root-config --cflags` minbiaslib.C -o minbiaslib 

/**
Usage: This code is used to correct the phi of the MB library after reweighting parameters are determined.  This correction is done in general because there is a small shift of the phi when the reweighting (which only accounts for MB set) is applied.  This code also allows for a shift in the phi of the original file (found using applyphishift_v6.C).  This shift is found comparing the MB and ZB library phi's, as the ZB library phi phase is correct.  If dphi is set to 0, the phi phase of the original file is unchanged.  The output of this file is used in minbiaslib_phicorr_v2.C to determine the final MB library.  Parameters for the library are determined earlier by making many libraries with a grid of parameters (power and number of 0 set events) and then fitting pmcs vs full mc in the zpt < 3, lumi < 2 region.

**/

void Compare2D_run4_v2_shift(){
  const double dphi=0.0; //add shift to outname.  Assumes file 1 is the original file we are shifting (and reweighting to), file 2 is the file we will reweight.

 TTree *tree2(0);
  TFile *input2(0);
 TTree *tree1(0);
  TFile *input1(0);
  TString rootfile1 = "mblibtest_default_Run3_nozeroset_origfile_nombset0.root";
  //  TString rootfile2 = "mblibtest_default_Run3_nozeroset_newmax_setpow0.40_small_zerofrac0.00.root";
   TString rootfile2 = "mblibtest_default_Run3_nozeroset_newmax_setpow0.60_small_zerofrac0.06.root"; //compout7
  //  TString rootfile2 = "mblibtest_default_Run3_nozeroset_newmax_setpow0.70_small_zerofrac0.09.root";//compout8
  //  TString rootfile2 = "mblibtest_default_Run4_nozeroset_newmax_setpow0.60_small_zerofrac0.06.root";
  //  TString rootfile2 = "mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.08.root";//compout20

  //TString rootfile2 = "mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06.root";
  //TString rootfile2 = "mblibtest_default_Run4_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06.root";

  if (!gSystem->AccessPathName( rootfile1 )) {
    cout << "accessing " << rootfile1 << endl;
    input1 = TFile::Open( rootfile1 );
  } 
  else{
    cout<< "problem accessing "<<rootfile1<< endl;
    exit(0);
  }
  tree1 = (TTree*)input1->Get("MBlib");


  //sprintf(name, "output/study_HardRecoil_newmodel_alllumi_COMPARE_testX.root");
  TFile* fout = new TFile("compout_v2.root", "recreate");

  float lumi, MBSET, mex, mey; 
  
  tree1->SetBranchStatus("*", 0);
  tree1->SetBranchStatus("lumi", 1);
  tree1->SetBranchStatus("MBSET", 1);
  tree1->SetBranchStatus("mex", 1);
   tree1->SetBranchStatus("mey", 1);
 
  
  tree1->SetBranchAddress("lumi", &lumi);
  tree1->SetBranchAddress("MBSET", &MBSET);
  tree1->SetBranchAddress("mex", &mex);
  tree1->SetBranchAddress("mey", &mey);
  TH1D *hPhi1  = new TH1D("Phi1", "Phi1", 32, 0., TMath::TwoPi());
  TH1D *hPhi2  = new TH1D("Phi2", "Phi2", 32, 0., TMath::TwoPi());

  TH2D *hMBSETPhi1  = new TH2D("MBSETPhi1", "MBSETPhi1", 1, 0, 1000, 32, 0., TMath::TwoPi());
  TH2D *hMBSETPhi2  = new TH2D("MBSETPhi2", "MBSETPhi2", 1, 0, 1000, 32, 0., TMath::TwoPi());
  
  hPhi1->Sumw2();
  hPhi2->Sumw2();
  hMBSETPhi1->Sumw2();
  hMBSETPhi2->Sumw2();

  int nentries1 = tree1->GetEntries();
  double met, phi;
  double metxnw, metynw, phinw;
  for (int i=0; i<nentries1; i++){
    if (i%1000000==0) std::cout << "Entries " << i << "/" << nentries1 << std::endl;
    tree1->GetEntry(i);
    // MBSET = TMath::Sqrt(MBSET);
    met = sqrt(mex*mex+mey*mey);
    phi = atan2(mey, mex);
    phinw = phi;
    metxnw = mex;
    metynw = mey;
    if(MBSET != 0){
      phinw = TVector2::Phi_0_2pi(phi+dphi);
      mex = met*cos(phinw);
      mey = met*sin(phinw);

      TVector2 v2met(mex, mey);
      hPhi1->Fill(TVector2::Phi_0_2pi(v2met.Phi()));
      if(MBSET > hMBSETPhi1->GetBinCenter(hMBSETPhi1->GetNbinsX()) ) hMBSETPhi1->Fill(hMBSETPhi1->GetBinCenter(hMBSETPhi1->GetNbinsX()), TVector2::Phi_0_2pi(v2met.Phi()));
      else hMBSETPhi1->Fill(MBSET, TVector2::Phi_0_2pi(v2met.Phi()));
    }
  }


    if (!gSystem->AccessPathName( rootfile2 )) {
    cout << "accessing " << rootfile2 << endl;
    input2 = TFile::Open( rootfile2 );
  } 
  else{
    cout<< "problem accessing "<<rootfile2<< endl;
    exit(0);
  }
  tree2 = (TTree*)input2->Get("MBlib");


  tree2->SetBranchStatus("*", 0);
  tree2->SetBranchStatus("lumi", 1);
  tree2->SetBranchStatus("MBSET", 1);
  tree2->SetBranchStatus("mex", 1);
   tree2->SetBranchStatus("mey", 1);
 
  
  tree2->SetBranchAddress("lumi", &lumi);
  tree2->SetBranchAddress("MBSET", &MBSET);
  tree2->SetBranchAddress("mex", &mex);
  tree2->SetBranchAddress("mey", &mey);

  int nentries2 = tree2->GetEntries();

  for (int i=0; i<nentries2; i++){
    if (i%1000000==0) std::cout << "Entries " << i << "/" << nentries2 << std::endl;
    tree2->GetEntry(i);
    // MBSET = TMath::Sqrt(MBSET);
    if(MBSET != 0){
      TVector2 v2met(mex, mey);
      hPhi2->Fill(TVector2::Phi_0_2pi(v2met.Phi()));
      if(MBSET > hMBSETPhi2->GetBinCenter(hMBSETPhi2->GetNbinsX()) ) {
	//cout<<MBSET<<"  "<<hMBSETPhi2->GetBinCenter(hMBSETPhi2->GetNbinsX())<<endl;
	hMBSETPhi2->Fill(hMBSETPhi2->GetBinCenter(hMBSETPhi2->GetNbinsX()), TVector2::Phi_0_2pi(v2met.Phi()));
      }
      else hMBSETPhi2->Fill(MBSET, TVector2::Phi_0_2pi(v2met.Phi()));
    }
  }

  hPhi2->Scale(hPhi1->Integral()/hPhi2->Integral());
  fout->cd();

     TCanvas *c1 = new TCanvas("c1","c1",800,800);

     TCanvas *c2 = new TCanvas("c2","c2",800,800);
  c1->Print("file.ps[");
  c2->Print("file2.ps[");
  for (int bin = 1; bin <= hMBSETPhi2->GetNbinsX(); bin++){
     TString name = "PMCSbin";
     name += bin;

     TString name2 = name;
     TString name3 = name;
     TString name4 = name;
     name2 += "phi1";
     name3 += "phi2";
     name4 += "eff";

     TH1D *px1 = hMBSETPhi1->ProjectionY(name2, bin, bin, "e");
     TH1D *px2 = hMBSETPhi2->ProjectionY(name3, bin, bin, "e");

     px2->Scale(px1->Integral()/px2->Integral());
     // px1->Write();
     // px2->Write();
     TH1D *eff=(TH1D*)px1->Clone();
     eff->SetName(name4);
     eff->SetTitle(name4);
     eff->Divide(px2);
     cout<<eff->Integral()<<endl;
     c1->cd();
     eff->Draw();
     c1->Print("file.ps");
     c2->cd();
     px1->Draw();
     px2->SetLineColor(2);
   
     px2->Draw("SAME");
     c2->Print("file2.ps");
     // eff->Write();
  }

  c1->Print("file.ps]"); 
  c2->Print("file2.ps]"); 
  //TH2D *heff(0);
  // heff->Divide(hMBSETPhi1, hMBSETPhi2, 1., 1., "b"); 

  fout->Write();
  fout->Close();

}
