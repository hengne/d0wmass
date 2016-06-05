#ifndef CAFE_TRIGGER_HPP__
#define CAFE_TRIGGER_HPP__

#include "cafe/Processor.hpp"

namespace cafe {

  class Trigger : public Processor {
    
  public:
    Trigger(const char *name);
    ClassDef(Trigger,0);
  };
}


#endif // CAFE_TRIGGER_HPP__
