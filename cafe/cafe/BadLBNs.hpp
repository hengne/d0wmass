#ifndef CAFE_BADLBNS_HPP__
#define CAFE_BADLBNS_HPP__

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include <set>

namespace cafe {

    class Event;

    /**
     * Reject events for bad LBNS.
     *
     * If the .MonteCarlo flag is set to 1, the rejection
     * is based on the luminosity block of the overlaid ZB 
     * event.
     *
     * Configuration options:
     * - .Files: ListOfBadLBNFiles [ default: ""]
     * - .MonteCarlo: [0|1]  [ default: 0 ]
     *
     * \ingroup cafe
     */
    class BadLBNs : public Processor {
    public:
        BadLBNs(const char *name);
        bool processEvent(cafe::Event& event);
    private:
	std::set<int>   _badLBNs;
	cafe::Variables _vars;
	bool            _MC;
    public:
        ClassDef(BadLBNs, 0);
    };
    
}

#endif // CAFE_BADLBNS_HPP__
