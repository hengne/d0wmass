
#include "cafe/Variables.hpp"

#include <vector>
#include <list>
#include <string>

namespace {
    void take_variables(const cafe::Variables& vars)
    {
    }
}

int main()
{
    using namespace cafe;
    using namespace std;

    static const char *names[] = 
	{
	    "name1",
	    "name2",
	    "name3"
	};

    Variables var1;
    Variables var2("test");
    Variables var3("test", "test1");
    Variables var4("test", "test1", "test2");
    Variables var5("test", "test1", "test2", "test3");

    vector<string> v(names, names + sizeof(names)/sizeof(names[0]));
    Variables var7(v);

    var1.add("test");
    var1.add(v);
    var2.add("test1").add(v);

    // this should not compile
    // take_variables("test");

    take_variables(Variables("test"));

    return 0;
}
