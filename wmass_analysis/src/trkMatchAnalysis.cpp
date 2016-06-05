// $Id: trkMatchAnalysis.cpp,v 1.1 2010/10/21 00:52:12 rclsa Exp $
//
// The purpose of these methods is to study Track Match Efficiency
// Some definitions are needed:
//  . I use tag and probe method and, for Full MC, also the true information
//  . For the data, we still have to save to background.
//  . The trigger requirement is NOT asked in case of data.
//  . The histograms saved are:
//     - NoTrkMatch : No track requirement imposed.
//     - Loose spatial track match: Prob > 0.01
//     - Tight spatial track match: Prob > 0.01 && SMT hit && PtTrack > 10 GeV

#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_analysis/ZAnalysis.hpp"
#include "wmass_analysis/histograms.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "wmass_util/WZ_Utils.hpp"
#include "tmb_tree/TMBCaloCell.hpp"
#include "wmass_util/CaloGeometryManager.hpp"
#include "tmb_tree/TMBMCvtx.hpp"
#include "TLorentzVector.h"

using namespace std;
using namespace cafe;

void ZAnalysis::trkMatchEfficiencyStudies(Event& event, std::vector<CAFEMObj*> emobjs, std::vector<CAFEMObj*> probe_emobjs, 
					  CAFMet &rawmet, float vtx[3], bool *pass_trigger) {

  // Run over tags and probes

  for(int iem=0; iem<emobjs.size(); ++iem){

    for(int iem_probe=0; iem_probe<probe_emobjs.size(); ++iem_probe){
      
      // Construct a tentative Z
      CAFZCand zcand;
      zcand = CAFZCand(emobjs[iem], probe_emobjs[iem_probe], &rawmet, vtx, true);	 
      
      // Get some physical information for cuts
      double mass = zcand.Mass();   // mass calculated using cal+tracker information
      double recoilPt = zcand.MagRecoil();

      // Get Scalar ET
      double zScalarEt = 0;
      double ScalarEt_Evt = 0;
      ScalarEt_Evt = rawmet.scalarEt();
      
      // Discount the Scalar ET from the EMObjs
      float cntrib1=0;
      float cntrib2=0;
      emobjs[iem]->getRawElecVectorFromCells(vtx,&cntrib1);
      probe_emobjs[iem_probe]->getRawElecVectorFromCells(vtx,&cntrib2);
      double ScalarEt_EMObjs = cntrib1 + cntrib2;
      zScalarEt = ScalarEt_Evt - ScalarEt_EMObjs;

      // Define the cuts. Trigger just for the tag!
      Bool_t cut = (recoilPt < _ZUtCut && recoilPt >= _ZUtCut_lower &&
		    mass>_ZMassCut1 && mass<_ZMassCut2 &&
		    emobjs[iem]->Pt()>_ElecPtCut1_lo &&  probe_emobjs[iem_probe]->Pt()>_ElecPtCut2_lo &&
		    emobjs[iem]->Pt()<_ElecPtCut1_hi &&  probe_emobjs[iem_probe]->Pt()<_ElecPtCut2_hi &&
		    emobjs[iem]->has_good_spatial_track_match() &&
		    zScalarEt>_ZScalarEtCut_lower && zScalarEt<_ZScalarEtCut &&
		    pass_trigger[iem] &&
		    // Now the probe cuts
		    probe_emobjs[iem_probe]->PassHMx(12., 20.) &&
		    probe_emobjs[iem_probe]->PassEMFracIso(0.9, 0.15) &&
		    probe_emobjs[iem_probe]->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2, false));

      Bool_t CCtag = emobjs[iem]->IsCCFid(_DetEtaCC);
      Bool_t ECtag = emobjs[iem]->IsECFid(_DetEtaEC1, _DetEtaEC2);
      Bool_t CCprobe = probe_emobjs[iem_probe]->IsCCFid(_DetEtaCC, false);
      Bool_t ECprobe = probe_emobjs[iem_probe]->IsECFid(_DetEtaEC1, _DetEtaEC2);

      // Separate types, my own version which is different from the one used in this code
      int type;
      if (CCtag && CCprobe) type=0;
      if (CCtag && ECprobe) type=1;
      if (ECtag && CCprobe) type=2;
      if (ECtag && ECprobe) type=3;

      // Now the variables we want to make the hists from
      TVector3 tag_vector = emobjs[iem]->vect3();
      double tag_eta = tag_vector.Eta();
      double tag_caleta = emobjs[iem]->CalDetectorEta();
      double tag_charge = emobjs[iem]->charge();
      TVector3 probe_vector = probe_emobjs[iem_probe]->vect3();
      double probe_eta = probe_vector.Eta();
      double probe_caleta = probe_emobjs[iem_probe]->CalDetectorEta();
      double probe_pT  = probe_vector.Pt();
      double probe_charge = probe_emobjs[iem_probe]->charge();
      double vtxz     = vtx[2];

      // To avoid tag and probe biasing
      Bool_t probe_cut = (!((probe_caleta > 1.4) && (vtxz > 30.)) && !((probe_caleta < -1.4) && (vtxz < -30.))) || !_fiducialForwardElectron;
      Bool_t tag_cut = (!((tag_caleta > 1.4) && (vtxz > 30.)) && !((tag_caleta < -1.4) && (vtxz < -30.))) || !_fiducialForwardElectron;

      TVector2 probe_trans = probe_emobjs[iem_probe]->vect2();
      TVector2 recoil_trans = zcand.GetRecoil();
	
      double upara = recoil_trans * probe_trans.Unit();
      double boson_pz = zcand.Pz();
      
      if(cut && tag_cut && probe_cut && (CCtag || ECtag)) {

	TString histname;

	// Fill NoTrkMatch hists     
	histname.Form("ZCandTrkMatchEff_NoTrkMatch_eta_%d", type);
	_histos.Fill1D(histname.Data(), probe_eta);
	histname.Form("ZCandTrkMatchEff_NoTrkMatch_caleta_%d", type);
	_histos.Fill1D(histname.Data(), probe_caleta);
	histname.Form("ZCandTrkMatchEff_NoTrkMatch_pT_%d", type);
	_histos.Fill1D(histname.Data(), probe_pT);
	histname.Form("ZCandTrkMatchEff_NoTrkMatch_vtxz_%d", type);
	_histos.Fill1D(histname.Data(), vtxz);
	histname.Form("ZCandTrkMatchEff_NoTrkMatch_upara_%d", type);
	_histos.Fill1D(histname.Data(), upara);

	histname.Form("ZCandTrkMatchEff_NoTrkMatch_eta_pT_%d", type);
	_histos.Fill2D(histname.Data(), probe_eta, probe_pT);
	histname.Form("ZCandTrkMatchEff_NoTrkMatch_eta_vtxz_%d", type);
	_histos.Fill2D(histname.Data(), probe_eta, vtxz);
	histname.Form("ZCandTrkMatchEff_NoTrkMatch_caleta_pT_%d", type);
	_histos.Fill2D(histname.Data(), probe_caleta, probe_pT);
	histname.Form("ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz_%d", type);
	_histos.Fill2D(histname.Data(), probe_caleta, vtxz);
	if (probe_charge < 0) {
	  histname.Form("ZCandTrkMatchEff_NoTrkMatch_etam_vtxz_%d", type);
	  _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	  if (tag_charge > 0) {
	    histname.Form("ZCandTrkMatchEff_NoTrkMatch_etam_etap_%d", type);
	    _histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	  }
	} else if (probe_charge > 0) {
	  histname.Form("ZCandTrkMatchEff_NoTrkMatch_etap_vtxz_%d", type);
	  _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	  if (tag_charge > 0) {
	    histname.Form("ZCandTrkMatchEff_NoTrkMatch_etap_etam_%d", type);
	    _histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	  }
	}
	histname.Form("ZCandTrkMatchEff_NoTrkMatch_upara_pz_%d", type);
	_histos.Fill2D(histname.Data(), upara, boson_pz);

	histname.Form("ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse_%d", type);
	_histos.Fill2D(histname.Data(), vtxz, probe_eta);

	if(type%2==0) {
	  _histos.Fill1D("ZCandTrkMatchEff_NoTrkMatch_eta_4", probe_eta);
	  _histos.Fill1D("ZCandTrkMatchEff_NoTrkMatch_caleta_4", probe_caleta);
	  _histos.Fill1D("ZCandTrkMatchEff_NoTrkMatch_pT_4", probe_pT);
	  _histos.Fill1D("ZCandTrkMatchEff_NoTrkMatch_vtxz_4", vtxz);
	  _histos.Fill1D("ZCandTrkMatchEff_NoTrkMatch_upara_4", upara);
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_eta_pT_4", probe_eta, probe_pT);
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_eta_vtxz_4", probe_eta, vtxz);
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_caleta_pT_4", probe_caleta, probe_pT);
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz_4", probe_caleta, vtxz);
	  if (probe_charge < 0) {
	    _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_etam_vtxz_4", probe_eta, vtxz);
	    if (tag_charge > 0) {
	      _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_etam_etap_4", tag_eta, probe_eta);
	    }
	  } else if (probe_charge > 0) {
	    _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_etap_vtxz_4", probe_eta, vtxz);
	    if (tag_charge > 0) {
	      _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_etap_etam_4", tag_eta, probe_eta);
	    }
	  }
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_upara_pz_4", upara, boson_pz);
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse_4", vtxz, probe_eta);
	} else {
	  _histos.Fill1D("ZCandTrkMatchEff_NoTrkMatch_eta_5", probe_eta);
	  _histos.Fill1D("ZCandTrkMatchEff_NoTrkMatch_caleta_5", probe_caleta);
	  _histos.Fill1D("ZCandTrkMatchEff_NoTrkMatch_pT_5", probe_pT);
	  _histos.Fill1D("ZCandTrkMatchEff_NoTrkMatch_vtxz_5", vtxz);
	  _histos.Fill1D("ZCandTrkMatchEff_NoTrkMatch_upara_5", upara);
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_eta_pT_5", probe_eta, probe_pT);
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_eta_vtxz_5", probe_eta, vtxz);
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_caleta_pT_5", probe_caleta, probe_pT);
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz_5", probe_caleta, vtxz);
	  if (probe_charge < 0) {
	    _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_etam_vtxz_5", probe_eta, vtxz);
	    if (tag_charge > 0) {
	      _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_etam_etap_5", tag_eta, probe_eta);
	    }
	  } else if (probe_charge > 0) {
	    _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_etap_vtxz_5", probe_eta, vtxz);
	    if (tag_charge > 0) {
	      _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_etap_etam_5", tag_eta, probe_eta);
	    }
	  }
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_upara_pz_5", upara, boson_pz);
	  _histos.Fill2D("ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse_5", vtxz, probe_eta);
	}

	// The track phi fiducial just asks for a loose track, so we can demand it here
	if(probe_emobjs[iem_probe]->has_spatial_track_match() && probe_emobjs[iem_probe]->is_in_TrkPhiFid()) {
	  
	  // Fill LooseTrkMatch hists
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_eta_%d", type);
	  _histos.Fill1D(histname.Data(), probe_eta);
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_caleta_%d", type);
	  _histos.Fill1D(histname.Data(), probe_caleta);
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_pT_%d", type);
	  _histos.Fill1D(histname.Data(), probe_pT);
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_vtxz_%d", type);
	  _histos.Fill1D(histname.Data(), vtxz);
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_upara_%d", type);
	  _histos.Fill1D(histname.Data(), upara);
	  
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_eta_pT_%d", type);
	  _histos.Fill2D(histname.Data(), probe_eta, probe_pT);
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_%d", type);
	  _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_%d", type);
	  _histos.Fill2D(histname.Data(), probe_caleta, probe_pT);
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_%d", type);
	  _histos.Fill2D(histname.Data(), probe_caleta, vtxz);
	  if (probe_charge < 0) {
	    histname.Form("ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_%d", type);
	    _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	    if (tag_charge > 0) {
	      histname.Form("ZCandTrkMatchEff_LooseTrkMatch_etam_etap_%d", type);
	      _histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	    }
	  } else if (probe_charge > 0) {
	    histname.Form("ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_%d", type);
	    _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	    if (tag_charge > 0) {
	      histname.Form("ZCandTrkMatchEff_LooseTrkMatch_etap_etam_%d", type);
	      _histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	    }
	  }
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_upara_pz_%d", type);
	  _histos.Fill2D(histname.Data(), upara, boson_pz);
	  
	  histname.Form("ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_%d", type);
	  _histos.Fill2D(histname.Data(), vtxz, probe_eta);
	  
	  if(type%2==0) {
	    _histos.Fill1D("ZCandTrkMatchEff_LooseTrkMatch_eta_4", probe_eta);
	    _histos.Fill1D("ZCandTrkMatchEff_LooseTrkMatch_caleta_4", probe_caleta);
	    _histos.Fill1D("ZCandTrkMatchEff_LooseTrkMatch_pT_4", probe_pT);
	    _histos.Fill1D("ZCandTrkMatchEff_LooseTrkMatch_vtxz_4", vtxz);
	    _histos.Fill1D("ZCandTrkMatchEff_LooseTrkMatch_upara_4", upara);
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_eta_pT_4", probe_eta, probe_pT);
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_4", probe_eta, vtxz);
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_4", probe_caleta, probe_pT);
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_4", probe_caleta, vtxz);
	    if (probe_charge < 0) {
	      _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_4", probe_eta, vtxz);
	      if (tag_charge > 0) {
		_histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_etam_etap_4", tag_eta, probe_eta);
	      }
	    } else if (probe_charge > 0) {
	      _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_4", probe_eta, vtxz);
	      if (tag_charge > 0) {
		_histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_etap_etam_4", tag_eta, probe_eta);
	      }
	    }
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_upara_pz_4", upara, boson_pz);
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_4", vtxz, probe_eta);
	  } else {
	    _histos.Fill1D("ZCandTrkMatchEff_LooseTrkMatch_eta_5", probe_eta);
	    _histos.Fill1D("ZCandTrkMatchEff_LooseTrkMatch_caleta_5", probe_caleta);
	    _histos.Fill1D("ZCandTrkMatchEff_LooseTrkMatch_pT_5", probe_pT);
	    _histos.Fill1D("ZCandTrkMatchEff_LooseTrkMatch_vtxz_5", vtxz);
	    _histos.Fill1D("ZCandTrkMatchEff_LooseTrkMatch_upara_5", upara);
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_eta_pT_5", probe_eta, probe_pT);
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_5", probe_eta, vtxz);
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_5", probe_caleta, probe_pT);
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_5", probe_caleta, vtxz);
	    if (probe_charge < 0) {
	      _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_5", probe_eta, vtxz);
	      if (tag_charge > 0) {
		_histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_etam_etap_5", tag_eta, probe_eta);
	      }
	    } else if (probe_charge > 0) {
	      _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_5", probe_eta, vtxz);
	      if (tag_charge > 0) {
		_histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_etap_etam_5", tag_eta, probe_eta);
	      }
	    }
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_upara_pz_5", upara, boson_pz);
	    _histos.Fill2D("ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_5", vtxz, probe_eta);
	  }
	  
	  if(probe_emobjs[iem_probe]->has_good_spatial_track_match()) {
	    
	    // Fill TigthTrkMatch hists
	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_eta_%d", type);
	    _histos.Fill1D(histname.Data(), probe_eta);
	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_caleta_%d", type);
	    _histos.Fill1D(histname.Data(), probe_caleta);
	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_pT_%d", type);
	    _histos.Fill1D(histname.Data(), probe_pT);
	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_vtxz_%d", type);
	    _histos.Fill1D(histname.Data(), vtxz);
	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_upara_%d", type);
	    _histos.Fill1D(histname.Data(), upara);
	    
	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_eta_pT_%d", type);
	    _histos.Fill2D(histname.Data(), probe_eta, probe_pT);
	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_%d", type);
	    _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_caleta_pT_%d", type);
	    _histos.Fill2D(histname.Data(), probe_caleta, probe_pT);
	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz_%d", type);
	    _histos.Fill2D(histname.Data(), probe_caleta, vtxz);
	    if (probe_charge < 0) {
	      histname.Form("ZCandTrkMatchEff_TightTrkMatch_etam_vtxz_%d", type);
	      _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	      if (tag_charge > 0) {
		histname.Form("ZCandTrkMatchEff_TightTrkMatch_etam_etap_%d", type);
		_histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	      }
	    } else if (probe_charge > 0) {
	      histname.Form("ZCandTrkMatchEff_TightTrkMatch_etap_vtxz_%d", type);
	      _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	      if (tag_charge > 0) {
		histname.Form("ZCandTrkMatchEff_TightTrkMatch_etap_etam_%d", type);
		_histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	      }
	    }
	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_upara_pz_%d", type);
	    _histos.Fill2D(histname.Data(), upara, boson_pz);

	    histname.Form("ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse_%d", type);
	    _histos.Fill2D(histname.Data(), vtxz, probe_eta);
	    	    
	    if(type%2==0) {
	      _histos.Fill1D("ZCandTrkMatchEff_TightTrkMatch_eta_4", probe_eta);
	      _histos.Fill1D("ZCandTrkMatchEff_TightTrkMatch_caleta_4", probe_caleta);
	      _histos.Fill1D("ZCandTrkMatchEff_TightTrkMatch_pT_4", probe_pT);
	      _histos.Fill1D("ZCandTrkMatchEff_TightTrkMatch_vtxz_4", vtxz);
	      _histos.Fill1D("ZCandTrkMatchEff_TightTrkMatch_upara_4", upara);
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_eta_pT_4", probe_eta, probe_pT);
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_4", probe_eta, vtxz);
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_caleta_pT_4", probe_caleta, probe_pT);
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz_4", probe_caleta, vtxz);
	      if (probe_charge < 0) {
		_histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_etam_vtxz_4", probe_eta, vtxz);
		if (tag_charge > 0) {
		  _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_etam_etap_4", tag_eta, probe_eta);
		}
	      } else if (probe_charge > 0) {
		_histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_etap_vtxz_4", probe_eta, vtxz);
		if (tag_charge > 0) {
		  _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_etap_etam_4", tag_eta, probe_eta);
		}
	      }
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_upara_pz_4", upara, boson_pz);
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse_4", vtxz, probe_eta);
	    } else {
	      _histos.Fill1D("ZCandTrkMatchEff_TightTrkMatch_eta_5", probe_eta);
	      _histos.Fill1D("ZCandTrkMatchEff_TightTrkMatch_caleta_5", probe_caleta);
	      _histos.Fill1D("ZCandTrkMatchEff_TightTrkMatch_pT_5", probe_pT);
	      _histos.Fill1D("ZCandTrkMatchEff_TightTrkMatch_vtxz_5", vtxz);
	      _histos.Fill1D("ZCandTrkMatchEff_TightTrkMatch_upara_5", upara);
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_eta_pT_5", probe_eta, probe_pT);
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_5", probe_eta, vtxz);
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_caleta_pT_5", probe_caleta, probe_pT);
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz_5", probe_caleta, vtxz);
	      if (probe_charge < 0) {
		_histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_etam_vtxz_5", probe_eta, vtxz);
		if (tag_charge > 0) {
		  _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_etam_etap_5", tag_eta, probe_eta);
		}
	      } else if (probe_charge > 0) {
		_histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_etap_vtxz_5", probe_eta, vtxz);
		if (tag_charge > 0) {
		  _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_etap_etam_5", tag_eta, probe_eta);
		}
	      }
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_upara_pz_5", upara, boson_pz);
	      _histos.Fill2D("ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse_5", vtxz, probe_eta);
	    }

	  } // End tight electron
	}   // End loose electron
      }     // End selection
    }       // End probe loop
  }         // End tag loop
}

void ZAnalysis::trueTrkMatchEfficiencyStudies(Event& event, std::vector<CAFEMObj*> probe_emobjs, 
					      CAFMet &rawmet, float vtx[3]) {

  // Run over tags and probes

  for(int iem=0; iem<probe_emobjs.size(); ++iem){

    for(int iem_probe=0; iem_probe<probe_emobjs.size(); ++iem_probe){
      
      // Construct a tentative Z
      CAFZCand zcand;
      zcand = CAFZCand(probe_emobjs[iem], probe_emobjs[iem_probe], &rawmet, vtx, true);	 
      
      // Get some physical information for cuts
      double mass = zcand.Mass();   // mass calculated using cal+tracker information
      double recoilPt = zcand.MagRecoil();

      // Get Scalar ET
      double zScalarEt = 0;
      double ScalarEt_Evt = 0;
      ScalarEt_Evt = rawmet.scalarEt();
      
      // Discount the Scalar ET from the EMObjs
      float cntrib1=0;
      float cntrib2=0;
      probe_emobjs[iem]->getRawElecVectorFromCells(vtx,&cntrib1);
      probe_emobjs[iem_probe]->getRawElecVectorFromCells(vtx,&cntrib2);
      double ScalarEt_EMObjs = cntrib1 + cntrib2;
      zScalarEt = ScalarEt_Evt - ScalarEt_EMObjs;

      // Define the cuts. Trigger just for the tag!
      Bool_t cut = (recoilPt < _ZUtCut && recoilPt >= _ZUtCut_lower &&
		    mass>_ZMassCut1 && mass<_ZMassCut2 &&
		    probe_emobjs[iem]->Pt()>_ElecPtCut1_lo &&  probe_emobjs[iem_probe]->Pt()>_ElecPtCut2_lo &&
		    probe_emobjs[iem]->Pt()<_ElecPtCut1_hi &&  probe_emobjs[iem_probe]->Pt()<_ElecPtCut2_hi &&
		    zScalarEt>_ZScalarEtCut_lower && zScalarEt<_ZScalarEtCut &&
		    // Now the probe cuts
		    probe_emobjs[iem]->PassHMx(12., 20.) &&
		    probe_emobjs[iem]->PassEMFracIso(0.9, 0.15) &&
		    probe_emobjs[iem_probe]->PassHMx(12., 20.) &&
		    probe_emobjs[iem_probe]->PassEMFracIso(0.9, 0.15));

      Bool_t CCtag = probe_emobjs[iem]->IsCCFid(_DetEtaCC, false);
      Bool_t ECtag = probe_emobjs[iem]->IsECFid(_DetEtaEC1, _DetEtaEC2);
      Bool_t CCprobe = probe_emobjs[iem_probe]->IsCCFid(_DetEtaCC, false);
      Bool_t ECprobe = probe_emobjs[iem_probe]->IsECFid(_DetEtaEC1, _DetEtaEC2);

      // Separate types, my own version which is different from the one used in this code
      int type;
      if (CCtag && CCprobe) type=0;
      if (CCtag && ECprobe) type=1;
      if (ECtag && CCprobe) type=2;
      if (ECtag && ECprobe) type=3;

      // Now the variables we want to make the hists from
      TVector3 tag_vector = probe_emobjs[iem]->vect3();
      double tag_eta = tag_vector.Eta();
      double tag_caleta = probe_emobjs[iem]->CalDetectorEta();
      double tag_charge = probe_emobjs[iem]->charge();
      TVector3 probe_vector = probe_emobjs[iem_probe]->vect3();
      double probe_eta = probe_vector.Eta();
      double probe_caleta = probe_emobjs[iem_probe]->CalDetectorEta();
      double probe_pT  = probe_vector.Pt();
      double probe_charge = probe_emobjs[iem_probe]->charge();
      double vtxz     = vtx[2];

      TVector2 probe_trans = probe_emobjs[iem_probe]->vect2();
      TVector2 recoil_trans = zcand.GetRecoil();

      // To avoid tag and probe biasing
      Bool_t probe_cut = (!((probe_caleta > 1.4) && (vtxz > 30.)) && !((probe_caleta < -1.4) && (vtxz < -30.))) || !_fiducialForwardElectron;
      Bool_t tag_cut = (!((tag_caleta > 1.4) && (vtxz > 30.)) && !((tag_caleta < -1.4) && (vtxz < -30.))) || !_fiducialForwardElectron;
	
      double upara = recoil_trans * probe_trans.Unit();
      double boson_pz = zcand.Pz();
      
      if(probe_cut && tag_cut && cut && (CCtag || ECtag) && (CCprobe || ECprobe)) {

	TString histname;

	// Fill NoTrkMatch hists     
	histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_eta_%d", type);
	_histos.Fill1D(histname.Data(), probe_eta);
	histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_%d", type);
	_histos.Fill1D(histname.Data(), probe_caleta);
	histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_pT_%d", type);
	_histos.Fill1D(histname.Data(), probe_pT);
	histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_vtxz_%d", type);
	_histos.Fill1D(histname.Data(), vtxz);
	histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_upara_%d", type);
	_histos.Fill1D(histname.Data(), upara);

	histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT_%d", type);
	_histos.Fill2D(histname.Data(), probe_eta, probe_pT);
	histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz_%d", type);
	_histos.Fill2D(histname.Data(), probe_eta, vtxz);
	histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT_%d", type);
	_histos.Fill2D(histname.Data(), probe_caleta, probe_pT);
	histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz_%d", type);
	_histos.Fill2D(histname.Data(), probe_caleta, vtxz);
	if (probe_charge < 0) {
	  histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz_%d", type);
	  _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	  if (tag_charge > 0) {
	    histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap_%d", type);
	    _histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	  }
	} else if (probe_charge > 0) {
	  histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz_%d", type);
	  _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	  if (tag_charge > 0) {
	    histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam_%d", type);
	    _histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	  }
	}
	histname.Form("ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz_%d", type);
	_histos.Fill2D(histname.Data(), upara, boson_pz);

	if(type%2==0) {
	  _histos.Fill1D("ZCandTrueTrkMatchEff_NoTrkMatch_eta_4", probe_eta);
	  _histos.Fill1D("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_4", probe_caleta);
	  _histos.Fill1D("ZCandTrueTrkMatchEff_NoTrkMatch_pT_4", probe_pT);
	  _histos.Fill1D("ZCandTrueTrkMatchEff_NoTrkMatch_vtxz_4", vtxz);
	  _histos.Fill1D("ZCandTrueTrkMatchEff_NoTrkMatch_upara_4", upara);
	  _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT_4", probe_eta, probe_pT);
	  _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz_4", probe_eta, vtxz);
	  _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT_4", probe_caleta, probe_pT);
	  _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz_4", probe_caleta, vtxz);
	  if (probe_charge < 0) {
	    _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz_4", probe_eta, vtxz);
	    if (tag_charge > 0) {
	      _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap_4", tag_eta, probe_eta);
	    }
	  } else if (probe_charge > 0) {
	    _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz_4", probe_eta, vtxz);
	    if (tag_charge > 0) {
	      _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam_4", tag_eta, probe_eta);
	    }
	  }
	  _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz_4", upara, boson_pz);
	} else {
	  _histos.Fill1D("ZCandTrueTrkMatchEff_NoTrkMatch_eta_5", probe_eta);
	  _histos.Fill1D("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_5", probe_caleta);
	  _histos.Fill1D("ZCandTrueTrkMatchEff_NoTrkMatch_pT_5", probe_pT);
	  _histos.Fill1D("ZCandTrueTrkMatchEff_NoTrkMatch_vtxz_5", vtxz);
	  _histos.Fill1D("ZCandTrueTrkMatchEff_NoTrkMatch_upara_5", upara);
	  _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT_5", probe_eta, probe_pT);
	  _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz_5", probe_eta, vtxz);
	  _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT_5", probe_caleta, probe_pT);
	  _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz_5", probe_caleta, vtxz);
	  if (probe_charge < 0) {
	    _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz_5", probe_eta, vtxz);
	    if (tag_charge > 0) {
	      _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap_5", tag_eta, probe_eta);
	    }
	  } else if (probe_charge > 0) {
	    _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz_5", probe_eta, vtxz);
	    if (tag_charge > 0) {
	      _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam_5", tag_eta, probe_eta);
	    }
	  }
	  _histos.Fill2D("ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz_5", upara, boson_pz);
	}

	// The track phi fiducial just asks for a loose track, so we can demand it here
	if(probe_emobjs[iem_probe]->has_spatial_track_match() && probe_emobjs[iem_probe]->is_in_TrkPhiFid()) {
	  
	  // Fill LooseTrkMatch hists
	  histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_%d", type);
	  _histos.Fill1D(histname.Data(), probe_eta);
	  histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_%d", type);
	  _histos.Fill1D(histname.Data(), probe_caleta);
	  histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_pT_%d", type);
	  _histos.Fill1D(histname.Data(), probe_pT);
	  histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_%d", type);
	  _histos.Fill1D(histname.Data(), vtxz);
	  histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_upara_%d", type);
	  _histos.Fill1D(histname.Data(), upara);
	  
	  histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_%d", type);
	  _histos.Fill2D(histname.Data(), probe_eta, probe_pT);
	  histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_%d", type);
	  _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	  histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_%d", type);
	  _histos.Fill2D(histname.Data(), probe_caleta, probe_pT);
	  histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_%d", type);
	  _histos.Fill2D(histname.Data(), probe_caleta, vtxz);
	  if (probe_charge < 0) {
	    histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_%d", type);
	    _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	    if (tag_charge > 0) {
	      histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_%d", type);
	      _histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	    }
	  } else if (probe_charge > 0) {
	    histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_%d", type);
	    _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	    if (tag_charge > 0) {
	      histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_%d", type);
	      _histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	    }
	  }
	  histname.Form("ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_%d", type);
	  _histos.Fill2D(histname.Data(), upara, boson_pz);
	  	  
	  if(type%2==0) {
	    _histos.Fill1D("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_4", probe_caleta);
	    _histos.Fill1D("ZCandTrueTrkMatchEff_LooseTrkMatch_pT_4", probe_pT);
	    _histos.Fill1D("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_4", probe_eta);
	    _histos.Fill1D("ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_4", vtxz);
	    _histos.Fill1D("ZCandTrueTrkMatchEff_LooseTrkMatch_upara_4", upara);
	    _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_4", probe_eta, probe_pT);
	    _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_4", probe_eta, vtxz);
	    _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_4", probe_caleta, probe_pT);
	    _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_4", probe_caleta, vtxz);
	    if (probe_charge < 0) {
	      _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_4", probe_eta, vtxz);
	      if (tag_charge > 0) {
		_histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_4", tag_eta, probe_eta);
	      }
	    } else if (probe_charge > 0) {
	      _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_4", probe_eta, vtxz);
	      if (tag_charge > 0) {
		_histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_4", tag_eta, probe_eta);
	      }
	    }
	    _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_4", upara, boson_pz);
	  } else {
	    _histos.Fill1D("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_5", probe_eta);
	    _histos.Fill1D("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_5", probe_caleta);
	    _histos.Fill1D("ZCandTrueTrkMatchEff_LooseTrkMatch_pT_5", probe_pT);
	    _histos.Fill1D("ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_5", vtxz);
	    _histos.Fill1D("ZCandTrueTrkMatchEff_LooseTrkMatch_upara_5", upara);
	    _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_5", probe_eta, probe_pT);
	    _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_5", probe_eta, vtxz);
	    _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_5", probe_caleta, probe_pT);
	    _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_5", probe_caleta, vtxz);
	    if (probe_charge < 0) {
	      _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_5", probe_eta, vtxz);
	      if (tag_charge > 0) {
		_histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_5", tag_eta, probe_eta);
	      }
	    } else if (probe_charge > 0) {
	      _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_5", probe_eta, vtxz);
	      if (tag_charge > 0) {
		_histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_5", tag_eta, probe_eta);
	      }
	    }
	    _histos.Fill2D("ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_5", upara, boson_pz);
	  }
	  
	  if(probe_emobjs[iem_probe]->has_good_spatial_track_match()) {
	    
	    // Fill TigthTrkMatch hists
	    histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_eta_%d", type);
	    _histos.Fill1D(histname.Data(), probe_eta);
	    histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_%d", type);
	    _histos.Fill1D(histname.Data(), probe_caleta);
	    histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_pT_%d", type);
	    _histos.Fill1D(histname.Data(), probe_pT);
	    histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_vtxz_%d", type);
	    _histos.Fill1D(histname.Data(), vtxz);
	    histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_upara_%d", type);
	    _histos.Fill1D(histname.Data(), upara);
	    
	    histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_eta_pT_%d", type);
	    _histos.Fill2D(histname.Data(), probe_eta, probe_pT);
	    histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_eta_vtxz_%d", type);
	    _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	    histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT_%d", type);
	    _histos.Fill2D(histname.Data(), probe_caleta, probe_pT);
	    histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz_%d", type);
	    _histos.Fill2D(histname.Data(), probe_caleta, vtxz);
	    if (probe_charge < 0) {
	      histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz_%d", type);
	      _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	      if (tag_charge > 0) {
		histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap_%d", type);
		_histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	      }
	    } else if (probe_charge > 0) {
	      histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz_%d", type);
	      _histos.Fill2D(histname.Data(), probe_eta, vtxz);
	      if (tag_charge > 0) {
		histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam_%d", type);
		_histos.Fill2D(histname.Data(), tag_eta, probe_eta);
	      }
	    }
	    histname.Form("ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz_%d", type);
	    _histos.Fill2D(histname.Data(), upara, boson_pz);
	    	    
	    if(type%2==0) {
	      _histos.Fill1D("ZCandTrueTrkMatchEff_TightTrkMatch_eta_4", probe_eta);
	      _histos.Fill1D("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_4", probe_caleta);
	      _histos.Fill1D("ZCandTrueTrkMatchEff_TightTrkMatch_pT_4", probe_pT);
	      _histos.Fill1D("ZCandTrueTrkMatchEff_TightTrkMatch_vtxz_4", vtxz);
	      _histos.Fill1D("ZCandTrueTrkMatchEff_TightTrkMatch_upara_4", upara);
	      _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_eta_pT_4", probe_eta, probe_pT);
	      _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_eta_vtxz_4", probe_eta, vtxz);
	      _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT_4", probe_caleta, probe_pT);
	      _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz_4", probe_caleta, vtxz);
	      if (probe_charge < 0) {
		_histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz_4", probe_eta, vtxz);
		if (tag_charge > 0) {
		  _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap_4", tag_eta, probe_eta);
		}
	      } else if (probe_charge > 0) {
		_histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz_4", probe_eta, vtxz);
		if (tag_charge > 0) {
		  _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam_4", tag_eta, probe_eta);
		}
	      }
	      _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz_4", upara, boson_pz);
	    } else {
	      _histos.Fill1D("ZCandTrueTrkMatchEff_TightTrkMatch_eta_5", probe_eta);
	      _histos.Fill1D("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_5", probe_caleta);
	      _histos.Fill1D("ZCandTrueTrkMatchEff_TightTrkMatch_pT_5", probe_pT);
	      _histos.Fill1D("ZCandTrueTrkMatchEff_TightTrkMatch_vtxz_5", vtxz);
	      _histos.Fill1D("ZCandTrueTrkMatchEff_TightTrkMatch_upara_5", upara);
	      _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT_5", probe_caleta, probe_pT);
	      _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz_5", probe_caleta, vtxz);
	      if (probe_charge < 0) {
		_histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz_5", probe_eta, vtxz);
		if (tag_charge > 0) {
		  _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap_5", tag_eta, probe_eta);
		}
	      } else if (probe_charge > 0) {
		_histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz_5", probe_eta, vtxz);
		if (tag_charge > 0) {
		  _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam_5", tag_eta, probe_eta);
		}
	      }
	      _histos.Fill2D("ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz_5", upara, boson_pz);
	    }

	  } // End tight electron
	}   // End loose electron
      }     // End selection
    }       // End probe loop
  }         // End tag loop  
}
