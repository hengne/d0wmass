#ifndef __EMFANALYSIS__
#define __EMFANALYSIS__

#include <vector>

#include <TVectorT.h>
#include <TF2.h>
#include <TH3D.h>
#include <TRandom3.h>

class EMFAnalysis {

private:
  
  std::vector < Double_t >                X0values;       // values of X0 that were used for the simulation
  std::vector < std::vector < TF2* > >        mean;       // mean a function of eta, E, for bins in X0
  std::vector < std::vector < TH3D* > > covariance;       // covariance matrix as a function of X0, eta and E
  TRandom3*                                   rndm;       // random number generator

public:

  EMFAnalysis();                                                        // Default constructor
  EMFAnalysis(const char* configFile, TRandom3* dummy);                 // Constructor
  EMFAnalysis(EMFAnalysis& emfAnalysis);                                // Copy constructor
  ~EMFAnalysis();                                                       // Destructor
  
  TVectorT<Double_t> getEMF     (Double_t nX0, Double_t eta, Double_t E);    // Returns a vector with the simulated EMF
  TVectorT<Double_t> operator() (Double_t nX0, Double_t eta, Double_t E);    // same thing.

  // Accessors
  TRandom3*                                        getRandom() const;
  std::vector < std::vector < TF2* > >          getMeanModel() const;
  std::vector < std::vector < TH3D* > >   getCovarianceModel() const;
  std::vector < Double_t >                       getX0values() const;

};
  
#endif
