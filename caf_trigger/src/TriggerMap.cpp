/* File TriggerMap.cpp
 *
 * Created       : June 30, 2006
 * Author        : Jovan Mitrevski
 *
 * Last modified : July 26, 2006
 * Comments      : A little utility to tell you the trigger version
 *                 of a run based on an input runvtriglist.txt.
 *                
 * History       : Was called TopTriggerMap in top_cafe before.
 *
 */

#include "caf_trigger/TriggerMap.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>

//namespace caf_trigger {
  
  void TriggerMap::BuildMap(char *filename)
  {

    std::ifstream listfile;
    int runnum, trigv;
    
    std::string tempstring;

    int cnt = 0;
	    
    listfile.open(filename);
    if (!listfile.good()) {
      std::cerr << "TriggerMap: Error opening runlistfile \"" << filename 
		<< "\".\nEXITING!" << std::endl; 
      exit(1);
    }
	
    while(listfile >> runnum >> trigv) {
      if(runnum>=0) {
	_runtrigmap[runnum]=trigv;
	cnt++;
      }
      //swallow the rest that maybe there...
      std::getline(listfile,tempstring);
    }
    _lastrun=runnum;
//     std::cout << "TriggerMap found " << cnt << " runs in " << filename << ", the last run is " << _lastrun << std::endl;
  }

int TriggerMap::TriggerX100(int runnum) const {

  using namespace std ;
  map<int, int>::const_iterator it = _runtrigmap.find(runnum) ;
  
  if (it==_runtrigmap.end()) {
    ostringstream s ;
    s << "caf_trigger:TriggerMap ERROR:  runnumber " << runnum << "not found in the trigger map" ;
    throw runtime_error(s.str()) ;
  }

  return it->second ;
}

float TriggerMap::TriggerVersion(int runnum) const {
  return ((float) TriggerX100(runnum)) / 100.0 ; 
}

//} // namespace top_cafe 

