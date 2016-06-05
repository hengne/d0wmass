#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TGraph.h>
#include <TApplication.h>
#include <TVector2.h>
#include <vector>
#include <map>
#include <TRandom3.h>
#include <TRandom.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraphErrors.h>
#include <TMath.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "perBinProfile.h"
#include "../../src/SETefficiencySmear.hpp"
#include "../../src/PParameterReader.hpp"
//#include "SETefficiencySmear.hpp"
//#include "PParameterReader.hpp"

using namespace std;

// ConvertRecoils2D Unfolds a Reconstructed Recoil File //////////////////////////////////////////////////////
// M. Wetstein ///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Binning Variables /////////////////////////////////////////////////////////////////////////
int _num_recoil_pT_bins;
int _num_RpT_bins;
int _num_delta_phi_bins;
int _num_psi_bins;
int _num_course_pT_bins;
int size_edges;
int size_Redges;
int size_dPedges;
int size_dPsiedges;
int size_courseedges;

double psi_bin_width;
double psi_halfbin_width;

vector<double> _recoil_pT_bin_edges;
vector<double> _course_pT_bin_edges;
vector<double> _RpT_bin_edges;
vector<double> _delta_phi_bin_edges;
vector<double> _psi_bin_edges;
vector<double> bincenters;

int *courseMap;
int *RcourseMap;
/////////////////////////////////////////////////////////////////////////////////////////


// Matrix Elements and Initial Distributions for Unfolding //////////////////////////////
double *_ZpT_Dist;
double *_pT_Phi_Norm;
double ***_pT_Phi;
double ***_smR_Norm;
double ***_pT_Psi_R_Dist;
double ***_pT_Psi_R_Count;

////////////////////////////////////////////////////////////////////////////////////////


// Profile Instances /////////////////////////////////////////////////////////////////////
perBinProfile* recoil_pT_corr;
perBinProfile* recoil_pT_gen;
perBinProfile* recoil_pT_smR;
perBinProfile* recoil_pY_corr;
perBinProfile* recoil_pY_gen;
perBinProfile* recoil_pY_smR;
perBinProfile* TOT_phi_corr;
perBinProfile* TOT_phi_gen;
perBinProfile* TOT_phi_smR;
////////////////////////////////////////////////////////////////////////////////////////


// Efficiency Instances ////////////////////////////////////////////////////////////////
SETefficiencySmear *_SETeffic; 


//Recoil File Histrograms///////////////////////////////////////////////////////////////
TH1D *_recoil_pY_means;
TH2D **_recoil_pT_histograms;
TH2D **_recoil_pT_histograms_smR;
TH2D **_recoil_pT_histograms_gen;
////////////////////////////////////////////////////////////////////////////////////////


//SET Histograms/////////////////////////////////////////////////////////////////////////////
TH1D ***_SEThist;
////////////////////////////////////////////////////////////////////////////////////////


// Diagnostic Histograms ///////////////////////////////////////////////////////////////
TH2D *InstLumi_runNo_WZ;
TH2D *InstLumi_SET_WZ;
TH2D *InstLumi_SET_WZ_orig;

TH1D *_Zspect;
TH1D *_Zspect_smR;
TH1D *_Recspect;

TH1D* _theSETweights;
TH1D* _theUPweights;
TH1D* _theunfoldweights;

TH1D ***_recoil_phi_hist;

TH1D **_recoil_pX_hist_gen;
TH1D **_recoil_pX_hist_smR;
TH1D **_recoil_pX_hist_corr;
TH1D **_recoil_pY_hist_gen;
TH1D **_recoil_pY_hist_smR;
TH1D **_recoil_pY_hist_corr;
TH1D **_recoil_pT_hist_gen;
TH1D **_recoil_pT_hist_smR;
TH1D **_recoil_pT_hist_corr;
TH1D **_recoil_psi_hist_gen;
TH1D **_recoil_psi_hist_smR;
TH1D **_recoil_psi_hist_corr;
TH1D **_recoil_frac_gen;
TH1D **_recoil_frac_smR;
TH1D **_recoil_frac_corr;
////////////////////////////////////////////////////////////////////////////////////////


// Mean recoil projected along boson direction /////////////////////////////////////////
double *recoil_pT_bin_meansY;
double *recoil_pT_bin_meansY_gen;
double *recoil_pT_bin_meansY_smR; 
///////////////////////////////////////////////////////////////////////////////////////


// Switches and file names ////////////////////////////////////////////////////////////
bool doSETcorr,doUparcorr,iszrecoil,kill_mode;
bool make_corrected_file;
int num_iters,num_rec_evts_touse;
TString output_label;
TString pmcs_mapname;
TString data_recoilname;
double baseNORM;
///////////////////////////////////////////////////////////////////////////////////////


// SET and Upara Efficiency Parameters ////////////////////////////////////////////////
bool _ZSETEffCorrScaled;
std::vector<float> _ZSETEffCorrParameters;

std::vector<float> _ZSETEffCorrParametersCCCC;
std::vector<float> _ZSETEffCorrParametersCCEC;
std::vector<float> _ZSETEffCorrParametersECEC;

//
int _ZSETEffCorrPTEpert;
std::vector<float> _ZSETEffCorrPTEpertBase;
std::vector<float> _ZSETEffCorrPTEpertA;
std::vector<float> _ZSETEffCorrPTEpertB;
std::vector<float> _ZSETEffCorrPTEpertC;
std::vector<float> _ZSETEffCorrPTEpertD;
std::vector<float> _ZSETEffCorrPTEpertE;
std::vector<float> _ZSETEffCorrPTEpertF;
std::vector<float> _ZSETEffCorrPTEpertG;
std::vector<float> _ZSETEffCorrPTEpertH;
std::vector<float> _ZSETEffCorrPTEpertNorm;

std::vector< std::vector< std::vector<float> > > _ZSETEffCorrDataRatioParameters;
std::vector< std::vector< std::vector<float> > > _ZSETEffCorrDataRatioParameters2;
bool _useHack;
bool _useLumiBins;

std::vector<float> _ZSETEffCorrPTEpertBase_EC;
std::vector<float> _ZSETEffCorrPTEpertA_EC;
std::vector<float> _ZSETEffCorrPTEpertB_EC;
std::vector<float> _ZSETEffCorrPTEpertC_EC;
std::vector<float> _ZSETEffCorrPTEpertD_EC;
std::vector<float> _ZSETEffCorrPTEpertE_EC;
std::vector<float> _ZSETEffCorrPTEpertF_EC;
std::vector<float> _ZSETEffCorrPTEpertG_EC;
std::vector<float> _ZSETEffCorrPTEpertH_EC;
std::vector<float> _ZSETEffCorrPTEpertNorm_EC;

int _UparaEffCorrOption;
std::vector<double> _ZUparaEffParameters;
double _Z_u0_CC, _Z_s_CC, _Z_u0_EC, _Z_s_EC;
///////////////////////////////////////////////////////////////////////////////////////


// Event Information //////////////////////////////////////////////////////////////////
vector< vector<double> > RecDatVec;
double Zpx_gen,Zpy_gen,Zpx_smear,Zpy_smear,Ex_before,Ey_before,evttype,evtweight,Ex_rot,Ey_rot, runno, epT1, epT2, eleta1, eleta2;
double ZpT_gen, ZpT_smear, RecpT, Ex_rot_smR, Ey_rot_smR ,Ex_rot_gen, Ey_rot_gen, PhiRecRot_gen, PhiRecRot_smR;
double thePsi_smR, thePsiFill_smR, thePsi_gen, thePsiFill_gen, the_smR_Norm, theSET, psipos, theLumi, upar1, upar2;
int genpTBin, smRpTBin, RecpTBin, PsiBin, PsiBin_true, line, NumRecEvts, courseBinR;
//////////////////////////////////////////////////////////////////////////////////////















/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int InitializeIt(){

  cout<<pmcs_mapname<<" "<<data_recoilname<<endl;

  // Defining my pT binning scheme

  _num_recoil_pT_bins = 156;
  _num_course_pT_bins = 34;
  _num_RpT_bins = 54;
  _num_delta_phi_bins = 33;
  _num_psi_bins = 64;

  double pT_bin_array[155] = {0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0, 5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25, 8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25, 11.5, 11.75, 12.0, 12.33, 12.66, 13.0, 13.33, 13.66, 14.0, 14.5, 15.0, 15.5, 16.0, 16.5, 17.0, 17.5, 18.0, 18.5, 19.0, 19.5, 20.0, 20.5, 21.0, 21.5, 22.0, 22.5, 23.0, 23.5, 24.0, 24.5, 25.0,25.5, 26.0, 26.5, 27.0, 27.5, 28.0, 28.5, 29.0, 29.5, 30.0, 30.5, 31.0, 31.5, 32.0, 32.5, 33.0, 33.5, 34.0, 34.5, 35.0,35.5, 36.0, 36.5, 37.0, 37.5, 38.0, 38.5, 39.0, 39.5, 40.0, 40.5, 41.0, 41.5, 42.0, 42.5, 43.0, 43.5, 44.0, 44.5, 45.0, 45.5, 46.0, 46.5, 47.0, 47.5, 48.0, 48.5, 49.0, 49.5, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0, 57.0, 58.0, 59.0, 60.0, 62.0, 64.0, 66.0, 68.0, 70.0, 72.0, 74.0, 76.0, 78.0, 80.0, 84.0, 88.0, 92.0, 96.0, 100.0, 105.0, 110.0, 120.0, 160.0};
  
  double RpT_bin_array[53] = {0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0, 34.0, 36.0, 38.0, 42.0, 46.0, 50.0, 55.0, 60.0, 62.0, 64.0, 66.0, 68.0, 70.0};

  double course_pT_bin_array[33] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 34.0, 38.0, 42.0, 46.0, 50.0, 55.0, 60.0, 70.0};

  double del_phi_bin_array[32];
  double psi_bin_array[64];

  psi_bin_width = 3.14159/(_num_delta_phi_bins-1);
  psi_halfbin_width = 3.14159/_num_psi_bins;

  for(int j=0; j<_num_psi_bins; j++) {
    psi_bin_array[j] = psi_halfbin_width + psi_bin_width*j; 
    cout<<psi_bin_array[j]<<", ";
  }

  for(int j=0; j<_num_delta_phi_bins-1; j++) {del_phi_bin_array[j] = psi_halfbin_width + psi_bin_width*j;}
 
  for(int i=0; i<(_num_recoil_pT_bins-1); i++){
    _recoil_pT_bin_edges.push_back(pT_bin_array[i]);
  }
  for(int i=0; i<(_num_course_pT_bins-1); i++){
    _course_pT_bin_edges.push_back(course_pT_bin_array[i]);
  }
  for(int i=0; i<(_num_RpT_bins-1); i++){
    _RpT_bin_edges.push_back(RpT_bin_array[i]);
  }
  for(int i=0; i<(_num_delta_phi_bins-1); i++){
    _delta_phi_bin_edges.push_back(del_phi_bin_array[i]);
  }
  for(int i=0; i<_num_psi_bins; i++){
    _psi_bin_edges.push_back(psi_bin_array[i]);
  }

  size_edges = _recoil_pT_bin_edges.size();
  size_courseedges = _course_pT_bin_edges.size();
  size_Redges = _RpT_bin_edges.size();
  size_dPedges = _delta_phi_bin_edges.size();
  size_dPsiedges = _psi_bin_edges.size(); 

  if(_num_recoil_pT_bins!=(size_edges+1)) {
    cout <<"_num_recoil_pT_bins should equal to _recoil_pT_bin_edges.size()+1"<<endl;
  }

  if(_num_RpT_bins!=(size_Redges+1)) {
    cout <<"_num_RpT_bins should equal to _RpT_bin_edges.size()+1"<<endl;
  }

  if(_num_course_pT_bins!=(size_courseedges+1)) {
    cout <<"_num_course_pT_bins should equal to _course_pT_bin_edges.size()+1"<<endl;
  }

  if(_num_delta_phi_bins!=(size_dPedges+1)) {
    cout <<"_num_delta_phi_bins should equal to _delta_phi_bin_edges.size()+1"<<endl;
  }

  if(_num_psi_bins!=(size_dPsiedges)) {
    cout <<"_num_delta_phi_bins should equal to _delta_phi_bin_edges.size()+1"<<endl;
  }
  
  // determine the bin centers for my pT binning scheme
  
  bincenters.push_back(0.125);
  for(int i=0; i<154; i++)
    {
      bincenters.push_back( (((pT_bin_array[i+1]-pT_bin_array[i])/2)+pT_bin_array[i]) );
    }
  bincenters.push_back(200.);


  // make course pT bin Map

  courseMap = new int[_num_recoil_pT_bins];

  if(pT_bin_array[0]>course_pT_bin_array[0]) cout<<"WTF!! Fine bin 0 is larger than course bin 0!!";

  courseMap[0]=0;

  int coursebin = 0;
  for(int i=1; i<_num_recoil_pT_bins; i++){

    if(pT_bin_array[i]>course_pT_bin_array[coursebin]){ 
      
      if(pT_bin_array[i-1]<course_pT_bin_array[coursebin]) cout<<"WTF!! "<<endl;
      
      if(coursebin<_num_course_pT_bins-1) coursebin++;
    }

    courseMap[i]=coursebin;
  }

  cout<<"THE BIN MAP: "<<endl;
  for(int i=0; i<_num_recoil_pT_bins; i++){
    cout<<i<<" "<<courseMap[i]<<endl;
  }


  // make course recoil pT bin Map

  RcourseMap = new int[_num_RpT_bins];

  if(RpT_bin_array[0]>course_pT_bin_array[0]) cout<<"WTF!! Fine bin 0 is larger than course bin 0!!";

  RcourseMap[0]=0;

  int Rcoursebin = 0;
  for(int i=1; i<_num_RpT_bins; i++){

    if( (RpT_bin_array[i]>course_pT_bin_array[Rcoursebin]) || ((RpT_bin_array[i]=course_pT_bin_array[Rcoursebin])&&(i==(_num_RpT_bins-1))) ){ 
      
      if(RpT_bin_array[i-1]<course_pT_bin_array[Rcoursebin]) cout<<"WTF!! "<<endl;
      
      if(Rcoursebin<_num_course_pT_bins-1) Rcoursebin++;
    }

    RcourseMap[i]=Rcoursebin;
  }

  cout<<"THE RECOIL BIN MAP: "<<endl;
  for(int i=0; i<_num_RpT_bins; i++){
    cout<<i<<" "<<RcourseMap[i]<<endl;
  }




  // initialize the "profile" instances

  recoil_pT_corr = new perBinProfile(_num_recoil_pT_bins,bincenters);
  recoil_pT_gen = new perBinProfile(_num_recoil_pT_bins,bincenters);
  recoil_pT_smR = new perBinProfile(_num_recoil_pT_bins,bincenters);
  
  recoil_pY_corr = new perBinProfile(_num_recoil_pT_bins,bincenters);
  recoil_pY_gen = new perBinProfile(_num_recoil_pT_bins,bincenters);
  recoil_pY_smR = new perBinProfile(_num_recoil_pT_bins,bincenters);
  
  TOT_phi_corr = new perBinProfile(_num_recoil_pT_bins,bincenters);
  TOT_phi_gen = new perBinProfile(_num_recoil_pT_bins,bincenters);
  TOT_phi_smR = new perBinProfile(_num_recoil_pT_bins,bincenters);

  recoil_pT_bin_meansY = new double[_num_recoil_pT_bins];
  recoil_pT_bin_meansY_gen = new double[_num_recoil_pT_bins];
  recoil_pT_bin_meansY_smR = new double[_num_recoil_pT_bins]; 

  // initialize efficiency classes and set parameters

  PParameterReader parm("parameters.rc"); 

  _ZSETEffCorrScaled = parm.GetBool("ZSETEffCorrScaled", kFALSE);
  bool _ZSETEffCorrRelative = parm.GetBool("ZSETEffCorrRelative", kFALSE);
  bool _ZSETEffCorrInterpolate = parm.GetBool("ZSETEffCorrInterpolate", kFALSE);
  double _ZSETEffCorrScale=200.;
  if (_ZSETEffCorrRelative) _ZSETEffCorrScale=20.;
  _ZSETEffCorrParameters = parm.GetVFloat("ZSETEffCorrParameters");

  _ZSETEffCorrParametersCCCC = parm.GetVFloat("ZSETEffCorrParametersCCCC");
  _ZSETEffCorrParametersCCEC = parm.GetVFloat("ZSETEffCorrParametersCCEC");
  _ZSETEffCorrParametersECEC = parm.GetVFloat("ZSETEffCorrParametersECEC");
  
  _ZSETEffCorrPTEpert = parm.GetInt("ZSETEffCorrPTEpert", 0);
  _ZSETEffCorrPTEpertBase = parm.GetVFloat("ZSETEffCorrPTEpertBase");
  _ZSETEffCorrPTEpertA = parm.GetVFloat("ZSETEffCorrPTEpertA");
  _ZSETEffCorrPTEpertB = parm.GetVFloat("ZSETEffCorrPTEpertB");
  _ZSETEffCorrPTEpertC = parm.GetVFloat("ZSETEffCorrPTEpertC");
  _ZSETEffCorrPTEpertD = parm.GetVFloat("ZSETEffCorrPTEpertD");
  _ZSETEffCorrPTEpertE = parm.GetVFloat("ZSETEffCorrPTEpertE");
  _ZSETEffCorrPTEpertF = parm.GetVFloat("ZSETEffCorrPTEpertF");
  _ZSETEffCorrPTEpertG = parm.GetVFloat("ZSETEffCorrPTEpertG");
  _ZSETEffCorrPTEpertH = parm.GetVFloat("ZSETEffCorrPTEpertH");
  _ZSETEffCorrPTEpertNorm = parm.GetVFloat("ZSETEffCorrPTEpertNorm");

  _useHack = parm.GetBool("SETuseHack");
  _useLumiBins = parm.GetBool("SETuseLumiBins");
  if (_useHack){
    char name[100];
    for (Int_t tv=0; tv<7; ++tv){
      std::vector< std::vector<float> >  _tempvec1;
      std::vector< std::vector<float> >  _tempvec2;
      for (Int_t tg=0; tg<7; ++tg){
        
        sprintf(name,"SETEffCorrDataRatioParametersBin%1d_%1d",tv,tg);
        if (tv==6)
          sprintf(name,"SETEffCorrDataRatioParametersBin_%1d",tg);
        _tempvec1.push_back(parm.GetVFloat(name));
        sprintf(name,"SETEffCorrDataRatioParameters2Bin%1d_%1d",tv,tg);
        if (tv==6)
          sprintf(name,"SETEffCorrDataRatioParameters2Bin_%1d",tg);
        _tempvec2.push_back(parm.GetVFloat(name));
      }
      _ZSETEffCorrDataRatioParameters.push_back(_tempvec1);
      _ZSETEffCorrDataRatioParameters2.push_back(_tempvec2);
      _tempvec1.clear();
      _tempvec2.clear();
    }
  }
  
  _ZSETEffCorrPTEpertBase_EC = parm.GetVFloat("ZSETEffCorrPTEpertBase_EC");
  _ZSETEffCorrPTEpertA_EC = parm.GetVFloat("ZSETEffCorrPTEpertA_EC");
  _ZSETEffCorrPTEpertB_EC = parm.GetVFloat("ZSETEffCorrPTEpertB_EC");
  _ZSETEffCorrPTEpertC_EC = parm.GetVFloat("ZSETEffCorrPTEpertC_EC");
  _ZSETEffCorrPTEpertD_EC = parm.GetVFloat("ZSETEffCorrPTEpertD_EC");
  _ZSETEffCorrPTEpertE_EC = parm.GetVFloat("ZSETEffCorrPTEpertE_EC");
  _ZSETEffCorrPTEpertF_EC = parm.GetVFloat("ZSETEffCorrPTEpertF_EC");
  _ZSETEffCorrPTEpertG_EC = parm.GetVFloat("ZSETEffCorrPTEpertG_EC");
  _ZSETEffCorrPTEpertH_EC = parm.GetVFloat("ZSETEffCorrPTEpertH_EC");
  _ZSETEffCorrPTEpertNorm_EC = parm.GetVFloat("ZSETEffCorrPTEpertNorm_EC");

  cout << " _ZSETEffCorrPTEpert " << _ZSETEffCorrPTEpert << endl;
  _SETeffic=0;
  if (doSETcorr) {
    if (_ZSETEffCorrPTEpert) {
      _SETeffic = new SETefficiencySmear(_ZSETEffCorrParametersCCCC,_ZSETEffCorrParametersCCEC,_ZSETEffCorrParametersECEC,
                          _ZSETEffCorrScaled,_ZSETEffCorrScale,_ZSETEffCorrRelative,_ZSETEffCorrInterpolate,
                          _ZSETEffCorrPTEpert,
                          &_ZSETEffCorrPTEpertBase,
                          &_ZSETEffCorrPTEpertA, &_ZSETEffCorrPTEpertB,
                          &_ZSETEffCorrPTEpertC, &_ZSETEffCorrPTEpertD,
                          &_ZSETEffCorrPTEpertE, &_ZSETEffCorrPTEpertF,
                          &_ZSETEffCorrPTEpertG, &_ZSETEffCorrPTEpertH,
                          &_ZSETEffCorrPTEpertNorm,
                          &_ZSETEffCorrDataRatioParameters, &_ZSETEffCorrDataRatioParameters2,
                          &_ZSETEffCorrPTEpertBase_EC,
                          &_ZSETEffCorrPTEpertA_EC, &_ZSETEffCorrPTEpertB_EC,
                          &_ZSETEffCorrPTEpertC_EC, &_ZSETEffCorrPTEpertD_EC,
                          &_ZSETEffCorrPTEpertE_EC, &_ZSETEffCorrPTEpertF_EC,
                          &_ZSETEffCorrPTEpertG_EC, &_ZSETEffCorrPTEpertH_EC,
                          &_ZSETEffCorrPTEpertNorm_EC, _useHack, _useLumiBins);
    } else {
      _SETeffic = new SETefficiencySmear(_ZSETEffCorrParameters,_ZSETEffCorrScaled);
    }
  }
 
  _UparaEffCorrOption = parm.GetInt("UparaEffCorrOption", 1);
  _ZUparaEffParameters = parm.GetVDouble("ZUparaEffCorrParameters_CC");

  _Z_u0_CC = parm.GetFloat("Z_u0_CC", 3.29440);
  _Z_s_CC = parm.GetFloat("Z_s_CC", 0.001787);
  _Z_u0_EC = parm.GetFloat("Z_u0_EC", 2.308);
  _Z_s_EC = parm.GetFloat("Z_s_EC", 0.0046);

 
  // Initialize relevant histograms

  char name[50], title[50],name2[50], title2[50], name3[50], title3[50];

 
  InstLumi_runNo_WZ = new TH2D("InstLumi_runNo_WZ","InstLumi_runNo_WZ",150,0.,15.0,30890,222027.5,252918.5);
  //InstLumi_runNo_WZ = new TH2D("InstLumi_runNo_WZ","InstLumi_runNo_WZ",100,0.,4.,500,21016699.5,21017200.5);
  InstLumi_SET_WZ = new TH2D("InstLumi_SET_WZ","InstLumi_SET_WZ",150,0,15.0,400,0,400);
  InstLumi_SET_WZ_orig = new TH2D("InstLumi_SET_WZ_orig","InstLumi_SET_WZ_orig",150,0,15.0,400,0,400);

  _recoil_pY_means = new TH1D("Mean_recoil_y","Mean_recoil_y",_num_recoil_pT_bins,-0.5,((double)_num_recoil_pT_bins-0.5));

  _recoil_pT_histograms = new TH2D*[_num_recoil_pT_bins];
  _recoil_pT_histograms_smR = new TH2D*[_num_recoil_pT_bins];
  _recoil_pT_histograms_gen = new TH2D*[_num_recoil_pT_bins];
  
  for(int i=0; i<_num_recoil_pT_bins; i++) {
    sprintf(name, "%s%d", "recoil_pT_", i);
    sprintf(title, "%s%d", "recoil x and y components for pT bin: ", i);
    _recoil_pT_histograms[i] = new TH2D(name, title, 440, -22, 22, 600, -30, 30);

    sprintf(name, "%s%d", "smRrecoil_pT_", i);
    sprintf(title, "%s%d", "recoil x and y components for smeared pT bin: ", i);
    _recoil_pT_histograms_smR[i] = new TH2D(name, title, 440, -22, 22, 600, -30, 30);

    sprintf(name, "%s%d", "genrecoil_pT_", i);
    sprintf(title, "%s%d", "recoil x and y components for gen pT bin: ", i);
    _recoil_pT_histograms_gen[i] = new TH2D(name, title, 440, -22, 22, 600, -30, 30);
  }

  _recoil_pT_hist_gen = new TH1D*[_num_recoil_pT_bins];
  _recoil_pT_hist_smR = new TH1D*[_num_recoil_pT_bins];
  _recoil_pT_hist_corr = new TH1D*[_num_recoil_pT_bins];
  _recoil_pX_hist_gen = new TH1D*[_num_recoil_pT_bins];
  _recoil_pX_hist_smR = new TH1D*[_num_recoil_pT_bins];
  _recoil_pX_hist_corr = new TH1D*[_num_recoil_pT_bins];
  _recoil_pY_hist_gen = new TH1D*[_num_recoil_pT_bins];
  _recoil_pY_hist_smR = new TH1D*[_num_recoil_pT_bins];
  _recoil_pY_hist_corr = new TH1D*[_num_recoil_pT_bins];
  _recoil_psi_hist_gen = new TH1D*[_num_recoil_pT_bins];
  _recoil_psi_hist_smR = new TH1D*[_num_recoil_pT_bins];
  _recoil_psi_hist_corr = new TH1D*[_num_recoil_pT_bins];

  _recoil_frac_gen = new TH1D*[_num_RpT_bins];
  _recoil_frac_smR = new TH1D*[_num_RpT_bins];
  _recoil_frac_corr = new TH1D*[_num_RpT_bins];

  for(int j=0; j<_num_RpT_bins; j++) {
    sprintf(name, "%s%d", "recoil_frac_gen_", j);
    sprintf(title, "%s%d", "per genpTbin recoil frac for RecpT bin: ", j);
    _recoil_frac_gen[j] = new TH1D(name, title, _num_recoil_pT_bins, -0.5, ((double)_num_recoil_pT_bins-0.5)); 
    sprintf(name2, "%s%d", "recoil_frac_smR_", j);
    sprintf(title2, "%s%d", "per smRpTbin recoil frac for RecpT bin: ", j);
    _recoil_frac_smR[j] = new TH1D(name2, title2, _num_recoil_pT_bins, -0.5, ((double)_num_recoil_pT_bins-0.5)); 
    sprintf(name3, "%s%d", "recoil_frac_corr_", j);
    sprintf(title3, "%s%d", "per corrpTbin recoil frac for RecpT bin: ", j);
    _recoil_frac_corr[j] = new TH1D(name3, title3, _num_recoil_pT_bins, -0.5, ((double)_num_recoil_pT_bins-0.5)); 
  }

  for(int j=0; j<_num_recoil_pT_bins; j++) {
    sprintf(name, "%s%d", "recoil_pX_gen_", j);
    sprintf(title, "%s%d", "recoil pX for gen bin: ", j);
    _recoil_pX_hist_gen[j] = new TH1D(name, title, 2000, -100.,100.);
    sprintf(name2, "%s%d", "recoil_pX_smR_", j);
    sprintf(title2, "%s%d", "recoil pX for smR bin: ", j);
    _recoil_pX_hist_smR[j] = new TH1D(name2, title2, 2000, -100.,100.);
    sprintf(name3, "%s%d", "recoil_pX_corr_", j);
    sprintf(title3, "%s%d", "recoil pX for corr bin: ", j);
    _recoil_pX_hist_corr[j] = new TH1D(name3, title3, 2000, -100.,100.);

    sprintf(name, "%s%d", "recoil_pY_gen_", j);
    sprintf(title, "%s%d", "recoil pY for gen bin: ", j);
    _recoil_pY_hist_gen[j] = new TH1D(name, title, 2000, -100.,100.);
    sprintf(name2, "%s%d", "recoil_pY_smR_", j);
    sprintf(title2, "%s%d", "recoil pY for smR bin: ", j);
    _recoil_pY_hist_smR[j] = new TH1D(name2, title2, 2000, -100.,100.);
    sprintf(name3, "%s%d", "recoil_pY_corr_", j);
    sprintf(title3, "%s%d", "recoil pY for corr bin: ", j);
    _recoil_pY_hist_corr[j] = new TH1D(name3, title3, 2000, -100.,100.);

    sprintf(name, "%s%d", "recoil_pT_gen_", j);
    sprintf(title, "%s%d", "recoil pT for gen bin: ", j);
    _recoil_pT_hist_gen[j] = new TH1D(name, title, _num_RpT_bins, -0.5, ((double)_num_RpT_bins-0.5)); 
    sprintf(name2, "%s%d", "recoil_pT_smR_", j);
    sprintf(title2, "%s%d", "recoil pT for smR bin: ", j);
    _recoil_pT_hist_smR[j] = new TH1D(name2, title2, _num_RpT_bins, -0.5, ((double)_num_RpT_bins-0.5)); 
    sprintf(name3, "%s%d", "recoil_pT_corr_", j);
    sprintf(title3, "%s%d", "recoil pT for corr bin: ", j);
    _recoil_pT_hist_corr[j] = new TH1D(name3, title3, _num_RpT_bins, -0.5, ((double)_num_RpT_bins-0.5)); 

    sprintf(name, "%s%d", "recoil_psi_gen_", j);
    sprintf(title, "%s%d", "recoil psi for gen bin: ", j);
    _recoil_psi_hist_gen[j] = new TH1D(name, title, _num_psi_bins, -0.5, ((double)_num_psi_bins-0.5));  
    sprintf(name2, "%s%d", "recoil_psi_smR_", j);
    sprintf(title2, "%s%d", "recoil psi for smR bin: ", j);
    _recoil_psi_hist_smR[j] = new TH1D(name2, title2, _num_psi_bins, -0.5, ((double)_num_psi_bins-0.5)); 
    sprintf(name3, "%s%d", "recoil_psi_corr_", j);
    sprintf(title3, "%s%d", "recoil psi for corr bin: ", j);
    _recoil_psi_hist_corr[j] = new TH1D(name3, title3, _num_psi_bins, -0.5, ((double)_num_psi_bins-0.5));  
  }

 
  _SEThist = new TH1D**[_num_course_pT_bins];
  
  for(int i=0; i<_num_course_pT_bins; i++){
    _SEThist[i] = new TH1D*[_num_course_pT_bins];
    
    for(int j=0; j<_num_course_pT_bins; j++){
      
      TString SEThistname;
      SEThistname+="SEThist_";
      SEThistname+=i;
      SEThistname+="_";
      SEThistname+=j;
      
      _SEThist[i][j] = new TH1D(SEThistname,SEThistname,500,0.,500.);
      
    }
    
  }

  _Zspect = new TH1D("Zspect","Zspect",400,0.,100.);
  _Zspect_smR = new TH1D("Zspect_smR","Zspect_smR",400,0.,100.);
  _Recspect = new TH1D("Recspect","Recoil Spectrum",400,0.,100.);

  _theSETweights = new TH1D("theSETweights","theSETweights",8000,0,1000);
  _theUPweights = new TH1D("theUPweights","theUPweights",8000,0,1000);
  _theunfoldweights = new TH1D("theunfoldweights","theunfoldweights",8000,0,1000);
  
  // initialize reweighting matrix...set elements and normalizations to 0

  cout<<"initializing reweighting matrices...setting elements and normalizations to 0"<<endl;

  _ZpT_Dist = new double[_num_recoil_pT_bins];
  _pT_Phi_Norm = new double[_num_recoil_pT_bins];

  _pT_Phi = new double**[_num_recoil_pT_bins];
  _smR_Norm = new double**[_num_recoil_pT_bins];
  _pT_Psi_R_Dist = new double**[_num_recoil_pT_bins];
  _pT_Psi_R_Count = new double**[_num_recoil_pT_bins];

  for(int i=0; i<_num_recoil_pT_bins; i++){
    
    _pT_Phi_Norm[i] = 0;
    _ZpT_Dist[i] = 0;

    _pT_Phi[i] = new double*[_num_recoil_pT_bins];

    for(int j=0; j<_num_recoil_pT_bins; j++){
      _pT_Phi[i][j]  = new double[_num_delta_phi_bins];
      for(int k=0; k<_num_delta_phi_bins; k++){
	_pT_Phi[i][j][k] = 0;
      }
    }

    _smR_Norm[i] = new double*[_num_psi_bins]; 
    _pT_Psi_R_Dist[i] = new double*[_num_psi_bins]; 
    _pT_Psi_R_Count[i] = new double*[_num_psi_bins]; 
 
    for(int j=0; j<_num_psi_bins; j++){
      _smR_Norm[i][j] = new double[_num_RpT_bins];
      _pT_Psi_R_Dist[i][j] = new double[_num_RpT_bins];
      _pT_Psi_R_Count[i][j] = new double[_num_RpT_bins];
 
      for(int k=0; k<_num_RpT_bins; k++){
	_smR_Norm[i][j][k]=0;
	_pT_Psi_R_Dist[i][j][k]=0;
	_pT_Psi_R_Count[i][j][k]=0;
      }
    }
  }   

  cout<<"done initializing reweighting matrix"<<endl;

  // Initial "Guess" Rec Psi Distribution

  cout<<"initializing rec psi guess distribution..."<<endl;

  for(int i=0; i<_num_recoil_pT_bins; i++){
    for(int j=0; j<_num_psi_bins; j++){
      for(int k=0; k<_num_RpT_bins; k++){
	_pT_Psi_R_Count[i][j][k]++;
      }      
    }
  }

  psipos=0;

  cout<<"done...Initial Rec Psi value 1 2 6: "<<_pT_Psi_R_Count[1][2][6]<<endl;


  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////















////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
double CalcSETEfficiency(float scalarEt_All, float lumi, float epT1, float epT2, float eta1, float eta2)
{
  float eff=1;
  if( !_SETeffic ) return eff;

  if (_ZSETEffCorrPTEpert) {
    eff=_SETeffic->getSETeff(scalarEt_All, lumi, epT1, epT2, false, false, eta1, eta2);
  } else {
    eff=_SETeffic->getSETeff(scalarEt_All, lumi);
  }

  return eff;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////















/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
double CalcUparaEfficiency(float upara1, float upara2)
{
  float eff=1;
 
  double the_upar[2];
  double upara_eff[2];
  
  the_upar[0]=upara1;
  the_upar[1]=upara2;

  // calculate uparallel efficiency for CC and EC regions

  for(int i=0; i<2; i++){

    if(_UparaEffCorrOption == 0) {
      if(the_upar[i]<_Z_u0_CC) upara_eff[i] = 1.;
      else upara_eff[i] = 1. - _Z_s_CC*(the_upar[i] - _Z_u0_CC);
    } else { // for _ZUparaEffCorrOption!=0, used for real data, two linear functions
      if(the_upar[i] < _ZUparaEffParameters[0])
	upara_eff[i] = 1. - _ZUparaEffParameters[1] * (the_upar[i] - _ZUparaEffParameters[0]);
      else
	upara_eff[i] = 1. - _ZUparaEffParameters[2] * (the_upar[i] - _ZUparaEffParameters[0]);
    }
  }
    
  eff = upara_eff[0]*upara_eff[1];

  return eff;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////















/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int MakeMapMatrices(){

  line=0;
  ifstream MapFile_PMCS(pmcs_mapname, ios::in);

  double ***_pT_Phi_Count;

  _pT_Phi_Count = new double**[_num_recoil_pT_bins];
  
  for(int i=0; i<_num_recoil_pT_bins; i++){

    _pT_Phi_Norm[i]=0;
    _pT_Phi_Count[i] = new double*[_num_recoil_pT_bins];

    for(int j=0; j<_num_recoil_pT_bins; j++){
      _pT_Phi_Count[i][j]  = new double[_num_delta_phi_bins];
      for(int k=0; k<_num_delta_phi_bins; k++){
	_pT_Phi_Count[i][j][k] = 0;
      }
    }
  }

 
  // DB Added electron eta to ascii file, should really replace ascii file by nice tree, but I'm not there yet...
  while(!MapFile_PMCS.eof()) {
    MapFile_PMCS >> Zpx_gen >> Zpy_gen >> Zpx_smear >> Zpy_smear >> Ex_before >> Ey_before >> theSET >> upar1 >> upar2 >> epT1 >> epT2 >> eleta1 >> eleta2 >> runno >> theLumi >> evttype >> evtweight;


    double zpTgen = sqrt(Zpy_gen*Zpy_gen +Zpx_gen*Zpx_gen);
    double zpTsmear = sqrt(Zpy_smear*Zpy_smear +Zpx_smear*Zpx_smear);
    
    _Zspect->Fill(zpTgen);
    _Zspect_smR->Fill(zpTsmear);
    
    // determine which smeared pT bin to use
    int smRpTBin = -1;
    if(zpTsmear<=_recoil_pT_bin_edges[0]) smRpTBin = 0;
    else if(zpTsmear>_recoil_pT_bin_edges[size_edges-1]) smRpTBin = size_edges;
    else {
      for(int ii=0; ii<size_edges-1; ii++){
	if((zpTsmear>_recoil_pT_bin_edges[ii]) && (zpTsmear<=_recoil_pT_bin_edges[ii+1])) smRpTBin = ii+1;
      }
    }
    
    // determine which gen pT bin to use
    int genpTBin = -1;
    if(zpTgen<=_recoil_pT_bin_edges[0]) genpTBin = 0;
    else if(zpTgen>_recoil_pT_bin_edges[size_edges-1]) genpTBin = size_edges;
    else {
      for(int ii=0; ii<size_edges-1; ii++){
	if((zpTgen>_recoil_pT_bin_edges[ii]) && (zpTgen<=_recoil_pT_bin_edges[ii+1])) genpTBin = ii+1;
      }
    }

    
    // calculate delta phi
    
    double phi_tmp = atan2(Zpy_gen, Zpx_gen);
    double PhiGen = (phi_tmp>=0.)?phi_tmp:(6.28319+phi_tmp);
    
    phi_tmp = atan2(Zpy_smear, Zpx_smear);
    double PhiSmear = (phi_tmp>=0.)?phi_tmp:(6.28319+phi_tmp);
    
    double deltaPhi= fabs(PhiGen-PhiSmear);
    if(deltaPhi>3.14159) deltaPhi = 6.28319 - deltaPhi;
    
    if(deltaPhi<0) cout<<"cannot have neg delta phi!!! "<<deltaPhi<<endl;
    
    // determine which delta phi bin
    
    int dPhiBin = -1;
    if(deltaPhi<=_delta_phi_bin_edges[0]) dPhiBin = 0;
    else if(deltaPhi>_delta_phi_bin_edges[size_dPedges-1]) dPhiBin = size_dPedges;
    else {
      for(int ii=0; ii<size_dPedges-1; ii++){
	if((deltaPhi>_delta_phi_bin_edges[ii]) && (deltaPhi<=_delta_phi_bin_edges[ii+1])) dPhiBin = ii+1;
	}
    }

    if(MapFile_PMCS.eof()) break;

    _ZpT_Dist[genpTBin]+=evtweight;
    _pT_Phi_Count[genpTBin][smRpTBin][dPhiBin]+=evtweight;
    _pT_Phi_Norm[genpTBin]+=evtweight;

    //   _WM_Norm[genpTBin]++;

    if(line%10000==0) cout<<"  Reading Map line "<<line<<endl;
    line++;
  }

  // Loop over recoil file...Fill initial Recoil Dist histos
  
  cout<<data_recoilname<<endl;

  ifstream RecoilFile_DATA(data_recoilname, ios::in);
  line=0;
  
  while(!RecoilFile_DATA.eof()) {
    RecoilFile_DATA >> Zpx_gen >> Zpy_gen >> Zpx_smear >> Zpy_smear >> Ex_before >> Ey_before >> theSET >> upar1 >> upar2 >> epT1 >> epT2 >> eleta1 >> eleta2 >> runno >> theLumi >> evttype >> evtweight;

    
    double zpTsmear = sqrt(Zpx_smear*Zpx_smear + Zpx_smear*Zpx_smear);
    double RecpT = sqrt(Ex_before*Ex_before + Ey_before*Ey_before);

    _Recspect->Fill(RecpT );

    // determine which smeared pT bin to use
    int smRpTBin = -1;
    if(zpTsmear<=_recoil_pT_bin_edges[0]) smRpTBin = 0;
    else if(zpTsmear>_recoil_pT_bin_edges[size_edges-1]) smRpTBin = size_edges;
    else {
      for(int ii=0; ii<size_edges-1; ii++){
	if((zpTsmear>_recoil_pT_bin_edges[ii]) && (zpTsmear<=_recoil_pT_bin_edges[ii+1])) smRpTBin = ii+1;
      }
    }


    // determine which recoil pT bin to use
    int RecpTBin = -1;
    if(RecpT<=_RpT_bin_edges[0]) RecpTBin = 0;
    else if(RecpT>_RpT_bin_edges[size_Redges-1]) RecpTBin = size_Redges;
    else {
      for(int ii=0; ii<size_Redges-1; ii++){
	if((RecpT>_RpT_bin_edges[ii]) && (RecpT<=_RpT_bin_edges[ii+1])) RecpTBin = ii+1;
      }
    }

    if(line%10000==0) cout<<"  Reading Recoil line "<<line<<endl;
    line++;
  }

  NumRecEvts=line;

  // Kill Low Stats Bins...

  kill_mode=false;
  
  if(kill_mode){

    cout<<"Killing Low Stats Bins"<<endl;
    
    for(int gnB=0; gnB<_num_recoil_pT_bins; gnB++){_pT_Phi_Norm[gnB]=0;}
    
    for(int gnB=0; gnB<_num_recoil_pT_bins; gnB++){ 
      for(int smRB=0; smRB<_num_recoil_pT_bins; smRB++){
	for(int dpB=0; dpB<_num_delta_phi_bins; dpB++){
	
	  if(_pT_Phi_Count[gnB][smRB][dpB]<50){
	    _pT_Phi_Count[gnB][smRB][dpB]=0;
	  }
	  
	  _pT_Phi_Norm[gnB]+=_pT_Phi_Count[gnB][smRB][dpB];
  
	}
      }
    }

    // Make sure diagonal elements are equal to 1

    for(int i=0; i<_num_recoil_pT_bins; i++){
      if(_pT_Phi_Count[i][i][0]==0){
	cout<<"Zero Diagonal Element! "<< i << endl;
	for(int dpB=0; dpB<_num_delta_phi_bins; dpB++){
	  _pT_Phi_Count[i][i][dpB] = 0;
	}
	_pT_Phi_Count[i][i][0]=1;
	_pT_Phi_Norm[i]=1;
      }
    }
  }


  // Normalize weight matrices...

  cout<<"normalizing weight matrices"<<endl;

  for(int gnB=0; gnB<_num_recoil_pT_bins; gnB++){
    for(int smRB=0; smRB<_num_recoil_pT_bins; smRB++){
      for(int dpB=0; dpB<_num_delta_phi_bins; dpB++){
       
	if(_pT_Phi_Norm[gnB]!=0) _pT_Phi[gnB][smRB][dpB]=_pT_Phi_Count[gnB][smRB][dpB]/_pT_Phi_Norm[gnB];
	else{
	  _pT_Phi[gnB][smRB][dpB]=0;
	  if((gnB==smRB) && (dpB==0)) _pT_Phi[gnB][smRB][dpB]=1;
	}
      } //end loop over dpB

      // Fill counthist and weighthist
      // counthist->SetBinContent(gnB,smRB,_W_M_noPhi[gnB][smRB]);
      // weighthist->SetBinContent(gnB,smRB,_W_M_noPhi[gnB][smRB]);

    } //end loop of smRB
    if(_pT_Phi_Norm[gnB]==0) cout<<"zero bin in pT_Phi_Norm!!! "<<gnB<<endl;
  } //end loop over gnB

  // Normalize ZpT Bin Spectrum

  cout<<"normalizing Z pT Spectrum"<<endl;

  double ZNorm=0;
  for(int i=0; i<_num_recoil_pT_bins; i++){
  ZNorm += _ZpT_Dist[i];
  }
  if(ZNorm!=0){
    for(int i=0; i<_num_recoil_pT_bins; i++){
      _ZpT_Dist[i] = _ZpT_Dist[i]/ZNorm;
    }
  } 
  else cout<<"DIVIDE BY ZERO!!!"<<endl;
  
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CalculateRecPsiMatrix(){


  //Normalize Opening Angle/Recoil Distribution
  
  cout<<"Normalizing opening angle/recoil distribution..."<<endl;
  
  for(int i=0; i<_num_recoil_pT_bins; i++){
    double OANorm=0;
    
    for(int j=0; j<_num_psi_bins; j++){
      for(int k=0; k<_num_RpT_bins; k++){
	OANorm += _pT_Psi_R_Count[i][j][k];
      }
    }
    
    for(int j=0; j<_num_psi_bins; j++){
      for(int k=0; k<_num_RpT_bins; k++){
	if(OANorm!=0) _pT_Psi_R_Dist[i][j][k]=_pT_Psi_R_Count[i][j][k]/OANorm;
	else cout<<"DIVIDE BY ZERO!"<<endl;
      }
    }
  }

  cout<<"Calculating smR_Norm..."<<endl;

  int PhiBin;
  double PsiRecProb,ZpTProb;
  double PsiRecNorm = 0;
  double multfact;

  for(int smRB=0; smRB<_num_recoil_pT_bins; smRB++){
    if(smRB%10==0) cout<<(_num_recoil_pT_bins - smRB)<<endl;
    for(int dpBs=0; dpBs<_num_psi_bins; dpBs++){
      for(int RecB=0; RecB<_num_RpT_bins; RecB++){

	PsiRecNorm = 0;
								    
	for(int dpD=0; dpD<_num_psi_bins; dpD++){

	  PhiBin=(int)fabs(dpBs-dpD);
	  if(PhiBin>(_num_delta_phi_bins-1)) PhiBin = _num_psi_bins - PhiBin;

	  if( (PhiBin==0) || (PhiBin==(_num_delta_phi_bins-1)) ) multfact = 1;
	  else multfact = 0.5;

	  for(int gnBD=0; gnBD<_num_recoil_pT_bins; gnBD++){ 
	    
	    PsiRecProb = _pT_Psi_R_Dist[gnBD][dpD][RecB];
	    ZpTProb = _ZpT_Dist[gnBD];
  	    PsiRecNorm += (multfact*((_pT_Phi[gnBD][smRB][PhiBin])*PsiRecProb*ZpTProb));
	  }
	}
	_smR_Norm[smRB][dpBs][RecB] = PsiRecNorm;
      }
    }
  }

  cout<<"Done Creating RecPsi Matrices..."<<endl;

  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////















///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int LoadRecoilFile(){

  TRandom randevt;
  int rec_evts_used=0;

  if(num_rec_evts_touse==-1) num_rec_evts_touse = NumRecEvts;

  cout<<data_recoilname<<endl;

  ifstream RecoilFile_DATA(data_recoilname, ios::in);
  line=0;
  
  while(!RecoilFile_DATA.eof()) {
    RecoilFile_DATA >> Zpx_gen >> Zpy_gen >> Zpx_smear >> Zpy_smear >> Ex_before >> Ey_before >> theSET >> upar1 >> upar2 >> epT1 >> epT2 >> eleta1 >> eleta2 >> runno >> theLumi >> evttype >> evtweight;

    vector<double> EvtVec;
    
    ZpT_gen = sqrt(Zpy_gen*Zpy_gen +Zpx_gen*Zpx_gen);
    ZpT_smear = sqrt(Zpy_smear*Zpy_smear +Zpx_smear*Zpx_smear);
    RecpT = sqrt(Ex_before*Ex_before + Ey_before*Ey_before); 
    
    TVector2 E_vec(Ex_before, Ey_before);
    
    TVector2 Z_vec_smR(Zpx_smear, Zpy_smear);
    TVector2 perp_direction_smR = Z_vec_smR.Rotate(TMath::Pi()/2);
    
    Ey_rot_smR = E_vec * Z_vec_smR.Unit();
    Ex_rot_smR = E_vec * perp_direction_smR.Unit();

    PhiRecRot_smR = atan2(Ex_rot_smR, -Ey_rot_smR);

    TVector2 Z_vec_gen(Zpx_gen, Zpy_gen);
    TVector2 perp_direction_gen = Z_vec_gen.Rotate(TMath::Pi()/2);
    
    Ey_rot_gen = E_vec * Z_vec_gen.Unit();
    Ex_rot_gen = E_vec * perp_direction_gen.Unit();
    
    PhiRecRot_gen = atan2(Ex_rot_gen, -Ey_rot_gen);

    // determine which smeared pT bin to use
    smRpTBin = -1;
    if(ZpT_smear<=_recoil_pT_bin_edges[0]) smRpTBin = 0;
    else if(ZpT_smear>_recoil_pT_bin_edges[size_edges-1]) smRpTBin = size_edges;
    else {
      for(int ii=0; ii<size_edges-1; ii++){
	if((ZpT_smear>_recoil_pT_bin_edges[ii]) && (ZpT_smear<=_recoil_pT_bin_edges[ii+1])) smRpTBin = ii+1;
      }
    }

    // determine which recoil pT bin to use
    RecpTBin = -1;
    if(RecpT<=_RpT_bin_edges[0]) RecpTBin = 0;
    else if(RecpT>_RpT_bin_edges[size_Redges-1]) RecpTBin = size_Redges;
    else {
      for(int ii=0; ii<size_Redges-1; ii++){
	if((RecpT>_RpT_bin_edges[ii]) && (RecpT<=_RpT_bin_edges[ii+1])) RecpTBin = ii+1;
      }
    }

    thePsiFill_smR = fabs(PhiRecRot_smR);
    thePsi_smR = 3.141519 - PhiRecRot_smR;

    // determine which smeared Psi bin to use

    PsiBin = -1;
    if(thePsi_smR<=_psi_bin_edges[0]) PsiBin = 0;
    else if(thePsi_smR>_psi_bin_edges[size_dPsiedges-1]) PsiBin = 0;
    else {
      for(int ii=0; ii<size_dPsiedges-1; ii++){
	if((thePsi_smR>_psi_bin_edges[ii]) && (thePsi_smR<=_psi_bin_edges[ii+1])) PsiBin = ii+1;
      }
    }

    // determine which gen pT bin to use
    genpTBin = -1;
    if(ZpT_gen<=_recoil_pT_bin_edges[0]) genpTBin = 0;
    else if(ZpT_gen>_recoil_pT_bin_edges[size_edges-1]) genpTBin = size_edges;
    else {
      for(int ii=0; ii<size_edges-1; ii++){
	if((ZpT_gen>_recoil_pT_bin_edges[ii]) && (ZpT_gen<=_recoil_pT_bin_edges[ii+1])) genpTBin = ii+1;
      }
    }

    double psi_halfbin_width = 3.14159/_num_psi_bins;
    double PsiBinCenter = PsiBin*psi_bin_width;
    if( (PsiBin==0) && (thePsi_smR>(6.28-psi_halfbin_width)) ) PsiBinCenter = 2*3.14159265;
    psipos = thePsi_smR - PsiBinCenter;


    if( fabs(psipos) > psi_halfbin_width ) cout<<"Psipos is Wrong!!! "<<psipos<<endl;

    thePsiFill_gen = fabs(PhiRecRot_gen);
    thePsi_gen = 3.141519 - PhiRecRot_gen;

    // determine which gen Psi bin to use

    PsiBin_true = -1;
    if(thePsi_gen<=_psi_bin_edges[0]) PsiBin_true = 0;
    else if(thePsi_gen>_psi_bin_edges[size_dPsiedges-1]) PsiBin_true = 0;
    else {
      for(int ii=0; ii<size_dPsiedges-1; ii++){
	if((thePsi_gen>_psi_bin_edges[ii]) && (thePsi_gen<=_psi_bin_edges[ii+1])) PsiBin_true = ii+1;
      }
    }


    // determine course recoil pT bin number

    courseBinR = -1;
    if(RecpT<_course_pT_bin_edges[0]) courseBinR = 0;
    else if(RecpT>_course_pT_bin_edges[size_courseedges-1]) courseBinR = size_courseedges;
    else {
      for(int ii=0; ii<size_courseedges-1; ii++){
	if((RecpT>_course_pT_bin_edges[ii]) && (RecpT<=_course_pT_bin_edges[ii+1])) courseBinR = ii+1;
      }
    }

    // sum the recoil_y in each gen pT bin, weighted by likelihood
    
    EvtVec.push_back(Zpx_gen);          //0
    EvtVec.push_back(Zpy_gen);          //1
    EvtVec.push_back(ZpT_gen);          //2
    EvtVec.push_back(Zpx_smear);        //3
    EvtVec.push_back(Zpy_smear);        //4
    EvtVec.push_back(ZpT_smear);        //5
    EvtVec.push_back(Ex_before);        //6
    EvtVec.push_back(Ey_before);        //7
    EvtVec.push_back(RecpT);            //8
    EvtVec.push_back(Ex_rot_gen);       //9
    EvtVec.push_back(Ey_rot_gen);       //10
    EvtVec.push_back(PhiRecRot_gen);    //11
    EvtVec.push_back(Ex_rot_smR);       //12
    EvtVec.push_back(Ey_rot_smR);       //13
    EvtVec.push_back(PhiRecRot_smR);    //14
    EvtVec.push_back(thePsi_gen);       //15
    EvtVec.push_back(thePsiFill_gen);   //16
    EvtVec.push_back(thePsi_smR);       //17
    EvtVec.push_back(thePsiFill_smR);   //18
    EvtVec.push_back((double)genpTBin); //19
    EvtVec.push_back((double)smRpTBin); //20
    EvtVec.push_back((double)RecpTBin); //21
    EvtVec.push_back((double)PsiBin);   //22 
    EvtVec.push_back((double)PsiBin_true);//23 
    EvtVec.push_back(psipos);           //24
    EvtVec.push_back(theSET);           //25
    EvtVec.push_back(evttype);          //26
    EvtVec.push_back(evtweight);        //27
    EvtVec.push_back(theLumi);          //28
    EvtVec.push_back(runno);            //29
    EvtVec.push_back(upar1);            //30
    EvtVec.push_back(upar2);            //31
    EvtVec.push_back(epT1);             //32
    EvtVec.push_back(epT2);             //33
    EvtVec.push_back(eleta1);		//34
    EvtVec.push_back(eleta2);		//35

    double ranuse = NumRecEvts*randevt.Rndm();
    if(ranuse<=num_rec_evts_touse){
      RecDatVec.push_back(EvtVec);
      rec_evts_used++;
    }

    if(line%10000==0) cout<<"  Reading Recoil line "<<line<<" "<<the_smR_Norm<<endl;
    line++;
  }

  cout<<line<<" recoil events total, "<<rec_evts_used<<" events to be used."<<endl;

  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DetermineRecoilMeans(bool final_iter){

  if(doSETcorr) cout<<"Doing SET correction"<<endl;

  // Reset Opening Angle/Recoil Histos

  for(int i=0; i<_num_recoil_pT_bins; i++){
    for(int j=0; j<_num_psi_bins; j++){
      for(int k=0; k<_num_RpT_bins; k++){
	_pT_Psi_R_Count[i][j][k]=0;
      }
    }
  }

  // Loop over recoil file...determine mean recoil_y...per gen bin
  
  line=0;
      
  for(int it=0; it<((int)RecDatVec.size()); it++){
    
    vector<double> EvtVec = RecDatVec.at(it);

    Zpx_gen = EvtVec.at(0);
    Zpy_gen = EvtVec.at(1);
    ZpT_gen = EvtVec.at(2);
    Zpx_smear = EvtVec.at(3);
    Zpy_smear = EvtVec.at(4);
    ZpT_smear = EvtVec.at(5);
    Ex_before = EvtVec.at(6);
    Ey_before = EvtVec.at(7);
    RecpT = EvtVec.at(8);
    Ex_rot_gen = EvtVec.at(9);
    Ey_rot_gen = EvtVec.at(10);
    PhiRecRot_gen = EvtVec.at(11);
    Ex_rot_smR = EvtVec.at(12);
    Ey_rot_smR = EvtVec.at(13);
    PhiRecRot_smR = EvtVec.at(14);
    thePsi_gen = EvtVec.at(15);
    thePsiFill_gen = EvtVec.at(16);
    thePsi_smR = EvtVec.at(17);
    thePsiFill_smR = EvtVec.at(18);
    genpTBin = (int) EvtVec.at(19);
    smRpTBin = (int) EvtVec.at(20);
    RecpTBin = (int) EvtVec.at(21);
    PsiBin = (int) EvtVec.at(22);
    PsiBin_true = (int) EvtVec.at(23);
    psipos = EvtVec.at(24);
    theSET = EvtVec.at(25);
    evttype = EvtVec.at(26);
    evtweight = EvtVec.at(27);
    theLumi = EvtVec.at(28); 
    runno = EvtVec.at(29); 
    upar1 = EvtVec.at(30);
    upar2 = EvtVec.at(31);
    epT1 = EvtVec.at(32);
    epT2 = EvtVec.at(33);
    eleta1 = EvtVec.at(34);
    eleta2 = EvtVec.at(35);

    if(final_iter){
      recoil_pT_smR->FillQuant(smRpTBin,sqrt(Ey_rot_smR*Ey_rot_smR + Ex_rot_smR*Ex_rot_smR),1.0); 
      recoil_pY_smR->FillQuant(smRpTBin,Ey_rot_smR,1.0);
      TOT_phi_smR->FillQuant(smRpTBin,PhiRecRot_smR,1.0);
           
      _recoil_pX_hist_smR[smRpTBin]->Fill(Ex_rot_smR);
      _recoil_pY_hist_smR[smRpTBin]->Fill(Ey_rot_smR);
      _recoil_pT_hist_smR[smRpTBin]->Fill(RecpTBin);
      _recoil_psi_hist_smR[smRpTBin]->Fill(PsiBin);       

      recoil_pT_gen->FillQuant(genpTBin,sqrt(Ey_rot_gen*Ey_rot_gen + Ex_rot_gen*Ex_rot_gen),1.0); 
      recoil_pY_gen->FillQuant(genpTBin,Ey_rot_gen,1.0); 
      TOT_phi_gen->FillQuant(genpTBin,PhiRecRot_gen,1.0);
      
      _recoil_pX_hist_gen[genpTBin]->Fill(Ex_rot_gen);
      _recoil_pY_hist_gen[genpTBin]->Fill(Ey_rot_gen);
      _recoil_pT_hist_gen[genpTBin]->Fill(RecpTBin);
      _recoil_psi_hist_gen[genpTBin]->Fill(PsiBin_true);       
    }


    // Determine Efficiency Related Weights
    double Zeffic = CalcSETEfficiency((float)theSET, (float)theLumi, (float)epT1, (float)epT2,(float) eleta1,(float) eleta2);
    double Ueffic = CalcUparaEfficiency(upar1,upar2);

    double SETweight,Uparaweight;
    SETweight=1;
    Uparaweight=1;

    if(doSETcorr){
      if(Zeffic>0) SETweight = 1/Zeffic;
      else SETweight=1;

      _theSETweights->Fill(SETweight);

      if(SETweight>5.) {
        cout << " SETweight " << SETweight << endl;
        SETweight=5.;
      }
    }

    if(doUparcorr){
      if(Ueffic>0) Uparaweight = 1/Ueffic;
      else Uparaweight=1;

      _theUPweights->Fill(Uparaweight);

      if(Uparaweight>5.) {
        cout << " Uparaweight " << Uparaweight << endl;
        Uparaweight=5.;
      }
    }

    double totweight=Uparaweight*SETweight*evtweight;

    // sum the recoil_y in each gen pT bin, and psi pT bin weighted by likelihood
    
    int PhiBin;
    double the_ZpT, PhiRecRot_corr, the_pT_Phi,the_pT_Psi_R, RPweight, DPsi;

    the_smR_Norm = _smR_Norm[smRpTBin][PsiBin][RecpTBin]; 

    for(int DgenpTBin=0; DgenpTBin<_num_recoil_pT_bins; DgenpTBin++){

      the_ZpT = _ZpT_Dist[DgenpTBin];
      for(int DPsiBin=0; DPsiBin<_num_psi_bins; DPsiBin++){

	PhiBin=(int)fabs(DPsiBin-PsiBin);
	if(PhiBin>(_num_delta_phi_bins-1)) PhiBin = _num_psi_bins - PhiBin;
	the_pT_Phi = _pT_Phi[DgenpTBin][smRpTBin][PhiBin];
	the_pT_Psi_R = _pT_Psi_R_Dist[DgenpTBin][DPsiBin][RecpTBin];

	if( !((PhiBin==0) || (PhiBin==(_num_delta_phi_bins-1))) ) the_pT_Phi = 0.5*the_pT_Phi;

	if(the_smR_Norm!=0) RPweight = totweight*((the_pT_Phi*the_pT_Psi_R*the_ZpT)/the_smR_Norm);
	else RPweight=0;

	_theunfoldweights->Fill(RPweight);

	// Rotate+++++++++++++++++++++++++++++++++++++++++++++++

	if(final_iter){

	  DPsi = DPsiBin*psi_bin_width + psipos;
 	  Ey_rot = sqrt(Ex_rot_smR*Ex_rot_smR + Ey_rot_smR*Ey_rot_smR)*cos(DPsi);
	  Ex_rot = sqrt(Ex_rot_smR*Ex_rot_smR + Ey_rot_smR*Ey_rot_smR)*sin(DPsi);
	  PhiRecRot_corr = atan2(Ex_rot, -Ey_rot);

	  recoil_pT_corr->FillQuant(DgenpTBin,sqrt(Ey_rot*Ey_rot + Ex_rot*Ex_rot),RPweight); 
	  recoil_pY_corr->FillQuant(DgenpTBin,Ey_rot,RPweight); 
	  TOT_phi_corr->FillQuant(DgenpTBin,PhiRecRot_corr,RPweight);
  	  _recoil_pX_hist_corr[DgenpTBin]->Fill(Ex_rot,RPweight);
	  _recoil_pY_hist_corr[DgenpTBin]->Fill(Ey_rot,RPweight);
	  _recoil_pT_hist_corr[DgenpTBin]->Fill(RecpTBin,RPweight);
	  _recoil_psi_hist_corr[DgenpTBin]->Fill(DPsiBin,RPweight);       
	}

	_pT_Psi_R_Count[DgenpTBin][DPsiBin][RecpTBin] += RPweight;
	
      }
    }
    
    if(line%10000==0) cout<<"  Reading Recoil line "<<line<<endl;
    line++;
  }
  
  // get the mean values

  if(final_iter){
    vector<double> corrRpYmeans = recoil_pY_corr->GetMeans();
    vector<double> genRpYmeans = recoil_pY_gen->GetMeans();
    vector<double> smRRpYmeans = recoil_pY_smR->GetMeans();
    
    for(int i=0; i<_num_recoil_pT_bins; i++){
      recoil_pT_bin_meansY[i] = corrRpYmeans.at(i);
      recoil_pT_bin_meansY_gen[i] = genRpYmeans.at(i);
      recoil_pT_bin_meansY_smR[i] = smRRpYmeans.at(i);
    }
 
    for(int i=0; i<_num_RpT_bins; i++){
      for(int j=0; j<_num_recoil_pT_bins; j++){
	double GENSUM=0;
	double CORRSUM=0;
	double SMRSUM=0;
	for(int k=0; k<_num_RpT_bins; k++){
	  GENSUM+=(_recoil_pT_hist_gen[j]->GetBinContent(k+1));
	  SMRSUM+=(_recoil_pT_hist_smR[j]->GetBinContent(k+1));
	  CORRSUM+=(_recoil_pT_hist_corr[j]->GetBinContent(k+1));
	}
	double frac;
	if(GENSUM!=0) frac = (_recoil_pT_hist_gen[j]->GetBinContent(i+1))/GENSUM;
	else frac = 0;
	_recoil_frac_gen[i]->SetBinContent((j+1),frac);
	if(SMRSUM!=0) frac = (_recoil_pT_hist_smR[j]->GetBinContent(i+1))/SMRSUM;
	else frac = 0;
	_recoil_frac_smR[i]->SetBinContent((j+1),frac);
	if(CORRSUM!=0) frac = (_recoil_pT_hist_corr[j]->GetBinContent(i+1))/CORRSUM;
	else frac = 0;
	_recoil_frac_corr[i]->SetBinContent((j+1),frac);
      }
    }
  }
  
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int MakeCorrectedRecoilHists(){

  line=0;
      
  for(int it=0; it<((int)RecDatVec.size()); it++){
    
    vector<double> EvtVec = RecDatVec.at(it);

    Zpx_gen = EvtVec.at(0);
    Zpy_gen = EvtVec.at(1);
    ZpT_gen = EvtVec.at(2);
    Zpx_smear = EvtVec.at(3);
    Zpy_smear = EvtVec.at(4);
    ZpT_smear = EvtVec.at(5);
    Ex_before = EvtVec.at(6);
    Ey_before = EvtVec.at(7);
    RecpT = EvtVec.at(8);
    Ex_rot_gen = EvtVec.at(9);
    Ey_rot_gen = EvtVec.at(10);
    PhiRecRot_gen = EvtVec.at(11);
    Ex_rot_smR = EvtVec.at(12);
    Ey_rot_smR = EvtVec.at(13);
    PhiRecRot_smR = EvtVec.at(14);
    thePsi_gen = EvtVec.at(15);
    thePsiFill_gen = EvtVec.at(16);
    thePsi_smR = EvtVec.at(17);
    thePsiFill_smR = EvtVec.at(18);
    genpTBin = (int) EvtVec.at(19);
    smRpTBin = (int) EvtVec.at(20);
    RecpTBin = (int) EvtVec.at(21);
    PsiBin = (int) EvtVec.at(22);
    PsiBin_true = (int) EvtVec.at(23);
    psipos = EvtVec.at(24);
    theSET = EvtVec.at(25);
    evttype = EvtVec.at(26);
    evtweight = EvtVec.at(27);
    theLumi = EvtVec.at(28); 
    runno = EvtVec.at(29); 
    upar1 = EvtVec.at(30);
    upar2 = EvtVec.at(31);
    epT1 = EvtVec.at(32);
    epT2 = EvtVec.at(33);
    eleta1 = EvtVec.at(34);
    eleta2 = EvtVec.at(35);


    _recoil_pT_histograms_smR[smRpTBin]-> Fill(Ex_rot_smR, Ey_rot_smR-recoil_pT_bin_meansY_smR[smRpTBin], 1.0);
    _recoil_pT_histograms_gen[genpTBin]-> Fill(Ex_rot_gen, Ey_rot_gen-recoil_pT_bin_meansY_gen[genpTBin], 1.0);


    // Determine Efficiency Related Weights
    double Zeffic = CalcSETEfficiency((float)theSET, (float)theLumi, (float)epT1,(float) epT2,(float) eleta1,(float) eleta2);
    double Ueffic = CalcUparaEfficiency(upar1,upar2);

    double SETweight,Uparaweight;
    SETweight=1;
    Uparaweight=1;

    if(doSETcorr){
      if(Zeffic>0) SETweight = 1/Zeffic;
      else SETweight=1;

      if(SETweight>5.) {
        cout << " SETweight " << SETweight << endl;
        SETweight=5.;
      }
    }

    if(doUparcorr){
      if(Ueffic>0) Uparaweight = 1/Ueffic;
      else Uparaweight=1;

      if(Uparaweight>5.) {
        cout << " Uparaweight " << Uparaweight << endl;
        Uparaweight=5.;
      }
    }
    
    double totweight=Uparaweight*SETweight*evtweight;

    // sum the recoil_y in each gen pT bin, and psi pT bin weighted by likelihood
    
    int PhiBin;
    double the_ZpT, the_pT_Phi,the_pT_Psi_R, RPweight, DPsi;

    the_smR_Norm = _smR_Norm[smRpTBin][PsiBin][RecpTBin]; 

    int DRcourseBin = RcourseMap[RecpTBin];

    for(int DgenpTBin=0; DgenpTBin<_num_recoil_pT_bins; DgenpTBin++){

      // determine the equivilent "course" pT bin corresponding to DgenpTBin
      int DcourseBin=courseMap[DgenpTBin];
      
      the_ZpT = _ZpT_Dist[DgenpTBin];
      for(int DPsiBin=0; DPsiBin<_num_psi_bins; DPsiBin++){

	PhiBin=(int)fabs(DPsiBin-PsiBin);
	if(PhiBin>(_num_delta_phi_bins-1)) PhiBin = _num_psi_bins - PhiBin;
	the_pT_Phi = _pT_Phi[DgenpTBin][smRpTBin][PhiBin];
	the_pT_Psi_R = _pT_Psi_R_Dist[DgenpTBin][DPsiBin][RecpTBin];

	if( !((PhiBin==0) || (PhiBin==(_num_delta_phi_bins-1))) ) the_pT_Phi = 0.5*the_pT_Phi;

	if(the_smR_Norm!=0) RPweight = totweight*((the_pT_Phi*the_pT_Psi_R*the_ZpT)/the_smR_Norm);
	else RPweight=0;

	DPsi = DPsiBin*psi_bin_width + psipos;

	// Rotate+++++++++++++++++++++++++++++++++++++++++++++++
  
	Ey_rot = sqrt(Ex_rot_smR*Ex_rot_smR + Ey_rot_smR*Ey_rot_smR)*cos(DPsi);
	Ex_rot = sqrt(Ex_rot_smR*Ex_rot_smR + Ey_rot_smR*Ey_rot_smR)*sin(DPsi);

	_SEThist[DcourseBin][DRcourseBin]->Fill(theSET,RPweight);
	_recoil_pT_histograms[DgenpTBin]-> Fill(Ex_rot, Ey_rot-recoil_pT_bin_meansY[DgenpTBin], RPweight);
	InstLumi_runNo_WZ->Fill(theLumi,(double)runno,RPweight);
        InstLumi_SET_WZ->Fill(theLumi,theSET,RPweight);
      }
    }
    InstLumi_SET_WZ_orig->Fill(theLumi,theSET);
    
    if(line%10000==0) cout<<"  Reading Recoil (Last x) line "<<line<<endl;
    line++;
  }
  
  for(int gnB=0; gnB<_num_recoil_pT_bins; gnB++){
    _recoil_pY_means->SetBinContent(gnB+1,recoil_pT_bin_meansY[gnB]);
  }

  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int WriteRecPsiHistos(int iter){

  cout<<"Writing RecPsI Histos..."<<endl;

  TString Fname;
  Fname+="Diagnostic_Hists_";
  Fname+=output_label;
  Fname+="_";
  Fname+=iter;
  Fname+=".root";

  TFile psihF(Fname,"recreate");

  TH1D **_recoil_frac = new TH1D*[_num_RpT_bins];
  TH1D **_recoil_psi = new TH1D*[_num_recoil_pT_bins];
  TH1D **_rec_spec = new TH1D*[_num_recoil_pT_bins];
  char name[50],title[50];

  for(int j=0; j<_num_RpT_bins; j++) {
    sprintf(name, "%s%d", "recoil_frac_", j);
    sprintf(title, "%s%d", "per pTbin recoil frac for RecpT bin: ", j);
    _recoil_frac[j] = new TH1D(name, title, _num_recoil_pT_bins, -0.5, ((double)_num_recoil_pT_bins-0.5)); 
  }

  for(int j=0; j<_num_recoil_pT_bins; j++) {
    sprintf(name, "%s%d", "recoil_psi_", j);
    sprintf(title, "%s%d", "recoil psi for ZpT bin: ", j);
    _recoil_psi[j] = new TH1D(name, title, _num_psi_bins, -0.5, ((double)_num_psi_bins-0.5));
    sprintf(name, "%s%d", "recoil_pT_", j);
    sprintf(title, "%s%d", "recoil pT for ZpT bin: ", j);
    _rec_spec[j] = new TH1D(name, title, _num_RpT_bins, -0.5, ((double)_num_RpT_bins-0.5));
  }

  double INTEG;

  for(int i=0; i<_num_RpT_bins; i++){
    for(int j=0; j<_num_recoil_pT_bins; j++){
      double RSum=0;
      for(int k=0; k<_num_psi_bins; k++){
	RSum+= _pT_Psi_R_Dist[j][k][i];
      }
      _recoil_frac[i]->SetBinContent((j+1),RSum);
    }
    sprintf(name, "%s%d%s%d", "rec_frac_", i,"_",iter);
    INTEG = _recoil_frac[i]->Integral();
    if(INTEG!=0) _recoil_frac[i]->Scale(1.0/INTEG);
    _recoil_frac[i]->Write(name);
  }

  for(int i=0; i<_num_recoil_pT_bins; i++){

    for(int j=0; j<_num_RpT_bins; j++){
      double RSum=0;
      for(int k=0; k<_num_psi_bins; k++){
 	RSum+= _pT_Psi_R_Dist[i][k][j];
      }
      _rec_spec[i]->SetBinContent((j+1),RSum);
    }
    sprintf(name, "%s%d%s%d", "rec_spec_", i,"_",iter);
    INTEG = _rec_spec[i]->Integral();
    if(INTEG!=0) _rec_spec[i]->Scale(1.0/INTEG);
    _rec_spec[i]->Write(name);

    for(int j=0; j<_num_psi_bins; j++){
      double RSum=0;
      for(int k=0; k<_num_RpT_bins; k++){
 	RSum+= _pT_Psi_R_Dist[i][j][k];
      }
      _recoil_psi[i]->SetBinContent((j+1),RSum);
    }
    sprintf(name, "%s%d%s%d", "rec_psi_", i,"_",iter);
    INTEG = _recoil_psi[i]->Integral();
    if(INTEG!=0) _recoil_psi[i]->Scale(1.0/INTEG);
    _recoil_psi[i]->Write(name);
  }

  psihF.Close();


  TString WFname;
  WFname+="Weight_Matrices_";
  WFname+=output_label;
  WFname+="_";
  WFname+=iter;
  WFname+=".txt";

  fstream Woutfile(WFname,ios::out);

  for(int i=0; i<_num_recoil_pT_bins; i++){
    Woutfile<<"0 "<<i<<" "<<9999<<" "<<9999<<" "<<_ZpT_Dist[i]<<endl;      
    for(int j=0; j<_num_psi_bins; j++){
      for(int k=0; k<_num_RpT_bins; k++){
	Woutfile<<"2 "<<i<<" "<<j<<" "<<k<<" "<<_smR_Norm[i][j][k]<<endl;
	Woutfile<<"3 "<<i<<" "<<j<<" "<<k<<" "<<_pT_Psi_R_Dist[i][j][k]<<endl;
      }
    }
    for(int l=0; l<_num_recoil_pT_bins; l++){
      for(int m=0; m<_num_delta_phi_bins; m++){
	Woutfile<<"1 "<<i<<" "<<l<<" "<<m<<" "<<_pT_Phi[i][l][m]<<endl;      
      }
    }
  }

  Woutfile.close();


  cout<<"Done Writing Histos"<<endl;
  
  return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ReadSavedTransitionMatrices(TString TMFname){

  ifstream TMFile(TMFname, ios::in);
  line=0;
  
  int itype,iit,jit,kit;
  double ivalue;

  while(!TMFile.eof()) {
    TMFile >> itype >> iit >> jit >> kit >> ivalue;

    if( itype == 0 ) _ZpT_Dist[iit] = ivalue;

    if( itype == 1 ) _pT_Phi[iit][jit][kit] = ivalue;

    if( itype == 2 ) _smR_Norm[iit][jit][kit] = ivalue;

    if( itype == 3 ) _pT_Psi_R_Dist[iit][jit][kit] = ivalue;
  }

  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int WriteHistos(){

  TGraphErrors *GRpYmeans_corr = recoil_pY_corr->GGetMeans();
  TGraphErrors *GRpYmeans_gen = recoil_pY_gen->GGetMeans();
  TGraphErrors *GRpYmeans_smR = recoil_pY_smR->GGetMeans();
  TGraphErrors *GRpYRMSs_corr = recoil_pY_corr->GGetRMSs();
  TGraphErrors *GRpYRMSs_gen = recoil_pY_gen->GGetRMSs();
  TGraphErrors *GRpYRMSs_smR = recoil_pY_smR->GGetRMSs();

  TGraphErrors *GRpTmeans_corr = recoil_pT_corr->GGetMeans();
  TGraphErrors *GRpTmeans_gen = recoil_pT_gen->GGetMeans();
  TGraphErrors *GRpTmeans_smR = recoil_pT_smR->GGetMeans();
  TGraphErrors *GRpTRMSs_corr = recoil_pT_corr->GGetRMSs();
  TGraphErrors *GRpTRMSs_gen = recoil_pT_gen->GGetRMSs();
  TGraphErrors *GRpTRMSs_smR = recoil_pT_smR->GGetRMSs();

  TGraphErrors *GRphimeans_corr = TOT_phi_corr->GGetMeans();
  TGraphErrors *GRphimeans_gen = TOT_phi_gen->GGetMeans();
  TGraphErrors *GRphimeans_smR = TOT_phi_smR->GGetMeans();
  TGraphErrors *GRphiRMSs_corr = TOT_phi_corr->GGetRMSs();
  TGraphErrors *GRphiRMSs_gen = TOT_phi_gen->GGetRMSs();
  TGraphErrors *GRphiRMSs_smR = TOT_phi_smR->GGetRMSs();

  TString SDname;
  SDname+="Summary_Dists_";
  SDname+=output_label;
  SDname+=".root";

  TFile tb(SDname,"recreate");

  for(int j=0; j<_num_RpT_bins; j++) {
    double NORM = _recoil_frac_gen[j]->Integral();
    _recoil_frac_gen[j]->Scale(1.0/NORM);
    NORM = _recoil_frac_smR[j]->Integral();
    _recoil_frac_smR[j]->Scale(1.0/NORM);
    NORM = _recoil_frac_corr[j]->Integral();
    _recoil_frac_corr[j]->Scale(1.0/NORM);

    _recoil_frac_gen[j]->Write();
    _recoil_frac_smR[j]->Write();
    _recoil_frac_corr[j]->Write();
  }


  for(int j=0; j<_num_recoil_pT_bins; j++) {
    
    double NORM = _recoil_psi_hist_gen[j]->Integral();
    _recoil_psi_hist_gen[j]->Scale(1.0/NORM);
    NORM = _recoil_psi_hist_smR[j]->Integral();
    _recoil_psi_hist_smR[j]->Scale(1.0/NORM);
    NORM = _recoil_psi_hist_corr[j]->Integral();
    _recoil_psi_hist_corr[j]->Scale(1.0/NORM);

    NORM = _recoil_pX_hist_gen[j]->Integral();
    _recoil_pX_hist_gen[j]->Scale(1.0/NORM);
    NORM = _recoil_pX_hist_smR[j]->Integral();
    _recoil_pX_hist_smR[j]->Scale(1.0/NORM);
    NORM = _recoil_pX_hist_corr[j]->Integral();
    _recoil_pX_hist_corr[j]->Scale(1.0/NORM);

    NORM = _recoil_pY_hist_gen[j]->Integral();
    _recoil_pY_hist_gen[j]->Scale(1.0/NORM);
    NORM = _recoil_pY_hist_smR[j]->Integral();
    _recoil_pY_hist_smR[j]->Scale(1.0/NORM);
    NORM = _recoil_pY_hist_corr[j]->Integral();
    _recoil_pY_hist_corr[j]->Scale(1.0/NORM);

    NORM = _recoil_pT_hist_gen[j]->Integral();
    _recoil_pT_hist_gen[j]->Scale(1.0/NORM);
    NORM = _recoil_pT_hist_smR[j]->Integral();
    _recoil_pT_hist_smR[j]->Scale(1.0/NORM);
    NORM = _recoil_pT_hist_corr[j]->Integral();
    _recoil_pT_hist_corr[j]->Scale(1.0/NORM);

    _recoil_psi_hist_gen[j]->Write(); 
    _recoil_psi_hist_smR[j]->Write();
    _recoil_psi_hist_corr[j]->Write();

    _recoil_pX_hist_gen[j]->Write(); 
    _recoil_pX_hist_smR[j]->Write();
    _recoil_pX_hist_corr[j]->Write();

    _recoil_pY_hist_gen[j]->Write(); 
    _recoil_pY_hist_smR[j]->Write();
    _recoil_pY_hist_corr[j]->Write();

    _recoil_pT_hist_gen[j]->Write(); 
    _recoil_pT_hist_smR[j]->Write();
    _recoil_pT_hist_corr[j]->Write();
  }


  _Zspect->Write();
  _Zspect_smR->Write();

  tb.Close();
    
  TString PGname;
  PGname+="Profile_Graphs_";
  PGname+=output_label;
  PGname+=".root";

  TFile tc(PGname,"recreate");

  GRpYmeans_corr->Write("GRpYmeans_corr");
  GRpYmeans_gen->Write("GRpYmeans_gen");
  GRpYmeans_smR->Write("GRpYmeans_smR"); 
  GRpYRMSs_corr->Write("GRpYRMSs_corr");
  GRpYRMSs_gen->Write("GRpYRMSs_gen");
  GRpYRMSs_smR->Write("GRpYRMSs_smR");

  GRpTmeans_corr->Write("GRpTmeans_corr");
  GRpTmeans_gen->Write("GRpTmeans_gen");
  GRpTmeans_smR->Write("GRpTmeans_smR"); 
  GRpTRMSs_corr->Write("GRpTRMSs_corr");
  GRpTRMSs_gen->Write("GRpTRMSs_gen");
  GRpTRMSs_smR->Write("GRpTRMSs_smR");

  GRphimeans_corr->Write("GRphimeans_corr");
  GRphimeans_gen->Write("GRphimeans_gen");
  GRphimeans_smR->Write("GRphimeans_smR"); 
  GRphiRMSs_corr->Write("GRphiRMSs_corr");
  GRphiRMSs_gen->Write("GRphiRMSs_gen");
  GRphiRMSs_smR->Write("GRphiRMSs_smR");

  tc.Close();

  if(make_corrected_file){  

    TString CorrFname;
    CorrFname+="Zrecoil_";
    CorrFname+=output_label;
    CorrFname+=".CORR.root";

    TFile tf(CorrFname,"recreate");

    for(int i=0; i<_num_recoil_pT_bins; i++){

      TString rechistname;
      rechistname+="rechist_";
      rechistname+=i;
      _recoil_pT_histograms[i]->Write(rechistname);
      TString rechistnameS;
      rechistnameS+="rechist_smR_";
      rechistnameS+=i;
      _recoil_pT_histograms_smR[i]->Write();
      TString rechistnameG;
      rechistnameG+="rechist_gen_";
      rechistnameG+=i;
      //      _recoil_pT_histograms_gen[i]->Write();
    }

    InstLumi_runNo_WZ->Write("InstLumi_runNo_WZ");
    InstLumi_SET_WZ->Write("InstLumi_SET_WZ");
    InstLumi_SET_WZ_orig->Write("InstLumi_SET_WZ_orig");

    _recoil_pY_means->Write();

    
    _theSETweights->Write();
    _theUPweights->Write();
    _theunfoldweights->Write();

    for(int j=0; j<_num_course_pT_bins; j++){
      for(int i=0; i<_num_course_pT_bins; i++){
	_SEThist[i][j]->Write();
      }
    }
    

    tf.Close();  
  }

  return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////















/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main( int argc, char *argv[] )
{
 
  iszrecoil=true;
  make_corrected_file=true;  
  
  if( argc < 7) {
    std::cout<<" Usage : ./ConvertRecoils2D <recoil-filenames> <map-filename> <output-label> <SET_option> <Upar_option> <num_iterations> <num_recoil_evts_to_unfold>" << std::endl;
    std::cout<<" Use <SET_option>=0   to make a recoil file withOUT correcting for the SET efficiency,"<<endl
	     <<"     <SET_option>=1   to make a recoil file WITH the SET efficiency correction"<<endl
	     <<"     <Upar_option>=0  to make a recoil file withOUT correcting for the Upara efficiency,"<<endl 
	     <<"     <Upar_option>=1  to make a recoil file WITH the Upara efficiency correction," << endl;
    return 1;
  }
  
  std::string in_filename = std::string( argv[argc-7] );
  data_recoilname = in_filename;
  cout<<"Recoil Text File to Unfold: "<<data_recoilname<<endl;

  std::string map_filename = std::string( argv[argc-6] );
  pmcs_mapname = map_filename;
  cout<<"MAP file: "<<pmcs_mapname<<endl;

  std::string out_filename = std::string( argv[argc-5] );
  output_label = out_filename;
  cout<<"Output Label: "<<output_label<<endl;
  
  int SET_option = atoi(argv[argc-4]);
  if(SET_option==1) doSETcorr=true;
  else if(SET_option==0) doSETcorr=false;
  else { 
    cout<<"doSETcorr must be 1 or 0!"<<endl;
    return 1;
  }
  cout<<"SEToption: "<<doSETcorr<<endl;

  int Upar_option = atoi(argv[argc-3]);
  if(Upar_option==1) doUparcorr=true;
  else if(Upar_option==0) doUparcorr=false;
  else { 
    cout<<"doUparcorr must be 1 or 0!"<<endl;
    return 1;
  }
  cout<<"Uparoption: "<<doUparcorr<<endl;

  num_iters = atoi(argv[argc-2]);
  cout<<"number of iterations: " <<num_iters<<endl;

  num_rec_evts_touse = atoi(argv[argc-1]);
  cout<<"number of events to unfold: " <<num_rec_evts_touse<<endl;

  // initialize variables and data structures

  cout<<"Initializing Variables and Data Structures..."<<endl;

  InitializeIt(); 

  // loop over Map-File, determine reweighting elements

  cout<<"Making Map Matrices..."<<endl;

  MakeMapMatrices();

  // Determine Initial Psi Matrix

  cout<<"Determining Initial Psi and Rec Matrix..."<<endl;
  CalculateRecPsiMatrix();

  // Load in Data From Recoil File To a Global Vector

  cout<<"Loading Recoil File..."<<endl;
  LoadRecoilFile();

  // Iterate And Recalculte Psi Matrix

  cout<<"Iterating And Recalculating Psi and Rec Matrix..."<<endl;

  for(int i=0; i<10; i++){
    cout<<"Iteration: "<<i<<endl;
    DetermineRecoilMeans(false);
    CalculateRecPsiMatrix();
    WriteRecPsiHistos(i);
  }

  // calculate final recoil means

  cout<<"Determining Final Recoil Means..."<<endl;

  DetermineRecoilMeans(true);

  // Make Corrected Recoil Histograms
  
  if(make_corrected_file){
    cout<<"Making Corrected Recoil Hists..."<<endl;
    MakeCorrectedRecoilHists();
  }

  // Write Histograms to New Recoil File

  cout<<"Writing Final Histograms..."<<endl;
  WriteHistos();
  
  return 0;
}

