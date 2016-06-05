

#include "cafe/Fork.hpp"
#include "cafe/ParseRun.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"

namespace cafe {

    Fork::Fork(const char *name) 
        : Controller(name)
    {
    }

    // Processor interface
    bool Fork::processEvent(Event& event)
    {
        for(std::list<Processor*>::iterator it = _processors.begin();
            it != _processors.end();
            ++it) {
	    event.untag(_untag.begin(), _untag.end());
	    event.tag(_tag.begin(), _tag.end());
            (*it)->incEventCount();
            (*it)->processEvent(event) ;
        }
        return true;
    }
}

ClassImp(cafe::Fork);

