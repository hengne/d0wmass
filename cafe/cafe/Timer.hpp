#ifndef CAFE_TIMER_HPP_
#define CAFE_TIMER_HPP_

#include "TStopwatch.h"

#include "cafe/Controller.hpp"

namespace cafe {

    /**
     * Time the execution of children.
     */
    class Timer : public cafe::Controller {
    public:
	Timer(const char *name);
	~Timer();
	bool processEvent(cafe::Event& event);
    private:
	  TStopwatch _timer;
    public:
	ClassDef(Timer,0 );
    };

}

#endif // CAFE_TIMER_HPP_
