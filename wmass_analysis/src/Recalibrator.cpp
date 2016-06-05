#include "wmass_analysis/Recalibrator.hpp"
#include "cafe/Config.hpp"
#include <iostream>


Recalibrator::Recalibrator(const char * name):cafe::SelectUserObjects<TMBEMCluster>(name){

  std::cout << std::endl << "=============== Recalibrator (" << name << ") ==============" << std::endl;
  
  cafe::Config config(name);
  _MClikeData = config.get("RecalibrateMClikeData", false);

}


bool Recalibrator::processEvent(cafe::Event& event) {

  _epoch = event.isRun2b() ? "p20" : "p17";
  _mode  = event.isMC()    ? "mc"  : "data";

  _event = &event;

  event.getCaloCells(); //needs to be called at some point before trying to access the cells.

  cafe::SelectUserObjects<TMBEMCluster>::processEvent(event);

  return true;

}


void Recalibrator::after(cafe::Collection<TMBEMCluster>& input, cafe::Collection<TMBEMCluster>& rejected) {

  const bool isMC = _mode == "mc";
  const bool isRunIIb = _epoch == "p20";

  for (cafe::Collection<TMBEMCluster>::iterator it_emcl = input.begin() ; it_emcl != input.end(); ++it_emcl){

    //////////// only consider id 10 or 11 clusters //////////////
    if(abs(it_emcl->id()) != 11 && it_emcl->id() != 10) continue;
    
    ////////// ENERGY CORRECTIONS DEFAULT TO 1.0 ///////////////////
    it_emcl->set_ecorr_smearing(1.0,0);
    it_emcl->set_ecorr_wmass_cell(1.0);
    it_emcl->set_ecorr_wmass_phi(1.0);
    it_emcl->set_ecorr_wmass_eloss(1.0);
    it_emcl->set_ecorr_phimod_hmx7(1.0);  
    it_emcl->set_ecorr_ilum(1.0);  
    it_emcl->set_ecorr_saturation(1.0);  

    // adjust cell energies, if needed
    float new_energy;
    if (isMC) {
      new_energy = it_emcl->uncorrE();
    } else if (!isMC || _MClikeData) {
      if (isRunIIb) {
	new_energy = _scalechangerIIbJan.NewScale(&(*it_emcl),_event->getGlobal()->runno(),false);
      } else {
	// we're not set up for Run IIa data
	std::cout<<"Recalibrator: do not know how to deal with Run IIa data. Aborting."<<std::endl;
	assert(0);
      }
    }
    
    // redo E-loss corrections - from scratch (in contrast to Mika)
    if (isMC) {
      new_energy = _geocorr.correvseta_S(new_energy, it_emcl->Eta(), it_emcl->CalDetectorEta(), isRunIIb, isMC);
      new_energy = _geocorr.correvsphi_S(new_energy, it_emcl->CalDetectorPhi(), it_emcl->CalDetectorEta(), !isMC);
    } else if (!isMC || _MClikeData) {
      if (fabs(it_emcl->CalDetectorEta())<1.3) {
	new_energy = _geocorrJan.correvseta_S(new_energy, it_emcl->Eta(), it_emcl->CalDetectorEta());
	new_energy = _geocorrJan.correvsphi_S(new_energy, it_emcl->CalDetectorPhi(), it_emcl->CalDetectorEta(), !isMC);
      } else {
	new_energy = _geocorr.correvseta_S(new_energy, it_emcl->Eta(), it_emcl->CalDetectorEta(), isRunIIb, isMC);
	new_energy = _geocorr.correvsphi_S(new_energy, it_emcl->CalDetectorPhi(), it_emcl->CalDetectorEta(), !isMC);
      }
    }
    it_emcl->set_ecorr_wmass_eloss(new_energy/it_emcl->E());

    //////// ACTUALLY APPLY THE CORRECTIONS HERE ///////////////////
    float final_ecorr = 1.0;
    final_ecorr *= it_emcl->ecorr_wmass_eloss();
    
    ScaleEM(*it_emcl,final_ecorr);//finally correct the energy of the TMBEMCluster
    
  }// loop over clusters in the collection
}


void Recalibrator::ScaleEM(TMBEMCluster & emcl,const float corr){

  emcl.SetPxPyPzE(emcl.Px()*corr,emcl.Py()*corr,emcl.Pz()*corr,emcl.E()*corr);
  emcl.SetCalE(emcl.E()); //also set the CalE variable,
}


bool Recalibrator::selectObject(const TMBEMCluster &emCluster) {return true;}


Recalibrator::~Recalibrator(){}


ClassImp(Recalibrator);

