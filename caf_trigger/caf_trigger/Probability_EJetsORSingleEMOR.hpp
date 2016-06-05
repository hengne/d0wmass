//----------------------------------------------------------
// Author:   Robert Wagner (rewagner@fnal.gov)
// Based on Probability_Ejets written by:
//           Thomas Gadfort (tgadfort@fnal.gov)
//           Len Christofek (leonard@fnal.gov)
// And Probability_nEM by:
//           Mark Owen (markowen@fnal.gov)
//
// Updated Nov 2010 by Joe Haley (cooljoe@fnal.gov)
//   - Automatic multi-epoch processing and a bunch of
//     "feature" fixes
//
// Purpose:  Calculates the probability an electron+jet of a certain quality
//           to pass the an e+jets trigger OR single EM condition
//----------------------------------------------------------

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

using namespace std;

class objectProbabilities;

//Inherits from probProcessor
class Probability_EJetsORSingleEMOR : public probProcessor
{
 public:
  Probability_EJetsORSingleEMOR(const char *name);
  
  //Define your effInfo objects here
  void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &_effInfo);
  
  ////////////////////////////////////////////////////////////
  //These methods define the probability calculations
  double calcProb(std::string version);
  
  double Prob_Jet(std::string version,std::string trigtype);
  double Prob_Jet3(std::string version,std::string trigtype);
  double Prob_Electron(std::string version,std::string emType);
  double Prob_EM(std::string version, int iobj,std::pair<std::string,eff_utils::EffVal> &weightstore,std::string emType);
  void PrintEfficiency();

  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////

  ClassDef(Probability_EJetsORSingleEMOR, 0);
 private:


  std::map<std::string, int> _trigger_version_map;

  bool _v15andAbove; // Changed from _isRun2b because this is a better name
  int _num_trigger_versions;
  bool _debug;
  bool _split_electron;
  bool _split_jet;
  string _jet_quality;
  string _electron_quality;

  bool _include_jet;
  bool _include_em;
  bool _includeEMshapingAtL3;

  std::map<std::string, std::vector<std::string> > _trigger_map;
  std::vector<std::string> _level;
  //std::vector<std::string> _trigger_version; defined in probProcessor
  //std::vector<float> _trigger_lumi; defined in probProcessor
  std::vector<std::string> _flags;
  std::vector<std::string> _flags_EM;
  std::vector<std::string> _object;
  std::vector<std::string> _location;
  std::vector<std::string> _threshold;
  std::vector<std::string> _jetTrigType;
  std::vector<std::string> _EMTrigType;
  std::vector<double> _uncertaintyArray;

  int _and_is_greater[100], _and_is_much_greater[100];

  std::vector<float> _float_thr;

  // LSC: This variable holds the value for the systematic
  // error calculation.  The value of 0 is nominal,
  // the value of -1 is minus, and the value of +1
  // in plus.
  std::string _systematic;
  double _sigma;

  double _jet1_uncertainty, _jet3_uncertainty, _ejet_uncertainty, _singleem_uncertainty, _and_uncertainty; 
  std::vector<double> _x0, _s0, _x1, _s1, _x2, _s2, _x3, _s3, _x4, _s4, _x5, _s5, _x6, _s6, _x7, _s7; 
  std::vector<double> _x8, _s8, _x9, _s9, _x10, _s10, _x11, _s11, _x12, _s12,_x13,_s13;

  unsigned int _reqid ;
  void change_triggermap();
};

//endfile:
