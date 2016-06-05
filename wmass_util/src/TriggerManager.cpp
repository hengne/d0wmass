#include "wmass_util/TriggerManager.hpp"
#include "cafe/Trigger.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace cafe;

// Global definitions
TriggerManager* TriggerManager::_instance=(TriggerManager*)0;

//Singleton.  If no instance exists, create one.  Get pointer to instance.
TriggerManager* TriggerManager::get_instance() {
  if (_instance == 0) _instance = new TriggerManager();
  return _instance;
}

// initialize trigger manager
void TriggerManager::LoadTriggers() {
  
  ifstream trigfile("trigs.map");  
  if(!trigfile) cout<<"Please provide a file called trigs.map"<<endl;
  
  cout<<"Initialize TriggerManager:"<<endl;

  string line;
  int runnum;
  int nlines=0;
  vector<string> trignamevec;
  
  while (getline(trigfile, line) ) { // loop over all lines
    runnum = 0;
    trignamevec.clear();
    nlines++;
    
    string trigname;
    istringstream newline(line);
    newline >> runnum;
    while (newline >> trigname) {
      trignamevec.push_back( trigname );
    }
    _trigger_map[runnum]=trignamevec;
  } // loop over all lines

  cout<<"Read "<<nlines<<" lines from trigs.map"<<endl;

  trigfile.close();
}

// Constructor initializes pointers to zero
TriggerManager::TriggerManager() {
  LoadTriggers();
  _global_vars.add("_runno");

}

// Destructor 
TriggerManager::~TriggerManager() { }

// reset all flags
void TriggerManager::ResetFlags() {
  // mainly for v8-10, v11 (eta converage for these two trigger lists changed)
  _using_EM_HI_SH = false;
  _using_EM_HI = false;
  _using_EM_MX = false;
  _using_EM_MX_SH = false;
  _using_EM_HI_2EM5_SH = false;
  // mainly for v12
  _using_E1_SHT20 = false;
  _using_E2_SHT20 = false;
  _using_E3_SHT20 = false;
  _using_E1_SH30 = false;
  // mainly for v13, E1_SH30 also used in this trigger list
  _using_E1_SHT22 = false;
  _using_E2_SHT22 = false;
  _using_E3_SHT22 = false;
  _using_any_trig = false;
  // mainly for v14
  _using_E1_ISHT22 = false;
  _using_E3_ISHT22 = false;
  _using_E4_ISHT22 = false;

  // mainly for v15
  _using_E1_SHT25 = false;
 
 // mainly for v16
  _using_E1_SHT27 = false; 
}

// trigger used
// this only indicates how many triggers were used for each run, not for each event
void TriggerManager::TrigsUsed(Event& event) {

  // reset all flags
  ResetFlags();

  const TMBGlobal *global = event.getGlobal(_global_vars);
  int runNo = global->runno();

  vector<string> trigs_used = _trigger_map[runNo];  
  //  cout<<"Trigs used: ";
  for(unsigned int i = 0; i < trigs_used.size(); i++) { 
    // for v8-10 and v11
    if(trigs_used[i]=="EM_HI_SH")           _using_EM_HI_SH = true;
    else if(trigs_used[i]=="EM_MX_SH")      _using_EM_MX_SH = true;
    else if(trigs_used[i]=="EM_HI_2EM5_SH") _using_EM_HI_2EM5_SH = true;
    else if(trigs_used[i]=="EM_MX")         _using_EM_MX = true;
    else if(trigs_used[i]=="EM_HI")         _using_EM_HI = true;
    // for v12
    else if(trigs_used[i]=="E1_SHT20")      _using_E1_SHT20 = true;
    else if(trigs_used[i]=="E2_SHT20")      _using_E2_SHT20 = true;
    else if(trigs_used[i]=="E3_SHT20")      _using_E3_SHT20 = true;
    else if(trigs_used[i]=="E1_SH30")       _using_E1_SH30 = true;
    // for v13
    else if(trigs_used[i]=="E1_SHT22")      _using_E1_SHT22 = true;
    else if(trigs_used[i]=="E2_SHT22")      _using_E2_SHT22 = true;
    else if(trigs_used[i]=="E3_SHT22")      _using_E3_SHT22 = true;
    // for v14
    else if(trigs_used[i]=="E1_ISHT22")     _using_E1_ISHT22 = true;
    else if(trigs_used[i]=="E3_ISHT22")     _using_E3_ISHT22 = true;
    else if(trigs_used[i]=="E4_ISHT22")     _using_E4_ISHT22 = true;
    
    //for v15 / v16
    if(trigs_used[i]=="E1_SHT25")     _using_E1_SHT25 = true;
    if(trigs_used[i]=="E1_SHT27")     _using_E1_SHT27 = true;
  }
  
  if (trigs_used.size() > 0) _using_any_trig = true;
}

// check whether certain triggers are fired for each event
void TriggerManager::TrigsFired(Event& event) {

  // loop over all triggers
  Collection<TMBTrigger> triggers = event.getTriggers();

  //  cout<<"Trigs fired: ";
  for (Collection<TMBTrigger>::iterator it = triggers.begin(); it!= triggers.end(); ++it) {
   
    const char* trigname = (*it).getTrgName();
    //    cout<<trigname<<" ";
    // for v8-10 and v11
    if((string)(trigname)=="EM_HI_SH")           _EM_HI_SH_fired = true;
    else if((string)(trigname)=="EM_MX_SH")      _EM_MX_SH_fired = true;
    else if((string)(trigname)=="EM_HI_2EM5_SH") _EM_HI_2EM5_SH_fired = true;
    else if((string)(trigname)=="EM_MX")         _EM_MX_fired = true;
    else if((string)(trigname)=="EM_HI")         _EM_HI_fired = true;
    // for v12
    else if((string)(trigname)=="E1_SHT20")      _E1_SHT20_fired = true;
    else if((string)(trigname)=="E2_SHT20")      _E2_SHT20_fired = true;
    else if((string)(trigname)=="E3_SHT20")      _E3_SHT20_fired = true;
    else if((string)(trigname)=="E1_SH30")       _E1_SH30_fired = true;
    // for v13
    else if((string)(trigname)=="E1_SHT22")      _E1_SHT22_fired = true;
    else if((string)(trigname)=="E2_SHT22")      _E2_SHT22_fired = true;
    else if((string)(trigname)=="E3_SHT22")      _E3_SHT22_fired = true;
    // for v14
    else if((string)(trigname)=="E1_ISHT22")     _E1_ISHT22_fired = true;
    else if((string)(trigname)=="E3_ISHT22")     _E3_ISHT22_fired = true;
    else if((string)(trigname)=="E4_ISHT22")     _E4_ISHT22_fired = true;

    //for v15 / v16
    if((string)(trigname)=="E1_SHT25")     _E1_SHT25_fired = true;
    if((string)(trigname)=="E1_SHT27")     _E1_SHT27_fired = true;

  }  
} // trigs fired

// configure triggers for this event
// need to be called at least once for each event
void TriggerManager::SetTrigs(Event& event) {
  TrigsUsed(event);
  TrigsFired(event);
}

// check whether this EVENT passes trigger pre-requirement
// does not mean the electron matches with trigger objects
bool TriggerManager::Passes_Trig(string trigname) {

  bool passes_trig = false;

  if(trigname=="EM_HI_SH") {          // for v8-10 and v11
    if(_using_EM_HI_SH && _EM_HI_SH_fired) passes_trig = true;
  } else if (trigname=="EM_MX_SH") {
    if(_using_EM_MX_SH && _EM_MX_SH_fired) passes_trig = true;
  } else if (trigname=="EM_HI_2EM5_SH") {
    if(_using_EM_HI_2EM5_SH && _EM_HI_2EM5_SH_fired) passes_trig = true;
  } else if (trigname=="EM_MX") {
    if(_using_EM_MX && _EM_MX_fired) passes_trig = true;
  } else if (trigname=="EM_HI") {
    if(_using_EM_HI && _EM_HI_fired) passes_trig = true;
  } else if (trigname=="E1_SHT20") {   // for v12
    if(_using_E1_SHT20 && _E1_SHT20_fired) passes_trig = true;
  } else if (trigname=="E2_SHT20") {
    if(_using_E2_SHT20 && _E2_SHT20_fired) passes_trig = true;
  } else if (trigname=="E3_SHT20") {
    if(_using_E3_SHT20 && _E3_SHT20_fired) passes_trig = true;
  } else if (trigname=="E1_SH30") {
    if(_using_E1_SH30 && _E1_SH30_fired) passes_trig = true;
  } else if (trigname=="E1_SHT22") {   // for v13
    if(_using_E1_SHT22 && _E1_SHT22_fired) passes_trig = true;
  } else if (trigname=="E2_SHT22") {
    if(_using_E2_SHT22 && _E2_SHT22_fired) passes_trig = true;
  } else if (trigname=="E3_SHT22") {
    if(_using_E3_SHT22 && _E3_SHT22_fired) passes_trig = true;
  } else if (trigname=="E1_ISHT22") {  // for v14
    if(_using_E1_ISHT22 && _E1_ISHT22_fired) passes_trig = true;
  } else if (trigname=="E2_ISHT22") {
    if(_using_E3_ISHT22 && _E3_ISHT22_fired) passes_trig = true;
  } else if (trigname=="E4_ISHT22") {
    if(_using_E4_ISHT22 && _E4_ISHT22_fired) passes_trig = true;
  } 
  else if (trigname=="E1_SHT25") {
    if(_using_E1_SHT25 && _E1_SHT25_fired) passes_trig = true;
  } 
  else if (trigname=="E1_SHT27") {
    if(_using_E1_SHT27 && _E1_SHT27_fired) passes_trig = true;
  } 

  return passes_trig;
}

bool TriggerManager::Uses_Trig(string trigname) {

  bool passes_trig = false;

  if(trigname=="EM_HI_SH") {          // for v8-10 and v11
    if(_using_EM_HI_SH) passes_trig = true;
  } else if (trigname=="EM_MX_SH") {
    if(_using_EM_MX_SH) passes_trig = true;
  } else if (trigname=="EM_HI_2EM5_SH") {
    if(_using_EM_HI_2EM5_SH) passes_trig = true;
  } else if (trigname=="EM_MX") {
    if(_using_EM_MX) passes_trig = true;
  } else if (trigname=="EM_HI") {
    if(_using_EM_HI) passes_trig = true;
  } else if (trigname=="E1_SHT20") {   // for v12
    if(_using_E1_SHT20) passes_trig = true;
  } else if (trigname=="E2_SHT20") {
    if(_using_E2_SHT20) passes_trig = true;
  } else if (trigname=="E3_SHT20") {
    if(_using_E3_SHT20) passes_trig = true;
  } else if (trigname=="E1_SH30") {
    if(_using_E1_SH30) passes_trig = true;
  } else if (trigname=="E1_SHT22") {   // for v13
    if(_using_E1_SHT22) passes_trig = true;
  } else if (trigname=="E2_SHT22") {
    if(_using_E2_SHT22) passes_trig = true;
  } else if (trigname=="E3_SHT22") {
    if(_using_E3_SHT22) passes_trig = true;
  } else if (trigname=="E1_ISHT22") {  // for v14
    if(_using_E1_ISHT22) passes_trig = true;
  } else if (trigname=="E2_ISHT22") {
    if(_using_E3_ISHT22) passes_trig = true;
  } else if (trigname=="E4_ISHT22") {
    if(_using_E4_ISHT22) passes_trig = true;
  } 
  else if (trigname=="E1_SHT25") {
    if(_using_E1_SHT25) passes_trig = true;
  } 
  else if (trigname=="E1_SHT27") {
    if(_using_E1_SHT27) passes_trig = true;
  } 
  return passes_trig;
}





// check whether this EVENT passes any trigger pre-requirements
// does not mean the electron matches with trigger objects
bool TriggerManager::Passes_Trig_CMB() {
  bool passes_all = false;
  if( (_using_EM_HI_SH && _EM_HI_SH_fired) ||     // for v8-10 and v11
      (_using_EM_MX_SH && _EM_MX_SH_fired) ||
      (_using_EM_HI_2EM5_SH && _EM_HI_2EM5_SH_fired) ||
      (_using_EM_MX && _EM_MX_fired) ||
      (_using_EM_HI && _EM_HI_fired) ||
      (_using_E1_SHT20 && _E1_SHT20_fired) ||     // for v12
      (_using_E2_SHT20 && _E2_SHT20_fired) ||
      (_using_E3_SHT20 && _E3_SHT20_fired) ||
      (_using_E1_SH30 && _E1_SH30_fired) ||
      (_using_E1_SHT22 && _E1_SHT22_fired) ||     // for v13
      (_using_E2_SHT22 && _E2_SHT22_fired) ||
      (_using_E3_SHT22 && _E3_SHT22_fired) ||
      (_using_E1_ISHT22 && _E1_ISHT22_fired) ||   // for v14
      (_using_E3_ISHT22 && _E3_ISHT22_fired) ||
      (_using_E4_ISHT22 && _E4_ISHT22_fired) )     
    passes_all = true;
  
  return passes_all;
}
