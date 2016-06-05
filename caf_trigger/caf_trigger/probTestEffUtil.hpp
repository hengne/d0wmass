//file: probTestEffUtil.hpp {probTestEffUtil.cpp}
//
//Author:   Kevin Chan
//
//Purpose:  Header file for the plugin processor probTestEffUtil

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"


//Inherits from probProcessor
class probTestEffUtil : public probProcessor
{
public:
    probTestEffUtil(const char *name);

    
////////////////////////////////////////////////////////////
    
    //Define your effInfo objects here
    void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &effInfo);

    
    //These methods define the probability calculations
    double calcProb(std::string version);

    double P_TestEffUtil(std::string version);


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

    ClassDef(probTestEffUtil, 0);
};

//endfile:
