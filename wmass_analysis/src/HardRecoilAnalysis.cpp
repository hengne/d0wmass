//Author: Rafael Lopes de Sa
//Date: 11/May/2013

//C++
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cassert>
#include <algorithm>   

//Cafe stuff
#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Variables.hpp"

//Other packages
#include "tmb_tree/TMBEMCluster.hpp"
#include "tmb_tree/TMBCaloCell.hpp"
#include "tmb_tree/TMBCellContainer.hpp"
#include "wmass_util/EMClusterPosCorr.hpp"
#include "wmass_util/CaloGeometryManager.hpp"
#include "wmass_util/WZ_Utils.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "wmass_util/CAFMet.hpp"
#include "kinem_util/AnglesUtil.hpp"

//This code
#include "wmass_analysis/HardRecoilAnalysis.hpp"

//ROOT
#include "TMath.h"
#include "TFile.h"
#include "TChain.h"

using namespace std;
using namespace cafe;

HardRecoilAnalysis::HardRecoilAnalysis(const char *name) : Processor(name) {

  Config config(name);

  //debug level
  _debugLevel = config.get("debugLevel", 0);

  // Analysis requirements
  _NuLoose_nMin   = config.get("ZNuNu_NuLoose_nMin",   2);       // require >=2 loose neutrionos
  _NuLoose_EtaMax = config.get("ZNuNu_NuLoose_EtaMax", 2.5);  // no cut
  _NuLoose_PtMin  = config.get("ZNuNu_NuLoose_PtMin",  0.0);     // no cut
  _NuTight_nMin   = config.get("ZNuNu_NuTight_nMin",   0);       // no cut
  _NuTight_EtaMax = config.get("ZNuNu_NuTight_EtaMax", 2.5);  // no cut
  _NuTight_PtMin  = config.get("ZNuNu_NuTight_PtMin",  0.0);     // no cut
  _PtCutMin       = config.get("ZNuNu_PtCutMin",       0.0);     // no cut
  _PtCutMax       = config.get("ZNuNu_PtCutMax",       10000.0); // no cut
  _UtCutMin       = config.get("ZNuNu_UtCutMin",       0.0);     // no cut
  _UtCutMax       = config.get("ZNuNu_UtCutMax",       10000.0); // no cut
  _SETCutMin      = config.get("ZNuNu_SETCutMin",      0.0);     // no cut
  _SETCutMax      = config.get("ZNuNu_SETCutMax",      10000.0); // no cut
  _LumiCutMin     = config.get("ZNuNu_LumiCutMin",     0.0);     // no cut
  _LumiCutMax     = config.get("ZNuNu_LumiCutMax",     10000.0); // no cut
  cout << "HardRecoilAnalysis configuration:  " << endl;
  cout << "   _NuLoose_nMin:   " << _NuLoose_nMin << endl
       << "   _NuLoose_EtaMax: " << _NuLoose_EtaMax << endl
       << "   _NuLoose_PtMin:  " << _NuLoose_PtMin << endl
       << "   _NuTight_nMin:   " << _NuTight_nMin << endl
       << "   _NuTight_EtaMax: " << _NuTight_EtaMax << endl
       << "   _NuTight_PtMin:  " << _NuTight_PtMin << endl
       << "   _PtCutMin:       " << _PtCutMin << endl
       << "   _PtCutMax:       " << _PtCutMax << endl
       << "   _UtCutMin:       " << _UtCutMin << endl
       << "   _UtCutMax:       " << _UtCutMax << endl
       << "   _SETCutMin:      " << _SETCutMin << endl
       << "   _SETCutMax:      " << _SETCutMax << endl
       << "   _LumiCutMin:     " << _LumiCutMin << endl
       << "   _LumiCutMax:     " << _LumiCutMax << endl;
  if(( _NuTight_PtMin < _NuLoose_PtMin ) || ( _NuTight_EtaMax > _NuLoose_EtaMax )) {
    cerr << "HardRecoilAnalysis: Wrong specification of Loose and Tight cuts!!!" << endl
	 << "                    pT(Loose nu)>=" << _NuLoose_PtMin << " GeV, |eta(Loose nu)|<" << _NuLoose_EtaMax << endl
	 << "                    pT(Tight nu)>=" << _NuTight_PtMin << " GeV, |eta(Tight nu)|<" << _NuTight_EtaMax << endl;
    assert(0);
  }
    
  //MC study
  _MCStudy = config.get("MCStudy", false);
  
  // ZB vertex?
  _useMCvertex = config.get("useMCvertex", false);
  
  //Which type of run
  _ZBrun = config.get("Znunu_ZBrun", true);
  _ZBfileName = config.get("Znunu_ZBfileName", "Znunu_ZBrun.root");
  _ZBrunList = config.get("Znunu_ZBrunList", "Znunu_ZBrunList.list");
  
  cout << "Starting HardRecoil Analysis" << endl;


  if (_ZBrun) {
    
    _ZBFile = new TFile(_ZBfileName, "RECREATE");
    _ZBTree = new TTree("zbrun", "zbrun");

    _ZBTree->Branch("ZBrunNum",&_ZBrunNum, "ZBrunNum/I");
    _ZBTree->Branch("ZBeventNum",&_ZBeventNum, "ZBeventNum/I");
    _ZBTree->Branch("ZBncells", &_ZBncells, "ZBncells/I");
    _ZBTree->Branch("ZBnormal", _ZBnormal, "ZBnormal[ZBncells]/O");
    _ZBTree->Branch("ZBieta", _ZBieta, "ZBieta[ZBncells]/I");
    _ZBTree->Branch("ZBiphi", _ZBiphi, "ZBiphi[ZBncells]/I");
    _ZBTree->Branch("ZBlayer", _ZBlayer, "ZBlayers[ZBncells]/I");
    _ZBTree->Branch("ZBenergy", _ZBenergy, "ZBenergy[ZBncells]/D");
    _ZBTree->Branch("tickNum", &_tickNum, "tickNum/D");

    initKillList();

  }

  if (!_ZBrun) {

    _numZBLib = 0;
    ifstream filelist(_ZBrunList.Data());
    TString _tfilename;
    Long64_t nentries = 0;
    while (!filelist.eof()) {
      _tfilename.ReadLine(filelist);
      cout << "Reading " << _tfilename.Data() << endl;
      _ZBLibraryFile[_numZBLib] = new TFile(_tfilename);
      _ZBLibrary[_numZBLib] = (TTree*) _ZBLibraryFile[_numZBLib]->Get("zbrun");
      _ZBLibrary[_numZBLib]->SetBranchAddress("ZBrunNum", &_ZBrunNum);
      _ZBLibrary[_numZBLib]->SetBranchAddress("ZBeventNum", &_ZBeventNum);
      _ZBLibrary[_numZBLib]->SetBranchAddress("ZBnormal", _ZBnormal);
      _ZBLibrary[_numZBLib]->SetBranchAddress("ZBieta", _ZBieta);
      _ZBLibrary[_numZBLib]->SetBranchAddress("ZBiphi", _ZBiphi);
      _ZBLibrary[_numZBLib]->SetBranchAddress("ZBlayer", _ZBlayer);
      _ZBLibrary[_numZBLib]->SetBranchAddress("ZBenergy", _ZBenergy);
      _ZBLibrary[_numZBLib]->SetBranchAddress("ZBncells", &_ZBncells);
      _ZBLibrary[_numZBLib]->SetBranchAddress("tickNum", &_tickNum);
      cout << "Building Index " << _ZBLibrary[_numZBLib]->BuildIndex("ZBrunNum", "ZBeventNum") << endl;
      cout << _ZBLibrary[_numZBLib]->GetEntries() << endl;
      nentries += _ZBLibrary[_numZBLib]->GetEntries();
      _numZBLib++;
      
      if (_numZBLib == 120) {
	cout << "This is the last ZB file I will read. Why do you have more files than allowed CAFE jobs?" << endl;
	break;
      }
    }
    cout << "I found " << nentries << " events." << endl;
    filelist.close();
      

    // Output file and tree
    _HardRecoilFile = new TFile("HardRecoilAnalysis.root", "RECREATE");
    _HardRecoilTree = new TTree("hardrecoil", "hardrecoil");
    
    //The run and event numbers
    _HardRecoilTree->Branch("runNum",&_runNum,"runNum/I");
    _HardRecoilTree->Branch("eventNum",&_eventNum,"eventNum/I");
    
    _HardRecoilTree->Branch("ZBrunNum",&_ZBrunNum, "ZBrunNum/I");
    _HardRecoilTree->Branch("ZBeventNum",&_ZBeventNum, "ZBeventNum/I");

    //Global variables
    _HardRecoilTree->Branch("lumi", &_lumi, "lumi/D");
    _HardRecoilTree->Branch("SET", &_SET, "SET/D");
    _HardRecoilTree->Branch("ZBSET", &_ZBSET, "ZBSET/D");
    _HardRecoilTree->Branch("bothSET", &_bothSET, "bothSET/D");
    _HardRecoilTree->Branch("tickNum", &_tickNum, "tickNum/D");
    
    // Z true momentum
    _HardRecoilTree->Branch("Ztruepx", &_Ztruepx, "Ztruepx/D");
    _HardRecoilTree->Branch("Ztruepy", &_Ztruepy, "Ztruepy/D");
    _HardRecoilTree->Branch("Ztruepz", &_Ztruepz, "Ztruepz/D");
    _HardRecoilTree->Branch("ZtrueE", &_ZtrueE, "ZtrueE/D");
    
    // Generate recoil
    _HardRecoilTree->Branch("utruepx", &_utruepx, "utruepx/D");
    _HardRecoilTree->Branch("utruepy", &_utruepy, "utruepy/D");
    _HardRecoilTree->Branch("utruepz", &_utruepz, "utruepz/D");
    _HardRecoilTree->Branch("utrueE", &_utrueE, "utrueE/D");
    
    // Reconstructed recoil
    _HardRecoilTree->Branch("urecopx", &_urecopx, "urecopx/D");
    _HardRecoilTree->Branch("urecopy", &_urecopy, "urecopy/D");
    _HardRecoilTree->Branch("urecopT", &_urecopT, "urecopT/D");
    _HardRecoilTree->Branch("urecophi", &_urecophi, "urecophi/D");

    // Reconstructed recoil
    _HardRecoilTree->Branch("uzbpx", &_uzbpx, "uzbpx/D");
    _HardRecoilTree->Branch("uzbpy", &_uzbpy, "uzbpy/D");
    _HardRecoilTree->Branch("uzbpT", &_uzbpT, "uzbpT/D");
    _HardRecoilTree->Branch("uzbphi", &_uzbphi, "uzbphi/D");

    // Reconstructed recoil
    _HardRecoilTree->Branch("ubothpx", &_ubothpx, "ubothpx/D");
    _HardRecoilTree->Branch("ubothpy", &_ubothpy, "ubothpy/D");
    _HardRecoilTree->Branch("ubothpT", &_ubothpT, "ubothpT/D");
    _HardRecoilTree->Branch("ubothphi", &_ubothphi, "ubothphi/D");
    

    initKillList();
  }
    
}

bool HardRecoilAnalysis::processEvent(cafe::Event& event) {
  
  //This analysis only makes sense for MC
  if (!_MCStudy) return 0;

  if (_ZBrun) {

    _ZBrunNum = event.getMCEventInfo()->overlayrun();
    _ZBeventNum = event.getMCEventInfo()->overlayevtid();
    _tickNum = event.getMCEventInfo()->overlaytick();
         
    const TMBCellContainer *calocells = event.get<TMBCellContainer>("CaloCells");
    if (!calocells) return 0;

    _ZBncells=0;
    for(UInt_t icell=0; icell<calocells->NumCells(); ++icell) {
      const TMBCaloCell *cell = calocells->GetCell(icell);
      if (!cell) continue;
      _ZBnormal[_ZBncells] = cell->isNormalCell();
      _ZBlayer[_ZBncells] = cell->layer();
      _ZBieta[_ZBncells] = cell->ieta();
      _ZBiphi[_ZBncells] = cell->iphi();
      _ZBenergy[_ZBncells] = cell->E();
      _ZBncells++;
    }

    _ZBTree->Fill();
  }

  if (!_ZBrun) {

    // Containers
    TMBMCpart *mc_Z;
    TMBMCpart *mc_Recoil;
    vector<TMBMCpart *> mc_neutrinos; 

    // Retrieves the information
    if(!( event.get("mc neutrinos", mc_neutrinos)        && 
	  mc_neutrinos.size()>=2                         &&
	  event.get("WZ boson object", mc_Z)             &&
	  event.get("mc recoil object", mc_Recoil)       &&
	  event.get("InstLumi", _lumi))) return 0;
    
    Float_t mcvtxx, mcvtxy, mcvtxz;
    cafe::Collection<TMBMCvtx> mcvtx = event.getMCVertices();
    Float_t _mcvtx[] = {mcvtx[0].x(), mcvtx[0].y(), mcvtx[0].z()};

    if (!_useMCvertex) {
      if (!(event.get("Best primary vertexX", _mcvtx[0]) &&
	    event.get("Best primary vertexY", _mcvtx[1]) &&
	    event.get("Best primary vertexZ", _mcvtx[2]))) return 0;
    }
        
    // # of good MC level neutrinos
    Int_t nTightNeutrinos = 0; 
    Int_t nLooseNeutrinos = 0;
    
    // check generator level neutrinos from Z
    for (std::vector<TMBMCpart *>::iterator it = mc_neutrinos.begin(); it!= mc_neutrinos.end(); ++it) {
      if( TMath::Abs((*it)->Eta())<_NuLoose_EtaMax && (*it)->Pt()>_NuLoose_PtMin) nLooseNeutrinos++;
      if( TMath::Abs((*it)->Eta())<_NuTight_EtaMax && (*it)->Pt()>_NuTight_PtMin) nTightNeutrinos++;
    }
    
    // The overlaid event
    Int_t ZBrunNum = event.getMCEventInfo()->overlayrun();
    Int_t ZBeventNum = event.getMCEventInfo()->overlayevtid();
    _runNum = event.getGlobal()->runno();
    _eventNum = event.getGlobal()->evtno();
    
    // Assigns the variables
    _ZtrueE = mc_Z->E();
    _Ztruepx = mc_Z->Px();
    _Ztruepy = mc_Z->Py();
    _Ztruepz = mc_Z->Pz();

    _utrueE = mc_Recoil->E();
    _utruepx = mc_Recoil->Px();
    _utruepy = mc_Recoil->Py();
    _utruepz = mc_Recoil->Pz();
    

    Bool_t foundZB = false;
    for (Int_t i=0; i<_numZBLib; i++) {
      Int_t ZBentry = _ZBLibrary[i]->GetEntryNumberWithIndex(ZBrunNum, ZBeventNum);
      if (ZBentry >= 0) {
	_ZBLibrary[i]->GetEntry(ZBentry);
	foundZB = true;
	break;
      }
    }
    if (!foundZB) {
      //      cout << "ZB not found" << endl;
      return 0;   
    }
    //    cout << "Found ZB" << endl;
 
    TVector2 _ureco = GetSubtractedRecoil(event, _ZBncells, _ZBieta, _ZBiphi, _ZBlayer, _ZBenergy, _ZBnormal, _mcvtx, _SET);
   
    _urecopx = _ureco.Px(); 
    _urecopy = _ureco.Py(); 
    _urecopT = _ureco.Mod();
    _urecophi = TVector2::Phi_0_2pi(_ureco.Phi());

    TVector2 _uboth = GetSubtractedRecoil(event, _ZBncells, _ZBieta, _ZBiphi, _ZBlayer, _ZBenergy, _ZBnormal, _mcvtx, _bothSET, false);
    
    _ubothpx = _uboth.Px(); 
    _ubothpy = _uboth.Py(); 
    _ubothpT = _uboth.Mod();
    _ubothphi = TVector2::Phi_0_2pi(_uboth.Phi());

    TVector2 _uzb = GetRecoil(event, _ZBncells, _ZBieta, _ZBiphi, _ZBlayer, _ZBenergy, _ZBnormal, _mcvtx, _ZBSET);

    _uzbpx = _uzb.Px(); 
    _uzbpy = _uzb.Py(); 
    _uzbpT = _uzb.Mod();
    _uzbphi = TVector2::Phi_0_2pi(_uzb.Phi());

    //    cout << _ZBSET << " " << _uzbpT << endl;
    
    // Kinematical cuts
    if (!(nLooseNeutrinos >= _NuLoose_nMin &&
	  nTightNeutrinos >= _NuTight_nMin &&
	  _SET < _SETCutMax &&
	  _SET >= _SETCutMin &&
	  _lumi < _LumiCutMax &&
	  _lumi >= _LumiCutMin &&
	  _urecopT >= _UtCutMin &&
	  _urecopT < _UtCutMax &&
	  mc_Z->Pt() >= _PtCutMin &&
	  mc_Z->Pt() < _PtCutMax)) return 0;


    //    cout << "Writing" << endl;
    _HardRecoilTree->Fill();
  }
  
  return true;
  
}

void HardRecoilAnalysis::finish() {


  if (_ZBrun) {
    _ZBFile->Write();
    _ZBFile->Close();
  }

  if (!_ZBrun) {  
    _HardRecoilFile->Write();
    _HardRecoilFile->Close();
    for (Int_t i=0; i<_numZBLib; i++)
      _ZBLibraryFile[i]->Close();
  }
}

TVector2 HardRecoilAnalysis::GetSubtractedRecoil(Event& event, Int_t zbncells, Int_t* zbieta, Int_t* zbiphi, Int_t* zblayer, Double_t* zbenergy, Bool_t* zbnormal, Float_t vtx[3], Double_t& SET, Bool_t subtract) {

  Double_t ux_em=0., uy_em=0., u_em=0., uz_em=0, scalarEt_em=0.;
  Double_t ux_icd=0., uy_icd=0., u_icd=0., uz_icd=0, scalarEt_icd=0.;
  Double_t ux_mg=0., uy_mg=0., u_mg=0., uz_mg=0, scalarEt_mg=0.;
  Double_t ux_fh=0., uy_fh=0., u_fh=0., uz_fh=0, scalarEt_fh=0.;

  // Fet calorimeter geometry manager
  const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
  TMBCellContainer *cells = const_cast<TMBCellContainer *>(event.get<TMBCellContainer>("CaloCells"));

  int ZBrunNum = event.getMCEventInfo()->overlayrun();
  for(UInt_t icell=0; icell<cells->NumCells(); ++icell) {

    const TMBCaloCell *cell = cells->GetCell(icell);
    if (!cell) continue;
    if (!cell->isNormalCell()) continue;
    if (cell->E() < 0) cout << "RCLSA NEGATIVE ENERGY" << endl;
    Int_t ilyr = cell->layer();
    Int_t ieta = cell->ieta();
    Int_t iphi = cell->iphi();
    if (isBadSCA(ZBrunNum, ieta, iphi)) continue;

    Double_t ZBsub = 0;
    if (subtract) {
      for (Int_t zbcell=0; zbcell < zbncells; zbcell++) {
	if (ilyr == zblayer[zbcell] && ieta == zbieta[zbcell] && iphi == zbiphi[zbcell] && zbnormal[zbcell]) {
	  ZBsub = zbenergy[zbcell];
	  break;
	}
      }
    }
    Double_t dE = cell->E() - ZBsub;

    if (ilyr >=15) continue;                                

    Int_t cell_index = wz_utils::EncodeCellIndex(ieta, iphi, ilyr);

    // calorimeter cell position
    map<int, CELLXYZ_STRUCT>::const_iterator iter = calogeometry_map.find(cell_index);
    if(iter != calogeometry_map.end()) {
      // Found it!
      const CELLXYZ_STRUCT cellgeo = (*iter).second;

      // calculate px py pz of a given cell 
      float cell_loc[3] = { cellgeo.x, cellgeo.y, cellgeo.z };
      double px_cell, py_cell, pT_cell;
      wz_utils::RevertexCell(dE, cell_loc, vtx, px_cell, py_cell, pT_cell);


      if(ilyr<=7) {
	ux_em += px_cell;
	uy_em += py_cell;
	scalarEt_em += pT_cell;
      } else if (ilyr==8 || ilyr==10) {
	ux_mg += px_cell;
	uy_mg += py_cell;
	scalarEt_mg += pT_cell;
      } else if (ilyr==9) {
	ux_icd += px_cell;
	uy_icd += py_cell;
	scalarEt_icd += pT_cell;
      } else if (ilyr >= 11) {
	ux_fh += px_cell;
	uy_fh += py_cell;
	scalarEt_fh += pT_cell;
      }
    }    // Calorimeter cells
  }      // Calorimeter geometry

  u_em = sqrt(ux_em*ux_em + uy_em*uy_em);
  u_mg = sqrt(ux_mg*ux_mg + uy_mg*uy_mg);
  u_icd = sqrt(ux_icd*ux_icd + uy_icd*uy_icd);
  u_fh = sqrt(ux_fh*ux_fh + uy_fh*uy_fh);

  // no ICD
  TVector2 uVec(ux_em + ux_mg + ux_fh, uy_em + uy_mg + uy_fh);
  SET = scalarEt_em + scalarEt_mg + scalarEt_fh;
  return uVec;
}

TVector2 HardRecoilAnalysis::GetRecoil(Event& event, Int_t zbncells, Int_t* zbieta, Int_t* zbiphi, Int_t* zblayer, Double_t* zbenergy, Bool_t* zbnormal, Float_t vtx[3], Double_t& SET) {

  Double_t ux_em=0., uy_em=0., u_em=0., uz_em=0, scalarEt_em=0.;
  Double_t ux_icd=0., uy_icd=0., u_icd=0., uz_icd=0, scalarEt_icd=0.;
  Double_t ux_mg=0., uy_mg=0., u_mg=0., uz_mg=0, scalarEt_mg=0.;
  Double_t ux_fh=0., uy_fh=0., u_fh=0., uz_fh=0, scalarEt_fh=0.;

  // Fetch calorimeter geometry manager
  const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
  
  int ZBrunNum = event.getMCEventInfo()->overlayrun();
  for(Int_t icell=0; icell<zbncells; ++icell) {
    if (!zbnormal[icell]) continue;
    Int_t ilyr = zblayer[icell];
    Int_t ieta = zbieta[icell];
    Int_t iphi = zbiphi[icell];
    if (isBadSCA(ZBrunNum, ieta, iphi)) continue;
    Double_t dE = zbenergy[icell];
    
    if (ilyr >=15) continue;                                

    Int_t cell_index = wz_utils::EncodeCellIndex(ieta, iphi, ilyr);

    // calorimeter cell position
    map<int, CELLXYZ_STRUCT>::const_iterator iter = calogeometry_map.find(cell_index);
    if(iter != calogeometry_map.end()) {
      // Found it!
      const CELLXYZ_STRUCT cellgeo = (*iter).second;

      // calculate px py pz of a given cell 
      float cell_loc[3] = { cellgeo.x, cellgeo.y, cellgeo.z };
      double px_cell, py_cell, pT_cell;
      wz_utils::RevertexCell(dE, cell_loc, vtx, px_cell, py_cell, pT_cell);

      if(ilyr<=7) {
	ux_em += px_cell;
	uy_em += py_cell;
	scalarEt_em += pT_cell;
      } else if (ilyr==8 || ilyr==10) {
	ux_mg += px_cell;
	uy_mg += py_cell;
	scalarEt_mg += pT_cell;
      } else if (ilyr==9) {
	ux_icd += px_cell;
	uy_icd += py_cell;
	scalarEt_icd += pT_cell;
      } else if (ilyr >= 11) {
	ux_fh += px_cell;
	uy_fh += py_cell;
	scalarEt_fh += pT_cell;
      }
    }    // Calorimeter cells
  }      // Calorimeter geometry

  u_em = sqrt(ux_em*ux_em + uy_em*uy_em);
  u_mg = sqrt(ux_mg*ux_mg + uy_mg*uy_mg);
  u_icd = sqrt(ux_icd*ux_icd + uy_icd*uy_icd);
  u_fh = sqrt(ux_fh*ux_fh + uy_fh*uy_fh);

  // no ICD
  TVector2 uVec(ux_em + ux_mg + ux_fh, uy_em + uy_mg + uy_fh);
  SET = scalarEt_em + scalarEt_mg + scalarEt_fh;
  return uVec;
}

Bool_t HardRecoilAnalysis::isBadSCA(Int_t ZBrunNum, Int_t ieta, Int_t iphi) {

  for (_killcells_it = _killcells.begin(); _killcells_it < _killcells.end(); _killcells_it++) {
    if (ZBrunNum >= (*_killcells_it)[0] && ZBrunNum <= (*_killcells_it)[1] && ieta == (*_killcells_it)[2] && iphi == (*_killcells_it)[3])
      return true;
  }
  return false;
}

void HardRecoilAnalysis::initKillList() {
  
  int initRun[17] = {262375, 257412, 257158, 257644, 261613, 255384, 257891, 258151, 262127, 275016, 270063, 270063, 274399, 273384, 272679, 268995, 268514};
  int endRun[17] =  {262419, 257415, 257178, 257711, 261717, 255518, 257956, 258172, 262218, 275022, 270162, 270162, 274405, 273409, 272826, 268999, 268543};
  int ieta[17] = {16, 32, -6, 19, 17, 6, -7, 25, 7, 6, 33, 34, 16, 9, 2, -30, -1};
  int iphi[17] = {40, 44, 55, 64, 16, 20, 20, 25, 28, 35, 43, 43, 37, 6, 8, 14, 30};
  for (int i=0; i<17; i++) {
    vector<int> info;
    info.push_back(initRun[i]);
    info.push_back(endRun[i]);
    info.push_back(ieta[i]);
    info.push_back(iphi[i]);
    _killcells.push_back(info);
  }

}

ClassImp(HardRecoilAnalysis)
