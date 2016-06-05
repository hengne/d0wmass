//file: probProcessor.cpp {probProcessor.hpp, probProcessor_linkdef.h}
//
//Author:   Kevin Chan
//
//Purpose:  Processor plug in processor for calculating the event 
//          weights and the total weights. It is the base class for
//          all of the probability processors.
//
//Usage:
//
//Example:

//Header file for this class
#include "caf_trigger/probProcessor.hpp"
#include "caf_mc_util/MCReqID.hpp"
#include <map>

using namespace std;
using namespace cafe;

extern caf_mc_util::MCReqID *MCREQID;

probProcessor::probProcessor(const char *name)
  : Processor(name), _reqid(1)
{

    //We grab terms from the CAFe configuration file here
    Config config(name);

    // Debug
    string debug = config.get("Debug", "no");
    _debug = ( debug == "yes" );

    //----------------------------------
    // Get a path if we need it
    //----------------------------------
    _path = config.get("Path", "./general_path_not_found");

    //----------------------------------
    // Get a track path if we need it
    //----------------------------------
    _path_track = config.get("TrackPath", "./track_path_not_found");

    //----------------------------------
    // Get a electron path if we need it
    //----------------------------------
    _path_electron = config.get("ElectronPath", "./electron_path_not_found");

    //----------------------------------
    // Get a muon path if we need it
    //----------------------------------
    _path_muon = config.get("MuonPath", "./muon_path_not_found");

    //----------------------------------
    // Get a muon OR path if we need it
    //----------------------------------
    _path_muor = config.get("MuonORPath", "./muor_path_not_found");

   //----------------------------------
    // Get a jet path if we need it
    //----------------------------------
    _path_jet = config.get("JetPath", "./jet_path_not_found");

    //----------------------------------
    // Get a eleJet path if we need it
    //----------------------------------
    _path_eleJet = config.get("EleJetPath", "./elejet_path_not_found");
    
    //----------------------------------
    // Get a tau path if we need it
    //----------------------------------
    _path_tau = config.get("TauPath", "./tau_path_not_found");
    
    //The sigma calculations
    _sigma = config.get("sigma", "false");


    _sigmaValue.push_back(-1.0);
    _sigmaValue.push_back(1.0);


    //------------------------------------
    // Get the list of trigger versions
    //------------------------------------
    // This is done in change_request(), but have to leave this here or
    // other triggers break.
    //_trigger_version = config.getVString("TriggerVersions", ",");
    // NO! Don't use _trigger_version! Use _mapVersionLumi provided by cafTriggerEfficiency!!!

    //------------------------------------
    // Under(over)flow treatment
    //------------------------------------
    _ignoreOverflow = config.get("ignoreOverflow",false);
    _ignoreUnderflow = config.get("ignoreUnderflow",false);
    
    
    //------------------------------------
    // JetActAs Setting
    //------------------------------------
    _Jet_ActAs_map["Disabled"]    = -1;
    _Jet_ActAs_map["UnCorrected"]    = 0;
    _Jet_ActAs_map["JESCorrected"]   = 1;
    _Jet_ActAs_map["JESCorrectedShiftedPlus"]  = 2;
    _Jet_ActAs_map["JESCorrectedShiftedMinus"] = 3;
    _Jet_ActAs_map["JESMUCorrected"] = 4;
    _Jet_ActAs_map["JESMUCorrectedShiftedPlus"]  = 5;
    _Jet_ActAs_map["JESMUCorrectedShiftedMinus"] = 6;
    _Jet_ActAs_map["Smeared"]        = 7;
    _Jet_ActAs_map["SmearedMU"]      = 8;
     
    
    string JES = config.get("JetActAs", "Smeared");
    cout << ">>>>>>> " << name << " : JetActAs is set to be \"" << JES << "\", " << _Jet_ActAs_map[JES] << endl;
    switch ( _Jet_ActAs_map[JES] ) {
	case -1:
		cout << "WARNING: JetActAs switch is disabled, jet trigger turn-ons will be applied with UNKNOWN JES correction stage, are you sure you want this?" << endl;
		JetActAs = -1;
		break; 
	case  0:
		cout << "Assume jet trigger turn-ons measured w.r.t. UNCORRECTED pT, please check if that is the case." << endl;
		JetActAs = 0;
		break;
	case  1:
		cout << "Assume jet trigger turn-ons measured w.r.t. JES CORRECTED pT, please check if that is the case." << endl;
		JetActAs = 1;
		break;
	case  2:
		cout << "Assume jet trigger turn-ons measured w.r.t. JES CORRECTED pT + ShiftedPlus, please check if that is the case." << endl;
		JetActAs = 2;
		break;
	case  3:
		cout << "Assume jet trigger turn-ons measured w.r.t. JES CORRECTED pT + ShiftedMinus, please check if that is the case." << endl;
		JetActAs = 3;
		break;
	case  4:
		cout << "Assume jet trigger turn-ons measured w.r.t. Muon JES CORRECTED pT, please check if that is the case." << endl;
		JetActAs = 4;
		break;  
	case  5:
		cout << "Assume jet trigger turn-ons measured w.r.t. Muon JES CORRECTED pT + ShiftedPlus, please check if that is the case." << endl;
		JetActAs = 5;
		break; 
	case  6:
		cout << "Assume jet trigger turn-ons measured w.r.t. Muon JES CORRECTED pT + ShiftedMinus, please check if that is the case." << endl;
		JetActAs = 6;
		break;  
	case  7:
		cout << "Assume jet trigger turn-ons measured w.r.t. Smeared JES CORRECTED pT, please check if that is the case." << endl;
		JetActAs = 7;
		break;  
	case  8:
		cout << "Assume jet trigger turn-ons measured w.r.t. Smeared Muon JES CORRECTED pT, please check if that is the case." << endl;
		JetActAs = 8;
		break; 
	default:
		cout << "Invalid JetActAs Setting: " << _Jet_ActAs_map[JES] << endl;
		exit(1);
		break;
   }

  // Initialize intermediate trigger weights    
  _savedweights.prob = 0.0 ;
  _savedweights.prob1 = 0.0 ;
  _savedweights.prob2 = 0.0 ;
  _saveweights = false ;
	
}

//begin() calls defineEffInfo() which will set up the effInfo objects <= Obsolete, with multi-epoch processing effInfo will be set up in change_request() -Joe
void probProcessor::begin()
{
  //  Everything that was here is now done in change_request()
}

void probProcessor::finish()
{
  PrintEfficiency();
}


//----------------------------------------------------------
// If we have a specific path for each turn on curve
//----------------------------------------------------------
string probProcessor::DeterminePath(string name) {
  if ( name.find("MuonOR") != string::npos || name.find("muonOR") != string::npos ) {
    return( _path_muor );
  }
  else if ( name.find("Muon") != string::npos || name.find("muon") != string::npos ) {
    return( _path_muon );
  }
  else if ( name.find("Electron") != string::npos || name.find("electron") != string::npos ) {
    return( _path_electron );
  }
  else if ( name.find("EleJet") != string::npos ) {
    return( _path_eleJet );
  }
  else if ( name.find("Jet") != string::npos || name.find("jet") != string::npos ) {
    return( _path_jet );
  }
  else if ( name.find("Tau") != string::npos || name.find("tau") != string::npos ) {
    return( _path_tau );
  }
  else if ( name.find("Track" ) != string::npos ) {
    return( _path_track );
  }
  else {
    return( _path );
  }
}

//Returns the probability defined earlier
const objectProbabilities *probProcessor::probObject(const string &name) const {
  
  //Creates an iterator to find the object given a string
  map<string, objectProbabilities>::const_iterator it = _objectProb.find(name);
  
  
  if (it == _objectProb.end()) {
    cout << "Could not find EffInfo object" << endl;
    cout << "Here are all the available objects:" << endl;
    for ( map<string, objectProbabilities>::const_iterator iter = _objectProb.begin(); iter != _objectProb.end(); iter++ ) {
      cout << iter->first << endl;
    }

    return 0;
  }
  
  return &(it->second);
}


void probProcessor::eventWeight(map<string, double> &mRefEvtw)
{
    //Create variables to hold temporary trigger weights and luminosities
    double nevtw = 0.0;
    double nevtw1 = 0.0;
    double nevtw2 = 0.0;
    double dlumi = 0.0;
    double dlumi1 = 0.0;
    double dlumi2 = 0.0;
    double revtw = 0.0;
    double revtw1 = 0.0;
    double revtw2 = 0.0;


    //We set the object probabilities for sigmas
    for(map<string, objectProbabilities>::const_iterator itProb = _objectProb.begin(); itProb != _objectProb.end(); ++itProb) {

        mSigma.clear();

        _objectProb[itProb->first].setSigma( mSigma );
    }

    if (_triggerPeriod == "none") {
      // (*it).first = version, (*it).second = lumi
      for(map<string, float>::iterator it = _mapVersionLumi.begin(); it != _mapVersionLumi.end(); ++it) {
        
        //We run through the variables and save it in the evtw vector
        //that we created earlier. At this stage, they shall be luminosity
        //weighted in order to be sent to the next processor.

	//cout<<"So I think it's here:  calling calcProb for version "<<(*it).first<<endl;


	if ( ! _saveweights ) {
        	nevtw += calcProb( (*it).first ) * (*it).second;
        }
	else {
		double prob = calcProb( (*it).first );
		if ( prob != _savedweights.prob ) {
			std::cerr << "caf_trigger::probProcessor internal error, savedweights.prob != prob : " << _savedweights.prob << " != " << prob << std::endl;
			exit(1);
		}
		nevtw += prob * (*it).second;
		nevtw1 += _savedweights.prob1 * _mapVersionLumi1[ (*it).first ];
		nevtw2 += _savedweights.prob2 * _mapVersionLumi2[ (*it).first ];
	}
        dlumi += (*it).second;
        dlumi1 += _mapVersionLumi1[ (*it).first ];
        dlumi2 += _mapVersionLumi2[ (*it).first ];
      }

      revtw = nevtw/dlumi;
      revtw1 = nevtw1/dlumi1;
      revtw2 = nevtw2/dlumi2;

    } else {
      revtw = calcProb(_triggerPeriod);
    }

    mRefEvtw[_channel] = revtw;
    if ( _saveweights ) {
    	mRefEvtw[_channel1] = revtw1;
    	mRefEvtw[_channel2] = revtw2;
    }
}

void probProcessor::eventWeightSigma(map<string, double> &mRefEvtw)
{
    //This for loop goes through the sigma values
    for(int iValue = 0; iValue < 2; ++iValue) {

        //We need to convert the sigma values to a string
        //using <sstream> and <iostream>
        stringstream convertSigmaValue;
        convertSigmaValue << _sigmaValue[iValue];

        string mapName, mapName1, mapName2;
                
        if(_sigmaValue[iValue] == 1.0) {

            mapName = _channel + " Sigmas: " + "+" + convertSigmaValue.str();
            mapName1 = _channel1 + " Sigmas: " + "+" + convertSigmaValue.str();
            mapName2 = _channel2 + " Sigmas: " + "+" + convertSigmaValue.str();

        }
        else {
                
            mapName = _channel + " Sigmas: " + convertSigmaValue.str();
            mapName1 = _channel1 + " Sigmas: " + convertSigmaValue.str();
            mapName2 = _channel2 + " Sigmas: " + convertSigmaValue.str();

        }

        //This variable is created for the addition in quadrature
        sigmaQuad quadrature = sigmaQuad();
        sigmaQuad quadrature1 = sigmaQuad();
        sigmaQuad quadrature2 = sigmaQuad();
        
        //This for loop goes through the _sigmaStrings set earlier
        for(int iObj = 0; iObj < _sigmaStrings.size(); ++iObj) {

            //Create a variable to hold the temporary event weights
            //and one to hold the total luminosities.
            double nevtw = 0.0;
            double nevtw1 = 0.0;
            double nevtw2 = 0.0;
            double dlumi = 0.0;
            double dlumi1 = 0.0;
            double dlumi2 = 0.0;

            // (*it).first = version, (*it).second = lumi
            //For each of the version of the triggerlist
            for(map<string, float>::iterator it = _mapVersionLumi.begin(); it != _mapVersionLumi.end(); ++it) {


                //We clear the sigma variable
                mSigma.clear();

                //Then set it to what we require
                mSigma[ _sigmaStrings[iObj] ] = _sigmaValue[iValue];

                //We set the object probabilities for sigmas
                for(map<string, objectProbabilities>::const_iterator itProb = _objectProb.begin(); itProb != _objectProb.end(); ++itProb) {

                    _objectProb[itProb->first].setSigma( mSigma );
                }

                //We run through the variables and save it in the 
                //evtw vector that we created earlier. At this stage,
                //they shall be luminosity
                //weighted in order to be sent to the next processor.
		if ( ! _saveweights ) {
        		nevtw += calcProb( (*it).first ) * (*it).second;
        	}
		else {
			double prob = calcProb ( (*it).first );
			if ( prob != _savedweights.prob ) {
				std::cerr << "caf_trigger::probProcessor internal error, savedweights.prob != returned probability: " << _savedweights.prob << " != " << prob << std::endl;
				exit(1);
			}
			nevtw += prob * (*it).second;
			nevtw1 += _savedweights.prob1 * _mapVersionLumi1[ (*it).first ];
			nevtw2 += _savedweights.prob2 * _mapVersionLumi2[ (*it).first ];
		}

                dlumi += (*it).second;
        	dlumi1 += _mapVersionLumi1[ (*it).first ];
        	dlumi2 += _mapVersionLumi2[ (*it).first ];
            }
        

            //Input into the object, the current number
            quadrature.sigmaAddQuad(nevtw/dlumi);
            quadrature1.sigmaAddQuad(nevtw1/dlumi1);
            quadrature2.sigmaAddQuad(nevtw2/dlumi2);
            
        
        }//endfor(iObj)
            
        //Finish the addition in quadrature by square rooting the values
        double revtw = quadrature.sigmaGetQuad();
        double revtw1 = quadrature1.sigmaGetQuad();
        double revtw2 = quadrature2.sigmaGetQuad();

        //And putting it in the referenced map
        mRefEvtw[ mapName ] = revtw;
	if ( _saveweights ) {
        	mRefEvtw[ mapName1 ] = revtw1;
        	mRefEvtw[ mapName2 ] = revtw2;
        }

    }//endfor(iValue)


}

void probProcessor::sigmaSet(map< string, EffInfo > effInfoPass)
{
    //Run through the passed EffInfo to set the sigmas
    for(map< string, EffInfo >::iterator it = effInfoPass.begin(); it != effInfoPass.end(); ++it) {

      //      cout << "sigmaSet: " << (*it).second.EffName() << "\t" << (*it).first << endl;
        
        //Strings to place into mSigma
        string effInfoLevel;
        string mSigmaString;

        //We set the level string
        if ( (*it).second.EffName().find("L1") < (*it).second.EffName().size() ||
            (*it).second.EffName().find("l1") < (*it).second.EffName().size() )         {
            effInfoLevel = "L1";
        }
        else if ( (*it).second.EffName().find("L2") < (*it).second.EffName().size() ||
            (*it).second.EffName().find("l2") < (*it).second.EffName().size() ) 
        {
            effInfoLevel = "L2";
        }
        else if ( (*it).second.EffName().find("L3") < (*it).second.EffName().size() ||
            (*it).second.EffName().find("l3") < (*it).second.EffName().size() ) 
        {
            effInfoLevel = "L3";
        }

        //Now we set the mSigmaString to place into the mSigma map
        mSigmaString = (*it).second.ObjType() + " " + effInfoLevel;
        bool sigmaStringSet = false;
        
        //And now we test to see if it's already been set
        for(int idup = 0; idup < _sigmaStrings.size(); ++idup) {
            if( _sigmaStrings[idup].find(mSigmaString) < _sigmaStrings[idup].size() ) {
                
                sigmaStringSet = true;
            }
        
        }

        if(sigmaStringSet == false) {
            _sigmaStrings.push_back(mSigmaString);
        
	    //            cout << "Sigma Calculation for: " << mSigmaString << endl;
        }

    }

}

bool probProcessor::processEvent(Event &event)
{
    //Run2b switch
    evtno = event.getGlobal()->evtno();
    runno = event.getGlobal()->runno();
    isRun2b = event.isRun2b();  // needed because some jet eta def changed between Run2a and Run2b, fine.

    change_request(event);
    if(_debug){
      cout<<"trigger version now has "<< _trigger_version.size()<<" entries."<<endl;
      cout<<"triglists: ";
      for (int i=0; i < _trigger_version.size(); i++) cout<<_trigger_version[i]<<" ";
      cout<<endl;
    }
    //First we use a created a map to grab the possibly empty information from
    //the previous processor, and grab this information
    mEvtw.clear();
    event.get("passedEvtw", mEvtw);

    _corrfactors.clear();
    _derivatives.clear();

    //Get the passed TObject information
    event.get("passedEM", EM);
    event.get("passedMU", MU);
    event.get("passedJET", JET);
    event.get("passedMET", MET);
    event.get("passedTAU", TAU);

    event.get("passedNEM", NEM);
    event.get("passedNMU", NMU);
    event.get("passedNJET", NJET);
    event.get("passedNTAU", NTAU);
    event.get("passedINSTLUM",INSTLUM);

    // decide whether to weight the periods, or simply pick one
    _triggerPeriod = "none";
    event.get("TriggerPeriod", _triggerPeriod);

    //We grab the stats pointer from the event
    //event.get("StatPointer", _stat);

    //Now we run through the map of the triggerlist version and luminousity
    //and calculate the probabilities.
    //This calls calcProb(version) which acts as the heart of the calculations.
    //Note: mEvtw[_channel] is set internally in this method.
    eventWeight(mEvtw);
    

    //If the user wishes outputs using the sigma variations in the event,
    //this will call calcProb(version) with the appropriate sigma variations.
    //Note: mEvtw[_channel sigma] is set internally in this method.
    if(_sigma != "false") {

        eventWeightSigma(mEvtw);
    }

    //Now we put these values into the event.
    event.put("passedEvtw", mEvtw);

    //Pass full object weight information to event
    //(needed for evaluation of efficiency uncertainties)
    vector<string> weightnames,derivnames;
    for (map<string, vector<EffVal> >::iterator it = _corrfactors.begin();
	 it!=_corrfactors.end(); it++) {
      if (it->second.size()>0) {
	event.put(name()+":weight_vector_"+it->first,it->second);
	weightnames.push_back(name()+":weight_vector_"+it->first);
	derivnames.push_back(name()+":derivative_vector_"+it->first);
      }
    }
    for (map<string, vector<double> >::iterator it = _derivatives.begin();
	 it!=_derivatives.end(); it++) {
      if (it->second.size()>0) {
	event.put(name()+":derivative_vector_"+it->first,it->second);
      }
    }

    // add list of weight and derivative vectors provided by this processor
    // to list of weight and derivative vectors already stored by other
    // caf_trigger processors (if any)
    vector<string> existing_weightnames,existing_derivnames;
    if (event.get("caf_trigger_weight_vectors",existing_weightnames)) {
      weightnames.insert(weightnames.end(),existing_weightnames.begin(),
			 existing_weightnames.end());
    }
    if (event.get("caf_trigger_derivative_vectors",existing_derivnames)) {
      derivnames.insert(derivnames.end(),existing_derivnames.begin(),
			existing_derivnames.end());
    }
    event.put("caf_trigger_weight_vectors",weightnames);
    event.put("caf_trigger_derivative_vectors",derivnames);

    return true;
}



////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void probProcessor::change_request(Event& event){

  cafe::Config config(name());
  
  
  
  if (!MCREQID) throw runtime_error("ERROR:  processor MCReqID is not initialized.") ;
  
  // verify if request id is stay the same. In that case do nothing.
  
  if ( MCREQID->reqid() == _reqid ) return ;
  _reqid = MCREQID->reqid() ;
  
  // verify data epochs associated to this MC
  const vector<string>* epochs =  MCREQID->current_data_epochs();

  // Actually we could do better than just checking if the reqid changed,
  // if the current_data_epochs did not change we can also stop.
  // This is a little work, but much faster than rereading all trigger map
  bool same_epochs=true;
  if(_previous_epochs.size() == epochs->size()){
    for(int i=0; i<epochs->size(); i++){
      if(_previous_epochs[i] != epochs->at(i)){
	same_epochs=false;
	break;
      }
    }
  }else{
    same_epochs=false;
  }
  if(same_epochs) return;
  else{
    _previous_epochs.clear();
    for(int i=0; i<epochs->size(); i++) _previous_epochs.push_back(epochs->at(i));
  }


  //Get new maps of trigger versions and lumis (provided by cafTriggerEfficiency)
  _mapVersionLumi.clear();
  _mapVersionLumi1.clear();
  _mapVersionLumi2.clear();
  event.get("passedVersionLumi", _mapVersionLumi);
  event.get("passedVersionLumi1", _mapVersionLumi1);
  event.get("passedVersionLumi2", _mapVersionLumi2);


  //// This is a quick solution, but really _trigger_version and _trigger_lumi should be
  //// completely removed and only _mapVersionLumi should be used
  _trigger_version.clear();
  _trigger_lumi.clear();
  for(map<string, float>::iterator it = _mapVersionLumi.begin(); it != _mapVersionLumi.end(); ++it) {
    _trigger_version.push_back((*it).first);
    _trigger_lumi.push_back((*it).second);
  }


  if(_debug){ 
    cout<<"trigger version now has "<< _trigger_version.size()<<" entries. "<<endl; 
    cout<<"triglists: ";
    for (int i=0; i < _trigger_version.size(); i++) cout<<_trigger_version[i]<<" ";
    cout<<endl;
  }

  //// Update the trigger map (must be defined in children classes)
  // change_triggermap();
  // Moved to the beginning of defineEffInfo() define in child classes
  
  map< string, EffInfo > effInfo ;
  
  defineEffInfo(effInfo) ;
  
  //Set up the sigma variables with the effInfo
  sigmaSet(effInfo);
  
  for (map< string, EffInfo >::iterator it = effInfo.begin();
       it != effInfo.end(); it++) {
    
    //      cout << "Adding " << it->first << " to the map." << endl;
    //With our objectProb mapping, we fill it with the constructed objects
    string path = DeterminePath(it->first);
      
//       cout << endl << endl;
//       cout << "Prob:" << endl;
//       cout << "  " << it->first << endl;
//       cout << endl;
    
    _objectProb[it->first] = objectProbabilities(it->second, path, 
						 _ignoreOverflow, _ignoreUnderflow);
    
  }
  
}

ClassImp(probProcessor)

//endfile:
