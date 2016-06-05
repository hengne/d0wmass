//----------------------------------------------------------
//Author:   Thomas Gadfort (tgadfort@fnal.gov)
//          Len Christofek (leonard@fnal.gov)
//
//Last Updated: 5/19/06
//
//Purpose:  Calculates the probability a set of jet to
//          passes the top multijets level1 trigger condition
//----------------------------------------------------------

//Header file for this class
#include "caf_trigger/Probability_TopAllJets_L2.hpp"

using namespace std;

Probability_TopAllJets_L2::Probability_TopAllJets_L2(const char *name)
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
  _flags.push_back("ObjRelativeTo");
  _flags.push_back("ObjType");
  _flags.push_back("Source");
  _flags.push_back("AddToEffUtils");

  _object.push_back("Multijet");

  _location.push_back("_INC");
  _location.push_back("_CC");
  _location.push_back("_EC");
  _location.push_back("_ICD");

  _level = "Level2";

  
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
	
	std::string add_to_eff_utils;
	
	for ( int j = 0; j < _flags.size(); j++ ) {
	  std::string flag = _flags[j];

	  std::stringstream flag_name;
	  flag_name << _level << object << flag << "_" << version << detector;
	  
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

  //------------------------------------
  // The sigma calculations. False by default
  //------------------------------------
  _sigma = config.get("sigma", "false");
  
}
    
//EffInfo terms are defined here
void Probability_TopAllJets_L2::defineEffInfo(std::map< std::string, eff_utils::EffInfo >& _effInfo)
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

	std::stringstream do_name;
	do_name << _level << object << "AddToEffUtils_" << version << detector;
	if ( _trigger_map[do_name.str()][0] == "yes" ) {
	  std::stringstream effInfoName;
	  effInfoName << _level << object << "_" << version << detector;
	  //	  cout << "Going to store infomration : " << effInfoName.str() << endl;
	  
	  for ( int j = 0; j < _flags.size(); j++ ) {
	    std::string flag = _flags[j];
	    
	    std::stringstream flag_name;
	    flag_name << _level << object << flag << "_" << version << detector;
	    std::vector<std::string> eff_utils_variable = _trigger_map[flag_name.str()];
	    
	    
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


//--------------------------------------
// The actual probability calculations are defined here and after calcProb
//--------------------------------------
double Probability_TopAllJets_L2::calcProb(std::string version)
{
  //------------------------------------
  // This sets up the channel name and is important to set!
  // This is the value specified to combine in the config file
  //------------------------------------
  _channel = "TopAllJets_L2";
    
  double probability = Prob_TopAllJets_L2(version);

  return probability;

}

//------------------------------------------------------------------------------
// This calculates the l2 probability
// P_L2(electron,jet) = P_L2(electron) * P_L2(jet)
//------------------------------------------------------------------------------
double Probability_TopAllJets_L2::Prob_TopAllJets_L2(std::string version)
{

  double probability = ( Prob_TopAllJets_Jet_L2(version) *
			 Prob_TopAllJets_Jet_HT(version) );

  if ( _debug ) {
    cout << "AllJets L2 probability = " << probability << endl;
  }

  return probability;
}


//------------------------------------------------------------------------------
// This calculates the jet l2 probability
//------------------------------------------------------------------------------
double Probability_TopAllJets_L2::Prob_TopAllJets_Jet_L2(std::string version){

  std::string object = "Jet";
  
  bool valid = false;
  for ( int i = 0; i < _location.size(); i++ ) {
    std::string detector = _location[i];
    std::stringstream do_name; 
    do_name << _level << object << "AddToEffUtils_" << version << detector;
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

  //------------------------------------
  // Loop over all jets to get L2 probability
  //------------------------------------
  for(int iobj = 0; iobj < NJET; ++iobj) {
    std::stringstream effInfoName;
    double detector_eta = TMath::Abs(JET[iobj].detEta()) / 10;

    if ( _split_jet ) {
      if ( detector_eta <= 0.8 ) {
	effInfoName << _level << object << "_" << version << "_CC";
      }
      else if ( detector_eta < 1.5 && detector_eta > 0.8 ) {
	effInfoName << _level << object << "_" << version << "_ICD";
      }
      else if ( detector_eta >= 1.5 ) {
	effInfoName << _level << object << "_" << version << "_EC";
      }
    }
    else {
      effInfoName << _level << object << "_" << version << "_INC";
    }
    
    const objectProbabilities *prob = probObject(effInfoName.str().c_str());
    if ( prob == 0 ) {
      cout << endl;
      cout << "Could not find the effInfo information" << endl;
      cout << "You gave: " << effInfoName.str() << endl;
      exit(1);
    }

    double sig = 0.0;
    float val = prob->getProbability(JET[iobj], sig, isRun2b, _debug);
    probArray.push_back( val );
  }

  //------------------------------------
  // P(not) = Sum(jets) ( 1 - P(jet) )
  //------------------------------------
  int length = probArray.size();
  if (length<3) return 0.0;
  double prob;
  
  if (version=="v14" || version=="v13") {
    // P1
    double P1 = 1.0;
    for (int iobj=0; iobj<length; iobj++){
      P1 *= (1.- probArray[iobj]);
    }
    // P2
    double P2 = 0.0;
    for (int iobj=0; iobj<length; iobj++){
      double Pt1 = probArray[iobj];   
      double Pt2 = 1.;
      for (int jobj=0; jobj<length; jobj++){
	if (iobj!=jobj) {
	  Pt2 *= (1.- probArray[jobj]);
	}
      }
      P2 += Pt1 * Pt2;
    }
    // P3
    double P3 = 0.0;
    for (int iobj=0; iobj<length; iobj++){
      double Pt1 = probArray[iobj];
      double Ps1 = 0.0;
      for (int jobj=iobj+1; jobj<length; jobj++){
	if (iobj!=jobj) {
	  double Pt2 = probArray[jobj];
	  double Pt3 = 1.0;
	  for (int kobj=0; kobj<length; kobj++){	  
	    if (kobj!=iobj && kobj!=jobj) {
	      Pt3 *= (1.0 - probArray[kobj]);
	    }
	  }
	  Ps1 += Pt2*Pt3;
	}
      }
      P3 += Pt1*Ps1;
    }
    double prob = 1.0 - P1 - P2 - P3;
  } else {
    prob = 1.0;
  }

  double probCalc;
  probCalc = prob;
  
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


//------------------------------------------------------------------------------
// This calculates the probability for the set of jets to pass the HT requirement
//------------------------------------------------------------------------------
double Probability_TopAllJets_L2::Prob_TopAllJets_Jet_HT(std::string version){

  std::string object = "Jet";
  
  bool valid = false;

  if ( valid == false ) { return( 1.0 ); }

  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  std::vector<double> probArray;

  //------------------------------------
  // Loop over all jets to get L2 probability
  //------------------------------------
  double Ht = 0.0;
  for(int iobj = 0; iobj < NJET; ++iobj) {
    //    Ht += Jet[iobj].Pt(); 
      //    const objectProbabilities *prob = probObject(effInfoName.str().c_str());
      //    if ( prob == 0 ) {
      //      cout << endl;
      //      cout << "Could not find the effInfo information" << endl;
      //      cout << "You gave: " << effInfoName.str() << endl;
      //      exit(1);
      //    }
  }

  //------------------------------------
  // P(not) = Sum(jets) ( 1 - P(jet) )
  //------------------------------------

  double tmpProb = 1.0;

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
    cout << _channel << " Jet HT Probability = " << probCalc << endl;
  }

  double probability;
  probability = probCalc;
  
  return probability;
}

ClassImp(Probability_TopAllJets_L2)


