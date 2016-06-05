
#include "EMSmear.hpp"
#include "PHistoTools.hpp"
#include "histograms.hpp"
#include "AnglesUtil.hpp"
#include "WZ_Utils.hpp"
#include "PCalTools.hpp"
#include "PMCSTH1.hpp"
#include "../geant_RunIIb/pmcsZBFunction.C"
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

// constructor and read smearing parameters
EMSmear::EMSmear(TString parameter_filename,hist_files &histos) {

  PParameterReader parm(parameter_filename.Data());

  cout<<"Start EMSmear initialization"<<endl;

  _histos = &histos;

  _run3bool = parm.GetBool("Run3");
  _run4bool = parm.GetBool("Run4");
  _middlerunnumber = parm.GetInt("MiddleRunNumber");

  _makeCheckSmearingPlots =  parm.GetBool("makeCheckSmearingPlots");

  if (_makeCheckSmearingPlots) {
    _histos->add(EMSMEAR_Hist,"","check_smearing");
    _histos->add(EMSMEAR_Hist_2D,"","check_smearing");
    _histos->add(EMSMEAR_Profile,"","check_zbdiff");
  }
  _histos->clone("ZBDiffvUparaCorr",11); 

  // smearing parameters for CC region  
  _etares_phy_CC = parm.GetFloat("EtaResolution_Phys_CC", 0.001);
  _phires_phy_CC = parm.GetFloat("PhiResolution_Phys_CC", 0.0001);
  _etares_det_CC = parm.GetFloat("EtaResolution_Det_CC", 0.007);
  _phires_det_CC = parm.GetFloat("EtaResolution_Det_CC", 0.007);

  // smear Phys Eta and Phys Phi with Hengne's histograms
  _SmearEtaPhiHengne = parm.GetBool("SmearEtaPhiHengne", false);
  _ApplyPhiModErespCorrHengne = parm.GetBool("ApplyPhiModErespCorrHengne", false);
  _ApplyPhiModEffHengne = parm.GetBool("ApplyPhiModEffHengne", false);
  if (_SmearEtaPhiHengne){
    TFile* fetaphi = new TFile(parm.GetChar("HistFileSmearEtaPhiHengne"));
    _hPhyPhiResoPos = (TH1D*)fetaphi->Get("hPhyPhiResoPos");
    _hPhyPhiResoEle = (TH1D*)fetaphi->Get("hPhyPhiResoEle");
    _hEmfIsoHMxEffVsPhiMod = (TH1D*)fetaphi->Get("hEmfIsoHMxEffVsPhiMod");
    _hTkMatchEffVsPhiModVsEtrue = (TH2D*)fetaphi->Get("hTkMatchEffVsPhiModVsEtrue");
    _hErespPhiModEtrue = (TH2D*)fetaphi->Get("hErespPhiModEtrue");
  }

  // if we also want to apply electron energy scale on the delta E correction of electron window
  _ApplyScaleOnDeltaE = parm.GetBool("ApplyScaleOnDeltaE", false);  

  // resolution smearing function 
  _ResolutionSmear_Option = (int)(parm.GetFloat("ResolutionSmear_Option", 2));
  
  // smearing parameters for CC region
  _scale_CC = parm.GetFloat("Scale_CC", 1.);
  _offset_CC = parm.GetFloat("Offset_CC", 0.0);
  _sampling_CC = parm.GetFloat("Sampling_CC", 0.15);
  _constant_CC = parm.GetFloat("Constant_CC", 0.04);
  _noise_CC = parm.GetFloat("Noise_CC", 0.29);
  _Energy_Nonlinearity_CC = parm.GetFloat("Energy_Nonlinearity_CC", 0.);
  _ZElec_AvePt_CC = parm.GetFloat("ZElec_AvePt_CC", 43.);

  // second copy of _scale_CC and _offset_CC
  _scale_CC0 = _scale_CC;
  _offset_CC0 = _offset_CC;

  // phi hack
  _doPhiHack = parm.GetBool("doPhiHack", kFALSE);
  if (_doPhiHack) {
    _PhiHack_bins  = parm.GetVDouble("PhiHack_bins");
    _PhiHack_corr = parm.GetVDouble("PhiHack_corr");
    assert(_PhiHack_bins.size()>0);
    assert(_PhiHack_corr.size()==(_PhiHack_bins.size()+1));
  }

  // lumi-dependent scale and offset in the CC region
  _doCCscale_lumidep = parm.GetInt("doCCscale_lumidep", 0);
  // upara-dependent scale and offset in the CC region
  _doCCscale_uparadep = parm.GetBool("doCCscale_uparadep", kFALSE);
  // read parameters for lumi- and upara- dependent scale and offset in the CC region
  if (_doCCscale_lumidep) {
    if (_doCCscale_lumidep==1 || _doCCscale_lumidep==3) {
      _CCscale_lumidep_lumibins = parm.GetVDouble("CCscale_lumidep_lumibins");

      //if( _doCCscale_lumidep==3){
      _CCscale_lumidep_scale_run3 = parm.GetVDouble("CCscale_lumidep_scale_run3");
      _CCscale_lumidep_offset_run3 = parm.GetVDouble("CCscale_lumidep_offset_run3");
      _CCscale_lumidep_scale_run4 = parm.GetVDouble("CCscale_lumidep_scale_run4");
      _CCscale_lumidep_offset_run4 = parm.GetVDouble("CCscale_lumidep_offset_run4");
      
      assert(_CCscale_lumidep_lumibins.size()>0);
      assert(_CCscale_lumidep_scale_run3.size()==(_CCscale_lumidep_lumibins.size()+1));
      assert(_CCscale_lumidep_offset_run3.size()==(_CCscale_lumidep_lumibins.size()+1));
      assert(_CCscale_lumidep_scale_run4.size()==(_CCscale_lumidep_lumibins.size()+1));
      assert(_CCscale_lumidep_offset_run4.size()==(_CCscale_lumidep_lumibins.size()+1));
      // }else{
      //	_CCscale_lumidep_lumibins = parm.GetVDouble("CCscale_lumidep_lumibins");
      //	_CCscale_lumidep_scale = parm.GetVDouble("CCscale_lumidep_scale");
      //	_CCscale_lumidep_offset = parm.GetVDouble("CCscale_lumidep_offset");
      //	assert(_CCscale_lumidep_lumibins.size()>0);
      //	assert(_CCscale_lumidep_scale.size()==(_CCscale_lumidep_lumibins.size()+1));
      //	assert(_CCscale_lumidep_offset.size()==(_CCscale_lumidep_lumibins.size()+1));
      // }
      if (_doCCscale_uparadep){
	_CCscaleUT30_lumidep_scale = parm.GetVDouble("CCscaleUT30_lumidep_scale");
	_CCscaleUT30_lumidep_offset = parm.GetVDouble("CCscaleUT30_lumidep_offset");
	assert(_CCscaleUT30_lumidep_scale.size()==(_CCscale_lumidep_lumibins.size()+1));
	assert(_CCscaleUT30_lumidep_offset.size()==(_CCscale_lumidep_lumibins.size()+1));
      }
    }
    if (_doCCscale_lumidep==2 || _doCCscale_lumidep==3) {
      _CCscale_lumidepFP_p0_q0 = parm.GetDouble("CCscale_lumidepFP_p0_q0", 0);
      _CCscale_lumidepFP_p0_q1 = parm.GetDouble("CCscale_lumidepFP_p0_q1", 0);
      _CCscale_lumidepFP_p2_q0 = parm.GetDouble("CCscale_lumidepFP_p2_q0", 0);
      _CCscale_lumidepFP_p2_q1 = parm.GetDouble("CCscale_lumidepFP_p2_q1", 0);
      _CCscale_lumidepFP_typical = parm.GetDouble("CCscale_lumidepFP_typical", 0);
      //
      _CCscale_DetEtaAdjust = parm.GetBool("CCscale_DetEtaAdjust", kFALSE);
      if (_CCscale_DetEtaAdjust) {
	if (_run3bool) _CCscale_DetEtaAdjust_factors = parm.GetVDouble("CCscale_DetEtaAdjust_factors_run3");
	else if (_run4bool)  _CCscale_DetEtaAdjust_factors = parm.GetVDouble("CCscale_DetEtaAdjust_factors_run4");

	if(_run3bool && _run4bool) cout<<"Warning in EMSmear::No DetEtaAdjust_factors for this run setting"<<endl;
      }
    }
  }
  else{
    if (_doCCscale_uparadep) {
      _CCscaleUT15_uparadep_scale = parm.GetFloat("CCscaleUT15_uparadep_scale", 1.);
      _CCscaleUT15_uparadep_offset = parm.GetFloat("CCscaleUT15_uparadep_offset", 0.);
      _CCscaleUT30_uparadep_scale = parm.GetFloat("CCscaleUT30_uparadep_scale", 1.);
      _CCscaleUT30_uparadep_offset = parm.GetFloat("CCscaleUT30_uparadep_offset", 0.);
    }
  }

  // smearing parameters for EC region  
  _etares_phy_EC = parm.GetFloat("EtaResolution_Phys_EC", 0.001);
  _phires_phy_EC = parm.GetFloat("PhiResolution_Phys_EC", 0.0001);
  _etares_det_EC = parm.GetFloat("EtaResolution_Det_EC", 0.004);
  _phires_det_EC = parm.GetFloat("EtaResolution_Det_EC", 0.004);

  // read in values for parameters used in Jan's smearing function
  _Sampling_CC1 = parm.GetFloat("Sampling_CC1", 0.164);
  _Sampling_CC2 = parm.GetFloat("Sampling_CC2", 0.122);
  _Sampling_CCexp0 = parm.GetFloat("Sampling_CCexp0", 1.35193);
  _Sampling_CCexp1 = parm.GetFloat("Sampling_CCexp1", 2.09564);
  _Sampling_CCexp2 = parm.GetFloat("Sampling_CCexp2", 6.98578);

  _Sampling_EC1 = parm.GetFloat("Sampling_EC1", 0.206);
  _Sampling_EC2 = parm.GetFloat("Sampling_EC2", 0.);
  _Sampling_ECexp0 = parm.GetFloat("Sampling_ECexp0", 0.);
  _Sampling_ECexp1 = parm.GetFloat("Sampling_ECexp1", 0.);
  _Sampling_ECexp2 = parm.GetFloat("Sampling_ECexp2", 0.);

  _scale_EC = parm.GetFloat("Scale_EC", 1.);
  _offset_EC = parm.GetFloat("Offset_EC", 0.0);
  _sampling_EC = parm.GetFloat("Sampling_EC", 0.21);
  _constant_EC = parm.GetFloat("Constant_EC", 0.02);
  _noise_EC = parm.GetFloat("Noise_EC", 0.0);
  _Energy_Nonlinearity_EC = parm.GetFloat("Energy_Nonlinearity_EC", 0.);
  _ZElec_AvePt_EC = parm.GetFloat("ZElec_AvePt_EC", 43.);

  // control flag
  _EnergySim_ElecWindow = parm.GetBool("EnergySim_ElecWindow", kFALSE);

  // use Crystall Ball response function in CC ??
  _CrackCBsim = parm.GetBool("CrackCBsim", kFALSE);
  _CrackCB_crlimit = parm.GetFloat("CrackCB_crlimit", 0.2);
  _CrackCB_n = parm.GetFloat("CrackCB_n", 5.0);
  _CrackCB_alphaOffset = parm.GetFloat("CrackCB_alphaOffset", 4.0);
  _CrackCB_alphaSlope = parm.GetFloat("CrackCB_alphaSlope", 20.0);
  _CrackCB_PeakShiftOffset = parm.GetFloat("CrackCB_PeakShiftOffset",500.);
  _CrackCB_PeakShiftSlope = parm.GetFloat("CrackCB_PeakShiftSlope", 500.);

  // use simple PhiMod-dependent EM response correction
  _Use_Simple_EMrespCorr_vs_PhiMod = parm.GetBool("Use_Simple_EMrespCorr_vs_PhiMod", kFALSE);
  if (!_SmearEtaPhiHengne || _ApplyPhiModErespCorrHengne) {
    //based on _SmearEtaPhiHengne
    _Use_Simple_EMrespCorr_vs_PhiMod = false;
  }
  if (_Use_Simple_EMrespCorr_vs_PhiMod){
     // turn of crystal ball Phimod response and smearing model to avoid overlaps
     _CrackCBsim = false;   
     _Simple_EMrespCorr_vs_PhiMod_filename = parm.GetChar("Simple_EMrespCorr_vs_PhiMod_filename");
     gROOT->ProcessLine(TString(".x ")+_Simple_EMrespCorr_vs_PhiMod_filename);
    _Simple_EMrespCorr_vs_PhiMod = (TH1D *)gROOT->FindObject("_Simple_EMrespCorr_vs_PhiMod");
  }



  // simulate the response of electron vs track phi mod in CC
  _simulate_elecResponse_V_TrkPhiMod = parm.GetBool("simulate_elecResponse_V_TrkPhiMod", kFALSE);
  // average E/p for events with 0.1<cal phimod<0.9
  _average_EOverP = parm.GetFloat("average_EOverP", 1.);
  _elecEOverP_V_TrkPhiMod_FileName = parm.GetChar("elecEOverP_V_TrkPhiMod_FileName", "");
  if(_simulate_elecResponse_V_TrkPhiMod) {
    gROOT->ProcessLine(TString(".x ")+_elecEOverP_V_TrkPhiMod_FileName);
    _elecEOverP_V_TrkPhiMod = (TH1F *)gROOT->FindObject("WCandEOverP_V_ElecTrkPhiMod");
  }
  
  // control flag to simulate electron energy below electron window
  // IF EnergySim_ElecWindowOption = 0, Energies below electron window is divided into two parts:
  //       \delta E = UParaCorr/sin(theta) + Delta_ZSUP (UE contribution and zero-suppression effect)
  //  where UParaCorr is described in the recoil system simulation
  //  and Delta_ZSUP is zero-suppression effect on tower energy measurement and real electron energy measurement
  //
  // IF EnergySim_ElecWindowOption = 1, use the method proposed by Jan and measured by Feng
  //   take the energy difference between single energy electron without and with non-zero-suppressed ZB overlay
  //   (offline zero-suppression applied for both samples), and parameterize the energy difference as a function
  //   of underlying event energy below electron window. In PMCS, we first read the underlying event below electron
  //   window from UParaCorr_CC_Hist file, and then use the parameterization to get the corrected energy, to do
  //   it this way, UE and zero-suppression effect are combined together
  _EnergySim_ElecWindowOption = parm.GetInt("EnergySim_ElecWindowOption", 0);

  // parameterizations used only for EnergySim_ElecWindowOption = 1
  _P0_EnergyDiff_Electron_With_Without_ZBOverlay = parm.GetVDouble("P0_EnergyDiff_Electron_With_Without_ZBOverlay");
  _P1_EnergyDiff_Electron_With_Without_ZBOverlay = parm.GetVDouble("P1_EnergyDiff_Electron_With_Without_ZBOverlay");
  _P2_EnergyDiff_Electron_With_Without_ZBOverlay = parm.GetVDouble("P2_EnergyDiff_Electron_With_Without_ZBOverlay");
  _EnergyDiff_FirstBin = parm.GetVDouble("EnergyDiff_FirstBin");

  if (_EnergySim_ElecWindowOption > 1 && _EnergySim_ElecWindowOption<=3){
    std::vector<double> parameters;
    for (Int_t s =0; s < 11; ++s){
      TString para("ZBParaBinz_");
      para+=s;
      parameters = parm.GetVDouble(para.Data());
      _EnergyDiffFunctionz.push_back(new pmcsZBFunction());
      std::cout << "calling setp" << std::endl;
      _EnergyDiffFunctionz.at(s)->setp(parameters);
    }
    _EnergyDiff_Model2_FirstBinz = parm.GetVDouble("EnergyDiff_Model2_FirstBinz");
    
    for (Int_t s =0; s < 11; ++s){
      TString para("ZBParaBinw_");
      para+=s;
      parameters = parm.GetVDouble(para.Data());
      _EnergyDiffFunctionw.push_back(new pmcsZBFunction());
      _EnergyDiffFunctionw.at(s)->setp(parameters);
    }
    _EnergyDiff_Model2_FirstBinw = parm.GetVDouble("EnergyDiff_Model2_FirstBinw");
    TString zbdiff_filename(parm.GetChar("ZBDiff_filenamebase"));
    Int_t nhist = 11;
    for(int ieta=0; ieta<nhist; ieta++) {
      TString  name_hist =  (zbdiff_filename+ TString("_"));
      name_hist+=ieta;
      gROOT->ProcessLine(TString(".x ")+name_hist+ TString("z.C"));
      TString hnamezb0 = TString("deltaEvfengH_bin0_");
      hnamezb0 +=  ieta;
      _hZBLibBin0_etabinz[ieta]= (TH1D *)gROOT->FindObject(hnamezb0 + "z");
      if ( _hZBLibBin0_etabinz[ieta]){
	double x = _hZBLibBin0_etabinz[ieta]->GetRandom();
      }
      else{
	std::cout << " Cannot find " << name_hist+"z" << std::endl;
      }
      gROOT->ProcessLine(TString(".x ")+name_hist+ TString("w.C"));
      _hZBLibBin0_etabinw[ieta]= (TH1D *)gROOT->FindObject(hnamezb0 + "w");     
      if (_hZBLibBin0_etabinw[ieta])
	double x = _hZBLibBin0_etabinw[ieta]->GetRandom();
      else{
	std::cout << " Cannot find " << hnamezb0+"w" << std::endl;
      }
    }
    
    cout << "  Finished reading average Bin 0 ZBDiff  histograms" << endl;
  }

  // added on Feb. 23, 2011
  // Model dE separately in the two conditions (1) dUPara=0, (2) dUPara>0.
  else if (_EnergySim_ElecWindowOption==4) {

    // When dUPara>0, dE correlations with:
    //   - dUPara :  66%
    //   - SET :     18%
    //   - Lumi:     6%
    //   - Eta:      4%
    //   - elecPt :  2%
    // The model: 
    //  - dE vs. dUPara profile is described as a straight line with 2 parameters. 
    //  - It is done in bins of SET, Lumi and Eta. Thus a 4-D vector is chosen to store the whole model.
    
    // read parameters for dUPara>0.
    ifstream fp_duplus(parm.GetChar("dEParFileNameFordUPlus")); 
    if (fp_duplus.good()){
      // get bins from in put file
      // set bins
      int nbins;
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _dUPlusSETBins.push_back(bin);
      }

      // lumi bins
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _dUPlusLumiBins.push_back(bin);
      }

      // eta bins
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _dUPlusEtaBins.push_back(bin);
      }
     
      // parameters
      for (int iset=0; iset<(int)_dUPlusSETBins.size()-1; iset++){
        vector< vector< vector<double> > > lumi_vec;
        for (int ilumi=0; ilumi<(int)_dUPlusLumiBins.size()-1; ilumi++){
          vector< vector<double> > eta_vec;
          for (int ieta=0; ieta<(int)_dUPlusEtaBins.size()-1; ieta++){
            double par0, par1, err0, err1, chi2, ndf;
            fp_duplus >> par0 >> par1 >> err0 >> err1 >> chi2 >> ndf ;
            vector<double> e3_vec;
            e3_vec.push_back(par0);
            e3_vec.push_back(par1);
            e3_vec.push_back(err0);
            e3_vec.push_back(err1);
            e3_vec.push_back(chi2);
            e3_vec.push_back(ndf);
            eta_vec.push_back(e3_vec);
          } // ieta
          lumi_vec.push_back(eta_vec);
        } // ilumi
        _duplus_par_vec.push_back(lumi_vec);
      } // iset.. 
      
    }// fp_duplus.good()

    // When dUPara=0, dE correlations with:
    //   - SET :     5%
    //   - Lumi:     -1.4%
    //   - Eta:      -3%
    //   - elecPt :  2%
    // The model: 
    //  - dE profile in bins of SET, Lumi, Eta, and elecPt.

    // read parameters for dUPara=0.
    ifstream fp_duzero(parm.GetChar("dEParFileNameFordUZero"));
    if (fp_duzero.good()){
      // get bins from in put file
      // set bins
      int nbins;
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _dUZeroSETBins.push_back(bin);
      }

      // lumi bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _dUZeroLumiBins.push_back(bin);
      }
 
      // eta bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _dUZeroEtaBins.push_back(bin);
      }

      // pt bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _dUZeroPtBins.push_back(bin);
      }

      // parameters
      for (int iset=0; iset<(int)_dUZeroSETBins.size()-1; iset++){
        vector< vector< vector<double> > > lumi_vec;
        for (int ilumi=0; ilumi<(int)_dUZeroLumiBins.size()-1; ilumi++){
          vector< vector<double> > eta_vec;
          for (int ieta=0; ieta<(int)_dUZeroEtaBins.size()-1; ieta++){
            vector<double> pt_vec;
            for (int ipt=0; ipt<(int)_dUZeroPtBins.size()-1; ipt++){
              double par0;
              fp_duzero >> par0;
              pt_vec.push_back(par0);
            }
            eta_vec.push_back(pt_vec);
          } // ieta
          lumi_vec.push_back(eta_vec);
        } // ilumi
        _duzero_par_vec.push_back(lumi_vec);
      } // iset.. 

    } // if fp_duzero.good()

    // debug
    bool debug_de_par_file=false;
    if(debug_de_par_file){
      // dUPara>0
      ofstream duplus_par_file("duplus_par_file_for_debug.txt");
      //set bins
      duplus_par_file << _dUPlusSETBins.size() << endl;
      for (int i=0; i<_dUPlusSETBins.size(); i++) {
        duplus_par_file << _dUPlusSETBins.at(i) << " ";
      }
      duplus_par_file << endl;
      //lumi bins
      duplus_par_file << _dUPlusLumiBins.size() << endl;
      for (int i=0; i<_dUPlusLumiBins.size(); i++) {
        duplus_par_file << _dUPlusLumiBins.at(i) << " ";
      }
      duplus_par_file << endl;
      //eta bins
      duplus_par_file << _dUPlusEtaBins.size() << endl;
      for (int i=0; i<_dUPlusEtaBins.size(); i++) {
        duplus_par_file << _dUPlusEtaBins.at(i) << " ";
      }
      duplus_par_file << endl;
     
      // parameters
      for (int iset=0; iset<(int)_dUPlusSETBins.size()-1; iset++){
        for (int ilumi=0; ilumi<(int)_dUPlusLumiBins.size()-1; ilumi++){
          for (int ieta=0; ieta<(int)_dUPlusEtaBins.size()-1; ieta++){
            for (int ipar=0; ipar<6; ipar++){
              duplus_par_file << _duplus_par_vec.at(iset).at(ilumi).at(ieta).at(ipar) << " " ;
            }
            duplus_par_file << endl;
          } // ieta
        } // ilumi
      } // iset..  

      // dUPara=0
      ofstream duzero_par_file("duzero_par_file_for_debug.txt");
      //set bins
      duzero_par_file << _dUZeroSETBins.size() << endl;
      for (int i=0; i<_dUZeroSETBins.size(); i++) {
        duzero_par_file << _dUZeroSETBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //lumi bins
      duzero_par_file << _dUZeroLumiBins.size() << endl;
      for (int i=0; i<_dUZeroLumiBins.size(); i++) {
        duzero_par_file << _dUZeroLumiBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //eta bins
      duzero_par_file << _dUZeroEtaBins.size() << endl;
      for (int i=0; i<_dUZeroEtaBins.size(); i++) {
        duzero_par_file << _dUZeroEtaBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //pt bins
      duzero_par_file << _dUZeroPtBins.size() << endl;
      for (int i=0; i<_dUZeroPtBins.size(); i++) {
        duzero_par_file << _dUZeroPtBins.at(i) << " ";
      }
      duzero_par_file << endl;


      // parameters
      for (int iset=0; iset<(int)_dUZeroSETBins.size()-1; iset++){
        for (int ilumi=0; ilumi<(int)_dUZeroLumiBins.size()-1; ilumi++){
          for (int ieta=0; ieta<(int)_dUZeroEtaBins.size()-1; ieta++){
            for (int ipt=0; ipt<(int)_dUZeroPtBins.size()-1; ipt++){
              duzero_par_file << _duzero_par_vec.at(iset).at(ilumi).at(ieta).at(ipt) << " " ;
            } // ipt
            duzero_par_file << endl;
          } // ieta
        } // ilumi
      } // iset..  

    } // if debug_de_par_file

  } // if (_EnergySim_ElecWindowOption==4) 

  // added on April 4, 2011
  // Model dE separately in the two conditions (1) dUPara=0, (2) dUPara>0.
  // using decomposed Wenu sample (CAEP)
  else if (_EnergySim_ElecWindowOption==5) {
     
    // options
    _CAEPSmoothdUPlus = parm.GetInt("CAEPSmoothdUPlus", 0);
    _CAEPSmoothdUZero = parm.GetInt("CAEPSmoothdUZero", 0);
  
    // When dUPara>0, dE correlations with:
    // The model: 
    //  - dE vs. dUPara profile is described as a straight line with 2 parameters. 
    //  - Modeld in bins of Eta, ElecPt, UPara, Lumi and SET. 
    //  - Binning is passed in through parameters file
    
    // read parameters for dUPara>0.
    ifstream fp_duplus(parm.GetChar("dEParFileNameFordUPlus_CAEP"));

    if (fp_duplus.good()){
      // get bins from in put file

      // eta bins
      int nbins;
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin; 
        fp_duplus >> bin;
        _CAEPdUPlusEtaBins.push_back(bin);
      }

      // pt bins
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _CAEPdUPlusPtBins.push_back(bin);
      }

      // upara bins
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _CAEPdUPlusUParaBins.push_back(bin);
      }

      // lumi bins
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _CAEPdUPlusLumiBins.push_back(bin);
      }

      // set bins
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _CAEPdUPlusSETBins.push_back(bin);
      }

      // parameters
      for (int ieta=0; ieta<(int)_CAEPdUPlusEtaBins.size()-1; ieta++){
        vector< vector< vector< vector<double*> > > > par_vec_4d;
        for (int ipt=0; ipt<(int)_CAEPdUPlusPtBins.size()-1; ipt++){
          vector< vector< vector<double*> > > par_vec_3d;
          for (int iupara=0; iupara<(int)_CAEPdUPlusUParaBins.size()-1; iupara++){
            vector< vector<double*> > par_vec_2d;
            for (int ilumi=0; ilumi<(int)_CAEPdUPlusLumiBins.size()-1; ilumi++){
              vector<double*> par_vec_1d;
              for (int iset=0; iset<(int)_CAEPdUPlusSETBins.size()-1; iset++){
                double meta, mpt, mupara, mlumi, mset, par0, par1, err0, err1, chi2, ndf;
                fp_duplus >>  meta >> mpt >> mupara >> mlumi >> mset >> par0 >> par1 >> err0 >> err1 >> chi2 >> ndf ;
                double* par = new double[11];
                par[0] = meta;
                par[1] = mpt;
                par[2] = mupara;
                par[3] = mlumi;
                par[4] = mset;
                par[5] = par0;
                par[6] = par1;
                par[7] = err0;
                par[8] = err1;
                par[9] = chi2;
                par[10] = ndf;
                par_vec_1d.push_back(par);
              }
              par_vec_2d.push_back(par_vec_1d);
            } // ilumi
            par_vec_3d.push_back(par_vec_2d);
          } // iupara
          par_vec_4d.push_back(par_vec_3d);
        } // ipt
        _caep_duplus_par_vec.push_back(par_vec_4d);
      }// ieta

    }// fp_duplus.good()

    // When dUPara=0, dE correlations with:
    // The model: 
    //  - mean dE in bins of Eta, ElecPt, UPara, Lumi, and SET.

    // read parameters for dUPara=0.
    ifstream fp_duzero(parm.GetChar("dEParFileNameFordUZero_CAEP"));
    if (fp_duzero.good()){
      // get bins from in put file

      // eta bins
      int nbins;
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _CAEPdUZeroEtaBins.push_back(bin);
      }

      // pt bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _CAEPdUZeroPtBins.push_back(bin);
      }

      // upara bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _CAEPdUZeroUParaBins.push_back(bin);
      }

      // lumi bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _CAEPdUZeroLumiBins.push_back(bin);
      }

      // set bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _CAEPdUZeroSETBins.push_back(bin);
      }

      // parameters
      for (int ieta=0; ieta<(int)_CAEPdUZeroEtaBins.size()-1; ieta++){
        vector< vector< vector< vector<double*> > > > par_vec_4d;
        for (int ipt=0; ipt<(int)_CAEPdUZeroPtBins.size()-1; ipt++){
          vector< vector< vector<double*> > > par_vec_3d;
          for (int iupara=0; iupara<(int)_CAEPdUZeroUParaBins.size()-1; iupara++){
            vector< vector<double*> > par_vec_2d;
            for (int ilumi=0; ilumi<(int)_CAEPdUZeroLumiBins.size()-1; ilumi++){
              vector<double*> par_vec_1d;
              for (int iset=0; iset<(int)_CAEPdUZeroSETBins.size()-1; iset++){
                double meta, mpt, mupara, mlumi, mset, mde;
                double merreta, merrpt, merrupara, merrlumi, merrset, merrde;
                fp_duzero >>  meta >> mpt >> mupara >> mlumi >> mset >> mde ;
                fp_duzero >>  merreta >> merrpt >> merrupara >> merrlumi >> merrset >> merrde ;
                double* par = new double[12];
                par[0] = meta;
                par[1] = mpt;
                par[2] = mupara;
                par[3] = mlumi;
                par[4] = mset;
                par[5] = mde;
                par[6] = merreta;
                par[7] = merrpt;
                par[8] = merrupara;
                par[9] = merrlumi;
                par[10] = merrset;
                par[11] = merrde;
                par_vec_1d.push_back(par);
              }
              par_vec_2d.push_back(par_vec_1d);
            } // ilumi
            par_vec_3d.push_back(par_vec_2d);
          } // iupara
          par_vec_4d.push_back(par_vec_3d);
        } // ipt
        _caep_duzero_par_vec.push_back(par_vec_4d);
      }// ieta

    } // if fp_duzero.good()



    // debug
    bool debug_de_par_file=false;
    if(debug_de_par_file){

      // dUPara>0
      ofstream duplus_par_file("caep_duplus_par_file_for_debug.txt");
      //eta bins
      duplus_par_file << _CAEPdUPlusEtaBins.size() << endl;
      for (int i=0; i<_CAEPdUPlusEtaBins.size(); i++) {
        duplus_par_file << _CAEPdUPlusEtaBins.at(i) << " ";
      }
      duplus_par_file << endl;
      //pt bins
      duplus_par_file << _CAEPdUPlusPtBins.size() << endl;
      for (int i=0; i<_CAEPdUPlusPtBins.size(); i++) {
        duplus_par_file << _CAEPdUPlusPtBins.at(i) << " ";
      }
      duplus_par_file << endl;
      //upara bins
      duplus_par_file << _CAEPdUPlusUParaBins.size() << endl;
      for (int i=0; i<_CAEPdUPlusUParaBins.size(); i++) {
        duplus_par_file << _CAEPdUPlusUParaBins.at(i) << " ";
      }
      duplus_par_file << endl;
      //lumi bins
      duplus_par_file << _CAEPdUPlusLumiBins.size() << endl;
      for (int i=0; i<_CAEPdUPlusLumiBins.size(); i++) {
        duplus_par_file << _CAEPdUPlusLumiBins.at(i) << " ";
      }
      duplus_par_file << endl;
      //set bins
      duplus_par_file << _CAEPdUPlusSETBins.size() << endl;
      for (int i=0; i<_CAEPdUPlusSETBins.size(); i++) {
        duplus_par_file << _CAEPdUPlusSETBins.at(i) << " ";
      }
      duplus_par_file << endl;
      // parameters
      for (int ieta=0; ieta<(int)_CAEPdUPlusEtaBins.size()-1; ieta++){
        for (int ipt=0; ipt<(int)_CAEPdUPlusPtBins.size()-1; ipt++){
          for (int iupara=0; iupara<(int)_CAEPdUPlusUParaBins.size()-1; iupara++){
            for (int ilumi=0; ilumi<(int)_CAEPdUPlusLumiBins.size()-1; ilumi++){
              for (int iset=0; iset<(int)_CAEPdUPlusSETBins.size()-1; iset++){
                for (int ipar=0; ipar<11; ipar++){
                  duplus_par_file << _caep_duplus_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[ipar] << " ";
                }
                duplus_par_file << endl; 
              } // iset
            } // ilumi
          } // iupara
        } // ipt
      }// ieta          

      // dUPara=0
      ofstream duzero_par_file("caep_duzero_par_file_for_debug.txt");
      //eta bins
      duzero_par_file << _CAEPdUZeroEtaBins.size() << endl;
      for (int i=0; i<_CAEPdUZeroEtaBins.size(); i++) {
        duzero_par_file << _CAEPdUZeroEtaBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //pt bins
      duzero_par_file << _CAEPdUZeroPtBins.size() << endl;
      for (int i=0; i<_CAEPdUZeroPtBins.size(); i++) {
        duzero_par_file << _CAEPdUZeroPtBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //upara bins
      duzero_par_file << _CAEPdUZeroUParaBins.size() << endl;
      for (int i=0; i<_CAEPdUZeroUParaBins.size(); i++) {
        duzero_par_file << _CAEPdUZeroUParaBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //lumi bins
      duzero_par_file << _CAEPdUZeroLumiBins.size() << endl;
      for (int i=0; i<_CAEPdUZeroLumiBins.size(); i++) {
        duzero_par_file << _CAEPdUZeroLumiBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //set bins
      duzero_par_file << _CAEPdUZeroSETBins.size() << endl;
      for (int i=0; i<_CAEPdUZeroSETBins.size(); i++) {
        duzero_par_file << _CAEPdUZeroSETBins.at(i) << " ";
      }
      duzero_par_file << endl;
      // parameters
      for (int ieta=0; ieta<(int)_CAEPdUZeroEtaBins.size()-1; ieta++){
        for (int ipt=0; ipt<(int)_CAEPdUZeroPtBins.size()-1; ipt++){
          for (int iupara=0; iupara<(int)_CAEPdUZeroUParaBins.size()-1; iupara++){
            for (int ilumi=0; ilumi<(int)_CAEPdUZeroLumiBins.size()-1; ilumi++){
              for (int iset=0; iset<(int)_CAEPdUZeroSETBins.size()-1; iset++){
                for (int ipar=0; ipar<12; ipar++){
                  duzero_par_file << _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[ipar] << " ";
                }
                duzero_par_file << endl;
              } // iset
            } // ilumi
          } // iupara
        } // ipt
      }// ieta
    } // if debug_de_par_file

  } //  if (_EnergySim_ElecWindowOption==5)

  // added on Feb 10, 2013
  // Model dE separately in the two conditions (1) dUPara=0, (2) dUPara>0.
  // using decomposed Wenu sample (CAEP)
  // same as opiton 5, just store parameters separately for 2b3 and 4
  else if (_EnergySim_ElecWindowOption==6) {
     
    // When dUPara>0, dE correlations with:
    // The model: 
    //  - dE vs. dUPara profile is described as a straight line with 2 parameters. 
    //  - Modeld in bins of Eta, ElecPt, UPara, Lumi and SET. 
    //  - Binning is passed in through parameters file
    
    // read parameters for dUPara>0.
    ifstream fp_duplus(parm.GetChar("dEParFileNameFordUPlus_CAEP"));

    if (fp_duplus.good()){
      // get bins from in put file

      // eta bins
      int nbins;
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin; 
        fp_duplus >> bin;
        _CAEPdUPlusEtaBins.push_back(bin);
      }

      // pt bins
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _CAEPdUPlusPtBins.push_back(bin);
      }

      // upara bins
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _CAEPdUPlusUParaBins.push_back(bin);
      }

      // lumi bins
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _CAEPdUPlusLumiBins.push_back(bin);
      }

      // set bins
      fp_duplus >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus >> bin;
        _CAEPdUPlusSETBins.push_back(bin);
      }

      // parameters
      for (int ieta=0; ieta<(int)_CAEPdUPlusEtaBins.size()-1; ieta++){
        vector< vector< vector< vector<double*> > > > par_vec_4d;
        for (int ipt=0; ipt<(int)_CAEPdUPlusPtBins.size()-1; ipt++){
          vector< vector< vector<double*> > > par_vec_3d;
          for (int iupara=0; iupara<(int)_CAEPdUPlusUParaBins.size()-1; iupara++){
            vector< vector<double*> > par_vec_2d;
            for (int ilumi=0; ilumi<(int)_CAEPdUPlusLumiBins.size()-1; ilumi++){
              vector<double*> par_vec_1d;
              for (int iset=0; iset<(int)_CAEPdUPlusSETBins.size()-1; iset++){
                double meta, mpt, mupara, mlumi, mset, par0, par1, err0, err1, chi2, ndf;
                fp_duplus >>  meta >> mpt >> mupara >> mlumi >> mset >> par0 >> par1 >> err0 >> err1 >> chi2 >> ndf ;
                double* par = new double[11];
                par[0] = meta;
                par[1] = mpt;
                par[2] = mupara;
                par[3] = mlumi;
                par[4] = mset;
                par[5] = par0;
                par[6] = par1;
                par[7] = err0;
                par[8] = err1;
                par[9] = chi2;
                par[10] = ndf;
                par_vec_1d.push_back(par);
              }
              par_vec_2d.push_back(par_vec_1d);
            } // ilumi
            par_vec_3d.push_back(par_vec_2d);
          } // iupara
          par_vec_4d.push_back(par_vec_3d);
        } // ipt
        _caep_duplus_par_vec.push_back(par_vec_4d);
      }// ieta

    }// fp_duplus.good()

    // When dUPara=0, dE correlations with:
    // The model: 
    //  - mean dE in bins of Eta, ElecPt, UPara, Lumi, and SET.

    // read parameters for dUPara=0.
    ifstream fp_duzero(parm.GetChar("dEParFileNameFordUZero_CAEP"));
    if (fp_duzero.good()){
      // get bins from in put file

      // eta bins
      int nbins;
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _CAEPdUZeroEtaBins.push_back(bin);
      }

      // pt bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _CAEPdUZeroPtBins.push_back(bin);
      }

      // upara bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _CAEPdUZeroUParaBins.push_back(bin);
      }

      // lumi bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _CAEPdUZeroLumiBins.push_back(bin);
      }

      // set bins
      fp_duzero >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero >> bin;
        _CAEPdUZeroSETBins.push_back(bin);
      }

      // parameters
      for (int ieta=0; ieta<(int)_CAEPdUZeroEtaBins.size()-1; ieta++){
        vector< vector< vector< vector<double*> > > > par_vec_4d;
        for (int ipt=0; ipt<(int)_CAEPdUZeroPtBins.size()-1; ipt++){
          vector< vector< vector<double*> > > par_vec_3d;
          for (int iupara=0; iupara<(int)_CAEPdUZeroUParaBins.size()-1; iupara++){
            vector< vector<double*> > par_vec_2d;
            for (int ilumi=0; ilumi<(int)_CAEPdUZeroLumiBins.size()-1; ilumi++){
              vector<double*> par_vec_1d;
              for (int iset=0; iset<(int)_CAEPdUZeroSETBins.size()-1; iset++){
                double meta, mpt, mupara, mlumi, mset, mde;
                double merreta, merrpt, merrupara, merrlumi, merrset, merrde;
                fp_duzero >>  meta >> mpt >> mupara >> mlumi >> mset >> mde ;
                fp_duzero >>  merreta >> merrpt >> merrupara >> merrlumi >> merrset >> merrde ;
                double* par = new double[12];
                par[0] = meta;
                par[1] = mpt;
                par[2] = mupara;
                par[3] = mlumi;
                par[4] = mset;
                par[5] = mde;
                par[6] = merreta;
                par[7] = merrpt;
                par[8] = merrupara;
                par[9] = merrlumi;
                par[10] = merrset;
                par[11] = merrde;
                par_vec_1d.push_back(par);
              }
              par_vec_2d.push_back(par_vec_1d);
            } // ilumi
            par_vec_3d.push_back(par_vec_2d);
          } // iupara
          par_vec_4d.push_back(par_vec_3d);
        } // ipt
        _caep_duzero_par_vec.push_back(par_vec_4d);
      }// ieta

    } // if fp_duzero.good()


    // A second copy of the parameters, this is for 2b4. 
    // When dUPara>0, dE correlations with:
    // The model: 
    //  - dE vs. dUPara profile is described as a straight line with 2 parameters. 
    //  - Modeld in bins of Eta, ElecPt, UPara, Lumi and SET. 
    //  - Binning is passed in through parameters file
    
    // read parameters for dUPara>0.
    ifstream fp_duplus2(parm.GetChar("dEParFileNameFordUPlus_CAEP2"));

    if (fp_duplus2.good()){
      // get bins from in put file

      // eta bins
      int nbins;
      fp_duplus2 >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin; 
        fp_duplus2 >> bin;
        _CAEPdUPlusEtaBins2.push_back(bin);
      }

      // pt bins
      fp_duplus2 >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus2 >> bin;
        _CAEPdUPlusPtBins2.push_back(bin);
      }

      // upara bins
      fp_duplus2 >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus2 >> bin;
        _CAEPdUPlusUParaBins2.push_back(bin);
      }

      // lumi bins
      fp_duplus2 >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus2 >> bin;
        _CAEPdUPlusLumiBins2.push_back(bin);
      }

      // set bins
      fp_duplus2 >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duplus2 >> bin;
        _CAEPdUPlusSETBins2.push_back(bin);
      }

      // parameters
      for (int ieta=0; ieta<(int)_CAEPdUPlusEtaBins2.size()-1; ieta++){
        vector< vector< vector< vector<double*> > > > par_vec_4d;
        for (int ipt=0; ipt<(int)_CAEPdUPlusPtBins2.size()-1; ipt++){
          vector< vector< vector<double*> > > par_vec_3d;
          for (int iupara=0; iupara<(int)_CAEPdUPlusUParaBins2.size()-1; iupara++){
            vector< vector<double*> > par_vec_2d;
            for (int ilumi=0; ilumi<(int)_CAEPdUPlusLumiBins2.size()-1; ilumi++){
              vector<double*> par_vec_1d;
              for (int iset=0; iset<(int)_CAEPdUPlusSETBins2.size()-1; iset++){
                double meta, mpt, mupara, mlumi, mset, par0, par1, err0, err1, chi2, ndf;
                fp_duplus2 >>  meta >> mpt >> mupara >> mlumi >> mset >> par0 >> par1 >> err0 >> err1 >> chi2 >> ndf ;
                double* par = new double[11];
                par[0] = meta;
                par[1] = mpt;
                par[2] = mupara;
                par[3] = mlumi;
                par[4] = mset;
                par[5] = par0;
                par[6] = par1;
                par[7] = err0;
                par[8] = err1;
                par[9] = chi2;
                par[10] = ndf;
                par_vec_1d.push_back(par);
              }
              par_vec_2d.push_back(par_vec_1d);
            } // ilumi
            par_vec_3d.push_back(par_vec_2d);
          } // iupara
          par_vec_4d.push_back(par_vec_3d);
        } // ipt
        _caep_duplus_par_vec2.push_back(par_vec_4d);
      }// ieta

    }// fp_duplus.good()

    // When dUPara=0, dE correlations with:
    // The model: 
    //  - mean dE in bins of Eta, ElecPt, UPara, Lumi, and SET.

    // read parameters for dUPara=0.
    ifstream fp_duzero2(parm.GetChar("dEParFileNameFordUZero_CAEP2"));
    if (fp_duzero.good()){
      // get bins from in put file

      // eta bins
      int nbins;
      fp_duzero2 >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero2 >> bin;
        _CAEPdUZeroEtaBins2.push_back(bin);
      }

      // pt bins
      fp_duzero2 >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero2 >> bin;
        _CAEPdUZeroPtBins2.push_back(bin);
      }

      // upara bins
      fp_duzero2 >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero2 >> bin;
        _CAEPdUZeroUParaBins2.push_back(bin);
      }

      // lumi bins
      fp_duzero2 >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero2 >> bin;
        _CAEPdUZeroLumiBins2.push_back(bin);
      }

      // set bins
      fp_duzero2 >> nbins;
      for (int i=0; i<nbins; i++) {
        double bin;
        fp_duzero2 >> bin;
        _CAEPdUZeroSETBins2.push_back(bin);
      }

      // parameters
      for (int ieta=0; ieta<(int)_CAEPdUZeroEtaBins2.size()-1; ieta++){
        vector< vector< vector< vector<double*> > > > par_vec_4d;
        for (int ipt=0; ipt<(int)_CAEPdUZeroPtBins2.size()-1; ipt++){
          vector< vector< vector<double*> > > par_vec_3d;
          for (int iupara=0; iupara<(int)_CAEPdUZeroUParaBins2.size()-1; iupara++){
            vector< vector<double*> > par_vec_2d;
            for (int ilumi=0; ilumi<(int)_CAEPdUZeroLumiBins2.size()-1; ilumi++){
              vector<double*> par_vec_1d;
              for (int iset=0; iset<(int)_CAEPdUZeroSETBins2.size()-1; iset++){
                double meta, mpt, mupara, mlumi, mset, mde;
                double merreta, merrpt, merrupara, merrlumi, merrset, merrde;
                fp_duzero2 >>  meta >> mpt >> mupara >> mlumi >> mset >> mde ;
                fp_duzero2 >>  merreta >> merrpt >> merrupara >> merrlumi >> merrset >> merrde ;
                double* par = new double[12];
                par[0] = meta;
                par[1] = mpt;
                par[2] = mupara;
                par[3] = mlumi;
                par[4] = mset;
                par[5] = mde;
                par[6] = merreta;
                par[7] = merrpt;
                par[8] = merrupara;
                par[9] = merrlumi;
                par[10] = merrset;
                par[11] = merrde;
                par_vec_1d.push_back(par);
              }
              par_vec_2d.push_back(par_vec_1d);
            } // ilumi
            par_vec_3d.push_back(par_vec_2d);
          } // iupara
          par_vec_4d.push_back(par_vec_3d);
        } // ipt
        _caep_duzero_par_vec2.push_back(par_vec_4d);
      }// ieta

    } // if fp_duzero.good()


    // debug
    bool debug_de_par_file=false;
    if(debug_de_par_file){
    
      // dUPara>0
      ofstream duplus_par_file("caep_duplus_par_file_for_debug.txt");
      //eta bins
      duplus_par_file << _CAEPdUPlusEtaBins.size() << endl;
      for (int i=0; i<_CAEPdUPlusEtaBins.size(); i++) {
        duplus_par_file << _CAEPdUPlusEtaBins.at(i) << " ";
      }
      duplus_par_file << endl;
      //pt bins
      duplus_par_file << _CAEPdUPlusPtBins.size() << endl;
      for (int i=0; i<_CAEPdUPlusPtBins.size(); i++) {
        duplus_par_file << _CAEPdUPlusPtBins.at(i) << " ";
      }
      duplus_par_file << endl;
      //upara bins
      duplus_par_file << _CAEPdUPlusUParaBins.size() << endl;
      for (int i=0; i<_CAEPdUPlusUParaBins.size(); i++) {
        duplus_par_file << _CAEPdUPlusUParaBins.at(i) << " ";
      }
      duplus_par_file << endl;
      //lumi bins
      duplus_par_file << _CAEPdUPlusLumiBins.size() << endl;
      for (int i=0; i<_CAEPdUPlusLumiBins.size(); i++) {
        duplus_par_file << _CAEPdUPlusLumiBins.at(i) << " ";
      }
      duplus_par_file << endl;
      //set bins
      duplus_par_file << _CAEPdUPlusSETBins.size() << endl;
      for (int i=0; i<_CAEPdUPlusSETBins.size(); i++) {
        duplus_par_file << _CAEPdUPlusSETBins.at(i) << " ";
      }
      duplus_par_file << endl;
      // parameters
      for (int ieta=0; ieta<(int)_CAEPdUPlusEtaBins.size()-1; ieta++){
        for (int ipt=0; ipt<(int)_CAEPdUPlusPtBins.size()-1; ipt++){
          for (int iupara=0; iupara<(int)_CAEPdUPlusUParaBins.size()-1; iupara++){
            for (int ilumi=0; ilumi<(int)_CAEPdUPlusLumiBins.size()-1; ilumi++){
              for (int iset=0; iset<(int)_CAEPdUPlusSETBins.size()-1; iset++){
                for (int ipar=0; ipar<11; ipar++){
                  duplus_par_file << _caep_duplus_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[ipar] << " ";
                }
                duplus_par_file << endl;
              } // iset
            } // ilumi
          } // iupara
        } // ipt
      }// ieta          

      // dUPara=0
      ofstream duzero_par_file("caep_duzero_par_file_for_debug.txt");
      //eta bins
      duzero_par_file << _CAEPdUZeroEtaBins.size() << endl;
      for (int i=0; i<_CAEPdUZeroEtaBins.size(); i++) {
        duzero_par_file << _CAEPdUZeroEtaBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //pt bins
      duzero_par_file << _CAEPdUZeroPtBins.size() << endl;
      for (int i=0; i<_CAEPdUZeroPtBins.size(); i++) {
        duzero_par_file << _CAEPdUZeroPtBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //upara bins
      duzero_par_file << _CAEPdUZeroUParaBins.size() << endl;
      for (int i=0; i<_CAEPdUZeroUParaBins.size(); i++) {
        duzero_par_file << _CAEPdUZeroUParaBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //lumi bins
      duzero_par_file << _CAEPdUZeroLumiBins.size() << endl;
      for (int i=0; i<_CAEPdUZeroLumiBins.size(); i++) {
        duzero_par_file << _CAEPdUZeroLumiBins.at(i) << " ";
      }
      duzero_par_file << endl;
      //set bins
      duzero_par_file << _CAEPdUZeroSETBins.size() << endl;
      for (int i=0; i<_CAEPdUZeroSETBins.size(); i++) {
        duzero_par_file << _CAEPdUZeroSETBins.at(i) << " ";
      }
      duzero_par_file << endl;
      // parameters
      for (int ieta=0; ieta<(int)_CAEPdUZeroEtaBins.size()-1; ieta++){
        for (int ipt=0; ipt<(int)_CAEPdUZeroPtBins.size()-1; ipt++){
          for (int iupara=0; iupara<(int)_CAEPdUZeroUParaBins.size()-1; iupara++){
            for (int ilumi=0; ilumi<(int)_CAEPdUZeroLumiBins.size()-1; ilumi++){
              for (int iset=0; iset<(int)_CAEPdUZeroSETBins.size()-1; iset++){
                for (int ipar=0; ipar<12; ipar++){
                  duzero_par_file << _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[ipar] << " ";
                }
                duzero_par_file << endl;
              } // iset
            } // ilumi
          } // iupara
        } // ipt
      }// ieta
    } // if debug_de_par_file


  } // end of  if (_EnergySim_ElecWindowOption==6)
  
 

  _electronicNoiseFactor = parm.GetDouble("electronicNoiseFactor",0.85);
  //
  //         Run Ia method
  //  
  // true underlying event contribution (before zero-suppression corrections)
  //_UE_ElecWindow_true = parm.GetFloat("UE_ElecWindow_True", 0.);
  // average number of towers per EM cluster
  //   _NumTowers_EMCluster = parm.GetFloat("NumTowers_EMCluster", 0.);
  // zero-suppression effect per tower due to asymmetric uranium noise
  //   _ZSUP_UE = parm.GetFloat("ZSUP_UE", 0.);
  // zero-suppression effect on real electron measurement
  //   _ZSUP_Elec = parm.GetFloat("ZSUP_Elec", 0.);
  // real electron energy that is outside of the electron cone
  //   _ENERGY_OUTCONE_Elec = parm.GetFloat("ENERGY_OUTCONE_Elec", 0.);
  //
  //        End of Run Ia method
  //

  // option for UParaCorrection
  _UParaCorrOption = (int)(parm.GetFloat("UParaCorrOption", 1));

  // if uparaCorrOption==2 will read average 13 tower Et distribution from a root file
  if(_UParaCorrOption == 2) {
    //    TFile *fupara = new TFile("/work/okaara-clued0/junjie/WMASS/p1810_release/result_fullMC_uEventAnalysis_Wen_bugFix.root");
    cout << "  Reading average 13 tower Et distributions for different luminosity and uparallel regions from a root file" << endl;
    TString uparacorr_filename(parm.GetChar("UParaCorr_13towers_root_filename"));
    TFile *fupara = new TFile(uparacorr_filename);
    if(fupara->IsZombie()) {
      cout<<"   Please provide "<<uparacorr_filename<<endl;
      exit(-1);
    }
    fupara->cd("UE_Hist");
    _UParaCorrRunIIb = (parm.GetBool("UParaCorrRunIIb", kFALSE));
    Int_t nhist = 13;
    if (_UParaCorrRunIIb) nhist = 5;
    for(int ilumi=0; ilumi<nhist; ilumi++) {
      for(int iupara=0; iupara<5; iupara++) {
	char name_hist[50]; 
	sprintf(name_hist, "%s%d%s%d", "sum13towEt_ReBin_Lumi_", ilumi, "_Upara_", iupara);
	_hEt_ThirteenTowers[ilumi][iupara]= (TH1F *)gROOT->FindObject(name_hist);
	// initalize the integration for each histogram, this will speed up the code
	// if the histogram is empty, it will print out some error messages     
        double x = _hEt_ThirteenTowers[ilumi][iupara]->GetRandom();
      }
    }
    cout << "  Finished reading average 13 tower Et histograms" << endl;
  }

  // UParaCorrOption==3, method added on Jan. 28, 2011, 
  // model the Mean of dUPara and Smear of dUPara separately
  else if (_UParaCorrOption == 3){
    // options of UParaCorrOption==3
    //  0: Smooth Function for Mean dUPara
    //  1: 2D Profile for Mean dUPara 
    //  2: Model dUPara=0 and dUPara>0 separately. 
    //    - Fraction of dUPara=0 : function of SET, UPara and Lumi
    //    - Mean of dUPara>0 : function of SET, UPara and Lumi
    //    - Smear of dUPara>0 : hists in bins of SET and UPara
    _OptionOfUParaCorrOption3 = parm.GetInt("OptionOfUParaCorrOption3", 1);
    _UParaCorrOption3_dUParaLibUsedEPara = parm.GetBool("UParaCorrOption3_dUParaLibUsedEPara", false);
    cout << "UParaCorrOption == 3 : Reading dUPara Mean and Smear functions from root file." << endl;
    TString dUParaFunction_filename(parm.GetChar("dUParaMeanAndSmearFunctionsFilename"));
    TFile *file_dUParaFunction = new TFile(dUParaFunction_filename);
    if(file_dUParaFunction->IsZombie()) {
      cout<<"   Please provide "<< dUParaFunction_filename <<endl;
      exit(-1);
    }
    TFile *file_dUParaFunction2; // predefine this TFile for Option of Option3 == 5, store 2b3/4 separately.

    if (_OptionOfUParaCorrOption3==0){
      // Get Mean dUPara Function vs SET and UPara
      _dUParaMeanFunction = (TF2*)file_dUParaFunction->Get("dUParaMeanFunction");
    }
    else if (_OptionOfUParaCorrOption3==1) {
      // Get Mean dUPara Profile vs SET and UPara
      _dUParaMeanProfile = (TProfile2D*)file_dUParaFunction->Get("dUParaMeanProfile");
    }
    else if (_OptionOfUParaCorrOption3==2) {
      // Get Mean dUPara Profile and ZeroFraction as a function of SET, UPara and Lumi
      _dUParaMeanProfile3D = (TH3D*)file_dUParaFunction->Get("dUParaMeanProfile3D");
      _dUParaZeroFraction3D = (TH3D*)file_dUParaFunction->Get("dUParaZeroFraction3D");
    }
    else if (_OptionOfUParaCorrOption3==3) {
      // Get Mean dUPara Profile and ZeroFraction as a function of SET, UPara and Lumi, in 11 PhyEta bins
      for (int ietabin=0; ietabin<11; ietabin++){
        char name_hist[500];
        sprintf(name_hist, "dUParaMeanProfile3D_%d", ietabin);
        _dUParaMeanProfile3DEta[ietabin] = (TH3D*)file_dUParaFunction->Get(name_hist);
        sprintf(name_hist, "dUParaZeroFraction3D_%d", ietabin);
        _dUParaZeroFraction3DEta[ietabin] = (TH3D*)file_dUParaFunction->Get(name_hist);
      }
    }
    else if (_OptionOfUParaCorrOption3==4) {
      // Option of Option3 == 4
      // Get Mean dUPara Profile and ZeroFraction as a function of SET, UPara and Lumi, in 11 DetEta bins and 10 eEta-DetEta bins
      for (int ietabin=0; ietabin<11; ietabin++){
        for (int jetabin=0; jetabin<10; jetabin++){
          char name_hist[500];
          sprintf(name_hist, "dUParaMeanProfile3D_%d_%d", ietabin, jetabin);
          _dUParaMeanProfile3D2Eta[ietabin][jetabin] = (TH3D*)file_dUParaFunction->Get(name_hist);
          sprintf(name_hist, "dUParaZeroFraction3D_%d_%d", ietabin, jetabin);
          _dUParaZeroFraction3D2Eta[ietabin][jetabin] = (TH3D*)file_dUParaFunction->Get(name_hist);
        }
      }
    }
    else if (_OptionOfUParaCorrOption3==5) {
      // Option of Option3 == 5
      // two sets of input files, one for 2b3, the other for 2b4
      TString dUParaFunction_filename2(parm.GetChar("dUParaMeanAndSmearFunctionsFilename2"));
      file_dUParaFunction2 = new TFile(dUParaFunction_filename2);
      if(file_dUParaFunction2->IsZombie()) {
        cout<<"   Please provide "<< dUParaFunction_filename2 <<endl;
        exit(-1);
      }
     
      // Get Mean dUPara Profile and ZeroFraction as a function of SET, UPara and Lumi, in 11 DetEta bins and 10 eEta-DetEta bins
      // for 2b3
      for (int ietabin=0; ietabin<11; ietabin++){
        for (int jetabin=0; jetabin<10; jetabin++){
          char name_hist[500];
          sprintf(name_hist, "dUParaMeanProfile3D_%d_%d", ietabin, jetabin);
          _dUParaMeanProfile3D2Eta[ietabin][jetabin] = (TH3D*)file_dUParaFunction->Get(name_hist);
          sprintf(name_hist, "dUParaZeroFraction3D_%d_%d", ietabin, jetabin);
          _dUParaZeroFraction3D2Eta[ietabin][jetabin] = (TH3D*)file_dUParaFunction->Get(name_hist);
        }
      } 
      // for 2b4
      for (int ietabin=0; ietabin<11; ietabin++){
        for (int jetabin=0; jetabin<10; jetabin++){
          char name_hist[500];
          sprintf(name_hist, "dUParaMeanProfile3D_%d_%d", ietabin, jetabin);
          _dUParaMeanProfile3D2Eta2[ietabin][jetabin] = (TH3D*)file_dUParaFunction2->Get(name_hist);
          sprintf(name_hist, "dUParaZeroFraction3D_%d_%d", ietabin, jetabin);
          _dUParaZeroFraction3D2Eta2[ietabin][jetabin] = (TH3D*)file_dUParaFunction2->Get(name_hist);
        }
      } 

    }
    else if (_OptionOfUParaCorrOption3==6) {
      // _OptionOfUParaCorrOption3==6 adds UPerp dependence on top of _OptionOfUParaCorrOption3==4
      // 
      // Get Mean dUPara Profile and ZeroFraction as a function of SET, UPara and Lumi,
      // in 5 DetEta bins and 5 eEta-detEta bins, and 2 bins in uperp
      for (int ietabin=0; ietabin<11; ietabin++){
        for (int jetabin=0; jetabin<10; jetabin++){
          for (int iuperpbin=0; iuperpbin<2; iuperpbin++){
            char name_hist[500];
            sprintf(name_hist, "dUParaMeanProfile3D_%d_%d_%d", ietabin, jetabin, iuperpbin);
            _dUParaMeanProfile3D2EtaUPerp[ietabin][jetabin][iuperpbin] = (TH3D*)file_dUParaFunction->Get(name_hist);
            sprintf(name_hist, "dUParaZeroFraction3D_%d_%d_%d", ietabin, jetabin, iuperpbin);
            _dUParaZeroFraction3D2EtaUPerp[ietabin][jetabin][iuperpbin] = (TH3D*)file_dUParaFunction->Get(name_hist);
          } // iuperp
        } // jetabin
      } // ietabin
 
    }
    else if (_OptionOfUParaCorrOption3==7) {
      // _OptionOfUParaCorrOption3==7 same as 6, adds UPerp dependence on top of _OptionOfUParaCorrOption3==4
      // but do it separately for 2b3 and 2b4
      TString dUParaFunction_filename2(parm.GetChar("dUParaMeanAndSmearFunctionsFilename2"));
      file_dUParaFunction2 = new TFile(dUParaFunction_filename2);
      if(file_dUParaFunction2->IsZombie()) {
        cout<<"   Please provide "<< dUParaFunction_filename2 <<endl;
        exit(-1);
      }

      // Get Mean dUPara Profile and ZeroFraction as a function of SET, UPara and Lumi,
      // 2b3
      // in 11 DetEta bins and 10 eEta-detEta bins, and 2 bins in uperp
      for (int ietabin=0; ietabin<11; ietabin++){
        for (int jetabin=0; jetabin<10; jetabin++){
          for (int iuperpbin=0; iuperpbin<2; iuperpbin++){
            char name_hist[500];
            sprintf(name_hist, "dUParaMeanProfile3D_%d_%d_%d", ietabin, jetabin, iuperpbin);
            _dUParaMeanProfile3D2EtaUPerp[ietabin][jetabin][iuperpbin] = (TH3D*)file_dUParaFunction->Get(name_hist);
            sprintf(name_hist, "dUParaZeroFraction3D_%d_%d_%d", ietabin, jetabin, iuperpbin);
            _dUParaZeroFraction3D2EtaUPerp[ietabin][jetabin][iuperpbin] = (TH3D*)file_dUParaFunction->Get(name_hist);
          } // iuperp
        } // jetabin
      } // ietabin
      // 2b4
      // in 11 DetEta bins and 10 eEta-detEta bins, and 2 bins in uperp
      for (int ietabin=0; ietabin<11; ietabin++){
        for (int jetabin=0; jetabin<10; jetabin++){
          for (int iuperpbin=0; iuperpbin<2; iuperpbin++){
            char name_hist[500];
            sprintf(name_hist, "dUParaMeanProfile3D_%d_%d_%d", ietabin, jetabin, iuperpbin);
            _dUParaMeanProfile3D2EtaUPerp2[ietabin][jetabin][iuperpbin] = (TH3D*)file_dUParaFunction2->Get(name_hist);
            sprintf(name_hist, "dUParaZeroFraction3D_%d_%d_%d", ietabin, jetabin, iuperpbin);
            _dUParaZeroFraction3D2EtaUPerp2[ietabin][jetabin][iuperpbin] = (TH3D*)file_dUParaFunction2->Get(name_hist);
          } // iuperp
        } // jetabin
      } // ietabin
    }
    else {
      cout<<"   OptionOfUParaCorrOption3 can only be 0 to 7 ." <<endl;
      exit(-1);
    }

    // dUPara Smearing parameters
    if (_OptionOfUParaCorrOption3<=5) {
      // Get Smear dUPara 3D Hist, x: SET, y: UPara, z: dUPara 
      _dUParaSmearHist3D = (TH3D*)file_dUParaFunction->Get("dUParaSmearHist3D");
      // Get Smear dUPara 1D Hist of all events
      _dUParaSmearHist1DAll = (TH1D*)file_dUParaFunction->Get("dUParaSmearHist1DAll");
    
      if (_OptionOfUParaCorrOption3==5) {
        // same parameters as above but for separately for 2b4
        // Get Smear dUPara 3D Hist, x: SET, y: UPara, z: dUPara 
        _dUParaSmearHist3D2 = (TH3D*)file_dUParaFunction2->Get("dUParaSmearHist3D");
        // Get Smear dUPara 1D Hist of all events
        _dUParaSmearHist1DAll2 = (TH1D*)file_dUParaFunction2->Get("dUParaSmearHist1DAll");
      } //

      // Get Smear dUPara 1D Hists in bins of SET and UPara
      double NbinsSET = _dUParaSmearHist3D->GetXaxis()->GetNbins(); 
      double NbinsUPara = _dUParaSmearHist3D->GetYaxis()->GetNbins();    
      for (int iset=0; iset<NbinsSET; iset++){
        for (int iupara=0; iupara<NbinsUPara; iupara++){
          char name_hist[300];
          sprintf(name_hist, "dUParaSmearHist1D_SET%d_UPara%d", iset, iupara);
          _dUParaSmearHist1D[iset][iupara] = (TH1D*)file_dUParaFunction->Get(name_hist);
          double x = _dUParaSmearHist1D[iset][iupara]->GetRandom();
          if (x==0) std::cout << " dUPara Smear Hist " << name_hist << " is Empty." <<  std::endl;
        }
      }
      // same as above just separately for 2b4
      if (_OptionOfUParaCorrOption3==5) {
        // Get Smear dUPara 1D Hists in bins of SET and UPara
        double NbinsSET2 = _dUParaSmearHist3D2->GetXaxis()->GetNbins();
        double NbinsUPara2 = _dUParaSmearHist3D2->GetYaxis()->GetNbins();
        for (int iset=0; iset<NbinsSET2; iset++){
          for (int iupara=0; iupara<NbinsUPara2; iupara++){
            char name_hist[300];
            sprintf(name_hist, "dUParaSmearHist1D_SET%d_UPara%d", iset, iupara);
            _dUParaSmearHist1D2[iset][iupara] = (TH1D*)file_dUParaFunction2->Get(name_hist);
            double x = _dUParaSmearHist1D2[iset][iupara]->GetRandom();
            if (x==0) std::cout << " dUPara Smear Hist " << name_hist << " is Empty." <<  std::endl;
          }
        }
      }
    }// if (_OptionOfUParaCorrOption3<=5) 
    else if (_OptionOfUParaCorrOption3==6||_OptionOfUParaCorrOption3==7){

      // For 5 LumiBins: Get Smear dUPara 3D Hist, x: SET, y: UPara, z: dUPara
      for (int ilumi=0; ilumi<5; ilumi++){
        char name_hist[500];
        sprintf(name_hist, "dUParaSmearHist3DLumi%d", ilumi);
        _dUParaSmearHist3DLumi[ilumi] = (TH3D*)file_dUParaFunction->Get(name_hist);
        sprintf(name_hist, "dUParaSmearHist1DLumi%d", ilumi);
        _dUParaSmearHist1DLumiAll[ilumi] = (TH1D*)file_dUParaFunction->Get(name_hist);
        // Get Smear dUPara 1D Hists in bins of SET and UPara
        double NbinsSET = _dUParaSmearHist3DLumi[ilumi]->GetXaxis()->GetNbins();
        double NbinsUPara = _dUParaSmearHist3DLumi[ilumi]->GetYaxis()->GetNbins();
        for (int iset=0; iset<NbinsSET; iset++){
          for (int iupara=0; iupara<NbinsUPara; iupara++){
            sprintf(name_hist, "dUParaSmearHist1D_Lumi%d_SET%d_UPara%d", ilumi, iset, iupara);
            _dUParaSmearHist1DLumi[ilumi][iset][iupara] = (TH1D*)file_dUParaFunction->Get(name_hist);
            double x = _dUParaSmearHist1DLumi[ilumi][iset][iupara]->GetRandom();
            if (x==0) std::cout << " Empty Smear Hist " << name_hist << std::endl;
          }
        }
      }
      // do it again for run2b4 if option 7
      if(_OptionOfUParaCorrOption3==7){
        // For 5 LumiBins: Get Smear dUPara 3D Hist, x: SET, y: UPara, z: dUPara
        for (int ilumi=0; ilumi<5; ilumi++){
          char name_hist[500];
          sprintf(name_hist, "dUParaSmearHist3DLumi%d", ilumi);
          _dUParaSmearHist3DLumi2[ilumi] = (TH3D*)file_dUParaFunction2->Get(name_hist);
          sprintf(name_hist, "dUParaSmearHist1DLumi%d", ilumi);
          _dUParaSmearHist1DLumiAll2[ilumi] = (TH1D*)file_dUParaFunction2->Get(name_hist);
          // Get Smear dUPara 1D Hists in bins of SET and UPara
          double NbinsSET = _dUParaSmearHist3DLumi2[ilumi]->GetXaxis()->GetNbins();
          double NbinsUPara = _dUParaSmearHist3DLumi2[ilumi]->GetYaxis()->GetNbins();
          for (int iset=0; iset<NbinsSET; iset++){
            for (int iupara=0; iupara<NbinsUPara; iupara++){
              sprintf(name_hist, "dUParaSmearHist1D_Lumi%d_SET%d_UPara%d", ilumi, iset, iupara);
              _dUParaSmearHist1DLumi2[ilumi][iset][iupara] = (TH1D*)file_dUParaFunction2->Get(name_hist);
              double x = _dUParaSmearHist1DLumi2[ilumi][iset][iupara]->GetRandom();
              if (x==0) std::cout << " Empty Smear Hist " << name_hist << std::endl;
            } // iupara
          } // iset
        } // for (int ilumi=0; ilumi<5;
      } //  if(OptionOfUParaCorrOption3==7)
    }
    else {
      cout<<"   OptionOfUParaCorrOption3 can only be 0 to 7 ." <<endl;
      exit(-1);
    } 

    cout << "Finish Reading dUPara Mean and Smear Functions. " << endl; 
  }
  

  _EnergySim_ElecWindowFudge = parm.GetFloat("EnergySim_ElecWindowFudge", 1.);
  _UParaCorrFudge = parm.GetFloat("UParaCorrFudge", 1.);


  /////////////////  Parameters for dUParaEfficiency. //////////////////
  // This is the efficiency of electron ID as a function of dUPara, which is the energy 
  //  flow of underlying events that falls inside the electron window. The electron 
  //  ID sensitively depends on this dUPara. In the UPara Correction, we add a 
  //  dUPara from a library into the electron. When we do this, we apply this 
  //  dUPara Efficiency.
 
  // _dUParaEff_Option == 0
  // The dUParaEfficiency is parameterized as a function of dUPara, and in bins
  //  of Pt of the electron.
  // - For dUPara=0, the efficiencies are given by dUParaEff_Zero_dUPara_W/Z .
  // - For all the rest, the efficienceis is parameterized as: 
  //        eff = par0 + par1*x, where x = dUpara/Pt_elec, 
  //          par0 and par1 are given by dUParaEff_Func_Par0_W/Z and dUParaEff_Func_Par1_W/Z, respectively.
  // - If switch dUParaEff_Smooth_Eff is true, a weighted mean efficiency will be calculated
  //        based on the efficiencies and the mean Pt of the 5 Pt bins, where the mean Pt is given by 
  //          dUParaEff_Mean_Pt_W/Z
  // 

  // _dUParaEff_Option == 1
  // add bins of PhyEta

  // switch 
  _Apply_dUParaEff = parm.GetBool("Apply_dUParaEff", false);
  // dUParaEff option
  _dUParaEff_Option = parm.GetInt("dUParaEff_Option", 0);
  // if use dEPara as reference
  _dUParaEffUsedEPara = parm.GetBool("dUParaEffUsedEPara", false);
  // if use TruePT as reference
  _dUParaEffUseTruePT = parm.GetBool("dUParaEffUseTruePT", false);
  // Parameters for _dUParaEff_Option = 0
  if (_dUParaEff_Option==0){
    // switch smooth efficiency
    _dUParaEff_Smooth_Eff = parm.GetBool("dUParaEff_Smooth_Eff", false);
    // paramters for W
    _dUParaEff_Nbins_W = parm.GetInt("dUParaEff_Nbins_W", 5);
    _dUParaEff_Bin_Min_W = parm.GetVDouble("dUParaEff_Bin_Min_W");
    _dUParaEff_Bin_Max_W = parm.GetVDouble("dUParaEff_Bin_Max_W");
    _dUParaEff_Mean_Pt_W = parm.GetVDouble("dUParaEff_Mean_Pt_W");
    _dUParaEff_Zero_dUPara_W =  parm.GetVDouble("dUParaEff_Zero_dUPara_W");
    _dUParaEff_Func_Par0_W =  parm.GetVDouble("dUParaEff_Func_Par0_W");
    _dUParaEff_Func_Par1_W =  parm.GetVDouble("dUParaEff_Func_Par1_W");
    // paramters for Z
    _dUParaEff_Nbins_Z = parm.GetInt("dUParaEff_Nbins_Z", 7);
    _dUParaEff_Bin_Min_Z = parm.GetVDouble("dUParaEff_Bin_Min_Z");
    _dUParaEff_Bin_Max_Z = parm.GetVDouble("dUParaEff_Bin_Max_Z");
    _dUParaEff_Mean_Pt_Z = parm.GetVDouble("dUParaEff_Mean_Pt_Z");
    _dUParaEff_Zero_dUPara_Z =  parm.GetVDouble("dUParaEff_Zero_dUPara_Z");
    _dUParaEff_Func_Par0_Z =  parm.GetVDouble("dUParaEff_Func_Par0_Z");
    _dUParaEff_Func_Par1_Z =  parm.GetVDouble("dUParaEff_Func_Par1_Z");
  }
  // parameters for _dUParaEff_Option = 1
  else if (_dUParaEff_Option==1) {
    ifstream dUParaEff_ParFile(parm.GetChar("dUParaEff_ParFile"), ifstream::in);
    if(dUParaEff_ParFile.good()){
      // eta bins
      dUParaEff_ParFile >> _dUParaEff_Option1_NEtaBins;
      for (int i=0; i<=_dUParaEff_Option1_NEtaBins; i++) {
        double bin;
        dUParaEff_ParFile >> bin;
        _dUParaEff_Option1_EtaBins.push_back(bin);
      }
      // pt bins
      dUParaEff_ParFile >> _dUParaEff_Option1_NPTBins;
      for (int i=0; i<=_dUParaEff_Option1_NPTBins; i++) {
        double bin;
        dUParaEff_ParFile >> bin;
        _dUParaEff_Option1_PTBins.push_back(bin);
      }

      // pars
      for (int ieta=0; ieta<_dUParaEff_Option1_NEtaBins; ieta++){
        vector<double*> par_ieta;
        for (int ipt=0; ipt<_dUParaEff_Option1_NPTBins; ipt++){
          double meanPT, eff0, effp0, effp1;
          dUParaEff_ParFile >> meanPT >> eff0 >> effp0 >> effp1 ;
          double* par = new double[4];
          par[0] = meanPT;
          par[1] = eff0;
          par[2] = effp0;
          par[3] = effp1;
          par_ieta.push_back(par);
        } // ipt
        _dUParaEff_Option1_Pars.push_back(par_ieta);
      } // ieta

    }
    else {
      cout << " dUParaEff_Option1_ParFile is not valid " << endl;
      abort();
    }

  }
  // parameters for _dUParaEff_Option = 2
  else if (_dUParaEff_Option==2) {
    ifstream dUParaEff_ParFile(parm.GetChar("dUParaEff_ParFile"), ifstream::in);
    if(dUParaEff_ParFile.good()){
      // eta bins
      dUParaEff_ParFile >> _dUParaEff_Option2_NEtaBins;
      for (int i=0; i<=_dUParaEff_Option2_NEtaBins; i++) {
        double bin;
        dUParaEff_ParFile >> bin;
        _dUParaEff_Option2_EtaBins.push_back(bin);
      }
      // pt bins
      dUParaEff_ParFile >> _dUParaEff_Option2_NPTBins;
      for (int i=0; i<=_dUParaEff_Option2_NPTBins; i++) {
        double bin;
        dUParaEff_ParFile >> bin;
        _dUParaEff_Option2_PTBins.push_back(bin);
      }

      // pars
      for (int ieta=0; ieta<_dUParaEff_Option2_NEtaBins; ieta++){
        vector<double*> par_ieta;
        for (int ipt=0; ipt<_dUParaEff_Option2_NPTBins; ipt++){
          double meanPT, eff0, effp0, effp1;
          dUParaEff_ParFile >> meanPT >> eff0 >> effp0 >> effp1 ;
          double* par = new double[4];
          par[0] = meanPT;
          par[1] = eff0;
          par[2] = effp0;
          par[3] = effp1;
          par_ieta.push_back(par);
        } // ipt
        _dUParaEff_Option2_Pars.push_back(par_ieta);
      } // ieta

    }
    else {
      cout << " dUParaEff_ParFile is not valid " << endl;
      abort();
    }

    ifstream dUParaEff_ParFile2(parm.GetChar("dUParaEff_ParFile2"), ifstream::in);
    if(dUParaEff_ParFile2.good()){
      // eta bins
      dUParaEff_ParFile2 >> _dUParaEff_Option2_NEtaBins2;
      for (int i=0; i<=_dUParaEff_Option2_NEtaBins2; i++) {
        double bin;
        dUParaEff_ParFile2 >> bin;
        _dUParaEff_Option2_EtaBins2.push_back(bin);
      }
      // pt bins
      dUParaEff_ParFile2 >> _dUParaEff_Option2_NPTBins2;
      for (int i=0; i<=_dUParaEff_Option2_NPTBins2; i++) {
        double bin;
        dUParaEff_ParFile2 >> bin;
        _dUParaEff_Option2_PTBins2.push_back(bin);
      }

      // pars
      for (int ieta=0; ieta<_dUParaEff_Option2_NEtaBins2; ieta++){
        vector<double*> par_ieta;
        for (int ipt=0; ipt<_dUParaEff_Option2_NPTBins2; ipt++){
          double meanPT, eff0, effp0, effp1;
          dUParaEff_ParFile2 >> meanPT >> eff0 >> effp0 >> effp1 ;
          double* par = new double[4];
          par[0] = meanPT;
          par[1] = eff0;
          par[2] = effp0;
          par[3] = effp1;
          par_ieta.push_back(par);
        } // ipt
        _dUParaEff_Option2_Pars2.push_back(par_ieta);
      } // ieta

    }
    else {
      cout << " dUParaEff_ParFile2 is not valid " << endl;
      abort();
    }

  }
  // parameters for _dUParaEff_Option = 6
  else if (_dUParaEff_Option==6) {
    SetdUParaEffParsModel6UseHists(parm);   
  }
  else {
    cout << "dUParaEff_Option can only be 0, 1, 2, 6" << endl;
    exit(-1); 
  }
  // dUParaEff if options else...


  // option for zero-suppression
  _ZSUPCorrOption = (int)(parm.GetFloat("ZSUPCorrOption", 1));

  // undelrying event contribution (no ZSUP effects on real electron energy measurement included)
  _UParaCorr_CC = parm.GetFloat("UParaCorr_CC", 0.);
  _UParaCorr_EC = parm.GetFloat("UParaCorr_EC", 0.);

  // we can also read uparallel corrections from a histogram
  TString uparacorr_cc_filename(parm.GetChar("UParaCorr_CC_Hist"));
  gROOT->ProcessLine(TString(".x ")+uparacorr_cc_filename);
  _UparaCorr_CC_Hist = (TH1F *)gROOT->FindObject("UParaCorrPerTower"); 

  // uparallel correction dependence on luminosity
  TString uparacorr_lumi_cc_filename(parm.GetChar("UParaCorr_CC_V_Lumi_Hist"));
  gROOT->ProcessLine(TString(".x ")+uparacorr_lumi_cc_filename);
  _UParaCorr_CC_V_Lumi_Hist = (TH1F *)gROOT->FindObject("UParaCorr_V_Lumi"); 

  // uparallel correction dependence on uparallel
  _UParaCorr_CC_V_UPara_Parameters = parm.GetVDouble("UParaCorr_CC_V_UPara_Parameters");

  // ZSUP effect on single energy electrons without MB overlay
  _ZSUP_CC_Elec_NoMBOverlay = parm.GetFloat("ZSUP_CC_Elec_NoMBOverlay", -0.765);

  // delta UParallel dependence on luminosity
  _UParaCorr_CC_V_Lumi_Slope = parm.GetFloat("UParaCorr_CC_V_Lumi_Slope", 0.0025);

  // zero-suppression effects on calorimeter energy measurment and real electron energy
  _Delta_ZSUP_CC = parm.GetFloat("Delta_ZSUP_CC", 0.);
  _Delta_ZSUP_EC = parm.GetFloat("Delta_ZSUP_EC", 0.);
  
  // zero-suppression effects on electron eta
  _ZSUP_CC_V_ElecEta_Parameters = parm.GetVDouble("ZSUP_CC_V_ElecEta_Parameters");

  // real electron energy that is outside of the electron cone
  _ENERGY_OUTCONE_MODEL_Elec_CC = parm.GetInt("ENERGY_OUTCONE_MODEL_Elec_CC", 1);
  _ENERGY_OUTCONE_Elec_CC = parm.GetFloat("ENERGY_OUTCONE_Elec_CC", 0.);
  _ENERGY_OUTCONE_Elec_EC = parm.GetFloat("ENERGY_OUTCONE_Elec_EC", 0.);
  if (_ENERGY_OUTCONE_MODEL_Elec_CC==3 || _ENERGY_OUTCONE_MODEL_Elec_CC==4) {
    TString ENERGY_OUTCONE_JanModel_FileName_Elec_CC(parm.GetChar("ENERGY_OUTCONE_JanModel_FileName_Elec_CC"));
    TFile *fleak = new TFile(ENERGY_OUTCONE_JanModel_FileName_Elec_CC);
    if(fleak->IsZombie()) {
      cout<<"   Please provide "<<ENERGY_OUTCONE_JanModel_FileName_Elec_CC<<endl;
      exit(-1);
    }
    for (int i=0; i<14; i++) {
      TString n;
      n="ETF_";
      n+=i;
      _ENERGY_OUTCONE_JanModel_Elec_CC[i]=(TH1D*)fleak->Get(n);
    }
    _ENERGY_OUTCONE_JanModel_Elec_Fudge_CC = parm.GetFloat("ENERGY_OUTCONE_JanModel_Elec_Fudge_CC", 1.);
    //
    if (_ENERGY_OUTCONE_MODEL_Elec_CC==4) {
      TString ENERGY_OUTCONE_JanModel_FileName_Elec_CCfsr(parm.GetChar("ENERGY_OUTCONE_JanModel_FileName_Elec_CCfsr"));
      TFile *fleak2 = new TFile(ENERGY_OUTCONE_JanModel_FileName_Elec_CCfsr);
      if(fleak2->IsZombie()) {
	cout<<"   Please provide "<<ENERGY_OUTCONE_JanModel_FileName_Elec_CCfsr<<endl;
	exit(-1);
      }
      for (int i=0; i<14; i++) {
	TString n;
	n="ETF_";
	n+=i;
	_ENERGY_OUTCONE_JanModel_Elec_CCfsr[i]=(TH1D*)fleak2->Get(n);
      }
      _ENERGY_OUTCONE_JanModel_Elec_Fudge_CCfsr = parm.GetFloat("ENERGY_OUTCONE_JanModel_Elec_Fudge_CCfsr", 1.);
    }
  }
  if (_ENERGY_OUTCONE_MODEL_Elec_CC == 5) {
    
    eleak_model5_ptbins = parm.GetVDouble("ENERGY_OUTCONE_model5_ptbins");
    eleak_model5_etabins = parm.GetVDouble("ENERGY_OUTCONE_model5_etabins");
    eleak_model5_setbins = parm.GetVDouble("ENERGY_OUTCONE_model5_setbins");
    eleak_model5_Xbins = parm.GetVDouble("ENERGY_OUTCONE_model5_Xbins");
    eleak_model5_interpolate = parm.GetBool("ENERGY_OUTCONE_model5_interpolate");
    eleak_model5_vetoFudge = parm.GetDouble("ENERGY_OUTCONE_model5_vetoFudge");
    eleak_model5_FSRFudge = parm.GetDouble("ENERGY_OUTCONE_model5_FSRFudge");

    TString eleak_model5_fileName = parm.GetChar("ENERGY_OUTCONE_model5_fileName");
    TFile* eleak_model5_file = TFile::Open(eleak_model5_fileName);
    
    TH1D* placeHolder = new TH1D("placeHolder", "", 250, 0., 0.1);
    
    eleak_model5_leakageProbability.resize(eleak_model5_ptbins.size()-1);
    eleak_model5_leakageProbabilityFSR.resize(eleak_model5_ptbins.size()-1);
    for (int i=0; i<eleak_model5_ptbins.size()-1; i++) {      
      eleak_model5_leakageProbability[i] = (TProfile2D*) eleak_model5_file->Get(TString::Format("leakageProbability_%d", i));
      eleak_model5_leakageProbability[i]->SetDirectory(0);
      eleak_model5_leakageProbabilityFSR[i] = (TProfile2D*) eleak_model5_file->Get(TString::Format("leakageProbabilityFSR_%d", i));
      eleak_model5_leakageProbabilityFSR[i]->SetDirectory(0);
    }    
    
    eleak_model5_leakageDistribution.resize(eleak_model5_ptbins.size()-1);
    for (int i=0; i<eleak_model5_ptbins.size()-1; i++) {
      eleak_model5_leakageDistribution[i].resize(eleak_model5_etabins.size()-1);
      for (int j=0; j<eleak_model5_etabins.size()-1; j++) {
	eleak_model5_leakageDistribution[i][j].resize(eleak_model5_setbins.size()-1, placeHolder);
	for (int k=0; k<eleak_model5_setbins.size()-1; k++) {
	  eleak_model5_leakageDistribution[i][j][k] = (TH1D*) eleak_model5_file->Get(TString::Format("leakageDistribution_%d_%d_%d", i, j, k));
	  // Only saves in memory if will use it
	  if (eleak_model5_leakageDistribution[i][j][k]->Integral() > 0.) 
	    eleak_model5_leakageDistribution[i][j][k]->SetDirectory(0);
	  else
	    eleak_model5_leakageDistribution[i][j][k] = 0;
	}
      }
    }
    eleak_model5_leakageDistributionFSR.resize(eleak_model5_ptbins.size()-1);
    for (int i=0; i<eleak_model5_ptbins.size()-1; i++) {
      eleak_model5_leakageDistributionFSR[i].resize(eleak_model5_etabins.size()-1);
      for (int j=0; j<eleak_model5_etabins.size()-1; j++) {
	eleak_model5_leakageDistributionFSR[i][j].resize(eleak_model5_setbins.size()-1);
	for (int k=0; k<eleak_model5_setbins.size()-1; k++) {
	  eleak_model5_leakageDistributionFSR[i][j][k].resize(eleak_model5_Xbins.size()-1, placeHolder);
	  for (int m=0; m<eleak_model5_Xbins.size()-1; m++) {
	    eleak_model5_leakageDistributionFSR[i][j][k][m] = (TH1D*) eleak_model5_file->Get(TString::Format("leakageDistributionFSR_%d_%d_%d_%d", i, j, k, m));
	    if (eleak_model5_leakageDistributionFSR[i][j][k][m]->Integral() > 0.)
	      eleak_model5_leakageDistributionFSR[i][j][k][m]->SetDirectory(0);
	    else 
	      eleak_model5_leakageDistributionFSR[i][j][k][m]= 0;
	  }
	}
      }
    }        
    eleak_model5_file->Close();
  }
  
  // smear track pT
  _SmearTrkpT = parm.GetBool("SmearTrkpT", kFALSE);

  // read in parameters used for smearing electron track pT
  _TrackRadLength_CC = parm.GetFloat("TrackRadLength_CC",0.0265);
  _A_CC = parm.GetFloat("A_CC", 1.);
  _B_CC = parm.GetFloat("B_CC", 0.0);
  _C_CC = parm.GetFloat("C_CC", 0.15);
  _TrackRadLength_EC = parm.GetFloat("TrackRadLength_EC",0.0265);
  _A_EC = parm.GetFloat("A_EC", 1.);
  _B_EC = parm.GetFloat("B_EC", 0.0);
  _C_EC = parm.GetFloat("C_EC", 0.15);
  _bremSim = parm.GetBool("bremSim", kFALSE);

  //read electron cluster phi shift within module
  _ApplyPhiModCorrection = parm.GetBool("PhiModCorrection");
  _ApplyPhiModEfficiency = parm.GetBool("PhiModEfficiency");
  _ApplyTrkPhiModEfficiency = parm.GetBool("TrkPhiModEfficiency");
  // phi module shift file
  TString phimodshift_filename(parm.GetChar("phimodshift_file"));
  gROOT->ProcessLine(TString(".x ")+phimodshift_filename);
  _hPhiModShift = (TH2F *)gROOT->FindObject("presel_deltaphi_scatter_CC");
  
  //Create phimod shift slices ahead of time
  Int_t nproj = _hPhiModShift->GetXaxis()->GetNbins();
  _hPhiModShiftSlice = new TH1D*[nproj+1];
  char tbuf[128];
  for(Int_t k=1;k<=nproj;k++){
  sprintf(tbuf,"hPhiModSlice[%d]",k);
   _hPhiModShiftSlice[k] = _hPhiModShift->ProjectionY(tbuf, k, k);
  }

  // get phi crack efficiency
  TString phicrackeff_filename(parm.GetChar("phicrackeff_file"));
  gROOT->ProcessLine(TString(".x ")+phicrackeff_filename);
  _hPhiCrackEff = (TH1F *)gROOT->FindObject("hPhiCrackEff");  

  cout<<"Finished EMSmear initialization"<<endl;
}

// smear a vector of EM objects
vector<PMCSEMObj> EMSmear::SmearEMObjs(vector<PMCSEMObj>& GenEMObjs, TRandom3 *dummy) {
  //Now, change to run2b3 or run2b4 energy scale and offset values depending on run number

  if(_run3bool && _run4bool){
    if(_runNumber < _middlerunnumber){//This is set in parameters file.  run2b3 is below ~263000.
      _CCscale_lumidep_scale = _CCscale_lumidep_scale_run3;
      _CCscale_lumidep_offset = _CCscale_lumidep_offset_run3;
    }else{
      _CCscale_lumidep_scale = _CCscale_lumidep_scale_run4;
      _CCscale_lumidep_offset = _CCscale_lumidep_offset_run4;
    }
  }else if(_run3bool && !_run4bool){
    _CCscale_lumidep_scale = _CCscale_lumidep_scale_run3;
    _CCscale_lumidep_offset = _CCscale_lumidep_offset_run3;
  }else if(!_run3bool && _run4bool){
    _CCscale_lumidep_scale = _CCscale_lumidep_scale_run4;
    _CCscale_lumidep_offset = _CCscale_lumidep_offset_run4;
  }else {
    cout<<"EMSmear: At least one of Run3 and Run4 in parameters file must be set to true"<<endl; 
    exit(0);
  }

  vector<PMCSEMObj> SmearedEMObjs;
  for(int iem=0; iem<GenEMObjs.size(); iem++) {
      // if needed, use Lumi and/or UPara depending _scale_CC and _offset_CC
      if ((_doCCscale_lumidep || _doCCscale_uparadep)&&GenEMObjs[iem].ppt()>15.){
        TVector2 genelecVec(GenEMObjs[iem].ppx(), GenEMObjs[iem].ppy());
        double upara = _RecoilVec * genelecVec.Unit();
        SetScaleOffsetDepCC(_luminosity, upara); 
      }
      PMCSEMObj smear = SmearEMObj(GenEMObjs[iem], dummy);
      SmearedEMObjs.push_back(smear);
      // change back to original _scale_CC and _offset_CC once finished smearing
      if (_doCCscale_lumidep || _doCCscale_uparadep){
        ResetScaleOffsetCC();
      }
  }

  if (GenEMObjs.size() < SmearedEMObjs.size()){
    std::cout << " we lost an object" << std::endl;
  }
  return SmearedEMObjs;
}

// smear one single EM object including energies below electron window
PMCSEMObj EMSmear::SmearEMObj(PMCSEMObj& part_gen, TRandom3 *dummy) {
  PMCSEMObj part_smear = part_gen;
  part_smear.SetTrueE(part_gen.pE());
  part_smear.SetTruePt(part_gen.ppt());
  part_smear.SetTrueEta(part_gen.peta());

  // debug: Hengne
  //if (_scale_CC!=_scale_CC0 ){ 
  //  if ( (!_doCCscale_lumidep) || 
  //       (_doCCscale_lumidep && 
  //        (_scale_CC!=_CCscale_lumidep_scale[0] &&
  //         _scale_CC!=_CCscale_lumidep_scale[1] &&
  //         _scale_CC!=_CCscale_lumidep_scale[2] &&
  //         _scale_CC!=_CCscale_lumidep_scale[3]
  //        )
  //       )  
  //     )  
  //  {
  //    std::cout << "Hengne: _scale_CC=" << _scale_CC << "; _offset_CC=" << _offset_CC << std::endl;
  //  }
  //}

  // smear EMObject in different detector eta regions
  if(fabs(part_smear.deteta())<1.3) {
    // if we want to simulate electron track pT
    if(_SmearTrkpT) SmearTrkpT(part_smear, dummy, _A_CC, _B_CC, _C_CC, _TrackRadLength_CC);
    part_smear = Smear(part_smear, _etares_phy_CC, _phires_phy_CC, 
		       _etares_det_CC, _phires_det_CC, 
		       _scale_CC, _offset_CC, 
		       _Energy_Nonlinearity_CC, _ZElec_AvePt_CC,
		       _sampling_CC, _constant_CC, _noise_CC, 
                       _Sampling_CC1, _Sampling_CC2,_Sampling_CCexp0, _Sampling_CCexp1, _Sampling_CCexp2, true, dummy);


    // if we want to simulate electron energy response vs track phimod
    // only for CC electrons
   
    if(_simulate_elecResponse_V_TrkPhiMod) {
      double new_energy = part_smear.pE();
      double eta = part_smear.peta();
      double phi = part_smear.pphi();
      SimulateEnergyResponseVsTrackPhiMod(part_smear, new_energy);
      part_smear.SetEnergyEtaPhi(new_energy, eta, phi);
    }
  
  } else {
    if(_SmearTrkpT) SmearTrkpT(part_smear, dummy, _A_EC, _B_EC, _C_EC, _TrackRadLength_EC);
    part_smear = Smear(part_smear, _etares_phy_EC, _phires_phy_EC, 
       		       _etares_det_EC, _phires_det_EC, 
      		       _scale_EC, _offset_EC, 
		       _Energy_Nonlinearity_EC, _ZElec_AvePt_EC,
		       _sampling_EC, _constant_EC, _noise_EC, 
                       _Sampling_EC1, _Sampling_EC2, _Sampling_ECexp0, _Sampling_ECexp1, _Sampling_ECexp2, false, dummy);
    if(_SmearTrkpT) SmearTrkpT(part_smear, dummy, _A_EC, _B_EC, _C_EC, _TrackRadLength_EC);
    
  } 
  
  return part_smear;
}

//
// smear EM object including energies below electron window
//
PMCSEMObj EMSmear::Smear(PMCSEMObj& part_gen,
			 double etares_phy, double phires_phy, 
			 double etares_det, double phires_det,
			 double scale, double offset,
			 double nonlinearity, double zelec_avept,
			 double sampling, double constant,
			 double noise, double sampling1, double sampling2, 
                         double sampling_exp0, double sampling_exp1, double sampling_exp2, 
			 bool needCBtailAndPeakShift,
			 TRandom3 *dummy) {
  
  double energy_gen = part_gen.pE();
  double eta_gen = part_gen.peta();
  double phi_gen = part_gen.pphi();
  double deteta_gen = part_gen.deteta();
  double detphi_gen = part_gen.detphi();
  double lumi = part_gen.getLumi();
  double upara = part_gen.getUPara();
  double rawpTUnderElecWindow=0., UParaCorr=0., Delta_ZSUP=0., EnergyLeakage=0.;
  double energy_smeared=0., phyeta_smeared=0., phyphi_smeared=0., deteta_smeared=0., detphi_smeared=0.;
  double id = part_gen.ppid();
  double vtxz = part_gen.getvtxz();
  double energy_gen_wfsr = part_gen.GetEnergyGenWFSR();

  // check whether this is a real electron
  // only do energy below electron window simulation for real electron, not for photon
  bool IsElectron = (abs(id)==11 || (abs(id)==12));

  // smear electron energy, eta and phi
  // no simulation of energies below electron window
  bool lost=false;
  Smear(energy_gen, energy_gen_wfsr, eta_gen, phi_gen, deteta_gen, detphi_gen,
	etares_phy, phires_phy, etares_det, phires_det,
	scale, offset, nonlinearity, zelec_avept,
	sampling, constant, noise, sampling1, sampling2, 
	sampling_exp0, sampling_exp1, sampling_exp2, needCBtailAndPeakShift,
	dummy, phyeta_smeared, phyphi_smeared,
	deteta_smeared, detphi_smeared, energy_smeared, lost, id, vtxz);  

  //
  // set smeared energy, eta, phi, detector eta, detector phi
  //
  PMCSEMObj part_smear = part_gen;
  part_smear.SetTrueE(part_gen.pE());
  if (lost) part_smear.SetLostInAcrack();
  bool useTrkPt = true;
  if ( _SmearEtaPhiHengne ) useTrkPt = false;
  part_smear.SetEnergyEtaPhi(energy_smeared, phyeta_smeared, phyphi_smeared,_ApplyTrkPhiModEfficiency, useTrkPt);
  part_smear.SetDetEtaDetPhi(deteta_smeared, detphi_smeared);

  // simulate energies below electron window
  // modify the scaled and smeared electron energy 
  // underlying event corrections and ZSUP effects were set in the SmearEnergyUnderElecWindow function
  if(_EnergySim_ElecWindow && IsElectron)  SmearEnergyUnderElecWindow(part_smear, dummy);

  // Apply PhiMod energy response correction after Electron Window Energy correction
  if (_SmearEtaPhiHengne && _ApplyPhiModErespCorrHengne){
    PhiModErespCorrHengne(part_smear);
  }

   
  if (_makeCheckSmearingPlots) fillSmearHistograms(part_gen,part_smear);

  return part_smear;
}

// this is the basic function for smearing electron energy, eta/phi and detector eta/phi
// But this will not do energies below electron window simulation
void EMSmear::Smear(double energy_gen, double energy_gen_wfsr, double eta_gen, double phi_gen,
		    double deteta_gen, double detphi_gen,
		    double etares_phy, double phires_phy, 
		    double etares_det, double phires_det,
		    double scale, double offset,
		    double nonlinearity, double zelec_avept,
		    double sampling, double constant,
		    double noise, double sampling1, double sampling2, 
		    double sampling_exp0, double sampling_exp1, double sampling_exp2, 
		    bool needCBtailAndPeakShift,
		    TRandom3 *dummy,
		    double &phyeta_smeared, double &phyphi_smeared,
		    double &deteta_smeared, double &detphi_smeared,
		    double &energy_smeared, bool &lost, double id, double vtxz) { 
  //  
  double theta_gen = 2.*atan(exp(-eta_gen));

  // track phi at em3, to be used with _SmearEtaPhiHengne 
  double track_phi_em3(phi_gen);
  if (_SmearEtaPhiHengne){
    // Smear Phys Phi at first, DetPhi will be smeared after Phys Phi smearing 
    //   and energy smearing. 
    SmearPhysEtaPhiHengne(eta_gen, phi_gen, etares_phy, phires_phy, dummy, 
                          phyeta_smeared, phyphi_smeared, id);
  }
  else {  
    SmearDetEtaPhi(deteta_gen, detphi_gen, etares_det, phires_det, dummy, 
                   deteta_smeared, detphi_smeared, lost, id);
  
    SmearPhysEtaPhi(eta_gen, phi_gen, etares_phy, phires_phy, dummy, 
                    phyeta_smeared, phyphi_smeared);
  }

  // treat electron and photon response differently
  if((abs(id)==22) && (energy_gen*sin(theta_gen)<15.)) 
    SmearPhotonEnergy(energy_gen, eta_gen, dummy, energy_smeared);
  else {
    // apply energy scale and offset, detector resolution
    double phimod_gen=fmod(detphi_gen*16/TMath::Pi(),1.0);
    SmearEnergy(energy_gen, eta_gen, phi_gen, phimod_gen, deteta_gen, scale, offset, nonlinearity, zelec_avept, 
		sampling, constant, noise, sampling1, sampling2, sampling_exp0, sampling_exp1, sampling_exp2, needCBtailAndPeakShift,
		dummy, energy_smeared);
  }


  // Apply Phimod Response correction and smear the DetPhi after Energy smearing
  if(_SmearEtaPhiHengne){
    // extrapolate Phys Phi (assume it is track phi) to EM3, 
    //  using smeared Pt
    double pt_smeared = energy_smeared * sin(2.0*atan(exp(-phyeta_smeared)));
    if (abs(id)!=22) {
      // electron or positron
      bool ispositron = ((int(id)==-11) || (int(id)==-12));
      track_phi_em3 = PCalTools::Phi_Magnetic_Field(vtxz, phyeta_smeared, phyphi_smeared,
                                                    pt_smeared, ispositron);
    }
    else {
      // photon
      track_phi_em3 = phyphi_smeared;
    }
    // Simple PhiMod Em response correction: 1D histogram
    if(_Use_Simple_EMrespCorr_vs_PhiMod){ 
      SimpleEMRespCorrVsPhiMod(energy_gen, energy_smeared, track_phi_em3);
    }
    // 
    SmearDetEtaPhiHengne(deteta_gen, phyphi_smeared, etares_det, phires_det, dummy,
                   deteta_smeared, detphi_smeared);    

    // apply PhiMod Eff Hengne
    if (_ApplyPhiModEffHengne){
      PhiModEffHengne(energy_gen_wfsr, track_phi_em3, dummy,detphi_smeared, lost );
    }
  }

}

void EMSmear::SimulateEnergyResponseVsTrackPhiMod(PMCSEMObj part_smear, double& new_energy) {
  double elec_trkPhi = part_smear.pphi();
  double elec_trkPhiMod = fmod(elec_trkPhi*16./TMath::Pi(), 1.0);

  Int_t bin = _elecEOverP_V_TrkPhiMod->FindBin(elec_trkPhiMod);

  // average response 1.07 for data
  // 1.0514 for full MC
  double response_EOverP = _elecEOverP_V_TrkPhiMod->GetBinContent(bin)/_average_EOverP;
  double E = part_smear.pE();
  double eta = part_smear.peta();
  double phi = part_smear.pphi();

  // only change the energy, not eta and phi
  new_energy = response_EOverP*E;
}

// smear photon energy, no resolution yet, just response
// since response of the photons in the recoil system already applied in pmcsana::fixEMBlock
// here I do not need to smear it again
// may need to consider the case whether the photon can be reconstructed as a separate EM cluster ???
void EMSmear::SmearPhotonEnergy(double energy_gen, double eta_gen, TRandom3 *dummy, double& energy_smeared) {
  energy_smeared = energy_gen;
}

// using scale, offset, sampling, etc defined by EMSmear class
// But this will not do energies below electron window simulation
void EMSmear::Smear(double energy_gen, double eta_gen, double phi_gen,
		    double deteta_gen, double detphi_gen, TRandom3 *dummy,
		    double &phyeta_smeared, double &phyphi_smeared,
		    double &deteta_smeared, double &detphi_smeared,
		    double &energy_smeared, bool &lost, double id, double vtxz) {  

  if(fabs(deteta_gen)<1.3) 
    Smear(energy_gen, energy_gen, eta_gen, phi_gen, deteta_gen, detphi_gen,
	  _etares_phy_CC, _phires_phy_CC, _etares_det_CC, _phires_det_CC,
	  _scale_CC, _offset_CC, _Energy_Nonlinearity_CC, _ZElec_AvePt_CC,
	  _sampling_CC, _constant_CC, _noise_CC, _Sampling_CC1, _Sampling_CC2, 
	  _Sampling_CCexp0, _Sampling_CCexp1, _Sampling_CCexp2, true,
	  dummy, phyeta_smeared, phyphi_smeared,
	  deteta_smeared, detphi_smeared, energy_smeared, lost, id, vtxz);
  else 
    Smear(energy_gen, energy_gen, eta_gen, phi_gen, deteta_gen, detphi_gen,
	  _etares_phy_EC, _phires_phy_EC, _etares_det_EC, _phires_det_EC,
	  _scale_EC, _offset_EC, _Energy_Nonlinearity_EC, _ZElec_AvePt_EC,
	  _sampling_EC, _constant_EC, _noise_EC, _Sampling_EC1, _Sampling_EC2, 
	  _Sampling_ECexp0, _Sampling_ECexp1, _Sampling_ECexp2, false,
	  dummy, phyeta_smeared, phyphi_smeared,
	  deteta_smeared, detphi_smeared, energy_smeared, lost, id, vtxz);
}

//
// bremsstrahlung simulation
//
void EMSmear::SmearTrkpT(PMCSEMObj& part_gen, TRandom3 *dummy, double &A, double &B, double &C, double &radlength) {
  
  double trkpT_brem = part_gen.trkpT();
  double pT_Smear = trkpT_brem;
  double theta = part_gen.theta();
  double BremFraction =1;
  double proba_total=0.;

  // only smear track pT if trkpT>1 GeV
  // I do not want to smear photon pT since for photons, track pT set to 0
  //if (sin(theta) > 0.)
  //  radlength = radlength/sin(theta);
  //else{
  //  std::cerr << "sin(theta) == 0" << std::endl;
  //  abort();
  // }
  if(trkpT_brem > 1.)  SmearTrkpT(trkpT_brem, dummy, pT_Smear,A, B,C, radlength, BremFraction, proba_total);
  
  // return smeared electron pT
  part_gen.SetBremFrac(BremFraction);
  part_gen.SetTrkpT( pT_Smear );

}

void EMSmear::SmearTrkpT(double trkpT_brem, TRandom3 *dummy, double& pT_Smear, double &A, double &B, double &C, double &radlength, double &BremFraction, double &proba_total, bool dobrem, double externalrndm, double externalrndm2[10]) {
  double nobrem = trkpT_brem;
  if(_bremSim && dobrem) { 
    //setup material simulation parameters
    double radiation_length = radlength;
    //double radiation_length = radlength/5.; 
    // int bin_radiation_length = 100;
    int bin_radiation_length = 10;
    double y_min = 0.0005;
    int bin_y = 100;
    //double k = 0.03;
    double k = 0.;
    // add bremsstrahlung simulation, electron will travel through SMT + CFT layers
    double elec_momentum = 1.;
    
    for(int i=0; i<bin_radiation_length; i++) {
      double proba[100];
      double elec_momentum_fraction;
      // double proba_total;
      if (externalrndm2)
	wz_utils::brem_simulation(radiation_length, y_min, bin_y, k, proba, 
				  proba_total, elec_momentum_fraction, dummy, externalrndm2[i]);
      else
	wz_utils::brem_simulation(radiation_length, y_min, bin_y, k, proba, 
				  proba_total, elec_momentum_fraction, dummy, 0.);
      elec_momentum = elec_momentum * elec_momentum_fraction;
    } //travel through materials
    //   std::cout << "Elec Momentum Fraction Final: " <<  elec_momentum << std::endl;
    trkpT_brem = trkpT_brem * elec_momentum;
  } //brem simulation
  
//   std::cout<< "SmearTrkPt after brem level : " <<  trkpT_brem << std::endl;
  if (dobrem){
    BremFraction =  1. - ( trkpT_brem / nobrem);
    
  }
  
  //Junjie's RunIIa method
  // track momentum simulation
  //  double reso_trk = sqrt(A*A*trkpT_brem*trkpT_brem + B*B);
  //double InvpT_Smear = 1/(C * trkpT_brem);      
  // double InvpT_Smear = 1/(trkpT_brem);
  //pT_Smear = 1/(InvpT_Smear*(1+dummy->Gaus(0., 1.)*reso_trk));     
  
  //RunIIb method
  
  double reso_trk = (abs(A) * 1./trkpT_brem + abs(B));
  //   //   //double reso_trk = sqrt(A*A*trkpT_brem*trkpT_brem + B*B);
  double InvpT_Smear = 1/(C*trkpT_brem);
  if (externalrndm)
    pT_Smear = 1/(InvpT_Smear*(1+externalrndm*reso_trk));
  else
    pT_Smear = 1/(InvpT_Smear*(1+dummy->Gaus(0., 1.)*reso_trk));
  //  std::cout<< "SmearTrkPt after after full smear : " << pT_Smear  << std::endl;
}

// simulate energies under electron window (only used for CC region)
// N towers will have true underlying event contribution before zsup correction
// 25 - N towers will have underlying event contribution after zsup correction
// then zsup will suppress real electron energy
//
// After I have corrected pT, I will modify electron energy
//
int EMSmear::SmearEnergyUnderElecWindow(PMCSEMObj& part, TRandom3* dummy, bool isW, Double_t *extrndm, Double_t *extrndm_duparaeff) {
  double pE_raw = part.pE();
  double eta_raw = part.peta();
  double deteta_raw = part.deteta();
  double phi_raw = part.pphi();
  double detphi_raw = part.detphi();
  double lumi = part.getLumi();
  double upara = part.getUPara();
  double uperp = part.getUPerp();
  double set = part.getScalarEt();

  // only used when _EnergySim_ElecWindowOption = 0
  double energy_after_ElecSim_ElecWindow=0., rawpTUnderElecWindow=0.;
  double UParaCorr=0., Delta_ZSUP=0., EnergyLeakage=0.;

  // energy difference between single energy electron with and without ZB overlay
  // only used when _EnergySim_ElecWindowOption = 1
  double energyDiffElecWithWithoutZBOverlay = 0.; 
  
  double theta = 2.*atan(exp(-eta_raw));
  double pT_raw = pE_raw*sin(theta);
  double truePT = part.getTrueE()/cosh(eta_raw);

  bool InCC = (fabs(deteta_raw)<1.1);

  ////////////////////////////////////////////////////////
  //                 Run Ia method
  //
  // we are really using exactly 13 towers per EM cluster (cone size R=0.2)
  //  double towers_remain = 13 - _NumTowers_EMCluster;
  
  // (1) all 13 towers will have raw energy deposited from underlying events, pileup and electronics noise
  // (2) (13-_NumTowers_EMCluster) will have small energy deposited, thus suffering from zero-suppression effects
  // (3) true energy energy will also be zero-suppressed
  //   rawpTUnderElecWindow = 13 * _UE_ElecWindow_true + towers_remain * _ZSUP_UE + _ZSUP_Elec;

  // apply the same EM energy corrections here as in EMReco
  // pT after energies under electron window correction
  // pT_new = pT_raw + rawpTUnderElecWindow;
  //
  //         End of Run Ia method
  /////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  //                 Run Ib method
  //
  if(InCC) {      

    // if UParaCorrOption==0, use average value
    // if UParaCorrOption==1, read uparallel correction PER TOWER from histogram
    //    need to do parameterization of luminosity and uparallel
    //    UParaCorr(upara, L) = UParaCorr - <UParaCorr> + <UParaCorr(upara, L=0)> + alpha * L
    //    see talk on 12/11/2006 W mass meeting (slide 7)
    // if UParaCorrOption = 2 will read the average 13 tower Et distribution for different luminosity and uparallel bins  
    //    from a root file defined by UParaCorr_13towers_root_filename
    // if UParaCorrOption = 3 will Model the Mean of dUPara and Smear of dUPara separately:

    if(_UParaCorrOption==0) UParaCorr = _UParaCorr_CC;
    else if(_UParaCorrOption==1){ 
       // read uparallel correction from histogram
       UParaCorr = _UparaCorr_CC_Hist->GetRandom();  

       // check luminosity dependence
       // int lumi_bin = _UParaCorr_CC_V_Lumi_Hist->FindBin(lumi);
       // double average_UParaCorr_upara_lumi = _UParaCorr_CC_V_Lumi_Hist->GetBinContent(lumi_bin);

       // Matt pointed out to me that we should subtract the overall mean value, not the mean value for different luminosity bins
       // so I commented out the previous two lines and add the following line
       double average_UParaCorr_upara_lumi = _UparaCorr_CC_Hist->GetMean();

       // check uparallel dependence, corrected back to zero luminosity
       if(upara>10.) upara = 10.;  // the parameterization only works for |upara|<10 GeV, and will assume it is constant for upara>10. GeV
       if(upara<-10.) upara = -10.;  // the parameterization only works for |upara|<10 GeV, and will assume it is constant for upara><-10. GeV
       double average_UParaCorr_lumi_0 = _UParaCorr_CC_V_UPara_Parameters[0] +  
                                         _UParaCorr_CC_V_UPara_Parameters[1]/10.*upara +
                                         _UParaCorr_CC_V_UPara_Parameters[2]/100.*upara*upara + 
                                         _UParaCorr_CC_V_UPara_Parameters[3]/1000.*upara*upara*upara + 
                                         _UParaCorr_CC_V_UPara_Parameters[4]/10000.*upara*upara*upara*upara;

       UParaCorr -= average_UParaCorr_upara_lumi; 
       UParaCorr += _UParaCorr_CC_V_Lumi_Slope * lumi;   // luminosity dependence
       UParaCorr += average_UParaCorr_lumi_0;       // uparallel corrections dependece on uparallel itself for zero luminosity

      // needs to x13 towers to get correction for each electron
      UParaCorr = 13 * UParaCorr;
    } 
    else if (_UParaCorrOption==2) { 
      // read uparallel correction from 169 histograms with 13 luminosity bins and 13 uparallel bins
      // divided into instantaneous luminosity bins
      int InstLumiBin = -1;
      if(lumi<0.225) InstLumiBin = 0;
      else if(lumi<0.45) InstLumiBin = 1;
      else if(lumi<0.6) InstLumiBin = 2;
      else if(lumi<0.75) InstLumiBin = 3;
      else if(lumi<0.9) InstLumiBin = 4;
      else if(lumi<1.075) InstLumiBin = 5;
      else if(lumi<1.3) InstLumiBin = 6;
      else if(lumi<1.5) InstLumiBin = 7;
      else if(lumi<1.8) InstLumiBin = 8;
      else if(lumi<2.) InstLumiBin = 9;
      else if(lumi<2.5) InstLumiBin = 10;
      else if(lumi<3.) InstLumiBin = 11;
      else InstLumiBin = 12;
      if (_UParaCorrRunIIb){
	if(lumi<1.075) InstLumiBin = 0;
	else if(lumi<1.8) InstLumiBin = 1;
	else if(lumi<2.5) InstLumiBin = 2;
	else if(lumi<3.5) InstLumiBin = 3;
	else InstLumiBin = 4;
        //if(lumi<0.225) InstLumiBin = 0;
        //else if(lumi<0.45) InstLumiBin = 1;
        //else if(lumi<0.6) InstLumiBin = 2;
        //else if(lumi<0.75) InstLumiBin = 3;
        //else if(lumi<0.9) InstLumiBin = 4;
	//else if(lumi<1.075) InstLumiBin = 5;
	//else if(lumi<1.3) InstLumiBin = 6;
	//else if(lumi<1.5) InstLumiBin = 7;
	//else if(lumi<1.8) InstLumiBin = 8;
	//else if(lumi<2.) InstLumiBin = 9;
	//else if(lumi<2.5) InstLumiBin = 10;
	//else if(lumi<3.) InstLumiBin = 11;
	//else if(lumi<3.5) InstLumiBin = 12;
	//else if(lumi<4.) InstLumiBin = 13;
	//else if(lumi<4.5) InstLumiBin = 14;
	//else if(lumi<5.5) InstLumiBin = 15;
	//else if(lumi<6.) InstLumiBin = 16;
	//else if(lumi<6.5) InstLumiBin = 17;
	//else if(lumi<7.) InstLumiBin = 18;
	//else if(lumi<7.5) InstLumiBin = 19;
	//else if(lumi<8.) InstLumiBin = 20;
	//else InstLumiBin = 21;
	
      }
      // divided into uparallel bins
      int UParaBin = -1;
      if(upara<-5.) UParaBin = 0;
      else if(upara<-1.5) UParaBin = 1;
      else if(upara<1.5) UParaBin = 2;
      else if(upara<3.) UParaBin = 3;
      else UParaBin = 4;
      //if(upara<-15.) UParaBin = 0;
      //else if(upara<-10.) UParaBin = 1;
      //else if(upara<-5.) UParaBin = 2;
      //else if(upara<-3.) UParaBin = 3;
      //else if(upara<-1.5) UParaBin = 4;
      //else if(upara<-0.25) UParaBin = 5;
      //else if(upara<0.25) UParaBin = 6;
      //else if(upara<1.5) UParaBin = 7;
      //else if(upara<3.) UParaBin = 8;
      //else if(upara<5.) UParaBin = 9;
      //else if(upara<10.) UParaBin = 10;
      //else if(upara<15.) UParaBin = 11;
      //else UParaBin = 12;
      
      // avoid empty histograms
      if(_UParaCorrRunIIb){
        // if the histogram is empty, first try the one near max Instlumi bin for the given UPara bin
        if (_hEt_ThirteenTowers[InstLumiBin][UParaBin]->Integral() ==0.){
          for (int ilumi=1; ilumi<abs(InstLumiBin-2); ilumi++){
            InstLumiBin = InstLumiBin - ilumi*(InstLumiBin-2)/abs(InstLumiBin-2);
            if (_hEt_ThirteenTowers[InstLumiBin][UParaBin]->Integral() >0.){ 
              break;
            }
          } 
	}
        // if for the given UPara bin, the max InstLumi bin is also empty, try the one near the max UPara bin
        if (_hEt_ThirteenTowers[InstLumiBin][UParaBin]->Integral() ==0.){
          for (int iupara=1; iupara<abs(UParaBin-2); iupara++){
            UParaBin = UParaBin - iupara*(UParaBin-2)/abs(UParaBin-2);
            if (_hEt_ThirteenTowers[InstLumiBin][UParaBin]->Integral() >0.){   
              break;
            }
          }
        }
        // if the max Instlumi and max UPara bin is also empty, we can imply the UParaCorr Library 
        // is not properly prepared. Let's abort!
        if (_hEt_ThirteenTowers[InstLumiBin][UParaBin]->Integral() ==0.){
           cout << "-- EMSmear:: Please check the UParaCorr ROOT file, all histograms are empty! " << endl;
           abort();
        }
      }

      // apply dUParaEff: see beginning for description.
      if (_Apply_dUParaEff){ 
        double duparaeff = 0; 
        int duparaeff_ntimes = 0;

        if (extrndm){
          UParaCorr = ((PMCSTH1*)(((_hEt_ThirteenTowers[InstLumiBin][UParaBin]) )))->GetRandom(extrndm[0]);
          // the first bin, 100% dUPara is 0
          if (UParaCorr<=1e-2) UParaCorr=0;
          duparaeff = Get_dUParaEff(UParaCorr, pT_raw, isW);
          // protection agains negtive Pt
          if (pT_raw<0.) duparaeff = 1.;

          // if fail, return false
          if (dummy->Rndm()>duparaeff) {
            return false;
          }
        } 
        else while (dummy->Rndm()>duparaeff) {
          duparaeff_ntimes++;
          UParaCorr = _hEt_ThirteenTowers[InstLumiBin][UParaBin]->GetRandom();
          // the first bin, 100% dUPara is 0
          if (UParaCorr<=1e-2) UParaCorr=0;
          // get duparaeff
          duparaeff = Get_dUParaEff(UParaCorr, pT_raw, isW);
          if (pT_raw<0.) {
            duparaeff = 1.;
            //UParaCorr = 0.;
          }
        } // while dummy-> ...

        // debug
        //std::cout << " ---- Hengne: UParaCorr=" << UParaCorr << "; duparaeff=" << duparaeff << "; duparaeff_ntimes=" << duparaeff_ntimes << std::endl;
      }
      else {
        if (!extrndm){
          UParaCorr = _hEt_ThirteenTowers[InstLumiBin][UParaBin]->GetRandom();
        }
        else{
          UParaCorr = ((PMCSTH1*)(((_hEt_ThirteenTowers[InstLumiBin][UParaBin]) )))->GetRandom(extrndm[0]);
        }
        // the first bin, 100% dUPara is 0
        if (UParaCorr<=1e-2) UParaCorr=0;
      } // if (_Apply_dUParaEff) ... else ...
    }
    else if (_UParaCorrOption==3){  
      // - method added on Jan. 20, 2011
      // Model the Mean of dUPara and Smear of dUPara separately:
      //  - Mean of dUPara: modeling the mean of dUPara as a smooth 2D function of SET and UPara.
      //  - Smear of dUpara: dUPara histograms in bins of SET and UPara.
      // - updated on Feb. 14, 2011:
      // if OptionOfUParaCorrOption3 = 2 : 
      //   - Modeling separately for (1) dUPara=0 and (2) dUPara>0:
      //    - The fraction of dUPara=0 is a 3D function of SET, UPara and Lumi,
      //    - For dUPara>0, the mean of dUPara is modeled as a 3D function of SET, UPara and Lumi; 
      //        the smear of dUPara is still as a 2D function of SET and UPara

      /////////////////////
      // (1) Mean and ZeroFraction of dUPara
      double dUParaMean = 0;
      double dUParaZeroFrac = 1.;

      // get dependence binning
      double eeta = eta_raw;
      double deteta = deteta_raw;

      // _OptionOfUParaCorrOption3==3 
      int etabin = -1;
      if (eeta<-0.9) etabin = 1;
      else if (eeta<-0.7) etabin = 1;
      else if (eeta<-0.5) etabin = 2;
      else if (eeta<-0.3) etabin = 3;
      else if (eeta<-0.1) etabin = 4;
      else if (eeta<0.1) etabin = 5;
      else if (eeta<0.3) etabin = 6;
      else if (eeta<0.5) etabin = 7;
      else if (eeta<0.7) etabin = 8;
      else if (eeta<0.9) etabin = 9;
      else etabin = 10;
      

      // _OptionOfUParaCorrOption3==4, 5, 6 and 7
      int ietabin = -1;
      int jetabin = -1;
      if (deteta<-0.9) ietabin = 0;
      else if (deteta<-0.7) ietabin = 1;
      else if (deteta<-0.5) ietabin = 2;
      else if (deteta<-0.3) ietabin = 3;
      else if (deteta<-0.1) ietabin = 4;
      else if (deteta<0.1) ietabin = 5;
      else if (deteta<0.3) ietabin = 6;
      else if (deteta<0.5) ietabin = 7;
      else if (deteta<0.7) ietabin = 8;
      else if (deteta<0.9) ietabin = 9;
      else ietabin = 10;

      if (eeta-deteta<-0.4) jetabin = 0;
      else if (eeta-deteta<-0.3) jetabin = 1;
      else if (eeta-deteta<-0.2) jetabin = 2;
      else if (eeta-deteta<-0.1) jetabin = 3;
      else if (eeta-deteta<0.0) jetabin = 4;
      else if (eeta-deteta<0.1) jetabin = 5;
      else if (eeta-deteta<0.2) jetabin = 6;
      else if (eeta-deteta<0.3) jetabin = 7;
      else if (eeta-deteta<0.4) jetabin = 8;
      else jetabin = 9;

      // lumi bin for dUpara Smearing for _OptionOfUParaCorrOption3==6 and 7
      int LumiBin = -1;
      if (lumi<2) LumiBin = 0;
      else if (lumi<4) LumiBin = 1;
      else if (lumi<6) LumiBin = 2;
      else if (lumi<8) LumiBin = 3;
      else LumiBin = 4;
 
      // get UperpBin for _OptionOfUParaCorrOption3==6 and 7
      int UPerpBin = -1;
      if (fabs(uperp)<10) UPerpBin=0;
      else UPerpBin=1;


      // get dUPara 
      if(_OptionOfUParaCorrOption3==0) {
        // use smooth function
        dUParaMean = _dUParaMeanFunction->Eval(set, upara);
        // if upara>15 or upara<-15, take the value at 15 or -15, respectively.
        if ( upara>15. ){
          dUParaMean = _dUParaMeanFunction->Eval(set, 15);
        }
        else if ( upara<-15.){
          dUParaMean = _dUParaMeanFunction->Eval(set, -15);
        }
      }
      else if (_OptionOfUParaCorrOption3==1) {
        // use profile
        dUParaMean = _dUParaMeanProfile->GetBinContent(_dUParaMeanProfile->FindBin(set, upara));
        // if upara>15 or upara<-15, take the value at 15 or -15, respectively.
        if ( !(upara>-15.&&upara<15.&&set>0.&&set<300.) ){
          dUParaMean = _dUParaMeanProfile->GetMean(3);
        }
      }
      else if (_OptionOfUParaCorrOption3==2) {
        dUParaMean = _dUParaMeanProfile3D->GetBinContent(_dUParaMeanProfile3D->FindBin(set, upara, lumi));
        dUParaZeroFrac = _dUParaZeroFraction3D->GetBinContent(_dUParaZeroFraction3D->FindBin(set, upara, lumi));
        // if outside profile axes bundaries, increase Zero fraction to 1 (UParaCorr will be 0) 
        if ( !(set>_dUParaMeanProfile3D->GetXaxis()->GetXmin() &&
               set<_dUParaMeanProfile3D->GetXaxis()->GetXmax() &&
               upara>_dUParaMeanProfile3D->GetYaxis()->GetXmin() &&
               upara<_dUParaMeanProfile3D->GetYaxis()->GetXmax() &&
               lumi>_dUParaMeanProfile3D->GetZaxis()->GetXmin() &&
               lumi<_dUParaMeanProfile3D->GetZaxis()->GetXmax() ) ) {
          dUParaMean = _dUParaSmearHist1DAll->GetMean();
        } 
      }
      else if (_OptionOfUParaCorrOption3==3) {
        dUParaMean = _dUParaMeanProfile3DEta[etabin]->GetBinContent(_dUParaMeanProfile3DEta[etabin]->FindBin(set, upara, lumi));
        dUParaZeroFrac = _dUParaZeroFraction3DEta[etabin]->GetBinContent(_dUParaZeroFraction3DEta[etabin]->FindBin(set, upara, lumi));
        // if outside profile axes bundaries, increase Zero fraction to 1 (UParaCorr will be 0) 
        if ( !(set>_dUParaMeanProfile3DEta[etabin]->GetXaxis()->GetXmin() &&
               set<_dUParaMeanProfile3DEta[etabin]->GetXaxis()->GetXmax() &&
               upara>_dUParaMeanProfile3DEta[etabin]->GetYaxis()->GetXmin() &&
               upara<_dUParaMeanProfile3DEta[etabin]->GetYaxis()->GetXmax() &&
               lumi>_dUParaMeanProfile3DEta[etabin]->GetZaxis()->GetXmin() &&
               lumi<_dUParaMeanProfile3DEta[etabin]->GetZaxis()->GetXmax() ) ) {
          dUParaMean = _dUParaSmearHist1DAll->GetMean();
        }
      }
      else if (_OptionOfUParaCorrOption3==4) {
        dUParaMean = _dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetBinContent(_dUParaMeanProfile3D2Eta[ietabin][jetabin]->FindBin(set, upara, lumi));
        dUParaZeroFrac = _dUParaZeroFraction3D2Eta[ietabin][jetabin]->GetBinContent(_dUParaZeroFraction3D2Eta[ietabin][jetabin]->FindBin(set, upara, lumi));
        // if outside profile axes bundaries, increase Zero fraction to 1 (UParaCorr will be 0) 
        if ( !(set>_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetXaxis()->GetXmin() &&
               set<_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetXaxis()->GetXmax() &&
               upara>_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetYaxis()->GetXmin() &&
               upara<_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetYaxis()->GetXmax() &&
               lumi>_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetZaxis()->GetXmin() &&
               lumi<_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetZaxis()->GetXmax() ) ) {
          dUParaMean = _dUParaSmearHist1DAll->GetMean();
        }

      }
      else if (_OptionOfUParaCorrOption3==5) {
        if(_runNumber < _middlerunnumber) {
          dUParaMean = _dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetBinContent(_dUParaMeanProfile3D2Eta[ietabin][jetabin]->FindBin(set, upara, lumi));
          dUParaZeroFrac = _dUParaZeroFraction3D2Eta[ietabin][jetabin]->GetBinContent(_dUParaZeroFraction3D2Eta[ietabin][jetabin]->FindBin(set, upara, lumi));
          // if outside profile axes bundaries, increase Zero fraction to 1 (UParaCorr will be 0) 
          if ( !(set>_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetXaxis()->GetXmin() &&
                 set<_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetXaxis()->GetXmax() &&
                 upara>_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetYaxis()->GetXmin() &&
                 upara<_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetYaxis()->GetXmax() &&
                 lumi>_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetZaxis()->GetXmin() &&
                 lumi<_dUParaMeanProfile3D2Eta[ietabin][jetabin]->GetZaxis()->GetXmax() ) ) {
            dUParaMean = _dUParaSmearHist1DAll->GetMean();
          }
        }
        else {
          dUParaMean = _dUParaMeanProfile3D2Eta2[ietabin][jetabin]->GetBinContent(_dUParaMeanProfile3D2Eta2[ietabin][jetabin]->FindBin(set, upara, lumi));
          dUParaZeroFrac = _dUParaZeroFraction3D2Eta2[ietabin][jetabin]->GetBinContent(_dUParaZeroFraction3D2Eta2[ietabin][jetabin]->FindBin(set, upara, lumi));
          if ( !(set>_dUParaMeanProfile3D2Eta2[ietabin][jetabin]->GetXaxis()->GetXmin() &&
                 set<_dUParaMeanProfile3D2Eta2[ietabin][jetabin]->GetXaxis()->GetXmax() &&
                 upara>_dUParaMeanProfile3D2Eta2[ietabin][jetabin]->GetYaxis()->GetXmin() &&
                 upara<_dUParaMeanProfile3D2Eta2[ietabin][jetabin]->GetYaxis()->GetXmax() &&
                 lumi>_dUParaMeanProfile3D2Eta2[ietabin][jetabin]->GetZaxis()->GetXmin() &&
                 lumi<_dUParaMeanProfile3D2Eta2[ietabin][jetabin]->GetZaxis()->GetXmax() ) ) {
            dUParaMean = _dUParaSmearHist1DAll2->GetMean();
          }
        }

      }
      else if (_OptionOfUParaCorrOption3==6||_OptionOfUParaCorrOption3==7) {
        dUParaMean = _dUParaMeanProfile3D2EtaUPerp[ietabin][jetabin][UPerpBin]->GetBinContent(_dUParaMeanProfile3D2EtaUPerp[ietabin][jetabin][UPerpBin]->FindBin(set, upara, lumi));
        dUParaZeroFrac = _dUParaZeroFraction3D2EtaUPerp[ietabin][jetabin][UPerpBin]->GetBinContent(_dUParaZeroFraction3D2EtaUPerp[ietabin][jetabin][UPerpBin]->FindBin(set, upara, lumi));
        // if outside profile axes bundaries, increase Zero fraction to 1 (UParaCorr will be 0)
        if ( !(set>_dUParaMeanProfile3D2EtaUPerp[ietabin][jetabin][UPerpBin]->GetXaxis()->GetXmin() &&
               set<_dUParaMeanProfile3D2EtaUPerp[ietabin][jetabin][UPerpBin]->GetXaxis()->GetXmax() &&
               upara>_dUParaMeanProfile3D2EtaUPerp[ietabin][jetabin][UPerpBin]->GetYaxis()->GetXmin() &&
               upara<_dUParaMeanProfile3D2EtaUPerp[ietabin][jetabin][UPerpBin]->GetYaxis()->GetXmax() &&
               lumi>_dUParaMeanProfile3D2EtaUPerp[ietabin][jetabin][UPerpBin]->GetZaxis()->GetXmin() &&
               lumi<_dUParaMeanProfile3D2EtaUPerp[ietabin][jetabin][UPerpBin]->GetZaxis()->GetXmax() ) ) {
          dUParaMean = _dUParaSmearHist1DLumiAll[LumiBin]->GetMean();
        }
	
	if (_OptionOfUParaCorrOption3==7&& _runNumber > _middlerunnumber) {
	  dUParaMean = _dUParaMeanProfile3D2EtaUPerp2[ietabin][jetabin][UPerpBin]->GetBinContent(_dUParaMeanProfile3D2EtaUPerp2[ietabin][jetabin][UPerpBin]->FindBin(set, upara, lumi));
	  dUParaZeroFrac = _dUParaZeroFraction3D2EtaUPerp2[ietabin][jetabin][UPerpBin]->GetBinContent(_dUParaZeroFraction3D2EtaUPerp2[ietabin][jetabin][UPerpBin]->FindBin(set, upara, lumi));
	  // if outside profile axes bundaries, increase Zero fraction to 1 (UParaCorr will be 0)
	  if ( !(set>_dUParaMeanProfile3D2EtaUPerp2[ietabin][jetabin][UPerpBin]->GetXaxis()->GetXmin() &&
		 set<_dUParaMeanProfile3D2EtaUPerp2[ietabin][jetabin][UPerpBin]->GetXaxis()->GetXmax() &&
		 upara>_dUParaMeanProfile3D2EtaUPerp2[ietabin][jetabin][UPerpBin]->GetYaxis()->GetXmin() &&
		 upara<_dUParaMeanProfile3D2EtaUPerp2[ietabin][jetabin][UPerpBin]->GetYaxis()->GetXmax() &&
		 lumi>_dUParaMeanProfile3D2EtaUPerp2[ietabin][jetabin][UPerpBin]->GetZaxis()->GetXmin() &&
		 lumi<_dUParaMeanProfile3D2EtaUPerp2[ietabin][jetabin][UPerpBin]->GetZaxis()->GetXmax() ) ) {
	    dUParaMean = _dUParaSmearHist1DLumiAll2[LumiBin]->GetMean();
	  }
	}
      }    
      else {
        cout<<"   OptionOfUParaCorrOption3 can only be 0 to 5 ." <<endl;
        exit(-1);
      }

      /////////////////////
      // (2) Smear of dUPara

      // get the right _dUParaSmearHist3D for option3 = 6 and 7, because of the lumi binning it was not  
      if(_OptionOfUParaCorrOption3==6 || _OptionOfUParaCorrOption3==7) {
        _dUParaSmearHist3D = _dUParaSmearHist3DLumi[LumiBin];
        if (_OptionOfUParaCorrOption3==7&& _runNumber > _middlerunnumber) {
          _dUParaSmearHist3D2 = _dUParaSmearHist3DLumi2[LumiBin];
        }
      }
      // find the SET and Upara binning
       
      // find SET bin
      int SETBin = -1;
      // for 2b3 if Option3 = 5
      if (_OptionOfUParaCorrOption3<5 || (_OptionOfUParaCorrOption3==5 &&  _runNumber<_middlerunnumber) ){
        if (set>_dUParaSmearHist3D->GetXaxis()->GetXmin()&&set<_dUParaSmearHist3D->GetXaxis()->GetXmax()){
          SETBin = _dUParaSmearHist3D->GetXaxis()->FindBin(set) - 1 ;
        }
        else if (set<_dUParaSmearHist3D->GetXaxis()->GetXmin()) {
          SETBin = 0; 
        }
        else if (set>_dUParaSmearHist3D->GetXaxis()->GetXmax()){
          SETBin = _dUParaSmearHist3D->GetXaxis()->GetNbins() - 1 ;
        }
      }
      // for 2b4 if Option3 = 5
      else if (_OptionOfUParaCorrOption3==5 && _runNumber > _middlerunnumber){
        if (set>_dUParaSmearHist3D2->GetXaxis()->GetXmin()&&set<_dUParaSmearHist3D2->GetXaxis()->GetXmax()){
          SETBin = _dUParaSmearHist3D2->GetXaxis()->FindBin(set) - 1 ;
        }
        else if (set<_dUParaSmearHist3D2->GetXaxis()->GetXmin()) {
          SETBin = 0;
        }
        else if (set>_dUParaSmearHist3D2->GetXaxis()->GetXmax()){
          SETBin = _dUParaSmearHist3D2->GetXaxis()->GetNbins() - 1 ;
        }
      }
      //Option3 = 6 or 7  with Lumi bin
      else if(_OptionOfUParaCorrOption3==6 || _OptionOfUParaCorrOption3==7) {
      
        if (set>_dUParaSmearHist3D->GetXaxis()->GetXmin()&&set<_dUParaSmearHist3D->GetXaxis()->GetXmax()){
          SETBin = _dUParaSmearHist3D->GetXaxis()->FindBin(set) - 1 ;
        }
        else if (set<_dUParaSmearHist3D->GetXaxis()->GetXmin()) {
          SETBin = 0;
        }
        else if (set>_dUParaSmearHist3D->GetXaxis()->GetXmax()){
          SETBin = _dUParaSmearHist3D->GetXaxis()->GetNbins() - 1 ;
        }
      
        // for 2b4 if Option3 = 7
        if (_OptionOfUParaCorrOption3==7 && _runNumber > _middlerunnumber){
          if (set>_dUParaSmearHist3D2->GetXaxis()->GetXmin()&&set<_dUParaSmearHist3D2->GetXaxis()->GetXmax()){
            SETBin = _dUParaSmearHist3D2->GetXaxis()->FindBin(set) - 1 ;
          }
          else if (set<_dUParaSmearHist3D2->GetXaxis()->GetXmin()) {
            SETBin = 0;
          }
          else if (set>_dUParaSmearHist3D2->GetXaxis()->GetXmax()){
            SETBin = _dUParaSmearHist3D2->GetXaxis()->GetNbins() - 1 ;
          }
        }
 
      }
      else {
        cout<<"   OptionOfUParaCorrOption3 can only be 0 to 7 ." <<endl;
        exit(-1);
      }

      // find UPara bin
      int UParaBin = -1;
      // for 2b3 if Option3 = 5
      if (_OptionOfUParaCorrOption3<5 || (_OptionOfUParaCorrOption3==5 &&  _runNumber<_middlerunnumber) ){
        if (upara>_dUParaSmearHist3D->GetYaxis()->GetXmin() && upara<_dUParaSmearHist3D->GetYaxis()->GetXmax()){
          UParaBin = _dUParaSmearHist3D->GetYaxis()->FindFixBin(upara) - 1;
        }
        else if (upara<=_dUParaSmearHist3D->GetYaxis()->GetXmin()) {
          UParaBin = 0; 
        }
        else if (upara>=_dUParaSmearHist3D->GetYaxis()->GetXmax()){
          UParaBin = _dUParaSmearHist3D->GetYaxis()->GetNbins() - 1;
        }
      }
      // for 2b4 if Option3 = 5
      else if (_OptionOfUParaCorrOption3==5 && _runNumber > _middlerunnumber){
        if (upara>_dUParaSmearHist3D2->GetYaxis()->GetXmin() && upara<_dUParaSmearHist3D2->GetYaxis()->GetXmax()){
          UParaBin = _dUParaSmearHist3D2->GetYaxis()->FindFixBin(upara) - 1;
        }
        else if (upara<=_dUParaSmearHist3D2->GetYaxis()->GetXmin()) {
          UParaBin = 0;
        }
        else if (upara>=_dUParaSmearHist3D2->GetYaxis()->GetXmax()){
          UParaBin = _dUParaSmearHist3D2->GetYaxis()->GetNbins() - 1;
        }
      }
      //Option3 = 6 or 7  with Lumi bin
      else if(_OptionOfUParaCorrOption3==6 || _OptionOfUParaCorrOption3==7) {
        if (upara>_dUParaSmearHist3D->GetYaxis()->GetXmin() && upara<_dUParaSmearHist3D->GetYaxis()->GetXmax()){
          UParaBin = _dUParaSmearHist3D->GetYaxis()->FindFixBin(upara) - 1;
        }
        else if (upara<=_dUParaSmearHist3D->GetYaxis()->GetXmin()) {
          UParaBin = 0;
        }
        else if (upara>=_dUParaSmearHist3D->GetYaxis()->GetXmax()){
          UParaBin = _dUParaSmearHist3D->GetYaxis()->GetNbins() - 1;
        }
        // for 2b4 if Option3 = 7
        if (_OptionOfUParaCorrOption3==7 && _runNumber > _middlerunnumber){
          if (upara>_dUParaSmearHist3D2->GetYaxis()->GetXmin() && upara<_dUParaSmearHist3D2->GetYaxis()->GetXmax()){
            UParaBin = _dUParaSmearHist3D2->GetYaxis()->FindFixBin(upara) - 1;
          }
          else if (upara<=_dUParaSmearHist3D2->GetYaxis()->GetXmin()) {
            UParaBin = 0;
          }
          else if (upara>=_dUParaSmearHist3D2->GetYaxis()->GetXmax()){
            UParaBin = _dUParaSmearHist3D2->GetYaxis()->GetNbins() - 1;
          }
        }
      }
      else {
        cout<<"   OptionOfUParaCorrOption3 can only be 0 to 7 ." <<endl;
        exit(-1);
      }

      // Get Smearing histogram
      TH1D* dUParaSmearHist1D; 

      if (_OptionOfUParaCorrOption3<=5) {

        dUParaSmearHist1D = _dUParaSmearHist1DAll;
        //
        if (SETBin!=-1 && UParaBin!=-1){
          dUParaSmearHist1D = _dUParaSmearHist1D[SETBin][UParaBin];
        }

        // if integral of a Hist is empty, use the total one.
        if (dUParaSmearHist1D->Integral()<1e-10){
          dUParaSmearHist1D = _dUParaSmearHist1DAll;
        }

        // for 2b4
        if (_OptionOfUParaCorrOption3==5 && _runNumber > _middlerunnumber){

          dUParaSmearHist1D = _dUParaSmearHist1DAll2;

          if (SETBin!=-1 && UParaBin!=-1){
            dUParaSmearHist1D = _dUParaSmearHist1D2[SETBin][UParaBin];
          }
          // if integral of a Hist is empty, use the total one.
          if (dUParaSmearHist1D->Integral()<1e-10){
            dUParaSmearHist1D = _dUParaSmearHist1DAll2;
          }

        }
        
      }
      else if (_OptionOfUParaCorrOption3==6||_OptionOfUParaCorrOption3==7) {

        dUParaSmearHist1D = _dUParaSmearHist1DLumiAll[LumiBin];
        //
        if (SETBin!=-1 && UParaBin!=-1){
          dUParaSmearHist1D = _dUParaSmearHist1DLumi[LumiBin][SETBin][UParaBin];
        }
        // if integral of a Hist is empty, use the total one.
        if (dUParaSmearHist1D->Integral()<1e-10){
          dUParaSmearHist1D = _dUParaSmearHist1DLumiAll[LumiBin];
        }

        // for 2b4
        if (_OptionOfUParaCorrOption3==7&&_runNumber > _middlerunnumber){

          dUParaSmearHist1D = _dUParaSmearHist1DLumiAll2[LumiBin];
          //
          if (SETBin!=-1 && UParaBin!=-1){
            dUParaSmearHist1D = _dUParaSmearHist1DLumi2[LumiBin][SETBin][UParaBin];
          }
          // if integral of a Hist is empty, use the total one.
          if (dUParaSmearHist1D->Integral()<1e-10){
            dUParaSmearHist1D = _dUParaSmearHist1DLumiAll2[LumiBin];
          }
        }

      }
      else {
        cout<<"   OptionOfUParaCorrOption3 can only be 0 to 7." <<endl;
        exit(-1);
      }

      // get mean dUPara of the Smearing Hist
      double dUParaMeanInSmearHist = dUParaSmearHist1D->GetMean();

      /////////////////////
      // (3) Final Smeared dUPara of the given event

      // smeared dUPara from the Smearing Hist
      double dUParaSmearInSmearHist = 0.;
      // assign dUParaZeroFrac to be 0, if _OptionOfUParaCorrOption3<=1
      if (_OptionOfUParaCorrOption3<=1) dUParaZeroFrac=0.;
      // (3.1) If Apply dUParaEff?
      if (_Apply_dUParaEff){

        double duparaeff = 0;
        int duparaeff_ntimes = 0;

	double ref_pt = pT_raw;
	if (_dUParaEffUseTruePT) ref_pt = truePT;	
	if (_dUParaEff_Option==6) Get_dUParaEff6_UseHistsInit(ref_pt, eta_raw, upara, set, uperp);

	if (extrndm && extrndm_duparaeff) {
	  while (extrndm_duparaeff[duparaeff_ntimes]>duparaeff) {
	    
	    // Not pass ZeroFraction, UParaCorr = 0
	    if (extrndm[0]<dUParaZeroFrac){
	      
	      UParaCorr = 0;
	      
	    } else {
	      
	      double random2 = (extrndm[0]-dUParaZeroFrac)/(1.-dUParaZeroFrac);
	      dUParaSmearInSmearHist = ((PMCSTH1*)(dUParaSmearHist1D))->GetRandom(random2);
	      
	      if (_OptionOfUParaCorrOption3<=1 && (dUParaSmearInSmearHist<1e-2 || dUParaMeanInSmearHist<1e-2)){
		UParaCorr = 0;
	      } else {
		UParaCorr = dUParaMean * dUParaSmearInSmearHist/dUParaMeanInSmearHist;
	      }
	      
	    }
	    // get duparaeff
	    double ref_dupara = UParaCorr;
	    if (_dUParaEffUsedEPara && !_UParaCorrOption3_dUParaLibUsedEPara ) {
	      ref_dupara = UParaCorr*cosh(eta_raw);
	    }
	    else if ( !_dUParaEffUsedEPara && _UParaCorrOption3_dUParaLibUsedEPara) {
	      ref_dupara = UParaCorr/cosh(eta_raw);
	    }
	    
	    if (_dUParaEff_Option==0 ){
	      duparaeff = Get_dUParaEff(ref_dupara, ref_pt, isW);
	    }
	    else if ( _dUParaEff_Option==1 ){
	      duparaeff = Get_dUParaEff1(ref_dupara, ref_pt, eta_raw);
	    }
	    else if ( _dUParaEff_Option==2 ){
	      duparaeff = Get_dUParaEff2(ref_dupara, ref_pt, eta_raw);
	    }
	    else if ( _dUParaEff_Option==3|| _dUParaEff_Option==4 || _dUParaEff_Option==5 ) {
	      cout << "EMSmear:: dUParaEff_Option 3, 4, 5 are adding dependencies of upara, \n"
		   << "          set, etc, only implemented in a testing framework by Hengne,\n"
		   << "          not yet copied here. "  << endl;
	    }
	    else if (_dUParaEff_Option==6) {
	      duparaeff = Get_dUParaEff6_UseHists(ref_dupara, ref_pt);
	    }
	    else {
	      cout << "dUParaEff_Option should be 0, 1, 2, or 6" << endl;
	      exit(-1);
	    }
	    
	    // protection against negtive Pt
	    if (pT_raw<0.) duparaeff = 1.;
	    
	    duparaeff_ntimes++;
	    if (duparaeff_ntimes>=10000) break;
	  }
	} else while (dummy->Rndm()>duparaeff) {
	  duparaeff_ntimes++;
	  if (duparaeff_ntimes>10000) break;
	  // another random
	  double random = dummy->Rndm();
	  
	  // Not pass ZeroFraction, UParaCorr = 0
	  if (random<dUParaZeroFrac){
	    UParaCorr = 0;
	  }
	  // Pass ZeroFraction, get Smeared dUPara from the Smearing Hist
	  else {
	    double random2 = (random-dUParaZeroFrac)/(1.-dUParaZeroFrac);
	    dUParaSmearInSmearHist = ((PMCSTH1*)(dUParaSmearHist1D))->GetRandom(random2);
	    // calculate UParaCorr
	    if (_OptionOfUParaCorrOption3<=1 && (dUParaSmearInSmearHist<1e-2 || dUParaMeanInSmearHist<1e-2)){
	      // if Smeared dUPara In Smear Hist is in the 1st bin, UParaCorr = 0
	      // if the Mean dUPara in the Smear Hist is near 0, UParaCorr = 0
	      UParaCorr = 0;
	    }
	    else {
	      UParaCorr = dUParaMean * dUParaSmearInSmearHist/dUParaMeanInSmearHist;
	    }
	  }
	  
	  // get duparaeff
	  double ref_dupara = UParaCorr;
	  if (_dUParaEffUsedEPara && !_UParaCorrOption3_dUParaLibUsedEPara ) {
	    ref_dupara = UParaCorr*cosh(eta_raw);
	  }
	  else if ( !_dUParaEffUsedEPara && _UParaCorrOption3_dUParaLibUsedEPara) {
	    ref_dupara = UParaCorr/cosh(eta_raw);
	  }
	  
	  if (_dUParaEff_Option==0 ){
	    duparaeff = Get_dUParaEff(ref_dupara, ref_pt, isW);
	  }
	  else if ( _dUParaEff_Option==1 ){
	    duparaeff = Get_dUParaEff1(ref_dupara, ref_pt, eta_raw);
	  }
	  else if ( _dUParaEff_Option==2 ){
	    duparaeff = Get_dUParaEff2(ref_dupara, ref_pt, eta_raw);
	  }
	  else if ( _dUParaEff_Option==3|| _dUParaEff_Option==4 || _dUParaEff_Option==5 ) {
	    cout << "EMSmear:: dUParaEff_Option 3, 4, 5 are adding dependencies of upara, \n" 
		 << "          set, etc, only implemented in a testing framework by Hengne,\n"
		 << "          not yet copied here. "  << endl;
	  }
	  else if (_dUParaEff_Option==6) {
	    duparaeff = Get_dUParaEff6_UseHists(ref_dupara, ref_pt);
	  }
	  else {
	    cout << "dUParaEff_Option should be 0, 1, 2, or 6" << endl;
	    exit(-1);
	  }
	  
	  // protection 
	  if (pT_raw<0.) {
	    duparaeff = 1.;
	  }
	  //  }
        } // while dummy-> ...
	
        // debug
        //std::cout << " ---- Hengne: UParaCorr=" << UParaCorr << "; duparaeff=" << duparaeff << "; duparaeff_ntimes=" << duparaeff_ntimes << std::endl;
      }
      // (3.2) Not Apply dUParaEff
      else {
        // get random
        double random = dummy->Rndm();
        if (extrndm) random = extrndm[0];
        // Not pass ZeroFraction, UParaCorr = 0
        if (random<dUParaZeroFrac){
          UParaCorr = 0;
        }
        // Pass ZeroFraction, get Smeared dUPara from the Smearing Hist
        else {
          double random2 = (random-dUParaZeroFrac)/(1.-dUParaZeroFrac);
          dUParaSmearInSmearHist = ((PMCSTH1*)(dUParaSmearHist1D))->GetRandom(random2);
          // calculate UParaCorr
          UParaCorr = dUParaMean * dUParaSmearInSmearHist/dUParaMeanInSmearHist;
        }
      } // if (_Apply_dUParaEff) ... else ...
      
      // debug
      //std::cout << " ---- Hengne: UParaCorr=" << UParaCorr << "; dUParaMean=" << dUParaMean << "; set=" << set << "; upara=" << upara << std::endl;
      //if (fabs(upara)>15.&&UParaCorr>0. ) std::cout << " ---- Hengne: upara=" << upara << "UParaCorr=" << UParaCorr << std::endl;
    }
    else {
       cout << "Error! Please specify UParaCorrOption to be either 0, 1, 2, 3, or 4" << endl;
       exit(-1);
    }

    if (_UParaCorrOption3_dUParaLibUsedEPara) {
      // convert dEPara to dUPara
      UParaCorr = UParaCorr/cosh(eta_raw);
    }

    // if ZSUPCorrOption==0, use average value
    // otherwise read zero-suppression correction vs electron eta from histogram
    if(_ZSUPCorrOption==0) Delta_ZSUP = _Delta_ZSUP_CC;
    else {
      // check zero-suppression effect on electron eta
      Delta_ZSUP = _ZSUP_CC_V_ElecEta_Parameters[0] + _ZSUP_CC_V_ElecEta_Parameters[1] * eta_raw +
	_ZSUP_CC_V_ElecEta_Parameters[2] * eta_raw * eta_raw;
    }

    // energy leakage outside of the recontruction cone
    int LeakBin=-1;
    switch (_ENERGY_OUTCONE_MODEL_Elec_CC) {
    case 1:
      EnergyLeakage = _ENERGY_OUTCONE_Elec_CC;
      break;
    case 2:
      EnergyLeakage = _ENERGY_OUTCONE_Elec_CC/sin(theta);
      break;
    case 3:
      LeakBin=(int)(eta_raw/0.2)+7;
      if (LeakBin<0) LeakBin=0;
      if (LeakBin>13) LeakBin=13;
      double r;
      if (extrndm) {
	r = extrndm[3];
      } else {
	r = gRandom->Rndm();
      }
      if (r<_ENERGY_OUTCONE_JanModel_Elec_CC[LeakBin]->GetBinContent(0)) {
	EnergyLeakage=0;
      } else {
	if (!extrndm)
	  EnergyLeakage=_ENERGY_OUTCONE_JanModel_Elec_CC[LeakBin]->GetRandom()*part.getTrueE();
	else{
	  EnergyLeakage = (((PMCSTH1* )(_ENERGY_OUTCONE_JanModel_Elec_CC[LeakBin]) ))->GetRandom(extrndm[1])*part.getTrueE() ;
	}
      }
      EnergyLeakage*=_ENERGY_OUTCONE_JanModel_Elec_Fudge_CC;
      break;
    case 4:
      LeakBin=(int)(eta_raw/0.2)+7;
      if (LeakBin<0) LeakBin=0;
      if (LeakBin>13) LeakBin=13;
      if (extrndm) {
	r = extrndm[3];
      } else {
	r = gRandom->Rndm();
      }
      //
      TH1D* theLeakHist;
      double theFudge;
      if (part.FSRxInCone()>0) {
	theLeakHist=_ENERGY_OUTCONE_JanModel_Elec_CCfsr[LeakBin];
	theFudge=_ENERGY_OUTCONE_JanModel_Elec_Fudge_CCfsr;
      } else {
	theLeakHist=_ENERGY_OUTCONE_JanModel_Elec_CC[LeakBin];
	theFudge=_ENERGY_OUTCONE_JanModel_Elec_Fudge_CC;
      }
      //
      if (r<theLeakHist->GetBinContent(0)) {
	EnergyLeakage=0;
      } else {
	if (!extrndm)
	  EnergyLeakage=theLeakHist->GetRandom()*part.getTrueE();
	else{
	  EnergyLeakage = (((PMCSTH1* )(theLeakHist) ))->GetRandom(extrndm[1])*part.getTrueE() ;
	}
      }
      EnergyLeakage*=theFudge;
      break;
    case 5:
      int ptbin = wz_utils::getbin(eleak_model5_ptbins, part.getTruePt());
      int etabin = wz_utils::getbin(eleak_model5_etabins, TMath::Abs(part.getTrueEta()));
      int setbin = wz_utils::getbin(eleak_model5_setbins, set);
      int Xbin = wz_utils::getbin(eleak_model5_Xbins, part.FSRxInCone());

      Double_t prob, rndm;
      if (part.FSRxInCone() > 0)
	if (eleak_model5_interpolate)
	  prob = wz_utils::interpolate2d(eleak_model5_leakageProbabilityFSR[ptbin], set, TMath::Abs(part.getTrueEta()));
	else 
	  prob = eleak_model5_leakageProbabilityFSR[ptbin]->GetBinContent(eleak_model5_leakageProbabilityFSR[ptbin]->FindBin(set, TMath::Abs(part.getTrueEta())));
      else 
	if (eleak_model5_interpolate)
	  prob = wz_utils::interpolate2d(eleak_model5_leakageProbability[ptbin], set, TMath::Abs(part.getTrueEta()));
	else 
	  prob = eleak_model5_leakageProbability[ptbin]->GetBinContent(eleak_model5_leakageProbability[ptbin]->FindBin(set, TMath::Abs(part.getTrueEta())));
      if (extrndm) {
        rndm = extrndm[3];
      } else {
        rndm = gRandom->Rndm();
      }
      EnergyLeakage = 0;
      if (rndm < prob) {
	if (part.FSRxInCone() > 0) {
	  if (eleak_model5_leakageDistributionFSR[ptbin][etabin][setbin][Xbin]) {
	    if (!extrndm) {
	      EnergyLeakage = eleak_model5_FSRFudge*eleak_model5_leakageDistributionFSR[ptbin][etabin][setbin][Xbin]->GetRandom()*part.getTrueE();
	    } else {
	      EnergyLeakage = eleak_model5_FSRFudge*(((PMCSTH1* )(eleak_model5_leakageDistributionFSR[ptbin][etabin][setbin][Xbin]) ))->GetRandom(extrndm[1])*part.getTrueE();
	    }
	  } else {
	    EnergyLeakage = 0.;
	  }
	} else {
	  if (eleak_model5_leakageDistribution[ptbin][etabin][setbin]) {
	    if (!extrndm) {
	      EnergyLeakage = eleak_model5_vetoFudge*eleak_model5_leakageDistribution[ptbin][etabin][setbin]->GetRandom()*part.getTrueE();
	    } else {
	      EnergyLeakage = eleak_model5_vetoFudge*(((PMCSTH1* )(eleak_model5_leakageDistribution[ptbin][etabin][setbin]) ))->GetRandom(extrndm[1])*part.getTrueE();
	    }
	  } else {
	    EnergyLeakage = 0.;
	  }
	}
      }
      break;
    default:
      assert(0);
    }

  } else {    // for EC region, currently set all corrections to 0 GeV
    UParaCorr = _UParaCorr_EC;
    Delta_ZSUP = _Delta_ZSUP_EC;
    EnergyLeakage = _ENERGY_OUTCONE_Elec_EC;
  }

  //IF EnergySim_ElecWindowOption = 0, Energies below electron window is divided into two parts:
  //       \delta E = UParaCorr/sin(theta) + Delta_ZSUP (UE contribution and zero-suppression effect)
  //  where UParaCorr is described in the recoil system simulation
  //  and Delta_ZSUP is zero-suppression effect on tower energy measurement and real electron energy measurement
  if(_EnergySim_ElecWindowOption == 0 || !InCC) {
    // Energy flow under electron window should be underlying event contribution (UParaCorr) and the ZSUP effects
    // energy leaks out of the electron cone should also be considered here (???)
    rawpTUnderElecWindow = UParaCorr + Delta_ZSUP * sin(theta);
    
    // apply the same EM energy corrections here as in EMReco
    // pT after energies under electron window correction
    // since all corrections factors were determined using EM energy after geometry corrections
    // we do not need to apply EMCorrFactor here
    double pT_new = pT_raw + rawpTUnderElecWindow;
    
    // then we need to subtract energy that is leakage out the electron code
    //  pT_new -= EnergyLeakage * sin(theta);
    
    // calculate final smeared energy
    energy_after_ElecSim_ElecWindow = pT_new/sin(theta);
    
    // E-loss corrections are derived from zero-suppressed single energy electrons (no MB overlay)
    // so the zero-suppression effect on the electron has been PARTIALLY taken into account during E-loss correction
    // the zero-suppression effect for single energy electrons with and without MB overlay are different
    // the real electrons observed in the detector always have MB overlay
    // need to subtract this effect
    energy_after_ElecSim_ElecWindow -= _ZSUP_CC_Elec_NoMBOverlay;
  } else if (_EnergySim_ElecWindowOption == 1)  {
    // IF EnergySim_ElecWindowOption = 1, use the method proposed by Jan and measured by Feng
    //   take the energy difference between single energy electron without and with non-zero-suppressed ZB overlay
    //   (offline zero-suppression applied for both samples), and parameterize the energy difference as a function
    //   of underlying event energy below electron window. In PMCS, we first read the underlying event below electron
    //   window from UParaCorr_CC_Hist file, and then use the parameterization to get the corrected energy, to do
    //   it this way, UE and zero-suppression effect are combined together
    // parameterized as a function of physics eta
    int etabin = (int)((deteta_raw+1.1)/0.2);    // 11 bins for detector eta between -1.1 and 1.1 with bin size 0.2
                                                 // even though Feng mentioned this as physics eta in his note
    if(etabin < 0) etabin = 0;
    if(etabin > 10) etabin = 10;
    if(fabs(UParaCorr) >0.01) 
      energyDiffElecWithWithoutZBOverlay = _P0_EnergyDiff_Electron_With_Without_ZBOverlay[etabin] + 
	_P1_EnergyDiff_Electron_With_Without_ZBOverlay[etabin] * TMath::Log(fabs(UParaCorr)/sin(theta)) +
	_P2_EnergyDiff_Electron_With_Without_ZBOverlay[etabin] * TMath::Log(fabs(UParaCorr)/sin(theta)) * TMath::Log(fabs(UParaCorr)/sin(theta));
    else 
      energyDiffElecWithWithoutZBOverlay = _EnergyDiff_FirstBin[etabin];      

    energy_after_ElecSim_ElecWindow = pE_raw + energyDiffElecWithWithoutZBOverlay;
    _energyDiffElec = energyDiffElecWithWithoutZBOverlay;
  }
  else if (_EnergySim_ElecWindowOption >1 && _EnergySim_ElecWindowOption <= 3){
    int etabin = (int)((deteta_raw+1.1)/0.2);
    if(etabin < 0) etabin = 0;
    if(etabin > 10) etabin = 10;
    double E_UPin[2]; 
    E_UPin[0] = (fabs(UParaCorr)/sin(theta));
    if(fabs(UParaCorr) >0.01) {
      if (isW){
        //std::cout << " This is a w" << std::endl;
        energyDiffElecWithWithoutZBOverlay = _EnergyDiffFunctionw.at(etabin)->Evaluate(E_UPin);
      }
      else {
        //std::cout << " This is a z" << std::endl;
        energyDiffElecWithWithoutZBOverlay = _EnergyDiffFunctionz.at(etabin)->Evaluate(E_UPin);
      }
    }
    else if (isW){
      //std::cout << " This is a w" << std::endl;
      if (_EnergySim_ElecWindowOption ==2){
        energyDiffElecWithWithoutZBOverlay = _EnergyDiff_Model2_FirstBinw[etabin];
      }
      else {	  
        energyDiffElecWithWithoutZBOverlay = (_hZBLibBin0_etabinw[etabin]->GetRandom()-_hZBLibBin0_etabinw[etabin]->GetMean()) *_electronicNoiseFactor + _hZBLibBin0_etabinw[etabin]->GetMean();
      }      
    }
    else {
      //std::cout << " This is a z" << std::endl;
      if (_EnergySim_ElecWindowOption ==2){
        energyDiffElecWithWithoutZBOverlay = _EnergyDiff_Model2_FirstBinz[etabin];
      }
      else{
        if (!extrndm){
          energyDiffElecWithWithoutZBOverlay = (_hZBLibBin0_etabinz[etabin]->GetRandom()-_hZBLibBin0_etabinz[etabin]->GetMean()) *_electronicNoiseFactor + _hZBLibBin0_etabinz[etabin]->GetMean();
        }
        else {
          energyDiffElecWithWithoutZBOverlay = (((PMCSTH1*)(_hZBLibBin0_etabinz[etabin]))->GetRandom(extrndm[2])-_hZBLibBin0_etabinz[etabin]->GetMean()) *_electronicNoiseFactor + _hZBLibBin0_etabinz[etabin]->GetMean();   
        } 
        //std::cout << pE_raw << "   " << _hZBLibBin0_etabinz[etabin]->GetMean() << "    " <<   std::endl;
      }    
    }
    // std::cout << deteta_raw << "   " << etabin << "   " <<  E_UPin[0] << "    " << energyDiffElecWithWithoutZBOverlay  <<  "   " << _EnergyDiffFunction.at(etabin)->Evaluate(E_UPin) << std::endl;

    // fudge UPara correction to EM cone, if requested
    energyDiffElecWithWithoutZBOverlay*=_EnergySim_ElecWindowFudge;

    energy_after_ElecSim_ElecWindow = pE_raw + energyDiffElecWithWithoutZBOverlay;
    _energyDiffElec = energyDiffElecWithWithoutZBOverlay;
  }
  else if (_EnergySim_ElecWindowOption==4){
    // case dUPara>0:
    if ( UParaCorr>0.001 ) {
      // find iset, ilumi and ieta
      int iset, ilumi, ieta;
      for (iset=0; iset<(int)_dUPlusSETBins.size()-2; iset++){
        if (set>=_dUPlusSETBins.at(iset)&&set<_dUPlusSETBins.at(iset+1)) break;
      }
      for (ilumi=0; ilumi<(int)_dUPlusLumiBins.size()-2; ilumi++){
        if (lumi>=_dUPlusLumiBins.at(ilumi)&&lumi<_dUPlusLumiBins.at(ilumi+1)) break;
      }
      for (ieta=0; ieta<(int)_dUPlusEtaBins.size()-2; ieta++){
        if (deteta_raw>=_dUPlusEtaBins.at(ieta)&&deteta_raw<_dUPlusEtaBins.at(ieta+1)) break;
      } 

      // get pars
      double par0 = _duplus_par_vec.at(iset).at(ilumi).at(ieta).at(0);
      double par1 = _duplus_par_vec.at(iset).at(ilumi).at(ieta).at(1);

      // calculate predicted dE
      energyDiffElecWithWithoutZBOverlay = par0+UParaCorr/sin(theta)*par1;  
    }
    // case dUPara=0:
    else {
      // find iset, ilumi, ieta and ipt
      int iset, ilumi, ieta, ipt;
      for (iset=0; iset<(int)_dUZeroSETBins.size()-2; iset++){
        if (set>=_dUZeroSETBins.at(iset)&&set<_dUZeroSETBins.at(iset+1)) break;
      }
      for (ilumi=0; ilumi<(int)_dUZeroLumiBins.size()-2; ilumi++){
        if (lumi>=_dUZeroLumiBins.at(ilumi)&&lumi<_dUZeroLumiBins.at(ilumi+1)) break;
      }
      for (ieta=0; ieta<(int)_dUZeroEtaBins.size()-2; ieta++){
        if (deteta_raw>=_dUZeroEtaBins.at(ieta)&&deteta_raw<_dUZeroEtaBins.at(ieta+1)) break;
      }
      for (ipt=0; ipt<(int)_dUZeroPtBins.size()-2; ipt++){
        if (pT_raw>=_dUZeroPtBins.at(ipt)&&pT_raw<_dUZeroPtBins.at(ipt+1)) break;
      }

      // get prediceted dE
      energyDiffElecWithWithoutZBOverlay = _duzero_par_vec.at(iset).at(ilumi).at(ieta).at(ipt);

    } // if dUPara>0 ... else dUPara=0 

    // fudge UPara correction to EM cone, if requested
    energyDiffElecWithWithoutZBOverlay*=_EnergySim_ElecWindowFudge;

    energy_after_ElecSim_ElecWindow = pE_raw + energyDiffElecWithWithoutZBOverlay;
    _energyDiffElec = energyDiffElecWithWithoutZBOverlay;
  
    
  }
  else if (_EnergySim_ElecWindowOption==5){

    // case dUPara>0:
    if ( UParaCorr>0.001 ) {

      // find ieta, ipt, iupara, ilumi, iset
      int ieta, ipt, iupara, ilumi, iset;
      // ieta
      for (ieta=0; ieta<(int)_CAEPdUZeroEtaBins.size()-1; ieta++){
        if (eta_raw>=_CAEPdUZeroEtaBins.at(ieta)&&eta_raw<_CAEPdUZeroEtaBins.at(ieta+1)) break;
      }
      // ipt
      for (ipt=0; ipt<(int)_CAEPdUPlusPtBins.size()-1; ipt++){
        if (pT_raw>=_CAEPdUPlusPtBins.at(ipt)&&pT_raw<_CAEPdUPlusPtBins.at(ipt+1)) break;
      }
      // iupara
      for (iupara=0; iupara<(int)_CAEPdUPlusUParaBins.size()-1; iupara++){
        if (upara>=_CAEPdUPlusUParaBins.at(iupara)&&upara<_CAEPdUPlusUParaBins.at(iupara+1)) break;
      }
      // ilumi
      for (ilumi=0; ilumi<(int)_CAEPdUPlusLumiBins.size()-1; ilumi++){
        if (lumi>=_CAEPdUPlusLumiBins.at(ilumi)&&lumi<_CAEPdUPlusLumiBins.at(ilumi+1)) break;
      }
      // iset
      for (iset=0; iset<(int)_CAEPdUPlusSETBins.size()-1; iset++){
        if (set>=_CAEPdUPlusSETBins.at(iset)&&set<_CAEPdUPlusSETBins.at(iset+1)) break;
      }

      // protection
      if ( ieta>=_CAEPdUPlusEtaBins.size()-1 ||  ipt>=_CAEPdUPlusPtBins.size()-1 || iupara>=_CAEPdUPlusUParaBins.size()-1 ||
           ilumi>=_CAEPdUPlusLumiBins.size()-1 || iset>=_CAEPdUPlusSETBins.size()-1 ) {
        // predicted dE is zero
        energyDiffElecWithWithoutZBOverlay = 0.;
      }
      else {
        // smooth?
        if ( _CAEPSmoothdUPlus>0 ) {
          // toy check shows it is not necessay to smooth when dUPara>0
          energyDiffElecWithWithoutZBOverlay = 0.;
        }
        else {
          // get pars
          double par0 = _caep_duplus_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[5];
          double par1 = _caep_duplus_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[6];
          // calculate predicted dE
          energyDiffElecWithWithoutZBOverlay = par0+UParaCorr/sin(theta)*par1;
        }
      } // protection

    }
    // case dUPara=0:
    else {

      // find ieta, ipt, iupara, ilumi, iset
      int ieta, ipt, iupara, ilumi, iset;
      // ieta
      for (ieta=0; ieta<(int)_CAEPdUZeroEtaBins.size()-1; ieta++){
        if (eta_raw>=_CAEPdUZeroEtaBins.at(ieta)&&eta_raw<_CAEPdUZeroEtaBins.at(ieta+1)) break;
      }
      // ipt
      for (ipt=0; ipt<(int)_CAEPdUZeroPtBins.size()-1; ipt++){
        if (pT_raw>=_CAEPdUZeroPtBins.at(ipt)&&pT_raw<_CAEPdUZeroPtBins.at(ipt+1)) break;
      }
      // iupara
      for (iupara=0; iupara<(int)_CAEPdUZeroUParaBins.size()-1; iupara++){
        if (upara>=_CAEPdUZeroUParaBins.at(iupara)&&upara<_CAEPdUZeroUParaBins.at(iupara+1)) break;
      }
      // ilumi
      for (ilumi=0; ilumi<(int)_CAEPdUZeroLumiBins.size()-1; ilumi++){
        if (lumi>=_CAEPdUZeroLumiBins.at(ilumi)&&lumi<_CAEPdUZeroLumiBins.at(ilumi+1)) break;
      }
      // iset
      for (iset=0; iset<(int)_CAEPdUZeroSETBins.size()-1; iset++){
        if (set>=_CAEPdUZeroSETBins.at(iset)&&set<_CAEPdUZeroSETBins.at(iset+1)) break;
      }

      // protection
      if ( ieta>=_CAEPdUZeroEtaBins.size()-1 ||  ipt>=_CAEPdUZeroPtBins.size()-1 || iupara>=_CAEPdUZeroUParaBins.size()-1 ||
           ilumi>=_CAEPdUZeroLumiBins.size()-1 || iset>=_CAEPdUZeroSETBins.size()-1 ) {
        // predicted dE is zero
        energyDiffElecWithWithoutZBOverlay = 0.;
      }
      else {
        // smooth mothod 1
        // find nearest 3 points in (set, lumi, de) space,
        // using the 3 points define a plane function to 
        // caclulate dE.
        // Not really working well. (6 April 2011)
        if ( _CAEPSmoothdUZero==1 && (int)_CAEPdUZeroSETBins.size()-1>1) {
          // vectors store the index of the 3 points 
          vector<int> ilumi_min;
          vector<int> iset_min;

          // find nearest 2 points in set for the given ilumi
          for (int idx=0; idx<2; idx++){
            // push back ilumi as the lumi index of the 1st and 2nd point
            ilumi_min.push_back(ilumi);
            // find the nearest 2 set points
            for (int jset=0; jset<(int)_CAEPdUZeroSETBins.size()-1; jset++){
              if (idx==1&&jset==iset_min.at(0)) continue;
              if (iset_min.size()==idx) iset_min.push_back(jset);
              double jmset = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(jset)[4];
              double mset = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset_min.at(idx))[4];
              double jdR = fabs(set-jmset);
              double dR = fabs(set-mset);
              if (jdR<dR) {
                iset_min.at(idx) = jset;
              }
            }
          }
          // find the 3ed point of anther ilumi with one of the 2 iset
          for (int idx=0; idx<2; idx++){
            if (iset_min.size()==2) iset_min.push_back(iset_min.at(0));
            for (int jlumi=0; jlumi<(int)_CAEPdUZeroLumiBins.size()-1; jlumi++){
              if (jlumi==ilumi_min.at(0)) continue;
              if (ilumi_min.size()==2) ilumi_min.push_back(jlumi);
              double jmset = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(jlumi).at(iset_min.at(idx))[4];
              double mset = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi_min.at(2)).at(iset_min.at(2))[4];
              double jmlumi = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(jlumi).at(iset_min.at(idx))[3];
              double mlumi = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi_min.at(2)).at(iset_min.at(2))[3];
              double jdR = sqrt((set-jmset)*(set-jmset)+(lumi-jmlumi)*(lumi-jmlumi));
              double dR = sqrt((set-mset)*(set-mset)+(lumi-mlumi)*(lumi-mlumi));
              if (jdR<dR){
                ilumi_min.at(2) = jlumi;
                iset_min.at(2) = iset_min.at(idx);
              }
            }
          }

          // define a plane using the 3 points
          // | set -set1 lumi -lumi1 de -de1 |
          // | set2-set1 lumi2-lumi1 de2-de1 | = 0 
          // | set3-set1 lumi3-lumi1 de3-de1 |

          // calculate mde
          double xmlumi[3], xmset[3], xmde[3];
          for (int idx=0; idx<(int)iset_min.size(); idx++){
            xmlumi[idx] = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi_min.at(idx)).at(iset_min.at(idx))[3];
            xmset[idx]  = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi_min.at(idx)).at(iset_min.at(idx))[4];
            xmde[idx]   = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi_min.at(idx)).at(iset_min.at(idx))[5];
          }
          double D12 = (xmset[2]-xmset[1])*(xmlumi[3]-xmlumi[1]) - (xmset[3]-xmset[1])*(xmlumi[2]-xmlumi[1]);
          double D23 = ( xmde[3]- xmde[1])*(xmlumi[2]-xmlumi[1]) - ( xmde[2]- xmde[1])*(xmlumi[3]-xmlumi[1]);
          double D31 = ( xmde[2]- xmde[1])*( xmset[3]- xmset[1]) - ( xmde[3]- xmde[1])*( xmset[2]- xmset[1]);
          double mde = xmde[1] - (lumi-xmlumi[1])*D31/D12 - (set-xmset[1])*D23/D12;

          // if any 2 points are in the same border of either lumi or set binning range,
          // turn to use the average dE of the given bin.
          int n0ilumi=0, n0iset=0;
          for (int idx=0; idx<(int)iset_min.size(); idx++){
            if (iset_min.at(idx)==0) n0iset++;
            if (ilumi_min.at(idx)==0) n0ilumi++;
          }
          if (n0ilumi==2||n0iset==2) {
            mde = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[5];
          }

          energyDiffElecWithWithoutZBOverlay = mde;

        }
        // smooth method 2
        // merging bins:
        // The idea is to merge adjacent bins dynamically in all possible dimensions
        // to reduce the statistical fluctuation and to smooth the dE at the same 
        // time. If the statistics is not enough to have a fixed fine binning and small
        // fluctuation at the same time when making the model, this mothod is a good
        // remedy. It requires the binning to be very fine without worrying about 
        // statistical fluctuation, but store the errors of the mean dE in each bin.
        // The merging method is simply the weighted mean of the dE of the bins around,
        // using 1/error^2 as weight.
        else if (_CAEPSmoothdUZero==2){
          // range in binning to average out
          int nieta = (int)(_CAEPdUZeroEtaBins.size()-1)/10;
          nieta = min(min(nieta, ieta), max(0, (int)_CAEPdUZeroEtaBins.size()-2-ieta));
          int nipt = (int)(_CAEPdUZeroPtBins.size()-1)/10;
          nipt = min(min(nipt, ipt), max(0, (int)_CAEPdUZeroPtBins.size()-2-ipt));
          int niupara = (int)(_CAEPdUZeroUParaBins.size()-1)/5;
          niupara = min(min(niupara, iupara), max(0, (int)_CAEPdUZeroUParaBins.size()-2-iupara));
          int nilumi = (int)(_CAEPdUZeroLumiBins.size()-1)/10;
          nilumi = min(min(nilumi, ilumi), max(0, (int)_CAEPdUZeroLumiBins.size()-2-ilumi));
          int niset = (int)(_CAEPdUZeroSETBins.size()-1)/10;
          niset = min(min(niset, iset), max(0, (int)_CAEPdUZeroSETBins.size()-2-iset));

          // calculate weighted mean
          double sum_mde = 0;
          double sum_merrde = 0;
          for (int jeta=ieta-nieta; jeta<=ieta+nieta; jeta++){
            for (int jpt=ipt-nipt; jpt<=ipt+nipt; jpt++){
              for (int jupara=iupara-niupara; jupara<=iupara+niupara; jupara++){
                for (int jlumi=ilumi-nilumi; jlumi<=ilumi+nilumi; jlumi++){
                  for (int jset=iset-niset; jset<=iset+niset; jset++){
                    double mde = _caep_duzero_par_vec.at(jeta).at(jpt).at(jupara).at(jlumi).at(jset)[5];
                    double merrde = _caep_duzero_par_vec.at(jeta).at(jpt).at(jupara).at(jlumi).at(jset)[11];
                    if (fabs(mde)>0.&&fabs(merrde)>0.){
                      sum_mde += mde/(merrde*merrde);
                      sum_merrde += 1./(merrde*merrde);
                    }
                  } // jset
                } // jlumi
              } // jupara
            } // jpt
          } // jeta

          double mde = 0.;
          if (fabs(sum_mde)>0.&&fabs(sum_merrde)>0.){
            mde = sum_mde/sum_merrde;
          }

          if (false){
            cout << "------------" << endl;
            cout << ieta << " " << ipt << " " << iupara << " " << ilumi << " " << iset << endl;
            cout << nieta << " " << nipt << " " << niupara << " " << nilumi << " " << niset << endl;
            cout << sum_mde << " " << sum_merrde << " " << mde << endl;
          }

          energyDiffElecWithWithoutZBOverlay = mde;

        }
        // smooth method 3
        // straight line smooth in Pt, and merging bins in SET and Lumi:
        //  This method 3 is desiged with another Pt bin below 25GeV in the model, and very fine binning in SET and 
        //  Lumi. Smooth Pt dependence using a straight line, if the bin is empty, merge the adjacent bins in SET and Lumi
        //  for the same Pt bin.
        else if (_CAEPSmoothdUZero==3){
          double mde = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[5];
          if ((int)_CAEPdUZeroPtBins.size()-1>1) {
            // find nearest 2 pt bins
            int npt[2];
            if (ipt==0) {
              npt[0] = ipt;
              npt[1] = ipt+1;
            }
            else if (ipt==(int)_CAEPdUZeroPtBins.size()-2){
              npt[0] = ipt;
              npt[1] = ipt-1;
            }
            else{
              double mpt  = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[1];
              if ( pT_raw<mpt ) {
                npt[0] = ipt;
                npt[1] = ipt-1;
              }
              else {
                npt[0] = ipt;
                npt[1] = ipt+1;
              }
            }

            // get mde and mpt of the 2 pt bins
            double mpt1 =  _caep_duzero_par_vec.at(ieta).at(npt[0]).at(iupara).at(ilumi).at(iset)[1];
            double mpt2 =  _caep_duzero_par_vec.at(ieta).at(npt[1]).at(iupara).at(ilumi).at(iset)[1];
            double mde1 =  _caep_duzero_par_vec.at(ieta).at(npt[0]).at(iupara).at(ilumi).at(iset)[5];
            double mde2 =  _caep_duzero_par_vec.at(ieta).at(npt[1]).at(iupara).at(ilumi).at(iset)[5];

            // check if all the 4 values are not empty
            if ( fabs(mde1)<1e-10 || fabs(mde2)<1e-10 || mpt1<1e-10 || mpt2<1e-10 || fabs(mpt2-mpt1)<1e-10 ) {
              //std::cout << " ERROR : Pt Bin " << npt[0] << " and/or " << npt[1] << " are empty! Try to merge bins in SET and Lumi!" << std::endl;

              // merge bins in set and lumi for the 2 pt bins
              for (int nstep=1; nstep<std::max((int)_CAEPdUZeroLumiBins.size()-1,(int)_CAEPdUZeroSETBins.size()-1); nstep++){
                double sum_mde[2] = {0, 0};
                double sum_merrde[2] = {0, 0};
                double sum_mpt[2] = {0, 0};
                double sum_merrpt[2] = {0, 0};
                for (int iipt=0; iipt<2; iipt++){
                  for (int jlumi=ilumi-nstep; jlumi<=ilumi+nstep; jlumi++){
                    for (int jset=iset-nstep; jset<=iset+nstep; jset++){
                      if (jlumi<0 || jset<0 || jlumi>(int)_CAEPdUZeroLumiBins.size()-2 || jset>(int)_CAEPdUZeroSETBins.size()-2){
                        continue;
                      }
                      double amde = _caep_duzero_par_vec.at(ieta).at(npt[iipt]).at(iupara).at(jlumi).at(jset)[5];
                      double amerrde = _caep_duzero_par_vec.at(ieta).at(npt[iipt]).at(iupara).at(jlumi).at(jset)[11];
                      double ampt =  _caep_duzero_par_vec.at(ieta).at(npt[iipt]).at(iupara).at(jlumi).at(jset)[1];
                      double amerrpt = _caep_duzero_par_vec.at(ieta).at(npt[1]).at(iupara).at(ilumi).at(iset)[7];
                      if (fabs(amde)<1e-10 || fabs(amerrde)<1e-10 || ampt<1e-10 || amerrpt<1e-10) {
                        continue;
                      }
                      sum_mde[iipt] += amde/(amerrde*amerrde);
                      sum_merrde[iipt] += 1./(amerrde*amerrde);
                      sum_mpt[iipt] += ampt/(amerrpt*amerrpt);
                      sum_merrpt[iipt] += 1./(amerrpt*amerrpt);
                    }// jset
                  }// jlumi 
                }// iipt

                // weighted mean
                double nmpt[2] = {0, 0};
                double nmde[2] = {0, 0};
                for (int iipt=0; iipt<2; iipt++){
                  if (fabs(sum_mde[iipt])>0.&&fabs(sum_merrde[iipt])>0.&&fabs(sum_mpt[iipt])>0.&&fabs(sum_merrpt[iipt])>0.){
                    nmde[iipt] = sum_mde[iipt]/sum_merrde[iipt];
                    nmpt[iipt] = sum_mpt[iipt]/sum_merrpt[iipt];
                  }
                }

                // if not empty now, calculate mde and break the loop
                if (fabs(nmpt[0])>0. && fabs(nmpt[1])>0. && fabs(nmde[0])>0. && fabs(nmde[1])>0.) {
                  mde = nmde[0] + (pT_raw-nmpt[0])*(nmde[1]-nmde[0])/(nmpt[1]-nmpt[0]);
                  break;
                } // if (fabs..

              }// nstep

              // if mde is still empty, print an error
              //if (fabs(mde)<1e-10){
              //  std::cout << "ERROR: merging bins doesn't help." << std::endl;
              //}
            }
            else {
              mde = mde1 + (pT_raw-mpt1)*(mde2-mde1)/(mpt2-mpt1);
            } // if ( bins are empty ) merge adjacent bins; else ...

          } // if ((int)_CAEPdUZeroSETBins.size()-1<2  ...) ... else ...

          energyDiffElecWithWithoutZBOverlay = mde;

        }
        // no smooth
        else {   
          // get mean dE
          double mde = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[5];
          // predicted dE is mean dE
          energyDiffElecWithWithoutZBOverlay = mde;
        } // smooth options

      } // protection


    } // if dUPara>0 ... else dUPara=0 

    // fudge UPara correction to EM cone, if requested
    energyDiffElecWithWithoutZBOverlay*=_EnergySim_ElecWindowFudge;

    // also apply Energy Scale on delta E correction
    if (_ApplyScaleOnDeltaE) {
      energyDiffElecWithWithoutZBOverlay *= _scale_CC;
    }

    energy_after_ElecSim_ElecWindow = pE_raw + energyDiffElecWithWithoutZBOverlay;
    _energyDiffElec = energyDiffElecWithWithoutZBOverlay;

  }
  else if (_EnergySim_ElecWindowOption==6){

    // case dUPara>0: 
    if ( UParaCorr>0.001 ) {

      // find ieta, ipt, iupara, ilumi, iset 
      int ieta, ipt, iupara, ilumi, iset;
 
      if(_runNumber < _middlerunnumber) {
        // ieta
        for (ieta=0; ieta<(int)_CAEPdUZeroEtaBins.size()-1; ieta++){
          if (eta_raw>=_CAEPdUZeroEtaBins.at(ieta)&&eta_raw<_CAEPdUZeroEtaBins.at(ieta+1)) break;
        }
        // ipt
        for (ipt=0; ipt<(int)_CAEPdUPlusPtBins.size()-1; ipt++){
          if (pT_raw>=_CAEPdUPlusPtBins.at(ipt)&&pT_raw<_CAEPdUPlusPtBins.at(ipt+1)) break;
        }
        // iupara
        for (iupara=0; iupara<(int)_CAEPdUPlusUParaBins.size()-1; iupara++){
          if (upara>=_CAEPdUPlusUParaBins.at(iupara)&&upara<_CAEPdUPlusUParaBins.at(iupara+1)) break;
        }
        // ilumi
        for (ilumi=0; ilumi<(int)_CAEPdUPlusLumiBins.size()-1; ilumi++){
          if (lumi>=_CAEPdUPlusLumiBins.at(ilumi)&&lumi<_CAEPdUPlusLumiBins.at(ilumi+1)) break;
        }
        // iset
        for (iset=0; iset<(int)_CAEPdUPlusSETBins.size()-1; iset++){
          if (set>=_CAEPdUPlusSETBins.at(iset)&&set<_CAEPdUPlusSETBins.at(iset+1)) break;
        }

        // protection 
        if ( ieta>=_CAEPdUPlusEtaBins.size()-1 ||  ipt>=_CAEPdUPlusPtBins.size()-1 || iupara>=_CAEPdUPlusUParaBins.size()-1 ||
             ilumi>=_CAEPdUPlusLumiBins.size()-1 || iset>=_CAEPdUPlusSETBins.size()-1 ) {
          // predicted dE is zero
          energyDiffElecWithWithoutZBOverlay = 0.;
        }
        else {
          // get pars
          double par0 = _caep_duplus_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[5];
          double par1 = _caep_duplus_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[6];
          // calculate predicted dE
          energyDiffElecWithWithoutZBOverlay = par0+UParaCorr/sin(theta)*par1;
        } // protection
      }
      else {
        // ieta
        for (ieta=0; ieta<(int)_CAEPdUZeroEtaBins2.size()-1; ieta++){
          if (eta_raw>=_CAEPdUZeroEtaBins2.at(ieta)&&eta_raw<_CAEPdUZeroEtaBins2.at(ieta+1)) break;
        }
        // ipt
        for (ipt=0; ipt<(int)_CAEPdUPlusPtBins2.size()-1; ipt++){
          if (pT_raw>=_CAEPdUPlusPtBins2.at(ipt)&&pT_raw<_CAEPdUPlusPtBins2.at(ipt+1)) break;
        }
        // iupara
        for (iupara=0; iupara<(int)_CAEPdUPlusUParaBins2.size()-1; iupara++){
          if (upara>=_CAEPdUPlusUParaBins2.at(iupara)&&upara<_CAEPdUPlusUParaBins2.at(iupara+1)) break;
        }
        // ilumi
        for (ilumi=0; ilumi<(int)_CAEPdUPlusLumiBins2.size()-1; ilumi++){
          if (lumi>=_CAEPdUPlusLumiBins2.at(ilumi)&&lumi<_CAEPdUPlusLumiBins2.at(ilumi+1)) break;
        }
        // iset
        for (iset=0; iset<(int)_CAEPdUPlusSETBins2.size()-1; iset++){
          if (set>=_CAEPdUPlusSETBins2.at(iset)&&set<_CAEPdUPlusSETBins2.at(iset+1)) break;
        }

        // protection 
        if ( ieta>=_CAEPdUPlusEtaBins2.size()-1 ||  ipt>=_CAEPdUPlusPtBins2.size()-1 || iupara>=_CAEPdUPlusUParaBins2.size()-1 ||
             ilumi>=_CAEPdUPlusLumiBins2.size()-1 || iset>=_CAEPdUPlusSETBins2.size()-1 ) {
          // predicted dE is zero
          energyDiffElecWithWithoutZBOverlay = 0.;
        }
        else {
          // get pars
          double par0 = _caep_duplus_par_vec2.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[5];
          double par1 = _caep_duplus_par_vec2.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[6];
          // calculate predicted dE
          energyDiffElecWithWithoutZBOverlay = par0+UParaCorr/sin(theta)*par1;
        } // protection
      }
    }
    // case dUPara=0:
    else {
      // find ieta, ipt, iupara, ilumi, iset
      int ieta, ipt, iupara, ilumi, iset;

      if(_runNumber < _middlerunnumber) {
        // ieta
        for (ieta=0; ieta<(int)_CAEPdUZeroEtaBins.size()-1; ieta++){
          if (eta_raw>=_CAEPdUZeroEtaBins.at(ieta)&&eta_raw<_CAEPdUZeroEtaBins.at(ieta+1)) break;
        }
        // ipt
        for (ipt=0; ipt<(int)_CAEPdUZeroPtBins.size()-1; ipt++){
          if (pT_raw>=_CAEPdUZeroPtBins.at(ipt)&&pT_raw<_CAEPdUZeroPtBins.at(ipt+1)) break;
        }
        // iupara
        for (iupara=0; iupara<(int)_CAEPdUZeroUParaBins.size()-1; iupara++){
          if (upara>=_CAEPdUZeroUParaBins.at(iupara)&&upara<_CAEPdUZeroUParaBins.at(iupara+1)) break;
        }
        // ilumi
        for (ilumi=0; ilumi<(int)_CAEPdUZeroLumiBins.size()-1; ilumi++){
          if (lumi>=_CAEPdUZeroLumiBins.at(ilumi)&&lumi<_CAEPdUZeroLumiBins.at(ilumi+1)) break;
        }
        // iset
        for (iset=0; iset<(int)_CAEPdUZeroSETBins.size()-1; iset++){
          if (set>=_CAEPdUZeroSETBins.at(iset)&&set<_CAEPdUZeroSETBins.at(iset+1)) break;
        }
      }
      else {
        // ieta
        for (ieta=0; ieta<(int)_CAEPdUZeroEtaBins2.size()-1; ieta++){
          if (eta_raw>=_CAEPdUZeroEtaBins2.at(ieta)&&eta_raw<_CAEPdUZeroEtaBins2.at(ieta+1)) break;
        }
        // ipt
        for (ipt=0; ipt<(int)_CAEPdUZeroPtBins2.size()-1; ipt++){
          if (pT_raw>=_CAEPdUZeroPtBins2.at(ipt)&&pT_raw<_CAEPdUZeroPtBins2.at(ipt+1)) break;
        }
        // iupara
        for (iupara=0; iupara<(int)_CAEPdUZeroUParaBins2.size()-1; iupara++){
          if (upara>=_CAEPdUZeroUParaBins2.at(iupara)&&upara<_CAEPdUZeroUParaBins2.at(iupara+1)) break;
        }
        // ilumi
        for (ilumi=0; ilumi<(int)_CAEPdUZeroLumiBins2.size()-1; ilumi++){
          if (lumi>=_CAEPdUZeroLumiBins2.at(ilumi)&&lumi<_CAEPdUZeroLumiBins2.at(ilumi+1)) break;
        }
        // iset
        for (iset=0; iset<(int)_CAEPdUZeroSETBins2.size()-1; iset++){
          if (set>=_CAEPdUZeroSETBins2.at(iset)&&set<_CAEPdUZeroSETBins2.at(iset+1)) break;
        }
      }

      // smooth
     if(_runNumber < _middlerunnumber) { 
        // protection
        if ( ieta>=_CAEPdUZeroEtaBins.size()-1 ||  ipt>=_CAEPdUZeroPtBins.size()-1 || iupara>=_CAEPdUZeroUParaBins.size()-1 ||
             ilumi>=_CAEPdUZeroLumiBins.size()-1 || iset>=_CAEPdUZeroSETBins.size()-1 ) {
          // predicted dE is zero
          energyDiffElecWithWithoutZBOverlay = 0.;
        }
        else {
          // smooth method 3
          // straight line smooth in Pt, and merging bins in SET and Lumi:
          //  This method 3 is desiged with another Pt bin below 25GeV in the model, and very fine binning in SET and 
          //  Lumi. Smooth Pt dependence using a straight line, if the bin is empty, merge the adjacent bins in SET and Lumi
          //  for the same Pt bin.
          double mde = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[5];
          if ((int)_CAEPdUZeroPtBins.size()-1>1) {
            // find nearest 2 pt bins
            int npt[2];
            if (ipt==0) {
              npt[0] = ipt;
              npt[1] = ipt+1;
            }
            else if (ipt==(int)_CAEPdUZeroPtBins.size()-2){
              npt[0] = ipt;
              npt[1] = ipt-1;
            }
            else{
              double mpt  = _caep_duzero_par_vec.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[1];
              if ( pT_raw<mpt ) {
                npt[0] = ipt;
                npt[1] = ipt-1;
              }
              else {
                npt[0] = ipt;
                npt[1] = ipt+1;
              }
            }

            // get mde and mpt of the 2 pt bins
            double mpt1 =  _caep_duzero_par_vec.at(ieta).at(npt[0]).at(iupara).at(ilumi).at(iset)[1];
            double mpt2 =  _caep_duzero_par_vec.at(ieta).at(npt[1]).at(iupara).at(ilumi).at(iset)[1];
            double mde1 =  _caep_duzero_par_vec.at(ieta).at(npt[0]).at(iupara).at(ilumi).at(iset)[5];
            double mde2 =  _caep_duzero_par_vec.at(ieta).at(npt[1]).at(iupara).at(ilumi).at(iset)[5];

            // check if all the 4 values are not empty
            if ( fabs(mde1)<1e-10 || fabs(mde2)<1e-10 || mpt1<1e-10 || mpt2<1e-10 || fabs(mpt2-mpt1)<1e-10 ) {
              //std::cout << " ERROR : Pt Bin " << npt[0] << " and/or " << npt[1] << " are empty! Try to merge bins in SET and Lumi!" << std::endl;

              // merge bins in set and lumi for the 2 pt bins
              for (int nstep=1; nstep<std::max((int)_CAEPdUZeroLumiBins.size()-1,(int)_CAEPdUZeroSETBins.size()-1); nstep++){
                double sum_mde[2] = {0, 0};
                double sum_merrde[2] = {0, 0};
                double sum_mpt[2] = {0, 0};
                double sum_merrpt[2] = {0, 0};
                for (int iipt=0; iipt<2; iipt++){
                  for (int jlumi=ilumi-nstep; jlumi<=ilumi+nstep; jlumi++){
                    for (int jset=iset-nstep; jset<=iset+nstep; jset++){
                      if (jlumi<0 || jset<0 || jlumi>(int)_CAEPdUZeroLumiBins.size()-2 || jset>(int)_CAEPdUZeroSETBins.size()-2){
                        continue;
                      }
                      double amde = _caep_duzero_par_vec.at(ieta).at(npt[iipt]).at(iupara).at(jlumi).at(jset)[5];
                      double amerrde = _caep_duzero_par_vec.at(ieta).at(npt[iipt]).at(iupara).at(jlumi).at(jset)[11];
                      double ampt =  _caep_duzero_par_vec.at(ieta).at(npt[iipt]).at(iupara).at(jlumi).at(jset)[1];
                      double amerrpt = _caep_duzero_par_vec.at(ieta).at(npt[1]).at(iupara).at(ilumi).at(iset)[7];
                      if (fabs(amde)<1e-10 || fabs(amerrde)<1e-10 || ampt<1e-10 || amerrpt<1e-10) {
                        continue;
                      }
                      sum_mde[iipt] += amde/(amerrde*amerrde);
                      sum_merrde[iipt] += 1./(amerrde*amerrde);
                      sum_mpt[iipt] += ampt/(amerrpt*amerrpt);
                      sum_merrpt[iipt] += 1./(amerrpt*amerrpt);
                    }// jset
                  }// jlumi 
                }// iipt

                // weighted mean
                double nmpt[2] = {0, 0};
                double nmde[2] = {0, 0};
                for (int iipt=0; iipt<2; iipt++){
                  if (fabs(sum_mde[iipt])>0.&&fabs(sum_merrde[iipt])>0.&&fabs(sum_mpt[iipt])>0.&&fabs(sum_merrpt[iipt])>0.){
                    nmde[iipt] = sum_mde[iipt]/sum_merrde[iipt];
                    nmpt[iipt] = sum_mpt[iipt]/sum_merrpt[iipt];
                  }
                }
  
                // if not empty now, calculate mde and break the loop
                if (fabs(nmpt[0])>0. && fabs(nmpt[1])>0. && fabs(nmde[0])>0. && fabs(nmde[1])>0.) {
                  mde = nmde[0] + (pT_raw-nmpt[0])*(nmde[1]-nmde[0])/(nmpt[1]-nmpt[0]);
                  break;
                } // if (fabs..
  
              }// nstep

            }
            else {
              mde = mde1 + (pT_raw-mpt1)*(mde2-mde1)/(mpt2-mpt1);
            } // if ( bins are empty ) merge adjacent bins; else ...
          } // if ((int)_CAEPdUZeroSETBins.size()-1<2  ...) ... else ...
          energyDiffElecWithWithoutZBOverlay = mde;
        } // protection
      }
      else {
        // run2b4
        // protection
        if ( ieta>=_CAEPdUZeroEtaBins2.size()-1 ||  ipt>=_CAEPdUZeroPtBins2.size()-1 || iupara>=_CAEPdUZeroUParaBins2.size()-1 ||
             ilumi>=_CAEPdUZeroLumiBins2.size()-1 || iset>=_CAEPdUZeroSETBins2.size()-1 ) {
          // predicted dE is zero
          energyDiffElecWithWithoutZBOverlay = 0.;
        }
        else {
          // smooth method 3
          // straight line smooth in Pt, and merging bins in SET and Lumi:
          //  This method 3 is desiged with another Pt bin below 25GeV in the model, and very fine binning in SET and 
          //  Lumi. Smooth Pt dependence using a straight line, if the bin is empty, merge the adjacent bins in SET and Lumi
          //  for the same Pt bin.
          double mde = _caep_duzero_par_vec2.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[5];
          if ((int)_CAEPdUZeroPtBins2.size()-1>1) {
            // find nearest 2 pt bins
            int npt[2];
            if (ipt==0) {
              npt[0] = ipt;
              npt[1] = ipt+1;
            }
            else if (ipt==(int)_CAEPdUZeroPtBins2.size()-2){
              npt[0] = ipt;
              npt[1] = ipt-1;
            }
            else{
              double mpt  = _caep_duzero_par_vec2.at(ieta).at(ipt).at(iupara).at(ilumi).at(iset)[1];
              if ( pT_raw<mpt ) {
                npt[0] = ipt;
                npt[1] = ipt-1;
              }
              else {
                npt[0] = ipt;
                npt[1] = ipt+1;
              }
            }

            // get mde and mpt of the 2 pt bins
            double mpt1 =  _caep_duzero_par_vec2.at(ieta).at(npt[0]).at(iupara).at(ilumi).at(iset)[1];
            double mpt2 =  _caep_duzero_par_vec2.at(ieta).at(npt[1]).at(iupara).at(ilumi).at(iset)[1];
            double mde1 =  _caep_duzero_par_vec2.at(ieta).at(npt[0]).at(iupara).at(ilumi).at(iset)[5];
            double mde2 =  _caep_duzero_par_vec2.at(ieta).at(npt[1]).at(iupara).at(ilumi).at(iset)[5];

            // check if all the 4 values are not empty
            if ( fabs(mde1)<1e-10 || fabs(mde2)<1e-10 || mpt1<1e-10 || mpt2<1e-10 || fabs(mpt2-mpt1)<1e-10 ) {
              //std::cout << " ERROR : Pt Bin " << npt[0] << " and/or " << npt[1] << " are empty! Try to merge bins in SET and Lumi!" << std::endl;

              // merge bins in set and lumi for the 2 pt bins
              for (int nstep=1; nstep<std::max((int)_CAEPdUZeroLumiBins2.size()-1,(int)_CAEPdUZeroSETBins2.size()-1); nstep++){
                double sum_mde[2] = {0, 0};
                double sum_merrde[2] = {0, 0};
                double sum_mpt[2] = {0, 0};
                double sum_merrpt[2] = {0, 0};
                for (int iipt=0; iipt<2; iipt++){
                  for (int jlumi=ilumi-nstep; jlumi<=ilumi+nstep; jlumi++){
                    for (int jset=iset-nstep; jset<=iset+nstep; jset++){
                      if (jlumi<0 || jset<0 || jlumi>(int)_CAEPdUZeroLumiBins2.size()-2 || jset>(int)_CAEPdUZeroSETBins2.size()-2){
                        continue;
                      }
                      double amde = _caep_duzero_par_vec2.at(ieta).at(npt[iipt]).at(iupara).at(jlumi).at(jset)[5];
                      double amerrde = _caep_duzero_par_vec2.at(ieta).at(npt[iipt]).at(iupara).at(jlumi).at(jset)[11];
                      double ampt =  _caep_duzero_par_vec2.at(ieta).at(npt[iipt]).at(iupara).at(jlumi).at(jset)[1];
                      double amerrpt = _caep_duzero_par_vec2.at(ieta).at(npt[1]).at(iupara).at(ilumi).at(iset)[7];
                      if (fabs(amde)<1e-10 || fabs(amerrde)<1e-10 || ampt<1e-10 || amerrpt<1e-10) {
                        continue;
                      }
                      sum_mde[iipt] += amde/(amerrde*amerrde);
                      sum_merrde[iipt] += 1./(amerrde*amerrde);
                      sum_mpt[iipt] += ampt/(amerrpt*amerrpt);
                      sum_merrpt[iipt] += 1./(amerrpt*amerrpt);
                    }// jset
                  }// jlumi 
                }// iipt

                // weighted mean
                double nmpt[2] = {0, 0};
                double nmde[2] = {0, 0};
                for (int iipt=0; iipt<2; iipt++){
                  if (fabs(sum_mde[iipt])>0.&&fabs(sum_merrde[iipt])>0.&&fabs(sum_mpt[iipt])>0.&&fabs(sum_merrpt[iipt])>0.){
                    nmde[iipt] = sum_mde[iipt]/sum_merrde[iipt];
                    nmpt[iipt] = sum_mpt[iipt]/sum_merrpt[iipt];
                  }
                }

                // if not empty now, calculate mde and break the loop
                if (fabs(nmpt[0])>0. && fabs(nmpt[1])>0. && fabs(nmde[0])>0. && fabs(nmde[1])>0.) {
                  mde = nmde[0] + (pT_raw-nmpt[0])*(nmde[1]-nmde[0])/(nmpt[1]-nmpt[0]);
                  break;
                } // if (fabs..

              }// nstep

            }
            else {
              mde = mde1 + (pT_raw-mpt1)*(mde2-mde1)/(mpt2-mpt1);
            } // if ( bins are empty ) merge adjacent bins; else ...
          } // if ((int)_CAEPdUZeroSETBins.size()-1<2  ...) ... else ...
          energyDiffElecWithWithoutZBOverlay = mde;
        } // protection

      } // if (run3); else (run4) ..    

    } // if dUPara>0 ... else dUPara=0 

    // fudge UPara correction to EM cone, if requested
    energyDiffElecWithWithoutZBOverlay*=_EnergySim_ElecWindowFudge;

    // also apply Energy Scale on delta E correction
    if (_ApplyScaleOnDeltaE) {
      energyDiffElecWithWithoutZBOverlay *= _scale_CC;
    }

    energy_after_ElecSim_ElecWindow = pE_raw + energyDiffElecWithWithoutZBOverlay;
    _energyDiffElec = energyDiffElecWithWithoutZBOverlay;

  } // end of EnergySim_ElecWindowOption == 6
  else {
    cout << " EnergySim_ElecWindowOption should be 1, 2, 3, 4, 5 or 6 !" << endl;
    exit(-1);
  }

  // if we wish to fudge the UParaCorr (as used to modify the recoil verctor), then we do it here (at the end, after the evaluation of the correction to the electron itself),
  // i.e. the intent is to fudage the effect on the recoil only (the effect on the EM cone has a separate fudging factor)
  UParaCorr*=_UParaCorrFudge;


  //
  //         End of Run Ib method
  /////////////////////////////////////////////////////////

  // set underlying event corrections and ZSUP effects here
   part.SetEnergyEtaPhi(energy_after_ElecSim_ElecWindow, eta_raw, phi_raw);
   part.SetRawpTUnderElecWindow(rawpTUnderElecWindow);
   part.SetUParaCorr(UParaCorr);
   part.SetDeltaZSUP(Delta_ZSUP);
   part.SetEnergyLeakage(EnergyLeakage);
   part.SetEnergyDiffElecWithWithoutZBOverlay(energyDiffElecWithWithoutZBOverlay);
 
   return 1;
}

// for energy scale and resolution studies, we first scale and smear electrons and then make the underlying event correction
// since the underlying event correction for each electron is the same, 
// will not do the real calculation for each energy scale and resolution parameters
// this only works for CC region
// rawpTUnderElecWindow is used for _EnergySim_ElecWindowOption =0 and energy_diff is used for _EnergySim_ElecWindowOption = 1
void EMSmear::CorrectEnergyUnderElecWindow(double ElecEnergy, double ElecEta, double rawpTUnderElecWindow, double energyDiffWithWithoutZBOverlay, double &corrElecEnergy) {
  if(_EnergySim_ElecWindowOption == 0) {
    double ElecTheta = 2.*atan(exp(-ElecEta));
    corrElecEnergy = ElecEnergy + rawpTUnderElecWindow/sin(ElecTheta) - _ZSUP_CC_Elec_NoMBOverlay;
  } else {
    corrElecEnergy = ElecEnergy + energyDiffWithWithoutZBOverlay;
  }
}

void EMSmear::fillSmearHistograms(PMCSEMObj &gen, PMCSEMObj &smear) {
  _histos->Fill1D("h_smearedEM_DeltaPt", smear.ppt() - gen.ppt());  
  _histos->Fill1D("h_smearedEM_DeltaEta",smear.peta() - gen.peta());
  _histos->Fill1D("h_smearedEM_DeltaPhi",kinem::delta_phi(smear.pphi(),gen.pphi()));
  _histos->Fill1D("h_smearedEM_DeltaDetEta",smear.deteta() - gen.deteta());
  _histos->Fill1D("h_smearedEM_DeltaDetPhi",kinem::delta_phi(smear.detphi(),gen.detphi()));

  _histos->Fill2D("h_smearedEM_DeltaPt_v_Pt",gen.ppt(),smear.ppt() - gen.ppt());
  _histos->Fill2D("h_smearedEM_DeltaEta_v_Eta",gen.peta(),smear.peta() - gen.peta());
  _histos->Fill2D("h_smearedEM_DeltaPhi_v_Phi",gen.pphi(),kinem::delta_phi(smear.pphi(),gen.pphi()));
  _histos->Fill2D("h_smearedEM_DeltaDetEta_v_DetEta",gen.deteta(),smear.deteta() - gen.deteta());
  _histos->Fill2D("h_smearedEM_DeltaDetPhi_v_DetPhi",gen.detphi(),kinem::delta_phi(smear.detphi(),gen.detphi()));

  _histos->Fill2D("h_smearedEM_GenPt_v_SmearPt",gen.ppt(),smear.ppt());
  _histos->Fill2D("h_smearedEM_GenEta_v_SmearEta",gen.peta(),smear.peta());
  _histos->Fill2D("h_smearedEM_GenPhi_v_SmearPhi",gen.pphi(),smear.pphi());
  _histos->Fill2D("h_smearedEM_GenDetEta_v_SmearDetEta",gen.deteta(),smear.deteta());
  _histos->Fill2D("h_smearedEM_GenDetPhi_v_SmearDetPhi",gen.detphi(),smear.detphi());
}

//
// smear physics eta and phi according to tracker resolutions
//
void EMSmear::SmearPhysEtaPhi(PMCSEMObj& part, double etares_phy, double phires_phy, TRandom3 *dummy, 
			      double& phyeta_smeared, double& phyphi_smeared) {
  double eta_gen = part.peta(), phi_gen = part.pphi();
  SmearPhysEtaPhi(eta_gen, phi_gen, etares_phy, phires_phy, dummy, phyeta_smeared, phyphi_smeared);
}

void EMSmear::SmearPhysEtaPhi(double eta_gen, double phi_gen, 
			      double etares_phy, double phires_phy, TRandom3 *dummy, 
			      double& phyeta_smeared, double& phyphi_smeared) {
  phyeta_smeared = eta_gen + dummy->Gaus(0., 1.)*etares_phy;

  phyphi_smeared = phi_gen + dummy->Gaus(0., 1.)*phires_phy;

  if(phyphi_smeared>2*TMath::Pi())  phyphi_smeared -= 2*TMath::Pi();
  if(phyphi_smeared<0.)             phyphi_smeared += 2.*TMath::Pi();
}


void EMSmear::SmearPhysEtaPhiHengne(double eta_gen, double phi_gen,
                                    double etares_phy, double phires_phy, TRandom3 *dummy,
                                    double& phyeta_smeared, double& phyphi_smeared, double ppid) {
  // smear phyeta
  phyeta_smeared = eta_gen + dummy->Gaus(0., 1.)*etares_phy;

  // smear phyphi
  double delta_phi(0);
  // positron
  if ((ppid==-11) || (ppid==-12)){
    delta_phi = ((PMCSTH1*)(_hPhyPhiResoPos))->GetRandom(dummy->Rndm());
  }
  // electron
  else if ((ppid==11) || (ppid==12)) {
    delta_phi = ((PMCSTH1*)(_hPhyPhiResoEle))->GetRandom(dummy->Rndm());
  }
  // photon
  else {
    delta_phi = dummy->Gaus(0., 1.)*phires_phy;
  }
  // smeared phi
  phyphi_smeared = phi_gen + delta_phi;  
  phyphi_smeared = TVector2::Phi_0_2pi(phyphi_smeared);

}

//
// smear detector eta and phi according to calorimeter resolutions
//
void EMSmear::SmearDetEtaPhi(PMCSEMObj& part, double etares_det, double phires_det, TRandom3 *dummy, 
			     double& deteta_smeared, double& detphi_smeared, bool& lost) {
  double deteta_gen = part.deteta(), detphi_gen = part.detphi();
  SmearDetEtaPhi(deteta_gen, detphi_gen, etares_det, phires_det, dummy, deteta_smeared, detphi_smeared, lost, part.ppid());
}

void EMSmear::SmearDetEtaPhi(double deteta_gen, double detphi_gen, double etares_det, double phires_det, TRandom3 *dummy, 
			     double& deteta_smeared, double& detphi_smeared, bool& lost, double id ) {

  // detector eta smearing
  deteta_smeared = deteta_gen + dummy->Gaus(0., 1.)*etares_det;
  lost = false;
  // apply phi module shift corrections on CC electrons
  if(_ApplyPhiModCorrection && (fabs(deteta_smeared)<1.3)) {

    // first check whether it will pass the phi crack efficiency
    // NOTE: phi crack efficiency is NOW applied here if _ApplyPhiModEfficiency is set to true

    // for events pass phi crack efficiency, the electron detector phi will be shifted;
    // for events not pass phi crack efficiency, the electron detector phi will be modified so that
    // later will be removed by applying phi module cut (done inside PMCSEMObj::IsCC function)

    double val=1., err=0.;    
    double fracmod = fmod(detphi_gen*16/TMath::Pi(),1.0);
    Bool_t status = PHistoTools::getBinValues(_hPhiCrackEff, fracmod, val, err);
    if(!status) cout<<"Warning: overflow in "<<_hPhiCrackEff->GetName() << " fracmod="
		    <<fracmod<<endl;

    //if pass phi crack efficiency
    if((dummy->Uniform(0., 1.) <= val)) {      
      // get phi module shift
      Int_t xbin = _hPhiModShift->GetXaxis()->FindBin(fracmod);
      double val = _hPhiModShiftSlice[xbin]->GetRandom();
      detphi_smeared = detphi_gen + val*TMath::Pi()/16;
    } else { 
      
      // if electron inside crack region or in fiducial region but fails the phimod efficiency, 
      // will not smear detector phi, but will make smeared electron detphi has 
      // fmod(detphi_smeared*16/TMath::Pi(),1.0) == 0 and 
      // these electrons will be remove later by fiducial reguirement
      // if you just check the detphi_smear without fiducial requirement, you may find many events with phimod=0

      if(_ApplyPhiModEfficiency) {
	detphi_smeared = detphi_gen - fracmod*TMath::Pi()/16;
	lost=true;
      } else detphi_smeared = detphi_gen;

    } // not pass phi crack efficiency    
  } else {   // apply detector phi resolution, no phimod shift applied
    detphi_smeared = detphi_gen + dummy->Gaus(0., 1.)*phires_det;
  }
    
  if(detphi_smeared>2*TMath::Pi())  detphi_smeared -= 2*TMath::Pi();
  if(detphi_smeared<0.) detphi_smeared += 2.*TMath::Pi();

}//end SmearDetEtaPhi()

void EMSmear::SmearDetEtaPhiHengne(double deteta_gen, double track_phi_em3, double etares_det, double phires_det, TRandom3 *dummy,
                                   double& deteta_smeared, double& detphi_smeared ) {
  // detector eta smearing
  deteta_smeared = deteta_gen + dummy->Gaus(0., 1.)*etares_det;

  // calculate phimod  
  double phimod = fmod(16.0*TVector2::Phi_0_2pi(track_phi_em3)/TMath::Pi(), 1.0);

  // phimod efficiency and det phimod shift on CC electrons
  if(_ApplyPhiModCorrection && (fabs(deteta_smeared)<1.3)) {
    // get phi module shift
    Int_t xbin = _hPhiModShift->GetXaxis()->FindBin(phimod);
    double val = _hPhiModShiftSlice[xbin]->GetRandom();
    detphi_smeared = track_phi_em3 + val*TMath::Pi()/16;
  } else {   // apply detector phi resolution, no phimod shift applied
    detphi_smeared = track_phi_em3 + dummy->Gaus(0., 1.)*phires_det;
  }

  detphi_smeared = TVector2::Phi_0_2pi(detphi_smeared);

}// end SmearDetEtaPhiHengne

void EMSmear::PhiModEffHengne(double energy_gen_wfsr, double track_phi_em3, TRandom3 *dummy, double& detphi_smeared, bool& lost ) {

  lost = false;
  
  // calculate phimod  
  double phimod = fmod(16.0*TVector2::Phi_0_2pi(track_phi_em3)/TMath::Pi(), 1.0);

  // 1. Get PhiMod Efficiencies
  double eff1(1), eff2(1), err(0);

  // 1.1 Emf, Iso and HMx efficiency vs. PhiMod
  Bool_t status = PHistoTools::getBinValues(_hEmfIsoHMxEffVsPhiMod, phimod, eff1, err);
  if(!status) {
    eff1 = 1.0;
    //cout<<"Warning: overflow in "<<_hEmfIsoHMxEffVsPhiMod->GetName() << " phimod=" <<phimod<< "; EmfIsoHMx PhiMod eff set to " << eff1 <<endl;
  }

  // 1.2 Track-Match efficiency vs. PhiMod and True Energy
  status = PHistoTools::getBinValues(_hTkMatchEffVsPhiModVsEtrue, phimod, energy_gen_wfsr, eff2, err);
  if(!status) {
    eff2 = 1.0;
    //cout<<"Warning: overflow in "<<_hTkMatchEffVsPhiModVsEtrue->GetName() << " phimod=" <<phimod << " energy_gen_wfsr=" << energy_gen_wfsr << "; TKMatch PhiMod eff set to " << eff2 <<endl;
  }

  // 2. Apply the two efficiencies
  if((dummy->Rndm()>eff1) || (dummy->Rndm()>eff2)) {
    detphi_smeared = track_phi_em3 - phimod*TMath::Pi()/16;
    lost=true;
  }

  detphi_smeared = TVector2::Phi_0_2pi(detphi_smeared);

}// PhiModEffHengne



//
// smearing electron energy
//
void EMSmear::SmearEnergy(double energy, double eta, double phi, double phimod, double deteta,
			  double scale, double offset,
			  double nonlinearity, double zelec_avept,
			  double sampling, double constant,
			  double noise, double sampling1, double sampling2,
			  double sampling_exp0, double sampling_exp1, double sampling_exp2, 
			  bool needCBtailAndPeakShift,
			  TRandom3 *dummy, double& energy_smeared, double *extnRndm) {
  double theta = 2.*atan(exp(-eta));

  double E = scale*(energy- zelec_avept) +offset + zelec_avept;
  if ((_doCCscale_lumidep==2 || _doCCscale_lumidep==3) && fabs(deteta)<1.3) {
    double p0=_CCscale_lumidepFP_p0_q0+_CCscale_lumidepFP_p0_q1*_theLumi;
    double p2=_CCscale_lumidepFP_p2_q0+_CCscale_lumidepFP_p2_q1*_theLumi;
    double loss=p0+p2*deteta*deteta-_CCscale_lumidepFP_typical;
    E*=(1-loss);
    if (_CCscale_DetEtaAdjust) {
      double absdeteta = fabs(deteta);
      int region;
      if(absdeteta<0.2) region = 0;
      else if(absdeteta<0.4) region = 1;
      else if(absdeteta<0.6) region = 2;
      else if(absdeteta<0.8) region = 3;
      else region = 4;
      E*=_CCscale_DetEtaAdjust_factors[region];
    }
  }
  E = E + nonlinearity * (E - zelec_avept);
  double pT = E * sin(theta);
  // use true electron energy instead of scaled electron energy
  // since all smearing parameters were determined using generator level energy information  
  double resoE = 0.;
  double resoE_CB = 0.;
  if (_ResolutionSmear_Option==0)
    resoE = sqrt(constant*constant*energy*energy + sampling*sampling*energy + noise*noise);
  else if (_ResolutionSmear_Option==1)
    resoE = sqrt(constant*constant*energy*energy + sampling*sampling*energy*sin(theta) + noise*noise);
  else if ((_ResolutionSmear_Option==2)||((_ResolutionSmear_Option==3)&&(sampling2>-1))) {
    double sampling_exp =  sampling_exp0  - sampling_exp1/energy - sampling_exp2/(energy*energy); //new jan parameterization

    //if energy (generator) is too small, sampling_exp can be very large, making exp(sampling_exp/sin(theta))/exp(sampling_exp) = 0/0 = nan. 
    double newsampling = sampling1;
    if(exp(sampling_exp) != 0 && theta != 0 && energy > 0) newsampling = (sampling1 + sampling2/sqrt(energy))*exp(sampling_exp/sin(theta))/exp(sampling_exp);
 
    resoE = sqrt(constant*constant*energy*energy + newsampling*newsampling*energy + noise*noise);    
  } else if (_ResolutionSmear_Option==3) {
    double fracressampling = jansmear_new(sampling1,fabs(eta),energy);
    if (_CrackCBsim && needCBtailAndPeakShift) {
      resoE = noise;
      resoE_CB = sqrt(constant*constant*energy*energy + fracressampling*fracressampling*energy*energy);
    } else {
      resoE = sqrt(constant*constant*energy*energy + fracressampling*fracressampling*energy*energy + noise*noise);
    }
  } else {
    cout << "ResolutionSmear_Option can only be 0, 1, 2 or 3" << endl;
  }
  if (!extnRndm)
    energy_smeared = E + dummy->Gaus(0., 1.)*resoE;
  else{
    energy_smeared = E + extnRndm[0]*resoE;
  }	
  if (_CrackCBsim && needCBtailAndPeakShift) {
    double folded_phimod;
    if (phimod>0.5) folded_phimod=1-phimod;
    else folded_phimod=phimod;
    if (folded_phimod>_CrackCB_crlimit) {
      // make it gaussian anyway
      if (!extnRndm)
	energy_smeared += dummy->Gaus(0., 1.)*resoE_CB;
      else
	energy_smeared +=  extnRndm[1]*resoE_CB;
    } else {
      // yikes, close to the crack
      double alpha=_CrackCB_alphaOffset-_CrackCB_alphaSlope*(_CrackCB_crlimit-folded_phimod);

      //introduce also peak position shift to model response degradation near phi-cracks in addition to resolution degradation
      double peak_position_shift=_CrackCB_PeakShiftOffset+_CrackCB_PeakShiftSlope*(_CrackCB_crlimit-folded_phimod);

      //this piece of commented lines is relevant only if you want to make PeakShiftSlope-PeakShiftOffset templates 
      //uncomment two lines below and comment out two active lines above ( double alpha = ...; double peak_position_shift=...;)
      //double alpha=1.8 - 10.6*(0.2-folded_phimod);
      //double peak_position_shift=_CrackCB_alphaOffset+_CrackCB_alphaSlope*(_CrackCB_crlimit-folded_phimod);

      if (alpha<0.0001) alpha=0.0001;

      double degraded_mean = -energy_smeared;
      degraded_mean*=peak_position_shift;

      if (!extnRndm)
	energy_smeared += wz_utils::flipCrystalBall(degraded_mean, resoE_CB, alpha, _CrackCB_n, dummy);
      else
	energy_smeared += wz_utils::flipCrystalBall(degraded_mean, resoE_CB, alpha, _CrackCB_n, dummy,&(extnRndm[2]));
      if (energy_smeared<0.5) energy_smeared=0.5;

    }
  }

  if (_doPhiHack) {
    // find phi bin
    int theBin=0;
    while (phi>_PhiHack_bins[theBin]) {
      theBin++;
      if (theBin==_PhiHack_bins.size()) break;
    }
    energy_smeared*=_PhiHack_corr[theBin];
  }

}

// a simple EM response correction as a function of PhiMod
void EMSmear::SimpleEMRespCorrVsPhiMod(double energy_gen, double& energy_smeared, double track_phi_em3){

  // calculate phimod
  double phimod = fmod(16.0*TVector2::Phi_0_2pi(track_phi_em3)/TMath::Pi(), 1.0);
  // get correction factor from histogram
  //  CorrFactor is defined as (Ereco-Etrue)/Etrue
  double CorrFactor(1), err=(0);
  Bool_t status = PHistoTools::getBinValues(_Simple_EMrespCorr_vs_PhiMod, phimod, CorrFactor, err);
  if(!status) cout<<"Warning: overflow in "<<_Simple_EMrespCorr_vs_PhiMod->GetName() << " phimod="<<phimod<<endl;
  // apply the correction
  energy_smeared = energy_smeared + CorrFactor*energy_gen;

}

// A (PhiMod, Energy) dependent Energy response correction
void EMSmear::PhiModErespCorrHengne(PMCSEMObj& part){

  // true energy
  double energy_gen = part.GetEnergyGenWFSR();
  // smeared energy
  double energy_smeared = part.pE();
  // raw eta phi
  double eta_raw = part.peta();
  double phi_raw = part.pphi();
  // track phi at EM3
  double track_phi_em3 = part.trkphiem3();

  // calculate phimod
  double phimod = fmod(16.0*TVector2::Phi_0_2pi(track_phi_em3)/TMath::Pi(), 1.0);
  // get correction factor from histogram
  //  CorrFactor is defined as (Ereco-Etrue)/Etrue
  double CorrFactor(0), err=(0);
  Bool_t status = PHistoTools::getBinValues(_hErespPhiModEtrue, phimod, energy_gen, CorrFactor, err);
  if(!status) {
    CorrFactor = 0.0;
    //cout<<"Warning: overflow in "<<_hErespPhiModEtrue->GetName() << " phimod="<<phimod << " energy="<< energy_gen<<endl;
  }
  // apply the correction
  // option 1 : as a correction
  //energy_smeared = energy_smeared + CorrFactor*energy_gen;
  // option 2: as a scale
  energy_smeared = energy_smeared* (CorrFactor+1.0);
  part.SetEnergyEtaPhi(energy_smeared, eta_raw, phi_raw);

}

// set smearing parameters
void EMSmear::SetCCSmearParameters(double etares_phy_cc, double phires_phy_cc, double etares_det_cc, double phires_det_cc, 
				   double scale_cc, double offset_cc, 
				   double nonlinearity_cc, double zelec_avept_cc,
				   double sampling_cc, double constant_cc, double noise_cc, 
                                   double sampling_cc1, double sampling_cc2, double sampling_ccexp0,  double sampling_ccexp1,  double sampling_ccexp2) {
  _etares_phy_CC = etares_phy_cc;
  _phires_phy_CC = phires_phy_cc;
  _etares_det_CC = etares_det_cc;
  _phires_det_CC = phires_det_cc;
  _scale_CC = scale_cc;
  _offset_CC = offset_cc;
  _Energy_Nonlinearity_CC = nonlinearity_cc;
  _ZElec_AvePt_CC = zelec_avept_cc;
  _sampling_CC = sampling_cc;
  _constant_CC = constant_cc;
  _noise_CC = noise_cc;
  _Sampling_CC1 = sampling_cc1;
  _Sampling_CC1 = sampling_cc2;
  _Sampling_CCexp0 = sampling_ccexp0;
  _Sampling_CCexp1 = sampling_ccexp1;
  _Sampling_CCexp2 = sampling_ccexp2;
}

void EMSmear::SetECSmearParameters(double etares_phy_ec, double phires_phy_ec, double etares_det_ec, double phires_det_ec, 
				   double scale_ec, double offset_ec, 
				   double nonlinearity_ec, double zelec_avept_ec,
				   double sampling_ec, double constant_ec, double noise_ec,
                                   double sampling_ec1, double sampling_ec2, double sampling_ecexp0, double sampling_ecexp1, double sampling_ecexp2) {
  
  _etares_phy_EC = etares_phy_ec;
  _phires_phy_EC = phires_phy_ec;
  _etares_det_EC = etares_det_ec;
  _phires_det_EC = phires_det_ec;
  _scale_EC = scale_ec;
  _offset_EC = offset_ec;
  _Energy_Nonlinearity_EC = nonlinearity_ec;
  _ZElec_AvePt_EC = zelec_avept_ec;
  _sampling_EC = sampling_ec;
  _constant_EC = constant_ec;
  _noise_EC = noise_ec;
  _Sampling_EC1 = sampling_ec1;
  _Sampling_EC1 = sampling_ec2;
  _Sampling_ECexp0 = sampling_ecexp0;
  _Sampling_ECexp1 = sampling_ecexp1;
  _Sampling_ECexp2 = sampling_ecexp2;
}


// helper functions for _ResolutionSmear_Option==3
double EMSmear::jansmear_new(double nX0, double etap, double e) const {
  // This is in units of copper in the coil, not uranium in front of the CAL !!

  static double params000[4] = {1.53798e-01, 1.42321e+00, -7.20661e-03, 1.44128e-01};
  static double params017[4] = {1.52908e-01, 1.54769e+00, -2.60290e-02, 1.72635e-01};
  static double params036[4] = {1.51836e-01, 1.74815e+00, -3.90201e-02, 2.25190e-01};
  static double params055[4] = {1.57284e-01, 1.88493e+00, -1.97392e-02, 2.51397e-01};

  //Where are we ?
  //
  double Jan_calc=0;
  if (nX0<0) {
    Jan_calc=janfunc(params000,etap,e);
  } else if (nX0<0.17) {
    double J1=janfunc(params000,etap,e);
    double J2=janfunc(params017,etap,e);
    Jan_calc=J1+((nX0-0)/0.17)*(J2-J1);
  } else if (nX0<0.36) {
    double J1=janfunc(params017,etap,e);
    double J2=janfunc(params036,etap,e);
    Jan_calc=J1+((nX0-0.17)/(0.36-0.17))*(J2-J1);
  } else if (nX0<0.55) {
    double J1=janfunc(params036,etap,e);
    double J2=janfunc(params055,etap,e);
    Jan_calc=J1+((nX0-0.36)/(0.55-0.36))*(J2-J1);
  } else {
    Jan_calc=janfunc(params055,etap,e);
  }

  return Jan_calc;

}

double EMSmear::janfunc(double params[4], double etap, double e) const {

  double theta=2.0*atan(exp(-etap));
  double predP0=params[0]/exp(params[1])*exp(params[1]/sin(theta));
  double predP1=params[2]*etap+params[3];
  double prediction=predP0/sqrt(e)+predP1/e;
  return prediction;

}

double EMSmear::Get_dUParaEff(double dupara, double elecpt, bool isW){
  if (!_Apply_dUParaEff) {
    std::cout << " -- Hengne: Error -- this function is only supposed to be used for dUParaEff, "<< std::endl;
    std::cout << "            please set \"Apply_dUParaEff\" and its parameters." << std::endl;
    abort();
  }
  double ratio_dupara_pt = dupara/elecpt;
  const int nbins = isW ? _dUParaEff_Nbins_W : _dUParaEff_Nbins_Z ;
  double xmin[nbins], xmax[nbins], pt_mean[nbins], eff_0dupara[nbins], eff[nbins];
  for (int i=0; i<nbins; i++){
    if (isW) {
      xmin[i] = _dUParaEff_Bin_Min_W[i];
      xmax[i] = _dUParaEff_Bin_Max_W[i];
      pt_mean[i] = _dUParaEff_Mean_Pt_W[i];
      eff_0dupara[i] = _dUParaEff_Zero_dUPara_W[i];
      eff[i] = _dUParaEff_Func_Par0_W[i] + _dUParaEff_Func_Par1_W[i]*ratio_dupara_pt;
    }
    else {
      xmin[i] = _dUParaEff_Bin_Min_Z[i];
      xmax[i] = _dUParaEff_Bin_Max_Z[i];
      pt_mean[i] = _dUParaEff_Mean_Pt_Z[i];
      eff_0dupara[i] = _dUParaEff_Zero_dUPara_Z[i];
      eff[i] = _dUParaEff_Func_Par0_Z[i] + _dUParaEff_Func_Par1_Z[i]*ratio_dupara_pt;
    }
  }
  
  double duparaeff = 0;

  if (_dUParaEff_Smooth_Eff && nbins>1) {
    int imin=0;
    int imax=nbins-1;
    for (int i=0; i<nbins; i++) {
      if ( elecpt>pt_mean[i] && pt_mean[i]>pt_mean[imin]) imin = i;
      if ( elecpt<pt_mean[i] && pt_mean[i]<pt_mean[imax]) imax = i;
    }
    if (imin==0&&imax==0) imax = 1;
    if (imin==nbins-1&&imax==nbins-1) imin = nbins-2;

    if (ratio_dupara_pt<1.e-5) {
      duparaeff = eff_0dupara[imin]+(elecpt-pt_mean[imin])*(eff_0dupara[imax]-eff_0dupara[imin])/(pt_mean[imax]-pt_mean[imin]);
    }
    else {
      duparaeff = eff[imin]+(elecpt-pt_mean[imin])*(eff[imax]-eff[imin])/(pt_mean[imax]-pt_mean[imin]);
    }
  }
  else {
    // do not smooth eff
    int ptbin = 0;
    for (int i=0; i<nbins; i++){
      if (i==0 && elecpt<xmax[0]) ptbin = 0;
      else if (i==nbins-1 && elecpt>xmin[nbins-1]) ptbin = nbins-1;
      else if (elecpt>xmin[i] && elecpt<xmax[i]) ptbin = i;
    }

    if  (ratio_dupara_pt<1.e-5) duparaeff = eff_0dupara[ptbin];
    else duparaeff = eff[ptbin];
  }

  return duparaeff;
}


double EMSmear::Get_dUParaEff1(double dupara, double elecpt, double eta){

 // get EtaBin
 int EtaBin = 0;
 for (int ieta=0; ieta<_dUParaEff_Option1_NEtaBins; ieta++){
   if (eta>_dUParaEff_Option1_EtaBins.at(ieta) && eta<_dUParaEff_Option1_EtaBins.at(ieta+1)){
     EtaBin = ieta;
     break;
   }
 }

 double ratio_dupara_pt = dupara/elecpt;
 const int nbins = _dUParaEff_Option1_NPTBins;
 double xmin[nbins], xmax[nbins], pt_mean[nbins], eff_0dupara[nbins], eff[nbins];
 for (int i=0; i<nbins; i++){
   xmin[i] = _dUParaEff_Option1_PTBins.at(i);
   xmax[i] = _dUParaEff_Option1_PTBins.at(i+1);
   pt_mean[i] = _dUParaEff_Option1_Pars.at(EtaBin).at(i)[0];
   eff_0dupara[i] = _dUParaEff_Option1_Pars.at(EtaBin).at(i)[1];
   double effp0 = _dUParaEff_Option1_Pars.at(EtaBin).at(i)[2];
   double effp1 = _dUParaEff_Option1_Pars.at(EtaBin).at(i)[3];
   eff[i] = effp0 + effp1*ratio_dupara_pt;
 }

  double duparaeff = 0;

  if (nbins>1) {
    int imin=0;
    int imax=nbins-1;
    for (int i=0; i<nbins; i++) {
      if ( elecpt>pt_mean[i] && pt_mean[i]>pt_mean[imin]) imin = i;
      if ( elecpt<pt_mean[i] && pt_mean[i]<pt_mean[imax]) imax = i;
    }
    if (imin==0&&imax==0) imax = 1;
    if (imin==nbins-1&&imax==nbins-1) imin = nbins-2;

    if (ratio_dupara_pt<1.e-5) {
      duparaeff = eff_0dupara[imin]+(elecpt-pt_mean[imin])*(eff_0dupara[imax]-eff_0dupara[imin])/(pt_mean[imax]-pt_mean[imin]);
    }
    else {
      duparaeff = eff[imin]+(elecpt-pt_mean[imin])*(eff[imax]-eff[imin])/(pt_mean[imax]-pt_mean[imin]);
    }
  }
  else {
    // do not smooth eff
    int ptbin = 0;
    for (int i=0; i<nbins; i++){
      if (i==0 && elecpt<xmax[0]) ptbin = 0;
      else if (i==nbins-1 && elecpt>xmin[nbins-1]) ptbin = nbins-1;
      else if (elecpt>xmin[i] && elecpt<xmax[i]) ptbin = i;
    }

    if  (ratio_dupara_pt<1.e-5) duparaeff = eff_0dupara[ptbin];
    else duparaeff = eff[ptbin];
  }

  return duparaeff;

}

double EMSmear::Get_dUParaEff2(double dupara, double elecpt, double eta){

  // get EtaBin
  int EtaBin = 0;
  if ( _runNumber < _middlerunnumber ) { // 2b3 
    for (int ieta=0; ieta<_dUParaEff_Option2_NEtaBins; ieta++){
      if (eta>_dUParaEff_Option2_EtaBins.at(ieta) && eta<_dUParaEff_Option2_EtaBins.at(ieta+1)){
        EtaBin = ieta;
        break;
      }
    }
  }
  else { // 2b4
    for (int ieta=0; ieta<_dUParaEff_Option2_NEtaBins2; ieta++){
      if (eta>_dUParaEff_Option2_EtaBins2.at(ieta) && eta<_dUParaEff_Option2_EtaBins2.at(ieta+1)){
        EtaBin = ieta;
        break;
      }
    }
  }

  double ratio_dupara_pt = dupara/elecpt;
  const int nbins = ( (_runNumber<_middlerunnumber) ? (_dUParaEff_Option2_NPTBins) : (_dUParaEff_Option2_NPTBins2) );
  double xmin[nbins], xmax[nbins], pt_mean[nbins], eff_0dupara[nbins], eff[nbins];
  if (_runNumber<_middlerunnumber) { // 2b3
    for (int i=0; i<nbins; i++){
      xmin[i] = _dUParaEff_Option2_PTBins.at(i);
      xmax[i] = _dUParaEff_Option2_PTBins.at(i+1);
      pt_mean[i] = _dUParaEff_Option2_Pars.at(EtaBin).at(i)[0];
      eff_0dupara[i] = _dUParaEff_Option2_Pars.at(EtaBin).at(i)[1];
      double effp0 = _dUParaEff_Option2_Pars.at(EtaBin).at(i)[2];
      double effp1 = _dUParaEff_Option2_Pars.at(EtaBin).at(i)[3];
      eff[i] = effp0 + effp1*ratio_dupara_pt;
    }
  }
  else { // 2b4
    for (int i=0; i<nbins; i++){
      xmin[i] = _dUParaEff_Option2_PTBins2.at(i);
      xmax[i] = _dUParaEff_Option2_PTBins2.at(i+1);
      pt_mean[i] = _dUParaEff_Option2_Pars2.at(EtaBin).at(i)[0];
      eff_0dupara[i] = _dUParaEff_Option2_Pars2.at(EtaBin).at(i)[1];
      double effp0 = _dUParaEff_Option2_Pars2.at(EtaBin).at(i)[2];
      double effp1 = _dUParaEff_Option2_Pars2.at(EtaBin).at(i)[3];
      eff[i] = effp0 + effp1*ratio_dupara_pt;
    }    
  }
  double duparaeff = 0; 

  if (nbins>1) {
    int imin=0;
    int imax=nbins-1;
    for (int i=0; i<nbins; i++) {
      if ( elecpt>pt_mean[i] && pt_mean[i]>pt_mean[imin]) imin = i;
      if ( elecpt<pt_mean[i] && pt_mean[i]<pt_mean[imax]) imax = i;
    }
    if (imin==0&&imax==0) imax = 1;
    if (imin==nbins-1&&imax==nbins-1) imin = nbins-2;

    if (ratio_dupara_pt<1.e-5) {
      duparaeff = eff_0dupara[imin]+(elecpt-pt_mean[imin])*(eff_0dupara[imax]-eff_0dupara[imin])/(pt_mean[imax]-pt_mean[imin]);
    }
    else {
      duparaeff = eff[imin]+(elecpt-pt_mean[imin])*(eff[imax]-eff[imin])/(pt_mean[imax]-pt_mean[imin]);
    }
  }
  else {
    // do not smooth eff
    int ptbin = 0;
    for (int i=0; i<nbins; i++){
      if (i==0 && elecpt<xmax[0]) ptbin = 0;
      else if (i==nbins-1 && elecpt>xmin[nbins-1]) ptbin = nbins-1;
      else if (elecpt>xmin[i] && elecpt<xmax[i]) ptbin = i;
    }

    if  (ratio_dupara_pt<1.e-5) duparaeff = eff_0dupara[ptbin];
    else duparaeff = eff[ptbin];
  }

  return duparaeff;

}

double EMSmear::Get_dUParaEff6_UseHists(double dupara, double elecpt){


  double ratio_dupara_pt = dupara/elecpt;
  double duparaeff = 0;


  if ( (_hist_UPerpSETUParaEtaPT->GetBinContent(_hist_UPerpSETUParaEtaPT->FindBin(ratio_dupara_pt))) > 0 ) {
    duparaeff = _hist_UPerpSETUParaEtaPT->Interpolate(ratio_dupara_pt);
//    cout << " from _hist_UPerpSETUParaEtaPT " << endl;
  }
  else if ( (_hist_SETUParaEtaPT->GetBinContent(_hist_SETUParaEtaPT->FindBin(ratio_dupara_pt))) > 0 ) {
    duparaeff = _hist_SETUParaEtaPT->Interpolate(ratio_dupara_pt);
//    cout << " from _hist_SETUParaEtaPT " << endl;
  }
  else if ( (_hist_UParaEtaPT->GetBinContent(_hist_UParaEtaPT->FindBin(ratio_dupara_pt))) > 0 ) {
    duparaeff = _hist_UParaEtaPT->Interpolate(ratio_dupara_pt);
//    cout << " from _hist_UParaEtaPT " << endl;
  }
  else if ( (_hist_EtaPT->GetBinContent(_hist_EtaPT->FindBin(ratio_dupara_pt))) > 0 ) {
    duparaeff = _hist_EtaPT->Interpolate(ratio_dupara_pt);
//    cout << " from _hist_EtaPT " << endl;
  }
  else {
    duparaeff = _hist_PT->Interpolate(ratio_dupara_pt);
//    cout << " from _hist_PT " << endl;
  }
  //  if(ratio_dupara_pt > 0.2) cout<<"outside boundry "<<duparaeff<<"  "<<dupara<<"  "<<elecpt<<endl;

  return duparaeff;

}

void EMSmear::Get_dUParaEff6_UseHistsInit(double elecpt, double eta, double upara, double set, double uperp){
  
  // get UPerpBin
  int UPerpBin = -1;
  for (int iuperp=0; iuperp<_dUParaEff_Option6_UseHists_NUPerpBins; iuperp++){
    if (fabs(uperp)>=_dUParaEff_Option6_UseHists_UPerpBins.at(iuperp) && fabs(uperp)<_dUParaEff_Option6_UseHists_UPerpBins.at(iuperp+1)){
      UPerpBin = iuperp;
      break;
    }
  }
  //cout << "uperp = " << uperp << "; iuperp = " << UPerpBin << endl;

  // get SETBin
  int SETBin = -1;
  for (int iset=0; iset<_dUParaEff_Option6_UseHists_NSETBins; iset++){
    if (set>_dUParaEff_Option6_UseHists_SETBins.at(iset) && set<_dUParaEff_Option6_UseHists_SETBins.at(iset+1)){
      SETBin = iset;
      break;
    }
  }

  // get UParaBin
  int UParaBin = -1;
  for (int iupara=0; iupara<_dUParaEff_Option6_UseHists_NUParaBins; iupara++){
    if (upara>_dUParaEff_Option6_UseHists_UParaBins.at(iupara) && upara<_dUParaEff_Option6_UseHists_UParaBins.at(iupara+1)){
      UParaBin = iupara;
      break;
    }
  }

  // get EtaBin
  int EtaBin = -1;
  for (int ieta=0; ieta<_dUParaEff_Option6_UseHists_NEtaBins; ieta++){
    if (eta>_dUParaEff_Option6_UseHists_EtaBins.at(ieta) && eta<_dUParaEff_Option6_UseHists_EtaBins.at(ieta+1)){
      EtaBin = ieta;
      break;
    }
  }

  // get PTBin
  int PTBin = -1;
  for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins; ipt++){
    if (elecpt>_dUParaEff_Option6_UseHists_PTBins.at(ipt) && elecpt<_dUParaEff_Option6_UseHists_PTBins.at(ipt+1)){
      PTBin = ipt;
      break;
    }
  }


  if(UPerpBin==-1){
    if (fabs(uperp)<_dUParaEff_Option6_UseHists_UPerpBins.at(0)) UPerpBin = 0;
    if (fabs(uperp)>=_dUParaEff_Option6_UseHists_UPerpBins.at(_dUParaEff_Option6_UseHists_NUPerpBins)) UPerpBin = _dUParaEff_Option6_UseHists_NUPerpBins-1;
  }
  if(SETBin==-1){
    if (set<_dUParaEff_Option6_UseHists_SETBins.at(0)) SETBin = 0;
    if (set>=_dUParaEff_Option6_UseHists_SETBins.at(_dUParaEff_Option6_UseHists_NSETBins)) SETBin = _dUParaEff_Option6_UseHists_NSETBins-1;
  }
  if(EtaBin==-1){
    if (eta<_dUParaEff_Option6_UseHists_EtaBins.at(0)) EtaBin = 0;
    if (eta>=_dUParaEff_Option6_UseHists_EtaBins.at(_dUParaEff_Option6_UseHists_NEtaBins)) EtaBin = _dUParaEff_Option6_UseHists_NEtaBins-1;
  }
  if(PTBin==-1){
    if (elecpt<_dUParaEff_Option6_UseHists_PTBins.at(0)) PTBin = 0;
    if (elecpt>=_dUParaEff_Option6_UseHists_PTBins.at(_dUParaEff_Option6_UseHists_NPTBins)) PTBin = _dUParaEff_Option6_UseHists_NPTBins-1;
  }
  if(UParaBin==-1){
    if (upara<_dUParaEff_Option6_UseHists_UParaBins.at(0)) UParaBin = 0;
    if (upara>=_dUParaEff_Option6_UseHists_UParaBins.at(_dUParaEff_Option6_UseHists_NUParaBins)) UParaBin = _dUParaEff_Option6_UseHists_NUParaBins-1;
  }
 

  //  cout << "Get Get_dUParaEff6_UseHists " ;
  _hist_UPerpSETUParaEtaPT = _dUParaEff_Option6_UseHists_hist_UPerpSETUParaEtaPT_vec.at(UPerpBin).at(SETBin).at(UParaBin).at(EtaBin).at(PTBin);
  _hist_SETUParaEtaPT = _dUParaEff_Option6_UseHists_hist_SETUParaEtaPT_vec.at(SETBin).at(UParaBin).at(EtaBin).at(PTBin);
  _hist_UParaEtaPT = _dUParaEff_Option6_UseHists_hist_UParaEtaPT_vec.at(UParaBin).at(EtaBin).at(PTBin);
  _hist_EtaPT = _dUParaEff_Option6_UseHists_hist_EtaPT_vec.at(EtaBin).at(PTBin);
  _hist_PT = _dUParaEff_Option6_UseHists_hist_PT_vec.at(PTBin);

}


/////////////
void EMSmear::SetScaleOffsetDepCC(double lumi, double upara) {

  _theLumi=lumi;

  if (_doCCscale_lumidep){

    if (!(_doCCscale_lumidep==1 || _doCCscale_lumidep==3)) return;

    // find lumi bin
    int theBin=0;
    while (lumi>_CCscale_lumidep_lumibins[theBin]) {
      theBin++;
      if (theBin==_CCscale_lumidep_lumibins.size()) break;
    }

    // set scale and offset accordingly
    if (_doCCscale_uparadep){
      if(fabs(upara)<15.){
        _scale_CC=_CCscale_lumidep_scale[theBin];
        _offset_CC=_CCscale_lumidep_offset[theBin];
      }
      else {
        _scale_CC=_CCscaleUT30_lumidep_scale[theBin];
        _offset_CC=_CCscaleUT30_lumidep_offset[theBin];
      }
    }
    else {
      _scale_CC=_CCscale_lumidep_scale[theBin];
      _offset_CC=_CCscale_lumidep_offset[theBin];
    }

  }
  else if (_doCCscale_uparadep) {

    if (fabs(upara)<15.){
      _scale_CC = _CCscaleUT15_uparadep_scale;
      _offset_CC = _CCscaleUT15_uparadep_offset;
    }
    else{
      _scale_CC = _CCscaleUT30_uparadep_scale;
      _offset_CC = _CCscaleUT30_uparadep_offset;
    }

  }
  

}

bool EMSmear::SetdUParaEffParsModel6UseHists(PParameterReader& parm){
//
  // _dUParaEff_Option = 6
  // _dUParaEff_Option6_UseHists == true

  _dUParaEff_Option6_UseHists_ParFile = new TFile(parm.GetChar("dUParaEff_Option6_UseHists_ParFile"));
  _dUParaEff_Option6_UseHists_ParFile2 = new TFile(parm.GetChar("dUParaEff_Option6_UseHists_ParFile2"));


  // initialize binning
  // eta
  _dUParaEff_Option6_UseHists_EtaBins.push_back(-2.0);
  _dUParaEff_Option6_UseHists_EtaBins.push_back(-1.1);
  _dUParaEff_Option6_UseHists_EtaBins.push_back(-0.9);
  _dUParaEff_Option6_UseHists_EtaBins.push_back(-0.6);
  _dUParaEff_Option6_UseHists_EtaBins.push_back(-0.3);
  _dUParaEff_Option6_UseHists_EtaBins.push_back(+0.0);
  _dUParaEff_Option6_UseHists_EtaBins.push_back(+0.3);
  _dUParaEff_Option6_UseHists_EtaBins.push_back(+0.6);
  _dUParaEff_Option6_UseHists_EtaBins.push_back(+0.9);
  _dUParaEff_Option6_UseHists_EtaBins.push_back(+1.1);
  _dUParaEff_Option6_UseHists_EtaBins.push_back(+2.0);
  // pt
  _dUParaEff_Option6_UseHists_PTBins.push_back(10.);
  //_dUParaEff_Option6_UseHists_PTBins.push_back(20.);
  _dUParaEff_Option6_UseHists_PTBins.push_back(25.);
  _dUParaEff_Option6_UseHists_PTBins.push_back(30.);
  _dUParaEff_Option6_UseHists_PTBins.push_back(35.);
  _dUParaEff_Option6_UseHists_PTBins.push_back(40.);
  _dUParaEff_Option6_UseHists_PTBins.push_back(50.);
  _dUParaEff_Option6_UseHists_PTBins.push_back(100.);
  // UPara
  _dUParaEff_Option6_UseHists_UParaBins.push_back(-30.0);
  _dUParaEff_Option6_UseHists_UParaBins.push_back(-15.0);
  _dUParaEff_Option6_UseHists_UParaBins.push_back(-10.0);
  _dUParaEff_Option6_UseHists_UParaBins.push_back(-5.0);
  _dUParaEff_Option6_UseHists_UParaBins.push_back(0.0);
  _dUParaEff_Option6_UseHists_UParaBins.push_back(+5.0);
  _dUParaEff_Option6_UseHists_UParaBins.push_back(+10.0);
  _dUParaEff_Option6_UseHists_UParaBins.push_back(+15.0);
  _dUParaEff_Option6_UseHists_UParaBins.push_back(+30.0);
  // SET
  _dUParaEff_Option6_UseHists_SETBins.push_back(0.);
  _dUParaEff_Option6_UseHists_SETBins.push_back(50.);
  _dUParaEff_Option6_UseHists_SETBins.push_back(100.);
  _dUParaEff_Option6_UseHists_SETBins.push_back(150.);
  _dUParaEff_Option6_UseHists_SETBins.push_back(1000.);
  // UPerp
  _dUParaEff_Option6_UseHists_UPerpBins.push_back(-1.0);
  _dUParaEff_Option6_UseHists_UPerpBins.push_back(10.0);
  _dUParaEff_Option6_UseHists_UPerpBins.push_back(1000.0);


  _dUParaEff_Option6_UseHists_NUPerpBins = (int)(_dUParaEff_Option6_UseHists_UPerpBins.size()-1);
  _dUParaEff_Option6_UseHists_NSETBins = (int)(_dUParaEff_Option6_UseHists_SETBins.size()-1);
  _dUParaEff_Option6_UseHists_NUParaBins = (int)(_dUParaEff_Option6_UseHists_UParaBins.size()-1);
  _dUParaEff_Option6_UseHists_NEtaBins = (int)(_dUParaEff_Option6_UseHists_EtaBins.size()-1);
  _dUParaEff_Option6_UseHists_NPTBins = (int)(_dUParaEff_Option6_UseHists_PTBins.size()-1);


  // binning in PT
  for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins; ipt++){
    char hname[500];
    sprintf(hname, "hdUParaRatioEf_PT%d", ipt);
    TH1D* hist = (TH1D*)_dUParaEff_Option6_UseHists_ParFile->Get(hname);
    _dUParaEff_Option6_UseHists_hist_PT_vec.push_back(hist);
  }

  // binning in Eta and PT
  for (int ieta=0; ieta<_dUParaEff_Option6_UseHists_NEtaBins; ieta++){
    vector<TH1D*> hist_ieta_vec;
    for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins; ipt++){
      char hname[500];
      sprintf(hname, "hdUParaRatioEf_Eta%d_PT%d", ieta, ipt);
      TH1D* hist = (TH1D*)_dUParaEff_Option6_UseHists_ParFile->Get(hname);
      hist_ieta_vec.push_back(hist);
    } // ipt
    _dUParaEff_Option6_UseHists_hist_EtaPT_vec.push_back(hist_ieta_vec);
  } // ieta


  // binning in UPara, Eta and PT
  for (int iupara=0; iupara<_dUParaEff_Option6_UseHists_NUParaBins; iupara++){
    vector< vector<TH1D*> > hist_iupara_vec;
    for (int ieta=0; ieta<_dUParaEff_Option6_UseHists_NEtaBins; ieta++){
      vector<TH1D*> hist_ieta_vec;
      for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins; ipt++){
        char hname[500];
        sprintf(hname, "hdUParaRatioEf_UPara%d_Eta%d_PT%d", iupara, ieta, ipt);
        TH1D* hist = (TH1D*)_dUParaEff_Option6_UseHists_ParFile->Get(hname);
        hist_ieta_vec.push_back(hist);
      } // ipt
      hist_iupara_vec.push_back(hist_ieta_vec);
    } // ieta
    _dUParaEff_Option6_UseHists_hist_UParaEtaPT_vec.push_back(hist_iupara_vec);
  } // iupara


  // binning in SET, UPara, Eta and PT
  for (int iset=0; iset<_dUParaEff_Option6_UseHists_NSETBins; iset++){
    vector< vector< vector<TH1D*> > > hist_iset_vec;
    for (int iupara=0; iupara<_dUParaEff_Option6_UseHists_NUParaBins; iupara++){
      vector< vector<TH1D*> > hist_iupara_vec;
      for (int ieta=0; ieta<_dUParaEff_Option6_UseHists_NEtaBins; ieta++){
        vector<TH1D*> hist_ieta_vec;
        for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins; ipt++){
          char hname[500];
          sprintf(hname, "hdUParaRatioEf_SET%d_UPara%d_Eta%d_PT%d", iset, iupara, ieta, ipt);
          TH1D* hist = (TH1D*)_dUParaEff_Option6_UseHists_ParFile->Get(hname);
          hist_ieta_vec.push_back(hist);
        } // ipt
        hist_iupara_vec.push_back(hist_ieta_vec);
      } // ieta
      hist_iset_vec.push_back(hist_iupara_vec);
    } // iupara
    _dUParaEff_Option6_UseHists_hist_SETUParaEtaPT_vec.push_back(hist_iset_vec);
  } // iset

  // binning in UPerp, SET, UPara, Eta and PT
  for (int iuperp=0; iuperp<_dUParaEff_Option6_UseHists_NUPerpBins; iuperp++){
    vector< vector< vector< vector<TH1D*> > > > hist_iuperp_vec;
    for (int iset=0; iset<_dUParaEff_Option6_UseHists_NSETBins; iset++){
      vector< vector< vector<TH1D*> > > hist_iset_vec;
      for (int iupara=0; iupara<_dUParaEff_Option6_UseHists_NUParaBins; iupara++){
        vector< vector<TH1D*> > hist_iupara_vec;
        for (int ieta=0; ieta<_dUParaEff_Option6_UseHists_NEtaBins; ieta++){
          vector<TH1D*> hist_ieta_vec;
          for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins; ipt++){
            char hname[500];
            sprintf(hname, "hdUParaRatioEf_UPerp%d_SET%d_UPara%d_Eta%d_PT%d", iuperp, iset, iupara, ieta, ipt);
            TH1D* hist = (TH1D*)_dUParaEff_Option6_UseHists_ParFile->Get(hname);
            hist_ieta_vec.push_back(hist);
          } // ipt
          hist_iupara_vec.push_back(hist_ieta_vec);
        } // ieta
        hist_iset_vec.push_back(hist_iupara_vec);
      } // iupara
      hist_iuperp_vec.push_back(hist_iset_vec);
    } // iset
    _dUParaEff_Option6_UseHists_hist_UPerpSETUParaEtaPT_vec.push_back(hist_iuperp_vec);
  } // iuperp



  // below repeate the same from the beginning for RunIIb4

  // initialize binning
  // eta
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(-2.0);
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(-1.1);
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(-0.9);
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(-0.6);
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(-0.3);
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(+0.0);
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(+0.3);
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(+0.6);
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(+0.9);
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(+1.1);
  _dUParaEff_Option6_UseHists_EtaBins2.push_back(+2.0);
  // pt
  _dUParaEff_Option6_UseHists_PTBins2.push_back(10.);
  //_dUParaEff_Option6_UseHists_PTBins2.push_back(20.);
  _dUParaEff_Option6_UseHists_PTBins2.push_back(25.);
  _dUParaEff_Option6_UseHists_PTBins2.push_back(30.);
  _dUParaEff_Option6_UseHists_PTBins2.push_back(35.);
  _dUParaEff_Option6_UseHists_PTBins2.push_back(40.);
  _dUParaEff_Option6_UseHists_PTBins2.push_back(50.);
  _dUParaEff_Option6_UseHists_PTBins2.push_back(100.);
  // UPara
  _dUParaEff_Option6_UseHists_UParaBins2.push_back(-30.0);
  _dUParaEff_Option6_UseHists_UParaBins2.push_back(-15.0);
  _dUParaEff_Option6_UseHists_UParaBins2.push_back(-10.0);
  _dUParaEff_Option6_UseHists_UParaBins2.push_back(-5.0);
  _dUParaEff_Option6_UseHists_UParaBins2.push_back(0.0);
  _dUParaEff_Option6_UseHists_UParaBins2.push_back(+5.0);
  _dUParaEff_Option6_UseHists_UParaBins2.push_back(+10.0);
  _dUParaEff_Option6_UseHists_UParaBins2.push_back(+15.0);
  _dUParaEff_Option6_UseHists_UParaBins2.push_back(+30.0);
  // SET
  _dUParaEff_Option6_UseHists_SETBins2.push_back(0.);
  _dUParaEff_Option6_UseHists_SETBins2.push_back(50.);
  _dUParaEff_Option6_UseHists_SETBins2.push_back(100.);
  _dUParaEff_Option6_UseHists_SETBins2.push_back(150.);
  _dUParaEff_Option6_UseHists_SETBins2.push_back(1000.);
  // UPerp
  _dUParaEff_Option6_UseHists_UPerpBins2.push_back(-1.0);
  _dUParaEff_Option6_UseHists_UPerpBins2.push_back(10.0);
  _dUParaEff_Option6_UseHists_UPerpBins2.push_back(1000.0);


  _dUParaEff_Option6_UseHists_NUPerpBins2 = (int)(_dUParaEff_Option6_UseHists_UPerpBins2.size()-1);
  _dUParaEff_Option6_UseHists_NSETBins2 = (int)(_dUParaEff_Option6_UseHists_SETBins2.size()-1);
  _dUParaEff_Option6_UseHists_NUParaBins2 = (int)(_dUParaEff_Option6_UseHists_UParaBins2.size()-1);
  _dUParaEff_Option6_UseHists_NEtaBins2 = (int)(_dUParaEff_Option6_UseHists_EtaBins2.size()-1);
  _dUParaEff_Option6_UseHists_NPTBins2 = (int)(_dUParaEff_Option6_UseHists_PTBins2.size()-1);

  // binning in PT
  for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins2; ipt++){
    char hname[500];
    sprintf(hname, "hdUParaRatioEf_PT%d", ipt);
    TH1D* hist = (TH1D*)_dUParaEff_Option6_UseHists_ParFile2->Get(hname);
    _dUParaEff_Option6_UseHists_hist_PT_vec2.push_back(hist);
  }

  // binning in Eta and PT
  for (int ieta=0; ieta<_dUParaEff_Option6_UseHists_NEtaBins2; ieta++){
    vector<TH1D*> hist_ieta_vec;
    for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins2; ipt++){
      char hname[500];
      sprintf(hname, "hdUParaRatioEf_Eta%d_PT%d", ieta, ipt);
      TH1D* hist = (TH1D*)_dUParaEff_Option6_UseHists_ParFile2->Get(hname);
      hist_ieta_vec.push_back(hist);
    } // ipt
    _dUParaEff_Option6_UseHists_hist_EtaPT_vec2.push_back(hist_ieta_vec);
  } // ieta


  // binning in UPara, Eta and PT
  for (int iupara=0; iupara<_dUParaEff_Option6_UseHists_NUParaBins2; iupara++){
    vector< vector<TH1D*> > hist_iupara_vec;
    for (int ieta=0; ieta<_dUParaEff_Option6_UseHists_NEtaBins2; ieta++){
      vector<TH1D*> hist_ieta_vec;
      for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins2; ipt++){
        char hname[500];
        sprintf(hname, "hdUParaRatioEf_UPara%d_Eta%d_PT%d", iupara, ieta, ipt);
        TH1D* hist = (TH1D*)_dUParaEff_Option6_UseHists_ParFile2->Get(hname);
        hist_ieta_vec.push_back(hist);
      } // ipt
      hist_iupara_vec.push_back(hist_ieta_vec);
    } // ieta
    _dUParaEff_Option6_UseHists_hist_UParaEtaPT_vec2.push_back(hist_iupara_vec);
  } // iupara


  // binning in SET, UPara, Eta and PT
  for (int iset=0; iset<_dUParaEff_Option6_UseHists_NSETBins2; iset++){
    vector< vector< vector<TH1D*> > > hist_iset_vec;
    for (int iupara=0; iupara<_dUParaEff_Option6_UseHists_NUParaBins2; iupara++){
      vector< vector<TH1D*> > hist_iupara_vec;
      for (int ieta=0; ieta<_dUParaEff_Option6_UseHists_NEtaBins2; ieta++){
        vector<TH1D*> hist_ieta_vec;
        for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins2; ipt++){
          char hname[500];
          sprintf(hname, "hdUParaRatioEf_SET%d_UPara%d_Eta%d_PT%d", iset, iupara, ieta, ipt);
          TH1D* hist = (TH1D*)_dUParaEff_Option6_UseHists_ParFile2->Get(hname);
          hist_ieta_vec.push_back(hist);
        } // ipt
        hist_iupara_vec.push_back(hist_ieta_vec);
      } // ieta
      hist_iset_vec.push_back(hist_iupara_vec);
    } // iupara
    _dUParaEff_Option6_UseHists_hist_SETUParaEtaPT_vec2.push_back(hist_iset_vec);
  } // iset

  // binning in UPerp, SET, UPara, Eta and PT
  for (int iuperp=0; iuperp<_dUParaEff_Option6_UseHists_NUPerpBins2; iuperp++){
    vector< vector< vector< vector<TH1D*> > > > hist_iuperp_vec;
    for (int iset=0; iset<_dUParaEff_Option6_UseHists_NSETBins2; iset++){
      vector< vector< vector<TH1D*> > > hist_iset_vec;
      for (int iupara=0; iupara<_dUParaEff_Option6_UseHists_NUParaBins2; iupara++){
        vector< vector<TH1D*> > hist_iupara_vec;
        for (int ieta=0; ieta<_dUParaEff_Option6_UseHists_NEtaBins2; ieta++){
          vector<TH1D*> hist_ieta_vec;
          for (int ipt=0; ipt<_dUParaEff_Option6_UseHists_NPTBins2; ipt++){
            char hname[500];
            sprintf(hname, "hdUParaRatioEf_UPerp%d_SET%d_UPara%d_Eta%d_PT%d", iuperp, iset, iupara, ieta, ipt);
            TH1D* hist = (TH1D*)_dUParaEff_Option6_UseHists_ParFile2->Get(hname);
            hist_ieta_vec.push_back(hist);
          } // ipt
          hist_iupara_vec.push_back(hist_ieta_vec);
        } // ieta
        hist_iset_vec.push_back(hist_iupara_vec);
      } // iupara
      hist_iuperp_vec.push_back(hist_iset_vec);
    } // iset
    _dUParaEff_Option6_UseHists_hist_UPerpSETUParaEtaPT_vec2.push_back(hist_iuperp_vec);
  } // iuperp



  cout << "Done SetdUParaEffParsModel6UseHists " << endl;
  return true;

}


