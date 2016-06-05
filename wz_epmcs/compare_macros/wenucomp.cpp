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
#include <cassert>

#include "plot_util.cpp"
#include "wmass_blinding_util/BlindingAuthority.hpp"
#include "PParameterReader.hpp"

#define MORE_ELECTRON_PHI_HISTOGRAMS 
//#define MORE_ZB_PLOTS

using namespace std;
using namespace plot;


vector<TH1 *> mass[3], Wpt[3], Wvertex[3], Wphi[3], TrueWpt[3];
vector<TH1 *> elecpt[3], eleceta[3], elecdeteta[3], elecphi[3], elecdetphi[3];
vector<TH1 *> elecphitrkatdca[3], elecphitrkatem3[3], elecdetphicalo[3];
vector<TH1 *> met[3], metx[3], mety[3], metphi[3], instlumi[3], scalarEt[3], upara[3], uperp[3];
vector<TH1 *> scalarEtZB[3], scalarEtZBNoScale[3];
vector<TH1 *> WRecoilpt[3], WRecoilpx[3], WRecoilpy[3], WRecoilphi[3];
vector<TH1 *> deltaphi_emmet[3], deltaphi_emrecoil[3], deltaphi_metrecoil[3];
vector<TH1 *> electrkpt[3], electrkptove[3], electrkphiem3mod[3];

vector<TH1 *> mass_spatial[3], Wpt_spatial[3], Wvertex_spatial[3], Wphi_spatial[3], TrueWpt_spatial[3];
vector<TH1 *> elecpt_spatial[3], eleceta_spatial[3], elecdeteta_spatial[3], elecphi_spatial[3], elecdetphi_spatial[3];
vector<TH1 *> elecphitrkatdca_spatial[3], elecphitrkatem3_spatial[3], elecdetphicalo_spatial[3];
vector<TH1 *> met_spatial[3], metx_spatial[3], mety_spatial[3], metphi_spatial[3], instlumi_spatial[3], scalarEt_spatial[3], upara_spatial[3], uperp_spatial[3];
vector<TH1 *> scalarEtZB_spatial[3], scalarEtZBNoScale_spatial[3];
vector<TH1 *> WRecoilpt_spatial[3], WRecoilpx_spatial[3], WRecoilpy_spatial[3], WRecoilphi_spatial[3];
vector<TH1 *> deltaphi_emmet_spatial[3], deltaphi_emrecoil_spatial[3], deltaphi_metrecoil_spatial[3];
vector<TH1 *> electrkpt_spatial[3], electrkptove_spatial[3], electrkphiem3mod_spatial[3];

vector<TH1 *> mtoverlay[3], eptoverlay[3], metoverlay[3], wptoverlay[3];
vector<TH1 *> mtoverlay_spatial[3], eptoverlay_spatial[3], metoverlay_spatial[3], wptoverlay_spatial[3];
vector<TH1 *> utbin[3], utbin_spatial[3];
vector<TH1 *> profiles[3];

vector<TH1 *> WMCPt_CC_bin[3], WRecoilPt_CC_bin[3];
vector<TH1 *> WMCPt_CC_bin_spatial[3], WRecoilPt_CC_bin_spatial[3];

vector<TH1 *> WCandTrueUPara[3], WCandTrueUPerp[3];
vector<TH1 *> WCandTrueUPara_Spatial[3], WCandTrueUPerp_Spatial[3];
vector<TH1 *> WCandResoUPara[3], WCandResoUPerp[3];
vector<TH1 *> WCandResoUPara_Spatial[3], WCandResoUPerp_Spatial[3];

vector<TFile *> file_bkgd;

// if is_fullMC=TRUE then treat this file as from FULL MC not REAL DATA
void getHistogramsFromData(TFile *f, int index, bool is_fullMC);
void getHistogramsFromPMCS(TFile *f, int index, BlindingAuthority* BA);
void getHistogramsFromBackgrounds(vector<TFile *> vect, int index, bool is_fullMC);


int main(int argc, char** argv) {

  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  TPostScript *ps = new TPostScript("histogramswenu.ps");
  TFile *wenucomp = new TFile("wenucomp.root", "recreate");
  TCanvas *c1 =  new TCanvas("aaa","c1",50,10,700,800);    // these 2 crazy lines are needed
  ps->NewPage();                                           // for proper alignment of the 1st page

  TString data_file = argv[1];
  TString mc_file = argv[2];

  if(argc!=6 && argc!=7 && argc!=8 && argc!=9 && argc!=11) { //need to have both param + option to run
    cout<<" Please run it the following way: " << endl
	<<" ./wenucomp  <first_root_file_name>  <second_root_file_name>  <make_chi2_option>  <compare_option>  <mc_or_data>  <qcd_bkg_type> <rows_per_page>  [blind_W_mass] <parameters file> <background run_bin option>"
	<<endl<<endl;  
    cout<<" If <make_chi2_option>=1 then CHI plots will be created too."<<endl;  
    cout<<" Use <compare_option>=0  for comparing DATA with Fast-MC (PMCS),"<<endl
	<<"     <compare_option>=1  for comparing DATA with DATA,"<<endl
	<<"     <compare_option>=2  for comparing Fast-MC (PMCS) with Fast-MC (PMCS),"<<endl 
        <<"     <compare_option>=3  for comparing Full-MC (GEANT) with Fast-MC (PMCS)," << endl
        <<"     <compare_option>=4  for comparing Full-MC (GEANT) with Full-MC (GEANT)." << endl
        <<"     <compare_option>=5  for comparing DATA with Full-MC (GEANT)." << endl << endl;
    cout<<" Use <mc_or_data>=0 for comparing DATA (background subtracted) with Fast-MC,"<<endl  
	<<"     <mc_or_data>=1 for comparing Full-MC (no background subtraction) with Fast-MC."<<endl << endl;
    cout<<" Use <qcd_bkg_type> to select either the matrix method (0 using constant eff and fake rate, "<<endl;
    cout<<"                1 using deteta- and pT-dependent eff and fake rate) or read from a histogram (2)"<<endl<<endl;
    cout<<" For example: ./wenucomp  data.root     fastmc.root   0 0  0  1 0 81.40 parameters.master run3_all"<<endl
        <<"              ./wenucomp  data1.root    data2.root    0 1  1"<<endl
        <<"              ./wenucomp  fastmc1.root  fastmc2.root  0 2  1"<<endl
        <<"              ./wenucomp  fullmc.root   fastmc.root   0 3  1"<<endl
        <<"              ./wenucomp  fullmc1.root  fullmc2.root  0 4  1"<<endl
		<<"		         ./wenucomp  data.root     fullmc.root   0 5  0"<<endl
		<<"------------------------------------------------------------"<<endl
		<<"for comparisons involving Run2B wenu pmcs please use <qcd_bkg_type> option 1 "<<endl<<endl
	<<"FOR FULL LIST OF BACKGROUND CUT OPTIONS, SEE background_options.txt"<<endl<<endl;

    return 1;
  }

  // make chi2 plot
  int chi2_option = atoi(argv[3]);
  bool make_chi2 = false;
  if(chi2_option>0) make_chi2 = true;

  //qcd background type
  int qcd_option = -1;
  if( argc > 6 ) 
    qcd_option = atoi(argv[6]);

  bool outputbkg=false;

  //DATA/MC/Backgrounds PLOTS
  TFile *fdata = new TFile(data_file, "OLD");// first file (index=0 in getHistogramsFromData/getHistogramsFromPMCS)
  TFile *fpmcs = new TFile(mc_file, "OLD");  // second file (index=1 in getHistogramsFromData/getHistogramsFromPMCS)
  
  TString zeefile = "bkgd_shape_zee_run2b34.root";
  TString wtaunufile = "bkgd_shape_wtaunu_resbos_run2b34.root";
  double zee_bkg_fraction = 0.00985; 
  double wtaunu_bkg_fraction = 0.01726;
  TString qcdfile = "qcdbackgroundfiles/qcdfile_run34default.txt";
  if(qcd_option==2) qcdfile = "result_wen_QCD_1.root";

  if(! argc >= 11 && atoi(argv[5]) == 0) cout<<"WARNING: You are using the old run34 background files, not most current version."<<endl;

  if(atoi(argv[5]) == 0 && argc >= 11 ){ //we are processing data and need background information
    TString parameter_filename = argv[9];
    if (gSystem->AccessPathName(  parameter_filename )){
      cout<<"Parameter filename is not valid.  Try parameters.master"<<endl;
      return 1;
    }
    PParameterReader parm(parameter_filename.Data());  
    TString szeefile = "zeefile_";
    szeefile += argv[10];
    zeefile = parm.GetChar(szeefile);

    TString swtaunufile = "wtaunufile_";
    swtaunufile += argv[10];
    wtaunufile = parm.GetChar(swtaunufile);

    TString sqcdfile = "qcdfile_";
    sqcdfile += argv[10];
    qcdfile = parm.GetChar(sqcdfile);

    TString szeefrac = "zee_bkg_fraction_";
    szeefrac += argv[10];
    zee_bkg_fraction = parm.GetDouble(szeefrac, -1.0);

    TString swtaunufrac = "wtaunu_bkg_fraction_";
    swtaunufrac += argv[10];
    wtaunu_bkg_fraction = parm.GetDouble(swtaunufrac, -1.0);

    if (gSystem->AccessPathName(zeefile)){
      cout<<"Zee background file doesn't exist"<<endl;
      return 1;
    }
    if (gSystem->AccessPathName(wtaunufile)){
      cout<<"Wtaunu background file doesn't exist"<<endl;
      return 1;
    }
    if (gSystem->AccessPathName(qcdfile)){
      cout<<"QCD background file doesn't exist"<<endl;
      return 1;
    }
  
  }else if(atoi(argv[5]) == 0){
    cout<<"NOTE: No background option is given, using internal default values"<<endl<<endl; 
  }

  cout<<"Background parameters used:  "<<endl;
  cout<<"Zeefile: "<<zeefile<<"  zee background fraction: "<<zee_bkg_fraction<<endl;
  cout<<"Wtaunufile: "<<wtaunufile<<"  wtaunu background fraction: "<<wtaunu_bkg_fraction<<endl;
  cout<<"QCD file: "<<qcdfile<<endl;

 TFile *fbkgd_zee = new TFile(zeefile, "OLD");
 TFile *fbkgd_wtaunu = new TFile(wtaunufile);
 file_bkgd.push_back(fbkgd_zee);
 file_bkgd.push_back(fbkgd_wtaunu);

  TFile *fbkgd_wen_qcd;
  if (qcd_option==2){
       fbkgd_wen_qcd =  new TFile(qcdfile, "OLD"); // optional third file (index=2 in getHistogramsFromData/getHistogramsFromPMCS)
    file_bkgd.push_back(fbkgd_wen_qcd);
  }

  if(!fdata || !fpmcs || !fbkgd_zee || !fbkgd_wtaunu) {
    cout << "Can't open first and/or second file !!!" << endl;
    if(fdata) fdata->Close();
    if(fpmcs) fpmcs->Close();
    if(fbkgd_zee) fbkgd_zee->Close();
    if(fbkgd_wtaunu) fbkgd_wtaunu->Close();
    return 1;
  }

  if ( (qcd_option==2) && !fbkgd_wen_qcd){
    cout<<"Can't open qcd background file!!!"<<endl;
    if(fdata) fdata->Close();
    if(fpmcs) fpmcs->Close();
    if(fbkgd_zee) fbkgd_zee->Close();
    if(fbkgd_wtaunu) fbkgd_wtaunu->Close();
    return 1;
  }
    
  // instatiate blinng authority
  BlindingAuthority BA(2);

  // blind value of the W mass
  double blind_W_mass = -1;
  if(argc>=9 && atof(argv[8])>0) {
    blind_W_mass=atof(argv[8]);
    if ((blind_W_mass<75.)||(blind_W_mass>85.)) {
      cout<<endl<<endl;
      cout<<"That's a strange value for the blind m(W): "<<blind_W_mass<<endl;
      cout<<"Are you sure that this is what you wanted ? - Abort."<<endl;
      assert(0);
    }
  }

  // make compare option
  int compare_option = atoi(argv[4]);
  switch(compare_option) {
  case 0:    // 0 for data - fast MC, 
    set_DATA_label("DATA");   // first file, upper label
    set_MC_label("FAST MC");  // second file, bottom label
    if(!(fdata->cd("WCand_Hist") && fpmcs->cd("default"))){
      cout<<" ==> compare option = 0, Are you comparing DATA to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    BA.SetConfiguration(fdata,fpmcs,0);
    BA.SetBlindMass(blind_W_mass);
    getHistogramsFromData(fdata, 0, false);// will assume the first data file is REAL data
    getHistogramsFromPMCS(fpmcs, 1, &BA);  // will assume the second MC file is PMCS
    getHistogramsFromBackgrounds(file_bkgd, 2, false);  
    outputbkg=true;
    cout<<" Red histogram for the first file (DATA), Blue histogram for the second file (PMCS)"<<endl;
    break;
  case 1:    // 1 for data - data, 
    set_DATA_label("DATA #1");   // first file, upper label
    set_MC_label("DATA #2");     // second file, bottom label
    if(!(fdata->cd("WCand_Hist") && fpmcs->cd("WCand_Hist"))){
      cout<<" ==> compare option = 1, Are you comparing DATA to DATA ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    BA.SetConfiguration(fdata,fpmcs,1);
    getHistogramsFromData(fdata, 0, false);// will assume the first data file is REAL data
    getHistogramsFromData(fpmcs, 1, false);// will assume the second data file is REAL data
    cout<<" Red histogram for the first DATA file, Blue histogram for the second DATA file"<<endl;
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
    BA.SetConfiguration(fdata,fpmcs,2);
    getHistogramsFromPMCS(fdata, 0, &BA);// will assume the first MC file is PMCS
    getHistogramsFromPMCS(fpmcs, 1, &BA);// will assume the second MC file is PMCS
    cout<<" Red histogram for the first PMCS file, Blue histogram for the second PMCS file"<<endl;
    break;
  case 3:   // 3 for full MC - fast MC 
    set_DATA_label("FULL MC");   // first file, upper label
    set_MC_label("FAST MC");     // second file, bottom label
    if(!(fdata->cd("WCand_Hist") && fpmcs->cd("default"))){
      cout<<" ==> compare option = 3, Are you comparing FULL-MC to FAST-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    BA.SetConfiguration(fdata,fpmcs,3);
    getHistogramsFromData(fdata, 0, true);// will assume the first data file is FULL MC
    getHistogramsFromPMCS(fpmcs, 1, &BA); // will assume the first data file is PMCS
    cout<<" Red histogram for the first file (FULL MC), Blue histogram for the second file (PMCS)"<<endl;
    break;
  case 4:    // 4 for full MC - full MC 
    set_DATA_label("FULL MC #1");   // first file, upper label
    set_MC_label("FULL MC #2");     // second file, bottom label
    if(!(fdata->cd("WCand_Hist") && fpmcs->cd("WCand_Hist"))){
      cout<<" ==> compare option = 4, Are you comparing FULL-MC to FULL-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    BA.SetConfiguration(fdata,fpmcs,4);
    getHistogramsFromData(fdata, 0, true);// will assume the first data file is FULL MC
    getHistogramsFromData(fpmcs, 1, true);// will assume the second data file is FULL MC
    cout<<" Red histogram for the first FULL MC file, Blue histogram for the second FULL MC file"<<endl;    
    break;
  case 5:    // 5 for DATA - full MC 
    set_DATA_label("DATA");   // first file, upper label
    set_MC_label("FULL MC");  // second file, bottom label
    if(!(fdata->cd("WCand_Hist") && fpmcs->cd("WCand_Hist"))){
      cout<<" ==> compare option = 5, Are you comparing DATA to FULL-MC ??? Aborted"<<endl;
      if(fdata) fdata->Close();
      if(fpmcs) fpmcs->Close();
      return 1;
    }
    BA.SetConfiguration(fdata,fpmcs,5);
    getHistogramsFromData(fdata, 0, false);// will assume the first data file is FULL MC
    getHistogramsFromData(fpmcs, 1, false);// will assume the second data file is FULL MC
    getHistogramsFromBackgrounds(file_bkgd, 2, false);  
    cout<<" Red histogram for the first FULL MC file, Blue histogram for the second FULL MC file"<<endl;    
    break;
  default:  // UNKNOWN
    cout<<"Wrong <compare_option>="<<compare_option<<" !!!"<<endl;
    return 1;
  };
  assert(BA.isConfigured());

  // data or full MC
  bool mc_option = true;
  int mc_option_value = atoi(argv[5]);
  if(mc_option_value!=1) mc_option = false;

  // max plots/page
  int plots_per_page = 10;
  if(argc>=8 && atoi(argv[7])>0) plots_per_page=atoi(argv[7]);

  ////////////////////////////////////////////////////////////////////////////
#define FULLRANGE {-1E30, 1E30}
  typedef struct {
    char *cname;
    vector<TH1 *> *vect;
    vector<TH1 *> *vect_spatial;
    const double rangeX[2];
    } canvasBKG_t; 

 canvasBKG_t plotBKG[]= {
    { "wmass",             mass,              mass_spatial,              { 50., 100. }},
    { "wpT",               Wpt,               Wpt_spatial,               {  0.,  30. }},
    { "TruewpT",           TrueWpt,           TrueWpt_spatial,           {  0.,  30. }},
    { "wvertex",           Wvertex,           Wvertex_spatial,           {-60.,  60. }},
    { "wPhi",              Wphi,              Wphi_spatial,              FULLRANGE},
    { "elecpT",            elecpt,            elecpt_spatial,            { 25.,  60. }},
    { "elecEta",           eleceta,           eleceta_spatial,           {-1.5,  1.5 }},
    { "elecDetEta",        elecdeteta,        elecdeteta_spatial,        {-1.1,  1.1 }},
    { "elecPhi",           elecphi,           elecphi_spatial,           FULLRANGE},
    { "elecDetPhi",        elecdetphi,        elecdetphi_spatial,        FULLRANGE},
#ifdef MORE_ELECTRON_PHI_HISTOGRAMS
    { "elecPhiTrkAtDCA",   elecphitrkatdca,   elecphitrkatdca_spatial,   FULLRANGE},
    { "elecPhiTrkAtEM3",   elecphitrkatem3,   elecphitrkatem3_spatial,   FULLRANGE},
    { "elecDetPhiCALO",    elecdetphicalo,    elecdetphicalo_spatial,    FULLRANGE},
#endif
    { "Met",               met,               met_spatial,               {  25., 60. }},
    { "MetPhi",            metphi,            metphi_spatial,            FULLRANGE},
    { "Metx",              metx,              metx_spatial,              { -60., 60. }},
    { "Mety",              mety,              mety_spatial,              { -60., 60. }},
    { "InstLumi",          instlumi,          instlumi_spatial,          FULLRANGE},
    { "ScalarET",          scalarEt,          scalarEt_spatial,          {   0.,300. }},
#ifdef MORE_ZB_PLOTS
    { "ScalarETZB",        scalarEtZB,        scalarEtZB_spatial,        {   0.,300. }},
    { "ScalarETZBNoScale", scalarEtZBNoScale, scalarEtZBNoScale_spatial, {   0.,300. }},
#endif
    { "Upara",             upara,             upara_spatial,             { -30., 30. }},
    { "Uperp",             uperp,             uperp_spatial,             { -30., 30. }},
    { "WRecoilpT",         WRecoilpt,         WRecoilpt_spatial,         {   0., 30. }},
    { "WRecoilPx",         WRecoilpx,         WRecoilpx_spatial,         { -30., 30. }},
    { "WRecoilPy",         WRecoilpy,         WRecoilpy_spatial,         { -30., 30. }},
    { "WRecoilPhi",        WRecoilphi,        WRecoilphi_spatial,        FULLRANGE},
    { "Deltaphi_emrecoil", deltaphi_emrecoil, deltaphi_emrecoil_spatial, FULLRANGE},
    { "Deltaphi_emmet",    deltaphi_emmet,    deltaphi_emmet_spatial,    {2.5, TMath::Pi()}},
    { "Deltaphi_metrecoil",deltaphi_metrecoil,deltaphi_metrecoil_spatial,FULLRANGE}
    //{ "ElecTrkPt"         ,electrkpt,         electrkpt_spatial,         FULLRANGE},
    //{ "ElecTrkPtOverEt",   electrkptove,      electrkptove_spatial,      FULLRANGE},
    //{ "ElecTrkPhiEM3Mod",  electrkphiem3mod,  electrkphiem3mod_spatial,  FULLRANGE},
    //    { "utbins",            utbin,             utbin_spatial,             {  50., 100.}}
  };

  canvasBKG_t plotOVR[]={
    { "mtover",            mtoverlay,         mtoverlay_spatial,         {  50., 100.}},
    { "eptover",           eptoverlay,        eptoverlay_spatial,        {  25., 60. }},
    { "metover",           metoverlay,        metoverlay_spatial,        {  25., 60. }},
    { "wptover",           wptoverlay,        wptoverlay_spatial,        {   0., 30. }}
  };

  canvasBKG_t plotWPtSlice[]={
    { "WMCPt_CC_bin",   WMCPt_CC_bin, WMCPt_CC_bin_spatial, {0.,30.0} },
    { "WRecoilPt_CC_bin",   WRecoilPt_CC_bin, WRecoilPt_CC_bin_spatial, {0.,30.0} }
  };

  canvasBKG_t plotUTrue[] = {
    {"WCandTrueUPara",     WCandTrueUPara, WCandTrueUPara_Spatial,FULLRANGE},
    {"WCandTrueUPerp",     WCandTrueUPerp, WCandTrueUPerp_Spatial,FULLRANGE},
    {"WCandResoUPara",     WCandResoUPara, WCandResoUPara_Spatial,FULLRANGE},
    {"WCandResoUPerp",     WCandResoUPerp, WCandResoUPerp_Spatial,FULLRANGE}
  };

  const int nplotsBKG=sizeof(plotBKG)/sizeof(canvasBKG_t);
  const int nplotsOVR=sizeof(plotOVR)/sizeof(canvasBKG_t);
  const int nplotsWPtSlice=sizeof(plotWPtSlice)/sizeof(canvasBKG_t);
  const int nplotsUTrue = sizeof(plotUTrue)/sizeof(canvasBKG_t);

  typedef struct {
    char *cname;
    vector<TH1 *> *vect;
    const double rangeX[2];
 } canvas_t; 
  canvas_t plot[]= {
    { "plotprof",          profiles,          FULLRANGE}
  };
  const int nplots=sizeof(plot)/sizeof(canvas_t);

  double CCscale = mass[0][0]->Integral()/mass[1][0]->Integral();
  double CCscaleE = CCscale*sqrt(pow(sqrt(mass[0][0]->Integral())/mass[0][0]->Integral(),2)+
				 pow(sqrt(mass[1][0]->Integral())/mass[1][0]->Integral(),2));
  cout<<"CCscale: "<<mass[0][0]->Integral()<<" "<<mass[1][0]->Integral()<<" "<<CCscale<<" +/- "<<CCscaleE<<endl;

  // plot::plot_util() now operates on copies of input histograms
  // and it does not scale the originals. 

  
  for(int iplot=0; iplot<nplotsBKG; iplot++) {     
    plot_util(plotBKG[iplot].cname, 
	      (plotBKG[iplot].vect)[0], (plotBKG[iplot].vect_spatial)[0], 
	      (plotBKG[iplot].vect_spatial)[1], (plotBKG[iplot].vect_spatial)[2],
	      make_chi2,  mc_option,
	      plotBKG[iplot].rangeX[0], plotBKG[iplot].rangeX[1],
	      ps, plots_per_page, wenucomp, qcd_option, outputbkg, zee_bkg_fraction, wtaunu_bkg_fraction, qcdfile);
  }

  // plot::plot_util() now operates on copies of input histograms
  // and it does not scale the originals. 
  for(int iplot=0; iplot<nplots; iplot++) {
    plot_util(plot[iplot].cname, 
	      (plot[iplot].vect)[0], (plot[iplot].vect)[1], make_chi2, 
	      plot[iplot].rangeX[0], plot[iplot].rangeX[1], 
	      ps, plots_per_page, wenucomp );
  }

 
  for(int iplot=0; iplot<nplotsOVR; iplot++) {
     // the function below produce just a single plot, so there is no need to
     // pass 'plots_per_page' to it
     //cout<<"cname="<<plotOVR[iplot].cname<<endl;
     if( mc_option == 1 )
       plot2overlay_without_background(plotOVR[iplot].cname, 
                                   (plotOVR[iplot].vect)[0], (plotOVR[iplot].vect_spatial)[0], 
                                   (plotOVR[iplot].vect_spatial)[1], mc_option,
                                   plotOVR[iplot].rangeX[0], plotOVR[iplot].rangeX[1], 
                                   ps, wenucomp);
     else if( mc_option == 0 )
       plot2overlay_with_background(plotOVR[iplot].cname, 
                                   (plotOVR[iplot].vect)[0], (plotOVR[iplot].vect_spatial)[0], 
                                   (plotOVR[iplot].vect_spatial)[2],(plotOVR[iplot].vect_spatial)[1], mc_option,
                                   plotOVR[iplot].rangeX[0], plotOVR[iplot].rangeX[1], 
				    qcd_option , ps, wenucomp, zee_bkg_fraction, wtaunu_bkg_fraction, qcdfile);
  }

//




  for(int iplot=0; iplot<nplotsWPtSlice; iplot++){
    //    cout << "Plotting: "<<plotWPtSlice[iplot].cname<<endl;
  
    // avoid blank pages for non-existing histograms
    if((plotWPtSlice[iplot].vect)[0].size() && (plotWPtSlice[iplot].vect)[1].size()) {

      plot_util(plotWPtSlice[iplot].cname, (plotWPtSlice[iplot].vect)[0], (plotWPtSlice[iplot].vect)[1], make_chi2,
                plotWPtSlice[iplot].rangeX[0], plotWPtSlice[iplot].rangeX[1], ps, 5, wenucomp );
    } 
  }

  if( mc_option == 1 )
    {
      for(int iplot=0; iplot<nplotsUTrue; iplot++) {     

	plot_util(plotUTrue[iplot].cname, 
		  (plotUTrue[iplot].vect)[0], (plotUTrue[iplot].vect)[1], 
		  make_chi2,
		  plotUTrue[iplot].rangeX[0], plotUTrue[iplot].rangeX[1],
		  ps, plots_per_page, wenucomp);
      }
    }

  ps->Close();
  wenucomp->Write("All");
  wenucomp->Close();
}


void getHistogramsFromData(TFile *f, int index, bool is_fullMC) {
  f->cd("WCand_Hist");

  char name[50];
  for(int i=0; i<1; i++) {

    sprintf(name, "%s%d", "WCandMt_", i);
    mass[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandPt_", i);
    Wpt[index].push_back((TH1F *)gROOT->FindObject(name));

    if (is_fullMC) {
      sprintf(name, "%s%d", "WMCPt_", i);
      TrueWpt[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d", "WCandTrueUPara_Spatial_Match_", i);
      WCandTrueUPara[index].push_back((TH1F *)gROOT->FindObject(name));
      WCandTrueUPara_Spatial[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d", "WCandTrueUPerp_Spatial_Match_", i);
      WCandTrueUPerp[index].push_back((TH1F *)gROOT->FindObject(name));
      WCandTrueUPerp_Spatial[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d", "WCandResolUPara_Spatial_Match_", i);
      WCandResoUPara[index].push_back((TH1F *)gROOT->FindObject(name));
      WCandResoUPara_Spatial[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d", "WCandResolUPerp_Spatial_Match_", i);
      WCandResoUPerp[index].push_back((TH1F *)gROOT->FindObject(name));
      WCandResoUPerp_Spatial[index].push_back((TH1F *)gROOT->FindObject(name));
    }

    sprintf(name, "%s%d", "WCandVtx_", i);
    Wvertex[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandPhi_", i);
    Wphi[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecPt_", i);
    elecpt[index].push_back((TH1F *)gROOT->FindObject(name));
    
    sprintf(name, "%s%d", "WCandElecTrkPt_", i);
    electrkpt[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecTrkPtOvE_", i);
    electrkptove[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElec_TrkPhiEM3Mod_", i);
    electrkphiem3mod[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecEta_", i);
    eleceta[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecDetEta_", i);
    elecdeteta[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecPhi_", i);
    elecphi[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecDetPhi_", i);
    elecdetphi[index].push_back((TH1F *)gROOT->FindObject(name));
#ifdef MORE_ELECTRON_PHI_HISTOGRAMS
    sprintf(name, "%s%d", "WCandElecPhiTrkAtDCA_", i);
    elecphitrkatdca[index].push_back((TH1F *)gROOT->FindObject(name));
    sprintf(name, "%s%d", "WCandElecPhiTrkAtEM3_", i);
    elecphitrkatem3[index].push_back((TH1F *)gROOT->FindObject(name));
    sprintf(name, "%s%d", "WCandElecDetPhiCALO_", i);
    elecdetphicalo[index].push_back((TH1F *)gROOT->FindObject(name));
#endif
    sprintf(name, "%s%d", "WCandMet_", i);
    met[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandMetx_", i);
    metx[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandMety_", i);
    mety[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandMetPhi_", i);
    metphi[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandInstLumi_", i);
    instlumi[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandScalarEt_", i);
    scalarEt[index].push_back((TH1F *)gROOT->FindObject(name));

#ifdef MORE_ZB_PLOTS
    if (is_fullMC) {
      sprintf(name, "%s%d", "WCandScalarEt_ZB_", i);
      scalarEtZB[index].push_back((TH1F *)gROOT->FindObject(name));
      sprintf(name, "%s%d", "WCandScalarEt_ZB_", i);
      scalarEtZBNoScale[index].push_back((TH1F *)gROOT->FindObject(name));
    }
#endif

    sprintf(name, "%s%d", "WCandRecoilPt_", i);
    WRecoilpt[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandRecoilPx_", i);
    WRecoilpx[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandRecoilPy_", i);
    WRecoilpy[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandRecoilPhi_", i);
    WRecoilphi[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandUPara_", i);
    upara[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandUPerp_", i);
    uperp[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecMetDeltaPhi_", i);
    deltaphi_emmet[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecRecoilDeltaPhi_", i);
    deltaphi_emrecoil[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandMetRecoilDeltaPhi_", i);
    deltaphi_metrecoil[index].push_back((TH1F *)gROOT->FindObject(name));


    // The _Spatial_Match_ histograms now
    sprintf(name, "%s%d", "WCandMt_Spatial_Match_", i);
    mass_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandPt_Spatial_Match_", i);
    Wpt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    if (is_fullMC) {
      sprintf(name, "%s%d", "WMCPt_", i);
      TrueWpt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
    }

    sprintf(name, "%s%d", "WCandElecTrkPt_Spatial_Match_", i);
    electrkpt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecTrkPtOvE_Spatial_Match_", i);
    electrkptove_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElec_TrkPhiEM3Mod_Spatial_Match_", i);
    electrkphiem3mod_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandVtx_Spatial_Match_", i);
    Wvertex_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandPhi_Spatial_Match_", i);
    Wphi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecPt_Spatial_Match_", i);
    elecpt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecEta_Spatial_Match_", i);
    eleceta_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecDetEta_Spatial_Match_", i);
    elecdeteta_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecPhi_Spatial_Match_", i);
    elecphi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecDetPhi_Spatial_Match_", i);
    elecdetphi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
#ifdef MORE_ELECTRON_PHI_HISTOGRAMS
    sprintf(name, "%s%d", "WCandElecPhiTrkAtDCA_Spatial_Match_", i);
    elecphitrkatdca_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
    sprintf(name, "%s%d", "WCandElecPhiTrkAtEM3_Spatial_Match_", i);
    elecphitrkatem3_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
    sprintf(name, "%s%d", "WCandElecDetPhiCALO_Spatial_Match_", i);
    elecdetphicalo_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
#endif
    sprintf(name, "%s%d", "WCandMet_Spatial_Match_", i);
    met_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandMetx_Spatial_Match_", i);
    metx_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandMety_Spatial_Match_", i);
    mety_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandMetPhi_Spatial_Match_", i);
    metphi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandInstLumi_Spatial_Match_", i);
    instlumi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandScalarEt_Spatial_Match_", i);
    scalarEt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

#ifdef MORE_ZB_PLOTS
    if (is_fullMC) {
      sprintf(name, "%s%d", "WCandScalarEt_ZB_Spatial_Match_", i);
      TH1F* ahist = (TH1F *)gROOT->FindObject(name);
      scalarEtZB_spatial[index].push_back(ahist);
      char ahistname[100];
      sprintf(ahistname, "%s%d", "WCandScalarEt_ZBNoScale_Spatial_Match_", i);
      TH1F* ahist2 = (TH1F*)ahist->Clone(ahistname);
      ahist2->SetTitle(ahistname);
      scalarEtZBNoScale_spatial[index].push_back(ahist2);
    }
#endif

    sprintf(name, "%s%d", "WCandRecoilPt_Spatial_Match_", i);
    WRecoilpt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandRecoilPx_Spatial_Match_", i);
    WRecoilpx_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandRecoilPy_Spatial_Match_", i);
    WRecoilpy_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandRecoilPhi_Spatial_Match_", i);
    WRecoilphi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandUPara_Spatial_Match_", i);
    upara_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandUPerp_Spatial_Match_", i);
    uperp_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecMetDeltaPhi_Spatial_Match_", i);
    deltaphi_emmet_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecRecoilDeltaPhi_Spatial_Match_", i);
    deltaphi_emrecoil_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandMetRecoilDeltaPhi_Spatial_Match_", i);
    deltaphi_metrecoil_spatial[index].push_back((TH1F *)gROOT->FindObject(name));


    // The recoil system now
    sprintf(name, "%s%d", "WCandMtUpara_", i);
    profiles[index].push_back((TProfile *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandWPtUpara_", i);
    profiles[index].push_back((TProfile *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandElecPtUpara_", i);
    profiles[index].push_back((TProfile *)gROOT->FindObject(name));

    sprintf(name, "%s%d", "WCandMetUpara_", i);
    profiles[index].push_back((TProfile *)gROOT->FindObject(name));
  }

  for(int i=0; i<2; i++) {

    sprintf(name, "%s%d%s", "WCandMtUpara", (i+1), "_0");
    mtoverlay[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandElecPtUpara", (i+1), "_0");
    eptoverlay[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandMetUpara", (i+1), "_0");
    metoverlay[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandWPtUpara", (i+1), "_0");
    wptoverlay[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandMtUpara", (i+1), "_Spatial_Match_0");
    mtoverlay_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandElecPtUpara", (i+1), "_Spatial_Match_0");
    eptoverlay_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandMetUpara", (i+1), "_Spatial_Match_0");
    metoverlay_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandWPtUpara", (i+1), "_Spatial_Match_0");
    wptoverlay_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    // get Mt distributions for three Ut bins
    sprintf(name, "%s%d", "WCandMt_UtBin_", i);
    utbin[index].push_back((TH1F *)gROOT->FindObject(name));
    
    sprintf(name, "%s%d", "WCandMt_UtBin_Spatial_Match_", i);
    utbin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
    
    if(i==1) {
      sprintf(name, "%s%d", "WCandMt_UtBin_", (i+1));
      utbin[index].push_back((TH1F *)gROOT->FindObject(name));
      
      sprintf(name, "%s%d", "WCandMt_UtBin_Spatial_Match_", (i+1));
      utbin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));      
    }
  }

  //  
  //3d histograms
  // 
  sprintf(name, "%s", "WCandMtVEtaPt");
  mass[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandPtVEtaPt");
  Wpt[index].push_back((TH1 *)gROOT->FindObject(name));

  sprintf(name, "%s", "WCandElecTrkPtVEtaPt");
  electrkpt[index].push_back((TH1F *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecTrkPtOvEVEtaPt");
  electrkptove[index].push_back((TH1F *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElec_TrkPhiEM3ModVEtaPt");
  electrkphiem3mod[index].push_back((TH1F *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandVtxVEtaPt");
  Wvertex[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandPhiVEtaPt");
  Wphi[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecPtVEtaPt");
  elecpt[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecEtaVEtaPt");
  eleceta[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecDetEtaVEtaPt");
  elecdeteta[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecPhiVEtaPt");
  elecphi[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecDetPhiVEtaPt");
  elecdetphi[index].push_back((TH1 *)gROOT->FindObject(name));
 
 #ifdef MORE_ELECTRON_PHI_HISTOGRAMS
  //sprintf(name, "%s", "WCandElecDetPhiVEtaPt");
  sprintf(name, "%s", "WCandElecPhiTrkAtDCAVEtaPt");
  elecphitrkatdca[index].push_back((TH1 *)gROOT->FindObject(name));

  //sprintf(name, "%s", "WCandElecDetPhiVEtaPt");
  sprintf(name, "%s", "WCandElecPhiTrkAtEM3VEtaPt");
  elecphitrkatem3[index].push_back((TH1F *)gROOT->FindObject(name));

  //sprintf(name, "%s", "WCandElecDetPhiVEtaPt");
  sprintf(name, "%s", "WCandElecDetPhiCALOVEtaPt");
  elecdetphicalo[index].push_back((TH1F *)gROOT->FindObject(name));
#endif
 
  sprintf(name, "%s", "WCandMetVEtaPt");
  met[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandMetxVEtaPt");
  metx[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandMetyVEtaPt");
  mety[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandMetPhiVEtaPt");
  metphi[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandInstLumiVEtaPt");
  instlumi[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandScalarEtVEtaPt");
  scalarEt[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandRecoilPtVEtaPt");
  WRecoilpt[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandRecoilPxVEtaPt");
  WRecoilpx[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandRecoilPyVEtaPt");
  WRecoilpy[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandRecoilPhiVEtaPt");
  WRecoilphi[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandUParaVEtaPt");
  upara[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandUPerpVEtaPt");
  uperp[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecMetDeltaPhiVEtaPt");
  deltaphi_emmet[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecRecoilDeltaPhiVEtaPt");
  deltaphi_emrecoil[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandMetRecoilDeltaPhiVEtaPt");
  deltaphi_metrecoil[index].push_back((TH1 *)gROOT->FindObject(name));  
  
  /*
  sprintf(name, "%s", "WCandMtVEtaPt_UtBin_0");
  utbin[index].push_back((TH1 *)gROOT->FindObject(name));
  sprintf(name, "%s", "WCandMtVEtaPt_UtBin_1");
  utbin[index].push_back((TH1 *)gROOT->FindObject(name));
  sprintf(name, "%s", "WCandMtVEtaPt_UtBin_2");
  utbin[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandMtVEtaPt_Match_UtBin_0");
  utbin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
  sprintf(name, "%s", "WCandMtVEtaPt_Match_UtBin_1");
  utbin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
  sprintf(name, "%s", "WCandMtVEtaPt_Match_UtBin_2");
  utbin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
  */
 
  // The _Spatial_Match_ histograms now
  sprintf(name, "%s", "WCandMtVEtaPt_Match");
  mass_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandPtVEtaPt_Match");
  Wpt_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecTrkPtVEtaPt_Match");
  electrkpt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecTrkPtOvEVEtaPt_Match");
  electrkptove_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElec_TrkPhiEM3ModVEtaPt_Match");
  electrkphiem3mod_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

  sprintf(name, "%s", "WCandVtxVEtaPt_Match");
  Wvertex_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandPhiVEtaPt_Match");
  Wphi_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecPtVEtaPt_Match");
  elecpt_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecEtaVEtaPt_Match");
  eleceta_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecDetEtaVEtaPt_Match");
  elecdeteta_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecPhiVEtaPt_Match");
  elecphi_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecDetPhiVEtaPt_Match");
  elecdetphi_spatial[index].push_back((TH1 *)gROOT->FindObject(name));

#ifdef MORE_ELECTRON_PHI_HISTOGRAMS
  //sprintf(name, "%s", "WCandElecDetPhiVEtaPt_Match");
  sprintf(name, "%s", "WCandElecPhiTrkAtDCAVEtaPt_Match");
  elecphitrkatdca_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
  //sprintf(name, "%s", "WCandElecDetPhiVEtaPt_Match");
  sprintf(name, "%s", "WCandElecPhiTrkAtEM3VEtaPt_Match");
  elecphitrkatem3_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
  //sprintf(name, "%s", "WCandElecDetPhiVEtaPt_Match");
  sprintf(name, "%s", "WCandElecDetPhiCALOVEtaPt_Match");
  elecdetphicalo_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
#endif 
 
  sprintf(name, "%s", "WCandMetVEtaPt_Match");
  met_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandMetxVEtaPt_Match");
  metx_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandMetyVEtaPt_Match");
  mety_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandMetPhiVEtaPt_Match");
  metphi_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandInstLumiVEtaPt_Match");
  instlumi_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandScalarEtVEtaPt_Match");
  scalarEt_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandRecoilPtVEtaPt_Match");
  WRecoilpt_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandRecoilPxVEtaPt_Match");
  WRecoilpx_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandRecoilPyVEtaPt_Match");
  WRecoilpy_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandRecoilPhiVEtaPt_Match");
  WRecoilphi_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandUParaVEtaPt_Match");
  upara_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandUPerpVEtaPt_Match");
  uperp_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecMetDeltaPhiVEtaPt_Match");
  deltaphi_emmet_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandElecRecoilDeltaPhiVEtaPt_Match");
  deltaphi_emrecoil_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  sprintf(name, "%s", "WCandMetRecoilDeltaPhiVEtaPt_Match");
  deltaphi_metrecoil_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
  
  for(int i=0; i<2; i++) {

    sprintf(name, "%s%d%s", "WCandMtUpara", (i+1), "VEtaPt");
    mtoverlay[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandElecPtUpara", (i+1), "VEtaPt");
    eptoverlay[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandMetUpara", (i+1), "VEtaPt");
    metoverlay[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandWPtUpara", (i+1), "VEtaPt");
    wptoverlay[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandMtUpara", (i+1), "VEtaPt_Match");
    mtoverlay_spatial[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandElecPtUpara", (i+1), "VEtaPt_Match");
    eptoverlay_spatial[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandMetUpara", (i+1), "VEtaPt_Match");
    metoverlay_spatial[index].push_back((TH1 *)gROOT->FindObject(name));

    sprintf(name, "%s%d%s", "WCandWPtUpara", (i+1), "VEtaPt_Match");
    wptoverlay_spatial[index].push_back((TH1 *)gROOT->FindObject(name));

    // get Mt distributions for three Ut bins
    sprintf(name, "%s%d", "WCandMtVEtaPt_UtBin_", i);
    utbin[index].push_back((TH1 *)gROOT->FindObject(name));
    
    sprintf(name, "%s%d", "WCandMtVEtaPt_UtBin_Spatial_Match_", i);
    utbin_spatial[index].push_back((TH1 *)gROOT->FindObject(name));
    
    if(i==1) {
      sprintf(name, "%s%d", "WCandMtVEtaPt_UtBin_", (i+1));
      utbin[index].push_back((TH1 *)gROOT->FindObject(name));
      
      sprintf(name, "%s%d", "WCandMtVEtaPt_UtBin_Spatial_Match_", (i+1));
      utbin_spatial[index].push_back((TH1 *)gROOT->FindObject(name));      
    }
  }

  for (int i=0; i<10; i++){
    if (is_fullMC) {
      sprintf(name, "%s%d", "WMCPt_CC_bin_", i);
      WMCPt_CC_bin[index].push_back((TH1F *)gROOT->FindObject(name));
      sprintf(name, "%s%d", "WRecoilPt_CC_bin_", i);
      WRecoilPt_CC_bin[index].push_back((TH1F *)gROOT->FindObject(name));
      sprintf(name, "%s%d", "WMCPt_CC_bin_", i);
      WMCPt_CC_bin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
      sprintf(name, "%s%d", "WRecoilPt_CC_bin_", i);
      WRecoilPt_CC_bin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
    }
  }

}

// for pmcs histograms, histograms without and with spatial track matching
// are the same
void getHistogramsFromPMCS(TFile *f, int index, BlindingAuthority* BA) {
  f -> cd("default");
  
  char name[50];
  string temp;
  for(int i=0; i<1; i++) {

    if(i==0)      temp = string("CC");

    TH1F* d = BA->Get_mass(f,temp.c_str());
    mass[index].push_back(d);
    mass_spatial[index].push_back(d);

    sprintf(name, "%s%s", "hWcandWPt_", temp.c_str());
    Wpt[index].push_back((TH1F *)gROOT->FindObject(name));
    Wpt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hMCW_Pt_", temp.c_str());
    TH1F *h1 = (TH1F *)gROOT->FindObject(name); 
    TrueWpt[index].push_back((TH1F *)gROOT->FindObject(name));
    TrueWpt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandTrueUpara_", temp.c_str());
    WCandTrueUPara[index].push_back((TH1F *)gROOT->FindObject(name));
    WCandTrueUPara_Spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandTrueUperp_", temp.c_str());
    WCandTrueUPerp[index].push_back((TH1F *)gROOT->FindObject(name));
    WCandTrueUPerp_Spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandResolUpara_", temp.c_str());
    WCandResoUPara[index].push_back((TH1F *)gROOT->FindObject(name));
    WCandResoUPara_Spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandResolUperp_", temp.c_str());
    WCandResoUPerp[index].push_back((TH1F *)gROOT->FindObject(name));
    WCandResoUPerp_Spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandElecTrkPt_",temp.c_str());
    electrkpt[index].push_back((TH1F *)gROOT->FindObject(name));
    electrkpt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "hWcandElecTrkPtOvE_", temp.c_str());
    electrkptove[index].push_back((TH1F *)gROOT->FindObject(name));
    electrkptove_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
    
    sprintf(name, "%s%s", "hWcandElecTrkPhiModEM3_", temp.c_str());
    electrkphiem3mod[index].push_back((TH1F *)gROOT->FindObject(name));
    electrkphiem3mod_spatial[index].push_back((TH1F *)gROOT->FindObject(name));


    sprintf(name, "%s%s", "hWcandVtx_", temp.c_str());
    Wvertex[index].push_back((TH1F *)gROOT->FindObject(name));
    Wvertex_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandWPhi_", temp.c_str());
    Wphi[index].push_back((TH1F *)gROOT->FindObject(name));
    Wphi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    d = BA->Get_elecpt(f,temp.c_str());
    elecpt[index].push_back(d);
    elecpt_spatial[index].push_back(d);

    sprintf(name, "%s%s", "hWcandElecEta_", temp.c_str());
    eleceta[index].push_back((TH1F *)gROOT->FindObject(name));
    eleceta_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandElecDetEta_", temp.c_str());
    elecdeteta[index].push_back((TH1F *)gROOT->FindObject(name));
    elecdeteta_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandElecPhi_", temp.c_str());
    elecphi[index].push_back((TH1F *)gROOT->FindObject(name));
    elecphi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandElecDetPhi_", temp.c_str());
    elecdetphi[index].push_back((TH1F *)gROOT->FindObject(name));
    elecdetphi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
#ifdef MORE_ELECTRON_PHI_HISTOGRAMS
    sprintf(name, "%s%s", "hWcandElecPhiTrkAtDCA_", temp.c_str());
    elecphitrkatdca[index].push_back((TH1F *)gROOT->FindObject(name));
    elecphitrkatdca_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandElecPhiTrkAtEM3_", temp.c_str());
    elecphitrkatem3[index].push_back((TH1F *)gROOT->FindObject(name));
    elecphitrkatem3_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandElecDetPhiCALO_", temp.c_str());
    elecdetphicalo[index].push_back((TH1F *)gROOT->FindObject(name));
    elecdetphicalo_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
#endif

    d = BA->Get_met(f,temp.c_str());
    met[index].push_back(d);
    met_spatial[index].push_back(d);

    sprintf(name, "%s%s", "hWcandMetx_", temp.c_str());
    metx[index].push_back((TH1F *)gROOT->FindObject(name));
    metx_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandMety_", temp.c_str());
    mety[index].push_back((TH1F *)gROOT->FindObject(name));
    mety_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandMetPhi_", temp.c_str());
    metphi[index].push_back((TH1F *)gROOT->FindObject(name));
    metphi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandLumi_", temp.c_str());
    instlumi[index].push_back((TH1F *)gROOT->FindObject(name));
    instlumi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandScalarEt_", temp.c_str());
    scalarEt[index].push_back((TH1F *)gROOT->FindObject(name));
    scalarEt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

#ifdef MORE_ZB_PLOTS
    sprintf(name, "%s%s", "hWcandScalarEtZB_", temp.c_str());
    scalarEtZB[index].push_back((TH1F *)gROOT->FindObject(name));
    scalarEtZB_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandScalarEtZBNoScale_", temp.c_str());
    scalarEtZBNoScale[index].push_back((TH1F *)gROOT->FindObject(name));
    scalarEtZBNoScale_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
#endif

    sprintf(name, "%s%s", "hWcandRecoilPt_", temp.c_str());
    WRecoilpt[index].push_back((TH1F *)gROOT->FindObject(name));
    WRecoilpt_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandRecoilPx_", temp.c_str());
    WRecoilpx[index].push_back((TH1F *)gROOT->FindObject(name));
    WRecoilpx_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandRecoilPy_", temp.c_str());
    WRecoilpy[index].push_back((TH1F *)gROOT->FindObject(name));
    WRecoilpy_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandRecoilPhi_", temp.c_str());
    WRecoilphi[index].push_back((TH1F *)gROOT->FindObject(name));
    WRecoilphi_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandUpara_", temp.c_str());
    upara[index].push_back((TH1F *)gROOT->FindObject(name));
    upara_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandUperp_", temp.c_str());
    uperp[index].push_back((TH1F *)gROOT->FindObject(name));
    uperp_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandElecMETDeltaPhi_", temp.c_str());
    deltaphi_emmet[index].push_back((TH1F *)gROOT->FindObject(name));
    deltaphi_emmet_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandElecRecoilDeltaPhi_", temp.c_str());
    deltaphi_emrecoil[index].push_back((TH1F *)gROOT->FindObject(name));
    deltaphi_emrecoil_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    sprintf(name, "%s%s", "hWcandMETRecoilDeltaPhi_", temp.c_str());
    deltaphi_metrecoil[index].push_back((TH1F *)gROOT->FindObject(name));
    deltaphi_metrecoil_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    // The recoil system now
    TH1* dd = BA->Get_hWcandMtUpara(f, temp.c_str());
    profiles[index].push_back(dd);

    sprintf(name, "%s%s", "hWcandWPtUpara_", temp.c_str());
    profiles[index].push_back((TProfile *)gROOT->FindObject(name));

    dd = BA->Get_hWcandElecPtUpara(f, temp.c_str());
    profiles[index].push_back(dd);

    dd = BA->Get_hWcandMetUpara(f, temp.c_str());
    profiles[index].push_back(dd);
  }

  for(int i=0; i<2; i++) {

    temp = string("CC");
    TH1F* d = BA->Get_mtoverlay(f,i+1,temp.c_str());
    mtoverlay[index].push_back(d);
    mtoverlay_spatial[index].push_back(d);

    d = BA->Get_eptoverlay(f,i+1,temp.c_str());
    eptoverlay[index].push_back(d);
    eptoverlay_spatial[index].push_back(d);

    d = BA->Get_metoverlay(f,i+1,temp.c_str());
    metoverlay[index].push_back(d);
    metoverlay_spatial[index].push_back(d);

    sprintf(name, "%s%d%s%s", "hWcandWPtUpara", (i+1), "_", temp.c_str());
    wptoverlay[index].push_back((TH1F *)gROOT->FindObject(name));
    wptoverlay_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

    d = BA->Get_utbinoverlay(f,i,temp.c_str());
    utbin[index].push_back(d);
    utbin_spatial[index].push_back(d);

    if(i==1) {
      d = BA->Get_utbinoverlay(f,i+1,temp.c_str());
      utbin[index].push_back(d);
      utbin_spatial[index].push_back(d);
    }

  }

  for (int i=0; i<10; i++){
    sprintf(name, "%s%d", "hMCW_Pt_CC_bin_", i);
    WMCPt_CC_bin[index].push_back((TH1F *)gROOT->FindObject(name));
    WMCPt_CC_bin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
    sprintf(name, "%s%d", "hRecoilW_Pt_CC_bin_", i);
    WRecoilPt_CC_bin[index].push_back((TH1F *)gROOT->FindObject(name));
    WRecoilPt_CC_bin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
    
  }

}



void getHistogramsFromBackgrounds(vector<TFile *> vect, int index, bool is_fullMC) {
  for(int i=0; i<vect.size(); i++){
    TFile *file=(TFile *) vect[i];
    file->cd();
    file->cd("WCand_Hist");
    mass_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandMt_Spatial_Match_0"));
    Wpt_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandPt_Spatial_Match_0"));
    Wvertex_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandVtx_Spatial_Match_0"));
    Wphi_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandPhi_Spatial_Match_0"));
    elecpt_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecPt_Spatial_Match_0"));
    eleceta_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecEta_Spatial_Match_0"));
    elecdeteta_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecDetEta_Spatial_Match_0"));
    elecphi_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecPhi_Spatial_Match_0"));
    elecdetphi_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecDetPhi_Spatial_Match_0"));
#ifdef MORE_ELECTRON_PHI_HISTOGRAMS
    elecphitrkatdca_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecPhiTrkAtDCA_Spatial_Match_0"));
    elecphitrkatem3_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecPhiTrkAtEM3_Spatial_Match_0"));
    elecdetphicalo_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecDetPhiCALO_Spatial_Match_0"));
#endif
    met_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandMet_Spatial_Match_0"));
    metphi_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandMetPhi_Spatial_Match_0"));
    metx_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandMetx_Spatial_Match_0"));
    mety_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandMety_Spatial_Match_0"));
    instlumi_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandInstLumi_Spatial_Match_0"));
    scalarEt_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandScalarEt_Spatial_Match_0"));
    upara_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandUPara_Spatial_Match_0"));
    uperp_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandUPerp_Spatial_Match_0"));
    WRecoilpt_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandRecoilPt_Spatial_Match_0"));
    WRecoilpx_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandRecoilPx_Spatial_Match_0"));
    WRecoilpy_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandRecoilPy_Spatial_Match_0"));
    WRecoilphi_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandRecoilPhi_Spatial_Match_0"));
    deltaphi_emrecoil_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecRecoilDeltaPhi_Spatial_Match_0"));
    deltaphi_emmet_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecMetDeltaPhi_Spatial_Match_0"));
    deltaphi_metrecoil_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandMetRecoilDeltaPhi_Spatial_Match_0"));
    utbin_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandMt_UtBin_Spatial_Match_0"));
    electrkpt_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecTrkPt_Spatial_Match_0"));
    electrkptove_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElecTrkPtOvE_Spatial_Match_0"));
    electrkphiem3mod_spatial[index].push_back((TH1F *)gROOT->FindObject("WCandElec_TrkPhiEM3Mod_Spatial_Match_0"));

    char name[50];
    for(int i=0; i<2; i++) {

      sprintf(name, "%s%d%s", "WCandMtUpara", (i+1), "_0");
      mtoverlay[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d%s", "WCandElecPtUpara", (i+1), "_0");
      eptoverlay[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d%s", "WCandMetUpara", (i+1), "_0");
      metoverlay[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d%s", "WCandWPtUpara", (i+1), "_0");
      wptoverlay[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d%s", "WCandMtUpara", (i+1), "_Spatial_Match_0");
      mtoverlay_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d%s", "WCandElecPtUpara", (i+1), "_Spatial_Match_0");
      eptoverlay_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d%s", "WCandMetUpara", (i+1), "_Spatial_Match_0");
      metoverlay_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

      sprintf(name, "%s%d%s", "WCandWPtUpara", (i+1), "_Spatial_Match_0");
      wptoverlay_spatial[index].push_back((TH1F *)gROOT->FindObject(name));

      // get Mt distributions for three Ut bins
      sprintf(name, "%s%d", "WCandMt_UtBin_", i);
      utbin[index].push_back((TH1F *)gROOT->FindObject(name));
      
      sprintf(name, "%s%d", "WCandMt_UtBin_Spatial_Match_", i);
      utbin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));
      
      if(i==1) {
        sprintf(name, "%s%d", "WCandMt_UtBin_", (i+1));
        utbin[index].push_back((TH1F *)gROOT->FindObject(name));
        
        sprintf(name, "%s%d", "WCandMt_UtBin_Spatial_Match_", (i+1));
        utbin_spatial[index].push_back((TH1F *)gROOT->FindObject(name));      
      }
    }
  }
}
