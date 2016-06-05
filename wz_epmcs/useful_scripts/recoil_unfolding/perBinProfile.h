#ifndef perBinProfile_h
#define perBinProfile_h

#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TApplication.h>
#include <TVector2.h>
#include <vector>
#include <map>
#include <TRandom.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraphErrors.h>
#include <iostream>
#include <TMath.h>

class perBinProfile
{

private:

  int _numbins;

  double *_theQuant;
  double *_theQuantSq;
  double *_Numevts;
  
  int _overallNumevts;
  int _overallQuant;
  int _overallQuantSq;

  std::vector<double> _theBinCenters;

public:
  
  perBinProfile(int numbins, std::vector<double> theBinCenters);

  ~perBinProfile();

  int FillQuant(int bin, double quantity, double weight);

  std::vector<double> GetMeans();

  std::vector<int> GetNevts();

  std::vector<double> GetRMSs();

  TGraphErrors *GGetMeans();

  TGraphErrors *GGetRMSs();

  TH1D* GGetNevts();

};

#endif
