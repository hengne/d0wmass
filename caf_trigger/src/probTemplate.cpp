//file: probTemplate.cpp {probTemplate.hpp, probTemplate_linkdef.h}
//
//Author:   Kevin Chan
//
//Purpose:  Template plug in processor for calculating the event 
//          weights and the total weights. Inherits from probProcessor.
//
//Usage:
//
//Example:

//Header file for this class
#include "caf_trigger/probTemplate.hpp"

probTemplate::probTemplate(const char *name)
        : probProcessor(name)
{ }

//EffInfo objects are defined here
void probTemplate::defineEffInfo(std::map< std::string, eff_utils::EffInfo >& effInfo)
{

    ////////////////////////////////////////////////////////////
    ///////////////////////Code goes here///////////////////////
    
    //We create an EffInfo request, then shove it in an object
    //with a name of our choosing to be used later on.
    
    effInfo["Template"].EffName("Template");
    effInfo["Template"].EffType("Binned");
    effInfo["Template"].EffVersion(2);

    effInfo["Template"].ObjQuality("LOOSE");
    effInfo["Template"].ObjType("EM");
    effInfo["Template"].ObjVersion(0);

    std::vector< std::string > vars;
    vars.push_back("pt");
  
    effInfo["Template"].EffVarNames( vars );

    ////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//The actual probability calculations are defined here and after calcProb
double probTemplate::calcProb(std::string version)
{
    
    //This sets up the channel name and is important to set!
    _channel = "Template";
    
    double probability = P_Template(version);

    return probability;

}

//This is where you shall be placing your own combinatorics. You'll
//want to read the instructions in doc/readme.html
double probTemplate::P_Template(std::string version)
{
    double probability = 1.0;
    
    double stat = 0.0;

    //Temporary for the Template.
    //This sets up the effInfo version object.

    //This grabs the probability of this template example, which doesn't
    //actually exist!
//    probObject("Template")->getProbability(MU[iobj], stat)

    //Now we just return 1.0    
    return probability;
}

ClassImp(probTemplate)

//endfile:
