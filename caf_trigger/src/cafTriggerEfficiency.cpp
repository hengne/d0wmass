//file: cafTriggerEfficiency.cpp
//
//Author:   Kevin Chan
//
//Purpose:  The CAFe processor interface to the rest of the classes.
//          This processor instantiates and passes the necessary
//          objects and variables to the remaining processors.
//          It also provides an easy to use interface for the end
//          user through a simple config file.
//
//Usage:    Fill this in.

//Header file for this class
#include "caf_mc_util/MCReqID.hpp"
#include "caf_trigger/cafTriggerEfficiency.hpp"
#include "caf_dq/CafeDataQualityProcessor.hpp"
#include "caf_dq/CafeDataQualityLuminosity.hpp"
#include "dq_util/DataQualityLuminosityBase.hpp"

#include "cafe/Config.hpp"

#include <stdexcept>
#include "TRandom2.h"
#include <map>
#include <sstream>
using namespace std;
using namespace cafe;
using namespace DataQualityChecker ;

extern caf_mc_util::MCReqID *MCREQID; 

cafTriggerEfficiency::cafTriggerEfficiency(const char *name)
        : Processor(name)
{
    //We grab terms from the CAFe configuration file here
    Config config(name);
    
    //The names of the EM, Muon and Jet branches
    branchNames.push_back( config.get("embranch","EMscone") );
    branchNames.push_back( config.get("mubranch","Muons") );
    branchNames.push_back( config.get("jetbranch","JCCB") );
    branchNames.push_back( config.get("trackbranch","Track") );
    branchNames.push_back( config.get("metbranch","Met") );
    branchNames.push_back( config.get("taubranch","Tau") );

    //See if need MET
    _met_on = config.get("MetOn",1);

    //Speed up switches
    bool all_speedups = config.get("AllSpeedUps",0);
    if(all_speedups) {
      _em_speedups = true;
      _jet_speedups = true;
      _mu_speedups = true;
      _met_speedups = true;
    }
    //The all switch is overridden by the separate switches
    _em_speedups = config.get("EMSpeedUps",0);
    _jet_speedups = config.get("JetSpeedUps",0);
    _mu_speedups = config.get("MuSpeedUps",0);
    _met_speedups = config.get("MetSpeedUps",0);

    //If speed up selected get the variables terms
    if(_mu_speedups) {
      out() << "Using cafe Variables speed ups for Muons for " << name << endl;
      vector<string> mu_vars_names = config.getVString("MuVars"," ,");
      if(mu_vars_names.size()==0) cerr << "Mu Speed ups selected but no variables were specified" << endl;
      _mu_vars = Variables(mu_vars_names);
    }
    if(_em_speedups) {
      out() << "Using cafe variables speed ups for EM for " << name << endl;
      vector<string> em_vars_names = config.getVString("EMVars"," ,");
      if(em_vars_names.size()==0) cerr << "EM speed ups selected but no variables were specified" << endl;
      _em_vars = Variables(em_vars_names);
    }
    if(_jet_speedups) {
      out() << "Using cafe variables speed ups for Jet for " << name << endl;
      vector<string> jet_vars_names = config.getVString("JetVars"," ,");
      if(jet_vars_names.size()==0) cerr << "Jet speed ups selected but no variables were specified" << endl;
      _jet_vars = Variables(jet_vars_names);
    }
    if(_met_speedups) {
      out() << "Using cafe variables speed ups for MET for " << name << endl;
      vector<string> met_vars_names = config.getVString("MetVars"," ,");
      if(met_vars_names.size()==0) cerr << "Met speed ups selected but no variables were specified" << endl;
      _met_vars = Variables(met_vars_names);
    }
    
    out()   << endl << "////////////////////////////////////" << endl
                << "TriggerEfficiency Calculations" << endl
                << "Using the following: " << endl
                << "EM Branch:       " << branchNames[0] << endl
                << "Muon Branch:     " << branchNames[1] << endl
                << "Jet Branch:      " << branchNames[2] << endl
                << "Tau Branch:      " << branchNames[5] << endl;    
    out()    << "////////////////////////////////////" << endl;

}

void cafTriggerEfficiency::begin()
{
  Config config(name());
  
  // Choose mode to specify luminosity per trigger. 
  // The default option is to specify the luminosity by hands using "lumi" option.
  // The alternative mode is to use the dq lumi interface.
  _dqLumi = config.get("GetLumiFromLumiCache", false) ; 


  _weightPeriods = config.get("WeightPeriods", true);
  if (! _weightPeriods) {
    _lumi_tot = 0;
    _rand = new TRandom2;
  }

}

void cafTriggerEfficiency::finish()
{
}

void cafTriggerEfficiency::inputFileOpened(TFile *file)
{
}
void cafTriggerEfficiency::inputFileClosing(TFile *file)
{
}

bool cafTriggerEfficiency::processEvent(Event &event)
{


  change_request(event);

   
    // If picking a period rather than weighting with all periods'
    // luminosities, insert the chosen period name into the Event
    if (! _weightPeriods) {
      float lumi_decider = _rand->Rndm() * _lumi_tot;
      float lumi_accumulated = 0;
      std::map<std::string, float>::iterator it;
      for (it = _mapVersionLumi.begin(); it != _mapVersionLumi.end(); ++it) {
	lumi_accumulated += it->second;
	if (lumi_accumulated > lumi_decider) break;
      }
      if (it == _mapVersionLumi.end()) --it;
      event.put("TriggerPeriod", it->first);
      if (debug() > 0)
	out() << "cafTriggerEfficiency[" << name() << "]: set TriggerPeriod to " << it->first << endl;
    }

    //We get the TMBObjects and MET in order to pass them to the
    //probability processors which shall use them. This allows us to hide
    //a bit of the implementation from the processor and give the user
    //what they will need and only that much.

    int NEM;
    int NMU;
    int NJET;
    int NTRACK;
    int NTAU;
    string turn_off = "TurnOff";
    

    //----------------------------------
    // Get the electrons
    //----------------------------------
    Collection<TMBEMCluster> electrons;
    if(branchNames[0]!=turn_off) {
      if(_em_speedups) electrons = event.getCollection<TMBEMCluster>(branchNames[0].c_str(),_em_vars);
      else electrons = event.getCollection<TMBEMCluster>( branchNames[0].c_str() );
    }
    NEM = electrons.size();
    

    //----------------------------------
    // Get the muons
    //----------------------------------
    Collection<TMBMuon> muons;
    if(branchNames[1]!=turn_off) {
      if(_mu_speedups) muons = event.getCollection<TMBMuon>(branchNames[1].c_str(),_mu_vars);
      else muons = event.getCollection<TMBMuon>( branchNames[1].c_str() );
    }
    NMU = muons.size();
    

    //----------------------------------
    // Get the jets
    //----------------------------------
    Collection<TMBJet> jets;
    if(branchNames[2]!=turn_off) {
      if(_jet_speedups) jets = event.getCollection<TMBJet>(branchNames[2].c_str(),_jet_vars);
      else jets = event.getCollection<TMBJet>( branchNames[2].c_str() );
    }
    NJET = jets.size();
    

    //----------------------------------
    // Get the tracks
    //----------------------------------
    Collection<TMBTrack> tracks;
    tracks = event.getCollection<TMBTrack>( branchNames[3].c_str() );
    NTRACK = tracks.size();


    //----------------------------------
    // Get the missing et
    //----------------------------------
    const TMBMet* metObject;
    float met = 0;
    if( _met_on && branchNames[4] != turn_off ) {
      if(_met_speedups) metObject = event.getMet(_met_vars);
      else metObject = event.get<TMBMet>(branchNames[4].c_str());

      if ( metObject == NULL ) {
	cerr << "caf_trigger could not get the Met object: " << branchNames[4] << endl;
	exit(1);
      }
      else {
	met = metObject->get_MET();
      }
    }
    //----------------------------------
    // Get the taus
    //----------------------------------
    Collection<TMBTau> taus;
    taus = event.getCollection<TMBTau>( branchNames[5].c_str() );
    NTAU = taus.size();
    


    //Instantaneous luminosity

    double INSTLUM = event.getMCEventInfo()->overlay_instlum()* 36.;


    //----------------------------------
    // Store the objects in the event class
    //----------------------------------
    event.put("passedEM", electrons);
    event.put("passedMU", muons);
    event.put("passedJET", jets);
    event.put("passedTRACK", tracks);
    event.put("passedMET", met);  
    event.put("passedTAU", taus);
    event.put("passedNEM", NEM);
    event.put("passedNMU", NMU);
    event.put("passedNJET", NJET);
    event.put("passedNTRACK", NTRACK);
    event.put("passedNTAU", NTAU);

    event.put("passedINSTLUM", INSTLUM);

    return true;
}

void cafTriggerEfficiency::change_request( cafe::Event &event ){

  cafe::Config config(name());
  
  
  
  if (!MCREQID) throw runtime_error("ERROR:  processor MCReqID is not initialized.") ;
  
  // verify if request id is stay the same. In that case do nothing.
  
  if ( MCREQID->reqid() == _reqid ) return ;
  _reqid = MCREQID->reqid() ;
  
    // verify data epochs associated to this MC
  const vector<string>* epochs =  MCREQID->current_data_epochs();




  //------------------------------------
  // Get the list of trigger versions
  //
  // Config should have trigger versions listed for each data epoch, like:
  // caftrig.triglist_RunIIa: 	08,09a,09b,10,11,12,13a,13b,13c,14
  // caftrig.triglist_RunIIb1: 	15a,15b
  // caftrig.triglist_RunIIb2: 	15c,16a,16b,16c
  // caftrig.triglist_RunIIb3: 	16d,16e
  //
  // And if more than one data epoch is used the lists will be concatinated here.
  //------------------------------------
  vector<string> triggerList;
  if(debug()>0) cout<<"Get trigger versions."<<endl;
  for (vector<string>::const_iterator eit=epochs->begin(); eit!=epochs->end(); eit++){
    vector<string> tmp_versions = config.getVString(("triglist_"+ *eit),",");
    triggerList.insert(triggerList.end(),tmp_versions.begin(),tmp_versions.end());
    if(debug()>0) cout<<"Added "<<tmp_versions.size()<<" trigger versions for "<<*eit<<endl;
  }
  
  vector<float> lumi, lumi1, lumi2;
  if (!_dqLumi) {
    out() << "Luminosity for each trigger is read from  the config file. " << endl ;  
    for (vector<string>::const_iterator eit=epochs->begin(); eit!=epochs->end(); eit++){

      vector<float> tmp_lumi;
      tmp_lumi = config.getVFloat(("lumi_"+ *eit),",");
      lumi.insert(lumi.end(),tmp_lumi.begin(),tmp_lumi.end());

      tmp_lumi.clear();
      tmp_lumi = config.getVFloat(("lumi1_"+ *eit),",");
      lumi1.insert(lumi1.end(),tmp_lumi.begin(),tmp_lumi.end());

      tmp_lumi.clear();
      tmp_lumi = config.getVFloat(("lumi2_"+ *eit),",");
      lumi2.insert(lumi2.end(),tmp_lumi.begin(),tmp_lumi.end());
    }
    
  } else {    
    CafeDataQualityLuminosity* dq_lumi = CafeDataQualityLuminosityInstance() ;
    if (!dq_lumi) 
      throw runtime_error("cafTriggerEfficiency ["+name()+"]: need DQ processor instantiated with lumicache file. No DQLuminosity object was found!") ;
    
    // read file caf_trigger/parameters/trignames.txt with correspondence between
    // trigger names and trigger versions
    ifstream fnames("caf_trigger/parameters/trignames.txt") ;
    if (!fnames)  
      throw runtime_error("Could not read file caf_trigger/parameters/trignames.txt") ;
    
    map<string,pair<float, float> > trig_names ;
    float t1=0, t2=0 ;
    string in_string, tname ;
    while ( getline(fnames,in_string) ) {
      istringstream s(in_string) ;
      s >> tname >> t1  >> t2 ;
      if (!tname.empty()) trig_names[tname] = pair<float,float>(t1,t2) ;
    }
    fnames.close() ;
    
    for (vector<string>::const_iterator it = triggerList.begin(); it != triggerList.end(); it++) {
      pair<float,float> trs = trig_names[*it] ;
      lumi.push_back(dq_lumi->integrateRecordedDqLuminosityByTriggerVersion(trs.first, trs.second));
    }
  }
  
  if ( lumi.size() != triggerList.size() ) {
    out() << "cafTriggerEfficiency::cafTriggerEfficiency" << endl ;
    out() << "- Error: The triggerlist and luminosity vectors must be equal in number" << endl;
    out() << endl;
    out() << "Lumi vector:" << endl;
    for(int i = 0; i < lumi.size(); ++i) {
      out() << "Lumi[" << i << "] = " << lumi[i] << endl;
    }
    
    out() << "TriggerList vector:" << endl;
    for(int i = 0; i < triggerList.size(); ++i) {
      out() << "TriggerList[" << i << "] = " << triggerList[i] << endl;
    }
    
    exit(1);
  }
  
  if ( lumi1.size() == 0 ) lumi1=lumi;
  if ( lumi2.size() == 0 ) lumi2=lumi;
  
  if ( lumi.size() != lumi1.size() || lumi.size() != lumi2.size() ) {
    err()   << "cafTriggerEfficiency::cafTriggerEfficiency" << endl
	   << "- Error: The luminosity vectors must be equal in number" << endl;
    err() << endl;
    err() << "Lumi vector" << endl;
    for(int i = 0; i < lumi.size(); ++i) {
      err() << "Lumi[" << i << "] = " << lumi[i] << endl;
    }
    for(int i = 0; i < lumi1.size(); ++i) {
      err() << "Lumi1[" << i << "] = " << lumi1[i] << endl;
    }
    for(int i = 0; i < lumi2.size(); ++i) {
      err() << "Lumi2[" << i << "] = " << lumi2[i] << endl;
    }
    
    exit(1);
  }
  
  //We place this information into a mapping for (triggerList, lumi)
  for(int i = 0; i < lumi.size(); ++i) {
    _mapVersionLumi[triggerList[i]] = lumi[i];
    _mapVersionLumi1[triggerList[i]] = lumi1[i];
    _mapVersionLumi2[triggerList[i]] = lumi2[i];
  }
 
  
  out() << endl << "////////////////////////////////////" << endl ;
  out() << "TriggerEfficiency Calculations: Lumi information:" << endl ;
  if (_dqLumi) 
    out() << "Read luminosity for each run range from lumicache file." << endl ;
  else 
    out() << "Read luminosity from the configuration file" << endl ;

  _lumi_tot = 0.0 ;
  for(map<string, float>::iterator it = _mapVersionLumi.begin(); it != _mapVersionLumi.end(); ++it) {
      out()   << "Trigger version: " << (*it).first
	     << " with lumi: " << (*it).second << endl;
      _lumi_tot += (*it).second  ;
    }
  out() << "Lumi total: " << _lumi_tot << " pb" << endl ;

  /// What is this for? -Joe
  //The sigma calculations
  string sigma = config.get("sigma", "false");
  if(sigma != "false") {
    out() << "with Sigma +1, -1 calculations" << endl;
  }
  out()    << "////////////////////////////////////" << endl;


  // replace maps in event
  event.put("passedVersionLumi", _mapVersionLumi);
  event.put("passedVersionLumi1", _mapVersionLumi1);
  event.put("passedVersionLumi2", _mapVersionLumi2);
  
}



ClassImp(cafTriggerEfficiency)

//endfile:
