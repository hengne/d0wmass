
#include "cafe/Timer.hpp"
#include <iostream>

namespace {
}

namespace cafe {

  Timer::Timer(const char *name)
	: Controller(name)
  {
  }

  Timer::~Timer()
  {
	out() << "Timer[" << name() << "] Total = " 
	  << _timer.RealTime() << " s"
	  << "; " << (_timer.RealTime() / eventCount()) * 1000.0 << " ms/event"
	  << std::endl;
  }

  bool Timer::processEvent(cafe::Event& event)
  {
	_timer.Start(false);
	bool result = Controller::processEvent(event);
	_timer.Stop();

	return result;
  }


}

