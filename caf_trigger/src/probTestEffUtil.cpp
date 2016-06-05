//file: probTestEffUtil.cpp {probTestEffUtil.hpp, probTestEffUtil_linkdef.h}
//
//Author:   Kevin Chan
//
//Purpose:  TestEffUtil plug in processor for calculating the event 
//          weights and the total weights. Inherits from probProcessor.
//
//Usage:
//
//Example:

//Header file for this class
#include "caf_trigger/probTestEffUtil.hpp"

probTestEffUtil::probTestEffUtil(const char *name)
        : probProcessor(name)
{ }

//EffInfo objects are defined here
void probTestEffUtil::defineEffInfo(std::map< std::string, eff_utils::EffInfo >& effInfo)
{

    ////////////////////////////////////////////////////////////
    ///////////////////////Code goes here///////////////////////
    
    //We create an EffInfo request, then shove it in an object
    //with a name of our choosing to be used later on.
    
    effInfo["gaus"].ObjType("EM");
    effInfo["gaus"].ObjQuality("Tight");
    effInfo["gaus"].ObjVersion(8);
        
    effInfo["gaus"].EffType("Binned");
    effInfo["gaus"].EffVersion(0);
    effInfo["gaus"].EffName("gaus");

    std::vector< std::string > vars;
    vars.push_back("eta");
  
    effInfo["gaus"].EffVarNames( vars );

    ////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//The actual probability calculations are defined here and after calcProb
double probTestEffUtil::calcProb(std::string version)
{
    
    //This sets up the channel name and is important to set!
    _channel = "TestEffUtil";
    
    double probability = P_TestEffUtil(version);

    return probability;

}

double probTestEffUtil::P_TestEffUtil(std::string version)
{
    double probability = 1.0;
    
    double stat = 0.0;

    //Temporary for the TestEffUtil.
    probability = probObject("gaus")->getProb1Objects(EM);
    
    return probability;
}

ClassImp(probTestEffUtil)

//endfile:
