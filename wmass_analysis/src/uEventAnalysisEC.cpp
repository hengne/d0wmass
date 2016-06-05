// Author: Rafael Lopes de Sa
// Date: 19/Mar/2012

// C++
#include <iostream>
#include <vector>
#include <set>

// Cafe stuff
#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Variables.hpp"

// Other packages
#include "tmb_tree/TMBEMCluster.hpp"
#include "tmb_tree/TMBCaloCell.hpp"
#include "tmb_tree/TMBCellContainer.hpp"
#include "tmb_tree/TMBL1CalTower.hpp"
#include "tmb_tree/TMBL2GblEM.hpp"
#include "tmb_tree/TMBL3Ele.hpp"
#include "wmass_util/EMClusterPosCorr.hpp"
#include "wmass_util/CaloGeometryManager.hpp"
#include "wmass_util/WZ_Utils.hpp"
#include "wmass_util/CAFZCand.hpp"
#include "wmass_util/CAFWCand.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "kinem_util/AnglesUtil.hpp"

// This code
#include "wmass_analysis/uEventAnalysisEC.hpp"
#include "wmass_analysis/histograms.hpp"

// ROOT
#include "TMath.h"
#include "TFile.h"

using namespace std;
using namespace cafe;

bool layerorder(const TMBCaloCell* i, const TMBCaloCell* j) { return (i->layer() < j->layer()); }
bool etaorder(const TMBCaloCell* i, const TMBCaloCell* j) { return (i->ieta() < j->ieta()); }

uEventAnalysisEC::uEventAnalysisEC(const char *name) : Processor(name) {

  Config config(name);

  // debug level
  _debugLevel = config.get("debugLevel", 0);
  
  // MC study
  _MCStudy = config.get("MCStudy", false);
   // MC study2 , store all EMObj truth and store only EMObjs information
  _MCStudy2 = config.get("MCStudy2", false);
  // switch off _MCStudy2 if _MCStudy is off
  if (!_MCStudy) _MCStudy2 = false;

  // analyzing W or Z
  _uEvtDoW = config.get("uEvtDoW", true);
  _uEvtDoZ = config.get("uEvtDoZ", false);

  // average delta Ut vector in the electron window. 
  _dUAverage = config.get("dUAverage", 0.0);

  // switch dUParaEffStudy
  _dUParaEffStudy = config.get("dUParaEffStudy", true);
 
  // no W or Z selection?
  if (!_dUParaEffStudy) {
    // options for applying selections or not
    _uEvtCutUt = config.get("uEvtCutUt", true);
    if (_uEvtDoZ){
      _uEvtCutBothPt = config.get("uEvtCutBothPt", true);
      _uEvtCCEC = config.get("uEvtCCEC", true);
      _uEvtECEC = config.get("uEvtECEC", false);
      _uEvtBothTrackMatch = config.get("uEvtBothTrackMatch", true);
    }
    else if (_uEvtDoW) {
      _uEvtCutMet = config.get("uEvtCutMet", true);
      _uEvtCutWMt = config.get("uEvtCutWMt", true);
    }
  }

  // store all electron cells?
  _uEvtStoreAllElecCells = config.get("uEvtStoreAllElecCells", false); 
  // store all cones in 2pi
  _uEvtStoreAllCones = config.get("uEvtStoreAllCones", false); 

  // EM Selection cuts
  _DetEtaCC = config.get("DetEtaCC", 1.1);
  _DetEtaEC1 = config.get("DetEtaEC1", 1.5);
  _DetEtaEC2 = config.get("DetEtaEC2", 3.2);

  _ElecPtCut = config.get("ElecPtCut", 25.);

  _HM7Cut = config.get("HM7Cut", 12.);
  _HM8Cut = config.get("HM8Cut", 20.);
  _EMFracCut = config.get("EMFracCut", 0.9);
  _IsoCut = config.get("IsoCut", 0.15);

  // Z boson mass, pT cuts
  _ZMassCut1 = config.get("ZMassCut1", 70.);
  _ZMassCut2 = config.get("ZMassCut2", 110.);
  _ZUtCut = config.get("ZUtCut", 999.);
  
  // W Mt and pT cuts
  _WMetCut = config.get("WMetCut", 25.);
  _WMtCut1 = config.get("WMtCut1", 50.);
  _WMtCut2 = config.get("WMtCut2", 200.);
  _WUtCut = config.get("WUtCut", 999.);

  // spatial track matching requirement
  _NumZSpatialTrk = config.get("NumZSpatialTrk", 1);
  
  // require smt hit for track match
  _require_smt = config.get("RequireSMT", kTRUE);
  _require_smtEC = config.get("RequireSMT_EC", kFALSE);

  // fill a tree
  _uEventOutFile = new TFile("uEventAnalaysisEC.root", "RECREATE");
  _tree = new TTree("tree", "tree");

  _tree->Branch("runnum",&_runNum,"runnum/I", 666000);
  _tree->Branch("evtnum",&_eventNum,"evtnum/I", 666000);
  _tree->Branch("vtx", _tvtx, "vtx[3]/D", 256000);
  _tree->Branch("lumi", &_tlumi, "lumi/D", 666000);
  _tree->Branch("nelec", &_tnelec, "nelec/I", 666000);

  if (_MCStudy && _MCStudy2){
    _tree->Branch("nelect", &_tnelect, "nelect/I", 666000);
    _tree->Branch("nnuet", &_tnnuet, "nnuet/I", 666000);
  }

  _tree->Branch("ut", &_tut, "ut/D", 666000);
  _tree->Branch("utx", &_tutx, "utx/D", 666000);
  _tree->Branch("uty", &_tuty, "uty/D", 666000);
  _tree->Branch("utphi", &_tutphi, "utphi/D", 666000);
  _tree->Branch("met", &_tmet, "met/D", 666000);
  _tree->Branch("metx", &_tmetx, "metx/D", 666000);
  _tree->Branch("mety", &_tmety, "mety/D", 666000);
  _tree->Branch("metphi", &_tmetphi, "metphi/D", 666000);
  _tree->Branch("set", &_tset, "set/D", 666000);

  if (_MCStudy && _MCStudy2){

    _tree->Branch("passCluster", _passCluster, "passCluster[nelect]/O", 666000);
    _tree->Branch("passEC", _passEC, "passEC[nelect]/O", 666000);
    _tree->Branch("passECFid", _passECFid, "passECFid[nelect]/O", 666000);
    _tree->Branch("passFid", _passFid, "passFid[nelect]/O", 666000);
    _tree->Branch("passCalPhiFid", _passCalPhiFid, "passCalPhiFid[nelect]/O", 666000);
    _tree->Branch("passCalEtaFid", _passCalEtaFid, "passCalEtaFid[nelect]/O", 666000);
    _tree->Branch("passTrkPhiFid", _passTrkPhiFid, "passTrkPhiFid[nelect]/O", 666000);
    _tree->Branch("passEmf", _passEmf, "passEmf[nelect]/O", 666000);
    _tree->Branch("passIso", _passIso, "passIso[nelect]/O", 666000);
    _tree->Branch("passHMx", _passHMx, "passHMx[nelect]/O", 666000);
    _tree->Branch("passTkMatchLoose", _passTkMatchLoose, "passTkMatchLoose[nelect]/O", 666000);
    _tree->Branch("passTkMatch", _passTkMatch, "passTkMatch[nelect]/O", 666000);

    _tree->Branch("eindex", _teindex, "eindex[nelect]/I", 666000);
    _tree->Branch("ee", _tee, "ee[nelect]/D", 666000);
    _tree->Branch("eeuc", _teeuc, "eeuc[nelect]/D", 666000);
    _tree->Branch("ept", _tept, "ept[nelect]/D", 666000);
    _tree->Branch("epx", _tepx, "epx[nelect]/D", 666000);
    _tree->Branch("epy", _tepy, "epy[nelect]/D", 666000);
    _tree->Branch("epz", _tepz, "epz[nelect]/D", 666000);
    _tree->Branch("ephi", _tephi, "ephi[nelect]/D", 666000);
    _tree->Branch("eeta", _teeta, "eeta[nelect]/D", 666000);
    _tree->Branch("echg", _techg, "echg[nelect]/D", 666000);
    _tree->Branch("edeteta", _tedeteta, "edeteta[nelect]/D", 666000);
    _tree->Branch("edetphi", _tedetphi, "edetphi[nelect]/D", 666000);
    _tree->Branch("eetaem3", _teetaem3, "eetaem3[nelect]/D", 666000);
    _tree->Branch("ephiem3", _tephiem3, "ephiem3[nelect]/D", 666000);
    _tree->Branch("ephimod", _tephimod, "ephimod[nelect]/D", 666000);
    _tree->Branch("etkpt", _tetkpt, "etkpt[nelect]/D", 666000);
  } else {
    _tree->Branch("ee", _tee, "ee[nelec]/D");
    _tree->Branch("eeuc", _teeuc, "eeuc[nelec]/D");
    _tree->Branch("ept", _tept, "ept[nelec]/D");
    _tree->Branch("epx", _tepx, "epx[nelec]/D");
    _tree->Branch("epy", _tepy, "epy[nelec]/D");
    _tree->Branch("epz", _tepz, "epz[nelec]/D");
    _tree->Branch("upara", _tupara, "upara[nelec]/D");
    _tree->Branch("uperp", _tuperp, "uperp[nelec]/D");
    _tree->Branch("ephi", _tephi, "ephi[nelec]/D");
    _tree->Branch("eeta", _teeta, "eeta[nelec]/D");
    _tree->Branch("eiphi", _teiphi, "eiphi[nelec]/I");
    _tree->Branch("eieta", _teieta, "eieta[nelec]/I");
    _tree->Branch("echg", _techg, "echg[nelec]/D");
    _tree->Branch("eetaem3", _teetaem3, "eetaem3[nelec]/D");
    _tree->Branch("edeteta", _tedeteta, "edeteta[nelec]/D");
    _tree->Branch("ephiem3", _tephiem3, "ephiem3[nelec]/D");
    _tree->Branch("ephimod", _tephimod, "ephimod[nelec]/D");
    _tree->Branch("edetphi", _tedetphi, "edetphi[nelec]/D");
    _tree->Branch("edetphimod", _tedetphimod, "edetphimod[nelec]/D");
    _tree->Branch("etkpt", _tetkpt, "etkpt[nelec]/D");
  }
 
 
  if (_MCStudy) {
    _tree->Branch("zbrunnum",&_ZBrunNum,"zbrunnum/I", 666000);
    _tree->Branch("zbevtnum",&_ZBeventNum,"zbevtnum/I", 666000);
    _tree->Branch("vtxtrue", _tvtxtrue, "vtxtrue[3]/D", 666000);
    _tree->Branch("uttrue", &_tuttrue, "uttrue/D", 666000);
    _tree->Branch("utxtrue", &_tutxtrue, "utxtrue/D", 666000);
    _tree->Branch("utytrue", &_tutytrue, "utytrue/D", 666000);
    _tree->Branch("utztrue", &_tutztrue, "utztrue/D", 666000);
  }
  if (_MCStudy && !_MCStudy2){
    _tree->Branch("echgtrue", _techgtrue, "echgtrue[nelec]/I");
    _tree->Branch("epttrue", _tepttrue, "epttrue[nelec]/D");
    _tree->Branch("epxtrue", _tepxtrue, "epxtrue[nelec]/D");
    _tree->Branch("epytrue", _tepytrue, "epytrue[nelec]/D");
    _tree->Branch("epztrue", _tepztrue, "epztrue[nelec]/D");
    _tree->Branch("eetrue", _teetrue, "eetrue[nelec]/D");
    _tree->Branch("ephitrue", _tephitrue, "ephitrue[nelec]/D");
    _tree->Branch("eetatrue", _teetatrue, "eetatrue[nelec]/D");
    _tree->Branch("eptftrue", _teptftrue, "eptftrue[nelec]/D");
    _tree->Branch("epxftrue", _tepxftrue, "epxftrue[nelec]/D");
    _tree->Branch("epyftrue", _tepyftrue, "epyftrue[nelec]/D");
    _tree->Branch("epzftrue", _tepzftrue, "epzftrue[nelec]/D");
    _tree->Branch("eeftrue", _teeftrue, "eeftrue[nelec]/D");
    _tree->Branch("ephiftrue", _tephiftrue, "ephiftrue[nelec]/D");
    _tree->Branch("eetaftrue", _teetaftrue, "eetaftrue[nelec]/D");
  }
  else if (_MCStudy && _MCStudy2){
    _tree->Branch("isW", &_tisW, "isW/O", 666000);
    _tree->Branch("foundWZ", &_tfoundWZ, "foundWZ/O", 666000);
    _tree->Branch("passECTrue", _passECTrue, "passECTrue[nelect]/O", 666000);
    _tree->Branch("passTkPhiFidTrue", _passTkPhiFidTrue, "passTkPhiFidTrue[nelect]/O", 666000);
    _tree->Branch("echgtrue", _techgtrue, "echgtrue[nelect]/I", 666000);
    _tree->Branch("epttrue", _tepttrue, "epttrue[nelect]/D", 666000);
    _tree->Branch("epxtrue", _tepxtrue, "epxtrue[nelect]/D", 666000);
    _tree->Branch("epytrue", _tepytrue, "epytrue[nelect]/D", 666000);
    _tree->Branch("epztrue", _tepztrue, "epztrue[nelect]/D", 666000);
    _tree->Branch("eetrue", _teetrue, "eetrue[nelect]/D", 666000);
    _tree->Branch("ephitrue", _tephitrue, "ephitrue[nelect]/D", 666000);
    _tree->Branch("eetatrue", _teetatrue, "eetatrue[nelect]/D", 666000);
    _tree->Branch("eiphitrue", _teiphitrue, "eiphitrue[nelect]/I", 666000);
    _tree->Branch("eietatrue", _teietatrue, "eietatrue[nelect]/I", 666000);
    _tree->Branch("edetphitrue", _tedetphitrue, "edetphitrue[nelect]/D", 666000);
    _tree->Branch("edetetatrue", _tedetetatrue, "edetetatrue[nelect]/D", 666000);
    _tree->Branch("ephimodtrue", _tephimodtrue, "ephimodtrue[nelect]/D", 666000);
    _tree->Branch("eptftrue", _teptftrue, "eptftrue[nelect]/D", 666000);
    _tree->Branch("epxftrue", _tepxftrue, "epxftrue[nelect]/D", 666000);
    _tree->Branch("epyftrue", _tepyftrue, "epyftrue[nelect]/D", 666000);
    _tree->Branch("epzftrue", _tepzftrue, "epzftrue[nelect]/D", 666000);
    _tree->Branch("eeftrue", _teeftrue, "eeftrue[nelect]/D", 666000);
    _tree->Branch("ephiftrue", _tephiftrue, "ephiftrue[nelect]/D", 666000);
    _tree->Branch("eetaftrue", _teetaftrue, "eetaftrue[nelect]/D", 666000);
 
    _tree->Branch("nptrue", _tnptrue, "nptrue[nnuet]/D", 666000);
    _tree->Branch("npttrue", _tnpttrue, "npttrue[nnuet]/D", 666000);
    _tree->Branch("npxtrue", _tnpxtrue, "npxtrue[nnuet]/D", 666000);
    _tree->Branch("npytrue", _tnpytrue, "npytrue[nnuet]/D", 666000);
    _tree->Branch("npztrue", _tnpztrue, "npztrue[nnuet]/D", 666000);
      
    _tree->Branch("eerawrec", _teerawrec, "eerawrec[nelect]/D", 666000);    
    _tree->Branch("eptrawrec", _teptrawrec, "eptrawrec[nelect]/D", 666000);    
    _tree->Branch("epxrawrec", _tepxrawrec, "epxrawrec[nelect]/D", 666000);    
    _tree->Branch("epyrawrec", _tepyrawrec, "epyrawrec[nelect]/D", 666000);    
    _tree->Branch("epzrawrec", _tepzrawrec, "epzrawrec[nelect]/D", 666000);    
    _tree->Branch("esetrawrec", _tesetrawrec, "esetrawrec[nelect]/D", 666000);    
    _tree->Branch("utrec", &_tutrec, "utrec/D", 666000);
    _tree->Branch("utxrec", &_tutxrec, "utxrec/D", 666000);
    _tree->Branch("utyrec", &_tutyrec, "utyrec/D", 666000);
    _tree->Branch("metrawrec", &_tmetrawrec, "metrawrec/D", 666000);
    _tree->Branch("metxrawrec", &_tmetxrawrec, "metxrawrec/D", 666000);
    _tree->Branch("metyrawrec", &_tmetyrawrec, "metyrawrec/D", 666000);
    _tree->Branch("metzrawrec", &_tmetzrawrec, "metzrawrec/D", 666000);
    _tree->Branch("setrec", &_tsetrec, "setrec/D", 666000);
  }
  
  if (_uEvtDoZ && !_MCStudy2){
    _tree->Branch("zpx", &_tzpx, "zpx/D");
    _tree->Branch("zpy", &_tzpy, "zpy/D");
    _tree->Branch("zpz", &_tzpz, "zpz/D");
    _tree->Branch("zpt", &_tzpt, "zpt/D");
    _tree->Branch("ze", &_tze, "ze/D");
  }
 
  if (_dUParaEffStudy && !_MCStudy2){
    _tree->Branch("passEmfIso", _passEmfIso, "passEmfIso[nelec]/O");
    _tree->Branch("passEmf", _passEmf, "passEmf[nelec]/O");
    _tree->Branch("passIso", _passIso, "passIso[nelec]/O");
    _tree->Branch("passHMx", _passHMx, "passHMx[nelec]/O");
    _tree->Branch("passEC", _passEC, "passEC[nelec]/O");
    _tree->Branch("passCalPhiFid", _passCalPhiFid, "passCalPhiFid[nelec]/O");
    _tree->Branch("passCalEtaFid", _passCalEtaFid, "passCalEtaFid[nelec]/O");
    _tree->Branch("passTrkPhiFid", _passTrkPhiFid, "passTrkPhiFid[nelec]/O");
    _tree->Branch("passFid", _passFid, "passFid[nelec]/O");
    _tree->Branch("passECFid", _passECFid, "passECFid[nelec]/O");
    _tree->Branch("passTkMatch", _passTkMatch, "passTkMatch[nelec]/O");
    _tree->Branch("passTkMatchLoose", _passTkMatchLoose, "passTkMatchLoose[nelec]/O", 666000);
    _tree->Branch("passElPt", _passElPt, "passElPt[nelec]/O");
    _tree->Branch("passEID", _passEID, "passEID[nelec]/O");
    if (_uEvtDoZ){
      _tree->Branch("passBothPt", &_passBothPt, "passBothPt/O");
      _tree->Branch("passCCECFid", &_passCCECFid, "passCCECFid/O");
      _tree->Branch("passECECFid", &_passECECFid, "passECECFid/O");
      _tree->Branch("passBothTkMatch", &_passBothTkMatch, "passBothTkMatch/O");
    } else if (_uEvtDoW){
      _tree->Branch("passCutMet", &_passCutMet, "passCutMet/O");
      _tree->Branch("passCutWMt", &_passCutWMt, "passCutWMt/O");
    }
    _tree->Branch("passCutUt", &_passCutUt, "passCutUt/O");
  }

  if (_uEvtStoreAllElecCells && !_MCStudy2) {
    _tree->Branch("encells", _tencells, "encells[nelec]/I");
    _tree->Branch("ecellilayer", _tecellilayer, "ecellilayer[nelec][200]/I", 6666666); 
    _tree->Branch("ecellieta", _tecellieta, "ecellieta[nelec][200]/I", 6666666); 
    _tree->Branch("ecelliphi", _tecelliphi, "ecelliphi[nelec][200]/I", 6666666); 
    _tree->Branch("ecelle", _tecelle, "ecelle[nelec][200]/D", 6666666); 
    // 1: normal cell, 0: not normal cell
    _tree->Branch("ecellstat", _tecellstat, "ecellstat[nelec][200]/I", 6666666); 
  }

  // store all cones in 2Pi if not _MCStudy2
  if (_uEvtStoreAllCones && !_MCStudy2) {
    _tree->Branch("conede", _tconede, "conede[nelec][64]/D", 256000);
    _tree->Branch("conedet", _tconedet, "conedet[nelec][64]/D", 256000);
    _tree->Branch("conephi", _tconephi, "conephi[nelec][64]/D",256000);
    _tree->Branch("coneiphi", _tconeiphi, "coneiphi[nelec][64]/I",256000);
  }
  // store all cones in 2Pi if _MCStudy2
  if (_uEvtStoreAllCones && _MCStudy2) {
    _tree->Branch("conede", _tconede, "conede[nelect][64]/D", 6666666);
    _tree->Branch("conedet", _tconedet, "conedet[nelect][64]/D", 6666666);
    _tree->Branch("coneiphi", _tconeiphi, "coneiphi[nelect][64]/I",6666666);
  } 
     
  // Radius (in cm) of the EC cone
  _radiusEC = config.get("radiusEC", 10.);

}


void uEventAnalysisEC::begin() {}
void uEventAnalysisEC::finish() {

  _uEventOutFile->Write();
  _uEventOutFile->Close();

}

bool uEventAnalysisEC::processEvent(cafe::Event& event) {

  // Get calorimeter geometry manager
  CaloGeometryManager::get_instance();
  const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
  const TMBCellContainer *calocells = event.get<TMBCellContainer>("CaloCells");

  float vtx_x, vtx_y, vtx_z;
  vector<CAFEMObj*> emobjs;
  std::vector<TMBMCpart *> raw_mc_electrons;
  std::vector<TMBMCpart *> em_mc_objects;
  std::vector<TMBMCpart *> mc_neutrinos;

  TMBMCpart* WZ;
  CAFMet met;
  CAFMet rawmet;
  int triglist_flag = -1;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;
  double mc_data_lumi_ratio = 1.;

  // Run and Event numbers
  _runNum = event.getGlobal()->runno();
  _eventNum = event.getGlobal()->evtno();

  // InstLumi
  if ( !(event.get("InstLumi", _tlumi)) ){
    _tlumi = -1e100;
  } 

  // ZB runNo and evtNo if MCStudy
  if (_MCStudy){
    _ZBrunNum = event.getMCEventInfo()->overlayrun();
    _ZBeventNum = event.getMCEventInfo()->overlayevtid();
  }
  
  // vertex
  if (event.get("New primary vertexX", vtx_x) && event.get("New primary vertexY", vtx_y) && event.get("New primary vertexZ", vtx_z)) {
    _tvtx[0] = vtx_x;
    _tvtx[1] = vtx_y;
    _tvtx[2] = vtx_z;
  } else {
    _tvtx[0] = -1e100;
    _tvtx[1] = -1e100;
    _tvtx[2] = -1e100;
  }
   
  // MC study store truth
  if (_MCStudy){
    event.get("raw mc electrons", raw_mc_electrons);
    event.get("em mc objects", em_mc_objects);
    event.get("WZ boson object", WZ);
    event.get("mc neutrinos", mc_neutrinos);
  }

  // Store and only store all true EMobjs and corresponding reconstructed EM objs
  // only if _MCStudy2 is also on
  if (_MCStudy && _MCStudy2){
    _tnelect = em_mc_objects.size();
    _tnelec = 0;

    _tisW = (WZ->abspdgid()==23) ? false : true;
    _tvtxtrue[0] = WZ->getDMCvtx()->x();
    _tvtxtrue[1] = WZ->getDMCvtx()->y();
    _tvtxtrue[2] = WZ->getDMCvtx()->z();
    _tuttrue = WZ->Pt();
    _tutxtrue = -WZ->Px();
    _tutytrue = -WZ->Py();
    _tutztrue = -WZ->Pz();

    // protection against too many true EMObjs
    if (_tnelect>10) {
      cout << "Warning:: Too many true EMObjs to be stored! return! Nelec=" << _tnelect << endl;
      return false;
    }

    // loop over incone FSR merged EMObjs
    for (int ielec=0; ielec<_tnelect; ielec++) {
      _teeftrue[ielec] = em_mc_objects[ielec]->E();
      _teptftrue[ielec] = em_mc_objects[ielec]->Pt();
      _tepxftrue[ielec] = em_mc_objects[ielec]->Px();
      _tepyftrue[ielec] = em_mc_objects[ielec]->Py();
      _tepzftrue[ielec] = em_mc_objects[ielec]->Pz();
      _teetaftrue[ielec] = em_mc_objects[ielec]->Eta();
      _tephiftrue[ielec] = em_mc_objects[ielec]->Phi();

      int pdgid = em_mc_objects[ielec]->pdgid();
      if (pdgid==11) {
        _techgtrue[ielec] = -1;
      }
      else if (pdgid==-11){
        _techgtrue[ielec] = 1;
      }
      else {
        _techgtrue[ielec] = 0;
      }
      
      int iindex = em_mc_objects[ielec]->GetGEANTindex();    
      int jindex = -100;
      // loop over raw EMObjs to find the corresponding raw EMObj
      int jelec=0;
      for (jelec=0; jelec<raw_mc_electrons.size(); jelec++){
        jindex = raw_mc_electrons[jelec]->GetGEANTindex();
        if (iindex == jindex) {
          _teetrue[ielec] = raw_mc_electrons[jelec]->E();
          _tepttrue[ielec] = raw_mc_electrons[jelec]->Pt();
          _tepxtrue[ielec] = raw_mc_electrons[jelec]->Px();
          _tepytrue[ielec] = raw_mc_electrons[jelec]->Py();
          _tepztrue[ielec] = raw_mc_electrons[jelec]->Pz();
          _teetatrue[ielec] = raw_mc_electrons[jelec]->Eta();
          _tephitrue[ielec] = raw_mc_electrons[jelec]->Phi();
          break;
        }
      }

      // calculate other variables

      // calculate true det eta, assuming R = 91.9 cm (distrance from beam pipe to EM3) 
      //  and an alignment shift dz = 3.0 cm Cal system with respect to Tracking system
      // sinh(deteta) = (vtx_z+dz)/R + sinh(eta)
      _tedetetatrue[ielec] = TMath::ASinH((_tvtxtrue[2]+3.0)/91.9 + TMath::SinH(_teetatrue[ielec]));
    
      // calculate true phi at EM3 or true det. phi
      _tedetphitrue[ielec] = _tephitrue[ielec] - _techgtrue[ielec] * 21.1/91.9 / _tepttrue[ielec];

      // calculate detector ieta and iphi
      _teietatrue[ielec] = (_tedetetatrue[ielec]>0) ? (int(_tedetetatrue[ielec]/0.1)+1) : (int(_tedetetatrue[ielec]/0.1)-1);
      _teiphitrue[ielec] = int(_tedetphitrue[ielec]/0.1) + 1;

      // EC cut on true det eta
      _passECTrue[ielec] = (fabs(_tedetetatrue[ielec])>_DetEtaEC1 && abs(_tedetetatrue[ielec])<_DetEtaEC2);

      // phimod based on tedetphitrue
      _tephimodtrue[ielec] = fmod(16.0*_tedetphitrue[ielec]/TMath::Pi(),1.0);

      // passTkPhiFidTrue
      _passTkPhiFidTrue[ielec] = (_tephimodtrue[ielec]>0.1&&_tephimodtrue[ielec]<0.9);
 
      // preset all the corresponding reconstructed EMObjs
      _passCluster[ielec] = false;
      _passEC[ielec] = false; 
      _passECFid[ielec] = false;
      _passFid[ielec] = false;
      _passCalEtaFid[ielec] = false;
      _passCalPhiFid[ielec] = false; 
      _passTrkPhiFid[ielec] = false; 
      _passEmf[ielec] = false; 
      _passIso[ielec] = false; 
      _passEmfIso[ielec] = false; 
      _passHMx[ielec] = false; 
      _passTkMatchLoose[ielec] = false; 
      _passTkMatch[ielec] = false; 
      _teindex[ielec] = -100;
      _tee[ielec] = -1e100;
      _teeuc[ielec] = -1e100;
      _tept[ielec] = -1e100; 
      _tepx[ielec] = -1e100; 
      _tepy[ielec] = -1e100; 
      _tepz[ielec] = -1e100; 
      _tephi[ielec] = -1e100; 
      _teeta[ielec] = -1e100; 
      _tedeteta[ielec] = -1e100; 
      _tedetphi[ielec] = -1e100; 
      _tetkpt[ielec] = -1e100; 
      _techg[ielec] = -1e100; 
    }

 
    // protection of very low pt electrons
    for (int ielec=0; ielec<_tnelect; ielec++){
      if (_teptftrue[ielec]<10.0) return false;
    }

    if ( event.get("Good EMObjs", emobjs) ){

      // set n reconstructed emobjs
      _tnelec = emobjs.size();

      //loop over all the reconstructed EMobjs
      for (int irelec=0; irelec<_tnelec; irelec++){

        // loop over all the true EMobjs to find the corresponding one
        double dRmin = 1e100;
        int itelecmin = 0;
        int itelec = 0;
        for (itelec=0; itelec<_tnelect; itelec++){
          double dR = kinem::delta_R(_teetaftrue[itelec], _tephiftrue[itelec], emobjs[irelec]->Eta(), emobjs[irelec]->Phi());
          if (dR<dRmin){
            dRmin = dR;
            itelecmin = itelec;
          }
        }

        // decide if assign this reconstructed EMObj to the corresponding true EMObj
        bool assign = false;
        // check if this is near enough with dR<0.3, otherwise a mis-identified reconstructed EMObjs
        // if true, assign the values to the corresponding true EMObj
        if (dRmin<0.3){
          // this true EMObj to see if it has already been assigned a reconstructed EMObjs?
          if (!(_passCluster[itelecmin])) {
            assign = true;
          } else if (_tept[itelecmin]< emobjs[irelec]->Pt()) 
	    assign = true;
        }

	// Do not count unindentified electron yet.

	//        else {
	//          if ((emobjs[irelec]->PassEMFrac(_EMFracCut)&&emobjs[irelec]->PassIso(_IsoCut)&&emobjs[irelec]->PassHMx(_HM7Cut,_HM8Cut)&&emobjs[irelec]->has_good_spatial_track_match(0.01,_require_smt))) {
	//            _nelec_misidentified++;
	//          }
	//        } // if (dRmin<0.3) .. else ...

        if (assign){
          _passCluster[itelecmin] = true;
          _passEC[itelecmin] = emobjs[irelec]->IsEC(_DetEtaEC1,_DetEtaEC2);
          _passFid[itelecmin] = emobjs[irelec]->is_in_fiducial();
          _passECFid[itelecmin] = emobjs[irelec]->IsECFid(_DetEtaEC1,_DetEtaEC2);
          _passCalEtaFid[itelecmin] = emobjs[irelec]->is_in_eta_fiducial();
          _passCalPhiFid[itelecmin] = emobjs[irelec]->is_in_phi_fiducial();
          _passTrkPhiFid[itelecmin] = emobjs[irelec]->is_in_TrkPhiFid();
          _passEmf[itelecmin] = emobjs[irelec]->PassEMFrac(_EMFracCut);
          _passIso[itelecmin] = emobjs[irelec]->PassIso(_IsoCut);
          _passHMx[itelecmin] = emobjs[irelec]->PassHMx(_HM7Cut,_HM8Cut);
          _passTkMatch[itelecmin] = emobjs[irelec]->has_good_spatial_track_match(0.01,_require_smt,10.,_require_smtEC);
          _passTkMatchLoose[itelecmin] = emobjs[irelec]->has_spatial_track_match(-0.5);
 
          _teindex[itelecmin] = irelec; // index of the reconstructed EMobj in emobjs
          _tee[itelecmin] = emobjs[irelec]->CalE();
          _teeuc[itelecmin] = emobjs[irelec]->uncorrE();
          _tept[itelecmin] = emobjs[irelec]->Pt();
          _tepx[itelecmin] = emobjs[irelec]->Px();
          _tepy[itelecmin] = emobjs[irelec]->Py();
          _tepz[itelecmin] = emobjs[irelec]->Pz();
          _tephi[itelecmin] = emobjs[irelec]->Phi();
          _teeta[itelecmin] = emobjs[irelec]->Eta();
          _tedeteta[itelecmin] = emobjs[irelec]->CalDetectorEta();
          _tedetphi[itelecmin] = TVector2::Phi_0_2pi(emobjs[irelec]->CalDetectorPhi());
          _teetaem3[itelecmin] = emobjs[irelec]->TrkEtaEM3();
          _tephiem3[itelecmin] = TVector2::Phi_0_2pi(emobjs[irelec]->TrkPhiEM3());
          _tephimod[itelecmin] = fmod(16.0*_tephiem3[itelecmin]/TMath::Pi(),1.0);   
          _techg[itelecmin] = emobjs[irelec]->charge();
          _tetkpt[itelecmin] = emobjs[irelec]->getPtrChp() ? emobjs[irelec]->getPtrChp()->Pt() : 0 ;
        } // if (assign) ..
      } // Reconstructed electrons
    } // Good EM objects
 
    // Calculate other variables from reconstructed EMObjs if they are found.
    // Firstly, preset these variables
    _tfoundWZ = false; // if a W or Z can be found based on the reconstructed EMObjs
    _tut = -1e100;
    _tutx = -1e100;
    _tuty = -1e100;
    _tutphi = -1e100;
    _tmet = -1e100;
    _tmetx = -1e100;
    _tmety = -1e100;
    _tmetphi = -1e100;
    _tset = -1e100;
  
    // Calculate "Raw MET"
    if (event.get("Raw Met", rawmet)){
      //cout << "got rawmet" ;
      // if the true Boson is W and the cluster of the leading Electron is found, and vertex is reconstructed
      if (_tisW && _passCluster[0] && _tvtx[0]>-1e10 && _tvtx[1]>-1e10 && _tvtx[2]>-1e10) {
        CAFEMObj* emobj = emobjs[_teindex[0]];

        // corrected EM vector
        TVector2 em_vec(emobj->Px(), emobj->Py());
        // raw EM vector and raw EM SET 
        float raw_em_set = 0.0; // be filled right after
        float vtx[3]; 
        vtx[0] = (float)_tvtx[0];
        vtx[1] = (float)_tvtx[1];
        vtx[2] = (float)_tvtx[2];
        TVector2 raw_em_vec = emobj->getRawElecVectorFromCells(vtx, &raw_em_set);
        // raw MET vector
        TVector2 raw_met_vec(rawmet.metx(), rawmet.mety());
        // raw SET 
        double raw_set = rawmet.scalarEt();

        // UT vector , calculated from raw MET and raw EM
        TVector2 ut_vec = -1. *(raw_em_vec + raw_met_vec);
        // consistent MET vector, from the (raw) UT vector and corrected EM vector
        TVector2 met_vec = -1. *(ut_vec + em_vec);
        // EM subtracted SET
        double set = raw_set - (double)raw_em_set;
 
        _tfoundWZ = true;
        _tut = ut_vec.Mod();
        _tutx = ut_vec.Px();
        _tuty = ut_vec.Py();
        _tutphi = ut_vec.Phi();
        _tmet = met_vec.Mod();
        _tmetx = met_vec.Px();
        _tmety = met_vec.Py();
        _tmetphi = met_vec.Phi();
        _tset = set;
 
      } 
      // if the true Boson is Z and the two clusters of the two leading electrons are found
      else if (!_tisW && _passCluster[0] && _passCluster[1] && _tvtx[0]>-1e10 && _tvtx[1]>-1e10 && _tvtx[2]>-1e10) {
        CAFEMObj* emobj1 = emobjs[_teindex[0]];
        CAFEMObj* emobj2 = emobjs[_teindex[1]];

        // corrected EM vector
        TVector2 em_vec1(emobj1->Px(), emobj1->Py());
        TVector2 em_vec2(emobj2->Px(), emobj2->Py());
        // raw EM vector and raw EM SET 
        float raw_em_set1 = 0.0; // be filled right after
        float raw_em_set2 = 0.0; // be filled right after
        float vtx[3];
        vtx[0] = (float)_tvtx[0];
        vtx[1] = (float)_tvtx[1];
        vtx[2] = (float)_tvtx[2];
        TVector2 raw_em_vec1 = emobj1->getRawElecVectorFromCells(vtx, &raw_em_set1);
        TVector2 raw_em_vec2 = emobj2->getRawElecVectorFromCells(vtx, &raw_em_set2);
        // raw MET vector
        TVector2 raw_met_vec(rawmet.metx(), rawmet.mety());
        // raw SET 
        double raw_set = rawmet.scalarEt();

        // UT vector , calculated from raw MET and raw EM
        TVector2 ut_vec = -1. *(raw_em_vec1 + raw_em_vec2 + raw_met_vec);
        // consistant MET vector, from the (raw) UT vector and corrected EM vector
        TVector2 met_vec = -1. *(ut_vec + em_vec1 + em_vec2);
        // EM subtracted SET
        double set = raw_set - (double)raw_em_set1 - (double)raw_em_set2;

        _tfoundWZ = true;
        _tut = ut_vec.Mod();
        _tutx = ut_vec.Px();
        _tuty = ut_vec.Py();
        _tutphi = ut_vec.Phi();
        _tmet = met_vec.Mod();
        _tmetx = met_vec.Px();
        _tmety = met_vec.Py();
        _tmetphi = met_vec.Phi();
        _tset = set;
      } // if (_tisW) ... else ... 
    } // if (event.get("Raw Met", ...

  
    // re-calculate everything based on truth and cell level information. 
    // i.e. in case no EMobj has been reconstructed, we could use the truth to "guide" us to find the reconstructed EMobj
    // However, then, no EM correction has been considered 
    // preset variable
    _tutrec = -1e100;
    _tutxrec = -1e100;
    _tutyrec = -1e100;
    _tmetrawrec = -1e100;
    _tmetxrawrec = -1e100;
    _tmetyrawrec = -1e100;
    _tsetrec = -1e100;
    for (int ielec=0; ielec<_tnelect; ielec++){
      _teerawrec[ielec] = -1e100;
      _teptrawrec[ielec] = -1e100;
      _tepxrawrec[ielec] = -1e100;
      _tepyrawrec[ielec] = -1e100;
      _tepzrawrec[ielec] = -1e100;
      _tesetrawrec[ielec] = -1e100;
      // if store all 64 cones energies 
      if (_uEvtStoreAllCones){
        // reset energy of 64 cones, and give cone phi values
        for (int icone=0; icone<64; icone++){
          _tconede[ielec][icone] = 0;
          _tconedet[ielec][icone] = 0;
          _tconedpx[ielec][icone] = 0;
          _tconedpy[ielec][icone] = 0;
          _tconeupara[ielec][icone] = 0;
          _tconeuperp[ielec][icone] = 0;
          _tconephi[ielec][icone] = double((icone)*(2.0*TMath::Pi()/64.));
          _tconeiphi[ielec][icone] = icone+1;
        }
      } // store all 64 cones
    }
    //cout << " reconstruct EMobj based on truth" << endl;
    // reconstruct EMobj based on truth
    for (int ielec=0; ielec<_tnelect; ielec++){

      //cout << " first iteration of all the cells of the events to associate a 13-tows to the true electron." << endl;
      // first iteration of all the cells of the events to associate a 13-tows to the true electron.
      int elec_ieta_raw = _teietatrue[ielec];
      int elec_iphi_raw = _teiphitrue[ielec];
      int elec_ieta(-1), elec_iphi(-1), elec_layer(-1);
      vector<const TMBCaloCell*> elec_cells = GetBestECClusterFromTrue(event, elec_ieta_raw, elec_iphi_raw, _radiusEC, elec_ieta, elec_iphi, elec_layer);
      double elec_raw_e(0), elec_raw_pt(0), elec_raw_px(0), elec_raw_py(0), elec_raw_pz(0), elec_raw_et(0);

      // if store all 64 cones energies 
      if (_uEvtStoreAllCones){
	// loop over all cones, if a cell is in one cone, add in the cell energy into the cone energy
	for (int icone=0; icone<64; icone++){
	  GetECRotatedCone(event, elec_ieta, icone+1, elec_layer, _tvtxtrue, _radiusEC, _tconede[ielec][icone], _tconedpx[ielec][icone], _tconedpy[ielec][icone]);
          _tconedet[ielec][icone] = sqrt(_tconedpx[ielec][icone]*_tconedpx[ielec][icone] + _tconedpy[ielec][icone]*_tconedpy[ielec][icone]);
	}// loop over all cones
      } //64 cones
      

      for(int icell=0; icell<elec_cells.size(); icell++) {
        const TMBCaloCell *thecell = elec_cells[icell];

        int cell_ieta = thecell->ieta();
        int cell_iphi = thecell->iphi();
        int cell_ilayer = thecell->layer();
        double cell_E = thecell->E();

        // calorimeter cell position
        int cell_index = wz_utils::EncodeCellIndex(cell_ieta, cell_iphi, cell_ilayer);
        map<int, CELLXYZ_STRUCT>::const_iterator iter = calogeometry_map.find(cell_index);
        CELLXYZ_STRUCT cellgeo = (*iter).second;
        float cell_pos[3] = { cellgeo.x, cellgeo.y, cellgeo.z };

        // calculate px py pz of a given cell 
        double direction[3];
        direction[0] = cell_pos[0] - _tvtxtrue[0];
        direction[1] = cell_pos[1] - _tvtxtrue[1];
        direction[2] = cell_pos[2] - _tvtxtrue[2];
        double length = sqrt(direction[0]*direction[0]+direction[1]*direction[1]+direction[2]*direction[2]);
        double cell_Px = cell_E * direction[0]/length;
        double cell_Py = cell_E * direction[1]/length;
        double cell_Pz = cell_E * direction[2]/length;
        double cell_Et = sqrt(cell_Px*cell_Px+cell_Py*cell_Py);

	elec_raw_e += cell_E;
	elec_raw_px += cell_Px;
	elec_raw_py += cell_Py;
	elec_raw_pz += cell_Pz;
	elec_raw_et += cell_Et;
      }
      
      // vector sum as electron pt
      elec_raw_pt = sqrt(elec_raw_px*elec_raw_px+elec_raw_py*elec_raw_py);

      // assign values
      _teerawrec[ielec] = elec_raw_e;
      _teptrawrec[ielec] = elec_raw_pt;
      _tepxrawrec[ielec] = elec_raw_px;
      _tepyrawrec[ielec] = elec_raw_py;
      _tepzrawrec[ielec] = elec_raw_pz;
      _tesetrawrec[ielec] = elec_raw_et;

    } // for (int ielec=0; ...

    // reconstruct ut met set
    std::vector<double> met = GetMet(event, _tvtxtrue);   
    // if the true Boson is W 
    if (_tisW) {
      // raw EM SET 
      double raw_em_set = _tesetrawrec[0];
      // raw EM vector
      TVector2 raw_em_vec(_tepxrawrec[0], _tepyrawrec[0]);
      // raw MET vector
      TVector2 raw_met_vec(met[0], met[1]);
      // raw SET 
      double raw_set = met[4];

      // UT vector , calculated from raw MET and raw EM
      TVector2 ut_vec = -1. *(raw_em_vec + raw_met_vec);
      // EM subtracted SET
      double set = raw_set - (double)raw_em_set;

      _tutrec = ut_vec.Mod();
      _tutxrec = ut_vec.Px();
      _tutyrec = ut_vec.Py();
      _tmetrawrec = raw_met_vec.Mod();
      _tmetxrawrec = raw_met_vec.Px();
      _tmetyrawrec = raw_met_vec.Py();
      _tmetzrawrec = met[3];
      _tsetrec = set;
    }
    // if the true Boson is Z
    else {
      // raw EM SET 
      double raw_em_set1 = _tesetrawrec[0];
      double raw_em_set2 = _tesetrawrec[1];
      // raw EM vector
      TVector2 raw_em_vec1(_tepxrawrec[0], _tepyrawrec[0]);
      TVector2 raw_em_vec2(_tepxrawrec[1], _tepyrawrec[1]);
      // raw MET vector
      TVector2 raw_met_vec(rawmet.metx(), rawmet.mety());
      // raw SET 
      double raw_set = rawmet.scalarEt();

      // UT vector , calculated from raw MET and raw EM
      TVector2 ut_vec = -1. *(raw_em_vec1 + raw_em_vec2 + raw_met_vec);
      // EM subtracted SET
      double set = raw_set - raw_em_set1 - raw_em_set2;

      _tutrec = ut_vec.Mod();
      _tutxrec = ut_vec.Px();
      _tutyrec = ut_vec.Py();
      _tmetrawrec = raw_met_vec.Mod();
      _tmetxrawrec = raw_met_vec.Px();
      _tmetyrawrec = raw_met_vec.Py();
      _tsetrec = set;

    }  //end:: reconstruct ut met set


    // neutrino truth
    _tnnuet = (int)mc_neutrinos.size();
    for (int i=0; i<_tnnuet; i++){
      _tnptrue[i] = mc_neutrinos[i]->E();
      _tnpttrue[i] = mc_neutrinos[i]->Pt();
      _tnpxtrue[i] = mc_neutrinos[i]->Px();
      _tnpytrue[i] = mc_neutrinos[i]->Py();
      _tnpztrue[i] = mc_neutrinos[i]->Pz();
    }

    _tree->Fill();

  } // if (_MCStudy && _MCStudy2) ..

  if ( !_MCStudy2 &&
      event.get("Good EMObjs", emobjs) && event.get("EMCorr Met", met) && event.get("Raw Met", rawmet) &&
      event.get("L1CalTowers", l1cal_vec) && event.get("L1Cal2bTowers", l1cal2b_vec) && event.get("L2GblEMs", l2cal_vec) &&
      event.get("L3Eles", l3cal_vec) && 
      event.get("triglist flag", triglist_flag) &&
      event.get("MC Data LumiRatio", mc_data_lumi_ratio) ) {

    // good cc electrons
    vector<CAFEMObj*> emobjs_cc;
    vector<CAFEMObj*> emobjs_ec;

    // primary vertex
    float vtx[3] = {vtx_x, vtx_y, vtx_z};

    // scalar Et
    double ScalarEt;

    // read cells infomation
    const TMBCellContainer * fCells = event.getCaloCells();
    int numcells = fCells->NumCells();
   
    // recoil system for W or Z events
    TVector2 recoil_vect;

    // number of electrons
    int Nele = emobjs.size();

    // at least 1 emobj
    if (Nele<1) return false;

    // trigger
    bool pass_trigger = false;

    // if MC, pass_trigger is true
    if (_MCStudy) pass_trigger = true;
    else {
      pass_trigger = emobjs[0]->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec);
      if (Nele>1) {
        pass_trigger = pass_trigger || emobjs[1]->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec);
      }
    }

    // need pass trigger 
    if (!pass_trigger) return false;

    // ieta and iphi of emobjs
    vector<int> emobjs_ieta, emobjs_iphi, emobjs_layer;

    // ieta and iphi of emobjs_cc
    vector<int> emobjs_cc_ieta, emobjs_cc_iphi;
    vector<int> emobjs_ec_ieta, emobjs_ec_iphi;

    // loop over all emobjs to find electron window center
    for(int ielec=0; ielec<Nele; ielec++) {
      const CAFEMObj *emobj = emobjs[ielec];
      int emobj_ieta, emobj_iphi, emobj_layer;
      GetBestECClusterFromReco(emobj, emobj_ieta, emobj_iphi, emobj_layer);

      emobjs_ieta.push_back(emobj_ieta);
      emobjs_iphi.push_back(emobj_iphi);
      emobjs_layer.push_back(emobj_layer);

    } // find electron center

    // select good EC emobjs_ec
    for (int ielec=0; ielec<min(2,Nele); ielec++) {

      if (_debugLevel > 1000) {
	if (emobjs[ielec]->IsEC(_DetEtaEC1, _DetEtaEC2)) {
	  cout << "Track match " << emobjs[ielec]->has_good_spatial_track_match(0.01,_require_smt,10.,_require_smtEC) << endl;
	  cout << "Pt          " << (emobjs[ielec]->Pt()>_ElecPtCut) << endl;
	  cout << "EMID        " << emobjs[ielec]->PassEMFracIso(_EMFracCut,_IsoCut) << endl;
	  cout << "EC fiducial " << emobjs[ielec]->IsECFid(_DetEtaEC1,_DetEtaEC2) << endl;
	} 
      }

      // if _dUParaEffStudy pass all EC electrons
      if (_dUParaEffStudy && emobjs[ielec]->IsEC(_DetEtaEC1,_DetEtaEC2)) {
        emobjs_ec.push_back(emobjs[ielec]);
        emobjs_ec_ieta.push_back(emobjs_ieta[ielec]);
        emobjs_ec_iphi.push_back(emobjs_iphi[ielec]);
      } else if (emobjs[ielec]->IsECFid(_DetEtaEC1,_DetEtaEC2) &&
		 emobjs[ielec]->Pt()>_ElecPtCut &&
		 emobjs[ielec]->PassEMFracIso(_EMFracCut,_IsoCut) &&
		 emobjs[ielec]->PassHMx(_HM7Cut,_HM8Cut) &&
		 emobjs[ielec]->has_good_spatial_track_match(0.01,_require_smt,10.,_require_smtEC)) {
	emobjs_ec.push_back(emobjs[ielec]);
	emobjs_ec_ieta.push_back(emobjs_ieta[ielec]);
	emobjs_ec_iphi.push_back(emobjs_iphi[ielec]);
      }
    }

    // select good CC emobjs_cc
    for (int ielec=0; ielec<min(2,Nele); ielec++) {
      // if _dUParaEffStudy pass all EC electrons
      if (_dUParaEffStudy && emobjs[ielec]->IsCC(_DetEtaCC)) {
        emobjs_cc.push_back(emobjs[ielec]);
        emobjs_cc_ieta.push_back(emobjs_ieta[ielec]);
        emobjs_cc_iphi.push_back(emobjs_iphi[ielec]);
      } else if (emobjs[ielec]->IsCCFid(_DetEtaCC) &&
		 emobjs[ielec]->Pt()>_ElecPtCut &&
		 emobjs[ielec]->PassEMFracIso(_EMFracCut,_IsoCut) &&
		 emobjs[ielec]->PassHMx(_HM7Cut,_HM8Cut) &&
		 emobjs[ielec]->has_good_spatial_track_match(0.01,_require_smt,10.,_require_smtEC)) {
	emobjs_cc.push_back(emobjs[ielec]);
	emobjs_cc_ieta.push_back(emobjs_ieta[ielec]);
	emobjs_cc_iphi.push_back(emobjs_iphi[ielec]);
      }
    }

    // number of CC electrons to be used
    int NeleCC = emobjs_cc.size();
    int NeleEC = emobjs_ec.size();

    // calculate recoil_vec
    if (_uEvtDoZ) {

      // if emobjs less than 2 or emobjs_cc less than 1, give up
      if (Nele < 2) return 0;
      if (_uEvtCCEC && (NeleEC < 1 || NeleCC < 1)) return 0;
      if (_uEvtECEC && NeleEC < 2) return 0;

      // Z candidate

      CAFZCand zcand = CAFZCand (emobjs[0], emobjs[1], &rawmet, vtx, true);
      
      // Z 4 vector
      _tzpx = zcand.Px();
      _tzpy = zcand.Py();
      _tzpz = zcand.Pz();
      _tzpt = zcand.Pt();
      _tze = zcand.E();

      // Z selection cuts
      // both electrons pass _ElecPtCut
      _passBothPt = (emobjs[0]->Pt()>_ElecPtCut && emobjs[1]->Pt()>_ElecPtCut);
      // fiducial requirement
      _passCCECFid = (emobjs[0]->IsCCFid(_DetEtaCC) && emobjs[1]->IsECFid(_DetEtaEC1,_DetEtaEC2)) || (emobjs[0]->IsECFid(_DetEtaEC1,_DetEtaEC2) && emobjs[1]->IsCCFid(_DetEtaCC));
      _passECECFid = (emobjs[0]->IsECFid(_DetEtaEC1,_DetEtaEC2) && emobjs[1]->IsECFid(_DetEtaEC1,_DetEtaEC2));
      // both electron good track match
      _passBothTkMatch = (emobjs[0]->has_good_spatial_track_match(0.01,_require_smt,10.,_require_smtEC) &&
                          emobjs[1]->has_good_spatial_track_match(0.01,_require_smt,10.,_require_smtEC)) ;
      // Boson Ut cut 
      _passCutUt = (zcand.MagRecoil()<_ZUtCut);

      // if not _dUParaEffStudy, apply the Z cuts; or, booleans will be stored
      if (!_dUParaEffStudy){ 
        if (_uEvtCutBothPt && !_passBothPt) return 0;
        if (_uEvtCCEC && !_passCCECFid) return 0;
        if (_uEvtECEC && !_passECECFid) return 0;
        if (_uEvtBothTrackMatch && !_passBothTkMatch ) return 0;
        if (_uEvtCutUt && !_passCutUt) return 0;
      }  
 
      recoil_vect = zcand.GetRecoil();
    }
    else if (_uEvtDoW) {

      if (_debugLevel > 1000) {
	if (NeleEC > 0)
	  cout << "W event with this amount of EM clusters " << Nele << " "  << NeleCC << " " << NeleEC << endl;
      }

      // if emobjs less than 1 or emobjs_cc less than 1, give up
      if (Nele < 1 || NeleEC < 1) return 0;

      // construct W candidate
      CAFWCand wcand = CAFWCand(emobjs_ec[0], &rawmet, vtx, true);

      // W selection cuts
      // pass W Ut cut
      _passCutUt = (wcand.MagRecoil()<_WUtCut);
      // pass Met cut
      _passCutMet = (met.met()>_WMetCut);
      // pass W Mt cut
      _passCutWMt = (wcand.Mt()>_WMtCut1 && wcand.Mt()<_WMtCut2);


      if (_debugLevel > 1000) {
	cout << "Ut cut  " << _passCutUt << endl
	     << "MET cut " << _passCutMet << endl
	     << "Mt cut  " << _passCutWMt << endl;
      }

      // if not _dUParaEffStudy, apply these cuts.
      if (!_dUParaEffStudy){ 
        if (_uEvtCutUt && !_passCutUt) return 0;
        if (_uEvtCutMet && !_passCutMet) return 0;
        if (_uEvtCutWMt && !_passCutWMt) return 0;
      }

      recoil_vect =  wcand.GetRecoil();
    }
    else {
      cout << " uEventAnalysis:: Error: please set uEvtDoW or uEvtDoZ " << endl; 
      return 0;
    }

    // calculate scalarEt and remove contribution due to two electrons
    ScalarEt = rawmet.scalarEt();
    float cntrib1=0;
    float cntrib2=0;
    emobjs[0]->getRawElecVectorFromCells(vtx,&cntrib1);
    if (_uEvtDoZ && Nele>1) emobjs[1]->getRawElecVectorFromCells(vtx,&cntrib2);
    double ScalarEt_EMObjs = cntrib1 + cntrib2;
    ScalarEt -= ScalarEt_EMObjs;
   
    // loop over EC electrons to calculate dUPara and fill Hist and tree
    for(int ielec=0; ielec<NeleEC; ielec++) {
      const CAFEMObj *emobj = emobjs_ec[ielec];  

      int elec_ieta = emobjs_ec_ieta[ielec];
      int elec_iphi = emobjs_ec_iphi[ielec];

      // from elec_iphi to phi_elec
      double phi_elec = double((elec_iphi-1)*(2.0*TMath::Pi()/64.)); 

      // from elec_ieta to eta_elec
      double eta_elec = elec_ieta>0. ? double((elec_ieta-1)*0.1) : double((elec_ieta+1)*0.1);

      // recoil phi
      double phi_recoil = recoil_vect.Phi();

      // Calculate U-Parallel      
      TVector2 elec_unit_vect(cos(phi_elec), sin(phi_elec));
      double upara = recoil_vect * elec_unit_vect;
      double uperp = recoil_vect * elec_unit_vect.Rotate(TMath::Pi()/2.);

      if (_debugLevel > 1000) {
	cout << "Electron direction " << elec_ieta << " " << elec_iphi << endl;
      }

      if (_uEvtStoreAllElecCells){
        _tencells[ielec] = 0;
      } 

      // if store all 64 cones energies 
      if (_uEvtStoreAllCones){
        // reset energy of 64 cones, and give cone phi values
        for (int icone=0; icone<64; icone++){
          _tconede[ielec][icone] = 0;
          _tconedet[ielec][icone] = 0;
          _tconedpx[ielec][icone] = 0;
          _tconedpy[ielec][icone] = 0;
          _tconeupara[ielec][icone] = 0;
          _tconeuperp[ielec][icone] = 0;
          _tconephi[ielec][icone] = double((icone)*(2.0*TMath::Pi()/64.));
          _tconeiphi[ielec][icone] = icone+1;
        }
      } // store all 64 cones
       
      // loop over all cells
      if (_uEvtStoreAllElecCells){
	for(int icell=0; icell<emobj->ncells(); icell++) {
	  const TMBCaloCell *thecell = emobj->GetCaloCell(icell);

	  int cell_ieta =thecell->ieta();
	  int cell_iphi = thecell->iphi();
	  int cell_layer = thecell->layer();	  
	  double cell_E = thecell->E();
	  	 
	  // if store all electron cells
	  _tecellilayer[ielec][_tencells[ielec]] = cell_layer ;
	  _tecellieta[ielec][_tencells[ielec]] = cell_ieta ;
	  _tecelliphi[ielec][_tencells[ielec]] = cell_iphi ;
	  _tecelle[ielec][_tencells[ielec]] = cell_E ;
	  _tecellstat[ielec][_tencells[ielec]] = (int)(thecell->isNormalCell() && cell_E>0);
	  _tencells[ielec]++;
        } 
      }
      // if store all 64 cones energies 
      if (_uEvtStoreAllCones){
	int cell_ieta(0), cell_iphi(0), cell_layer(0); 
	GetBestECClusterFromReco(emobj, cell_ieta, cell_iphi, cell_layer);
	for (int icone=0; icone<64; icone++) {
	  double tvtx[] = {vtx[0], vtx[1], vtx[2]};
	  GetECRotatedCone(event, cell_ieta, icone+1, cell_layer, tvtx, _radiusEC, _tconede[ielec][icone], _tconedpx[ielec][icone], _tconedpy[ielec][icone]);	
	  if (_debugLevel > 1000) {
	    cout << "Rotated cone " << cell_ieta << " " << icone+1 << " " << _tconede[ielec][icone] << endl;
	  }
	  _tconedet[ielec][icone] = sqrt(_tconedpx[ielec][icone]*_tconedpx[ielec][icone] + _tconedpy[ielec][icone]*_tconedpy[ielec][icone]);
	  TVector2 cone_unit_vect(cos(_tconephi[ielec][icone]), sin(_tconephi[ielec][icone]));
          _tconeupara[ielec][icone] = recoil_vect * cone_unit_vect;
          _tconeuperp[ielec][icone] = recoil_vect * cone_unit_vect.Rotate(TMath::Pi()/2.);
        }  // loop over cones
      } // if store all 64 cones

      // values for the _tree
      _tee[ielec] = emobj->CalE();
      _teeuc[ielec] = emobj->uncorrE();
      _tept[ielec] = emobj->Pt();
      _tepx[ielec] = emobj->Px();
      _tepy[ielec] = emobj->Py();
      _tepz[ielec] = emobj->Pz(); 
      _tupara[ielec] = upara;
      _tuperp[ielec] = uperp;
      _tephi[ielec] = emobj->Phi();
      _teeta[ielec] = emobj->Eta();
      _teetaem3[ielec] = emobj->TrkEtaEM3();
      _tedeteta[ielec] = emobj->CalDetectorEta();
      _teiphi[ielec] = elec_iphi;
      _teieta[ielec] = elec_ieta;
      _techg[ielec] = emobj->charge();
      _tephiem3[ielec] = TVector2::Phi_0_2pi(emobj->TrkPhiEM3());
      _tephimod[ielec] = fmod(16.0*_tephiem3[ielec]/TMath::Pi(),1.0);
      _tedetphi[ielec] = TVector2::Phi_0_2pi(emobj->CalDetectorPhi());
      _tedetphimod[ielec] = fmod(16.0*_tedetphi[ielec]/TMath::Pi(),1.0);
      _tetkpt[ielec] =  emobjs[ielec]->getPtrChp() ? emobjs[ielec]->getPtrChp()->Pt() : 0  ; 
      if (_dUParaEffStudy){
        _passEC[ielec] = emobj->IsEC(_DetEtaEC1, _DetEtaEC2);
        _passCalEtaFid[ielec] = emobj->is_in_eta_fiducial();
        _passCalPhiFid[ielec] = emobj->is_in_phi_fiducial();
        _passTrkPhiFid[ielec] = emobj->is_in_TrkPhiFid();
        _passFid[ielec] = emobj->is_in_fiducial();
        _passECFid[ielec] = emobj->IsECFid(_DetEtaEC1,_DetEtaEC2);
        _passElPt[ielec] = emobj->Pt()>_ElecPtCut;
        _passEmf[ielec] = emobj->PassEMFrac(_EMFracCut);
        _passIso[ielec] = emobj->PassIso(_IsoCut);
        _passEmfIso[ielec] = emobj->PassEMFracIso(_EMFracCut,_IsoCut);
        _passHMx[ielec] = emobj->PassHMx(_HM7Cut,_HM8Cut);
        _passTkMatch[ielec] = emobj->has_good_spatial_track_match(0.01,_require_smt,10.,_require_smtEC);
        _passTkMatchLoose[ielec] = emobj->has_good_spatial_track_match(-0.5);
        _passEID[ielec] = _passECFid[ielec]&&_passElPt[ielec]&&_passEmfIso[ielec]&&_passHMx[ielec]&&_passTkMatch[ielec];
      } 
      // mc study
      if (_MCStudy) {
        if (ielec<raw_mc_electrons.size()) {
          _teetrue[ielec] = raw_mc_electrons[ielec]->E();
          _tepttrue[ielec] = raw_mc_electrons[ielec]->Pt();
          _tepxtrue[ielec] = raw_mc_electrons[ielec]->Px();
          _tepytrue[ielec] = raw_mc_electrons[ielec]->Py();
          _tepztrue[ielec] = raw_mc_electrons[ielec]->Pz();
          _teetatrue[ielec] = raw_mc_electrons[ielec]->Eta();
          _tephitrue[ielec] = raw_mc_electrons[ielec]->Phi();
          _teeftrue[ielec] = em_mc_objects[ielec]->E();
          _teptftrue[ielec] = em_mc_objects[ielec]->Pt();
          _tepxftrue[ielec] = em_mc_objects[ielec]->Px();
          _tepyftrue[ielec] = em_mc_objects[ielec]->Py();
          _tepzftrue[ielec] = em_mc_objects[ielec]->Pz();
          _teetaftrue[ielec] = em_mc_objects[ielec]->Eta();
          _tephiftrue[ielec] = em_mc_objects[ielec]->Phi();
        }
        else {
          _teetrue[ielec] = -100.;
          _tepttrue[ielec] = -100.;
          _tepxtrue[ielec] = -100.;
          _tepytrue[ielec] = -100.;
          _tepztrue[ielec] = -100.;
          _teetatrue[ielec] = -100.;
          _tephitrue[ielec] = -100.;
          _teeftrue[ielec] = -100.;
          _teptftrue[ielec] = -100.;
          _tepxftrue[ielec] = -100.;
          _tepyftrue[ielec] = -100.;
          _tepzftrue[ielec] = -100.;
          _teetaftrue[ielec] = -100.;
          _tephiftrue[ielec] = -100.;
        }
      } // mc study
      
    } // loop over EC electron(s)     

    // values for the _tree
    _tnelec = NeleEC;
    _tvtx[0] = vtx[0]; 
    _tvtx[1] = vtx[1]; 
    _tvtx[2] = vtx[2]; 
    _tut = recoil_vect.Mod();
    _tutx = recoil_vect.Px();
    _tuty = recoil_vect.Py();
    _tutphi = recoil_vect.Phi();
    _tmet = met.met();
    _tmetx = met.metx();
    _tmety = met.mety();
    _tmetphi = met.metphi();
    _tset = ScalarEt;
  
    // MC study store truth
    if (_MCStudy ){
      _tvtxtrue[0] = WZ->getDMCvtx()->x();
      _tvtxtrue[1] = WZ->getDMCvtx()->y();
      _tvtxtrue[2] = WZ->getDMCvtx()->z();
      _tuttrue = WZ->Pt();
      _tutxtrue = -WZ->Px();
      _tutytrue = -WZ->Py();
      _tutztrue = -WZ->Pz();
    }
 
    // fill the _tree
    _tree->Fill();

  } // get pointers to all needed objects

  return true;

}

std::vector<double> uEventAnalysisEC::GetMet(cafe::Event& event, double vtx[3]) {

  float metx_new=0., mety_new=0., met_new=0., metz_new=0, scalarEt_new=0.;
  float metx_em=0., mety_em=0., met_em=0., metz_em=0, scalarEt_em=0.;
  float metx_icd=0., mety_icd=0., met_icd=0., metz_icd=0, scalarEt_icd=0.;
  float metx_mg=0., mety_mg=0., met_mg=0., metz_mg=0, scalarEt_mg=0.;
  float metx_fh=0., mety_fh=0., met_fh=0., metz_fh=0, scalarEt_fh=0.;
  float metx_nada=0., mety_nada=0., met_nada=0., metz_nada=0, scalarEt_nada=0.;
  float metx_t42=0., mety_t42=0., met_t42=0., metz_t42=0, scalarEt_t42=0.;

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
          //double px_cell, py_cell, pz_cell, pT_cell;
          //wz_utils::RevertexCell( E, cell_pos, vtx, px_cell, py_cell, pT_cell);
          // calculate px py pzof a given cell 
          double direction[3];
          direction[0] = cell_pos[0] - vtx[0];
          direction[1] = cell_pos[1] - vtx[1];
          direction[2] = cell_pos[2] - vtx[2];
          double length = sqrt(direction[0]*direction[0]+direction[1]*direction[1]+direction[2]*direction[2]);
          double px_cell = E * direction[0]/length;
          double py_cell = E * direction[1]/length;
          double pz_cell = E * direction[2]/length;
          double pT_cell = sqrt(px_cell*px_cell+py_cell*py_cell);

          if(ilyr<=7) {
            metx_em -= px_cell;
            mety_em -= py_cell;
            metz_em -= pz_cell;
            scalarEt_em += pT_cell;
          } else if (ilyr==8 || ilyr==10) {
            metx_mg -= px_cell;
            mety_mg -= py_cell;
            metz_mg -= pz_cell;
            scalarEt_mg += pT_cell;
          } else if (ilyr==9) {
            metx_icd -= px_cell;
            mety_icd -= py_cell;
            metz_icd -= pz_cell;
            scalarEt_icd += pT_cell;
          } else {
            metx_fh -= px_cell;
            mety_fh -= py_cell;
            metz_fh -= pz_cell;
            scalarEt_fh += pT_cell;
          }

          if(cell->isNadaCell()) {
            metx_nada -= px_cell;
            mety_nada -= py_cell;
            metz_nada -= pz_cell;
            scalarEt_nada += pT_cell;
          }

          if(cell->isCalT42Cell()) {
            metx_t42 -= px_cell;
            mety_t42 -= py_cell;
            metz_t42 -= pz_cell;
            scalarEt_t42 += pT_cell;
          }

          // for all positive cells, no CH layers and no ICD detector
          if(ilyr!=9) {
            metx_new -= px_cell;
            mety_new -= py_cell;
            metz_new -= pz_cell;
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

  std::vector<double> met;
  met.push_back(metx_new);
  met.push_back(mety_new);
  met.push_back(met_new);
  met.push_back(metz_new);
  met.push_back(scalarEt_new);

  return met;
}

// Tries to get the raw energy from the true electron
std::vector<const TMBCaloCell*> uEventAnalysisEC::GetBestECClusterFromTrue(cafe::Event& event, int elec_ieta, int elec_iphi, double radius, int& cell_ieta, int& cell_iphi, int& cell_layer) {

  // The calorimeter map and cells
  CaloGeometryManager::get_instance();
  const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
  const TMBCellContainer *calocells = event.get<TMBCellContainer>("CaloCells");
  
  int elec_layer;
  double layerEmax = -1;
  // Get the hottest cell in the direction of the electron as a first guess
  for(int icell=0; icell<calocells->NumCells(); icell++) {
    const TMBCaloCell *calocell = calocells->GetCell(icell);      
    
    if (!(calocell->isNormalCell())) continue;                                    // Normal T42 cell
    if (elec_ieta != calocell->ieta() || elec_iphi != calocell->iphi()) continue; // Same side of the detector
    if (calocell->layer() > 7) continue;                                          // In EM

    if (calocell->E() > layerEmax) {
      elec_layer = calocell->layer();
      layerEmax = calocell->E();
    }
  }

  // Gets the reference
  int cell_index = wz_utils::EncodeCellIndex(elec_ieta, elec_iphi, elec_layer);
  map<int, CELLXYZ_STRUCT>::const_iterator iter = calogeometry_map.find(cell_index);
  CELLXYZ_STRUCT cellgeo = (*iter).second;
  float elec_pos[] = {cellgeo.x, cellgeo.y, cellgeo.z};

  // Get estimate of the window size
  float r_estimate = sqrt(elec_pos[0]*elec_pos[0]+elec_pos[1]*elec_pos[1]);
  int s_estimate = static_cast<int> (1 + 64.* radius / ( r_estimate * TMath::TwoPi()));

  // Make a first loop to do a first estimate of the cluster
  std::vector<const TMBCaloCell*> cluster;
  
  for(int icell=0; icell<calocells->NumCells(); icell++) {
    const TMBCaloCell *calocell = calocells->GetCell(icell);      
    
    if (!(calocell->isNormalCell())) continue;                           // Normal T42 cell
    if (calocell->ieta()*elec_ieta < 0) continue;                       // Same side of the detector
    if (fabs(calocell->ieta()) < 10) continue;                          // In the EC
    if (!(calocell->layer() <= 7 || calocell->layer() == 11)) continue; // In EM calo or FH1
    
    cell_index = wz_utils::EncodeCellIndex(calocell->ieta(), calocell->iphi(), calocell->layer());
    iter = calogeometry_map.find(cell_index);
    cellgeo = (*iter).second;
    
    double deltax = (cellgeo.x * elec_pos[2]/cellgeo.z) - elec_pos[0];
    double deltay = (cellgeo.y * elec_pos[2]/cellgeo.z) - elec_pos[1];
    double d2 = deltax*deltax + deltay*deltay;
    int deltaeta = calocell->ieta() - elec_ieta;
    int deltaphi = calocell->iphi() - elec_iphi;
    if (deltaphi < 0) deltaphi = -deltaphi;
    if (deltaphi > 32) deltaphi = 64 - deltaphi;
    double dR2 = deltaeta*deltaeta + deltaphi * deltaphi;
    
    if (d2 < radius * radius && dR2 <= s_estimate*s_estimate) {
      cluster.push_back(calocell);
    }
  } // First estimate done. Now let's find the hottest tower

  // Store the tower ET
  double caltowers[75][65];
  for (int i=0; i<75; i++)
    for (int j=0; j<65; j++)
      caltowers[i][j] = 0.0;
  
  // Stores the cell with highes energy in the highest pT tower
  // or neighbor
  int ietamax, iphimax, ilayermax;    
  double Emax=-1.0; 
  float hottest_pos[3];
  
  // Tower with maximum ET and the ET.
  int itetamax,itphimax;
  double Etmax=-1.0;
  
  // Loop over the cells to get the hottest tower.
  for (int icell=0; icell < cluster.size(); icell++) {
    const TMBCaloCell* calocell = cluster[icell];
    
    // Calculate the pseudo-rapidity of the tower
    double eta;
    if (calocell->ieta() > 0) eta = (((double)(calocell->ieta()-1))*0.1);
    else eta = (((double)(calocell->ieta()+1))*0.1);
    
    // Ignore bad cells - Is this right?
    if (!(calocell->isNormalCell())) continue;
    caltowers[calocell->ieta()+37][calocell->iphi()] += calocell->E()/cosh(eta);
  }

  // Loop over the calorimeter towers to get the one with highest ET
  for (int i=0; i<75; i++) {
    for (int j=0; j<65; j++) {
      if (caltowers[i][j] > Etmax) {
	itetamax = i;
	itphimax = j;
	Etmax = caltowers[i][j];
      }
    }
  }
  itetamax -= 37;

  // Now loops agains to find the best estimate of the seed
  for (int icell=0; icell < cluster.size(); icell++) {
    const TMBCaloCell* calocell = cluster[icell];
        
    // Look at good EM cells
    if (!(calocell->isNormalCell())) continue;
    if (calocell->layer() > 7) continue;
	
    // Is it a neighbor of the highest ET cell?
    int deltaeta = calocell->ieta() - itetamax;
    if (deltaeta < 0) deltaeta = -deltaeta;
    int deltaphi = calocell->iphi() - itphimax;
    if (deltaphi < 0) deltaphi = -deltaphi;
    if (deltaphi > 32) deltaphi = 64 - deltaphi;	
    
    if (deltaeta > 1 || deltaphi > 1) continue;
      
    if (calocell->E() > Emax) {
      cell_index = wz_utils::EncodeCellIndex(calocell->ieta(), calocell->iphi(), calocell->layer());
      iter = calogeometry_map.find(cell_index);
      cellgeo = (*iter).second;
	
      ietamax = calocell->ieta();
      iphimax = calocell->iphi();
      ilayermax = calocell->layer();
      Emax = calocell->E();
      hottest_pos[0] = cellgeo.x;
      hottest_pos[1] = cellgeo.y;
      hottest_pos[2] = cellgeo.z;
    }	    
  }

  int deltateta = ietamax - itetamax;
  if (deltateta < 0) deltateta = -deltateta;
  int deltatphi = iphimax - itphimax;
  if (deltatphi < 0) deltatphi = -deltatphi;
  if (deltatphi > 32) deltatphi = 64 - deltatphi;	

  cell_ieta = ietamax;
  cell_iphi = iphimax;
  cell_layer = ilayermax;

  // Get the new estimate of the radius
  r_estimate = sqrt(hottest_pos[0]*hottest_pos[0]+hottest_pos[1]*hottest_pos[1]);
  s_estimate = static_cast<int> (1 + 64.* radius / ( r_estimate * TMath::TwoPi()));

  // And the new cluster
  cluster.clear();

  for(int icell=0; icell<calocells->NumCells(); icell++) {
    const TMBCaloCell *calocell = calocells->GetCell(icell);      

    if (!(calocell->isNormalCell() && calocell->E() > 0.0)) continue;   // Normal cell with positive energy
    if (calocell->ieta()*ietamax < 0) continue;                         // Same side of the detector
    if (fabs(calocell->ieta()) < 10) continue;                          // In the EC
    if (!(calocell->layer() <= 7 || calocell->layer() == 11)) continue; // In EM calo or FH1
    
    cell_index = wz_utils::EncodeCellIndex(calocell->ieta(), calocell->iphi(), calocell->layer());
    iter = calogeometry_map.find(cell_index);
    cellgeo = (*iter).second;
    
    double deltax = (cellgeo.x * hottest_pos[2]/cellgeo.z) - hottest_pos[0];
    double deltay = (cellgeo.y * hottest_pos[2]/cellgeo.z) - hottest_pos[1];
    double d2 = deltax*deltax + deltay*deltay;
    int deltaeta = calocell->ieta() - ietamax;
    int deltaphi = calocell->iphi() - iphimax;
    if (deltaphi < 0) deltaphi = -deltaphi;
    if (deltaphi > 32) deltaphi = 64 - deltaphi;
    double dR2 = deltaeta*deltaeta + deltaphi * deltaphi;
    
    if (d2 < radius * radius && dR2 <= s_estimate*s_estimate) {
      cluster.push_back(calocell);
    }

  }
  return cluster;
}

void uEventAnalysisEC::GetECRotatedCone(cafe::Event& event, int elec_ieta, int elec_iphi, int elec_layer, double vtx[3], double radius, double& coneE, double& conepx, double& conepy) {
  
  coneE = 0;
  conepx = 0;
  conepy = 0;

  // The calorimeter map and cells
  CaloGeometryManager::get_instance();
  const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
  const TMBCellContainer *calocells = event.get<TMBCellContainer>("CaloCells");

  int cell_index = wz_utils::EncodeCellIndex(elec_ieta, elec_iphi, elec_layer);
  map<int, CELLXYZ_STRUCT>::const_iterator iter = calogeometry_map.find(cell_index);
  CELLXYZ_STRUCT cellgeo = (*iter).second;
  float elec_pos[] = {cellgeo.x, cellgeo.y, cellgeo.z};

  float r_estimate = sqrt(elec_pos[0]*elec_pos[0]+elec_pos[1]*elec_pos[1]);
  int s_estimate = static_cast<int> (1 + 64.* radius / ( r_estimate * TMath::TwoPi()));

  for(int icell=0; icell<calocells->NumCells(); icell++) {
    const TMBCaloCell *calocell = calocells->GetCell(icell);      

    if (!(calocell->isNormalCell() && calocell->E() > 0.0)) continue;   // Normal cell with positive energy
    if (calocell->ieta()*elec_ieta < 0) continue;                         // Same side of the detector
    if (fabs(calocell->ieta()) < 10) continue;                          // In the EC
    if (!(calocell->layer() <= 7 || calocell->layer() == 11)) continue; // In EM calo or FH1
    
    cell_index = wz_utils::EncodeCellIndex(calocell->ieta(), calocell->iphi(), calocell->layer());
    iter = calogeometry_map.find(cell_index);
    cellgeo = (*iter).second;
    
    double deltax = (cellgeo.x * elec_pos[2]/cellgeo.z) - elec_pos[0];
    double deltay = (cellgeo.y * elec_pos[2]/cellgeo.z) - elec_pos[1];
    double d2 = deltax*deltax + deltay*deltay;
    int deltaeta = calocell->ieta() - elec_ieta;
    int deltaphi = calocell->iphi() - elec_iphi;
    if (deltaphi < 0) deltaphi = -deltaphi;
    if (deltaphi > 32) deltaphi = 64 - deltaphi;
    double dR2 = deltaeta*deltaeta + deltaphi * deltaphi;
    
    if (d2 < radius * radius && dR2 <= s_estimate*s_estimate) {

        int cell_ieta = calocell->ieta();
        int cell_iphi = calocell->iphi();
        int cell_ilayer = calocell->layer();
        double cell_E = calocell->E();

        float cell_pos[3] = { cellgeo.x, cellgeo.y, cellgeo.z };

        // calculate px py pzof a given cell 
        double direction[3];
        direction[0] = cell_pos[0] - vtx[0];
        direction[1] = cell_pos[1] - vtx[1];
        direction[2] = cell_pos[2] - vtx[2];
        double length = sqrt(direction[0]*direction[0]+direction[1]*direction[1]+direction[2]*direction[2]);
        double cell_Px = cell_E * direction[0]/length;
        double cell_Py = cell_E * direction[1]/length;
        double cell_Pz = cell_E * direction[2]/length;
        double cell_Et = sqrt(cell_Px*cell_Px+cell_Py*cell_Py);

	coneE += cell_E;
	conepx += cell_Px;
	conepy += cell_Py;
    }
  }

}

void uEventAnalysisEC::GetBestECClusterFromReco(const CAFEMObj* emobj, int& cell_ieta, int& cell_iphi, int& cell_layer) {

  // Store the tower ET
  double caltowers[75][65];
  for (int i=0; i<75; i++)
    for (int j=0; j<65; j++)
      caltowers[i][j] = 0.0;
  
  // Stores the cell with highes energy in the highest pT tower
  // or neighbor
  int ietamax, iphimax, ilayermax;    
  double Emax=-1.0; 
  
  // Tower with maximum ET and the ET.
  int itetamax,itphimax;
  double Etmax=-1.0;

  // Loop over the cells to get the hottest tower.
  for (int icell=0; icell<(int)emobj->ncells(); icell++){
    int aieta = emobj->GetCaloCell(icell)->ieta();
    int aiphi = emobj->GetCaloCell(icell)->iphi();
    caltowers[aieta+37][aiphi] += emobj->Pt();
  }

  // Loop over the calorimeter towers to get the one with highest ET
  for (int i=0; i<75; i++) {
    for (int j=0; j<65; j++) {
      if (caltowers[i][j] > Etmax) {
	itetamax = i;
	itphimax = j;
	Etmax = caltowers[i][j];
      }
    }
  }
  itetamax -= 37;
  
  for (int icell=0; icell<(int)emobj->ncells(); icell++){
        
    // Look at good EM cells
    int aieta = (int) emobj->GetCaloCell(icell)->ieta();
    int aiphi = (int) emobj->GetCaloCell(icell)->iphi();
    int alayer = (int) emobj->GetCaloCell(icell)->layer();
    double aE = emobj->GetCaloCell(icell)->E();
    if (!(emobj->GetCaloCell(icell)->isNormalCell() && emobj->GetCaloCell(icell)->E() > 0.0)) continue;
    if (emobj->GetCaloCell(icell)->layer() > 7) continue;
    
    // Is it a neighbor of the highest ET cell?
    int deltaeta = aieta - itetamax;
    if (deltaeta < 0) deltaeta = -deltaeta;
    int deltaphi = aiphi - itphimax;
    if (deltaphi < 0) deltaphi = -deltaphi;
    if (deltaphi > 32) deltaphi = 64 - deltaphi;	    
    if (deltaeta > 1 || deltaphi > 1) continue;
    
    if (aE > Emax) {
      
      ietamax = aieta;
      iphimax = aiphi;
      ilayermax = alayer;
      Emax = aE;
    }	    
  }
  
  cell_ieta = ietamax;
  cell_iphi = iphimax;
  cell_layer = ilayermax;

}


ClassImp(uEventAnalysisEC)
