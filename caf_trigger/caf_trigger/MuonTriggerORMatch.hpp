#ifndef MuonTriggerORMatch_h
#define MuonTriggerORMatch_h

// cafe
#include "cafe/Processor.hpp"
#include "cafe/Event.hpp"
#include "caf_trigger/MuonTriggerMatch.hpp"
#include "caf_trigger/TriggerMap.hpp"

// root
#include "TTree.h"

// stl
#include <string>
#include <vector>
#include <list>

using namespace std ;

namespace caf_trigger {

  namespace MuonTriggerORMatch_Tree {

    /// \brief Contains information about the offline muons
    /// (the 7 first muons in the input branch)
    struct Offline_struct {
      Float_t mupt[7] ;
      Float_t mudeteta[7] ;
      Float_t muphi[7] ;
      Float_t muz[7] ;
    } ;

    /// Contains global information about the event (run number, ...)
    struct Global_struct {
      Int_t evtno ;
      Int_t runno ;
      Float_t trigvers ;
    } ;

    /// \brief Contains two variables:
    /// - ORMatched: set to 1 if at least one of the triggers fulfilled the 
    /// matching requirement, 0 otherwise
    /// - ORFired: set to 1 if at least one of the triggers did fire, 0
    /// otherwise
    struct OR_struct {
      UChar_t ORMatched ;
      UChar_t ORFired ;    
    } ;

  }

  using namespace MuonTriggerORMatch_Tree ;

  /**
     \brief
     A class to test the offline-online matching of a list of single muon 
     triggers. The method processEvent returns true if and only if at least 
     one trigger is matched to an offline muon. The option UseTriggerFire 
     requires in addition that any matched trigger did actually fire.

     This class instanciate caf_trigger::MuonTriggerMatch objects to perform
     the matching tests. The required trigger term definitions are declared 
     in a configuration file which is read by each instance of 
     caf_trigger::MuonTriggerMatch.

     To study (or debug) the effiency of the matching, an output tree can be
     written with the result of the test of each trigger and and trigger terms.
     This tree also contains the TriggerFire bits.

     ex.: to get the efficiency of the matching of the term L3L15 (muo_cert 
     notation), given that MUH1_LM15 did fire, and in function of the trigger 
     list version, proceed as follows (in root):

     <code>
     output_tree_name->Draw( "TermMatched.l3l15:trigvers",
                             "TrigFired.MUH1_LM15",
                             "prof" )
     </code>

     <B>Required configuration:</B>
     - muonBranch: input muon branch.
     - ListOfTriggers: list of triggers that have to be tested.

     <B>Options:</B>
     - UseTriggerFire: if this option is turned on, the method processEvent 
     returns true if and only if at least one trigger which fired is matched 
     to an offline muon. [default: true]
     - ExcludeBadRunRange: if this option is turned on, the matching test of
     a given trigger will always fail if it the current trigger version is out
     of the trigger's epoch. This option has been introduced for backward 
     compatibility with MuonTriggerMatch(), which systematically assumed the 
     success of the matching in such cases. This option should always be set 
     to true and is forced to be true if "UseTriggerFire" is set to false.
     [default: true]
     - TreeName: Optional output tree name. An empty string as tree name 
     switches off this feature. The tree is copied in the file pointed by 
     cafe.Ouput. [default: ""]
     - Tag: if tag is an empty string, the processor will select events. If 
     tag is an non empty string, the processor will not select events but tag 
     them with event.put(). [default: false]
     - Summary: print the summary output for each called MuonTriggerMatch 
     object. [default: false]
     - Debug: switch on/off the debug option. [default: false]

     \author Philippe Calfayan, <calfayan@fnal.gov>
  */

  class MuonTriggerORMatch : public cafe::Processor {

  private:
	  
    /// Instance name
    string _instance_name ;
  
    /// Counters
    unsigned int _processed_events ;    
    unsigned int _nevents_with_at_least_one_matched_trig ;
    unsigned int _nevents_where_at_least_one_trig_fired ;
    unsigned int _nevents_in_the_range ;

    /// Input muon branch
    string _muonBranch ;

    /// Input reco version
    string _RecoVer;
  
    /// Tag string
    string _tag ;

    /// Vector of triggers to test
    /// Given trigger names may differ from the official names but must
    /// contain an official name to test the triggerfire bit.
    vector<string> _input_triggers ;

    /// Container for TrigMatched branches
    Bool_t* _TrigMatched_tab ; 

    /// Container for TrigFired branches
    Bool_t* _TrigFired_tab ; 

    /// Container for TermMatched branches
    Bool_t* _TermMatched_tab ; 

    /// Map of term test results
    map<string, bool> _terms_map ;

    /// List of MuonTriggerMatch objects (one for each input trigger)
    list<MuonTriggerMatch> _MuonTriggerMatch_list ;

    /// Ouput tree name (optional)
    string _output_tree_name ;

    /// Switch on/off the summary output of each called 
    /// MuonTriggerMatch object
    bool _MuonTriggerMatch_summary_ouput ;

    /// Ouput TTree
    TTree* _results_tree ;

    /// Branch containing the OR of the _TrigMatched_branch elements,
    /// and the OR of the _TrigFired_branch elements (in output tree)
    OR_struct _OR_branch ;

    /// Branch containing information about the offline tested muon
    Offline_struct _Offline_branch ;

    /// Branch containing global event information, like the run number, etc...
    /// (in output tree)
    Global_struct _Global_branch ;

    /// UseTriggerFire option
    bool _use_trigger_fired ;
    
    bool _use_run_range;
    std::vector<float> _applied_trigger_version;

    /// ExcludeBadRunRange option
    bool _exclude_bad_run_range ;

    /// TriggerMap object: allows to get the trigger version
    TriggerMap* _runnum_to_triggerversion ;

  public:

    /// \brief Constructor of the class MuonTriggerORMatch. A MuonTriggerMatch
    /// object is instanciated for each triggers of the list given as input.
    MuonTriggerORMatch(const char* name) ;

    /// This method manages the optionnal ouput tree
    void begin() ;

    /// \brief This method is called for each event and returns true if at 
    /// least one of the given triggers can be matched by a reconstructed muon
    bool processEvent(cafe::Event& event) ;

    /// Write optional output information
    void finish() ;

    ClassDef(MuonTriggerORMatch, 0) ;

  };

}

#endif
