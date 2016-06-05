// This is an integrated test to test the Trigger processor.

#include <iostream>
#include "cafe/Config.hpp"
#include "cafe/RunController.hpp"
#include "cafe/Event.hpp"
#include "cafe/Trigger.hpp"

using namespace cafe;
using namespace std;

namespace {
  bool is_mc;
  bool is_run2b;
  bool is_run2a;
}

int main()
{
  string file[3] = {"run2b_data.root", "run2a_data.root","run2a_trigbits.root"};

  // Make a config object.

  Config config("cafe");
  config.set("cafe.Run", "Trigger(trig)");
  config.set("trig.Triggers", "MUJ5_MM0_4TK05_V MUJ5_MM0_3TK07_V MUJ5_MM0_3T05L_V DMU4_2LM0MM0TLM3 MU_JT20_L2M0 2MU_C_2L2_2TRK");

  // Loop over files.

  for(int i=0; i<3; ++i) {

    // Process caf file.

    config.set("cafe.Input", file[i]);
    config.set("trig.Accounting", "1");
    RunController c1("cafe");
    bool ok = c1.Run(0);
    assert(ok);

    // Again without individual trigger accounting.

    config.set("trig.Accounting", "0");
    RunController c2("cafe");
    ok = c2.Run(0);
    assert(ok);
  }

  return 0;
}
