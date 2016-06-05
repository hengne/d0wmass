#include <iostream>
#include <vector>
#include "wmass_analysis/EMSelector.hpp"
#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"

using namespace std;
using namespace cafe;

// Constructor
EMSelector::EMSelector(const char *name):Processor(name) {
  Config config(name);
  
  // debug
  _debugLevel = config.get("debugLevel", 0);
  
  // EM selection requirements
  _DetEtaCC = config.get("DetEtaCC", 1.1);
  _DetEtaEC1 = config.get("DetEtaEC1", 1.5);
  _DetEtaEC2 = config.get("DetEtaEC2", 2.3);
  
  _ElecPtCut = config.get("ElecPtCut", 25.);
  _ElecPtCut_Probe = config.get("ElecPtCut_Probe", 15.);
  _preselTrk       =  config.get("RequirePreselTrk", true);

  _nonStdEMobjs = config.get("nonStdEMobjs", false);
  if (_nonStdEMobjs) {
    _nameEMobjs = config.get("nameEMobjs", "");
  }

  _HM7Cut = config.get("HM7Cut", 12.);
  _HM8Cut = config.get("HM8Cut", 20.);
  _EMFracCut = config.get("EMFracCut", 0.9);
  _IsoCut = config.get("IsoCut", 0.15);

  _truthMatchEMs = config.get("truthMatchEMs", false);

  _QCDBkgStudy = config.get("QCDBkgStudy", false);
  _InvertHM7Cut = config.get("InvertHM7Cut", 30.);
  _InvertHM8Cut = config.get("InvertHM8Cut", 40.);
  
  _studyPhiMod = config.get("StudyPhiMod", false);
  _MCStudy = config.get("MCStudy", false);
  _useTrackFiducial = config.get("UseTrackPhiFiducial", true);
  std::cout << "UseTrackPhiFiducial : " << _useTrackFiducial<< std::endl;
  _goodsameasprobe = config.get("goodsameasprobe", true);

  _emclusposcorr = new EMClusterPosCorr(config);


  // make efficiency files 
  _makeEfficStudyFile = config.get("makeEfficStudyFile", false);
  if(_makeEfficStudyFile) {
    _HM7Cut = 50.;
    _HM8Cut = 50.;
    _IsoCut = 0.2;
    _EMFracCut = 0.9;
  }
  
  // study uparallel efficiency, will change isolation and hmatrix cut
  _uParaEffStudy = config.get("uParaEffStudy", false);
  if(_uParaEffStudy) {
   _HM7Cut = 10000.;
   _HM8Cut = 10000.;
   _IsoCut = 10000.;
   _EMFracCut = 0.;
  }
}

// Destructor
EMSelector::~EMSelector() {}

//
// delete useless pointers from last event
// should be called at the beginning of extract
// should NOT called at the end of extract
//
void EMSelector::cleanObjects(){
  // delete probe emobjects
  for(int i=0; i<_probe_emobjs.size(); i++) delete _probe_emobjs[i];
  _probe_emobjs.clear();

  // delete good emobjects
  for(int i=0; i<_good_emobjs.size(); i++) delete _good_emobjs[i];
  _good_emobjs.clear();
}

//
// extract good EM candidates
//
void EMSelector::extract(cafe::Event& event) {  

  // delete useless pointers from last event
  cleanObjects();
  
  //get em objects from the event
  cafe::Collection<TMBEMCluster> em;
  if (_nonStdEMobjs) {
    em = event.getEM(_nameEMobjs);
  } else {
    em = event.getEMscone();
  }

  for (Collection<TMBEMCluster>::iterator it = em.begin(); it!= em.end(); ++it) {

    if (_truthMatchEMs) {
      bool haveMatch=false;
      cafe::Collection<TMBMCpart> mc = event.getMCParticles();
      for (cafe::Collection<TMBMCpart>::iterator itMC = mc.begin(); itMC!= mc.end(); ++itMC) {
        if(itMC->Pt()>4 && (itMC->abspdgid()==11 || itMC->pdgid()==22)) {
          if (kinem::delta_R(it->Eta(),it->Phi(),itMC->Eta(),itMC->Phi())<0.3) {
            haveMatch=true;
            break;
          }
        }
      }
      if (!haveMatch) continue;
    }

    if ((abs((*it).id())==11  || (abs((*it).id())==10))      && ((*it).Pt()>_ElecPtCut_Probe) ) {
      // probe electrons only have few cuts since they are used to study efficiencies
      CAFEMObj *emobjptr = new CAFEMObj(&(*it)) ;
      if ((*it).has_spatial_track_match(-0.5)){
	TrackPhiFiducial(emobjptr, event); // This is a kluge to set the _trkphiem3 data member
      }

//       if ((!((*it).has_spatial_track_match(-0.5))) && (abs((*it).id())==11)){
// 	std::cerr << " |type ID| = 11 and no spatial_track_match" << std::endl;
// 	std::cerr << "Spatial Chi2 Prob = " << (*it).track_match_spatialchi2prob() << std::endl;
// 	std::cerr << "Chi2 Prob = " << (*it).track_match_chi2prob() << std::endl;
// 	abort();
//       }
      else if (((*it).has_spatial_track_match(-0.5)) && (abs((*it).id())==10)){
	std::cerr << " |type ID| = 10 and has spatial_track_match" << std::endl;
	abort();
      }
      
      if (_preselTrk && !((*it).has_spatial_track_match(-0.5))){ 
	continue;
      }
      
      _probe_emobjs.push_back(emobjptr);
      

      if (!_goodsameasprobe){
    	  // more cuts for good EM objects
    	  if( (*it).Pt()>_ElecPtCut ) {
        	if( (*it).emfrac()>_EMFracCut && (*it).iso()<_IsoCut ) {

        	  bool IsFiducial = false;
        	  if(_studyPhiMod) IsFiducial = (*it).is_in_eta_fiducial();
		  else if (_useTrackFiducial && (*it).has_spatial_track_match(-0.5)) IsFiducial = TrackPhiFiducial(emobjptr, event) && (*it).is_in_eta_fiducial();
        	  else if (!_useTrackFiducial) IsFiducial = (*it).is_in_fiducial();

		  if (IsFiducial) {   // fiducial requirement
	    	// for QCD background study, I just invert HMx7 and HMx8 cut for CC and EC regions
	    	// the code organized this way so that we can have exactly the same histograms filled as the signals
	    	// of course, need to run the program twice, one for signal and one for background 
	    	CAFEMObj *femobjptr = new CAFEMObj(&(*it));
        	if (!_useTrackFiducial) femobjptr->SetTrkPhiEM3(1.0);//this is protection for a special case of no TrkPhiFiducial,TrkPresel both set to false
	    	if ((*it).has_spatial_track_match(-0.5)){
	    	  TrackPhiFiducial(femobjptr, event); // This is a kluge to set the _trkphiem3 data member
	    	}
	    	if(!_QCDBkgStudy) {
	    	  if(((fabs((*it).CalDetectorEta())<_DetEtaCC && (*it).HMx7()<_HM7Cut) || 
			  ((fabs((*it).CalDetectorEta())<_DetEtaEC2 && fabs((*it).CalDetectorEta())>_DetEtaEC1 && (*it).HMx8()<_HM8Cut) )) ){
			_good_emobjs.push_back(femobjptr);
	    	  }
	    	} else {
	    	  if(((fabs((*it).CalDetectorEta())<_DetEtaCC && (*it).HMx7()>_InvertHM7Cut) || 
			  ((fabs((*it).CalDetectorEta())<_DetEtaEC2 && fabs((*it).CalDetectorEta())>_DetEtaEC1 && (*it).HMx8()>_InvertHM8Cut) )) ) 
			_good_emobjs.push_back(femobjptr);
	    	}
		  } //study phimod
		}
    	  }// pT cut
      }//if (!_goodsameasprobe){
      else{
	    CAFEMObj *femobjptr = new CAFEMObj(&(*it));        
  	    femobjptr->SetTrkPhiEM3(1.0);//this is protection 
        if ((*it).has_spatial_track_match(-0.5)){
	       TrackPhiFiducial(femobjptr, event); // This is a kluge to set the _trkphiem3 data member
        }
        _good_emobjs.push_back(femobjptr);//good objects same as probe objects
      } 
    } // probe EM objects    
  }//loop over all EMs
  
  // sort EM objects
  
  sort(_probe_emobjs.begin(), _probe_emobjs.end(), ComparePt);
  sort(_good_emobjs.begin(), _good_emobjs.end(), ComparePt);
  
  
  // print out information
  if(_debugLevel>=5) {
    cout<<"Probe EM Objects: "<<endl;
    for(int i=0; i<_probe_emobjs.size(); i++) _probe_emobjs[i]->print();
    cout<<"Good EM Objects: "<<endl;
    for(int i=0; i<_good_emobjs.size(); i++) _good_emobjs[i]->print();
  }
}

//
// recalculate EM candidate properties for different primary vertex
//
void EMSelector::applyCorrection(cafe::Event& event, float vtx_old[3], float vtx_new[3]) {
 
  //  for(vector<CAFEMObj*>::iterator it=_good_emobjs.begin(); it!=_good_emobjs.end(); ++it)
  //    (*it)->UpdateForNewVertex(vtx_old, vtx_new);
 
  // pT will not change, so do not need to sort them again
  //sort(_good_emobjs.begin(), _good_emobjs.end(), ComparePt); 
}

// 
// put pointers into event class
//
void EMSelector::putPointers(cafe::Event& event) {
  event.put("Probe EMObjs", _probe_emobjs);
  event.put("Good EMObjs", _good_emobjs);
}


bool EMSelector::TrackPhiFiducial(CAFEMObj* emobj, cafe::Event& event){
// if this functions needs to be updated,
// please update also function 
// bool TrackPhiFiducial(CAFEMObj* emobj, cafe::Event& event)
// in wmass_analysis/src/EffAnalysis.cpp
  int solpol = -999;  
  event.get("solenoid polarity", solpol);
  int polarity = 2*solpol - 1;
  double phi = emobj->trkPhiEM3(_emclusposcorr, polarity, -0.5, _MCStudy);
  double eta = emobj->trkEtaEM3(_emclusposcorr, polarity, -0.5, _MCStudy);
  emobj->SetTrkPhiEM3(phi);
  emobj->SetTrkEtaEM3(eta);
  bool outside_phi_crack=true;
  if (phi == 9999.)
    return outside_phi_crack;
  if (emobj->IsCC(_DetEtaCC)){
    float phimod=fmod(phi+0.1,kinem::PI/16.);
    outside_phi_crack=((phimod<0.1-0.02) || (phimod>0.1+0.02));
  }
  return outside_phi_crack;
}

ClassImp(EMSelector)
