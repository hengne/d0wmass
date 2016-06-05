#include "cafe/IfPr.hpp"
#include "cafe/ParseRun.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"

#include "TFile.h"
#include "TTreeFormula.h"

#include <iostream>
#include <vector>

namespace cafe {

    IfPr::IfPr(const char *name) 
      : Controller(name, std::list<Processor*>())
    {
	using namespace std;

        Config config(name);

	// Get select/then/else branches
	ParseRun parser;
	string pelse =  config.get("Else", "") ;
	add(new Controller((string(name) + "_Select").c_str(), parser.parse(config.get("Select", ""))));
	add(new Controller((string(name) + "_Then").c_str(), parser.parse(config.get("Then", ""))));
	if (!pelse.empty()) 
	  add(new Controller((string(name) + "_Else").c_str(), parser.parse(pelse))); 

	// Be nice and tell user if he specified the .Run: entry
	if(config.get("Run","") != "") {
	    err() << "IfPr[" << name << "]: .Run not used in IfPr[]. .Use 'Then:' and '.Else:' instead" << endl;
	}

	_untag = config.getVString("Untag", " ,");
	_tag = config.getVString("Tag", " ,");
    }

    IfPr::~IfPr() {}


    // Processor interface
    bool IfPr::processEvent(Event& event)
    {
        event.untag(_untag.begin(), _untag.end());
        event.tag(_tag.begin(), _tag.end());

        if(_processors.size() == 0) return true ;
	std::list<Processor*>::iterator it = _processors.begin();
	// call first subprocessor
	
	(*it)->incEventCount();
	if ((*it)->processEvent(event)) {	    
	  // call second subprocessor(than)
	  ++it;
	  (*it)->incEventCount();
	  return (*it)->processEvent(event) ;
	}		  
	  // call any other subprocessor, abort if
	  // any of them returns false.
	  ++it;
	  ++it;
	  while(it != _processors.end()) {
	    (*it)->incEventCount();
	    if(!(*it)->processEvent(event)) return false;
	    ++it;
	  }
	
	return true;
    }
}

ClassImp(cafe::IfPr);

