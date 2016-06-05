#include "ZNuNuAnalysis.hpp"
#include "histograms.hpp"
#include "PParameterReader.hpp"
#include "WZ_Utils.hpp"

#include <TFile.h>
#include <TObject.h>
#include <TString.h>
#include <iostream>
#include <vector>

using namespace std;

// Constructor
ZNuNuAnalysis::ZNuNuAnalysis(TString parameter_filename, TRandom3* dummy) {

  // Read other control flags
  ReadParameters(parameter_filename);

  // recoil smear
  _recoilsmear = new RecoilSmear(parameter_filename, _histos, dummy);

  // histograms
  _histos.add(ZNuNuCand_Hist);
  _histos.add(ZNuNuCand_Hist_Profile);
  
  // clone some histograms for Junjie's comparison plots
  // per bins of: UT        (with suffix _bin_<N>), 
  //              true Z Pt (with suffix _genZPt_bin_<N>) 
  const string _histos_name[]={ 
    "ZNuNu_genZPt_Cuts",
    "ZNuNu_genZPhi_Cuts",
    "ZNuNu_genVtxZ_Cuts",
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

    _histos.clone(_histos_name[ihist].c_str(), 10, "_genZPhi_bin");
    _histos.clone(_histos_name[ihist].c_str(), 10, "_UPhi_bin");
    _histos.clone(_histos_name[ihist].c_str(), 10, "_lumi_bin");
    _histos.clone(_histos_name[ihist].c_str(), 10, "_zbset_bin");
  }

  // random number generator
  _random = new TRandom3(0);
}

// read parameters
void ZNuNuAnalysis::ReadParameters(TString parameter_filename) {
  
  PParameterReader parm(parameter_filename.Data());  
  _debug = parm.GetBool("debug", kFALSE);  
  
  // get cuts for MC  neutrions for hadronic recoil transverse energy flow studies 
  _NuLoose_nMin   = parm.GetInt("ZNuNu_NuLoose_nMin",      2);       // require >=2 loose neutrionos
  _NuLoose_EtaMax = parm.GetDouble("ZNuNu_NuLoose_EtaMax", 1000.0);  // no cut
  _NuLoose_PtMin  = parm.GetDouble("ZNuNu_NuLoose_PtMin",  0.0);     // no cut
  _NuTight_nMin   = parm.GetInt("ZNuNu_NuTight_nMin",      0);       // no cut
  _NuTight_EtaMax = parm.GetDouble("ZNuNu_NuTight_EtaMax", 1000.0);  // no cut
  _NuTight_PtMin  = parm.GetDouble("ZNuNu_NuTight_PtMin",  0.0);     // no cut
  _UtCutMin       = parm.GetDouble("ZNuNu_UtCutMin",       0.0);     // no cut
  _UtCutMax       = parm.GetDouble("ZNuNu_UtCutMax",       10000.0); // no cut
  _SETCutMin      = parm.GetDouble("ZNuNu_SETCutMin",      0.0);     // no cut
  _SETCutMax      = parm.GetDouble("ZNuNu_SETCutMax",      10000.0); // no cut
  if(( _NuTight_PtMin < _NuLoose_PtMin ) || 
     ( _NuTight_EtaMax > _NuLoose_EtaMax )) {
    cerr << "ZNuNuAnalysis: Wrong specification of Loose and Tight cuts!!!" << endl
	 << "               pT(Loose nu)>=" << _NuLoose_PtMin 
	 << " GeV, |eta(Loose nu)|<" << _NuLoose_EtaMax << endl
	 << "               pT(Tight nu)>=" << _NuTight_PtMin 
	 << " GeV, |eta(Tight nu)|<" << _NuTight_EtaMax << endl;
    throw;
  }

  // output file
  _znunufilename = parm.GetChar("output_file_znunu", "result_znunu.root");

  // dump smeared hadronic recoil and generated Z info to an ASCII file
  _dumpRecoilInfo = parm.GetBool("ZNuNu_dumpRecoilInfo", kFALSE);
  string _dumpRecoilFile = parm.GetChar("ZNuNu_dumpRecoilFile", "znunu_recoil_dump.txt");
  if(_dumpRecoilInfo) {
    _znunu_out_recoil_txt = new fstream(_dumpRecoilFile.c_str(), std::ios::out);
    if(_znunu_out_recoil_txt) {
      _znunu_out_recoil_txt->flags( ios::right | ios::scientific );
      (*_znunu_out_recoil_txt) << setw(15) << "gen.Z.Px" 
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
			       << setw(16) << "Tot.Lumi" 
			       << setw(16) << "Tot.ZBSET" 
			       << endl;
    }
  } else _znunu_out_recoil_txt=NULL;
}

// Analyze an event
void ZNuNuAnalysis::analyzeEvent(PMCSEvent& pmcsevent, int nLooseNeutrinos, 
				 int nTightNeutrinos, TRandom3 *dummy) {

  // get Z boson information
  PMCSParticle ZBoson = pmcsevent.GetWZBoson();
  
  // generator-level met and recoil system information
  PMCSRecoil recoil_gen = pmcsevent.GetRecoil();

  // smear recoil system
  PMCSRecoil recoil_smear = _recoilsmear->SmearRecoil(recoil_gen, dummy);

  // met
  PMCSMet met_smear = PMCSMet(-recoil_smear.Recoilx(),-recoil_smear.Recoily()); 

  double ZPt_true = ZBoson.ppt();
  double ZPhi_true = ZBoson.phi();
  double VtxZ_true = pmcsevent.GetVtx().vtxz();
  double recoilPt = recoil_smear.Recoil();
  double recoilPx = recoil_smear.Recoilx();
  double recoilPy = recoil_smear.Recoily();
  double recoilPhi = recoil_smear.RecoilPhi();
  double scalarEt = _recoilsmear->scalarEt();

  // recoil system vector
  TVector2 recoil_vect(recoilPx, recoilPy);
  TVector2 recoil_vect_gen(-ZBoson.ppx(), -ZBoson.ppy());
  double recoilPx_true = recoil_vect_gen.Px();
  double recoilPy_true = recoil_vect_gen.Py();
  double recoilPt_true = recoil_vect_gen.Mod();
  double recoilPhi_true = kinem::phi(recoilPx_true, recoilPy_true);

   double luminosity = _recoilsmear->GetLumi();
  double zbset = _recoilsmear->scalarEt_ZB_NoScale();
  // require a combination of "Loose" and "Tight" neutrinos that fulfill 
  // user specified cuts on PT and ETA
  bool kinem_cuts_ok = false;
  if(nLooseNeutrinos>=_NuLoose_nMin &&
     nTightNeutrinos>=_NuTight_nMin &&
     recoilPt>=_UtCutMin            &&
     recoilPt<_UtCutMax             &&
     scalarEt>=_SETCutMin           &&
     scalarEt<_SETCutMax              ) kinem_cuts_ok=true;
  if(!kinem_cuts_ok) return;

   // define two responses: one as the projection along generator level axis
  // this value can be negative, the other one is just the ratio of the magnitude
  // of the reconstructed recoil system vs true pT
  double recoilPtResp    = recoilPt/recoilPt_true;
  double recoilPtRespPrj = recoil_vect*recoil_vect_gen.Unit()/recoilPt_true;
  double recoilPtResol   = 1.0-recoilPtResp;
  double phi_trueZ_Recoil = kinem::delta_phi(recoilPhi,ZPhi_true);

  int ZPt_true_bin = wz_utils::pTee_Eta_Bin(ZPt_true);
  char sn[15]; sprintf(sn, "_genZPt_bin_%d", ZPt_true_bin);
  
  int Ut_bin = wz_utils::pTee_Eta_Bin(recoilPt);
  char sn_smear[10];  sprintf(sn_smear, "_bin_%d", Ut_bin);
  
  int zbset_bin = wz_utils::pTee_Eta_Bin(TMath::Sqrt(zbset));
  char sn_zbset[15]; sprintf(sn_zbset, "_zbset_bin_%d", zbset_bin);

  int lumi_bin = 0;
  if(luminosity > 2 && luminosity<=3) lumi_bin = 1;
  if(luminosity > 3 && luminosity<=4) lumi_bin = 2;
  if(luminosity > 4 && luminosity<=5) lumi_bin = 3;
  if(luminosity > 5 && luminosity<=6) lumi_bin = 4;
  if(luminosity > 6 && luminosity<=8) lumi_bin = 5;
  if(luminosity > 8) lumi_bin = 6;
  char sn_lumi[15]; sprintf(sn_lumi, "_lumi_bin_%d", lumi_bin);


  int truephi_bin = 0;
  if(ZPhi_true > 1.0 && ZPhi_true <=2.0) truephi_bin = 1;
  if(ZPhi_true > 2.0 && ZPhi_true <=3.0) truephi_bin = 2;
  if(ZPhi_true > 3.0 && ZPhi_true <=4.0) truephi_bin = 3;
  if(ZPhi_true > 4.0 && ZPhi_true <=5.0) truephi_bin = 4;
  if(ZPhi_true > 5.0 && ZPhi_true <=6.0) truephi_bin = 5;
  if(ZPhi_true >6.0) truephi_bin = 6;

  //  if(! (ZPhi_true >= 3.0) ) return;
 
  char sn_truephi[15]; sprintf(sn_truephi, "_genZPhi_bin_%d", truephi_bin);

  int recophi_bin = 0;
  if(recoilPhi > 1.0 && recoilPhi <=2.0) recophi_bin = 1;
  if(recoilPhi > 2.0 && recoilPhi <=3.0) recophi_bin = 2;
  if(recoilPhi > 3.0 && recoilPhi <=4.0) recophi_bin = 3;
  if(recoilPhi > 4.0 && recoilPhi <=5.0) recophi_bin = 4;
  if(recoilPhi > 5.0 && recoilPhi <=6.0) recophi_bin = 5;
  if(recoilPhi >6.0) recophi_bin = 6;

  //  if(!(recoilPhi > 4.0 && recoilPhi <=5.0)) return;

  char sn_recophi[15]; sprintf(sn_recophi, "_UPhi_bin_%d", recophi_bin);


  // fill recoil pT, pX, pY and phi    
  _histos.Fill1D("ZNuNu_genZPt_Cuts", ZPt_true);
  _histos.Fill1D("ZNuNu_genZPhi_Cuts", TVector2::Phi_0_2pi(ZPhi_true));
  _histos.Fill1D("ZNuNu_genVtxZ_Cuts", VtxZ_true);
  _histos.Fill1D("ZNuNu_RecoilPt_Cuts", recoilPt);
  _histos.Fill1D("ZNuNu_RecoilPx_Cuts", recoilPx);
  _histos.Fill1D("ZNuNu_RecoilPy_Cuts", recoilPy);
  _histos.Fill1D("ZNuNu_RecoilPhi_Cuts", TVector2::Phi_0_2pi(recoilPhi));
  _histos.Fill1D("ZNuNu_RecoilResolution_Cuts", recoilPtResol);
  _histos.Fill1D("ZNuNu_DeltaPhi_genZ_Recoil_Cuts", phi_trueZ_Recoil);
  _histos.Fill1D("ZNuNu_Met_Cuts", met_smear.met() );
  _histos.Fill1D("ZNuNu_MetPhi_Cuts", TVector2::Phi_0_2pi(met_smear.metphi()) );
  _histos.Fill1D("ZNuNu_MetX_Cuts", met_smear.metx() );
  _histos.Fill1D("ZNuNu_MetY_Cuts", met_smear.mety() );
  _histos.Fill1D("ZNuNu_ScalarEt_Cuts", scalarEt );
  
  // fill response profile
  _histos.FillProfile("ZNuNu_RecoilResponse_V_RecoilPt_Cuts", recoilPt, recoilPtResp);
  _histos.FillProfile("ZNuNu_RecoilResponse_V_genZPt_Cuts", ZPt_true, recoilPtResp);
  _histos.FillProfile("ZNuNu_RecoilResponseProjection_V_RecoilPt_Cuts", recoilPt, recoilPtRespPrj);
  _histos.FillProfile("ZNuNu_RecoilResponseProjection_V_genZPt_Cuts", ZPt_true, recoilPtRespPrj);

  _histos.FillProfile("ZNuNu_RecoilResponse_V_RecoilPhi_Cuts", TVector2::Phi_0_2pi(recoilPhi), recoilPtResp);
  _histos.FillProfile("ZNuNu_RecoilResponse_V_genZPhi_Cuts", TVector2::Phi_0_2pi(ZPhi_true), recoilPtResp);
  _histos.FillProfile("ZNuNu_RecoilResponse_V_lumi_Cuts", luminosity, recoilPtResp);
  _histos.FillProfile("ZNuNu_RecoilResponse_V_zbset_Cuts", TMath::Sqrt(zbset), recoilPtResp);

  
  if(Ut_bin >= 0) {
    _histos.Fill1D(string("ZNuNu_genZPt_Cuts")+sn_smear, ZPt_true);
    _histos.Fill1D(string("ZNuNu_genZPhi_Cuts")+sn_smear, TVector2::Phi_0_2pi(ZPhi_true));
    _histos.Fill1D(string("ZNuNu_genVtxZ_Cuts")+sn_smear, VtxZ_true);
    _histos.Fill1D(string("ZNuNu_RecoilPt_Cuts")+sn_smear, recoilPt);
    _histos.Fill1D(string("ZNuNu_RecoilPx_Cuts")+sn_smear, recoilPx);
    _histos.Fill1D(string("ZNuNu_RecoilPy_Cuts")+sn_smear, recoilPy);
    _histos.Fill1D(string("ZNuNu_RecoilPhi_Cuts")+sn_smear, TVector2::Phi_0_2pi(recoilPhi));
    _histos.Fill1D(string("ZNuNu_RecoilResolution_Cuts")+sn_smear, recoilPtResol);
    _histos.Fill1D(string("ZNuNu_DeltaPhi_genZ_Recoil_Cuts")+sn_smear, phi_trueZ_Recoil);
    _histos.Fill1D(string("ZNuNu_Met_Cuts")+sn_smear, met_smear.met() );
    _histos.Fill1D(string("ZNuNu_MetPhi_Cuts")+sn_smear, TVector2::Phi_0_2pi(met_smear.metphi()) );
    _histos.Fill1D(string("ZNuNu_MetX_Cuts")+sn_smear, met_smear.metx() );
    _histos.Fill1D(string("ZNuNu_MetY_Cuts")+sn_smear, met_smear.mety() );
    _histos.Fill1D(string("ZNuNu_ScalarEt_Cuts")+sn_smear, scalarEt );
  }
  
  if(ZPt_true_bin >= 0) {
    _histos.Fill1D(string("ZNuNu_genZPt_Cuts")+sn, ZPt_true);
    _histos.Fill1D(string("ZNuNu_genZPhi_Cuts")+sn, TVector2::Phi_0_2pi(ZPhi_true));
    _histos.Fill1D(string("ZNuNu_genVtxZ_Cuts")+sn, VtxZ_true);          // gen
    _histos.Fill1D(string("ZNuNu_RecoilPt_Cuts")+sn, recoilPt);
    _histos.Fill1D(string("ZNuNu_RecoilPx_Cuts")+sn, recoilPx);
    _histos.Fill1D(string("ZNuNu_RecoilPy_Cuts")+sn, recoilPy);
    _histos.Fill1D(string("ZNuNu_RecoilPhi_Cuts")+sn, TVector2::Phi_0_2pi(recoilPhi));
    _histos.Fill1D(string("ZNuNu_RecoilResolution_Cuts")+sn, recoilPtResol);
    _histos.Fill1D(string("ZNuNu_DeltaPhi_genZ_Recoil_Cuts")+sn, phi_trueZ_Recoil);
    _histos.Fill1D(string("ZNuNu_Met_Cuts")+sn, met_smear.met() );
    _histos.Fill1D(string("ZNuNu_MetPhi_Cuts")+sn, TVector2::Phi_0_2pi(met_smear.metphi()) );
    _histos.Fill1D(string("ZNuNu_MetX_Cuts")+sn, met_smear.metx() );
    _histos.Fill1D(string("ZNuNu_MetY_Cuts")+sn, met_smear.mety() );
    _histos.Fill1D(string("ZNuNu_ScalarEt_Cuts")+sn, scalarEt );
  }

  if(truephi_bin >= 0) {
    _histos.Fill1D(string("ZNuNu_genZPt_Cuts")+sn_truephi, ZPt_true);
    _histos.Fill1D(string("ZNuNu_genZPhi_Cuts")+sn_truephi, TVector2::Phi_0_2pi(ZPhi_true));
    _histos.Fill1D(string("ZNuNu_genVtxZ_Cuts")+sn_truephi, VtxZ_true);          // gen
    _histos.Fill1D(string("ZNuNu_RecoilPt_Cuts")+sn_truephi, recoilPt);
    _histos.Fill1D(string("ZNuNu_RecoilPx_Cuts")+sn_truephi, recoilPx);
    _histos.Fill1D(string("ZNuNu_RecoilPy_Cuts")+sn_truephi, recoilPy);
    _histos.Fill1D(string("ZNuNu_RecoilPhi_Cuts")+sn_truephi, TVector2::Phi_0_2pi(recoilPhi));
    _histos.Fill1D(string("ZNuNu_RecoilResolution_Cuts")+sn_truephi, recoilPtResol);
    _histos.Fill1D(string("ZNuNu_DeltaPhi_genZ_Recoil_Cuts")+sn_truephi, phi_trueZ_Recoil);
    _histos.Fill1D(string("ZNuNu_Met_Cuts")+sn_truephi, met_smear.met() );
    _histos.Fill1D(string("ZNuNu_MetPhi_Cuts")+sn_truephi, TVector2::Phi_0_2pi(met_smear.metphi()) );
    _histos.Fill1D(string("ZNuNu_MetX_Cuts")+sn_truephi, met_smear.metx() );
    _histos.Fill1D(string("ZNuNu_MetY_Cuts")+sn_truephi, met_smear.mety() );
    _histos.Fill1D(string("ZNuNu_ScalarEt_Cuts")+sn_truephi, scalarEt );
  }

 if(recophi_bin >= 0) {
    _histos.Fill1D(string("ZNuNu_genZPt_Cuts")+sn_recophi, ZPt_true);
    _histos.Fill1D(string("ZNuNu_genZPhi_Cuts")+sn_recophi, TVector2::Phi_0_2pi(ZPhi_true));
    _histos.Fill1D(string("ZNuNu_genVtxZ_Cuts")+sn_recophi, VtxZ_true);          // gen
    _histos.Fill1D(string("ZNuNu_RecoilPt_Cuts")+sn_recophi, recoilPt);
    _histos.Fill1D(string("ZNuNu_RecoilPx_Cuts")+sn_recophi, recoilPx);
    _histos.Fill1D(string("ZNuNu_RecoilPy_Cuts")+sn_recophi, recoilPy);
    _histos.Fill1D(string("ZNuNu_RecoilPhi_Cuts")+sn_recophi, TVector2::Phi_0_2pi(recoilPhi));
    _histos.Fill1D(string("ZNuNu_RecoilResolution_Cuts")+sn_recophi, recoilPtResol);
    _histos.Fill1D(string("ZNuNu_DeltaPhi_genZ_Recoil_Cuts")+sn_recophi, phi_trueZ_Recoil);
    _histos.Fill1D(string("ZNuNu_Met_Cuts")+sn_recophi, met_smear.met() );
    _histos.Fill1D(string("ZNuNu_MetPhi_Cuts")+sn_recophi, TVector2::Phi_0_2pi(met_smear.metphi()) );
    _histos.Fill1D(string("ZNuNu_MetX_Cuts")+sn_recophi, met_smear.metx() );
    _histos.Fill1D(string("ZNuNu_MetY_Cuts")+sn_recophi, met_smear.mety() );
    _histos.Fill1D(string("ZNuNu_ScalarEt_Cuts")+sn_recophi, scalarEt );
  }

 if(lumi_bin >= 0) {
    _histos.Fill1D(string("ZNuNu_genZPt_Cuts")+sn_lumi, ZPt_true);
    _histos.Fill1D(string("ZNuNu_genZPhi_Cuts")+sn_lumi, TVector2::Phi_0_2pi(ZPhi_true));
    _histos.Fill1D(string("ZNuNu_genVtxZ_Cuts")+sn_lumi, VtxZ_true);          // gen
    _histos.Fill1D(string("ZNuNu_RecoilPt_Cuts")+sn_lumi, recoilPt);
    _histos.Fill1D(string("ZNuNu_RecoilPx_Cuts")+sn_lumi, recoilPx);
    _histos.Fill1D(string("ZNuNu_RecoilPy_Cuts")+sn_lumi, recoilPy);
    _histos.Fill1D(string("ZNuNu_RecoilPhi_Cuts")+sn_lumi, TVector2::Phi_0_2pi(recoilPhi));
    _histos.Fill1D(string("ZNuNu_RecoilResolution_Cuts")+sn_lumi, recoilPtResol);
    _histos.Fill1D(string("ZNuNu_DeltaPhi_genZ_Recoil_Cuts")+sn_lumi, phi_trueZ_Recoil);
    _histos.Fill1D(string("ZNuNu_Met_Cuts")+sn_lumi, met_smear.met() );
    _histos.Fill1D(string("ZNuNu_MetPhi_Cuts")+sn_lumi, TVector2::Phi_0_2pi(met_smear.metphi()) );
    _histos.Fill1D(string("ZNuNu_MetX_Cuts")+sn_lumi, met_smear.metx() );
    _histos.Fill1D(string("ZNuNu_MetY_Cuts")+sn_lumi, met_smear.mety() );
    _histos.Fill1D(string("ZNuNu_ScalarEt_Cuts")+sn_lumi, scalarEt );
  }

 if(zbset_bin >= 0) {
    _histos.Fill1D(string("ZNuNu_genZPt_Cuts")+sn_zbset, ZPt_true);
    _histos.Fill1D(string("ZNuNu_genZPhi_Cuts")+sn_zbset, TVector2::Phi_0_2pi(ZPhi_true));
    _histos.Fill1D(string("ZNuNu_genVtxZ_Cuts")+sn_zbset, VtxZ_true);          // gen
    _histos.Fill1D(string("ZNuNu_RecoilPt_Cuts")+sn_zbset, recoilPt);
    _histos.Fill1D(string("ZNuNu_RecoilPx_Cuts")+sn_zbset, recoilPx);
    _histos.Fill1D(string("ZNuNu_RecoilPy_Cuts")+sn_zbset, recoilPy);
    _histos.Fill1D(string("ZNuNu_RecoilPhi_Cuts")+sn_zbset, TVector2::Phi_0_2pi(recoilPhi));
    _histos.Fill1D(string("ZNuNu_RecoilResolution_Cuts")+sn_zbset, recoilPtResol);
    _histos.Fill1D(string("ZNuNu_DeltaPhi_genZ_Recoil_Cuts")+sn_zbset, phi_trueZ_Recoil);
    _histos.Fill1D(string("ZNuNu_Met_Cuts")+sn_zbset, met_smear.met() );
    _histos.Fill1D(string("ZNuNu_MetPhi_Cuts")+sn_zbset, TVector2::Phi_0_2pi(met_smear.metphi()) );
    _histos.Fill1D(string("ZNuNu_MetX_Cuts")+sn_zbset, met_smear.metx() );
    _histos.Fill1D(string("ZNuNu_MetY_Cuts")+sn_zbset, met_smear.mety() );
    _histos.Fill1D(string("ZNuNu_ScalarEt_Cuts")+sn_zbset, scalarEt );
  }




  // Dump measured recoil and generated Z to an ascii file
  // for events that passed kinematical cuts on 2 neutrinos
  // 4-momentum of generated Z (px,py,pz,E) / 4-momentum of generated recoil (px,py,pz,E) / 
  // Transverse momentum of smeared recoil (px,py) / Smeared scalar Et [GeV]
  if(_dumpRecoilInfo && _znunu_out_recoil_txt) {
    (*_znunu_out_recoil_txt) << setw(15) << setprecision(8) << ZBoson.ppx()  << " " 
			     << setw(15) << setprecision(8) << ZBoson.ppy()  << " " 
			     << setw(15) << setprecision(8) << ZBoson.ppz()  << " " 
			     << setw(15) << setprecision(8) << ZBoson.pE()   << " " 
			     << setw(15) << setprecision(8) << -ZBoson.ppx() << " " 
			     << setw(15) << setprecision(8) << -ZBoson.ppy() << " " 
			     << setw(15) << setprecision(8) << -ZBoson.ppz() << " " 
			     << setw(15) << setprecision(8) << ZBoson.pE()   << " " 
			     << setw(15) << setprecision(8) << recoilPx      << " " 
			     << setw(15) << setprecision(8) << recoilPy      << " "
			     << setw(15) << setprecision(8) << scalarEt      <<  " "
			     << setw(15) << setprecision(8) << luminosity      << " "
			     << setw(15) << setprecision(8) << zbset      << endl;
    //<< setw(15) << setprecision(8) << scalarEt      << endl;
  }  
}
ZNuNuAnalysis::~ZNuNuAnalysis () {
}

void ZNuNuAnalysis::jobSummary() {
  _histos.save(_znunufilename);
  if(_dumpRecoilInfo && _znunu_out_recoil_txt) _znunu_out_recoil_txt->close();
}


