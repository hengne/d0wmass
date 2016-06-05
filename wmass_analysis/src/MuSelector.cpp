#include <iostream>
#include <vector>
#include "wmass_analysis/MuSelector.hpp"

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "tmb_tree/TMBTrack.hpp"

using namespace std;
using namespace cafe;

// Constructor
MuSelector::MuSelector(const char *name):Processor(name) {
  Config config(name);
  
  _debugLevel = config.get("debugLevel", 0);

  _muon_vars.add("_nseg");
  _muon_vars.add("_chptr");
  _muon_vars.add("_isTight");
  _muon_vars.add("_isCosmic");
  _muon_vars.add("fX");
  _muon_vars.add("fY");
}

// Destructor
MuSelector::~MuSelector() {}

//
// delete useless pointers from last event
// should be called at the beginning of extract
// should NOT called at the end of extract
//
void MuSelector::cleanObjects(){
  for(int i=0; i<_good_muons.size(); i++) delete _good_muons[i];
  _good_muons.clear();
}

//
// extract good Muon candidates
//
void MuSelector::extract(cafe::Event& event) {  
  
  // delete useless pointers from last event
  cleanObjects();
  
  // select good muon candiates
  cafe::Collection<TMBMuon> muons = event.getMuons(_muon_vars);
  for (Collection<TMBMuon>::iterator it = muons.begin(); it!= muons.end(); ++it) {    
    
    // only look at very good muons with 3 segments, pT>2 and in central region
    if((*it).nseg()>=3 && (*it).Pt()>2.) {
//    if((*it).nseg()>=3 && (*it).Pt()>2. && (*it).region()==0) {
      TMBTrack *trk=(*it).GetChargedTrack();
      if((trk->nsmt()>=1) && (trk->ncft()>=9)) {
	_good_muons.push_back(new CAFMuon(&(*it)));
      } // smt and cft hits
    } // muon quality cuts
    
  } // loop over all muons 
  
  // sort muons
  sort(_good_muons.begin(), _good_muons.end(), ComparePt);
  
  if(_debugLevel>=5) {
    cout<<"# of muons: "<<_good_muons.size()<<endl;
    for(int i=0; i<_good_muons.size(); i++)
      cout<<"pT,isTight,isCosmic = "<<_good_muons[i]->Pt()
	  <<" "<<_good_muons[i]->isTight()<<" "<<_good_muons[i]->isCosmic()<<endl;
  }//debug
}

//
// recalculate muon candidate properties for different primary vertex
//
void MuSelector::applyCorrection(cafe::Event& event, float vtx_old[3], float vtx_new[3]) {
  
}

//
// put pointers to event class
void MuSelector::putPointers(cafe::Event& event) {
  event.put("Good Muons", _good_muons);
}

ClassImp(MuSelector)
  
