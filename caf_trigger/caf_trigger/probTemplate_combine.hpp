//file: probTemplate_combine.hpp {probTemplate_combine.cpp}
//
//Author:   Kevin Chan
//
//Purpose:  Header file for the plugin processor probTemplate_combine
//          Inherits from probProcessor.

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"

using namespace cafe;

class objectProbabilities;

//Inherits from probProcessor
class probTemplate_combine : public probProcessor
{
public:
    probTemplate_combine(const char *name);

    //Overrides eventWeightSigma from probProcessor
    void eventWeightSigma(std::map<std::string, double> &mRefEvtw);
    

////////////////////////////////////////////////////////////

    //Define your effInfo objects here
    void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &effInfo) {};

    
    //These methods define the probability calculations
    double calcProb(std::string version);

    double P_Template_combine(std::string version);


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

    ClassDef(probTemplate_combine, 0);
private:

    //Extra parameters for the combination processor.
    std::vector< std::string >  _combineVStr;

};

//endfile:
