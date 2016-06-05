//
// RunEventChecker.hpp
//

#ifndef __RunEventChecker__
#define __RunEventChecker__

#include "TObject.h"

namespace cafe {

    class Event;

    ///  Utility that keeps track of a run and event number. Saves you
    ///  a small bit of code and having to declare both run and event, etc.
    ///
    class RunEventChecker  : public TObject  {
    public:
	inline RunEventChecker (void)
	    : _run (-1), _event (-1)
	{}
	bool isNewEvent (cafe::Event &reader);
	
    private:
	ClassDef (RunEventChecker,0);
	int _run;
	int _event;
    };
}

#endif
