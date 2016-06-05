/* File EMTriggerMatch.hpp
 *
 * Created       : Sat Jul 15 14:21:22 CDT 2006
 * Author        : jmitrevs
 *
 * Purpose       : This processor passes events if any electron given
 *                 to it fires the elctron part of any trigger given
 *                 to it. Only triggers that actually fired are considered.
 *                 (Checking whether the trigger fired is copied from
 *                 cafe/Trigger.{hpp|cpp}, matching code is modeled after
 *                 caf_trigger/MatchL1CalTowerReco.{hpp|cpp} and similar
 *                 for L2 and L3, and after em_cert.)
 *
 * Last modified : 
 * Comments      : 
 */



#ifndef EMTriggerMatch_HPP_
#define EMTriggerMatch_HPP_

#include <set>
#include <string>

#include "cafe/Processor.hpp"
#include "cafe/Event.hpp"

#include "caf_trigger/TriggerMap.hpp"

using namespace cafe;

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

    - .EMBranch: string
      The electrons to consider for matching. Returns true if ANY match, not
      necessarily ALL. (Should be able to modify easily and provide and
      ALL mode if that's wanted.)

    - .L1CalTowerBranch: string [default L1CalEMTowers]
      The L1 cal towers for matching.

    - .L2EMBranch: string [default L2EM]
      The L2 EM for matching.

    - .L3EleBranch: string [default L3Electron]
      The L3 electrons for matching.

    - .MatchV13SHT20: bool [default true]
      In v13 before v13.20, there were SHT20 triggers in addition to SHT22
      triggers, though they were prescaled. If one indicates Ex_SHT20
      in the .Triggers option, should it match any SHT20 triggers (true)
      or just v12 (false)?

    - .L1DeltaR: double [default: 0.4]
    - .L2DeltaR: double [default: 0.4]
    - .L3DeltaR: double [default: 0.4]
      The maximum distance between the electron and the trigger object to 
      consider it a match.

    \authors Jovan Mitrevski (jmitrevs@fnal.gov)

  */


  
  class EMTriggerMatch : public cafe::Processor {
	/**
	   this is a Template to build a new processor in package "top_cafe"
	 */    
  public:
    
    // Constructor, destructor: 
    EMTriggerMatch(const char *name);
    ~EMTriggerMatch();
    
    void begin();
    bool processEvent(cafe::Event& event);
    void finish();
    void inputFileOpened(TFile *file);
    void inputFileClosing(TFile *file);
    
    ClassDef(EMTriggerMatch, 0);
    
  private:
  
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

    // this is to pass an l2 trigger
    bool PassL2EM(float Et, Collection<TMBEMCluster>::const_iterator emit, 
		  Collection<TMBL2EM> L2EM) const;

    // this is to pass an l2 trigger with an emf cut
    bool PassL2EM_emf(float Et, float emf, Collection<TMBEMCluster>::const_iterator emit, 
		      Collection<TMBL2EM> L2EM) const;

    // this is to pass an l3 SHT for v8-11
    bool PassL3Ele_SHT_v811(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			    Collection<TMBL3Ele> L3Ele) const;

    // this is to pass an l3 LOOSE for v8-11
    bool PassL3Ele_LOOSE_v811(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			      Collection<TMBL3Ele> L3Ele) const;

    // this is to pass an l3 SHT for v12+
    bool PassL3Ele_SHT_v12plus(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			       Collection<TMBL3Ele> L3Ele) const;

    // this is to pass an l3 SH for v12+
    bool PassL3Ele_SH_v12plus(float Et, Collection<TMBEMCluster>::const_iterator emit, 
			      Collection<TMBL3Ele> L3Ele) const;
  
    int _Ninput;
    int _Npassed;
    
    std::set<std::string> _triggerNames;
    cafe::Variables       _trigvars;
    
    TriggerMap _trigMap; // use the default file location

    std::string _EMBranch;
    std::string _L1CalTowerBranch;
    std::string _L2EMBranch;
    std::string _L3EleBranch;
    
    bool _matchV13SHT20;

    double _L1DeltaR;
    double _L2DeltaR;
    double _L3DeltaR;

  };
  
} // namespace caf_trigger

#endif

