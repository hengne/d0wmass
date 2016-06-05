#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include "wmass_analysis/ZNuNuAnalysis.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "wmass_util/WZ_Utils.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "wmass_analysis/histograms.hpp"
#include <TFile.h>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cafe;

#define PrintSNsup false

ZNuNuAnalysis::ZNuNuAnalysis(const char *name) : Processor(name)
{
  Config config(name);

  // histograms
  _histos.add(ZNuNu_Hist);
  _histos.add(ZNuNu_Profile);
  _histos.add(ZNuNu_Profile);

  // debug level
  _debugLevel = config.get("debugLevel", 0);

  _MCStudy = config.get("MCStudy", false);
  _MCStudy_ZNuNu = config.get("MCStudy_ZNuNu", false);

  if(!_MCStudy || !_MCStudy_ZNuNu) {
    cerr << "ZNuNuAnalysis: Both MCStudy_ZNuNu and MCStudy parameters must be set to 'true'" << endl
         << "               in order to run this processor !!!" << endl
	 << "               MCStudy       = " << _MCStudy << endl
	 << "               MCStudy_ZNuNu = " << _MCStudy_ZNuNu << endl;
    throw;
  }

  // get cuts for MC neutrions for hadronic recoil transverse energy flow studies 
  _NuLoose_nMin   = config.get("ZNuNu_NuLoose_nMin",   2);       // require >=2 loose neutrionos
  _NuLoose_EtaMax = config.get("ZNuNu_NuLoose_EtaMax", 1000.0);  // no cut
  _NuLoose_PtMin  = config.get("ZNuNu_NuLoose_PtMin",  0.0);     // no cut
  _NuTight_nMin   = config.get("ZNuNu_NuTight_nMin",   0);       // no cut
  _NuTight_EtaMax = config.get("ZNuNu_NuTight_EtaMax", 1000.0);  // no cut
  _NuTight_PtMin  = config.get("ZNuNu_NuTight_PtMin",  0.0);     // no cut
  _UtCutMin       = config.get("ZNuNu_UtCutMin",       0.0);     // no cut
  _UtCutMax       = config.get("ZNuNu_UtCutMax",       10000.0); // no cut
  _SETCutMin      = config.get("ZNuNu_SETCutMin",      0.0);     // no cut
  _SETCutMax      = config.get("ZNuNu_SETCutMax",      10000.0); // no cut
  _LumiCutMin     = config.get("ZNuNu_LumiCutMin",     0.0);     // no cut
  _LumiCutMax     = config.get("ZNuNu_LumiCutMax",     10000.0); // no cut
  if(( _NuTight_PtMin < _NuLoose_PtMin ) || ( _NuTight_EtaMax > _NuLoose_EtaMax )) {
    cerr << "ZNuNuAnalysis: Wrong specification of Loose and Tight cuts!!!" << endl
	 << "               pT(Loose nu)>=" << _NuLoose_PtMin << " GeV, |eta(Loose nu)|<" << _NuLoose_EtaMax << endl
	 << "               pT(Tight nu)>=" << _NuTight_PtMin << " GeV, |eta(Tight nu)|<" << _NuTight_EtaMax << endl;
    throw;
  }
  ////////// cout << "ZNuNuAnalysis::ZNuNuAnalysis: Loose/Thight neutrinos config OK" << endl;

  _do_RecoilEtFlow_studies = config.get("ZNuNu_EtFlow_studies", false);
  if(_debugLevel>10) cout << "ZNuNuAnalysis: ZNuNu_EtFlow_studies OK" << endl;

  _RecoilEtFlow_studies_TowCut = config.get("ZNuNu_EtFlow_studies_TowCut", 99999.);

  _dumpRecoilInfo = config.get("ZNuNu_dumpRecoilInfo", false);
  if(_debugLevel>10) cout << "ZNuNuAnalysis: ZNuNu_dumpRecoilInfo OK" << endl;

  if((_do_RecoilEtFlow_studies || _dumpRecoilInfo) && !_MCStudy) {
    cerr << "ZNuNuAnalysis: MCStudy parameter must be set to 'true' whenever ET-flow studies and/or" << endl
	 << "               dumping the events with generator/reco recoil information is requested!!!" << endl
	 << "               MCStudy              = " << _MCStudy << endl
	 << "               ZNuNu_EtFlow_studies = " << _do_RecoilEtFlow_studies << endl
	 << "               ZNuNu_dumpRecoilInfo = " << _dumpRecoilInfo << endl;
    throw;
  }

  string _EtFlow_fname = config.get("ZNuNu_EtFlow_studies_inputfile", " ");
  if(_debugLevel>10) cout << "ZNuNuAnalysis: ZNuNu_EtFlow_studies_inputfile OK" << endl;

  if(_do_RecoilEtFlow_studies && _EtFlow_fname==" ") {

    cerr << "ZNuNuAnalysis: ET-flow studies are enabled, but the input file with relative response" << endl
	 << "               per PHI towers is missiing!!!" << endl
	 << "               MCStudy                        = " << _MCStudy << endl
	 << "               ZNuNu_EtFlow_studies           = " << _do_RecoilEtFlow_studies << endl
	 << "               ZNuNu_EtFlow_studies_inputfile = " << _EtFlow_fname << endl;
    throw;
  }
  for(int iphi=-31; iphi<=32; iphi++) _RelResponse_scale[iphi]=1.0;
  if(_debugLevel>10) cout << "ZNuNuAnalysis: _RelResponse_scale[iphi] init to 1 OK" << endl;

  fstream *_EtFlow_input=new fstream(_EtFlow_fname.c_str(), std::ios::in);
  if(_debugLevel>10) cout << "ZNuNuAnalysis: _EtFlow_input open OK" << endl;

  while( _EtFlow_input->good() ) {
    int    iphi=0;
    double resp=-1;
    /////////// if(_debugLevel>10) cout << "ZNuNuAnalysis: _EtFlow_input->good() loop OK" << endl;
    (*_EtFlow_input) >> iphi >> resp;
    if(iphi>=-31 && iphi<=32 && resp>=0.0) _RelResponse_scale[iphi]=resp;
  };
  _EtFlow_input->close();
  if(_debugLevel>10) cout << "ZNuNuAnalysis: _EtFlow_input->close() OK" << endl;

  // clone some histograms for Junjie's comparison plots
  // per bins of: UT        (with suffix _bin_<N>), 
  //              true Z Pt (with suffix _genZPt_bin_<N>) 
  const string _histos_name[]={ 
    "ZNuNu_genZPt_Cuts",
    "ZNuNu_genZPhi_Cuts",
    "ZNuNu_genVtxZ_Cuts",
    "ZNuNu_VtxZ_Cuts",
    "ZNuNu_RecoilPt_Cuts",
    "ZNuNu_RecoilPx_Cuts",
    "ZNuNu_RecoilPy_Cuts",
    "ZNuNu_RecoilPhi_Cuts",
    "ZNuNu_RecoilResolution_Cuts",
    "ZNuNu_DeltaPhi_genZ_Recoil_Cuts",
    "ZNuNu_Met_Cuts",
    "ZNuNu_MetX_Cuts",
    "ZNuNu_MetY_Cuts",
    "ZNuNu_MetPhi_Cuts",
    "ZNuNu_ScalarEt_Cuts"
  };
  int nhist=sizeof(_histos_name)/sizeof(string);
  for(int ihist=0;ihist<nhist;ihist++) {
    _histos.clone(_histos_name[ihist].c_str(), 10, "_bin");
    _histos.clone(_histos_name[ihist].c_str(), 10, "_genZPt_bin");
  }

  // hadronic recoil transverse energy flow studies (wrt direction of the true MC recoil)
  if(_do_RecoilEtFlow_studies) {
    _EtFlow_histos.add(ZNuNu_EtFlow_Hist);        // 1d histograms
    _EtFlow_histos.add(ZNuNu_EtFlow_Profile);     // profiles
    _EtFlow_histos.add(ZNuNu_EtFlow_Profile_2D);     // profiles
    _EtFlow_histos.add(ZNuNu_EtFlow_Profile_VarX);// profiles
    const int nbins_cuts=_EtFlow_histos.tprofile("ZNuNu_EtFlow_genZPt_V_genZPt_Cuts")->GetNbinsX(); 
    if(_debugLevel>10) cout << "ZNuNuAnalysis: clone - begin" << endl;

    // clone some histograms for ET-flow studies
    const string _EtFlow_histos_name[]={ 
      "ZNuNu_EtFlow_genVtxZ_Cuts",
      "ZNuNu_EtFlow_VtxZ_Cuts",
      "ZNuNu_EtFlow_genZPt_Cuts",
      "ZNuNu_EtFlow_genUt_Cuts",
      "ZNuNu_EtFlow_recoUt_Cuts",
      "ZNuNu_EtFlow_recoRecoilPhi_Cuts",
      "ZNuNu_EtFlow_recoRecoilResp_Cuts",
      "ZNuNu_EtFlow_recoRecoilRespPrj_Cuts",
      "ZNuNu_EtFlow_DPhi_recoUt_genZPt_Cuts",
      "ZNuNu_EtFlow_DPhi_CellsUt_recoUt_Cuts",
      //      "ZNuNu_EtFlow_DPhi_CellsScaledUt_recoUt_Cuts",
      "ZNuNu_EtFlow_recoUt_V_DPhi_recoUt_genZPt_Cuts",
      "ZNuNu_EtFlow_CellsUt_Cuts",
      //      "ZNuNu_EtFlow_CellsScaledUt_Cuts",
      "ZNuNu_EtFlow_CellsRecoilPhi_Cuts",
      //      "ZNuNu_EtFlow_CellsScaledRecoilPhi_Cuts",
      "ZNuNu_EtFlow_CellsRecoilResp_Cuts",
      //      "ZNuNu_EtFlow_CellsScaledRecoilResp_Cuts",
      "ZNuNu_EtFlow_CellsRecoilRespPrj_Cuts",
      //      "ZNuNu_EtFlow_CellsScaledRecoilRespPrj_Cuts",
      "ZNuNu_EtFlow_CellsUt_V_DPhi_CellsUt_genZPt_Cuts",
      //      "ZNuNu_EtFlow_CellsScaledUt_V_DPhi_CellsScaledUt_genZPt_Cuts",
      "ZNuNu_EtFlow_AveEt_V_iphi_wrt_genZPt_Cuts",
      //      "ZNuNu_EtFlow_AveEtScaled_V_iphi_wrt_genZPt_Cuts"
      "ZNuNu_EtFlow_Et_wrt_genUt_Cuts"
    };
    nhist=sizeof(_EtFlow_histos_name)/sizeof(string);
    for(int ihist=0;ihist<nhist;ihist++) {
      _EtFlow_histos.clone(_EtFlow_histos_name[ihist].c_str(), nbins_cuts, "_genZPt_bin");
    }
    if(_debugLevel>10) cout << "ZNuNuAnalysis: clone - OK" << endl;
  }

  // dump measured hadronic recoil and generated Z info to an ASCII file
  string _dumpRecoilFile = config.get("ZNuNu_dumpRecoilFile", "znunu_recoil_dump.txt");
  if(_dumpRecoilInfo) {
    _znunu_out_recoil_txt = new fstream(_dumpRecoilFile.c_str(), std::ios::out);
    if(_znunu_out_recoil_txt) {
      _znunu_out_recoil_txt->flags( ios::right | ios::scientific );
      (*_znunu_out_recoil_txt) << setw(9)  << "#  Run.No" 
			       << setw(9)  << "Evt.No" 
			       << setw(16) << "gen.Z.Px" 
			       << setw(16) << "gen.Z.Py" 
			       << setw(16) << "gen.Z.Pz" 
			       << setw(16) << "gen.Z.E" 
			       << setw(16) << "gen.rec.Px" 
			       << setw(16) << "gen.rec.Py" 
			       << setw(16) << "gen.rec.Pz" 
			       << setw(16) << "gen.rec.E" 
			       << setw(16) << "rec.Px"
			       << setw(16) << "rec.Py" 
			       << setw(16) << "Tot.SET"
			       << endl;
    }
  }

  // Per-event "single neutrino subtraction"
  _SubtractSingleNeutrinos = config.get("ZNuNu_SubtractSingleNeutrinos",false);
  if (_SubtractSingleNeutrinos) {
    _SNdirectory = config.get("ZNuNu_SNdirectory", "");
    TString fn;
    fn=_SNdirectory;
    fn+="/Metadata.txt";
    Int_t SNrun,SNevent,SNfile,SNindex;
    fstream rein(fn,ios::in);
    while (rein.good()) {
      rein>>SNrun>>SNevent>>SNfile>>SNindex;
      if (rein.eof()) break;
      _SNmetadata.insert(pair<pair<int,int>,pair<int,int> >(pair<int,int>(SNrun,SNevent),pair<int,int>(SNfile,SNindex)));
    }
    rein.close();
    cout<<"ZNuNuAnalysis: read metadata for "<<_SNmetadata.size()<<" single neutrino events."<<endl;
  }

  if(_debugLevel>10) cout << "ZNuNuAnalysis: Ended OK" << endl;
}

ZNuNuAnalysis::~ZNuNuAnalysis() {
}

// process 
bool ZNuNuAnalysis::processEvent(cafe::Event& event) {
 
  CAFMet met, raw_met;
  vector<CAFEMObj*> emobjs;
  float vtx_x, vtx_y, vtx_z;
  double instlumi;

  TMBMCpart *mc_Z;
  TMBMCpart *mc_Recoil;
  vector<TMBMCpart *> mc_neutrinos; 
  
  if(_debugLevel>10) {
    cout << "ZNuNuAnalysis: RECO level:" << endl;
    cout << "ZNuNuAnalysis: event.get('EMCorr Met')           = " << event.get("EMCorr Met", met) <<endl;
    cout << "ZNuNuAnalysis: event.get('Raw Met')              = " << event.get("Raw Met", raw_met) <<endl;
    cout << "ZNuNuAnalysis: event.get('Good EMObjs')          = " << event.get("Good EMObjs", emobjs) <<endl;
    cout << "ZNuNuAnalysis: " << emobjs.size() << " EM objs" << endl;
    cout << "ZNuNuAnalysis: event.get('Best primary vertexX') = " << event.get("Best primary vertexX", vtx_x) <<endl;
    cout << "ZNuNuAnalysis: event.get('Best primary vertexY') = " << event.get("Best primary vertexY", vtx_y) <<endl;
    cout << "ZNuNuAnalysis: event.get('Best primary vertexZ') = " << event.get("Best primary vertexZ", vtx_z) <<endl;
    cout << "ZNuNuAnalysis: MC level:" <<endl;
    cout << "ZNuNuAnalysis: event.get('WZ boson object')      = " << event.get("WZ boson object", mc_Z) <<endl;
    cout << "ZNuNuAnalysis: event.get('mc recoil object')     = " << event.get("mc recoil object", mc_Recoil) <<endl;
    cout << "ZNuNuAnalysis: event.get('mc neutrinos')         = " << event.get("mc neutrinos", mc_neutrinos) <<endl;
    cout << "ZNuNuAnalysis: "<< mc_neutrinos.size() << " neutrinos" << endl;
  }

  if( event.get("mc neutrinos", mc_neutrinos)  && 
      mc_neutrinos.size()>=2                   &&
      event.get("WZ boson object", mc_Z)       &&
      event.get("mc recoil object", mc_Recoil) &&
      event.get("Raw Met", raw_met)            &&
      event.get("Best primary vertexX", vtx_x) && 
      event.get("Best primary vertexY", vtx_y) && 
      event.get("Best primary vertexZ", vtx_z) &&
      event.get("InstLumi", instlumi)   )  {
    
    // Single neutrino subtraction, if requested
    if (_SubtractSingleNeutrinos) {
      float vtx[3]={vtx_x,vtx_y,vtx_z};
      raw_met=CalculateSNSubtrMet(event,vtx);
      if (raw_met.scalarEt()<-600) return false;
    }

    // # of good MC level neutrinos
    int nTightNeutrinos = 0; 
    int nLooseNeutrinos = 0;
    
    // check generator level neutrinos from Z
    for (std::vector<TMBMCpart *>::iterator it = mc_neutrinos.begin(); 
	 it!= mc_neutrinos.end(); ++it) {
      if( fabs((*it)->Eta())<_NuLoose_EtaMax && (*it)->Pt()>_NuLoose_PtMin) nLooseNeutrinos++;
      if( fabs((*it)->Eta())<_NuTight_EtaMax && (*it)->Pt()>_NuTight_PtMin) nTightNeutrinos++;
    }
    if(_debugLevel>10) cout << "ZNuNuAnalysis: N(loose)=" << nLooseNeutrinos << ", N(tight)=" << nTightNeutrinos << endl;

    double recoilPt = raw_met.met();
    double scalarEt = raw_met.scalarEt();

    // require a combination of "Loose" and "Tight" neutrinos that fulfill 
    // user specified cuts on PT and ETA
    bool kinem_cuts_ok = false;
    if(nLooseNeutrinos>=_NuLoose_nMin &&
       nTightNeutrinos>=_NuTight_nMin &&
       scalarEt<_SETCutMax            &&
       scalarEt>=_SETCutMin           &&
       instlumi<_LumiCutMax           &&
       instlumi>=_LumiCutMin          &&
       recoilPt>=_UtCutMin            &&
       recoilPt<_UtCutMax               ) kinem_cuts_ok=true;
    if(!kinem_cuts_ok) return false;
    if(_debugLevel>10) cout << "ZNuNuAnalysis: kinematical cuts OK" << endl;

    // MC - RECO observables
    double VtxZ_true = mc_Z->getPMCvtx()->z();
    double ZPt_true  = mc_Z->Pt();
    double ZPx_true  = mc_Z->Px();
    double ZPy_true  = mc_Z->Py();
    double ZPhi_true = kinem::phi(ZPx_true, ZPy_true);
    double recoilPx_true = mc_Recoil->Px();
    double recoilPy_true = mc_Recoil->Py();
    double recoilPt_true = mc_Recoil->Pt();
    double recoilPhi_true = kinem::phi(recoilPx_true, recoilPy_true);
    
    double recoilPx = -raw_met.metx();
    double recoilPy = -raw_met.mety();
    double recoilPhi = kinem::phi(recoilPx, recoilPy);
    
    double recoilPtResp    = recoilPt/recoilPt_true;
    double recoilPtRespPrj = (recoilPx_true*recoilPx + recoilPy_true*recoilPy)/recoilPt_true/recoilPt_true;
    double recoilPtResol   = 1.0-recoilPtResp;
    
    double phi_trueZ_Recoil = kinem::delta_phi(recoilPhi,ZPhi_true);                         // reco-gen
    double phi_trueZ_trueRecoil = kinem::delta_phi(recoilPhi_true,ZPhi_true);                // gen-gen
    
    // recoil system vector
    TVector2 recoil_vect(recoilPx, recoilPy);
    TVector2 recoil_vect_gen(-ZPx_true, -ZPy_true);
    
    ////////////////////////////////////////////////////////////////////
    // begin of backward compatibility plots for Junjie's znunucomp.cpp
    ////////////////////////////////////////////////////////////////////
    //
    //
    int ZPt_true_bin = wz_utils::pTee_Eta_Bin(ZPt_true);
    char sn[20]; sprintf(sn, "_genZPt_bin_%d", ZPt_true_bin);

    int Ut_bin = wz_utils::pTee_Eta_Bin(recoilPt);
    char sn_smear[10];  sprintf(sn_smear, "_bin_%d", Ut_bin);

    // fill recoil pT, pX, pY and phi    
    _histos.Fill1D("ZNuNu_genZPt_Cuts", ZPt_true);
    _histos.Fill1D("ZNuNu_genZPhi_Cuts", ZPhi_true);
    _histos.Fill1D("ZNuNu_VtxZ_Cuts", vtx_z); 
    _histos.Fill1D("ZNuNu_genVtxZ_Cuts", VtxZ_true);
    _histos.Fill1D("ZNuNu_RecoilPt_Cuts", recoilPt);
    _histos.Fill1D("ZNuNu_RecoilPx_Cuts", recoilPx);
    _histos.Fill1D("ZNuNu_RecoilPy_Cuts", recoilPy);
    _histos.Fill1D("ZNuNu_RecoilPhi_Cuts", recoilPhi);
    _histos.Fill1D("ZNuNu_RecoilResolution_Cuts", recoilPtResol);
    _histos.Fill1D("ZNuNu_DeltaPhi_genZ_Recoil_Cuts", phi_trueZ_Recoil);
    _histos.Fill1D("ZNuNu_Met_Cuts", raw_met.met() );
    _histos.Fill1D("ZNuNu_MetPhi_Cuts", raw_met.metphi() );
    _histos.Fill1D("ZNuNu_MetX_Cuts", raw_met.metx() );
    _histos.Fill1D("ZNuNu_MetY_Cuts", raw_met.mety() );
    _histos.Fill1D("ZNuNu_ScalarEt_Cuts", scalarEt );
    
    // fill response profile
    _histos.FillProfile("ZNuNu_RecoilResponse_V_RecoilPt_Cuts", recoilPt, recoilPtResp);
    _histos.FillProfile("ZNuNu_RecoilResponse_V_genZPt_Cuts", ZPt_true, recoilPtResp);
    _histos.FillProfile("ZNuNu_RecoilResponseProjection_V_RecoilPt_Cuts", recoilPt, recoilPtRespPrj);
    _histos.FillProfile("ZNuNu_RecoilResponseProjection_V_genZPt_Cuts", ZPt_true, recoilPtRespPrj);
    
    if(Ut_bin >= 0) {
      _histos.Fill1D(string("ZNuNu_genZPt_Cuts")+sn_smear, ZPt_true);
      _histos.Fill1D(string("ZNuNu_genZPhi_Cuts")+sn_smear, ZPhi_true);
      _histos.Fill1D(string("ZNuNu_VtxZ_Cuts")+sn_smear, vtx_z); 
      _histos.Fill1D(string("ZNuNu_genVtxZ_Cuts")+sn_smear, VtxZ_true);
      _histos.Fill1D(string("ZNuNu_RecoilPt_Cuts")+sn_smear, recoilPt);
      _histos.Fill1D(string("ZNuNu_RecoilPx_Cuts")+sn_smear, recoilPx);
      _histos.Fill1D(string("ZNuNu_RecoilPy_Cuts")+sn_smear, recoilPy);
      _histos.Fill1D(string("ZNuNu_RecoilPhi_Cuts")+sn_smear, recoilPhi);
      _histos.Fill1D(string("ZNuNu_RecoilResolution_Cuts")+sn_smear, recoilPtResol);
      _histos.Fill1D(string("ZNuNu_DeltaPhi_genZ_Recoil_Cuts")+sn_smear, phi_trueZ_Recoil);
      _histos.Fill1D(string("ZNuNu_Met_Cuts")+sn_smear, raw_met.met() );
      _histos.Fill1D(string("ZNuNu_MetPhi_Cuts")+sn_smear, raw_met.metphi() );
      _histos.Fill1D(string("ZNuNu_MetX_Cuts")+sn_smear, raw_met.metx() );
      _histos.Fill1D(string("ZNuNu_MetY_Cuts")+sn_smear, raw_met.mety() );
      _histos.Fill1D(string("ZNuNu_ScalarEt_Cuts")+sn_smear, scalarEt );
    }
    
    if(ZPt_true_bin >= 0) {
      _histos.Fill1D(string("ZNuNu_genZPt_Cuts")+sn, ZPt_true);
      _histos.Fill1D(string("ZNuNu_genZPhi_Cuts")+sn, ZPhi_true);
      _histos.Fill1D(string("ZNuNu_VtxZ_Cuts")+sn, vtx_z);                 // reco
      _histos.Fill1D(string("ZNuNu_genVtxZ_Cuts")+sn, VtxZ_true);          // gen
      _histos.Fill1D(string("ZNuNu_RecoilPt_Cuts")+sn, recoilPt);
      _histos.Fill1D(string("ZNuNu_RecoilPx_Cuts")+sn, recoilPx);
      _histos.Fill1D(string("ZNuNu_RecoilPy_Cuts")+sn, recoilPy);
      _histos.Fill1D(string("ZNuNu_RecoilPhi_Cuts")+sn, recoilPhi);
      _histos.Fill1D(string("ZNuNu_RecoilResolution_Cuts")+sn, recoilPtResol);
      _histos.Fill1D(string("ZNuNu_DeltaPhi_genZ_Recoil_Cuts")+sn, phi_trueZ_Recoil);
      _histos.Fill1D(string("ZNuNu_Met_Cuts")+sn, raw_met.met() );
      _histos.Fill1D(string("ZNuNu_MetPhi_Cuts")+sn, raw_met.metphi() );
      _histos.Fill1D(string("ZNuNu_MetX_Cuts")+sn, raw_met.metx() );
      _histos.Fill1D(string("ZNuNu_MetY_Cuts")+sn, raw_met.mety() );
      _histos.Fill1D(string("ZNuNu_ScalarEt_Cuts")+sn, scalarEt );
    }
    //
    //
    ////////////////////////////////////////////////////////////////////
    // end of backward compatibility plots for Junjie's znunucomp.cpp
    ////////////////////////////////////////////////////////////////////
      
    ////////////////////////////////////////////////////////////////////
    // do Mikolaj's recoil ET-flow studies for Z events with 2 neutrinos
    ////////////////////////////////////////////////////////////////////
    if(_do_RecoilEtFlow_studies) {
        
      if(_debugLevel>10) cout << "ZNuNuAnalysis: ET-Flow studies started" << endl << flush;
      
      // now recompute the recoil momentum from the cells, exclude 2 EM clusters
      // - raw_calcells_Recoil vector should be in principle same as the RECO one (it's computed as a cross-check)
      // - raw_calcells_Recoil_scaled vector is from rescaled cells and should be different that that from RECO
      TVector2 raw_calcells_Recoil(0., 0.);           // recoil transverse momentum from cells
      TVector2 raw_calcells_Recoil_scaled(0., 0.);    // recoil transverse momentum from cells (rescaled)
      TVector2 raw_calcells_Recoil_xcheck(0., 0.);    // recoil transverse momentum from cells (alternative)
      map<int,double> Et_flow;                        // average ET per PHI-tower in an event
      map<int,double> Et_flow_scaled;                 // average ET per PHI-tower in an event (rescaled cells)
      map<int,double>::iterator it;
      vector<CAFEMObj*> emobjs(0);                    // an empty vector (just for compatibility)
      
      float vtx[3] = {vtx_x, vtx_y, vtx_z};    
      wz_utils::calc_Et_per_tower(event, emobjs, recoilPhi_true, vtx, 
				  _RelResponse_scale,
				  raw_calcells_Recoil, raw_calcells_Recoil_scaled, raw_calcells_Recoil_xcheck,
				  Et_flow, Et_flow_scaled);
      
      double recoilPt_cells                = raw_calcells_Recoil.Mod();
      double recoilPt_cells_scaled         = raw_calcells_Recoil_scaled.Mod();
      double recoilPtResp_cells            = recoilPt_cells/recoilPt_true;
      double recoilPtResp_cells_scaled     = recoilPt_cells_scaled/recoilPt_true;
      
      double recoilPtRespPrj_cells         = (recoilPx_true*raw_calcells_Recoil.Px() + 
					      recoilPy_true*raw_calcells_Recoil.Py())/recoilPt_true;
      double recoilPtRespPrj_cells_scaled  = (recoilPx_true*raw_calcells_Recoil_scaled.Px() + 
					      recoilPy_true*raw_calcells_Recoil_scaled.Py())/recoilPt_true;
      double recoilPtRespPrj_cells_xcheck  = (recoilPx_true*raw_calcells_Recoil_xcheck.Px() + 
					      recoilPy_true*raw_calcells_Recoil_xcheck.Py())/recoilPt_true;
      
      double recoilPhi_cells         = kinem::phi(raw_calcells_Recoil.Px(), raw_calcells_Recoil.Py());
      double recoilPhi_cells_scaled  = kinem::phi(raw_calcells_Recoil_scaled.Px(), raw_calcells_Recoil_scaled.Py());
      double recoilPhi_cells_xcheck  = kinem::phi(raw_calcells_Recoil_xcheck.Px(), raw_calcells_Recoil_xcheck.Py());
      
      double phi_trueZ_Recoil_cells        = kinem::delta_phi(raw_calcells_Recoil.Phi(),ZPhi_true);
      double phi_trueZ_Recoil_cells_scaled = kinem::delta_phi(raw_calcells_Recoil_scaled.Phi(),ZPhi_true);
      double phi_Recoil_Recoil_cells       = kinem::delta_phi(raw_calcells_Recoil.Phi(),recoilPhi);
      double phi_Recoil_Recoil_cells_scaled= kinem::delta_phi(raw_calcells_Recoil_scaled.Phi(),recoilPhi);
      
      double phi_Recoil_Recoil_cells_xcheck= kinem::delta_phi(raw_calcells_Recoil_xcheck.Phi(),recoilPhi);
      
      // determine the bin number for a given true PT(Z) to fill the right histograms
      const int bin_gen  = _EtFlow_histos.tprofile("ZNuNu_EtFlow_genZPt_V_genZPt_Cuts")
	->FindBin(ZPt_true)-1;                                                             // gen
      const int nbin_gen = _EtFlow_histos.tprofile("ZNuNu_EtFlow_genZPt_V_genZPt_Cuts")
	->GetNbinsX();                                                                     // gen
      char sn[15];
      bool bingen_ok = (bin_gen>=0 && bin_gen<nbin_gen);
      if(bingen_ok) sprintf(sn, "_genZPt_bin_%d", bin_gen);
      
      // Fill histograms based on MC / RECO recoil -- all events
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_genVtxZ_Cuts", VtxZ_true);                       // gen
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_VtxZ_Cuts", vtx_z);                              // reco
      
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_genZPt_Cuts", 
			    ZPt_true);                                                     // gen
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_genUt_Cuts", 
			    recoilPt_true);                                                // gen
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_recoUt_Cuts", 
			    recoilPt);                                                     // reco
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_recoRecoilPhi_Cuts",
			    recoilPhi);                                                    // reco
      _EtFlow_histos.FillProfile("ZNuNu_EtFlow_genZPt_V_genZPt_Cuts",  
				 ZPt_true, ZPt_true);                                      // gen
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_recoRecoilResp_Cuts", 
			    recoilPtResp);                                                 // gen-reco
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_recoRecoilRespPrj_Cuts", 
			    recoilPtRespPrj);                                              // gen-reco
      _EtFlow_histos.FillProfile("ZNuNu_EtFlow_recoRecoilResp_V_genZPt_Cuts", 
				 recoilPtResp, ZPt_true);                                  // gen
      _EtFlow_histos.FillProfile("ZNuNu_EtFlow_recoRecoilRespPrj_V_genZPt_Cuts", 
				 recoilPtRespPrj, ZPt_true);                               // gen
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_DPhi_recoUt_genZPt_Cuts",  
			    phi_trueZ_Recoil);                                             // reco-gen
      _EtFlow_histos.FillProfile("ZNuNu_EtFlow_recoUt_V_DPhi_recoUt_genZPt_Cuts",
				 phi_trueZ_Recoil, recoilPt);	                            // reco-gen 
      
      // Fill histograms related to ET FLOW -- all events
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_CellsUt_Cuts",
			    recoilPt_cells);                                               // cells
      /*
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_CellsScaledUt_Cuts",
			    recoilPt_cells_scaled);                                        // cells(scaled)
      */
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_CellsRecoilPhi_Cuts",
			    recoilPhi_cells);                                              // cells
      /*
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_CellsScaledRecoilPhi_Cuts",
			    recoilPhi_cells_scaled);                                     // cells(scaled)
      */
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_CellsRecoilResp_Cuts",
			    recoilPtResp_cells);                                           // cells
      /*
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_CellsScaledRecoilResp_Cuts",
			    recoilPtResp_cells_scaled);                                    // cells(scaled)
      */
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_CellsRecoilRespPrj_Cuts",
			    recoilPtRespPrj_cells);                                        // cells
      /*
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_CellsScaledRecoilRespPrj_Cuts",
			    recoilPtRespPrj_cells_scaled);                                 // cells(scaled)
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_XCHECKrecoRecoilRespPrj_Cuts",
			    recoilPtRespPrj_cells_xcheck);                          // gen-cells(reco xcheck)
      */
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_DPhi_CellsUt_recoUt_Cuts",
			    phi_Recoil_Recoil_cells);                               // cells-reco
      /*
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_DPhi_CellsScaledUt_recoUt_Cuts",
			    phi_Recoil_Recoil_cells_scaled);                        // cells(scaled)-reco
      _EtFlow_histos.Fill1D("ZNuNu_EtFlow_DPhi_XCHECKrecoUt_recoUt_Cuts",
			    phi_Recoil_Recoil_cells_xcheck);                        // cells(reco xcheck)-reco
      */
      _EtFlow_histos.FillProfile("ZNuNu_EtFlow_CellsUt_V_DPhi_CellsUt_genZPt_Cuts",
				 phi_trueZ_Recoil_cells, recoilPt_cells);	            // cells-gen    
      /*
      _EtFlow_histos.FillProfile("ZNuNu_EtFlow_CellsScaledUt_V_DPhi_CellsScaledUt_genZPt_Cuts",
				 phi_trueZ_Recoil_cells_scaled, recoilPt_cells_scaled);    // cells(scaled)-gen
      */
      for(int delta_iphi=-31; delta_iphi<=32; delta_iphi++) {
	if (Et_flow[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	  _EtFlow_histos.FillProfile("ZNuNu_EtFlow_AveEt_V_iphi_wrt_genZPt_Cuts",       
				     delta_iphi, Et_flow[delta_iphi]);                     // cells-gen
	  _EtFlow_histos.Fill1D("ZNuNu_EtFlow_Et_wrt_genUt_Cuts", Et_flow[delta_iphi]);
	  _EtFlow_histos.FillProfile2D("ZNuNu_EtFlow_AveEt_V_iphi_V_genZPt_Cuts", delta_iphi, ZPt_true, Et_flow[delta_iphi]);
	}
	/*
	if (Et_flow_scaled[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	  _EtFlow_histos.FillProfile("ZNuNu_EtFlow_AveEtScaled_V_iphi_wrt_genZPt_Cuts",
  	                              delta_iphi, Et_flow_scaled[delta_iphi]);             // cells(scaled)-gen
        }
	*/
      }
      // individual true PT(Z) bins
      if(bingen_ok) {
	// Fill histograms based on MC / RECO recoil
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_genVtxZ_Cuts")+sn, VtxZ_true);          // gen
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_VtxZ_Cuts")+sn, vtx_z);                 // reco
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_genZPt_Cuts")+sn, 
			      ZPt_true);                                                   // gen
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_genUt_Cuts")+sn, 
			      recoilPt_true);                                              // gen
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_recoUt_Cuts")+sn, 
			      recoilPt);                                                   // reco
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_recoRecoilPhi_Cuts")+sn,
			      recoilPhi);                                                  // reco
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_recoRecoilResp_Cuts")+sn, 
			      recoilPtResp);                                               // gen-reco
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_recoRecoilRespPrj_Cuts")+sn, 
			      recoilPtRespPrj);                                            // gen-reco
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_DPhi_recoUt_genZPt_Cuts")+sn,  
			      phi_trueZ_Recoil);                                           // reco-gen
	_EtFlow_histos.FillProfile(string("ZNuNu_EtFlow_recoUt_V_DPhi_recoUt_genZPt_Cuts")+sn,
				   phi_trueZ_Recoil, recoilPt);	                           // reco-gen
           
	// Fill histograms related to ET FLOW -- individual bins
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_CellsUt_Cuts")+sn,
			      recoilPt_cells);                                             // cells
	/*
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_CellsScaledUt_Cuts")+sn,
			      recoilPt_cells_scaled);                                      // cells(scaled)
	*/
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_CellsRecoilPhi_Cuts")+sn,
			      recoilPhi_cells);                                            // cells
	/*
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_CellsScaledRecoilPhi_Cuts")+sn,
			      recoilPhi_cells_scaled);                                     // cells(scaled)
	*/
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_CellsRecoilResp_Cuts")+sn,
			      recoilPtResp_cells);                                         // cells
	/*
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_CellsScaledRecoilResp_Cuts")+sn,
			      recoilPtResp_cells_scaled);                                  // cells(scaled)
	*/
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_CellsRecoilRespPrj_Cuts")+sn,
			      recoilPtRespPrj_cells);                                      // cells
	/*
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_CellsScaledRecoilRespPrj_Cuts")+sn,
			      recoilPtRespPrj_cells_scaled);                               // cells(scaled)
	*/
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_DPhi_CellsUt_recoUt_Cuts")+sn,  
			      phi_Recoil_Recoil_cells);                                    // cells-reco
	/*
	_EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_DPhi_CellsScaledUt_recoUt_Cuts")+sn,
			      phi_Recoil_Recoil_cells_scaled);                             // cells(scaled)-reco
	*/
	_EtFlow_histos.FillProfile(string("ZNuNu_EtFlow_CellsUt_V_DPhi_CellsUt_genZPt_Cuts")+sn,
				   phi_trueZ_Recoil_cells, recoilPt_cells);                 // cells-gen
	/*
	_EtFlow_histos.FillProfile(string("ZNuNu_EtFlow_CellsScaledUt_V_DPhi_CellsScaledUt_genZPt_Cuts")+sn,
				   phi_trueZ_Recoil_cells_scaled, recoilPt_cells_scaled);   // cells(scaled)-gen      
	*/
	for(int delta_iphi=-31; delta_iphi<=32; delta_iphi++) {
	  if (Et_flow[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
	    _EtFlow_histos.FillProfile(string("ZNuNu_EtFlow_AveEt_V_iphi_wrt_genZPt_Cuts")+sn,
				       delta_iphi, Et_flow[delta_iphi]);                    // cells-gen                
	    _EtFlow_histos.Fill1D(string("ZNuNu_EtFlow_Et_wrt_genUt_Cuts")+sn, Et_flow[delta_iphi]);
	  }
	  /*
	  if (Et_flow_scaled[delta_iphi]<_RecoilEtFlow_studies_TowCut) {
             _EtFlow_histos.FillProfile(string("ZNuNu_EtFlow_AveEtScaled_V_iphi_wrt_genZPt_Cuts")+sn,
                                               delta_iphi, Et_flow_scaled[delta_iphi]);     // cells(scaled)-gen
          }
	  */
	}
      }
   
      if(_debugLevel>10) cout << "ZNuNuAnalysis: ET-Flow studies ended" << endl;
    } // end of Mikolaj's recoil ET-flow studies

    // Dump measured recoil and generated Z to an ascii file
    // for events that passed kinematical cuts on 2 neutrinos
    // Run # / Evt # / 4-momentum of generated Z / 4-momentum of generated recoil / transverse momentum of measured recoil
    if(_dumpRecoilInfo && kinem_cuts_ok) {
      int runNo, evtNo;
      if( event.get("run number", runNo) && event.get("event number", evtNo) ) {
	(*_znunu_out_recoil_txt) << setw(8)  << runNo << " " 
				 << setw(8)  << evtNo << " " 
				 << setw(15) << setprecision(8) << mc_Z->Px() << " " 
				 << setw(15) << setprecision(8) << mc_Z->Py() << " " 
				 << setw(15) << setprecision(8) << mc_Z->Pz() << " " 
				 << setw(15) << setprecision(8) << mc_Z->E()  << " " 
				 << setw(15) << setprecision(8) << mc_Recoil->Px() << " " 
				 << setw(15) << setprecision(8) << mc_Recoil->Py() << " " 
				 << setw(15) << setprecision(8) << mc_Recoil->Pz() << " " 
				 << setw(15) << setprecision(8) << mc_Recoil->E()  << " " 
				 << setw(15) << setprecision(8) << recoilPx        << " " 
				 << setw(15) << setprecision(8) << recoilPy        << " "
				 << setw(15) << setprecision(8) << scalarEt        << endl;
      } 
    }
    return true;
  }
  return false;
}

void ZNuNuAnalysis::begin() {}

void ZNuNuAnalysis::finish() {
 TFile *file = histfiles::initializeTFile( this );
 if(file==NULL) return;

 // needed for Junjie's znunucomp.cpp macro in wz_epmcs
 string directory_name("ZNuNuCand_Hist");
 file->mkdir(directory_name.c_str());
 _histos.save(file, directory_name);

 // needed for Mikolaj's hard recoil / Et-flow studies
 if(_do_RecoilEtFlow_studies) {
   string directory_name_2("ZNuNu_EtFlow_Hist");
   file->mkdir(directory_name_2.c_str());
   _EtFlow_histos.save(file, directory_name_2);
 }
 file->Close();

  if(_dumpRecoilInfo) _znunu_out_recoil_txt->close();
}


CAFMet ZNuNuAnalysis::CalculateSNSubtrMet(cafe::Event& event, float vtx[3]) {

  // Fetch the SN cell data
  map<pair<int,int>,pair<int,int> >::iterator it;
  it=_SNmetadata.find(pair<int,int>(event.getMCEventInfo()->overlayrun(),event.getMCEventInfo()->overlayevtid()));
  if (it==_SNmetadata.end()) {
    CAFMet dum(0,0,0,-666);
    return dum;
  } else {
    TString n;
    n=_SNdirectory;
    n+="/CellLibrary_";
    n+=it->second.first;
    n+=".root";
    TFile f(n);
    TTree* tree = (TTree*)f.Get("CellLibrary");
    tree->SetBranchAddress("CLrun", &_SNrun);
    tree->SetBranchAddress("CLevent", &_SNevent);
    tree->SetBranchAddress("CLn", &_SNn);
    tree->SetBranchAddress("CLieta", &_SNieta);
    tree->SetBranchAddress("CLiphi", &_SNiphi);
    tree->SetBranchAddress("CLlayer", &_SNlayer);
    tree->SetBranchAddress("CLe", &_SNe);
    tree->GetEntry(it->second.second);
    assert((_SNrun==event.getMCEventInfo()->overlayrun())&&(_SNevent==event.getMCEventInfo()->overlayevtid()));
    f.Close();
  }

  // Calculate MET
  assert(CaloGeometryManager::get_instance());
  const map<int, CELLXYZ_STRUCT>& calogeometry_map = CaloGeometryManager::get_instance()->getCaloGeometry2005Map();
  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");
  float metx_new=0., mety_new=0., met_new=0., scalarEt_new=0.;
  // loop over all calorimeter cells
  if (PrintSNsup) cout<<"Loop over cells"<<endl;
  for(UInt_t icell=0; icell<cells->NumCells(); ++icell) {
    const TMBCaloCell *cell = cells->GetCell(icell);
    int ilyr = cell->layer();
    float E = cell->E();
    bool normalCell = cell->isNormalCell();
    // only look at positive cells and no CH layers and normal cells, will also remove ICD detector for final MET calculation
    if(E>=0. && ilyr<15 && normalCell) {
      // SN subtraction
      Int_t theInd=-1;
      for (Int_t i=0; i<_SNn; i++) {
	if (_SNieta[i]==cell->ieta() && _SNiphi[i]==cell->iphi() && _SNlayer[i]==cell->layer()) {
	  theInd=i;
	  break;
	}
      }
      if (theInd>=0) {
	if (PrintSNsup) cout<<cell->ieta()<<" "<<cell->iphi()<<" "<<ilyr<<"   "<<E<<" "<<_SNe[theInd]<<" "<<(E-_SNe[theInd])<<endl;
	E-=_SNe[theInd];
      } else {
	if (PrintSNsup) cout<<cell->ieta()<<" "<<cell->iphi()<<" "<<ilyr<<"   "<<E<<" --"<<endl;
      }
      //
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
	if(ilyr!=9) {
	  metx_new -= px_cell;
	  mety_new -= py_cell;
	  scalarEt_new += pT_cell;
	}
      }
    }
  }
  met_new = sqrt(metx_new*metx_new + mety_new*mety_new);
  CAFMet m(metx_new, mety_new, met_new, scalarEt_new);

  return m;

}

ClassImp(ZNuNuAnalysis)
