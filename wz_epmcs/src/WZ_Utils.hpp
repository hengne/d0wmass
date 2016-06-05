#ifndef INC_WZUTILS
#define INC_WZSUTILS

#include <cmath>
#include <cstdlib>
#include "AnglesUtil.hpp"
#include "TRandom3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cassert>
#include "TSpline.h"
#include "TComplex.h"
#include "TAxis.h"
#include "TF2.h"
#include "TFile.h"
#include "TF2jan.h"
#include "PMCSWCand.hpp"
#include "TProfile.h"
#include "TH2D.h"
#include "TH3D.h"

#define maxim(A,B) ( (A)>(B) ? (A) : (B) )
#define minim(A,B) ( (A)<(B) ? (A) : (B) )

using namespace std;

namespace wz_utils {


  static const double dphibins[9] = {0.0, 0.05, 0.10, 0.15, 0.20, 0.30, 0.50, 1.0, 3.2};
  static const double ptbins[17] = {0,0.05, 0.1, 0.15, 0.2, 0.3, 0.4, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 8.0, 10.0, 15.0, 4000};
  
  static const double probs_eta_pt_dphi[3][16][9] = {{{0, 0.420391, 0.601955, 0.709497, 0.763966, 0.835196, 0.892458, 0.959497, 1}, //for EC
						     {0, 0.528753, 0.734877, 0.802838, 0.840179, 0.88947, 0.93652, 0.980583, 1},
						     {0, 0.64142, 0.807692, 0.863314, 0.895266, 0.928994, 0.963905, 0.991124, 1},
						     {0, 0.677856, 0.83216, 0.877098, 0.905252, 0.93882, 0.968056, 0.989172, 1},
						     {0, 0.742424, 0.860978, 0.903775, 0.927964, 0.953482, 0.977671, 0.995747, 1},
						     {0, 0.785327, 0.887884, 0.926117, 0.949884, 0.971325, 0.990958, 0.998967, 1},
						     {0, 0.832176, 0.912198, 0.941928, 0.958322, 0.978327, 0.993331, 0.999722, 1},
						     {0, 0.89494, 0.957925, 0.977762, 0.986733, 0.996525, 0.999368, 0.999937, 1},
						     {0, 0.951387, 0.987397, 0.996399, 0.999182, 0.999836, 0.999918, 1, 1},
						     {0, 0.97779, 0.99805, 0.999892, 0.999892, 0.999892, 1, 1, 1},
						     {0, 0.992682, 1, 1, 1, 1, 1, 1, 1},
						     {0, 0.998593, 1, 1, 1, 1, 1, 1, 1},
						     {0, 0.999877, 1, 1, 1, 1, 1, 1, 1},
						     {0, 1, 1, 1, 1, 1, 1, 1, 1},
						     {0, 1, 1, 1, 1, 1, 1, 1, 1},
						     {0, 1, 1, 1, 1, 1, 1, 1, 1}},

						     //for ICR
						     {{0, 0.642857, 0.785714, 0.821429, 0.857143, 0.964286, 0.964286, 1, 1},
						      {0, 0.535714, 0.723214, 0.75, 0.776786, 0.8125, 0.883929, 0.946429, 1},
						      {0, 0.552174, 0.695652, 0.76087, 0.795652, 0.821739, 0.873913, 0.926087, 1},
						      {0, 0.590909, 0.717532, 0.775974, 0.811688, 0.844156, 0.883117, 0.931818, 1},
						      {0, 0.650589, 0.79314, 0.832797, 0.855305, 0.884244, 0.912111, 0.953912, 1},
						      {0, 0.676768, 0.819024, 0.855219, 0.875421, 0.902357, 0.934343, 0.98064, 1},
						      {0, 0.727132, 0.848062, 0.874419, 0.895349, 0.918605, 0.960465, 0.989147, 1},
						      {0, 0.758696, 0.856071, 0.886719, 0.90922, 0.945687, 0.979309, 0.994698, 1},
						      {0, 0.797076, 0.881871, 0.921784, 0.950585, 0.978216, 0.989912, 0.996784, 1},
						      {0, 0.82611, 0.909267, 0.951022, 0.970049, 0.986434, 0.993658, 0.998238, 1},
						      {0, 0.856546, 0.942963, 0.972342, 0.982545, 0.990289, 0.995821, 0.998525, 1},
						      {0, 0.896958, 0.960087, 0.978385, 0.985933, 0.992681, 0.996112, 0.999199, 1},
						      {0, 0.935211, 0.977713, 0.986869, 0.991534, 0.995162, 0.998791, 0.999827, 1},
						      {0, 0.952141, 0.984887, 0.993703, 0.996641, 0.997901, 1, 1, 1},
						      {0, 0.969634, 0.992473, 0.996107, 0.998962, 0.999481, 1, 1, 1},
						      {0, 0.988294, 0.99807, 0.999357, 0.999485, 0.999871, 1, 1, 1}},

						     //for CC
                                                      {{0, 0.787234, 0.893617, 0.914894, 0.914894, 0.93617, 0.93617, 0.978723, 1},
						       {0, 0.79602, 0.910448, 0.950249, 0.960199, 0.9801, 0.9801, 0.9801, 1},
						       {0, 0.817978, 0.92809, 0.955056, 0.966292, 0.977528, 0.988764, 0.995506, 1},
                                                       {0, 0.828666, 0.917628, 0.947282, 0.962109, 0.976936, 0.98682, 0.991763, 1},
						       {0, 0.856284, 0.93991, 0.958438, 0.96695, 0.975463, 0.983475, 0.99349, 1},
						       {0, 0.85362, 0.939539, 0.955847, 0.963405, 0.975736, 0.985282, 0.997613, 1},
						       {0, 0.874665, 0.933981, 0.943365, 0.949397, 0.95744, 0.975871, 0.996984, 1},
						       {0, 0.887755, 0.929561, 0.941249, 0.953061, 0.973717, 0.993197, 0.999072, 1},
						       {0, 0.914683, 0.941176, 0.958685, 0.978114, 0.995085, 0.999309, 1, 1},
						       {0, 0.93175, 0.964658, 0.988122, 0.996592, 0.999513, 1, 1, 1},
						       {0, 0.957792, 0.988528, 0.998773, 0.999856, 0.999856, 1, 1, 1},
						       {0, 0.983003, 0.999424, 1, 1, 1, 1, 1, 1},
						       {0, 0.997787, 1, 1, 1, 1, 1, 1, 1},
						       {0, 0.999419, 1, 1, 1, 1, 1, 1, 1},
						       {0, 1, 1, 1, 1, 1, 1, 1, 1},
						       {0, 1, 1, 1, 1, 1, 1, 1, 1}}};


  //static const double dphibins[9] = {0.0, 0.05, 0.10, 0.15, 0.20, 0.30, 0.50, 1.0, 3.2};
  //static const double ptbins[17] = {0,0.05, 0.1, 0.15, 0.2, 0.3, 0.4, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 8.0, 10.0, 15.0, 4000};

  //for EC
  static const double respo_eta_pt_dphi[3][16][8] = {{{0.985393, 0.70679, 0.494404, 0.726195, 0.648179, 0.543741, 0.293657, 0.231219},
						      {0.715546, 0.537691, 0.551825, 0.510875, 0.390471, 0.282926, 0.265143, 0.172837},
						      {0.67909, 0.560233, 0.396818, 0.467024, 0.266595, 0.23797, 0.308024, 0.0597007},
						      {0.675553, 0.545085, 0.470578, 0.41097, 0.387645, 0.387216, 0.587245, 0.139162},
						      {0.690211, 0.527751, 0.410335, 0.468498, 0.34019, 0.25706, 0.200877, 0.092256},
						      {0.705414, 0.517089, 0.531108, 0.325533, 0.408081, 0.328806, 0.148192, 0.0105709},
						      {0.725673, 0.559406, 0.403204, 0.446419, 0.260943, 0.284175, 0.128093, 0.195321},
						      {0.769093, 0.569824, 0.463672, 0.462613, 0.461801, 0.321627, 0.111931, 0.00971348},
						      {0.81483, 0.606154, 0.545331, 0.416863, 0.36792, 0.272393, 0.00184041, 0},
						      {0.837438, 0.647361, 0.584875, 0, 0, 0, 0, 0},
						      {0.860022, 0.715719, 0, 0, 0, 0, 0, 0},
						      {0.886969, 0.821569, 0, 0, 0, 0, 0, 0},
						      {0.911961, 0.794627, 0, 0, 0, 0, 0, 0},
						      {0.926772, 0, 0, 0, 0, 0, 0, 0},
						      {0.93544, 0, 0, 0, 0, 0, 0, 0},
						      {0.952007, 0, 0, 0, 0, 0, 0, 0}},

  //for ICR
						     {{3.57833, 1.91894, 5.91197, 0, 1.22795, 0, 0.203306, 0},
						      {1.32177, 0.876237, 0.902961, 0.51069, 0.642968, 0.184353, 0.26477, 0.280494},
						      {1.02189, 0.815945, 0.652347, 0.458803, 0.214893, 0.320039, 0.194006, 0.160185},
						      {0.743814, 0.483814, 0.352681, 0.152844, 0.55383, 0.143196, 0.259946, 0.212512},
						      {0.590542, 0.45244, 0.355221, 0.334925, 0.435896, 0.26321, 0.208281, 0.109644},
						      {0.573406, 0.397041, 0.258604, 0.331425, 0.347742, 0.335685, 0.296111, 0.117589},
						      {0.518094, 0.318118, 0.272763, 0.295351, 0.268906, 0.405808, 0.199122, 0.0494783},
						      {0.489967, 0.281471, 0.232761, 0.253408, 0.250709, 0.208408, 0.102148, 0.0683412},
						      {0.515948, 0.270601, 0.242737, 0.22975, 0.202629, 0.145832, 0.0729419, 0.0231781},
						      {0.532508, 0.289104, 0.250969, 0.202295, 0.125441, 0.0730969, 0.0639817, 0.0111137},
						      {0.553654, 0.268965, 0.204574, 0.103355, 0.0698564, 0.0799616, 0.0334438, 0.0150058},
						      {0.570316, 0.21355, 0.0785482, 0.0454183, 0.0459296, 0.0295985, 0.0157112, 0.00768973},
						      {0.57773, 0.102551, 0.0517708, 0.0405679, 0.019127, 0.0212034, 0.0192682, 0.0133812},
						      {0.605375, 0.0853159, 0.0465787, 0.0601071, 0, 0.00928211, 0, 0},
						      {0.602947, 0.0890647, 0.0454792, 0.0582906, 0.0488123, 0.0532831, 0, 0},
						      {0.638049, 0.0795275, 0.0605934, 0, 0.0115565, 0.0516018, 0, 0}},

  //for CC
						     {{3.73302, 2.81973, 0.550156, 0, 3.11621, 0, 0, 0.405626},
						      {1.88881, 1.27376, 0.212165, 1.14652, 1.00571, 0, 0, 1.16896},
						      {1.11801, 1.03926, 1.15707, 0.116321, 0.638205, 0.418155, 0.359574, 0},
						      {0.894985, 0.84287, 0.801826, 0.504003, 0.487188, 0.87649, 0.532912, 0.232266},
						      {0.769651, 0.607015, 0.494773, 0.367104, 0.448188, 0.284601, 0.341235, 0.424579},
						      {0.699647, 0.457143, 0.388978, 0.494751, 0.273939, 0.328401, 0.374484, 0.119801},
						      {0.666316, 0.442862, 0.341097, 0.310334, 0.416882, 0.402528, 0.340254, 0.154128},
						      {0.689884, 0.373006, 0.388971, 0.381731, 0.412459, 0.314584, 0.20623, 0.124084},
						      {0.757907, 0.46468, 0.460411, 0.452292, 0.367841, 0.226044, 0.0629196, 0},
						      {0.800568, 0.526352, 0.499005, 0.416639, 0.296079, 0.194666, 0, 0},
						      {0.834997, 0.599986, 0.545406, 0.454042, 0, 0.0834299, 0, 0},
						      {0.876826, 0.65784, 0.588559, 0, 0, 0, 0, 0},
						      {0.91066, 0.715542, 0, 0, 0, 0, 0, 0},
						      {0.934796, 0.775128, 0, 0, 0, 0, 0, 0},
						      {0.943491, 0, 0, 0, 0, 0, 0, 0},
						      {0.963331, 0, 0, 0, 0, 0, 0, 0}}};



  // code used to study W mass for different cuts
  bool passCut(TString cut_under_study, bool invert_cut,
               int runNo, int runNo_cut_lowcut, int runNo_cut_highcut,
               double InstLumi, double InstLumi_lowcut, double InstLumi_highcut,
               double ScalarEt, double ScalarEt_lowcut, double ScalarEt_highcut,
               double ElecEta, double ElecEta_cut,
               double ElecDetEta, double ElecDetEta_lowcut, double ElecDetEta_highcut,
               double ElecPhiMod, double ElecPhiMod_cut,
               double UPara, double UPara_lowcut, double UPara_highcut,
	       double ElecPt, double ElecPt_lowcut, double ElecPt_highcut,
	       double ElecPhi, double ElecPhi_lowcut, double ElecPhi_highcut,
	       double RecoilPhi, double RecoilPhi_lowcut, double RecoilPhi_highcut);

  bool passCutEvent(TString cut_under_study, bool invert_cut,
		    int runNo, int runNo_lowcut, int runNo_highcut,
		    double InstLumi, double InstLumi_lowcut, double InstLumi_highcut,
		    double ScalarEt, double ScalarEt_lowcut, double ScalarEt_highcut,
		    double RecoilPhi, double RecoilPhi_lowcut, double RecoilPhi_highcut);
  bool passCutElectron(TString cut_under_study, bool invert_cut,
		       double ElecEta, double ElecEta_cut,
		       double ElecDetEta, double ElecDetEta_lowcut, double ElecDetEta_highcut,
		       double ElecPhiMod, double ElecPhiMod_cut,
		       double UPara, double UPara_lowcut, double UPara_highcut,
		       double ElecPt, double ElecPt_lowcut, double ElecPt_highcut,
		       double ElecPhi, double ElecPhi_lowcut, double ElecPhi_highcut);

  // encode calorimeter cell (ieta, iphi, ilyr) to a unique integer
  int EncodeCellIndex(int ieta, int iphi, int ilyr);
  
  // decode a unique integer to calorimeter cell address (ieta, iphi, ilyr)
  void DecodeCellIndex(int cell_index, int& ieta, int& iphi, int& ilyr);
  
  // for a given vector of cuts and a given value, find the corresponding region
  void FindRegion(std::vector<double>& cut_vect, double value, int& region);
  
  // define physics eta region for CC electron
  int PhyEtaRegion_CC(double eta);
  
  // revertexing and calculate impact parameter, phi for a track with given b0, phi0
  // distance_vertices is a spatial vector (new vertex - old vertex)
  void BeamSpotCorrection(double b0, double phi0, double& b1,
			  double& phi1, double kappa, double distance_vertices[3]);
  
  // functions used for bremsstralung simulation
  double BremProba(double y, double k);
  void brem_simulation(double radiation_length, double y_min, int bin_y, double k,
		       double proba[100], double& proba_total, double& elec_energy_fraction, TRandom3 *random, double externrndm);

  // probability for in-cone photon to reach the calorimeter
  double photon_prob_in_cone(double pT, std::vector<float>& p0, std::vector<float>& p1, std::vector<float>& p2, std::vector<float>& p3);

  // probability for out-cone photon to reach the calorimeter
  double photon_prob_out_cone(double pT, std::vector<float>& p0, std::vector<float>& p1, std::vector<float>& p2, std::vector<float>& p3, std::vector<float>& p4);

  double photon_prob_out_cone_test( double pt, double deta);

  double calculate_dphi( double pt, double deta, TRandom3 *dummy);

  // response for in-cone photon that reached the calorimeter
  double photon_response_in_cone(double eta, double pT, std::vector<float>& p0, std::vector<float>& p1, std::vector<float>& p2,
				 std::vector<float>& p3, std::vector<float>& p4, std::vector<float>& p5);

  // response for out-cone photon that reached the calorimeter
  double photon_response_out_cone(double eta, double pT, std::vector<float>& p0, std::vector<float>& p1, std::vector<float>& p2,
				  std::vector<float>& p3, std::vector<float>& p4, std::vector<float>& p5);

  double photon_response_out_cone_test2(double pt, double deta, double dphi);


  // for singularity variable study
  float SingularityVariable(PMCSWCand& wcand, float trialmass, TRandom3* dummy); //main SV method
  float SingularityVariable_LongUnSmeared(PMCSWCand& wcand, PMCSWCand& wcand_gen, float trialmass, TRandom3* dummy);//used for check only

  bool interpolate2d(vector< vector < TProfile* > > hists, vector< float > boundaries1, vector < float > boundaries2,
		     vector< vector < double > > midpoints1, vector< vector < double > > midpoints2, double x, double y, double z, double& interp);
  double interpolate2d(TH2D* hist, Double_t x, Double_t y);
  double interpolate3d(TH3D* hist, Double_t x, Double_t y, Double_t z);
    
  int getbin(vector< float > boundaries, float val);
  int getbin(vector< double > boundaries, float val);
  
  inline int getbin(vector< float > boundaries, float val) {
    int retval = -1;
    for (int i=0; i<boundaries.size(); i++) {
      if (val >= boundaries[i]) retval++;
      else break;
    }
    return retval;
  } 

  inline int getbin(vector< double > boundaries, double val) {
    int retval = -1;
    for (int i=0; i<boundaries.size(); i++) {
      if (val >= boundaries[i]) retval++;
      else break;
    }
    return retval;
  } 

  inline bool interpolate2d(vector< vector < TProfile* > > hists, vector< float > boundaries1, vector < float > boundaries2,
			    vector< vector < double > > midpoints1, vector< vector < double > > midpoints2, double x, double y, double z, double& interp) {
    
    Int_t bin_x=-1, bin_y=-1;
    Double_t x0=0,x1=0,x2=0,y0=0,y1=0,y2=0;
    Int_t bin_0=-1, bin_1=-1;
    Int_t quadrant=-1;
    Double_t q11=0,q12=0,q21=0,q22=0;
    Int_t bin_q11=-1,bin_q12=-1,bin_q21=-1,bin_q22=-1;

    for (Int_t i=0; i<boundaries1.size(); i++) {
      if (x > boundaries1[i]) bin_x++;
      else break;
    }
    if (bin_x < 0 || bin_x > (boundaries1.size() - 2)) return false;
    for (Int_t i=0; i<boundaries2.size(); i++) {
      if (y > boundaries2[i]) bin_y++;
      else break;
    }
    if (bin_y < 0 || bin_y > (boundaries2.size() - 2)) return false;
    

    if (x < boundaries1[1] || x > boundaries1[boundaries1.size()-2] )  {
      
      if (y < boundaries2[1] || y > boundaries2[boundaries2.size()-2]) {
	
	bin_0 = hists[bin_x][bin_y]->FindBin(z);
	interp = hists[bin_x][bin_y]->GetBinContent(bin_0);
	return true;
      } else { 
	
	if(y<=midpoints2[bin_x][bin_y]) {
	  bin_0 = hists[bin_x][bin_y-1]->FindBin(z);
	  y0 = hists[bin_x][bin_y-1]->GetBinContent(bin_0);;
	  x0 = midpoints2[bin_x][bin_y-1];
	  bin_1 = hists[bin_x][bin_y]->FindBin(z);
	  y1 = hists[bin_x][bin_y]->GetBinContent(bin_1);;
	  x1 = midpoints2[bin_x][bin_y];
	} else {
	  bin_0 = hists[bin_x][bin_y]->FindBin(z);
	  y0 = hists[bin_x][bin_y]->GetBinContent(bin_0);;
	  x0 = midpoints2[bin_x][bin_y];
	  bin_1 = hists[bin_x][bin_y+1]->FindBin(z);
	  y1 = hists[bin_x][bin_y+1]->GetBinContent(bin_1);;
	  x1 = midpoints2[bin_x][bin_y+1];
	}
	interp = y0 + (x-x0)*((y1-y0)/(x1-x0));
	return true;
      }
      
    } else if (y <= boundaries2[1] || y > boundaries2[boundaries2.size()-2] || 
	       y <= boundaries2[1] || y > boundaries2[boundaries2.size()-2] || 
	       y <= boundaries2[1] || y > boundaries2[boundaries2.size()-2]) {

      if(x<=midpoints1[bin_x][bin_y]) {
	bin_0 = hists[bin_x-1][bin_y]->FindBin(z);
	y0 = hists[bin_x-1][bin_y]->GetBinContent(bin_0);;
	x0 = midpoints1[bin_x-1][bin_y];
	bin_1 = hists[bin_x][bin_y]->FindBin(z);
	y1 = hists[bin_x][bin_y]->GetBinContent(bin_1);;
	x1 = midpoints1[bin_x][bin_y];
      } else {
	bin_0 = hists[bin_x][bin_y]->FindBin(z);
	y0 = hists[bin_x][bin_y]->GetBinContent(bin_0);;
	x0 = midpoints1[bin_x][bin_y];
	bin_1 = hists[bin_x+1][bin_y]->FindBin(z);
	y1 = hists[bin_x+1][bin_y]->GetBinContent(bin_1);;
	x1 = midpoints1[bin_x+1][bin_y];
      }
      interp = y0 + (x-x0)*((y1-y0)/(x1-x0));
      return true;
	
    } else {	    
      
      if (x<=midpoints1[bin_x][bin_y] && y<=midpoints2[bin_x][bin_y])
	quadrant = 3;
      if (x>midpoints1[bin_x][bin_y] && y<=midpoints2[bin_x][bin_y])
	quadrant = 4;
      if (x>midpoints1[bin_x][bin_y] && y>midpoints2[bin_x][bin_y])
	quadrant = 1;
      if (x<=midpoints1[bin_x][bin_y] && y>midpoints2[bin_x][bin_y])
	quadrant = 2;
      switch(quadrant) {
      case 1:
	x1 = midpoints1[bin_x][bin_y];	      
	y1 = midpoints2[bin_x][bin_y];
	x2 = midpoints1[bin_x+1][bin_y];
	y2 = midpoints2[bin_x][bin_y+1];
	bin_q11 = hists[bin_x][bin_y]->FindBin(z);
	bin_q12 = hists[bin_x][bin_y+1]->FindBin(z);
	bin_q21 = hists[bin_x+1][bin_y]->FindBin(z);
	bin_q22 = hists[bin_x+1][bin_y+1]->FindBin(z);
	q11 = hists[bin_x][bin_y]->GetBinContent(bin_q11);
	q12 = hists[bin_x][bin_y+1]->GetBinContent(bin_q12);
	q21 = hists[bin_x+1][bin_y]->GetBinContent(bin_q21);
	q22 = hists[bin_x+1][bin_y+1]->GetBinContent(bin_q22);
	break;
      case 2:
	x1 = midpoints1[bin_x-1][bin_y];
	y1 = midpoints2[bin_x][bin_y];
	x2 = midpoints1[bin_x][bin_y];
	y2 = midpoints2[bin_x][bin_y+1];
	bin_q11 = hists[bin_x-1][bin_y]->FindBin(z);
	bin_q12 = hists[bin_x-1][bin_y+1]->FindBin(z);
	bin_q21 = hists[bin_x][bin_y]->FindBin(z);
	bin_q22 = hists[bin_x][bin_y+1]->FindBin(z);
	q11 = hists[bin_x-1][bin_y]->GetBinContent(bin_q11);
	q12 = hists[bin_x-1][bin_y+1]->GetBinContent(bin_q12);
	q21 = hists[bin_x][bin_y]->GetBinContent(bin_q21);
	q22 = hists[bin_x][bin_y+1]->GetBinContent(bin_q22);
	break;
      case 3:
	x1 = midpoints1[bin_x-1][bin_y];
	y1 = midpoints2[bin_x][bin_y-1];
	x2 = midpoints1[bin_x][bin_y];
	y2 = midpoints2[bin_x][bin_y];
	bin_q11 = hists[bin_x-1][bin_y-1]->FindBin(z);
	bin_q12 = hists[bin_x-1][bin_y]->FindBin(z);
	bin_q21 = hists[bin_x][bin_y-1]->FindBin(z);
	bin_q22 = hists[bin_x][bin_y]->FindBin(z);
	q11 = hists[bin_x-1][bin_y-1]->GetBinContent(bin_q11);
	q12 = hists[bin_x-1][bin_y]->GetBinContent(bin_q12);
	q21 = hists[bin_x][bin_y-1]->GetBinContent(bin_q21);
	q22 = hists[bin_x][bin_y]->GetBinContent(bin_q22);
	break;
      case 4:
	x1 = midpoints1[bin_x][bin_y];
	y1 = midpoints2[bin_x][bin_y-1];
	x2 = midpoints1[bin_x+1][bin_y];
	y2 = midpoints2[bin_x][bin_y];
	bin_q11 = hists[bin_x][bin_y-1]->FindBin(z);
	bin_q12 = hists[bin_x][bin_y]->FindBin(z);
	bin_q21 = hists[bin_x+1][bin_y-1]->FindBin(z);
	bin_q22 = hists[bin_x+1][bin_y]->FindBin(z);
	q11 = hists[bin_x][bin_y-1]->GetBinContent(bin_q11);
	q12 = hists[bin_x][bin_y]->GetBinContent(bin_q12);
	q21 = hists[bin_x+1][bin_y-1]->GetBinContent(bin_q21);
	q22 = hists[bin_x+1][bin_y]->GetBinContent(bin_q22);
	break;
      }
      
      Double_t d = 1.0*(x2-x1)*(y2-y1);
      interp = 1.0*q11/d*(x2-x)*(y2-y)+1.0*q21/d*(x-x1)*(y2-y)+1.0*q12/d*(x2-x)*(y-y1)+1.0*q22/d*(x-x1)*(y-y1);
      return true;

	      
    }
    

    return false;

  }

  inline double interpolate2d(TH2D* hist, Double_t x, Double_t y)
  {

    Double_t f=0;
    Double_t x1=0,x2=0,y1=0,y2=0;
    Double_t dx,dy;
    Int_t bin_x = hist->GetXaxis()->FindBin(x);
    Int_t bin_y = hist->GetYaxis()->FindBin(y);
    if(bin_x<1 || bin_x>hist->GetNbinsX() || bin_y<1 || bin_y>hist->GetNbinsY()) {
      Double_t retval = hist->GetBinContent(hist->FindBin(x,y));
      return retval;
    }
    Int_t quadrant = 0; // CCW from UR 1,2,3,4
    // which quadrant of the bin (bin_P) are we in?
    dx = hist->GetXaxis()->GetBinUpEdge(bin_x)-x;
    dy = hist->GetYaxis()->GetBinUpEdge(bin_y)-y;
    if (dx<=hist->GetXaxis()->GetBinWidth(bin_x)/2 && dy<=hist->GetYaxis()->GetBinWidth(bin_y)/2)
      quadrant = 1; // upper right
    if (dx>hist->GetXaxis()->GetBinWidth(bin_x)/2 && dy<=hist->GetYaxis()->GetBinWidth(bin_y)/2)
      quadrant = 2; // upper left
    if (dx>hist->GetXaxis()->GetBinWidth(bin_x)/2 && dy>hist->GetYaxis()->GetBinWidth(bin_y)/2)
      quadrant = 3; // lower left
    if (dx<=hist->GetXaxis()->GetBinWidth(bin_x)/2 && dy>hist->GetYaxis()->GetBinWidth(bin_y)/2)
      quadrant = 4; // lower right
    switch(quadrant) {
    case 1:
      x1 = hist->GetXaxis()->GetBinCenter(bin_x);
      y1 = hist->GetYaxis()->GetBinCenter(bin_y);
      x2 = hist->GetXaxis()->GetBinCenter(bin_x+1);
      y2 = hist->GetYaxis()->GetBinCenter(bin_y+1);
      break;
    case 2:
      x1 = hist->GetXaxis()->GetBinCenter(bin_x-1);
      y1 = hist->GetYaxis()->GetBinCenter(bin_y);
      x2 = hist->GetXaxis()->GetBinCenter(bin_x);
      y2 = hist->GetYaxis()->GetBinCenter(bin_y+1);
      break;
    case 3:
      x1 = hist->GetXaxis()->GetBinCenter(bin_x-1);
      y1 = hist->GetYaxis()->GetBinCenter(bin_y-1);
      x2 = hist->GetXaxis()->GetBinCenter(bin_x);
      y2 = hist->GetYaxis()->GetBinCenter(bin_y);
      break;
    case 4:
      x1 = hist->GetXaxis()->GetBinCenter(bin_x);
      y1 = hist->GetYaxis()->GetBinCenter(bin_y-1);
      x2 = hist->GetXaxis()->GetBinCenter(bin_x+1);
      y2 = hist->GetYaxis()->GetBinCenter(bin_y);
      break;
    }
    Int_t bin_x1 = hist->GetXaxis()->FindBin(x1);
    if(bin_x1<1) bin_x1=1;
    Int_t bin_x2 = hist->GetXaxis()->FindBin(x2);
    if(bin_x2>hist->GetNbinsX()) bin_x2=hist->GetNbinsX();
    Int_t bin_y1 = hist->GetYaxis()->FindBin(y1);
    if(bin_y1<1) bin_y1=1;
    Int_t bin_y2 = hist->GetYaxis()->FindBin(y2);
    if(bin_y2>hist->GetNbinsY()) bin_y2=hist->GetNbinsY();
    Int_t bin_q22 = hist->GetBin(bin_x2,bin_y2);
    Int_t bin_q12 = hist->GetBin(bin_x1,bin_y2);
    Int_t bin_q11 = hist->GetBin(bin_x1,bin_y1);
    Int_t bin_q21 = hist->GetBin(bin_x2,bin_y1);
    Double_t q11 = hist->GetBinContent(bin_q11);
    Double_t q12 = hist->GetBinContent(bin_q12);
    Double_t q21 = hist->GetBinContent(bin_q21);
    Double_t q22 = hist->GetBinContent(bin_q22);
    Double_t d = 1.0*(x2-x1)*(y2-y1);
    f = 1.0*q11/d*(x2-x)*(y2-y)+1.0*q21/d*(x-x1)*(y2-y)+1.0*q12/d*(x2-x)*(y-y1)+1.0*q22/d*(x-x1)*(y-y1);
    return f;
  }

  inline double interpolate3d(TH3D* hist, Double_t x, Double_t y, Double_t z) 
  {

    Int_t ubx = hist->GetXaxis()->FindBin(x);
    if ( x < hist->GetXaxis()->GetBinCenter(ubx) ) ubx -= 1;
    Int_t obx = ubx + 1;

    Int_t uby = hist->GetYaxis()->FindBin(y);
    if ( y < hist->GetYaxis()->GetBinCenter(uby) ) uby -= 1;
    Int_t oby = uby + 1;

    Int_t ubz = hist->GetZaxis()->FindBin(z);
    if ( z < hist->GetZaxis()->GetBinCenter(ubz) ) ubz -= 1;
    Int_t obz = ubz + 1;


    if (ubx <=0 || uby <=0 || ubz <= 0 ||
	obx > hist->GetXaxis()->GetNbins() || oby > hist->GetYaxis()->GetNbins() || obz > hist->GetZaxis()->GetNbins() ) {
      Double_t retval = hist->GetBinContent(hist->FindBin(x,y,z));
      return retval;
    }

    Double_t xw = hist->GetXaxis()->GetBinCenter(obx) - hist->GetXaxis()->GetBinCenter(ubx);
    Double_t yw = hist->GetYaxis()->GetBinCenter(oby) - hist->GetYaxis()->GetBinCenter(uby);
    Double_t zw = hist->GetZaxis()->GetBinCenter(obz) - hist->GetZaxis()->GetBinCenter(ubz);

    Double_t xd = (x - hist->GetXaxis()->GetBinCenter(ubx)) / xw;
    Double_t yd = (y - hist->GetYaxis()->GetBinCenter(uby)) / yw;
    Double_t zd = (z - hist->GetZaxis()->GetBinCenter(ubz)) / zw;


    Double_t v[] = { hist->GetBinContent( ubx, uby, ubz ), hist->GetBinContent( ubx, uby, obz ),
		     hist->GetBinContent( ubx, oby, ubz ), hist->GetBinContent( ubx, oby, obz ),
		     hist->GetBinContent( obx, uby, ubz ), hist->GetBinContent( obx, uby, obz ),
		     hist->GetBinContent( obx, oby, ubz ), hist->GetBinContent( obx, oby, obz ) };


    Double_t i1 = v[0] * (1 - zd) + v[1] * zd;
    Double_t i2 = v[2] * (1 - zd) + v[3] * zd;
    Double_t j1 = v[4] * (1 - zd) + v[5] * zd;
    Double_t j2 = v[6] * (1 - zd) + v[7] * zd;


    Double_t w1 = i1 * (1 - yd) + i2 * yd;
    Double_t w2 = j1 * (1 - yd) + j2 * yd;


    Double_t result = w1 * (1 - xd) + w2 * xd;
    return result;
  }

  inline float SingularityVariable(PMCSWCand& wcand, float trialmass, TRandom3* dummy) {
    
    // The lepton and recoil four momenta
    TLorentzVector lepton = wcand.GetElec().GetLorentzVect();
    TLorentzVector recoil(wcand.GetRecoil().Recoilx(), wcand.GetRecoil().Recoily(), 0., wcand.GetRecoil().Recoil());
    
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

  inline float SingularityVariable_LongUnSmeared(PMCSWCand& wcand, PMCSWCand& wcand_gen, float trialmass, TRandom3* dummy) {

    // The lepton and recoil four momenta
    TLorentzVector lepton = wcand.GetElec().GetLorentzVect();
    TLorentzVector lepton_gen = wcand_gen.GetElec().GetLorentzVect();
    lepton.SetPz(lepton_gen.Pz());

    TLorentzVector recoil(wcand.GetRecoil().Recoilx(), wcand.GetRecoil().Recoily(), 0., wcand.GetRecoil().Recoil());
    
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

  // Scalar Et model for hard component only modelled using 1-dimensional RooPdfKeys technique.
  // For details see W-mass talk by Mikolaj on Sep 27, 2007
  void ScalarEt_ver1(double true_PT,
		     double recoil_UT,
		     double &scalar_ET, 
		     double &scalar_ET_expectation,
		     const char *fname);
    
    // Scalar Et model for hard component only modelled using 2-dimensional RooPdf2dKeys technique.
  // For details see W-mass talk by Mikolaj on Dec 12, 2007 (Model #3).
  // Parameters that work best are: 
  //  INIT_model=3
  //  INIT_USE_PT_INTERPOLATION=false
  //  INIT_USE_UT_INTERPOLATION=false
  //  INIT_USE_UT_CENTRAL_VALUE=false
  //  INIT_USE_UT_INTERPOLATION_IF_EMPTY=false.
  //  scalarEt_input_root_filename="../geant/ScalarEt_input_model=3.root".
  //
  // Currently 4 models can be selected by user: 
  //  model=0 : use parameterized x:=(Recoil UT)/(Recoil SET) vs (Recoil UT) vs (generated PT)
  //  model=1 : use parameterized x:=(Recoil SET) vs (Recoil UT) vs (generated PT)
  //  model=2 : use parameterized x:=(Recoil UT)/(Recoil SET) vs [1-(Recoil UT)/(generated PT)] vs (generated PT)
  //  model=3 : use parameterized x:=(Recoil SET)-(Recoil UT) vs (Recoil UT) vs (generated PT)
  // Each of them requires a separate input ROOT file. 
  void ScalarEt_ver2(double true_PT,
		     double recoil_UT,
		     double &scalar_ET, 
		     double &scalar_ET_expectation,
		     const char *scalarEt_input_root_filename,
		     int  INIT_model=3,
		     bool INIT_USE_PT_INTERPOLATION=false,
		     bool INIT_USE_UT_INTERPOLATION=false,
		     bool INIT_USE_UT_CENTRAL_VALUE=false,
		     bool INIT_USE_UT_INTERPOLATION_IF_EMPTY=false);
  
  // Scalar Et model
  // Currently ScalarEt_ver1 is our DEFAULT model.
  inline void ScalarEt(double true_PT,
		       double recoil_UT,
		       double &scalar_ET, 
		       double &scalar_ET_expectation,
		       const char* fname) {
    //ScalarEt_ver1(true_PT, recoil_UT, scalar_ET, scalar_ET_expectation, fname);
    ScalarEt_ver2(true_PT, recoil_UT, scalar_ET, scalar_ET_expectation, fname);
  }
  
  // from true recoil pT and phi to smeared pT and phi (from Mikolaj's new bifurcated model)
  void FlipARecoil2(double truepT, 
		    double truephi, 
		    double& smpT, 
		    double& smphi, 
		    double RelScale, 
		    double RelOffset,
		    double RelTau,
		    double RelSampA, 
		    double RelSampB, 
		    double RelConst,
		    double RelRespTrans,
                    double RelResnTrans,
                    double RelTauTrans,
		    double RelPhiA,
		    double RelPhiB, 
		    double PhiConst,
		    double pt_resol_external=-1.0, // effective only when skip_Znunu_randomization=TRUE
		    double delta_phi_external=-1.0,// effective only when skip_Znunu_randomization=TRUE  
		    bool skip_Znunu_randomization=false,
		    bool skip_Znunu_fudging=false,
		    int EtFlowFudge=0,
		    double instlum=-1);
  
  // for bifurcated 6
  Double_t bifurcated2d_for_FlipARecoil_BIFURCATED6(Double_t *x, Double_t *par);
  void FlipARecoil_BIFURCATED6(double truepT, 
			       double truephi, 
			       double& smpT, 
			       double& smphi, 
			       double RelScale, 
			       double RelOffset, 
			       double RelTau,
			       double RelSampA,
			       double RelSampB, 
			       double RelConst, 
			       double RelPhiA, 
			       double RelPhiB, 
			       double PhiConst,
			       double pt_resol_external=-1.0, // effective only when skip_Znunu_randomization=TRUE
			       double delta_phi_external=-1.0,// effective only when skip_Znunu_randomization=TRUE  
			       bool skip_Znunu_randomization=false,
			       bool skip_Znunu_fudging=false);
  
  // for bifurcated 7
  Double_t bifurcated2d_for_FlipARecoil_BIFURCATED7(Double_t *x, Double_t *par);
  void FlipARecoil_BIFURCATED7(double truepT, 
			       double truephi, 
			       double& smpT, 
			       double& smphi, 
			       double RelScale, 
			       double RelOffset, 
			       double RelTau,
			       double RelSampA,
			       double RelSampB, 
			       double RelConst,
			       double RelRespTrans,
			       double RelResnTrans,
			       double RelTauTrans,
			       double RelPhiA, 
			       double RelPhiB, 
			       double PhiConst,
			       double pt_resol_external=-1.0, // effective only when skip_Znunu_randomization=TRUE
			       double delta_phi_external=-1.0,// effective only when skip_Znunu_randomization=TRUE  
			       bool skip_Znunu_randomization=false,
			       bool skip_Znunu_fudging=false,
			       int EtFlowFudge=0,
			       double instlum=-1);
  
  // determine pT_ee * eta direction region
  int pTee_Eta_Bin(double pee_eta);

  // generate random numbers according to Crystall Ball function
  double flipCrystalBall(double mean, double sigma, double alpha, double n, TRandom* r, double *extnRndm=0);
}

// code used to study W mass for different cuts
inline bool wz_utils::passCut(TString cut_under_study, bool invert_cut,
                              int runNo, int runNo_lowcut, int runNo_highcut,
                              double InstLumi, double InstLumi_lowcut, double InstLumi_highcut,
                              double ScalarEt, double ScalarEt_lowcut, double ScalarEt_highcut,
                              double ElecEta, double ElecEta_cut,
                              double ElecDetEta, double ElecDetEta_lowcut, double ElecDetEta_highcut,
                              double ElecPhiMod, double ElecPhiMod_cut,
                              double UPara, double UPara_lowcut, double UPara_highcut,
			      double ElecPt, double ElecPt_lowcut, double ElecPt_highcut,
			      double ElecPhi, double ElecPhi_lowcut, double ElecPhi_highcut,
			      double RecoilPhi, double RecoilPhi_lowcut, double RecoilPhi_highcut) {

  bool cevt = passCutEvent(cut_under_study, invert_cut, 
			   runNo, runNo_lowcut, runNo_highcut,
			   InstLumi, InstLumi_lowcut, InstLumi_highcut,
			   ScalarEt, ScalarEt_lowcut, ScalarEt_highcut,
			   RecoilPhi, RecoilPhi_lowcut, RecoilPhi_highcut);
  bool cele = passCutElectron(cut_under_study, invert_cut,
			      ElecEta, ElecEta_cut,
			      ElecDetEta, ElecDetEta_lowcut, ElecDetEta_highcut,
			      ElecPhiMod, ElecPhiMod_cut,
			      UPara, UPara_lowcut, UPara_highcut,
			      ElecPt, ElecPt_lowcut, ElecPt_highcut,
			      ElecPhi, ElecPhi_lowcut, ElecPhi_highcut);

  return (cevt&&cele);
}

inline bool wz_utils::passCutEvent(TString cut_under_study, bool invert_cut,
				   int runNo, int runNo_lowcut, int runNo_highcut,
				   double InstLumi, double InstLumi_lowcut, double InstLumi_highcut,
				   double ScalarEt, double ScalarEt_lowcut, double ScalarEt_highcut,
				   double RecoilPhi, double RecoilPhi_lowcut, double RecoilPhi_highcut) {
  bool passTheCut = true;
  if(cut_under_study.Contains("runNo_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (runNo<runNo_lowcut) || (runNo>runNo_highcut) );
    else passTheCut = passTheCut&&( (runNo>=runNo_lowcut) && (runNo<=runNo_highcut) );
  }
  if (cut_under_study.Contains("InstLumi_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (InstLumi<InstLumi_lowcut) || (InstLumi>InstLumi_highcut) );
    else passTheCut = passTheCut&&( (InstLumi>=InstLumi_lowcut) && (InstLumi<=InstLumi_highcut) );
  }
  if(cut_under_study.Contains("ScalarEt_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (ScalarEt<ScalarEt_lowcut) || (ScalarEt>ScalarEt_highcut));
    else passTheCut = passTheCut&&( (ScalarEt>=ScalarEt_lowcut) && (ScalarEt<=ScalarEt_highcut) );
  }
  if(cut_under_study.Contains("RecoilPhi_cut")) {
    if(invert_cut) passTheCut = passTheCut&&( (RecoilPhi<RecoilPhi_lowcut) || (RecoilPhi>RecoilPhi_highcut) );
    else passTheCut = passTheCut&&( (RecoilPhi>=RecoilPhi_lowcut) && (RecoilPhi<=RecoilPhi_highcut) );
  }

  return passTheCut;
}

inline bool wz_utils::passCutElectron(TString cut_under_study, bool invert_cut,
				      double ElecEta, double ElecEta_cut,
				      double ElecDetEta, double ElecDetEta_lowcut, double ElecDetEta_highcut,
				      double ElecPhiMod, double ElecPhiMod_cut,
				      double UPara, double UPara_lowcut, double UPara_highcut,
				      double ElecPt, double ElecPt_lowcut, double ElecPt_highcut,
				      double ElecPhi, double ElecPhi_lowcut, double ElecPhi_highcut) {
  bool passTheCut = true;

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

  return passTheCut;
}

inline int wz_utils::PhyEtaRegion_CC(double eta) {
 if(eta<-1.1) return 0;
 else if (eta<-0.9) return 1;
 else if (eta<-0.7) return 2;
 else if (eta<-0.5) return 3;
 else if (eta<-0.3) return 4;
 else if (eta<-0.1) return 5;
 else if (eta<0.1) return 6;
 else if (eta<0.3) return 7;
 else if (eta<0.5) return 8;
 else if (eta<0.7) return 9;
 else if (eta<0.9) return 10;
 else if (eta<1.1) return 11;
 else return 12;
}

inline int wz_utils::EncodeCellIndex(int ieta, int iphi, int ilyr) {
 int ieta_new = 0;
 if(ieta<0) ieta_new = abs(ieta)+40;
 else ieta_new = ieta;

 return (ieta_new*10000 + iphi*100 + ilyr);
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
inline void wz_utils::BeamSpotCorrection(double b0, double phi0, double& b1,
                                        double& phi1, double kappa, double distance_vertices[3]) {
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
  //std::cout << "y = " << y << std::endl; 
 return ( ( (1.-y)*(k+4./3) + y*y)/y );
}

//calculate the probability of the electron to emit a photon after it travels through radiation
//length radiation_length
inline void wz_utils::brem_simulation(double radiation_length, double y_min, int bin_y, double k,
				      double proba[100], double& proba_total, double& elec_energy_fraction, TRandom3 *random, double externrndm) {

 elec_energy_fraction = 1.;

 double step_y = (1. - y_min)/bin_y;    //calculate dy
 double proba_add[100] = {0.};

 proba_total = 0.;

 //
 //calculate the probability for the electron to emit a photon with fraction of energy given by y
 //
 for(int istep = 0; istep < bin_y; istep ++) {
   proba[istep] = 0.5*step_y*BremProba(y_min + istep * step_y, k);
   //    std::cout << "The probability to emit a photon that carries " << y_min + istep * step_y
   //        << " percent of the electron energy is " << proba[istep]*radiation_length << std::endl;
   proba_total += proba[istep]*radiation_length;
   proba_add[istep] = proba_total;
   
 }
 
 if  (proba_total > 0.9){
   std::cout << "Total Probability = " << proba_total << std::endl;
 }
 double rand = random -> Rndm();
 
 
 if (externrndm){
   rand = externrndm;
 }
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

// probability for in-cone photon to reach the calorimeter
inline double wz_utils::photon_prob_in_cone(double pT, std::vector<float>& p0, std::vector<float>& p1, std::vector<float>& p2, std::vector<float>& p3) {
  double val = 0.;
  if(pT < p3[0]) val = p0[0] + p1[0]*log(pT) + p2[0]*pow(log(pT), 2);
  else val = p0[0] + p1[0]*log(p3[0]) + p2[0]*pow(log(p3[0]), 2);
  return val;
}

// probability for out-cone photon to reach the calorimeter
inline double wz_utils::photon_prob_out_cone(double pT, std::vector<float>& p0, std::vector<float>& p1, std::vector<float>& p2, std::vector<float>& p3, std::vector<float>& p4) {
  double val = 0.;

  if(pT < p4[0]) val = p0[0] + p1[0]*pT + p2[0]*pT*pT + p3[0]*pT*pT*pT;
  else val = p0[0] + p1[0]*p4[0] + p2[0]*p4[0]*p4[0] + p3[0]*p4[0]*p4[0]*p4[0];
  return val;
}

inline double wz_utils::photon_prob_out_cone_test( double pt, double deta) {
  //TF1 paramfracpt0("paramfracpt0","[0]*TMath::Exp([1]*x) + [2]*TMath::Gaus(x,0,[3])",0,100);
  //paramfracpt0.SetParameters(0.6653, -7.842, 0.1921, 0.004118); //for ec

  float x0 = 0.6653;
  float x1 = -7.842;
  float x2 = 0.1921;
  float x3 = 0.004118;

  if(fabs(deta) < 1.0)
    {
      //paramfracpt0.SetParameters(0.4524, -3.293, 0.5728, 0.2995);
      //paramfracpt0.SetParameters(0.4208, -3.660, 0.6123, 0.2936);  // fit to weighted bin centers

      x0 = 0.4208;
      x1 = -3.660;
      x2 = 0.6123;
      x3 = 0.2936 ;
    }
  else if(fabs(deta) < 1.5)
    {
      //paramfracpt0.SetParameters(0.4601, -0.4798, 0.5221, 0.2712);
      x0 = 0.4601;
      x1 = -0.4798;
      x2 = 0.5221;
      x3 = 0.2712 ;
    }

  float probmissed = x0 * TMath::Exp( x1*pt) + x2* TMath::Gaus(pt,0,x3);

  return (1.0 - probmissed);

  //return (1.0 - paramfracpt0.Eval(pt));

}

inline double wz_utils::calculate_dphi( double pt, double deta, TRandom3 *dummy)
{


/*
						      {{0, 0.8, 0.9, 0.933333, 0.933333, 0.95, 0.95, 0.983333, 1},
						       {0, 0.788104, 0.914498, 0.95539, 0.966543, 0.981413, 0.981413, 0.981413, 1},
						       {0, 0.809287, 0.92869, 0.958541, 0.968491, 0.9801, 0.988391, 0.995025, 1},
						       {0, 0.805257, 0.908005, 0.941458, 0.955795, 0.966547, 0.978495, 0.988053, 1},
						       {0, 0.841217, 0.938761, 0.957096, 0.96663, 0.974697, 0.982765, 0.994133, 1},
						       {0, 0.837289, 0.933086, 0.949957, 0.957678, 0.970546, 0.982271, 0.99714, 1},
						       {0, 0.859208, 0.929604, 0.940744, 0.947855, 0.955203, 0.972505, 0.996445, 1},
						       {0, 0.879981, 0.92747, 0.940518, 0.95194, 0.973641, 0.993279, 0.998902, 1},
						       {0, 0.907453, 0.937869, 0.957515, 0.976295, 0.994101, 0.999188, 1, 1},
						       {0, 0.928933, 0.963166, 0.986649, 0.996097, 0.999315, 1, 1, 1},
						       {0, 0.95496, 0.988081, 0.998681, 0.999848, 0.999899, 1, 1, 1},
						       {0, 0.983194, 0.999445, 1, 1, 1, 1, 1, 1},
						       {0, 0.997343, 1, 1, 1, 1, 1, 1, 1},
						       {0, 0.999591, 1, 1, 1, 1, 1, 1, 1},
						       {0, 1, 1, 1, 1, 1, 1, 1, 1},
						       {0, 1, 1, 1, 1, 1, 1, 1, 1}}};
*/

  int etabin = 0;
  if(fabs(deta) < 1.0) etabin = 2;
  else if(fabs(deta) < 1.5) etabin = 1;

  int ptbin = 0;
  for(int ipt = 0; ipt != 16; ++ipt)
    {
      if(pt > ptbins[ipt] && pt <=  ptbins[ipt + 1])
	{
	  ptbin = ipt;
	  break;
	}
    }
  
  double fprob = dummy->Uniform(0,1);
  
  for(int idphi = 0; idphi != 8; ++idphi)
    {
      if(fprob > probs_eta_pt_dphi[etabin][ptbin][idphi] && fprob <= probs_eta_pt_dphi[etabin][ptbin][idphi+1])
	{
	  double width = dphibins[idphi+1] - dphibins[idphi];
	  double frac_width = (fprob - probs_eta_pt_dphi[etabin][ptbin][idphi])/(probs_eta_pt_dphi[etabin][ptbin][idphi+1] - probs_eta_pt_dphi[etabin][ptbin][idphi]);
	  double dphi_ret = dphibins[idphi] + (frac_width*width);
	  if(dphi_ret > TMath::Pi()) dphi_ret =  TMath::Pi();
	  return dphi_ret;
	}
    }

  //return bad value to indicate error
  return -1;

}

// response for in-cone photon that reached the calorimeter
inline double wz_utils::photon_response_in_cone(double eta, double pT, std::vector<float>& p0, std::vector<float>& p1, std::vector<float>& p2,
						std::vector<float>& p3, std::vector<float>& p4, std::vector<float>& p5) {
  // for EC electrons, will use response from CC global response parameterization
  int eta_bin = -1;
  if((eta<=-1.0) && (eta>=-1.5)) eta_bin=0;
  else if((eta>-1.0)&&(eta<=-0.6)) eta_bin=1;
  else if((eta>-0.6)&&(eta<=-0.2)) eta_bin=2;
  else if((eta>-0.2)&&(eta<=0.2)) eta_bin=3;
  else if((eta>0.2)&&(eta<=0.6)) eta_bin=4;
  else if((eta>0.6)&&(eta<=1.0)) eta_bin=5;
  else if((eta>1.0)&&(eta<=1.5)) eta_bin=6;
  else eta_bin = 7;   // eta_bin = 7 for all EC electrons

  double val = 0;
  if(pT<1.) val = p0[eta_bin]*pow(pT, (double)(p1[eta_bin])) + p2[eta_bin]/pow(pT, (double)(p3[eta_bin]));
  else val = p0[eta_bin] + p2[eta_bin] + p4[eta_bin]*log(pT) + p5[eta_bin]*pow(log(pT), 2);
  return val;
}

// response for out-cone photon that reached the calorimeter
inline double wz_utils::photon_response_out_cone(double eta, double pT, std::vector<float>& p0, std::vector<float>& p1, std::vector<float>& p2,
						 std::vector<float>& p3, std::vector<float>& p4, std::vector<float>& p5) {
  // for EC electrons, will use response from CC global response parameterization
  int eta_bin = -1;
  if((eta<=-1.0) && (eta>=-1.5)) eta_bin=0;
  else if((eta>-1.0)&&(eta<=-0.6)) eta_bin=1;
  else if((eta>-0.6)&&(eta<=-0.2)) eta_bin=2;
  else if((eta>-0.2)&&(eta<=0.2)) eta_bin=3;
  else if((eta>0.2)&&(eta<=0.6)) eta_bin=4;
  else if((eta>0.6)&&(eta<=1.0)) eta_bin=5;
  else if((eta>1.0)&&(eta<=1.5)) eta_bin=6;
  else eta_bin = 7;   // eta_bin = 7 for all EC electrons

  double val = 0;
  if(pT<1.2) val = p0[eta_bin]*pT*p1[eta_bin] + p2[eta_bin]/pT*p3[eta_bin];
  else val = p0[eta_bin] + p2[eta_bin] + p4[eta_bin]*log(pT) + p5[eta_bin]*pow(log(pT), 2);
  return val;
}


inline double wz_utils::photon_response_out_cone_test2(double pt, double deta, double dphi)
{



/*
						     {{3.53821, 3.2194, 1.43268, 0, 3.11621, 0, 0, 0.405626},
						      {1.83108, 1.23461, 0.60635, 1.20325, 1.00571, 0, 0, 1.16896},
						      {1.156, 1.11912, 0.798423, 0.43982, 0.61936, 0.418155, 0.359574, 0},
						      {0.90645, 0.783143, 0.720247, 0.483931, 0.487188, 0.501829, 0.652769, 0.307741},
						      {0.774763, 0.585917, 0.477067, 0.438279, 0.440531, 0.324377, 0.347462, 0.385089},
						      {0.688901, 0.462837, 0.351332, 0.425861, 0.307861, 0.362156, 0.396107, 0.241729},
						      {0.654802, 0.395662, 0.381563, 0.319355, 0.397181, 0.422639, 0.35031, 0.137438},
						      {0.667716, 0.368086, 0.374981, 0.387017, 0.404513, 0.328678, 0.214394, 0.142174},
						      {0.727081, 0.438276, 0.469992, 0.457753, 0.367541, 0.208131, 0.0729172, 0},
						      {0.769389, 0.524326, 0.503804, 0.46132, 0.307893, 0.168454, 0, 0},
						      {0.803439, 0.595236, 0.561607, 0.465497, 0, 0.0834299, 0, 0},
						      {0.843683, 0.663939, 0.554694, 0, 0, 0, 0, 0},
						      {0.877876, 0.722043, 0, 0, 0, 0, 0, 0},
						      {0.902614, 0.775128, 0, 0, 0, 0, 0, 0},
						      {0.911152, 0, 0, 0, 0, 0, 0, 0},
						      {0.93158, 0, 0, 0, 0, 0, 0, 0}}};
*/


  int etabin = 0;
  if(fabs(deta) < 1.0) etabin = 2;
  else if(fabs(deta) < 1.5) etabin = 1;

  int ptbin = 0;
  for(int ipt = 0; ipt != 16; ++ipt)
    {
      if(pt > ptbins[ipt] && pt <=  ptbins[ipt + 1])
	{
	  ptbin = ipt;
	  break;
	}
    }

  int dphibin = 0;
  for(int idphi = 0; idphi != 8; ++idphi)
    {
      if(dphi > dphibins[idphi] && dphi <=  dphibins[idphi + 1])
	{
	  dphibin = idphi;
	  break;
	}
    }  

  return respo_eta_pt_dphi[etabin][ptbin][dphibin];

}

// bifurcated model measured from Z->nunu events
// from true recoil pT and phi to smeared recoil pT and phi
inline void wz_utils::FlipARecoil2(double truepT, 
				   double truephi, 
				   double& smpT, 
				   double& smphi, 
				   double RelScale, 
				   double RelOffset, 
				   double RelTau,
				   double RelSampA, 
				   double RelSampB, 
				   double RelConst,
				   double RelRespTrans,
				   double RelResnTrans,
				   double RelTauTrans,
				   double RelPhiA, 
				   double RelPhiB, 
				   double PhiConst,
				   double pt_resol_external, // effective only when skip_Znunu_randomization=TRUE
				   double delta_phi_external,// effective only when skip_Znunu_randomization=TRUE
				   bool skip_Znunu_randomization,
				   bool skip_Znunu_fudging,
				   int EtFlowFudge,
				   double instlum) {
  FlipARecoil_BIFURCATED7(truepT, truephi, smpT, smphi, RelScale, RelOffset, RelTau, RelSampA, RelSampB, RelConst, RelRespTrans, RelResnTrans, RelTauTrans, RelPhiA, RelPhiB, PhiConst,
			  pt_resol_external, // effective only when skip_Znunu_randomization=TRUE
			  delta_phi_external,// effective only when skip_Znunu_randomization=TRUE  
			  skip_Znunu_randomization,
			  skip_Znunu_fudging,
			  EtFlowFudge, instlum);
  return;
}

//====================================================================================
// FlipARecoil_BIFURCATED6
//====================================================================================
// This funtion is based on the ASCII file dumped by a hacked ZAnalysis CAF processor
// using NuEtaCut=1.3 (CC-CC events) while processing 600k Z->nunu events from full MC.
//
// It calls internally bifurcated2d_for_FlipARecoil_BIFURCATED6() function which
// has 6 parameters (inluding one parameter for an absolute normalization).
//
inline Double_t wz_utils::bifurcated2d_for_FlipARecoil_BIFURCATED6(Double_t *x, Double_t *par) {
 Double_t Xmean=par[1]+par[2]*x[1];
 Double_t Ysigma=par[5]+par[2]*x[1];
 Double_t Xsigma;
 if(x[0]<Xmean) Xsigma=par[3];
 else           Xsigma=par[4];
 return par[0]*exp( -0.5*(pow( (x[0]-Xmean)/Xsigma, 2) + pow(x[1]/Ysigma, 2)));
}

inline void wz_utils::FlipARecoil_BIFURCATED6
(double truepT, 
 double truephi, 
 double& smpT, 
 double& smphi, 
 double RelScale, 
 double RelOffset, 
 double RelTau,
 double RelSampA, 
 double RelSampB, 
 double RelConst, 
 double RelPhiA, 
 double RelPhiB, 
 double PhiConst, 
 double pt_resol_external,  // effective only when skip_Znunu_randomization=TRUE
 double delta_phi_external, // effective only when skip_Znunu_randomization=TRUE  
 bool skip_Znunu_randomization,
 bool skip_Znunu_fudging       ) {
 //
 // Parameters of 2D probability distribution functions for
 // PT-resolution vs PHI-resolution for different true PT bins
 //
 const Int_t nbins=32;
 const Int_t ncols=22;
#if !defined (__CINT__)  // || defined (__MAKECINT__)
 static Float_t table[nbins*ncols]={
#else
 static Float_t table[32*22]={
#endif
 //Bin             Min.PT[GeV]    Max.PT[GeV]    Ave.PT[GeV]
 //Normal.par.     E(Normal.par.) Mean           E(Mean)
 //Slope.Mean      E(Slope.Mean)  Sigma L        E(Sigma L)
 //Sigma R         E(Sigma R)     Sigma PHI      E(Sigma PHI)
 //CHI**2          NDF            Min.PTres      Max.PTres
 //Min.PHIres[rad] Max.PHIres[rad]


  0              ,5.000000e-01   ,1.000000e+00   ,7.754628e-01   ,
   1.551167e-03   ,5.482889e-05   ,3.975326e-01   ,9.054281e-02   ,
   2.462614e-02   ,2.396368e-02   ,1.606513e+00   ,5.685288e-02   ,
   2.790570e-01   ,6.049788e-02   ,2.574569e+00   ,1.553708e-01   ,
   5.879046e+02   ,649            ,-8.573780e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   1              ,1.000000e+00   ,1.500000e+00   ,1.264908e+00   ,
   1.556796e-03   ,4.127117e-05   ,5.025333e-01   ,3.484264e-02   ,
   4.314286e-02   ,1.132592e-02   ,9.193455e-01   ,2.121784e-02   ,
   2.090548e-01   ,1.980231e-02   ,2.068940e+00   ,7.599341e-02   ,
   7.451861e+02   ,765            ,-4.800671e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   2              ,1.500000e+00   ,2.000000e+00   ,1.757492e+00   ,
   1.781548e-03   ,4.017908e-05   ,5.673272e-01   ,2.216983e-02   ,
   7.270107e-02   ,7.277211e-03   ,6.700977e-01   ,1.510659e-02   ,
   1.631267e-01   ,1.309770e-02   ,1.607806e+00   ,3.933994e-02   ,
   9.887886e+02   ,795            ,-3.583979e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   3              ,2.000000e+00   ,2.500000e+00   ,2.252469e+00   ,
   2.203538e-03   ,4.566596e-05   ,5.807759e-01   ,1.655900e-02   ,
   9.181845e-02   ,6.147332e-03   ,5.095641e-01   ,1.017870e-02   ,
   1.536551e-01   ,1.032190e-02   ,1.254275e+00   ,2.811864e-02   ,
   1.050968e+03   ,793            ,-2.644811e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   4              ,2.500000e+00   ,3.000000e+00   ,2.750494e+00   ,
   2.412590e-03   ,5.076133e-05   ,5.799698e-01   ,1.388046e-02   ,
   1.112584e-01   ,5.839168e-03   ,4.276524e-01   ,8.192380e-03   ,
   1.439311e-01   ,8.744995e-03   ,1.037427e+00   ,2.175887e-02   ,
   1.125584e+03   ,785            ,-2.266797e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   5              ,3.000000e+00   ,3.500000e+00   ,3.249376e+00   ,
   2.798263e-03   ,5.630693e-05   ,6.158710e-01   ,1.288090e-02   ,
   1.134459e-01   ,6.065571e-03   ,3.934235e-01   ,7.750956e-03   ,
   1.338805e-01   ,7.784725e-03   ,8.268124e-01   ,1.677453e-02   ,
   1.209946e+03   ,757            ,-2.183210e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   6              ,3.500000e+00   ,4.000000e+00   ,3.747003e+00   ,
   3.251548e-03   ,6.517025e-05   ,6.244777e-01   ,1.080626e-02   ,
   1.223086e-01   ,5.836856e-03   ,3.641872e-01   ,6.958635e-03   ,
   1.283124e-01   ,6.617278e-03   ,6.846520e-01   ,1.335912e-02   ,
   1.120629e+03   ,721            ,-2.102475e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   7              ,4.000000e+00   ,4.500000e+00   ,4.246392e+00   ,
   3.546645e-03   ,7.573152e-05   ,6.113976e-01   ,1.053003e-02   ,
   1.450368e-01   ,6.248795e-03   ,3.385627e-01   ,6.918167e-03   ,
   1.280123e-01   ,6.306280e-03   ,5.860707e-01   ,1.329199e-02   ,
   9.668684e+02   ,698            ,-2.058824e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   8              ,4.500000e+00   ,5.000000e+00   ,4.748772e+00   ,
   3.980379e-03   ,8.585519e-05   ,6.261662e-01   ,1.035586e-02   ,
   1.478275e-01   ,6.556844e-03   ,3.259178e-01   ,7.051404e-03   ,
   1.197783e-01   ,6.221934e-03   ,4.937693e-01   ,1.147549e-02   ,
   8.588271e+02   ,664            ,-2.058824e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   9              ,5.000000e+00   ,6.000000e+00   ,5.485021e+00   ,
   4.816396e-03   ,7.573630e-05   ,6.229713e-01   ,6.683736e-03   ,
   1.617520e-01   ,4.691559e-03   ,3.119935e-01   ,4.683906e-03   ,
   1.169748e-01   ,3.966667e-03   ,3.838645e-01   ,6.808288e-03   ,
   9.869156e+02   ,682            ,-2.058824e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,

   10             ,6.000000e+00   ,7.000000e+00   ,6.487538e+00   ,
   5.365397e-03   ,9.036675e-05   ,6.201891e-01   ,6.618823e-03   ,
   1.409617e-01   ,4.842918e-03   ,2.875382e-01   ,4.693030e-03   ,
   1.163057e-01   ,3.892732e-03   ,3.460461e-01   ,6.317521e-03   ,
   9.435802e+02   ,654            ,-2.058824e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   11             ,7.000000e+00   ,8.000000e+00   ,7.488922e+00   ,
   6.116321e-03   ,1.170942e-04   ,5.858170e-01   ,6.477358e-03   ,
   1.734706e-01   ,5.024916e-03   ,2.677166e-01   ,4.864705e-03   ,
   1.270404e-01   ,4.157720e-03   ,2.619810e-01   ,5.728837e-03   ,
   6.908224e+02   ,603            ,-1.941176e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   12             ,8.000000e+00   ,9.000000e+00   ,8.484242e+00   ,
   6.768263e-03   ,1.415670e-04   ,5.882322e-01   ,6.914846e-03   ,
   1.572134e-01   ,5.875581e-03   ,2.537722e-01   ,5.199722e-03   ,
   1.158174e-01   ,4.173218e-03   ,2.439457e-01   ,5.831483e-03   ,
   6.490916e+02   ,562            ,-1.901961e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.141593e+00   ,
   13             ,9.000000e+00   ,1.000000e+01   ,9.490493e+00   ,
   7.099848e-03   ,1.582032e-04   ,5.666121e-01   ,6.629324e-03   ,
   1.441161e-01   ,6.581072e-03   ,2.386430e-01   ,4.888772e-03   ,
   1.229241e-01   ,4.385375e-03   ,2.321237e-01   ,6.027100e-03   ,
   5.780956e+02   ,531            ,-1.894932e+00  ,1.000000e+00   ,
   0.000000e+00   ,3.073092e+00   ,
   14             ,1.000000e+01   ,1.200000e+01   ,1.094538e+01   ,
   8.419510e-03   ,1.411603e-04   ,5.638070e-01   ,4.858531e-03   ,
   1.354259e-01   ,5.740256e-03   ,2.300283e-01   ,3.597668e-03   ,
   1.151263e-01   ,2.912161e-03   ,2.006746e-01   ,4.244556e-03   ,
   6.238214e+02   ,537            ,-1.823529e+00  ,1.000000e+00   ,
   0.000000e+00   ,2.519136e+00   ,
   15             ,1.200000e+01   ,1.400000e+01   ,1.296376e+01   ,
   9.645510e-03   ,1.865771e-04   ,5.363169e-01   ,5.132377e-03   ,
   1.352788e-01   ,6.991510e-03   ,2.083973e-01   ,3.787467e-03   ,
   1.191812e-01   ,3.268510e-03   ,1.704213e-01   ,4.296495e-03   ,
   5.120439e+02   ,482            ,-1.666667e+00  ,1.000000e+00   ,
   0.000000e+00   ,2.173394e+00   ,
   16             ,1.400000e+01   ,1.600000e+01   ,1.495937e+01   ,
   1.107144e-02   ,2.471894e-04   ,5.068402e-01   ,6.194315e-03   ,
   1.502940e-01   ,7.017017e-03   ,1.893120e-01   ,4.667180e-03   ,
   1.253920e-01   ,3.881163e-03   ,1.406307e-01   ,3.951253e-03   ,
   4.824930e+02   ,440            ,-1.588235e+00  ,1.000000e+00   ,
   0.000000e+00   ,2.218533e+00   ,
   17             ,1.600000e+01   ,1.800000e+01   ,1.697287e+01   ,
   1.225710e-02   ,2.924686e-04   ,5.065162e-01   ,6.331831e-03   ,
   1.399045e-01   ,9.352681e-03   ,1.862162e-01   ,4.564539e-03   ,
   1.156445e-01   ,4.066520e-03   ,1.312882e-01   ,4.414139e-03   ,
   3.526221e+02   ,394            ,-1.509804e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.836781e+00   ,
   18             ,1.800000e+01   ,2.000000e+01   ,1.897992e+01   ,
   1.287650e-02   ,3.609497e-04   ,4.820583e-01   ,7.597040e-03   ,
   1.040178e-01   ,1.376587e-02   ,1.696342e-01   ,5.037630e-03   ,
   1.268144e-01   ,5.095409e-03   ,1.308740e-01   ,5.542313e-03   ,
   3.530666e+02   ,340            ,-1.485965e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.385997e+00   ,
   19             ,2.000000e+01   ,2.200000e+01   ,2.099429e+01   ,
   1.456718e-02   ,4.498553e-04   ,4.625879e-01   ,8.092847e-03   ,
   1.509370e-01   ,1.191265e-02   ,1.630032e-01   ,5.946550e-03   ,
   1.254522e-01   ,5.367492e-03   ,1.038067e-01   ,4.642840e-03   ,
   3.251687e+02   ,330            ,-1.431373e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.697354e+00   ,
   20             ,2.200000e+01   ,2.400000e+01   ,2.296795e+01   ,
   1.610199e-02   ,5.673224e-04   ,4.672533e-01   ,7.931797e-03   ,
   1.516253e-01   ,1.439297e-02   ,1.626095e-01   ,6.007905e-03   ,
   1.136039e-01   ,5.036429e-03   ,9.245841e-02   ,4.767239e-03   ,
   3.463977e+02   ,298            ,-1.431373e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.525175e+00   ,
   21             ,2.400000e+01   ,2.600000e+01   ,2.497236e+01   ,
   1.731681e-02   ,6.540773e-04   ,4.401659e-01   ,8.118745e-03   ,
   1.572056e-01   ,1.417860e-02   ,1.405252e-01   ,6.033721e-03   ,
   1.253874e-01   ,5.820455e-03   ,8.674449e-02   ,4.635796e-03   ,
   2.726155e+02   ,278            ,-1.274510e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.600468e+00   ,
   22             ,2.600000e+01   ,2.800000e+01   ,2.697255e+01   ,
   1.748432e-02   ,7.128846e-04   ,4.235863e-01   ,9.245287e-03   ,
   1.623025e-01   ,1.541844e-02   ,1.550182e-01   ,6.514018e-03   ,
   1.233560e-01   ,6.752148e-03   ,7.828278e-02   ,4.727803e-03   ,
   2.862859e+02   ,269            ,-1.431373e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.634330e+00   ,
   23             ,2.800000e+01   ,3.000000e+01   ,2.897303e+01   ,
   1.814483e-02   ,8.465432e-04   ,4.348632e-01   ,9.347258e-03   ,
   1.438423e-01   ,1.901855e-02   ,1.471399e-01   ,7.608651e-03   ,
   1.170591e-01   ,6.636807e-03   ,7.972661e-02   ,5.354835e-03   ,
   3.015774e+02   ,239            ,-1.352941e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.164406e+00   ,
   24             ,3.000000e+01   ,3.500000e+01   ,3.233948e+01   ,
   2.182663e-02   ,6.864097e-04   ,3.985282e-01   ,6.565409e-03   ,
   1.639892e-01   ,1.120096e-02   ,1.315799e-01   ,4.659574e-03   ,
   1.282556e-01   ,4.525298e-03   ,6.892334e-02   ,3.100087e-03   ,
   2.726335e+02   ,274            ,-1.279411e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.501496e+00   ,
   25             ,3.500000e+01   ,4.000000e+01   ,3.734241e+01   ,
   2.506254e-02   ,9.122889e-04   ,3.967463e-01   ,7.302150e-03   ,
   1.471138e-01   ,1.415299e-02   ,1.305037e-01   ,4.985281e-03   ,
   1.170207e-01   ,5.014084e-03   ,6.304262e-02   ,3.349271e-03   ,
   2.241877e+02   ,241            ,-1.271631e+00  ,1.000000e+00   ,
   0.000000e+00   ,9.817477e-01   ,
   26             ,4.000000e+01   ,4.500000e+01   ,4.238624e+01   ,
   2.730468e-02   ,1.282744e-03   ,3.694813e-01   ,8.265731e-03   ,
   1.630789e-01   ,1.646638e-02   ,1.216384e-01   ,6.277943e-03   ,
   1.259381e-01   ,6.506602e-03   ,5.447719e-02   ,3.657848e-03   ,
   1.896605e+02   ,220            ,-1.274510e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.167530e+00   ,
   27             ,4.500000e+01   ,5.000000e+01   ,4.742388e+01   ,
   2.970304e-02   ,1.495633e-03   ,3.483384e-01   ,9.848676e-03   ,
   1.785427e-01   ,2.233432e-02   ,1.066153e-01   ,6.323788e-03   ,
   1.310284e-01   ,7.542335e-03   ,4.755209e-02   ,3.902534e-03   ,
   1.970723e+02   ,189            ,-1.196078e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.426414e+00   ,
   28             ,5.000000e+01   ,6.000000e+01   ,5.449768e+01   ,
   3.420147e-02   ,1.495020e-03   ,3.340324e-01   ,7.825632e-03   ,
   1.809773e-01   ,1.474538e-02   ,1.098028e-01   ,5.239477e-03   ,
   1.314280e-01   ,5.998674e-03   ,4.245825e-02   ,2.665855e-03   ,
   1.452024e+02   ,187            ,-1.274510e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.403122e+00   ,
   29             ,6.000000e+01   ,7.000000e+01   ,6.426595e+01   ,
   3.798649e-02   ,2.272763e-03   ,2.913801e-01   ,9.943059e-03   ,
   1.559984e-01   ,2.612995e-02   ,7.628636e-02   ,6.631567e-03   ,
   1.370595e-01   ,7.531183e-03   ,4.386045e-02   ,4.347590e-03   ,
   1.285542e+02   ,149            ,-1.039216e+00  ,1.000000e+00   ,
   0.000000e+00   ,8.005524e-01   ,

   30             ,7.000000e+01   ,8.000000e+01   ,7.447521e+01   ,
   4.224801e-02   ,3.217583e-03   ,3.126790e-01   ,1.381210e-02   ,
   1.827541e-01   ,4.466394e-02   ,1.024236e-01   ,1.045707e-02   ,
   1.219186e-01   ,1.101414e-02   ,3.447117e-02   ,5.273899e-03   ,
   9.511345e+01   ,105            ,-1.274510e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.308805e+00   ,
   31             ,8.000000e+01   ,1.000000e+02   ,8.853231e+01   ,
   5.239400e-02   ,4.222262e-03   ,2.713293e-01   ,1.347480e-02   ,
   2.272559e-01   ,2.301687e-02   ,7.868005e-02   ,1.062842e-02   ,
   1.269960e-01   ,1.067763e-02   ,2.604078e-02   ,2.996508e-03   ,
   1.051510e+02   ,114            ,-1.039216e+00  ,1.000000e+00   ,
   0.000000e+00   ,1.924425e+00
 };
 // Initialize array of TF2 functions
 const Int_t npars=6;
 static Bool_t need_init=true;
#if !defined (__CINT__)  // || defined (__MAKECINT__)
 static TF2jan *func[nbins];
#else
 static TF2jan *func[32];
#endif
 if(need_init) {
   cout << "FlipARecoil_BIFURCATED6: Initializing "<<nbins<<" TF2 functions"<<endl;
   for(Int_t ibin=0; ibin<nbins; ibin++) {
     cout << "FlipARecoil_BIFURCATED6: Calculating integral for bin "<<ibin<<endl;
     stringstream s;
     s<<"bifurcated_2d_"<<ibin;
     func[ibin]=new TF2jan(s.str().c_str(), bifurcated2d_for_FlipARecoil_BIFURCATED6,
                        table[18+ibin*ncols], table[19+ibin*ncols],
                        table[20+ibin*ncols], table[21+ibin*ncols], npars);
     for(Int_t ipar=0; ipar<npars; ipar++) {
       func[ibin]->SetParameter(ipar, table[4+2*ipar+ibin*ncols]);
     }
     func[ibin]->SetNpx(300);
     func[ibin]->SetNpy(300);
     Double_t x,y; // dummy variables
     func[ibin]->GetRandom2(x,y); // force to calculate an integral
   }
   need_init=false;
   cout << "FlipARecoil_BIFURCATED6: Initialization done"<<endl;
 }
   
   // Find bin corresponding to truePT using exactly the same bin sizes as during the fit
   Int_t theBin=-1;
   if(truepT<table[1]) theBin=0;
   else if(truepT>=table[2+(nbins-1)*ncols]) theBin=nbins-1;
   else {
     // assume that there are no gaps between bins given in the table
     for(Int_t i=0;i<nbins;i++) if( truepT>=table[1+i*ncols] && truepT<table[2+i*ncols] ) {
       theBin=i;
       break;
     }
     
     if(theBin==-1) {
       // but if gaps exist, then pick the nearest bin in terms of its average PT
       theBin=0;
       Double_t dist=fabs(truepT-table[3+theBin*ncols]);
       Int_t i=0;
       while( i<nbins ) {
	 if( fabs(truepT-table[3+i*ncols])<dist ) {
	   dist=fabs(truepT-table[3+i*ncols]);
	   theBin=i;
	 }
       };
     }
 }
 /////////////////////////////// sanity check
 if(theBin<0 || theBin>=nbins) {
   std::cerr<<"FlipARecoil_BIFURCATED6: #### FATAL ERROR #### "<<endl
            <<"Look-up table bin="<<theBin
            <<" is outside [0,"<<nbins-1<<"] range for truePT="
            <<truepT<<" GeV !!!"<<std::endl<<std::endl;
   throw;
 }
 /////////////////////////////// sanity check

 Double_t thepTmean=-1;
 Double_t pt_resol, delta_phi;
 if(skip_Znunu_randomization) {

   // use external values for PT and PHI resolutions
   //
   pt_resol = pt_resol_external;
   delta_phi = delta_phi_external;

   // Get mean pT in this delta_phi bin:
   // NOTE: An extarnally supplied delta_phi can range from -2*Pi to +2*Pi
   // and we need |delta_phi| converted to [0, Pi[ range in order
   // to get the mean pT resolution corresponding to a given |delta_phi| slice.  
   //
   Double_t delta_phi_for_pTmean = kinem::delta_phi(0., delta_phi);
   //   cout << "SKIPPED_RND: pt_resol=" << pt_resol
   //        << ", delta_phi=" << delta_phi 
   //        << ", delta_phi_for_pTmean=" << delta_phi_for_pTmean << endl << flush;
   thepTmean=func[theBin]->getMeanInX(fabs(delta_phi_for_pTmean));
   //   cout << "SKIPPED_RND: thepTmean=" << thepTmean << endl << flush;

 } else {

   // pick a pair of random numbers following pdf
   // described by a TF2 function
   //
   Int_t iter=0;
   const Int_t maxiter=10;
   do {
     iter++;
     func[theBin]->GetRandom2(pt_resol, delta_phi);
     
     //    cout <<"RND(step1) iter="<<iter
     //         <<" truePT[GeV]/truePTbin/PTresolution/PHIresolution[rad]="
     //         <<truepT<<"/"<<theBin<<"/"<<pt_resol<<"/"<<delta_phi<<endl;
     
     // since func[] describes |dPHI| (not signed dPHI)
     // one has to pick a random sign for PHI smearing
     if(gRandom->Rndm()>0.5) delta_phi*=-1;
     
     //    cout <<"RND(step2) iter="<<iter
     //   <<" truePT[GeV]/truePTbin/PTresolution/PHIresolution[rad]="
     //   <<truepT<<"/"<<theBin<<"/"<<pt_resol<<"/"<<delta_phi<<endl;
     
   } while( (pt_resol>1.0 || fabs(delta_phi)>TMath::Pi()) &&
	    iter<maxiter );

   /////////////////////////////// sanity check
   if(iter>=maxiter) {
     std::cerr<<"FlipARecoil_BIFURCATED6: #### FATAL ERROR #### "<<endl
	      <<" Recoil PT and/or PHI resolution(s) outside allowed range after "
	      <<maxiter<<" iterations!!!"<<std::endl
	      <<" (truePT[GeV]/truePTbin/PTresolution/PHIresolution[rad]="
	      <<truepT<<"/"<<theBin<<"/"<<pt_resol<<"/"<<delta_phi<<") !!!"
	      <<std::endl<<std::endl;
     throw;
   }
   /////////////////////////////// sanity check
   
   // Get mean pT in this delta_phi bin
   //   cout << "NOT_SKIPPED_RND: pt_resol=" << pt_resol << ", delta_phi=" << delta_phi << endl << flush;
   thepTmean=func[theBin]->getMeanInX(fabs(delta_phi));
   //   cout << "NOT_SKIPPED_RND: thepTmean=" << thepTmean << endl << flush;
 }

 // smear PHI
 if(!skip_Znunu_fudging) {
   
   delta_phi*=(RelPhiA+RelPhiB/sqrt(truepT));
   if((RelPhiA+RelPhiB/sqrt(truepT))<0) delta_phi=0.;  //make sure fudging factor is always positive
   delta_phi+=PhiConst*gRandom->Gaus(0.,1.);

 }

 // make sure that the final PHI is within [0,2*Pi[ range
 smphi=truephi+delta_phi;
 while ((smphi>2*TMath::Pi())||(smphi<0)) {
   if(smphi>2*TMath::Pi()) smphi-=2*TMath::Pi();
   else if (smphi<0) smphi+=2*TMath::Pi();
 }

 if(!skip_Znunu_fudging) {
   
   // smear pT
   Double_t RelResn=1;
   Double_t RelResp=1;
   Double_t smpTErwartungswert=truepT*((1-thepTmean)*RelResp);
   Double_t smpTZittern=truepT*(-RelResn*(pt_resol-thepTmean));
   smpTZittern+=truepT*(1-thepTmean)*RelResp*RelConst*gRandom->Gaus(0.,1.);
   //
   Double_t spx_true = smpTErwartungswert * cos(delta_phi);
   Double_t spy_true = smpTErwartungswert * sin(delta_phi);
   Double_t smpTZittern_x_true=smpTZittern * cos(delta_phi);
   Double_t smpTZittern_y_true=smpTZittern * sin(delta_phi);
   RelResp=RelScale+RelOffset*exp(-truepT/RelTau);
   spx_true = RelResp*spx_true;
   RelResn=RelSampA+RelSampB/sqrt(truepT);
   spx_true+=RelResn*smpTZittern_x_true;
   spy_true+=smpTZittern_y_true;
   smpT = sqrt(spx_true*spx_true + spy_true*spy_true);

 } else {

   smpT = truepT*(1.0-pt_resol);
   if(smpT<0.0) smpT=0.0;

 }

 //  std::cout<<"Smeared: PT="<<smpT<<", PHI="<<smphi<<", theBin="<<theBin<<std::endl;
 return;
}

//=============================================================================
// FlipARecoil_BIFURCATED7
//=============================================================================
// This funtion is based on the parameterization obtained from Z->nu+nu
// events from full GEANT MC (600k events). Selected CC-CC events were stored
// in a text file by wmass_analysis (ZNuNuAnalysis processor).
// Cuts: Recoil reconstructed Ut<1000 GeV,
//       2 neutrinos of |eta|<1.3,
//       MC vertex |z|<60cm (true MC vertex was used for MET, Ut calculations).
// Function bifurcated2d_for_FlipARecoil_BIFURCATED7 contains analytical
// formula for 2D p.d.f. of Pt-resolution vs Phi-resolution in a given
// true Pt(Z) bin.
// Function FlipARecoil_BIFURCATED7 initialize TF2 functions for 32 variable
// size true Pt(Z) bins ranging from 0 to 100 GeV.
//
 inline Double_t wz_utils::bifurcated2d_for_FlipARecoil_BIFURCATED7(Double_t *x,
								    Double_t *par) {
   Double_t Xmean=par[1] + par[2]*x[1];
   Double_t Xrms=par[3];
   Double_t Ysigma=par[4]+par[5]*x[1];
   //
   // A standard log-normal distribution is defined as:
   // F(U) := exp( -0.5 * ( (log(U)-Mu)/Sigma )^2 )/(2*sqrt(Pi)*Sigma*U)
   // where:
   //      Mean = exp( Mu + 0.5*Sigma^2 )
   //  Variance = (Standard Deviation of U)^2
   //           = ( exp(Sigma^2) - 1 ) * exp( 2*Mu + Sigma^2 )
   //      Mode = (Most Probable value of U) = exp( Mu - Sigma^2 )
   // Let's define a new variable U:=1-x such that it is always greater than 0
   // for any x<1 (x = PT-resolution).
   // If x is log-normally distributed and MEAN and RMS denote mean of x and
   // standard deviation of x respectively then one can show that:
   //     Mu = log( (1-MEAN)^2 / sqrt( RMS^2 + (1-MEAN)^2 ))
   //  Sigma = sqrt( log( RMS^2 / (1-MEAN)^2 + 1 )).
   //
   Double_t Uoffset= pow(1+par[6],2); // always >=1
   Double_t U      = Uoffset - x[0];
   Double_t Umu    = TMath::Log( (Uoffset-Xmean)*(Uoffset-Xmean) /
				 sqrt( Xrms*Xrms +
				       (Uoffset-Xmean)*(Uoffset-Xmean) ) );
   Double_t Usigma = sqrt( TMath::Log( Xrms*Xrms/(Uoffset-Xmean)/
				       (Uoffset-Xmean) + 1 ) );
   Double_t Umode = exp( Umu - Usigma*Usigma ); // most probable value
   
   return par[0]*exp( -0.5*(pow( (TMath::Log(U)-Umu)/Usigma, 2)))/U/Usigma
     *( exp( -0.5*(pow( x[1]/Ysigma, 2))) );
 }
 
 
 inline void wz_utils::FlipARecoil_BIFURCATED7
   (double truepT,
    double truephi,
    double& smpT,
    double& smphi,
    double RelScale,
    double RelOffset,
    double RelTau,
    double RelSampA,
    double RelSampB,
    double RelConst,
    double RelRespTrans,
    double RelResnTrans,
    double RelTauTrans,
    double RelPhiA,
    double RelPhiB,
    double PhiConst,
    double pt_resol_external,  // effective only when skip_Znunu_randomization=TRUE
    double delta_phi_external, // effective only when skip_Znunu_randomization=TRUE
    bool skip_Znunu_randomization,
    bool skip_Znunu_fudging,
    int EtFlowFudge,
    double instlum) {

   //
   // Parameters of 2D probability distribution functions for
   // PT-resolution vs PHI-resolution for different true PT bins
   //
   const Int_t nbins=32;
   const Int_t ncols=24;
   // #if !defined (__CINT__)  // || defined (__MAKECINT__)
   static Double_t table[nbins*ncols]={
     // #else
     //  static Float_t table[32*24]={
     // #endif
     //
     // Bin          Min.PT[GeV]    Max.PT[GeV]     Ave.PT[GeV]
     // Normal.par.  E(Normal.par.) Mean.PT         E(Mean.PT)
     // Slope.PT     E(Slope.PT)    Sigma.PT        E(Sigma.PT)
     // Sigma.PHI    E(Sigma.PHI)   Slope.PHI       E(Slope.PHI)
     // Offset.PT    E(Offset.PT)   CHI**2          NDF
     // Min.PTres    Max.PTres      Min.PHIres[rad] Max.PHIres[rad]
     //
     0              ,0.000000e+00   ,7.500000e-01   ,4.950719e-01   ,
     9.585263e-03   ,8.170604e-04   ,-1.962466e+00  ,1.128456e-01   ,
     7.478415e-02   ,2.597828e-02   ,2.755637e+00   ,2.223750e-01   ,
     5.398324e-01   ,5.056420e-01   ,9.799682e-01   ,1.465018e-01   ,
     6.495555e-02   ,2.525221e-02   ,4.546715e+02   ,487            ,
     -2.000000e+01  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     1              ,7.500000e-01   ,1.500000e+00   ,1.159873e+00   ,
     6.764856e-03   ,1.687909e-04   ,-1.579544e-01  ,1.429329e-02   ,
     6.715803e-02   ,7.561292e-03   ,7.586584e-01   ,1.533809e-02   ,
     8.768804e-01   ,1.048726e-01   ,4.686787e-01   ,3.672028e-02   ,
     1.807563e-01   ,2.643204e-02   ,4.037456e+02   ,384            ,
     -2.000000e+01  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     2              ,1.500000e+00   ,2.000000e+00   ,1.756049e+00   ,
     4.839973e-03   ,1.120759e-04   ,1.755100e-01   ,9.016890e-03   ,
     7.811644e-02   ,5.039090e-03   ,4.949788e-01   ,9.187677e-03   ,
     7.905583e-01   ,6.270994e-02   ,3.494891e-01   ,2.313225e-02   ,
     1.257097e-01   ,1.356551e-02   ,3.625084e+02   ,375            ,
     -6.683842e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     3              ,2.000000e+00   ,2.500000e+00   ,2.253064e+00   ,
     4.286461e-03   ,8.945239e-05   ,2.991369e-01   ,7.480326e-03   ,
     9.034071e-02   ,6.506511e-03   ,4.141446e-01   ,7.531093e-03   ,
     6.418161e-01   ,3.657578e-02   ,3.232141e-01   ,1.472118e-02   ,
     1.394697e-01   ,2.128060e-02   ,4.716916e+02   ,409            ,
     -1.277698e+01  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     4              ,2.500000e+00   ,3.000000e+00   ,2.748663e+00   ,
     3.902494e-03   ,8.105991e-05   ,3.782116e-01   ,6.212647e-03   ,
     1.067391e-01   ,6.238653e-03   ,3.432283e-01   ,5.230229e-03   ,
     5.362357e-01   ,2.665750e-02   ,3.120650e-01   ,1.138709e-02   ,
     1.698815e-01   ,2.210678e-02   ,4.974625e+02   ,438            ,
     -8.257963e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     5              ,3.000000e+00   ,3.500000e+00   ,3.247742e+00   ,
     2.861174e-03   ,5.604330e-05   ,4.292743e-01   ,5.376332e-03   ,
     1.012744e-01   ,5.061087e-03   ,3.127897e-01   ,5.660301e-03   ,
     4.420084e-01   ,1.763747e-02   ,2.957534e-01   ,8.163675e-03   ,
     1.153045e-01   ,1.432195e-02   ,6.747653e+02   ,548            ,
     -9.511082e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     6              ,3.500000e+00   ,4.000000e+00   ,3.746168e+00   ,
     2.898943e-03   ,5.477631e-05   ,4.517165e-01   ,4.876164e-03   ,
     1.000036e-01   ,3.990608e-03   ,2.996414e-01   ,5.461741e-03   ,
     4.703359e-01   ,1.686207e-02   ,2.401317e-01   ,8.017025e-03   ,
     7.079608e-02   ,8.121601e-03   ,6.224071e+02   ,513            ,
     -2.814401e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     7              ,4.000000e+00   ,4.500000e+00   ,4.245657e+00   ,
     3.050930e-03   ,5.876268e-05   ,4.613564e-01   ,4.628843e-03   ,
     1.180597e-01   ,4.893264e-03   ,2.728791e-01   ,4.443957e-03   ,
     4.022768e-01   ,1.372899e-02   ,2.428489e-01   ,7.197922e-03   ,
     1.004481e-01   ,1.091873e-02   ,6.150798e+02   ,508            ,
     -2.968125e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     8              ,4.500000e+00   ,5.000000e+00   ,4.746933e+00   ,
     3.582075e-03   ,7.068231e-05   ,4.769410e-01   ,4.622137e-03   ,
     1.128458e-01   ,4.552709e-03   ,2.654560e-01   ,4.772004e-03   ,
     3.781346e-01   ,1.242838e-02   ,2.139411e-01   ,7.092046e-03   ,
     6.634070e-02   ,8.277624e-03   ,5.762697e+02   ,434            ,
     -1.835146e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     9              ,5.000000e+00   ,6.000000e+00   ,5.481076e+00   ,
     1.643171e-03   ,2.394288e-05   ,4.785722e-01   ,3.300845e-03   ,
     1.289797e-01   ,4.353860e-03   ,2.519935e-01   ,3.226233e-03   ,
     3.153084e-01   ,7.687984e-03   ,2.045784e-01   ,5.406209e-03   ,
     8.819286e-02   ,7.508894e-03   ,1.039982e+03   ,969            ,
     -3.410626e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     10             ,6.000000e+00   ,7.000000e+00   ,6.486215e+00   ,
     2.181845e-03   ,3.443308e-05   ,4.788093e-01   ,3.322291e-03   ,
     1.456459e-01   ,5.604534e-03   ,2.280875e-01   ,2.675745e-03   ,
     2.986274e-01   ,7.969249e-03   ,1.828218e-01   ,6.475558e-03   ,
     1.145336e-01   ,1.013819e-02   ,6.738712e+02   ,727            ,
     -1.581270e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     11             ,7.000000e+00   ,8.000000e+00   ,7.487105e+00   ,
     2.321378e-03   ,4.054510e-05   ,4.724136e-01   ,3.444282e-03   ,
     1.659442e-01   ,7.622356e-03   ,2.137232e-01   ,2.565508e-03   ,
     2.488332e-01   ,7.717377e-03   ,1.801356e-01   ,7.776696e-03   ,
     1.404980e-01   ,1.416611e-02   ,6.031632e+02   ,653            ,
     -1.286046e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     12             ,8.000000e+00   ,9.000000e+00   ,8.482749e+00   ,
     2.390502e-03   ,4.636811e-05   ,4.738480e-01   ,3.637322e-03   ,
     1.590645e-01   ,9.507985e-03   ,1.988855e-01   ,2.542107e-03   ,
     2.480237e-01   ,9.347772e-03   ,1.409702e-01   ,1.113288e-02   ,
     1.574247e-01   ,1.862087e-02   ,5.569368e+02   ,577            ,
     -1.688700e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     13             ,9.000000e+00   ,1.000000e+01   ,9.490234e+00   ,
     2.882532e-03   ,5.934254e-05   ,4.718800e-01   ,4.032682e-03   ,
     1.393535e-01   ,1.237004e-02   ,1.921410e-01   ,2.368977e-03   ,
     2.194387e-01   ,8.093925e-03   ,1.535674e-01   ,1.022673e-02   ,
     2.081941e-01   ,2.760679e-02   ,4.830874e+02   ,473            ,
     -8.094171e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     14             ,1.000000e+01   ,1.200000e+01   ,1.094498e+01   ,
     1.845782e-03   ,2.905177e-05   ,4.631446e-01   ,2.884138e-03   ,
     1.567489e-01   ,1.034466e-02   ,1.823230e-01   ,1.852153e-03   ,
     2.096966e-01   ,6.044558e-03   ,1.178366e-01   ,8.910844e-03   ,
     1.490106e-01   ,1.682716e-02   ,6.283760e+02   ,683            ,
     -1.682599e+00  ,1.000000e+00   ,0.000000e+00   ,3.066766e+00   ,
     15             ,1.200000e+01   ,1.400000e+01   ,1.296392e+01   ,
     1.733225e-03   ,3.137981e-05   ,4.573974e-01   ,3.194997e-03   ,
     1.637735e-01   ,1.428932e-02   ,1.673826e-01   ,1.843893e-03   ,
     1.745956e-01   ,6.412656e-03   ,1.141917e-01   ,1.231001e-02   ,
     1.948935e-01   ,2.941964e-02   ,6.558453e+02   ,655            ,
     -1.081362e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     16             ,1.400000e+01   ,1.600000e+01   ,1.495906e+01   ,
     2.458072e-03   ,5.053009e-05   ,4.437971e-01   ,3.301815e-03   ,
     1.976880e-01   ,1.614777e-02   ,1.619288e-01   ,2.027468e-03   ,
     1.436989e-01   ,5.468139e-03   ,1.400597e-01   ,1.103829e-02   ,
     2.292166e-01   ,3.972717e-02   ,4.575179e+02   ,485            ,
     -1.008459e+00  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     17             ,1.600000e+01   ,1.800000e+01   ,1.697241e+01   ,
     2.793347e-03   ,6.240248e-05   ,4.412885e-01   ,3.583220e-03   ,
     1.572612e-01   ,1.982007e-02   ,1.539076e-01   ,1.947982e-03   ,
     1.348814e-01   ,5.781111e-03   ,1.278350e-01   ,1.337197e-02   ,
     1.816633e-01   ,3.787939e-02   ,3.854198e+02   ,400            ,
     -6.532511e-01  ,1.000000e+00   ,0.000000e+00   ,3.141593e+00   ,
     18             ,1.800000e+01   ,2.000000e+01   ,1.898002e+01   ,
     3.773526e-03   ,9.452761e-05   ,4.365590e-01   ,3.865382e-03   ,
     1.646895e-01   ,2.544805e-02   ,1.482798e-01   ,1.914110e-03   ,
     1.249488e-01   ,6.383048e-03   ,1.140728e-01   ,1.697792e-02   ,
     4.078657e-01   ,9.625525e-02   ,3.174830e+02   ,292            ,
     -4.188887e-01  ,1.000000e+00   ,0.000000e+00   ,3.097497e+00   ,
     19             ,2.000000e+01   ,2.200000e+01   ,2.099448e+01   ,
     3.937806e-03   ,1.082211e-04   ,4.227067e-01   ,4.139872e-03   ,
     2.227836e-01   ,2.993874e-02   ,1.442185e-01   ,2.141518e-03   ,
     1.121925e-01   ,5.821048e-03   ,1.292745e-01   ,1.574258e-02   ,
     4.273208e-01   ,1.210494e-01   ,2.673927e+02   ,278            ,
     -3.985880e-01  ,1.000000e+00   ,0.000000e+00   ,2.716672e+00   ,
     20             ,2.200000e+01   ,2.400000e+01   ,2.296710e+01   ,
     4.830214e-03   ,1.427371e-04   ,4.272816e-01   ,4.234230e-03   ,
     1.477113e-01   ,3.079027e-02   ,1.417957e-01   ,2.310987e-03   ,
     1.011289e-01   ,5.362722e-03   ,1.354487e-01   ,1.548028e-02   ,
     3.144945e-01   ,8.982086e-02   ,1.804919e+02   ,226            ,
     -3.203520e-01  ,1.000000e+00   ,0.000000e+00   ,2.246391e+00   ,
     21             ,2.400000e+01   ,2.600000e+01   ,2.497092e+01   ,
     5.511291e-03   ,1.783433e-04   ,4.197939e-01   ,4.647511e-03   ,
     1.710462e-01   ,3.733492e-02   ,1.374589e-01   ,2.368533e-03   ,
     9.180863e-02   ,5.398109e-03   ,1.428065e-01   ,1.694396e-02   ,
     4.857780e-01   ,1.684590e-01   ,1.409854e+02   ,195            ,
     -2.869819e-01  ,1.000000e+00   ,0.000000e+00   ,3.066975e+00   ,
     22             ,2.600000e+01   ,2.800000e+01   ,2.697386e+01   ,
     6.450463e-03   ,2.546291e-04   ,3.909939e-01   ,5.260625e-03   ,
     2.346389e-01   ,4.095829e-02   ,1.439972e-01   ,2.959081e-03   ,
     7.666284e-02   ,6.007641e-03   ,1.786770e-01   ,2.014469e-02   ,
     3.328315e-01   ,1.224821e-01   ,1.477559e+02   ,169            ,
     -1.665737e-01  ,1.000000e+00   ,0.000000e+00   ,2.043384e+00   ,
     23             ,2.800000e+01   ,3.000000e+01   ,2.897046e+01   ,
     6.156882e-03   ,2.409458e-04   ,3.952389e-01   ,5.993600e-03   ,
     2.163105e-01   ,5.865214e-02   ,1.396207e-01   ,2.982446e-03   ,
     8.528913e-02   ,6.519797e-03   ,1.326744e-01   ,2.323232e-02   ,
     4.289136e-01   ,1.737654e-01   ,1.490080e+02   ,154            ,
     -3.052354e-01  ,1.000000e+00   ,0.000000e+00   ,1.736249e+00   ,
     24             ,3.000000e+01   ,3.500000e+01   ,3.234099e+01   ,
     3.726736e-03   ,1.031551e-04   ,3.915095e-01   ,3.670470e-03   ,
     1.646169e-01   ,3.512892e-02   ,1.302108e-01   ,2.005618e-03   ,
     6.979676e-02   ,3.520558e-03   ,1.631230e-01   ,1.370112e-02   ,
     1.007487e+00   ,7.001931e-01   ,2.563680e+02   ,271            ,
     -3.393199e-01  ,1.000000e+00   ,0.000000e+00   ,2.010822e+00   ,
     25             ,3.500000e+01   ,4.000000e+01   ,3.734442e+01   ,
     4.524085e-03   ,1.488915e-04   ,3.907241e-01   ,4.381462e-03   ,
     7.179414e-02   ,5.801485e-02   ,1.262044e-01   ,2.042928e-03   ,
     6.300389e-02   ,4.022367e-03   ,1.461493e-01   ,1.881208e-02   ,
     1.925430e+00   ,2.120754e+00   ,2.179860e+02   ,228            ,
     -2.286734e-01  ,1.000000e+00   ,0.000000e+00   ,1.041883e+00   ,
     26             ,4.000000e+01   ,4.500000e+01   ,4.238693e+01   ,
     5.372322e-03   ,2.252222e-04   ,3.696326e-01   ,4.999825e-03   ,
     2.006829e-01   ,6.170845e-02   ,1.216455e-01   ,2.814609e-03   ,
     5.169079e-02   ,3.986639e-03   ,1.820198e-01   ,1.893946e-02   ,
     1.994479e+00   ,3.050035e+00   ,1.898382e+02   ,184            ,
     -5.965324e-01  ,1.000000e+00   ,0.000000e+00   ,8.990717e-01   ,     
     27             ,4.500000e+01   ,5.000000e+01   ,4.742476e+01   ,
     8.035815e-03   ,4.741207e-04   ,3.667236e-01   ,5.946167e-03   ,
     1.252454e-01   ,8.233578e-02   ,1.188824e-01   ,6.303805e-04   ,
     5.267168e-02   ,6.221030e-03   ,1.543979e-01   ,3.136877e-02   ,
     4.777978e+02   ,6.377934e+03   ,1.236247e+02   ,131            ,
     -2.125039e-01  ,1.000000e+00   ,0.000000e+00   ,1.634343e+00   ,
     28             ,5.000000e+01   ,6.000000e+01   ,5.449250e+01   ,
     5.990497e-03   ,2.946837e-04   ,3.431122e-01   ,5.000484e-03   ,
     3.123617e-01   ,7.168615e-02   ,1.207600e-01   ,5.648147e-04   ,
     4.008856e-02   ,3.781347e-03   ,1.994324e-01   ,2.175587e-02   ,
     4.296767e+02   ,5.937230e+02   ,1.201917e+02   ,175            ,
     -1.353384e-01  ,1.000000e+00   ,0.000000e+00   ,1.115518e+00   ,
     29             ,6.000000e+01   ,7.000000e+01   ,6.426508e+01   ,
     2.292648e-03   ,1.321299e-04   ,3.402203e-01   ,5.966827e-03   ,
     1.097549e-02   ,1.079652e-01   ,1.093425e-01   ,3.648003e-03   ,
     3.622874e-02   ,4.392854e-03   ,2.302989e-01   ,3.015959e-02   ,
     5.946444e+02   ,4.326007e+01   ,1.712299e+02   ,228            ,
     -8.851916e-02  ,1.000000e+00   ,0.000000e+00   ,4.348785e-01   ,
     30             ,7.000000e+01   ,8.000000e+01   ,7.447777e+01   ,
     3.889409e-03   ,2.597071e-04   ,3.394146e-01   ,8.018307e-03   ,
     -1.128626e-01  ,1.813749e-01   ,1.123648e-01   ,1.532809e-03   ,
     3.758295e-02   ,5.877359e-03   ,1.798592e-01   ,5.030334e-02   ,
     4.433245e+02   ,1.157956e+03   ,8.112698e+01   ,130            ,
     -1.325927e-01  ,1.000000e+00   ,0.000000e+00   ,6.265599e-01   ,
     31             ,8.000000e+01   ,1.000000e+02   ,8.853222e+01   ,
     4.648702e-03   ,1.142354e-04   ,3.139458e-01   ,4.526500e-03   ,
     5.361989e-02   ,1.155797e-01   ,1.117493e-01   ,4.887457e-02   ,
     2.057378e-02   ,7.502494e-04   ,2.761300e-01   ,1.101810e-02   ,
     5.390242e+02   ,9.481325e+03   ,1.108784e+02   ,148            ,
     -1.278531e-01  ,1.000000e+00   ,0.000000e+00   ,5.924760e-01
   };
   
   // Initialize array of TF2 functions
   const Int_t npars=7;
   static Bool_t need_init=true;
   // #if !defined (__CINT__)  // || defined (__MAKECINT__)
   static TF2jan *func[nbins];
   // #else
   //  static TF2jan *func[32];
   // #endif
   if(need_init) {
     cout << "FlipARecoil_BIFURCATED7: Initializing "<<nbins<<" TF2 functions"<<endl;
     for(Int_t ibin=0; ibin<nbins; ibin++) {
       cout << "FlipARecoil_BIFURCATED7: Calculating integral for bin "<<ibin<<endl;
       stringstream s;
       s<<"bifurcated_2d_"<<ibin;
       func[ibin]=new TF2jan(s.str().c_str(), bifurcated2d_for_FlipARecoil_BIFURCATED7,
			     table[20+ibin*ncols], table[21+ibin*ncols],
			     table[22+ibin*ncols], table[23+ibin*ncols], npars);
       for(Int_t ipar=0; ipar<npars; ipar++) {
	 func[ibin]->SetParameter(ipar, table[4+2*ipar+ibin*ncols]);
       }
       func[ibin]->SetNpx(300);
       func[ibin]->SetNpy(300);
       Double_t x,y; // dummy variables
       func[ibin]->GetRandom2(x,y); // force to calculate an integral
     }
     need_init=false;
     cout << "FlipARecoil_BIFURCATED7: Initialization done"<<endl;
   }
   
   // Find bin corresponding to truePT using exactly the same bin sizes as during the fit
   Int_t theBin=-1;
   if(truepT<table[1]) theBin=0;
   else if(truepT>=table[2+(nbins-1)*ncols]) theBin=nbins-1;
   else {
     // assume that there are no gaps between bins given in the table
     for(Int_t i=0;i<nbins;i++) if( truepT>=table[1+i*ncols] && truepT<table[2+i*ncols] ) {
       theBin=i;
       break;
     }
     
     if(theBin==-1) {
       // but if gaps exist, then pick the nearest bin in terms of its average PT
       theBin=0;
       Double_t dist=fabs(truepT-table[3+theBin*ncols]);
       Int_t i=0;
       while( i<nbins ) {
         if( fabs(truepT-table[3+i*ncols])<dist ) {
           dist=fabs(truepT-table[3+i*ncols]);
           theBin=i;
         }
       };
     }
   }
   
   //sanity check
   if(theBin<0 || theBin>=nbins) {
     std::cerr<<"FlipARecoil_BIFURCATED7: #### FATAL ERROR #### "<<endl
	      <<"Look-up table bin="<<theBin
	      <<" is outside [0,"<<nbins-1<<"] range for truePT="
	      <<truepT<<" GeV !!!"<<std::endl<<std::endl;
     throw;
   }
   
   //sanity check       
   Double_t thepTmean=-1;
   Double_t pt_resol, delta_phi;
   if(skip_Znunu_randomization) {
     
     // use external values for PT and PHI resolutions
     //
     pt_resol = pt_resol_external;
     delta_phi = delta_phi_external;
     
     // Get mean pT in this delta_phi bin:
     // NOTE: An extarnally supplied delta_phi can range from -2*Pi to +2*Pi
     // and we need |delta_phi| converted to [0, Pi[ range in order
     // to get the mean pT resolution corresponding to a given |delta_phi| slice.
     //
     Double_t delta_phi_for_pTmean = kinem::delta_phi(0., delta_phi);
     //        cout << "SKIPPED_RND: pt_resol=" << pt_resol
     //             << ", delta_phi=" << delta_phi
     //             << ", delta_phi_for_pTmean=" << delta_phi_for_pTmean << endl << flush;
     thepTmean=func[theBin]->getMeanInX(fabs(delta_phi_for_pTmean));
     //       cout << "SKIPPED_RND: thepTmean=" << thepTmean << endl << flush;
     
   } else {
     
     // pick a pair of random numbers following pdf
     // described by a TF2 function
     //
     Int_t iter=0;
     const Int_t maxiter=10;
     do {
       iter++;
       func[theBin]->GetRandom2(pt_resol, delta_phi);
       
       //           cout <<"RND(step1) iter="<<iter
       //                <<" truePT[GeV]/truePTbin/PTresolution/PHIresolution[rad]="
       //                <<truepT<<"/"<<theBin<<"/"<<pt_resol<<"/"<<delta_phi<<endl;
       
       // since func[] describes |dPHI| (not signed dPHI)
       // one has to pick a random sign for PHI smearing
       if(gRandom->Rndm()>0.5) delta_phi*=-1;
       
       //           cout <<"RND(step2) iter="<<iter
       //          <<" truePT[GeV]/truePTbin/PTresolution/PHIresolution[rad]="
       //          <<truepT<<"/"<<theBin<<"/"<<pt_resol<<"/"<<delta_phi<<endl;
       
     } while( (pt_resol>1.0 || fabs(delta_phi)>TMath::Pi()) &&
	      iter<maxiter );
     
     // sanity check
     if(iter>=maxiter) {
       std::cerr<<"FlipARecoil_BIFURCATED7: #### FATAL ERROR #### "<<endl
		<<" Recoil PT and/or PHI resolution(s) outside allowed range after "
		<<maxiter<<" iterations!!!"<<std::endl
		<<" (truePT[GeV]/truePTbin/PTresolution/PHIresolution[rad]="
		<<truepT<<"/"<<theBin<<"/"<<pt_resol<<"/"<<delta_phi<<") !!!"
		<<std::endl<<std::endl;
       throw;
     }
    
     // sanity check
     // Get mean pT in this delta_phi bin
     //        cout << "NOT_SKIPPED_RND: pt_resol=" << pt_resol << ", delta_phi=" << delta_phi << endl << flush;
     //      thepTmean=func[theBin]->getMeanInX(fabs(delta_phi));
     //        cout << "NOT_SKIPPED_RND: thepTmean=" << thepTmean << endl << flush;
   }
   
   // smear PHI
   if(!skip_Znunu_fudging) {

     //make sure fudging factor is always positive
     delta_phi*=maxim(0.0, (RelPhiA+RelPhiB/sqrt(truepT)));
     if(PhiConst) delta_phi+=PhiConst*gRandom->Gaus(0.,1.);

   }
   
   // make sure that the final PHI is within [0,2*Pi[ range
   smphi=truephi+delta_phi;
   while ((smphi>2*TMath::Pi())||(smphi<0)) {
     if(smphi>2*TMath::Pi()) smphi-=2*TMath::Pi();
     else if (smphi<0) smphi+=2*TMath::Pi();
   }
   
   if(!skip_Znunu_fudging) {
     
     // smear pT
     Double_t RelResn=1;
     Double_t RelResp=1;
     Double_t smpTErwartungswert=truepT*((1-thepTmean)*RelResp);
     Double_t smpTZittern=truepT*(-RelResn*(pt_resol-thepTmean));
     if(RelConst) smpTZittern+=truepT*(1-thepTmean)*RelResp*RelConst*gRandom->Gaus(0.,1.);

     Double_t spx_true = smpTErwartungswert * cos(delta_phi);
     Double_t spy_true = smpTErwartungswert * sin(delta_phi);
     Double_t smpTZittern_x_true=smpTZittern * cos(delta_phi);
     Double_t smpTZittern_y_true=smpTZittern * sin(delta_phi);

     if (EtFlowFudge) {
       if (EtFlowFudge==400) {
         if ((truepT>12)&&(instlum<2)&&(smphi>3.140)&&(smphi<5.495)) {
           RelResp*=1.07;
         }
       } else if (EtFlowFudge==1) {
	 // This is from the data/MC ratio in Z -> e e
	 Double_t theFudge[6] = {
	   2.23337e+00,
	   1.02567e+00,
	   2.37743e+00,
	   -1.29922e+00,
	   1.58845e+02,
	   -5.70017e-03};   
	 RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT);
       } else if (EtFlowFudge==2) {
	 // This is from the data/Znunu(IIa) ratio
         Double_t theFudge[6] = {
	   -1.27258e+00,
           8.22150e-01,
	   2.34385e+00,
	   2.36753e+00,
	   2.20601e+02,
	   8.43940e-03};
         RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT);
       } else if (EtFlowFudge==3) {
	 // This is from the data/Znunu(IIa) ratio - LumLT2
	 Double_t theFudge[6] = {
           8.25295e-01,
	   2.63597e+00,
	   1.50697e+00,
	   4.07919e-01,
	   1.85510e+01,
           3.27947e-03};
         RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT);
       } else if (EtFlowFudge==4) {
	 // This is from the data/Znunu(IIa) ratio - LumLT4GT2
	 Double_t theFudge[6] = {
	   -3.76932e-01,
	   7.21719e-01,
	   1.98287e+00,
	   1.50225e+00,
	   1.38448e+02,
	   7.45620e-03};
         RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT);
       } else if (EtFlowFudge==5) {
	 // This is from the data/Znunu(IIa) ratio - LumLT6GT4
	 Double_t theFudge[6] = {
           1.12254e+00,
           1.68501e+01,
           4.28139e+00,
	   -1.59869e+01,
           4.45019e+00,
	   -2.09876e-03};
         RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT);
       } else if (EtFlowFudge==6) {
	 // This is from the data/Znunu(IIa) ratio - LumGT6
	 Double_t theFudge[6] = {
           1.21529e+00,
	   1.61516e+01,
	   4.81673e+00,
	   -1.51775e+01,
           5.18899e+00,
	   -2.06743e-03};
         RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT);
       } else if (EtFlowFudge==7) {
	 // This is from the Zee(FullMC)/Znunu(IIb) ratio - All
	 Double_t theFudge[6] = {
           1.24318e+00,
           4.91889e+00,
           5.20096e+00,
           5.08244e+01,
           1.37849e+00,
	   -2.84578e-03};
         RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT);
       } else if (EtFlowFudge==8) {
	 // This is from the Zee(FullMC)/Znunu(IIb) ratio - LumiLT2
	 Double_t theFudge[] = {
	   1.12885e+00,
	   -6.97601e-01,
	   2.29148e-01,
	   -4.31251e-01,
	   2.33743e-01,
	   -1.23653e-02,
	   5.06661e-04,
	   -7.73334e-06,
	   3.94031e-08};
         RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT+theFudge[6]*truepT*truepT+theFudge[7]*truepT*truepT*truepT+theFudge[8]*truepT*truepT*truepT*truepT);
       } else if (EtFlowFudge==9) {
	 // This is from the Zee(FullMC)/Znunu(IIb) ratio - LumiLT4GT2
	 Double_t theFudge[] = {
	   1.14318e+00,
	   -6.98617e-01,
	   5.96958e-02,
	   -4.44581e-01,
	   1.69049e-02,
	   -1.44079e-02,
	   6.76252e-04,
	   -1.28289e-05,
	   8.15702e-08};
         RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT+theFudge[6]*truepT*truepT+theFudge[7]*truepT*truepT*truepT+theFudge[8]*truepT*truepT*truepT*truepT);
       } else if (EtFlowFudge==10) {
	 // This is from the Zee(FullMC)/Znunu(IIb) ratio - LumiLT6GT4
	 Double_t theFudge[] = {
	   1.16102e+00,
	   -5.83328e-01,
	   2.21053e-02,
	   -5.77446e-01,
	   1.38715e-02,
	   -1.86320e-02,
	   9.86588e-04,
	   -2.01171e-05,
	   1.33204e-07};
         RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT+theFudge[6]*truepT*truepT+theFudge[7]*truepT*truepT*truepT+theFudge[8]*truepT*truepT*truepT*truepT);
       } else if (EtFlowFudge==11) {
	 // This is from the Zee(FullMC)/Znunu(IIb) ratio - LumiGT6
	 Double_t theFudge[] = {
	   1.16106e+00,
	   -5.80530e-01,
	   7.02668e-03,
	   -5.80530e-01,
	   7.02668e-03,
	   -1.85141e-02,
	   9.15778e-04,
	   -1.76184e-05,
	   1.13654e-07};
         RelResp*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT+theFudge[6]*truepT*truepT+theFudge[7]*truepT*truepT*truepT+theFudge[8]*truepT*truepT*truepT*truepT);
       } else if (EtFlowFudge==200) {
	 RelResp*=(1+0.10*cos(truephi-5.5));
       } else if (EtFlowFudge==201) {
	 if ((truepT>12)&&(smphi>2.355)&&(smphi<4.710)) {
	   RelResp*=1.06;
	 }
       } else if (EtFlowFudge==301) {
         if (truepT>12) {
	   RelResp*=1.01;
         }
       } else if (EtFlowFudge==302) {
         if (truepT>12) {
           RelResp*=1.02;
         }
       } else if (EtFlowFudge==303) {
         if (truepT>12) {
           RelResp*=1.03;
         }
       } else if (EtFlowFudge==304) {
         if (truepT>12) {
           RelResp*=1.04;
         }
       } else if (EtFlowFudge==305) {
         if (truepT>12) {
           RelResp*=1.05;
         }
       } else if (EtFlowFudge==306) {
         if (truepT>12) {
           RelResp*=1.06;
         }
       } else if (EtFlowFudge==307) {
         if (truepT>12) {
           RelResp*=1.07;
         }
       } else if (EtFlowFudge==308) {
         if (truepT>12) {
           RelResp*=1.08;
         }
       } else if (EtFlowFudge==309) {
         if (truepT>12) {
           RelResp*=1.09;
         }
       } else if (EtFlowFudge==310) {
         if (truepT>12) {
           RelResp*=0.99;
         }
       } else if (EtFlowFudge==311) {
         if (truepT>12) {
           RelResp*=0.98;
         }
       } else if (EtFlowFudge==312) {
         if (truepT>12) {
           RelResp*=0.97;
         }
       } else if (EtFlowFudge==313) {
         if (truepT>12) {
           RelResp*=0.96;
         }
       } else if (EtFlowFudge==314) {
         if (truepT>12) {
           RelResp*=0.95;
         }
       } else if (EtFlowFudge==315) {
         if (truepT>12) {
           RelResp*=0.94;
         }
       } else if (EtFlowFudge==316) {
         if (truepT>12) {
           RelResp*=0.93;
         }
       } else if (EtFlowFudge==317) {
         if (truepT>12) {
           RelResp*=0.92;
         }
       } else if (EtFlowFudge==318) {
         if (truepT>12) {
           RelResp*=0.91;
         }
       } else if (EtFlowFudge==319) {
         if (truepT>12) {
           RelResp*=0.90;
         }
       }
     }

     RelResp*=(RelScale+RelOffset*exp(-truepT/RelTau));
     spx_true = RelResp*spx_true;
     if (RelRespTrans>0) spy_true = RelRespTrans*spy_true;
     else if (RelRespTrans<-10) spy_true = (1-(RelRespTrans+10)*exp(-truepT/(RelTauTrans*RelTau)))*spy_true;
     else spy_true = (1+RelRespTrans*exp(-truepT/(RelTauTrans*RelTau)))*spy_true;
     RelResn=RelSampA+RelSampB/sqrt(truepT);

     spx_true+=RelResn*smpTZittern_x_true;
     spy_true+=RelResnTrans*smpTZittern_y_true;
     smpT = sqrt(spx_true*spx_true + spy_true*spy_true);
     
   } else {     
     smpT = maxim(0.0, truepT*(1.0-pt_resol));
   }
   //     std::cout<<"Smeared: PT="<<smpT<<", PHI="<<smphi<<", theBin="<<theBin<<std::endl;
   return;
 }

 // Scalar Et model for hard component only modelled using 1-dimensional RooPdfKeys technique.
 // For details see W-mass talk by Mikolaj on Sep 27, 2007
 inline void wz_utils::ScalarEt_ver1(double true_PT,
				     double recoil_UT,
				     double& scalar_ET,
				     double& scalar_ET_expectation,
				     const char *fname) {

   static Bool_t need_init=true;
   static double average_true_PT[1000];
   static int nbins_PT=0, nbins_UT=0;
   static double bins_PT[1000], bins_UT[1000];
   static TH1D *pdf_x[1000][1000];
   static TFile *f;
   
   // Initialize P.D.F. histograms of x:=(Recoil Ut)/(Recoil SET)
   // variable for different UT and PT bins
   if(need_init) {
     cout << "ScalarEt: Initializing p.d.f. histograms from "<<fname<<" ROOT file"<<endl;
     f=new TFile(fname, "OLD");
     if(!f) {
       cerr << "ScalarEt: Can't open file: "<<fname<<" !!!"<<endl;
       throw;
     }
     f->cd();
     
     // Profile histogram: <PT(true)> vs PT(true)
     TH1D *hist_PT=(TH1D*)f->Get("h_AveRecoilPt_V_RecoilPt_FULL_ALL");
     if(hist_PT==NULL || hist_PT->GetNbinsX()==0 || hist_PT->GetNbinsX()>999 ) {
       cerr << "ScalarEt: Can't get histogram with PT bins from file: "<<fname<<" !!!"<<endl;
       throw;
     }
     
     nbins_PT=hist_PT->GetNbinsX();
     for(int ipt=0; ipt<nbins_PT; ipt++) {
       average_true_PT[ipt]=hist_PT->GetBinContent(ipt+1);
       bins_PT[ipt]=hist_PT->GetBinLowEdge(ipt+1);
       cout << "ScalarEt: PT bins ipt="<<ipt<<", <PT>="<<average_true_PT[ipt]<<" GeV"<<endl;
     }
     bins_PT[nbins_PT]=hist_PT->GetBinLowEdge(nbins_PT)+hist_PT->GetBinWidth(nbins_PT);
     cout <<  "ScalarEt: Using "<<nbins_PT<<" PT bins"<<endl;
     
     // 1D histogram: Recoil UT distribution (integrated over all PT bins)
     TH1D *hist_UT=(TH1D*)f->Get("h_RecoilUt_FULL_ALL");
     if(hist_UT==NULL || hist_UT->GetNbinsX()==0 || hist_UT->GetNbinsX()>999 ) {
       cerr << "ScalarEt: Can't get histogram with UT bins from file: "<<fname<<" !!!"<<endl;
       throw;
     }
     nbins_UT=hist_UT->GetNbinsX();
     for(int iut=0; iut<nbins_UT; iut++) {
       bins_UT[iut]=hist_UT->GetBinLowEdge(iut+1);
     }
     bins_UT[nbins_UT]=hist_UT->GetBinLowEdge(nbins_UT)+hist_UT->GetBinWidth(nbins_UT);
     cout <<  "ScalarEt: Using "<<nbins_UT<<" UT bins"<<endl;
     
     // now read the histograms with p.d.f's of
     // x:=(Recoil Ut)/(Recoil SET) variable
     for(int ipt=0; ipt<nbins_PT; ipt++) {
       for(int iut=0; iut<nbins_UT; iut++) {
	 stringstream hname;
	 hname<<"hist_PTbin"<<ipt<<"_UTbin"<<iut;
	 TH1D *hist_PDF=(TH1D*)f->Get(hname.str().c_str());
	 if(hist_PDF==NULL) {
	   pdf_x[ipt][iut]=NULL;
	   //      cerr << "ScalarEt: P.D.F. histogram "<<hname.str()<<" is empty"<<endl;
	 } else {
	   pdf_x[ipt][iut]=new TH1D(*hist_PDF);
	   stringstream pdf_x_name;
	   pdf_x_name<<pdf_x[ipt][iut]->GetName()<<"_copy";
	   pdf_x[ipt][iut]->SetName(pdf_x_name.str().c_str());
	   Double_t integral=pdf_x[ipt][iut]->ComputeIntegral();
	   cout << "Created P.D.F. histogram: " << pdf_x[ipt][iut]->GetName() << " (integral=" << integral << ")" << endl;
	 }
       }
     }
     cout <<  "ScalarEt: All P.D.F. histograms initialized"<<endl;
     need_init=false;
   } // end of initialization
   
   scalar_ET=0.0;
   scalar_ET_expectation=0.0;

   // Find PT bin (don't change PT distribution)
   Int_t theBin_PT=0;
   if(true_PT<bins_PT[0]) theBin_PT=0;
   else if(true_PT>=bins_PT[nbins_PT-1]) theBin_PT=nbins_PT-1;
   else {
     for(Int_t ipt=0; ipt<nbins_PT;ipt++) {
       if(true_PT>=bins_PT[ipt] && true_PT<bins_PT[ipt+1]) {
	 theBin_PT=ipt;
	 break;
       }
     }
   }
   
   // Find UT bin (don't change UT distribution)
   Int_t theBin_UT=0;
   if(recoil_UT<bins_UT[0]) theBin_UT=0;
   else if(recoil_UT>=bins_UT[nbins_UT-1]) theBin_UT=nbins_UT-1;
   else {
     for(Int_t iut=0; iut<nbins_UT;iut++) {
       if(recoil_UT>=bins_UT[iut] && recoil_UT<bins_UT[iut+1]) {
	 theBin_UT=iut;
	 break;
       }
     }
   }
   // Create an interpolated P.D.F. histogram for a given UT and 2 neighbour PT bins.
   double t=0.0;
   TH1D *h1=NULL, *h2=NULL, *hint=NULL;
   if(true_PT>=average_true_PT[nbins_PT-1]) {
     t=1.0;
     h1=NULL;
     h2=pdf_x[theBin_PT][theBin_UT];
   } else if (true_PT>=average_true_PT[theBin_PT]) {
     t=(true_PT-average_true_PT[theBin_PT])/(average_true_PT[theBin_PT+1]-average_true_PT[theBin_PT]);
     h1=pdf_x[theBin_PT][theBin_UT];
     h2=pdf_x[theBin_PT+1][theBin_UT];
   } else if (true_PT<average_true_PT[0]) {
     t=0.0;
     h1=pdf_x[theBin_PT][theBin_UT];
     h2=NULL;
   } else {
     t=(true_PT-average_true_PT[theBin_PT-1])/(average_true_PT[theBin_PT]-average_true_PT[theBin_PT-1]);
     h1=pdf_x[theBin_PT-1][theBin_UT];
     h2=pdf_x[theBin_PT][theBin_UT];
   }
   //    cout << "h1="<<h1<<" h2="<<h2<<" t="<<t<<", ipt="<<theBin_PT<<", iut="<<theBin_UT<<endl<<flush;
   
   // If both P.D.F. histograms for a given UT and 2 neighbour PT bins
   // are empty then try to interpolate between 2 different UT's in the same PT bin.
   // In this case will try to find 2 nearest non-zero P.D.F. histograms on the left
   // and right hand side w.r.t. a given UT value.
   if(h1==NULL && h2==NULL) {
     
     // left side
     Double_t UT_h1=0.0;
     for(int iut=theBin_UT-1; iut>=0; iut--) {
       if(pdf_x[theBin_PT][iut] && pdf_x[theBin_PT][iut]->GetEntries()>0) {
	 h1=pdf_x[theBin_PT][iut];
	 UT_h1=0.5*(bins_UT[iut]+bins_UT[iut+1]); // UT at bin center
	 break;
       }
     }
     // right side
     Double_t UT_h2=0.0;
     for(int iut=theBin_UT+1; iut<nbins_UT; iut++) {
       if(pdf_x[theBin_PT][iut] && pdf_x[theBin_PT][iut]->GetEntries()>0) {
	 h2=pdf_x[theBin_PT][iut];
	 UT_h2=0.5*(bins_UT[iut]+bins_UT[iut+1]); // UT at bin center
	 break;
       }
     }
     // final check
     if(h1 && h2) t=(recoil_UT-UT_h1)/(UT_h2-UT_h1);
     else if(h1)  t=0.0;
     else if(h2)  t=1.0;
     else {
       cerr << "ScalarEt: All P.D.F histograms for PT-bin "<<theBin_PT<<" are empty!!!" << endl;
       throw;
     }
   } // end of if(h1==NULL && h2==NULL)...
   
   // Finally get random SET
   if(h1==NULL) {
     scalar_ET = recoil_UT / h2->GetRandom();
     scalar_ET_expectation = recoil_UT / h2->GetMean();
   }
   else if (h2==NULL) {
     scalar_ET = recoil_UT / h1->GetRandom();
     scalar_ET_expectation = recoil_UT / h1->GetMean();
   }
   else {
     hint=new TH1D(*h1);
     hint->Add(h1,h2,t,1.0-t);
     scalar_ET = recoil_UT / hint->GetRandom();
     scalar_ET_expectation = recoil_UT / hint->GetMean();
     delete hint;
   }
   //    cout << "set="<<scalar_ET<<endl<<flush;
 }

 // Scalar Et model for hard component only modelled using 2-dimensional RooPdf2dKeys technique.
 // For details see W-mass talk by Mikolaj on Dec 12, 2007 (Model #3).
 // Parameters of this model that work best are: 
 //  INIT_model=3
 //  INIT_USE_PT_INTERPOLATION=false
 //  INIT_USE_UT_INTERPOLATION=false
 //  INIT_USE_UT_CENTRAL_VALUE=false
 //  INIT_USE_UT_INTERPOLATION_IF_EMPTY=false.
 //  scalarEt_input_root_filename="../geant/ScalarEt_input_model=3.root".
 //
 // Currently 4 models can be selected by user: 
 //  model=0 : use parameterized x:=(Recoil UT)/(Recoil SET) vs (Recoil UT) vs (generated PT)
 //  model=1 : use parameterized x:=(Recoil SET) vs (Recoil UT) vs (generated PT)
 //  model=2 : use parameterized x:=(Recoil UT)/(Recoil SET) vs [1-(Recoil UT)/(generated PT)] vs (generated PT)
 //  model=3 : use parameterized x:=(Recoil SET)-(Recoil UT) vs (Recoil UT) vs (generated PT)
 // Each of them requires a separate input ROOT file. 
 inline void wz_utils::ScalarEt_ver2(double true_PT,
				     double recoil_UT,
				     double &scalar_ET, 
				     double &scalar_ET_expectation,
				     const char *scalarEt_input_root_filename,
				     int  INIT_model,
				     bool INIT_USE_PT_INTERPOLATION,
				     bool INIT_USE_UT_INTERPOLATION,
				     bool INIT_USE_UT_CENTRAL_VALUE,
				     bool INIT_USE_UT_INTERPOLATION_IF_EMPTY) {
   static bool need_init=true;
   static bool individual_ut_bins=false; 
   static int  model=-1;
   static bool USE_PT_INTERPOLATION=false;
   static bool USE_UT_INTERPOLATION=false;
   static bool USE_UT_CENTRAL_VALUE=false;
   static bool USE_UT_INTERPOLATION_IF_EMPTY=false;
   static double average_true_PT[1000],  // bins for generated PT of the Z boson
                 central_UT[1000][1000]; // model=0, 1: bins for smeared hard recoil [GeV]
                                         // model=2:    bins for recoil Ut resolution, 1-UT/PT 
   static int nbins_PT=0, nbins_UT[1000];
   static double bins_PT[1000],          // bins for generated PT of the Z boson 
                 bins_UT[1000][1000];    // model=0, 1: bins for smeared hard recoil [GeV]
                                         // model=2:    bins for recoil Ut resolution, 1-UT/PT 
   static TH1D *pdf_x[1000][1000];
   
   // Initialize P.D.F. histograms of:
   // model=0: variable x:=(Recoil Ut)/(Recoil SET) for different UT and PT bins
   // model=1: variable x:=(Recoil SET) for different UT and PT bins
   // model=2: variable x:=(Recoil Ut)/(Recoil SET) for different (1-UT/PT) and PT bins
   // model=3: variable x:=[(Recoil SET)-(Recoil UT)] for different UT and PT bins
   if(need_init || INIT_model!=model) {
     if(INIT_model<0 || INIT_model>3) {
       cerr << "ScalarEt: Wrong MODEL="<<INIT_model<<"!!!"<<endl; 
       throw;
     }
     model=INIT_model;
     cout << "ScalarEt: Initializing p.d.f. histograms for MODEL="<<model<<" from "<<scalarEt_input_root_filename<<" ROOT file"<<endl;
     USE_PT_INTERPOLATION=INIT_USE_PT_INTERPOLATION;
     USE_UT_INTERPOLATION=INIT_USE_UT_INTERPOLATION;
     USE_UT_CENTRAL_VALUE=INIT_USE_UT_CENTRAL_VALUE;
     USE_UT_INTERPOLATION_IF_EMPTY=INIT_USE_UT_INTERPOLATION_IF_EMPTY;
     
     TFile *f=new TFile(scalarEt_input_root_filename, "OLD");
     if(!f) {
       cerr << "ScalarEt: Can't open file: "<<scalarEt_input_root_filename<<" !!!"<<endl; 
       throw;
     }
     f->cd();
     
     // Profile histogram: <PT(true)> vs PT(true) 
     TH1D *hist_PT=(TH1D*)f->Get("h_AveRecoilPt_V_RecoilPt_FULL_ALL");
     if(hist_PT==NULL || hist_PT->GetNbinsX()==0 || hist_PT->GetNbinsX()>999 ) {
       cerr << "ScalarEt: Can't get histogram with PT bins from file: "<<scalarEt_input_root_filename<<" !!!"<<endl; 
       throw;
     }
     nbins_PT=hist_PT->GetNbinsX();
     for(int ipt=0; ipt<nbins_PT; ipt++) {
       average_true_PT[ipt]=hist_PT->GetBinContent(ipt+1);
       bins_PT[ipt]=hist_PT->GetBinLowEdge(ipt+1);
       cout << "ScalarEt: PT bin ipt="<<ipt<<", <PT>="<<average_true_PT[ipt]<<" GeV"<<endl; 
     }
     bins_PT[nbins_PT]=hist_PT->GetBinLowEdge(nbins_PT)+hist_PT->GetBinWidth(nbins_PT);
     cout <<  "ScalarEt: Using "<<nbins_PT<<" PT bins"<<endl; 
     
     // Chieck if Recoil UT (model=0,1,3) or Recoil UT resolution (model=2) 
     // distributions are available for individual PT bins. 
     // If not, will use a common binning from h_RecoilUt_FULL_ALL for model=0,1,3
     // or from h_RecoilUtResolution_FULL_ALL for model=2.
     individual_ut_bins=true; 
     TH1D *hist_UT[1000];
     for(int ipt=0;ipt<nbins_PT;ipt++) {
       stringstream hname;
       switch(model) {
       case 0:
       case 1:
       case 3:
	 hname<<"h_RecoilUt_FULL_PTbin"<<ipt;
	 break;
       case 2:
	 hname<<"h_RecoilUtResolution_FULL_PTbin"<<ipt;
	 break;
       };       
       hist_UT[ipt]=(TH1D*)f->Get(hname.str().c_str());
       if(hist_UT[ipt]==NULL || hist_UT[ipt]->GetNbinsX()==0 || hist_UT[ipt]->GetNbinsX()>999 ) {
	 individual_ut_bins=false;
	 break;
       } else {
	 nbins_UT[ipt]=hist_UT[ipt]->GetNbinsX();
	 for(int iut=0;iut<=nbins_UT[ipt];iut++) {
	   if(iut!=nbins_UT[ipt]) central_UT[ipt][iut]=hist_UT[ipt]->GetBinCenter(iut+1);
	   bins_UT[ipt][iut]=hist_UT[ipt]->GetBinLowEdge(iut+1);
	 }
       }
     }
     // Check if Recoil UT (model=0,1,3) or Recoil UT resolution (model=2) distribution 
     // integrated over all PT bins is available.
     if(!individual_ut_bins) {
       switch(model) {
       case 0:
       case 1: 
       case 3:
	 hist_UT[0]=(TH1D*)f->Get("h_RecoilUt_FULL_ALL");
	 if(hist_UT[0]==NULL || hist_UT[0]->GetNbinsX()==0 || hist_UT[0]->GetNbinsX()>999 ) {
	   cerr << "ScalarEt: Can't get histogram with UT bins from file: "<<scalarEt_input_root_filename<<" !!!"<<endl; 
	   throw;
	 }
	 nbins_UT[0]=hist_UT[0]->GetNbinsX();
	 for(int iut=0; iut<=nbins_UT[0]; iut++) {
	   bins_UT[0][iut]=hist_UT[0]->GetBinLowEdge(iut+1);
	   if(iut!=nbins_UT[0]) {
	     central_UT[0][iut]=hist_UT[0]->GetBinCenter(iut+1);
	     cout << "ScalarEt: Recoil UT bin iut="<<iut<<", UT_central="<<central_UT[0][iut]<<" GeV"<<endl; 
	   }
	 }
	 cout <<  "ScalarEt: Using "<<nbins_UT[0]<<" UT bins"<<endl; 
	 break;
       case 2:
	 hist_UT[0]=(TH1D*)f->Get("h_RecoilUtResolution_FULL_ALL");
	 if(hist_UT[0]==NULL || hist_UT[0]->GetNbinsX()==0 || hist_UT[0]->GetNbinsX()>999 ) {
	   cerr << "ScalarEt: Can't get histogram with Recoil UT resolution bins from file: "<<scalarEt_input_root_filename<<" !!!"<<endl; 
	   throw;
	 }
	 nbins_UT[0]=hist_UT[0]->GetNbinsX();
	 for(int iut=0; iut<=nbins_UT[0]; iut++) {
	   bins_UT[0][iut]=hist_UT[0]->GetBinLowEdge(iut+1);
	   if(iut!=nbins_UT[0]) {
	     central_UT[0][iut]=hist_UT[0]->GetBinCenter(iut+1);
	     cout << "ScalarEt: Recoil UT resolution bin iut="<<iut<<", UTres_central="<<central_UT[0][iut]<<endl; 
	   }
	 }
	 cout <<  "ScalarEt: Using "<<nbins_UT[0]<<" Recoil UT resolution bins"<<endl; 
	 break;
       }; // end of switch(model)....
       // Update arrays for other PT bins
       for(int ipt=1;ipt<nbins_PT; ipt++) {
	 nbins_UT[ipt] = nbins_UT[0];
	 for(int iut=0; iut<=nbins_UT[0]; iut++) {
	   if(iut!=nbins_UT[0]) central_UT[ipt][iut]=central_UT[0][iut];
	   bins_UT[ipt][iut]=bins_UT[0][iut];
	 }
       }
     }
     
     // now read the histograms with p.d.f's of:
     // model=0: variable x:=(Recoil Ut)/(Recoil SET) for different UT and PT bins
     // model=1: variable x:=(Recoil SET) for different UT and PT bins
     // model=2: variable x:=(Recoil Ut)/(Recoil SET) for different (1-UT/PT) and PT bins
     bool  first_pdf_x_axis_ok=false;
     TAxis first_pdf_x_axis;
     for(int ipt=0; ipt<nbins_PT; ipt++) {
       for(int iut=0; iut<nbins_UT[ipt]; iut++) {
	 stringstream hname;
	 switch(model) {
	 case 0: // y=UT
	 case 1: // y=UT
	 case 3: // y=UT
	   hname<<"hist_PTbin"<<ipt<<"_UTbin"<<iut;
	   break;
	 case 2: // y=1-UT/PT
	   hname<<"hist_PTbin"<<ipt<<"_UTresBin"<<iut;
	   break;
	 }; // end of switch(model)	 
	 TH1D *hist_PDF=(TH1D*)f->Get(hname.str().c_str());
	 if(hist_PDF==NULL) {
	   pdf_x[ipt][iut]=NULL;
	   //	 cerr << "ScalarEt: P.D.F. histogram "<<hname.str()<<" is empty"<<endl;
	 } else {
	   pdf_x[ipt][iut]=new TH1D(*hist_PDF);
	   stringstream pdf_x_name;
	   pdf_x_name<<pdf_x[ipt][iut]->GetName()<<"_copy";
	   pdf_x[ipt][iut]->SetName(pdf_x_name.str().c_str());
	   
	   // Check if all PDF(x) histograms have identical X axis. 
	   // This is mandatory for doing inter-UT and inter-PT interpolations.
	   TAxis *new_pdf_x_axis=pdf_x[ipt][iut]->GetXaxis();
	   bool new_pdf_x_axis_ok=false;
	   if(!first_pdf_x_axis_ok) {
	     new_pdf_x_axis->Copy(first_pdf_x_axis);
	     first_pdf_x_axis_ok=true;
	     new_pdf_x_axis_ok=true;
	   } else if ( new_pdf_x_axis->GetXbins()->GetSize()==first_pdf_x_axis.GetXbins()->GetSize() &&
		       TString(new_pdf_x_axis->GetTitle())==TString(first_pdf_x_axis.GetTitle()) &&
		       new_pdf_x_axis->GetNbins()==first_pdf_x_axis.GetNbins() &&
		       new_pdf_x_axis->GetXmin()==first_pdf_x_axis.GetXmin() &&
		       new_pdf_x_axis->GetXmax()==first_pdf_x_axis.GetXmax() ) {
	     new_pdf_x_axis_ok=true;
	     if( new_pdf_x_axis->GetXbins()->GetSize() ) {
	       for(int ibin=0; ibin<=new_pdf_x_axis->GetNbins(); ibin++)
		 if(new_pdf_x_axis->GetXbins()->GetArray()[ibin] != first_pdf_x_axis.GetXbins()->GetArray()[ibin]) {
		   new_pdf_x_axis_ok=false;
		   break;
		 }
	     }
	   } else new_pdf_x_axis_ok=false;
	   if(!new_pdf_x_axis_ok) {
	     cerr << "ScalarEt: PDF(x) histograms have different axes!!! (PTbin="<<ipt<<", UTbin="<<iut<<")"<<endl;
	     throw;
	   }
	   
	   // check bin boundaries
	   switch(model) {
	   case 0: // 0 < x=UT/SET < 1
	   case 2:
	     if( pdf_x[ipt][iut]->GetBinLowEdge(1) < 0.0 ||
		 pdf_x[ipt][iut]->GetBinLowEdge(pdf_x[ipt][iut]->GetNbinsX()+1) > 1.0 ) {
	       cerr << "ScalarEt: Wrong lower/upper histogram limit!!!" << endl
		    << "          Expected limits are between 0 and 1"<<endl;
	       throw;
	     }
	     break;
	   case 1: // x=SET >= UT >= 0
	   case 3: // x=(SET-UT) >= 0
	     if( pdf_x[ipt][iut]->GetBinLowEdge(1) < 0.0 ) {
	       cerr << "ScalarEt: Wrong lower histogram limit!!!" << endl
		    << "          Expected lower limit >=0."<<endl;
	       throw;
	     }
	     break;
	   }; // end of switch(model)
	   
	   Double_t integral=pdf_x[ipt][iut]->Integral("width");
	   // normalize p.d.f. to 1
	   if(integral>0) pdf_x[ipt][iut]->Scale(1.0/integral);
	   cout << "Created P.D.F. histogram: " << pdf_x[ipt][iut]->GetName() << endl;
	 }
       }
     }
     if(USE_UT_INTERPOLATION_IF_EMPTY) {
       // now look for any missing or empty histograms
       // between UT bins for a given PT bin and do a linear interpolation in UT. 
       for(int ipt=0; ipt<nbins_PT; ipt++) {
	 switch(model) {
	   ////////////////////////////////
	 case 0: // y=UT
	 case 1: // y=UT
	 case 3: // y=UT
	   for(int iut1=0; iut1<nbins_UT[ipt]-1; iut1++) {
	     TH1D *h1=pdf_x[ipt][iut1],*h2;
	     bool firstUTbin_empty=((iut1==0 && (!h1 || (h1 && h1->Integral("width")==0.0))));
	     if((h1 && h1->Integral("width")>0) || firstUTbin_empty) {
	       
	       // find next non-empy histogram
	       int iut2=iut1+1;
	       for(int iut=iut1+1; iut<nbins_UT[ipt]; iut++) {
		 h2=pdf_x[ipt][iut];
		 if(h2 && h2->Integral("width")>0) {
		   iut2=iut;
		   break;
		 }
		 iut2++;
	       }
	       if(iut2==nbins_UT[ipt]) break; // go to the next PT bin
	       if(!firstUTbin_empty && iut2==iut1+1) continue;  // proceed to the next UT bin
	       int istart=iut1+1;
	       // perform a linear interpolation in UT
	       for(int iut=istart; iut<iut2; iut++) {
		 if(pdf_x[ipt][iut]) delete pdf_x[ipt][iut];
		 Double_t t=(central_UT[ipt][iut]-central_UT[ipt][iut1])/(central_UT[ipt][iut2]-central_UT[ipt][iut1]);
		 TH1D *hint=new TH1D(*h1);
		 hint->Add(h1,h2,1.0-t,t);
		 pdf_x[ipt][iut]=hint;
		 stringstream hname;
		 hname<<"hist_PTbin"<<ipt<<"_UTbin"<<iut<<"_copy";
		 pdf_x[ipt][iut]->SetName(hname.str().c_str());
		 Double_t integral=pdf_x[ipt][iut]->Integral("width");
		 // normalize p.d.f. to 1
		 if(integral>0) pdf_x[ipt][iut]->Scale(1.0/integral);
		 cout << "Created interpolated P.D.F. histogram: " << pdf_x[ipt][iut]->GetName() << endl;
		 
	       }
	     }
	   } // end of UT bin loop
	   break;
	   ////////////////////////////////
	 case 2: // y=(1-UT/PT)
	   for(int iut1=nbins_UT[ipt]-1; iut1>=1; iut1--) {
	     TH1D *h1=pdf_x[ipt][iut1],*h2;
	     bool lastUTbin_empty=((iut1==nbins_UT[ipt]-1 && (!h1 || (h1 && h1->Integral("width")==0.0))));
	     if((h1 && h1->Integral("width")>0) || lastUTbin_empty) {
	       
	       // find next non-empy histogram (going backward)
	       int iut2=iut1-1;
	       for(int iut=iut1-1; iut>=0; iut--) {
		 h2=pdf_x[ipt][iut];
		 if(h2 && h2->Integral("width")>0) {
		   iut2=iut;
		   break;
		 }
		 iut2--;
	       }
	       if(iut2<0) break; // go to the next PT bin
	       if(!lastUTbin_empty && iut2==iut1-1) continue;  // proceed to the next UT bin
	       int istart=iut1-1;
	       // perform a linear interpolation in UT
	       for(int iut=istart; iut>iut2; iut--) {
		 if(pdf_x[ipt][iut]) delete pdf_x[ipt][iut];
		 Double_t t=(central_UT[ipt][iut]-central_UT[ipt][iut1])/(central_UT[ipt][iut2]-central_UT[ipt][iut1]);;
		 TH1D *hint=new TH1D(*h1);
		 hint->Add(h1,h2,1.0-t,t);
		 pdf_x[ipt][iut]=hint;
		 stringstream hname;
		 hname<<"hist_PTbin"<<ipt<<"_UTResBin"<<iut<<"_copy";
		 pdf_x[ipt][iut]->SetName(hname.str().c_str());
		 Double_t integral=pdf_x[ipt][iut]->Integral("width");
		 // normalize p.d.f. to 1
		 if(integral>0) pdf_x[ipt][iut]->Scale(1.0/integral);
		 cout << "Created interpolated P.D.F. histogram: " << pdf_x[ipt][iut]->GetName() << endl;
		 
	       }
	     }
	   } // end of Recoil UT resolution bin loop
	   break;
	   ////////////////////////////////
	 }; // end of switch(model)
       } // end of PT bin loop
     } // end of filling empty gaps in UT
     
     cout <<  "ScalarEt: All P.D.F. histograms initialized for MODEL="<<model<<endl;  
     need_init=false;
   } // end of initialization
   
   scalar_ET=0.0;     // final SET should be >= UT !!!
   scalar_ET_expectation=0.0;
   
   // Find PT bin
   Int_t theBin_PT=0;
   if(true_PT<bins_PT[0]) theBin_PT=0;
   else if(true_PT>=bins_PT[nbins_PT-1]) theBin_PT=nbins_PT-1;
   else {
     for(Int_t ipt=0; ipt<nbins_PT;ipt++) {
       if(true_PT>=bins_PT[ipt] && true_PT<bins_PT[ipt+1]) {
	 theBin_PT=ipt;
	 break;
       }
     }
   }
   // model=0,1: Find UT bin
   // model=0,1: Find (1-UT/PT) bin
   Int_t theBin_UT=0;
   Int_t adjacentBin_UT[3]={-1,-1,-1}; // UT bin corresponding to PT bins: theBin_PT-1, theBin_PT, theBin_PT+1
   Int_t lowerBin_UT[3]={-1,-1,-1};    // lower UT bin for interpolation corresponding to PT bins: theBin_PT-1, theBin_PT, theBin_PT+1
   Int_t upperBin_UT[3]={-1,-1,-1};    // upper UT bin for interpolation corresponding to PT bins: theBin_PT-1, theBin_PT, theBin_PT+1
   int istart=1, iend=1;
   double value;   // value to compare (can be: recoil_UT, resolution)
   switch(model) {
   case 0: // y=UT
   case 1: // y=UT
   case 3: // y=UT
     value = recoil_UT;	
     break;
   case 2: // y=(1-UT/PT)
     value = 1.0 - recoil_UT / true_PT;
     break;
   }; // end switch(model)
   if(individual_ut_bins) { istart=0; iend=2; }
   for(int i=istart; i<=iend; i++) {
     int ipt=theBin_PT+i-1; // minim(nbins_PT-1, maxim(0, theBin_PT+(i-1))); // PT bin under test
     if(ipt<0 || ipt>nbins_PT-1) continue;
     adjacentBin_UT[i]=0;
     for(int iut=nbins_UT[ipt]-1;iut>=0;iut--) if(value>=bins_UT[ipt][iut]) {
       adjacentBin_UT[i]=iut;
       break;
     }
     if(value>=central_UT[ipt][nbins_UT[ipt]-1]) {
       lowerBin_UT[i]=-1;
       upperBin_UT[i]=nbins_UT[ipt]-1;
     } else if(value>=central_UT[ipt][adjacentBin_UT[i]]) {
       lowerBin_UT[i]=adjacentBin_UT[i];
       upperBin_UT[i]=minim(adjacentBin_UT[i]+1, nbins_UT[ipt]-1);
     } else if(value<central_UT[ipt][0]) {
       lowerBin_UT[i]=-1;
       upperBin_UT[i]=0;
     } else {
       lowerBin_UT[i]=maxim(adjacentBin_UT[i]-1, 0);
       upperBin_UT[i]=adjacentBin_UT[i];
     }
   }
   if(!individual_ut_bins) {
     lowerBin_UT[0]=lowerBin_UT[1];
     lowerBin_UT[2]=lowerBin_UT[1];
     upperBin_UT[0]=upperBin_UT[1];
     upperBin_UT[2]=upperBin_UT[1];
     adjacentBin_UT[2]=adjacentBin_UT[1];
     adjacentBin_UT[0]=adjacentBin_UT[1];
   } 
   theBin_UT=adjacentBin_UT[1];
   
   if(USE_UT_INTERPOLATION) {
     // Create an interpolated P.D.F. histogram for a given PT and:
     // model=0,1,3: 2 neighbour UT bins
     // model=2:     2 neighbour (1-UT/PT) bins
     
     /////////////////////
     double t_pt=0.0;
     int ipt[2]={-1,-1};             // contains lower and upper pT bin for PT-itnerpolation (-1 for none)
     int iut[2][2]={{-1,-1},{-1,-1}};// iut[j][] contains lower and upper uT bins for UT interpolation for a pT
                                     // bin pointed by ipt[j]
     int iutc[2]={-1,-1};
     if(USE_PT_INTERPOLATION) { // UT interpolation (first) and PT interpolation (later)
       
       if(true_PT>=average_true_PT[nbins_PT-1]) { 
	 t_pt=1.0; 
	 ipt[0]=-1;          iut[0][0]=-1;             iut[0][1]=-1;             iutc[0]=-1;
	 ipt[1]=theBin_PT;   iut[1][0]=lowerBin_UT[1]; iut[1][1]=upperBin_UT[1]; iutc[1]=adjacentBin_UT[1];
       } else if (true_PT>=average_true_PT[theBin_PT]) { 
	 t_pt=(true_PT-average_true_PT[theBin_PT])/(average_true_PT[theBin_PT+1]-average_true_PT[theBin_PT]);
	 ipt[0]=theBin_PT;   iut[0][0]=lowerBin_UT[1]; iut[0][1]=upperBin_UT[1]; iutc[0]=adjacentBin_UT[1];
	 ipt[1]=theBin_PT+1; iut[1][0]=lowerBin_UT[2]; iut[1][1]=upperBin_UT[2]; iutc[1]=adjacentBin_UT[2];
       } else if (true_PT<average_true_PT[0]) {
	 t_pt=0.0;
	 ipt[0]=theBin_PT;   iut[0][0]=lowerBin_UT[1]; iut[0][1]=upperBin_UT[1]; iutc[0]=adjacentBin_UT[1];
	 ipt[1]=-1;          iut[1][0]=-1;             iut[1][1]=-1;             iutc[1]=-1;
       } else {
	 t_pt=(true_PT-average_true_PT[theBin_PT-1])/(average_true_PT[theBin_PT]-average_true_PT[theBin_PT-1]);
	 ipt[0]=theBin_PT-1; iut[0][0]=lowerBin_UT[0]; iut[0][1]=upperBin_UT[0]; iutc[0]=adjacentBin_UT[0];
	 ipt[1]=theBin_PT;   iut[1][0]=lowerBin_UT[1]; iut[1][1]=upperBin_UT[1]; iutc[1]=adjacentBin_UT[1];
       }
     } else { // UT interpolation, but no PT interpolation
       t_pt=0.0;
       ipt[0]=theBin_PT;     iut[0][0]=lowerBin_UT[1]; iut[0][1]=upperBin_UT[1]; iutc[0]=adjacentBin_UT[1];
       ipt[1]=-1;            iut[1][0]=-1;             iut[1][1]=-1;             iutc[1]=-1;
     }
     
     TH1D *hint[2]={NULL, NULL};
     bool hint_delete[2]={false, false};
     double t_ut[2];
     for(int i=0;i<2;i++) {
       if(ipt[i]>=0) {
	 if(iut[i][0]>=0 && 
	    iut[i][1]>=0 &&
	    pdf_x[ipt[i]][iut[i][0]] &&
	    pdf_x[ipt[i]][iut[i][1]]   ) { // UT interpolation is possible
	   hint[i]=new TH1D(*(pdf_x[ipt[i]][iut[i][0]]));
	   t_ut[i]=(value-central_UT[ipt[i]][iut[i][0]])/(central_UT[ipt[i]][iut[i][1]]-central_UT[ipt[i]][iut[i][0]]);
	   hint[i]->Add(pdf_x[ipt[i]][iut[i][0]], pdf_x[ipt[i]][iut[i][1]], 1.0-t_ut[i], t_ut[i]);
	   double integral=hint[i]->Integral("width");
	   if (integral>0) hint[i]->Scale(1.0/integral);
	   hint_delete[i]=true;
	 } else  if(iut[i][0]>=0 && pdf_x[ipt[i]][iut[i][0]]) {
	   hint[i]=pdf_x[ipt[i]][iut[i][0]];
	 } else if(iut[i][1]>=0 && pdf_x[ipt[i]][iut[i][1]]) {
	   hint[i]=pdf_x[ipt[i]][iut[i][1]];
	 }
       }
     } 
     
     if(USE_UT_CENTRAL_VALUE) {
       switch(model) {
       case 0:
       case 1: 
       case 3: recoil_UT = central_UT[theBin_UT][theBin_UT]; // interpret central_UT[] as UT
	 break;
       case 2: recoil_UT = (1.0-central_UT[theBin_UT][theBin_UT])*true_PT; // interpret central_UT[] as 1-UT/PT
	 break; 
       }; // end of switch(model)
     }

     if(!hint[0] && !hint[1]) {
       scalar_ET = recoil_UT;
       scalar_ET_expectation = recoil_UT;
     } else {
       double rnd;
       double mean;
       if(!hint[0]) {
	 rnd = hint[1]->GetRandom();
	 mean = hint[1]->GetMean();
	 if(hint_delete[1]) delete hint[1];     
       } else if (!hint[1]) {
	 rnd = hint[0]->GetRandom();
	 mean = hint[0]->GetMean();
	 if(hint_delete[0]) delete hint[0];     
       } else {
	 TH1D *hint_pt=new TH1D(*(hint[0]));
	 hint_pt->Add(hint[0], hint[1], 1.0-t_pt, t_pt);
	 rnd = hint_pt->GetRandom();
	 mean = hint_pt->GetMean();
	 if(hint_delete[0]) delete hint[0];
	 if(hint_delete[1]) delete hint[1];
	 if(hint_pt) delete hint_pt;
       }
       switch(model) {
       case 2:
       case 0: scalar_ET = recoil_UT / rnd;  // rnd=UT/SET
	 scalar_ET_expectation = recoil_UT / mean;
	 break;
       case 1: scalar_ET = maxim( rnd, recoil_UT );  // rnd=SET
	 scalar_ET_expectation = mean;
	 break;
       case 3: scalar_ET = rnd + recoil_UT;  // rnd=(SET-UT)
	 scalar_ET_expectation = mean + recoil_UT;
	 break;
       }; // end of switch(model)
     }
   } else {
     if(USE_PT_INTERPOLATION) { // PT interpolation, but no UT interpolation
       
       // Create an interpolated P.D.F. histogram for a given UT and 2 neighbour PT bins.
       double t=0.0;
       TH1D *h1=NULL, *h2=NULL, *hint=NULL;
       if(true_PT>=average_true_PT[nbins_PT-1]) { 
	 t=1.0; 
	 h1=NULL; 
	 h2=pdf_x[theBin_PT][theBin_UT]; 
       } else if (true_PT>=average_true_PT[theBin_PT]) { 
	 h1=pdf_x[theBin_PT][theBin_UT];
	 if(adjacentBin_UT[2]>=0) {
	   t=(true_PT-average_true_PT[theBin_PT])/(average_true_PT[theBin_PT+1]-average_true_PT[theBin_PT]);
	   h2=pdf_x[theBin_PT+1][adjacentBin_UT[2]];
	 } else {
	   t=0.0;
	   h2=NULL;
	 }
       } else if (true_PT<average_true_PT[0]) {
	 t=0.0;
	 h1=pdf_x[theBin_PT][theBin_UT]; 
	 h2=NULL; 
       } else {
	 h2=pdf_x[theBin_PT][theBin_UT];
	 if(adjacentBin_UT[0]>=0) {
	   t=(true_PT-average_true_PT[theBin_PT-1])/(average_true_PT[theBin_PT]-average_true_PT[theBin_PT-1]);
	   h1=pdf_x[theBin_PT-1][adjacentBin_UT[0]];
	 } else {
	   t=1.0;
	   h1=NULL;
	 }
       }
       
       if(USE_UT_CENTRAL_VALUE) {
	 switch(model) {
	 case 0:
	 case 1: 
	 case 3: recoil_UT = central_UT[theBin_UT][theBin_UT]; // interpret central_UT[] as UT
	   break;
	 case 2: recoil_UT = (1.0-central_UT[theBin_UT][theBin_UT])*true_PT; // interpret central_UT[] as 1-UT/PT
	   break; 
	 }; // end of switch(model)
       }
       
       // Finally get random SET 
       if(!h1 && !h2) {
	 scalar_ET = recoil_UT;
	 scalar_ET_expectation = recoil_UT;
       } else {
	 double rnd, mean;
	 if(!h1) {
	   rnd = h2->GetRandom();
	   mean = h2->GetMean();
	 } else if (h2==NULL) {
	   rnd = h1->GetRandom();
	   mean =  h1->GetMean();
	 } else {
	   hint=new TH1D(*h1);
	   hint->Add(h1,h2,1.0-t,t);
	   rnd = hint->GetRandom();
	   mean =  hint->GetMean();
	   if(hint) delete hint;
	 }
	 switch(model) {
	 case 2: 
	 case 0: scalar_ET = recoil_UT / rnd;  // rnd=UT/SET
	   scalar_ET_expectation = recoil_UT / mean;
	   break;
	 case 1: scalar_ET = maxim( rnd, recoil_UT ); // rnd=SET
	   scalar_ET_expectation = mean;
	   break;
	 case 3: scalar_ET = rnd + recoil_UT;  // rnd=(SET-UT) 
	   scalar_ET_expectation = mean + recoil_UT;
	   break;
	 }; // end of switch(model)
       }
     } else { // no PT interpolation, no UT interpolation
       
       if(USE_UT_CENTRAL_VALUE) {
	 switch(model) {
	 case 0:
	 case 1: 
	 case 3: recoil_UT = central_UT[theBin_UT][theBin_UT]; // interpret central_UT[] as UT
	   break;
	 case 2: recoil_UT = (1.0-central_UT[theBin_UT][theBin_UT])*true_PT; // interpret central_UT[] as 1-UT/PT
	   break; 
	 }; // end of switch(model)
       }
       
       TH1D *h1=pdf_x[theBin_PT][theBin_UT]; 
       if(h1) {
	 double rnd = h1->GetRandom();
	 double mean = h1->GetMean();
	 switch(model) {
	 case 2:
	 case 0: scalar_ET = recoil_UT / rnd;  // rnd=UT/SET
	   scalar_ET_expectation = recoil_UT / mean;
	   break;
	 case 1: scalar_ET = maxim( rnd, recoil_UT );              // rnd=SET
	   scalar_ET_expectation = mean;
	   break;
	 case 3: scalar_ET = rnd + recoil_UT;  // rnd=(SET-UT)
	   scalar_ET_expectation = mean + recoil_UT;
	   break;
	 }; // end of switch(model)
       } else {
	 scalar_ET = recoil_UT;
       }
     }
   }
   // cout << "set="<<scalar_ET<<endl<<flush;
 }

 // generate random numbers according to Crystall Ball function
 inline double wz_utils::flipCrystalBall(double mean, double sigma, double alpha, double n, TRandom* r, double *extnRndm) {
   // Here we only implement "lower" tails
   assert(alpha>0);

   // Auxiliary calculations
   double A=pow(n/fabs(alpha),n)*exp(-alpha*alpha/2.);
   double B=n/fabs(alpha)-fabs(alpha);

   // Surfaces of the two halves
   //
   // gaussian part one
   double Sgauss=sigma*sqrt(TMath::Pi()/2.);
   // gaussian part two
   Sgauss+=sigma*sqrt(TMath::Pi()/2.)*TMath::Erf(alpha/sqrt(2.));
   // tail
   double Stail=A*sigma/(n-1.)*pow(B+alpha,-n+1.);

   // Pick one of the halves
   double S=Stail+Sgauss;
   double ran = 0;
   if (!extnRndm)
     ran=r->Rndm();
   else
     ran=extnRndm[0];
   if (ran<(Stail/S)) {
     // generate a tail event
     double d = 0;
     if (!extnRndm)
       d=r->Rndm();
     else
       d=extnRndm[1];
     return sigma*B+mean-sigma*(B+alpha)*pow(d,1./(-n+1.));
   } else {
     // generate a gaussian event
     while ((ran=r->Gaus(mean,sigma))<(mean-alpha*sigma)) {
       // flip again
     }   
     return ran;
   }
 }

#endif // INC_WZUTILS
