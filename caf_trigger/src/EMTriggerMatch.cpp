/* File EMTriggerMatch.cpp
 *
 * Created       : Sat Jul 15 14:21:22 CDT 2006
 * Author        : jmitrevs
 *
 * Purpose       : This processor passes events if any electron given
 *                 to it fires the elctron part of any trigger given
 *                 to it. Only triggers that actually fired are considered.
 *                 (Checking whether the trigger fired is copied from
 *                 cafe/Trigger.{hpp|cpp}, matching code is modeled after
 *                 caf_trigger/MatchL1CalTowerReco.{hpp|cpp} and similar
 *                 for L2 and L3, and after em_cert).
 *
 * Last modified :
 * Comments      :
*/

#include <stdexcept>

#include "caf_trigger/EMTriggerMatch.hpp"

#include <algorithm>
#include "cafe/Processor.hpp"
#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "tmb_tree/TMBTrigger.hpp"
#include "tmb_tree/TMBEMCluster.hpp"
#include "tmb_tree/TMBL1CalTower.hpp"
#include "tmb_tree/TMBL2EM.hpp"
#include "tmb_tree/TMBL3Ele.hpp"


using namespace std;

namespace caf_trigger {
  
    /// constructor 
    EMTriggerMatch::EMTriggerMatch(const char *name) 
	: cafe::Processor(name),
	  _Ninput(0), _Npassed(0), _trigvars("_trgname")

    {
    }

    /// destructor
    EMTriggerMatch::~EMTriggerMatch()
    {
    }
  
    void EMTriggerMatch::begin()
    {
	/// Here you can read parameters from the config file:
	Config config(name());
    
	vector<string> temp = config.getVString("Triggers", " ,");
	_triggerNames.insert(temp.begin(), temp.end());

	if(_triggerNames.size() == 0) {
	  // for some reason I can't get warn() to work.
	  fprintf(stderr, 
		  "EMTriggerMatch[ %s ]: No triggers specified. All events will fail! Exiting.\n",
		  name().c_str());
	  exit(1);
	}

	_EMBranch         = config.get("EMBranch", "");
	_L1CalTowerBranch = config.get("L1CalTowerBranch", "L1CalEMTowers");
	_L2EMBranch       = config.get("L2EMBranch", "L2EM");
	_L3EleBranch      = config.get("L2EleBranch", "L3Electron");
	_matchV13SHT20    = config.get("MatchV13SHT20", true);
	_L1DeltaR         = config.get("L1DeltaR", 0.4);
	_L2DeltaR         = config.get("L2DeltaR", 0.4);
	_L3DeltaR         = config.get("L3DeltaR", 0.4);


        printf("============================================\n");
        printf("  EMTriggerMatch[ %s ]\n\n",name().c_str());

	printf("    Triggers:             ");
	for(set<string>::iterator it = _triggerNames.begin();
	    it != _triggerNames.end(); ++it) {
	  printf("%s\n                          ", it->c_str());
	}

	printf("\n    EM input branch:      %s\n", _EMBranch.c_str());
	printf("\n    L1Cal Tower branch:   %s\n", _L1CalTowerBranch.c_str());
	printf("    L2EM branch:          %s\n", _L2EMBranch.c_str());
	printf("    L3Ele branch:         %s\n", _L3EleBranch.c_str());
	if (_matchV13SHT20) {
	  printf("\n    If Ex_SHT20 specified, will match in all trigger versions.\n");
	} else {
	  printf("\n    If Ex_SHT20 specified, will match only in v12.\n");
	}
	printf("\n    L1DeltaR:             %f\n", _L1DeltaR);
	printf("    L2DeltaR:             %f\n", _L2DeltaR);
	printf("    L3DeltaR:             %f\n", _L3DeltaR);

        printf("\n============================================\n");

    }
  
    /// add here, your comment (for Doxygen documentation) 
    bool EMTriggerMatch::processEvent(cafe::Event& event)
    {
	++_Ninput;

    
	Collection<TMBEMCluster> GoodElectrons  = event.getEM(_EMBranch);
	Collection<TMBL1CalTower> L1Towers = 
	  event.getCollection<TMBL1CalTower>(_L1CalTowerBranch);
	Collection<TMBL2EM> L2EM = 
	  event.getCollection<TMBL2EM>(_L2EMBranch);
	Collection<TMBL3Ele> L3Ele = 
	  event.getCollection<TMBL3Ele>(_L3EleBranch);


	Collection<TMBTrigger> triggers = event.getTriggers(_trigvars);

	const int trigVer = _trigMap.TriggerX100(event.getGlobal()->runno());

	//
	// This is proportional to the number of triggers in the event
	// and about log(numUserTriggers).
	//
	for(Collection<TMBTrigger>::const_iterator it = triggers.begin();
	    it != triggers.end();
	    ++it) {

	  const std::string trigName = it->getTrgName();

	  if(_triggerNames.find(trigName) != _triggerNames.end()) {

	    // Need to add en entry here for evey trigger that you support

	    // let's divide up in the v8-11, v12, v13 and v14 ranges.

	    if (trigVer < 800) {
	      fprintf(stderr, 
		      "EMTriggerMatch: Does not yet support triggers in trigger version %f. Please add it first.\n",
		      trigVer/100.0 );
	      exit(1);
	    } else if (trigVer < 820) {
	      // only limited support for v8.00 and v8.10

	      if (trigName == "EM_HI_SH") {
		
		// v8.00 and v8.10

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(10.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 req
		    
		    if (PassL3Ele_SHT_v811(20.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}
		
	      } else if (trigName == "EM_HI") {
		
		// v8.00 and v8.10
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(10.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 req
		    
		    if (PassL3Ele_LOOSE_v811(30.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}

	      } else if (trigName == "EM_HI_2EM5_SH") {
		
		// v8.00 and v8.10

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(5.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 req
		    
		    if (PassL3Ele_SHT_v811(20.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}
		
	      } else if (trigName == "EM_HI_2EM5") {
		
		// v8.00 and v8.10
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(5.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 req
		    
		    if (PassL3Ele_LOOSE_v811(30.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}

	      } else { 
		// trigger not supported
		fprintf(stderr, 
			"EMTriggerMatch: Does not yet support trigger %s in trigger version %f. Please add it first.\n",
			trigName.c_str(), trigVer/100.0 );
		exit(2);
	      }

	    } else if (trigVer < 1200) {

	      ///////////////////////////
	      // v8-11 triggers go here
	      ///////////////////////////
	      
	      if (trigName == "EM15_2JT15") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(10.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM_emf(10.0, 0.85, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v811(15.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
	      
	      } else if (trigName == "EM_HI_SH") {
		
		// v8.20 - v11

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(10.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (trigVer < 950 || PassL2EM(12, emit, L2EM)) {
		      // passed L2 or there was no L2 requirement
		    
		      if (PassL3Ele_SHT_v811(20.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		
	      } else if (trigName == "EM_HI") {
		
		// v8.20 - v11

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(10.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (trigVer < 950 || PassL2EM(12, emit, L2EM)) {
		      // passed L2 or there was no L2 requirement
		    
		      if (PassL3Ele_LOOSE_v811(30.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}

	      } else if (trigName == "EM_HI_2EM5_SH") {
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(5.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (trigVer < 950 || PassL2EM(12, emit, L2EM)) {
		      // passed L2 or there was no L2 requirement
		    
		      if (PassL3Ele_SHT_v811(20.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		
	      } else if (trigName == "EM_HI_2EM5") {
		
		// v8.20 - v11
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(5.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (trigVer < 950 || PassL2EM(12, emit, L2EM)) {
		      // passed L2 or there was no L2 requirement
		      
		      if (PassL3Ele_LOOSE_v811(30.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}

	      } else if (trigName == "EM_MX_SH") {
		
		// v8-11
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(15.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 req
		    
		  if (PassL3Ele_SHT_v811(20.0, emit, L3Ele)) {
		    // passed L3
		    _Npassed++;
		    return true;
		  }
		  }
		}
		
	      } else if (trigName == "EM_MX") {
		
		// v8-11
		
		// EM_HI/EM_HI_SH sometimes has an L2 req, sometimes not; will wait for run number
		// to trigger version map to implement that
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(15.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 req
		    
		    if (PassL3Ele_LOOSE_v811(30.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}
	      } else { 
		// trigger not supported
		fprintf(stderr, 
			"EMTriggerMatch: Does not yet support trigger %s in trigger version %f. Please add it first.\n",
			trigName.c_str(), trigVer/100.0 );
		exit(3);
	      }
	    } else if (trigVer < 1300) {

	      ///////////////////////////
	      // v12 triggers
	      ///////////////////////////

	      if (trigName == "E1_SHT15_2J20") {

		// v12

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  // let's try L1
		  if (PassSingleL1Tower(11.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 required
		    
		    if (PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}
		
	      } else if (trigName == "E2_SHT15_2J20") {

		// v12
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  // let's try L1
		  if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 required
		    
		    if (PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}
	      } else if (trigName == "E3_SHT15_2J20") {
		
		// v12
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  // let's try L1
		  if (PassTwoL1TowersAsym(9.0, 3.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 required
		    
		    if (PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}

		// the single-electron triggers are below

	      } else if (trigName == "E1_SHT20") {

		// v12

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(11.0, emit, L1Towers)) {
		    // passed L1

		    // no L2 required

		    if (PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}
		
	      } else if (trigName == "E1_SH30") {

		// v12

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(11.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no l2 required

		    if (PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}
		

	      } else if (trigName == "E2_SHT20") {

		// v12
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
		    // passed L1

		    // no L2 required

		    if (PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}

	      } else if (trigName == "E2_SH30") {

		// v12
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
		    // passed L1

		    // no L2 required

		    if (PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}
		
	      } else if (trigName == "E3_SHT20") {

	      // v12

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersAsym(9.0, 3.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 required
		    
		    if (PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}

	      } else if (trigName == "E3_SH30") {

	      // v12

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersAsym(9.0, 3.0, emit, L1Towers)) {
		    // passed L1
		    
		    // no L2 required
		    
		    if (PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {
		      // passed L3
		      _Npassed++;
		      return true;
		    }
		  }
		}
		
	      } else { 
		// trigger not supported
		fprintf(stderr, 
			"EMTriggerMatch: Does not yet support trigger %s in trigger version %f. Please add it first.\n",
			trigName.c_str(), trigVer/100.0 );
		exit(4);
	      }
	    } else if (trigVer < 1400) {

	      ///////////////////////////
	      // v13 triggers
	      ///////////////////////////
	      if (trigName == "E1_SHT15_2J_J25" || trigName == "E1_SHT15_2J_J30") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(11.0, emit, L1Towers)) {
		    
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		
	      } else if (trigName == "E2_SHT15_2J_J25" || trigName == "E2_SHT15_2J_J30") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		
		  if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2

		      if (PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		
	      } else if (trigName == "E3_SHT15_2J_J25" || trigName == "E3_SHT15_2J_J30") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersAsym(9.0, 3.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		

	      } else if (trigName == "E1_SHT22") {
		
		// v13
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(11.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		
	      } else if (trigName == "E1_SH30") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(11.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		

	      } else if (trigName == "E2_SHT22") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
		  // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}

	      } else if (trigName == "E2_SH30") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
		  // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		
	      } else if (trigName == "E3_SHT22") {
		
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersAsym(9.0, 3.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(22.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		

	      } else if (trigName == "E3_SH30") {
		
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersAsym(9.0, 3.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SH_v12plus(30.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}

	      } else if (_matchV13SHT20 && trigName == "E1_SHT20") {
		// SHT20: These only existed before v13.20. A parameter flag
		// can be specified on whether to match SHT20 here or just
		// in v12
		
		// v13
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(11.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		
	      } else if (_matchV13SHT20 && trigName == "E2_SHT20") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
		  // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}

	      } else if (_matchV13SHT20 && trigName == "E3_SHT20") {
		
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersAsym(9.0, 3.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(20.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		
	      } else { 
		// trigger not supported
		fprintf(stderr, 
			"EMTriggerMatch: Does not yet support trigger %s in trigger version %f. Please add it first.\n",
			trigName.c_str(), trigVer/100.0 );
		exit(5);
	      }
	    } else if (trigVer < 1500) {

	      ///////////////////////////
	      // v14 triggers
	      ///////////////////////////

	      if (trigName == "E1_SHT15_2J_J25") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(12.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}

	      } else if (trigName == "E4_SHT15_2J_J25") {
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2

		      if (PassL3Ele_SHT_v12plus(15.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}

	      } else if (trigName == "E1_SHT25") {
		
		// v14
		
		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(12.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		
	      } else if (trigName == "E1_SH35") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassSingleL1Tower(12.0, emit, L1Towers)) {
		    // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
		
	      
	      } else if (trigName == "E4_SHT25") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
		  // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SHT_v12plus(25.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}

	      } else if (trigName == "E4_SH35") {

		for (Collection<TMBEMCluster>::const_iterator emit = GoodElectrons.begin();
		     emit != GoodElectrons.end();
		     emit++) {
		  
		  if (PassTwoL1TowersSym(6.0, emit, L1Towers)) {
		  // passed L1
		    
		    if (PassL2EM(15.0, emit, L2EM)) {
		      // passed L2
		      
		      if (PassL3Ele_SH_v12plus(35.0, emit, L3Ele)) {
			// passed L3
			_Npassed++;
			return true;
		      }
		    }
		  }
		}
	      
	      } else { 
		// trigger not supported
		fprintf(stderr, 
			"EMTriggerMatch: Does not yet support trigger %s in trigger version %f. Please add it first.\n",
			trigName.c_str(), trigVer/100.0 );
		exit(6);
	      }
	    } else {

	      //////////////////////////////
	      // trigger versions v15+
	      //////////////////////////////

	      fprintf(stderr, 
		      "EMTriggerMatch: Does not yet support triggers in trigger version %f. Please add it first.\n",
		      trigVer/100.0 );
	      exit(19);
	    }
	  }
	}
	  
	return false;
   
    } // processEvent
  
    void EMTriggerMatch::finish() 
    { 
        printf("============================================\n");
        printf("  EMTriggerMatch[ %s ] SUMMARY\n\n",name().c_str());
	
	printf("    Events processed:     %5d\n",_Ninput);
	printf("    Events passed:        %5d\n",_Npassed);
	//printf("    Electron input branch: %s\n"_ElectronBranch.c_str());
	
        printf("\n============================================\n");
    }
  
  
    void EMTriggerMatch::inputFileOpened(TFile *file)
    {  
    }
  
    void EMTriggerMatch::inputFileClosing(TFile *file)
    {
    }
  
  // some private helper functions

  // This function is for standard single L1 trigger tower.
  bool EMTriggerMatch::PassSingleL1Tower(float Et, Collection<TMBEMCluster>::const_iterator emit, 
					 Collection<TMBL1CalTower> L1Towers) const
  {
    for (Collection<TMBL1CalTower>::const_iterator l1it = L1Towers.begin();
	 l1it != L1Towers.end();
	 l1it++) {
      if (l1it->Et() >= Et) { // copied >= from em_cert, not sure if it should be > or >=
	float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
	float deta = l1it->Eta() - emit->CalDetectorEta();
	if (hypot(dphi, deta) < _L1DeltaR) {
	  return true;
	}
      }
    }
    return false;
  }

  // This function is for CEM(2,6) and such; It does after-the-fact clustering, like we do in
  // in em_cert, though the actual trigger does not
  bool EMTriggerMatch::PassTwoL1TowersSym(float Et, Collection<TMBEMCluster>::const_iterator emit, 
					 Collection<TMBL1CalTower> L1Towers) const
  {

    int count = 0;

    for (Collection<TMBL1CalTower>::const_iterator l1it = L1Towers.begin();
	 l1it != L1Towers.end();
	 l1it++) {

      if (l1it->Et() >= Et) { // copied >= from em_cert, not sure if it should be > or >=
	float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
	float deta = l1it->Eta() - emit->CalDetectorEta();
	if (hypot(dphi, deta) < _L1DeltaR) {
	  count++;
	}
      }
    }
    return (count >= 2);
  }

  // This function is for CEM(2,3)CEM(1,9) and such; It does after-the-fact clustering, like we do in
  // in em_cert, though the actual trigger does not
  bool EMTriggerMatch::PassTwoL1TowersAsym(float Et_high, float Et_low, 
					   Collection<TMBEMCluster>::const_iterator emit, 
					   Collection<TMBL1CalTower> L1Towers) const
  {

    bool found_high = false;
    bool found_low = false;

    for (Collection<TMBL1CalTower>::const_iterator l1it = L1Towers.begin();
	 l1it != L1Towers.end();
	 l1it++) {

      if (l1it->Et() >= Et_high && !found_high) { // copied >= from em_cert, not sure if it should be > or >=
	float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
	float deta = l1it->Eta() - emit->CalDetectorEta();
	if (hypot(dphi, deta) < _L1DeltaR) {
	  found_high = true;
	}
      } else if (l1it->Et() >= Et_low) { // copied >= from em_cert, not sure if it should be > or >=
	float dphi = kinem::delta_phi(l1it->Phi(), emit->CalDetectorPhi());
	float deta = l1it->Eta() - emit->CalDetectorEta();
	if (hypot(dphi, deta) < _L1DeltaR) {
	  found_low = true;
	}
      }
    }
    return (found_high && found_low);
  }

  // This function is for standard L2
  bool EMTriggerMatch::PassL2EM(float Et, Collection<TMBEMCluster>::const_iterator emit, 
				Collection<TMBL2EM> L2EM) const
  {
    for (Collection<TMBL2EM>::const_iterator l2it = L2EM.begin();
	 l2it != L2EM.end();
	 l2it++) {
      if (l2it->Et() >= Et) {
	float dphi = kinem::delta_phi(l2it->Phi(), emit->CalDetectorPhi());
	float deta = l2it->Eta() - emit->CalDetectorEta();
	if (hypot(dphi, deta) < _L2DeltaR) {
	  return true;
	}
      }
    }
    return false;
  }

  // This function is for L2 with an emf cut, as in EM15_2J15 trigger
  bool EMTriggerMatch::PassL2EM_emf(float Et, float emf, 
				    Collection<TMBEMCluster>::const_iterator emit, 
				    Collection<TMBL2EM> L2EM) const
  {
    for (Collection<TMBL2EM>::const_iterator l2it = L2EM.begin();
	 l2it != L2EM.end();
	 l2it++) {
      if (l2it->Et() >= Et && l2it->Emf() >= emf) {
	float dphi = kinem::delta_phi(l2it->Phi(), emit->CalDetectorPhi());
	float deta = l2it->Eta() - emit->CalDetectorEta();
	if (hypot(dphi, deta) < _L2DeltaR) {
	  return true;
	}
      }
    }
    return false;
  }


  // this is to pass an l3 SHT for v8-11
  bool EMTriggerMatch::PassL3Ele_SHT_v811(float Et, 
					  Collection<TMBEMCluster>::const_iterator emit, 
					  Collection<TMBL3Ele> L3Ele) const
    
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
	 l3it != L3Ele.end();
	 l3it++) {

      if (l3it->ToolName() == "ELE_LOOSE_SH_T") {

	// don't know if should use DetEta or Eta below
	if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.0 && 
	    l3it->Em1Width() < 0.09 && l3it->Em2Width() < 0.08 && l3it->Em3Width() < 0.05) {
	  float dphi = kinem::delta_phi(l3it->Phi(), emit->CalDetectorPhi());
	  float deta = l3it->DetEta() - emit->CalDetectorEta();
	  if (hypot(dphi, deta) < _L3DeltaR) {
	    return true;
	  }
	}
      }
    }
    return false;
  }

  // this is to pass an l3 LOOSE for v8-11
  bool EMTriggerMatch::PassL3Ele_LOOSE_v811(float Et, 
					    Collection<TMBEMCluster>::const_iterator emit, 
					    Collection<TMBL3Ele> L3Ele) const
    
  {
    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
	 l3it != L3Ele.end();
	 l3it++) {

      if (l3it->ToolName() == "ELE_LOOSE") {

	// don't know if should use DetEta or Eta below
	if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.0) {
	  float dphi = kinem::delta_phi(l3it->Phi(), emit->CalDetectorPhi());
	  float deta = l3it->DetEta() - emit->CalDetectorEta();
	  if (hypot(dphi, deta) < _L3DeltaR) {
	    return true;
	  }
	}
      }
    }
    return false;
  }

  // this is to pass an L3 SHT for v12+
  bool EMTriggerMatch::PassL3Ele_SHT_v12plus(float Et, 
					     Collection<TMBEMCluster>::const_iterator emit, 
					     Collection<TMBL3Ele> L3Ele) const
    
  {

    // not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;


    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
	 l3it != L3Ele.end();
	 l3it++) {

      if (l3it->ToolName() == "ELE_NLV_SHT") {
	
	bool isCC = l3it->DetEta() < L3_CC_EDGE;
	
	// don't know if should use DetEta or Eta below
	if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
	    (isCC &&  l3it->Em1RescWidth() < 1.8 && l3it->Em2RescWidth() < 1.4 && l3it->Em3RescWidth() < 1.15) ||
	    (!isCC &&  l3it->Em1RescWidth() < 1.0 && l3it->Em2RescWidth() < 1.0 && l3it->Em3RescWidth() < 1.2)) {
	  float dphi = kinem::delta_phi(l3it->Phi(), emit->CalDetectorPhi());
	  float deta = l3it->DetEta() - emit->CalDetectorEta();
	  if (hypot(dphi, deta) < _L3DeltaR) {
	    return true;
	  }
	}
      }
    }
    return false;
  }

  // this is to pass an L3 SH for v12+
  bool EMTriggerMatch::PassL3Ele_SH_v12plus(float Et, 
					    Collection<TMBEMCluster>::const_iterator emit, 
					    Collection<TMBL3Ele> L3Ele) const
    
  {

    // not shure where L3 sets the edge
    const float L3_CC_EDGE = 1.3;


    for (Collection<TMBL3Ele>::const_iterator l3it = L3Ele.begin();
	 l3it != L3Ele.end();
	 l3it++) {

      if (l3it->ToolName() == "ELE_NLV_SH") {

	bool isCC = l3it->DetEta() < L3_CC_EDGE;
	
	// don't know if should use DetEta or Eta below
	if (l3it->Et() > Et && l3it->Emf() > 0.9 && fabs(l3it->DetEta()) < 3.6 && 
	    (isCC &&  l3it->Em1RescWidth() < 2.3 && l3it->Em2RescWidth() < 1.7 && l3it->Em3RescWidth() < 1.5) ||
	    (!isCC &&  l3it->Em1RescWidth() < 1.4 && l3it->Em2RescWidth() < 1.35 && l3it->Em3RescWidth() < 1.4)) {
	  float dphi = kinem::delta_phi(l3it->Phi(), emit->CalDetectorPhi());
	  float deta = l3it->DetEta() - emit->CalDetectorEta();
	  if (hypot(dphi, deta) < _L3DeltaR) {
	    return true;
	  }
	}
      }
    }
    return false;
  }

} // using namespace caf_trigger

ClassImp(caf_trigger::EMTriggerMatch)
  
