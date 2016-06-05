//file: cafTriggerOutput.cpp
//
//Author:   Kevin Chan
//
//Purpose:  This processor collects the calculations from the probability
//          weight processors and outputs them based on specifications
//          in the config file.
//
//Usage:    Place at the end of a chain in a config file
//          cafTriggerEfficiency(),probProcessor(),cafTriggerOutput()

//Header file for this class
#include "caf_trigger/cafTriggerOutput.hpp"
#include "cafe/Stat.hpp"

using namespace cafe;

cafTriggerOutput::cafTriggerOutput(const char *name)
  : cafe::Processor(name)
{
  //We grab terms from the CAFe configuration file here
  cafe::Config config(name);

  //Debug printout
  std::string debug = config.get("Debug", "no");
  _debug = ( debug == "yes" );

  //This is a setup to grab the histogram information that the
  //user wants to output
  _histosString = config.getVString("histos", " ,");
  _histosBins = config.get("histosBins", 25) ;

  //This will grab the channel the user wishes to put in the
  //global event weight variable
  _globalWeightKey = config.get("globalWeight", "");

  //This is so we don't a bunch of extra work outputting
  //histograms when it isn't required.
  if(_histosString.size() == 0) {
    _histosCheck = false;
  }
  else {
    _histosCheck = true;
  }


}

void cafTriggerOutput::begin()
{

  _passedToProc = false;

  if(_histosCheck) {
        
    //This iterates through the first map to get the
    //name of the channels
    for(std::vector<std::string>::iterator chanMap = _histosString.begin(); chanMap != _histosString.end(); ++chanMap) {

      //We set the title of the histograms here which will
      //go out of scope very fast
      std::string histoAvgName = (*chanMap) + "Average";
      std::string histoAvgTitle = "Event Weights: " + histoAvgName;

      //We now dynamically create histograms for the averages
      _evtwChanVer_h[ (*chanMap) ] = new TH1F( histoAvgName.c_str() , histoAvgTitle.c_str(), _histosBins, -0.1, 1.1);

    }
        
  }
    
}

void cafTriggerOutput::finish()
{
  //Create a few new lines
  std::cout   << std::endl << std::endl
	      << "////////////////////////////////////" << std::endl << std::endl;
    
  for(std::map<std::string, double>::iterator chanMap = _wsum.begin(); chanMap != _wsum.end(); ++chanMap) {
        
    //This is just part of the output
    std::cout   << "Channel: " << (*chanMap).first
		<< " has the following average event weights" << std::endl;

    //We fill some maps with the weights for each event and
    //increment a counter to get the average at the end.
    double evtwChanAvg = _wsum[ (*chanMap).first ]/
      _wint[ (*chanMap).first ];
                
    //And give them to the user
    std::cout   << (*chanMap).first 
		<< ": with all triggerlists: " << evtwChanAvg
		<< std::endl << std::endl;

  }

  //Create the ending lines
  std::cout << std::endl << "////////////////////////////////////" << std::endl;

}

void cafTriggerOutput::inputFileOpened(TFile *file)
{
}
void cafTriggerOutput::inputFileClosing(TFile *file)
{
}

bool cafTriggerOutput::processEvent(cafe::Event &event)
{    
  //Now we create a map to hold the passed event weights
  std::map<std::string, double> mEvtw;
    
  event.get("passedEvtw", mEvtw);

  //Finally this for loop shall fill everything we want it to fill
  //whether it be histograms or audio files with noise.
  for(std::map<std::string, double>::iterator chanMap = mEvtw.begin(); chanMap != mEvtw.end(); ++chanMap) {
        

    //We fill some maps with the weights for each event 
    _wsum[ (*chanMap).first ] += (*chanMap).second;
                        
    //So now we have histograms that we have to create.
    if(_histosCheck) {  
      //This line prevents us from filling a histogram that
      //hasn't been constructed.
      if(_evtwChanVer_h.find( (*chanMap).first ) != _evtwChanVer_h.end()) {

	//And finally we go through our histogram
	//mappings and fill the histograms with the event info.
	_evtwChanVer_h[ (*chanMap).first ]->Fill( (*chanMap).second );
                    
      }//endif      
    }//endif(_histosCheck)
          
    
    //We increment the counter for each channel
    ++_wint[ (*chanMap).first ];

    //This portion here puts (*chanMap).second into the event
    //under the names
    //caf_triggerWeight_Channel
    //caf_triggerWeight_Channel Sigmas: +1
    //caf_triggerWeight_Channel Sigmas: -1

    std::string caf_triggerWeight = "caf_triggerWeight_" + (*chanMap).first;
    float caf_trigWeightFloat = (*chanMap).second;
    event.put(caf_triggerWeight, caf_trigWeightFloat );

    //This is for the global passed weight
    //float globalWeight = 1;
    //event.get("_globalWeightKey", globalWeight);

    if ( _debug ) std::cout << "caf_trigger Weight: " << (*chanMap).first << "\t" << (*chanMap).second << std::endl;
    
    //----------------------------------
    // Store the event weights
    //----------------------------------
    if ( (*chanMap).first == "TriggerProbability" ) {
      event.put("TriggerProbability", caf_trigWeightFloat);
      StatPointer statPointer;
      bool got_it = event.get("StatPointer",statPointer);
      if (!got_it) {
	std::cerr << "caf_trigger::cafTriggerOutput: Cannot access the stat pointer - you must run the Stat processor!" << std::endl;
	exit(1);
      }

      Stat *stat = statPointer.pointer();
      
      stat->applyWeight("TriggerProbability", caf_trigWeightFloat);

      if ( _debug ) std::cout << std::endl << "Apply TriggerWeight: " << caf_trigWeightFloat << std::endl << std::endl;

    }
    else {

      float weight;              
      event.get(caf_triggerWeight, weight);
      if ( _debug ) std::cout << "Saved " << caf_triggerWeight << " : " << weight << std::endl;

    }	

  }//endfor(chanMap)
   
  return true;
}

ClassImp(cafTriggerOutput)

//endfile:
