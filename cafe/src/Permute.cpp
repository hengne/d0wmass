
#include "cafe/Permute.hpp"

#include "cafe/Config.hpp"
#include "cafe/ParseRun.hpp"

#include <vector>
#include <string>
#include <algorithm>

namespace cafe {


    Permute::Permute(const char *name) 
	: Controller(name, std::list<Processor*>())
    {
	using namespace std;

	Config config(name);
	vector<string> runs = config.getVString("Run"," ,");

	if(!runs.empty()) {

	    sort(runs.begin(), runs.end());
	    do {
		string key(name);
		string result;
		for(vector<string>::iterator it = runs.begin();
		    it != runs.end();
		    ++it) {
		    key    += "_";
		    key    += *it;

		    result += " ";
		    result += *it; 
		}

		result += " ";
		result += "Passed";

		/* 
		 * Add entry: 
		 *    name_KEY.Run:       RESULT
		 *    name_KEY.Directory: name_KEY
		 */

		config.set(key + ".Run", result);
		config.set(key + ".Directory", key); 
		add(new Controller(key.c_str()));

	    } while(next_permutation(runs.begin(), runs.end()));
	}
    }

    bool Permute::processEvent(cafe::Event& event)
    {
        for(std::list<Processor*>::iterator it = _processors.begin();
            it != _processors.end();
            ++it) {
            (*it)->incEventCount();
            (*it)->processEvent(event);
        }
        return true;
    }	

    Permute::~Permute()
    {}

}

ClassImp(cafe::Permute)
