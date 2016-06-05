/* File MatchEMTriggers.hpp
 *
 * Created       : Nov 28 12:31:34 CDT 2006
 * Author        : Marc Hohlfeld hohlfeld@fnal.gov
 *
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
 *
 * Modified      : Mika Vesterinen, mikav@fnal.gov
 *               : May 2009  
 * Comments      : Added possiblity to tag as opposed to select events. Default is still to select events.
 */



#ifndef MatchEMTriggers_HPP_
#define MatchEMTriggers_HPP_

#include <set>
#include <string>

#include "cafe/Processor.hpp"
#include "cafe/Event.hpp"
#include "caf_trigger/TriggerMap.hpp"


using namespace cafe;
using namespace std;

namespace caf_trigger {


  /*! \brief 
   This processor passes events if any electron given to it fires the
   electron part of any trigger given to it. Only triggers that actually
   fired are considered. (Checking whether the trigger fired is copied
   from cafe/Trigger.{hpp|cpp}, matching code is modeled after
   caf_trigger/MatchL1CalTowerReco.{hpp|cpp} and similar for L2 and L3,
   and after em_cert.)

    Required parameters:
    --------------------
    - .Triggers: vector of string (eg: E1_SHT22 E1_SHT15_2J_J25) 
      Names of the triggers to consider for matching. Only ones that actually
      fire are considered for matching.

    - .EMBranch: string [default EMscone]
      The electrons to consider for matching. Returns true if ANY match, not
      necessarily ALL. (Should be able to modify easily and provide and
      ALL mode if that's wanted.)
      
      - Tag: if tag is an empty string, the processor will select events. If                                                                                                                 
      tag is an non empty string, the processor will not select events but tag                                                                                                                       
      them with event.put(). [default "", i.e. select events]    

    - .L1CalTowerBranch: string [default L1CalEMTowers]
      The L1 cal towers for matching (Run IIa).

    - .L1Cal2bBranch: string [default L1Cal2bEM]
      The L1 EM for matching (Run IIb).

	  - .L1TrackBranch: string [default L1Track]
      The L1 tracks for matching.

    - .L2EMBranch: string [default L2EM]
      The L2 EM for matching.

    - .L2TrackBranch: string [default STTPT]
      The L2 tracks for matching.

    - .L3EleBranch: string [default L3Electron]
      The L3 electrons for matching.

    - .L3TrackBranch: string [default L3Track]
      The L3 Tracks for matching.

	  - .L3IsoBranch: string [default L3Isolation]
      The L3 Isolation objects for matching.


    - .L1DeltaR: double [default: 0.4]
    - .L2DeltaR: double [default: 0.4]
    - .L3DeltaR: double [default: 0.4]

		- Which kind of electron triggers should be considered
		  DoSingleEleCalOnly: bool [default true] 
			DoSingleEleTrack: bool [default true] 
			DoSingleEleIso: bool [default true] 
			DoDiEleCalOnly: bool [default true] 
			DoDiEleTrack: bool [default true] 
			DoDiEleIso: bool [default true] 
			DoElectronJet: bool [default true]
			DoElectronMuon: bool [default true]
			DoElectronTau: bool [default true]

      The maximum distance between the electron and the trigger object to 
      consider it a match.

    \authors Jovan Mitrevski (jmitrevs@fnal.gov)

  */


  
  class MatchEMTriggers : public cafe::Processor {
	/**
	   this is a Template to build a new processor in package "top_cafe"
	 */    
  public:
    
    // Constructor, destructor: 
    MatchEMTriggers(const char *name);
    ~MatchEMTriggers();
    
    void begin();
    bool processEvent(cafe::Event& event);
    void finish();
    void inputFileOpened(TFile *file);
    void inputFileClosing(TFile *file);
    
    ClassDef(MatchEMTriggers, 0);
    
  private:

    void MatchEMTriggers::StoreEMTrigInfo(bool emo_pass, TMBEMCluster* emp, std::string trigName, int index);

		bool FindMatchSingleEleCalOnly_v811(std::string trigName, const int trigVersion,
																				Collection<TMBEMCluster>& Ele,
																				const Collection<TMBL1CalTower>& L1Towers,
																				const Collection<TMBL2EM>& L2EM,
																				const Collection<TMBL3Ele>& L3Ele);
 
		bool FindMatchSingleEleTrack_v811(std::string trigName, const int trigVersion,
																			Collection<TMBEMCluster>& Ele,
																			const Collection<TMBL1CalTower>& L1Towers, 
																			const Collection<TMBL2EM>& L2EM,
																			const Collection<TMBL3Ele>& L3Ele,
																			const Collection<TMBL3Track>& L3Track);

		bool FindMatchDiEleCalOnly_v811(std::string trigName, const int trigVersion,
																		Collection<TMBEMCluster>& Ele,
																		const Collection<TMBL1CalTower>& L1Towers, 
																		const Collection<TMBL2EM>& L2EM,
																		const Collection<TMBL3Ele>& L3Ele);
 
		bool FindMatchDiEleTrack_v811(std::string trigName, const int trigVersion,
																	Collection<TMBEMCluster>& Ele,
																	const Collection<TMBL1CalTower>& L1Towers,
																	const Collection<TMBL3Ele>& L3Ele,
																	const Collection<TMBL3Track>& L3Track);
		
		bool FindMatchEleJet_v811(std::string trigName,Collection<TMBEMCluster>& Ele,
															const Collection<TMBL1CalTower>& L1Towers, 
															const Collection<TMBL2EM>& L2EM, 
															const Collection<TMBL3Ele>& L3Ele);

		bool FindMatchEleMuon_v811(std::string trigName,Collection<TMBEMCluster>& Ele,
															 const Collection<TMBL1CalTower>& L1Towers, 
															 const Collection<TMBL3Ele>& L3Ele);

		bool FindMatchSingleEleCalOnly_v12(std::string trigName,
																			Collection<TMBEMCluster>& Ele,
																			 const Collection<TMBL1CalTower>& L1Towers,
																			 const Collection<TMBL3Ele>& L3Ele);
 
		bool FindMatchSingleEleTrack_v12(std::string trigName,
																		Collection<TMBEMCluster>& Ele,
																		 const Collection<TMBL1CalTower>& L1Towers, 
																		 const Collection<TMBL1Track>& L1Track,
																		 const Collection<TMBL3Ele>& L3Ele,
																		 const Collection<TMBL3Track>& L3Track);

		bool FindMatchDiEleCalOnly_v12(std::string trigName,
																	 Collection<TMBEMCluster>& Ele,
																	 const Collection<TMBL1CalTower>& L1Towers, 
																	 const Collection<TMBL2EM>& L2EM,
																	 const Collection<TMBL3Ele>& L3Ele);
 
		bool FindMatchDiEleTrack_v12(std::string trigName, 
																 Collection<TMBEMCluster>& Ele,
																 const Collection<TMBL1CalTower>& L1Towers,
																 const Collection<TMBL1Track>& L1Track,
																 const Collection<TMBL2EM>& L2EM,
																 const Collection<TMBL3Ele>& L3Ele,
																 const Collection<TMBL3Track>& L3Track);
		
		bool FindMatchEleJet_v12(std::string trigName,Collection<TMBEMCluster>& Ele,
														 const Collection<TMBL1CalTower>& L1Towers, 
														 const Collection<TMBL3Ele>& L3Ele);
		
		bool FindMatchEleMuon_v12(std::string trigName,Collection<TMBEMCluster>& Ele,
															const Collection<TMBL1CalTower>& L1Towers, 
															const Collection<TMBL3Ele>& L3Ele);

		bool FindMatchSingleEleCalOnly_v13(std::string trigName,
																			 Collection<TMBEMCluster>& Ele,
																			 const Collection<TMBL1CalTower>& L1Towers,
																			 const Collection<TMBL2EM>& L2EM,
																			 const Collection<TMBL3Ele>& L3Ele);

		bool FindMatchSingleEleTrack_v13(std::string trigName,
																		 Collection<TMBEMCluster>& Ele,
																		 const Collection<TMBL1CalTower>& L1Towers,
																		 const Collection<TMBL1Track>& L1Track,
																		 const Collection<TMBL2EM>& L2EM,
																		 const Collection<TMBL2Track>& L2Track,
																		 const Collection<TMBL3Ele>& L3Ele,	
																		 const Collection<TMBL3Track>& L3Track);

		bool FindMatchSingleEleIso_v13(std::string trigName,
																	 Collection<TMBEMCluster>& Ele,
																	 const Collection<TMBL1CalTower>& L1Towers,
																	 const Collection<TMBL1Track>& L1Track,
																	 const Collection<TMBL2EM>& L2EM,
																	 const Collection<TMBL2Track>& L2Track,
																	 const Collection<TMBL3Ele>& L3Ele,	
																	 const Collection<TMBL3Track>& L3Track);

		bool FindMatchEleMuon_v13(std::string trigName,
															Collection<TMBEMCluster>& Ele,
															const Collection<TMBL1CalTower>& L1Towers,
															const Collection<TMBL2EM>& L2EM,
															const Collection<TMBL3Ele>& L3Ele);
		

		bool FindMatchEleJet_v13(std::string trigName,
														 Collection<TMBEMCluster>& Ele,
														 const Collection<TMBL1CalTower>& L1Towers,
														 const Collection<TMBL1Track>& L1Track,
														 const Collection<TMBL2EM>& L2EM,
														 const Collection<TMBL2Track>& L2Track,
														 const Collection<TMBL3Ele>& L3Ele);

		bool FindMatchSingleEleCalOnly_v14(std::string trigName,
																			 Collection<TMBEMCluster>& Ele,
																			 const Collection<TMBL1CalTower>& L1Towers,
																			 const Collection<TMBL2EM>& L2EM,
																			 const Collection<TMBL3Ele>& L3Ele);

		bool FindMatchSingleEleTrack_v14(std::string trigName,
																		 Collection<TMBEMCluster>& Ele,
																		 const Collection<TMBL1CalTower>& L1Towers,
																		 const Collection<TMBL1Track>& L1Track,
																		 const Collection<TMBL2EM>& L2EM,
																		 const Collection<TMBL2Track>& L2Track,
																		 const Collection<TMBL3Ele>& L3Ele,	
																		 const Collection<TMBL3Track>& L3Track,
																		 const Collection<TMBL3Isolation>& L3Iso);

		bool FindMatchSingleEleIso_v14(std::string trigName, const int trigVersion,
																	 Collection<TMBEMCluster>& Ele,
																	 const Collection<TMBL1CalTower>& L1Towers,
																	 const Collection<TMBL2EM>& L2EM,
																	 const Collection<TMBL3Isolation>& L3Iso);

		bool FindMatchEleMuon_v14(std::string trigName, const int trigVersion, 
															Collection<TMBEMCluster>& Ele,
															const Collection<TMBL1CalTower>& L1Towers,
															const Collection<TMBL2EM>& L2EM,
															const Collection<TMBL3Ele>& L3Ele,
															const Collection<TMBL3Isolation>& L3Iso);

		bool FindMatchEleJet_v14(std::string trigName, 
														 Collection<TMBEMCluster>& Ele,
														 const Collection<TMBL1CalTower>& L1Towers,
														 const Collection<TMBL1Track>& L1Track,
														 const Collection<TMBL2EM>& L2EM,
														 const Collection<TMBL2Track>& L2Track,
														 const Collection<TMBL3Ele>& L3Ele);

		bool FindMatchSingleEleCalOnly_v15(std::string trigName,
																			 Collection<TMBEMCluster>& Ele,
																			 const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																			 const Collection<TMBL2EM>& L2EM,
																			 const Collection<TMBL3Ele>& L3Ele);

		bool FindMatchSingleEleTrack_v15(std::string trigName,
																		 Collection<TMBEMCluster>& Ele,
																		 const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																		 const Collection<TMBL1Track>& L1Track,
																		 const Collection<TMBL2EM>& L2EM,
																		 const Collection<TMBL2Track>& L2Track,
																		 const Collection<TMBL3Ele>& L3Ele,	
																		 const Collection<TMBL3Track>& L3Track,
																		 const Collection<TMBL3Isolation>& L3Iso);

		bool FindMatchSingleEleIso_v15(std::string trigName,
																	 Collection<TMBEMCluster>& Ele,
																	 const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																	 const Collection<TMBL2EM>& L2EM,
																	 const Collection<TMBL3Ele>& L3Ele,
																	 const Collection<TMBL3Isolation>& L3Iso);

		bool FindMatchEleMuon_v15(std::string trigName, 
															Collection<TMBEMCluster>& Ele,
															const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
															const Collection<TMBL2EM>& L2EM,
															const Collection<TMBL3Ele>& L3Ele,
															const Collection<TMBL3Isolation>& L3Iso);

		bool FindMatchEleJet_v15(std::string trigName, 
														 Collection<TMBEMCluster>& Ele,
														 const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
														 const Collection<TMBL1Track>& L1Track,
														 const Collection<TMBL2EM>& L2EM,
														 const Collection<TMBL2Track>& L2Track,
														 const Collection<TMBL3Ele>& L3Ele,
														 const Collection<TMBL3Track>& L3Track,
														 const Collection<TMBL3Isolation>& L3Iso);

		bool FindMatchEleTau_v15(std::string trigName, 
														 Collection<TMBEMCluster>& Ele,
														 const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
														 const Collection<TMBL1Track>& L1Track,
														 const Collection<TMBL2EM>& L2EM,
														 const Collection<TMBL2Track>& L2Track,
														 const Collection<TMBL3Ele>& L3Ele,
														 const Collection<TMBL3Track>& L3Track,
														 const Collection<TMBL3Isolation>& L3Iso);

		bool FindMatchSingleEleCalOnly_v16(std::string trigName,
																			 Collection<TMBEMCluster>& Ele,
																			 const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																			 const Collection<TMBL2EM>& L2EM,
																			 const Collection<TMBL3Ele>& L3Ele);

		bool FindMatchSingleEleTrack_v16(std::string trigName,
																		 Collection<TMBEMCluster>& Ele,
																		 const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																		 const Collection<TMBL1Track>& L1Track,
																		 const Collection<TMBL2EM>& L2EM,
																		 const Collection<TMBL2Track>& L2Track,
																		 const Collection<TMBL3Ele>& L3Ele,	
																		 const Collection<TMBL3Track>& L3Track,
																		 const Collection<TMBL3Isolation>& L3Iso);

		bool FindMatchSingleEleIso_v16(std::string trigName,
																	 Collection<TMBEMCluster>& Ele,
																	 const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
																	 const Collection<TMBL2EM>& L2EM,
																	 const Collection<TMBL3Ele>& L3Ele,
																	 const Collection<TMBL3Isolation>& L3Iso);
    

		bool FindMatchEleJet_v16(std::string trigName, 
														 Collection<TMBEMCluster>& Ele,
														 const Collection<TMBL1Cal2bEM>& L1Cal2bEMs,
														 const Collection<TMBL1Track>& L1Track,
														 const Collection<TMBL2EM>& L2EM,
														 const Collection<TMBL2Track>& L2Track,
														 const Collection<TMBL3Ele>& L3Ele,
														 const Collection<TMBL3Track>& L3Track,
														 const Collection<TMBL3Isolation>& L3Iso);


    bool FindMatchSingleEleSCJetPt20(std::string trigName, Collection<TMBEMCluster>& Ele,
                                      const Collection<TMBL3Jet>& L3Jet);

    bool FindMatchSingleEleSCJetPt25(std::string trigName, Collection<TMBEMCluster>& Ele,
                                     const Collection<TMBL3Jet>& L3Jet);



    // this is the standard single l1 em tower
    bool PassSingleL1Tower(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			   Collection<TMBL1CalTower> L1Towers) const;

    // this is two pass 2 symmetric towers (for CEM(2,6), for example)
    bool PassTwoL1TowersSym(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			    Collection<TMBL1CalTower> L1Towers) const;

    // this is two pass 2 asymmetric towers (for CEM(2,3)CEM(1,9), for example)
    bool PassTwoL1TowersAsym(float Et_high, float Et_low, 
			     Collection<TMBEMCluster>::const_iterator emit, 
			     Collection<TMBL1CalTower> L1Towers) const;

		// this is the standard single l1 em for RunIIb
		bool PassSingleEML1(float Et, Collection<TMBEMCluster>::const_iterator emit, 
												Collection<TMBL1Cal2bEM> L1EM) const;

		// this is the isolated single l1 em for RunIIb
		bool PassSingleEMisoL1(float Et, Collection<TMBEMCluster>::const_iterator emit, 
													 Collection<TMBL1Cal2bEM> L1EM) const;

		// this is to pass l1 TTK trigger
		bool PassL1TTK(float Pt,
									 Collection<TMBEMCluster>::const_iterator emit, 
									 Collection<TMBL1Track> L1Track) const;

		// this is to pass l1 TIS trigger
		bool PassL1TIS(float Pt,
									 Collection<TMBEMCluster>::const_iterator emit, 
									 Collection<TMBL1Track> L1Track) const;
		
		// this is to pass l1 TEL trigger
		bool PassL1TEL(float Pt,
									 Collection<TMBEMCluster>::const_iterator emit, 
									 Collection<TMBL1Track> L1Track) const;

		// this is to pass l1 TES trigger
		bool PassL1TES(float Pt,
									 Collection<TMBEMCluster>::const_iterator emit, 
									 Collection<TMBL1Track> L1Track) const;
		

    // this is to pass an l2 trigger
    bool PassL2EM(float Et, Collection<TMBEMCluster>::const_iterator emit, 
		  Collection<TMBL2EM> L2EM) const;

		// this is to pass an l2 trigger
    bool PassL2EM(float Et, float Eta, Collection<TMBEMCluster>::const_iterator emit, 
		  Collection<TMBL2EM> L2EM) const;

    // this is to pass an l2 trigger with an emf cut
    bool PassL2EM_emf(float Et, float emf, Collection<TMBEMCluster>::const_iterator emit, 
		      Collection<TMBL2EM> L2EM) const;

		// this is to pass an l2 trigger with an iso cut
    bool PassL2EM_Iso(float Et, float iso, Collection<TMBEMCluster>::const_iterator emit, 
		      Collection<TMBL2EM> L2EM) const;

		// this is to pass an l2 trigger with a likelihood cut
    bool PassL2EM_LH(float Et, float lh, Collection<TMBEMCluster>::const_iterator emit, 
		      Collection<TMBL2EM> L2EM) const;

		// this is to pass an l2 trigger with a likelihood cut
    bool PassL2EM_LHIso(float Et, float lh, float iso, 
												Collection<TMBEMCluster>::const_iterator emit, 
												Collection<TMBL2EM> L2EM) const;

		// This function is for L2 Tracks
		bool PassL2Track(float Pt, std::string tracktype,
										 Collection<TMBEMCluster>::const_iterator emit, 
										 Collection<TMBL2Track> L2Track) const;

    // this is to pass an l3 SHT for v8-11
    bool PassL3Ele_SHT_v811(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			    Collection<TMBL3Ele> L3Ele) const;

    // this is to pass an l3 LOOSE for v8-11
    bool PassL3Ele_LOOSE_v811(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			      Collection<TMBL3Ele> L3Ele) const;

		// this is to pass an l3 VERYLOOSE for v8-11
    bool PassL3Ele_VERYLOOSE_v811(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			      Collection<TMBL3Ele> L3Ele) const;

		
		// this is to pass an l3 NOCUT for v8-11
    bool PassL3Ele_NOCUT_v811(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			      Collection<TMBL3Ele> L3Ele) const;

		// this is to pass an l3 Tracks for v8-11
		bool MatchEMTriggers::PassL3Track_v811(float Pt, int hitsxy, float dca,
																					 Collection<TMBEMCluster>::const_iterator emit, 
																					 Collection<TMBL3Track> L3Track) const;
  		
    // this is to pass an l3 SHT for v12+
    bool PassL3Ele_SHT_v12plus(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			       Collection<TMBL3Ele> L3Ele, float LHood = -1.0) const;

    // this is to pass an l3 SH for v12+
    bool PassL3Ele_SH_v12plus(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			      Collection<TMBL3Ele> L3Ele, float LHood = -1.0) const;

		// this is to pass an l3 L for v12+
		bool PassL3Ele_L_v12plus(float Et, 
														 Collection<TMBEMCluster>::const_iterator emit, 
														 Collection<TMBL3Ele> L3Ele, float LHood = -1.0) const;

		// this is to pass an l3 VL for v12+
		bool PassL3Ele_VL_v12plus(float Et, 
															Collection<TMBEMCluster>::const_iterator emit, 
															Collection<TMBL3Ele> L3Ele) const;
  
		// this is to pass an l3 NC for v12+
		bool PassL3Ele_NC_v12plus(float Et, 
															Collection<TMBEMCluster>::const_iterator emit, 
															Collection<TMBL3Ele> L3Ele) const;

				// this is to pass an l3 T25VL for v12+
		bool PassL3Ele_VL_T25_v12plus(float Et, 
																	Collection<TMBEMCluster>::const_iterator emit, 
																	Collection<TMBL3Ele> L3Ele) const;

		// this is to pass an l3 T15L for v12+
		bool PassL3Ele_L_T15_v12plus(float Et, 
																 Collection<TMBEMCluster>::const_iterator emit, 
																 Collection<TMBL3Ele> L3Ele) const;

		// this is to pass an l3 T13L for v12+
		bool PassL3Ele_L_T13_v12plus(float Et, 
																 Collection<TMBEMCluster>::const_iterator emit, 
																 Collection<TMBL3Ele> L3Ele) const;
		
		// this is to pass an l3 T12L for v12+
		bool PassL3Ele_L_T12_v12plus(float Et, 
																 Collection<TMBEMCluster>::const_iterator emit, 
																 Collection<TMBL3Ele> L3Ele) const;

		// this is to pass an L3 T8L for v12+
		bool PassL3Ele_L_T8_v12plus(float Et, 
																Collection<TMBEMCluster>::const_iterator emit, 
																Collection<TMBL3Ele> L3Ele) const;

		// this is to pass an L3 T4L for v12+
		bool PassL3Ele_L_T4_v12plus(float Et, 
																Collection<TMBEMCluster>::const_iterator emit, 
																Collection<TMBL3Ele> L3Ele) const;

		// this is to pass an L3 T15SH for v12+
		bool PassL3Ele_SH_T15_v12plus(float Et, 
																 Collection<TMBEMCluster>::const_iterator emit, 
																 Collection<TMBL3Ele> L3Ele) const;
		
		bool PassL3Ele_SH_T14_v12plus(float Et, 
																	Collection<TMBEMCluster>::const_iterator emit, 
																	Collection<TMBL3Ele> L3Ele, float LHood = -1.0) const; 	

		// this is to pass an L3 T13SH for v12+
		bool PassL3Ele_SH_T13_v12plus(float Et, 
																 Collection<TMBEMCluster>::const_iterator emit, 
																 Collection<TMBL3Ele> L3Ele) const;

		// this is to pass an L3 T5SH for v12+
		bool PassL3Ele_SH_T5_v12plus(float Et, 
																 Collection<TMBEMCluster>::const_iterator emit, 
																 Collection<TMBL3Ele> L3Ele) const;

		// this is to pass an L3 T13SHT for v12+
		bool PassL3Ele_SHT_T13_v12plus(float Et, 
																	 Collection<TMBEMCluster>::const_iterator emit, 
																	 Collection<TMBL3Ele> L3Ele) const;


		// this is to pass an L3 T7SHT for v12+
		bool PassL3Ele_SHT_T7_v12plus(float Et, 
																	Collection<TMBEMCluster>::const_iterator emit, 
																	Collection<TMBL3Ele> L3Ele) const;

    // this is to pass an L3 IT7SHT for v12+
    bool PassL3Ele_SHT_IT7T_v12plus(float Et,
				    Collection<TMBEMCluster>::const_iterator emit, 
				    Collection<TMBL3Ele> L3Ele) const { return true; }
		
    // this is to pass an L3 IT10SHT for v12+
    bool PassL3Ele_SHT_IT10T_v12plus(float Et, 
				     Collection<TMBEMCluster>::const_iterator emit, 
				     Collection<TMBL3Ele> L3Ele) const;
		
		// this is to pass an L3 ISH for v12+
		bool PassL3Ele_ISH_v12plus(float Et,
															 Collection<TMBEMCluster>::const_iterator emit, 
															 Collection<TMBL3Isolation> L3Iso) const ;

		// this is to pass an L3 ISHT for v12+
		bool PassL3Ele_ISHT_v12plus(float Et,
																Collection<TMBEMCluster>::const_iterator emit, 
																Collection<TMBL3Isolation> L3Iso) const ;

		// this is to pass an L3 RD5 for v12+
		bool PassL3Ele_RD5_v12plus(Collection<TMBEMCluster>::const_iterator emit, 
															 Collection<TMBL3Ele> L3Ele) const ;

		// this is to pass an l3 Tracks for v12plus
		bool 	PassL3Track_v12plus(float Pt, int hitsxy, float dca, 
															Collection<TMBEMCluster>::const_iterator emit, 
															Collection<TMBL3Track> L3Track) const;	

		// this is to pass an l3 Isolated Tracks for v12plus
		bool 	PassL3IsoTrack_v12plus(float Pt, int hitsxy, float dca,
															Collection<TMBEMCluster>::const_iterator emit, 
															Collection<TMBL3Track> L3Track) const;	


                bool  PassL3Ele_SCJet(float Pt, float dR, Collection<TMBEMCluster>::const_iterator emit,
                          Collection<TMBL3Jet> L3Jet) const;


		// does a dielectron event pass L1
		bool DiElectronPassL1(float Et1, float Et2, 
													const Collection<TMBEMCluster>& Ele,
													const Collection<TMBL1CalTower>& L1Towers);

		bool DiElectronPassL1(float Et1, 
													const Collection<TMBEMCluster>& Ele,
													const Collection<TMBL1CalTower>& L1Towers);

		bool DiElectronPassL1(float Et1, std::string tracktype,
													const Collection<TMBEMCluster>& Ele,
													const Collection<TMBL1Track>& L1Track);

		bool DiElectronPassL1(float Pt1, std::string tracktype1,
													float Pt2, std::string tracktype2,
													const Collection<TMBEMCluster>& Ele,
													const Collection<TMBL1Track>& L1Track) ;

		// does a dieletron event pass L2
		bool DiElectronPassL2(float Et1, float Eta1, float Et2, float Eta2,
													const Collection<TMBEMCluster>& Ele,
													const Collection<TMBL2EM>& L2EM) ;

		bool DiElectronPassL2(float Et1, float Eta1,
													const Collection<TMBEMCluster>& Ele,
													const Collection<TMBL2EM>& L2EM) ;


		// does a dielectron event pass L3
		bool DiElectronPassL3_LOOSE_v12plus(float Et1, int Nele,
																				const Collection<TMBEMCluster>& Ele,
																				const Collection<TMBL3Ele>& L3Ele) ;

		bool DiElectronPassL3_SH_v12plus(float Et1, int Nele,
																		 const Collection<TMBEMCluster>& Ele,
																		 const Collection<TMBL3Ele>& L3Ele) ;

		bool DiElectronPassL3_SHT_v12plus(float Et1, int Nele,
																			const Collection<TMBEMCluster>& Ele,
																			const Collection<TMBL3Ele>& L3Ele) ;
		
		bool DiElectronPassL3_L_T8_v12plus(float Et1, int Nele,
																			 const Collection<TMBEMCluster>& Ele,
																			 const Collection<TMBL3Ele>& L3Ele) ;

		bool DiElectronPassL3_SHT_T7_v12plus(float Et1, int Nele,
																				 const Collection<TMBEMCluster>& Ele,
																				 const Collection<TMBL3Ele>& L3Ele) ;

		bool DiElectronPassL3_SH_T5_v12plus(float Et1, int Nele,
																				const Collection<TMBEMCluster>& Ele,
																				const Collection<TMBL3Ele>& L3Ele) ;

		bool DiElectronPassL3_L_T4_v12plus(float Et1, int Nele,
																			 const Collection<TMBEMCluster>& Ele,
																			 const Collection<TMBL3Ele>& L3Ele) ;

		bool DiElectronPassL3_Track_v12plus(float Pt, int hitsxy, float dca, int Nele,
																				const Collection<TMBEMCluster>& Ele, 
																				const Collection<TMBL3Track>& L3Track) ;
		
		

    int _Ninput;
    int _Npassed;
    
    std::set<std::string> _triggerNames;
    cafe::Variables       _trigvars;
    
    //TriggerMap _trigMap; // use the default file location
    std::string _Tag;
    std::string _EMBranch;
    std::string _L1CalTowerBranch;
    std::string _L1Cal2bBranch;
		std::string _L1TrackBranch;
		std::string _L2EMBranch;
		std::string _L2TrackBranch;
    std::string _L3EleBranch;
		std::string _L3TrackBranch;
		std::string _L3IsoBranch;
		std::string _L3JetBranch;

    
    bool _matchV13SHT20;

    double _L1DeltaR;
    double _L2DeltaR;
    double _L3DeltaR;

		bool _DoSingleEleCalOnly;
		bool _DoSingleEleIso;
		bool _DoSingleEleTrack;
		bool _DoDiEleCalOnly;
		bool _DoDiEleIso;
		bool _DoDiEleTrack;
		bool _DoElectronJet;
		bool _DoElectronMuon;
		bool _DoElectronTau;
		
		bool _FoundSingleEleCalOnly;
		bool _FoundSingleEleIso;
		bool _FoundSingleEleTrack;
		bool _FoundDiEleCalOnly;
		bool _FoundDiEleIso;
		bool _FoundDiEleTrack;
		bool _FoundElectronJet;
		bool _FoundElectronMuon;
		bool _FoundElectronTau;

                bool _FoundSingleEleSCJetPt20;
                bool _FoundSingleEleSCJetPt25;

		bool tl57error;
				
		int _Nfailed;
		int _passed_L1;
		int _passed_L2;

                TriggerMap *_runnum_to_triggerversion;

                bool _EffCalc;
                map<TMBEMCluster*, vector<string> > trig_f;
                int _trigVmin;
                int _trigVmax;
  };
  
} // namespace caf_trigger

#endif

