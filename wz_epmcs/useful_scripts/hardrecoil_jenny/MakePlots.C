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

void GetChiHist(TH1D *t, TH1D *b, TCanvas *plots);
void GetRegHist(TH1D *t, TH1D *b, TCanvas *plots);

void MakePlots(){
    gROOT->ProcessLine(".x /home/jholzbau/rootlogon.C");
  //.x /home/jholzbau/rootlogon.C
    //  TH1::Sumw2();
  TRandom3 rand(1117);
  
  char name[1000];
  //TChain* tree = new TChain("tree", "tree");
  //for (int i=0; i<4; i++){
  //sprintf(name, "data/uEvt_%s_%d.root", tag, i);
  //tree->Add(name);
  //}
  // TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu_nozbset_lumiall.root");
  //TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu_nozbset_lumi6999.root");
  //TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu_nozbset_lumi46.root");
  //TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu_nozbset_lumi24.root");
  //   TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu_nozbset_lumi02.root");
  //   TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu_newmodel_zptbigbindep_lumi02.root");
  //TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu_newmodel_zptbigbindep_lumi6999.root");
   TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu.root");
  // TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu_lumi6999_2dzbzpt_hist.root");
  // TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu_lumi6999_default_hist.root");

  // TFile fpmcs ("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/result_znunu_nozbset_lumiall.root");

  double minlumi = 0.;
  double maxlumi = 9999.;
  
  TH1D *hpmcsGenZPt = (TH1D*)fpmcs.Get("default/ZNuNu_genZPt_Cuts");
  TH1D *hpmcsGenZPhi = (TH1D*)fpmcs.Get("default/ZNuNu_genZPhi_Cuts");
  TH1D *hpmcsRecoilResolution = (TH1D*)fpmcs.Get("default/ZNuNu_RecoilResolution_Cuts");
  TH1D *hpmcsRecoilPt = (TH1D*)fpmcs.Get("default/ZNuNu_RecoilPt_Cuts");
  TH1D *hpmcsRecoilPx = (TH1D*)fpmcs.Get("default/ZNuNu_RecoilPx_Cuts");
  TH1D *hpmcsRecoilPy = (TH1D*)fpmcs.Get("default/ZNuNu_RecoilPy_Cuts");
  TH1D *hpmcsRecoilPhi = (TH1D*)fpmcs.Get("default/ZNuNu_RecoilPhi_Cuts");
  TH1D *hpmcsGenVtxZ = (TH1D*)fpmcs.Get("default/ZNuNu_genVtxZ_Cuts");
  TH1D *hpmcsDeltaPhi_genZ_Recoil = (TH1D*)fpmcs.Get("default/ZNuNu_DeltaPhi_genZ_Recoil_Cuts");
  TH1D *hpmcsMET = (TH1D*)fpmcs.Get("default/ZNuNu_Met_Cuts");
  TH1D *hpmcsMETPhi = (TH1D*)fpmcs.Get("default/ZNuNu_MetPhi_Cuts");
  TH1D *hpmcsMEX = (TH1D*)fpmcs.Get("default/ZNuNu_MetX_Cuts");
  TH1D *hpmcsMEY = (TH1D*)fpmcs.Get("default/ZNuNu_MetY_Cuts");
  TH1D *hpmcsSET = (TH1D*)fpmcs.Get("default/ZNuNu_ScalarEt_Cuts");
  
  TProfile *hpmcsRecoilResponse_V_RecoilPt = (TProfile*)fpmcs.Get("default/ZNuNu_RecoilResponse_V_RecoilPt_Cuts");
  TProfile *hpmcsRecoilResponse_V_genZPt = (TProfile*)fpmcs.Get("default/ZNuNu_RecoilResponse_V_genZPt_Cuts");
  TProfile *hpmcsRecoilResponseProjection_V_RecoilPt = (TProfile*)fpmcs.Get("default/ZNuNu_RecoilResponseProjection_V_RecoilPt_Cuts");
  TProfile *hpmcsRecoilResponseProjection_V_genZPt = (TProfile*)fpmcs.Get("default/ZNuNu_RecoilResponseProjection_V_genZPt_Cuts");


  TTree *tree(0);
  TFile *input2(0);
  TString rootfile2 = "/work/rebel-clued0/jenny/Summer2013/COPYOTHER/fromrafael/ForJenny/hard_recoil/Znunu_Znunurun_Final.root";//NewRafaelRootFiles/znunu_killcell_20131003_All.root";
  if (!gSystem->AccessPathName( rootfile2 )) {
    cout << "accessing " << rootfile2 << endl;
    input2 = TFile::Open( rootfile2 );
  } 
  else{
    cout<< "problem accessing "<<rootfile2<< endl;
    exit(0);
  }
  tree = (TTree*)input2->Get("hardrecoil");

  sprintf(name, "output/study_HardRecoil_newmodel_zptdepsmeared4_extrasetbin_smooth_nophimodel_alllumidep_moremoreptbins_phitest22_lumi0999__testrafptbins46_signhist_64bin_noeffnohalf_test331_regbins46_lumiall_zphibinsfordeltaphiandresp_nophirespfunc.root");
  TFile* fout = new TFile(name, "recreate");
  
  char plotfile[500];
  sprintf(plotfile, "output/study_HardRecoil_newmodel_zptdepsmeared4_extrasetbin_smooth_nophimodel_alllumidep_moremoreptbins_phitest22_lumi0999__testrafptbins46_signhist_64bin_noeffnohalf_test331_regbins46_lumiall_zphibinsfordeltaphiandresp_nophirespfunc.ps");
  char plotfile1[500];
  sprintf(plotfile1, "output/study_HardRecoil_newmodel_zptdepsmeared4_extrasetbin_smooth_nophimodel_alllumidep_moremoreptbins_phitest22_lumi0999__testrafptbins46_signhist_64bin_noeffnohalf_test331_regbins46_lumiall_zphibinsfordeltaphiandresp_nophirespfunc.pdf");
  
  /**
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(0);
  gStyle->SetStatStyle(0);
  gStyle->SetFillStyle(0);
  gStyle->SetOptFit(1111);
  **/
  int colors[64];
  for (int i=0; i<50; i++) colors[i] = 51+i;
  for (int i=0; i<14; i++) colors[50+i] = 30+i;
  
  
  double lumi, ZBSET, SET, tickNum, Ztruepx, Ztruepy, Ztruepz, ZtrueE, utruepx, utruepy, utruepz, utrueE, urecopx, urecopy, urecopT, urecophi; 
  
  tree->SetBranchStatus("*", 0);
  tree->SetBranchStatus("lumi", 1);
  tree->SetBranchStatus("ZBSET", 1);
  tree->SetBranchStatus("SET", 1);
  tree->SetBranchStatus("tickNum", 1);
  tree->SetBranchStatus("Ztruepx", 1);
  tree->SetBranchStatus("Ztruepy", 1);
  tree->SetBranchStatus("Ztruepz", 1);
  tree->SetBranchStatus("ZtrueE", 1);
 tree->SetBranchStatus("utruepx", 1);
  tree->SetBranchStatus("utruepy", 1);
  tree->SetBranchStatus("utruepz", 1);
  tree->SetBranchStatus("utrueE", 1);
  tree->SetBranchStatus("urecopx", 1);
  tree->SetBranchStatus("urecopy", 1);
  tree->SetBranchStatus("urecopT", 1);
  tree->SetBranchStatus("urecophi", 1);
  
  tree->SetBranchAddress("lumi", &lumi);
  tree->SetBranchAddress("ZBSET", &ZBSET);
  tree->SetBranchAddress("SET", &SET);
  tree->SetBranchAddress("tickNum", &tickNum);
  tree->SetBranchAddress("Ztruepx", &Ztruepx);
  tree->SetBranchAddress("Ztruepy", &Ztruepy);
  tree->SetBranchAddress("Ztruepz", &Ztruepz);
  tree->SetBranchAddress("ZtrueE", &ZtrueE);
  tree->SetBranchAddress("utruepx", &utruepx);
  tree->SetBranchAddress("utruepy", &utruepy);
  tree->SetBranchAddress("utruepz", &utruepz);
  tree->SetBranchAddress("utrueE", &utrueE);
  tree->SetBranchAddress("urecopx", &urecopx);
  tree->SetBranchAddress("urecopy", &urecopy);
  tree->SetBranchAddress("urecopT", &urecopT);
  tree->SetBranchAddress("urecophi", &urecophi);
  
  TLegend* lg ;
  
  TH1D* hGenZPt = new TH1D("hGenZPt", "hGenZPt", 300, 0, 150);

  TH1D* hRecoilResolution = new TH1D("hRecoilResolution", "hRecoilResolution", 100, -2., 2.);
  TH1D* hRecoilPhi = new TH1D("hRecoilPhi", "hRecoilPhi", 64, 0., TMath::TwoPi());
  TH1D* hSET = new TH1D("hSET", "hSET", 300, 0., 300.);//no MB or ZB in the PMCS we are current running, so this is just hard recoil SET

  TH1D *hGenZPhi  = new TH1D("hgenZPhi", "gen Phi(Z)", 64, 0., TMath::TwoPi());
  TH1D *hRecoilPt = new TH1D("hRecoilPt", "recoil pT", 100, 0., 50.);
  TH1D *hRecoilPx = new TH1D("hRecoilPx", "recoil pX", 200, -50., 50.);
  TH1D *hRecoilPy = new TH1D("hRecoilPy", "recoil pY", 200, -50., 50.);
  TH1D *hDeltaPhi_genZ_Recoil = new TH1D("hDeltaPhi_genZ_Recoil", "DPhi(Z,recoil)", 64, 0., TMath::Pi());
 
  TProfile* hRecoilResponse_V_RecoilPt = new TProfile("hRecoilResponse_V_RecoilPt", "RecoilResponse_V_RecoilPt", 50, 0., 50., -20., 20., "i");
  TProfile* hRecoilResponse_V_genZPt = new TProfile("hRecoilResponse_V_genZPt", "RecoilResponse_V_genZPt", 50, 0., 50., -20., 20., "i");
  TProfile* hRecoilResponseProjection_V_RecoilPt = new TProfile("hRecoilResponseProjection_V_RecoilPt", "RecoilResponseProjection_V_RecoilPt", 50, 0., 50., -20., 20., "i");
  TProfile* hRecoilResponseProjection_V_genZPt = new TProfile("hRecoilResponseProjection_V_genZPt", "RecoilResponseProjection_V_genZPt", 50, 0., 50., -20., 20., "i");

  TH2D* hRecoilPt_V_RecoilPhi = new TH2D("hRecoilPt_V_RecoilPhi", "hRecoilPt_V_RecoilPhi", 16, 0, 1, 200, 0, 100);
  TH2D* hRecoilPt_V_ZBset = new TH2D("hRecoilPt_V_ZBset", "hRecoilPt_V_ZBset", 100, 0, 20, 200, 0, 100);
  TH2D* hZBset_V_RecoilPhi = new TH2D("hZBset_V_RecoilPhi", "hZBset_V_RecoilPhi",  16, 0, 1, 100, 0, 20);

  TH2D* hRecoilPt_V_lumi = new TH2D("hRecoilPt_V_lumi", "hRecoilPt_V_lumi", 50, 0, 12, 200, 0, 100);
  TH2D* hlumi_V_RecoilPhi = new TH2D("hlumi_V_RecoilPhi", "hlumi_V_RecoilPhi", 16, 0, 1, 50, 0, 12);

  hGenZPt->Sumw2();
  hRecoilResolution->Sumw2();
  hRecoilPhi->Sumw2();
  hSET->Sumw2();
  hRecoilResponse_V_RecoilPt->Sumw2();
  hRecoilResponse_V_genZPt->Sumw2();
  hRecoilResponseProjection_V_RecoilPt->Sumw2();
  hRecoilResponseProjection_V_genZPt->Sumw2();
hRecoilPt_V_RecoilPhi->Sumw2();
hRecoilPt_V_ZBset->Sumw2();
hZBset_V_RecoilPhi->Sumw2();
hRecoilPt_V_lumi->Sumw2();
hlumi_V_RecoilPhi->Sumw2();

  hGenZPhi->Sumw2();
  hRecoilPt->Sumw2();
  hRecoilPx->Sumw2();
  hRecoilPy->Sumw2();
  hDeltaPhi_genZ_Recoil->Sumw2();
 


  /**
     static HIST_1D ZNuNuCand_Hist[]={
     // same as above + kinematical cuts applied to neutrinos
     {"ZNuNu_genZPt_Cuts", "gen Pt(Z)", 300, 0., 150.},
     {"ZNuNu_genZPhi_Cuts", "gen Phi(Z)", 64, 0., TMath::TwoPi()},
     {"ZNuNu_RecoilResolution_Cuts", "recoil resolution", 100, -2., 2.},
     {"ZNuNu_RecoilPt_Cuts", "recoil pT", 100, 0., 50.},
     {"ZNuNu_RecoilPx_Cuts", "recoil pX", 200, -50., 50.},
     {"ZNuNu_RecoilPy_Cuts", "recoil pY", 200, -50., 50.},
     {"ZNuNu_RecoilPhi_Cuts", "recoil Phi", 64, 0., TMath::TwoPi()},
     {"ZNuNu_genVtxZ_Cuts", "gen vtx Z", 320, -80., 80.},
     {"ZNuNu_DeltaPhi_genZ_Recoil_Cuts", "DPhi(Z,recoil)", 64, 0., TMath::Pi()},
     {"ZNuNu_Met_Cuts", "Met", 100, 0., 50.},
     {"ZNuNu_MetPhi_Cuts", "Met Phi", 64, 0., TMath::Pi()},
     {"ZNuNu_MetX_Cuts", "MetX", 200, -50., 50.},
     {"ZNuNu_MetY_Cuts", "MetY", 200, -50., 50.},
     {"ZNuNu_ScalarEt_Cuts", "Scalar Et", 300, 0., 300.},
     {"", "", 0, 0., 0.}};
     
     // profiles used for ZNuNuAnalysis
     static HIST_PROFILE ZNuNuCand_Hist_Profile[]={
     {"ZNuNu_RecoilResponse_V_RecoilPt_Cuts","", 50, 0., 50., -20., 20., "i"},
     {"ZNuNu_RecoilResponse_V_genZPt_Cuts", "", 50, 0., 50., -20., 20., "i"},
     {"ZNuNu_RecoilResponseProjection_V_RecoilPt_Cuts", "", 50, 0., 50., -20., 20., "i"},
     {"ZNuNu_RecoilResponseProjection_V_genZPt_Cuts", "", 50, 0., 50., -20., 20., "i"},
  **/
  
  int nentries = tree->GetEntries();
  
  for (int i=0; i<nentries; i++){
    
    if (i%1000000==0) std::cout << "Entries " << i << "/" << nentries << std::endl;
    
    tree->GetEntry(i);
    //if(! (lumi < maxlumi && lumi > minlumi) ) continue;
    // if(TMath::Sqrt(ZBSET) < 5) continue;
    //cout<<lumi<<endl;
    TVector2 v2tZ(Ztruepx, Ztruepy);
    TVector2 v2tut(-1*Ztruepx, -1*Ztruepy);
    TVector2 v2ut(urecopx, urecopy);
    
    double tZpt = v2tZ.Mod();
    double tut = v2tut.Mod();
    double ut = v2ut.Mod();

   TLorentzVector z_vec(Ztruepx, Ztruepy, Ztruepz, ZtrueE);
    TLorentzVector utrue_vec(utruepx, utruepy, utruepz, utrueE);
    TVector2 utrue_vec2(utruepx, utruepy);
    TVector2 u_vec(urecopx, urecopy);

   Double_t response = u_vec.Mod()/utrue_vec2.Mod();
   //Double_t resolution = u_vec.Mod(); //should be 1- response
    Double_t response_proj = (u_vec*utrue_vec2)/(utrue_vec2*utrue_vec2);
    Double_t delta_phi = TMath::Abs(u_vec.DeltaPhi(utrue_vec2));
    ZBSET = TMath::Sqrt(ZBSET);
    double phi_norm = TVector2::Phi_0_2pi(v2ut.Phi())/TMath::TwoPi();
   
    //  if(! (u_vec.Mod() <= 1 && (1.0-response) >= 0.8 )) continue;
    //  if(! (tZpt >= 2.0 && tZpt < 10.0)) continue;

    hGenZPt->Fill(tZpt);
    hRecoilResolution->Fill(1.0-response);
    hRecoilPhi->Fill(u_vec.Phi());
    hSET->Fill(SET);
    hRecoilResponse_V_RecoilPt->Fill(ut, response);
    hRecoilResponse_V_genZPt->Fill(tZpt, response);
    hRecoilResponseProjection_V_RecoilPt->Fill(ut, response_proj);
    hRecoilResponseProjection_V_genZPt->Fill(tZpt, response_proj);

    hGenZPhi->Fill(TVector2::Phi_0_2pi(z_vec.Phi()));
    hRecoilPt->Fill(u_vec.Mod());
    hRecoilPx->Fill(urecopx);
    hRecoilPy->Fill(urecopy);
    hDeltaPhi_genZ_Recoil->Fill(TMath::Abs(TVector2::Phi_mpi_pi(z_vec.Phi() - u_vec.Phi())));


    hRecoilPt_V_RecoilPhi->Fill(phi_norm, ut);
    hRecoilPt_V_ZBset->Fill(ZBSET, ut);
    hZBset_V_RecoilPhi->Fill(phi_norm, ZBSET);
    hRecoilPt_V_lumi->Fill(lumi, ut);
    hlumi_V_RecoilPhi->Fill(phi_norm, lumi);

  }
  
  // print
  TCanvas* plots = new TCanvas("plots", "plots",50,10,700,800);
  sprintf(name, "%s[", plotfile);
  plots->Print(name);
  plots->Clear();

  // hGenZPt
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsGenZPt, hGenZPt, plots);
 plots->cd(2);
   GetChiHist(hpmcsGenZPt, hGenZPt, plots);
   plots->Print(plotfile);
   plots->Clear();

 // hGenZPhi
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsGenZPhi, hGenZPhi, plots);
 plots->cd(2);
   GetChiHist(hpmcsGenZPhi, hGenZPhi, plots);
   plots->Print(plotfile);
   plots->Clear();

 // hDeltaPhi_genZ_Recoil
  plots->Divide(1,2);
  plots->cd(1);
  GetRegHist(hpmcsDeltaPhi_genZ_Recoil, hDeltaPhi_genZ_Recoil, plots);
  plots->cd(2);
  GetChiHist(hpmcsDeltaPhi_genZ_Recoil, hDeltaPhi_genZ_Recoil, plots);
  plots->Print(plotfile);
   plots->Clear();

 // hRecoilResolution
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsRecoilResolution, hRecoilResolution, plots);
    plots->cd(2);
   GetChiHist(hpmcsRecoilResolution, hRecoilResolution, plots);
   plots->Print(plotfile);
   plots->Clear();

 
 // hRecoilPt
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsRecoilPt, hRecoilPt, plots);
    plots->cd(2);
   GetChiHist(hpmcsRecoilPt, hRecoilPt, plots);
   plots->Print(plotfile);
   plots->Clear();

 // hRecoilPhi
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsRecoilPhi, hRecoilPhi, plots);
    plots->cd(2);
   GetChiHist(hpmcsRecoilPhi, hRecoilPhi, plots);
   plots->Print(plotfile);
   plots->Clear();

 // hRecoilPx
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsRecoilPx, hRecoilPx, plots);
    plots->cd(2);
   GetChiHist(hpmcsRecoilPx, hRecoilPx, plots);
   plots->Print(plotfile);
   plots->Clear();

 // hRecoilPy
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsRecoilPy, hRecoilPy, plots);
    plots->cd(2);
   GetChiHist(hpmcsRecoilPy, hRecoilPy, plots);
   plots->Print(plotfile);
   plots->Clear();


 // hSET
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsSET, hSET, plots);
    plots->cd(2);
   GetChiHist(hpmcsSET, hSET, plots);
   plots->Print(plotfile);
   plots->Clear();


 // hRecoilResponse_V_RecoilPt
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsRecoilResponse_V_RecoilPt, hRecoilResponse_V_RecoilPt, plots);
    plots->cd(2);
   GetChiHist(hpmcsRecoilResponse_V_RecoilPt, hRecoilResponse_V_RecoilPt, plots);
   plots->Print(plotfile);
   plots->Clear();

 // hRecoilResponse_V_genZPt
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsRecoilResponse_V_genZPt, hRecoilResponse_V_genZPt, plots);
    plots->cd(2);
   GetChiHist(hpmcsRecoilResponse_V_genZPt, hRecoilResponse_V_genZPt, plots);
   plots->Print(plotfile);
   plots->Clear();

 // hRecoilResponseProjection_V_RecoilPt
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsRecoilResponseProjection_V_RecoilPt, hRecoilResponseProjection_V_RecoilPt, plots);
    plots->cd(2);
   GetChiHist(hpmcsRecoilResponseProjection_V_RecoilPt, hRecoilResponseProjection_V_RecoilPt, plots);
   plots->Print(plotfile);
   plots->Clear();

 // hRecoilResponseProjection_V_genZPt
  plots->Divide(1,2);
  plots->cd(1);
   GetRegHist(hpmcsRecoilResponseProjection_V_genZPt, hRecoilResponseProjection_V_genZPt, plots);
    plots->cd(2);
   GetChiHist(hpmcsRecoilResponseProjection_V_genZPt, hRecoilResponseProjection_V_genZPt, plots);
   plots->Print(plotfile);
   plots->Clear();


   hRecoilPt_V_RecoilPhi->Draw("colz");
   plots->Print(plotfile);
   plots->Clear();
    hRecoilPt_V_ZBset->Draw("colz");
   plots->Print(plotfile);
   plots->Clear();
    hZBset_V_RecoilPhi->Draw("colz");
   plots->Print(plotfile);
   plots->Clear();
    hRecoilPt_V_lumi->Draw("colz");
   plots->Print(plotfile);
   plots->Clear();
    hlumi_V_RecoilPhi->Draw("colz");
   plots->Print(plotfile);
   plots->Clear();


  // end
  sprintf(name, "%s]", plotfile);
  plots->Print(name);
  sprintf(name, ".! ps2pdf %s %s", plotfile, plotfile1);
  gROOT->ProcessLine(name);
  
  // 
  fout->Write();
  fout->Close();
   
}
void GetRegHist(TH1D *t, TH1D *b, TCanvas *plots){
  t->SetLineColor(4);
  t->SetLineStyle(1);
  b->SetLineColor(2);
  b->SetLineStyle(1);
  //  b->SetMarkerColor(2);
  // b->SetMarkerStyle(11);//20);
  b->Draw("le");
  t->Scale(b->Integral()/t->Integral());
  t->Draw("SAME ple");
  
  if(t->GetMaximum() > b->GetMaximum()) b->SetMaximum(t->GetMaximum()*1.05);

gPad->Update();
plots->Update();
}

void GetChiHist(TH1D *t, TH1D *b, TCanvas *plots){
//  TCanvas *c2 = new TCanvas("c2","c2",800,800);

  
  // histograms for chi2
  TH1 *histo_chi2;
  
  TH1D *temp_chi2 = new TH1D("temp_chi2", "", t->GetNbinsX(), t->GetXaxis()->GetXmin(), t->GetXaxis()->GetXmax());
  TProfile *h2 = dynamic_cast<TProfile *>(t);
  
  if(h2 != 0) {
    histo_chi2 = (TH1D *)temp_chi2->Clone();
    histo_chi2->SetName("test");
    histo_chi2->Reset();
  } else {
    histo_chi2 = (TH1D *)t->Clone();
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
    if((center >= t->GetXaxis()->GetXmin()) && (center <= t->GetXaxis()->GetXmax())) {
      n2 = t->GetBinContent(i+1);
      n1 = b->GetBinContent(i+1);
      error2=t->GetBinError(i+1);
      error1=b->GetBinError(i+1);
      if(fabs(n1)<0.001) error1 = 1.;  // if no entries for data, assign the error to 1

      // only look at entries where fast MC distribution have some entries
      if(fabs(n2)>0.){
        NBin ++;
        delta = n1-n2;
        chisq += delta*delta/(error1*error1+error2*error2);
	//cout<<center<<"  "<<n1<<"  "<<error1<<"  "<<n2<<"  "<<error2<<"  "<<delta<<"  "<<delta/sqrt(error1*error1+error2*error2)<<endl;
        histo_chi2->SetBinContent(i+1, delta/sqrt(error1*error1+error2*error2));
        histo_chi2->SetBinError(i+1, 1);
      } else {
        histo_chi2->SetBinContent(i+1, 0.);
        histo_chi2->SetBinError(i+1, 1);
      }
    } // for given range
  }//loop over all bins
  // cout<<"chi2 "<<chisq<<" over ndof of "<<t->GetNbinsX()<<endl;
  histo_chi2->SetMarkerStyle(8);
  histo_chi2->SetMarkerSize(0.5);
  histo_chi2->SetMarkerColor(2);
  histo_chi2->SetLineColor(1);

  //char name[150]; 
  //sprintf(name, "#chi distribution");
  //sprintf(name, chisq);

  TString namez = "#chi distribution with overall #chi^{2} of ";
  namez += int(chisq);
  namez += " for ";
  namez += t->GetNbinsX();
  namez += " bins";

  histo_chi2->SetTitle(namez);

  histo_chi2->Draw("pe ");

gPad->Update();
plots->Update();

}
  
