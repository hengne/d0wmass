#ifndef CAFE_REMOVEOBJECTS_HPP_
#define CAFE_REMOVEOBJECTS_HPP_

#include "cafe/Processor.hpp"

#include <string>
#include <vector>

class TObjArray;

namespace cafe {

    /**
     * Remove all objects from a user defined branch.
     * The list of objects to keep is passed in one or more
     * TObjArray via the Event.
     *
     * The package assumes that some other code determines which
     * objects are worth keeping and puts the objects into a 
     * TObjArray. There can be more than one such list. The names
     * of these arrays is given in the .Keep: option.
     *
     * Configuration options:
     *
     *  - .Branch:  BRANCHNAME [ default: "Track" ] branch to modify
     *  - .Keep:    NAME NAME... [ default: empty ] list of object arrays.
     * 
     */
    
    class RemoveObjects : public cafe::Processor {
    public:
	RemoveObjects(const char *name);
	bool processEvent(cafe::Event& event);
    private:
	std::string              _branch;
	std::vector<std::string> _list;
    public:
	ClassDef(RemoveObjects,0);
    };
}

#endif // CAFE_REMOVEOBJECTS_HPP_

