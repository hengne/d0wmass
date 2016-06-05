#include "caf_trigger/TriggerSelection.hpp"

#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Stat.hpp"

#include "tmb_tree/TMBTrigger.hpp"
#include "tmb_tree/TMBTrigBits.hpp"

#include <stdexcept> 
#include <sstream> 
#include <algorithm>

using namespace std;
using namespace cafe ;

namespace caf_trigger {

    TriggerSelection::TriggerSelection(const char *name)
	: Processor(name),
	  _vars("_trgname"),
	  _numEvents(0),
	  _numPassed(0)
    {
	Config config(name);

	// different trigger list could be specified for each epoch
	// epoch could be the predefine name (see cafe::DataEpochs) 
	// or epoch specified with trigger versions
	vector<string> epochs = config.getVString("Epochs", " ,");

	_Tracking = config.get("Accounting", false);

	if (epochs.size()==0) _epochs.push_back(TriggerEpoch(name)) ;
	else {

	  // create epochs, and verify that there is no duplicated epoch names

	  for(vector<string>::const_iterator it = epochs.begin(); 
	      it != epochs.end(); it++) {

	    vector<TriggerEpoch>::const_iterator jt = _epochs.begin(); 
	    for( ; jt != _epochs.end(); jt++) 	      
	      if (jt->name() == *it)
		throw runtime_error("caf_trigger::TriggerSelection [" + (string) name +  
                        "] ERROR: duplicated epoch  name [" + *it + "]") ;
	    
	    _epochs.push_back(TriggerEpoch(name, *it)) ;
	  }
	}

	_numEvents = 0;
	_numPassed = 0;


	out() << "============================================================================="  << endl ;
	out() << "caf_trigger::TriggerSelection  processor [" << name << "] List of triggers: " << endl << endl ;
	for(vector<TriggerEpoch>::const_iterator jt = _epochs.begin() ; jt != _epochs.end(); jt++)
	  out() << *jt << endl ;	
	out() << "============================================================================="  << endl ;
	
	_useTrigBits=config.get("UseTrigBits",false);
	if(_useTrigBits) out()<<"Will use TMBTrigBits instead of TMBTriggers"<<endl;
	_required=config.get("Required",true);
	if(!_required) out()<<"Will veto on trigger list"<<endl;
    }
  
    bool TriggerSelection::processEvent(Event& event)
    {
	++_numEvents;

	vector<TriggerEpoch>::iterator epoch = _epochs.end() ;
	for(vector<TriggerEpoch>::iterator jt = _epochs.begin() ; jt != _epochs.end(); jt++) {
	  if (jt->isEpoch(event)) {
	    if (epoch != _epochs.end()) 
	      throw runtime_error ("caf_trigger::TriggerSelection [" + name() +  
                        "] ERROR: event belong to two epoch [" + 
				   jt->name() + "] and [" + epoch->name() + "]." + 
				   " No overlaping epoch allows." ) ;
	    epoch = jt ; 
	  }
	}
	
	if (epoch == _epochs.end()) {
	  ostringstream s ;
	  s << "caf_trigger::TriggerSelection  [" + name() +   
                        "] ERROR: can't find epoch for the current event with run number " 
	    <<  event.getGlobal()->runno() ;
	  throw runtime_error (s.str()) ;
	}

	// increase number of events processed
	epoch->increaseNevents() ;

	StatPointer stat ;
	event.get("StatPointer", stat) ;

	bool trig_found = !_required;
	Collection<TMBTrigger> triggers = event.getTriggers(_vars);
	
	if(triggers.size()>0 && !_useTrigBits){


	  for(Collection<TMBTrigger>::const_iterator it = triggers.begin(); 
	      it != triggers.end(); ++it) {
	    
	    if(epoch->isInList(it->getTrgName())) {
	      trig_found = _required;
	      
	      // if _Tracking required, will run over all trigger in the list and increase 
	      // number of times when trigger fired. 
	      // If not, only the first fired trigger is detected.
	      if(!_Tracking) break ;
	    }
	  }
	}else{
	  const TMBTrigBits* trigbits = event.getTrigBits();
	  if(!trigbits) return false ;

	  map<string,long>* triggers = epoch->getMapOfTriggers() ;

	  for(map<string,long>::iterator it = triggers->begin(); it != triggers->end(); it++){

	    // if any trigger allow, doesn't make a verification
	    if (it->first == "ANY") break ;

	    if(trigbits->triggerFired(it->first)){
	      trig_found=_required;
	      it->second++ ; 
	      if(!_Tracking)  break ;
	    }
	  }
	}

	if(!trig_found) return false ;
	
	++_numPassed;
	stat.EventSelected(name()); 
	return true;
    }


    void TriggerSelection::finish() {

        if(_numEvents > 0) {
	    out() << "============================================\n";
	    out() << "  TriggerSelection [" << name() << "] SUMMARY\n\n";
	    out() << "  " << _numEvents << " events processed.\n";
	    out() << "  " << _numPassed << " events passed, pass rate = "
		  << double(_numPassed) / double(_numEvents) * 100.
		  << "%\n\n";
	    if(_Tracking) {
	        out() << ">>> Individual Trigger Efficencies <<< \n\n";	     
		for(vector<TriggerEpoch>::const_iterator jt = _epochs.begin() ; jt != _epochs.end(); jt++) 
		  jt->print_efficiencies(out()) ;
	    }
	    out() << "============================================" << endl;
	}
    }

  TriggerEpoch::TriggerEpoch(const std::string& proc_name) : 
    _name("RunII"), _trigVerMin(-1.0), _trigVerMax(-1.0),  _events(0) {
    
    Config config(proc_name);	
    vector<string> temp = config.getVString("Triggers", " ,");
    

    // add trigger  name, verify duplicated names, create trigger counter
    for(vector<string>::const_iterator it = temp.begin(); it != temp.end() ; it++) {
      map<string, long>::iterator jt = _triggers.begin() ;
      for(; jt != _triggers.end(); jt++) 
	if (jt->first == *it) 
	  throw runtime_error("cafe::Trigger  [" + name() +   
                        "] ERROR: duplicated trigger name [" + *it + "]") ;
      _triggers[*it] = 0 ;
    }
  }
  
  TriggerEpoch::TriggerEpoch(const std::string& proc_name, const std::string& epoch_name) : 
    _name(epoch_name), _events(0) {
    
    DataEpochs cafeEpochs ;

    Config cfg(proc_name + "_" + epoch_name) ;
     _trigVerMin = cfg.get("TrigVerFrom", -1.0) ;
     _trigVerMax = cfg.get("TrigVerUpTo", -1.0) ;
    
    if ( !cafeEpochs.epochExist(epoch_name) ) {

      if (_trigVerMin <= 0 || _trigVerMax <= 0)
	throw runtime_error ("cafe::Trigger  [" + proc_name +   
                        "] ERROR: epoch name [" + epoch_name + "] is not a standard epoch " + 
			     "name in cafe. Specify TrigVerFrom and TrigVerUpTo." ) ; 

    } else if (_trigVerMin > 0 || _trigVerMax > 0) 
      throw runtime_error ("caf_trigger::TriggerSelection  [" + proc_name +    
                        "] ERROR: epoch name [" + epoch_name + "] is a standard epoch name " +
			   " in cafe. TrigVerFrom and TrigVerUpTo can't be specified." ) ; 
	    
    vector<string> temp = cfg.getVString("Triggers", " ,");

    if (temp.size() ==0 )
      throw runtime_error("caf_trigger::TriggerSelection [" + proc_name + 
			  "] ERROR: No triggers specified for epoch [" 
			  + epoch_name + "].  Please, remove this epoch as unneeded. "
			  " If you want to allow any trigger for this epoch, please specify ANY "+
			  "keyword as trigger") ; 
    

    // add trigger  name, verify duplicated names, create trigger counter

    for(vector<string>::const_iterator it = temp.begin(); it != temp.end() ; it++) {
      map<string, long>::iterator jt = _triggers.begin() ;
      for(; jt != _triggers.end(); jt++) 
	if (jt->first == *it) 
	  throw runtime_error("caf_trigger::TriggerSelection [" + proc_name +  
			      "] ERROR: duplicated trigger name [" + *it + "]") ;
      _triggers[*it] = 0 ;
    }
  }

  bool TriggerEpoch::isEpoch(const cafe::Event& event) const {

    if (_trigVerMin <= 0) return event.isEpoch(_name) ;
    
    float trigVer = _runnum_to_triggerversion.TriggerVersion(event.getGlobal()->runno());
    
    if ( trigVer >= _trigVerMin && trigVer <= _trigVerMax) return true ;

    return false ;
  }
  
  void TriggerEpoch::print_efficiencies ( ostream & os) const {

    if (_events==0) return ;

    os.precision(3) ;
    os << name()  << " ";
    if (_trigVerMin>0) 
      os << " (v" << _trigVerMin << " -- v" << _trigVerMax << ") ";   
    os << _events << " events processed:" << endl ;   

    for(map<string, long>::const_iterator tit = _triggers.begin() ; tit != _triggers.end(); tit++) {
      float eff = ((float) tit->second) / _events ;
      os  << tit->first << " efficiency " << 100.0*eff << " +- " 
	  << 100.0*sqrt(eff*(1.0-eff)/_events) << "%" << endl ;  
    }
    os << endl;
  }

  ostream & operator << ( ostream & os, const TriggerEpoch& epoch ) {

    os << epoch.name()  ;
    if (epoch._trigVerMin>0) 
      os << " (v" << epoch._trigVerMin << " -- v" << epoch._trigVerMax << ")";   
    os << ": " ;   

    for(map<string, long>::const_iterator tit = epoch._triggers.begin() ; 
	tit != epoch._triggers.end(); tit++) 
    os  << tit->first << " "  ;  
    return os ;
  }

  // return true if triggers in the list and increase counter by one
  bool TriggerEpoch::isInList(const string& trig_name) {
    for (map<string, long>::iterator it = _triggers.begin(); it != _triggers.end(); it++) {

      if (it->first == "ANY") return true ;
      
      if (it->first == trig_name) { 
	it->second++ ; 
	return true ;
      }
    }
    return false ;

  }


}
ClassImp(caf_trigger::TriggerSelection)
ClassImp(caf_trigger::TriggerEpoch)
