//file: TriggerProbability.cpp {TriggerProbability.hpp, TriggerProbability_linkdef.h}
//
//Author:   Thomas Gadfort (tgadfort@fnal.gov)
//
//Purpose:  TriggerProbability processor for combining L1/L2/L3 terms
//
//Usage:
//
//Example:

//Header file for this class
#include "caf_trigger/TriggerProbability.hpp"

TriggerProbability::TriggerProbability(const char *name)
        : probProcessor(name)
{
    //We grab terms from the CAFe configuration file here
    cafe::Config config(name);

    //Extra parameters for the combination processor
    _combineVStr = config.getVString("CombineL1L2L3", ",");

}

//Overrides the inheritance from probProcessor
void TriggerProbability::eventWeightSigma(std::map<std::string, double> &mRefEvtw)
{
    //This for loop goes through the sigma values
    for(int iValue = 0; iValue < 2; ++iValue) {

        sigmaQuad quadrature = sigmaQuad();
        
        //This loop is used to combine the various levels
        for(int iLevel = 0; iLevel < _combineVStr.size(); ++iLevel) {
        
            //This will multiply out whatever our vector of strings has
            //chosen. This may be L3*L2, L3*L2*L3, L3*L3, etc.
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

            quadrature.sigmaAddQuad( mRefEvtw[ mapNameSigma ] - mRefEvtw[ tmpLevel ] );

        }//endfor(iLevel)

        //We need to convert the sigma values to a string
        //using <sstream> and <iostream>
        std::stringstream convertSigmaValue;
        convertSigmaValue << _sigmaValue[iValue];

        std::string mapName;
        
        //Set up the double returned event weight    
        double revtw;
        
        if(_sigmaValue[iValue] == 1) {

            //Add the quadrature
            revtw = mRefEvtw[ _channel ] + quadrature.sigmaGetQuad();

            mapName = _channel + " Sigmas: " 
                            + "+" + convertSigmaValue.str();

        }
        else {

            //Subtract the quadrature
            revtw = mRefEvtw[ _channel ] - quadrature.sigmaGetQuad();
                
            mapName = _channel + " Sigmas: " 
                            + convertSigmaValue.str();

        }

        //And putting it in the referenced map
        mRefEvtw[ mapName ] = revtw;
        
    }//endfor(iValue)


}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
double TriggerProbability::calcProb(std::string version)
{
    
    //This sets up the channel name and is important to set!
    _channel = "TriggerProbability";

    double probability = P_Trigger(version);

    return probability;

}

double TriggerProbability::P_Trigger(std::string version)
{
    double probability = 1.0;

    //We make a copy of mEvtw for safety
    std::map<std::string, double> mEvtwCopy = mEvtw;

    //Now we can use it to combine whichever variables we wanted.
    for(int iLevel = 0; iLevel < _combineVStr.size(); ++iLevel) {

        //MegaOR? stop right here!
    	if ( _combineVStr[iLevel].find("MegaOR") != std::string::npos ) return 1.0;
        
        //This will multiply out whatever our vector of strings has
        //chosen. This may be L3*L2, L3*L2*L3, L3*L3, etc.
        std::string tmpLevel = _combineVStr[iLevel];

        probability *= mEvtwCopy[ tmpLevel ];
        
    }
    
    return probability;
}

ClassImp(TriggerProbability)

//endfile:

