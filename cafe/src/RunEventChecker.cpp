///
/// RunEventChecker.cpp
///
///  Utility to check on the event number and notice when it changes.
///
#include "cafe/RunEventChecker.hpp"
#include "cafe/Event.hpp"

#include "tmb_tree/TMBGlobal.hpp"

ClassImp(cafe::RunEventChecker);

namespace cafe {
    
    ///
    /// isNewEvent
    ///
    ///  Check current event # against cached one. If there is a change,
    /// return true, otherwise false. Update the cached values.
    ///
    bool RunEventChecker::isNewEvent (cafe::Event &reader)
    {
	const TMBGlobal *g = reader.getGlobal();
	bool result = false;
	if (_run != g->runno() || _event != g->evtno()) {
	    result = true;
	    _run = g->runno();
	    _event = g->evtno();
	}
	
	return result;
    }
}
