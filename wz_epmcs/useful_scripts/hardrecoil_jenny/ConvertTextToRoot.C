#include <TVector2.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile2D.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <TTree.h>
#include <TLeaf.h>

using namespace std;

void ConvertTextToRoot(){
  TFile *f = new TFile("Znunu_Znunurun_PostPMCS_Converted_AllLumi_NEW2_lumiall_zphibinsfordeltaphiandresp_46zptbins.root", "RECREATE");
  TTree *tree = new TTree("hardrecoilPMCS", "");
  // tree->ReadFile("Dump.txt", "runno:evtno:z_px:z_py:z_pz:z_E:gen_rec_px:gen_rec_py:gen_rec_pz:gen_rec_E:rec_px:rec_py:set:lumi:zbset");
  //  tree->ReadFile("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/znunu_recoil_dump_default_smear_allLumi.txt", "Ztruepx:Ztruepy:Ztruepz:ZtrueE:utruepx:utruepy:utruepz:utrueE:urecopx:urecopy:SET:lumi:ZBSET");
 tree->ReadFile("/work/rebel-clued0/jenny/Summer2013/epmcs_analysis_p21.26.00_winterconfupdates_default_bkup_rafael_COPY/wz_epmcs/src/znunu_recoil_dump_lumiall_zphibinsfordeltaphiandresp_46zptbins.txt", "Ztruepx:Ztruepy:Ztruepz:ZtrueE:utruepx:utruepy:utruepz:utrueE:urecopx:urecopy:SET:lumi:ZBSET");
  tree->Write();
  f->Close();
}
