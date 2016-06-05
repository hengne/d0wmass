#include "cafe/Processor.hpp"
#include <string>
#include <map>
#include <set>

class cafe::Event;

class DumpLBN : public cafe::Processor {

 public:
  std::map<int, int> _run_lbn_map;
  std::map<int, int> _lbn_map;
  std::set<int> _lbn_list;

  DumpLBN(const char *name);

  void begin();
  bool processEvent(cafe::Event& event);
  void finish();

 private:

  // Configuration of this instance
  std::string _prefix;

  ClassDef(DumpLBN, 0);

};
