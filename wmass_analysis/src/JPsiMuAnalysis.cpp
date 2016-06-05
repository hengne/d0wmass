#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include "wmass_analysis/JPsiMuAnalysis.hpp"
#include "wmass_analysis/histograms.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "wmass_util/CAFMuon.hpp"
#include "wmass_util/WZ_Utils.hpp"
#include "wmass_util/hist_files.hpp"
#include <TFile.h>

using namespace std;
using namespace cafe;

JPsiMuAnalysis::JPsiMuAnalysis(const char *name)
  : Processor(name)
{
  Config config(name);

  _histos.add(JPsiMuCand_Hist);

  _NumJPsiCand = 0;

  // histograms for different regions
  _histos.clone("JPsiCandMass_MuInvPt",10);
  _histos.clone("JPsiCand_MuInvPt",10);
  _histos.clone("JPsiCandMass_MuInvPt2",10);
  _histos.clone("JPsiCand_MuInvPt2",10);
  _histos.clone("JPsiCandMass_MuPt",10);
  _histos.clone("JPsiCand_MuPt",10);
  _histos.clone("JPsiCandMass_MuAveInvPt",10);
  _histos.clone("JPsiCand_MuAveInvPt",10);
  _histos.clone("JPsiCandMass_MuAveInvPt2",10);
  _histos.clone("JPsiCand_MuAveInvPt2",10);
  _histos.clone("JPsiCandMass_MuAvePt",10);
  _histos.clone("JPsiCand_MuAvePt",10);
  _histos.clone("JPsiCandMass_JPsiPt",10);
  _histos.clone("JPsiCand_JPsiPt",10);
  _histos.clone("JPsiCandMass_DCosTheta",10);     
  _histos.clone("JPsiCand_DCosTheta",10);     
  _histos.clone("JPsiCandMass_SumInvSinTheta",10);     
  _histos.clone("JPsiCand_SumInvSinTheta",10);    
  // for different J/Psi eta region 
  _histos.clone("JPsiCandMass_JPsiPhi_Eta1",10);
  _histos.clone("JPsiCand_JPsiPhi_Eta1",10);
  _histos.clone("JPsiCandMass_JPsiPhi_Eta2",10);
  _histos.clone("JPsiCand_JPsiPhi_Eta2",10);
  _histos.clone("JPsiCandMass_JPsiPhi_Eta3",10);
  _histos.clone("JPsiCand_JPsiPhi_Eta3",10);
  _histos.clone("JPsiCandMass_JPsiPhi_Eta4",10);
  _histos.clone("JPsiCand_JPsiPhi_Eta4",10);
  _histos.clone("JPsiCandMass_JPsiPhi_Eta5",10);
  _histos.clone("JPsiCand_JPsiPhi_Eta5",10);
  // for runs
  _histos.clone("JPsiCandMass_Run", 34);
  _histos.clone("JPsiCand_Run", 34);

  _global_vars.add("_runno");
}

// process 
bool JPsiMuAnalysis::processEvent(cafe::Event& event) {

 vector<CAFMuon*> muons;
 if (event.get("Good Muons", muons) ) {
  //at least two muons
   if(muons.size()>=2) {
     
     TMBLorentzVector mu1(muons[0]->Px(), muons[0]->Py(), muons[0]->Pz(), muons[0]->E());
     TMBLorentzVector mu2(muons[1]->Px(), muons[1]->Py(), muons[1]->Pz(), muons[1]->E());
     
     double mass = sqrt( (mu1[3]+mu2[3])*(mu1[3]+mu2[3]) - (mu1[0]+mu2[0])*(mu1[0]+mu2[0]) -
			 (mu1[1]+mu2[1])*(mu1[1]+mu2[1]) - (mu1[2]+mu2[2])*(mu1[2]+mu2[2]) );
     
     // muon quality and dimuon mass requirement
     if( ((muons[0]->nseg()>=3) || (muons[1]->nseg()>=3)) &&
         (mass > 2.5 && mass < 3.7) && 
	 (muons[0]->charge()*muons[1]->charge()==-1) &&
         !(muons[0]->isCosmic()) && !(muons[1]->isCosmic()) ) {     
       
       _NumJPsiCand++;
       int runno = event.getGlobal(_global_vars)->runno();

       // muon quantities
       double mupT[2], invmupT[2], invmupT2[2], muCharge[2], muTheta[2];
       for (int imu=0; imu<2; imu++) {
	 mupT[imu] = muons[imu]->Pt();
	 invmupT[imu] = 1./mupT[imu];
	 invmupT2[imu] = invmupT[imu]*invmupT[imu];
	 muCharge[imu] = muons[imu]->charge();
	 muTheta[imu] = muons[imu]->Theta();
	 
	 _histos.Fill1D("JPsiCandMuPt", mupT[imu]);
	 _histos.Fill1D("JPsiCandMuInvPt", invmupT[imu]);
	 _histos.Fill1D("JPsiCandMuInvPt2", invmupT2[imu]);
	 _histos.Fill1D("JPsiCandMuEta", muons[imu]->Eta());
	 _histos.Fill1D("JPsiCandMuPhi", muons[imu]->Phi());
       }
       
       double SumInvSinTheta = TMath::Abs(1./sin(muTheta[0])) + TMath::Abs(1./sin(muTheta[1]));

       double invpT_average = (invmupT[0]+invmupT[1])/2.;
       double invpT2_average = (invmupT2[0]+invmupT2[1])/2.;
       double pT_average = (mupT[0]+mupT[1])/2.;
       
       //open angle between two muons
       TVector3 mu2_vec(mu2[0], mu2[1], mu2[2]);
       double angle_Mu_Mu = mu1.Angle(mu2_vec);
       
       // properties of JPsi
       double px_jpsi = mu1[0]+mu2[0];
       double py_jpsi = mu1[1]+mu2[1];
       double pz_jpsi = mu1[2]+mu2[2];
       double pT_jpsi = sqrt(px_jpsi*px_jpsi+py_jpsi*py_jpsi);
       double phi_jpsi = kinem::phi(px_jpsi, py_jpsi);
       double eta_jpsi = kinem::eta(px_jpsi, py_jpsi, pz_jpsi); 
 
       //opening polar angle delta_cotTheta = cotTheta(+)-cotTheta(-)
       double delta_cotTheta = 0.;
       if(muTheta[0]!=0. && muTheta[1]!=0.) {
	 if(muCharge[0]==1) delta_cotTheta = 1./TMath::Tan(muTheta[0])-1./TMath::Tan(muTheta[1]);
	 else delta_cotTheta = 1./TMath::Tan(muTheta[1])-1./TMath::Tan(muTheta[0]);
       }

       // fill mass for different 1/pT region (for second muon)
       int region_invpt = -1;
       char region_invpt_char[10];
       GetRegion(0.12, 0.17, 0.2, 0.23, 0.26, 0.3, 0.33, 0.36, 0.4, invmupT[1], region_invpt);   
       sprintf(region_invpt_char, "%d", region_invpt); 
       
       // fill mass for different (1/pT)^2 region (for second muon)
       int region_invpt2 = -1;
       char region_invpt2_char[10];
       GetRegion(0.0144, 0.04, 0.0625, 0.09, 0.1225, 0.16, 0.25, 0.4225, 0.64, invmupT2[1], region_invpt2);   
       sprintf(region_invpt2_char, "%d", region_invpt2); 
       
       // fill mass for different muon pT region (for second muon)
       int region_mupt = -1;
       char region_mupt_char[10];
       GetRegion(1.25, 1.53, 2., 2.5, 2.86, 3.33, 4., 5., 8.33, mupT[1], region_mupt);   
       sprintf(region_mupt_char, "%d", region_mupt); 
       
       // fill mass for average 1/pT region
       int region_invpt_average = -1;
       char region_invpt_average_char[10];
       GetRegion(0.15, 0.2, 0.22, 0.25, 0.27, 0.29, 0.32, 0.35, 0.4, invpT_average, region_invpt_average);    
       sprintf(region_invpt_average_char, "%d", region_invpt_average); 
       
       // fill mass for average (1/pT)^2 region
       int region_invpt2_average = -1;
       char region_invpt2_average_char[10];
       GetRegion(0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, invpT2_average, region_invpt2_average);    
       sprintf(region_invpt2_average_char, "%d", region_invpt2_average); 
       
       // fill mass for average muon pT region
       int region_mupt_average = -1;
       char region_mupt_average_char[10];
       GetRegion(2.6, 3.0, 3.4, 3.7, 4., 4.3, 4.8, 5.2, 7.33, pT_average, region_mupt_average);   
       sprintf(region_mupt_average_char, "%d", region_mupt_average); 
       
       // fill mass for JPsi pT
       int region_jpsipt = -1;
       char region_jpsipt_char[10];
       GetRegion(2., 4., 6., 8., 10., 12., 14., 16., 18., pT_jpsi, region_jpsipt);   
       GetRegion(5., 6., 7.5, 8.5, 9.5, 11., 13., 15., 17., pT_jpsi, region_jpsipt);   
       sprintf(region_jpsipt_char, "%d", region_jpsipt); 
       
       // fill mass for JPsi phi
       int region_jpsiphi = -1;
       char region_jpsiphi_char[10];
       GetRegion(0.628, 1.256, 1.884, 2.512, 3.14, 3.768, 4.396, 5.024, 5.652, phi_jpsi, region_jpsiphi);   
       sprintf(region_jpsiphi_char, "%d", region_jpsiphi); 

       // fill mass for delta_cosTheta
       int region_dcotTheta = -1;
       char region_dcotTheta_char[10];
       GetRegion(-1.2, -0.9, -0.6, -0.3, 0., 0.3, 0.6, 0.9, 1.2, delta_cotTheta, region_dcotTheta);   
       sprintf(region_dcotTheta_char, "%d", region_dcotTheta); 

       // fill mass for open angle region
       int region_angle = -1;
       char region_angle_char[10];
       GetRegion(0.28, 0.35, 0.4, 0.48, 0.55, 0.6, 0.7, 0.9, 1.2, angle_Mu_Mu, region_angle);    
       sprintf(region_angle_char, "%d", region_angle); 
       
       // fill mass for |1./sinTheta1| + |1./sinTheta2| region
       int region_sumSinTheta = -1;
       char region_sumSinTheta_char[10];
       GetRegion(2.28, 2.70, 3.1, 3.3, 3.5, 3.7, 3.9, 4.1, 4.5, SumInvSinTheta, region_sumSinTheta);    
       sprintf(region_sumSinTheta_char, "%d", region_sumSinTheta); 

       // fill mass for different run region
       int region_Run = -1;
       char region_Run_char[10];
       int run_regions[34];
       for(int i=0; i<34; i++) run_regions[i] = 164000 + i*1000;
       vector<double> run_vect(run_regions, run_regions+34);
       wz_utils::FindRegion(run_vect, runno, region_Run);
       sprintf(region_Run_char, "%d", region_Run); 

       // Fill histograms for different bins 
       _histos.Fill1D(string("JPsiCandMass_MuInvPt_")+region_invpt_char, mass);
       _histos.Fill1D(string("JPsiCand_MuInvPt_")+region_invpt_char, invmupT[1]);
       _histos.Fill1D(string("JPsiCandMass_MuInvPt2_")+region_invpt2_char, mass);
       _histos.Fill1D(string("JPsiCand_MuInvPt2_")+region_invpt2_char, invmupT2[1]);
       _histos.Fill1D(string("JPsiCandMass_MuPt_")+region_mupt_char, mass);
       _histos.Fill1D(string("JPsiCand_MuPt_")+region_mupt_char, mupT[1]);
       _histos.Fill1D(string("JPsiCandMass_MuAveInvPt_")+region_invpt_average_char, mass);
       _histos.Fill1D(string("JPsiCand_MuAveInvPt_")+region_invpt_average_char, invpT_average);
       _histos.Fill1D(string("JPsiCandMass_MuAveInvPt2_")+region_invpt2_average_char, mass);
       _histos.Fill1D(string("JPsiCand_MuAveInvPt2_")+region_invpt2_average_char, invpT2_average);
       _histos.Fill1D(string("JPsiCandMass_MuAvePt_")+region_mupt_average_char, mass);
       _histos.Fill1D(string("JPsiCand_MuAvePt_")+region_mupt_average_char, pT_average);
       _histos.Fill1D(string("JPsiCandMass_JPsiPt_")+region_jpsipt_char, mass);
       _histos.Fill1D(string("JPsiCand_JPsiPt_")+region_jpsipt_char, pT_jpsi); 
       _histos.Fill1D(string("JPsiCandMass_DCosTheta_")+region_dcotTheta_char, mass);     
       _histos.Fill1D(string("JPsiCand_DCosTheta_")+region_dcotTheta_char, delta_cotTheta);      
       _histos.Fill1D(string("JPsiCandMass_SumInvSinTheta_")+region_sumSinTheta_char, mass);     
       _histos.Fill1D(string("JPsiCand_SumInvSinTheta_")+region_sumSinTheta_char, SumInvSinTheta);     
       _histos.Fill1D(string("JPsiCandMass_Run_")+region_Run_char, mass);     
       _histos.Fill1D(string("JPsiCand_Run_")+region_Run_char, runno);     
 
       // require DeltaPhi(mu, mu)<pi/3 in order for the J/psi direction to represent muon track directions
       if(fabs(muons[0]->Phi() - muons[1]->Phi())<1.05) {
         if(eta_jpsi>-1. && eta_jpsi<-0.6) { 
	   _histos.Fill1D(string("JPsiCandMass_JPsiPhi_Eta1_")+region_jpsiphi_char, mass);     
	   _histos.Fill1D(string("JPsiCand_JPsiPhi_Eta1_")+region_jpsiphi_char, phi_jpsi);      
         } else if(eta_jpsi>-0.6 && eta_jpsi<-0.2) {
	   _histos.Fill1D(string("JPsiCandMass_JPsiPhi_Eta2_")+region_jpsiphi_char, mass);     
	   _histos.Fill1D(string("JPsiCand_JPsiPhi_Eta2_")+region_jpsiphi_char, phi_jpsi);      
         } else if(eta_jpsi>-0.2 && eta_jpsi<0.2) {
	   _histos.Fill1D(string("JPsiCandMass_JPsiPhi_Eta3_")+region_jpsiphi_char, mass);     
	   _histos.Fill1D(string("JPsiCand_JPsiPhi_Eta3_")+region_jpsiphi_char, phi_jpsi);      
         } else if(eta_jpsi>0.2 && eta_jpsi<0.6) {
	   _histos.Fill1D(string("JPsiCandMass_JPsiPhi_Eta4_")+region_jpsiphi_char, mass);     
	   _histos.Fill1D(string("JPsiCand_JPsiPhi_Eta4_")+region_jpsiphi_char, phi_jpsi);      
         } else if(eta_jpsi>0.6 && eta_jpsi<1.) {
	   _histos.Fill1D(string("JPsiCandMass_JPsiPhi_Eta5_")+region_jpsiphi_char, mass);     
	   _histos.Fill1D(string("JPsiCand_JPsiPhi_Eta5_")+region_jpsiphi_char, phi_jpsi);      
         } 
       }

       // fill distributions for each variable
       _histos.Fill1D("JPsiCand_MuInvPt", invmupT[1]);
       _histos.Fill1D("JPsiCand_MuInvPt2", invmupT2[1]);
       _histos.Fill1D("JPsiCand_MuPt", mupT[1]);
       _histos.Fill1D("JPsiCand_MuAveInvPt", invpT_average);
       _histos.Fill1D("JPsiCand_MuAveInvPt2", invpT2_average);
       _histos.Fill1D("JPsiCand_MuAvePt", pT_average);
       _histos.Fill1D("JPsiCand_JPsiPt", pT_jpsi);      
       _histos.Fill1D("JPsiCand_DCosTheta", delta_cotTheta);      
       _histos.Fill1D("JPsiCand_SumInvSinTheta", SumInvSinTheta);      
       
       _histos.Fill1D("JPsiCandMass", mass);
       _histos.Fill1D("JPsiCandPt", pT_jpsi);
       _histos.Fill1D("JPsiCandMuAngle", angle_Mu_Mu);
       
       _histos.Fill1D("JPsiCandSecMuPt", mupT[1]);
       _histos.Fill1D("JPsiCandSecMuInvPt", invmupT[1]);
       _histos.Fill1D("JPsiCandSecMuInvPt2", invmupT2[1]);
       
     } // mass requirement
   } // at least two muons
 } // get muon pointer
  return true;   
}

void JPsiMuAnalysis::GetRegion(double cut1, double cut2, double cut3, double cut4,
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

void JPsiMuAnalysis::begin() {}

void JPsiMuAnalysis::finish() {
 cout<<"# of JPsi candiates = "<<_NumJPsiCand<<endl;
 TFile *file = histfiles::initializeTFile( this );
 if(file==NULL) return;
 string directory_name("JPsiMuCand_Hist");
 file->mkdir(directory_name.c_str());
 _histos.save(file, directory_name);
 file->Close();
}

ClassImp(JPsiMuAnalysis)
