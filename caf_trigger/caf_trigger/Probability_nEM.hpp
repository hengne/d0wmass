//---------------------------------------------------------------
// Author: Mark Owen (markowen@fnal.gov) - original code
//
// Created: 27 February 2007
//
// Last Updated: 2 April 2007
//
// Description:
//
// Class to apply trigger efficiencies for single electrons from
// the spc efficiency files. Closely follows Probability_nMuon.
//
//-----------------------------------------------------------------
#ifndef _CAF_TRIGGER_PROBABILITY_NEM_HPP__
#define _CAF_TRIGGER_PROBABILITY_NEM_HPP__

#include "caf_trigger/probProcessor.hpp"
#include "eff_utils/EffInfo.hpp"
#include <utility>
#include <map>
#include <string>
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

class Probability_nEM : public probProcessor {

public:

  /// Constructor
  Probability_nEM(const char* name);

  ///Define your effInfo objects here
  void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &_effInfo);
  
  ////////////////////////////////////////////////////////////
  ///These methods define the probability calculations
  double calcProb(std::string version);
  
  double Prob_EM(std::string version, int iobj,
		   std::pair<std::string,eff_utils::EffVal> &weightstore);


  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////

  ClassDef(Probability_nEM, 0);
  
private:
  
  //vector<vector<int> > _trigcond;
  //int _num_nonempty_trigconds;

  int _num_trigger_versions;
  bool _debug;
  std::string _electron_quality;

  //map to map version to list of trigger conditions
  std::map<std::string, std::vector<std::string> > _trigger_map;

  //  std::vector<std::string> _trigger_version;
  std::vector<std::string> _flags;
  std::vector<std::string> _object;
  std::vector<std::string> _location;

  unsigned int _reqid ;
  void change_triggermap();
};


#endif
