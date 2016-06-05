#ifndef CAF_TRIGGER_TRIGGERSELECTION_HPP__
#define CAF_TRIGGER_TRIGGERSELECTION_HPP__

#include <map>
#include <string>

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "caf_trigger/TriggerMap.hpp"

namespace caf_trigger {

  class TriggerEpoch {
    
    std::string _name ;
    
    // is this epoch is not a  standard cafe DataEpoch, minimum and maximum
    // trigger version need to be specified
    float _trigVerMin ;
    float _trigVerMax ;
    
    // list of triggers name specified for this epoch and fired trigger count
    std::map<std::string, long> _triggers ;

    // object to translate runnum to trigger version
    TriggerMap _runnum_to_triggerversion;

    // number of events processed 
    long _events ;

  public:

    TriggerEpoch(const std::string& proc_name) ;    

    TriggerEpoch(const std::string& proc_name, const std::string& epoch_name) ;    

    virtual ~TriggerEpoch() {}

    std::string name() const {return _name;} 

    bool isEpoch(const cafe::Event& event) const ;

    // return true if triggers in the list and increase counter by one
    bool isInList(const std::string& trig_name)  ;

    std::map<std::string, long>* getMapOfTriggers() { return &_triggers;}

    void increaseNevents() {_events++;}

    void print_efficiencies ( std::ostream & os) const ;
    friend std::ostream & operator << ( std::ostream & os, const TriggerEpoch& epoch );  
    
    ClassDef(TriggerEpoch,0);

  } ;

    /**
     * Select events based on a list of trigger names.
     * uses either TMBTrigger or TMBTrigBits (if no Trigger branch present)
     *
     * Configuration options:

     * _.Triggers: triggerName0 triggerName1....

     * alternative way of specifying trigger
     * - procname.Epochs: RunIIa, RunIIb1 ... (predefined epoch name from cafe::DataEpochs or 
     *  user specified epoch, see below).
     * - procname_RunIIa.Triggers: triggerName0 triggerName1....
     * - procname_RunIIb1.Triggers: triggerName2 triggerName3....
     * One can specify "ANY" keyword to trigger on any trigger name.
     * 
     * User can specify epoch additionally to epochs from cafe::DataEpochs, for this
     * use follwowing configuration
     * procname_EpochName.TrigVerFrom: GlobalTriggerVersionToStartEpochWith (as float number)
     * procname_EpochName.TrigVerUpTo: GlobalTriggerVersionToFinishEpoch (as float number)
     *
     * _.UseTrigBits: true (use TMBTrigBits instead of TMBTrigger), default false
     * _.Required : true (default): select on Triggers), false: veto on Triggers
     * _.Accounting: 0 / 1
     *
     * \ingroup cafe
     */

  class TriggerSelection : public cafe::Processor {
    
    // epochs with triggers list associated to each epoch
    std::vector<TriggerEpoch> _epochs ;
    
    bool _Tracking;
    long _numEvents;
    long _numPassed;
    cafe::Variables  _vars;
    
    bool _useTrigBits;
    bool _required;

  public:

    TriggerSelection(const char *name);
    bool processEvent(cafe::Event& event);
    void finish();

    ClassDef(TriggerSelection,0);

  };

}

#endif // CAF_TRIGGER_TRIGGERSELECTION_HPP__
