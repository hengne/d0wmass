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
// Uncertainties from the trigger paramaterization are not propagated yet.
//
// Nov 2010:   Multi-epoch processing - MB
//-----------------------------------------------------------------

#include "caf_trigger/Probability_nEM.hpp"
#include "eff_utils/EffVal.hpp"

using namespace std;

/// Constructor sets up all the relevant
/// settings from the cafe config files.
///
Probability_nEM::Probability_nEM(const char* name)
  : probProcessor(name) {

  //We grab terms from the CAFe configuration file here
  cafe::Config config(name);

  //------------------------------------
  // Debug
  //------------------------------------
  _debug = config.get("Debug", false);
  if (_debug) cout << endl << "Debugging for Probability_nEM is turned on." << endl << endl;


  //------------------------------------
  // Channel name
  // This is the value specified to combine in the config file
  //------------------------------------
  _channel = config.get("ChannelName", "nEM");

  //-----------------------------------------------
  // Electron quality - must match ElectronSelector
  //-----------------------------------------------
  _electron_quality = config.get("ElectronQuality","none");
  if(_electron_quality=="none") {
    cerr << name << ": WARNING: No ElectronQuality specified, defaulting to top_tight" << endl;
    _electron_quality = "top_tight";
  }

  //------------------------------------
  // Store the eff_utils look-up information
  //------------------------------------
  _flags.push_back("EffName");
  _flags.push_back("EffType");
  _flags.push_back("EffVarNames");
  _flags.push_back("EffVersion");
  _flags.push_back("ObjQuality");
  _flags.push_back("ObjRelativeTo");
  _flags.push_back("ObjType");
  _flags.push_back("TriggerVersionLow");
  _flags.push_back("AddToEffUtils");

} //constuctor

//EffInfo terms are defined here
void Probability_nEM::defineEffInfo(map< string, eff_utils::EffInfo >& _effInfo) {


  if(_debug) cout << "Probability_nEm: " << name() << " DefiningEffInfo" << endl;

  //// Update the trigger map (must be defined in children classes)
  change_triggermap();

  //------------------------------------
  // We create an EffInfo request, then shove it in an object
  // with a name of our choosing to be used later on.
  //------------------------------------
  for ( int i = 0; i < _num_trigger_versions; i++ ) {
    string version = _trigger_version[i];
    
    stringstream do_name;
    do_name << "AddToEffUtils_" << version;
    if(_debug) cout << "\tDo name = " << do_name.str().c_str() << endl;

    if ( _trigger_map[do_name.str()][0] == "yes" ) {
      stringstream effInfoName;
      effInfoName  << version;
      
      for ( int j = 0; j < _flags.size(); j++ ) {
	string flag = _flags[j];
	      
	stringstream flag_name;
	flag_name << flag << "_" << version;
	vector<string> eff_utils_variable = _trigger_map[flag_name.str()];
	//Don't set effInfo if there is no setting for a particular flag
	if(eff_utils_variable.size()==0) {
	  //Print warning unless this is ObjRelative to - we dont
	  //use this for electrons at present (just QbjQuality)
	  if(flag!="ObjRelativeTo") cerr << "Probability_nEM: " << name() << ": WARNING efficiency"
					 << " flag " << flag_name.str().c_str()  << " is not specified" << endl;
	  continue;
	}

	if ( flag == "EffName" ) {
	  _effInfo[effInfoName.str().c_str()].EffName(eff_utils_variable[0]);
	} else if ( flag == "EffVarNames" ) {
	  _effInfo[effInfoName.str().c_str()].EffVarNames(eff_utils_variable);
	} else if ( flag == "EffType" ) {
	  _effInfo[effInfoName.str().c_str()].EffType(eff_utils_variable[0]);
	} else if( flag == "EffVersion" ) {
	  _effInfo[effInfoName.str().c_str()].EffVersion(atoi(eff_utils_variable[0].c_str()));
	} else if ( flag == "ObjQuality" ) {
	  _effInfo[effInfoName.str().c_str()].ObjQuality(eff_utils_variable[0]);
	} else if ( flag == "ObjRelativeTo" ) {
	  _effInfo[effInfoName.str().c_str()].ObjRelativeTo(eff_utils_variable[0]);
	} else if ( flag == "ObjType" ) {
	  _effInfo[effInfoName.str().c_str()].ObjType(eff_utils_variable[0]);
	} else if ( flag == "TriggerVersionLow" ) {
	  _effInfo[effInfoName.str().c_str()].TriggerVersionLow(eff_utils_variable[0]);
	} else if ( flag == "AddToEffUtils" ) {
	  // ignore this. this flag is only used for internal purposes
	} else {
	  cout << name() << " ERROR: internal inconsistency. Ignoring "
	       << flag << endl;
	  exit(1);
	}
      } // loop over flags
    } // Add to effutils
  } // loop over trigger versions.
} // defineEffInfo


//--------------------------------------
// The actual probability calculations are defined here and after calcProb
//--------------------------------------
double Probability_nEM::calcProb(string version) {
 
  map<string,map<int,EffVal> > weightvals;
  
  //Each electron can fire the trigger.
  double emprobs[NEM];

  for (int iobj=0; iobj<NEM; iobj++) {
    // get probabilities (plus information required for uncertainty
    // determination) for this Electron to pass the trigger.
    pair< string, eff_utils::EffVal> weightstore;

					     
    double prob = Prob_EM(version,iobj,weightstore);
    int &binno = weightstore.second.binno;
    // store EffVal object
    string eff_identifier=weightstore.first;
    weightvals[eff_identifier][binno]=weightstore.second;

    emprobs[iobj] = prob;

    //Debug current status
    if (_debug) {
      cout << "Probability_nEM: electron " << iobj << ": " << emprobs[iobj] << endl;
      cout << "Probability = " << emprobs[iobj] << endl;
    }
  } // loop over electrons

  //In order for trigger not to fire all
  //electrons must fail the trigger
  double totalProbNotFire = 1.0;
  for(int iobj=0; iobj<NEM; ++iobj) {
    totalProbNotFire *= (1-emprobs[iobj]);
    if(_debug) cout << "After electron " << iobj << " prob of not firing = " << totalProbNotFire << endl;
  }
  double totalProb = 1.0 - totalProbNotFire;
  if (_debug) {
    cout << "Probability_nEM: event probability = " << totalProb << endl;
  }
  
  return totalProb;

}//calcProb

//------------------------------------
// Calculate trigger probability
//------------------------------------

double Probability_nEM::Prob_EM(string version, int iobj,
				pair<string,eff_utils::EffVal> &weightstore) {
  
  double probproduct=1;

  stringstream do_name; 
  do_name << "AddToEffUtils_" << version;
  if ( _trigger_map[do_name.str()][0] == "yes" ) {
	 
    string effInfoName = version ;
  
    const objectProbabilities *prob = probObject(effInfoName.c_str());
    if ( prob == 0 ) {
      cerr << endl;
      cerr << "Could not find the effInfo information" << endl;
      cerr << "You gave: " << effInfoName << endl;
      exit(1);
    }

    double sig = 0.0;
    EffVal eff;
    float val;
    val = prob->getProbability(EM[iobj], sig, eff, isRun2b, _debug);
    if (_debug) {
      cout << "Probability_nEM::Prob_EM probability " << iobj << ": " << val << endl;
    }
    if (val<0) val=0;
    string eff_identifier = prob->Info()->ObjType()+"_"
      +prob->Info()->ObjQuality()+"_"
      +prob->Info()->ObjRelativeTo();
    weightstore.first = eff_identifier;
    weightstore.second=eff;
    probproduct *= val;
  } //AddToEffUtils

  //------------------------------------
  // Make sure the probability is [0,1]
  //------------------------------------
  if(probproduct > 1.0) {
    cerr << name() << " ERROR: EM probability " << probproduct << endl;
    probproduct = 1.0;
  }
  else if(probproduct < 0.0) {
    cerr << name() << " ERROR: EM probability " << probproduct << endl;
    probproduct = 0.0;
  }
  
  return probproduct;

} //Prob_EM


void  Probability_nEM::change_triggermap() {

  if(_debug) cout<<"==>Probability_nEM::change_triggermap()"<<endl;

  Config config(name());
  //  string name(config.name());
 
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

    string add_to_eff_utils;
	  
    for ( int j = 0; j < _flags.size(); j++ ) {
      string flag = _flags[j];
      
      stringstream flag_name;
      flag_name << flag << "_" << version;
      if(_debug) cout << "\tLooking for flag " << flag_name.str().c_str() << endl;

      vector<string> tmp;

      if ( flag == "AddToEffUtils" ) {
	tmp.push_back(add_to_eff_utils);
      }
      else {
	tmp = config.getVString(flag_name.str().c_str(), " ");
      }
      if ( flag == "EffVarNames" ) {
	if ( tmp.size() == 1 ) {
	  // provide capability to override settings with nothing
	  if ( tmp[0]=="none" ) tmp.clear();
	}
	if ( tmp.size() == 0 ) {
	  add_to_eff_utils = "no";
	}
	else {
	  add_to_eff_utils = "yes";		
	}
      }
	    
      if ( flag == "EffName" && tmp.size() == 0 ) {
	tmp.push_back("eff");
      }
	    
      if ( flag == "EffType" && tmp.size() == 0 ) {
	tmp.push_back("Binned");
      }
      
      if ( flag == "ObjQuality" && tmp.size() == 0 ) { 
	//tmp.push_back("dummy"); 
	if (tmp.size()>0) {
	  cout << " ERROR: must not specify ObjQuality "
	       << "in config file." << endl;
	  exit(1);
	}
	tmp.push_back(_electron_quality);
      } 
      
      if ( flag == "TriggerVersionLow" && tmp.size() == 0 ) {
	continue;
	//tmp.push_back("99");
      }
      
      if ( flag == "ObjRelativeTo" ) {
	if (tmp.size()>0) {
	  cout << " ERROR: must not specify ObjRelativeTo "
	       << "in config file." << endl;
	  exit(1);
	}
      continue;
      //tmp.push_back(_electron_quality);
      }
	
      if ( flag == "ObjType" && tmp.size() == 0 ) {
	tmp.push_back("Electron");
      }
      
      _trigger_map[flag_name.str()] = tmp;
      if(_debug) {
	cout << "\tAdded to trigger map at " << flag_name.str().c_str();
	for(int i=0; i<tmp.size(); ++i) cout << ' ' << tmp[i].c_str();
	cout << endl;
      }
    } // loop over flags
  } // loop over trigger versions
}

ClassImp(Probability_nEM)
