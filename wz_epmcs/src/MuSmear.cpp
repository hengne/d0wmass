#include "MuSmear.hpp"
#include "AnglesUtil.hpp"

#include <cmath>
#include <iostream>

using namespace std;

// constructor and read smearing parameters
MuSmear::MuSmear(TString parameter_filename) {
  PParameterReader parm(parameter_filename.Data());

  cout<<"Start MuSmear initialization"<<endl;

  // smearing parameters  
  _etares_phy = parm.GetFloat("EtaResolution_Phys_CC", 0.001);
  _phires_phy = parm.GetFloat("PhiResolution_Phys_CC", 0.0001);

  _A = parm.GetFloat("A", 1.);
  _B = parm.GetFloat("B", 0.0);
  _C = parm.GetFloat("C", 0.15);
  
  cout<<"Finished MuSmear initialization"<<endl;
}

PMCSMuon MuSmear::SmearMuon(PMCSMuon& part_gen, TRandom3 *dummy) {
  
  PMCSMuon part_smear;
  part_smear = Smear(part_gen, _etares_phy, _phires_phy, 
		     _A, _B, _C, dummy);
  return part_smear;
}

vector<PMCSMuon> MuSmear::SmearMuons(vector<PMCSMuon> GenMuons, TRandom3 *dummy) {

  vector<PMCSMuon> SmearedMuons;
  for(int imu=0; imu<GenMuons.size(); imu++) {
    PMCSMuon smear = SmearMuon(GenMuons[imu], dummy);
    SmearedMuons.push_back(smear);
  }
  
  return SmearedMuons;
}

PMCSMuon MuSmear::Smear(PMCSMuon& part_gen,
		        double etares_phy, double phires_phy, 
		        double A, double B, double C, TRandom3 *dummy) {
  
  double phyeta_smeared, phyphi_smeared, theta_smeared;
  double momentum_smeared, energy_smeared;
  
  SmearPhysEtaPhi(part_gen, etares_phy, phires_phy, dummy, phyeta_smeared, phyphi_smeared);
  SmearMomentum(part_gen, A, B, C, dummy, momentum_smeared);
  theta_smeared = 2.0*atan(exp(-phyeta_smeared));

  PMCSMuon part_smear = part_gen;
  energy_smeared = momentum_smeared/sin(theta_smeared);
  
  part_smear.SetEnergyEtaPhi(energy_smeared, phyeta_smeared, phyphi_smeared);
  return part_smear;
}

void MuSmear::SmearPhysEtaPhi(PMCSMuon& part, double etares_phy, double phires_phy, TRandom3 *dummy, 
			      double& phyeta_smeared, double& phyphi_smeared) {

   phyeta_smeared = part.peta() + dummy->Gaus(0., 1.)*etares_phy;
   phyphi_smeared = part.pphi() + dummy->Gaus(0., 1.)*phires_phy;

   // I did not use the formula used in pmcs_chprt/chprt_smear.cpp
   // since I think the multiple scattering effect already being include in eta, phi resolution
   // measured from cosmic muon events, the formula used in chaprt_smear.cpp is the following:
   //double gen_theta = kinem::theta(part.peta());
   //double length=0;
   //if (fabs(sin(gen_theta))>0.358)  length=1.;   // Weight of track len in fiber tracker
   //else length=fabs(tan(gen_theta))/tan(0.366);  // John Rha's correction

   //double sigma_theta = sqrt(1.3*pow(0.025/(126*length),2)*pow(sin(gen_theta),4));
   //double sigma_phi = 0.51*_A/(pow(length,2));
   //double theta_smeared = gen_theta + dummy->Gaus(0., 1.)*sigma_theta;
   //phyeta_smeared = kinem::eta(theta_smeared);
   //phyphi_smeared = part.pphi() + dummy->Gaus(0., 1.)*sigma_phi;
}

void MuSmear::SmearMomentum(PMCSMuon& part, double A, double B, double C,
			    TRandom3 *dummy, double& momentum_smeared) {
   // copied from pmcs_chprt/chprt_smear.cpp
   double gen_theta = kinem::theta(part.peta());
   double length=0.;
   if (fabs(sin(gen_theta))>0.358)  length=1.;   // Weight of track len in fiber tracker
   else length=fabs(tan(gen_theta))/tan(0.366);  // John Rha's correction

   // use the simplied formula to smear track momentum
   // sigma(1/pT) / (1/pT) = sqrt(A^2*pT^2/L^4 + B^2/(Lsin(theta)))
   double length4 = pow(length, 4);
   double length_theta = length*sin(gen_theta);
   
   double reso_trk = sqrt(_A*_A*part.ppt()*part.ppt()/length4 + _B*_B/length_theta);
   //   double reso_trk = sqrt(_A*_A*part.ppt()*part.ppt() + _B*_B);
   double InvpT_Smear = 1/(_C*part.ppt());
   double rand = dummy->Gaus(0., 1.);
   momentum_smeared = 1/(InvpT_Smear *(1+rand*reso_trk));
}

void MuSmear::SetSmearParameters(double etares_phy, double phires_phy, double A, double B, double C) {
  _etares_phy = etares_phy;
  _phires_phy = phires_phy;
  _A = A;
  _B = B;
  _C = C;
}

