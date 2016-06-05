
#include "cafe/EventBase.hpp"
#include <cassert>
#include <list>
#include <iostream>

namespace {
    struct MyClass {
	MyClass() { 
	    _counter++; 
	    std::cerr << "Creating MyClass: " << _counter << std::endl;
	}
	~MyClass() { 
	    _counter--; 
	    std::cerr << "Destroying MyClass:" << _counter << std::endl;
	}
	static int _counter;
    };

    int MyClass::_counter = 0;

}

int main()
{
    using namespace std;
    using namespace cafe;

    cafe::EventBase event;

    event.put("integer", (int )5);
    int x;
    
    assert(event.get("integer", x) && (x == 5));

    MyClass * ptr = new MyClass();
    assert(MyClass::_counter == 1);

    event.put("myClass", ptr);
    event.clear();
    assert(MyClass::_counter == 0);    

    ptr = new MyClass();
    event.put("myKeep", keep(ptr));
    event.clear();
    assert(MyClass::_counter == 1);        

    delete ptr;

    event.tag("Hello");
    event.tag("World");

    assert(event.hasTag("Hello"));
    assert(event.hasTag("World"));

    assert(!event.hasTag("Hello World"));

    event.untag("Hello");
    assert(!event.hasTag("Hello"));

    std::list<std::string> tags;
    tags.push_back("Hello");
    tags.push_back("World");
    
    event.untag(tags.begin(), tags.end());

    assert(!event.hasTag("Hello"));
    assert(!event.hasTag("World"));

    return 0;
}
