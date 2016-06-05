#ifndef INC_WZUTILS
#define INC_WZSUTILS

#include <cmath>
#include <cstdlib>
#include "kinem_util/AnglesUtil.hpp"
#include "TRandom3.h"
#include <iostream>
#include <vector>
#include <TString.h>
#include "TComplex.h"
#include "tmb_tree/TMBCaloCell.hpp"
#include "wmass_util/CaloGeometryManager.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "wmass_util/CAFTrack.hpp"
#include "wmass_util/CAFWCand.hpp"

namespace wz_utils {
  const double PI=2.0*acos(0.);
  const double TWOPI=2.0*PI;
  const double ETA_LIMIT=15.0;
  const double EPSILON=1.E-10;

  const double CC_XSHIFT=-0.33;
  const double CC_YSHIFT=-0.46;
  const double CC_ZSHIFT=-3.2;

  const double EC_3Z_NORTH=-182.8;
  const double EC_XSHIFT_NORTH=0.38;
  const double EC_YSHIFT_NORTH=0.00;

  const double EC_3Z_SOUTH=179.;
  const double EC_XSHIFT_SOUTH=0.0;
  const double EC_YSHIFT_SOUTH=0.0;

  const double CC_3R=91.9;
  const double EC_3Z=178.9;

  const double EC_R_MAX=85.0;
  const double CC_Z_MAX=115.0;

  const double B_field = 2.;

  // code used to study W mass for different cuts
  bool passCut(TString cut_under_study, bool invert_cut, 
			  int runNo, int runNo_lowcut,  int runNo_highcut,
              int tickNo, int tickNo_lowcut , int tickNo_highcut,
	       double InstLumi, double InstLumi_lowcut, double InstLumi_highcut,
	       double ScalarEt, double ScalarEt_lowcut, double ScalarEt_highcut,
               double ElecEta, double ElecEta_cut,
	       double ElecDetEta, double ElecDetEta_lowcut, double ElecDetEta_highcut,
	       double ElecPhiMod, double ElecPhiMod_cut,
	       double UPara, double UPara_lowcut, double UPara_highcut,
	       double ElecPt, double ElecPt_lowcut, double ElecPt_highcut,
	       double ElecPhi, double ElecPhi_lowcut, double ElecPhi_highcut,
	       double RecoilPhi, double RecoilPhi_lowcut, double RecoilPhi_highcut,
           double ZPTee,  double ZPTee_lowcut, double ZPTee_highcut);

  // encode calorimeter cell (ieta, iphi, ilyr) to a unique integer
  int EncodeCellIndex(int ieta, int iphi, int ilyr);

  // decode a unique integer to calorimeter cell address (ieta, iphi, ilyr)
  void DecodeCellIndex(int cell_index, int& ieta, int& iphi, int& ilyr);

  // calculate new Ex, Ey, ET of a cell for an arbitrary primary vertex
  //          E - cell's total energy
  // cellpos[3] - cell's Cartesian position wrt detector center
  //     vtx[3] - Cartesian position of the new vertex wrt detector center
  void RevertexCell(float E, float cellpos[3], float new_vtx[3],
		    double &new_ETx, double &new_ETy, double &new_ET);
  void RevertexCell(double E, double direction_vect[3],
		    double &new_ETx, double &new_ETy, double &new_ET);

  // for a given vector of cuts and a given value, find the corresponding region
  void FindRegion(std::vector<double>& cut_vect, double value, int& region);
  
  // revertexing and calculate impact parameter, phi for a track with given b0, phi0
  // distance_vertices is a spatial vector (new vertex - old vertex) 
  void BeamSpotCorrection(float b0, float phi0, float& b1,
			  float& phi1, float kappa, float distance_vertices[3]);

  // functions used for bremsstralung simulation
  double BremProba(double y, double k);
  void brem_simulation(double radiation_length, double y_min, int bin_y, double k,
		       double proba[50], double& proba_total, double& elec_energy_fraction, TRandom3 *random);

  // from true recoil pT and phi to smeared pT and phi
  void FlipARecoil2(double truepT, double truephi, double& smpT, double& smphi, double RelScale, double RelOffset);

  // determine pT_ee * eta direction region
  int pTee_Eta_Bin(double pee_eta);

  // define upara bins for uparallel efficiency studies
  int UParaBins(double UPara);

  // trigger category (according to note 5374)
  int TriggerCategory(int runno);
  
  // extrapolate the track to the EM3 layer
  // r0, z0, phi0, eta, qoverpt = track at DCA in global frame
  // rclu - cluster position in (x, y) 
  // E - EM cluster energy
  // r_xy - cluster position in global frame
  void CC_extrap(int matchingFloor, double r0, double z0, double phi0, double eta, int solenoid_polarity, 
 		 double qoverpt, double em_E, double r_xy, double& xtra, double& ytra, double& ztra, bool isGeantMC=false);
  
  void CC_extrap_track(CAFTrack *track, int solenoid_polarity, int matchingFloor, 
 		       double em_E, double r_xy, double& xtra, double& ytra, double& ztra, bool isGeantMC=false);

  void CC_extrap_track(const TMBTrack *track, int solenoid_polarity, int matchingFloor, 
 		       double em_E, double r_xy, double& xtra, double& ytra, double& ztra, bool isGeantMC=false);
  

  // simple extrapolation
  void simple_extrap(double vtx, double eta, double phi, double& deteta, double& detphi);
  
  // calculate the recoil and ET-flow per PHI tower in an event  
  void calc_Et_per_tower(cafe::Event& event,                      // input
			 std::vector<CAFEMObj*> emobjs,           // input
			 double phi_direction,                    // input
			 float  vtx[3],                           // input
			 std::map<int, double> &RelResponse_scale,// input
			 TVector2 &raw_calcells_Recoil,           // output
			 TVector2 &raw_calcells_Recoil_scaled,    // output
			 TVector2 &raw_calcells_Recoil_xcheck,    // output
			 std::map<int, double> &Et_flow,          // output
			 std::map<int, double> &Et_flow_scaled,   // output
			 int _debugLevel=0 );

 // for singularity variable study
  float SingularityVariable(CAFWCand& wcand, float trialmass, TRandom3* dummy); //main SV method

  inline float SingularityVariable(CAFWCand& wcand, float trialmass, TRandom3* dummy) {
    
    // The lepton and recoil four momenta
    TLorentzVector lepton;
    lepton.SetPxPyPzE(wcand.EM()->Px(), wcand.EM()->Py(), wcand.EM()->Pz(), wcand.EM()->E()); 
    TLorentzVector recoil(wcand.GetRecoil().X(), wcand.GetRecoil().Y(), 0., wcand.MagRecoil());
    
    // Azimuthal angle between lepton and recoil
    Double_t dphi(lepton.DeltaPhi(recoil)); 

    // Maximum lepton momentum
    Double_t lptm(trialmass * trialmass / (2 * (TMath::Sqrt(trialmass*trialmass + recoil.Pt()*recoil.Pt()) + recoil.Pt()*TMath::Cos(dphi))));

    Double_t pm = 0;    
    if (dummy->Rndm() > 0.5) pm = 1.;
    else pm = -1.;

    // Randomly select one on the neutrino solutions...
    TComplex disc(trialmass * trialmass + recoil.Pt() * recoil.Pt());
    TComplex x3(lepton.Pz() * (trialmass*trialmass + 2 * recoil.Pt() * (recoil.Pt() + pm * TMath::Cos(dphi) * TMath::Sqrt(disc)))/(trialmass*trialmass));

    // ... and corresponding W solution
    Double_t W3 = lepton.Pz() +  TComplex::Abs(x3);
    
    // The normal vector to the phase space manifold
    TVector3 normal(-4 * (recoil.Pt()*TMath::Cos(dphi) * (2*lepton.Pz()*W3 + trialmass*trialmass) + 2*lepton.Pt()*(trialmass*trialmass + recoil.Pt()*recoil.Pt()*TMath::Sin(dphi)*TMath::Sin(dphi) + W3*W3)),
		    -4*(lepton.Pz()*trialmass*trialmass + 2*lepton.Pz()*recoil.Pt()*recoil.Pt() + 2*W3*lepton.Pt()*lepton.Pt() - trialmass*trialmass*W3) - 8*lepton.Pt()*(lepton.Pz() + W3)*recoil.Pt()*TMath::Cos(dphi),
		    4*lepton.Pz()*(trialmass*trialmass - 2*lepton.Pt()*recoil.Pt()*TMath::Cos(dphi)) - 8*lepton.Pt()*lepton.Pt()*W3);

    // The singularity variable (define up to a minus sign from what is in arXiv:1106.0396v2)
    Double_t sigma = (lptm - lepton.Pt())/(normal.X()/normal.Mag());
    return sigma;

  }

}


// code used to study W mass for different cuts
inline bool wz_utils::passCut(TString cut_under_study, bool invert_cut, 
			      int runNo, int runNo_lowcut,  int runNo_highcut,
                             int tickNo, int tickNo_lowcut , int tickNo_highcut,
			      double InstLumi, double InstLumi_lowcut, double InstLumi_highcut,
			      double ScalarEt, double ScalarEt_lowcut, double ScalarEt_highcut,
                              double ElecEta, double ElecEta_cut,
			      double ElecDetEta, double ElecDetEta_lowcut, double ElecDetEta_highcut,
			      double ElecPhiMod, double ElecPhiMod_cut,
			      double UPara, double UPara_lowcut, double UPara_highcut,
			      double ElecPt, double ElecPt_lowcut, double ElecPt_highcut,
			      double ElecPhi, double ElecPhi_lowcut, double ElecPhi_highcut,
			      double RecoilPhi, double RecoilPhi_lowcut, double RecoilPhi_highcut,
                  double ZPTee,  double ZPTee_lowcut, double ZPTee_highcut) {
  bool passTheCut = true;
  if (cut_under_study.Contains("runNo_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (runNo<runNo_lowcut) || (runNo>runNo_highcut) );
    else passTheCut = passTheCut&&( (runNo>=runNo_lowcut) && (runNo<=runNo_highcut) );
  }
  if (cut_under_study.Contains("tickNo_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (tickNo<tickNo_lowcut) || (tickNo>tickNo_highcut) );
    else passTheCut = passTheCut&&( (tickNo>=tickNo_lowcut) && (tickNo<=tickNo_highcut) );
  }
  if (cut_under_study.Contains("InstLumi_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (InstLumi<InstLumi_lowcut) || (InstLumi>InstLumi_highcut) );
    else passTheCut = passTheCut&&( (InstLumi>=InstLumi_lowcut) && (InstLumi<=InstLumi_highcut) );
  }
  if(cut_under_study.Contains("ScalarEt_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (ScalarEt<ScalarEt_lowcut) || (ScalarEt>ScalarEt_highcut) );
    else passTheCut = passTheCut&&( (ScalarEt>=ScalarEt_lowcut) && (ScalarEt<=ScalarEt_highcut) );
  }
  if(cut_under_study.Contains("UPara_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (UPara<UPara_lowcut) || (UPara>UPara_highcut) );
    else passTheCut = passTheCut&&( (UPara>=UPara_lowcut) && (UPara<=UPara_highcut) );
  }
  if(cut_under_study.Contains("ElecEta_cut")) {
    if(invert_cut) passTheCut = passTheCut&&(fabs(ElecEta)>ElecEta_cut);
    else passTheCut = passTheCut&&(fabs(ElecEta)<=ElecEta_cut);
  }
  if(cut_under_study.Contains("ElecDetEta_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (fabs(ElecDetEta)<ElecDetEta_lowcut) || (fabs(ElecDetEta)>ElecDetEta_highcut) );
    else passTheCut = passTheCut&&( (fabs(ElecDetEta)>=ElecDetEta_lowcut) && (fabs(ElecDetEta)<=ElecDetEta_highcut) );
  }
  if(cut_under_study.Contains("ElecPhiMod_cut")) {
    if(invert_cut) passTheCut = passTheCut&&(ElecPhiMod<(0.5-ElecPhiMod_cut/2) || ElecPhiMod>(0.5+ElecPhiMod_cut/2));
    else passTheCut = passTheCut&&(ElecPhiMod>(0.5-ElecPhiMod_cut/2) && ElecPhiMod<(0.5+ElecPhiMod_cut/2));
  }
  if(cut_under_study.Contains("ElecPt_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (ElecPt<ElecPt_lowcut) || (ElecPt>ElecPt_highcut) );
    else passTheCut = passTheCut&&( (ElecPt>=ElecPt_lowcut) && (ElecPt<=ElecPt_highcut) );
  }
  if(cut_under_study.Contains("ElecPhi_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (ElecPhi<ElecPhi_lowcut) || (ElecPhi>ElecPhi_highcut) );
    else passTheCut = passTheCut&&( (ElecPhi>=ElecPhi_lowcut) && (ElecPhi<=ElecPhi_highcut) );
  }
  if(cut_under_study.Contains("RecoilPhi_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (RecoilPhi<RecoilPhi_lowcut) || (RecoilPhi>RecoilPhi_highcut) );
    else passTheCut = passTheCut&&( (RecoilPhi>=RecoilPhi_lowcut) && (RecoilPhi<=RecoilPhi_highcut) );
  }
  if(cut_under_study.Contains("ZPTee_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (ZPTee<ZPTee_lowcut) || (ZPTee>ZPTee_highcut) );
    else passTheCut = passTheCut&&( (ZPTee>=ZPTee_lowcut) && (ZPTee<=ZPTee_highcut) );
  }

  return passTheCut;
}

inline void wz_utils::CC_extrap_track(const TMBTrack *track, int solenoid_polarity, int matchingFloor, 
				      double em_E, double r_xy, double& xtra, double& ytra, double& ztra, bool isGeantMC) {
  double r0 = track->rdca();
  double z0 = track->z();
  double phi0 = track->phid();
  double tanlam = track-> tlm();
  double eta = log(sqrt(1+tanlam*tanlam) + tanlam);
  double qoverpt = track->qpt();
  CC_extrap(matchingFloor, r0, z0, phi0, eta, solenoid_polarity, qoverpt, em_E, r_xy, xtra, ytra, ztra, isGeantMC);
}

inline void wz_utils::CC_extrap_track(CAFTrack *track, int solenoid_polarity, int matchingFloor,
				      double em_E, double r_xy, double& xtra, double& ytra, double& ztra, bool isGeantMC) {
  double r0 = track->rdca();
  double z0 = track->z();
  double phi0 = track->phid();
  double tanlam = track-> tlm();
  double eta = log(sqrt(1+tanlam*tanlam) + tanlam);
  double qoverpt = track->qpt();
  CC_extrap(matchingFloor, r0, z0, phi0, eta, solenoid_polarity, qoverpt, em_E, r_xy, xtra, ytra, ztra, isGeantMC);
}

inline void wz_utils::CC_extrap(int matchingFloor, double r0, double z0, double phi0, double eta,
				int solenoid_polarity, double qoverpt, double em_E, double r_xy, 
				double& xtra, double& ytra, double& ztra, bool isGeantMC) {
  // Masato added
  // r0 = -r0;   // do not need this since we modify the line with ytra
  
  // 1. extrapolate in phi/y
  double Et = em_E/cosh(eta);
  double qoverEt = solenoid_polarity*qoverpt/fabs(qoverpt)/Et;

  // 22.55 cm used for data and 21.65 cm used for GEANT from em_util package
  // but I found that if we use these two numbers, the phi difference between electrons and positrons
  // will not agree with each other, 21cm gives the best agreement
  double slope[4] = {20.5, 21.2, 21., 25.0};
  if(isGeantMC) slope[2] = 21.;
  ytra = -r0 + slope[matchingFloor-1] * qoverEt;
  
  // 2. extrapolate in z
  double tanl = sinh(eta);
  ztra = z0 + r_xy*tanl;
  
  // 3. correct for inclined showers
  double zlim = 1.1, zsl = 2.0;
  if(tanl > zlim) ztra -= zsl * (tanl - zlim);
  if(tanl < -zlim) ztra -= zsl * (tanl + zlim);
  
  // 4. beam spot position
  double c0 = cos(phi0);
  double s0 = sin(phi0);
  xtra = r_xy * c0 - ytra * s0;
  ytra = r_xy * s0 + ytra * c0;
}

// simple extrapolation
inline void wz_utils::simple_extrap(double vtx, double eta, double phi, double& deteta, double& detphi) {
  double mc_vtx_z = vtx;
	
  double theta_mc = kinem::theta(eta);
  double phi_mc = phi;
  
  double zem3 = mc_vtx_z + CC_3R/tan(theta_mc);	
  double det_x, det_y, det_theta, det_r;
  if(zem3 > 125.){  // pos EC
    double trk_r = fabs((EC_3Z_SOUTH-mc_vtx_z)*tan(theta_mc));
    det_x = trk_r*cos(phi_mc) - EC_XSHIFT_SOUTH;
    det_y = trk_r*sin(phi_mc) - EC_YSHIFT_SOUTH;
    det_r = sqrt(det_x*det_x +det_y*det_y);
    det_theta = atan2(det_r, EC_3Z);
  } else if(zem3 > -125.) { // CC
    det_x = CC_3R*cos(phi_mc) - CC_XSHIFT;
    det_y = CC_3R*sin(phi_mc) - CC_YSHIFT;
    det_r = sqrt(det_x*det_x +det_y*det_y);
    det_theta = atan2(det_r, zem3-CC_ZSHIFT);
  } else { // neg EC
    double trk_r = fabs((EC_3Z_NORTH-mc_vtx_z)*tan(theta_mc));
    det_x = trk_r*cos(phi_mc) - EC_XSHIFT_NORTH;
    det_y = trk_r*sin(phi_mc) - EC_YSHIFT_NORTH;
    det_r = sqrt(det_x*det_x +det_y*det_y);
    det_theta = atan2(det_r, -EC_3Z);
  }

  // extrapolated particle phi at EM3
  double DetPhiEM3_gen = kinem::phi(det_x, det_y);
  double DetEtaEM3_gen = -log(tan(det_theta/2.));

  deteta = DetEtaEM3_gen;
  detphi = DetPhiEM3_gen;
}

inline int wz_utils::TriggerCategory(int runno) {
  int triggerCategory = -1;
  if(runno>=160582 && runno<=174802) triggerCategory = 0;
  if(runno>=174896 && runno<=178721) triggerCategory = 1;
  if(runno>=178722 && runno<=190370) triggerCategory = 2;
  if(runno>=191266 && runno<=194566) triggerCategory = 3;
  if(runno>=194567 && runno<=196584) triggerCategory = 4;
  if(runno>=201485 && runno<=208144) triggerCategory = 5;
  if(runno>=208168 && runno<=211213) triggerCategory = 6;
  if(runno>=211214 && runno<=212951) triggerCategory = 7;
  if(runno>=212953 && runno<=214299) triggerCategory = 8;
  if(runno>=214630 && runno<=215670) triggerCategory = 9;
  return triggerCategory;
}

inline int wz_utils::EncodeCellIndex(int ieta, int iphi, int ilyr) {
  int ieta_new = 0;
  if(ieta<0) ieta_new = abs(ieta)+40;
  else ieta_new = ieta;

  return (ieta_new*10000 + iphi*100 + ilyr);
}

inline void wz_utils::RevertexCell(double E, double direction_vect[3],
				   double &new_ETx, double &new_ETy, double &new_ET) {
  // get cell position wrt new vertex
  double length = sqrt(direction_vect[0]*direction_vect[0] + 
		       direction_vect[1]*direction_vect[1] + 
		       direction_vect[2]*direction_vect[2]  );
  
  new_ETx = E * direction_vect[0]/length; // E*Sin(theta)*Cos(phi)
  new_ETy = E * direction_vect[1]/length; // E*Sin(theta)*Sin(phi)
  new_ET  = E * sqrt(direction_vect[0]*direction_vect[0] +
		     direction_vect[1]*direction_vect[1])/length; // E*Sin(theta)
}
inline void wz_utils::RevertexCell(float E, float cellpos[3], float new_vtx[3],
				   double &new_ETx, double &new_ETy, double &new_ET) {
  double direction_vect[3] = { (double)(cellpos[0] - new_vtx[0]),
                               (double)(cellpos[1] - new_vtx[1]),
                               (double)(cellpos[2] - new_vtx[2])};
  wz_utils::RevertexCell((double)E, direction_vect, new_ETx, new_ETy, new_ET);
}

/////////////////////////////////////////////////////////////
//
// recompute ET per PHI tower and recoil vector from 
// all calorimter cells except the ones belonging to:
// - reco EM objects
// - ICD layer
// - CH layer
// 
inline void wz_utils::calc_Et_per_tower
(// --------- INPUTS: ----------
 cafe::Event& event,            // event info
 std::vector<CAFEMObj*> emobjs, // vector with RECO em objects to be excluded from the recoil 
 double phi_direction,          // an arbitrary PHI on the azimuthal plane (eg. true direction of the recoil)
 float  vtx[3],                 // a vertex to recompute new recoil transverse momenta from cal.cells
 std::map<int, double>          // needed for computing a rescaled recoil 
    &RelResponse_scale,         // for a given delta_ieta:=(true_iphi-cell_iphi) the ET of a cell is scaled 
                                // by a factor of RelResponse_scale[delta_iphi]                           
                                // where delta_iphi=-31,...,0,...,32 (63 possibilities) is a PHI-distance
                                // between the true (ie. GENERATOR level) recoil direction and the RECO one
                                // expressed in calorimter readout towers
 // --------- OUTPUTS: ---------
 TVector2 &raw_calcells_Recoil,        // vectorial sum over ALL cal cells (excl.ICD,CH,cells of EM clusters)
 TVector2 &raw_calcells_Recoil_scaled, // vectorial sum over ALL RESCALED cal cells (excl.ICD,CH,cells of EM clusters)
 TVector2 &raw_calcells_Recoil_xcheck, // vectorial sum over ALL cal cells + RECO PT(ee) transverse momentum (excl.ICD,CH)
 std::map<int, double> &Et_flow,       // distribution of <ET> per PHI-tower wrt a given PHI direction in an event                  
 std::map<int, double> &Et_flow_scaled,// same but for cells rescaled according to RelResponse_scale map
 int _debugLevel ) {     
  
  if (_debugLevel>10) std::cout << "calc_Et_per_tower: Started" << std::endl;

  double raw_calcells_Recoil_X=0.0;
  double raw_calcells_Recoil_Y=0.0;
  double raw_calcells_Recoil_scaled_X=0.0;
  double raw_calcells_Recoil_scaled_Y=0.0;
  double raw_calcells_Recoil_xcheck_X=0.0;
  double raw_calcells_Recoil_xcheck_Y=0.0;
  
  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");
  if( cells ) {
    if (_debugLevel>11) std::cout << "calc_Et_per_tower: CaloCells -- PASSED" << std::endl;
    
    // get calorimeter geometry manager
    if(CaloGeometryManager::get_instance()) {    
      if (_debugLevel>11) std::cout << "calc_Et_per_tower: CaloGeometryManager -- PASSED" << std::endl;
      
      const std::map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
      
      // prepare map of EM calorimeter cells indices
      std::map<int, int> em_index;
      
      // get IPHI of the RECO recoil
      double phi=phi_direction;
      while(phi>=TMath::TwoPi()) phi-=TMath::TwoPi();
      while(phi<0.0)             phi+=TMath::TwoPi();
      int iphi_direction=(Int_t)(phi/TMath::TwoPi()*64); // iphi=0...63
      
      // loop over all EM calorimeter cells
      for(Int_t iem=0; iem<emobjs.size(); iem++) {

	// subtract raw cells PT(e) vector from raw_calcells_Recoil_xcheck vector 
	raw_calcells_Recoil_xcheck_X -= emobjs[iem]->getRawElecVectorFromCells(vtx).Px();
	raw_calcells_Recoil_xcheck_Y -= emobjs[iem]->getRawElecVectorFromCells(vtx).Py();

	for(UInt_t icell=0; icell<emobjs[iem]->ncells(); icell++) {
	  const TMBCaloCell *cell = emobjs[iem]->GetCaloCell(icell);
	  const int ieta = cell->ieta();
	  const int iphi = cell->iphi();
	  const int ilyr = cell->layer();
	  const int cell_index = wz_utils::EncodeCellIndex(ieta, iphi, ilyr);
	  em_index[cell_index]=cell_index;
	} // end of for(UInt_t icell=.... loop
      } // end of for(Int_t iem=.... loop
      
      // loop over all calorimeter cells but EM ones
      for(UInt_t icell=0; icell<cells->NumCells(); ++icell) {
	const TMBCaloCell *cell = cells->GetCell(icell);
	float E = cell->E();
	bool normalCell = cell->isNormalCell();
	
	// only look at positive cells and normal cells
	if(E>=0. && normalCell) {
	  
	  if (_debugLevel>12) std::cout << "calc_Et_per_tower:   icell="
				   <<icell<<": E>0 && normalCell -- PASSED" << std::endl;
	  
	  int ieta = cell->ieta();
	  int iphi = cell->iphi();
	  int ilyr = cell->layer();
	  
	  int cell_index = wz_utils::EncodeCellIndex(ieta, iphi, ilyr);
	  
	  if (_debugLevel>12) std::cout << "calc_Et_per_tower:   icell="
				   <<icell<<": EMobj veto -- PASSED" << std::endl;
	  
	  if(ilyr==9) {
	    if (_debugLevel>12) 
	      std::cout << "calc_Et_per_tower:   Rejected ICD cell!!! (icell="
		   <<icell << ", ieta=" 
		   << ieta << ", iphi=" 
		   << iphi << ", ilayer=" 
		   << ilyr << ")" << std::endl;
	    continue;
	  }
	  if(ilyr>14) {
	    if (_debugLevel>12) 
	      std::cout << "calc_Et_per_tower:   Rejected CH cell!!! (icell="
		   << icell << ", ieta=" 
		   << ieta << ", iphi=" 
		   << iphi << ", ilayer=" 
		   << ilyr << ")" << std::endl;
	    continue;
	  }
	  
	  //////////////////////////////////////////////////////////////////////////////////////////
	  //
	  //
	  // calorimeter cell position
	  std::map<int, CELLXYZ_STRUCT>::const_iterator iter = calogeometry_map.find(cell_index);
	  const CELLXYZ_STRUCT cellgeo = (*iter).second;

	  // get cell position

#define _USE_WZ_UTILS_REVERTEXCELL_
#ifdef _USE_WZ_UTILS_REVERTEXCELL_ //______wz_utils::RevertexCell METHOD_________
	  float cell_pos[3]={ cellgeo.x, cellgeo.y, cellgeo.z };
          double ETx, ETy, ET;
	  wz_utils::RevertexCell( E, cell_pos, vtx, ETx, ETy, ET);
#else

#define RVTX
#ifdef RVTX  // __ REVERTEX COMPATIBLE METHOD____________________________________	  
	  float cell_pos[3]={0., 0., 0.};
	  cell_pos[0] = cellgeo.x;
          cell_pos[1] = cellgeo.y;
          cell_pos[2] = cellgeo.z;        
	  
	  float theta_cell = kinem::theta(vtx, cell_pos);
	  float phi_cell = kinem::phi(cell_pos[0]-vtx[0], cell_pos[1]-vtx[1]);
	  
          double ET  = cell->E() * sin(theta_cell);
	  double ETx = ET * cos(phi_cell);
	  double ETy = ET * sin(phi_cell);       
	  
#else // ________ DEFAULT METHOD________________________________________________
	  double cellx = (cellgeo.x - vtx[0]);
	  double celly = (cellgeo.y - vtx[1]);
	  double cellz = (cellgeo.z - vtx[3]);
	  
	  double length = sqrt(cellx*cellx + celly*celly + cellz*cellz);
	  double ET  = E*sqrt(cellx*cellx+celly*celly)/length;
	  double ETx = E*cellx/length;
	  double ETy = E*celly/length;
#endif // ______________________________________________________________________
#endif
	  raw_calcells_Recoil_xcheck_X    += ETx;              
	  raw_calcells_Recoil_xcheck_Y    += ETy;
	  //
	  //
	  //
	  /////////////////////////////////////////////////////////////////////////////////////////

	  // finally reject cells belonging to EM objects, CH layer, ICD layer
	  if(em_index.find(cell_index)!=em_index.end()) {
	    if (_debugLevel>12) 
	      std::cout << "calc_Et_per_tower:   Rejected EM cell!!! (icell="
		   << icell << ", ieta=" 
		   << ieta << ", iphi="
		   << iphi << ", ilayer="
		   << ilyr << ")" << std::endl;
	    continue;
	  }
	  
	  if (_debugLevel>12) std::cout << "calc_Et_per_tower:   icell="
				   << icell << ": ICD & CH veto -- PASSED" << std::endl;
	  
	  int delta_iphi=iphi_direction - iphi;       // -31,...,0,...,32 range  (-32 and 32 are eqivalent)
	  if(delta_iphi>32)  delta_iphi=delta_iphi-64;
	  if(delta_iphi<-31) delta_iphi=64+delta_iphi;
	  
	  raw_calcells_Recoil_X         += ETx;              
	  raw_calcells_Recoil_Y         += ETy;
	  Et_flow[delta_iphi]           += ET;
	  
	  raw_calcells_Recoil_scaled_X  += ETx * RelResponse_scale[delta_iphi];
	  raw_calcells_Recoil_scaled_Y  += ETy * RelResponse_scale[delta_iphi];
	  Et_flow_scaled[delta_iphi]    += ET * RelResponse_scale[delta_iphi];
	  
	} // good cell
      } // loop over all cells
      
      // recompute recoil transverse momentum
      raw_calcells_Recoil.Set(raw_calcells_Recoil_X, raw_calcells_Recoil_Y);
      raw_calcells_Recoil_scaled.Set(raw_calcells_Recoil_scaled_X, raw_calcells_Recoil_scaled_Y);
      raw_calcells_Recoil_xcheck.Set(raw_calcells_Recoil_xcheck_X, raw_calcells_Recoil_xcheck_Y);
            
      if (_debugLevel>10) {
	for(int delta_iphi=-31; delta_iphi<=32; delta_iphi++) {
	  std::cout << "calc_Et_per_tower:  Detla_IPHI="<<delta_iphi
	       <<"  ET="<<Et_flow[delta_iphi]<<"  ET(scaled)="<<Et_flow_scaled[delta_iphi]<<std::endl;
	}
      }
      
    } // get geometry map
  } // end of if(cells)...
  
  if (_debugLevel>10) std::cout << "calc_Et_per_tower: Ended" << std::endl;
}
//
/////////////////////////////////////////////////////////////

inline int wz_utils::UParaBins(double UPara) {
  int UPara_type = -1;
  if(UPara<=-22) UPara_type=0;
  else if(UPara<=-15) UPara_type=1;
  else if(UPara<=-10) UPara_type=2;
  else if(UPara<=-7) UPara_type=3;
  else if(UPara<=-5) UPara_type=4;
  else if(UPara<=-3) UPara_type=5;
  else if(UPara<=-2) UPara_type=6;
  else if(UPara<=-1) UPara_type=7;
  else if(UPara<=0) UPara_type=8;
  else if(UPara<=1) UPara_type=9;
  else if(UPara<=2) UPara_type=10;
  else if(UPara<=3) UPara_type=11;
  else if(UPara<=5) UPara_type=12;
  else if(UPara<=8) UPara_type=13;
  else if(UPara<=12) UPara_type=14;
  else if(UPara<=17) UPara_type=15;
  else if(UPara<=23) UPara_type=16;
  else UPara_type=17;

  return UPara_type;
}

inline void wz_utils::DecodeCellIndex(int cell_index, int& ieta, int& iphi, int& ilyr) {
  ilyr = cell_index%100;
  iphi = ((cell_index-ilyr)/100)%100;
  ieta = (int) ((cell_index-ilyr-iphi*100)/10000);

  if(ieta>=40) {
    ieta -= 40;
    ieta = -ieta;
  }
}

inline void wz_utils::FindRegion(std::vector<double>& cut_vect, double value, int& region) {
  region = -1;
  int size_all = cut_vect.size();
  if(value<cut_vect[0]) region = 0;
  else if(value>cut_vect[size_all-1]) region=size_all;
  else {
    for(int i=0; i< cut_vect.size()-1; i++) {
      if(value>cut_vect[i] && value<=cut_vect[i+1]) region=i+1;
    }
  }
}

// calculate (b1, phi1) for a track with (b0, phi0)
// beam spot (pv0, pv1, pv2)
inline void wz_utils::BeamSpotCorrection(float b0, float phi0, float& b1,
					 float& phi1, float kappa, float distance_vertices[3]) {
  //
  // calculate distance between two vertices (rb, phib)
  //
  double rb = sqrt(distance_vertices[0]*distance_vertices[0] + distance_vertices[1]*distance_vertices[1] + 
		  distance_vertices[2]*distance_vertices[2]);

  double phib = kinem::phi(distance_vertices[1], distance_vertices[0]);
  
   double A = 1./(2*kappa) - b0;
  
  b1 = 1./(2*kappa) - sqrt(A*A + rb*rb + 2*A*rb*sin(phib-phi0));
  phi1 = phi0 - atan2(rb*cos(phib-phi0), rb*sin(phib-phi0)+A);
}

// for bremsstrahlung simulation
inline double wz_utils::BremProba(double y, double k) {
  return ( 0.01*( (1.-y)*(k+4./3) + y*y)/y );
}

//calculate the probability of the electron to emit a photon after it travels through radiation
//length radiation_length
inline void wz_utils::brem_simulation(double radiation_length, double y_min, int bin_y, double k,
				      double proba[50], double& proba_total, double& elec_energy_fraction, TRandom3 *random) {
  
  elec_energy_fraction = 1.;

  double step_y = (1. - y_min)/bin_y;    //calculate dy
  double proba_add[50] = {0.};

  proba_total = 0.;

  //
  //calculate the probability for the electron to emit a photon with fraction of energy given by y
  //
  for(int istep = 0; istep < bin_y; istep ++) {
    proba[istep] = BremProba(y_min + istep * step_y, k);
    //    std::cout << "The probability to emit a photon that carries " << y_min + istep * step_y
    //	      << " percent of the electron energy is " << proba[istep]*radiation_length << std::endl;
    proba_total += proba[istep]*radiation_length;
    proba_add[istep] = proba_total;
  }
  
  //  std::cout << "Total Probability = " << proba_total << std::endl;
  
  double rand = random -> Rndm();
  
  //
  //determine whether the electron should emit a photon
  //if it does, what fraction of energy will the photon carry
  //
  if(rand < proba_total) {
    //    std::cout << "This electron will emit a photon" << std::endl;
    
    //
    //what fraction of energy will be assigned to the photon
    //
    if(rand<proba_add[0]){
      //      std::cout << "The photon energy will be " << y_min << std::endl;
      elec_energy_fraction = 1. - y_min;
    }
    
    for(int istep = 0; istep < bin_y; istep ++) {
      if((rand>proba_add[istep]) && (rand<proba_add[istep+1])){
	//        std::cout << "The photon energy will be " << y_min+istep*step_y << std::endl;
        elec_energy_fraction = 1. - (y_min+istep*step_y);
      }
    } //determine the energy of the photon
    
  }//emit a photon
}

// determine pT_ee * eta direction region 
inline int wz_utils::pTee_Eta_Bin(double pee_eta) {
  int bin = -1;
  if(pee_eta >= 30) bin = -1;
  else if(pee_eta >= 20) bin = 9;
  else if(pee_eta >= 15) bin = 8;
  else if(pee_eta >= 10) bin = 7;
  else if(pee_eta >=  7) bin = 6;
  else if(pee_eta >=  5) bin = 5;
  else if(pee_eta >=  4) bin = 4;
  else if(pee_eta >=  3) bin = 3;
  else if(pee_eta >=  2) bin = 2;
  else if(pee_eta >=  1) bin = 1;
  else bin = 0;
  return bin;
}

// from true recoil pT and phi to smeared recoil pT and phi
inline void wz_utils::FlipARecoil2(double truepT, double truephi, double& smpT, double& smphi, double RelScale, double RelOffset) {

  // We start with the respose
  //
  static Float_t bifurcated[210] = {
    0.65306,   0.238184, 0.103967,  1.64265, 0.153533,  0.370652, 0.0681173,
    1.52608,   0.648833, 0.0276558,  0.886347, 0.0213089,  0.157053, 0.0172546,
    2.53103,   0.822688, 0.00904848,  0.611407, 0.00899293,  0.0835345, 0.00662865,
    3.48436,   0.96247, 9.57509e-06,  0.530735, 0.00529039,  2.52689e-05, 8.04174e-06,
    4.43473,   0.962219, 0.000122507,  0.485521, 0.00471107,  0.000190436, 8.31256e-05,
    5.48155,   0.710773, 0.0119056,  0.379311, 0.00870969,  0.13366, 0.00830995,
    6.48067,   0.661748, 0.0142095,  0.344549, 0.0100636,  0.151496, 0.00985188,
    7.48979,   0.600927, 0.0118487,  0.303321, 0.00935552,  0.158463, 0.00761413,
    8.47235,   0.601168, 0.0112567,  0.288181, 0.00905858,  0.141588, 0.00729572,
    9.48343,   0.584834, 0.0118833,  0.276973, 0.00798643,  0.132888, 0.00642,
    10.473,   0.574474, 0.0131216,  0.262011, 0.00925993,  0.127442, 0.00785258,
    11.4889,   0.565041, 0.0119201,  0.250388, 0.00881499,  0.124906, 0.0072687,
    12.4911,   0.52116, 0.0125273,  0.234863, 0.010091,  0.140692, 0.00741158,
    13.4828,   0.533243, 0.0116285,  0.229607, 0.00978484,  0.117448, 0.00661069,
    14.4885,   0.492567, 0.0132564,  0.191185, 0.0102086,  0.131144, 0.00828218,
    16.4345,   0.481637, 0.00892892,  0.19368, 0.00647588,  0.129348, 0.00518637,
    19.4341,   0.461193, 0.0087317,  0.18232, 0.00701597,  0.119644, 0.00544167,
    22.4464,   0.443283, 0.00945622,  0.17269, 0.00714131,  0.124173, 0.00580423,
    25.4548,   0.41973, 0.010188,  0.151478, 0.00767245,  0.12262, 0.00724669,
    28.4588,   0.425839, 0.0113644,  0.153078, 0.00815066,  0.107395, 0.00785428,
    32.4351,   0.393237, 0.00995797,  0.136665, 0.00685529,  0.114528, 0.00644977,
    37.431,   0.400189, 0.0118877,  0.147077, 0.00905135,  0.0992337, 0.00845132,
    44.3307,   0.353523, 0.00982457,  0.127875, 0.00656976,  0.112578, 0.00648988,
    54.2683,   0.323596, 0.0116171,  0.102373, 0.00832569,  0.107325, 0.00794623,
    64.3459,   0.319674, 0.0163173,  0.115791, 0.0115136,  0.0965003, 0.0119345,
    74.6479,   0.281643, 0.0220739,  0.0905185, 0.0143972,  0.114015, 0.0162966,
    84.769,   0.300571, 0.0193749,  0.10703, 0.0160154,  0.0844774, 0.0134411,
    999};

  // find bin
  Int_t theBin=0;
  Float_t dist=fabs(truepT-bifurcated[0]);
  Int_t i=1;
  while (bifurcated[i*7]<900) {
    if (fabs(truepT-bifurcated[i*7])<dist) {
      theBin=i;
      dist=fabs(truepT-bifurcated[i*7]);
    }
    i++;
  }
  // flip response
  Float_t M=bifurcated[theBin*7+1];
  Float_t S1=bifurcated[theBin*7+3];
  Float_t S2=bifurcated[theBin*7+5];
  Float_t area1=S1;
  Float_t area2=S2;
  Float_t rn=gRandom->Rndm()*(area1+area2);
  Float_t response;
  if (rn<area1) {
    response=M-fabs(gRandom->Gaus(0,S1));
  } else {
    response=M+fabs(gRandom->Gaus(0,S2));
  }
  if (response>1) response=1;

  // Now the phi smearing
  //
  static Float_t phiMP0=3.15969;
  static Float_t phiMP1=0.0108019;
  static Float_t phiSLP0=1.21916;
  static Float_t phiSLP1=-0.168109;
  Float_t phiM=phiMP0/truepT+phiMP1;
  Float_t phiSL=phiSLP0*exp(phiSLP1*truepT);
  Float_t phiResn=phiM+(response-0.5)*phiSL;

  // We are ready to smear
  Float_t dpT=response*truepT;
  smpT=(RelScale+RelOffset/truepT)*(truepT-dpT);
  smphi=truephi+gRandom->Gaus(0,phiResn);
  if (smphi>2*TMath::Pi()) {
    smphi-=2*TMath::Pi();
  } else if (smphi<0) {
    smphi+=2*TMath::Pi();
  }

  return;

}

#endif // INC_WZUTILS
