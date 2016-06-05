#include "wmass_util/CAFEMObj.hpp"
#include "wmass_util/WZ_Utils.hpp"
#include "tmb_tree/TMBTrack.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "wmass_util/CaloGeometryManager.hpp"
#include "tmb_tree/TMBCaloCell.hpp"

using namespace std;

const double B_field = 2.;

// constructor
CAFEMObj::CAFEMObj(TMBEMCluster* p){
  _tmbemcluster_ptr = p;
  _trkphiem3 = -999.;
}
  
// destructor
CAFEMObj::~CAFEMObj() {}

// extrapolate the track to EM3 and calculate extrapolated phi
// if no track match, just return 9999.
double CAFEMObj::trkPhiEM3(EMClusterPosCorr *emclusposcorr, int solenoid_polarity, Float_t Chi2Cut, bool isGeantMC) const {
  double floorX = _tmbemcluster_ptr->floorX(3);
  double floorY = _tmbemcluster_ptr->floorY(3);
  double floorZ = _tmbemcluster_ptr->floorZ(3);
  
  double xcor, ycor, zcor;
  emclusposcorr->CorrectClusterPosition(floorX, floorY, floorZ, xcor, ycor, zcor, 3);
  double r_xy = sqrt(xcor*xcor + ycor*ycor);
  
  if(_tmbemcluster_ptr->has_spatial_track_match(Chi2Cut)) {
    const TMBTrack *tmp_track = _tmbemcluster_ptr->getPtrChpSpatial();
    if (tmp_track!=NULL){
      double xtra, ytra, ztra;
      wz_utils::CC_extrap_track(tmp_track, solenoid_polarity, 3, _tmbemcluster_ptr->E(), r_xy, xtra, ytra, ztra, isGeantMC);
      return kinem::phi(xtra, ytra);
    }else {
      return 9999.;
    }
  } else {
    return 9999.;
  }
}

// extrapolate the track to EM3 and calculate extrapolated eta
// if no track match, just return 1e10.
double CAFEMObj::trkEtaEM3(EMClusterPosCorr *emclusposcorr, int solenoid_polarity, Float_t Chi2Cut, bool isGeantMC) const {
  double floorX = _tmbemcluster_ptr->floorX(3);
  double floorY = _tmbemcluster_ptr->floorY(3);
  double floorZ = _tmbemcluster_ptr->floorZ(3);

  double xcor, ycor, zcor;
  emclusposcorr->CorrectClusterPosition(floorX, floorY, floorZ, xcor, ycor, zcor, 3);
  double r_xy = sqrt(xcor*xcor + ycor*ycor);

  if(_tmbemcluster_ptr->has_spatial_track_match(Chi2Cut)) {
    const TMBTrack *tmp_track = _tmbemcluster_ptr->getPtrChpSpatial();
    if (tmp_track!=NULL){
      double xtra, ytra, ztra;
      wz_utils::CC_extrap_track(tmp_track, solenoid_polarity, 3, _tmbemcluster_ptr->E(), r_xy, xtra, ytra, ztra, isGeantMC);
      return kinem::eta(xtra, ytra, ztra);
    }else {
      return 1.e10;
    }
  } else {
    return 1.e10;
  }
}

// find the vector of the raw electron energy using electron cell information
TVector2 CAFEMObj::getRawElecVectorFromCells(float thevert[3], float* SETcontrib) {

  double rawElecVector_X = 0., rawElecVector_Y = 0.;
  double rawSET = 0.;

  // get calorimeter geometry manager
  if(CaloGeometryManager::get_instance()) {    
    const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();

    // loop over all calorimeter cells
    for(UInt_t icell=0; icell<_tmbemcluster_ptr->ncells(); ++icell) {
      const TMBCaloCell *cell = _tmbemcluster_ptr->GetCaloCell(icell);
      float E = cell->E();
      bool normalCell = cell->isNormalCell();
      
      // only look at positive cells and normal cells
      if(E>=0. && normalCell) {
        int ieta = cell->ieta();
        int iphi = cell->iphi();
	int ilyr = cell->layer();
	
        int cell_index = wz_utils::EncodeCellIndex(ieta, iphi, ilyr);
	
        // calorimeter cell position
	map<int, CELLXYZ_STRUCT>::const_iterator iter = calogeometry_map.find(cell_index);
	const CELLXYZ_STRUCT cellgeo = (*iter).second;
	
	float cell_pos[3] = { cellgeo.x, cellgeo.y, cellgeo.z };
	double px_cell, py_cell, pT_cell;
	wz_utils::RevertexCell( E, cell_pos, thevert, px_cell, py_cell, pT_cell);
	rawElecVector_X += px_cell;
	rawElecVector_Y += py_cell;
	rawSET += sqrt(px_cell*px_cell+py_cell*py_cell);
      } // good cell
    } // loop over all cells
  } // get geometry map

  if (SETcontrib) *SETcontrib=rawSET;
  return (TVector2(rawElecVector_X, rawElecVector_Y));
}

// recalculate px, py, eta, phi for new primary vertex
// detector eta, detector phi will not change
// if an electron has a matched track, (b, phi) of the track will be recalculated
// else physics eta, phi of the electron will be determined from the extrapolation
//  from the new vertex to the cluster position in EM3
void CAFEMObj::UpdateForNewVertex(float vertex_old[3], float vertex_new[3]) {
  
  // distance between two vertices
  float distance_vertices[3] = {vertex_new[0]-vertex_old[0], vertex_new[1]-vertex_old[1], 
				vertex_new[2]-vertex_old[2]};
  
  if(!has_track_match()) {
    double eta_new = kinem::eta(vertex_old, vertex_new);
    
    float vertex_old_vect[2] = {vertex_old[0], vertex_old[1]};
    float vertex_new_vect[2] = {vertex_new[0], vertex_new[1]};
    double phi_new = kinem::phi(vertex_old_vect, vertex_new_vect);
    
    // set new physics eta and phi for this EM cluster
    SetPtEtaPhiE(Pt(), eta_new, phi_new, E());
  } else {
    float b0 = sqrt( getPtrChp()->xdca()*getPtrChp()->xdca() + 
		     getPtrChp()->ydca()*getPtrChp()->ydca());
    float phi0 = getPtrChp()->Phi();
    
    float b_new=0., phi_new=0.;
    float kappa = 0.0015 * B_field/Pt(); 
    wz_utils::BeamSpotCorrection(b0, phi0, b_new, phi_new, kappa, distance_vertices);
    
    // set new physics eta and phi for this EM cluster
    SetPtEtaPhiE(Pt(), Eta(), phi_new, E());
  }
}

//pass L1 trigger requirement
// CEM(1, 10): EM_HI_SH, EM_HI
// CEM(1, 11): E1_SH30, E1_SHT22, E1_SHT20
// CEM(1, 12): E1_SHT25
// CSWEM(1, 19): E1_SHT25_IIb, E1_SHT27 (v15 and later)
 
// CEM(1, 15): EM_MX, EM_MX_SH
// CEM(2, 5):  EM_HI_2EM5_SH
// CEM(2, 6):  E2_SHT20, E2_SHT22
// CEM(1,9)CEM(2,3): E3_SHT20, E3_SHT22
int CAFEMObj::PassL1Trig(const char *name, double DeltaR_Cut, vector<const TMBL1CalTower*>& l1cal_vec,  vector<const TMBL1Cal2bEM*>& l1cal2b_vec) const {
  int pass = 0;
  if(strcmp(name, "EM_HI_SH")==0 || strcmp(name, "EM_HI")==0) 
    pass = PassL1_CEM(DeltaR_Cut, 10., l1cal_vec);
  else if(strcmp(name, "E1_SH30")==0 || strcmp(name, "E1_SHT22")==0 || strcmp(name, "E1_SHT20")==0) 
    pass = PassL1_CEM(DeltaR_Cut, 11., l1cal_vec);
  else if(strcmp(name, "E1_SHT25")==0 ) 
    pass = PassL1_CEM(DeltaR_Cut, 12., l1cal_vec);
  else if(strcmp(name, "E1_SHT25_v15")==0  || strcmp(name, "E1_SHT25_v16")==0 ||  strcmp(name, "E1_SHT27")==0 || strcmp(name, "E1_SHT25_v16t")==0 ||  strcmp(name, "E1_SHT27t")==0 ) 
    pass = PassL1_CSWEM(DeltaR_Cut, 19., l1cal2b_vec);
  else if(strcmp(name, "EM_MX")==0 || strcmp(name, "EM_MX_SH")==0) 
    pass = PassL1_CEM(DeltaR_Cut, 15., l1cal_vec);
  else if(strcmp(name, "EM_HI_2EM5_SH")==0) 
    pass = PassL1_CEM2(DeltaR_Cut, 5., l1cal_vec);
  else if(strcmp(name, "E2_SHT20")==0 || strcmp(name, "E2_SHT22")==0)  
    pass = PassL1_CEM2(DeltaR_Cut, 6., l1cal_vec);
  else if(strcmp(name, "E3_SHT20")==0 || strcmp(name, "E3_SHT22")==0) 
    pass = PassL1_CEM3(DeltaR_Cut, 9., 3., l1cal_vec);
  else 
    pass = 0;
  //  std::cout << "CAFEMObj::PassL1Trig returns " << pass << " for trigger name " << name <<  std::endl; 
  return pass;
}

//Pass L2 trigger requirement
// EM(1, 12): EM_HI_SH, EM_HI, EM_HI_2EM5_SH
// EM(1, 15): E1_SH30, E1_SHT22, E2_SHT22, E3_SHT22, E1_SHT25
// EM(1,19,X,0.4): E1_SHT25_IIb_v16, E1_SHT_27 (likelihood cut)
// EM(1,19,0.2): E1_SHT25_IIb_v15              (Iso Cut)
// EM(1,22): E1_SHT25_IIb_15, 
// EM(1,25): E1_SHT25_IIb_16, E1_SHT_27
// none for other trigger names  
int CAFEMObj::PassL2Trig(const char *name, double DeltaR_Cut, vector<const TMBL2GblEM*>& l2cal_vec) const {
  int pass = 0;

  if(strcmp(name, "EM_HI_SH")==0 || strcmp(name, "EM_HI")==0 || strcmp(name, "EM_HI_2EM5_SH")==0) 
    pass = PassL2_EM(DeltaR_Cut, 12., l2cal_vec);
  else if(strcmp(name, "E1_SH30")==0 || strcmp(name, "E1_SHT22")==0 || strcmp(name, "E2_SHT22")==0 ||
	  strcmp(name, "E3_SHT22")==0 || strcmp(name, "E1_SHT25")==0  ) 
    pass = PassL2_EM(DeltaR_Cut, 15., l2cal_vec);
  else if(strcmp(name, "EM_MX_SH")==0 || strcmp(name, "EM_MX")==0 || strcmp(name, "E1_SHT20")==0 ||
	  strcmp(name, "E2_SHT20")==0 || strcmp(name, "E3_SHT20")==0) 
    pass = true;
  else if (strcmp(name, "E1_SHT25_v15")==0) {
    int pass1 = PassL2_EM(DeltaR_Cut, 22., l2cal_vec);
    int pass2 = PassL2_EM_Iso(DeltaR_Cut, 19., 0.2, l2cal_vec) ;
    if (pass2)
      pass = pass2;
    else if (pass1)
      pass = pass1;
  }
  else  if (strcmp(name, "E1_SHT25_v16")==0  ||  strcmp(name, "E1_SHT27")==0){
    int pass1 = PassL2_EM(DeltaR_Cut, 25., l2cal_vec);
    int pass2 = PassL2_EM_lhood(DeltaR_Cut, 19., 0.4, l2cal_vec) ;
    if (pass2)
      pass = pass2;
    else if (pass1)
      pass = pass1;
  }
  else  if (strcmp(name, "E1_SHT25_v16t")==0  ||  strcmp(name, "E1_SHT27t")==0){
    int pass1 = PassL2_EM(DeltaR_Cut, 25., l2cal_vec);
    int pass2 = PassL2_EM_lhood(DeltaR_Cut, 19., 0.0, l2cal_vec) ;
    if (pass2)
      pass = pass2;
    else if (pass1)
      pass = pass1;
  }
  else
    pass = false;
  
  return pass;
}

//Pass L3 trigger requirement
// ELE_NLV_SHT(1,22): E1_SHT22, E2_SHT22, E3_SHT22
// ELE_NLV_SHT(1,25): E1_SHT25
// ELE_NLV_SHT(1,27): E1_SHT27
// ELE_NLV_SHT(1,20): E1_SHT20, E2_SHT20, E3_SHT20
// ELE_NLV_SH(1, 30): E1_SH30
// ELE_LOOSE_SH_T(1,20): EM_HI_SH, EM_MX_SH, EM_HI_2EM5_SH
// ELE_LOOSE(1, 30): EM_HI, EM_MX
//
bool CAFEMObj::PassL3Trig(const char *name, double DeltaR_Cut, vector<const TMBL3Ele*>& l3cal_vec) const {
  bool pass = false;

  if(strcmp(name, "E1_SHT22")==0 || strcmp(name, "E2_SHT22")==0 || strcmp(name, "E3_SHT22")==0) 
    pass = PassL3_ELE_NLV_SHT(DeltaR_Cut, 22., l3cal_vec);
  else if(strcmp(name, "E1_SHT25")==0 || strcmp(name, "E1_SHT25_v15")==0 || strcmp(name, "E1_SHT25_v16")==0  || strcmp(name, "E1_SHT25_v16t")==0   ) 
    pass = PassL3_ELE_NLV_SHT(DeltaR_Cut, 25., l3cal_vec);
  else if(strcmp(name, "E1_SHT27")==0 ||strcmp(name, "E1_SHT27t")==0  ) 
    pass = PassL3_ELE_NLV_SHT(DeltaR_Cut, 27., l3cal_vec);
  else if(strcmp(name, "E1_SHT20")==0 || strcmp(name, "E2_SHT20")==0 || strcmp(name, "E3_SHT20")==0)
    pass = PassL3_ELE_NLV_SHT(DeltaR_Cut, 20., l3cal_vec);
  else if(strcmp(name, "E1_SH30")==0) 
    pass = PassL3_ELE_NLV_SH(DeltaR_Cut, 30., l3cal_vec);
  else if(strcmp(name, "EM_HI_SH")==0 || strcmp(name, "EM_MX_SH")==0 || strcmp(name, "EM_HI_2EM5_SH")==0) 
    pass = PassL3_ELE_LOOSE_SH_T(DeltaR_Cut, 20., l3cal_vec);
  else if(strcmp(name, "EM_HI")==0 || strcmp(name, "EM_MX")==0) 
    pass = PassL3_ELE_LOOSE(DeltaR_Cut, 30., l3cal_vec);
  else 
    pass = false;
  
  return pass;
}

//pass L1, L2, L3 trigger requirement
bool CAFEMObj::PassL1L2L3Trig(const char *name, double DeltaR_Cut, vector<const TMBL1CalTower*>& l1cal_vec, vector<const TMBL1Cal2bEM*>& l1cal2b_vec, 
			      vector<const TMBL2GblEM*>& l2cal_vec, vector<const TMBL3Ele*>& l3cal_vec) const {
  bool passL1 = PassL1Trig(name, DeltaR_Cut, l1cal_vec, l1cal2b_vec);
  bool passL2 = PassL2Trig(name, DeltaR_Cut, l2cal_vec);
  bool passL3 = PassL3Trig(name, DeltaR_Cut, l3cal_vec);
  //cout<<"    Pass L1/L2/L3="<<passL1<<"/"<<passL2<<"/"<<passL3<<endl;
  return (passL1 && passL2 && passL3);
}

//pass any trigger combination 
bool CAFEMObj::PassTrigCMB(int triglist_flag, double DeltaR_Cut, vector<const TMBL1CalTower*>& l1cal_vec, vector<const TMBL1Cal2bEM*>& l1cal2b_vec,  
			   vector<const TMBL2GblEM*>& l2cal_vec, vector<const TMBL3Ele*>& l3cal_vec) const {
  bool pass_any = false;

  // for v8-10 and v11
  if(triglist_flag == 0 || triglist_flag == 1) {
    if(PassL1L2L3Trig("EM_HI_SH", DeltaR_Cut, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec))
      pass_any = true;
  } else if (triglist_flag == 2) {
    if(PassL1L2L3Trig("E1_SHT20", DeltaR_Cut, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec))
      pass_any = true;
  } else if (triglist_flag == 3) {
    if(PassL1L2L3Trig("E1_SHT22", DeltaR_Cut, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec))
      pass_any = true;
  } else if (triglist_flag == 4) {
    if(PassL1L2L3Trig("E1_SHT25", DeltaR_Cut, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec) )
      pass_any = true;  
  }
  else if (triglist_flag == 5) {
    if(PassL1L2L3Trig("E1_SHT25_v15", DeltaR_Cut, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec) )
      pass_any = true; 
  }
  else if (triglist_flag == 6) {
    if(PassL1L2L3Trig("E1_SHT25_v16", DeltaR_Cut, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec) )
      pass_any = true;  
    if(PassL1L2L3Trig("E1_SHT27", DeltaR_Cut, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec) )
      pass_any = true;  
  }
  else if (triglist_flag == 7) {
    if(PassL1L2L3Trig("E1_SHT27", DeltaR_Cut, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec) )
      pass_any = true;  
  }
  
  return pass_any;
}




//one L1 EM sliding window (RunIIb) passes certain Et cut
int CAFEMObj::PassL1_CSWEM(double DeltaR_Cut, double Et_Cut, vector<const TMBL1Cal2bEM*>& l1cal_vec) const {
  bool pass = false;
  for(int i=0; i<l1cal_vec.size() && !pass; i++) {
    if( (l1cal_vec[i]->Etem() -4.0)>Et_Cut ) {
      double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
      				 l1cal_vec[i]->Eta(), l1cal_vec[i]->Phi());
      if(dR<DeltaR_Cut){ pass = true;
	//std::cout << " CAFEMObj::PassL1_CSWEM returns: " << i+1 << " from a vector of size " << l1cal_vec.size() << " with i = " << i << std::endl;
	return (i+1);
      }
    }//pass l1 Et cut
  }//loop over all L1cal objects
  
  return pass;
}

//Hengne -- withEt, one L1 EM sliding window (RunIIb) passes certain Et cut
int CAFEMObj::PassL1_CSWEM_withEt(double DeltaR_Cut, double Et_Cut, vector<const TMBL1Cal2bEM*>& l1cal_vec, double& Et) const {
  bool pass = false;

  Et=-10000;
  for(int i=0; i<l1cal_vec.size() && !pass; i++) {
    double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(),
                               l1cal_vec[i]->Eta(), l1cal_vec[i]->Phi());
    if (dR<DeltaR_Cut) {
      double aet = (double)l1cal_vec.at(i)->Etem();
      if (aet>Et) Et = aet;
    }//pass dR 
  }//loop over all L1cal objects

  if (Et-4.0>Et_Cut) pass = true;
  return pass;
}

//one L1 EM tower passes certain Et cut
int CAFEMObj::PassL1_CEM(double DeltaR_Cut, double Et_Cut, vector<const TMBL1CalTower*>& l1cal_vec) const {
  bool pass = false;
  for(int i=0; i<l1cal_vec.size() && !pass; i++) {
    if( (l1cal_vec[i]->Et())>Et_Cut ) {
      double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
      				 l1cal_vec[i]->Eta(), l1cal_vec[i]->Phi());
      if(dR<DeltaR_Cut){ pass = true;
	return (i+1);
      }
    }//pass l1 Et cut
  }//loop over all L1cal objects
  
  return pass;
}



//two L1 EM towers pass certain Et cut (symmetric)
bool CAFEMObj::PassL1_CEM2(double DeltaR_Cut, double Et_Cut, vector<const TMBL1CalTower*>& l1cal_vec) const {
  bool pass = false;
  int NumPass = 0;
  for(int i=0; i<l1cal_vec.size(); i++) {
    if( (l1cal_vec[i]->Et())>Et_Cut ) {
      double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
				 l1cal_vec[i]->Eta(), l1cal_vec[i]->Phi());
      if(dR<DeltaR_Cut) NumPass++;
    }//pass l1 Et cut
  }//loop over all L1cal objects
  
  if(NumPass>=2) pass = true;
  return pass;
}

//two L1 EM towers pass certain cut (asymmetric)
bool CAFEMObj::PassL1_CEM3(double DeltaR_Cut, double Et_Cut1, double Et_Cut2, vector<const TMBL1CalTower*>& l1cal_vec) const {
  bool pass = false;
  
  // use a vector to store Et of the closest towers
  vector<double> Et_close_towers;  
  for(int i=0; i<l1cal_vec.size(); i++) {
    double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
			       l1cal_vec[i]->Eta(), l1cal_vec[i]->Phi());
    Et_close_towers.push_back(l1cal_vec[i]->Et());    
  }//loop over all L1cal objects
  
  // if at least two close towers
  int size_close_towers = Et_close_towers.size();
  if(size_close_towers>=2) {
    // sort tower Et
    sort(Et_close_towers.begin(), Et_close_towers.end());
    
    // get the minimum and maximum of Et_cut1 and Et_cut2
    double Et_Cut_min = min(Et_Cut1, Et_Cut2);
    double Et_Cut_max = max(Et_Cut1, Et_Cut2);
    
    // sort function sorts the vector in resverse direction
    if(Et_close_towers[size_close_towers-1]>=Et_Cut_max && Et_close_towers[size_close_towers-2]>=Et_Cut_min) 
      pass = true;
  }
  
  return pass;
}

//one L2 EM tower passes certain pt cut
int CAFEMObj::PassL2_EM(double DeltaR_Cut, double Et_Cut, vector<const TMBL2GblEM*>& l2cal_vec) const {
  bool pass = false;
  for(int i=0; i<l2cal_vec.size(); i++) {
    if((l2cal_vec[i]->Et())>Et_Cut) {
      double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
      				 l2cal_vec[i]->Eta(), l2cal_vec[i]->Phi());
      if(dR<DeltaR_Cut) {pass = true;
	return i+1;
      }
    }//pass l1 Et cut
  }//loop over all L1cal objects
  return pass;
}

//Hengne -- withEt, one L2 EM tower passes certain pt cut
int CAFEMObj::PassL2_EM_withEt(double DeltaR_Cut, double Et_Cut, vector<const TMBL2GblEM*>& l2cal_vec, double& Et) const {
  bool pass = false;
  Et = -10000;
  for(int i=0; i<l2cal_vec.size(); i++) {
    double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(),
                                 l2cal_vec[i]->Eta(), l2cal_vec[i]->Phi());
    if(dR<DeltaR_Cut) {
      double aet = (double)l2cal_vec.at(i)->Et();
      if (aet>Et) Et = aet;
    }//pass dR cut
  }//loop over all L1cal objects

  if (Et>Et_Cut) pass = true;
  return pass;
}

//two L2 EM towers pass certain Et cut (symmetric)
bool CAFEMObj::PassL2_2EM(double DeltaR_Cut, double Et_Cut, vector<const TMBL2GblEM*>& l2cal_vec) const {
  bool pass = false;
  int NumPass = 0;
  for(int i=0; i<l2cal_vec.size(); i++) {
    if( (l2cal_vec[i]->Et())>Et_Cut ) {
      double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
				 l2cal_vec[i]->Eta(), l2cal_vec[i]->Phi());
      if(dR<DeltaR_Cut) NumPass++;
    }//pass l1 Et cut
  }//loop over all L2cal objects
  
  if(NumPass>=2) pass = true;
  return pass;
}

//one L2 EM tower passes certain pt cut and isolation cut
int CAFEMObj::PassL2_EM_Iso(double DeltaR_Cut, double Et_Cut, double Iso_Cut, vector<const TMBL2GblEM*>& l2cal_vec) const {
  bool pass = false;
  for(int i=0; i<l2cal_vec.size(); i++) {
    if((l2cal_vec[i]->Et())>Et_Cut && l2cal_vec[i]->Iso()<Iso_Cut) {
      double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
      				 l2cal_vec[i]->Eta(), l2cal_vec[i]->Phi());
      if(dR<DeltaR_Cut){ pass = true;
	return i+1;
      }
    }//pass l1 Et cut
  }//loop over all L1cal objects
  return pass;
}

// Hengne -- withEt, one L2 EM tower passes certain pt cut and isolation cut
int CAFEMObj::PassL2_EM_Iso_withEt(double DeltaR_Cut, double Et_Cut, double Iso_Cut, vector<const TMBL2GblEM*>& l2cal_vec, double& Et) const {
  bool pass = false;
  Et = -10000;
  for(int i=0; i<l2cal_vec.size(); i++) {
    double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(),
                                 l2cal_vec[i]->Eta(), l2cal_vec[i]->Phi());
    if(dR<DeltaR_Cut && l2cal_vec.at(i)->Iso()<Iso_Cut){ 
      double aet = (double)l2cal_vec.at(i)->Et();
      if (aet>Et) Et = aet;
    }//pass dR and ISO cuts
  }//loop over all L1cal objects

  if(Et>Et_Cut) pass = true;

  return pass;
}

//one L2 EM tower passes certain pt cut and isolation cut
int CAFEMObj::PassL2_EM_lhood(double DeltaR_Cut, double Et_Cut, double lhood_Cut, vector<const TMBL2GblEM*>& l2cal_vec) const {
  int pass = 0;
  for(int i=0; i<l2cal_vec.size(); i++) {
    if((l2cal_vec[i]->Et())>Et_Cut && l2cal_vec[i]->EMLikelihood()>lhood_Cut) {
      double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
      				 l2cal_vec[i]->Eta(), l2cal_vec[i]->Phi());
      if(dR<DeltaR_Cut){ pass = i+1;
	return i+1;
      } 
    }//pass l1 Et cut
  }//loop over all L1cal objects
  return pass;
}

// Hengne -- withEt, one L2 EM tower passes certain pt cut and likelihood cut
int CAFEMObj::PassL2_EM_lhood_withEt(double DeltaR_Cut, double Et_Cut, double lhood_Cut, vector<const TMBL2GblEM*>& l2cal_vec, double& Et) const {
  bool pass = false;
  Et = -10000;
  for(int i=0; i<l2cal_vec.size(); i++) {
    double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(),
                                 l2cal_vec[i]->Eta(), l2cal_vec[i]->Phi());
    if(dR<DeltaR_Cut && l2cal_vec.at(i)->EMLikelihood()>lhood_Cut){
      double aet = (double)l2cal_vec.at(i)->Et();
      if (aet>Et) Et = aet;
    }//pass dR and lhood cuts
  }//loop over all L1cal objects

  if(Et>Et_Cut) pass = true;

  return pass;
}
//ELE_LOOSE_SH_T
bool CAFEMObj::PassL3_ELE_LOOSE_SH_T(double DeltaR_Cut, double Et_Cut, vector<const TMBL3Ele*>& l3cal_vec) const {
  bool pass = false;
  //  int algo_ELE_LOOSE_SH_T = 3;
  
  for (int i=0; i<l3cal_vec.size() && !pass; i++){     
    double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
			       l3cal_vec[i]->DetEta(), l3cal_vec[i]->Phi());    
    bool passes_shower = ((fabs(l3cal_vec[i]->Em1Width()) < 0.09) &&
			  (fabs(l3cal_vec[i]->Em2Width()) < 0.08) &&
			  (fabs(l3cal_vec[i]->Em3Width()) < 0.05));
    
    //    if ((dR<DeltaR_Cut) && (l3cal_vec[i]->L3Algo()==algo_ELE_LOOSE_SH_T) &&
    if ((dR<DeltaR_Cut) && (l3cal_vec[i]->Et()>Et_Cut) && (l3cal_vec[i]->Emf()>0.9) && passes_shower) 
      pass = true;
  }//loop over all l3calInfo  
  
  return pass;
}

//ELE_LOOSE
bool CAFEMObj::PassL3_ELE_LOOSE(double DeltaR_Cut, double Et_Cut, vector<const TMBL3Ele*>& l3cal_vec) const {
  bool pass = false;
  //  int algo_ELE_LOOSE = 1;
  
  for (int i=0; i<l3cal_vec.size() && !pass; i++){ 
    double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
			       l3cal_vec[i]->DetEta(), l3cal_vec[i]->Phi());   
    
    if ((dR<DeltaR_Cut) && (l3cal_vec[i]->Et()>Et_Cut) && (l3cal_vec[i]->Emf()>0.9) ) 
      pass = true;
  }//loop over all l3calinfo
  
  return pass;
}

//ELE_NLV_SHT
bool CAFEMObj::PassL3_ELE_NLV_SHT(double DeltaR_Cut, double Et_Cut, vector<const TMBL3Ele*>& l3cal_vec) const {
  bool pass = false;
  //  int algo_ELE_NLV_SHT = 8;
  
  for (int i=0; i<l3cal_vec.size() && !pass; i++) {
   
    double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
			       l3cal_vec[i]->DetEta(), l3cal_vec[i]->Phi());   
    
    bool passes_shower = false;
    if (fabs(CalDetectorEta()) > 1.3)
      passes_shower = ((fabs(l3cal_vec[i]->Em1RescWidth()) < 1.0) &&
		       (fabs(l3cal_vec[i]->Em2RescWidth()) < 1.0) &&
		       (fabs(l3cal_vec[i]->Em3RescWidth()) < 1.2));
    else 
      passes_shower = ((fabs(l3cal_vec[i]->Em1RescWidth()) < 1.8) &&
		       (fabs(l3cal_vec[i]->Em2RescWidth()) < 1.4) &&
		       (fabs(l3cal_vec[i]->Em3RescWidth()) < 1.15));
    
    if ((dR<DeltaR_Cut) && (l3cal_vec[i]->Et()>Et_Cut) && (l3cal_vec[i]->Emf()>0.9) && passes_shower) 
      pass = true;    
  }//loop over all l3calinfo
  
  return pass;
}

//Hengne -- withEt, ELE_NLV_SHT
bool CAFEMObj::PassL3_ELE_NLV_SHT_withEt(double DeltaR_Cut, double Et_Cut, vector<const TMBL3Ele*>& l3cal_vec, double& Et) const {
  bool pass = false;
  //  int algo_ELE_NLV_SHT = 8;

  Et = -10000;
  for (int i=0; i<l3cal_vec.size() && !pass; i++) {
    //cout << " -- Hengne :: l3cal->ToolName() is " << l3cal_vec.at(i)->ToolName() << endl;
    double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(),
                               l3cal_vec[i]->DetEta(), l3cal_vec[i]->Phi());

    bool passes_shower = false;
    if (fabs(CalDetectorEta()) > 1.3)
      passes_shower = ((fabs(l3cal_vec[i]->Em1RescWidth()) < 1.0) &&
                       (fabs(l3cal_vec[i]->Em2RescWidth()) < 1.0) &&
                       (fabs(l3cal_vec[i]->Em3RescWidth()) < 1.2));
    else
      passes_shower = ((fabs(l3cal_vec[i]->Em1RescWidth()) < 1.8) &&
                       (fabs(l3cal_vec[i]->Em2RescWidth()) < 1.4) &&
                       (fabs(l3cal_vec[i]->Em3RescWidth()) < 1.15));

    if ((dR<DeltaR_Cut) && (l3cal_vec[i]->Emf()>0.9) && passes_shower) {
      double aet = (double)l3cal_vec.at(i)->Et();
      if (aet>Et) Et = aet;
    }
  }//loop over all l3calinfo

  if (Et>Et_Cut) pass = true;
  return pass;
}

//ELE_NLV_SH
bool CAFEMObj::PassL3_ELE_NLV_SH(double DeltaR_Cut, double Et_Cut, vector<const TMBL3Ele*>& l3cal_vec) const {
  bool pass = false;
  //  int algo_ELE_NLV_SH = 7;
  
  for (int i=0; i<l3cal_vec.size() && !pass; i++) { 
    double dR = kinem::delta_R(CalDetectorEta(), CalDetectorPhi(), 
			       l3cal_vec[i]->DetEta(), l3cal_vec[i]->Phi());   
    bool passes_shower = false;
    if (fabs(CalDetectorEta()) > 1.3) 
      passes_shower = ((fabs(l3cal_vec[i]->Em1RescWidth()) < 1.4) &&
		       (fabs(l3cal_vec[i]->Em2RescWidth()) < 1.35) &&
		       (fabs(l3cal_vec[i]->Em3RescWidth()) < 1.4));
    else 
      passes_shower = ((fabs(l3cal_vec[i]->Em1RescWidth()) < 2.3) &&
		       (fabs(l3cal_vec[i]->Em2RescWidth()) < 1.7) &&
		       (fabs(l3cal_vec[i]->Em3RescWidth()) < 1.5));
    
    if ((dR<DeltaR_Cut) && (l3cal_vec[i]->Et()>Et_Cut) && (l3cal_vec[i]->Emf()>0.9) && passes_shower) 
      pass = true;
  }//loop over all l3calinfo

  return pass;
}

// sort emobjects according to pT
bool ComparePt(const CAFEMObj* emobj1, const CAFEMObj* emobj2) {
  return (emobj1->Pt()>emobj2->Pt());
}

bool ComparePtElec(const CAFEMObj* emobj1, const CAFEMObj* emobj2) {
  return (emobj1->Pt()>emobj2->Pt());
}

bool CAFEMObj::is_in_TrkPhiFid() const {
  bool outside_phi_crack=false;
  float phimod=fmod(_trkphiem3+0.1,kinem::PI/16.);
  outside_phi_crack=((phimod<0.1-0.02) || (phimod>0.1+0.02));
  return outside_phi_crack;
}

ClassImp(CAFEMObj)
