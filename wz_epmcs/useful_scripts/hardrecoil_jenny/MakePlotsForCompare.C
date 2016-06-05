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
int pTee_Eta_Bin(double pTee_eta); //from WZ_Utils in wmass_analysis

void MakePlotsForCompare(){
    gROOT->ProcessLine(".x /home/jholzbau/rootlogon.C");
 
  TTree *tree(0);
  TFile *input2(0);
  TString rootfile2 = "/work/rebel-clued0/jenny/Summer2013/COPYOTHER/fromrafael2/ForJenny/hard_recoil/Znunu_RCLSA_newkillcell_runiib3.root";
  // TString rootfile2 = "/work/rebel-clued0/jenny/Summer2013/COPYOTHER/fromrafael/ForJenny/hard_recoil/Znunu_Znunurun_Final.root";
  //TString rootfile2 = "/work/rebel-clued0/jenny/Summer2013/COPYOTHER/fromrafael/ForJenny/hard_recoil/Znunu_Znunurun_HVtest.root";


  if (!gSystem->AccessPathName( rootfile2 )) {
    cout << "accessing " << rootfile2 << endl;
    input2 = TFile::Open( rootfile2 );
  } 
  else{
    cout<< "problem accessing "<<rootfile2<< endl;
    exit(0);
  }
  tree = (TTree*)input2->Get("hardrecoil");

  //sprintf(name, "output/study_HardRecoil_newmodel_alllumi_COMPARE_testX.root");
  TFile* fout = new TFile("output/study_HardRecoil_newmodel_alllumi_COMPARE_testX_GOODKILLCELL.root", "recreate");
  //TFile* fout = new TFile("output/study_HardRecoil_newmodel_alllumi_COMPARE_testX_HVtest.root", "recreate");
  TDirectory *cdtof = fout->mkdir("ZNuNuCand_Hist");
  cdtof->cd();    // make the "tof" directory the current directory

  
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
  
  TH1D* hGenZPt = new TH1D("ZNuNu_genZPt_Cuts", "ZNuNu_genZPt_Cuts", 300, 0, 150);

  TH1D* hRecoilResolution = new TH1D("ZNuNu_RecoilResolution_Cuts", "ZNuNu_RecoilResolution_Cuts", 100, -2., 2.);
  TH1D* hRecoilPhi = new TH1D("ZNuNu_RecoilPhi_Cuts", "ZNuNu_RecoilPhi_Cuts", 64, 0., TMath::TwoPi());
  TH1D* hSET = new TH1D("ZNuNu_ScalarEt_Cuts", "ZNuNu_ScalarEt_Cuts", 300, 0., 300.);//no MB or ZB in the PMCS we are current running, so this is just hard recoil SET

  TH1D *hGenZPhi  = new TH1D("ZNuNu_genZPhi_Cuts", "ZNuNu_genZPhi_Cuts", 64, 0., TMath::TwoPi());
  TH1D *hRecoilPt = new TH1D("ZNuNu_RecoilPt_Cuts", "ZNuNu_RecoilPt_Cuts", 100, 0., 50.);
  TH1D *hRecoilPx = new TH1D("ZNuNu_RecoilPx_Cuts", "ZNuNu_RecoilPx_Cuts", 200, -50., 50.);
  TH1D *hRecoilPy = new TH1D("ZNuNu_RecoilPy_Cuts", "ZNuNu_RecoilPy_Cuts", 200, -50., 50.);
  TH1D *hDeltaPhi_genZ_Recoil = new TH1D("ZNuNu_DeltaPhi_genZ_Recoil_Cuts", "ZNuNu_DeltaPhi_genZ_Recoil_Cuts", 64, 0., TMath::Pi());
 
  TProfile* hRecoilResponse_V_RecoilPt = new TProfile("ZNuNu_RecoilResponse_V_RecoilPt_Cuts", "ZNuNu_RecoilResponse_V_RecoilPt_Cuts", 50, 0., 50., -20., 20., "i");
  TProfile* hRecoilResponse_V_genZPt = new TProfile("ZNuNu_RecoilResponse_V_genZPt_Cuts", "ZNuNu_RecoilResponse_V_genZPt_Cuts", 50, 0., 50., -20., 20., "i");
  TProfile* hRecoilResponseProjection_V_RecoilPt = new TProfile("ZNuNu_RecoilResponseProjection_V_RecoilPt_Cuts", "ZNuNu_RecoilResponseProjection_V_RecoilPt_Cuts", 50, 0., 50., -20., 20., "i");
  TProfile* hRecoilResponseProjection_V_genZPt = new TProfile("ZNuNu_RecoilResponseProjection_V_genZPt_Cuts", "ZNuNu_RecoilResponseProjection_V_genZPt_Cuts", 50, 0., 50., -20., 20., "i");

  TProfile *hRecoilResponse_V_RecoilPhi  = new TProfile("ZNuNu_RecoilResponse_V_RecoilPhi_Cuts", "RecoilResponse_V_RecoilPhi", 50, 0., 7., -20., 20., "i");
  TProfile *hRecoilResponse_V_genZPhi  = new TProfile("ZNuNu_RecoilResponse_V_genZPhi_Cuts", "RecoilResponse_V_genZPhi", 50, 0., 7., -20., 20., "i");
  TProfile *hRecoilResponse_V_lumi  = new TProfile("ZNuNu_RecoilResponse_V_lumi_Cuts", "RecoilResponse_V_lumi", 50, 0., 15., -20., 20., "i");
  TProfile *hRecoilResponse_V_zbset   = new TProfile("ZNuNu_RecoilResponse_V_zbset_Cuts", "RecoilResponse_V_zbset", 50, 0., 50., -20., 20., "i");

TProfile2D* hRecoilResponse_V_RecoilPt_genZPt = new TProfile2D("ZNuNu_RecoilResponse_V_RecoilPt_genZPt_Cuts", "ZNuNu_RecoilResponse_V_RecoilPt_genZPt_Cuts", 50, 0., 50.,50, 0., 50., -20., 20., "i");
  
  TH1D* hGenVtxZ = new TH1D("ZNuNu_genVtxZ_Cuts", "ZNuNu_genVtxZ_Cuts",320, -80., 80.);
  TH1D* hVtxZ = new TH1D("ZNuNu_VtxZ_Cuts", "ZNuNu_VtxZ_Cuts", 320, -80., 80.);
  TH1D* hMET = new TH1D("ZNuNu_Met_Cuts", "ZNuNu_Met_Cuts", 100, 0., 50.);
  TH1D* hMETPhi = new TH1D("ZNuNu_MetPhi_Cuts", "ZNuNu_MetPhi_Cuts", 64, 0., TMath::Pi());
  TH1D* hMEX = new TH1D("ZNuNu_MetX_Cuts", "ZNuNu_MetX_Cuts", 200, -50., 50.);
  TH1D* hMEY = new TH1D("ZNuNu_MetY_Cuts", "ZNuNu_MetY_Cuts", 200, -50., 50.);

  hGenZPt->Sumw2();
  hRecoilResolution->Sumw2();
  hRecoilPhi->Sumw2();
  hSET->Sumw2();
  hGenZPhi->Sumw2();
  hRecoilPt->Sumw2();
  hRecoilPx->Sumw2();
  hRecoilPy->Sumw2();
  hDeltaPhi_genZ_Recoil->Sumw2();

  hGenVtxZ->Sumw2();
  hVtxZ->Sumw2();
  hMET->Sumw2();
  hMETPhi->Sumw2();
  hMEX->Sumw2();
  hMEY->Sumw2();

  hRecoilResponse_V_RecoilPt->Sumw2();
  hRecoilResponse_V_genZPt->Sumw2();
  hRecoilResponseProjection_V_RecoilPt->Sumw2();
  hRecoilResponseProjection_V_genZPt->Sumw2();
  hRecoilResponse_V_RecoilPhi->Sumw2();
  hRecoilResponse_V_genZPhi->Sumw2();
  hRecoilResponse_V_lumi->Sumw2();
  hRecoilResponse_V_zbset->Sumw2();
hRecoilResponse_V_RecoilPt_genZPt->Sumw2();

  TH1D* histo[15];
  histo[0] = hGenZPt;
  histo[1] = hRecoilResolution;
  histo[2] = hRecoilPhi;
  histo[3] = hSET;
  histo[4] =  hGenZPhi;
  histo[5] = hRecoilPt;
  histo[6] = hRecoilPx;
  histo[7] = hRecoilPy;
  histo[8] = hDeltaPhi_genZ_Recoil;
  histo[9] = hGenVtxZ;
  histo[10] = hVtxZ;
  histo[11] = hMET;
  histo[12] = hMETPhi;
  histo[13] =  hMEX;
  histo[14] = hMEY;
  
 // clone some histograms for Junjie's comparison plots
  // per bins of: UT        (with suffix _bin_<N>), 
  //              true Z Pt (with suffix _genZPt_bin_<N>) 
  const string _histos_name[]={ 
    "ZNuNu_genZPt_Cuts",
    "ZNuNu_RecoilResolution_Cuts",
    "ZNuNu_RecoilPhi_Cuts",
    "ZNuNu_ScalarEt_Cuts",
    "ZNuNu_genZPhi_Cuts",
    "ZNuNu_RecoilPt_Cuts",
    "ZNuNu_RecoilPx_Cuts",
    "ZNuNu_RecoilPy_Cuts",
    "ZNuNu_DeltaPhi_genZ_Recoil_Cuts",
    "ZNuNu_genVtxZ_Cuts",
    "ZNuNu_VtxZ_Cuts",
    "ZNuNu_Met_Cuts",
    "ZNuNu_MetPhi_Cuts",
    "ZNuNu_MetX_Cuts",
    "ZNuNu_MetY_Cuts"
  };
 
  if(sizeof(_histos_name) != sizeof(histo)){ cout<<"histogram array and histogram name array have different sizes"<<"  "<<sizeof(_histos_name)/sizeof(string)<<"  "<<sizeof(histo)/sizeof(string)<<endl; exit(0);}
  int nhist=sizeof(_histos_name)/sizeof(string);

  const int n=10;
  TH1D* histoTRUE[nhist][n];
  TH1D* histoSMEAR[nhist][n];
  TH1D* histozbset[nhist][n];
  TH1D* histolumi[nhist][n];
  TH1D* histotruephi[nhist][n];
  TH1D* historecophi[nhist][n];

   char sn_smear[10];  
   char sn[20];
   char sn_zbset[15]; 
   char sn_lumi[15]; 
   char sn_truephi[15]; 
   char sn_recophi[15]; 

  for(int ihist=0;ihist<nhist;ihist++) {
   for(Int_t i=0; i<n; i++){
     sprintf(sn, "_genZPt_bin_%d", i);
     sprintf(sn_smear, "_bin_%d", i);
     sprintf(sn_zbset, "_zbset_bin_%d", i);
     sprintf(sn_lumi, "_lumi_bin_%d", i);
     sprintf(sn_truephi, "_genZPhi_bin_%d", i);
     sprintf(sn_recophi, "_UPhi_bin_%d", i);

     histoTRUE[ihist][i] =  (TH1D*) histo[ihist]->Clone();
     histoTRUE[ihist][i]->SetName(TString(_histos_name[ihist].c_str())+sn);
  
     histoSMEAR[ihist][i] =  (TH1D*) histo[ihist]->Clone();
     histoSMEAR[ihist][i]->SetName(TString(_histos_name[ihist].c_str())+sn_smear);

     histozbset[ihist][i] =  (TH1D*) histo[ihist]->Clone();
     histozbset[ihist][i]->SetName(TString(_histos_name[ihist].c_str())+sn_zbset);

     histolumi[ihist][i] =  (TH1D*) histo[ihist]->Clone();
     histolumi[ihist][i]->SetName(TString(_histos_name[ihist].c_str())+sn_lumi);

     histotruephi[ihist][i] =  (TH1D*) histo[ihist]->Clone();
     histotruephi[ihist][i]->SetName(TString(_histos_name[ihist].c_str())+sn_truephi);

     historecophi[ihist][i] =  (TH1D*) histo[ihist]->Clone();
     historecophi[ihist][i]->SetName(TString(_histos_name[ihist].c_str())+sn_recophi);
   }

 }
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
    TVector2 v2met(-1*urecopx, -1*urecopy);
    
    double tZpt = v2tZ.Mod();
    double tut = v2tut.Mod();
    double ut = v2ut.Mod();

   TLorentzVector z_vec(Ztruepx, Ztruepy, Ztruepz, ZtrueE);
    TLorentzVector utrue_vec(utruepx, utruepy, utruepz, utrueE);
    TVector2 utrue_vec2(utruepx, utruepy);
    TVector2 u_vec(urecopx, urecopy);

   Double_t response = u_vec.Mod()/utrue_vec2.Mod();
   //Double_t resolution = u_vec.Mod(); //should be 1- response to match pmcs
    Double_t response_proj = (u_vec*utrue_vec2)/(utrue_vec2*utrue_vec2);
    Double_t delta_phi = TMath::Abs(u_vec.DeltaPhi(utrue_vec2));
    ZBSET = TMath::Sqrt(ZBSET);
    double phi_norm = TVector2::Phi_0_2pi(v2ut.Phi())/TMath::TwoPi();
  
 

    histo[0]->Fill(tZpt);
    histo[1]->Fill(1.0-response);
    histo[2]->Fill(u_vec.Phi());
    histo[3]->Fill(SET);
    
    histo[4]->Fill(TVector2::Phi_0_2pi(z_vec.Phi()));
    histo[5]->Fill(u_vec.Mod());
    histo[6]->Fill(urecopx);
    histo[7]->Fill(urecopy);
    histo[8]->Fill(TMath::Abs(TVector2::Phi_mpi_pi(z_vec.Phi() - u_vec.Phi())));

    histo[9]->Fill(0.);
    histo[10]->Fill(0.);
    histo[11]->Fill(v2met.Mod());
    histo[12]->Fill( TVector2::Phi_0_2pi(v2met.Phi()));
    histo[13]->Fill(-1*urecopx);
    histo[14]->Fill(-1*urecopy);

    int ZPt_true_bin = pTee_Eta_Bin(tZpt);
    int Ut_bin = pTee_Eta_Bin(u_vec.Mod());
    int zbset_bin = pTee_Eta_Bin(ZBSET);


  int lumi_bin = 0;
  if(lumi > 2 && lumi<=3) lumi_bin = 1;
  if(lumi > 3 && lumi<=4) lumi_bin = 2;
  if(lumi > 4 && lumi<=5) lumi_bin = 3;
  if(lumi > 5 && lumi<=6) lumi_bin = 4;
  if(lumi > 6 && lumi<=8) lumi_bin = 5;
  if(lumi > 8) lumi_bin = 6;

  int truephi_bin = 0;
  if(TVector2::Phi_0_2pi(z_vec.Phi()) > 1.0 && TVector2::Phi_0_2pi(z_vec.Phi()) <=2.0) truephi_bin = 1;
  if(TVector2::Phi_0_2pi(z_vec.Phi()) > 2.0 && TVector2::Phi_0_2pi(z_vec.Phi()) <=3.0) truephi_bin = 2;
  if(TVector2::Phi_0_2pi(z_vec.Phi()) > 3.0 && TVector2::Phi_0_2pi(z_vec.Phi()) <=4.0) truephi_bin = 3;
  if(TVector2::Phi_0_2pi(z_vec.Phi()) > 4.0 && TVector2::Phi_0_2pi(z_vec.Phi()) <=5.0) truephi_bin = 4;
  if(TVector2::Phi_0_2pi(z_vec.Phi()) > 5.0 && TVector2::Phi_0_2pi(z_vec.Phi()) <=6.0) truephi_bin = 5;
  if(TVector2::Phi_0_2pi(z_vec.Phi()) > 6.0) truephi_bin = 6;

 
  int recophi_bin = 0;
  if(TVector2::Phi_0_2pi(u_vec.Phi()) > 1.0 && TVector2::Phi_0_2pi(u_vec.Phi()) <=2.0) recophi_bin = 1;
  if(TVector2::Phi_0_2pi(u_vec.Phi()) > 2.0 && TVector2::Phi_0_2pi(u_vec.Phi()) <=3.0) recophi_bin = 2;
  if(TVector2::Phi_0_2pi(u_vec.Phi()) > 3.0 && TVector2::Phi_0_2pi(u_vec.Phi()) <=4.0) recophi_bin = 3;
  if(TVector2::Phi_0_2pi(u_vec.Phi()) > 4.0 && TVector2::Phi_0_2pi(u_vec.Phi()) <=5.0) recophi_bin = 4;
  if(TVector2::Phi_0_2pi(u_vec.Phi()) > 5.0 && TVector2::Phi_0_2pi(u_vec.Phi()) <=6.0) recophi_bin = 5;
  if(TVector2::Phi_0_2pi(u_vec.Phi()) > 6.0) recophi_bin = 6;

 
 
 if(ZPt_true_bin >= 0) {
    histoTRUE[0][ZPt_true_bin]->Fill(tZpt);
    histoTRUE[1][ZPt_true_bin]->Fill(1.0-response);
    histoTRUE[2][ZPt_true_bin]->Fill(u_vec.Phi());
    histoTRUE[3][ZPt_true_bin]->Fill(SET);
    
    histoTRUE[4][ZPt_true_bin]->Fill(TVector2::Phi_0_2pi(z_vec.Phi()));
    histoTRUE[5][ZPt_true_bin]->Fill(u_vec.Mod());
    histoTRUE[6][ZPt_true_bin]->Fill(urecopx);
    histoTRUE[7][ZPt_true_bin]->Fill(urecopy);
    histoTRUE[8][ZPt_true_bin]->Fill(TMath::Abs(TVector2::Phi_mpi_pi(z_vec.Phi() - u_vec.Phi())));

    histoTRUE[9][ZPt_true_bin]->Fill(0.);
    histoTRUE[10][ZPt_true_bin]->Fill(0.);
    histoTRUE[11][ZPt_true_bin]->Fill(v2met.Mod());
    histoTRUE[12][ZPt_true_bin]->Fill( TVector2::Phi_0_2pi(v2met.Phi()));
    histoTRUE[13][ZPt_true_bin]->Fill(-1*urecopx);
    histoTRUE[14][ZPt_true_bin]->Fill(-1*urecopy);
 }
if(Ut_bin >= 0) {
    histoSMEAR[0][Ut_bin]->Fill(tZpt);
    histoSMEAR[1][Ut_bin]->Fill(1.0-response);
    histoSMEAR[2][Ut_bin]->Fill(u_vec.Phi());
    histoSMEAR[3][Ut_bin]->Fill(SET);
    
    histoSMEAR[4][Ut_bin]->Fill(TVector2::Phi_0_2pi(z_vec.Phi()));
    histoSMEAR[5][Ut_bin]->Fill(u_vec.Mod());
    histoSMEAR[6][Ut_bin]->Fill(urecopx);
    histoSMEAR[7][Ut_bin]->Fill(urecopy);
    histoSMEAR[8][Ut_bin]->Fill(TMath::Abs(TVector2::Phi_mpi_pi(z_vec.Phi() - u_vec.Phi())));

    histoSMEAR[9][Ut_bin]->Fill(0.);
    histoSMEAR[10][Ut_bin]->Fill(0.);
    histoSMEAR[11][Ut_bin]->Fill(v2met.Mod());
    histoSMEAR[12][Ut_bin]->Fill( TVector2::Phi_0_2pi(v2met.Phi()));
    histoSMEAR[13][Ut_bin]->Fill(-1*urecopx);
    histoSMEAR[14][Ut_bin]->Fill(-1*urecopy);
 }

if(zbset_bin >= 0) {
    histozbset[0][zbset_bin]->Fill(tZpt);
    histozbset[1][zbset_bin]->Fill(1.0-response);
    histozbset[2][zbset_bin]->Fill(u_vec.Phi());
    histozbset[3][zbset_bin]->Fill(SET);
    
    histozbset[4][zbset_bin]->Fill(TVector2::Phi_0_2pi(z_vec.Phi()));
    histozbset[5][zbset_bin]->Fill(u_vec.Mod());
    histozbset[6][zbset_bin]->Fill(urecopx);
    histozbset[7][zbset_bin]->Fill(urecopy);
    histozbset[8][zbset_bin]->Fill(TMath::Abs(TVector2::Phi_mpi_pi(z_vec.Phi() - u_vec.Phi())));

    histozbset[9][zbset_bin]->Fill(0.);
    histozbset[10][zbset_bin]->Fill(0.);
    histozbset[11][zbset_bin]->Fill(v2met.Mod());
    histozbset[12][zbset_bin]->Fill( TVector2::Phi_0_2pi(v2met.Phi()));
    histozbset[13][zbset_bin]->Fill(-1*urecopx);
    histozbset[14][zbset_bin]->Fill(-1*urecopy);
 }

if(lumi_bin >= 0) {
    histolumi[0][lumi_bin]->Fill(tZpt);
    histolumi[1][lumi_bin]->Fill(1.0-response);
    histolumi[2][lumi_bin]->Fill(u_vec.Phi());
    histolumi[3][lumi_bin]->Fill(SET);
    
    histolumi[4][lumi_bin]->Fill(TVector2::Phi_0_2pi(z_vec.Phi()));
    histolumi[5][lumi_bin]->Fill(u_vec.Mod());
    histolumi[6][lumi_bin]->Fill(urecopx);
    histolumi[7][lumi_bin]->Fill(urecopy);
    histolumi[8][lumi_bin]->Fill(TMath::Abs(TVector2::Phi_mpi_pi(z_vec.Phi() - u_vec.Phi())));

    histolumi[9][lumi_bin]->Fill(0.);
    histolumi[10][lumi_bin]->Fill(0.);
    histolumi[11][lumi_bin]->Fill(v2met.Mod());
    histolumi[12][lumi_bin]->Fill( TVector2::Phi_0_2pi(v2met.Phi()));
    histolumi[13][lumi_bin]->Fill(-1*urecopx);
    histolumi[14][lumi_bin]->Fill(-1*urecopy);
 }

if(truephi_bin >= 0) {
    histotruephi[0][truephi_bin]->Fill(tZpt);
    histotruephi[1][truephi_bin]->Fill(1.0-response);
    histotruephi[2][truephi_bin]->Fill(u_vec.Phi());
    histotruephi[3][truephi_bin]->Fill(SET);
    
    histotruephi[4][truephi_bin]->Fill(TVector2::Phi_0_2pi(z_vec.Phi()));
    histotruephi[5][truephi_bin]->Fill(u_vec.Mod());
    histotruephi[6][truephi_bin]->Fill(urecopx);
    histotruephi[7][truephi_bin]->Fill(urecopy);
    histotruephi[8][truephi_bin]->Fill(TMath::Abs(TVector2::Phi_mpi_pi(z_vec.Phi() - u_vec.Phi())));

    histotruephi[9][truephi_bin]->Fill(0.);
    histotruephi[10][truephi_bin]->Fill(0.);
    histotruephi[11][truephi_bin]->Fill(v2met.Mod());
    histotruephi[12][truephi_bin]->Fill( TVector2::Phi_0_2pi(v2met.Phi()));
    histotruephi[13][truephi_bin]->Fill(-1*urecopx);
    histotruephi[14][truephi_bin]->Fill(-1*urecopy);
 }

if(recophi_bin >= 0) {
    historecophi[0][recophi_bin]->Fill(tZpt);
    historecophi[1][recophi_bin]->Fill(1.0-response);
    historecophi[2][recophi_bin]->Fill(u_vec.Phi());
    historecophi[3][recophi_bin]->Fill(SET);
    
    historecophi[4][recophi_bin]->Fill(TVector2::Phi_0_2pi(z_vec.Phi()));
    historecophi[5][recophi_bin]->Fill(u_vec.Mod());
    historecophi[6][recophi_bin]->Fill(urecopx);
    historecophi[7][recophi_bin]->Fill(urecopy);
    historecophi[8][recophi_bin]->Fill(TMath::Abs(TVector2::Phi_mpi_pi(z_vec.Phi() - u_vec.Phi())));

    historecophi[9][recophi_bin]->Fill(0.);
    historecophi[10][recophi_bin]->Fill(0.);
    historecophi[11][recophi_bin]->Fill(v2met.Mod());
    historecophi[12][recophi_bin]->Fill( TVector2::Phi_0_2pi(v2met.Phi()));
    historecophi[13][recophi_bin]->Fill(-1*urecopx);
    historecophi[14][recophi_bin]->Fill(-1*urecopy);
 }


    hRecoilResponse_V_RecoilPt->Fill(ut, response);
    hRecoilResponse_V_genZPt->Fill(tZpt, response);
    hRecoilResponseProjection_V_RecoilPt->Fill(ut, response_proj);
    hRecoilResponseProjection_V_genZPt->Fill(tZpt, response_proj);

    hRecoilResponse_V_RecoilPhi->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), response);
    hRecoilResponse_V_genZPhi->Fill(TVector2::Phi_0_2pi(z_vec.Phi()), response);
    hRecoilResponse_V_lumi->Fill(lumi, response);
    hRecoilResponse_V_zbset->Fill(ZBSET, response);

hRecoilResponse_V_RecoilPt_genZPt->Fill(ut, tZpt, response);
 

  }
 
  fout->Write();
  fout->Close();
   
}
// determine pT_ee * eta direction region 
int pTee_Eta_Bin(double pTee_eta) {
  int bin = -1;
  if(pTee_eta >= 30) bin = -1;
  else if(pTee_eta >= 20) bin = 9;
  else if(pTee_eta >= 15) bin = 8;
  else if(pTee_eta >= 10) bin = 7;
  else if(pTee_eta >=  7) bin = 6;
  else if(pTee_eta >=  5) bin = 5;
  else if(pTee_eta >=  4) bin = 4;
  else if(pTee_eta >=  3) bin = 3;
  else if(pTee_eta >=  2) bin = 2;
  else if(pTee_eta >=  1) bin = 1;
  else bin = 0;
  return bin;
}
