//file: probQCDJet.hpp {probQCDJet.cpp}
//
//Author:   Kevin Chan
//
//Purpose:  Header file for the plugin processor probQCDJet.
//          Inherits from probProcessor.

#ifndef probQCDJet_hpp
#define probQCDJet_hpp

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"

#include "caf_trigger/TriggerMap.hpp"
#include "caf_trigger/TriggerTermMap.hpp"

#include <set>
#include <map>
#include <vector>

//Inherits from probProcessor
class probQCDJet : public probProcessor
{
public:
    probQCDJet(const char *name);
    bool processEvent(cafe::Event &event);
    
////////////////////////////////////////////////////////////

    //Define your effInfo objects here
    void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &effInfo);


    //These methods define the probability calculations
    double calcProb(std::string version);

    double P_QCDJet(std::string version);

    std::string findEffInfoName(std::string trigname, int run);

private:

  std::set<std::string> _triggerNames;
  TriggerMap _trigMap; // use the default file location
  caf_trigger::TriggerTermMap _trigTerms; // use the default file location

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
public:
    ClassDef(probQCDJet, 0);
};

//endfile:
#endif // probQCDJet_hpp
