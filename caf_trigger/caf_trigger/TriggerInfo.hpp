#ifndef EMCERT_TRIGGERINFO_HPP
#define EMCERT_TRIGGERINFO_HPP

#include "caf_trigger/TriggerMap.hpp"

namespace caf_trigger {
  int global_CMTversionX100(TriggerMap *runnum_vs_triggerlist, int run);

  const int RUNL2 = 169524; // L2 not applied below this run number
  const int RUN2p4 = 174845;	// L1 range only |eta| < 2.4 below this run

}

#endif
