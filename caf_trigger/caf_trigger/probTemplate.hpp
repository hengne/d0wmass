//file: probTemplate.hpp {probTemplate.cpp}
//
//Author:   Kevin Chan
//
//Purpose:  Header file for the plugin processor probTemplate.
//          Inherits from probProcessor.

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"

//Inherits from probProcessor
class probTemplate : public probProcessor
{
public:
    probTemplate(const char *name);

    
////////////////////////////////////////////////////////////

    //Define your effInfo objects here
    void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &effInfo);


    //These methods define the probability calculations
    double calcProb(std::string version);

    double P_Template(std::string version);


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

    ClassDef(probTemplate, 0);
};

//endfile:
