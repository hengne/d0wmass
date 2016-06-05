#include "wmass_analysis/ObjSelector.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"

#include <iostream>

using namespace std;
using namespace cafe;

// Constructor
ObjSelector::ObjSelector(const char *name)
  : Processor(name)
{
  Config config(name);
  
  // debug Level
  _debugLevel = config.get("debugLevel", 0);
  
  // muon channel
  _doMuon = config.get("doMuon", false);

  // MC study
  _MCStudy = config.get("MCStudy", false);
  _dump_mctruth = config.get("dump_mctruth", false);
  _MCStudy_ZNuNu = config.get("MCStudy_ZNuNu", false);
  if(_MCStudy_ZNuNu && _doMuon) {
    cerr << "ObjSelector: doMuon and MCStudy_ZNuNu switches are mutually exclusive !!!" << endl
	 << "             doMuon        = " << _doMuon << endl
	 << "             MCStudy_ZNuNu = " << _MCStudy_ZNuNu << endl;
    throw;
  }

  _extractTriggerObjects = config.get("extractTriggerObjects", false);

  // primary/MC vertex cut
  _VtxCut      = config.get("VtxCut", 60.);  // cut on |Z| coordinate of d0reco PV or MC vertex
  _NumVtxCut   = config.get("NumVtxCut", 1); // minimal numer of d0reco vertices present
  _useMCvertex = config.get("useMCvertex", false); // if set to true, then MC vertex wille be
                                                   // used instead of the d0reco PV 
                                                   // (in such a case NumVtxCut is void,
                                                   // VtxCut will be applied to true MC vertex)
  if(!_MCStudy_ZNuNu && _useMCvertex) {
    cerr << "ObjSelector: Currently true MC vertex can be used only in Z->nunu mode !!!" << endl
	 << "             VtxFromMC     = " << _useMCvertex << endl
	 << "             MCStudy       = " << _MCStudy << endl
	 << "             MCStudy_ZNuNu = " << _MCStudy_ZNuNu << endl;
    throw;
  }

  // "SCA" kill list
  _excludeSCAfailures = config.get("excludeSCAfailures", false);
  if (_excludeSCAfailures) initialiseKillList();

  // FSR selection
  _cutOnLeadingFSR = config.get("cutOnLeadingFSR", false);
  _LeadingFSR_ETmin = config.get("LeadingFSR_ETmin",-1.);
  _LeadingFSR_ETmax = config.get("LeadingFSR_ETmax",9999999.);
  _LeadingFSR_dRmin = config.get("LeadingFSR_dRmin",-1.);
  _LeadingFSR_dRmax = config.get("LeadingFSR_dRmax",9999999.);
  _LeadingFSR_xmin = config.get("LeadingFSR_xmin",-1.);
  _LeadingFSR_xmax = config.get("LeadingFSR_xmax",2.);
  _cutOnTrailingFSR = config.get("cutOnTrailingFSR", false);
  _TrailingFSR_ETmin = config.get("TrailingFSR_ETmin",-1.);
  _TrailingFSR_ETmax = config.get("TrailingFSR_ETmax",9999999.);
  _cutOnFSRnPhot = config.get("cutOnFSRnPhot", false);
  _FSR_nPhot_min = config.get("FSR_nPhot_min",-1);
  _FSR_nPhot_max = config.get("FSR_nPhot_max",9999);

  // True WZ selection
  _cutOnTrueWZPt = config.get("cutOnTrueWZPt", false);
  _TrueWZPtCut_Lo = config.get("TrueWZPtCut_Lo", -1.);
  _TrueWZPtCut_Hi = config.get("TrueWZPtCut_Hi", 99990.0);
  _cutOnTrueWZPhi = config.get("cutOnTrueWZPhi", false);
  _TrueWZPhiCut_Lo = config.get("TrueWZPhiCut_Lo", -1.0);
  _TrueWZPhiCut_Hi = config.get("TrueWZPhiCut_Hi", 7.0);  
  _cutOnTrueWZMass = config.get("cutOnTrueWZMass", false);
  _TrueWZMassCut_Lo = config.get("TrueWZMassCut_Lo", -1.);
  _TrueWZMassCut_Hi = config.get("TrueWZMassCut_Hi", 99990.0);

  // initialize TrigObjSelector, EMSelector, TrkSelector and MetSelector or MuSelector
  if(_doMuon) {
    _muselector = new MuSelector(name);
    _trigobjselector = NULL;
    _emselector = NULL;
    _trkselector = NULL;
    _metselector = NULL;
    _vtxselector = NULL;
    _mcselector = NULL;
  } if (_MCStudy_ZNuNu) {
    _trigobjselector = NULL;
    _emselector = new EMSelector(name);
    _trkselector = new TrkSelector(name);
    _metselector = new MetSelector(name);
    _vtxselector = new VtxSelector(name);
    _muselector = NULL;
    _mcselector = NULL;
  } else {
    _trigobjselector = new TrigObjSelector(name);
    _emselector = new EMSelector(name);
    _trkselector = new TrkSelector(name);
    _metselector = new MetSelector(name);
    _vtxselector = new VtxSelector(name);
    _muselector = NULL;
    _mcselector = NULL;
  }
  
  if(_MCStudy || _MCStudy_ZNuNu) _mcselector = new MCSelector(name);;
  
  // revertexing, will be very slow
  _ReVertexing = config.get("ReVertexing", false);

  // revertexing condition
  _PV_displaced_Limit = config.get("PV_displaced_Limit", 2.);
  
  // event counter
  _events = 0;
  _events_fail_vtxcut = 0;
  _events_fail_FSRcut = 0;
}

// Destructor
ObjSelector::~ObjSelector() {
  if(_trigobjselector!=NULL) delete _trigobjselector;
  if(_emselector!=NULL) delete _emselector;
  if(_muselector!=NULL) delete _muselector;
  if(_trkselector!=NULL) delete _trkselector;
  if(_metselector!=NULL) delete _metselector;
  if(_vtxselector!=NULL) delete _vtxselector;
  if(_mcselector!=NULL) delete _mcselector;
}

// Process event
bool ObjSelector::processEvent(Event& event)
{ 
  _events ++;
  //  cout<<"ObjSelector::processEvent: "<<_events<<endl;

  // Study Geant MC simulation
  if(_MCStudy || _MCStudy_ZNuNu) {
    _mcselector->extract(event);
    if (_cutOnLeadingFSR) {
      _events_fail_FSRcut++;
      if (_mcselector->LeadFSR_ET()<_LeadingFSR_ETmin) return false;
      if (_mcselector->LeadFSR_ET()>_LeadingFSR_ETmax) return false;
      if (_mcselector->LeadFSR_dR()<_LeadingFSR_dRmin) return false;
      if (_mcselector->LeadFSR_dR()>_LeadingFSR_dRmax) return false;
      if (_mcselector->LeadFSR_x()<_LeadingFSR_xmin) return false;
      if (_mcselector->LeadFSR_x()>_LeadingFSR_xmax) return false;
      _events_fail_FSRcut--;
    }
    if (_cutOnTrailingFSR) {
      _events_fail_FSRcut++;
      if (_mcselector->TrailFSR_ET()<_TrailingFSR_ETmin) return false;
      if (_mcselector->TrailFSR_ET()>_TrailingFSR_ETmax) return false;
      _events_fail_FSRcut--;
    }
    if (_cutOnFSRnPhot) {
      _events_fail_FSRcut++;
      if (_mcselector->FSR_nPhot()<_FSR_nPhot_min) return false;
      if (_mcselector->FSR_nPhot()>_FSR_nPhot_max) return false;
      _events_fail_FSRcut--;
    }
    if (_cutOnTrueWZPt) {
      if(_mcselector->TrueWZPt()<_TrueWZPtCut_Lo) return false;
      if(_mcselector->TrueWZPt()>_TrueWZPtCut_Hi) return false;
    }
    if (_cutOnTrueWZPhi) {
      if(_mcselector->TrueWZPhi()<_TrueWZPhiCut_Lo) return false;
      if(_mcselector->TrueWZPhi()>_TrueWZPhiCut_Hi) return false;
    }
    if (_cutOnTrueWZMass) {
      if(_mcselector->TrueWZMass()<_TrueWZMassCut_Lo) return false;
      if(_mcselector->TrueWZMass()>_TrueWZMassCut_Hi) return false;
    }
    if (_dump_mctruth){
      TMBMCpart* WZ=NULL;
      std::vector<TMBMCpart *> raw_mc_electrons;
      std::vector<TMBMCpart *> raw_mc_photons;
      std::vector<TMBMCpart *> good_mc_emobjs;
      if ( event.get("WZ boson object", WZ) && event.get("raw mc electrons", raw_mc_electrons) && event.get("em mc objects", good_mc_emobjs) && event.get("raw mc photons", raw_mc_photons)) {
        std::cout << "DT " << _events << " " << "WZ " << WZ->pdgid() << " " << WZ->E() << " " << WZ->Px() << " " << WZ->Py() << " " << WZ->Pz() << " "
                  << WZ->getDMCvtx()->ct() << " " << WZ->getDMCvtx()->x() << " " << WZ->getDMCvtx()->y() << " " << WZ->getDMCvtx()->z() << " " << std::endl;
        for (vector<TMBMCpart*>::iterator it = raw_mc_electrons.begin(); it != raw_mc_electrons.end(); ++it) {
          std::cout << "DT " << _events << " " << "RawEle " << (*it)->pdgid() << " " << (*it)->E() << " " << (*it)->Px() << " " << (*it)->Py() << " " << (*it)->Pz() << " "
                    << (*it)->getPMCvtx()->ct() << " " << (*it)->getPMCvtx()->x() << " " << (*it)->getPMCvtx()->y() << " " << (*it)->getPMCvtx()->z() << " " << std::endl;
        }
        for (vector<TMBMCpart*>::iterator it = raw_mc_photons.begin(); it != raw_mc_photons.end(); ++it) {
          std::cout << "DT " << _events << " " << "RawPho " << (*it)->pdgid() << " " << (*it)->E() << " " << (*it)->Px() << " " << (*it)->Py() << " " << (*it)->Pz() << " "
                    << (*it)->getPMCvtx()->ct() << " " << (*it)->getPMCvtx()->x() << " " << (*it)->getPMCvtx()->y() << " " << (*it)->getPMCvtx()->z() << " " << std::endl;
        }
        for (vector<TMBMCpart*>::iterator it = good_mc_emobjs.begin(); it != good_mc_emobjs.end(); ++it) {
          std::cout << "DT " << _events << " " << "GoodEM " << (*it)->pdgid() << " " << (*it)->E() << " " << (*it)->Px() << " " << (*it)->Py() << " " << (*it)->Pz() << " "
                    << (*it)->getPMCvtx()->ct() << " " << (*it)->getPMCvtx()->x() << " " << (*it)->getPMCvtx()->y() << " " << (*it)->getPMCvtx()->z() << " " << std::endl;
        }
      }// if get mc objects
    }// dump_mctruth
  } // if _MCStudy
  
  if(_doMuon) {                  //############################################
                                 //###       deal with MUON channel         ###
                                 //############################################

    ///////////////////////////////////////////////////////////////////////////
    ///   Extract Muons                                                     ///
    ///////////////////////////////////////////////////////////////////////////
    _muselector->extract(event);
    _muselector->putPointers(event);
    if((_muselector->getGoodMuons()).size()<1) return false; // if no muons found, return false
    else return true;
    
  } else if(!_MCStudy_ZNuNu) {   //############################################
                                 //###       deal with ELECTRON channel     ###
                                 //############################################

    ///////////////////////////////////////////////////////////////////////////
    ///   Extract Trigger objects, EM, track, MET based on event vertex     ///
    ///////////////////////////////////////////////////////////////////////////
    _emselector->extract(event);
    // if no electrons found, return false
    //if(_emselector->getProbeEMObjs().size()<1) return false; 
    
    // require primary vertex must be inside some range
    float event_vtx[3];
    int nvtx = 0;

    _vtxselector->extract(event, _emselector->getGoodEMObjs(), nvtx);
    _vtxselector->EventVertex(event_vtx);

    // extract other physics objects
    if (_extractTriggerObjects) _trigobjselector->extract(event);
    _trkselector->extract(event);
    _metselector->extract(event, _emselector->getGoodEMObjs());
    
    ///////////////////////////////////////////////////////////////////////////
    ///   apply correction for electrons, tracks and missingEt with respect ///
    ///   to new primary vertex                                             ///
    ///////////////////////////////////////////////////////////////////////////
    float best_X_PV = event_vtx[0];
    float best_Y_PV = event_vtx[1];
    float best_Z_PV = event_vtx[2];

    if(_ReVertexing) {

      // get the new priamry vertex based on track z position(s) from electron(s)
      float track_vtx[3];
      _vtxselector->TrackVertex(track_vtx);
      
      // if track vertex and d0reco primary vertex are far away from each other
      // will do revertexing
      double vtx_diff = event_vtx[2] - track_vtx[2];
      
      // will also do revertexing if we have something to kill
      std::map<std::pair<int,int>,int> liste;
      if (_excludeSCAfailures) liste = consultKillList(event.getMCEventInfo()->overlayrun());

      if(fabs(vtx_diff)>_PV_displaced_Limit || liste.size()) {
	_emselector->applyCorrection(event, event_vtx, track_vtx);
	_metselector->applyCorrection(event, _emselector->getGoodEMObjs(), event_vtx, track_vtx, &liste);
	//_trkselector->applyCorrection(event, event_vtx, track_vtx);
	
	// use track vertex
	best_Z_PV = track_vtx[2];
      } // revertexing if primary vertex is displaced
    }   

    //
    // make cut on primary vertex
    //
    if(fabs(best_Z_PV)>_VtxCut || nvtx<_NumVtxCut) {  // require at least N vertices
      _events_fail_vtxcut++;                             // (usually N=0, though)
      if(_debugLevel>10) {
	cout << "ObjSelector: Z->ee mode: Event failed d0reco PV cut:  "<<endl
	     << "                         ";
	if(nvtx) cout << "|PVz|=" << fabs(best_Z_PV) << ", ";
	cout << "Nvtx=" << nvtx << endl; 
      }
      return false;
    }

    // push back pointers
    _trigobjselector->putPointers(event);
    _emselector->putPointers(event);
    _vtxselector->putPointers(event);
    _trkselector->putPointers(event);
    _metselector->putPointers(event);
    
    // pass best PV (or MC vertex) pointer to the event
    event.put("Best primary vertexX", best_X_PV);
    event.put("Best primary vertexY", best_Y_PV);
    event.put("Best primary vertexZ", best_Z_PV);
    event.put("Number of primary verticies", nvtx);
    
    return true;
    
  } else {                       //############################################
                                 //### deal with NEUTRINO channel (MC only) ###
                                 //############################################

    ///////////////////////////////////////////////////////////////////////////
    ///   Extract MET, EM, track, MET based on event reco/truth vertex      ///
    ///   (don't care about the number of good EM objects)                  ///
    ///////////////////////////////////////////////////////////////////////////
    _emselector->extract(event);

    float event_vtx[3];
    int nvtx = 0;

    _vtxselector->extract(event, _emselector->getGoodEMObjs(), nvtx);
    _vtxselector->EventVertex(event_vtx);
    
    ///////////////////////////////////////////////////////////////////////////
    // extract other reconstructed physics objects                          ///
    ///////////////////////////////////////////////////////////////////////////
    _trkselector->extract(event);
    _metselector->extract(event, _emselector->getGoodEMObjs());
    
    ///////////////////////////////////////////////////////////////////////////
    /// apply correction for electrons, tracks and missingEt with respect   ///
    /// to new primary vertex                                               ///
    ///////////////////////////////////////////////////////////////////////////
    float best_X_PV = event_vtx[0];
    float best_Y_PV = event_vtx[1];
    float best_Z_PV = event_vtx[2];

    if(_ReVertexing) {

      // get the new priamry vertex based on track z position(s) from electron(s)
      float track_vtx[3];
      _vtxselector->TrackVertex(track_vtx);
	
      if(!_useMCvertex) {  // use event, track vertices from d0reco
	
	// if track vertex and d0reco primary vertex are far away from each other
	// will do revertexing
	double vtx_diff = event_vtx[2] - track_vtx[2];

	// will also do revertexing if we have something to kill
	std::map<std::pair<int,int>,int> liste;
	if (_excludeSCAfailures) liste = consultKillList(event.getMCEventInfo()->overlayrun());

	if(fabs(vtx_diff)>_PV_displaced_Limit || liste.size()) {
	  _emselector->applyCorrection(event, event_vtx, track_vtx); // it currently does nothing
	  _metselector->applyCorrection(event, _emselector->getGoodEMObjs(), event_vtx, track_vtx, &liste);
	  //_trkselector->applyCorrection(event, event_vtx, track_vtx);
	  
	  // use track vertex
	  best_Z_PV = track_vtx[2];
	} // revertexing if primary vertex is displaced

      } else {  // use MC truth vertex from the hard scatter 

	// do revertexing using true MC vertex
	// force recomputing MET from raw cells using MC truth 
	std::map<std::pair<int,int>,int> liste;
        if (_excludeSCAfailures) liste = consultKillList(event.getMCEventInfo()->overlayrun());
	_metselector->applyCorrection(event, _emselector->getGoodEMObjs(), event_vtx, event_vtx, &liste);
	  
	// don't change best_Z_PV because it has been already initialized
	// to the true MC vertex
      }
    } // end of revertexing

    ///////////////////////////////////////////////////////////////////////////
    // apply vertex cuts (if any)                                           ///
    ///////////////////////////////////////////////////////////////////////////
    if(!_useMCvertex) { // use event vertex from d0reco

      // require primary vertex to be inside some range
      if(fabs(best_Z_PV)>_VtxCut || nvtx<_NumVtxCut) {// require at least N vertices
	_events_fail_vtxcut++;                           // (usually N=0, though)
	if(_debugLevel>10) {
	  cout << "ObjSelector: Z->nunu mode: Event failed d0reco PV cut:  "<<endl
	       << "                           ";
	  if(nvtx) cout << "|PVz|=" << fabs(best_Z_PV) << ", ";
	  cout << "Nvtx=" << nvtx << endl; 
	}
	return false;
      }

    } else {  // use MC truth vertex from the hard scatter 
      
      TMBMCpart *mc_WZ;
      if(!event.get("WZ boson object", mc_WZ)) nvtx=0;
      else {
	nvtx=1;
	event_vtx[0] = mc_WZ->getPMCvtx()->x();
	event_vtx[1] = mc_WZ->getPMCvtx()->y();
	event_vtx[2] = mc_WZ->getPMCvtx()->z();

	best_X_PV = event_vtx[0];
	best_Y_PV = event_vtx[1];
	best_Z_PV = event_vtx[2];

      }

      if(nvtx==0 || fabs(event_vtx[2])>_VtxCut) {
	_events_fail_vtxcut++; 
	if(_debugLevel>10) {
	  cout << "ObjSelector: Z->nunu mode: Event failed MC truth vertex cut:  "<<endl
	       << "                           ";
	  if(nvtx) cout << "|MC z|=" << fabs(event_vtx[2]) << ", ";
	  cout << "MC Nvtx=" << nvtx << endl; 
	}
	return false;
      }
    }

    // push back pointers
    _emselector->putPointers(event);
    _vtxselector->putPointers(event);
    _trkselector->putPointers(event);
    _metselector->putPointers(event);
    
    // pass best PV (or MC vertex) pointer to the event
    event.put("Best primary vertexX", best_X_PV);
    event.put("Best primary vertexY", best_Y_PV);
    event.put("Best primary vertexZ", best_Z_PV);
    event.put("Number of primary verticies", nvtx);

    return true;

  } // end of MUON/ELECTRON/NEUTRINO channel switch
}

void ObjSelector::begin() { }

void ObjSelector::finish() { 
  cout<<"Events processed by ObjSelector: "<<_events<<endl;
  cout<<"Events failed primary vertex cut: "<<_events_fail_vtxcut<<endl;
  if (_cutOnLeadingFSR||_cutOnTrailingFSR||_cutOnFSRnPhot) {
    cout<<"Events failed FSR cuts: "<<_events_fail_FSRcut<<endl;
  }
}

void ObjSelector::initialiseKillList() {

  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(262375,262419),std::pair<int,int>(16,40)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(257412,257415),std::pair<int,int>(32,44)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(257158,257178),std::pair<int,int>(-6,55)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(257644,257711),std::pair<int,int>(19,64)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(261613,261717),std::pair<int,int>(17,16)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(255384,255518),std::pair<int,int>(6,20)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(257891,257956),std::pair<int,int>(-7,20)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(258151,258172),std::pair<int,int>(25,25)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(262127,262218),std::pair<int,int>(7,28)));
  //
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(275016,275022),std::pair<int,int>(6,35)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(270063,270162),std::pair<int,int>(33,43)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(270063,270162),std::pair<int,int>(34,43)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(274399,274405),std::pair<int,int>(16,37)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(273384,273409),std::pair<int,int>(9,6)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(272679,272826),std::pair<int,int>(2,8)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(268995,268999),std::pair<int,int>(-30,14)));
  _SCAkillList.insert(std::pair<std::pair<int,int>,std::pair<int,int> >(std::pair<int,int>(268514,268543),std::pair<int,int>(-1,30)));

}

std::map<std::pair<int,int>,int> ObjSelector::consultKillList(int run) {

  std::map<std::pair<int,int>,int> liste;

  for (std::map<std::pair<int,int>,std::pair<int,int> >::iterator it = _SCAkillList.begin(); it!=_SCAkillList.end(); it++) {
    if (run<=it->first.second && run>=it->first.first) {
      liste.insert(std::pair<std::pair<int,int>,int>(it->second,1));
    }
  }

  return liste;

}

ClassImp(ObjSelector)
