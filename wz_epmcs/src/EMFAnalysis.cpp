#include <cassert>

#include "EMFAnalysis.hpp"
#include "PParameterReader.hpp"

#include <TMatrixT.h>
#include <TString.h>
#include <TFile.h>
#include <TMath.h>

#include <iostream>

using namespace std;

EMFAnalysis::EMFAnalysis()  {}
EMFAnalysis::~EMFAnalysis() {}

EMFAnalysis::EMFAnalysis(const char* configFile, TRandom3* dummy) : rndm(dummy) 
{

  PParameterReader parm(configFile);

  X0values = parm.GetVDouble("EMFAnalysisX0values");

  TFile* inputFile = TFile::Open(parm.GetChar("EMFAnalysisModelFile"));  
  assert(inputFile->IsOpen());
   
  // Gets the mean functions
  mean.resize(3);
  for (Int_t iLayer=0; iLayer<3; iLayer++) {
    for (Int_t X0Index=0; X0Index < X0values.size(); X0Index++) {
      TF2* meanFunction = (TF2*) inputFile->Get(TString::Format("mean_%d_%d", X0Index, iLayer))->Clone();
      mean[iLayer].push_back(meanFunction);      
      assert(mean[iLayer][X0Index]);
    }
  }
	
  // Gets the covariance matrices
  covariance.resize(3);
  for (Int_t iLayer1=0; iLayer1<3; iLayer1++) {
    for (Int_t iLayer2=0; iLayer2<3; iLayer2++) {
      covariance[iLayer1].push_back((TH3D*) inputFile->Get(TString::Format("covariance_%d_%d", iLayer1, iLayer2)));
      assert(covariance[iLayer1][iLayer2]);
      covariance[iLayer1][iLayer2]->SetDirectory(0);
    }
  }

}

EMFAnalysis::EMFAnalysis(EMFAnalysis& emfAnalysis)
{

  rndm       =          emfAnalysis.getRandom();
  X0values   =        emfAnalysis.getX0values();
  mean       =       emfAnalysis.getMeanModel();
  covariance = emfAnalysis.getCovarianceModel();

}

TVectorT<Double_t> EMFAnalysis::getEMF(Double_t nX0, Double_t eta, Double_t E) 
{
    
  TVectorT<Double_t> retval(3);
  TVectorT<Double_t> retval4(4);

  assert(nX0 > X0values[0]);
  assert(nX0 < X0values[X0values.size()-1]);    
  Int_t X0bin = 0;
  while (nX0 > (X0values[X0bin]+X0values[X0bin+1]/2.)) {
    X0bin++;
    if (X0bin == X0values.size()-1) break;
  }

  TMatrixT<Double_t> covarianceMatrix(3,3);
  for (Int_t iLayer1=0; iLayer1<3; iLayer1++) {
    for (Int_t iLayer2=0; iLayer2<3; iLayer2++) {
      covarianceMatrix[iLayer1][iLayer2] = covariance[iLayer1][iLayer2]->GetBinContent(covariance[iLayer1][iLayer2]->FindBin(nX0, eta, E));
    }
  }

  TVectorD meanVector(3);
  for (Int_t iLayer=0; iLayer<3; iLayer++) {
    meanVector[iLayer] = (nX0 - X0values[X0bin])*(mean[iLayer][X0bin+1]->Eval(eta, E)-mean[iLayer][X0bin]->Eval(eta, E))/(X0values[X0bin+1]-X0values[X0bin]) + mean[iLayer][X0bin]->Eval(eta, E);
  }

  TVectorT<Double_t> eigenvalues(3);
  TMatrixT<Double_t> eigenvectors(3,3);
  eigenvectors = covarianceMatrix.EigenVectors(eigenvalues);

  eigenvectors.Transpose(eigenvectors);
  meanVector = eigenvectors*meanVector;
  
  retval[0] = rndm->Gaus(meanVector[0], TMath::Sqrt(eigenvalues[0]));
  retval[1] = rndm->Gaus(meanVector[1], TMath::Sqrt(eigenvalues[1]));
  retval[2] = rndm->Gaus(meanVector[2], TMath::Sqrt(eigenvalues[2]));
  
  eigenvectors.Transpose(eigenvectors);
  retval = eigenvectors*retval;

  retval4[0] = retval[0];
  retval4[1] = retval[1];
  retval4[2] = retval[2];
  retval4[3] = 1-retval[0]-retval[1]-retval[2];
  
  return retval4;
  
}
 
TVectorT<Double_t> EMFAnalysis::operator() (Double_t nX0, Double_t eta, Double_t E) { return this->getEMF(nX0, eta, E); }

TRandom3*                             EMFAnalysis::getRandom() const            { return rndm; }
std::vector < std::vector < TF2* > >  EMFAnalysis::getMeanModel() const         { return mean; }
std::vector < std::vector < TH3D* > > EMFAnalysis::getCovarianceModel() const   { return covariance; }
std::vector < Double_t >              EMFAnalysis::getX0values() const          { return X0values; }
