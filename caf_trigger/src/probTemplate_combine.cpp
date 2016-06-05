//file: probTemplate_combine.cpp {probTemplate_combine.hpp, probTemplate_combine_linkdef.h}
//
//Author:   Kevin Chan
//
//Purpose:  Template_combine processor for combining L1, L2 and L3.
//          Inherits from probProcessor.
//
//Usage:
//
//Example:

//Header file for this class
#include "caf_trigger/probTemplate_combine.hpp"

probTemplate_combine::probTemplate_combine(const char *name)
        : probProcessor(name)
{
    //We grab terms from the CAFe configuration file here
    cafe::Config config(name);
    
    //Extra parameters for the combination processor
    _combineVStr = config.getVString("combine", ",");

}



//Overrides the inheritance from probProcessor
void probTemplate_combine::eventWeightSigma(std::map<std::string, double> &mRefEvtw)
{
    //This for loop goes through the sigma values
    for(int iValue = 0; iValue < 2; ++iValue) {

        sigmaQuad quadrature = sigmaQuad();

        //This loop is used to combine the various levels
        for(int iLevel = 0; iLevel < _combineVStr.size(); ++iLevel) {
        
            //This will multiply out whatever our vector of strings has
            //chosen. This may be L1*L2, L1*L2*L3, L1*L3, etc.
            std::string tmpLevel = _combineVStr[iLevel];
            
            //We need to convert the sigma values to a string
            //using <sstream> and <iostream>
            std::stringstream convertSigmaValue;
            convertSigmaValue << _sigmaValue[iValue];

            std::string mapNameSigma;
                
            if(_sigmaValue[iValue] == 1) {

                mapNameSigma = tmpLevel + " Sigmas: " 
                                + "+" + convertSigmaValue.str();

            }
            else {
                
                mapNameSigma = tmpLevel + " Sigmas: " 
                                + convertSigmaValue.str();

            }
            
            quadrature.sigmaAddQuad( mRefEvtw[ mapNameSigma ] );

        }//endfor(iLevel)

        //We need to convert the sigma values to a string
        //using <sstream> and <iostream>
        std::stringstream convertSigmaValue;
        convertSigmaValue << _sigmaValue[iValue];

        std::string mapName;
            
        if(_sigmaValue[iValue] == 1) {

            mapName = _channel + " Sigmas: " 
                            + "+" + convertSigmaValue.str();

        }
        else {
                
            mapName = _channel + " Sigmas: " 
                            + convertSigmaValue.str();

        }
            
        double revtw = quadrature.sigmaGetQuad();
        
        //And putting it in the referenced map
        mRefEvtw[ mapName ] = revtw;
        
    }//endfor(iValue)


}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
double probTemplate_combine::calcProb(std::string version)
{
    
    //This sets up the channel name and is important to set!
    _channel = "Template_combine";
    
    double probability = P_Template_combine(version);

    return probability;

}

double probTemplate_combine::P_Template_combine(std::string version)
{
    double probability = 1.0;
    
    //We make a copy of mEvtw for safety
    std::map<std::string, double> mEvtwCopy = mEvtw;

    //Now we can use it to combine whichever variables we wanted.
    for(int iLevel = 0; iLevel < _combineVStr.size(); ++iLevel) {
        
        //This will multiply out whatever our vector of strings has
        //chosen. This may be L1*L2, L1*L2*L3, L1*L3, etc.
        std::string tmpLevel = _combineVStr[iLevel];

        probability *= mEvtwCopy[ tmpLevel ];
        
    }
    
    return probability;
}

ClassImp(probTemplate_combine)

//endfile:
