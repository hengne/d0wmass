// previous Trigger copied over from old cafe package

#include "wmass_util/WmassTrigger.hpp"

#include <algorithm>
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "tmb_tree/TMBTrigger.hpp"
#include "tmb_tree/TMBTrigBits.hpp"

using namespace std;
using namespace cafe;

    WmassTrigger::WmassTrigger(const char *name)
	: Processor(name),
	  _vars("_trgname"),
	  _numEvents(0),
	  _numPassed(0),
	  _stat(0)
    {
	Config config(name);
	vector<string> epochs = config.getVString("Epochs", " ,");

	_Tracking = config.get("Accounting", false);

	if (epochs.size()==0) {
	  _triggers["RunII"] = TriggerByName() ;
	
	  vector<string> temp = config.getVString("Triggers", " ,");
	  for(int i = 0; i < temp.size(); i++) 
	    (_triggers.begin()->second)[temp.at(i)] = 0;

	} else {

	  for(vector<string>::const_iterator it = epochs.begin(); 
	      it != epochs.end(); it++) {
	    
	    _triggers[*it] = TriggerByName() ;
	    map<string,TriggerByName>::iterator mit = _triggers.find(*it) ;
	    Config cfg((string) name + "_" + *it) ;
	    vector<string> temp = cfg.getVString("Triggers", " ,");

	    for(int i = 0; i < temp.size(); i++) 
	      (mit->second)[temp.at(i)] = 0;	    
	  }
	}

	_numEvents = 0;
	_numPassed = 0;


	out() << " Trigger[" << name << "] List of triggers: " << endl ;

	for (map<string, TriggerByName>::const_iterator it = _triggers.begin();
	     it != _triggers.end() ; it++ ) {	  

	  if(it->second.size() == 0) 
	    warn() << "No triggers specified for epoch [" 
		   << it->first << "].  All events will fail." 
		   << endl;
	  
	  out() << endl << it->first << ": " ; 

	  for(map<string, long>::const_iterator tit = it->second.begin() ;
	      tit != it->second.end(); tit++) 
	    out() << tit->first << " "  ;
	  
	  out() << endl;
	}
	out() << endl;

	_useTrigBits=config.get("UseTrigBits",false);
	if(_useTrigBits) out()<<"Will use TMBTrigBits instead of TMBTriggers"<<endl;
	_required=config.get("Required",true);
	if(!_required) out()<<"Will veto on trigger list"<<endl;
    }
	
    bool WmassTrigger::processEvent(Event& event)
    {
	++_numEvents;

	map<string, TriggerByName>::iterator eit = _triggers.begin();
	for (; eit != _triggers.end(); eit++ ) 
	    if (event.isEpoch(eit->first)) break ;
	if (eit == _triggers.end()) return false ;

	_stat = 0;
	event.get("StatPointer", _stat);
	bool trig_found = !_required;
	Collection<TMBTrigger> triggers = event.getTriggers(_vars);
	if(triggers.size()>0 && !_useTrigBits){
	  
	//
	// This is proportional to the number of triggers in the event
	// and about log(numUserTriggers).
	//


	  for(Collection<TMBTrigger>::const_iterator it = triggers.begin(); 
	      it != triggers.end();
	    ++it) {
	    if(eit->second.find((*it).getTrgName()) != eit->second.end()) {
	        trig_found = _required;

		if(_Tracking) {

		    // Find the trigger in the list and increment the counter
			
		    string tmpname = (*it).getTrgName();
		    ++eit->second[tmpname];
		}
	    }
	  }

	}else{
	  const TMBTrigBits* trigbits = event.getTrigBits();
	  if(!trigbits) return false;
	  for(map<string,long>::iterator it = eit->second.begin();
	      it != eit->second.end(); ++it){
	    string tmpname = it->first;
	    if(trigbits->triggerFired(tmpname)){
	      trig_found=_required;
	      if(_Tracking)  ++eit->second[tmpname];
	    }
	  }
	}

	if(trig_found) {
	    ++_numPassed;
	    if(_stat != 0) {
	        _stat->EventSelected(name()); 
	    }
	    return true;
	}

	return false;
    }


    void WmassTrigger::finish() {

        if(_numEvents > 0) {
	    out() << "============================================\n";
	    out() << "  Trigger[" << name() << "] SUMMARY\n\n";
	    out() << "  " << _numEvents << " events processed.\n";
	    out() << "  " << _numPassed << " events passed, pass rate = "
		  << double(_numPassed) / double(_numEvents) * 100.
		  << "%\n\n";
	    if(_Tracking) {
	        out() << "    Individual Trigger Efficencies\n\n";
	     
		for (map<string, TriggerByName>::const_iterator eit = _triggers.begin();
		     eit != _triggers.end() ; eit++ ) {

		  out() << eit->first << ":" << endl ;
		  
		  for(map<string, long>::const_iterator it = eit->second.begin(); 
		      it != eit->second.end(); ++it) {
		    string tmpname = it->first;
		    out() << "    " << tmpname << ": " 
			  << (double(it->second) / _numEvents) * 100.0 
			  << "% (" << it->second << " events)\n";
		  }
		out() << '\n';
		}
	    }	    
	    out() << "============================================" << endl;
	}
    }

ClassImp(WmassTrigger)

