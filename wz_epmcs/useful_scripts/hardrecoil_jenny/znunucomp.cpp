#include <iostream>
#include <fstream>
#include <TApplication.h>
#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TPostScript.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TProfile.h>
#include <TGraphErrors.h>
#include <vector>
#include "plot_util.cpp"

using namespace std;
using namespace plot;

// add standard generated Z properties plots !!!

// smeared recoil UT bins
vector<TH1 *>     
    GenZPt_Cuts_bin[2],
    GenZPhi_Cuts_bin[2],
    GenVtxZ_Cuts_bin[2],
    RecoilPt_Cuts_bin[2],
    RecoilPx_Cuts_bin[2],
    RecoilPy_Cuts_bin[2],
    RecoilPhi_Cuts_bin[2],
    RecoilResolution_Cuts_bin[2],
    DeltaPhi_genZ_Recoil_Cuts_bin[2],
    Met_Cuts_bin[2],
    MetPhi_Cuts_bin[2],
    MetX_Cuts_bin[2],
    MetY_Cuts_bin[2],
    ScalarEt_Cuts_bin[2];

    // generator PT(Z) bins
vector<TH1 *>     
    GenZPt_Cuts_genZPtBin[2],
    GenZPhi_Cuts_genZPtBin[2],
    GenVtxZ_Cuts_genZPtBin[2],
    RecoilPt_Cuts_genZPtBin[2],
    RecoilPx_Cuts_genZPtBin[2],
    RecoilPy_Cuts_genZPtBin[2],
    RecoilPhi_Cuts_genZPtBin[2],
    RecoilResolution_Cuts_genZPtBin[2],
    DeltaPhi_genZ_Recoil_Cuts_genZPtBin[2],
    Met_Cuts_genZPtBin[2],
    MetX_Cuts_genZPtBin[2],
    MetY_Cuts_genZPtBin[2],
    MetPhi_Cuts_genZPtBin[2],
    ScalarEt_Cuts_genZPtBin[2];

    // generator Phi(Z) bins
vector<TH1 *>     
    GenZPt_Cuts_genZPhiBin[2],
    GenZPhi_Cuts_genZPhiBin[2],
    GenVtxZ_Cuts_genZPhiBin[2],
    RecoilPt_Cuts_genZPhiBin[2],
    RecoilPx_Cuts_genZPhiBin[2],
    RecoilPy_Cuts_genZPhiBin[2],
    RecoilPhi_Cuts_genZPhiBin[2],
    RecoilResolution_Cuts_genZPhiBin[2],
    DeltaPhi_genZ_Recoil_Cuts_genZPhiBin[2],
    Met_Cuts_genZPhiBin[2],
    MetX_Cuts_genZPhiBin[2],
    MetY_Cuts_genZPhiBin[2],
    MetPhi_Cuts_genZPhiBin[2],
    ScalarEt_Cuts_genZPhiBin[2];

    // generator PT(Z) bins
vector<TH1 *>     
    GenZPt_Cuts_UPhiBin[2],
    GenZPhi_Cuts_UPhiBin[2],
    GenVtxZ_Cuts_UPhiBin[2],
    RecoilPt_Cuts_UPhiBin[2],
    RecoilPx_Cuts_UPhiBin[2],
    RecoilPy_Cuts_UPhiBin[2],
    RecoilPhi_Cuts_UPhiBin[2],
    RecoilResolution_Cuts_UPhiBin[2],
    DeltaPhi_genZ_Recoil_Cuts_UPhiBin[2],
    Met_Cuts_UPhiBin[2],
    MetX_Cuts_UPhiBin[2],
    MetY_Cuts_UPhiBin[2],
    MetPhi_Cuts_UPhiBin[2],
    ScalarEt_Cuts_UPhiBin[2];


    // generator PT(Z) bins
vector<TH1 *>     
    GenZPt_Cuts_lumiBin[2],
    GenZPhi_Cuts_lumiBin[2],
    GenVtxZ_Cuts_lumiBin[2],
    RecoilPt_Cuts_lumiBin[2],
    RecoilPx_Cuts_lumiBin[2],
    RecoilPy_Cuts_lumiBin[2],
    RecoilPhi_Cuts_lumiBin[2],
    RecoilResolution_Cuts_lumiBin[2],
    DeltaPhi_genZ_Recoil_Cuts_lumiBin[2],
    Met_Cuts_lumiBin[2],
    MetX_Cuts_lumiBin[2],
    MetY_Cuts_lumiBin[2],
    MetPhi_Cuts_lumiBin[2],
    ScalarEt_Cuts_lumiBin[2];

    // generator PT(Z) bins
vector<TH1 *>     
    GenZPt_Cuts_zbsetBin[2],
    GenZPhi_Cuts_zbsetBin[2],
    GenVtxZ_Cuts_zbsetBin[2],
    RecoilPt_Cuts_zbsetBin[2],
    RecoilPx_Cuts_zbsetBin[2],
    RecoilPy_Cuts_zbsetBin[2],
    RecoilPhi_Cuts_zbsetBin[2],
    RecoilResolution_Cuts_zbsetBin[2],
    DeltaPhi_genZ_Recoil_Cuts_zbsetBin[2],
    Met_Cuts_zbsetBin[2],
    MetX_Cuts_zbsetBin[2],
    MetY_Cuts_zbsetBin[2],
    MetPhi_Cuts_zbsetBin[2],
    ScalarEt_Cuts_zbsetBin[2];

  // for all regions
vector<TH1 *>      
    GenZPt_Cuts[2],
    GenZPhi_Cuts[2],
    GenVtxZ_Cuts[2],
    RecoilPt_Cuts[2],
    RecoilPx_Cuts[2],
    RecoilPy_Cuts[2],
    RecoilPhi_Cuts[2],
    RecoilResolution_Cuts[2],
    DeltaPhi_genZ_Recoil_Cuts[2],
    Met_Cuts[2],
    MetX_Cuts[2],
    MetY_Cuts[2],
    MetPhi_Cuts[2],
    ScalarEt_Cuts[2];
  
  // profile histograms
vector<TH1 *> 
  RecoilResponse_V_Recoilt_Cuts[2],
  RecoilResponse_V_genZPt_Cuts[2],
  RecoilResponseProjection_V_RecoilPt_Cuts[2],
  RecoilResponseProjection_V_genZPt_Cuts[2],
  
  RecoilResponse_V_RecoilPhi_Cuts[2],
  RecoilResponse_V_genZPhi_Cuts[2],
  RecoilResponse_V_lumi_Cuts[2],
  RecoilResponse_V_zbset_Cuts[2];

void getHistogramsFromFile(TFile *f, int index, bool is_fullMC);

// main function
int main(int argc, char** argv){

  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  TPostScript *ps = new TPostScript("histogramsznunu.ps");
  TFile *znunucomp = new TFile("znunucomp.root", "recreate");
  TCanvas *c1 =  new TCanvas("aaa","c1",50,10,700,800);   // these 2 crazy lines are needed
  ps->NewPage();                                          // for proper alignment of the 1st page

  TString data_file = argv[1];
  TString mc_file = argv[2];

  //DATA/MC PLOTS
  TFile *fdata = new TFile(data_file, "OLD"); // first file (index=0 in getHistogramsFromFile)
  TFile *fpmcs = new TFile(mc_file, "OLD");   // second file (index=1 in getHistogramsFromFile)
  if(!fdata || !fpmcs) {
    cout << "Can't open first and/or second file !!!" << endl;
    if(fdata) fdata->Close();
    if(fpmcs) fpmcs->Close();
    return 1;
  }

  if(argc!=5 && argc!=6) {
    cout<<" Please run it the following way: "
	<<" ./znunucomp  <first_root_file_name>  <second_root_file_name>  <make_chi2_option>  <compare_option>  [rows_per_page]" 
	<< endl <<endl
	<<" If <make_chi2_option>=1 then CHI plots will be created too."<<endl
	<<" Use <compare_option>=0  for comparing Full-MC (GEANT) with Fast-MC (PMCS)," << endl
        <<"     <compare_option>=1  for comparing Full-MC (GEANT) with Full-MC (GEANT)," << endl
	<<"     <compare_option>=2  for comparing Fast-MC (PMCS) with Fast-MC (PMCS)." << endl << endl;
    return 1;
  }

  // make chi2 plot
  int chi2_option = atoi(argv[3]);
  bool make_chi2 = false;
  if(chi2_option>0) make_chi2 = true;

  // make compare option
  int compare_option = atoi(argv[4]);
  switch(compare_option) {
  case 0:   // 0 for full MC - fast MC 
    set_DATA_label("FULL MC");      // first file, upper label
    set_MC_label("FAST MC");        // second file, bottom label
    if(!(fdata->cd("ZNuNuCand_Hist") && fpmcs->cd("default"))){
      cout<<" ==> compare option = 0, Are you comparing FULL-MC to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromFile(fdata, 0, true); // will assume the first file is FULL MC
    getHistogramsFromFile(fpmcs, 1, false);// will assume the second file is PMCS
    cout<<" Red histogram for the first file (FULL MC), Blue histogram for the second file (PMCS)"<<endl;
    break;
  case 1:    // 1 for full MC - full MC 
    set_DATA_label("FULL MC #1");   // first file, upper label
    set_MC_label("FULL MC #2");     // second file, bottom label
    if(!(fdata->cd("ZNuNuCand_Hist") && fpmcs->cd("ZNuNuCand_Hist"))){
      cout<<" ==> compare option = 1, Are you comparing FULL-MC to FULL-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromFile(fdata, 0, true);// will assume the first file is FULL MC
    getHistogramsFromFile(fpmcs, 1, true);// will assume the second file is FULL MC
    cout<<" Red histogram for the first FULL MC file, Blue histogram for the second FULL MC file"<<endl;    
    break;
  case 2:    // 2 for fast MC - fast MC 
    set_DATA_label("FAST MC #1");   // first file, upper label
    set_MC_label("FAST MC #2");     // second file, bottom label
    if(!(fdata->cd("default") && fpmcs->cd("default"))){
      cout<<" ==> compare option = 2, Are you comparing FAST-MC to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromFile(fdata, 0, false);// will assume the first file is PMCS
    getHistogramsFromFile(fpmcs, 1, false);// will assume the second file is PMCS
    cout<<" Red histogram for the first PMCS file, Blue histogram for the second PMCS file"<<endl;
    break;
  default:  // UNKNOWN
    cout<<"Wrong <compare_option>="<<compare_option<<" !!!"<<endl;
    if(fdata) fdata->Close();
    if(fpmcs) fpmcs->Close();
    return 1;
  };

  // max plots/page
  int plots_per_page = 10;
  if(argc==6 && atoi(argv[5])>0) plots_per_page=atoi(argv[5]);

  ////////////////////////////////////////////////////////////////////////////
  typedef struct {
    char *cname;
    vector<TH1 *> *vect;
  } canvas_t;
  canvas_t plot[]= {
    {"ZNuNu_genZPt_Cuts", GenZPt_Cuts},
    {"ZNuNu_genZPt_Cuts_bin", GenZPt_Cuts_bin},
    {"ZNuNu_genZPt_Cuts_genZPtBin", GenZPt_Cuts_genZPtBin},
{"ZNuNu_genZPt_Cuts_genZPhiBin", GenZPt_Cuts_genZPhiBin},
{"ZNuNu_genZPt_Cuts_UPhiBin", GenZPt_Cuts_UPhiBin},
{"ZNuNu_genZPt_Cuts_lumiBin", GenZPt_Cuts_lumiBin},
{"ZNuNu_genZPt_Cuts_zbsetBin", GenZPt_Cuts_zbsetBin},
    {"ZNuNu_genZPhi_Cuts", GenZPhi_Cuts},
    {"ZNuNu_genZPhi_Cuts_bin", GenZPhi_Cuts_bin},
    {"ZNuNu_genZPhi_Cuts_genZPtBin", GenZPhi_Cuts_genZPtBin},
{"ZNuNu_genZPhi_Cuts_genZPhiBin", GenZPhi_Cuts_genZPhiBin},
{"ZNuNu_genZPhi_Cuts_UPhiBin", GenZPhi_Cuts_UPhiBin},
{"ZNuNu_genZPhi_Cuts_lumiBin", GenZPhi_Cuts_lumiBin},
{"ZNuNu_genZPhi_Cuts_zbsetBin", GenZPhi_Cuts_zbsetBin},
    {"ZNuNu_genVtxZ_Cuts", GenVtxZ_Cuts},
    {"ZNuNu_genVtxZ_Cuts_bin", GenVtxZ_Cuts_bin},
    {"ZNuNu_genVtxZ_Cuts_genZPtBin", GenVtxZ_Cuts_genZPtBin},
    {"ZNuNu_RecoilPt_Cuts", RecoilPt_Cuts},
    {"ZNuNu_RecoilPt_Cuts_bin", RecoilPt_Cuts_bin},
    {"ZNuNu_RecoilPt_Cuts_genZPtBin", RecoilPt_Cuts_genZPtBin},
{"ZNuNu_RecoilPt_Cuts_genZPhiBin", RecoilPt_Cuts_genZPhiBin},
{"ZNuNu_RecoilPt_Cuts_UPhiBin", RecoilPt_Cuts_UPhiBin},
{"ZNuNu_RecoilPt_Cuts_lumiBin", RecoilPt_Cuts_lumiBin},
{"ZNuNu_RecoilPt_Cuts_zbsetBin", RecoilPt_Cuts_zbsetBin},
    {"ZNuNu_RecoilPx_Cuts", RecoilPx_Cuts},
    {"ZNuNu_RecoilPx_Cuts_bin", RecoilPx_Cuts_bin},
    {"ZNuNu_RecoilPx_Cuts_genZPtBin", RecoilPx_Cuts_genZPtBin},
{"ZNuNu_RecoilPx_Cuts_genZPhiBin", RecoilPx_Cuts_genZPhiBin},
{"ZNuNu_RecoilPx_Cuts_UPhiBin", RecoilPx_Cuts_UPhiBin},
{"ZNuNu_RecoilPx_Cuts_lumiBin", RecoilPx_Cuts_lumiBin},
{"ZNuNu_RecoilPx_Cuts_zbsetBin", RecoilPx_Cuts_zbsetBin},
    {"ZNuNu_RecoilPy_Cuts", RecoilPy_Cuts},
    {"ZNuNu_RecoilPy_Cuts_bin", RecoilPy_Cuts_bin},
    {"ZNuNu_RecoilPy_Cuts_genZPtBin", RecoilPy_Cuts_genZPtBin},
{"ZNuNu_RecoilPy_Cuts_genZPhiBin", RecoilPy_Cuts_genZPhiBin},
{"ZNuNu_RecoilPy_Cuts_UPhiBin", RecoilPy_Cuts_UPhiBin},
{"ZNuNu_RecoilPy_Cuts_lumiBin", RecoilPy_Cuts_lumiBin},
{"ZNuNu_RecoilPy_Cuts_zbsetBin", RecoilPy_Cuts_zbsetBin},
    {"ZNuNu_RecoilPhi_Cuts", RecoilPhi_Cuts},
    {"ZNuNu_RecoilPhi_Cuts_bin", RecoilPhi_Cuts_bin},
    {"ZNuNu_RecoilPhi_Cuts_genZPtBin", RecoilPhi_Cuts_genZPtBin},
{"ZNuNu_RecoilPhi_Cuts_genZPhiBin", RecoilPhi_Cuts_genZPhiBin},
{"ZNuNu_RecoilPhi_Cuts_UPhiBin", RecoilPhi_Cuts_UPhiBin},
{"ZNuNu_RecoilPhi_Cuts_lumiBin", RecoilPhi_Cuts_lumiBin},
{"ZNuNu_RecoilPhi_Cuts_zbsetBin", RecoilPhi_Cuts_zbsetBin},
    {"ZNuNu_RecoilResolution_Cuts", RecoilResolution_Cuts},
    {"ZNuNu_RecoilResolution_Cuts_bin", RecoilResolution_Cuts_bin},
    {"ZNuNu_RecoilResolution_Cuts_genZPtBin", RecoilResolution_Cuts_genZPtBin},
{"ZNuNu_RecoilResolution_Cuts_genZPhiBin", RecoilResolution_Cuts_genZPhiBin},
{"ZNuNu_RecoilResolution_Cuts_UPhiBin", RecoilResolution_Cuts_UPhiBin},
{"ZNuNu_RecoilResolution_Cuts_lumiBin", RecoilResolution_Cuts_lumiBin},
{"ZNuNu_RecoilResolution_Cuts_zbsetBin", RecoilResolution_Cuts_zbsetBin},
    {"ZNuNu_DeltaPhi_genZ_Recoil_Cuts", DeltaPhi_genZ_Recoil_Cuts},
    {"ZNuNu_DeltaPhi_genZ_Recoil_Cuts_bin", DeltaPhi_genZ_Recoil_Cuts_bin},
    {"ZNuNu_DeltaPhi_genZ_Recoil_Cuts_genZPtBin", DeltaPhi_genZ_Recoil_Cuts_genZPtBin},
{"ZNuNu_DeltaPhi_genZ_Recoil_Cuts_genZPhiBin", DeltaPhi_genZ_Recoil_Cuts_genZPhiBin},
{"ZNuNu_DeltaPhi_genZ_Recoil_Cuts_UPhiBin", DeltaPhi_genZ_Recoil_Cuts_UPhiBin},
{"ZNuNu_DeltaPhi_genZ_Recoil_Cuts_lumiBin", DeltaPhi_genZ_Recoil_Cuts_lumiBin},
{"ZNuNu_DeltaPhi_genZ_Recoil_Cuts_zbsetBin", DeltaPhi_genZ_Recoil_Cuts_zbsetBin},
    {"ZNuNu_Met_Cuts", Met_Cuts},
    {"ZNuNu_Met_Cuts_bin", Met_Cuts_bin},
    {"ZNuNu_Met_Cuts_genZPtBin", Met_Cuts_genZPtBin},
{"ZNuNu_Met_Cuts_genZPhiBin", Met_Cuts_genZPhiBin},
{"ZNuNu_Met_Cuts_UPhiBin", Met_Cuts_UPhiBin},
{"ZNuNu_Met_Cuts_lumiBin", Met_Cuts_lumiBin},
{"ZNuNu_Met_Cuts_zbsetBin", Met_Cuts_zbsetBin},
    {"ZNuNu_MetPhi_Cuts", MetPhi_Cuts},
    {"ZNuNu_MetPhi_Cuts_bin", MetPhi_Cuts_bin},
    {"ZNuNu_MetPhi_Cuts_genZPtBin", MetPhi_Cuts_genZPtBin},
{"ZNuNu_MetPhi_Cuts_genZPhiBin", MetPhi_Cuts_genZPhiBin},
{"ZNuNu_MetPhi_Cuts_UPhiBin", MetPhi_Cuts_UPhiBin},
{"ZNuNu_MetPhi_Cuts_lumiBin", MetPhi_Cuts_lumiBin},
{"ZNuNu_MetPhi_Cuts_zbsetBin", MetPhi_Cuts_zbsetBin},
    {"ZNuNu_MetX_Cuts", MetX_Cuts},
    {"ZNuNu_MetX_Cuts_bin", MetX_Cuts_bin},
    {"ZNuNu_MetX_Cuts_genZPtBin", MetX_Cuts_genZPtBin},
{"ZNuNu_MetX_Cuts_genZPhiBin", MetX_Cuts_genZPhiBin},
{"ZNuNu_MetX_Cuts_UPhiBin", MetX_Cuts_UPhiBin},
{"ZNuNu_MetX_Cuts_lumiBin", MetX_Cuts_lumiBin},
{"ZNuNu_MetX_Cuts_zbsetBin", MetX_Cuts_zbsetBin},
    {"ZNuNu_MetY_Cuts", MetY_Cuts},
    {"ZNuNu_MetY_Cuts_bin", MetY_Cuts_bin},
    {"ZNuNu_MetY_Cuts_genZPtBin", MetY_Cuts_genZPtBin},
{"ZNuNu_MetY_Cuts_genZPhiBin", MetY_Cuts_genZPhiBin},
{"ZNuNu_MetY_Cuts_UPhiBin", MetY_Cuts_UPhiBin},
{"ZNuNu_MetY_Cuts_lumiBin", MetY_Cuts_lumiBin},
{"ZNuNu_MetY_Cuts_zbsetBin", MetY_Cuts_zbsetBin},
    {"ZNuNu_ScalarEt_Cuts", ScalarEt_Cuts},
    {"ZNuNu_ScalarEt_Cuts_bin", ScalarEt_Cuts_bin},
    {"ZNuNu_ScalarEt_Cuts_genZPtBin", ScalarEt_Cuts_genZPtBin},
{"ZNuNu_ScalarEt_Cuts_genZPhiBin", ScalarEt_Cuts_genZPhiBin},
{"ZNuNu_ScalarEt_Cuts_UPhiBin", ScalarEt_Cuts_UPhiBin},
{"ZNuNu_ScalarEt_Cuts_lumiBin", ScalarEt_Cuts_lumiBin},
{"ZNuNu_ScalarEt_Cuts_zbsetBin", ScalarEt_Cuts_zbsetBin},
    {"ZNuNu_RecoilResponse_V_RecoilPt_Cuts", RecoilResponse_V_Recoilt_Cuts},
    {"ZNuNu_RecoilResponse_V_genZPt_Cuts", RecoilResponse_V_genZPt_Cuts},
    {"ZNuNu_RecoilResponseProjection_V_RecoilPt_Cuts", RecoilResponseProjection_V_RecoilPt_Cuts},
    {"ZNuNu_RecoilResponseProjection_V_genZPt_Cuts", RecoilResponseProjection_V_genZPt_Cuts},
    {"ZNuNu_RecoilResponse_V_RecoilPhi_Cuts", RecoilResponse_V_RecoilPhi_Cuts},
    {"ZNuNu_RecoilResponse_V_genZPhi_Cuts", RecoilResponse_V_genZPhi_Cuts},
    {"ZNuNu_RecoilResponse_V_lumi_Cuts",RecoilResponse_V_lumi_Cuts},
    {"ZNuNu_RecoilResponse_V_zbset_Cuts", RecoilResponse_V_zbset_Cuts}
  };
  const int nplots=sizeof(plot)/sizeof(canvas_t);
  // plot::plot_util() now operates on copies of input histograms
  // and it does not scale the originals. 
  for(int iplot=0; iplot<nplots; iplot++) {
    plot_util(plot[iplot].cname, (plot[iplot].vect)[0], (plot[iplot].vect)[1], make_chi2, -1E30, 1E30, ps, plots_per_page, znunucomp );
  }
  ////////////////////////////////////////////////////////////////////////////
 
  ps->Close();
  znunucomp->Write("All");
  znunucomp->Close();
}

void getHistogramsFromFile(TFile *f, int index, bool is_fullMC) {
  if(is_fullMC) f->cd("ZNuNuCand_Hist");  // Full MC file
  else          f->cd("default");         // PMCS file

  // histograms with '_genZPtBin_<N>' suffixes are for true PT(Z) bins 
  // histograms with '_bin_<N>' suffixes are for smeared recoil UT bins 
  char name[50];
  for(int i=0; i<10; i++) {

    // smeared recoil UT bins
    sprintf(name, "%s%d", "ZNuNu_genZPt_Cuts_bin_", i);
    GenZPt_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));
 
    sprintf(name, "%s%d", "ZNuNu_genZPhi_Cuts_bin_", i);
    GenZPhi_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_genVtxZ_Cuts_bin_", i);
    GenVtxZ_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_RecoilPt_Cuts_bin_", i);
    RecoilPt_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_RecoilPx_Cuts_bin_", i);
    RecoilPx_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_RecoilPy_Cuts_bin_", i);
    RecoilPy_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_RecoilPhi_Cuts_bin_", i);
    RecoilPhi_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%d", "ZNuNu_RecoilResolution_Cuts_bin_", i);
    RecoilResolution_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_bin_", i);
    DeltaPhi_genZ_Recoil_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_Met_Cuts_bin_", i);
    Met_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_MetPhi_Cuts_bin_", i);
    MetPhi_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_MetX_Cuts_bin_", i);
    MetX_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_MetY_Cuts_bin_", i);
    MetY_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZNuNu_ScalarEt_Cuts_bin_", i);
    ScalarEt_Cuts_bin[index].push_back((TH1 *)gROOT->FindObject(name));

    // generator PT(Z) bins
    TH1 *h;

    if( (sprintf(name, "ZNuNu_genZPt_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_genZPt_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) ||
	(sprintf(name, "ZNuNu_genZPt_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      )  
      GenZPt_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_genZPhi_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_genZPhi_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_genZPhi_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      ) 
      GenZPhi_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_genVtxZ_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_genVtxZ_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))|| 
	(sprintf(name, "ZNuNu_genVtxZ_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))     ) 
      GenVtxZ_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_RecoilPt_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPt_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_RecoilPt_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      ) 
      RecoilPt_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_RecoilPx_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPx_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_RecoilPx_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      )
      RecoilPx_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_RecoilPy_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPy_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) ||
	(sprintf(name, "ZNuNu_RecoilPy_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      )
      RecoilPy_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_RecoilPhi_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPhi_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_RecoilPhi_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      ) 
      RecoilPhi_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_RecoilResolution_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_RecoilResolution_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_RecoilResolution_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      )
      RecoilResolution_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  || 
        (sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) ||
	(sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      ) 
      DeltaPhi_genZ_Recoil_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_Met_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_Met_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_Met_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      ) 
      Met_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_MetX_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_MetX_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_MetX_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      ) 
      MetX_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_MetY_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_MetY_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_MetY_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      )
      MetY_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_MetPhi_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_MetPhi_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_MetPhi_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      ) 
      MetPhi_Cuts_genZPtBin[index].push_back(h);

    if( (sprintf(name, "ZNuNu_ScalarEt_Cuts_genZPtBin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_ScalarEt_Cuts_genZPt_bin_%d", i) && (h=(TH1 *)gROOT->FindObject(name))) || 
	(sprintf(name, "ZNuNu_ScalarEt_Cuts_genZbin_%d", i) && (h=(TH1 *)gROOT->FindObject(name)))      ) 
      ScalarEt_Cuts_genZPtBin[index].push_back(h);
  

    // generator Phi(Z) bins
    TH1 *h2;

    if( (sprintf(name, "ZNuNu_genZPt_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_genZPt_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  )  
      GenZPt_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_genZPhi_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_genZPhi_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))   ) 
      GenZPhi_Cuts_genZPhiBin[index].push_back(h2);

   
    if( (sprintf(name, "ZNuNu_RecoilPt_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPt_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  ) 
      RecoilPt_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_RecoilPx_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPx_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  )
      RecoilPx_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_RecoilPy_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPy_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  )
      RecoilPy_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_RecoilPhi_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPhi_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))   ) 
      RecoilPhi_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_RecoilResolution_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_RecoilResolution_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  )
      RecoilResolution_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  || 
        (sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  ) 
      DeltaPhi_genZ_Recoil_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_Met_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_Met_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  ) 
      Met_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_MetX_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_MetX_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  ) 
      MetX_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_MetY_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_MetY_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  )
      MetY_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_MetPhi_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_MetPhi_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  ) 
      MetPhi_Cuts_genZPhiBin[index].push_back(h2);

    if( (sprintf(name, "ZNuNu_ScalarEt_Cuts_genZPhiBin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_ScalarEt_Cuts_genZPhi_bin_%d", i) && (h2=(TH1 *)gROOT->FindObject(name)))  ) 
      ScalarEt_Cuts_genZPhiBin[index].push_back(h2);
  


   
 // generator Phi(Ureco) bins
    TH1 *h3;

    if( (sprintf(name, "ZNuNu_genZPt_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_genZPt_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  )  
      GenZPt_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_genZPhi_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_genZPhi_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))   ) 
      GenZPhi_Cuts_UPhiBin[index].push_back(h3);

   
    if( (sprintf(name, "ZNuNu_RecoilPt_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPt_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  ) 
      RecoilPt_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_RecoilPx_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPx_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  )
      RecoilPx_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_RecoilPy_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPy_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  )
      RecoilPy_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_RecoilPhi_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPhi_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))   ) 
      RecoilPhi_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_RecoilResolution_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_RecoilResolution_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  )
      RecoilResolution_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  || 
        (sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  ) 
      DeltaPhi_genZ_Recoil_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_Met_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_Met_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  ) 
      Met_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_MetX_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_MetX_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  ) 
      MetX_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_MetY_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_MetY_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  )
      MetY_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_MetPhi_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_MetPhi_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  ) 
      MetPhi_Cuts_UPhiBin[index].push_back(h3);

    if( (sprintf(name, "ZNuNu_ScalarEt_Cuts_UPhiBin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_ScalarEt_Cuts_UPhi_bin_%d", i) && (h3=(TH1 *)gROOT->FindObject(name)))  ) 
      ScalarEt_Cuts_UPhiBin[index].push_back(h3);
  

 // lumi bins
    TH1 *h4;

    if( (sprintf(name, "ZNuNu_genZPt_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_genZPt_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  )  
      GenZPt_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_genZPhi_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_genZPhi_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))   ) 
      GenZPhi_Cuts_lumiBin[index].push_back(h4);

   
    if( (sprintf(name, "ZNuNu_RecoilPt_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPt_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  ) 
      RecoilPt_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_RecoilPx_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPx_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  )
      RecoilPx_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_RecoilPy_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPy_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  )
      RecoilPy_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_RecoilPhi_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPhi_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))   ) 
      RecoilPhi_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_RecoilResolution_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_RecoilResolution_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  )
      RecoilResolution_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  || 
        (sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  ) 
      DeltaPhi_genZ_Recoil_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_Met_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_Met_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  ) 
      Met_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_MetX_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_MetX_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  ) 
      MetX_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_MetY_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_MetY_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  )
      MetY_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_MetPhi_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_MetPhi_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  ) 
      MetPhi_Cuts_lumiBin[index].push_back(h4);

    if( (sprintf(name, "ZNuNu_ScalarEt_Cuts_lumiBin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_ScalarEt_Cuts_lumi_bin_%d", i) && (h4=(TH1 *)gROOT->FindObject(name)))  ) 
      ScalarEt_Cuts_lumiBin[index].push_back(h4);
  
 // zbset bins
    TH1 *h5;

    if( (sprintf(name, "ZNuNu_genZPt_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_genZPt_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  )  
      GenZPt_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_genZPhi_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_genZPhi_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))   ) 
      GenZPhi_Cuts_zbsetBin[index].push_back(h5);

   
    if( (sprintf(name, "ZNuNu_RecoilPt_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPt_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  ) 
      RecoilPt_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_RecoilPx_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPx_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  )
      RecoilPx_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_RecoilPy_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPy_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  )
      RecoilPy_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_RecoilPhi_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_RecoilPhi_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))   ) 
      RecoilPhi_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_RecoilResolution_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_RecoilResolution_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  )
      RecoilResolution_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  || 
        (sprintf(name, "ZNuNu_DeltaPhi_genZ_Recoil_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  ) 
      DeltaPhi_genZ_Recoil_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_Met_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_Met_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  ) 
      Met_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_MetX_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_MetX_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  ) 
      MetX_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_MetY_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_MetY_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  )
      MetY_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_MetPhi_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  ||
	(sprintf(name, "ZNuNu_MetPhi_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  ) 
      MetPhi_Cuts_zbsetBin[index].push_back(h5);

    if( (sprintf(name, "ZNuNu_ScalarEt_Cuts_zbsetBin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  || 
	(sprintf(name, "ZNuNu_ScalarEt_Cuts_zbset_bin_%d", i) && (h5=(TH1 *)gROOT->FindObject(name)))  ) 
      ScalarEt_Cuts_zbsetBin[index].push_back(h5);
  }


  // for all regions
  sprintf(name, "%s", "ZNuNu_genZPt_Cuts");
  GenZPt_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));

  sprintf(name, "%s", "ZNuNu_genZPhi_Cuts");
  GenZPhi_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));

  sprintf(name, "%s", "ZNuNu_genVtxZ_Cuts");
  GenVtxZ_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_RecoilPt_Cuts");
  RecoilPt_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_RecoilPx_Cuts");
  RecoilPx_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_RecoilPy_Cuts");
  RecoilPy_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_RecoilPhi_Cuts");
  RecoilPhi_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_RecoilResolution_Cuts");
  RecoilResolution_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_DeltaPhi_genZ_Recoil_Cuts");
  DeltaPhi_genZ_Recoil_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_Met_Cuts");
  Met_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_MetX_Cuts");
  MetX_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_MetY_Cuts");
  MetY_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_MetPhi_Cuts");
  MetPhi_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));

  sprintf(name, "%s", "ZNuNu_ScalarEt_Cuts");
  ScalarEt_Cuts[index].push_back((TH1 *)gROOT->FindObject(name));
  
  // profile histograms
  sprintf(name, "%s", "ZNuNu_RecoilResponse_V_RecoilPt_Cuts");
  RecoilResponse_V_Recoilt_Cuts[index].push_back((TProfile *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_RecoilResponse_V_genZPt_Cuts");
  RecoilResponse_V_genZPt_Cuts[index].push_back((TProfile *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "ZNuNu_RecoilResponseProjection_V_RecoilPt_Cuts");
  RecoilResponseProjection_V_RecoilPt_Cuts[index].push_back((TProfile *)gROOT->FindObject(name));

  sprintf(name, "%s", "ZNuNu_RecoilResponseProjection_V_genZPt_Cuts");
  RecoilResponseProjection_V_genZPt_Cuts[index].push_back((TProfile *)gROOT->FindObject(name));

sprintf(name, "%s", "ZNuNu_RecoilResponse_V_RecoilPhi_Cuts");
  RecoilResponse_V_RecoilPhi_Cuts[index].push_back((TProfile *)gROOT->FindObject(name));
  
sprintf(name, "%s", "ZNuNu_RecoilResponse_V_genZPhi_Cuts");
  RecoilResponse_V_genZPhi_Cuts[index].push_back((TProfile *)gROOT->FindObject(name));
  
sprintf(name, "%s", "ZNuNu_RecoilResponse_V_lumi_Cuts");
  RecoilResponse_V_lumi_Cuts[index].push_back((TProfile *)gROOT->FindObject(name));
  
sprintf(name, "%s", "ZNuNu_RecoilResponse_V_zbset_Cuts");
  RecoilResponse_V_zbset_Cuts[index].push_back((TProfile *)gROOT->FindObject(name));



}
