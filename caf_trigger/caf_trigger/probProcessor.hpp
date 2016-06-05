//file: probProcessor.hpp {probProcessor.cpp}
//
//Author:   Kevin Chan
//
//Purpose:  Header file for the plugin processor probProcessor.

//C++ Objects and interfaces
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iostream>

//CAFe include files
#include "cafe/Processor.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include "TFile.h"

//caf trigger objects and required code
#include "caf_trigger/objectProbabilities.hpp"
#include "caf_trigger/sigmaQuad.hpp"

//eff utils objects and required code
#include "eff_utils/RawEffTool.hpp"
#include "eff_utils/EffInfo.hpp"
#include "eff_utils/EffVal.hpp"

//caf util statistics object
#include "cafe/Stat.hpp"


using namespace eff_utils;
using namespace cafe;

class objectProbabilities;
class StatPointer;

//Inherits from cafe::Processor
class probProcessor : public cafe::Processor
{
 public:
  probProcessor(const char *name);

  //Calculates the event weight and calls the virtual abstract method calcProb
  virtual void eventWeight(std::map<std::string, double> &mRefEvtw);

  //Similarly calculates the event weights with +/- 1 sigma
  virtual void eventWeightSigma(std::map<std::string, double> &mRefEvtw);

  void sigmaSet(std::map< std::string, EffInfo > effInfoPass);

  //The processEvent inherited from cafe::Processor. This gathers
  //the necessary information and passes them on to the eventWeight
  //and eventWeightSigma methods.
  bool processEvent(cafe::Event &event);

  //The begin portion which defines the effInfo object
  void begin();
  void finish();

  virtual void DefineHistos(std::string version) {};

  virtual void PrintEfficiency() {};

  // this method must be implemented by the succesor classes and corresponding
  // meta data will be used to search the efficiencies
  virtual void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &effInfo) = 0;

  // return probabilty object. Can be used to find efficiency yfor the given axis value
  const objectProbabilities *probObject(const std::string &name) const;

  std::string DeterminePath(std::string name);

  ////////////////////////////////////////////////////////////

  //Virtual method defined in the inheriter
  virtual double calcProb(std::string version) = 0;
    
  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////

  ClassDef(probProcessor, 0);

  //Available to the inheritee classes
 protected:

  //Get the TMB objects that have been thrown by the previous processor
  cafe::Collection<TMBEMCluster>  EM;
  cafe::Collection<TMBMuon>       MU;
  cafe::Collection<TMBJet>        JET;
  cafe::Collection<TMBTau>        TAU;

  //And the number of these objects
  int NEM;
  int NMU;
  int NJET;
  float MET;
  int NTAU;
  
  double INSTLUM;

  //Define a variable to determine if we have already put event
  bool _passedToProc;
    
  //Define a map for the version and luminousity
  std::map<std::string, float> _mapVersionLumi;
  std::map<std::string, float> _mapVersionLumi1;
  std::map<std::string, float> _mapVersionLumi2;
  std::vector<std::string> _trigger_version;
  std::vector<float> _trigger_lumi;

  // used if a specific period is picked (randomly) for each event
  std::string         _triggerPeriod;
    
  //Define a string for the channel
  std::string         _channel;

  //Define a string to test whether the user wants the event sigmas
  //Then define a vector of strings to place into mSigma
  std::string         _sigma;
  std::vector<std::string> _sigmaStrings;

  //Define the sigma values
  std::vector<float>    _sigmaValue;

  //This holds the sigma +1,-1 variances
  std::map<std::string, float> mSigma;

  //Map to hold the event weights
  std::map<std::string, double> mEvtw;

  //Map to hold individual object weights use in event weight calculation
  //(needed for proper evaluation of efficiency uncertainties)
  std::map<std::string, std::vector<EffVal> > _corrfactors;
  std::map<std::string, std::vector<double> > _derivatives;

  //construct an objectProbabilities object
  std::map<std::string, objectProbabilities> _objectProb;

  bool _debug;

  std::string _path;
  std::string _path_track;
  std::string _path_electron;
  std::string _path_muon;
  std::string _path_muor;
  std::string _path_jet;
  std::string _path_eleJet;
  std::string _path_tau;

  // Under(over)flow treatment in eff_util efficiencies
  bool _ignoreOverflow, _ignoreUnderflow ;

  // Run2b switch
  int runno;
  int evtno;
  bool isRun2b;
  
  // Jet ActAs Setting
  std::map<std::string, int> _Jet_ActAs_map;
  int JetActAs;

  // Save intermediate weights
  bool _saveweights;
  std::string _channel1;
  std::string _channel2;
  
  struct {
  double prob;
  double prob1;
  double prob2;
  } _savedweights;
 
  void change_request(Event& event);
  unsigned int _reqid;
  std::vector<std::string> _previous_epochs;
};

//endfile:
