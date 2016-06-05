
#include "cafe/Ptr.hpp"

#include "TRefCnt.h"
#include <iostream>

namespace {

    static int i = 0;

    class MyObject : public TRefCnt {
    public:
	  MyObject() {
	    id = i++;
	    std::cout << "MyObject Created : " << id << std::endl;
	  }
	  ~MyObject() {
	    std::cout << "MyObject Destroyed : " << id << std::endl;
	  }
    private:
	  int id;
    };

    cafe::Ptr<MyObject> save(0);
}

int main()
{
    using namespace cafe;

    for(int i = 0; i < 10; i++) {
       Ptr<MyObject> p(new MyObject);
       save = p;
    }
    return 0;
}

