#define MuonTriggerMatch_cxx
////////////////////////////////////////////////////////////////////////
// $Id: MuonTriggerMatch.cpp
// 
// File:    MuonTriggerMatch.cpp
// Purpose: CAF processor to enforce offline muon matching to triggers
// Author:  Kristian Harder, 5 May 2006
//
// History:
//  02/05/10 by Rick Jesik: Fixed bug in translation of l1bttx to correct trigger term, added medium quality for central track matched L3 muons
//  11/25/08 by Liang Li: Added support for L2 muon tight scintillator cut, also a few sanity checks
//  01/31/08 by Liang Li: Updated program so it can run on old (p18) caf trees (L3 Muon Pt issue, see 05/21/07 entry)
//  12/26/07 by Liang Li: Ken Herner discovered a bug for matching MUON_CM terms (PtCentral is signed!) 
//  10/31/07 by Liang Li: Added support for ISO term "ISO_MUON_CAL8"
//  09/05/07 by Liang Li: Marco updated L1Muterm to include run2b terms (event.isRun2b() switch), also added new terms for v15 MUH1,2,3 triggers (from Ken)
//  07/11/07 by Liang Li: fixed a bug in L1 track matching and a bug in L3 muon matching, added detailed summary & debugging printout 
//  06/06/07 by Philippe & Liang: improved printings, added "ExcludeBadRunRange" switch, and corrected a bug with "_found%" variables 
//  05/21/07 by Liang Li: added v15 trigger terms & medium/tight muon quality checks, also changed L3 Muon Pt variable 
//  05/12/07 by Philippe Calfayan: added iso, CM support, a bug fix, also added new functions (to be used by MuonTriggerORMatch)
//  07/26/06 by Thomas Gadfort: I added the ability to match in certain trigger versions.
////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "tmb_tree/TMBL1Muon.hpp"
#include "tmb_tree/TMBL1Track.hpp"
#include "tmb_tree/TMBGlobal.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "caf_trigger/MuonTriggerMatch.hpp"
#include "caf_trigger/L1MuTerms.hpp"
#include "caf_trigger/TriggerMap.hpp"

using namespace std;

MuonTriggerMatch::MuonTriggerMatch(const char *name): cafe::Processor(name){

  // cuts that are hardcoded in wzreco
  // for the time being, I prefer not to have the possibility to override
  // those with config file parameters!
  _dphi_l1trk  = 0.5;
  _dR_l2muon   = 0.95;
  _dphi_l3muon = 0.5;
  _dphi_l3trk  = 0.5;
  _dphi_l3iso  = 0.2; 
  _dphi_l3cm   = 0.5;  	

  cafe::Config config(name);

  setDebug(config.get("Debug",0));
	    
  //------------------------------------------------
  // 1 map is created relating runnumber and trigger list version
  // the filename must be given at the .config file
  //------------------------------------------------
  
  std::ifstream listfile;
  std::string runvstriglistfile,tempstring;
  int runnum,cnt;
  float trigv,trig_ver_min,trig_ver_max;

  _runnum_to_triggerversion = new TriggerMap();
  _use_run_range = config.get("UseRunRange",false);
  if ( _use_run_range ) {
    _applied_trigger_version = config.getVFloat("TriggerVersions",",");
    if ( _applied_trigger_version.size() != 2 ) {
      cerr << "TriggerVersions size must be 2." << endl;
      exit(1);
    }
  }

  _exclude_bad_run_range = config.get("ExcludeBadRunRange", false) ;
  
  // input muon branch
  _muonBranch=config.get("muonBranch","selectedMuons");

  // find out which trigger matching conditions to apply for which muons
  memset(_n_used_conds,0,sizeof(_n_used_conds));
  for (int icond=0; icond<_max_matchconds; icond++) {
    std::stringstream configname;
    configname << "Muon" << icond << "_requireL1L2L3";
    std::vector<int> nextcond = config.getVInt(configname.str(),",");
    if (nextcond.size()==0) continue;
    if (nextcond.size()!=3) {
      cout << name << " ERROR: need to specify exactly three arguments for "
	   << configname.str() << endl;
      exit(1);
    }
    for (int ilevel=0; ilevel<3; ilevel++) {
      if (nextcond[ilevel]!=0 && nextcond[ilevel]!=1) {
	cout << name << " ERROR: only arguments 0 and 1 allowed for "
	   << configname.str() << endl;
	exit(1);
      }
      _n_used_conds[ilevel]+=nextcond[ilevel];
    }
    _matchconds.push_back(nextcond);
  } 

  // sanity check
  if (_matchconds.size()==0) {
    cout << name << " ERROR: need to specify at least Muon0_requireL1L2L3"
	 << endl;
    exit(1);
  }

  // read trigger object specifications.
  // these should be given as muid_eff like trigger object names.
  // that makes it easier to compare to caf_trigger configurations
  for (int ilevel=0; ilevel<3; ilevel++) {
    std::stringstream configname;
    configname << "Level" << ilevel+1 << "MuonObject";
    _trigcond_muon[ilevel] = config.get(configname.str(),"");
    _check_muon[ilevel]=(_trigcond_muon[ilevel]!="");
    configname.str("");
    configname << "Level" << ilevel+1 << "TrackObject";
    _trigcond_track[ilevel] = config.get(configname.str(),"");
    _check_track[ilevel]=(_trigcond_track[ilevel]!="");
    configname.str(""); 
    configname << "Level" << ilevel+1 << "IsolationObject";
    _trigcond_iso[ilevel] = config.get(configname.str(),"");
    _check_iso[ilevel]=(_trigcond_iso[ilevel]!="");
    configname.str("");
    configname << "Level" << ilevel+1 << "CMObject";
    _trigcond_cm[ilevel] = config.get(configname.str(),"");
    _check_cm[ilevel]=(_trigcond_cm[ilevel]!="");  
    if (_n_used_conds[ilevel]>0 &&
	!_check_muon[ilevel] && !_check_track[ilevel] &&
	!_check_iso[ilevel] && !_check_cm[ilevel]) {
      cout << name << " ERROR: level " << ilevel+1 << " matching condition "
	   << "requested, but no trigger objects specified" << endl;
      exit(1);
    }
  }

  // convert muid_eff l1muon name to actual trigger term name
  // do this case by case to make sure we know what we are doing
  if (_check_muon[level1]) {
    _l1muon_name="";
    if (_trigcond_muon[level1]=="l1atxx") _l1muon_name="mu1ptxatxx";
    if (_trigcond_muon[level1]=="l1atlx") _l1muon_name="mu1ptxatlx";
    if (_trigcond_muon[level1]=="l1wtxx") _l1muon_name="mu1ptxwtxx";
    if (_trigcond_muon[level1]=="l1wtlx") _l1muon_name="mu1ptxwtlx";
    if (_trigcond_muon[level1]=="l1atx10") _l1muon_name="mu1pt4atxx"; 
    if (_trigcond_muon[level1]=="l1atl10") _l1muon_name="mu1pt4atlx"; 
    if (_trigcond_muon[level1]=="l1wtx10") _l1muon_name="mu1pt4wtxx"; 
    if (_trigcond_muon[level1]=="l1wtl10") _l1muon_name="mu1pt4wtlx"; 
    if (_trigcond_muon[level1]=="l1wttx") _l1muon_name="mu1ptxwttx"; 
    if (_trigcond_muon[level1]=="l1bttx") _l1muon_name="mu1ptxbttx"; 
    if (_trigcond_muon[level1]=="l1wllx") _l1muon_name="mu1ptxwllx"; 
    if (_trigcond_muon[level1]=="l1wll10") _l1muon_name="mu1pt4wllx"; 	    
  //new  v15 trigger terms here
    if (_trigcond_muon[level1]=="l1attx") _l1muon_name="mu1ptxattx";    //MUJ1, MUJ2
    if (_trigcond_muon[level1]=="l13wtlx") _l1muon_name="mu1pt3wtlx";  
    if (_trigcond_muon[level1]=="l18wtlx") _l1muon_name="mu1pt8wtlx";   //MUJ3, MUJ4
    if (_trigcond_muon[level1]=="l113wtlx") _l1muon_name="mu1p13wtlx";  //MUHI1
    if (_trigcond_muon[level1]=="l18wttx") _l1muon_name="mu1pt8wttx";   //MUHI2
    if (_trigcond_muon[level1]=="l113wttx") _l1muon_name="mu1p13wttx";  //MUHI3
    if (_trigcond_muon[level1]=="l1allx") _l1muon_name="mu1ptxallx";

  // sanity check	    
    if (_l1muon_name=="" && _trigcond_muon[level1]!="") {
      cout << name << " ERROR: unknown L1 muon term "
	   << _trigcond_muon[level1] << endl;
      exit(1);
    }
  }

  // extract pt thresholds and muon quality from l2muon term
  _l2muon_prompt=0;
  _l2muon_quality=0;
  if (_check_muon[level2]) {
  // deal with "l2m3t" here
    int l2size = _trigcond_muon[level2].size();
    if ( l2size > 4 && _trigcond_muon[level2].substr(l2size-1,1) == "t" ) {
        _trigcond_muon[level2].erase(l2size-1);
        _l2muon_prompt=3;
    }
    
  // L2 muon qualities: 1 (loose), 2 (medium), 3 (tight)    
    if (_trigcond_muon[level2].substr(0,3)=="l2l") _l2muon_quality=1;	  
    if (_trigcond_muon[level2].substr(0,3)=="l2m") _l2muon_quality=2;
    if (_trigcond_muon[level2].substr(0,3)=="l2t") _l2muon_quality=3;
  // sanity check
    if ( _l2muon_quality > 3 || _l2muon_quality < 1 ) {
      cout << name << " ERROR: cannot parse L2 muon quality "
	   << _trigcond_muon[level2] << endl;
      exit(1);
    }	    	    
    _l2muon_ptthreshold=atoi(_trigcond_muon[level2].substr(3,3).c_str());
    std::stringstream test;
    test << _trigcond_muon[level2].substr(0,3) << _l2muon_ptthreshold;
    if (test.str()!=_trigcond_muon[level2]) {
      cout << name << " ERROR: cannot parse L2 muon pt threshold "
	   << _trigcond_muon[level2] << endl;
      exit(1);
    }
    // l2m0 means pt>=0, not pt>0, so need to move the cut value further down
    if (_l2muon_ptthreshold==0) _l2muon_ptthreshold=-1;
  }

  // extract pt thresholds and muon quality from l3muon term.
  // note that L3 muon quality has different numbers than L2 muon quality
  _l3muon_quality=0;
  if (_check_muon[level3]) {
  // L3 muon qualities: 0, 1, 2 (loose), 3 (medium), 4 (tight)	  
    if (_trigcond_muon[level3].substr(0,3)=="l3l") _l3muon_quality=2;
    if (_trigcond_muon[level3].substr(0,3)=="l3m") _l3muon_quality=3;
    if (_trigcond_muon[level3].substr(0,3)=="l3t") _l3muon_quality=4;	    
  // sanity check
    if ( _l3muon_quality > 4 || _l3muon_quality < 2 ) {
      cout << name << " ERROR: cannot parse L3 muon quality "
	   << _trigcond_muon[level3] << endl;
      exit(1);
    }	
    _l3muon_ptthreshold=atoi(_trigcond_muon[level3].substr(3,3).c_str());
    std::stringstream test;
    test << _trigcond_muon[level3].substr(0,3) << _l3muon_ptthreshold;
    if (test.str()!=_trigcond_muon[level3]) {
      cout << name << " ERROR: cannot parse L3 muon pt threshold "
	   << _trigcond_muon[level3] << endl;
      exit(1);
    }
  }

  // extract pt thresholds and muon quality from l3cm term
  _l3cm_quality=0;
  if (_check_cm[level3]) {
    if (_trigcond_cm[level3].substr(0,5)=="l3cml") _l3cm_quality=2;
    if (_trigcond_cm[level3].substr(0,5)=="l3cmm") _l3cm_quality=3;
    _l3cm_ptthreshold=atoi(_trigcond_cm[level3].substr(5,3).c_str());
    std::stringstream test;
    test << _trigcond_cm[level3].substr(0,5) << _l3cm_ptthreshold;
    if ( _l3cm_quality < 2 || test.str()!=_trigcond_cm[level3]) {
      cout << name << " ERROR: cannot parse L3 cm term "
           << _trigcond_cm[level3] << endl;
      exit(1);
    }
  }
  
  // extract pt threshold from l1track term
  _l1track_iso=0;
  if (_check_track[level1]) {
    _l1track_ptthreshold=atoi(_trigcond_track[level1].substr(5,3).c_str());
    std::stringstream test;
    test << "l1trk" << _l1track_ptthreshold;
    int l1itrack_ptthreshold=atoi(_trigcond_track[level1].substr(6,3).c_str());
    std::stringstream testi;
    testi << "l1itrk" << l1itrack_ptthreshold;
    if (testi.str()==_trigcond_track[level1]) { 
      _l1track_iso=1 ;
      _l1track_ptthreshold=l1itrack_ptthreshold ;
    }
    if (test.str()!=_trigcond_track[level1] &&
	testi.str()!=_trigcond_track[level1] ){
      cout << name << " ERROR: cannot parse L1 track term "
	   << _trigcond_track[level1] << endl;
      exit(1);
    }
  }
  
  //  L2 tracks
  if (_check_track[level2]) {
    
    _l2track_ptthreshold=atoi(_trigcond_track[level2].substr(5,3).c_str());
    std::stringstream test;
    std::stringstream testOtk;
    std::stringstream testmtk;
    std::stringstream teststt;

    test << "l2trk" << _l2track_ptthreshold;
    testOtk << "l2Otk" << _l2track_ptthreshold;
    testmtk << "l2mtk" << _l2track_ptthreshold;
    teststt << "l2stt" << _l2track_ptthreshold;


    if(test.str()!=_trigcond_track[level2] && testOtk.str()!=_trigcond_track[level2] && testmtk.str() !=_trigcond_track[level2] && teststt.str() != _trigcond_track[level2] ){
      cout << name << " ERROR: cannot parse L2 track term " << _trigcond_track[level2] << endl;
      
      exit(1);
    }
    if(_trigcond_track[level2].substr(0,5) != "l2trk" && _trigcond_track[level2].substr(0,5) != "l2mtk" &&  _trigcond_track[level2].substr(0,5) != "l2Otk" &&  _trigcond_track[level2].substr(0,5) != "l2stt" ) {
      cout << name << " ERROR: L2 track terms must begin with l2trk, l2Otk, l2mtk, or l2stt: " << _trigcond_track[level2] << endl;
      
      exit(1);
      
    }
  }
  
  // extract pt threshold from l3track term
  if (_check_track[level3]) {
    std::string trigcond=_trigcond_track[level3];
    if (trigcond.find("h10")!=std::string::npos) {
      _l3track_nhits=10;
      trigcond=trigcond.replace(trigcond.find("h10"),3,"");
    } else {
      _l3track_nhits=8;
    }
    _l3track_ptthreshold=atoi(trigcond.substr(5,3).c_str());
    std::stringstream test;
    test << "l3trk" << _l3track_ptthreshold;
    if (_l3track_nhits==10) test << "h10";
    if (test.str()!=_trigcond_track[level3]) {
      cout << name << " ERROR: cannot parse L3 track term "
	   << _trigcond_track[level3] << endl;
      exit(1);
    }
  }

  // get l3iso toolname
  if (_check_iso[level3]) {
    std::string trigcond = _trigcond_iso[level3] ;
    transform( trigcond.begin(), trigcond.end(), trigcond.begin(),
	       static_cast<int (*)(int)>(toupper) ) ; 
    _l3iso_toolname = trigcond ;
    if ( trigcond!="ISO_MUON_CM_L1" && 
	 trigcond!="ISO_MUON_CAL3" &&
	 trigcond!="ISO_MUON_CAL8" && 
	 _trigcond_iso[level3]!="") {
      cout << name << " ERROR: Unknown L3 isolation toolname "
	   << _trigcond_iso[level3] << endl;
      exit(1);
    }
  }
  
  if ( debug() ){
    // print configuration summary
    cout << "=======================================" << endl;
    cout << "MuonTriggerMatch processor " << name << endl;
    cout << " - input muon branch: \"" << _muonBranch << "\"" << endl;
    cout << " - number of matching requirements: " << _matchconds.size() << endl;
    for (int i=0; i<_matchconds.size(); i++) {
      cout << " - matching requirement #" << i << ":";
      for (int ilevel=0; ilevel<3; ilevel++) {
	if (_matchconds[i][ilevel]) {
	  cout << " L" << ilevel+1;
	} else {
	  cout << " --";
	}
      }
      cout << endl;
    }
    for (int ilevel=0; ilevel<3; ilevel++) {
      cout << " - L" << ilevel+1 << " Muon requirement : ";
      if (_trigcond_muon[ilevel]!="") {
	cout << _trigcond_muon[ilevel] << endl;
      } else {
	cout << "none" << endl;
      }
      cout << " - L" << ilevel+1 << " Track requirement: ";
      if (_trigcond_track[ilevel]!="") {
	cout << _trigcond_track[ilevel] << endl;
      } else {
	cout << "none" << endl;
      }
    }
    cout << " - L3" << " Muon CM requirement : ";
    if (_trigcond_cm[2]!="") {
      cout << _trigcond_cm[2] << endl;
    } else {
      cout << "none" << endl;
    }
    cout << " - L3" << " Isolation requirement : ";
    if (_trigcond_iso[2]!="") {
      cout << _trigcond_iso[2] << endl;
    } else {
      cout << "none" << endl;
    }
    
    // also print how we converted the input information
    if (_check_muon[level1])
      cout << "-> L1 muon trigger term " << _l1muon_name << endl;
    if (_check_muon[level2]) {
      cout << "-> L2 muon quality " << _l2muon_quality
	   << ", pt threshold " << _l2muon_ptthreshold << endl;
      if ( _l2muon_prompt > 0 ) cout << "-> L2 muon tight scintillator cut active" << endl;
    }  	  
    if (_check_muon[level3])
      cout << "-> L3 muon quality " << _l3muon_quality
	   << ", pt threshold " << _l3muon_ptthreshold << endl;
    if (_check_cm[level3])
      cout << "-> L3 cm muon quality " << _l3cm_quality
	   << ", pt threshold " << _l3cm_ptthreshold << endl; 
    if (_check_track[level1]) { 
      cout << "-> L1 track trigger pt threshold " << _l1track_ptthreshold << endl;
      cout << "-> L1 track trigger iso " << _l1track_iso << endl; 
    }
    if (_check_track[level3]) {
      cout << "-> L3 track trigger pt threshold " << _l3track_ptthreshold << endl;
      cout << "-> L3 track trigger min num hits " << _l3track_nhits << endl; 
    }
    cout << "=======================================" << endl;
  }

  // reset event counters
  _n_events=0;
  _n_matched_events=0;
  _n_wrong_triglist=0;

  // number of rejected events because of missing/empty chunk
  _n_no_l1muon=0;
  _n_no_l1track=0;
  _n_no_l2muon=0;
  _n_no_l2track=0;
  _n_no_l3muon=0;
  _n_no_l3track=0;
  _n_no_l3iso=0; 

  // run numbers where this happened
  _allruns.clear();
  _runs_no_l1muon.clear();
  _runs_no_l2muon.clear();
  _runs_no_l2track.clear();
  _runs_no_l3muon.clear();
  _runs_no_l1track.clear();
  _runs_no_l3track.clear();
  _runs_no_l3iso.clear();

  // number of rejected events because no match found
  _n_nomatch_l1muon=0;
  _n_nomatch_l1track=0;
  _n_nomatch_l2muon=0;
  _n_nomatch_l2track=0;
  _n_nomatch_l3muon=0;
  _n_nomatch_l3track=0;

}



//=========================================================================
//=========================================================================


bool MuonTriggerMatch::processEvent(cafe::Event& event)
{

  //---------------------
  // Check the run range
  //---------------------
  ++_n_events;
  int runno   = event.getGlobal()->runno();



  ++_allruns[runno];


  if ( _use_run_range ) {
    bool found = false;
    float triggerversion = _runnum_to_triggerversion->TriggerVersion(runno);
    int lastrun = _runnum_to_triggerversion->LastRun();

// Make sure runvstriglistX100.txt is up-to-date
    if ( runno > lastrun ) {
      cout << "caf_trigger::MuonTriggerMatch ERROR:" << endl;
      cout << "Current Run number exceeds the last run in caf_trigger/parameters/runvstriglistX100.txt !"<< endl;
      printf("Run number: %d, Last Run: %d\nConsider a manual fix by running caf_trigger/parameters/mkruntrigvlist.py\n\n", runno, lastrun);
      exit(1);
    }
    if ( triggerversion <= 0 ) {
      cout << "caf_trigger::MuonTriggerMatch ERROR:" << endl;
      cout << "Unable to find trigger version corresponding to runno " << runno << endl;
      cout << "Is caf_trigger/parameters/runvstriglistX100.txt up-to-date ?" << endl << endl;
      exit(1);
    }

    if ( triggerversion >= _applied_trigger_version[0]-0.0001 &&
	 triggerversion <= _applied_trigger_version[1]+0.0001 ) {
      found = true;
    }    

    if ( found == false ) {
      ++_n_wrong_triglist;	    
      if (_exclude_bad_run_range)
	return( false );
      else
	return( true );
    }
  }

  // get requested muon branch, and all trigger branches we might need
  cafe::Collection<TMBMuon> muons
    = event.getCollection<TMBMuon>(_muonBranch.c_str());
  const TMBL1Muon *l1muon = event.getL1Muon();
  if (!l1muon) {
    ++_n_no_l1muon;
    ++_runs_no_l1muon[runno];
    return false;
  }
  L1MuTermsClass l1muterms(l1muon,event.isRun2b());
  cafe::Collection<TMBL2GblMuon> l2muons = event.getL2GblMuons();
  if (l2muons.size()==0) {
    ++_n_no_l2muon;
    ++_runs_no_l2muon[runno];
  }
  cafe::Collection<TMBL3Muon> l3muons = event.getL3Muons();
  if (l3muons.size()==0) {
    ++_n_no_l3muon;
    ++_runs_no_l3muon[runno];
  }
  cafe::Collection<TMBL1Track> l1tracks = event.getL1Tracks();
  if (l1tracks.size()==0) {
    ++_n_no_l1track;
    ++_runs_no_l1track[runno];
  }
  cafe::Collection<TMBL2Track> l2tracks = event.getL2STTPT();
  if (l2tracks.size()==0) {
    ++_n_no_l2track;
    ++_runs_no_l2track[runno];
  }
  
  cafe::Collection<TMBL3Track> l3tracks = event.getL3Tracks();
  if (l3tracks.size()==0) {
    ++_n_no_l3track;
    ++_runs_no_l3track[runno];
  }
  cafe::Collection<TMBL3Isolation> l3iso = event.getL3Isolations();
  if (l3iso.size()==0) {
    ++_n_no_l3iso;
    ++_runs_no_l3iso[runno];
  }
  
  // now loop over all offline muons and check which matching condition
  // they fulfill
  int nmatched[_matchconds.size()];
  memset(nmatched,0,sizeof(nmatched));
  int nmatched_muon[3],nmatched_track[3],nmatched_iso[3],nmatched_cm[3];
  memset(nmatched_muon,0,sizeof(nmatched_muon));
  memset(nmatched_track,0,sizeof(nmatched_track));
  memset(nmatched_iso,0,sizeof(nmatched_iso));
  memset(nmatched_cm,0,sizeof(nmatched_cm));
  int nmuonsmatched=0;

  for (int imuon=0; imuon<muons.size(); imuon++) {
    // offline muon properties
    double reco_phi=muons[imuon].Phi();
    double reco_deteta=muons[imuon].GetEtaDetector();
    double reco_detetaAlayer=muons[imuon].detectorEta();
    double reco_physeta=muons[imuon].Eta();
    int reco_region=muons[imuon].region();
    int reco_octant=muons[imuon].octant();

    double reco_pt=muons[imuon].Pt();
    TMBTrack *track = muons[imuon].GetChargedTrack();
    if (track) reco_pt=track->Pt();
	    
    bool found_muon[3],found_track[3],found_iso[3],found_cm[3];
    
    for (unsigned int level=0 ; level<3 ; level++) {
      _found_muon[level] = false ;
      _found_track[level] = false ;
      _found_iso[level] = false ;
      _found_cm[level] = false ;
    }
    
    //////////////////////
    // L1 muon matching //
    //////////////////////

    // require specific trigger term to be present in same or neighboring
    // region and octant as the offline muon
    found_muon[level1]=false;
    if (_check_muon[level1]) {
      if (reco_region<0) {
 	cout << name() << " WARNING: negative region number -> no match"
	     << endl;
      } 
      for (int ioct=reco_octant-1; ioct<=reco_octant+1; ioct++) {
	int octant=(ioct+8)%8;
	// some stupid arithmetics to loop over neighboring regions
	// (2 is next to 0, but not next to 1...)
	int minregion=0,maxregion=2;
        if (reco_region==0 && _trigcond_muon[level1]=="l1bttx") {
	  found_muon[level1]|=false ; 
	  continue ;  
	}	
	if (reco_region==1) maxregion=1;
	if (reco_region==2) { maxregion=3; minregion=2; }
	for (int iregion=minregion; iregion<=maxregion; iregion++) {
	  int region=(iregion%3);
	  found_muon[level1]|=l1muterms.match_trigger_named(region,octant,_l1muon_name);
	}
      }
    }

    //////////////////////
    // L2 muon matching //
    //////////////////////

    // require minimum quality and minimum Pt(),
    // and dR<0.5 between L2global object and offline muon, where
    // dR is calculated from phi and detector eta.
    // WZReco: L2 phi from iphi; L2 eta from ieta
    //         reco phi from A layer phi, or global phi if no A layer hit
    // L2 muon qualities: 1 (loose), 2 (medium), 3 (tight)
    found_muon[level2]=false;
    found_track[level2]=false;
    //////////////////// code from Sungwoon, need to modify a bit

      

                int l2size = _trigcond_muon[level2].size();

        if (l2size<6){//in case of l2gblmuon  ex)l2m3t
        if (_check_muon[level2]) {
           for (int i=0; i<l2muons.size(); i++) {
             if (l2muons[i].Quality()>=_l2muon_quality && l2muons[i].Prompt()>=_l2muon_prompt) {

              double dphi = kinem::delta_phi(reco_phi,l2muons[i].Phi());
              double deta = reco_deteta - l2muons[i].Eta();
              double dR   = sqrt(dphi * dphi + deta * deta);
	      
	      //check the dR first, otherwise go on to the next one
	      if(dR<_dR_l2muon) {
		
		//check for a track match at L2 if necessary
		if (_check_track[level2] &&  (_trigcond_track[level2].find("l2mtk") != string::npos || _trigcond_track[level2].find("l2stt") != string::npos) ) {
		  if(_trigcond_track[level2].find("l2mtk") != string::npos ) {
		    for(int ii=0; ii<l2tracks.size(); ii++){
		      double trkdphi = 3.2;
		      if (l2tracks[ii].STTPt()>_l2track_ptthreshold && l2tracks[ii].FitStatus() >=2 ) {
			trkdphi = kinem::delta_phi(l2tracks[ii].STTPhi() , l2muons[i].Phi());
			found_muon[level2]|=( trkdphi < 0.07853  );  //0.07853 = 2Pi / 80
		      }
		      else if(l2tracks[ii].CTTPt()>_l2track_ptthreshold ) {
			trkdphi = kinem::delta_phi(l2tracks[ii].CTTPhi() , l2muons[i].Phi());
			found_muon[level2]|=( trkdphi < 0.07853  );
		      }
		    }
		  }
		  else if (_check_track[level2] && _trigcond_track[level2].find("l2stt") != string::npos ) {   //special case of MUHI6
		    for(int ii=0; ii<l2tracks.size(); ii++){
		           double trkdphi = 3.2;
			   if (l2tracks[ii].STTPt()>_l2track_ptthreshold && l2tracks[ii].FitStatus() >=2 && l2tracks[ii].Chi2() < 5.5) {
			trkdphi = kinem::delta_phi(l2tracks[ii].STTPhi() , l2muons[i].Phi());
			found_muon[level2]|=( trkdphi < 0.07853  );
		      }
		      else if(l2tracks[ii].CTTPt() >  20. ) {
			trkdphi = kinem::delta_phi(l2tracks[ii].CTTPhi() , l2muons[i].Phi());
			found_muon[level2]|=( trkdphi < 0.07853  );
		      }
		    }
		  } //l2stt only
		} // l2 mutk match check
		else if (_check_track[level2] &&  (_trigcond_track[level2].find("l2Otk") != string::npos) ) {
		 for(int ii=0; ii<l2tracks.size(); ii++){
		           double trkdphi = 3.2;
   
		      if (l2tracks[ii].STTPt()>_l2track_ptthreshold && l2tracks[ii].FitStatus() >=2 ) {
			trkdphi = kinem::delta_phi(l2tracks[ii].STTPhi() , l2muons[i].Phi());
			found_muon[level2]|=( trkdphi < 0.1571  );  //0.07853 = 2Pi / 80
		      }
		      else if(l2tracks[ii].CTTPt()>_l2track_ptthreshold ) {
			trkdphi = kinem::delta_phi(l2tracks[ii].CTTPhi() , l2muons[i].Phi());
			found_muon[level2]|=( trkdphi < 0.1571  );
		      }
		 }
		 found_muon[level2]|=(dR<_dR_l2muon  && l2muons[i].ToroidPt() > _l2muon_ptthreshold);
		} //l2trk OR checks

		else found_muon[level2]|=(dR<_dR_l2muon  && l2muons[i].ToroidPt() > _l2muon_ptthreshold); // no track match required at L2
	      } // if(dR<_dR_l2muon) {
	     }
	   }
	} // if (_check_muon[level2])
	   
	   
	   
	   //// let's do it like this:  l2trk is L2 muon OR track only, l2Otk is L2muon OR l2mutk,  l2mtk is muon+ STT/CTT match, l2stt is STT only match
	   
	   if (_check_track[level2] &&  (_trigcond_track[level2].find("l2trk") != string::npos) ) {
	     for(int ii=0; ii<l2tracks.size(); ii++){
	       if( l2tracks[ii].STTPt()>_l2track_ptthreshold &&  l2tracks[ii].FitStatus() == 2){
		 double dphi = kinem::delta_phi(l2tracks[ii].STTPhi(), reco_phi);
			 found_muon[level2] |= (dphi < 0.1571); //0.1571 = 4*Pi/80
	       }  // if(l2tracks[ii].CTTPt()>8)
	     }   // for(int ii=0; ii<l2tracks.size(); ii++)
           }
	   
	}

	//since the l2 muon and track matching are basically joined at the hip, we set one equal to the other
	found_track[level2] =  found_muon[level2];
	//unless of course you don't require a track at level 2; then it should be true
	if(!_check_track[level2]) found_track[level2] = true;

    /////////////////////////////////////////////// end l2muon/ track matching

    //////////////////////
    // L3 muon matching //
    //////////////////////

    // require minimum quality and minimum Pt(),
    // and dphi<0.5 between L3 object and offline muon
    // L3 muon qualities: 0,1,2 (loose), 3 (medium), 4 (tight)
    found_muon[level3]=false;
    found_cm[level3]=false;
    if (_check_muon[level3] || _check_cm[level3] ) {
      for (int i=0; i<l3muons.size(); i++) {
	if (l3muons[i].ToolName()=="Muon") {
	// Ok, for p20 caf_trees Pt() no longer gives correct muon Pt
        // use PtLocal() for normal muon, PtCentral() (signed?!) for track-matched muon
        // same thing applies to Phi, Eta....etc
	  if ( event.isRun2b() ) {
        // p20 = Run2b
	  	if (l3muons[i].Quality()>=_l3muon_quality && l3muons[i].PtLocal()>_l3muon_ptthreshold) {
	    		double dphi = fabs(kinem::delta_phi(reco_phi,l3muons[i].PhiLocal()));
	    		found_muon[level3]|=(dphi<_dphi_l3muon);
	  	}
	  }
	  else {
        // p18 = Run2a
	  	if (l3muons[i].Quality()>=_l3muon_quality && l3muons[i].Pt()>_l3muon_ptthreshold) {
	    		double dphi = fabs(kinem::delta_phi(reco_phi,l3muons[i].Phi()));
	    		found_muon[level3]|=(dphi<_dphi_l3muon);
	  	}
          }
	}
	// central matching
        if (l3muons[i].ToolName()=="MUON_CM" ) {
	   if ( event.isRun2b() ) {
            	if ( fabs(l3muons[i].PtCentral())>_l3cm_ptthreshold && l3muons[i].Quality()>=_l3cm_quality ) {
          		double dphi = fabs(kinem::delta_phi(reco_phi,l3muons[i].PhiCentral()));
          		found_cm[level3]|=(dphi<_dphi_l3cm);
		}
	   }
	   else {
            	if ( l3muons[i].Pt()>_l3cm_ptthreshold && l3muons[i].Quality()>=_l3cm_quality ) {
          		double dphi = fabs(kinem::delta_phi(reco_phi,l3muons[i].Phi()));
          		found_cm[level3]|=(dphi<_dphi_l3cm);
		}
	   }	
        }
      }
    }
    
    //////////////////////////////////
    // L3 isolation matching
    //////////////////////////////////

    // require:
    // . dphi<0.2 between L3 object and offline muon
    // . iso tool name
    found_iso[level3]=false;
    if (_check_iso[level3]) {
      for (int i=0; i<l3iso.size(); i++) {
	if (l3iso[i].ToolName()==_l3iso_toolname.c_str()) {
	  double dphi = fabs(kinem::delta_phi(reco_phi,l3iso[i].Phi()));
	  found_iso[level3]|=(dphi<_dphi_l3iso);
	  //if (found_iso[level3]) {
	  //  cout << "TrackPtSum= " << l3iso[i].TrackPtSum() << endl ;
	  //  cout << "ConeEnergy= " << l3iso[i].ConeEnergy() << endl ;
	  //}
	}  
      }
    }
    
    ////////////////////////
    // L1 track matching  //
    ////////////////////////

    found_track[level1]=false;
    if (_check_track[level1]) {
      for (int i=0; i<l1tracks.size(); i++) {
	if (l1tracks[i].LowerPt()>=_l1track_ptthreshold) {
	  double dphi = fabs(kinem::delta_phi(reco_phi,l1tracks[i].Phi()));
	  if (!_l1track_iso) found_track[level1]|=(dphi<_dphi_l1trk);
	  // iso	  
	  else found_track[level1]|=(dphi<_dphi_l1trk && l1tracks[i].Iso()>0);	
	}
      }
    }


    ////////////////////////
    // L2 track matching  //
    ////////////////////////

    //  implemented as part of the l2 muon matching
    //   

  

    ////////////////////////
    // L3 track matching  //
    ////////////////////////
    
    _dR_l3trk_jets = 999. ;
    found_track[level3]=false;
    if (_check_track[level3]) {
      for (int i=0; i<l3tracks.size(); i++) {
	if (l3tracks[i].ToolName()!="PhTrk10_H") {
	  if (l3tracks[i].Pt()>_l3track_ptthreshold &&
	      l3tracks[i].nHitsXY()>=_l3track_nhits) {
	    double dphi = fabs(kinem::delta_phi(reco_phi,l3tracks[i].Phi()));
	    found_track[level3]|=(dphi<_dphi_l3trk);
	  }
	}
	cafe::Collection<TMBJet> jets = 
	  event.getCollection<TMBJet>("GoodJCCB") ;
	for (unsigned int ijet=0 ; ijet<jets.size() ; ijet++) {
	  double dR_tmp = fabs(kinem::delta_R(l3tracks[i].DetEta(), 
					      l3tracks[i].Phi(), 
					      jets[ijet].detEta(),
					      jets[ijet].Phi())) ;
	  if (dR_tmp < _dR_l3trk_jets) _dR_l3trk_jets = dR_tmp ;
	}	
      }
      event.put("l3track_min_dR", _dR_l3trk_jets) ;      
    }

    //////////////////////////////////////////////////////////////////////////
    // does pattern of found trigger objects match any matching conditions? //
    //////////////////////////////////////////////////////////////////////////

    bool matchany=false;
    for (int icond=0; icond<_matchconds.size(); icond++) {
      bool match=true;
      for (int ilevel=0; ilevel<3; ilevel++) {
	if (_matchconds[icond][ilevel]) {
	  if (_check_muon[ilevel])  match&=found_muon[ilevel];
	  if (_check_track[ilevel]) match&=found_track[ilevel];
          if (_check_iso[ilevel]) match&=found_iso[ilevel];
          if (_check_cm[ilevel]) match&=found_cm[ilevel];
	}
      }
      if (match) ++nmatched[icond];
      matchany|=match;
    }

    // book keeping: total number of muons fulfilling at least one matching
    // condition, and total number of muons matched to specific trigger objects
    if (matchany) ++nmuonsmatched;
    for (int ilevel=0; ilevel<3; ilevel++) {
      if (found_muon[ilevel]) ++nmatched_muon[ilevel];
      if (found_track[ilevel]) ++nmatched_track[ilevel];
      if (found_iso[ilevel]) ++nmatched_iso[ilevel];
      if (found_cm[ilevel]) ++nmatched_cm[ilevel];     
    }
    
    // test if the muon, track, iso, or cm term are matched to at least one muon
    for (unsigned int ilevel=0; ilevel<3; ilevel++) {
      _found_muon[ilevel] |= found_muon[ilevel] ;
      _found_track[ilevel] |= found_track[ilevel] ;
      _found_iso[ilevel] |= found_iso[ilevel] ;
      _found_cm[ilevel] |= found_cm[ilevel] ;
    }
    
  }

  // did we find at least one muon for each matching condition?
  bool allmatched=true;
  for (int icond=0; icond<_matchconds.size(); icond++) {
    allmatched&=(nmatched[icond]>0);
  }
  // make sure we had at least as many muons matching any condition
  // as we had different matching conditions. otherwise we might pass
  // situations where a single muon fulfilled both conditions.
  allmatched&=(nmuonsmatched>=_matchconds.size());


  // if this event did not pass, provide debug output that will help
  // understand what went wrong
  if (debug() && !allmatched) {
    const TMBGlobal *global = event.getGlobal();
    cout << "--------MuonTriggerMatch " << name() << ": run " << global->runno()
	 << " event " << global->evtno() << " failed matching requirements, debugging printout starts"
	 << endl;

    // offline muon debug output
    cout << " number of offline muons in branch " << _muonBranch
	 << ": " << muons.size() << endl;
    for (int i=0; i<muons.size(); i++) {
      cout << " offline muon " << i << ": phi=" << muons[i].Phi()
	   << ", eta=" << muons[i].Eta() << ", region=" << muons[i].region()
	   << ", octant=" << muons[i].octant() << endl;
    }

    // L1 muon debug output
    if (_check_muon[level1]) {
    	std::stringstream l1mulist;
    	int nl1mu=0;
    	for (int iregion=0; iregion<3; iregion++) {
      		for (int ioctant=0; ioctant<7; ioctant++) {
			if (l1muterms.match_trigger_named(iregion,ioctant,_l1muon_name)) {
	  			++nl1mu;
	  			if (iregion==0) {
	    				l1mulist << " central";
	  			} else if (iregion==1) {
	    					l1mulist << " north  ";
	  			} else {
	    					l1mulist << " south  ";
	  			}
	  			l1mulist << " octant " << ioctant << endl;
			}
      		}
    	}
    		
    	cout << " number of L1 muon octants with " << _l1muon_name << " trigger: "
	 	<< nl1mu << endl;
    	cout << " (number of L1 muons matched to offline: "
		 << nmatched_muon[0] << ")" << endl << l1mulist.str();;
    	if (nl1mu<2) {
      	// sometimes there are two hits in the same octant. we can only
      	// check this by looking at whether the dimuon trigger bit is set
      		std::string dimuname="mu2"+_l1muon_name.substr(3,999);
    	  	if (l1muterms.get_mtm_named(dimuname)) {
			cout << " (" << dimuname << " fired)" << endl;
      		} else {
			cout << " (" << dimuname << " did not fire)" << endl;
      		}
    	}
    }	

    // L2 muon debug output
    if (_check_muon[level2]) {    
    	std::stringstream l2mulist;
    	int nl2mu=0;
    	for (int i=0; i<l2muons.size(); i++) {
      		bool selected=(l2muons[i].Quality()>=_l2muon_quality &&
      		     l2muons[i].Prompt()>=_l2muon_prompt &&
		     l2muons[i].ToroidPt()>_l2muon_ptthreshold);

		if (_check_track[level2]) {
		  bool trkmatch = false;
	if (_check_track[level2] &&  (_trigcond_track[level2].find("l2mtk") != string::npos || _trigcond_track[level2].find("l2stt") != string::npos) ) {

		     
		  if(_trigcond_track[level2].find("l2mtk") != string::npos ) {

		    for(int ii=0; ii<l2tracks.size(); ii++){

		      double trkdphi = 3.2;
		      if (l2tracks[ii].STTPt()>_l2track_ptthreshold && l2tracks[ii].FitStatus() >=2 ) {
			trkdphi = kinem::delta_phi(l2tracks[ii].STTPhi() , l2muons[i].Phi());
			 trkmatch |=( trkdphi < 0.07853  );  //0.07853 = 2Pi / 80
		      }
		      else if(l2tracks[ii].CTTPt()>_l2track_ptthreshold ) {
			trkdphi = kinem::delta_phi(l2tracks[ii].CTTPhi() , l2muons[i].Phi());
			trkmatch |=( trkdphi < 0.07853  );
		      }
		    }
		  }
		  else if (_check_track[level2] && _trigcond_track[level2].find("l2stt") != string::npos ) {   //special case of MUHI6
		    for(int ii=0; ii<l2tracks.size(); ii++){
		           double trkdphi = 3.2;
			   if (l2tracks[ii].STTPt()>_l2track_ptthreshold && l2tracks[ii].FitStatus() >=2 && l2tracks[ii].Chi2() < 5.5) {
			trkdphi = kinem::delta_phi(l2tracks[ii].STTPhi() , l2muons[i].Phi());
			trkmatch |=( trkdphi < 0.07853  );
		      }
		      else if(l2tracks[ii].CTTPt() >  20. ) {
			trkdphi = kinem::delta_phi(l2tracks[ii].CTTPhi() , l2muons[i].Phi());
			trkmatch |=( trkdphi < 0.07853  );
		      }
		    }
		  } //l2stt only
		} // l2 mutk match check
		else if (_check_track[level2] &&  (_trigcond_track[level2].find("l2Otk") != string::npos) ) {
		 for(int ii=0; ii<l2tracks.size(); ii++){
		           double trkdphi = 3.2;
   
		      if (l2tracks[ii].STTPt()>_l2track_ptthreshold && l2tracks[ii].FitStatus() >=2 ) {
			trkdphi = kinem::delta_phi(l2tracks[ii].STTPhi() , l2muons[i].Phi());
			selected  |=( trkdphi < 0.1571  );  //0.07853 = 2Pi / 80
		      }
		      else if(l2tracks[ii].CTTPt()>_l2track_ptthreshold ) {
			trkdphi = kinem::delta_phi(l2tracks[ii].CTTPhi() , l2muons[i].Phi());
			selected  |=( trkdphi < 0.1571  );
		      }
		 }
		trkmatch  |= ( l2muons[i].ToroidPt() > _l2muon_ptthreshold);
		} //l2trk OR checks
	
		else trkmatch |=( l2muons[i].ToroidPt() > _l2muon_ptthreshold); // no track match required at L2
	
	selected &= trkmatch;
		}
      		if (selected) l2mulist << " "; else l2mulist << " (";
      		l2mulist << "phi=" << l2muons[i].Phi() << ", eta=" << l2muons[i].Eta()
	       		<< ", quality=" << l2muons[i].Quality() << ", ToroidPt="
	       		<< l2muons[i].ToroidPt();
	        if ( _l2muon_prompt > 0 ) l2mulist << ", prompt=" << l2muons[i].Prompt();
      		if (!selected) l2mulist << ")";
      		l2mulist << endl;
      		if (selected) ++nl2mu;
    	}
    	if ( _l2muon_prompt > 0 ) {
    		cout << " number of L2 muons passing quality, pt and tight scintillator cuts: " << nl2mu << endl;
    	}	
    	else {
    	        cout << " number of L2 muons passing quality and pt cuts: " << nl2mu << endl;
    	}
    	cout << " (number of L2 muons matched to offline: " << nmatched_muon[1] << ")" << endl << l2mulist.str();
    }
    
    /// L2 matching debug from Sungwoon, again some mods needed


//     if (_check_muon[level2]) {
//         std::stringstream l2mulist;
//         std::stringstream l2matchlist;
//         int nl2mu=0;
//         int nl2match=0;
//         for (int i=0; i<l2muons.size(); i++) {
//         bool selected1;

//                 for(int ii=0; ii<l2tracks.size(); ii++){
//                         selected1=( (l2tracks[ii].CTTPt()>_l2muon_ptthreshold || l2tracks[ii].CTTPt()>_l2muon_ptthreshold) && (kinem::delta_phi(l2tracks[ii].CTTPhi(),l2muons[i].Phi())<0.1571 || kinem::delta_phi(l2tracks[ii].STTPhi(),l2muons[i].Phi())<0.1571) );
//                         if (selected1) l2matchlist << " "; else l2matchlist << " (";
//                         l2matchlist << " CTTphi=" << l2tracks[ii].CTTPhi() << " STTphi=" << l2tracks[ii].STTPhi() <<" and dphiCTT="<< kinem::delta_phi(l2tracks[ii].CTTPhi(),l2muons[i].Phi()) << " and dphiSTT="<< kinem::delta_phi(l2tracks[ii].STTPhi(),l2muons[i].Phi()) <<  " CTT pT=" << l2tracks[ii].CTTPt() << " STT pT=" << l2tracks[ii].STTPt();
//                         if(!selected1) l2matchlist << ")";
//                         l2matchlist << endl;
//                         if (selected1) ++nl2match;


//                 }//for(int ii=0; ii<l2tracks.size(); ii++)
//                 cout << " number of L2 muons matched to L2 tracks : " << nl2match << endl << l2matchlist.str();

//                 bool selected=(selected1==1 && l2muons[i].Quality()>=_l2muon_quality);
//                 if (selected) l2mulist << " "; else l2mulist << " (";
//                 l2mulist << "phi=" << l2muons[i].Phi() << ", eta=" << l2muons[i].Eta()
//                         << ", quality=" << l2muons[i].Quality();
//                 if (!selected) l2mulist << ")";
//                 l2mulist << endl;
//                 if (selected) ++nl2mu;
//         }//for i++
//                 cout << " number of L2 muons passing quality and pt cuts: " << nl2mu << endl;

//                 cout << " (number of L2 muons matched to offline: " << nmatched_muon[1] << ")" << endl << l2mulist.str();
//         }//if (_check_muon[level2])







    // L3 muon debug output
    if (_check_muon[level3]) {
        bool selected;
    	std::stringstream l3mulist;
    	int nl3mu=0;    
    	for (int i=0; i<l3muons.size(); i++) {
                if ( event.isRun2b() ) {
      		  selected=(l3muons[i].Quality()>=_l3muon_quality &&
		     l3muons[i].PtLocal()>_l3muon_ptthreshold);
      		  if (selected) l3mulist << " "; else l3mulist << " (";
      		  l3mulist << "phiLocal=" << l3muons[i].PhiLocal() << ", etaLocal=" << l3muons[i].EtaLocal()
	       		<< ", quality=" << l3muons[i].Quality() << ", PtLocal="
	       		<< l3muons[i].PtLocal();
		}
		else {
      		  selected=(l3muons[i].Quality()>=_l3muon_quality &&
		     l3muons[i].Pt()>_l3muon_ptthreshold);
      		  if (selected) l3mulist << " "; else l3mulist << " (";
      		  l3mulist << "phi=" << l3muons[i].Phi() << ", eta=" << l3muons[i].Eta()
	       		<< ", quality=" << l3muons[i].Quality() << ", Pt="
	       		<< l3muons[i].Pt();
		}
      		if (!selected) l3mulist << ")";
      		l3mulist << endl;
      		if (selected) ++nl3mu;
    	}
    	cout << " number of L3 muons passing quality and pt cuts: " << nl3mu << endl;
    	cout << " (number of L3 muons matched to offline: " << nmatched_muon[2] << ")" << endl << l3mulist.str();
    }
    
    // L3 CM debug output
    if (_check_cm[level3]) {
	bool selected;
    	std::stringstream l3cmlist;
    	int nl3cm=0;    
    	for (int i=0; i<l3muons.size(); i++) {
        	if (l3muons[i].ToolName()=="MUON_CM") {
			if ( event.isRun2b() ) {
      			  selected=(l3muons[i].Quality()>=_l3cm_quality &&
		     		fabs(l3muons[i].PtCentral())>_l3cm_ptthreshold);
      			  if (selected) l3cmlist << " "; else l3cmlist << " (";
      			  l3cmlist << "phiCentral=" << l3muons[i].PhiCentral() << ", etaCentral=" << l3muons[i].EtaCentral()
	       			<< ", quality=" << l3muons[i].Quality() << ", PtCentral="
	       			<< l3muons[i].PtCentral();
			}
			else {
      			  selected=(l3muons[i].Quality()>=_l3cm_quality &&
		     		fabs(l3muons[i].Pt())>_l3cm_ptthreshold);
      			  if (selected) l3cmlist << " "; else l3cmlist << " (";
      			  l3cmlist << "phi=" << l3muons[i].Phi() << ", eta=" << l3muons[i].Eta()
	       			<< ", quality=" << l3muons[i].Quality() << ", Pt="
	       			<< l3muons[i].Pt();
			}
      			if (!selected) l3cmlist << ")";
      			l3cmlist << endl;
      			if (selected) ++nl3cm;
		}	
    	}
	cout << " number of L3 cms passing " << _trigcond_cm[level3] << ": " << nl3cm << endl;
    	cout << " (number of L3 cms matched to offline: " << nmatched_cm[2] << ")" << endl << l3cmlist.str();
    }    	
    
    // L3 iso debug output
    if (_check_iso[level3]) {
    	cout << "number of L3 muons passing iso " << _trigcond_iso[level3] << ": " << nmatched_iso[2] << endl;
    }
     
    // L1 track debug output
    if (_check_track[level1]) {
    	std::stringstream l1trklist;
    	int nl1trk=0;
    	int nl1trk_iso=0;
    	for (int i=0; i<l1tracks.size(); i++) {
      		bool selected=(l1tracks[i].LowerPt()>=_l1track_ptthreshold);
      		if (selected) l1trklist << " "; else l1trklist << " (";
      		l1trklist << "phi=" << l1tracks[i].Phi() << ", pt between "
			<< l1tracks[i].LowerPt() << " and " << l1tracks[i].UpperPt();
      		if (!selected) l1trklist << ")";
      		l1trklist << endl;
      		if (selected) ++nl1trk;
      		if (_l1track_iso) selected &= (l1tracks[i].Iso()); 
    	}
    	cout << " number of L1 tracks passing pt cut: " << nl1trk << endl;
    	if (_l1track_iso)
      		cout << "number of L1 tracks passing iso: " << nl1trk_iso << endl;
    	cout << " (number of L1 tracks matched to offline: "
	 	<< nmatched_track[0] << ")" << endl << l1trklist.str();
    }		

    //from sungwoon, check whether a CTT track is ok... probably is
    // L2 track debug output - swcho for l2trk20
         if (_check_track[level2]) {
             std::stringstream l2trklist;
             int nl2trk=0;
             for (int i=0; i<l2tracks.size(); i++) {
                     bool selected=(l2tracks[i].STTPt()>=_l2track_ptthreshold && l2tracks[i].FitStatus()==2);
                     if (selected) l2trklist << " "; else l2trklist << " (";
                     l2trklist << "phi=" << l2tracks[i].STTPhi() << ", pt "
                             << l2tracks[i].STTPt() << " and FitStatus " << l2tracks[i].FitStatus();
                     if (!selected) l2trklist << ")";
                     l2trklist << endl;
                     if (selected) ++nl2trk;
             }
             cout << " number of L2 tracks passing pt cut: " << nl2trk << endl;
             cout << " (number of L2 tracks matched to offline: "
                     << nmatched_track[0] << ")" << endl << l2trklist.str();
             }


    // L3 track debug output
    if (_check_track[level3]) {
    	std::stringstream l3trklist;
    	int nl3trk=0;
    	for (int i=0; i<l3tracks.size(); i++) {
      		bool selected=(l3tracks[i].Pt()>_l3track_ptthreshold);
      		if (selected) l3trklist << " "; else l3trklist << " (";
      		l3trklist << "phi=" << l3tracks[i].Phi() << ", pt=" << l3tracks[i].Pt();
      		if (!selected) l3trklist << ")";
      		l3trklist << endl;
      		if (selected) ++nl3trk;
    	}
    	cout << " number of L3 tracks passing pt cut: " << nl3trk << endl;
    	cout << " (number of L3 tracks matched to offline: "
	 	<< nmatched_track[2] << ")" << endl << l3trklist.str();
    }
    
    // summary debug output   
    cout << "--------event " << global->evtno() << " matching summary:" << endl;
    for (int ilevel=0; ilevel<3; ilevel++) {
      int nrequired=0;
      for (int icond=0; icond<_matchconds.size(); icond++) {
	if (_matchconds[icond][ilevel] && _check_muon[ilevel]) {
	  ++nrequired;
	}
      }
      cout << " muon level " << ilevel+1 << ": required " << nrequired
	   << ", found " << nmatched_muon[ilevel] << endl;
    }
    
    for (int ilevel=2; ilevel<3; ilevel++) {
      int nrequired=0;
      for (int icond=0; icond<_matchconds.size(); icond++) {
	if (_matchconds[icond][ilevel] && _check_cm[ilevel]) {
	  ++nrequired;
	}
      }
      cout << " cm level " << ilevel+1 << ": required " << nrequired
	   << ", found " << nmatched_cm[ilevel] << endl;
    }
        
    for (int ilevel=0; ilevel<3; ilevel++) {
      int nrequired=0;
      for (int icond=0; icond<_matchconds.size(); icond++) {
	if (_matchconds[icond][ilevel] && _check_track[ilevel]) {
	  ++nrequired;
	}
      }
      cout << " tracking level " << ilevel+1 << ": required " << nrequired
	   << ", found " << nmatched_track[ilevel] << endl;
    }	   
	   
    for (int ilevel=2; ilevel<3; ilevel++) {
      int nrequired=0;
      for (int icond=0; icond<_matchconds.size(); icond++) {
	if (_matchconds[icond][ilevel] && _check_iso[ilevel]) {
	  ++nrequired;
	}
      }
      cout << " iso level " << ilevel+1 << ": required " << nrequired
	   << ", found " << nmatched_iso[ilevel] << endl;	   
    }
    
    cout << "--------MuonTriggerMatch " << name() << ": run " << global->runno()
	 << " event " << global->evtno() << " debugging printout ends" << endl;   
  }


  // counting matched events
  if ( allmatched ) ++_n_matched_events;
  
  return allmatched;
	}



void MuonTriggerMatch::finish() {

  // print event counters
  cout << "==============================================================="
       << endl;
  cout << "MuonTriggerMatch " << name() << endl;
  
  cout << "number of events processed by MuonTriggerMatch              : "
       << setw(6) << _n_events << endl;
       
  cout << "number of events found to be matched by MuonTriggerMatch    : "
       << setw(6) << _n_matched_events << endl;
   
  cout << "number of events failed due to trigger list version mismatch: "
       << setw(6) << _n_wrong_triglist << endl;
  if (_check_muon[0]) {
    cout << "number of events with no L1 muons at all                    : "
	 << setw(6) << _n_no_l1muon << endl;
    for (map<int,int>::iterator it=_runs_no_l1muon.begin();
	 it!=_runs_no_l1muon.end(); it++) {
      cout << "  MuonTriggerMatch WARNING: " << (*it).second
	   << " out of " << _allruns[(*it).first] << " events from run "
	   << (*it).first << " without any L1 muons" << endl;
    }
  }
  if (_check_muon[1]) {
    cout << "number of events with no L2 muons at all                    : "
	 << setw(6) << _n_no_l2muon << endl;
    for (map<int,int>::iterator it=_runs_no_l2muon.begin();
	 it!=_runs_no_l2muon.end(); it++) {
      cout << "  MuonTriggerMatch WARNING: " << (*it).second
	   << " out of " << _allruns[(*it).first] << " events from run "
	   << (*it).first << " without any L2 muons" << endl;
    }
  }
  if (_check_muon[2] || _check_cm[2]) {
    cout << "number of events with no L3 muons at all                    : "
	 << setw(6) << _n_no_l3muon << endl;
    for (map<int,int>::iterator it=_runs_no_l3muon.begin();
	 it!=_runs_no_l3muon.end(); it++) {
      cout << "  MuonTriggerMatch WARNING: " << (*it).second
	   << " out of " << _allruns[(*it).first] << " events from run "
	   << (*it).first << " without any L3 muons" << endl;
    }
  }
  if (_check_track[0]) {
    cout << "number of events with no L1 tracks at all                   : "
	 << setw(6) << _n_no_l1track << endl;
    for (map<int,int>::iterator it=_runs_no_l1track.begin();
	 it!=_runs_no_l1track.end(); it++) {
      cout << "  MuonTriggerMatch WARNING: " << (*it).second
	   << " out of " << _allruns[(*it).first] << " events from run "
	   << (*it).first << " without any L1 tracks" << endl;
    }
  }
 if (_check_track[1]) {
    cout << "number of events with no L2 tracks at all                   : "
	 << setw(6) << _n_no_l2track << endl;
    for (map<int,int>::iterator it=_runs_no_l2track.begin();
	 it!=_runs_no_l2track.end(); it++) {
      cout << "  MuonTriggerMatch WARNING: " << (*it).second
	   << " out of " << _allruns[(*it).first] << " events from run "
	   << (*it).first << " without any L2 tracks" << endl;
    }
  }
  if (_check_track[2]) {
    cout << "number of events with no L3 tracks at all                   : "
	 << setw(6) << _n_no_l3track << endl;
    for (map<int,int>::iterator it=_runs_no_l3track.begin();
	 it!=_runs_no_l3track.end(); it++) {
      cout << "  MuonTriggerMatch WARNING: " << (*it).second
	   << " out of " << _allruns[(*it).first] << " events from run "
	   << (*it).first << " without any L3 tracks" << endl;
    }
  }
  if (_check_iso[2]) {  // only l3iso
    cout << "number of events with no L3 isolated muons at all           : "
         << setw(6) << _n_no_l3iso << endl;
    for (map<int,int>::iterator it=_runs_no_l3iso.begin();
         it!=_runs_no_l3iso.end(); it++) {
      cout << "  MuonTriggerMatch WARNING: " << (*it).second
           << " out of " << _allruns[(*it).first] << " events from run "
           << (*it).first << " without any L3 isolated muons" << endl;
    }
  }  
  // the following counters are not yet filled
  //cout << "number of events with not enough matched L1 muons      : "
  //     << setw(6) << _n_nomatch_l1muon << endl;
  //cout << "number of events with not enough matched L2 muons      : "
  //     << setw(6) << _n_nomatch_l2muon << endl;
  //cout << "number of events with not enough matched L3 muons      : "
  //     << setw(6) << _n_nomatch_l3muon << endl;
  //cout << "number of events with not enough matched L1 tracks     : "
  //     << setw(6) << _n_nomatch_l1track << endl;
  //cout << "number of events with not enough matched L3 tracks     : "
  //     << setw(6) << _n_nomatch_l3track << endl;
  cout << "==============================================================="
       << endl;

}

// To be used in MuonTriggerORMatch
map<string, bool>  MuonTriggerMatch::getMuonTermTestResults() { 
  map<string, bool> res ;
  for (unsigned int level=0 ; level<3 ; level++)
    if (_trigcond_muon[level].size()) 
      res[ _trigcond_muon[level] ] = (bool) (_found_muon[level]>0) ;
  return res ;
}

map<string, bool>  MuonTriggerMatch::getTrackTermTestResults() {
  map<string, bool> res ;
  for (unsigned int level=0 ; level<3 ; level++)
    if (_trigcond_track[level].size()) 
      res[ _trigcond_track[level] ] = (bool) (_found_track[level]>0) ;
  return res ;
}

map<string, bool>  MuonTriggerMatch::getIsoTermTestResults() {
  map<string, bool> res ;
  for (unsigned int level=0 ; level<3 ; level++)
    if (_trigcond_iso[level].size()) 
      res[ _trigcond_iso[level] ] = (bool) (_found_iso[level]>0) ;
  return res ;
}

map<string, bool> MuonTriggerMatch::getCMTermTestResults() {
  map<string, bool> res ;
  for (unsigned int level=0 ; level<3 ; level++)
    if (_trigcond_cm[level].size())
      res[ _trigcond_cm[level] ] = (bool) (_found_cm[level]>0) ;
  return res ;
}

double MuonTriggerMatch::getDR_l3trk_jets() {
  return _dR_l3trk_jets ;
}

ClassImp(MuonTriggerMatch)
