#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include "wmass_analysis/FakeAnalysis_with_ej_tree.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "wmass_util/CAFTrack.hpp"
#include "wmass_analysis/histograms.hpp"
#include "wmass_util/CAFMet.hpp"
#include "wmass_util/hist_files.hpp"
#include <TFile.h>
using namespace std;
using namespace cafe;
using std::cout;
using std::endl;


  Int_t entry;
  Int_t run;
  Int_t evt;
  Float_t lumi;
  Float_t vtxz;
  Float_t evtmet;
  Float_t evtset;
  Float_t evtmeticd;
  Float_t evtseticd;

  Float_t wcandut;
  Float_t wcandmt;

  Int_t e_n;
  Float_t e_pt;
  Float_t e_e;
  Float_t e_eta;
  Float_t e_deta;
  Float_t e_phi;
  Float_t e_charge;
  Int_t e_spmtch;
  Int_t e_goodspmtch;
  Int_t e_id;

  Int_t j_n;
  Int_t j_n90; 
  Float_t j_pt; 
  Float_t j_e; 
  Float_t j_emf; 
  Float_t j_chf; 
  Float_t j_hcr; 
  Int_t j_trks;
  Float_t j_phi; 
  Float_t j_eta; 
  Float_t j_deta;


  Float_t ej_deltaphi;
  Float_t ej_angle;
  Float_t ej_m;


  TTree *ej;





FakeAnalysis_with_ej_tree::FakeAnalysis_with_ej_tree(const char *name)
  : Processor(name)
{

   ej = new TTree("ej","electron-jet tree");

   ej->Branch("entry", &entry, "entry/I");
   ej->Branch("run", &run, "run/I");
   ej->Branch("evt", &evt, "evt/I");
   ej->Branch("lumi", &lumi, "lumi/F");
   ej->Branch("vtxz", &vtxz, "vtxz/F");
   ej->Branch("evtmet", &evtmet, "evtmet/F");
   ej->Branch("evtset", &evtset, "evtset/F");
   ej->Branch("evtmeticd", &evtmeticd, "evtmeticd/F");
   ej->Branch("evtseticd", &evtseticd, "evtseticd/F");

   ej->Branch("wcandut", &wcandut, "wcandut/F");
   ej->Branch("wcandmt", &wcandmt, "wcandmt/F");

   ej->Branch("e_pt",    &e_pt,    "e_pt/F");
   ej->Branch("e_e",     &e_e,     "e_e/F");
   ej->Branch("e_eta",   &e_eta,   "e_eta/F");
   ej->Branch("e_deta",   &e_deta,   "e_deta/F");
   ej->Branch("e_phi",   &e_phi,   "e_phi/F");
   ej->Branch("e_charge", &e_charge, "e_charge/F");
   ej->Branch("e_spmtch", &e_spmtch, "e_spmtch/I");
   ej->Branch("e_goodspmtch", &e_goodspmtch, "e_goodspmtch/I");
   ej->Branch("e_id", &e_id, "e_id/I");

   ej->Branch("e_n", &e_n, "e_n/I");
   ej->Branch("j_n", &j_n, "j_n/I");

   ej->Branch("j_pt",    &j_pt,    "j_pt/F");
   ej->Branch("j_e",     &j_e,     "j_e/F");
   ej->Branch("j_eta",   &j_eta,   "j_eta/F");
   ej->Branch("j_deta",   &j_deta,   "j_deta/F");
   ej->Branch("j_phi",   &j_phi,   "j_phi/F");

   ej->Branch("j_trks", &j_trks, "j_trks/I");
   ej->Branch("j_n90", &j_n90, "j_n90/I");

   ej->Branch("j_emf",   &j_emf,   "j_emf/F");
   ej->Branch("j_chf",   &j_chf,   "j_chf/F");
   ej->Branch("j_hcr",   &j_hcr,   "j_hcr/F");

   ej->Branch("ej_m", &ej_m	   , "ej_m/F");
   ej->Branch("ej_deltaphi", &ej_deltaphi, "ej_deltaphi/F");
   ej->Branch("ej_angle", &ej_angle, "ej_angle/F");

   entry=0;



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

  ////Recoil config
  _dorawCellsRecoil = config.get("dorawCellsRecoil", true);
  _useConsistentMET = config.get("useConsistentMET", true);



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
bool FakeAnalysis_with_ej_tree::processEvent(cafe::Event& event) {
cout <<"in Fakeanalysis code"<<endl;
  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");

  vector<CAFEMObj*> emobjs;
  CAFMet met_corr;
  CAFMet met_corricd;
  CAFMet rawmet;
  

  int triglist_flag = -1;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;
  float event_vertex;
  float v_x,v_y,v_z;

  int solpol = -999;  
  double instlumi = 0.;


   cout<<"Good EMObjs, emobjs " <<event.get("Good EMObjs", emobjs) << endl; 
   cout<<"EMCorr Met, met_cor " <<event.get("EMCorr Met", met_corr) << endl; 
   cout<<"Raw Met, rawmet) << " <<event.get("Raw Met", rawmet) << endl;
   cout<<"EMCorr MetICD, met_ " <<event.get("EMCorr MetICD", met_corricd) << endl;
  cout<<"L1CalTowers, l1cal_ " <<event.get("L1CalTowers", l1cal_vec) << endl;  
  cout<<"L1Cal2bTowers, l1ca " <<event.get("L1Cal2bTowers", l1cal2b_vec) << endl;	
  cout<<"L2GblEMs, l2cal_vec " <<event.get("L2GblEMs", l2cal_vec) << endl; 
  cout<<"L3Eles, l3cal_vec)  " <<event.get("L3Eles", l3cal_vec) << endl; 
  cout<<"triglist flag, trig " <<event.get("triglist flag", triglist_flag) << endl; 
  cout<<"InstLumi, instlumi) " <<event.get("InstLumi", instlumi) << endl; 
  cout<<"solenoid polarity,  " <<event.get("solenoid polarity", solpol) << endl; 
  cout<<"Best primary vertexZ " <<event.get("Best primary vertexZ", v_z) << endl;
  cout<<"Best primary vertexX " <<event.get("Best primary vertexX", v_x) << endl;
  cout<<"Best primary vertexY " <<event.get("Best primary vertexY", v_y) << endl;
  cout<<" just before event.get loop"<<endl;
  if(event.get("Good EMObjs", emobjs) && 
     event.get("EMCorr Met", met_corr) && 
     event.get("Raw Met", rawmet) &&
     //event.get("EMCorr MetICD", met_corricd) &&
     event.get("L1CalTowers", l1cal_vec) &&  event.get("L1Cal2bTowers", l1cal2b_vec) &&   
     event.get("L2GblEMs", l2cal_vec) && 
     event.get("L3Eles", l3cal_vec) && event.get("triglist flag", triglist_flag) && 
     event.get("InstLumi", instlumi) && event.get("solenoid polarity", solpol) && 
     event.get("Best primary vertexZ", v_z) &&
     event.get("Best primary vertexX", v_x) &&
     event.get("Best primary vertexY", v_y)
     ) {
    cout<<" just before inst lumi"<<endl;
    if(instlumi > _InstLumi_lowcut && instlumi < _InstLumi_highcut){
	 
    	double met = met_corr.met(); 
        double set = met_corr.scalarEt();

    	double meticd = met_corricd.met(); 
        double seticd = met_corricd.scalarEt();


    	// require exactly one electron and this electron must pass trigger requirement
    	bool pass_trigger = false;

    	if(emobjs.size() == 1) 
    	  pass_trigger = emobjs[0]->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec);
    	// only look at the electron that passes trigger requirement
    	if(pass_trigger) {

    		// get primary vertex
    		//double v_z = event_vertex;
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

    			// construct W candidate
    			// primary vertex
    			float vtx[3]={v_x, v_y, v_z};

    			CAFWCand wcand;
    			CAFEMObj *emobj = 0;
    			double wScalarET = 0.;
    			if (emobjs.size()>=1) {
    			  emobj = emobjs[0];
    			  if(_dorawCellsRecoil) {
				if (_useConsistentMET) {
				  wcand = CAFWCand(emobj, &rawmet, vtx, true);
				} else {
				  wcand = CAFWCand(emobj, &met_corr, vtx);
				}
    			  } else {
				wcand = CAFWCand(emobj, &met_corr);
    			  }
    			  if (_useConsistentMET) {
				TVector2 consistMET=wcand.GetConsistentMET();
				double dummySET=met_corr.scalarEt();
        			wScalarET = dummySET;
				met_corr.SetMet(consistMET.X(),consistMET.Y(),consistMET.Mod(),dummySET);
    			  }
    			}

				// ejt tree code
				//entry = -555;
				run = -555;
				evt = -555;
				lumi = -555;
				vtxz = -555;
				evtmet = -555;
				evtset = -555;
				evtmeticd = -555;
				evtseticd = -555;

				wcandut = -555;
				wcandmt = -555;

				e_n = -555;
				e_pt = -555;
				e_e = -555;
				e_eta = -555;
				e_deta = -555;
				e_phi = -555;
				e_charge = -555;
				e_spmtch = -555;
				e_goodspmtch = -555;
				e_id = -555;

				j_n = -555;
				j_pt = -555;
				j_e = -555;
				j_eta = -555;
				j_deta = -555;
				j_phi = -555;
				j_trks = -555;
				j_n90 = -555;

				j_emf = -555;
				j_chf = -555;
				j_hcr = -555;
	
				ej_deltaphi = -555;
				ej_m = -555;
				ej_angle = -555;
				

    			bool found_JET=false;

				entry++;
				run=event.getGlobal()->runno();
				evt=event.getGlobal()->evtno();
				lumi=instlumi*36.0;
				vtxz=v_z;
				evtmet =  met;
				evtset =  set;
				evtmeticd =  meticd;
				evtseticd =  seticd;

    			wcandut = wcand.MagRecoil();
    			wcandmt = wcand.Mt();	

				if(emobjs[0]->has_spatial_track_match(-0.5)) e_spmtch=1;
				if(emobjs[0]->has_good_spatial_track_match()) e_goodspmtch=1;

    			e_id=emobjs[0]->id();
				e_pt=emobjs[0]->Pt();
				e_e=emobjs[0]->E();
				e_eta=emobjs[0]->Eta();
				e_deta=emobjs[0]->CalDetectorEta();
				e_phi=emobjs[0]->Phi();
				e_charge=emobjs[0]->charge();
				e_n=emobjs.size();

	            //loop over jets
				cafe::Collection<TMBJet> jets_ejttree = event.getJCCB();
    			j_n = 0;
				if(jets_ejttree.size() > 0) {
    			  for(Collection<TMBJet>::iterator iter = jets_ejttree.begin(); iter != jets_ejttree.end(); ++iter) { 
        			  j_n++;
                	  ej_deltaphi=kinem::delta_phi(e_phi, (*iter).Phi());
					  j_n90  = (*iter).n90(); 
					  j_pt   = (*iter).Pt();	 
					  j_emf  = (*iter).emf();
					  j_chf  = (*iter).chf();
					  j_hcr  = (*iter).hotcellratio();
					  j_trks = (*iter).Ntr(); 
					  j_eta  = (*iter).Eta();
					  j_phi  = (*iter).Phi();
					  j_deta = 0.1*((*iter).deta());
 					  j_e = (*iter).E();
	    			  TLorentzVector vect_jet((*iter).Px(), (*iter).Py(),(*iter).Pz(),(*iter).E());
	    			  TLorentzVector vect_emobj(emobjs[0]->Px(),emobjs[0]->Py(),emobjs[0]->Pz(),emobjs[0]->E());
	    			  TLorentzVector vect_Z=vect_jet+vect_emobj;
        			  ej_m=vect_Z.M();
					  TVector3 em_vect3 = emobjs[0]->vect3();
					  TVector3 jet_vect3( (*iter).Px(), (*iter).Py(), (*iter).Pz() );  
					  ej_angle = em_vect3.Angle(jet_vect3);
        			  found_JET = true;
                	  ej->Fill();
    			  }// for(Collection<TMBJet>
				}//if(jets_ejttree.size() > 0)
                // end of ejt tree code


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
					  cout<<"Fake_Electron_DetEta "<<elec_deteta<<endl;
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
  }// if event.get loop
  cout<<" end of process event" <<endl;
  return true;
}

// definition of good jet
bool FakeAnalysis_with_ej_tree::GoodJet(const TMBJet& jet) {

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

void FakeAnalysis_with_ej_tree::begin() {}

void FakeAnalysis_with_ej_tree::finish() {
  TFile *file = histfiles::initializeTFile( this );
  if(file==NULL) return;
  string directory_name("Fake_Hist");
  file->mkdir(directory_name.c_str());
  _histos.save(file, directory_name); 
  ej->Write();
  file->Close();
}

ClassImp(FakeAnalysis_with_ej_tree)
