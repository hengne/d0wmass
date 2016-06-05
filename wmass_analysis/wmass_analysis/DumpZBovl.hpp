#include "cafe/Processor.hpp"
#include <string>

class cafe::Event;

class DumpZBovl : public cafe::Processor {

 public:

  DumpZBovl(const char *name);

  void begin();
  bool processEvent(cafe::Event& event);
  void finish();

 private:

  // Configuration of this instance
  std::string _prefix;

  ClassDef(DumpZBovl, 0);

};
