#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include "wmass_analysis/ZMuAnalysis.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "wmass_analysis/histograms.hpp"
#include <TFile.h>

using namespace std;
using namespace cafe;

ZMuAnalysis::ZMuAnalysis(const char *name)
  : Processor(name)
{
  Config config(name);

  _MCStudy = config.get("MCStudy", false);

  _histos.add(ZMuCand_Hist);
  _histos.add(ZMuMC_Hist_Profile);
  
  _histos.clone("ZMCMuInvpTDiff", 5);
  _histos.clone("ZMCMuPt", 5);
  _histos.clone("ZMCMuInvPt", 5);

  _NumZCand = 0;

  // MC smearing parameters
  _A = config.get("A_Resolution", 0.);
  _B = config.get("B_Resolution", 0.);
  _C = config.get("C_Scale", 1.);
  _CNonLinear = config.get("C_Scale_NonLinear", 0.);
  _eta_Resolution = config.get("eta_Resolution", 0.);
  _phi_Resolution = config.get("phi_Resolution", 0.);

  _random = new TRandom3(0);
}

// process 
bool ZMuAnalysis::processEvent(cafe::Event& event) {

 vector<CAFMuon*> muons;
 if (event.get("Good Muons", muons) ) {
  //at least two muons
   if(muons.size()>=2) {

     double mupT[2], invmupT[2];
     mupT[0] = muons[0]->Pt();
     mupT[1] = muons[1]->Pt();

     if( (mupT[0]>20.) && (mupT[1]>20.) && 
	 (muons[0]->isMedium()) && (muons[1]->isMedium()) &&
	 !(muons[0]->isCosmic()) && !(muons[1]->isCosmic()) ) {
      
       _NumZCand++;
 
       invmupT[0] = 1./mupT[0];
       invmupT[1] = 1./mupT[1];
       
       TMBLorentzVector mu1(muons[0]->Px(), muons[0]->Py(), muons[0]->Pz(), muons[0]->E());
       TMBLorentzVector mu2(muons[1]->Px(), muons[1]->Py(), muons[1]->Pz(), muons[1]->E());
       
       double mass = sqrt( (mu1[3]+mu2[3])*(mu1[3]+mu2[3]) - (mu1[0]+mu2[0])*(mu1[0]+mu2[0]) -
			   (mu1[1]+mu2[1])*(mu1[1]+mu2[1]) - (mu1[2]+mu2[2])*(mu1[2]+mu2[2]) );
       
       // properties of Z
       double px_Z = mu1[0]+mu2[0];
       double py_Z = mu1[1]+mu2[1];
       double pT_Z = sqrt(px_Z*px_Z+py_Z*py_Z);
       
       _histos.Fill1D("ZCandMass", mass);
       _histos.Fill1D("ZCandPt", pT_Z);

       // fill muon quantities
       for(int imu=0; imu<2; imu++) {
	 _histos.Fill1D("ZCandMuPt", mupT[imu]);
	 _histos.Fill1D("ZCandMuInvPt", invmupT[imu]);
	 _histos.Fill1D("ZCandMuInvPt2", invmupT[imu]*invmupT[imu]);
	 _histos.Fill1D("ZCandMuEta", muons[imu]->Eta());
	 _histos.Fill1D("ZCandMuPhi", muons[imu]->Phi());
       }

     } // more requirements
   } // at least two muons

   // Study GEANT MC simulation
   if(_MCStudy) MCStudies(event, muons);

 } // get muon pointer
  return true;   
}

void ZMuAnalysis::MCStudies(cafe::Event& event, vector<CAFMuon*>& muons) {
  vector<TMBMCpart*> mc_muons;  
  if (event.get("muon mc objects", mc_muons)) {
    
    bool TwoCCMuons = false;  //only smear MC muons when two central reconstructed muons found

    // only look at Central-Central muons
    if(muons.size()>=2) {    
      if( (muons[0]->Pt()>20.) && (muons[1]->Pt()>20.) &&
	  (muons[0]->isMedium()) && (muons[1]->isMedium()) &&
	  (fabs(muons[0]->detectorEta())<1.2) && (fabs(muons[1]->detectorEta())<1.2) ) {

	TwoCCMuons = true;

	// find best matched mc muons for each reconstructed muon
	for(int imu=0; imu<2; imu++) {	  	  
	  double muonpT = muons[imu]->Pt();
	  _histos.Fill1D("ZCandCentralMuPt", muonpT);
	  _histos.Fill1D("ZCandCentralMuInvPt", 1./muonpT);
	  _histos.Fill1D("ZCandCentralMuInvPt2", 1./(muonpT*muonpT));
	   _histos.Fill1D("ZCandCentralMuEta", muons[imu]->Eta());
	   _histos.Fill1D("ZCandCentralMuPhi", muons[imu]->Phi());
	  
          int index_best_mc = -1;
	  double R_best = 9999.;
	  for(int imc=0; imc<mc_muons.size(); imc++) {
	    double R = kinem::delta_R(muons[imu]->Eta(), muons[imu]->Phi(),
				      mc_muons[imc]->Eta(), mc_muons[imc]->Phi());
	    if( (R_best>R) && (R<0.15) ) {
	      R_best = R;
	      index_best_mc = imc;
	    }
	  } // get best matched monte carlo muon
	  
	  if(R_best < 0.15) {
	    _histos.FillProfile("ZMCMuPt_V_ZRECOMuPt", mc_muons[index_best_mc]->Pt(), muons[imu]->Pt());
	    _histos.FillProfile("ZMCMuE_V_ZRECOMuE", mc_muons[index_best_mc]->E(), muons[imu]->E());
	    _histos.FillProfile("ZMCMuCurv_V_ZRECOMuCurv", 1./mc_muons[index_best_mc]->Pt(), 1./muons[imu]->Pt());
	    
	    double mc_pT = mc_muons[index_best_mc]->Pt();
	    double mc_invpT = 1./mc_pT;
	    int mc_invpT_region = -1;
	    char mc_invpT_region_char[10];
	    if(mc_invpT < 0.0185) mc_invpT_region = 0;
	    else if(mc_invpT < 0.0227) mc_invpT_region = 1;
	    else if(mc_invpT < 0.0263) mc_invpT_region = 2;
	    else if(mc_invpT < 0.033) mc_invpT_region = 3;
	    else mc_invpT_region = 4;
	    sprintf(mc_invpT_region_char, "%d", mc_invpT_region);
	    double reco_invpT = 1./muons[imu]->Pt();
	    
	    _histos.Fill1D("ZMCMuInvpTDiff", reco_invpT/mc_invpT-1.);
	    _histos.Fill1D(string("ZMCMuInvpTDiff_")+mc_invpT_region_char, reco_invpT/mc_invpT-1.);
	    _histos.Fill1D(string("ZMCMuPt_")+mc_invpT_region_char, mc_muons[index_best_mc]->Pt());
	    _histos.Fill1D(string("ZMCMuInvPt_")+mc_invpT_region_char, mc_invpT);	  
	  } // fill some histograms for the matched reconstructed muon and MC muon
	}// loop over 2 reconstructed muons
      }//central muons
    }// at least two reconstructed muons    

    //
    //smear mc muons and measure momentum scale and resolution
    //
    if(mc_muons.size()>=2 && TwoCCMuons) {
      
      double mc_pT[2], E_Smear[2], pT_Smear[2], pX_Smear[2], pY_Smear[2], pZ_Smear[2];
      double mc_Eta[2], mc_Phi[2], mc_Theta[2];
      for(int imc=0; imc<2; imc++) {
	mc_pT[imc] = mc_muons[imc]->Pt();
	mc_Eta[imc] = mc_muons[imc]->Eta();
	mc_Phi[imc] = mc_muons[imc]->Phi();
	double reso = sqrt(_A*_A*mc_pT[imc]*mc_pT[imc] + _B*_B);
	double randN1 = _random->Gaus(0., 1.);
	double randN2 = _random->Gaus(0., 1.);
	double randN3 = _random->Gaus(0., 1.);
	mc_Eta[imc] = mc_Eta[imc] * (1. + randN1*_eta_Resolution);
	mc_Phi[imc] = mc_Phi[imc] * (1. + randN2*_phi_Resolution);
	mc_Theta[imc] = 2.0*atan(exp(-mc_Eta[imc]));

        double InvpT_Smear = 1/(_C*mc_pT[imc]) + _CNonLinear * pow((1/mc_pT[imc] - 0.0246),2);
	pT_Smear[imc] = 1/(InvpT_Smear*(1+randN3*reso)); // need to times C
	E_Smear[imc] = pT_Smear[imc]/sin(mc_Theta[imc]);
	pX_Smear[imc] = E_Smear[imc] * sin(mc_Theta[imc]) * cos(mc_Phi[imc]);
	pY_Smear[imc] = E_Smear[imc] * sin(mc_Theta[imc]) * sin(mc_Phi[imc]);
	pZ_Smear[imc] = E_Smear[imc] * cos(mc_Theta[imc]);
	
	if(pT_Smear[imc]>20.) {
	  _histos.FillProfile("ZMCMuPt_V_ZSmearMuPt", mc_muons[imc]->Pt(), pT_Smear[imc]);
	  _histos.FillProfile("ZMCMuE_V_ZSmearMuE", mc_muons[imc]->E(), E_Smear[imc]);
	  _histos.FillProfile("ZMCMuCurv_V_ZSmearMuCurv", 1./mc_muons[imc]->Pt(), 1./pT_Smear[imc]);
	  
	  _histos.Fill1D("ZMCMuInvpTDiffSmear", mc_muons[imc]->Pt()/pT_Smear[imc]-1.);
	  _histos.Fill1D("ZMCMuPtSmear", pT_Smear[imc]);
	  _histos.Fill1D("ZMCMuInvPtSmear", 1./pT_Smear[imc]);
	} // good muons
      }
      
      if(pT_Smear[0]>20. && pT_Smear[1]>20.) {
	double mass_smear = sqrt( (E_Smear[0]+E_Smear[1])*(E_Smear[0]+E_Smear[1]) -
				  (pX_Smear[0]+pX_Smear[1])*(pX_Smear[0]+pX_Smear[1]) -
				  (pY_Smear[0]+pY_Smear[1])*(pY_Smear[0]+pY_Smear[1]) -
				  (pZ_Smear[0]+pZ_Smear[1])*(pZ_Smear[0]+pZ_Smear[1]) );
	
	double pT_Z_smear = sqrt( (pX_Smear[0]+pX_Smear[1])*(pX_Smear[0]+pX_Smear[1]) +
				  (pY_Smear[0]+pY_Smear[1])*(pY_Smear[0]+pY_Smear[1]) );
	
	_histos.Fill1D("ZMCMassSmear", mass_smear);
	_histos.Fill1D("ZMCPtSmear", pT_Z_smear);
      } // good mc muons
    }//at least two MC muons
        
  }// get pointer
}

void ZMuAnalysis::GetRegion(double cut1, double cut2, double cut3, double cut4,
                             double cut5, double cut6, double cut7, double cut8,
                             double cut9, double value, int& region) {
  if(value < cut1) region = 0;
  else if(value < cut2) region = 1;
  else if(value < cut3) region = 2;
  else if(value < cut4) region = 3;
  else if(value < cut5) region = 4;
  else if(value < cut6) region = 5;
  else if(value < cut7) region = 6;
  else if(value < cut8) region = 7;
  else if(value < cut9) region = 8;
  else region = 9;
}

void ZMuAnalysis::begin() {}

void ZMuAnalysis::finish() {
 cout<<"# of Zmumu candidates = "<<_NumZCand<<endl;
 TFile *file = histfiles::initializeTFile( this );
 if(file==NULL) return;
 string directory_name("ZMuCand_Hist");
 file->mkdir(directory_name.c_str());
 _histos.save(file, directory_name);
 file->Close();
}

ClassImp(ZMuAnalysis)
