// previous processor Trigger copied over from old cafe packcage

#ifndef WMASSTRIGGER_HPP__
#define WMASSTRIGGER_HPP__

#include <map>
#include <string>

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"
#include "cafe/Stat.hpp"


    /**
     * Select events based on a list of trigger names.
     * uses either TMBTrigger or TMBTrigBits (if no Trigger branch present)
     *
     * Configuration options:

     * - .Triggers: triggerName0 triggerName1....

     * alternative way of specifying trigger
     * - procname.Epochs: RunIIa, RunIIb1 ... (or any other name from cafe::DataEpochs)
     * - procname_RunIIa.Triggers: triggerName0 triggerName1....
     * - procname_RunIIb1.Triggers: triggerName2 triggerName3....

     * _.UseTrigBits: true (use TMBTrigBits instead of TMBTrigger), default false
     * _.Required : true (default): select on Triggers), false: veto on Triggers
     * - .Accounting: 0 / 1
     *
     * \ingroup cafe
     */
    class WmassTrigger : public cafe::Processor {
    public:
	WmassTrigger(const char *name);
	bool processEvent(cafe::Event& event);
	void finish();
    private:
        typedef std::map<std::string, long> TriggerByName ;
      
        // epochs name, list of triggers name and number of fired events
        std::map<std::string, TriggerByName>  _triggers ;
	bool _Tracking;
	long _numEvents;
        long _numPassed;
        cafe::Stat *_stat;
	cafe::Variables       _vars;

        bool _useTrigBits;
        bool _required;
    public:
	ClassDef(WmassTrigger,0);
    };


#endif // WMASS_TRIGGER_HPP__
