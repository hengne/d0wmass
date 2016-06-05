#ifndef pcaltools_hpp
#define pcaltools_hpp

#include <math.h>  //fmod (others from TMath)
#include "TVector3.h"
#include "TMath.h"

#include "PTools.hpp"  //etaToTheta, thetaToEta

//These values were taken from:
// cal_alignment/rcp/CalOverallXforms.rcp
// em_util/src/Fiducial_Cuts.cpp
// em_util/src/CalAlign.cpp

// Note: x-y alignment is not implemented yet

#define EC_DIV        140.0 //z position of EC/CC division

#define CC_XSHIFT      0.0 //-0.33  //-0.33 //CC shift wrt to tracker
#define CC_YSHIFT      0.0 //-0.46  //-0.46 //CC shift wrt to tracker

// according to Jan and d0gstar/d0db/detc/calo.tz
// CC_ZSHIFT should be set to -3 cm instead of -3.2 cm
#define CC_ZSHIFT      -3.2 //-3.2  //CC shift wrt to tracker

#define EC_3Z_SOUTH   179.0 //real position of third floor in EC
#define EC_3Z_NORTH  -182.8 //real position of third floor in EC
#define EC_XSHIFT_NORTH 0.38  //0.38 // EC shift wrt to tracker
#define EC_YSHIFT_NORTH 0.00
#define EC_XSHIFT_SOUTH  0.0
#define EC_YSHIFT_SOUTH  0.0

#define CC_3R          91.9 //local distance to 3rd floor in the CC
#define EC_3Z         178.9 //local distance to 3rd floor in the EC

#define EC_R_MAX       85.0 //local edge of EC
#define CC_Z_MAX      115.0 //local edge of CC

#define EPSILON       1.E-10

#define MAG_R         0.60  //Solenoid Radius
#define MAG_Z         125.0  //Solenoid Length
#define MAGField      2.  //B Field

class PCalTools {

protected:
  PCalTools();  
  ~PCalTools();

private:

public:

  static TVector3 toLocal(const TVector3 &global){

    TVector3 local = global;

    if(TMath::Abs(global.Z()) < EC_DIV){ //CC
      local.SetX(local.X()-CC_XSHIFT);
      local.SetY(local.Y()-CC_YSHIFT);
      local.SetZ(local.Z()-CC_ZSHIFT);
    }else{
      if (global.Z() < 0) local.SetX(local.X()-EC_XSHIFT_NORTH);
      local.SetZ( (global.Z()>0) ? EC_3Z : -EC_3Z );
    }

    return local;
  }

  static TVector3 toGlobal(const TVector3 &local){

    TVector3 global = local;

    if(TMath::Abs(local.Z()) < EC_DIV){ //CC
      global.SetX(global.X()+CC_XSHIFT);
      global.SetY(global.Y()+CC_YSHIFT);
      global.SetZ(global.Z()+CC_ZSHIFT);
    }else{
      if (local.Z() < 0) global.SetX(local.X()+EC_XSHIFT_NORTH);
      global.SetZ( (local.Z()>0) ? EC_3Z_SOUTH : EC_3Z_NORTH );
    }

    return global;
  }


  static Bool_t is_in_phi_fiducial(const TVector3 &v) {
    // converted from emid::is_in_phi_fiducial
    
    const double PHI_CRACK_WIDTH=0.02; 
    
    double phi = v.Phi()>=0 ? v.Phi() : (v.Phi()+TMath::TwoPi()); 
    
    // CC phi cracks
    Bool_t outside_phi_crack=true;
    if (TMath::Abs(v.Z()) < 150.) {
      double phimod=fmod(phi+0.1,TMath::Pi()/16.);
      outside_phi_crack=(phimod<0.1-PHI_CRACK_WIDTH) || 
	(phimod>0.1+PHI_CRACK_WIDTH);
    }
    return outside_phi_crack;
  }
  

  static Bool_t is_in_eta_fiducial(const TVector3 &pos) {
    // converted from emid::is_in_eta_fiducial

    // NOTE: this routine assumes pos is in local coordinates!
    //convert pos to local coordinate system
    //TVector3 v = toLocal(pos);

    // cryostat edges
    bool is_at_edge;
    if (TMath::Abs(pos.Z())>150.) {
      is_at_edge=pos.Perp()>EC_R_MAX;
    } else {
      is_at_edge=fabs(pos.Z())>CC_Z_MAX;
    }
    return (!is_at_edge);
    
  }

  static TVector3 floorXYZ(double zvtx, double physeta, double physphi) {
    // Function to calculate detector position when particle is extrapolated
    // to 3rd layer of em calorimeter.

    // Note that we assume an x,y vertex position of zero.
    // Also, the x,y cal shifts are not implemented...yet.

    TVector3 v;
    
    double phi = physphi;  
    double eta = physeta;
    double theta = PTools::etaToTheta(eta);
    double ztmp = zvtx + CC_3R/TMath::Tan(theta);
    
    if( TMath::Abs(ztmp) >= EC_DIV ){ // in EC
      (eta>=0) ? v.SetZ(EC_3Z_SOUTH) : v.SetZ(EC_3Z_NORTH);
      v.SetX( (v.Z()-zvtx) * TMath::Tan(theta) * TMath::Cos(phi));
      v.SetY( (v.Z()-zvtx) * TMath::Tan(theta) * TMath::Sin(phi));
      
    }
    else{ // in CC
      v.SetZ(ztmp);
      v.SetX( CC_3R * TMath::Cos(phi));
      v.SetY( CC_3R * TMath::Sin(phi));
      
    }
    
    return v;
  }
  
  static TVector3 floorXYZ_Local(double zvtx, double physeta, 
				 double physphi) {
    return toLocal(floorXYZ(zvtx,physeta,physphi));
  }

  static double eta_em_extrap(double z, double physeta) {
    return floorXYZ(z,physeta,0.0).Eta();
  }

  static double eta_extrap_Local(double z, double physeta) {
    return floorXYZ_Local(z,physeta,0.0).Eta();
  }

  static double detectorToPhysicsEta(double z, double deteta) {
    //
    // deteta must be in global coordinates
    //
    const double THDIV = TMath::ATan2(CC_3R,EC_DIV);
    const double ETADIV= PTools::thetaToEta(THDIV);

    double theta = PTools::etaToTheta(deteta);
    double thphys;

    if( TMath::Abs(deteta) < ETADIV ){ //CC region
      double zdif = (CC_3R / TMath::Tan(theta)) - z;
      thphys = TMath::ATan2(CC_3R,zdif);
    }else{ //EC
      double L = (deteta>0) ? EC_3Z_SOUTH : EC_3Z_NORTH;
      double R = L * TMath::Tan(theta);
      thphys = TMath::ATan2(R,L-z);
    }
  
    return PTools::thetaToEta(thphys);
  }

  static double eta(double x, double y, double z) {
    return 0.5*log((sqrt(x*x + y*y + z*z) + z + EPSILON) /
		   (sqrt(x*x + y*y + z*z) - z + EPSILON));
  }

  static double Phi_Magnetic_Field(double ZVtx, double PhysEta, double PhysPhi, double ElecPt, bool ispositron) {
    // Angular kick due to the magnetic field, need to
    // distinguish between CC and EC, since the
    // track length in the magnetic field is different.
    // The magnetic field is assumed to be uniform (2 Tesla)
    // in a cylinder of 60cm radius, spanning from -125 cm to 125 cm.

    int charge = -1;
    if(ispositron) charge = 1;
    
    int polarity = -1;
    
    //double phiCorr = (22./CC_3R*polarity*charge)/ElecPt;
    double phiCorr = (21.1/CC_3R*polarity*charge)/ElecPt; // change to 21. by Hengne
    double phiGbl = PhysPhi + phiCorr;
    double trk_theta = kinem::theta(PhysEta);
    
    //
    // use true primary vertex
    //
    double mc_vtx_z = ZVtx;
    double zem3 = mc_vtx_z + CC_3R/tan(trk_theta);

    double det_x, det_y, det_theta, det_r;
    if(zem3 > 125.){  // pos EC
      double trk_r = fabs((EC_3Z_SOUTH-mc_vtx_z)*tan(trk_theta));
      det_x = trk_r*cos(phiGbl) - EC_XSHIFT_SOUTH;
      det_y = trk_r*sin(phiGbl) - EC_YSHIFT_SOUTH;
      det_r = sqrt(det_x*det_x +det_y*det_y);
      det_theta = atan2(det_r, EC_3Z);
    } else if(zem3 > -125.) { // CC
      det_x = CC_3R*cos(phiGbl) - CC_XSHIFT;
      det_y = CC_3R*sin(phiGbl) - CC_YSHIFT;
      det_r = sqrt(det_x*det_x +det_y*det_y);
      det_theta = atan2(det_r, zem3-CC_ZSHIFT);
    } else { // neg EC
      double trk_r = fabs((EC_3Z_NORTH-mc_vtx_z)*tan(trk_theta));
      det_x = trk_r*cos(phiGbl) - EC_XSHIFT_NORTH;
      det_y = trk_r*sin(phiGbl) - EC_YSHIFT_NORTH;
      det_r = sqrt(det_x*det_x +det_y*det_y);
      det_theta = atan2(det_r, -EC_3Z);
    }
    
    // extrapolated particle phi at EM3
    double DetPhiEM3_gen = kinem::phi(det_x, det_y);
    return DetPhiEM3_gen;

    /*    
    double Phi_Magnetic = 0.;
    double IntBdL = 0.;

    double theta = 2.0 * TMath::ATan(TMath::Exp(-PhysEta));

    if ( PhysEta > 0 ) {
      IntBdL = MAGField*TMath::Min(MAG_R, (MAG_Z - ZVtx)*TMath::Tan(theta)/100.)/2.;
    } else {
      IntBdL = MAGField*TMath::Min(MAG_R,-(MAG_Z + ZVtx)*TMath::Tan(theta)/100.)/2.;
    }
    
    double SinPhiKick = 0.2998 * IntBdL/ElecPt;
    
    Phi_Magnetic = PhysPhi;
    
    if ( fabs(SinPhiKick) < 1.0 ) {
      double PhiKick = 2.0*TMath::ASin(SinPhiKick);
      if ( !ispositron ) PhiKick = -PhiKick;
      Phi_Magnetic = PhysPhi + PhiKick;
    }
    if (Phi_Magnetic < 0) Phi_Magnetic+= 2*M_PI;
    if (Phi_Magnetic >= 2*M_PI) Phi_Magnetic-= 2*M_PI;
    return Phi_Magnetic;
    */


  } //phi in magnetic field

  static Float_t Deltar(const TVector3 &pos1, const TVector3 &pos2 ) {
    return sqrt(pow(pos1.X()-pos2.X(),2)+pow(pos1.Y()-pos2.Y(),2)+pow(pos1.Z()-pos2.Z(),2));
  }
  
};

#endif
