//----------------------------------------------------------
//Author:   Thomas Gadfort (tgadfort@fnal.gov)
//          Len Christofek (leonard@fnal.gov)
//
//Last Updated: 5/19/06
//
//Purpose:  Calculates the probability a set of jet to
//          passes the top multijets level3 trigger condition
//----------------------------------------------------------

//Header file for this class
#include "caf_trigger/Probability_TopAllJets_L3.hpp"

using namespace std;

Probability_TopAllJets_L3::Probability_TopAllJets_L3(const char *name)
  : probProcessor(name)
{
  //We grab terms from the CAFe configuration file here
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
  _flags.push_back("EffType");
  _flags.push_back("EffVarNames");
  _flags.push_back("ObjQuality");
  //  _flags.push_back("ObjRelativeTo");
  _flags.push_back("ObjType");
  _flags.push_back("Source");
  _flags.push_back("AddToEffUtils");

  _object.push_back("Multijet");

  _location.push_back("_INC");
  _location.push_back("_CC");
  _location.push_back("_EC");
  _location.push_back("_ICD");

  _level = "Level3";

  _threshold.push_back("10");
  _threshold.push_back("12");
  _threshold.push_back("15");
  _threshold.push_back("20");
  _threshold.push_back("25");
  
  
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
	    
	    if ( flag == "ObjRelativeTo" && tmp.size() == 0 ) {
	      tmp.push_back("loose");
	    }
	    
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
void Probability_TopAllJets_L3::defineEffInfo(std::map< std::string, eff_utils::EffInfo >& _effInfo)
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
	      
	      if ( flag == "ObjRelativeTo" && object == "Muon" ) {
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
double Probability_TopAllJets_L3::calcProb(std::string version)
{
  //------------------------------------
  // This sets up the channel name and is important to set!
  // This is the value specified to combine in the config file
  //------------------------------------
  _channel = "TopAllJets_L3";
    
  double probability = Prob_TopAllJets_L3(version);

  return probability;

}

//------------------------------------------------------------------------------
// This calculates the l3 probability
// P_L3(electron,jet) = P_L3(electron) * P_L3(jet)
//------------------------------------------------------------------------------
double Probability_TopAllJets_L3::Prob_TopAllJets_L3(std::string version)
{

  double probability = ( Prob_TopAllJets_Jet_L3(version) );

  if ( _debug ) {
    cout << "AllJets L3 probability = " << probability << endl;
  }

  return probability;
}


//------------------------------------------------------------------------------
// This calculates the jet l3 probability
//------------------------------------------------------------------------------
double Probability_TopAllJets_L3::Prob_TopAllJets_Jet_L3(std::string version){

  if ( _debug ) {
    cout << "Top multijets L3 version = " << version << endl;
  }
  std::string object = "Jet";
  
  bool valid = false;
  for ( int i = 0; i < _location.size(); i++ ) {
    std::string detector = _location[i];
    for (int j=0; j < _threshold.size(); ++j) {
      std::stringstream do_name; 
      std::string threshold = _threshold[j];
      do_name << _level << object << "AddToEffUtils_" << version << detector;
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

  double prob_t10[100];
  double prob_t12[100];
  double prob_t15[100];
  double prob_t20[100];
  double prob_t25[100];

  if ( _debug ) {
    cout << "Number of jets = " << NJET << endl;
  }
  
  //------------------------------------
  // Loop over all jets to get L3 probability
  //------------------------------------
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
      float val = prob->getProbability(JET[iobj], sig, isRun2b, _debug);
      cout.precision(3);
      
      // LSC: Fill in the arrays for the probability calculation.
      if (threshold == "10") prob_t10[iobj] = val;
      if (threshold == "12") prob_t12[iobj] = val;
      if (threshold == "15") prob_t15[iobj] = val;
      if (threshold == "20") prob_t20[iobj] = val;
      if (threshold == "25") prob_t25[iobj] = val;
      if ( _debug ) {
	if (threshold == "10") cout << "Multijets L3 probability T10 = " << prob_t10[iobj] << endl;
	if (threshold == "12") cout << "Multijets L3 probability T12 = " << prob_t12[iobj] << endl;
	if (threshold == "15") cout << "Multijets L3 probability T15 = " << prob_t15[iobj] << endl;
	if (threshold == "20") cout << "Multijets L3 probability T20 = " << prob_t20[iobj] << endl;
	if (threshold == "25") cout << "Multijets L3 probability T25 = " << prob_t25[iobj] << endl;
      }
    }
  }
  
  int total_objects = NJET;
  
  if (_debug) {
    cout << "DIAGNOSTIC" << endl;
    for (int i= 0; i < total_objects; i++) {
      cout << " i = " << i << endl;
      cout << "Multijets L3 probability T10 = " << prob_t10[i] << endl;
      cout << "Multijets L3 probability T12 = " << prob_t12[i] << endl;
      cout << "Multijets L3 probability T15 = " << prob_t15[i] << endl;
      cout << "Multijets L3 probability T20 = " << prob_t20[i] << endl;
      cout << "Multijets L3 probability T25 = " << prob_t25[i] << endl;
    }
  }
  
  //------------------------------------
  // P(not) = Sum(jets) ( 1 - P(jet) )
  //------------------------------------
  
  double Pjet;
  if (_debug) cout << "I have version " << version << endl;
  if (version=="v13a" || version=="v13b" || version=="v14") {   // JET(2,25)JET(3,15)JET(4,12)JET(5,10)  only applicable upto v13.3 trigger list.
    
    // The actual trigger encoded is JET(1,25)JET(2,25)JET(3,15)JET(4,12)JET(5,10)
    if (total_objects<5) {  // Do not execute the code if the number of jets is smaller than the numbers needed to satisfy the trigger.
      Pjet = 0.0;
      return Pjet;
    }
    double P0 = 1.0;
    double P1 = 0.0;
    double P2 = 0.0;
    double P3 = 0.0;
    double P4 = 0.0;
        
    // Calculation that none of the jets are above the threshold of 25 GeV.
    for (int i = 0; i < total_objects; i++) 
      P0 *= 1 - prob_t25[i];
    
    // Calculation that at most one of the jets is above the threshold of 25 GeV and no other jets above 25 GeV.
    double P1_factor_1;
    double P1_factor_2;
    for (int i = 0; i < total_objects; i++) {
      P1_factor_1 = prob_t25[i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t25[j];
      P1 += P1_factor_1 * P1_factor_2;
    }
    
    // Calculation that two of the jets are above the threshold of 25 GeV and no other jets are above 15 GeV.
    double P2_20, P2_11;
    double P2_factor_1;
    double P2_factor_2;
    double P2_factor_3;
    double P2_factor_4;
    P2_20 = 0.0;
    P2_11 = 0.0;
    for (int i = 0; i < total_objects; i++) {
      P2_factor_1 = prob_t25[i];
      P2_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P2_factor_3 = prob_t25[j];
	  P2_factor_4 = 1.0;
	  for (int k = 0; k < total_objects; k++)
	    if (k!=i && k!=j) P2_factor_4 *= 1 - prob_t15[k];
	  P2_factor_2 += P2_factor_3 * P2_factor_4;
	}
      }
      P2_20 += P2_factor_1 * P2_factor_2;
    }
    P2 = P2_20 + P2_11;
    
    // Calculation that at most two of the jets are above the threshold of 25 GeV, one additional jet above 15 GeV, and no other
    // jets are above 12 GeV.
    double P3_300, P3_210, P3_201, P3_120, P3_111;
    double P3_factor_1;
    double P3_factor_2;
    double P3_factor_3;
    double P3_factor_4;
    double P3_factor_5;
    double P3_factor_6;
    P3_300 = 0.0;
    P3_210 = 0.0;
    P3_201 = 0.0;
    P3_120 = 0.0;
    P3_111 = 0.0;
    // This loop is the first three jets above 25 GeV.
    for (int i = 0; i < total_objects; i++) {
      P3_factor_1 = prob_t25[i];
      P3_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P3_factor_3 = prob_t25[j];
	  P3_factor_4 = 0.0;
	  for (int k = j+1; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P3_factor_5 = prob_t25[k];
	      P3_factor_6 = 1.0;
	      for (int l = 0; l < total_objects; l++) 
		if (l!=i && l!=j && l!=k) P3_factor_6 *= 1 - prob_t12[l];
	      P3_factor_4 += P3_factor_5 * P3_factor_6;
	    }
	  }
	  P3_factor_2 += P3_factor_3 * P3_factor_4;
	}
      }
      P3_300 += P3_factor_1 * P3_factor_2;
    }
    // This loop is the first two above 25, but the third between 15 and 25.
    for (int i = 0; i < total_objects; i++) {
      P3_factor_1 = prob_t25[i];
      P3_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P3_factor_3 = prob_t25[j];
	  P3_factor_4 = 0.0;
	  for (int k = 0; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P3_factor_5 = prob_t15[k] - prob_t25[k];
	      P3_factor_6 = 1.0;
	      for (int l = 0; l < total_objects; l++) 
		if (l!=i && l!=j && l!=k) P3_factor_6 *= 1 - prob_t12[l];
	      P3_factor_4 += P3_factor_5 * P3_factor_6;
	    }
	  }
	  P3_factor_2 += P3_factor_3 * P3_factor_4;
	}
      }
      P3_201 += P3_factor_1 * P3_factor_2;
    }
    P3 = P3_300 + P3_210 + P3_201 + P3_120 + P3_111;

    // Calculation that at most two of the jets are above the threshold of 25 GeV, one additional jet above 15 GeV, one additional
    // jets above 12, and no other jets above 10 GeV.
    double P4_4000;
    double P4_3100, P4_3010, P4_3001;
    double P4_2200, P4_2110, P4_2101, P4_2020, P4_2011;
    double P4_1300, P4_1210, P4_1201, P4_1120, P4_1111;
    P4_4000 = 0.0;
    P4_3100 = 0.0;
    P4_3010 = 0.0;
    P4_3001 = 0.0;
    P4_2200 = 0.0;
    P4_2110 = 0.0;
    P4_2101 = 0.0;
    P4_2020 = 0.0;
    P4_2011 = 0.0;
    P4_1300 = 0.0;
    P4_1210 = 0.0;
    P4_1201 = 0.0;
    P4_1120 = 0.0;
    P4_1111 = 0.0;

    double P4_factor_1;
    double P4_factor_2;
    double P4_factor_3;
    double P4_factor_4;
    double P4_factor_5;
    double P4_factor_6;
    double P4_factor_7;
    double P4_factor_8;
    // First four jets above 25 GeV.
    for (int i = 0; i < total_objects; i++) {
      P4_factor_1 = prob_t25[i];
      P4_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P4_factor_3 = prob_t25[j];
	  P4_factor_4 = 0.0;
	  for (int k = j+1; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P4_factor_5 = prob_t25[k];
	      P4_factor_6 = 0.0;
	      for (int l = k+1; l < total_objects; l++) {
		if (l!=i && l!=j && l!=k) {
		  P4_factor_7 = prob_t25[l];
		  P4_factor_8 = 1.0;
	          for (int m = 0; m < total_objects; m++) 
		    if (m!=i && m!=j && m!=k && m!=l) P4_factor_8 *= 1 - prob_t10[m];
		  P4_factor_6 += P4_factor_7 * P4_factor_8;
		}
	      }
	      P4_factor_4 += P4_factor_5 * P4_factor_6;
	    }
	  }
	  P4_factor_2 += P4_factor_3 * P4_factor_4;
	}
      }
      P4_4000 += P4_factor_1 * P4_factor_2;
    }
    // First three above jets above 25 GeV, the fourth jet between 15 and 25.
    for (int i = 0; i < total_objects; i++) {
      P4_factor_1 = prob_t25[i];
      P4_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P4_factor_3 = prob_t25[j];
	  P4_factor_4 = 0.0;
	  for (int k = j+1; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P4_factor_5 = prob_t25[k];
	      P4_factor_6 = 0.0;
	      for (int l = 0; l < total_objects; l++) {
		if (l!=i && l!=j && l!=k) {
		  P4_factor_7 = prob_t15[l] - prob_t25[l];
		  P4_factor_8 = 1.0;
	          for (int m = 0; m < total_objects; m++) 
		    if (m!=i && m!=j && m!=k && m!=l) P4_factor_8 *= 1 - prob_t10[m];
		  P4_factor_6 += P4_factor_7 * P4_factor_8;
		}
	      }
	      P4_factor_4 += P4_factor_5 * P4_factor_6;
	    }
	  }
	  P4_factor_2 += P4_factor_3 * P4_factor_4;
	}
      }
      P4_3010 += P4_factor_1 * P4_factor_2;
    }
    // First three above jets above 25 GeV, the fourth jet between 12 and 15.
    for (int i = 0; i < total_objects; i++) {
      P4_factor_1 = prob_t25[i];
      P4_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P4_factor_3 = prob_t25[j];
	  P4_factor_4 = 0.0;
	  for (int k = j+1; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P4_factor_5 = prob_t25[k];
	      P4_factor_6 = 0.0;
	      for (int l = 0; l < total_objects; l++) {
		if (l!=i && l!=j && l!=k) {
		  P4_factor_7 = prob_t12[l] - prob_t15[l];
		  P4_factor_8 = 1.0;
	          for (int m = 0; m < total_objects; m++) 
		    if (m!=i && m!=j && m!=k && m!=l) P4_factor_8 *= 1 - prob_t10[m];
		  P4_factor_6 += P4_factor_7 * P4_factor_8;
		}
	      }
	      P4_factor_4 += P4_factor_5 * P4_factor_6;
	    }
	  }
	  P4_factor_2 += P4_factor_3 * P4_factor_4;
	}
      }
      P4_3001 += P4_factor_1 * P4_factor_2;
    }
    // First two above jets above 25 GeV, third jet and fourth between 15 and 25
    for (int i = 0; i < total_objects; i++) {
      P4_factor_1 = prob_t25[i];
      P4_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P4_factor_3 = prob_t25[j];
	  P4_factor_4 = 0.0;
	  for (int k = 0; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P4_factor_5 = prob_t15[k] - prob_t25[k];
	      P4_factor_6 = 0.0;
	      for (int l = k+1; l < total_objects; l++) {
		if (l!=i && l!=j && l!=k) {
		  P4_factor_7 = prob_t15[l] - prob_t25[l];
		  P4_factor_8 = 1.0;
	          for (int m = 0; m < total_objects; m++) 
		    if (m!=i && m!=j && m!=k && m!=l) P4_factor_8 *= 1 - prob_t10[m];
		  P4_factor_6 += P4_factor_7 * P4_factor_8;
		}
	      }
	      P4_factor_4 += P4_factor_5 * P4_factor_6;
	    }
	  }
	  P4_factor_2 += P4_factor_3 * P4_factor_4;
	}
      }
      P4_2020 += P4_factor_1 * P4_factor_2;
    }
    // First two above jets above 25 GeV, third jet between 15 and 25, the fourth jet between 12 and 15.
    for (int i = 0; i < total_objects; i++) {
      P4_factor_1 = prob_t25[i];
      P4_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P4_factor_3 = prob_t25[j];
	  P4_factor_4 = 0.0;
	  for (int k = 0; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P4_factor_5 = prob_t15[k] - prob_t25[k];
	      P4_factor_6 = 0.0;
	      for (int l = 0; l < total_objects; l++) {
		if (l!=i && l!=j && l!=k) {
		  P4_factor_7 = prob_t12[l] - prob_t15[l];
		  P4_factor_8 = 1.0;
	          for (int m = 0; m < total_objects; m++) 
		    if (m!=i && m!=j && m!=k && m!=l) P4_factor_8 *= 1 - prob_t10[m];
		  P4_factor_6 += P4_factor_7 * P4_factor_8;
		}
	      }
	      P4_factor_4 += P4_factor_5 * P4_factor_6;
	    }
	  }
	  P4_factor_2 += P4_factor_3 * P4_factor_4;
	}
      }
      P4_2011 += P4_factor_1 * P4_factor_2;
    }
    P4 = P4_4000 + P4_3100 + P4_3010 + P4_3001 + P4_2200 + P4_2110 + P4_2101 + P4_2020 + P4_2011 + P4_1300 + P4_1210 + P4_1201 + P4_1120 + P4_1111;
    
    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0 - P1 - P2 - P3 - P4;
    //std::cout << "Calculating v13. P0 = " << P0 << "  P1 = " << P1 << "  P2 = " << P2 << "  P3 = " << P3 << "  P4 = " << P4 << std::endl; 
    
  }
  else if (version=="v12") {   // JET(2,25)JET(3,15)JET(4,12)
    if (total_objects<4) {  // Do not execute the code if the number of jets is smaller than the numbers needed to satisfy the trigger.
      Pjet = 0.0;
      return Pjet;
    }

    // The actual trigger encoded is JET(1,25)JET(2,25)JET(3,15)JET(4,12)
    double P0 = 1.0;
    double P1 = 0.0;
    double P2 = 0.0;
    double P3 = 0.0;

    // Calculation that none of the jets are above the threshold of 25 GeV.
    for (int i = 0; i < total_objects; i++) 
      P0 *= 1 - prob_t25[i];

    // Calculation that at most one of the jets is above the threshold of 25 GeV and no other jets above 25 GeV.
    double P1_factor_1;
    double P1_factor_2;
    for (int i = 0; i < total_objects; i++) {
      P1_factor_1 = prob_t25[i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t25[j];
      P1 += P1_factor_1 * P1_factor_2;
    }

    // Calculation that two of the jets are above the threshold of 25 GeV and no other jets are above 15 GeV.
    double P2_20, P2_11;
    double P2_factor_1;
    double P2_factor_2;
    double P2_factor_3;
    double P2_factor_4;
    P2_20 = 0.0;
    P2_11 = 0.0;
    for (int i = 0; i < total_objects; i++) {
      P2_factor_1 = prob_t25[i];
      P2_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P2_factor_3 = prob_t25[j];
	  P2_factor_4 = 1.0;
	  for (int k = 0; k < total_objects; k++)
	    if (k!=i && k!=j) P2_factor_4 *= 1 - prob_t15[k];
	  P2_factor_2 += P2_factor_3 * P2_factor_4;
	}
      }
      P2_20 += P2_factor_1 * P2_factor_2;
    }
    P2 = P2_20 + P2_11;

    // Calculation that at most two of the jets are above the threshold of 25 GeV, one additional jet above 15 GeV, and no other
    // jets are above 12 GeV.
    double P3_300, P3_210, P3_201, P3_120, P3_111;
    double P3_factor_1;
    double P3_factor_2;
    double P3_factor_3;
    double P3_factor_4;
    double P3_factor_5;
    double P3_factor_6;
    P3_300 = 0.0;
    P3_210 = 0.0;
    P3_201 = 0.0;
    P3_120 = 0.0;
    P3_111 = 0.0;
    // This loop is the first three jets above 25 GeV.
    for (int i = 0; i < total_objects; i++) {
      P3_factor_1 = prob_t25[i];
      P3_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P3_factor_3 = prob_t25[j];
	  P3_factor_4 = 0.0;
	  for (int k = j+1; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P3_factor_5 = prob_t25[k];
	      P3_factor_6 = 1.0;
	      for (int l = 0; l < total_objects; l++) 
		if (l!=i && l!=j && l!=k) P3_factor_6 *= 1 - prob_t12[l];
	      P3_factor_4 += P3_factor_5 * P3_factor_6;
	    }
	  }
	  P3_factor_2 += P3_factor_3 * P3_factor_4;
	}
      }
      P3_300 += P3_factor_1 * P3_factor_2;
    }
    // This loop is the first two above 25, but the third between 15 and 25.
    for (int i = 0; i < total_objects; i++) {
      P3_factor_1 = prob_t25[i];
      P3_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P3_factor_3 = prob_t25[j];
	  P3_factor_4 = 0.0;
	  for (int k = 0; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P3_factor_5 = prob_t15[k] - prob_t25[k];
	      P3_factor_6 = 1.0;
	      for (int l = 0; l < total_objects; l++) 
		if (l!=i && l!=j && l!=k) P3_factor_6 *= 1 - prob_t12[l];
	      P3_factor_4 += P3_factor_5 * P3_factor_6;
	    }
	  }
	  P3_factor_2 += P3_factor_3 * P3_factor_4;
	}
      }
      P3_201 += P3_factor_1 * P3_factor_2;
    }
    P3 = P3_300 + P3_210 + P3_201 + P3_120 + P3_111;
    
    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0 - P1 - P2 - P3;
  }
  else if (version=="v11" || version=="v10" || version=="v9") {  // JET(2,20)JET(4,10)
    if (total_objects<4) {  // Do not execute the code if the number of jets is smaller than the numbers needed to satisfy the trigger.
      Pjet = 0.0;
      return Pjet;
    }

    // The actual trigger encoded is JET(1,20)JET(2,20)JET(3,10)JET(4,10)
    double P0 = 1.0;
    double P1 = 0.0;
    double P2 = 0.0;
    double P3 = 0.0;

    // Calculation that none of the jets are above the threshold of 20 GeV.
    for (int i = 0; i < total_objects; i++) 
      P0 *= 1 - prob_t20[i];

    // Calculation that at most one of the jets is above the threshold of 20 GeV and no other jets above 20 GeV.
    double P1_factor_1;
    double P1_factor_2;
    for (int i = 0; i < total_objects; i++) {
      P1_factor_1 = prob_t20[i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t20[j];
      P1 += P1_factor_1 * P1_factor_2;
    }

    // Calculation that two of the jets are above the threshold of 20 GeV and no other jets are above 10 GeV.
    double P2_20, P2_11;
    double P2_factor_1;
    double P2_factor_2;
    double P2_factor_3;
    double P2_factor_4;
    P2_20 = 0.0;
    P2_11 = 0.0;
    for (int i = 0; i < total_objects; i++) {
      P2_factor_1 = prob_t20[i];
      P2_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P2_factor_3 = prob_t20[j];
	  P2_factor_4 = 1.0;
	  for (int k = 0; k < total_objects; k++)
	    if (k!=i && k!=j) P2_factor_4 *= 1 - prob_t10[k];
	  P2_factor_2 += P2_factor_3 * P2_factor_4;
	}
      }
      P2_20 += P2_factor_1 * P2_factor_2;
    }
    P2 = P2_20 + P2_11;

    // Calculation that at most two of the jets are above the threshold of 20 GeV, one additional jet above 10 GeV, and no other
    // jets are above 10 GeV.
    double P3_300, P3_210, P3_201, P3_120, P3_111;
    double P3_factor_1;
    double P3_factor_2;
    double P3_factor_3;
    double P3_factor_4;
    double P3_factor_5;
    double P3_factor_6;
    P3_300 = 0.0;
    P3_210 = 0.0;
    P3_201 = 0.0;
    P3_120 = 0.0;
    P3_111 = 0.0;
    // This loop is the first three jets above 20 GeV.
    for (int i = 0; i < total_objects; i++) {
      P3_factor_1 = prob_t20[i];
      P3_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P3_factor_3 = prob_t20[j];
	  P3_factor_4 = 0.0;
	  for (int k = j+1; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P3_factor_5 = prob_t20[k];
	      P3_factor_6 = 1.0;
	      for (int l = 0; l < total_objects; l++) 
		if (l!=i && l!=j && l!=k) P3_factor_6 *= 1 - prob_t10[l];
	      P3_factor_4 += P3_factor_5 * P3_factor_6;
	    }
	  }
	  P3_factor_2 += P3_factor_3 * P3_factor_4;
	}
      }
      P3_300 += P3_factor_1 * P3_factor_2;
    }
    // This loop is the first two above 20, but the third between 10 and 20.
    for (int i = 0; i < total_objects; i++) {
      P3_factor_1 = prob_t20[i];
      P3_factor_2 = 0.0;
      for (int j = i+1; j < total_objects; j++) {
	if (j!=i) {
	  P3_factor_3 = prob_t20[j];
	  P3_factor_4 = 0.0;
	  for (int k = 0; k < total_objects; k++) {
	    if (k!=i && k!=j) {
	      P3_factor_5 = prob_t10[k] - prob_t20[k];
	      P3_factor_6 = 1.0;
	      for (int l = 0; l < total_objects; l++) 
		if (l!=i && l!=j && l!=k) P3_factor_6 *= 1 - prob_t10[l];
	      P3_factor_4 += P3_factor_5 * P3_factor_6;
	    }
	  }
	  P3_factor_2 += P3_factor_3 * P3_factor_4;
	}
      }
      P3_201 += P3_factor_1 * P3_factor_2;
    }
    P3 = P3_300 + P3_210 + P3_201 + P3_120 + P3_111;
    
    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0 - P1 - P2 - P3;

  }
  else if (version=="v8") {   // JET(4,10)
    if (total_objects<4) {  // Do not execute the code if the number of jets is smaller than the numbers needed to satisfy the trigger.
      Pjet = 0.0;
      return Pjet;
    }
    // LSC: The trigger for the version 8 trigger list only requires four jets
    // above 10 GeV, so calling the method P_4_object will give the correct
    // probability. 

    // Pjet = P_4_object(version,"L3","JET","JET(1,10)_alljets",JET);
  }


  //------------------------------------
  // We've calculate the P(no) and we need P
  //------------------------------------
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

ClassImp(Probability_TopAllJets_L3)


