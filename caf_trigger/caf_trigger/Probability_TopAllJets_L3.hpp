//----------------------------------------------------------
// Author:   Thomas Gadfort (tgadfort@fnal.gov)
//
// Last Updated: 2/9/06
//
// Purpose:  Header file for the plugin processor Probability_TopAllJets_L3
//           Inherits from probProcessor.
//----------------------------------------------------------

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"

class objectProbabilities;

//Inherits from probProcessor
class Probability_TopAllJets_L3 : public probProcessor
{
 public:
  Probability_TopAllJets_L3(const char *name);
  
  //Define your effInfo objects here
  void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &_effInfo);
  
  ////////////////////////////////////////////////////////////
  //These methods define the probability calculations
  double calcProb(std::string version);
  
  double Prob_TopAllJets_L3(std::string version);
  double Prob_TopAllJets_Jet_L3(std::string version);


  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////

  ClassDef(Probability_TopAllJets_L3, 0);
 private:


  std::map<std::string, int> _trigger_version_map;

  int _num_trigger_versions;
  bool _debug;
  bool _split_electron;
  bool _split_jet;

  bool _include_jet;
  bool _include_em;

  std::map<std::string, std::vector<std::string> > _trigger_map;
  std::string _level;
  std::vector<std::string> _trigger_version;
  std::vector<std::string> _flags;
  std::vector<std::string> _object;
  std::vector<std::string> _location;
  std::vector<std::string> _threshold;
};

//endfile:
