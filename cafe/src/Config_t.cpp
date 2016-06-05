
#include "cafe/Config.hpp"
#include <cassert>
#include <cmath>

#include <iostream>

int main()
{
    using namespace std;

    cafe::Config c("test");
    cafe::Config g("global");

    // add entries by hand, test that we get the correct values back.

    c.set("test.aString", "testString");
    c.set("test.anInt", "54");
    c.set("test.aReal", "8.52");
    c.set("test.aStringVec", "test1 test2 test3");
    c.set("test.TrailingSpace", "a    ");
    c.set("test.OnlySpace", "    ");
    c.set("test.EmptyString", "");
    c.set("test.anIntVec", "1 2 3 4 5");
    c.set("test.aRealVec", "1.0 2.0 3.0");
    c.set("test.aTrueBool", "true");
    c.set("test.aFalseBool", "false");

    c.set("global.var1", "globalVar1");
    c.set("global.var2", "globalVar2");
    c.set("test.stringVar1","%{global.var1}");
    c.set("test.stringVar2","%{global.var1}-%{global.var2}");

    c.set("global.int","1234");
    c.set("test.intVar", "%{global.int}");

    c.set("global.real","12.34");
    c.set("test.realVar", "%{global.real}");

    c.set("test.unused", "1234");
    c.set("test.unused2", "5678");
    c.set("proc.unused", "should be ok");

    c.set("first.data","789");
    c.set("second.data", "%{first.data}");
    c.set("test.recursive", "%{second.data}");
    c.set("test.recursive2", "%{test.recursive}");

    c.set("test.recIntVector","123 %{test.recursive} 456");

    c.set("myglobal", "1234");
    c.set("test.simple", "%{myglobal}");

    c.resolve();

    c.dumpConfig(std::cout);

    g.get("junk", "");  // Define "global" as a processor.

    assert(c.get("aString","") == "testString");
    assert(c.get("anInt", 0) == 54);
    assert(fabs(c.get("aReal",0.0) - 8.52) < 1.0e-10);

    assert(c.getVString("aStringVec").size() == 3);
    assert(c.getVString("aStringVec")[0] == "test1");
    assert(c.getVString("aStringVec")[1] == "test2");
    assert(c.getVString("aStringVec")[2] == "test3");

    assert(c.get("TrailingSpace", "junk") == "a");
    assert(c.get("OnlySpace", "junk") == "");
    assert(c.get("EmptyString", "junk") == "");
    
    assert(c.getVInt("anIntVec").size() == 5);
    for(int i = 0; i < 5; i++) {
	assert(c.getVInt("anIntVec")[i] == i + 1);
    }

    assert(c.getVFloat("aRealVec").size() == 3);
    for(int i = 0; i < 3; i++) {
	assert(fabs(c.getVFloat("aRealVec")[i] - ((float )i + 1.)) < 1.0e-10);
    }

    assert(c.get("aTrueBool",false) == true);
    assert(c.get("aFalseBool",true) == false);

    assert(c.get("aTrueBool", 0) == 1);
    assert(c.get("aFalseBool", 1) == 0);

    assert(c.get("stringVar1","") == "globalVar1");
    assert(c.get("stringVar2","") == "globalVar1-globalVar2");
    assert(c.get("intVar", 0) == 1234);
    assert(fabs(c.get("realVar", -1.) - 12.34) < 1.0e-10);

    assert(c.get("recursive", 0) == 789);
    assert(c.get("recursive2", 0) == 789);

    assert(c.getVInt("recIntVector").size() == 3);
    assert(c.getVInt("recIntVector")[0] == 123);
    assert(c.getVInt("recIntVector")[1] == 789);
    assert(c.getVInt("recIntVector")[2] == 456);

    // this should *fail*, and not return 1234
    assert(c.get("simple", 4321) == 4321);


    std::vector<std::string> unused = cafe::Config::checkConfiguration();
    if(unused.size() > 0) {
      std::cout << "-----------------" << std::endl;
      std::cout << "ERROR: Unused (mispelled?) configuration variables:" << std::endl;
      for(std::vector<std::string>::iterator it = unused.begin();
	  it != unused.end();
	  ++it) {
	std::cout << *it << std::endl;
      }
      std::cout << "-----------------" << std::endl;
    }
    assert(unused.size() == 2);

    return 0;
}
