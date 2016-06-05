#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include "wmass_analysis/FakeAnalysis.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "wmass_util/CAFTrack.hpp"
#include "wmass_analysis/histograms.hpp"
#include "wmass_util/CAFMet.hpp"
#include "wmass_util/hist_files.hpp"
#include <TFile.h>
using namespace std;
using namespace cafe;

FakeAnalysis::FakeAnalysis(const char *name)
  : Processor(name)
{
  Config config(name);

  // debug level
  _debugLevel = config.get("debugLevel", 0);

  // definition of good EMs
  _EMFracCut = config.get("EMFracCut", 0.9);
  _IsoCut = config.get("IsoCut", 0.15);
  _HM7Cut = config.get("HM7Cut", 12.);
  _HM8Cut = config.get("HM8Cut", 20.);

  _DetEtaCC = config.get("DetEtaCC", 1.1);
  _DetEtaEC1 = config.get("DetEtaEC1", 1.5);
  _DetEtaEC2 = config.get("DetEtaEC2", 2.5);

  // definition of good jets
  _jetN90Cut = config.get("jetN90Cut", 1);
  _jetpTCut = config.get("jetpTCut", 25.);
  _jetEMFracCut1 = config.get("jetEMFracCut1", 0.05);
  _jetEMFracCut2 = config.get("jetEMFracCut2", 0.7);
  _jetCHFracCut = config.get("jetCHFracCut", 0.4);
  _jetHCRatioCut = config.get("jetHCRatioCut", 10);
  _jetTrackCut = config.get("jetTracks", 5);

  _DetEtaCC_Jet = config.get("DetEtaCC_Jet", 0.8);
  _DetEtaEC1_Jet = config.get("DetEtaEC1_Jet", 1.5);
  _DetEtaEC2_Jet = config.get("DetEtaEC2_Jet", 2.5);

  // angle and phi seperation between EM and Jet
  _Angle_Jet_EM_Cut = config.get("Angle_Jet_EM_Cut", 0.25);
  _DPhi_Jet_EM_Cut = config.get("DPhi_Jet_EM_Cut", 2.8);

  // histograms
  _histos.add(Fake_Hist);
  _histos.add(Fake_Hist_2D);

  // missing Et cut used to determine fake rate
  _MetCut_FakeRate = config.get("MetCut_FakeRate", 10.);

  _InstLumi_lowcut  = config.get("InstLumi_lowcut", 100.);
  _InstLumi_highcut = config.get("InstLumi_highcut", 100.);


  // histograms for CC and EC region
  _histos.clone("Fake_Electron_DetEta", 2);
  _histos.clone("Fake_Electron_Eta", 2);
  _histos.clone("Fake_Electron_Pt", 2);
  _histos.clone("Fake_Met", 2);
  _histos.clone("Fake_Electron_DetEta_Match", 2);
  _histos.clone("Fake_Electron_Eta_Match", 2);
  _histos.clone("Fake_Electron_Pt_Match", 2);
  _histos.clone("Fake_Met_Match", 2);
  _histos.clone("Fake_Electron_DetEta_Spatial_Match", 2);
  _histos.clone("Fake_Electron_Eta_Spatial_Match", 2);
  _histos.clone("Fake_Electron_Pt_Spatial_Match", 2);
  _histos.clone("Fake_Met_Spatial_Match", 2);
  _histos.clone("Fake_Electron_DetEta_Spatial_Match_Tight", 2);
  _histos.clone("Fake_Electron_Eta_Spatial_Match_Tight", 2);
  _histos.clone("Fake_Electron_Pt_Spatial_Match_Tight", 2);
  _histos.clone("Fake_Met_Spatial_Match_Tight", 2);

  _histos.clone("Fake_Electron_Chi2_V_Met_Spatial_Match", 2);
  _histos.clone("Fake_Electron_Chi2_V_Met_Spatial_Match_Tight", 2);
  _histos.clone("Fake_Electron_Chi2", 2);
  _histos.clone("Fake_Electron_Chi2_Tight", 2);

  //for Fake Rate Study
  _histos.clone("Fake_Electron_DetEta_CCVtxBin", 6);
  _histos.clone("Fake_Electron_DetEta_CCVtxBin_Spatial_Match", 6);

  // histograms for CC and EC region after missing Et cut
  _histos.clone("Fake_Electron_DetEta_MetCut", 2);
  _histos.clone("Fake_Electron_Eta_MetCut", 2);
  _histos.clone("Fake_Electron_Pt_MetCut", 2);
  _histos.clone("Fake_Electron_DetEta_Match_MetCut", 2);
  _histos.clone("Fake_Electron_Eta_Match_MetCut", 2);
  _histos.clone("Fake_Electron_Pt_Match_MetCut", 2);
  _histos.clone("Fake_Electron_DetEta_Spatial_Match_MetCut", 2);
  _histos.clone("Fake_Electron_Eta_Spatial_Match_MetCut", 2);
  _histos.clone("Fake_Electron_Pt_Spatial_Match_MetCut", 2);
  _histos.clone("Fake_Electron_DetEta_Spatial_Match_Tight_MetCut", 2);
  _histos.clone("Fake_Electron_Eta_Spatial_Match_Tight_MetCut", 2);
  _histos.clone("Fake_Electron_Pt_Spatial_Match_Tight_MetCut", 2);

  _met_vars.add("_metC");

  _jccb_vars.add("fX");
  _jccb_vars.add("fY");
  _jccb_vars.add("fZ");
  _jccb_vars.add("_n90");
  _jccb_vars.add("_emf");
  _jccb_vars.add("_chf");
  _jccb_vars.add("_hot");
  _jccb_vars.add("_tracks");
  _jccb_vars.add("_deta");
}

// process
bool FakeAnalysis::processEvent(cafe::Event& event) {

  vector<CAFEMObj*> emobjs;
  CAFMet met_corr;
  int triglist_flag = -1;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;
  float event_vertex;

  int solpol = -999;  
  double instlumi = 0.;

  if(event.get("Good EMObjs", emobjs) && event.get("EMCorr Met", met_corr) &&
     event.get("L1CalTowers", l1cal_vec) &&  event.get("L1Cal2bTowers", l1cal2b_vec) &&   
     event.get("L2GblEMs", l2cal_vec) && 
     event.get("L3Eles", l3cal_vec) && event.get("triglist flag", triglist_flag) && 
     event.get("InstLumi", instlumi) && event.get("solenoid polarity", solpol) && 
     event.get("Primary vertexZ", event_vertex)) {

  
	if(instlumi > _InstLumi_lowcut && instlumi < _InstLumi_highcut){

    	double met = met_corr.met(); 

    	// require exactly one electron and this electron must pass trigger requirement
    	bool pass_trigger = false;

    	if(emobjs.size() == 1) 
    	  pass_trigger = emobjs[0]->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec);
    	// only look at the electron that passes trigger requirement
    	if(pass_trigger) {

    		// get primary vertex
    		double v_z = event_vertex;
    		char bins_Vtx[10];
    		int bin_Vtx_number;
    		bin_Vtx_number=int((v_z+60.)/20.);
    		sprintf(bins_Vtx, "%d", bin_Vtx_number);


    		// identify Zee candidates
    		// ************* code from WAnalysis *********************
    		// ************* for estimating zee bkgd *****************
			// require no high pT isolated track back-to-back with the electron
			bool EM_Track_backtoback = false;

    		// change solpol from 0/1 to -1/1
    		int polarity = 2*solpol -1;

			// get all isolated tracks
			vector<CAFTrack *> isolatedTrks;
			if(event.get("Good Tracks", isolatedTrks)) {
			  for(int itrk=0; itrk<isolatedTrks.size(); itrk++) {
	    		double em_trk_phidiff = kinem::delta_phi(emobjs[0]->Phi(), isolatedTrks[itrk]->Phi());
	    		if(em_trk_phidiff > 2.5 && // back to back with the EM cluster
	    		   fabs(isolatedTrks[itrk]->TrackDetEta(polarity, false /*_MCStudy*/))>1.1 &&  // track in ICR 
	    		   fabs(isolatedTrks[itrk]->TrackDetEta(polarity, false /*_MCStudy*/))<1.5 &&
	    		   fabs(isolatedTrks[itrk]->z()-v_z)<1. &&  // vertex close to each other 
	    		   (isolatedTrks[itrk]->charge())*(emobjs[0]->charge())<0.) { // opposite charge

	    		  TLorentzVector vect_trk(isolatedTrks[itrk]->Px(),isolatedTrks[itrk]->Py(),isolatedTrks[itrk]->Pz(),isolatedTrks[itrk]->E());
	    		  TLorentzVector vect_emobj(emobjs[0]->Px(),emobjs[0]->Py(),emobjs[0]->Pz(),emobjs[0]->E());
	    		  TLorentzVector vect_Z=vect_trk+vect_emobj;

	    		  // invariant mass
	    		  if(vect_Z.M()>70. && vect_Z.M()<110.)   EM_Track_backtoback = true;
	    		}
			  }
			}
			// end of identify Zee candidates

		    if(EM_Track_backtoback==false) {

    			//get jets from the event
    			cafe::Collection<TMBJet> jets = event.getJCCB(_jccb_vars);

    			for(Collection<TMBJet>::iterator iter = jets.begin(); iter!= jets.end(); ++iter) {

				if(GoodJet(*iter)) {
        		  float dphi_jet_em = kinem::delta_phi(emobjs[0]->Phi(), (*iter).Phi());
				  //get rid of the jet if they are close to each other
				  //since EM cluster may also be reconstructed as a jet
	    			if(fabs(dphi_jet_em) > _DPhi_Jet_EM_Cut) {

            			  // determine whether electron in CC or EC region
            			  int cal_region = -1; 
            			  if(emobjs[0]->IsCC(_DetEtaCC)) cal_region = 0;
            			  if(emobjs[0]->IsEC(_DetEtaEC1, _DetEtaEC2)) cal_region = 1;

            			  char region[10];  sprintf(region, "%d", cal_region);

	    				  float elec_deteta = emobjs[0]->CalDetectorEta();
	    				  float elec_eta = emobjs[0]->Eta();
	    				  float elec_pT = emobjs[0]->Pt();

            				  _histos.Fill1D("Fake_Electron_DetEta", elec_deteta);
	    				  _histos.Fill1D("Fake_Electron_Eta", elec_eta);
	    				  _histos.Fill1D("Fake_Electron_Pt", elec_pT);
	    				  _histos.Fill1D("Fake_Met", met);

	    				  // fill distributions for CC or EC region
	    				  _histos.Fill1D(string("Fake_Electron_DetEta_")+region, elec_deteta);
	    				  _histos.Fill1D(string("Fake_Electron_Eta_")+region, elec_eta);
	    				  _histos.Fill1D(string("Fake_Electron_Pt_")+region, elec_pT);
	    				  _histos.Fill1D(string("Fake_Met_")+region, met);


	    				  if(met< 15. && cal_region==0){
						      _histos.Fill1D(string("Fake_Electron_DetEta_CCVtxBin_")+bins_Vtx, emobjs[0]->CalDetectorEta());
	    				  }

	    				  // spatial+E/P
	    				  if(emobjs[0]->has_track_match()) {
							_histos.Fill1D("Fake_Electron_DetEta_Match", elec_deteta);
							_histos.Fill1D("Fake_Electron_Eta_Match", elec_eta);
							_histos.Fill1D("Fake_Electron_Pt_Match", elec_pT);
							_histos.Fill1D("Fake_Met_Match", met);

                					// fill distributions for CC or EC region
	        					_histos.Fill1D(string("Fake_Electron_DetEta_Match_")+region, elec_deteta);
	        					_histos.Fill1D(string("Fake_Electron_Eta_Match_")+region, elec_eta);
	        					_histos.Fill1D(string("Fake_Electron_Pt_Match_")+region, elec_pT);
                					_histos.Fill1D(string("Fake_Met_Match_")+region, met);
	    				  }

	    			  // spatial only
	    			  if(emobjs[0]->has_good_spatial_track_match()) {
						_histos.Fill1D("Fake_Electron_DetEta_Spatial_Match", elec_deteta);
						_histos.Fill1D("Fake_Electron_Eta_Spatial_Match", elec_eta);
						_histos.Fill1D("Fake_Electron_Pt_Spatial_Match", elec_pT);
						_histos.Fill1D("Fake_Met_Spatial_Match", met);

                				// fill distributions for CC or EC region
	        				_histos.Fill1D(string("Fake_Electron_DetEta_Spatial_Match_")+region, elec_deteta);
	        				_histos.Fill1D(string("Fake_Electron_Eta_Spatial_Match_")+region, elec_eta);
	        				_histos.Fill1D(string("Fake_Electron_Pt_Spatial_Match_")+region, elec_pT);
                				_histos.Fill1D(string("Fake_Met_Spatial_Match_")+region, met);

						if(met< 15. && cal_region==0){
						  _histos.Fill1D(string("Fake_Electron_DetEta_CCVtxBin_Spatial_Match_")+bins_Vtx, emobjs[0]->CalDetectorEta());
						}
	    			  }

	    			  // spatial only+SMT,CFT
	    			  if(emobjs[0]->has_spatial_track_match(-0.5)) {
						  // check chi2 vs met
						  _histos.Fill2D("Fake_Electron_Chi2_V_Met_Spatial_Match", met, emobjs[0]->track_match_spatialchi2prob());
						  _histos.Fill2D(string("Fake_Electron_Chi2_V_Met_Spatial_Match_")+region, met, emobjs[0]->track_match_spatialchi2prob());
                	    		  _histos.Fill1D("Fake_Electron_Chi2", emobjs[0]->track_match_spatialchi2prob());
                	    		  _histos.Fill1D(string("Fake_Electron_Chi2_")+region, emobjs[0]->track_match_spatialchi2prob());

						  double ElecPt = emobjs[0]->Pt();
						  double TrkPt = emobjs[0]->getPtrSpatialChp()->Pt();
						  double EOverP = 0.;
						  if(TrkPt>0.) EOverP = ElecPt/TrkPt;

						  if(emobjs[0]->getPtrSpatialChp()->nsmt()>=1 && emobjs[0]->getPtrSpatialChp()->ncft()>=4) {

							  // check chi2 vs met
							  _histos.Fill2D("Fake_Electron_Chi2_V_Met_Spatial_Match_Tight", met, emobjs[0]->track_match_spatialchi2prob());
							  _histos.Fill2D(string("Fake_Electron_Chi2_V_Met_Spatial_Match_Tight_")+region, met, emobjs[0]->track_match_spatialchi2prob());
                					  _histos.Fill1D("Fake_Electron_Chi2_Tight", emobjs[0]->track_match_spatialchi2prob());
                					  _histos.Fill1D(string("Fake_Electron_Chi2_Tight_")+region, emobjs[0]->track_match_spatialchi2prob());

							  _histos.Fill1D("Fake_Electron_DetEta_Spatial_Match_Tight", elec_deteta);
							  _histos.Fill1D("Fake_Electron_Eta_Spatial_Match_Tight", elec_eta);
							  _histos.Fill1D("Fake_Electron_Pt_Spatial_Match_Tight", elec_pT);
							  _histos.Fill1D("Fake_Met_Spatial_Match_Tight", met);

							  // fill distributions for CC or EC region
							  _histos.Fill1D(string("Fake_Electron_DetEta_Spatial_Match_Tight_")+region, elec_deteta);
							  _histos.Fill1D(string("Fake_Electron_Eta_Spatial_Match_Tight_")+region, elec_eta);
							  _histos.Fill1D(string("Fake_Electron_Pt_Spatial_Match_Tight_")+region, elec_pT);
							  _histos.Fill1D(string("Fake_Met_Spatial_Match_Tight_")+region, met);
				    	  }
	    			  }

	    			  //#######################################################
	    			  // same histograms for met<_MetCut_FakeRate
	    			  //#######################################################
	    			  if( met < _MetCut_FakeRate ) {
						_histos.Fill1D("Fake_Electron_DetEta_MetCut", elec_deteta);
						_histos.Fill1D("Fake_Electron_Eta_MetCut", elec_eta);
						_histos.Fill1D("Fake_Electron_Pt_MetCut", elec_pT);

						// fill distributions for CC or EC region
						_histos.Fill1D(string("Fake_Electron_DetEta_MetCut_")+region, elec_deteta);
						_histos.Fill1D(string("Fake_Electron_Eta_MetCut_")+region, elec_eta);
						_histos.Fill1D(string("Fake_Electron_Pt_MetCut_")+region, elec_pT);

						// spatial+E/P
						if(emobjs[0]->has_track_match()) {
						  _histos.Fill1D("Fake_Electron_DetEta_Match_MetCut", elec_deteta);
						  _histos.Fill1D("Fake_Electron_Eta_Match_MetCut", elec_eta);
						  _histos.Fill1D("Fake_Electron_Pt_Match_MetCut", elec_pT);

						  // fill distributions for CC or EC region
						  _histos.Fill1D(string("Fake_Electron_DetEta_Match_MetCut_")+region, elec_deteta);
						  _histos.Fill1D(string("Fake_Electron_Eta_Match_MetCut_")+region, elec_eta);
						  _histos.Fill1D(string("Fake_Electron_Pt_Match_MetCut_")+region, elec_pT);
						}

						// good spatial only
						if(emobjs[0]->has_good_spatial_track_match()) {
						  _histos.Fill1D("Fake_Electron_DetEta_Spatial_Match_MetCut", elec_deteta);
						  _histos.Fill1D("Fake_Electron_Eta_Spatial_Match_MetCut", elec_eta);
						  _histos.Fill1D("Fake_Electron_Pt_Spatial_Match_MetCut", elec_pT);

						  // fill distributions for CC or EC region
						  _histos.Fill1D(string("Fake_Electron_DetEta_Spatial_Match_MetCut_")+region, elec_deteta);
						  _histos.Fill1D(string("Fake_Electron_Eta_Spatial_Match_MetCut_")+region, elec_eta);
						  _histos.Fill1D(string("Fake_Electron_Pt_Spatial_Match_MetCut_")+region, elec_pT);
						}

						// spatial only+SMT,CFT+E/p
						if(emobjs[0]->has_spatial_track_match(-0.5)) {
						  double ElecPt = emobjs[0]->Pt();
						  double TrkPt = emobjs[0]->getPtrSpatialChp()->Pt();
						  double EOverP = 0.;
						  if(TrkPt>0.) EOverP = ElecPt/TrkPt;

						  if(emobjs[0]->getPtrSpatialChp()->nsmt()>=1 && emobjs[0]->getPtrSpatialChp()->ncft()>=4) {
		    				_histos.Fill1D("Fake_Electron_DetEta_Spatial_Match_Tight_MetCut", elec_deteta);
		    				_histos.Fill1D("Fake_Electron_Eta_Spatial_Match_Tight_MetCut", elec_eta);
		    				_histos.Fill1D("Fake_Electron_Pt_Spatial_Match_Tight_MetCut", elec_pT);

		    				// fill distributions for CC or EC region
		    				_histos.Fill1D(string("Fake_Electron_DetEta_Spatial_Match_Tight_MetCut_")+region, elec_deteta);
		    				_histos.Fill1D(string("Fake_Electron_Eta_Spatial_Match_Tight_MetCut_")+region, elec_eta);
		    				_histos.Fill1D(string("Fake_Electron_Pt_Spatial_Match_Tight_MetCut_")+region, elec_pT);
						  }
						}

	    			  } // missing Et cut

	    			} // EM and Jet are back-to-back
				}
    		    } // loop over jets

		   }//if(EM_Track_backtoback==false) i.e. this is not zee event 

    	}// exactly one good EM object and pass trigger

	}//lumi cut
  }
  return true;
}

// definition of good jet
bool FakeAnalysis::GoodJet(const TMBJet& jet) {

  bool good = false;
  
  float jetpT = jet.Pt();
  if(jetpT > _jetpTCut) {
    int jetN90 = jet.n90();
    float jetEMFrac = jet.emf();
    float jetCHFrac = jet.chf();
    float jetHCRatio = jet.hotcellratio();
    int jetTrack = jet.Ntr();
    float deta = 0.1*(jet.deta());

    if( (fabs(deta)<_DetEtaCC_Jet) || ((fabs(deta)>_DetEtaEC1_Jet) && (fabs(deta)<_DetEtaEC2_Jet)) ) {
      if( (jetN90>_jetN90Cut) && (jetEMFrac>_jetEMFracCut1) && (jetEMFrac<_jetEMFracCut2) &&
	  (jetCHFrac<_jetCHFracCut) && (jetHCRatio<_jetHCRatioCut) && (jetTrack>=_jetTrackCut) )
	good = true;
    }
  }
  return good;
}

void FakeAnalysis::begin() {}

void FakeAnalysis::finish() {
  TFile *file = histfiles::initializeTFile( this );
  if(file==NULL) return;
  string directory_name("Fake_Hist");
  file->mkdir(directory_name.c_str());
  _histos.save(file, directory_name);
  file->Close();
}

ClassImp(FakeAnalysis)
