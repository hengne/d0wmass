#include "wmass_util/CAFTrack.hpp"
#include "cafe/Collection.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "wmass_util/WZ_Utils.hpp"

using namespace std;
using namespace cafe;

#define CC_XSHIFT  -0.33
#define CC_YSHIFT  -0.46
#define CC_ZSHIFT  -3.2

#define EC_3Z_NORTH -182.8
#define EC_XSHIFT_NORTH 0.38
#define EC_YSHIFT_NORTH 0.00

#define EC_3Z_SOUTH      179.
#define EC_XSHIFT_SOUTH  0.0
#define EC_YSHIFT_SOUTH  0.0

#define CC_3R   91.9
#define EC_3Z   178.9

#define EC_R_MAX  85.0
#define CC_Z_MAX  115.0

const double B_field = 2.;

// constructor
CAFTrack::CAFTrack(TMBTrack* p) {
  _tmbtrack_ptr = p;

  _trk_vars.add("fX");
  _trk_vars.add("fY");
  _trk_vars.add("fZ");
}
  
// destructor
CAFTrack::~CAFTrack() {}

// update track eta, phi for new primary vertex
void CAFTrack::UpdateForNewVertex(float vertex_old[3], float vertex_new[3]) {
  // distance between two vertices
  float distance_vertices[3] = {vertex_new[0]-vertex_old[0], vertex_new[1]-vertex_old[1], 
				vertex_new[2]-vertex_old[2]};

  float b0 = sqrt(xdca()*xdca() + ydca()*ydca());;
  float phi0 = this->Phi();
  float kappa = 0.0015*B_field/(this->Pt());

  float b_new=0., phi_new=0.;
  wz_utils::BeamSpotCorrection(b0, phi0, b_new, phi_new, kappa, distance_vertices);

  // set new physics eta and phi for this track
  SetPtEtaPhiE(Pt(), Eta(), phi_new, E());
}

// isolated track
bool CAFTrack::IsIsolatedTrack(Event& event, float coneSize, float sumPtCut) {
   bool isolated = false;
   float eta = this->Eta();
   float phi = this->Phi();
   float Pt = this->Pt();
   
   float sumPt = 0.;   //sum pT of tracks inside the cone
   cafe::Collection<TMBTrack> trks = event.getTracks(_trk_vars);
   
   for(Collection<TMBTrack>::iterator it=trks.begin(); it!=trks.end(); ++it) {
     float delta_R = kinem::delta_R((*it).Eta(), (*it).Phi(), eta, phi);
     if(delta_R < coneSize) sumPt += (*it).Pt();
   }
   
   if( (sumPt-Pt) < sumPtCut ) isolated = true;
   return isolated;
}

// extrapolate track to EM3 and calculate detector eta
float CAFTrack::TrackDetEta(int polarity, bool isGeantMC) const {
  // now will extrapolate the track to EM3 layer
  // 22.55 cm for data and 21.65 cm for GEANT MC from em_util
  // but we found that if we use these two numbers, the phi difference between
  // electrons and positrons do not agreem, needs to use 21 cm
  // maybe problematic to use track pT here, should use EM cluster pT, but no
  // EM cluster pT information available here
  double corr_EM3 = 21.;
  if(isGeantMC) corr_EM3 = 21.;
  float phiCorr = corr_EM3/CC_3R*polarity*charge()/Pt();
  float phiGbl = Phi()+phiCorr;
  float z0 = z();
  float trk_theta = kinem::theta(Eta());
  float zem3 = z0+CC_3R/tan(trk_theta);  

  double det_x, det_y, det_r, det_theta;
  if(zem3 > 125.){  // pos EC
    float trk_r = fabs((EC_3Z_SOUTH-z0)*tan(trk_theta));
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
    float trk_r = fabs((EC_3Z_NORTH-z0)*tan(trk_theta));
    det_x = trk_r*cos(phiGbl) - EC_XSHIFT_NORTH;
    det_y = trk_r*sin(phiGbl) - EC_YSHIFT_NORTH;
    det_r = sqrt(det_x*det_x +det_y*det_y);
    det_theta = atan2(det_r, -EC_3Z);
  } 
  
  return -log(tan(det_theta/2.));
}

// extrapolate track to EM3 and calculate detector phi 
float CAFTrack::TrackDetPhi(int polarity, bool isGeantMC) const {
  // now will extrapolate the track to EM3 layer
  // 22.55 cm for data and 21.65 cm for GEANT MC from em_util
  // but we found that if we use these two numbers, the phi difference between
  // electrons and positrons do not agreem, needs to use 21 cm
  // maybe problematic to use track pT here, should use EM cluster pT, but no
  // EM cluster pT information available here
  double corr_EM3 = 21.;
  if(isGeantMC) corr_EM3 = 21.;
  float phiCorr = corr_EM3/CC_3R*polarity*charge()/Pt();
  float phiGbl = Phi()+phiCorr;
  float z0 = z();
  float trk_theta = kinem::theta(Eta());
  float zem3 = z0+CC_3R/tan(trk_theta);  

  float det_x, det_y;
  if(zem3 > 125.){  // pos EC
    float trk_r = fabs((EC_3Z_SOUTH-z0)*tan(trk_theta));
    det_x = trk_r*cos(phiGbl) - EC_XSHIFT_SOUTH;
    det_y = trk_r*sin(phiGbl) - EC_YSHIFT_SOUTH;
  } else if(zem3 > -125.) { // CC
    det_x = CC_3R*cos(phiGbl) - CC_XSHIFT;
    det_y = CC_3R*sin(phiGbl) - CC_YSHIFT;
  } else { // neg EC
    float trk_r = fabs((EC_3Z_NORTH-z0)*tan(trk_theta));
    det_x = trk_r*cos(phiGbl) - EC_XSHIFT_NORTH;
    det_y = trk_r*sin(phiGbl) - EC_YSHIFT_NORTH;
  } 
  
  return (kinem::phi(det_x, det_y));
}

// require track must be in calorimeter fiducial region, only used for preselection efficiency measurement
bool CAFTrack::IsCCECFid(float trk_deteta, float trk_detphi, float DetEtaCC, float DetEtaEC1, float DetEtaEC2) const {
   bool IsEtaFid = (fabs(trk_deteta)<DetEtaCC) || (fabs(trk_deteta)<DetEtaEC2 && fabs(trk_deteta)>DetEtaEC1);
   float trk_phi_mod = fmod(16.*trk_detphi/3.1415926, 1.0);
   bool IsPhiFid = true;
   if(fabs(trk_deteta)<DetEtaCC && (trk_phi_mod<0.1 || trk_phi_mod>0.9)) IsPhiFid = false;
   return (IsEtaFid && IsPhiFid); 
}

// sort tracks according to pT
bool ComparePt(const CAFTrack* track1, const CAFTrack* track2) {
  return (track1->Pt()>track2->Pt());
}

ClassImp(CAFTrack)
