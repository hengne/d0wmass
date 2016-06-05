#ifndef CAFE_EVENTLISTEXPANDER_HPP_
#define CAFE_EVENTLISTEXPANDER_HPP_

#include "cafe/Expander.hpp"

#include <list>
#include <string>

namespace cafe {

    class EventListExpander : public Expander {
    public:
	EventListExpander(const char *url);
	virtual std::string nextFile();
    private:
	std::list<std::string> _files;
	ClassDef(EventListExpander, 0);
    };

}

#endif // CAFE_EVENTLISTEXPANDER_HPP_
