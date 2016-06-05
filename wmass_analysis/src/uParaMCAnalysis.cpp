#include "wmass_analysis/uParaMCAnalysis.hpp"
#include "cafe/Event.hpp"
#include "cafe/Variables.hpp"
#include "cafe/Config.hpp"
#include "wmass_util/CAFZCand.hpp"
#include "wmass_util/CAFWCand.hpp"
#include "wmass_analysis/histograms.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "tmb_tree/TMBCaloCell.hpp"
#include "TNtuple.h"
#include <TFile.h>

using namespace std;
using namespace cafe;

uParaMCAnalysis::uParaMCAnalysis(const char *name) : Processor(name) {

  Config config(name);

  // debug level
  _debugLevel = config.get("debugLevel", 0);
  
  // MC study
  _MCStudy = config.get("MCStudy", false);
  
  // EM Eta cuts
  _DetEtaCC = config.get("DetEtaCC", 1.1);
  _DetEtaEC1 = config.get("DetEtaEC1", 1.5);
  _DetEtaEC2 = config.get("DetEtaEC2", 2.3);
  _ElecPtCut = config.get("ElecPtCut1_Lo", 25.);
  _StudyW = config.get("StudyW", true);
  _StudyZ = config.get("StudyZ", false);
  // do raw cells
  _dorawCellsRecoil = config.get("dorawCellsRecoil", true);

  _no_overlay = config.get("no_overlay", false);
  
  
  
  // require smt hit for track match
  _require_smt = config.get("RequireSMT", kTRUE);
  if (!_no_overlay){
    _tuple = new TTree("tuple","tuple");
    _tuple->Branch("nelec",&_nelec,"nelec/I");
    _tuple->Branch("elec_E",_elec_E,"elec_E[nelec]/F");
    _tuple->Branch("elec_uncorrE",_elec_uncorrE,"elec_uncorrE[nelec]/F");
    _tuple->Branch("elec_deteta",_elec_deteta,"elec_deteta[nelec]/F");
    _tuple->Branch("elec_detphi",_elec_detphi,"elec_detphi[nelec]/F");
    _tuple->Branch("fcone",_fcone,"fcone[nelec]/F");
    _tuple->Branch("jcone",_jcone,"jcone[nelec]/F");
    _tuple->Branch("econe",_econe,"econe[nelec]/F");
    _tuple->Branch("eventNum",&_eventNum,"eventNum/I");
    _tuple->Branch("runNum",&_runNum,"runNum/I");
    _tuple->Branch("ZBeventNum",&_ZBeventNum,"ZBeventNum/I");
    _tuple->Branch("ZBrunNum",&_ZBrunNum,"ZBrunNum/I");
    _tuple->Branch("elec_ieta",_elec_ieta,"elec_ieta[nelec]/I");
    _tuple->Branch("elec_iphi",_elec_iphi,"elec_iphi[nelec]/I");
    
  
    // histograms
    _histos.add(UE_Hist_Profile);
    _histos.add(UE_Hist);


    _histos.clone("deltaEvjunjie", 11);
    _histos.clone("deltauncorrEvjunjie", 11);
    _histos.clone("deltaeconevjunjie", 11);
    _histos.clone("deltaoeconevjunjie", 11);
    
    _histos.clone("deltaEvfeng", 11);
    _histos.clone("deltauncorrEvfeng", 11);
    _histos.clone("deltaeconevfeng", 11);
    _histos.clone("deltaoeconevfeng", 11);

    _histos.clone("sum5towE_Lumi", 22,2);
    _histos.clone("sum5towEME_Lumi", 22,2);
    _histos.clone("sum5towFHE_Lumi", 22,2);
    _histos.clone("sum5towEt_Lumi", 22,2);
    _histos.clone("sum5towEMEt_Lumi", 22,2);
    _histos.clone("sum5towFHEt_Lumi", 22,2);
    _histos.clone("sum5towE_UPara", 13,2);
    _histos.clone("sum5towEME_UPara", 13,2);
    _histos.clone("sum5towFHE_UPara", 13,2);
    _histos.clone("sum5towEt_UPara", 13,2);
    _histos.clone("sum5towEMEt_UPara", 13,2);
    _histos.clone("sum5towFHEt_UPara", 13,2);

    _histos.clone("sum13towE_Lumi", 22,2);
    _histos.clone("sum13towEME_Lumi", 22,2);
    _histos.clone("sum13towFHE_Lumi", 22,2);
    _histos.clone("sum13towEt_Lumi", 22,2);
    _histos.clone("sum13towEMEt_Lumi", 22,2);
    _histos.clone("sum13towFHEt_Lumi", 22,2);
    _histos.clone("sum13towE_UPara", 13,2);
    _histos.clone("sum13towEME_UPara", 13,2);
    _histos.clone("sum13towFHE_UPara", 13,2);
    _histos.clone("sum13towEt_UPara", 13,2);
    _histos.clone("sum13towEMEt_UPara", 13,2);
    _histos.clone("sum13towFHEt_UPara", 13,2);

    _histos.clone("sum13towE_Lumi_New", 22,2);
    _histos.clone("sum13towEME_Lumi_New", 22,2);
    _histos.clone("sum13towFHE_Lumi_New", 22,2);
    _histos.clone("sum13towEt_Lumi_New", 22,2);
    _histos.clone("sum13towEMEt_Lumi_New", 22,2);
    _histos.clone("sum13towFHEt_Lumi_New", 22,2);
    _histos.clone("sum13towE_UPara_New", 13,2);
    _histos.clone("sum13towEME_UPara_New", 13,2);
    _histos.clone("sum13towFHE_UPara_New", 13,2);
    _histos.clone("sum13towEt_UPara_New", 13,2);
    _histos.clone("sum13towEMEt_UPara_New", 13,2);
    _histos.clone("sum13towFHEt_UPara_New", 13,2);

    // divide events into 25 luminosity bins and then for each luminosity bins, divide into 13 upara bins
    _histos.clone("sum13towEt_Lumi_0_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_1_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_2_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_3_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_4_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_5_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_6_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_7_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_8_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_9_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_10_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_11_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_12_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_13_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_14_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_15_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_16_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_17_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_18_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_19_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_20_Upara", 13,2);
    _histos.clone("sum13towEt_Lumi_21_Upara", 13,2);

    // divide events into 13 upara bins and then for each luminosity bins, divide into 25 luminosity bins
    _histos.clone("sum13towEt_Upara_0_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_1_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_2_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_3_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_4_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_5_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_6_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_7_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_8_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_9_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_10_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_11_Lumi", 22,2);
    _histos.clone("sum13towEt_Upara_12_Lumi", 22,2);



    _histos.clone("UPara", 13,2);
    _histos.clone("InstLumi", 22,2);

  }

  else{
      _tuple2 = new TTree("tuple2","tuple2");
      _tuple2->Branch("nelec",&_nelec2,"nelec/I");
      _tuple2->Branch("elec_E_diff",_elec_E_diff,"elec_E_diff[nelec]/F");
      _tuple2->Branch("eventNum",&_eventNum2,"eventNum/I");
      _tuple2->Branch("runNum",&_runNum2,"runNum/I");
      _tuple2->Branch("ZBeventNum",&_ZBeventNum2,"ZBeventNum/I");
      _tuple2->Branch("ZBrunNum",&_ZBrunNum2,"ZBrunNum/I");
      _tuple2->Branch("elec_ieta",_elec_ieta2,"elec_ieta[nelec]/I");
      _tuple2->Branch("elec_iphi",_elec_iphi2,"elec_iphi[nelec]/I");
      _tuple2->Branch("elec_E",_elec_E2,"elec_E[nelec]/F");
      
      
      // histograms
    _histos.add(UE_Hist_Profile);
    _histos.add(UE_Hist);
    _histos.clone("deltaEvjunjie", 11);
    _histos.clone("deltauncorrEvjunjie", 11);
    _histos.clone("deltaeconevjunjie", 11);
    _histos.clone("deltaoeconevjunjie", 11);
    
    _histos.clone("deltaEvfeng", 11);
    _histos.clone("deltauncorrEvfeng", 11);
    _histos.clone("deltaeconevfeng", 11);
    _histos.clone("deltaoeconevfeng", 11);

    TString filename;
    filename = config.get("overlay_tuplefilename", "result_overlay.root");
    TFile *file = TFile::Open(filename);
    file->GetObject("tuple", _tuple);
    _belecE = _tuple->GetBranch("elec_E");
    _belecE->SetAddress(_elec_E); 
    _beventNum = _tuple->GetBranch("eventNum");
    _brunNum = _tuple->GetBranch("runNum");
    _bieta = _tuple->GetBranch("elec_ieta");
    _biphi = _tuple->GetBranch("elec_iphi");
    _becone = _tuple->GetBranch("econe");
    _bjcone = _tuple->GetBranch("jcone");
    _bfcone = _tuple->GetBranch("fcone");
    _bdeteta = _tuple->GetBranch("elec_deteta");
    _bdetphi = _tuple->GetBranch("elec_detphi");
    _belecuncorrE = _tuple->GetBranch("elec_uncorrE");
    _bZBeventNum = _tuple->GetBranch("ZBeventNum");
    _bZBrunNum = _tuple->GetBranch("ZBrunNum");
    _bnelec = _tuple->GetBranch("nelec");

    
    _belecuncorrE->SetAddress(_elec_uncorrE); 
    _bZBeventNum->SetAddress(&_ZBeventNum);
    _bZBrunNum->SetAddress(&_ZBrunNum);

    _beventNum->SetAddress(&_eventNum);
    _brunNum->SetAddress(&_runNum);
    _bieta->SetAddress(_elec_ieta);
    _biphi->SetAddress(_elec_iphi);
    _becone->SetAddress(_econe);
    _bjcone->SetAddress(_jcone);
    _bfcone->SetAddress(_fcone);
    _bdeteta->SetAddress(_elec_deteta);
    _bdetphi->SetAddress(_elec_detphi);
    _bnelec->SetAddress(&_nelec);
    _tuple->SetDirectory(0);
    file->Close();
    
    for (int oEvent = 0; oEvent < _tuple->GetEntries(); ++oEvent){
      _tuple->GetEntry(oEvent);
      //if (matching_option ==0)
      _MCLibraryMap.insert(make_pair(make_pair((int)_runNum,(int)_eventNum), oEvent)) ;
      // else
      _ZBLibraryMap.insert(make_pair(make_pair((int)_ZBrunNum,(int)_ZBeventNum), oEvent)) ;
      
    }
  }
  _nfail1 = 0;
  _nfail2 = 0;
  _nfail3 = 0;
  _nfail4 = 0;
  _ntotal=0;
  
  
}

void uParaMCAnalysis::begin() {
}

bool uParaMCAnalysis::processEvent(cafe::Event& event) {
  // acess all cell information
  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");
  ++_ntotal;
  vector<CAFEMObj*> emobjs;
  cafe::Collection<TMBEMCluster> em;
  CAFMet met;
  double InstLumi;
  cafe::Variables MCEventInfo_vars;
  MCEventInfo_vars.add("_npart");
  double mc_data_lumi_ratio = 1.;
  cafe::Collection<TMBMCpart> mc = event.getMCParticles();
  
//   if (!((event.getMCEventInfo(MCEventInfo_vars)->npart(0) + event.getMCEventInfo(MCEventInfo_vars)->npart(1)) == mc.size())){
//     std::cout << "problem with count -- check " << std::endl;
//     std::cout << "event.getMCEventInfo(MCEventInfo_vars)->npart(0)  " << event.getMCEventInfo(MCEventInfo_vars)->npart(0) << std::endl;
//     std::cout << "event.getMCEventInfo(MCEventInfo_vars)->npart(1)  " << event.getMCEventInfo(MCEventInfo_vars)->npart(1) << std::endl;
//     std::cout << "mc.size() " << mc.size() << std::endl;
//     std::cout << (event.getMCEventInfo()->npart(0) + event.getMCEventInfo()->npart(1)) << " == " << mc.size() << " is " << ((event.getMCEventInfo(MCEventInfo_vars)->npart(0) + event.getMCEventInfo(MCEventInfo_vars)->npart(1)) == mc.size()) << std::endl;
//     int scount = 0;
//     for (cafe::Collection<TMBMCpart>::iterator it = mc.begin(); it!= mc.end(); ++it) {
//       ++scount;
//       std::cout << " scount = " << scount << "  " << it->pdgid() <<  std::endl;
//       std::cout << it->E() <<  "   " << std::endl;
//       // if(it->pdgid() == 22) {
//       //  return false;
//       // }
//     }
//   }
//   else {
//     std::cout << "good count " << std::endl;
//   }
  
  for (int i = 0;i < mc.size() ;i++) {
    if ( mc[i].pdgid() == 22) {
      // std::cout << "Found a photon " << std::endl;
      return false;
    }
  }
//   int scount = 0;
//   for (cafe::Collection<TMBMCpart>::iterator it = mc.begin(); it!= mc.end(); ++it) {
//     ++scount;
//     std::cout << " scount = " << scount <<  std::endl;
//     // if(it->pdgid() == 22) {
//     //  return false;
//     // }
//   }

  float vtx_x, vtx_y, vtx_z;
  if (event.get("Good EMObjs", emobjs) && event.get("EMCorr Met", met) &&
      event.get("InstLumi", InstLumi) &&
      event.get("Primary vertexX", vtx_x) &&
      event.get("Primary vertexY", vtx_y) && event.get("Primary vertexZ", vtx_z)) {
    
// primary vertex
    float vtx[3] = {vtx_x, vtx_y, vtx_z};
    if (!_no_overlay){
      _runNum = event.getGlobal()->runno();
      _eventNum = event.getGlobal()->evtno();
      _MCevent = make_pair(_runNum,_eventNum);
      _ZBrunNum = event.getMCEventInfo()->overlayrun();
      _ZBeventNum = event.getMCEventInfo()->overlayevtid();
      _MCevent = make_pair(_ZBrunNum,_ZBeventNum);
    }
    const TMBCellContainer * fCells = event.getCaloCells();

    if(!_no_overlay) {
      if (emobjs.size() < 1){
	++_nfail2;
	//	std::cout << "No EMOBJ" << std::endl;
	return false;
      }
      int numcells = fCells->NumCells();
      
      const TMBGlobal * fglobal = event.getGlobal();
      double instlumi = fglobal->instlum();
      
      // calculate recoil system for W or Z events
      TVector2 recoil_vect;
      Int_t nemobj  = emobjs.size();
      recoil_vect.Set(-(emobjs[0]->Px()+met.metx()), -(emobjs[0]->Py()+met.mety()));
      bool goodz = false;
      bool goodw = false;
      if ((emobjs.size() > 1) && (_StudyZ))
	goodz = (emobjs[0]->Pt()>_ElecPtCut && emobjs[1]->Pt()>_ElecPtCut && emobjs[0]->IsCCFid(_DetEtaCC, true) && emobjs[1]->IsCCFid(_DetEtaCC, true) && emobjs[0]->has_good_spatial_track_match()  && emobjs[1]->has_good_spatial_track_match());
      if ((emobjs.size() > 0) && (_StudyW))
	goodw = (emobjs[0]->Pt() > _ElecPtCut && emobjs[0]->IsCCFid(_DetEtaCC, true) && emobjs[0]->has_good_spatial_track_match());
      
      _nelec = 0;
      
      if ((_StudyW && !goodw)){
	_nfail3++;
	return false;
      }
      else if (_StudyW)
	_nelec =1;
      
      if ((_StudyZ && !goodz)){
	_nfail3++;
	return false;
      }
      else if (_StudyZ)
	_nelec = 2;
      
      if (goodz || goodw){
	for(int ielec=0; ielec<_nelec; ielec++) {
	  
	TVector2 recoil_vect; 	
	if (_StudyW)
	  recoil_vect.Set(-(emobjs[0]->Px()+met.metx()), -(emobjs[0]->Py()+met.mety()));
	if (_StudyZ)
	  recoil_vect.Set(-(emobjs[0]->Px()+met.metx() + emobjs[1]->Px()), -(emobjs[0]->Py()+met.mety() + emobjs[1]->Py()));
	
	double electron_eta = emobjs[ielec]->CalDetectorEta();
	double electron_phi = emobjs[ielec]->CalDetectorPhi();
	double electron_E = emobjs[ielec]->CalE();
	double electron_Px = emobjs[ielec]->Px();
	double electron_Py = emobjs[ielec]->Py();
	double coshElecEta = cosh(electron_eta);
	// uncorrected and corrected electron energy
	double uncorrE = emobjs[ielec]->uncorrE();
	double corrE = emobjs[ielec]->CalE();
	double ratio = corrE/uncorrE;

	// calculate electron detector ieta and iphi
	int ieta = 9999;
	if(electron_eta>0.) ieta = (int)(electron_eta/0.1+1);
	else ieta = (int)(electron_eta/0.1-1);
	int iphi = (int)(electron_phi/(2.0*3.1415926/64)+1);
		
	// Calculate U-Parallel      
	TVector2 elec_vect(electron_Px, electron_Py);		  
	double upara = recoil_vect * elec_vect.Unit();	
	if(_debugLevel>=15) cout<<"Electron ieta, iphi, E="<<ieta<<" "<<iphi<<" "<<electron_E<<endl;

	// divided into instantaneous luminosity bins
	int InstLumiBin = -1;
	if(InstLumi<0.225) InstLumiBin = 0;
	else if(InstLumi<0.45) InstLumiBin = 1;
	else if(InstLumi<0.6) InstLumiBin = 2;
	else if(InstLumi<0.75) InstLumiBin = 3;
	else if(InstLumi<0.9) InstLumiBin = 4;
	else if(InstLumi<1.075) InstLumiBin = 5;
	else if(InstLumi<1.3) InstLumiBin = 6;
	else if(InstLumi<1.5) InstLumiBin = 7;
	else if(InstLumi<1.8) InstLumiBin = 8;
	else if(InstLumi<2.) InstLumiBin = 9;
	else if(InstLumi<2.5) InstLumiBin = 10;
	else if(InstLumi<3.0) InstLumiBin = 11;
	else if(InstLumi<3.5) InstLumiBin = 12;
	else if(InstLumi<4.) InstLumiBin = 13;
	else if(InstLumi<4.5) InstLumiBin = 14;
	else if(InstLumi<5.5) InstLumiBin = 15;
	else if(InstLumi<6.) InstLumiBin = 16;
	else if(InstLumi<6.5) InstLumiBin = 17;
	else if(InstLumi<7.) InstLumiBin = 18;
	else if(InstLumi<7.5) InstLumiBin = 19;
	else if(InstLumi<8.) InstLumiBin = 20;
	else InstLumiBin = 21;
	char sn_lumi[10];   
	sprintf(sn_lumi, "%d", InstLumiBin);
	
	// divided into uparallel bins
	int UParaBin = -1;
	if(upara<-15.) UParaBin = 0;
	else if(upara<-10.) UParaBin = 1;
	else if(upara<-5.) UParaBin = 2;
	else if(upara<-3.) UParaBin = 3;
	else if(upara<-1.5) UParaBin = 4;
	else if(upara<-0.25) UParaBin = 5;
	else if(upara<0.25) UParaBin = 6;
	else if(upara<1.5) UParaBin = 7;
	else if(upara<3.) UParaBin = 8;
	else if(upara<5.) UParaBin = 9;
	else if(upara<10.) UParaBin = 10;
	else if(upara<15.) UParaBin = 11;
	else UParaBin = 12;
	char sn_upara[10];   
	sprintf(sn_upara, "%d", UParaBin);
	
	_histos.Fill1D(string("InstLumi_")+sn_lumi, InstLumi);
	_histos.Fill1D(string("UPara_")+sn_upara, upara);
	_histos.Fill1D("InstLumi", InstLumi);
	_histos.Fill1D("InstLumiReweight", InstLumi, mc_data_lumi_ratio);
	_histos.Fill1D("UPara", upara);
	
	// electron ieta and iphi
	int elec_ieta = ieta;
	int elec_iphi = iphi;

	//First use no Rotation:
	double energy_clus = 0., EMenergy_clus = 0., FHenergy_clus = 0.;
	double Et_clus = 0., EMEt_clus = 0., FHEt_clus = 0.;



	GetRawEnergy(elec_ieta,elec_iphi, fCells, coshElecEta,  energy_clus,  Et_clus, EMenergy_clus, EMEt_clus ,  FHenergy_clus, FHEt_clus);

	if (!_no_overlay){
	  _fcone[ielec] = Feng_cone(elec_ieta, elec_iphi, fCells);
	  _jcone[ielec] = Junjie_cone(elec_ieta, elec_iphi, fCells);
	  _elec_ieta[ielec] = elec_ieta;
	  _elec_iphi[ielec] = elec_iphi;
	  _econe[ielec] = energy_clus;
	  _elec_E[ielec] = corrE;
	  _elec_uncorrE[ielec] = uncorrE;
	  _elec_deteta[ielec] = electron_eta;
	  _elec_detphi[ielec] =  electron_phi;
	  _nVtx = 0;
	
	
	}
	// rotate 8 times in opposite direction, also let the rotated position diffes by 1 tower in phi

	for(int irotate = 0; irotate < 8; irotate++) {
	  int iphi_rotated = elec_iphi;
	  if(irotate < 4) { // rotate clock-wise
	    iphi_rotated = elec_iphi + irotate + 5;
	    if(iphi_rotated > 64) iphi_rotated -= 64;
	  } else { // rotate counterclockwise
	    iphi_rotated = elec_iphi - (irotate-4) - 5;
	    if(iphi_rotated < 0) iphi_rotated += 64;
	  }
	  if(_debugLevel>=15) cout<<"Rotated iphi = "<<iphi_rotated<<endl;
	  
	  // define some variables
	  double energy_rotated = 0., EMenergy_rotated = 0., FHenergy_rotated = 0.;
	  double Et_rotated = 0., EMEt_rotated = 0., FHEt_rotated = 0.;

	  // loop over all cells
	  if(_debugLevel>=15) cout<<"Cells that are close to this rotated position: ";
	  GetRawEnergy(elec_ieta,iphi_rotated, fCells, coshElecEta,  energy_rotated,  Et_rotated, EMenergy_rotated, EMEt_rotated ,  FHenergy_rotated, FHEt_rotated);
	
	  // remove the rotated position where we have a lot of energy deposited due to jet contamination
	  if(energy_rotated/corrE<0.15) {
	    _histos.Fill1D("sum13towE_Lumi", energy_rotated);
	    _histos.Fill1D("sum13towEME_Lumi", EMenergy_rotated);
	    _histos.Fill1D("sum13towFHE_Lumi", FHenergy_rotated);
	    _histos.Fill1D("sum13towEt_Lumi", Et_rotated);
	    _histos.Fill1D("sum13towEMEt_Lumi", EMEt_rotated);
	    _histos.Fill1D("sum13towFHEt_Lumi", FHEt_rotated);

	    // luminosity
	    _histos.Fill1D(string("sum13towE_Lumi_")+sn_lumi, energy_rotated);
	    _histos.Fill1D(string("sum13towEME_Lumi_")+sn_lumi, EMenergy_rotated);
	    _histos.Fill1D(string("sum13towFHE_Lumi_")+sn_lumi, FHenergy_rotated);
	    _histos.Fill1D(string("sum13towEt_Lumi_")+sn_lumi, Et_rotated);
	    _histos.Fill1D(string("sum13towEMEt_Lumi_")+sn_lumi, EMEt_rotated);
	    _histos.Fill1D(string("sum13towFHEt_Lumi_")+sn_lumi, FHEt_rotated);

	    // upara
	    _histos.Fill1D(string("sum13towE_UPara_")+sn_upara, energy_rotated);
	    _histos.Fill1D(string("sum13towEME_UPara_")+sn_upara, EMenergy_rotated);
	    _histos.Fill1D(string("sum13towFHE_UPara_")+sn_upara, FHenergy_rotated);
	    _histos.Fill1D(string("sum13towEt_UPara_")+sn_upara, Et_rotated);
	    _histos.Fill1D(string("sum13towEMEt_UPara_")+sn_upara, EMEt_rotated);
	    _histos.Fill1D(string("sum13towFHEt_UPara_")+sn_upara, FHEt_rotated);
	    
	    // bin size is 10 MeV, remove the first bin
	    if(energy_rotated > 0.01) {
	      _histos.Fill1D("sum13towE_Lumi_New", energy_rotated);
	      _histos.Fill1D(string("sum13towE_Lumi_New_")+sn_lumi, energy_rotated);
	      _histos.Fill1D(string("sum13towE_UPara_New_")+sn_upara, energy_rotated);
	    }

	    if(EMenergy_rotated > 0.01) {
	      _histos.Fill1D("sum13towEME_Lumi_New", EMenergy_rotated);
	      _histos.Fill1D(string("sum13towEME_Lumi_New_")+sn_lumi, EMenergy_rotated);
	      _histos.Fill1D(string("sum13towEME_UPara_New_")+sn_upara, EMenergy_rotated);
	    }

	    if(FHenergy_rotated > 0.01) {
	      _histos.Fill1D("sum13towFHE_Lumi_New", FHenergy_rotated);
	      _histos.Fill1D(string("sum13towFHE_Lumi_New_")+sn_lumi, FHenergy_rotated);
	      _histos.Fill1D(string("sum13towFHE_UPara_New_")+sn_upara, FHenergy_rotated);
	    }

	    if(Et_rotated > 0.01) {
	      _histos.Fill1D("sum13towEt_Lumi_New", Et_rotated);
	      _histos.Fill1D(string("sum13towEt_Lumi_New_")+sn_lumi, Et_rotated);
	      _histos.Fill1D(string("sum13towEt_UPara_New_")+sn_upara, Et_rotated);
	    }

	    if(EMEt_rotated > 0.01) {
	      _histos.Fill1D("sum13towEMEt_Lumi_New", EMEt_rotated);
	      _histos.Fill1D(string("sum13towEMEt_Lumi_New_")+sn_lumi, EMEt_rotated);
	      _histos.Fill1D(string("sum13towEMEt_UPara_New_")+sn_upara, EMEt_rotated);
	    }

	    if(FHEt_rotated > 0.01) {
	      _histos.Fill1D("sum13towFHEt_Lumi_New", FHEt_rotated);
	      _histos.Fill1D(string("sum13towFHEt_Lumi_New_")+sn_lumi, FHEt_rotated);
	      _histos.Fill1D(string("sum13towFHEt_UPara_New_")+sn_upara, FHEt_rotated);
	    }

	    // divide events into 13 luminosity bins and then for each luminosity bins, divide into 13 upara bins
	    char sn_lumi_upara[10];   sprintf(sn_lumi_upara, "%s%d%s%d", "Lumi_", InstLumiBin, "_Upara_", UParaBin);
	    char sn_upara_lumi[10];   sprintf(sn_upara_lumi, "%s%d%s%d", "Upara_", UParaBin, "_Lumi_", InstLumiBin);

	    _histos.Fill1D(string("sum13towEt_")+sn_lumi_upara, Et_rotated);	    
	    if(Et_rotated > 0.01) _histos.Fill1D(string("sum13towEt_New_")+sn_lumi_upara, Et_rotated);

	    _histos.Fill1D(string("sum13towEt_")+sn_upara_lumi, Et_rotated);	    
	    if(Et_rotated > 0.01) _histos.Fill1D(string("sum13towEt_New_")+sn_upara_lumi, Et_rotated);

	  } // remove the region contaminated by jet
	  if(_debugLevel>=15) cout<<endl;
	} // rotate four times	
	}
	_tuple->Fill();
      }
    }
    else if (_no_overlay){
      bool fmatch = kFALSE;
      em = event.getEMscone();
      emobjs.clear();
      for (Collection<TMBEMCluster>::iterator it = em.begin(); it!= em.end(); ++it) {
	CAFEMObj *emobjptr = new CAFEMObj(&(*it)) ;
	emobjs.push_back(emobjptr);
      }
      sort(emobjs.begin(), emobjs.end(), ComparePtElec);
      pair<int,int> theEvt(event.getGlobal()->runno(), event.getGlobal()->evtno());
      
      map<pair<int,int>,int>::iterator haveIt=_MCLibraryMap.find(theEvt);
      if (haveIt!=_MCLibraryMap.end()) {
	_tuple->GetEntry((*haveIt).second);
	fmatch = kTRUE;
      }
      _nelec2=0;
      if (!fmatch){
	++_nfail4;
	std::cout << " No Event Match" << std::endl;
	return false;
      }
      for(int ielec=0; ielec<emobjs.size(); ielec++) {
	double electron_eta = emobjs[ielec]->CalDetectorEta();
	double electron_phi = emobjs[ielec]->CalDetectorPhi();
	double electron_E = emobjs[ielec]->CalE();
	double electron_Px = emobjs[ielec]->Px();
	double electron_Py = emobjs[ielec]->Py();
	double coshElecEta = cosh(electron_eta);
	// uncorrected and corrected electron energy
	double uncorrE = emobjs[ielec]->uncorrE();
	double corrE = emobjs[ielec]->CalE();
	double ratio = corrE/uncorrE;
	
	// calculate electron detector ieta and iphi
	int ieta = 9999;
	if(electron_eta>0.) ieta = (int)(electron_eta/0.1+1);
	else ieta = (int)(electron_eta/0.1-1);
	int iphi = (int)(electron_phi/(2.0*3.1415926/64)+1);
	
	if(_debugLevel>=15) cout<<"Electron ieta, iphi, E="<<ieta<<" "<<iphi<<" "<<electron_E<<endl;
	
	// electron ieta and iphi
	int elec_ieta = ieta;
	int elec_iphi = iphi;
	
	int pick_elec = -1;
	bool matched_electron = 0;
	for (Int_t ij = 0; ij < _nelec; ++ij){
	  if (!matched_electron){
	    if ((abs(elec_ieta-_elec_ieta[ij]) > 1 && !(abs(elec_ieta)==1 && abs(_elec_ieta[ij])==1))  || abs(elec_iphi-_elec_iphi[ij]) > 2 ){
	      std::cout << elec_ieta << "   " << _elec_ieta[ij] << "   " << elec_iphi << "    " << _elec_iphi[ij] << std::endl;
	      std::cout << " no iphi ieta match" << std::endl;
	      continue;
	    }
	    else{
	      matched_electron = 1;
	      pick_elec=ij;
	      ++_nelec2;
	    }
	  }
	}
	
	if ((_nelec2 >1) &&  _StudyW){
	  std::cout << " _nelec > 1 " << std::endl;
	  _nelec2 = 1;
	  continue;
	}
	
	if (_nelec2 > 2){
	  _nelec2 = 2;
	  std::cout << " _nelec > 2 " << std::endl;
	  continue;
	}
	
	//First use no Rotation:
	double energy_clus = 0., EMenergy_clus = 0., FHenergy_clus = 0.;
	double Et_clus = 0., EMEt_clus = 0., FHEt_clus = 0.;
	
	double oenergy_clus = 0., oEMenergy_clus = 0., oFHenergy_clus = 0.;
	double oEt_clus = 0., oEMEt_clus = 0., oFHEt_clus = 0.;
	
	GetRawEnergy(elec_ieta,elec_iphi, fCells, coshElecEta,  energy_clus,  Et_clus, EMenergy_clus, EMEt_clus ,  FHenergy_clus, FHEt_clus);
	
	GetRawEnergy(_elec_ieta[pick_elec],_elec_iphi[pick_elec], fCells, cosh(_elec_deteta[pick_elec]),  oenergy_clus,  oEt_clus, oEMenergy_clus, oEMEt_clus ,  oFHenergy_clus, oFHEt_clus);
	
	double fcone1 = Feng_cone(elec_ieta, elec_iphi, fCells);
	double jcone1 = Junjie_cone(elec_ieta, elec_iphi, fCells);
	
	double ofcone1 = Feng_cone(_elec_ieta[pick_elec], _elec_iphi[pick_elec], fCells);
	double ojcone1 = Junjie_cone(_elec_ieta[pick_elec], _elec_iphi[pick_elec], fCells);

	double diffE = _elec_E[pick_elec] - electron_E;
	double diffuncorrE = _elec_uncorrE[pick_elec] - uncorrE;
	double diffecone = _econe[pick_elec] - energy_clus;
	double diffoecone = _econe[pick_elec] - oenergy_clus;
	
	_elec_E_diff[ielec] =  diffE;
	_eventNum2 = _eventNum;
	_runNum2 = _runNum;
	_ZBeventNum2 = _ZBeventNum;
	_ZBrunNum2 = _ZBrunNum;
	_elec_ieta2[ielec] = _elec_ieta[pick_elec];
        _elec_iphi2[ielec] =   _elec_iphi[pick_elec];
	_elec_E2[ielec]    = _elec_E[pick_elec];

	
	char sn_deteta[11];
	Int_t EtaBin = (Int_t)(0. + (_elec_deteta[pick_elec] - (-1.1))/0.2);
        sprintf(sn_deteta, "%d", EtaBin);
       
	_histos.FillProfile(string("deltaEvjunjie_")+sn_deteta,_jcone[pick_elec],diffE);
	_histos.FillProfile(string("deltauncorrEvjunjie_")+sn_deteta,_jcone[pick_elec],diffuncorrE);
	_histos.FillProfile(string("deltaeconevjunjie_")+sn_deteta,_jcone[pick_elec],diffecone);
	_histos.FillProfile(string("deltaoeconevjunjie_")+sn_deteta,_jcone[pick_elec],diffoecone);


	_histos.FillProfile(string("deltaEvfeng_")+sn_deteta,_fcone[pick_elec],diffE);
	_histos.FillProfile(string("deltauncorrEvfeng_")+sn_deteta,_fcone[pick_elec],diffuncorrE);
	_histos.FillProfile(string("deltaeconevfeng_")+sn_deteta,_fcone[pick_elec],diffecone);
	_histos.FillProfile(string("deltaoeconevfeng_")+sn_deteta,_fcone[pick_elec],diffoecone);  
	
      }
      _tuple2->Fill();
    }
  }
  else{
    std::cout << "fails this if statement" << std::endl;
    ++_nfail1;
  }
  return true;
}// get pointers to all needed objects

void uParaMCAnalysis::finish() {

  TFile *file = histfiles::initializeTFile( this );
  if(file==NULL) return;
  string directory_name("UE_Hist");
  file->mkdir(directory_name.c_str());
  _histos.save(file, directory_name);
  if (!_no_overlay){
    _tuple->SetDirectory(file);
    _tuple->Write();
 } 
  else{
    _tuple2->Write();
  }
  std::cout << "nTotal =                         " << _ntotal << std::endl;
  std::cout << "Could not get all pointers:      " << _nfail1 << std::endl;
  std::cout << "less than 1 emobj found:         " << _nfail2 << std::endl;
  std::cout << "no good boson candidates:        " << _nfail3 << std::endl;
  std::cout << "no match found to overlay level: " << _nfail4 << std::endl;

  file->Close();
}


void uParaMCAnalysis::GetRawEnergy(const int ieta,const  int iphi, const TMBCellContainer * fCells, const double coshElecEta, double &energy, double &et, double &EMenergy, double &EMet, double &FHenergy, double &FHet) {
  energy = et = EMenergy = EMet = FHenergy = FHet = 0.;
  int numcells = fCells->NumCells();
  for(int icell=0; icell<numcells; icell++) {
    const TMBCaloCell *thecell = fCells->GetCell(icell);
    
    int cell_ieta =thecell->ieta();
    int cell_iphi = thecell->iphi();
    int cell_ilayer = thecell->layer();	  
    double cell_E = thecell->E();
    double cell_Et = cell_E/coshElecEta;	    

    bool positive_cell = (cell_E>0.);
    bool normalCell = thecell->isNormalCell();   // only use cells processed after T42 algorithm

    //
    if( ((cell_ilayer<8) || (cell_ilayer==11)) && positive_cell && normalCell) {
      // first define 5*5 towers around the electron rotated position
      bool inEtaRange5 = false;
      if(ieta==2) inEtaRange5 = (cell_ieta<=4) && (cell_ieta>=-1);
      else if(ieta==1) inEtaRange5 = (cell_ieta<=3) && (cell_ieta>=-2);
      else if(ieta==-1) inEtaRange5 = (cell_ieta<=2) && (cell_ieta>=-3);
      else if(ieta==-2) inEtaRange5 = (cell_ieta<=1) && (cell_ieta>=-4);
      else inEtaRange5 = (cell_ieta>=(ieta-2)) && cell_ieta<=(ieta+2);

      bool inPhiRange5 = false;
      if(iphi==63) inPhiRange5 = (cell_iphi==61) || (cell_iphi==62) || (cell_iphi==63) || (cell_iphi==64) || (cell_iphi==1);
      else if(iphi==64) inPhiRange5 = (cell_iphi==62) || (cell_iphi==63) || (cell_iphi==64) || (cell_iphi==1) || (cell_iphi==2);
      else if(iphi==1) inPhiRange5 = (cell_iphi==63) || (cell_iphi==64) || (cell_iphi==1) || (cell_iphi==2) || (cell_iphi==3);
      else if(iphi==2) inPhiRange5 = (cell_iphi==64) || (cell_iphi==1) || (cell_iphi==2) || (cell_iphi==3) || (cell_iphi==4);
      else inPhiRange5 = (cell_iphi>=(iphi-2)) && (cell_iphi<=(iphi+2));

      // first define 3*3 towers around the electron rotated position
      bool inEtaRange3 = false;
      if(ieta==1) inEtaRange3 = (cell_ieta<=2) && (cell_ieta>=-1);
      else if(ieta==-1) inEtaRange3 = (cell_ieta<=1) && (cell_ieta>=-2);
      else inEtaRange3 = (cell_ieta>=(ieta-1)) && cell_ieta<=(ieta+1);

      bool inPhiRange3 = false;
      if(iphi==64) inPhiRange3 = (cell_iphi==63) || (cell_iphi==64) || (cell_iphi==1);
      else if(iphi==1) inPhiRange3 = (cell_iphi==64) || (cell_iphi==1) || (cell_iphi==2);
      else inPhiRange3 = (cell_iphi>=(iphi-1)) && (cell_iphi<=(iphi+1));

      //
      //  there are 13 towers, we have 3*3 towers, and then we have the case for 5 towers with the same iphi
      //  and 5 towers with the same ieta
      //
      bool case1 = inEtaRange3 && inPhiRange3;
      bool case2 = (cell_iphi == iphi) && inEtaRange5;
      bool case3 = (cell_ieta == ieta) && inPhiRange5;

      // find all 13 towers
      if(case1 || case2 || case3) {
	if(_debugLevel>=15) cout<<"("<<cell_ieta<<", "<<cell_iphi<<") ";

	energy += cell_E;
	et += cell_Et;

	// for EM layers
	if(cell_ilayer<8) {
	  EMenergy += cell_E;
	  EMet += cell_Et;
	}

	// for FH layer
	if(cell_ilayer==11) {
	  FHenergy += cell_E;
	  FHet += cell_Et;
	}
      } // for all rotated 13 towers

    } // EM+FH1 cells	  
  } // loop over all calorimeter cells
}
	
Double_t uParaMCAnalysis::Feng_cone(const int elec_ieta, const int elec_iphi,const TMBCellContainer * fCells ){
  Double_t zones[2];
  zones[0]=0.;
  zones[1]=0.;
  double coshElecEta, energy, et, EMenergy, EMet, FHenergy, FHet;
  double phi =  (3.14159265*( 2* ((double)elec_iphi) -1) ) / 64.;
  Double_t cone[32];
  for (Int_t i=0; i<32; i++) cone[i]=0;
  for(int irotate = 0; irotate < 31; irotate++) {
	  
    for (Int_t i=0; i<31; i++) {
      int _ciphi = elec_iphi + i;
      if(_ciphi > 64) {
	_ciphi = _ciphi - 64;
      }    
      GetRawEnergy(elec_ieta,_ciphi, fCells, coshElecEta, energy, et, EMenergy, EMet, FHenergy, FHet);
      cone[i] = energy;
      double _cphi =  (3.14159265*( 2* ((double)_ciphi) -1) ) / 64.;
	      
      double _delphi = fabs(_cphi - phi);
      if(_delphi>3.14159265) _delphi = 2*3.14159265 - _delphi;
      if((_delphi>0.3)&&(_delphi<2.8)){
	if (cone[i]/cone[0] < 0.15){
	  ++zones[0];
	  zones[1]+=cone[i];
	}
      }
    }
    if (zones[0] > 0.){
      return zones[1]/(zones[0]);  
    }
    else
      return 0;
  }
  return 0;
}


Double_t uParaMCAnalysis::Junjie_cone(const int elec_ieta, const int elec_iphi,const TMBCellContainer * fCells ){
  Double_t zones[2];
  zones[0]=0.;
  zones[1]=0.;
  double coshElecEta, energy, et, EMenergy, EMet, FHenergy, FHet;
  double phi =  (3.14159265*( 2* ((double)elec_iphi) -1) ) / 64.;
  Double_t cone[9];
  for (Int_t i=0; i<8; i++) cone[i]=0;
  for(int irotate = 0; irotate < 31; irotate++) {
	  
    for (Int_t i=0; i<9; i++) {
      int iphi_rotated;
      if (i==0)
	iphi_rotated = elec_iphi;
      else if(irotate < 5) { // rotate clock-wise
	iphi_rotated = elec_iphi + irotate + 4;
	if(iphi_rotated > 64) iphi_rotated -= 64;
      } else { // rotate counterclockwise
	iphi_rotated = elec_iphi - (irotate-5) - 5;
	if(iphi_rotated < 0) iphi_rotated += 64;
      }
      
      GetRawEnergy(elec_ieta,iphi_rotated, fCells, coshElecEta, energy, et, EMenergy, EMet, FHenergy, FHet);
      cone[i] = energy;
      double _cphi =  (3.14159265*( 2* ((double)iphi_rotated) -1) ) / 64.;
	      
      double _delphi = fabs(_cphi - phi);
      if(_delphi>3.14159265) _delphi = 2*3.14159265 - _delphi;
      if((_delphi>0.3)&&(_delphi<2.8)){
	if (cone[i]/cone[0] < 0.15){
	  ++zones[0];
	  zones[1]+=cone[i];
	}
      }
    }
    if (zones[0] > 0.){
      return zones[1]/(zones[0]);  
    }
    else
      return 0;
  }
  return 0;
}





ClassImp(uParaMCAnalysis)
