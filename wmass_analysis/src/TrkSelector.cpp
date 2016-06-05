#include <iostream>
#include <vector>
#include "wmass_analysis/TrkSelector.hpp"

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"

using namespace std;
using namespace cafe;

// constructor
TrkSelector::TrkSelector(const char *name):Processor(name) {
  Config config(name);

  // debug level
  _debugLevel = config.get("debugLevel", 0);
  
  // Track selection requirements
  _PtCut_Trk = config.get("PtCut_Trk", 15.);
  _TrkIsolated = config.get("TrkIsolated", false);
  _coneSize_Trk = config.get("coneSize_Trk", 0.2);
  _sumPtCut_Trk = config.get("sumPtCut_Trk", 5.);

  _trk_vars.add("fX");
  _trk_vars.add("fY");
  _trk_vars.add("fZ");
}

// destructor
TrkSelector::~TrkSelector() {}

//
// delete useless pointers from last event
// should be called at the beginning of extract
// should NOT called at the end of extract
//
void TrkSelector::cleanObjects(){
  // delete good tracks
  for(int i=0; i<_good_trks.size(); i++) delete _good_trks[i];
  _good_trks.clear();
}

//
// extract good tracks
//
void TrkSelector::extract(cafe::Event& event) {  
  
  // delete useless pointers from last event
  cleanObjects();
 
  //get tracks from the event
  cafe::Collection<TMBTrack> trks = event.getTracks(_trk_vars);  
  for (Collection<TMBTrack>::iterator it = trks.begin(); it!= trks.end(); ++it) {
    
    if((*it).Pt()>_PtCut_Trk) {
      CAFTrack track(&(*it));
      
      // push back the pointer to the vector
      // have to do this way to avoid memory leak
      if(!_TrkIsolated) {
        _good_trks.push_back(new CAFTrack(&(*it)));
      } else {
        if (track.IsIsolatedTrack(event, _coneSize_Trk, _sumPtCut_Trk)) {
	  _good_trks.push_back(new CAFTrack(&(*it)));
	}
      }
      
    } // pT>_PtCut_Trk
  }
} 

//
// recalculate track properties for different primary vertex
//
void TrkSelector::applyCorrection(cafe::Event& event, float vtx_old[3], float vtx_new[3]) {
  
  for(vector<CAFTrack*>::iterator it=_good_trks.begin(); it!=_good_trks.end(); ++it) 
    (*it)->UpdateForNewVertex(vtx_old, vtx_new);
  
  // print out information
  if(_debugLevel >= 5) {
    cout<<"Good Isolated tracks: " << _good_trks.size()<<endl;
    for(int i=0; i<_good_trks.size(); i++) _good_trks[i]->print();
  }
}

//
// put pointers to event class
//
void TrkSelector::putPointers(cafe::Event& event) {
  event.put("Good Tracks", _good_trks);
}

ClassImp(TrkSelector)
  
