//----------------------------------------------------------
// Author:   Robert Wagner (rewagner@fnal.gov)
// Based on Probability_Ejets written by:
//           Thomas Gadfort (tgadfort@fnal.gov)
//           Len Christofek (leonard@fnal.gov)
// And Probability_nEM by:
//           Mark Owen (markowen@fnal.gov)
//
// History:
// Jun 2008:   Added support for v15 postshutdown (Liang Li)
// Dec 2007:   Implemented Run2b switch, backward compatibility (Liang Li & Robert Wagner)
// Nov 2007:   Initial release
// Nov 2010:   Multi-epoch processing - MB
//
//
//
// Purpose:  Calculates the probability an electron+jet of a certain quality
//           to pass the an e+jets trigger OR single EM condition
//----------------------------------------------------------

//Header file for this class
#include "caf_trigger/Probability_EJets.hpp"
#include "eff_utils/EffVal.hpp"

using namespace std;

Probability_EJets::Probability_EJets(const char *name)
  : probProcessor(name)
{
  // We grab terms from the CAFe configuration file here
  cafe::Config config(name);
  
  //------------------------------------
  // This sets up the channel name and is important to set!
  // This is the value specified to combine in the config file
  //------------------------------------
  _channel = config.get("ChannelName", "EJets");

  
  //------------------------------------
  // Debug
  //------------------------------------
  std::string debug = config.get("Debug", "no");
  _debug = ( debug == "yes" );
  if (_debug) cout << endl << "Debugging for Probability_EJets is turned on." << endl << endl;

  //-----------------------------------------------
  // Electron quality - must match ElectronSelector
  //-----------------------------------------------
  _electron_quality = config.get("ElectronQuality","none");
  if(_electron_quality=="none") {
    cerr << ">>>>>>> " << name << " WARNING: No ElectronQuality specified, defaulting to top_tight" << endl;
    _electron_quality = "top_tight";
  }

  //------------------------------------
  // Jet_Quality
  //------------------------------------
  _jet_quality = config.get("JetQuality", "none");
  if ( _jet_quality == "none" ) {
    cout << ">>>>>>> " << name << " WARNING: No JetQuality parameter was found. Using loose jets as default." << endl;
    _jet_quality = "loose";
  }
  
  //------------------------------------
  // Split jets turn on curves
  //------------------------------------
  std::string split_jet = config.get("SplitJet", "yes");
  _split_jet = ( split_jet == "yes" );
  
  //------------------------------------
  // Ask if user wants to include the additional from electrons
  //------------------------------------
  std::string include_EM_shaping_L3 = config.get("IncludeEMShapingAtL3", "no");
  _includeEMshapingAtL3 = ( include_EM_shaping_L3 == "yes" );
  
  
  //------------------------------------
  // LSC:  I am making a patch for the systematic calculation.
  // Doing the calculation properly would require an interface
  // change.  The three values will be nominal, plus, minus
  // sigma.
  //------------------------------------
  _sigma = 0.0;
  _systematic = config.get("Systematic", "nominal");
  if (_systematic == "plus")    _sigma = +1.0;
  if (_systematic == "nominal") _sigma =  0.0;
  if (_systematic == "minus")   _sigma = -1.0;

  std::cout << "Probability Ejet systematics setting is " << _systematic << std::endl;
  std::cout << "The value of sigma is set to " << _sigma << std::endl << std::endl;

//   for (int i=0; i<_trigger_version.size(); i++) {
//     _and_is_greater[i] = 0;
//     _and_is_much_greater[i] = 0;
//   }

}

   
//EffInfo terms are defined here
void Probability_EJets::defineEffInfo(std::map< std::string, eff_utils::EffInfo >& _effInfo)
{

  if(_debug) cout<<"==>Probability_EJets::defineEffInfo(std::map< std::string, eff_utils::EffInfo >& _effInfo)"<<endl;

  //// Update the trigger map (must be defined in children classes)
  change_triggermap();

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
	    
	for ( int ml = 0; ml < _level.size(); ml++ ) {
	  std::string level = _level[ml];
	    
	  for ( int mt = 0; mt < _jetTrigType.size(); mt++ ) {
	    std:: string trigtype = _jetTrigType[mt];

	    std::stringstream do_name;
	    if ( _isRun2b ) {	    
		do_name << level << object << "AddToEffUtils_" << version << detector << "_T" << threshold << "_" << trigtype;
	    }
	    else {
		do_name << level << object << "AddToEffUtils_" << version << detector << "_T" << threshold;
	    }		  
	    if (_debug) std::cout << "Checking flag : " << do_name.str().c_str() << std::endl;
		    
	    if ( _trigger_map[do_name.str()][0] == "yes" ) {
	      std::stringstream effInfoName;
	      if ( _isRun2b ) {
		effInfoName << level << object << "_" << version << detector << "_T" << threshold << "_" << trigtype;
	      }
              else {
		effInfoName << level << object << "_" << version << detector << "_T" << threshold;
	      }	      
	      if (_debug) std::cout << "Going to store effInfo : " << effInfoName.str() << std::endl;
	    
	      for ( int j = 0; j < _flags.size(); j++ ) {
		std::string flag = _flags[j];
	      
		std::stringstream flag_name;
		if ( _isRun2b ) {      
			flag_name << level << object << flag << "_" << version << detector << "_T" << threshold << "_" << trigtype;
		}
		else {
			flag_name << level << object << flag << "_" << version << detector << "_T" << threshold;
		}	
		if (_debug) std::cout << "\tDefinition flag = " << flag_name.str().c_str() << std::endl;
		std::vector<std::string> eff_utils_variable = _trigger_map[flag_name.str()];
		if (_debug) std::cout << "\t\tSize = " << eff_utils_variable.size() << std::endl;	      
	      
		if ( flag == "EffName" ) {
                  if (_debug) std::cout << "\t\tEffName = " << eff_utils_variable[0].c_str() << std::endl;
		  _effInfo[effInfoName.str().c_str()].EffName(eff_utils_variable[0]);
		}
	      
		if ( flag == "EffVarNames" ) {
		  _effInfo[effInfoName.str().c_str()].EffVarNames(eff_utils_variable);
		}
 
		if ( flag == "EffType" ) {
		  _effInfo[effInfoName.str().c_str()].EffType(eff_utils_variable[0]);
		}
	      
		if ( flag == "EffVersion" ) {
		  if (_debug) std::cout << "\t\tEffVersion = " << atoi(eff_utils_variable[0].c_str()) << std::endl;
		  _effInfo[effInfoName.str().c_str()].EffVersion(atoi(eff_utils_variable[0].c_str()));
		}
	      
                /*
		if ( flag == "ObjVersion" ) {
		  if (_debug) std::cout << "ObjVersion = " << atoi(eff_utils_variable[0].c_str()) << std::endl;
		  _effInfo[effInfoName.str().c_str()].ObjVersion(atoi(eff_utils_variable[0].c_str()));
		}
	        */

		if ( flag == "ObjQuality" ) {
		  _effInfo[effInfoName.str().c_str()].ObjQuality(eff_utils_variable[0]);
		}
		
		if ( flag == "ObjRelativeTo" && object == "Jet" ) {
		  _effInfo[effInfoName.str().c_str()].ObjRelativeTo(eff_utils_variable[0].c_str());
		}
	      
		if ( flag == "TriggerVersion" ) {
                  if (_debug) std::cout << "\t\tTriggerVersion = " << eff_utils_variable[0].c_str() << std::endl;
		  _effInfo[effInfoName.str().c_str()].TriggerVersion(eff_utils_variable[0]);
		}
	      
		if ( flag == "ObjType" ) {
		  _effInfo[effInfoName.str().c_str()].ObjType(eff_utils_variable[0]);
		}

                if ( flag == "AddToEffUtils" ) {
                  if ( eff_utils_variable[0] != "yes" ) {
                        std::cout << "Probability_EJetsORSingleEMOR: " << name() << " ERROR: internal inconsistency, "
                        << flag_name.str() << " = " << eff_utils_variable[0].c_str() << " != yes " << std::endl;
                        exit(1);
                  }
                }

	      }
	    }
	  }
	}
	}
      }
    }
  }

  if(_debug) cout<<"Special trigger flags..."<<endl;

  // Needed for special trigger flags ("Group1" like)

  for ( int i = 0; i < _num_trigger_versions; i++ ) {
    string version = _trigger_version[i];
     
    for ( int mt = 0; mt <= _EMTrigType.size(); mt++ ) {
      string emType;	    
      if ( mt == _EMTrigType.size() ) {
	emType = "";
      } 
      else {
	emType = _EMTrigType[mt];
      }
    
      stringstream do_name;
      if ( emType != "" ) {
	do_name << "AddToEffUtils_" << emType << "_" << version;
      }
      else {
	do_name << "AddToEffUtils_" << version;
      }
      if(_debug) cout << "Checking flag : " << do_name.str().c_str() << endl;

      if ( _trigger_map[do_name.str()][0] == "yes" ) {
	stringstream effInfoName;
        if ( emType != "" ) {
		effInfoName  << emType << "_" << version;
	}
        else {
		effInfoName << version;
	}

	for ( int j = 0; j < _flags_EM.size(); j++ ) {
	  string flag = _flags_EM[j];
	  stringstream flag_name;
	  if ( emType != "" ) {      
		flag_name << flag << "_" << emType << "_" << version;
	  }
	  else {
		flag_name << flag << "_" << version;
	  }

          if (_debug) cout << "\tDefinition flag = " << flag_name.str().c_str() << endl;
	  vector<string> eff_utils_variable = _trigger_map[flag_name.str()];
          if (_debug) cout << "\t\tSize = " << eff_utils_variable.size() << endl;

	  //Don't set effInfo if there is no setting for a particular flag
	  if(eff_utils_variable.size()==0) {
	    //Print warning unless this is ObjRelative to - we dont
	    //use this for electrons at present (just QbjQuality)
	    if(flag!="ObjRelativeTo") cerr << "Probability_EJets: " << name() << ": WARNING efficiency"
					   << " flag " << flag_name.str().c_str()  << " is not specified" << endl;
	    continue;
	  }

	  if ( flag == "EffName" ) {
            if (_debug) cout << "\t\tEffName = " << eff_utils_variable[0].c_str() << endl;
	    _effInfo[effInfoName.str().c_str()].EffName(eff_utils_variable[0]);
	  } else if ( flag == "EffVarNames" ) {
	    _effInfo[effInfoName.str().c_str()].EffVarNames(eff_utils_variable);
	  } else if ( flag == "EffType" ) {
	    _effInfo[effInfoName.str().c_str()].EffType(eff_utils_variable[0]);
	  } else if( flag == "EffVersion" ) {
            if (_debug) cout << "\t\tEffVersion = " << eff_utils_variable[0].c_str() << endl;
	    _effInfo[effInfoName.str().c_str()].EffVersion(atoi(eff_utils_variable[0].c_str()));
	  } else if ( flag == "ObjQuality" ) {
	    _effInfo[effInfoName.str().c_str()].ObjQuality(eff_utils_variable[0]);
	  } else if ( flag == "ObjRelativeTo" ) {
	    _effInfo[effInfoName.str().c_str()].ObjRelativeTo(eff_utils_variable[0]);
	  } else if ( flag == "ObjType" ) {
	    _effInfo[effInfoName.str().c_str()].ObjType(eff_utils_variable[0]);
	  } else if ( flag == "AddToEffUtils" ) {
	    // exception
	  } else {
	    cout << "Probability_EJetsOR: " << name() << " ERROR: internal inconsistency. Ignoring "
		 << flag << endl;
	    exit(1);
	  }
	} // loop over flags
      } // Add to effutils
    }
  } // loop over trigger versions.

}


//--------------------------------------
// The actual probability calculations are defined here and after calcProb
//--------------------------------------
double Probability_EJets::calcProb(std::string version)
{

  double prob_e, prob_j, event_uncertainty;

//Check consistency
  if ( isRun2b != _isRun2b ) {
	cout << endl << "Error in Probability_EJets::calcProb :" << endl;
        cout << "Config file says isRun2b is " << _isRun2b << endl;
        cout << "Event says isRun2b is " << isRun2b << endl;
	exit(1);
  }

  if ( isRun2b ) {	  
	prob_e = Prob_Electron(version, "Group1");
	prob_j = Prob_Jet(version, "Group1");
  }
  else {
	prob_e = Prob_Electron(version, "");
	prob_j = Prob_Jet(version, "");
  }	  
  
  int iversion = -1;
  for (int i=0; i<_trigger_version.size(); i++) {
    if (_trigger_version[i] == version) iversion = i;
  }

  double probability =  prob_e*prob_j;

  if (probability > 1.) probability = 1.;
  if (probability < 0.) probability = 0.;

  if (_systematic == "nominal") {
    
     event_uncertainty = sqrt( prob_e * prob_e * _jet1_uncertainty * _jet1_uncertainty
				     + prob_j * prob_j * _ejet_uncertainty * _ejet_uncertainty );

     if (version.substr(0,2) == "16")  { _x12.push_back(probability); _s12.push_back(event_uncertainty); } 	  
     if (version == "15c")  { _x11.push_back(probability); _s11.push_back(event_uncertainty); } 
     if (version == "15b")  { _x10.push_back(probability); _s10.push_back(event_uncertainty); } 
     if (version == "15a") { _x9.push_back(probability); _s9.push_back(event_uncertainty); } 
     if (version == "14")  { _x8.push_back(probability); _s8.push_back(event_uncertainty); } 
     if (version == "13c") { _x7.push_back(probability); _s7.push_back(event_uncertainty); } 
     if (version == "13b") { _x6.push_back(probability); _s6.push_back(event_uncertainty); } 
     if (version == "13a") { _x5.push_back(probability); _s5.push_back(event_uncertainty); } 
     if (version == "12")  { _x4.push_back(probability); _s4.push_back(event_uncertainty); } 
     if (version == "11")  { _x3.push_back(probability); _s3.push_back(event_uncertainty); } 
     if (version == "10")  { _x2.push_back(probability); _s2.push_back(event_uncertainty); } 
     if (version == "09")  { _x1.push_back(probability); _s1.push_back(event_uncertainty); } 
     if (version == "08")  { _x0.push_back(probability); _s0.push_back(event_uncertainty); } 
  }

  if ( _debug ) {
    std::cout << "\tVersion: " << version << std::endl;
    std::cout << "\tProb EM of EJets: " << prob_e << std::endl;
    std::cout << "\tProb Jet of EJets: " << prob_j << std::endl;    
    std::cout << "\tErr of EM of EJets: " << _ejet_uncertainty << std::endl;
    std::cout << "\tErr of Jet of Ejets: " << _jet1_uncertainty << std::endl;
    std::cout << "\tEJets probability: " << probability << " +- " << event_uncertainty << std::endl << std::endl;
  }

  return probability;

}


//------------------------------------------------------------------------------
// The electron part of EJets probability calculator
//------------------------------------------------------------------------------
double Probability_EJets::Prob_Electron(string version, string emType) {

  if (_debug ) cout << "Probability_EJets::Prob_Electron Run2b = " << isRun2b << ", EMType = " << emType << endl;
	
  if ( emType != "" ) {
	  
	  map<string,map<int,EffVal> > weightvals;
	  
	  //Each electron can fire the trigger.
	  double emprobs[NEM];

	  for (int iobj=0; iobj<NEM; iobj++) {
	    // get probabilities (plus information required for uncertainty
	    // determination) for this Electron to pass the trigger.
	    pair< string, eff_utils::EffVal> weightstore;

						     
	    double prob = Prob_EM(version,iobj,weightstore,emType);
	    int &binno = weightstore.second.binno;
	    // store EffVal object
	    string eff_identifier=weightstore.first;
	    weightvals[eff_identifier][binno]=weightstore.second;

	    emprobs[iobj] = prob;

	    //Debug current status
	    if (_debug) {
	      cout << "Probability_EJets: Electron part of EJets " << iobj << ": " << emprobs[iobj] << endl;
	    }
	  } // loop over electrons

	  //In order for trigger not to fire all
	  //electrons must fail the trigger
	  double totalProbNotFire = 1.0;
	  for(int iobj=0; iobj<NEM; ++iobj) {
	    totalProbNotFire *= (1-emprobs[iobj]);
	    if(_debug) cout << "Probability_EJets: After electron " << iobj << " prob of not firing = " << totalProbNotFire << endl;
	  }
	  double totalProb = 1.0 - totalProbNotFire;
	  if (_debug) {
	    cout << "Probability_EJets: Electron part of EJets event probability = " << totalProb << endl;
	  }
	  
	  // LSC: Okay, let's calculate the error for just this part of the calculation.
	  double df_dp[10][2];
	  double P1_factor_2;
	  for (int i = 0; i < NEM; i++) { 
	    df_dp[i][0] = _uncertaintyArray[i]; 
	    //std::cout << "df_dp[0] " << i << " = " << df_dp[i][0] << std::endl;
	    P1_factor_2 = 1.0;
	    for (int j = 0; j < NEM; j++)
	      if (j!=i) P1_factor_2 *= 1 - emprobs[j];
	    df_dp[i][1] = P1_factor_2;
	    //std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
	  }
	  double tmpErr = 0.0;
	  for (int i = 0; i < NEM; i++) tmpErr += df_dp[i][0]*df_dp[i][0]*df_dp[i][1]*df_dp[i][1]; 
	  tmpErr = sqrt( tmpErr );
	  //std::cout << "Prob for electron is = " << probCalc << " +- " << tmpErr << std::endl;

	  _ejet_uncertainty = tmpErr;
	  return totalProb;
	  
  } // end of Run2b
  
  else {
	  
	  std::string object = "Electron";
	  bool valid = false;
	  for ( int i = 0; i < _location.size(); i++ ) {
	    std::string detector = _location[i];
	    std::stringstream do_name; 
	    do_name << "Level3" << object << "AddToEffUtils_" << version << detector << "_T15";
	    if ( _trigger_map[do_name.str()][0] == "yes" ) {
	      valid = true;
	    }
	  }
	  
	  if ( valid == false ) return( 1.0 ) ;
	  //------------------------------------
	  // We setup an array to simplify the code and check that the number
	  // of terms is valid
	  //------------------------------------
	  std::vector<double> probArray;
	  std::vector<double> uncertaintyArray;
	  double probJet;
	  double probEM;
	  //------------------------------------
	  // Loop over all electrons to get L3 probability
	  //------------------------------------
	  for(int iobj = 0; iobj < NEM; ++iobj) {
	    std::stringstream effInfoName;
	    double detector_eta = TMath::Abs(EM[iobj].CalDetectorEta());
	    std::string detector;

	    // LSC: Just use the inclusively name field.
	    effInfoName << "Level3" << object << "_" << version << "_INC" << "_T15";
	    
	    const objectProbabilities *prob = probObject(effInfoName.str().c_str());
	    if ( prob == 0 ) {
	      cout << endl;
	      cout << "Could not find the effInfo information" << endl;
	      cout << "You gave: " << effInfoName.str() << endl;
	      exit(1);
	    }

	    //std::cout << "E: The value of sigma is = " << _sigma << std::endl;
	    double uncertainty = 0.0;
	    if (_sigma == -1.0) uncertainty = -1.0;
	    if (_sigma ==  1.0) uncertainty =  1.0;
	    // If _sigma == 0, then we don't have to set the variable.
	    float val = prob->getProbability(EM[iobj], uncertainty, isRun2b, _debug);
	    //std::cout << "The uncertainty value return is = " << uncertainty << std::endl;

	    // LSC: Statistical error calculation for the probability
	    uncertaintyArray.push_back( uncertainty );

	    cout.precision(3);
	    if ( _debug ) cout << "Probability_EJets::Prob_Electron: Electron part of EJets\t" << version << "\t" << detector_eta << "\t" << EM[iobj].Pt() << "\t" << val << endl;
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


	  // LSC: Okay, let's calculate the error for just this part of the calculation.
	  double df_dp[10][2];
	  double P1_factor_2;
	  for (int i = 0; i < NEM; i++) { 
	    df_dp[i][0] = uncertaintyArray[i]; 
	    //std::cout << "df_dp[0] " << i << " = " << df_dp[i][0] << std::endl;
	    P1_factor_2 = 1.0;
	    for (int j = 0; j < NEM; j++)
	      if (j!=i) P1_factor_2 *= 1 - probArray[j];
	    df_dp[i][1] = P1_factor_2;
	    //std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
	  }
	  double tmpErr = 0.0;
	  for (int i = 0; i < NEM; i++) tmpErr += df_dp[i][0]*df_dp[i][0]*df_dp[i][1]*df_dp[i][1]; 
	  tmpErr = sqrt( tmpErr );
	  //std::cout << "Prob for electron is = " << probCalc << " +- " << tmpErr << std::endl;
	  _ejet_uncertainty = tmpErr;   
	  
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
	  
  }// end of Run2a	  
  
}

//------------------------------------
// Calculate Electron part of EJets trigger probability
//------------------------------------

double Probability_EJets::Prob_EM(string version, int iobj,
						   pair<string,eff_utils::EffVal> &weightstore,
						   string emType) {

  double probproduct=1;

  stringstream do_name; 
  if ( emType == "" ) {
	  do_name << "AddToEffUtils_" << version;
  }
  else {  
	do_name << "AddToEffUtils_" << emType << "_" << version;
  }
  
  bool eff_found = false;
  if ( _trigger_map[do_name.str()][0] == "yes" ) {
    
    eff_found = true;
    
    std::stringstream effInfoName;
    if ( emType != "" ) {
    	effInfoName << emType << "_" << version;
    }
    else {
	effInfoName << version;
    }

    const objectProbabilities *prob = probObject(effInfoName.str().c_str());

    if ( prob == 0 ) {
      cerr << endl;
      cerr << "Could not find the effInfo information" << endl;
      cerr << "You gave: " << effInfoName.str() << endl;
      exit(1);
    }

    double sig = 0.0;
    if (_sigma == -1.0) sig = -1.0;
    if (_sigma ==  1.0) sig =  1.0;
    EffVal eff;
    float val;
    val = prob->getProbability(EM[iobj], sig, eff, isRun2b, _debug);
    _uncertaintyArray.push_back( sig );
    if (_debug) {
      cout << "Probability_EJets::Prob_EM EM probability " << iobj << ": " << val << endl;
    }
    if (val<0) val=0;
    string eff_identifier = prob->Info()->ObjType()+"_"+emType+"_"
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
    cerr << "Probability_EJets::Prob_EM " << name() << " ERROR: EM  probability " << probproduct << endl;
    probproduct = 1.0;
  }
  else if(probproduct < 0.0) {
    cerr << "Probability_EJets::Prob_EM " <<name() << " ERROR: EM  probability " << probproduct << endl;
    probproduct = 0.0;
  }
  
  if (eff_found) 
    return probproduct;
  else
    return 0.;

} //Prob_EM_ejets


//------------------------------------------------------------------------------
// This calculates the jet l3 probability
//------------------------------------------------------------------------------
double Probability_EJets::Prob_Jet(std::string version, string trigtype){
  
  if ( _debug ) {
    cout << "Probability_EJets::Prob_Jet: EJets (Jets) version = " << version << ", TrigType = " << trigtype << endl;
  }
  
  /////////////////////////////////////////////////////////////////////
  // LSC: This part of the code finds and fills the arrays for the
  // jets.
  //////////////////////////////////////////////////////////////////////
  std::string object = "Jet";

  for (int ml=0; ml < _level.size(); ++ml) if (ml == 2 || version == "08" || version == "09" || version == "10" || version == "11") {
    std::string level = _level[ml];
    bool valid = false;
    for ( int i = 0; i < _location.size(); i++ ) {
      std::string detector = _location[i];
      for (int j=0; j < _threshold.size(); ++j) {
        std::string threshold = _threshold[j];
	std::stringstream do_name; 
	if ( trigtype != "" ) {      
		do_name << level << object << "AddToEffUtils_" << version << detector << "_T" << threshold << "_" << trigtype;
	}
	else {
		do_name << level << object << "AddToEffUtils_" << version << detector << "_T" << threshold;
	}	
	if (_debug) cout << "I am looking for trigger map " << do_name.str().c_str() << endl;
	if ( _trigger_map[do_name.str()][0] == "yes" ) {
	  valid = true;
	}
      }
    }
    if ( _debug ) cout << "Was the trigger map found ? " << valid << endl;
    if ( valid == false ) { return( 1.0 ); }
    if ( _debug )  std::cout << "\t\tJetValid: " << valid << std::endl;
  }
  

  //------------------------------------
  // We setup an array to simplify the code and check that the number
  // of terms is valid
  //------------------------------------
  
  double prob_t15[3][100], uncertainty_t15[3][100];
  double prob_t20[3][100], uncertainty_t20[3][100];
  double prob_t25[3][100], uncertainty_t25[3][100];
  double prob_t30[3][100], uncertainty_t30[3][100];
  
  if ( _debug ) {
    cout << "Number of jets = " << NJET << endl;
  }
  
  for(int iobj = 0; iobj < NJET; ++iobj) {
    
    if ( _debug ) {
      cout << "EJets (Jets) Jet number = " << iobj << "/" << NJET << endl;
    }
    
    for (int ml=0; ml < _level.size(); ++ml) {
      std::string level = _level[ml];
      for (int i=0; i < _threshold.size(); ++i) {
	
	bool valid = false;
	for ( int k = 0; k < _location.size(); k++ ) {
	  std::string detector = _location[k];
	  std::stringstream do_name; 
	  std::string threshold = _threshold[i];
	  if ( trigtype != "" ) {      
		do_name << level << object << "AddToEffUtils_" << version << detector << "_T" << threshold << "_" << trigtype;
	  }
	  else {
		do_name << level << object << "AddToEffUtils_" << version << detector << "_T" << threshold;
	  }
	  if ( _trigger_map[do_name.str()][0] == "yes" ) {
	    valid = true;
	  }
	}
	if (_debug) std::cout << "Is the trigger valid ? " << valid << std::endl;
	if (!valid) continue;
	
	std::stringstream effInfoName;
	std::string threshold = _threshold[i];
	if ( trigtype != "" ) {
		effInfoName << level << object << "_" << version << "_INC_T" << threshold << "_" << trigtype;
	}
	else {
		effInfoName << level << object << "_" << version << "_INC_T" << threshold ;
	}	
	if (_debug) std::cout << "Looking for parameterization : " << effInfoName.str().c_str() << std::endl;
	
	if (ml == 2 || version == "08" || version == "09" || version == "10" || version == "11") {
	  const objectProbabilities *prob = probObject(effInfoName.str().c_str());
	  if ( prob == 0 ) {
	    cout << endl;
	    cout << "Could not find the effInfo information" << endl;
	    cout << "You gave: " << effInfoName.str() << endl;
	    exit(1);
	  }

	  // LSC: This is the new interface to the uncertainty calculation.
	  //std::cout << "J: The value of sigma is = " << _sigma << std::endl;
	  double uncertainty = 0.0;
	  if (_sigma == -1.0) uncertainty = -1.0;
	  if (_sigma ==  1.0) uncertainty =  1.0;
	  // If _sigma == 0, then we don't have to set the variable.
	  float val = prob->getProbability(JET[iobj], uncertainty, JetActAs, isRun2b,_debug);
	  //std::cout << "NJET The prob value return is = " << val << std::endl;
	  //std::cout << "NJET The uncertainty value return is = " << uncertainty << std::endl;


	  cout.precision(3);
	  if ( _debug ) cout << "L3Jet\t" << version << "\t" << JET[iobj].Pt() << "\t" << val << endl;
	  
	  // LSC: Fill in the arrays for the probability calculation.
	  if (threshold == "15") { prob_t15[ml][iobj] = val; uncertainty_t15[ml][iobj] = uncertainty; }
	  if (threshold == "20") { prob_t20[ml][iobj] = val; uncertainty_t20[ml][iobj] = uncertainty; }
	  if (threshold == "25") { prob_t25[ml][iobj] = val; uncertainty_t25[ml][iobj] = uncertainty; }
	  if (threshold == "30") { prob_t30[ml][iobj] = val; uncertainty_t30[ml][iobj] = uncertainty; }
	  if ( _debug ) {
	    if (threshold == "15") cout << "\tEJets (Jets) " << version << " " << level << " probability T15 = " << prob_t15[ml][iobj] << endl;
	    if (threshold == "20") cout << "\tEJets (Jets) " << version << " " << level << " probability T20 = " << prob_t20[ml][iobj] << endl;
	    if (threshold == "25") cout << "\tEJets (Jets) " << version << " " << level << " probability T25 = " << prob_t25[ml][iobj] << endl;
	    if (threshold == "30") cout << "\tEJets (Jets) " << version << " " << level << " probability T30 = " << prob_t30[ml][iobj] << endl;
	  }
	}
      }
    }
  }
  int total_objects = NJET;


  //////////////////////////////////////////////////////////////////////
  // LSC: This part of the code finds and fills the electron
  // into the appropiate arrays.
  //////////////////////////////////////////////////////////////////////
  object = "Electron";

  bool valid = false;
  for ( int i = 0; i < _location.size(); i++ ) {
    std::string detector = _location[i];
    for (int j=0; j < _threshold.size(); ++j) {
      std::stringstream do_name; 
      std::string threshold = _threshold[j];
      if ( version != "08" && version != "09" && version != "10" && version != "11"  ) {
	if ( trigtype != "" ) {		
		do_name << "Level3" << object << "AddToEffUtils_" << version << detector << "_T" << threshold << "_" << trigtype;
	}
	else {
		do_name << "Level3" << object << "AddToEffUtils_" << version << detector << "_T" << threshold;
	}	
	if (_debug) cout << "I am looking for trigger map " << do_name.str().c_str() << endl;
	if ( _trigger_map[do_name.str()][0] == "yes" ) {
	  valid = true;
	}
      }
      else valid = true;
    }
  }

  if ( _debug ) cout << "Was the EM trigger map found ? " << valid << endl;
  if ( valid == false ) { return( 1.0 ); }

  for(int iobj = 0; iobj < NEM; ++iobj) {
    double detector_eta = TMath::Abs(EM[iobj].CalDetectorEta());
    
    if ( _debug ) {
      cout << "EJets (Jets) electron number = " << iobj << "/" << NEM << endl;
    }
    
    for (int i=0; i < _threshold.size(); ++i) {
      
      std::string threshold = _threshold[i];
      bool valid = false;
      for ( int k = 0; k < _location.size(); k++ ) {
	std::string detector = _location[k];
	std::stringstream do_name; 
	if ( version != "08" && version != "09" && version != "10" && version != "11"  ) {
	  if ( trigtype != "" ) { 			    
		do_name << "Level3" << object << "AddToEffUtils_" << version << "_INC" << "_T" << threshold << "_" << trigtype;
	  }
	  else {
		do_name << "Level3" << object << "AddToEffUtils_" << version << "_INC" << "_T" << threshold ;
	  }		
	  if ( _trigger_map[do_name.str()][0] == "yes" ) {
	    valid = true;
	    if ( _debug) std::cout << "do name " << do_name.str() << std::endl;
	  }
	}
	else valid = true;
      }
      if ( _debug) std::cout << "Is the EM trigger valid ? " << valid << std::endl;
      if (!valid) continue;
      
      for ( int ml = 0; ml < _level.size(); ml++ ) {
	if (threshold == "15") { prob_t15[ml][total_objects + iobj] = 1.0; uncertainty_t15[ml][total_objects + iobj] = 0.0; }
	if (threshold == "20") { prob_t20[ml][total_objects + iobj] = 1.0; uncertainty_t20[ml][total_objects + iobj] = 0.0; }
	if (threshold == "25") { prob_t25[ml][total_objects + iobj] = 1.0; uncertainty_t25[ml][total_objects + iobj] = 0.0; }
	if (threshold == "30") { prob_t30[ml][total_objects + iobj] = 1.0; uncertainty_t30[ml][total_objects + iobj] = 0.0; }
      }
 
      std::stringstream effInfoName;
      if ( version != "08" && version != "09" && version != "10" && version != "11"  ) {
	if ( trigtype != "" ) {			  
		effInfoName << "Level3" << object << "_" << version << "_INC" << "_T" << threshold << "_" << trigtype;
	}
	else {
		effInfoName << "Level3" << object << "_" << version << "_INC" << "_T" << threshold;
	}	
	if (_debug) std::cout << "Looking for parameterization : " << effInfoName.str().c_str() << std::endl;
      
	const objectProbabilities *prob = probObject(effInfoName.str().c_str());
	if ( prob == 0 ) {
	  cout << endl;
	  cout << "Could not find the effInfo information" << endl;
	  cout << "You gave: " << effInfoName.str() << endl;
	  exit(1);
	}
	
	if (_includeEMshapingAtL3 && ( version != "08" && version != "09" && version != "10" && version != "11" ) ) {
	  if ( _debug) std::cout << "Looking for parameterization : " << effInfoName.str().c_str() << std::endl;	
	  if ( _debug) std::cout << "including shaping " << _threshold[i] << std::endl;


	  //std::cout << "EJ: The value of sigma is = " << _sigma << std::endl;
	  double uncertainty = 0.0;
	  if (_sigma == -1.0) uncertainty = -1.0;
	  if (_sigma ==  1.0) uncertainty =  1.0;
	  // If _sigma == 0, then we don't have to set the variable.
	  float val = prob->getProbability(EM[iobj], uncertainty, isRun2b,_debug);
	  //std::cout << "EM The uncertainty value return is = " << uncertainty << std::endl;

	  if ( _debug) cout.precision(3);
	  if ( _debug) cout << "L3EM Jet\t" << version << "\t" << detector_eta << "\t" << EM[iobj].Pt() << "\t" << val << endl;
	  
	  // LSC: Fill in the arrays for the probability calculation.
	  if (threshold == "15") { prob_t15[2][total_objects + iobj] = val; uncertainty_t15[2][total_objects + iobj] = uncertainty; }
	  if (threshold == "20") { prob_t20[2][total_objects + iobj] = val; uncertainty_t20[2][total_objects + iobj] = uncertainty; }
	  if (threshold == "25") { prob_t25[2][total_objects + iobj] = val; uncertainty_t25[2][total_objects + iobj] = uncertainty; }
	  if (threshold == "30") { prob_t30[2][total_objects + iobj] = val; uncertainty_t30[2][total_objects + iobj] = uncertainty; }
	}
	
	if ( _debug ) {
	  if (threshold == "15") cout << "\tEJets (Jets) L3EM probability T15 = " << prob_t15[2][total_objects + iobj] << endl;
	  if (threshold == "20") cout << "\tEJets (Jets) L3EM probability T20 = " << prob_t20[2][total_objects + iobj] << endl;
	  if (threshold == "25") cout << "\tEJets (Jets) L3EM probability T25 = " << prob_t25[2][total_objects + iobj] << endl;
	  if (threshold == "30") cout << "\tEJets (Jets) L3EM probability T30 = " << prob_t30[2][total_objects + iobj] << endl;
	}
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
      cout << "EJets (Jets) L3 probability T15 = " << prob_t15[2][i] << " +- " << uncertainty_t15[2][i] << std::endl;
      cout << "EJets (Jets) L3 probability T20 = " << prob_t20[2][i] << " +- " << uncertainty_t20[2][i] << std::endl;
      cout << "EJets (Jets) L3 probability T25 = " << prob_t25[2][i] << " +- " << uncertainty_t25[2][i] << std::endl;
      cout << "EJets (Jets) L3 probability T30 = " << prob_t30[2][i] << " +- " << uncertainty_t30[2][i] << std::endl;
    }
  }


  /////////////////////////////////////////////
  // Do the combinatorial calculation.
  /////////////////////////////////////////////

  double P0L3 = 1.0;
  double P1L3 = 0.0;
  double P0L2 = 1.0;
  double P0L1 = 1.0;

  double Pjet;
  double P1_factor_1;
  double P1_factor_2;

  if (_debug) cout << "I have version " << version << endl;

  if (version=="14") {
    
    // Calculation that none of the jets are above the threshold of 25 GeV.
    for (int i = 0; i < total_objects; i++){
      
      P0L3 *= 1 - prob_t25[2][i];
     
    }
    
    // Calculation that at most one of the jets is above the threshold of 25 GeV 
    // and no other jets above 20 GeV.
    for (int i = 0; i < total_objects; i++) {
      
      P1_factor_1 = prob_t25[2][i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
      P1L3 += P1_factor_1 * P1_factor_2;
      
    }
    
    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0L3 - P1L3;
    if ( _debug ) {
      cout << "\t\tv14 - P0L3: " << P0L3 << endl;
      cout << "\t\tv14 - P1L3: " << P1L3 << endl;
      cout << "\t\tv14 - Pjet: " << Pjet << endl;
      cout << "V14 EJets (Jets) L3 probability = " << Pjet << endl;
    }

    if (_systematic=="nominal") {
      // LSC:  Okay let's calculate the uncertainty for the v14 trigger probability.
      // I am calculating the derivatives here in the propogation error formula.    
      double df_dp[100][2];
      int num_of_terms = 2 * total_objects;
      for (int i = 0; i < total_objects; i++) {
	df_dp[i][0] = uncertainty_t25[2][i];
	df_dp[i+total_objects][0] = uncertainty_t20[2][i];
      }
      
      double P1_factor_1, P1_factor_2;
      // Uncertainty for P0L3 from P0L3
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t25[2][j];
	df_dp[i][1] = P1_factor_2;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty for P0L3 from term P1L3
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[i][0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
	df_dp[i][1] -= P1_factor_2;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty for P1L3 term from term P1L3
      for (int i = 0; i < total_objects; i++) {
	P1_factor_1 = 0.0; 
	//std::cout << "df_dp[i+total_objects][0] " << i+total_objects << " = " << df_dp[i+total_objects][0] << std::endl;
	for (int j = 0; j < total_objects; j++) {
	  if (j!=i) P1_factor_2 = prob_t25[2][j];
	  double P1_factor_3 = 1.0;
	  for (int k = 0; k< total_objects; k++) {
	    if ((k!=i)&&(k!=j)) P1_factor_3 *= 1 - prob_t20[2][k];
	  }
	  P1_factor_1 += P1_factor_2 * P1_factor_3;
	}
	df_dp[i+total_objects][1] = P1_factor_1;
	//std::cout << "df_dp[1] " << i+total_objects << " = " << df_dp[i+total_objects][1] << std::endl;
      }
      
      double tmpErr = 0.0;
      for (int i = 0; i < num_of_terms; i++) tmpErr += df_dp[i][0]*df_dp[i][0]*df_dp[i][1]*df_dp[i][1]; 
      tmpErr = sqrt( tmpErr );
      //std::cout << "Prob for jets v14 is = " << Pjet << " +- " << tmpErr << std::endl;
      _jet1_uncertainty = tmpErr;   
    }   

    
  } else if (version=="13b") {
    
    // Calculation that none of the jets are above the threshold of 30 GeV.
    for (int i = 0; i < total_objects; i++){
      
      P0L3 *= 1 - prob_t30[2][i];
      
    }
    
    // Calculation that at most one of the jets is above the threshold of 30 GeV 
    // and no other jets above 20 GeV.
    for (int i = 0; i < total_objects; i++) {
      
      P1_factor_1 = prob_t30[2][i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
      P1L3 += P1_factor_1 * P1_factor_2;
      
    }
    
    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0L3 - P1L3 ;//- P0L2 - P0L1 + P0L20L1 + P0L30L1 + P0L30L2 - P0L30L20L1 + P1L30L1 + P1L30L2 - P1L30L20L1 ;
    if ( _debug ) {
      cout << "\t\tv13b - P0L3: " << P0L3 << endl;
      cout << "\t\tv13b - P1L3: " << P1L3 << endl;
      cout << "\t\tv13b - Pjet: " << Pjet << endl;
      cout << "V13b EJets (Jets) L3 probability = " << Pjet << endl;
    }


    if (_systematic == "nominal") {    
      // LSC:  Okay let's calculate the uncertainty for the v13c trigger probability.
      // I am calculating the derivatives here in the propogation error formula.    
      double df_dp[100][2];
      int num_of_terms = 2 * total_objects;
      for (int i = 0; i < total_objects; i++) {
	df_dp[i][0] = uncertainty_t30[2][i];
	df_dp[i+total_objects][0] = uncertainty_t20[2][i];
      }
      
      double P1_factor_1, P1_factor_2;
      // Uncertainty for P0L3 from P0L3
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t30[2][j];
	df_dp[i][1] = P1_factor_2;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty for P0L3 from term P1L3
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[i][0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
	df_dp[i][1] -= P1_factor_2;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty for P1L3 term from term P1L3
      for (int i = 0; i < total_objects; i++) {
	P1_factor_1 = 0.0; 
	//std::cout << "df_dp[i+total_objects][0] " << i+total_objects << " = " << df_dp[i+total_objects][0] << std::endl;
	for (int j = 0; j < total_objects; j++) {
	  if (j!=i) P1_factor_2 = prob_t30[2][j];
	  double P1_factor_3 = 1.0;
	  for (int k = 0; k< total_objects; k++) {
	    if ((k!=i)&&(k!=j)) P1_factor_3 *= 1 - prob_t20[2][k];
	  }
	  P1_factor_1 += P1_factor_2 * P1_factor_3;
	}
	df_dp[i+total_objects][1] = P1_factor_1;
	//std::cout << "df_dp[1] " << i+total_objects << " = " << df_dp[i+total_objects][1] << std::endl;
      }
      
      double tmpErr = 0.0;
      for (int i = 0; i < num_of_terms; i++) tmpErr += df_dp[i][0]*df_dp[i][0]*df_dp[i][1]*df_dp[i][1]; 
      tmpErr = sqrt( tmpErr );
      //std::cout << "Prob for jets v13b is = " << Pjet << " +- " << tmpErr << std::endl;
      _jet1_uncertainty = tmpErr;   
    }


  } else if (version=="13a") {
    
    // Calculation that none of the jets are above the threshold of 25 GeV.
    for (int i = 0; i < total_objects; i++){
      
      P0L3 *= 1 - prob_t25[2][i];
      
    }
    
    // Calculation that at most one of the jets is above the threshold of 25 GeV 
    // and no other jets above 20 GeV.
    for (int i = 0; i < total_objects; i++) {
      
      P1_factor_1 = prob_t25[2][i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
      P1L3 += P1_factor_1 * P1_factor_2;
      
    }
    
    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0L3 - P1L3 ;
    if ( _debug ) {
      cout << "\t\tv13a - P0L3: " << P0L3 << endl;
      cout << "\t\tv13a - P1L3: " << P1L3 << endl;
      cout << "\t\tv13a - Pjet: " << Pjet << endl;
      cout << "V13a EJets (Jets) L3 probability = " << Pjet << endl;
    }

    if (_systematic == "nominal") {
      // LSC:  Okay let's calculate the uncertainty for the v13a trigger probability.
      // I am calculating the derivatives here in the propogation error formula.    
      double df_dp[100][2];
      int num_of_terms = 2 * total_objects;
      for (int i = 0; i < total_objects; i++) {
	df_dp[i][0] = uncertainty_t25[2][i];
	df_dp[i+total_objects][0] = uncertainty_t20[2][i];
      }
      
      double P1_factor_1, P1_factor_2;
      // Uncertainty for P0L3 from P0L3
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t25[2][j];
	df_dp[i][1] = P1_factor_2;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty for P0L3 from term P1L3
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[i][0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
	df_dp[i][1] -= P1_factor_2;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty for P1L3 term from term P1L3
      for (int i = 0; i < total_objects; i++) {
	P1_factor_1 = 0.0; 
	//std::cout << "df_dp[i+total_objects][0] " << i+total_objects << " = " << df_dp[i+total_objects][0] << std::endl;
	for (int j = 0; j < total_objects; j++) {
	  if (j!=i) P1_factor_2 = prob_t25[2][j];
	  double P1_factor_3 = 1.0;
	  for (int k = 0; k< total_objects; k++) {
	    if ((k!=i)&&(k!=j)) P1_factor_3 *= 1 - prob_t20[2][k];
	  }
	  P1_factor_1 += P1_factor_2 * P1_factor_3;
	}
	df_dp[i+total_objects][1] = P1_factor_1;
	//std::cout << "df_dp[1] " << i+total_objects << " = " << df_dp[i+total_objects][1] << std::endl;
      }
      
      double tmpErr = 0.0;
      for (int i = 0; i < num_of_terms; i++) tmpErr += df_dp[i][0]*df_dp[i][0]*df_dp[i][1]*df_dp[i][1]; 
      tmpErr = sqrt( tmpErr );
      //std::cout << "Prob for jets v13a is = " << Pjet << " +- " << tmpErr << std::endl;
      _jet1_uncertainty = tmpErr;   
    }

    
  } else if (version=="12") {
    
    // Calculation that none of the jets are above the threshold of 20 GeV.
    for (int i = 0; i < total_objects; i++){
      
      P0L3 *= 1 - prob_t20[2][i];
      
    }
    
    // Calculation that at most one of the jets is above the threshold of 20 GeV 
    // and no other jets above 20 GeV.
    for (int i = 0; i < total_objects; i++) {
      
      P1_factor_1 = prob_t20[2][i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
      P1L3 += P1_factor_1 * P1_factor_2;
      
    }

    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0L3 - P1L3 ;
    if ( _debug ) {
      cout << "\t\tv12 - P0L3: " << P0L3 << endl;
      cout << "\t\tv12 - P1L3: " << P1L3 << endl;
      cout << "\t\tv12 - Pjet: " << Pjet << endl;
      cout << "V12 EJets (Jets) L3 probability = " << Pjet << endl;
    }

    if (_systematic == "nominal") {
      // LSC:  Okay let's calculate the uncertainty for the v14 trigger probability.
      // I am calculating the derivatives here in the propogation error formula.    
      double df_dp[100][2];
      int num_of_terms = total_objects;
      for (int i = 0; i < total_objects; i++) {
	df_dp[i][0] = uncertainty_t20[2][i];
      }
      
      double P1_factor_1, P1_factor_2;
      // Uncertainty from P0L3 term
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
	df_dp[i][1] = P1_factor_2;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty from P1L3 term.  I know it cancels the first term, but I am
      // leaving it for clarification.
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[i][0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
	df_dp[i][1] = df_dp[i][1] - P1_factor_2;
	//std::cout << "Factor = " << P1_factor_2 << std::endl;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty for P1L3 term
      for (int i = 0; i < total_objects; i++) {
	P1_factor_1 = 0.0; 
	//std::cout << "df_dp[i][0] " << i << " = " << df_dp[i][0] << std::endl;
	for (int j = 0; j < total_objects; j++) {
	  if (j!=i) P1_factor_2 = prob_t20[2][j];
	  double P1_factor_3 = 1.0;
	  for (int k = 0; k< total_objects; k++) {
	    if ((k!=i)&&(k!=j)) P1_factor_3 *= 1 - prob_t20[2][k];
	  }
	  P1_factor_1 += P1_factor_2 * P1_factor_3;
	}
	df_dp[i][1] = df_dp[i][1] + P1_factor_1;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      
      double tmpErr = 0.0;
      for (int i = 0; i < num_of_terms; i++) tmpErr += df_dp[i][0]*df_dp[i][0]*df_dp[i][1]*df_dp[i][1]; 
      tmpErr = sqrt( tmpErr );
      //std::cout << "Prob for jets v12 is = " << Pjet << " +- " << tmpErr << std::endl;
      _jet1_uncertainty = tmpErr;   
    }
        
  } else if (version == "11" || version=="10" || version=="09" || version=="08") {
    
   // Calculation that none of the jets are above the threshold of 15 GeV.
    for (int i = 0; i < total_objects; i++){
      
      P0L3 *= 1 - prob_t15[2][i];
      if (i!=total_objects) P0L2 *= 1 - prob_t15[1][i];	
      if (i!=total_objects) P0L1 *= 1 - prob_t15[0][i];
	
    }
    
    // Calculation that at most one of the jets is above the threshold of 15 GeV 
    // and no other jets above 15 GeV.
    for (int i = 0; i < total_objects; i++) {
      
      P1_factor_1 = prob_t15[2][i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t15[2][j];
      P1L3 += P1_factor_1 * P1_factor_2;
      
    }
    
    // LSC: The probability to fire the trigger is:
    Pjet = (1 - P0L1)*(1 - P0L2)*(1 - P0L3 - P1L3) ;
    if ( _debug ) {
      cout << "\t\tv8-11 - P0L1: " << P0L1 << endl;
      cout << "\t\tv8-11 - P0L2: " << P0L2 << endl;
      cout << "\t\tv8-11 - P0L3: " << P0L3 << endl;
      cout << "\t\tv8-11 - P1L3: " << P1L3 << endl;
      cout << "\t\tv8-11 - Pjet: " << Pjet << endl;
      cout << "V8-11 EJets (Jets) L3 probability = " << Pjet << endl;
    }
 
    if (_systematic == "nominal") {
      // LSC:  Okay let's calculate the uncertainty for the v8-11 trigger probability.
      // I am calculating the derivatives here in the propogation error formula.    
      double df_dp[100][2];
      int num_of_terms = total_objects;
      for (int i = 0; i < total_objects; i++) {
	df_dp[i][0] = uncertainty_t15[2][i];
      }
      
      double P1_factor_1, P1_factor_2;
      // Uncertainty from P0L3 term
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t15[2][j];
	df_dp[i][1] = P1_factor_2;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty from P1L3 term.  I know it cancels the first term, but I am
      // leaving it for clarification.
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[i][0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t15[2][j];
	df_dp[i][1] = df_dp[i][1] - P1_factor_2;
	//std::cout << "Factor = " << P1_factor_2 << std::endl;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty for P1L3 term
      for (int i = 0; i < total_objects; i++) {
	P1_factor_1 = 0.0; 
	//std::cout << "df_dp[i][0] " << i << " = " << df_dp[i][0] << std::endl;
	for (int j = 0; j < total_objects; j++) {
	  if (j!=i) P1_factor_2 = prob_t15[2][j];
	  double P1_factor_3 = 1.0;
	  for (int k = 0; k< total_objects; k++) {
	    if ((k!=i)&&(k!=j)) P1_factor_3 *= 1 - prob_t15[2][k];
	  }
	  P1_factor_1 += P1_factor_2 * P1_factor_3;
	}
	df_dp[i][1] = df_dp[i][1] + P1_factor_1;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      
      double tmpErr = 0.0;
      for (int i = 0; i < num_of_terms; i++) tmpErr += df_dp[i][0]*df_dp[i][0]*df_dp[i][1]*df_dp[i][1]; 
      tmpErr = sqrt( tmpErr );
      //std::cout << "Prob for jets v8-11 is = " << Pjet << " +- " << tmpErr << std::endl;
      _jet1_uncertainty = tmpErr;   
    }
  }

  if ( version.substr(0,2) >= "15" ) {
    
    // Calculation that none of the jets are above the threshold of 25 GeV.
    for (int i = 0; i < total_objects; i++){
      
      P0L3 *= 1 - prob_t25[2][i];
      
    }
    
    // Calculation that at most one of the jets is above the threshold of 25 GeV 
    // and no other jets above 20 GeV.
    for (int i = 0; i < total_objects; i++) {
      
      P1_factor_1 = prob_t25[2][i];
      P1_factor_2 = 1.0;
      for (int j = 0; j < total_objects; j++)
        if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
      P1L3 += P1_factor_1 * P1_factor_2;
      
    }
    
    // LSC: The probability to fire the trigger is:
    Pjet = 1 - P0L3 - P1L3 ;
    if ( _debug ) {
      cout << "\t\tv15 - P0L3: " << P0L3 << endl;
      cout << "\t\tv15 - P1L3: " << P1L3 << endl;
      cout << "\t\tv15 - Pjet: " << Pjet << endl;
      cout << "V15 EJets (Jets) L3 probability = " << Pjet << endl;
    }
    
    if (_systematic == "nominal") {
      // LSC:  Okay let's calculate the uncertainty for the v15 trigger probability.
      // I am calculating the derivatives here in the propogation error formula.    
      double df_dp[100][2];
      int num_of_terms = 2 * total_objects;
      for (int i = 0; i < total_objects; i++) {
	df_dp[i][0] = uncertainty_t25[2][i];
	df_dp[i+total_objects][0] = uncertainty_t20[2][i];
      }
      
      double P1_factor_1, P1_factor_2;
      // Uncertainty for P0L3 from P0L3
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t25[2][j];
	df_dp[i][1] = P1_factor_2;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty for P0L3 from term P1L3
      for (int i = 0; i < total_objects; i++) { 
	//std::cout << "df_dp[i][0] " << i << " = " << df_dp[i][0] << std::endl;
	P1_factor_2 = 1.0;
	for (int j = 0; j < total_objects; j++)
	  if (j!=i) P1_factor_2 *= 1 - prob_t20[2][j];
	df_dp[i][1] -= P1_factor_2;
	//std::cout << "df_dp[1] " << i << " = " << df_dp[i][1] << std::endl;
      }
      // Uncertainty for P1L3 term from term P1L3
      for (int i = 0; i < total_objects; i++) {
	P1_factor_1 = 0.0; 
	//std::cout << "df_dp[i+total_objects][0] " << i+total_objects << " = " << df_dp[i+total_objects][0] << std::endl;
	for (int j = 0; j < total_objects; j++) {
	  P1_factor_2 = 0.;
	  if (j!=i) P1_factor_2 = prob_t25[2][j];
	  double P1_factor_3 = 1.0;
	  for (int k = 0; k< total_objects; k++) {
	    if ((k!=i)&&(k!=j)) P1_factor_3 *= 1 - prob_t20[2][k];
	  }
	  P1_factor_1 += P1_factor_2 * P1_factor_3;
	}
	df_dp[i+total_objects][1] = P1_factor_1;
	//std::cout << "df_dp[1] " << i+total_objects << " = " << df_dp[i+total_objects][1] << std::endl;
      }
      
      double tmpErr = 0.0;
      for (int i = 0; i < num_of_terms; i++) tmpErr += df_dp[i][0]*df_dp[i][0]*df_dp[i][1]*df_dp[i][1]; 
      tmpErr = sqrt( tmpErr );
      _jet1_uncertainty = tmpErr;   
    } 
  }

  double probCalc;
  probCalc = Pjet;
  
  if (_debug) std::cout << "\t\tProbJet: " << Pjet << std::endl;
  
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
    cout << "Probability_EJets::Prob_Jet" << _channel << " Jet Probability = " << probCalc << endl;
  }
  
  double probability;
  probability = probCalc;
  
  return probability;
  
}

  
// //------------------------------------------------------------------------------
// // Finish
// //------------------------------------------------------------------------------
void Probability_EJets::PrintEfficiency()
{
  double weighted_mean_numerator = 0.0;
  double weighted_mean_denominator = 0.0;
  static const int size = 13;
  double weighted_mean[size];
  double weighted_mean_sigma[size];

  double mean_numerator = 0.0;
  double mean_numerator_sigma = 0.0;
  double mean[size];
  double mean_sigma[size];

  if (_debug) {
    cout << "--------------------------------------------------------------------------\n";
    for (int i=0; i<_trigger_version.size(); i++) {
      cout << "And probability was greater than EJets probability in version " << _trigger_version[i] << ' ' << _and_is_greater[i] << " times\n";
      cout << "And probability was 10% greater than EJets probability in version " << _trigger_version[i] << ' ' << _and_is_much_greater[i] << " times\n";
    }
    cout << "--------------------------------------------------------------------------\n";
  }

  if (_systematic == "nominal") {
	  
    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x12.size() != _s12.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x12!= _s12 " << std::endl;
    for (int i=0; i < _x12.size(); ++i) {
      weighted_mean_numerator += _x12[i] / ( _s12[i] * _s12[i] );
      weighted_mean_denominator += 1 / ( _s12[i] * _s12[i] );
      mean_numerator += _x12[i];
      mean_numerator_sigma += _s12[i] * _s12[i];
    }
    weighted_mean[12] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[12] = sqrt( 1 / weighted_mean_denominator );
    mean[12] = mean_numerator / (_x12.size()+1.e-10);
    mean_sigma[12] = sqrt( mean_numerator_sigma ) / _s12.size();
    if ( mean[12] > 0.0 ) std::cout << "A: Average trigger probability for v16 is " << mean[12] << " +- " << mean_sigma[12] << std::endl;

	    
    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x11.size() != _s11.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x11!= _s11 " << std::endl;
    for (int i=0; i < _x11.size(); ++i) {
      weighted_mean_numerator += _x11[i] / ( _s11[i] * _s11[i] );
      weighted_mean_denominator += 1 / ( _s11[i] * _s11[i] );
      mean_numerator += _x11[i];
      mean_numerator_sigma += _s11[i] * _s11[i];
    }
    weighted_mean[11] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[11] = sqrt( 1 / weighted_mean_denominator );
    mean[11] = mean_numerator / (_x11.size()+1.e-10);
    mean_sigma[11] = sqrt( mean_numerator_sigma ) / _s11.size();
    if ( mean[11] > 0.0 ) std::cout << "A: Average trigger probability for v15c is " << mean[11] << " +- " << mean_sigma[11] << std::endl;


    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x10.size() != _s10.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x10 != _s10 " << std::endl;
    for (int i=0; i < _x10.size(); ++i) {
      weighted_mean_numerator += _x10[i] / ( _s10[i] * _s10[i] );
      weighted_mean_denominator += 1 / ( _s10[i] * _s10[i] );
      mean_numerator += _x10[i];
      mean_numerator_sigma += _s10[i] * _s10[i];
    }
    weighted_mean[10] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[10] = sqrt( 1 / weighted_mean_denominator );
    mean[10] = mean_numerator / (_x10.size()+1.e-10);
    mean_sigma[10] = sqrt( mean_numerator_sigma ) / _s10.size();
    if ( mean[10] > 0.0 ) std::cout << "A: Average trigger probability for v15b is " << mean[10] << " +- " << mean_sigma[10] << std::endl;
    
    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x9.size() != _s9.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x9 != _s9" << std::endl;
    for (int i=0; i < _x9.size(); ++i) {
      weighted_mean_numerator += _x9[i] / ( _s9[i] * _s9[i] );
      weighted_mean_denominator += 1 / ( _s9[i] * _s9[i] );
      mean_numerator += _x9[i];
      mean_numerator_sigma += _s9[i] * _s9[i];
    }
    weighted_mean[9] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[9] = sqrt( 1 / weighted_mean_denominator );
    mean[9] = mean_numerator / (_x9.size()+1.e-10);
    mean_sigma[9] = sqrt( mean_numerator_sigma ) / _s9.size();
    if ( mean[9] > 0.0 ) std::cout << "A: Average trigger probability for v15a is " << mean[9] << " +- " << mean_sigma[9] << std::endl;

    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x8.size() != _s8.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x8 != _s8 " << std::endl;
    for (int i=0; i < _x8.size(); ++i) {
      weighted_mean_numerator += _x8[i] / ( _s8[i] * _s8[i] );
      weighted_mean_denominator += 1 / ( _s8[i] * _s8[i] );
      mean_numerator += _x8[i];
      mean_numerator_sigma += _s8[i] * _s8[i];
    }
    weighted_mean[8] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[8] = sqrt( 1 / weighted_mean_denominator );
    mean[8] = mean_numerator / (_x8.size()+1.e-10);
    mean_sigma[8] = sqrt( mean_numerator_sigma ) / _s8.size();
    if ( mean[8] > 0.0 ) std::cout << "A: Average trigger probability for v14 is " << mean[8] << " +- " << mean_sigma[8] << std::endl;

    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x7.size() != _s7.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x7 != _s7" << std::endl;
    for (int i=0; i < _x7.size(); ++i) {
      //std::cout << "x and s are " << _x7[i] << " ... " << _s7[i] << std::endl; 
      weighted_mean_numerator += _x7[i] / ( _s7[i] * _s7[i] );
      weighted_mean_denominator += 1 / ( _s7[i] * _s7[i] );
      mean_numerator += _x7[i];
      mean_numerator_sigma += _s7[i] * _s7[i];
    }
    weighted_mean[7] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[7] = sqrt( 1 / weighted_mean_denominator );
    mean[7] = mean_numerator / (_x7.size()+1.e-10);
    mean_sigma[7] = sqrt( mean_numerator_sigma ) / _s7.size();
    if ( mean[7] > 0.0 ) std::cout << "A: Average trigger probability for v13c is " << mean[7] << " +- " << mean_sigma[7] << std::endl;

    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x6.size() != _s6.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x6 != _s6" << std::endl;
    for (int i=0; i < _x6.size(); ++i) {
      weighted_mean_numerator += _x6[i] / ( _s6[i] * _s6[i] );
      weighted_mean_denominator += 1 / ( _s6[i] * _s6[i] );
      mean_numerator += _x6[i];
      mean_numerator_sigma += _s6[i] * _s6[i];
    }
    weighted_mean[6] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[6] = sqrt( 1 / weighted_mean_denominator );
    mean[6] = mean_numerator / (_x6.size()+1.e-10);
    mean_sigma[6] = sqrt( mean_numerator_sigma ) / _s6.size();
    if ( mean[6] > 0.0 ) std::cout << "A: Average trigger probability for v13b is " << mean[6] << " +- " << mean_sigma[6] << std::endl;

    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x5.size() != _s5.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x5 != _s5" << std::endl;
    for (int i=0; i < _x5.size(); ++i) {
      //std::cout << "x and s are " << _x5[i] << " ... " << _s5[i] << std::endl; 
      weighted_mean_numerator += _x5[i] / ( _s5[i] * _s5[i] );
      weighted_mean_denominator += 1 / ( _s5[i] * _s5[i] );
      mean_numerator += _x5[i];
      mean_numerator_sigma += _s5[i] * _s5[i];
    }
    weighted_mean[5] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[5] = sqrt( 1 / weighted_mean_denominator );
    mean[5] = mean_numerator / (_x5.size()+1.e-10);
    mean_sigma[5] = sqrt( mean_numerator_sigma ) / _s5.size();
    if ( mean[5] > 0.0 ) std::cout << "A: Average trigger probability for v13a is " << mean[5] << " +- " << mean_sigma[5] << std::endl;

    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x4.size() != _s4.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x4 != _s4" << std::endl;
    for (int i=0; i < _x4.size(); ++i) {
      weighted_mean_numerator += _x4[i] / ( _s4[i] * _s4[i] );
      weighted_mean_denominator += 1 / ( _s4[i] * _s4[i] );
      mean_numerator += _x4[i];
      mean_numerator_sigma += _s4[i] * _s4[i];
    }
    weighted_mean[4] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[4] = sqrt( 1 / weighted_mean_denominator );
    mean[4] = mean_numerator / (_x4.size()+1.e-10);
    mean_sigma[4] = sqrt( mean_numerator_sigma ) / _s4.size();
    if ( mean[4] > 0.0 ) std::cout << "A: Average trigger probability for v12 is " << mean[4] << " +- " << mean_sigma[4] << std::endl;

    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x3.size() != _s3.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x3 != _s3" << std::endl;
    for (int i=0; i < _x3.size(); ++i) {
      weighted_mean_numerator += _x3[i] / ( _s3[i] * _s3[i] );
      weighted_mean_denominator += 1 / ( _s3[i] * _s3[i] );
      mean_numerator += _x3[i];
      mean_numerator_sigma += _s3[i] * _s3[i];
    }
    weighted_mean[3] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[3] = sqrt( 1 / weighted_mean_denominator );
    mean[3] = mean_numerator / (_x3.size()+1.e-10);
    mean_sigma[3] = sqrt( mean_numerator_sigma ) / _s3.size();
    if ( mean[3] > 0.0 ) std::cout << "A: Average trigger probability for v11 is " << mean[3] << " +- " << mean_sigma[3] << std::endl;

    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x2.size() != _s2.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x2 != _s2" << std::endl;
    for (int i=0; i < _x2.size(); ++i) {
      weighted_mean_numerator += _x2[i] / ( _s2[i] * _s2[i] );
      weighted_mean_denominator += 1 / ( _s2[i] * _s2[i] );
      mean_numerator += _x2[i];
      mean_numerator_sigma += _s2[i] * _s2[i];
    }
    weighted_mean[2] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[2] = sqrt( 1 / weighted_mean_denominator );
    mean[2] = mean_numerator / (_x2.size()+1.e-10);
    mean_sigma[2] = sqrt( mean_numerator_sigma ) / _s2.size();
    if ( mean[2] > 0.0 ) std::cout << "A: Average trigger probability for v10 is " << mean[2] << " +- " << mean_sigma[2] << std::endl;

    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x1.size() != _s1.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x1 != _s1" << std::endl;
    for (int i=0; i < _x1.size(); ++i) {
      weighted_mean_numerator += _x1[i] / ( _s1[i] * _s1[i] );
      weighted_mean_denominator += 1 / ( _s1[i] * _s1[i] );
      mean_numerator += _x1[i];
      mean_numerator_sigma += _s1[i] * _s1[i];
    }
    weighted_mean[1] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[1] = sqrt( 1 / weighted_mean_denominator );
    mean[1] = mean_numerator / (_x1.size()+1.e-10);
    mean_sigma[1] = sqrt( mean_numerator_sigma ) / _s1.size();
    if ( mean[1] > 0.0 ) std::cout << "A: Average trigger probability for v09 is " << mean[1] << " +- " << mean_sigma[1] << std::endl;

    weighted_mean_numerator = 0.0;
    weighted_mean_denominator = 0.0;
    mean_numerator = 0.0;
    mean_numerator_sigma = 0.0;
    if ( _x0.size() != _s0.size() ) std::cout << "Probability_EJets: WARNING - arrays not same size, _x0 != _s0" << std::endl;
    for (int i=0; i < _x0.size(); ++i) {
      weighted_mean_numerator += _x0[i] / ( _s0[i] * _s0[i] );
      weighted_mean_denominator += 1 / ( _s0[i] * _s0[i] );
      mean_numerator += _x0[i];
      mean_numerator_sigma += _s0[i] * _s0[i];
    }
    weighted_mean[0] = weighted_mean_numerator / weighted_mean_denominator;
    weighted_mean_sigma[0] = sqrt( 1 / weighted_mean_denominator );
    mean[0] = mean_numerator / (_x0.size()+1.e-10);
    mean_sigma[0] = sqrt( mean_numerator_sigma ) / _s0.size();
    if ( mean[0] > 0.0 ) std::cout << "A: Average trigger probability for v08 is " << mean[0] << " +- " << mean_sigma[0] << std::endl;

    ////////////////////////////////////////////////////////////////////////
    // Now calculate the lumi weighted average.
    ////////////////////////////////////////////////////////////////////////
    double lumi_weighted_numerator = 0.0;
    double lumi_weighted_denominator = 0.0;
    // Now calculate the luminosity weighted mean.
    int j = 0;
    for (int i = 0; i< size; i++) {
      if (mean[i]<1.e-10) continue;
      //lumi_weighted_numerator += weighted_mean[i] * _trigger_lumi[_trigger_lumi.size()-1-j];
      lumi_weighted_numerator += mean[i] * _trigger_lumi[_trigger_lumi.size()-1-j];
      lumi_weighted_denominator += _trigger_lumi[_trigger_lumi.size()-1-j];
      j++;
    }

    double lumi_weighted_mean = lumi_weighted_numerator / lumi_weighted_denominator;
    double lumi_weighted_sigma = 0.0;

    double df_dp[size][2];
    double sum_weights = 0.0;
    j = 0;
    for (int i = 0; i < size; i++) {
      if (mean[i]<1.e-10) continue;
      //df_dp[i][0] = weighted_mean_sigma[i];
      df_dp[i][0] = mean_sigma[i];
      sum_weights += _trigger_lumi[_trigger_lumi.size()-1-j];
      j++;
    }
    j = 0;
    for (int i = 0; i < size; i++) { 
      if (mean[i]<1.e-10) continue;
      df_dp[i][1] = _trigger_lumi[_trigger_lumi.size()-1-j] / sum_weights;
      j++;
    }
    double tmpErr = 0.0;
    for (int i = 0; i < size; i++) {
      if (mean[i]<1.e-10) continue;
      tmpErr += df_dp[i][0]*df_dp[i][0]*df_dp[i][1]*df_dp[i][1]; 
    }
    tmpErr = sqrt( tmpErr );
    lumi_weighted_sigma = tmpErr;
    
    std::cout << "The lumi weighted trig prob is " << lumi_weighted_mean << " +- " << lumi_weighted_sigma << std::endl;
  }

}

void  Probability_EJets::change_triggermap() {

  if(_debug) cout<<"==>Probability_EJets::change_triggermap()"<<endl;

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


  //---------------------------------
  // Way to differentiate between Run2b & Run2b at config level
  //---------------------------------
  if ( _trigger_version[_trigger_version.size()-1].substr(0,2) <= "14" ) {
    _isRun2b = false;
  } else {
    _isRun2b = true;
  }
  if ( _debug ) {
    if ( _isRun2b) {
	cout << "Config " << name() << " is Run2b" << endl;
    } else {
	cout << "Config " << name() << " is Run2a" << endl;
    }
  }
  
  //------------------------------------
  // Store the eff_utils look-up information
  //------------------------------------
  _flags.clear();
  _flags.push_back("EffName");
  _flags.push_back("EffVarNames");
  _flags.push_back("EffType");
  _flags.push_back("EffVersion");
  _flags.push_back("ObjQuality");
  _flags.push_back("ObjType");
  _flags.push_back("ObjRelativeTo");
  _flags.push_back("ObjVersion");
  _flags.push_back("TriggerVersion");
  _flags.push_back("AddToEffUtils");

  _object.clear();
  _object.push_back("Electron");
  _object.push_back("EleJet");
  _object.push_back("Jet");

  _location.clear();
  _location.push_back("_INC");

  _level.clear();
  _level.push_back("Level1");
  _level.push_back("Level2");
  _level.push_back("Level3");
  
  _threshold.clear();
  _threshold.push_back("15");
  _threshold.push_back("20");
  _threshold.push_back("25");
  _threshold.push_back("30");

  _jetTrigType.clear();
  _jetTrigType.push_back("Group1");

  //------------------------------------
  // Create a map of trigger flags for later use
  //------------------------------------

  // These are for "standard" eff_utils objects consist of "Level", "ObjType" etc...

  for ( int i = 0; i < _num_trigger_versions; i++ ) {
    std::string version = _trigger_version[i];
    _trigger_version_map[version] = i;
    
    for ( int l = 0; l < _location.size(); l++ ) {
      std::string detector = _location[l];
      
      for ( int k = 0; k < _object.size(); k++ ) {
	std::string object = _object[k];

	for ( int m = 0; m < _threshold.size(); m++ ) {
	  std::string threshold = _threshold[m];
	
	for ( int ml = 0; ml < _level.size(); ml++ ) {
	  std::string level = _level[ml];

	  for ( int mt = 0; mt < _jetTrigType.size(); mt++ ) {
	    std::string trigtype = _jetTrigType[mt];
	
	    std::string add_to_eff_utils;

	    for ( int j = 0; j < _flags.size(); j++ ) {
	      std::string flag = _flags[j];

	      std::stringstream flag_name;
	      if ( _isRun2b ) {	    
		flag_name << level << object << flag << "_" << version << detector << "_T" << threshold << "_" << trigtype;
	      }
              else {
		flag_name << level << object << flag << "_" << version << detector << "_T" << threshold;
              }		      
	      if (_debug) std::cout << "Looking for flag " << flag_name.str().c_str() << std::endl;
	    
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

// tmp.size() == 0 means that keyword has no value (i.e. non-specified flag), either use default value or throw exception
	      
	      if ( flag == "EffName" && tmp.size() == 0 ) {
		if ( object == "Electron" || object == "EleJet" ) {
		  tmp.push_back("eff");
		}
		if ( object == "Jet" ) {
		  tmp.push_back("TrigEff");
		}
	      }

	      if ( flag == "EffType" && tmp.size() == 0 ) {
		tmp.push_back("Binned");
	      }
	    
	      if ( flag == "EffVersion" && tmp.size() == 0 ) {
		tmp.push_back("1");
	      }
	    
	      if ( flag == "ObjQuality" && tmp.size() == 0 ) {
	        if ( _isRun2b ) {	
			tmp.push_back(_electron_quality);
	        }
	        else {
			tmp.push_back("matched");
		}			
	      }
	    
	      if ( flag == "ObjRelativeTo" && tmp.size() == 0 ) {
		if ( object == "Electron"  || object == "EleJet" ) {
		  continue;
		}
		if ( object == "Jet") {
		  tmp.push_back(_jet_quality);
		}
	      }
	    
	      if ( flag == "ObjType" && tmp.size() == 0 ) {
		if ( object == "Jet" ) {
		  tmp.push_back("Jet");
		}
		if ( object == "Electron" ) {
		  tmp.push_back("Electron");
		}
		if ( object == "EleJet" ) {
		  tmp.push_back("EleJet");
		}
	      }
              
              /*	      
	      if ( flag == "ObjVersion" && tmp.size() == 0 ) {
		if ( object == "Electron" ) {
		  tmp.push_back("1");
		}
		if ( object == "EleJet" ) {
		  tmp.push_back("1");
		}
		if ( object == "Jet" ) {
		  tmp.push_back("1");
		}
	      }
	      */

	      if ( flag == "TriggerVersion" && tmp.size() == 0 ) {
		if (object == "Electron" || object == "EleJet" ) {
			if (version == "08") {
				tmp.push_back("v8");
			}
			else if (version == "09") {
				tmp.push_back("v9");
			}
			else {
				tmp.push_back("v"+version);
			}
		}
		if ( version.substr(0,2) > "16" || version.substr(0,2) < "08" ) {
			cerr << "Probability_EJets::Probablity_EJets " << name() << " WARNING: trigger version is out of range: "
				<< version << endl << endl;
		}
	      }
	    
	      _trigger_map[flag_name.str()] = tmp;
              if(_debug) {
                  cout << "Added to trigger map at " << flag_name.str().c_str();
                  for(int i=0; i<tmp.size(); ++i) cout << ' ' << tmp[i].c_str();
                  cout << endl;
              }
	    }
	  }
	}
	}
      }
    }
  }


  // These are for special trigger flags ("Group1" like)
  
  _flags_EM.clear();
  _flags_EM.push_back("EffName");
  _flags_EM.push_back("EffType");
  _flags_EM.push_back("EffVarNames");
  _flags_EM.push_back("EffVersion");
  _flags_EM.push_back("ObjQuality");
  _flags_EM.push_back("ObjRelativeTo");
  _flags_EM.push_back("ObjType");
  _flags_EM.push_back("AddToEffUtils");




  _EMTrigType.push_back("Group1");







  for ( int i = 0; i < _num_trigger_versions; i++ ) {
    string version = _trigger_version[i];

    for ( int mt = 0; mt < _EMTrigType.size(); mt++) {






      string emType = _EMTrigType[mt];


      string add_to_eff_utils;
	  
      for ( int j = 0; j < _flags_EM.size(); j++ ) {
	string flag = _flags_EM[j];
      
	stringstream flag_name;

	flag_name << flag << "_" << emType << "_" << version;




	if(_debug) cout << "Looking for flag " << flag_name.str().c_str() << endl;

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
      
	if ( flag == "ObjQuality" ) { 
	  if (tmp.size()>0) {
	    cout << name() << " ERROR: must not specify ObjQuality again in config file, "
		  << "already have ObjQuality given as " << _electron_quality << endl << endl;
	    exit(1);
	  }
	  tmp.push_back(_electron_quality);
	} 
      
	if ( flag == "ObjRelativeTo" ) {
	  if (tmp.size()>0) {
	    cout << name() << " ERROR: must not specify ObjRelativeTo "
		 << "in config file, this flag is disabled in electron SPCs." << endl << endl;
	    exit(1);
	  }
	}
	
	if ( flag == "ObjType" && tmp.size() == 0 ) {
	  tmp.push_back("Electron");
	}
      
	_trigger_map[flag_name.str()] = tmp;
	if(_debug) {
	  cout << "Added to trigger map at " << flag_name.str().c_str();
	  for(int i=0; i<tmp.size(); ++i) cout << ' ' << tmp[i].c_str();
	  cout << endl;
	}
      } // loop over flags
    }
  }// loop over trigger versions

}
ClassImp(Probability_EJets)


