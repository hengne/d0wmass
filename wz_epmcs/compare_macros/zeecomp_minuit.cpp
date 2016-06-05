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

#include "plot_util.cpp"

using namespace std;
using namespace plot;

vector<TH1 *> mass[2], Zpt[2], genZpt[2], Delta_genZpt_Zpt[2];
vector<TH1 *> elecpt[2], eleceta[2], elecdeteta[2], elecphi[2], elecupara[2], elecuperp[2];
vector<TH1 *> met[2], metphi[2], metx[2], mety[2];
vector<TH1 *> ZRecoilpt[2], ZRecoilpx[2], ZRecoilpy[2], ZRecoilphi[2];
vector<TH1 *> instlumi[2], deltaphi_emrecoil[2], deltaphi_emmet[2], balance1[2], balance2[2], balance3[2], balance4[2];
vector<TH1 *> peerecoprofile[2], peebalanceprofile[2], kappa3profile[2];
vector<TH1 *> hetaimbalance[2], hxiimbalance[2], hZpt[2], hDelta_genZpt_Zpt[2], hrecoilpt[2], hrecoilphi[2], hmet[2], hmetphi[2], hdeltaPhi_Z_Recoil[2], hdeltaPhi_Z_Met[2];
vector<TH1 *> h_smearUt_binno[2];

vector<TH1 *> Vtx[2], TrkPt[2];
double chi2_mean_EtaImbalance[2],
       chi2_width_EtaImbalance[2],
       chi2_mean_XiImbalance[2],
       chi2_width_XiImbalance[2],
       chi2_deltaphimbalance[2];
TGraphErrors *mean_etaimbalance_ge1[2], *mean_etaimbalance_ge2[2], *mean_etaimbalance_ge_chi[2], 
             *width_etaimbalance_ge1[2], *width_etaimbalance_ge2[2], *width_etaimbalance_ge_chi[2], 
             *mean_xiimbalance_ge1[2], *mean_xiimbalance_ge2[2], *mean_xiimbalance_ge_chi[2], 
             *width_xiimbalance_ge1[2], *width_xiimbalance_ge2[2], *width_xiimbalance_ge_chi[2],
             *deltaphimbalance_ge1[2], *deltaphimbalance_ge2[2], *deltaphimbalance_chi[2];

// if is_fullMC=TRUE then treat this file as from FULL MC not REAL DATA
void getHistogramsFromData_MINUITonly(TFile *f, int index, bool is_fullMC); // index = 0,1
void getHistogramsFromPMCS_MINUITonly(TFile *f, int index);                 // index = 0,1
void getHistogramsFromPMCS(TFile *f, int index);                            // index = 0,1

// main file
int main(int argc, char** argv){

  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  TPostScript *ps = new TPostScript("histogramszee_minuit.ps");
  TFile *zeecomp = new TFile("zeecomp_minuit.root", "recreate");
  TCanvas *c1 =  new TCanvas("aaa","c1",50,10,700,800);   // these 2 crazy lines are needed
  ps->NewPage();                                          // for proper alignment of the 1st page

  TString data_file = argv[1];
  TString mc_file = argv[2];

  if(argc!=5 && argc!=6) {
    cout<<" Please run it the following way: " << endl
	<<" ./zeecomp_minuit  <full_mc_root_file_name>  <pmcs_root_file_name_after_MINUIT>  <make_chi2_option>  <compare_option>  [rows_per_page]"
	<< endl << endl;  
    cout<<" If <make_chi2_option>=1 then CHI plots will be created too."<<endl;  
    cout<<" Use <compare_option>=0  for comparing DATA with Fast-MC after MINUIT fit (PMCS)," << endl
        <<"     <compare_option>=1  for comparing Full-MC (GEANT) with Fast-MC (PMCS, after MINUIT fit)," << endl
        <<"     <compare_option>=2  for comparing Fast-MC (PMCS)  with Fast-MC (PMCS, after MINUIT fit)," << endl
        <<"     <compare_option>=3  for comparing Fast-MC (PMCS, after MINUIT fit) with Fast-MC (PMCS, after MINUIT fit)." << endl << endl;
    cout<<" For example: ./zeecomp_minuit  data.root             fastmc_minuit.root   0 0"<<endl
        <<"              ./zeecomp_minuit  fullmc.root           fastmc_minuit.root   0 1"<<endl
        <<"              ./zeecomp_minuit  fastmc.root           fastmc_minuit.root   0 2"<<endl
        <<"              ./zeecomp_minuit  fastmc_minuit1.root   fastmc_minuit2.root  0 3"<<endl << endl;
    cout<<" If <make_chi2_option>=1 then CHI plots will be created too."<<endl;  
    cout<<" For example: ./zeecomp_minuit  fullmc.root   fastmc_minuit.root  0  1"<<endl<<endl;
    return 1;
  }

  // make chi2 plot
  int chi2_option = atoi(argv[3]);
  bool make_chi2 = false;
  if(chi2_option>0) make_chi2 = true;

  //DATA/MC PLOTS
  TFile *fdata = new TFile(data_file, "OLD");// first file (index=0 in getHistogramsFromData/getHistogramsFromPMCS)
  TFile *fpmcs = new TFile(mc_file, "OLD");  // second file (index=1 in getHistogramsFromData/getHistogramsFromPMCS)
  if(!fdata || !fpmcs) {
    cout << "Can't open first and/or second file !!!" << endl;
    if(fdata) fdata->Close();
    if(fpmcs) fpmcs->Close();
    return 1;
  }

  // make compare option
  int compare_option = atoi(argv[4]);
  switch(compare_option) {
  case 0:    // 0 for data - fast MC (MINUIT part) 
    set_DATA_label("DATA");         // first file, upper label
    set_MC_label("FAST MC");        // second file, bottom label
    if(!(fdata->cd("ZCand_Hist") && fpmcs->cd("smeared"))){
      cout<<" ==> compare option = 0, Are you comparing DATA to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromData_MINUITonly(fdata, 0, false);// will assume the first file is REAL data
    getHistogramsFromPMCS_MINUITonly(fpmcs, 1);       // will assume the second file is PMCS (MINUIT fit)
    cout<<" Red histogram for the first file (DATA), Blue histogram for the second file (PMCS)"<<endl;
    break;
  case 1:   // 1 for full MC - fast MC (MINUIT part) 
    set_DATA_label("FULL MC");      // first file, upper label
    set_MC_label("FAST MC");        // second file, bottom label
    if(!(fdata->cd("ZCand_Hist") && fpmcs->cd("smeared"))){
      cout<<" ==> compare option = 1, Are you comparing FULL-MC to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromData_MINUITonly(fdata, 0, true);// will assume the first file is FULL MC
    getHistogramsFromPMCS_MINUITonly(fpmcs, 1);      // will assume the second file is PMCS (MINUIT fit)
    cout<<" Red histogram for the first file (FULL MC), Blue histogram for the second file (PMCS)"<<endl;
    break;
  case 2:   // 2 for fast MC (default) - fast MC (MINUIT part) 
    set_DATA_label("FAST MC - default");  // first file, upper label
    set_MC_label("FAST MC - MINUIT fit"); // second file, bottom label
    if(!(fdata->cd("smeared") && fpmcs->cd("smeared"))){
      cout<<" ==> compare option = 2, Are you comparing FAST-MC to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromPMCS(fdata, 0);            // will assume the first file is PMCS (default)
    getHistogramsFromPMCS_MINUITonly(fpmcs, 1); // will assume the second file is PMCS (MINUIT fit) 
    cout<<" Red histogram for the first file (FULL MC), Blue histogram for the second file (PMCS)"<<endl;
    break;
  case 3:   // 3 for fast MC (MINUIT part) - fast MC (MINUIT part) 
    set_DATA_label("FAST MC - MINUIT fit #1"); // first file, upper label
    set_MC_label("FAST MC - MINUIT fit #2");   // second file, bottom label
    if(!(fdata->cd("smeared") && fpmcs->cd("smeared"))){
      cout<<" ==> compare option = 3, Are you comparing FAST-MC to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromPMCS_MINUITonly(fdata, 0); // will assume the first file is PMCS (MINUIT fit) 
    getHistogramsFromPMCS_MINUITonly(fpmcs, 1); // will assume the second file is PMCS (MINUIT fit) 
    cout<<" Red histogram for the first file (FULL MC), Blue histogram for the second file (PMCS)"<<endl;
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
#define FULLRANGE {-1E30, 1E30}
  typedef struct {
    char *cname;
    vector<TH1 *> *vect;
    const double rangeX[2]; } canvas_t; canvas_t plot[]= {
    { "hEtaImbalance",     hetaimbalance,     FULLRANGE},
    { "deltaPhi_Z_Recoil", hdeltaPhi_Z_Recoil,FULLRANGE}};
  const int nplots=sizeof(plot)/sizeof(canvas_t);

  typedef struct {
    char *cname;
    int property;         // 0=MEAN, 1=RMS
    int distribution;     // 0=Eta Imbalance, 1=Xi Imbalance
    vector<TH1 *> *inputY, *inputX;
    TGraphErrors *plot1[2], *plot2[2], *plotCHI[2];  // index: 0=non-fitted
    double *chi2;                                    //        1=from gauss fit
  } canvasMeanRms_t;
  canvasMeanRms_t plotMeanRms[]= { 
    { "etaimbalance_mean_compare", 0, 0,
      hetaimbalance, h_smearUt_binno,
      { mean_etaimbalance_ge1[0], mean_etaimbalance_ge1[1] },
      { mean_etaimbalance_ge2[0], mean_etaimbalance_ge2[1] },
      { mean_etaimbalance_ge_chi[0], mean_etaimbalance_ge_chi[1] },
      chi2_mean_EtaImbalance },
    { "etaimbalance_width_compare", 1, 0,
      hetaimbalance, h_smearUt_binno,
      { width_etaimbalance_ge1[0], width_etaimbalance_ge1[1] }, 
      { width_etaimbalance_ge2[0], width_etaimbalance_ge2[1] }, 
      { width_etaimbalance_ge_chi[0], width_etaimbalance_ge_chi[1] },
      chi2_width_EtaImbalance }
  };
 const int nplotsMeanRms=sizeof(plotMeanRms)/sizeof(canvasMeanRms_t);

  typedef struct {
    char *cname;
    vector<TH1 *> *inputY, *inputX;
    TGraphErrors *plot1[2], *plot2[2], *plotCHI[2];  // index: 0=non-fitted
    double *chi2;                                    //        1=from gauss fit
  } canvasRmsDeltaPhiZRecoil_t;
  canvasRmsDeltaPhiZRecoil_t plotRmsDeltaPhiZRecoil[]= { 
    { "deltaphiimbalance_compare",
      hdeltaPhi_Z_Recoil, h_smearUt_binno,
      { deltaphimbalance_ge1[0], deltaphimbalance_ge1[1] },
      { deltaphimbalance_ge2[0], deltaphimbalance_ge2[1] },
      { deltaphimbalance_chi[0], deltaphimbalance_chi[1] },
      chi2_deltaphimbalance }
  };
  const int nplotsRmsDeltaPhiZRecoil=sizeof(plotRmsDeltaPhiZRecoil)/sizeof(canvasRmsDeltaPhiZRecoil_t);

  // too many bins for eta-imbalance and xi-imbalance
  // will rebin them here
  for(int i=0; i<hetaimbalance[0].size(); i++) {
    (hetaimbalance[0])[i]->Rebin(2);
    (hetaimbalance[1])[i]->Rebin(2);
  }
 
  for(int iplot=0; iplot<nplots; iplot++) {
    // avoid blank pages for non-existing histograms
    if((plot[iplot].vect)[0].size() && (plot[iplot].vect)[1].size()) {
      plot_util(plot[iplot].cname, (plot[iplot].vect)[0], (plot[iplot].vect)[1], make_chi2, 
		plot[iplot].rangeX[0], plot[iplot].rangeX[1], ps, plots_per_page, zeecomp);
    }
  }

  // plot::plot_util() now operates on copies of input histograms
  // and it does not scale the originals. 
  // Here we calculate: mean value of EtaImbalance (property=0, distribution=0) 
  //                    mean value of XiImbalance  (property=0, distribution=1)
  //                    rms value of EtaImbalance (property=1, distribution=0) 
  //                    rms value of XiImbalance  (property=1, distribution=1).
  for(int iplot=0; iplot<nplotsMeanRms; iplot++) {
    // avoid blank pages for non-existing histograms
    if((plotMeanRms[iplot].inputY)[0].size() && (plotMeanRms[iplot].inputY)[1].size() && (plotMeanRms[iplot].inputX)[1].size()) {
      plot_MeanSigma_pTeeBin(plotMeanRms[iplot].cname, 
			     (plotMeanRms[iplot].inputY)[0], (plotMeanRms[iplot].inputY)[1], (plotMeanRms[iplot].inputX)[0], 
			     (plotMeanRms[iplot].plot1)[0], (plotMeanRms[iplot].plot2)[0], (plotMeanRms[iplot].plotCHI)[0], // non-fitted
			     (plotMeanRms[iplot].plot1)[1], (plotMeanRms[iplot].plot2)[1], (plotMeanRms[iplot].plotCHI)[1], // fitted
			     plotMeanRms[iplot].property, plotMeanRms[iplot].distribution, make_chi2, 
			     plotMeanRms[iplot].chi2[0], // non-fitted
			     plotMeanRms[iplot].chi2[1], // fitted
			     ps, plots_per_page, zeecomp );
    }
  }

  // plot::plot_util() now operates on copies of input histograms
  // and it does not scale the originals. 
  // Here sigma of Phi(Z)-Phi(Recoil) distribution (centered at PI) from histogram 
  // |Phi(Z)-Phi(Recoil)| is calculated. A standard RMS won't work in this case.  
  for(int iplot=0; iplot<nplotsRmsDeltaPhiZRecoil; iplot++) {
    // avoid blank pages for non-existing histograms
    if((plotRmsDeltaPhiZRecoil[iplot].inputY)[0].size() && (plotRmsDeltaPhiZRecoil[iplot].inputY)[1].size() && (plotRmsDeltaPhiZRecoil[iplot].inputX)[1].size()) {
      plot_SigmaDeltaPhiZRecoil_pTeeBin
	(plotRmsDeltaPhiZRecoil[iplot].cname, 
	 (plotRmsDeltaPhiZRecoil[iplot].inputY)[0], 
	 (plotRmsDeltaPhiZRecoil[iplot].inputY)[1], (plotRmsDeltaPhiZRecoil[iplot].inputX)[0], 
	 (plotRmsDeltaPhiZRecoil[iplot].plot1)[0], (plotRmsDeltaPhiZRecoil[iplot].plot2)[0], (plotRmsDeltaPhiZRecoil[iplot].plotCHI)[0], // non-fitted
	 (plotRmsDeltaPhiZRecoil[iplot].plot1)[1], (plotRmsDeltaPhiZRecoil[iplot].plot2)[1], (plotRmsDeltaPhiZRecoil[iplot].plotCHI)[1], // fitted
	 make_chi2, 
	 plotRmsDeltaPhiZRecoil[iplot].chi2[0], // non-fitted
	 plotRmsDeltaPhiZRecoil[iplot].chi2[1], // fitted
	 ps, plots_per_page, zeecomp );
    }
  }

  ps->Close();
  zeecomp->Write("All");
  zeecomp->Close();
}


void getHistogramsFromData_MINUITonly(TFile *f, int index, bool is_fullMC) {
  f -> cd("ZCand_Hist");
  char name[50];

  // PLOTS IN BINS OF RECOIL_PT
  for(int i=0; i<10; i++) {
    sprintf(name, "%s%d", "ZCandEtaImBalance_bin_", i);
    hetaimbalance[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDeltaPhi_Z_Recoil_bin_", i);
    hdeltaPhi_Z_Recoil[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCand_Ut_binno_", i);
    h_smearUt_binno[index].push_back(new TH1F(name,name,10,-0.5,10.5));
    (*(h_smearUt_binno[index].rbegin()))->Fill((float)i);
  }
}


void getHistogramsFromPMCS_MINUITonly(TFile *f, int index) {
  f -> cd("smeared");
  char name[50];

  // PLOTS IN BINS OF RECOIL_PT 
  for(int i=0; i<10; i++) {
    sprintf(name, "%s%d", "minuit_hZcandEtaImBalance_bin_", i);
    hetaimbalance[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "minuit_hZcandDeltaPhi_Z_Recoil_bin_", i);
    hdeltaPhi_Z_Recoil[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "minuit_hZcandUt_binno_", i);
    h_smearUt_binno[index].push_back(new TH1F(name,name,10,-0.5,10.5));
    (*(h_smearUt_binno[index].rbegin()))->Fill((float)i);
  }
}

void getHistogramsFromPMCS(TFile *f, int index) {
  f -> cd("smeared");
  char name[50];

  // PLOTS IN BINS OF RECOIL_PT 
  for(int i=0; i<10; i++) {
    sprintf(name, "%s%d", "smeared_hZcandEtaImBalance_bin_", i);
    hetaimbalance[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDeltaPhi_Z_Recoil_bin_", i);
    hdeltaPhi_Z_Recoil[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandUt_binno_", i);
    h_smearUt_binno[index].push_back(new TH1F(name,name,10,-0.5,10.5));
    (*(h_smearUt_binno[index].rbegin()))->Fill((float)i);
  }
}
