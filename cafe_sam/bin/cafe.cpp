
#include <iostream>
#include <algorithm>
#include "cafe/Config.hpp"
#include "cafe/RunController.hpp"

#include "cafe_sam/Dontuse.hpp"
#include "tmb_tree/TMBMet.hpp"

#include "TSystem.h"

#include <cstdlib>
#include <map>
#include <vector>
#include <set>

using namespace cafe;
using namespace std;

namespace {

    // Loaded packages.

    set<string> _loaded;

    // Package level dependencies.
    // _dependencies[mypackage] is a vector of packages that mypackage
    // depends on (i.e. that must be loaded before mypackage).

    map<string, vector<string> > _dependencies;

    void fill_dependencies()
    {
      // Fill known package-level dependencies.
      // These lines can be cut-and-pasted from the output of cafe_depend.py.

      _dependencies["caf_trigger"].push_back("caf_mc_util");
      _dependencies["caf_dq"].push_back("dq_util");
      _dependencies["caf_mc_util"].push_back("caf_util");
      _dependencies["caf_mc_util"].push_back("eff_utils");
      _dependencies["caf_mc_util"].push_back("caf_dq");
      _dependencies["d0root_jlip"].push_back("d0root_analysis");
      _dependencies["d0root_example_caf"].push_back("btags_cert");
      _dependencies["d0root_csip"].push_back("d0root_btag");
      _dependencies["d0root_csip"].push_back("bc_csiptagger");
      _dependencies["btags_cert_caf"].push_back("btags_cert");
      _dependencies["btags_cert_caf"].push_back("caf_mc_util");
      _dependencies["d0root_sltnn"].push_back("d0root_analysis");
      _dependencies["btags_cert"].push_back("d0root_slt");
      _dependencies["btags_cert"].push_back("d0root_jlip");
      _dependencies["btags_cert"].push_back("d0root_sltnn");
      _dependencies["btags_cert"].push_back("d0root_nnbtag");
      _dependencies["btags_cert"].push_back("d0root_csip");
      _dependencies["btags_cert"].push_back("d0root_tmbtree");
      _dependencies["btags_cert"].push_back("d0root_mva_btagger");
      _dependencies["caf_eff_utils"].push_back("caf_mc_util");
      _dependencies["muid_eff"].push_back("eff_utils");
      _dependencies["d0root_btag"].push_back("d0root_analysis");
      _dependencies["caf_cert"].push_back("d0root_analysis");
      _dependencies["d0root_slt"].push_back("d0root_analysis");
      _dependencies["caf_util"].push_back("d0root_btag");
      _dependencies["caf_util"].push_back("tau_tmb");
      _dependencies["caf_util"].push_back("bdt_reader");
      _dependencies["caf_util"].push_back("d0root_tmbtree");
      _dependencies["caf_util"].push_back("tmb2ttau");
      _dependencies["caf_util"].push_back("jetcorr");
      _dependencies["caf_util"].push_back("emid_cuts");
      _dependencies["d0root_tmbtree"].push_back("d0root_analysis");
    }

    void load_package(const string& pkg, bool auto_load,
		      const vector<string>& ignore_packages)
    {
        // Make sure dependencies are filled.

        if(_dependencies.size() == 0)
	  fill_dependencies();

        // Check dependencies.

	if(auto_load) {
	  for(vector<string>::const_iterator i = _dependencies[pkg].begin();
	      i != _dependencies[pkg].end(); ++i) {
	    string dep_pkg = *i;

	    // Check ignore list.

	    bool ignore = false;
	    for(vector<string>::const_iterator j = ignore_packages.begin();
		j != ignore_packages.end() && !ignore; ++j) {
	      if(dep_pkg == *j)
		ignore = true;
	    }

	    // Auto-load, if required and not on ignore list.

	    if(!ignore && _loaded.count(dep_pkg) == 0)
	      load_package(dep_pkg, auto_load, ignore_packages);
	  }
	}

	cout << "Cafe: loading package " << pkg << endl;
	string name = "lib";
	name += pkg;
	if(gSystem->Load(name.c_str()) == -1) {
	    cerr << "cafe: Cannot load requested package: " << pkg << endl;
	    exit(EXIT_FAILURE);
	}
	_loaded.insert(pkg);
    }

    void never_used()
    {
	int *p = &cafe::dont_use_me;
	TMBMet *met = new TMBMet;
        *p = 1;
    }
}

int main(int argc, char *argv[])
{
    // 
    // If the first argument does not end in ':', assume
    // it is the name of the configuration file
    //
    // if so, set CAFE_CONFIG to filename and skip to the
    // rest of arguments; this has to happen before we instantiate
    // the first version of 'Config'
    //
    if((argc > 1) && argv[1][strlen(argv[1])-1] != ':') {
	gSystem->Setenv("CAFE_CONFIG", argv[1]);
	--argc;
	++argv;
    }

    Config config("cafe");

    //
    // Every pair of arguments 'name: value' is entered
    // into the configuration db. If the 'name' has not '.'
    // in it, prefix it automatically with 'cafe.'
    //
    for(int i = 1; i < argc; i++) {
        if(argv[i][strlen(argv[i])-1] == ':') {
            argv[i][strlen(argv[i])-1] = '\0';

	    string key(argv[i]);
	    if(key.find('.') == string::npos && key.find("cafe.", 0) != 0) {
		key = "cafe." + key;
	    }
            config.set(key, argv[i+1]);
            i++;
        } else {
            cerr << "Unknown argument: " << argv[i] << endl;
	    assert(false);
	    abort();
        }
    }

    Config::resolve();

    try {
	// Now load all required packages and libraries
	vector<string> packages = config.getVString("Packages", " ,");
	vector<string> ignore_packages =
	  config.getVString("IgnorePackages", " ,");
	bool auto_load = config.get("Autoload", true);
	for(vector<string>::const_iterator i = packages.begin();
	    i != packages.end(); ++i) {
	  string pkg = *i;
	  load_package(pkg, auto_load, ignore_packages);
	}
    } catch (exception& ex) {
	cerr << "cafe: caught exception during package loading:  " << ex.what() << endl;
	return EXIT_FAILURE;
    } catch(...) {
	cerr << "cafe: caught unknown exception during package loading" << endl;	
	return EXIT_FAILURE;
    }

    try {
      RunController c("cafe");
      c.Run();
    } catch(exception& ex) {
      cerr << "cafe: caught exception during running:  " << ex.what() << endl;
      return EXIT_FAILURE;
    } catch(...) {
      cerr << "cafe: caught unknown exception during running" << endl;
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
