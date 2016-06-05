#include "cafe/OR.hpp"
#include "cafe/ParseRun.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"

#include "TFile.h"
#include "TTreeFormula.h"

#include <iostream>
#include <vector>

namespace cafe {

    OR::OR(const char *name) : Controller(name) {
    }
  // Processor interface
  bool OR::processEvent(Event& event) {
    event.untag(_untag.begin(), _untag.end());
    event.tag(_tag.begin(), _tag.end());
    
    if (_processors.size()==0) return true ;
    for(std::list<Processor*>::iterator it = _processors.begin();
	it != _processors.end(); it++) {
      (*it)->incEventCount();
      if ((*it)->processEvent(event))  return true ;
    }

    return false ;
  }
}

ClassImp(cafe::OR);

