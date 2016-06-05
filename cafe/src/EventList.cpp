
#include "cafe/EventList.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include "TSystem.h"
#include "TFile.h"
#include "TEventList.h"

namespace cafe {

    EventList::EventList(const char *name)
	: Processor(name),
	  _list(0),
	  _file(0)
    {
	Config config(name);
	
	std::string filename = config.get("File", "");
	_tags = config.getVString("Tags"," ,");

	if(filename != "") {
	    _file = new TFile(filename.c_str(), "RECREATE");
	    out() << "EventList[" << name << "] : Created event list file: " << filename << std::endl;
	}

    }

    EventList::~EventList()
    {
    }

    void EventList::inputFileOpened(TFile *file)
    {
	if(_file) {
	    _file->cd();
	    _list = new TEventList((std::string("EVTS-") + gSystem->BaseName(file->GetName())).c_str(), file->GetName());
	}
    }

    void EventList::inputFileClosing(TFile *file)
    {
	if(_file) {
	    _file->cd();
	    _list->Write();
	    delete _list; // ??
	    _list = 0;
	}
    }

    bool EventList::processEvent(cafe::Event& event)
    {
	if(_list && (_tags.empty() || event.hasTag(_tags))) {
	    _list->Enter(event.getTree()->GetReadEntry());
	}
	return true;
    }

    void EventList::finish()
    {
	if(_file) {
	    // _file->Write();
	    _file->Close();
	    delete _file;
	}
    }
}

ClassImp(cafe::EventList);

