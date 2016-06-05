//----------------------------------------------------------
//Authors: Thomas Gadfort (tgadfort@fnal.gov) - original single muon code
//         Carsten Hensel (carsten@fnal.gov) - adaptation for dimuon trigger
//         Kristian Harder (harderk@fnal.gov) - combination + error propagation
//         Liang Li (liangli@fnal.gov)  - added support for single muon ORing & TriggerVersionHigh switch
//
//Last Updated: 4/30/06
//
//Purpose:  Calculates the probability muons of a certain quality
//          pass a single muon or dimuon trigger condition
//----------------------------------------------------------

//Header file for this class
#include "caf_trigger/Probability_nMuon.hpp"
#include "caf_mc_util/MCReqID.hpp"
#include "eff_utils/EffVal.hpp"

using namespace std;

extern caf_mc_util::MCReqID *MCREQID;

Probability_nMuon::Probability_nMuon(const char *name)
  : probProcessor(name)
{
  //We grab terms from the CAFe configuration file here
  cafe::Config config(name);

  //------------------------------------
  // Debug
  //------------------------------------
  string debug = config.get("Debug", "no");
  _debug = ( debug == "yes" );
  if (_debug) cout << endl << "Debugging for Probability_nMuon is turned on." << endl << endl;

  //------------------------------------
  // Channel name
  // This is the value specified to combine in the config file
  //------------------------------------
  _channel = config.get("ChannelName", "nMuon");


  //------------------------------------
  // Muon_Quality
  //------------------------------------
  _muon_quality = config.get("MuonQuality", "none");
  if ( _muon_quality == "none" ) {
    cout << name << " WARNING: No MuonQuality parameter was specified."
	 << " Using loose muons as default." << endl;
    _muon_quality = "loose";
  }
  
  
  //------------------------------------
  // Track_Quality
  //------------------------------------
  _track_quality = config.get("TrackQuality", "none");
  if ( _track_quality == "none" ) {
    cout << name << " WARNING: No TrackQuality parameter was specified."
	 << " Using loose tracks as default." << endl;
    _track_quality = "trackloose";
  }

   _iso_quality = config.get("IsolationQuality", "none");
   if ( _iso_quality == "none" ) {
    cout << name << " WARNING: No IsolationQuality parameter was specified."
   << " Using none as default." << endl;
 }

  
  
  //------------------------------------
  // Get muon trigger definitions
  //------------------------------------
  for (int itrigcond=0; itrigcond<2; itrigcond++) {
    stringstream configname;
    configname << "Muon" << itrigcond << "_requireL1L2L3";
    vector<int> nextcond = config.getVInt(configname.str(),",");
    // is this muon specified at all?
    if (nextcond.size()==0) continue;
    // check whether all L1,L2,L3 conditions are specified properly
    if (nextcond.size()!=3) {
      cout << name << " ERROR: " << "Muon" << itrigcond << "_requireL1L2L3"
	   << " needs exactly three comma separated arguments" << endl;
      exit(1);
    }
    int nrequirements=0;
    for (int ilevel=0; ilevel<3; ilevel++) {
      if (nextcond[ilevel]==1) {
	++nrequirements;
      } else if (nextcond[ilevel]!=0) {
	cout << name << " ERROR: " << "Muon" << itrigcond << "_requireL1L2L3"
	     << " arguments must be either 0 or 1" << endl;
	exit(1);
      }
    }
    if (nrequirements==0) {
      cout << name << " ERROR: " << "Muon" << itrigcond << "_requireL1L2L3"
	   << " should have at least one trigger requirement" << endl;
      exit(1);
    }
    _trigcond.push_back(nextcond);
  }
  _num_nonempty_trigconds=_trigcond.size();
  if (_trigcond.size()==1) {
    // as far as this code is concerned, a single muon trigger is just
    // a dimuon trigger where the second trigger condition has no
    // trigger requirements
    vector<int> dummycond(3,0);
    _trigcond.push_back(dummycond);
  } else if (_trigcond.size()==2) {
    // dimuon trigger: the algorithm here only works if the trigger
    // requirements for one of the muons are a subset of the requirements
    // for the other muon. That means you cannot have a requirement like
    // muon 1: L1,L2
    // muon 2: L1,L3
    // instead you would have to use
    // muon 1: L1,L2,L3
    // muon 2: L1
    // which is nothing but a matter of trigger-object matching anyway.
    bool uniquecondition_muon0=false;
    bool uniquecondition_muon1=false;
    for (int ilevel=0; ilevel<3; ilevel++) {
      uniquecondition_muon0|=(_trigcond[0][ilevel]>_trigcond[1][ilevel]);
      uniquecondition_muon1|=(_trigcond[1][ilevel]>_trigcond[0][ilevel]);
    }
    if (uniquecondition_muon0 && uniquecondition_muon1) {
      cout << name << " ERROR: can only use dimuon triggers where one "
	   << "condition is subset of the other" << endl;
      exit(1);
    }
    // now, to make things simpler later, make sure that the trigger
    // condition with more requirements is the first one in the list
    if (uniquecondition_muon1) {
      vector<int> swap = _trigcond[0];
      _trigcond[0]=_trigcond[1];
      _trigcond[1]=swap;
    }
  } else {
    cout << name << " ERROR: need to specify one or two trigger conditions"
	 << endl;
    exit(1);
  }

  /*
  //------------------------------------
  // Get the list of trigger versions
  //------------------------------------
  _trigger_version = config.getVString("TriggerVersions", ",");

  //------------------------------------
  // Save the number of trigger version for later use
  //------------------------------------
  _num_trigger_versions = _trigger_version.size();
  if ( _num_trigger_versions == 0 ) {
    cout << name << " ERROR: no trigger versions selected." << endl;
    exit(1);
  }
  */

  //OK, now we want to read this in from the change_request function

  //------------------------------------
  // Store the eff_utils look-up information
  //------------------------------------
  _flags.push_back("EffName");
  _flags.push_back("EffType");
  _flags.push_back("EffVarNames");
  _flags.push_back("ObjQuality");
  _flags.push_back("ObjRelativeTo");
  _flags.push_back("ObjType");
  _flags.push_back("TriggerVersionLow");
  _flags.push_back("TriggerVersionHigh");
  _flags.push_back("AddToEffUtils");

  _object.push_back("Muon");
  _object.push_back("Track");
  _object.push_back("Match");
  _object.push_back("SingleMuonOR");
  _object.push_back("Isolation");
  _location.push_back("_INC");
  _location.push_back("_CC");
  _location.push_back("_EC");
  _location.push_back("_ICD");

  _level.push_back("Level1");
  _level.push_back("Level2");
  _level.push_back("Level3");
  
  /*
  //------------------------------------
  // Create a map of trigger versions for later use
  //------------------------------------
  for ( int i = 0; i < _num_trigger_versions; i++ ) {
    string version = _trigger_version[i];
    
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
	    flag_name << level << object
		      << flag << "_" << version << detector;

	    // For dimuon triggers the two trigger conditions may have different
	    // ObjRelativeTo information (e.g. v14 DMU1_2LM6 required one muon
	    // at L2, but two at L3. Therefore we need different L3 efficiencies
	    // for the two muons. Therefore we create a separate entry in the
	    // trigger map for each object and force ObjRelativeTo into the
	    // proper setting given the conditions from earlier trigger levels.
	    for (int itrigcond=0; itrigcond<_trigcond.size(); itrigcond++) {
	      stringstream map_name;
	      map_name << flag_name.str() << "_Trigcond" << itrigcond;

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
                tmp.push_back("dummy"); 
              } 
             
	      if ( flag == "TriggerVersionLow" && tmp.size() == 0 ) {
		tmp.push_back("99");
	      }
	    
	      if ( flag == "ObjRelativeTo" ) {
		if (tmp.size()>0) {
		  cout << name << " ERROR: must not specify ObjRelativeTo "
		       << "in config file." << endl;
		  exit(1);
		}
		stringstream relativeto;
		if ( object == "Track" ) {
		  relativeto << _track_quality;
		}
		else if (object == "Isolation") {
		  if(_iso_quality != "none") relativeto << _iso_quality;
		}
		else {
		  relativeto << _muon_quality;
		}
		for (int iprev=0; iprev<m; iprev++) {
		  if (_trigcond[itrigcond][iprev]) {
		    stringstream prevflagname;
		    prevflagname << _level[iprev] << object
				 << "ObjQuality_" << version << detector
				 << "_Trigcond" << itrigcond;
		    if (_trigger_map[prevflagname.str()][0]!="dummy") {
		      relativeto << "_" << _trigger_map[prevflagname.str()][0];
		    }
		  }
		}
		// very special case: the L3 muon-track match (muon_cm tool)
		if ( object == "Match" ) {
		  for (int iprev=0; iprev<m; iprev++) {
		    stringstream prevflagname;
		    prevflagname << _level[iprev] << "Muon"
				 << "ObjQuality_" << version << detector
				 << "_Trigcond" << itrigcond;
		    if (_trigger_map[prevflagname.str()][0]!="dummy") {
		      relativeto << "_" << _trigger_map[prevflagname.str()][0];
		    }
		  }
		  relativeto << "_l3l0_l3trkxh10";
		}
		tmp.push_back(relativeto.str());
	      }

              if ( flag == "ObjType" && tmp.size() == 0 ) {
                if (object == "Track" || object == "Match" || object == "Isolation") {
                  tmp.push_back("Muon");
                }
                else {
                  tmp.push_back(object);
                }
              }
	  
	      if ( flag == "Source" && tmp.size() == 0 ) {
		tmp.push_back("muo_cert");
	      }

	      _trigger_map[map_name.str()] = tmp;
	    }
	  }
	}
      }
    }
  }
  */

  //------------------------------------
  // "Systematic" calculation
  //------------------------------------
  
  _systematic = config.get("Systematic", "nominal");
  if (_systematic == "plus")    _sigma = +1.0; 
  if (_systematic == "nominal") _sigma =  0.0;
  if (_systematic == "minus")   _sigma = -1.0;

  out() << "Probability_nMuon systematics setting is " << _systematic 
        << "\nThe value of sigma is set to             " << _sigma  << endl;

}
    
//EffInfo terms are defined here
void Probability_nMuon::defineEffInfo(map< string, eff_utils::EffInfo >& _effInfo)
{

  if(_debug) cout<<">>> Probability_nMuon::defineEffInfo(...) <<<"<<endl;
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

	  for (int itrigcond=0; itrigcond<_trigcond.size(); itrigcond++) {
	    stringstream do_name;
	    do_name << level << object << "AddToEffUtils_" << version
		    << detector << "_Trigcond" << itrigcond;
	    if ( _trigger_map[do_name.str()][0] == "yes" ) {
	      stringstream effInfoName;
	      effInfoName << level << object << "_" << version << detector
			  << "_Trigcond" << itrigcond;
	      
	      for ( int j = 0; j < _flags.size(); j++ ) {
		string flag = _flags[j];
	      
		stringstream flag_name;
		flag_name << level << object << flag << "_" << version
			  << detector << "_Trigcond" << itrigcond;
		vector<string> eff_utils_variable = _trigger_map[flag_name.str()];
	      
	      
		if ( flag == "EffName" ) {
		  _effInfo[effInfoName.str().c_str()].EffName(eff_utils_variable[0]);
		} else if ( flag == "EffVarNames" ) {
		  _effInfo[effInfoName.str().c_str()].EffVarNames(eff_utils_variable);
		} else if ( flag == "EffType" ) {
		  _effInfo[effInfoName.str().c_str()].EffType(eff_utils_variable[0]);
		} else if ( flag == "ObjQuality" ) {
		  _effInfo[effInfoName.str().c_str()].ObjQuality(eff_utils_variable[0]);
		} else if ( flag == "ObjRelativeTo" ) {
		  _effInfo[effInfoName.str().c_str()].ObjRelativeTo(eff_utils_variable[0]);
		} else if ( flag == "ObjType" ) {
		  _effInfo[effInfoName.str().c_str()].ObjType(eff_utils_variable[0]);
		} else if ( flag == "TriggerVersionLow" ) {
		  _effInfo[effInfoName.str().c_str()].TriggerVersionLow(eff_utils_variable[0]);
		} else if ( flag == "TriggerVersionHigh" && eff_utils_variable.size() != 0 ) {
                  _effInfo[effInfoName.str().c_str()].TriggerVersionHigh(eff_utils_variable[0]);
		} else if ( flag == "AddToEffUtils" ) {
		  // ignore this. this flag is only used for internal purposes
		} else {
		  cout << name() << " ERROR: internal inconsistency. Ignoring "
		       << flag << endl;
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
  
//--------------------------------------
// The actual probability calculations are defined here and after calcProb
//--------------------------------------
double Probability_nMuon::calcProb(string version)
{
  // bit values used to identify the trigger conditions
  const int cond0 = 1;
  const int cond1 = 2;

  // for each muon: get probability to fire condition 0 only, condition 1 only,
  // condition 0 and 1, and neither 0 nor 1
  map<string,map<int,EffVal> > weightvals;
  double muonprobs[NMU][4];
  map<string,map<int,double> > muonprobs_deriv[NMU][4];
  for (int iobj=0; iobj<NMU; iobj++) {
    // get probabilities (plus information required for uncertainty
    // determination) for this muon to pass the two trigger criteria
    double prob[2];
    map<string,map<int,double> > derivatives[2];
    for (int itrigcond=0; itrigcond<2; itrigcond++) {
      map<string,EffVal> weightmap;
      prob[itrigcond]=Prob_Muon(version,itrigcond,iobj,weightmap);
      // make sure that all correction weights used in this calculation
      // are stored for later use in uncertainty determination
      for (map<string,EffVal>::iterator it=weightmap.begin();
	   it!=weightmap.end(); it++) {
	string eff_identifier=(*it).first;
	// warning: this is a temporary fix for DMU1_2LM6
	if (eff_identifier=="Muon_l3l6_loose_l1atxx") {
	  eff_identifier="Muon_l3l6_loose_l1atxx_l2m0";
	}
	// temporary fix end
	int &binno=(*it).second.binno;
	// store EffVal object
	weightvals[eff_identifier][binno]=(*it).second;
	// partial derivatives: d(x*y*z)/dx=y*z
        // (each correction weight taken from different efficiency
	// parameterisation, therefore assume all to be independent)
	derivatives[itrigcond][eff_identifier][binno]=1.0;
	for (map<string,EffVal>::iterator it2=weightmap.begin();
	     it2!=weightmap.end(); it2++) {
	  if (it2!=it) {
	    derivatives[itrigcond][eff_identifier][binno]*=(*it2).second.val;
	  }
	}
      }
    }
    // reminder: cond1 is a subset of the conditions required for cond0.
    // thus, whenever an object fulfils cond0, it automatically fulfils cond1.
    // conversely, if it does not fulfil cond1, it does not fulfil cond0 either.
    muonprobs[iobj][cond0+cond1]=prob[0];
    muonprobs[iobj][cond1]=0;
    muonprobs[iobj][cond0]=prob[1]-prob[0];
    muonprobs[iobj][0]=1-prob[1];
    // derive partial derivatives of muonprobs[][] from prob[] derivatives
    for (map<string,map<int,EffVal> >::iterator eff_it=weightvals.begin();
	 eff_it!=weightvals.end(); eff_it++) {
      const string &eff_identifier=(*eff_it).first;
      map<int,EffVal> &eff_map=(*eff_it).second;
      for (map<int,EffVal>::iterator bin_it=eff_map.begin();
	   bin_it!=eff_map.end(); bin_it++) {
	const int &eff_binno=(*bin_it).first;
	muonprobs_deriv[iobj][cond0+cond1][eff_identifier][eff_binno]=
	  derivatives[0][eff_identifier][eff_binno];
	muonprobs_deriv[iobj][cond1][eff_identifier][eff_binno]=0;
	muonprobs_deriv[iobj][cond0][eff_identifier][eff_binno]=
	  derivatives[1][eff_identifier][eff_binno]
	  -derivatives[0][eff_identifier][eff_binno];
	muonprobs_deriv[iobj][0][eff_identifier][eff_binno]=
	  -derivatives[1][eff_identifier][eff_binno];
      }
    }

    // print intermediate results: weights for each muon for each
    // specific combination of passing/failing the two trigger conditions,
    // plus the partial derivatives of those probabilities with respect
    // to all contributing efficiency weights
    if (_debug) {
      for (int itrigcomb=0; itrigcomb<4; itrigcomb++) {
	cout << "Probability_nMuon: muon " << iobj << " trigcomb "
	     << itrigcomb << ": " << muonprobs[iobj][itrigcomb] << endl;
	cout << "  partial derivatives:" << endl;
	for (map<string,map<int,EffVal> >::iterator eff_it=weightvals.begin();
	     eff_it!=weightvals.end(); eff_it++) {
	  const string &eff_identifier=(*eff_it).first;
	  map<int,EffVal> &eff_map=(*eff_it).second;
	  for (map<int,EffVal>::iterator bin_it=eff_map.begin();
	       bin_it!=eff_map.end(); bin_it++) {
	    const int &eff_binno=(*bin_it).first;
	    cout << "   with respect to " << eff_identifier << ", bin "
		 << eff_binno << ": "
		 << muonprobs_deriv[iobj][itrigcomb][eff_identifier][eff_binno]
		 << endl;
	  }
	}
      }
    }
  }

  // prepare the correction weight vectors to be passed to later processors,
  // so we can sum up the corresponding partial derivatives in the following
  // part of this code
  for (map<string,map<int,EffVal> >::iterator eff_it=weightvals.begin();
       eff_it!=weightvals.end(); eff_it++) {
    const string &eff_identifier=(*eff_it).first;
    map<int,EffVal> &eff_map=(*eff_it).second;
    for (map<int,EffVal>::iterator bin_it=eff_map.begin();
	 bin_it!=eff_map.end(); bin_it++) {
      const int &eff_binno=(*bin_it).first;
      if (_debug) cout << name() << ": efficiency vector " << eff_identifier
		       << " push_back " << (*bin_it).second.val << endl;
      _corrfactors[eff_identifier].push_back((*bin_it).second);
      _derivatives[eff_identifier].push_back(0);
    }
  }

  // now do the event weight combinatorics.
  // we have 4^NMU combinations of probabilities.
  // we need to sum the probabilities for all configurations where
  // at least one object fires cond0 and at least one other object fires
  // cond1.
  double totalProb = 0;
  if (_debug) cout << "Probability_nMuon: checking 4^NMU=" << (1<<(2*NMU))
		   << " combinations of probabilities" << endl; 
  for (int icase=0; icase<(1<<(2*NMU)); ++icase) {
    double caseProb=1.0;
    int nfired0=0,nfired1=0,nobjfired=0;
    if (_debug) cout << "Probability_nMuon: combination "; 
    for (int iobj=0; iobj<NMU; ++iobj) {
      int trigcomb=(icase/(1<<(2*iobj)))&3;
      if (_debug) cout << trigcomb;
      caseProb*=muonprobs[iobj][trigcomb];
      if (trigcomb) ++nobjfired;
      if (trigcomb & cond0) ++nfired0;
      if (trigcomb & cond1) ++nfired1;
    }
    if (nfired0>0 && nfired1>0 && nobjfired>=_num_nonempty_trigconds) {
      if (_debug) {
	cout << ": probability " << caseProb << endl;
      }
      totalProb+=caseProb;
      // calculate partial derivatives of total event weight with respect
      // to all contributing efficiency weights
      for (map<string,map<int,EffVal> >::iterator eff_it=weightvals.begin();
	   eff_it!=weightvals.end(); eff_it++) {
	const string &eff_identifier=(*eff_it).first;
	map<int,EffVal> &eff_map=(*eff_it).second;
	for (int i=0; i<_corrfactors[eff_identifier].size(); i++) {
	  const int &eff_binno=_corrfactors[eff_identifier][i].binno;
	  double thisweight=_corrfactors[eff_identifier][i].val;
	  // calculate derivative for weight eff_identifier bin eff_binno
	  double deriv=1;
	  int n_found=0;
	  for (int iobj=0; iobj<NMU; iobj++) {
	    int trigcomb=(icase/(1<<(2*iobj)))&3;
	    double thisderiv=muonprobs_deriv[iobj][trigcomb][eff_identifier][eff_binno];
	    if (thisderiv!=0) {
	      ++n_found;
	      deriv*=thisderiv;
	    } else {
	      deriv*=muonprobs[iobj][trigcomb];
	    }
	  }
          // if the same weight appears n times (n>1) in the same product,
	  //  then, rather than multiply with dw/dx, we should have multiplied
	  // by d(w^n)/dx = (dw^n/dw)*(dw/dx) = nw^(n-1)*(dw/dx). Therefore,
	  // to fix what we did wrong, we have to multiply by nw^(n-1) here.
	  // This does only work because all muonprobs weights depend
	  // linearly on the individual efficiency weights.
	  if (n_found>1) deriv*=n_found*pow(thisweight,n_found-1);
	  _derivatives[eff_identifier][i]+=deriv;
	}
      }
    } else if (_debug) {
      cout << ": not enough objects firing trigger" << endl;
    }
  }

  if (_debug) {
    cout << "Probability_nMuon: event probability = " << totalProb << endl;
    for (map<string,vector<EffVal> >::iterator it=_corrfactors.begin();
	 it!=_corrfactors.end(); it++) {
      cout << "  weights contributed by " << (*it).first << ":" << endl;
      vector<EffVal> &values = (*it).second;
      for (int i=0; i<values.size(); i++) {
	cout << "   bin " << values[i].binno << ", weight " << values[i].val
	     << " +-" << values[i].ehi << "/" << values[i].elo
	     << ", event weight partial derivative "
	     << _derivatives[(*it).first][i] << endl;
      }
    }
    cout << endl;
  }

  return totalProb;
}


//------------------------------------------------------------------------------
// This calculates the trigger probability
// P(muon,track) = P(muon) * P(track)
//------------------------------------------------------------------------------
double Probability_nMuon::Prob_Muon(string version, int itrigcond, int iobj,
				    map<string,EffVal> &weightstore){

  double probproduct=1;

  for ( int m = 0; m < _level.size(); m++ ) {
    string level = _level[m];
    // if this level is not used in this specific trigger condition, skip it
    if (!_trigcond[itrigcond][m]) continue;
     
    for ( int i = 0; i < _location.size(); i++ ) {
      string detector = _location[i];

      for ( int k = 0 ; k < _object.size(); k++ ) {
	string object = _object[k];
	
	stringstream do_name; 
	do_name << level << object << "AddToEffUtils_" << version << detector
		<< "_Trigcond" << itrigcond;

	if ( _trigger_map[do_name.str()][0] == "yes" ) {
	 
	  stringstream effInfoName;
	  effInfoName << level << object << "_" << version << detector
		      << "_Trigcond" << itrigcond;
	 
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
	  EffVal eff;
	  float val;
	  if ( object == "Track" ) {
	     const TMBTrack *muon_track = MU[iobj].GetChargedTrack();
	     if ( muon_track == NULL ) {
	       val = 0.0;
	     }
	     else {
	       val = prob->getProbability(*muon_track, uncertainty, eff, isRun2b, _debug);
	     }
	  }
	  else {
	    //	    val = prob->getProbability(MU[iobj], uncertainty, eff, isRun2b, _debug, NJET);
	    val = prob->getProbability(MU[iobj], uncertainty, eff, isRun2b, _debug, NJET, INSTLUM);
	    //	    val = prob->getProbability(MU[iobj], uncertainty, eff, isRun2b, _debug);
	  }
	  
	  if (_debug) {
	    cout << "Probability_nMuon::Prob_Muon probability " << object
		 << " " << iobj << " trigcond " << itrigcond << " level "
		 << m+1 << ": " << val << endl;
	  }
	  if (val<0) val=0;
	  probproduct*=val;
	  string eff_identifier = prob->Info()->ObjType()+"_"
	    +prob->Info()->ObjQuality()+"_"
	    +prob->Info()->ObjRelativeTo();
	  weightstore[eff_identifier]=eff;
	}
      }
    }
  }

  //------------------------------------
  // Make sure the probability is [0,1]
  //------------------------------------
  if(probproduct > 1.0) {
    cout << name() << " ERROR: muon probability " << probproduct << endl;
    probproduct = 1.0;
  }
  else if(probproduct < 0.0) {
    cout << name() << " ERROR: muon probability " << probproduct << endl;
    probproduct = 0.0;
  }
  
  return probproduct;
}



void  Probability_nMuon::change_triggermap() {

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
    cout<<"doing change for "<<version<<endl;
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
	    flag_name << level << object
		      << flag << "_" << version << detector;

	    // For dimuon triggers the two trigger conditions may have different
	    // ObjRelativeTo information (e.g. v14 DMU1_2LM6 required one muon
	    // at L2, but two at L3. Therefore we need different L3 efficiencies
	    // for the two muons. Therefore we create a separate entry in the
	    // trigger map for each object and force ObjRelativeTo into the
	    // proper setting given the conditions from earlier trigger levels.
	    for (int itrigcond=0; itrigcond<_trigcond.size(); itrigcond++) {
	      stringstream map_name;
	      map_name << flag_name.str() << "_Trigcond" << itrigcond;

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
                tmp.push_back("dummy"); 
              } 
             
	      if ( flag == "TriggerVersionLow" && tmp.size() == 0 ) {
		tmp.push_back("99");
	      }
	    
	      if ( flag == "ObjRelativeTo" ) {
		if (tmp.size()>0) {
		  cout << name() << " ERROR: must not specify ObjRelativeTo "
		       << "in config file." << endl;
		  exit(1);
		}
		stringstream relativeto;
		if ( object == "Track" ) {
		  relativeto << _track_quality;
		}
		else if (object == "Isolation") {
		  if(_iso_quality != "none") relativeto << _iso_quality;
		}
		else {
		  relativeto << _muon_quality;
		}
		for (int iprev=0; iprev<m; iprev++) {
		  if (_trigcond[itrigcond][iprev]) {
		    stringstream prevflagname;
		    prevflagname << _level[iprev] << object
				 << "ObjQuality_" << version << detector
				 << "_Trigcond" << itrigcond;
		    if (_trigger_map[prevflagname.str()][0]!="dummy") {
		      relativeto << "_" << _trigger_map[prevflagname.str()][0];
		    }
		  }
		}
		// very special case: the L3 muon-track match (muon_cm tool)
		if ( object == "Match" ) {
		  for (int iprev=0; iprev<m; iprev++) {
		    stringstream prevflagname;
		    prevflagname << _level[iprev] << "Muon"
				 << "ObjQuality_" << version << detector
				 << "_Trigcond" << itrigcond;
		    if (_trigger_map[prevflagname.str()][0]!="dummy") {
		      relativeto << "_" << _trigger_map[prevflagname.str()][0];
		    }
		  }
		  relativeto << "_l3l0_l3trkxh10";
		}
		tmp.push_back(relativeto.str());
	      }

              if ( flag == "ObjType" && tmp.size() == 0 ) {
                if (object == "Track" || object == "Match" || object == "Isolation") {
                  tmp.push_back("Muon");
                }
                else {
                  tmp.push_back(object);
                }
              }
	  
	      if ( flag == "Source" && tmp.size() == 0 ) {
		tmp.push_back("muo_cert");
	      }

	      _trigger_map[map_name.str()] = tmp;
	    }
	  }
	}
      }
    }
  }

 
}

ClassImp(Probability_nMuon)


