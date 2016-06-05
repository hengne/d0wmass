
#include "cafe/BadLBNs.hpp"

#include <algorithm>
#include <fstream>

#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

namespace cafe {

    BadLBNs::BadLBNs(const char *name)
	: Processor(name),
	  _MC(false)
    {
	Config config(name);
	std::vector<std::string> files = config.getVString("Files", " ,");
	_MC = config.get("MonteCarlo", 0);

	if(_MC) {
	    _vars.add("_overlaylumblk");
	} else {
	    _vars.add("_lumblk");
	}

	for(std::vector<std::string>::iterator it = files.begin();
	    it != files.end();
	    ++it) {
	    out() << "BadLBN[" << name << "]: Adding file: " << *it << std::endl;
	    std::ifstream f((*it).c_str());
	    for(int lbn; f >> lbn; ) {
		_badLBNs.insert(lbn);
	    }
	}
    }
    
    bool BadLBNs::processEvent(cafe::Event& event)
    {
	if(_MC) {
	    // Monte Carlo
	    return _badLBNs.find(event.getMCEventInfo(_vars)->overlaylumblk()) == _badLBNs.end();	    
	} else {
	    // Data
	    return _badLBNs.find(event.getGlobal(_vars)->lumblk()) == _badLBNs.end();
	}
    }

}

ClassImp(cafe::BadLBNs)

