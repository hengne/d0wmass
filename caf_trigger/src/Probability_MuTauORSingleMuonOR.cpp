//----------------------------------------------------------
//Author:  Liang Li (liangli@fnal.gov)
//
//Last Updated: 2008.06.05
//
//Purpose:  Calculates the probability an muon and tau of a certain quality passes the mu+tau trigger OR SingleMuonOR trigger
//                SingleMuonOR is defined as ORing of all available single muon triggers
//
//History:   2007.07.09 by Liang Li: adding detailed debugging output (controlled by 'debug' switch)
//               2006.10.02 by Liang Li: initial release
//
//           2008.06.05 by Abid Patwa:  added Tau and objects & trigger probabilities for mu-tau trigger ORs to code
//----------------------------------------------------------

//Header file for this class
#include "caf_trigger/Probability_MuTauORSingleMuonOR.hpp"

using namespace std;

Probability_MuTauORSingleMuonOR::Probability_MuTauORSingleMuonOR(const char *name)
  : probProcessor(name)
{
  //We grab terms from the CAFe configuration file here
  cafe::Config config(name);


  cout<<"Welcome to the jungle..."<<endl;

  
  //------------------------------------
  // Get the list of trigger versions
  //------------------------------------
  _trigger_version = config.getVString("TriggerVersions", ",");

  //------------------------------------
  // Channel name
  // This is the value specified to combine in the config file
  //------------------------------------
  _channel = config.get("ChannelName", "MuTauOR");

  //------------------------------------
  // Debug
  //------------------------------------
  string debug = config.get("Debug", "no");
  _debug = ( debug == "yes" );
  if (_debug) cout << "Debugging for Probability_MuTauORSingleMuonOR is turned on." << std::endl;
	  
  //------------------------------------
  // Muon_Quality
  //------------------------------------
  _muon_quality = config.get("MuonQuality", "none");
  if ( _muon_quality == "none" ) {
    cout << "WARNING: No MuonQuality parameter was found. Using loose muons as default." << endl;
    _muon_quality = "loose";
  }

  //------------------------------------
  // Tau_Quality
  //------------------------------------
  _tau_quality = config.get("TauQuality", "none");
  if ( _tau_quality == "none" ) {
    cout << "WARNING: No Tau Quality parameter was found. Using loose tau as default." << endl;
    _tau_quality = "loose";
  }

  //------------------------------------
  // Track_Quality
  //------------------------------------
  _track_quality = config.get("TrackQuality", "none");
  if ( _track_quality == "none" ) {
    cout << "WARNING: No TrackQuality parameter was found. Using loose tracks as default." << endl;
    _track_quality = "trackloose";
  }

  //------------------------------------
  // Split taus turn on curves
  //------------------------------------
  string split_tau = config.get("Splittau", "yes");
  _split_tau = ( split_tau == "yes" );
  
  //------------------------------------
  // Save the number of trigger version for later use
  //------------------------------------
  _num_trigger_versions = _trigger_version.size();
  if ( _num_trigger_versions == 0 ) {
    cout << "There are no trigger versions, caf_trigger will not work." << endl;
    exit(1);
  }

  _MakeHistos = config.get("MakeHistos", false);

  _Indiv = config.get("Indiv", true);

  //------------------------------------
  // Store the eff_utils look-up information
  //------------------------------------
  _flags.push_back("EffName");
  _flags.push_back("EffType");
  _flags.push_back("EffVarNames");
  _flags.push_back("ObjQuality");
  _flags.push_back("ObjRelativeTo");
  _flags.push_back("ObjType");
  _flags.push_back("TriggerVersion");
  _flags.push_back("TriggerVersionLow");
  _flags.push_back("TriggerVersionHigh");
  _flags.push_back("AddToEffUtils");

  _object.push_back("Muon");
  _object.push_back("Tau");
  _object.push_back("Track");
  _object.push_back("Match");
  _object.push_back("SingleMuonOR");
  _object.push_back("MuANDSingleMuonOR");

  _location.push_back("_INC");
//   _location.push_back("_CC");
//   _location.push_back("_EC");
//   _location.push_back("_ICD");

  _level.push_back("Level1");
  _level.push_back("Level2");
  _level.push_back("Level3");
  
  
  //------------------------------------
  // Create a map of trigger versions for later use
  //------------------------------------
  for ( int i = 0; i < _num_trigger_versions; i++ ) {
    string version = _trigger_version[i];
    _trigger_version_map[version] = i;
    
    for ( int m = 0; m < _level.size(); m++ ) {
      string level = _level[m];

      for ( int l = 0; l < _location.size(); l++ ) {
	string detector = _location[l];
	
	for ( int k = 0; k < _object.size(); k++ ) {
	  string object = _object[k];
	  
	  string add_to_eff_utils;
	  
	  for ( int j = 0; j < _flags.size(); j++ ) {
	    string flag = _flags[j];
	    
	    stringstream flag_name;
	    flag_name << level << object << flag << "_" << version << detector;
	    
	    vector<string> tmp;
	    if ( flag == "AddToEffUtils" ) {
	      tmp.push_back(add_to_eff_utils);
	    }
	    else {
	      tmp = config.getVString(flag_name.str().c_str(), " ");
	    }
	    
	    if ( flag == "EffVarNames" ) {
	      if ( tmp.size() == 0 ) {
		add_to_eff_utils = "no";
	      }
	      else {
		add_to_eff_utils = "yes";		
	      }
	    }
	    
	    if ( flag == "EffName" && tmp.size() == 0 ) {
	      if ( object == "Tau" ) {
		//		tmp.push_back("TrigEff");
		tmp.push_back("eff");
	      } else {
		tmp.push_back("eff");
	      }
	    }
	  
	    if ( flag == "EffType" && tmp.size() == 0 ) {
	      tmp.push_back("Binned");
	    }
	  
	    if ( flag == "ObjQuality" && tmp.size() == 0 ) {
	      tmp.push_back("matched");
	    }
	  
	    if ( flag == "ObjRelativeTo" && tmp.size() == 0 ) {
	      if ( object == "Muon" || object == "Match" || object == "SingleMuonOR" || object == "MuANDSingleMuonOR" ) {
		tmp.push_back(_muon_quality);
	      }
	      if ( object == "Tau" ) {
		tmp.push_back(_tau_quality);
	      }
	      if ( object == "Track" ) {
		tmp.push_back(_track_quality);
	      }
	    }
	  
	    if ( flag == "ObjType" && tmp.size() == 0 ) {
	      if (object == "Track" || object == "Match") {
		tmp.push_back("Muon");
	      }
	      else {
		tmp.push_back(object);
	      }
            }  
	  
	    _trigger_map[flag_name.str()] = tmp;
	  }
	}
      }
    }

    //------------------------------------
    // "Systematic" calculation
    //------------------------------------
    
    _systematic = config.get("Systematic", "nominal");
    if (_systematic == "plus")    _sigma = +1.0; 
    if (_systematic == "nominal") _sigma =  0.0;
    if (_systematic == "minus")   _sigma = -1.0;
	    
    cout << "Probability_MuTauORSingleMuonOR systematics setting is " << _systematic << endl;
    cout << "The value of sigma is set to " << _sigma << endl;
    
    _num_events = 0;
  }
}
    
//EffInfo terms are defined here
void Probability_MuTauORSingleMuonOR::defineEffInfo(map< string, eff_utils::EffInfo >& _effInfo)
{
    
  _passedToProc = false;

  //------------------------------------
  // We create an EffInfo request, then shove it in an object
  // with a name of our choosing to be used later on.
  //------------------------------------
  for ( int i = 0; i < _num_trigger_versions; i++ ) {
    string version = _trigger_version[i];
    
    for ( int m = 0; m < _level.size(); m++ ) {
      string level = _level[m];

      for ( int l = 0; l < _location.size(); l++ ) {
	string detector = _location[l];
	
	for ( int k = 0; k < _object.size(); k++ ) {
	  string object = _object[k];
	  
	    
	  stringstream do_name;
	  do_name << level << object << "AddToEffUtils_" << version << detector;
	  if ( _trigger_map[do_name.str()][0] == "yes" ) {
	    stringstream effInfoName;
	    effInfoName << level << object << "_" << version << detector;
	    
	    for ( int j = 0; j < _flags.size(); j++ ) {
	      string flag = _flags[j];
	      
	      stringstream flag_name;
	      flag_name << level << object << flag << "_" << version << detector;
	      vector<string> eff_utils_variable = _trigger_map[flag_name.str()];
	      
	      
	      if ( flag == "EffName" ) {
		_effInfo[effInfoName.str().c_str()].EffName(eff_utils_variable[0]);
	      }
	      
	      if ( flag == "EffVarNames" ) {
		_effInfo[effInfoName.str().c_str()].EffVarNames(eff_utils_variable);
	      }
	      
	      if ( flag == "EffType" ) {
		_effInfo[effInfoName.str().c_str()].EffType(eff_utils_variable[0]);
	      }
	      
	      if ( flag == "ObjQuality" ) {
		_effInfo[effInfoName.str().c_str()].ObjQuality(eff_utils_variable[0]);
	      }
	      
	      if ( flag == "ObjRelativeTo" ) {
		_effInfo[effInfoName.str().c_str()].ObjRelativeTo(eff_utils_variable[0]);
	      }
	      
	      if (flag == "TriggerVersionLow" && eff_utils_variable.size() != 0)
		_effInfo[effInfoName.str().c_str()].TriggerVersionLow(eff_utils_variable[0]);
	      
	      if (flag == "TriggerVersionHigh" && eff_utils_variable.size() != 0)
		_effInfo[effInfoName.str().c_str()].TriggerVersionHigh(eff_utils_variable[0]);
	      
	      
	      if ( flag == "ObjType" ) {
		_effInfo[effInfoName.str().c_str()].ObjType(eff_utils_variable[0]);
	      }
	    }
	  }
	}
      }
    }
  }
}

void Probability_MuTauORSingleMuonOR::DefineHistos(std::string version)
{
  if ( _MakeHistos ) {
    std::stringstream muon_name, muon_title;
    std::stringstream muonturnon_name, muonturnon_title;
    std::stringstream tau_name, tau_title;
    std::stringstream tauturnon_name, tauturnon_title;
    std::stringstream mutau_name, mutau_title;
    std::stringstream singlemuonor_name, singlemuonor_title;
    std::stringstream singlemuonorturnon_name, singlemuonorturnon_title;	  
    std::stringstream muandsinglemuonor_name, muandsinglemuonor_title;
    std::stringstream muandsinglemuonorturnon_name, muandsinglemuonorturnon_title;	  
    std::stringstream mutauorsinglemuonor_name, mutauorsinglemuonor_title;	  
	  
    muon_name << "MuonEfficiency_" << version;
    muon_title << "Muon Trigger Efficiency for Trigger Version " << version;
    _MuonTriggerEfficiency[version] = new TH1F( muon_name.str().c_str(), muon_title.str().c_str(), 100, 0.0, 1.0);
    
    muonturnon_name << "MuonTurnOn_" << version;
    muonturnon_title << "Muon Turn On Curve for Trigger Version " << version;
    _MuonTurnOnCurve[version] = new TH2F( muonturnon_name.str().c_str(), muonturnon_title.str().c_str(), 10, 0.0, TMath::TwoPi(), 10, -2.0, 2.0);
    
    tau_name << "TauEfficiency_" << version;
    tau_title << "Tau Trigger Efficiency for Trigger Version " << version;
    _TauTriggerEfficiency[version] = new TH1F( tau_name.str().c_str(), tau_title.str().c_str(), 100, 0.0, 1.0);
    
    tauturnon_name << "TauTurnOn_" << version;
    tauturnon_title << "Tau Turn On Curve for Trigger Version " << version;
    _TauTurnOnCurve[version] = new TH2F( tauturnon_name.str().c_str(), tauturnon_title.str().c_str(), 50, 0.0, 100.0, 7, -3.5, 3.5);
    
    mutau_name << "MuTauEfficiency_" << version;
    mutau_title << "MuTau Trigger Efficiency for Trigger Version " << version;
    _MuTauTriggerEfficiency[version] = new TH1F( mutau_name.str().c_str(), mutau_title.str().c_str(), 100, 0.0, 1.0);
    
    singlemuonor_name << "SingleMuonOREfficiency_" << version;
    singlemuonor_title << "SingleMuonOR Trigger Efficiency for Trigger Version " << version;
    _SingleMuonORTriggerEfficiency[version] = new TH1F( singlemuonor_name.str().c_str(), singlemuonor_title.str().c_str(), 100, 0.0, 1.0);
    
    singlemuonorturnon_name << "SingleMuonORTurnon_" << version;
    singlemuonorturnon_title << "SingleMuonOR Turn On Curve for Trigger Version " << version;
    _SingleMuonORTurnOnCurve[version] = new TH2F( singlemuonorturnon_name.str().c_str(), singlemuonorturnon_title.str().c_str(), 10, 0.0, TMath::TwoPi(), 10, -2.0, 2.0);
    
    muandsinglemuonor_name << "MuANDSingleMuonOREfficiency_" << version;
    muandsinglemuonor_title << "MuANDSingleMuonOR Trigger Efficiency for Trigger Version " << version;
    _MuANDSingleMuonORTriggerEfficiency[version] = new TH1F( muandsinglemuonor_name.str().c_str(), muandsinglemuonor_title.str().c_str(), 100, 0.0, 1.0);
    
    muandsinglemuonorturnon_name << "MuANDSingleMuonORTurnon_" << version;
    muandsinglemuonorturnon_title << "MuANDSingleMuonOR Turn On Curve for Trigger Version " << version;
    _MuANDSingleMuonORTurnOnCurve[version] = new TH2F( muandsinglemuonorturnon_name.str().c_str(), muandsinglemuonorturnon_title.str().c_str(), 10, 0.0, TMath::TwoPi(), 10, -2.0, 2.0);    
    
    mutauorsinglemuonor_name << "MuTauORSingleMuonOREfficiency_" << version;
    mutauorsinglemuonor_title << "MuTauORSingleMuonOR Trigger Efficiency for Trigger Version " << version;
    _MuTauORSingleMuonORTriggerEfficiency[version] = new TH1F( mutauorsinglemuonor_name.str().c_str(), mutauorsinglemuonor_title.str().c_str(), 100, 0.0, 1.0);
    
  }
  
  return;
}
  
//--------------------------------------
// The actual probability calculations are defined here and after calcProb
//--------------------------------------
double Probability_MuTauORSingleMuonOR::calcProb(string version)
{
	
  _num_events++;
  return Prob_MuTauORSingleMuonOR(version);
	
}

double Probability_MuTauORSingleMuonOR::Prob_MuTauORSingleMuonOR(string version)
{
	
  if ( _debug ) {
        cout << endl << "**********************************************" << endl;
	cout << "Event = " << _num_events <<endl;
	cout << "Version= " << version << endl;    
  }
  
  double prob_muon;
  if ( _Indiv ) {
    prob_muon = Prob_MuTauOR_MuonIndiv(version);  
  }
  else {
    prob_muon = Prob_MuTauOR_Muon(version, "All");  
  }
  
  double prob_tau;
  if ( _Indiv ) {
    prob_tau = Prob_MuTauOR_TauIndiv(version);
  }
  else {
    prob_tau = Prob_MuTauOR_Tau(version, "All");
  }
  
  double prob_singlemuonor = Prob_MuTauOR_SingleMuonOR(version, "Level3");
  
  double prob_muandsinglemuonor = Prob_MuTauOR_MuANDSingleMuonOR(version, "Level3");
//------------------------------------------------------------------------------
// This calculates the overall trigger probability
// P(muon,tau) OR P(singlemuonOR) = P(muon) * P(tau) + P(singlemuonOR) - P(muon) * P(SinglemuonOR) * P(tau)
//------------------------------------------------------------------------------
  
  double probability = ( prob_muon * prob_tau + prob_singlemuonor - prob_muandsinglemuonor * prob_tau );
 
  //------------------------------------
  // Make sure the probability is [0,1]
  //------------------------------------
  if(probability > 1.0) {
    probability = 1.0;
  }
  else if(probability < 0.0) {
    probability = 0.0;
  }
  
  if ( _MakeHistos ) {
    if ( _MuonTriggerEfficiency[version] ) {
      _MuonTriggerEfficiency[version]->Fill(prob_muon);
    }
    else {
      cout << "MuonTriggerEfficiency histogram not defined" << endl;
      cout << "caf_trigger" << endl;
      exit(1);
    }
    
    if ( _TauTriggerEfficiency[version] ) {
      _TauTriggerEfficiency[version]->Fill(prob_tau);
    }
    else {
      cout << "TauTriggerEfficiency histogram not defined" << endl;
      cout << "caf_trigger" << endl;
      exit(1);
    }
    
    if ( _MuTauTriggerEfficiency[version] ) {
      _MuTauTriggerEfficiency[version]->Fill(prob_muon*prob_tau);
    }
    else {
      cout << "MuTauTriggerEfficiency histogram not defined" << endl;
      cout << "caf_trigger" << endl;
      exit(1);
    }
    
    if ( _SingleMuonORTriggerEfficiency[version] ) {
      _SingleMuonORTriggerEfficiency[version]->Fill(prob_singlemuonor);
    }
    else {
      cout << "SingleMuonORTriggerEfficiency histogram not defined" << endl;
      cout << "caf_trigger" << endl;
      exit(1);
    }    

    if ( _MuANDSingleMuonORTriggerEfficiency[version] ) {
      _MuANDSingleMuonORTriggerEfficiency[version]->Fill(prob_muandsinglemuonor);
    }
    else {
      cout << "MuANDSingleMuonORTriggerEfficiency histogram not defined" << endl;
      cout << "caf_trigger" << endl;
      exit(1);
    }    

    if ( _MuTauORSingleMuonORTriggerEfficiency[version] ) {
      _MuTauORSingleMuonORTriggerEfficiency[version]->Fill(probability);
    }
    else {
      cout << "MuTauORSingleMuonORTriggerEfficiency histogram not defined" << endl;
      cout << "caf_trigger" << endl;
      exit(1);
    }        
  }

  _tau_eff[version] += prob_tau;
  _muon_eff[version] += prob_muon;
  _mutau_eff[version] += prob_tau*prob_muon;
  _singlemuonor_eff[version] += prob_singlemuonor;
  _muandsinglemuonor_eff[version] += prob_muandsinglemuonor;
  _mutauorsinglemuonor_eff[version] += probability;  

  if ( _debug ) {
    cout << "Muon Probability = "<< prob_muon << endl;
    cout << "Tau Probability = "<< prob_tau << endl;
    cout << "MuTau Probability = " << prob_muon * prob_tau <<endl;
    cout << "SingleMuonOR Probability = "<< prob_singlemuonor << endl;
    cout << "MuANDSingleMuonOR Probability = "<< prob_muandsinglemuonor << endl;	  
    cout << "MuTauORSingleMuonOR Probability = " << probability << endl;
  }
  
  return probability;
}

//------------------------------------------------------------------------------
// This calculates Muon probability
//------------------------------------------------------------------------------
double Probability_MuTauORSingleMuonOR::Prob_MuTauOR_MuonIndiv(string version){

  double prob_L1 = Prob_MuTauOR_Muon(version, "Level1");
  double prob_L2 = Prob_MuTauOR_Muon(version, "Level2");
  double prob_L3 = Prob_MuTauOR_Muon(version, "Level3");
	
  double prob = prob_L1 * prob_L2 * prob_L3;

  _muon_eff_L1[version] += prob_L1;
  _muon_eff_L2[version] += prob_L2;
  _muon_eff_L3[version] += prob_L3;

  return( prob );
}

//------------------------------------------------------------------------------
// This calculates Muon probability (overall or individual level)
//------------------------------------------------------------------------------
double Probability_MuTauORSingleMuonOR::Prob_MuTauOR_Muon(string version, string level="All"){


  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  vector<double> probArray;
  vector<string> levels; 
  string printlevel = level;
  if ( level == "All" ) {
	levels = _level;
  }
  else {
	levels.push_back(level);
  }
  
  //------------------------------------
  // Loop over all muons to get trigger probability
  //------------------------------------
  if ( _debug ) cout << "\tNMuons: " << NMU << endl;
	  
  for(int iobj = 0; iobj < NMU; ++iobj) {
    vector<double> prob_muon;
	    
    for ( int m = 0; m < levels.size(); m++ ) {
	level = levels[m];
      
      for ( int i = 0; i < _location.size(); i++ ) {
	string detector = _location[i];

	for (int k = 0; k < _object.size(); k++) {
	  string object = _object[k];
	  // Make sure not to include non-Muons here!
	  if ( object != "Muon" && object != "Match" && object != "Track" ) continue;
	
	  stringstream do_name; 
	  do_name << level << object << "AddToEffUtils_" << version << detector;
	  if ( _debug) {
		cout << "\tDoName: " << do_name.str() << "\tOK = " << _trigger_map[do_name.str()][0] << endl; 
          }
	  
	  if ( _trigger_map[do_name.str()][0] == "yes" ) {
	    stringstream effInfoName;
	    effInfoName << level << object << "_" << version << detector;
  	    if ( _debug ) {
		cout << "\tEffInfoName: " << effInfoName.str() << endl;
	    }	
	  
	    const objectProbabilities *prob = probObject(effInfoName.str().c_str());
	    if ( prob == 0 ) {
	      cout << endl;
	      cout << "Could not find the effInfo information" << endl;
	      cout << "You gave: " << effInfoName.str() << endl;
	      exit(1);
	    }
	  
	    double uncertainty = 0.0;
	    if (_sigma == -1.0) uncertainty = -1.0;
	    if (_sigma ==  1.0) uncertainty =  1.0;
	    float val;
	    if (object == "Muon" || object == "Match") {
	      val = prob->getProbability(MU[iobj], uncertainty, isRun2b, _debug);
	    } else {
			const TMBTrack *muon_track = MU[iobj].GetChargedTrack();
			val = (muon_track == 0) ? 0 : prob->getProbability(*muon_track, uncertainty, isRun2b, _debug);
	    }
	    prob_muon.push_back( val );
	    
	    if ( _debug ) {
		if ( object =="Track" ) {
			cout << "\t" << object << " " << iobj << " Val: " << val << endl;
		}
		else {
			cout << "\t" << object << " " << iobj << " Eta: " << MU[iobj].Eta() << endl;
			cout << "\t" << object << " " << iobj << " Phi: " << MU[iobj].Phi() << endl;		  
			cout << "\t" << object << " " << iobj << " Val: " << val << endl;
		}
	    }
	  }
	}
      }
    }

    double prob = 1.0;
    if ( _debug )   cout << "\tMuon " << iobj << " efficiency size: " << prob_muon.size() << endl;    
    for ( int probs = 0; probs < prob_muon.size(); probs++ ) {
      prob *= prob_muon[probs];
    }
    if ( _debug ) cout << " \tMuon " << iobj << " efficiency: " << prob << endl;
	    
    probArray.push_back(prob);
  }


  //------------------------------------
  // Fill the turn on curves
  //------------------------------------
  if ( _MakeHistos ) {
    for(int iobj = 0; iobj < NMU; ++iobj) {
      if ( _MuonTurnOnCurve[version] ) {
	_MuonTurnOnCurve[version]->Fill(MU[iobj].Phi(), MU[iobj].Eta(), probArray[iobj]);
      }
    }
  }
  
  //------------------------------------
  // P(not) = Sum(muons) ( 1 - P(muon) )
  //------------------------------------
  double tmpProb = 1.0;
  for(int iobj = 0; iobj < NMU; ++iobj) {
    tmpProb *= (1.0 - probArray[iobj]);
  }

  //------------------------------------
  // We've calculate the P(no) and we need P
  //------------------------------------
  double probCalc;
  probCalc = 1.0 - tmpProb;

  
  //------------------------------------
  // Make sure the probability is [0,1]
  //------------------------------------
  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }
  
  if ( _debug ) {
    cout << _channel << " " << printlevel << " Muon Prob: " << probCalc << endl;
  }
  
  double probability;
  probability = probCalc;
  
  return probability;
}

//------------------------------------------------------------------------------
// This calculates the SingleMuonOR probability
//------------------------------------------------------------------------------
double Probability_MuTauORSingleMuonOR::Prob_MuTauOR_SingleMuonOR(string version, string level="All"){


  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  vector<double> probArray;
  vector<string> levels;
  string printlevel = level;
  if ( level == "All" ) {
	levels = _level;
  }
  else {
	levels.push_back(level);
  }
  
  //------------------------------------
  // Loop over all muons to get trigger probability
  //------------------------------------
  if ( _debug ) cout << "\tNMuons: " << NMU << endl;
	  
  for(int iobj = 0; iobj < NMU; ++iobj) {
    vector<double> prob_muon;  
    
    for ( int m = 0; m < levels.size(); m++ ) {
	level = levels[m];
      
        for ( int i = 0; i < _location.size(); i++ ) {
	string detector = _location[i];
	string object = "SingleMuonOR";
	stringstream do_name; 
	do_name << level << object << "AddToEffUtils_" << version << detector;
	if ( _debug) {
		cout << "\tDoName: " << do_name.str() << "\tOK = " << _trigger_map[do_name.str()][0] << endl; 
	}
	  
	if ( _trigger_map[do_name.str()][0] == "yes" ){
	    stringstream effInfoName;
	    effInfoName << level << object << "_" << version << detector;
  	    if ( _debug ) {
		cout << "\tEffInfoName: " << effInfoName.str() << endl;
	    }	
	    
	    const objectProbabilities *prob = probObject(effInfoName.str().c_str());
	    if ( prob == 0 ) {
	      cout << endl;
	      cout << "Could not find the effInfo information" << endl;
	      cout << "You gave: " << effInfoName.str() << endl;
	      exit(1);
	    }
	    
	    double uncertainty = 0.0;
	    if (_sigma == -1.0) uncertainty = -1.0;
	    if (_sigma ==  1.0) uncertainty =  1.0;
	    float val = prob->getProbability(MU[iobj], uncertainty, isRun2b, _debug);
	    prob_muon.push_back( val );
	    
	    if ( _debug ) {
		cout << "\t" << object << " " << iobj << " Eta: " << MU[iobj].Eta() << endl;
		cout << "\t" << object << " " << iobj << " Phi: " << MU[iobj].Phi() << endl;		  
		cout << "\t" << object << " " << iobj << " Val: " << val << endl;
	    }	  
	    
	}
      }
    }

    double prob = 1.0;
    for ( int probs = 0; probs < prob_muon.size(); probs++ ) {
      prob *= prob_muon[probs];
    }

    probArray.push_back(prob);
  }


  //------------------------------------
  // Fill the turn on curves
  //------------------------------------
  if ( _MakeHistos ) {
    for(int iobj = 0; iobj < NMU; ++iobj) {
      if ( _SingleMuonORTurnOnCurve[version] ) {
	_SingleMuonORTurnOnCurve[version]->Fill(MU[iobj].Phi(), MU[iobj].Eta(), probArray[iobj]);
      }
    }
  }

  //------------------------------------
  // P(not) = Sum(muons) ( 1 - P(muon) )
  //------------------------------------
  double tmpProb = 1.0;
  for(int iobj = 0; iobj < NMU; ++iobj) {
    tmpProb *= (1.0 - probArray[iobj]);
  }

  //------------------------------------
  // We've calculate the P(no) and we need P
  //------------------------------------
  double probCalc;
  probCalc = 1.0 - tmpProb;

  
  //------------------------------------
  // Make sure the probability is [0,1]
  //------------------------------------
  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }
  
  if ( _debug ) {
    cout << _channel << " " << printlevel << " SingleMuonTriggersOR Prob: " << probCalc << endl;
  }
  
  double probability;
  probability = probCalc;
  
  return probability;
}


//------------------------------------------------------------------------------
// This calculates the SingleMuonOR.and.Muon probability
//------------------------------------------------------------------------------
double Probability_MuTauORSingleMuonOR::Prob_MuTauOR_MuANDSingleMuonOR(string version, string level="All"){

	
  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  vector<double> probArray;
  vector<string> levels;
  string printlevel = level;
  if ( level == "All" ) {
	levels = _level;
  }
  else {
	levels.push_back(level);
  }
  
  //------------------------------------
  // Loop over all muons to get trigger probability
  //------------------------------------
  if ( _debug ) cout << "\tNMuons: " << NMU << endl;
	  
  for(int iobj = 0; iobj < NMU; ++iobj) {
    vector<double> prob_muon;    
    for ( int m = 0; m < levels.size(); m++ ) {
	level = levels[m];
      
      for ( int i = 0; i < _location.size(); i++ ) {
	string detector = _location[i];
	string object = "MuANDSingleMuonOR";
	stringstream do_name; 
	do_name << level << object << "AddToEffUtils_" << version << detector;
	if ( _debug) {
		cout << "\tDoName: " << do_name.str() << "\tOK = " << _trigger_map[do_name.str()][0] << endl; 
	}
	
	if ( _trigger_map[do_name.str()][0] == "yes" ){
	    stringstream effInfoName;
	    effInfoName << level << object << "_" << version << detector;
  	    if ( _debug ) {
		cout << "\tEffInfoName: " << effInfoName.str() << endl;
	    }	
	    
	    const objectProbabilities *prob = probObject(effInfoName.str().c_str());
	    if ( prob == 0 ) {
	      cout << endl;
	      cout << "Could not find the effInfo information" << endl;
	      cout << "You gave: " << effInfoName.str() << endl;
	      exit(1);
	    }
	    
	    double uncertainty = 0.0;
	    if (_sigma == -1.0) uncertainty = -1.0;
	    if (_sigma ==  1.0) uncertainty =  1.0;
	    float val = prob->getProbability(MU[iobj], uncertainty, isRun2b, _debug);
	    prob_muon.push_back( val );
	    
	    if ( _debug ) {
		cout << "\t" << object << " " << iobj << " Eta: " << MU[iobj].Eta() << endl;
		cout << "\t" << object << " " << iobj << " Phi: " << MU[iobj].Phi() << endl;		  
		cout << "\t" << object << " " << iobj << " Val: " << val << endl;
	    }	  
	    
	}
     }
   }

    double prob = 1.0;
    for ( int probs = 0; probs < prob_muon.size(); probs++ ) {
      prob *= prob_muon[probs];
    }

    probArray.push_back(prob);
  }

  
  //------------------------------------
  // Fill the turn on curves
  //------------------------------------
  if ( _MakeHistos ) {
    for(int iobj = 0; iobj < NMU; ++iobj) {
      if ( _MuANDSingleMuonORTurnOnCurve[version] ) {
	_MuANDSingleMuonORTurnOnCurve[version]->Fill(MU[iobj].Phi(), MU[iobj].Eta(), probArray[iobj]);
      }
    }
  }

  //------------------------------------
  // P(not) = Sum(muons) ( 1 - P(muon) )
  //------------------------------------
  double tmpProb = 1.0;
  for(int iobj = 0; iobj < NMU; ++iobj) {
    tmpProb *= (1.0 - probArray[iobj]);
  }

  //------------------------------------
  // We've calculate the P(no) and we need P
  //------------------------------------
  double probCalc;
  probCalc = 1.0 - tmpProb;
  
  //------------------------------------
  // Make sure the probability is [0,1]
  //------------------------------------
  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }
  
  if ( _debug ) {
    cout << _channel << " " << printlevel << " MuANDSingleMuonTriggersOR Prob: " << probCalc << endl;
  }
  
  double probability;
  probability = probCalc;
  
  return probability;
}


//------------------------------------------------------------------------------
// This calculates Tau probability
//------------------------------------------------------------------------------
double Probability_MuTauORSingleMuonOR::Prob_MuTauOR_TauIndiv(string version){

  double prob_L1 = Prob_MuTauOR_Tau(version, "Level1");
  double prob_L2 = Prob_MuTauOR_Tau(version, "Level2");
  double prob_L3 = Prob_MuTauOR_Tau(version, "Level3");

  double prob = prob_L1 * prob_L2 * prob_L3;

  _tau_eff_L1[version] += prob_L1;
  _tau_eff_L2[version] += prob_L2;
  _tau_eff_L3[version] += prob_L3;

  return( prob );
}

//------------------------------------------------------------------------------
// This calculates Tau probability (overall or individual level)
//------------------------------------------------------------------------------
double Probability_MuTauORSingleMuonOR::Prob_MuTauOR_Tau(string version, string level="All"){

  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  vector<double> probArray;
  vector<string> levels;	
  string printlevel = level;
  if ( level == "All" ) {
	levels = _level;
  }
  else {
	levels.push_back(level);
  }
  
  //------------------------------------
  // Loop over all taus to get trigger probability
  //------------------------------------
  if ( _debug ) cout << "\tNtaus: " << NTAU << endl;
	  
  for(int iobj = 0; iobj < NTAU; ++iobj) {
    vector<double> prob_tau;
    
    for ( int m = 0; m < levels.size(); m++ ) {
	level = levels[m];
      
      for ( int i = 0; i < _location.size(); i++ ) {
	string detector = _location[i];
	string object = "Tau";
	
	stringstream do_name; 
	do_name << level << object << "AddToEffUtils_" << version << detector;
        if ( _debug) {
	      cout << "\tDoName: " << do_name.str() << "\tOK = " << _trigger_map[do_name.str()][0] << endl; 
        }
      
	if ( _trigger_map[do_name.str()][0] == "yes" ) {	  
	  stringstream effInfoName;
	  effInfoName << level << object << "_" << version << detector;
	  if ( _debug ) {
		cout << "\tEffInfoName: " << effInfoName.str() << endl;
	  }
	  
	  const objectProbabilities *prob = probObject(effInfoName.str().c_str());
	  if ( prob == 0 ) {
	    cout << endl;
	    cout << "Could not find the effInfo information" << endl;
	    cout << "You gave: " << effInfoName.str() << endl;
	    exit(1);
	  }
	  
	  double uncertainty = 0.0;
	  if (_sigma == -1.0) uncertainty = -1.0;
	  if (_sigma ==  1.0) uncertainty =  1.0;
	  float val = prob->getProbability(TAU[iobj], uncertainty, isRun2b, _debug);
 	  prob_tau.push_back( val );
	  
	if ( _debug ) {
		cout << "\t" << object << " " << iobj << " Pt: " << TAU[iobj].Pt() << endl;
		cout << "\t" << object << " " << iobj << " Eta: " << TAU[iobj].Eta() << endl;		  
		cout << "\t" << object << " " << iobj << " Val: " << val << endl;
	}
	  
	}
      }

    }
    
    double prob = 1.0;
    if ( _debug )   cout << "\tTau " << iobj << " efficiency size: " << prob_tau.size() << endl;    
    for ( int probs = 0; probs < prob_tau.size(); probs++ ) {
      prob *= prob_tau[probs];
    }
    if ( _debug ) cout << " \tTau " << iobj << " efficiency: " << prob << endl;
	    
    probArray.push_back(prob);
  }

  //------------------------------------
  // Fill the turn on curves
  //------------------------------------
  if ( _MakeHistos ) {
    for(int iobj = 0; iobj < NTAU; ++iobj) {
      if ( _TauTurnOnCurve[version] ) {
	_TauTurnOnCurve[version]->Fill(TAU[iobj].Pt(), TAU[iobj].Eta(), probArray[iobj]);
      }
    }
  }
  
  //------------------------------------
  // P(not) = Sum(taus) ( 1 - P(tau) )
  //------------------------------------
  double tmpProb = 1.0;
  for(int iobj = 0; iobj < NTAU; ++iobj) {
    tmpProb *= (1.0 - probArray[iobj]);
  }

  //------------------------------------
  // We've calculate the P(no) and we need P
  //------------------------------------
  double probCalc;
  probCalc = 1.0 - tmpProb;

  
  //------------------------------------
  // Make sure the probability is [0,1]
  //------------------------------------
  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }
  
  if ( _debug ) {
    cout << _channel << " " << printlevel << " Tau Prob: " << probCalc << endl;
  }
  
  double probability;
  probability = probCalc;
  
  return probability;

}


//------------------------------------------------------------------------------
// Finish
//------------------------------------------------------------------------------
void Probability_MuTauORSingleMuonOR::PrintEfficiency()
{
  _num_events /= _trigger_version.size();
  cout.precision(3);
  cout << endl;
  cout << "////////////////////////////////////" << endl;
  cout << endl;
  cout << "Average Trigger Efficiency by Trigger Version" << endl;
  cout << "\nVersion\tTau Efficiency\tMuon Efficiency\tMuTau Efficiency\tSingleMuonOR Efficiency\tMuANDSingleMuonOR Efficiency\tMuTauORSingleMuonOR Efficiency" << endl;
  for ( map<string,double>::iterator it = _tau_eff.begin(); it != _tau_eff.end(); it++) {

    cout << "  " << it->first << "\t    " << _tau_eff[it->first]/_num_events << "\t     " << _muon_eff[it->first]/_num_events <<"\t     "
	   << _mutau_eff[it->first]/_num_events <<"\t     "
	   << _singlemuonor_eff[it->first]/_num_events <<"\t     " << _muandsinglemuonor_eff[it->first]/_num_events <<"\t     "
	   << _mutauorsinglemuonor_eff[it->first]/_num_events << endl;
	  
    if ( _Indiv ) {
      cout << "   L1\t" << _tau_eff_L1[it->first]/_num_events << "\t     " << _muon_eff_L1[it->first]/_num_events << endl;
      cout << "   L2\t" << _tau_eff_L2[it->first]/_num_events << "\t     " << _muon_eff_L2[it->first]/_num_events << endl;
      cout << "   L3\t" << _tau_eff_L3[it->first]/_num_events << "\t     " << _muon_eff_L3[it->first]/_num_events << endl;
    }
    
  }
  cout << endl;
  cout << "////////////////////////////////////" << endl;
}

ClassImp(Probability_MuTauORSingleMuonOR)


