///////////////////////////////// TauTriggerMatch.cpp ////////////////////////
// By Ken Herner
// Purpose:  Match offline taus to tau trigger objects in data when using triggers
// that have hadronic tau requirements.  To be run on data only.
//
//
//
////////////////////////////////////////////////////////////////////////////////
#include "caf_trigger/TauTriggerMatch.hpp"
#include "cafe/Event.hpp"
#include "tmb_tree/TMBTau.hpp"
#include "tmb_tree/TMBL1Cal2bTau.hpp"
#include "tmb_tree/TMBL1Cal2bJet.hpp"
#include "tmb_tree/TMBL1Cal2bBase.hpp"
#include "tmb_tree/TMBL2Jet.hpp"
#include "tmb_tree/TMBL2Track.hpp"
#include "tmb_tree/TMBL1Cal2bSeed.hpp"
#include "tmb_tree/TMBL3Track.hpp"
#include "tmb_tree/TMBL3Tau.hpp"
#include "tmb_tree/TMBTrigger.hpp"
#include "tmb_tree/TMBL1AndOr.hpp"
#include "cafe/Collection.hpp"
#include "cafe/Processor.hpp"
#include "TObjArray.h"
#include "cafe/Config.hpp"
#include "cafe/Function.hpp"
#include "tmb_tree/TMBL2Base.hpp"
#include "tmb_tree/TMBL1Track.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "caf_trigger/TriggerMap.hpp"
#include <set>
#include <map>

using namespace cafe;
using namespace std;

TauTriggerMatch::TauTriggerMatch(const char *name)
    : cafe::Processor(name)
{

 cafe::Config config(name);
 
 vec_is_a_tau_trigger = config.getVInt("IsATauTrigger",",");
 trigname = config.getVString("TrigName");
 _offline_tau = config.get("OfflineTauBranch","Tau");
 _offline_jet = config.get("OfflineJetBranch","JCCB");
 
 vec_do_jet = config.getVInt("DoJetTerm",",");
 vec_do_l1track = config.getVInt("DoL1Track",",");
 vec_muon_pt = config.getVFloat("MuonPt");
 vec_muon_eta = config.getVFloat("MuonEta");
 
 vec_jet_et = config.getVFloat("JetEt",",");
 vec_jet_eta = config.getVFloat("JetEta",",");
 vec_tau_core = config.getVFloat("TauCoreET",",");
 vec_tau_at_l2 = config.getVInt("JetIsTauAtL2",",");
 vec_tau_et = config.getVFloat("TauEt",",");
 vec_tau_eta = config.getVFloat("TauEta",",");
 vec_tau_ratio = config.getVFloat("TauRatio",",");
 vec_l1track_pt = config.getVFloat("L1TrackPt",",");
 vec_trackjet_pt = config.getVFloat("L1TrackJetPt",",");
 
 vec_l2tau_et = config.getVFloat("L2TauEt",",");
 vec_l2tau_eta = config.getVFloat("L2TauEta",",");
 vec_l2tau_ratio = config.getVFloat("L2TauRatio",",");
 vec_do_tau_stt = config.getVInt("L2TauSTT",","); 
 vec_tau_sttpt = config.getVFloat("TauSTTPt",",");
 tau_sttiso = config.get("TauSTTIso",0);
 
 vec_l3taunn = config.getVFloat("L3TauNN",",");
 vec_l3taupt = config.getVFloat("L3TauPt",",");
 vec_l3taueta = config.getVFloat("L3TauEta",",");
 vec_l3tau_ntracks = config.getVInt("L3TauNTracks",",");
 
 _match_cut = config.get("MatchdR",0.5);
 _runnumber = config.get("RunNumberCut",225246);
 _matchseeds = config.get("MatchToTauSeeds",true);
 _trkonlytau = config.get("TauTrkMatchOnly",true);
 _use_run_range = config.get("UseRunRange",false);
 _check_trigger = config.get("CheckTrigger",true); //check if the trigger fired
 _runnum_to_triggerversion = new TriggerMap();
 
 //sanity chck that you have the same number of entries in each list
 assert( vec_l3taunn.size() == vec_l3taueta.size() );
 assert(vec_l3taunn.size() == vec_l3taupt.size() );
 assert(vec_l3taunn.size() == vec_jet_et.size());
 assert(vec_l3taunn.size() == vec_tau_et.size());
 assert(vec_l3taunn.size() == vec_jet_eta.size());
 assert(vec_l3taunn.size() == vec_tau_eta.size());
 assert(vec_l3taunn.size() == vec_tau_ratio.size());
 assert(vec_l3taunn.size() == vec_l2tau_et.size());
 assert(vec_l3taunn.size() == vec_l2tau_eta.size());
 assert(vec_l3taunn.size() == vec_tau_core.size());
 assert(vec_l3taunn.size() == vec_l2tau_ratio.size());
 assert(vec_l3taunn.size() == vec_tau_sttpt.size());
 assert(vec_l3taunn.size() == vec_l1track_pt.size());
 assert(vec_l3taunn.size() == trigname.size());
 assert(vec_l3taunn.size() == vec_do_jet.size());
 assert(vec_l3taunn.size() == vec_l3tau_ntracks.size());

///////   Now we make the trigger to L1 cal term map, useful if you want to check and/or terms independent of whether the trigger fired or not.  Currently not implemented but available for future use.

 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(1, 8,2.4,0.60)",    "l1cal2b_D03"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(1,10,2.4,0.75)",  "l1cal2b_D04"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(1,15,2.4,0.50)",   "l1cal2b_D05"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(1,15,2.4,0.75)",  "l1cal2b_D06"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(1,20,2.4,0.50)",   "l1cal2b_D07"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(1,20,2.4,0.60)",   "l1cal2b_D08"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(1,20,2.4,0.75)",  "l1cal2b_D09"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(1,30,2.4,0.50)",   "l1cal2b_D10"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(1,30,2.4,0.75)",  "l1cal2b_D11"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(2,10,2.4,0.75)",  "l1cal2b_D12"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(2,15,2.4,0.50)",   "l1cal2b_D13"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(2,20,2.4,0.50)",   "l1cal2b_D14"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWTA(2,10,3.2,0.75)",  "l1cal2b_D15"));
 _l1cal_trig_to_andor_v15.insert(pair<string,const char*>("CSWJT(1,20,3.2)",  "l1cal2b_A03"));
 
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWJT(1,20,3.2)",       "l1cal2b_A03"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWJT(1,30,3.2)",       "l1cal2b_A04"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(1, 8,2.4,0.75)",   "l1cal2b_D03"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(1,10,2.4,0.75)",  "l1cal2b_D04"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(1,10,2.4,0.8)",   "l1cal2b_D05"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(1,15,2.4,0.75)",  "l1cal2b_D06"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(1,15,2.4,0.8)",   "l1cal2b_D07"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(1,15,2.4,0.85)",  "l1cal2b_D08"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(1,20,2.4,0.8)",   "l1cal2b_D09"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(1,20,2.4,0.85)",  "l1cal2b_D10"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(2, 8,2.4,0.75)",   "l1cal2b_D11"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(2,15,2.4,0.8)",   "l1cal2b_D12"));
 _l1cal_trig_to_andor_v16.insert(pair<string,const char*>( "CSWTA(2,10,3.2,0.75)",  "l1cal2b_D13"));


}



void TauTriggerMatch::begin()
{
  //  getDirectory()->cd();

  char tname[64];


  _vars.add("_trgname");
  _vars.add("_l3passed");
  _vars.add("_l2passed");
  _vars.add("_l1passed");
  _vars.add("_l3unbiased");
  _vars.add("_l2unbiased");

  //zero out our counters

  _n_events =0;
 _n_matched_events=0;
  _n_wrong_triglist=0;

  // number of rejected events because of missing/empty chunk
  _n_no_l1tau=0;
  _n_no_l1track=0;
  _n_no_l2tau=0;
  _n_no_l2track=0;
  _n_no_l3track=0;
  _n_no_l3tau=0; 
  // number of rejected events because of missing/empty chunk
  _n_nomatch_l1tau=0;
  _n_nomatch_l1track=0;
  _n_nomatch_l2tau=0;
  _n_nomatch_l2track=0;
  _n_nomatch_l3track=0;
  _n_nomatch_l3tau=0; 


}



void TauTriggerMatch::finish()
{ 

  cout<<"Number of events: "<< _n_events<<endl;
  cout<<"Number of matched events: "<< _n_matched_events<<endl;
  cout<<"Number rejected because of wrong triglist: "<< _n_wrong_triglist<<endl;

  // number of rejected events because of missing/empty chunk
  cout<<"Number rejected because of no L1 Taus: "<<  _n_no_l1tau<<endl;
  cout<<"Number rejected because of no L1 CTT tracks: "<<  _n_no_l1track<<endl;
  cout<<"Number rejected because of no L2 Taus: "<<  _n_no_l2tau<<endl;
  cout<<"Number rejected because of no L2STT tracks: "<<  _n_no_l2track<<endl;
  cout<<"Number rejected because of no L3 tracks: "<< _n_no_l3track<<endl;
  cout<<"Number rejected because of no L3 Taus: "<<_n_no_l3tau<<endl; 
}



bool TauTriggerMatch::processEvent(cafe::Event& event)
{
 ++_n_events;
  const TMBGlobal* gbl = event.getGlobal();
 int runnum = gbl->runno();
int evtnum = gbl->evtno();



 //stolen from MuonTriggerMatch
  if ( _use_run_range ) {
    bool found = false;
    float triggerversion = _runnum_to_triggerversion->TriggerVersion(runnum);
    if ( triggerversion >= _applied_trigger_version[0] &&
	 triggerversion <= _applied_trigger_version[1] ) {
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
  //get the offline branches and the default track branch

  Collection<TMBTrack> tracks = event.getTracks();
  Collection<TMBTau> offtaus = event.getCollection<TMBTau>(_offline_tau);
  Collection<TMBMuon> offmus = event.getCollection<TMBMuon>(_offline_muon);
  Collection<TMBJet> offjets = event.getCollection<TMBJet>(_offline_jet);
  Collection<TMBTrigger> triggers = event.getTriggers(); 
  
  //get L1 tracks, jets, and taus
  Collection<TMBL1Track> l1ctt = event.getL1Tracks();
  Collection<TMBL1Cal2bSeed> tauseeds = event.getL1Cal2bJetSeeds(); //really jet seeds as opposed to the tau seeds, there is a bug in the tau seeds
  Collection<TMBL1Cal2bJet> l1jets = event.getL1Cal2bJets();
  Collection<TMBL1Cal2bTau> l1taus = event.getL1Cal2bTaus();
  const TMBL1AndOr* andor = event.getL1AndOr();  
  
  //get L2 objects-- L2 taus are really L2 jets in the CAF tree
  Collection<TMBL2Track> stt = event.getL2STTPT(); 
  Collection<TMBL2Jet> l2taus = event.getL2Jets();
  
  
  //and the L3 objects
  Collection<TMBL3Track> l3tracks = event.getL3Tracks();
  Collection<TMBL3Tau> l3taus = event.getL3Taus();
  
  //check the sizes
  
  if(l1taus.size() == 0) ++_n_no_l1tau;
  if(l1ctt.size() == 0) ++_n_no_l1track;
  if(l2taus.size() == 0) ++_n_no_l2tau;
  if(stt.size() == 0) ++_n_no_l2track=0;
  if(l3tracks.size() == 0) _n_no_l3track=0;
  if(l3taus.size() == 0) ++_n_no_l3tau=0; 

  //loop over the listed triggers
  for (int itrig =0; itrig < trigname.size() ; itrig++) {
    
  //first we will loop over the triggers in our list to see if any of them are non-tau triggers.  If they are AND they fire, we return true
    if(vec_is_a_tau_trigger[itrig] == 0) {
      
      for(int testtrig =0; testtrig <triggers.size() ; testtrig++) {
	
	if( (trigname[itrig]  == triggers[testtrig].getTrgName()) && triggers[testtrig].L3Passed() ) {
	  ++_n_matched_events;
	  return true;
	}
	
      }	    
    }
  }
  
  //now loop over the offline taus
  for (int itau=0;itau< offtaus.size();itau++) {
    
    int tautype = offtaus[itau].type(); //not really needed now, but here for future cases if we have enough statistics to measure per-type efficiencies
    
    for (int itrig = 0 ; itrig < vec_tau_et.size() ; itrig++ ) {
      
      //set the numbers to the appropriate values from the vectors
      
      do_jet = vec_do_jet[itrig];
      do_l1track = vec_do_l1track[itrig];
      trackjet_pt = vec_trackjet_pt[itrig];
      jet_et = vec_jet_et[itrig];
      jet_eta = vec_jet_eta[itrig];
      tau_core = vec_tau_core[itrig];	       	     
      tau_at_l2 = vec_tau_at_l2[itrig];
      tau_et = vec_tau_et[itrig];
      tau_eta = vec_tau_eta[itrig];
      tau_ratio = vec_tau_ratio[itrig];
      l1track_pt = vec_l1track_pt[itrig];
      
      l2tau_et = vec_l2tau_et[itrig];
      _l2tau_eta = vec_l2tau_eta[itrig];
      l2tau_ratio = vec_l2tau_ratio[itrig];
      do_tau_stt = vec_do_tau_stt[itrig];
      tau_sttpt = vec_tau_sttpt[itrig];
      
      _l3taueta = vec_l3taueta[itrig];
      _l3taunn = vec_l3taunn[itrig];
      _l3taupt = vec_l3taupt[itrig];	   
      _l3tau_ntracks = vec_l3tau_ntracks[itrig];
      
      
      // first of all, check that this trigger actually fired...
      
      bool trigfired = false;
      
      for(int testtrig =0; testtrig <triggers.size() ; testtrig++) {
	
	if( (trigname[itrig]  == triggers[testtrig].getTrgName()) && triggers[testtrig].L3Passed() )  trigfired = true;
	
      }
      
      //if the bool is still false, this trigger didn't fire, so go on to the next one if we require the trigger to fire, which we almost always do...
      if(!trigfired && _check_trigger) continue;
      
      //also, if this isn't a tau trigger, no point in checking it, so continue here also
      if (vec_is_a_tau_trigger[itrig] == 0) continue;
      
      //check for a seed and a L1 track if required
      
      bool seedmatch=false;
      if(_matchseeds) {
	for(int is=0;is<tauseeds.size(); is++) {
	  
	  double seedeta = tauseeds[is].Eta()*0.2 + 0.1;
	  double seedphi  = tauseeds[is].Phi()*0.2 + 0.1;
	  if(kinem::delta_R(seedeta,seedphi,offtaus[itau].Eta(),offtaus[itau].Phi()) < _match_cut ) {seedmatch=true; break;}
	}
      }
      else seedmatch = true;
      
      if(!seedmatch) continue; //there was no jet seed near this offline tau so it wouldn't have fired the trigger. On to the next one...
      
      //this string checks for the L1CTK and/or term if it was require in this trigger
      sprintf(track_andorterm,"l1ctk-CTK(J,1,%d.,%d.,W,X,X)",(int)l1track_pt,(int)trackjet_pt);
      
      bool trkmatch =false;
      //if we require an L1 track, i.e. CTK term
      if(do_l1track) {
	
	if(andor->l1andor(track_andorterm) || (runnum < 230126) ) { //no L1CTK before run number 230126 (but there was still a L1 track required in the event), so skip the AO term part
	  
	  for(int itrk=0;itrk< l1ctt.size(); itrk++) {
	    if(l1ctt[itrk].LowerPt() >= l1track_pt && ((kinem::delta_phi(l1ctt[itrk].Phi(),offtaus[itau].Phi()) < 0.2  ))) {trkmatch=true; break;}
	  }
	  
	}
      }
      
      else trkmatch =true; //if this trigger doesn't have a CTK term
      
      //for the MTA1 suite there is never a track requirement so set to true when do_jet is true
      if(do_jet) trkmatch = true;
      
      //these lines are for checking if the and-or term fired independently of whether the full trigger fired.  Not implement for now as we really should always require the trigger to fire
      sprintf(trigbuilder,"CSWTA(1,%2.0f,%2.1f,%3.2f)",tau_et,tau_eta,tau_ratio);
      if(do_jet) sprintf(trigbuilder,"CSWJT(1,%2.0f,%2.1f)",jet_et,jet_eta);
      termstring= trigbuilder;
      
      //now check if the L1/L2/L3 objects are matched to the offline tau
      if(trkmatch) {
	if((!do_jet && tauPassL1(l1taus,offtaus[itau]))|| (do_jet && jetPassL1(l1jets,offtaus[itau]) ) )    {
	  
	  //if we passed level 1, check L2
	  
	  if(tauPassL2(l2taus,stt,offtaus[itau])) {
	    
	    //so we passed L2, now try L3
	    if(tauPassL3(l3taus,l3tracks,offtaus[itau]) ) {
	      
	      ++_n_matched_events;		      
	      //so one trigger has passed all levels.  We don't care if more did so just return a true now and skip the rest
	      return true;
	      
	    } //pased L3
	  }//if tau pass L2
	}//if you pass the and-or terms
	
      }//if trackmatch
    } //end trigger loop
  } //end tau loop
  
  return false; //if at least one trigger in the event fired and was matched, we should not get to this line.  If we get here, it means the event didn't have any matches, and/or none of the non-tau triggers in the list fired.
}//end process event


bool TauTriggerMatch::jetPassL1(cafe::Collection<TMBL1Cal2bJet>& l1jets, const TMBTau& offtau)
{
  
  for (int i=0 ; i<l1jets.size() ; i++) {
    if (l1jets[i].Et()>jet_et && fabs(l1jets[i].Eta())<jet_eta ) {
      
      //now match 
      if(kinem::delta_R(l1jets[i].Eta(),l1jets[i].Phi(),offtau.Eta(),offtau.Phi()) <= _match_cut)  return true;
    }
  }
  return false;
}


  
bool TauTriggerMatch::tauPassL1(cafe::Collection<TMBL1Cal2bTau>& l1taus, const TMBTau& offtau)
{
  for (int i=0 ; i<l1taus.size() ; i++) {
    if(kinem::delta_R(l1taus[i].Eta(),l1taus[i].Phi(),offtau.Eta(),offtau.Phi()) <= _match_cut)  {
      if (l1taus[i].Et()>tau_et && fabs(l1taus[i].Eta())<tau_eta)    {

	if (l1taus[i].Ratio()>tau_ratio && (l1taus[i].Et()*l1taus[i].Ratio()) > tau_core) return true;
      }
    }
  }
  return false;
}


bool TauTriggerMatch::tauPassL2(cafe::Collection<TMBL2Jet>& l2taus, Collection<TMBL2Track>& stt, const TMBTau& offtau) {
  
  bool itpassed=false;
  for (int i=0 ; i<l2taus.size() ; i++) {

    //check for a dR match between the offline tau and the L2 tau

    if(l2taus[i].TauEt() >= l2tau_et && l2taus[i].iEta() > int((-1.*_l2tau_eta +4.)*20.) && l2taus[i].iEta()< int((_l2tau_eta+4.)*20.) && l2taus[i].TauRatio() >= l2tau_ratio ) {

      //if these two match, check for the STT match if it is required
      if(do_tau_stt) {
	
	for(int j=0; j< stt.size();j++) {
	  //check for an STT match to the L2 tau object
	  if(abs(l2taus[i].iPhi() - stt[j].STTiPhi()) < 5 && stt[j].STTPt() > tau_sttpt && stt[j].CTTIso() >= tau_sttiso && stt[j].FitStatus()==2 && stt[j].Chi2() <= 15.5) {
	    //now match
	    if(kinem::delta_R(l2taus[i].Eta(),l2taus[i].Phi(),offtau.Eta(),offtau.Phi()) <= _match_cut) itpassed= true;
	  }
	  
	  //if the STT failed, fall back to the CTT information and check for a CTT match 
	  else if(abs(l2taus[i].iPhi() - stt[j].CTTiPhi0())< 5 && stt[j].CTTPt()> tau_sttpt && stt[j].CTTIso() >= tau_sttiso && (stt[j].FitStatus()==0 || (stt[j].FitStatus() == 2 && stt[j].Chi2()> 15.5 ))) {
	    
	    if(kinem::delta_R(l2taus[i].Eta(),l2taus[i].Phi(),offtau.Eta(),offtau.Phi()) <= _match_cut) itpassed = true;
	  }
	}
      }
      else {
	if(kinem::delta_R(l2taus[i].Eta(),l2taus[i].Phi(),offtau.Eta(),offtau.Phi()) <= _match_cut) itpassed = true;
      }
    }
  }
  return itpassed;
}

bool TauTriggerMatch::tauPassL3(cafe::Collection<TMBL3Tau>& l3taus, cafe::Collection<TMBL3Track>& l3tracks, const TMBTau& offtau)
{
  
  for (int i=0 ; i<l3taus.size() ; i++) {
        
    if(l3taus[i].NNOut() >= _l3taunn && fabs(l3taus[i].Eta()) <= _l3taueta && l3taus[i].Pt() >= _l3taupt && l3taus[i].NTracks() >= _l3tau_ntracks) {
      if(kinem::delta_R(l3taus[i].Eta(),l3taus[i].Phi(),offtau.Eta(),offtau.Phi()) <= _match_cut) {
	
	return true;
      }
    }
  }
  return false;
}


ClassImp(TauTriggerMatch);
