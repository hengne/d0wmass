#ifndef CAFE_EVENTLIST_HPP_
#define CAFE_EVENTLIST_HPP_

#include "cafe/Processor.hpp"

#include <string>
#include <vector>

class TEventList;
class TFile;

namespace cafe {
    /**
     * Create event list. Save index for current event
     * in a TEventList. Events can be selected from this
     * list by specifying the 'cafe.EventList: filename' 
     * option.
     *
     *
     * Configuration 
     *
     *   .File: EventListFile [ default: "" ]
     *   .Tags: EventTags*    [ default: "", i.e. all events ]
     */
    class EventList : public cafe::Processor {
    public:
	EventList(const char *name);
	~EventList();
	void inputFileOpened(TFile *file);
	void inputFileClosing(TFile *file);
	bool processEvent(cafe::Event& event);
	void finish();
    private:
	std::vector<std::string> _tags;
	TEventList  *_list;
	TFile       *_file;
    public:
	ClassDef(EventList, 0);
    };
}

#endif // CAFE_EVENTLIST_HPP_
