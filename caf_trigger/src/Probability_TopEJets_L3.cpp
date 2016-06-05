//----------------------------------------------------------
//Author:   Thomas Gadfort (tgadfort@fnal.gov)
//          Len Christofek (leonard@fnal.gov)
//
//Last Updated: 2/23/06
//
//Purpose:  Calculates the probability an electron+jet of a certain quality
//          passes the top e+jets level3 trigger condition
//----------------------------------------------------------

//Header file for this class
#include "caf_trigger/Probability_TopEJets_L3.hpp"

using namespace std;

Probability_TopEJets_L3::Probability_TopEJets_L3(const char *name)
  : probProcessor(name)
{
  // We grab terms from the CAFe configuration file here
  cafe::Config config(name);
  
  //------------------------------------
  // Get the list of trigger versions
  //------------------------------------
  _trigger_version = config.getVString("TriggerVersions", ",");


  //------------------------------------
  // Debug
  //------------------------------------
  std::string debug = config.get("Debug", "no");
  _debug = ( debug == "yes" );
  if (_debug) std::cout << "Debugging for Ejets is turned on." << std::endl;

  //------------------------------------
  // Include jets in EM?
  //------------------------------------
  std::string include_jet = config.get("IncludeJetsInEM", "no");
  _include_jet = ( include_jet == "yes" );


  //------------------------------------
  // Include jets in EM?
  //------------------------------------
  std::string include_em = config.get("IncludeEMInJets", "no");
  _include_em = ( include_em == "yes" );


  //------------------------------------
  // Split electrons turn on curves
  //------------------------------------
  std::string split_electron = config.get("SplitElectron", "yes");
  _split_electron = ( split_electron == "yes" );


  //------------------------------------
  // Split jets turn on curves
  //------------------------------------
  std::string split_jet = config.get("SplitJet", "yes");
  _split_jet = ( split_jet == "yes" );
  
  
  //------------------------------------
  // Save the number of trigger version for later use
  //------------------------------------
  _num_trigger_versions = _trigger_version.size();
  if ( _num_trigger_versions == 0 ) {
    cout << "There are no trigger versions. caf_trigger will not work." << endl;
    exit(1);
  }


  //------------------------------------
  // Store the eff_utils look-up information
  //------------------------------------
  _flags.push_back("EffName");
  _flags.push_back("EffVarNames");
  _flags.push_back("EffType");
  _flags.push_back("ObjQuality");
  //  _flags.push_back("ObjRelativeTo");
  _flags.push_back("ObjType");
  _flags.push_back("Source");
  _flags.push_back("AddToEffUtils");

  _object.push_back("Electron");
  _object.push_back("Jet");

  _location.push_back("_INC");
  _location.push_back("_CC");
  _location.push_back("_EC");
  _location.push_back("_ICD");

  _level = "Level3";

  _threshold.push_back("15");
  _threshold.push_back("20");
  _threshold.push_back("25");
  _threshold.push_back("30");
  _threshold.push_back("35");
  
  //------------------------------------
  // Create a map of trigger versions for later use
  //------------------------------------
  for ( int i = 0; i < _num_trigger_versions; i++ ) {
    std::string version = _trigger_version[i];
    _trigger_version_map[version] = i;
    
    for ( int l = 0; l < _location.size(); l++ ) {
      std::string detector = _location[l];
      
      for ( int k = 0; k < _object.size(); k++ ) {
	std::string object = _object[k];

	for ( int m = 0; m < _threshold.size(); m++ ) {
	  std::string threshold = _threshold[m];
	
	  std::string add_to_eff_utils;

	  for ( int j = 0; j < _flags.size(); j++ ) {
	    std::string flag = _flags[j];

	    std::stringstream flag_name;
	    flag_name << _level << object << flag << "_" << version << detector << "_T" << threshold;
	    if (_debug) std::cout << "Flag name is = " << flag_name.str().c_str() << std::endl;
	    
	    std::vector<std::string> tmp;
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
              tmp.push_back("eff");
	    }

	    if ( flag == "EffType" && tmp.size() == 0 ) {
	      tmp.push_back("Binned");
	    }
	    
	    if ( flag == "ObjQuality" && tmp.size() == 0 ) {
	      tmp.push_back("matched");
	    }
	    
	    //if ( flag == "ObjRelativeTo" && tmp.size() == 0 ) {
	    //  tmp.push_back("loose");
	    //}
	    
	    if ( flag == "ObjType" && tmp.size() == 0 ) {
	      tmp.push_back(object);
	    }
	    
	    if ( flag == "Source" && tmp.size() == 0 ) {
	      tmp.push_back("TopTrigger");
	    }
	    
	    _trigger_map[flag_name.str()] = tmp;
	  }
	}
      }
    }
  }

  //------------------------------------
  // The sigma calculations. False by default
  //------------------------------------
  _sigma = config.get("sigma", "false");
  
}
    
//EffInfo terms are defined here
void Probability_TopEJets_L3::defineEffInfo(std::map< std::string, eff_utils::EffInfo >& _effInfo)
{
  _passedToProc = false;

  //------------------------------------
  // We create an EffInfo request, then shove it in an object
  // with a name of our choosing to be used later on.
  //------------------------------------
  for ( int i = 0; i < _num_trigger_versions; i++ ) {
    std::string version = _trigger_version[i];
    
    for ( int l = 0; l < _location.size(); l++ ) {
      std::string detector = _location[l];
      
      for ( int k = 0; k < _object.size(); k++ ) {
	std::string object = _object[k];

	for ( int m = 0; m < _threshold.size(); m++ ) {
	  std::string threshold = _threshold[m];
	    
	  std::stringstream do_name;
	  do_name << _level << object << "AddToEffUtils_" << version << detector << "_T" << threshold;
	  if (_debug) std::cout << "Going to look for : " << do_name.str().c_str() << std::endl;
	  if ( _trigger_map[do_name.str()][0] == "yes" ) {
	    std::stringstream effInfoName;
	    //	    effInfoName << _level << object << "_" << version << detector;
	    effInfoName << _level << object << "_" << version << detector << "_T" << threshold;
	    if (_debug) std::cout << "L3 Going to store information : " << effInfoName.str() << std::endl;
	    
	    for ( int j = 0; j < _flags.size(); j++ ) {
	      std::string flag = _flags[j];
	      
	      std::stringstream flag_name;
	      flag_name << _level << object << flag << "_" << version << detector << "_T" << threshold;
	      if (_debug) std::cout << "Definition flag = " << flag_name.str().c_str() << std::endl;
	      std::vector<std::string> eff_utils_variable = _trigger_map[flag_name.str()];
	      if (_debug) std::cout << "  Size = " << eff_utils_variable.size() << std::endl;	      
	      
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
	      
	      if ( flag == "ObjRelativeTo" && object == "Electron" ) {
		_effInfo[effInfoName.str().c_str()].ObjRelativeTo(eff_utils_variable[0]);
	      }
	      
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


//--------------------------------------
// The actual probability calculations are defined here and after calcProb
//--------------------------------------
double Probability_TopEJets_L3::calcProb(std::string version)
{
  //------------------------------------
  // This sets up the channel name and is important to set!
  // This is the value specified to combine in the config file
  //------------------------------------
  _channel = "TopEJets_L3";
    
  double probability = Prob_TopEJets_L3(version);

  return probability;

}

//------------------------------------------------------------------------------
// This calculates the l3 probability
// P_L3(electron,jet) = P_L3(electron) * P_L3(jet)
//------------------------------------------------------------------------------
double Probability_TopEJets_L3::Prob_TopEJets_L3(std::string version)
{

  double probability = ( Prob_TopEJets_Electron_L3(version) *
			 Prob_TopEJets_Jet_L3(version) );

  if ( _debug ) {
    cout << "EJets L3 probability = " << probability << endl;
  }

  return probability;
}

//------------------------------------------------------------------------------
// This calculates the electron l3 probability
//------------------------------------------------------------------------------
double Probability_TopEJets_L3::Prob_TopEJets_Electron_L3(std::string version){

  std::string object = "Electron";
  
  bool valid = false;
  for ( int i = 0; i < _location.size(); i++ ) {
    std::string detector = _location[i];
    std::stringstream do_name; 
    do_name << _level << object << "AddToEffUtils_" << version << detector << "_T15";
    if ( _trigger_map[do_name.str()][0] == "yes" ) {
      valid = true;
    }
  }
  
  if ( valid == false ) { return( 1.0 ); }


  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  std::vector<double> probArray;
  double probJet;
  double probEM;

  //------------------------------------
  // Loop over all electrons to get L3 probability
  //------------------------------------
  for(int iobj = 0; iobj < NEM; ++iobj) {
    std::stringstream effInfoName;
    double detector_eta = TMath::Abs(EM[iobj].CalDetectorEta());
    std::string detector;

    if ( _split_electron ) {
      if ( detector_eta <= 1.1 ) {
	effInfoName << _level << object << "_" << version << "_CC" << "_T15";
      }
      else {
	effInfoName << _level << object << "_" << version << "_EC" << "_T15";
      }
    }
    else {
      effInfoName << _level << object << "_" << version << "_INC" << "_T15";
    }

    const objectProbabilities *prob = probObject(effInfoName.str().c_str());
    if ( prob == 0 ) {
      cout << endl;
      cout << "Could not find the effInfo information" << endl;
      cout << "You gave: " << effInfoName.str() << endl;
      exit(1);
    }

    double sig = 0.0;
    float val = prob->getProbability(EM[iobj], sig);
    if (_debug) std::cout << "THE level 3 EM probability is = " << val << std::endl;
    cout.precision(3);
    //    cout << "Ele\t" << version << "\t" << detector_eta << "\t" << EM[iobj].Pt() << "\t" << val << endl;
    probArray.push_back( val );
  }

  //------------------------------------
  // P(not) = Sum(electrons) ( 1 - P(electron) )
  //------------------------------------
  double tmpProb = 1.0;
  for(int iobj = 0; iobj < NEM; ++iobj) {
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
    cout << _channel << " Electron Probability = " << probCalc << endl;
  }

  double probability;
  probability = probCalc;
  
  return probability;
}


//------------------------------------------------------------------------------
// This calculates the jet l3 probability
//------------------------------------------------------------------------------
double Probability_TopEJets_L3::Prob_TopEJets_Jet_L3(std::string version){

  if ( _debug ) {
    cout << "Top EJets L3 (Jets) version = " << version << endl;
  }

  /////////////////////////////////////////////////////////////////////
  // LSC: This part of the code finds and fills the arrays for the
  // jets.
  //////////////////////////////////////////////////////////////////////
  std::string object = "Jet";

  bool valid = false;
  for ( int i = 0; i < _location.size(); i++ ) {
    std::string detector = _location[i];
    for (int j=0; j < _threshold.size(); ++j) {
      std::stringstream do_name; 
      std::string threshold = _threshold[j];
      do_name << _level << object << "AddToEffUtils_" << version << detector << "_T" << threshold;
      if (_debug) cout << "I am looking for trigger map " << do_name.str().c_str() << endl;
      if ( _trigger_map[do_name.str()][0] == "yes" ) {
	valid = true;
      }
    }
  }

  if ( _debug ) cout << "Was the jet trigger map found ? " << valid << endl;
  if ( valid == false ) { return( 1.0 ); }

  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  std::vector<double> probArray;
  double probJet;
  double probEM;

  double prob_t15[100];
  double prob_t20[100];
  double prob_t25[100];
  double prob_t30[100];

  if ( _debug ) {
    cout << "Number of jets = " << NJET << endl;
  }
  
  for(int iobj = 0; iobj < NJET; ++iobj) {
    double detector_eta = TMath::Abs(JET[iobj].detEta()) / 10;

    if ( _debug ) {
      cout << "EJets (Jets) Jet number = " << iobj << "/" << NJET << endl;
    }
    
    for (int i=0; i < _threshold.size(); ++i) {

      bool valid = false;
      for ( int k = 0; k < _location.size(); k++ ) {
	std::string detector = _location[k];
	std::stringstream do_name; 
	std::string threshold = _threshold[i];
	do_name << _level << object << "AddToEffUtils_" << version << detector << "_T" << threshold;
	if ( _trigger_map[do_name.str()][0] == "yes" ) {
	  valid = true;
	}
      }
      if (_debug) std::cout << "Is the trigger valid ? " << valid << std::endl;
      if (!valid) continue;

      std::stringstream effInfoName;
      std::string threshold = _threshold[i];
      if ( _split_jet ) {
	if ( detector_eta <= 0.8 ) {
	  effInfoName << _level << object << "_" << version << "_CC" << "_T" << threshold;
	}
	else if ( detector_eta < 1.5 && detector_eta > 0.8 ) {
	  effInfoName << _level << object << "_" << version << "_ICD" << "_T" << threshold;
	}
	else if ( detector_eta >= 1.5 ) {
	  effInfoName << _level << object << "_" << version << "_EC" << "_T" << threshold;
	} 
	else {
	  //      effInfoName << _level << object << "_" << version << "_INC";
	  cout << "Parameterization not found: " << effInfoName.str() << " in Prob_Ejet_L3_jet." << endl;
	  exit(1);
	}
      }
      if (_debug) std::cout << "Looking for parameterization : " << effInfoName.str().c_str() << std::endl;
      
      const objectProbabilities *prob = probObject(effInfoName.str().c_str());
      if ( prob == 0 ) {
	cout << endl;
	cout << "Could not find the effInfo information" << endl;
	cout << "You gave: " << effInfoName.str() << endl;
	exit(1);
      }
	
      double sig = 0.0;
      float val = prob->getProbability(JET[iobj], sig);
      cout.precision(3);
      //    cout << "Jet\t" << version << "\t" << detector_eta << "\t" << JET[iobj].Pt() << "\t" << val << endl;
      
      // LSC: Fill in the arrays for the probability calculation.
      if (threshold == "15") prob_t15[iobj] = val;
      if (threshold == "20") prob_t20[iobj] = val;
      if (threshold == "25") prob_t25[iobj] = val;
      if (threshold == "30") prob_t30[iobj] = val;
      if ( _debug ) {
	if (threshold == "15") cout << "EJets (Jets) L3 probability T15 = " << prob_t15[iobj] << endl;
	if (threshold == "20") cout << "EJets (Jets) L3 probability T20 = " << prob_t20[iobj] << endl;
	if (threshold == "25") cout << "EJets (Jets) L3 probability T25 = " << prob_t25[iobj] << endl;
	if (threshold == "30") cout << "EJets (Jets) L3 probability T30 = " << prob_t30[iobj] << endl;
      }
    }
  }

  int total_objects = NJET;

  //////////////////////////////////////////////////////////////////////
  // LSC: This part of the code finds and fills the electron
  // into the appropiate arrays.
  //////////////////////////////////////////////////////////////////////
  object = "Electron";

  valid = false;
  for ( int i = 0; i < _location.size(); i++ ) {
    std::string detector = _location[i];
    for (int j=0; j < _threshold.size(); ++j) {
      std::stringstream do_name; 
      std::string threshold = _threshold[j];
      do_name << _level << object << "AddToEffUtils_" << version << detector << "_T" << threshold;
      if (_debug) cout << "I am looking for trigger map " << do_name.str().c_str() << endl;
      if ( _trigger_map[do_name.str()][0] == "yes" ) {
	valid = true;
      }
    }
  }

  if ( _debug ) cout << "Was the EM trigger map found ? " << valid << endl;
  if ( valid == false ) { return( 1.0 ); }

  for(int iobj = 0; iobj < NEM; ++iobj) {
    double detector_eta = TMath::Abs(EM[iobj].CalDetectorEta());

    if ( _debug ) {
      cout << "EJets (Jets) Jet number = " << iobj << "/" << NEM << endl;
    }
    
    for (int i=0; i < _threshold.size(); ++i) {

      bool valid = false;
      for ( int k = 0; k < _location.size(); k++ ) {
	std::string detector = _location[k];
	std::stringstream do_name; 
	std::string threshold = _threshold[i];
	do_name << _level << object << "AddToEffUtils_" << version << detector << "_T" << threshold;
	if ( _trigger_map[do_name.str()][0] == "yes" ) {
	  valid = true;
	}
      }
      if (_debug) std::cout << "Is the EM trigger valid ? " << valid << std::endl;
      if (!valid) continue;

      std::stringstream effInfoName;
      std::string threshold = _threshold[i];
      if ( _split_electron ) {
	if ( detector_eta <= 1.1 ) {
	  effInfoName << _level << object << "_" << version << "_CC" << "_T" << threshold;;
	}
	else {
	  effInfoName << _level << object << "_" << version << "_EC" << "_T" << threshold;;
	}
      }
      else {
	effInfoName << _level << object << "_" << version << "_INC" << "_T" << threshold;;
      }
      if (_debug) std::cout << "Looking for parameterization : " << effInfoName.str().c_str() << std::endl;
      
      const objectProbabilities *prob = probObject(effInfoName.str().c_str());
      if ( prob == 0 ) {
	cout << endl;
	cout << "Could not find the effInfo information" << endl;
	cout << "You gave: " << effInfoName.str() << endl;
	exit(1);
      }
	
      double sig = 0.0;
      float val = prob->getProbability(EM[iobj], sig);
      cout.precision(3);
      //    cout << "Jet\t" << version << "\t" << detector_eta << "\t" << EM[iobj].Pt() << "\t" << val << endl;
      
      // LSC: Fill in the arrays for the probability calculation.
      if (threshold == "15") prob_t15[total_objects + iobj] = val;
      if (threshold == "20") prob_t20[total_objects + iobj] = val;
      if (threshold == "25") prob_t25[total_objects + iobj] = val;
      if (threshold == "30") prob_t30[total_objects + iobj] = val;
      if ( _debug ) {
	if (threshold == "15") cout << "EJets (Jets) L3EM probability T15 = " << prob_t15[total_objects + iobj] << endl;
	if (threshold == "20") cout << "EJets (Jets) L3EM probability T20 = " << prob_t20[total_objects + iobj] << endl;
	if (threshold == "25") cout << "EJets (Jets) L3EM probability T25 = " << prob_t25[total_objects + iobj] << endl;
	if (threshold == "30") cout << "EJets (Jets) L3EM probability T30 = " << prob_t30[total_objects + iobj] << endl;
      }
    }
  }

  total_objects = total_objects + NEM;

  /////////////////////////////////////////////////////////////////////////
  // LSC: Okay, we have filled in the arrays.  Let us see what has
  // really happened.
  /////////////////////////////////////////////////////////////////////////

  if (_debug) {
    cout << "DIAGNOSTIC" << endl;
    for (int i= 0; i < total_objects; i++) {
      cout << " i = " << i << endl;
      cout << "EJets (Jets) L3 probability T15 = " << prob_t15[i] << endl;
      cout << "EJets (Jets) L3 probability T20 = " << prob_t20[i] << endl;
      cout << "EJets (Jets) L3 probability T25 = " << prob_t25[i] << endl;
      cout << "EJets (Jets) L3 probability T30 = " << prob_t30[i] << endl;
    }
  }

  double Pjet;
  if (_debug) cout << "I have version " << version << endl;
  if (version=="14") {
    double P0 = 1.0;
    double P1 = 0.0;
    
    // Calculation that none of the jets are above the threshold of 25 GeV.
    for (int i = 0; i < total_objects; i++)
      P0 *= 1 - prob_t25[i];
    
    // Calculation that at most one of the jets is above the threshold of 25 GeV 
    // and no other jets above 20 GeV.
    double P1_factor_1;
    double P1_factor_2;
    for (int i = 0; i < total_objects; i++) {
      P1_factor_1 = prob_t25[i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t20[j];
      P1 += P1_factor_1 * P1_factor_2;
    }

    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0 - P1;
    if ( _debug ) cout << "V14 EJets (Jets) L3 probability = " << Pjet << endl;

  } else if (version=="13b") {
    double P0 = 1.0;
    double P1 = 0.0;
    
    // Calculation that none of the jets are above the threshold of 30 GeV.
    for (int i = 0; i < total_objects; i++) 
      P0 *= 1 - prob_t30[i];

    // Calculation that at most one of the jets is above the threshold of 30 GeV 
    // and no other jets above 20 GeV.
    double P1_factor_1;
    double P1_factor_2;
    for (int i = 0; i < total_objects; i++) {
      P1_factor_1 = prob_t30[i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t20[j];
      P1 += P1_factor_1 * P1_factor_2;
    }

    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0 - P1;
    if ( _debug ) cout << "V13b EJets (Jets) L3 probability = " << Pjet << endl;

  } else if (version=="13a") {
    double P0 = 1.0;
    double P1 = 0.0;
    
    // Calculation that none of the jets are above the threshold of 25 GeV.
    for (int i = 0; i < total_objects; i++) 
      P0 *= 1 - prob_t25[i];

    // Calculation that at most one of the jets is above the threshold of 25 GeV 
    // and no other jets above 20 GeV.
    double P1_factor_1;
    double P1_factor_2;
    for (int i = 0; i < total_objects; i++) {
      P1_factor_1 = prob_t25[i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t20[j];
      P1 += P1_factor_1 * P1_factor_2;
    }

    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0 - P1;
    if ( _debug ) cout << "V13a EJets (Jets) L3 probability = " << Pjet << endl;

  } else if (version=="12") {
    double P0 = 1.0;
    double P1 = 0.0;

    // Calculation that none of the jets are above the threshold of 20 GeV.
    for (int i = 0; i < total_objects; i++) 
      P0 *= 1 - prob_t20[i];
    
    // Calculation that at most one of the jets is above the threshold of 20 GeV 
    // and no other jets above 20 GeV.
    double P1_factor_1;
    double P1_factor_2;
    for (int i = 0; i < total_objects; i++) {
      P1_factor_1 = prob_t20[i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t20[j];
      P1 += P1_factor_1 * P1_factor_2;
    }
   
    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0 - P1;
    if ( _debug ) cout << "V12 EJets (Jets) L3 probability = " << Pjet << endl;

  } else if (version == "11" || version=="10" || version=="9" || version=="8") {
    double P0 = 1.0;
    double P1 = 0.0;
    
    // Calculation that none of the jets are above the threshold of 15 GeV.
    for (int i = 0; i < total_objects; i++) 
      P0 *= 1 - prob_t15[i];
    
    // Calculation that at most one of the jets is above the threshold of 15 GeV 
    // and no other jets above 15 GeV.
    double P1_factor_1;
    double P1_factor_2;
    for (int i = 0; i < total_objects; i++) {
      P1_factor_1 = prob_t15[i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t15[j];
      P1 += P1_factor_1 * P1_factor_2;
    }
   
    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0 - P1;
    if ( _debug ) cout << "V8-11 EJets (Jets) L3 probability = " << Pjet << endl;
  }

  double probCalc;
  probCalc = Pjet;
  
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
    cout << _channel << " Jet Probability = " << probCalc << endl;
  }

  double probability;
  probability = probCalc;
  
  return probability;

}

ClassImp(Probability_TopEJets_L3)


