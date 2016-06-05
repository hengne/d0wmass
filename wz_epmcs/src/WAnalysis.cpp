#include "WAnalysis.hpp"
#include "PMCSWCand.hpp"
#include "PMCSZCand.hpp"
#include "SETefficiencySmear.hpp"
#include "SETefficiencySmear_LumiDispatch.hpp"
#include "histograms.hpp"
#include "WZ_Utils.hpp"
#include "AnglesUtil.hpp"

#include <TFile.h>
#include <TObject.h>
#include <iostream>
#include "PHistoTools.hpp"

#include "wmass_blinding_util/BlindingManagerPMCS.hpp"

using namespace std;

bool ComparePt(const PMCSParticle part1, const PMCSParticle part2);

// Constructor
WAnalysis::WAnalysis(TString parameter_filename, TRandom3* dummy):_ntotal(0) {
    
  // Read control flags
  ReadParameters(parameter_filename);

  // initialize EMSmear, EfficiencySmear, RecoilSmear and SETefficiencySmear
  _emsmear = new EMSmear(parameter_filename, _histos);
  _efficiencysmear = new EfficiencySmear(parameter_filename, _histos, _eff_ratios_W_includeECtag);
  _recoilsmear = new RecoilSmear(parameter_filename, _histos, dummy);
  _SETefficiencysmear=0;
  if (_WSETEffCorrection) {
    if (_WSETEffCorrLumiSplit) {
      _SETefficiencysmear = new SETefficiencySmear_LumiDispatch(parameter_filename, true, &_WSETEffCorrLumiSplit_Bins, &_WSETEffCorrLumiSplit_Norm);
    } else {
      if (_WSETEffCorrPTEpert) {
	if (_WSETEffCorrPTEpert==3) {
	  _SETefficiencysmear = new SETefficiencySmear(_WSETEffCorrParameters,_WSETEffCorrParameters, // no dedicated EC values here
						       _WSETEffCorrScaled, _WSETEffCorrScale, _WSETEffCorrRelative, _WSETEffCorrInterpolate,
						       _WSETEffCorrPTEupara, _WSETEffCorrPTEpert,
						       &_WSETEffCorrEPTEpertBase,
						       &_WSETEffCorrEPTEpertA, &_WSETEffCorrEPTEpertB,
						       &_WSETEffCorrEPTEpertC, &_WSETEffCorrEPTEpertD,
						       &_WSETEffCorrEPTEpertE, &_WSETEffCorrEPTEpertF,
						       &_WSETEffCorrEPTEpertG, &_WSETEffCorrEPTEpertH,
						       &_WSETEffCorrEPTEpertNorm, _WSETEffCorrPTEpertRelGlobNorm,
						       &_WSETEffCorrDataRatioParameters, &_WSETEffCorrDataRatioParameters2,
						       &_WSETEffDataHackParameters,
						       &_WSETEffCorrDataRatioPTFit, &_WSETEffCorrDataRatioLumiFit,
						       _useHack,_useLumiBins );
	} else {
	  _SETefficiencysmear = new SETefficiencySmear(_WSETEffCorrParameters,_WSETEffCorrScaled, _WSETEffCorrScale, _WSETEffCorrRelative, _WSETEffCorrInterpolate,
						       _WSETEffCorrPTEpert, &_WSETEffCorrPTEpertBase,
						       &_WSETEffCorrPTEpertA, &_WSETEffCorrPTEpertB,
						       &_WSETEffCorrPTEpertC, &_WSETEffCorrPTEpertD,
						       &_WSETEffCorrPTEpertE, &_WSETEffCorrPTEpertF,
						       &_WSETEffCorrPTEpertG, &_WSETEffCorrPTEpertH,
						       &_WSETEffCorrPTEpertNorm,
						       &_WSETEffCorrDataRatioParameters, &_WSETEffCorrDataRatioParameters2,
						       &_WSETEffDataHackParameters,
						       &_WSETEffCorrDataRatioPTFit, &_WSETEffCorrDataRatioLumiFit,
						       _useHack,_useLumiBins );
	}
      } else {
	_SETefficiencysmear = new SETefficiencySmear(_WSETEffCorrParameters,_WSETEffCorrScaled, _WSETEffCorrScale);
      }
    }
  } else {
    // dummy object - we might use its interpolation methods
    std::vector<float> params; params.push_back(0); params.push_back(0); params.push_back(0); params.push_back(0); params.push_back(0);
    _SETefficiencysmear = new SETefficiencySmear(params);
  }

  // event counters
  _ntotal  = 0;
  _ngoodWCand = 0;
  _ngoodWCandCC = 0;
  _ngoodWCandEC = 0;
  
  // Book histograms

  // Do singularity variable study
  if(_doSingVariableStudy) {
    cout << "Adding singularity variable histograms" << endl;
    _histos.add(WCand_Hist_SingVariable);
//     2D templates for side-study.  Need extra loop in SV section to actually run this again
//     _histos.clone("hWcandSingVariable_CC", (int) ((_Bins_SingVariableStudy+1)*(_Bins_SingVariableStudy+1)));
//     _histos.clone("hWcandSingVariable_Gen_CC", (int) ((_Bins_SingVariableStudy+1)*(_Bins_SingVariableStudy+1)));
    
//     _histos.th1d("histd1map_SingVariableTemplates")->GetXaxis()->Set((int) _Bins_SingVariableStudy, 
// 									     _Center_SingVariable-(_Bins_SingVariableStudy/2)*_Step_SingVariable, 
// 									     _Center_SingVariable+(_Bins_SingVariableStudy/2)*_Step_SingVariable);
//     _histos.th1d("histd2map_SingVariableTemplates")->GetXaxis()->Set((int) _Bins_SingVariableStudy, 
// 									     _Center_SingVariable-(_Bins_SingVariableStudy/2)*_Step_SingVariable, 
    if(_wmass_reweight) {
      _histos.clone("hWcandSingVariable_CC", 100);
      //_histos.clone("hWcandSingVariable", 100);
      if(_doSVgeneratorstudy) _histos.clone("hWcandSingVariable_Gen_CC", 100);
      //if(_doSVgeneratorstudy) _histos.clone("hWcandSingVariable_Gen", 100);
      //    if(_doSVnolongitudinalstudy) _histos.clone("hWcandSingVariable_LongUnSmeared_CC", 100);
      //  if(_doSVnolongitudinalstudy) _histos.clone("hWcandSingVariable_LongUnSmeared", 100);
    }
    if(_doPdfReweight) {
      _histos.clone("hWcandSingVariable_PDF_CC", 45);
      //_histos.clone("hWcandSingVariable_PDF", 45);
      if(_doSVgeneratorstudy) _histos.clone("hWcandSingVariable_Gen_PDF_CC", 45);
      //if(_doSVgeneratorstudy) _histos.clone("hWcandSingVariable_Gen_PDF", 45);
      //  if(_doSVnolongitudinalstudy) _histos.clone("hWcandSingVariable_LongUnSmeared_PDF_CC", 45);
      //  if(_doSVnolongitudinalstudy) _histos.clone("hWcandSingVariable_LongUnSmeared_PDF", 45);
    }

    //using regular wmass template now
    //  if(_wmass_reweight) _histos.th1d("histd1map_SingVariableTemplates")->GetXaxis()->Set((int) _Bins_SingVariableStudy, 
    //									     _Center_SingVariable-(_Bins_SingVariableStudy/2)*_Step_SingVariable, 
    //									     _Center_SingVariable+(_Bins_SingVariableStudy/2)*_Step_SingVariable);
  }


  // Histograms for PDF study
  if(_doPdfReweight) {
    cout << "Adding PDF histograms " << endl;
    _histos.add(WCand_PDF_Hist);
    _histos.clone("hWcandMt_CC_PDF", 45);
    _histos.clone("hWcandElecPt_CC_PDF", 45);
    _histos.clone("hWcandMet_CC_PDF", 45);
    _histos.clone("hWcandMt_PDF", 45);
    _histos.clone("hWcandElecPt_PDF", 45);
    _histos.clone("hWcandMet_PDF", 45);
  }

  //histograms for general purposes
  _histos.add(WCand_Hist);
  _histos.add(WCand_Profile);
  _histos.add(WCand_Hist_2D);
  // The following executable statement has been commented out by Jan on January 16th, 2011.
  // It defines various control histograms. Most of them (all except two) are filled in
  // in EMSmear (to control/debug EM smearing). The remaining two are filled in the event loop
  // of WAnalysis and can be used to investigate/debug the treatment of high-energy FSR
  // photons. The motivation to remove these plots by default comes from their large size in RAM.
  //_histos.add(EMSMEAR_Hist_2D);

  // truth plots
  _histos.add(MCWBOSON_Hist);
  _histos.clone("hMCW_Pt_CC_bin", 10);
  _histos.clone("hRecoilW_Pt_CC_bin", 10);

  // histograms for w mass reweighting
  if(_wmass_reweight) {
    _histos.clone("hWcandMt", 100);
    _histos.clone("hWcandElecPt", 100);
    _histos.clone("hWcandMet", 100);
    _histos.clone("hWcandMt_CC", 100);
    _histos.clone("hWcandElecPt_CC", 100);
    _histos.clone("hWcandMet_CC", 100);
    _histos.clone("hWcandWPt_CC", 100);
    //
    _histos.clone("hWcandMtUpara_CC", 100);
    _histos.clone("hWcandElecPtUpara_CC", 100);
    _histos.clone("hWcandMetUpara_CC", 100);
    //
    _histos.clone("hWcandElecPtUpara1_CC", 100);
    _histos.clone("hWcandMetUpara1_CC", 100);
    _histos.clone("hWcandMtUpara1_CC", 100);
    _histos.clone("hWcandElecPtUpara2_CC", 100);
    _histos.clone("hWcandMetUpara2_CC", 100);
    _histos.clone("hWcandMtUpara2_CC", 100);
    //
    _histos.clone("hWcandMt_UtBin0_CC", 100);
    _histos.clone("hWcandMt_UtBin1_CC", 100);
    _histos.clone("hWcandMt_UtBin2_CC", 100);
  }
  // histograms for w width reweighting
  if(_wwidth_reweight) {
    _histos.clone("hWcandMt_CC_Width", 100);
    _histos.clone("hWcandElecPt_CC_Width", 100);
    _histos.clone("hWcandMet_CC_Width", 100);
    _histos.clone("hWcandWPt_CC_Width", 100);
  }

  _histos.clone("hWcandEOverP_V_ElecPhiMod", 32);
  _histos.clone("hWcandEOverP_V_ElecTrkPhiMod", 32);
  _histos.clone("hWcandEOverP_Mod", 32);
  _histos.clone("hWcandEOverP_TrkMod", 32);

  // for CC events, divided into different Pt regions
  _histos.clone("hWcandMt_RecoilBin", 10);
  _histos.clone("hWcandElecPt_RecoilBin", 10);
  _histos.clone("hWcandMet_RecoilBin", 10);
  _histos.clone("hWcandElecMetDeltaPhi_RecoilBin", 10);
  _histos.clone("hWcandElecRecoilDeltaPhi_RecoilBin", 10);
  _histos.clone("hWcandMetRecoilDeltaPhi_RecoilBin", 10);
  _histos.clone("hWcandRecoilPhi_RecoilBin", 10);
  _histos.clone("hWcandUPara_RecoilBin", 10);
  _histos.clone("hWcandUPerp_RecoilBin", 10);
  _histos.clone("hWcandVtx_RecoilBin", 10);
  _histos.clone("hWcandPhi_RecoilBin", 10);
  _histos.clone("hWcandInstLumi_RecoilBin", 10);
  _histos.clone("hWcandScalarEt_RecoilBin", 10);

  //MW
  // for CC events, divided into different electron Pt regions
  _histos.clone("hWcandScalarEt_ElecPtBin", 7);
  _histos.clone("hWcandSEToverEpt_ElecPtBin", 7);
  _histos.clone("hWcandUpara_ElecPtBin", 7);
 
  // for electron pT distributions in different eta regions
  _histos.clone("hWcandElecPt_Spatial_Match_EtaBin_CC", 15);
  _histos.clone("hWcandMCElecPt_Spatial_Match_EtaBin_CC", 15);
  _histos.clone("hWcandMCElecPtDiff_Spatial_Match_EtaBin_CC", 15);
  _histos.clone("hWcandElecPt_Spatial_Match_EtaBin_CC_Tail", 15);
  _histos.clone("hWcandMCElecPt_Spatial_Match_EtaBin_CC_Tail", 15);
  _histos.clone("hWcandMCElecPtDiff_Spatial_Match_EtaBin_CC_Tail", 15);
  _histos.clone("hWcandMCElecPt_EtaBin_CC_NoCuts", 15);

  // define map histograms, often number of bins is sqrt(# of grids)
  _histos.th1d("histd1map_WMassTemplates")->GetXaxis()->Set(99, _wmass_default-50*_wmass_step, _wmass_default+49*_wmass_step );
  _histos.th1d("histd1map_WWidthTemplates")->GetXaxis()->Set(99, _wwidth_default-50*_wwidth_step, _wwidth_default+49*_wwidth_step );

  // Upara control study in bins of electron pT
  if (_makeU_parControlPlot) {
    _histos.clone("hWcandUpara_noEff_CC",8);
    _histos.clone("hWcandUpara_noEff_EC",8);
    _histos.clone("hWcandUpara_emEff_CC",8);
    _histos.clone("hWcandUpara_emEff_EC",8);
    _histos.clone("hWcandUpara_emtrkEff_CC",8);
    _histos.clone("hWcandUpara_emtrkEff_EC",8);
    _histos.clone("hWcandUpara_emtrksetEff_CC",8);
    _histos.clone("hWcandUpara_emtrksetEff_EC",8);
    for (Int_t i=0; i<8; i++) {
      TString n;
      n="hWcandUpara_noEff_CC_"; n+=i;
      _histos.clone(n,5);
      n="hWcandUpara_noEff_EC_"; n+=i;
      _histos.clone(n,5);
      n="hWcandUpara_emEff_CC_"; n+=i;
      _histos.clone(n,5);
      n="hWcandUpara_emEff_EC_"; n+=i;
      _histos.clone(n,5);
      n="hWcandUpara_emtrkEff_CC_"; n+=i;
      _histos.clone(n,5);
      n="hWcandUpara_emtrkEff_EC_"; n+=i;
      _histos.clone(n,5);
      n="hWcandUpara_emtrksetEff_CC_"; n+=i;
      _histos.clone(n,5);
      n="hWcandUpara_emtrksetEff_EC_"; n+=i;
      _histos.clone(n,5);
    }
    _histos.clone("hWcandUpara_noEff_CC_cosdphi",10);
    _histos.clone("hWcandUpara_noEff_EC_cosdphi",10);
    _histos.clone("hWcandUpara_emEff_CC_cosdphi",10);
    _histos.clone("hWcandUpara_emEff_EC_cosdphi",10);
    _histos.clone("hWcandUpara_emtrkEff_CC_cosdphi",10);
    _histos.clone("hWcandUpara_emtrkEff_EC_cosdphi",10);
    _histos.clone("hWcandUpara_emtrksetEff_CC_cosdphi",10);
    _histos.clone("hWcandUpara_emtrksetEff_EC_cosdphi",10);
    for (Int_t i=0; i<10; i++) {
      TString n;
      n="hWcandUpara_noEff_CC_cosdphi_"; n+=i;
      _histos.clone(n,8);
      n="hWcandUpara_noEff_EC_cosdphi_"; n+=i;
      _histos.clone(n,8);
      n="hWcandUpara_emEff_CC_cosdphi_"; n+=i;
      _histos.clone(n,8);
      n="hWcandUpara_emEff_EC_cosdphi_"; n+=i;
      _histos.clone(n,8);
      n="hWcandUpara_emtrkEff_CC_cosdphi_"; n+=i;
      _histos.clone(n,8);
      n="hWcandUpara_emtrkEff_EC_cosdphi_"; n+=i;
      _histos.clone(n,8);
      n="hWcandUpara_emtrksetEff_CC_cosdphi_"; n+=i;
      _histos.clone(n,8);
      n="hWcandUpara_emtrksetEff_EC_cosdphi_"; n+=i;
      _histos.clone(n,8);
    }
    //
    _histos.clone("hWcandElecPt_noEff_CC",5);
    _histos.clone("hWcandElecPt_noEff_EC",5);
    _histos.clone("hWcandElecPt_emEff_CC",5);
    _histos.clone("hWcandElecPt_emEff_EC",5);
    _histos.clone("hWcandElecPt_emtrkEff_CC",5);
    _histos.clone("hWcandElecPt_emtrkEff_EC",5);
    _histos.clone("hWcandElecPt_emtrksetEff_CC",5);
    _histos.clone("hWcandElecPt_emtrksetEff_EC",5);
    //
    _histos.clone("hWcandElecEta_noEff_CC",8);
    _histos.clone("hWcandElecEta_noEff_EC",8);
    _histos.clone("hWcandElecEta_emEff_CC",8);
    _histos.clone("hWcandElecEta_emEff_EC",8);
    _histos.clone("hWcandElecEta_emtrkEff_CC",8);
    _histos.clone("hWcandElecEta_emtrkEff_EC",8);
    _histos.clone("hWcandElecEta_emtrksetEff_CC",8);
    _histos.clone("hWcandElecEta_emtrksetEff_EC",8);
  }

  // use square root of sum of weights
  _histos.SumWeight();

  //MW
  // for making a table of average leakage outside electron cone as a function of eta (for recoil library method)
  if(_MakeEleakTable){
    _LeakSum = new double[_NleakBins];
    _LeakCount = new double[_NleakBins];

    for(int i=0; i<_NleakBins; i++){ _LeakSum[i]=0; _LeakCount[i]=0; }
  }
  
  if (_makeROOTfile_for_WFIT || _makegenROOTfile_for_WFIT) {
    std::string wfitree_block = "mass_W_gen/D:tranmass_W_smear/D:elec_E/D:elec_px/D:elec_py/D:elec_pz/D:elec_deteta/D:elec_id/D:met_x/D:met_y/D:gen_W_E/D:gen_W_px/D:gen_W_py/D:gen_W_pz/D:gen_elec_E/D:gen_elec_px/D:gen_elec_py/D:gen_elec_pz/D:gen_nu_x/D:gen_nu_y/D:gen_nu_z/D:nu_px/D:nu_py/D:nu_pz/D:nu_deteta/D:nu_E/D:Trig_Ver/D:RecoilX/D:RecoilY/D:RecoilX_gen/D:RecoilY_gen/D:event_weight/D:elec_upara/D:elec_leakage/D:nu_upara/D:nu_leakage/D:elec_ZBdiff/D:nu_ZBdiff/D:lumi/D:elec_peta/D:nu_peta/D:mass_W_smear/D:vtxZ/D:nInConePh/I:xInConePh/D:SET/D:OutConePh_px/D:OutConePh_py/D:OutConePh_pz/D:OutConePh_E/D:pdfweights[45]/D:massweights[100]/D";
    if( _makeROOTfile_for_WFIT )
    {
      Wfitfile = new TFile("Wfittree.root","recreate");
      Wfittree = new TTree("Wfittree","W fit tree");
      Wfittree->Branch("Wfitdata",&wfit_data.mass_W_gen, wfitree_block.c_str() );
    }
    else if( _makegenROOTfile_for_WFIT )
    {
      Wfitfile = new TFile("Wfittree_gen.root","recreate");
      Wfittree = new TTree("Wfittree_gen","W fit tree");
      Wfittree->Branch("Wfitdata_gen",&wfit_data.mass_W_gen, wfitree_block.c_str() );
    }
  }//if make W fit file

}

// read other parameters
void WAnalysis::ReadParameters(TString parameter_filename) {
  PParameterReader parm(parameter_filename.Data());  
  _debug = parm.GetBool("debug", kFALSE);  

  _makeU_parControlPlot = parm.GetBool("MakeU_parControlPlot", kFALSE);

  // output file
  _wenfilename = parm.GetChar("output_file_wen");

  // optional output file containing 
  _makeROOTfile_for_WFIT = parm.GetBool("makeROOTfile_for_WFIT");
  _makegenROOTfile_for_WFIT = parm.GetBool("makegenROOTfile_for_WFIT");

  // optional ASCII printouts
  _makeASCIIfile_LumiEff = parm.GetBool("makeASCIIfile_LumiEff");
  _makeASCIIfile_Eresponse = parm.GetBool("makeASCIIfile_Eresponse");

  // for reweighting
  _wmass_reweight = parm.GetBool("wmass_reweight", kTRUE);
  _wmass_default = parm.GetFloat("wmass_default", 80.45);

  // for pdf reweigting:
  _doPdfReweight = parm.GetBool("PDFReweight", false);

  // for singularity variable study
  _doSingVariableStudy = parm.GetBool("doSingVariableStudy", false);
  _doSVgeneratorstudy = parm.GetBool("doSVgeneratorstudy", false);
  // _doSVnolongitudinalstudy = parm.GetBool("doSVnolongitudinalstudy", false);
  //  _Step_SingVariable = parm.GetFloat("wmass_step", 0.040);
  // _Center_SingVariable = parm.GetFloat("wmass_default", 80.400);
  // _Bins_SingVariableStudy = parm.GetFloat("wmass_bins", 100);

  // W mass reweighting
  _wwidth_default = parm.GetFloat("wwidth_default", 2.1);
  _wmass_step = parm.GetFloat("wmass_step", 0.050);

  // W width reweighting
  _wwidth_reweight = parm.GetBool("wwidth_reweight", kTRUE);
  _wwidth_default = parm.GetFloat("wwidth_default", 2.1);
  _wwidth_step = parm.GetFloat("wwidth_step", 0.050);

  // Uparallel correction
  _WUparaCorrection = parm.GetBool("WUparaCorrection", kTRUE);
  
  _PlotUparaOverPte = parm.GetBool("PlotUparaOverPte", kFALSE);
  _PlotCosUphi = parm.GetBool("PlotCosUphi", kFALSE);

  if (_PlotUparaOverPte) {
    cout << "Add WCand_Hist_UparaOverPte to Histos ..." << endl;
    _histos.add(WCand_Hist_UparaOverPte);
  } else if (_PlotCosUphi) {
    cout << "Add WCand_Hist_CosUphi to Histos ..." << endl;
    _histos.add(WCand_Hist_CosUphi);
  } else {
    cout << "Add WCand_Hist_Upara to Histos ..." << endl;
    _histos.add(WCand_Hist_Upara);
    _histos.add(WCand_Hist_UparaUperp);
  };

  // Apply AddOnEff for Wen
  _ApplyAddOnEff_Wen = parm.GetBool("ApplyAddOnEff_Wen", false);

  // Uparallel efficiency correction
  _UseUparaOverPte  = parm.GetBool("UseUparaOverPte", kFALSE);
  _UseCosUphi  = parm.GetBool("UseCosUphi", kFALSE);
  _WUparaEffCorrection = parm.GetBool("WUparaEffCorrection", kTRUE);
  _UparaEffCorrOption = parm.GetInt("WUparaEffCorrOption", 1);
  _WUparaEffParameters = parm.GetVDouble("WUparaEffCorrParameters_CC");

  _W_u0_CC = parm.GetFloat("W_u0_CC", 2.57375);
  _W_s_CC = parm.GetFloat("W_s_CC", 0.002841);
  _W_u0_EC = parm.GetFloat("W_u0_EC", 2.308);
  _W_s_EC = parm.GetFloat("W_s_EC", 0.0046);
  _W_seta_CC = parm.GetFloat("W_seta_CC", 0.0084);

  _WUparaEffLumiDep = parm.GetBool("WUparaEffLumiDep", kFALSE);
  if (_WUparaEffLumiDep) {
    _WUparaEffLumiDep_Bins = parm.GetVFloat("WUparaEffLumiDep_Bins");
    _WUparaEffLumiDep_Slopes = parm.GetVFloat("WUparaEffLumiDep_Slopes");
    assert(_WUparaEffLumiDep_Slopes.size()==(_WUparaEffLumiDep_Bins.size()+1));
  }

  _W_u0pte_CC = parm.GetFloat("W_u0pte_CC", 0.0185);
  _W_spte_CC = parm.GetFloat("W_spte_CC", 0.0244);
  _W_u1pte_CC = parm.GetFloat("W_u1pte_CC", 0.43);
  _W_u0pte_EC = parm.GetFloat("W_u0pte_EC", 0.0185);
  _W_spte_EC = parm.GetFloat("W_spte_EC", 0.0244);

  _W_u0phi_CC = parm.GetFloat("W_u0phi_CC", 0.0185);
  _W_sphi_CC = parm.GetFloat("W_sphi_CC", 0.0244);
  _W_u1phi_CC = parm.GetFloat("W_u1phi_CC", 0.43);
  _W_u0phi_EC = parm.GetFloat("W_u0phi_EC", 0.0185);
  _W_sphi_EC = parm.GetFloat("W_sphi_EC", 0.0244);

  _WUparaEffCorrectionPert = parm.GetBool("WUparaEffCorrectionPert", kFALSE);
  if (_WUparaEffCorrectionPert) {
    _WUparaEffCorrectionPertInterpolate = parm.GetBool("WUparaEffCorrectionPertInterpolate", kFALSE);
    _Wpert_u0_CC = parm.GetFloat("Wpert_u0_CC", 0.0);
    _Wpert_lumidep = parm.GetBool("Wpert_lumidep", kFALSE);
    if (_Wpert_lumidep) {
      _Wpert_lumibins = parm.GetVFloat("Wpert_lumibins");
      for (int i=0; i<=_Wpert_lumibins.size(); i++) {
        TString n;
        n="Wpert_s_CC_lum";
        n+=i;
        _Wpert_s_CC[i] = parm.GetVFloat(n.Data());
      }
    } else {
      _Wpert_s_CC[0] = parm.GetVFloat("Wpert_s_CC");
    }
    _WUparaEffCorrectionPertInterpolate2 = parm.GetBool("WUparaEffCorrectionPertInterpolate2", kFALSE);
    _WpertG_u0_CC = parm.GetFloat("WpertG_u0_CC", 0.0);
    _WpertG_lumidep = parm.GetBool("WpertG_lumidep", kFALSE);
    if (_WpertG_lumidep) {
      _WpertG_lumibins = parm.GetVFloat("WpertG_lumibins");
      for (int i=0; i<=_WpertG_lumibins.size(); i++) {
	TString n;
	n="WpertG_p_CC_lum";
	n+=i;
	_WpertG_p_CC[i] = parm.GetVFloat(n.Data());
	n="WpertG_s_CC_lum";
        n+=i;
        _WpertG_s_CC[i] = parm.GetVFloat(n.Data());
	n="WpertG_pm_CC_lum";
        n+=i;
        _WpertG_pm_CC[i] = parm.GetVFloat(n.Data());
        n="WpertG_sm_CC_lum";
        n+=i;
        _WpertG_sm_CC[i] = parm.GetVFloat(n.Data());
      }
    } else {
      _WpertG_p_CC[0] = parm.GetVFloat("WpertG_p_CC");
      _WpertG_s_CC[0] = parm.GetVFloat("WpertG_s_CC");
      _WpertG_pm_CC[0] = parm.GetVFloat("WpertG_pm_CC");
      _WpertG_sm_CC[0] = parm.GetVFloat("WpertG_sm_CC");
    }
  }

  _WUparaEffCorrectionCDPPert = parm.GetBool("WUparaEffCorrectionCDPPert", kFALSE);
  if (_WUparaEffCorrectionCDPPert) {
    _WCDPpert_u0_CC = parm.GetFloat("WCDPpert_u0_CC", 0.0);
    _WCDPpert_p_CC = parm.GetVFloat("WCDPpert_p_CC");
    _WCDPpert_s_CC = parm.GetVFloat("WCDPpert_s_CC");
  }

  _WUparaEffCorrHengne = parm.GetBool("WUparaEffCorrHengne", kFALSE); 
  if (_WUparaEffCorrHengne){
    _WUparaEffCorrHengneOption = parm.GetInt("WUparaEffCorrHengneOption", 0);
    if (_WUparaEffCorrHengneOption==0||_WUparaEffCorrHengneOption==1){
      TFile* fupeHengne = new TFile(parm.GetChar("WUparaEffCorrHengneFile"));
      if (_WUparaEffCorrHengneOption==0){
        _WUparaEffCorrHengne_hUParaUPerpEFRT = (TH1D*)fupeHengne->Get("hUParaUPerpEFRT");  
      }
      else if (_WUparaEffCorrHengneOption==1){
        _WUparaEffCorrHengne_hUTUPhiEFRT = (TH1D*)fupeHengne->Get("hUTUPhiEFRT");  
      }
    }
    else if (_WUparaEffCorrHengneOption==2){
      _WUparaEffCorrHengne_3GausPars = parm.GetVDouble("WUparaEffCorrHengne_3GausPars"); 
    }
  } 
 

  //Trk Phimod Cut
  _ApplyTrkPhiModCut = parm.GetBool("TrkPhiModEfficiency");

  // Efficiency correction
  _WtrigEffCorrection = parm.GetBool("WtrigEffCorrection", kFALSE);
  _WpreselEffCorrection = parm.GetBool("WpreselEffCorrection", kFALSE);
  _WIDEffCorrection = parm.GetBool("WIDEffCorrection", kFALSE);
  _WtrkEffCorrection = parm.GetBool("WtrkEffCorrection", kFALSE);
  _WElecPhiEffCorrection = parm.GetBool("WElecPhiEffCorrection", kFALSE);
  _WElecPhiEffCorrectionUseDetPhi = parm.GetBool("WElecPhiEffCorrectionUseDetPhi", kFALSE);

  //Cut on ZB Triggers 'Turned On'
  _TrigSelector = parm.GetInt("TriggerSelector", 0);

  // FSR photons in cracks
  _WsimuFSRcracks = parm.GetBool("WsimuFSRcracks", kFALSE);
  _WsimuFSRcracksWidth = parm.GetFloat("WsimuFSRcracksWidth", 0.05);

  // SET efficiency
  _WSETEffCorrection = parm.GetBool("WSETEffCorrection", kFALSE);
  _WSETEffCorrLumiSplit = parm.GetBool("WSETEffCorrLumiSplit", kFALSE);
  if (_WSETEffCorrLumiSplit) {
    _WSETEffCorrLumiSplit_Bins = parm.GetVFloat("WSETEffCorrLumiSplit_Bins");
    _WSETEffCorrLumiSplit_Norm = parm.GetVFloat("WSETEffCorrLumiSplit_Norm");
    assert((_WSETEffCorrLumiSplit_Bins.size()+1)==_WSETEffCorrLumiSplit_Norm.size());
  }
  _WSETEffCorrPedantic = parm.GetBool("WSETEffCorrPedantic", kFALSE);
  if (_WSETEffCorrPedantic) {
    _WSETEffCorrPedanticPar = parm.GetVFloat("WSETEffCorrPedanticPar");
  }
  _WSETEffCorrScaled = parm.GetBool("WSETEffCorrScaled", kFALSE);
  _WSETEffCorrRelative = parm.GetBool("WSETEffCorrRelative", kFALSE);
  _WSETEffCorrScale=200.;
  if (_WSETEffCorrRelative) _WSETEffCorrScale=20.;
  _WSETEffCorrInterpolate = parm.GetBool("WSETEffCorrInterpolate", kFALSE);
  _WSETEffCorrParameters = parm.GetVFloat("WSETEffCorrParameters");
  //
  _WSETEffCorrPTEpert = parm.GetInt("WSETEffCorrPTEpert", 0);

  if (_WSETEffCorrPTEpert==1||_WSETEffCorrPTEpert==2) {
    _WSETEffCorrPTEpertBase = parm.GetVFloat("WSETEffCorrPTEpertBase");
    _WSETEffCorrPTEpertA = parm.GetVFloat("WSETEffCorrPTEpertA");
    _WSETEffCorrPTEpertB = parm.GetVFloat("WSETEffCorrPTEpertB");
    _WSETEffCorrPTEpertC = parm.GetVFloat("WSETEffCorrPTEpertC");
    _WSETEffCorrPTEpertD = parm.GetVFloat("WSETEffCorrPTEpertD");
    _WSETEffCorrPTEpertE = parm.GetVFloat("WSETEffCorrPTEpertE");
    _WSETEffCorrPTEpertF = parm.GetVFloat("WSETEffCorrPTEpertF");
    _WSETEffCorrPTEpertG = parm.GetVFloat("WSETEffCorrPTEpertG");
    _WSETEffCorrPTEpertH = parm.GetVFloat("WSETEffCorrPTEpertH");
    _WSETEffCorrPTEpertNorm = parm.GetVFloat("WSETEffCorrPTEpertNorm");
  } else if (_WSETEffCorrPTEpert==3) {
    _WSETEffCorrPTEupara = parm.GetInt("WSETEffCorrPTEupara", 0);
    for (int i=0; i<5; i++) {
      TString n;
      n="WSETEffCorrPTEpertBase_";
      n+=i;
      _WSETEffCorrEPTEpertBase.push_back(parm.GetVFloat(n.Data()));
      n="WSETEffCorrPTEpertA_";
      n+=i;
      _WSETEffCorrEPTEpertA.push_back(parm.GetVFloat(n.Data()));
      n="WSETEffCorrPTEpertB_";
      n+=i;
      _WSETEffCorrEPTEpertB.push_back(parm.GetVFloat(n.Data()));
      n="WSETEffCorrPTEpertC_";
      n+=i;
      _WSETEffCorrEPTEpertC.push_back(parm.GetVFloat(n.Data()));
      n="WSETEffCorrPTEpertD_";
      n+=i;
      _WSETEffCorrEPTEpertD.push_back(parm.GetVFloat(n.Data()));
      n="WSETEffCorrPTEpertE_";
      n+=i;
      _WSETEffCorrEPTEpertE.push_back(parm.GetVFloat(n.Data()));
      n="WSETEffCorrPTEpertF_";
      n+=i;
      _WSETEffCorrEPTEpertF.push_back(parm.GetVFloat(n.Data()));
      n="WSETEffCorrPTEpertG_";
      n+=i;
      _WSETEffCorrEPTEpertG.push_back(parm.GetVFloat(n.Data()));
      n="WSETEffCorrPTEpertH_";
      n+=i;
      _WSETEffCorrEPTEpertH.push_back(parm.GetVFloat(n.Data()));
      n="WSETEffCorrPTEpertNorm_";
      n+=i;
      _WSETEffCorrEPTEpertNorm.push_back(parm.GetVFloat(n.Data()));
    }
    if (_WSETEffCorrPTEupara==1) {
      for (int i=0; i<5; i++) {
	TString n;
	n="WSETEffCorrPTEpertBase_";
	n+=i;
	n+="b";
	_WSETEffCorrEPTEpertBase.push_back(parm.GetVFloat(n.Data()));
	n="WSETEffCorrPTEpertA_";
	n+=i;
	n+="b";
	_WSETEffCorrEPTEpertA.push_back(parm.GetVFloat(n.Data()));
	n="WSETEffCorrPTEpertB_";
	n+=i;
	n+="b";
	_WSETEffCorrEPTEpertB.push_back(parm.GetVFloat(n.Data()));
	n="WSETEffCorrPTEpertC_";
	n+=i;
	n+="b";
	_WSETEffCorrEPTEpertC.push_back(parm.GetVFloat(n.Data()));
	n="WSETEffCorrPTEpertD_";
	n+=i;
	n+="b";
	_WSETEffCorrEPTEpertD.push_back(parm.GetVFloat(n.Data()));
	n="WSETEffCorrPTEpertE_";
	n+=i;
	n+="b";
	_WSETEffCorrEPTEpertE.push_back(parm.GetVFloat(n.Data()));
	n="WSETEffCorrPTEpertF_";
	n+=i;
	n+="b";
	_WSETEffCorrEPTEpertF.push_back(parm.GetVFloat(n.Data()));
	n="WSETEffCorrPTEpertG_";
	n+=i;
	n+="b";
	_WSETEffCorrEPTEpertG.push_back(parm.GetVFloat(n.Data()));
	n="WSETEffCorrPTEpertH_";
	n+=i;
	n+="b";
	_WSETEffCorrEPTEpertH.push_back(parm.GetVFloat(n.Data()));
	n="WSETEffCorrPTEpertNorm_";
	n+=i;
	n+="b";
	_WSETEffCorrEPTEpertNorm.push_back(parm.GetVFloat(n.Data()));
      }
      //
      _WSETEffCorrPTEpertRelGlobNorm=parm.GetFloat("WSETEffCorrPTEpertRelGlobNorm");
    }
  }
  _useHack = parm.GetInt("SETuseHack");
  _useLumiBins = parm.GetBool("SETuseLumiBins");
  char name[100];
  if (_useHack && _useHack<=2){
    for (Int_t tv=0; tv<7; ++tv){
      std::vector< std::vector<float> >  _tempvec;
      std::vector< std::vector<float> >  _tempvec2;
      for (Int_t tg=0; tg<7; ++tg){
	sprintf(name,"SETEffCorrDataRatioParametersBin%1d_%1d",tv, tg);
	if (tv==6)
	  sprintf(name,"SETEffCorrDataRatioParametersBin_%1d",tg);
	_tempvec.push_back(parm.GetVFloat(name));

	//not used -- but required for SETefficiencysmear constructor 
	sprintf(name,"SETEffCorrDataRatioParameters2Bin%1d_%1d",tv,tg);
	if (tv==6)
	  sprintf(name,"SETEffCorrDataRatioParameters2Bin_%1d",tg);
	_tempvec2.push_back(parm.GetVFloat(name));
      }
      _WSETEffCorrDataRatioParameters.push_back(_tempvec);
      _tempvec.clear();
      _WSETEffCorrDataRatioParameters2.push_back(_tempvec2);
      _tempvec2.clear();
      //
      if (_useHack==2) {
	_WSETEffCorrDataRatioPTFit = parm.GetVFloat("WSETEffCorrDataRatioPTFit");
	_WSETEffCorrDataRatioLumiFit = parm.GetVFloat("WSETEffCorrDataRatioLumiFit");
      }
    }
  }
  if (_useHack==3){
    _WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackPtDepParameters"));
    if(parm.GetBool("Run3")) {
      _WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackSETDepParameters3"));
      _WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackLumiDepParameters3"));
    } else if(parm.GetBool("Run4")) {
      _WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackSETDepParameters4"));
      _WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackLumiDepParameters4"));
    }
    _WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackDetEtaDepParameters"));
  }

  // UT reweighting for sensitivity studies
  _UTreweighting = parm.GetBool("UTreweighting",kFALSE);
  if (_UTreweighting) {
    _UTreweightingWT = parm.GetVFloat("UTreweightingWT");
    assert(_UTreweightingWT.size()==5);
  }

  // for pT-dependent efficiencies
  _eff_ratios_W_includeECtag = parm.GetBool("eff_ratios_W_includeECtag", kFALSE);

  // track pT cut
  _trkpTCut = parm.GetFloat("trkpTCut", 10.);
 
  // True W Pt and True W Phi cut
  _CutTrueWPtLo = parm.GetFloat("CutTrueWPtLo", -1.0);
  _CutTrueWPtHi = parm.GetFloat("CutTrueWPtHi", 99999.0);
  _CutTrueWPhiLo = parm.GetFloat("CutTrueWPhiLo", -1.0);
  _CutTrueWPhiHi = parm.GetFloat("CutTrueWPhiHi", 7.0);
  _CutTrueWMassLo = parm.GetFloat("CutTrueWMassLo", -1.0);
  _CutTrueWMassHi = parm.GetFloat("CutTrueWMassHi", 999999.0);
 
  // electron and W boson pT cut
  _CutEPT = parm.GetFloat("CutEPT", 25.);
  _CutMET = parm.GetFloat("CutMET", 25.);
  _CutWUT = parm.GetFloat("CutWUT", 15.);
  _CutWUT_lower = parm.GetFloat("CutWUT_lower", 0.);
  _CutWScalarEt = parm.GetFloat("CutWScalarEt", 100000.);
  _CutWScalarEt_lower = parm.GetFloat("CutWScalarEt_lower", 0.);

  // W Mt cut
  _WMtCut1 = parm.GetFloat("WMtCut1", 50.);
  _WMtCut2 = parm.GetFloat("WMtCut2", 200.);

  // eta cut
  _CutEtaCC = parm.GetFloat("CutEtaCC", 1.05);
  _CutEtaEC1 = parm.GetFloat("CutEtaECLow", 1.5);
  _CutEtaEC2 = parm.GetFloat("CutEtaECHigh", 2.5);

  // MW
  // make a table of energy leakage versus eta bin (for unfolding)
  _MakeEleakTable = parm.GetBool("MakeEleakTable", kFALSE);
  _NleakBins = parm.GetInt("NleakBins", 14);

  // photons with pT > pT_cut and well separated from electrons
  // will be treated as independent EM clusters, energy smearing will be applied
  // and also be included in the final missing Et calculation
  _merge_fsr_photons_met = parm.GetBool("merge_fsr_photons_met", kTRUE);

  
  // vary cut values and check the consistency of W mass
  _consistency_check = parm.GetBool("consistency_check", kFALSE);
  _invert_cut = parm.GetBool("invert_cut", kFALSE);
  _cut_under_study = (TString)(parm.GetChar("cut_under_study", ""));

  _runNo_lowcut = parm.GetInt("runNo_lowcut", 0);
  _runNo_highcut = parm.GetInt("runNo_highcut", 0);
  _InstLumi_lowcut = parm.GetFloat("InstLumi_lowcut", 0.);
  _InstLumi_highcut = parm.GetFloat("InstLumi_highcut", 0.);
  _ScalarEt_lowcut = parm.GetFloat("ScalarEt_lowcut", 0.);
  _ScalarEt_highcut = parm.GetFloat("ScalarEt_highcut", 0.);
  _UPara_lowcut = parm.GetFloat("UPara_lowcut", 0.);
  _UPara_highcut = parm.GetFloat("UPara_highcut", 0.);
  _ElecEta_cut = parm.GetFloat("ElecEta_cut", 0.);
  _ElecDetEta_lowcut = parm.GetFloat("ElecDetEta_lowcut", 0.);
  _ElecDetEta_highcut = parm.GetFloat("ElecDetEta_highcut", 0.);
  _ElecPhiMod_cut = parm.GetFloat("ElecPhiMod_cut", 0.);
  _ElecPt_lowcut = parm.GetFloat("ElecPt_lowcut", 0.);
  _ElecPt_highcut = parm.GetFloat("ElecPt_highcut", 0.);
  _ElecPhi_lowcut = parm.GetFloat("ElecPhi_lowcut", 0.);
  _ElecPhi_highcut = parm.GetFloat("ElecPhi_highcut", 0.);
  _RecoilPhi_lowcut = parm.GetFloat("RecoilPhi_lowcut", 0.);
  _RecoilPhi_highcut = parm.GetFloat("RecoilPhi_highcut", 0.);
}

// return the event weight for given w mass point
// the weight should be very close to 1
vector<double> WAnalysis::BreitWignerReweightMass(PMCSEvent& pmcsevent){
  vector<double> mass_weightfactor;
  mass_weightfactor.clear();
  
  double wmass_event = pmcsevent.GetWZBoson().Mass();
  double bw_default = pow(wmass_event*_wwidth_default/_wmass_default,2)/( pow(wmass_event*wmass_event-_wmass_default*_wmass_default,2) + 
									  pow(wmass_event*wmass_event*_wwidth_default/_wmass_default,2));
  
  double wmass_point=0., bw_reweight=0., factor=1.;

  for(int iloop=0; iloop<100; iloop++) {
    wmass_point = _wmass_default + (iloop-50)*_wmass_step;
    bw_reweight = pow(wmass_event*_wwidth_default/wmass_point,2)/( pow(wmass_event*wmass_event-wmass_point*wmass_point,2) + 
								   pow(wmass_event*wmass_event*_wwidth_default/wmass_point,2));
    if(bw_default!=0) factor=bw_reweight/bw_default;
    
    mass_weightfactor.push_back(factor);
  }
  
  return mass_weightfactor;
}

// return the event weight for given w mass point for different width values
// the weight should be very close to 1
vector<double> WAnalysis::BreitWignerReweightWidth(PMCSEvent& pmcsevent){
  vector<double> width_weightfactor;
  width_weightfactor.clear();

  double wmass_event = pmcsevent.GetWZBoson().Mass();
  double bw_default = pow(wmass_event*_wwidth_default/_wmass_default,2)/( pow(wmass_event*wmass_event-_wmass_default*_wmass_default,2) +
                                                                          pow(wmass_event*wmass_event*_wwidth_default/_wmass_default,2));

  double wwidth_point=0., bw_reweight=0., factor=1.;

  for(int iloop=0; iloop<100; iloop++) {
    wwidth_point = _wwidth_default + (iloop-50)*_wwidth_step;
    bw_reweight = pow(wmass_event*wwidth_point/_wmass_default,2)/( pow(wmass_event*wmass_event-_wmass_default*_wmass_default,2) +
                                                                   pow(wmass_event*wmass_event*wwidth_point/_wmass_default,2));
    if(bw_default!=0) factor=bw_reweight/bw_default;

    width_weightfactor.push_back(factor);
  }

  return width_weightfactor;
}


// the whole event passes efficiency cuts
bool WAnalysis::passesAllEffs(PMCSWCand& wcand, PMCSVtx& vtx_gen, TRandom3 *dummy, double TrigVer, bool neverUseTrack=kFALSE) {
  
  bool passesAllEffs = true;
  
  //
  // apply Uparallel corrections
  //
  bool passesUParaCorrection=true;
  if(_WUparaEffCorrection) {
    
    double upara = wcand.UPara();
    double uperp = wcand.UPerp();
    double ut = wcand.UT();
    double uphi = fabs(wcand.DeltaPhi_EM_Recoil());

    double upara_eff = 1.;

    double u0_CC, u1_CC, s_CC, u0_EC, s_EC;

    if ( _UseUparaOverPte) {
      _UparaEffCorrOption = 0;
      PMCSEMObj emobj = wcand.GetElec();
      double WElecPt=0., WElecEta=0., WElecDetEta=0., WElecPhi=0., WElecDetPhi=0.;
      emobj.getProperties(WElecPt, WElecEta, WElecPhi, WElecDetEta, WElecDetPhi);
      upara=upara/WElecPt;
      u0_CC = _W_u0pte_CC;
      u1_CC = _W_u1pte_CC;
      s_CC  = _W_spte_CC;
      u0_EC = _W_u0pte_EC;
      s_EC  = _W_spte_EC;
    }
    else if ( _UseCosUphi ) {
      _UparaEffCorrOption = 0;
      //wcand.getProperties(WMt, WPt, WUpara, WUperp);
      double uperp = wcand.UPerp();
      upara = upara / sqrt(upara*upara + uperp*uperp);
      u0_CC = _W_u0phi_CC;
      u1_CC = _W_u1phi_CC;
      s_CC  = _W_sphi_CC;
      u0_EC = _W_u0phi_EC;
      s_EC  = _W_sphi_EC;
    }
    else {
      u0_CC = _W_u0_CC;
      s_CC  = _W_s_CC;
      u0_EC = _W_u0_EC;
      s_EC  = _W_s_EC;
      if (_WUparaEffLumiDep) {
	int theBin=0;
	while (wcand.GetElec().getLumi()>_WUparaEffLumiDep_Bins[theBin]) {
	  theBin++;
	  if (theBin==_WUparaEffLumiDep_Bins.size()) break;
	}
	s_CC=_WUparaEffLumiDep_Slopes[theBin];
      }
    }

    
    // calculate uparallel efficiency for CC and EC regions
    if(wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _ApplyTrkPhiModCut) == 0) {
      if(_UparaEffCorrOption == 0) { // for _UparaEffCorrOption==0
	if(upara<u0_CC) upara_eff = 1.;	    
	else if ( (_UseUparaOverPte || _UseCosUphi) && upara > u1_CC) upara_eff = 1. - s_CC*(u1_CC - u0_CC);
	else upara_eff = 1. - s_CC*(upara - u0_CC);
      } else if (_UparaEffCorrOption == 1) { // for _UparaEffCorrOption!=0, use a second order polynomial function
	upara_eff = _WUparaEffParameters[0] + _WUparaEffParameters[1] * upara + 
	  _WUparaEffParameters[2] * upara * upara;
      } else if (_UparaEffCorrOption == 2) { //use slope of slope
	if(upara< u0_CC) upara_eff = 1.;
	else upara_eff = 1. - ( s_CC + _W_seta_CC*fabs(wcand.GetElec().peta()) )*(upara - u0_CC);
      }
    } 

    // pTe-dependent perturbation
    if (_WUparaEffCorrectionPert) {
      float epT = wcand.GetElec().ppt();
      int theepTbin=(int)((epT-25)/5);
      if (theepTbin<0) theepTbin=0;
      if (theepTbin>5) {
        theepTbin=5;
        if (epT>60) theepTbin=6;
        if (epT>70) theepTbin=7;
      }
      float upara_eff_pert=1.;
      int theLumiBin=0;
      if (_Wpert_lumidep) {
        while (wcand.GetElec().getLumi()>_Wpert_lumibins[theLumiBin]) {
          theLumiBin++;
          if (theLumiBin==_Wpert_lumibins.size()) break;
        }
      }
      if (!_WUparaEffCorrectionPertInterpolate) {
        if(upara>_Wpert_u0_CC) upara_eff_pert = 1. + _Wpert_s_CC[theLumiBin].at(theepTbin)*(upara - _Wpert_u0_CC);
      } else {
        if(upara>_Wpert_u0_CC) {
          int bin1=0;
          int bin2=0;
          float d=0;
          _SETefficiencysmear->InterpBinner(epT,bin1,bin2,d);
          float slope=_Wpert_s_CC[theLumiBin].at(bin1)+d*(_Wpert_s_CC[theLumiBin].at(bin2)-_Wpert_s_CC[theLumiBin].at(bin1));
          upara_eff_pert = 1. + slope*(upara - _Wpert_u0_CC);
        }
      }
      upara_eff*=upara_eff_pert;
      //
      upara_eff_pert=1.;
      theLumiBin=0;
      if (_WpertG_lumidep) {
	while (wcand.GetElec().getLumi()>_WpertG_lumibins[theLumiBin]) {
	  theLumiBin++;
	  if (theLumiBin==_WpertG_lumibins.size()) break;
	}
      }
      if (!_WUparaEffCorrectionPertInterpolate2) {
        if(upara>_WpertG_u0_CC) upara_eff_pert = _WpertG_p_CC[theLumiBin].at(theepTbin) + _WpertG_s_CC[theLumiBin].at(theepTbin)*(upara - _WpertG_u0_CC);
        else upara_eff_pert = _WpertG_pm_CC[theLumiBin].at(theepTbin) + _WpertG_sm_CC[theLumiBin].at(theepTbin)*(upara - _WpertG_u0_CC);
      } else {
        int bin1=0;
        int bin2=0;
        float d=0;
        _SETefficiencysmear->InterpBinner(epT,bin1,bin2,d);
        if(upara>_WpertG_u0_CC) {
          float slope=_WpertG_s_CC[theLumiBin].at(bin1)+d*(_WpertG_s_CC[theLumiBin].at(bin2)-_WpertG_s_CC[theLumiBin].at(bin1));
          float absnm=_WpertG_p_CC[theLumiBin].at(bin1)+d*(_WpertG_p_CC[theLumiBin].at(bin2)-_WpertG_p_CC[theLumiBin].at(bin1));
          upara_eff_pert = absnm + slope*(upara - _WpertG_u0_CC);
        } else {
          float slope=_WpertG_sm_CC[theLumiBin].at(bin1)+d*(_WpertG_sm_CC[theLumiBin].at(bin2)-_WpertG_sm_CC[theLumiBin].at(bin1));
          float absnm=_WpertG_pm_CC[theLumiBin].at(bin1)+d*(_WpertG_pm_CC[theLumiBin].at(bin2)-_WpertG_pm_CC[theLumiBin].at(bin1));
          upara_eff_pert = absnm + slope*(upara - _WpertG_u0_CC);
        }
      }
      upara_eff*=upara_eff_pert;
      //
      upara_eff*=0.9;
    }

    // cos(dphi)-dependent perturbation
    if (_WUparaEffCorrectionCDPPert) {
      double uperp = wcand.UPerp();
      double cdp = upara / sqrt(upara*upara + uperp*uperp);
      int thecosdphibin=(int)(cdp/0.2)+4;
      if (thecosdphibin<0) thecosdphibin=0;
      if (thecosdphibin>9) thecosdphibin=9;
      float upara_eff_pert=1.;
      if(upara>_WCDPpert_u0_CC) upara_eff_pert = _WCDPpert_p_CC[thecosdphibin] + _WCDPpert_s_CC[thecosdphibin]*(upara - _WCDPpert_u0_CC);
      upara_eff*=upara_eff_pert;
      upara_eff*=0.95;
    }

    if(wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2,_ApplyTrkPhiModCut) == 1) {
      if(upara<_W_u0_EC) upara_eff = 1.;	    
      else upara_eff = 1. - _W_s_EC*(upara - _W_u0_EC);
    } 
    
    if (_WUparaEffCorrHengne){
      upara_eff = 1.0;
      if ( ut>_CutWUT){
        upara_eff = 1.0;
      }
      else if (_WUparaEffCorrHengneOption==0){
        upara_eff = _WUparaEffCorrHengne_hUParaUPerpEFRT->GetBinContent(_WUparaEffCorrHengne_hUParaUPerpEFRT->FindBin(upara, uperp));
      }
      else if (_WUparaEffCorrHengneOption==1) {
        upara_eff = _WUparaEffCorrHengne_hUTUPhiEFRT->GetBinContent(_WUparaEffCorrHengne_hUTUPhiEFRT->FindBin(ut, uphi));
      }
      else if (_WUparaEffCorrHengneOption==2) {
        double norm1 = _WUparaEffCorrHengne_3GausPars[0];
        double mean1 = _WUparaEffCorrHengne_3GausPars[1];
        double sigma1 = _WUparaEffCorrHengne_3GausPars[2];
        double norm2 = _WUparaEffCorrHengne_3GausPars[3];
        double mean2 = _WUparaEffCorrHengne_3GausPars[4];
        double sigma2 = _WUparaEffCorrHengne_3GausPars[5];
        double norm3 = _WUparaEffCorrHengne_3GausPars[6];
        double mean3 = _WUparaEffCorrHengne_3GausPars[7];
        double sigma3 = _WUparaEffCorrHengne_3GausPars[8];
   
        upara_eff = norm1 * exp( -(upara-mean1)*(upara-mean1)/sigma1/sigma1 )
                  + norm2 * exp( -(upara-mean2)*(upara-mean2)/sigma2/sigma2 ) 
                  + norm3 * exp( -(upara-mean3)*(upara-mean3)/sigma3/sigma3 ) ; 
      }
      else {
        std::cout << "Warning:: No UparaEff is applied! _WUparaEffCorrHengneOption must be 0, or 1." << std::endl;
      }
    }

    if(dummy->Uniform(0., 1.) > upara_eff)   passesUParaCorrection = false;

  }//Uparallel correction  
  
  //
  // Selection efficiencies
  //
  bool  passesTrigEff=true, passesPreselEff=true, passesEMIDEff=true, passesTrkEff=true;
  bool passesLooseTrkEff=true;
  bool passesAddOnEff=true;

  if(_WtrigEffCorrection)
    passesTrigEff= _efficiencysmear->passesTriggerEff(wcand.GetElec(), dummy, TrigVer, _ZBrunNum);
  
  if(_WpreselEffCorrection) 
    passesPreselEff = _efficiencysmear->passesPreselEff(wcand.GetElec(), dummy, 0, &vtx_gen, 0, 1);
  
  passesLooseTrkEff =  _efficiencysmear->passesLooseTrkEff(wcand.GetElec(), &vtx_gen, dummy); 
  
  if(_WIDEffCorrection) 
    passesEMIDEff = _efficiencysmear->passesEMIDEff(wcand.GetElec(), dummy);
  
  if(_WtrkEffCorrection && ! neverUseTrack) {
    passesTrkEff = _efficiencysmear->passesTrkEff(wcand.GetElec(), vtx_gen, dummy) && passesLooseTrkEff ;
    if(_WElecPhiEffCorrection) {
      bool passesElecPhiEff=true;
      passesElecPhiEff = _efficiencysmear->passesElecPhiEff(wcand.GetElec(), dummy, _WElecPhiEffCorrectionUseDetPhi);
      passesTrkEff = passesTrkEff && passesElecPhiEff;	
    }
  }
  // AddOnEff
  if (_ApplyAddOnEff_Wen){
    passesAddOnEff = _efficiencysmear->passesAddOnEff(wcand.GetElec(), true, dummy);
  }
 
  //
  // global flag for whether this event passes all selection efficiencies and uparallel correction
  //
  passesAllEffs = (passesTrigEff && passesPreselEff && passesEMIDEff && passesTrkEff && passesUParaCorrection && passesAddOnEff);
  
  return passesAllEffs;
}

void WAnalysis::MakeU_parControlPlot(std::vector<PMCSEMObj>& emobjs_smear,
                                     PMCSRecoil& recoil_smear,
                                     PMCSMet& met_smear,
                                     PMCSVtx& vtx_gen,
                                     double evtweight,
                                     TRandom3 *dummy) {
  bool neverUseTrack=false;
  bool withCutTrkPt=true;

  double Trigger_Version = dummy->Uniform(0., 1.);

  double WMt=0., WPt=0., WUpara=0., WUperp=0. , Upara=0, Uperp=0;

  PMCSWCand wcand(emobjs_smear[0], recoil_smear, met_smear);
  wcand.getProperties(WMt, WPt, WUpara, WUperp);

  double mt = wcand.TMass();
  double scalarEt_All = _recoilsmear->scalarEt();
  double Lumi = emobjs_smear[0].getLumi();

  // require track pT requirement
  bool passTrkpT = true;
  if(_WtrkEffCorrection)
    if( withCutTrkPt )
      passTrkpT = (emobjs_smear[0].trkpT()>_trkpTCut);

  // scalar ET
  bool passSET=true;
  if (_WSETEffCorrection) {
    if (_WSETEffCorrPTEpert) {
      if (_WSETEffCorrPTEpert==3) passSET=_SETefficiencysmear->passesSETeff(scalarEt_All, emobjs_smear[0].getLumi(), dummy,0,emobjs_smear[0].ppt(), -10, false, false, emobjs_smear[0].deteta(), 0, WUpara, -1); // sloppy EC treatment
      else passSET=_SETefficiencysmear->passesSETeff(scalarEt_All, emobjs_smear[0].getLumi(), dummy,0,emobjs_smear[0].ppt());                                                                                    // just as sloppy
    } else {
      passSET=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),dummy);
    }
  }

  bool passPreSel=true;
  passPreSel = _efficiencysmear->passesPreselEff(wcand.GetElec(), dummy, 0, &vtx_gen, 0, neverUseTrack);
  // add W Ut Cut (same as W cand pT) here to analyse event

  if(passPreSel && wcand.MagRecoil() < _CutWUT && wcand.MagRecoil() >= _CutWUT_lower && wcand.ppt() <_CutWUT && (mt>_WMtCut1) && (mt<_WMtCut2) && (scalarEt_All >= _CutWScalarEt_lower && scalarEt_All < _CutWScalarEt) ) {
    //  passTrkpT && passSET

    if (_PlotUparaOverPte) {
      PMCSEMObj emobj = wcand.GetElec();
      double WElecPt=0., WElecEta=0., WElecDetEta=0., WElecPhi=0., WElecDetPhi=0.;
      emobj.getProperties(WElecPt, WElecEta, WElecPhi, WElecDetEta, WElecDetPhi);
      Upara=WUpara/WElecPt;
    }
    else if ( _PlotCosUphi ) {
      Upara= WUpara / sqrt( WUpara*WUpara + WUperp*WUperp);
    }
    else
      Upara=WUpara;
      Uperp=WUperp;

    float epT=emobjs_smear[0].ppt();
    int theepTbin=(int)((epT-25)/5);
    if (theepTbin>5) {
      theepTbin=5;
      if (epT>60) theepTbin=6;
      if (epT>70) theepTbin=7;
    }
    char theepTbinS[10]; sprintf(theepTbinS, "%d", theepTbin);
    //
    int theetabin=(int)(fabs(emobjs_smear[0].peta())/0.2);
    if (theetabin>4) theetabin=4;
    char theetabinS[10]; sprintf(theetabinS, "%d", theetabin);
    //
    int thecosdphibin=(int)(WUpara/WPt/0.2)+4;
    if (thecosdphibin<0) thecosdphibin=0;
    if (thecosdphibin>9) thecosdphibin=9;
    char thecosdphibinS[10]; sprintf(thecosdphibinS, "%d", thecosdphibin);

    if (wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2,_ApplyTrkPhiModCut) == 0){
      _histos.Fill1D("hWcandUpara_noEff_CC", Upara, evtweight);
      _histos.Fill2D("hWcandUparaUperp_noEff_CC", Upara, Uperp, evtweight);
      _histos.Fill1D("hWcandSET_noEff_CC", scalarEt_All, evtweight);
      _histos.Fill1D("hWcandLumi_noEff_CC", Lumi, evtweight);
      _histos.Fill2D("hWcandSETLumi_noEff_CC", scalarEt_All, Lumi, evtweight);
      if (theepTbinS>=0) {
        _histos.Fill1D(string("hWcandUpara_noEff_CC_")+theepTbinS, Upara, evtweight);
        _histos.Fill1D(string("hWcandUpara_noEff_CC_")+theepTbinS+"_"+theetabinS, Upara, evtweight);
      }
      _histos.Fill1D("hWcandElecPt_noEff_CC", epT, evtweight);
      _histos.Fill1D(string("hWcandElecPt_noEff_CC_")+theetabinS, epT, evtweight);
      _histos.Fill1D("hWcandElecEta_noEff_CC", emobjs_smear[0].peta(), evtweight);
      if (theepTbinS>=0) _histos.Fill1D(string("hWcandElecEta_noEff_CC_")+theepTbinS, emobjs_smear[0].peta(), evtweight);
      _histos.Fill1D(string("hWcandUpara_noEff_CC_cosdphi_")+thecosdphibinS, Upara, evtweight);
      _histos.Fill1D(string("hWcandUpara_noEff_CC_cosdphi_")+thecosdphibinS+"_"+theepTbinS, Upara, evtweight);
    } else if (wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2,_ApplyTrkPhiModCut) == 1){
      _histos.Fill1D("hWcandUpara_noEff_EC", Upara, evtweight);
      if (theepTbinS>=0) {
        _histos.Fill1D(string("hWcandUpara_noEff_EC_")+theepTbinS, Upara, evtweight);
        _histos.Fill1D(string("hWcandUpara_noEff_EC_")+theepTbinS+"_"+theetabinS, Upara, evtweight);
      }
      _histos.Fill1D("hWcandElecPt_noEff_EC", epT, evtweight);
      _histos.Fill1D(string("hWcandElecPt_noEff_EC_")+theetabinS, epT, evtweight);
      _histos.Fill1D("hWcandElecEta_noEff_EC", emobjs_smear[0].peta(), evtweight);
      if (theepTbinS>=0) _histos.Fill1D(string("hWcandElecEta_noEff_EC_")+theepTbinS, emobjs_smear[0].peta(), evtweight);
      _histos.Fill1D(string("hWcandUpara_noEff_EC_cosdphi_")+thecosdphibinS, Upara, evtweight);
      _histos.Fill1D(string("hWcandUpara_noEff_EC_cosdphi_")+thecosdphibinS+"_"+theepTbinS, Upara, evtweight);
    }

    bool passesEffs = passesAllEffs(wcand, vtx_gen, dummy, Trigger_Version, neverUseTrack);
    bool passesTrkEff=true;
    if (neverUseTrack){
      passesTrkEff = _efficiencysmear->passesTrkEff(wcand.GetElec(), vtx_gen, dummy);
      passesEffs = passesEffs && passesTrkEff;
    }

    //
    // events pass all efficiencies (including selection efficiencies and uparallel efficiency)
    //
    if(passesEffs) {
      if (wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2,_ApplyTrkPhiModCut) == 0){
        _histos.Fill1D("hWcandUpara_emEff_CC", Upara, evtweight);
        _histos.Fill2D("hWcandUparaUperp_emEff_CC", Upara, Uperp, evtweight);
	if (theepTbinS>=0) {
          _histos.Fill1D(string("hWcandUpara_emEff_CC_")+theepTbinS, Upara, evtweight);
          _histos.Fill1D(string("hWcandUpara_emEff_CC_")+theepTbinS+"_"+theetabinS, Upara, evtweight);
        }
        _histos.Fill1D("hWcandElecPt_emEff_CC", epT, evtweight);
        _histos.Fill1D(string("hWcandElecPt_emEff_CC_")+theetabinS, epT, evtweight);
        _histos.Fill1D("hWcandElecEta_emEff_CC", emobjs_smear[0].peta(), evtweight);
        if (theepTbinS>=0) _histos.Fill1D(string("hWcandElecEta_emEff_CC_")+theepTbinS, emobjs_smear[0].peta(), evtweight);
        _histos.Fill1D(string("hWcandUpara_emEff_CC_cosdphi_")+thecosdphibinS, Upara, evtweight);
        _histos.Fill1D(string("hWcandUpara_emEff_CC_cosdphi_")+thecosdphibinS+"_"+theepTbinS, Upara, evtweight);
      } else if (wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2,_ApplyTrkPhiModCut) == 1){
        _histos.Fill1D("hWcandUpara_emEff_EC", Upara, evtweight);
	if (theepTbinS>=0) {
          _histos.Fill1D(string("hWcandUpara_emEff_EC_")+theepTbinS, Upara, evtweight);
          _histos.Fill1D(string("hWcandUpara_emEff_EC_")+theepTbinS+"_"+theetabinS, Upara, evtweight);
        }
        _histos.Fill1D("hWcandElecPt_emEff_EC", epT, evtweight);
        _histos.Fill1D(string("hWcandElecPt_emEff_EC_")+theetabinS, epT, evtweight);
        _histos.Fill1D("hWcandElecEta_emEff_EC", emobjs_smear[0].peta(), evtweight);
        if (theepTbinS>=0) _histos.Fill1D(string("hWcandElecEta_emEff_EC_")+theepTbinS, emobjs_smear[0].peta(), evtweight);
        _histos.Fill1D(string("hWcandUpara_emEff_EC_cosdphi_")+thecosdphibinS, Upara, evtweight);
        _histos.Fill1D(string("hWcandUpara_emEff_EC_cosdphi_")+thecosdphibinS+"_"+theepTbinS, Upara, evtweight);
      }
      if(passTrkpT) {
        if (wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2,_ApplyTrkPhiModCut) == 0){
          _histos.Fill1D("hWcandUpara_emtrkEff_CC", Upara, evtweight);
          _histos.Fill2D("hWcandUparaUperp_emtrkEff_CC", Upara, Uperp, evtweight);
	  if (theepTbinS>=0) {
            _histos.Fill1D(string("hWcandUpara_emtrkEff_CC_")+theepTbinS, Upara, evtweight);
            _histos.Fill1D(string("hWcandUpara_emtrkEff_CC_")+theepTbinS+"_"+theetabinS, Upara, evtweight);
          }
          _histos.Fill1D("hWcandElecPt_emtrkEff_CC", epT, evtweight);
          _histos.Fill1D(string("hWcandElecPt_emtrkEff_CC_")+theetabinS, epT, evtweight);
          _histos.Fill1D("hWcandElecEta_emtrkEff_CC", emobjs_smear[0].peta(), evtweight);
          if (theepTbinS>=0) _histos.Fill1D(string("hWcandElecEta_emtrkEff_CC_")+theepTbinS, emobjs_smear[0].peta(), evtweight);
          _histos.Fill1D(string("hWcandUpara_emtrkEff_CC_cosdphi_")+thecosdphibinS, Upara, evtweight);
          _histos.Fill1D(string("hWcandUpara_emtrkEff_CC_cosdphi_")+thecosdphibinS+"_"+theepTbinS, Upara, evtweight);
        } else if (wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2,_ApplyTrkPhiModCut) == 1){
          _histos.Fill1D("hWcandUpara_emtrkEff_EC", Upara, evtweight);
          if (theepTbinS>=0) {
            _histos.Fill1D(string("hWcandUpara_emtrkEff_EC_")+theepTbinS, Upara, evtweight);
            _histos.Fill1D(string("hWcandUpara_emtrkEff_EC_")+theepTbinS+"_"+theetabinS, Upara, evtweight);
          }
          _histos.Fill1D("hWcandElecPt_emtrkEff_EC", epT, evtweight);
          _histos.Fill1D(string("hWcandElecPt_emtrkEff_EC_")+theetabinS, epT, evtweight);
          _histos.Fill1D("hWcandElecEta_emtrkEff_EC", emobjs_smear[0].peta(), evtweight);
          if (theepTbinS>=0) _histos.Fill1D(string("hWcandElecEta_emtrkEff_EC_")+theepTbinS, emobjs_smear[0].peta(), evtweight);
          _histos.Fill1D(string("hWcandUpara_emtrkEff_EC_cosdphi_")+thecosdphibinS, Upara, evtweight);
          _histos.Fill1D(string("hWcandUpara_emtrkEff_EC_cosdphi_")+thecosdphibinS+"_"+theepTbinS, Upara, evtweight);
        }
        if(passSET) {
          if (wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2,_ApplyTrkPhiModCut) == 0){
            _histos.Fill1D("hWcandUpara_emtrksetEff_CC", Upara, evtweight);
            _histos.Fill2D("hWcandUparaUperp_emtrksetEff_CC", Upara, Uperp, evtweight);
            _histos.Fill1D("hWcandSET_emtrksetEff_CC", scalarEt_All, evtweight);
            _histos.Fill1D("hWcandLumi_emtrksetEff_CC", Lumi, evtweight);
            _histos.Fill2D("hWcandSETLumi_emtrksetEff_CC", scalarEt_All, Lumi, evtweight);
	    if (theepTbinS>=0) {
              _histos.Fill1D(string("hWcandUpara_emtrksetEff_CC_")+theepTbinS, Upara, evtweight);
              _histos.Fill1D(string("hWcandUpara_emtrksetEff_CC_")+theepTbinS+"_"+theetabinS, Upara, evtweight);
            }
            _histos.Fill1D("hWcandElecPt_emtrksetEff_CC", epT, evtweight);
            _histos.Fill1D(string("hWcandElecPt_emtrksetEff_CC_")+theetabinS, epT, evtweight);
            _histos.Fill1D("hWcandElecEta_emtrksetEff_CC", emobjs_smear[0].peta(), evtweight);
            if (theepTbinS>=0) _histos.Fill1D(string("hWcandElecEta_emtrksetEff_CC_")+theepTbinS, emobjs_smear[0].peta(), evtweight);
            _histos.Fill1D(string("hWcandUpara_emtrksetEff_CC_cosdphi_")+thecosdphibinS, Upara, evtweight);
            _histos.Fill1D(string("hWcandUpara_emtrksetEff_CC_cosdphi_")+thecosdphibinS+"_"+theepTbinS, Upara, evtweight);
          } else if (wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2,_ApplyTrkPhiModCut) == 1){
            _histos.Fill1D("hWcandUpara_emtrksetEff_EC", Upara, evtweight);
            if (theepTbinS>=0) {
              _histos.Fill1D(string("hWcandUpara_emtrksetEff_EC_")+theepTbinS, Upara, evtweight);
              _histos.Fill1D(string("hWcandUpara_emtrksetEff_EC_")+theepTbinS+"_"+theetabinS, Upara, evtweight);
            }
            _histos.Fill1D("hWcandElecPt_emtrksetEff_EC", epT, evtweight);
            _histos.Fill1D(string("hWcandElecPt_emtrksetEff_EC_")+theetabinS, epT, evtweight);
            _histos.Fill1D("hWcandElecEta_emtrksetEff_EC", emobjs_smear[0].peta(), evtweight);
            if (theepTbinS>=0) _histos.Fill1D(string("hWcandElecEta_emtrksetEff_EC_")+theepTbinS, emobjs_smear[0].peta(), evtweight);
            _histos.Fill1D(string("hWcandUpara_emtrksetEff_EC_cosdphi_")+thecosdphibinS, Upara, evtweight);
            _histos.Fill1D(string("hWcandUpara_emtrksetEff_EC_cosdphi_")+thecosdphibinS+"_"+theepTbinS, Upara, evtweight);
          }
        }
      }
    }
  }
}

// Analyze an event
void WAnalysis::analyzeEvent(PMCSEvent& pmcsevent, TRandom3 *dummy) {

  // this weight will be 1 if you set reweight=false in the configuration file
  double evtweight = pmcsevent.GetEvtWeight();

  // fill event counter
  _histos.Fill1D("hWcandEvtCnt", 1, evtweight);

  // get run number
  int runNo = pmcsevent.GetRunNo();
  
  //ZBRunNo for Trigger
  _ZBrunNum  = pmcsevent.GetRunNo();

  // cuts on W truth
  double TrueWPt = pmcsevent.GetWZBoson().ppt();
  double TrueWPhi = pmcsevent.GetWZBoson().pphi();
  double TrueWMass = pmcsevent.GetWZBoson().Mass();

  if (TrueWPt<_CutTrueWPtLo) return;
  if (TrueWPt>_CutTrueWPtHi) return;
  if (TrueWPhi<_CutTrueWPhiLo) return;
  if (TrueWPhi>_CutTrueWPhiHi) return;
  if (TrueWMass<_CutTrueWMassLo) return;
  if (TrueWMass>_CutTrueWMassHi) return;


  // PV, EM objects, recoil and MET
  PMCSVtx vtx_gen = pmcsevent.GetVtx();
  vector<PMCSEMObj> emobjs_gen = pmcsevent.GetEMObjs();
  PMCSRecoil recoil_gen = pmcsevent.GetRecoil();
  PMCSMet met_gen = pmcsevent.GetMet();

  // Get instantaneous luminosity, propagate to our helper objects, if needed
  double luminosity = pmcsevent.GetInstLumi();
  recoil_gen.SetLumi(luminosity);

  // no photon merging
  vector<PMCSEMObj> raw_emobjs_gen = pmcsevent.GetRawEMObjs(); 

  // simple photon merging
  vector<PMCSEMObj> raw_emobjs_gen_wfsr = pmcsevent.GetRawEMObjsWFSR();  

  PMCSEMObj Smeared_Nu;
  double recoilX_orig = recoil_gen.Recoilx();
  double recoilY_orig = recoil_gen.Recoily();

  // recoil system before Uparallel correction
  PMCSRecoil recoil_smear_beforeUparaCorr = _recoilsmear->SmearRecoil(recoil_gen, dummy);
  TVector2 recoil_vec_beforeUparaCorr(recoil_smear_beforeUparaCorr.Recoilx(), recoil_smear_beforeUparaCorr.Recoily());

  // Set Luminosity and RecoilVec to _emsmear, to be used for Lumi/UPara dependent Scale/Offset
  _emsmear->SetLuminosity(luminosity);
  _emsmear->SetRunNumber(runNo);
  _emsmear->SetRecoilVec(recoil_vec_beforeUparaCorr);

  //Set run number for run3, 4 dependent efficiency application
  _efficiencysmear->SetRunNumber(runNo);

  // smear EM objects, recoil system and calculate smeared MET
  // do not simulate energies below electron window first since it depends on uparallel 
  // which will be calculated later
  _emsmear->Set_EnergySim_ElecWindow(false);
  vector<PMCSEMObj> emobjs_smear = _emsmear->SmearEMObjs(emobjs_gen, dummy);
  
  //std::cout <<emobjs_gen.size() << std::endl ;
  Int_t check_nu_rem =  emobjs_smear.size();
  //std::cout << check_nu_rem << std::endl;
  for(int inu=0;inu < emobjs_smear.size(); inu++){
    PMCSEMObj test_nu = (emobjs_smear.at(inu));
    //std::cout << test_nu.ppid() << std::endl;
    if (abs(test_nu.ppid()) == 12. || abs(test_nu.ppid()) == 14. || abs(test_nu.ppid()) == 16. ){
      Smeared_Nu = test_nu;
      emobjs_smear.erase(emobjs_smear.begin()+inu,emobjs_smear.end()-(emobjs_smear.size()-(inu+1)));
    }
  }
  // std::cout << "end event" << std::endl;
  Int_t check_nu_rem1 =  emobjs_smear.size();
  if (!((check_nu_rem1+1) == check_nu_rem)){
    //  std::cerr <<check_nu_rem - check_nu_rem1 << " Neutrino's removed" << std::endl;
    //abort();
  }
  
  for(int inu=0;inu < emobjs_smear.size(); inu++){
    PMCSEMObj test_nu = (emobjs_smear.at(inu));
    if (abs(test_nu.ppid()) == 12. || abs(test_nu.ppid()) == 14. || abs(test_nu.ppid()) == 16.){
      std::cerr << "Neutrino removal failure" << std::endl;
      abort();
    }
  } 
  
  // sort smeared electrons according to pT
  sort(emobjs_smear.begin(), emobjs_smear.end(), ComparePt);
  sort(emobjs_gen.begin(), emobjs_gen.end(), ComparePt);    


  // check generator electron pT distributions for different eta regions
  if(raw_emobjs_gen.size()>0) {
    if(raw_emobjs_gen[0].IsCC(1.05, true, _ApplyTrkPhiModCut)) {   // truth electron in CC fiducial region
      int FineEtaRegion_CC_gen = raw_emobjs_gen[0].FineEtaRegion_CC(raw_emobjs_gen[0].eta(), 1.05, true, _ApplyTrkPhiModCut);
      char sn_FineEtaRegion_CC_gen[10];   sprintf(sn_FineEtaRegion_CC_gen, "%d", FineEtaRegion_CC_gen);

      _histos.Fill1D(TString("hWcandMCElecPt_EtaBin_CC_NoCuts_")+sn_FineEtaRegion_CC_gen, raw_emobjs_gen[0].ppt(), evtweight);
    }
  }


  // at least one EM Objects
  if(((emobjs_smear.size() >= 1) && (!emobjs_smear[0].IsLostInAcrack())) ||  (_makegenROOTfile_for_WFIT && (emobjs_smear.size() >= 1) ) ) {

    // need to apply uparallel correction here
    // modify recoil_smear_beforeUparaCorr to recoil_smear
    // recalculate MET object      
    PMCSRecoil recoil_smear = recoil_smear_beforeUparaCorr;

    // First set luminosity and uparallel for electron in order to do simulation of energies below electron window
    // which is luminosity and uparallel dependent
    // also set ScalarEt for simulation of energies below elecron window (added on Jan. 28, 2011 for UParaCorrOption==3).
    // Then add energies below electron window
    TVector2 recoil_vec(recoil_smear.Recoilx(), recoil_smear.Recoily());
    double ScalarEt = _recoilsmear->scalarEt();
    for(int ielec=0; ielec<emobjs_smear.size(); ielec++) {
      // new requirement, only do this for electron, similar already included in EMSmear
      // here I want to make sure that we only do this for real electrons
      //moved ppt requirement two lines down 5/30/2012 for ZAnalysis EnergyScale to run, consistent with ZAnalysis
      emobjs_smear[ielec].SetLumi(luminosity);
      emobjs_smear[ielec].SetScalarEt(ScalarEt);
      
      if(abs(emobjs_smear[ielec].ppt()) > 15.) {
	TVector2 elec_vec(emobjs_smear[ielec].ppx(), emobjs_smear[ielec].ppy());
	double upara_elec = recoil_vec*elec_vec.Unit();
	double uperp_elec = recoil_vec*(elec_vec.Unit().Rotate(TMath::Pi()/2.0));
	emobjs_smear[ielec].SetUPara(upara_elec);
	emobjs_smear[ielec].SetUPerp(uperp_elec);
	
	_emsmear->SmearEnergyUnderElecWindow(emobjs_smear[ielec],dummy,true);
      }
    }
    
    // smear neutrino the same way as electron for the ratio method
    Smeared_Nu.SetLumi(luminosity);
    Smeared_Nu.SetScalarEt(ScalarEt);
    TVector2 elec_vec(Smeared_Nu.ppx(), Smeared_Nu.ppy());
    double upara_elec = recoil_vec*elec_vec.Unit();
    double uperp_elec = recoil_vec*(elec_vec.Unit().Rotate(TMath::Pi()/2.0));
    Smeared_Nu.SetUPara(upara_elec);
    Smeared_Nu.SetUPerp(uperp_elec);
    _emsmear->SmearEnergyUnderElecWindow(Smeared_Nu, dummy);

    // will only apply uparallel correction for the highest electron since we set merge_fsr_photons_met = false
    if(_WUparaCorrection)
      _recoilsmear -> applyUparaCorrection(emobjs_smear, recoil_smear_beforeUparaCorr, recoil_smear, 1);
     
    //
    // include photons in the smeared recoil system
    // the photon response is described in EMSmear::SmearPhotonEnergy
    //
    double recoilX_component = recoil_smear.Recoilx();
    double recoilY_component = recoil_smear.Recoily();
    for(int i=0; i<emobjs_smear.size(); i++) {
      if (!(emobjs_gen[i].getIndex() == emobjs_smear[0].getIndex())){
	recoilX_orig += emobjs_gen[i].ppx();
	recoilY_orig += emobjs_gen[i].ppy();
      }
      if (i > 0){
	if (!_WsimuFSRcracks) {
	  recoilX_component += emobjs_smear[i].ppx();
	  recoilY_component += emobjs_smear[i].ppy();
	} else {
	  float deteta=emobjs_smear[i].deteta();
	  float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	  if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>(_WsimuFSRcracksWidth))&&(phimod<(1-_WsimuFSRcracksWidth)))) {
	    recoilX_component += emobjs_smear[i].ppx();
	    recoilY_component += emobjs_smear[i].ppy();
	  }
	}
      }
    }
    // reset smeared recoil
    recoil_smear.SetRecoil(recoilX_component, recoilY_component);

    // calculate met using emobjs and recoil information, will only use the highest electron for met calculation
    // to match with the definition of met used in wmass_analysis
    PMCSMet met_smear = PMCSMet(emobjs_smear, recoil_smear);
    if(emobjs_smear.size() >= 1) { // will overwrite met_smear for the case with at least one electron
       double metX_component = -(emobjs_smear[0].ppx()+recoil_smear.Recoilx());
       double metY_component = -(emobjs_smear[0].ppy()+recoil_smear.Recoily());
       met_smear.SetMet(metX_component, metY_component);
    } 

    // UT reweighting, if requested
    if (_UTreweighting) {
      Float_t Jrec=recoil_smear.Recoil();
      Float_t Jwt=_UTreweightingWT[0]+_UTreweightingWT[1]*(Jrec/20.)+_UTreweightingWT[2]*pow(Jrec/20.,2)+_UTreweightingWT[3]*pow(Jrec/20.,3)+_UTreweightingWT[4]*pow(Jrec/20.,4);
      evtweight*=Jwt;   // this is not completely without danger, assubsequent code can get the weight from the PMVDEvent object
    }

    // construct W candidate
    PMCSWCand wcand(emobjs_smear[0], recoil_smear, met_smear);
    if (_makegenROOTfile_for_WFIT) {
      fillWFitFile(pmcsevent.GetEvtWeight(),pmcsevent.GetWZBoson().Mass(), wcand, met_gen, emobjs_gen, pmcsevent.GetWZBoson().ppz(),Smeared_Nu,0, recoilX_orig, recoilY_orig,  luminosity, vtx_gen.vtxz()  , pmcsevent.pdfreweights, pmcsevent , ScalarEt , emobjs_smear);
      Wfittree->Fill();
    }
    
    //
    // apply offline selection cuts here
    //
    if((emobjs_smear[0].ppt() > _CutEPT) && (met_smear.met()>_CutMET) ) {      
      
      _recoilsmear->InputLuminosity(luminosity);

      if(_makeU_parControlPlot) {
	WAnalysis::MakeU_parControlPlot(emobjs_smear, recoil_smear, met_smear, vtx_gen, evtweight, dummy);
	return;
      }


      // transverse mass
      double mt = wcand.TMass();
      
      // require track pT requirement
      bool passTrkpT = false;
      if(_WtrkEffCorrection) passTrkpT = (emobjs_smear[0].trkpT()>_trkpTCut);
      else passTrkpT = true;

      double scalarEt_All = _recoilsmear->scalarEt();
      double scalarEt_ZB = _recoilsmear->scalarEt_ZB();
      double scalarEt_ZB_NoScale = _recoilsmear->scalarEt_ZB_NoScale();

      // scalar ET
      bool passSET=true;
      if (_WSETEffCorrection) {
	if (_WSETEffCorrPTEpert) {
          if (_WSETEffCorrPTEpert==3) passSET=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),dummy,0,emobjs_smear[0].ppt(), -10, false, false, emobjs_smear[0].deteta(), 0, wcand.UPara(), -1); // sloppy EC treatment
          else passSET=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),dummy,0,emobjs_smear[0].ppt());                                                                                           // just as sloppy
	} else {
	  passSET=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),dummy);
	}
	//
	if (_WSETEffCorrPedantic && passSET) {
	  float lumi=emobjs_smear[0].getLumi();
	  float r=1;
	  if (lumi>=0 && lumi<2) {
	    r=(_WSETEffCorrPedanticPar[0]+_WSETEffCorrPedanticPar[1]*(lumi-0));
	  } else if (lumi>=2 && lumi<4) {
	    r=(_WSETEffCorrPedanticPar[2]+_WSETEffCorrPedanticPar[3]*(lumi-2));
	  } else if (lumi>=4 && lumi<6) {
	    r=(_WSETEffCorrPedanticPar[4]+_WSETEffCorrPedanticPar[5]*(lumi-4));
	  } else if (lumi>=6 && lumi<8) {
	    r=(_WSETEffCorrPedanticPar[6]+_WSETEffCorrPedanticPar[7]*(lumi-6));
	  } else if (lumi>=8) {
	    r=(_WSETEffCorrPedanticPar[8]+_WSETEffCorrPedanticPar[9]*(lumi-8));
	  }
	  float theRnd=dummy->Uniform(0.,1.);
	  if (theRnd>r) passSET=false;
	}
      }

      // add W Ut Cut (same as W cand pT) here
      if(wcand.MagRecoil() < _CutWUT && wcand.MagRecoil() >= _CutWUT_lower && wcand.ppt() <_CutWUT && (mt>_WMtCut1) && (mt<_WMtCut2) && passTrkpT && passSET && (scalarEt_All >= _CutWScalarEt_lower && scalarEt_All < _CutWScalarEt) ) {
	double Trigger_Version = dummy->Uniform(0., 1.);
	bool passesEffs = passesAllEffs(wcand, vtx_gen, dummy, Trigger_Version);
	
	//
	// events pass all efficiencies (including selection efficiencies and uparallel efficiency)
	//
	if(passesEffs) {
	  
	  PMCSEMObj emobj = wcand.GetElec();
	  PMCSMet met = wcand.GetMet();
	  
	  double WMt=0., WPt=0., WUpara=0., WUperp=0.;
	  double WElecPt=0., WElecEta=0., WElecDetEta=0., WElecPhi=0., WElecDetPhi=0.;
	  double WElecPhiTrkAtDCA=0., WElecPhiTrkAtEM3=0., WElecDetPhiCALO=0.;
	  
	  double WMet=0., WMetPhi=0.;
	  wcand.getProperties(WMt, WPt, WUpara, WUperp);
	  emobj.getProperties(WElecPt, WElecEta, WElecPhiTrkAtDCA, WElecDetEta, WElecDetPhiCALO);
	  met.getProperties(WMet, WMetPhi);
	  
	  double WPx=wcand.ppx();
	  double WPy=wcand.ppy();
	  double WPhi=kinem::phi(WPx, WPy);
	  double WRecoilPt=wcand.MagRecoil();
	  double WRecoilPx=(wcand.GetRecoilVec()).Px();
	  double WRecoilPy=(wcand.GetRecoilVec()).Py();
	  double WRecoilPhi=(wcand.GetRecoilVec()).Phi();
	  double Ut=sqrt(WRecoilPx*WRecoilPx+WRecoilPy*WRecoilPy);
	  TVector2 met_vect(met.metx(), met.mety());
 	  double singVariable = 0;
	  double singVariable_gen = 0;
	  //double singVariable_LongUnSmeared = 0; 

	  vector<PMCSEMObj> emobjs_gen = pmcsevent.GetEMObjs();
	  int ielec = 0;
	  for (ielec = 0; ielec < emobjs_gen.size(); ielec++)
	    if (TMath::Abs(emobjs_gen[ielec].GetPID()) == 11) break;
	  PMCSWCand wcand_gen(emobjs_gen[ielec], recoil_gen, met_gen);
	  int FSRInConeNum = emobjs_gen[ielec].FSRnInCone();

	  // Fills the variables for Singularity Variable study
	  if(_doSingVariableStudy) {
	    singVariable = (double) (wz_utils::SingularityVariable(wcand, _wmass_default, dummy));
	    singVariable_gen = (double) (wz_utils::SingularityVariable(wcand_gen, _wmass_default, dummy));
	    // singVariable_LongUnSmeared = (double) (wz_utils::SingularityVariable_LongUnSmeared(wcand, wcand_gen, _wmass_default, dummy));
	  }
	 
	  if(_wmass_reweight) {
	    // Get Breit-Wigner Weight
	    vector<double> ReweightFactorMass = BreitWignerReweightMass(pmcsevent);
	    
	    char sn[10];
	    double massweight = evtweight; 
	    
	    for(int i=0; i<ReweightFactorMass.size(); i++) {
	      massweight = evtweight * ReweightFactorMass[i];   //also include the whole event weight		  
	      sprintf(sn,"%d", i); 
	      //note: some generator level histograms of these variables are in _doSingVariableStudy
	      _histos.Fill1D(string("hWcandMt_")+sn, WMt, massweight);
	      _histos.Fill1D(string("hWcandElecPt_")+sn, WElecPt, massweight);
	      _histos.Fill1D(string("hWcandMet_")+sn, WMet, massweight);
	    
	      if(_doSingVariableStudy){
		//_histos.Fill1D(string("hWcandSingVariable_")+sn, singVariable, massweight);
		//if(_doSVgeneratorstudy) _histos.Fill1D(string("hWcandSingVariable_Gen_")+sn, singVariable_gen, massweight);
		//	if(_doSVnolongitudinalstudy) _histos.Fill1D(string("hWcandSingVariable_LongUnSmeared_")+sn, singVariable_LongUnSmeared, massweight);
	      }
	    }
	  }//w mass reweight

	  if(_doPdfReweight) {
	    
	    char sn[10];
	    double massweight; 

	    for(int i=0; i<45; i++) {
	      //	      cout << i << " " << massweight << " Writing PDF hists" << endl;
	      massweight = evtweight * pmcsevent.pdfreweights[i];   //also include the whole event weight		  
	      sprintf(sn,"%d", i); 
	      _histos.Fill1D(string("hWcandMt_PDF_")+sn, WMt, massweight);
	      _histos.Fill1D(string("hWcandElecPt_PDF_")+sn, WElecPt, massweight);
	      _histos.Fill1D(string("hWcandMet_PDF_")+sn, WMet, massweight);
	      //	      cout << "Wrote PDF hist" << endl;
	      if(_doSingVariableStudy){
		//_histos.Fill1D(string("hWcandSingVariable_PDF_")+sn, singVariable, massweight);
		//if(_doSVgeneratorstudy) _histos.Fill1D(string("hWcandSingVariable_Gen_PDF_")+sn, singVariable_gen, massweight);
		//	if(_doSVnolongitudinalstudy) _histos.Fill1D(TString::Format("hWcandSingVariable_LongUnSmeared_PDF_")+sn, singVariable_LongUnSmeared, massweight);
	      }
	      
	    }
	  }//w mass reweight

	  
          // W candidates with electrons in CC region
          if(wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _ApplyTrkPhiModCut) == 0) {
            _ngoodWCandCC++;
            _ngoodWCand++;
            if (emobjs_smear[0].ppid()==22.){
              // protection
              emobjs_smear[0].SetTrkpT(emobjs_smear[0].ppt());

              if (emobjs_smear.size()>1) {
                std::cout << "Photon used :      partid = " << emobjs_smear[0].ppid()
                          << "pt = " <<  emobjs_smear[0].ppt() <<  " deteta = " <<  emobjs_smear[0].deteta()
                          << " detphi = " <<  emobjs_smear[0].detphi() << std::endl;
                if ((emobjs_smear[0].ppt() > 25.) || (emobjs_smear[1].ppt() > 25.)  ){
                  _histos.Fill2D("h_false_Phi_v_Eta",emobjs_smear[0].deteta(),emobjs_smear[0].detphi(),pmcsevent.GetEvtWeight());
                }
                for (Int_t sahal =1; sahal < emobjs_smear.size(); sahal++){
                  std::cout << "Electron Ignored : partid = " << emobjs_smear[sahal].ppid()
                            << "pt = " <<  emobjs_smear[sahal].ppt()
                            <<  " deteta = " <<  emobjs_smear[sahal].deteta()
                            <<  " detphi = " <<  emobjs_smear[sahal].detphi() << std::endl;
                  if ((emobjs_smear[sahal].ppt() > 25.) || (emobjs_smear[0].ppt() > 25.)){
                    _histos.Fill2D("h_true_Phi_v_Eta",emobjs_smear[0].deteta(),emobjs_smear[0].detphi(),pmcsevent.GetEvtWeight());
                  }
                }
              }
            }

	    // check E/p
            double TrkPt = emobj.trkpT();
            // calorimeter phi
            int mod_phi = (int)(WElecDetPhi/(TMath::Pi()/16.));
            if(mod_phi>31) mod_phi=31;
            double PhiMod =  (fmod(16.*WElecDetPhi/TMath::Pi(), 1.0));
            char sn_mod[10]; sprintf(sn_mod, "%d", mod_phi);
            // track phi
	        WElecPhiTrkAtEM3 = emobj.trkphiem3();
            int mod_trkphi = (int)(WElecPhiTrkAtEM3/(TMath::Pi()/16.));
            if(mod_trkphi>31) mod_trkphi=31;
            double trkPhiMod =  (fmod(16.*WElecPhiTrkAtEM3/TMath::Pi(), 1.0));
            char sn_trkmod[10]; sprintf(sn_trkmod, "%d", mod_trkphi);
            // calculate E/p
            double EOverP = WElecPt/TrkPt;

	    // MW
 	    // fill SET histograms for different electron pTs...
 	    // calculate electron pT bin for W electron
 	    double pTe = emobj.ppt(); 
 	    double EpToverSET = 0;
 	    if(scalarEt_All>0) EpToverSET = pTe/scalarEt_All;
 	    int pTebin=(int)((pTe-25)/5);
 	    if(pTebin<0) pTebin=0;
 	    if( (pTe>50) && (pTe<60) ) pTebin=5;
 	    if(pTe>60) pTebin=6;
 	    char pTebin_sn[10]; sprintf(pTebin_sn, "%d", pTebin);

	    //
	    // now we can do some systematic studies by varying the cuts
	    //
	    if(_consistency_check) {
	      bool passCut_under_study =  wz_utils::passCut(_cut_under_study, _invert_cut,
							    runNo, _runNo_lowcut, _runNo_highcut,
							    luminosity, _InstLumi_lowcut, _InstLumi_highcut,
							    scalarEt_All, _ScalarEt_lowcut, _ScalarEt_highcut,
							    WElecEta, _ElecEta_cut,
							    WElecDetEta, _ElecDetEta_lowcut, _ElecDetEta_highcut,
							    trkPhiMod, _ElecPhiMod_cut,
							    WUpara, _UPara_lowcut, _UPara_highcut,
							    WElecPt, _ElecPt_lowcut, _ElecPt_highcut,
							    WElecPhiTrkAtDCA, _ElecPhi_lowcut, _ElecPhi_highcut,
							    WRecoilPhi, _RecoilPhi_lowcut, _RecoilPhi_highcut);
	      if(!passCut_under_study) return;
	    }

	    // MW
	    if( _MakeEleakTable && (wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _ApplyTrkPhiModCut) == 0) ){
	      double eleak = emobjs_smear[0].EnergyLeakage();
	      int LeakBin = (int)((emobjs_smear[0].peta())/0.2)+7;
	      if (LeakBin<0) LeakBin=0;
	      if (LeakBin>13) LeakBin=13;
	      _LeakSum[LeakBin]+=eleak;
	      _LeakCount[LeakBin]++;
	    }
	  
 	    _histos.Fill1D(string("hWcandScalarEt_ElecPtBin_")+pTebin_sn, scalarEt_All, evtweight);
 	    _histos.Fill1D(string("hWcandSEToverEpt_ElecPtBin_")+pTebin_sn, EpToverSET, evtweight);
 	    if(pTe>50) _histos.Fill1D("hWcandScalarEt_Tail", scalarEt_All, evtweight);
 	    if(pTe>50) _histos.Fill1D("hWcandSEToverEpt_Tail", EpToverSET, evtweight);
 	    //MW

	    _histos.Fill1D("hWcandEOverP", EOverP, evtweight);
            _histos.Fill1D(TString("hWcandEOverP_Mod_")+sn_mod, EOverP, evtweight);
            if (TrkPt>1) _histos.Fill1D(TString("hWcandEOverP_TrkMod_")+sn_trkmod, EOverP, evtweight);

            if(EOverP>0.9 && EOverP<1.3) {
              _histos.FillProfile("hWcandEOverP_V_ElecPhiMod", PhiMod, EOverP, evtweight);
              _histos.FillProfile("hWcandEOverP_V_ElecTrkPhiMod", trkPhiMod, EOverP, evtweight);

              _histos.FillProfile(TString("hWcandEOverP_V_ElecPhiMod_")+sn_mod, PhiMod, EOverP, evtweight);
              _histos.FillProfile(TString("hWcandEOverP_V_ElecTrkPhiMod_")+sn_trkmod, trkPhiMod, EOverP, evtweight);
            } // E/p requirement
            
            _histos.Fill1D("hWcandLumi_CC", luminosity, evtweight);
	    _histos.Fill2D("hWcandScalarEt_V_Lumi2D_CC",luminosity, scalarEt_All, evtweight);
	    _histos.FillProfile("hWcandScalarEt_V_Lumi_CC",luminosity, scalarEt_All, evtweight );
	    _histos.Fill1D("hWcandScalarEt_CC", scalarEt_All, evtweight);
	    _histos.Fill1D("hWcandScalarEtZB_CC", scalarEt_ZB, evtweight);
	    _histos.Fill1D("hWcandScalarEtZBNoScale_CC", scalarEt_ZB_NoScale, evtweight);
	    _histos.Fill1D("hWcandWPt_CC", WPt, evtweight);
	    //
	    _histos.Fill1D("hWcandTrueWPt_CC", recoil_gen.Recoil(), evtweight);
            _histos.Fill1D("hWcandResolWPt_CC", recoil_gen.Recoil()-WPt, evtweight);
	    //
	    _histos.Fill1D("hWcandMt_CC", WMt, evtweight);
	    _histos.Fill1D("hWcandElecPt_CC", WElecPt, evtweight);
	    _histos.Fill1D("hWcandElecTrkPt_CC", TrkPt, evtweight);
	    _histos.Fill1D("hWcandElecPx_CC", WElecPt*cos(WElecPhiTrkAtDCA), evtweight);
	    _histos.Fill1D("hWcandElecPy_CC", WElecPt*sin(WElecPhiTrkAtDCA), evtweight);

	    _histos.Fill1D("hWcandMet_CC", WMet, evtweight);
	    _histos.Fill1D("hWcandUpara_CC", WUpara, evtweight);
	    _histos.Fill1D("hWcandUperp_CC", WUperp, evtweight);
            _histos.Fill1D(string("hWcandUpara_ElecPtBin_")+pTebin_sn, WUpara, evtweight);

	    _histos.Fill1D("hWcandInConeFSR_Number_CC", FSRInConeNum, evtweight);
	    _histos.Fill2D("hWcandInConeFSR_Number_V_MergedTrueEnergy", FSRInConeNum, pmcsevent.GetRawEMObjsWFSR()[0].pE());
            // some Truth plots
            {
              _histos.Fill1D("hMCW_Pt_CC", TrueWPt, evtweight);
              _histos.Fill1D("hMCW_Phi_CC", TrueWPhi, evtweight);
              _histos.Fill1D("hMCW_Mass_CC", TrueWMass, evtweight);
              int TrueWPtBin = wz_utils::pTee_Eta_Bin(TrueWPt);
              int WPtBin = wz_utils::pTee_Eta_Bin(WPt);
              char TrueWPtBin_sn[10]; sprintf(TrueWPtBin_sn, "%d", TrueWPtBin);
              char WPtBin_sn[10]; sprintf(WPtBin_sn, "%d", WPtBin);
              if(TrueWPtBin>=0) _histos.Fill1D(TString("hRecoilW_Pt_CC_bin_")+TString(TrueWPtBin_sn), WPt, evtweight);
              if(WPtBin>=0) _histos.Fill1D(TString("hMCW_Pt_CC_bin_")+TString(WPtBin_sn), TrueWPt, evtweight);
            }

	    //
	    int theJ=-1;
            for (int jj=0; jj<emobjs_gen.size(); jj++) {
              if (theJ<0 && abs(emobjs_gen[jj].ppid())==11) theJ=jj;
            }
            TVector2 jrec(recoil_gen.Recoilx(),recoil_gen.Recoily());
            TVector2 jelec(emobjs_gen[theJ].ppx(),emobjs_gen[theJ].ppy());
            double WTrueUpara=jrec*jelec.Unit();
            _histos.Fill1D("hWcandTrueUpara_CC", WTrueUpara, evtweight);
            _histos.Fill1D("hWcandResolUpara_CC", WTrueUpara-WUpara, evtweight);
            TVector2 jperpdir = jelec.Rotate(TMath::Pi()/2);
            double WTrueUperp=jrec*jperpdir.Unit();
            _histos.Fill1D("hWcandTrueUperp_CC", WTrueUperp, evtweight);
            _histos.Fill1D("hWcandResolUperp_CC", WTrueUperp-WUperp, evtweight);
	    //
	    _histos.Fill1D("hWcandWPhi_CC", WPhi, evtweight);
	    _histos.Fill1D("hWcandMetx_CC", met.metx(), evtweight);
	    _histos.Fill1D("hWcandMety_CC", met.mety(), evtweight);
	    
	    _histos.Fill1D("hWcandElecEta_CC", WElecEta, evtweight); 
	    _histos.Fill1D("hWcandElecTrkPhiModEM3_CC", trkPhiMod, evtweight);
	    _histos.Fill1D("hWcandElecTrkPtOvE_CC",TrkPt / WElecPt, evtweight);
	    _histos.Fill1D("hWcandElecDetEta_CC", WElecDetEta, evtweight); 
	    //jenny, may 29 2012
	    //changed phi from WElecPhiTrkAtEM3 to WElecPhiTrkAtDCA to match full MC/data def in cafe, also def used in electron phi eff smearing code 
	    _histos.Fill1D("hWcandElecPhi_CC", WElecPhiTrkAtDCA, evtweight); 
	    _histos.Fill1D("hWcandElecDetPhi_CC", WElecDetPhiCALO, evtweight); 
	    _histos.Fill1D("hWcandElecPhiTrkAtDCA_CC", WElecPhiTrkAtDCA , evtweight);
	    _histos.Fill1D("hWcandElecPhiTrkAtEM3_CC", WElecPhiTrkAtEM3 , evtweight);
	    _histos.Fill1D("hWcandElecDetPhiCALO_CC", WElecDetPhiCALO   , evtweight);
	    _histos.Fill1D("hWcandMetPhi_CC", WMetPhi, evtweight); 
	    _histos.Fill1D("hWcandVtx_CC", vtx_gen.vtxz(), evtweight);
	    _histos.Fill1D("hWcandRecoilPt_CC", WRecoilPt, evtweight);
            _histos.Fill1D("hWcandRecoilPx_CC", WRecoilPx, evtweight);
            _histos.Fill1D("hWcandRecoilPy_CC", WRecoilPy, evtweight);
            _histos.Fill1D("hWcandRecoilPhi_CC", WRecoilPhi, evtweight);
            _histos.Fill1D("hWcandElecMETDeltaPhi_CC", wcand.DeltaPhi_EM_MET(), evtweight);
            _histos.Fill1D("hWcandElecRecoilDeltaPhi_CC", wcand.DeltaPhi_EM_Recoil(), evtweight);
            _histos.Fill1D("hWcandMETRecoilDeltaPhi_CC", fabs(met_vect.DeltaPhi(wcand.GetRecoilVec())), evtweight);

	    _histos.Fill1D("hWcandEOverP_CC", EOverP, evtweight);

	    // fill electron pT spectrum for different eta regions (only for CC events)
	    int FineEtaRegion_CC = emobj.FineEtaRegion_CC(WElecEta, 1.05, true, _ApplyTrkPhiModCut);
	    char sn_FineEtaRegion_CC[10];   sprintf(sn_FineEtaRegion_CC, "%d", FineEtaRegion_CC);
	    
	    _histos.Fill1D(TString("hWcandElecPt_Spatial_Match_EtaBin_CC_")+sn_FineEtaRegion_CC, WElecPt, evtweight);
	    _histos.Fill1D(TString("hWcandMCElecPt_Spatial_Match_EtaBin_CC_")+sn_FineEtaRegion_CC, raw_emobjs_gen[0].ppt(), evtweight);
	    if(kinem::delta_R(WElecPhiTrkAtDCA, WElecEta, raw_emobjs_gen[0].phi(), raw_emobjs_gen[0].eta())<0.3) { // find smear-truth matched electron
	      double pt_diff = WElecPt - raw_emobjs_gen[0].ppt();
	      _histos.Fill1D(TString("hWcandMCElecPtDiff_Spatial_Match_EtaBin_CC_")+sn_FineEtaRegion_CC, pt_diff, evtweight);
	    }

	    if(WMt>100.) {
	      _histos.Fill1D(TString("hWcandElecPt_Spatial_Match_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, WElecPt, evtweight);
	      _histos.Fill1D(TString("hWcandMCElecPt_Spatial_Match_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, raw_emobjs_gen[0].ppt(), evtweight);

	      if(kinem::delta_R(WElecEta, WElecPhiTrkAtDCA, raw_emobjs_gen[0].eta(), raw_emobjs_gen[0].phi())<0.3) { // find smear-truth matched electron
		double pt_diff = WElecPt - raw_emobjs_gen[0].ppt();
		_histos.Fill1D(TString("hWcandMCElecPtDiff_Spatial_Match_EtaBin_CC_Tail_")+sn_FineEtaRegion_CC, pt_diff, evtweight);
	      }
	    }
	    
	    // for W width measurement
            if(WMt > 100. && WMt < 200.) {
	      _histos.Fill1D("hWcandMt_CC_Tail_Width", WMt, evtweight);
	      _histos.Fill1D("hWcandElecPt_CC_Tail_Width", WElecPt, evtweight);
	      _histos.Fill1D("hWcandMet_CC_Tail_Width", WMet, evtweight);
	      _histos.Fill1D("hWcandWPt_CC_Tail_Width", WPt, evtweight);
            }

	    // check distributions for different recoil pT bins
	    int bin = wz_utils::pTee_Eta_Bin(WRecoilPt);
            char recoilPt_bin_sn[10]; sprintf(recoilPt_bin_sn, "%d", bin);
	    
            if(bin >= 0) {
              _histos.Fill1D(string("hWcandMt_RecoilBin_")+recoilPt_bin_sn, WMt, evtweight);
              _histos.Fill1D(string("hWcandElecPt_RecoilBin_")+recoilPt_bin_sn, WElecPt, evtweight);
              _histos.Fill1D(string("hWcandMet_RecoilBin_")+recoilPt_bin_sn, WMet, evtweight);
              _histos.Fill1D(TString("hWcandElecMetDeltaPhi_RecoilBin_")+recoilPt_bin_sn, wcand.DeltaPhi_EM_MET(), evtweight);
              _histos.Fill1D(TString("hWcandElecRecoilDeltaPhi_RecoilBin_")+recoilPt_bin_sn, wcand.DeltaPhi_EM_Recoil(), evtweight);
              _histos.Fill1D(TString("hWcandMetRecoilDeltaPhi_RecoilBin_")+recoilPt_bin_sn, fabs(met_vect.DeltaPhi(wcand.GetRecoilVec())), evtweight);
              _histos.Fill1D(string("hWcandRecoilPhi_RecoilBin_")+recoilPt_bin_sn, WRecoilPhi, evtweight);
              _histos.Fill1D(string("hWcandUPara_RecoilBin_")+recoilPt_bin_sn, WUpara, evtweight);
              _histos.Fill1D(string("hWcandUPerp_RecoilBin_")+recoilPt_bin_sn, WUperp, evtweight);
              _histos.Fill1D(string("hWcandVtx_RecoilBin_")+recoilPt_bin_sn, vtx_gen.vtxz(), evtweight);
              _histos.Fill1D(string("hWcandPhi_RecoilBin_")+recoilPt_bin_sn, WPhi, evtweight);
              _histos.Fill1D(string("hWcandInstLumi_RecoilBin_")+recoilPt_bin_sn, luminosity, evtweight);
              _histos.Fill1D(string("hWcandScalarEt_RecoilBin_")+recoilPt_bin_sn, scalarEt_All, evtweight);
            }
	    
	    if(wcand.UPara()<0.) {
	      _histos.Fill1D("hWcandElecPtUpara1_CC", WElecPt, evtweight);
	      _histos.Fill1D("hWcandElecTrkPtUpara1_CC", TrkPt, evtweight);
	      _histos.Fill1D("hWcandMetUpara1_CC", WMet, evtweight);
	      _histos.Fill1D("hWcandMtUpara1_CC", WMt, evtweight);
	      _histos.Fill1D("hWcandWPtUpara1_CC", WPt, evtweight);
	    } else {
	      _histos.Fill1D("hWcandElecPtUpara2_CC", WElecPt, evtweight);
	      _histos.Fill1D("hWcandElecTrkPtUpara2_CC", TrkPt, evtweight);
	      _histos.Fill1D("hWcandMetUpara2_CC", WMet, evtweight);
	      _histos.Fill1D("hWcandMtUpara2_CC", WMt, evtweight);
	      _histos.Fill1D("hWcandWPtUpara2_CC", WPt, evtweight);
	    }
	    
	    // fill upara vs electron pT, MET, transverse mass and W pT
	    _histos.Fill2D("hWcandElecPt_V_Upara_CC", WElecPt, WUpara, evtweight);
	    _histos.FillProfile("hWcandMtUpara_CC", WMt, WUpara, evtweight);
	    _histos.FillProfile("hWcandElecPtUpara_CC", WElecPt, WUpara, evtweight);
	    _histos.FillProfile("hWcandMetUpara_CC", WMet, WUpara, evtweight);
	    _histos.FillProfile("hWcandWPtUpara_CC", WPt, WUpara, evtweight);
	    
	    // fill transverse mass for different Ut regions
	    if(Ut<5.)
              _histos.Fill1D("hWcandMt_UtBin0_CC", WMt, evtweight);
            else if(Ut<10.)
              _histos.Fill1D("hWcandMt_UtBin1_CC", WMt, evtweight);
            else if(Ut<15)
              _histos.Fill1D("hWcandMt_UtBin2_CC", WMt, evtweight);

	    // optional ASCII printouts
	    if (_makeASCIIfile_LumiEff) {
	      cout<<"Lumi "<<_recoilsmear->GetEvtIDrun()<<" "<<_recoilsmear->GetEvtIDevent()<<" "
		  <<luminosity<<" "<<scalarEt_All<<" "<<_recoilsmear->scalarEt_MB()<<" "<<_recoilsmear->scalarEt_ZB()<<" "
		  <<_recoilsmear->scalarEt_hard()<<" "<<WElecPt<<" "<<WElecDetEta<<" "<<WElecEta<<" "
		  <<WUpara<<" "<<WPt<<endl;
	    }
	    //
	    if (_makeASCIIfile_Eresponse) {
              PMCSEMObj h_emobj_gen, h_emobj_gen_raw, h_emobj_gen_raw_wfsr;
              for (int hh=0; hh<emobjs_gen.size(); hh++){
                if (emobjs_gen[hh].getIndex() == emobj.getIndex()){
                  h_emobj_gen = emobjs_gen[hh];
                  break;
                 }
              }
              double dRmin = 1000.;
              for (int hh=0; hh<raw_emobjs_gen.size(); hh++){
                double dR = raw_emobjs_gen.at(hh).GetLorentzVect().DeltaR(h_emobj_gen.GetLorentzVect());
                if (dR< dRmin){
                  dRmin = dR;
                  h_emobj_gen_raw = raw_emobjs_gen.at(hh);
                }
              }
              dRmin = 1000;
              for (int hh=0; hh<raw_emobjs_gen_wfsr.size(); hh++){
                double dR = raw_emobjs_gen_wfsr.at(hh).GetLorentzVect().DeltaR(h_emobj_gen.GetLorentzVect());
                if (dR< dRmin){
                  dRmin = dR;
                  h_emobj_gen_raw_wfsr = raw_emobjs_gen_wfsr.at(hh) ;
                }
              }
              cout<<"Eresponse "<<_recoilsmear->GetEvtIDrun()<<" "<<_recoilsmear->GetEvtIDevent()<<" "
                  <<luminosity<<" "<<scalarEt_All<<" "
                  <<WElecPt<<" "<<emobj.pE()<<" "<<WElecDetEta<<" "<<WElecEta<<" "
                  <<h_emobj_gen_raw.pE()<<" "<<h_emobj_gen_raw.ppx()<<" "<<h_emobj_gen_raw.ppy()<< " " << h_emobj_gen_raw.ppz() << " "<<recoil_gen.Recoil()<<" "
                  <<WUpara<<" "<<WPt<< " " << recoil_gen.Recoilx() << " " << recoil_gen.Recoily() << " " << WUperp << " "
                  <<WRecoilPx<< " " << WRecoilPy << " "
                  <<emobj.ppx() << " " << emobj.ppy() << " " << emobj.ppz() << " " << emobj.trkphiem3() << " " << emobj.ppid() << " " << evtweight << " "
                  <<h_emobj_gen.pE()<<" "<<h_emobj_gen.ppx()<<" "<<h_emobj_gen.ppy()<<" "<<h_emobj_gen.ppz()<<" "
                  <<h_emobj_gen_raw_wfsr.pE()<<" "<<h_emobj_gen_raw_wfsr.ppx()<<" "<<h_emobj_gen_raw_wfsr.ppy()<<" "<<h_emobj_gen_raw_wfsr.ppz()<<" "
                  << _recoilsmear->GetMet_MB().Px() << " "<< _recoilsmear->GetMet_MB().Py() << " " << _recoilsmear->scalarEt_MB() << " "
                  << _recoilsmear->GetMet_ZB().Px() << " "<< _recoilsmear->GetMet_ZB().Py() << " " << _recoilsmear->scalarEt_ZB() << " "
                  << emobj.UParaCorr() << " " << emobj.getEnergyDiffElecWithWithoutZBOverlay() << " " << emobj.EnergyLeakage() << " "
                  << endl;
	    }
 
	    if(_doSingVariableStudy) {
	      _histos.Fill1D("hWcandSingVariable_CC", singVariable, evtweight);
	      
	      // if(_doSVnolongitudinalstudy) _histos.Fill1D("hWcandSingVariable_LongUnSmeared_CC", singVariable_LongUnSmeared, evtweight);
	      if(_doSVgeneratorstudy) {
		_histos.Fill1D("hWcandSingVariable_Gen_CC", singVariable_gen, evtweight);
		//other variables for comparison
		_histos.Fill1D(string("hWcandMt_Gen_CC"), wcand_gen.TMass(), evtweight);
		_histos.Fill1D(string("hWcandElecPt_Gen_CC"), emobjs_gen[ielec].ppt(), evtweight);
		_histos.Fill1D(string("hWcandMet_Gen_CC"), met_gen.met(), evtweight);
	      }
	    }
 
	    if(_doPdfReweight) {
	      
	      char sn[10];
	      double massweight; 
	      
	      for(int i=0; i<45; i++) {
		massweight = evtweight * pmcsevent.pdfreweights[i];   //also include the whole event weight		  
		sprintf(sn,"%d", i); 
		_histos.Fill1D(string("hWcandMt_CC_PDF_")+sn, WMt, massweight);
		_histos.Fill1D(string("hWcandElecPt_CC_PDF_")+sn, WElecPt, massweight);
		_histos.Fill1D(string("hWcandMet_CC_PDF_")+sn, WMet, massweight);
		
		if(_doSingVariableStudy){
		  _histos.Fill1D(string("hWcandSingVariable_PDF_CC_")+sn, singVariable, massweight);
		  if(_doSVgeneratorstudy) _histos.Fill1D(string("hWcandSingVariable_Gen_PDF_CC_")+sn, singVariable_gen, massweight);
		  // if(_doSVnolongitudinalstudy) _histos.Fill1D(TString::Format("hWcandSingVariable_LongUnSmeared_PDF_CC_")+sn, singVariable_LongUnSmeared, massweight);
		}		
	      }
	    }//w mass reweight

	    //	  
	    // fill weighted histogram for electron pT, MET and transverse mass distributions
	    // for W mass analysis
	    //
	    if(_wmass_reweight) {
	      // Get Breit-Wigner Weight
	      vector<double> ReweightFactorMass = BreitWignerReweightMass(pmcsevent);
	      
	      char sn[10];
	      double massweight = evtweight; 
	      
	      for(int i=0; i<ReweightFactorMass.size(); i++) {
		massweight = evtweight * ReweightFactorMass[i];   //also include the whole event weight		  
		sprintf(sn,"%d", i); 
		//note: some generator level histograms of these variables are in _doSingVariableStudy
		_histos.Fill1D(string("hWcandMt_CC_")+sn, WMt, massweight);
		_histos.Fill1D(string("hWcandElecPt_CC_")+sn, WElecPt, massweight);
		_histos.Fill1D(string("hWcandMet_CC_")+sn, WMet, massweight);
		_histos.Fill1D(string("hWcandWPt_CC_")+sn, WPt, massweight);
		//
		if(_doSingVariableStudy){
		  _histos.Fill1D(string("hWcandSingVariable_CC_")+sn, singVariable, massweight);
		  if(_doSVgeneratorstudy) _histos.Fill1D(string("hWcandSingVariable_Gen_CC_")+sn, singVariable_gen, massweight);
		  // if(_doSVnolongitudinalstudy) _histos.Fill1D(string("hWcandSingVariable_LongUnSmeared_CC_")+sn, singVariable_LongUnSmeared, massweight);
		}
		_histos.FillProfile(string("hWcandMtUpara_CC_")+sn, WMt, WUpara, massweight);
		_histos.FillProfile(string("hWcandElecPtUpara_CC_")+sn, WElecPt, WUpara, massweight);
		_histos.FillProfile(string("hWcandMetUpara_CC_")+sn, WMet, WUpara, massweight);
		//
		if(wcand.UPara()<0.) {
		  _histos.Fill1D(string("hWcandElecPtUpara1_CC_")+sn, WElecPt, massweight);
		  _histos.Fill1D(string("hWcandMetUpara1_CC_")+sn, WMet, massweight);
		  _histos.Fill1D(string("hWcandMtUpara1_CC_")+sn, WMt, massweight);
		} else {
		  _histos.Fill1D(string("hWcandElecPtUpara2_CC_")+sn, WElecPt, massweight);
		  _histos.Fill1D(string("hWcandMetUpara2_CC_")+sn, WMet, massweight);
		  _histos.Fill1D(string("hWcandMtUpara2_CC_")+sn, WMt, massweight);
		}
		//
		if(Ut<5.)
		  _histos.Fill1D(string("hWcandMt_UtBin0_CC_")+sn, WMt, massweight);
		else if(Ut<10.)
		  _histos.Fill1D(string("hWcandMt_UtBin1_CC_")+sn, WMt, massweight);
		else if(Ut<15)
		  _histos.Fill1D(string("hWcandMt_UtBin2_CC_")+sn, WMt, massweight);
	      }
	    }//w mass reweight
	    
	    //	  
	    // fill weighted histogram for electron pT, MET and transverse mass distributions
	    // for W width analysis
	    //
	    if(_wwidth_reweight) {
	      // Get Breit-Wigner Weight
	      vector<double> ReweightFactorWidth = BreitWignerReweightWidth(pmcsevent);
	      
	      char sn[10];
	      double widthweight = evtweight; 
	      
	      for(int i=0; i<ReweightFactorWidth.size(); i++) {
		widthweight = evtweight * ReweightFactorWidth[i];   //also include the whole event weight		  
		sprintf(sn,"%d", i); 
		_histos.Fill1D(string("hWcandMt_CC_Width_")+sn, WMt, widthweight);
		_histos.Fill1D(string("hWcandElecPt_CC_Width_")+sn, WElecPt, widthweight);
		_histos.Fill1D(string("hWcandMet_CC_Width_")+sn, WMet, widthweight);
		_histos.Fill1D(string("hWcandWPt_CC_Width_")+sn, WPt, widthweight);
	      }
	    }//w width reweight
	    
	  } // CC W candidates
	  
	    // W candidates with electrons in EC region
	  if(wcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _ApplyTrkPhiModCut)==1) {
	    _ngoodWCandEC++;
	    _ngoodWCand++;


	  } //EC W candidates
	  if (_makeROOTfile_for_WFIT && !_makegenROOTfile_for_WFIT) {
	    fillWFitFile(pmcsevent.GetEvtWeight(),pmcsevent.GetWZBoson().Mass(), wcand, met_gen, emobjs_gen, pmcsevent.GetWZBoson().ppz(),Smeared_Nu,Trigger_Version, recoilX_orig,  recoilY_orig, luminosity, vtx_gen.vtxz() , pmcsevent.pdfreweights, pmcsevent , scalarEt_All, emobjs_smear);
	    Wfittree->Fill();
	  }//fill optional W fit file
	  
	}//pass all efficiencies
      }//W pT cut      
    }//electron pT>_CutEPT and MET<_CutMET
  }//at least one EM Objects
  
  // Increase the counter for the number of events processed
  _ntotal++;
} 

void WAnalysis::fillWFitFile(double event_weight, double gen_mass, PMCSWCand &wcand, PMCSMet &met_gen, vector<PMCSEMObj> &emobjs_gen, double gen_boson_pz, PMCSEMObj &nu, double TrigVer, double recoilX_orig, double recoilY_orig, double luminosity, double vtxZ, double weights[], PMCSEvent& pmcsevent , double SET, std::vector<PMCSEMObj>& emobjs_smear) {
  wfit_data.mass_W_gen = gen_mass;
  wfit_data.tranmass_W_smear = wcand.TMass();

  wfit_data.elec_E = wcand.GetElec().pE();
  wfit_data.elec_px = wcand.GetElec().ppx();
  wfit_data.elec_py = wcand.GetElec().ppy();
  wfit_data.elec_pz = wcand.GetElec().ppz();
  wfit_data.elec_id = wcand.GetElec().ppid();
  wfit_data.elec_deteta = wcand.GetElec().deteta();
  wfit_data.elec_peta = wcand.GetElec().peta();
  wfit_data.elec_upara = wcand.GetElec().UParaCorr();
  wfit_data.elec_leakage = wcand.GetElec().EnergyLeakage();
  wfit_data.elec_ZBdiff = wcand.GetElec().getEnergyDiffElecWithWithoutZBOverlay();
  if (!(TMath::Abs(wfit_data.elec_id) == 11.)){
    std::cout << "fillWFitFile elec_id : " << wfit_data.elec_id << std::endl;
  }
  
  wfit_data.met_x = wcand.GetMet().metx();
  wfit_data.met_y = wcand.GetMet().mety();
  wfit_data.gen_elec_E = 0.;

  wfit_data.gen_W_E = pmcsevent.GetWZBoson().pE();
  wfit_data.gen_W_px = pmcsevent.GetWZBoson().ppx();
  wfit_data.gen_W_py = pmcsevent.GetWZBoson().ppy();
  wfit_data.gen_W_pz = pmcsevent.GetWZBoson().ppz();

  for(int inu=0;inu < emobjs_gen.size(); inu++){
    PMCSEMObj test_em = (emobjs_gen.at(inu));
    if ( test_em.getIndex() == wcand.GetElec().getIndex() ){
      if (wfit_data.gen_elec_E > 0.){
	std::cout << "mismatch of generator electron" << std::endl;
      }
      wfit_data.gen_elec_E = test_em.pE();
      wfit_data.gen_elec_px = test_em.ppx();
      wfit_data.gen_elec_py = test_em.ppy();
      wfit_data.gen_elec_pz = test_em.ppz();
      if (inu > 0){
	//std::cout << test_em.ppid() << "   " << inu << std::endl;
      }
      
    }
    
    if ((test_em.ppid() == 12.)){
      wfit_data.gen_nu_x = test_em.ppx();
      wfit_data.gen_nu_y = test_em.ppy();
      wfit_data.gen_nu_z = test_em.ppz();
    }
    
  }
  
  wfit_data.nu_px = nu.ppx();
  wfit_data.nu_py = nu.ppy();
  wfit_data.nu_pz = nu.ppz();
  wfit_data.nu_E = nu.pE();
  wfit_data.nu_deteta = nu.deteta();
  wfit_data.nu_upara = nu.UParaCorr();
  wfit_data.nu_leakage = nu.EnergyLeakage();
  wfit_data.nu_peta = nu.peta();
  wfit_data.nu_ZBdiff = nu.getEnergyDiffElecWithWithoutZBOverlay();

  wfit_data.Trig_Ver = TrigVer;
  wfit_data.RecoilX = wcand.GetRecoilVec().Px();
  wfit_data.RecoilY = wcand.GetRecoilVec().Py();
  wfit_data.RecoilX_gen = recoilX_orig;
  wfit_data.RecoilY_gen = recoilY_orig;

  wfit_data.event_weight = event_weight;
  wfit_data.lumi = luminosity;
  PMCSEMObj WCand_elec = wcand.GetElec();
  wfit_data.mass_W_smear = PMCSZCand(WCand_elec,nu).mass();
  wfit_data.vtxZ = vtxZ;

  wfit_data.SET = SET; // RCLSA

  wfit_data.OutConePh_px = 0.;
  wfit_data.OutConePh_py = 0.;
  wfit_data.OutConePh_pz = 0.;
  wfit_data.OutConePh_E = 0.;
  for(int i=0; i<emobjs_smear.size(); i++) {
    if (i > 0){
      if (!_WsimuFSRcracks) {
	wfit_data.OutConePh_px += emobjs_smear[i].ppx();
	wfit_data.OutConePh_py += emobjs_smear[i].ppy();
	wfit_data.OutConePh_pz += emobjs_smear[i].ppz();
	wfit_data.OutConePh_E += emobjs_smear[i].pE();
      } else {
	float deteta=emobjs_smear[i].deteta();
	float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>(_WsimuFSRcracksWidth))&&(phimod<(1-_WsimuFSRcracksWidth)))) {
	  wfit_data.OutConePh_px += emobjs_smear[i].ppx();
	  wfit_data.OutConePh_py += emobjs_smear[i].ppy();
	  wfit_data.OutConePh_pz += emobjs_smear[i].ppz();
	  wfit_data.OutConePh_E += emobjs_smear[i].pE();
	}
      }
    }
  }

  wfit_data.nInConePh = ((int) wcand.GetElec().FSRnInCone());
  wfit_data.xInConePh = ((double) wcand.GetElec().FSRxInCone());

  for( int i = 0 ; i < 45 ; i++ )
     wfit_data.pdfweights[i] = weights[i];

  vector<double> massweight_vec;
  massweight_vec = BreitWignerReweightMass(pmcsevent);
  for(int i=0; i<massweight_vec.size(); i++) {
    wfit_data.massweights[i] = massweight_vec[i];
  }
}

//destructor
WAnalysis::~WAnalysis () {
  if(_emsmear!=NULL) delete _emsmear;
  if(_recoilsmear!=NULL) delete _recoilsmear;
  if(_efficiencysmear!=NULL) delete _efficiencysmear;
  if(_SETefficiencysmear!=NULL) delete _SETefficiencysmear;
}

void WAnalysis::jobSummary() {

  cout << "WAnalysis number of events processed = " << _ntotal << endl ; 
  cout << "Good W Candidates (CC, EC, All): (" << _ngoodWCandCC <<", "<< _ngoodWCandEC
       << ", " << _ngoodWCand << ")" << endl;


  if(_MakeEleakTable){
    double LeakMean=0;
    std::fstream* LeakTableFile = new std::fstream("LeakTable.txt",std::ios::out);
    
    for(int i=0; i<_NleakBins; i++){
      
      if(_LeakCount[i]<200) cout<<"Low LeakStats in bin "<<i<<" Num evts is: "<<_LeakCount[i]<<endl;
      
      if(_LeakCount[i]!=0) LeakMean = _LeakSum[i]/_LeakCount[i];
      (*LeakTableFile)<< i <<" "<< LeakMean<<endl;
    }
    
    LeakTableFile->close();
  }
  

  BlindingManagerPMCS bm;
  bm.SetInfo(_wmass_reweight,
	     _wmass_default, _wmass_step, 100,
	     _wwidth_reweight,
	     _wwidth_default, _wwidth_step, 100);
  vector<TObject*> bmhists;
  bmhists.push_back(bm.GetVerdict());
  _histos.save(_wenfilename,false,false,&bmhists);

  if (_makeROOTfile_for_WFIT || _makegenROOTfile_for_WFIT) {
    cout << "Writing W fit file Wfittree.root" << endl;
    Wfitfile->Write();
  }
}

