// This is an integrated test to test various aspects of the Evant class.

#include <iostream>
#include "cafe/Config.hpp"
#include "cafe/RunController.hpp"
#include "cafe/Function.hpp"
#include "cafe/Event.hpp"

using namespace cafe;
using namespace std;

namespace {
  bool is_mc;
  bool is_run2b;
  bool is_run2a;
}

bool test_function(Event& event)
{
  is_mc = event.isMC();
  is_run2b = event.isRun2b();
  is_run2a = event.isRun2a();
  cout << "MC: " << is_mc << endl;
  cout << "Run 2b: " << is_run2b << endl;
  cout << "Run 2a: " << is_run2a << endl;
  return true;
}

CAFE_FUNCTION(test_function)

int main()
{
  string file[4] = {"run2b_data.root", "run2b_mc.root",
		    "run2a_data.root", "run2a_mc.root"};

  // Make a config object.

  Config config("cafe");
  config.set("cafe.Run", "test_function");

  // Loop over files.

  for(int i=0; i<4; ++i) {

    config.set("cafe.Input", file[i]);

    // Process caf file.

    RunController c("cafe");
    bool ok = c.Run(0);
    assert(ok);

    if(file[i].find("mc") < string::npos)
      assert(is_mc);
    else
      assert(!is_mc);

    if(file[i].find("run2b") < string::npos) {
      assert(is_run2b);
      assert(!is_run2a);
    }
    else {
      assert(!is_run2b);
      assert(is_run2a);
    }
  }

  return 0;
}
