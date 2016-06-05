//----------------------------------------------------------
// Author:   Thomas Gadfort (tgadfort@fnal.gov)
//
// Last Updated: 2/9/06
//
// Purpose:  Header file for the plugin processor Probability_TopEMu_L2
//           Inherits from probProcessor.
//----------------------------------------------------------

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"

class objectProbabilities;

//Inherits from probProcessor
class Probability_TopEMu_L2 : public probProcessor
{
 public:
  Probability_TopEMu_L2(const char *name);
  
  //Define your effInfo objects here
  void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &_effInfo);
  
  ////////////////////////////////////////////////////////////
  //These methods define the probability calculations
  double calcProb(std::string version);
  
  double Prob_TopEMu_L2(std::string version);
  double Prob_TopEMu_Electron_L2(std::string version);
  double Prob_TopEMu_Muon_L2(std::string version);
  double Prob_TopEMu_Track_L2(std::string version);


  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////

  ClassDef(Probability_TopEMu_L2, 0);
 private:


  std::map<std::string, int> _trigger_version_map;

  int _num_trigger_versions;
  bool _debug;
  bool _split_electron;
  bool _split_jet;

  bool _include_jet;

  std::map<std::string, std::vector<std::string> > _trigger_map;
  std::string _level;
  std::vector<std::string> _trigger_version;
  std::vector<std::string> _flags;
  std::vector<std::string> _object;
  std::vector<std::string> _location;
};

//endfile:
