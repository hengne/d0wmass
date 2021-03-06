#include "TROOT.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "config.hpp"

// global vars
TH1D* hdata;
TH1D* hbkgd;
TH1D* hpmcs;
double fit_min, fit_max;
double GetChi2A(Double_t* par);
double GetChi2B(Double_t* par);
void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void PrintPlots(TCanvas* plots, std::string OutPlotFile, double frac, double frac_err, int stat);


int main(int argc, char** argv) {

  if( argc<2 ) {
     std::cout << " storehist_fullmc:     " << std::endl ;
     std::cout << " Author : Hengne Li @ LPSC 2010 " << std::endl ;
     std::cout << " Functionality: store hists for track match efficiency."  << std::endl;
     std::cout << "                 "  << std::endl;
     std::cout << " usage: storehist storehist.config" << std::endl ;
     exit(1) ;
  }

  std::cout << " storehist:     " << std::endl ;
  std::cout << " Author : Hengne Li @ LPSC 2010 " << std::endl ;

  // readme:

  // open steering file names
  config  steer(std::string((const char*)argv[1]));
  
  // output root file name
  std::string OutRootFile = steer.getString("OutRootFile");
  // input file name
  std::string InRootFile = steer.getString("InRootFile");
  // Electron Basis, if true, it will draw twice for each electron
  bool ElectronBasis = steer.getBool("ElectronBasis");
  // Dimension of efficiency dependece vars: e.g. elecPt 1D , SET-Lumi 2D
  int DepVarDimension = steer.getInt("DepVarDimension");
  if (DepVarDimension>3) {
    std::cout << " Error:: DepVarDimension maximum to be 3 dimintion, no more, modify me if needed! " << std::endl;
    abort();
  }
  if (DepVarDimension==0) {
    std::cout << " Warning:: DepVarDimension should at least be 1 -- set it to be 1 " << std::endl;
    DepVarDimension = 1;
  }

  // Dependence Variable is of electrons?  
  //  For SET or Lumi these Event based variable, it should be set to false, binning
  //   will be written as "set>0&&set<20" ;
  //  For elecPt these electron based variable, it should be set to true, because the binning should be written as 
  //   "elecPt[0]>0&&elecPt[0]<20".
  bool ElectronDepVar1(false), ElectronDepVar2(false), ElectronDepVar3(false);
  ElectronDepVar1 = steer.getBool("ElectronDepVar");
  // only if DepVarDimension above 1, the following will be read 
  if (DepVarDimension>1) ElectronDepVar2 = steer.getBool("ElectronDepVar2");
  // Tree name
  std::string TreeName = steer.getString("TreeName");
  // histogram names : e.g. hnum hdeno or htrk0, htrk1, htrk2
  std::vector<std::string> HistNames = steer.getStringArray("HistNames");
  // efficiency dependence variable name
  std::string DepVarName1, DepVarName2, DepVarName3;
  DepVarName1 = steer.getString("DepVarName");
  // only if DepVarDimension above 1, the following will be read 
  if (DepVarDimension>1) DepVarName2 = steer.getString("DepVarName2");
  if (DepVarDimension>2) DepVarName3 = steer.getString("DepVarName3");
  // dependence variable bins
  std::vector<double> DepVarBins1, DepVarBins2, DepVarBins3;
  DepVarBins1 = steer.getDoubleArray("DepVarBins");
  // only if DepVarDimension above 1, the following will be read 
  if (DepVarDimension>1) DepVarBins2 = steer.getDoubleArray("DepVarBins2");
  if (DepVarDimension>2) DepVarBins3 = steer.getDoubleArray("DepVarBins3");
  // base selection string to be applied everywhere 
  std::string BaseSelection = steer.getString("BaseSelection");
  // First electron selection array for the corresponding histnames 
  std::vector<std::string> SelectionVecE1 = steer.getStringArray("SelectionVecE1");
  // Second electron selection array for the corresponding histnames 
  std::vector<std::string> SelectionVecE2 = steer.getStringArray("SelectionVecE2");

  // initialize
  // root files
  TFile* finput = new TFile(InRootFile.c_str());
  TFile* foutput = new TFile(OutRootFile.c_str(), "recreate");

  // tree
  TTree* tree = (TTree*)finput->Get(TreeName.c_str());

  // Dep variable binning
  int Nbins1 = DepVarBins1.size()-1;
  int Nbins2(1), Nbins3(1);
  if (DepVarDimension>1) Nbins2 = DepVarBins2.size()-1;
  if (DepVarDimension>2) Nbins3 = DepVarBins3.size()-1;

  double Bins1[ (const int)(Nbins1+1) ];
  double Bins2[ (const int)(Nbins2+1) ];
  double Bins3[ (const int)(Nbins3+1) ];

  for (int i=0; i<(int)DepVarBins1.size(); i++){
    Bins1[i] = DepVarBins1.at(i);
  }
  if (DepVarDimension>1) {
    for (int i=0; i<(int)DepVarBins2.size(); i++){
      Bins2[i] = DepVarBins2.at(i);
    }
  }
  if (DepVarDimension>2) {
    for (int i=0; i<(int)DepVarBins3.size(); i++){
      Bins3[i] = DepVarBins3.at(i);
    }
  }

 
  // dependence histograms
  const int Nhists = HistNames.size();
  std::vector<TH1*> Hists;
  for (int i=0; i<Nhists; i++){
      char hname[100];
      TH1* hist;
      sprintf(hname, "%s", HistNames.at(i).c_str());
      if (DepVarDimension==1) {
        hist = new TH1D(hname, hname, Nbins1, Bins1);
      }
      else if (DepVarDimension==2) {
        hist = new TH2D(hname, hname, Nbins1, Bins1, Nbins2, Bins2);
      }
      else if (DepVarDimension==3) {
        hist = new TH3D(hname, hname, Nbins1, Bins1, Nbins2, Bins2, Nbins3, Bins3);
      }
      else{
        std::cout << "Error:: DepVarDimension can be 1 to 3, no more. Modify me if needed!" << std::endl;
        abort();
      }
      hist->Sumw2();
      Hists.push_back(hist);
  }

  // Draw hists
  for (int i=0; i<Nhists; i++){
    char draw[100], sele[500];
    
    // if variables are of electrons
    char str_elecdep1[5], str_elecdep2[5], str_elecdep3[5];
    sprintf(str_elecdep1, "");
    sprintf(str_elecdep2, "");
    sprintf(str_elecdep3, "");

    if (ElectronDepVar1) sprintf(str_elecdep1, "[0]");
    if (DepVarDimension>1 && ElectronDepVar2) sprintf(str_elecdep2, "[0]");
    if (DepVarDimension>2 && ElectronDepVar3) sprintf(str_elecdep2, "[0]");

    // print draw string
    if (DepVarDimension==1) {
      sprintf(draw, "%s%s>>%s", DepVarName1.c_str(), str_elecdep1, HistNames.at(i).c_str());
    }
    else if (DepVarDimension==2) {
      sprintf(draw, "%s%s:%s%s>>%s", DepVarName2.c_str(), str_elecdep2, DepVarName1.c_str(), str_elecdep1, HistNames.at(i).c_str());
    }
    else if (DepVarDimension==3) {
      sprintf(draw, "%s%s:%s%s:%s%s>>%s", DepVarName3.c_str(), str_elecdep3, DepVarName2.c_str(), str_elecdep2, DepVarName1.c_str(), str_elecdep1, HistNames.at(i).c_str());
    }
    else {
      std::cout << " Error::  DepVarDimension can be 1 to 3, no more. Modify me if needed!" << std::endl;
      abort();
    }

    // print sele string
    sprintf(sele, "(%s)&&(%s)", BaseSelection.c_str(), SelectionVecE1.at(i).c_str());
    std::cout << " -- draw = "  << draw << std::endl;
    std::cout << " -- sele = "  << sele << std::endl;
   
    // draw
    tree->Draw(draw, sele);

    // if electron basis, draw for the 2nd electron
    if (ElectronBasis) {

      // if variables are of electrons
      sprintf(str_elecdep1, "");
      sprintf(str_elecdep2, "");
      sprintf(str_elecdep3, "");
      if (ElectronDepVar1) sprintf(str_elecdep1, "[1]");
      if (DepVarDimension>1 && ElectronDepVar2) sprintf(str_elecdep2, "[1]");
      if (DepVarDimension>2 && ElectronDepVar3) sprintf(str_elecdep2, "[1]");

      // print draw string
      if (DepVarDimension==1) {
        sprintf(draw, "%s%s>>+%s", DepVarName1.c_str(), str_elecdep1, HistNames.at(i).c_str());
      }
      else if (DepVarDimension==2) {
        sprintf(draw, "%s%s:%s%s>>+%s", DepVarName2.c_str(), str_elecdep2, DepVarName1.c_str(), str_elecdep1, HistNames.at(i).c_str());
      }
      else if (DepVarDimension==3) {
        sprintf(draw, "%s%s:%s%s:%s%s>>+%s", DepVarName3.c_str(), str_elecdep3, DepVarName2.c_str(), str_elecdep2, DepVarName1.c_str(), str_elecdep1, HistNames.at(i).c_str());
      }
      else {
        std::cout << " Error::  DepVarDimension can be 1 to 3, no more. Modify me if needed!" << std::endl;
        abort();
      }

      // print sele string
      sprintf(sele, "(%s)&&(%s)", BaseSelection.c_str(), SelectionVecE2.at(i).c_str());    
      std::cout << " -- draw = "  << draw << std::endl;
      std::cout << " -- sele = "  << sele << std::endl;

      // draw
      tree->Draw(draw, sele);    
    }
  }

  foutput->cd();
  for (int i=0; i<Nhists; i++){
    Hists.at(i)->Write();
  }
  foutput->Close();
  return 0;
}


