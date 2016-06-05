#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "wmass_analysis/EMSelector.hpp"
#include "wmass_analysis/EffAnalysis.hpp"
#include "wmass_analysis/histograms.hpp"
#include "wmass_util/TriggerManager.hpp"
#include "wmass_util/hist_files.hpp"
#include <TFile.h>

using namespace std;
using namespace cafe;


bool TrackPhiFiducial(CAFEMObj* emobj, cafe::Event& event);
EffAnalysis::EffAnalysis(const char *name)
  : Processor(name)
{
  Config config(name);
  
  // debug level
  _debugLevel = config.get("debugLevel", 0);
  // truth mode
  _truthMode = config.get("truthMode", 0);
  cout<<"Truth Mode: "<<_truthMode<<endl;

  // switches to control "details" in the different Tag&Probe analyses
  _TPhmx_DoTheTrackFirst = config.get("TPhmx_DoTheTrackFirst", true);
  _TPtrk_IncludeECtag = config.get("TPtrk_IncludeECtag", true);
  _TPtrk_TrigMatchOnTag_not_on_EitherObject = config.get("TPtrk_TrigMatchOnTag_not_on_EitherObject", false);
  _TPtrk_DoTheStepByStepThing = config.get("TPtrk_DoTheStepByStepThing", false);
  
  _useTrackFiducial = config.get("UseTrackPhiFiducial", true);
  
  // MC study
  _MCStudy = config.get("MCStudy", false);
  
  // efficiencies for different cuts
  _EMFracCut = config.get("EMFracCut", 0.9);
  _IsoCut = config.get("IsoCut", 0.15);
  _HM7Cut = config.get("HM7Cut", 12.);
  _HM8Cut = config.get("HM8Cut", 20.);
  _ElecPtCut = config.get("ElecPtCut", 25.);

  _DetEtaCC = config.get("DetEtaCC", 1.1);
  _DetEtaEC1 = config.get("DetEtaEC1", 1.5);
  _DetEtaEC2 = config.get("DetEtaEC2", 2.5);
  
  // Z boson mass, UT cuts 
  _ZMassCut1 = config.get("ZMassCut1", 70.);
  _ZMassCut2 = config.get("ZMassCut2", 110.);
  _ZUtCut = config.get("ZUtCut", 999.);

  // Track selection requirements
  _coneSize_Trk = config.get("coneSize_Trk", 0.2);
  _sumPtCut_Trk = config.get("sumPtCut_Trk", 5.);

  _DropTriggerObjectMatchRequirement = config.get("DropTriggerObjectMatchRequirement", false);

  _InstLumi_lowcut  = config.get("InstLumi_lowcut", 100.);
  _InstLumi_highcut = config.get("InstLumi_highcut", 100.);

  _emclusposcorr = new EMClusterPosCorr(config);

  // trigger names
  _trignames[0] = config.getVString("TrigNames_V0810", " ");
  _trignames[1] = config.getVString("TrigNames_V11", " ");
  _trignames[2] = config.getVString("TrigNames_V12", " ");
  _trignames[3] = config.getVString("TrigNames_V13", " ");
  _trignames[4] = config.getVString("TrigNames_V14", " ");
  _trignames[5] = config.getVString("TrigNames_V15", " ");
  _trignames[6] = config.getVString("TrigNames_V16", " ");
  _trignames[7] = config.getVString("TrigNames_V16h", " ");
 
  cout<<"Trigger names: "<<endl;
  for(int i=0; i<8; i++) {
    for(int j=0; j<_trignames[i].size(); j++) cout<<_trignames[i][j]<<" ";
  }
  cout<<endl;

  ////Recoil config
  _dorawCellsRecoil = config.get("dorawCellsRecoil", true);
  _useConsistentMET = config.get("useConsistentMET", true);

  // histograms
  _histos.add(Eff_Hist);
  _histos.add(Eff_Hist_2D);
  _histos.add(Eff_Hist_varbinY_2D);
  _histos.add(LumiEff_Hist);
  
  _histos.clone("InstLumi_bare",3);
  _histos.clone("InstLumi_trig", 3);
  _histos.clone("InstLumi_2EM_20", 3);
  _histos.clone("InstLumi_2EM_25", 3);
  _histos.clone("InstLumi_CCCC", 3);
  _histos.clone("InstLumi_etafid", 3);
  _histos.clone("InstLumi_trkfid", 3);
  _histos.clone("InstLumi_trk", 3);
  _histos.clone("InstLumi_preseltrk", 3);
  _histos.clone("InstLumi_emiso", 3);
  _histos.clone("InstLumi_hmx", 3);
  _histos.clone("InstLumi_vtx", 3);
	
  	
  
  // clone histograms for trigger efficiency studies
  // 5 trigger list so far, each trigger list at most contains 5 triggers
  _histos.clone("InvMass_EM_Probe_Trig_All_Triglist", 8);
  _histos.clone("DetEta_EM_Probe_Trig_All_Triglist", 8);
  _histos.clone("PhysEta_EM_Probe_Trig_All_Triglist", 8);
  _histos.clone("DetPhi_EM_Probe_Trig_All_Triglist", 8);
  _histos.clone("Pt_EM_Probe_Trig_All_Triglist", 8);
  _histos.clone("Pt_DetEta_EM_Probe_Trig_All_Triglist", 8);
  _histos.clone("Pt_PhysEta_EM_Probe_Trig_All_Triglist", 8);
  _histos.clone("InvMass_DetEta_EM_Probe_Trig_All_Triglist", 8);
  _histos.clone("InvMass_PhysEta_EM_Probe_Trig_All_Triglist", 8);
  _histos.clone("Pt_InvMass_EM_Probe_Trig_All_Triglist", 8);
 
  
  // for all triggers in one trigger list
  _histos.clone("InvMass_EM_Probe_Trig_Matched_Triglist", 8);
  _histos.clone("DetEta_EM_Probe_Trig_Matched_Triglist", 8);
  _histos.clone("PhysEta_EM_Probe_Trig_Matched_Triglist", 8);
  _histos.clone("DetPhi_EM_Probe_Trig_Matched_Triglist", 8);
  _histos.clone("Pt_EM_Probe_Trig_Matched_Triglist", 8);
  _histos.clone("Pt_DetEta_EM_Probe_Trig_Matched_Triglist", 8);
  _histos.clone("Pt_PhysEta_EM_Probe_Trig_Matched_Triglist", 8);
  _histos.clone("InvMass_DetEta_EM_Probe_Trig_Matched_Triglist", 8);
  _histos.clone("InvMass_PhysEta_EM_Probe_Trig_Matched_Triglist", 8);
  _histos.clone("Pt_InvMass_EM_Probe_Trig_Matched_Triglist", 8);

  _histos.clone("Pt_EM_Probe_Trig_Matched_v16_Both",1);
  _histos.clone("Pt_EM_Probe_Trig_Matched_v16_27",1);
  _histos.clone("Pt_EM_Probe_Trig_Matched_v16_25",1);
  _histos.clone("Pt_EM_Probe_Trig_Matched_v15",1);
 
   _histos.clone("Pt_EM_Probe_Trig_v16_27_7", 1);
  _histos.clone("Pt_EM_Probe_Trig_v16_25",1);
  _histos.clone("Pt_EM_Probe_Trig_v16_27",1);
  
  _histos.clone("Pt_EM_Probe_Trig_TT_v16_27_7", 1);
  _histos.clone("Pt_EM_Probe_Trig_TT_v16_25",1);
  _histos.clone("Pt_EM_Probe_Trig_TT_v16_27",1);

  _histos.clone("Pt_EM_Probe_Trig_v16_27_7_lumi", 1);
  _histos.clone("Pt_EM_Probe_Trig_v16_25_lumi",1);
  _histos.clone("Pt_EM_Probe_Trig_v16_27_lumi",1);
  
  _histos.clone("Pt_EM_Probe_Trig_TT_v16_27_7_lumi", 1);
  _histos.clone("Pt_EM_Probe_Trig_TT_v16_25_lumi",1);
  _histos.clone("Pt_EM_Probe_Trig_TT_v16_27_lumi",1);

  // for each trigger
   _histos.clone("Pt_EM_Probe_Trig_All", 7, 5);
   
  _histos.cloneArray("InvMass_EM_Probe_Trig_Matched", 8, 5);
  _histos.cloneArray("DetEta_EM_Probe_Trig_Matched", 8, 5);
  _histos.cloneArray("PhysEta_EM_Probe_Trig_Matched", 8, 5);
  _histos.cloneArray("DetPhi_EM_Probe_Trig_Matched", 8, 5);
  _histos.cloneArray("Pt_EM_Probe_Trig_Matched", 8, 5);
  _histos.cloneArray("Pt_EM_Probe_L1_Matched", 8, 5);
  _histos.cloneArray("Pt_EM_Probe_L2_Matched", 8, 5);
  _histos.cloneArray("Pt_EM_Probe_L3_Matched", 8, 5);
  _histos.cloneArray("l1Pt_EM_Probe_L1_Matched", 8, 5);
  _histos.cloneArray("l2Pt_EM_Probe_L2_Matched", 8, 5);
  _histos.cloneArray("l3Pt_EM_Probe_L3_Matched", 8, 5);
  
  _histos.cloneArray("Pt_DetEta_EM_Probe_Trig_Matched", 8, 5);
  _histos.cloneArray("Pt_PhysEta_EM_Probe_Trig_Matched", 8, 5);
  _histos.cloneArray("InvMass_DetEta_EM_Probe_Trig_Matched", 8, 5);
  _histos.cloneArray("InvMass_PhysEta_EM_Probe_Trig_Matched", 8, 5);
  _histos.cloneArray("Pt_InvMass_EM_Probe_Trig_Matched", 8, 5);

  // For Loose Track Match
   //next three are varbin
  _histos.clone("loose_ZMass_vs_Pt_Before_Trk_CC", 1);
  _histos.clone("loose_ZMass_vs_Pt_Before_Trk_TAG" , 1);
  _histos.clone("loose_ZMass_vs_Pt_After__Trk_CC", 1);
  //
  _histos.clone("loose_ZMass_vs_DetEta_Before_Trk_CC", 1);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_CC", 1);
  _histos.clone("loose_ZMass_vs_DetEta_Before_Trk_TAG", 1);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_TAG", 1);
  _histos.clone("loose_ZMass_vs_DetEta_After_Trk_CC", 1);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_CC", 1);

  // for track match (for loose track match ?)
  _histos.clone("loose_EMEta_EM_Probe_Trk", 2);
  _histos.clone("loose_EMPt_EM_Probe_Trk", 2);
  _histos.clone("loose_EMEta_EM_Probe_Trk_Matched", 2);
  _histos.clone("loose_EMPt_EM_Probe_Trk_Matched", 2);
  _histos.clone("loose_EMEta_EM_Probe_Spatial_Trk_Matched", 2);
  _histos.clone("loose_EMPt_EM_Probe_Spatial_Trk_Matched", 2);

  // for different primary vertex region
  // 5 vertex regions: <-40, between -40 and -10, between -10 and 10, between 10 and 40, >40
  _histos.clone("loose_EMDetEta_EM_Probe_Trk_All_Vtx", 12);
  _histos.clone("loose_EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx", 12);
  _histos.clone("loose_EMEta_EM_Probe_Trk_All_Vtx", 12);
  _histos.clone("loose_EMEta_EM_Probe_Spatial_Trk_Matched_Vtx", 12);
  _histos.clone("loose_EMPt_EM_Probe_Trk_All_CC_Vtx", 12);
  _histos.clone("loose_EMPt_EM_Probe_Spatial_Trk_Matched_CC_Vtx", 12);
  _histos.clone("loose_EMPt_EM_Probe_Trk_All_EC_Vtx", 12);
  _histos.clone("loose_EMPt_EM_Probe_Spatial_Trk_Matched_EC_Vtx", 12);

  // mass before and after track matching for different vertex and eta regions
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC", 12);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC", 12);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_0", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_1", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_2", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_3", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_4", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_5", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_6", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_7", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_8", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_9", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_10", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_11", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_0", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_1", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_2", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_3", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_4", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_5", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_6", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_7", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_8", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_9", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_10", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_11", 31);






  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC", 12);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC", 12);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_0", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_1", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_2", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_3", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_4", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_5", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_6", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_7", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_8", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_9", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_10", 31);
  _histos.clone("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_11", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_0", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_1", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_2", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_3", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_4", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_5", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_6", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_7", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_8", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_9", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_10", 31);
  _histos.clone("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_11", 31);

  // for track match
  _histos.clone("EMEta_EM_Probe_Trk", 2);
  _histos.clone("EMPt_EM_Probe_Trk", 2);
  _histos.clone("EMEta_EM_Probe_Trk_Matched", 2);
  _histos.clone("EMPt_EM_Probe_Trk_Matched", 2);
  _histos.clone("EMEta_EM_Probe_Spatial_Trk_Matched", 2);
  _histos.clone("EMPt_EM_Probe_Spatial_Trk_Matched", 2);

  // for different primary vertex region
  // 5 vertex regions: <-40, between -40 and -10, between -10 and 10, between 10 and 40, >40
  _histos.clone("EMDetEta_EM_Probe_Trk_All_Vtx", 12);
  _histos.clone("EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx", 12);
  _histos.clone("EMEta_EM_Probe_Trk_All_Vtx", 12);
  _histos.clone("EMEta_EM_Probe_Spatial_Trk_Matched_Vtx", 12);
  _histos.clone("EMPt_EM_Probe_Trk_All_CC_Vtx", 12);
  _histos.clone("EMPt_EM_Probe_Spatial_Trk_Matched_CC_Vtx", 12);
  _histos.clone("EMPt_EM_Probe_Trk_All_EC_Vtx", 12);
  _histos.clone("EMPt_EM_Probe_Spatial_Trk_Matched_EC_Vtx", 12);

  // mass before and after track matching for different vertex and eta regions
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC", 14);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC", 14);
  
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC", 14);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC", 14);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC", 14);

  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_0", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_1", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_2", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_3", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_4", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_5", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_6", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_7", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_8", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_9", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_10", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_11", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_12", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_CC_13", 31);




  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_0", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_1", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_2", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_3", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_4", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_5", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_6", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_7", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_8", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_9", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_10", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_11", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_12", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_CC_13", 31);


  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_0", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_1", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_2", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_3", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_4", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_5", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_6", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_7", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_8", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_9", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_10", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_11", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_12", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_13", 31);


  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_0", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_1", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_2", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_3", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_4", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_5", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_6", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_7", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_8", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_9", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_10", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_11", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_12", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_13", 31);




   _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_0", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_1", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_2", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_3", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_4", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_5", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_6", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_7", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_8", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_9", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_10", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_11", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_12", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_13", 31);


  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC", 12);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC", 12);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_0", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_1", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_2", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_3", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_4", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_5", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_6", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_7", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_8", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_9", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_10", 31);
  _histos.clone("ZMass_vs_Eta_Before_Trk_Vtx_EC_11", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_0", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_1", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_2", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_3", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_4", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_5", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_6", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_7", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_8", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_9", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_10", 31);
  _histos.clone("ZMass_vs_Eta_After_Trk_Vtx_EC_11", 31);

  //for Efficiency Study
  _histos.clone("EMDetEta_ZMass_EM_Probe_Trk_All", 6);
  _histos.clone("EMDetEta_ZMass_EM_Probe_Trk_Matched", 6);
  _histos.clone("EMDetEta_Bkgd", 6);
  _histos.clone("EMEta_ZMass_EM_Probe_Trk_All", 6);
  _histos.clone("EMEta_ZMass_EM_Probe_Trk_Matched", 6);
  _histos.clone("EMEta_Bkgd", 6);

  _histos.clone("ZMass_vs_Pt_Before_HMx_CC_Etabin", 15);
  _histos.clone("ZMass_vs_Pt_After_HMx_CC_Etabin", 15);

  _histos.clone("ZMass_V_Pt_EM_Probe_Trk_All_Etabin", 15);
  _histos.clone("ZMass_V_Pt_EM_Probe_Trk_Matched_Etabin", 15);
  _histos.clone("ZMass_V_Pt_Bkgd_Etabin", 15);
  _histos.clone("ZMass_V_Pt_EM_Probe_Trk_All_SETbin", 5);
  _histos.clone("ZMass_V_Pt_EM_Probe_Trk_Matched_SETbin", 5);
  _histos.clone("ZMass_V_Pt_EM_Probe_HMx_All_SETbin", 5);
  _histos.clone("ZMass_V_Pt_EM_Probe_HMx_Matched_SETbin", 5);
  _histos.clone("ZMass_V_Pt_Bkgd_SETbin", 5);
  _histos.clone("ZMass_V_Vtx_Bkgd_Etabin", 15);

  //for pT efficiency in different Eta bins
  _histos.clone("EMPt_inEtaBin_RecoEff_CC", 15);
  _histos.clone("EMPt_emfrac_iso_inEtaBin_RecoEff_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_inEtaBin_RecoEff_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_spatial_inEtaBin_RecoEff_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_spatial_smt_inEtaBin_RecoEff_CC", 15);
  _histos.clone("ZMass_inEtaBin_RecoEff_CC", 15);
  _histos.clone("ZMass_emfrac_iso_inEtaBin_RecoEff_CC", 15);
  _histos.clone("ZMass_emfrac_iso_HMx7_inEtaBin_RecoEff_CC", 15);
  _histos.clone("ZMass_emfrac_iso_HMx7_spatial_inEtaBin_RecoEff_CC", 15);
  _histos.clone("ZMass_emfrac_iso_HMx7_spatial_smt_inEtaBin_RecoEff_CC", 15);

  //Jun: tag-probe for CC
  _histos.clone("EMPt_CC", 15);
  _histos.clone("EMPt_emfrac_iso_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_spatial_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_spatial_smt_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 15);

  _histos.clone("EMPt_first_CC", 15);
  _histos.clone("EMPt_first_emfrac_iso_CC", 15);
  _histos.clone("EMPt_first_emfrac_iso_HMx7_CC", 15);
  _histos.clone("EMPt_first_emfrac_iso_HMx7_spatial_CC", 15);
  _histos.clone("EMPt_first_emfrac_iso_HMx7_spatial_smt_CC", 15);
  _histos.clone("EMPt_first_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 15);

  _histos.clone("EMPt_second_CC", 15);
  _histos.clone("EMPt_second_emfrac_iso_CC", 15);
  _histos.clone("EMPt_second_emfrac_iso_HMx7_CC", 15);
  _histos.clone("EMPt_second_emfrac_iso_HMx7_spatial_CC", 15);
  _histos.clone("EMPt_second_emfrac_iso_HMx7_spatial_smt_CC", 15);
  _histos.clone("EMPt_second_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 15);

  _histos.clone("EMPt_MC_CC", 15);
  _histos.clone("EMPt_MC_emfrac_iso_CC", 15);
  _histos.clone("EMPt_MC_emfrac_iso_HMx7_CC", 15);
  _histos.clone("EMPt_MC_emfrac_iso_HMx7_spatial_CC", 15);
  _histos.clone("EMPt_MC_emfrac_iso_HMx7_spatial_smt_CC", 15);
  _histos.clone("EMPt_MC_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 15);

  _histos.clone("EMVtx_CC", 15);
  _histos.clone("EMVtx_emfrac_iso_CC", 15);
  _histos.clone("EMVtx_emfrac_iso_HMx7_CC", 15);
  _histos.clone("EMVtx_emfrac_iso_HMx7_spatial_CC", 15);
  _histos.clone("EMVtx_emfrac_iso_HMx7_spatial_smt_CC", 15);
  _histos.clone("EMVtx_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 15);

  _histos.clone("EMEta_CC", 15);
  _histos.clone("EMEta_emfrac_iso_CC", 15);
  _histos.clone("EMEta_emfrac_iso_HMx7_CC", 15);
  _histos.clone("EMEta_emfrac_iso_HMx7_spatial_CC", 15);
  _histos.clone("EMEta_emfrac_iso_HMx7_spatial_smt_CC", 15);
  _histos.clone("EMEta_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 15);

  _histos.clone("EMDetEta_CC", 15);
  _histos.clone("EMDetEta_emfrac_iso_CC", 15);
  _histos.clone("EMDetEta_emfrac_iso_HMx7_CC", 15);
  _histos.clone("EMDetEta_emfrac_iso_HMx7_spatial_CC", 15);
  _histos.clone("EMDetEta_emfrac_iso_HMx7_spatial_smt_CC", 15);
  _histos.clone("EMDetEta_emfrac_iso_HMx7_spatial_smt_trkpT_CC", 15);

  _histos.clone("EMPt_vs_DetEta_tagprobe", 15);
  _histos.clone("EMPt_vs_DetEta_emfrac_iso_tagprobe", 15);
  _histos.clone("EMPt_vs_DetEta_emfrac_iso_Hmx7_tagprobe", 15);
  _histos.clone("EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_tagprobe", 15);
  _histos.clone("EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_smt_tagprobe", 15);
  _histos.clone("EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_smt_trkpT_tagprobe", 15);

  ////by Jun: truth method
  _histos.clone("EMPt_truth_CC", 15);
  _histos.clone("EMPt_emfrac_iso_truth_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_truth_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_spatial_truth_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_spatial_smt_truth_CC", 15);
  _histos.clone("EMPt_emfrac_iso_HMx7_spatial_smt_trkpT_truth_CC", 15);

  _histos.clone("EMVtx_truth_CC", 15);
  _histos.clone("EMVtx_emfrac_iso_truth_CC", 15);
  _histos.clone("EMVtx_emfrac_iso_HMx7_truth_CC", 15);
  _histos.clone("EMVtx_emfrac_iso_HMx7_spatial_truth_CC", 15);
  _histos.clone("EMVtx_emfrac_iso_HMx7_spatial_smt_truth_CC", 15);
  _histos.clone("EMVtx_emfrac_iso_HMx7_spatial_smt_trkpT_truth_CC", 15);

  _tree3 = new TTree("ztrigeff", "");
  _tree3->Branch("run", &tree3_run, "run/I");
  _tree3->Branch("evt",  &tree3_evt,   "evt/I");
  _tree3->Branch("triglist", &tree3_triglist, "triglist/I");
  _tree3->Branch("lumi", &tree3_lumi, "lumi/F");
  _tree3->Branch("mee", &tree3_mee, "mee/F");
  _tree3->Branch("probe_pt", &tree3_probe_pt, "probe_pt/F");
  _tree3->Branch("probe_chg", &tree3_probe_chg, "probe_chg/I");
  _tree3->Branch("probe_eta", &tree3_probe_eta, "probe_eta/F");
  _tree3->Branch("probe_trackmatch25", &tree3_probe_trackmatch25, "probe_trackmatch25/I");
  _tree3->Branch("probe_trackmatch27", &tree3_probe_trackmatch27, "probe_trackmatch27/I");
  _tree3->Branch("tag_pt", &tree3_tag_pt, "tag_pt/F");
  _tree3->Branch("tag_chg", &tree3_tag_chg, "tag_chg/I");
  _tree3->Branch("tag_eta", &tree3_tag_eta, "tag_eta/F");
  _tree3->Branch("tag_trackmatch25", &tree3_tag_trackmatch25, "tag_trackmatch25/I");
  _tree3->Branch("tag_trackmatch27", &tree3_tag_trackmatch27, "tag_trackmatch27/I");
  _tree3->Branch("pass_25", &tree3_pass_25, "pass_25/I");
  _tree3->Branch("pass_27", &tree3_pass_27, "pass_27/I");
  
  tree3_run=tree3_evt=tree3_triglist=tree3_pass_27=tree3_pass_25=tree3_probe_chg= -555;
  tree3_lumi=tree3_mee=tree3_probe_pt=tree3_probe_eta= -555.;
  tree3_probe_trackmatch25=tree3_probe_trackmatch27=tree3_tag_trackmatch25=tree3_tag_trackmatch27= tree3_tag_chg= -555;
  tree3_tag_pt=tree3_tag_eta= -555.;
}

// process 
bool EffAnalysis::processEvent(cafe::Event& event) {

  // only study trigger efficiency for data
  if(!_MCStudy) TriggerEff(event);
  if(_MCStudy) MCEff(event);
  pTDependenceEff(event);
  PreSelectionEff(event);
  HMxEff(event);
  LooseTrackMatchEff(event);
  TrackMatchEff(event);
  LumiEff(event);
  return true;   
}

//
// study efficiencies using generator level information
//
void EffAnalysis::MCEff(cafe::Event& event) {
  
  //get em objects from the event
  cafe::Collection<TMBEMCluster> em = event.getEMscone();
  
  // Primary Vertex
  Collection<TMBPrimaryVertex> vertices = event.getPrimaryVertices();
  
  double zvtx = 0.;  
  if(vertices.size()>0) zvtx = vertices[0].vz();
  else zvtx = 0.;
  
  std::vector<TMBMCpart *> mc_emobjs; 
  if(event.get("em mc objects", mc_emobjs)) {
    for(int imc=0; imc<mc_emobjs.size(); imc++) {
      if(mc_emobjs[imc]->Pt()>10.) {
	
	// extrapolate to calorimeter region
	double phi = mc_emobjs.at(imc)->Phi();
	double eta = mc_emobjs[imc]->Eta();
	double theta = 2.0 * TMath::ATan(TMath::Exp(-eta));
	double ztmp = zvtx + 91.9/TMath::Tan(theta);
	
	// extrapolated position in central calorimeter
	if(fabs(ztmp)<110.) {
	  double phimod = fmod(phi+0.1,(TMath::Pi()/16.));
	  if((phimod<0.1-0.02) || (phimod>0.1+0.02) ) {
	    
	    // loop over reconstructed EM clusters
	    for (Collection<TMBEMCluster>::iterator it = em.begin(); it!= em.end(); ++it) {	      
	      // found EM clusters in CC fiducial region with pT>20 GeV
	      	CAFEMObj  emobj = CAFEMObj(&(*it));
	      if (( abs((*it).id())==10 || abs((*it).id())==11) && ((*it).Pt()>20.) && 
		  emobj.IsCCECFid(_DetEtaCC,_DetEtaEC1,_DetEtaEC2,_useTrackFiducial) && fabs((*it).CalDetectorEta())<1.1) {
		

		int solpol = -999;  
		event.get("solenoid polarity", solpol);
		int polarity = 2*solpol - 1;

        // 042310 Alex changed this line	
		// double phi_em =emobj.TrkPhiEM3();
        // to
        double phi_em=emobj.Phi();
        // to conform to latest strategy
        // of not doing propagation to EM3 outside EMSelector
        // (now phi of track at dca will be used instead in the code below)

		double eta_em = (*it).Eta();
		
		// calculate eta,phi difference
		double delta_phi = fabs(phi-phi_em);
		if(delta_phi>TMath::Pi()) delta_phi = 2*TMath::Pi() - delta_phi;
		double delta_eta = eta - eta_em;
		double delta_R = sqrt(delta_phi * delta_phi + delta_eta * delta_eta);
		
		// require the extroplated MC particle position and the reconstructed EM cluster close to each other
		if(delta_R < 0.2) {
		  _histos.Fill1D("EMPt_Reco_After_EMID_Match", (*it).Pt());
		  
		  if((*it).emfrac()>0.9 && (*it).iso()<0.15) {
		    _histos.Fill1D("EMPt_Reco_After_EMID_EMFrac_Iso_Match", (*it).Pt());

		    if((*it).HMx7()<12.) {
		      _histos.Fill1D("EMPt_Reco_After_EMID_EMFrac_Iso_HMx_Match", (*it).Pt());

		      if((*it).has_spatial_track_match() && emobj.IsCCFid(_DetEtaCC,_useTrackFiducial)) {
			const TMBTrack *tmp_track = (*it).getPtrChpSpatial();
                        if(tmp_track!=NULL) {
			  _histos.Fill1D("EMPt_Reco_After_EMID_EMFrac_Iso_HMx_SpatialTrack_Match", (*it).Pt());
			  
			  if(tmp_track->Pt()>10.) 
			    _histos.Fill1D("EMPt_Reco_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_Match", (*it).Pt());
			  if(tmp_track->nsmt()>0)
			    _histos.Fill1D("EMPt_Reco_After_EMID_EMFrac_Iso_HMx_SpatialTrack_SMTHit_Match", (*it).Pt());
			  if(tmp_track->Pt()>10. && tmp_track->nsmt()>0)
			    _histos.Fill1D("EMPt_Reco_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_SMTHit_Match", (*it).Pt());
                        } // not null pointer
		      } // spatial track
		    } // hmx
		  } // emfrac, iso

		  // check track matching efficiency
		  if((*it).emfrac()>0.9 && (*it).iso()<0.15 && (*it).Pt()>25. && (*it).HMx7()<12.   &&  (*it).has_spatial_track_match(-0.5)  ) {
		    // fill histogram
		    _histos.Fill2D("EMEta_Vtx_TrkEff_After_EMID_EMFrac_Iso_HMx", zvtx, (*it).Eta());
		    _histos.Fill2D("EMVtx_Eta_TrkEff_After_EMID_EMFrac_Iso_HMx", (*it).Eta(), zvtx);
		    _histos.Fill1D("EMVtx_TrkEff_After_EMID_EMFrac_Iso_HMx", zvtx);
		    _histos.Fill1D("EMEta_TrkEff_After_EMID_EMFrac_Iso_HMx", (*it).Eta());
		    
		    if((*it).has_spatial_track_match() && emobj.IsCCFid(_DetEtaCC,_useTrackFiducial) ) {
		      const TMBTrack *tmp_track = (*it).getPtrChpSpatial();
		      if(tmp_track!=NULL) {			
			_histos.Fill2D("EMEta_Vtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_Match", zvtx, (*it).Eta()); 	
			_histos.Fill2D("EMVtx_Eta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_Match", (*it).Eta(), zvtx); 	
			_histos.Fill1D("EMEta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_Match", zvtx);   	
			_histos.Fill1D("EMVtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_Match", (*it).Eta());	
			
			if(tmp_track->Pt()>10.) {
			  _histos.Fill2D("EMEta_Vtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_Match", zvtx, (*it).Eta());
			  _histos.Fill2D("EMVtx_Eta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_Match", (*it).Eta(), zvtx);
			  _histos.Fill1D("EMVtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_Match", zvtx);
			  _histos.Fill1D("EMEta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_Match", (*it).Eta());
			}
			
			if(tmp_track->nsmt()>0) {
			  _histos.Fill2D("EMEta_Vtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_SMTHit_Match", zvtx, (*it).Eta());
			  _histos.Fill2D("EMVtx_Eta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_SMTHit_Match", (*it).Eta(), zvtx);
			  _histos.Fill1D("EMVtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_SMTHit_Match", zvtx);
			  _histos.Fill1D("EMEta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_SMTHit_Match", (*it).Eta());
			}

			if(tmp_track->Pt()>10. && tmp_track->nsmt()>0)
			  _histos.Fill2D("EMEta_Vtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_SMTHit_Match", zvtx, (*it).Eta());
			  _histos.Fill2D("EMVtx_Eta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_SMTHit_Match", (*it).Eta(), zvtx);
			  _histos.Fill1D("EMVtx_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_SMTHit_Match", zvtx);
			  _histos.Fill1D("EMEta_TrkEff_After_EMID_EMFrac_Iso_HMx_SpatialTrack_TrkPt_SMTHit_Match", (*it).Eta());
		      }		      
		    }
		  } // check track matching efficiency		    
		  
		} // MC and reco EM match with each other
		
	      } // pass EMID cut
	    } // loop over all reconstructed EM clusters
	    
	  } // in phi fiducial region
	} // in CC fiducial region
      } // pT>10 GeV
    } // loop over all MC em objects
  }
}

//
// study overall pT dependence using tag-probe method
// no trigger efficiency involved
//
void EffAnalysis::pTDependenceEff(cafe::Event& event) {

  vector<CAFEMObj*> emobjs;
  if(event.get("Probe EMObjs", emobjs)) { // only id=10,11 and pT>15 GeV cut applied for probe electrons

    if(emobjs.size()>=2) {
      double Z_Px = emobjs[0]->Px() + emobjs[1]->Px();
      double Z_Py = emobjs[0]->Py() + emobjs[1]->Py();
      double Z_Pz = emobjs[0]->Pz() + emobjs[1]->Pz();
      double Z_E = emobjs[0]->E() + emobjs[1]->E();
      double mass = Z_E*Z_E - Z_Px*Z_Px - Z_Py*Z_Py - Z_Pz*Z_Pz;
      if(mass<0.) mass = 0.; 
      else mass = sqrt(mass);

      // mass requirement
      if(mass > 70. && mass < 110.) {
	// use the highest pT electron as the tag electron
	if(emobjs[0]->Pt()>25. && emobjs[0]->IsCCECFid(_DetEtaCC,_DetEtaEC1,_DetEtaEC2,_useTrackFiducial) && emobjs[0]->has_good_spatial_track_match() && 
	   emobjs[0]->emfrac()>0.9 && emobjs[0]->iso()<0.15 && 
	   ((fabs(emobjs[0]->CalDetectorEta())<1.1 && emobjs[0]->HMx7()<12.) || 
	    ((fabs(emobjs[0]->CalDetectorEta())<2.3 && fabs(emobjs[0]->CalDetectorEta())>1.5 && emobjs[0]->HMx8()<20.)))) {
	  
	  if(emobjs[1]->Pt()>20. && emobjs[1]->IsCCECFid(_DetEtaCC,_DetEtaEC1,_DetEtaEC2,_useTrackFiducial) && fabs(emobjs[1]->CalDetectorEta())<1.1) {
	    // fill probe electron pT here
	    _histos.Fill1D("EMPt_pTDependence_before", emobjs[1]->Pt());
	    _histos.Fill1D("EMPt1_pTDependence_before", emobjs[1]->Pt());
	    
	    if(emobjs[1]->emfrac()>0.9 && emobjs[1]->iso()<0.15) {
	      // fill histogram
	      _histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso", emobjs[1]->Pt());
	      _histos.Fill1D("EMPt1_pTDependence_after_EMFrac_Iso", emobjs[1]->Pt());
	      
	      if(emobjs[1]->HMx7()<12.) {
		// fill histogram
		_histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso_HMx", emobjs[1]->Pt());
		_histos.Fill1D("EMPt1_pTDependence_after_EMFrac_Iso_HMx", emobjs[1]->Pt());
		
		if(_debugLevel>=30) cout<<"right before spatial track match"<<endl; 
		if(emobjs[1]->has_spatial_track_match()) {
		  const TMBTrack* track_spatial = emobjs[1]->getPtrSpatialChp();
		  if (track_spatial!=NULL){
		    // fill histogram
		    _histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch", emobjs[1]->Pt());
		    _histos.Fill1D("EMPt1_pTDependence_after_EMFrac_Iso_HMx_TrackMatch", emobjs[1]->Pt());
		    if(_debugLevel>=30) cout<<"right before spatial track match getting nsmt"<<endl; 
		    if(track_spatial->nsmt()>0) {
		      _histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_SMTHit", emobjs[1]->Pt());
		      _histos.Fill1D("EMPt1_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_SMTHit", emobjs[1]->Pt());
		    }
		    if(_debugLevel>=30) cout<<"right before spatial track match getting pt"<<endl; 
		    if(track_spatial->Pt()>10.) {
		      _histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt", emobjs[1]->Pt());
		      _histos.Fill1D("EMPt1_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt", emobjs[1]->Pt());
		    }
		    if(_debugLevel>=30) cout<<"right after both"<<endl; 
		    if(track_spatial->Pt()>10. && track_spatial->nsmt()>0) {
		      _histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt_SMTHit", emobjs[1]->Pt());
		      _histos.Fill1D("EMPt1_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt_SMTHit", emobjs[1]->Pt());
		    }
		  }
		}
	      }
	    }
	  } // probe electron
	} // highest pT electron as the tag
	
	// use the second highest pT electron as the tag electron
	if(emobjs[1]->Pt()>20. && emobjs[1]->IsCCECFid(_DetEtaCC,_DetEtaEC1,_DetEtaEC2,_useTrackFiducial) && emobjs[1]->has_good_spatial_track_match() && 
	   emobjs[1]->emfrac()>0.9 && emobjs[1]->iso()<0.15 && 
	   ((fabs(emobjs[1]->CalDetectorEta())<1.1 && emobjs[1]->HMx7()<12.) || 
	    ((fabs(emobjs[1]->CalDetectorEta())<2.3 && fabs(emobjs[1]->CalDetectorEta())>1.5 && emobjs[1]->HMx8()<20.)))) {
	  
	  if(emobjs[0]->Pt()>20. && emobjs[0]->IsCCECFid(_DetEtaCC,_DetEtaEC1,_DetEtaEC2,_useTrackFiducial) && fabs(emobjs[0]->CalDetectorEta())<1.1) {
	    // fill probe electron pT here
	    _histos.Fill1D("EMPt_pTDependence_before", emobjs[0]->Pt());
	    _histos.Fill1D("EMPt2_pTDependence_before", emobjs[0]->Pt());
	    
	    if(emobjs[0]->emfrac()>0.9 && emobjs[0]->iso()<0.15) {
	      // fill histogram
	      _histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso", emobjs[0]->Pt());
	      _histos.Fill1D("EMPt2_pTDependence_after_EMFrac_Iso", emobjs[0]->Pt());
	      
	      if(emobjs[0]->HMx7()<12.) {
		// fill histogram
		_histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso_HMx", emobjs[0]->Pt());
		_histos.Fill1D("EMPt2_pTDependence_after_EMFrac_Iso_HMx", emobjs[0]->Pt());
		if(_debugLevel>=30) cout<<"right before spatial track match 2"<<endl; 
		if(emobjs[0]->has_spatial_track_match()  && emobjs[0]->IsCCECFid(_DetEtaCC,_DetEtaEC1,_DetEtaEC2,_useTrackFiducial)) {
		  const TMBTrack* track_spatial = emobjs[0]->getPtrSpatialChp();
		  if (track_spatial!=NULL) {
		    // fill histogram
		    _histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch", emobjs[0]->Pt());
		    _histos.Fill1D("EMPt2_pTDependence_after_EMFrac_Iso_HMx_TrackMatch", emobjs[0]->Pt());
		    if(_debugLevel>=30) cout<<"right before spatial track match getting nsmt 2"<<endl; 
		    if(track_spatial->nsmt()>0) {
		      _histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_SMTHit", emobjs[0]->Pt());
		      _histos.Fill1D("EMPt2_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_SMTHit", emobjs[0]->Pt());
		    }
		    if(_debugLevel>=30) cout<<"right before spatial track match getting pt 2"<<endl; 
		    if(track_spatial->Pt()>10.) {
		      _histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt", emobjs[0]->Pt());
		      _histos.Fill1D("EMPt2_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt", emobjs[0]->Pt());
		    }
		    if(_debugLevel>=30) cout<<"right after both 2"<<endl; 
		    if(track_spatial->Pt()>10. && track_spatial->nsmt()>0) {
		      _histos.Fill1D("EMPt_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt_SMTHit", emobjs[0]->Pt());
		      _histos.Fill1D("EMPt2_pTDependence_after_EMFrac_Iso_HMx_TrackMatch_TrkPt_SMTHit", emobjs[0]->Pt());
		    }
		  }
		}
	      }
	    }
	  } // probe electron
	} // second highest pT electron as the tag
	
      } // at least two EM objects
    } // mass
  } // get probe EM objects
 
  /////////////////////////////
  ///study efficiency for data
  /////////////////////////////
  vector<CAFEMObj*> emobjs_good;
  vector<CAFEMObj*> probeEMs;
  const CAFEMObj *emobj;
  const CAFEMObj *emobj_probe;

  int triglist_flag = -1;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;

  // get primary vertex
  float v_z;
  bool getPrimaryVertex = event.get("Primary vertexZ", v_z);
  char bins_Vtx[10];
  int bin_Vtx_number;
  bin_Vtx_number=int((v_z+60.)/20.);
  sprintf(bins_Vtx, "%d", bin_Vtx_number);

  // get probe electrons
  bool getProbeElectrons = event.get("Probe EMObjs", probeEMs);

  if(event.get("Good EMObjs", emobjs_good) && 
     (_MCStudy || (event.get("L1CalTowers", l1cal_vec) &&  event.get("L1Cal2bTowers", l1cal2b_vec) && 
     event.get("L2GblEMs", l2cal_vec) && event.get("L3Eles", l3cal_vec) &&
		   event.get("triglist flag", triglist_flag)))) {

    for(int iem=0; iem<emobjs_good.size(); ++iem){
      emobj = emobjs_good[iem];

      // the tag electron must pass trigger requirements
      // for GEANT MC, we do not need to check trigger efficiency
      bool pass_trigger = false;
      if(_MCStudy || _DropTriggerObjectMatchRequirement) pass_trigger = true;
      else pass_trigger = emobj->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec,  l2cal_vec, l3cal_vec);
      if(!pass_trigger) continue;
 
      // if tag electron and probe electron are the same, zcand mass will be very small
      // and will be removed by z mass window requirment
      for(int iprobe=0; iprobe<probeEMs.size(); ++iprobe){
        emobj_probe = probeEMs[iprobe];
	
	const TMBTrack *tmp_track = emobj->getPtrSpatialChp();

		// require tag electron in CC region
	// need to make sure that the probe em object already
	// passes id, emfrac, isolation and hmx cuts
	

	if(emobj->IsCCFid(_DetEtaCC,_useTrackFiducial) && emobj->has_spatial_track_match() && tmp_track!=NULL && tmp_track->nsmt()>0) {

	  //////To study the Reco selection efficiency
	  if(emobj_probe->IsEM() && emobj_probe->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial) && 
	     emobj_probe->Pt()>25.) {
	    
	    ////for different electron eta bins
	    char bins_Eta[10];
	    int bin_Eta_number;
	    double eta_probe=emobj_probe->Eta();
	    if(eta_probe<-1.3)
	      bin_Eta_number=0;
	    else if(eta_probe>1.3)
	      bin_Eta_number=14;
	    else
	      bin_Eta_number=int((eta_probe+1.3)/0.2)+1;
	    sprintf(bins_Eta, "%d", bin_Eta_number);
	    
	    double pT_e = emobj_probe->Pt();

	    CAFZCand zcand_0(emobj, emobj_probe); 
	    
	    //only study CC electrons
	    if(emobj_probe->IsCCFid(_DetEtaCC,_useTrackFiducial) && zcand_0.In_ZPeak(70., 110.)){
	      _histos.Fill1D("EMPt_inEtaBin_RecoEff_CC", pT_e);
	      _histos.Fill1D("ZMass_inEtaBin_RecoEff_CC", zcand_0.Mass());
	      _histos.Fill1D(string("EMPt_inEtaBin_RecoEff_CC_")+bins_Eta, pT_e);
	      _histos.Fill1D(string("ZMass_inEtaBin_RecoEff_CC_")+bins_Eta, zcand_0.Mass());
	      if(emobj_probe->PassEMFracIso(_EMFracCut, _IsoCut)){
		_histos.Fill1D("EMPt_emfrac_iso_inEtaBin_RecoEff_CC", pT_e);
		_histos.Fill1D("ZMass_emfrac_iso_inEtaBin_RecoEff_CC", zcand_0.Mass());
		_histos.Fill1D(string("EMPt_emfrac_iso_inEtaBin_RecoEff_CC_")+bins_Eta, pT_e);
		_histos.Fill1D(string("ZMass_emfrac_iso_inEtaBin_RecoEff_CC_")+bins_Eta, zcand_0.Mass());
		if(emobj_probe->PassHMx(_HM7Cut, _HM8Cut)){
		  _histos.Fill1D("EMPt_emfrac_iso_HMx7_inEtaBin_RecoEff_CC", pT_e);
		  _histos.Fill1D("ZMass_emfrac_iso_HMx7_inEtaBin_RecoEff_CC", zcand_0.Mass());
		  _histos.Fill1D(string("EMPt_emfrac_iso_HMx7_inEtaBin_RecoEff_CC_")+bins_Eta, pT_e);
		  _histos.Fill1D(string("ZMass_emfrac_iso_HMx7_inEtaBin_RecoEff_CC_")+bins_Eta, zcand_0.Mass()); 
		  if(emobj_probe->has_spatial_track_match() && emobj_probe->IsCCFid(_DetEtaCC,_useTrackFiducial)){
		    _histos.Fill1D("EMPt_emfrac_iso_HMx7_spatial_inEtaBin_RecoEff_CC", pT_e);
		    _histos.Fill1D("ZMass_emfrac_iso_HMx7_spatial_inEtaBin_RecoEff_CC", zcand_0.Mass());
		    _histos.Fill1D(string("EMPt_emfrac_iso_HMx7_spatial_inEtaBin_RecoEff_CC_")+bins_Eta, pT_e);
		    _histos.Fill1D(string("ZMass_emfrac_iso_HMx7_spatial_inEtaBin_RecoEff_CC_")+bins_Eta, zcand_0.Mass());
		    if(tmp_track!=NULL && tmp_track->nsmt()>0){
		      _histos.Fill1D("EMPt_emfrac_iso_HMx7_spatial_smt_inEtaBin_RecoEff_CC", pT_e);
		      _histos.Fill1D("ZMass_emfrac_iso_HMx7_spatial_smt_inEtaBin_RecoEff_CC", zcand_0.Mass());
		      _histos.Fill1D(string("EMPt_emfrac_iso_HMx7_spatial_smt_inEtaBin_RecoEff_CC_")+bins_Eta, pT_e);
		      _histos.Fill1D(string("ZMass_emfrac_iso_HMx7_spatial_smt_inEtaBin_RecoEff_CC_")+bins_Eta, zcand_0.Mass());
		    }
		  }
		}
	      }
	    }	    
	  }
	  //////End of the Reco selection efficiency
	}
      }
    }
  }
}

// 
// Trigger efficiency
//
void EffAnalysis::TriggerEff(cafe::Event& event) {

  if(_debugLevel>=30) cout<<"Trigger Efficiency Study"<<endl; 
  
  int triglist_flag = -1;
  double instlumi=0;
  int runNo, evtNo;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;

  vector<CAFEMObj*> emobjs;
  const CAFEMObj *emobj;
  const CAFEMObj *emobj_probe;
  TriggerManager *trigmanager = TriggerManager::get_instance();
  trigmanager->SetTrigs(event);

  //
  // event has to pass at least one trigger
  //
  //  if(trigmanager->Passes_Trig_CMB()) {    
  if(event.get("Probe EMObjs", emobjs) && event.get("L1CalTowers", l1cal_vec) && event.get("L1Cal2bTowers", l1cal2b_vec) && 
     event.get("L2GblEMs", l2cal_vec) && event.get("L3Eles", l3cal_vec) &&
     event.get("triglist flag", triglist_flag) && event.get("InstLumi", instlumi) && 
     event.get("run number", runNo) && event.get("event number", evtNo) ) {
      for(int iem=0; iem<emobjs.size(); ++iem){
	emobj = emobjs[iem];	

	// tag electron has a good spatial track match
	if(emobj->has_good_spatial_track_match() && emobj->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial) && 
	   emobj->PassHMx(_HM7Cut, _HM8Cut) && emobj->Pt()>_ElecPtCut && emobj->PassEMFracIso(_EMFracCut, _IsoCut)) {
	  
	  // loop over probe electron
	  for(int iem_probe=0; iem_probe<emobjs.size(); ++iem_probe){
	    if (iem_probe==iem) continue;
	    emobj_probe = emobjs[iem_probe];
	    
	    // construct Z candidate
	    //4/23/12 jenny removed Z candidate selection- want CC-EC option and also not listed in paper
	    CAFZCand zcand(emobj, emobj_probe);
	    float mass = zcand.Mass();
	    if( (mass<_ZMassCut1) || (mass>_ZMassCut2) ) continue;              // not inside Z mass region
	    //  if( zcand.Type(_DetEtaCC, _DetEtaEC1, _DetEtaEC2)!=0 ) continue;    // only use CC-CC events

	    // probe electron also needs to pass fiducial, HMx, EMFraction and isolation requirements
	    //4/23/12 jenny changed CCECFid to CCFid so probe is CC only
	    if( !(emobj_probe->IsCCFid(_DetEtaCC,_useTrackFiducial) && 
		  emobj_probe->PassHMx(_HM7Cut, _HM8Cut) && emobj_probe->PassEMFracIso(_EMFracCut, _IsoCut) &&  emobj_probe->has_good_spatial_track_match())) continue;

	    // triglist flag
	    char sn1[10]; sprintf(sn1,"%d", triglist_flag);
	    TString SN_Triglist=TString("_")+sn1;
	    
	    bool _uses25=false;
	    bool _uses27=false;
	    for(int itrig=0; itrig<_trignames[triglist_flag].size(); itrig++) {
	      // get each trigger name		  
	      string trigname =_trignames[triglist_flag][itrig];
	      if (!(trigmanager->Uses_Trig(trigname.substr(0,8).c_str()))) continue;
	      if (strncmp(trigname.c_str(),string("E1_SHT25").c_str(),8)==0){
		_uses25 = true;
	      }
	      if (strncmp(trigname.c_str(),string("E1_SHT27").c_str(),8)==0){
		_uses27 = true;
	      }	
	    }
            bool pass_trigger=false;
	    pass_trigger = (emobj->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec));
        if(_DropTriggerObjectMatchRequirement) pass_trigger=true;	   
        // tag electron passes trigger requirements (for all possible triggers in one specific trigger list)
	    if(pass_trigger  && (_uses25 ||  (emobj->PassL1L2L3Trig("E1_SHT27", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec) && _uses27) ))     {
	      if (_uses27 && _uses25 && triglist_flag==6){
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_All_Both"), emobj_probe->Pt());	 
	      }

	       tree3_run= runNo;  				
	       tree3_evt= evtNo;  				
	       tree3_triglist= triglist_flag;
	       tree3_lumi= instlumi;			 
	       tree3_mee= mass;			  
	       tree3_probe_pt= emobj_probe->Pt() ;  			  
	       tree3_probe_chg= (int) emobj_probe->charge();  			  
	       tree3_probe_eta= emobj_probe->Eta();  
	
	       if(emobj_probe->PassL1L2L3Trig("E1_SHT25", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)) tree3_probe_trackmatch25 = 1;
	       else tree3_probe_trackmatch25 = 0;
	       
	       if(emobj_probe->PassL1L2L3Trig("E1_SHT27", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)) tree3_probe_trackmatch27 = 1;
	       else tree3_probe_trackmatch27 = 0;

	       tree3_tag_pt= emobj->Pt();  			  
	       tree3_tag_chg= (int) emobj->charge();  			  
	       tree3_tag_eta= emobj->Eta();  

	       if(emobj->PassL1L2L3Trig("E1_SHT25", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)) tree3_tag_trackmatch25 = 1;
	       else tree3_tag_trackmatch25 = 0;
	       
	       if(emobj->PassL1L2L3Trig("E1_SHT27", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)) tree3_tag_trackmatch27 = 1;
	       else tree3_tag_trackmatch27 = 0;

	       if(_uses25) tree3_pass_25= 1;
	       else tree3_pass_25= 0;

	       if(_uses27) tree3_pass_27= 1;
	       else tree3_pass_27= 0;     

	      _tree3->Fill();

	      //Jenny added six histos below 4/16/2012
	      //contains all events with a passing tag by trigger
	      // probe_pass_trigger = (emobj_probe->PassL1L2L3Trig(trigname.c_str(), 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec));
	      if (_uses27 && triglist_flag==7 && emobj->PassL1L2L3Trig("E1_SHT27", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)){
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_v16_27_7"), emobj_probe->Pt());
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_v16_27_7_lumi"), instlumi);
	      }
	      if (_uses25 && triglist_flag==6 && emobj->PassL1L2L3Trig("E1_SHT25", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)){
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_v16_25"), emobj_probe->Pt());
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_v16_25_lumi"), instlumi);
	      }
	      if (_uses27 && triglist_flag==6 && emobj->PassL1L2L3Trig("E1_SHT27", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)){
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_v16_27"), emobj_probe->Pt());
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_v16_27_lumi"), instlumi);
	      }
	      
	      if (_uses27 && triglist_flag==7 && emobj_probe->PassL1L2L3Trig("E1_SHT27", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec) && emobj->PassL1L2L3Trig("E1_SHT27", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)){
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_TT_v16_27_7"), emobj_probe->Pt());
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_TT_v16_27_7_lumi"), instlumi);
	      }
	      if (_uses25 && triglist_flag==6 && emobj_probe->PassL1L2L3Trig("E1_SHT25", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec) && emobj->PassL1L2L3Trig("E1_SHT25", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)){
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_TT_v16_25"), emobj_probe->Pt());
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_TT_v16_25_lumi"), instlumi);
	      }
	      if (_uses27 && triglist_flag==6 && emobj_probe->PassL1L2L3Trig("E1_SHT27", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec) && emobj->PassL1L2L3Trig("E1_SHT27", 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec)){
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_TT_v16_27"), emobj_probe->Pt());
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_TT_v16_27_lumi"), instlumi);
	      }
	      

	      // for all triggers in one specific trigger list
	      _histos.Fill1D(TString("InvMass_EM_Probe_Trig_All_Triglist")+SN_Triglist, mass);	      
	      _histos.Fill1D(TString("DetEta_EM_Probe_Trig_All_Triglist")+SN_Triglist, emobj_probe->CalDetectorEta());	  
	      _histos.Fill1D(TString("PhysEta_EM_Probe_Trig_All_Triglist")+SN_Triglist, emobj_probe->Eta());	  
	      _histos.Fill1D(TString("DetPhi_EM_Probe_Trig_All_Triglist")+SN_Triglist, emobj_probe->CalDetectorPhi());
	      _histos.Fill1D(TString("TrkPhiEM3_EM_Probe_Trig_All_Triglist")+SN_Triglist, emobj_probe->TrkPhiEM3());
	      _histos.Fill1D(TString("Pt_EM_Probe_Trig_All_Triglist")+SN_Triglist, emobj_probe->Pt());	 
	      _histos.Fill2D(TString("Pt_DetEta_EM_Probe_Trig_All_Triglist")+SN_Triglist, emobj_probe->Pt(),emobj_probe->CalDetectorEta());
	      _histos.Fill2D(TString("Pt_PhysEta_EM_Probe_Trig_All_Triglist")+SN_Triglist, emobj_probe->Pt(),emobj_probe->Eta());
	      _histos.Fill2D(TString("InvMass_DetEta_EM_Probe_Trig_All_Triglist")+SN_Triglist, mass,emobj_probe->CalDetectorEta());	      
	      _histos.Fill2D(TString("InvMass_PhysEta_EM_Probe_Trig_All_Triglist")+SN_Triglist, mass,emobj_probe->Eta());	      
	      _histos.Fill2D(TString("Pt_InvMass_EM_Probe_Trig_All_Triglist")+SN_Triglist, emobj_probe->Pt(),mass);	 
 	    
	      // for all triggers from v8 to v14
	      _histos.Fill1D(TString("InvMass_EM_Probe_Trig_All"), mass);
	      _histos.Fill1D(TString("DetEta_EM_Probe_Trig_All"), emobj_probe->CalDetectorEta());
	      _histos.Fill1D(TString("PhysEta_EM_Probe_Trig_All"), emobj_probe->Eta());
	      _histos.Fill1D(TString("DetPhi_EM_Probe_Trig_All"), emobj_probe->CalDetectorPhi());
	      _histos.Fill1D(TString("TrkPhiEM3_EM_Probe_Trig_All"), emobj_probe->TrkPhiEM3());
	      _histos.Fill1D(TString("Pt_EM_Probe_Trig_All"), emobj_probe->Pt());	      
	      _histos.Fill2D(TString("Pt_DetEta_EM_Probe_Trig_All"), emobj_probe->Pt(),emobj_probe->CalDetectorEta());	      
	      _histos.Fill2D(TString("Pt_PhysEta_EM_Probe_Trig_All"), emobj_probe->Pt(),emobj_probe->Eta());	      
	      _histos.Fill2D(TString("InvMass_DetEta_EM_Probe_Trig_All"), mass,emobj_probe->CalDetectorEta());	      
	      _histos.Fill2D(TString("InvMass_PhysEta_EM_Probe_Trig_All"), mass,emobj_probe->Eta());	      
	      _histos.Fill2D(TString("Pt_InvMass_EM_Probe_Trig_All"), emobj_probe->Pt(),mass);	      

	      // probe electron passes any triggers in this trigger list
	      bool trigger_matched_probelist = false;
	      bool trigger_matched_probe = false;
	      bool fired25_v15=false;
	      bool fired25_v16=false;
	      bool fired27=false;

	      // look at each trigger inside each trigger list
	      for(int itriglist_flag=0; itriglist_flag < 8; ++itriglist_flag){
		for(int itrig=0; itrig<_trignames[itriglist_flag].size(); itrig++) {
                // get each trigger name  	  
		  string trigname =_trignames[itriglist_flag][itrig];
		  // the name of histogram will be hist_name_triglist_flag, itrig
		  // for example his_0_0 for trigger EM_HI_SH in v8-10, hist_3_1 for trigger E2_SHT20 in v12
		  char sn1[10]; sprintf(sn1,"%d", itriglist_flag);
		  char sn2[10]; sprintf(sn2,"%d", itrig);		  
		  TString SN=TString("_")+sn1+TString("_")+sn2;
		  int pass_l1 = emobj_probe->PassL1Trig(trigname.c_str(),0.4, l1cal_vec, l1cal2b_vec);
		  
                //std::cout << "Effanalysis Sees pass_l1 = " <<  pass_l1  << " vecsize =   " <<  l1cal2b_vec.size() << std::endl;
		  if (pass_l1){
		    _histos.Fill1D(TString("Pt_EM_Probe_L1_Matched")+SN, emobj_probe->Pt());
		    if (itriglist_flag < 5)
		      _histos.Fill1D(TString("l1Pt_EM_Probe_L1_Matched")+SN, l1cal_vec[pass_l1-1]->Et());
		    else if( l1cal2b_vec.size() > pass_l1 )
		      _histos.Fill1D(TString("l1Pt_EM_Probe_L1_Matched")+SN, l1cal2b_vec.at(pass_l1-1)->Etem() - 4.0);
		    int pass_l2 = emobj_probe->PassL2Trig(trigname.c_str(),0.4, l2cal_vec);
		    if (pass_l2){
		      _histos.Fill1D(TString("Pt_EM_Probe_L2_Matched")+SN, emobj_probe->Pt());
		      _histos.Fill1D(TString("l2Pt_EM_Probe_L2_Matched")+SN, l2cal_vec[pass_l2-1]->Et());
		      int pass_l3 = emobj_probe->PassL3Trig(trigname.c_str(),0.4, l3cal_vec);
		      if (pass_l3){
			_histos.Fill1D(TString("Pt_EM_Probe_L3_Matched")+SN, emobj_probe->Pt());
			_histos.Fill1D(TString("l3Pt_EM_Probe_L3_Matched")+SN, l3cal_vec[pass_l3-1]->Et());
		      }
		    }
		  }
		  // probe electron also passes trigger requirements (for each trigger)
		  bool probe_pass_trigger = false;
		  probe_pass_trigger = (emobj_probe->PassL1L2L3Trig(trigname.c_str(), 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec));
          if(_DropTriggerObjectMatchRequirement) probe_pass_trigger=true;
		  if(probe_pass_trigger) {
		    trigger_matched_probe = true;
		    if (itriglist_flag==triglist_flag)
		      trigger_matched_probelist = true;
		    if (strncmp(trigname.c_str(),string("E1_SHT25").c_str(),8)==0){
		      if (itriglist_flag==6)
			fired25_v16=true;
		      if (itriglist_flag==5){
			fired25_v15=true;
		      }
		    }
		    if (strncmp(trigname.c_str(),string("E1_SHT27").c_str(),8)==0){
		      fired27=true;
		    }
		   

		    // for each trigger
		    _histos.Fill1D(TString("InvMass_EM_Probe_Trig_Matched")+SN, mass);	      
		    _histos.Fill1D(TString("DetEta_EM_Probe_Trig_Matched")+SN, emobj_probe->CalDetectorEta());
		    _histos.Fill1D(TString("PhysEta_EM_Probe_Trig_Matched")+SN, emobj_probe->Eta());
		    _histos.Fill1D(TString("DetPhi_EM_Probe_Trig_Matched")+SN, emobj_probe->CalDetectorPhi());
		    _histos.Fill1D(TString("TrkPhiEM3_EM_Probe_Trig_Matched")+SN, emobj_probe->TrkPhiEM3());
		    _histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched")+SN, emobj_probe->Pt());

		    
		    _histos.Fill2D(TString("Pt_DetEta_EM_Probe_Trig_Matched")+SN, emobj_probe->Pt(), emobj_probe->CalDetectorEta());	     
		    _histos.Fill2D(TString("Pt_PhysEta_EM_Probe_Trig_Matched")+SN, emobj_probe->Pt(), emobj_probe->Eta());
		    _histos.Fill2D(TString("InvMass_DetEta_EM_Probe_Trig_Matched")+SN, mass,emobj_probe->CalDetectorEta());	      
		    _histos.Fill2D(TString("InvMass_PhysEta_EM_Probe_Trig_Matched")+SN, mass,emobj_probe->Eta());	      
		    _histos.Fill2D(TString("Pt_InvMass_EM_Probe_Trig_Matched")+SN, emobj_probe->Pt(),mass);
		  } // probe electron also matches with trigger objects
		} // loop over all triggers in this trigger list	      
	      } // loop over all trigger lists
	      if(trigger_matched_probe) {
		// for all triggers in one specific trigger list
		if (fired25_v15 ){
		  _histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched_v15"), emobj_probe->Pt());
		  if (triglist_flag==5)
		    _histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched_v15_0"), emobj_probe->Pt());
		}
		
		if (fired25_v16){		  
		  _histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched_v16_25"), emobj_probe->Pt());
		  if (triglist_flag==6  && _uses25)
		    _histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched_v16_25_0"), emobj_probe->Pt());
		}
		
		if (fired27){
		  _histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched_v16_27"), emobj_probe->Pt());
		  if (_uses27)
		    _histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched_v16_27_0"), emobj_probe->Pt());
		}
		if (fired27 || fired25_v16){		  
		  _histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched_v16_Both"), emobj_probe->Pt());
		  if (triglist_flag==6 && _uses25 && _uses27)
		    _histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched_v16_Both_0"), emobj_probe->Pt());
		}

		if  (trigger_matched_probelist){
		  _histos.Fill1D(TString("InvMass_EM_Probe_Trig_Matched_Triglist")+SN_Triglist, mass);	      
		  _histos.Fill1D(TString("DetEta_EM_Probe_Trig_Matched_Triglist")+SN_Triglist, emobj_probe->CalDetectorEta());
		  _histos.Fill1D(TString("PhysEta_EM_Probe_Trig_Matched_Triglist")+SN_Triglist, emobj_probe->Eta());
		  _histos.Fill1D(TString("DetPhi_EM_Probe_Trig_Matched_Triglist")+SN_Triglist, emobj_probe->CalDetectorPhi());
		  _histos.Fill1D(TString("TrkPhiPhiEM3_EM_Probe_Trig_Matched_Triglist")+SN_Triglist, emobj_probe->TrkPhiEM3());
		  _histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched_Triglist")+SN_Triglist, emobj_probe->Pt());	   
		  
		  _histos.Fill2D(TString("Pt_PhysEta_EM_Probe_Trig_Matched_Triglist")+SN_Triglist, emobj_probe->Pt(), emobj_probe->Eta());
		  _histos.Fill2D(TString("InvMass_DetEta_EM_Probe_Trig_Matched_Triglist")+SN_Triglist, mass,emobj_probe->CalDetectorEta());	      
		  _histos.Fill2D(TString("InvMass_PhysEta_EM_Probe_Trig_Matched_Triglist")+SN_Triglist, mass,emobj_probe->Eta());	      
		  _histos.Fill2D(TString("Pt_InvMass_EM_Probe_Trig_Matched_Triglist")+SN_Triglist, emobj_probe->Pt(),mass);
		  
		}	    
		// for all triggers from v8 to v14
		_histos.Fill1D(TString("InvMass_EM_Probe_Trig_Matched"), mass);
		_histos.Fill1D(TString("DetEta_EM_Probe_Trig_Matched"), emobj_probe->CalDetectorEta());
		_histos.Fill1D(TString("PhysEta_EM_Probe_Trig_Matched"), emobj_probe->Eta());
		_histos.Fill1D(TString("DetPhi_EM_Probe_Trig_Matched"), emobj_probe->CalDetectorPhi());
		_histos.Fill1D(TString("TrkPhiEM3_EM_Probe_Trig_Matched"), emobj_probe->TrkPhiEM3());
		_histos.Fill1D(TString("Pt_EM_Probe_Trig_Matched"), emobj_probe->Pt());	  
		_histos.Fill2D(TString("Pt_DetEta_EM_Probe_Trig_Matched"), emobj_probe->Pt(), emobj_probe->CalDetectorEta());	  
		_histos.Fill2D(TString("Pt_PhysEta_EM_Probe_Trig_Matched"), emobj_probe->Pt(), emobj_probe->Eta());
		_histos.Fill2D(TString("InvMass_DetEta_EM_Probe_Trig_Matched"), mass,emobj_probe->CalDetectorEta());	      
		_histos.Fill2D(TString("InvMass_PhysEta_EM_Probe_Trig_Matched"), mass,emobj_probe->Eta());	      
		_histos.Fill2D(TString("Pt_InvMass_EM_Probe_Trig_Matched"), emobj_probe->Pt(),mass);
	      }
	      
	    } // tag electron matches with trigger objects

	  } // loop over triggers for each trigger list
	}
      } // loop over all EM objects    
    } // get emselector and triglist flag
} //passes at least one trigger

//
// EM+Track sample to study PreSelection Efficiency: id=10,11, emfraction, isolation
//
void EffAnalysis::PreSelectionEff(cafe::Event& event) {
  if(_debugLevel>=30) cout<<"Preselection Efficiency Study"<<endl;

  vector<CAFEMObj*> emobjs;
  vector<CAFEMObj*> probeEMs;
  vector<CAFTrack*> trks; 
  const CAFEMObj *emobj;
  CAFTrack *trk;

  // get primary vertex
  float v_z;
  bool getPrimaryVertex = event.get("Primary vertexZ", v_z);

  // trigger list
  int triglist_flag = -1;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;

  // solenoid polarity
  int solpol = 999;

  if(event.get("Good EMObjs", emobjs) && event.get("L1CalTowers", l1cal_vec) && event.get("L1Cal2bTowers", l1cal2b_vec) && 
     event.get("L2GblEMs", l2cal_vec) && event.get("L3Eles", l3cal_vec) &&
     event.get("triglist flag", triglist_flag) && event.get("Probe EMObjs", probeEMs) && 
     event.get("Good Tracks", trks) && event.get("solenoid polarity", solpol)) {

    // convert it from 0 and 1 to -1 and 1
    solpol = 2*solpol - 1;
    
    for(int iem=0; iem<emobjs.size(); ++iem){
      emobj = emobjs[iem];
      
      // the tag electron must pass trigger requirements
      // for GEANT MC, we do not need to check trigger efficiency
      bool pass_trigger = false;
      if(_MCStudy || _DropTriggerObjectMatchRequirement) pass_trigger = true;
      else pass_trigger = emobj->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec);
      if(!pass_trigger) continue;
      
      // loop over all selected tracks
      for(int itrk=0; itrk<trks.size(); ++itrk){
	trk = trks[itrk];

	// construct Z candidate (track already has pT>_PtCut_trk GeV requirement)
	// the track needs to have at least one SMT hits and have Chi2/dof<8. (from Terry's Z rapidity analysis)       
	if(trk->nsmt()>=1 && trk->getChi2Ndf()<8.) {
	  CAFZCand zcand(emobj, trk);
	 
          // make tight requirement on the tag electron and also emobj-track invariant mass 
          // to get more pure sample 
	  if(emobj->has_good_spatial_track_match() && zcand.In_ZPeak(_ZMassCut1, _ZMassCut2) ) {
	    TVector3 em_vect = emobj->vect3();
	    TVector3 trk_vect = trk->vect3();
	    float dphi = abs(em_vect.DeltaPhi(trk_vect));
	    
	    // EM and Track are back-to-back in phi so that the track will not be associated with the tag electron
	    if(dphi>2.8) {
	      float trk_deteta = trk->TrackDetEta(solpol);
	      float trk_detphi = trk->TrackDetPhi(solpol);

	      // require extrapolated track position must be in CC or EC fiducial region
	      // and it also needs to be isolated
	      if(trk->IsCCECFid(trk_deteta, trk_detphi, _DetEtaCC, _DetEtaEC1, _DetEtaEC2) && trk->IsIsolatedTrack(event, _coneSize_Trk, _sumPtCut_Trk)) {
		_histos.Fill1D("ZCandMass_EM_Trk", zcand.Mass());	    
		_histos.Fill1D("TrkDetEta_EM_Trk_PreSel_All", trk_deteta);
		
		if(fabs(trk_deteta)<_DetEtaCC){
		  _histos.Fill2D("ZMass_vs_DetEta_Before_Presel_CC", trk_deteta,zcand.Mass());
		  _histos.Fill2D("ZMass_vs_Eta_Before_Presel_CC", trk->Eta(),zcand.Mass());
		  _histos.Fill2D("ZMass_vs_Vtx_Before_Presel_CC", v_z,zcand.Mass());
		  _histos.Fill2D("ZMass_vs_Pt_Before_Presel_CC", trk->Pt(),zcand.Mass());
		} else if(fabs(trk_deteta)>_DetEtaEC1 && fabs(trk_deteta)<_DetEtaEC2  ){
		  _histos.Fill2D("ZMass_vs_DetEta_Before_Presel_EC", trk_deteta,zcand.Mass());
		  _histos.Fill2D("ZMass_vs_Eta_Before_Presel_EC", trk->Eta(),zcand.Mass());
		  _histos.Fill2D("ZMass_vs_Vtx_Before_Presel_EC", v_z,zcand.Mass());
		  _histos.Fill2D("ZMass_vs_Pt_Before_Presel_EC", trk->Pt(),zcand.Mass());
		}

		bool found_matched_EM = false;	

		for(int i=0; i<probeEMs.size(); i++) {	  
    		   
		  // the matched EM cluster has to pass id, emfraction and isolation cuts
		  if( probeEMs[i]->IsEM() && probeEMs[i]->PassEMFracIso(_EMFracCut, _IsoCut) ) {
		    // if (probeEMs[i]->GetChargedTrack()){
		    // TMBTrack *newtrack = (TMBTrack*)(probeEMs[i]->GetChargedTrack()->Clone());
		      
		    //CAFTrack p(newtrack);
		      //float deltaR = kinem::delta_R(p.TrackDetEta(solpol), p.TrackDetPhi(solpol), trk_deteta, trk_detphi);
		      float deltaR = kinem::delta_R(probeEMs[i]->CalDetectorEta(), probeEMs[i]->CalDetectorPhi(), 
                                                  trk_deteta, trk_detphi);
		      
		      if(deltaR<0.2) found_matched_EM = true;
		      //delete newtrack;
		      // }
		  }//pass emfrac and isolation cuts
		}
		if(found_matched_EM) {
		  _histos.Fill1D("TrkDetEta_EM_Trk_PreSel_Matched", trk_deteta);
		  _histos.Fill1D("ZCandMass_EM_Trk_Matched", zcand.Mass());
		  if(fabs(trk_deteta)<_DetEtaCC){
		    _histos.Fill2D("ZMass_vs_DetEta_After_Presel_CC", trk_deteta,zcand.Mass());
		    _histos.Fill2D("ZMass_vs_Eta_After_Presel_CC", trk->Eta(),zcand.Mass());
		    _histos.Fill2D("ZMass_vs_Vtx_After_Presel_CC", v_z,zcand.Mass());
		    _histos.Fill2D("ZMass_vs_Pt_After_Presel_CC", trk->Pt(),zcand.Mass());
		  } else if(fabs(trk_deteta)>_DetEtaEC1 && fabs(trk_deteta)<_DetEtaEC2 ){
		    _histos.Fill2D("ZMass_vs_DetEta_After_Presel_EC", trk_deteta,zcand.Mass());
		    _histos.Fill2D("ZMass_vs_Eta_After_Presel_EC", trk->Eta(),zcand.Mass());
		    _histos.Fill2D("ZMass_vs_Vtx_After_Presel_EC", v_z,zcand.Mass());
		    _histos.Fill2D("ZMass_vs_Pt_After_Presel_EC", trk->Pt(),zcand.Mass());
		  }
		}
	      } // extrapolated track position in CC/EC fiducial region
	    }//dphi>2.8
	    
	  }// Good EM-Track Z candidate
	  else if ((emobj->has_good_spatial_track_match() && zcand.In_ZPeak(_ZMassCut1- ((_ZMassCut2 - _ZMassCut1)/2.)  , _ZMassCut1) ) ||  (emobj->has_good_spatial_track_match() && zcand.In_ZPeak(_ZMassCut2, _ZMassCut2 + ((_ZMassCut2 - _ZMassCut1)/2.)) ) )              {
	    TVector3 em_vect = emobj->vect3();
	    TVector3 trk_vect = trk->vect3();
	    float dphi = em_vect.DeltaPhi(trk_vect);
	    if(dphi>2.8) {
	      float trk_deteta = trk->TrackDetEta(solpol);
	      float trk_detphi = trk->TrackDetPhi(solpol);
	      if(trk->IsCCECFid(trk_deteta, trk_detphi, _DetEtaCC, _DetEtaEC1, _DetEtaEC2) && trk->IsIsolatedTrack(event, _coneSize_Trk, _sumPtCut_Trk)) {
		_histos.Fill1D("QCDZCandMass_EM_Trk", zcand.Mass());	    
		_histos.Fill1D("QCDTrkDetEta_EM_Trk_PreSel_All", trk_deteta);
		
		if(fabs(trk_deteta)<_DetEtaCC){
		  _histos.Fill2D("QCDZMass_vs_DetEta_Before_Presel_CC", trk_deteta,zcand.Mass());
		  _histos.Fill2D("QCDZMass_vs_Eta_Before_Presel_CC", trk->Eta(),zcand.Mass());
		  _histos.Fill2D("QCDZMass_vs_Vtx_Before_Presel_CC", v_z,zcand.Mass());
		  _histos.Fill2D("QCDZMass_vs_Pt_Before_Presel_CC", trk->Pt(),zcand.Mass());
		} else if(fabs(trk_deteta)>_DetEtaEC1 && fabs(trk_deteta)<_DetEtaEC2  ){
		  _histos.Fill2D("QCDZMass_vs_DetEta_Before_Presel_EC", trk_deteta,zcand.Mass());
		  _histos.Fill2D("QCDZMass_vs_Eta_Before_Presel_EC", trk->Eta(),zcand.Mass());
		  _histos.Fill2D("QCDZMass_vs_Vtx_Before_Presel_EC", v_z,zcand.Mass());
		  _histos.Fill2D("QCDZMass_vs_Pt_Before_Presel_EC", trk->Pt(),zcand.Mass());
		}
		
		bool found_matched_EM = false;		 
		for(int i=0; i<probeEMs.size(); i++) {	      		   
		  // the matched EM cluster has to pass id, emfraction and isolation cuts
		  if( probeEMs[i]->IsEM() && probeEMs[i]->PassEMFracIso(_EMFracCut, _IsoCut) ) {
		    float deltaR = kinem::delta_R(probeEMs[i]->CalDetectorEta(), probeEMs[i]->CalDetectorPhi(), 
						  trk_deteta, trk_detphi);
		    if(deltaR<0.2) found_matched_EM = true;
		  }//pass emfrac and isolation cuts
		}
		
		if(found_matched_EM) {
		  _histos.Fill1D("QCDTrkDetEta_EM_Trk_PreSel_Matched", trk_deteta);
		  _histos.Fill1D("QCDZCandMass_EM_Trk_Matched", zcand.Mass());	    
		  if(fabs(trk_deteta)<_DetEtaCC){
		    _histos.Fill2D("QCDZMass_vs_DetEta_After_Presel_CC", trk_deteta,zcand.Mass());
		    _histos.Fill2D("QCDZMass_vs_Eta_After_Presel_CC", trk->Eta(),zcand.Mass());
		    _histos.Fill2D("QCDZMass_vs_Vtx_After_Presel_CC", v_z,zcand.Mass());
		    _histos.Fill2D("QCDZMass_vs_Pt_After_Presel_CC", trk->Pt(),zcand.Mass());
		  } else if(fabs(trk_deteta)>_DetEtaEC1 && fabs(trk_deteta)<_DetEtaEC2 ){
		    _histos.Fill2D("QCDZMass_vs_DetEta_After_Presel_EC", trk_deteta,zcand.Mass());
		    _histos.Fill2D("QCDZMass_vs_Eta_After_Presel_EC", trk->Eta(),zcand.Mass());
		    _histos.Fill2D("QCDZMass_vs_Vtx_After_Presel_EC", v_z,zcand.Mass());
		    _histos.Fill2D("QCDZMass_vs_Pt_After_Presel_EC", trk->Pt(),zcand.Mass());
		  }
		}
	      } // extrapolated track position in CC/EC fiducial region
	    }
	  }
	} // track requirements

      }//itrk
    }//iem

  }//getEventInfo
}

//
// EM+Loose EM sample to study HMx efficiency
//
void EffAnalysis::HMxEff(cafe::Event& event) {
  if(_debugLevel>=30) cout<<"HMatrix Efficiency Study"<<endl;
  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");

  vector<CAFEMObj*> emobjs;
  vector<CAFEMObj*> probeEMs;
  const CAFEMObj *emobj;
  const CAFEMObj *emobj_probe;

  CAFMet met;
  CAFMet rawmet;
  double instlumi;
  int runNo, evtNo;

  vector<CAFEMObj*> emobjs_forSET;

  // get primary vertex
  float v_x, v_y, v_z;
  bool getPrimaryVertexX = event.get("Primary vertexZ", v_x);
  bool getPrimaryVertexY = event.get("Primary vertexZ", v_y);
  bool getPrimaryVertexZ = event.get("Primary vertexZ", v_z);

  // construct Z candidates
  float vtx[3] = {v_x, v_y, v_z};

  double zScalarEt = 0;
  double ScalarEt_Evt = 0;

  int triglist_flag = -1;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;
  int solpol = -999;
  float vtx_x, vtx_y, vtx_z;

  CAFZCand zcand;
  bool passcuts=false;
  if (event.get("Probe EMObjs", emobjs_forSET) && event.get("EMCorr Met", met) && 
      event.get("Raw Met", rawmet) &&
      event.get("L1CalTowers", l1cal_vec) && event.get("L2GblEMs", l2cal_vec) && 
      event.get("L3Eles", l3cal_vec) && event.get("triglist flag", triglist_flag) &&
      event.get("run number", runNo) && event.get("event number", evtNo) &&
      event.get("InstLumi", instlumi) && event.get("Best primary vertexX", vtx_x) && 
      event.get("Best primary vertexY", vtx_y) && event.get("Best primary vertexZ", vtx_z) &&
      event.get("solenoid polarity", solpol)) {
   
    
    if(emobjs_forSET.size() >= 2) passcuts=true;
  
    if(!passcuts) return;
    
    if(_dorawCellsRecoil) {
      if (_useConsistentMET) {
	zcand = CAFZCand(emobjs_forSET[0], emobjs_forSET[1], &rawmet, vtx, true);
      } else {
	zcand = CAFZCand(emobjs_forSET[0], emobjs_forSET[1], &met, vtx);
      }
    } else {
      zcand = CAFZCand(emobjs_forSET[0], emobjs_forSET[1], &met);
    }
    
  }

  if (_useConsistentMET) {
    TVector2 consistMET=zcand.GetConsistentMET();
    double dummySET=met.scalarEt();
    met.SetMet(consistMET.X(),consistMET.Y(),consistMET.Mod(),dummySET);
  }
  
  // MOVED FROM LATER IN THE CODE /////////////////////////////////////////////////////////////
  // calculate scalarEt and remove contribution due to two electrons
  if (!_dorawCellsRecoil) {
    ScalarEt_Evt = met.scalarEt();
    double ScalarEt_EMObjs = emobjs_forSET[0]->EMScalarEt()*emobjs_forSET[0]->E()/emobjs_forSET[0]->uncorrE() +
      emobjs_forSET[1]->EMScalarEt()*emobjs_forSET[1]->E()/emobjs_forSET[1]->uncorrE();
    zScalarEt = ScalarEt_Evt - ScalarEt_EMObjs;
  } else {
    ScalarEt_Evt = rawmet.scalarEt();
    float cntrib1=0;
    float cntrib2=0;
    emobjs_forSET[0]->getRawElecVectorFromCells(vtx,&cntrib1);
    emobjs_forSET[1]->getRawElecVectorFromCells(vtx,&cntrib2);
    double ScalarEt_EMObjs = cntrib1 + cntrib2;
    zScalarEt = ScalarEt_Evt - ScalarEt_EMObjs;
  }
  //
 
  char bins_SET[10];
  int bin_SET_number;
  if(zScalarEt<30.)
    bin_SET_number=0;
  else if(zScalarEt<50.)
    bin_SET_number=1;
  else if(zScalarEt<80.)
    bin_SET_number=2;
  else if(zScalarEt<120.)
    bin_SET_number=3;
  else 
    bin_SET_number=4;
  sprintf(bins_SET, "%d", bin_SET_number);

  // make sure that we get pointers to each selector
  if(event.get("Good EMObjs", emobjs) && event.get("L1CalTowers", l1cal_vec) && event.get("L1Cal2bTowers", l1cal2b_vec) && 
     event.get("L2GblEMs", l2cal_vec) && event.get("L3Eles", l3cal_vec) &&
     event.get("triglist flag", triglist_flag) && event.get("Probe EMObjs", probeEMs)) {
     

    
    for(int iem=0; iem<emobjs.size(); ++iem){
      emobj = emobjs[iem];
       bool pass_trigger = false;
      if(_MCStudy || _DropTriggerObjectMatchRequirement) pass_trigger = true;
      else pass_trigger = emobj->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec);
      if(!pass_trigger) continue;
      if(!emobj->has_good_spatial_track_match()) continue;
      
	 // loop over probe electrons      
      for(int iprobe=0; iprobe<probeEMs.size(); ++iprobe){
        emobj_probe = probeEMs[iprobe];
	
	CAFZCand zcand(emobj, emobj_probe);
	
	// need to make sure that the probe em object already
	// passes id, emfraction and isolation cuts
	if(((!_TPhmx_DoTheTrackFirst)|| (emobj_probe->has_good_spatial_track_match() && emobj_probe->IsCCECFid(_DetEtaCC,_DetEtaEC1, _DetEtaEC2,_useTrackFiducial))) && 
	   emobj_probe->IsEM() && 
	   emobj_probe->PassEMFracIso(_EMFracCut, _IsoCut) &&
	   emobj_probe->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial) &&
	    zcand.In_ZPeak(_ZMassCut1, _ZMassCut2) && emobj_probe->Pt()>_ElecPtCut) {

	  /* removed only tag needs to pass trigger requirement */	   
	  // the probe electron must pass trigger requirements
	  // for GEANT MC, we do not need to check trigger efficiency
	  //  bool pass_trigger = false;
	  //if(_MCStudy) pass_trigger = true;
	  //else pass_trigger = emobj_probe->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l2cal_vec, l3cal_vec);
	  //if(!pass_trigger) continue;
      
 	  double elec_eta=emobj_probe->Eta();

	  char bins_Eta[10];
	  int bin_Eta_number;
	  if(elec_eta<-1.3)
	    bin_Eta_number=0;
	  else if(elec_eta>1.3)
	    bin_Eta_number=14;
	  else
	    bin_Eta_number=int((elec_eta+1.3)/0.2)+1;
	  sprintf(bins_Eta, "%d", bin_Eta_number);

	  _histos.Fill1D("EMDetEta_EM_Probe_HMx_All", emobj_probe->CalDetectorEta());

	  if( emobj_probe->IsCCFid(_DetEtaCC,_useTrackFiducial)){
	    _histos.Fill2D("ZMass_vs_DetEta_Before_HMx_CC", emobj_probe->CalDetectorEta(),zcand.Mass());
	    _histos.Fill2D("ZMass_vs_Eta_Before_HMx_CC", emobj_probe->Eta(),zcand.Mass());
	    _histos.Fill2D("ZMass_vs_Vtx_Before_HMx_CC", v_z,zcand.Mass());
	    _histos.Fill2D("ZMass_vs_Pt_Before_HMx_CC", emobj_probe->Pt(),zcand.Mass());
	    _histos.Fill2D("Eta_vs_Pt_Before_HMx_CC", emobj_probe->Pt(),emobj_probe->Eta());
            _histos.Fill2D("EMEta_beforeHMx_Vtx_Eta_CC",  v_z, emobj_probe->Eta());
            _histos.Fill2D("EMDetEta_beforeHMx_Vtx_DetEta_CC",  v_z, emobj_probe->CalDetectorEta());
	    _histos.Fill2D("ZMass_vs_Pt_Before_HMx_CC_Etabin", emobj_probe->Pt(), zcand.Mass());
	    _histos.Fill2D(string("ZMass_vs_Pt_Before_HMx_CC_Etabin_")+bins_Eta, emobj_probe->Pt(), zcand.Mass());
	    _histos.Fill2D("ZMass_V_Pt_EM_Probe_HMx_All_SETbin", emobj_probe->Pt(), zcand.Mass());
	    _histos.Fill2D(string("ZMass_V_Pt_EM_Probe_HMx_All_SETbin_")+bins_SET, emobj_probe->Pt(), zcand.Mass());

	  } else if( emobj_probe->IsECFid(_DetEtaEC1, _DetEtaEC2)){
	    _histos.Fill2D("ZMass_vs_DetEta_Before_HMx_EC", emobj_probe->CalDetectorEta(),zcand.Mass());
	    _histos.Fill2D("ZMass_vs_Eta_Before_HMx_EC", emobj_probe->Eta(),zcand.Mass());
	    _histos.Fill2D("ZMass_vs_Vtx_Before_HMx_EC", v_z,zcand.Mass());
	    _histos.Fill2D("ZMass_vs_Pt_Before_HMx_EC", emobj_probe->Pt(),zcand.Mass());
	    _histos.Fill2D("EMEta_beforeHMx_Vtx_Eta_EC", v_z, emobj_probe->Eta());
            _histos.Fill2D("EMDetEta_beforeHMx_Vtx_DetEta_EC", v_z, emobj_probe->CalDetectorEta());
	  }
	  
	  if(emobj_probe->PassHMx(_HM7Cut, _HM8Cut)){
	    _histos.Fill1D("EMDetEta_EM_Probe_HMx_Matched", emobj_probe->CalDetectorEta());
	    if( emobj_probe->IsCCFid(_DetEtaCC,_useTrackFiducial)){
	      _histos.Fill2D("ZMass_vs_DetEta_After_HMx_CC", emobj_probe->CalDetectorEta(),zcand.Mass());
	      _histos.Fill2D("ZMass_vs_Eta_After_HMx_CC", emobj_probe->Eta(),zcand.Mass());
	      _histos.Fill2D("ZMass_vs_Vtx_After_HMx_CC", v_z,zcand.Mass());
	      _histos.Fill2D("ZMass_vs_Pt_After_HMx_CC", emobj_probe->Pt(),zcand.Mass());
	      _histos.Fill2D("Eta_vs_Pt_After_HMx_CC", emobj_probe->Pt(),emobj_probe->Eta());
              _histos.Fill2D("EMEta_afterHMx_Vtx_Eta_CC", v_z, emobj_probe->Eta());
              _histos.Fill2D("EMDetEta_afterHMx_Vtx_DetEta_CC", v_z, emobj_probe->CalDetectorEta());
	      _histos.Fill2D("ZMass_vs_Pt_After_HMx_CC_Etabin", emobj_probe->Pt(), zcand.Mass());
	      _histos.Fill2D(string("ZMass_vs_Pt_After_HMx_CC_Etabin_")+bins_Eta, emobj_probe->Pt(), zcand.Mass());
	      _histos.Fill2D("ZMass_V_Pt_EM_Probe_HMx_Matched_SETbin", emobj_probe->Pt(), zcand.Mass());
	      _histos.Fill2D(string("ZMass_V_Pt_EM_Probe_HMx_Matched_SETbin_")+bins_SET, emobj_probe->Pt(), zcand.Mass());
	    } else if ( emobj_probe->IsECFid(_DetEtaEC1, _DetEtaEC2)){
	      _histos.Fill2D("ZMass_vs_DetEta_After_HMx_EC", emobj_probe->CalDetectorEta(),zcand.Mass());
	      _histos.Fill2D("ZMass_vs_Eta_After_HMx_EC", emobj_probe->Eta(),zcand.Mass());
	      _histos.Fill2D("ZMass_vs_Vtx_After_HMx_EC", v_z,zcand.Mass());
	      _histos.Fill2D("ZMass_vs_Pt_After_HMx_EC", emobj_probe->Pt(),zcand.Mass());
	      _histos.Fill2D("EMEta_afterHMx_Vtx_Eta_EC", v_z, emobj_probe->Eta());
              _histos.Fill2D("EMDetEta_afterHMx_Vtx_DetEta_EC", v_z, emobj_probe->CalDetectorEta());
	    }
	  }
	}
      }
    }//iem
    
  }//getEventInfo
}

void EffAnalysis::LooseTrackMatchEff(cafe::Event& event) {
  if(_debugLevel>=30) cout<<"Loose Track Matching Efficiency Study"<<endl;
  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");  
  double pT_low=0., pT_high=1000.;

  CAFMet met;
  CAFMet rawmet;

  vector<CAFEMObj*> emobjs;
  vector<CAFEMObj*> probeEMs;
  const CAFEMObj *emobj;
  const CAFEMObj *emobj_probe;
  
  int triglist_flag = -1;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;
  int solpol = -999;
  float vtx_x, vtx_y, vtx_z;
  double instlumi = 0.;
 
  // get primary vertex
  float v_x, v_y, v_z;
  bool getPrimaryVertexX = event.get("Primary vertexZ", v_x);
  bool getPrimaryVertexY = event.get("Primary vertexZ", v_y);
  bool getPrimaryVertexZ = event.get("Primary vertexZ", v_z);
  
  // construct Z candidates
  float vtx[3] = {v_x, v_y, v_z};
  
  char bins_Vtx[10];
  int bin_Vtx_number;
  bin_Vtx_number=int((v_z+60.)/20.);
  sprintf(bins_Vtx, "%d", bin_Vtx_number);
  
  // get probe electrons
  bool getProbeElectrons = event.get("Probe EMObjs", probeEMs);

  
  double zScalarEt = 0;
  double ScalarEt_Evt = 0;

  CAFZCand zcand;

  if (_useConsistentMET) {
    TVector2 consistMET=zcand.GetConsistentMET();
    double dummySET=met.scalarEt();
    met.SetMet(consistMET.X(),consistMET.Y(),consistMET.Mod(),dummySET);
  }
  // make sure that we get pointers to each selector
  if(event.get("Good EMObjs", emobjs) && event.get("L1CalTowers", l1cal_vec) && event.get("L1Cal2bTowers", l1cal2b_vec) && 
     event.get("L2GblEMs", l2cal_vec) && event.get("L3Eles", l3cal_vec) &&
     event.get("triglist flag", triglist_flag) &&
     event.get("Raw Met", rawmet) &&
     event.get("InstLumi", instlumi) ) 
  {
  if (instlumi > _InstLumi_lowcut && instlumi < _InstLumi_highcut) 
  {

    for(int iem=0; iem<emobjs.size(); ++iem){
      emobj = emobjs[iem];

      // the tag electron must pass trigger requirements
      // for GEANT MC, we do not need to check trigger efficiency
      bool pass_trigger = false;
      if(_MCStudy || _DropTriggerObjectMatchRequirement) pass_trigger = true;
      else pass_trigger = emobj->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec);
      if(!pass_trigger) continue;

      // if tag electron and probe electron are the same, zcand mass will be very small
      // and will be removed by z mass window requirment
      for(int iprobe=0; iprobe<probeEMs.size(); ++iprobe){
        emobj_probe = probeEMs[iprobe];

	if(emobj->has_good_spatial_track_match() && /* !!! this is the cut to vary !!! */
	   (((!_TPtrk_IncludeECtag)&&emobj->IsCCFid(_DetEtaCC,_useTrackFiducial))||(_TPtrk_IncludeECtag&&emobj->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial)))) {
	  if(emobj_probe->IsEM() && emobj_probe->PassEMFracIso(_EMFracCut, _IsoCut) && emobj_probe->Pt()>_ElecPtCut) {

        zcand = CAFZCand(emobj, emobj_probe, &rawmet, vtx, true);
        double recoilPt = zcand.MagRecoil();
        if (recoilPt > _ZUtCut) return;
       
	    if(zcand.In_ZPeak(_ZMassCut1, _ZMassCut2)) {

	      // probe electron type, 0 for CC, 1 for EC
	      int type = -1;
	      if(emobj_probe->IsCC(_DetEtaCC)) type = 0;
	      else type = 1;
	      char elec_type[10];  sprintf(elec_type, "%d", type);

	      // kinematical variables
	      float elec_deteta = emobj_probe->CalDetectorEta();
	      float elec_eta = emobj_probe->Eta();
	      float elec_pT = emobj_probe->Pt();
              double mass = zcand.Mass();

	      double pT_true;
              double event_vertex=v_z;

              char bins_Eta[10];
              int bin_Eta_number;
              if(elec_eta<-1.3)
                bin_Eta_number=0;
              else if(elec_eta>1.3)
                bin_Eta_number=14;
              else
                bin_Eta_number=int((elec_eta+1.3)/0.2)+1;
              sprintf(bins_Eta, "%d", bin_Eta_number);	      

	      _histos.Fill1D("loose_EMDetEta_EM_Probe_Trk_All", elec_deteta);
	      _histos.Fill1D(string("loose_EMEta_EM_Probe_Trk_")+elec_type, elec_eta);
	      _histos.Fill1D(string("loose_EMPt_EM_Probe_Trk_")+elec_type, elec_pT);

	      // for different primary vertex region
	      int vtx_region = -1;
              if(v_z<-50.) vtx_region = 0;
              else if (v_z<-40.) vtx_region = 1;
              else if (v_z<-30.) vtx_region = 2;
	      else if (v_z<-20.) vtx_region = 3;
              else if (v_z<-10.) vtx_region = 4;
              else if (v_z<0.) vtx_region = 5;
              else if (v_z<10.) vtx_region = 6;
	      else if (v_z<20.) vtx_region = 7;
              else if (v_z<30.) vtx_region = 8;
	      else if (v_z<40.) vtx_region = 9;
              else if (v_z<50.) vtx_region = 10;
	      else vtx_region = 11;
	      char vtx_region_char[10];  sprintf(vtx_region_char, "%d", vtx_region);

	      _histos.Fill1D(string("loose_EMDetEta_EM_Probe_Trk_All_Vtx_")+vtx_region_char, elec_deteta);
	      _histos.Fill1D(string("loose_EMEta_EM_Probe_Trk_All_Vtx_")+vtx_region_char, elec_eta);
	      if(type==0) _histos.Fill1D(string("loose_EMPt_EM_Probe_Trk_All_CC_Vtx_")+vtx_region_char, elec_pT);
	      if(type==1) _histos.Fill1D(string("loose_EMPt_EM_Probe_Trk_All_EC_Vtx_")+vtx_region_char, elec_pT);

              // fill invariant mass distribution for different eta region: 31 regions from -3.0 to 3.0
	      double peta =  elec_eta;
	      int eta_region = -1;
	      if (-3.1<=peta && peta<-2.9) {eta_region = 0;}
	      else if (-2.9<=peta && peta<-2.7) {eta_region = 1;}
	      else if (-2.7<=peta && peta<-2.5) {eta_region = 2;}
	      else if (-2.5<=peta && peta<-2.3) {eta_region = 3;}
	      else if (-2.3<=peta && peta<-2.1) {eta_region = 4;}
	      else if (-2.1<=peta && peta<-1.9) {eta_region = 5;}
	      else if (-1.9<=peta && peta<-1.7) {eta_region = 6;}
	      else if (-1.7<=peta && peta<-1.5) {eta_region = 7;}
	      else if (-1.5<=peta && peta<-1.3) {eta_region = 8;}
	      else if (-1.3<=peta && peta<-1.1) {eta_region = 9;}
	      else if (-1.1<=peta && peta<-0.9) {eta_region = 10;}
	      else if (-0.9<=peta && peta<-0.7) {eta_region = 11;}
	      else if (-0.7<=peta && peta<-0.5) {eta_region = 12;}
	      else if (-0.5<=peta && peta<-0.3) {eta_region = 13;}
	      else if (-0.3<=peta && peta<-0.1) {eta_region = 14;}
	      else if (-0.1<=peta && peta<0.1) {eta_region = 15;}
	      else if (0.1<=peta && peta<0.3) {eta_region = 16;}
	      else if (0.3<=peta && peta<0.5) {eta_region = 17;}
	      else if (0.5<=peta && peta<0.7) {eta_region = 18;}
	      else if (0.7<=peta && peta<0.9) {eta_region = 19;}
	      else if (0.9<=peta && peta<1.1) {eta_region = 20;}
	      else if (1.1<=peta && peta<1.3) {eta_region = 21;}
	      else if (1.3<=peta && peta<1.5) {eta_region = 22;}
	      else if (1.5<=peta && peta<1.7) {eta_region = 23;}
	      else if (1.7<=peta && peta<1.9) {eta_region = 24;}
	      else if (1.9<=peta && peta<2.1) {eta_region = 25;}
	      else if (2.1<=peta && peta<2.3) {eta_region = 26;}
	      else if (2.3<=peta && peta<2.5) {eta_region = 27;}
	      else if (2.5<=peta && peta<2.7) {eta_region = 28;}
	      else if (2.7<=peta && peta<2.9) {eta_region = 29;}
	      else if (2.9<=peta && peta<3.1) {eta_region = 30;}
	      char eta_region_char[10];  sprintf(eta_region_char, "%d", eta_region);

              // later we need to subtract background
	      if (type == 0) {//was cccc event, so cc probe
		_histos.Fill1D(string("loose_ZMass_vs_Eta_Before_Trk_Vtx_CC_")+vtx_region_char+string("_")+eta_region_char, mass);
		if(emobj_probe->has_spatial_track_match(-0.5)) {
		  _histos.Fill1D(string("loose_ZMass_vs_Eta_After_Trk_Vtx_CC_")+vtx_region_char+string("_")+eta_region_char, mass);
		}
	      }else if (type == 1){ //was ccec, so probe was ec
		_histos.Fill1D(string("loose_ZMass_vs_Eta_Before_Trk_Vtx_EC_")+vtx_region_char+string("_")+eta_region_char, mass);
		if(emobj_probe->has_spatial_track_match(-0.5)) {
		  _histos.Fill1D(string("loose_ZMass_vs_Eta_After_Trk_Vtx_EC_")+vtx_region_char+string("_")+eta_region_char, mass);
		}
	      }


	      if(type==1){  // for EC 
		_histos.Fill2D(string("loose_EMEta_EM_Probe_Trk_All_Vtx_Eta_EC"),v_z,elec_eta);
		_histos.Fill2D(string("loose_EMDetEta_EM_Probe_Trk_All_Vtx_DetEta_EC"),v_z,elec_deteta);
	      }

	      if(type==0){ 
		_histos.Fill2D(string("loose_EMEta_EM_Probe_Trk_All_Vtx_Eta_CC"),v_z,elec_eta);
		_histos.Fill2D(string("loose_EMDetEta_EM_Probe_Trk_All_Vtx_DetEta_CC"),v_z,elec_deteta);
		_histos.Fill2D(string("loose_EMDetEta_ZMass_EM_Probe_Trk_All_")+bins_Vtx, emobj_probe->CalDetectorEta(), mass);
		_histos.Fill2D(string("loose_EMEta_ZMass_EM_Probe_Trk_All_")+bins_Vtx, emobj_probe->Eta(), mass);
		_histos.Fill2D("loose_ZMass_vs_DetEta_Before_Trk_CC", emobj_probe->CalDetectorEta(), mass);
		_histos.Fill2D("loose_ZMass_vs_Eta_Before_Trk_CC", emobj_probe->Eta(), mass);
		_histos.Fill2D("loose_ZMass_vs_Vtx_Before_Trk_CC", v_z, mass);
		_histos.Fill2D("loose_ZMass_vs_Pt_Before_Trk_CC",  mass, emobj_probe->Pt());
		_histos.Fill2D("loose_ZMass_vs_DetEta_Before_Trk_TAG", emobj->CalDetectorEta(), mass);
		_histos.Fill2D("loose_ZMass_vs_Eta_Before_Trk_TAG", emobj->Eta(), mass);
		_histos.Fill2D("loose_ZMass_vs_Pt_Before_Trk_TAG",  mass, emobj->Pt());

	      }



	      if(emobj_probe->has_spatial_track_match(-0.5)) {
		_histos.Fill1D("loose_EMDetEta_EM_Probe_Spatial_Trk_Matched_All", elec_deteta);
		_histos.Fill1D(string("loose_EMEta_EM_Probe_Spatial_Trk_Matched_")+elec_type, elec_eta);
		_histos.Fill1D(string("loose_EMPt_EM_Probe_Spatial_Trk_Matched_")+elec_type, elec_pT);
		_histos.Fill1D(string("loose_EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx_")+vtx_region_char, elec_deteta);
		_histos.Fill1D(string("loose_EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_")+vtx_region_char, elec_eta);
		if(type==0) _histos.Fill1D(string("loose_EMPt_EM_Probe_Spatial_Trk_Matched_CC_Vtx_")+vtx_region_char, elec_pT);
		if(type==1) _histos.Fill1D(string("loose_EMPt_EM_Probe_Spatial_Trk_Matched_EC_Vtx_")+vtx_region_char, elec_pT);

		if(type==1){   // for EC
		  _histos.Fill2D(string("loose_EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_Eta_EC"), v_z, elec_eta);
		  _histos.Fill2D(string("loose_EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx_DetEta_EC"), v_z, elec_deteta);
		}

		if(type==0){
		  _histos.Fill2D(string("loose_EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_Eta_CC"), v_z, elec_eta);
		  _histos.Fill2D(string("loose_EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx_DetEta_CC"), v_z, elec_deteta);
		  _histos.Fill2D(string("loose_EMDetEta_ZMass_EM_Probe_Trk_Matched_")+bins_Vtx, emobj_probe->CalDetectorEta(), mass);
		  _histos.Fill2D(string("loose_EMEta_ZMass_EM_Probe_Trk_Matched_")+bins_Vtx, emobj_probe->Eta(), mass);
		  _histos.Fill2D("loose_ZMass_vs_DetEta_After_Trk_CC", emobj_probe->CalDetectorEta(), mass);
		  _histos.Fill2D("loose_ZMass_vs_Eta_After_Trk_CC", emobj_probe->Eta(), mass);
		  _histos.Fill2D("loose_ZMass_vs_Vtx_After_Trk_CC", v_z, mass);
		  _histos.Fill2D("loose_ZMass_vs_Pt_After__Trk_CC", mass, emobj_probe->Pt() );
		}

	      } //good spatial only matching	      

	    } // Z mass window
	  } // requirements on probe electrons
	} // requirements on tag electrons
      }
    }//iem
  }//lumicut
  }//getEventInfo  
}





//
// EM+Loose EM sample to study track matching efficiency 
//
void EffAnalysis::TrackMatchEff(cafe::Event& event) {

  int run=event.getGlobal()->runno();
  int evt=event.getGlobal()->evtno();

  if(_debugLevel>=30) cout<<"Track Matching Efficiency Study"<<endl;
  const TMBCellContainer *cells = event.get<TMBCellContainer>("CaloCells");

  double pT_low=0., pT_high=1000.;

  CAFMet met;
  CAFMet rawmet;
  double instlumi = 0.;
  int runNo, evtNo;

  vector<CAFEMObj*> emobjs;
  vector<CAFEMObj*> probeEMs;
  const CAFEMObj *emobj;
  const CAFEMObj *emobj_probe;
  vector<CAFEMObj*> emobjs_forSET;

  int triglist_flag = -1;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL3Ele*> l3cal_vec;
  int solpol = -999;
  float vtx_x, vtx_y, vtx_z;

  // get primary vertex
  float v_x, v_y, v_z;
  bool getPrimaryVertexX = event.get("Primary vertexZ", v_x);
  bool getPrimaryVertexY = event.get("Primary vertexZ", v_y);
  bool getPrimaryVertexZ = event.get("Primary vertexZ", v_z);

  // construct Z candidates
  float vtx[3] = {v_x, v_y, v_z};

  char bins_Vtx[10];
  int bin_Vtx_number;
  bin_Vtx_number=int((v_z+60.)/20.);
  sprintf(bins_Vtx, "%d", bin_Vtx_number);

  // get probe electrons
  bool getProbeElectrons = event.get("Probe EMObjs", probeEMs);

  //Reverse HMx7 to get background shape for CC
  cafe::Collection<TMBEMCluster> electrons = event.getEMscone();
  
  double zScalarEt = 0;
  double ScalarEt_Evt = 0;

  CAFZCand zcand;
  bool passcuts=false;
  if (event.get("Probe EMObjs", emobjs_forSET) && event.get("EMCorr Met", met) && 
      event.get("Raw Met", rawmet) &&
      event.get("L1CalTowers", l1cal_vec) && event.get("L2GblEMs", l2cal_vec) && 
      event.get("L3Eles", l3cal_vec) && event.get("triglist flag", triglist_flag) &&
      event.get("run number", runNo) && event.get("event number", evtNo) &&
      event.get("InstLumi", instlumi) && event.get("Best primary vertexX", vtx_x) && 
      event.get("Best primary vertexY", vtx_y) && event.get("Best primary vertexZ", vtx_z) &&
      event.get("solenoid polarity", solpol)) {

    if(emobjs_forSET.size() >= 2 && instlumi > _InstLumi_lowcut && instlumi < _InstLumi_highcut) passcuts=true;
  
    if(!passcuts) return;

    if(_dorawCellsRecoil) {
      if (_useConsistentMET) {
	zcand = CAFZCand(emobjs_forSET[0], emobjs_forSET[1], &rawmet, vtx, true);
      } else {
	zcand = CAFZCand(emobjs_forSET[0], emobjs_forSET[1], &met, vtx);
      }
    } else {
      zcand = CAFZCand(emobjs_forSET[0], emobjs_forSET[1], &met);
    }
    
  }

  if (_useConsistentMET) {
    TVector2 consistMET=zcand.GetConsistentMET();
    double dummySET=met.scalarEt();
    met.SetMet(consistMET.X(),consistMET.Y(),consistMET.Mod(),dummySET);
  }
  
  //  cout<<"OK"<<endl;
  // MOVED FROM LATER IN THE CODE /////////////////////////////////////////////////////////////
  // calculate scalarEt and remove contribution due to two electrons
  if (!_dorawCellsRecoil) {
    ScalarEt_Evt = met.scalarEt();
    double ScalarEt_EMObjs = emobjs_forSET[0]->EMScalarEt()*emobjs_forSET[0]->E()/emobjs_forSET[0]->uncorrE() +
      emobjs_forSET[1]->EMScalarEt()*emobjs_forSET[1]->E()/emobjs_forSET[1]->uncorrE();
    zScalarEt = ScalarEt_Evt - ScalarEt_EMObjs;
  } else {
    ScalarEt_Evt = rawmet.scalarEt();
    float cntrib1=0;
    float cntrib2=0;
    emobjs_forSET[0]->getRawElecVectorFromCells(vtx,&cntrib1);
    emobjs_forSET[1]->getRawElecVectorFromCells(vtx,&cntrib2);
    double ScalarEt_EMObjs = cntrib1 + cntrib2;
    zScalarEt = ScalarEt_Evt - ScalarEt_EMObjs;
  }
  //

  double recoilPt = zcand.MagRecoil();
  if (recoilPt > _ZUtCut ) return;

  ///////////////////////////
  ////Get Background shape
  ///////////////////////////
  vector<CAFEMObj*> v_it_bkgd;
  for (int iprobe=0; iprobe<probeEMs.size(); iprobe++) {
    if(probeEMs[iprobe]->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial) && probeEMs[iprobe]->Pt()>25.&& probeEMs[iprobe]->PassEMFracIso(_EMFracCut, _IsoCut)) {
      if((fabs(probeEMs[iprobe]->CalDetectorEta())<1.05 && probeEMs[iprobe]->HMx7() > 30.) || (fabs(probeEMs[iprobe]->CalDetectorEta())>1.5 && fabs(probeEMs[iprobe]->CalDetectorEta())<2.3 && probeEMs[iprobe]->HMx8() > 30.)){ ////for CC or EC tag
	//if(probeEMs[iprobe]->IsCCFid(_DetEtaCC) && fabs(v_z)<60. && probeEMs[iprobe]->Pt()>25.) { ////for CC tag only
	  v_it_bkgd.push_back(probeEMs[iprobe]);
	}
	//      }
    } // electron quality cuts
  } // loop over all probe electrons  

  //  cout<<"v_it_bkgd.size()="<<v_it_bkgd.size()<<endl;
  if(v_it_bkgd.size() >= 2 && (fabs(v_it_bkgd[0]->CalDetectorEta())<1.05 || fabs(v_it_bkgd[1]->CalDetectorEta())<1.05)){ ////for CC or EC tag
    //if(v_it_bkgd.size() >= 2 && fabs(v_it_bkgd[0]->CalDetectorEta())<1.05 && fabs(v_it_bkgd[1]->CalDetectorEta())<1.05){ ////for CC tag only
    TLorentzVector v_bkgd1(v_it_bkgd[0]->Px(), v_it_bkgd[0]->Py(), v_it_bkgd[0]->Pz(), v_it_bkgd[0]->E());
    TLorentzVector v_bkgd2(v_it_bkgd[1]->Px(), v_it_bkgd[1]->Py(), v_it_bkgd[1]->Pz(), v_it_bkgd[1]->E());
    TLorentzVector v_Bkgd = v_bkgd1 + v_bkgd2;
    _histos.Fill2D(string("EMDetEta_Bkgd_")+bins_Vtx, v_it_bkgd[0]->CalDetectorEta(), v_Bkgd.M());
    _histos.Fill2D(string("EMDetEta_Bkgd_")+bins_Vtx, v_it_bkgd[1]->CalDetectorEta(), v_Bkgd.M());
    _histos.Fill2D(string("EMEta_Bkgd_")+bins_Vtx, v_it_bkgd[0]->Eta(), v_Bkgd.M());
    _histos.Fill2D(string("EMEta_Bkgd_")+bins_Vtx, v_it_bkgd[1]->Eta(), v_Bkgd.M());

    for(int i=0; i<2; i++){
      char bins_Eta[10];
      int bin_Eta_number;
      if(v_it_bkgd[i]->Eta()<-1.3)
        bin_Eta_number=0;
      else if(v_it_bkgd[i]->Eta()>1.3)
        bin_Eta_number=14;
      else
        bin_Eta_number=int((v_it_bkgd[i]->Eta()+1.3)/0.2)+1;
      sprintf(bins_Eta, "%d", bin_Eta_number);
      
      _histos.Fill2D("EMZMass_V_Pt_Bkgd_Etabin", v_it_bkgd[i]->Pt(), v_Bkgd.M());
      _histos.Fill2D(string("EMZMass_V_Pt_Bkgd_Etabin_")+bins_Eta, v_it_bkgd[i]->Pt(), v_Bkgd.M());
      _histos.Fill2D("EMZMass_V_Vtx_Bkgd_Etabin", v_z, v_Bkgd.M());
      _histos.Fill2D(string("EMZMass_V_Vtx_Bkgd_Etabin_")+bins_Eta, v_z, v_Bkgd.M());

      char bins_SET[10];
      int bin_SET_number;
      if(zScalarEt<30.)
	bin_SET_number=0;
      else if(zScalarEt<50.)
	bin_SET_number=1;
      else if(zScalarEt<80.)
        bin_SET_number=2;
      else if(zScalarEt<120.)
        bin_SET_number=3;
      else 
        bin_SET_number=4;
      sprintf(bins_SET, "%d", bin_SET_number);

      _histos.Fill2D("EMZMass_V_Pt_Bkgd_SETbin", v_it_bkgd[i]->Pt(), v_Bkgd.M());
      _histos.Fill2D(string("EMZMass_V_Pt_Bkgd_SETbin_")+bins_SET, v_it_bkgd[i]->Pt(), v_Bkgd.M());
    }
  }
  
  ///////////////////////////
  ////End: Background shape
  ///////////////////////////

  // make sure that we get pointers to each selector
  if(event.get("Good EMObjs", emobjs) && event.get("L1CalTowers", l1cal_vec) && event.get("L1Cal2bTowers", l1cal2b_vec) && 
     event.get("L2GblEMs", l2cal_vec) && event.get("L3Eles", l3cal_vec) &&
     event.get("triglist flag", triglist_flag)) {

    /////   Jun: use truth method
    Bool_t executeTruth=false;
    if (_truthMode==0) {
      executeTruth=(probeEMs.size() >= 2);
    } else if (_truthMode==1) {
      executeTruth=(probeEMs.size() >= 1);
    } else if (_truthMode==2) {
      executeTruth=((probeEMs.size()>=2)&&
		    (probeEMs[0]->IsCCFid(_DetEtaCC,_useTrackFiducial)&&(probeEMs[0]->Pt()>_ElecPtCut))&&
		    (probeEMs[1]->IsCCFid(_DetEtaCC,_useTrackFiducial)&&(probeEMs[1]->Pt()>_ElecPtCut)));
    }

    if (executeTruth) {

      //TVector2 pt_e0(probeEMs[0]->Px(),probeEMs[0]->Py());
      //TVector2 pt_e1(probeEMs[1]->Px(),probeEMs[1]->Py());
      //TVector2 pt_Z=pt_e0+pt_e1;

      for(int iprobe=0; iprobe<probeEMs.size(); ++iprobe){
	emobj_probe = probeEMs[iprobe];
	if(emobj_probe->IsEM() && emobj_probe->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial) &&
	   emobj_probe->Pt()>_ElecPtCut) {

	  // kinematical variables
	  float elec_deteta = emobj_probe->CalDetectorEta();
	  float elec_eta = emobj_probe->Eta();
	  float elec_pT = emobj_probe->Pt();
	  //float elec_pT = (emobj_probe->Pt())*80.419/91.188;

	  char bins_Eta[10];
	  int bin_Eta_number;
	  if(elec_eta<-1.3)
	    bin_Eta_number=0;
	  else if(elec_eta>1.3)
	    bin_Eta_number=14;
	  else
	    bin_Eta_number=int((elec_eta+1.3)/0.2)+1;
	  sprintf(bins_Eta, "%d", bin_Eta_number);

	  if(emobj_probe->IsCCFid(_DetEtaCC,_useTrackFiducial)){
	    _histos.Fill1D("EMPt_truth_CC", elec_pT);
	    _histos.Fill1D(string("EMPt_truth_CC_")+bins_Eta, elec_pT);
	    _histos.Fill1D("EMVtx_truth_CC", v_z);
	    _histos.Fill1D(string("EMVtx_truth_CC_")+bins_Eta, v_z);
	    if(emobj_probe->PassEMFracIso(_EMFracCut, _IsoCut)){
	      //if(emobj_probe->iso()<0.15){
	      _histos.Fill1D("EMPt_emfrac_iso_truth_CC", elec_pT);
	      _histos.Fill1D(string("EMPt_emfrac_iso_truth_CC_")+bins_Eta, elec_pT);
	      _histos.Fill1D("EMVtx_emfrac_iso_truth_CC", v_z);
	      _histos.Fill1D(string("EMVtx_emfrac_iso_truth_CC_")+bins_Eta, v_z);
	      if(emobj_probe->PassHMx(_HM7Cut, _HM8Cut)){
		_histos.Fill1D("EMPt_emfrac_iso_HMx7_truth_CC", elec_pT);
		_histos.Fill1D(string("EMPt_emfrac_iso_HMx7_truth_CC_")+bins_Eta, elec_pT);
		_histos.Fill1D("EMVtx_emfrac_iso_HMx7_truth_CC", v_z);
		_histos.Fill1D(string("EMVtx_emfrac_iso_HMx7_truth_CC_")+bins_Eta, v_z);
		if(emobj_probe->has_spatial_track_match() && emobj_probe->IsCCFid(_DetEtaCC,_useTrackFiducial) ){
		  _histos.Fill1D("EMPt_emfrac_iso_HMx7_spatial_truth_CC", elec_pT);
		  _histos.Fill1D(string("EMPt_emfrac_iso_HMx7_spatial_truth_CC_")+bins_Eta, elec_pT);
		  _histos.Fill1D("EMVtx_emfrac_iso_HMx7_spatial_truth_CC", v_z);
		  _histos.Fill1D(string("EMVtx_emfrac_iso_HMx7_spatial_truth_CC_")+bins_Eta, v_z);
		  const TMBTrack *tmp_track = emobj_probe->getPtrSpatialChp();
		  if(tmp_track!=NULL && tmp_track->nsmt()>0){
		    _histos.Fill1D("EMPt_emfrac_iso_HMx7_spatial_smt_truth_CC", elec_pT);
		    _histos.Fill1D(string("EMPt_emfrac_iso_HMx7_spatial_smt_truth_CC_")+bins_Eta, elec_pT);
		    _histos.Fill1D("EMVtx_emfrac_iso_HMx7_spatial_smt_truth_CC", v_z);
		    _histos.Fill1D(string("EMVtx_emfrac_iso_HMx7_spatial_smt_truth_CC_")+bins_Eta, v_z);
		    if(tmp_track->Pt()>10.){
		      _histos.Fill1D("EMPt_emfrac_iso_HMx7_spatial_smt_trkpT_truth_CC", elec_pT);
		      _histos.Fill1D(string("EMPt_emfrac_iso_HMx7_spatial_smt_trkpT_truth_CC_")+bins_Eta, elec_pT);
		      _histos.Fill1D("EMVtx_emfrac_iso_HMx7_spatial_smt_trkpT_truth_CC", v_z);
		      _histos.Fill1D(string("EMVtx_emfrac_iso_HMx7_spatial_smt_trkpT_truth_CC_")+bins_Eta, v_z);

		    }
		  }
		}
	      }
	    }
	  }

	}

      }
    }
    /////end truth method

    for(int iem=0; iem<emobjs.size(); ++iem){
      emobj = emobjs[iem];

      // the tag electron must pass trigger requirements
      // for GEANT MC, we do not need to check trigger efficiency
      bool pass_trigger_tag = false;
      if(_MCStudy || _DropTriggerObjectMatchRequirement) pass_trigger_tag = true;
      else pass_trigger_tag = emobj->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec);

      if(_TPtrk_TrigMatchOnTag_not_on_EitherObject && !pass_trigger_tag && !_DropTriggerObjectMatchRequirement) continue;
 
      // if tag electron and probe electron are the same, zcand mass will be very small
      // and will be removed by z mass window requirment
      for(int iprobe=0; iprobe<probeEMs.size(); ++iprobe){
        emobj_probe = probeEMs[iprobe];

      bool pass_trigger_probe = false;
      if(_MCStudy) pass_trigger_probe = true;
      else pass_trigger_probe = emobj_probe->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec);

      if(!_TPtrk_TrigMatchOnTag_not_on_EitherObject && !pass_trigger_tag && !pass_trigger_probe && !_DropTriggerObjectMatchRequirement) continue;
	  	
	// require tag electron in CC region (!?!)
	// need to make sure that the probe em object already
	// passes id, emfrac, isolation and hmx cuts
	if(emobj->has_good_spatial_track_match() && /*!!! this is the cut to vary !!!*/
	   (((!_TPtrk_IncludeECtag)&&emobj->IsCCFid(_DetEtaCC,_useTrackFiducial))||(_TPtrk_IncludeECtag&&emobj->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial)))) {
	  if(emobj_probe->IsEM() && 
	     (_TPtrk_DoTheStepByStepThing||(emobj_probe->PassEMFracIso(_EMFracCut, _IsoCut)&&emobj_probe->PassHMx(_HM7Cut, _HM8Cut))) && 
	     emobj_probe->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial) && 
             emobj_probe->Pt()>_ElecPtCut && emobj_probe->has_spatial_track_match(-0.5)) {
	
	    CAFZCand zcand(emobj, emobj_probe);    
	    if(zcand.In_ZPeak(_ZMassCut1, _ZMassCut2)) {

	      // probe electron type, 0 for CC, 1 for EC
	      int type = -1;
	      if(emobj_probe->IsCCFid(_DetEtaCC,_useTrackFiducial)) type = 0;
	      else type = 1;
	      char elec_type[10];  sprintf(elec_type, "%d", type);

	      // kinematical variables
	      float elec_deteta = emobj_probe->CalDetectorEta();
	      float elec_eta = emobj_probe->Eta();
	      float elec_pT = emobj_probe->Pt();
              double mass = zcand.Mass();

	      double pT_true;
              double event_vertex=v_z;

              char bins_Eta[10];
              int bin_Eta_number;
              if(elec_eta<-1.3)
                bin_Eta_number=0;
              else if(elec_eta>1.3)
                bin_Eta_number=14;
              else
                bin_Eta_number=int((elec_eta+1.3)/0.2)+1;
              sprintf(bins_Eta, "%d", bin_Eta_number);

	      //add plots step by step
              if(type==0){
                //if(type==0 || type==1){
		//              if(elec_pT>20.){
                _histos.Fill1D("EMPt_CC", elec_pT);
                _histos.Fill1D(string("EMPt_CC_")+bins_Eta, elec_pT);
                _histos.Fill1D("EMPt_MC_CC", pT_true);
                _histos.Fill1D(string("EMPt_MC_CC_")+bins_Eta, pT_true);
                if(emobj->Pt()<emobj_probe->Pt()){
                  _histos.Fill1D("EMPt_first_CC", elec_pT);
                  _histos.Fill1D(string("EMPt_first_CC_")+bins_Eta, elec_pT);
                }
                else {
                  _histos.Fill1D("EMPt_second_CC", elec_pT);
                  _histos.Fill1D(string("EMPt_second_CC_")+bins_Eta, elec_pT);
                }
                if(emobj_probe->Pt()>pT_low && emobj_probe->Pt()<pT_high){
		  _histos.Fill1D("EMVtx_CC", event_vertex);
		  _histos.Fill1D(string("EMVtx_CC_")+bins_Eta, event_vertex);
		  _histos.Fill1D("EMEta_CC", elec_eta);
		  _histos.Fill1D(string("EMEta_CC_")+bins_Eta, elec_eta);
		  _histos.Fill1D("EMDetEta_CC", elec_deteta);
		  _histos.Fill1D(string("EMDetEta_CC_")+bins_Eta, elec_deteta);
		  _histos.Fill2D("EMPt_vs_DetEta_tagprobe", elec_deteta, elec_pT);
		  _histos.Fill2D(string("EMPt_vs_DetEta_tagprobe_")+bins_Eta, elec_deteta, elec_pT);
                }
                if(emobj_probe->PassEMFracIso(_EMFracCut, _IsoCut)){
                  _histos.Fill1D("EMPt_emfrac_iso_CC", elec_pT);
                  _histos.Fill1D(string("EMPt_emfrac_iso_CC_")+bins_Eta, elec_pT);
                  _histos.Fill1D("EMPt_MC_emfrac_iso_CC", pT_true);
                  _histos.Fill1D(string("EMPt_MC_emfrac_iso_CC_")+bins_Eta, pT_true);
                  if(emobj->Pt()<emobj_probe->Pt()){
                    _histos.Fill1D("EMPt_first_emfrac_iso_CC", elec_pT);
                    _histos.Fill1D(string("EMPt_first_emfrac_iso_CC_")+bins_Eta, elec_pT);
                  }
                  else {
                    _histos.Fill1D("EMPt_second_emfrac_iso_CC", elec_pT);
                    _histos.Fill1D(string("EMPt_second_emfrac_iso_CC_")+bins_Eta, elec_pT);
                  }
                  if(emobj_probe->Pt()>pT_low && emobj_probe->Pt()<pT_high){
		    _histos.Fill1D("EMVtx_emfrac_iso_CC", event_vertex);
		    _histos.Fill1D(string("EMVtx_emfrac_iso_CC_")+bins_Eta, event_vertex);
		    _histos.Fill1D("EMEta_emfrac_iso_CC", elec_eta);
		    _histos.Fill1D(string("EMEta_emfrac_iso_CC_")+bins_Eta, elec_eta);
		    _histos.Fill1D("EMDetEta_emfrac_iso_CC", elec_deteta);
		    _histos.Fill1D(string("EMDetEta_emfrac_iso_CC_")+bins_Eta, elec_deteta);
		    _histos.Fill2D("EMPt_vs_DetEta_emfrac_iso_tagprobe", elec_deteta, elec_pT);
		    _histos.Fill2D(string("EMPt_vs_DetEta_emfrac_iso_tagprobe_")+bins_Eta, elec_deteta, elec_pT);
                  }
                  //            if(emobj_probe->PassHMx(_HM7Cut, _HM8Cut)){
                  if(emobj_probe->PassHMx(_HM7Cut, _HM8Cut)){
                    _histos.Fill1D("EMPt_emfrac_iso_HMx7_CC", elec_pT);
                    _histos.Fill1D(string("EMPt_emfrac_iso_HMx7_CC_")+bins_Eta, elec_pT);
                    _histos.Fill1D("EMPt_MC_emfrac_iso_HMx7_CC", pT_true);
                    _histos.Fill1D(string("EMPt_MC_emfrac_iso_HMx7_CC_")+bins_Eta, pT_true);
                    if(emobj->Pt()<emobj_probe->Pt()){
                      _histos.Fill1D("EMPt_first_emfrac_iso_HMx7_CC", elec_pT);
                      _histos.Fill1D(string("EMPt_first_emfrac_iso_HMx7_CC_")+bins_Eta, elec_pT);
                    }
                    else {
                      _histos.Fill1D("EMPt_second_emfrac_iso_HMx7_CC", elec_pT);
                      _histos.Fill1D(string("EMPt_second_emfrac_iso_HMx7_CC_")+bins_Eta, elec_pT);
                    }
                    if(emobj_probe->Pt()>pT_low && emobj_probe->Pt()<pT_high){
		      _histos.Fill1D("EMVtx_emfrac_iso_HMx7_CC", event_vertex);
		      _histos.Fill1D(string("EMVtx_emfrac_iso_HMx7_CC_")+bins_Eta, event_vertex);
		      _histos.Fill1D("EMEta_emfrac_iso_HMx7_CC", elec_eta);
		      _histos.Fill1D(string("EMEta_emfrac_iso_HMx7_CC_")+bins_Eta, elec_eta);
		      _histos.Fill1D("EMDetEta_emfrac_iso_HMx7_CC", elec_deteta);
		      _histos.Fill1D(string("EMDetEta_emfrac_iso_HMx7_CC_")+bins_Eta, elec_deteta);
		      _histos.Fill2D("EMPt_vs_DetEta_emfrac_iso_Hmx7_tagprobe", elec_deteta, elec_pT);
		      _histos.Fill2D(string("EMPt_vs_DetEta_emfrac_iso_Hmx7_tagprobe_")+bins_Eta, elec_deteta, elec_pT);
                    }
                    if(emobj_probe->has_spatial_track_match()&& emobj_probe->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial)){
                      _histos.Fill1D("EMPt_emfrac_iso_HMx7_spatial_CC", elec_pT);
                      _histos.Fill1D(string("EMPt_emfrac_iso_HMx7_spatial_CC_")+bins_Eta, elec_pT);
                      _histos.Fill1D("EMPt_MC_emfrac_iso_HMx7_spatial_CC", pT_true);
                      _histos.Fill1D(string("EMPt_MC_emfrac_iso_HMx7_spatial_CC_")+bins_Eta, pT_true);
		     

		      if(emobj->Pt()<emobj_probe->Pt()){
			_histos.Fill1D("EMPt_first_emfrac_iso_HMx7_spatial_CC", elec_pT);
			_histos.Fill1D(string("EMPt_first_emfrac_iso_HMx7_spatial_CC_")+bins_Eta, elec_pT);
		      }
		      else {
			_histos.Fill1D("EMPt_second_emfrac_iso_HMx7_spatial_CC", elec_pT);
			_histos.Fill1D(string("EMPt_second_emfrac_iso_HMx7_spatial_CC_")+bins_Eta, elec_pT);
		      }
		      if(emobj_probe->Pt()>pT_low && emobj_probe->Pt()<pT_high){
			_histos.Fill1D("EMVtx_emfrac_iso_HMx7_spatial_CC", event_vertex);
			_histos.Fill1D(string("EMVtx_emfrac_iso_HMx7_spatial_CC_")+bins_Eta, event_vertex);
			_histos.Fill1D("EMEta_emfrac_iso_HMx7_spatial_CC", elec_eta);
			_histos.Fill1D(string("EMEta_emfrac_iso_HMx7_spatial_CC_")+bins_Eta, elec_eta);
			_histos.Fill1D("EMDetEta_emfrac_iso_HMx7_spatial_CC", elec_deteta);
			_histos.Fill1D(string("EMDetEta_emfrac_iso_HMx7_spatial_CC_")+bins_Eta, elec_deteta);
			_histos.Fill2D("EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_tagprobe", elec_deteta, elec_pT);
			_histos.Fill2D(string("EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_tagprobe_")+bins_Eta, elec_deteta, elec_pT);
		      }
		      const TMBTrack *tmp_track = emobj_probe->getPtrSpatialChp();
		      if(tmp_track!=NULL && tmp_track->nsmt()>0){
			_histos.Fill1D("EMPt_emfrac_iso_HMx7_spatial_smt_CC", elec_pT);
			_histos.Fill1D(string("EMPt_emfrac_iso_HMx7_spatial_smt_CC_")+bins_Eta, elec_pT);
			_histos.Fill1D("EMPt_MC_emfrac_iso_HMx7_spatial_smt_CC", pT_true);
			_histos.Fill1D(string("EMPt_MC_emfrac_iso_HMx7_spatial_smt_CC_")+bins_Eta, pT_true);
			if(emobj->Pt()<emobj_probe->Pt()){
			  _histos.Fill1D("EMPt_first_emfrac_iso_HMx7_spatial_smt_CC", elec_pT);
			  _histos.Fill1D(string("EMPt_first_emfrac_iso_HMx7_spatial_smt_CC_")+bins_Eta, elec_pT);
			}
			else {
			  _histos.Fill1D("EMPt_second_emfrac_iso_HMx7_spatial_smt_CC", elec_pT);
			  _histos.Fill1D(string("EMPt_second_emfrac_iso_HMx7_spatial_smt_CC_")+bins_Eta, elec_pT);
			}
			if(emobj_probe->Pt()>pT_low && emobj_probe->Pt()<pT_high){
			  _histos.Fill1D("EMVtx_emfrac_iso_HMx7_spatial_smt_CC", event_vertex);
			  _histos.Fill1D(string("EMVtx_emfrac_iso_HMx7_spatial_smt_CC_")+bins_Eta, event_vertex);
			  _histos.Fill1D("EMEta_emfrac_iso_HMx7_spatial_smt_CC", elec_eta);
			  _histos.Fill1D(string("EMEta_emfrac_iso_HMx7_spatial_smt_CC_")+bins_Eta, elec_eta);
			  _histos.Fill1D("EMDetEta_emfrac_iso_HMx7_spatial_smt_CC", elec_deteta);
			  _histos.Fill1D(string("EMDetEta_emfrac_iso_HMx7_spatial_smt_CC_")+bins_Eta, elec_deteta);
			  _histos.Fill2D("EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_smt_tagprobe", elec_deteta, elec_pT);
			  _histos.Fill2D(string("EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_smt_tagprobe_")+bins_Eta, elec_deteta, elec_pT);
			}
			if(tmp_track->Pt()>10.){
			  _histos.Fill1D("EMPt_emfrac_iso_HMx7_spatial_smt_trkpT_CC", elec_pT);
			  _histos.Fill1D(string("EMPt_emfrac_iso_HMx7_spatial_smt_trkpT_CC_")+bins_Eta, elec_pT);
			  _histos.Fill1D("EMPt_MC_emfrac_iso_HMx7_spatial_smt_trkpT_CC", pT_true);
			  _histos.Fill1D(string("EMPt_MC_emfrac_iso_HMx7_spatial_smt_trkpT_CC_")+bins_Eta, pT_true);
			  if(emobj->Pt()<emobj_probe->Pt()){
			    _histos.Fill1D("EMPt_first_emfrac_iso_HMx7_spatial_smt_trkpT_CC", elec_pT);
			    _histos.Fill1D(string("EMPt_first_emfrac_iso_HMx7_spatial_smt_trkpT_CC_")+bins_Eta, elec_pT);
			  }
			  else {
			    _histos.Fill1D("EMPt_second_emfrac_iso_HMx7_spatial_smt_trkpT_CC", elec_pT);
			    _histos.Fill1D(string("EMPt_second_emfrac_iso_HMx7_spatial_smt_trkpT_CC_")+bins_Eta, elec_pT);
			  }
			  if(emobj_probe->Pt()>pT_low && emobj_probe->Pt()<pT_high){
			    _histos.Fill1D("EMVtx_emfrac_iso_HMx7_spatial_smt_trkpT_CC", event_vertex);
			    _histos.Fill1D(string("EMVtx_emfrac_iso_HMx7_spatial_smt_trkpT_CC_")+bins_Eta, event_vertex);
			    _histos.Fill1D("EMEta_emfrac_iso_HMx7_spatial_smt_trkpT_CC", elec_eta);
			    _histos.Fill1D(string("EMEta_emfrac_iso_HMx7_spatial_smt_trkpT_CC_")+bins_Eta, elec_eta);
			    _histos.Fill1D("EMDetEta_emfrac_iso_HMx7_spatial_smt_trkpT_CC", elec_deteta);
			    _histos.Fill1D(string("EMDetEta_emfrac_iso_HMx7_spatial_smt_trkpT_CC_")+bins_Eta, elec_deteta);
			    _histos.Fill2D("EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_smt_trkpT_tagprobe", elec_deteta, elec_pT);
			    _histos.Fill2D(string("EMPt_vs_DetEta_emfrac_iso_Hmx7_spatial_smt_trkpT_tagprobe_")+bins_Eta, elec_deteta, elec_pT);
			  }
			}
		      }
		    }
		  }
                }
              }
	      // Jun is done
	    
	      
	    
	      _histos.Fill1D("EMDetEta_EM_Probe_Trk_trkfid_All", elec_deteta);
	      
	      _histos.Fill1D("EMDetEta_EM_Probe_Trk_All", elec_deteta);
	      _histos.Fill1D(string("EMEta_EM_Probe_Trk_")+elec_type, elec_eta);
	      _histos.Fill1D(string("EMPt_EM_Probe_Trk_")+elec_type, elec_pT);

	      // for different primary vertex region
	      int vtx_region = -1;
              if(v_z<-50.) vtx_region = 0;
	      //else if (v_z<-45.) vtx_region = 1;
              else if (v_z<-43.) vtx_region = 1;
              else if (v_z<-37.) vtx_region = 2;
	      else if (v_z<-30.) vtx_region = 3;
	      else if (v_z<-20.) vtx_region = 4;
              else if (v_z<-10.) vtx_region = 5;
              else if (v_z<0.) vtx_region = 6;
              else if (v_z<10.) vtx_region =7;
	      else if (v_z<20.) vtx_region = 8;
              else if (v_z<30.) vtx_region = 9;
	      else if (v_z<37.) vtx_region = 10;
	      else if (v_z<43.) vtx_region = 11;
	      //else if (v_z<40.) vtx_region = 13;
              else if (v_z<50.) vtx_region = 12;
	      else vtx_region = 13;
	      char vtx_region_char[10];  sprintf(vtx_region_char, "%d", vtx_region);

	      _histos.Fill1D(string("EMDetEta_EM_Probe_Trk_All_Vtx_")+vtx_region_char, elec_deteta);
	      _histos.Fill1D(string("EMEta_EM_Probe_Trk_All_Vtx_")+vtx_region_char, elec_eta);
	      if(type==0) _histos.Fill1D(string("EMPt_EM_Probe_Trk_All_CC_Vtx_")+vtx_region_char, elec_pT);
	      if(type==1) _histos.Fill1D(string("EMPt_EM_Probe_Trk_All_EC_Vtx_")+vtx_region_char, elec_pT);

              // fill invariant mass distribution for different eta region: 31 regions from -3.0 to 3.0
	      double peta =  elec_eta;
	      int eta_region = -1;
	      if (-3.1<=peta && peta<-2.9) {eta_region = 0;}
	      else if (-2.9<=peta && peta<-2.7) {eta_region = 1;}
	      else if (-2.7<=peta && peta<-2.5) {eta_region = 2;}
	      else if (-2.5<=peta && peta<-2.3) {eta_region = 3;}
	      else if (-2.3<=peta && peta<-2.1) {eta_region = 4;}
	      else if (-2.1<=peta && peta<-1.9) {eta_region = 5;}
	      else if (-1.9<=peta && peta<-1.7) {eta_region = 6;}
	      else if (-1.7<=peta && peta<-1.5) {eta_region = 7;}
	      else if (-1.5<=peta && peta<-1.3) {eta_region = 8;}
	      else if (-1.3<=peta && peta<-1.1) {eta_region = 9;}
	      else if (-1.1<=peta && peta<-0.9) {eta_region = 10;}
	      else if (-0.9<=peta && peta<-0.7) {eta_region = 11;}
	      else if (-0.7<=peta && peta<-0.5) {eta_region = 12;}
	      else if (-0.5<=peta && peta<-0.3) {eta_region = 13;}
	      else if (-0.3<=peta && peta<-0.1) {eta_region = 14;}
	      else if (-0.1<=peta && peta<0.1) {eta_region = 15;}
	      else if (0.1<=peta && peta<0.3) {eta_region = 16;}
	      else if (0.3<=peta && peta<0.5) {eta_region = 17;}
	      else if (0.5<=peta && peta<0.7) {eta_region = 18;}
	      else if (0.7<=peta && peta<0.9) {eta_region = 19;}
	      else if (0.9<=peta && peta<1.1) {eta_region = 20;}
	      else if (1.1<=peta && peta<1.3) {eta_region = 21;}
	      else if (1.3<=peta && peta<1.5) {eta_region = 22;}
	      else if (1.5<=peta && peta<1.7) {eta_region = 23;}
	      else if (1.7<=peta && peta<1.9) {eta_region = 24;}
	      else if (1.9<=peta && peta<2.1) {eta_region = 25;}
	      else if (2.1<=peta && peta<2.3) {eta_region = 26;}
	      else if (2.3<=peta && peta<2.5) {eta_region = 27;}
	      else if (2.5<=peta && peta<2.7) {eta_region = 28;}
	      else if (2.7<=peta && peta<2.9) {eta_region = 29;}
	      else if (2.9<=peta && peta<3.1) {eta_region = 30;}
	      char eta_region_char[10];  sprintf(eta_region_char, "%d", eta_region);

              // later we need to subtract background
	      if (type == 0) {//was cccc event, so cc probe
		_histos.Fill1D(string("ZMass_vs_Eta_Before_Trk_Vtx_CC_")+vtx_region_char+string("_")+eta_region_char, mass);
		if(emobj_probe->has_good_spatial_track_match()) {
		  _histos.Fill1D(string("ZMass_vs_Eta_After_Trk_Vtx_CC_")+vtx_region_char+string("_")+eta_region_char, mass);
		}
		if(emobj_probe->has_spatial_track_match(-0.5)) {
		  _histos.Fill1D(string("ZMass_vs_Eta_After_Trk_Spatial_Only_Vtx_CC_")+vtx_region_char+string("_")+eta_region_char, mass);
		}
		if(emobj_probe->has_good_spatial_track_match(0.01,kFALSE,0.)){
		  _histos.Fill1D(string("ZMass_vs_Eta_After_Trk_gSpatial_Vtx_CC_")+vtx_region_char+string("_")+eta_region_char, mass);
		}
		if(emobj_probe->has_good_spatial_track_match(0.01,kTRUE,0.)){
		  _histos.Fill1D(string("ZMass_vs_Eta_After_Trk_gSpatial_smt_Vtx_CC_")+vtx_region_char+string("_")+eta_region_char, mass);
		}
		  
		  
	      }else if (type == 1){ //was ccec, so probe was ec
		_histos.Fill1D(string("ZMass_vs_Eta_Before_Trk_Vtx_EC_")+vtx_region_char+string("_")+eta_region_char, mass);
		if(emobj_probe->has_good_spatial_track_match()) {
		  _histos.Fill1D(string("ZMass_vs_Eta_After_Trk_Vtx_EC_")+vtx_region_char+string("_")+eta_region_char, mass);
		}
	      }
	    
	    
	      if(type==1){  // for EC 
		_histos.Fill2D(string("EMEta_EM_Probe_Trk_All_Vtx_Eta_EC"),v_z,elec_eta);
		_histos.Fill2D(string("EMDetEta_EM_Probe_Trk_All_Vtx_DetEta_EC"),v_z,elec_deteta);
	      }
	      
	      if(type==0){ 
		_histos.Fill2D(string("EMEta_EM_Probe_Trk_All_Vtx_Eta_CC"),v_z,elec_eta);
		_histos.Fill2D(string("EMDetEta_EM_Probe_Trk_All_Vtx_DetEta_CC"),v_z,elec_deteta);
		_histos.Fill2D(string("EMDetEta_ZMass_EM_Probe_Trk_All_")+bins_Vtx, emobj_probe->CalDetectorEta(), mass);
		_histos.Fill2D(string("EMEta_ZMass_EM_Probe_Trk_All_")+bins_Vtx, emobj_probe->Eta(), mass);
		_histos.Fill2D("ZMass_vs_DetEta_Before_Trk_CC", emobj_probe->CalDetectorEta(), mass);
		_histos.Fill2D("ZMass_vs_Eta_Before_Trk_CC", emobj_probe->Eta(), mass);
		_histos.Fill2D("ZMass_vs_Vtx_Before_Trk_CC", v_z, mass);
		_histos.Fill2D("ZMass_vs_Pt_Before_Trk_CC", emobj_probe->Pt(), mass);
		_histos.Fill2D("ZMass_vs_DetEta_Before_Trk_TAG", emobj->CalDetectorEta(), mass);
		_histos.Fill2D("ZMass_vs_Eta_Before_Trk_TAG", emobj->Eta(), mass);
		_histos.Fill2D("ZMass_vs_Pt_Before_Trk_TAG", emobj->Pt(), mass);


	      }
	      if(emobj_probe->has_track_match()) {
		_histos.Fill1D("EMDetEta_EM_Probe_Trk_Matched_All", elec_deteta);
		if (emobj_probe->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial)){
		  _histos.Fill1D("EMDetEta_EM_Probe_Trk_Matched_trkfid_All", elec_deteta);
		  if  (((!_TPtrk_IncludeECtag)&&emobj->IsCCFid(_DetEtaCC,_useTrackFiducial))||(_TPtrk_IncludeECtag&&emobj->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial))) {
		    _histos.Fill1D("EMDetEta_EM_Probe_Trk_Matched_trkfid_All2", elec_deteta);
		  }
		}
		_histos.Fill1D(string("EMEta_EM_Probe_Trk_Matched_")+elec_type, elec_eta);
		_histos.Fill1D(string("EMPt_EM_Probe_Trk_Matched_")+elec_type, elec_pT);
	      } //spatial+E/p matching
              
	      
	    if(emobj_probe->has_good_spatial_track_match()) {

		_histos.Fill1D("EMDetEta_EM_Probe_Spatial_Trk_Matched_All", elec_deteta);
		_histos.Fill1D(string("EMEta_EM_Probe_Spatial_Trk_Matched_")+elec_type, elec_eta);
		_histos.Fill1D(string("EMPt_EM_Probe_Spatial_Trk_Matched_")+elec_type, elec_pT);
		_histos.Fill1D(string("EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx_")+vtx_region_char, elec_deteta);
		_histos.Fill1D(string("EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_")+vtx_region_char, elec_eta);
		if(type==0) _histos.Fill1D(string("EMPt_EM_Probe_Spatial_Trk_Matched_CC_Vtx_")+vtx_region_char, elec_pT);
		if(type==1) _histos.Fill1D(string("EMPt_EM_Probe_Spatial_Trk_Matched_EC_Vtx_")+vtx_region_char, elec_pT);
		
		if (emobj_probe->IsCCECFid(_DetEtaCC, _DetEtaEC1, _DetEtaEC2,_useTrackFiducial)){
		  _histos.Fill1D("EMDetEta_EM_Probe_Spatial_Trk_Matched_trkfid_All", elec_deteta);
		}

		if(type==1){   // for EC
		  _histos.Fill2D(string("EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_Eta_EC"), v_z, elec_eta);
		  _histos.Fill2D(string("EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx_DetEta_EC"), v_z, elec_deteta);
		}

		if(type==0){

		  _histos.Fill2D(string("EMEta_EM_Probe_Spatial_Trk_Matched_Vtx_Eta_CC"), v_z, elec_eta);
		  _histos.Fill2D(string("EMDetEta_EM_Probe_Spatial_Trk_Matched_Vtx_DetEta_CC"), v_z, elec_deteta);
		  _histos.Fill2D(string("EMDetEta_ZMass_EM_Probe_Trk_Matched_")+bins_Vtx, emobj_probe->CalDetectorEta(), mass);
		  _histos.Fill2D(string("EMEta_ZMass_EM_Probe_Trk_Matched_")+bins_Vtx, emobj_probe->Eta(), mass);
		  _histos.Fill2D("ZMass_vs_DetEta_After_Trk_CC", emobj_probe->CalDetectorEta(), mass);
		  _histos.Fill2D("ZMass_vs_Eta_After_Trk_CC", emobj_probe->Eta(), mass);
		  _histos.Fill2D("ZMass_vs_Vtx_After_Trk_CC", v_z, mass);
		  _histos.Fill2D("ZMass_vs_Pt_After_Trk_CC", emobj_probe->Pt(), mass);
		}
		
	      } //good spatial only matching	      

	    } // Z mass window
	  } // requirements on probe electrons
	} // requirements on tag electrons
      }
    }//iem


  }//getEventInfo 

}

// Trigger efficiency
//
void EffAnalysis::LumiEff(cafe::Event& event) {

  if(_debugLevel>=30) cout<<"Trigger Efficiency Study"<<endl; 
  
  double instlumi=0.;
  int triglist_flag = -1;
  vector<const TMBL1CalTower*> l1cal_vec;
  vector<const TMBL2GblEM*> l2cal_vec;
  vector<const TMBL1Cal2bEM*> l1cal2b_vec;
  vector<const TMBL3Ele*> l3cal_vec;
  
  vector<CAFEMObj*> emobjs;
  const CAFEMObj *emobj;
  const CAFEMObj *emobj_probe;
  TriggerManager *trigmanager = TriggerManager::get_instance();
  trigmanager->SetTrigs(event);

  if  (event.get("InstLumi", instlumi) && event.get("triglist flag", triglist_flag) ) {
    
    _histos.Fill1D("InstLumi_bare", instlumi);
    bool _uses25=false;
    bool _uses27=false;
    for(int itrig=0; itrig<_trignames[triglist_flag].size(); itrig++) {
      // get each trigger name		  
      string trigname =_trignames[triglist_flag][itrig];
      if (!(trigmanager->Uses_Trig(trigname.substr(0,8).c_str()))) continue;
      if (strncmp(trigname.c_str(),string("E1_SHT25").c_str(),8)==0){
	_uses25 = true;
      }
      if (strncmp(trigname.c_str(),string("E1_SHT27").c_str(),8)==0){
	_uses27 = true;
      }	
    }
    char sn[10];
    if (_uses25 && !_uses27)
      sprintf(sn,"_0");
      _histos.Fill1D("InstLumi_bare", instlumi);
    if (!_uses25 && _uses27)
      sprintf(sn,"_1");
    if (_uses25 && _uses27)
      sprintf(sn,"_2");
    
    _histos.Fill1D(TString("InstLumi_bare")+sn, instlumi);
    _histos.Fill1D(TString("InstLumi_bare").Data(), instlumi);

    float v_z;
    bool getPrimaryVertex = event.get("Primary vertexZ", v_z);
    if (abs(v_z) < 40.){
      _histos.Fill1D(TString("InstLumi_vtx")+sn, instlumi);
      _histos.Fill1D(TString("InstLumi_vtx").Data(), instlumi);
    int n20 =0;
    int n25 =0;
    int npreseltrk =0;
    int nemiso =0;
    int netafid =0;
    int ntrkfid =0;
    int nhmx =0;
    int ntrig = 0;
    int nCC = 0;
    int nmatch=0;
    
    cafe::Collection<TMBEMCluster> em = event.getEMscone();
    for (Collection<TMBEMCluster>::iterator it = em.begin(); it!= em.end(); ++it) { 
      if ((abs((*it).id())==11  || (abs((*it).id())==10))      && ((*it).Pt()>20.) ) {
	++n20;
	if (((*it).Pt()>25.))
	  ++n25;
	CAFEMObj *emobjptr = new CAFEMObj(&(*it)) ;
	if ((*it).has_spatial_track_match(-0.5)){
	  ++npreseltrk;
	  if( (*it).emfrac()>_EMFracCut && (*it).iso()<_IsoCut ) {
	    ++nemiso;
	    if ( (*it).is_in_eta_fiducial()){
	      ++netafid;
	      if (TrackPhiFiducial(emobjptr, event)){
		++ntrkfid;
		if(((fabs((*it).CalDetectorEta())<_DetEtaCC && (*it).HMx7()<_HM7Cut) || 
		    ((fabs((*it).CalDetectorEta())<_DetEtaEC2 && fabs((*it).CalDetectorEta())>_DetEtaEC1 && (*it).HMx8()<_HM8Cut) )) ){
		  ++nhmx;
		}
	
		if(event.get("Good EMObjs", emobjs) && 
		   event.get("L1CalTowers", l1cal_vec) && 
		   event.get("L1Cal2bTowers", l1cal2b_vec) && 
		   event.get("L3Eles", l3cal_vec) &&
		   event.get("L2GblEMs", l2cal_vec) && 
		   (_DropTriggerObjectMatchRequirement || emobjptr->PassTrigCMB(triglist_flag, 0.4, l1cal_vec, l1cal2b_vec, l2cal_vec, l3cal_vec))){
		  ++ntrig;
		  if ((fabs((*it).CalDetectorEta())<_DetEtaCC))
		  ++nCC;
		  if (emobjptr->has_good_spatial_track_match()){
		   ++nmatch;
		  }
		}
	      }
	    }
	  }
	} 
      }
    }
    if (n20 >1){
      _histos.Fill1D(TString("InstLumi_2EM_20")+sn, instlumi);
      _histos.Fill1D(TString("InstLumi_2EM_20").Data(), instlumi);
      if (n25 > 1){
	_histos.Fill1D(TString("InstLumi_2EM_25")+sn, instlumi);
	_histos.Fill1D(TString("InstLumi_2EM_25").Data(), instlumi);
	if (npreseltrk >1){
	  _histos.Fill1D(TString("InstLumi_preseltrk")+sn, instlumi);
	  _histos.Fill1D(TString("InstLumi_preseltrk").Data(), instlumi);
	  if (nemiso > 1){
	    _histos.Fill1D(TString("InstLumi_emiso")+sn, instlumi);
	    _histos.Fill1D(TString("InstLumi_emiso").Data(), instlumi);
	    if (netafid >1){
	      _histos.Fill1D(TString("InstLumi_etafid")+sn, instlumi);
	      _histos.Fill1D(TString("InstLumi_etafid").Data(), instlumi);
	      if (ntrkfid >1){
		_histos.Fill1D(TString("InstLumi_trkfid")+sn, instlumi);
		_histos.Fill1D(TString("InstLumi_trkfid").Data(), instlumi);
		if (nhmx >1){
		  _histos.Fill1D(TString("InstLumi_hmx")+sn, instlumi);
		  _histos.Fill1D(TString("InstLumi_hmx").Data(), instlumi);
		  if (ntrig > -1){
		    _histos.Fill1D(TString("InstLumi_trig")+sn, instlumi);
		    _histos.Fill1D(TString("InstLumi_trig").Data(), instlumi);
		    if (nCC > 1){
		      _histos.Fill1D(TString("InstLumi_CCCC")+sn, instlumi);
		      _histos.Fill1D(TString("InstLumi_CCCC").Data(), instlumi);
		      
		      if (nmatch >1){
			_histos.Fill1D(TString("InstLumi_trk")+sn, instlumi);
			_histos.Fill1D(TString("InstLumi_trk").Data(), instlumi);
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    }
  }
  
}



void EffAnalysis::begin() {}

void EffAnalysis::finish() {

  TFile *file = histfiles::initializeTFile( this );
  if(file==NULL) return;
  _tree3->Write();
  string directory_name("Eff_Hist");
  file->mkdir(directory_name.c_str());
  _histos.save(file, directory_name);
  file->Close();
}


bool TrackPhiFiducial(CAFEMObj* emobj, cafe::Event& event){
// this function needs to be the same as
// bool EMSelector::TrackPhiFiducial(CAFEMObj* emobj, cafe::Event& event)
// for consistent behaviour between EffAnalysis and Z/WAnalysis
   Config config("myname");
   bool _MCStudy = false;
  EMClusterPosCorr *_emclusposcorr = new EMClusterPosCorr(config);
  int solpol = -999;  
  event.get("solenoid polarity", solpol);
  int polarity = 2*solpol - 1;
  double phi = emobj->trkPhiEM3(_emclusposcorr, polarity, -0.5,_MCStudy );
  emobj->SetTrkPhiEM3(phi);
  bool outside_phi_crack=true;
  if (phi == 9999.)
    return outside_phi_crack;
  if (emobj->IsCC(1.05)){
    float phimod=fmod(phi+0.1,kinem::PI/16.);
    outside_phi_crack=((phimod<0.1-0.02) || (phimod>0.1+0.02));
  }
  return outside_phi_crack;
}
ClassImp(EffAnalysis)
