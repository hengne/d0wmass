// Author: Rafael Lopes de Sa
// Date: 19/Mar/2012

// Updating ... 

// C++
#include <iostream>
#include <vector>
#include <map>

// Cafe stuff
#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Variables.hpp"

// Other packages
#include "tmb_tree/TMBEMCluster.hpp"
#include "tmb_tree/TMBMCpart.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "wmass_util/WZ_Utils.hpp"
#include "kinem_util/AnglesUtil.hpp"

// This code
#include "wmass_analysis/FSRAnalysis.hpp"

// ROOT
#include "TMath.h"
#include "TFile.h"

using namespace std;
using namespace cafe;



FSRAnalysis::FSRAnalysis(const char *name) : Processor(name) {

  Config config(name);

  // debug level
  _debugLevel = config.get("debugLevel", 0);
  
  // MC study
  _MCStudy = config.get("MCStudy", false);

  // EM Selection cuts
  _DetEtaCC = config.get("DetEtaCC", 1.1);
  _DetEtaEC1 = config.get("DetEtaEC1", 1.5);
  _DetEtaEC2 = config.get("DetEtaEC2", 3.2);

  _ElecPtCut = config.get("ElecPtCut", 0.);

  _HM7Cut = config.get("HM7Cut", 12.);
  _HM8Cut = config.get("HM8Cut", 20.);
  _EMFracCut = config.get("EMFracCut", 0.9);
  _IsoCut = config.get("IsoCut", 0.15);
  
  // Require smt hit for track match
  _require_smt = config.get("RequireSMT", true);
  _require_smtEC = config.get("RequireSMT_EC", true);

  // Which type of run
  _MergedRun = config.get("FSRMergedRun", kTRUE);
  _ZBoverlay = config.get("FSRZBoverlay", kTRUE);


  _MergedFileName = config.get("FSRMergedFile", "FSRMerged.root");
  _FSRFileName = config.get("FSRFile", "FSRAnalysis.root");

  // fill a tree
  if (!_MergedRun) {

    cout << "Starting FSR Analysis" << endl;
    _FSRFile = new TFile(_FSRFileName, "RECREATE");
    _FSRTree = new TTree("fsr", "fsr");

    // The run and event numbers
    _FSRTree->Branch("RunNum",&_RunNum,"RunNum/I");
    _FSRTree->Branch("EventNum",&_EventNum,"EventNum/I");

    _FSRTree->Branch("ZBRunNum",&_ZBRunNum,"ZBRunNum/I");
    _FSRTree->Branch("ZBEventNum",&_ZBEventNum,"ZBEventNum/I");

    // Electron variables
    _FSRTree->Branch("NRecoEl", &_NRecoEl, "NRecoEl/I");

    _FSRTree->Branch("RecoE", _RecoE, "RecoE[NRecoEl]/D");
    _FSRTree->Branch("RecoPx", _RecoPx, "RecoPx[NRecoEl]/D");
    _FSRTree->Branch("RecoPy", _RecoPy, "RecoPy[NRecoEl]/D");
    _FSRTree->Branch("RecoPz", _RecoPz, "RecoPz[NRecoEl]/D");

    _FSRTree->Branch("RecoDetEta", _RecoDetEta, "RecoDetEta[NRecoEl]/D");
    _FSRTree->Branch("RecoUncorrE", _RecoUncorrE, "RecoUncorrE[NRecoEl]/D");
    _FSRTree->Branch("RecoDetPhi", _RecoDetPhi, "RecoDetPhi[NRecoEl]/D");
    _FSRTree->Branch("RecoFloor1", _RecoFloor1, "RecoFloor1[NRecoEl]/D");
    _FSRTree->Branch("RecoFloor2", _RecoFloor2, "RecoFloor2[NRecoEl]/D");
    _FSRTree->Branch("RecoFloor3", _RecoFloor3, "RecoFloor3[NRecoEl]/D");
    _FSRTree->Branch("RecoFloor4", _RecoFloor4, "RecoFloor4[NRecoEl]/D");
    _FSRTree->Branch("RecoFloor5", _RecoFloor5, "RecoFloor5[NRecoEl]/D");

    _FSRTree->Branch("NTruePh", &_NTruePh, "NTruePh/I");
    _FSRTree->Branch("TruePhE", _TruePhE, "TruePhE[NTruePh]/D");
    _FSRTree->Branch("TruePhPx", _TruePhPx, "TruePhPx[NTruePh]/D");
    _FSRTree->Branch("TruePhPy", _TruePhPy, "TruePhPy[NTruePh]/D");
    _FSRTree->Branch("TruePhPz", _TruePhPz, "TruePhPz[NTruePh]/D");

    _FSRTree->Branch("NTrueNu", &_NTrueNu, "NTrueNu/I");
    _FSRTree->Branch("TrueNuE", _TrueNuE, "TrueNuE[NTrueNu]/D");
    _FSRTree->Branch("TrueNuPx", _TrueNuPx, "TrueNuPx[NTrueNu]/D");
    _FSRTree->Branch("TrueNuPy", _TrueNuPy, "TrueNuPy[NTrueNu]/D");
    _FSRTree->Branch("TrueNuPz", _TrueNuPz, "TrueNuPz[NTrueNu]/D");
    
    _FSRTree->Branch("NTrueEl", &_NTrueEl, "NTrueEl/I");
    _FSRTree->Branch("TrueE", _TrueE, "TrueE[NTrueEl]/D");
    _FSRTree->Branch("TruePx", _TruePx, "TruePx[NTrueEl]/D");
    _FSRTree->Branch("TruePy", _TruePy, "TruePy[NTrueEl]/D");
    _FSRTree->Branch("TruePz", _TruePz, "TruePz[NTrueEl]/D");
    
    _FSRTree->Branch("NMergedRecoEl", &_NMergedRecoEl, "NMergedRecoEl/I");

    _FSRTree->Branch("MergedRecoE", _MergedRecoE, "MergedRecoE[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedRecoPx", _MergedRecoPx, "MergedRecoPx[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedRecoPy", _MergedRecoPy, "MergedRecoPy[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedRecoPz", _MergedRecoPz, "MergedRecoPz[NMergedRecoEl]/D");

    _FSRTree->Branch("MergedRecoDetEta", _MergedRecoDetEta, "MergedRecoDetEta[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedRecoUncorrE", _MergedRecoUncorrE, "MergedRecoUncorrE[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedRecoDetPhi", _MergedRecoDetPhi, "MergedRecoDetPhi[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedRecoFloor1", _MergedRecoFloor1, "MergedRecoFloor1[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedRecoFloor2", _MergedRecoFloor2, "MergedRecoFloor2[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedRecoFloor3", _MergedRecoFloor3, "MergedRecoFloor3[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedRecoFloor4", _MergedRecoFloor4, "MergedRecoFloor4[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedRecoFloor5", _MergedRecoFloor5, "MergedRecoFloor5[NMergedRecoEl]/D");

    _FSRTree->Branch("NMergedTrueEl", &_NMergedTrueEl, "NMergedTrueEl/I");
    _FSRTree->Branch("MergedTrueE", _MergedTrueE, "MergedTrueE[NMergedTrueEl]/D");
    _FSRTree->Branch("MergedTruePx", _MergedTruePx, "MergedTruePx[NMergedTrueEl]/D");
    _FSRTree->Branch("MergedTruePy", _MergedTruePy, "MergedTruePy[NMergedTrueEl]/D");
    _FSRTree->Branch("MergedTruePz", _MergedTruePz, "MergedTruePz[NMergedTrueEl]/D");

    _FSRTree->Branch("RecoPhUPx", &_RecoPhUPx[0][0], "RecoPhUPx[10][10]/D");
    _FSRTree->Branch("RecoPhUPy", &_RecoPhUPy[0][0], "RecoPhUPy[10][10]/D");

    _FSRTree->Branch("SET", _SET, "SET[NRecoEl]/D");
    _FSRTree->Branch("MergedSET", _MergedSET, "MergedSET[NMergedRecoEl]/D");
    _FSRTree->Branch("Lumi", &_lumi, "Lumi/D");

    _FSRTree->Branch("mcvtx", _mcvtx, "mcvtx[3]/D"); 

    _FSRTree->Branch("isPassCCFid", _isPassCCFid, "isPassCCFid[NRecoEl]/O");
    _FSRTree->Branch("isPassEmFracIso", _isPassEmFracIso, "isPassEmFracIso[NRecoEl]/O");
    _FSRTree->Branch("isPassHmx", _isPassHmx, "isPassHmx[NRecoEl]/O");
    _FSRTree->Branch("isPassSpatialMatchLoose", _isPassSpatialMatchLoose, "isPassSpatialMatchLoose[NRecoEl]/O");
    _FSRTree->Branch("isPassSpatialMatchTight", _isPassSpatialMatchTight, "isPassSpatialMatchTight[NRecoEl]/O");

    _FSRTree->Branch("isPassCCFidMerged", _isPassCCFidMerged, "isPassCCFidMerged[NMergedRecoEl]/O");
    _FSRTree->Branch("isPassEmFracIsoMerged", _isPassEmFracIsoMerged, "isPassEmFracIsoMerged[NMergedRecoEl]/O");
    _FSRTree->Branch("isPassHmxMerged", _isPassHmxMerged, "isPassHmxMerged[NMergedRecoEl]/O");
    _FSRTree->Branch("isPassSpatialMatchLooseMerged", _isPassSpatialMatchLooseMerged, "isPassSpatialMatchLooseMerged[NMergedRecoEl]/O");
    _FSRTree->Branch("isPassSpatialMatchTightMerged", _isPassSpatialMatchTightMerged, "isPassSpatialMatchTightMerged[NMergedRecoEl]/O");

    _FSRTree->Branch("TrackPt", _TrackPt, "TrackPt[NRecoEl]/D");
    _FSRTree->Branch("TrackSMT", _TrackSMT, "TrackSMT[NRecoEl]/D");
    _FSRTree->Branch("TrackCFT", _TrackCFT, "TrackCFT[NRecoEl]/D");
    _FSRTree->Branch("TrackSpatialChi2", _TrackSpatialChi2, "TrackSpatialChi2[NRecoEl]/D");

    _FSRTree->Branch("MergedTrackPt", _MergedTrackPt, "TrackPt[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedTrackSMT", _MergedTrackSMT, "TrackSMT[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedTrackCFT", _MergedTrackCFT, "TrackCFT[NMergedRecoEl]/D");
    _FSRTree->Branch("MergedTrackSpatialChi2", _MergedTrackSpatialChi2, "TrackSpatialChi2[NMergedRecoEl]/D");

    _MergedFile = new TFile(_MergedFileName);
    _MergedTree = (TTree*) _MergedFile->Get("fsr");
    _MergedIndex = new TTreeIndex(_MergedTree, "RunNum", "EventNum");  

    _MergedTree->SetBranchAddress("NMergedRecoEl", &_NMergedRecoEl);
    _MergedTree->SetBranchAddress("MergedRecoE", _MergedRecoE);
    _MergedTree->SetBranchAddress("MergedRecoPx", _MergedRecoPx);
    _MergedTree->SetBranchAddress("MergedRecoPy", _MergedRecoPy);
    _MergedTree->SetBranchAddress("MergedRecoPz", _MergedRecoPz);

    _MergedTree->SetBranchAddress("MergedRecoDetEta", _MergedRecoDetEta);
    _MergedTree->SetBranchAddress("MergedRecoUncorrE", _MergedRecoUncorrE);
    _MergedTree->SetBranchAddress("MergedRecoDetPhi", _MergedRecoDetPhi);
    _MergedTree->SetBranchAddress("MergedRecoFloor1", _MergedRecoFloor1);
    _MergedTree->SetBranchAddress("MergedRecoFloor2", _MergedRecoFloor2);
    _MergedTree->SetBranchAddress("MergedRecoFloor3", _MergedRecoFloor3);
    _MergedTree->SetBranchAddress("MergedRecoFloor4", _MergedRecoFloor4);
    _MergedTree->SetBranchAddress("MergedRecoFloor5", _MergedRecoFloor5);

    _MergedTree->SetBranchAddress("NMergedTrueEl", &_NMergedTrueEl);
    _MergedTree->SetBranchAddress("MergedTrueE", _MergedTrueE);
    _MergedTree->SetBranchAddress("MergedTruePx", _MergedTruePx);
    _MergedTree->SetBranchAddress("MergedTruePy", _MergedTruePy);
    _MergedTree->SetBranchAddress("MergedTruePz", _MergedTruePz);

    _MergedTree->SetBranchAddress("RunNum",&_RunNum);
    _MergedTree->SetBranchAddress("EventNum",&_EventNum);

    _MergedTree->SetBranchAddress("ZBRunNum",&_ZBRunNum);
    _MergedTree->SetBranchAddress("ZBEventNum",&_ZBEventNum);

    _MergedTree->SetBranchAddress("ZBncells", &_ZBncells);
    _MergedTree->SetBranchAddress("ZBnormal", _ZBnormal);
    _MergedTree->SetBranchAddress("ZBieta", _ZBieta);
    _MergedTree->SetBranchAddress("ZBiphi", _ZBiphi);
    _MergedTree->SetBranchAddress("ZBlayer", _ZBlayer);
    _MergedTree->SetBranchAddress("ZBenergy", _ZBenergy);

    _MergedTree->SetBranchAddress("Merged_ncells", _Merged_ncells);
    _MergedTree->SetBranchAddress("Merged_ieta", &_Merged_ieta[0][0]);
    _MergedTree->SetBranchAddress("Merged_iphi", &_Merged_iphi[0][0]);
    _MergedTree->SetBranchAddress("Merged_layer", &_Merged_layer[0][0]);

    _MergedTree->SetBranchAddress("MergedSET", _MergedSET);

    _MergedTree->SetBranchAddress("isPassCCFidMerged", _isPassCCFidMerged);
    _MergedTree->SetBranchAddress("isPassEmFracIsoMerged", _isPassEmFracIsoMerged);
    _MergedTree->SetBranchAddress("isPassHmxMerged", _isPassHmxMerged);
    _MergedTree->SetBranchAddress("isPassSpatialMatchLooseMerged", _isPassSpatialMatchLooseMerged);
    _MergedTree->SetBranchAddress("isPassSpatialMatchTightMerged", _isPassSpatialMatchTightMerged);

    _MergedTree->SetBranchAddress("MergedTrackPt", _MergedTrackPt);
    _MergedTree->SetBranchAddress("MergedTrackSMT", _MergedTrackSMT);
    _MergedTree->SetBranchAddress("MergedTrackCFT", _MergedTrackCFT);
    _MergedTree->SetBranchAddress("MergedTrackSpatialChi2", _MergedTrackSpatialChi2);

  } 
    
  if (_MergedRun) {

    _MergedFile = new TFile(_MergedFileName, "RECREATE");
    _MergedTree = new TTree("fsr", "fsr");

    _MergedTree->Branch("NMergedRecoEl", &_NMergedRecoEl, "NMergedRecoEl/I");

    _MergedTree->Branch("MergedRecoE", _MergedRecoE, "MergedRecoE[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedRecoPx", _MergedRecoPx, "MergedRecoPx[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedRecoPy", _MergedRecoPy, "MergedRecoPy[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedRecoPz", _MergedRecoPz, "MergedRecoPz[NMergedRecoEl]/D");

    _MergedTree->Branch("NMergedTrueEl", &_NMergedTrueEl, "NMergedTrueEl/I");

    _MergedTree->Branch("MergedTrueE", _MergedTrueE, "MergedTrueE[NMergedTrueEl]/D");
    _MergedTree->Branch("MergedTruePx", _MergedTruePx, "MergedTruePx[NMergedTrueEl]/D");
    _MergedTree->Branch("MergedTruePy", _MergedTruePy, "MergedTruePy[NMergedTrueEl]/D");
    _MergedTree->Branch("MergedTruePz", _MergedTruePz, "MergedTruePz[NMergedTrueEl]/D");

    _MergedTree->Branch("MergedRecoDetEta", _MergedRecoDetEta, "MergedRecoDetEta[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedRecoUncorrE", _MergedRecoUncorrE, "MergedRecoUncorrE[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedRecoDetPhi", _MergedRecoDetPhi, "MergedRecoDetPhi[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedRecoFloor1", _MergedRecoFloor1, "MergedRecoFloor1[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedRecoFloor2", _MergedRecoFloor2, "MergedRecoFloor2[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedRecoFloor3", _MergedRecoFloor3, "MergedRecoFloor3[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedRecoFloor4", _MergedRecoFloor4, "MergedRecoFloor4[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedRecoFloor5", _MergedRecoFloor5, "MergedRecoFloor5[NMergedRecoEl]/D");

    _MergedTree->Branch("RunNum",&_RunNum, "RunNum/I");
    _MergedTree->Branch("EventNum",&_EventNum, "EventNum/I");

    _MergedTree->Branch("ZBRunNum",&_ZBRunNum, "ZBRunNum/I");
    _MergedTree->Branch("ZBEventNum",&_ZBEventNum, "ZBEventNum/I");

    _MergedTree->Branch("ZBncells", &_ZBncells, "ZBncells/I");
    _MergedTree->Branch("ZBnormal", _ZBnormal, "ZBnormal[ZBncells]/O");
    _MergedTree->Branch("ZBieta", _ZBieta, "ZBieta[ZBncells]/I");
    _MergedTree->Branch("ZBiphi", _ZBiphi, "ZBiphi[ZBncells]/I");
    _MergedTree->Branch("ZBlayer", _ZBlayer, "ZBlayers[ZBncells]/I");
    _MergedTree->Branch("ZBenergy", _ZBenergy, "ZBenergy[ZBncells]/D");

    _MergedTree->Branch("Merged_ncells", _Merged_ncells, "Merged_ncells[10]/I");
    _MergedTree->Branch("Merged_ieta", &_Merged_ieta[0][0], "Merged_ieta[10][120]/I");
    _MergedTree->Branch("Merged_iphi", &_Merged_iphi[0][0], "Merged_iphi[10][120]/I");
    _MergedTree->Branch("Merged_layer", &_Merged_layer[0][0], "Merged_layers[10][120]/I");

    _MergedTree->Branch("MergedSET", _MergedSET, "MergedSET[NMergedRecoEl]/D");

    _MergedTree->Branch("isPassCCFidMerged", _isPassCCFidMerged, "isPassCCFidMerged[NMergedRecoEl]/O");
    _MergedTree->Branch("isPassEmFracIsoMerged", _isPassEmFracIsoMerged, "isPassEmFracIsoMerged[NMergedRecoEl]/O");
    _MergedTree->Branch("isPassHmxMerged", _isPassHmxMerged, "isPassHmxMerged[NMergedRecoEl]/O");
    _MergedTree->Branch("isPassSpatialMatchLooseMerged", _isPassSpatialMatchLooseMerged, "isPassSpatialMatchLooseMerged[NMergedRecoEl]/O");
    _MergedTree->Branch("isPassSpatialMatchTightMerged", _isPassSpatialMatchTightMerged, "isPassSpatialMatchTightMerged[NMergedRecoEl]/O");

    _MergedTree->Branch("MergedTrackPt", _MergedTrackPt, "TrackPt[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedTrackSMT", _MergedTrackSMT, "TrackSMT[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedTrackCFT", _MergedTrackCFT, "TrackCFT[NMergedRecoEl]/D");
    _MergedTree->Branch("MergedTrackSpatialChi2", _MergedTrackSpatialChi2, "TrackSpatialChi2[NMergedRecoEl]/D");

  }

  initKillList();
}


bool FSRAnalysis::processEvent(cafe::Event& event) {

  // This analysis only makes sense for MC
  if (!_MCStudy) return 0;

  cout << "RCLSA 1" << endl;
 
  Bool_t cal_empty_crate, cal_coherent_noise, cal_ring_of_fire, cal_noon_noise, cal_spanish_fan, cal_sca_failure;
  event.get("cal_empty_crate", cal_empty_crate);
  event.get("cal_coherent_noise", cal_coherent_noise);
  event.get("cal_ring_of_fire", cal_ring_of_fire);
  event.get("cal_noon_noise", cal_noon_noise);
  event.get("cal_spanish_fan", cal_spanish_fan);
  event.get("cal_sca_failure", cal_sca_failure);
  if (cal_empty_crate || cal_coherent_noise || cal_ring_of_fire || cal_noon_noise || cal_spanish_fan || cal_sca_failure) {
    return 0;
  }

  cout << "RCLSA 2" << endl;

  // For the ZB run is easy
  if (_MergedRun) {

    vector<CAFEMObj*> emobjs;
    vector<TMBMCpart*> raw_mc_electrons;

    _RunNum = event.getMCEventInfo()->run();
    _EventNum = event.getMCEventInfo()->evtid();

    _ZBRunNum = event.getMCEventInfo()->overlayrun();
    _ZBEventNum = event.getMCEventInfo()->overlayevtid();

    cout << event.get("Probe EMObjs", emobjs) << " " << event.get("raw mc electrons", raw_mc_electrons) << endl;


    if(!(event.get("Probe EMObjs", emobjs) &&      
	 event.get("raw mc electrons", raw_mc_electrons))) return 0;

    const TMBCellContainer *calocells = event.get<TMBCellContainer>("CaloCells");
    if (!calocells) return 0;

    Float_t mcvtxx, mcvtxy, mcvtxz;
    cafe::Collection<TMBMCvtx> mcvtx = event.getMCVertices();
    mcvtxx = mcvtx[0].x();
    mcvtxy = mcvtx[0].y();
    mcvtxz = mcvtx[0].z();
    _mcvtx[0] = mcvtxx;
    _mcvtx[1] = mcvtxy;
    _mcvtx[2] = mcvtxz;

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

    _NMergedTrueEl = raw_mc_electrons.size();
    if (_NMergedTrueEl > 10) return 0; // Too many electrons... you are clearly doing something wrong
    for (int ielec=0; ielec<_NMergedTrueEl; ielec++) {	
      _MergedTrueE[ielec] = raw_mc_electrons[ielec]->E();
      _MergedTruePx[ielec] = raw_mc_electrons[ielec]->Px();
      _MergedTruePy[ielec] = raw_mc_electrons[ielec]->Py();
      _MergedTruePz[ielec] = raw_mc_electrons[ielec]->Pz();	
    }

    _NMergedRecoEl = emobjs.size();
    if (emobjs.size() > 10) return 0; // Too many electrons... you are clearly doing something wrong
    
    for (int ielec=0; ielec<emobjs.size(); ielec++) {

      // Quality requirements
      _isPassEmFracIsoMerged[ielec] = emobjs[ielec]->PassEMFracIso(_EMFracCut,_IsoCut);
      _isPassHmxMerged[ielec] = emobjs[ielec]->PassHMx(_HM7Cut,_HM8Cut);
      _isPassSpatialMatchLooseMerged[ielec] = emobjs[ielec]->has_spatial_track_match(-0.5);
      _isPassCCFidMerged[ielec] = emobjs[ielec]->IsCCFid(_DetEtaCC);
      _isPassSpatialMatchTightMerged[ielec] = emobjs[ielec]->has_good_spatial_track_match(0.01,_require_smt,10.,_require_smtEC);

      // The electron four-momentum
      _MergedRecoE[ielec] = (Double_t) emobjs[ielec]->E();
      _MergedRecoUncorrE[ielec] = (Double_t) emobjs[ielec]->uncorrE();
      _MergedRecoPx[ielec] = (Double_t) emobjs[ielec]->Px();
      _MergedRecoPy[ielec] = (Double_t) emobjs[ielec]->Py();
      _MergedRecoPz[ielec] = (Double_t) emobjs[ielec]->Pz();
      _MergedRecoDetEta[ielec] = (Double_t) emobjs[ielec]->CalDetectorEta();
      _MergedRecoDetPhi[ielec] = (Double_t) emobjs[ielec]->CalDetectorPhi();
      _MergedRecoFloor1[ielec] = (Double_t) emobjs[ielec]->floorE(1);
      _MergedRecoFloor2[ielec] = (Double_t) emobjs[ielec]->floorE(2);
      _MergedRecoFloor3[ielec] = (Double_t) emobjs[ielec]->floorE(3);
      _MergedRecoFloor4[ielec] = (Double_t) emobjs[ielec]->floorE(4);
      _MergedRecoFloor5[ielec] = (Double_t) emobjs[ielec]->floorE(5);
      if (_isPassSpatialMatchLooseMerged[ielec]) {
	_MergedTrackPt[ielec]    = (Double_t) emobjs[ielec]->getPtrSpatialChp()->Pt();
	_MergedTrackSMT[ielec]   = (Double_t) emobjs[ielec]->getPtrSpatialChp()->nsmt();
	_MergedTrackCFT[ielec]   = (Double_t) emobjs[ielec]->getPtrSpatialChp()->ncft();
	_MergedTrackSpatialChi2[ielec]  = (Double_t) emobjs[ielec]->track_match_spatialchi2prob();
      } else {
	_MergedTrackPt[ielec]    = -1.0;
	_MergedTrackSMT[ielec]   = -1.0;
	_MergedTrackCFT[ielec]   = -1.0;
	_MergedTrackSpatialChi2[ielec]  = -1.0;
      }

      _MergedSET[ielec] = GetSET(event, _mcvtx, emobjs[ielec]);
      _Merged_ncells[ielec] = 0;
      for (Int_t i=0; i<emobjs[ielec]->ncells(); i++) {
	const TMBCaloCell* elcell = emobjs[ielec]->GetCaloCell(i);
	if (!elcell) continue;
	_Merged_layer[ielec][_Merged_ncells[ielec]] = elcell->layer();
	_Merged_ieta[ielec][_Merged_ncells[ielec]] = elcell->ieta();
	_Merged_iphi[ielec][_Merged_ncells[ielec]] = elcell->iphi();
	_Merged_ncells[ielec]++;
      }

    }
   
    _MergedTree->Fill();
  }
  // Now comes the real analysis
  if  (!_MergedRun) {

    vector<CAFEMObj*> emobjs;
    vector<TMBMCpart*> raw_mc_electrons;
    vector<TMBMCpart*> raw_mc_photons;
    vector<TMBMCpart*> raw_mc_neutrinos;

    _RunNum = event.getMCEventInfo()->run();
    _EventNum = event.getMCEventInfo()->evtid();
    _ZBRunNum = event.getMCEventInfo()->overlayrun();
    _ZBEventNum = event.getMCEventInfo()->overlayevtid();
    _lumi = event.getMCEventInfo()->overlay_instlum();

    Float_t mcvtxx, mcvtxy, mcvtxz;
    cafe::Collection<TMBMCvtx> mcvtx = event.getMCVertices();
    mcvtxx = mcvtx[0].x();
    mcvtxy = mcvtx[0].y();
    mcvtxz = mcvtx[0].z();
    _mcvtx[0] = mcvtxx;
    _mcvtx[1] = mcvtxy;
    _mcvtx[2] = mcvtxz;

    // Tries to get the needed information
    if (!(event.get("Probe EMObjs", emobjs) &&	  
	  event.get("mc neutrinos", raw_mc_neutrinos) && 
	  event.get("raw mc photons", raw_mc_photons) &&
	  event.get("raw mc electrons", raw_mc_electrons))) return 0;

    if (_MergedTree->GetEntry(_MergedIndex->GetEntryNumberWithIndex(_RunNum, _EventNum)) < 0) return 0;

    _NTrueEl = raw_mc_electrons.size();
    if (_NTrueEl > 10) return 0; // Too many electrons... you are clearly doing something wrong
    for (int ielec=0; ielec<_NTrueEl; ielec++) {	
      _TrueE[ielec] = (Double_t) raw_mc_electrons[ielec]->E();
      _TruePx[ielec] = (Double_t) raw_mc_electrons[ielec]->Px();
      _TruePy[ielec] = (Double_t) raw_mc_electrons[ielec]->Py();
      _TruePz[ielec] = (Double_t) raw_mc_electrons[ielec]->Pz();	
    }

    _NTruePh = raw_mc_photons.size();
    //    cout << _NTruePh << endl;
    if (_NTruePh > 10) return 0; // Too many photons... you are clearly doing something wrong
    for (int iph=0; iph<_NTruePh; iph++) {
      _TruePhE[iph] = (Double_t) raw_mc_photons[iph]->E();
      _TruePhPx[iph] = (Double_t) raw_mc_photons[iph]->Px();
      _TruePhPy[iph] = (Double_t) raw_mc_photons[iph]->Py();
      _TruePhPz[iph] = (Double_t) raw_mc_photons[iph]->Pz();	
    }

    _NTrueNu = (Int_t) raw_mc_neutrinos.size();
    if (_NTrueNu > 10) return 0; // Too many neutrinos... you are clearly doing something wrong
    for (int inu=0; inu<_NTrueNu; inu++) {
      _TrueNuE[inu] = (Double_t) raw_mc_neutrinos[inu]->E();
      _TrueNuPx[inu] = (Double_t) raw_mc_neutrinos[inu]->Px();
      _TrueNuPy[inu] = (Double_t) raw_mc_neutrinos[inu]->Py();
      _TrueNuPz[inu] = (Double_t) raw_mc_neutrinos[inu]->Pz();	
    }

    _NRecoEl = emobjs.size();
    if (emobjs.size() > 10) return 0; // Too many electrons... you are clearly doing something wrong

    for (int ielec=0; ielec<emobjs.size(); ielec++) {

      // How well it hits and where it hits
      Bool_t _passcuts = (emobjs[ielec]->IsCCFid(_DetEtaCC) &&                                                  // Cal fiducial region
			  emobjs[ielec]->Pt()>_ElecPtCut &&                                                     // Pt cut
			  emobjs[ielec]->PassEMFracIso(_EMFracCut,_IsoCut) &&                                   // EM frac and Isolation
			  emobjs[ielec]->PassHMx(_HM7Cut,_HM8Cut) &&                                            // HMatrix
			  emobjs[ielec]->has_spatial_track_match(-0.5) &&                                       // Loose track match
			  emobjs[ielec]->has_good_spatial_track_match(0.01,_require_smt,10., _require_smtEC));   // Tight track match

      _isPassEmFracIso[ielec] = emobjs[ielec]->PassEMFracIso(_EMFracCut,_IsoCut);
      _isPassHmx[ielec] = emobjs[ielec]->PassHMx(_HM7Cut,_HM8Cut);
      _isPassSpatialMatchLoose[ielec] = emobjs[ielec]->has_spatial_track_match(-0.5);
      _isPassCCFid[ielec] = emobjs[ielec]->IsCCFid(_DetEtaCC);
      _isPassSpatialMatchTight[ielec] = emobjs[ielec]->has_good_spatial_track_match(0.01,_require_smt,10.,_require_smtEC);

      // The electron four-momentum
      _RecoE[ielec] = (Double_t) emobjs[ielec]->E();
      _RecoUncorrE[ielec] = (Double_t) emobjs[ielec]->uncorrE();
      _RecoPx[ielec] = (Double_t) emobjs[ielec]->Px();
      _RecoPy[ielec] = (Double_t) emobjs[ielec]->Py();
      _RecoPz[ielec] = (Double_t) emobjs[ielec]->Pz();
      _RecoDetEta[ielec] = (Double_t) emobjs[ielec]->CalDetectorEta();
      _RecoDetPhi[ielec] = (Double_t) emobjs[ielec]->CalDetectorPhi();
      _RecoFloor1[ielec] = (Double_t) emobjs[ielec]->floorE(1);
      _RecoFloor2[ielec] = (Double_t) emobjs[ielec]->floorE(2);
      _RecoFloor3[ielec] = (Double_t) emobjs[ielec]->floorE(3);
      _RecoFloor4[ielec] = (Double_t) emobjs[ielec]->floorE(4);
      _RecoFloor5[ielec] = (Double_t) emobjs[ielec]->floorE(5);
      if (_isPassSpatialMatchLoose[ielec]) {
	_TrackPt[ielec]    = (Double_t) emobjs[ielec]->getPtrSpatialChp()->Pt();
	_TrackSMT[ielec]   = (Double_t) emobjs[ielec]->getPtrSpatialChp()->nsmt();
	_TrackCFT[ielec]   = (Double_t) emobjs[ielec]->getPtrSpatialChp()->ncft();
	_TrackSpatialChi2[ielec]  = (Double_t) emobjs[ielec]->track_match_spatialchi2prob();
      } else {
	_TrackPt[ielec]    = -1.0;
	_TrackSMT[ielec]   = -1.0;
	_TrackCFT[ielec]   = -1.0;
	_TrackSpatialChi2[ielec]  = -1.0;
      }

      _SET[ielec] = GetSET(event, _mcvtx, emobjs[ielec]);
      _ElectronCells[ielec] = new TMBCellContainer();
      for (Int_t i=0; i<emobjs[ielec]->ncells(); i++) {
	const TMBCaloCell* elcell = emobjs[ielec]->GetCaloCell(i);
	_ElectronCells[ielec]->AddCell(elcell->ieta(), elcell->iphi(), elcell->layer(), elcell->E(), elcell->flags());
      }

      for (Int_t imerged=0; imerged<_NMergedRecoEl; imerged++) {
	Double_t SETfake;
	TVector2 _ureco = GetSubtractedRecoil(event, 
					      _ZBncells, _ZBieta, _ZBiphi, _ZBlayer, _ZBenergy, _ZBnormal, 
					      _Merged_ncells[imerged], _Merged_ieta[imerged], 
					      _Merged_iphi[imerged], _Merged_layer[imerged],
					      _ElectronCells[ielec], 
					      _mcvtx, SETfake);
      
	_RecoPhUPx[ielec][imerged] = _ureco.Px();
	_RecoPhUPy[ielec][imerged] = _ureco.Py();
      }

    }


    _FSRTree->Fill();
  }
  
  return true;

}

void FSRAnalysis::finish() {

  if (_MergedRun) {
    _MergedFile->Write();
    _MergedFile->Close();
  } else {
    _FSRFile->Write();
    _FSRFile->Close();
  }

}

TVector2 FSRAnalysis::GetSubtractedRecoil(Event& event, 
					  Int_t zbncells, Int_t* zbieta, Int_t* zbiphi, Int_t* zblayer, Double_t* zbenergy, Bool_t* zbnormal,
					  Int_t mergedncells, Int_t* mergedieta, Int_t* mergediphi, Int_t* mergedlayer,
					  TMBCellContainer* ElectronCells, 
					  Float_t vtx[3], Double_t& SET) {

  //  cout << "Getting it" << endl;

  Double_t ux_em=0., uy_em=0., u_em=0., uz_em=0, scalarEt_em=0.;
  Double_t ux_icd=0., uy_icd=0., u_icd=0., uz_icd=0, scalarEt_icd=0.;
  Double_t ux_mg=0., uy_mg=0., u_mg=0., uz_mg=0, scalarEt_mg=0.;
  Double_t ux_fh=0., uy_fh=0., u_fh=0., uz_fh=0, scalarEt_fh=0.;

  // Fet calorimeter geometry manager
  const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");

  int ZBrunNum = event.getMCEventInfo()->overlayrun();
  for(UInt_t icell=0; icell<cells->NumCells(); ++icell) {
    const TMBCaloCell *cell = cells->GetCell(icell);
    if (!cell) continue;
    if (!cell->isNormalCell()) continue;

    Int_t ilyr = cell->layer();
    Int_t ieta = cell->ieta();
    Int_t iphi = cell->iphi();
    if (isBadSCA(ZBrunNum, ieta, iphi)) continue;
    if (ilyr >=15) continue;                                

    Bool_t isElectron = false;
    for(UInt_t ielcell=0; ielcell<ElectronCells->NumCells(); ++ielcell) {
      const TMBCaloCell *elcell = ElectronCells->GetCell(ielcell);
      if ((ilyr == elcell->layer()) && (ieta == elcell->ieta()) && (iphi == elcell->iphi())) {
	isElectron = true;
	break;
      }
    }
    if (isElectron) continue;

    Double_t ZBsub = 0;
    for (Int_t zbcell=0; zbcell < zbncells; zbcell++) {
      if (ilyr == zblayer[zbcell] && ieta == zbieta[zbcell] && iphi == zbiphi[zbcell] && zbnormal[zbcell]) {
	ZBsub = zbenergy[zbcell];
	break;
      }
    }

    Bool_t isMergedElectron = false;
    for(UInt_t imelcell=0; imelcell<mergedncells; ++imelcell) {
      if ((ilyr == mergedlayer[imelcell]) && (ieta == mergedieta[imelcell]) && (iphi == mergediphi[imelcell])) {
	isMergedElectron = true;
	break;
      }
    }

    Double_t dE = cell->E();
    if (!isMergedElectron) dE -= ZBsub;

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

Double_t FSRAnalysis::GetSET(Event& event, Float_t vtx[3], CAFEMObj* _emobj) {

  Double_t ux_em=0., uy_em=0., u_em=0., uz_em=0, scalarEt_em=0.;
  Double_t ux_icd=0., uy_icd=0., u_icd=0., uz_icd=0, scalarEt_icd=0.;
  Double_t ux_mg=0., uy_mg=0., u_mg=0., uz_mg=0, scalarEt_mg=0.;
  Double_t ux_fh=0., uy_fh=0., u_fh=0., uz_fh=0, scalarEt_fh=0.;
  Double_t scalarEt_elec=0.;

  if (_emobj) {
    float* elecset = new float();
    _emobj->getRawElecVectorFromCells(vtx, elecset);
    scalarEt_elec = *elecset;
    delete elecset;
    // This is really stupid! References? Have you heard about it?!
  }

  // Fetch calorimeter geometry manager
  const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");

  int ZBrunNum = event.getMCEventInfo()->overlayrun();
  for(UInt_t icell=0; icell<cells->NumCells(); ++icell) {

    const TMBCaloCell *cell = cells->GetCell(icell);
    if (!cell) continue;
    if (!cell->isNormalCell()) continue;

    Int_t ilyr = cell->layer();
    Int_t ieta = cell->ieta();
    Int_t iphi = cell->iphi();

    if (isBadSCA(ZBrunNum, ieta, iphi)) continue;

    Double_t dE = cell->E();

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
  Double_t SET = scalarEt_em + scalarEt_mg + scalarEt_fh - scalarEt_elec;
  return SET;
}

 Bool_t FSRAnalysis::isBadSCA(Int_t ZBrunNum, Int_t ieta, Int_t iphi) {

   for (_killcells_it = _killcells.begin(); _killcells_it < _killcells.end(); _killcells_it++) {
     if (ZBrunNum >= (*_killcells_it)[0] && ZBrunNum <= (*_killcells_it)[1] && ieta == (*_killcells_it)[2] && iphi == (*_killcells_it)[3])
       return true;
   }
   return false;
 }

 void FSRAnalysis::initKillList() {

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
ClassImp(FSRAnalysis)
