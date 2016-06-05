
#include "cafe/EventFlags.hpp"

#include <algorithm>
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "tmb_tree/TMBEventFlags.hpp"


namespace cafe {

    EventFlags::EventFlags(const char *name)
	: Processor(name),
	  _any(true),_veto(false)
    {
	using namespace std;

	Config config(name);
	_flagNames = config.getVString("Any", " ,");
	if(_flagNames.size() == 0) {
	    _flagNames = config.getVString("All", " ,");
	    _any = false;
	}
        _vetoflagNames = config.getVString("Veto", " ,");
        if(_vetoflagNames.size() != 0)
            _veto = true;        

	out() << "EventFlags[" << name << "] Flags = "
	      << (_any ? " Any of :" : "All of :" );
	for(vector<string>::iterator it = _flagNames.begin();
	    it != _flagNames.end(); ++it) {
	    out() << *it << ' ';
	}
	out() << endl;

        if(_veto){
          out() << "EventFlags[" << name << "] Flags = "
                << " Veto of :";
          for(vector<string>::iterator it = _vetoflagNames.begin();
              it != _vetoflagNames.end(); ++it) {
              out() << *it << ' ';
          }
          out() << endl;
        }   

	TMBEventFlags f;
	for(vector<string>::iterator it = _flagNames.begin();
	    it != _flagNames.end(); ++it) {
	    TMBEventFlags::Flag flag = f.GetFlagValue((*it).c_str());
	    if (flag == (TMBEventFlags::Flag )128) {
		out() << name << " : Unknown flag name: " << *it << endl;
	    } else {
		_flagValues.push_back(flag);
	    }
	}
       // Do the same with a list of Veto-ed flags
       for(vector<string>::iterator it = _vetoflagNames.begin();
            it != _vetoflagNames.end(); ++it) {
            TMBEventFlags::Flag flag = f.GetFlagValue((*it).c_str());
            if (flag == (TMBEventFlags::Flag )128) {
                out() << name << " : Unknown flag name: " << *it << endl;
            } else {
                _vetoflagValues.push_back(flag);
            }
        }
    }
	
    bool EventFlags::processEvent(Event& event) 
    {
	using namespace std;

	if(const TMBEventFlags *flags = event.getEventFlags()) {
           if(_veto)
                 for(vector<TMBEventFlags::Flag>::iterator it = _vetoflagValues.begin();
                     it != _vetoflagValues.end();
                     ++it)
                     if(flags->HasFlag(*it)) return false;

	    if(_any) {
		for(vector<TMBEventFlags::Flag>::iterator it = _flagValues.begin();
		    it != _flagValues.end();
		    ++it) {
		    if(flags->HasFlag(*it)) {
			return true;
		    }
		}
		return false;
	    } else {
		for(vector<TMBEventFlags::Flag>::iterator it = _flagValues.begin();
		    it != _flagValues.end();
		    ++it) {
		    if(!flags->HasFlag(*it)) {
			return false;
		    }
		}
		return true;
	    }
	}

	return false;

    }

}

ClassImp(cafe::EventFlags)

