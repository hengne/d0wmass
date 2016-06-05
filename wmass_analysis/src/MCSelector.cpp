#include <iostream>
#include <vector>
#include "wmass_analysis/MCSelector.hpp"

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"

#include "kinem_util/AnglesUtil.hpp"
#include <algorithm>
using namespace std;
using namespace cafe;

// Constructor
MCSelector::MCSelector(const char *name):Processor(name) {
  Config config(name);
  
  // debug
  _debugLevel = config.get("debugLevel", 0);

  _selectLeadingFSR = config.get("selectLeadingFSR", false);

  _MC_ElecPtCut = config.get("MCElecPtCut", 10.);
  _addFSR = config.get("addFSR", true);
  _computeMCRecoil = config.get("computeMCRecoil",false);

  _MCStudy_ZNuNu = config.get("MCStudy_ZNuNu", false);

  _MCEventInfo_vars.add("_npart");

  _HackedBypass = config.get("HackedBypass", false);

}

// Destructor
MCSelector::~MCSelector() {}

// delete useless pointers
void MCSelector::cleanObjects() {
  for(int i=0; i<_good_mc_emobjs.size(); i++) delete _good_mc_emobjs[i];
  _good_mc_emobjs.clear();
  for(int i=0; i<_good_mc_muons.size(); i++) delete _good_mc_muons[i];
  _good_mc_muons.clear();
  for(int i=0; i<_raw_mc_electrons.size(); i++) delete _raw_mc_electrons[i];
  _raw_mc_electrons.clear();
  for(int i=0; i<_raw_mc_photons.size(); i++) delete _raw_mc_photons[i];
  _raw_mc_photons.clear();
  for(int i=0; i<_good_mc_neutrinos.size(); i++) delete _good_mc_neutrinos[i];
  _good_mc_neutrinos.clear();
  for(int i=0; i<_unmerged_mc_photons.size(); i++) delete _unmerged_mc_photons[i];
  _unmerged_mc_photons.clear();
}

bool findDup(vector <TMBMCpart *> &vec, TMBMCpart *b) {
  bool dupl = false;
  for (vector<TMBMCpart*>::iterator it = vec.begin(); it != vec.end(); ++it) {
    if ((&(*(*it)))==(&(*b))) dupl = true;
    if ((*it)->pdgid() == b->pdgid() &&
	(**it) == (*b) ){
      dupl = true;
    }
  }
  return dupl;
}

//
// extract good MC candidates
//
void MCSelector::extract(cafe::Event& event) {

  // delete useless pointers
  cleanObjects();
  _mc_recoil = new TMBMCpart;
  _WZ = 0;

  //get mc objects from the event  
  double ppx_WZ = 0., ppy_WZ = 0., ppz_WZ = 0., energy_WZ = 0.;
  cafe::Collection<TMBMCpart> mc = event.getMCParticles();
  for (cafe::Collection<TMBMCpart>::iterator it = mc.begin(); it!= mc.end(); ++it) {

    if (_HackedBypass) {
      if(it->abspdgid()==11) {
        _raw_mc_electrons.push_back(new TMBMCpart(*it));
        _good_mc_emobjs.push_back(new TMBMCpart(*it));
      }
      if(it->abspdgid()==22) _raw_mc_photons.push_back(new TMBMCpart(*it));
      if((it->abspdgid()==12 ||
          it->abspdgid()==14 ||
          it->abspdgid()==16   )) _good_mc_neutrinos.push_back(new TMBMCpart(*it));

    }

    // make it both for Z and W
    bool FoundWZ = false;
    if((it->abspdgid() == 23 || it->abspdgid() == 24) && !FoundWZ) {
      _WZ = new TMBMCpart(*it);    
      
      // check W or Z daughters
      if ( const TMBMCvtx *vtx = it->getDMCvtx() ) {
	if(vtx->ndaughters()>0) FoundWZ = true;
	for(int i=0; i<vtx->ndaughters(); i++) {	  
	  const TMBMCpart *daughter = vtx->getDaughter(i);
	  
	  double abspdgid = daughter->abspdgid();
	  // save generator level electrons and photons to three vectors for future use
	  if(abspdgid==22)        _raw_mc_photons.push_back(new TMBMCpart(*daughter));
	  else if(abspdgid==11) { _raw_mc_electrons.push_back(new TMBMCpart(*daughter));
	    _good_mc_emobjs.push_back(new TMBMCpart(*daughter));
	  } else if((abspdgid==12 || 
		     abspdgid==14 ||
		     abspdgid==16   )) _good_mc_neutrinos.push_back(new TMBMCpart(*daughter));
	  
	  // sum up the energy, pX, pY, pZ for all final state particles
	  if(abspdgid==11 || abspdgid==22 ||  // electrons or photons
	     abspdgid==13 || abspdgid==15 ||  // muons or taus
	     abspdgid==12 || abspdgid==14 || abspdgid==16) {  // for neutrinos
	    ppx_WZ += daughter->Px();
	    ppy_WZ += daughter->Py();
	    ppz_WZ += daughter->Pz();
	    energy_WZ += daughter->E();
	  }
	}
      }      
    } // check W or Z boson

    // use pX, pY, pZ and energy for all final state particles to calculate pX, pY, pZ and energy 
    // of the boson
    if(_WZ) {
      _WZ->SetPxPyPzE(ppx_WZ, ppy_WZ, ppz_WZ, energy_WZ);
      
    }
    
    if(it->abspdgid() == 13) {
      if (!(findDup(_good_mc_muons,(&(*it))))) {
	_good_mc_muons.push_back(new TMBMCpart(*it));
      }
    }
    
    // do not need the following code any more   
    /*
    if(it->pdgid() == 22) {
      if (!(findDup(_raw_mc_photons,(&(*it))))) {
	_raw_mc_photons.push_back(new TMBMCpart(*it));
      }
    }
    // need to have raw MC electrons (before merging) information in order to study E/p distribution    
    if (it->abspdgid() == 11 && it->Pt() > _MC_ElecPtCut) {
      if (!(findDup(_raw_mc_electrons,(&(*it))))) {
	_raw_mc_electrons.push_back(new TMBMCpart(*it));
      }
      if (!(findDup(_good_mc_emobjs,(&(*it))))) {
	_good_mc_emobjs.push_back(new TMBMCpart(*it));
      }
    }
    */
    
  } // loop over all MC particles

  // Look for leading FSR photon, if requested
  _LeadFSR_ET=-1;
  _LeadFSR_dR=9999;
  _LeadFSR_x=-1;
  _TrailFSR_ET=9999;
  _TrailFSR_dR=9999;
  _TrailFSR_x=-1;
  _FSR_nPhot=0;
  if (_selectLeadingFSR) {
    for (vector<TMBMCpart*>::iterator it = _raw_mc_photons.begin(); it != _raw_mc_photons.end(); ++it) {
      _FSR_nPhot++;
      if ((*it)->Pt()>_LeadFSR_ET) {
        _LeadFSR_ET=(*it)->Pt();
        _LeadFSR_dR=9999;
        _LeadFSR_x=-1;
        for(vector<TMBMCpart*>::iterator it2 = _good_mc_emobjs.begin(); it2 !=_good_mc_emobjs.end(); it2++) {
          float dR=kinem::delta_R((*it)->Eta(), (*it)->Phi(), (*it2)->Eta(), (*it2)->Phi());
          if (dR < _LeadFSR_dR) {
            _LeadFSR_dR=dR;
            _LeadFSR_x=(*it)->E()/((*it2)->E()+(*it)->E());
          }
        }
      }
      if ((*it)->Pt()<_TrailFSR_ET) {
        _TrailFSR_ET=(*it)->Pt();
        _TrailFSR_dR=9999;
        _TrailFSR_x=-1;
        for(vector<TMBMCpart*>::iterator it2 = _good_mc_emobjs.begin(); it2 !=_good_mc_emobjs.end(); it2++) {
          float dR=kinem::delta_R((*it)->Eta(), (*it)->Phi(), (*it2)->Eta(), (*it2)->Phi());
          if (dR < _TrailFSR_dR) {
            _TrailFSR_dR=dR;
            _TrailFSR_x=(*it)->E()/((*it2)->E()+(*it)->E());
          }
        }
      }
    }
  }

  vector<const TMBMCpart*> FSR;
  // Merge electron and photons
  if (_addFSR) {

    // Create an array (isMerged) that records which photons are merged
    int numphots = _raw_mc_photons.size();
    int *isMerged; 
    if(numphots>0) isMerged = new int[numphots];
    for(int mm=0; mm<numphots; mm++) isMerged[mm]=0;
   
    for(vector<TMBMCpart*>::iterator it = _good_mc_emobjs.begin(); it!=_good_mc_emobjs.end(); it++) {   
      double merged_pX = (*it)->Px();
      double merged_pY = (*it)->Py();
      double merged_pZ = (*it)->Pz();
      double merged_E = (*it)->E();
      
      int pnum=0;
      for (vector<TMBMCpart*>::iterator it2 = _raw_mc_photons.begin(); it2!= _raw_mc_photons.end(); ++it2) {      
	if (kinem::delta_R((*it)->Eta(), (*it)->Phi(), (*it2)->Eta(), (*it2)->Phi()) < 0.3 && !isMerged[pnum]) {
	  merged_pX += (*it2)->Px();
	  merged_pY += (*it2)->Py();
	  merged_pZ += (*it2)->Pz();
	  merged_E += (*it2)->E();
	  FSR.push_back(*it2);
	  isMerged[pnum]=1;
	}//photon and electron are close
	pnum++;
      }// loop over all photons
      
      (*it)->SetPxPyPzE(merged_pX, merged_pY, merged_pZ, merged_E);
    }//loop over all electrons
 
    //loop over photons, store unmerged photons
    int pnum=0;
    for (vector<TMBMCpart*>::iterator it2 = _raw_mc_photons.begin(); it2!= _raw_mc_photons.end(); ++it2) {
      if( isMerged[pnum] == 0 ) {
	const TMBMCpart *copy = *it2;
	_unmerged_mc_photons.push_back( new TMBMCpart(*copy) );
      }
      pnum++;
    }
    
  }//addFSR
  if (_computeMCRecoil) {
    //want to compute recoil here
    //loop over generator-level particles, not d0gstar
    for (int i = 0;i < event.getMCEventInfo(_MCEventInfo_vars)->npart(0);i++) {
      if ( mc[i].pdgid() == 23 || mc[i].pdgid() == 24) {
	continue;
      }//don't want the W/Z
      if ( mc[i].abspdgid() == 11 &&  mc[i].Pt() > _MC_ElecPtCut) {
	continue;
      }//don't want the electrons from W/Z

      bool accept = true;
      for (vector<const TMBMCpart*>::iterator fsr_it = FSR.begin(); fsr_it != FSR.end(); fsr_it++) {
	if ( (&(mc[i])) == (*fsr_it)) {
	  accept = false;
	  //break;
	}//reject if it is FSR
      }//loop over FSR particles
      if (accept && mc[i].isStableParticle()) {
	(*_mc_recoil)+= (mc[i]);
      }//take the stable ones
    }//loop over all MC particles again
  }//if compute mc recoil
  else {
    if (_WZ)
      (*_mc_recoil) -= (*_WZ);
  }

  // sort MC objects
  sort(_good_mc_emobjs.begin(), _good_mc_emobjs.end(), CompareMCPt);
  sort(_raw_mc_electrons.begin(), _raw_mc_electrons.end(), CompareMCPt);
  sort(_good_mc_muons.begin(), _good_mc_muons.end(), CompareMCPt);
  if(_MCStudy_ZNuNu) sort(_good_mc_neutrinos.begin(), _good_mc_neutrinos.end(), CompareMCPt);

  // push back pointers
  event.put("em mc objects", _good_mc_emobjs);
  event.put("muon mc objects", _good_mc_muons);
  event.put("raw mc electrons", _raw_mc_electrons);
  event.put("raw mc photons", _raw_mc_photons);
  event.put("mc recoil object", _mc_recoil);
  event.put("mc neutrinos", _good_mc_neutrinos);
  event.put("unmerged photons", _unmerged_mc_photons);

  if (!_HackedBypass)
    event.put("WZ boson object", _WZ);

}

// FSR accessors

float MCSelector::LeadFSR_ET() {
  assert(_selectLeadingFSR);
  return _LeadFSR_ET;
}

float MCSelector::LeadFSR_dR() {
  assert(_selectLeadingFSR);
  return _LeadFSR_dR;
}

float MCSelector::LeadFSR_x() {
  assert(_selectLeadingFSR);
  return _LeadFSR_x;
}

float MCSelector::TrailFSR_ET() {
  assert(_selectLeadingFSR);
  return _TrailFSR_ET;
}

float MCSelector::TrailFSR_dR() {
  assert(_selectLeadingFSR);
  return _TrailFSR_dR;
}

float MCSelector::TrailFSR_x() {
  assert(_selectLeadingFSR);
  return _TrailFSR_x;
}

int MCSelector::FSR_nPhot() {
  assert(_selectLeadingFSR);
  return _FSR_nPhot;
}

double MCSelector::TrueWZPt() {
  if(_WZ) return _WZ->Pt();
  else return -100.0;
}

double MCSelector::TrueWZPhi() {
  if(_WZ) return _WZ->Phi();
  else return -100.0;
}

double MCSelector::TrueWZMass() {
  if(_WZ) return _WZ->M();
  else return -100.0;
}

ClassImp(MCSelector)
