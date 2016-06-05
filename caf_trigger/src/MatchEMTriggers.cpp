/* File MatchEMTriggers.cpp
 *
 * Created       : Nov 28 12:31:34 CDT 2006
 * Author        : Marc Hohlfeld hohlfeld@fnal.gov
 *
 * Purpose       : This processor passes events if any electron given
 *                 to it fires the electron part of any trigger given
 *                 to it. Only triggers that actually fired are considered.
 *                 (Checking whether the trigger fired is copied from
 *                 cafe/Trigger.{hpp|cpp}, matching code is modeled after
 *                 EMTriggerMatch.{hpp|cpp} and after em_cert).
 *
 * Modified      : Dmitry Bandurin, bandurin@fnal.gov
 *               : Nov 2008 - May 2009
 * Comments      : Added possibility of trigger eff-cy calculation
 *
 * Modified      : Mika Vesterinen, mikav@fnal.gov
 *               : May 2009  
 * Comments      : Added possiblity to tag as opposed to select events. Default is still to select events. 
 */

#include <stdexcept>

#include "caf_trigger/MatchEMTriggers.hpp"
#include "caf_trigger/TriggerInfo.hpp"

#include <algorithm>
#include "cafe/Processor.hpp"
#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "tmb_tree/TMBTrigger.hpp"
#include "tmb_tree/TMBEMCluster.hpp"
#include "tmb_tree/TMBL1CalTower.hpp"
#include "tmb_tree/TMBL1Track.hpp"
#include "tmb_tree/TMBL1Cal2bEM.hpp"
#include "tmb_tree/TMBL2EM.hpp"
#include "tmb_tree/TMBL2Track.hpp"
#include "tmb_tree/TMBL3Ele.hpp"
#include "tmb_tree/TMBL3Track.hpp"
#include "tmb_tree/TMBL3Isolation.hpp"

using namespace std;

namespace caf_trigger {
  
	/// constructor 
	MatchEMTriggers::MatchEMTriggers(const char *name) 
		: cafe::Processor(name),
			_Ninput(0), _Npassed(0), _trigvars("_trgname")

	{
	}

	/// destructor
	MatchEMTriggers::~MatchEMTriggers()
	{
	}
  
	void MatchEMTriggers::begin()
	{
                /// Create map between runnumber and trigger list version
                _runnum_to_triggerversion = new TriggerMap();

		/// Here you can read parameters from the config file:
		Config config(name());

		_passed_L1 = 0;
		_passed_L2 = 0;
		_Nfailed = 0;
		vector<string> temp = config.getVString("Triggers", " ,");
		_triggerNames.insert(temp.begin(), temp.end());

		if(_triggerNames.size() == 0) {
			// for some reason I can't get warn() to work.
			fprintf(stderr, 
							"MatchEMTriggers[ %s ]: No triggers specified. All events will fail! Exiting.\n",
							name().c_str());
			exit(1);
		}

		_EMBranch         = config.get("EMBranch", "EMscone");
		_L1CalTowerBranch = config.get("L1CalTowerBranch", "L1CalEMTowers");
		_L1Cal2bBranch    = config.get("L1Cal2bBranch", "L1Cal2bEM");
		_L1TrackBranch    = config.get("L1TrackBranch", "L1Track");
		_L2EMBranch       = config.get("L2EMBranch", "L2EM");
		_L2TrackBranch    = config.get("L2TrackBranch", "STTPT");
		_L3EleBranch      = config.get("L3EleBranch", "L3Electron");
		_L3TrackBranch    = config.get("L3TrackBranch", "L3Track");
		_L3IsoBranch      = config.get("L3IsoBranch", "L3Isolation");
		_L3JetBranch      = config.get("L3JetBranch", "L3Jet");


		_L1DeltaR         = config.get("L1DeltaR", 0.4);
		_L2DeltaR         = config.get("L2DeltaR", 0.4);
		_L3DeltaR         = config.get("L3DeltaR", 0.4);
		_DoSingleEleCalOnly = config.get("DoSingleEleCalOnly", true);
		_DoSingleEleIso     = config.get("DoSingleEleIso", true);
		_DoSingleEleTrack   = config.get("DoSingleEleTrack", true);
		_DoDiEleCalOnly     = config.get("DoDiEleCalOnly", true);
		_DoDiEleIso         = config.get("DoDiEleIso", true);
		_DoDiEleTrack       = config.get("DoDiEleTrack", true);
		_DoElectronJet      = config.get("DoElectronJet", true);
		_DoElectronMuon     = config.get("DoElectronMuon", true);
		_DoElectronTau      = config.get("DoElectronTau", true);

                _EffCalc            =  config.get("EffCalc", false);
                _trigVmin           =  config.get("trigVmin", 800);
                _trigVmax           =  config.get("trigVmax", 1700);

                cout << " _EffCalc = " << _EffCalc << endl;

		printf("============================================\n");
		printf("  MatchEMTriggers[ %s ]\n\n",name().c_str());

		// If tag is an empty string, the processor will select events.
		// If tag is an non empty string, the processor will not select events                                                                                        
		// but tag them with event.put().  
		_Tag = config.get("Tag","");
		if(_Tag.size()) printf("MatchEMTriggers will pass all events\nTag = %s\n\n", _Tag.c_str());
		
// 		printf("    Triggers:             ");
// 		for(set<string>::iterator it = _triggerNames.begin();
// 				it != _triggerNames.end(); ++it) {
// 			printf("%s\n                          ", it->c_str());
// 		}

// 		printf("\n    EM input branch:      %s\n", _EMBranch.c_str());
// 		printf("\n    L1Cal Tower branch:   %s\n", _L1CalTowerBranch.c_str());
// 		printf("    L1Track branch:       %s\n", _L1TrackBranch.c_str());
// 		printf("    L1Cal2b branch:       %s\n", _L1Cal2bBranch.c_str());
// 		printf("    L2EM branch:          %s\n", _L2EMBranch.c_str());
// 		printf("    L2Track branch:       %s\n", _L2TrackBranch.c_str());
// 		printf("    L3Ele branch:         %s\n", _L3EleBranch.c_str());
// 		printf("    L3Track branch:       %s\n", _L3TrackBranch.c_str());

// 		if (_DoSingleEleCalOnly) {
// 			printf("\n    WILL MATCH all single electron triggers with CALONLY information.\n");
// 		} else {
// 			printf("\n    WILL NOT MATCH single electron triggers with CALONLY information.\n");
// 		}
// 		if (_DoSingleEleTrack) {
// 			printf("\n    WILL MATCH all single electron triggers with TRACK information.\n");
// 		} else {
// 			printf("\n    WILL NOT MATCH single electron triggers with TRACK information.\n");
// 		}
// 		if (_DoSingleEleIso) {
// 			printf("\n    WILL MATCH all single electron triggers with ISOLATION information.\n");
// 		} else {
// 			printf("\n    WILL NOT MATCH single electron triggers with ISOLATION information.\n");
// 		}
// 		if (_DoDiEleCalOnly) {
// 			printf("\n    WILL MATCH all dielectron triggers with CALONLY information.\n");
// 		} else {
// 			printf("\n    WILL NOT MATCH dielectron triggers with CALONLY information.\n");
// 		}
// 		if (_DoDiEleTrack) {
// 			printf("\n    WILL MATCH all dielectron triggers with TRACK information.\n");
// 		} else {
// 			printf("\n    WILL NOT MATCH dielectron triggers with TRACK information.\n");
// 		}
// 		if (_DoDiEleIso) {
// 			printf("\n    WILL MATCH all dielectron triggers with ISOLATION information.\n");
// 		} else {
// 			printf("\n    WILL NOT MATCH dielectron triggers with ISOLATION information.\n");
// 		}
// 		if (_DoElectronJet) {
// 			printf("\n    WILL MATCH all electron+jet triggers.\n");
// 		} else {
// 			printf("\n    WILL NOT MATCH electron+jet triggers.\n");
// 		}
// 		if (_DoElectronMuon) {
// 			printf("\n    WILL MATCH all electron+muon triggers.\n");
// 		} else {
// 			printf("\n    WILL NOT MATCH electron+muon triggers.\n");
// 		}
// 		if (_DoElectronTau) {
// 			printf("\n    WILL MATCH all electron+tau triggers.\n");
// 		} else {
// 			printf("\n    WILL NOT MATCH electron+tau triggers.\n");
// 		}

//                 if (_EffCalc) printf("\n We will run caf_trigger to calculate eff-cy (mark & pass).\n");

// 		printf("\n    L1DeltaR:             %f\n", _L1DeltaR);
// 		printf("    L2DeltaR:             %f\n", _L2DeltaR);
// 		printf("    L3DeltaR:             %f\n", _L3DeltaR);
		
		
// 		printf("\n============================================\n");

		tl57error = true;
		
	}
  
	/// add here, your comment (for Doxygen documentation) 
	bool MatchEMTriggers::processEvent(cafe::Event& event)
	{
		++_Ninput;

		if(_Tag.size()) event.put(_Tag.c_str(), (int)1) ;

		const TMBGlobal *global = event.getGlobal();
		int runnumber = global->runno();
		int evtnumber = global->evtno();              

		Collection<TMBEMCluster> EM  = event.getEM(_EMBranch);
		Collection<TMBJet> Jets = event.getJCCA();

		Collection<TMBL1CalTower> L1Towers = 
			event.getCollection<TMBL1CalTower>(_L1CalTowerBranch);
		Collection<TMBL1Track> L1Tracks = 
			event.getCollection<TMBL1Track>(_L1TrackBranch);
		Collection<TMBL1Cal2bEM> L1Cal2bEMs = 
			event.getCollection<TMBL1Cal2bEM>(_L1Cal2bBranch);
		Collection<TMBL2EM> L2EMs = 
			event.getCollection<TMBL2EM>(_L2EMBranch);
		Collection<TMBL2Track> L2Tracks = 
			event.getCollection<TMBL2Track>(_L2TrackBranch);
		Collection<TMBL3Ele> L3Ele = 
			event.getCollection<TMBL3Ele>(_L3EleBranch);
		Collection<TMBL3Track> L3Tracks = 
			event.getCollection<TMBL3Track>(_L3TrackBranch);
		Collection<TMBL3Isolation> L3Iso = 
			event.getCollection<TMBL3Isolation>(_L3IsoBranch);
		Collection<TMBTrigger> triggers = event.getTriggers(_trigvars);
			
                Collection<TMBL3Jet> L3Jet = event.getCollection<TMBL3Jet>(_L3JetBranch);

                const int trigVer = caf_trigger::global_CMTversionX100(_runnum_to_triggerversion,runnumber);

                if (trigVer < _trigVmin || trigVer > _trigVmax) return false;

		// clear the map with trigger names
                trig_f.clear();

                // set trig.firing info to "false" for all EM objects in this event.
                for (Collection<TMBEMCluster>::iterator emit = EM.begin(); emit != EM.end(); emit++) {
                    emit->SetTrigInfo(false); 
                    emit->SetTrig_SingleEleCalOnly(false);
                    emit->SetTrig_SingleEleTrack(false);
                    emit->SetTrig_SingleEleIso(false);
                    emit->SetTrig_SingleEleAny(false);
                    emit->SetTrig_SingleEleJet(false);
		    emit->SetTrig_SingleEleL3JetPt20(false);
		    emit->SetTrig_SingleEleL3JetPt25(false);
                }

		//
		// This is proportional to the number of triggers in the event
		// and about log(numUserTriggers).
		//
		for(Collection<TMBTrigger>::const_iterator it = triggers.begin();
				it != triggers.end();
				++it) {
			const std::string trigName = it->getTrgName();
			
			// check if trigger that fired is in the trigger list of the user
			if(_triggerNames.find(trigName) != _triggerNames.end()) {
				// Need to add an entry here for every trigger that you support
				// let's divide up in the v8-11, v12, v13, v14, v15 and v16 ranges.
				_FoundSingleEleCalOnly = false;
				_FoundSingleEleIso = false;
				_FoundSingleEleTrack = false;
				_FoundElectronJet = false;
				_FoundElectronMuon = false;
				_FoundElectronTau = false;
                                bool pass = false;

                                //cout <<"\n We have trigger " << trigName << " in this event! \n" << endl;	                   

				if (trigVer < 800) {
					if(tl57error) {
						fprintf(stderr, 
									"MatchEMTriggers: Does not yet support triggers in trigger version %4.2f. Please add it first.\n",
									trigVer/100.0 );
						fprintf(stderr,"For now, every event will pass");
						tl57error = false;
					}
					if(!_EffCalc) return true;
				} // end  if (trigVer < 800) {
				else if (trigVer < 1200) {
					//+------------------------------+
					//|    TriggerVersion < 12.00    |
					//+------------------------------+
				       if(_DoSingleEleCalOnly ) {
						 //cout << "SingleEleCalOnly v8-v11: FOUND MATCH for trigger " << trigName << endl;
				                pass=FindMatchSingleEleCalOnly_v811(trigName,trigVer,EM,L1Towers,L2EMs,L3Ele);   
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoSingleEleTrack ) {
						//cout << "SingleEleTrack v8-v11: FOUND MATCH for trigger " << trigName << endl;
					        pass = FindMatchSingleEleTrack_v811(trigName,trigVer,EM,L1Towers,L2EMs,L3Ele,L3Tracks);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoDiEleCalOnly ) {
					        pass=FindMatchDiEleCalOnly_v811(trigName,trigVer,EM,L1Towers,L2EMs,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoDiEleTrack ) {
					        pass=FindMatchDiEleTrack_v811(trigName,trigVer,EM,L1Towers,L3Ele,L3Tracks);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronJet ) {
						//cout << "Electron+jet v8-v11: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchEleJet_v811(trigName,EM,L1Towers,L2EMs,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronMuon) {
					        pass=FindMatchEleMuon_v811(trigName,EM,L1Towers,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(_FoundSingleEleCalOnly || _FoundSingleEleIso || _FoundSingleEleTrack ||
						 _FoundElectronJet || _FoundElectronMuon || _FoundElectronTau) {
						_Nfailed++;
					}
					else {
						fprintf(stderr, "MatchEMTriggers::processEvent: Trigger %s is not in the specified categories of triggers, does not exist in triggerlist version %4.2f or is not implemented.\n", trigName.c_str(), float(trigVer) / 100.);
					}
			  } // end  else if (trigVer < 1200) {
				else if (trigVer < 1300) {
					//+------------------------------+	
					//|    TriggerVersion < 13.00    |
					//+------------------------------+
					if(_DoSingleEleCalOnly ) {
					  //cout << "SingleEleCalOnly v12: FOUND MATCH for trigger " << trigName << endl;
					        pass =  FindMatchSingleEleCalOnly_v12(trigName,EM,L1Towers,L3Ele);
                                                // cout << "SingleEleCalOnly v12: FOUND MATCH for trigger " << trigName << endl;
//                                                 cout << "SingleEleCalOnly v12: pass = " << pass << endl;
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoSingleEleTrack) {
					  //cout << "SingleEleTrack v12: FOUND MATCH for trigger " << trigName << endl;
				   	        pass=FindMatchSingleEleTrack_v12(trigName,EM,L1Towers,L1Tracks,L3Ele,L3Tracks);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoDiEleCalOnly) {
					       pass=FindMatchDiEleCalOnly_v12(trigName,EM,L1Towers,L2EMs,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoDiEleTrack ) {
					        pass=FindMatchDiEleTrack_v12(trigName,EM,L1Towers,L1Tracks,L2EMs,L3Ele,L3Tracks);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronJet) {
						//cout << "Electron+jet v12: FOUND MATCH for trigger " << trigName << endl;
  					        pass=FindMatchEleJet_v12(trigName,EM,L1Towers,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronMuon) {
					        pass=FindMatchEleMuon_v12(trigName,EM,L1Towers,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(_FoundSingleEleCalOnly || _FoundSingleEleIso || _FoundSingleEleTrack ||
						 _FoundElectronJet || _FoundElectronMuon || _FoundElectronTau) {
						_Nfailed++;
					}
					else {
						fprintf(stderr, "MatchEMTriggers::processEvent: Trigger %s is not in the specified categories of triggers, does not exist in triggerlist version %4.2f or is not implemented.\n", trigName.c_str(), float(trigVer) / 100.);
					}
				} //  end  else if (trigVer < 1300) {
				else if (trigVer < 1400) {
					//+------------------------------+	
					//|    TriggerVersion < 14.00    |
					//+------------------------------+
					if(_DoSingleEleCalOnly) {
					        pass = FindMatchSingleEleCalOnly_v13(trigName,EM,L1Towers,L2EMs,L3Ele);
						//cout << "SingleEleCalOnly v13: FOUND MATCH for trigger " << trigName << endl;
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoSingleEleTrack) {
						//cout << "SingleEleTrack v13: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleTrack_v13(trigName,EM,L1Towers,L1Tracks,L2EMs,L2Tracks,L3Ele,L3Tracks);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoSingleEleIso ) {
						//cout << "SingleEleIso v13: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleIso_v13(trigName,EM,L1Towers,L1Tracks,L2EMs,L2Tracks,L3Ele,L3Tracks);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronMuon ) {
					        pass = FindMatchEleMuon_v13(trigName,EM,L1Towers,L2EMs,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronJet ) {
						//cout << "Electron+jet v13: FOUND MATCH for trigger " << trigName << endl;
					        pass= FindMatchEleJet_v13(trigName,EM,L1Towers,L1Tracks,L2EMs,L2Tracks,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(_FoundSingleEleCalOnly || _FoundSingleEleIso || _FoundSingleEleTrack ||
						 _FoundElectronJet || _FoundElectronMuon || _FoundElectronTau) {
						_Nfailed++;
					}
					else {
						fprintf(stderr, "MatchEMTriggers::processEvent: Trigger %s is not in the specified categories of triggers, does not exist in triggerlist version %4.2f or is not implemented.\n", trigName.c_str(), float(trigVer) / 100.);
					}
				} //  end  else if (trigVer < 1400) {
				else if (trigVer < 1500) {
					//+------------------------------+	
					//|    TriggerVersion < 15.00    |
					//+------------------------------+
					if(_DoSingleEleCalOnly) {
						//cout << "SingleEleCalOnly v14: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleCalOnly_v14(trigName,EM,L1Towers,L2EMs,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoSingleEleTrack ) {
						//cout << "SingleEleTrack v14: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleTrack_v14(trigName,EM,L1Towers,L1Tracks,L2EMs,L2Tracks,L3Ele,L3Tracks,L3Iso);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoSingleEleIso ) {
						//cout << "SingleEleIso v14: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleIso_v14(trigName,trigVer,EM,L1Towers,L2EMs,L3Iso);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronMuon ) {
					       pass=FindMatchEleMuon_v14(trigName,trigVer,EM,L1Towers,L2EMs,L3Ele, L3Iso);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronJet ) {
						//cout << "Electron+jet v14: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchEleJet_v14(trigName,EM,L1Towers,L1Tracks,L2EMs,L2Tracks,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(_FoundSingleEleCalOnly || _FoundSingleEleIso || _FoundSingleEleTrack ||
						 _FoundElectronJet || _FoundElectronMuon || _FoundElectronTau) {
						_Nfailed++;
					}
					else {
						fprintf(stderr, "MatchEMTriggers::processEvent: Trigger %s is not in the specified categories of triggers, does not exist in triggerlist version %4.2f or is not implemented.\n", trigName.c_str(), float(trigVer) / 100.);
					}
				} //  end  else if (trigVer < 1500) {
				else if (trigVer < 1600) {
					//+------------------------------+	
					//|    TriggerVersion < 16.00    |
					//+------------------------------+
					if(_DoSingleEleCalOnly) {
						//cout << "SingleEleCalOnly v15: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleCalOnly_v15(trigName,EM,L1Cal2bEMs,L2EMs,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoSingleEleTrack) {
						//cout << "SingleEleTrack v15: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleTrack_v15(trigName,EM,L1Cal2bEMs,L1Tracks,L2EMs,L2Tracks,L3Ele,L3Tracks,L3Iso);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoSingleEleIso) {
						//cout << "SingleEleIso v15: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleIso_v15(trigName,EM,L1Cal2bEMs,L2EMs,L3Ele,L3Iso);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronMuon) {
					        pass=FindMatchEleMuon_v15(trigName,EM,L1Cal2bEMs,L2EMs,L3Ele,L3Iso);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronJet) {
						//cout << "Electron+jet v15: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchEleJet_v15(trigName,EM,L1Cal2bEMs,L1Tracks,L2EMs,L2Tracks,L3Ele,L3Tracks,L3Iso);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronTau) {
					  //cout << "Electron+jet v15: FOUND MATCH for trigger " << trigName << endl;
					  pass=FindMatchEleTau_v15(trigName,EM,L1Cal2bEMs,L1Tracks,L2EMs,L2Tracks,L3Ele,L3Tracks,L3Iso);
					  if(_EffCalc) FindMatchSingleEleSCJetPt20(trigName, EM, L3Jet);
					  if(_EffCalc) FindMatchSingleEleSCJetPt25(trigName, EM, L3Jet);
					  if(pass) _Npassed++;
					  if(!_EffCalc && pass ) return true;
					}
					if(_FoundSingleEleCalOnly || _FoundSingleEleIso || _FoundSingleEleTrack ||
						 _FoundElectronJet || _FoundElectronMuon || _FoundElectronTau) {
						_Nfailed++;
					}
					else {
						fprintf(stderr, "MatchEMTriggers::processEvent: Trigger %s is not in the specified categories of triggers, does not exist in triggerlist version %4.2f or is not implemented.\n", trigName.c_str(), float(trigVer) / 100.);
					}
				} //  end  else if (trigVer < 1600) {
				else if (trigVer < 1700) {
					//+------------------------------+	
					//|    TriggerVersion < 17.00    |
					//+------------------------------+
					if(_DoSingleEleCalOnly ) {
						//cout << "SingleEleCalOnly v16: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleCalOnly_v16(trigName,EM,L1Cal2bEMs,L2EMs,L3Ele);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoSingleEleTrack) {
						//cout << "SingleEleTrack v16: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleTrack_v16(trigName,EM,L1Cal2bEMs,L1Tracks,L2EMs,L2Tracks,L3Ele,L3Tracks,L3Iso);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoSingleEleIso ) {
						//cout << "SingleEleIso v16: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchSingleEleIso_v16(trigName,EM,L1Cal2bEMs,L2EMs,L3Ele,L3Iso);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
					if(!pass && _DoElectronJet) {
						//cout << "Electron+jet v16: FOUND MATCH for trigger " << trigName << endl;
					        pass=FindMatchEleJet_v16(trigName,EM,L1Cal2bEMs,L1Tracks,L2EMs,L2Tracks,L3Ele,L3Tracks,L3Iso);
                                                if(_EffCalc) FindMatchSingleEleSCJetPt20(trigName, EM, L3Jet);
                                                if(_EffCalc) FindMatchSingleEleSCJetPt25(trigName, EM, L3Jet);
						if(pass) _Npassed++;
						if(!_EffCalc && pass ) return true;
					}
				} // end  if (trigVer < 1700) {
				else {
					//////////////////////////////
					// trigger versions v17+
					//////////////////////////////
					fprintf(stderr, 
									"MatchEMTriggers::processEvent does not yet support triggers in trigger version %4.2f. Please add it first.\n",
									trigVer/100.0 );
					exit(19);
				}
				//cout << "Trigger " << trigName << " did not fire, go to next trigger " << endl << endl; 
			} // END of  if(_triggerNames.find(trigName) != _triggerNames.end())
			//cout << endl;
		} // END of cycle over triggers
	  
                //printf("\n MatchEMTriggers: trig_f.size() = %d \n",trig_f.size());
                for( map<TMBEMCluster*, vector<string> >::iterator it = trig_f.begin(); it != trig_f.end(); ++it) {
		  //printf(" EM E: %f \n ", it->first->CalE());
                    vector<string> firedEMtrig = it->second;
                    // print fired triggers for a given EM object
                    //printf("\n firedEMtrig.size() = %d \n",firedEMtrig.size());
                    //for( int j=0; j<firedEMtrig.size(); j++) {
                    //     cout << firedEMtrig[j] << "  ";
                    //}
                    //cout << endl;
                    it->first->StoreMatchedEMTrig(it->second); 
                }


	        if(_EffCalc) return true;

		// Return result or tag event
		if(_Tag.size()){
		  event.put(_Tag.c_str(), (int)0) ;
		  return true ;
		}
				
		return false;
   
	} // processEvent
  
	void MatchEMTriggers::finish() 
	{ 
		printf("============================================\n");
		printf("  MatchEMTriggers[ %s ] SUMMARY\n\n",name().c_str());
	
		printf("    Events processed:     %5d\n",_Ninput);
		printf("    Events passed:        %5d\n",_Npassed);
		//printf("    Events failed L1:     %5d\n",_passed_L1);
		//printf("    Events failed L2:     %5d\n",_passed_L2);
		float eff = -1.0, efferr = -1.0;
		if(_Ninput) {
			eff = float(_Npassed)/float(_Ninput);
			efferr = sqrt(float(_Npassed))/float(_Ninput);
		}
		if(_Ninput) printf("    Efficiency:           %5.4f +- %5.4f\n",eff,efferr);
		//printf("    Electron input branch: %s\n"_ElectronBranch.c_str());
	
		printf("\n============================================\n");
	}
  
  
	void MatchEMTriggers::inputFileOpened(TFile *file)
	{  
	}
  
	void MatchEMTriggers::inputFileClosing(TFile *file)
	{
	}


        // store trigger name and type for a given EM object

        void MatchEMTriggers::StoreEMTrigInfo(bool emo_pass, TMBEMCluster* emp, std::string trigName, int index) {
           
             map<TMBEMCluster*, vector<string> >::iterator itm = trig_f.find(emp);		
             if ( emo_pass ) {
                emp->SetTrigInfo(true);
                if(index == 1) emp->SetTrig_SingleEleCalOnly(true);
                if(index == 2) emp->SetTrig_SingleEleTrack(true);
                if(index == 3) emp->SetTrig_SingleEleIso(true);
                if(index == 6) emp->SetTrig_SingleEleJet(true);
		if(index == 7) emp->SetTrig_SingleEleL3JetPt20(true);
		if(index == 8) emp->SetTrig_SingleEleL3JetPt25(true);
                if(index == 1 || index == 2 || index == 3) emp->SetTrig_SingleEleAny(true);

                //cout << "StoreEMTrigInfo:  trigName = " << trigName << " index = " << index << endl;

                if( itm == trig_f.end()) {
		   vector<string> trigs(1, trigName);
                   trig_f.insert(pair<TMBEMCluster*, vector<string> >(emp, trigs));
                }
                else {                        
		   vector<string> old = itm->second;                           
                   unsigned int n = old.size();                          
                   vector<string> trigs_new(n+1);                           
                   for (int i=0; i<n; i++) trigs_new[i] = old[i];
                   trigs_new[n] = trigName;                                                  
                   trig_f.erase(itm);
                   trig_f.insert(pair<TMBEMCluster*, vector<string> >( emp, trigs_new));                           
                }
             }
         }


	//+-------------------------------------------------------------------------------+
	//|                                                                               |
	//|            Methods for Triggerlist v8 -- v11                                  |
	//|                                                                               |
        //+-------------------------------------------------------------------------------+
	bool MatchEMTriggers::FindMatchSingleEleCalOnly_v811(std::string trigName, const int trigVersion,
																											 Collection<TMBEMCluster>& Ele,
																											 const Collection<TMBL1CalTower>& L1Towers,
																											 const Collection<TMBL2EM>& L2EM,
																											 const Collection<TMBL3Ele>& L3Ele) {
		_FoundSingleEleCalOnly = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                        bool emo_pass = false;     
			if (trigName == "EM_HI" || trigName == "EM_HI_SH" || trigName == "EM_HI_EMFR8" || trigName == "EM_HI_F0") {
				if (PassSingleL1Tower(10.0, emit, L1Towers)) {
					if (trigVersion < 950 || PassL2EM(12, emit, L2EM)) {
						if (trigName == "EM_HI_SH" && PassL3Ele_SHT_v811(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "EM_HI" && PassL3Ele_LOOSE_v811(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "EM_HI_EMFR8" && PassL3Ele_VERYLOOSE_v811(40.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "EM_HI_F0" && PassL3Ele_NOCUT_v811(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (trigVersion < 950 || PassL2EM(12, emit, L2EM)) {
				} // end if (PassSingleL1Tower(10.0, emit, L1Towers)) {
			} // end (trigName == "EM_HI" || trigName == "EM_HI_SH" || trigName == "EM_HI_EMFR8" || trigName == "EM_HI_F0") {
			else if (trigName == "EM_MX" && trigVersion < 820) {
				if (PassSingleL1Tower(15.0, emit, L1Towers)) {
					if (PassL3Ele_LOOSE_v811(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassSingleL1Tower(15.0, emit, L1Towers)) {
			} // end (trigName == "EM_MX") {
			else if (trigName == "EM_MX" || trigName == "EM_MX_SH" || trigName == "EM_MX_EMFR8" || trigName == "EM_MX_F0") {
				if (PassSingleL1Tower(15.0, emit, L1Towers)) {
					if (trigName == "EM_MX_SH" && PassL3Ele_SHT_v811(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "EM_MX" && PassL3Ele_LOOSE_v811(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "EM_MX_EMFR8" && PassL3Ele_VERYLOOSE_v811(40.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "EM_MX_F0" && PassL3Ele_NOCUT_v811(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassSingleL1Tower(15.0, emit, L1Towers)) {
			} // end (trigName == "EM_MX" || trigName == "EM_MX_SH" || trigName == "EM_MX_EMFR8" || trigName == "EM_MX_F0") {
			else if (trigName == "EM_HI_2EM5" || trigName == "EM_HI_2EM5_SH" || 
							 trigName == "EM_HI_2EM5_EMFR8" || trigName == "EM_HI_2EM5_F0") {
				if (PassTwoL1TowersSym(5.0, emit, L1Towers)) {
					if (trigVersion < 950 || PassL2EM(12, emit, L2EM)) {
						if (trigName == "EM_HI_2EM5_SH" && PassL3Ele_SHT_v811(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "EM_HI_2EM5" && PassL3Ele_LOOSE_v811(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "EM_HI_2EM5_EMFR8" && PassL3Ele_VERYLOOSE_v811(40.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "EM_HI_2EM5_F0" && PassL3Ele_NOCUT_v811(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (trigVersion < 950 || PassL2EM(12, emit, L2EM)) {
				} // end if (PassTwoL1TowersSym(5.0, emit, L1Towers)) {
			} // end else if (trigName == "EM_HI_2EM5" || trigName == "EM_HI_2EM5_SH") {
			else { 
				_FoundSingleEleCalOnly = false;
			} // end else {

                        int index = emo_pass ? 1 : -1;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = GoodElectrons.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}
	
	bool MatchEMTriggers::FindMatchSingleEleTrack_v811(std::string trigName, const int trigVersion,
																										 Collection<TMBEMCluster>& Ele,
																										 const Collection<TMBL1CalTower>& L1Towers, 
																										 const Collection<TMBL2EM>& L2EM,
																										 const Collection<TMBL3Ele>& L3Ele,
																										 const Collection<TMBL3Track>& L3Track) {
		_FoundSingleEleTrack = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                        bool emo_pass = false; 
			if (trigName == "EM_HI_TR" || trigName == "EM_HI_SH_TR") {
				if (PassSingleL1Tower(10.0, emit, L1Towers)) {
					if (trigVersion < 950 || PassL2EM(12, emit, L2EM)) {
						if (trigName == "EM_HI_TR" && PassL3Track_v811(25.0, 10, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "EM_HI_SH_TR" && PassL3Ele_SHT_v811(12.0, emit, L3Ele) &&
								PassL3Track_v811(12.0, 10, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if (trigVersion < 950 || PassL2EM(12, emit, L2EM)) {
				} // end if (PassSingleL1Tower(10.0, emit, L1Towers)) {
			} // end (trigName == "EM_HI_TR" || trigName == "EM_HI_SH_TR") {
			else if (trigName == "EM_MX_TR" || trigName == "EM_MX_SH_TR") {
				if (PassSingleL1Tower(15.0, emit, L1Towers)) {
					if (trigName == "EM_MX_TR" && PassL3Track_v811(25.0, 10, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					if (trigName == "EM_MX_SH_TR" && PassL3Ele_SHT_v811(12.0, emit, L3Ele) &&
							PassL3Track_v811(12.0, 10, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
				} // end if (PassSingleL1Tower(10.0, emit, L1Towers)) {
			} // end (trigName == "EM_HI_TR" || trigName == "EM_HI_SH_TR") {
			else if (trigName == "EM_HI_2EM5_TR" || trigName == "EM_HI_2EM5_SH_TR") {
				if (PassTwoL1TowersSym(5.0, emit, L1Towers)) {
					if (trigVersion < 950 || PassL2EM(12, emit, L2EM)) {
						if (trigName == "EM_HI_2EM5_TR" && PassL3Track_v811(25.0, 10, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "EM_HI_2EM5_SH_TR" && PassL3Ele_SHT_v811(12.0, emit, L3Ele) &&
								PassL3Track_v811(12.0, 10, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end  if (trigVersion < 950 || PassL2EM(12, emit, L2EM)) {
				} // end if (PassTwoL1TowersSym(5.0, emit, L1Towers)) {
			} // end else if (trigName == "EM_HI_2EM5_TR" || trigName == "EM_HI_2EM5_SH_TR") {
			else { 
				_FoundSingleEleTrack = false;
			} // end else {

                        int index = emo_pass ? 2 : -2;
   	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = GoodElectrons.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}



	bool MatchEMTriggers::FindMatchDiEleCalOnly_v811(std::string trigName, const int trigVersion,
																									 Collection<TMBEMCluster>& Ele,
																									 const Collection<TMBL1CalTower>& L1Towers,
																									 const Collection<TMBL2EM>& L2EM,
																									 const Collection<TMBL3Ele>& L3Ele) {
		if(Ele.size() < 2) return false;
                bool emo_pass = false; 
		if (trigName == "2EM_HI" && trigVersion < 920) {
			int l1from1 = 0, l1from2 = 0, l3from1 = 0;
			for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

				if (PassTwoL1TowersSym(10.0, emit, L1Towers)) l1from1++;
				if (PassSingleL1Tower(10.0, emit, L1Towers)) l1from2++;
				if (PassL3Ele_LOOSE_v811(10.0, emit, L3Ele)) l3from1++;
			}
			if ((l1from1 >= 1 || l1from2 >= 2) && l3from1 >= 1) {return true;}
		} //end 2EM_HI
		else if (trigName == "2EM_HI" || trigName == "2EM_HI_EMFR8" || trigName == "2EM_HI_SH") {
			int l1from1 = 0, l1from2 = 0, l3from1 = 0;
			for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
				if (PassTwoL1TowersSym(10.0, emit, L1Towers)) l1from1++;
				if (PassSingleL1Tower(10.0, emit, L1Towers)) l1from2++;
				if (trigName == "2EM_HI_SH" && PassL3Ele_SHT_v811(15.0, emit, L3Ele)) l3from1++;
				else if (trigName == "2EM_HI" && PassL3Ele_LOOSE_v811(20.0, emit, L3Ele)) l3from1++;
				else if (trigName == "2EM_HI_EMFR8" && PassL3Ele_VERYLOOSE_v811(40.0, emit, L3Ele)) l3from1++;
			}
			if ((l1from1 >= 1 || l1from2 >= 2) && l3from1 >= 1) {return true;}
		} //end lse if (trigName == "2EM_HI" || trigName == "2EM_HI_EMFR8" || 
		else if (trigName == "2EM_MD10_CEM10") {
			int l1from1 = 0, l1highfrom2 = 0, l1lowfrom2 = 0, l3from1 = 0;
			for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
				if (PassTwoL1TowersAsym(10.0, 5.0, emit, L1Towers)) l1from1++;
				if (PassSingleL1Tower(10.0, emit, L1Towers)) l1highfrom2++;
				if (PassSingleL1Tower(5.0, emit, L1Towers)) l1lowfrom2++;
				if (PassL3Ele_LOOSE_v811(10.0, emit, L3Ele)) l3from1++;
			}
			if ((l1from1 >= 1 || l1highfrom2 >= 2 || (l1highfrom2 >= 1 && l1lowfrom2 >=2)) && l3from1 >= 1) {return true;}
		} // end 2EM_MD10_CEM10
		else if (trigName == "2EM_MD12_CEM10") {
			int l1from1 = 0, l1highfrom2 = 0, l1lowfrom2 = 0, l2highfrom2 = 0, l2lowfrom2 = 0, l3from1 = 0;
			for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
				if (PassTwoL1TowersAsym(10.0, 5.0, emit, L1Towers)) l1from1++;
				if (PassSingleL1Tower(10.0, emit, L1Towers)) l1highfrom2++;
				if (trigVersion < 950 || PassL2EM(6.0, emit, L2EM)) l2lowfrom2++;
				if (trigVersion < 950 || PassL2EM(8.0, emit, L2EM)) l2highfrom2++;
				if (PassSingleL1Tower(5.0, emit, L1Towers)) l1lowfrom2++;
				if (PassL3Ele_LOOSE_v811(12.0, emit, L3Ele)) l3from1++;
			}
			if ((l1from1 >= 1 || l1highfrom2 >= 2 || (l1highfrom2 >= 1 && l1lowfrom2 >=2)) && 
					(l2highfrom2 >= 2 || (l2highfrom2 >= 1 && l2lowfrom2 >= 2)) && l3from1 >= 1) {return true;}
		} // end 2EM_MD12_CEM10
		else if (trigName == "2EM_2MD7") {
			int l1from1 = 0, l1from2, l2lowfrom2 = 0, l2highfrom2 = 0, l3from2 = 0;
			for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
				if (PassTwoL1TowersSym(5.0, emit, L1Towers)) l1from1++;
				if (PassSingleL1Tower(5.0, emit, L1Towers)) l1from2++;
				if (trigVersion < 950 || PassL2EM(6.0, emit, L2EM)) l2lowfrom2++;
				if (trigVersion < 950 || PassL2EM(8.0, emit, L2EM)) l2highfrom2++;
				if (PassL3Ele_LOOSE_v811(7.0, emit, L3Ele)) l3from2++;
			}
			if ((l1from1 >= 1 || l1from2 >= 2) && 
					(l2highfrom2 >= 2 || (l2highfrom2 >= 1 && l2lowfrom2 >= 2)) && l3from2 >= 2) {return true;}
		}// end 2EM_2MD7
		else if (trigName == "2EM_2MD12") {
			int l1from1 = 0, l1from2, l2lowfrom2 = 0, l2highfrom2 = 0, l3from2 = 0;
			for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
				if (PassTwoL1TowersSym(5.0, emit, L1Towers)) l1from1++;
				if (PassSingleL1Tower(5.0, emit, L1Towers)) l1from2++;
				if (trigVersion < 950 || PassL2EM(6.0, emit, L2EM)) l2lowfrom2++;
				if (trigVersion < 950 || PassL2EM(8.0, emit, L2EM)) l2highfrom2++;
				if (PassL3Ele_LOOSE_v811(12.0, emit, L3Ele)) l3from2++;
			}
			if ((l1from1 >= 1 || l1from2 >= 2) && 
					(l2highfrom2 >= 2 || (l2highfrom2 >= 1 && l2lowfrom2 >= 2)) && l3from2 >= 2) {return true;}
		}// end 2EM_2MD12
       
		return false;
	}	

		bool MatchEMTriggers::FindMatchDiEleTrack_v811(std::string trigName, const int trigVersion,
																									 Collection<TMBEMCluster>& Ele,
																									 const Collection<TMBL1CalTower>& L1Towers,
																									 const Collection<TMBL3Ele>& L3Ele,
																									 const Collection<TMBL3Track>& L3Track) {
		if(Ele.size() < 2) return false;
           
		if (trigName == "2EM_HI_SH_TR") {
			int l1from1 = 0, l1from2 = 0, l3calfrom1 = 0, l3trackfrom1;
			for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
				if (PassTwoL1TowersSym(10.0, emit, L1Towers)) l1from1++;
				if (PassSingleL1Tower(10.0, emit, L1Towers)) l1from2++;
				if (PassL3Ele_SHT_v811(12.0, emit, L3Ele)) l3calfrom1++;
				if (PassL3Track_v811(12.0, 10, 1.0, emit, L3Track)) l3trackfrom1++;
			}
			if ((l1from1 >= 1 || l1from2 >= 2) && l3calfrom1 >= 1 && l3trackfrom1 >= 1) {return true;}
		} //end lse if (trigName == "2EM_HI" || trigName == "2EM_HI_EMFR8" || 

		return false;
	}


	bool MatchEMTriggers::FindMatchEleMuon_v811(std::string trigName,Collection<TMBEMCluster>& Ele,
																							const Collection<TMBL1CalTower>& L1Towers, 
																							const Collection<TMBL3Ele>& L3Ele) {
		_FoundElectronMuon = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                        bool emo_pass = false; 
			if (trigName == "MU_EM_L3L0" || trigName == "MU_EM_L2L3L0" || trigName == "MU_EM_L2M0_L3L0" ||
					trigName == "MU_EM_L2M0" || trigName == "MU_EM_L2M5") {
				if (PassSingleL1Tower(5.0, emit, L1Towers)) {emo_pass = true; pass = true;}
			} // end if (trigName == "MU_EM_L3L0" || trigName == "MU_EM_L2L3L0" || trigName == "MU_EM_L2M0_L3L0" ||
			else if (trigName == "MU_W_EM10" || trigName == "MU_A_EM10") {
				if (PassSingleL1Tower(5.0, emit, L1Towers)) {
					if (PassL3Ele_LOOSE_v811(10.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassSingleL1Tower(5.0, emit, L1Towers)) {
			}	 // end else if (trigName == "MU_W_EM10" || trigName == "MU_A_EM10") {
			else {
				_FoundElectronMuon = false;
			}

                        int index = emo_pass ? 4 : -4;
   	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);	           

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	bool MatchEMTriggers::FindMatchEleJet_v811(std::string trigName,Collection<TMBEMCluster>& Ele,
																						 const Collection<TMBL1CalTower>& L1Towers, 
																						 const Collection<TMBL2EM>& L2EM, 
																						 const Collection<TMBL3Ele>& L3Ele) {
		_FoundElectronJet = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                        bool emo_pass = false;      
			if (trigName == "EM15_2JT15" || trigName == "EM15_2JT25") {
				if (PassSingleL1Tower(10.0, emit, L1Towers)) {
					if (PassL2EM_emf(10.0, 0.85, emit, L2EM)) {
						if (PassL3Ele_SHT_v811(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_emf(10.0, 0.85, emit, L2EM)) {
				} // end if (PassSingleL1Tower(10.0, emit, L1Towers)) {
			} // end if (trigName == "EM15_2JT15" || trigName == "EM15_2JT25") {
			else {
				_FoundElectronJet = false;
			}

                        int index = emo_pass ? 6 : -6;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}
	/*------ END METHODS FOR V8 -- V11 --------------------------------------------------------------------------------*/

	//+-------------------------------------------------------------------------------+
	//|                                                                               |
	//|            Methods for Triggerlist v12                                        |
	//|                                                                               |
  //+-------------------------------------------------------------------------------+
	bool MatchEMTriggers::FindMatchSingleEleCalOnly_v12(std::string trigName,
																											Collection<TMBEMCluster>& Ele,
																											const Collection<TMBL1CalTower>& L1Towers,
																											const Collection<TMBL3Ele>& L3Ele) {
		_FoundSingleEleCalOnly = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                        bool emo_pass = false; 
                        //cout << "  EMobject with emcl->CalE() :" << emit->CalE() << endl;
			if (trigName == "E1_VL70" || trigName == "E1_L50" || trigName == "E1_SH30" || trigName == "E1_SHT20") {
				if (PassSingleL1Tower(11.0, emit, L1Towers)) {
				        if (trigName == "E1_VL70" && PassL3Ele_VL_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E1_L50" && PassL3Ele_L_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E1_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E1_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassSingleL1Tower(11.0, emit, L1Towers)) {
			} // end if (trigName == "E1_VL70" || trigName == "E1_L50" || trigName == "E1_SH30" || trigName == "E1_SHT20") {
			else if (trigName == "E2_SH30" || trigName == "E2_SHT20") {
				if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
					if (trigName == "E2_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E2_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if (trigName == "E2_SH30" || trigName == "E2_SHT20") {
			else if (trigName == "E3_SH30" || trigName == "E3_SHT20") {
				if (PassTwoL1TowersAsym(9.0,3.0, emit, L1Towers)) {
					if (trigName == "E3_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E3_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassTwoL1TowersAsym(9.0,3.0,emit, L1Towers)) {
			} // end else if (trigName == "E3_SH30" || trigName == "E3_SHT20") {
			else { 
				_FoundSingleEleCalOnly = false;
			} // end else {
			
                        int index = emo_pass ? 1 : -1;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);
                
		} // end for (Collection<TMBEMCluster>::iterator emit = GoodElectrons.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}



	bool MatchEMTriggers::FindMatchSingleEleTrack_v12(std::string trigName,
																										Collection<TMBEMCluster>& Ele,
																										const Collection<TMBL1CalTower>& L1Towers,
																										const Collection<TMBL1Track>& L1Track,
	       																								const Collection<TMBL3Ele>& L3Ele,	
																										const Collection<TMBL3Track>& L3Track) {
		_FoundSingleEleTrack = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
		        bool emo_pass = false;                           
			if (trigName == "E1_T13L15" || trigName == "E1_T25VL30" || trigName == "E1_SHT15_TK13") {
				if (PassSingleL1Tower(11.0, emit, L1Towers)) {
					if (trigName == "E1_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E1_T25VL30" && PassL3Ele_VL_T25_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E1_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
							PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
				} // end if (PassSingleL1Tower(11.0, emit, L1Towers)) {
			} // end if (trigName == "E1_T13L15" || trigName == "E1_T25VL30" || trigName == "E1_SHT15_TK13") {
			else if (trigName == "E2_T13L15" || trigName == "E2_T25VL30" || trigName == "E2_SHT15_TK13") {
				if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
					if (trigName == "E2_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E2_T25VL30" && PassL3Ele_VL_T25_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E2_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
							PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
				} // end if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if (trigName == "E2_T13L15" || trigName == "E2_T25VL30" || trigName == "E2_SHT15_TK13") {
			else if (trigName == "E3_T13L15" || trigName == "E3_T25VL30" || trigName == "E3_SHT15_TK13") {
				if (PassTwoL1TowersAsym(9.0,3.0, emit, L1Towers)) {
					if (trigName == "E3_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E3_T25VL30" && PassL3Ele_VL_T25_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E3_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
							PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
				} // end if (PassTwoL1TowersAsym(9.0,3.0,emit, L1Towers)) {
			} // end else if (trigName == "E3_T13L15" || trigName == "E3_T25VL30" || trigName == "E3_SHT15_TK13") {
			else if (trigName == "E4_SH30" || trigName == "E4_SHT20" || 
							 trigName == "E4_T13L15" || trigName == "E4_T25VL30" || trigName == "E4_SHT15_TK13") {
				if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
					if (trigName == "E4_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E4_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E4_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E4_T25VL30" && PassL3Ele_VL_T25_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E4_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
							PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
				} // end if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
			} // end else if (trigName = "E4_SH30" || trigName == "E4_SHT20" || 
			else if (trigName == "E5_SHT15_TK13") {
				if (PassTwoL1TowersAsym(6.0, 3.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
					if (trigName == "E5_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
							PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
				} // end 
			} // end else if (trigName = "E5_SHT15_TK13") {
			else if (trigName == "E6_T13L15" || trigName == "E6_SHT15_TK13") {
				if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
					if (trigName == "E6_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if (trigName == "E6_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
							PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
				} // end 
			} // end else if (trigName = "E5_SHT15_TK13") {
			else { 
				_FoundSingleEleTrack = false;
			} // end else {
	      
                        int index = emo_pass ? 2 : -2;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);
                       
		} // end for (Collection<TMBEMCluster>::iterator emit = GoodElectrons.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}


	bool MatchEMTriggers::FindMatchDiEleCalOnly_v12(std::string trigName, 
																									Collection<TMBEMCluster>& Ele,
																									const Collection<TMBL1CalTower>& L1Towers,
																									const Collection<TMBL2EM>& L2EM,
																									const Collection<TMBL3Ele>& L3Ele) {
		if(Ele.size() < 2) return false;
		if (trigName == "E1_2SH8" || trigName == "E1_2L15_SH15" || trigName == "E1_2L20") {
			if(DiElectronPassL1(11.0, Ele, L1Towers)) {
				if(trigName == "E1_2SH8" && DiElectronPassL3_SH_v12plus(8.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E1_2L15_SH15" && DiElectronPassL3_LOOSE_v12plus(15.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_SH_v12plus(15.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E1_2L20" && DiElectronPassL3_LOOSE_v12plus(20.0, 2, Ele, L3Ele)) {return true;}
			} // end if(DiElectronPassL1(11.0, Ele, L1Towers) {
		} //end if(trigName == "E1_2SH8" || trigName == "E1_2L15_SH15" || trigName == "E1_2L20") {
		else if (trigName == "E2_2SH8" || trigName == "E2_2L15_SH15" || trigName == "E2_2L20") {
			if(DiElectronPassL1(6.0, 6.0,Ele, L1Towers)) {
				if(trigName == "E2_2SH8" && DiElectronPassL3_SH_v12plus(8.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E2_2L15_SH15" && DiElectronPassL3_LOOSE_v12plus(15.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_SH_v12plus(15.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E2_2L20" && DiElectronPassL3_LOOSE_v12plus(20.0, 2, Ele, L3Ele)) {return true;}
			} // end if(DiElectronPassL1(6.0, 6.0, Ele, L1Towers) {
		} //end if(trigName == "E2_2SH8" || trigName == "E2_2L15_SH15" || trigName == "E2_2L20") {
		else if (trigName == "E3_2SH8" || trigName == "E3_2L15_SH15" || trigName == "E3_2L20") {
			if(DiElectronPassL1(9.0, 3.0,Ele, L1Towers)) {
				if(trigName == "E3_2SH8" && DiElectronPassL3_SH_v12plus(8.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E3_2L15_SH15" && DiElectronPassL3_LOOSE_v12plus(15.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_SH_v12plus(15.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E3_2L20" && DiElectronPassL3_LOOSE_v12plus(20.0, 2, Ele, L3Ele)) {return true;}
			} // end if(DiElectronPassL1(9.0, 3.0, Ele, L1Towers) {
		} //end if(trigName == "E3_2SH8" || trigName == "E3_2L15_SH15" || trigName == "E3_2L20") {

		return false;
	}	

	bool MatchEMTriggers::FindMatchDiEleTrack_v12(std::string trigName, 
																								Collection<TMBEMCluster>& Ele,
																								const Collection<TMBL1CalTower>& L1Towers,
																								const Collection<TMBL1Track>& L1Track,
																								const Collection<TMBL2EM>& L2EM,
																								const Collection<TMBL3Ele>& L3Ele,
																								const Collection<TMBL3Track>& L3Track) {
		if(Ele.size() < 2) return false;          
		if (trigName == "E1_2L8_T8L8" || trigName == "E1_T7SHT8_2TK5") {
			if(DiElectronPassL1(11.0, Ele, L1Towers)) {
				if(trigName == "E1_2L8_T8L8" && DiElectronPassL3_LOOSE_v12plus(8.0, 2, Ele, L3Ele) &&
					 DiElectronPassL3_L_T8_v12plus(8.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E1_T7SHT8_2TK5" && DiElectronPassL3_SHT_T7_v12plus(8.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_Track_v12plus(5.0, 10, 1.0, 2, Ele, L3Track)) {return true;}
			} // end if(DiElectronPassL1(11.0, Ele, L1Towers) {
		} //end if(trigName == "E1_2L8_T8L8" || trigName == "E1_T7SHT8_2TK5") {
		else if (trigName == "E2_2L8_T8L8" || trigName == "E2_T7SHT8_2TK5" || trigName == "E2_2T5SH5" ||
						 trigName == "E2_5_11_SH5_T4L5") {
			if(DiElectronPassL1(6.0, 6.0,Ele, L1Towers)) {
				if(trigName == "E2_2L8_T8L8" && DiElectronPassL3_LOOSE_v12plus(8.0, 2, Ele, L3Ele) &&
					 DiElectronPassL3_L_T8_v12plus(8.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E2_T7SHT8_2TK5" && DiElectronPassL3_SHT_T7_v12plus(8.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_Track_v12plus(5.0, 10, 1.0, 2, Ele, L3Track)) {return true;}
				else if(trigName == "E2_2T5SH5" && DiElectronPassL3_SH_T5_v12plus(5.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E2_5_11_SH5_T4L5" && DiElectronPassL3_LOOSE_v12plus(5.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_LOOSE_v12plus(11.0, 1, Ele, L3Ele) && 
								DiElectronPassL3_SH_v12plus(5.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_L_T4_v12plus(5.0, 1, Ele, L3Ele)) {return true;}
			} // end if(DiElectronPassL1(6.0, 6.0, Ele, L1Towers) {
		} //end else if(trigName == "E2_2L8_T8L8" || trigName == "E2_T7SHT8_2TK5" || trigName == "E2_2T5SH5" ||
		else if (trigName == "E3_2L8_T8L8" || trigName == "E3_T7SHT8_2TK5" || trigName == "E3_2T5SH5" ||
						 trigName == "E3_5_11_SH5_T4L5") {
			if(DiElectronPassL1(9.0, 3.0,Ele, L1Towers)) {
				if(DiElectronPassL2(6.0, 1.6, 3.0, 1.6, Ele, L2EM)) {
					if(trigName == "E3_2L8_T8L8" && DiElectronPassL3_LOOSE_v12plus(8.0, 2, Ele, L3Ele) &&
						 DiElectronPassL3_L_T8_v12plus(8.0, 1, Ele, L3Ele)) {return true;}
					else if(trigName == "E3_T7SHT8_2TK5" && DiElectronPassL3_SHT_T7_v12plus(8.0, 1, Ele, L3Ele) &&
									DiElectronPassL3_Track_v12plus(5.0, 10, 1.0, 2, Ele, L3Track)) {return true;}
					else if(trigName == "E3_2T5SH5" && DiElectronPassL3_SH_T5_v12plus(5.0, 2, Ele, L3Ele)) {return true;}
					else if(trigName == "E3_5_11_SH5_T4L5" && DiElectronPassL3_LOOSE_v12plus(5.0, 2, Ele, L3Ele) &&
									DiElectronPassL3_LOOSE_v12plus(11.0, 1, Ele, L3Ele) && 
									DiElectronPassL3_SH_v12plus(5.0, 1, Ele, L3Ele) &&
									DiElectronPassL3_L_T4_v12plus(5.0, 1, Ele, L3Ele)) {return true;}
				} // end if(DiElectronPassL2(6.0, 1.6, 3.0, 1.6, Ele, L2EM)) {
			} // end if(DiElectronPassL1(9.0, 3.0, Ele, L1Towers) {
		} //end else if(trigName == "E3_2L8_T8L8" || trigName == "E3_T7SHT8_2TK5" || trigName == "E3_2T5SH5" ||
		else if (trigName == "E4_2SH8" || trigName == "E4_2L15_SH15" || trigName == "E4_2L20" ||
						 trigName == "E4_2L8_T8L8" || trigName == "E4_T7SHT8_2TK5" || trigName == "E4_5_11_SH5_T4L5") {
			if(DiElectronPassL1(9.0, Ele, L1Towers) && DiElectronPassL1(10.0, "TTK", Ele, L1Track)) {
				if(DiElectronPassL2(9.0, 1.6, Ele, L2EM)) {
					if(trigName == "E4_2SH8" && DiElectronPassL3_SH_v12plus(8.0, 2, Ele, L3Ele)) {return true;}
					else if(trigName == "E4_2L15_SH15" && DiElectronPassL3_LOOSE_v12plus(15.0, 2, Ele, L3Ele) &&
									DiElectronPassL3_SH_v12plus(15.0, 1, Ele, L3Ele)) {return true;}
					else if(trigName == "E4_2L20" && DiElectronPassL3_LOOSE_v12plus(20.0, 2, Ele, L3Ele)) {return true;}
					else if(trigName == "E4_2L8_T8L8" && DiElectronPassL3_LOOSE_v12plus(8.0, 2, Ele, L3Ele) &&
									DiElectronPassL3_L_T8_v12plus(8.0, 1, Ele, L3Ele)) {return true;}
					else if(trigName == "E4_T7SHT8_2TK5" && DiElectronPassL3_SHT_T7_v12plus(8.0, 1, Ele, L3Ele) &&
									DiElectronPassL3_Track_v12plus(5.0, 10, 1.0, 2, Ele, L3Track)) {return true;}
					else if(trigName == "E4_5_11_SH5_T4L5" && DiElectronPassL3_LOOSE_v12plus(5.0, 2, Ele, L3Ele) &&
									DiElectronPassL3_LOOSE_v12plus(11.0, 1, Ele, L3Ele) && 
									DiElectronPassL3_SH_v12plus(5.0, 1, Ele, L3Ele) &&
									DiElectronPassL3_L_T4_v12plus(5.0, 1, Ele, L3Ele)) {return true;}
				} // end f(DiElectronPassL2(9.0, 1.6, Ele, L2EM)) {
			} // end  if(DiElectronPassL1(9.0, Ele, L1Towers) && DiElectronPassL1(10.0, "TTK", Ele, L1Track)) {
		} //end else if (trigName == "E4_2SH8" || trigName == "E4_2L15_SH15" || trigName == "E4_2L20" ||
		else if (trigName == "E5_2SH8" || trigName == "E5_2L15_SH15" || trigName == "E5_2L20" || trigName == "E5_2T5SH5" ||
						 trigName == "E5_2L8_T8L8" || trigName == "E5_T7SHT8_2TK5" || trigName == "E5_5_11_SH5_T4L5") {
			if(DiElectronPassL1(6.0, 3.0, Ele, L1Towers) && DiElectronPassL1(10.0, "TTK", Ele, L1Track)) {
				if(trigName == "E5_2SH8" && DiElectronPassL3_SH_v12plus(8.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E5_2L15_SH15" && DiElectronPassL3_LOOSE_v12plus(15.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_SH_v12plus(15.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E5_2L20" && DiElectronPassL3_LOOSE_v12plus(20.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E5_2L8_T8L8" && DiElectronPassL3_LOOSE_v12plus(8.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_L_T8_v12plus(8.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E5_T7SHT8_2TK5" && DiElectronPassL3_SHT_T7_v12plus(8.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_Track_v12plus(5.0, 10, 1.0, 2, Ele, L3Track)) {return true;}
				else if(trigName == "E5_2T5SH5" && DiElectronPassL3_SH_T5_v12plus(5.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E5_5_11_SH5_T4L5" && DiElectronPassL3_LOOSE_v12plus(5.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_LOOSE_v12plus(11.0, 1, Ele, L3Ele) && 
								DiElectronPassL3_SH_v12plus(5.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_L_T4_v12plus(5.0, 1, Ele, L3Ele)) {return true;}
			} // end  if(DiElectronPassL1(6.0, 3.0, Ele, L1Towers) && DiElectronPassL1(10.0, "TTK", Ele, L1Track)) {
		} //end else if (trigName == "E5_2SH8" || trigName == "E5_2L15_SH15" || trigName == "E5_2L20" || trigName == "E5_2T5SH5" ||
		else if (trigName == "E6_2SH8" || trigName == "E6_2L15_SH15" || trigName == "E6_2T5SH5" ||
						 trigName == "E6_2L8_T8L8" || trigName == "E6_T7SHT8_2TK5" || trigName == "E6_5_11_SH5_T4L5") {
			if(DiElectronPassL1(6.0, Ele, L1Towers) && DiElectronPassL1(10.0, "TIS", Ele, L1Track)) {
				if(trigName == "E6_2SH8" && DiElectronPassL3_SH_v12plus(8.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E6_2L15_SH15" && DiElectronPassL3_LOOSE_v12plus(15.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_SH_v12plus(15.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E6_2L8_T8L8" && DiElectronPassL3_LOOSE_v12plus(8.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_L_T8_v12plus(8.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E6_T7SHT8_2TK5" && DiElectronPassL3_SHT_T7_v12plus(8.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_Track_v12plus(5.0, 10, 1.0, 2, Ele, L3Track)) {return true;}
				else if(trigName == "E6_2T5SH5" && DiElectronPassL3_SH_T5_v12plus(5.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E6_5_11_SH5_T4L5" && DiElectronPassL3_LOOSE_v12plus(5.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_LOOSE_v12plus(11.0, 1, Ele, L3Ele) && 
								DiElectronPassL3_SH_v12plus(5.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_L_T4_v12plus(5.0, 1, Ele, L3Ele)) {return true;}
			} // end  if(DiElectronPassL1(6.0, Ele, L1Towers) && DiElectronPassL1(10.0, "TIS", Ele, L1Track)) {
		} //end else if (trigName == "E6_2SH8" || trigName == "E6_2L15_SH15" || trigName == "E6_2T5SH5" ||
		else if (trigName == "E7A_2T5SH5" || trigName == "E7A_2L8_T8L8" || trigName == "E7A_T7SHT8_2TK5") {
			if(DiElectronPassL1(6.0, 3.0, Ele, L1Towers) && DiElectronPassL1(5.0, "TTK", 3.0, "TTK", Ele, L1Track)) {
				if(trigName == "E7A_2L8_T8L8" && DiElectronPassL3_LOOSE_v12plus(8.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_L_T8_v12plus(8.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E7A_T7SHT8_2TK5" && DiElectronPassL3_SHT_T7_v12plus(8.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_Track_v12plus(5.0, 10, 1.0, 2, Ele, L3Track)) {return true;}
				else if(trigName == "E7A_2T5SH5" && DiElectronPassL3_SH_T5_v12plus(5.0, 2, Ele, L3Ele)) {return true;}
			} // end  if(DiElectronPassL1(6.0, 3.0, Ele, L1Towers) && DiElectronPassL1(5.0, "TTK", 3.0, "TTK", Ele, L1Track)) {
		} //end else if (trigName == "E7A_2T5SH5" || trigName == "E7A_2L8_T8L8" || trigName == "E7A_T7SHT8_2TK5") {
		else if (trigName == "E7B_2T5SH5" || trigName == "E7B_2L8_T8L8" || 
						 trigName == "E7B_T7SHT8_2TK5" || trigName == "E7B_5_11_SH5_T4L5") {
			if(DiElectronPassL1(6.0, 3.0, Ele, L1Towers) && DiElectronPassL1(5.0, "TTK", 3.0, "TTK", Ele, L1Track)) {
				if(trigName == "E7B_2L8_T8L8" && DiElectronPassL3_LOOSE_v12plus(8.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_L_T8_v12plus(8.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E7B_T7SHT8_2TK5" && DiElectronPassL3_SHT_T7_v12plus(8.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_Track_v12plus(5.0, 10, 1.0, 2, Ele, L3Track)) {return true;}
				else if(trigName == "E7B_2T5SH5" && DiElectronPassL3_SH_T5_v12plus(5.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E7B_5_11_SH5_T4L5" && DiElectronPassL3_LOOSE_v12plus(5.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_LOOSE_v12plus(11.0, 1, Ele, L3Ele) && 
								DiElectronPassL3_SH_v12plus(5.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_L_T4_v12plus(5.0, 1, Ele, L3Ele)) {return true;}
			} // end  if(DiElectronPassL1(6.0, 3.0, Ele, L1Towers) && DiElectronPassL1(5.0, "TTK", 3.0, "TTK", Ele, L1Track)) {
		}// end  else if (trigName == "E7B_2T5SH5" || trigName == "E7B_2L8_T8L8" ||
		else if (trigName == "E8_2SH8" || trigName == "E8_2T5SH5" || trigName == "E8_2L8_T8L8" || 
						 trigName == "E8_T7SHT8_2TK5" || trigName == "E8_5_11_SH5_T4L5") {
			if(DiElectronPassL1(6.0, Ele, L1Towers) && DiElectronPassL1(5.0, "TIS", 5.0, "TTK", Ele, L1Track)) {
				if(trigName == "E8_2SH8" && DiElectronPassL3_SH_v12plus(8.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E8_2L8_T8L8" && DiElectronPassL3_LOOSE_v12plus(8.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_L_T8_v12plus(8.0, 1, Ele, L3Ele)) {return true;}
				else if(trigName == "E8_T7SHT8_2TK5" && DiElectronPassL3_SHT_T7_v12plus(8.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_Track_v12plus(5.0, 10, 1.0, 2, Ele, L3Track)) {return true;}
				else if(trigName == "E8_2T5SH5" && DiElectronPassL3_SH_T5_v12plus(5.0, 2, Ele, L3Ele)) {return true;}
				else if(trigName == "E8_5_11_SH5_T4L5" && DiElectronPassL3_LOOSE_v12plus(5.0, 2, Ele, L3Ele) &&
								DiElectronPassL3_LOOSE_v12plus(11.0, 1, Ele, L3Ele) && 
								DiElectronPassL3_SH_v12plus(5.0, 1, Ele, L3Ele) &&
								DiElectronPassL3_L_T4_v12plus(5.0, 1, Ele, L3Ele)) {return true;}
			} // end  if(DiElectronPassL1(6.0, Ele, L1Towers) && DiElectronPassL1(5.0, "TIS", 5.0, "TTK", Ele, L1Track)) {
		}// end  else if (trigName == "E8_2SH8" || trigName == "E8_2T5SH5" || trigName == "E8_2L8_T8L8" ||

		return false;
	}	

	bool MatchEMTriggers::FindMatchEleMuon_v12(std::string trigName,
																						 Collection<TMBEMCluster>& Ele,
																						 const Collection<TMBL1CalTower>& L1Towers,
																						 const Collection<TMBL3Ele>& L3Ele) {
		_FoundElectronMuon = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                        bool emo_pass = false;      
			if (trigName == "MATX_EM6_L12" || trigName == "MATX_EM6_SHT7" || 
					trigName == "MWLXT10_EM6_L12" || trigName == "MWLXT10_EM6_SHT7") {
				if (PassSingleL1Tower(6.0, emit, L1Towers)) {
					if ((trigName == "MATX_EM6_L12" || trigName == "MWLXT10_EM6_L12") && 
							PassL3Ele_L_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if ((trigName == "MATX_EM6_SHT7" || trigName == "MWLXT10_EM6_SHT7") && 
							PassL3Ele_SHT_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassSingleL1Tower(6.0, emit, L1Towers)) {
			} // end if (trigName == "MATX_EM6_L12" || trigName == "MATX_EM6_SHT7" || 
			else if (trigName == "MATX_2EM3_L12" || trigName == "MATX_2EM3_SHT7" || 
							 trigName == "MWLXT10_2EM3_L12" || trigName == "MWLXT10_2EM3_SHT7") {
				if (PassTwoL1TowersSym(3.0, emit, L1Towers)) {
					if ((trigName == "MATX_2EM3_L12" || trigName == "MWLXT10_2EM3_L12") && 
							PassL3Ele_L_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if ((trigName == "MATX_2EM3_SHT7" || trigName == "MWLXT10_2EM3_SHT7") && 
							PassL3Ele_SHT_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassTwoL1TowersSym(3.0, emit, L1Towers)) {
			} // end else if (trigName == "MATX_2EM3_L12" || trigName == "MATX_2EM3_SHT7" || 
			else { 
				_FoundElectronMuon = false;
			} // end else {

                        int index = emo_pass ? 4 : -4;
   	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);	   

		} // end for (Collection<TMBEMCluster>::iterator emit = GoodElectrons.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	bool MatchEMTriggers::FindMatchEleJet_v12(std::string trigName,
																						Collection<TMBEMCluster>& Ele,
																						const Collection<TMBL1CalTower>& L1Towers,
																						const Collection<TMBL3Ele>& L3Ele) {
		_FoundElectronJet = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                        bool emo_pass = false;      
			if (trigName == "E1_SHT15_2J20") {
				if (PassSingleL1Tower(11.0, emit, L1Towers)) {
					if (trigName == "E1_SHT15_2J20" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassSingleL1Tower(11.0, emit, L1Towers)) {
			} // end if (trigName == "E1_SHT15_2J20") {
			else if (trigName == "E2_SHT15_2J20") {
				if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
					if (trigName == "E2_SHT15_2J20" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if (trigName == "E2_SHT15_2J20") {
			else if (trigName == "E3_SHT15_2J20") {
				if (PassTwoL1TowersAsym(9.0,3.0, emit, L1Towers)) {
					if (trigName == "E3_SHT15_2J20" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if (PassTwoL1TowersAsym(9.0,3.0,emit, L1Towers)) {
			} // end else if (trigName == "E3_SHT15_2J20") {
			else { 
				_FoundElectronJet = false;
			} // end else {
 
                        int index = emo_pass ? 6 : -6;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = GoodElectrons.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	/*------ END METHODS FOR V12 --------------------------------------------------------------------------------------*/

	//+-------------------------------------------------------------------------------+
	//|                                                                               |
	//|            Methods for Triggerlist v13                                        |
	//|                                                                               |
  //+-------------------------------------------------------------------------------+
	bool MatchEMTriggers::FindMatchSingleEleCalOnly_v13(std::string trigName, 
																											Collection<TMBEMCluster>& Ele,
																											const Collection<TMBL1CalTower>& L1Towers,
																											const Collection<TMBL2EM>& L2EM,
																											const Collection<TMBL3Ele>& L3Ele) {
		_FoundSingleEleCalOnly = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if (trigName == "E1_NC90" || trigName == "E1_VL70" || trigName == "E1_L70" || trigName == "E1_L50" || 
					trigName == "E1_SH30" || trigName == "E1_SHT22" || trigName == "E1_SHT20") {
				if (PassSingleL1Tower(11.0, emit, L1Towers)) {
					if (PassL2EM(15.0, emit, L2EM)) {
						if (trigName == "E1_NC90" && PassL3Ele_NC_v12plus(90.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E1_VL70" && PassL3Ele_VL_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E1_L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E1_L50" && PassL3Ele_L_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E1_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E1_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E1_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassSingleL1Tower(11.0, emit, L1Towers)) {
			} // end if (trigName == "E1_VL70" || trigName == "E1_L50" || trigName == "E1_SH30" || trigName == "E1_SHT20") {
			else if (trigName == "E2_SH30" || trigName == "E2_SHT22" || trigName == "E2_SHT20") {
				if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
					if (PassL2EM(15.0, emit, L2EM)) {
						if (trigName == "E2_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E2_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E2_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if (trigName == "E2_SH30" || trigName == "E2_SHT20") {
			else if (trigName == "E3_SH30" || trigName == "E3_SHT22" || trigName == "E3_SHT20") {
				if (PassTwoL1TowersAsym(9.0,3.0, emit, L1Towers)) {
					if (PassL2EM(15.0, emit, L2EM)) {
						if (trigName == "E3_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E3_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E3_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassTwoL1TowersAsym(9.0,3.0,emit, L1Towers)) {
			} // end else if (trigName == "E3_SH30" || trigName == "E3_SHT20") {
			else if (trigName == "E4_SH30" || trigName == "E4_SHT22" || trigName == "E4_SHT20") {
				if (PassSingleL1Tower(11.0, emit, L1Towers)) {
					if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
						if (trigName == "E4_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E4_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E4_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if (trigName == "E4_SH30" || trigName == "E4_SHT20") {
			else { 
				_FoundSingleEleCalOnly = false;
			} // end else {

                        int index = emo_pass ? 1 : -1;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = GoodElectrons.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	bool MatchEMTriggers::FindMatchSingleEleTrack_v13(std::string trigName, 
																										Collection<TMBEMCluster>& Ele,
																										const Collection<TMBL1CalTower>& L1Towers,
																										const Collection<TMBL1Track>& L1Track,
																										const Collection<TMBL2EM>& L2EM,
																										const Collection<TMBL2Track>& L2Track,
																										const Collection<TMBL3Ele>& L3Ele,
																										const Collection<TMBL3Track>& L3Track) {
		_FoundSingleEleTrack = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if (trigName == "E1_SHT15_TK13" || trigName == "E1_T13L15" || trigName == "E1_T25VL30" ||
					trigName == "E1_T13SH15" || trigName == "E1_T15L20") {
				if (PassSingleL1Tower(11.0, emit, L1Towers)) {
					if (PassL2EM(15.0, emit, L2EM)) {
						if (trigName == "E1_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
								PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E1_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E1_T25VL30" && PassL3Ele_VL_T25_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E1_T13SH15" && PassL3Ele_SH_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E1_T15L20" && PassL3Ele_L_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassSingleL1Tower(11.0, emit, L1Towers)) {
			} // end if (trigName == "E1_SHT15_TK13" || trigName == "E1_T13L15" || trigName == "E1_T25VL30" ||
			else if (trigName == "E2_SHT15_TK13" || trigName == "E2_T13L15" || trigName == "E2_T25VL30" ||
							 trigName == "E2_T13SH15" || trigName == "E2_T15L20") {
				if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
					if (PassL2EM(15.0, emit, L2EM)) {
						if (trigName == "E2_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
								PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E2_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E2_T25VL30" && PassL3Ele_VL_T25_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E2_T13SH15" && PassL3Ele_SH_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E2_T15L20" && PassL3Ele_L_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if (trigName == "E2_SHT15_TK13" || trigName == "E2_T13L15" || trigName == "E2_T25VL30" ||
			else if (trigName == "E3_SHT15_TK13" || trigName == "E3_T13L15" || trigName == "E3_T25VL30" ||
							 trigName == "E3_T13SH15" || trigName == "E3_T15L20") {
				if (PassTwoL1TowersAsym(9.0,3.0, emit, L1Towers)) {
					if (PassL2EM(15.0, emit, L2EM)) {
						if (trigName == "E3_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
								PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E3_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E3_T25VL30" && PassL3Ele_VL_T25_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E3_T13SH15" && PassL3Ele_SH_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E3_T15L20" && PassL3Ele_L_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassTwoL1TowersAsym(9.0,3.0,emit, L1Towers)) {
			} // end else if (trigName == "E3_SHT15_TK13" || trigName == "E3_T13L15" || trigName == "E3_T25VL30" ||
			else if (trigName == "E4_SHT15_TK13" || trigName == "E4_T13L15" || 
							 trigName == "E4_T13SH15" || trigName == "E4_T15L20") {
				if (PassSingleL1Tower(11.0, emit, L1Towers)) {
					if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
						if (trigName == "E4_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
								PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E4_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E4_T13SH15" && PassL3Ele_SH_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E4_T15L20" && PassL3Ele_L_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if (trigName == "E4_SHT15_TK13" || trigName == "E4_T13L15" 
			else if (trigName == "E5_SH30" || trigName == "E5_SHT22" || trigName == "E5_SHT20" || 
							 trigName == "E5_SHT15_TK13" || trigName == "E5_T13L15" || 
							 trigName == "E5_T13SH15" || trigName == "E5_T15L20") {
				if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
					if (PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
						if (trigName == "E5_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E5_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E5_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E5_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
								PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E5_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E5_T13SH15" && PassL3Ele_SH_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E5_T15L20" && PassL3Ele_L_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
				} // end if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
			} // end if (trigName == "E5_SH30" || trigName == "E5_SHT22" || trigName == "E5_SHT20") {
			else if (trigName == "E6_SH30" || trigName == "E6_SHT22" || trigName == "E6_SHT20" ||
							 trigName == "E6_SHT15_TK13" || trigName == "E6_T13L15" || 
							 trigName == "E6_T13SH15" || trigName == "E6_T15L20") {
				if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
					if (PassL2EM_Iso(9.0, 0.15, emit, L2EM)) {
						if (trigName == "E6_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E6_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E6_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E6_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
								PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E6_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E6_T13SH15" && PassL3Ele_SH_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E6_T15L20" && PassL3Ele_L_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(9.0, 0.15, emit, L2EM)) {
				} // end if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
			} // end else if (trigName == "E6_SH30" || trigName == "E6_SHT20") {
			else if (trigName == "E7_SH30" || trigName == "E7_SHT22" || trigName == "E7_SHT20" ||
							 trigName == "E7_SHT15_TK13" || trigName == "E7_T13L15" || 
							 trigName == "E7_T13SH15" || trigName == "E7_T15L20") {
				if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
					if (PassL2EM_Iso(9.0, 0.25, emit, L2EM) && PassL2Track(10.0, "TTK", emit, L2Track) ) {
						if (trigName == "E7_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E7_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E7_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E7_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
								PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E7_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E7_T13SH15" && PassL3Ele_SH_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E7_T15L20" && PassL3Ele_L_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
			} // end else if (trigName == "E7_SH30" || trigName == "E7_SHT20") {
			else if (trigName == "E8_SH30" || trigName == "E8_SHT22" || trigName == "E8_SHT20" ||
							 trigName == "E8_SHT15_TK13" || trigName == "E8_T13L15" || 
							 trigName == "E8_T13SH15" || trigName == "E8_T15L20") {
				if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
					if (PassL2EM(9.0, emit, L2EM) && PassL2EM_Iso(6.0, 0.2, emit, L2EM)) {
						if (trigName == "E8_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E8_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E8_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E8_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
								PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E8_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E8_T13SH15" && PassL3Ele_SH_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E8_T15L20" && PassL3Ele_L_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
			} // end else if (trigName == "E8_SH30" || trigName == "E8_SHT20") {
			else if (trigName == "E9_SH30" || trigName == "E9_SHT22" || trigName == "E9_SHT20" ||
							 trigName == "E9_SHT15_TK13" || trigName == "E9_T13L15" || 
							 trigName == "E9_T13SH15" || trigName == "E9_T15L20") {
				if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
					if (PassL2EM_Iso(6.0, 0.2, emit, L2EM) && PassL2Track(10.0, "TIS", emit, L2Track)) {
						if (trigName == "E9_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E9_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E9_SHT20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E9_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele) &&
								PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E9_T13L15" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E9_T13SH15" && PassL3Ele_SH_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E9_T15L20" && PassL3Ele_L_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
			} // end else if (trigName == "E9_SH30" || trigName == "E9_SHT20") {
			else { 
				_FoundSingleEleTrack = false;
			} // end else {

                        int index = emo_pass ? 2 : -2;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = GoodElectrons.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	bool MatchEMTriggers::FindMatchSingleEleIso_v13(std::string trigName, 
																									Collection<TMBEMCluster>& Ele,
																									const Collection<TMBL1CalTower>& L1Towers,
																									const Collection<TMBL1Track>& L1Track,
																									const Collection<TMBL2EM>& L2EM,
																									const Collection<TMBL2Track>& L2Track,
																									const Collection<TMBL3Ele>& L3Ele,
																									const Collection<TMBL3Track>& L3Track) {
		_FoundSingleEleIso = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if (trigName == "E8_IT7SHT8" || trigName == "E8_SHT8_ITK10" || 
					trigName == "E8_IT10SHT10" || trigName == "E8_SHT10_ITK10") {  
				if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
					if (PassL2EM(9.0, emit, L2EM) && PassL2EM_Iso(6.0, 0.2, emit, L2EM)) {
						if (trigName == "E8_IT7SHT8" && PassL3Ele_SHT_IT7T_v12plus(8.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E8_IT10SHT10" && PassL3Ele_SHT_IT10T_v12plus(10.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E8_SHT8_ITK10" && PassL3Ele_SHT_v12plus(8.0, emit, L3Ele) &&
								PassL3IsoTrack_v12plus(10.0, 8, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E8_SHT10_ITK10" && PassL3Ele_SHT_v12plus(10.0, emit, L3Ele) &&
								PassL3IsoTrack_v12plus(10.0, 8, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
			} // end if (trigName == "E8_IT7SHT8" || trigName == "E8_SHT8_ITK10" || 
			else if (trigName == "E9_IT7SHT8" || trigName == "E9_SHT8_ITK10" || 
							 trigName == "E9_IT10SHT10" || trigName == "E9_SHT10_ITK10") { 
				if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
					if (PassL2EM_Iso(6.0, 0.2, emit, L2EM) && PassL2Track(10.0, "TIS", emit, L2Track)) {
						if (trigName == "E9_IT7SHT8" && PassL3Ele_SHT_IT7T_v12plus(8.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E9_IT10SHT10" && PassL3Ele_SHT_IT10T_v12plus(10.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if (trigName == "E9_SHT8_ITK10" && PassL3Ele_SHT_v12plus(8.0, emit, L3Ele) &&
								PassL3IsoTrack_v12plus(10.0, 8, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if (trigName == "E9_SHT10_ITK10" && PassL3Ele_SHT_v12plus(10.0, emit, L3Ele) &&
								PassL3IsoTrack_v12plus(10.0, 8, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
			} // end else if (trigName == "E9_IT7SHT8" || trigName == "E9_SHT8_ITK10" || 
			else { 
				_FoundSingleEleIso = false;
			} // end else {

                        int index = emo_pass ? 3 : -3;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = GoodElectrons.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	bool MatchEMTriggers::FindMatchEleMuon_v13(std::string trigName, 
																						 Collection<TMBEMCluster>& Ele,
																						 const Collection<TMBL1CalTower>& L1Towers,
																						 const Collection<TMBL2EM>& L2EM,
																						 const Collection<TMBL3Ele>& L3Ele) {
		_FoundElectronMuon = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "MUEM1_LEL12" || trigName == "MUEM1_SHT7" || trigName == "MUEM1_RD5" ||
				 trigName == "MUEM1_LEL12_TRK5" || trigName == "MUEM1_LEL12_MM5" ||
				 trigName == "MUEM1_SH7_TRK5" || trigName == "MUEM1_SH7_MM5") {
				if(PassSingleL1Tower(3.0, emit, L1Towers)) {
					if(PassL2EM(6.0, emit, L2EM)) {
						if((trigName == "MUEM1_LEL12" || trigName == "MUEM1_LEL12_TRK5" || trigName == "MUEM1_LEL12_MM5") &&
							 PassL3Ele_L_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "MUEM1_SHT7" && PassL3Ele_SHT_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "MUEM1_SH7_TRK5" || trigName == "MUEM1_SH7_MM5") && 
							 PassL3Ele_SH_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "MUEM1_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(6.0, emit, L2EM)) {
				} // end if(PassSingleL1Tower(3.0, emit, L1Towers)) {
			} // end if(trigName == "MUEM1_LEL12" || trigName == "MUEM1_SHT7" || trigName == "MUEM1_RD5" ||
			else if(trigName == "MUEM2_LEL12" || trigName == "MUEM2_SHT7" || trigName == "MUEM2_RD5" ||
							trigName == "MUEM2_LEL12_TRK5" || trigName == "MUEM2_LEL12_MM5" ||
							trigName == "MUEM2_SH7_TRK5" || trigName == "MUEM2_SH7_MM5") {
				if(PassSingleL1Tower(6.0, emit, L1Towers)) {
					if((trigName == "MUEM2_LEL12" || trigName == "MUEM2_LEL12_TRK5" || trigName == "MUEM2_LEL12_MM5") &&
						 PassL3Ele_L_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM2_SHT7" && PassL3Ele_SHT_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "MUEM2_SH7_TRK5" || trigName == "MUEM2_SH7_MM5") && 
						 PassL3Ele_SH_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM2_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if(PassSingleL1Tower(6.0, emit, L1Towers)) {
			} // end if(trigName == "MUEM2_LEL12" || trigName == "MUEM2_SHT7" || trigName == "MUEM2_RD5" ||
			else if(trigName == "MUEM3_LEL12" || trigName == "MUEM3_SHT7" || trigName == "MUEM3_RD5" ||
							trigName == "MUEM3_LEL12_TRK5" || trigName == "MUEM3_SH7_TRK3") {
				if(PassL2EM(6.0, emit, L2EM)) {
					if((trigName == "MUEM3_LEL12" || trigName == "MUEM3_LEL12_TRK5") &&
						 PassL3Ele_L_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM3_SHT7" && PassL3Ele_SHT_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM3_SH7_TRK3" && PassL3Ele_SH_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM3_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if(PassL2EM(6.0, emit, L2EM)) {
			} // end if(trigName == "MUEM3_LEL12" || trigName == "MUEM3_SHT7" || trigName == "MUEM3_RD5" ||
			else if(trigName == "MUEM4_LEL12" || trigName == "MUEM4_SHT7" || trigName == "MUEM4_RD5" ||
							trigName == "MUEM4_LEL12_TRK3" || trigName == "MUEM4_SH7_TRK3") {
				if(PassL2EM(6.0, emit, L2EM)) {
					if((trigName == "MUEM4_LEL12" || trigName == "MUEM4_LEL12_TRK3") &&
						 PassL3Ele_L_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM4_SHT7" && PassL3Ele_SHT_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM4_SH7_TRK3" && PassL3Ele_SH_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM4_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(6.0, emit, L2EM)) {
			} // end if(trigName == "MUEM4_LEL12" || trigName == "MUEM4_SHT7" || trigName == "MUEM4_RD5" ||
			else if(trigName == "MUEM5_LEL12" || trigName == "MUEM5_SHT7" || trigName == "MUEM5_RD5") {
				if(PassL2EM(6.0, emit, L2EM)) {
					if(trigName == "MUEM5_LEL12" && PassL3Ele_L_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM5_SHT7" && PassL3Ele_SHT_v12plus(7.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM5_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if(PassL2EM(6.0, emit, L2EM)) {
			} // end else if(trigName == "MUEM5_LEL12" || trigName == "MUEM5_SHT7" || trigName == "MUEM5_RD5"
			else {
				_FoundElectronMuon = false;
			}

                        int index = emo_pass ? 4 : -4;
   	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);	   

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}


	bool MatchEMTriggers::FindMatchEleJet_v13(std::string trigName, 
																						Collection<TMBEMCluster>& Ele,
																						const Collection<TMBL1CalTower>& L1Towers,
																						const Collection<TMBL1Track>& L1Track,
																						const Collection<TMBL2EM>& L2EM,
																						const Collection<TMBL2Track>& L2Track,
																						const Collection<TMBL3Ele>& L3Ele) {
		_FoundElectronJet = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if (trigName == "E1_SHT15_2JHA80" || trigName == "E1_SH15_2JHA90" || trigName == "E1_SHT15_2J_J25" ||
					trigName ==	"E1_T13L15_2JH50" || trigName == "E1_SH15_2JHA100" || trigName == "E1_SHT15_2JHA80V" ||
					trigName == "E1_T13L15_2JH50V" || trigName == "E1_SHT15_2J_J30") {
				if (PassSingleL1Tower(11.0, emit, L1Towers)) {
					if (PassL2EM(15.0, emit, L2EM)) {
						if((trigName == "E1_SHT15_2JHA80" ||  trigName == "E1_SHT15_2J_J25" || 
								trigName == "E1_SHT15_2JHA80V" || trigName == "E1_SHT15_2J_J30") &&
							 PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "E1_SH15_2JHA90" || trigName == "E1_SH15_2JHA100") &&
							 PassL3Ele_SH_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName ==	"E1_T13L15_2JH50" || trigName ==	"E1_T13L15_2JH50V") &&
							 PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassSingleL1Tower(11.0, emit, L1Towers)) {
			} // end if (trigName == "E1_SHT15_2JHA80" || trigName == "E1_SH15_2JHA90" || trigName == "E1_SHT15_2J_J25" ||
			else if (trigName == "E2_SHT15_2JHA80" || trigName == "E2_SH15_2JHA90" || trigName == "E2_SHT15_2J_J25" ||
							 trigName == "E2_T13L15_2JH50" || trigName == "E2_SH15_2JHA100" || trigName == "E2_SHT15_2JHA80V" ||
							 trigName == "E2_T13L15_2JH50V" || trigName == "E2_SHT15_2J_J30") {
				if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
					if (PassL2EM(15.0, emit, L2EM)) {
						if((trigName == "E2_SHT15_2JHA80" ||  trigName == "E2_SHT15_2J_J25" || 
								trigName == "E2_SHT15_2JHA80V" || trigName == "E2_SHT15_2J_J30") &&
							 PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "E2_SH15_2JHA90" || trigName == "E2_SH15_2JHA100") &&
							 PassL3Ele_SH_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName ==	"E2_T13L15_2JH50" || trigName ==	"E2_T13L15_2JH50V") &&
							 PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if (trigName == "E2_SHT15_2JHA80" || trigName == "E2_SH15_2JHA90" || trigName == "E2_SHT15_2J_J25" ||
			else if (trigName == "E3_SHT15_2JHA80" || trigName == "E3_SH15_2JHA90" || trigName == "E3_SHT15_2J_J25" ||
							 trigName == "E3_T13L15_2JH50" || trigName == "E3_SH15_2JHA100" || trigName == "E3_SHT15_2JHA80V" ||
							 trigName == "E3_T13L15_2JH50V" || trigName == "E3_SHT15_2J_J30") {
				if (PassTwoL1TowersAsym(9.0,3.0, emit, L1Towers)) {
					if (PassL2EM(15.0, emit, L2EM)) {
						if((trigName == "E3_SHT15_2JHA80" ||  trigName == "E3_SHT15_2J_J25" || 
								trigName == "E3_SHT15_2JHA80V" || trigName == "E3_SHT15_2J_J30") &&
							 PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "E3_SH15_2JHA90" || trigName == "E3_SH15_2JHA100") &&
							 PassL3Ele_SH_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName ==	"E3_T13L15_2JH50" || trigName ==	"E3_T13L15_2JH50V") &&
							 PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassTwoL1TowersAsym(9.0,3.0,emit, L1Towers)) {
			} // end else if (trigName == "E3_SHT15_2JHA80" || trigName == "E3_SH15_2JHA90" || trigName == "E3_SHT15_2J_J25" ||
			else if (trigName == "E4_SHT15_2JHA80" || trigName == "E4_SH15_2JHA90" || trigName == "E4_SHT15_2J_J25" ||
							 trigName == "E4_T12L12_2JH50" || trigName == "E4_SH15_2JHA100" || trigName == "E4_SHT15_2JHA80V" ||
							 trigName == "E4_T12L12_2JH50V") {
				if (PassSingleL1Tower(11.0, emit, L1Towers)) {
					if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
						if((trigName == "E4_SHT15_2JHA80" ||  trigName == "E4_SHT15_2J_J25" || 
								trigName == "E4_SHT15_2JHA80V") && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "E4_SH15_2JHA90" || trigName == "E4_SH15_2JHA100") &&
							 PassL3Ele_SH_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName ==	"E4_T12L12_2JH50" || trigName ==	"E4_T12L12_2JH50V") &&
							 PassL3Ele_L_T12_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if (trigName == "E4_SHT15_2JHA80" || trigName == "E4_SH15_2JHA90" || trigName == "E4_SHT15_2J_J25" ||
			else if (trigName == "E5_SHT15_2JHA80" || trigName == "E5_SH15_2JHA90" || trigName == "E5_SHT15_2J_J25" ||
							 trigName == "E5_T12L12_2JH50" || trigName == "E5_SH15_2JHA100" || trigName == "E5_SHT15_2JHA80V" ||
							 trigName == "E5_T12L12_2JH50V") {
				if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
					if (PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
						if((trigName == "E5_SHT15_2JHA80" ||  trigName == "E5_SHT15_2J_J25" || 
								trigName == "E5_SHT15_2JHA80V") && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "E5_SH15_2JHA90" || trigName == "E5_SH15_2JHA100") &&
							 PassL3Ele_SH_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName ==	"E5_T12L12_2JH50" || trigName ==	"E5_T12L12_2JH50V") &&
							 PassL3Ele_L_T12_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
				} // end if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
			} // end else if (trigName == "E5_SHT15_2JHA80" || trigName == "E5_SH15_2JHA90" || trigName == "E5_SHT15_2J_J25" ||
			else if (trigName == "E6_SHT15_2JHA80" || trigName == "E6_SH15_2JHA90" || trigName == "E6_SHT15_2J_J25" ||
							 trigName == "E6_T12L12_2JH50" || trigName == "E6_SH15_2JHA100" || trigName == "E6_SHT15_2JHA80V" ||
							 trigName == "E6_T12L12_2JH50V") {
				if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
					if (PassL2EM_Iso(9.0, 0.15, emit, L2EM)) {
						if((trigName == "E6_SHT15_2JHA80" ||  trigName == "E6_SHT15_2J_J25" || 
								trigName == "E6_SHT15_2JHA80V") && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "E6_SH15_2JHA90" || trigName == "E6_SH15_2JHA100") &&
							 PassL3Ele_SH_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName ==	"E6_T12L12_2JH50" || trigName ==	"E6_T12L12_2JH50V") &&
							 PassL3Ele_L_T12_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(9.0, 0.15, emit, L2EM)) {
				} // end if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
			} // end else if (trigName == "E6_SHT15_2JHA80" || trigName == "E6_SH15_2JHA90" || trigName == "E6_SHT15_2J_J25" ||
			else if (trigName == "E7_SHT15_2JHA80" || trigName == "E7_SH15_2JHA90" || trigName == "E7_SHT15_2J_J25" ||
							 trigName == "E7_T12L12_2JH50" || trigName == "E7_SH15_2JHA100" || trigName == "E7_SHT15_2JHA80V" ||
							 trigName == "E7_T12L12_2JH50V") {
				if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
					if (PassL2EM_Iso(9.0, 0.25, emit, L2EM) && PassL2Track(10.0, "TTK", emit, L2Track) ) {
						if((trigName == "E7_SHT15_2JHA80" ||  trigName == "E7_SHT15_2J_J25" || 
								trigName == "E7_SHT15_2JHA80V") && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "E7_SH15_2JHA90" || trigName == "E7_SH15_2JHA100") &&
							 PassL3Ele_SH_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName ==	"E7_T12L12_2JH50" || trigName ==	"E7_T12L12_2JH50V") &&
							 PassL3Ele_L_T12_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM(15.0, emit, L2EM)) {
				} // end if (PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TTK(10.0,emit, L1Track)) {
			} // end else if (trigName == "E7_SHT15_2JHA80" || trigName == "E7_SH15_2JHA90" || trigName == "E7_SHT15_2J_J25" ||
			else if (trigName == "E8_SHT15_2JHA80" || trigName == "E8_SH15_2JHA90" || trigName == "E8_SHT15_2J_J25" ||
							 trigName == "E8_T12L12_2JH50" || trigName == "E8_SH15_2JHA100" || trigName == "E8_SHT15_2JHA80V" ||
							 trigName == "E8_T12L12_2JH50V") {
				if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
					if (PassL2EM(9.0, emit, L2EM) && PassL2EM_Iso(6.0, 0.2, emit, L2EM)) {
						if((trigName == "E8_SHT15_2JHA80" ||  trigName == "E8_SHT15_2J_J25" || 
								trigName == "E8_SHT15_2JHA80V") && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "E8_SH15_2JHA90" || trigName == "E8_SH15_2JHA100") &&
							 PassL3Ele_SH_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName ==	"E8_T12L12_2JH50" || trigName ==	"E8_T12L12_2JH50V") &&
							 PassL3Ele_L_T12_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
			} // end else if (trigName == "E8_SHT15_2JHA80" || trigName == "E8_SH15_2JHA90" || trigName == "E8_SHT15_2J_J25" ||
			else if (trigName == "E9_SHT15_2JHA80" || trigName == "E9_T12L12_2JH50" || 
							 trigName == "E9_SHT15_2JHA80V" || trigName == "E9_T12L12_2JH50V") {
				if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
					if (PassL2EM_Iso(6.0, 0.2, emit, L2EM) && PassL2Track(10.0, "TIS", emit, L2Track)) {
						if((trigName == "E9_SHT15_2JHA80" || trigName == "E9_SHT15_2JHA80V") && 
							 PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName ==	"E9_T12L12_2JH50" || trigName ==	"E9_T12L12_2JH50V") &&
							 PassL3Ele_L_T12_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if (PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if (PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TIS(10.0,emit, L1Track)) {
			} // end 
			else { 
				_FoundElectronJet = false;
			} // end else {

                        int index = emo_pass ? 6 : -6;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = GoodElectrons.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}
	/*------ END METHODS FOR V13 --------------------------------------------------------------------------------------*/

	//+-------------------------------------------------------------------------------+
	//|                                                                               |
	//|            Methods for Triggerlist v14                                        |
	//|                                                                               |
  //+-------------------------------------------------------------------------------+
	bool MatchEMTriggers::FindMatchSingleEleCalOnly_v14(std::string trigName, 
																											Collection<TMBEMCluster>& Ele,
																											const Collection<TMBL1CalTower>& L1Towers,
																											const Collection<TMBL2EM>& L2EM,
																											const Collection<TMBL3Ele>& L3Ele) {
		_FoundSingleEleCalOnly = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_SHT25" || trigName == "E1_SH35" || trigName == "E1_L70" ||
				 trigName == "2CEM12_E15_SHT22" || trigName == "2CEM12_E15_SH30") {
				//cout << " Check Trigger " << trigName << endl;
				if(PassSingleL1Tower(12.0, emit, L1Towers)) {
					//cout << "Passed L1 " << endl;
					if(PassL2EM(15.0, emit, L2EM)) {
						//cout << "Passed L2 " << endl;
						if(trigName == "E1_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "2CEM12_E15_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "2CEM12_E15_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(15.0, emit, L2EM)) {
				} // end if(PassSingleL1Tower(12.0, emit, L1Towers)) {
			} // end if(trigName == "E1_SHT25" || trigName == "E1_SH35" || trigName == "E1_L70") {
			else if(trigName == "E3_SHT25" || trigName == "E3_SH35") {
				if(PassSingleL1Tower(12.0, emit, L1Towers)) {
					if(PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
						if(trigName == "E3_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E3_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleL1Tower(12.0, emit, L1Towers)) {
			} // end trigName == "E3_SHT25" || trigName == "E3_SH35") {
			else if(trigName == "E4_SHT25" || trigName == "E4_SH35" ||
							trigName == "2CEM6_E15_SHT22" || trigName == "2CEM6_E15_SH30") {
				if(PassTwoL1TowersSym(6.0, emit, L1Towers)) {
					if(PassL2EM(15.0, emit, L2EM)) {
						if(trigName == "E4_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E4_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "2CEM6_E15_SHT22" && PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "2CEM6_E15_SH30" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if(PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end trigName == "E4_SHT25" || trigName == "E4_SH35") {
			else {
				_FoundSingleEleCalOnly = false;
			}

                        int index = emo_pass ? 1 : -1;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	bool MatchEMTriggers::FindMatchSingleEleTrack_v14(std::string trigName, 
																										Collection<TMBEMCluster>& Ele,
																										const Collection<TMBL1CalTower>& L1Towers,
																										const Collection<TMBL1Track>& L1Track,
																										const Collection<TMBL2EM>& L2EM,
																										const Collection<TMBL2Track>& L2Track,
																										const Collection<TMBL3Ele>& L3Ele,
																										const Collection<TMBL3Track>& L3Track,
																										const Collection<TMBL3Isolation>& L3Iso) {
		_FoundSingleEleTrack = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_T13SHT15" || trigName == "E1_T15SH20" || trigName == "E1_ISHT15_TK13") {
				if(PassSingleL1Tower(12.0, emit, L1Towers)) {
					if(PassL2EM(15.0, emit, L2EM)) {
						if(trigName == "E1_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(15.0, emit, L2EM)) {
				} // end if(PassSingleL1Tower(12.0, emit, L1Towers)) {
			} // end if(trigName == "E1_T13SHT15" || trigName == "E1_T15SH20" || trigName == "E1_ISHT15_TK13") {
			else if(trigName == "E3_T13SHT15" || trigName == "E3_T15SH20" || trigName == "E3_ISHT15_TK13") {
				if(PassSingleL1Tower(12.0, emit, L1Towers)) {
					if(PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
						if(trigName == "E3_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E3_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E3_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleL1Tower(12.0, emit, L1Towers)) {
			} // end else if(trigName == "E1_T13SHT15" || trigName == "E1_T15SH20" || trigName == "E1_ISHT15_TK13") {
			else if(trigName == "E4_T13SHT15" || trigName == "E4_T15SH20" || trigName == "E4_ISHT15_TK13") {
				if(PassTwoL1TowersSym(6.0, emit, L1Towers)) {
					if(PassL2EM(15.0, emit, L2EM)) {
						if(trigName == "E4_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E4_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E4_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if(PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if(trigName == "E4_T13SHT15" || trigName == "E4_T15SH20" || trigName == "E4_ISHT15_TK13") {
			else if(trigName == "E13_T13SHT15" || trigName == "E13_T15SH20" || trigName == "E13_ISHT15_TK13" ||
							trigName == "E13_SHT25" || trigName == "E13_SH35" || trigName == "E13_ISH30" || trigName == "E13_ISHT22") {
				//cout << "Check triggers using E13_XXX in the v14 list " << endl;
				if(PassTwoL1TowersAsym(9.0, 3.0, emit, L1Towers) && PassL1TTK(10.0, emit, L1Track)) {
					//cout << "E13_XXX passed Level 1" << endl; 
					if(PassL2EM(15.0, emit, L2EM)) {
						//cout << "E13_XXX passed Level 2" << endl; 
						if(trigName == "E13_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E13_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E13_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E13_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E13_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E13_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E13_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleL1Tower(12.0, emit, L1Towers) && PassL1TTK(10.0, emit, L1Track)) {
			} // end else if(trigName == "E13_T13SHT15" || trigName == "E13_T15SH20" || trigName == "E13_ISHT15_TK13" ||
			else if(trigName == "E17_T13SHT15" || trigName == "E17_T15SH20" || trigName == "E17_ISHT15_TK13" ||
							trigName == "E17_SHT25" || trigName == "E17_SH35" || trigName == "E17_ISH30" || trigName == "E17_ISHT22" ||
							trigName == "E17_SHT12_ITK10" || trigName == "E17_IT10SHT10") {
				if(PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TIS(10.0, emit, L1Track)) {
					if(PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
						if(trigName == "E17_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E17_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E17_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E17_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E17_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E17_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E17_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "E17_SHT12_ITK10" && PassL3Ele_SHT_v12plus(12.0, emit, L3Ele) &&
								PassL3IsoTrack_v12plus(10.0, 8, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "E17_IT10SHT10" && PassL3Ele_SHT_IT10T_v12plus(10.0, emit, L3Ele) && 
							 PassL3Track_v12plus(10.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
				} // end if(PassSingleL1Tower(9.0, emit, L1Towers)) {
			} // end else if(trigName == "E17_T13SHT15" || trigName == "E17_T15SH20" || trigName == "E17_ISHT15_TK13" ||
			else if(trigName == "E18_T13SHT15" || trigName == "E18_T15SH20" || trigName == "E18_ISHT15_TK13" ||
							trigName == "E18_SHT25" || trigName == "E18_SH35" || trigName == "E18_ISH30" || trigName == "E18_ISHT22") {
				if(PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TIS(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(9.0, 0.15, emit, L2EM)) {
						if(trigName == "E18_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E18_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E18_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E18_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E18_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E18_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E18_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
				} // end if(PassSingleL1Tower(9.0, emit, L1Towers)) {
			} // end else if(trigName == "E18_T13SHT15" || trigName == "E18_T15SH20" || trigName == "E18_ISHT15_TK13" ||
			else if(trigName == "E19_T13SHT15" || trigName == "E19_T15SH20" || trigName == "E19_ISHT15_TK13" ||
							trigName == "E19_SHT25" || trigName == "E19_SH35" || trigName == "E19_ISH30" || trigName == "E19_ISHT22") {
				if(PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TIS(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(9.0, 0.25, emit, L2EM) && PassL2Track(10.0, "TTK", emit, L2Track)) {
						if(trigName == "E19_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E19_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E19_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E19_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E19_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E19_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E19_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
				} // end if(PassSingleL1Tower(9.0, emit, L1Towers)) {
			} // end else if(trigName == "E19_T13SHT15" || trigName == "E19_T15SH20" || trigName == "E19_ISHT15_TK13" ||
			else if(trigName == "E20_T13SHT15" || trigName == "E20_T15SH20" || trigName == "E20_ISHT15_TK13" ||
							trigName == "E20_SHT25" || trigName == "E20_SH35" || trigName == "E20_ISH30" || trigName == "E20_ISHT22" ||
							trigName == "E20_SHT12_ITK10" || trigName == "E20_IT10SHT10") {
				if(PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TES(10.0, emit, L1Track)) {
					if(PassL2EM(9.0, emit, L2EM) && PassL2EM_Iso(6.0, 0.2, emit, L2EM)) {
						if(trigName == "E20_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E20_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E20_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E20_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E20_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E20_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E20_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "E20_SHT12_ITK10" && PassL3Ele_SHT_v12plus(12.0, emit, L3Ele) &&
								PassL3IsoTrack_v12plus(10.0, 8, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "E20_IT10SHT10" && PassL3Ele_SHT_IT10T_v12plus(10.0, emit, L3Ele) && 
							 PassL3Track_v12plus(10.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
				} // end if(PassSingleL1Tower(9.0, emit, L1Towers)) {
			} // end else if(trigName == "E20_T13SHT15" || trigName == "E20_T15SH20" || trigName == "E20_ISHT15_TK13" ||
			else if(trigName == "E21_T13SHT15" || trigName == "E21_T15SH20" || trigName == "E21_ISHT15_TK13" ||
							trigName == "E21_SHT25" || trigName == "E21_SH35" || trigName == "E21_ISH30" || trigName == "E21_ISHT22" ||
							trigName == "E21_SHT12_ITK10" || trigName == "E21_IT10SHT10") {
				if(PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TES(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(6.0, 0.2, emit, L2EM) && PassL2Track(10.0, "TIS", emit, L2Track)) {
						if(trigName == "E21_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E21_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E21_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E21_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E21_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E21_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E21_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "E21_SHT12_ITK10" && PassL3Ele_SHT_v12plus(12.0, emit, L3Ele) &&
								PassL3IsoTrack_v12plus(10.0, 8, 1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "E21_IT10SHT10" && PassL3Ele_SHT_IT10T_v12plus(10.0, emit, L3Ele) && 
							 PassL3Track_v12plus(10.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
				} // end if(PassSingleL1Tower(9.0, emit, L1Towers)) {
			} // end else if(trigName == "E21_T13SHT15" || trigName == "E21_T15SH20" || trigName == "E21_ISHT15_TK13" ||
			else {
				_FoundSingleEleTrack = false;
			}

                        int index = emo_pass ? 2 : -2;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
		
                if (pass) return true;
		return false;
	}


	bool MatchEMTriggers::FindMatchSingleEleIso_v14(std::string trigName, const int trigVersion, 
																									Collection<TMBEMCluster>& Ele,
																									const Collection<TMBL1CalTower>& L1Towers,
																									const Collection<TMBL2EM>& L2EM,
																									const Collection<TMBL3Isolation>& L3Iso) {
		_FoundSingleEleIso = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_ISHT22" || trigName == "E1_ISH30") {
				//cout << "Trigger under study " << trigName << endl;
				if(PassSingleL1Tower(12.0, emit, L1Towers)) {
					//cout << "--> Passed L1 "<< endl;
					if(PassL2EM(15.0, emit, L2EM)) {
						//cout << "--> Passed L2 "<< endl;
						if(trigName == "E1_ISHT22" && (trigVersion < 1451 || PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso))) {emo_pass = true; pass = true;}
						if(trigName == "E1_ISH30" && (trigVersion < 1451 || PassL3Ele_ISH_v12plus(30.0, emit, L3Iso))) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(15.0, emit, L2EM)) {
				} // end if(PassSingleL1Tower(12.0, emit, L1Towers)) {
			} // end if(trigName == "E1_ISHT22" || trigName == "E1_ISH30") {
			else if(trigName == "E3_ISHT22" || trigName == "E3_ISH30") {
				if(PassSingleL1Tower(12.0, emit, L1Towers)) {
					if(PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
						if(trigName == "E3_ISHT22" && (trigVersion < 1451 || PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso))) {emo_pass = true; pass = true;}
						if(trigName == "E3_ISH30" && (trigVersion < 1451 || PassL3Ele_ISH_v12plus(30.0, emit, L3Iso))) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleL1Tower(12.0, emit, L1Towers)) {
			} // end trigName == "E3_SHT25" || trigName == "E3_SH35") {
			else if(trigName == "E4_ISHT22" || trigName == "E4_ISH30") {
				if(PassTwoL1TowersSym(6.0, emit, L1Towers)) {
					if(PassL2EM(15.0, emit, L2EM)) {
						if(trigName == "E4_ISHT22" && (trigVersion < 1451 || PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso))) {emo_pass = true; pass = true;}
							 if(trigName == "E4_ISH30" && (trigVersion < 1451 || PassL3Ele_ISH_v12plus(30.0, emit, L3Iso))) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(11.0, 0.2, emit, L2EM)) {
				} // end if(PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end trigName == "E4_ISHT22" || trigName == "E4_ISH30") {
			else {
				_FoundSingleEleIso = false;
			}

                        int index = emo_pass ? 3 : -3;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}


	bool MatchEMTriggers::FindMatchEleMuon_v14(std::string trigName, const int trigVersion, 
																						 Collection<TMBEMCluster>& Ele,
																						 const Collection<TMBL1CalTower>& L1Towers,
																						 const Collection<TMBL2EM>& L2EM,
																						 const Collection<TMBL3Ele>& L3Ele,
																						 const Collection<TMBL3Isolation>& L3Iso) {
		_FoundElectronMuon = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "MUEM1_LEL15_TRK5" || trigName == "MUEM1_LEL15_MM5" ||
				 trigName == "MUEM1_SH12_TRK5" || trigName == "MUEM1_SH12_MM5" ||
				 trigName == "MUEM1_ISH7_TRK5" || trigName == "MUEM1_ISH7_MM5" || trigName == "MUEM1_RD5") {
				if(PassSingleL1Tower(3.0, emit, L1Towers)) {
					if(PassL2EM(6.0, emit, L2EM)) {
						if((trigName == "MUEM1_LEL15_TRK5" || trigName == "MUEM1_LEL15_MM5") &&
							 PassL3Ele_L_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "MUEM1_SH12_TRK5" || trigName == "MUEM1_SH12_MM5") && 
							 PassL3Ele_SH_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "MUEM1_ISH7_TRK5" || trigName == "MUEM1_ISH7_MM5") && 
							 (trigVersion < 1451 || PassL3Ele_ISH_v12plus(7.0, emit, L3Iso))) {emo_pass = true; pass = true;}
						if(trigName == "MUEM1_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(6.0, emit, L2EM)) {
				} // end if(PassSingleL1Tower(3.0, emit, L1Towers)) {
			} // end if(trigName == "MUEM1_LEL15_TRK5" || trigName == "MUEM1_LEL15_MM5" ||
			else if(trigName == "MUEM2_LEL15_TRK5" || trigName == "MUEM2_LEL15_MM5" ||
							trigName == "MUEM2_SH12_TRK5" || trigName == "MUEM2_SH12_MM5" ||
							trigName == "MUEM2_ISH7_TRK5" || trigName == "MUEM2_ISH7_MM5" || trigName == "MUEM2_RD5") {
				if(PassSingleL1Tower(6.0, emit, L1Towers)) {
					if((trigName == "MUEM2_LEL15_TRK5" || trigName == "MUEM2_LEL15_MM5") &&
						 PassL3Ele_L_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "MUEM2_SH12_TRK5" || trigName == "MUEM2_SH12_MM5") && 
						 PassL3Ele_SH_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "MUEM2_ISH7_TRK5" || trigName == "MUEM2_ISH7_MM5") && 
						 (trigVersion < 1451 || PassL3Ele_ISH_v12plus(7.0, emit, L3Iso))) {emo_pass = true; pass = true;}
					if(trigName == "MUEM2_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if(PassSingleL1Tower(6.0, emit, L1Towers)) {
			} // end else if(trigName == "MUEM2_LEL15_TRK5" || trigName == "MUEM2_LEL15_MM5" ||
			else if(trigName == "MUEM3_LEL15_TRK5" || trigName == "MUEM3_SH12_TRK5" ||
							trigName == "MUEM3_ISH7_TRK5" || trigName == "MUEM3_RD5") {
				if(trigVersion < 1450 || PassSingleL1Tower(3.0, emit, L1Towers)) {
					if(PassL2EM(6.0, emit, L2EM)) {
						if(trigName == "MUEM3_LEL15_TRK5" && PassL3Ele_L_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "MUEM3_SH12_TRK5" && PassL3Ele_SH_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "MUEM3_ISH7_TRK5" && 
							 (trigVersion < 1451 || PassL3Ele_ISH_v12plus(7.0, emit, L3Iso))) {emo_pass = true; pass = true;}
						if(trigName == "MUEM3_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(6.0, emit, L2EM)) {
				} // end if(trigVersion < 1450 || PassSingleL1Tower(3.0, emit, L1Towers)) {
			} // end else if(trigName == "MUEM3_LEL15_TRK5" || trigName == "MUEM3_SH12_TRK5" ||
			else if(trigName == "MUEM4_LEL15_TRK5" || trigName == "MUEM4_SH12_TRK5" ||
							trigName == "MUEM4_ISH7_TRK5" || trigName == "MUEM4_RD5") {
				if(PassSingleL1Tower(3.0, emit, L1Towers)) {
					if(PassL2EM(6.0, emit, L2EM)) {
						if(trigName == "MUEM4_LEL15_TRK5" && PassL3Ele_L_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "MUEM4_SH12_TRK5" && PassL3Ele_SH_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "MUEM4_ISH7_TRK5" && 
							 (trigVersion < 1451 || PassL3Ele_ISH_v12plus(7.0, emit, L3Iso))) {emo_pass = true; pass = true;}
						if(trigName == "MUEM4_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(6.0, emit, L2EM)) {
				} // end if(PassSingleL1Tower(3.0, emit, L1Towers)) {
			} // end else if(trigName == "MUEM4_LEL15_TRK5" || trigName == "MUEM4_SH12_TRK5" ||
			else if(trigName == "MUEM5_LEL15" || trigName == "MUEM5_SH12" || trigName == "MUEM5_RD5") {
				if(PassL2EM(6.0, emit, L2EM)) {
					if(trigName == "MUEM5_LEL15" && PassL3Ele_L_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM5_SH12" && PassL3Ele_SH_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if(trigName == "MUEM5_ISH7" && 
						 (trigVersion < 1451 || PassL3Ele_ISH_v12plus(7.0, emit, L3Iso))) {emo_pass = true; pass = true;}
					if(trigName == "MUEM5_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(6.0, emit, L2EM)) {
			} // end else if(trigName == "MUEM5_LEL15" || trigName == "MUEM5_SH12" || trigName == "MUEM5_RD5"
			else {
				_FoundElectronMuon = false;	
			}

                        int index = emo_pass ? 4 : -4;
   	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);	   

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	bool MatchEMTriggers::FindMatchEleJet_v14(std::string trigName, 
																						Collection<TMBEMCluster>& Ele,
																						const Collection<TMBL1CalTower>& L1Towers,
																						const Collection<TMBL1Track>& L1Track,
																						const Collection<TMBL2EM>& L2EM,
																						const Collection<TMBL2Track>& L2Track,
																						const Collection<TMBL3Ele>& L3Ele) {
		_FoundElectronJet = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_SHT15_2J_J25" || trigName == "E1_SHT15_JHA80" || trigName == "E1_T13L15_2JH50V") {
				if(PassSingleL1Tower(12.0, emit, L1Towers)) {
					if(PassL2EM(15.0, emit, L2EM)) {
						if((trigName == "E1_SHT15_2J_J25" || trigName == "E1_SHT15_JHA80") && 
							 PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_T13L15_2JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(15.0, emit, L2EM)) {
				} // end if(PassSingleL1Tower(12.0, emit, L1Towers)) {
			} // end if(trigName == "E1_SHT15_2J_J25" || trigName == "E1_SHT15_JHA80" || trigName == "E1_T13L15_2JH50V") {
			else if(trigName == "E3_T12L12_2JH50V" || trigName == "E3_SHT15_JHA80V") {
				if(PassSingleL1Tower(12.0, emit, L1Towers)) {
					if(PassL2EM_Iso(11.0, 0.2 ,emit, L2EM)) {
						if(trigName == "E3_SHT15_JHA80V" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E3_T12L12_2JH50V" && PassL3Ele_L_T12_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(11.0, 0.2 ,emit, L2EM)) {
				} // end if(PassSingleL1Tower(12.0, emit, L1Towers)) {
			} // end else if(trigName == "E3_T12L12_2JH50V" || trigName == "E3_SHT15_JHA80V") {
			else if(trigName == "E4_SHT15_2J_J25" || trigName == "E4_SHT15_JHA80" || trigName == "E4_T13L15_2JH50V") {
				if(PassTwoL1TowersSym(6.0, emit, L1Towers)) {
					if(PassL2EM(15.0, emit, L2EM)) {
						if((trigName == "E4_SHT15_2J_J25" || trigName == "E4_SHT15_JHA80") && 
							 PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E4_T13L15_2JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(15.0, emit, L2EM)) {
				} // end if(PassTwoL1TowersSym(6.0, emit, L1Towers)) {
			} // end else if(trigName == "E4_SHT15_2J_J25" || trigName == "E4_SHT15_JHA80" || trigName == "E4_T13L15_2JH50V") {
			else if(trigName == "E13_SHT15_2J_J25" || trigName == "E13_SHT15_JHA80" || trigName == "E13_T13L152JH50V") {
				if(PassTwoL1TowersAsym(9.0, 3.0, emit, L1Towers) && PassL1TTK(10.0, emit, L1Track)) {
					if(PassL2EM(15.0, emit, L2EM)) {
						if((trigName == "E13_SHT15_2J_J25" || trigName == "E13_SHT15_JHA80") && 
							 PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E13_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(15.0, emit, L2EM)) {	
				} // end if(PassTwoL1TowersAsym(9.0, 3.0, emit, L1Towers) && PassL1TTK(10.0, emit, L1Track)) {
			} // end else if(trigName == "E13_SHT15_2J_J25" || trigName == "E13_SHT15_JHA80" || trigName == "E13_T13L15_2JH50V") {
			else if(trigName == "E17_SHT15_JHA80V" || trigName == "E17_T12L122JH50V") {
				if(PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TIS(10.0, emit, L1Track)) {
					if(PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
						if(trigName == "E17_SHT15_JHA80V" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E17_T12L122JH50V" && PassL3Ele_L_T12_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(11.0, emit, L2EM) && PassL2EM_Iso(9.0, 0.25, emit, L2EM)) {
				} // end if(PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TIS(10.0, emit, L1Track)) {
			} // end else if(trigName == "E17_SHT15_JHA80V" || trigName == "E17_T12L122JH50V") {
			else if(trigName == "E18_SHT15_JHA80V" || trigName == "E18_T12L122JH50V") {
				if(PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TIS(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(9.0, 0.15, emit, L2EM)) {
						if(trigName == "E18_SHT15_JHA80V" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E18_T12L122JH50V" && PassL3Ele_L_T12_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(9.0, 0.15, emit, L2EM)) {
				} // end if(PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TIS(10.0, emit, L1Track)) {
			} // end else if(trigName == "E18_SHT15_JHA80V" || trigName == "E18_T12L122JH50V") {
			else if(trigName == "E19_SHT15_JHA80V" || trigName == "E19_T12L122JH50V") {
				if(PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TIS(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(9.0, 0.25, emit, L2EM) && PassL2Track(10.0,"TTK", emit, L2Track)) {
						if(trigName == "E19_SHT15_JHA80V" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E19_T12L122JH50V" && PassL3Ele_L_T12_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(9.0, 0.25, emit, L2EM) && PassL2Track(10.0,"TTT", emit, L2Track)) {
				} // end if(PassSingleL1Tower(9.0, emit, L1Towers) && PassL1TIS(10.0, emit, L1Track)) {
			} // end else if(trigName == "E19_SHT15_JHA80V" || trigName == "E19_T12L122JH50V") {
			else if(trigName == "E20_SHT15_JHA80V" || trigName == "E20_T12L122JH50V") {
				if(PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TES(10.0, emit, L1Track)) {
					if(PassL2EM(9.0, emit, L2EM) && PassL2EM_Iso(6.0, 0.2, emit, L2EM)) {
						if(trigName == "E20_SHT15_JHA80V" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E20_T12L122JH50V" && PassL3Ele_L_T12_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(9.0, emit, L2EM) && PassL2EM_Iso(6.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TES(10.0, emit, L1Track)) {
			} // end else if(trigName == "E20_SHT15_JHA80V" || trigName == "E20_T12L122JH50V") {
			else if(trigName == "E21_SHT15_JHA80V" || trigName == "E21_T12L122JH50V") {
				if(PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TES(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(6.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TIS", emit, L2Track)) {
						if(trigName == "E21_SHT15_JHA80V" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E21_T12L122JH50V" && PassL3Ele_L_T12_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(9.0, emit, L2EM) && PassL2EM_Iso(6.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleL1Tower(6.0, emit, L1Towers) && PassL1TES(10.0, emit, L1Track)) {
			} // end else if(trigName == "E21_SHT15_JHA80V" || trigName == "E21_T12L122JH50V") {
			else {
				_FoundElectronJet = false;
			}

                        int index = emo_pass ? 6 : -6;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}
	/*--- END v14 ---------------------------------------------------------------------------------------------------*/

	//+-------------------------------------------------------------------------------+
	//|                                                                               |
	//|            Methods for Triggerlist v15                                        |
	//|                                                                               |
  //+-------------------------------------------------------------------------------+
	bool MatchEMTriggers::FindMatchSingleEleCalOnly_v15(std::string trigName, 
																											Collection<TMBEMCluster>& Ele,
																											const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																											const Collection<TMBL2EM>& L2EM,
																											const Collection<TMBL3Ele>& L3Ele) {
		_FoundSingleEleCalOnly = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_SHT25" || trigName == "E1_SH35" || trigName == "E1_L70" || 
				 trigName == "E1_SHT50" || trigName == "E1_SH60" || trigName == "E1_LH2SH27" ||
				 trigName == "E1_LH2L70" || trigName == "E1_L80") {
				//cout << " Check Trigger " << trigName << endl;
				if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
					//cout << "Passed L1 " << endl;
					if(PassL2EM(22.0, emit, L2EM) || PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
						//cout << "Passed L2 " << endl;
						if(trigName == "E1_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "E1_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(22.0, emit, L2EM) && PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(19.0, emit, L1Towers)) {
			} // end if(trigName == "E1_SHT25" || trigName == "E1_SH35" || trigName == "E1_L70") {
			else if(trigName == "E2_SHT25" || trigName == "E2_SH35" || trigName == "E2_L70" ||
							trigName == "E2_SHT50" || trigName == "E2_SH60" || trigName == "E2_LH2SH27" ||
							trigName == "E2_LH2L70" || trigName == "E2_L80") {
				//cout << " Check Trigger " << trigName << endl;
				if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
					//cout << "Passed L1 " << endl;
					if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
						//cout << "Passed L2 " << endl;
						if(trigName == "E2_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "E2_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEMisoL1(16.0, emit, L1Towers)) {
			} // end else if(trigName == "E2_SHT25" || trigName == "E2_SH35" || trigName == "E2_L70") {
			else {
				_FoundSingleEleCalOnly = false;
			}

                        int index = emo_pass ? 1 : -1;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	bool MatchEMTriggers::FindMatchSingleEleTrack_v15(std::string trigName, 
																										Collection<TMBEMCluster>& Ele,
																										const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																										const Collection<TMBL1Track>& L1Track,
																										const Collection<TMBL2EM>& L2EM,
																										const Collection<TMBL2Track>& L2Track,
																										const Collection<TMBL3Ele>& L3Ele,
																										const Collection<TMBL3Track>& L3Track,
																										const Collection<TMBL3Isolation>& L3Iso) {
		_FoundSingleEleTrack = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_T13SHT15" || trigName == "E1_T15SH20" || trigName == "E1_ISHT15_TK13" ||
				trigName == "E1_LH2ISHT17T14" || trigName == "E1_T14LH2SH17") {
				if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
					if(PassL2EM(22.0, emit, L2EM) || PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
						if(trigName == "E1_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "E1_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "E1_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(19.0, emit, L2EM) && PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "E1_T13SHT15" || trigName == "E1_T15SH20" || trigName == "E1_ISHT15_TK13") {
			else if(trigName == "E2_T13SHT15" || trigName == "E2_T15SH20" || trigName == "E2_ISHT15_TK13" ||
				trigName == "E2_LH2ISHT17T14" || trigName == "E2_T14LH2SH17") {
				if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
						if(trigName == "E2_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "E2_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "E2_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
			} // end else if(trigName == "E2_T13SHT15" || trigName == "E2_T15SH20" || trigName == "E2_ISHT15_TK13") {
			else if(trigName == "TE1_SHT25" || trigName == "TE1_SH35" || trigName == "TE1_L70" ||
							trigName == "TE1_ISHT22" || trigName == "TE1_ISH30" ||
							trigName == "TE1_T13SHT15" || trigName == "TE1_T15SH20" || trigName == "TE1_ISHT15_TK13" ||
							trigName == "TE1_SHT50" || trigName == "TE1_SH60" || trigName == "TE1_LH2SH27" ||
							trigName == "TE1_LH2L70" || trigName == "TE1_L80" ||
							trigName == "TE1_LH2ISHT17T14" || trigName == "TE1_T14LH2SH17" || trigName == "TE1_LH2ISH24") {
				if(PassSingleEML1(16.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
					if(PassL2EM(16.0, emit, L2EM) && PassL2Track(13.0,"TTK", emit, L2Track)) {
						if(trigName == "TE1_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(16.0, emit, L2EM) && PassL2Track(13.0,"TTK", emit, L2Track)) {
				} // end if(PassSingleEML1(16.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE1_SHT25" || trigName == "TE1_SH35" || trigName == "TE1_L70" ||
			else if(trigName == "TE2_SHT25" || trigName == "TE2_SH35" || trigName == "TE2_L70" ||
							trigName == "TE2_ISHT22" || trigName == "TE2_ISH30" ||
							trigName == "TE2_T13SHT15" || trigName == "TE2_T15SH20" || trigName == "TE2_ISHT15_TK13" ||
							trigName == "TE2_SHT50" || trigName == "TE2_SH60" || trigName == "TE2_LH2SH27" ||
							trigName == "TE2_LH2L70" || trigName == "TE2_L80" ||
							trigName == "TE2_LH2ISHT17T14" || trigName == "TE2_T14LH2SH17" || trigName == "TE2_LH2ISH24") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TTK", emit, L2Track)) {
						if(trigName == "TE2_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TTK", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE2_SHT25" || trigName == "TE2_SH35" || trigName == "TE2_L70" ||
			else if(trigName == "TE3_SHT25" || trigName == "TE3_SH35" || trigName == "TE3_L70" ||
							trigName == "TE3_ISHT22" || trigName == "TE3_ISH30" ||
							trigName == "TE3_T13SHT15" || trigName == "TE3_T15SH20" || trigName == "TE3_ISHT15_TK13" ||
							trigName == "TE3_SHT50" || trigName == "TE3_SH60" || trigName == "TE3_LH2SH27" ||
							trigName == "TE3_LH2L70" || trigName == "TE3_L80" ||
							trigName == "TE3_LH2ISHT17T14" || trigName == "TE3_T14LH2SH17" || trigName == "TE3_LH2ISH24") {
				if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
					if(PassL2EM(13.0, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
						if(trigName == "TE3_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(13.0, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE3_SHT25" || trigName == "TE3_SH35" || trigName == "TE3_L70" ||
			else if(trigName == "TE4_SHT25" || trigName == "TE4_SH35" || trigName == "TE4_L70" ||
							trigName == "TE4_ISHT22" || trigName == "TE4_ISH30" ||
							trigName == "TE4_T13SHT15" || trigName == "TE4_T15SH20" || trigName == "TE4_ISHT15_TK13" |
							trigName == "TE4_SHT50" || trigName == "TE4_SH60" || trigName == "TE4_LH2SH27" ||
							trigName == "TE4_LH2L70" || trigName == "TE4_L80" ||
							trigName == "TE4_LH2ISHT17T14" || trigName == "TE4_T14LH2SH17" || trigName == "TE4_LH2ISH24") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TIS(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TIS", emit, L2Track)) {
						if(trigName == "TE4_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TIS", emit, L2Track)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TIS(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE4_SHT25" || trigName == "TE4_SH35" || trigName == "TE4_L70" ||
			else if(trigName == "TE5_SHT25" || trigName == "TE5_SH35" || trigName == "TE5_L70" ||
							trigName == "TE5_ISHT22" || trigName == "TE5_ISH30" ||
							trigName == "TE5_T13SHT15" || trigName == "TE5_T15SH20" || trigName == "TE5_ISHT15_TK13" ||
							trigName == "TE5_SHT50" || trigName == "TE5_SH60" || trigName == "TE5_LH2SH27" ||
							trigName == "TE5_LH2L70" || trigName == "TE5_L80" ||
							trigName == "TE5_LH2ISHT17T14" || trigName == "TE5_T14LH2SH17" || trigName == "TE5_LH2ISH24") {
				if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
					if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(8.0,"TES", emit, L2Track)) {
						if(trigName == "TE5_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_SH35" && PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(8.0,"TES", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
			} // end else if(trigName == "TE5_SHT25" || trigName == "TE5_SH35" || trigName == "TE5_L70" ||
			else {
				_FoundSingleEleTrack = false;
			}

                        int index = emo_pass ? 2 : -2;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
		
                if (pass) return true;
		return false;
	}



	
	bool MatchEMTriggers::FindMatchSingleEleIso_v15(std::string trigName, 
																									Collection<TMBEMCluster>& Ele,
																									const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																									const Collection<TMBL2EM>& L2EM,
																									const Collection<TMBL3Ele>& L3Ele,
																									const Collection<TMBL3Isolation>& L3Iso) {
		_FoundSingleEleIso = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_ISHT22" || trigName == "E1_ISH30" || trigName == "E1_LH2ISH24") {
				//cout << "Trigger under study " << trigName << endl;
				if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
					//cout << "--> Passed L1 "<< endl;
					if(PassL2EM(22.0, emit, L2EM) || PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
						//cout << "--> Passed L2 "<< endl;
						if(trigName == "E1_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E1_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E1_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(22.0, emit, L2EM) && PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "E1_ISHT22" || trigName == "E1_ISH30") {
			else if(trigName == "E2_ISHT22" || trigName == "E2_ISH30" || trigName == "E2_LH2ISH24") {
				if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
						if(trigName == "E2_ISHT22" && PassL3Ele_ISHT_v12plus(22.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E2_ISH30" && PassL3Ele_ISH_v12plus(30.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "E2_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
			} // end trigName == "E2_SHT25" || trigName == "E2_SH35") {
			else {
				_FoundSingleEleIso = false;
			}

                        int index = emo_pass ? 3 : -3;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	bool MatchEMTriggers::FindMatchEleJet_v15(std::string trigName, 
																						Collection<TMBEMCluster>& Ele,
																						const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																						const Collection<TMBL1Track>& L1Track,
																						const Collection<TMBL2EM>& L2EM,
																						const Collection<TMBL2Track>& L2Track,
																						const Collection<TMBL3Ele>& L3Ele,
																						const Collection<TMBL3Track>& L3Track,
																						const Collection<TMBL3Isolation>& L3Iso) {
		_FoundElectronJet = true;
	        bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_SHT15_2J_J25" || trigName == "E1_SHT15_JHA80" || trigName == "E1_T13L152JH50V") {
				if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
//					if(PassL2EM(19.0, emit, L2EM) || PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
					if(PassL2EM(22.0, emit, L2EM) || PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
						if(trigName == "E1_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(19.0, emit, L2EM) && PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "E1_SHT15_2J_J25") {
			else if(trigName == "E2_SHT15_2J_J25" || trigName == "E2_SHT15_JHA80" || trigName == "E2_T13L152JH50V") {
				if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
						if(trigName == "E2_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
			} // end else if(trigName == "E2_SHT15_2J_J25") {
			else if(trigName == "TE1_SHT15_2J_J25" || trigName == "TE1_SHT15_JHA80" || trigName == "TE1_T13L152JH50V") {
				if(PassSingleEML1(16.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
					if(PassL2EM(16.0, emit, L2EM) && PassL2Track(13.0,"TTK", emit, L2Track)) {
//						if(trigName == "TE1_TE1SHT15" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(16.0, emit, L2EM) && PassL2Track(13.0,"TTK", emit, L2Track)) {
				} // end if(PassSingleEML1(16.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE1_SHT15_2J_J25") {
			else if(trigName == "TE2_SHT15_2J_J25" || trigName == "TE2_SHT15_JHA80" || trigName == "TE2_T13L152JH50V") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TTK", emit, L2Track)) {
						if(trigName == "TE2_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TTK", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE2_SHT15_2J_J25") {
			else if(trigName == "TE3_SHT15_2J_J25" || trigName == "TE3_SHT15_JHA80" || trigName == "TE3_T13L152JH50V") {
				if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
					if(PassL2EM(13.0, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
						if(trigName == "TE3_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(13.0, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE3_SHT15_2J_J25") {
			else if(trigName == "TE4_SHT15_2J_J25" || trigName == "TE4_SHT15_JHA80" || trigName == "TE4_T13L152JH50V") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TIS(10.0, emit, L1Track)) {
//					if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TIS", emit, L2Track)) {
					if(PassL2EM(13.0, emit, L2EM) && PassL2Track(10.0,"TIS", emit, L2Track)) {
						if(trigName == "TE4_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TIS", emit, L2Track)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TIS(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE4_SHT15_2J_J25") {
			else if(trigName == "TE5_SHT15_2J_J25" || trigName == "TE5_SHT15_JHA80" || trigName == "TE5_T13L152JH50V") {
				if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
					if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(8.0,"TES", emit, L2Track)) {
						if(trigName == "TE5_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(8.0,"TES", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
			} // end else if(trigName == "TE5_SHT15_2J_J25") {
			else if(trigName == "EJT_ISHT15_TK13" || trigName == "EJT_T13SHT15" || trigName == "EJT_T15SH20" ||
							trigName == "EJT_SHT15_2J_J25" || trigName == "EJT_SHT15_JHA80" || trigName == "EJT_13L152JH50V" ||
							trigName == "EJT_ISHT15_M25" || trigName == "EJT_SH30_M15" || trigName == "EJT_SHT20_M20") {
				if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
						if(trigName == "EJT_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_ISHT15_M25" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_SH30_M15" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_SHT20_M20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(8.0,"TES", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
			} // end else if(trigName == "EJT_SHT15_2J_J25") {
			else if(trigName == "ET1_SHT15_2J_J25" || trigName == "ET1_SHT15_JHA80" || trigName == "ET1_T13L152JH50V") {
				if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
						if(trigName == "ET1_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET1_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET1_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
			} // end else if(trigName == "ET1_SHT15_2J_J25") {
			else if(trigName == "ET2_SHT15_2J_J25" || trigName == "ET2_SHT15_JHA80" || trigName == "ET2_T13L152JH50V") {
				if(PassSingleEMisoL1(7.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
					if(PassL2EM_Iso(7.0, 0.2, emit, L2EM) && PassL2Track(6.7,"TES", emit, L2Track)) {
						if(trigName == "ET2_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET2_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET2_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(7.0, 0.2, emit, L2EM) && PassL2Track(6.7,"TES", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(7.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
			} // end else if(trigName == "ET2_SHT15_2J_J25") {
			else if(trigName == "ET3_SHT15_2J_J25" || trigName == "ET3_SHT15_JHA80" || trigName == "ET3_T13L152JH50V") {
				if(PassSingleEMisoL1(7.0, emit, L1Cal2bEMs) && PassL1TEL(5.0, emit, L1Track)) {
					if(PassL2EM_Iso(7.0, 0.2, emit, L2EM) && PassL2Track(6.7,"TEL", emit, L2Track)) {
						if(trigName == "ET3_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET3_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET3_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(7.0, 0.2, emit, L2EM) && PassL2Track(6.7,"TES", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(7.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
			} // end else if(trigName == "ET3_SHT15_2J_J25") {
			else {
				_FoundElectronJet = false;
			}

                        int index = emo_pass ? 6 : -6;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}


	bool MatchEMTriggers::FindMatchEleMuon_v15(std::string trigName, 
																						 Collection<TMBEMCluster>& Ele,
																						 const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																						 const Collection<TMBL2EM>& L2EM,
																						 const Collection<TMBL3Ele>& L3Ele,
																						 const Collection<TMBL3Isolation>& L3Iso) {
		_FoundElectronMuon = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "ME1_LEL15_TRK5" || trigName == "ME1_LEL15_MM5" || 
				 trigName == "ME1_SH12_TRK5" || trigName == "ME1_SH12_MM5" ||
				 trigName == "ME1_ISH7_TRK5" || trigName == "ME1_ISH7_MM5" || trigName == "ME1_RD5") {
				if(PassSingleEML1(10.0, emit, L1Cal2bEMs)) {
					//if(PassL2EM(6.0, emit, L2EM)) {
						if((trigName == "ME1_LEL15_TRK5" || trigName == "ME1_LEL15_MM5") &&
							 PassL3Ele_L_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "ME1_SH12_TRK5" || trigName == "ME1_SH12_MM5") && 
							 PassL3Ele_SH_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if((trigName == "ME1_ISH7_TRK5" || trigName == "ME1_ISH7_MM5") && 
							 PassL3Ele_SH_v12plus(7.0, emit, L3Ele) && PassL3Ele_ISH_v12plus(7.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "ME1_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
						//} // end if(PassL2EM(6.0, emit, L2EM)) {
				} // end if(PassSingleEML1(10.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "ME1_LEL15_TRK5" || trigName == "ME1_LEL15_MM5" ||
			else if(trigName == "ME2_LEL15_TRK5" || trigName == "ME2_LEL15_MM5" ||
							trigName == "ME2_SH12_TRK5" || trigName == "ME2_SH12_MM5" ||
							trigName == "ME2_ISH7_TRK5" || trigName == "ME2_ISH7_MM5" || trigName == "ME2_RD5") {
				if(PassSingleEMisoL1(7.0, emit, L1Cal2bEMs)) {
					if((trigName == "ME2_LEL15_TRK5" || trigName == "ME2_LEL15_MM5") &&
						 PassL3Ele_L_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "ME2_SH12_TRK5" || trigName == "ME2_SH12_MM5") && 
						 PassL3Ele_SH_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "ME2_ISH7_TRK5" || trigName == "ME2_ISH7_MM5") && 
							 PassL3Ele_SH_v12plus(7.0, emit, L3Ele) && PassL3Ele_ISH_v12plus(7.0, emit, L3Iso)) {emo_pass = true; pass = true;}
					if(trigName == "ME2_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if(PassSingleEMisoL1(7.0, emit, L1Cal2bEMs)) {
			} // end else if(trigName == "ME2_LEL15_TRK5" || trigName == "ME2_LEL15_MM5" ||
			else if(trigName == "ME3_LEL15_TRK5" || trigName == "ME3_LEL15_MM5" ||
							trigName == "ME3_SH12_TRK5" || trigName == "ME3_SH12_MM5" ||
							trigName == "ME3_ISH7_TRK5" || trigName == "ME3_ISH7_MM5" || trigName == "ME3_RD5") {
				if(PassSingleEML1(7.0, emit, L1Cal2bEMs)) {
					if((trigName == "ME3_LEL15_TRK5" || trigName == "ME3_LEL15_MM5") &&
						 PassL3Ele_L_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "ME3_SH12_TRK5" || trigName == "ME3_SH12_MM5") && 
						 PassL3Ele_SH_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "ME3_ISH7_TRK5" || trigName == "ME3_ISH7_MM5") && 
							 PassL3Ele_SH_v12plus(7.0, emit, L3Ele) && PassL3Ele_ISH_v12plus(7.0, emit, L3Iso)) {emo_pass = true; pass = true;}
					if(trigName == "ME3_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if(PassSingleEML1(7.0, emit, L1Cal2bEMs)) {
			} // end else if(trigName == "ME3_LEL15_TRK5" || trigName == "ME3_LEL15_MM5" ||
			else if(trigName == "ME4_LEL15_TRK5" || trigName == "ME4_LEL15_MM5" ||
							trigName == "ME4_SH12_TRK5" || trigName == "ME4_SH12_MM5" ||
							trigName == "ME4_ISH7_TRK5" || trigName == "ME4_ISH7_MM5" || trigName == "ME4_RD5") {
				if(PassSingleEML1(4.0, emit, L1Cal2bEMs)) {
					if((trigName == "ME4_LEL15_TRK5" || trigName == "ME4_LEL15_MM5") &&
						 PassL3Ele_L_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "ME4_SH12_TRK5" || trigName == "ME4_SH12_MM5") && 
						 PassL3Ele_SH_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "ME4_ISH7_TRK5" || trigName == "ME4_ISH7_MM5") && 
							 PassL3Ele_SH_v12plus(7.0, emit, L3Ele) && PassL3Ele_ISH_v12plus(7.0, emit, L3Iso)) {emo_pass = true; pass = true;}
					if(trigName == "ME4_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if(PassSingleEML1(4.0, emit, L1Cal2bEMs)) {
			} // end else if(trigName == "ME4_LEL15_TRK5" || trigName == "ME4_LEL15_MM5" ||
			else if(trigName == "ME5_LEL15_TRK5" || trigName == "ME5_LEL15_MM5" ||
							trigName == "ME5_SH12_TRK5" || trigName == "ME5_SH12_MM5" ||
							trigName == "ME5_ISH7_TRK5" || trigName == "ME5_ISH7_MM5" || trigName == "ME5_RD5") {
				if(PassSingleEML1(4.0, emit, L1Cal2bEMs)) {
					if((trigName == "ME5_LEL15_TRK5" || trigName == "ME5_LEL15_MM5") &&
						 PassL3Ele_L_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "ME5_SH12_TRK5" || trigName == "ME5_SH12_MM5") && 
						 PassL3Ele_SH_v12plus(12.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					if((trigName == "ME5_ISH7_TRK5" || trigName == "ME5_ISH7_MM5") && 
							 PassL3Ele_SH_v12plus(7.0, emit, L3Ele) && PassL3Ele_ISH_v12plus(7.0, emit, L3Iso)) {emo_pass = true; pass = true;}
					if(trigName == "ME5_RD5" && PassL3Ele_RD5_v12plus(emit, L3Ele)) {emo_pass = true; pass = true;}
				} // end if(PassSingleEML1(4.0, emit, L1Cal2bEMs)) {
			} // end else if(trigName == "ME5_LEL15_TRK5" || trigName == "ME5_LEL15_MM5" ||
			else {
				_FoundElectronMuon = false;
			}

                        int index = emo_pass ? 4 : -4;
   	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);	   

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	bool MatchEMTriggers::FindMatchEleTau_v15(std::string trigName, 
																						Collection<TMBEMCluster>& Ele,
																						const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																						const Collection<TMBL1Track>& L1Track,
																						const Collection<TMBL2EM>& L2EM,
																						const Collection<TMBL2Track>& L2Track,
																						const Collection<TMBL3Ele>& L3Ele,
																						const Collection<TMBL3Track>& L3Track,
																						const Collection<TMBL3Isolation>& L3Iso) {
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "ETAU1_SHT102TA10" || trigName == "ETAU1_SHT15_TK13" || 
				 trigName == "ETAU1_2T5SH5" || trigName == "ETAU1_SHT15_M25") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
						if(trigName == "ETAU1_SHT102TA10" && PassL3Ele_SHT_v12plus(10.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU1_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU1_2T5SH5" && PassL3Ele_SH_T5_v12plus(5.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU1_SHT15_M25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "ETAU1_SHT102TA10" || trigName == "ETAU1_SHT15_TK13" || 
			else if(trigName == "ETAU2_SHT102TA10" || trigName == "ETAU2_SHT15_TK13" || 
				 trigName == "ETAU2_2T5SH5" || trigName == "ETAU2_SHT15_M25") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
						if(trigName == "ETAU2_SHT102TA10" && PassL3Ele_SHT_v12plus(10.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU2_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU2_2T5SH5" && PassL3Ele_SH_T5_v12plus(5.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU2_SHT15_M25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "ETAU2_SHT102TA10" || trigName == "ETAU2_SHT15_TK13" || 
			else if(trigName == "ETAU3_SHT102TA10" || trigName == "ETAU3_SHT15_TK13" || 
				 trigName == "ETAU3_2T5SH5" || trigName == "ETAU3_SHT15_M25") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
						if(trigName == "ETAU3_SHT102TA10" && PassL3Ele_SHT_v12plus(10.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU3_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU3_2T5SH5" && PassL3Ele_SH_T5_v12plus(5.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU3_SHT15_M25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "ETAU3_SHT102TA10" || trigName == "ETAU3_SHT15_TK13" || 
			else if(trigName == "ETAU4_SHT102TA10" || trigName == "ETAU4_SHT15_TK13" || 
				 trigName == "ETAU4_2T5SH5" || trigName == "ETAU4_SHT15_M25") {
				if(PassSingleEML1(10.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
						if(trigName == "ETAU4_SHT102TA10" && PassL3Ele_SHT_v12plus(10.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU4_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU4_2T5SH5" && PassL3Ele_SH_T5_v12plus(5.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU4_SHT15_M25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "ETAU4_SHT102TA10" || trigName == "ETAU4_SHT15_TK13" || 
			else if(trigName == "ETAU5_SHT102TA10" || trigName == "ETAU5_SHT15_TK13" || 
				 trigName == "ETAU5_2T5SH5" || trigName == "ETAU5_SHT15_M25") {
				if(PassSingleEML1(10.0, emit, L1Cal2bEMs) && PassL1TTK(5.0, emit, L1Track)) {
					if(PassL2EM(10.0, emit, L2EM) && PassL2Track(8.0,"TTK", emit, L2Track)) {
						if(trigName == "ETAU5_SHT102TA10" && PassL3Ele_SHT_v12plus(10.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU5_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU5_2T5SH5" && PassL3Ele_SH_T5_v12plus(5.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU5_SHT15_M25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "ETAU5_SHT102TA10" || trigName == "ETAU5_SHT15_TK13" || 
			else if(trigName == "ETAU6_SHT102TA10" || trigName == "ETAU6_SHT15_TK13" || 
				 trigName == "ETAU6_2T5SH5" || trigName == "ETAU6_SHT15_M25") {
				if(PassSingleEML1(10.0, emit, L1Cal2bEMs) && PassL1TIS(5.0, emit, L1Track)) {
					if(PassL2EM(10.0, emit, L2EM) && PassL2Track(8.0,"TIS", emit, L2Track)) {
						if(trigName == "ETAU6_SHT102TA10" && PassL3Ele_SHT_v12plus(10.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU6_SHT15_TK13" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU6_2T5SH5" && PassL3Ele_SH_T5_v12plus(5.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ETAU6_SHT15_M25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "ETAU6_SHT102TA10" || trigName == "ETAU6_SHT15_TK13" || 

                        int index = emo_pass ? 5 : -5;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}


	/*-------- END METHODS FOR V15 ---------*/


	//+-------------------------------------------------------------------------------+
	//|                                                                               |
	//|            Methods for Triggerlist v16                                        |
	//|                                                                               |
  //+-------------------------------------------------------------------------------+
	bool MatchEMTriggers::FindMatchSingleEleCalOnly_v16(std::string trigName, 
																											Collection<TMBEMCluster>& Ele,
																											const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																											const Collection<TMBL2EM>& L2EM,
																											const Collection<TMBL3Ele>& L3Ele) {
		_FoundSingleEleCalOnly = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_SHT25" || trigName == "E1_SHT27" || trigName == "E1_LH3SH27" || 
				 trigName == "E1_SHT50" || trigName == "E1_SH60" || trigName == "E1_LH2SH27" ||
				 trigName == "E1_LH2L70" || trigName == "E1_L80" || trigName == "E1_SHT27_NOLUM") {
				//cout << " Check Trigger " << trigName << endl;
				if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
					//cout << "Passed L1 " << endl;
					if(PassL2EM(25.0, emit, L2EM) || PassL2EM_LH(19.0, 0.4, emit, L2EM)) {
						//cout << "Passed L2 " << endl;
						if(trigName == "E1_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_SHT27" && PassL3Ele_SHT_v12plus(27.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_SHT27_NOLUM" && PassL3Ele_SHT_v12plus(27.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_LH3SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele, 0.3)) {emo_pass = true; pass = true;}
						if(trigName == "E1_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "E1_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(22.0, emit, L2EM) && PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(19.0, emit, L1Towers)) {
			} // end if(trigName == "E1_SHT25" || trigName == "E1_SH35" || trigName == "E1_L70") {
			else if(trigName == "E2_SHT25" || trigName == "E2_SHT27" || trigName == "E2_LH3SH27" ||
							trigName == "E2_SHT50" || trigName == "E2_SH60" || trigName == "E2_LH2SH27" ||
							trigName == "E2_LH2L70" || trigName == "E2_L80") {
				//cout << " Check Trigger " << trigName << endl;
				if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
					//cout << "Passed L1 " << endl;
					if(PassL2EM_LHIso(16.0, 0.5, 0.2, emit, L2EM)) {
						//cout << "Passed L2 " << endl;
						if(trigName == "E2_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						//if(trigName == "E2_SHT27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_SHT27" && PassL3Ele_SHT_v12plus(27.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						//if(trigName == "E2_LH3SH27" && PassL3Ele_L_v12plus(27.0, emit, L3Ele, 0.3)) {emo_pass = true; pass = true;}
						if(trigName == "E2_LH3SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele, 0.3)) {emo_pass = true; pass = true;}
						if(trigName == "E2_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "E2_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEMisoL1(16.0, emit, L1Towers)) {
			} // end else if(trigName == "E2_SHT25" || trigName == "E2_SH35" || trigName == "E2_L70") {
			else {
				_FoundSingleEleCalOnly = false;
			}

                        int index = emo_pass ? 1 : -1;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}

	
	bool MatchEMTriggers::FindMatchSingleEleTrack_v16(std::string trigName, 
																										Collection<TMBEMCluster>& Ele,
																										const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																										const Collection<TMBL1Track>& L1Track,
																										const Collection<TMBL2EM>& L2EM,
																										const Collection<TMBL2Track>& L2Track,
																										const Collection<TMBL3Ele>& L3Ele,
																										const Collection<TMBL3Track>& L3Track,
																										const Collection<TMBL3Isolation>& L3Iso) {
		_FoundSingleEleTrack = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_LH2ISHT17T14" || trigName == "E1_T14LH2SH17") {
				if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
					if(PassL2EM(25.0, emit, L2EM) || PassL2EM_LH(19.0, 0.4, emit, L2EM)) {
						if(trigName == "E1_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "E1_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						//                                      if(PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso)) cout<<"PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso)!!!"<<endl;
						//                                      if(PassL3Track_v12plus(14.0,10,1.0, emit, L3Track)) cout<<"PassL3Track_v12plus(14.0,10,1.0, emit, L3Track)!!!"<<endl;
						//                                      if(PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) cout<<"PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)!!!"<<endl;
					} // end if(PassL2EM(19.0, emit, L2EM) && PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "E1_T13SHT15" || trigName == "E1_T15SH20" || trigName == "E1_ISHT15_TK13") {
			else if(trigName == "E2_LH2ISHT17T14" || trigName == "E2_T14LH2SH17") {
				if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_LHIso(16.0, 0.5, 0.2, emit, L2EM)) {
						if(trigName == "E2_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "E2_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
			} // end else if(trigName == "E2_T13SHT15" || trigName == "E2_T15SH20" || trigName == "E2_ISHT15_TK13") {
			else if(trigName == "TE1_SHT25_NOLUM" || trigName == "TE1_LH2SH27_NOLUM" ||
							trigName == "TE1_SHT50_NOLUM" || trigName == "TE1_SH60_NOLUM" || 
							trigName == "TE1_LH2L70_NOLUM" || trigName == "TE1_L80_NOLUM" ||
							trigName == "TE1_LH2ISHT17T14_NOLUM" || trigName == "TE1_T14LH2SH17_NOLUM" || 
							trigName == "TE1_LH2ISH24_NOLUM") {
				if(PassSingleEML1(16.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
					if(PassL2EM_LH(16.0, 0.5, emit, L2EM) && PassL2Track(13.0,"TTK", emit, L2Track)) {
						if(trigName == "TE1_SHT25_NOLUM" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_SHT50_NOLUM" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_SH60_NOLUM" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_L80_NOLUM" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_LH2SH27_NOLUM" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_LH2L70_NOLUM" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_T14LH2SH17_NOLUM" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_LH2ISHT17T14_NOLUM" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_LH2ISH24_NOLUM" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(16.0, emit, L2EM) && PassL2Track(13.0,"TTK", emit, L2Track)) {
				} // end if(PassSingleEML1(16.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE1_SHT25" || trigName == "TE1_SH35" || trigName == "TE1_L70" ||
			else if(trigName == "TE2_SHT25" || trigName == "TE2_LH2SH27" ||
							trigName == "TE2_SHT50" || trigName == "TE2_SH60" || 
							trigName == "TE2_LH2L70" || trigName == "TE2_L80" ||
							trigName == "TE2_LH2ISHT17T14" || trigName == "TE2_T14LH2SH17" || 
							trigName == "TE2_LH2ISH24") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
					if(PassL2EM_LHIso(13.0, 0.5, 0.2, emit, L2EM) && PassL2Track(10.0,"TTK", emit, L2Track)) {
						if(trigName == "TE2_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TTK", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE2_SHT25" || trigName == "TE2_SH35" || trigName == "TE2_L70" ||
			else if(trigName == "TE3_SHT25_NOLUM" || trigName == "TE3_LH2SH27_NOLUM" ||
							trigName == "TE3_SHT50_NOLUM" || trigName == "TE3_SH60_NOLUM" || 
							trigName == "TE3_LH2L70_NOLUM" || trigName == "TE3_L80_NOLUM" ||
							trigName == "TE3_LH2ISHT17T14_NOLUM" || trigName == "TE3_T14LH2SH17_NOLUM" || 
							trigName == "TE3_LH2ISH24_NOLUM") {
				if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
					if(PassL2EM_LH(13.0, 0.5, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
						if(trigName == "TE3_SHT25_NOLUM" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_SHT50_NOLUM" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_SH60_NOLUM" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_L80_NOLUM" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_LH2SH27_NOLUM" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_LH2L70_NOLUM" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_T14LH2SH17_NOLUM" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_LH2ISHT17T14_NOLUM" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_LH2ISH24_NOLUM" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(13.0, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE3_SHT25" || trigName == "TE3_SH35" || trigName == "TE3_L70" ||
			else if(trigName == "TE4_SHT25_NOLUM" || trigName == "TE4_LH2SH27_NOLUM" ||
							trigName == "TE4_SHT50_NOLUM" || trigName == "TE4_SH60_NOLUM" || 
							trigName == "TE4_LH2L70_NOLUM" || trigName == "TE4_L80_NOLUM" ||
							trigName == "TE4_LH2ISHT17T14_NOLUM" || trigName == "TE4_T14LH2SH17_NOLUM" || 
							trigName == "TE4_LH2ISH24_NOLUM") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TIS(10.0, emit, L1Track)) {
					if(PassL2EM_LH(13.0, 0.5, emit, L2EM) && PassL2Track(10.0,"TIS", emit, L2Track)) {
						if(trigName == "TE4_SHT25_NOLUM" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_SHT50_NOLUM" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_SH60_NOLUM" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_L80_NOLUM" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_LH2SH27_NOLUM" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_LH2L70_NOLUM" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_T14LH2SH17_NOLUM" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_LH2ISHT17T14_NOLUM" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SHT_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_LH2ISH24_NOLUM" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TIS", emit, L2Track)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TIS(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE4_SHT25" || trigName == "TE4_SH35" || trigName == "TE4_L70" ||
			else if(trigName == "TE5_SHT25" || trigName == "TE5_LH2SH27" ||
							trigName == "TE5_SHT50" || trigName == "TE5_SH60" || 
							trigName == "TE5_LH2L70" || trigName == "TE5_L80" ||
							trigName == "TE5_LH2ISHT17T14" || trigName == "TE5_T14LH2SH17" || 
							trigName == "TE5_LH2ISH24") {
				if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
					if(PassL2EM_LH(10.0, 0.2, emit, L2EM) && PassL2Track(8.0,"TES", emit, L2Track)) {
						if(trigName == "TE5_SHT25" && PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_SHT50" && PassL3Ele_SHT_v12plus(50.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_SH60" && PassL3Ele_SH_v12plus(60.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_L80" && PassL3Ele_L_v12plus(80.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_LH2SH27" && PassL3Ele_SH_v12plus(27.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_LH2L70" && PassL3Ele_L_v12plus(70.0, emit, L3Ele,0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_T14LH2SH17" && PassL3Ele_SH_T14_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_LH2ISHT17T14" && PassL3Ele_ISHT_v12plus(17.0, emit, L3Iso) &&
							 PassL3Track_v12plus(14.0,10,1.0, emit, L3Track) &&
							 PassL3Ele_SH_v12plus(17.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(8.0,"TES", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
			} // end else if(trigName == "TE5_SHT25" || trigName == "TE5_SH35" || trigName == "TE5_L70" ||
			else {
				_FoundSingleEleTrack = false;
			}

                        int index = emo_pass ? 2 : -2;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);
                        //cout << " Store " << emo_pass <<" " << trigName << endl;

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
		
                if (pass) return true;
		return false;
	}



	bool MatchEMTriggers::FindMatchSingleEleIso_v16(std::string trigName, 
																									Collection<TMBEMCluster>& Ele,
																									const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																									const Collection<TMBL2EM>& L2EM,
																									const Collection<TMBL3Ele>& L3Ele,
																									const Collection<TMBL3Isolation>& L3Iso) {
		_FoundSingleEleIso = true;
                bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_LH3ISH25" || trigName == "E1_LH2ISH24") {
				//cout << "Trigger under study " << trigName << endl;
				if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
					//cout << "--> Passed L1 "<< endl;
					if(PassL2EM(25.0, emit, L2EM) || PassL2EM_LH(19.0, 0.4, emit, L2EM)) {
						//cout << "--> Passed L2 "<< endl;
						if(trigName == "E1_LH3ISH25" && PassL3Ele_ISH_v12plus(25.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(25.0, emit, L3Ele, 0.3)) {emo_pass = true; pass = true;}
						if(trigName == "E1_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(22.0, emit, L2EM) && PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "E1_ISHT22" || trigName == "E1_ISH30") {
			else if(trigName == "E2_LH3ISH25" || trigName == "E2_LH2ISH24") {
				if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_LHIso(16.0, 0.5, 0.2, emit, L2EM)) {
						//if(trigName == "E2_LH2ISH25" && PassL3Ele_ISH_v12plus(25.0, emit, L3Iso) &&
						if(trigName == "E2_LH3ISH25" && PassL3Ele_ISH_v12plus(25.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(25.0, emit, L3Ele, 0.3)) {emo_pass = true; pass = true;}
						if(trigName == "E2_LH2ISH24" && PassL3Ele_ISH_v12plus(24.0, emit, L3Iso) &&
							 PassL3Ele_SH_v12plus(24.0, emit, L3Ele, 0.2)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
			} // end trigName == "E2_SHT25" || trigName == "E2_SH35") {
			else {
				_FoundSingleEleIso = false;
			}

                        int index = emo_pass ? 3 : -3;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}




	bool MatchEMTriggers::FindMatchEleJet_v16(std::string trigName, 
																						                                     Collection<TMBEMCluster>& Ele,
																						                                     const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																						                                     const Collection<TMBL1Track>& L1Track,
																						                                     const Collection<TMBL2EM>& L2EM,
																						                                     const Collection<TMBL2Track>& L2Track,
																						                                     const Collection<TMBL3Ele>& L3Ele,
																						                                     const Collection<TMBL3Track>& L3Track,
																						                                     const Collection<TMBL3Isolation>& L3Iso) {
		_FoundElectronJet = true;
	        bool pass = false;
		for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
                       bool emo_pass = false;      
			if(trigName == "E1_SHT15_2J_J25" || trigName == "E1_SHT15_JHA80" || trigName == "E1_T13L152JH50V") {
				if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
					if(PassL2EM(25.0, emit, L2EM) || PassL2EM_LH(19.0, 0.4, emit, L2EM)) {
						if(trigName == "E1_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E1_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(19.0, emit, L2EM) && PassL2EM_Iso(19.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEML1(19.0, emit, L1Cal2bEMs)) {
			} // end if(trigName == "E1_SHT15_2J_J25") {
			else if(trigName == "E2_SHT15_2J_J25" || trigName == "E2_SHT15_JHA80" || trigName == "E2_T13L152JH50V") {
				if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_LHIso(16.0, 0.5, 0.2, emit, L2EM)) {
						if(trigName == "E2_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "E2_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(16.0, 0.2, emit, L2EM)) {
				} // end if(PassSingleEMisoL1(16.0, emit, L1Cal2bEMs)) {
			} // end else if(trigName == "E2_SHT15_2J_J25") {
			else if(trigName == "TE1_SHT15_2J_J25_NOLUM" || trigName == "TE1_SHT15_JHA80" || trigName == "TE1_T13L152JH50V") {
				if(PassSingleEML1(16.0, emit, L1Cal2bEMs) && PassL1TTK(13.0, emit, L1Track)) {
					if(PassL2EM_LH(16.0, 0.5, emit, L2EM) && PassL2Track(13.0,"TTK", emit, L2Track)) {
						if(trigName == "TE1_SHT15_2J_J25_NOLUM" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE1_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(16.0, emit, L2EM) && PassL2Track(13.0,"TTK", emit, L2Track)) {
				} // end if(PassSingleEML1(16.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE1_SHT15_2J_J25") {
			else if(trigName == "TE2_SHT15_2J_J25" || trigName == "TE2_SHT15_JHA80" || trigName == "TE2_T13L152JH50V") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
					if(PassL2EM_LHIso(13.0, 0.5, 0.2, emit, L2EM) && PassL2Track(10.0,"TTK", emit, L2Track)) {
						if(trigName == "TE2_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE2_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TTK", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TTK(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE2_SHT15_2J_J25") {
			else if(trigName == "TE3_SHT15_2J_J25_NOLUM" || trigName == "TE3_SHT15_JHA80" || trigName == "TE3_T13L152JH50V") {
				if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
					if(PassL2EM_LH(13.0, 0.5, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
						if(trigName == "TE3_SHT15_2J_J25_NOLUM" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE3_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM(13.0, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE3_SHT15_2J_J25") {
			else if(trigName == "TE4_SHT15_2J_J25_NOLUM" || trigName == "TE4_SHT15_JHA80" || trigName == "TE4_T13L152JH50V") {
				if(PassSingleEMisoL1(13.0, emit, L1Cal2bEMs) && PassL1TIS(10.0, emit, L1Track)) {
					if(PassL2EM_LH(13.0, 0.5, emit, L2EM) && PassL2Track(10.0,"TIS", emit, L2Track) ) {
						if(trigName == "TE4_SHT15_2J_J25_NOLUM" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE4_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(13.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TIS", emit, L2Track)) {
				} // end if(PassSingleEML1(13.0, emit, L1Cal2bEMs) && PassL1TIS(10.0, emit, L1Track)) {
			} // end else if(trigName == "TE4_SHT15_2J_J25") {
			else if(trigName == "TE5_SHT15_2J_J25" || trigName == "TE5_SHT15_JHA80" || trigName == "TE5_T13L152JH50V") {
				if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TES(8.0, emit, L1Track)) {
					if(PassL2EM_LH(10.0, 0.2, emit, L2EM) && PassL2Track(8.0,"TES", emit, L2Track)) {
						if(trigName == "TE5_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "TE5_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(8.0,"TES", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
			} // end else if(trigName == "TE5_SHT15_2J_J25") {
			else if(trigName == "EJT_ISHT15_TK13" || trigName == "EJT_T13SHT15" || trigName == "EJT_T15SH20" ||
							trigName == "EJT_SHT15_2J_J25" || trigName == "EJT_SHT15_JHA80" || trigName == "EJT_13L152JH50V" ||
							trigName == "EJT_ISHT15_M25" || trigName == "EJT_SH30_M15" || trigName == "EJT_SHT20_M20") {
				if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs)) {
					if(PassL2EM_Iso(10.0, 0.2, emit, L2EM)) {
						if(trigName == "EJT_ISHT15_TK13" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso) && 
							 PassL3Track_v12plus(13.0,10,1.0, emit, L3Track)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_T13SHT15" && PassL3Ele_SHT_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_T15SH20" && PassL3Ele_SH_T15_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_ISHT15_M25" && PassL3Ele_ISHT_v12plus(15.0, emit, L3Iso)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_SH30_M15" && PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "EJT_SHT20_M20" && PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(8.0,"TES", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
			} // end else if(trigName == "EJT_SHT15_2J_J25") {
			else if(trigName == "ET1_SHT15_2J_J25" || trigName == "ET1_SHT15_JHA80" || trigName == "ET1_T13L152JH50V") {
				if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
					if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
						if(trigName == "ET1_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET1_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET1_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(10.0, 0.2, emit, L2EM) && PassL2Track(10.0,"TEL", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(10.0, emit, L1Cal2bEMs) && PassL1TEL(10.0, emit, L1Track)) {
			} // end else if(trigName == "ET1_SHT15_2J_J25") {
			else if(trigName == "ET2_SHT15_2J_J25" || trigName == "ET2_SHT15_JHA80" || trigName == "ET2_T13L152JH50V") {
				if(PassSingleEMisoL1(7.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
					if(PassL2EM_Iso(7.0, 0.2, emit, L2EM) && PassL2Track(6.7,"TES", emit, L2Track)) {
						if(trigName == "ET2_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET2_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET2_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(7.0, 0.2, emit, L2EM) && PassL2Track(6.7,"TES", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(7.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
			} // end else if(trigName == "ET2_SHT15_2J_J25") {
			else if(trigName == "ET3_SHT15_2J_J25" || trigName == "ET3_SHT15_JHA80" || trigName == "ET3_T13L152JH50V") {
				if(PassSingleEMisoL1(7.0, emit, L1Cal2bEMs) && PassL1TEL(5.0, emit, L1Track)) {
					if(PassL2EM_Iso(7.0, 0.2, emit, L2EM) && PassL2Track(6.7,"TEL", emit, L2Track)) {
						if(trigName == "ET3_SHT15_2J_J25" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET3_SHT15_JHA80" && PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
						if(trigName == "ET3_T13L152JH50V" && PassL3Ele_L_T13_v12plus(15.0, emit, L3Ele)) {emo_pass = true; pass = true;}
					} // end if(PassL2EM_Iso(7.0, 0.2, emit, L2EM) && PassL2Track(6.7,"TES", emit, L2Track)) {
				} // end if(PassSingleEMisoL1(7.0, emit, L1Cal2bEMs) && PassL1TES(5.0, emit, L1Track)) {
			} // end else if(trigName == "ET3_SHT15_2J_J25") {
			else {
				_FoundElectronJet = false;
			}

                        int index = emo_pass ? 6 : -6;
	                StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);

		} // end for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {

                if (pass) return true;
		return false;
	}


  //Added by Keti
  bool MatchEMTriggers::FindMatchSingleEleSCJetPt20(std::string trigName, Collection<TMBEMCluster>& Ele,
						    const Collection<TMBL3Jet>& L3Jet) {
    _FoundSingleEleSCJetPt20 = true;
    bool pass = false;
    for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
      bool emo_pass = false;
      if ( PassL3Ele_SCJet(20, 0.4, emit, L3Jet) ){
	emo_pass = true; pass=true;
      }else _FoundSingleEleSCJetPt20 = false;    

      int index = emo_pass ? 7 : -7;
      //      cout << " MatchEMTriggers::FindMatchSingleEleSCJetPt20_v16: emo_pass " << index << endl;
      StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);
    } // End of loop over TMBEMClusters
    if ( pass ) return true;
    return false;
  }

  bool MatchEMTriggers::FindMatchSingleEleSCJetPt25(std::string trigName, Collection<TMBEMCluster>& Ele,
							const Collection<TMBL3Jet>& L3Jet) {
    _FoundSingleEleSCJetPt25 = true;
    bool pass = false;
    for (Collection<TMBEMCluster>::iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
      bool emo_pass = false;
      if ( PassL3Ele_SCJet(25, 0.4, emit, L3Jet) ){
	emo_pass = true; pass=true;
      }else  _FoundSingleEleSCJetPt25 = false;   

      int index = emo_pass? 8 : -8;
      //      cout << " MatchEMTriggers::FindMatchSingleEleSCJetPt25_v16: emo_pass " << index << endl;
      StoreEMTrigInfo(emo_pass, &(*emit), trigName, index);
    } // End of loop over TMBEMCluster
    if ( pass ) return true;
    return false;
  }


  /*----------------------------------------------------------------------------------------------------------------*/
  // some private helper functions

  //Added by Keti
  bool MatchEMTriggers::PassL3Ele_SCJet(float Pt, float dR, Collection<TMBEMCluster>::const_iterator emit, 
					Collection<TMBL3Jet> L3Jet) const {
    bool matched = false;
    for ( Collection<TMBL3Jet>::const_iterator l3it = L3Jet.begin(); l3it != L3Jet.end(); ++l3it ) {
      if ( l3it->Pt() < Pt ) continue;
      double delta_R = kinem::delta_R(l3it->Eta(), l3it->Phi(), emit->CalEta(), emit->CalPhi());
      if ( delta_R < dR ) {
	matched = true;
	//	std::cout << " MatchEMTriggers::PassL3Ele_SCJet: FoundMatched Jet with Pt and dR " << l3it->Pt << " " << delta_R << std::endl;
	break;
      }
    }
    return matched;
  }

  // This function is for standard single L1 trigger tower.
  bool MatchEMTriggers::PassSingleL1Tower(float Et, Collection<TMBEMCluster>::const_iterator emit, 
																				 Collection<TMBL1CalTower> L1Towers) const
  {
    for (Collection<TMBL1CalTower>::const_iterator l1it = L1Towers.begin();
				 l1it != L1Towers.end();
				 l1it++) {
      if (l1it->Et() >= Et) { // copied >= from em_cert, not sure if it should be > or >=
				float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
				float deta = l1it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L1DeltaR) {
					return true;
				}
      }
    }
    return false;
  }

  // This function is for CEM(2,6) and such; It does after-the-fact clustering, like we do in
  // in em_cert, though the actual trigger does not
  bool MatchEMTriggers::PassTwoL1TowersSym(float Et, Collection<TMBEMCluster>::const_iterator emit, 
																					Collection<TMBL1CalTower> L1Towers) const
  {

    int count = 0;

    for (Collection<TMBL1CalTower>::const_iterator l1it = L1Towers.begin();
				 l1it != L1Towers.end();
				 l1it++) {

      if (l1it->Et() >= Et) { // copied >= from em_cert, not sure if it should be > or >=
				float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
				float deta = l1it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L1DeltaR) {
					count++;
				}
      }
    }
    return (count >= 2);
  }

  // This function is for CEM(2,3)CEM(1,9) and such; It does after-the-fact clustering, like we do in
  // in em_cert, though the actual trigger does not
  bool MatchEMTriggers::PassTwoL1TowersAsym(float Et_high, float Et_low, 
																					 Collection<TMBEMCluster>::const_iterator emit, 
																					 Collection<TMBL1CalTower> L1Towers) const
  {

		int high_towers = 0;
		int low_towers = 0;
    for (Collection<TMBL1CalTower>::const_iterator l1it = L1Towers.begin();
				 l1it != L1Towers.end();
				 l1it++) {

      if (l1it->Et() >= Et_high) { // copied >= from em_cert, not sure if it should be > or >=
				float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
				float deta = l1it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L1DeltaR) {
					high_towers++;
				}
      }
			if (l1it->Et() >= Et_low) { // copied >= from em_cert, not sure if it should be > or >=
				float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
				float deta = l1it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L1DeltaR) {
					low_towers++;
				}
      }
    }
		//cout << "Towers with Et > " << Et_high << ": " << high_towers << "  Towers with Et > " << 
		//	Et_low << ": " << low_towers << endl;
    return (high_towers >= 1 && low_towers >= 2);
  }

	// This function is for standard single L1 trigger tower.
  bool MatchEMTriggers::PassSingleEML1(float Et, Collection<TMBEMCluster>::const_iterator emit, 
																			 Collection<TMBL1Cal2bEM> L1EM) const
  {
    for (Collection<TMBL1Cal2bEM>::const_iterator l1it = L1EM.begin();
				 l1it != L1EM.end();
				 l1it++) {

      float ET = l1it->Etem() - 4.0;
      //if (l1it->Et() >= Et) {
			float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
			float deta = l1it->Eta() - emit->CalDetectorEta();
			//if (hypot(dphi, deta) < _L1DeltaR && l1it->Et() >= Et) {
			if (hypot(dphi, deta) < _L1DeltaR && ET > Et) {
				return true;
			}
			//else cout << l1it->Et() << " " << hypot(dphi, deta) << endl;
      //}
    }
    return false;
  }

	// This function is for standard single L1 trigger tower.
  bool MatchEMTriggers::PassSingleEMisoL1(float Et, Collection<TMBEMCluster>::const_iterator emit, 
																					Collection<TMBL1Cal2bEM> L1EM) const
  {
    for (Collection<TMBL1Cal2bEM>::const_iterator l1it = L1EM.begin();
				 l1it != L1EM.end();
				 l1it++) {

      float ET = l1it->Etem() - 4.0; 
      float EThad = l1it->Ethad() - 4.0;
      float ETiso = l1it->EmIsoRing() - 8.0;

      //if (l1it->Et() >= Et && l1it->Etem() > (8. * l1it->Ethad()) && l1it->Etem() > (8. * l1it->EmIsoRing())) { 
      //if (l1it->Etem() >= Et && l1it->Etem() > (8. * l1it->Ethad()) && l1it->Etem() > (8. * l1it->EmIsoRing())) { 
      //if ( ET >= Et && ET > (8. * l1it->Ethad()) && ET > (8. * l1it->EmIsoRing())) { 
      if ( ET > Et && ET > (8. * ETiso) && ET > (8. * EThad)) {
				float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
				float deta = l1it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L1DeltaR) {
					return true;
				}
      }
    }
    return false;
  }


	bool MatchEMTriggers::PassL1TTK(float Pt,
																	Collection<TMBEMCluster>::const_iterator emit, 
																	Collection<TMBL1Track> L1Track) const
	{
		int ptbin;
		if(Pt >= 10.) ptbin = 3;
		else if(Pt >= 5.) ptbin = 2;
		else if(Pt >= 3.) ptbin = 1;
		else ptbin = 0;
		for (Collection<TMBL1Track>::const_iterator l1it = L1Track.begin();
				 l1it != L1Track.end();
				 l1it++) {
			if(l1it->PtBin() >= ptbin) {
				float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
//				if (dphi < _L1DeltaR) {
				if (dphi < 0.3) {
					return true;
				}
			}	
		}
		return false;
	}


	bool MatchEMTriggers::PassL1TIS(float Pt,
																	Collection<TMBEMCluster>::const_iterator emit, 
																	Collection<TMBL1Track> L1Track) const
	{
		int ptbin;
		if(Pt >= 10.) ptbin = 3;
		else if(Pt >= 5.) ptbin = 2;
		else if(Pt >= 3.) ptbin = 1;
		else ptbin = 0;
		for (Collection<TMBL1Track>::const_iterator l1it = L1Track.begin();
				 l1it != L1Track.end();
				 l1it++) {
			if(l1it->PtBin() >= ptbin && l1it->Iso() >= 1) {
				float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
//				if (dphi < _L1DeltaR) {
				if (dphi < 0.3) {
					return true;
				}
			}	
		}
		return false;
	}
	
	bool MatchEMTriggers::PassL1TEL(float Pt,
																	Collection<TMBEMCluster>::const_iterator emit, 
																	Collection<TMBL1Track> L1Track) const
	{
		int ptbin;
		if(Pt >= 10.) ptbin = 3;
		else if(Pt >= 5.) ptbin = 2;
		else if(Pt >= 3.) ptbin = 1;
		else ptbin = 0;
		for (Collection<TMBL1Track>::const_iterator l1it = L1Track.begin();
				 l1it != L1Track.end();
				 l1it++) {
			if(l1it->PtBin() >= ptbin && l1it->CPSMatch() >= 1) {
				float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
//				if (dphi < _L1DeltaR) {
				if (dphi < 0.3) {
					return true;
				}
			}	
		}
		return false;
	}

	bool MatchEMTriggers::PassL1TES(float Pt,
																	Collection<TMBEMCluster>::const_iterator emit, 
																	Collection<TMBL1Track> L1Track) const
	{
		int ptbin;
		if(Pt >= 10.) ptbin = 3;
		else if(Pt >= 5.) ptbin = 2;
		else if(Pt >= 3.) ptbin = 1;
		else ptbin = 0;
		for (Collection<TMBL1Track>::const_iterator l1it = L1Track.begin();
				 l1it != L1Track.end();
				 l1it++) {
			if(l1it->PtBin() >= ptbin && l1it->Iso() >= 1 && l1it->CPSMatch() >= 1) {
				float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
//				if (dphi < _L1DeltaR) {
				if (dphi < 0.3) {
					return true;
				}
			}	
		}
		return false;
	}


  // This function is for standard L2
  bool MatchEMTriggers::PassL2EM(float Et, Collection<TMBEMCluster>::const_iterator emit, 
																Collection<TMBL2EM> L2EM) const
  {
    for (Collection<TMBL2EM>::const_iterator l2it = L2EM.begin();
				 l2it != L2EM.end();
				 l2it++) {
      if (l2it->Et() >= Et) {
				float dphi = kinem::delta_phi(l2it->Phi(), emit->CalDetectorPhi());
				float deta = l2it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L2DeltaR) {
					return true;
				}
      }
    }
    return false;
  }

	// This function is for standard L2
  bool MatchEMTriggers::PassL2EM(float Et, float Eta, Collection<TMBEMCluster>::const_iterator emit, 
																Collection<TMBL2EM> L2EM) const
  {
    for (Collection<TMBL2EM>::const_iterator l2it = L2EM.begin();
				 l2it != L2EM.end();
				 l2it++) {
      if (l2it->Et() >= Et && fabs(l2it->Eta()) < Eta) {
				float dphi = kinem::delta_phi(l2it->Phi(), emit->CalDetectorPhi());
				float deta = l2it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L2DeltaR) {
					return true;
				}
      }
    }
    return false;
  }


  // This function is for L2 with an emf cut, as in EM15_2J15 trigger
  bool MatchEMTriggers::PassL2EM_emf(float Et, float emf, 
																		Collection<TMBEMCluster>::const_iterator emit, 
																		Collection<TMBL2EM> L2EM) const
  {
    for (Collection<TMBL2EM>::const_iterator l2it = L2EM.begin();
				 l2it != L2EM.end();
				 l2it++) {
      if (l2it->Et() >= Et && l2it->Emf() >= emf) {
				float dphi = kinem::delta_phi(l2it->Phi(), emit->CalDetectorPhi());
				float deta = l2it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L2DeltaR) {
					return true;
				}
      }
    }
    return false;
  }

	// This function is for L2 with an isolation cut
  bool MatchEMTriggers::PassL2EM_Iso(float Et, float iso, 
																		Collection<TMBEMCluster>::const_iterator emit, 
																		Collection<TMBL2EM> L2EM) const
  {
    for (Collection<TMBL2EM>::const_iterator l2it = L2EM.begin();
				 l2it != L2EM.end();
				 l2it++) {
      if (l2it->Et() >= Et && l2it->Iso() <= iso) {
				float dphi = kinem::delta_phi(l2it->Phi(), emit->CalDetectorPhi());
				float deta = l2it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L2DeltaR) {
					return true;
				}
      }
    }
    return false;
  }

	// This function is for L2 with a Likelihood cut 
  bool MatchEMTriggers::PassL2EM_LH(float Et, float lh, 
																		Collection<TMBEMCluster>::const_iterator emit, 
																		Collection<TMBL2EM> L2EM) const
  {
    for (Collection<TMBL2EM>::const_iterator l2it = L2EM.begin();
				 l2it != L2EM.end();
				 l2it++) {
      if (l2it->Et() >= Et && l2it->EmLikelihood() >= lh) {
				float dphi = kinem::delta_phi(l2it->Phi(), emit->CalDetectorPhi());
				float deta = l2it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L2DeltaR) {
					return true;
				}
      }
    }
    return false;
  }


	// This function is for L2 with a Likelihood cut 
  bool MatchEMTriggers::PassL2EM_LHIso(float Et, float lh, float iso, 
																		Collection<TMBEMCluster>::const_iterator emit, 
																		Collection<TMBL2EM> L2EM) const
  {
    for (Collection<TMBL2EM>::const_iterator l2it = L2EM.begin();
				 l2it != L2EM.end();
				 l2it++) {
      if (l2it->Et() >= Et && l2it->EmLikelihood() >= lh && l2it->Iso() <= iso) {
				float dphi = kinem::delta_phi(l2it->Phi(), emit->CalDetectorPhi());
				float deta = l2it->Eta() - emit->CalDetectorEta();
				if (hypot(dphi, deta) < _L2DeltaR) {
					return true;
				}
      }
    }
    return false;
  }

	// This function is for L2 Tracks
  bool MatchEMTriggers::PassL2Track(float Pt, std::string tracktype,
																		Collection<TMBEMCluster>::const_iterator emit, 
																		Collection<TMBL2Track> L2Track) const
  {
		for (Collection<TMBL2Track>::const_iterator l2it = L2Track.begin();
				 l2it != L2Track.end();
				 l2it++) {
			if (l2it->CTTPt() >= Pt) {
				float dphi = kinem::delta_phi(l2it->CTTPhi(), emit->CalDetectorPhi());
//				if(dphi < 0.2) {
				if(dphi < 0.16) {
					if(tracktype == "TTK") return true;
					else if(tracktype == "TIS" && l2it->CTTIso() >= 1) return true;
					else if(tracktype == "TEL" && l2it->CTTPreshower() >= 1) return true;
					else if(tracktype == "TES" && l2it->CTTIso() >= 1 && l2it->CTTPreshower() >= 1) return true;
				}
      }
    }
    return false;
  }


  // this is to pass an l3 SHT for v8-11
  bool MatchEMTriggers::PassL3Ele_SHT_v811(float Et, 
																					Collection<TMBEMCluster>::const_iterator emit, 
																					Collection<TMBL3Ele> L3Ele) const
    
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {

      if (l3it->ToolName() == "ELE_LOOSE_SH_T") {

	// printf("\n\n Inside PassL3Ele_SHT_v811 \n");

				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.0 && 
						l3it->Em1Width() < 0.09 && l3it->Em2Width() < 0.08 && l3it->Em3Width() < 0.05) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
                                        float deta = l3it->DetEta() - emit->CalDetectorEta();
//					float deta = l3it->Eta() - emit->CalEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

  // this is to pass an l3 LOOSE for v8-11
  bool MatchEMTriggers::PassL3Ele_LOOSE_v811(float Et, 
																						Collection<TMBEMCluster>::const_iterator emit, 
																						Collection<TMBL3Ele> L3Ele) const
    
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {

      if (l3it->ToolName() == "ELE_LOOSE") {

				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.0) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
                                        float deta = l3it->DetEta() - emit->CalDetectorEta();
//					float deta = l3it->Eta() - emit->CalEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }
	
  // this is to pass an l3 VERYLOOSE for v8-11
  bool MatchEMTriggers::PassL3Ele_VERYLOOSE_v811(float Et, 
																								 Collection<TMBEMCluster>::const_iterator emit, 
																								 Collection<TMBL3Ele> L3Ele) const
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {

      if (l3it->ToolName() == "ELE_VLOOSE") {

				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.8 && fabs(l3it->DetEta()) < 3.0) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
                                        float deta = l3it->DetEta() - emit->CalDetectorEta();
//					float deta = l3it->Eta() - emit->CalEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	// this is to pass an l3 NOCUT for v8-11
  bool MatchEMTriggers::PassL3Ele_NOCUT_v811(float Et, 
																						 Collection<TMBEMCluster>::const_iterator emit, 
																						 Collection<TMBL3Ele> L3Ele) const
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {

      if (l3it->ToolName() == "ELE_NOCUT") {

				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && fabs(l3it->DetEta()) < 3.0) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
                                        float deta = l3it->DetEta() - emit->CalDetectorEta();
//					float deta = l3it->Eta() - emit->CalEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	// this is to pass an l3 Tracks for v8-11
  bool MatchEMTriggers::PassL3Track_v811(float Pt, int hitsxy, float dca,
																				 Collection<TMBEMCluster>::const_iterator emit, 
																				 Collection<TMBL3Track> L3Track) const
  {
    for (Collection<TMBL3Track>::const_iterator l3it = L3Track.begin(); l3it != L3Track.end(); l3it++) {
      if (l3it->ToolName() == "GlobalTracker") {
				if (l3it->Pt() >= Pt && l3it->nHitsXY() > hitsxy && l3it->DCA() < dca) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					//float deta = l3it->Eta() - emit->CalEta();
					if (dphi < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

  // this is to pass an L3 SHT for v12+
  bool MatchEMTriggers::PassL3Ele_SHT_v12plus(float Et, 
																						 Collection<TMBEMCluster>::const_iterator emit, 
																							Collection<TMBL3Ele> L3Ele, float LHood) const 
  {
    // not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;
		for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
	
		
      if (l3it->ToolName() == "ELE_NLV_SHT") {
	//if (l3it->ToolName() == "ELE_SHT") {
	
				bool isCC = fabs(l3it->DetEta()) < L3_CC_EDGE;
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
						(LHood < 0.0 || l3it->Likelihood() > LHood) &&
				     ((isCC &&  l3it->Em1RescWidth() < 1.8 && l3it->Em2RescWidth() < 1.4 && l3it->Em3RescWidth() < 1.15) ||
				     (!isCC &&  l3it->Em1RescWidth() < 1.0 && l3it->Em2RescWidth() < 1.0 && l3it->Em3RescWidth() < 1.2))) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
					//if (hypot(dphi, deta) < 0.16) {
						return true;
					}
				}
			}
    }
    return false;
  }

  // this is to pass an L3 SH for v12+
  bool MatchEMTriggers::PassL3Ele_SH_v12plus(float Et, 
																						Collection<TMBEMCluster>::const_iterator emit, 
																						 Collection<TMBL3Ele> L3Ele, float LHood) const
	{
    // not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_SH") {
				bool isCC = fabs(l3it->DetEta()) < L3_CC_EDGE;
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
						(LHood < 0.0 || l3it->Likelihood() > LHood) &&
				     ((isCC &&  l3it->Em1RescWidth() < 2.3 && l3it->Em2RescWidth() < 1.7 && l3it->Em3RescWidth() < 1.5) ||
				     (!isCC &&  l3it->Em1RescWidth() < 1.4 && l3it->Em2RescWidth() < 1.35 && l3it->Em3RescWidth() < 1.4))) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
					//if (hypot(dphi, deta) < 0.16) {
						return true;
					}
					//else cout << "DeltaR " << dphi << " " << deta << " " << sqrt(deta*deta + dphi*dphi) << endl;
				}
      }
    }
    return false;
  }

	// this is to pass an L3 SH for v12+
  bool MatchEMTriggers::PassL3Ele_L_v12plus(float Et, 
																						Collection<TMBEMCluster>::const_iterator emit, 
																						Collection<TMBL3Ele> L3Ele, float LHood) const 	   
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
			//cout << l3it->ToolName() << " " << l3it->Et() << " " << l3it->Emf() << endl;
      if (l3it->ToolName() == "ELE_NLV") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 &&
						(LHood < 0.0 || l3it->Likelihood() > LHood)) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					//cout << dphi << " " << deta << " " << sqrt(deta*deta + dphi*dphi) << endl;
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	
	// this is to pass an L3 SH for v12+
  bool MatchEMTriggers::PassL3Ele_VL_v12plus(float Et, 
																						Collection<TMBEMCluster>::const_iterator emit, 
																						Collection<TMBL3Ele> L3Ele) const
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_VL") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.8 && fabs(l3it->DetEta()) < 3.6) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	// this is to pass an L3 NC for v12+
  bool MatchEMTriggers::PassL3Ele_NC_v12plus(float Et, 
																						Collection<TMBEMCluster>::const_iterator emit, 
																						Collection<TMBL3Ele> L3Ele) const
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_NC") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && fabs(l3it->DetEta()) < 3.6) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }
	

	// this is to pass an L3 T13L for v12+
  bool MatchEMTriggers::PassL3Ele_L_T13_v12plus(float Et, 
																								Collection<TMBEMCluster>::const_iterator emit, 
																								Collection<TMBL3Ele> L3Ele) const 	   
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_T13") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	// this is to pass an L3 T12L for v12+
  bool MatchEMTriggers::PassL3Ele_L_T12_v12plus(float Et, 
																								Collection<TMBEMCluster>::const_iterator emit, 
																								Collection<TMBL3Ele> L3Ele) const 	   
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_T13") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	bool MatchEMTriggers::PassL3Ele_L_T8_v12plus(float Et, 
																							 Collection<TMBEMCluster>::const_iterator emit, 
																							 Collection<TMBL3Ele> L3Ele) const 	   
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_T8") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	
	bool MatchEMTriggers::PassL3Ele_SHT_T7_v12plus(float Et, 
																							 Collection<TMBEMCluster>::const_iterator emit, 
																							 Collection<TMBL3Ele> L3Ele) const 	   
  {
		// not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_SHT_T7") {
				bool isCC = fabs(l3it->DetEta()) < L3_CC_EDGE;
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
				    ((isCC &&  l3it->Em1RescWidth() < 1.8 && l3it->Em2RescWidth() < 1.4 && l3it->Em3RescWidth() < 1.15) ||
				     (!isCC &&  l3it->Em1RescWidth() < 1.0 && l3it->Em2RescWidth() < 1.0 && l3it->Em3RescWidth() < 1.2))) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	bool MatchEMTriggers::PassL3Ele_SHT_T13_v12plus(float Et, 
																									Collection<TMBEMCluster>::const_iterator emit, 
																									Collection<TMBL3Ele> L3Ele) const 	   
  {
		// not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;
		for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_SHT_T13") {
				bool isCC = fabs(l3it->DetEta()) < L3_CC_EDGE;
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
				    ((isCC &&  l3it->Em1RescWidth() < 1.8 && l3it->Em2RescWidth() < 1.4 && l3it->Em3RescWidth() < 1.15) ||
				     (!isCC &&  l3it->Em1RescWidth() < 1.0 && l3it->Em2RescWidth() < 1.0 && l3it->Em3RescWidth() < 1.2))) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	bool MatchEMTriggers::PassL3Ele_SHT_IT10T_v12plus(float Et, 
																											Collection<TMBEMCluster>::const_iterator emit, 
																											Collection<TMBL3Ele> L3Ele) const 	   
  {
		// not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_SHT_IT10T") {
				bool isCC = fabs(l3it->DetEta()) < L3_CC_EDGE;
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
				    ((isCC &&  l3it->Em1RescWidth() < 1.8 && l3it->Em2RescWidth() < 1.4 && l3it->Em3RescWidth() < 1.15) ||
				     (!isCC &&  l3it->Em1RescWidth() < 1.0 && l3it->Em2RescWidth() < 1.0 && l3it->Em3RescWidth() < 1.2))) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }


	bool MatchEMTriggers::PassL3Ele_SH_T5_v12plus(float Et, 
																								Collection<TMBEMCluster>::const_iterator emit, 
																								Collection<TMBL3Ele> L3Ele) const 	   
  {
		// not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_SH_T5") {
				bool isCC = fabs(l3it->DetEta()) < L3_CC_EDGE;
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
				    ((isCC &&  l3it->Em1RescWidth() < 2.3 && l3it->Em2RescWidth() < 1.7 && l3it->Em3RescWidth() < 1.5) ||
				     (!isCC &&  l3it->Em1RescWidth() < 1.4 && l3it->Em2RescWidth() < 1.35 && l3it->Em3RescWidth() < 1.4))) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	bool MatchEMTriggers::PassL3Ele_SH_T15_v12plus(float Et, 
																								 Collection<TMBEMCluster>::const_iterator emit, 
																								 Collection<TMBL3Ele> L3Ele) const 	   
  {
		// not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
			//cout << "PassL3Ele_SH_T15_v12plus " << l3it->ToolName() << endl;
      if (l3it->ToolName() == "ELE_NLV_SH_T15") {
				bool isCC = fabs(l3it->DetEta()) < L3_CC_EDGE;
				// don't know if should use DetEta or Eta below
				//cout << l3it->Et() << " " << emit->Pt() << endl;
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
				    ((isCC &&  l3it->Em1RescWidth() < 2.3 && l3it->Em2RescWidth() < 1.7 && l3it->Em3RescWidth() < 1.5) ||
				     (!isCC &&  l3it->Em1RescWidth() < 1.4 && l3it->Em2RescWidth() < 1.35 && l3it->Em3RescWidth() < 1.4))) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
					//else //cout << dphi << " " << deta << " " << hypot(dphi, deta) << endl;
				}
      }
    }
    return false;
  }

	bool MatchEMTriggers::PassL3Ele_SH_T14_v12plus(float Et, 
																								 Collection<TMBEMCluster>::const_iterator emit, 
																								 Collection<TMBL3Ele> L3Ele, float LHood) const 	   
  {
		// not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
			//cout << "PassL3Ele_SH_T15_v12plus " << l3it->ToolName() << endl;
      if (l3it->ToolName() == "ELE_NLV_SH_T14") {
				bool isCC = fabs(l3it->DetEta()) < L3_CC_EDGE;
				// don't know if should use DetEta or Eta below
				//cout << l3it->Et() << " " << emit->Pt() << endl;
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
						(LHood < 0.0 || l3it->Likelihood() > LHood) &&
				    ((isCC &&  l3it->Em1RescWidth() < 2.3 && l3it->Em2RescWidth() < 1.7 && l3it->Em3RescWidth() < 1.5) ||
				     (!isCC &&  l3it->Em1RescWidth() < 1.4 && l3it->Em2RescWidth() < 1.35 && l3it->Em3RescWidth() < 1.4))) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
					//else //cout << dphi << " " << deta << " " << hypot(dphi, deta) << endl;
				}
      }
    }
    return false;
  }



	bool MatchEMTriggers::PassL3Ele_L_T4_v12plus(float Et, 
																							 Collection<TMBEMCluster>::const_iterator emit, 
																							 Collection<TMBL3Ele> L3Ele) const 	   
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_T4") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	// this is to pass an L3 T25VL for v12+
  bool MatchEMTriggers::PassL3Ele_VL_T25_v12plus(float Et, 
																								 Collection<TMBEMCluster>::const_iterator emit, 
																								 Collection<TMBL3Ele> L3Ele) const
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_VL_T25") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.8 && fabs(l3it->DetEta()) < 3.6) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	// this is to pass an L3 T15L for v12+
  bool MatchEMTriggers::PassL3Ele_L_T15_v12plus(float Et, 
																								 Collection<TMBEMCluster>::const_iterator emit, 
																								 Collection<TMBL3Ele> L3Ele) const
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_L_T15") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	bool MatchEMTriggers::PassL3Ele_SH_T13_v12plus(float Et, 
																								Collection<TMBEMCluster>::const_iterator emit, 
																								Collection<TMBL3Ele> L3Ele) const 	   
  {
		// not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_NLV_SH_T13") {
				bool isCC = fabs(l3it->DetEta()) < L3_CC_EDGE;
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
				    ((isCC &&  l3it->Em1RescWidth() < 2.3 && l3it->Em2RescWidth() < 1.7 && l3it->Em3RescWidth() < 1.5) ||
				     (!isCC &&  l3it->Em1RescWidth() < 1.4 && l3it->Em2RescWidth() < 1.35 && l3it->Em3RescWidth() < 1.4))) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }


	// this is to pass an L3 ISH for v12+
  bool MatchEMTriggers::PassL3Ele_ISH_v12plus(float Et, 
																							Collection<TMBEMCluster>::const_iterator emit, 
																							Collection<TMBL3Isolation> L3Iso) const
  {
    for (Collection<TMBL3Isolation>::const_iterator l3it = L3Iso.begin();
				 l3it != L3Iso.end();
				 l3it++) {
			//cout << l3it->ToolName() << " " << l3it->Et() << " " << l3it->TrackPtSum() << endl;
      if (l3it->ToolName() == "IsoEle_SH") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->TrackPtSum() < 1.0 && fabs(l3it->DetEta()) < 3.6) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
					//if (hypot(dphi, deta) < 0.16) {
						return true;
					}
					//else cout << "DeltaR " << dphi << " " << deta << " " << sqrt(deta*deta + dphi*dphi) << endl;
				}
      }
    }
    return false;
  }

	// this is to pass an L3 ISHT for v12+
  bool MatchEMTriggers::PassL3Ele_ISHT_v12plus(float Et, 
																							 Collection<TMBEMCluster>::const_iterator emit, 
																							 Collection<TMBL3Isolation> L3Iso) const
  {   

    for (Collection<TMBL3Isolation>::const_iterator l3it = L3Iso.begin();
				 l3it != L3Iso.end();
				 l3it++) {
      if (l3it->ToolName() == "IsoEle_SHT") {
				// don't know if should use DetEta or Eta below
				if (l3it->Et() > Et && l3it->TrackPtSum() < 1.0 && fabs(l3it->DetEta()) < 3.6) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
					//if (hypot(dphi, deta) < 0.16) {
						return true;
					}
				}
      }
    }
    return false;
  }
	

	// this is to pass an L3 RD for v12+
  bool MatchEMTriggers::PassL3Ele_RD5_v12plus(Collection<TMBEMCluster>::const_iterator emit, 
																						 Collection<TMBL3Ele> L3Ele) const 	   
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
				 l3it != L3Ele.end();
				 l3it++) {
      if (l3it->ToolName() == "ELE_Road_T5") {
				// don't know if should use DetEta or Eta below
				if (l3it->Emf() > 0.85 && fabs(l3it->DetEta()) < 3.6 && 
						l3it->EoverP() > 0.6 && l3it->EoverP() < 1.05) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (hypot(dphi, deta) < _L3DeltaR) {
						return true;
					}
				}
      }
    }
    return false;
  }

	// this is to pass an l3 Tracks for v12plus
  bool MatchEMTriggers::PassL3Track_v12plus(float Pt, int hitsxy, float dca, 
																						Collection<TMBEMCluster>::const_iterator emit, 
																						Collection<TMBL3Track> L3Track) const
  {

    float _L3DeltaRsq = _L3DeltaR * _L3DeltaR;

    for (Collection<TMBL3Track>::const_iterator l3it = L3Track.begin(); l3it != L3Track.end(); l3it++) {
    if (l3it->ToolName() == "PhTrk3" || l3it->ToolName() == "PhTrk8" || l3it->ToolName() == "PhTrk10") {

				if (l3it->Pt() > Pt && l3it->nHitsXY() > hitsxy && l3it->DCA() < dca) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					if (dphi < _L3DeltaRsq) {
					  //if (dphi < 0.16) {
						return true;
					}
				}
      }
    }
    return false;
  }

	// this is to pass an l3 Tracks for v12plus
  bool MatchEMTriggers::PassL3IsoTrack_v12plus(float Pt, int hitsxy, float dca,
																						Collection<TMBEMCluster>::const_iterator emit, 
																						Collection<TMBL3Track> L3Track) const
  {
    float _L3DeltaRsq = _L3DeltaR * _L3DeltaR;

    for (Collection<TMBL3Track>::const_iterator l3it = L3Track.begin(); l3it != L3Track.end(); l3it++) {
      if (l3it->ToolName() == "IsoTrk5") {
				if (l3it->Pt() > Pt && l3it->nHitsXY() > hitsxy && l3it->DCA() < dca) {
					float dphi = kinem::delta_phi(l3it->Phi(), emit->CalPhi());
					//float deta = l3it->DetEta() - emit->CalDetectorEta();
					if (dphi < _L3DeltaRsq) {
						return true;
					}
				}
      }
    }
    return false;
  }


	bool MatchEMTriggers::DiElectronPassL1(float Et1, float Et2, 
																				 const Collection<TMBEMCluster>& Ele,
																				 const Collection<TMBL1CalTower>& L1Towers) 
	{
		int Et1towers = 0, Et2towers = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(Et1 == Et2) {
				if(PassTwoL1TowersSym(Et1, emit, L1Towers)) return true;
				else if(PassSingleL1Tower(Et1, emit, L1Towers)) Et1towers++;
				if(Et1towers >= 2) return true;
			}
			else {
				if(PassTwoL1TowersAsym(Et1, Et2, emit, L1Towers)) return true;
				else if(PassSingleL1Tower(Et1, emit, L1Towers)) {
					Et1towers++;
					Et2towers++;
				}
				else if(PassSingleL1Tower(Et2, emit, L1Towers)) Et2towers++;
				if(Et1towers >= 1 && Et2towers >= 2) return true;
			}
		}	
		return false;
	}

	bool MatchEMTriggers::DiElectronPassL1(float Et1, 
																				 const Collection<TMBEMCluster>& Ele,
																				 const Collection<TMBL1CalTower>& L1Towers) 
	{
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if (PassSingleL1Tower(Et1, emit, L1Towers)) return true;
		}	
		return false;
	}

	bool MatchEMTriggers::DiElectronPassL1(float Pt1, std::string tracktype,
																				 const Collection<TMBEMCluster>& Ele,
																				 const Collection<TMBL1Track>& L1Track) 
	{
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(tracktype == "TTK" && PassL1TTK(Pt1, emit, L1Track)) return true;
			else if(tracktype == "TIS" && PassL1TIS(Pt1, emit, L1Track)) return true;
			else if(tracktype == "TEL" && PassL1TEL(Pt1, emit, L1Track)) return true;
			else if(tracktype == "TES" && PassL1TES(Pt1, emit, L1Track)) return true;
		}	
		return false;
	}

	bool MatchEMTriggers::DiElectronPassL1(float Pt1, std::string tracktype1,
																				 float Pt2, std::string tracktype2,
																				 const Collection<TMBEMCluster>& Ele,
																				 const Collection<TMBL1Track>& L1Track) 
	{
		int Pt1track = 0, Pt2track = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(tracktype1 == "TTK" && PassL1TTK(Pt1, emit, L1Track)) Pt1track++;
			else if(tracktype1 == "TIS" && PassL1TIS(Pt1, emit, L1Track)) Pt1track++;
			else if(tracktype1 == "TEL" && PassL1TEL(Pt1, emit, L1Track)) Pt1track++;
			else if(tracktype1 == "TES" && PassL1TES(Pt1, emit, L1Track)) Pt1track++;
			if(tracktype2 == "TTK" && PassL1TTK(Pt2, emit, L1Track)) Pt2track++;
			else if(tracktype2 == "TIS" && PassL1TIS(Pt2, emit, L1Track)) Pt2track++;
			else if(tracktype2 == "TEL" && PassL1TEL(Pt2, emit, L1Track)) Pt2track++;
			else if(tracktype2 == "TES" && PassL1TES(Pt2, emit, L1Track)) Pt2track++;
			if(Pt1track >= 1 && Pt2track >= 2) return true;
		}	
		return false;
	}


	bool MatchEMTriggers::DiElectronPassL2(float Et1, float Eta1, float Et2, float Eta2,
																				 const Collection<TMBEMCluster>& Ele,
																				 const Collection<TMBL2EM>& L2EM) 
	{
		int Et1em = 0, Et2em = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(PassL2EM(Et1, Eta1, emit, L2EM)) {
					 Et1em++;
					 Et2em++;
			}
			else if(PassL2EM(Et2, Eta2, emit, L2EM)) Et2em++;
			if(Et1em >= 1 && Et2em >= 2) return true;
			
		}	
		return false;
	}
	
	
	bool MatchEMTriggers::DiElectronPassL2(float Et1, float Eta1, 
																				 const Collection<TMBEMCluster>& Ele,
																				 const Collection<TMBL2EM>& L2EM) 
	{
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(PassL2EM(Et1, Eta1, emit, L2EM)) return true;
		}
		return false;
	}

	bool MatchEMTriggers::DiElectronPassL3_LOOSE_v12plus(float Et1, int Nele,
																											 const Collection<TMBEMCluster>& Ele,
																											 const Collection<TMBL3Ele>& L3Ele) 
	{
		int Nelepassed = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(PassL3Ele_L_v12plus(Et1, emit, L3Ele)) Nelepassed++;
			if(Nelepassed >= Nele) return true;
		}	
		return false;
	}

	bool MatchEMTriggers::DiElectronPassL3_SH_v12plus(float Et1, int Nele,
																										const Collection<TMBEMCluster>& Ele,
																										const Collection<TMBL3Ele>& L3Ele) 
	{
		int Nelepassed = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(PassL3Ele_SH_v12plus(Et1, emit, L3Ele)) Nelepassed++;
			if(Nelepassed >= Nele) return true;
		}	
		return false;
	}
			
	bool MatchEMTriggers::DiElectronPassL3_SHT_v12plus(float Et1, int Nele,
																										 const Collection<TMBEMCluster>& Ele,
																										 const Collection<TMBL3Ele>& L3Ele) 
	{
		int Nelepassed = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(PassL3Ele_SHT_v12plus(Et1, emit, L3Ele)) Nelepassed++;
			if(Nelepassed >= Nele) return true;
		}	
		return false;
	}

	bool MatchEMTriggers::DiElectronPassL3_L_T8_v12plus(float Et1, int Nele,
																											const Collection<TMBEMCluster>& Ele,
																											const Collection<TMBL3Ele>& L3Ele) 
	{
		int Nelepassed = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(PassL3Ele_L_T8_v12plus(Et1, emit, L3Ele)) Nelepassed++;
			if(Nelepassed >= Nele) return true;
		}	
		return false;
	}

	bool MatchEMTriggers::DiElectronPassL3_SHT_T7_v12plus(float Et1, int Nele,
																											const Collection<TMBEMCluster>& Ele,
																											const Collection<TMBL3Ele>& L3Ele) 
	{
		int Nelepassed = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(PassL3Ele_SHT_T7_v12plus(Et1, emit, L3Ele)) Nelepassed++;
			if(Nelepassed >= Nele) return true;
		}	
		return false;
	}

	bool MatchEMTriggers::DiElectronPassL3_SH_T5_v12plus(float Et1, int Nele,
																											 const Collection<TMBEMCluster>& Ele,
																											 const Collection<TMBL3Ele>& L3Ele) 
	{
		int Nelepassed = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(PassL3Ele_SH_T5_v12plus(Et1, emit, L3Ele)) Nelepassed++;
			if(Nelepassed >= Nele) return true;
		}	
		return false;
	}

	bool MatchEMTriggers::DiElectronPassL3_L_T4_v12plus(float Et1, int Nele,
																											const Collection<TMBEMCluster>& Ele,
																											const Collection<TMBL3Ele>& L3Ele) 
	{
		int Nelepassed = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(PassL3Ele_L_T4_v12plus(Et1, emit, L3Ele)) Nelepassed++;
			if(Nelepassed >= Nele) return true;
		}	
		return false;
	}


	bool MatchEMTriggers::DiElectronPassL3_Track_v12plus(float Pt, int hitsxy, float dca, int Nele,
																											 const Collection<TMBEMCluster>& Ele, 
																											 const Collection<TMBL3Track>& L3Track) 
	{	
		int Nelepassed = 0;
		for (Collection<TMBEMCluster>::const_iterator emit = Ele.begin(); emit != Ele.end(); emit++) {
			if(PassL3Track_v12plus(Pt, hitsxy, dca, emit, L3Track)) Nelepassed++;
			if(Nelepassed >= Nele) return true;
		}	
		return false;
	}


} // using namespace caf_trigger

ClassImp(caf_trigger::MatchEMTriggers)
  
