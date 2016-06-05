#include "wmass_analysis/VtxSelector.hpp"
#include "wmass_util/BeamSpotManager.hpp"

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"

#include <map>
#include <iostream>

using namespace std;
using namespace cafe;

// Constructor
VtxSelector::VtxSelector(const char *name):Processor(name) {
  Config config(name);

  // debug level
  _debugLevel = config.get("debugLevel", 0);

  _global_vars.add("_runno");
  _PV_vars.add("_VertexX");
  _PV_vars.add("_VertexY");
  _PV_vars.add("_VertexZ");
}

// Destructor
VtxSelector::~VtxSelector() {
}

//
// extract event vertex and track vertex 
//
void VtxSelector::extract(cafe::Event& event, const vector<CAFEMObj*>& emobjs, int& nvtx) {  
 
  // Primary Vertex
  Collection<TMBPrimaryVertex> vertices = event.getPrimaryVertices(_PV_vars);

  // event vertex from the first primary vertex
  nvtx = vertices.size();

  if(nvtx>0) {
    _event_vertex[0] = vertices[0].vx();
    _event_vertex[1] = vertices[0].vy();
    _event_vertex[2] = vertices[0].vz();
  } else {
    _event_vertex[0] = 0.;
    _event_vertex[1] = 0.;
    _event_vertex[2] = 0.;
  }

  if(_debugLevel>=10) cout<<"Old primary vertex="<<_event_vertex[0]<<" "
                          <<_event_vertex[1]<<" "<<_event_vertex[2]<<endl;

  //
  // get beam spot position for this run 
  // and then correct for the beam spot position
  // comment out by J. Zhu on Sep 17, 2006
  // I do not really believe that we need to do this beam spot corrections
  //
  // int runno = event.getGlobal(_global_vars)->runno();
  //   float xoffset=0., yoffset=0., xslope=0., yslope=0.;
  
  //   BeamSpotManager *beamspot_manager = BeamSpotManager::get_instance();
  //   if(beamspot_manager){
  //     const map<int, BEAMSPOT_STRUCT>& beamspot_map = beamspot_manager->BeamSpotMap();
  
  //     map<int, BEAMSPOT_STRUCT>::const_iterator iter = beamspot_map.find(runno);
  //     if(iter != beamspot_map.end()){
  //       xoffset = (*iter).second.xoffset;
  //       yoffset = (*iter).second.yoffset;
  //       xslope = (*iter).second.xslope;
  //       yslope = (*iter).second.yslope;
  //     }
  //   }
  
  // if no tracks found, Z of the track vertex will be the same as that of event vertex
  float vtx_new_z = _event_vertex[2];

  // if two EM clusters have track match, using the average track Z postion
  // if only one EM cluster has track match, just use the track Z position
  // if the track Z position and the D0reco primary vertex are far away from each, 
  // will modify met later in ObjSelector

  if(emobjs.size() >= 1) { // at least one good EM cluster
    bool has_trk1 = emobjs[0]->has_good_spatial_track_match();
    
    if(emobjs.size() >= 2) { // at least two good EM clusters
      bool has_trk2 = emobjs[1]->has_good_spatial_track_match();
      
      if(has_trk1 && has_trk2) {
	vtx_new_z = ( (emobjs[0]->getPtrSpatialChp())->z() + (emobjs[1]->getPtrSpatialChp())->z())/2.;      
      } else if(has_trk1 || has_trk2) {
	if(has_trk1) vtx_new_z = (emobjs[0]->getPtrSpatialChp())->z();
	else vtx_new_z = (emobjs[1]->getPtrSpatialChp())->z();
      }    
    } else if (emobjs.size() == 1) // only one good EM cluster
      if(has_trk1) vtx_new_z = (emobjs[0]->getPtrSpatialChp())->z();
  }

  // find corrected primary vertex 
  //  _track_vertex[0] = xoffset + xslope * vtx_new_z;
  //  _track_vertex[1] = yoffset + yslope * vtx_new_z;
  _track_vertex[0] = _event_vertex[0];
  _track_vertex[1] = _event_vertex[1];
  _track_vertex[2] = vtx_new_z;
  
  if(_debugLevel>=10) cout<<"New primary vertex="<<_track_vertex[0]<<" "
                          <<_track_vertex[1]<<" "<<_track_vertex[2]<<endl;
  
}

//
// put pointers into event class 
//
void VtxSelector::putPointers(cafe::Event& event) {
  event.put("Primary vertexX", _event_vertex[0]);
  event.put("Primary vertexY", _event_vertex[1]);
  event.put("Primary vertexZ", _event_vertex[2]);
  event.put("New primary vertexX", _track_vertex[0]);
  event.put("New primary vertexY", _track_vertex[1]);
  event.put("New primary vertexZ", _track_vertex[2]);
}


ClassImp(VtxSelector)
