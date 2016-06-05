//----------------------------------------------------------
// Author:   Thomas Gadfort (tgadfort@fnal.gov)
//
// Last Updated: 4/11/06
//
// Purpose:  Header file for the plugin processor Probability_MuJets
//           Inherits from probProcessor.
//----------------------------------------------------------

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"


#include <map>

using namespace std;

class objectProbabilities;

//Inherits from probProcessor
class Probability_MuJets : public probProcessor
{
 public:
  Probability_MuJets(const char *name);
  
  //Define your effInfo objects here
  void defineEffInfo(map< string, eff_utils::EffInfo > &_effInfo);
  
  ////////////////////////////////////////////////////////////
  //These methods define the probability calculations
  double calcProb(string version);
  
  double Prob_MuJets(string version);
  double Prob_MuJets_Jet(string version);
  double Prob_MuJets_JetNew(string version);
  double Prob_MuJets_Jet_Level(string version, string level);
  double Prob_MuJets_Dijet_Level(string version, string level); 
  double Prob_MuJets_Muon(string version);
  double Prob_MuJets_MuonNew(string version);
  double Prob_MuJets_Muon_Level(string version, string level);

  void DefineHistos(std::string version);

  void PrintEfficiency();


  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////

  ClassDef(Probability_MuJets, 0);
 private:


  map<string, int> _trigger_version_map;

  int _num_trigger_versions;
  bool _debug;
  bool _split_electron;
  bool _split_jet;
  string _muon_quality;
  string _jet_quality;
  string _track_quality;

  bool _include_jet;

  map<string, double> _jet_eff;
  map<string, double> _jet_eff_L1;
  map<string, double> _jet_eff_L2;
  map<string, double> _jet_eff_L3;
  map<string, double> _muon_eff;
  map<string, double> _muon_eff_L1;
  map<string, double> _muon_eff_L2;
  map<string, double> _muon_eff_L3;
  int _num_events;

  map<string, vector<string> > _trigger_map;
  vector<string> _level;
  /// NO!!! vector<string> _trigger_version;
  vector<string> _flags;
  vector<string> _object;
  vector<string> _location;

  bool _MakeHistos;
  bool _Indiv;

  std::map<std::string, TH1*> _MuonTriggerEfficiency;
  std::map<std::string, TH2*> _MuonTurnOnCurve;
  std::map<std::string, TH1*> _JetTriggerEfficiency;
  std::map<std::string, TH2*> _JetTurnOnCurve;
  std::map<std::string, TH1*> _MuJetsTriggerEfficiency;

  // LSC: This variable holds the value for the systematic
  // error calculation.  The value of 0 is nominal,
  // the value of -1 is minus, and the value of +1
  // in plus.
  std::string _systematic;
  double _sigma;

  unsigned int _reqid ;
  void change_triggermap();
  void change_request();


};

//endfile:
