#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
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
//#include "SETefficiencySmear.hpp"
//#include "PParameterReader.hpp"
#include "../../src/SETefficiencySmear.hpp"
#include "../../src/PParameterReader.hpp"



using namespace std;


// Binning Variables /////////////////////////////////////////////////////////////////////////
int _num_recoil_pT_bins;
int _num_RpT_bins;
int _num_delta_phi_bins;
int _num_psi_bins;
int _num_course_pT_bins;
int _num_Lumi_bins;
int size_edges;
int size_Redges;
int size_dPedges;
int size_dPsiedges;
int size_courseedges;
int size_Lumiedges;

double psi_bin_width;
double psi_halfbin_width;
vector<double> _recoil_pT_bin_edges;
vector<double> _course_pT_bin_edges;
vector<double> _Lumi_bin_edges;
vector<double> _RpT_bin_edges;
vector<double> _delta_phi_bin_edges;
vector<double> _psi_bin_edges;
vector<double> bincenters;

int *binevtcount;
int totevtcount;
int **SETbinevtcount;
/////////////////////////////////////////////////////////////////////////////////////////



// Profile Instances /////////////////////////////////////////////////////////////////////
perBinProfile* recoil_pT_corr;
perBinProfile* recoil_pT_gen;
perBinProfile* recoil_pT_smR;
perBinProfile* recoil_pX_corr;
perBinProfile* recoil_pX_gen;
perBinProfile* recoil_pX_smR;
perBinProfile* recoil_pY_corr;
perBinProfile* recoil_pY_gen;
perBinProfile* recoil_pY_smR;
perBinProfile* TOT_phi_corr;
perBinProfile* TOT_phi_gen;
perBinProfile* TOT_phi_smR;
////////////////////////////////////////////////////////////////////////////////////////


// Efficiency Instances ////////////////////////////////////////////////////////////////
SETefficiencySmear *_SETeffic; 


// SET histograms //////////////////////////////////////////////////////////////////////
TH1D ***_SEThist;


// Diagnostic Histograms ///////////////////////////////////////////////////////////////
TH2D **_recoil_pT_histograms_gen;
TH1D **_recoil_pT_1Dhistograms_gen;
TH1D *_recoil_pY_means;
TH1D *_recoil_pT;
TH2D *InstLumi_runNo_WZ;
TH1D* _SETdist_orig;
TH1D* _SETdist;

TH1D* _UPdist;
TH1D* _epTdist;
TH1D* _leadepTdist;
TH1D* _subleadepTdist;
TH1D* _RunNodist;
TH1D* _Lumidist;
TH1D* _theSETweights;
TH1D* _theUPweights;
////////////////////////////////////////////////////////////////////////////////////////


// Mean recoil projected along boson direction /////////////////////////////////////////
double *recoil_pT_bin_meansY;
double *recoil_pT_bin_meansY_gen;
double *recoil_pT_bin_meansY_smR; 
///////////////////////////////////////////////////////////////////////////////////////


// Switches and file names ////////////////////////////////////////////////////////////
bool doSETcorr,doUparcorr,iszrecoil;
TString pmcs_mapname;
TString output_label;
TString data_recoilname;
TString recoiloutfile,recoiloutfile2;
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


// Variables to read in //////////////////////////////////////////////////////////////
double Zpx_gen,Zpy_gen,Zpx_smear,Zpy_smear,Ex_before,Ey_before,evttype,evtweight,Ex_rot,Ey_rot,Ex_rot_gen,Ey_rot_gen,theSET,upar1,upar2,theLumi, runno,epT1, epT2,eleta1,eleta2;
int line;  
//////////////////////////////////////////////////////////////////////////////////////







/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int InitializeIt(){


  // Defining my pT binning scheme


  _num_recoil_pT_bins = 156;
  _num_RpT_bins = 54;
  _num_delta_phi_bins = 33;
  _num_psi_bins = 64;
  _num_course_pT_bins = 34;
  _num_Lumi_bins = 12;

  double pT_bin_array[155] = {0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0, 5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25, 8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25, 11.5, 11.75, 12.0, 12.33, 12.66, 13.0, 13.33, 13.66, 14.0, 14.5, 15.0, 15.5, 16.0, 16.5, 17.0, 17.5, 18.0, 18.5, 19.0, 19.5, 20.0, 20.5, 21.0, 21.5, 22.0, 22.5, 23.0, 23.5, 24.0, 24.5, 25.0,25.5, 26.0, 26.5, 27.0, 27.5, 28.0, 28.5, 29.0, 29.5, 30.0, 30.5, 31.0, 31.5, 32.0, 32.5, 33.0, 33.5, 34.0, 34.5, 35.0,35.5, 36.0, 36.5, 37.0, 37.5, 38.0, 38.5, 39.0, 39.5, 40.0, 40.5, 41.0, 41.5, 42.0, 42.5, 43.0, 43.5, 44.0, 44.5, 45.0, 45.5, 46.0, 46.5, 47.0, 47.5, 48.0, 48.5, 49.0, 49.5, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0, 57.0, 58.0, 59.0, 60.0, 62.0, 64.0, 66.0, 68.0, 70.0, 72.0, 74.0, 76.0, 78.0, 80.0, 84.0, 88.0, 92.0, 96.0, 100.0, 105.0, 110.0, 120.0, 160.0};

  double course_pT_bin_array[33] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 34.0, 38.0, 42.0, 46.0, 50.0, 55.0, 60.0, 70.0};

  double Lumi_bin_array[11] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

  double RpT_bin_array[53] = {0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0, 34.0, 36.0, 38.0, 40.0, 44.0, 48.0, 52.0, 60.0, 62.0, 64.0, 66.0, 68.0, 70.0};

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
    cout<<pT_bin_array[i]<<", ";
  }
  for(int i=0; i<(_num_course_pT_bins-1); i++){
    _course_pT_bin_edges.push_back(course_pT_bin_array[i]);
    cout<<course_pT_bin_array[i]<<", ";
  }
  for(int i=0; i<(_num_Lumi_bins-1); i++){
    _Lumi_bin_edges.push_back(Lumi_bin_array[i]);
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
  size_Lumiedges = _Lumi_bin_edges.size();
  size_Redges = _RpT_bin_edges.size();
  size_dPedges = _delta_phi_bin_edges.size();
  size_dPsiedges = _psi_bin_edges.size(); 


  if(_num_recoil_pT_bins!=(size_edges+1)) {
    cout <<"_num_recoil_pT_bins should equal to _recoil_pT_bin_edges.size()+1"<<endl;
  }

  if(_num_RpT_bins!=(size_Redges+1)) {
    cout <<"_num_RpT_bins should equal to _RpT_bin_edges.size()+1"<<endl;
  }

  if(_num_delta_phi_bins!=(size_dPedges+1)) {
    cout <<"_num_delta_phi_bins should equal to _delta_phi_bin_edges.size()+1"<<endl;
  }


  if(_num_course_pT_bins!=(size_courseedges+1)) {
    cout <<"_num_course_pT__bins should equal to _course_pT_bin_edges.size()+1"<<endl;
  }

  if(_num_Lumi_bins!=(size_Lumiedges+1)) {
    cout <<"_num_Lumi_bins should equal to _Lumi_bin_edges.size()+1"<<endl;
  }

  if(_num_psi_bins!=(size_dPsiedges)) {
    cout <<"_num_delta_phi_bins should equal to _delta_phi_bin_edges.size()+1"<<endl;
  }

  binevtcount = new int[_num_recoil_pT_bins];
  for(int i=0; i<_num_recoil_pT_bins; i++){
    binevtcount[i]=0;
  }
  
  SETbinevtcount = new int*[_num_course_pT_bins];
  for(int i=0; i<_num_course_pT_bins; i++){
    SETbinevtcount[i] = new int[_num_course_pT_bins];
    for(int j=0; j<_num_course_pT_bins; j++){
      SETbinevtcount[i][j]=0;
    }
  }

  totevtcount=0;

  // determine the bin centers for my pT binning scheme


  bincenters.push_back(0.125);
  for(int i=0; i<154; i++)
    {
      bincenters.push_back( (((pT_bin_array[i+1]-pT_bin_array[i])/2)+pT_bin_array[i]) );
    }
  bincenters.push_back(200.);

  // initialize the "profile" instances

  recoil_pT_corr = new perBinProfile(_num_recoil_pT_bins,bincenters);
  recoil_pT_gen = new perBinProfile(_num_recoil_pT_bins,bincenters);
  recoil_pT_smR = new perBinProfile(_num_recoil_pT_bins,bincenters);
  
  recoil_pY_corr = new perBinProfile(_num_recoil_pT_bins,bincenters);
  recoil_pY_gen = new perBinProfile(_num_recoil_pT_bins,bincenters);
  recoil_pY_smR = new perBinProfile(_num_recoil_pT_bins,bincenters);

  recoil_pX_corr = new perBinProfile(_num_recoil_pT_bins,bincenters);
  recoil_pX_gen = new perBinProfile(_num_recoil_pT_bins,bincenters);
  recoil_pX_smR = new perBinProfile(_num_recoil_pT_bins,bincenters);
  
  TOT_phi_corr = new perBinProfile(_num_recoil_pT_bins,bincenters);
  TOT_phi_gen = new perBinProfile(_num_recoil_pT_bins,bincenters);
  TOT_phi_smR = new perBinProfile(_num_recoil_pT_bins,bincenters);

  recoil_pT_bin_meansY = new double[_num_recoil_pT_bins];
  recoil_pT_bin_meansY_gen = new double[_num_recoil_pT_bins];
  recoil_pT_bin_meansY_smR = new double[_num_recoil_pT_bins]; 


  // initialize efficiency classes and parameters

  PParameterReader parm("parameters.rc"); 

  _ZSETEffCorrScaled = parm.GetBool("ZSETEffCorrScaled", kFALSE);
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

  _SETeffic=0;
  if (doSETcorr) {
    if (_ZSETEffCorrPTEpert) {
      _SETeffic = new SETefficiencySmear(_ZSETEffCorrParametersCCCC,_ZSETEffCorrParametersCCEC,_ZSETEffCorrParametersECEC,
                          _ZSETEffCorrScaled,20,true,
                          true,
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

  char name[50], title[50];
  char name2[50], title2[50];


  _UPdist= new TH1D("UPd","UPd",200,-100.,100.);
  _epTdist= new TH1D("epTd","epTd",300,0.,150.);
  _leadepTdist= new TH1D("leadepTd","leadepTd",300,0.,150.);
  _subleadepTdist= new TH1D("sibleadepTd","subleadepTd",300,0.,150.);
  _RunNodist = new TH1D("runodist","runnodist",500,160581.5,299999);
  _Lumidist = new TH1D("lumidist","lumidist",150,0.,15.0);
  InstLumi_runNo_WZ = new TH2D("InstLumi_runNo_WZ","InstLumi_runNo_WZ",150,0.,15.0,30890,222027.5,252918.5);
  //  InstLumi_runNo_WZ = new TH2D("InstLumi_runNo_WZ","InstLumi_runNo_WZ",100,0.,4.,500,21016699.5,21017200.5);
  _recoil_pT = new TH1D("recoilpT","recoilpT",1000,0.,100.);
  _SETdist_orig = new TH1D("SETd_orig","SETd_orig",300,0.,300.);
  _SETdist = new TH1D("SETd","SETd",300,0.,300.);
  _recoil_pY_means = new TH1D("Mean_recoil_y","Mean_recoil_y",_num_recoil_pT_bins,-0.5,((double)_num_recoil_pT_bins-0.5));
  _recoil_pT_histograms_gen = new TH2D*[_num_recoil_pT_bins];
  _recoil_pT_1Dhistograms_gen = new TH1D*[_num_recoil_pT_bins];  

  _theSETweights = new TH1D("theSETweights","theSETweights",8000,0,1000);
  _theUPweights = new TH1D("theUPweights","theUPweights",8000,0,1000);


  for(int i=0; i<_num_recoil_pT_bins; i++) {
    sprintf(name, "%s%d", "recoil_pT_", i);
    sprintf(title, "%s%d", "recoil x and y components for pT bin: ", i);
    _recoil_pT_histograms_gen[i] = new TH2D(name, title, 440, -22, 22, 600, -30, 30);

    sprintf(name2, "%s%d", "recoil_pT1D_", i);
    sprintf(title2, "%s%d", "recoil pT for Z pT bin: ", i);
    _recoil_pT_1Dhistograms_gen[i] = new TH1D(name2,title2, 500,0.,100.);
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
      
      _SEThist[i][j] = new TH1D(SEThistname,SEThistname,300,0.,300.);
      
    }
    
  }



  return 0;
}//////////////////////////////////////////////////////////////////////////////////////////////////////////////















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















////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
double CalcSETEfficiency(float scalarEt_All, float lumi, float epT1, float epT2, float eta1, float eta2)
{
  float eff=1;
  
  if (_ZSETEffCorrPTEpert) {
    eff=_SETeffic->getSETeff(scalarEt_All, lumi , epT1, epT2, false, false, eta1, eta2);
    //    if(eff<0) cout<<"inCalcSETEff "<<eff<<" "<<scalarEt_All<<" "<<epT1<<" "<<epT2<<endl;
  } else {
    eff=_SETeffic->getSETeff(scalarEt_All, lumi);
  }
  return eff;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DetermineRecoilMeans(bool final_iter){


  // Reset Opening Angle Histos

  // Loop over recoil file...determine mean recoil_y...per gen bin
  
  ifstream RecoilFile_DATA(data_recoilname, ios::in);
  line=0;

  if(doSETcorr) cout<<"Doing SET correction"<<endl;

  while(!RecoilFile_DATA.eof()) {
    RecoilFile_DATA >> Zpx_gen >> Zpy_gen >> Zpx_smear >> Zpy_smear >> Ex_before >> Ey_before >> theSET >> upar1 >> upar2 >> epT1 >> epT2 >> eleta1 >> eleta2 >> runno >> theLumi >> evttype >> evtweight;    

    if(line%100000==0) cout<<"  Reading Recoil line "<<line<<endl;

    //    if(line>17000) break;

    double zpTgen = sqrt(Zpy_gen*Zpy_gen +Zpx_gen*Zpx_gen);
    
    TVector2 E_vec(Ex_before, Ey_before);
    
    TVector2 Z_vec_gen(Zpx_gen, Zpy_gen);
    TVector2 perp_direction_gen = Z_vec_gen.Rotate(TMath::Pi()/2);
    
    double Ey_rot_gen = E_vec * Z_vec_gen.Unit();
    double Ex_rot_gen = E_vec * perp_direction_gen.Unit();
    
    double PhiRecRot_gen = atan2(Ex_rot_gen, -Ey_rot_gen);

     // determine which gen pT bin to use

    int genBin = -1;
    if(zpTgen<=_recoil_pT_bin_edges[0]) genBin = 0;
    else if(zpTgen>_recoil_pT_bin_edges[size_edges-1]) genBin = size_edges;
    else {
      for(int ii=0; ii<size_edges-1; ii++){
	if((zpTgen>_recoil_pT_bin_edges[ii]) && (zpTgen<=_recoil_pT_bin_edges[ii+1])) genBin = ii+1;
      }
    }


    double RecpT = sqrt(Ey_rot_gen*Ey_rot_gen + Ex_rot_gen*Ex_rot_gen);
    
    // determine which recoil pT bin to use
    int RecpTBin = -1;
    if(RecpT<=_RpT_bin_edges[0]) RecpTBin = 0;
    else if(RecpT>_RpT_bin_edges[size_Redges-1]) RecpTBin = size_Redges;
    else {
      for(int ii=0; ii<size_Redges-1; ii++){
	if((RecpT>_RpT_bin_edges[ii]) && (RecpT<=_RpT_bin_edges[ii+1])) RecpTBin = ii+1;
      }
    }

    double Zeffic=1.; 
    double Ueffic=1.; 

    //    cout<<"about to calc efficiencies"<<endl;

    if(doSETcorr) Zeffic = CalcSETEfficiency((float)theSET, (float)theLumi, (float)epT1, (float)epT2,(float) eleta1,(float) eleta2);
    if(doUparcorr) Ueffic = CalcUparaEfficiency(upar1,upar2);


    //    cout<<"done with efficiencies"<<endl;

    double SETweight,Uparaweight;
    SETweight=1;
    Uparaweight=1;

    if(doSETcorr){
      if(Zeffic>0) SETweight = 1/Zeffic;
      else SETweight=1;

      _theSETweights->Fill(SETweight);

      if(SETweight>5.) SETweight=5.;
    }

    if(doUparcorr){
      if(Ueffic>0) Uparaweight = 1/Ueffic;
      else Uparaweight=1;

      _theUPweights->Fill(Uparaweight);

      if(Uparaweight>5.) Uparaweight=5.;
    }


    double totweight=Uparaweight*SETweight*evtweight;

 
    _recoil_pT->Fill(sqrt(Ey_rot_gen*Ey_rot_gen + Ex_rot_gen*Ex_rot_gen),totweight);
    _SETdist_orig->Fill(theSET);
    _SETdist->Fill(theSET,totweight);
    InstLumi_runNo_WZ->Fill(theLumi,(double)runno,totweight);
    //    cout<<theLumi<<" "<<runno<<" "<<totweight<<endl;
    _RunNodist->Fill(runno);
    _Lumidist->Fill(theLumi);
    _UPdist->Fill(upar1,totweight);
    _UPdist->Fill(upar2,totweight);
    _epTdist->Fill(epT1,totweight);
    _epTdist->Fill(epT2,totweight);
    if(epT1>epT2){
      _leadepTdist->Fill(epT1,totweight);
      _subleadepTdist->Fill(epT2,totweight);
    } else{
      _leadepTdist->Fill(epT2,totweight);
      _subleadepTdist->Fill(epT1,totweight);
    }
        
    recoil_pT_gen->FillQuant(genBin,sqrt(Ey_rot_gen*Ey_rot_gen + Ex_rot_gen*Ex_rot_gen),totweight); 
    recoil_pY_gen->FillQuant(genBin,Ey_rot_gen,totweight); 
    recoil_pX_gen->FillQuant(genBin,Ex_rot_gen,totweight); 
    TOT_phi_gen->FillQuant(genBin,PhiRecRot_gen,totweight);

    line++;
  }

  vector<double> genRpXmeans = recoil_pX_gen->GetMeans();
  vector<double> genRpYmeans = recoil_pY_gen->GetMeans();
  vector<double> genRpTmeans = recoil_pT_gen->GetMeans();
  
  for(int i=0; i<_num_recoil_pT_bins; i++){
    recoil_pT_bin_meansY_gen[i] = genRpYmeans.at(i);
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int MakeCorrectedRecoilHists(){

  ifstream recoilFile2(data_recoilname, ios::in);
  line=0;
  
  while(!recoilFile2.eof()) {
    recoilFile2 >> Zpx_gen >> Zpy_gen >> Zpx_smear >> Zpy_smear >> Ex_before >> Ey_before >> theSET >> upar1 >> upar2 >> epT1 >> epT2 >> eleta1 >> eleta2 >> runno >> theLumi >> evttype >> evtweight;
    if(recoilFile2.eof()) break;

    if(line%100000==0) cout<<"  Reading Recoil line "<<line<<endl;
    
    //    if(line>17000) break;

    double zpTgen = sqrt(Zpy_gen*Zpy_gen +Zpx_gen*Zpx_gen);
    
    TVector2 E_vec(Ex_before, Ey_before);
    
    TVector2 Z_vec_gen(Zpx_gen, Zpy_gen);
    TVector2 perp_direction_gen = Z_vec_gen.Rotate(TMath::Pi()/2);
    
    double Ey_rot_gen = E_vec * Z_vec_gen.Unit();
    double Ex_rot_gen = E_vec * perp_direction_gen.Unit();
    
    double RecpT = sqrt(Ey_rot_gen*Ey_rot_gen + Ex_rot_gen*Ex_rot_gen);

    //    double PhiRecRot_smR = atan2(Ex_rot_smR, -Ey_rot_smR);`
    double PhiRecRot_gen = atan2(Ex_rot_gen, -Ey_rot_gen);

    // determine which gen pT bin to use
    int genBin = -1;
    if(zpTgen<=_recoil_pT_bin_edges[0]) genBin = 0;
    else if(zpTgen>_recoil_pT_bin_edges[size_edges-1]) genBin = size_edges;
    else {
      for(int ii=0; ii<size_edges-1; ii++){
	if((zpTgen>_recoil_pT_bin_edges[ii]) && (zpTgen<=_recoil_pT_bin_edges[ii+1])) genBin = ii+1;
      }
    }

    // determine course ZpT bin number
    int courseBin = -1;
    if(zpTgen<_course_pT_bin_edges[0]) courseBin = 0;
    else if(zpTgen>_course_pT_bin_edges[size_courseedges-1]) courseBin = size_courseedges;
    else {
      for(int ii=0; ii<size_courseedges-1; ii++){
	if((zpTgen>_course_pT_bin_edges[ii]) && (zpTgen<=_course_pT_bin_edges[ii+1])) courseBin = ii+1;
      }
    }
    
    // determine course recoil pT bin number
    int courseBinR = -1;
    if(RecpT<_course_pT_bin_edges[0]) courseBinR = 0;
    else if(RecpT>_course_pT_bin_edges[size_courseedges-1]) courseBinR = size_courseedges;
    else {
      for(int ii=0; ii<size_courseedges-1; ii++){
	if((RecpT>_course_pT_bin_edges[ii]) && (RecpT<=_course_pT_bin_edges[ii+1])) courseBinR = ii+1;
      }
    }
    
    
    // determine lumi bin number
    int LumiBin = -1;
    if(theLumi<=_Lumi_bin_edges[0]) LumiBin = 0;
    else if(theLumi>_Lumi_bin_edges[size_Lumiedges-1]) LumiBin = size_Lumiedges;
    else {
      for(int ii=0; ii<size_Lumiedges-1; ii++){
	if((theLumi>_Lumi_bin_edges[ii]) && (theLumi<=_Lumi_bin_edges[ii+1])) LumiBin = ii+1;
      }
    }
    
    double thePsi_gen = 3.141519 - PhiRecRot_gen;
    
    // determine which smeared Psi bin to use
    
    int PsiBin = -1;
    if(thePsi_gen<=_psi_bin_edges[0]) PsiBin = 0;
    else if(thePsi_gen>_psi_bin_edges[size_dPsiedges-1]) PsiBin = 0;
    else {
      for(int ii=0; ii<size_dPsiedges-1; ii++){
	if((thePsi_gen>_psi_bin_edges[ii]) && (thePsi_gen<=_psi_bin_edges[ii+1])) PsiBin = ii+1;
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


    double Zeffic=1.; 
    double Ueffic=1.; 

    //    cout<<"about to calc efficiencies"<<endl;

    if(doSETcorr) Zeffic = CalcSETEfficiency((float)theSET, (float)theLumi , (float)epT1, (float)epT2,(float) eleta1,(float) eleta2);
    if(doUparcorr) Ueffic = CalcUparaEfficiency(upar1,upar2);

    //    cout<<"done with efficiencies"<<endl;

    double SETweight,Uparaweight;
    SETweight=1;
    Uparaweight=1;

    if(doSETcorr){
      if(Zeffic>0) SETweight = 1/Zeffic;
      else SETweight=1;

      if(SETweight>5.) SETweight=5.;
    }

    if(doUparcorr){
      if(Ueffic>0) Uparaweight = 1/Ueffic;
      else Uparaweight=1;

      if(Uparaweight>5.) Uparaweight=5.;
    }
    
    double totweight = Uparaweight*SETweight*evtweight;

    //    cout<<courseBin<<" "<<theLumi<<" "<<LumiBin<<endl;

    _SEThist[courseBin][courseBinR]->Fill(theSET,totweight);
    _recoil_pT_histograms_gen[genBin]->Fill(Ex_rot_gen, Ey_rot_gen-recoil_pT_bin_meansY_gen[genBin],totweight);
    _recoil_pT_1Dhistograms_gen[genBin]->Fill( sqrt(Ex_rot_gen*Ex_rot_gen + Ey_rot_gen*Ey_rot_gen),totweight);
    SETbinevtcount[courseBin][courseBinR]++;
    binevtcount[genBin]++;
    totevtcount++;
    line++;
  }

  for(int gnB=0; gnB<_num_recoil_pT_bins; gnB++){
    _recoil_pY_means->SetBinContent(gnB+1,recoil_pT_bin_meansY_gen[gnB]);
  }
  
  return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int WriteHistos(){

  TFile tf(recoiloutfile,"recreate");

  for(int genpTBin=0; genpTBin<_num_recoil_pT_bins; genpTBin++){

    TString rechistname;
    rechistname+="rechist_";
    rechistname+=genpTBin;

    _recoil_pT_histograms_gen[genpTBin]->Write(rechistname);
  }

  for(int j=0; j<_num_course_pT_bins; j++){
    for(int i=0; i<_num_course_pT_bins; i++){

      _SEThist[i][j]->Write();

    }
  }

  _recoil_pY_means->Write();
  _recoil_pT->Write();
  _SETdist_orig->Write();
  _SETdist->Write();
  InstLumi_runNo_WZ->Write("InstLumi_runNo_WZ");
  _RunNodist->Write();
  _Lumidist->Write();
  
  _UPdist->Write();
  _epTdist->Write();
  _leadepTdist->Write();
  _subleadepTdist->Write();  
  
  _theSETweights->Write();
  _theUPweights->Write();

  TGraphErrors *GRpYmeans_gen = recoil_pY_gen->GGetMeans();
  TGraphErrors *GRpYRMSs_gen = recoil_pY_gen->GGetRMSs();

  TGraphErrors *GRpTmeans_gen = recoil_pT_gen->GGetMeans();
  TGraphErrors *GRpTRMSs_gen = recoil_pT_gen->GGetRMSs();

  TGraphErrors *GRpXmeans_gen = recoil_pX_gen->GGetMeans();
  TGraphErrors *GRpXRMSs_gen = recoil_pX_gen->GGetRMSs();

  GRpYmeans_gen->Write("GRpYmeans_gen");
  GRpYRMSs_gen->Write("GRpYRMSs_gen");

  GRpTmeans_gen->Write("GRpTmeans_gen");
  GRpTRMSs_gen->Write("GRpTRMSs_gen");

  GRpXmeans_gen->Write("GRpXmeans_gen");
  GRpXRMSs_gen->Write("GRpXRMSs_gen");

  tf.Close();


  TFile tf2(recoiloutfile2,"recreate");

  for(int genpTBin=0; genpTBin<_num_recoil_pT_bins; genpTBin++){

    TString rechistname;
    rechistname+="rec1Dhist_";
    rechistname+=genpTBin;

    _recoil_pT_1Dhistograms_gen[genpTBin]->Write(rechistname);

  }


  tf2.Close();


  return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////















/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main( int argc, char *argv[] )
{


  if( argc < 4) {
    std::cout<<" Usage : ./MakeGenRec <recoil-filenames> <output-label> <SET_option> <Upar_option>" << std::endl;
    std::cout<<" Use <SET_option>=0   to make a recoil file withOUT correcting for the SET efficiency,"<<endl
	     <<"     <SET_option>=1   to make a recoil file WITH the SET efficiency correction"<<endl
	     <<"     <Upar_option>=0  to make a recoil file withOUT correcting for the Upara efficiency,"<<endl 
	     <<"     <Upar_option>=1  to make a recoil file WITH the Upara efficiency correction," << endl;
    return 1;
  }
  
  std::string in_filename = std::string( argv[argc-4] );
  data_recoilname = in_filename;
  cout<<"Recoil Text File to Unfold: "<<data_recoilname<<endl;

  std::string out_filename = std::string( argv[argc-3] );
  output_label = out_filename;
  cout<<"Output Label: "<<output_label<<endl;
  
  int SET_option = atoi(argv[argc-2]);
  if(SET_option==1) doSETcorr=true;
  else if(SET_option==0) doSETcorr=false;
  else { 
    cout<<"doSETcorr must be 1 or 0!"<<endl;
    return 1;
  }
  cout<<"SEToption: "<<doSETcorr<<endl;

  int Upar_option = atoi(argv[argc-1]);
  if(Upar_option==1) doUparcorr=true;
  else if(Upar_option==0) doUparcorr=false;
  else { 
    cout<<"doUparcorr must be 1 or 0!"<<endl;
    return 1;
  }
  cout<<"Uparoption: "<<doUparcorr<<endl;

  iszrecoil=true;
  recoiloutfile+=output_label;
  recoiloutfile+=".root";
  recoiloutfile2+="TH1D";
  recoiloutfile2+=recoiloutfile;

  // initialize variables and data structures

  cout<<"Initializing Variables and Data Structures..."<<endl;

  InitializeIt(); 

  // calculate final recoil means

  cout<<"Determining Recoil Means..."<<endl;

  DetermineRecoilMeans(true);

  // Make Corrected Recoil Histograms
  
  cout<<"Making Corrected Recoil Hists..."<<endl;
  MakeCorrectedRecoilHists();

  // Write Histograms to New Recoil File
  
  cout<<"Writing Final Histograms..."<<endl;
  WriteHistos();

  cout<<"Total Event Count: "<<totevtcount<<endl;
  for(int i=0; i<_num_recoil_pT_bins; i++){
    cout<<binevtcount[i]<<" events in bin "<<i<<endl;
  }

  /*
  for(int j=0; j<_num_Lumi_bins; j++){
    for(int i=0; i<_num_course_pT_bins; i++){

      if(SETbinevtcount[i][j]<=10) cout<<"SETcount "<<i<<" "<< j <<" "<<SETbinevtcount[i][j]<<endl;
    }
  }
  */

  return 0;
}

