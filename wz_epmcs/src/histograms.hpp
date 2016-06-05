#ifndef _HISTOGRAMS_HPP
#define _HISTOGRAMS_HPP

#include "hist_nd.hpp"

//Efficiency smear histograms
static HIST_1D EFFSMEAR_Hist[]={
  {"h_PhiCrackEff_Denominator","Phi - All Objects, Phi Crack Eff (denominator)", 132 , 0., 6.4},
  {"h_PhiCrackEff_Numerator","Phi - Passing Objects, Phi Crack Eff (numerator)", 132 , 0., 6.4},
  {"h_TriggerEff_Pt_Denominator","Pt - All Objects, Trigger Eff (denominator)", 120 , 0., 60.},
  {"h_TriggerEff_Pt_Numerator","Pt - Passing Objects, Trigger Eff (numerator)", 120 , 0., 60.},
  {"h_TriggerEff_DetEta_Denominator","Detector Eta - All Objects, Trigger Eff (denominator)", 160 , -4., 4.},
  {"h_TriggerEff_DetEta_Numerator","Detector Eta - Passing Objects, Trigger Eff (numerator)", 160 , -4., 4.},
  {"h_PreselEff_DetEta_Denominator","Detector Eta - All Objects, Presel Eff (denominator)", 160 , -4., 4.},
  {"h_PreselEff_DetEta_Numerator","Detector Eta - Passing Objects, Presel Eff (numerator)", 160 , -4., 4.},
  {"h_EMIDEff_DetEta_Denominator","Detector Eta - All Objects, EMID Eff (denominator)", 160 , -4., 4.},
  {"h_EMIDEff_DetEta_Numerator","Detector Eta - Passing Objects, EMID Eff (numerator)", 160 , -4., 4.},
  {"h_TrkEff_DetEta_Denominator","Detector Eta - All Objects, Trk Eff (denominator)", 160 , -4., 4.},
  {"h_TrkEff_DetEta_Numerator","Detector Eta - Passing Objects, Trk Eff (numerator)", 160 , -4., 4.},
  {"h_TrkEff_ZVertex_Denominator","Z Vertex - All Objects, Trk Eff (denominator)", 400 , -100., 100.},
  {"h_TrkEff_ZVertex_Numerator","Z Vertex - Passing Objects, Trk Eff (numerator)", 400 , -100., 100.},
  {"h_looseTrkEff_DetEta_Denominator","Detector Eta - All Objects, Trk Eff (denominator)", 160 , -4., 4.},
  {"h_looseTrkEff_DetEta_Numerator","Detector Eta - Passing Objects, Trk Eff (numerator)", 160 , -4., 4.},
  {"h_looseTrkEff_ZVertex_Denominator","Z Vertex - All Objects, Trk Eff (denominator)", 400 , -100., 100.},
  {"h_looseTrkEff_ZVertex_Numerator","Z Vertex - Passing Objects, Trk Eff (numerator)", 400 , -100., 100.},
  {"", "", 0, 0, 0}
};

static HIST_2D EFFSMEAR_Hist_2D[]={
  {"h_TriggerEff_PtVDetEta_Denominator","Pt vs. Detector Eta - All Objects, Trigger Eff (denominator)", 80 , -4., 4., 60 , 0., 60.},
  {"h_TriggerEff_PtVDetEta_Numerator","Pt vs. Detector Eta - Passing Objects, Trigger Eff (numerator)", 80 , -4., 4., 60 , 0., 60.},
  {"h_TrkEff_DetEtaVZVertex_Denominator","Detector Eta vs. Z Vertex - All Objects, Trk Eff (denominator)", 80 , -4., 4., 200 , -100., 100.},
  {"h_TrkEff_DetEtaVZVertex_Numerator","Detector Eta vs. Z Vertex - Passing Objects, Trk Eff (numerator)", 80 , -4., 4., 200 , -100., 100.},
  {"h_looseTrkEff_DetEtaVZVertex_Denominator","Detector Eta vs. Z Vertex - All Objects, Trk Eff (denominator)", 80 , -4., 4., 200 , -100., 100.},
  {"h_looseTrkEff_DetEtaVZVertex_Numerator","Detector Eta vs. Z Vertex - Passing Objects, Trk Eff (numerator)", 80 , -4., 4., 200 , -100., 100.},
  {"", "", 0, 0, 0, 0, 0, 0}
};

//EM smear histograms
static HIST_1D EMSMEAR_Hist[]={
  {"h_smearedEM_DeltaPt","Smeared MC EM Particle - change in Pt (smeared - generated)", 600, -30., 30.},
  {"h_smearedEM_DeltaEta","Smeared MC EM Particle - change in Eta (smeared - generated)", 10000, -1., 1.},
  {"h_smearedEM_DeltaPhi","Smeared MC EM Particle - change in Phi (smeared - generated)", 200000, 0, 4.0},
  {"h_smearedEM_DeltaDetEta","Smeared MC EM Particle - change in Det Eta (smeared - generated)", 2000, -1., 1.},
  {"h_smearedEM_DeltaDetPhi","Smeared MC EM Particle - change in Det Phi (smeared - generated)", 200000, 0., 4.0},
  {"", "", 0, 0, 0}
};


static HIST_PROFILE EMSMEAR_Profile[]={
  {"ZBDiffvUparaCorr","ZBDiffvUparaCorr", 1500, 0.,5.,-10.,10.,"i"},
  {"", "", 0, 0, 0,0,0,"i"}
};

static HIST_2D EMSMEAR_Hist_2D[]={
  {"h_smearedEM_DeltaPt_v_Pt","Smeared MC EM Particle - change in Pt (smeared - generated) vs. Pt", 120,0,60,600, -30., 30.},
  {"h_smearedEM_DeltaEta_v_Eta","Smeared MC EM Particle - change in Eta (smeared - generated) vs. Eta", 100,-5.,5.,2000, -1., 1.},
  {"h_smearedEM_DeltaPhi_v_Phi","Smeared MC EM Particle - change in Phi (smeared - generated) vs. Phi", 132, 0, 6.4,32000, 0, 3.2},
  {"h_smearedEM_DeltaDetEta_v_DetEta","Smeared MC EM Particle - change in Det Eta (smeared - generated) vs. Det Eta", 100,-5.,5.,2000, -1., 1.},
  {"h_smearedEM_DeltaDetPhi_v_DetPhi","Smeared MC EM Particle - change in Det Phi (smeared - generated) vs. Det Phi", 132, 0, 6.4,32000, 0., 3.2},
  {"h_false_Phi_v_Eta","phi vs. eta", 100,-2,2,100, -3.2, 3.2},
  {"h_true_Phi_v_Eta","phi vs. eta",  100,-2,2,100, -3.2, 3.2},


  {"h_smearedEM_GenPt_v_SmearPt","Smeared MC EM Particle - Pt smeared vs. Pt generated", 120,0,60., 120,0,60.},
  {"h_smearedEM_GenEta_v_SmearEta","Smeared MC EM Particle - Eta smeared vs. Eta generated", 100,-5.,5.,100,-5.,5.},
  {"h_smearedEM_GenPhi_v_SmearPhi","Smeared MC EM Particle - Phi smeared vs. Phi generated", 132, 0, 6.4,132, 0, 6.4},
  {"h_smearedEM_GenDetEta_v_SmearDetEta","Smeared MC EM Particle - Det Eta smeared vs. Det Eta generated", 100,-5.,5.,100,-5.,5.},
  {"h_smearedEM_GenDetPhi_v_SmearDetPhi","Smeared MC EM Particle - Det Phi smeared vs. Det Phi generated", 132, 0, 6.4,132, 0, 6.4},

  {"", "", 0, 0, 0, 0, 0, 0}
};


//Recoil smear histograms
static HIST_1D RECOILSMEAR_Hist[]={
  {"h_smearedRecoil_DeltaX","Smeared MC Recoil - change in X (smeared - generated)", 300, -30., 30.},
  {"h_smearedRecoil_DeltaY","Smeared MC Recoil - change in Y (smeared - generated)", 300, -30., 30.},
  {"h_smearedRecoil_DeltaPhi","Smeared MC Recoil - change in Phi (smeared - generated)", 640, 0, 3.2},
  {"", "", 0, 0, 0}
};

static HIST_2D RECOILSMEAR_Hist_2D[]={
  {"h_smearedRecoil_DeltaX_v_X","Smeared MC Recoil - change in X (smeared - generated) vs. X", 200,-50.,50.,200, -50., 50.},
  {"h_smearedRecoil_DeltaY_v_Y","Smeared MC Recoil - change in Y (smeared - generated) vs. Y", 200,-50.,50.,200, -50., 50.},
  {"h_smearedRecoil_DeltaPhi_v_Phi","Smeared MC Recoil - change in Phi (smeared - generated) vs. Phi", 132, 0, 6.4,64, 0, 3.2},

  {"h_smearedRecoil_GenX_v_SmearX","Smeared MC Recoil - X smeared vs. X generated", 100,-50.,50., 100,-50.,50.},
  {"h_smearedRecoil_GenY_v_SmearY","Smeared MC Recoil - Y smeared vs. Y generated", 100,-50.,50.,100,-50.,50.},
  {"h_smearedRecoil_GenPhi_v_SmearPhi","Smeared MC Recoil - Phi smeared vs. Phi generated", 132, 0, 6.4,132, 0, 6.4},

  {"", "", 0, 0, 0, 0, 0, 0}
};


//MC W Boson histograms
static HIST_1D MCWBOSON_Hist[]={
  {"hMCW_Pt_CC","MC W Pt CC", 120, 0., 60.},
  {"hMCW_Phi_CC","MC W Phi CC", 132, 0., 6.4},
  {"hMCW_Mass_CC","MC W Mass CC", 300, 50., 200.},
  {"hMCW_Pt_CC_bin","MC W Pt CC bin", 120, 0., 60.},
  {"hRecoilW_Pt_CC_bin","MC W Recoil Pt CC bin", 120, 0., 60.},
  {"", "", 0, 0, 0}
};

//W cand histograms
static HIST_1D WCand_Hist_Upara[]={
  {"hWcandUpara_CC","U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandTrueUpara_CC","True U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandResolUpara_CC","U_parallel resolution for W events (CC)", 120, -30., 30.},
  {"hWcandUpara_emEff_CC","U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandUpara_emtrkEff_CC","U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandUpara_emtrksetEff_CC","U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandUpara_noEff_CC","U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandUpara_emEff_EC","U_parallel for W events (EC)", 120, -30., 30.},
  {"hWcandUpara_emtrkEff_EC","U_parallel for W events (EC)", 120, -30., 30.},
  {"hWcandUpara_emtrksetEff_EC","U_parallel for W events (EC)", 120, -30., 30.},
  {"hWcandUpara_noEff_EC","U_parallel for W events (EC)", 120, -30., 30.},
  {"hWcandUpara_CC_cosdphi","U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandUpara_emEff_CC_cosdphi","U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandUpara_emtrkEff_CC_cosdphi","U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandUpara_emtrksetEff_CC_cosdphi","U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandUpara_noEff_CC_cosdphi","U_parallel for W events (CC)", 120, -30., 30.},
  {"hWcandUpara_emEff_EC_cosdphi","U_parallel for W events (EC)", 120, -30., 30.},
  {"hWcandUpara_emtrkEff_EC_cosdphi","U_parallel for W events (EC)", 120, -30., 30.},
  {"hWcandUpara_emtrksetEff_EC_cosdphi","U_parallel for W events (EC)", 120, -30., 30.},
  {"hWcandUpara_noEff_EC_cosdphi","U_parallel for W events (EC)", 120, -30., 30.},
  //
  {"hWcandElecPt_emEff_CC","U_parallel for W events (CC)", 200, 0., 100.},
  {"hWcandElecPt_emtrkEff_CC","U_parallel for W events (CC)", 200, 0., 100.},
  {"hWcandElecPt_emtrksetEff_CC","U_parallel for W events (CC)", 200, 0., 100.},
  {"hWcandElecPt_noEff_CC","U_parallel for W events (CC)", 200, 0., 100.},
  {"hWcandElecPt_emEff_EC","U_parallel for W events (EC)", 200, 0., 100.},
  {"hWcandElecPt_emtrkEff_EC","U_parallel for W events (EC)", 200, 0., 100.},
  {"hWcandElecPt_emtrksetEff_EC","U_parallel for W events (EC)", 200, 0., 100.},
  {"hWcandElecPt_noEff_EC","U_parallel for W events (EC)", 200, 0., 100.},
  //
  {"hWcandElecEta_emEff_CC","U_parallel for W events (CC)", 60, -3., 3.},
  {"hWcandElecEta_emtrkEff_CC","U_parallel for W events (CC)", 60, -3., 3.},
  {"hWcandElecEta_emtrksetEff_CC","U_parallel for W events (CC)", 60, -3., 3.},
  {"hWcandElecEta_noEff_CC","U_parallel for W events (CC)", 60, -3., 3.},
  {"hWcandElecEta_emEff_EC","U_parallel for W events (EC)", 60, -3., 3.},
  {"hWcandElecEta_emtrkEff_EC","U_parallel for W events (EC)", 60, -3., 3.},
  {"hWcandElecEta_emtrksetEff_EC","U_parallel for W events (EC)", 60, -3., 3.},
  {"hWcandElecEta_noEff_EC","U_parallel for W events (EC)", 60, -3., 3.},

  {"hWcandSET_noEff_CC","SET for W events (CC)", 300, 0., 300.},
  {"hWcandSET_emtrksetEff_CC","SET for W events (CC)", 300, 0., 300.},
  {"hWcandLumi_noEff_CC","Lumi for W events (CC)", 100, 0., 10.},
  {"hWcandLumi_emtrksetEff_CC","Lumi for W events (CC)", 100, 0., 10.},


  //
  {"", "", 0, 0, 0}
};

static HIST_2D WCand_Hist_UparaUperp[]={
  {"hWcandUparaUperp_emEff_CC","Upara vs. Uperp for W events (CC)", 120, -30., 30., 120, -30., 30.},
  {"hWcandUparaUperp_emtrkEff_CC","Upara vs. Uperp for W events (CC)", 120, -30., 30., 120, -30., 30.},
  {"hWcandUparaUperp_emtrksetEff_CC","Upara vs. Uperp for W events (CC)", 120, -30., 30., 120, -30., 30.},
  {"hWcandUparaUperp_noEff_CC","Upara vs. Uperp for W events (CC)", 120, -30., 30., 120, -30., 30.},
  {"hWcandSETLumi_noEff_CC","SET vs. Lumi for W events (CC)", 30, 0., 300., 100, 0., 10.},
  {"hWcandSETLumi_emtrksetEff_CC","SET vs. Lumi for W events (CC)", 30, 0., 300., 100, 0., 10.},
  {"", "", 0, 0, 0, 0, 0, 0}
};

static HIST_1D WCand_Hist_UparaOverPte[]={
  {"hWcandUpara_CC","U_parallel over pTe for W events (CC)", 100, -1., 1.},
  {"hWcandUpara_emEff_CC","U_parallel over pTe for W events (CC)", 100, -1., 1.},
  {"hWcandUpara_emtrkEff_CC","U_parallel over pTe for W events (CC)", 100, -1., 1.},
  {"hWcandUpara_emtrksetEff_CC","U_parallel over pTe for W events (CC)", 100, -1., 1.},
  {"hWcandUpara_noEff_CC","U_parallel over pTe for W events (CC)", 100, -1., 1.},
  {"hWcandUpara_emEff_EC","U_parallel over pTe for W events (EC)", 100, -1., 1.},
  {"hWcandUpara_emtrkEff_EC","U_parallel over pTe for W events (EC)", 100, -1., 1.},
  {"hWcandUpara_emtrksetEff_EC","U_parallel over pTe for W events (EC)", 100, -1., 1.},
  {"hWcandUpara_noEff_EC","U_parallel over pTe for W events (EC)", 100, -1., 1.},
  {"", "", 0, 0, 0}
};

static HIST_1D WCand_Hist_CosUphi[]={
  {"hWcandUpara_CC","cos(Uphi) for W events (CC)", 100, -1., 1.},
  {"hWcandUpara_emEff_CC","cos(Uphi) for W events (CC)", 100, -1., 1.},
  {"hWcandUpara_emtrkEff_CC","cos(Uphi) for W events (CC)", 100, -1., 1.},
  {"hWcandUpara_emtrksetEff_CC","cos(Uphi) for W events (CC)", 100, -1., 1.},
  {"hWcandUpara_noEff_CC","cos(Uphi) for W events (CC)", 100, -1., 1.},
  {"hWcandUpara_emEff_EC","cos(Uphi) for W events (EC)", 100, -1., 1.},
  {"hWcandUpara_emtrkEff_EC","cos(Uphi) for W events (EC)", 100, -1., 1.},
  {"hWcandUpara_emtrksetEff_EC","cos(Uphi) for W events (EC)", 100, -1., 1.},
  {"hWcandUpara_noEff_EC","cos(Uphi) for W events (EC)", 100, -1., 1.},
  {"", "", 0, 0, 0}
};

static HIST_1D WCand_PDF_Hist[]={
  {"hWcandMt_CC_PDF","Transverse mass for W events (CC)", 300, 50., 200.},
  {"hWcandElecPt_CC_PDF","Electron pT for W events (CC)", 200, 0., 100.},
  {"hWcandMet_CC_PDF","MET for W events (CC)", 200, 0., 100.},
  {"hWcandMt_PDF","Transverse mass for W events (CC and EC)", 300, 50., 200.},
  {"hWcandElecPt_PDF","Electron pT for W events (CC and EC)", 200, 0., 100.},
  {"hWcandMet_PDF","MET for W events (CC and EC)", 200, 0., 100.},
  {"", "", 0, 0, 0}
};


static HIST_1D WCand_Hist[]={
  {"hWcandEvtCnt","Event counter for efficiency measurements", 1, 0., 1.},
  //
  {"hWcandMt","Transverse mass for W events", 300, 50., 200.},
  {"hWcandElecPt","Electron pT for W events", 200, 0., 100.},
  {"hWcandMet","MET for W events", 200, 0., 100.},
  {"hWcandElecPt_Spatial_Match_EtaBin_CC", "", 200, 0., 100.},
  {"hWcandMCElecPt_Spatial_Match_EtaBin_CC", "", 200, 0., 100.},
  {"hWcandMCElecPtDiff_Spatial_Match_EtaBin_CC", "", 200, -10., 10.},
  {"hWcandElecPt_Spatial_Match_EtaBin_CC_Tail", "", 200, 0., 100.},
  {"hWcandMCElecPt_Spatial_Match_EtaBin_CC_Tail", "", 200, 0., 100.},
  {"hWcandMCElecPtDiff_Spatial_Match_EtaBin_CC_Tail", "", 200, -10., 10.},
  {"hWcandMCElecPt_EtaBin_CC_NoCuts", "", 200, 0., 100.},
  {"hWcandVtx_CC", "Vertex for W candidate (CC)", 320, -80., 80.},
  {"hWcandLumi_CC", "W lumi profile (CC)", 250, 0., 10.},
  {"hWcandScalarEt_CC", "W scalar ET (CC)", 300, 0., 300.},
  {"hWcandScalarEtZB_CC", "W scalar ET of ZB (CC)", 300, 0., 300.},
  {"hWcandScalarEtZBNoScale_CC", "W scalar ET of ZB no scale_zb (CC)", 300, 0., 300.},
  {"hWcandWPt_CC","W pT for W events (CC)", 100, 0, 50},
  {"hWcandTrueWPt_CC","True W pT for W events (CC)", 100, 0, 50},
  {"hWcandResolWPt_CC","W pT resolution for W events (CC)", 100, -30, 30},
  {"hWcandMt_CC","Transverse mass for W events (CC)", 300, 50., 200.},
  {"hWcandElecPt_CC","Electron pT for W events (CC)", 200, 0., 100.},
  {"hWcandElecPx_CC","Electron pX for W events (CC)", 400, -100., 100.},
  {"hWcandElecPy_CC","Electron pY for W events (CC)", 400, -100., 100.},
  {"hWcandElecTrkPt_CC","Electron track pT for W events (CC)", 200, 0., 100.},
  {"hWcandMet_CC","MET for W events (CC)", 200, 0., 100.},
  {"hWcandMetx_CC","METx for W events (CC)", 200, -100., 100.},
  {"hWcandMety_CC","METy for W events (CC)", 200, -100., 100.},
  {"hWcandWPhi_CC","W candidate Phi (CC)", 64, 0., TMath::TwoPi()},
  {"hWcandMt_CC_Width","Transverse mass for W events (CC)", 300, 50., 200.},
  {"hWcandElecPt_CC_Width","Electron pT for W events (CC)", 200, 0., 100.},
  {"hWcandMet_CC_Width","MET for W events (CC)", 200, 0., 100.},
  {"hWcandWPt_CC_Width","W pT for W events (CC)", 200, 0, 100},
  {"hWcandMt_CC_Tail_Width","Transverse mass for W events (CC)", 300, 50., 200.},
  {"hWcandElecPt_CC_Tail_Width","Electron pT for W events (CC)", 200, 0., 100.},
  {"hWcandMet_CC_Tail_Width","MET for W events (CC)", 200, 0., 100.},
  {"hWcandWPt_CC_Tail_Width","W pT for W events (CC)", 200, 0, 100},

  {"hWcandUperp_CC","U_perpendicular for W events (CC)", 120, -30., 30.},
  {"hWcandTrueUperp_CC","True U_perpendicular for W events (CC)", 120, -30., 30.},
  {"hWcandResolUperp_CC","U_perpendicular resolution for W events (CC)", 120, -30., 30.},
  {"hWcandElecPtUpara1_CC","Electron pT for W events with Upara<0 (CC)", 160, 20., 100.},
  {"hWcandElecPtUpara2_CC","Electron pT for W events with Upara>0 (CC)", 160, 20., 100.},
  {"hWcandElecTrkPtUpara1_CC","Electron track pT for W events with Upara<0 (CC)", 200, 0., 100.},
  {"hWcandElecTrkPtUpara2_CC","Electron track pT for W events with Upara>0 (CC)", 200, 0., 100.},
  {"hWcandMetUpara1_CC","MET for W events with Upara<0 (CC)", 160, 20., 100.},
  {"hWcandMetUpara2_CC","MET for W events with Upara>0 (CC)", 160, 20., 100.},
  {"hWcandMtUpara1_CC","Transverse mass for W events with Upara<0 (CC)", 300, 50., 200.},
  {"hWcandMtUpara2_CC","Transverse mass for W events with Upara>0 (CC)", 300, 50., 200.},
  {"hWcandWPtUpara1_CC","W pT for W events with Upara<0 (CC)", 100, 0., 50.},
  {"hWcandWPtUpara2_CC","W pT for W events with Upara>0 (CC)", 100, 0., 50.},
  {"hWcandElecEta_CC", "Elec Eta for W candidate (CC)", 60, -3., 3.},
  {"hWcandElecDetEta_CC", "Elec DetEta for W candidate (CC)", 60, -3., 3.},
  {"hWcandElecPhi_CC", "Elec Phi for W candidate (CC)", 64, 0., TMath::TwoPi()},
  {"hWcandElecDetPhi_CC", "Elec DetPhi for W candidate (CC)", 64, 0., TMath::TwoPi()},
  {"hWcandElecPhiTrkAtDCA_CC", "Elec Phi from TrkAtDCA for W candidate (CC)", 64, 0., TMath::TwoPi()},
  {"hWcandElecPhiTrkAtEM3_CC", "Elec Phi from TrkAtEM3 for W candidate (CC)", 64, 0., TMath::TwoPi()},
  {"hWcandElecDetPhiCALO_CC",  "Elec DetPhi from CALO  for W candidate (CC)", 64, 0., TMath::TwoPi()},
  {"hWcandElecTrkPhiModEM3_CC", "Elec Trk PhiMod at EM3  - W candidate (CC)", 64, 0., 1.},
  {"hWcandMetPhi_CC", "MET Phi for W candidate (CC)", 64, 0., TMath::TwoPi()},
  {"hWcandEOverP_CC", "E/p for W candidate (CC)", 100, 0., 3.},
  {"hWcandElecTrkPtOvE_CC", "Track P_t /  E (CC)", 200, 0., 1.1},
  {"hWcandRecoilPt_CC","Recoil Pt for W events (CC)", 100, 0., 50.},
  {"hWcandRecoilPx_CC","Recoil Px for W events (CC)", 200, -50., 50.},
  {"hWcandRecoilPy_CC","Recoil Py for W events (CC)", 200, -50., 50.},
  {"hWcandRecoilPhi_CC","Recoil Phi for W events (CC)", 64, 0., TMath::TwoPi()},
  {"hWcandElecMETDeltaPhi_CC", "Elec MET Delta Phi - W candidate (CC)", 100, 0., TMath::Pi()},
  {"hWcandElecRecoilDeltaPhi_CC", "Elec Recoil Delta Phi - W candidate (CC)", 100, 0.,TMath::Pi()},
  {"hWcandMETRecoilDeltaPhi_CC", "MET Recoil Delta Phi - W candidate (CC)", 100, 0., TMath::Pi()},
  {"hWcandMt_UtBin0_CC","Transverse mass for W events with Ut < 5 (CC)", 300, 50., 200.},
  {"hWcandMt_UtBin1_CC","Transverse mass for W events with 5 < Ut < 10 (CC)", 300, 50., 200.},
  {"hWcandMt_UtBin2_CC","Transverse mass for W events with 10 < Ut < 15 (CC)", 300, 50., 200.},
  // for different recoil Pt bins
  {"hWcandMt_RecoilBin", "Mt for different recoil pT bins", 300, 50., 200.},
  {"hWcandElecPt_RecoilBin",  "Elec Pt for different recoil pT bins", 200, 0., 100.},
  {"hWcandMet_RecoilBin",  "Met for different recoil pT bins", 200, 0., 100.},
  {"hWcandElecMetDeltaPhi_RecoilBin", "Elec-Met DeltaPhi for different recoil pT bins", 100, 0., TMath::Pi()},
  {"hWcandElecRecoilDeltaPhi_RecoilBin", "Elec-Recoil DeltaPhi for different recoil pT bins", 100, 0., TMath::Pi()},
  {"hWcandMetRecoilDeltaPhi_RecoilBin", "Met-Recoil DeltaPhi for different recoil pT bins", 100, 0., TMath::Pi()},
  {"hWcandRecoilPhi_RecoilBin", "Recoil Phi for different recoil pT bins", 64, 0., TMath::TwoPi()},
  {"hWcandUPara_RecoilBin", "UPara for different recoil pT bins", 120, -30., 30.},
  {"hWcandUPerp_RecoilBin", "UPerp for different recoil pT bins", 120, -30., 30.},
  {"hWcandVtx_RecoilBin", "vertex for different recoil pT bins", 320, -80., 80.},
  {"hWcandPhi_RecoilBin", "W Phi for different recoil pT bins", 64, 0., TMath::TwoPi()},
  {"hWcandInstLumi_RecoilBin", "instlumi for different recoil pT bins", 100, 0., 4.},
  {"hWcandScalarEt_RecoilBin", "ScalarEt for different recoil pT bins", 300, 0., 300.},  
  //MW
  // for different electron Pt bins 
  {"hWcandScalarEt_ElecPtBin", "ScalarEt for different electron pT bins", 300, 0., 300.},  
  {"hWcandSEToverEpt_ElecPtBin", "SET over epT for different electron pT bins", 100, 0., 5.},  
  {"hWcandScalarEt_Tail", "ScalarEt for epTs in the tail", 300, 0., 300.},  
  {"hWcandSEToverEpt_Tail", "SET over epT for epTs in the tail", 100, 0., 5.},
  {"hWcandUpara_ElecPtBin", "UPara for different recoil pT bins", 120, -30., 30.}, 
  //E/p
  {"hWcandEOverP", "E/p", 100, 0., 3.},
  {"hWcandEOverP_Mod", "E/p", 100, 0., 3.},
  {"hWcandEOverP_TrkMod", "E/p", 100, 0., 3.},
  // maps for W mass and width
  // number of bins, x min and max will be modified inside the code
  {"histd1map_WMassTemplates", "Map for W Mass templates", 100, 89., 92.},
  {"histd1map_WWidthTemplates", "Map for W Width templates", 100, 89., 92.},
  // FSR stuff
  { "hWcandInConeFSR_Number_CC", "Number of incone FSR photons", 10, 0., 10.},
  {"","", 0,0,0}
};

static HIST_PROFILE WCand_Profile[]={
  {"hWcandWPtUpara_CC","W pT vs U_parallel", 60, 0., 30., -20., 20., "i"},
  {"hWcandMtUpara_CC","W M_T vs U_parallel", 75, 50., 200., -20., 20., "i"},
  {"hWcandElecPtUpara_CC","W Electron pT vs U_parallel", 50, 25., 50., -20., 20., "i"},
  {"hWcandMetUpara_CC","W MET vs U_parallel", 50, 25., 50., -20., 20., "i"},
  {"hWcandEOverP_V_ElecPhiMod", "E/p vs phimod", 40, 0., 1., 0., 3., "i"},
  {"hWcandEOverP_V_ElecTrkPhiMod", "E/p vs track phimod", 40, 0., 1., 0., 3., "i"},
  {"hWcandEOverP_V_ElecTrkPhiModEM3", "E/p vs track phimod", 40, 0., 1., 0., 3., "i"},
  {"hWcandScalarEt_V_Lumi_CC", "W SET V. Lumi (CC)",100, 0., 10., 0., 300., "i"},  
  {"","", 0,0,0,0,0, "i"}
};

static HIST_2D WCand_Hist_2D[]={
  {"hWcandElecPt_V_Upara_CC","W Electron pT vs U_parallel", 50, 0., 50., 100, -50., 50.},
  {"hWcandScalarEt_V_Lumi2D_CC", "W SET Lumi 2D (CC)",100, 0., 10.,  100, 0., 300.},  
  {"hWcandInConeFSR_Number_V_MergedTrueEnergy", "", 10, 0., 10., 200, 0., 100.},
  {"","", 0,0,0,0,0,0}
};

static HIST_1D WCand_Hist_SingVariable[] = {
  {"hWcandSingVariable_CC", "Singularity variable for W mass (CC)", 200, -30., 30.},
  // {"hWcandSingVariable", "Singularity variable for W mass", 200, -30., 30.},

  {"hWcandSingVariable_PDF_CC", "Singularity variable for W mass (CC) with PDF weights", 200, -30., 30.},
  // {"hWcandSingVariable_PDF", "Singularity variable for W mass with PDF weights", 200, -30., 30.},

  {"hWcandSingVariable_Gen_CC", "Singularity variable for W mass at generator level (CC)", 200, -30., 30.},
  // {"hWcandSingVariable_Gen", "Singularity variable for W mass at generator level", 200, -30., 30.},
  {"hWcandMt_Gen_CC","Transverse mass for Generator W events (CC)", 300, 50., 200.},
  {"hWcandElecPt_Gen_CC","Electron pT for Generator W events (CC)", 200, 0., 100.},
  {"hWcandMet_Gen_CC","MET for Generator W events (CC)", 200, 0., 100.},
  // {"hWcandMt_Gen","Transverse mass for Generator W events", 300, 50., 200.},
  //  {"hWcandElecPt_Gen","Electron pT for Generator W events", 200, 0., 100.},
  // {"hWcandMet_Gen","MET for Generator W events", 200, 0., 100.},
  {"hWcandSingVariable_Gen_PDF_CC", "Singularity variable for W mass at generator level (CC)", 200, -30., 30.},
  //  {"hWcandSingVariable_Gen_PDF", "Singularity variable for W mass at generator level", 200, -30., 30.},

  // {"hWcandSingVariable_LongUnSmeared_CC", "Singularity variable for W mass (CC)", 200, -30., 30.},
  // {"hWcandSingVariable_LongUnSmeared", "Singularity variable for W mass", 200, -30., 30.},
  // {"hWcandSingVariable_LongUnSmeared_PDF_CC", "Singularity variable for W mass (CC)", 200, -30., 30.},
  // {"hWcandSingVariable_LongUnSmeared_PDF", "Singularity variable for W mass", 200, -30., 30.},

  //use the wmass templates now like with other variables
  // {"histd1map_SingVariableTemplates", "Map for template mass templates", 50, 79.400, 81.400},

  //  {"histd2map_SingVariableTemplates", "Map for template mass templates", 50, 79.400, 81.400},
  {"", "", 0, 0, 0}
};


//Z cand histograms
static HIST_1D MCZBOSON_Hist[]={
  {"hMCZ_Pt","MC Z Pt", 120, 0., 60.},
  {"hMCZ_Eta","MC Z Eta", 100, -10., 10.},
  {"hMCZ_Phi","MC Z Phi", 132, 0., 6.4},
  {"hMCZ_Mass","MC Z Mass", 150, 0., 150.},
  {"", "", 0, 0, 0}
};

static HIST_1D ZCand_Hist_Upara[]={
  {"hZcandUpara_noEff_CC","U_parallel for Z events (CC-CC)", 120, -30., 30.},
  {"hZcandUpara_emEff_CC","U_parallel for Z events (CC-CC)", 120, -30., 30.},
  {"hZcandUpara_emuparaEff_CC","U_parallel for Z events (CC-CC)", 120, -30., 30.},
  {"hZcandUpara_emuparasetEff_CC","U_parallel for Z events (CC-CC)", 120, -30., 30.},
  {"hZcandUparaOnePass_noEff_CC","UPara for Z events (CC-CC) One Pass NoEff", 120, -30., 30.},
  {"hZcandUparaOnePass_emuparasetEff_CC","UPara for Z events (CC-CC) One Pass AllEff", 120, -30., 30.},
  {"hZcandUparaOneNotPass_noEff_CC","UPara for Z events (CC-CC) One Not Pass NoEff", 120, -30., 30.},
  {"hZcandUparaOneNotPass_emuparasetEff_CC","UPara for Z events (CC-CC) One Not Pass AllEff", 120, -30., 30.},
  {"hZcandUparaBothPass_noEff_CC","UPara for Z events (CC-CC) Both Pass NoEff", 120, -30., 30.},
  {"hZcandUparaBothPass_emuparasetEff_CC","UPara for Z events (CC-CC) Both Pass AllEff", 120, -30., 30.},

  {"hZcandElecPt_noEff_CC","ElecPt for Z events (CC-CC)", 200, 0., 100.},
  {"hZcandElecPt_emuparasetEff_CC","ElecPt for Z events (CC-CC)", 200, 0., 100.},
  {"hZcandElecPtOnePass_noEff_CC","ElecPt for Z events (CC-CC) One Pass NoEff", 200, 0., 100.},
  {"hZcandElecPtOnePass_emuparasetEff_CC","ElecPt for Z events (CC-CC) One Pass AllEff", 200, 0., 100.},
  {"hZcandElecPtOneNotPass_noEff_CC","ElecPt for Z events (CC-CC) One Not Pass NoEff", 200, 0., 100.},
  {"hZcandElecPtOneNotPass_emuparasetEff_CC","ElecPt for Z events (CC-CC) One Not Pass AllEff", 200, 0., 100.},
  {"hZcandElecPtBothPass_noEff_CC","ElecPt for Z events (CC-CC) Both Pass NoEff", 200, 0., 100.},
  {"hZcandElecPtBothPass_emuparasetEff_CC","ElecPt for Z events (CC-CC) Both Pass AllEff", 200, 0., 100.},

  {"hZcandTrueElecPt_noEff_CC","ElecPt for Z events (CC-CC)", 200, 0., 100.},
  {"hZcandTrueElecPt_emuparasetEff_CC","ElecPt for Z events (CC-CC)", 200, 0., 100.},
  {"hZcandTrueElecPtOnePass_noEff_CC","ElecPt for Z events (CC-CC) One Pass NoEff", 200, 0., 100.},
  {"hZcandTrueElecPtOnePass_emuparasetEff_CC","ElecPt for Z events (CC-CC) One Pass AllEff", 200, 0., 100.},
  {"hZcandTrueElecPtOneNotPass_noEff_CC","ElecPt for Z events (CC-CC) One Not Pass NoEff", 200, 0., 100.},
  {"hZcandTrueElecPtOneNotPass_emuparasetEff_CC","ElecPt for Z events (CC-CC) One Not Pass AllEff", 200, 0., 100.},
  {"hZcandTrueElecPtBothPass_noEff_CC","ElecPt for Z events (CC-CC) Both Pass NoEff", 200, 0., 100.},
  {"hZcandTrueElecPtBothPass_emuparasetEff_CC","ElecPt for Z events (CC-CC) Both Pass AllEff", 200, 0., 100.},

  {"hZcandPtee_noEff_CC","Ptee for Z events (CC-CC)", 200, 0., 50.},
  {"hZcandPtee_emuparasetEff_CC","Ptee for Z events (CC-CC)", 200, 0., 50.},
  {"hZcandPteeOnePass_noEff_CC","Ptee for Z events (CC-CC) One Pass NoEff", 200, 0., 50.},
  {"hZcandPteeOnePass_emuparasetEff_CC","Ptee for Z events (CC-CC) One Pass AllEff", 200, 0., 50.},
  {"hZcandPteeOneNotPass_noEff_CC","Ptee for Z events (CC-CC) One Not Pass NoEff", 200, 0., 50.},
  {"hZcandPteeOneNotPass_emuparasetEff_CC","Ptee for Z events (CC-CC) One Not Pass AllEff", 200, 0., 50.},
  {"hZcandPteeBothPass_noEff_CC","Ptee for Z events (CC-CC) Both Pass NoEff", 200, 0., 50.},
  {"hZcandPteeBothPass_emuparasetEff_CC","Ptee for Z events (CC-CC) Both Pass AllEff", 200, 0., 50.},

  {"hZcandSET_noEff_CC","SET for Z events (CC-CC)", 300, 0., 300.},
  {"hZcandSET_emuparasetEff_CC","SET for Z events (CC-CC)", 300, 0., 300.},
  {"hZcandLumi_noEff_CC","Lumi for Z events (CC-CC)", 100, 0., 10.},
  {"hZcandLumi_emuparasetEff_CC","Lumi for Z events (CC-CC)", 100, 0., 10.},

  {"", "", 0, 0, 0}
};

static HIST_2D ZCand_Hist_UparaUperp[]={
  {"hZcandUparaUperp_noEff_CC","Upara vs. Uperp for Z events (CC-CC)", 120, -30., 30., 120, -30., 30.},
  {"hZcandUparaUperp_emEff_CC","Upara vs. Uperp for Z events (CC-CC)", 120, -30., 30., 120, -30., 30.},
  {"hZcandUparaUperp_emuparaEff_CC","Upara vs. Uperp for Z events (CC-CC)", 120, -30., 30., 120, -30., 30.},
  {"hZcandUparaUperp_emuparasetEff_CC","Upara vs. Uperp for Z events (CC-CC)", 120, -30., 30., 120, -30., 30.},
  {"hZcandSETLumi_noEff_CC","SET vs. Lumi for Z events (CC-CC)", 300, 0., 300., 100, 0., 10.},
  {"hZcandSETLumi_emuparasetEff_CC","SET vs. Lumi for Z events (CC-CC)", 300, 0., 300., 100, 0., 10.},
  {"", "", 0, 0, 0, 0, 0, 0}
};

static HIST_1D ZCand_Hist_UparaOverPte[]={
  {"hZcandUpara_noEff_CC","U_parallel/pTe for Z events (CC-CC)", 100, -1., 1.},
  {"hZcandUpara_emEff_CC","U_parallel/pTe for Z events (CC-CC)", 100, -1., 1.},
  {"hZcandUpara_emuparaEff_CC","U_parallel/pTe for Z events (CC-CC)", 100, -1., 1.},
  {"hZcandUpara_emuparasetEff_CC","U_parallel/pTe for Z events (CC-CC)", 100, -1., 1.},
  {"", "", 0, 0, 0}
};

static HIST_1D ZCand_Hist_CosUphi[]={
  {"hZcandUpara_noEff_CC","cos(Uphi) for Z events (CC-CC)", 100, -1., 1.},
  {"hZcandUpara_emEff_CC","cos(Uphi) for Z events (CC-CC)", 100, -1., 1.},
  {"hZcandUpara_emuparaEff_CC","cos(Uphi) for Z events (CC-CC)", 100, -1., 1.},
  {"hZcandUpara_emuparasetEff_CC","cos(Uphi) for Z events (CC-CC)", 100, -1., 1.},
  {"", "", 0, 0, 0}
};

static HIST_1D ZCand_Hist[]={
  // truth eff studies
  {"EffTruth_EMPt_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_hmx_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_hmx_upara_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_hmx_upara_set_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_hmx_set_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_hmx_trk_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set__cluscorr_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_hmx_trk_set_CC", "electron pT", 100,0.,100.},
  {"EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set_trkpt_CC", "electron pT", 100,0.,100.},

  // for studying tag-probe method
  {"elecpT","electron pT", 100,0.,100.},
  {"elecpT_after","electron pT", 100,0.,100.},

  {"h_FMass","Fake Mass", 150,0.,150.},
  {"hZcandPt","Z candidate Pt", 240, 0., 60.},
  {"hZcandPx","Z candidate Px", 150, -100., 100.},
  {"hZcandPy","Z candidate Py", 150, -100., 100.},
  {"hZcandPz","Z candidate Pz", 150, -100., 100.},
  {"hZcandEta","Z candidate Rapidity", 100, -10., 10.},
  {"hZcandPhi","Z candidate Phi", 64, 0., TMath::TwoPi()},
  {"hZcandPhi_All","Z candidate Phi", 64, 0., TMath::TwoPi()},
  {"hZcandPhi_CCCC","Z candidate Phi", 64, 0., TMath::TwoPi()},
  {"hZcandPhi_CCEC","Z candidate Phi", 64, 0., TMath::TwoPi()},
  {"hZcandPhi_ECEC","Z candidate Phi", 64, 0., TMath::TwoPi()},
  {"hZcandPhi_bin","Z candidate Phi", 64, 0., TMath::TwoPi()},
  {"hZcandMass","Z candidate Mass", 400, 50., 150.},
  {"hZcandMass_Scale","hZcandMass_Scale", 400, 50., 150.},
  {"hZcandMass_Scale_CCCC","hZcandMass_Scale (CC-CC)", 400, 50., 150.},
  {"hZcandMass_Scale_ECEC","hZcandMass_Scale (EC-EC)", 400, 50., 150.},
  {"hZcandMass_Resolution_CCCC","hZcandMass_Resolution (CC-CC)", 400, 50., 150.},
  {"hZcandMass_Resolution_ECEC","hZcandMass_Resolution (EC-EC)", 400, 50., 150.},

  {"hZcandVtx_All" , "Vertex - Z candidate (All)" , 320, -80., 80.},
  {"hZcandVtx_CCCC", "Vertex - Z candidate (CCCC)", 320, -80., 80.},
  {"hZcandVtx_CCEC", "Vertex - Z candidate (CCEC)", 320, -80., 80.},
  {"hZcandVtx_ECEC", "Vertex - Z candidate (ECEC)", 320, -80., 80.},

  {"hZcandMass_All" , "Z candidate Mass (All)"  , 400, 50., 150.},
  {"hZcandMass_CCCC", "Z candidate Mass (CC-CC)", 400, 50., 150.},
  {"hZcandMass_CCEC", "Z candidate Mass (CC-EC)", 400, 50., 150.},
  {"hZcandMass_ECEC", "Z candidate Mass (EC-EC)", 400, 50., 150.},

  {"hZcandDiffMass_All" , "reco-truth Z candidate Mass (All)"  , 200, -10., 10.},
  {"hZcandDiffMass_CCCC", "reco-truth Z candidate Mass (CC-CC)", 200, -10., 10.},
  {"hZcandDiffMass_CCEC", "reco-truth Z candidate Mass (CC-EC)", 200, -10., 10.},
  {"hZcandDiffMass_ECEC", "reco-truth Z candidate Mass (EC-EC)", 200, -10., 10.},

  {"hZcandMass_All_Mass" , "Z candidate Mass (All)"  , 400, 50., 150.}, // for different Z mass points
  {"hZcandMass_CCCC_Mass" , "Z candidate Mass (CC-CC)"  , 400, 50., 150.}, 
  {"hZcandMass_CCEC_Mass" , "Z candidate Mass (CC-EC)"  , 400, 50., 150.}, 
  {"hZcandMass_ECEC_Mass" , "Z candidate Mass (EC-EC)"  , 400, 50., 150.}, 
  {"hZcandElecPtBoth_CCCC_Mass", "Elec pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecPt1_CCCC_Mass", "Elec pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecPt2_CCCC_Mass", "Elec pT - Z candidate (CC-CC)", 300, 0., 100.},


  {"hZcandMtBoth_CC_Mass", "Elec pT - Z candidate (CC-CC)",  300, 50., 200.},
  {"hZcandMt1_CC_Mass", "Elec pT - Z candidate (CC-CC)",  300, 50., 200.},
  {"hZcandMt2_CC_Mass", "Elec pT - Z candidate (CC-CC)", 300, 50., 200.},


  {"hZcandEta_All" , "Rapidity for Z boson (All)" , 60, -3., 3.},
  {"hZcandEta_CCCC", "Rapidity for Z boson (CCCC)", 60, -3., 3.},
  {"hZcandEta_CCEC", "Rapidity for Z boson (CCEC)", 60, -3., 3.},
  {"hZcandEta_ECEC", "Rapidity for Z boson (ECEC)", 60, -3., 3.},

  {"hZcandPt_All" , "Z candidate Pt (All)"  , 150, 0., 50.},
  {"hZcandPt_CCCC", "Z candidate Pt (CC-CC)", 150, 0., 50.},
  {"hZcandPt_CCEC", "Z candidate Pt (CC-EC)", 150, 0., 50.},
  {"hZcandPt_ECEC", "Z candidate Pt (EC-EC)", 150, 0., 50.},

  {"hZcandPx_All","Z candidate Px (All)", 150, -100., 100.},
  {"hZcandPy_All","Z candidate Py (All)", 150, -100., 100.},
  {"hZcandPz_All","Z candidate Pz (All)", 150, -100., 100.},

  {"hZcandPx_CCCC","Z candidate Px (CC-CC)", 150, -100., 100.},
  {"hZcandPy_CCCC","Z candidate Py (CC-CC)", 150, -100., 100.},
  {"hZcandPz_CCCC","Z candidate Pz (CC-CC)", 150, -100., 100.},

  {"hZcandPx_CCEC","Z candidate Px (CC-EC)", 150, -100., 100.},
  {"hZcandPy_CCEC","Z candidate Py (CC-EC)", 150, -100., 100.},
  {"hZcandPz_CCEC","Z candidate Pz (CC-EC)", 150, -100., 100.},


  {"hZcandPx_ECEC","Z candidate Px (EC-EC)", 150, -100., 100.},
  {"hZcandPy_ECEC","Z candidate Py (EC-EC)", 150, -100., 100.},
  {"hZcandPz_ECEC","Z candidate Pz (EC-EC)", 150, -100., 100.},


  {"hZcandAt_All" , "Z candidate At (All)"  , 150, 0., 50.},
  {"hZcandAt_CCCC", "Z candidate At (CC-CC)", 150, 0., 50.},
  {"hZcandAt_CCEC", "Z candidate At (CC-EC)", 150, 0., 50.},
  {"hZcandAt_ECEC", "Z candidate At (EC-EC)", 150, 0., 50.},

  {"hZcandAl_All" , "Z candidate Al (All)"  , 150, 0., 50.},
  {"hZcandAl_CCCC", "Z candidate Al (CC-CC)", 150, 0., 50.},
  {"hZcandAl_CCEC", "Z candidate Al (CC-EC)", 150, 0., 50.},
  {"hZcandAl_ECEC", "Z candidate Al (EC-EC)", 150, 0., 50.},

  {"hZcandMCPt_All" , "True Z candidate Pt (All)"  , 100, 0., 50.},
  {"hZcandMCPt_CCCC", "True Z candidate Pt (CC-CC)", 100, 0., 50.},
  {"hZcandMCPt_CCEC", "True Z candidate Pt (CC-EC)", 100, 0., 50.},
  {"hZcandMCPt_ECEC", "True Z candidate Pt (EC-EC)", 100, 0., 50.},

  {"hZcandMCPtDiff_All" , "True-Smear Z candidate Pt (All)"  , 200, -10., 10.},
  {"hZcandMCPtDiff_CCCC", "True-Smear Z candidate Pt (CC-CC)", 200, -10., 10.},
  {"hZcandMCPtDiff_CCEC", "True-Smear Z candidate Pt (CC-EC)", 200, -10., 10.},
  {"hZcandMCPtDiff_ECEC", "True-Smear Z candidate Pt (EC-EC)", 200, -10., 10.},

  {"hZcandMCPhiDiff_All" , "True-Smear Z candidate Phi (All)"  , 200, -TMath::Pi(), TMath::Pi()},
  {"hZcandMCPhiDiff_CCCC", "True-Smear Z candidate Phi (CC-CC)", 200, -TMath::Pi(), TMath::Pi()},
  {"hZcandMCPhiDiff_CCEC", "True-Smear Z candidate Phi (CC-EC)", 200, -TMath::Pi(), TMath::Pi()},
  {"hZcandMCPhiDiff_ECEC", "True-Smear Z candidate Pt (EC-EC)", 200, -TMath::Pi(), TMath::Pi()},

  {"hZcandElecpT_All", "Elec pT - Z candidate (All)", 300, 0., 100.},
  {"hZcandElec0pT_All", "Elec0 pT - Z candidate (All)", 300, 0., 100.},
  {"hZcandElec1pT_All", "Elec1 pT - Z candidate (All)", 300, 0., 100.},
  {"hZcandElecGenpT_All", "Gen Elec pT - Z candidate (All)", 300, 0., 100.},
  {"hZcandElecGen0pT_All", "Gen Elec0 pT - Z candidate (All)", 300, 0., 100.},
  {"hZcandElecGen1pT_All", "Gen Elec1 pT - Z candidate (All)", 300, 0., 100.},
  {"hZcandElecRawGenpT_All", "Raw Gen Elec pT - Z candidate (All)", 300, 0., 100.},
  {"hZcandElecRawGen0pT_All", "Raw Gen Elec0 pT - Z candidate (All)", 300, 0., 100.},
  {"hZcandElecRawGen1pT_All", "Raw Gen Elec1 pT - Z candidate (All)", 300, 0., 100.},

  {"hZcandDiffElecpT_All", "reco-truth Elec pT - Z candidate (All)", 200, -10., 10.},
  {"hZcandDiffElec0pT_All", "reco-truth Elec0 pT - Z candidate (All)", 200, -10., 10.},
  {"hZcandDiffElec1pT_All", "reco-truth Elec1 pT - Z candidate (All)", 200, -10., 10.},

  {"hZcandElecE_All", "Elec E - Z candidate (All)", 600, 0., 200.},
  {"hZcandElec0E_All", "Elec0 E - Z candidate (All)", 600, 0., 200.},
  {"hZcandElec1E_All", "Elec1 E - Z candidate (All)", 600, 0., 200.},
  {"hZcandElecGenE_All", "Gen Elec E - Z candidate (All)", 600, 0., 200.},
  {"hZcandElecGen0E_All", "Gen Elec0 E - Z candidate (All)", 600, 0., 200.},
  {"hZcandElecGen1E_All", "Gen Elec1 E - Z candidate (All)", 600, 0., 200.},
  {"hZcandElecRawGenE_All", "Raw Gen Elec E - Z candidate (All)", 600, 0., 200.},
  {"hZcandElecRawGen0E_All", "Raw Gen Elec0 E - Z candidate (All)", 600, 0., 200.},
  {"hZcandElecRawGen1E_All", "Raw Gen Elec1 E - Z candidate (All)", 600, 0., 200.},

  {"hZcandDiffElecE_All", "reco-truth Elec E - Z candidate (All)", 200, -10., 10.},
  {"hZcandDiffElec0E_All", "reco-truth Elec0 E - Z candidate (All)", 200, -10., 10.},
  {"hZcandDiffElec1E_All", "reco-truth Elec1 E - Z candidate (All)", 200, -10., 10.},

  {"hZcandElecEta_All", "Elec Eta - Z candidate (All)", 60, -3., 3.},
  {"hZcandElecDetEta_All", "Elec DetEta - Z candidate (All)", 60, -3., 3.},
  {"hZcandElecPhi_All", "Elec Phi - Z candidate (All)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiTrkAtDCA_All", "Elec Phi from TrkAtDCA for Z candidate (All)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiTrkAtEM3_All", "Elec Phi from TrkAtEM3 for Z candidate (All)", 64, 0., TMath::TwoPi()},
  {"hZcandElecDetPhiCALO_All",  "Elec DetPhi from CALO  for Z candidate (All)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiMod_All", "Elec PhiMod - Z candidate (All)", 64, 0., 1.},
  {"hZcandElecTrkPhiModEM3_All", "Elec Track PhiMod at EM3 - Z candidate (All)", 64, 0., 1.},
  {"hZcandRecoilPt_All", "Recoil Pt - Z candidate (All)", 150, 0., 50.},
  {"hZcandRecoilPhi_All", "Recoil Phi - Z candidate (All)", 64, 0., TMath::TwoPi()},
  {"hZcandRecoilPx_All", "Recoil Px - Z candidate (All)", 150, -50., 50.},
  {"hZcandRecoilPy_All", "Recoil Py - Z candidate (All)", 150, -50., 50.},
  {"hZcandMET_All", "MET - Z candidate (All)", 150, 0., 50.},
  {"hZcandMETx_All", "METx - Z candidate (All)", 150, -50., 50.},
  {"hZcandMETy_All", "METy - Z candidate (All)", 150, -50., 50.},
  {"hZcandMETPhi_All", "MET Phi - Z candidate (All)", 64, 0., TMath::TwoPi()},
  {"hZcandElecTrkPt_All", "Elec track pT - Z candidate (All)", 300, 0., 100.},
  {"hZcandElecTrkPtTight_All", "Elec track pT - Z candidate (All)", 300, 0., 100.},
  {"hZcandElecTrkCalMass_All", "Cal-Track Z Invariant Mass (All)", 400, 50., 150.},
  {"hZcandElecTrkCalMass_All_CC", "Cal-Track Z Invariant Mass (All CC Trk)", 400, 50., 150.},
  {"hZcandElecTrkPtOvE_All", "Track P_t /  E (All)", 200, 0., 1.1},
  {"hZcandElecTrkPtOvETight_All", "Track P_t /  E (All)", 200, 0., 1.1},
  {"hZcandElecTrkPtOvE_All_DetEta", "Track Deteta (All)", 30, -3.5, 3.5},
  {"hZcandElecUpara_All","U_parallel for Z events (All)", 120, -30., 30.},
  {"hZcandElecUperp_All","U_perp for Z events (All)", 120, -30., 30.},
  {"hZcandDeltaPhi_EM_Recoil_All", "open angle between EM and recoil (All)", 64, 0., TMath::Pi()},  
  {"hZcandDeltaPhi_EM_Met_All", "open angle between EM and met (All)", 64, 0., TMath::Pi()},  
  {"hZcandCosDeltaPhi_EM1_EM2_All" , "cosine open angle between EM1 and EM2 (All)", 100, -1 , -0.6 },
  {"hZcandDiffCosDeltaPhi_EM1_EM2_All" , "reco-truth cosine open angle between EM1 and EM2 (All)", 100, -0.002 , 0.002 },

  {"hZcandDeltaEta_EM1_EM2_All" , "delta eta between EM1 and EM2 (All)", 100, -1 , 1 },
  {"hZcandDiffDeltaEta_EM1_EM2_All" , "reco-truth delta eta between EM1 and EM2 (All)", 100, -0.02 , 0.02 },

 {"hZcandElecpX_All", "Elec pX - Z candidate (All)", 400, -200., 200.},
  {"hZcandElec0pX_All", "Elec0 pX - Z candidate (All)", 400, -200., 200.},
  {"hZcandElec1pX_All", "Elec1 pX - Z candidate (All)", 400, -200., 200.},
 {"hZcandElecpY_All", "Elec pY - Z candidate (All)", 400, -200., 200.},
  {"hZcandElec0pY_All", "Elec0 pY - Z candidate (All)", 400, -200., 200.},
  {"hZcandElec1pY_All", "Elec1 pY - Z candidate (All)", 400, -200., 200.},
 {"hZcandElecpZ_All", "Elec pZ - Z candidate (All)", 400, -200., 200.},
  {"hZcandElec0pZ_All", "Elec0 pZ - Z candidate (All)", 400, -200., 200.},
  {"hZcandElec1pZ_All", "Elec1 pZ - Z candidate (All)", 400, -200., 200.},

 {"hZcandElecpX_CCCC", "Elec pX - Z candidate (CC-CC)", 400, -200., 200.},
  {"hZcandElec0pX_CCCC", "Elec0 pX - Z candidate (CC-CC)", 400, -200., 200.},
  {"hZcandElec1pX_CCCC", "Elec1 pX - Z candidate (CC-CC)", 400, -200., 200.},
 {"hZcandElecpY_CCCC", "Elec pY - Z candidate (CC-CC)", 400, -200., 200.},
  {"hZcandElec0pY_CCCC", "Elec0 pY - Z candidate (CC-CC)", 400, -200., 200.},
  {"hZcandElec1pY_CCCC", "Elec1 pY - Z candidate (CC-CC)", 400, -200., 200.},
 {"hZcandElecpZ_CCCC", "Elec pZ - Z candidate (CC-CC)", 400, -200., 200.},
  {"hZcandElec0pZ_CCCC", "Elec0 pZ - Z candidate (CC-CC)", 400, -200., 200.},
  {"hZcandElec1pZ_CCCC", "Elec1 pZ - Z candidate (CC-CC)", 400, -200., 200.},

 {"hZcandElecpX_CCEC", "Elec pX - Z candidate (CC-EC)", 400, -200., 200.},
  {"hZcandElec0pX_CCEC", "Elec0 pX - Z candidate (CC-EC)", 400, -200., 200.},
  {"hZcandElec1pX_CCEC", "Elec1 pX - Z candidate (CC-EC)", 400, -200., 200.},
 {"hZcandElecpY_CCEC", "Elec pY - Z candidate (CC-EC)", 400, -200., 200.},
  {"hZcandElec0pY_CCEC", "Elec0 pY - Z candidate (CC-EC)", 400, -200., 200.},
  {"hZcandElec1pY_CCEC", "Elec1 pY - Z candidate (CC-EC)", 400, -200., 200.},
 {"hZcandElecpZ_CCEC", "Elec pZ - Z candidate (CC-EC)", 400, -200., 200.},
  {"hZcandElec0pZ_CCEC", "Elec0 pZ - Z candidate (CC-EC)", 400, -200., 200.},
  {"hZcandElec1pZ_CCEC", "Elec1 pZ - Z candidate (CC-EC)", 400, -200., 200.},

 {"hZcandElecpX_ECEC", "Elec pX - Z candidate (EC-EC)", 400, -200., 200.},
  {"hZcandElec0pX_ECEC", "Elec0 pX - Z candidate (EC-EC)", 400, -200., 200.},
  {"hZcandElec1pX_ECEC", "Elec1 pX - Z candidate (EC-EC)", 400, -200., 200.},
 {"hZcandElecpY_ECEC", "Elec pY - Z candidate (EC-EC)", 400, -200., 200.},
  {"hZcandElec0pY_ECEC", "Elec0 pY - Z candidate (EC-EC)", 400, -200., 200.},
  {"hZcandElec1pY_ECEC", "Elec1 pY - Z candidate (EC-EC)", 400, -200., 200.},
 {"hZcandElecpZ_ECEC", "Elec pZ - Z candidate (EC-EC)", 400, -200., 200.},
  {"hZcandElec0pZ_ECEC", "Elec0 pZ - Z candidate (EC-EC)", 400, -200., 200.},
  {"hZcandElec1pZ_ECEC", "Elec1 pZ - Z candidate (EC-EC)", 400, -200., 200.},


  // *** THE 3 HISTOS BELOW ADDED BY J0
  {"hZcandDeltaPhi_Recoil_Met_All", "open angle between Recoil and MET (All)", 64, 0., TMath::Pi()},
  {"hZcandDeltaPhi_Z_Recoil_All", "open angle between Recoil and pT(Z) (All)", 64, 0., TMath::Pi()},
  {"hZcandDeltaPhi_Z_Met_All", "open angle between Z and MET (All)", 64, 0., TMath::Pi()},

  {"hZcandElecpT_CCCC", "Elec pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElec0pT_CCCC", "Elec0 pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElec1pT_CCCC", "Elec1 pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecGenpT_CCCC", "Gen Elec pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecGen0pT_CCCC", "Gen Elec0 pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecGen1pT_CCCC", "Gen Elec1 pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecRawGenpT_CCCC", "Raw Gen Elec pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecRawGen0pT_CCCC", "Raw Gen Elec0 pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecRawGen1pT_CCCC", "Raw Gen Elec1 pT - Z candidate (CC-CC)", 300, 0., 100.},

  {"hZcandDiffElecpT_CCCC", "reco-truth Elec pT - Z candidate (CC-CC)", 200, -10., 10.},
  {"hZcandDiffElec0pT_CCCC", "reco-truth Elec0 pT - Z candidate (CC-CC)", 200, -10., 10.},
  {"hZcandDiffElec1pT_CCCC", "reco-truth Elec1 pT - Z candidate (CC-CC)", 200, -10., 10.},

  {"hZcandElecE_CCCC", "Elec E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElec0E_CCCC", "Elec0 E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElec1E_CCCC", "Elec1 E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecGenE_CCCC", "Gen Elec E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecGen0E_CCCC", "Gen Elec0 E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecGen1E_CCCC", "Gen Elec1 E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecRawGenE_CCCC", "Raw Gen Elec E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecRawGen0E_CCCC", "Raw Gen Elec0 E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecRawGen1E_CCCC", "Raw Gen Elec1 E - Z candidate (CC-CC)", 600, 0., 200.},

  {"hZcandDiffElecE_CCCC", "reco-truth Elec E - Z candidate (CC-CC)", 200, -10., 10.},
  {"hZcandDiffElec0E_CCCC", "reco-truth Elec0 E - Z candidate (CC-CC)", 200, -10., 10.},
  {"hZcandDiffElec1E_CCCC", "reco-truth Elec1 E - Z candidate (CC-CC)", 200, -10., 10.},

  {"hZcandElecEta_CCCC", "Elec Eta - Z candidate (CC-CC)", 60, -3., 3.},
  {"hZcandElecDetEta_CCCC", "Elec DetEta - Z candidate (CC-CC)", 60, -3., 3.},
  {"hZcandElecPhi_CCCC", "Elec Phi - Z candidate (CC-CC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiTrkAtDCA_CCCC", "Elec Phi from TrkAtDCA for Z candidate (CC-CC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiTrkAtEM3_CCCC", "Elec Phi from TrkAtEM3 for Z candidate (CC-CC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecDetPhiCALO_CCCC",  "Elec DetPhi from CALO  for Z candidate (CC-CC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiMod_CCCC", "Elec PhiMod - Z candidate (CC-CC)", 50, 0., 1.},
  {"hZcandElecTrkPhiModEM3_CCCC", "Elec Track PhiMod at EM3  - Z candidate (CC-CC)", 50, 0., 1.},
  {"hZcandRecoilPt_CCCC", "Recoil Pt - Z candidate (CCCC)", 150, 0., 50.},
  {"hZcandRecoilPhi_CCCC", "Recoil Phi - Z candidate (CCCC)", 64, 0., TMath::TwoPi()},
  {"hZcandRecoilPx_CCCC", "Recoil Px - Z candidate (CCCC)", 150, -50., 50.},
  {"hZcandRecoilPy_CCCC", "Recoil Py - Z candidate (CCCC)", 150, -50., 50.},
  {"hZcandMET_CCCC", "MET - Z candidate (CC-CC)", 150, 0., 50.},
  {"hZcandMETx_CCCC", "METx - Z candidate (CC-CC)", 150, -50., 50.},
  {"hZcandMETy_CCCC", "METy - Z candidate (CC-CC)", 150, -50., 50.},
  {"hZcandMETPhi_CCCC", "MET Phi - Z candidate (CC-CC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecTrkPt_CCCC", "Elec track pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecTrkPtTight_CCCC", "Elec track pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecTrkCalMass_CC", "Cal-Track Z Invariant Mass (CC Cluster)", 400, 50., 150.},
  {"hZcandElecTrkCalMass_CCCC", "Cal-Track Z Invariant Mass (CC Cluster)", 400, 50., 150.},
  {"hZcandElecTrkCalMass_CC_CC", "Cal-Track Z Invariant Mass (CC Cluster CC Trk)", 400, 50., 150.},
  {"hZcandElecTrkCalMass_CC_EC", "Cal-Track Z Invariant Mass (CC Cluster EC Trk)", 400, 50., 150.},
  {"hZcandElecTrkPtOvE_CC", "Track p#_T / E  (CC)", 200, 0., 1.1},
  {"hZcandElecTrkPtOvE_CC_DetEta", "Track DetEta", 30, -3.5, 3.5},
  {"hZcandElecTrkPtOvE_CCCC", "Track p#_T / E  (CC)", 200, 0., 1.1},
  {"hZcandElecTrkPtOvETight_CCCC", "Track p#_T / E  (CC)", 200, 0., 1.1},
  {"hZcandElecTrkPtOvE_DetEta_CCCC", "Track DetEta", 30, -3.5, 3.5},
  {"hZcandElecUpara_CCCC","U_parallel for Z events (CC-CC)", 120, -30., 30.},
  {"hZcandElecUperp_CCCC","U_perp for Z events (CC-CC)", 120, -30., 30.},
  {"hZcandDeltaPhi_EM_Recoil_CCCC", "open angle between EM and recoil (CC-CC)", 64, 0., TMath::Pi()},  
  {"hZcandDeltaPhi_EM_Met_CCCC", "open angle between EM and met (CC-CC)", 64, 0., TMath::Pi()},  
  {"hZcandCosDeltaPhi_EM1_EM2_CCCC", "open angle between EM1 and EM2 (CC-CC)", 100, -1 , -0.6 },  
  {"hZcandDiffCosDeltaPhi_EM1_EM2_CCCC", "reco-truth open angle between EM1 and EM2 (CC-CC)", 100, -0.002 , 0.002 },  

  {"hZcandDeltaEta_EM1_EM2_CCCC" , "delta eta between EM1 and EM2 (CC-CC)", 100, -1 , 1 },
  {"hZcandDiffDeltaEta_EM1_EM2_CCCC" , "reco-truth delta eta between EM1 and EM2 (CC-CC)", 100, -0.02 , 0.02 },

  // *** THE 3 HISTOS BELOW ADDED BY J0
  {"hZcandDeltaPhi_Recoil_Met_CCCC", "open angle between Recoil and MET (CC-CC)", 64, 0., TMath::Pi()},
  {"hZcandDeltaPhi_Z_Recoil_CCCC", "open angle between Recoil and pT(Z)(CC-CC)", 64, 0., TMath::Pi()},
  {"hZcandDeltaPhi_Z_Met_CCCC", "open angle between Z and MET (CC-CC)", 64, 0., TMath::Pi()},

  {"hZcandElecpT_CCEC", "Elec pT - Z candidate (EC-CC)", 300, 0., 100.},
  {"hZcandElec0pT_CCEC", "Elec0 pT - Z candidate (EC-CC)", 300, 0., 100.},
  {"hZcandElec1pT_CCEC", "Elec1 pT - Z candidate (EC-CC)", 300, 0., 100.},
  {"hZcandElecGenpT_CCEC", "Gen Elec pT - Z candidate (EC-CC)", 300, 0., 100.},
  {"hZcandElecGen0pT_CCEC", "Gen Elec0 pT - Z candidate (EC-CC)", 300, 0., 100.},
  {"hZcandElecGen1pT_CCEC", "Gen Elec1 pT - Z candidate (EC-CC)", 300, 0., 100.},
  {"hZcandElecRawGenpT_CCEC", "Raw Gen Elec pT - Z candidate (EC-CC)", 300, 0., 100.},
  {"hZcandElecRawGen0pT_CCEC", "Raw Gen Elec0 pT - Z candidate (EC-CC)", 300, 0., 100.},
  {"hZcandElecRawGen1pT_CCEC", "Raw Gen Elec1 pT - Z candidate (EC-CC)", 300, 0., 100.},

  {"hZcandDiffElecpT_CCEC", "reco-truth Elec pT - Z candidate (EC-CC)", 200, -10., 10.},
  {"hZcandDiffElec0pT_CCEC", "reco-truth Elec0 pT - Z candidate (EC-CC)", 200, -10., 10.},
  {"hZcandDiffElec1pT_CCEC", "reco-truth Elec1 pT - Z candidate (EC-CC)", 200, -10., 10.},

  {"hZcandElecE_CCEC", "Elec E - Z candidate (EC-CC)", 600, 0., 200.},
  {"hZcandElec0E_CCEC", "Elec0 E - Z candidate (EC-CC)", 600, 0., 200.},
  {"hZcandElec1E_CCEC", "Elec1 E - Z candidate (EC-CC)", 600, 0., 200.},
  {"hZcandElecGenE_CCEC", "Gen Elec E - Z candidate (EC-CC)", 600, 0., 200.},
  {"hZcandElecGen0E_CCEC", "Gen Elec0 E - Z candidate (EC-CC)", 600, 0., 200.},
  {"hZcandElecGen1E_CCEC", "Gen Elec1 E - Z candidate (EC-CC)", 600, 0., 200.},
  {"hZcandElecRawGenE_CCEC", "Raw Gen Elec E - Z candidate (EC-CC)", 600, 0., 200.},
  {"hZcandElecRawGen0E_CCEC", "Raw Gen Elec0 E - Z candidate (EC-CC)", 600, 0., 200.},
  {"hZcandElecRawGen1E_CCEC", "Raw Gen Elec1 E - Z candidate (EC-CC)", 600, 0., 200.},

  {"hZcandDiffElecE_CCEC", "reco-truth Elec E - Z candidate (EC-CC)", 200, -10., 10.},
  {"hZcandDiffElec0E_CCEC", "reco-truth Elec0 E - Z candidate (EC-CC)", 200, -10., 10.},
  {"hZcandDiffElec1E_CCEC", "reco-truth Elec1 E - Z candidate (EC-CC)", 200, -10., 10.},

  {"hZcandElecEta_CCEC", "Elec Eta - Z candidate (EC-CC)", 60, -3., 3.},
  {"hZcandElecDetEta_CCEC", "Elec DetEta - Z candidate (EC-CC)", 60, -3., 3.},
  {"hZcandElecPhi_CCEC", "Elec Phi - Z candidate (EC-CC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiTrkAtDCA_CCEC", "Elec Phi from TrkAtDCA for Z candidate (CC-EC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiTrkAtEM3_CCEC", "Elec Phi from TrkAtEM3 for Z candidate (CC-EC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecDetPhiCALO_CCEC",  "Elec DetPhi from CALO  for Z candidate (CC-EC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiMod_CCEC", "Elec PhiMod - Z candidate (EC-CC)", 64, 0., 1.},
  {"hZcandElecTrkPhiModEM3_CCEC", "Elec Track PhiMod at EM3 - Z candidate (EC-CC)", 64, 0., 1.},
  {"hZcandRecoilPt_CCEC", "Recoil Pt - Z candidate (CCEC)", 150, 0., 50.},
  {"hZcandRecoilPhi_CCEC", "Recoil Phi - Z candidate (CCEC)", 64, 0., TMath::TwoPi()},
  {"hZcandRecoilPx_CCEC", "Recoil Px - Z candidate (CCEC)", 150, -50., 50.},
  {"hZcandRecoilPy_CCEC", "Recoil Py - Z candidate (CCEC)", 150, -50., 50.},
  {"hZcandMET_CCEC", "MET - Z candidate (EC-CC)", 150, 0., 50.},
  {"hZcandMETx_CCEC", "METx - Z candidate (EC-CC)", 150, -50., 50.},
  {"hZcandMETy_CCEC", "METy - Z candidate (EC-CC)", 150, -50., 50.},
  {"hZcandMETPhi_CCEC", "MET Phi - Z candidate (EC-CC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecTrkPt_CCEC", "Elec track pT - Z candidate (EC-CC)", 300, 0., 100.},
  {"hZcandElecTrkPtTight_CCEC", "Elec track pT - Z candidate (EC-CC)", 300, 0., 100.},
  {"hZcandElecTrkCalMass_CCEC", "Cal-Track Z Invariant Mass ", 400, 50., 150.},
  {"hZcandElecTrkPtOvE_EC", "Track pt/E  (EC Cluster)", 200, 0., 1.1},
  {"hZcandElecTrkPtOvE_EC_DetEta", "Track DetEta (EC)", 30, -3.5, 3.5},
  {"hZcandElecTrkPtOvE_CCEC", "Track pt/E  (EC Cluster)", 200, 0., 1.1},
  {"hZcandElecTrkPtOvETight_CCEC", "Track pt/E  (EC Cluster)", 200, 0., 1.1},
  {"hZcandElecTrkPtOvE_DetEta_CCEC", "Track DetEta (EC)", 30, -3.5, 3.5},
  {"hZcandElecUpara_CCEC","U_parallel for Z events (CC-EC)", 120, -30., 30.},
  {"hZcandElecUperp_CCEC","U_perp for Z events (CC-EC)", 120, -30., 30.},
  {"hZcandDeltaPhi_EM_Recoil_CCEC", "open angle between EM and recoil (CC-EC)", 64, 0., TMath::Pi()},  
  {"hZcandDeltaPhi_EM_Met_CCEC", "open angle between EM and met (CC-EC)", 64, 0., TMath::Pi()},  
  {"hZcandCosDeltaPhi_EM1_EM2_CCEC", "open angle between EM1 and EM2 (CC-EC)", 100, -1 , -0.6 },  
  {"hZcandDiffCosDeltaPhi_EM1_EM2_CCEC", "reco-truth open angle between EM1 and EM2 (CC-EC)", 100, -0.002 , 0.002 },

  {"hZcandDeltaEta_EM1_EM2_CCEC" , "delta eta between EM1 and EM2 (CC-EC)", 100, -1 , 1 },
  {"hZcandDiffDeltaEta_EM1_EM2_CCEC" , "reco-truth delta eta between EM1 and EM2 (CC-EC)", 100, -0.02 , 0.02 },

  // *** THE 3 HISTOS BELOW ADDED BY J0
  {"hZcandDeltaPhi_Recoil_Met_CCEC", "open angle between Recoil and MET (CC-EC)", 64, 0., TMath::Pi()},
  {"hZcandDeltaPhi_Z_Recoil_CCEC", "open angle between Recoil and pT(Z)(CC-EC)", 64, 0., TMath::Pi()},
  {"hZcandDeltaPhi_Z_Met_CCEC", "open angle between Z and MET (CC-EC)", 64, 0., TMath::Pi()},

  {"hZcandElecpT_ECEC", "Elec pT - Z candidate (EC-EC)", 300, 0., 100.},
  {"hZcandElec0pT_ECEC", "Elec0 pT - Z candidate (EC-EC)", 300, 0., 100.},
  {"hZcandElec1pT_ECEC", "Elec1 pT - Z candidate (EC-EC)", 300, 0., 100.},
  {"hZcandElecGenpT_ECEC", "Gen Elec pT - Z candidate (EC-EC)", 300, 0., 100.},
  {"hZcandElecGen0pT_ECEC", "Gen Elec0 pT - Z candidate (EC-EC)", 300, 0., 100.},
  {"hZcandElecGen1pT_ECEC", "Gen Elec1 pT - Z candidate (EC-EC)", 300, 0., 100.},
  {"hZcandElecRawGenpT_ECEC", "Raw Gen Elec pT - Z candidate (EC-EC)", 300, 0., 100.},
  {"hZcandElecRawGen0pT_ECEC", "Raw Gen Elec0 pT - Z candidate (EC-EC)", 300, 0., 100.},
  {"hZcandElecRawGen1pT_ECEC", "Raw Gen Elec1 pT - Z candidate (EC-EC)", 300, 0., 100.},

  {"hZcandDiffElecpT_ECEC", "reco-truth Elec pT - Z candidate (EC-EC)", 200, -10., 10.},
  {"hZcandDiffElec0pT_ECEC", "reco-truth Elec0 pT - Z candidate (EC-EC)", 200, -10., 10.},
  {"hZcandDiffElec1pT_ECEC", "reco-truth Elec1 pT - Z candidate (EC-EC)", 200, -10., 10.},

  {"hZcandElecE_ECEC", "Elec E - Z candidate (EC-EC)", 600, 0., 200.},
  {"hZcandElec0E_ECEC", "Elec0 E - Z candidate (EC-EC)", 600, 0., 200.},
  {"hZcandElec1E_ECEC", "Elec1 E - Z candidate (EC-EC)", 600, 0., 200.},
  {"hZcandElecGenE_ECEC", "Gen Elec E - Z candidate (EC-EC)", 600, 0., 200.},
  {"hZcandElecGen0E_ECEC", "Gen Elec0 E - Z candidate (EC-EC)", 600, 0., 200.},
  {"hZcandElecGen1E_ECEC", "Gen Elec1 E - Z candidate (EC-EC)", 600, 0., 200.},
  {"hZcandElecRawGenE_ECEC", "Raw Gen Elec E - Z candidate (EC-EC)", 600, 0., 200.},
  {"hZcandElecRawGen0E_ECEC", "Raw Gen Elec0 E - Z candidate (EC-EC)", 600, 0., 200.},
  {"hZcandElecRawGen1E_ECEC", "Raw Gen Elec1 E - Z candidate (EC-EC)", 600, 0., 200.},

  {"hZcandDiffElecE_ECEC", "reco-truth Elec E - Z candidate (EC-EC)", 200, -10., 10.},
  {"hZcandDiffElec0E_ECEC", "reco-truth Elec0 E - Z candidate (EC-EC)", 200, -10., 10.},
  {"hZcandDiffElec1E_ECEC", "reco-truth Elec1 E - Z candidate (EC-EC)", 200, -10., 10.},

  {"hZcandElecEta_ECEC", "Elec Eta - Z candidate (EC-EC)", 60, -3., 3.},
  {"hZcandElecDetEta_ECEC", "Elec DetEta - Z candidate (EC-EC)", 60, -3., 3.},
  {"hZcandElecPhi_ECEC", "Elec Phi - Z candidate (EC-EC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiTrkAtDCA_ECEC", "Elec Phi from TrkAtDCA for Z candidate (EC-EC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiTrkAtEM3_ECEC", "Elec Phi from TrkAtEM3 for Z candidate (EC-EC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecDetPhiCALO_ECEC",  "Elec DetPhi from CALO  for Z candidate (EC-EC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecPhiMod_ECEC", "Elec PhiMod - Z candidate (EC-EC)", 64, 0., 1.},
  {"hZcandElecTrkPhiModEM3_ECEC", "Elec Track PhiMod at EM3 - Z candidate (EC-EC)", 64, 0., 1.},
  {"hZcandRecoilPt_ECEC", "Recoil Pt - Z candidate (ECEC)", 150, 0., 50.},
  {"hZcandRecoilPhi_ECEC", "Recoil Phi - Z candidate (ECEC)", 64, 0., TMath::TwoPi()},
  {"hZcandRecoilPx_ECEC", "Recoil Px - Z candidate (ECEC)", 150, -50., 50.},
  {"hZcandRecoilPy_ECEC", "Recoil Py - Z candidate (ECEC)", 150, -50., 50.},
  {"hZcandMET_ECEC", "MET - Z candidate (EC-EC)", 150, 0., 50.},
  {"hZcandMETx_ECEC", "METx - Z candidate (EC-EC)", 150, -50., 50.},
  {"hZcandMETy_ECEC", "METy - Z candidate (EC-EC)", 150, -50., 50.},
  {"hZcandMETPhi_ECEC", "MET Phi - Z candidate (EC-EC)", 64, 0., TMath::TwoPi()},
  {"hZcandElecTrkPt_ECEC", "Elec track pT - Z candidate (EC-EC)", 300, 0., 100.},
  {"hZcandElecTrkPtTight_ECEC", "Elec track pT - Z candidate (EC-EC)", 300, 0., 100.},
  {"hZcandElecTrkPtOvETight_ECEC", "Track pt/E  (EC Cluster)", 200, 0., 1.1},
  {"hZcandElecTrkPtOvE_ECEC", "Track pt/E  (EC Cluster)", 200, 0., 1.1},
  {"hZcandElecTrkCalMass_ECEC","Cal-Track Z Invariant Mass ", 400, 50., 150.},
  {"hZcandElecUpara_ECEC","U_parallel for Z events (EC-EC)", 120, -30., 30.},
  {"hZcandElecUperp_ECEC","U_perp for Z events (EC-EC)", 120, -30., 30.},
  {"hZcandDeltaPhi_EM_Recoil_ECEC", "open angle between EM and recoil (EC-EC)", 64, 0., TMath::Pi()},  
  {"hZcandDeltaPhi_EM_Met_ECEC", "open angle between EM and met (EC-EC)", 64, 0., TMath::Pi()},  
  {"hZcandCosDeltaPhi_EM1_EM2_ECEC", "open angle between EM1 and EM2 (EC-EC)", 100, -1 , -0.6 },  
  {"hZcandDiffCosDeltaPhi_EM1_EM2_ECEC", "reco-truth open angle between EM1 and EM2 (EC-EC)", 100, -0.002 , 0.002 },

  {"hZcandDeltaEta_EM1_EM2_ECEC" , "delta eta between EM1 and EM2 (EC-EC)", 100, -1 , 1 },
  {"hZcandDiffDeltaEta_EM1_EM2_ECEC" , "reco-truth delta eta between EM1 and EM2 (EC-EC)", 100, -0.02 , 0.02 },

  // *** THE 3 HISTOS BELOW ADDED BY J0
  {"hZcandDeltaPhi_Recoil_Met_ECEC", "open angle between Recoil and MET (EC-EC)", 64, 0., TMath::Pi()},
  {"hZcandDeltaPhi_Z_Recoil_ECEC", "open angle between Recoil and pT(Z)(EC-EC)", 64, 0., TMath::Pi()},
  {"hZcandDeltaPhi_Z_Met_ECEC", "open angle between Z and MET (EC-EC)", 64, 0., TMath::Pi()},

  {"hZcandMass_Category", "Z mass for different physics eta categories", 400, 50., 150.},
  {"hZcandElecPt_Category", "Electron pT for different physics eta categories", 300, 0., 100.},
  {"hZcandMass_Category_DetEta", "Z mass for different detector eta categories", 400, 50., 150.},
  {"hZcandMass_Category_PhiMod", "Z mass for different phimod categories", 400, 50., 150.},
  {"hZcandMass_Category_TruePhiMod", "Z mass for different true phimod categories", 400, 50., 150.},
  {"hZcandMass_CrackCBTemplates_Category_PhiMod", "Z mass for different phimod categories for Crystal Ball parameter templates", 400, 50., 150.},
  {"hZcandElecPt_Category_DetEta", "Electron pT for different detector eta categories", 300, 0., 100.},
  {"hZcandMass_Category_all", "Z mass for all categories", 400, 50., 150.},
  {"hZcandElecPt_Category_all", "Electron pT for all categories", 300, 0., 100.},
  // maps for Z mass, energy scale/offset, sampling/noise term
  // number of bins, x min and max will be modified inside the code
  {"histd1map_ZMassTemplates", "Map for Z Mass templates", 100, 89., 92.},
  {"histd1map_TBalphaTemplates", "Map for  TB alpha templates", 100, 0.9, 1.1},
  {"histd2map_TBbetaTemplates", "Map for TB beta templates", 100, 0.9, 1.1},
  {"histd1map_CCMSTemplates", "Map for MomentumStudy  templates", 100, 0.9, 1.1},
  {"histd2map_CCMSTemplates", "Map for MomentumStudy templates", 100, 0.9, 1.1},
  {"histd1map_ECMSTemplates", "Map for MomentumStudy  CC-EC templates", 100, 0.9, 1.1},
  {"histd2map_ECMSTemplates", "Map for MomentumStudy CC-EC templates", 100, 0.9, 1.1},
  {"histd1map_RADTemplates", "Map for EnergyLoss templates", 100, 0.9, 1.1},
  {"histd2map_RADTemplates2", "Map for EnergyLoss templates2", 100, 0.9, 1.1},
  {"histd1map_EScaleOffsetTemplates", "Map for energy scale templates", 100, 0.9, 1.1},
  {"histd2map_EScaleOffsetTemplates", "Map for energy offset templates", 100, 0.9, 1.1},
  {"histd1map_SamplingConstantTemplates", "Map for sampling term templates", 100, 0.9, 1.1},
  {"histd2map_SamplingConstantTemplates", "Map for constant term templates", 100, 0.9, 1.1},
  {"histd1map_eNoiseTemplates", "Map for eNoise term templates", 100, 0.9, 1.1},
  {"histd1map_CrackCB_alphaOffsetSlopeTemplates", "Map for Crystal Ball paremeter templates", 100, 0.9, 1.1},
  {"histd2map_CrackCB_alphaOffsetSlopeTemplates", "Map for Crystal Ball paremeter templates", 100, 0.9, 1.1},
  // maps for studying hadronic momentum scale, hadronic sampling term and # of minbias events to overlay
  // number of bins, x min and max will be modified inside the code
  {"histd1map_HadronicScaleTemplates", "Map for hadronic scale A templates", 100, 0.9, 1.1},
  {"histd2map_HadronicScaleTemplates", "Map for hadronic scale B templates", 100, 0.9, 1.1},
  {"histd1map_HadronicResolutionTemplates", "Map for hadronic sampling term templates", 100, 0.9, 1.1},
  {"histd2map_HadronicResolutionTemplates", "Map for number of overlaid minbias events  templates", 100, 0.9, 1.1},
  {"histd1map_HadronicScaleBifurcateTemplates", "Map for hadronic scale_HAD_bifurcate_A templates", 100, 0.9, 1.1},
  {"histd2map_HadronicScaleBifurcateTemplates", "Map for hadronic scale_HAD_bifurcate_B templates", 100, 0.9, 1.1},
  {"histd1map_HadronicScale2BifurcateTemplates", "Map for hadronic scale_HAD_bifurcate_A templates", 100, 0.9, 1.1},
  {"histd2map_HadronicScale2BifurcateTemplates", "Map for hadronic scale_HAD_bifurcate_B templates", 100, 0.9, 1.1},
  {"histd3map_HadronicScale2BifurcateTemplates", "Map for hadronic scale_HAD_bifurcate_Tau templates", 100, 0.9, 1.1},
  {"histd1map_HadronicResolutionBifurcateTemplates", "Map for hadronic Relsampling_HAD_bifurcate_A templates", 100, 0.9, 1.1},
  {"histd2map_HadronicResolutionBifurcateTemplates", "Map for hadronic Relsampling_HAD_bifurcate_B templates", 100, 0.9, 1.1},
  {"histd1map_HadronicResolution2BifurcateTemplates", "Map for hadronic Relsampling_HAD_bifurcate2_A templates", 100, 0.9, 1.1},
  {"histd2map_HadronicResolution2BifurcateTemplates", "Map for hadronic alpha_mb templates", 100, 0.9, 1.1},
  {"histd1map_HadronicResolution3BifurcateTemplates", "Map for hadronic Relsampling_HAD_bifurcate3_A templates", 100, 0.9, 1.1},
  {"histd2map_HadronicResolution3BifurcateTemplates", "Map for hadronic alpha_mb templates", 100, 0.9, 1.1},
  {"histd3map_HadronicResolution3BifurcateTemplates", "Map for hadronic alpha_zb templates", 100, 0.9, 1.1},
  {"histd1map_HadronicPhiSmearingBifurcateTemplates", "Map for hadronic Relphi_HAD_bifurcate_A templates", 100, 0.9, 1.1},
  {"histd2map_HadronicPhiSmearingBifurcateTemplates", "Map for hadronic Relphi_HAD_bifurcate_B templates", 100, 0.9, 1.1},
  // for fZ studies
  {"hZcandElecPt_fz", "Electron pT for different fz categories", 100, 20., 70.},
  {"hZcandElec1Pt_fz", "Electron1 pT for different fz categories", 100, 20., 70.},
  {"hZcandElec2Pt_fz", "Electron2 pT for different fz categories", 100, 20., 70.},
  {"hZcandElecE_fz", "Electron E for different fz categories", 200, 20., 120.},
  {"hZcandElec1E_fz", "Electron1 E for different fz categories", 200, 20., 120.},
  {"hZcandElec2E_fz", "Electron2 E for different fz categories", 200, 20., 120.},
  {"hZcandElecEta_fz", "Elec Eta - Z candidate fz categories", 60, -3., 3.},
  {"hZcandElec1Eta_fz", "Elec Eta - Z candidate fz categories", 60, -3., 3.},
  {"hZcandElec2Eta_fz", "Elec Eta - Z candidate fz categories", 60, -3., 3.},
  {"hZcandElecDetEta_fz", "Elec DetEta - Z candidate fz categories)", 60, -3., 3.},
  {"hZcandElec1DetEta_fz", "Elec DetEta - Z candidate fz categories)", 60, -3., 3.},
  {"hZcandElec2DetEta_fz", "Elec DetEta - Z candidate fz categories)", 60, -3., 3.},
  {"hZcandMass_CCCC_fz", "Z candidate mass (CCCC) by fz categories)", 400, 50., 150.},
  {"hZcandMass_CCCC_fz_Coarse", "Z candidate mass (CCCC) by fz categories)", 400, 50., 150.},
  //new plots by Jun Guo
  {"hZcandLumi_All", "Z candidate (All) lumi profile)", 250, 0., 10.},
  {"hZcandLumi_CCCC", "Z candidate (CCCC) lumi profile)", 250, 0., 10.},
  {"hZcandLumi_CCEC", "Z candidate (CCEC) lumi profile)", 250, 0., 10.},
  {"hZcandLumi_ECEC", "Z candidate (ECEC) lumi profile)", 250, 0., 10.},
  //MW
  // for different electron Pt bins 
  {"hZcandScalarEt_ElecPtBin", "ScalarEt for different electron pT bins", 300, 0., 300.},  
  {"hZcandSEToverEpt_ElecPtBin", "SET over epT for different electron pT bins", 100, 0., 5.},  
  {"hZcandScalarEt_Tail", "ScalarEt for epTs in the tail", 300, 0., 300.},  
  {"hZcandSEToverEpt_Tail", "SET over epT for epTs in the tail", 100, 0., 5.}, 
  
  {"hZcandScalarEt_All", "Z candidate (All) scalarEt", 300, 0., 300.},
  {"hZcandScalarEt_CCCC", "Z candidate (CCCC) scalarEt", 300, 0., 300.},
  {"hZcandScalarEt_CCEC", "Z candidate (CCEC) scalarEt", 300, 0., 300.},
  {"hZcandScalarEt_ECEC", "Z candidate (ECEC) scalarEt", 300, 0., 300.},

  {"hZcandScalarEtZB_All", "Z candidate (All) scalarEt of ZB", 300, 0., 300.},
  {"hZcandScalarEtZB_CCCC", "Z candidate (CCCC) scalarEt of ZB", 300, 0., 300.},
  {"hZcandScalarEtZB_CCEC", "Z candidate (CCEC) scalarEt of ZB", 300, 0., 300.},
  {"hZcandScalarEtZB_ECEC", "Z candidate (ECEC) scalarEt of ZB", 300, 0., 300.},

  {"hZcandScalarEtZBNoScale_All", "Z candidate (All) scalarEt of ZB no _scale_zb", 300, 0., 300.},
  {"hZcandScalarEtZBNoScale_CCCC", "Z candidate (CCCC) scalarEt of ZB no _scale_zb", 300, 0., 300.},
  {"hZcandScalarEtZBNoScale_CCEC", "Z candidate (CCEC) scalarEt of ZB no _scale_zb", 300, 0., 300.},
  {"hZcandScalarEtZBNoScale_ECEC", "Z candidate (ECEC) scalarEt of ZB no _scale_zb", 300, 0., 300.},

  {"hZcandScalarEt_CCCC_bin", "Z candidate (CCCC) scalarEt", 300, 0., 300.},
  {"hZcandSqrtScalarEt_CCCC_bin", "Z candidate (CCCC) sqrt(scalarEt)", 400, 0., 15.},
  {"hZcandScalarEt_CCCC_genZPt_bin", "Z candidate (CCCC) scalarEt", 300, 0., 300.},
  {"hZcandSqrtScalarEt_CCCC_genZPt_bin", "Z candidate (CCCC) sqrt(scalarEt)", 400, 0., 15.},

  {"hZcandSqrtScalarEt_All", "Z candidate (All) sqrt(scalarEt))", 400, 0., 15.},
  {"hZcandSqrtScalarEt_CCCC", "Z candidate (CCCC) sqrt(scalarEt))", 400, 0., 15.},
  {"hZcandSqrtScalarEt_CCEC", "Z candidate (CCEC) sqrt(scalarEt))", 400, 0., 15.},
  {"hZcandSqrtScalarEt_ECEC", "Z candidate (ECEC) sqrt(scalarEt))", 400, 0., 15.},

  {"hZcandElecE_All", "Elec E - Z candidate (All)", 600, 0., 200.},
  {"hZcandElecE_CCCC", "Elec E - Z candidate (CCCC)", 600, 0., 200.},
  {"hZcandElecE_CCEC", "Elec E - Z candidate (CCEC)", 600, 0., 200.},
  {"hZcandElecE_ECEC", "Elec E - Z candidate (ECEC)", 600, 0., 200.},

  {"hZcandElecOpenAngle_All", "Elec Open Angle - Z candidate (All)", 20, -1., 1.},
  {"hZcandElecOpenAngle_CCCC", "Elec Open Angle - Z candidate (CCCC)", 20, -1., 1.},
  {"hZcandElecOpenAngle_CCEC", "Elec Open Angle - Z candidate (CCEC)", 20, -1., 1.},
  {"hZcandElecOpenAngle_ECEC", "Elec Open Angle - Z candidate (ECEC)", 20, -1., 1.},

  // mass for track matching efficiency studies in different eta and vtx region
  {"ZMass_vs_Eta_Before_Trk_Vtx", "Z mass for different vertex and eta", 150, 0., 150.},
  {"ZMass_vs_Eta_After_Trk_Vtx", "Z mass for different vertex and eta", 150, 0., 150.},
  {"loose_ZMass_vs_Eta_Before_Trk_Vtx", "Z mass for different vertex and eta", 150, 0., 150.},
  {"loose_ZMass_vs_Eta_After_Trk_Vtx", "Z mass for different vertex and eta", 150, 0., 150.},
  // Z pT eff
  {"ZCandpT_gen", "Z pT", 100, 0., 50.},
  {"ZCandpT_gen_selected", "Z pT", 100, 0., 50.},
  {"ZCandpT_gen_selected_CCCC", "Z pT", 100, 0., 50.},
  {"ZCandpT_gen_selected_CCEC", "Z pT", 100, 0., 50.},
  {"ZCandpT_gen_selected_ECEC", "Z pT", 100, 0., 50.}, 

  {"", "", 0, 0, 0}
};

// more histograms for loose track Efficiency studies
// these would be used as signal to fit the data with signal+bkgd
#define _NPTBINS_ 23
#define _PTBINS_  {0.,25.,27.,29.,31.,33.,35.,37.,39.,41., 43.,45.,47.,49.,51.,53.,57.,61.,65.,70., 75.,80.,90.,100.}
static HIST_2D_VARBIN_Y ZCand_Hist_2D_VARBIN_Y[]={
	{"loose_ZMass_vs_varbinPt_Before_Trk_CC","M vs ElecPT Before Loose Track Requirement", 90, 50., 140., _NPTBINS_, _PTBINS_ },
	{"loose_ZMass_vs_varbinPt_After_Trk_CC","M vs ElecPT After Loose Track Requirement", 90, 50., 140., _NPTBINS_, _PTBINS_ },
	{"","", 0, 0., 0., 0, {0.} }
};
#undef _NPTBINS_
#undef _PTBINS_

//############################
//Kappa and underlying events
//############################
static HIST_1D RECOIL_Hist[]={
   //All
  {"hZcandEtaBalance_All", "Balance in eta direction", 150, -25., 25.},
  {"hZcandXiBalance_All", "Balance in xi direction", 150, -25., 25.},
  {"hZcandEtaImBalance_All", "ImBalance in eta direction", 150, -25., 25.},
  {"hZcandXiImBalance_All", "ImBalance in xi direction", 150, -25., 25.},

   //CC-CC
  {"hZcandEtaBalance_CCCC", "Balance in eta direction", 150, -25., 25.},
  {"hZcandXiBalance_CCCC", "Balance in xi direction", 150, -25., 25.},
  {"hZcandEtaImBalance_CCCC", "ImBalance in eta direction", 150, -25., 25.},
  {"hZcandXiImBalance_CCCC", "ImBalance in xi direction", 150, -25., 25.},

   //CC-CC and CC-EC
  {"hZcandEtaBalance_CCEC", "Balance in eta direction", 150, -25., 25.},
  {"hZcandXiBalance_CCEC", "Balance in xi direction", 150, -25., 25.},
  {"hZcandEtaImBalance_CCEC", "ImBalance in eta direction", 150, -25., 25.},
  {"hZcandXiImBalance_CCEC", "ImBalance in xi direction", 150, -25., 25.},

   //EC-EC
  {"hZcandEtaBalance_ECEC", "Balance in eta direction", 150, -25., 25.},
  {"hZcandXiBalance_ECEC", "Balance in xi direction", 150, -25., 25.},
  {"hZcandEtaImBalance_ECEC", "ImBalance in eta direction", 150, -25., 25.},
  {"hZcandXiImBalance_ECEC", "ImBalance in xi direction", 150, -25., 25.},

   // eta and phi balance/imbalance, recoil and met for different pT_ee bins
  {"hZcandEtaBalance_bin", "eta-balance for smeared Z pT",150, -25., 25.},        // eta balance bin 
  {"hZcandXiBalance_bin", "xi-balance for smeared Z pT",150, -25., 25.},         // xi balance bin 

  {"hZcandEtaImBalance_bin", "eta-imbalance for smeared Z pT",150, -25., 25.},      // eta imbalance bin
  {"hZcandXiImBalance_bin", "xi-imbalance for smeared Z pT",150, -25., 25.},       // xi imbalance bin

  {"hZcandEtaImBalance_ZPt_Projected_bin", "eta-imbalance for smeared Z pT projected along eta axis",150, -25., 25.},      // eta imbalance bin
  {"hZcandXiImBalance_ZPt_Projected_bin", "xi-imbalance for smeared Z pT projected along eta axis",150, -25., 25.},       // xi imbalance bin
  {"hZcandEtaImBalance_genZPt_bin", "eta-imbalance for generator level Z pT",150, -25., 25.},      // eta imbalance bin
  {"hZcandXiImBalance_genZPt_bin", "xi-imbalance for generator level Z pT",150, -25., 25.},       // xi imbalance bin
  {"hZcandRecoilPt_genZPt_bin", "recoil pT for generator level Z pT", 150, 0., 50.},       // recoil pT
  {"hZcandMCPtDiff_genZPt_bin", "MC Z pT - reco Z pT for generator level Z pT", 200, -10., 10.},       // mc Z pT - reco Z pT
  {"hZcandMCPtDiff_bin", "MC Z pT - reco Z pT for smeared Z pT", 200, -10., 10.},       // mc Z pT - reco Z pT
  {"hZcandMCPhiDiff_bin", "MC Z phi - reco Z phi for smeared Z pT", 200, -TMath::Pi(), TMath::Pi()},       // mc Z pT - reco Z pT
  {"hZcandEtaImBalance_all_bins", "eta-imbalance",150, -25., 25.},      // eta imbalance for all pTee bins
  
  {"hZcandMass_bin", "Z candidate Mass (CC-CC)"  , 400, 50., 150.}, // Mee for pTZ bins

  {"hZcandDiffMass_bin", "reco-truth Z candidate Mass (CC-CC)"  , 200, -10., 10.}, // Mee for pTZ bins

  {"hZcandElecpT_bin", "Elec pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElec0pT_bin", "Elec0 pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElec1pT_bin", "Elec1 pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecGenpT_bin", "Gen Elec pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecGen0pT_bin", "Gen Elec0 pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecGen1pT_bin", "Gen Elec1 pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecRawGenpT_bin", "Raw Gen Elec pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecRawGen0pT_bin", "Raw Gen Elec0 pT - Z candidate (CC-CC)", 300, 0., 100.},
  {"hZcandElecRawGen1pT_bin", "Raw Gen Elec1 pT - Z candidate (CC-CC)", 300, 0., 100.},
  
  {"hZcandDiffElecpT_bin", "reco-truth Elec pT - Z candidate (CC-CC)", 200, -10., 10.},
  {"hZcandDiffElec0pT_bin", "reco-truth Elec0 pT - Z candidate (CC-CC)", 200, -10., 10.},
  {"hZcandDiffElec1pT_bin", "reco-truth Elec1 pT - Z candidate (CC-CC)", 200, -10., 10.},

  {"hZcandElecE_bin", "Elec E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElec0E_bin", "Elec0 E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElec1E_bin", "Elec1 E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecGenE_bin", "Gen Elec E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecGen0E_bin", "Gen Elec0 E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecGen1E_bin", "Gen Elec1 E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecRawGenE_bin", "Raw Gen Elec E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecRawGen0E_bin", "Raw Gen Elec0 E - Z candidate (CC-CC)", 600, 0., 200.},
  {"hZcandElecRawGen1E_bin", "Raw Gen Elec1 E - Z candidate (CC-CC)", 600, 0., 200.},
  
  {"hZcandDiffElecE_bin", "reco-truth Elec E - Z candidate (CC-CC)", 200, -10., 10.},
  {"hZcandDiffElec0E_bin", "reco-truth Elec0 E - Z candidate (CC-CC)", 200, -10., 10.},
  {"hZcandDiffElec1E_bin", "reco-truth Elec1 E - Z candidate (CC-CC)", 200, -10., 10.},

  // *** THE HISTO BELOW ADDED BY J0
  {"hZcandPee_eta_bin", "pT(Z)_eta", 150, 0., 50.},  // Pee_eta bin
  
  {"hZcandPt_bin", "Z Pt - Z candidate (CCCC)", 150, 0., 50.},
  {"hZcandPt_Projected_bin", "Z Pt projected along eta axis - Z candidate (CCCC)", 150, 0., 50.},
  {"hZcandRecoilPt_bin", "Recoil Pt - Z candidate (CCCC)", 150, 0., 50.},
  {"hZcandRecoilPhi_bin", "Recoil Phi - Z candidate (CCCC)", 64, 0., TMath::TwoPi()},
  {"hZcandRecoilPx_bin", "Recoil Px - Z candidate (CCCC)", 150, -50., 50.},
  {"hZcandRecoilPy_bin", "Recoil Py - Z candidate (CCCC)", 150, -50., 50.},
  {"hZcandMET_bin", "MET - Z candidate (CC-CC)", 150, 0., 50.},
  {"hZcandMETx_bin", "METx - Z candidate (CC-CC)", 150, -50., 50.},
  {"hZcandMETy_bin", "METy - Z candidate (CC-CC)", 150, -50., 50.},
  {"hZcandMETPhi_bin", "MET Phi - Z candidate (CC-CC)", 64, 0., TMath::TwoPi()},
  {"hZcandDeltaPhi_EM_Recoil_bin", "open angle between EM and recoil (CC-CC)", 64, 0., TMath::Pi()},  
  {"hZcandDeltaPhi_EM_Met_bin", "open angle between EM and met (CC-CC)", 64, 0., TMath::Pi()},  
  {"hZcandCosDeltaPhi_EM1_EM2_bin", "open angle between EM1 and EM2 (CC-CC)", 100, -1 , -0.6 },  
  {"hZcandDiffCosDeltaPhi_EM1_EM2_bin", "reco-truth open angle between EM1 and EM2 (CC-CC)", 100, -0.002 , 0.002},  

  {"hZcandDeltaEta_EM1_EM2_bin", "delta eta between EM1 and EM2 (CC-CC)", 100, -1 , 1 },  
  {"hZcandDiffDeltaEta_EM1_EM2_bin", "reco-truth delta eta between EM1 and EM2 (CC-CC)", 100, -0.02 , 0.02 },  

  // *** THE HISTOS BELOW ADDED BY J0
  {"hZcandDeltaPhi_Recoil_Met_bin", "open angle between Recoil and MET (CC-CC)", 64, 0., TMath::Pi()},
  {"hZcandDeltaPhi_Z_Recoil_bin", "open angle between Recoil and Z (CC-CC)", 64, 0., TMath::Pi()},
  {"hZcandDeltaPhiUnfolded_Z_Recoil_bin", "open angle between Recoil and Z (CC-CC)", 64, -TMath::Pi(), TMath::Pi()},
  {"hZcandDeltaPhi_Z_Met_bin", "open angle between Z and MET (CC-CC)", 64, 0., TMath::Pi()},

  {"hZcandOpeningAngle_bin", "di-electron opening angle (CC-CC)", 640, 0., TMath::Pi()},
  {"hZcandEtaImBalancePt1_bin", "eta-imbalance part 1 for smeared Z pT",150, -25., 25.},
  {"hZcandEtaImBalancePt2_bin", "eta-imbalance part 2 for smeared Z pT",150, -25., 25.},

  {"hZcandPee_eta_CCCC", "pT(Z)_eta_CCCC",150, 0., 50.},
  {"hZcandDeltaPhi_EM1_EM2_CCCC", "Delta phi (ee) CCCC", 64, 0, TMath::TwoPi()},

  {"hZcandPee_eta_All", "pT(Z)_eta_All",150, 0., 50.},
  {"hZcandDeltaPhi_EM1_EM2_All", "Delta phi (ee) All", 64, 0, TMath::TwoPi()},

  {"hZcandPee_eta_CCEC", "pT(Z)_eta_CCEC",150, 0., 50.},
  {"hZcandDeltaPhi_EM1_EM2_CCEC", "Delta phi (ee) CCEC", 64, 0, TMath::TwoPi()},

  {"hZcandPee_eta_ECEC", "pT(Z)_eta_ECECC",150, 0., 50.},
  {"hZcandDeltaPhi_EM1_EM2_ECEC", "Delta phi (ee) ECEC", 64, 0, TMath::TwoPi()},

  {"", "", 0, 0, 0}
};

static HIST_2D RECOIL_Hist_2D[]={
  {"hZcandPeeReco_All", "P_ee vs Recoil in eta direction", 25, 0., 25., 80, -40., 40.},
  {"hZcandPeeBalance_All", "P_ee vs Balance in eta direction", 10, 0., 20., 80, -40., 40},
  {"hZcandKappa3_All", "Pow(P_ee, 2) vs Pow(P_e1 + P_e2 + MET, 2)", 20, 0., 500., 80, 0., 800.},

  {"hZcandPeeReco_CCCC", "P_ee vs Recoil in eta direction", 25, 0., 25., 80, -40., 40.},
  {"hZcandPeeBalance_CCCC", "P_ee vs Balance in eta direction", 10, 0., 20., 80, -40., 40},
  {"hZcandKappa3_CCCC", "Pow(P_ee, 2) vs Pow(P_e1 + P_e2 + MET, 2)", 20, 0., 500., 80, 0., 800.},

  {"hZcandPeeReco_CCEC", "P_ee vs Recoil in eta direction", 25, 0., 25., 80, -40., 40.},
  {"hZcandPeeBalance_CCEC", "P_ee vs Balance in eta direction", 10, 0., 20., 80, -40., 40},
  {"hZcandKappa3_CCEC", "Pow(P_ee, 2) vs Pow(P_e1 + P_e2 + MET, 2)", 20, 0., 500., 80, 0., 800.},

  {"hZcandPeeReco_ECEC", "P_ee vs Recoil in eta direction", 25, 0., 25., 80, -40., 40.},
  {"hZcandPeeBalance_ECEC", "P_ee vs Balance in eta direction", 10, 0., 20., 80, -40., 40.},
  {"hZcandKappa3_ECEC", "Pow(P_ee, 2) vs Pow(P_e1 + P_e2 + MET, 2)", 20, 0., 500., 80, 0., 800.},

  {"hZcand_Recoil_pT_All", "pT_Z vs Hadronic Response (All)", 30, 0., 30., 40, 0., 1.5},
  {"hZcand_Recoil_pT_CCCC", "pT_Z vs Hadronic Response (CCCC)", 30, 0., 30., 40, 0., 1.5},
  {"hZcand_Recoil_pT_CCEC", "pT_Z vs Hadronic Response (CCEC)", 30, 0., 30., 40, 0., 1.5},
  {"hZcand_Recoil_pT_ECEC", "pT_Z vs Hadronic Response (ECEC)", 30, 0., 30., 40, 0., 1.5},

  //By Jun Guo
  {"hZcandPeeImBalance_All", "P_ee vs ImBalance(All) in eta direction", 10, 0., 20., 80, -40., 40},
  {"hZcandPeeImBalance_CCCC", "P_ee vs ImBalance(CCCC) in eta direction", 10, 0., 20., 80, -40., 40},
  {"hZcandPeeImBalance_CCEC", "P_ee vs ImBalance(CCEC) in eta direction", 10, 0., 20., 80, -40., 40},
  {"hZcandPeeImBalance_ECEC", "P_ee vs ImBalance(ECEC) in eta direction", 10, 0., 20., 80, -40., 40},

  {"", "", 0, 0, 0, 0, 0, 0}
};
//more histograms for zpt dphi reweighting
#define _NXBINS_ 65
#define _XBINS_  {0, 2.521278, 2.541288, 2.561299, 2.581309, 2.601319, 2.621329, 2.641339, 2.661349, 2.681359, 2.70137, 2.72138, 2.74139, 2.7614, 2.78141, 2.80142, 2.82143, 2.841441, 2.861451, 2.881461, 2.901471, 2.921481, 2.941491, 2.961501, 2.981512, 3.001522, 3.021532, 3.041542, 3.061552, 3.081562, 3.101572, 3.121583, 3.141593, 3.161603, 3.181613, 3.201623, 3.221633, 3.241643, 3.261654, 3.281664, 3.301674, 3.321684, 3.341694, 3.361704, 3.381714, 3.401725, 3.421735, 3.441745, 3.461755, 3.481765, 3.501775, 3.521785, 3.541796, 3.561806, 3.581816, 3.601826, 3.621836, 3.641846, 3.661857, 3.681867, 3.701877, 3.721887, 3.741897, 3.761907, 3.781917, 6.283185}
#define _NYBINS_ 11
#define _YBINS_  {0, 1, 2, 3, 4, 5, 7, 10, 15, 20, 30, 300}

static HIST_2D_VARBIN_XY RECOIL_Hist_2D_VARBIN_XY[]={
  {"hZcandDeltaPhi_EM1_EM2_Zpt_2pi_varbin_CCCC","open angle between EM and EM (CC-CC) vs Zpt",  _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
  {"hZcandDeltaPhi_EM1_EM2_Zpt_2pi_varbin_CCEC","open angle between EM and EM (CC-EC) vs Zpt",  _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
  {"hZcandDeltaPhi_EM1_EM2_Zpt_2pi_varbin_ECEC","open angle between EM and EM (EC-EC) vs Zpt",  _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
  {"hZcandDeltaPhi_EM1_EM2_Zpt_2pi_varbin_All","open angle between EM and EM (EC-EC) vs Zpt",  _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
  //	{"hZcandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi02_varbin","open angle between EM and EM (CC-CC) vs Zpt Lumi02", _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
  //	{"hZcandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi24_varbin","open angle between EM and EM (CC-CC) vs Zpt Lumi24", _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
  //	{"hZcandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi46_varbin","open angle between EM and EM (CC-CC) vs Zpt Lumi46", _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
  //	{"hZcandDeltaPhi_EM1_EM2_Zpt_CCCC_2pi_Lumi6999_varbin","open angle between EM and EM (CC-CC) vs Zpt Lumi6999", _NXBINS_, _XBINS_  , _NYBINS_, _YBINS_ },
	{"","", 0, {0.}, 0, {0.} }
};
#undef _NXBINS_
#undef _XBINS_
#undef _NYBINS_
#undef _YBINS_


static HIST_PROFILE RECOIL_Hist_Profile[]={
  {"hZcandPeeRecoProfile_All", "P_ee vs Recoil in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandPeeBalanceProfile_All", "P_ee vs Balance in eta direction", 30, 0., 30., -30., 60., "i"},
  {"hZcandKappa3Profile_All", "Pow(P_ee, 2) vs Pow(P_e1 + P_e2 + MET, 2)", 20, 0., 500., 0., 800., "i"},
  
  {"hZcandPeeRecoProfile_CCCC", "P_ee vs Recoil in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandPeeBalanceProfile_CCCC", "P_ee vs Balance in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandKappa3Profile_CCCC", "Pow(P_ee, 2) vs Pow(P_e1 + P_e2 + MET, 2)", 20, 0., 500., 0., 800., "i"},

  {"hZcandPeeRecoProfile_CCEC", "P_ee vs Recoil in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandPeeBalanceProfile_CCEC", "P_ee vs Balance in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandKappa3Profile_CCEC", "Pow(P_ee, 2) vs Pow(P_e1 + P_e2 + MET, 2)", 20, 0., 500., 0., 800., "i"},

  {"hZcandPeeRecoProfile_ECEC", "P_ee vs Recoil in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandPeeBalanceProfile_ECEC", "P_ee vs Balance in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandPeeRecoProfile_nECnEC", "P_ee vs Recoil in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandPeeBalanceProfile_nECnEC", "P_ee vs Balance in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandPeeRecoProfile_pECpEC", "P_ee vs Recoil in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandPeeBalanceProfile_pECpEC", "P_ee vs Balance in eta direction", 30, 0., 30., -60., 60., "i"},
  {"hZcandKappa3Profile_ECEC", "Pow(P_ee, 2) vs Pow(P_e1 + P_e2 + MET, 2)", 20, 0., 500., 0., 800., "i"},

  {"hZcand_Recoil_pT_Profile_All", "pT_Z vs Hadronic Response (All)", 30, 0., 30., 0., 1.5, "i"},
  {"hZcand_Recoil_pT_Profile_CCCC", "pT_Z vs Hadronic Response (CCCC)", 30, 0., 30., 0., 1.5, "i"},
  {"hZcand_Recoil_pT_Profile_CCEC", "pT_Z vs Hadronic Response (CCEC)", 30, 0., 30., 0., 1.5, "i"},
  {"hZcand_Recoil_pT_Profile_ECEC", "pT_Z vs Hadronic Response (ECEC)", 30, 0., 30., 0., 1.5, "i"},

  {"hZcandMass_V_fZ_CCCC_pro","Mee vs fZ_CCCC profile", 75, 1., 2.5, 60., 130., "i"},
  {"hZcandMass_V_fZ_ECEC_pro","Mee vs fZ_ECEC profile", 75, 1., 2.5, 60., 130., "i"},

  {"", "", 0, 0, 0, 0, 0, "i"}
};

static HIST_PROFILE ZCand_Profile[]={
  {"hZcandScalarEt_V_Lumi_CCCC", "Z SET V. Lumi (CC)",100, 0., 10., 0., 300., "i"},  
  {"","", 0,0,0,0,0, "i"}
};


static HIST_2D ZCand_Hist_2D[]={
  {"hZcandPt_V_Mass","Z candidate Pt vs Mass", 30, 0, 150, 120, 0., 60.},
  {"hZcandEta_V_Mass","Z candidate Rapidity vs Mass", 30, 0., 150., 31, -3.1, 3.1},
  {"hZcandMass_V_fZ_CCCC","Mee vs fZ for CCCC", 60, 1., 2.2, 140, 60., 130.},
  {"hZcandMass_V_fZ_ECEC","Mee vs fZ for ECEC", 60, 1., 2.2, 140, 60., 130.},
  {"hZcandMass_V_fZ_CCCC_Category","Mee vs fZ for CCCC eta bins", 60, 1., 2.2, 140, 60., 130.},
  {"hZcandMass_V_fZ_CCCC_Category_DetEta","Mee vs fZ for CCCC det eta bins", 60, 1., 2.2, 140, 60., 130.},
  {"hZcandMass_V_fZ_CCCC_Category_PhiMod","Mee vs fZ for CCCC phimod bins", 60, 1., 2.2, 140, 60., 130.},
  {"hZcandMass_V_fZ_CCCC_ElecPt2","Mee vs fZ for CCCC energy bins", 60, 1., 2.2, 140, 60., 130.},
  {"hZcandMass_V_fZ_CCCC_ElecPt1","Mee vs fZ for CCCC energy bins", 60, 1., 2.2, 140, 60., 130.},
  {"hZcandMass_V_fZ_CCCC_ElecPt","Mee vs fZ for CCCC energy bins", 60, 1., 2.2, 140, 60., 130.},
  {"hZcandElecEGen_V_Smear", "gen level vs smeared", 200, 0., 200., 200, 0., 200.},  

  // for tag-probe efficiency studies
  // trigger 2D plots
  {"ZMass_vs_Eta_Before_Trig_CC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_Before_Trig_CC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_Before_Trig_CC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_Before_Trig_CC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  
  {"ZMass_vs_Eta_After_Trig_CC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_After_Trig_CC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_After_Trig_CC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_After_Trig_CC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},

  //Preselection 2D plots
  {"ZMass_vs_Eta_Before_Presel_CC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_Before_Presel_CC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_Before_Presel_CC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_Before_Presel_CC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  
  {"ZMass_vs_Eta_After_Presel_CC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_After_Presel_CC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_After_Presel_CC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_After_Presel_CC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  
  {"ZMass_vs_Eta_Before_Presel_EC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_Before_Presel_EC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_Before_Presel_EC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_Before_Presel_EC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  
  {"ZMass_vs_Eta_After_Presel_EC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_After_Presel_EC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_After_Presel_EC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_After_Presel_EC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  
  //HMx 2D plots
  {"ZMass_vs_Eta_Before_HMx_CC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_Before_HMx_CC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_Before_HMx_CC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_Before_HMx_CC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  
  {"ZMass_vs_Eta_After_HMx_CC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_After_HMx_CC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_After_HMx_CC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_After_HMx_CC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  
  {"ZMass_vs_Eta_Before_HMx_EC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_Before_HMx_EC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_Before_HMx_EC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_Before_HMx_EC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  
  {"ZMass_vs_Eta_After_HMx_EC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_After_HMx_EC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_After_HMx_EC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_After_HMx_EC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  
  {"Eta_vs_Pt_Before_HMx_CC", "Eta vs Pt", 100, 0., 100., 31, -3.1, 3.1},
  {"Eta_vs_Pt_After_HMx_CC", "Eta vs Pt", 100, 0., 100., 31, -3.1, 3.1},

  {"Eta_vs_Vtx_Before_HMx_CC", "Eta vs Pt", 36, -60., 60., 31, -3.1, 3.1},
  {"Eta_vs_Vtx_After_HMx_CC", "Eta vs Pt", 36, -60., 60., 31, -3.1, 3.1},

  //Trk 2D plots
  {"ZMass_vs_Eta_Before_Trk_CC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_Before_Trk_CC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_Before_Trk_CC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_Before_Trk_CC", "mass vs Vtx",  24, -60., 60., 150, 0., 150.},
  {"Eta_vs_Pt_Before_Trk_CC", "Eta vs Pt", 100, 0., 100., 31, -3.1, 3.1},
  {"Eta_vs_Vtx_Before_Trk_CC", "Eta vs Pt", 36, -60., 60., 31, -3.1, 3.1},

  {"ZMass_vs_Eta_After_Trk_CC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_After_Trk_CC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_After_Trk_CC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_After_Trk_CC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  {"Eta_vs_Pt_After_Trk_CC", "Eta vs Pt", 100, 0., 100., 31, -3.1, 3.1},
  {"Eta_vs_Vtx_After_Trk_CC", "Eta vs Pt", 36, -60., 60., 31, -3.1, 3.1},

  {"ZMass_vs_Eta_Before_Trk_EC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_Before_Trk_EC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_Before_Trk_EC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_Before_Trk_EC", "mass vs Vtx",  24, -60., 60., 150, 0., 150.},
  
  {"ZMass_vs_Eta_After_Trk_EC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_DetEta_After_Trk_EC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"ZMass_vs_Pt_After_Trk_EC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_After_Trk_EC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},

  //Loose Trk 2D plots
  {"loose_ZMass_vs_Eta_Before_Trk_CC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"loose_ZMass_vs_DetEta_Before_Trk_CC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"loose_ZMass_vs_Pt_Before_Trk_CC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Vtx_Before_Trk_CC", "mass vs Vtx",  24, -60., 60., 150, 0., 150.},
  {"loose_Eta_vs_Pt_Before_Trk_CC", "Eta vs Pt", 100, 0., 100., 31, -3.1, 3.1},
  {"loose_Eta_vs_Vtx_Before_Trk_CC", "Eta vs Pt", 36, -60., 60., 31, -3.1, 3.1},

  {"loose_ZMass_vs_Eta_After_Trk_CC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"loose_ZMass_vs_DetEta_After_Trk_CC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"loose_ZMass_vs_Pt_After_Trk_CC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Vtx_After_Trk_CC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},
  {"loose_Eta_vs_Pt_After_Trk_CC", "Eta vs Pt", 100, 0., 100., 31, -3.1, 3.1},
  {"loose_Eta_vs_Vtx_After_Trk_CC", "Eta vs Pt", 36, -60., 60., 31, -3.1, 3.1},

  {"loose_ZMass_vs_Eta_Before_Trk_EC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"loose_ZMass_vs_DetEta_Before_Trk_EC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"loose_ZMass_vs_Pt_Before_Trk_EC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Vtx_Before_Trk_EC", "mass vs Vtx",  24, -60., 60., 150, 0., 150.},
  
  {"loose_ZMass_vs_Eta_After_Trk_EC", "mass vs Eta", 31, -3.1, 3.1, 150, 0., 150.},
  {"loose_ZMass_vs_DetEta_After_Trk_EC", "mass vs DetEta", 31, -3.1, 3.1, 150, 0., 150.},
  {"loose_ZMass_vs_Pt_After_Trk_EC", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Vtx_After_Trk_EC", "mass vs Vtx", 24, -60., 60., 150, 0., 150.},





  {"hZcandMass_V_ElecPt_CCCC", "Z mass vs Elect 2 Pt CCCC", 100, 50., 150., 100, 0., 100.},
  {"hZcandMass_V_ElecPt1_CCCC", "Z mass vs Elect 1 Pt CCCC", 100, 50., 150., 100, 0., 100.},
  {"hZcandMass_V_ElecPt2_CCCC", "Z mass vs Elect 2 Pt CCCC", 100, 50., 150., 100, 0., 100.},
  {"hZcandMass_V_ElecPt_CCEC", "Z mass vs Elect 1 Pt CCCC", 100, 50., 150., 100, 0., 100.},
  {"hZcandMass_V_ElecPt1_CCEC", "Z mass vs Elect 2 Pt CCCC", 100, 50., 150., 100, 0., 100.},
  {"hZcandMass_V_ElecPt2_CCEC", "Z mass vs Elect 1 Pt CCCC", 100, 50., 150., 100, 0., 100.},
  {"hZcandMass_V_UPara_CCCC", "Z mass vs Upara CCCC", 100, 50., 150., 120, -30., 30.},
  {"hZcandMass_V_UPara1_CCCC", "Z mass vs Upara 1 CCCC", 100, 50., 150., 120, -30., 30.},
  {"hZcandMass_V_UPara2_CCCC", "Z mass vs UPara 2 CCCC", 100, 50., 150., 120, -30., 30.},
  {"hZcandMass_V_UPara_CCEC", "Z mass vs UPara CCEC", 100, 50., 150., 120, -30., 30.},
  {"hZcandMass_V_UPara1_CCEC", "Z mass vs UPara 2 CCEC", 100, 50., 150., 120, -30., 30.},
  {"hZcandMass_V_UPara2_CCEC", "Z mass vs UPara 1 CCEC", 100, 50., 150., 120, -30., 30.},

  {"loose_ZMass_vs_Pt_Before_HMx_CC_Etabin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Pt_After_HMx_CC_Etabin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Pt_Before_Trk_CC_Etabin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Pt_After_Trk_CC_Etabin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Pt_Before_HMx_CC_SETbin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Pt_After_HMx_CC_SETbin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Pt_Before_Trk_CC_SETbin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Pt_After_Trk_CC_SETbin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"loose_ZMass_vs_Vtx_Before_Trk_CC_Etabin", "mass vs Pt", 36, -60., 60., 150, 0., 150.},
  {"loose_ZMass_vs_Vtx_After_Trk_CC_Etabin", "mass vs Pt", 36, -60., 60., 150, 0., 150.},

  {"ZMass_vs_Pt_Before_HMx_CC_Etabin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Pt_After_HMx_CC_Etabin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Pt_Before_Trk_CC_Etabin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Pt_After_Trk_CC_Etabin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Pt_Before_HMx_CC_SETbin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Pt_After_HMx_CC_SETbin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Pt_Before_Trk_CC_SETbin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Pt_After_Trk_CC_SETbin", "mass vs Pt", 100, 0., 100., 150, 0., 150.},
  {"ZMass_vs_Vtx_Before_Trk_CC_Etabin", "mass vs Pt", 36, -60., 60., 150, 0., 150.},
  {"ZMass_vs_Vtx_After_Trk_CC_Etabin", "mass vs Pt", 36, -60., 60., 150, 0., 150.},
  
  {"ZMass_vs_UPara_Before_CC", "mass vs Pt", 120, -30., 30., 150, 0., 150.},
  {"ZMass_vs_UPara_After_CC", "mass vs Pt", 120, -30., 30., 150, 0., 150.},
  {"ZMass_vs_UPara_Before_CC_ScaleToW", "mass vs Pt", 120, -30., 30., 150, 0., 150.},
  {"ZMass_vs_UPara_After_CC_ScaleToW", "mass vs Pt", 120, -30., 30., 150, 0., 150.},
  {"hZcandScalarEt_V_Lumi2D_CCCC", "Z SET Lumi 2D (CC)",100, 0., 10.,  100, 0., 300.},  
  {"dPhi_vs_ZPt_CCCC", "dPhi vs Z pT (CCCC)", 1256, 0., TMath::TwoPi(), 2400, 0., 200.},
 
  {"", "", 0, 0., 0., 0, 0., 0.}
};

static HIST_1D JPsiMuCand_Hist[]={
  {"hJPsiMucandMass","J/Psi Mass", 120, 2.5, 3.7},
  {"hJPsiMucandPt", "J/Psi pT", 200, 0., 20.},
  {"hJPsiMucandEta","J/Psi Eta", 200, -3., 3.},
  {"hJPsiMucandPhi","J/Psi Phi", 140, 0., 7.},
  {"hJPsiMucandMuPt", "J/Psi muon pT", 200, 0., 20.},
  {"hJPsiMucandMuEta","J/Psi muon Eta", 200, -3., 3.},
  {"hJPsiMucandMuPhi","J/Psi muon Phi", 140, 0., 7.},
  // histograms used to determine A, B and C for muon smearing
  {"hJPsiMucandMass_AB","J/Psi Mass", 120, 2.5, 3.7},
  {"hJPsiMucandMass_C","J/Psi Mass", 120, 2.5, 3.7},
  {"", "", 0, 0, 0}
};

static HIST_2D JPsiMuCand_Hist_2D[]={
  {"hJPsiMucandPt_V_Eta","J/psi candidate Pt vs Eta", 150, 0, 20, 150, -3., 3.},
  {"", "", 0, 0, 0, 0, 0, 0}
};

static HIST_1D ZMuCand_Hist[]={
  {"hZMucandMass","Z boson Mass", 240, 30., 150.},
  {"hZMucandPt", "Z boson pT", 120, 20., 80.},
  {"hZMucandEta","Z boson Eta", 100, -5., 5.},
  {"hZMucandRapidity","Z boson Rapidity", 100, -5., 5.},
  {"hZMucandPhi","Z boson Phi", 64, 0., TMath::TwoPi()},
  {"hZMucandMuPt", "Z muon pT", 180, 20., 80.},
  {"hZMucandMuEta","Z muon Eta", 100, -5., 5.},
  {"hZMucandMuPhi","Z muon Phi", 64, 0., TMath::TwoPi()},
  // histograms used to determine A, B and C for muon smearing
  {"hZMucandMass_AB","Z boson Mass", 240, 30., 150.},
  {"hZMucandMass_C","Z boson Mass", 240, 30., 150.},
  {"", "", 0, 0, 0}
};

// histograms used for ZNuNuAnalysis
// some histograms will be cloned in ZNuNuAnalysis constructor
// and appropriate suffixes will be added to their titles
// eg. _bin_<N>        -- for smeared recoil PT bins
//     _genZPt_bin_<N> -- for generator PT(Z) bin
//
static HIST_1D ZNuNuCand_Hist[]={
                      // same as above + kinematical cuts applied to neutrinos
                      {"ZNuNu_genZPt_Cuts", "gen Pt(Z)", 300, 0., 150.},
                      {"ZNuNu_genZPhi_Cuts", "gen Phi(Z)", 64, 0., TMath::TwoPi()},
                      {"ZNuNu_RecoilResolution_Cuts", "recoil resolution", 100, -2., 2.},
                      {"ZNuNu_RecoilPt_Cuts", "recoil pT", 100, 0., 50.},
                      {"ZNuNu_RecoilPx_Cuts", "recoil pX", 200, -50., 50.},
                      {"ZNuNu_RecoilPy_Cuts", "recoil pY", 200, -50., 50.},
                      {"ZNuNu_RecoilPhi_Cuts", "recoil Phi", 64, 0., TMath::TwoPi()},
                      {"ZNuNu_genVtxZ_Cuts", "gen vtx Z", 320, -80., 80.},
                      {"ZNuNu_DeltaPhi_genZ_Recoil_Cuts", "DPhi(Z,recoil)", 64, 0., TMath::Pi()},
                      {"ZNuNu_Met_Cuts", "Met", 100, 0., 50.},
                      {"ZNuNu_MetPhi_Cuts", "Met Phi", 64, 0., TMath::Pi()},
                      {"ZNuNu_MetX_Cuts", "MetX", 200, -50., 50.},
                      {"ZNuNu_MetY_Cuts", "MetY", 200, -50., 50.},
                      {"ZNuNu_ScalarEt_Cuts", "Scalar Et", 300, 0., 300.},
                      {"", "", 0, 0., 0.}};

// profiles used for ZNuNuAnalysis
static HIST_PROFILE ZNuNuCand_Hist_Profile[]={
  {"ZNuNu_RecoilResponse_V_RecoilPt_Cuts","", 50, 0., 50., -20., 20., "i"},
  {"ZNuNu_RecoilResponse_V_genZPt_Cuts", "", 50, 0., 50., -20., 20., "i"},
  {"ZNuNu_RecoilResponseProjection_V_RecoilPt_Cuts", "", 50, 0., 50., -20., 20., "i"},
  {"ZNuNu_RecoilResponseProjection_V_genZPt_Cuts", "", 50, 0., 50., -20., 20., "i"},

  {"ZNuNu_RecoilResponse_V_RecoilPhi_Cuts", "", 50, 0., 7., -20., 20., "i"},
  {"ZNuNu_RecoilResponse_V_genZPhi_Cuts", "", 50, 0., 7., -20., 20., "i"},
  {"ZNuNu_RecoilResponse_V_lumi_Cuts", "", 50, 0., 15., -20., 20., "i"},
  {"ZNuNu_RecoilResponse_V_zbset_Cuts", "", 50, 0., 25., -20., 20., "i"},

  {"", "",0, 0, 0, 0, 0, "i"}};

#endif //end _HISTOGRAMS_HPP

//
// Supported histogram types are:
//
// HIST_1D 
//   1D histogram having constant bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, X_min, X_max } 
//
// HIST_1D_VARBIN
//   1D histogram having variable bin widths (up to 50 bins) 
//   Initialization format: {"NAME", "TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)} }
//   NOTE: Array of bin boundaries has to have (Nbins_x+1) elements!
//
// HIST_PROFILE 
//   1D profile histogram having constant bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, X_min, X_max, Y_min, Y_max, ErrorOption } 
//   NOTE: Only Y values between Y_min and Y_max will be taken into account. 
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile::GetErrorOption() documentation.
//
// HIST_PROFILE_VARBIN
//   1D profile histogram having constant bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)}, Y_min, Y_max, ErrorOption } 
//   NOTE: Only Y values between Y_min and Y_max will be taken into account. 
//   NOTE: Array of bin boundaries has to have (Nbins_x+1) elements!
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile::GetErrorOption() documentation.
//
// HIST_2D 
//   2D histogram having constant X and Y bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, X_min, X_max, 
//                                            Nbins_y, Y_min, Y_max } 
//
// HIST_2D_VARBIN_X
//   2D histogram having variable X- and constant Y bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)}, 
//                                            Nbins_y, Y_min, Y_max } 
//   NOTE: Array of bin boundaries for X axis has to have (Nbins_x+1) elements!
//
// HIST_2D_VARBIN_Y
//   2D histogram having constant X- and variable Y bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, X_min, X_max, 
//                                            Nbins_y, {Y(0), Y(1), ..., Y(Nbins_y)} } 
//   NOTE: Array of bin boundaries for Y axis has to have (Nbins_y+1) elements!
//
// HIST_2D_VARBIN_XY
//   2D histogram having variable X and Y bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)}, 
//                                            Nbins_y, {Y(0), Y(1), ..., Y(Nbins_y)} } 
//   NOTE: Arrays of bin boundaries for X and Y axes have to have (Nbins_x+1) and (Nbins_y+1) elements, respectively!
//
// HIST_PROFILE_2D 
//   2D profile histogram having constant X and Y bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, X_min, X_max, 
//                                            Nbins_y, Y_min, Y_max, Z_min, Z_max, ErrorOption } 
//   NOTE: Only Z values between Z_min and Z_max will be taken into account. 
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile2D::GetErrorOption() documentation.
//
// HIST_PROFILE_2D_VARBIN_X
//   2D profile histogram having variable X- and constant Y bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)}, 
//                                            Nbins_y, Y_min, Y_max, Z_min, Z_max, ErrorOption } 
//   NOTE: Only Z values between Z_min and Z_max will be taken into account. 
//   NOTE: Array of bin boundaries for X axis has to have (Nbins_x+1) elements!
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile2D::GetErrorOption() documentation.
//
// HIST_PROFILE_2D_VARBIN_Y
//   2D profile histogram having constant X- and variable Y bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, X_min, X_max, 
//                                            Nbins_y, {Y(0), Y(1), ..., Y(Nbins_y)}, Z_min, Z_max, ErrorOption } 
//   NOTE: Only Z values between Z_min and Z_max will be taken into account. 
//   NOTE: Array of bin boundaries for Y axis has to have (Nbins_y+1) elements!
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile2D::GetErrorOption() documentation.
//
// HIST_PROFILE_2D_VARBIN_XY
//   2D profile histogram having variable X and Y bin widths 
//   Initialization format: {"NAME", "TITLE", Nbins_x, {X(0), X(1), ..., X(Nbins_x)}, 
//                                            Nbins_y, {Y(0), Y(1), ..., Y(Nbins_y)}, Z_min, Z_max, ErrorOption } 
//   NOTE: Only Z values between Z_min and Z_max will be taken into account. 
//   NOTE: Arrays of bin boundaries for X and Y axes have to have (Nbins_x+1) and (Nbins_y+1) elements, respectively!
//   NOTE: The default ErrorOption is " ". Other options are: I,S,G.
//         See ROOT's TProfile2D::GetErrorOption() documentation.
//
 

