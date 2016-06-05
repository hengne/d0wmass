#include <iostream>
#include <vector>
#include "wmass_analysis/TrigObjSelector.hpp"

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"

using namespace std;
using namespace cafe;

// Constructor
TrigObjSelector::TrigObjSelector(const char *name):Processor(name) {
  Config config(name);
  
  // debug
  _debugLevel = config.get("debugLevel", 0);

  // minimum pT cut, used to make the code faster
  _TrigObjPtCut_L1 = config.get("TrigObjPtCut_L1", 2.5);
  _TrigObjPtCut_L2 = config.get("TrigObjPtCut_L2", 10.);
  _TrigObjPtCut_L3 = config.get("TrigObjPtCut_L3", 18.);

  _l1_vars.add("et");
  _l1_vars.add("eta");
  _l1_vars.add("phi");

  _l2_vars.add("et");
  _l2_vars.add("ieta");
  _l2_vars.add("iphi");
  _l2_vars.add("iso");
  _l2_vars.add("likelihood");
  

  _l3_vars.add("et");
  _l3_vars.add("eta");
  _l3_vars.add("deteta");
  _l3_vars.add("phi");
  _l3_vars.add("em1width");
  _l3_vars.add("em2width");
  _l3_vars.add("em3width");
  _l3_vars.add("emf");
  _l3_vars.add("em1rescwidth");
  _l3_vars.add("em2rescwidth");
  _l3_vars.add("em3rescwidth");
}

// Destructor
TrigObjSelector::~TrigObjSelector() {}

//
// extract L1/L2/L3 trigger objects
//
void TrigObjSelector::extract(cafe::Event& event) {  
  // do not need to delete useless pointers since they are not created with new
  _l1_trigobjs.clear();
  _l12b_trigobjs.clear();
  _l2_trigobjs.clear();
  _l3_trigobjs.clear();

  
  //get L1 trigger objects
  cafe::Collection<TMBL1CalTower> l1caltowers = event.getL1CalEMTowers(_l1_vars);
  for (Collection<TMBL1CalTower>::iterator it = l1caltowers.begin(); it!= l1caltowers.end(); ++it) {
    if( (*it).Et()>_TrigObjPtCut_L1 ) _l1_trigobjs.push_back(&(*it));
  }

  //get L1 trigger objects
  cafe::Collection<TMBL1Cal2bEM> l1calwindows = event.getL1Cal2bEMs();
  for (Collection<TMBL1Cal2bEM>::iterator it = l1calwindows.begin(); it!= l1calwindows.end(); ++it) {
    if( (*it).Etem()>_TrigObjPtCut_L1 ) _l12b_trigobjs.push_back(&(*it));
  }
  
  //get L2 trigger objects
  cafe::Collection<TMBL2GblEM> l2ems = event.getL2GblEMs(_l2_vars);
  for (Collection<TMBL2GblEM>::iterator it = l2ems.begin(); it!= l2ems.end(); ++it) {
    if( (*it).Et()>_TrigObjPtCut_L2 ) _l2_trigobjs.push_back(&(*it));
  }
  
  //get L3 trigger objects
  cafe::Collection<TMBL3Ele> l3eles = event.getL3Eles(_l3_vars);
  for (Collection<TMBL3Ele>::iterator it = l3eles.begin(); it!= l3eles.end(); ++it) {
    if( (*it).Et()>_TrigObjPtCut_L3 ) _l3_trigobjs.push_back(&(*it));
  }
  
  // print out information for debug purpose
  if(_debugLevel>=15) {
    cout<<"L1 Cal Towers="<<_l1_trigobjs.size()<<" ";
    for(int i=0; i<_l1_trigobjs.size(); i++) {
      cout<<"("<<_l1_trigobjs[i]->Eta()<<" "<<_l1_trigobjs[i]->Phi()<<" "
	  <<_l1_trigobjs[i]->Et()<<") ";
    }
    cout<<endl;
    cout<<"L1 Cal Windows (RunIIb) ="<<_l1_trigobjs.size()<<" ";
    for(int i=0; i<_l12b_trigobjs.size(); i++) {
      cout<<"("<<_l12b_trigobjs[i]->Eta()<<" "<<_l12b_trigobjs[i]->Phi()<<" "
	  <<_l12b_trigobjs[i]->Et()<<") ";
    }
    cout<<endl;
    cout<<"L2 EMs="<<_l2_trigobjs.size()<<" ";
    for(int i=0; i<_l2_trigobjs.size(); i++) {
      cout<<"("<<_l2_trigobjs[i]->Eta()<<" "<<_l2_trigobjs[i]->Phi()<<" "<<_l2_trigobjs[i]->Et()<<") ";
    }
    cout<<endl;
    cout<<"L3 electrons="<<_l3_trigobjs.size()<<" ";
    for(int i=0; i<_l3_trigobjs.size(); i++) {
      cout<<"("<<_l3_trigobjs[i]->DetEta()<<" "<<_l3_trigobjs[i]->Phi()<<" "<<_l3_trigobjs[i]->Et()<<") ";
    }
    cout<<endl;
  } // debug

}

//
// put pointers to event class
//
void TrigObjSelector::putPointers(cafe::Event& event) {
  event.put("L1CalTowers", _l1_trigobjs);
  event.put("L1Cal2bTowers", _l12b_trigobjs);
  event.put("L2GblEMs", _l2_trigobjs);
  event.put("L3Eles", _l3_trigobjs);
}

ClassImp(TrigObjSelector)
