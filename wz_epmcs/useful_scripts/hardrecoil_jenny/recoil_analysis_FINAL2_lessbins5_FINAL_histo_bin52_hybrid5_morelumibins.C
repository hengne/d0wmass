#include <TVector2.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile2D.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>

#include <fstream>
#include <iostream>
#include <vector>

#define debug 0


using namespace std;

int recoil_analysis(TString rootfile2, TString rootoutput, char* psoutput, int binz) {


  TFile* ROOTout = new TFile(rootoutput, "update");

  int theBin = -1;
  theBin = binz;

  TTree *tree(0);
  TFile *input2(0);

  if (!gSystem->AccessPathName( rootfile2 )) {
    cout << "accessing " << rootfile2 << endl;
    input2 = TFile::Open( rootfile2 );
  } 
  else{
    cout<< "problem accessing "<<rootfile2<< endl;
    exit(0);
  }
  tree = (TTree*)input2->Get("hardrecoil");

   
  double lumi, ZBSET, SET, Ztruepx, Ztruepy, Ztruepz, ZtrueE, utruepx, utruepy, utruepz, utrueE, urecopx, urecopy, urecopT, urecophi; 
  
  tree->SetBranchStatus("*", 0);
  tree->SetBranchStatus("lumi", 1);
  tree->SetBranchStatus("ZBSET", 1);
  tree->SetBranchStatus("SET", 1);
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

 int ptnbins = 52;
 double ptbins[] = {0.0, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.5, 5.0, 5.5, 6.0, 7.0, 8.0, 9.0, 
		   10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 
		    30.0, 33.0, 36.0, 39.0, 42.0, 45.0, 49.0, 55.0, 70.0, 100.0, 500.0};


double resp_bdr[] = {20., 20., 20., 20., 20., 20., 20., 15., 15., 10.,10.,10., 5., 5.,5., 5.,5.,5.,3., 3., 3., 3., 3., 3., 3., 3., 3., 3., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5};
  double dphi_bdr[] = { 1., 1.,1.,1., 1.,1.,1.,  1.,  1., 1., 1., 1., 1., 1., 1., 1.,  1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., .5, .5, .5, .5, .5, .5, .5, .5, .3, .3, .3, .3,.3,.3,.3,.3, .2, .2, .2, .2, .2, .2, .1, .1};
  
  
  int ptnbinszphi = 16;
  double ptbinszphi[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 15.0, 20.0, 30., 500.0};
  
  
  int ptnbinsset = 15;
  double ptbinsset[] = {0.0, 1.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 15.0, 20.0, 25.0, 30., 40.0, 50.0, 70.0, 500.0};
  double set_ut_bdr[]= {20., 30., 40., 40., 50., 50., 60., 60., 60., 60., 70.,70.,70., 70., 90.};
  double ut_bdr[]=    {10., 10., 15., 15.,15., 20., 20., 25., 30., 40.,40., 60.,60.,90., 200.}; //250
  
  int nentries = tree->GetEntries();
  const int n=6;
  const int n3=7;
  double twopi = 2*TMath::Pi();
  TH2D* histoRecoilResp[ptnbins][n];
  TH2D* histoZBsetResp[ptnbins][n3];
  TH2D* histoSET[ptnbinsset];
  TH2D* histoZPhiResp[ptnbinszphi];
  TProfile *myhisty[ptnbins];
  std::vector <double>  parmMean;
  std::vector <double>  parmA;
  std::vector <double>  parmB;
  std::vector <double>  parmC;
  std::vector <double>  parmD;
  
  for(int ihist=0;ihist<ptnbins;ihist++) {
    for(Int_t i=0; i<n; i++){   
      if (theBin == -1) histoRecoilResp[ihist][i] =  new TH2D(TString::Format("recoil_resp_hist_truephi%d_bin_%d", i, ihist), "",  250, 0., resp_bdr[ihist], 128, -1*dphi_bdr[ihist], dphi_bdr[ihist]);
    }
    for(Int_t i=0; i<n3; i++){   
      if (theBin == -3) histoZBsetResp[ihist][i] =  new TH2D(TString::Format("recoil_resp_zbset_hist_lumibin%d_bin_%d", i, ihist), "",  500, 0., resp_bdr[ihist], 25, 0., 25.);
    }
  }
  for(int ihist=0;ihist<ptnbinszphi;ihist++) {
    if (theBin == -4) histoZPhiResp[ihist] =  new TH2D(TString::Format("recoil_resp_zphi_hist_bin_%d", ihist),"",  500, 0., resp_bdr[ihist], 64, 0., twopi);
  }
  for(int ihist=0;ihist<ptnbinsset;ihist++) {
    if (theBin == -2) histoSET[ihist] =  new TH2D(TString::Format("set_ut_hist_bin_%d", ihist),"",  500, 0., set_ut_bdr[ihist], 500, 0., ut_bdr[ihist]);
  }
  
 for (int ient=0; ient<nentries; ient++){
   
    if (ient%1000000==0) std::cout << "Entries " << ient << "/" << nentries << std::endl;
    
    tree->GetEntry(ient);

    TVector2 z_vec(Ztruepx, Ztruepy);
    TVector2 rec_vec(urecopx, urecopy);
    TVector2 utrue_vec(utruepx, utruepy);
    
    int ptbin = -1;
    if (theBin == -1 || theBin == -3) {
      for (int i=0; i<ptnbins; i++) {
	if (z_vec.Mod() > ptbins[i])
	  ptbin++;
	else
	  break;
      }
      if (ptbin > ptnbins-1 || ptbin < 0) continue;
    }
    
    if(theBin == -2){
      for (int i=0; i<ptnbinsset; i++) {
	if (z_vec.Mod() > ptbinsset[i])
	  ptbin++;
	else
	  break;
      }
      if (ptbin > ptnbinsset-1 || ptbin < 0) continue;
    }
    if(theBin == -4){
      for (int i=0; i<ptnbinszphi; i++) {
	if (z_vec.Mod() > ptbinszphi[i])
	  ptbin++;
	else
	  break;
      }
      if (ptbin > ptnbinszphi-1 || ptbin < 0) continue;
    }

    // Sets the variables
    double ZBset, resp, dphi_norm, zphi, set_ut, ut;
    ZBset = TMath::Sqrt(ZBSET);
    resp = rec_vec.Mod()/z_vec.Mod();
    dphi_norm = rec_vec.DeltaPhi(utrue_vec)/TMath::Pi(); 
    zphi = TVector2::Phi_0_2pi(utrue_vec.Phi());
    set_ut = SET - rec_vec.Mod();
    ut = rec_vec.Mod();
   

    if (theBin == -1) {
      if (zphi>=0.&&zphi<1.) histoRecoilResp[ptbin][0]->Fill(resp, dphi_norm);
      if (zphi>=1.&&zphi<2.) histoRecoilResp[ptbin][1]->Fill(resp, dphi_norm);
      if (zphi>=2.&&zphi<3.) histoRecoilResp[ptbin][2]->Fill(resp, dphi_norm);
      if (zphi>=3.&&zphi<4.) histoRecoilResp[ptbin][3]->Fill(resp, dphi_norm);
      if (zphi>=4.&&zphi<5.) histoRecoilResp[ptbin][4]->Fill(resp, dphi_norm);
      if (zphi>=5.&&zphi<7.) histoRecoilResp[ptbin][5]->Fill(resp, dphi_norm);
    }
    if (theBin == -3) {
      if (lumi>=0.&&lumi<2.) histoZBsetResp[ptbin][0]->Fill(resp, ZBset);
      if (lumi>=2.&&lumi<3.) histoZBsetResp[ptbin][1]->Fill(resp, ZBset);
      if (lumi>=3.&&lumi<4.) histoZBsetResp[ptbin][2]->Fill(resp, ZBset);
      if (lumi>=4.&&lumi<5.) histoZBsetResp[ptbin][3]->Fill(resp, ZBset);
      if (lumi>=5.&&lumi<6.) histoZBsetResp[ptbin][4]->Fill(resp, ZBset);
      if (lumi>=6.&&lumi<8.) histoZBsetResp[ptbin][5]->Fill(resp, ZBset);
      if (lumi>=8.) histoZBsetResp[ptbin][6]->Fill(resp, ZBset);
    }
    if (theBin == -4) {
      histoZPhiResp[ptbin]->Fill(resp, zphi);
    }
    if (theBin == -2) {
      histoSET[ptbin]->Fill(set_ut, ut);
    }
 }
  
  
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(1,0);
  TCanvas* c1 = new TCanvas("c1","c1");
  c1->Print(TString::Format("%s[", psoutput));

  
   parmMean.clear();
   parmA.clear();
   parmB.clear();
   parmC.clear();
   parmD.clear();

  for(int ihist=0;ihist<ptnbins;ihist++) {
    for(Int_t i=0; i<n; i++){   
      if (theBin == -1){
	if(ihist<20) histoRecoilResp[ihist][i]->Smooth(1);
	histoRecoilResp[ihist][i]->SetName(TString::Format("recoil_resp_hist_truephi%d_bin_%d", i, ihist));
	histoRecoilResp[ihist][i]->SetTitle(TString::Format("recoil_resp_hist_truephi%d_bin_%d", i, ihist));      
	double integral = histoRecoilResp[ihist][i]->Integral();
	histoRecoilResp[ihist][i]->Scale(1/integral);
      }
    }
    for(Int_t i=0; i<n3; i++){   
      if (theBin == -3){
	histoZBsetResp[ihist][i]->Smooth(1);
	histoZBsetResp[ihist][i]->SetName(TString::Format("recoil_resp_zbset_hist_lumibin%d_bin_%d", i, ihist));
	histoZBsetResp[ihist][i]->SetTitle(TString::Format("recoil_resp_zbset_hist_lumibin%d_bin_%d", i, ihist));      
	double integral = histoZBsetResp[ihist][i]->Integral();
	histoZBsetResp[ihist][i]->Scale(1/integral);
      }
    }
  }
  for(int ihist=0;ihist<ptnbinszphi;ihist++) {
    if (theBin == -4){
      myhisty[ihist] = histoZPhiResp[ihist]->ProfileY();
      myhisty[ihist]->SetName(TString::Format("recoil_resp_zphi_hist_bin_%d", ihist));
      myhisty[ihist]->SetTitle(TString::Format("recoil_resp_zphi_hist_bin_%d", ihist));      
     
    }
  }
 for(int ihist=0;ihist<ptnbinsset;ihist++) {
    if (theBin == -2){
      // histoSET[ihist]->Smooth(1);
      histoSET[ihist]->SetName(TString::Format("set_ut_hist_bin_%d", ihist));
      histoSET[ihist]->SetTitle(TString::Format("set_ut_hist_bin_%d", ihist));      
      double integral =  histoSET[ihist]->Integral();
      histoSET[ihist]->Scale(1/integral);
    }
    
  } 
  ROOTout->cd();
  for(int ihist=0;ihist<ptnbins;ihist++) {
    for(Int_t i=0; i<n; i++){   
      if (theBin == -1){
	histoRecoilResp[ihist][i]->Write(TString::Format("recoil_resp_hist_truephi%d_bin_%d", i, ihist),TObject::kOverwrite);
	histoRecoilResp[ihist][i]->Draw("colz");      
	c1->Print(psoutput);
      }
    }
    for(Int_t i=0; i<n3; i++){   
      if (theBin == -3){
	histoZBsetResp[ihist][i]->Write(TString::Format("recoil_resp_zbset_hist_lumibin%d_bin_%d", i, ihist),TObject::kOverwrite);
	histoZBsetResp[ihist][i]->Draw("colz");      
	c1->Print(psoutput);
      }
    }
  }
  for(int ihist=0;ihist<ptnbinszphi;ihist++) {
    if (theBin == -4){     
      TF1 *pol3 = new TF1("pol3", "pol3");
      myhisty[ihist]->Fit("pol3");
      double stats[7];
      myhisty[ihist]->GetStats(stats); 
      parmMean.push_back(myhisty[ihist]->GetMean(2));
      parmA.push_back(pol3->GetParameter(0));
      parmB.push_back(pol3->GetParameter(1));
      parmC.push_back(pol3->GetParameter(2));
      parmD.push_back(pol3->GetParameter(3));
      myhisty[ihist]->Draw("");      
      c1->Print(psoutput);
      cout<<"HardRecoil_zphiresp_Mean:       ";
      for (int i=0; i<ptnbinszphi-1; i++) {
	cout<<parmMean[i]<<" ";
      }
      cout<<parmMean[ptnbinszphi-1]<<endl;;
      
      cout<<"HardRecoil_zphiresp_ParameterA: ";
      for (int i=0; i<ptnbinszphi-1; i++) {
	cout<<parmA[i]<<" ";
      }
      cout<<parmA[ptnbinszphi-1]<<endl;;
      
      cout<<"HardRecoil_zphiresp_ParameterB: ";
      for (int i=0; i<ptnbinszphi-1; i++) {
	cout<<parmB[i]<<" ";
      }
      cout<<parmB[ptnbinszphi-1]<<endl;;
      
      cout<<"HardRecoil_zphiresp_ParameterC: ";
      for (int i=0; i<ptnbinszphi-1; i++) {
	cout<<parmC[i]<<" ";
      }
      cout<<parmC[ptnbinszphi-1]<<endl;;
      
      cout<<"HardRecoil_zphiresp_ParameterD: ";
      for (int i=0; i<ptnbinszphi-1; i++) {
	cout<<parmD[i]<<" ";
      }
      cout<<parmD[ptnbinszphi-1]<<endl;
      
      
    }
  }
for(int ihist=0;ihist<ptnbinsset;ihist++) {
    if (theBin == -2){
      histoSET[ihist]->Write(TString::Format("set_ut_hist_bin_%d", ihist),TObject::kOverwrite);
      histoSET[ihist]->Draw("colz");      
      c1->Print(psoutput);
    }
    
  }

  

  c1->Print(TString::Format("%s]", psoutput));

  ROOTout->Close();

  return(0);
}
int recoil_analysis_FINAL2_lessbins5_FINAL_histo_bin52_hybrid5_morelumibins(){
  
  //NOTE: Throughout this code, recoil manager, and other recoil processing scripts, zphi and true recoil phi are used interchangably.  
  //However, we always mean true recoil phi for applications that are used in PMCS.
  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__3_v3_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run3_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run3_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_4.ps", -4);
  //  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__4_v3_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run4_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run4_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_4.ps", -4);
  //  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__3_v3_hvloss_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run3_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run3_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_4.ps", -4);
  //  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__4_v3_hvloss_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run4_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run4_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_4.ps", -4);
 
  /**
  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__3_v3_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run3_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run3_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_1.ps", -1);
    recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__3_v3_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run3_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run3_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_2.ps", -2);
  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__3_v3_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run3_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run3_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_3.ps", -3);
 
  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__4_v3_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run4_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run4_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_1.ps", -1);
  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__4_v3_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run4_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run4_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_2.ps", -2);
  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__4_v3_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run4_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run4_ALL_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_3.ps", -3);
 

 recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__3_v3_hvloss_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run3_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run3_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_1.ps", -1);
    recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__3_v3_hvloss_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run3_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run3_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_2.ps", -2);
  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__3_v3_hvloss_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run3_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run3_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_3.ps", -3);
 
 recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__4_v3_hvloss_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run4_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run4_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_1.ps", -1);
    recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__4_v3_hvloss_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run4_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run4_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_2.ps", -2);
  recoil_analysis("/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/FinalFiles/znunu_newkillcell__4_v3_hvloss_ALL.root", "/prj_root/7055/wmass2/jenny/hrlib/Znunu_RCLSA_newkillcell__Run4_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST.root", "/work/rebel-clued0/jenny/Summer2013/files_for_hard_recoil_model/Znunu_RCLSA_newkillcell__Run4_ALL_HVLOSS_Morept4_model_RooNDKeysPdf_52bin_HYBRID5_MORELUMIBINS_0kde_NEW_HIST_3.ps", -3);
  **/



  return(0);
}

