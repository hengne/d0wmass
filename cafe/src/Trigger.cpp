#include "cafe/Trigger.hpp"
#include <stdexcept>

using namespace std;

namespace cafe {

    Trigger::Trigger(const char *name)
      : Processor(name)
    {
      throw runtime_error("cafe::Trigger processor is obsolete. Use caf_trigger::TriggerSelection instead.") ;      
    }
}
ClassImp(cafe::Trigger)
