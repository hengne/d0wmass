#ifndef CAFE_SKIMEVENTS_HPP__
#define CAFE_SKIMEVENTS_HPP__

#include "cafe/Processor.hpp"
#include <set>
#include <string>

class SkimEvents : public cafe::Processor {
public:
  SkimEvents(const char *name);
  bool processEvent(cafe::Event& event);
  void finish();

  ClassDef(SkimEvents, 0);

private:
  std::set<std::pair<int, int> > event_set;
  int _skimedEvents;  
  bool _MCSkim;
};
   
#endif // CAFE_SKIMEVENTS_HPP__
