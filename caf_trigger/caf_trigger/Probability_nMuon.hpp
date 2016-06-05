//----------------------------------------------------------
//Authors: Thomas Gadfort (tgadfort@fnal.gov) - original single muon code
//         Carsten Hensel (carsten@fnal.gov) - adaptation for dimuon trigger
//         Kristian Harder (harderk@fnal.gov) - combination + error propagation
//
// Last Updated: 4/30/06
//
// Purpose:  Header file for the plugin processor Probability_nMuon
//           Based on Thomas' single muon processor
//----------------------------------------------------------

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include <map>

using namespace std;

class objectProbabilities;

//Inherits from probProcessor
class Probability_nMuon : public probProcessor
{
 public:
  Probability_nMuon(const char *name);
  
  //Define your effInfo objects here
  void defineEffInfo(map< string, eff_utils::EffInfo > &_effInfo);
  
  ////////////////////////////////////////////////////////////
  //These methods define the probability calculations
  double calcProb(string version);
  
  double Prob_Muon(string version, int itrigcond, int iobj,
		   map<string,eff_utils::EffVal> &weightstore);


  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////

  ClassDef(Probability_nMuon, 0);
 private:

  vector<vector<int> > _trigcond;
  int _num_nonempty_trigconds;

  int _num_trigger_versions;
  bool _debug;
  string _muon_quality;
  string _track_quality;
  string _iso_quality;
  string _systematic;
  double _sigma;

  bool _include_jet;

  map<string, vector<string> > _trigger_map;
  vector<string> _level;
  //  vector<string> _trigger_version;
  vector<string> _flags;
  vector<string> _object;
  vector<string> _location;

  unsigned int _reqid ;
  void change_triggermap();
  void change_request();

};

//endfile:
