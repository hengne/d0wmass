
#include "cafe/EventListExpander.hpp"

#include <stdexcept>

#include "TFile.h"
#include "TKey.h"
#include "TList.h"
#include "TEventList.h"

namespace cafe {

    EventListExpander::EventListExpander(const char *url)
	: Expander()
    {
	const char *ptr = strchr(url, ':') + 1;
	TFile file(ptr, "READ");
	if(!file.IsZombie()) {
	    if(TList *keys = file.GetListOfKeys()) {
		TIter iter(keys);
		while(TKey *k = (TKey *)iter.Next()) {
		    if(strcmp(k->GetClassName(), "TEventList") == 0) {
			if(TEventList *ev_list = dynamic_cast<TEventList*>(file.Get(k->GetName()))) {
			    _files.push_back(ev_list->GetTitle());
			}
		    }
		}
	    }
	} else {
	    throw std::runtime_error("EventListExpander: cannot open file: " + std::string(url));
	}
    }

    std::string EventListExpander::nextFile()
    {
	if(_files.empty()) return "";
	std::string result = _files.front();
	_files.pop_front();
	return result;
    }
}

ClassImp(cafe::EventListExpander);
