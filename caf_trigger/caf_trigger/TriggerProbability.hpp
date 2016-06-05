//file: TriggerProbability.hpp {TriggerProbability.cpp}
//
//Author:   Thomas Gadfort (tgadfort@fnal.gov)
//
//Purpose:  Header file for the plugin processor TriggerProbability

//Inherit probProcessor virtual abstracts
#include "caf_trigger/probProcessor.hpp"

using namespace cafe;

class objectProbabilities;

//Inherits from probProcessor
class TriggerProbability : public probProcessor
{
public:
    TriggerProbability(const char *name);

    //Overrides eventWeightSigma from probProcessor
    void eventWeightSigma(std::map<std::string, double> &mRefEvtw);

    
////////////////////////////////////////////////////////////

    //Define your effInfo objects here
    void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &effInfo) {};

    
    //These methods define the probability calculations
    double calcProb(std::string version);

    double P_Trigger(std::string version);

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

    ClassDef(TriggerProbability, 0);
private:

    //Extra parameters for the combination processor.
    std::vector< std::string >  _combineVStr;

};

//endfile:
