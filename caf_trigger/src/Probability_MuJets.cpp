//----------------------------------------------------------
//Author:   Thomas Gadfort (tgadfort@fnal.gov)
//
//Last Updated: 2007.06.25
//
//Purpose:  Calculates the probability an muon and jet of a certain quality passes the mu+jets trigger condition
//
//History: 2007.06.25 by Liang Li: codes cleaning up; adding detailed debugging output (controlled by 'debug' switch)
//
//----------------------------------------------------------

//Header file for this class
#include "caf_trigger/Probability_MuJets.hpp"
#include "caf_mc_util/MCReqID.hpp"
#include "eff_utils/EffVal.hpp"

using namespace std;

extern caf_mc_util::MCReqID *MCREQID;

Probability_MuJets::Probability_MuJets(const char *name)
  : probProcessor(name)
{
  //We grab terms from the CAFe configuration file here
  cafe::Config config(name);
  
  //------------------------------------
  // Get the list of trigger versions
  //------------------------------------
  //_trigger_version = config.getVString("TriggerVersions", ","); 

  //------------------------------------
  // Channel name
  // This is the value specified to combine in the config file
  //------------------------------------
  _channel = config.get("ChannelName", "MuJets");

  //------------------------------------
  // Debug
  //------------------------------------
  string debug = config.get("Debug", "no");
  _debug = ( debug == "yes" );
  if (_debug) cout << endl << "Debugging for Probability_MuJets is turned on." << endl << endl;

  //------------------------------------
  // Muon_Quality
  //------------------------------------
  _muon_quality = config.get("MuonQuality", "none");
  if ( _muon_quality == "none" ) {
    cout << ">>>>>>> " << name << " WARNING: No MuonQuality parameter was found. Using medium muons as default. If you use any Muon object, please check." << endl;
    _muon_quality = "mediumnseg3";
  }

  //------------------------------------
  // Jet_Quality
  //------------------------------------
  _jet_quality = config.get("JetQuality", "none");
  if ( _jet_quality == "none" ) {
    cout << ">>>>>>> " << name << " WARNING: No JetQuality parameter was found. Using good jets as default. If you use any Jet object, please check." << endl;
    _jet_quality = "goodJet";
  }
  

  //------------------------------------
  // Track_Quality
  //------------------------------------
  _track_quality = config.get("TrackQuality", "none");
  if ( _track_quality == "none" ) {
    cout << ">>>>>>> " << name << " WARNING: No TrackQuality parameter was found. Using medium tracks as default. If you use any Track object, please check." << endl;
    _track_quality = "trackmedium";
  }


  //------------------------------------
  // Split jets turn on curves
  //------------------------------------
  string split_jet = config.get("SplitJet", "yes");
  _split_jet = ( split_jet == "yes" );
  
  
  /*
  //------------------------------------
  // Save the number of trigger version for later use
  //------------------------------------
  _num_trigger_versions = _trigger_version.size();
  if ( _num_trigger_versions == 0 ) {
    cout << endl << name << ": There are no trigger versions. caf_trigger will not work." << endl <<endl;
    exit(1);
  }
  */

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
  _object.push_back("Jet");
  _object.push_back("Track");
  _object.push_back("Match");

  _location.push_back("_INC");
//   _location.push_back("_CC");
//   _location.push_back("_EC");
//   _location.push_back("_ICD");

  _level.push_back("Level1");
  _level.push_back("Level2");
  _level.push_back("Level3");
 
// For mu+dijet
  _object.push_back("Jet1");
  _object.push_back("Jet2");  
  

  /*
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
	      if ( object == "Jet" || object == "Jet1" || object == "Jet2" ) {
		tmp.push_back("TrigEff");
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
	      if ( object == "Muon" || object == "Match" ) {
		tmp.push_back(_muon_quality);
	      }
	      if ( object == "Jet" || object == "Jet1" || object == "Jet2" ) {
		tmp.push_back(_jet_quality);
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
  }  
  */

  //------------------------------------
  // LSC:  I am making a patch for the systematic calculation.
  // Doing the calculation properly would require an interface
  // change.  The three values will be nominal, plus, minus
  // sigma.
  //------------------------------------
  _systematic = config.get("Systematic", "nominal");
  if (_systematic == "plus")    _sigma = +1.0;
  if (_systematic == "nominal") _sigma =  0.0;
  if (_systematic == "minus")   _sigma = -1.0;

  std::cout << "Probability_MuJets systematics setting is " << _systematic << std::endl;
  std::cout << "The value of sigma is set to " << _sigma << std::endl;

    _num_events = 0;
  

}
    
//EffInfo terms are defined here
void Probability_MuJets::defineEffInfo(map< string, eff_utils::EffInfo >& _effInfo)
{
    
  if(_debug) cout<<">>> Probability_MuJets::defineEffInfo(...) <<<"<<endl;
  _passedToProc = false;

  //// Update the trigger map (must be defined in children classes)
  change_triggermap();
    
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
	  if ( _debug ) {
		cout << do_name.str() << " is " << _trigger_map[do_name.str()][0] << endl;
	  }		  
	  
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
		if ( _debug ) cout << "EffName of " << flag_name.str() << " is " <<  eff_utils_variable[0] << endl;     
	      }
	      
	      if ( flag == "EffVarNames" ) {
		_effInfo[effInfoName.str().c_str()].EffVarNames(eff_utils_variable);
		if ( _debug ) cout << "EffVarNames of " << flag_name.str() << " is " <<  eff_utils_variable[0] << " " << eff_utils_variable[1] << endl;     		      
	      }
	      
	      if ( flag == "EffType" ) {
		_effInfo[effInfoName.str().c_str()].EffType(eff_utils_variable[0]);
		if ( _debug ) cout << "EffType of " << flag_name.str() << " is " <<  eff_utils_variable[0] << endl;  		      
	      }
	      
	      if ( flag == "ObjQuality" ) {
		_effInfo[effInfoName.str().c_str()].ObjQuality(eff_utils_variable[0]);
		if ( _debug ) cout << "ObjQuality of " << flag_name.str() << " is " <<  eff_utils_variable[0] << endl;  		      
	      }
	      
	      if ( flag == "ObjRelativeTo" ) {
		_effInfo[effInfoName.str().c_str()].ObjRelativeTo(eff_utils_variable[0]);
		if ( _debug ) cout << "ObjRelativeTo of " << flag_name.str() << " is " <<  eff_utils_variable[0] << endl;  		      
	      }
	      
	      if ( flag == "TriggerVersion" && eff_utils_variable.size() != 0 ) {
		_effInfo[effInfoName.str().c_str()].TriggerVersion(eff_utils_variable[0]);
		if ( _debug ) cout << "TriggerVersion of " << flag_name.str() << " is " <<  eff_utils_variable[0] << endl;  		      
	      }

	      if (flag == "TriggerVersionLow" && eff_utils_variable.size() != 0) {
		_effInfo[effInfoName.str().c_str()].TriggerVersionLow(eff_utils_variable[0]);
		if ( _debug ) cout << "TriggerVersionLow of " << flag_name.str() << " is " <<  eff_utils_variable[0] << endl;  
	      }			

	      if (flag == "TriggerVersionHigh" && eff_utils_variable.size() != 0) {
		_effInfo[effInfoName.str().c_str()].TriggerVersionHigh(eff_utils_variable[0]);
		if ( _debug ) cout << "TriggerVersionHigh of " << flag_name.str() << " is " <<  eff_utils_variable[0] << endl;  
	      }			

	      if ( flag == "ObjType" ) {
		// For mu+dijet 
		if ( object == "Jet1" || object == "Jet2" ) {	      
			_effInfo[effInfoName.str().c_str()].ObjType("Jet");
		if ( _debug ) cout << "ObjType of " << flag_name.str() << " is " <<  "Jet" << endl;  			
		}
		else {
			_effInfo[effInfoName.str().c_str()].ObjType(eff_utils_variable[0]);
		if ( _debug ) cout << "ObjType of " << flag_name.str() << " is " <<  eff_utils_variable[0] << endl;  			
		}		
	      }
	    }
	  }
	}
      }
    }
  }
}

void Probability_MuJets::DefineHistos(std::string version)
{
  if ( _MakeHistos ) {
    std::stringstream muon_name, muon_title;
    std::stringstream muonturnon_name, muonturnon_title;
    std::stringstream jet_name, jet_title;
    std::stringstream jetturnon_name, jetturnon_title;
    std::stringstream mujets_name, mujets_title;
    
    muon_name << "MuonEfficiency_" << _channel << "_" << version;
    muon_title << "Muon Trigger Efficiency for Trigger Version " << version;
    _MuonTriggerEfficiency[version] = new TH1F( muon_name.str().c_str(), muon_title.str().c_str(), 100, 0.0, 1.0);
    
    muonturnon_name << "MuonTurnOn_" << _channel << "_" << version;
    muonturnon_title << "Muon Turn On Curve for Trigger Version " << version;
    _MuonTurnOnCurve[version] = new TH2F( muonturnon_name.str().c_str(), muonturnon_title.str().c_str(), 10, 0.0, TMath::TwoPi(), 10, -2.0, 2.0);
    
    jet_name << "JetEfficiency_" << _channel << "_" << version;
    jet_title << "Jet Trigger Efficiency for Trigger Version " << version;
    _JetTriggerEfficiency[version] = new TH1F( jet_name.str().c_str(), jet_title.str().c_str(), 100, 0.0, 1.0);
    
    jetturnon_name << "JetTurnOn_" << _channel << "_" << version;
    jetturnon_title << "Jet Turn On Curve for Trigger Version " << version;
    _JetTurnOnCurve[version] = new TH2F( jetturnon_name.str().c_str(), jetturnon_title.str().c_str(), 50, 0.0, 100.0, 7, -3.5, 3.5);
    
    mujets_name << "MuJetsEfficiency_" << _channel << "_" << version;
    mujets_title << "MuJets Trigger Efficiency for Trigger Version " << version;
    _MuJetsTriggerEfficiency[version] = new TH1F( mujets_name.str().c_str(), mujets_title.str().c_str(), 100, 0.0, 1.0);
  }
  
  return;
}
  
//--------------------------------------
// The actual probability calculations are defined here and after calcProb
//--------------------------------------
double Probability_MuJets::calcProb(string version)
{
  _num_events++;

  return Prob_MuJets(version);
}

//------------------------------------------------------------------------------
// This calculates the trigger probability
// P(muon,jet) = P(muon) * P(jet)
//------------------------------------------------------------------------------
double Probability_MuJets::Prob_MuJets(string version)
{
  double prob_muon;

  if ( _debug ) {
        cout << endl << "**********************************************" << endl;
	cout << "Event = " << _num_events <<endl;
	cout << "Version= " << version << endl;  
  }
  
  if ( _Indiv ) {
    prob_muon = Prob_MuJets_MuonNew(version);  
  }
  else {
    prob_muon = Prob_MuJets_Muon(version);  
  }

  double prob_jet;

  if ( _Indiv ) {
    prob_jet = Prob_MuJets_JetNew(version);
  }
  else {
    prob_jet = Prob_MuJets_Jet(version);
  }

  double probability = ( prob_muon * prob_jet );

  if ( _MakeHistos ) {
    if ( _MuonTriggerEfficiency[version] ) {
      _MuonTriggerEfficiency[version]->Fill(prob_muon);
    }
    else {
      cout << "MuonTriggerEfficiency histogram not defined" << endl;
      cout << "caf_trigger" << endl;
      exit(1);
    }
    
    if ( _JetTriggerEfficiency[version] ) {
      _JetTriggerEfficiency[version]->Fill(prob_jet);
    }
    else {
      cout << "JetTriggerEfficiency histogram not defined" << endl;
      cout << "caf_trigger" << endl;
      exit(1);
    }
    
    if ( _MuJetsTriggerEfficiency[version] ) {
      _MuJetsTriggerEfficiency[version]->Fill(probability);
    }
    else {
      cout << "MuJetsTriggerEfficiency histogram not defined" << endl;
      cout << "caf_trigger" << endl;
      exit(1);
    }
  }
  
  _jet_eff[version] += prob_jet;
  _muon_eff[version] += prob_muon;

  if ( _debug ) {
    cout << endl;
    cout << "Muon Probability = " << prob_muon << endl;
    cout << "Jet Probability = " << prob_jet << endl;
    cout << "MuJets Probability = " << probability << endl;
  }
  
  return probability;
}

//------------------------------------------------------------------------------
// This calculates the muon probability
//------------------------------------------------------------------------------
double Probability_MuJets::Prob_MuJets_MuonNew(string version){

  double prob_L1 = Prob_MuJets_Muon_Level(version, "Level1");
  double prob_L2 = Prob_MuJets_Muon_Level(version, "Level2");
  double prob_L3 = Prob_MuJets_Muon_Level(version, "Level3");

  double prob = prob_L1 * prob_L2 * prob_L3;

  _muon_eff_L1[version] += prob_L1;
  _muon_eff_L2[version] += prob_L2;
  _muon_eff_L3[version] += prob_L3;

  return( prob );
}

//------------------------------------------------------------------------------
// This calculates the jet probability
//------------------------------------------------------------------------------
double Probability_MuJets::Prob_MuJets_JetNew(string version){

  double prob_L1 = Prob_MuJets_Jet_Level(version, "Level1");
  double prob_L2 = Prob_MuJets_Jet_Level(version, "Level2");
  double prob_L3;
	
  if ( version == "08" || version == "09" || version == "10" || version == "11" || version == "12" || version == "13a" || version == "13b" || version == "13c" || version == "14a" || version == "14b" || version == "14c" || version == "15a2" || version == "15b2" ) {	  
	prob_L3 = Prob_MuJets_Jet_Level(version, "Level3");
  }
  else {
	prob_L3 = Prob_MuJets_Dijet_Level(version, "Level3");

  }	  

  double prob = prob_L1 * prob_L2 * prob_L3;

  _jet_eff_L1[version] += prob_L1;
  _jet_eff_L2[version] += prob_L2;
  _jet_eff_L3[version] += prob_L3;

  return( prob );
}

//*************************************************************************
// This calculates the dijet probability for combined L1/L2/L3
//*************************************************************************

double Probability_MuJets::Prob_MuJets_Dijet_Level(string version, string level){

  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  vector<double> probArray1;
  vector<double> probArray2;	
  string obj[2] = {"Jet1", "Jet2"};

  if ( _debug ) cout << "Probability_MuJets::Prob_MuJets_Dijet_Level debugging starts: " << version << " " << level <<endl;
	  
  //------------------------------------
  // Loop over all jets to get trigger probability
  //------------------------------------
  if ( _debug ) cout << "\tNJets: " << NJET << endl;
	  
  for(int iobj = 0; iobj < NJET; ++iobj) {	  
       for (int k = 0; k < 2; ++k) {
          string object = obj[k];
          vector<double> prob_jet;
          
	    for ( int i = 0; i < _location.size(); ++i ) {
	      string detector = _location[i];      
	      stringstream do_name; 
	      do_name << level << object << "AddToEffUtils_" << version << detector;
		    
	      if ( _debug ) {
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
		
		float val = prob->getProbability(JET[iobj], uncertainty, JetActAs, isRun2b, _debug);
		prob_jet.push_back( val );
		
		if ( _debug ) {
			cout << "\t" << level << " " << object << " " << iobj << " Pt: " << JET[iobj].Pt() << endl;
			cout << "\t" << level << " " << object << " " << iobj << " Eta: " << JET[iobj].Eta() << endl;		  
			cout << "\t" << level << " " << object << " " << iobj << " Val: " << val << endl;
		}		
	      }
	    }

	  double prob = 1.0;
	  if ( _debug )   cout << "\tJet " << iobj << " efficiency size: " << prob_jet.size() << endl;
	  for ( int probs = 0; probs < prob_jet.size(); probs++ ) {
	    prob *= prob_jet[probs];
	  }
	  if ( _debug ) cout << " \tJet " << iobj << " efficiency: " << prob << endl;
	    
	  if ( object == "Jet1" ) {
	    probArray1.push_back(prob); 
	  }
	  else {
	    probArray2.push_back(prob);
	  }	
	    
       }       
  }

  //------------------------------------
  // Fill the turn on curves
  //------------------------------------
  /*
  if ( _MakeHistos ) {
    for(int iobj = 0; iobj < NJET; ++iobj) {
      if ( _JetTurnOnCurve[version] ) {
	_JetTurnOnCurve[version]->Fill(JET[iobj].Pt(), JET[iobj].Eta(), probArray[iobj]);
      }
    }
  }
  */
  
  // Dijet probability calculation (remember: 2 or more jets!)
  //------------------------------------
  // P(>=2) = 1 - P(0) - P(1)
  //------------------------------------
  
  // Probability of exactly 0 jet fired
  double P0 = 1.0;

  // Loop over Jet2 (Jet2 has TIGHTER requirement)
  for(int iobj = 0; iobj < NJET; ++iobj) {
    P0 *= (1.0 - probArray2[iobj]); 
  }
  
  // Probability of exactly 1 jet fired
  double P1 = 0.0;
  // i.e. Probability when Jet1 not fired (but only one Jet2 fired)
  double P11;

  for(int i = 0; i < NJET; ++i) { 
      P11 = 1.0;	  	  
      for (int j = 0; j < NJET; ++j) {
        if ( j != i ) P11 *= (1.0 - probArray1[j]);
      }       
      P1 += probArray2[i]* P11;      
  }  
  
  //------------------------------------
  // We've calculate the P(no) and we need P
  //------------------------------------
  double probCalc;
  probCalc = 1.0 - P0 - P1;

  if ( _debug ) {
      cout << "\t" << version << " " << level << " P0: " << P0 << endl;
      cout << "\t" << version << " " << level << " P1: " << P1 << endl;
      cout << "\t" << version << " " << level << " probCalc: " << probCalc << endl;
  }
    
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
    cout << "Probability_MuJets::Prob_MuJets_Dijet_Level debugging ends: " << _channel << " " << level << " NJet: " << NJET << " Jet Prob: " << probCalc << endl;	
  }
  
  double probability;
  probability = probCalc;
  
  return probability;

}


//*************************************************************************
// This calculates the muon probability for a given level
//*************************************************************************

double Probability_MuJets::Prob_MuJets_Muon_Level(string version, string level){


  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  vector<double> probArray;

  //------------------------------------
  // Loop over all muons to get trigger probability
  //------------------------------------
  if ( _debug ) cout << "\tNMuons: " << NMU << endl;
	  
  for(int iobj = 0; iobj < NMU; ++iobj) {
    vector<double> prob_muon;
    
    for ( int i = 0; i < _location.size(); i++ ) {
      string detector = _location[i];
      
      for (int k = 0; k < _object.size(); k++) {
	string object = _object[k];
	// Make sure not to include the jets here!
	if ( object != "Muon" && object != "Track" && object != "Match" ) continue;

	stringstream do_name; 
	do_name << level << object << "AddToEffUtils_" << version << detector;
        if ( _debug ) {
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
	  if (object=="Muon" || object=="Match") {
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
    cout << _channel << " " << level << " Muon Prob: " << probCalc << endl;
  }
  
  double probability;
  probability = probCalc;
  
  return probability;
}


//*************************************************************************
// This calculates the jet probability for a given level
//*************************************************************************

double Probability_MuJets::Prob_MuJets_Jet_Level(string version, string level){

  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  vector<double> probArray;
	
  if ( _debug ) cout << "Probability_MuJets::Prob_MuJets_Jet_Level debugging starts: " << version << " " << level <<endl; 
	  
  //------------------------------------
  // Loop over all jets to get trigger probability
  //------------------------------------
  if ( _debug ) cout << "\tNJets: " << NJET << endl;
	  
  for(int iobj = 0; iobj < NJET; ++iobj) {
    vector<double> prob_jet;
    
    for ( int i = 0; i < _location.size(); i++ ) {
      string detector = _location[i];
      string object = "Jet";
      
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
	float val = prob->getProbability(JET[iobj], uncertainty, JetActAs, isRun2b, _debug);
	prob_jet.push_back( val );
	
	if ( _debug ) {
		cout << "\t" << object << " " << iobj << " Pt: " << JET[iobj].Pt() << endl;
		cout << "\t" << object << " " << iobj << " Eta: " << JET[iobj].Eta() << endl;		  
		cout << "\t" << object << " " << iobj << " Val: " << val << endl;
	}
	
      }
    }
    
    
    double prob = 1.0;
    if ( _debug )   cout << "\tJet " << iobj << " efficiency size: " << prob_jet.size() << endl;
    for ( int probs = 0; probs < prob_jet.size(); probs++ ) {
      prob *= prob_jet[probs];
    }
    if ( _debug ) cout << " \tJet " << iobj << " efficiency: " << prob << endl;
    
    probArray.push_back(prob);
  }

  //------------------------------------
  // Fill the turn on curves
  //------------------------------------
  if ( _MakeHistos ) {
    for(int iobj = 0; iobj < NJET; ++iobj) {
      if ( _JetTurnOnCurve[version] ) {
	_JetTurnOnCurve[version]->Fill(JET[iobj].Pt(), JET[iobj].Eta(), probArray[iobj]);
      }
    }
  }

  
  //------------------------------------
  // P(not) = Sum(jets) ( 1 - P(jet) )
  //------------------------------------
  double tmpProb = 1.0;
  for(int iobj = 0; iobj < NJET; ++iobj) {
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
    cout << "Probability_MuJets::Prob_MuJets_Jet_Level debugging ends: " << _channel << " " << level << " Jet Prob: " << probCalc << endl;	
  }
  
  double probability;
  probability = probCalc;
  
  return probability;

}


//*************************************************************************
//*************************************************************************
// This calculates the muon probability with combined L1/L2/L3
//*************************************************************************
//*************************************************************************

double Probability_MuJets::Prob_MuJets_Muon(string version){


  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  vector<double> probArray;

 
  //------------------------------------
  // Loop over all muons to get trigger probability
  //------------------------------------
  for(int iobj = 0; iobj < NMU; ++iobj) {
    vector<double> prob_muon;

    for ( int m = 0; m < _level.size(); m++ ) {
      string level = _level[m];
      
      for ( int i = 0; i < _location.size(); i++ ) {
	string detector = _location[i];

	for (int k = 0; k < _object.size(); k++) {
	  string object = _object[k];
	  // Make sure not to include the jets here!
	  if (object == "Jet") continue;
	
	  stringstream do_name; 
	  do_name << level << object << "AddToEffUtils_" << version << detector;
	  if ( _trigger_map[do_name.str()][0] == "yes" ) {

	    stringstream effInfoName;
	    effInfoName << level << object << "_" << version << detector;
	    const objectProbabilities *prob = probObject(effInfoName.str().c_str());
	    if ( prob == 0 ) {
	      cout << endl;
	      cout << "Could not find the effInfo information" << endl;
	      cout << "You gave: " << effInfoName.str() << endl;
	      exit(1);
	    }
	  
	    //double sig = 0.0;
	    double uncertainty = 0.0;
	    if (_sigma == -1.0) uncertainty = -1.0;
	    if (_sigma ==  1.0) uncertainty =  1.0;
	    float val;
	    if (object=="Muon" || object=="Match") {
	      val = prob->getProbability(MU[iobj], uncertainty, isRun2b, _debug);
	    } else {
	      const TMBTrack *muon_track = MU[iobj].GetChargedTrack();
	      val = (muon_track == 0) ? 0 : prob->getProbability(*muon_track, uncertainty, isRun2b, _debug);
	    }
	    prob_muon.push_back( val );
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
    cout << _channel << " Muon Prob = " << probCalc << endl;
  }
  
  double probability;
  probability = probCalc;
  
  return probability;
}


//*************************************************************************
//*************************************************************************
// This calculates the jet probability with combined L1/L2/L3
//*************************************************************************
//*************************************************************************

double Probability_MuJets::Prob_MuJets_Jet(string version){

  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  vector<double> probArray;

  //------------------------------------
  // Loop over all jets to get trigger probability
  //------------------------------------
  //  cout << "Njets: " << NJET << endl;
  for(int iobj = 0; iobj < NJET; ++iobj) {
    vector<double> prob_jet;
    
    for ( int m = 0; m < _level.size(); m++ ) {
      string level = _level[m];
      
      for ( int i = 0; i < _location.size(); i++ ) {
	string detector = _location[i];
	string object = "Jet";
	
	stringstream do_name; 
	do_name << level << object << "AddToEffUtils_" << version << detector;
	//	cout << "DoName: " << do_name.str() << "\tOK = " << _trigger_map[do_name.str()][0] << endl; 
	
	if ( _trigger_map[do_name.str()][0] == "yes" ) {
	  
	  stringstream effInfoName;
	  effInfoName << level << object << "_" << version << detector;
	  //	  cout << "\tEffInfoName: " << effInfoName.str() << endl;
	  
	  const objectProbabilities *prob = probObject(effInfoName.str().c_str());
	  if ( prob == 0 ) {
	    cout << endl;
	    cout << "Could not find the effInfo information" << endl;
	    cout << "You gave: " << effInfoName.str() << endl;
	    exit(1);
	  }
		
	  //double sig = 0.0;
	  double uncertainty = 0.0;
	  if (_sigma == -1.0) uncertainty = -1.0;
	  if (_sigma ==  1.0) uncertainty =  1.0;
	  float val = prob->getProbability(JET[iobj], uncertainty, JetActAs, isRun2b, _debug);
	  prob_jet.push_back( val );
	  //	  cout << "\tVal = " << val << endl;
	}
      }

    }

    double prob = 1.0;
    //    cout << "Size: " << prob_jet.size() << endl;
    for ( int probs = 0; probs < prob_jet.size(); probs++ ) {
      prob *= prob_jet[probs];
    }
    //    cout << "  Jet " << iobj << "\tVal: " << prob << endl;
    
    probArray.push_back(prob);
  }

  //------------------------------------
  // Fill the turn on curves
  //------------------------------------
  if ( _MakeHistos ) {
    for(int iobj = 0; iobj < NJET; ++iobj) {
      if ( _JetTurnOnCurve[version] ) {
	_JetTurnOnCurve[version]->Fill(JET[iobj].Pt(), JET[iobj].Eta(), probArray[iobj]);
      }
    }
  }

  
  //------------------------------------
  // P(not) = Sum(jets) ( 1 - P(jet) )
  //------------------------------------
  double tmpProb = 1.0;
  for(int iobj = 0; iobj < NJET; ++iobj) {
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
    cout << _channel << " Jet Prob = " << probCalc << endl;
  }
  
  double probability;
  probability = probCalc;
  
  return probability;

}

//------------------------------------------------------------------------------
// Finish
//------------------------------------------------------------------------------
void Probability_MuJets::PrintEfficiency()
{
  _num_events /= _trigger_version.size();
  cout.precision(3);
  cout << endl;
  cout << "////////////////////////////////////" << endl;
  cout << endl;
  cout << "Average Trigger Efficiency by Trigger Version" << endl;
  cout << "Version\tJet Efficiency\tMuon Efficiency" << endl;
  for ( map<string,double>::iterator it = _jet_eff.begin(); it != _jet_eff.end(); it++) {
    cout << "  " << it->first << "\t    " << _jet_eff[it->first]/_num_events << "\t     " << _muon_eff[it->first]/_num_events << endl;
    if ( _Indiv ) {
      cout << "   L1\t" << _jet_eff_L1[it->first]/_num_events << "\t     " << _muon_eff_L1[it->first]/_num_events << endl;
      cout << "   L2\t" << _jet_eff_L2[it->first]/_num_events << "\t     " << _muon_eff_L2[it->first]/_num_events << endl;
      cout << "   L3\t" << _jet_eff_L3[it->first]/_num_events << "\t     " << _muon_eff_L3[it->first]/_num_events << endl;
    }
  }
  cout << endl;
  cout << "////////////////////////////////////" << endl;
}

void  Probability_MuJets::change_triggermap() {

  Config config(name());
  //  string name(config.name());
 
  /*
  if (!MCREQID) throw runtime_error("ERROR:  processor MCReqID is not initialized.") ;
  
  // verify if request id is stay the same. In that case do nothing.
  
  if ( MCREQID->reqid() == _reqid ) return ;
  _reqid = MCREQID->reqid() ;
  
    // verify data epochs associated to this MC
  const vector<string>* epochs =  MCREQID->current_data_epochs();
  
  // form identificator for the map
  string ename("TriggerVersions") ;
  for (vector<string>::const_iterator eit=epochs->begin(); 
       eit!=epochs->end(); eit++) 
    ename = ename + "_" + *eit ;
  
  _trigger_version.clear();
  _trigger_version = config.getVString(ename,",");
  */


  //------------------------------------
  // Save the number of trigger version for later use
  //------------------------------------
  _num_trigger_versions =  _trigger_version.size();
  if ( _num_trigger_versions == 0 ) {
    cout << ">>>>>>> " << name() << " There are no trigger versions. caf_trigger will not work." << endl;
    exit(1);
  }

  //------------------------------------
  // Create a map of trigger flags for later use
  //------------------------------------
  _trigger_map.clear();


  
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
	      if ( object == "Jet" || object == "Jet1" || object == "Jet2" ) {
		tmp.push_back("TrigEff");
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
	      if ( object == "Muon" || object == "Match" ) {
		tmp.push_back(_muon_quality);
	      }
	      if ( object == "Jet" || object == "Jet1" || object == "Jet2" ) {
		tmp.push_back(_jet_quality);
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
  }
}


ClassImp(Probability_MuJets)


