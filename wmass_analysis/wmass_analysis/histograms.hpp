#ifndef HISTOGRAMS_HPP
#define HISTOGRAMS_HPP

#include "wmass_util/hist_nd.hpp"
#include <TMath.h>

// histograms used for EffAnalysis
static HIST_1D Eff_Hist[]={
                      // trigger efficiency for different trigger list
		      // the histogram for each trigger is hist_ij, where i is triglist and j is trigger index in this triglist
		      // for example hist_00 is EM_HI_SH in v8-10, hist_21 is E2_SHT20 in v12
		      {"InvMass_EM_Probe_Trig_All", 140, 60., 130.},     //invariant mass for EM+probe 
                      {"InvMass_EM_Probe_Trig_Matched", 140, 60., 130.}, //invariant mass for EM+probe after matching probe EM with trigger objects
		      {"DetEta_EM_Probe_Trig_All", 31, -3.1, 3.1},       //probe EM DetEta
		      {"Pt_EM_Probe_Trig_All_Both", 100, 0., 100.},       //
		      {"Pt_EM_Probe_Trig_Matched_v16_Both", 100, 0., 100.},   //probe EM DetEta after matching with trigger objects
		      {"Pt_EM_Probe_Trig_Matched_v15", 100, 0., 100.},   //probe EM DetEta after matching with trigger objects
		      {"Pt_EM_Probe_L1_Matched", 100, 0., 100.},
		      {"l1Pt_EM_Probe_L1_Matched", 100, 0., 100.},
		      {"Pt_EM_Probe_L2_Matched", 100, 0., 100.},
		      {"l2Pt_EM_Probe_L2_Matched", 100, 0., 100.},
		      {"Pt_EM_Probe_L3_Matched", 100, 0., 100.},
		      {"l3Pt_EM_Probe_L3_Matched", 100, 0., 100.},


		      {"Pt_EM_Probe_Trig_v16_25_lumi", 250, 0., 10.},
		      {"Pt_EM_Probe_Trig_v16_27_lumi", 250, 0., 10.},
		      {"Pt_EM_Probe_Trig_v16_27_7_lumi", 250, 0., 10.},

		      {"Pt_EM_Probe_Trig_TT_v16_25_lumi", 250, 0., 10.},
		      {"Pt_EM_Probe_Trig_TT_v16_27_lumi", 250, 0., 10.},
		      {"Pt_EM_Probe_Trig_TT_v16_27_7_lumi", 250, 0., 10.},
	      

		      {"Pt_EM_Probe_Trig_v16_25", 100, 0., 100.},   //probe EM DetEta after matching with trigger objects
		      {"Pt_EM_Probe_Trig_v16_27", 100, 0., 100.},   //probe EM DetEta after matching with trigger objects
		      {"Pt_EM_Probe_Trig_v16_27_7", 100, 0., 100.},   //probe EM DetEta after matching with trigger objects

		      {"Pt_EM_Probe_Trig_TT_v16_25", 100, 0., 100.},   //probe EM DetEta after matching with trigger objects
		      {"Pt_EM_Probe_Trig_TT_v16_27", 100, 0., 100.},   //probe EM DetEta after matching with trigger objects
		      {"Pt_EM_Probe_Trig_TT_v16_27_7", 100, 0., 100.},   //probe EM DetEta after matching with trigger objects
	      
		      {"Pt_EM_Probe_Trig_Matched_v16_25", 100, 0., 100.},   //probe EM DetEta after matching with trigger objects
		      {"Pt_EM_Probe_Trig_Matched_v16_27", 100, 0., 100.},   //probe EM DetEta after matching with trigger objects
                      {"DetEta_EM_Probe_Trig_Matched", 31, -3.1, 3.1},   //probe EM DetEta after matching with trigger objects
		      {"PhysEta_EM_Probe_Trig_All", 31, -3.1, 3.1},      //probe EM PhysEta 
                      {"PhysEta_EM_Probe_Trig_Matched", 31, -3.1, 3.1},  //probe EM PhysEta after matching with trigger objects
		      {"DetPhi_EM_Probe_Trig_All", 64, 0., TMath::TwoPi()},        //probe EM DetPhi 
                      {"DetPhi_EM_Probe_Trig_Matched", 64, 0., TMath::TwoPi()},    //probe EM DetPhi after matching with trigger objects
		      {"TrkPhiEM3_EM_Probe_Trig_All", 64, 0., TMath::TwoPi()},        //probe EM Trk Phi extrap to EM3 
                      {"TrkPhiEM3_EM_Probe_Trig_Matched", 64, 0., TMath::TwoPi()},    //probe EM Trk Phi extrap to EM3 after matching with trigger objects
		      {"Pt_EM_Probe_Trig_All", 100, 0., 100.},           //probe EM Pt 
                      {"Pt_EM_Probe_Trig_Matched", 100, 0., 100.},       //probe EM Pt after matching with trigger objects
		      // for each trigger list
		      {"InvMass_EM_Probe_Trig_All_Triglist", 140, 60.,130.},      //invariant mass for EM+probe 
                      {"InvMass_EM_Probe_Trig_Matched_Triglist", 140, 60., 130.}, //invariant mass for EM+probe after matching probe EM with trigger objects
		      {"DetEta_EM_Probe_Trig_All_Triglist", 31, -3.1, 3.1},       //probe EM DetEta 
                      {"DetEta_EM_Probe_Trig_Matched_Triglist", 31, -3.1, 3.1},   //probe EM DetEta after matching with trigger objects
		      {"PhysEta_EM_Probe_Trig_All_Triglist", 31, -3.1, 3.1},      //probe EM PhysEta 
                      {"PhysEta_EM_Probe_Trig_Matched_Triglist", 31, -3.1, 3.1},  //probe EM PhysEta after matching with trigger objects
		      {"DetPhi_EM_Probe_Trig_All_Triglist", 64, 0., TMath::TwoPi()},        //probe EM DetPhi 
                      {"DetPhi_EM_Probe_Trig_Matched_Triglist", 64, 0., TMath::TwoPi()},    //probe EM DetPhi after matching with trigger objects
		      {"TrkPhiEM3_EM_Probe_Trig_All_Triglist", 64, 0., TMath::TwoPi()},        //probe EM Trk Phi extrap to EM3 
                      {"TrkPhiEM3_EM_Probe_Trig_Matched_Triglist", 64, 0., TMath::TwoPi()},    //probe EM Trk Phi extrap to EM3 after matching with trigger objects
		      {"Pt_EM_Probe_Trig_All_Triglist", 100, 0., 100.},           //probe EM Pt 
                      {"Pt_EM_Probe_Trig_Matched_Triglist", 100, 0., 100.},       //probe EM Pt after matching with trigger objects

		      // preselection efficiency
                      {"ZCandMass_EM_Trk", 140, 60., 130.},               // invariant mass for EM+trk
		      {"ZCandMass_EM_Trk_Matched", 140, 60., 130.},               // invariant mass for EM+trk
                      {"TrkDetEta_EM_Trk_PreSel_All", 60, -3., 3.},      //probe track DetEta
                      {"TrkDetEta_EM_Trk_PreSel_Matched", 60, -3., 3.},  //probe track DetEta after matching with EM cluster
		      {"QCDZCandMass_EM_Trk", 320, 20., 180.},
		      {"QCDZCandMass_EM_Trk_Matched", 320, 20., 180.},
		      {"QCDTrkDetEta_EM_Trk_PreSel_All", 60, -3., 3.},      //probe track DetEta
                      {"QCDTrkDetEta_EM_Trk_PreSel_Matched", 60, -3., 3.},  //probe track DetEta after matching with EM cluster

		      // HMx efficiency
                      {"EMDetEta_EM_Probe_HMx_All", 60, -3., 3.},        //probe EM DetEta  
                      {"EMDetEta_EM_Probe_HMx_Matched", 60, -3., 3.},    //probe EM DetEta after passing HMx cut
		      ////by Jun: truth method
		      {"EMPt_truth_CC", 100, 0., 100.},
		      {"EMPt_emfrac_truth_CC", 100, 0., 100.},    
		      {"EMPt_emfrac_iso_truth_CC", 100, 0., 100.},    
		      {"EMPt_emfrac_iso_HMx7_truth_CC", 100, 0., 100.},    
		      {"EMPt_emfrac_iso_HMx7_spatial_truth_CC", 100, 0., 100.},    
		      {"EMPt_emfrac_iso_HMx7_spatial_smt_truth_CC", 100, 0., 100.},    
		      {"EMPt_emfrac_iso_HMx7_spatial_smt_trkpT_truth_CC", 100, 0., 100.},    
		      
		      {"EMVtx_truth_CC", 36, -60., 60.},
		      {"EMVtx_emfrac_truth_CC", 36, -60., 60.},    
		      {"EMVtx_emfrac_iso_truth_CC", 36, -60., 60.},    
		      {"EMVtx_emfrac_iso_HMx7_truth_CC", 36, -60., 60.},    
		      {"EMVtx_emfrac_iso_HMx7_spatial_truth_CC", 36, -60., 60.},    
		      {"EMVtx_emfrac_iso_HMx7_spatial_smt_truth_CC", 36, -60., 60.},    
		      {"EMVtx_emfrac_iso_HMx7_spatial_smt_trkpT_truth_CC", 36, -60., 60.},

		      // more Jun: step by step
		      {"EMPt_CC", 100, 0., 100.},
		      {"EMPt_emfrac_iso_CC", 100, 0., 100.},    
		      {"EMPt_emfrac_iso_HMx7_CC", 100, 0., 100.},    
		      {"EMPt_emfrac_iso_HMx7_spatial_CC", 100, 0., 100.},    
		      {"EMPt_emfrac_iso_HMx7_spatial_smt_CC", 100, 0., 100.},    
		      {"EMPt_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 100, 0., 100.}, 

		      {"EMPt_first_CC", 100, 0., 100.},
		      {"EMPt_first_emfrac_iso_CC", 100, 0., 100.},    
		      {"EMPt_first_emfrac_iso_HMx7_CC", 100, 0., 100.},    
		      {"EMPt_first_emfrac_iso_HMx7_spatial_CC", 100, 0., 100.},    
		      {"EMPt_first_emfrac_iso_HMx7_spatial_smt_CC", 100, 0., 100.},    
		      {"EMPt_first_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 100, 0., 100.},    
 
		      {"EMPt_second_CC", 100, 0., 100.},
		      {"EMPt_second_emfrac_iso_CC", 100, 0., 100.},    
		      {"EMPt_second_emfrac_iso_HMx7_CC", 100, 0., 100.},    
		      {"EMPt_second_emfrac_iso_HMx7_spatial_CC", 100, 0., 100.},    
		      {"EMPt_second_emfrac_iso_HMx7_spatial_smt_CC", 100, 0., 100.},    
		      {"EMPt_second_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 100, 0., 100.},    

		      {"EMPt_MC_CC", 100, 0., 100.},
		      {"EMPt_MC_emfrac_iso_CC", 100, 0., 100.},    
		      {"EMPt_MC_emfrac_iso_HMx7_CC", 100, 0., 100.},    
		      {"EMPt_MC_emfrac_iso_HMx7_spatial_CC", 100, 0., 100.},    
		      {"EMPt_MC_emfrac_iso_HMx7_spatial_smt_CC", 100, 0., 100.},    
		      {"EMPt_MC_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 100, 0., 100.},    

		      {"EMVtx_CC", 320, -80., 80.},
		      {"EMVtx_emfrac_iso_CC", 320, -80., 80.},    
		      {"EMVtx_emfrac_iso_HMx7_CC", 320, -80., 80.},    
		      {"EMVtx_emfrac_iso_HMx7_spatial_CC", 320, -80., 80.},    
		      {"EMVtx_emfrac_iso_HMx7_spatial_smt_CC", 320, -80., 80.},    
		      {"EMVtx_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 320, -80., 80.},    

		      {"EMEta_CC", 310, -3.1, 3.1},
		      {"EMEta_emfrac_iso_CC", 310, -3.1, 3.1},    
		      {"EMEta_emfrac_iso_HMx7_CC", 310, -3.1, 3.1},    
		      {"EMEta_emfrac_iso_HMx7_spatial_CC", 310, -3.1, 3.1},    
		      {"EMEta_emfrac_iso_HMx7_spatial_smt_CC", 310, -3.1, 3.1},    
		      {"EMEta_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 310, -3.1, 3.1},    

		      {"EMDetEta_CC", 310, -3.1, 3.1},
		      {"EMDetEta_emfrac_iso_CC", 310, -3.1, 3.1},    
		      {"EMDetEta_emfrac_iso_HMx7_CC", 310, -3.1, 3.1},    
		      {"EMDetEta_emfrac_iso_HMx7_spatial_CC", 310, -3.1, 3.1},    
		      {"EMDetEta_emfrac_iso_HMx7_spatial_smt_CC", 310, -3.1, 3.1},    
		      {"EMDetEta_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 310, -3.1, 3.1},    



		      // Loose track matching efficiency
                      {"loose_EMDetEta_EM_Probe_Trk_All", 31, -3.1, 3.1},            //probe EM DetEta 
                      {"loose_EMEta_EM_Probe_Trk", 31, -3.1, 3.1},                   //probe EM Eta 
                      {"loose_EMPt_EM_Probe_Trk", 100, 0., 100.},                    //probe EM Pt 
                      {"loose_EMDetEta_EM_Probe_Trk_Matched_All", 31, -3.1, 3.1},    //probe EM DetEta after matching with track
                      {"loose_EMEta_EM_Probe_Trk_Matched", 31, -3.1, 3.1},           //probe EM Eta after track match
                      {"loose_EMPt_EM_Probe_Trk_Matched", 100, 0., 100.},            //probe EM Pt  after trac match
                     


		      {"loose_EMDetEta_EM_Probe_Spatial_Trk_Matched_All", 31, -3.1, 3.1},          //probe EM DetEta after matching with track
                      {"loose_EMEta_EM_Probe_Spatial_Trk_Matched", 31, -3.1, 3.1},                 //probe EM Eta 
                      {"loose_EMPt_EM_Probe_Spatial_Trk_Matched", 100, 0., 100.},                  //probe EM Pt 
                     
		      // for different vertex regions
                      {"loose_EMDetEta_EM_Probe_Trk_All_Vtx", 31, -3.1, 3.1},                    //probe EM DetEta 
                      {"loose_EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx", 31, -3.1, 3.1},        //probe EM DetEta after matching with track
                     
		      {"loose_EMEta_EM_Probe_Trk_All_Vtx", 31, -3.1, 3.1},                    //probe EM Eta 
                      {"loose_EMEta_EM_Probe_Spatial_Trk_Matched_Vtx", 31, -3.1, 3.1},        //probe EM Eta after matching with track
                      
		      {"loose_EMPt_EM_Probe_Trk_All_CC_Vtx", 100, 0., 100.},                     //probe EM Pt (for CC region)
                      {"loose_EMPt_EM_Probe_Spatial_Trk_Matched_CC_Vtx", 100, 0., 100.},         //probe EM Pt after matching with track (for CC region)
                      
		      {"loose_EMPt_EM_Probe_Trk_All_EC_Vtx", 100, 0., 100.},                     //probe EM Pt (for EC region)
                      {"loose_EMPt_EM_Probe_Spatial_Trk_Matched_EC_Vtx", 100, 0., 100.},         //probe EM Pt after matching with track (for EC region)
		      
		      // mass for different vertex and eta region (need to subtract background)
                      {"loose_ZMass_vs_Eta_Before_Trk_Vtx_CC", 150, 0., 150.},
                      {"loose_ZMass_vs_Eta_After_Trk_Vtx_CC", 150, 0., 150.},
		      {"loose_ZMass_vs_Eta_Before_Trk_Vtx_EC", 150, 0., 150.},
                      {"loose_ZMass_vs_Eta_After_Trk_Vtx_EC", 150, 0., 150.},


		      // track matching efficiency
                      {"EMDetEta_EM_Probe_Trk_All", 31, -3.1, 3.1},            //probe EM DetEta 
		      {"EMDetEta_EM_Probe_Trk_trkfid_All", 31, -3.1, 3.1},            //probe EM DetEta 
                      {"EMEta_EM_Probe_Trk", 31, -3.1, 3.1},                   //probe EM Eta 
                      {"EMPt_EM_Probe_Trk", 100, 0., 100.},                    //probe EM Pt 
                      {"EMDetEta_EM_Probe_Trk_Matched_All", 31, -3.1, 3.1},    //probe EM DetEta after matching with track
                      {"EMEta_EM_Probe_Trk_Matched", 31, -3.1, 3.1},           //probe EM Eta 
                      {"EMPt_EM_Probe_Trk_Matched", 100, 0., 100.},            //probe EM Pt 
                      {"EMDetEta_EM_Probe_Spatial_Trk_Matched_All", 31, -3.1, 3.1},          //probe EM DetEta after matching with track
		      {"EMDetEta_EM_Probe_Spatial_Trk_Matched_trkfid_All", 31, -3.1, 3.1},          //probe EM DetEta after matching with track
                      {"EMEta_EM_Probe_Spatial_Trk_Matched", 31, -3.1, 3.1},                 //probe EM Eta 
                      {"EMPt_EM_Probe_Spatial_Trk_Matched", 100, 0., 100.},                  //probe EM Pt 
                      {"EMDetEta_EM_Probe_Spatial_Trk_Matched_Tight_All", 31, -3.1, 3.1},    //probe EM DetEta after matching with track
                      {"EMEta_EM_Probe_Spatial_Trk_Matched_Tight", 31, -3.1, 3.1},           //probe EM Eta 
                      {"EMPt_EM_Probe_Spatial_Trk_Matched_Tight", 100, 0., 100.},            //probe EM Pt 
		      // for different vertex regions
                      {"EMDetEta_EM_Probe_Trk_All_Vtx", 31, -3.1, 3.1},                    //probe EM DetEta 
                      {"EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx", 31, -3.1, 3.1},        //probe EM DetEta after matching with track
                      {"EMEta_EM_Probe_Trk_All_Vtx", 31, -3.1, 3.1},                    //probe EM Eta 
                      {"EMEta_EM_Probe_Spatial_Trk_Matched_Vtx", 31, -3.1, 3.1},        //probe EM Eta after matching with track
                      {"EMPt_EM_Probe_Trk_All_CC_Vtx", 100, 0., 100.},                     //probe EM Pt (for CC region)
                      {"EMPt_EM_Probe_Spatial_Trk_Matched_CC_Vtx", 100, 0., 100.},         //probe EM Pt after matching with track (for CC region)
                      {"EMPt_EM_Probe_Trk_All_EC_Vtx", 100, 0., 100.},                     //probe EM Pt (for EC region)
                      {"EMPt_EM_Probe_Spatial_Trk_Matched_EC_Vtx", 100, 0., 100.},         //probe EM Pt after matching with track (for EC region)
		      // mass for different vertex and eta region (need to subtract background)
                      {"ZMass_vs_Eta_Before_Trk_Vtx_CC", 150, 0., 150.},
                      {"ZMass_vs_Eta_After_Trk_Vtx_CC", 150, 0., 150.},
		      {"ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC", 150, 0., 150.},
		      {"ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC", 150, 0., 150.},
		      {"ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC", 150, 0., 150.},
		      {"ZMass_vs_Eta_Before_Trk_Vtx_EC", 150, 0., 150.},
                      {"ZMass_vs_Eta_After_Trk_Vtx_EC", 150, 0., 150.},

		      


		      // use generator level information to check pT dependence
                      {"EMPt_Reco_After_EMID_Match", 60, 20., 80.},
                      {"EMPt_Reco_After_EMID_EMFrac_Iso_Match", 60, 20., 80.},
                      {"EMPt_Reco_After_EMID_EMFrac_Iso_HMx_Match", 60, 20., 80.},
                      {"EMPt_Reco_After_EMID_EMFrac_Iso_HMx_SpatialTrack_Match", 60, 20., 80.},
                      {"EMPt_Reco_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_Match", 60, 20., 80.},
                      {"EMPt_Reco_After_EMID_EMFrac_Iso_HMx_SpatialTrack_SMTHit_Match", 60, 20., 80.},
                      {"EMPt_Reco_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_SMTHit_Match", 60, 20., 80.},
		      // use generator level information to check track matching efficiency
                      {"EMEta_TrkEff_After_EMID_EMFrac_Iso_HMx", 31, -3.1, 3.1},
                      {"EMEta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_Match", 31, -3.1, 3.1},
                      {"EMEta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_Match", 31, -3.1, 3.1},
                      {"EMEta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_SMTHit_Match", 31, -3.1, 3.1},
                      {"EMEta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_SMTHit_Match", 31, -3.1, 3.1},
                      {"EMVtx_TrkEff_After_EMID_EMFrac_Iso_HMx", 12, -60., 60.},
                      {"EMVtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_Match", 12, -60., 60.},
                      {"EMVtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_Match", 12, -60., 60.},
                      {"EMVtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_SMTHit_Match", 12, -60., 60.},
                      {"EMVtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_SMTHit_Match", 12, -60., 60.},
                      // check the electron pT dependence of overall selection efficiency
                      {"EMPt_pTDependence_before", 60, 20., 80.},  // use both electrons as the probe electron
                      {"EMPt_pTDependence_after_EMFrac_Iso", 60, 20., 80.},
                      {"EMPt_pTDependence_after_EMFrac_Iso_HMx", 60, 20., 80.},
                      {"EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch", 60, 20., 80.},
                      {"EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_SMTHit", 60, 20., 80.},
                      {"EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt", 60, 20., 80.},
                      {"EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt_SMTHit", 60, 20., 80.},
                      {"EMPt1_pTDependence_before", 60, 20., 80.},  // only use the second highest pT electron as the probe electron
                      {"EMPt1_pTDependence_after_EMFrac_Iso", 60, 20., 80.},
                      {"EMPt1_pTDependence_after_EMFrac_Iso_HMx", 60, 20., 80.},
                      {"EMPt1_pTDependence_after_EMFrac_Iso_HMx_TrackMatch", 60, 20., 80.},
                      {"EMPt1_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_SMTHit", 60, 20., 80.},
                      {"EMPt1_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt", 60, 20., 80.},
                      {"EMPt1_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt_SMTHit", 60, 20., 80.},
                      {"EMPt2_pTDependence_before", 60, 20., 80.},  // only use the highest pT electron as the probe electron
                      {"EMPt2_pTDependence_after_EMFrac_Iso", 60, 20., 80.},
                      {"EMPt2_pTDependence_after_EMFrac_Iso_HMx", 60, 20., 80.},
                      {"EMPt2_pTDependence_after_EMFrac_Iso_HMx_TrackMatch", 60, 20., 80.},
                      {"EMPt2_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_SMTHit", 60, 20., 80.},
                      {"EMPt2_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt", 60, 20., 80.},
                      {"EMPt2_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt_SMTHit", 60, 20., 80.},

		      ////study Reco pT effeciency 
		      {"EMPt_inEtaBin_RecoEff_CC", 100, 0., 100.},
     		      {"EMPt_emfrac_iso_inEtaBin_RecoEff_CC", 100, 0., 100.},    
     		      {"EMPt_emfrac_iso_HMx7_inEtaBin_RecoEff_CC", 100, 0., 100.},    
     		      {"EMPt_emfrac_iso_HMx7_spatial_inEtaBin_RecoEff_CC", 100, 0., 100.},    
     		      {"EMPt_emfrac_iso_HMx7_spatial_smt_inEtaBin_RecoEff_CC", 100, 0., 100.},    
		      {"ZMass_inEtaBin_RecoEff_CC", 140, 60., 130.},
		      {"ZMass_emfrac_iso_inEtaBin_RecoEff_CC", 140, 60., 130.},
		      {"ZMass_emfrac_iso_HMx7_inEtaBin_RecoEff_CC", 140, 60., 130.},
		      {"ZMass_emfrac_iso_HMx7_spatial_inEtaBin_RecoEff_CC", 140, 60., 130.},
		      {"ZMass_emfrac_iso_HMx7_spatial_smt_inEtaBin_RecoEff_CC", 140, 60., 130.},
		      {"", 0, 0, 0}};

static HIST_1D LumiEff_Hist[]={
                      {"InstLumi_bare", 250, 0., 10.},
		      {"InstLumi_trig", 250, 0., 10.},
		      {"InstLumi_2EM_20", 250, 0., 10.},
		      {"InstLumi_2EM_25", 250, 0., 10.},
		      {"InstLumi_CCCC", 250, 0., 10.},
		      {"InstLumi_etafid", 250, 0., 10.},
		      {"InstLumi_trkfid", 250, 0., 10.},
		      {"InstLumi_trk", 250, 0., 10.},
		      {"InstLumi_preseltrk", 250, 0., 10.},
		      {"InstLumi_emiso", 250, 0., 10.},
		      {"InstLumi_hmx", 250, 0., 10.},
		      {"InstLumi_vtx", 250, 0., 10.},
		      {"", 0, 0, 0}};

// 2D histograms used for EffAnalysis
static HIST_2D Eff_Hist_2D[]={
                      {"EMDetEta_ZMass_EM_Probe_Trk_All", 31, -3.1, 3.1, 150, 0., 150.},
                      {"EMDetEta_ZMass_EM_Probe_Trk_Matched", 31, -3.1, 3.1, 150, 0., 150.},
                      {"EMDetEta_Bkgd", 31, -3.1, 3.1, 150, 0., 150.},
		      {"EMEta_ZMass_EM_Probe_Trk_All", 31, -3.1, 3.1, 150, 0., 150.},
                      {"EMEta_ZMass_EM_Probe_Trk_Matched", 31, -3.1, 3.1, 150, 0., 150.},
                      {"EMEta_Bkgd", 31, -3.1, 3.1, 150, 0., 150.},
		      // use generator level information to check track matching efficiency
                      // electron eta vs primary vertex
                      {"EMEta_Vtx_TrkEff_After_EMID_EMFrac_Iso_HMx", 12, -60., 60., 31, -3.1, 3.1},
                      {"EMEta_Vtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_Match", 12, -60., 60., 31, -3.1, 3.1},
                      {"EMEta_Vtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_Match", 12, -60., 60., 31, -3.1, 3.1},
                      {"EMEta_Vtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_SMTHit_Match", 12, -60., 60., 31, -3.1, 3.1},
                      {"EMEta_Vtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_SMTHit_Match", 12, -60., 60., 31, -3.1, 3.1},
                      // primary vertex vs electron eta
                      {"EMVtx_Eta_TrkEff_After_EMID_EMFrac_Iso_HMx", 15, -3., 3., 24, -60., 60.},
                      {"EMVtx_Eta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_Match", 15, -3., 3., 24, -60., 60.},
                      {"EMVtx_Eta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_Match", 15, -3., 3., 24, -60., 60.},
                      {"EMVtx_Eta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_SMTHit_Match", 15, -3., 3., 24, -60., 60.},
                      {"EMVtx_Eta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_SMTHit_Match", 15, -3., 3., 24, -60., 60.},
		      //trigger 2d
		      {"Pt_DetEta_EM_Probe_Trig_All_Triglist", 100, 0., 100., 31, -3.1, 3.1},
		      {"Pt_DetEta_EM_Probe_Trig_All", 100, 0., 100., 31, -3.1, 3.1},
		      {"Pt_DetEta_EM_Probe_Trig_Matched_Triglist", 100, 0., 100., 31, -3.1, 3.1},
		      {"Pt_DetEta_EM_Probe_Trig_Matched", 100, 0., 100., 31, -3.1, 3.1},
		      {"Pt_PhysEta_EM_Probe_Trig_All_Triglist", 100, 0., 100., 31, -3.1, 3.1},
		      {"Pt_PhysEta_EM_Probe_Trig_All", 100, 0., 100., 31, -3.1, 3.1},
		      {"Pt_PhysEta_EM_Probe_Trig_Matched_Triglist", 100, 0., 100., 31, -3.1, 3.1},
		      {"Pt_PhysEta_EM_Probe_Trig_Matched", 100, 0., 100., 31, -3.1, 3.1},
		      {"InvMass_DetEta_EM_Probe_Trig_All_Triglist", 150, 0., 150., 31, -3.1, 3.1},
		      {"InvMass_DetEta_EM_Probe_Trig_All", 150, 0., 150., 31, -3.1, 3.1},
		      {"InvMass_DetEta_EM_Probe_Trig_Matched_Triglist", 150, 0., 150., 31, -3.1, 3.1},
		      {"InvMass_DetEta_EM_Probe_Trig_Matched", 150, 0., 150., 31, -3.1, 3.1},
		      {"InvMass_PhysEta_EM_Probe_Trig_All_Triglist", 150, 0., 150., 31, -3.1, 3.1},
		      {"InvMass_PhysEta_EM_Probe_Trig_All", 150, 0., 150., 31, -3.1, 3.1},
		      {"InvMass_PhysEta_EM_Probe_Trig_Matched_Triglist", 150, 0., 150., 31, -3.1, 3.1},
		      {"InvMass_PhysEta_EM_Probe_Trig_Matched", 150, 0., 150., 31, -3.1, 3.1},
		      {"Pt_InvMass_EM_Probe_Trig_All_Triglist", 100, 0., 100., 150, 0., 150.},
		      {"Pt_InvMass_EM_Probe_Trig_All", 100, 0., 100.,150, 0., 150.},
		      {"Pt_InvMass_EM_Probe_Trig_Matched_Triglist", 100, 0., 100.,150, 0., 150.},
		      {"Pt_InvMass_EM_Probe_Trig_Matched", 100, 0., 100.,150, 0., 150.},
		      
		      //trk eff
		      {"EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_Eta_CC",36,-60,60,31,-3.1,3.1},
		      {"EMEta_EM_Probe_Trk_All_Vtx_Eta_CC",36,-60,60,31,-3.1,3.1},
		      {"EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_Eta_EC",36,-60,60,31,-3.1,3.1},
		      {"EMEta_EM_Probe_Trk_All_Vtx_Eta_EC",36,-60,60,31,-3.1,3.1},
		      {"EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx_DetEta_CC",36,-60,60,31,-3.1,3.1},
		      {"EMDetEta_EM_Probe_Trk_All_Vtx_DetEta_CC",36,-60,60,31,-3.1,3.1},
		      {"EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx_DetEta_EC",36,-60,60,31,-3.1,3.1},
		      {"EMDetEta_EM_Probe_Trk_All_Vtx_DetEta_EC",36,-60,60,31,-3.1,3.1},


		      //loose trk eff
		      {"loose_EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_Eta_CC",36,-60,60,31,-3.1,3.1},
		      {"loose_EMEta_EM_Probe_Trk_All_Vtx_Eta_CC",36,-60,60,31,-3.1,3.1},
		      {"loose_EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_Eta_EC",36,-60,60,31,-3.1,3.1},
		      {"loose_EMEta_EM_Probe_Trk_All_Vtx_Eta_EC",36,-60,60,31,-3.1,3.1},
		      {"loose_EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx_DetEta_CC",36,-60,60,31,-3.1,3.1},
		      {"loose_EMDetEta_EM_Probe_Trk_All_Vtx_DetEta_CC",36,-60,60,31,-3.1,3.1},
		      {"loose_EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx_DetEta_EC",36,-60,60,31,-3.1,3.1},
		      {"loose_EMDetEta_EM_Probe_Trk_All_Vtx_DetEta_EC",36,-60,60,31,-3.1,3.1},
              //
			  {"loose_ZMass_vs_DetEta_Before_Trk_CC",31,-3.1,3.1 , 150, 0., 150.},
			  {"loose_ZMass_vs_Eta_Before_Trk_CC",31,-3.1,3.1 , 150, 0., 150.},
			  {"loose_ZMass_vs_DetEta_After_Trk_CC",31,-3.1,3.1 , 150, 0., 150.},
			  {"loose_ZMass_vs_Eta_After_Trk_CC",31,-3.1,3.1 , 150, 0., 150.},
			  {"loose_ZMass_vs_DetEta_Before_Trk_TAG",31,-3.1,3.1 , 150, 0., 150.},
			  {"loose_ZMass_vs_Eta_Before_Trk_TAG",31,-3.1,3.1 , 150, 0., 150.},

		      //Preselection 2D plots
                      {"ZMass_vs_Eta_Before_Presel_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_Before_Presel_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_Before_Presel_CC",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Vtx_Before_Presel_CC",  24, -60., 60., 150, 0., 150.},

                      {"ZMass_vs_Eta_After_Presel_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_After_Presel_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_After_Presel_CC",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Vtx_After_Presel_CC",  24, -60., 60., 150, 0., 150.},

		      {"ZMass_vs_Eta_Before_Presel_EC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_Before_Presel_EC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_Before_Presel_EC",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Vtx_Before_Presel_EC",  24, -60., 60., 150, 0., 150.},

                      {"ZMass_vs_Eta_After_Presel_EC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_After_Presel_EC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_After_Presel_EC",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Vtx_After_Presel_EC",  24, -60., 60., 150, 0., 150.},

		      //Preselection 2D Background plots

		      {"QCDZMass_vs_Eta_Before_Presel_CC", 31, -3.1, 3.1, 180, 0., 180.},
                      {"QCDZMass_vs_DetEta_Before_Presel_CC", 31, -3.1, 3.1, 180, 0., 180.},
                      {"QCDZMass_vs_Pt_Before_Presel_CC",  100, 0., 100., 180, 0., 180.},
                      {"QCDZMass_vs_Vtx_Before_Presel_CC",  24, -60., 60., 180, 0., 180.},

                      {"QCDZMass_vs_Eta_After_Presel_CC", 31, -3.1, 3.1, 180, 0., 180.},
                      {"QCDZMass_vs_DetEta_After_Presel_CC", 31, -3.1, 3.1, 180, 0., 180.},
                      {"QCDZMass_vs_Pt_After_Presel_CC",  100, 0., 100., 180, 0., 180.},
                      {"QCDZMass_vs_Vtx_After_Presel_CC",  24, -60., 60., 180, 0., 180.},

		      {"QCDZMass_vs_Eta_Before_Presel_EC", 31, -3.1, 3.1, 180, 0., 180.},
                      {"QCDZMass_vs_DetEta_Before_Presel_EC", 31, -3.1, 3.1, 180, 0., 180.},
                      {"QCDZMass_vs_Pt_Before_Presel_EC",  100, 0., 100., 180, 0., 180.},
                      {"QCDZMass_vs_Vtx_Before_Presel_EC",  24, -60., 60., 180, 0., 180.},

                      {"QCDZMass_vs_Eta_After_Presel_EC", 31, -3.1, 3.1, 180, 0., 180.},
                      {"QCDZMass_vs_DetEta_After_Presel_EC", 31, -3.1, 3.1, 180, 0., 180.},
                      {"QCDZMass_vs_Pt_After_Presel_EC",  100, 0., 100., 180, 0., 180.},
                      {"QCDZMass_vs_Vtx_After_Presel_EC",  24, -60., 60., 180, 0., 180.},

		      
		      



		      //HMx 2D plots
                      {"ZMass_vs_Eta_Before_HMx_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_Before_HMx_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_Before_HMx_CC",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Vtx_Before_HMx_CC",  24, -60., 60., 150, 0., 150.},

                      {"ZMass_vs_Eta_After_HMx_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_After_HMx_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_After_HMx_CC",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Vtx_After_HMx_CC",  24, -60., 60., 150, 0., 150.},
 
		      {"Eta_vs_Pt_Before_HMx_CC",  100, 0., 100., 31, -3.1, 3.1},
                      {"Eta_vs_Pt_After_HMx_CC",  100, 0., 100., 31, -3.1, 3.1},

		      {"ZMass_vs_Eta_Before_HMx_EC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_Before_HMx_EC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_Before_HMx_EC",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Vtx_Before_HMx_EC",  24, -60., 60., 150, 0., 150.},

                      {"ZMass_vs_Eta_After_HMx_EC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_After_HMx_EC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_After_HMx_EC",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Vtx_After_HMx_EC",  24, -60., 60., 150, 0., 150.},

		      {"EMEta_beforeHMx_Vtx_Eta_CC",36,-60,60,31,-3.1,3.1},
                      {"EMEta_afterHMx_Vtx_Eta_CC",36,-60,60,31,-3.1,3.1},
                      {"EMEta_beforeHMx_Vtx_Eta_EC",36,-60,60,31,-3.1,3.1},
                      {"EMEta_afterHMx_Vtx_Eta_EC",36,-60,60,31,-3.1,3.1},
                      {"EMDetEta_beforeHMx_Vtx_DetEta_CC",36,-60,60,31,-3.1,3.1},
                      {"EMDetEta_afterHMx_Vtx_DetEta_CC",36,-60,60,31,-3.1,3.1},
                      {"EMDetEta_beforeHMx_Vtx_DetEta_EC",36,-60,60,31,-3.1,3.1},
                      {"EMDetEta_afterHMx_Vtx_DetEta_EC",36,-60,60,31,-3.1,3.1},

		      //Trk 2D plots
                      {"ZMass_vs_Eta_Before_Trk_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_Before_Trk_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_Before_Trk_CC",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Vtx_Before_Trk_CC",  24, -60., 60., 150, 0., 150.},
                      {"ZMass_vs_Eta_Before_Trk_TAG", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_Before_Trk_TAG", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_Before_Trk_TAG",  100, 0., 100., 150, 0., 150.},

                      {"ZMass_vs_Eta_After_Trk_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_DetEta_After_Trk_CC", 31, -3.1, 3.1, 150, 0., 150.},
                      {"ZMass_vs_Pt_After_Trk_CC",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Vtx_After_Trk_CC",  24, -60., 60., 150, 0., 150.},

                      //tagprobe
                      {"EMPt_vs_DetEta_tagprobe", 62, -3.1, 3.1, 100, 0., 100.},
                      {"EMPt_vs_DetEta_emfrac_iso_tagprobe", 62, -3.1, 3.1, 100, 0., 100.},
                      {"EMPt_vs_DetEta_emfrac_iso_Hmx7_tagprobe", 62, -3.1, 3.1, 100, 0., 100.},
                      {"EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_tagprobe", 62, -3.1, 3.1, 100, 0., 100.},
                      {"EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_smt_tagprobe", 62, -3.1, 3.1, 100, 0., 100.},
                      {"EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_smt_trkpT_tagprobe", 62, -3.1, 3.1, 100, 0., 100.},


		      ////hmx eff pT, Eta & SET dependence
                      {"ZMass_vs_Pt_Before_HMx_CC_Etabin",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_vs_Pt_After_HMx_CC_Etabin",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_V_Pt_EM_Probe_HMx_All_SETbin",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_V_Pt_EM_Probe_HMx_Matched_SETbin",  100, 0., 100., 150, 0., 150.},

		      ////trk eff pT, Eta & SET dependence
                      {"ZMass_V_Pt_EM_Probe_Trk_All_Etabin",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_V_Pt_EM_Probe_Trk_Matched_Etabin",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_V_Pt_EM_Probe_Trk_All_SETbin",  100, 0., 100., 150, 0., 150.},
                      {"ZMass_V_Pt_EM_Probe_Trk_Matched_SETbin",  100, 0., 100., 150, 0., 150.},
		      {"ZMass_V_Pt_Bkgd_Etabin",  100, 0., 100., 150, 0., 150.},
		      {"ZMass_V_Vtx_Bkgd_Etabin",  320, -80., 80., 150, 0., 150.},
		      {"ZMass_V_Pt_Bkgd_SETbin",  100, 0., 100., 150, 0., 150.},
                      {"", 0, 0, 0, 0, 0, 0}};


// histograms used for FakeAnalysis
static HIST_1D Fake_Hist[]={
		      // for both spatial only and spatial+E/P
		      {"Fake_Electron_DetEta", 31, -3.1, 3.1},             //Fake electron DetEta, without track requirement
		      {"Fake_Electron_Eta", 31, -3.1, 3.1},                //Fake electron DetEta, without track requirement
		      {"Fake_Electron_Pt", 100, 0., 100.},                 //Fake electron DetEta, without track requirement
		      {"Fake_Met", 100, 0., 50.},                          //MET without track requirement
		      {"Fake_Electron_DetEta_CCVtxBin", 31, -3.1, 3.1},
                      // spatial track matching + E/P
		      {"Fake_Electron_DetEta_Match", 31, -3.1, 3.1},       //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Eta_Match", 31, -3.1, 3.1},          //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Pt_Match", 100, 0., 100.},           //Fake electron DetEta, with track requirement
		      {"Fake_Met_Match", 100, 0., 50.},                    //MET with track requirement
		      // spatial track matching
		      {"Fake_Electron_DetEta_Spatial_Match", 31, -3.1, 3.1},       //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Eta_Spatial_Match", 31, -3.1, 3.1},          //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Pt_Spatial_Match", 100, 0., 100.},           //Fake electron DetEta, with track requirement
		      {"Fake_Met_Spatial_Match", 100, 0., 50.},                    //MET with track requirement
		      // spatial track matching +SMT+CFT hits
		      {"Fake_Electron_DetEta_Spatial_Match_Tight", 31, -3.1, 3.1},       //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Eta_Spatial_Match_Tight", 31, -3.1, 3.1},          //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Pt_Spatial_Match_Tight", 100, 0., 100.},           //Fake electron DetEta, with track requirement
		      {"Fake_Met_Spatial_Match_Tight", 100, 0., 50.},                    //MET with track requirement
		      {"Fake_Electron_DetEta_CCVtxBin_Spatial_Match", 31, -3.1, 3.1},
		      // for both spatial only and spatial+E/P after missing Et cut
		      {"Fake_Electron_DetEta_MetCut", 31, -3.1, 3.1},             //Fake electron DetEta, without track requirement
		      {"Fake_Electron_Eta_MetCut", 31, -3.1, 3.1},                //Fake electron DetEta, without track requirement
		      {"Fake_Electron_Pt_MetCut", 100, 0., 100.},                 //Fake electron DetEta, without track requirement
                      // spatial track matching + E/P
		      {"Fake_Electron_DetEta_Match_MetCut", 31, -3.1, 3.1},       //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Eta_Match_MetCut", 31, -3.1, 3.1},          //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Pt_Match_MetCut", 100, 0., 100.},           //Fake electron DetEta, with track requirement
		      // spatial track matching
		      {"Fake_Electron_DetEta_Spatial_Match_MetCut", 31, -3.1, 3.1},       //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Eta_Spatial_Match_MetCut", 31, -3.1, 3.1},          //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Pt_Spatial_Match_MetCut", 100, 0., 100.},           //Fake electron DetEta, with track requirement
		      // spatial track matching +SMT+CFT hits
		      {"Fake_Electron_DetEta_Spatial_Match_Tight_MetCut", 31, -3.1, 3.1},       //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Eta_Spatial_Match_Tight_MetCut", 31, -3.1, 3.1},          //Fake electron DetEta, with track requirement
		      {"Fake_Electron_Pt_Spatial_Match_Tight_MetCut", 100, 0., 100.},           //Fake electron DetEta, with track requirement
		      // chi2 distribution
		      {"Fake_Electron_Chi2", 200, 0., 0.2},
		      {"Fake_Electron_Chi2_Tight", 200, 0., 0.2},
		      {"", 0, 0, 0}};

// histograms used for FakeAnalysis
static HIST_2D Fake_Hist_2D[]={
                      {"Fake_Electron_Chi2_V_Met_Spatial_Match", 100, 0., 20., 400, 0.0, 0.8},        //Fake electron DetEta, without track requirement
                      {"Fake_Electron_Chi2_V_Met_Spatial_Match_Tight", 100, 0., 20., 400, 0.0, 0.8},  //Fake electron DetEta, without track requirement
		      {"", 0, 0, 0, 0, 0, 0}};

//histograms used for Ratio Method
static HIST_1D RatioMethod_Hist[]={
                      // distribution for different regions
                      // _0 for CCCC, _1 for CCEC, _2 for ECEC, no index for all
                      {"WCandVtx", 320, -80., 80.},
                      {"WCandNPV", 30,0,30},
                      {"WCandTick", 150,0,150},
                      {"WCandInstLumi", 250, 0., 10.},
                      {"WCandElecPt", 200, 0., 100.},
                      {"WCandMet", 200, 0., 100.},
                      {"WCandMt", 300, 50., 200.},
                      {"WCandPt", 100, 0., 50.},
                      {"WCandElecEta", 60, -3., 3.},
                      {"WCandElecDetEta", 60, -3., 3.},
                      {"WCandnuEta", 60, -3., 3.},
                      {"WCandnuDetEta", 60, -3., 3.},
                      {"WCandEta", 60, -4., 4.},
                      {"ElecThetaStar", 60, -1., 1.},
                      {"PosiThetaStar", 60, -1., 1.},
                      {"ThetaStar", 60, -1., 1.},
                      {"WCandMass", 200, 50., 150.},
                      {"", 0, 0, 0}};

static HIST_2D RatioMethod_2D[]={
  {"BosonRapidity_V_costhetastar1", 60, -4, 4., 60, -1., 1.},        //Fake electron DetEta, without track requirement
  {"BosonRapidity_V_costhetastar2", 60, -4, 4., 60, -1., 1.},  //Fake electron DetEta, without track requirement
                      {"", 0, 0, 0, 0, 0, 0}};

// histograms used for ZAnalysis
static HIST_1D ZCand_Hist[]={
		      // distribution for different regions 
		      // _0 for CCCC, _1 for CCEC, _2 for ECEC, no index for all 
		      {"ZCandElecE", 600, 0., 200.},
		      {"ZCandElecPx", 400, -200., 200.},
		      {"ZCandElecPy", 400, -200., 200.},
		      {"ZCandElecPz", 400, -200., 200.},
		      {"ZCandElecPt", 300, 0., 100.},
		      {"ZCandElecPt_Upara", 300, 0., 100.},
		      {"ZCandElec0Px", 400, -200., 200.},
		      {"ZCandElec1Px", 400, -200., 200.},
		      {"ZCandElec0Py", 400, -200., 200.},
		      {"ZCandElec1Py", 400, -200., 200.},
		      {"ZCandElec0Pz", 400, -200., 200.},
		      {"ZCandElec1Pz", 400, -200., 200.},
            {"ZCandElec0Pt", 300, 0., 100.},
            {"ZCandElec1Pt", 300, 0., 100.},
            {"ZCandElecPt_bin", 300, 0., 100.},
            {"ZCandElec0Pt_bin", 300, 0., 100.},
            {"ZCandElec1Pt_bin", 300, 0., 100.},
            {"ZCandDiffElecPt", 200, -10., 10.},
            {"ZCandDiffElec0Pt", 200, -10., 10.},
            {"ZCandDiffElec1Pt", 200, -10., 10.},
            {"ZCandDiffElecPt_bin", 200, -10., 10.},
            {"ZCandDiffElec0Pt_bin", 200, -10., 10.},
            {"ZCandDiffElec1Pt_bin", 200, -10., 10.},
            {"ZCandElecGenPt", 300, 0., 100.},
            {"ZCandElecGen0Pt", 300, 0., 100.},
            {"ZCandElecGen1Pt", 300, 0., 100.},
            {"ZCandElecGenPt_bin", 300, 0., 100.},
            {"ZCandElecGen0Pt_bin", 300, 0., 100.},
            {"ZCandElecGen1Pt_bin", 300, 0., 100.},
            {"ZCandElecRawGenPt", 300, 0., 100.},
            {"ZCandElecRawGen0Pt", 300, 0., 100.},
            {"ZCandElecRawGen1Pt", 300, 0., 100.},
            {"ZCandElecRawGenPt_bin", 300, 0., 100.},
            {"ZCandElecRawGen0Pt_bin", 300, 0., 100.},
            {"ZCandElecRawGen1Pt_bin", 300, 0., 100.},

            {"ZCandElec0E", 600, 0., 200.},
            {"ZCandElec1E", 600, 0., 200.},
            {"ZCandElecE_bin", 600, 0., 200.},
            {"ZCandElec0E_bin", 600, 0., 200.},
            {"ZCandElec1E_bin", 600, 0., 200.},
            {"ZCandDiffElecE", 200, -10., 10.},
            {"ZCandDiffElec0E", 200, -10., 10.},
            {"ZCandDiffElec1E", 200, -10., 10.},
            {"ZCandDiffElecE_bin", 200, -10., 10.},
            {"ZCandDiffElec0E_bin", 200, -10., 10.},
            {"ZCandDiffElec1E_bin", 200, -10., 10.},
            {"ZCandElecGenE", 600, 0., 200.},
            {"ZCandElecGen0E", 600, 0., 200.},
            {"ZCandElecGen1E", 600, 0., 200.},
            {"ZCandElecGenE_bin", 600, 0., 200.},
            {"ZCandElecGen0E_bin", 600, 0., 200.},
            {"ZCandElecGen1E_bin", 600, 0., 200.},
            {"ZCandElecRawGenE", 600, 0., 200.},
            {"ZCandElecRawGen0E", 600, 0., 200.},
            {"ZCandElecRawGen1E", 600, 0., 200.},
            {"ZCandElecRawGenE_bin", 600, 0., 200.},
            {"ZCandElecRawGen0E_bin", 600, 0., 200.},
            {"ZCandElecRawGen1E_bin", 600, 0., 200.},

            {"ZCandElecTrkPt", 300, 0., 100.},
		      {"ZCandElecTrkPtTight", 300, 0., 100.},
		      {"ZCandElecEta", 60, -3., 3.},
		      {"ZCandElecDetEta", 60, -3., 3.},
		      {"ZCandElecPhi", 64, 0., TMath::TwoPi()},
		      {"ZCandElecDetPhi", 64, 0., TMath::TwoPi()},
		      {"ZCandElecTrkPhiEM3", 64, 0., TMath::TwoPi()},
              {"ZCandElecPhiTrkAtDCA", 64, 0., TMath::TwoPi()},
              {"ZCandElecPhiTrkAtEM3", 64, 0., TMath::TwoPi()},
              {"ZCandElecDetPhiCALO", 64, 0., TMath::TwoPi()},
		      {"ZCandPt", 150, 0., 50.},
		      {"ZCandPx", 150, -100., 100.},
		      {"ZCandPy", 150, -100., 100.},
		      {"ZCandPz", 150, -100., 100.},
		      {"ZCandAt", 150, 0., 50.},
                      {"ZCandAl", 150, 0., 50.},
		      {"ZCandMCPt", 100, 0., 50.},
		      {"ZCandMCPtDiff", 200, -10., 10.},
            {"ZCandMCPhiDiff", 200, -TMath::Pi(), TMath::Pi()},
		      {"ZCandEta", 200, -10., 10.},
		      {"ZCandPhi", 64, 0., TMath::TwoPi()},
		      {"ZCandMass", 400, 50., 150.}, // mass calculated using cal+track information
            {"ZCandDiffMass", 200, -10., 10.}, // mass diff
		      {"ZCandEMTrkMass", 400, 50., 150.},
		      {"ZCandVtx", 320, -80., 80.},
            {"ZCandNPV", 30,0,30},
            {"ZCandTick", 150,0,150},
		      {"ZCandMass_Trks", 400, 50., 150.},
		      {"ZCandMass_CCCC_Trks", 400, 50., 150.},
		      {"ZCandMass_CCEC_Trks", 400, 50., 150.},
		      {"ZCandMass_ECEC_Trks", 400, 50., 150.},
		      {"ZCandMass_TwoTrks", 400, 50., 150.},
		      {"ZCandTrksMass", 400, 50., 150.},  // mass calculated using tracker information only
		      {"ZCandMass_Cal", 400, 50., 150.}, // mass calculated using cal information only
		      {"ZCandMass_Trks_Cal", 400, 50., 150.},
		      {"ZCandMass_CCCC_Trks_Cal", 400, 50., 150.},
		      {"ZCandMass_CCEC_Trks_Cal", 400, 50., 150.},
		      {"ZCandMass_ECEC_Trks_Cal", 400, 50., 150.},
                      {"ZCandMassWide", 400, 50., 150.},
                      {"ZCandMassWide_CCCC_Trks", 400, 50., 150.},
                      {"ZCandMassWide_CCEC_Trks", 400, 50., 150.},
                      {"ZCandMassWide_ECEC_Trks", 400, 50., 150.},
		      // recoil system
		      {"ZCandRecoilPt", 150, 0., 50.},
		      {"ZCandRecoilPhi", 64, 0., TMath::TwoPi()},
		      {"ZCandRecoilPx", 150, -50., 50.},
		      {"ZCandRecoilPy", 150, -50., 50.},
		      {"ZCandRecoilPt_bin", 150, 0., 50.},
		      {"ZCandRecoilPhi_bin", 64, 0., TMath::TwoPi()},
		      {"ZCandRecoilPt_ZPt_Projected_bin", 150, 0., 50.},
		      {"ZCandRecoilPhi_ZPt_Projected_bin", 64, 0., TMath::TwoPi()},
		      {"ZCandRecoilPt_genZPt_bin", 150, 0., 50.},
		      {"ZCandRecoilPhi_genZPt_bin", 64, 0., TMath::TwoPi()},
		      {"ZCandRecoilPx_bin", 150, -50., 50.},
		      {"ZCandRecoilPy_bin", 150, -50., 50.},
		      // met
		      {"ZCandMet", 150, 0., 50.},
		      {"ZCandMetPhi", 64, 0., TMath::TwoPi()},
		      {"ZCandMetX", 150, -50., 50.},
		      {"ZCandMetY", 150, -50., 50.},
		      {"ZCandMet_bin", 150, 0., 50.},
		      {"ZCandMetPhi_bin", 64, 0., TMath::TwoPi()},
		      {"ZCandMetX_bin", 150, -50., 50.},
		      {"ZCandMetY_bin", 150, -50., 50.},
		      {"ZCandMass_TwoTrks_Category", 400, 50., 150.},  // Z mass distribution for two spatial track matching and divide into different detector eta regions
		      {"ZCandElecPt_TwoTrks_Category", 300, 0., 100.},
		      {"ZCandElecPt_TwoTrks_Both", 300, 0., 100.},
		      {"ZCandElecPt_TwoTrks_Elec1", 300, 0., 100.},
		      {"ZCandElecPt_TwoTrks_Elec2", 300, 0., 100.},
		      // uparallel and uperpendicular
		      {"ZCandElecUPara", 120, -30., 30.},
		      {"ZCandElecUPerp", 120, -30., 30.},
                      // open angle between EM+recoil, EM+MET
                      {"ZCandDeltaPhi_EM_Recoil", 64, 0., TMath::Pi()},
                      {"ZCandDeltaPhi_EM_Met", 64, 0., TMath::Pi()},

		      {"ZCandPee_eta", 150, 0., 50.},
		      {"ZCandDeltaPhi_EM1_EM2", 64, 0, TMath::TwoPi()},

                      {"ZCandCosDeltaPhi_EM1_EM2", 100, -1 , -0.6 },
                      {"ZCandCosDeltaPhi_EM1_EM2_bin", 100, -1 , -0.6 },

                      {"ZCandDiffCosDeltaPhi_EM1_EM2", 100, -0.002 , 0.002 },
                      {"ZCandDiffCosDeltaPhi_EM1_EM2_bin", 100, -0.005 , 0.005 },

                      {"ZCandDeltaEta_EM1_EM2", 100, -1 , 1 },
                      {"ZCandDeltaEta_EM1_EM2_bin", 100, -1 , 1 },

                      {"ZCandDiffDeltaEta_EM1_EM2", 100, -0.02 , 0.02 },
                      {"ZCandDiffDeltaEta_EM1_EM2_bin", 100, -0.02 , 0.02 },

                      {"ZCandDeltaPhi_Recoil_Met", 64, 0., TMath::Pi()},
                      {"ZCandDeltaPhi_Z_Recoil", 64, 0., TMath::Pi()},
                      {"ZCandDeltaPhi_Z_Met", 64, 0., TMath::Pi()},
                      {"ZCandDeltaPhi_Z_Recoil_bin", 64, 0., TMath::Pi()},
                      {"ZCandDeltaPhi_Z_Met_bin", 64, 0., TMath::Pi()},
                      {"ZCandDeltaPhi_EM1_EM2_bin", 64, 0., TMath::Pi()},
		      // eta and phi balances
		      {"ZCandEtaBalance", 150, -25., 25.},      // eta imbalance
		      {"ZCandXiBalance", 150, -25., 25.},       // xi imbalance
		      {"ZCandEtaImBalance", 150, -25., 25.},      // eta balance
		      {"ZCandXiImBalance", 150, -25., 25.},       // xi balance

		      {"ZCandEtaImBalance_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandXiImBalance_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandEtaImBalance_ZPt_Projected_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandXiImBalance_ZPt_Projected_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandEtaImBalance_genZPt_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandXiImBalance_genZPt_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandMCPtDiff_bin", 200, -10., 10.},      // MC Z pT - reconstructed Z pT
            {"ZCandMCPhiDiff_bin", 200, -TMath::Pi(), TMath::Pi()},      // MC Z phi - reconstructed Z phi
            {"ZCandMass_bin", 400, 50., 150.},      // Mee in ptZ bins
            {"ZCandDiffMass_bin", 200, -10., 10.},      // Mee in ptZ bins
		      {"ZCandMCPtDiff_genZPt_bin", 200, -10., 10.},      // MC Z pT - reconstructed Z pT
		      {"ZCandNewEtaBalance_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandNewXiBalance_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandNewEtaBalance_ZPt_Projected_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandNewXiBalance_ZPt_Projected_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandNewEtaBalance_genZPt_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandNewXiBalance_genZPt_bin", 150, -25., 25.},      // eta imbalance bin
		      {"ZCandPt_bin", 150, 0., 50.},
                      {"ZCandPhi_bin", 64, 0., TMath::TwoPi()},
		      {"ZCandPt_Projected_bin", 150, 0., 50.},
		      {"ZCandPee_eta_bin", 150, 0., 50.},
		      {"ZCandEtaBalance_bin", 150, -25., 25.},      // eta balance bin
		      {"ZCandXiBalance_bin", 150, -25., 25.},      // eta balance bin 
		      // E/p distributions
                      {"ZCandEOverP", 100, 0., 3.}, 
                      {"ZCandRawEOverP", 100, 0., 3.}, 
                      {"ZCandEOverP_Mod", 100, 0., 3.}, 
                      {"ZCandEOverP_TrkMod", 100, 0., 3.}, 
                      {"ZCandRawEOverP_Mod", 100, 0., 3.}, 
                      {"ZCandRawEOverP_TrkMod", 100, 0., 3.}, 
		      // instantaneous luminosity
		      {"ZCandInstLumi", 250, 0., 10.},
		      {"ZCandNCaloCells", 200, 0., 7000.},
		      {"ZCandfZ_CCCC", 120, 0., 3.},
		      {"ZCandfZ_CCEC", 120, 0., 3.},
		      {"ZCandfZ_ECEC", 120, 0., 3.},
                      // energy and pT for 0.2<R<0.4, mainly from underlying events
                      {"ZCandElecEnergyCoreCone", 100, 0., 10.},
                      {"ZCandElecPtCoreCone", 100, 0., 10.},
		      {"ZCandRecoil_CCCC_2trks",100,0.,100.},
		      {"ZcandElecPt_fz", 100, 20., 70.},
		      {"ZcandElecE_fz", 200, 20., 120.},
		      {"ZcandElecEta_fz", 60, -3., 3.},
		      {"ZcandElecDetEta_fz", 60, -3., 3.},
		      {"ZcandMass_CCCC_fz", 400, 50., 150.},
		      {"ZcandMass_CCCC_fz_Coarse", 400, 50., 150.},
		      {"ZcandElecPt_fz_Coarse", 100, 20., 70.},
		      {"ZcandElecE_fz_Coarse", 200, 20., 120.},
		      {"ZcandElecEta_fz_Coarse", 60, -3., 3.},
		      {"ZcandElecDetEta_fz_Coarse", 60, -3., 3.},

		      // scalar Et
		      {"ZCandScalarEt", 300, 0., 300.},
		      {"ZCandSqrtScalarEt", 400, 0., 15.},
		      {"ZCandScalarEt_ZPtBin", 300, 0., 300.},
		      {"ZCandSqrtScalarEt_ZPtBin", 400, 0., 15.},
		      {"ZCandScalarEt_genZPt_bin", 300, 0., 300.},
		      {"ZCandSqrtScalarEt_genZPt_bin", 400, 0., 15.},
		      // study track extrapolation
		      {"ZCandEMTrkPhiDiff_Positron", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_Positron", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDiff_Positron_PosSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_Positron_PosSolpol", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDiff_Positron_NegSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_Positron_NegSolpol", 100, -0.08, 0.08},

		      {"ZCandEMTrkPhiDiff_Electron", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_Electron", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDiff_Electron_PosSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_Electron_PosSolpol", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDiff_Electron_NegSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_Electron_NegSolpol", 100, -0.08, 0.08},

		      {"ZCandEMTrkPhiDCADiff_Electron", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDCADiff_Electron", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDCADiff_Electron_PosSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDCADiff_Electron_PosSolpol", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDCADiff_Electron_NegSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDCADiff_Electron_NegSolpol", 100, -0.08, 0.08},

		      {"ZCandEMTrkPhiDCADiff_Positron", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDCADiff_Positron", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDCADiff_Positron_PosSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDCADiff_Positron_PosSolpol", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDCADiff_Positron_NegSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDCADiff_Positron_NegSolpol", 100, -0.08, 0.08},

		      // for generator level
		      {"ZCandEMTrkPhiDiff_gen_Positron", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_gen_Positron", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDiff_gen_Positron_PosSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_gen_Positron_PosSolpol", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDiff_gen_Positron_NegSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_gen_Positron_NegSolpol", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDiff_gen_Electron", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_gen_Electron", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDiff_gen_Electron_PosSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_gen_Electron_PosSolpol", 100, -0.08, 0.08},
		      {"ZCandEMTrkPhiDiff_gen_Electron_NegSolpol", 100, -0.015, 0.015},
		      {"ZCandEMTrkPhiModDiff_gen_Electron_NegSolpol", 100, -0.08, 0.08},

		      // study phi crack efficiency
		      {"ZCandElecPhiMod", 50, 0., 1.},
		      {"ZCandElecTrkPhiModEM3", 50, 0., 1.},
		      {"ZCandEMTrkMass_PhiMod", 100, 50, 150},
		      {"ZCandTrkPhiMod_gen", 50, 0., 1.},
		      {"ZCandTrkPhiMod_gen_afterPhiFiducial", 50, 0., 1.},
		      {"ZCandTrkPhiMod", 50, 0., 1.},
		      {"ZCandTrkPhiMod_afterPhiFiducial", 50, 0., 1.},
		      {"ZCandElecPhiMod_PtCut", 50, 0., 1.},
		      {"ZCandTrkPhiMod_PtCut", 50, 0., 1.},
		      {"ZCandTrkPhiMod_afterPhiFiducial_PtCut", 50, 0., 1.},
		      {"ZCandCalTrkDeltaPhi", 200, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_pTBin", 200, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_EtaBin", 200, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_gen_pTBin", 200, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_gen_EtaBin", 200, -0.2, 0.2},
		      {"ZCandEMTrkDeltaR", 200, 0, 6.},
		      {"ZCandElecPhiMod2", 50, 0., 1.},
		      {"ZCandTrkPhiMod2", 50, 0., 1.},
		      {"ZCandTrkPhiMod2_afterPhiFiducial", 50, 0., 1.},
		      {"ZCandElecPhiMod2_PtCut", 50, 0., 1.},
		      {"ZCandTrkPhiMod2_PtCut", 50, 0., 1.},
		      {"ZCandTrkPhiMod2_afterPhiFiducial_PtCut", 50, 0., 1.},
		      {"ZCandCalTrkDeltaPhi2", 200, -0.2, 0.2},
		      // Z mass in different trigger list and different eta, deteta regions
		      {"ZCandMass_CCCC_TrigCategory", 400, 50, 150},
		      {"ZCandMass_CCCC_EtaCategory", 400, 50, 150},
		      {"ZCandMass_CCCC_DetEtaCategory", 400, 50, 150},
		      {"ZCandMass_CCCC_PhiModCategory", 400, 50, 150},
		      {"ZCandMass_CCCC_PhiMod", 50, 0., 1.},
		      {"ZCandMass_CCCC_TrkPhiEM3Mod", 50, 0., 1.},
		      {"ZCandMass_CCCC_TrkPhiModCategory", 400, 50, 150},
		      {"ZCandMass_CCCC_TrkPhiEM3ModCategory", 400, 50, 150},
		      {"ZCandMass_CCCC_EM3PhiEM3ModCategory", 400, 50, 150},
		      // generator-level Z boson pT
                      {"ZCandpT_gen", 100, 0., 50.},
                      {"ZCandpT_gen_selected", 100, 0., 50.},
                      {"ZCandpT_gen_selected_CCCC", 100, 0., 50.},
                      {"ZCandpT_gen_selected_CCEC", 100, 0., 50.},
                      {"ZCandpT_gen_selected_ECEC", 100, 0., 50.},
		      // track smearing studies
		      
		      {"ZCandElecTrkCalMass", 400, 50., 150.},
		      {"ZCandElecTrkCalMass_CC_EC", 400, 50., 150.},
		      {"ZCandElecTrkPtOvETight", 200, 0., 1.1},
		      {"ZCandElecTrkPtOvE", 200, 0., 1.1},
		      {"ZCandElecTrkPhiEM3Mod", 50, 0., 1.},
		      {"", 0, 0, 0}};

// histograms used for ZAnalysis
static HIST_PROFILE ZCand_Hist_Profile[]={
		      // distribution for different regions 
		      // _0 for CCCC, _1 for CCEC, _2 for ECEC, no index for all 
		      {"ZCandEtaPeeRecoil", 30, 0., 30., -60., 60., " "},    // pT_ee vs pT_recoil in eta axis
		      {"ZCandXiPeeRecoil", 30, 0., 30., -60., 60., " "},     // pT_ee vs pT_recoil in xi axis
		      {"ZCandEtaPeeBalance", 30, 0., 30., -30., 60., " "},    // pT_ee vs (pT_ee+pT_recoil) in eta axis
		      {"ZCandXiPeeBalance", 30, 0., 30., -30., 60., " "},     // pT_ee vs (pT_ee+pT_recoil) in xi axis
		      {"ZCandEtaPeeImBalance", 30, 0., 30., -30., 60., " "},    // pT_ee vs (pT_ee+pT_recoil/kappa) in eta axis
		      {"ZCandXiPeeImBalance", 30, 0., 30., -30., 60., " "},     // pT_ee vs (pT_ee+pT_recoil/kappa) in xi axis
		      {"ZCandKappaUE", 20, 0., 500., 0., 800., " "},          // Pow(P_ee, 2) vs Pow(P_e1 + P_e2 + MET, 2)
		      {"ZCandPt_V_HadResponse", 30, 0., 30., 0., 1.5, " "},   // Z boson pT vs hadronic response
		      // E/p distributions
		      {"ZCandEOverP_V_Et", 30, 25., 55., 0., 3., " "},    
		      {"ZCandEOverP_V_EMPhi_Electron", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"ZCandEOverP_V_TrkPhi_Electron", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"ZCandEOverP_V_EMPhi_Positron", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"ZCandEOverP_V_TrkPhi_Positron", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      // check E/p for physics and detector eta, phi after EM corrections
		      {"ZCandEOverP_V_ElecEta", 20, -1.5, 1.5, 0., 3., " "},    
		      {"ZCandEOverP_V_ElecDetEta", 20, -1.5, 1.5, 0., 3., " "},    
		      {"ZCandEOverP_V_ElecPhi", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"ZCandEOverP_V_ElecDetPhi", 32, 0., TMath::TwoPi(), 0., 3., " "},
		      {"ZCandEOverP_V_ElecTrkPhiEM3", 32, 0., TMath::TwoPi(), 0., 3., " "},
		      {"ZCandEOverP_V_ElecPhiMod", 40, 0., 1., 0., 3., " "},
		      {"ZCandEOverP_V_ElecTrkPhiMod", 40, 0., 1., 0., 3., " "},
		      // check E/p for physics and detector eta,phi before EM corrections
		      {"ZCandRawEOverP_V_ElecEta", 20, -1.5, 1.5, 0., 3., " "},    
		      {"ZCandRawEOverP_V_ElecDetEta", 20, -1.5, 1.5, 0., 3., " "},    
		      {"ZCandRawEOverP_V_ElecPhi", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"ZCandRawEOverP_V_ElecDetPhi", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"ZCandRawEOverP_V_ElecTrkPhiEM3", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"ZCandRawEOverP_V_ElecPhiMod", 40, 0., 1., 0., 3., " "},
		      {"ZCandRawEOverP_V_ElecTrkPhiMod", 40, 0., 1., 0., 3., " "},
                      // fZ vs mass
                      {"ZCandMass_V_fZ_CCCC_pro", 75, 1., 2.5, 60., 130., " "},
                      {"ZCandMass_V_fZ_CCEC_pro", 75, 1., 2.5, 60., 130., " "},
                      {"ZCandMass_V_fZ_ECEC_pro", 75, 1., 2.5, 60., 130., " "},
                      // energy and pT for 0.2<R<0.4 vs detector eta mainly from underlying events
                      {"ZCandElecEnergyCoreConeVDetEta", 22, -1.15, 1.15, 0., 100., " "},
                      {"ZCandElecPtCoreConeVDetEta", 22, -1.15, 1.15, 0., 100., " "},
		      // study track extrapolation
		      // for electron
		      {"ZCandEMTrkPhiDiffVTrkPhi_Electron", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhi_Electron", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCA_Electron", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiMod_Electron", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhiMod_Electron", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCAMod_Electron", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhi_Electron_PosSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhi_Electron_PosSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCA_Electron_PosSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiMod_Electron_PosSolpol", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhiMod_Electron_PosSolpol", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCAMod_Electron_PosSolpol", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhi_Electron_NegSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhi_Electron_NegSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCA_Electron_NegSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiMod_Electron_NegSolpol", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhiMod_Electron_NegSolpol", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCAMod_Electron_NegSolpol", 50, 0., 1., -1., 1., " "},
		      // for positron
		      {"ZCandEMTrkPhiDiffVTrkPhi_Positron", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhi_Positron", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCA_Positron", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiMod_Positron", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhiMod_Positron", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCAMod_Positron", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhi_Positron_PosSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhi_Positron_PosSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCA_Positron_PosSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiMod_Positron_PosSolpol", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhiMod_Positron_PosSolpol", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCAMod_Positron_PosSolpol", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhi_Positron_NegSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhi_Positron_NegSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCA_Positron_NegSolpol", 32, 0., 2*TMath::Pi(), -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiMod_Positron_NegSolpol", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVEMPhiMod_Positron_NegSolpol", 50, 0., 1., -1., 1., " "},
		      {"ZCandEMTrkPhiDiffVTrkPhiDCAMod_Positron_NegSolpol", 50, 0., 1., -1., 1., " "},
		      // study phi crack efficiency
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod2_pro", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pro", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pro_pTBin", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pro_EtaBin", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_PassPtTrkMatch", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin_PassPtTrkMatch", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin_PassPtTrkMatch", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_PassPt", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin_PassPt", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin_PassPt", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_PassTrkMatch", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_pTBin_PassTrkMatch", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pro_EtaBin_PassTrkMatch", 50, 0., 1., -0.2, 0.2, " "},
		      {"ZCandScalarEt_V_Lumi",100, 0., 10., 0., 300., " "},
		      {"", 0, 0, 0, 0, 0, " "}};

// histograms used by ZAnalysis for special Recoil Et flow studies
static HIST_1D ZCand2Trks_EtFlow_Hist[]={
  {"ZCand2Trks_EtFlow_genZPt",
   200, 0.0, 100.0},
  {"ZCand2Trks_EtFlow_recoZPt",
   200, 0.0, 100.0},
  {"ZCand2Trks_EtFlow_genUt",
   200, 0.0, 100.0},
  {"ZCand2Trks_EtFlow_recoUt",
   200, 0.0, 100.0},
  {"ZCand2Trks_EtFlow_recoRecoilPhi",
   100, 0.0, TMath::TwoPi()},
  {"ZCand2Trks_EtFlow_recoRecoilResp",
   200, 0.0, 10.0},
  {"ZCand2Trks_EtFlow_recoRecoilRespPrj",
   220, -10.0, 100.0},
  {"ZCand2Trks_EtFlow_DPhi_recoUt_genZPt",
   100, 0.0, TMath::Pi()},
  {"ZCand2Trks_EtFlow_DPhi_recoUt_recoZPt",
   100, 0.0, TMath::Pi()},
  {"ZCand2Trks_EtFlow_DPhi_CellsUt_recoUt",
   100, 0.0, TMath::Pi()},
  //  {"ZCand2Trks_EtFlow_DPhi_CellsScaledUt_recoUt",
  //   100, 0.0, TMath::Pi()},
  //  {"ZCand2Trks_EtFlow_DPhi_XCHECKrecoUt_recoUt",
  //   100, 0.0, TMath::Pi()},
  {"ZCand2Trks_EtFlow_CellsUt",
   200, 0.0, 100.0},
  //  {"ZCand2Trks_EtFlow_CellsScaledUt",
  //   200, 0.0, 100.0},
  {"ZCand2Trks_EtFlow_CellsRecoilPhi",
   200, 0.0, TMath::TwoPi()},
  //  {"ZCand2Trks_EtFlow_CellsScaledRecoilPhi",
  //   200, 0.0, TMath::TwoPi()},
  {"ZCand2Trks_EtFlow_CellsRecoilResp",
   200, 0.0, 10.0},
  //  {"ZCand2Trks_EtFlow_CellsScaledRecoilResp",
  //   200, 0.0, 10.0},
  {"ZCand2Trks_EtFlow_CellsRecoilRespPrj",
   220, -10.0, 100.0},
  //  {"ZCand2Trks_EtFlow_CellsScaledRecoilRespPrj",
  //   220, -10.0, 100.0},
  //  {"ZCand2Trks_EtFlow_XCHECKrecoRecoilRespPrj",
  //   220, -10.0, 100.0},
  {"", 0, 0, 0}};

// histograms used for ZAnalysis (special Recoil Et flow studies)
static HIST_PROFILE ZCand2Trks_EtFlow_Profile[]={
  {"ZCand2Trks_EtFlow_recoRecoilResp_V_genZPt",
   200, 0.0, 100.0, 0, 0, " "},
  {"ZCand2Trks_EtFlow_recoRecoilResp_V_recoZPt",
   200, 0.0, 100.0, 0, 0, " "},
  {"ZCand2Trks_EtFlow_recoRecoilRespPrj_V_genZPt",
   200, 0.0, 100.0, 0, 0, " "},
  {"ZCand2Trks_EtFlow_recoRecoilRespPrj_V_recoZPt",
   200, 0.0, 100.0, 0, 0, " "},
  {"ZCand2Trks_EtFlow_recoUt_V_DPhi_recoUt_genZPt",
   100, 0.0, TMath::Pi(), 0, 0, " "},
  {"ZCand2Trks_EtFlow_recoUt_V_DPhi_recoUt_recoZPt",
   100, 0.0, TMath::Pi(), 0, 0, " "},
  {"ZCand2Trks_EtFlow_CellsUt_V_DPhi_CellsUt_genZPt",
   100, 0.0, TMath::Pi(), 0, 0, " "},
  //  {"ZCand2Trks_EtFlow_CellsScaledUt_V_DPhi_CellsScaledUt_genZPt",
  //   100, 0.0, TMath::Pi(), 0, 0, " "},
  {"ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_genZPt",
   64, -31.0, 33.0, 0, 0, " "},
  //  {"ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_genZPt",
  //   64, -31.0, 33.0, 0, 0, " "},
  {"ZCand2Trks_EtFlow_AveEt_V_iphi_wrt_recoZPt",
   64, -31.0, 33.0, 0, 0, " "},
  //  {"ZCand2Trks_EtFlow_AveEtScaled_V_iphi_wrt_recoZPt",
  //   64, -31.0, 33.0, 0, 0, " "},
  {"", 0, 0, 0, 0, 0, " "}};

static HIST_PROFILE_2D ZCand2Trks_EtFlow_Profile_2D[]={
  {"ZCand2Trks_EtFlow_AveEt_V_iphi_V_genZPt",
   64, -31.0, 33.0, 200, 0., 100., 0, 0, " "},
  {"", 0, 0, 0, 0, 0, 0, 0, 0, " "}};

// histograms used for ZAnalysis (special Recoil Et flow studies)
#define _NPTBINS_ 27
#define _PTBINS_  {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,18,21,24,27,30,35,40,50,60,70,80,90}
static HIST_PROFILE_VARBIN ZCand2Trks_EtFlow_Profile_VarX[]={
  {"ZCand2Trks_EtFlow_genZPt_V_genZPt", 
   _NPTBINS_, _PTBINS_, 0.0, 100.0, " "},
  {"ZCand2Trks_EtFlow_recoZPt_V_recoZPt", 
   _NPTBINS_, _PTBINS_, 0.0, 100.0, " "},
  {"", 0, {0}, 0, 0, " "}};
#undef _NPTBINS_
#undef _PTBINS_

//more histograms for loose track Efficiency studies
#define _NPTBINS_ 23
#define _PTBINS_  {0,25,27,29,31,33,35,37,39,41, 43,45,47,49,51,53,57,61,65,70, 75,80,90,100}
static HIST_2D_VARBIN_Y Eff_Hist_varbinY_2D[]={
	{"loose_ZMass_vs_Pt_Before_Trk_CC", 90, 50., 140., _NPTBINS_, _PTBINS_ },
	{"loose_ZMass_vs_Pt_After__Trk_CC", 90, 50., 140., _NPTBINS_, _PTBINS_ },
	{"loose_ZMass_vs_Pt_Before_Trk_TAG", 90, 50., 140., _NPTBINS_, _PTBINS_ },
	{"", 0, 0., 0., 0, {0} }
};
#undef _NPTBINS_
#undef _PTBINS_


//more histograms for zpt dphi reweighting
#define _NXBINS_ 65
#define _XBINS_  {0, 2.521278, 2.541288, 2.561299, 2.581309, 2.601319, 2.621329, 2.641339, 2.661349, 2.681359, 2.70137, 2.72138, 2.74139, 2.7614, 2.78141, 2.80142, 2.82143, 2.841441, 2.861451, 2.881461, 2.901471, 2.921481, 2.941491, 2.961501, 2.981512, 3.001522, 3.021532, 3.041542, 3.061552, 3.081562, 3.101572, 3.121583, 3.141593, 3.161603, 3.181613, 3.201623, 3.221633, 3.241643, 3.261654, 3.281664, 3.301674, 3.321684, 3.341694, 3.361704, 3.381714, 3.401725, 3.421735, 3.441745, 3.461755, 3.481765, 3.501775, 3.521785, 3.541796, 3.561806, 3.581816, 3.601826, 3.621836, 3.641846, 3.661857, 3.681867, 3.701877, 3.721887, 3.741897, 3.761907, 3.781917, 6.283185}
#define _NYBINS_ 11
#define _YBINS_  {0, 1, 2, 3, 4, 5, 7, 10, 15, 20, 30, 300}

static HIST_2D_VARBIN_XY ZCand_Hist_2D_varbin[]={
	{"ZCandDeltaPhi_EM1_EM2_Zpt_2pi_varbin", _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
	//{"ZCandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi02_varbin", _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
	//{"ZCandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi24_varbin", _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
	//{"ZCandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi46_varbin", _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
	//{"ZCandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi6999_varbin", _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
	{"", 0, {0.}, 0, {0.} }
};
#undef _NXBINS_
#undef _XBINS_
#undef _NYBINS_
#undef _YBINS_

// For ZB event studies
static HIST_1D ZCand_ZBevent_Hist[]={
  {"ZCandScalarEt_ZB", 300, 0., 300.},
  {"", 0, 0, 0}
};

// MC histograms used in ZAnalysis
static HIST_1D Z_MC_Hist[]={
		      {"ZMCElecPt", 100, 0., 100.},
		      {"ZMCElecEta", 60, -3., 3.},
		      {"ZMCElecPhi", 64, 0., TMath::TwoPi()},
		      {"ZMCPt", 100, 0., 50.},
		      {"ZMCElecE", 200, 0., 200.},
		      {"ZMCMass", 400, 50., 150.},
		      {"ZMCdeltaR", 100,0.0,10.0},
		      {"ZMC_RECO_deltaR", 100,0.0,10.0},
		      {"ZMC_RECO_deltaeta", 200,-10.0,10.0},
		      {"ZMC_RECO_deltaphi", 315,0.0,3.15},
		      {"ZMC_RECO_deltapx", 1000,-50.0,50.0},
		      {"ZMC_RECO_deltapy", 1000,-50.0,50.0},
		      {"ZMC_RECO_deltapz", 1000,-50.0,50.0},
		      {"ZMC_RECO_deltaPt", 1000,-50.0,50.0},
		      {"ZMC_RECO_deltaMass", 1000,-50.0,50.0},
		      {"ZMC_RECO_deltaZPt", 1000,-50.0,50.0},
		      {"ZMCMassSmear", 150, 0., 150.},
		      {"ZMCElecPtSmear", 100, 0., 100.},
		      {"ZMCPtSmear", 100, 0., 50.},
		      {"ZElectronSmearPt_CCCC_2trks_TruePtBin", 600, -10., 10.},
		      {"ZElectronSmearE_CCCC_2trks_TrueEBin", 600, -10., 10.},
		      {"ZElectronSmearE_CCCC_2trks_TrueE_Thetabin", 600, -10., 10.},
		      //{"ZElectronAvgModelRes_CCCC_2trks_TrueEBin", 600, -10., 10.},
		      {"", 0, 0, 0}};

static HIST_2D ZCand_Hist_2D[]={
                      {"ZCandMass_V_fZ_CCCC", 60, 0., 3., 140, 60., 130.},
                      {"ZCandMass_V_fZ_CCEC", 60, 0., 3., 140, 60., 130.},
                      {"ZCandMass_V_fZ_ECEC", 60, 0., 3., 140, 60., 130.},
		      {"ZCandElecEnergyVTruth_CCCC_2trks",200, 0., 200.,200, 0., 200.},
		      {"ZCandNCaloCellsVInstLumi", 200, 0., 7000., 100, 0., 10.},
		      {"ZCandElecEnergy_V_Eta",100,0,100,22,-1.1,1.1},
		      // study phi crack efficiency
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod2", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_pTBin", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_gen_EtaBin", 50, 0., 1., 25, -0.2, 0.2},
                      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_PassPtTrkMatch", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin_PassPtTrkMatch", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin_PassPtTrkMatch", 50, 0., 1., 25, -0.2, 0.2},
                      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_PassPt", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin_PassPt", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin_PassPt", 50, 0., 1., 25, -0.2, 0.2},
                      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_PassTrkMatch", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_pTBin_PassTrkMatch", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandCalTrkDeltaPhi_V_ElecPhiMod_EtaBin_PassTrkMatch", 50, 0., 1., 25, -0.2, 0.2},
		      {"ZCandElecPt_V_Mass",300, 0., 100.,400, 50., 150.},
		      {"ZCandUPerp_V_Mass",120, -30., 30.,400, 50., 150.},
		      {"ZCandUPara_V_Mass",120, -30., 30.,400, 50., 150.},
		      {"ZCandUPara_V_Mass_NoCuts",400, 50., 150.,120, -30., 30.},
		      {"ZCandUPara_V_Mass_OnlyWithGoodSpatialMatch",400, 50., 150.,120, -30., 30.},
		      {"ZCandUPara_V_Mass_OnlyIsoHMxCut",400, 50., 150.,120, -30., 30.},
		      {"ZCandUPara_V_Mass_OnlyWithSpatialMatch",400, 50., 150.,120, -30., 30.},
		      {"ZCandUPara_V_Mass_BothWithGoodSpatialMatch_IsoHMxCut",400, 50., 150.,120, -30., 30.},
		      {"ZCandScalarEt_V_Lumi2D" ,100, 0., 10.,  100, 0., 300.}, 
		      {"ZCandMass_vs_DetEta_CCCC_Trks",31,-3.1,3.1 , 150, 0., 150.},
		      {"ZCandMass_vs_Eta____CCCC_Trks",31,-3.1,3.1 , 150, 0., 150.},
		      {"ZCandMass_vs_Pt_____CCCC_Trks",100, 0.,100., 150, 0., 150.},
		      {"", 0, 0, 0, 0, 0, 0}};
 
// histograms used for MC Recoil Studies
static HIST_1D MC_RECOIL_Hist[]={
		      {"MC_RECOIL_Px", 200, -100., 100.},
		      {"MC_RECOIL_Py", 200, -100., 100.},
		      {"MC_RECOIL_Pt", 100, 0., 100.},
		      {"MC_RECOIL_Eta", 60, -3., 3.},
		      {"MC_RECOIL_Phi", 63, 0., 6.3},
		      {"MC_RECOIL_MCZ_deltapx", 200,-100.0,100.0},
		      {"MC_RECOIL_MCZ_deltapy", 200,-100.0,100.0},
		      {"MC_RECOIL_MCZ_deltapt", 100,-50.0,50.0},
		      {"MC_RECOIL_MCZ_deltaeta", 200,-10.0,10.0},
		      {"MC_RECOIL_MCZ_deltaphi", 315,0.0,3.15},
		      {"MC_RECOIL_RECO_deltapx", 200,-100.0,100.0},
		      {"MC_RECOIL_RECO_deltapy", 200,-100.0,100.0},
		      {"MC_RECOIL_RECO_deltapt", 100,-50.0,50.0},
		      {"MC_RECOIL_RECO_deltaeta", 200,-10.0,10.0},
		      {"MC_RECOIL_RECO_deltaphi", 315,0.0,3.15},
		      {"ZRecoilSmearPt_TruePtBin",600, -10., 10.},
		      {"ZRecoilSmearPhi_TruePtBin",600, -10., 10.},
		      {"ZRecoilSmearE_TrueEBin",600, -10., 10.},
		      {"", 0, 0, 0}};

static HIST_2D Z_MC_Hist_2D[]={
                      {"ZMCElecE_V_ZRECOElecE", 200, 0., 200., 200, 0., 200.},          // generator-level vs reco-level
		      {"ZMCElecPt_V_ZRECOElecPt", 240, 0., 60., 240, 0., 60.},
		      {"ZMCElecEta_V_ZRECOElecEta", 60, -3., 3., 60, -3., 3.},
		      {"ZMCElecPhi_V_ZRECOElecPhi", 64, 0., TMath::TwoPi(), 64, 0., TMath::TwoPi()},
		      {"MC_RECOIL_Pt_V_RECO_RECOIL_pt",100, 0., 100.,100, 0., 100.},
		      {"MC_RECOIL_Pt_V_RECO_RECOIL_pt_response",100, 0., 100.,100, 0., 1.},
		      {"ZElectronAvgModelRes_CCCC_2trks_2D",1000, 0., 100.,1000, 0., 1.},
		      {"ZMCElecESmear_V_ZRecoElecE_CCCC_2",200, 0., 200., 200, 0., 200.}, 
		      {"", 0, 0, 0, 0, 0, 0}};

static HIST_PROFILE Z_MC_Hist_Profile[]={
		      {"ZMCElecE_V_ZRECOElecE_prof", 200, 0., 200., 0., 200., " "},          // generator-level vs reco-level
		      {"ZMCElecPt_V_ZRECOElecPt_prof", 400, 0., 100., 0., 100., " "},
		      {"ZMCElecPt_V_ZRECOElecPt_prof2", 1000, 0., 100., 0., 100., " "},
		      {"ZMCElecPt_V_ZSmearElecPt", 200, 0., 100., 0., 100., " "},       // generator-level vs smeared-level
		      {"ZMCElecE_V_ZSmearElecE", 200, 0., 200., 0., 200., " "},
		      {"ZElectronAvgModelRes_CCCC_2trks_TrueEBin", 40, 0., 200.,0.0,10.0, " "},
		      {"", 0, 0, 0, 0, 0, ""}};

// histograms for trk match efficiency
static HIST_1D ZCandTrkMatch_Hist[]={
                      {"ZCandTrkMatchEff_NoTrkMatch_eta", 80, -4., 4.},
                      {"ZCandTrkMatchEff_NoTrkMatch_caleta", 80, -4., 4.},
                      {"ZCandTrkMatchEff_NoTrkMatch_pT", 100, 0., 100.},
                      {"ZCandTrkMatchEff_NoTrkMatch_upara", 120, -30., 30.},
                      {"ZCandTrkMatchEff_NoTrkMatch_vtxz", 320, -80., 80.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_eta", 80, -4., 4.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_caleta", 80, -4., 4.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_pT", 100, 0., 100.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_upara", 120, -30., 30.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_vtxz", 320, -80., 80.},
                      {"ZCandTrkMatchEff_TightTrkMatch_eta", 80, -4., 4.},
                      {"ZCandTrkMatchEff_TightTrkMatch_caleta", 80, -4., 4.},
                      {"ZCandTrkMatchEff_TightTrkMatch_pT", 100, 0., 100.},
                      {"ZCandTrkMatchEff_TightTrkMatch_upara", 120, -30., 30.},
                      {"ZCandTrkMatchEff_TightTrkMatch_vtxz", 320, -80., 80.},
                      {"", 0, 0, 0}};

static HIST_2D ZCandTrkMatch_Hist_2D[]={
                      {"ZCandTrkMatchEff_NoTrkMatch_eta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrkMatchEff_NoTrkMatch_eta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_NoTrkMatch_caleta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_NoTrkMatch_etam_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_NoTrkMatch_etap_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_NoTrkMatch_etam_etap", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrkMatchEff_NoTrkMatch_etap_etam", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrkMatchEff_NoTrkMatch_upara_pz", 120, -30., 30., 400, -200., 200.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_eta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_caleta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_etam_etap", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_etap_etam", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrkMatchEff_LooseTrkMatch_upara_pz", 120, -30., 30., 400, -200., 200.},
                      {"ZCandTrkMatchEff_TightTrkMatch_eta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrkMatchEff_TightTrkMatch_eta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_TightTrkMatch_caleta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_TightTrkMatch_etam_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_TightTrkMatch_etap_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrkMatchEff_TightTrkMatch_etam_etap", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrkMatchEff_TightTrkMatch_etap_etam", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrkMatchEff_TightTrkMatch_upara_pz", 120, -30., 30., 400, -200., 200.},
                      {"", 0, 0, 0, 0, 0, 0}};

static HIST_2D ZCandTrkMatch_Coarse_Hist_2D[]={
                      {"ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse", 36, -60., 60., 32, -3.2, 3.2},
                      {"ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse", 36, -60., 60., 32, -3.2, 3.2},
                      {"ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse", 36, -60., 60., 32, -3.2, 3.2},
                      {"", 0, 0, 0, 0, 0, 0}};
  
static HIST_1D ZCandTrueTrkMatch_Hist[]={
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_eta", 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_caleta", 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_pT", 100, 0., 100.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_upara", 120, -30., 30.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_vtxz", 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_eta", 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_caleta", 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_pT", 100, 0., 100.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_upara", 120, -30., 30.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz", 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_eta", 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_caleta", 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_pT", 100, 0., 100.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_upara", 120, -30., 30.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_vtxz", 320, -80., 80.},
                      {"", 0, 0, 0}};

static HIST_2D ZCandTrueTrkMatch_Hist_2D[]={
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz", 120, -30., 30., 400, -200., 200.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz", 120, -30., 30., 400, -200., 200.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_eta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_eta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT", 80, -4., 4., 100, 0., 100.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz", 80, -4., 4., 320, -80., 80.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam", 80, -4., 4., 80, -4., 4.},
                      {"ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz", 120, -30., 30., 400, -200., 200.},
                      {"", 0, 0, 0, 0, 0, 0}};

// histograms for uparallel efficiency studies
static HIST_1D ZCandUPara_Hist[]={
// old stuff - kept for compatibility and data
                    {"ZCandUPara_WithoutIsoHMxCut_trkmatch", 120, -30, 30.},
		    {"ZCandUPara_WithIsoHMxCut_trkmatch", 120, -30, 30.},
                    {"ZCandUPara_notrkmatch_UPara", 120, -30., 30.},
                    {"ZCandUPara_trkmatch_UPara", 120, -30., 30.},

// new stuff - Tag and Probe Denominator
                    {"ZCandUPara_Denominator_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_0_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_1_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_2_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_3_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_4_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_5_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_6_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_7_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_8_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_9_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_10_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_11_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_12_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_13_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_14_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_15_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_16_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_17_Tagprobe", 120, -30., 30.},
                    {"ZCandUParaETRatio_Denominator_Tagprobe", 120, -0.8, 0.8},
                    {"ZCandUPara_Denominator_UtCut_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_PtCut_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_VtxCut_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_2EM_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_trkpresel_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_phifiducial_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_CCECtag_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Denominator_ECtag_Tagprobe", 120, -30., 30.},
// Tag and Probe Numerator
                    {"ZCandUPara_Numerator_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_0_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_1_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_2_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_3_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_4_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_5_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_6_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_7_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_8_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_9_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_10_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_11_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_12_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_13_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_14_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_15_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_16_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_17_Tagprobe", 120, -30., 30.},
                    {"ZCandUParaETRatio_Numerator_Tagprobe", 120, -0.8, 0.8},
                    {"ZCandUPara_Numerator_UtCut_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_PtCut_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_VtxCut_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_2EM_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_trkpresel_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_phifiducial_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_CCECtag_Tagprobe", 120, -30., 30.},
                    {"ZCandUPara_Numerator_ECtag_Tagprobe", 120, -30., 30.},
// Truth Denominator
                    {"ZCandUPara_Denominator_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_0_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_1_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_2_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_3_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_4_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_5_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_6_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_7_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_8_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_9_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_10_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_11_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_12_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_13_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_14_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_15_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_16_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_instlumi_17_Truth", 120, -30., 30.},
                    {"ZCandUParaETRatio_Denominator_Truth", 120, -0.8, 0.8},
                    {"ZCandUPara_Denominator_UtCut_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_PtCut_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_VtxCut_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_2EM_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_trkpresel_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_phifiducial_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_CCECtag_Truth", 120, -30., 30.},
                    {"ZCandUPara_Denominator_ECtag_Truth", 120, -30., 30.},
// Truth Numerator
                    {"ZCandUPara_Numerator_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_0_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_1_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_2_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_3_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_4_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_5_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_6_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_7_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_8_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_9_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_10_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_11_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_12_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_13_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_14_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_15_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_16_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_instlumi_17_Truth", 120, -30., 30.},
                    {"ZCandUParaETRatio_Numerator_Truth", 120, -0.8, 0.8},
                    {"ZCandUPara_Numerator_UtCut_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_PtCut_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_VtxCut_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_2EM_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_trkpresel_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_phifiducial_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_CCECtag_Truth", 120, -30., 30.},
                    {"ZCandUPara_Numerator_ECtag_Truth", 120, -30., 30.},
		    {"", 0, 0, 0}
};

static HIST_2D ZCandUPara_Hist_2D[]={


// old stuff - kept for compatibility and data
		      {"ZCandMass_V_UPara_Bkgd", 120, -30, 30, 150, 0., 150.},
		      {"ZCandMass_V_UPara_WithoutIsoHMxCut", 120, -30, 30, 150, 0., 150.},
		      {"ZCandMass_V_UPara_WithIsoHMxCut_trkmatch", 120, -30, 30, 150, 0., 150.},
		      {"ZCandMass_V_UPara_Bkgd_ScaleToW", 120, -30, 30, 150, 0., 150.},
		      {"ZCandMass_V_UPara_WithoutIsoHMxCut_ScaleToW", 120, -30, 30, 150, 0., 150.},
		      {"ZCandMass_V_UPara_WithIsoHMxCut_trkmatch_ScaleToW", 120, -30, 30, 150, 0., 150.},
//new stuff
                      {"ZCandUPara_V_CosPhi_Denominator_Tagprobe", 120, -30., 30., 20, -1., 1.},
                      {"ZCandUPara_V_CosPhi_Numerator_Tagprobe" , 120, -30., 30., 20, -1., 1.},
		      {"ZCandUPara_V_CosPhi_Denominator_Truth", 120, -30., 30., 20, -1., 1.},
		      {"ZCandUPara_V_CosPhi_Numerator_Truth", 120, -30., 30., 20, -1., 1.},
                      {"ZCandU_V_CosPhi_Denominator_Tagprobe", 60, 0., 30., 20, -1., 1.},
                      {"ZCandU_V_CosPhi_Numerator_Tagprobe" , 60, 0., 30., 20, -1., 1.},
		      {"ZCandU_V_CosPhi_Denominator_Truth", 60, 0., 30., 20, -1., 1.},
		      {"ZCandU_V_CosPhi_Numerator_Truth", 60, 0., 30., 20, -1., 1.},
		      {"ZCandUPara_V_instlumi_Denominator_Tagprobe", 120, -30, 30, 250, 0., 10.},
		      {"ZCandUPara_V_instlumi_Numerator_Tagprobe", 120, -30, 30, 250, 0., 10.},
		      {"ZCandUPara_V_instlumi_Denominator_Truth", 120, -30, 30, 250, 0., 10.},
		      {"ZCandUPara_V_instlumi_Numerator_Truth", 120, -30, 30, 250, 0., 10.},
		      {"", 0, 0, 0, 0, 0, 0}
};

// histograms used for WAnalysis
static HIST_1D WCand_Hist[]={
                      // histograms used for study scalar Et efficiency (only used for full MC)
		      {"WCandScalarEt_NoCuts", 100, 0., 200.},
		      {"WCandElecPtOverScalarEt_NoCuts", 100, 0., 5.},
		      {"WCandMCElecPt_NoCuts", 100, 0., 100.},
		      {"WCandScalarEt_Cut1", 100, 0., 200.},
		      {"WCandElecPtOverScalarEt_Cut1", 100, 0., 5.},
		      {"WCandMCElecPt_Cut1", 100, 0., 100.},
		      {"WCandScalarEt_Cut2", 100, 0., 200.},
		      {"WCandElecPtOverScalarEt_Cut2", 100, 0., 5.},
		      {"WCandMCElecPt_Cut2", 100, 0., 100.},
		      {"WCandScalarEt_Cut3", 100, 0., 200.},
		      {"WCandElecPtOverScalarEt_Cut3", 100, 0., 5.},
		      {"WCandMCElecPt_Cut3", 100, 0., 100.},
		      {"WCandScalarEt_Cut4", 100, 0., 200.},
		      {"WCandElecPtOverScalarEt_Cut4", 100, 0., 5.},
		      {"WCandMCElecPt_Cut4", 100, 0., 100.},
		      {"WCandScalarEt_Cut5", 100, 0., 200.},
		      {"WCandElecPtOverScalarEt_Cut5", 100, 0., 5.},
		      {"WCandMCElecPt_Cut5", 100, 0., 100.},
                      // make reconstructed and generator-level 
                      // electron pT distributions for different eta regions
                      {"WCandMt_EtaBin_CC", 300, 50., 200.},
                      {"WCandMt_Spatial_Match_EtaBin_CC", 300, 50., 200.},
                      {"WCandElecPt_EtaBin_CC", 200, 0., 100.},
                      {"WCandElecPt_Spatial_Match_EtaBin_CC", 200, 0., 100.},
                      {"WCandMet_EtaBin_CC", 200, 0., 100.},
                      {"WCandMet_Spatial_Match_EtaBin_CC", 200, 0., 100.},
                      {"WCandMCElecPt_EtaBin_CC", 200, 0., 100.},
                      {"WCandMCElecPtDiff_EtaBin_CC", 200, -10., 10.},
                      {"WCandMCElecPt_Spatial_Match_EtaBin_CC", 200, 0., 100.},
                      {"WCandMCElecPtDiff_Spatial_Match_EtaBin_CC", 200, -10., 10.},
                      {"WCandMt_EtaBin_CC_Tail", 300, 50., 200.},
                      {"WCandMt_Spatial_Match_EtaBin_CC_Tail", 300, 50., 200.},
                      {"WCandElecPt_EtaBin_CC_Tail", 200, 0., 100.},
                      {"WCandElecPt_Spatial_Match_EtaBin_CC_Tail", 200, 0., 100.},
                      {"WCandMet_EtaBin_CC_Tail", 200, 0., 100.},
                      {"WCandMet_Spatial_Match_EtaBin_CC_Tail", 200, 0., 100.},
                      {"WCandMCElecPt_EtaBin_CC_Tail", 200, 0., 100.},
                      {"WCandMCElecPtDiff_EtaBin_CC_Tail", 200, -10., 10.},
                      {"WCandMCElecPt_Spatial_Match_EtaBin_CC_Tail", 200, 0., 100.},
                      {"WCandMCElecPtDiff_Spatial_Match_EtaBin_CC_Tail", 200, -10., 10.},
                      {"WCandMCElecPt_EtaBin_CC_NoCuts", 200, 0., 100.},
                      // distributions for CC/EC and all, 0 for CC, 1 for EC
		      // without track requirement
                      {"WCandVtx", 320, -80., 80.},
                      {"WCandNPV", 30,0,30},
                      {"WCandTick", 150,0,150},
                      {"WCandPhi", 64, 0., TMath::TwoPi()},
                      {"WCandInstLumi", 250, 0., 10.},
		      {"WCandNCaloCells", 200, 0., 7000.},
		      {"WCandScalarEt", 300, 0., 300.},
                      {"WCandSqrtScalarEt", 400, 0., 15.},
                      {"WCandElecPt", 200, 0., 100.},
                      {"WCandElecPx", 400, -100., 100.},
                      {"WCandElecPy", 400, -100., 100.},
		      {"WCandElecTrkPt", 200, 0., 100.},
                      {"WCandMet", 200, 0., 100.},
                      {"WCandMetx", 200, -100., 100.},
                      {"WCandMety", 200, -100., 100.},
                      {"WCandMetPhi", 64, 0., TMath::TwoPi()},
                      {"WCandMt", 300, 50., 200.},
                      {"WCandPt", 100, 0., 50.},
                      {"WCandElecEta", 60, -3., 3.},
                      {"WCandElecDetEta", 60, -3., 3.},
                      {"WCandElecPhi", 64, 0., TMath::TwoPi()},
                      {"WCandElecDetPhi", 64, 0., TMath::TwoPi()},
		      {"WCandElecTrkPhiEM3", 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtDCA", 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtEM3", 64, 0., TMath::TwoPi()},
                      {"WCandElecDetPhiCALO", 64, 0., TMath::TwoPi()},
                      {"WCandRecoilPt", 100, 0., 50.},
                      {"WCandRecoilPx", 200, -50., 50.},
                      {"WCandRecoilPy", 200, -50., 50.},
                      {"WCandRecoilPhi", 64, 0., TMath::TwoPi()},
                      {"WCandElecMetDeltaPhi", 100, 0., TMath::Pi()},
                      {"WCandElecRecoilDeltaPhi", 100, 0., TMath::Pi()},
                      {"WCandMetRecoilDeltaPhi", 100, 0., TMath::Pi()},
                      {"WCandMt_UtBin", 300, 50., 200.},
		      // for width analysis
                      {"WCandElecPt_Width", 200, 0., 200.},
                      {"WCandMet_Width", 200, 0., 200.},
                      {"WCandMt_Width", 300, 50., 200.},
                      {"WCandPt_Width", 200, 0., 100.},
                      {"WCandElecPt_Tail_Width", 200, 0., 100.},
                      {"WCandMet_Tail_Width", 200, 0., 100.},
                      {"WCandMt_Tail_Width", 300, 50., 200.},
                      {"WCandPt_Tail_Width", 200, 0., 100.},


		      {"WCandElecTrkPtOvE", 200, 0., 1.1},
		      {"WCandElec_TrkPhiEM3Mod", 50, 0., 1.},
		      
                      // with good spatial only track matching
                      {"WCandVtx_Spatial_Match", 320, -80., 80.},
                      {"WCandNPV_Spatial_Match", 30,0,30},
                      {"WCandTick_Spatial_Match", 150,0,150},
                      {"WCandPhi_Spatial_Match", 64, 0., TMath::TwoPi()},
                      {"WCandInstLumi_Spatial_Match", 250, 0., 10.},
		      {"WCandScalarEt_Spatial_Match", 300, 0., 300.},
                      {"WCandSqrtScalarEt_Spatial_Match", 400, 0., 15.},
                      {"WCandElecPt_Spatial_Match", 200, 0., 100.},
                      {"WCandElecPx_Spatial_Match", 400, -100., 100.},
                      {"WCandElecPy_Spatial_Match", 400, -100., 100.},
                      {"WCandElecTrkPt_Spatial_Match", 200, 0., 100.},
                      {"WCandMet_Spatial_Match", 200, 0., 100.},
                      {"WCandMetx_Spatial_Match", 200, -100., 100.},
                      {"WCandMety_Spatial_Match", 200, -100., 100.},
                      {"WCandMetPhi_Spatial_Match", 64, 0., TMath::TwoPi()},
                      {"WCandMt_Spatial_Match", 300, 50., 200.},
                      {"WCandPt_Spatial_Match", 100, 0., 50.},
		      {"WCandTruePt_Spatial_Match", 100, 0., 50.},
		      {"WCandResolPt_Spatial_Match", 100, -30., 30.},
                      {"WCandElecEta_Spatial_Match", 60, -3., 3.},
                      {"WCandElecDetEta_Spatial_Match", 60, -3., 3.},
                      {"WCandElecPhi_Spatial_Match", 64, 0., TMath::TwoPi()},
                      {"WCandElecDetPhi_Spatial_Match", 64, 0., TMath::TwoPi()},
		      {"WCandElecTrkPhiEM3_Spatial_Match", 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtDCA_Spatial_Match", 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtEM3_Spatial_Match", 64, 0., TMath::TwoPi()},
                      {"WCandElecDetPhiCALO_Spatial_Match", 64, 0., TMath::TwoPi()},
                      {"WCandRecoilPt_Spatial_Match", 100, 0., 50.},
                      {"WCandRecoilPx_Spatial_Match", 200, -50., 50.},
                      {"WCandRecoilPy_Spatial_Match", 200, -50., 50.},
                      {"WCandRecoilPhi_Spatial_Match", 64, 0., TMath::TwoPi()},
                      {"WCandElecMetDeltaPhi_Spatial_Match",  100, 0., TMath::Pi()},
                      {"WCandElecRecoilDeltaPhi_Spatial_Match",  100, 0., TMath::Pi()},
                      {"WCandMetRecoilDeltaPhi_Spatial_Match",  100, 0., TMath::Pi()},
                      {"WCandMt_UtBin_Spatial_Match", 300, 50., 200.},
		      // for width analysis
                      {"WCandElecPt_Spatial_Match_Width", 250, 25., 150.},
                      {"WCandMet_Spatial_Match_Width", 250, 25., 150.},
                      {"WCandMt_Spatial_Match_Width", 300, 50., 200.},
                      {"WCandPt_Spatial_Match_Width", 200, 0., 100.},
                      {"WCandElecPt_Spatial_Match_Tail_Width", 250, 25., 150.},
                      {"WCandMet_Spatial_Match_Tail_Width", 250, 25., 150.},
                      {"WCandMt_Spatial_Match_Tail_Width", 300, 50., 200.},
                      {"WCandPt_Spatial_Match_Tail_Width", 200, 0., 100.},
                      // for different recoil Pt bins
                      {"WCandMt_RecoilBin", 300, 50., 200.},
                      {"WCandElecPt_RecoilBin", 200, 0., 100.},
                      {"WCandMet_RecoilBin", 200, 0., 100.},
                      {"WCandElecMetDeltaPhi_RecoilBin",  100, 0., TMath::Pi()},
                      {"WCandElecRecoilDeltaPhi_RecoilBin",  100, 0., TMath::Pi()},
                      {"WCandMetRecoilDeltaPhi_RecoilBin",  100, 0., TMath::Pi()},
                      {"WCandRecoilPhi_RecoilBin", 64, 0., TMath::TwoPi()},
		      {"WCandUPara_RecoilBin", 120, -30., 30.},
		      {"WCandUPerp_RecoilBin", 120, -30., 30.},
                      {"WCandVtx_RecoilBin", 320, -80., 80.},
                      {"WCandNPV_RecoilBin", 30,0,30},
                      {"WCandPhi_RecoilBin", 64, 0., TMath::TwoPi()},
                      {"WCandInstLumi_RecoilBin", 250, 0., 10.},
		      {"WCandScalarEt_RecoilBin", 300, 0., 300.},
                      // phimod
                      {"WCandElecEMPhiMod", 100, 0., 1.},
                      {"WCandElecEMPhiMod_Posi", 100, 0., 1.},
                      {"WCandElecEMPhiMod_Elec", 100, 0., 1.},
                      {"WCandElecEMPhiMod_Posi_QSolpol", 100, 0., 1.},
                      {"WCandElecEMPhiMod_Elec_QSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiMod", 100, 0., 1.},
                      {"WCandElecTrkPhiMod_Posi", 100, 0., 1.},
                      {"WCandElecTrkPhiMod_Elec", 100, 0., 1.},
                      {"WCandElecTrkPhiMod_Posi_QSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiMod_Elec_QSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiModEM3", 100, 0., 1.},
                      {"WCandElecTrkPhiModEM3_Posi", 100, 0., 1.},
                      {"WCandElecTrkPhiModEM3_Elec", 100, 0., 1.},
                      {"WCandElecTrkPhiModEM3_Posi_QSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiModEM3_Elec_QSolpol", 100, 0., 1.},

                      {"WCandElecTrkPhiMod_Posi_PosSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiMod_Elec_PosSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiMod_Posi_NegSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiMod_Elec_NegSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiModEM3_Posi_PosSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiModEM3_Elec_PosSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiModEM3_Posi_NegSolpol", 100, 0., 1.},
                      {"WCandElecTrkPhiModEM3_Elec_NegSolpol", 100, 0., 1.},

		      // E/p distribution
                      {"WCandEOverP", 100, 0., 3.}, //after EM corrections
                      {"WCandRawEOverP", 100, 0., 3.},  //before EM corrections
                      {"WMCElecTrkPt_Smear", 200, 0., 100.},
                      {"WMCEOverP_Merge", 100, 0., 3.},  // for MC simulation
                      {"WMCEOverP_CalSmear", 100, 0., 3.},  // for MC simulation
                      {"WMCEOverP_CalTrkSmear", 100, 0., 3.},  // for MC simulation
                      {"WMCEOverP_CalBremSmear", 100, 0., 3.},  // for MC simulation
                      {"WMCEOverP", 100, 0., 3.},  // for MC simulation
		      {"WCandEOverP_CalPhiModPosition", 100, 0., 3.},    // E/p for different EM phimod
                      {"WCandRawEOverP_CalPhiModPosition", 100, 0., 3.},  
                      {"WCandEOverP_TrkPhiModPosition", 100, 0., 3.},    // E/p for different track phimod at DCA
                      {"WCandEOverP_TrkPhiModPosition_Elec", 100, 0., 3.},    
                      {"WCandEOverP_TrkPhiModPosition_Posi", 100, 0., 3.},   
                      {"WCandRawEOverP_TrkPhiModPosition", 100, 0., 3.}, 
                      {"WCandEOverP_TrkMod", 100, 0., 3.},    // E/p 
                      {"WCandRawEOverP_TrkMod", 100, 0., 3.},    // E/p 
                      {"WCandEOverP_TrkPhiModEM3Position", 100, 0., 3.},  // E/p for different track phimod at EM3
                      {"WCandEOverP_TrkPhiModEM3Position_Elec", 100, 0., 3.},  // E/p for different track phimod at EM3
                      {"WCandEOverP_TrkPhiModEM3Position_Posi", 100, 0., 3.},  // E/p for different track phimod at EM3
                      {"WCandRawEOverP_TrkPhiModEM3Position", 100, 0., 3.}, 
                      // for electron and positron
                      {"WCandEOverP_Electron_PosSolPol", 100, 0., 3.},
                      {"WCandEOverP_Electron_NegSolPol", 100, 0., 3.},
                      {"WCandEOverP_Positron_PosSolPol", 100, 0., 3.},
                      {"WCandEOverP_Positron_NegSolPol", 100, 0., 3.},
                      {"WCandEt_Electron_PosSolPol", 100, 0., 100.},
                      {"WCandEt_Electron_NegSolPol", 100, 0., 100.},
                      {"WCandEt_Positron_PosSolPol", 100, 0., 100.},
                      {"WCandEt_Positron_NegSolPol", 100, 0., 100.},
                      {"WCandPt_Electron_PosSolPol", 100, 0., 100.},
                      {"WCandPt_Electron_NegSolPol", 100, 0., 100.},
                      {"WCandPt_Positron_PosSolPol", 100, 0., 100.},
                      {"WCandPt_Positron_NegSolPol", 100, 0., 100.},
                      {"WCandEOverP_Electron_PosSolPol_Eta", 100, 0., 3.},
                      {"WCandEOverP_Electron_NegSolPol_Eta", 100, 0., 3.},
                      {"WCandEOverP_Positron_PosSolPol_Eta", 100, 0., 3.},
                      {"WCandEOverP_Positron_NegSolPol_Eta", 100, 0., 3.},
                      {"WCandEOverP_Electron_PosSolPol_DetEta", 100, 0., 3.},
                      {"WCandEOverP_Electron_NegSolPol_DetEta", 100, 0., 3.},
                      {"WCandEOverP_Positron_PosSolPol_DetEta", 100, 0., 3.},
                      {"WCandEOverP_Positron_NegSolPol_DetEta", 100, 0., 3.},
                      {"WCandEOverP_Electron_PosSolPol_Phi", 100, 0., 3.},
                      {"WCandEOverP_Electron_NegSolPol_Phi", 100, 0., 3.},
                      {"WCandEOverP_Positron_PosSolPol_Phi", 100, 0., 3.},
                      {"WCandEOverP_Positron_NegSolPol_Phi", 100, 0., 3.},
		      // Uparallel, uperpendicular
                      {"WCandElecPtUpara1", 160, 20., 100.},
                      {"WCandElecPtUpara2", 160, 20., 100.},
                      {"WCandMetUpara1", 160, 20., 100.},
                      {"WCandMetUpara2", 160, 20., 100.},
                      {"WCandMtUpara1", 300, 50., 200.},
                      {"WCandMtUpara2", 300, 50., 200.},
                      {"WCandWPtUpara1", 100, 0., 50.},
                      {"WCandWPtUpara2", 100, 0., 50.},
                      {"WCandElecPtUpara1_Spatial_Match", 160, 20., 100.},
                      {"WCandElecPtUpara2_Spatial_Match", 160, 20., 100.},
		      {"WCandElecTrkPtUpara1_Spatial_Match", 200, 0., 100.},
		      {"WCandElecTrkPtUpara2_Spatial_Match", 200, 0., 100.},
                      {"WCandMetUpara1_Spatial_Match", 160, 20., 100.},
                      {"WCandMetUpara2_Spatial_Match", 160, 20., 100.},
                      {"WCandMtUpara1_Spatial_Match", 300, 50., 200.},
                      {"WCandMtUpara2_Spatial_Match", 300, 50., 200.},
                      {"WCandWPtUpara1_Spatial_Match", 100, 0., 50.},
                      {"WCandWPtUpara2_Spatial_Match", 100, 0., 50.},
		      {"WCandUPara", 120, -30., 30.},
		      {"WCandUPerp", 120, -30., 30.},
		      {"WCandUt", 60, 0., 30.},
		      {"WCandElecRecPhi", 64, 0., 3.2},
		      {"WCandElecMetPhi", 64, 0., 3.2},
		      {"WCandUPara_Spatial_Match", 120, -30., 30.},
		      {"WCandTrueUPara_Spatial_Match", 120, -30., 30.},
		      {"WCandResolUPara_Spatial_Match", 120, -30., 30.},
		      {"WCandUPerp_Spatial_Match", 120, -30., 30.},
		      {"WCandTrueUPerp_Spatial_Match", 120, -30., 30.},
		      {"WCandResolUPerp_Spatial_Match", 120, -30., 30.},
		      {"WCandUt_Spatial_Match", 60, 0., 30.},
		      {"WCandElecRecPhi_Spatial_Match", 64, 0., 3.2},
		      {"WCandElecMetPhi_Spatial_Match", 64, 0., 3.2},
                      // distribution for each module
		      // will automatically generate 32 histograms for 32 modules
                      {"WCandElecPt_Mod", 200, 0., 100.}, 
                      {"WCandMet_Mod", 200, 0., 100.},
                      {"WCandMt_Mod", 300, 50., 200.},
                      {"WCandPt_Mod", 100, 0., 50.},
                      {"WCandEOverP_Mod", 100, 0., 3.}, 
                      {"WCandRawEOverP_Mod", 100, 0., 3.}, 
		      {"WCandElecTrkPtOvE_Spatial_Match", 200, 0., 1.1},
		      {"WCandElec_TrkPhiEM3Mod_Spatial_Match", 50, 0., 1.},
                      // UPara in elec pT bin 
                      {"WCandUPara_Spatial_Match_ElecPtBin", 120, -30., 30.},
                      {"WCandUPerp_Spatial_Match_ElecPtBin", 120, -30., 30.},
                      {"WCandRecoil_Spatial_Match_ElecPtBin", 120, -30., 30.},
                      {"WCandMt_Spatial_Match_ElecPtBin", 120, -30., 30.},
                      {"WCandMet_Spatial_Match_ElecPtBin", 120, -30., 30.},
		      {"", 0, 0, 0}};

// MC histograms used in WAnalysis
static HIST_1D W_MC_Hist[]={
                      {"WMCPt", 120, 0., 60.},
                      {"WMCPhi", 132, 0., 6.4},
                      {"WMCPt_CC_bin", 120, 0., 60.},
                      {"WRecoilPt_CC_bin", 120, 0., 60.},
                      {"", 0, 0, 0}};

// For ZB event studies
static HIST_1D WCand_ZBevent_Hist[]={
  {"WCandScalarEt_ZB", 300, 0., 300.},
  {"WCandScalarEt_ZB_Spatial_Match", 300, 0., 300.},
  {"", 0, 0, 0}
};

// profile histograms used for WAnalysis
static HIST_PROFILE WCand_Hist_Profile[]={
                      // Uparallel
                      {"WCandWPtUpara", 60, 0., 30., -20., 20., " "},
                      {"WCandMtUpara", 75, 50., 200., -20., 20., " "},
                      {"WCandElecPtUpara", 50, 25., 50., -20., 20., " "},
                      {"WCandMetUpara", 50, 25., 50., -20., 20., " "},

		      {"WCandEOverP_V_Et", 60, 25., 55., 0., 3., " "},    
		      {"WMCEOverP_V_Et", 60, 25., 55., 0., 3., " "},   
		      {"WCandEOverP_V_EMPhi_Electron", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_TrkPhi_Electron", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_EMPhi_Positron", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_TrkPhi_Positron", 32, 0., TMath::TwoPi(), 0., 3., " "},    

		      {"WCandEOverP_V_EMEta_Electron_PosSolPol", 30, -1.5, 1.5, 0., 3., " "},    
		      {"WCandEOverP_V_EMEta_Electron_NegSolPol", 30, -1.5, 1.5, 0., 3., " "},    
		      {"WCandEOverP_V_EMEta_Positron_PosSolPol", 30, -1.5, 1.5, 0., 3., " "},    
		      {"WCandEOverP_V_EMEta_Positron_NegSolPol", 30, -1.5, 1.5, 0., 3., " "},    
		      {"WCandEOverP_V_TrkPhi_Electron_PosSolPol", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_TrkPhi_Electron_NegSolPol", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_TrkPhi_Positron_PosSolPol", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_TrkPhi_Positron_NegSolPol", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_EMPhi_Electron_PosSolPol", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_EMPhi_Electron_NegSolPol", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_EMPhi_Positron_PosSolPol", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_EMPhi_Positron_NegSolPol", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      // check E/p for physics and detector eta, phi after EM corrections
		      {"WCandEOverP_V_ElecEta", 20, -1.5, 1.5, 0., 3., " "},    
		      {"WCandEOverP_V_ElecDetEta", 20, -1.5, 1.5, 0., 3., " "},    
		      {"WCandEOverP_V_ElecPhi", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandEOverP_V_ElecDetPhi", 32, 0., TMath::TwoPi(), 0., 3., " "},  
		      {"WCandEOverP_V_ElecTrkPhiEM3", 32, 0., TMath::TwoPi(), 0., 3., " "},  
		      {"WCandEOverP_V_ElecPhiMod", 40, 0., 1., 0., 3., " "},
		      {"WCandEOverP_V_ElecTrkPhiMod", 40, 0., 1., 0., 3., " "},
		      // check E/p for physics and detector eta,phi before EM corrections
		      {"WCandRawEOverP_V_ElecEta", 20, -1.5, 1.5, 0., 3., " "},    
		      {"WCandRawEOverP_V_ElecDetEta", 20, -1.5, 1.5, 0., 3., " "},    
		      {"WCandRawEOverP_V_ElecPhi", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandRawEOverP_V_ElecDetPhi", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandRawEOverP_V_ElecTrkPhiEM3", 32, 0., TMath::TwoPi(), 0., 3., " "},    
		      {"WCandRawEOverP_V_ElecPhiMod", 40, 0., 1., 0., 3., " "},
		      {"WCandRawEOverP_V_ElecTrkPhiMod", 40, 0., 1., 0., 3., " "},
		      {"WCandScalarEt_V_Lumi",100, 0., 10., 0., 300., " "},
		      {"", 0, 0, 0, 0, 0, ""}};

// histograms used for WAnalysis
static HIST_3D WCand_Hist_3D[]={
                      // Mt, electron pT, MET and W pT vs detector eta and pT (used for matrix method)
		      {"WCandInstLumiVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 250, 0, 10.},
		      {"WCandScalarEtVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 300, 0., 300.,},
		      {"WCandSqrtScalarEtVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 400, 0., 15.},
		      {"WCandVtxVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 320, -80, 80.},
		      {"WCandPhiVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
		      {"WCandElecPtVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandMetVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandMetxVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 200, -100., 100.},
		      {"WCandMetyVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 200, -100., 100.},
		      {"WCandMetPhiVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
		      {"WCandMtVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandPtVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 100, 0, 50.},
		      {"WCandElecPxVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 400, -100., 100.},
		      {"WCandElecPyVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 400, -100., 100.},
		      {"WCandElecEtaVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 60, -3, 3.},
		      {"WCandElecDetEtaVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 60, -3, 3.},
		      {"WCandElecPhiVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
		      {"WCandElecDetPhiVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtDCAVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtEM3VDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecDetPhiCALOVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
		      {"WCandUParaVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 120, -30, 30.},
		      {"WCandUPerpVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 120, -30, 30.},
		      {"WCandUtVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 60, 0., 30.},
		      {"WCandRecoilPtVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 100, 0., 50.},
		      {"WCandRecoilPxVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 200, -50., 50.},
		      {"WCandRecoilPyVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 200, -50., 50.},
		      {"WCandRecoilPhiVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
		      {"WCandElecMetDeltaPhiVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 100, 0, TMath::Pi()},
		      {"WCandElecRecoilDeltaPhiVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 100, 0, TMath::Pi()},
		      {"WCandMetRecoilDeltaPhiVDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 100, 0, TMath::Pi()},
		      {"WCandMtVDetEtaPt_Width", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandElecPtVDetEtaPt_Width", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandMetVDetEtaPt_Width", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandPtVDetEtaPt_Width", 11, -1.1, 1.1, 75, 25, 100, 100, 0, 50.},
		      {"WCandMtUpara1VDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandMtUpara2VDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandElecPtUpara1VDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandElecPtUpara2VDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandMetUpara1VDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandMetUpara2VDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandWPtUpara1VDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 100, 0, 50.},
		      {"WCandWPtUpara2VDetEtaPt", 11, -1.1, 1.1, 75, 25, 100, 100, 0, 50.},
		      {"WCandMtVDetEtaPt_UtBin_0", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandMtVDetEtaPt_UtBin_1", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandMtVDetEtaPt_UtBin_2", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},

		      //phys eta plots
                      {"WCandInstLumiVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 250, 0, 10.},
                      {"WCandScalarEtVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 300, 0., 300.,},
                      {"WCandSqrtScalarEtVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 400, 0., 15.},
                      {"WCandVtxVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 320, -80, 80.},
                      {"WCandPhiVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecPtVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandMetVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandMetxVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 200, -100., 100.},
                      {"WCandMetyVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 200, -100., 100.},
                      {"WCandMetPhiVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandMtVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandPtVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 100, 0, 50.},
                      {"WCandElecPxVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 400, -100., 100.},
                      {"WCandElecPyVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 400, -100., 100.},
                      {"WCandElecEtaVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 60, -3, 3.},
                      {"WCandElecDetEtaVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 60, -3, 3.},
                      {"WCandElecPhiVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecDetPhiVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtDCAVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtEM3VEtaPt", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecDetPhiCALOVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandUParaVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 120, -30, 30.},
                      {"WCandUPerpVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 120, -30, 30.},
                      {"WCandUtVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 60, 0., 30.},
                      {"WCandRecoilPtVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 100, 0., 50.},
                      {"WCandRecoilPxVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 200, -50., 50.},
                      {"WCandRecoilPyVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 200, -50., 50.},
                      {"WCandRecoilPhiVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecMetDeltaPhiVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 100, 0, TMath::Pi()},
                      {"WCandElecRecoilDeltaPhiVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 100, 0, TMath::Pi()},
                      {"WCandMetRecoilDeltaPhiVEtaPt", 10, -1.5, 1.5, 75, 25, 100, 100, 0, TMath::Pi()},
                      {"WCandMtVEtaPt_Width", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandElecPtVEtaPt_Width", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandMetVEtaPt_Width", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandPtVEtaPt_Width", 10, -1.5, 1.5, 75, 25, 100, 100, 0, 50.},
                      {"WCandMtUpara1VEtaPt", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandMtUpara2VEtaPt", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandElecPtUpara1VEtaPt", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandElecPtUpara2VEtaPt", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandMetUpara1VEtaPt", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandMetUpara2VEtaPt", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandWPtUpara1VEtaPt", 10, -1.5, 1.5, 75, 25, 100, 100, 0, 50.},
                      {"WCandWPtUpara2VEtaPt", 10, -1.5, 1.5, 75, 25, 100, 100, 0, 50.},
                      {"WCandMtVEtaPt_UtBin_0", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandMtVEtaPt_UtBin_1", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandMtVEtaPt_UtBin_2", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},

		      // for track match
		      {"WCandInstLumiVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 250, 0, 10.},
		      {"WCandScalarEtVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 300, 0., 300.,},
		      {"WCandSqrtScalarEtVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 400, 0., 15.},
		      {"WCandVtxVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 320, -80, 80.},
		      {"WCandPhiVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
		      {"WCandElecPtVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandMetVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandMetxVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 200, -100., 100.},
		      {"WCandMetyVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 200, -100., 100.},
		      {"WCandMetPhiVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
		      {"WCandMtVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.}, 
		      {"WCandPtVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 100, 0, 50.},
		      {"WCandElecPxVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 400, -100., 100.},
		      {"WCandElecPyVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 400, -100., 100.},
		      {"WCandElecEtaVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 60, -3, 3.},
		      {"WCandElecDetEtaVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 60, -3, 3.},
		      {"WCandElecPhiVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
		      {"WCandElecDetPhiVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtDCAVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtEM3VDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecDetPhiCALOVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
		      {"WCandUParaVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 120, -30, 30.},
		      {"WCandUPerpVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 120, -30, 30.},
		      {"WCandUtVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 60, 0., 30.},
		      {"WCandRecoilPtVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 100, 0., 50.},
		      {"WCandRecoilPxVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 200, -50., 50.},
		      {"WCandRecoilPyVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 200, -50., 50.},
		      {"WCandRecoilPhiVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 64, 0., TMath::TwoPi()},
		      {"WCandElecMetDeltaPhiVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 100, 0, TMath::Pi()},
		      {"WCandElecRecoilDeltaPhiVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 100, 0, TMath::Pi()},
		      {"WCandMetRecoilDeltaPhiVDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 100, 0, TMath::Pi()},
		      {"WCandMtVDetEtaPt_Match_Width", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandElecPtVDetEtaPt_Match_Width", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandMetVDetEtaPt_Match_Width", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandPtVDetEtaPt_Match_Width", 11, -1.1, 1.1, 75, 25, 100, 100, 0, 50.},
		      {"WCandMtUpara1VDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandMtUpara2VDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandElecPtUpara1VDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandElecPtUpara2VDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandMetUpara1VDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandMetUpara2VDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 200, 0, 100.},
		      {"WCandWPtUpara1VDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 100, 0, 50.},
		      {"WCandWPtUpara2VDetEtaPt_Match", 11, -1.1, 1.1, 75, 25, 100, 100, 0, 50.},
		      {"WCandMtVDetEtaPt_Match_UtBin_0", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandMtVDetEtaPt_Match_UtBin_1", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},
		      {"WCandMtVDetEtaPt_Match_UtBin_2", 11, -1.1, 1.1, 75, 25, 100, 300, 50, 200.},

		      //for phys eta plots
                      {"WCandInstLumiVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 250, 0, 10.},
                      {"WCandScalarEtVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 300, 0., 300.,},
                      {"WCandSqrtScalarEtVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 400, 0., 15.},
                      {"WCandVtxVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 320, -80, 80.},
                      {"WCandPhiVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecPtVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandMetVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandMetxVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 200, -100., 100.},
                      {"WCandMetyVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 200, -100., 100.},
                      {"WCandMetPhiVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandMtVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandPtVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 100, 0, 50.},
                      {"WCandElecPxVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 400, -100., 100.},
                      {"WCandElecPyVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 400, -100., 100.},
                      {"WCandElecEtaVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 60, -3, 3.},
                      {"WCandElecDetEtaVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 60, -3, 3.},
                      {"WCandElecPhiVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecDetPhiVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtDCAVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecPhiTrkAtEM3VEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecDetPhiCALOVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandUParaVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 120, -30, 30.},
                      {"WCandUPerpVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 120, -30, 30.},
                      {"WCandUtVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 60, 0., 30.},
                      {"WCandRecoilPtVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 100, 0., 50.},
                      {"WCandRecoilPxVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 200, -50., 50.},
                      {"WCandRecoilPyVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 200, -50., 50.},
                      {"WCandRecoilPhiVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 64, 0., TMath::TwoPi()},
                      {"WCandElecMetDeltaPhiVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 100, 0, TMath::Pi()},
                      {"WCandElecRecoilDeltaPhiVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 100, 0, TMath::Pi()},
                      {"WCandMetRecoilDeltaPhiVEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 100, 0, TMath::Pi()},
                      {"WCandMtVEtaPt_Match_Width", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandElecPtVEtaPt_Match_Width", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandMetVEtaPt_Match_Width", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandPtVEtaPt_Match_Width", 10, -1.5, 1.5, 75, 25, 100, 100, 0, 50.},
                      {"WCandMtUpara1VEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandMtUpara2VEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandElecPtUpara1VEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandElecPtUpara2VEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandMetUpara1VEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandMetUpara2VEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 200, 0, 100.},
                      {"WCandWPtUpara1VEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 100, 0, 50.},
                      {"WCandWPtUpara2VEtaPt_Match", 10, -1.5, 1.5, 75, 25, 100, 100, 0, 50.},
                      {"WCandMtVEtaPt_Match_UtBin_0", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandMtVEtaPt_Match_UtBin_1", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"WCandMtVEtaPt_Match_UtBin_2", 10, -1.5, 1.5, 75, 25, 100, 300, 50, 200.},
                      {"", 0,0,0,0,0,0,0,0,0}};

// histograms used for WAnalysis
static HIST_2D WCand_Hist_2D[]={
                      // Mt, electron pT, MET and W pT vs detector eta (used for matrix method)
                      {"WCandMtVElecDetEta", 31, -3.1, 3.1, 300, 50., 200.},
                      {"WCandElecPtVElecDetEta", 31, -3.1, 3.1, 200, 0., 100.},
                      {"WCandMetVElecDetEta", 31, -3.1, 3.1, 200, 0., 100.},
                      {"WCandWPtVElecDetEta", 31, -3.1, 3.1, 100, 0., 50.},
                      // Mt, electron pT, MET and W pT vs detector eta for spatial+E/p match (used for matrix method)
                      {"WCandMtVElecDetEta_Match", 31, -3.1, 3.1, 300, 50., 200.},
                      {"WCandElecPtVElecDetEta_Match", 31, -3.1, 3.1, 200, 0., 100.},
                      {"WCandMetVElecDetEta_Match", 31, -3.1, 3.1, 200, 0., 100.},
                      {"WCandWPtVElecDetEta_Match", 31, -3.1, 3.1, 100, 0., 50.},
                      // Mt, electron pT, MET and W pT vs detector eta for spatial only match (used for matrix method)
                      {"WCandMtVElecDetEta_Spatial_Match", 31, -3.1, 3.1, 300, 50., 200.},
                      {"WCandElecPtVElecDetEta_Spatial_Match", 31, -3.1, 3.1, 200, 0., 100.},
                      {"WCandMetVElecDetEta_Spatial_Match", 31, -3.1, 3.1, 200, 0., 100.},
                      {"WCandWPtVElecDetEta_Spatial_Match", 31, -3.1, 3.1, 100, 0., 50.},
		      // Electron pT vs uparallel
                      {"WCandElecPt_V_Upara", 100, 0., 50., 200, -50., 50.},
		      // SET
		      {"WCandScalarEtVElecPt_Spatial_Match", 100, 0., 100., 300, 0., 300.},
		      {"WCandNCaloCellsVInstLumi", 200, 0., 7000., 100, 0., 10.},
		      //Background Study
                      {"WCandMt_vs_DetEta", 31, -3.1, 3.1, 300, 50., 200.},
                      {"WCandElecPt_vs_DetEta", 31, -3.1, 3.1, 200, 0., 100.},
                      {"WCandMet_vs_DetEta", 31, -3.1, 3.1, 200, 0., 100.},
                      {"WCandMt_vs_DetEta_Spatial_Match", 31, -3.1, 3.1, 300, 50., 200.},
                      {"WCandElecPt_vs_DetEta_Spatial_Match", 31, -3.1, 3.1, 200, 0., 100.},
                      {"WCandMet_vs_DetEta_Spatial_Match", 31, -3.1, 3.1, 200, 0., 100.},
		      {"WCandScalarEt_V_Lumi2D",100, 0., 10.,  100, 0., 300.},  
                      {"", 0,0,0,0,0,0}};

//histograms for singularity variable
static HIST_1D WCand_Hist_SingVariable[] = {
                      {"WCandSingVariable", 200, -30., 30.},
                      {"WCandSingVariable_Spatial_Match", 200, -30., 30.},
                      {"", 0, 0, 0}};

// histograms for uparallel efficiency studies
static HIST_1D WCandUPara_Hist[]={
// for CC region
                      {"WCandUPara_notrkmatch_UPara", 120, -30, 30.},
                      {"WCandUPara_noIsoHMxCut", 120, -30, 30.},
                      {"WCandUParaETRatio_noIsoHMxCut", 120, -0.8, 0.8},
		      {"WCandUPara_trkmatch_UPara", 120, -30, 30.},
                      {"WCandUPara_notrkmatch_PassJet_UPara", 120, -30, 30.},
		      {"WCandUPara_trkmatch_PassJet_UPara", 120, -30, 30.},
		      // first require hmx and iso, check spatial track matching vs upara
		      {"WCandUPara_WithIsoHMxCut", 120, -30, 30.},
		      {"WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut", 120, -30, 30.},
		      {"WCandUParaETRatio_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut", 120, -0.8, 0.8},
		      {"WCandUPara_WithIsoHMxCut_trkmatch_noTrkPtCut", 120, -30, 30.},
		      {"WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut", 120, -30, 30.},
		      {"WCandUPara_WithIsoHMxCut_trkmatch", 120, -30, 30.},
		      // first require good spatial track match, check iso, hmx vs upara
		      {"WCandUPara_WithGoodSpatialMatch", 120, -30, 30.},
		      {"WCandUPara_WithGoodSpatialMatch_IsoHMxCut", 120, -30, 30.},
		      // first require spatial track match, check iso, hmx vs upara
		      {"WCandUPara_WithSpatialMatch", 120, -30, 30.},
		      {"WCandUPara_WithSpatialMatch_IsoHMxCut", 120, -30, 30.},
		      // for EC region
                      {"WCandUPara_notrkmatch_UPara_EC", 120, -30, 30.},
		      {"WCandUPara_trkmatch_UPara_EC", 120, -30, 30.},
                      {"WCandUPara_notrkmatch_PassJet_UPara_EC", 120, -30, 30.},
		      {"WCandUPara_trkmatch_PassJet_UPara_EC", 120, -30, 30.},
		      // first require hmx and iso, check spatial track matching vs upara
		      {"WCandUPara_WithIsoHMxCut_EC", 120, -30, 30.},
		      {"WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_noTrkPtCut_EC", 120, -30, 30.},
		      {"WCandUPara_WithIsoHMxCut_trkmatch_noTrkPtCut_EC", 120, -30, 30.},
		      {"WCandUPara_WithIsoHMxCut_trkmatch_noSMTHitCut_EC", 120, -30, 30.},
		      {"WCandUPara_WithIsoHMxCut_trkmatch_EC", 120, -30, 30.},
		      // first require good spatial track match, check iso, hmx vs upara
		      {"WCandUPara_WithGoodSpatialMatch_EC", 120, -30, 30.},
		      {"WCandUPara_WithGoodSpatialMatch_IsoHMxCut_EC", 120, -30, 30.},
		      // first require spatial track match, check iso, hmx vs upara
		      {"WCandUPara_WithSpatialMatch_EC", 120, -30, 30.},
		      {"WCandUPara_WithSpatialMatch_IsoHMxCut_EC", 120, -30, 30.},
{"", 0, 0, 0}
};

static HIST_2D WCandUPara_Hist_2D[]={
// for CC
//		      {"WCandIsoVsHMx7_notrkmatch_UPara", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx7_trkmatch_UPara", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx7_trkmatch_noTrkPtCut_noSMTHitCut_UPara", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx7_trkmatch_noTrkPtCut_UPara", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx7_trkmatch_noSMTHitCut_UPara", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx7_notrkmatch_PassJet_UPara", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx7_trkmatch_PassJet_UPara", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx7_trkmatch_noTrkPtCut_noSMTHitCut_PassJet_UPara", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx7_trkmatch_noTrkPtCut_PassJet_UPara", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx7_trkmatch_noSMTHitCut_PassJet_UPara", 240, 0, 60, 300, 0, 0.3},
		      // for EC
//		      {"WCandIsoVsHMx8_notrkmatch_UPara_EC", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx8_trkmatch_UPara_EC", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx8_trkmatch_noTrkPtCut_noSMTHitCut_UPara_EC", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx8_trkmatch_noTrkPtCut_UPara_EC", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx8_trkmatch_noSMTHitCut_UPara_EC", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx8_notrkmatch_PassJet_UPara_EC", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx8_trkmatch_PassJet_UPara_EC", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx8_trkmatch_noTrkPtCut_noSMTHitCut_PassJet_UPara_EC", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx8_trkmatch_noTrkPtCut_PassJet_UPara_EC", 240, 0, 60, 300, 0, 0.3},
//		      {"WCandIsoVsHMx8_trkmatch_noSMTHitCut_PassJet_UPara_EC", 240, 0, 60, 300, 0, 0.3},
                      {"WCandUPara_V_CosPhi_Denominator", 120, -30., 30., 20, -1., 1.},
                      {"WCandUPara_V_CosPhi_Numerator", 120, -30., 30., 20, -1., 1.},
                      {"WCandU_V_CosPhi_Denominator", 60, 0., 30., 20, -1., 1.},
                      {"WCandU_V_CosPhi_Numerator", 60, 0., 30., 20, -1., 1.},
                      {"", 0, 0, 0, 0, 0, 0}
};

static HIST_PROFILE WCandUPara_Hist_Profile[]={
		      {"", 0, 0, 0, 0, 0, ""}
};

// histograms used for JPsiMuAnalysis
static HIST_1D JPsiMuCand_Hist[]={
                      {"JPsiCandMuPt", 100, 0., 20.},
                      {"JPsiCandMuEta", 100, -3., 3.},
                      {"JPsiCandMuPhi", 70, 0., 7.},
                      {"JPsiCandMuInvPt", 100, 0., 0.5},
                      {"JPsiCandMuInvPt2", 100, 0., 0.25}, //(1/pT)^2 for both muons
                      {"JPsiCandSecMuPt", 100, 0., 20.},
                      {"JPsiCandSecMuInvPt", 100, 0., 0.5},
                      {"JPsiCandSecMuInvPt2", 100, 0., 0.25}, //(1/pT)^2 for the second muon
                      {"JPsiCandMuAngle", 50, 0., 4.}, //open angle between two muons
                      {"JPsiCandMass", 100, 2.5, 3.7},
                      {"JPsiCandPt", 200, 0., 20.},
                      {"JPsiCandMass_MuInvPt", 100, 2.5, 3.7},  // JPsi mass vs second muon curvature for each bin
                      {"JPsiCand_MuInvPt", 100, 0., 0.5}, // Second muon curvature for different mass bin
                      {"JPsiCandMass_MuInvPt2", 100, 2.5, 3.7},  // JPsi mass vs second muon curvature square for each bin
                      {"JPsiCand_MuInvPt2", 100, 0., 0.3}, // Second muon curvature square for different mass bin
                      {"JPsiCandMass_MuPt", 100, 2.5, 3.7},  // JPsi mass vs second muon pT for each bin
                      {"JPsiCand_MuPt", 100, 0., 20.}, // Second muon pT for different bin
                      {"JPsiCandMass_MuAveInvPt", 100, 2.5, 3.7},  // JPsi mass vs average muon curvature for each bin
                      {"JPsiCand_MuAveInvPt", 100, 0., 0.5}, // Average muon curvature for different bin
                      {"JPsiCandMass_MuAveInvPt2", 100, 2.5, 3.7},  // JPsi mass vs average muon curvature square for each bin
                      {"JPsiCand_MuAveInvPt2", 100, 0., 0.3}, // Average muon curvature square for different bin
                      {"JPsiCandMass_MuAvePt", 100, 2.5, 3.7},  // JPsi mass vs muonaverage pT for each bin
                      {"JPsiCand_MuAvePt", 100, 0., 20.}, // Average muon pT for different bin
                      {"JPsiCandMass_JPsiPt", 100, 2.5, 3.7},  // JPsi mass vs JPsi pT for each bin
                      {"JPsiCand_JPsiPt", 100, 0., 20.}, // JPsi pT for different bin
                      {"JPsiCandMass_DCosTheta", 100, 2.5, 3.7},  // JPsi mass vs delta_cosTheta for each bin
                      {"JPsiCand_DCosTheta", 100, -1.5, 1.5}, // delta_cosTheta for different bin
                      {"JPsiCandMass_SumInvSinTheta", 100, 2.5, 3.7},  // JPsi mass vs |1/sinTheta1|+|1/sinTheta2|
                      {"JPsiCand_SumInvSinTheta", 100, 0., 10.}, // |1/sinTheta1|+|1/sinTheta2|
                      {"JPsiCandMass_Run", 100, 2.5, 3.7}, //JPsi mass vs run range
                      {"JPsiCand_Run", 102, 163000, 197000},
                      // check JPsi mass vs JPsi phi for different eta region
                      {"JPsiCandMass_JPsiPhi_Eta1", 100, 2.5, 3.7},  // -1<eta<-0.6 
                      {"JPsiCand_JPsiPhi_Eta1", 100, 0., 20.},
                      {"JPsiCandMass_JPsiPhi_Eta2", 100, 2.5, 3.7},  // -0.6<eta<-0.2 
                      {"JPsiCand_JPsiPhi_Eta2", 100, 0., 20.},
                      {"JPsiCandMass_JPsiPhi_Eta3", 100, 2.5, 3.7},  // -0.2<eta<0.2 
                      {"JPsiCand_JPsiPhi_Eta3", 100, 0., 20.},
                      {"JPsiCandMass_JPsiPhi_Eta4", 100, 2.5, 3.7},  // 0.2<eta<0.6 
                      {"JPsiCand_JPsiPhi_Eta4", 100, 0., 20.},
                      {"JPsiCandMass_JPsiPhi_Eta5", 100, 2.5, 3.7},  // 0.6<eta<1.0 
                      {"JPsiCand_JPsiPhi_Eta5", 100, 0., 20.},
                      {"", 0, 0, 0}};

// histograms for ZMuAnalysis
static HIST_1D ZMuCand_Hist[]={
                      {"ZCandMass", 120, 30., 150.},
                      {"ZCandPt", 120, 0., 60.},
                      {"ZCandMuPt", 100, 0., 100.},
                      {"ZCandMuInvPt", 50, 0., 0.05},
                      {"ZCandMuInvPt2", 50, 0., 0.0025},
                      {"ZCandMuEta", 100, -3., 3.},
                      {"ZCandMuPhi", 70, 0., 7.},
                      {"ZCandCentralMuPt", 100, 0., 100.},
                      {"ZCandCentralMuInvPt", 50, 0., 0.05},
                      {"ZCandCentralMuInvPt2", 50, 0., 0.0025},
                      {"ZCandCentralMuEta", 100, -3., 3.},
                      {"ZCandCentralMuPhi", 70, 0., 7.},
                      {"ZMCMuInvpTDiff", 100, -0.4, 0.4},
                      {"ZMCMuPt", 100, 0., 100.},
                      {"ZMCMuInvPt", 100, 0.01, 0.05},
                      {"ZMCMuInvpTDiffSmear", 100, -0.4, 0.4},
                      {"ZMCMuPtSmear", 100, 0., 100.},
                      {"ZMCMuInvPtSmear", 50, 0.0, 0.05},
                      {"ZMCMassSmear", 120, 30., 150.},
                      {"ZMCPtSmear", 120, 0., 60.},
                      {"", 0, 0, 0}};

static HIST_PROFILE ZMuMC_Hist_Profile[]={
                      {"ZMCMuPt_V_ZRECOMuPt", 150, 0., 100., 0., 200., " "},
                      {"ZMCMuE_V_ZRECOMuE", 200, 0., 200., 0., 300., " "},
                      {"ZMCMuCurv_V_ZRECOMuCurv", 80, 0.01, 0.05, 0.005, 0.05, " "},
                      {"ZMCMuPt_V_ZSmearMuPt", 150, 0., 100., 0., 200., " "},
                      {"ZMCMuE_V_ZSmearMuE", 200, 0., 200., 0., 300., " "},
                      {"ZMCMuCurv_V_ZSmearMuCurv", 80, 0.01, 0.05, 0.005, 0.05, " "},
                      {"", 0, 0, 0, 0, 0, ""}};

// histograms for CosmicMuAnalysis
static HIST_1D CosmicMuCand_Hist[]={
                      {"CosmicCandTimeDiff", 300, -150., 150.},
                      {"CosmicCandSumEta", 200, -0.05, 0.05}, // sumEta after time difference requirement
                      {"CosmicCandSumPhi", 500, -0.02, 0.02}, // sumPhi after time difference requirement
                      {"CosmicCandSumEta2", 200, -0.05, 0.05}, // sumEta before time difference requirement
                      {"CosmicCandSumPhi2", 500, -0.02, 0.02}, // sumPhi before time difference requirement
                      {"CosmicCandMuEta", 60, -3., 3.},
                      {"CosmicCandMuPhi", 64, 0., 6.4},
                      {"CosmicCandMuPt", 100, 0., 100.},
                      {"CosmicCandDiffPt", 1000, -0.5, 0.5},
                      {"CosmicCandMuDca", 100, -0.1, 0.1}, // DCA distribution for two muons
                      {"CosmicCandSumEta_Run", 200, -0.05, 0.05}, // sumEta vs Run Number
                      {"CosmicCandSumPhi_Run", 500, -0.02, 0.02}, // sumPhi vs Run Number
                      {"CosmicCandSumEta_Polarity", 200, -0.05, 0.05}, // sumEta vs polarity
                      {"CosmicCandSumPhi_Polarity", 500, -0.02, 0.02}, // sumPhi vs polarity
                      {"CosmicCandSumEta_Eta", 200, -0.05, 0.05}, // sumEta for different eta region
                      {"CosmicCandSumPhi_Eta", 500, -0.02, 0.02}, // sumPhi for different eta region
                      {"CosmicCandSumEta_DetEta", 200, -0.05, 0.05}, // sumEta for different detector eta region
                      {"CosmicCandSumPhi_DetEta", 500, -0.02, 0.02}, // sumPhi for different detector eta region
                      {"CosmicCandMass", 200, 0., 200.},
                      {"CosmicCandPt", 120, 0., 60.},
                      {"", 0, 0, 0}};

// histograms for uEventAnalysis
static HIST_PROFILE UE_Hist_Profile[]={
                      {"sumsqrd5towE", 30, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towE2", 30, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towEME2", 30, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towFHE2", 30, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towE", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towEME", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towFHE", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towEt", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towEMEt", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towFHEt", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towE_Lumi", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towEME_Lumi", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towFHE_Lumi", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towEt_Lumi", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towEMEt_Lumi", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towFHEt_Lumi", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towE_UPara", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towEME_UPara", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towFHE_UPara", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towEt_UPara", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towEMEt_UPara", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towFHEt_UPara", 90, 0.05, 3.05, -1E30, 1E30, " "},
                      {"sum5towE_ElecDetEta", 44, -1.1, 1.1, -1E30, 1E30, " "},
                      {"sum5towEME_ElecDetEta", 44, -1.1, 1.1, -1E30, 1E30, " "},
                      {"sum5towFHE_ElecDetEta", 44, -1.1, 1.1, -1E30, 1E30, " "},
                      {"sum5towEt_ElecDetEta", 44, -1.1, 1.1, -1E30, 1E30, " "},
                      {"sum5towEMEt_ElecDetEta", 44, -1.1, 1.1, -1E30, 1E30, " "},
                      {"sum5towFHEt_ElecDetEta", 44, -1.1, 1.1, -1E30, 1E30, " "},
                      {"sum5towE_ElecDetPhi", 64, 0., TMath::TwoPi(), -1E30, 1E30, " "},
                      {"sum5towEME_ElecDetPhi", 64, 0., TMath::TwoPi(), -1E30, 1E30, " "},
                      {"sum5towFHE_ElecDetPhi", 64, 0., TMath::TwoPi(), -1E30, 1E30, " "},
                      {"sum5towEt_ElecDetPhi", 64, 0., TMath::TwoPi(), -1E30, 1E30, " "},
                      {"sum5towEMEt_ElecDetPhi", 64, 0., TMath::TwoPi(), -1E30, 1E30, " "},
                      {"sum5towFHEt_ElecDetPhi", 64, 0., TMath::TwoPi(), -1E30, 1E30, " "},
		      {"deltaEvjunjie", 750, 0.,2.5,-10.,10.," "},
		      {"deltauncorrEvjunjie", 750, 0.,2.5,-10.,10.," "},
		      {"deltaeconevjunjie", 750, 0.,2.5,-10.,10.," "},
		      {"deltaoeconevjunjie", 750, 0.,2.5,-10.,10.," "},
		      {"deltaEvfeng", 750, 0.,2.5,-10.,10.," "},
		      {"deltauncorrEvfeng", 750, 0.,2.5,-10.,10.," "},
		      {"deltaeconevfeng", 750, 0.,2.5,-10.,10.," "},
		      {"deltaoeconevfeng", 750, 0.,2.5,-10.,10.," "},
                      {"", 0, 0, 0, 0, 0, ""}};

static HIST_1D UE_Hist[]={
                      {"InstLumi", 250, 0., 10.},
                      {"InstLumiReweight", 250, 0., 10.},
                      {"UPara", 240, -30., 30.},
                      {"deltaE_UPara", 200, 0., 1.},
                      {"deltaEME_UPara", 200, 0., 1.},
                      {"deltaFHE_UPara", 200, 0., 1.},
                      {"deltaEt_UPara", 200, 0., 1.},
                      {"deltaEMEt_UPara", 200, 0., 1.},
                      {"deltaFHEt_UPara", 200, 0., 1.},
                      {"sum13towE_Lumi", 500, 0., 5.},
                      {"sum13towEME_Lumi", 500, 0., 5.},
                      {"sum13towFHE_Lumi", 500, 0., 5.},
                      {"sum13towEt_Lumi", 500, 0., 5.},
                      {"sum13towEMEt_Lumi", 500, 0., 5.},
                      {"sum13towFHEt_Lumi", 500, 0., 5.},
                      {"sum13towE_UPara", 500, 0., 5.},
                      {"sum13towEME_UPara", 500, 0., 5.},
                      {"sum13towFHE_UPara", 500, 0., 5.},
                      {"sum13towEt_UPara", 500, 0., 5.},
                      {"sum13towEMEt_UPara", 500, 0., 5.},
                      {"sum13towFHEt_UPara", 500, 0., 5.},
                      {"sum13towE_Lumi_New", 500, 0., 5.},
                      {"sum13towEME_Lumi_New", 500, 0., 5.},
                      {"sum13towFHE_Lumi_New", 500, 0., 5.},
                      {"sum13towEt_Lumi_New", 500, 0., 5.},
                      {"sum13towEMEt_Lumi_New", 500, 0., 5.},
                      {"sum13towFHEt_Lumi_New", 500, 0., 5.},
                      {"sum13towE_UPara_New", 500, 0., 5.},
                      {"sum13towEME_UPara_New", 500, 0., 5.},
                      {"sum13towFHE_UPara_New", 500, 0., 5.},
                      {"sum13towEt_UPara_New", 500, 0., 5.},
                      {"sum13towEMEt_UPara_New", 500, 0., 5.},
                      {"sum13towFHEt_UPara_New", 500, 0., 5.},
                      // divide events into 21 luminosity bins and then for each luminosity bins, divide into 13 upara bins
                      {"sum13towEt_Lumi_0_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_1_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_2_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_3_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_4_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_5_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_6_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_7_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_8_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_9_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_10_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_11_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_12_Upara", 500, 0., 5.},
		      {"sum13towEt_Lumi_13_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_14_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_15_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_16_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_17_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_18_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_19_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_20_Upara", 500, 0., 5.},
                      {"sum13towEt_Lumi_21_Upara", 500, 0., 5.},
                     
                      // divide events into 13 upara bins and then for each luminosity bins, divide into 13 luminosity bins
                      {"sum13towEt_Upara_0_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_1_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_2_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_3_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_4_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_5_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_6_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_7_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_8_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_9_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_10_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_11_Lumi", 500, 0., 5.},
                      {"sum13towEt_Upara_12_Lumi", 500, 0., 5.},

                      {"CellE", 600, -0.5, 19.5},
                      {"CellEME", 600, -0.5, 19.5},
                      {"CellFHE", 600, -0.5, 19.5},
                      {"", 0, 0, 0}};

// histograms used for ZNuNuAnalysis
// all events that passed EvtSelector, ObjSelector,
// recoul Ut cuts, SET cuts and kinematical cuts applied to neutrinos 
static HIST_1D ZNuNu_Hist[]={
                      {"ZNuNu_genZPt_Cuts", 300, 0., 150.},
                      {"ZNuNu_genZPhi_Cuts", 64, 0., TMath::TwoPi()},
                      {"ZNuNu_RecoilResolution_Cuts", 100, -2., 2.},
                      {"ZNuNu_RecoilPt_Cuts", 100, 0., 50.},
                      {"ZNuNu_RecoilPx_Cuts", 200, -50., 50.},
                      {"ZNuNu_RecoilPy_Cuts", 200, -50., 50.},
                      {"ZNuNu_RecoilPhi_Cuts", 64, 0., TMath::TwoPi()},
                      {"ZNuNu_genVtxZ_Cuts", 320, -80., 80.},
                      {"ZNuNu_VtxZ_Cuts", 320, -80., 80.},
                      {"ZNuNu_DeltaPhi_genZ_Recoil_Cuts", 64, 0., TMath::Pi()},
		      {"ZNuNu_Met_Cuts", 100, 0., 50.},
		      {"ZNuNu_MetPhi_Cuts", 64, 0., TMath::Pi()},
		      {"ZNuNu_MetX_Cuts", 200, -50., 50.},
		      {"ZNuNu_MetY_Cuts", 200, -50., 50.},
		      {"ZNuNu_ScalarEt_Cuts", 300, 0., 300.},
                      {"", 0, 0, 0}};

// profiles used for ZNuNuAnalysis
// all events that passed EvtSelector, ObjSelector,
// recoul Ut cuts, SET cuts and kinematical cuts applied to neutrinos 
static HIST_PROFILE ZNuNu_Profile[]={
                      {"ZNuNu_RecoilResponse_V_RecoilPt_Cuts", 50, 0, 50, -20., 20., " "},
                      {"ZNuNu_RecoilResponse_V_genZPt_Cuts", 50, 0, 50, -20., 20., " "},
                      {"ZNuNu_RecoilResponseProjection_V_RecoilPt_Cuts", 50, 0, 50, -20., 20., " "},
                      {"ZNuNu_RecoilResponseProjection_V_genZPt_Cuts", 50, 0, 50, -20., 20., " "},
                      {"", 0, 0, 0, 0, 0, " "}};

// histograms used by ZNuNuAnalysis for special Recoil Et flow studies
// all events that passed EvtSelector, ObjSelector,
// recoul Ut cuts, SET cuts and kinematical cuts applied to neutrinos 
static HIST_1D ZNuNu_EtFlow_Hist[]={
  {"ZNuNu_EtFlow_VtxZ_Cuts", 
   320, -80., 80.},
  {"ZNuNu_EtFlow_genVtxZ_Cuts", 
   320, -80., 80.},
  {"ZNuNu_EtFlow_genZPt_Cuts",
   200, 0.0, 100.0},
  {"ZNuNu_EtFlow_genUt_Cuts",
   200, 0.0, 100.0},
  {"ZNuNu_EtFlow_recoUt_Cuts",
   200, 0.0, 100.0},
  {"ZNuNu_EtFlow_recoRecoilPhi_Cuts",
   100, 0.0, TMath::TwoPi()},
  {"ZNuNu_EtFlow_recoRecoilResp_Cuts",
   200, 0.0, 10.0},
  {"ZNuNu_EtFlow_recoRecoilRespPrj_Cuts",
   220, -10.0, 100.0},
  {"ZNuNu_EtFlow_DPhi_recoUt_genZPt_Cuts",
   100, 0.0, TMath::Pi()},
  {"ZNuNu_EtFlow_DPhi_CellsUt_recoUt_Cuts",
   100, 0.0, TMath::Pi()},
  //  {"ZNuNu_EtFlow_DPhi_CellsScaledUt_recoUt_Cuts",
  //   100, 0.0, TMath::Pi()},
  //  {"ZNuNu_EtFlow_DPhi_XCHECKrecoUt_recoUt_Cuts",
  //   100, 0.0, TMath::Pi()},
  {"ZNuNu_EtFlow_CellsUt_Cuts",
   200, 0.0, 100.0},
  //  {"ZNuNu_EtFlow_CellsScaledUt_Cuts",
  //   200, 0.0, 100.0},
  {"ZNuNu_EtFlow_CellsRecoilPhi_Cuts",
   200, 0.0, TMath::TwoPi()},
  //  {"ZNuNu_EtFlow_CellsScaledRecoilPhi_Cuts",
  //   200, 0.0, TMath::TwoPi()},
  {"ZNuNu_EtFlow_CellsRecoilResp_Cuts",
   200, 0.0, 10.0},
  //  {"ZNuNu_EtFlow_CellsScaledRecoilResp_Cuts",
  //   200, 0.0, 10.0},
  {"ZNuNu_EtFlow_CellsRecoilRespPrj_Cuts",
   220, -10.0, 100.0},
  //  {"ZNuNu_EtFlow_CellsScaledRecoilRespPrj_Cuts",
  //   220, -10.0, 100.0},
  //  {"ZNuNu_EtFlow_XCHECKrecoRecoilRespPrj_Cuts",
  //   220, -10.0, 100.0},
  {"ZNuNu_EtFlow_Et_wrt_genUt_Cuts",
   4000, 0.0, 1000.},
  {"", 0, 0, 0}};

// histograms used for ZNuNuAnalysis (special Recoil Et flow studies)
// all events that passed EvtSelector, ObjSelector,
// recoul Ut cuts, SET cuts and kinematical cuts applied to neutrinos 
static HIST_PROFILE ZNuNu_EtFlow_Profile[]={
  {"ZNuNu_EtFlow_recoRecoilResp_V_genZPt_Cuts",
   200, 0.0, 100.0, 0, 0, " "},
  {"ZNuNu_EtFlow_recoRecoilRespPrj_V_genZPt_Cuts",
   200, 0.0, 100.0, 0, 0, " "},
  {"ZNuNu_EtFlow_recoUt_V_DPhi_recoUt_genZPt_Cuts",
   100, 0.0, TMath::Pi(), 0, 0, " "},
  {"ZNuNu_EtFlow_CellsUt_V_DPhi_CellsUt_genZPt_Cuts",
   100, 0.0, TMath::Pi(), 0, 0, " "},
  //  {"ZNuNu_EtFlow_CellsScaledUt_V_DPhi_CellsScaledUt_genZPt_Cuts",
  //   100, 0.0, TMath::Pi(), 0, 0, " "},
  {"ZNuNu_EtFlow_AveEt_V_iphi_wrt_genZPt_Cuts",
   64, -31.0, 33.0, 0, 0, " "},
  //  {"ZNuNu_EtFlow_AveEtScaled_V_iphi_wrt_genZPt_Cuts",
  //   64, -31.0, 33.0, 0, 0, " "},
  {"", 0, 0, 0, 0, 0, " "}};

static HIST_PROFILE_2D ZNuNu_EtFlow_Profile_2D[]={
  {"ZNuNu_EtFlow_AveEt_V_iphi_V_genZPt_Cuts",
   64, -31.0, 33.0, 200, 0., 100., 0, 0, " "},
  {"", 0, 0, 0, 0, 0, 0, 0, 0, " "}};
  

// histograms used for ZNuNuAnalysis (special Recoil Et flow studies)
// all events that passed EvtSelector, ObjSelector,
// recoul Ut cuts, SET cuts and kinematical cuts applied to neutrinos 
#define _NPTBINS_ 27
#define _PTBINS_  {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,18,21,24,27,30,35,40,50,60,70,80,90}
static HIST_PROFILE_VARBIN ZNuNu_EtFlow_Profile_VarX[]={
  {"ZNuNu_EtFlow_genZPt_V_genZPt_Cuts", 
   _NPTBINS_, _PTBINS_, 0.0, 100.0, " "},
  {"", 0, {0}, 0, 0, " "}};
#undef _NPTBINS_
#undef _PTBINS_

// histograms for EMF study
#define EMFstudyWindowLow 80
#define EMFstudyWindowHigh 103
#define EMFstudyWindowNBins 40
static HIST_1D EMFstudy_Hist[]={
  {"mass", EMFstudyWindowNBins, EMFstudyWindowLow, EMFstudyWindowHigh},
  {"pT", 40, 0, 100},
  {"RunNumZee", 1000, 166000, 300000},
  {"InstLumZee", 100, 0, 400},
  {"nVtxZee", 16, -0.5, 15.5},
  {"E1pT", 40, 25, 100},
  {"E2pT", 40, 25, 100},
  {"E1E", 40, 25, 120},
  {"E2E", 40, 25, 120},
  {"E1physeta", 160, -1.6, 1.6},
  {"E2physeta", 160, -1.6, 1.6},
  {"E1deteta", 160, -1.6, 1.6},
  {"E2deteta", 160, -1.6, 1.6},
  //
  {"E1emf", 40, 0, 1},
  {"E2emf", 40, 0, 1},
  {"Eemf", 40, 0, 1},
  //
  {"EemfB", 40, 0, 1},
  //
  {"massK", EMFstudyWindowNBins, EMFstudyWindowLow, EMFstudyWindowHigh},
  {"InstLumZeeK", 100, 0, 400},
  {"pTK", 40, 0, 100},
  {"E1pTK", 40, 25, 100},
  {"E2pTK", 40, 25, 100},
  {"E1EK", 40, 25, 120},
  {"E2EK", 40, 25, 120},
  {"E1physetaK", 160, -1.6, 1.6},
  {"E2physetaK", 160, -1.6, 1.6},
  {"E1detetaK", 160, -1.6, 1.6},
  {"E2detetaK", 160, -1.6, 1.6},
  //
  {"E1emfK", 40, 0, 1},
  {"E2emfK", 40, 0, 1},
  {"EemfK", 40, 0, 1},
  //
  {"massKD", EMFstudyWindowNBins, EMFstudyWindowLow, EMFstudyWindowHigh},
  {"InstLumZeeKD", 100, 0, 400},
  {"pTKD", 40, 0, 100},
  {"E1pTKD", 40, 25, 100},
  {"E2pTKD", 40, 25, 100},
  {"E1EKD", 40, 25, 120},
  {"E2EKD", 40, 25, 120},
  {"E1physetaKD", 160, -1.6, 1.6},
  {"E2physetaKD", 160, -1.6, 1.6},
  {"E1detetaKD", 160, -1.6, 1.6},
  {"E2detetaKD", 160, -1.6, 1.6},
  //
  {"E1emfKD", 40, 0, 1},
  {"E2emfKD", 40, 0, 1},
  {"EemfKD", 40, 0, 1},
  //
  //
  {"ECmass", EMFstudyWindowNBins, EMFstudyWindowLow, EMFstudyWindowHigh},
  {"ECpT", 40, 0, 100},
  {"ECRunNumZee", 1000, 166000, 300000},
  {"ECInstLumZee", 100, 0, 400},
  {"ECnVtxZee", 16, -0.5, 15.5},
  {"ECE1pT", 40, 25, 100},
  {"ECE2pT", 40, 25, 100},
  {"ECE1E", 40, 25, 300},
  {"ECE2E", 40, 25, 300},
  {"ECE1physeta", 160, -3.2, 3.2},
  {"ECE2physeta", 160, -3.2, 3.2},
  {"ECE1deteta", 160, -3.2, 3.2},
  {"ECE2deteta", 160, -3.2, 3.2},
  //
  {"ECE1emf", 40, 0, 1},
  {"ECE2emf", 40, 0, 1},
  {"ECEemf", 40, 0, 1},
  //
  {"ECmassB", EMFstudyWindowNBins, EMFstudyWindowLow, EMFstudyWindowHigh},
  {"ECInstLumZeeB", 100, 0, 400},
  {"ECpTB", 40, 0, 100},
  {"ECE1pTB", 40, 25, 100},
  {"ECE2pTB", 40, 25, 100},
  {"ECE1EB", 40, 25, 300},
  {"ECE2EB", 40, 25, 300},
  {"ECE1physetaB", 160, -3.2, 3.2},
  {"ECE2physetaB", 160, -3.2, 3.2},
  {"ECE1detetaB", 160, -3.2, 3.2},
  {"ECE2detetaB", 160, -3.2, 3.2},
  //
  {"ECE1emfB", 40, 0, 1},
  {"ECE2emfB", 40, 0, 1},
  {"ECEemfB", 40, 0, 1},
  {"", 0, 0, 0}};

// histograms for single photon study
static HIST_1D Photon_Hist1D[]={
  {"NumCells", 50, 0, 50},
  {"Gen_Photon_Energy", 50, 0, 2.5}, 
  {"Gen_Photon_Energy_reach", 50, 0, 2.5},
  {"Gen_Photon_Energy_reach03", 50, 0, 2.5},
  {"Gen_Photon_Num", 10, 0, 10},
  {"Gen_Photon_Eta", 23, -1.15, 1.15},
  {"Gen_Photon_Phi", 64, 0, 6.4},
  {"Gen_Photon_VtxZ", 60, -60, 60},
  {"", 0, 0, 0}
};

static HIST_2D Photon_Hist2D[]={
  {"Photon_Response_scatter", 100, 0, 30, 200, 0., 5.},
  {"Photon_Response03_scatter", 100, 0, 30, 200, 0., 5.}, // only consider calo cells within dR<0.3 of gen level photon direction 
  {"", 0, 0, 0, 0, 0, 0}
};

static HIST_PROFILE Photon_Profile[]={
  {"Photon_Response", 50, 0, 30, 0., 5., " "}, 
  {"Photon_Response03", 50, 0, 30, 0., 5., " "}, // only consider calo cells within dR<0.3 of gen level photon direction
  {"", 0, 0, 0, 0, 0, " "}
};

// histograms used for EvtSelector
// check some general hitograms
static HIST_1D General_Hist[]={
  {"RunNo", 1120, 160000, 216000},
  {"", 0, 0, 0}};
#endif

//
// Supported histogram types are:
//
// HIST_1D 
//   1D histogram having constant bin widths 
//   Initialization format: {"TITLE", Nbins_x, X_min, X_max } 
//
// HIST_1D_VARBIN
//   1D histogram having variable bin widths (up to 50 bins) 
//   Initialization format: {"TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)} }
//   NOTE: Array of bin boundaries has to have (Nbins_x+1) elements!
//
// HIST_PROFILE 
//   1D profile histogram having constant bin widths 
//   Initialization format: {"TITLE", Nbins_x, X_min, X_max, Y_min, Y_max, ErrorOption } 
//   NOTE: Only Y values between Y_min and Y_max will be taken into account. 
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile::GetErrorOption() documentation.
//
// HIST_PROFILE_VARBIN
//   1D profile histogram having constant bin widths 
//   Initialization format: {"TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)}, Y_min, Y_max, ErrorOption } 
//   NOTE: Only Y values between Y_min and Y_max will be taken into account. 
//   NOTE: Array of bin boundaries has to have (Nbins_x+1) elements!
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile::GetErrorOption() documentation.
//
// HIST_2D 
//   2D histogram having constant X and Y bin widths 
//   Initialization format: {"TITLE", Nbins_x, X_min, X_max, 
//                                    Nbins_y, Y_min, Y_max } 
//
// HIST_2D_VARBIN_X
//   2D histogram having variable X- and constant Y bin widths 
//   Initialization format: {"TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)}, 
//                                    Nbins_y, Y_min, Y_max } 
//   NOTE: Array of bin boundaries for X axis has to have (Nbins_x+1) elements!
//
// HIST_2D_VARBIN_Y
//   2D histogram having constant X- and variable Y bin widths 
//   Initialization format: {"TITLE", Nbins_x, X_min, X_max, 
//                                    Nbins_y, {Y(0), Y(1), ..., Y(Nbins_y)} } 
//   NOTE: Array of bin boundaries for Y axis has to have (Nbins_y+1) elements!
//
// HIST_2D_VARBIN_XY
//   2D histogram having variable X and Y bin widths 
//   Initialization format: {"TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)}, 
//                                    Nbins_y, {Y(0), Y(1), ..., Y(Nbins_y)} } 
//   NOTE: Arrays of bin boundaries for X and Y axes have to have (Nbins_x+1) and (Nbins_y+1) elements, respectively!
//
// HIST_PROFILE_2D 
//   2D profile histogram having constant X and Y bin widths 
//   Initialization format: {"TITLE", Nbins_x, X_min, X_max, 
//                                    Nbins_y, Y_min, Y_max, Z_min, Z_max, ErrorOption } 
//   NOTE: Only Z values between Z_min and Z_max will be taken into account. 
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile2D::GetErrorOption() documentation.
//
// HIST_PROFILE_2D_VARBIN_X
//   2D profile histogram having variable X- and constant Y bin widths 
//   Initialization format: {"TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)}, 
//                                    Nbins_y, Y_min, Y_max, Z_min, Z_max, ErrorOption } 
//   NOTE: Only Z values between Z_min and Z_max will be taken into account. 
//   NOTE: Array of bin boundaries for X axis has to have (Nbins_x+1) elements!
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile2D::GetErrorOption() documentation.
//
// HIST_PROFILE_2D_VARBIN_Y
//   2D profile histogram having constant X- and variable Y bin widths 
//   Initialization format: {"TITLE", Nbins_x, X_min, X_max, 
//                                    Nbins_y, {Y(0), Y(1), ..., Y(Nbins_y)}, Z_min, Z_max, ErrorOption } 
//   NOTE: Only Z values between Z_min and Z_max will be taken into account. 
//   NOTE: Array of bin boundaries for Y axis has to have (Nbins_y+1) elements!
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile2D::GetErrorOption() documentation.
//
// HIST_PROFILE_2D_VARBIN_XY
//   2D profile histogram having variable X and Y bin widths 
//   Initialization format: {"TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)}, 
//                                    Nbins_y, {Y(0), Y(1), ..., Y(Nbins_y)}, Z_min, Z_max, ErrorOption } 
//   NOTE: Only Z values between Z_min and Z_max will be taken into account. 
//   NOTE: Arrays of bin boundaries for X and Y axes have to have (Nbins_x+1) and (Nbins_y+1) elements, respectively!
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile2D::GetErrorOption() documentation.
//
 

