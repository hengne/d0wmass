#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include <iostream>


void EfficiencyPlotZptDphi2(){

  //should be tree output from wmass program, maybe this would work better?
  //cafe wmass_analysis/config/cafe_runIIb.config.runIIb Input: ../WMASSskimRUN2B_3and4_caftrees_2EM___from_EMinclusive_PASS5_fix_84_of_84.root

  //./zeecomp  /prj_root/5007/wz2_write/jenny/cafe_newhisto/run3_ut15.root /prj_root/5007/wz2_write/jenny/pythia_zee_run2b3_default_newznunu_default_all_testtemplate2parm_ut15_test8_etflow3_ALL_plusfit_zptphirw_all_2pivarbins_test9_20130415_112117/result.root 1 3
  //./zeecomp  /prj_root/5007/wz2_write/jenny/cafe_newhisto/run3_ut30.root /prj_root/5007/wz2_write/jenny/pythia_zee_run2b3_default_newznunu_default_all_testtemplate2parm_ut30_test8_etflow3_ALL_plusfit_zptphirw_all_2pivarbins_test9_20130415_112117/result.root 1 3

  //SPECIAL RUN4 FILE
  TFile f ("/prj_root/5007/wz2_write/jenny/cafe_newhisto/run4_ut30.root");
  //  TFile f2 ("/prj_root/5007/wz2_write/jenny/pmcs_newhisto/pythia_zee_run2b3_default_newznunu_default_newphieff_v2_all_etflow3_TEST3_ut15_NORW_moreplots5_plusfit_20130418_122850/result.root");
   //TFile f2 ("/prj_root/5007/wz2_write/jenny/pmcs_newhisto/pythia_zee_run2b3_default_newznunu_default_newphieff_v2_all_etflow3_TEST3_ut30_NORW_moreplots5_plusfit_20130418_122850/result.root");
  
  // TFile f2 ("/prj_root/5007/wz2_write/jenny/pmcs_newhisto/pythia_zee_run2b3_default_newznunu_default_newphieff_ut15_nullfit_newhisto_20130417_172939/result.root");
  // TFile f2 ("/prj_root/5007/wz2_write/jenny/pmcs_newhisto/pythia_zee_run2b3_default_newznunu_default_newphieff_ut30_nullfit_newhisto_20130417_172947/result.root");

  // TFile f2 ("/prj_root/5007/wz2_write/jenny/pmcs_newhisto/pythia_zee_run2b4_default_newznunu_default_newphieff_ut15_nullfit_newhisto_20130417_172930/result.root");
  //  TFile f2 ("/prj_root/5007/wz2_write/jenny/pmcs_newhisto/pythia_zee_run2b4_default_newznunu_default_newphieff_ut30_nullfit_newhisto_20130417_172930/result.root");

  TFile f2 ("/prj_root/5007/wz2_write/jenny/pythia_zee_run2b4_default_newznunu_default_newphieff_ut30_NORW_newhisto_newfit_20130422_110712/result.root");
  //TFile f2 ("/prj_root/5007/wz2_write/jenny/pythia_zee_run2b4_default_newznunu_default_newphieff_ut15_NORW_newhisto_newfit_20130422_110712/result.root");


   // TFile f2 ("/prj_root/5007/wz2_write/jenny/pmcs_newhisto/pythia_zee_run2b3_default_newznunu_default_v2_all_etflow3_TEST3_ut15_specialrw3_moreplots4_plusfit_20130411_123958/result.root");//pythia_zee_run2b3_default_newznunu_default_v2_all_etflow3_TEST2_ut999_specialrw3_moreplots_20130409_114601/result.root");
   //  TFile f2 ("/prj_root/5007/wz2_write/jenny/pmcs_newhisto/pythia_zee_run2b3_default_newznunu_default_v2_all_etflow3_TEST3_ut30_specialrw3_moreplots4_plusfit_20130411_123958/result.root");//pythia_zee_run2b3_default_newznunu_default_v2_all_etflow3_TEST3_ut30_specialrw3_moreplots3_20130410_130822/result.root");//pythia_zee_run2b3_default_newznunu_default_v2_all_etflow3_TEST2_ut30_specialrw3_moreplots_20130409_114554/result.root");
 // TFile f2 ("/prj_root/5007/wz2_write/jenny/pmcs_newhisto/pythia_zee_run2b3_default_newznunu_default_v2_all_etflow3_TEST2_specialrw3_moreplots_20130409_114554/result.root");

 // TFile f2 ("/prj_root/5007/wz2_write/jenny/pmcs_newhisto/pythia_zee_run2b3_default_newznunu_default_v2_all_etflow3_TEST3_ut30_specialrw3_moreplots3_zptphirwplusfit_withpz_20130410_222544/result.root");

  //  TH2D *hp225 = (TH2D*)f.Get("ZCand_Hist/ZCandDeltaPhi_EM1_EM2_Zpt_CCCC");
  // TH2D *htp225 = (TH2D*)f2.Get("smeared/smeared_hZcandDeltaPhi_Zpt_CCCC");//hZcandDeltaPhi_Zpt_CCCC");


  TString lumi = "all";
  TString ut = "30";
  TString extra = "newfit";
  TString run = "run4";

    TH2D *hp225 = (TH2D*)f.Get("ZCand_Hist/ZCandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_varbin");
   TH2D *htp225 = (TH2D*)f2.Get("smeared/smeared_hZcandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_varbin");//hZcandDeltaPhi_Zpt_CCCC_v2");//hZcandDeltaPhi_Zpt_CCCC");

  //  TH2D *hp225 = (TH2D*)f.Get("ZCand_Hist/ZCandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi02_varbin");
  // TH2D *htp225 = (TH2D*)f2.Get("smeared/smeared_hZcandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi02_varbin");//hZcandDeltaPhi_Zpt_CCCC_v2");//hZcandDeltaPhi_Zpt_CCCC");

  // TH2D *hp225 = (TH2D*)f.Get("ZCand_Hist/ZCandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi24_varbin");
  //  TH2D *htp225 = (TH2D*)f2.Get("smeared/smeared_hZcandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi24_varbin");//hZcandDeltaPhi_Zpt_CCCC_v2");//hZcandDeltaPhi_Zpt_CCCC");
    
  //  TH2D *hp225 = (TH2D*)f.Get("ZCand_Hist/ZCandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi46_varbin");
  // TH2D *htp225 = (TH2D*)f2.Get("smeared/smeared_hZcandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi46_varbin");//hZcandDeltaPhi_Zpt_CCCC_v2");//hZcandDeltaPhi_Zpt_CCCC");

   // TH2D *hp225 = (TH2D*)f.Get("ZCand_Hist/ZCandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi6999_varbin");
   //  TH2D *htp225 = (TH2D*)f2.Get("smeared/smeared_hZcandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi6999_varbin");//hZcandDeltaPhi_Zpt_CCCC_v2");//hZcandDeltaPhi_Zpt_CCCC");



 TCanvas *c1 = new TCanvas("c1","c1",800,800);

  htp225->Scale(hp225->Integral()/htp225->Integral());//scale to "data"

 hp225->Draw("colz");
 gPad->Update();
c1->Update();
c1->Print("PlotEffZptDphicafe_"+run+"_ut"+ut+"_2pi_varbin_new_lumi"+lumi+"_"+extra+".eps");
c1->Print("PlotEffZptDphicafe_"+run+"_ut"+ut+"_2pi_varbin_new_lumi"+lumi+"_"+extra+".gif");

 htp225->Draw("colz");
 gPad->Update();
c1->Update();
c1->Print("PlotEffZptDphipmcs_"+run+"_ut"+ut+"_2pi_varbin_new_lumi"+lumi+"_"+extra+".eps");
c1->Print("PlotEffZptDphipmcs_"+run+"_ut"+ut+"_2pi_varbin_new_lumi"+lumi+"_"+extra+".gif");

 hp225->Divide(hp225, htp225,1.0,1.0,"B");
 // hp225->SetMaximum(2); //sets height, i.e. ratio maximum
 TCanvas *c2 = new TCanvas("c1","c1",800,800);
 hp225->Draw("colz");
 gPad->Update();
c2->Update();
c2->Print("PlotEffZptDphi_"+run+"_ut"+ut+"_2pi_varbin_new_lumi"+lumi+"_"+extra+".eps");
c2->Print("PlotEffZptDphi_"+run+"_ut"+ut+"_2pi_varbin_new_lumi"+lumi+"_"+extra+".gif");

 hp225->SetName("dphi_vs_zpt_reweight"); //NOTE: MUST CHANGE NAME TO MATCH EFFICIENCY SMEAR, L111
c2->Print("PlotEffZptDphi_"+run+"_ut"+ut+"_2pi_varbin_new_lumi"+lumi+"_"+extra+".C");

// cout<<hp225->GetMaximum()<<" "<<hp225->GetXaxis()->GetBinLowEdge(hp225->GetMaximumBin())<<" "<<hp225->GetYaxis()->GetBinLowEdge(hp225->GetMaximumBin())<<endl;
hp225->Scale(1/hp225->GetMaximum());
 hp225->Draw("colz");
gPad->Update();
c2->Update();
c2->Print("PlotEffZptDphi2_"+run+"_ut"+ut+"_2pi_varbin_new_lumi"+lumi+"_"+extra+".eps");
c2->Print("PlotEffZptDphi2_"+run+"_ut"+ut+"_2pi_varbin_new_lumi"+lumi+"_"+extra+".gif");


// hp225->SetName("dphi_vs_zpt_reweight"); //NOTE: MUST CHANGE NAME TO MATCH EFFICIENCY SMEAR, L111
//c1->Print("PlotEffZptDphi_ ut"+ut+".C");

}
