#include "wmass_util/CAFMet.hpp"
#include "tmb_tree/TMBCaloCell.hpp"
#include "wmass_util/CaloGeometryManager.hpp"
#include "wmass_util/WZ_Utils.hpp"
#include "kinem_util/AnglesUtil.hpp"

#include <iostream>
#include <map>

using namespace std;
using namespace cafe;

CAFMet::CAFMet() {
  _metx = _mety = _met = _scalarEt = 0.;
}

CAFMet::CAFMet(double metx, double mety, double met, double scalarEt) {
  _metx = metx;
  _mety = mety;
  _met = met;
  _scalarEt = scalarEt;
}

// revertexing and recalculate missingEt from all calorimeter cells 
void CAFMet::SetMet(cafe::Event& event, float vtx[3], std::map<std::pair<int,int>,int>* liste) {
  
  float metx_new=0., mety_new=0., met_new=0., scalarEt_new=0.;
  float metx_em=0., mety_em=0., met_em=0., scalarEt_em=0.;
  float metx_icd=0., mety_icd=0., met_icd=0., scalarEt_icd=0.;
  float metx_mg=0., mety_mg=0., met_mg=0., scalarEt_mg=0.;
  float metx_fh=0., mety_fh=0., met_fh=0., scalarEt_fh=0.;
  float metx_nada=0., mety_nada=0., met_nada=0., scalarEt_nada=0.;
  float metx_t42=0., mety_t42=0., met_t42=0., scalarEt_t42=0.;
  
  // get calorimeter geometry manager
  if(CaloGeometryManager::get_instance()) {
    
    const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
    const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");
    
    // loop over all calorimeter cells
    for(UInt_t icell=0; icell<cells->NumCells(); ++icell) {
      const TMBCaloCell *cell = cells->GetCell(icell);
      int ilyr = cell->layer();
      float E = cell->E();
      bool normalCell = cell->isNormalCell(); 
      // "SCA" killing
      if (liste) {
	pair<int,int> adr(cell->ieta(),cell->iphi());
	std::map<std::pair<int,int>,int>::iterator it = liste->find(adr);
	if (it!=liste->end()) normalCell=false;
      }

      // only look at positive cells and no CH layers and normal cells, will also remove ICD detector for final MET calculation
      if(E>=0. && ilyr<15 && normalCell) {
        int ieta = cell->ieta();
        int iphi = cell->iphi();
	int cell_index = wz_utils::EncodeCellIndex(ieta, iphi, ilyr);
	
	// calorimeter cell position
	float cell_pos[3] = {0., 0., 0.};
	map<int, CELLXYZ_STRUCT>::const_iterator iter = calogeometry_map.find(cell_index);
	if(iter != calogeometry_map.end()) {
	  cell_pos[0] = (*iter).second.x;
	  cell_pos[1] = (*iter).second.y;
	  cell_pos[2] = (*iter).second.z;	 

	  // -------------------------------------------------------
          double px_cell, py_cell, pT_cell;
	  wz_utils::RevertexCell( E, cell_pos, vtx, px_cell, py_cell, pT_cell);
          if(ilyr<=7) {
	    metx_em -= px_cell;
	    mety_em -= py_cell;
	    scalarEt_em += pT_cell;
	  } else if (ilyr==8 || ilyr==10) {
	    metx_mg -= px_cell;
	    mety_mg -= py_cell;
	    scalarEt_mg += pT_cell;	    
	  } else if (ilyr==9) {
	    metx_icd -= px_cell;
	    mety_icd -= py_cell;
	    scalarEt_icd += pT_cell;	    
	  } else {
	    metx_fh -= px_cell;
	    mety_fh -= py_cell;
	    scalarEt_fh += pT_cell;	    
	  }
	 
	  if(cell->isNadaCell()) {
	    metx_nada -= px_cell;
	    mety_nada -= py_cell;
	    scalarEt_nada += pT_cell;	    
	  } 

	  if(cell->isCalT42Cell()) {
	    metx_t42 -= px_cell;
	    mety_t42 -= py_cell;
	    scalarEt_t42 += pT_cell;	    
	  }

	  // for all positive cells, no CH layers and no ICD detector
	  if(ilyr!=9) {
	    metx_new -= px_cell;
	    mety_new -= py_cell;
	    scalarEt_new += pT_cell;
	  }
	} else {
	  //  do nothing now
	  //          cout<<"Can not find the position of this calorimeter cell, please investigate"<<endl;
	}
      }// positive cells and no CH layers
    } // loop over all cells
  } // get calorimeter geometry
  
  met_new = sqrt(metx_new*metx_new + mety_new*mety_new);
  met_em = sqrt(metx_em*metx_em + mety_em*mety_em);
  met_mg = sqrt(metx_mg*metx_mg + mety_mg*mety_mg);
  met_icd = sqrt(metx_icd*metx_icd + mety_icd*mety_icd);
  met_fh = sqrt(metx_fh*metx_fh + mety_fh*mety_fh);
  met_nada = sqrt(metx_nada*metx_nada + mety_nada*mety_nada);
  met_t42 = sqrt(metx_t42*metx_t42 + mety_t42*mety_t42);

/*
  cout<<"met_new: "<<metx_new<<" "<<mety_new<<" "<<met_new<<" "<<scalarEt_new<<endl;  
  cout<<"met_em: "<<metx_em<<" "<<mety_em<<" "<<met_em<<" "<<scalarEt_em<<endl;  
  cout<<"met_mg: "<<metx_mg<<" "<<mety_mg<<" "<<met_mg<<" "<<scalarEt_mg<<endl;  
  cout<<"met_icd: "<<metx_icd<<" "<<mety_icd<<" "<<met_icd<<" "<<scalarEt_icd<<endl;  
  cout<<"met_fh: "<<metx_fh<<" "<<mety_fh<<" "<<met_fh<<" "<<scalarEt_fh<<endl;  
  cout<<"met_nada: "<<metx_nada<<" "<<mety_nada<<" "<<met_nada<<" "<<scalarEt_nada<<endl;  
  cout<<"met_t42: "<<metx_t42<<" "<<mety_t42<<" "<<met_t42<<" "<<scalarEt_t42<<endl;  
*/

  SetMet(metx_new, mety_new, met_new, scalarEt_new);
  
  return;
}

void CAFMet::SetMet(double metx, double mety, double met, double scalarEt) {
  _metx = metx;
  _mety = mety;
  _met = met;
  _scalarEt = scalarEt;
}

CAFMet::CAFMet(double metx, double mety) {
  _metx = metx;
  _mety = mety;
  _met = sqrt(metx*metx+mety*mety);
}

CAFMet::~CAFMet() {}

ClassImp(CAFMet)
