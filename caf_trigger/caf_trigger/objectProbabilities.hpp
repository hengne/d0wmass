//file: objectProbabilities.hpp {objectProbabilities.cpp}
//
//Author:   Kevin Chan
//
//Purpose:  Header file for objectProbabilities.cpp

//C++ Objects and interfaces
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#include <iostream>

//CAFe include files
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "cafe/Processor.hpp"

//eff utils objects and required code
#include "eff_utils/RawEffTool.hpp"
#include "eff_utils/EffInfo.hpp"
#include "eff_utils/EffVal.hpp"

#include "caf_trigger/PrelCorr.hpp"
	
#include "tmb_tree/TMBEMCluster.hpp"
#include "tmb_tree/TMBMuon.hpp"
#include "tmb_tree/TMBJet.hpp"
#include "tmb_tree/TMBTrack.hpp"
#include "tmb_tree/TMBTau.hpp"
class TMBEMCluster;
class TMBMuon;
class TMBJet;
class TMBTau;

using namespace eff_utils;

#ifndef PI
#define PI 3.141592654
#endif

#ifndef OBJECT_PROBABILITIES_H
#define OBJECT_PROBABILITIES_H

class turnOnFunctions;

class objectProbabilities
{
 public:

  //Constructor
  objectProbabilities(EffInfo &effInfoObj, const std::string &path="./",
		      bool ignoreOverflow=false, bool ignoreUnderflow=false, bool isRun2b=0);

  //Default constructor defines an empty effTool object
  objectProbabilities() : _effTool(0) {}

  //Destructor
  ~objectProbabilities() {}

  void setSigma(std::map<std::string, float> Sigma);
    
  //Methods for calculating the probability of x objects of N passing
  //the trigger
  double getProb1Objects(const cafe::Collection<TMBEMCluster> &object) const;
  double getProb2Objects(const cafe::Collection<TMBEMCluster> &object) const;
  double getProb3Objects(const cafe::Collection<TMBEMCluster> &object) const;
  double getProb4Objects(const cafe::Collection<TMBEMCluster> &object) const;
    

  double getProb1Objects(const cafe::Collection<TMBMuon> &object) const;
  double getProb2Objects(const cafe::Collection<TMBMuon> &object) const;
  double getProb3Objects(const cafe::Collection<TMBMuon> &object) const;
  double getProb4Objects(const cafe::Collection<TMBMuon> &object) const;
    

  double getProb1Objects(const cafe::Collection<TMBJet> &object) const;
  double getProb2Objects(const cafe::Collection<TMBJet> &object) const;
  double getProb3Objects(const cafe::Collection<TMBJet> &object) const;
  double getProb4Objects(const cafe::Collection<TMBJet> &object) const;


  double getProb1Objects(const cafe::Collection<TMBTau> &object) const;
  double getProb2Objects(const cafe::Collection<TMBTau> &object) const;
  double getProb3Objects(const cafe::Collection<TMBTau> &object) const;
  double getProb4Objects(const cafe::Collection<TMBTau> &object) const;

  const EffInfo* Info() const {return !_effTool ? 0 : &_effTool->Info();}

  //Methods for retrieving the probability from an eff_utils efficiency class.
  double getProbability(const TMBTrack &iObject, double &stat) const;
  double getProbability(const TMBTrack &iObject, double &stat, bool isRun2b) const;
  double getProbability(const TMBTrack &iObject, double &stat, bool isRun2b, bool debug) const;
  double getProbability(const TMBTrack &iObject, double &stat, EffVal &eff) const;
  double getProbability(const TMBTrack &iObject, double &stat, EffVal &eff, bool isRun2b) const;
  double getProbability(const TMBTrack &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug) const;
  double getProbability(const TMBEMCluster &iObject, double &stat) const;
  double getProbability(const TMBEMCluster &iObject, double &stat, bool isRun2b) const;
  double getProbability(const TMBEMCluster &iObject, double &stat, bool isRun2b, bool debug) const;
  double getProbability(const TMBEMCluster &iObject, double &stat, EffVal &eff) const;
  double getProbability(const TMBEMCluster &iObject, double &stat, EffVal &eff, bool isRun2b) const;
  double getProbability(const TMBEMCluster &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug) const;
  double getProbability(const TMBMuon &iObject, double &stat) const;
  double getProbability(const TMBMuon &iObject, double &stat, bool isRun2b) const;
  double getProbability(const TMBMuon &iObject, double &stat, bool isRun2b, bool debug) const;
  double getProbability(const TMBMuon &iObject, double &stat, EffVal &eff) const;
  double getProbability(const TMBMuon &iObject, double &stat, EffVal &eff, bool isRun2b) const;
  double getProbability(const TMBMuon &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug) const;
  double getProbability(const TMBMuon &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug, int njets) const;
  double getProbability(const TMBMuon &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug, int njets, double instlumi) const;

  double getProbability(const TMBJet &iObject, double &stat) const;
  double getProbability(const TMBJet &iObject, double &stat, bool isRun2b) const;  
  double getProbability(const TMBJet &iObject, double &stat, bool isRun2b, bool debug) const;  
  double getProbability(const TMBJet &iObject, double &stat, EffVal &eff) const;
  double getProbability(const TMBJet &iObject, double &stat, EffVal &eff, bool isRun2b) const;  
  double getProbability(const TMBJet &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug) const;  
  double getProbability(const TMBJet &iObject, double &stat, int JetActAs) const;
  double getProbability(const TMBJet &iObject, double &stat, int JetActAs, bool isRun2b) const;  
  double getProbability(const TMBJet &iObject, double &stat, int JetActAs, bool isRun2b, bool debug) const;  
  double getProbability(const TMBJet &iObject, double &stat, EffVal &eff, int JetActAs) const;
  double getProbability(const TMBJet &iObject, double &stat, EffVal &eff, int JetActAs, bool isRun2b) const;  
  double getProbability(const TMBJet &iObject, double &stat, EffVal &eff, int JetActAs, bool isRun2b, bool debug) const;  
  double getProbability(const TMBTau &iObject, double &stat) const;
  double getProbability(const TMBTau &iObject, double &stat, bool isRun2b) const;  
  double getProbability(const TMBTau &iObject, double &stat, bool isRun2b, bool debug) const;  
  double getProbability(const TMBTau &iObject, double &stat, EffVal &eff) const;
  double getProbability(const TMBTau &iObject, double &stat, EffVal &eff, bool isRun2b) const;  
  double getProbability(const TMBTau &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug) const;   
  float EtaDToEtaDet(float const etaD) const;

 private:
  //Defining the sigma variable
  std::map<std::string, float>        mSigma;

  //Create a local EffTool object for use when instantiating the class
  eff_utils::EffTool  *_effTool;

  //Object to load preliminary to final JES correction table
  PrelCorr *_PrelCTable;

};

#endif

//endfile:
