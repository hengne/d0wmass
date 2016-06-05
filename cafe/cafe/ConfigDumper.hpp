#ifndef CAFE_CONFIGDUMPER_HPP__
#define CAFE_CONFIGDUMPER_HPP__

#include "cafe/Processor.hpp"

#include <vector>
#include <string>

namespace cafe {

  class Event;

  /**
   * Dump configuration DB to screen or to the
   * current ROOT directory.
   *
   * Configuration options:
   * - .DumpToScreen : dump info to screen if true [default: 1]
   * - .DumpToROOTDir: dump info to current ROOT directory
   *                   if true [default: 1]
   * - .DumpName     : name of the TClonesArray in which the
   *                   various settings end up in the ROOT file
   *                   [default: configDB]
   *
   * \ingroup cafe
   */
  class ConfigDumper : public Processor {
  public:
    ConfigDumper(const char *name);
    void begin();
    void finish();
  private:
    std::string _dumpName;
    bool _dumpToScreen;
    bool _dumpToROOTDir;
  public:
    ClassDef(ConfigDumper, 0);
  };

}

#endif // CAFE_CONFIGDUMPER_HPP__
