// "MuonTriggerORMatch.cpp", Philippe Calfayan <calfayan@fnal.gov> 
// Purpose: CAF processor to enforce offline muon matching to an ORing of triggers
// History:
// 06/08/07 by Philippe: added "global summary" printout for matching result
// 06/06/07 by Liang Li: added "RecoVer" switch & checks for missing config input
// 05/29/07 created by Philippe Calfayan

// cafe
#include "caf_trigger/MuonTriggerORMatch.hpp"
#include "cafe/Config.hpp"
#include "cafe/Collection.hpp"

// root
#include "TLeaf.h"
#include "TObjString.h"
#include "TClonesArray.h"

// stl
#include <map>

using namespace std ;
using namespace caf_trigger::MuonTriggerORMatch_Tree ;

namespace caf_trigger {

  MuonTriggerORMatch::MuonTriggerORMatch(const char *name) 
    : cafe::Processor(name) {

    // Instance name
    _instance_name = name ;

    // Instanciate cafe 'Config' object to parse the configuration file
    cafe::Config config(name) ;

    // Get list of triggers
    _input_triggers = config.getVString("ListOfTriggers", " ,") ;

    // Get reco version
    _RecoVer = config.get("RecoVer", "");
    if (!_RecoVer.size()) {
	cerr << "MuonTriggerORMatch[" << _instance_name << "]" 
	   << " ERROR: The reco version given as input is empty, please specify 'RecoVer'."
	   << endl ;
	exit(1);
    }	  	    
    
    // Get muons input branch
    _muonBranch = config.get("muonBranch", "") ;
    if (!_muonBranch.size()) {
        cerr << "MuonTriggerORMatch[" << _instance_name << "] " 
	   << " ERROR: The muon branch given as input is empty, please specify 'muonBranch'."
	   << endl ;
        exit(1);
    }

    // Optional output tree name. The string "", given as name, switches 
    // off this feature. The tree is copied in the file pointed by cafe.Ouput.
    _output_tree_name = config.get("TreeName", "") ;

    // Switch on/off the UseTriggerFire option (default: on)
    _use_trigger_fired = config.get("UseTriggerFired", true) ;


    // muonmatchinf will be applied only if runnumber is in the specified trigger range
    _use_run_range = config.get("UseRunRange",false);
    if ( _use_run_range ) {
      _applied_trigger_version = config.getVFloat("TriggerVersions",",");
      if ( _applied_trigger_version.size() != 2 ) {
	cerr << "TriggerVersions size must be 2." << endl;
	exit(1);
      }
    }

    // Switch on/off the Exclude Bad Run Range option (default: on)
    _exclude_bad_run_range = config.get("ExcludeBadRunRange", true) ;

    // If tag is an empty string, the processor will select events.
    // If tag is an non empty string, the processor will not select events
    // but tag them with event.put().
    _tag = config.get("Tag", "") ;

    // Switch on/off the debug option (default: off)
    bool debug = config.get("Debug", false) ;
    setDebug(debug) ;

    // Print the summary output of each called MuonTriggerMatch object
    _MuonTriggerMatch_summary_ouput = config.get("Summary", false) ;

    // Instanciate a TriggerMap object
    _runnum_to_triggerversion = new TriggerMap();

    // Instanciate a MuonTriggerMatch object for each input trigger
    string prefix = "MuonTriggerORMatch_" + _RecoVer + "_" ;
    for (unsigned int i=0 ; i<_input_triggers.size() ; i++) {

      // This name will be used as argument of cafe::Config() in the 
      // constructor of MuonTriggerMatch
      string instance_name = prefix + _input_triggers[i] ;

      // Propagate the input branch string, the debug flag, and the 
      // ExcludeBadRunRange option to the configuration of MuonTriggerMatch
      config.set(instance_name+".muonBranch", _muonBranch) ;
      config.set(instance_name+".Debug", debug ? "true" : "false") ;
      config.set(instance_name+".ExcludeBadRunRange", 
		 _exclude_bad_run_range ? "true" : "false") ;

      // If UseTriggerFire set to false, force exclusion of bad run ranges
      if (!_use_trigger_fired && !_exclude_bad_run_range) 
	config.set(instance_name+".ExcludeBadRunRange", "true") ;

      // Store the instanciated MuonTriggerMatch in a list
      _MuonTriggerMatch_list
	.push_back( MuonTriggerMatch(instance_name.c_str()) ) ;

    }

    // Initialize global counters
    _processed_events = 0 ;
    _nevents_with_at_least_one_matched_trig = 0 ;
    _nevents_where_at_least_one_trig_fired = 0 ;
    _nevents_in_the_range = 0 ;
  }

  void MuonTriggerORMatch::begin() {

    // If feature switched on, create output_tree
    if (_output_tree_name.size()) {

      // Declare output tree
      _results_tree = new TTree( _output_tree_name.c_str(), 
      				 _output_tree_name.c_str() ) ;

      //
      // Create output tree branches
      //

      _results_tree->Branch("OR", 
			    &_OR_branch, 
			    "ORMatched/b:ORFired/b") ;
      _results_tree->Branch("Global",
			    &_Global_branch, 
			    "evtno/I:runno/I:trigvers/F") ;
      _results_tree->Branch("Offline", 
			    &_Offline_branch, 
			    "mupt[7]/F:mudeteta[7]/F:muphi[7]/F:muz[7]/F") ;


      // Get list of trigger terms, initialise terms_map
      vector<string> list_of_terms ;

      map<string, bool> found_muon ;
      map<string, bool> found_track ;
      map<string, bool> found_iso ;
      map<string, bool> found_cm  ;

      list<MuonTriggerMatch>::iterator iter_trigs 
	= _MuonTriggerMatch_list.begin() ;
      while ( iter_trigs != _MuonTriggerMatch_list.end()) {

	found_muon = iter_trigs->getMuonTermTestResults() ;
	found_track = iter_trigs->getTrackTermTestResults() ;
	found_iso = iter_trigs->getIsoTermTestResults() ;
	found_cm = iter_trigs->getCMTermTestResults() ;

	map<string, bool>::iterator iter_terms = found_muon.begin() ;
	while (iter_terms != found_muon.end()) {
	  if (!_terms_map.count(iter_terms->first))
	    _terms_map[iter_terms->first] = 0 ;
	  iter_terms++ ;
	}
	iter_terms = found_track.begin() ;
	while (iter_terms != found_track.end()) {
	  if (!_terms_map.count(iter_terms->first))
	    _terms_map[iter_terms->first] = 0 ;
	  iter_terms++ ;
	}
	iter_terms = found_iso.begin() ;
	while (iter_terms != found_iso.end()) {
	  if (!_terms_map.count(iter_terms->first))
	    _terms_map[iter_terms->first] ;
	  iter_terms++ ;
	}
	iter_terms = found_cm.begin() ;
	while (iter_terms != found_cm.end()) {
	  if (!_terms_map.count(iter_terms->first))
	    _terms_map[iter_terms->first] ;
	  iter_terms++ ;
	}
 
	iter_trigs++ ;
      }

      // Initialise branch containers for TrigMatched, TermMatched 
      // and TrigFired information
      _TrigMatched_tab = new Bool_t[_input_triggers.size()] ;
      _TrigFired_tab = new Bool_t[_input_triggers.size()] ;
      _TermMatched_tab = new Bool_t[_terms_map.size()] ;


      // Create TrigMatched and TrigFired branches
      for (unsigned int i=0 ; i<_input_triggers.size() ; i++) {
 	string name = "" ;
 	string type = "" ;

 	name = "TrigMatched."+_input_triggers[i] ;
 	type = name+"/O" ;
 	_results_tree->Branch( name.c_str(),
			       &(_TrigMatched_tab[i]),
			       type.c_str() ) ;

  	name = "TrigFired."+_input_triggers[i] ;
  	type = name+"/O" ;
  	_results_tree->Branch( name.c_str(),
			       &(_TrigFired_tab[i]),
			       type.c_str() ) ;
      }

      // Create TermMatched branch
      unsigned int iterm = 0 ;
      map<string, bool>::iterator iter_terms = _terms_map.begin() ;
      while (iter_terms != _terms_map.end()) {
	string name = "" ;
        string type = "" ;

	name = "TermMatched."+iter_terms->first ;
	type = name+"/O" ;
	_results_tree->Branch( name.c_str(),
			       &(_TermMatched_tab[iterm]),
			       type.c_str() ) ;
	iterm++ ;
	iter_terms++ ;
      }

      // Some prints
      cout << "MuonTriggerORMatch[" << _instance_name << "] "
	   << "Number of triggers in "
	   << _output_tree_name.c_str() << "      :   " 
	   << _input_triggers.size() << endl;
      cout << "MuonTriggerORMatch[" << _instance_name << "] "
	   << "Number of trigger terms in "
	   << _output_tree_name.c_str() << " :   "
	   << _terms_map.size() << endl;

    }

  }

  bool MuonTriggerORMatch::processEvent(cafe::Event& event) {

    //
    // Global event info
    //

    int runno = event.getGlobal()->runno();
    float trigvers = _runnum_to_triggerversion->TriggerVersion(runno) ;    

    if (_output_tree_name.size()) {
      int evtno = event.getGlobal()->evtno() ;

      // Fill output tree  
      _Global_branch.evtno = evtno ; 
      _Global_branch.runno = runno ;
      _Global_branch.trigvers = trigvers ;


    //
    // Offline muon info
    //
      
      cafe::Collection<TMBMuon> muons = 
	event.getCollection<TMBMuon>(_muonBranch.c_str()) ;

      // Fill output tree
       for (unsigned int m=0 ; m<7 && m<muons.size() ; m++) {
 	_Offline_branch.mupt[m] = muons[m].Pt() ;
 	_Offline_branch.mudeteta[m] = muons[m].detectorEta() ;
 	_Offline_branch.muphi[m] = muons[m].Phi() ; 
 	_Offline_branch.muz[m] = muons[m].z() ;
       }

    }


    //
    // Trigger Matching test
    //

    map<string, bool> match_map ;

    list<MuonTriggerMatch>::iterator iter = _MuonTriggerMatch_list.begin() ;
    for (unsigned int i=0 ; i<_input_triggers.size() ; i++ ) {
      bool result =  iter->processEvent(event) ;
      match_map[ _input_triggers[i] ] = result ;
      iter++ ;
    }

    // Fill ouput tree
    if (_output_tree_name.size()) {
      for (unsigned int i=0 ; i<_input_triggers.size() ; i++) {
	_TrigMatched_tab[i] =  match_map[ _input_triggers[i] ] ;
      }
    }

    //
    // TriggerFire test
    //

    map<string, bool> triggerfire_map ;
    triggerfire_map.clear() ;

    // Local counter 
    unsigned int nb_fired = 0 ;

    if (_use_trigger_fired) {

      // Get the collection of triggers that fired
      cafe::Collection<TMBTrigger> fired_coll = event.getTriggers() ;

      // Loop on the input triggers
      for (unsigned int i=0 ; i<_input_triggers.size() ; i++) {

	// Initialisation
	triggerfire_map[_input_triggers[i]] = 0 ;

	// Loop on the triggers which fired and check if it includes the 
	// tested trigger
	for ( unsigned int j=0 ; j<fired_coll.size() ; j++ ) {

	  TMBTrigger trigger = fired_coll[j] ;
	  string trgname = trigger.getTrgName() ;

	  // allow variations in the given name in order to account for
	  // different versiosn of the same trigger

	  if (_input_triggers[i].find(trgname) != string::npos) {
	    triggerfire_map[_input_triggers[i]] = 1 ;
	    nb_fired++ ;
	  }

	}

      }

    }
    _OR_branch.ORFired = (bool) nb_fired ;

    // Fill output tree
    if (_output_tree_name.size()) {
      for (unsigned int i=0 ; i<_input_triggers.size() ; i++) {
	_TrigFired_tab[i] = triggerfire_map[ _input_triggers[i] ] ;
      }
    }

    //
    // Term Matching Test (only for output_tree)
    //

    if (_output_tree_name.size()) {

      //
      // Get the matching results for all the trigger terms
      //

      map<string, bool> found_muon ;
      map<string, bool> found_track ;
      map<string, bool> found_iso ;
      map<string, bool> found_cm ;

      // reset trigger terms map
      unsigned int iterm2 = 0 ;
      map<string, bool>::iterator iter2 = _terms_map.begin() ;
      while (iter2 != _terms_map.end()) {
	_TermMatched_tab[iterm2] = 0 ;
        _terms_map[iter2->first] = 0 ;
        iter2++ ;
	iterm2++ ;
      }

      unsigned int itrig = 0 ;
      list<MuonTriggerMatch>::iterator iter = _MuonTriggerMatch_list.begin() ;
      while (iter != _MuonTriggerMatch_list.end()) {
	
	bool fired = triggerfire_map[_input_triggers[itrig]] ;
	if (!fired && _use_trigger_fired) {
	  itrig++ ;
	  iter++ ;
	  continue ;
	}

	found_muon = iter->getMuonTermTestResults() ;
	found_track = iter->getTrackTermTestResults() ;
	found_iso = iter->getIsoTermTestResults() ;
	found_cm = iter->getCMTermTestResults() ;

	map<string, bool>::iterator iter_terms = found_muon.begin() ;
	while (iter_terms != found_muon.end()) {
	  _terms_map[iter_terms->first] |= iter_terms->second ;
	  iter_terms++ ;
	}
	iter_terms = found_track.begin() ;
	while (iter_terms != found_track.end()) {
	  _terms_map[iter_terms->first] |= iter_terms->second ;
	  iter_terms++ ;
	}
	iter_terms = found_iso.begin() ;
        while (iter_terms != found_iso.end()) {
          _terms_map[iter_terms->first] |= iter_terms->second ;
	  iter_terms++ ;
	}
        iter_terms = found_cm.begin() ;
        while (iter_terms != found_cm.end()) {
	  _terms_map[iter_terms->first] |= iter_terms->second ;
	  iter_terms++ ;
	}

	found_muon.clear() ;
	found_track.clear() ;
	found_iso.clear() ;
	found_cm.clear() ;

	itrig++ ;
	iter++ ;

      }     

      // Fill branch container
      unsigned int iterms = 0 ;
      map<string, bool>::iterator iter_terms = _terms_map.begin() ;
      while (iter_terms != _terms_map.end()) {
	_TermMatched_tab[iterms] = iter_terms->second ;
	iter_terms++ ;
	iterms++ ;
      }

    }

    // test if event is in the specified trigger range

    bool event_in_the_range = true;
    if ( _use_run_range ) {
      int lastrun = _runnum_to_triggerversion->LastRun();
      
      // Make sure runvstriglistX100.txt is up-to-date
      if ( runno > lastrun ) {
	cout << "caf_trigger::MuonTriggerORMatch ERROR:" << endl;
	cout << "Current Run number exceeds the last run in caf_trigger/parameters/runvstriglistX100.txt !"<< endl;
	printf("Run number: %d, Last Run: %d\nConsider a manual fix by running caf_trigger/parameters/mkruntrigvlist.py\n\n", runno, lastrun);
	exit(1);
      }
      
      if ( trigvers <= 0 ) {
	err() << "caf_trigger::MuonTriggerORMatch ERROR:" << endl;
	err() << "Unable to find trigger version corresponding to runno " << runno << endl;
	err() << "Is caf_trigger/parameters/runvstriglistX100.txt up-to-date ?" << endl << endl;
	exit(1);
      }
      
      if ( trigvers < _applied_trigger_version[0]+0.0001 ||
	   trigvers > _applied_trigger_version[1]-0.0001 ) {
	event_in_the_range = false ;
      } else _nevents_in_the_range++ ;
    }

    //
    // Result
    //

    list<pair<bool, string> > result_list ;

    // Loop on the input triggers
    for (unsigned int i=0 ; i<_input_triggers.size() ; i++) {

      // Initialisation
      bool result = false ;    

      // If UseTriggerFired is set to false, we fill the list as if all the 
      // triggers did fire

      // Test if the trigger is matched and fired
      if ( _use_trigger_fired ) {
	result = ( match_map[_input_triggers[i]] &&
		   triggerfire_map[_input_triggers[i]] ) ;
      }

      // Test if trigger is matched
      if ( !_use_trigger_fired ) 
	result = match_map[_input_triggers[i]] ;

      // Fill list
      result_list.push_back( pair<bool, string>(result, _input_triggers[i]) ) ;

    }

    multimap<bool, string> result_map(result_list.begin(), result_list.end()) ;

    // Keep event if and only if at least one trigger is matched to an 
    // offline muon (and eventually fired, if required), ie, the multimap 
    // 'result_map' contains at least one entry whose key is 1

    // Local counter
    unsigned int nb_matched = result_map.count(1) ;

    // Result
    _OR_branch.ORMatched = (bool) nb_matched ;

    // Update global counters
    _processed_events++ ;
    _nevents_with_at_least_one_matched_trig += (unsigned int) nb_matched>0 ;
    _nevents_where_at_least_one_trig_fired += (unsigned int) nb_fired>0 ;

    // Fill output tree
    if (_output_tree_name.size())    
      _results_tree->Fill() ;

    // Return result or tag event
    if (!_tag.size())
      if (event_in_the_range) return _OR_branch.ORMatched ;
      else return true ;
    else {
      event.put(_tag.c_str(), _OR_branch.ORMatched) ;
      return true ;
    }

  }

  void MuonTriggerORMatch::finish() {

    // Summary output for each instance of MuonTriggerMatch
    if (_MuonTriggerMatch_summary_ouput) {

      // Execute the finish() method for each MuonTriggerMatch object 
      list<MuonTriggerMatch>::iterator iter = _MuonTriggerMatch_list.begin() ;
      while (iter != _MuonTriggerMatch_list.end()) {
	iter->finish() ;
	iter++ ;   
      }

    }

    //
    // Global summary ouput
    //
    cout << endl;
    cout << "===============================================================" << endl; 
    cout << "MuonTriggerORMatch[" << _instance_name << "] SUMMARY " <<endl;
    cout <<  endl ;

    cout << "  Number of processed events : \t" 
	 << _processed_events
	 << endl ;
    if (_use_run_range) 
      cout << "  Number of events in the trigger range : \t"
	   << _nevents_in_the_range
	   << endl ;
    if (!_use_run_range ||  _nevents_in_the_range >0)
      cout << "  Number of selected events  : \t"
	   << _nevents_with_at_least_one_matched_trig 
	   << endl ;
    cout <<  endl ;

    cout << "Note: selected events are events for which at least "
	 << "one input trigger was matched" ;
    if (_use_trigger_fired) 
      cout << " and fired. " << endl  <<"In "
	   << _nevents_where_at_least_one_trig_fired
	   << " events, at least one trigger did fire" ;
    if (_output_tree_name.size())
      cout << ". Matching tests (for triggers and corresponding terms) and "
	   << "triggerfire bit tests have been stored to the tree named "
	   << _output_tree_name.c_str() ;
    cout << "."
	 << endl ;
    cout << "===============================================================" << endl; 

  }

}

ClassImp(caf_trigger::MuonTriggerORMatch)
