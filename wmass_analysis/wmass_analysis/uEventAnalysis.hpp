#include "cafe/Processor.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_util/hist_nd.hpp"
#include <map>

class TTree;

class uEventAnalysis : public cafe::Processor {

 public:
  uEventAnalysis(const char *name);
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();

  ClassDef(uEventAnalysis, 0);
  
 private:


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
  bool _uEvtCutBothPt, _uEvtBothCC, _uEvtBothTrackMatch, _uEvtCutUt, _uEvtCutMet, _uEvtCutWMt;

  // store all electron cells?
  bool _uEvtStoreAllElecCells ;

  // if store all 64 cones
  bool _uEvtStoreAllCones;

  // if store all iphi and CC ieta cones
  bool _uEvtStoreAllCones2;

  // process W or Z
  bool _uEvtDoW, _uEvtDoZ;

  // tree for dUParaEffStudy
  TTree* _tree;
  bool _passEmfIso[10], _passHMx[10], _passCC[10], _passFid[10], _passCCFid[10], _passTkMatch[10], _passTkMatchLoose[10], _passElPt[10], _passEID[10];
  bool _passEmf[10], _passIso[10], _passCalEtaFid[10], _passCalPhiFid[10], _passTrkPhiFid[10];
  bool _passBothPt, _passBothCCFid, _passBothTkMatch, _passCutUt, _passCutMet, _passCutWMt;
  bool _passCCTrue[10], _passCluster[10], _passTkPhiFidTrue[10];
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

  // number of spatial track matching requirement
  int _NumZSpatialTrk;

  // outputfile
  TFile* _uevtfile;
  
  // get UParaBin number
  int getUParaBin(double upara);

  // get InstLumiBin number 
  int getInstLumiBin(double InstLumi);

  // cell is inside a 13towers window
  bool CellIsIn13Tow(int elec_ieta, int iphi_rotated, int cell_ieta, int cell_iphi);

  // get missing Et and missing Ez, and scalar Et
  std::vector<double> uEventAnalysis::GetMet(cafe::Event& event, double vtx[3]); 

  int _nelec_processed;
  int _nelec_misidentified;

  // SCA killing list copied from ObjSelector Jan update in 17/01/2013
  // exclude "SCA failures" from recoil calculation
  bool _excludeSCAfailures;
  std::map<std::pair<int,int>,std::pair<int,int> > _SCAkillList; 
  void initialiseKillList();
  std::map<std::pair<int,int>,int> consultKillList(int run);

};
