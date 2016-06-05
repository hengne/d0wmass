//----------------------------------------------------------
// Author:  Liang Li
//
// Last Updated: 2006.10.02
//
// Purpose:  Header file for the plugin processor Probability_MuJetsORSingleMuonOR
//           Inherits from probProcessor.
//----------------------------------------------------------

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include <map>

using namespace std;

class objectProbabilities;

//Inherits from probProcessor
class Probability_MuJetsORSingleMuonOR : public probProcessor
{
 public:
  Probability_MuJetsORSingleMuonOR(const char *name);
  
  //Define your effInfo objects here
  void defineEffInfo(map< string, eff_utils::EffInfo > &_effInfo);
  
  ////////////////////////////////////////////////////////////
  //These methods define the probability calculations
  double calcProb(string version);
  
  double Prob_MuJetsORSingleMuonOR(string version);
  double Prob_MuJetsOR_Jet(string version, string level);
  double Prob_MuJetsOR_Dijet_Level(string version, string level); 
  double Prob_MuJetsOR_JetIndiv(string version);
  double Prob_MuJetsOR_Muon(string version, string level);
  double Prob_MuJetsOR_MuonIndiv(string version);
  double Prob_MuJetsOR_SingleMuonOR(string version, string level);
  double Prob_MuJetsOR_MuANDSingleMuonOR(string version, string level);

  void DefineHistos(std::string version);

  void PrintEfficiency();

  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////

  ClassDef(Probability_MuJetsORSingleMuonOR, 0);
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
  string _systematic;
  double _sigma;

  map<string, double> _jet_eff;
  map<string, double> _jet_eff_L1;
  map<string, double> _jet_eff_L2;
  map<string, double> _jet_eff_L3;
  map<string, double> _muon_eff;
  map<string, double> _muon_eff_L1;
  map<string, double> _muon_eff_L2;
  map<string, double> _muon_eff_L3;
  map<string, double> _singlemuonor_eff;
  map<string, double> _muandsinglemuonor_eff;
  map<string, double> _mujets_eff;
  map<string, double> _mujetsorsinglemuonor_eff;
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
  std::map<std::string, TH1*> _SingleMuonORTriggerEfficiency;
  std::map<std::string, TH2*> _SingleMuonORTurnOnCurve; 
  std::map<std::string, TH1*> _MuANDSingleMuonORTriggerEfficiency;
  std::map<std::string, TH2*> _MuANDSingleMuonORTurnOnCurve; 
  std::map<std::string, TH1*> _MuJetsORSingleMuonORTriggerEfficiency;  

  unsigned int _reqid ;
  void change_triggermap();
  void change_request();

};

//endfile:
