//file: probQCDJet.cpp {probQCDJet.hpp, probQCDJet_linkdef.h}
//
//Author:   Kevin Chan
//
//Purpose:  QCDJet plug in processor for calculating the event 
//          weights and the total weights. Inherits from probProcessor.
//
//Usage:
//
//Example:

//Header file for this class
#include "caf_trigger/probQCDJet.hpp"

using std::map;
using std::set;
using std::endl;
using std::vector;
using std::string;
using eff_utils::EffInfo;
using caf_trigger::TriggerTermMap;

probQCDJet::probQCDJet(const char *name)
        : probProcessor(name)
{ }

//EffInfo objects are defined here
void probQCDJet::defineEffInfo(std::map< std::string, eff_utils::EffInfo >& effInfo)
{

  ////////////////////////////////////////////////////////////
  ///////////////////////Code goes here///////////////////////
  
  if (debug() > 3)
    _trigTerms.dumpConfig();
  vector<string> triggers = _trigTerms.getListOfTriggers();
  _triggerNames.insert(triggers.begin(), triggers.end());
  
  //We create an EffInfo request, then shove it in an object
  //with a name of our choosing to be used later on.
  
  // Fill the object qualities for unique trigger versions
  for (int itrig = 0; itrig != triggers.size(); ++itrig) {
    
    string trigname = triggers[itrig];
    vector<int> trigvers = _trigTerms.getTriggerListVersionsX100(trigname);
    for (int iver = 0; iver != trigvers.size(); ++iver) {
      
      int trigver = trigvers[iver];
      string infoname = Form("%s_%d",trigname.c_str(),
			     _trigTerms.getTriggerVersion(trigver, trigname));
      if (effInfo.find(infoname) == effInfo.end()) {
	
	string objquality =
	  Form("%s_%s_%1.0f_%s_%1.0f",
	       _trigTerms.getL1Tool(trigver, trigname).c_str(),
	       _trigTerms.getL2Cut(trigver, trigname).first.c_str(),
	       _trigTerms.getL2Cut(trigver, trigname).second,
	       _trigTerms.getL3Cut(trigver, trigname).first.c_str(),
	       _trigTerms.getL3Cut(trigver, trigname).second);
	effInfo[infoname].ObjQuality(objquality);
      }
      
    } // for trigver
  } // for itrig
  
    //effInfo["JT_8TT"].ObjQuality("CJT(1,5)_ncu_none_0_SCJET_8_8");
    //effInfo["JT_15TTa"].ObjQuality("CJT(2,3)CJT(1,5)_none_0_SCJET_8_15");
    //effInfo["JT_15TTb"].ObjQuality("CJT(2,3)_ncu_none_0_SCJET_8_15");
  
  std::vector< std::string > vars;
  vars.push_back("deteta");
  vars.push_back("pt");
  
  // Fill in the common stuff in a loop
  for (map<string, EffInfo>::iterator it = effInfo.begin();
       it != effInfo.end(); ++it) {
    
    it->second.EffMethod("Ratio");
    it->second.EffName("TrigEff");
    it->second.EffType("Binned");
    it->second.EffVersion(-1);
    
    it->second.ObjRelativeTo("goodJet");
    it->second.ObjType("Jet");
    it->second.ObjVersion(-1);
    it->second.TriggerVersion("v000");
    it->second.EffVarNames( vars );
  }
  
  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////
  
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//The actual probability calculations are defined here and after calcProb
double probQCDJet::calcProb(std::string version)
{
    
    //This sets up the channel name and is important to set!
    _channel = "QCDJet";
    
    double probability = P_QCDJet(version);

    return probability;

}

//This is where you shall be placing your own combinatorics. You'll
//want to read the instructions in doc/readme.html
//This routine is not doing anything very useful now
double probQCDJet::P_QCDJet(std::string version)
{
    double probability = 1.0;
    
    double stat = 0.0;

    if (JET.size() != 0)
      probability = probObject("JT_8TT")->getProbability(JET[0], stat, isRun2b);

    if (debug() > 3)
      out() << "Efficiency : " << probability
	    << "(jet pt " << JET[0].Pt()
	    << " deteta " << JET[0].deta()
	    << " actas " << JET[0].CurrentlyActAs() << ")" << endl;

    return probability;
}

// Match the trigger and run number to efficiency Info name
string probQCDJet::findEffInfoName(string trigname, int run) {

  const int trigVer = _trigMap.TriggerX100(run);
  
  return Form("%s_%d", trigname.c_str(),
	      _trigTerms.getTriggerVersion(trigVer,trigname));
}

// Override probProcessor::processEvent to get access to run and trigger info
bool probQCDJet::processEvent(Event &event) {

  _corrfactors.clear();
  //_derivatives.clear();
                                                                               
  //We grab the stats pointer from the event
  //    StatPointer _stat;
                                                                               
  //We grab the stats pointer from the event
  //    event.get("StatPointer", _stat);

  //Get the passed TObject information
  event.get("passedJET", JET);

  // Make sure jets are uncorrected, that's the way there were parametrized
  for (int ijet = 0; ijet != JET.size(); ++ijet)
    JET[ijet].ActAsUnCorrected();

  // Get additional trigger and run information
  cafe::Collection<TMBTrigger> triggers = event.getTriggers();//_varsTrig);
  const TMBGlobal *global = event.getGlobal();//_varsGlobal);

  // Select all jet triggers that fired
  vector<string> trignames;
  for (cafe::Collection<TMBTrigger>::const_iterator trig = triggers.begin();
       trig != triggers.end(); ++trig)
    if (_triggerNames.find(trig->getTrgName()) != _triggerNames.end())
      trignames.push_back(trig->getTrgName());

  // For selected jet triggers, find correct probability object
  map<string, const objectProbabilities*> probObjs;
  for (int i = 0; i != trignames.size(); ++i)
    probObjs[trignames[i]] = 
      probObject( findEffInfoName(trignames[i], global->runno()) );

  // Use probability objects to calculate trigger efficiency per jet
  map<string, const objectProbabilities*>::iterator it_prob = 0;
  for (it_prob = probObjs.begin(); it_prob != probObjs.end(); ++it_prob) {

    for (int ijet = 0; ijet != JET.size(); ++ijet) {

      EffVal eff;
      double stat = 0;
      it_prob->second->getProbability(JET[ijet], stat, eff, isRun2b);
      _corrfactors[it_prob->first].push_back(eff);
    }
  } // prob_it

  //Pass full object weight information to event
  for (map<string, vector<EffVal> >::iterator it = _corrfactors.begin();
       it!=_corrfactors.end(); ++it) {
    if (it->second.size()>0) {
      event.put(name()+":weight_vector_"+it->first,it->second);

    if (debug() > 3 && JET.size() != 0 && it->second.size() != 0)
      out () << 
	Form("Efficiency  %10s: %4.3f (jet pt %3.1f deteta %5.2f actas %d)",
	     it->first.c_str(), it->second[0].val,
	     JET[0].Pt(), JET[0].deta()*0.1, JET[0].CurrentlyActAs()) << endl;
    if (debug() > 3 && JET.size() >= 2 && it->second.size() >= 2)
      out () << 
	Form("Efficiency2 %10s: %4.3f (jet pt %3.1f deteta %5.2f actas %d)",
	     it->first.c_str(), it->second[1].val,
	     JET[1].Pt(), JET[1].deta()*0.1, JET[1].CurrentlyActAs()) << endl;
    }
  }

  return true;
}

ClassImp(probQCDJet)

//endfile:
