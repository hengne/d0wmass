#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include "wmass_analysis/CosmicMuAnalysis.hpp"
#include "wmass_analysis/MuSelector.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "wmass_util/CAFMuon.hpp"
#include "wmass_analysis/histograms.hpp"
#include "wmass_util/hist_files.hpp"
#include <TFile.h>

using namespace std;
using namespace cafe;

CosmicMuAnalysis::CosmicMuAnalysis(const char *name)
  : Processor(name)
{
  Config config(name);

  _histos.add(CosmicMuCand_Hist);

  _NumCosmicCand = 0;

  _rand = new TRandom3(0);

  _histos.clone("CosmicCandSumEta_Eta", 6);
  _histos.clone("CosmicCandSumPhi_Eta", 6);
  _histos.clone("CosmicCandSumEta_DetEta", 6);
  _histos.clone("CosmicCandSumPhi_DetEta", 6);
  _histos.clone("CosmicCandSumEta_Run", 4);
  _histos.clone("CosmicCandSumPhi_Run", 4);
  _histos.clone("CosmicCandSumEta_Polarity", 2);
  _histos.clone("CosmicCandSumPhi_Polarity", 2);

  _global_vars.add("_solpol");
  _global_vars.add("_runno");
}

// process 
bool CosmicMuAnalysis::processEvent(cafe::Event& event) {

  // get solenoid polarity
  int solPolarity = event.getGlobal(_global_vars)->solpol();

 vector<CAFMuon*> muons_selector;
 if (event.get("Good Muons", muons_selector) ) {
   vector<CAFMuon*> muons;
   muons.clear();

   // get a new vector of muons with tight requirements
   for(int imu=0; imu<muons_selector.size(); imu++) {
     if( (muons_selector[imu]->Pt()>20.) && muons_selector[imu]->isLoose() ) 
       muons.push_back(muons_selector[imu]);
   }

  //at least two muons
   if(muons.size()>=2) {
     double mupT[2], invmupT[2];
     mupT[0] = muons[0]->Pt();
     mupT[1] = muons[1]->Pt();

     // select cosmic muon candidates
     if( (muons[0]->isCosmic()) || (muons[1]->isCosmic()) ) {
       
       double mass = sqrt( (muons[0]->E()+muons[1]->E()) * (muons[0]->E()+muons[1]->E()) -
			   (muons[0]->Px()+muons[1]->Px()) * (muons[0]->Px()+muons[1]->Px()) -
			   (muons[0]->Py()+muons[1]->Py()) * (muons[0]->Py()+muons[1]->Py()) -
			   (muons[0]->Pz()+muons[1]->Pz()) * (muons[0]->Pz()+muons[1]->Pz()) );
       
       double diff_time_As = muons[0]->sctimeA() - muons[1]->sctimeA();
       double sumEta = muons[0]->Eta() + muons[1]->Eta();
       double phi_diff = kinem::signed_delta_phi(muons[0]->Phi(), muons[1]->Phi());
       double sumPhi = 999.;
       if(phi_diff<-2.5) sumPhi = phi_diff + 3.1415926;
       if(phi_diff>2.5) sumPhi = phi_diff - 3.1415926;

       // use a random number to make diff_pT distribution symmetric around 0 
       double diff_pT = (mupT[0]-mupT[1])/(mupT[0]+mupT[1]);
       double randomN = _rand->Uniform(0., 1.);
       if(randomN<0.5) diff_pT = -diff_pT;
       
       // pT of the dimuon system
       double pX_muons = muons[0]->Px() + muons[1]->Px();
       double pY_muons = muons[0]->Py() + muons[1]->Py();
       double pT_muons = sqrt(pX_muons*pX_muons + pY_muons*pY_muons);

       _histos.Fill1D("CosmicCandTimeDiff", diff_time_As);
       _histos.Fill1D("CosmicCandSumEta2", sumEta);
       _histos.Fill1D("CosmicCandSumPhi2", sumPhi);

       // require two muons must have timing difference larger than 15 ns       
       if(fabs(diff_time_As) > 15.) {
	 _NumCosmicCand++;

	 _histos.Fill1D("CosmicCandSumEta", sumEta);
	 _histos.Fill1D("CosmicCandSumPhi", sumPhi);	 
	 _histos.Fill1D("CosmicCandDiffPt", diff_pT);
	 _histos.Fill1D("CosmicCandMass", mass);
	 _histos.Fill1D("CosmicCandPt", pT_muons);

	 // fill muon quantities
	 for(int imu=0; imu<2; imu++) {
	   _histos.Fill1D("CosmicCandMuEta", muons[imu]->Eta());
	   _histos.Fill1D("CosmicCandMuPhi", muons[imu]->Phi());
	   _histos.Fill1D("CosmicCandMuPt", muons[imu]->Pt());
	 }

	 // get sumEta and sumPhi vs phyiscs/detector eta of the second muon 
	 int region_Eta, region_DetEta, region_Run;
	 double Eta2 = muons[1]->Eta();
	 double DetEta2 = muons[1]->detectorEta();

	 // divide events into different physics eta region
	 if(Eta2<-1.) region_Eta = 0;
	 else if(Eta2<-0.5) region_Eta = 1;
	 else if(Eta2<0.) region_Eta = 2;
	 else if(Eta2<0.5) region_Eta = 3;
	 else if(Eta2<1.) region_Eta = 4;
	 else region_Eta = 5;
	 char region_Eta_char[10];	 
	 sprintf(region_Eta_char, "%d", region_Eta);

	 // divide events into different detector eta region
	 if(DetEta2<-1.) region_DetEta = 0;
	 else if(DetEta2<-0.5) region_DetEta = 1;
	 else if(DetEta2<0.) region_DetEta = 2;
	 else if(DetEta2<0.5) region_DetEta = 3;
	 else if(DetEta2<1.) region_DetEta = 4;
	 else region_DetEta = 5;
	 char region_DetEta_char[10];	 
	 sprintf(region_DetEta_char, "%d", region_DetEta);

	 // divide events into different run regions
	 int runno = event.getGlobal(_global_vars)->runno();
	 if(runno<189361) region_Run = 0;
	 else if(runno<170334) region_Run = 1;
	 else if(runno<180949) region_Run = 2;
	 else region_Run = 3;
	 char region_Run_char[10];	 
	 sprintf(region_Run_char, "%d", region_Run);

	 // for different polarity
	 char solPolarity_char[10];	 
	 sprintf(solPolarity_char, "%d", solPolarity);

	 _histos.Fill1D(string("CosmicCandSumEta_Eta_")+region_Eta_char, sumEta);
	 _histos.Fill1D(string("CosmicCandSumPhi_Eta_")+region_Eta_char, sumPhi);
	 _histos.Fill1D(string("CosmicCandSumEta_DetEta_")+region_DetEta_char, sumEta);
	 _histos.Fill1D(string("CosmicCandSumPhi_DetEta_")+region_DetEta_char, sumPhi);
	 _histos.Fill1D(string("CosmicCandSumEta_Run_")+region_Run_char, sumEta);
	 _histos.Fill1D(string("CosmicCandSumPhi_Run_")+region_Run_char, sumPhi);
	 _histos.Fill1D(string("CosmicCandSumEta_Polarity_")+solPolarity_char, sumEta);
	 _histos.Fill1D(string("CosmicCandSumPhi_Polarity_")+solPolarity_char, sumPhi);

       } // time difference requirement
      
     } // more requirements for two muons       
   } // at least two muons
 } // get muon pointer
  return true;   
}

void CosmicMuAnalysis::begin() {}

void CosmicMuAnalysis::finish() {
  cout<<"# of cosmic muon candidates = "<<_NumCosmicCand<<endl;
  TFile *file = histfiles::initializeTFile( this );
  if(file==NULL) return;
  string directory_name("CosmicMuCand_Hist");
  file->mkdir(directory_name.c_str());
  _histos.save(file, directory_name);
  file->Close();
}

ClassImp(CosmicMuAnalysis)
