#ifndef CAFE_EVENTFLAGS_HPP__
#define CAFE_EVENTFLAGS_HPP__

#include <vector>
#include <string>

#include "cafe/Processor.hpp"
#include "tmb_tree/TMBEventFlags.hpp"

namespace cafe {

    /**
     * Select events based on a list of event flag names.
     *
     * Configuration options: one of
     *
     * - .Any:  flagName1 flagName2...
     * - .All:  flagName1 flagName2...
     * - .Veto: flagName1 flagName2... <- This will not pass an event if it 
     *                                    has at least one of the flags
     *
     * \ingroup cafe
     */
    class EventFlags : public Processor {
    public:
	EventFlags(const char *name);
	bool processEvent(Event& event);
    private:
	bool                              _any;
	std::vector<std::string>          _flagNames;
	std::vector<TMBEventFlags::Flag>  _flagValues;
        bool                              _veto;
        std::vector<std::string>          _vetoflagNames;
        std::vector<TMBEventFlags::Flag>  _vetoflagValues;

    public:
	ClassDef(EventFlags,1);
    };

}

#endif // CAFE_EVENTFLAGS_HPP__
