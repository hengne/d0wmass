
#include "cafe/ConfigDumper.hpp"

#include <algorithm>
#include <fstream>

#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

namespace cafe {

  ConfigDumper::ConfigDumper(const char *name)
    : Processor(name)
  {
    Config config(name);

    _dumpToScreen  = static_cast<bool>(config.get("DumpToScreen", 1));
    _dumpToROOTDir = static_cast<bool>(config.get("DumpToROOTDir", 1));

    if (_dumpToROOTDir)
      _dumpName = config.get("DumpName","configDB");
  }

  void ConfigDumper::begin()
  {
    Config config(name());

    if (_dumpToScreen) {
      out() << "========================================" << std::endl;
      out() << "ConfigDumper[" << name() << "]:"
	    << " Dumping configuration DB to screen" << std::endl;
      config.dumpConfig(out());
      out() << "========================================" << std::endl;
    } // if

    return;
  }

  void ConfigDumper::finish()
  {
    if (_dumpToROOTDir) {
      out() << "========================================" << std::endl;
      out() << "ConfigDumper[" << name() << "]:"
	    << " Dumping configuration to current ROOT directory" << std::endl;
      out() << "   (using name '" << _dumpName << "')" << std::endl;
      if (TDirectory* dir = getDirectory()) {
	Config config(name());
	config.dumpConfig(dir,_dumpName);
      } else {
	// Could not find a directory to store things.
	err() << fullName() << ": No valid directory" << std::endl;
      } // else
      out() << "========================================" << std::endl;
    } // if

    return;
  }
}

ClassImp(cafe::ConfigDumper)

