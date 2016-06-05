#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include "wmass_analysis/SinglePhotonAnalysis.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "wmass_analysis/histograms.hpp"
#include "tmb_tree/TMBCaloCell.hpp"
#include "tmb_tree/TMBMCpart.hpp"
#include "cafe/Collection.hpp"
#include "wmass_util/CaloGeometryManager.hpp"
#include "wmass_util/WZ_Utils.hpp"
#include "tmb_tree/TMBMCevtInfo.hpp"
#include <TFile.h> 
#define CC_3R   91.9
#define CC_Z_MAX  115.0

using namespace std;
using namespace cafe;

SinglePhotonAnalysis::SinglePhotonAnalysis(const char *name)
  : Processor(name)
{
  Config config(name);

  //debug level
  _debugLevel = config.get("debugLevel", 0);

  //add histograms
  _histos.add(Photon_Hist1D);
  _histos.add(Photon_Hist2D);
  _histos.add(Photon_Profile);
  cellinfo.open("dump_cell.txt");
  _processed_events = 0;
}

void SinglePhotonAnalysis::CaloCellPos(const int& ieta, const int& iphi, const int& ilyr, double cell_pos[3]) {
  if(CaloGeometryManager::get_instance()) {
    const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
    int cell_index = wz_utils::EncodeCellIndex(ieta, iphi, ilyr);
    map<int, CELLXYZ_STRUCT>::const_iterator iter = calogeometry_map.find(cell_index);
    if(iter != calogeometry_map.end()) {
	  cell_pos[0] = (*iter).second.x;
	  cell_pos[1] = (*iter).second.y;
	  cell_pos[2] = (*iter).second.z;
    }
  }
}

// process 
bool SinglePhotonAnalysis::processEvent(cafe::Event& event) {
  bool is_fiducial = true;
  _processed_events++;
  cellinfo<<"---------------Event "<<_processed_events<<"-------------------"<<endl;
  //get mc objects from the event
  double gen_photon_E = 0.;
  double gen_photon_eta = 0.;
  double gen_photon_phi = 0.;
  double gen_photon_vtx[3] = {0., 0., 0.};
  double gen_photon_vtx2[2] = {0., 0.};
  int counter = 0;
  Collection<TMBMCpart> mc = event.getMCParticles();
  for (Collection<TMBMCpart>::iterator it = mc.begin(); it!= mc.end(); ++it) {
    if (it->abspdgid() == 22){
      gen_photon_E = it->E();
      gen_photon_eta = it->Eta();
      gen_photon_phi = it->Phi();
      cellinfo<<"gen level photon E = "<<gen_photon_E<<" eta = "<<gen_photon_eta<<" phi = "<<gen_photon_phi<<endl;
      counter++;
      _histos.Fill1D("Gen_Photon_Eta", gen_photon_eta);
      _histos.Fill1D("Gen_Photon_Phi", gen_photon_phi);
      // find the MC primary vtx of the photon
     
      if ( const TMBMCvtx *vtx = it->getPMCvtx() ) {
	gen_photon_vtx[0] = vtx->x();
	gen_photon_vtx[1] = vtx->y();
	gen_photon_vtx[2] = vtx->z();
	gen_photon_vtx2[0] = gen_photon_vtx[0];
	gen_photon_vtx2[1] = gen_photon_vtx[1];
      }
      else {
	if (_debugLevel>5) cout<<"cannot find the decay vtx of this photon"<<endl;
      }     
    }// if MC particle is a photon
  }
  _histos.Fill1D("Gen_Photon_Num", counter);
  
  /*
    const TMBMCevtInfo *mc_info = event.getMCEventInfo();
    gen_photon_vtx[0] = mc_info->getmcPV_x();
    gen_photon_vtx[1] = mc_info->getmcPV_y();
    gen_photon_vtx[2] = mc_info->getmcPV_z();
xsxs    gen_photon_vtx2[0] = gen_photon_vtx[0];
    gen_photon_vtx2[1] = gen_photon_vtx[1];
  */
  
  _histos.Fill1D("Gen_Photon_VtxZ", gen_photon_vtx[2]);

  double theta = kinem::theta(gen_photon_eta);
  double z3EM = gen_photon_vtx[2]+CC_3R/tan(theta);

  if (z3EM>CC_Z_MAX) return false;

  // get the calorimeter cells
  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");
  if (cells==NULL) cout<<"cannot find any cells in this event"<<endl;
  // loop over all calorimeter cells
  int num_cells = cells->NumCells();
  _histos.Fill1D("NumCells", num_cells);
  double sum_E = 0.;
  bool reach_calo = false;
  bool reach03_calo = false; 
  for(UInt_t icell=0; icell<num_cells; ++icell) {
    const TMBCaloCell *cell = cells->GetCell(icell);
    float E = cell->E();
    const int ilyr = cell->layer();
    const int ieta = cell->ieta();
    const int iphi = cell->iphi();
    bool normalCell = cell->isNormalCell();
    // only look at positive cells and EM+FH1 cells 
    if(E>=0. && ((ilyr<8)||(ilyr==11)) && normalCell) {
      reach_calo = true;
      double pos[3] = {0., 0., 0.,};
      double pos2[2] = {0., 0.};
      CaloCellPos(ieta, iphi, ilyr, pos);
      if (_debugLevel>5) cout<<"pos[0]="<<pos[0]<<" pos[1]="<<pos[1]<<" pos[2]="<<pos[2]<<endl;
      pos2[0] = pos[0];
      pos2[1] = pos[1];
      double cell_eta = kinem::eta(gen_photon_vtx, pos);
      double cell_phi = kinem::phi(gen_photon_vtx2, pos2);
      double dR = kinem::delta_R(gen_photon_eta, gen_photon_phi, cell_eta, cell_phi);
      if(dR<0.3) {
	if ((ieta>11)||(ieta<-11)) is_fiducial = false;
	reach03_calo = true;
	sum_E += E;
	cellinfo<<"cell_E = "<<E<<" eta = "<<cell_eta<<" phi = "<<cell_phi
		<<" dR = "<<dR<<" ieta = "<<ieta<< " iphi = "<<iphi<<" ilyr = "<<ilyr<<endl;
      }
      else cellinfo<<"******cell_E = "<<E<<" eta = "<<cell_eta<<" phi = "<<cell_phi
		   <<" dR = "<<dR<<" ieta = "<<ieta<< " iphi = "<<iphi<<" ilyr = "<<ilyr<<"********"<<endl;
    }
  } // loop over all calo cells 
  cellinfo<<" sum of E for all cells dR<0.3 = "<<sum_E<<endl;
  double resp = sum_E/gen_photon_E;

  if (is_fiducial) {
    if (reach03_calo && sum_E>0.){
      _histos.FillProfile("Photon_Response03", gen_photon_E, resp);
      _histos.Fill2D("Photon_Response03_scatter", gen_photon_E, resp);
    }
    if (reach_calo && sum_E>0.){
      _histos.FillProfile("Photon_Response", gen_photon_E, resp);
      _histos.Fill2D("Photon_Response_scatter", gen_photon_E, resp);
    }
  
    _histos.Fill1D("Gen_Photon_Energy", gen_photon_E);
    if(reach_calo) _histos.Fill1D("Gen_Photon_Energy_reach", gen_photon_E);
    if(reach03_calo) _histos.Fill1D("Gen_Photon_Energy_reach03", gen_photon_E);
  }
  return true;   
}

void SinglePhotonAnalysis::begin() {}

void SinglePhotonAnalysis::finish() {
 TFile *file = histfiles::initializeTFile( this );
 if(file==NULL) return;
 string directory_name("SinglePhoton_Hist");
 file->mkdir(directory_name.c_str());
 _histos.save(file, directory_name);
 file->Close();
 cellinfo.close();
}

ClassImp(SinglePhotonAnalysis)
