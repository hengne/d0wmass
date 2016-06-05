#ifndef CAFE_GOODRUNS_HPP__
#define CAFE_GOODRUNS_HPP__

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include <set>

namespace cafe {

    class Event;

    /**
     * Reject events for bad runs or
     * accept events for good runs.
     *
     * Configuration options:
     * - .Files: ListOfRunFiles [ default: ""]
     * - .GoodRuns: if true, use only runs in the file
     *              if false, use only runs not in the file
     *    [default: 1]
     *
     * \ingroup cafe
     */
    class GoodRuns : public Processor {
    public:
        GoodRuns(const char *name);
        bool processEvent(cafe::Event& event);
    private:
        std::set<int>   _goodRuns;
        bool            _useRuns;
	cafe::Variables _vars;
    public:
        ClassDef(GoodRuns, 0);
    };

}

#endif // CAFE_GOODRUNS_HPP__
