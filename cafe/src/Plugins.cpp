
#include "cafe/Plugins.hpp"
#include "cafe/Config.hpp"

#include "TEnv.h"

namespace cafe {

    Plugins *Plugins::s_instance = 0;

    Plugins *Plugins::instance()
    {
	if(s_instance == 0) {
	    s_instance = new Plugins();
	}
	return s_instance;
    }

    Plugins::Plugins()
    {
	using namespace std;

        if(TPluginManager *mgr = gROOT->GetPluginManager()) {

	    const char *public_context = getenv("SRT_PUBLIC_CONTEXT");
	    const char *private_context = getenv("SRT_PRIVATE_CONTEXT");
	    if(private_context == 0) private_context = ".";

	    Config conf("cafe");
	    vector<string> packages = conf.getVString("Packages", " ,");
	    packages.push_back("cafe");

	    for(vector<string>::iterator it = packages.begin();
		it != packages.end();
		++it) {
		if(public_context) {
		    string name = public_context;
                    name += '/' + *it + "/scripts/rootrc";
                    TEnv env(name.c_str());
                    mgr->LoadHandlersFromEnv(&env);

		}
		string name = private_context;
		name += '/' + *it + "/scripts/rootrc";
		TEnv env(name.c_str());
		mgr->LoadHandlersFromEnv(&env);
	    }
	}	
    }
    
    Plugins::~Plugins()
    {
    }
}

