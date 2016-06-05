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
// #define MORE_ELECTRON_PHI_HISTOGRAMS
// #define MORE_PEE_HISTOGRAMS
//#define MORE_ZB_PLOTS

using namespace std;
using namespace plot;

vector<TH1 *> mass[2], diffmass[2], Zpt[2], genZpt[2], Delta_genZpt_Zpt[2], Delta_genZphi_Zphi[2], Zphi[2];
vector<TH1 *> elecpt[2], elec0pt[2], elec1pt[2], elecgenpt[2], elecgen0pt[2], elecgen1pt[2], elecrawgenpt[2], elecrawgen0pt[2], elecrawgen1pt[2], diffelecpt[2], diffelec0pt[2], diffelec1pt[2], elece[2], elec0e[2], elec1e[2], elecgene[2], elecgen0e[2], elecgen1e[2], elecrawgene[2], elecrawgen0e[2], elecrawgen1e[2], diffelece[2], diffelec0e[2], diffelec1e[2], eleceta[2], elecdeteta[2], elecphi[2], elecupara[2], elecuperp[2];
vector<TH1 *> elecpx[2], elec0px[2], elec1px[2], elecpy[2], elec0py[2], elec1py[2], elecpz[2], elec0pz[2], elec1pz[2], Zpx[2], Zpy[2],  Zpz[2], hZpeeeta[2], hZdeltaphi[2];
vector<TH1 *> elecphitrkatdca[2], elecphitrkatem3[2], elecdetphicalo[2];
vector<TH1 *> met[2], metphi[2], metx[2], mety[2], zcandphi[2];
vector<TH1 *> ZRecoilpt[2], ZRecoilpx[2], ZRecoilpy[2], ZRecoilphi[2];
vector<TH1 *> instlumi[2], scalarEt[2], deltaphi_emrecoil[2], deltaphi_emmet[2], balance1[2], balance2[2], balance3[2], balance4[2] , cosdeltaphi_em1em2[2] , diffcosdeltaphi_em1em2[2] , deltaeta_em1em2[2] , diffdeltaeta_em1em2[2];
vector<TH1 *> scalarEtZB[2], scalarEtZBNoScale[2];
vector<TH1 *> peerecoprofile[2], peebalanceprofile[2], kappa3profile[2];
vector<TH1 *> hetaimbalance[2], hxiimbalance[2], hZpt[2], hZphi[2], hDelta_genZpt_Zpt[2], hDelta_genZphi_Zphi[2], hMass[2] , hdiffMass[2] , hrecoilpt[2], hrecoilphi[2], hmet[2], hmetphi[2], hdeltaPhi_Z_Recoil[2], hdeltaPhi_Z_Met[2], hscalarEt[2], hzcandelectrkphiem3mod[2] , hCosDeltaPhi_EM1EM2[2] , hDiffCosDeltaPhi_EM1EM2[2] , hDeltaEta_EM1EM2[2] , hDiffDeltaEta_EM1EM2[2] , helecpt[2], helec0pt[2], helec1pt[2], helecgenpt[2], helecgen0pt[2], helecgen1pt[2], helecrawgenpt[2], helecrawgen0pt[2], helecrawgen1pt[2], hdiffelecpt[2] , hdiffelec0pt[2] , hdiffelec1pt[2] , helece[2], helec0e[2], helec1e[2], helecgene[2], helecgen0e[2], helecgen1e[2], helecrawgene[2], helecrawgen0e[2], helecrawgen1e[2], hdiffelece[2] , hdiffelec0e[2] , hdiffelec1e[2];
vector<TH1 *> Vtx[2], TrkPt[2], TrkCalMass[2], TrkPtOvE[2],  TrkPtOvETight[2],  TrkPtTight[2] ;
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
vector<TH1 *> Mass_Category[2], ElecPt_Category[2];
vector<TH1 *> Mass_PhiModCategory[2];
vector<TH1 *> hpeeetabin[2];

// if is_fullMC=TRUE then treat this file as from FULL MC not REAL DATA
void getHistogramsFromData(TFile *f, int index, bool is_fullMC);   // index = 0,1
void getHistogramsFromPMCS(TFile *f, int index);                   // index = 0,1

// main file
int main(int argc, char** argv){

  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  TPostScript *ps = new TPostScript("histogramszee.ps");
  TFile *zeecomp = new TFile("zeecomp.root", "recreate");
  TCanvas *c1 =  new TCanvas("aaa","c1",50,10,700,800);   // these 2 crazy lines are needed
  ps->NewPage();                                          // for proper alignment of the 1st page

  TString data_file = argv[1];
  TString mc_file = argv[2];

  if(argc!=5 && argc!=6 && argc!=7) {
    cout<<" Please run it the following way: " << endl
	<<" ./zeecomp  <first_root_file_name>  <second_root_file_name>  <make_chi2_option>  <compare_option>  [rows_per_page]  [detail_level]"
	<< endl << endl;  
    cout<<" If <make_chi2_option>=1 then CHI plots will be created too."<<endl;  
    cout<<" Use <compare_option>=0  for comparing DATA with Fast-MC (PMCS)," << endl
        <<"     <compare_option>=1  for comparing DATA with DATA," << endl
	<<"     <compare_option>=2  for comparing Fast-MC (PMCS) with Fast-MC (PMCS)," << endl
        <<"     <compare_option>=3  for comparing Full-MC (GEANT) with Fast-MC (PMCS)," << endl
        <<"     <compare_option>=4  for comparing Full-MC (GEANT) with Full-MC (GEANT)," << endl
        <<"     <compare_option>=5  for comparing DATA with Full-MC (GEANT)." << endl << endl;
    cout<<" For example: ./zeecomp  data.root     fastmc.root   0 0"<<endl
        <<"              ./zeecomp  data1.root    data2.root    0 1"<<endl
        <<"              ./zeecomp  fastmc1.root  fastmc2.root  0 2"<<endl
        <<"              ./zeecomp  fullmc.root   fastmc.root   0 3"<<endl
        <<"              ./zeecomp  fullmc1.root  fullmc2.root  0 4"<<endl
        <<"              ./zeecomp  data.root     fullmc.root   0 5"<<endl<<endl;
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
  case 0:    // 0 for data - fast MC, 
    set_DATA_label("DATA");         // first file, upper label
    set_MC_label("FAST MC");        // second file, bottom label
    if(!(fdata->cd("ZCand_Hist") && fpmcs->cd("smeared"))){
      cout<<" ==> compare option = 0, Are you comparing DATA to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromData(fdata, 0, false);// will assume the first data file is REAL data
    getHistogramsFromPMCS(fpmcs, 1);       // will assume the second MC file is PMCS
    cout<<" Red histogram for the first file (DATA), Blue histogram for the second file (PMCS)"<<endl;
    break;
  case 1:    // 1 for data - data, 
    set_DATA_label("DATA #1");      // first file, upper label
    set_MC_label("DATA #2");        // second file, bottom label
    if(!(fdata->cd("ZCand_Hist") && fpmcs->cd("ZCand_Hist"))){
      cout<<" ==> compare option = 1, Are you comparing DATA to DATA ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromData(fdata, 0, false);// will assume the first data file is REAL data
    getHistogramsFromData(fpmcs, 1, false);// will assume the second data file is REAL data
    cout<<" Red histogram for the first DATA file, Blue histogram for the second DATA file"<<endl;
    break;
  case 2:    // 2 for fast MC - fast MC 
    set_DATA_label("FAST MC #1");   // first file, upper label
    set_MC_label("FAST MC #2");     // second file, bottom label
    if(!(fdata->cd("smeared") && fpmcs->cd("smeared"))){
      cout<<" ==> compare option = 2, Are you comparing FAST-MC to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromPMCS(fdata, 0);// will assume the first MC file is PMCS
    getHistogramsFromPMCS(fpmcs, 1);// will assume the second MC file is PMCS
    cout<<" Red histogram for the first PMCS file, Blue histogram for the second PMCS file"<<endl;
    break;
  case 3:   // 3 for full MC - fast MC 
    set_DATA_label("FULL MC");      // first file, upper label
    set_MC_label("FAST MC");        // second file, bottom label
    if(!(fdata->cd("ZCand_Hist") && fpmcs->cd("smeared"))){
      cout<<" ==> compare option = 3, Are you comparing FULL-MC to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromData(fdata, 0, true);// will assume the first data file is FULL MC
    getHistogramsFromPMCS(fpmcs, 1);      // will assume the first data file is PMCS
    cout<<" Red histogram for the first file (FULL MC), Blue histogram for the second file (PMCS)"<<endl;
    break;
  case 4:    // 4 for full MC - full MC 
    set_DATA_label("FULL MC #1");   // first file, upper label
    set_MC_label("FULL MC #2");     // second file, bottom label
    if(!(fdata->cd("ZCand_Hist") && fpmcs->cd("ZCand_Hist"))){
      cout<<" ==> compare option = 4, Are you comparing FULL-MC to FULL-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromData(fdata, 0, true);// will assume the first data file is FULL MC
    getHistogramsFromData(fpmcs, 1, true);// will assume the second data file is FULL MC
    cout<<" Red histogram for the first FULL MC file, Blue histogram for the second FULL MC file"<<endl;    
    break;
  case 5:    // 5 for DATA - full MC 
    set_DATA_label("DATA");   // first file, upper label
    set_MC_label("FULL MC");  // second file, bottom label
    if(!(fdata->cd("ZCand_Hist") && fpmcs->cd("ZCand_Hist"))){
      cout<<" ==> compare option = 5, Are you comparing DATA to FULL-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    getHistogramsFromData(fdata, 0, false);// will assume the first data file is FULL MC
    getHistogramsFromData(fpmcs, 1, false);// will assume the second data file is FULL MC
    cout<<" Red histogram for the first FULL MC file, Blue histogram for the second FULL MC file"<<endl;    
    break;
  default:  // UNKNOWN
    cout<<"Wrong <compare_option>="<<compare_option<<" !!!"<<endl;
    if(fdata) fdata->Close();
    if(fpmcs) fpmcs->Close();
    return 1;
  };

  // max plots/page
  int plots_per_page = 10;
  if(argc>=6 && atoi(argv[5])>0) plots_per_page=atoi(argv[5]);

  // detail level
  int detail_level = 0;
  if(argc>=7 && atoi(argv[6])>0) detail_level=atoi(argv[6]);

  ////////////////////////////////////////////////////////////////////////////
#define FULLRANGE {-1E30, 1E30}
  typedef struct {
    char *cname;
    vector<TH1 *> *vect;
    const double rangeX[2]; } canvas_t; canvas_t plot_part1[]= {
    { "zmass",             mass,              { 70., 110. }},
    { "diffzmass",             diffmass,              FULLRANGE},
    #ifdef MORE_PEE_HISTOGRAMS
    { "hpeeetabin",    hpeeetabin, FULLRANGE},
    { "elecpx",            elecpx,            FULLRANGE},
    { "elec0px",           elec0px,            FULLRANGE},
    { "elec1px",           elec1px,            FULLRANGE},
    { "elecpy",            elecpy,            FULLRANGE},
    { "elec0py",           elec0py,            FULLRANGE},
    { "elec1py",           elec1py,            FULLRANGE},
    { "elecpz",            elecpz,            FULLRANGE},
    { "elec0pz",           elec0pz,            FULLRANGE},
    { "elec1pz",           elec1pz,            FULLRANGE},

    { "ZpX",               Zpx,               FULLRANGE},
    { "ZpY",               Zpy,               FULLRANGE},
    { "ZpZ",               Zpz,               FULLRANGE},

    { "hZpeeeta",             hZpeeeta,           FULLRANGE},
    { "hZdeltaphi",            hZdeltaphi,           FULLRANGE},
    #endif
    { "elecpT",            elecpt,            { 25.,  70. }},
    { "elec0pT",           elec0pt,            { 25.,  70. }},
    { "elec1pT",           elec1pt,            { 25.,  70. }},
    { "elecgenpT",           elecgenpt,            { 25.,  70. }},
    { "elecgen0pT",           elecgen0pt,            { 25.,  70. }},
    { "elecgen1pT",           elecgen1pt,            { 25.,  70. }},
    { "elecrawgenpT",           elecrawgenpt,            { 25.,  70. }},
    { "elecrawgen0pT",           elecrawgen0pt,            { 25.,  70. }},
    { "elecrawgen1pT",           elecrawgen1pt,            { 25.,  70. }},
    { "diffelecpT",           diffelecpt,            FULLRANGE},
    { "diffelec0pT",           diffelec0pt,            FULLRANGE},
    { "diffelec1pT",           diffelec1pt,            FULLRANGE},
    { "elecE",            elece,            { 25.,  90. }},
    { "elec0E",           elec0e,            { 25.,  90. }},
    { "elec1E",           elec1e,            { 25.,  90. }},
    { "elecgenE",           elecgene,            { 25.,  90. }},
    { "elecgen0E",           elecgen0e,            { 25.,  90. }},
    { "elecgen1E",           elecgen1e,            { 25.,  90. }},
    { "elecrawgenE",           elecrawgene,            { 25.,  90. }},
    { "elecrawgen0E",           elecrawgen0e,            { 25.,  90. }},
    { "elecrawgen1E",           elecrawgen1e,            { 25.,  90. }},
    { "diffelecE",           diffelece,            FULLRANGE},
    { "diffelec0E",           diffelec0e,            FULLRANGE},
    { "diffelec1E",           diffelec1e,            FULLRANGE},
    { "elecEta",           eleceta,           FULLRANGE},
    { "elecDetEta",        elecdeteta,        FULLRANGE},
    { "elecPhi",           elecphi,           FULLRANGE},
#ifdef MORE_ELECTRON_PHI_HISTOGRAMS
    { "elecPhiTrkAtDCA",   elecphitrkatdca,  FULLRANGE},
    { "elecPhiTrkAtEM3",   elecphitrkatem3,  FULLRANGE},
    { "elecDetPhiCALO",    elecdetphicalo,   FULLRANGE},
#endif
    { "ZpT",               Zpt,               FULLRANGE},
    { "ZPhi",              Zphi,              FULLRANGE},
    { "genZpT",            genZpt,            FULLRANGE},
    { "Delta_genZpT_ZpT",  Delta_genZpt_Zpt,  FULLRANGE},
    { "Delta_genZphi_Zphi", Delta_genZphi_Zphi, FULLRANGE},
    { "ZRecoilpT",         ZRecoilpt,         {  0.,  30. }},
    { "ZRecoilPhi",        ZRecoilphi,        FULLRANGE},
    { "ZRecoilPx",         ZRecoilpx,         {-20.,  20. }},
    { "ZRecoilPy",         ZRecoilpy,         {-20.,  20. }},
    { "Met",               met,               {  0.,  30. }},
    { "MetPhi",            metphi,            FULLRANGE},
    { "ZCandPhi",          zcandphi,          FULLRANGE},
    { "Metx",              metx,              {-20.,  20. }},
    { "Mety",              mety,              {-20.,  20. }},
    { "vertex",            Vtx,               {-60.,  60. }},
    { "trkpT",             TrkPt,             { 10.,  60. }},
    { "trkpTtight",             TrkPtTight,             { 10.,  60. }},
    { "trkcalMass",        TrkCalMass,        { 70,  110.}},
    { "trkptove",          TrkPtOvE,          {0.,   1.1}},
    { "trkptovetight",          TrkPtOvETight,          {0.,   1.1}},
    { "elecUpara",         elecupara,         {-20.,  20. }},
    { "elecUperp",         elecuperp,         {-20.,  20. }},
    { "Instlumi",          instlumi,          FULLRANGE},
    { "ScalarET",          scalarEt,          {0.,   300. }},
#ifdef MORE_ZB_PLOTS
    { "ScalarETZB",        scalarEtZB,        {0.,   300. }},
    { "ScalarETZBNoScale", scalarEtZBNoScale, {0.,   300. }},
#endif
    { "Deltaphi_emrecoil", deltaphi_emrecoil, FULLRANGE},
    { "Deltaphi_emmet",    deltaphi_emmet,    FULLRANGE},
    { "cosDeltaphi_em1em2",    cosdeltaphi_em1em2,    FULLRANGE},
    { "diffCosDeltaphi_em1em2",    diffcosdeltaphi_em1em2,    FULLRANGE},
    { "deltaeta_em1em2",    deltaeta_em1em2,    FULLRANGE},
    { "diffDeltaeta_em1em2",    diffdeltaeta_em1em2,    FULLRANGE},
    { "Balance1",          balance1,          FULLRANGE},
    { "Balance2",          balance2,          FULLRANGE},
    { "Balance3",          balance3,          {-10.,  20. }},
    { "Balance4",          balance4,          {-15.,  15. }},
    { "peerecoprof",       peerecoprofile,    FULLRANGE},
    { "peebalanceprof",    peebalanceprofile, FULLRANGE},
    { "kappa3prof",        kappa3profile,     FULLRANGE}};
  const int nplots_part1=sizeof(plot_part1)/sizeof(canvas_t);
  canvas_t plot_part2[] = { 
    { "hZpT",              hZpt,              FULLRANGE},
    { "hZPhi",             hZphi,             FULLRANGE},
    { "hDelta_genZpT_ZpT", hDelta_genZpt_Zpt, FULLRANGE},
    { "hDelta_genZphi_Zphi", hDelta_genZphi_Zphi, FULLRANGE},
    { "hMass" ,            hMass,             FULLRANGE},
    { "hdiffMass" ,            hdiffMass,             FULLRANGE},
    { "hEtaImbalance",     hetaimbalance,     FULLRANGE},
    { "hXiImbalance",      hxiimbalance,      FULLRANGE},
    { "hRecoilpT",         hrecoilpt,         {  0.,  30. }},
    { "hRecoilPhi",        hrecoilphi,        FULLRANGE},
    { "hMET",              hmet,              {  0.,  30. }},
    { "hMETPhi",           hmetphi,           FULLRANGE},
    { "hZcandElecTrkPhiEM3Mod",      hzcandelectrkphiem3mod,         FULLRANGE},
    { "deltaPhi_Z_Met",    hdeltaPhi_Z_Met,   FULLRANGE},
    { "deltaPhi_Z_Recoil", hdeltaPhi_Z_Recoil,FULLRANGE},
    { "CosDeltaPhi_em1em2", hCosDeltaPhi_EM1EM2,FULLRANGE},
    { "DiffCosDeltaPhi_em1em2", hDiffCosDeltaPhi_EM1EM2,FULLRANGE},
    { "DeltaEta_em1em2", hDeltaEta_EM1EM2,FULLRANGE},
    { "DiffDeltaEta_em1em2", hDiffDeltaEta_EM1EM2,FULLRANGE},

    { "ElecPt",   helecpt, { 25.,  70. }},
    { "Elec0Pt",  helec0pt, { 25.,  70. }},
    { "Elec1Pt",  helec1pt, { 25.,  70. }},
    { "ElecGenPt", helecgenpt, { 25.,  70. }},
    { "ElecGen0Pt", helecgen0pt, { 25.,  70. }},
    { "ElecGen1Pt", helecgen1pt, { 25.,  70. }},
    { "ElecRawGenPt", helecrawgenpt, { 25.,  70. }},
    { "ElecRawGen0Pt", helecrawgen0pt, { 25.,  70. }},
    { "ElecRawGen1Pt", helecrawgen1pt, { 25.,  70. }},
    { "ElecE",   helece, { 25.,  90. }},
    { "Elec0E",  helec0e, { 25.,  90. }},
    { "Elec1E",  helec1e, { 25.,  90. }},
    { "ElecGenE", helecgene, { 25.,  90. }},
    { "ElecGen0E", helecgen0e, { 25.,  90. }},
    { "ElecGen1E", helecgen1e, { 25.,  90. }},
    { "ElecRawGenE", helecrawgene, { 25.,  90. }},
    { "ElecRawGen0E", helecrawgen0e, { 25.,  90. }},
    { "ElecRawGen1E", helecrawgen1e, { 25.,  90. }},

    { "DiffElecPt", hdiffelecpt,FULLRANGE},
    { "DiffElec0Pt", hdiffelec0pt,FULLRANGE},
    { "DiffElec1Pt", hdiffelec1pt,FULLRANGE},

    { "DiffElecE", hdiffelece,FULLRANGE},
    { "DiffElec0E", hdiffelec0e,FULLRANGE},
    { "DiffElec1E", hdiffelec1e,FULLRANGE}
  };
  const int nplots_part2=sizeof(plot_part2)/sizeof(canvas_t);

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
      hetaimbalance, hZpt, 
      { mean_etaimbalance_ge1[0], mean_etaimbalance_ge1[1] },
      { mean_etaimbalance_ge2[0], mean_etaimbalance_ge2[1] },
      { mean_etaimbalance_ge_chi[0], mean_etaimbalance_ge_chi[1] },
      chi2_mean_EtaImbalance },
    { "etaimbalance_width_compare", 1, 0,
      hetaimbalance, hZpt,
      { width_etaimbalance_ge1[0], width_etaimbalance_ge1[1] }, 
      { width_etaimbalance_ge2[0], width_etaimbalance_ge2[1] }, 
      { width_etaimbalance_ge_chi[0], width_etaimbalance_ge_chi[1] },
      chi2_width_EtaImbalance },
    { "xiimbalance_mean_compare", 0, 1,
      hxiimbalance, hZpt,     
      { mean_xiimbalance_ge1[0], mean_xiimbalance_ge1[1] }, 
      { mean_xiimbalance_ge2[0], mean_xiimbalance_ge2[1] }, 
      { mean_xiimbalance_ge_chi[0], mean_xiimbalance_ge_chi[1] },
      chi2_mean_XiImbalance },
    { "xiimbalance_width_compare", 1, 1,
      hxiimbalance, hZpt,     
      { width_xiimbalance_ge1[0], width_xiimbalance_ge1[1] },  
      { width_xiimbalance_ge2[0], width_xiimbalance_ge2[1] }, 
      { width_xiimbalance_ge_chi[0], width_xiimbalance_ge_chi[1] },
      chi2_width_XiImbalance }
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
      hdeltaPhi_Z_Recoil, hZpt, 
      { deltaphimbalance_ge1[0], deltaphimbalance_ge1[1] },
      { deltaphimbalance_ge2[0], deltaphimbalance_ge2[1] },
      { deltaphimbalance_chi[0], deltaphimbalance_chi[1] },
      chi2_deltaphimbalance }
  };
  const int nplotsRmsDeltaPhiZRecoil=sizeof(plotRmsDeltaPhiZRecoil)/sizeof(canvasRmsDeltaPhiZRecoil_t);

  canvas_t plot_EtaCategories[] = { 
    { "Mass_Category", Mass_Category, { 70., 110. }}};
  const int nplots_EtaCategories=sizeof(plot_EtaCategories)/sizeof(canvas_t);

  canvas_t plot_EtaCategories2[] = {
    { "ElecPt_Category", ElecPt_Category, { 25., 70. }}};
  const int nplots_EtaCategories2=sizeof(plot_EtaCategories2)/sizeof(canvas_t);

  canvas_t plot_PhiModCategories[] = {
    { "Mass_PhiModCategory", Mass_PhiModCategory, { 70., 110. }}};
  const int nplots_PhiModCategories=sizeof(plot_PhiModCategories)/sizeof(canvas_t);

  canvas_t plot_part3[] = {
    { "ScalarEt", hscalarEt, { 0., 200. }}};
  const int nplots_part3=sizeof(plot_part3)/sizeof(canvas_t);

  double CCscale = mass[0][1]->Integral()/mass[1][1]->Integral();
  double CCscaleE = CCscale*sqrt(pow(sqrt(mass[0][1]->Integral())/mass[0][1]->Integral(),2)+
				 pow(sqrt(mass[1][1]->Integral())/mass[1][1]->Integral(),2));
  cout<<"CCscale: "<<mass[0][1]->Integral()<<" "<<mass[1][1]->Integral()<<" "<<CCscale<<" +/- "<<CCscaleE<<endl;

  for(int iplot=0; iplot<nplots_part1; iplot++) {
    //cout << "Plotting: "<<plot_part1[iplot].cname<<endl;
    //cout << (plot_part1[iplot].vect)[0].size() << "   " << (plot_part1[iplot].vect)[1].size() << endl;
    // avoid blank pages for non-existing histograms
    if((plot_part1[iplot].vect)[0].size() && (plot_part1[iplot].vect)[1].size()) {
      plot_util(plot_part1[iplot].cname, (plot_part1[iplot].vect)[0], (plot_part1[iplot].vect)[1], make_chi2, 
		plot_part1[iplot].rangeX[0], plot_part1[iplot].rangeX[1], ps, plots_per_page, zeecomp);
    }
  }

  // too many bins for eta-imbalance and xi-imbalance
  // will rebin them here
  for(int i=0; i<hetaimbalance[0].size(); i++) {
    (hetaimbalance[0])[i]->Rebin(2);
    (hetaimbalance[1])[i]->Rebin(2);
    (hxiimbalance[0])[i]->Rebin(2);
    (hxiimbalance[1])[i]->Rebin(2);
    //  (hetaimbalance[0])[i]->GetXaxis()->SetRangeUser((hetaimbalance[0])[i]->GetMean()-10., (hetaimbalance[0])[i]->GetMean()+10.);
    //  (hetaimbalance[1])[i]->GetXaxis()->SetRangeUser((hetaimbalance[0])[i]->GetMean()-10., (hetaimbalance[0])[i]->GetMean()+10.);
  }

  // plot::plot_util() now operates on copies of input histograms
  // and it does not scale the originals. 
  // Here we calculate: mean value of EtaImbalance (property=0, distribution=0) 
  //                    mean value of XiImbalance  (property=0, distribution=1)
  //                    rms value of EtaImbalance (property=1, distribution=0) 
  //                    rms value of XiImbalance  (property=1, distribution=1).
  for(int iplot=0; iplot<nplotsMeanRms; iplot++) {

    //    cout << "Plotting: "<<plotMeanRms[iplot].cname<<endl;

    // avoid blank pages for non-existing histograms
    if((plotMeanRms[iplot].inputY)[0].size() && (plotMeanRms[iplot].inputY)[1].size() && (plotMeanRms[iplot].inputX)[1].size()) {
      plot_MeanSigma_pTeeBin(plotMeanRms[iplot].cname, 
			     (plotMeanRms[iplot].inputY)[0], (plotMeanRms[iplot].inputY)[1], (plotMeanRms[iplot].inputX)[1], 
			     (plotMeanRms[iplot].plot1)[0], (plotMeanRms[iplot].plot2)[0], (plotMeanRms[iplot].plotCHI)[0], // non-fitted
			     (plotMeanRms[iplot].plot1)[1], (plotMeanRms[iplot].plot2)[1], (plotMeanRms[iplot].plotCHI)[1], // fitted
			     plotMeanRms[iplot].property, plotMeanRms[iplot].distribution, make_chi2, 
			     plotMeanRms[iplot].chi2[0], // non-fitted
			     plotMeanRms[iplot].chi2[1], // fitted
			     ps, plots_per_page, zeecomp );
    }
  }

  for(int iplot=0; iplot<nplots_part2; iplot++) {

    //    cout << "Plotting: "<<plot_part2[iplot].cname<<endl;

    // avoid blank pages for non-existing histograms
    if((plot_part2[iplot].vect)[0].size() && (plot_part2[iplot].vect)[1].size()) {
      plot_util(plot_part2[iplot].cname, (plot_part2[iplot].vect)[0], (plot_part2[iplot].vect)[1], make_chi2, 
		plot_part2[iplot].rangeX[0], plot_part2[iplot].rangeX[1], ps, plots_per_page, zeecomp );
    }
  }

  // plot::plot_util() now operates on copies of input histograms
  // and it does not scale the originals. 
  // Here sigma of Phi(Z)-Phi(Recoil) distribution (centered at PI) from histogram 
  // |Phi(Z)-Phi(Recoil)| is calculated. A standard RMS won't work in this case.  
  for(int iplot=0; iplot<nplotsRmsDeltaPhiZRecoil; iplot++) {

    //    cout << "Plotting: "<<plotRmsDeltaPhiZRecoil[iplot].cname<<endl;

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

  if (detail_level>1) {
    for (int i=0; i<2; i++) {
      for (int ii=0; ii<Mass_Category[0].size(); ii++) {
	if((Mass_Category[i])[ii]) (Mass_Category[i])[ii]=(Mass_Category[i])[ii]->Rebin(4);
	if((ElecPt_Category[i])[ii]) (ElecPt_Category[i])[ii]=(ElecPt_Category[i])[ii]->Rebin(4);
      }
    }
    //
    for(int iplot=0; iplot<nplots_EtaCategories; iplot++) {

      //      cout << "Plotting: "<<plot_EtaCategories[iplot].cname<<endl;

      // avoid blank pages for non-existing histograms
      if((plot_EtaCategories[iplot].vect)[0].size() && (plot_EtaCategories[iplot].vect)[1].size()) {
        plot_util(plot_EtaCategories[iplot].cname, (plot_EtaCategories[iplot].vect)[0], (plot_EtaCategories[iplot].vect)[1], make_chi2,
                  plot_EtaCategories[iplot].rangeX[0], plot_EtaCategories[iplot].rangeX[1], ps, plots_per_page, zeecomp);
      }
    }
    //
    for(int iplot=0; iplot<nplots_EtaCategories2; iplot++) {

      //      cout << "Plotting: "<<plot_EtaCategories2[iplot].cname<<endl;

      // avoid blank pages for non-existing histograms
      if((plot_EtaCategories2[iplot].vect)[0].size() && (plot_EtaCategories2[iplot].vect)[1].size()) {
	plot_util(plot_EtaCategories2[iplot].cname, (plot_EtaCategories2[iplot].vect)[0], (plot_EtaCategories2[iplot].vect)[1], make_chi2, 
		  plot_EtaCategories2[iplot].rangeX[0], plot_EtaCategories2[iplot].rangeX[1], ps, plots_per_page, zeecomp);
      }
    }
  }

  if (detail_level>3) {
    for (int i=0; i<2; i++) {
      for (int ii=0; ii<Mass_PhiModCategory[0].size(); ii++) {
        (Mass_PhiModCategory[i])[ii]=(Mass_PhiModCategory[i])[ii]->Rebin(4);
      }
    }
    //
    for(int iplot=0; iplot<nplots_PhiModCategories; iplot++) {
      // avoid blank pages for non-existing histograms
      if((plot_PhiModCategories[iplot].vect)[0].size() && (plot_PhiModCategories[iplot].vect)[1].size()) {
        plot_util(plot_PhiModCategories[iplot].cname, (plot_PhiModCategories[iplot].vect)[0], (plot_PhiModCategories[iplot].vect)[1], make_chi2,
                  plot_PhiModCategories[iplot].rangeX[0], plot_PhiModCategories[iplot].rangeX[1], ps, 4, zeecomp);
      }
    }
  }

  if (detail_level>2) {
    for (int i=0; i<2; i++) {
      for (int ii=0; ii<hscalarEt[0].size(); ii++) {
        if((hscalarEt[i])[ii]) (hscalarEt[i])[ii]=(hscalarEt[i])[ii]->Rebin(4);
      }
    }
    //
    for(int iplot=0; iplot<nplots_part3; iplot++) {

      //      cout << "Plotting: "<<plot_part3[iplot].cname<<endl;

      // avoid blank pages for non-existing histograms
      if((plot_part3[iplot].vect)[0].size() && (plot_part3[iplot].vect)[1].size()) {
	plot_util(plot_part3[iplot].cname, (plot_part3[iplot].vect)[0], (plot_part3[iplot].vect)[1], make_chi2,
		  plot_part3[iplot].rangeX[0], plot_part3[iplot].rangeX[1], ps, plots_per_page, zeecomp );
      }
    }
  }

  ps->Close();
  zeecomp->Write("All");
  zeecomp->Close();
}

void getHistogramsFromData(TFile *f, int index, bool is_fullMC) {
  f -> cd("ZCand_Hist");

  char name[50];
  for(int i=0; i<4; i++) {

    if(i==0) sprintf(name, "%s", "ZCandMass");
    else if(i==1) sprintf(name, "%s", "ZCandMass_CCCC_Trks");
    else if(i==2) sprintf(name, "%s", "ZCandMass_CCEC_Trks");
    else if(i==3) sprintf(name, "%s", "ZCandMass_ECEC_Trks");
    mass[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandDiffMass");
    else sprintf(name, "%s%d", "ZCandDiffMass_", i-1);
    diffmass[index].push_back((TH1 *)gROOT->FindObject(name));
    
    if(i==0) sprintf(name, "%s", "ZCandElecPt");
    else sprintf(name, "%s%d", "ZCandElecPt_", i-1);
    elecpt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    if(i==0) sprintf(name, "%s", "ZCandElec0Pt");
    else sprintf(name, "%s%d", "ZCandElec0Pt_", i-1);
    elec0pt[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElec1Pt");
    else sprintf(name, "%s%d", "ZCandElec1Pt_", i-1);
    elec1pt[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElecE");
    else sprintf(name, "%s%d", "ZCandElecE_", i-1);
    elece[index].push_back((TH1 *)gROOT->FindObject(name));
    
    if(i==0) sprintf(name, "%s", "ZCandElec0E");
    else sprintf(name, "%s%d", "ZCandElec0E_", i-1);
    elec0e[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElec1E");
    else sprintf(name, "%s%d", "ZCandElec1E_", i-1);
    elec1e[index].push_back((TH1 *)gROOT->FindObject(name));

    if(is_fullMC) { // only fill these for FULL MC file, not REAL DATA
      if(i==0) sprintf(name, "%s", "ZCandElecGenPt");
      else sprintf(name, "%s%d", "ZCandElecGenPt_", i-1);
      elecgenpt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecGen0Pt");
      else sprintf(name, "%s%d", "ZCandElecGen0Pt_", i-1);
      elecgen0pt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecGen1Pt");
      else sprintf(name, "%s%d", "ZCandElecGen1Pt_", i-1);
      elecgen1pt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecRawGenPt");
      else sprintf(name, "%s%d", "ZCandElecRawGenPt_", i-1);
      elecrawgenpt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecRawGen0Pt");
      else sprintf(name, "%s%d", "ZCandElecRawGen0Pt_", i-1);
      elecrawgen0pt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecRawGen1Pt");
      else sprintf(name, "%s%d", "ZCandElecRawGen1Pt_", i-1);
      elecrawgen1pt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandDiffElecPt");
      else sprintf(name, "%s%d", "ZCandDiffElecPt_", i-1);
      diffelecpt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandDiffElec0Pt");
      else sprintf(name, "%s%d", "ZCandDiffElec0Pt_", i-1);
      diffelec0pt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandDiffElec1Pt");
      else sprintf(name, "%s%d", "ZCandDiffElec1Pt_", i-1);
      diffelec1pt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecGenE");
      else sprintf(name, "%s%d", "ZCandElecGenE_", i-1);
      elecgene[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecGen0E");
      else sprintf(name, "%s%d", "ZCandElecGen0E_", i-1);
      elecgen0e[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecGen1E");
      else sprintf(name, "%s%d", "ZCandElecGen1E_", i-1);
      elecgen1e[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecRawGenE");
      else sprintf(name, "%s%d", "ZCandElecRawGenE_", i-1);
      elecrawgene[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecRawGen0E");
      else sprintf(name, "%s%d", "ZCandElecRawGen0E_", i-1);
      elecrawgen0e[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandElecRawGen1E");
      else sprintf(name, "%s%d", "ZCandElecRawGen1E_", i-1);
      elecrawgen1e[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandDiffElecE");
      else sprintf(name, "%s%d", "ZCandDiffElecE_", i-1);
      diffelece[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandDiffElec0E");
      else sprintf(name, "%s%d", "ZCandDiffElec0E_", i-1);
      diffelec0e[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandDiffElec1E");
      else sprintf(name, "%s%d", "ZCandDiffElec1E_", i-1);
      diffelec1e[index].push_back((TH1 *)gROOT->FindObject(name));
    }
    
    if(i==0) sprintf(name, "%s", "ZCandElecEta");
    else sprintf(name, "%s%d", "ZCandElecEta_", i-1);
    eleceta[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElecDetEta");
    else sprintf(name, "%s%d", "ZCandElecDetEta_", i-1);
    elecdeteta[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElecPhi");
    else sprintf(name, "%s%d", "ZCandElecPhi_", i-1);
    elecphi[index].push_back((TH1 *)gROOT->FindObject(name));
#ifdef MORE_ELECTRON_PHI_HISTOGRAMS
    if(i==0) sprintf(name, "%s", "ZCandElecPhiTrkAtDCA", i);
    else sprintf(name, "%s%d", "ZCandElecPhiTrkAtDCA_", i-1);
    elecphitrkatdca[index].push_back((TH1 *)gROOT->FindObject(name));
    if(i==0) sprintf(name, "%s", "ZCandElecPhiTrkAtEM3", i);
    else sprintf(name, "%s%d", "ZCandElecPhiTrkAtEM3_", i-1);
    elecphitrkatem3[index].push_back((TH1 *)gROOT->FindObject(name));
    if(i==0) sprintf(name, "%s", "ZCandElecDetPhiCALO", i);
    else sprintf(name, "%s%d", "ZCandElecDetPhiCALO_", i-1);
    elecdetphicalo[index].push_back((TH1 *)gROOT->FindObject(name));
#endif
    if(i==0) sprintf(name, "%s", "ZCandMet");
    else sprintf(name, "%s%d", "ZCandMet_", i-1);
    met[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandPt");
    else sprintf(name, "%s%d", "ZCandPt_", i-1);
    Zpt[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandPhi");
    else sprintf(name, "%s%d", "ZCandPhi_", i-1);
    Zphi[index].push_back((TH1 *)gROOT->FindObject(name));

    if(is_fullMC) { // only fill these for FULL MC file, not REAL DATA
      if(i==0) sprintf(name, "%s", "ZCandMCPt");
      else sprintf(name, "%s%d", "ZCandMCPt_", i-1);
      genZpt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandMCPtDiff");
      else sprintf(name, "%s%d", "ZCandMCPtDiff_", i-1);
      Delta_genZpt_Zpt[index].push_back((TH1 *)gROOT->FindObject(name));

      if(i==0) sprintf(name, "%s", "ZCandMCPhiDiff");
      else sprintf(name, "%s%d", "ZCandMCPhiDiff_", i-1);
      Delta_genZphi_Zphi[index].push_back((TH1 *)gROOT->FindObject(name));
    }

    if(i==0) sprintf(name, "%s", "ZCandRecoilPt");
    else sprintf(name, "%s%d", "ZCandRecoilPt_", i-1);
    ZRecoilpt[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandRecoilPhi");
    else sprintf(name, "%s%d", "ZCandRecoilPhi_", i-1);
    ZRecoilphi[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandRecoilPx");
    else sprintf(name, "%s%d", "ZCandRecoilPx_", i-1);
    ZRecoilpx[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandRecoilPy");
    else sprintf(name, "%s%d", "ZCandRecoilPy_", i-1);
    ZRecoilpy[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandMetPhi");
    else sprintf(name, "%s%d", "ZCandMetPhi_", i-1);
    metphi[index].push_back((TH1 *)gROOT->FindObject(name));


    if(i==0) sprintf(name, "%s", "ZCandElecTrkPhiModEM3");
    else sprintf(name, "%s%d", "ZCandElecPhiEM3Mod_", i-1);
    hzcandelectrkphiem3mod[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandMetX");
    else sprintf(name, "%s%d", "ZCandMetX_", i-1);
    metx[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandMetY");
    else sprintf(name, "%s%d", "ZCandMetY_", i-1);
    mety[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandVtx");
    else sprintf(name, "%s%d", "ZCandVtx_", i-1);
    Vtx[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElecTrkPt");
    else sprintf(name, "%s%d", "ZCandElecTrkPt_", i-1);
    TrkPt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    if(i==0) sprintf(name, "%s", "ZCandElecTrkPtOvE");
    else sprintf(name, "%s%d", "ZCandElecTrkPtOvE_", i-1);
    TrkPtOvE[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElecTrkCalMass");
    else sprintf(name, "%s%d", "ZCandElecTrkCalMass_", i-1);
    TrkCalMass[index].push_back((TH1 *)gROOT->FindObject(name));
      
     if(i==0) sprintf(name, "%s", "ZCandElecTrkPtTight");
    else sprintf(name, "%s%d", "ZCandElecTrkPtTight_", i-1);
    TrkPtTight[index].push_back((TH1 *)gROOT->FindObject(name));
    
    if(i==0) sprintf(name, "%s", "ZCandElecTrkPtOvETight");
    else sprintf(name, "%s%d", "ZCandElecTrkPtOvETight_", i-1);
    TrkPtOvETight[index].push_back((TH1 *)gROOT->FindObject(name));  

    if(i==0) sprintf(name, "%s", "ZCandElecUPara");
    else sprintf(name, "%s%d", "ZCandElecUPara_", i-1);
    elecupara[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElecUPerp");
    else sprintf(name, "%s%d", "ZCandElecUPerp_", i-1);
    elecuperp[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandInstLumi");
    else sprintf(name, "%s%d", "ZCandInstLumi_", i-1);
    instlumi[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandScalarEt");
    else sprintf(name, "%s%d", "ZCandScalarEt_", i-1);
    scalarEt[index].push_back((TH1 *)gROOT->FindObject(name));
#ifdef MORE_ZB_PLOTS
    if(is_fullMC) {
      if(i==0) sprintf(name, "%s", "ZCandScalarEt_ZB");
      else sprintf(name, "%s%d", "ZCandScalarEt_ZB_", i-1);
      TH1* ahist = (TH1 *)gROOT->FindObject(name);
      scalarEtZB[index].push_back(ahist);
 
      char ahist2name[100];
      if(i==0) sprintf(ahist2name, "%s", "ZCandScalarEt_ZBNoScale");
      else sprintf(ahist2name, "%s%d", "ZCandScalarEt_ZBNoScale_", i-1);
      TH1* ahist2 = (TH1*)ahist->Clone(ahist2name);
      ahist2->SetTitle(ahist2name);
      scalarEtZBNoScale[index].push_back(ahist2);
    }
#endif
    if(i==0) sprintf(name, "%s", "ZCandDeltaPhi_EM_Recoil");
    else sprintf(name, "%s%d", "ZCandDeltaPhi_EM_Recoil_", i-1);
    deltaphi_emrecoil[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandDeltaPhi_EM_Met");
    else sprintf(name, "%s%d", "ZCandDeltaPhi_EM_Met_", i-1);
    deltaphi_emmet[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandCosDeltaPhi_EM1_EM2");
    else sprintf(name, "%s%d", "ZCandCosDeltaPhi_EM1_EM2_", i-1);
    cosdeltaphi_em1em2[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandDiffCosDeltaPhi_EM1_EM2");
    else sprintf(name, "%s%d", "ZCandDiffCosDeltaPhi_EM1_EM2_", i-1);
    diffcosdeltaphi_em1em2[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandDeltaEta_EM1_EM2");
    else sprintf(name, "%s%d", "ZCandDeltaEta_EM1_EM2_", i-1);
    deltaeta_em1em2[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandDiffDeltaEta_EM1_EM2");
    else sprintf(name, "%s%d", "ZCandDiffDeltaEta_EM1_EM2_", i-1);
    diffdeltaeta_em1em2[index].push_back((TH1 *)gROOT->FindObject(name));

    // Recoil plots for DATA
    if(i==0) sprintf(name, "%s", "ZCandEtaBalance");
    else sprintf(name, "%s%d", "ZCandEtaBalance_", i-1);
    balance1[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandXiBalance");
    else sprintf(name, "%s%d", "ZCandXiBalance_", i-1);
    balance2[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandEtaImBalance");
    else sprintf(name, "%s%d", "ZCandEtaImBalance_", i-1);
    balance3[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandXiImBalance");
    else sprintf(name, "%s%d", "ZCandXiImBalance_", i-1);
    balance4[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandEtaPeeRecoil");
    else sprintf(name, "%s%d", "ZCandEtaPeeRecoil_", i-1);
    peerecoprofile[index].push_back((TProfile *)gROOT->FindObject(name));
   
    if(i==0) sprintf(name, "%s", "ZCandEtaPeeBalance");
    else sprintf(name, "%s%d", "ZCandEtaPeeBalance_", i-1);
    peebalanceprofile[index].push_back((TProfile *)gROOT->FindObject(name));
    
    if(i==0) sprintf(name, "%s", "ZCandKappaUE");
    else sprintf(name, "%s%d", "ZCandKappaUE_", i-1);
    kappa3profile[index].push_back((TProfile *)gROOT->FindObject(name));

#ifdef MORE_PEE_HISTOGRAMS
 
 if(i==0) sprintf(name, "%s", "ZCandPx");
    else sprintf(name, "%s%d", "ZCandPx_", i-1);
    Zpx[index].push_back((TH1 *)gROOT->FindObject(name));

 if(i==0) sprintf(name, "%s", "ZCandPy");
    else sprintf(name, "%s%d", "ZCandPy_", i-1);
    Zpy[index].push_back((TH1 *)gROOT->FindObject(name));

 if(i==0) sprintf(name, "%s", "ZCandPz");
    else sprintf(name, "%s%d", "ZCandPz_", i-1);
    Zpz[index].push_back((TH1 *)gROOT->FindObject(name));

  
    if(i==0) sprintf(name, "%s", "ZCandElecPx");
    else sprintf(name, "%s%d", "ZCandElecPx_", i-1);
    elecpx[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElecPy");
    else sprintf(name, "%s%d", "ZCandElecPy_", i-1);
    elecpy[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElecPz");
    else sprintf(name, "%s%d", "ZCandElecPz_", i-1);
    elecpz[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElec0Px");
    else sprintf(name, "%s%d", "ZCandElec0Px_", i-1);
    elec0px[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElec0Py");
    else sprintf(name, "%s%d", "ZCandElec0Py_", i-1);
    elec0py[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElec0Pz");
    else sprintf(name, "%s%d", "ZCandElec0Pz_", i-1);
    elec0pz[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElec1Px");
    else sprintf(name, "%s%d", "ZCandElec1Px_", i-1);
    elec1px[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandElec1Py");
    else sprintf(name, "%s%d", "ZCandElec1Py_", i-1);
    elec1py[index].push_back((TH1 *)gROOT->FindObject(name));


    if(i==0) sprintf(name, "%s", "ZCandElec1Pz");
    else sprintf(name, "%s%d", "ZCandElec1Pz_", i-1);
    elec1pz[index].push_back((TH1 *)gROOT->FindObject(name));

  
    if(i==0) sprintf(name, "%s", "ZCandDeltaPhi_EM1_EM2");
    else sprintf(name, "%s%d", "ZCandDeltaPhi_EM1_EM2_", i-1);
    hZdeltaphi[index].push_back((TH1 *)gROOT->FindObject(name));

    if(i==0) sprintf(name, "%s", "ZCandPee_eta");
    else sprintf(name, "%s%d", "ZCandPee_eta_", i-1);
    hZpeeeta[index].push_back((TH1 *)gROOT->FindObject(name));
    

#endif

  }

  // PLOTS IN BINS OF PT(ee)
  for(int i=0; i<10; i++) {
#ifdef MORE_PEE_HISTOGRAMS
    sprintf(name, "%s%d", "ZCandPee_eta_bin_", i);
    hpeeetabin[index].push_back((TH1 *)gROOT->FindObject(name));
#endif

    sprintf(name, "%s%d", "ZCandEtaImBalance_bin_", i);
    hetaimbalance[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandXiImBalance_bin_", i);
    hxiimbalance[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandPt_bin_", i);
    hZpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandPhi_bin_", i);
    hZphi[index].push_back((TH1 *)gROOT->FindObject(name));

    if(is_fullMC) { // only fill these for FULL MC file, not REAL DATA
      sprintf(name, "%s%d", "ZCandMCPtDiff_bin_", i);
      hDelta_genZpt_Zpt[index].push_back((TH1 *)gROOT->FindObject(name));
      sprintf(name, "%s%d", "ZCandMCPhiDiff_bin_", i);
      hDelta_genZphi_Zphi[index].push_back((TH1 *)gROOT->FindObject(name));
      sprintf(name, "%s%d", "ZCandMass_bin_", i);
      hMass[index].push_back((TH1 *)gROOT->FindObject(name));
      sprintf(name, "%s%d", "ZCandDiffMass_bin_", i);
      hdiffMass[index].push_back((TH1 *)gROOT->FindObject(name));
    }

    sprintf(name, "%s%d", "ZCandRecoilPt_bin_", i);
    hrecoilpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandRecoilPhi_bin_", i);
    hrecoilphi[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandMet_bin_", i);
    hmet[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandMetPhi_bin_", i);
    hmetphi[index].push_back((TH1 *)gROOT->FindObject(name));
    

    sprintf(name, "%s%d", "ZCandDeltaPhi_Z_Recoil_bin_", i);
    hdeltaPhi_Z_Recoil[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDeltaPhi_Z_Met_bin_", i);
    hdeltaPhi_Z_Met[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandCosDeltaPhi_EM1_EM2_bin_", i);
    hCosDeltaPhi_EM1EM2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDiffCosDeltaPhi_EM1_EM2_bin_", i);
    hDiffCosDeltaPhi_EM1EM2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDeltaEta_EM1_EM2_bin_", i);
    hDeltaEta_EM1EM2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDiffDeltaEta_EM1_EM2_bin_", i);
    hDiffDeltaEta_EM1EM2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecPt_bin_", i);
    helecpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElec0Pt_bin_", i);
    helec0pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElec1Pt_bin_", i);
    helec1pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecGenPt_bin_", i);
    helecgenpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecGen0Pt_bin_", i);
    helecgen0pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecGen1Pt_bin_", i);
    helecgen1pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecRawGenPt_bin_", i);
    helecrawgenpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecRawGen0Pt_bin_", i);
    helecrawgen0pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecRawGen1Pt_bin_", i);
    helecrawgen1pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDiffElecPt_bin_", i);
    hdiffelecpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDiffElec0Pt_bin_", i);
    hdiffelec0pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDiffElec1Pt_bin_", i);
    hdiffelec1pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecE_bin_", i);
    helece[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElec0E_bin_", i);
    helec0e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElec1E_bin_", i);
    helec1e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecGenE_bin_", i);
    helecgene[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecGen0E_bin_", i);
    helecgen0e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecGen1E_bin_", i);
    helecgen1e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecRawGenE_bin_", i);
    helecrawgene[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecRawGen0E_bin_", i);
    helecrawgen0e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecRawGen1E_bin_", i);
    helecrawgen1e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDiffElecE_bin_", i);
    hdiffelece[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDiffElec0E_bin_", i);
    hdiffelec0e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandDiffElec1E_bin_", i);
    hdiffelec1e[index].push_back((TH1 *)gROOT->FindObject(name));

    TH1 *h;
    if( (sprintf(name, "%s%d", "ZCandScalarEt_ZPtBin_", i) && (h=(TH1 *)gROOT->FindObject(name))) ||
	(sprintf(name, "%s%d", "ZCandScalarEt_bin_", i) && (h=(TH1 *)gROOT->FindObject(name)))      )
      hscalarEt[index].push_back(h);
  }
  
  // PLOTS PER PHYSICS ETA CATEGORY
  for(int i=0; i<=14; i++) {
    sprintf(name, "%s%d", "ZCandMass_TwoTrks_Category_", i);
    Mass_Category[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "ZCandElecPt_TwoTrks_Category_", i);
    ElecPt_Category[index].push_back((TH1 *)gROOT->FindObject(name));
  }

  // PLOTS PER PHIMOD CATEGORY
  for(int i=0; i<=14; i++) {
    sprintf(name, "%s%d", "ZCandMass_CCCC_TrkPhiEM3ModCategory_", i);
    Mass_PhiModCategory[index].push_back((TH1 *)gROOT->FindObject(name));
  }

}

void getHistogramsFromPMCS(TFile *f, int index) {
  f -> cd("smeared");
  
  char name[50];
  string temp;
  for(int i=0; i<4; i++) {
    if(i==0)           temp = string("All");
    else if(i==1)      temp = string("CCCC");
    else if(i==2)      temp = string("CCEC");
    else if(i==3)      temp = string("ECEC");
 
    sprintf(name, "%s%s", "smeared_hZcandMass_", temp.c_str());
    mass[index].push_back((TH1 *)gROOT->FindObject(name));
   
    sprintf(name, "%s%s", "smeared_hZcandDiffMass_", temp.c_str());
    diffmass[index].push_back((TH1 *)gROOT->FindObject(name));
   
    sprintf(name, "%s%s", "smeared_hZcandElecpT_", temp.c_str());
    elecpt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElec0pT_", temp.c_str());
    elec0pt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElec1pT_", temp.c_str());
    elec1pt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecGenpT_", temp.c_str());
    elecgenpt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecGen0pT_", temp.c_str());
    elecgen0pt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecGen1pT_", temp.c_str());
    elecgen1pt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecRawGenpT_", temp.c_str());
    elecrawgenpt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecRawGen0pT_", temp.c_str());
    elecrawgen0pt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecRawGen1pT_", temp.c_str());
    elecrawgen1pt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandDiffElecpT_", temp.c_str());
    diffelecpt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandDiffElec0pT_", temp.c_str());
    diffelec0pt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandDiffElec1pT_", temp.c_str());
    diffelec1pt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecE_", temp.c_str());
    elece[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElec0E_", temp.c_str());
    elec0e[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElec1E_", temp.c_str());
    elec1e[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecGenE_", temp.c_str());
    elecgene[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecGen0E_", temp.c_str());
    elecgen0e[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecGen1E_", temp.c_str());
    elecgen1e[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecRawGenE_", temp.c_str());
    elecrawgene[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecRawGen0E_", temp.c_str());
    elecrawgen0e[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecRawGen1E_", temp.c_str());
    elecrawgen1e[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandDiffElecE_", temp.c_str());
    diffelece[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandDiffElec0E_", temp.c_str());
    diffelec0e[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandDiffElec1E_", temp.c_str());
    diffelec1e[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecEta_", temp.c_str());
    eleceta[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElecDetEta_", temp.c_str());
    elecdeteta[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElecPhi_", temp.c_str());
    elecphi[index].push_back((TH1 *)gROOT->FindObject(name));

#ifdef MORE_ELECTRON_PHI_HISTOGRAMS
    sprintf(name, "%s%s", "smeared_hZcandElecPhiTrkAtDCA_", temp.c_str());
    elecphitrkatdca[index].push_back((TH1 *)gROOT->FindObject(name));
    sprintf(name, "%s%s", "smeared_hZcandElecPhiTrkAtEM3_", temp.c_str());
    elecphitrkatem3[index].push_back((TH1 *)gROOT->FindObject(name));
    sprintf(name, "%s%s", "smeared_hZcandElecDetPhiCALO_", temp.c_str());
    elecdetphicalo[index].push_back((TH1 *)gROOT->FindObject(name));
#endif

    sprintf(name, "%s%s", "smeared_hZcandMET_", temp.c_str());
    met[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandPt_", temp.c_str());
    Zpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandPhi_", temp.c_str());
    Zphi[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandMCPt_", temp.c_str());
    genZpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandMCPtDiff_", temp.c_str());
    Delta_genZpt_Zpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandMCPhiDiff_", temp.c_str());
    Delta_genZphi_Zphi[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandRecoilPt_", temp.c_str());
    ZRecoilpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandRecoilPhi_", temp.c_str());
    ZRecoilphi[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandRecoilPx_", temp.c_str());
    ZRecoilpx[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandRecoilPy_", temp.c_str());
    ZRecoilpy[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandMETPhi_", temp.c_str());
    metphi[index].push_back((TH1 *)gROOT->FindObject(name));



    sprintf(name, "%s%s", "smeared_hZcandElecTrkPhiModEM3_", temp.c_str());
    hzcandelectrkphiem3mod[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandMETx_", temp.c_str());
    metx[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandMETy_", temp.c_str());
    mety[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandVtx_", temp.c_str());
    Vtx[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElecTrkPtOvE_", temp.c_str());
    TrkPtOvE[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecTrkPtOvETight_", temp.c_str());
    TrkPtOvETight[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElecTrkPt_", temp.c_str());
    TrkPt[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandElecTrkPtTight_", temp.c_str());
    TrkPtTight[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElecTrkCalMass_", temp.c_str());
    TrkCalMass[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElecUpara_", temp.c_str());
    elecupara[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElecUperp_", temp.c_str());
    elecuperp[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandLumi_", temp.c_str());
    instlumi[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandScalarEt_", temp.c_str());
    scalarEt[index].push_back((TH1 *)gROOT->FindObject(name));
#ifdef MORE_ZB_PLOTS
    sprintf(name, "%s%s", "smeared_hZcandScalarEtZB_", temp.c_str());
    scalarEtZB[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandScalarEtZBNoScale_", temp.c_str());
    scalarEtZBNoScale[index].push_back((TH1 *)gROOT->FindObject(name));
#endif
    sprintf(name, "%s%s", "smeared_hZcandDeltaPhi_EM_Recoil_", temp.c_str());
    deltaphi_emrecoil[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandDeltaPhi_EM_Met_", temp.c_str());
    deltaphi_emmet[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandCosDeltaPhi_EM1_EM2_", temp.c_str());
    cosdeltaphi_em1em2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandDiffCosDeltaPhi_EM1_EM2_", temp.c_str());
    diffcosdeltaphi_em1em2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandDeltaEta_EM1_EM2_", temp.c_str());
    deltaeta_em1em2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandDiffDeltaEta_EM1_EM2_", temp.c_str());
    diffdeltaeta_em1em2[index].push_back((TH1 *)gROOT->FindObject(name));

    //Recoil plots for PMCS
    sprintf(name, "%s%s", "smeared_hZcandEtaBalance_", temp.c_str());
    balance1[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandXiBalance_", temp.c_str());
    balance2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandEtaImBalance_", temp.c_str());
    balance3[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandXiImBalance_", temp.c_str());
    balance4[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandPeeRecoProfile_", temp.c_str());
    peerecoprofile[index].push_back((TProfile *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandPeeBalanceProfile_", temp.c_str());
    peebalanceprofile[index].push_back((TProfile *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandKappa3Profile_", temp.c_str());
    kappa3profile[index].push_back((TProfile *)gROOT->FindObject(name));

#ifdef MORE_PEE_HISTOGRAMS

  sprintf(name, "%s%s", "smeared_hZcandPx_", temp.c_str());
    Zpx[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandPy_", temp.c_str());
    Zpy[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "smeared_hZcandPz_", temp.c_str());
    Zpz[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElecpX_", temp.c_str());
    elecpx[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElecpY_", temp.c_str());
    elecpy[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElecpZ_", temp.c_str());
    elecpz[index].push_back((TH1 *)gROOT->FindObject(name));


    sprintf(name, "%s%s", "smeared_hZcandElec0pX_", temp.c_str());
    elec0px[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElec0pY_", temp.c_str());
    elec0py[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElec0pZ_", temp.c_str());
    elec0pz[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElec1pX_", temp.c_str());
    elec1px[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElec1pY_", temp.c_str());
    elec1py[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "smeared_hZcandElec1pZ_", temp.c_str());
    elec1pz[index].push_back((TH1 *)gROOT->FindObject(name));


    sprintf(name, "%s%s", "smeared_hZcandPee_eta_",  temp.c_str());
    hZpeeeta[index].push_back((TH1 *)gROOT->FindObject(name));
   
    sprintf(name, "%s%s", "smeared_hZcandDeltaPhi_EM1_EM2_",  temp.c_str());
    hZdeltaphi[index].push_back((TH1 *)gROOT->FindObject(name));

    

#endif



  }

  // PLOTS IN BINS OF PT(ee)
  for(int i=0; i<10; i++) {
#ifdef MORE_PEE_HISTOGRAMS
    sprintf(name, "%s%d", "smeared_hZcandPee_eta_bin_", i);
    hpeeetabin[index].push_back((TH1 *)gROOT->FindObject(name));
#endif
    sprintf(name, "%s%d", "smeared_hZcandEtaImBalance_bin_", i);
    hetaimbalance[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandXiImBalance_bin_", i);
    hxiimbalance[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandPt_bin_", i);
    hZpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandPhi_bin_", i);
    hZphi[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandMCPtDiff_bin_", i);
    hDelta_genZpt_Zpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandMCPhiDiff_bin_", i);
    hDelta_genZphi_Zphi[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandMass_bin_", i);
    hMass[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDiffMass_bin_", i);
    hdiffMass[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandRecoilPt_bin_", i);
    hrecoilpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandRecoilPhi_bin_", i);
    hrecoilphi[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandMET_bin_", i);
    hmet[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandMETPhi_bin_", i);
    hmetphi[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDeltaPhi_Z_Recoil_bin_", i);
    hdeltaPhi_Z_Recoil[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDeltaPhi_Z_Met_bin_", i);
    hdeltaPhi_Z_Met[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandCosDeltaPhi_EM1_EM2_bin_", i);
    hCosDeltaPhi_EM1EM2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDiffCosDeltaPhi_EM1_EM2_bin_", i);
    hDiffCosDeltaPhi_EM1EM2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDeltaEta_EM1_EM2_bin_", i);
    hDeltaEta_EM1EM2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDiffDeltaEta_EM1_EM2_bin_", i);
    hDiffDeltaEta_EM1EM2[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecpT_bin_", i);
    helecpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElec0pT_bin_", i);
    helec0pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElec1pT_bin_", i);
    helec1pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecGenpT_bin_", i);
    helecgenpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecGen0pT_bin_", i);
    helecgen0pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecGen1pT_bin_", i);
    helecgen1pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecRawGenpT_bin_", i);
    helecrawgenpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecRawGen0pT_bin_", i);
    helecrawgen0pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecRawGen1pT_bin_", i);
    helecrawgen1pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDiffElecpT_bin_", i);
    hdiffelecpt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDiffElec0pT_bin_", i);
    hdiffelec0pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDiffElec1pT_bin_", i);
    hdiffelec1pt[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecE_bin_", i);
    helece[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElec0E_bin_", i);
    helec0e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElec1E_bin_", i);
    helec1e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecGenE_bin_", i);
    helecgene[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecGen0E_bin_", i);
    helecgen0e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecGen1E_bin_", i);
    helecgen1e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecRawGenE_bin_", i);
    helecrawgene[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecRawGen0E_bin_", i);
    helecrawgen0e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecRawGen1E_bin_", i);
    helecrawgen1e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDiffElecE_bin_", i);
    hdiffelece[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDiffElec0E_bin_", i);
    hdiffelec0e[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandDiffElec1E_bin_", i);
    hdiffelec1e[index].push_back((TH1 *)gROOT->FindObject(name));

    TH1 *h;
    if( (sprintf(name, "%s%d", "smeared_hZcandScalarEt_CCCC_ZPtBin_", i) && (h=(TH1 *)gROOT->FindObject(name))) ||
	(sprintf(name, "%s%d", "smeared_hZcandScalarEt_CCCC_bin_", i) && (h=(TH1 *)gROOT->FindObject(name)))      )
      hscalarEt[index].push_back(h);
  }

  // PLOTS PER PHYSICS ETA CATEGORY
  for(int i=0; i<=14; i++) {
    sprintf(name, "%s%d", "smeared_hZcandMass_Category_", i);
    Mass_Category[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "smeared_hZcandElecPt_Category_", i);
    ElecPt_Category[index].push_back((TH1 *)gROOT->FindObject(name));
  }

  // PLOTS PER PHIMOD CATEGORY
  for(int i=0; i<=14; i++) {
    // AM switched to using histograms based on trkEM3 PhiMod rather than TruePhiMod
    //sprintf(name, "%s%d", "smeared_hZcandMass_Category_TruePhiMod_", i);  // here we are making the assumption that tracking is (spatially) infinitely precise
    sprintf(name, "%s%d", "smeared_hZcandMass_Category_PhiMod_", i);  
    Mass_PhiModCategory[index].push_back((TH1 *)gROOT->FindObject(name));
  }

}
