// Author: Rafael Lopes de Sa
// Date: 19/Mar/2012
//
// The EC reconstruction is different from the CC one.
// Let's see if I can get it right

#include "cafe/Processor.hpp"
#include "cafe/Event.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "tmb_tree/TMBCaloCell.hpp"

#include "TTree.h"
#include "TFile.h"

class uEventAnalysisEC : public cafe::Processor {

public:

  uEventAnalysisEC(const char* name);
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();

  ClassDef(uEventAnalysisEC, 1);

private:

  bool _nonStdEMobjs;
  std::string _nameEMobjs;

  // debug level
  int _debugLevel;
  
  // MC studies
  bool _MCStudy;

  // MC study2: store all truth
  bool _MCStudy2;

  // The average delta Ut vector in the electron window from underlying events
  double _dUAverage;

  // switch dUParaEffStudy
  bool _dUParaEffStudy;

  // selection options
  bool _uEvtCutBothPt, _uEvtECEC, _uEvtCCEC, _uEvtBothTrackMatch, _uEvtCutUt, _uEvtCutMet, _uEvtCutWMt;

  // store all electron cells?
  bool _uEvtStoreAllElecCells ;

  // if store all 64 cones
  bool _uEvtStoreAllCones;

  // process W or Z
  bool _uEvtDoW, _uEvtDoZ;

  // tree for dUParaEffStudy
  TFile* _uEventOutFile;
  TTree* _tree;
  bool _passEmfIso[10], _passHMx[10], _passEC[10], _passFid[10], _passECFid[10], _passTkMatch[10], _passTkMatchLoose[10], _passElPt[10], _passEID[10];
  bool _passEmf[10], _passIso[10], _passCalEtaFid[10], _passCalPhiFid[10], _passTrkPhiFid[10];
  bool _passBothPt, _passCCECFid, _passECECFid, _passBothTkMatch, _passCutUt, _passCutMet, _passCutWMt;
  bool _passECTrue[10], _passCluster[10], _passTkPhiFidTrue[10];
  int _eventNum, _runNum, _ZBeventNum, _ZBrunNum;

  double _tzpx, _tzpy, _tzpz, _tzpt, _tze;

  int _tnelec, _teiphi[2], _teieta[2], _tconeiphi[2][64];
  int _tnelect;
  double _tvtx[3];
  double _tephi[2], _teeta[2], _tedeteta[2], _teetaem3[2], _tee[2], _teeuc[2], _tept[2], _tepx[2], _tepy[2], _tepz[2];
  double _tupara[2], _tuperp[2], _tut, _tutx, _tuty, _tutphi, _tmet, _tmetx, _tmety, _tmetphi, _tlumi, _tset;
  double _tetkpt[2];
  double _techg[2], _tephiem3[2], _tephimod[2], _tedetphi[2], _tedetphimod[2];
  double _tconede[2][64], _tconedet[2][64], _tconedpx[2][64], _tconedpy[2][64], _tconephi[2][64], _tconeupara[2][64], _tconeuperp[2][64];
  double _tconede2[22][64];
  double _tvtxtrue[3];
  int _techgtrue[10], _teietatrue[10], _teiphitrue[10];
  double _tepttrue[10], _tepxtrue[10], _tepytrue[10], _tepztrue[10], _teetrue[10], _tephitrue[10], _teetatrue[10];
  double _teptftrue[10], _tepxftrue[10], _tepyftrue[10], _tepzftrue[10], _teeftrue[10], _tephiftrue[10], _teetaftrue[10];
  double _tedetetatrue[10], _tedetphitrue[10], _tephimodtrue[10];
  double _tuttrue, _tutxtrue, _tutytrue, _tutztrue;
  int _tencells[2], _tecellilayer[2][200], _tecellieta[2][200], _tecelliphi[2][200], _tecellstat[2][200];
  double  _tecelle[2][200];
  bool _tisW, _tfoundWZ;
  int _teindex[10];
  double _teerawrec[10], _teptrawrec[10], _tepxrawrec[10], _tepyrawrec[10], _tepzrawrec[10], _tesetrawrec[10];
  double _tutrec, _tutxrec, _tutyrec, _tmetrawrec, _tmetxrawrec, _tmetyrawrec, _tmetzrawrec, _tsetrec;
  int _tnnuet;
  double _tnptrue[10], _tnpttrue[10], _tnpxtrue[10], _tnpytrue[10], _tnpztrue[10];
 
  // good electron cuts
  float _ElecPtCut, _DetEtaCC, _DetEtaEC1, _DetEtaEC2;
  float _EMFracCut, _IsoCut, _HM7Cut, _HM8Cut;
   
  // Z boson mass, pT cuts
  float _ZMassCut1, _ZMassCut2, _ZUtCut;

  // W boson transverse mass, Ut cut
  float _WMetCut, _WMtCut1, _WMtCut2, _WUtCut;

  //require SMT hit for track match     
  bool _require_smt;
  bool _require_smtEC;

  // number of spatial track matching requirement
  int _NumZSpatialTrk;

  // histograms
  hist_files _histos;

  // EC radius cone
  double _radiusEC;

  // get missing Et and missing Ez, and scalar Et
  std::vector<double> GetMet(cafe::Event& event, double vtx[3]); 

  // Reproduce EC reconstruction procedure
  std::vector<const TMBCaloCell*> GetBestECClusterFromTrue(cafe::Event& event, int elec_ieta, int elec_iphi, double radius, int& cell_ieta, int& cell_iphi, int& cell_layer);
  void GetBestECClusterFromReco(const CAFEMObj* emobj, int& cell_ieta, int& cell_iphi, int& cell_layer);
  void GetECRotatedCone(cafe::Event& event, int elec_ieta, int elec_iphi, int elec_layer, double vtx[3], double radius, double& coneE, double& conepx, double& conepy);


};
