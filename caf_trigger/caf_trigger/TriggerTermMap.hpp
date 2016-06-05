/* File TriggerTermMap.hpp
 *
 * Created       : August 21, 2006
 * Author        : Mikko Voutilainen (mavoutil)
 *
 * Purpose       : Match trigger version and trigger to
 *                 corresponding L1tool, L2tool+cut and
 *                 L3tool+cut. Used in JetTriggerMatch.cpp.
 *                 The mappings are given in a text file,
 *                 parameters/triggerterms.txt by default.
 *                 Modeled after TriggerTerm.hpp.
 *
 * Last modified : 
 * Comments      : 
 *
 *   The information was queried using Trigger Database Report Interface
 *   http://www-d0.fnal.gov/trigger_meister/private/trigdb/tdb_front.html
 *
 *   To find triggers (and their versions) used in physics runs
 *   TRIGGER List: global_CMT
 *   TRIGGER Name: <trigname>
 *   <Click on Trigger Name>
 *
 *   To match trigger versions to trigger lists
 *   TRIGGER List: global_CMT
 *   Trigger Name: <trigname> Version: <version>
 *   <Click on Trigger List>
 *                
 * History       : 
 *
 */



#ifndef TriggerTermMap_HPP_
#define TriggerTermMap_HPP_

#include <map>
#include <vector>
#include <string>

namespace caf_trigger {
  
  class TriggerTermMap{
  public:
    
    // Constructor, destructor: 
    TriggerTermMap() {BuildMap("caf_trigger/parameters/triggerterms.txt");};
    TriggerTermMap(char *filename) {BuildMap(filename);};
    ~TriggerTermMap() {};
    std::string getL1Tool(int trigver, std::string trigname);
    std::pair<std::string, float> getL2Cut(int trigver, std::string trigname);
    std::pair<std::string, float> getL3Cut(int trigver, std::string trigname);
    int getTriggerVersion(int trigver, std::string trigname);
    std::vector<std::string> getListOfTriggers();
    std::vector<int> getTriggerListVersionsX100(std::string trigname);
    void dumpConfig();

    int getnL3Cut(int trigver, std::string trigname);
  private:

    void BuildMap(char *filename);

    std::map<std::string, std::map<int, int> > _trigvermap;
    std::map<std::string, std::map<int, std::string> > _l1termmap;
    std::map<std::string, std::map<int, std::pair<std::string, float> > > _l2termmap;
    std::map<std::string, std::map<int, std::pair<std::string, float> > > _l3termmap;
    std::map<std::string, std::map<int, int> > _nl3jetsmap;

  }; // class TriggerTermMap
  
} // namespace caf_trigger {

#endif
