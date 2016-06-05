#include "JPsiMuAnalysis.hpp"
#include "PMCSJPsiMuCand.hpp"
#include "histograms.hpp"

#include <TFile.h>
#include <TObject.h>
#include <TROOT.h>
#include <iostream>
#include <vector>

using namespace std;

bool ComparePt(const PMCSParticle part1, const PMCSParticle part2);
bool CompareE(const PMCSParticle part1, const PMCSParticle part2);

// Constructor
JPsiMuAnalysis::JPsiMuAnalysis(TString parameter_filename):_ntotal(0) {

  // initialize MuSmear
  _musmear = new MuSmear(parameter_filename);

  // read pT ratio histogram
  gROOT->ProcessLine(".x pT_eta_ratio.C");
  _pT_eta_ratio = (TH2F *)gROOT->FindObject("hpT_eta_ratio");

  // Read other control flags
  ReadParameters(parameter_filename);
}

// read parameters
void JPsiMuAnalysis::ReadParameters(TString parameter_filename) {

  PParameterReader parm(parameter_filename.Data());  
  _debug = parm.GetBool("debug", kFALSE);  

  // use event weight or not
  _reweight = parm.GetBool("reweight", kTRUE);

  // output file
  _jpsimumufilename = parm.GetChar("output_file_jpsimumu");

  // muon pT cut
  _CutMuPT = parm.GetFloat("CutJPsiMuPT", 2.);

  // momentum scale study
  _momentumScaleStudy = parm.GetBool("momentumScaleStudy", kFALSE);  
  
  // step sizes for A, B and C
  _step_A = parm.GetFloat("A_step", 0.0001);
  _step_B = parm.GetFloat("B_step", 0.001);
  _step_C = parm.GetFloat("C_step", 0.0001);
  
  // histograms
  _histos.add(JPsiMuCand_Hist);
  _histos.add(JPsiMuCand_Hist_2D);
  
  if(_momentumScaleStudy) {
    _histos.clone("hJPsiMucandMass_AB", 100);
    _histos.clone("hJPsiMucandMass_C", 50);
  }

}

// Analyze an event
void JPsiMuAnalysis::analyzeEvent(PMCSEvent& pmcsevent, TRandom3 *dummy) {
  
  // generator-level objects
  vector<PMCSMuon> muons_gen = pmcsevent.GetMuons();
  PMCSVtx vtx_gen = pmcsevent.GetVtx();
  double evtweight = pmcsevent.GetEvtWeight();
  if(!_reweight) evtweight = 1.;  

  double totalweight = 1.;

  // smear Muons
  vector<PMCSMuon> muons_smear = _musmear->SmearMuons(muons_gen, dummy);
  
  // sort smeared muons according to pT  
  sort(muons_smear.begin(), muons_smear.end(), ComparePt);
  
  // at least two muon Objects
  if(muons_smear.size() >= 2) {
    if( (muons_smear[0].ppt()>_CutMuPT) && (muons_smear[1].ppt()>_CutMuPT) ) {
      PMCSJPsiMuCand jpsicand(muons_smear[0], muons_smear[1]);

      // reweight MC events to get better agreement with data
      double jpsi_pT = jpsicand.ppt();
      double jpsi_eta = jpsicand.eta();
      Int_t bin_pT_eta = _pT_eta_ratio->FindBin(jpsi_pT, jpsi_eta);
      double wgt_factor = _pT_eta_ratio->GetBinContent(bin_pT_eta);
      totalweight = evtweight * wgt_factor;

      double mass = jpsicand.mass();
      if(mass > 2.9 && mass < 3.3 && totalweight > 0.001) {
	_histos.Fill1D("hJPsiMucandMass", mass, totalweight);
	_histos.Fill1D("hJPsiMucandPt", jpsi_pT, totalweight);
	_histos.Fill1D("hJPsiMucandEta", jpsi_eta, totalweight);
	_histos.Fill1D("hJPsiMucandPhi", jpsicand.phi(), totalweight);
	_histos.Fill2D("hJPsiMucandPt_V_Eta", jpsi_pT, jpsi_eta, totalweight);
	
	for(int imu=0; imu<2; imu++) {
	  _histos.Fill1D("hJPsiMucandMuPt", muons_smear[imu].ppt(), totalweight);
	  _histos.Fill1D("hJPsiMucandMuEta", muons_smear[imu].eta(), totalweight);
	  _histos.Fill1D("hJPsiMucandMuPhi", muons_smear[imu].phi(), totalweight);
	} // for each muon

      } // mass cut

    }//both with pT>_CutMuPT
  }//at least two muon Objects
  
  if(_momentumScaleStudy) momentumScaleStudy(pmcsevent, dummy, totalweight);
  
  // Increase the counter for the number of events processed
  _ntotal++;
} 

//////////////////////////////////////////////////////////
// measure A, B and C, study momentum scale
//////////////////////////////////////////////////////////
void JPsiMuAnalysis::momentumScaleStudy(PMCSEvent& pmcsevent, TRandom3 *dummy, double evtweight) {
  
  // generator-level objects
  vector<PMCSMuon> muons_gen = pmcsevent.GetMuons();
  //  double evtweight = pmcsevent.GetEvtWeight();
  //  if(!_reweight) evtweight = 1.;
  
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
	
	if(iA == 5 || iB == 5) {
	  _musmear->SetSmearParameters(etares_raw, phires_raw, A_new, B_new, C_raw);
	  vector<PMCSMuon> muons_new_smear = _musmear->SmearMuons(muons_gen, dummy);
	  
	  // sort smeared muons according to pT  
	  sort(muons_new_smear.begin(), muons_new_smear.end(), ComparePt);
	  
	  if( (muons_new_smear[0].ppt()>_CutMuPT) && (muons_new_smear[1].ppt()>_CutMuPT) ) {
	    PMCSJPsiMuCand jpsicand(muons_new_smear[0], muons_new_smear[1]);	 

	    double mass = jpsicand.mass();
	    if(mass > 2.9 && mass < 3.3) 
	      _histos.Fill1D(TString("hJPsiMucandMass_AB_")+sn_AB, mass, evtweight);
	  }
	} // only need to smear the central values

	
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
	PMCSJPsiMuCand jpsicand(muons_new_smear[0], muons_new_smear[1]);	  

	double mass = jpsicand.mass();
	if(mass > 2.9 && mass < 3.3) 
	  _histos.Fill1D(TString("hJPsiMucandMass_C_")+sn_C, mass, evtweight);
      }
      
      ihist_C ++;
    } // iC
    
  } // at least two generator level muons
  
  // set smearing parameters back to raw values
  _musmear->SetSmearParameters(etares_raw, phires_raw, A_raw, B_raw, C_raw);
}

JPsiMuAnalysis::~JPsiMuAnalysis () {
}

void JPsiMuAnalysis::jobSummary() {
  cout << "JPsiMuAnalysis number of events processed = " << _ntotal << endl; 
  _histos.save(_jpsimumufilename);
}

