#include "ZMuAnalysis.hpp"
#include "PMCSZMuCand.hpp"
#include "histograms.hpp"

#include <TFile.h>
#include <TObject.h>
#include <iostream>
#include <vector>

using namespace std;

bool ComparePt(const PMCSParticle part1, const PMCSParticle part2);

// Constructor
ZMuAnalysis::ZMuAnalysis(TString parameter_filename):_ntotal(0) {

  // initialize MuSmear
  _musmear = new MuSmear(parameter_filename);

  // Read other control flags
  ReadParameters(parameter_filename);
}

// read parameters
void ZMuAnalysis::ReadParameters(TString parameter_filename) {

  PParameterReader parm(parameter_filename.Data());  
  _debug = parm.GetBool("debug", kFALSE);  

  // for reweighting
  _reweight = parm.GetBool("reweight", kTRUE);

  // output file
  _zmumufilename = parm.GetChar("output_file_zmumu");

  // muon pT cut
  _CutMuPT = parm.GetFloat("CutZMuPT", 20.);

  // momentum scale study
  _momentumScaleStudy = parm.GetBool("momentumScaleStudy", kFALSE);  

  // step sizes for A, B and C
  _step_A = parm.GetFloat("A_step", 0.0001);
  _step_B = parm.GetFloat("B_step", 0.001);
  _step_C = parm.GetFloat("C_step", 0.0001);

  // histograms
  _histos.add(ZMuCand_Hist);

  if(_momentumScaleStudy) {
    _histos.clone("hZMucandMass_AB", 100);
    _histos.clone("hZMucandMass_C", 50);
  }
}

// Analyze an event
void ZMuAnalysis::analyzeEvent(PMCSEvent& pmcsevent, TRandom3 *dummy) {
  
  // generator-level objects
  vector<PMCSMuon> muons_gen = pmcsevent.GetMuons();
  PMCSVtx vtx_gen = pmcsevent.GetVtx();
  double evtweight = pmcsevent.GetEvtWeight();
  if(!_reweight) evtweight = 1.;

  // smear Muons
  vector<PMCSMuon> muons_smear = _musmear->SmearMuons(muons_gen, dummy);
  
  // sort smeared muons according to pT  
  sort(muons_smear.begin(), muons_smear.end(), ComparePt);
 
  // at least two muon Objects
  if(muons_smear.size() >= 2) {
    if( (muons_smear[0].ppt()>_CutMuPT) && (muons_smear[1].ppt()>_CutMuPT) ) {
      PMCSZMuCand zcand(muons_smear[0], muons_smear[1]);
      
      _histos.Fill1D("hZMucandMass", zcand.mass(), evtweight);
      _histos.Fill1D("hZMucandPt", zcand.ppt(), evtweight);
      _histos.Fill1D("hZMucandEta", zcand.eta(), evtweight);
      _histos.Fill1D("hZMucandRapidity", zcand.rapidity(), evtweight);
      _histos.Fill1D("hZMucandPhi", zcand.phi(), evtweight);
      
      for(int imu=0; imu<2; imu++) {
        _histos.Fill1D("hZMucandMuPt", muons_smear[imu].ppt(), evtweight);
        _histos.Fill1D("hZMucandMuEta", muons_smear[imu].eta(), evtweight);
        _histos.Fill1D("hZMucandMuPhi", muons_smear[imu].phi(), evtweight);
      } // for each muon
    }//both with pT>_CutMuPT
  }//at least two muon Objects

  // study muon momentum scale  
  if(_momentumScaleStudy) momentumScaleStudy(pmcsevent, dummy);

  // Increase the counter for the number of events processed
  _ntotal++;
} 

//////////////////////////////////////////////////////////
// measure A, B and C, study momentum scale
//////////////////////////////////////////////////////////
void ZMuAnalysis::momentumScaleStudy(PMCSEvent& pmcsevent, TRandom3 *dummy) {

  // generator-level objects
  vector<PMCSMuon> muons_gen = pmcsevent.GetMuons();
  double evtweight = pmcsevent.GetEvtWeight();
  if(!_reweight) evtweight = 1.;
  
  // first get original smearing parameters
  double etares_raw = _musmear->EtaRes_Phy();
  double phires_raw = _musmear->PhiRes_Phy();
  double A_raw = _musmear->A();
  double B_raw = _musmear->B();
  double C_raw = _musmear->C();
  
  // A and B are correlated
  // C is uncorrelated with A and B
  if(muons_gen.size()>=2) {
    int ihist_AB = 0, ihist_C = 0;
    char sn_AB[20], sn_C[20];
    
    // Code to determine A and B
    for(int iA = 0; iA < 10; iA ++) {
      for(int iB = 0; iB < 10; iB ++) {
	double A_new = A_raw + (iA - 5)*_step_A;
	double B_new = B_raw + (iB - 5)*_step_B;	
	sprintf(sn_AB, "%d", ihist_AB);
	
	_musmear->SetSmearParameters(etares_raw, phires_raw, A_new, B_new, C_raw);
	vector<PMCSMuon> muons_new_smear = _musmear->SmearMuons(muons_gen, dummy);
	
	// sort smeared muons according to pT  
	sort(muons_new_smear.begin(), muons_new_smear.end(), ComparePt);
	
	if( (muons_new_smear[0].ppt()>_CutMuPT) && (muons_new_smear[1].ppt()>_CutMuPT) ) {
	  PMCSZMuCand zcand(muons_new_smear[0], muons_new_smear[1]);	  
	  _histos.Fill1D(TString("hZMucandMass_AB_")+sn_AB, zcand.mass(), evtweight);
	}
	
	ihist_AB ++;
      } // iB
    } // iA
    
    // Code to determine C
    for(int iC = 0; iC < 50; iC ++) {
      double C_new = C_raw + (iC - 25)*_step_C;	
      sprintf(sn_C, "%d", ihist_C);
      
      _musmear->SetSmearParameters(etares_raw, phires_raw, A_raw, B_raw, C_new);
      vector<PMCSMuon> muons_new_smear = _musmear->SmearMuons(muons_gen, dummy);
      
      // sort smeared muons according to pT  
      sort(muons_new_smear.begin(), muons_new_smear.end(), ComparePt);
      
      if( (muons_new_smear[0].ppt()>_CutMuPT) && (muons_new_smear[1].ppt()>_CutMuPT) ) {
	PMCSZMuCand zcand(muons_new_smear[0], muons_new_smear[1]);	  
	_histos.Fill1D(TString("hZMucandMass_C_")+sn_C, zcand.mass(), evtweight);
      }
      
      ihist_C ++;
    } // iC
    
  } // at least two generator level muons
  
  // set smearing parameters back to raw values
  _musmear->SetSmearParameters(etares_raw, phires_raw, A_raw, B_raw, C_raw);
}

ZMuAnalysis::~ZMuAnalysis () {
}

void ZMuAnalysis::jobSummary() {
  cout << "ZMuAnalysis number of events processed = " << _ntotal << endl; 
  _histos.save(_zmumufilename);
}


