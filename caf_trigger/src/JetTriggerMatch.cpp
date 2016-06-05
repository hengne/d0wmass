/* File JetTriggerMatch.cpp
 *
 * Created       : Mon Aug 21 10:00:01 CDT 2006
 * Author        : Mikko Voutilainen (mavoutil)
 *
 * Purpose       : This processor returns a list of triggers
 *                 matched and confirmed for each reco jet.
 *                 Only triggers that actually fired are considered.
 *                 The code is partially modeled after
 *                 EMTriggerMatch.cpp.
 *
 * Last modified :
 * Comments      :
*/
#include "caf_trigger/JetTriggerMatch.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

using namespace std;
using cafe::Collection;

namespace caf_trigger {

JetTriggerMatch::JetTriggerMatch(const char *name)
  : cafe::Processor(name)
    ,_varsGlobal("_runno")
    ,_varsTrig("_trgname")
    ,_varsL1("et","eta","ieta","phi")
    ,_varsL2("et","ieta","iphi")
    ,_varsL3("et","eta","phi","toolname")
{

  cafe::Config config(name);
  
  _varsJet.add("fX");
  _varsJet.add("fY");
  _varsJet.add("fZ");
  _varsJet.add("fM");
  _varsJet.add("_deta");
  _varsJet.add("_dphi");

}

void JetTriggerMatch::begin() {
  
  cafe::Config config(name());
  
  vector<string> temp = config.getVString("Triggers", " ,");
  if (temp.size()==0) temp = _trigTerms.getListOfTriggers();
  _triggerNames.insert(temp.begin(), temp.end());
  assert(_triggerNames.size()!=0);

  _jetBranch        = config.get("JetBranch", "JCCB");
  _L1CalTowerBranch = config.get("L1CalTowerBranch", "L1CalTotalTowers");
  _L2JetBranch      = config.get("L2JetBranch", "L2Jet");
  _L3JetBranch      = config.get("L3JetBranch", "L3Jet");

  _confirmL1 = config.get("ConfirmL1", true);
  _confirmL2 = config.get("ConfirmL2", true);
  _confirmL3 = config.get("ConfirmL3", true);

  _L1DeltaR = config.get("L1DeltaR", 0.5);
  _L2DeltaR = config.get("L2DeltaR", 0.5);
  _L3DeltaR = config.get("L3DeltaR", 0.5);

  setDebug(0);
  if (debug()>3)
    dumpConfig();
    _trigTerms.dumpConfig();
}

bool JetTriggerMatch::processEvent(cafe::Event& event) {


  bool matched_trigger = false;
  
  Collection<TMBJet> recojets = event.getJets(_jetBranch, _varsJet);
  Collection<TMBL1CalTower> L1Towers;
  Collection<TMBL1Cal2bJet> L1Jets;
  if (_confirmL1) { 
    L1Towers = event.getCollection<TMBL1CalTower>(_L1CalTowerBranch, _varsL1);
    L1Jets = event.getL1Cal2bJets();
  }
  Collection<TMBL2Jet> L2Jet;
  if (_confirmL2) 
    L2Jet = event.getCollection<TMBL2Jet>(_L2JetBranch, _varsL2);
  Collection<TMBL3Jet> L3Jet;
  if (_confirmL3) 
    L3Jet = event.getCollection<TMBL3Jet>(_L3JetBranch, _varsL3);

  Collection<TMBTrigger> triggers = event.getTriggers(_varsTrig);

  const int trigVer = 
    _trigMap.TriggerX100(event.getGlobal(_varsGlobal)->runno());

  // remove elements from previous event
  _mapConfirmed.clear();

 

  if (debug()>3)
    out() << "JetTriggerMatch["<<name()<<"]: " << event.getGlobal(_varsGlobal)->runno()<< "  "<< event.getGlobal(_varsGlobal)->evtno() << endl;

  // Collect for each reco jet all the triggers that fired and were confirmed 


    for(Collection<TMBTrigger>::const_iterator it = triggers.begin();
	it != triggers.end(); ++it) {
 
 int nL3jets = 0; //number of jets that have passed a given trigger at L3-- can be more than one depending on trigger
    bool confirmed_trig = false;
    int nL3jets_cut; 


      const std::string trigName = it->getTrgName();
 

      if (_triggerNames.find(trigName) != _triggerNames.end()) {
	
     if (debug()>3)
	out() << " trig=" << trigName;

       nL3jets_cut =  _trigTerms.getnL3Cut(trigVer,trigName);
 if (debug()>3)
   out() << " this trigger requires " << nL3jets_cut << " jets." << endl;
 //check of this trigger does not have any jet requirement (e.g. single muon triggers.  If so, pass it
 if( _trigTerms.getL1Tool(trigVer, trigName) == "none" && (_trigTerms.getL2Cut(trigVer,trigName)).first == "none" && (_trigTerms.getL3Cut(trigVer,trigName)).first == "none" ) {
   matched_trigger  = true;
   continue;
 }

  for (Collection<TMBJet>::iterator jetit = recojets.begin();
       jetit != recojets.end(); ++jetit) {

    if (debug()>3)
      out() << "Jet pT= "<<jetit->Pt() << " deteta= " <<jetit->detEta()/10.;

	bool isL1 = false, isL2 = false, isL3 = false;
	if (_confirmL1) {

	  string l1tool = _trigTerms.getL1Tool(trigVer, trigName);
// 	  if (debug()>3)
// 	    out() << " L1("<<_trigTerms.getL1Tool(trigVer, trigName)<<")";
	  isL1 = _l1term.doL1Term(L1Towers, L1Jets, _L1DeltaR, *jetit, l1tool);
	  if (debug()>3)
	    out() << " L1("<<l1tool<<")="<<isL1;
	} 
	if (_confirmL2) {
	  pair<string, float> l2cut = _trigTerms.getL2Cut(trigVer,trigName);
// 	  if (debug()>3)
// 	    out() << " L2("<<_trigTerms.getL2Cut(trigVer, trigName).first<<")";
	  sprintf(_cut_buf, "%1.1f", l2cut.second);
	  isL2 = _l2term.doL2Term(L2Jet, _L2DeltaR, *jetit,
				  l2cut.first, string(_cut_buf));
	  if (debug()>3)
	    out() << " L2("<<l2cut.first<<","<<_cut_buf<<")="<<isL2;
	}
	if (_confirmL3) {
	  pair<string, float> l3cut = _trigTerms.getL3Cut(trigVer,trigName);
// 	  if (debug()>3)
// 	    out() << " L3("<<_trigTerms.getL3Cut(trigVer, trigName).first<<")";



	  sprintf(_cut_buf, "%1.1f", l3cut.second);
	  isL3 = _l3term.doL3Term(L3Jet, _L3DeltaR, *jetit,
				  l3cut.first, string(_cut_buf));
	  if (debug()>3)  out() << " L3("<<l3cut.first<<","<<_cut_buf<<")="<<isL3;

	  if(isL3) nL3jets++;
	}
	
	if (isL1 && isL2 && isL3) confirmed_trig = true;

	if(confirmed_trig && nL3jets >= nL3jets_cut ) {
	  _mapConfirmed[jetit].insert(trigName);
	matched_trigger = true;
	}
	if (debug()>3)
	  out() << " confirmed: " << (isL1 && isL2 && isL3) << endl;
      }
    }
  
    }

  if (debug()>3) {
    out() << "mapConfirmed for " << _mapConfirmed.size() << " jets:" << endl;
    for (map<jet_it, set<string> >::const_iterator it = _mapConfirmed.begin();
	 it != _mapConfirmed.end(); ++it) {
      out() << (it->first - recojets.begin()) << " ";
      for (set<string>::const_iterator jt = it->second.begin();
	   jt != it->second.end(); ++jt) {
	out() << *jt << " ";
      }
      out() << endl;
    }
  }
  
  event.put("mapConfirmed", _mapConfirmed);


   return matched_trigger;
  return true;
}

void JetTriggerMatch::inputFileOpened(TFile *file) {
}

void JetTriggerMatch::inputFileClosing(TFile *file) {
}

void JetTriggerMatch::finish() {
}

void JetTriggerMatch::dumpConfig() {

  out() << "JetTriggerMatch["<<name()<<"]::dumpConfig" << endl;
  out() << "==============================================" << endl;
  out() << " TriggerNames:" << endl;
  for (set<string>::const_iterator it = _triggerNames.begin();
       it != _triggerNames.end(); ++it)
    out() << " " << *it << endl;

  out() << "JetBranch: " << _jetBranch << endl;
  out() << "L1CalTowerBranch: " << _L1CalTowerBranch << endl;
  out() << "L2JetBranch: " << _L2JetBranch << endl;
  out() << "L3JetBranch: " << _L3JetBranch << endl;

  out () << "ConfirmL1: " << _confirmL1 << endl;
  out () << "ConfirmL2: " << _confirmL2 << endl;
  out () << "ConfirmL3: " << _confirmL3 << endl;

  out() << "L1DeltaR: " << _L1DeltaR << endl;
  out() << "L2DeltaR: " << _L2DeltaR << endl;
  out() << "L3DeltaR: " << _L3DeltaR << endl;
  
  out() << "==============================================" << endl;
}

} // namespace caf_trigger

ClassImp(caf_trigger::JetTriggerMatch);

