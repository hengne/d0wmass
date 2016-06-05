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
#include<iostream>
#include "perBinProfile.h"
#include <TMath.h>

using namespace std;

perBinProfile::perBinProfile(int numbins, std::vector<double> theBinCenters)
{

  _numbins=numbins;

  _theBinCenters = theBinCenters;

  _Numevts = new double[_numbins];
  _theQuant = new double[_numbins];
  _theQuantSq = new double[_numbins];

  _overallNumevts=0;
  _overallQuant=0;
  _overallQuantSq=0;

 
  for(int i=0; i<_numbins; i++)
    {
      _theQuant[i]=0;
      _theQuantSq[i]=0;
      _Numevts[i]=0;
    }
}



int perBinProfile::FillQuant(int bin, double quantity, double weight)
{

  _Numevts[bin]+=weight;

  _theQuant[bin]+=weight*quantity;
  _theQuantSq[bin]+=weight*quantity*quantity;

  return 1;
}


std::vector<double> perBinProfile::GetMeans()
{
  std::vector<double> theQuantMeans;

  for (int i=0; i<_numbins; i++)
    {
      double dMean;

      if(_Numevts[i]>0) { dMean=(_theQuant[i]/_Numevts[i]); }
      else { dMean=0; }

      theQuantMeans.push_back(dMean);

    }

  return theQuantMeans;
}


std::vector<double> perBinProfile::GetRMSs()
{
  std::vector<double> theRMSs;

  for (int i=0; i<_numbins; i++)
    {
      
      double dsqmean;
      double dmean;
      double drms;

  
      if(_Numevts[i]>0) { dsqmean=(_theQuantSq[i]/_Numevts[i]); }
      else { dsqmean=0; }

      if(_Numevts[i]>0) { dmean=(_theQuant[i]/_Numevts[i]); }
      else { dmean=0; }     

      drms=sqrt( dsqmean - dmean*dmean );

      theRMSs.push_back(drms);
    }
  
  return theRMSs;
}



std::vector<int> perBinProfile::GetNevts()
{
  std::vector<int> theNevts;

  for(int i=0; i<_numbins; i++)
    {
      theNevts.push_back((int)_Numevts[i]);
    }

  return theNevts;
}



TGraphErrors *perBinProfile::GGetMeans()
{

  double *aMean = new double[_numbins];
  double *aErr = new double[_numbins];
  double *abcenter = new double[_numbins];
  double *aXerr = new double[_numbins];

  std::vector<int> itheNevts;  
  std::vector<double> itheMeans;
  std::vector<double> itheRMSs;

  itheNevts = GetNevts();
  itheMeans = GetMeans();
  itheRMSs = GetRMSs();

  for (int i=0; i<_numbins; i++)
    {
      aMean[i] = itheMeans.at(i);
      abcenter[i] = _theBinCenters.at(i);
      if(itheNevts.at(i)>0) aErr[i] = (itheRMSs.at(i))/(sqrt(itheNevts.at(i)));
      else aErr[i] = 0.;
      aXerr[i] = 0.;

      cout<<i<<" "<<aMean[i]<<" "<<aErr[i]<<" "<<abcenter[i]<<" "<<aXerr[i]<<endl;
    }

  TGraphErrors *outgraph = new TGraphErrors(_numbins,abcenter,aMean,aXerr,aErr);
  
  return outgraph;
}


TGraphErrors *perBinProfile::GGetRMSs()
{

  double *aMean = new double[_numbins];
  double *aErr = new double[_numbins];
  double *abcenter = new double[_numbins];
  double *aXerr = new double[_numbins];

  std::vector<int> itheNevts;  
  std::vector<double> itheMeans;
  std::vector<double> itheRMSs;

  itheNevts = GetNevts();
  itheMeans = GetMeans();
  itheRMSs = GetRMSs();

  for (int i=0; i<_numbins; i++)
    {
      aMean[i] = itheRMSs.at(i);
      abcenter[i] = _theBinCenters.at(i);
      if(itheNevts.at(i)>0) aErr[i] = sqrt(2)*(itheRMSs.at(i))/(sqrt(itheNevts.at(i)));
      else aErr[i] = 0.;
      aXerr[i] = 0.;

      cout<<i<<" "<<aMean[i]<<" "<<aErr[i]<<" "<<abcenter[i]<<" "<<aXerr[i]<<endl;
    }

  TGraphErrors *outgraph = new TGraphErrors(_numbins,abcenter,aMean,aXerr,aErr);
  
  return outgraph;
}


TH1D *perBinProfile::GGetNevts()
{
  std::vector<int> itheNevts; 
  TH1D* outhist = new TH1D("nevts","nevts",_numbins,-0.5,((double)_numbins-0.5));

  itheNevts = GetNevts();
  for (int i=0; i<_numbins; i++)
    {
      outhist->SetBinContent(i,itheNevts.at(i)); 
    }

  return outhist;
}


perBinProfile::~perBinProfile()
{
  //  _pt_bins.delete();

  delete _Numevts;
  delete _theQuant;
  delete _theQuantSq;
}

