#include "cafe/GoodRuns.hpp"

#include <algorithm>
#include <fstream>

#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

namespace cafe {

    GoodRuns::GoodRuns(const char *name)
        : Processor(name),
	  _vars("_runno")
    {
        Config config(name);
        _useRuns = static_cast<bool>(config.get("GoodRuns", 1));

        std::vector<std::string> files = config.getVString("Files", " ,");
        for(std::vector<std::string>::iterator it = files.begin();
            it != files.end();
            ++it) {
            out() << "GoodRun[" << name << "]: Adding file: " << *it << std::endl;
            std::ifstream f((*it).c_str());
            for(int run; f >> run; ) {
                _goodRuns.insert(run);
            }
        }
    }

    bool GoodRuns::processEvent(cafe::Event& event)
    {
	if (_useRuns)
	    return _goodRuns.find(event.getGlobal(_vars)->runno()) != _goodRuns.end();
	else
	    return _goodRuns.find(event.getGlobal(_vars)->runno()) == _goodRuns.end();
    }
    
}

ClassImp(cafe::GoodRuns)
