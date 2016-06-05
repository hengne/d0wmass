/* File TriggerTermMap.cpp
 *
 * Created       : August 21, 2006
 * Author        : Mikko Voutilainen (mavoutil)
 *
 * Purpose       : Match trigger version and trigger to
 *                 corresponding L1tool, L2tool+cut and
 *                 L3tool+cut. Used in JetTriggerMatch.cpp.
 *                 The mappings are given in a text file,
 *                 parameters/triggerterms.txt by default.
 *                 Modeled after TriggerTerm.cpp.
 *
 * Last modified : 
 * Comments      : Hard-coded available trigger list versions
 *                 so that a given trigger list range can be
 *                 transformed to a set of trigger lists for the map
 *                
 * History       : 
 *
 */

#include "caf_trigger/TriggerTermMap.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace caf_trigger {
  
void TriggerTermMap::BuildMap(char *filename)  {
  
  ifstream listfile(filename);
  if (!listfile || !listfile.good()) {
    cerr << "TriggerTermMap: Error opening runlistfile \"" << filename 
	 << "\".\nEXITING!" << std::endl; 
    exit(1);
  }
  float triglists[] = 
    {8.00,   8.10,  8.20,  8.30,  8.40,  8.41,
     9.20,   9.30,  9.31,  9.40,  9.41,  9.42,  9.50,
     10.00, 10.01, 10.02, 10.03, 10.30, 10.35, 10.36,
     11.00, 11.01, 11.02, 11.03, 11.04,
     12.10, 12.20, 12.30, 12.31, 12.32, 12.33, 12.34, 12.35, 12.36, 12.37,
     12.38,
     13.00, 13.01, 13.02, 13.03, 13.04, 13.10, 13.11, 13.20, 13.21, 13.22,
     13.23, 13.29, 13.30, 13.31, 13.32, 13.40, 13.50, 13.51, 13.52, 13.60,
     13.61, 13.62, 13.70, 13.80, 13.81, 13.90,
     14.00, 14.10, 14.20, 14.21, 14.30, 14.31, 14.40, 14.41, 14.42, 14.43,
     14.50, 14.51, 14.60, 14.61, 14.70, 14.71, 14.80, 14.81, 14.82, 14.90,
     14.91, 14.92, 14.93, // 14.41->14.51 sep-22
     15.00, 15.01, 15.02, 15.03, 15.04, 15.05, 15.06, 15.07, 15.08, 15.09,
     15.10, 15.11, 15.12, 15.13, 15.14, 15.15, 15.16, 15.17, 15.20, 15.21,
     15.22, // 15.23->15.99 apr-08
     15.23, 15.24, 15.25, 15.26, 15.27, 15.28, 15.29, 15.30, 15.31, 15.50,
     15.51, 15.52, 15.53, 15.54, 15.60, 15.61, 15.62, 15.63, 15.64, 15.65,
     15.66, 15.67, 15.68, 15.69, 15.70, 15.71, 15.72, 15.73, 15.80, 15.90,
     15.91, 15.92, 15.93, 15.94, 15.95, 15.96,
     16.00, 16.01, 16.02, 16.03, 16.04, 16.05, 16.06, 16.07, 16.08, 16.09, 
     16.10, 16.11, 16.12, 16.13, 16.14, 16.16, 16.17, 16.18, 16.19, 16.20, 
     16.21, 16.22, 16.23, 16.30, 16.31, 16.32, 16.33, 16.50, 16.51, 16.52, 
     16.53, 16.54, 16.55, 16.56, 16.60, 16.61, 16.62, 16.63, 16.64, 16.65, 
     16.66, 16.67, 16.68, 16.69, 16.70, 16.71, 16.72, 16.73, 16.74, 16.75, 
     16.76, 16.77, 16.78, 16.79, 16.80, 16.81, 16.82, 16.83, 16.84, 16.85, 
     16.86, 16.87, 16.88, 16.89, 16.90, 16.91, 16.92, 16.93, 16.94, 16.95, 
     16.96, 16.97, 16.98, 16.99 }; //as of 30 sep 2010

  int ntriglists = sizeof(triglists)/sizeof(triglists[0]);
  // assert(ntriglists==123);//106);//102);  //KRH:   why????

  string trigname, l1toolname, l2toolname, l3toolname;
  int trigver, nl3cut;
  float triglistmin, triglistmax, l2cut, l3cut;

  while (listfile >> trigname >> trigver >> triglistmin >> triglistmax
	 >> l1toolname >> l2toolname >> l2cut >> l3toolname >> l3cut >> nl3cut) {

    int counter = 0;
    for (int i = 0; i != ntriglists; ++i) {
      
      int triglist = int(triglists[i]*100+0.5);
      int trigmin = int(triglistmin*100+0.5);
      int trigmax = int(triglistmax*100+0.5);
      if (triglist >= trigmin && triglist <= trigmax) {

	_l1termmap[trigname][triglist] = l1toolname;
	_l2termmap[trigname][triglist] = make_pair(l2toolname, l2cut);
	_l3termmap[trigname][triglist] = make_pair(l3toolname, l3cut);
	_trigvermap[trigname][triglist] = trigver;
	_nl3jetsmap[trigname][triglist] = nl3cut;

	++counter;
      }
    }
    if (counter == 0)
      cerr << "Warning: TriggerTermMap("<<filename<<"): " << endl
	   << "  no trigger list found for triglistmin="<<triglistmin
	   << " triglistmax="<<triglistmax<<endl;
  }
  
//   cout << "TriggerTermMap found " << _l1termmap.size() << " triggers with "
//        << endl;
//   for (map<string, map<int, string> >::const_iterator it = _l1termmap.begin();
//        it != _l1termmap.end(); ++it)
//     cout << "  " << it->second.size() << " trigger lists for "
// 	 << it->first << endl;
}

  
string TriggerTermMap::getL1Tool(int trigver, string trigname) {
  
  if (!(_l1termmap.find(trigname) != _l1termmap.end() &&
	_l1termmap[trigname].find(trigver) != _l1termmap[trigname].end()))
    cerr << "Warning: TriggerTermMap: "
	 << "  L1Tool not found for trigger "<<trigname
	 << " trigver "<<trigver<<endl;
  
  return _l1termmap[trigname][trigver];
}
  
pair<string, float> TriggerTermMap::getL2Cut(int trigver, string trigname) {

  if (!(_l2termmap.find(trigname) != _l2termmap.end() &&
	_l2termmap[trigname].find(trigver) != _l2termmap[trigname].end()))
    cerr << "Warning: TriggerTermMap: "
	 << "  L2Tool not found for trigger "<<trigname
	 << " trigver "<<trigver<<endl;

  return _l2termmap[trigname][trigver];
}

pair<string, float> TriggerTermMap::getL3Cut(int trigver, string trigname) {

  if (!(_l3termmap.find(trigname) != _l3termmap.end() &&
	_l3termmap[trigname].find(trigver) != _l3termmap[trigname].end()))
    cerr << "Warning: TriggerTermMap: "
	 << "  L3Tool not found for trigger "<<trigname
	 << " trigver "<<trigver<<endl;
  
  return _l3termmap[trigname][trigver];
}

int TriggerTermMap::getnL3Cut(int trigver, string trigname) {

  if (!(_nl3jetsmap.find(trigname) != _nl3jetsmap.end() &&
	_nl3jetsmap[trigname].find(trigver) != _nl3jetsmap[trigname].end()))
    cerr << "Warning: TriggerTermMap: "
	 << "  number of L3 jets not found for trigger "<<trigname
	 << " trigver "<<trigver<<endl;
  
  return _nl3jetsmap[trigname][trigver];
}

int TriggerTermMap::getTriggerVersion(int trigver, string trigname) {

  if (!(_trigvermap.find(trigname) != _trigvermap.end() &&
	_trigvermap[trigname].find(trigver) != _trigvermap[trigname].end()))
    cerr << "Warning: TriggerTermMap: "
	 << " Trigger version not found for trigger "<<trigname
	 << " trigver "<<trigver<<endl;
  
  return _trigvermap[trigname][trigver];
}
  
vector<string> TriggerTermMap::getListOfTriggers() {

  vector<string> triggers;
  for (map<string, map<int, string> >::const_iterator it = _l1termmap.begin();
       it != _l1termmap.end(); ++it) {
    triggers.push_back(it->first);
  }

  return triggers;
}

vector<int> TriggerTermMap::getTriggerListVersionsX100(string trigname) {

  vector<int> trigvers;
  for (map<int, int>::const_iterator it = _trigvermap[trigname].begin();
       it != _trigvermap[trigname].end(); ++it) {
    trigvers.push_back(it->first);
  }

  return trigvers;
}

void TriggerTermMap::dumpConfig() {

//   for (map<string, map<int, string> >::const_iterator it = _l1termmap.begin();
//        it != _l1termmap.end(); ++it) {
//     for (map<int, string>::const_iterator jt = it->second.begin();
// 	 jt != it->second.end(); ++jt) {

//       string trig = it->first;
//       int triglist = jt->first;
//       printf("%s %d %d %s %s %1.0f %s %1.0f %d\n",
// 	     trig.c_str(), triglist,
// 	     _trigvermap[trig][triglist],
// 	     _l1termmap[trig][triglist].c_str(),
// 	     _l2termmap[trig][triglist].first.c_str(),
// 	     _l2termmap[trig][triglist].second,
// 	     _l3termmap[trig][triglist].first.c_str(),
// 	     _l3termmap[trig][triglist].second,
// 	     _nl3jetsmap[trig][triglist]);
//     }
//   }
}

} // namespace caf_trigger

