
#include "cafe/RemoveObjects.hpp"

#include "cafe/Config.hpp"
#include "cafe/Event.hpp"

#include "TCollection.h"
#include "TObjArray.h"
#include "TClonesArray.h"

namespace cafe {

    RemoveObjects::RemoveObjects(const char *name)
	: cafe::Processor(name)
    {
	using namespace cafe;
	
	Config config(name);

	_branch = config.get("Branch", "");
	_list = config.getVString("Keep", " ,");
    }

    bool RemoveObjects::processEvent(cafe::Event& event)
    {
	using namespace cafe;
	using namespace std;

	vector<TObjArray*> vars;

	for(vector<string>::const_iterator it = _list.begin();
	    it != _list.end();
	    ++it) {
	    TObjArray *ptr = 0;
	    if(event.get(*it, ptr) && ptr != 0) {
		vars.push_back(ptr);
	    } else {
		err() << "RemoveObjects[" << name() << "]: No such list:" << *it << endl;
	    }
	}

	if(TClonesArray *objects = const_cast<TClonesArray*>(event.getClonesArray(_branch))) {

	    unsigned int initial = objects->GetLast() + 1;
	    unsigned int count = 0;

	    // need non-const object since we modify it...
	    TIter iter(objects);
	    while(TObject *obj = iter.Next()) {
		bool remove = true;

		for(vector<TObjArray*>::const_iterator it = vars.begin();
		    it != vars.end();
		    ++it) {
		    if((*it)->FindObject(obj) != 0) {
			remove = false;
			break;
		    }
		}

		if(remove) {
		    count++;
		    objects->Remove(obj);
		}
	    }

	    objects->Compress();

	} else {
	    err() << "RemoveObjects[" << name() << "]: No such branch: " << _branch << endl;
	}

	return true;
    }

}

ClassImp(cafe::RemoveObjects);


