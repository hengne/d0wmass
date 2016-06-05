#include "TROOT.h"
#include "EfficiencySmear.hpp"
#include "PHistoTools.hpp"
#include "histograms.hpp"
#include "WZ_Utils.hpp"

#include <iostream>

using namespace std;

// constructor and read in smearing parameters
EfficiencySmear::EfficiencySmear(TString parameter_filename,hist_files &histos,bool includeECtag) {
  PParameterReader parm(parameter_filename.Data());
  
  cout<<"Start EfficiencySmear initialization"<<endl;

  _histos = &histos;

  _run3bool = parm.GetBool("Run3");
  _run4bool = parm.GetBool("Run4");
  _middlerunnumber = parm.GetInt("MiddleRunNumber");

  _makeCheckSmearingPlots =  parm.GetBool("makeCheckSmearingPlots");

  if (_makeCheckSmearingPlots) {
    _histos->add(EFFSMEAR_Hist,"","check_smearing");
    _histos->add(EFFSMEAR_Hist_2D,"","check_smearing");
  }

  // trigger efficiency
  _TrigFrac_ListOne = parm.GetFloat("TrigFrac_ListOne");
  _TrigFrac_ListTwo = parm.GetFloat("TrigFrac_ListTwo");
  _TrigFrac_ListThree = parm.GetFloat("TrigFrac_ListThree");
  _TrigFrac_ListFour = parm.GetFloat("TrigFrac_ListFour");
  _TrigFrac_ListFive = parm.GetFloat("TrigFrac_ListFive");
  _TrigFrac_ListSix = parm.GetFloat("TrigFrac_ListSix");

  //old trigger efficiency
  _TrigFrac_V8_10 = parm.GetFloat("TrigFrac_V8_10");
  _TrigFrac_V11 = parm.GetFloat("TrigFrac_V11");
  _TrigFrac_V12 = parm.GetFloat("TrigFrac_V12");
  _TrigFrac_V13 = parm.GetFloat("TrigFrac_V13");
  _TrigFrac_V14 = parm.GetFloat("TrigFrac_V14");

  // trigger smearing options
  _TrigEff_Smear_Option = parm.GetInt("TrigEff_Smear_Option", 0);

  if(_TrigEff_Smear_Option == 0) cout<<"Will reading trigger efficiency histograms"<<endl;
  else cout<<"Will using trigger efficiency parameterization"<<endl;

  TString trig_v8_10_filename(parm.GetChar("trigeff_V8_10_file"));
  gROOT->ProcessLine(TString(".x ")+trig_v8_10_filename);
  _hTrigEff_V8_10 = (TH1F *)gROOT->FindObject("v8_10_Pt");
  
  TString trig_v11_filename(parm.GetChar("trigeff_V11_file"));
  gROOT->ProcessLine(TString(".x ")+trig_v11_filename);
  _hTrigEff_V11 = (TH1F *)gROOT->FindObject("v11_Pt");

  TString trig_v12_filename(parm.GetChar("trigeff_V12_file"));
  gROOT->ProcessLine(TString(".x ")+trig_v12_filename);
  _hTrigEff_V12 = (TH1F *)gROOT->FindObject("v12_Pt");

  TString trig_v13_filename(parm.GetChar("trigeff_V13_file"));
  gROOT->ProcessLine(TString(".x ")+trig_v13_filename);
  _hTrigEff_V13 = (TH1F *)gROOT->FindObject("v13_Pt");

  TString trig_v14_filename(parm.GetChar("trigeff_V14_file"));
  gROOT->ProcessLine(TString(".x ")+trig_v14_filename);
  _hTrigEff_V14 = (TH1F *)gROOT->FindObject("v14_Pt");


  TString trig_v15_filename(parm.GetChar("trigeff_V15_file"));
  gROOT->ProcessLine(TString(".x ")+trig_v15_filename);
  _hTrigEff_V15 = (TH1F *)gROOT->FindObject("v15_Pt");

  TString trig_v16_filename(parm.GetChar("trigeff_V16_file"));
  gROOT->ProcessLine(TString(".x ")+trig_v16_filename);
  _hTrigEff_V16 = (TH1F *)gROOT->FindObject("v16_Pt");
  
  TString trig_v16b_filename(parm.GetChar("trigeff_V16b_file"));
  gROOT->ProcessLine(TString(".x ")+trig_v16b_filename);
  _hTrigEff_V16h = (TH1F *)gROOT->FindObject("v16b_Pt");

  std::cout << " Done with Trigger Histos" << std::endl;

  _applyDPhiReweight = parm.GetBool("applyDPhiReweight");
  _DPhiReweightFile = parm.GetChar("DPhiReweightFile");
  _applyDPhiZPtReweight = parm.GetBool("applyDPhiZPtReweight");
  _DPhiZPtReweightFile = parm.GetChar("DPhiZPtReweightFile");

  _applyReweightPerLumi = parm.GetBool("applyReweightPerLumi");
  _DPhiZPtReweightFile0 = parm.GetChar("DPhiZPtReweightFile0");
  _DPhiZPtReweightFile2 = parm.GetChar("DPhiZPtReweightFile2");
  _DPhiZPtReweightFile4 = parm.GetChar("DPhiZPtReweightFile4");
  _DPhiZPtReweightFile6 = parm.GetChar("DPhiZPtReweightFile6");

  if (_applyDPhiReweight && _applyDPhiZPtReweight) {
    std::cout << "Yo, you cannot apply both reweights, moron. I'll choose for you." << std::endl;
    _applyDPhiReweight = false;
  }

  if (_applyDPhiReweight) {
    gROOT->ProcessLine(TString(".x ")+_DPhiReweightFile);
    _DPhiReweightHist = (TH2F*) gROOT->FindObject("dphi_reweight");
    cout << "Got dPhi reweight histogram " << _DPhiReweightHist << endl;
    assert(_DPhiReweightHist);
  } else if (_applyDPhiZPtReweight && !_applyReweightPerLumi) {
    gROOT->ProcessLine(TString(".x ")+_DPhiZPtReweightFile);
    _DPhiZPtReweightHist = (TH2F*) gROOT->FindObject("dphi_vs_zpt_reweight");
    cout << "Got dPhi vs zPt reweight histogram " << _DPhiZPtReweightHist << endl;
    assert(_DPhiZPtReweightHist);
  } else if (_applyDPhiZPtReweight && _applyReweightPerLumi) {
    gROOT->ProcessLine(TString(".x ")+_DPhiZPtReweightFile0);
    gROOT->ProcessLine(TString(".x ")+_DPhiZPtReweightFile2);
    gROOT->ProcessLine(TString(".x ")+_DPhiZPtReweightFile4);
    gROOT->ProcessLine(TString(".x ")+_DPhiZPtReweightFile6);
    _DPhiZPtReweightHist0 = (TH2F*) gROOT->FindObject("dphi_vs_zpt_reweight0");
    _DPhiZPtReweightHist2 = (TH2F*) gROOT->FindObject("dphi_vs_zpt_reweight2");
    _DPhiZPtReweightHist4 = (TH2F*) gROOT->FindObject("dphi_vs_zpt_reweight4");
    _DPhiZPtReweightHist6 = (TH2F*) gROOT->FindObject("dphi_vs_zpt_reweight6");
    cout << "Got dPhi vs zPt reweight histograms per lumi " << _DPhiZPtReweightHist0 << " " << _DPhiZPtReweightHist2 << " " 
	 << _DPhiZPtReweightHist4 << " " << _DPhiZPtReweightHist6 << endl;
    assert(_DPhiZPtReweightHist0);
    assert(_DPhiZPtReweightHist2);
    assert(_DPhiZPtReweightHist4);
    assert(_DPhiZPtReweightHist6);
  }
  if(_TrigEff_Smear_Option == 2){
 // reading parameterization
  _TrigEff_P0_lumi02 = parm.GetVDouble("TrigEff_P0_lumi02");
  _TrigEff_P1_lumi02 = parm.GetVDouble("TrigEff_P1_lumi02");
  _TrigEff_P2_lumi02 = parm.GetVDouble("TrigEff_P2_lumi02");
  _TrigEff_P3_lumi02 = parm.GetVDouble("TrigEff_P3_lumi02");
  _TrigEff_P4_lumi02 = parm.GetVDouble("TrigEff_P4_lumi02");

  _TrigEff_P0_lumi24 = parm.GetVDouble("TrigEff_P0_lumi24");
  _TrigEff_P1_lumi24 = parm.GetVDouble("TrigEff_P1_lumi24");
  _TrigEff_P2_lumi24 = parm.GetVDouble("TrigEff_P2_lumi24");
  _TrigEff_P3_lumi24 = parm.GetVDouble("TrigEff_P3_lumi24");
  _TrigEff_P4_lumi24 = parm.GetVDouble("TrigEff_P4_lumi24");

  _TrigEff_P0_lumi46 = parm.GetVDouble("TrigEff_P0_lumi46");
  _TrigEff_P1_lumi46 = parm.GetVDouble("TrigEff_P1_lumi46");
  _TrigEff_P2_lumi46 = parm.GetVDouble("TrigEff_P2_lumi46");
  _TrigEff_P3_lumi46 = parm.GetVDouble("TrigEff_P3_lumi46");
  _TrigEff_P4_lumi46 = parm.GetVDouble("TrigEff_P4_lumi46");

  _TrigEff_P0_lumi6999 = parm.GetVDouble("TrigEff_P0_lumi6999");
  _TrigEff_P1_lumi6999 = parm.GetVDouble("TrigEff_P1_lumi6999");
  _TrigEff_P2_lumi6999 = parm.GetVDouble("TrigEff_P2_lumi6999");
  _TrigEff_P3_lumi6999 = parm.GetVDouble("TrigEff_P3_lumi6999");
  _TrigEff_P4_lumi6999 = parm.GetVDouble("TrigEff_P4_lumi6999");

  }else if(_TrigEff_Smear_Option == 4){
 // reading parameterization

  _TrigEff_P0_lumi02_run3 = parm.GetVDouble("TrigEff_P0_lumi02_run3");
  _TrigEff_P1_lumi02_run3 = parm.GetVDouble("TrigEff_P1_lumi02_run3");
  _TrigEff_P2_lumi02_run3 = parm.GetVDouble("TrigEff_P2_lumi02_run3");
  _TrigEff_P3_lumi02_run3 = parm.GetVDouble("TrigEff_P3_lumi02_run3");
  _TrigEff_P4_lumi02_run3 = parm.GetVDouble("TrigEff_P4_lumi02_run3");

  _TrigEff_P0_lumi24_run3 = parm.GetVDouble("TrigEff_P0_lumi24_run3");
  _TrigEff_P1_lumi24_run3 = parm.GetVDouble("TrigEff_P1_lumi24_run3");
  _TrigEff_P2_lumi24_run3 = parm.GetVDouble("TrigEff_P2_lumi24_run3");
  _TrigEff_P3_lumi24_run3 = parm.GetVDouble("TrigEff_P3_lumi24_run3");
  _TrigEff_P4_lumi24_run3 = parm.GetVDouble("TrigEff_P4_lumi24_run3");

  _TrigEff_P0_lumi46_run3 = parm.GetVDouble("TrigEff_P0_lumi46_run3");
  _TrigEff_P1_lumi46_run3 = parm.GetVDouble("TrigEff_P1_lumi46_run3");
  _TrigEff_P2_lumi46_run3 = parm.GetVDouble("TrigEff_P2_lumi46_run3");
  _TrigEff_P3_lumi46_run3 = parm.GetVDouble("TrigEff_P3_lumi46_run3");
  _TrigEff_P4_lumi46_run3 = parm.GetVDouble("TrigEff_P4_lumi46_run3");

  _TrigEff_P0_lumi6999_run3 = parm.GetVDouble("TrigEff_P0_lumi6999_run3");
  _TrigEff_P1_lumi6999_run3 = parm.GetVDouble("TrigEff_P1_lumi6999_run3");
  _TrigEff_P2_lumi6999_run3 = parm.GetVDouble("TrigEff_P2_lumi6999_run3");
  _TrigEff_P3_lumi6999_run3 = parm.GetVDouble("TrigEff_P3_lumi6999_run3");
  _TrigEff_P4_lumi6999_run3 = parm.GetVDouble("TrigEff_P4_lumi6999_run3");

  _TrigEff_P0_lumi02_run4 = parm.GetVDouble("TrigEff_P0_lumi02_run4");
  _TrigEff_P1_lumi02_run4 = parm.GetVDouble("TrigEff_P1_lumi02_run4");
  _TrigEff_P2_lumi02_run4 = parm.GetVDouble("TrigEff_P2_lumi02_run4");
  _TrigEff_P3_lumi02_run4 = parm.GetVDouble("TrigEff_P3_lumi02_run4");
  _TrigEff_P4_lumi02_run4 = parm.GetVDouble("TrigEff_P4_lumi02_run4");

  _TrigEff_P0_lumi24_run4 = parm.GetVDouble("TrigEff_P0_lumi24_run4");
  _TrigEff_P1_lumi24_run4 = parm.GetVDouble("TrigEff_P1_lumi24_run4");
  _TrigEff_P2_lumi24_run4 = parm.GetVDouble("TrigEff_P2_lumi24_run4");
  _TrigEff_P3_lumi24_run4 = parm.GetVDouble("TrigEff_P3_lumi24_run4");
  _TrigEff_P4_lumi24_run4 = parm.GetVDouble("TrigEff_P4_lumi24_run4");

  _TrigEff_P0_lumi46_run4 = parm.GetVDouble("TrigEff_P0_lumi46_run4");
  _TrigEff_P1_lumi46_run4 = parm.GetVDouble("TrigEff_P1_lumi46_run4");
  _TrigEff_P2_lumi46_run4 = parm.GetVDouble("TrigEff_P2_lumi46_run4");
  _TrigEff_P3_lumi46_run4 = parm.GetVDouble("TrigEff_P3_lumi46_run4");
  _TrigEff_P4_lumi46_run4 = parm.GetVDouble("TrigEff_P4_lumi46_run4");

  _TrigEff_P0_lumi6999_run4 = parm.GetVDouble("TrigEff_P0_lumi6999_run4");
  _TrigEff_P1_lumi6999_run4 = parm.GetVDouble("TrigEff_P1_lumi6999_run4");
  _TrigEff_P2_lumi6999_run4 = parm.GetVDouble("TrigEff_P2_lumi6999_run4");
  _TrigEff_P3_lumi6999_run4 = parm.GetVDouble("TrigEff_P3_lumi6999_run4");
  _TrigEff_P4_lumi6999_run4 = parm.GetVDouble("TrigEff_P4_lumi6999_run4");

  }else if(_TrigEff_Smear_Option == 5){
 // reading parameterization

  _TrigEff_P0_lumi03_run3 = parm.GetVDouble("TrigEff_P0_lumi03_run3");
  _TrigEff_P1_lumi03_run3 = parm.GetVDouble("TrigEff_P1_lumi03_run3");
  _TrigEff_P2_lumi03_run3 = parm.GetVDouble("TrigEff_P2_lumi03_run3");
  _TrigEff_P3_lumi03_run3 = parm.GetVDouble("TrigEff_P3_lumi03_run3");
  _TrigEff_P4_lumi03_run3 = parm.GetVDouble("TrigEff_P4_lumi03_run3");
  _TrigEff_P5_lumi03_run3 = parm.GetVDouble("TrigEff_P5_lumi03_run3");

  _TrigEff_P0_lumi3999_run3 = parm.GetVDouble("TrigEff_P0_lumi3999_run3");
  _TrigEff_P1_lumi3999_run3 = parm.GetVDouble("TrigEff_P1_lumi3999_run3");
  _TrigEff_P2_lumi3999_run3 = parm.GetVDouble("TrigEff_P2_lumi3999_run3");
  _TrigEff_P3_lumi3999_run3 = parm.GetVDouble("TrigEff_P3_lumi3999_run3");
  _TrigEff_P4_lumi3999_run3 = parm.GetVDouble("TrigEff_P4_lumi3999_run3");
  _TrigEff_P5_lumi3999_run3 = parm.GetVDouble("TrigEff_P5_lumi3999_run3");

  _TrigEff_P0_lumi03_run4 = parm.GetVDouble("TrigEff_P0_lumi03_run4");
  _TrigEff_P1_lumi03_run4 = parm.GetVDouble("TrigEff_P1_lumi03_run4");
  _TrigEff_P2_lumi03_run4 = parm.GetVDouble("TrigEff_P2_lumi03_run4");
  _TrigEff_P3_lumi03_run4 = parm.GetVDouble("TrigEff_P3_lumi03_run4");
  _TrigEff_P4_lumi03_run4 = parm.GetVDouble("TrigEff_P4_lumi03_run4");
  _TrigEff_P5_lumi03_run4 = parm.GetVDouble("TrigEff_P5_lumi03_run4");

  _TrigEff_P0_lumi3999_run4 = parm.GetVDouble("TrigEff_P0_lumi3999_run4");
  _TrigEff_P1_lumi3999_run4 = parm.GetVDouble("TrigEff_P1_lumi3999_run4");
  _TrigEff_P2_lumi3999_run4 = parm.GetVDouble("TrigEff_P2_lumi3999_run4");
  _TrigEff_P3_lumi3999_run4 = parm.GetVDouble("TrigEff_P3_lumi3999_run4");
  _TrigEff_P4_lumi3999_run4 = parm.GetVDouble("TrigEff_P4_lumi3999_run4");
  _TrigEff_P5_lumi3999_run4 = parm.GetVDouble("TrigEff_P5_lumi3999_run4");

  }else if(_TrigEff_Smear_Option == 6){

    TFile* triggerModel = TFile::Open(parm.GetChar("trigeff_p20_run2b34_file"));

    s2ElecPt_triggerEff_0_0_run2b3 = (TSpline3*) triggerModel->Get("s2ElecPt_triggerEff_0_0_run2b3");
    s2ElecPt_triggerEff_0_1_run2b3 = (TSpline3*) triggerModel->Get("s2ElecPt_triggerEff_0_1_run2b3");
    s2ElecPt_triggerEff_1_0_run2b3 = (TSpline3*) triggerModel->Get("s2ElecPt_triggerEff_1_0_run2b3");

    s2ElecPt_triggerEff_0_0_run2b4 = (TSpline3*) triggerModel->Get("s2ElecPt_triggerEff_0_0_run2b4");
    s2ElecPt_triggerEff_0_1_run2b4 = (TSpline3*) triggerModel->Get("s2ElecPt_triggerEff_0_1_run2b4");
    s2ElecPt_triggerEff_1_0_run2b4 = (TSpline3*) triggerModel->Get("s2ElecPt_triggerEff_1_0_run2b4");

  }else{
  // reading parameterization
  _TrigEff_P0 = parm.GetVDouble("TrigEff_P0");
  _TrigEff_P1 = parm.GetVDouble("TrigEff_P1");
  _TrigEff_P2 = parm.GetVDouble("TrigEff_P2");
  _TrigEff_P3 = parm.GetVDouble("TrigEff_P3");
  _TrigEff_P4 = parm.GetVDouble("TrigEff_P4");
  }
  // use the following switch to control whether you want to study systematic uncertainty 
  // due to trigger efficiency (only when TrigEff_Smear_Option == 1)
  _Study_TrigEff_Systematics = parm.GetBool("Study_TrigEff_Systematics");

  // trigger efficiency uncertainty
  _TrigEff_P0_Uncertainty = parm.GetVDouble("TrigEff_P0_Uncertainty");
  _TrigEff_P1_Uncertainty = parm.GetVDouble("TrigEff_P1_Uncertainty");
  _TrigEff_P2_Uncertainty = parm.GetVDouble("TrigEff_P2_Uncertainty");
  _TrigEff_P3_Uncertainty = parm.GetVDouble("TrigEff_P3_Uncertainty");
  _TrigEff_P4_Uncertainty = parm.GetVDouble("TrigEff_P4_Uncertainty");
  

  TString trig_filename(parm.GetChar("trigeff_p20_file","../p20/trigs.map"));
  ifstream trigfile(trig_filename);
  if(!trigfile) cout<<"Please provide a file called ../p20/trigs.map"<<endl;
  
  string line;
  int runnum;
  int nlines=0;
  vector<string> trignamevec;

  while (getline(trigfile, line) ) { // loop over all lines
    runnum = 0;
    trignamevec.clear();
    nlines++;
    
    string trigname;
    istringstream newline(line);
    newline >> runnum;
    while (newline >> trigname) {
      trignamevec.push_back( trigname );
    }
    _trigger_map[runnum]=trignamevec;
  } // loop over all lines
  
  cout<<"Read "<<nlines<<" lines from trigs.map"<<endl;
  
  trigfile.close();
  


  // preselection efficiency
  TString preseleff_filename(parm.GetChar("preseff_file"));
  gROOT->ProcessLine(TString(".x ")+preseleff_filename);
  _hPreselEff = (TH1F *)gROOT->FindObject("PreSelEffDetEta");


  // Loose Track matching efficiency
  _applypreseltrkmatch = parm.GetBool("apply_presel_trk_match");
  
  TString loosetrkeff_filename_run3(parm.GetChar("loose_trkeff_file_run3"));
  gROOT->ProcessLine(TString(".x ")+loosetrkeff_filename_run3);
  TString loosetrkeff_filename_run4(parm.GetChar("loose_trkeff_file_run4"));
  gROOT->ProcessLine(TString(".x ")+loosetrkeff_filename_run4);
  TString loosetrkeff_filename_EC(parm.GetChar("loose_trkeff_file_EC"));
  gROOT->ProcessLine(TString(".x ")+loosetrkeff_filename_EC);
  // vs physics eta and primary vertex
  _ApplyLooseTrackMatchEfficiency = parm.GetBool("ApplyLooseTrackMatchEfficiency");
  _hlooseTrkEffRun3 = (TH3F *)gROOT->FindObject("loosetrkEffVsEtaZvtxRun3");
  _hlooseTrkEffRun4 = (TH3F *)gROOT->FindObject("loosetrkEffVsEtaZvtxRun4");
  _hlooseTrkEff_EC = (TH2F *)gROOT->FindObject("loosetrkEffVsEtaZvtx_EC");
  _simulatelooseTrkVtxDepEC = parm.GetBool("loose_simulateTrkVtxDepEC");

  // vs detector eta only
  TString loosetrkeff_filename_deteta(parm.GetChar("loose_trkeff_file_deteta"));
  gROOT->ProcessLine(TString(".x ")+loosetrkeff_filename_deteta);
  _hlooseTrkEff_deteta = (TH1F *)gROOT->FindObject("loose_trkEffVsDetEta");



  
  // EMID efficiency
  TString ideff_filename(parm.GetChar("ideff_file"));
  gROOT->ProcessLine(TString(".x ")+ideff_filename);
  _hEMIDEff = (TH1F *)gROOT->FindObject("idEffDetEta");


  // Electron Phi efficiency
  TString phieff_filename(parm.GetChar("elecphieff_file"));
  gROOT->ProcessLine(TString(".x ")+phieff_filename);
  _RatioDataToPMCS = (TH1F *)gROOT->FindObject("RatioDataToPMCS");

   TString phieff_filename4(parm.GetChar("elecphieff_file_run4"));
  gROOT->ProcessLine(TString(".x ")+phieff_filename4);
  _RatioDataToPMCSRun4 = (TH1F *)gROOT->FindObject("RatioDataToPMCSRun4");

  
  // Track matching efficiency
  _ApplyTrackMatchEfficiency = parm.GetBool("ApplyTrackMatchEfficiency");
  TString trkeff_filename_run3(parm.GetChar("trkeff_file_run3"));
  gROOT->ProcessLine(TString(".x ")+trkeff_filename_run3);
  TString trkeff_filename_run4(parm.GetChar("trkeff_file_run4"));
  gROOT->ProcessLine(TString(".x ")+trkeff_filename_run4);
  TString trkeff_filename_EC(parm.GetChar("trkeff_file_EC"));
  gROOT->ProcessLine(TString(".x ")+trkeff_filename_EC);
  // vs physics eta and primary vertex
  _hTrkEffRun3 = (TH2F *)gROOT->FindObject("trkEffVsEtaZvtxRun3");
  _hTrkEffRun4 = (TH2F *)gROOT->FindObject("trkEffVsEtaZvtxRun4");
  _hTrkEff_EC = (TH2F *)gROOT->FindObject("trkEffVsEtaZvtx_EC");
  _simulateTrkVtxDepEC = parm.GetBool("simulateTrkVtxDepEC");

  // vs detector eta only
  TString trkeff_filename_deteta(parm.GetChar("trkeff_file_deteta"));
  gROOT->ProcessLine(TString(".x ")+trkeff_filename_deteta);
  _hTrkEff_deteta = (TH1F *)gROOT->FindObject("trkEffVsDetEta");

  // Eta hack for sensitivity studies
  _DoEtaHack = parm.GetBool("DoEtaHack");
  if (_DoEtaHack) {
    _EtaHackFile = parm.GetChar("EtaHackFile");
    TFile* fHack = new TFile(_EtaHackFile);
    _hEtaHack = (TH1F*)fHack->Get("ratio");
  }

  // pT-dependencies in the efficiencies
  _simulate_pT_dependence = parm.GetBool("simulate_pT_dependence");
  if(_simulate_pT_dependence) cout << "Simulate pT dependence for CC region"<<endl;

  _CCideff_pTphyEta_ParameterA = parm.GetVDouble("CCideff_pTphyEta_ParameterA");
  _CCideff_pTphyEta_ParameterB = parm.GetVDouble("CCideff_pTphyEta_ParameterB");
  _CCtrkeff_pTphyEta_ParameterA = parm.GetVDouble("CCtrkeff_pTphyEta_ParameterA");
  _CCtrkeff_pTphyEta_ParameterB = parm.GetVDouble("CCtrkeff_pTphyEta_ParameterB");
  //
  _CCcluseff_pTphyEta_ParameterA = parm.GetVDouble("CCcluseff_pTphyEta_ParameterA");
  _CCcluseff_pTphyEta_ParameterB = parm.GetVDouble("CCcluseff_pTphyEta_ParameterB");

  // corrections to pT/eta dependence from Tag/Probe
  _includeECtag=includeECtag;
  //
  _apply_HMxeff_ratio = parm.GetBool("apply_HMxeff_ratio");
  if (_apply_HMxeff_ratio) {
    cout << "apply HMx efficiency ratio";
    if (_includeECtag) cout << ", including EC tags"<<endl;
    else cout << ", excluding EC tags"<<endl;
  }
  _apply_TRKeff_ratio = parm.GetBool("apply_TRKeff_ratio");
  if (_apply_TRKeff_ratio) {
    cout << "apply TRK efficiency ratio";
    if (_includeECtag) cout << ", including EC tags"<<endl;
    else cout << ", excluding EC tags"<<endl;
  }
  //
  _eff_ratios_function = parm.GetInt("eff_ratios_function", 0);
  //
  if (_includeECtag) {
    _CChmxeffratio_pTphyEta_ParameterA = parm.GetVDouble("CCECtag_CChmxeffratio_pTphyEta_ParameterA");
    _CChmxeffratio_pTphyEta_ParameterB = parm.GetVDouble("CCECtag_CChmxeffratio_pTphyEta_ParameterB");
    _CChmxeffratio_pTphyEta_ParameterC = parm.GetVDouble("CCECtag_CChmxeffratio_pTphyEta_ParameterC");
    _CChmxeffratio_pTphyEta_ParameterD = parm.GetVDouble("CCECtag_CChmxeffratio_pTphyEta_ParameterD");
    _CChmxeffratio_pTphyEta_ParameterE = parm.GetVDouble("CCECtag_CChmxeffratio_pTphyEta_ParameterE");
    //
    _CCtrkeffratio_pTphyEta_ParameterA = parm.GetVDouble("CCECtag_CCtrkeffratio_pTphyEta_ParameterA");
    _CCtrkeffratio_pTphyEta_ParameterB = parm.GetVDouble("CCECtag_CCtrkeffratio_pTphyEta_ParameterB");
    _CCtrkeffratio_pTphyEta_ParameterC = parm.GetVDouble("CCECtag_CCtrkeffratio_pTphyEta_ParameterC");
    _CCtrkeffratio_pTphyEta_ParameterD = parm.GetVDouble("CCECtag_CCtrkeffratio_pTphyEta_ParameterD");
    _CCtrkeffratio_pTphyEta_ParameterE = parm.GetVDouble("CCECtag_CCtrkeffratio_pTphyEta_ParameterE");
  } else {
    _CChmxeffratio_pTphyEta_ParameterA = parm.GetVDouble("CCtag_CChmxeffratio_pTphyEta_ParameterA");
    _CChmxeffratio_pTphyEta_ParameterB = parm.GetVDouble("CCtag_CChmxeffratio_pTphyEta_ParameterB");
    _CChmxeffratio_pTphyEta_ParameterC = parm.GetVDouble("CCtag_CChmxeffratio_pTphyEta_ParameterC");
    _CChmxeffratio_pTphyEta_ParameterD = parm.GetVDouble("CCtag_CChmxeffratio_pTphyEta_ParameterD");
    _CChmxeffratio_pTphyEta_ParameterE = parm.GetVDouble("CCtag_CChmxeffratio_pTphyEta_ParameterE");
    //
    _CCtrkeffratio_pTphyEta_ParameterA = parm.GetVDouble("CCtag_CCtrkeffratio_pTphyEta_ParameterA");
    _CCtrkeffratio_pTphyEta_ParameterB = parm.GetVDouble("CCtag_CCtrkeffratio_pTphyEta_ParameterB");
    _CCtrkeffratio_pTphyEta_ParameterC = parm.GetVDouble("CCtag_CCtrkeffratio_pTphyEta_ParameterC");
    _CCtrkeffratio_pTphyEta_ParameterD = parm.GetVDouble("CCtag_CCtrkeffratio_pTphyEta_ParameterD");
    _CCtrkeffratio_pTphyEta_ParameterE = parm.GetVDouble("CCtag_CCtrkeffratio_pTphyEta_ParameterE");
  }

  // AddOnEff
  _ApplyAddOnEff_Wen = parm.GetBool("ApplyAddOnEff_Wen", false);
  _ApplyAddOnEff_Zee = parm.GetBool("ApplyAddOnEff_Zee", false);

  if (_ApplyAddOnEff_Wen) {
    _AddOnEff_Wen_TEPT_On = parm.GetBool("AddOnEff_Wen_TEPT_On", false);
    if (_AddOnEff_Wen_TEPT_On) {
      _AddOnEff_Wen_TEPT_Pars = parm.GetVDouble("AddOnEff_Wen_TEPT_Pars");
    }
    _AddOnEff_Wen_DetEta_On = parm.GetBool("AddOnEff_Wen_DetEta_On", false);
    if (_AddOnEff_Wen_DetEta_On) {
        TString rootmacro = (parm.GetChar("AddOnEff_Wen_DetEta_Pars"));
        gROOT->ProcessLine(TString(".x ")+rootmacro);
        _AddOnEff_Wen_DetEta_Pars = (TH1D*)gROOT->FindObject("hElecDetEtaRatio"); 
    }
    _AddOnEff_Wen_SET_On = parm.GetBool("AddOnEff_Wen_SET_On", false);
    if (_AddOnEff_Wen_SET_On){
      _AddOnEff_Wen_SET_Pars = parm.GetVDouble("AddOnEff_Wen_SET_Pars");
    }
  }

  if (_ApplyAddOnEff_Zee) {
    _AddOnEff_Zee_TEPT_On = parm.GetBool("AddOnEff_Zee_TEPT_On", false);
    if (_AddOnEff_Zee_TEPT_On) {
      _AddOnEff_Zee_TEPT_Pars = parm.GetVDouble("AddOnEff_Zee_TEPT_Pars");
    }
    _AddOnEff_Zee_DetEta_On = parm.GetBool("AddOnEff_Zee_DetEta_On", false);
    if (_AddOnEff_Zee_DetEta_On) {
        TString rootmacro = (parm.GetChar("AddOnEff_Zee_DetEta_Pars"));
        gROOT->ProcessLine(TString(".x ")+rootmacro);
        _AddOnEff_Zee_DetEta_Pars = (TH1D*)gROOT->FindObject("hElecDetEtaRatio");
    }
    _AddOnEff_Zee_CorrelTEPT_On = parm.GetBool("AddOnEff_Zee_CorrelTEPT_On", false);
    if (_AddOnEff_Zee_CorrelTEPT_On) {
      _AddOnEff_Zee_CorrelTEPT_DontKnowPars = parm.GetVDouble("AddOnEff_Zee_CorrelTEPT_DontKnowPars");
      _AddOnEff_Zee_CorrelTEPT_OnePassPars = parm.GetVDouble("AddOnEff_Zee_CorrelTEPT_OnePassPars");
      _AddOnEff_Zee_CorrelTEPT_OneNotPassPars = parm.GetVDouble("AddOnEff_Zee_CorrelTEPT_OneNotPassPars");
    }
    _AddOnEff_Zee_SET_On = parm.GetBool("AddOnEff_Zee_SET_On", false);
    if (_AddOnEff_Zee_SET_On){
      _AddOnEff_Zee_SET_Pars = parm.GetVDouble("AddOnEff_Zee_SET_Pars");
    }
  }

  cout<<"Finished EfficiencySmear initialization"<<endl;
}

Double_t EfficiencySmear::ApplyRecoilReweight(Double_t DPhi, Double_t zPt, Double_t luminosity) {

  Bool_t status;
  Double_t val=1., err=0.;

  if (_applyDPhiReweight) {
    status = PHistoTools::getBinValues(_DPhiReweightHist, DPhi, zPt, val, err);
  } else if (_applyDPhiZPtReweight && !_applyReweightPerLumi) {
    status = PHistoTools::getBinValues(_DPhiZPtReweightHist, DPhi, zPt, val, err);
  } else if (_applyDPhiZPtReweight && _applyReweightPerLumi) {
    
    if (luminosity >= 0.0 && luminosity < 2.0) {
      status = PHistoTools::getBinValues(_DPhiZPtReweightHist0, DPhi, zPt, val, err);
    } else if (luminosity >= 2.0 && luminosity < 4.0) {
      status = PHistoTools::getBinValues(_DPhiZPtReweightHist2, DPhi, zPt, val, err);
    } else if (luminosity >= 4.0 && luminosity < 6.0) {
      status = PHistoTools::getBinValues(_DPhiZPtReweightHist4, DPhi, zPt, val, err);
    } else if (luminosity >= 6.0) {
      status = PHistoTools::getBinValues(_DPhiZPtReweightHist6, DPhi, zPt, val, err);
    }

  }

  return val;
}
 
  

int EfficiencySmear::TriggerType(Int_t runNo){
  
  int triglist_flag =0;
  Bool_t _E1_SHT25 = kFALSE;
  Bool_t _E1_SHT27 = kFALSE;
  vector<string> trigs_used = _trigger_map[runNo];
  for(unsigned int i = 0; i < trigs_used.size(); i++) { 
    if(trigs_used[i]=="E1_SHT25")     _E1_SHT25 = kTRUE;
    if(trigs_used[i]=="E1_SHT27")     _E1_SHT27 = kTRUE;
  }
  
  if ((runNo>=221989 and runNo <= 240438) || (runNo>=240576 and runNo <= 240743))
    triglist_flag = 1;
  else if ( (runNo>= 240762 ) || (runNo>=240476 and runNo <= 240566)){
    triglist_flag = 2;
    if (!_E1_SHT25){
      triglist_flag = 3;
      if (!_E1_SHT27){
	std::cerr << " Logic Error" << std::endl;
	abort();
      }
    }
  }
  return triglist_flag;
  
}


//Trigger Efficiency (vs pT)
bool EfficiencySmear::passesTriggerEff(PMCSEMObj part, TRandom3 *dummy, double randomNum, Int_t runNum, double* externalRndm, int force_trigger) {
  double val=1., err=0.;

  // trigger efficiency for different trigger versions
  //double randomNum = dummy->Uniform(0., 1.);
  
  // electron pT
  double lumi = part.getLumi();
  double pT = part.ppt();
  Bool_t _E1_SHT25 = kFALSE;
  Bool_t _E1_SHT27 = kFALSE;
  if (!force_trigger){
    vector<string> trigs_used = _trigger_map[runNum];
    for(unsigned int i = 0; i < trigs_used.size(); i++) { 
      if(trigs_used[i]=="E1_SHT25")     _E1_SHT25 = kTRUE;
      if(trigs_used[i]=="E1_SHT27")     _E1_SHT27 = kTRUE;
    }
  }
  else if(force_trigger==1){
    _E1_SHT25 = kTRUE;
  } 
  else if(force_trigger==2){
    _E1_SHT25 = kTRUE;
    _E1_SHT27 = kTRUE;
  } 
  else if(force_trigger==3){
    _E1_SHT25 = kFALSE;
    _E1_SHT27 = kTRUE;
  } 
  


  if(_TrigEff_Smear_Option == 0) {    // reading histograms
    if(randomNum <= _TrigFrac_V8_10) {
      Bool_t status = PHistoTools::getBinValues(_hTrigEff_V8_10, pT, val, err);
    } else if (randomNum <= (_TrigFrac_V8_10+_TrigFrac_V11)) {
      Bool_t status = PHistoTools::getBinValues(_hTrigEff_V11, pT, val, err);
    } else if (randomNum <= (_TrigFrac_V8_10+_TrigFrac_V11+_TrigFrac_V12)) {
      Bool_t status = PHistoTools::getBinValues(_hTrigEff_V12, pT, val, err);
    } else if (randomNum <= (_TrigFrac_V8_10+_TrigFrac_V11+_TrigFrac_V12+_TrigFrac_V13)) {
      Bool_t status = PHistoTools::getBinValues(_hTrigEff_V13, pT, val, err);
    } else {
      Bool_t status = PHistoTools::getBinValues(_hTrigEff_V14, pT, val, err);
    } 
  } else {   
    // using parameterizations
    double eff_p0, eff_p1, eff_p2, eff_p3, eff_p4, eff_p5, eff_p0_uncertainty, eff_p1_uncertainty, eff_p2_uncertainty, eff_p3_uncertainty, eff_p4_uncertainty;
    eff_p5 = 0.0;
    if (_TrigEff_Smear_Option == 1) { 
    
      if(randomNum <= _TrigFrac_ListOne) {
	eff_p0 = _TrigEff_P0[0];
	eff_p1 = _TrigEff_P1[0];
	eff_p2 = _TrigEff_P2[0];
	eff_p3=  _TrigEff_P3[0];
	eff_p4 = _TrigEff_P4[0];
	eff_p0_uncertainty = _TrigEff_P0_Uncertainty[0];
	eff_p1_uncertainty = _TrigEff_P1_Uncertainty[0];
	eff_p2_uncertainty = _TrigEff_P2_Uncertainty[0];
	eff_p3_uncertainty = _TrigEff_P3_Uncertainty[0];
	eff_p4_uncertainty = _TrigEff_P4_Uncertainty[0];
      } else if (randomNum <= (_TrigFrac_ListOne+_TrigFrac_ListTwo)) {
	eff_p0 = _TrigEff_P0[1];
	eff_p1 = _TrigEff_P1[1];
	eff_p2 = _TrigEff_P2[1];
	eff_p3 = _TrigEff_P3[1];
	eff_p4 = _TrigEff_P4[1];
	eff_p0_uncertainty = _TrigEff_P0_Uncertainty[1];
	eff_p1_uncertainty = _TrigEff_P1_Uncertainty[1];
	eff_p2_uncertainty = _TrigEff_P2_Uncertainty[1];
	eff_p3_uncertainty = _TrigEff_P3_Uncertainty[1];
	eff_p4_uncertainty = _TrigEff_P4_Uncertainty[1];
      } else if (randomNum <= (_TrigFrac_ListOne+_TrigFrac_ListTwo+_TrigFrac_ListThree)) {
	eff_p0 = _TrigEff_P0[2];
	eff_p1 = _TrigEff_P1[2];
	eff_p2 = _TrigEff_P2[2];
	eff_p3 = _TrigEff_P3[2];
	eff_p4 = _TrigEff_P4[2];
	eff_p0_uncertainty = _TrigEff_P0_Uncertainty[2];
	eff_p1_uncertainty = _TrigEff_P1_Uncertainty[2];
	eff_p2_uncertainty = _TrigEff_P2_Uncertainty[2];
	eff_p3_uncertainty = _TrigEff_P3_Uncertainty[2];
	eff_p4_uncertainty = _TrigEff_P4_Uncertainty[2];
      } else if (randomNum <= (_TrigFrac_ListOne+_TrigFrac_ListTwo+_TrigFrac_ListThree + _TrigFrac_ListFour  || _TrigFrac_ListFive==0. ))  {
	eff_p0 = _TrigEff_P0[3];
	eff_p1 = _TrigEff_P1[3];
	eff_p2 = _TrigEff_P2[3];
	eff_p3 = _TrigEff_P3[3];
	eff_p4 = _TrigEff_P4[3];
	eff_p0_uncertainty = _TrigEff_P0_Uncertainty[3];
	eff_p1_uncertainty = _TrigEff_P1_Uncertainty[3];
	eff_p2_uncertainty = _TrigEff_P2_Uncertainty[3];
	eff_p3_uncertainty = _TrigEff_P3_Uncertainty[3];
	eff_p4_uncertainty = _TrigEff_P4_Uncertainty[3];
      } else if (randomNum <= (_TrigFrac_ListOne+_TrigFrac_ListTwo+_TrigFrac_ListThree + _TrigFrac_ListFour + _TrigFrac_ListFive )) {
	eff_p0 = _TrigEff_P0[4];
	eff_p1 = _TrigEff_P1[4];
	eff_p2 = _TrigEff_P2[4];
	eff_p3 = _TrigEff_P3[4];
	eff_p4 = _TrigEff_P4[4];
	eff_p0_uncertainty = _TrigEff_P0_Uncertainty[4];
	eff_p1_uncertainty = _TrigEff_P1_Uncertainty[4];
	eff_p2_uncertainty = _TrigEff_P2_Uncertainty[4];
	eff_p3_uncertainty = _TrigEff_P3_Uncertainty[4];
	eff_p4_uncertainty = _TrigEff_P4_Uncertainty[4];
      }else if ((randomNum <= (_TrigFrac_ListOne+_TrigFrac_ListTwo+_TrigFrac_ListThree + _TrigFrac_ListFour + _TrigFrac_ListFive + _TrigFrac_ListSix )) &&  (part.getLumi() < (200./36.)))  {
	eff_p0 = _TrigEff_P0[5];
	eff_p1 = _TrigEff_P1[5];
	eff_p2 = _TrigEff_P2[5];
	eff_p3 = _TrigEff_P3[5];
	eff_p4 = _TrigEff_P4[5];
	eff_p0_uncertainty = _TrigEff_P0_Uncertainty[5];
	eff_p1_uncertainty = _TrigEff_P1_Uncertainty[5];
	eff_p2_uncertainty = _TrigEff_P2_Uncertainty[5];
	eff_p3_uncertainty = _TrigEff_P3_Uncertainty[5];
	eff_p4_uncertainty = _TrigEff_P4_Uncertainty[5];
      }
      else {
	eff_p0 = _TrigEff_P0[6];
	eff_p1 = _TrigEff_P1[6];
	eff_p2 = _TrigEff_P2[6];
	eff_p3 = _TrigEff_P3[6];
	eff_p4 = _TrigEff_P4[6];
	eff_p0_uncertainty = _TrigEff_P0_Uncertainty[6];
	eff_p1_uncertainty = _TrigEff_P1_Uncertainty[6];
	eff_p2_uncertainty = _TrigEff_P2_Uncertainty[6];
	eff_p3_uncertainty = _TrigEff_P3_Uncertainty[6];
	eff_p4_uncertainty = _TrigEff_P4_Uncertainty[6];

      }
    }
   if (_TrigEff_Smear_Option == 2) { 
     if (_E1_SHT25 && _E1_SHT27){
       if(lumi >= 0 && lumi < 2){
	 eff_p0 = _TrigEff_P0_lumi02[5];
	 eff_p1 = _TrigEff_P1_lumi02[5];
	 eff_p2 = _TrigEff_P2_lumi02[5];
	 eff_p3 = _TrigEff_P3_lumi02[5];
	 eff_p4 = _TrigEff_P4_lumi02[5];
       }else if(lumi >= 2 && lumi < 4){
	 eff_p0 = _TrigEff_P0_lumi24[5];
	 eff_p1 = _TrigEff_P1_lumi24[5];
	 eff_p2 = _TrigEff_P2_lumi24[5];
	 eff_p3 = _TrigEff_P3_lumi24[5];
	 eff_p4 = _TrigEff_P4_lumi24[5];
       }else if(lumi >= 4 && lumi < 6){
	 eff_p0 = _TrigEff_P0_lumi46[5];
	 eff_p1 = _TrigEff_P1_lumi46[5];
	 eff_p2 = _TrigEff_P2_lumi46[5];
	 eff_p3 = _TrigEff_P3_lumi46[5];
	 eff_p4 = _TrigEff_P4_lumi46[5];
       }else{//6+
	 eff_p0 = _TrigEff_P0_lumi6999[5];
	 eff_p1 = _TrigEff_P1_lumi6999[5];
	 eff_p2 = _TrigEff_P2_lumi6999[5];
	 eff_p3 = _TrigEff_P3_lumi6999[5];
	 eff_p4 = _TrigEff_P4_lumi6999[5];
       }
       eff_p0_uncertainty = _TrigEff_P0_Uncertainty[5];
       eff_p1_uncertainty = _TrigEff_P1_Uncertainty[5];
       eff_p2_uncertainty = _TrigEff_P2_Uncertainty[5];
       eff_p3_uncertainty = _TrigEff_P3_Uncertainty[5];
       eff_p4_uncertainty = _TrigEff_P4_Uncertainty[5];
     }
     else if (_E1_SHT27 && !_E1_SHT25){
       if(lumi >= 0 && lumi < 2){
	 eff_p0 = _TrigEff_P0_lumi02[6];
	 eff_p1 = _TrigEff_P1_lumi02[6];
	 eff_p2 = _TrigEff_P2_lumi02[6];
	 eff_p3 = _TrigEff_P3_lumi02[6];
	 eff_p4 = _TrigEff_P4_lumi02[6];
       }else if(lumi >= 2 && lumi < 4){
	 eff_p0 = _TrigEff_P0_lumi24[6];
	 eff_p1 = _TrigEff_P1_lumi24[6];
	 eff_p2 = _TrigEff_P2_lumi24[6];
	 eff_p3 = _TrigEff_P3_lumi24[6];
	 eff_p4 = _TrigEff_P4_lumi24[6];
       }else if(lumi >= 4 && lumi < 6){
	 eff_p0 = _TrigEff_P0_lumi46[6];
	 eff_p1 = _TrigEff_P1_lumi46[6];
	 eff_p2 = _TrigEff_P2_lumi46[6];
	 eff_p3 = _TrigEff_P3_lumi46[6];
	 eff_p4 = _TrigEff_P4_lumi46[6];
       }else{//6+
	 eff_p0 = _TrigEff_P0_lumi6999[6];
	 eff_p1 = _TrigEff_P1_lumi6999[6];
	 eff_p2 = _TrigEff_P2_lumi6999[6];
	 eff_p3 = _TrigEff_P3_lumi6999[6];
	 eff_p4 = _TrigEff_P4_lumi6999[6];
       }
       eff_p0_uncertainty = _TrigEff_P0_Uncertainty[6];
       eff_p1_uncertainty = _TrigEff_P1_Uncertainty[6];
       eff_p2_uncertainty = _TrigEff_P2_Uncertainty[6];
       eff_p3_uncertainty = _TrigEff_P3_Uncertainty[6];
       eff_p4_uncertainty = _TrigEff_P4_Uncertainty[6];
     }
     else {
       std::cerr << " no Trigger option 2" << std::endl;
       abort();
       
     }
     
   }
   else if (_TrigEff_Smear_Option == 4) { 
  
      if (_E1_SHT25 && _E1_SHT27 && (_run3bool || (_run3bool && _run4bool && (runNum < _middlerunnumber))) ){
       if(lumi >= 0 && lumi < 2){
	 eff_p0 = _TrigEff_P0_lumi02_run3[5];
	 eff_p1 = _TrigEff_P1_lumi02_run3[5];
	 eff_p2 = _TrigEff_P2_lumi02_run3[5];
	 eff_p3 = _TrigEff_P3_lumi02_run3[5];
	 eff_p4 = _TrigEff_P4_lumi02_run3[5];
       }else if(lumi >= 2 && lumi < 4){
	 eff_p0 = _TrigEff_P0_lumi24_run3[5];
	 eff_p1 = _TrigEff_P1_lumi24_run3[5];
	 eff_p2 = _TrigEff_P2_lumi24_run3[5];
	 eff_p3 = _TrigEff_P3_lumi24_run3[5];
	 eff_p4 = _TrigEff_P4_lumi24_run3[5];
       }else if(lumi >= 4 && lumi < 6){
	 eff_p0 = _TrigEff_P0_lumi46_run3[5];
	 eff_p1 = _TrigEff_P1_lumi46_run3[5];
	 eff_p2 = _TrigEff_P2_lumi46_run3[5];
	 eff_p3 = _TrigEff_P3_lumi46_run3[5];
	 eff_p4 = _TrigEff_P4_lumi46_run3[5];
       }else{//6+
	 eff_p0 = _TrigEff_P0_lumi6999_run3[5];
	 eff_p1 = _TrigEff_P1_lumi6999_run3[5];
	 eff_p2 = _TrigEff_P2_lumi6999_run3[5];
	 eff_p3 = _TrigEff_P3_lumi6999_run3[5];
	 eff_p4 = _TrigEff_P4_lumi6999_run3[5];
       }
     }
      else if (_E1_SHT25 && _E1_SHT27  && (_run4bool || (_run3bool && _run4bool && (runNum > _middlerunnumber)))){
       if(lumi >= 0 && lumi < 2){
	 eff_p0 = _TrigEff_P0_lumi02_run4[5];
	 eff_p1 = _TrigEff_P1_lumi02_run4[5];
	 eff_p2 = _TrigEff_P2_lumi02_run4[5];
	 eff_p3 = _TrigEff_P3_lumi02_run4[5];
	 eff_p4 = _TrigEff_P4_lumi02_run4[5];
       }else if(lumi >= 2 && lumi < 4){
	 eff_p0 = _TrigEff_P0_lumi24_run4[5];
	 eff_p1 = _TrigEff_P1_lumi24_run4[5];
	 eff_p2 = _TrigEff_P2_lumi24_run4[5];
	 eff_p3 = _TrigEff_P3_lumi24_run4[5];
	 eff_p4 = _TrigEff_P4_lumi24_run4[5];
       }else if(lumi >= 4 && lumi < 6){
	 eff_p0 = _TrigEff_P0_lumi46_run4[5];
	 eff_p1 = _TrigEff_P1_lumi46_run4[5];
	 eff_p2 = _TrigEff_P2_lumi46_run4[5];
	 eff_p3 = _TrigEff_P3_lumi46_run4[5];
	 eff_p4 = _TrigEff_P4_lumi46_run4[5];
       }else{//6+
	 eff_p0 = _TrigEff_P0_lumi6999_run4[5];
	 eff_p1 = _TrigEff_P1_lumi6999_run4[5];
	 eff_p2 = _TrigEff_P2_lumi6999_run4[5];
	 eff_p3 = _TrigEff_P3_lumi6999_run4[5];
	 eff_p4 = _TrigEff_P4_lumi6999_run4[5];
       }
       eff_p0_uncertainty = _TrigEff_P0_Uncertainty[5];
       eff_p1_uncertainty = _TrigEff_P1_Uncertainty[5];
       eff_p2_uncertainty = _TrigEff_P2_Uncertainty[5];
       eff_p3_uncertainty = _TrigEff_P3_Uncertainty[5];
       eff_p4_uncertainty = _TrigEff_P4_Uncertainty[5];
     }
      else if (_E1_SHT27 && !_E1_SHT25  && (_run3bool || (_run3bool && _run4bool && (runNum < _middlerunnumber))) ){
       if(lumi >= 0 && lumi < 2){
	 eff_p0 = _TrigEff_P0_lumi02_run3[6];
	 eff_p1 = _TrigEff_P1_lumi02_run3[6];
	 eff_p2 = _TrigEff_P2_lumi02_run3[6];
	 eff_p3 = _TrigEff_P3_lumi02_run3[6];
	 eff_p4 = _TrigEff_P4_lumi02_run3[6];
       }else if(lumi >= 2 && lumi < 4){
	 eff_p0 = _TrigEff_P0_lumi24_run3[6];
	 eff_p1 = _TrigEff_P1_lumi24_run3[6];
	 eff_p2 = _TrigEff_P2_lumi24_run3[6];
	 eff_p3 = _TrigEff_P3_lumi24_run3[6];
	 eff_p4 = _TrigEff_P4_lumi24_run3[6];
       }else if(lumi >= 4 && lumi < 6){
	 eff_p0 = _TrigEff_P0_lumi46_run3[6];
	 eff_p1 = _TrigEff_P1_lumi46_run3[6];
	 eff_p2 = _TrigEff_P2_lumi46_run3[6];
	 eff_p3 = _TrigEff_P3_lumi46_run3[6];
	 eff_p4 = _TrigEff_P4_lumi46_run3[6];
       }else{//6+
	 eff_p0 = _TrigEff_P0_lumi6999_run3[6];
	 eff_p1 = _TrigEff_P1_lumi6999_run3[6];
	 eff_p2 = _TrigEff_P2_lumi6999_run3[6];
	 eff_p3 = _TrigEff_P3_lumi6999_run3[6];
	 eff_p4 = _TrigEff_P4_lumi6999_run3[6];
       }
     }
      else if (_E1_SHT27 && !_E1_SHT25  && (_run4bool || (_run3bool && _run4bool && (runNum > _middlerunnumber))) ){
       if(lumi >= 0 && lumi < 2){
	 eff_p0 = _TrigEff_P0_lumi02_run4[6];
	 eff_p1 = _TrigEff_P1_lumi02_run4[6];
	 eff_p2 = _TrigEff_P2_lumi02_run4[6];
	 eff_p3 = _TrigEff_P3_lumi02_run4[6];
	 eff_p4 = _TrigEff_P4_lumi02_run4[6];
       }else if(lumi >= 2 && lumi < 4){
	 eff_p0 = _TrigEff_P0_lumi24_run4[6];
	 eff_p1 = _TrigEff_P1_lumi24_run4[6];
	 eff_p2 = _TrigEff_P2_lumi24_run4[6];
	 eff_p3 = _TrigEff_P3_lumi24_run4[6];
	 eff_p4 = _TrigEff_P4_lumi24_run4[6];
       }else if(lumi >= 4 && lumi < 6){
	 eff_p0 = _TrigEff_P0_lumi46_run4[6];
	 eff_p1 = _TrigEff_P1_lumi46_run4[6];
	 eff_p2 = _TrigEff_P2_lumi46_run4[6];
	 eff_p3 = _TrigEff_P3_lumi46_run4[6];
	 eff_p4 = _TrigEff_P4_lumi46_run4[6];
       }else{//6+
	 eff_p0 = _TrigEff_P0_lumi6999_run4[6];
	 eff_p1 = _TrigEff_P1_lumi6999_run4[6];
	 eff_p2 = _TrigEff_P2_lumi6999_run4[6];
	 eff_p3 = _TrigEff_P3_lumi6999_run4[6];
	 eff_p4 = _TrigEff_P4_lumi6999_run4[6];
       }
       eff_p0_uncertainty = _TrigEff_P0_Uncertainty[6];
       eff_p1_uncertainty = _TrigEff_P1_Uncertainty[6];
       eff_p2_uncertainty = _TrigEff_P2_Uncertainty[6];
       eff_p3_uncertainty = _TrigEff_P3_Uncertainty[6];
       eff_p4_uncertainty = _TrigEff_P4_Uncertainty[6];
      }
      else {
	std::cerr << " no Trigger option 4" << std::endl;
	abort();
	
      }
   }else if (_TrigEff_Smear_Option == 5) { 
     
     if (_E1_SHT25 && _E1_SHT27 && (_run3bool || (_run3bool && _run4bool && (runNum < _middlerunnumber))) ){
       if(lumi >= 0 && lumi < 3){
	 eff_p0 = _TrigEff_P0_lumi03_run3[5];
	 eff_p1 = _TrigEff_P1_lumi03_run3[5];
	 eff_p2 = _TrigEff_P2_lumi03_run3[5];
	 eff_p3 = _TrigEff_P3_lumi03_run3[5];
	 eff_p4 = _TrigEff_P4_lumi03_run3[5];
	 eff_p5 = _TrigEff_P5_lumi03_run3[5];
       }else{
	 eff_p0 = _TrigEff_P0_lumi3999_run3[5];
	 eff_p1 = _TrigEff_P1_lumi3999_run3[5];
	 eff_p2 = _TrigEff_P2_lumi3999_run3[5];
	 eff_p3 = _TrigEff_P3_lumi3999_run3[5];
	 eff_p4 = _TrigEff_P4_lumi3999_run3[5];
	 eff_p5 = _TrigEff_P5_lumi3999_run3[5];
      }
     }
      else if (_E1_SHT25 && _E1_SHT27  && (_run4bool || (_run3bool && _run4bool && (runNum > _middlerunnumber)))){
       if(lumi >= 0 && lumi < 3){
	 eff_p0 = _TrigEff_P0_lumi03_run4[5];
	 eff_p1 = _TrigEff_P1_lumi03_run4[5];
	 eff_p2 = _TrigEff_P2_lumi03_run4[5];
	 eff_p3 = _TrigEff_P3_lumi03_run4[5];
	 eff_p4 = _TrigEff_P4_lumi03_run4[5];
	 eff_p5 = _TrigEff_P5_lumi03_run4[5];
       }else {
	 eff_p0 = _TrigEff_P0_lumi3999_run4[5];
	 eff_p1 = _TrigEff_P1_lumi3999_run4[5];
	 eff_p2 = _TrigEff_P2_lumi3999_run4[5];
	 eff_p3 = _TrigEff_P3_lumi3999_run4[5];
	 eff_p4 = _TrigEff_P4_lumi3999_run4[5];
	 eff_p5 = _TrigEff_P5_lumi3999_run4[5];
       }
       eff_p0_uncertainty = _TrigEff_P0_Uncertainty[5];
       eff_p1_uncertainty = _TrigEff_P1_Uncertainty[5];
       eff_p2_uncertainty = _TrigEff_P2_Uncertainty[5];
       eff_p3_uncertainty = _TrigEff_P3_Uncertainty[5];
       eff_p4_uncertainty = _TrigEff_P4_Uncertainty[5];
     }
      else if (_E1_SHT27 && !_E1_SHT25  && (_run3bool || (_run3bool && _run4bool && (runNum < _middlerunnumber))) ){
       if(lumi >= 0 && lumi < 3){
	 eff_p0 = _TrigEff_P0_lumi03_run3[6];
	 eff_p1 = _TrigEff_P1_lumi03_run3[6];
	 eff_p2 = _TrigEff_P2_lumi03_run3[6];
	 eff_p3 = _TrigEff_P3_lumi03_run3[6];
	 eff_p4 = _TrigEff_P4_lumi03_run3[6];
	 eff_p5 = _TrigEff_P5_lumi03_run3[6];
       }else{
	 eff_p0 = _TrigEff_P0_lumi3999_run3[6];
	 eff_p1 = _TrigEff_P1_lumi3999_run3[6];
	 eff_p2 = _TrigEff_P2_lumi3999_run3[6];
	 eff_p3 = _TrigEff_P3_lumi3999_run3[6];
	 eff_p4 = _TrigEff_P4_lumi3999_run3[6];
	 eff_p5 = _TrigEff_P5_lumi3999_run3[6];
       }
     }
      else if (_E1_SHT27 && !_E1_SHT25  && (_run4bool || (_run3bool && _run4bool && (runNum > _middlerunnumber))) ){
       if(lumi >= 0 && lumi < 3){
	 eff_p0 = _TrigEff_P0_lumi03_run4[6];
	 eff_p1 = _TrigEff_P1_lumi03_run4[6];
	 eff_p2 = _TrigEff_P2_lumi03_run4[6];
	 eff_p3 = _TrigEff_P3_lumi03_run4[6];
	 eff_p4 = _TrigEff_P4_lumi03_run4[6];
	 eff_p5 = _TrigEff_P5_lumi03_run4[6];
       }else{
	 eff_p0 = _TrigEff_P0_lumi3999_run4[6];
	 eff_p1 = _TrigEff_P1_lumi3999_run4[6];
	 eff_p2 = _TrigEff_P2_lumi3999_run4[6];
	 eff_p3 = _TrigEff_P3_lumi3999_run4[6];
	 eff_p4 = _TrigEff_P4_lumi3999_run4[6];
	 eff_p5 = _TrigEff_P5_lumi3999_run4[6];
       }
       eff_p0_uncertainty = _TrigEff_P0_Uncertainty[6];
       eff_p1_uncertainty = _TrigEff_P1_Uncertainty[6];
       eff_p2_uncertainty = _TrigEff_P2_Uncertainty[6];
       eff_p3_uncertainty = _TrigEff_P3_Uncertainty[6];
       eff_p4_uncertainty = _TrigEff_P4_Uncertainty[6];
      }
      else {
	std::cerr << " no Trigger option 5" << std::endl;
	abort();
	
      }
   } else if (_TrigEff_Smear_Option == 6) { 
    eff_p0 = 0.;
    eff_p1 = 0.;
    eff_p2 = 0.;
    eff_p3 = 0.;
    eff_p4 = 0.;
    eff_p5 = 0.;
  }
  
    else {

      if (_E1_SHT25 && !_E1_SHT27){
	eff_p0 = _TrigEff_P0[4];
	eff_p1 = _TrigEff_P1[4];
	eff_p2 = _TrigEff_P2[4];
	eff_p3 = _TrigEff_P3[4];
	eff_p4 = _TrigEff_P4[4];
	eff_p0_uncertainty = _TrigEff_P0_Uncertainty[4];
	eff_p1_uncertainty = _TrigEff_P1_Uncertainty[4];
	eff_p2_uncertainty = _TrigEff_P2_Uncertainty[4];
	eff_p3_uncertainty = _TrigEff_P3_Uncertainty[4];
	eff_p4_uncertainty = _TrigEff_P4_Uncertainty[4];
      }
      else if (_E1_SHT25 && _E1_SHT27){
	eff_p0 = _TrigEff_P0[5];
	eff_p1 = _TrigEff_P1[5];
	eff_p2 = _TrigEff_P2[5];
	eff_p3 = _TrigEff_P3[5];
	eff_p4 = _TrigEff_P4[5];
	eff_p0_uncertainty = _TrigEff_P0_Uncertainty[5];
	eff_p1_uncertainty = _TrigEff_P1_Uncertainty[5];
	eff_p2_uncertainty = _TrigEff_P2_Uncertainty[5];
	eff_p3_uncertainty = _TrigEff_P3_Uncertainty[5];
	eff_p4_uncertainty = _TrigEff_P4_Uncertainty[5];
      }
      else if (_E1_SHT27 && !_E1_SHT25){
      	eff_p0 = _TrigEff_P0[6];
	eff_p1 = _TrigEff_P1[6];
	eff_p2 = _TrigEff_P2[6];
	eff_p3 = _TrigEff_P3[6];
	eff_p4 = _TrigEff_P4[6];
	eff_p0_uncertainty = _TrigEff_P0_Uncertainty[6];
	eff_p1_uncertainty = _TrigEff_P1_Uncertainty[6];
	eff_p2_uncertainty = _TrigEff_P2_Uncertainty[6];
	eff_p3_uncertainty = _TrigEff_P3_Uncertainty[6];
	eff_p4_uncertainty = _TrigEff_P4_Uncertainty[6];
      }
      else {
	std::cerr << " no Trigger option " << std::endl;
	abort();
	
      }
    }

   //cout<<"trig "<<_E1_SHT25<<"  "<<_E1_SHT27<<endl;
   //cout<<"lumi "<<lumi<<"  "<<eff_p0<<"  "<<eff_p1<<"  "<<eff_p2<<"  "<<eff_p3<<"  "<<eff_p4<<endl;
   
    // if we want to study trigger efficiency uncertainty, just randomly change trigger efficiency
    // parameters according to the uncertainty
    if(_Study_TrigEff_Systematics) {
      eff_p0 += dummy->Gaus(0., 1.) * eff_p0_uncertainty;
      eff_p1 += dummy->Gaus(0., 1.) * eff_p1_uncertainty;
      eff_p2 += dummy->Gaus(0., 1.) * eff_p2_uncertainty;
      eff_p3 += dummy->Gaus(0., 1.) * eff_p3_uncertainty;
      eff_p4 += dummy->Gaus(0., 1.) * eff_p4_uncertainty;
    }

    if (_TrigEff_Smear_Option == 5) { 
      val = 0.5 * eff_p2 * (1. + TMath::Erf((pT-eff_p0)/(sqrt(2)*eff_p1)))*(1. + TMath::Erf((pT-eff_p4)/(sqrt(2)*eff_p3))) + pT*eff_p5;
    } else if (_TrigEff_Smear_Option == 6) { 

      if (pT > 40) val = 1.0;
      else {
	if (_E1_SHT25 && _E1_SHT27 && (_run3bool || (_run3bool && _run4bool && (runNum < _middlerunnumber))) && lumi < 3)
	  val = s2ElecPt_triggerEff_0_0_run2b3->Eval(pT);
	else if (_E1_SHT25 && _E1_SHT27 && (_run3bool || (_run3bool && _run4bool && (runNum < _middlerunnumber))) && lumi > 3)
	  val = s2ElecPt_triggerEff_0_1_run2b3->Eval(pT);
	else if (!_E1_SHT25 && _E1_SHT27 && (_run3bool || (_run3bool && _run4bool && (runNum < _middlerunnumber))))
	  val = s2ElecPt_triggerEff_1_0_run2b3->Eval(pT);
	else if (_E1_SHT25 && _E1_SHT27 && (_run4bool || (_run3bool && _run4bool && (runNum > _middlerunnumber))) && lumi < 3)
	  val = s2ElecPt_triggerEff_0_0_run2b4->Eval(pT);
	else if (_E1_SHT25 && _E1_SHT27 && (_run4bool || (_run3bool && _run4bool && (runNum > _middlerunnumber))) && lumi > 3)
	  val = s2ElecPt_triggerEff_0_1_run2b4->Eval(pT);
	else if (!_E1_SHT25 && _E1_SHT27 && (_run4bool || (_run3bool && _run4bool && (runNum > _middlerunnumber))))
	  val = s2ElecPt_triggerEff_1_0_run2b4->Eval(pT);
      }

    }else{
      // calculate efficiency for most trig options
      val = 0.5 * eff_p2 * (1. + TMath::Erf((pT-eff_p0)/(sqrt(2)*eff_p1)))*(1. + TMath::Erf((pT-eff_p4)/(sqrt(2)*eff_p3)));
    }
    //    std::cout << val << std::endl;
  }

  if (_makeCheckSmearingPlots) {
    _histos->Fill1D("h_TriggerEff_Pt_Denominator",pT);
    _histos->Fill1D("h_TriggerEff_DetEta_Denominator",part.deteta());
    _histos->Fill2D("h_TriggerEff_PtVDetEta_Denominator",part.deteta(),part.ppt());
  }

  // check trigger efficiency
  double r;
  if (externalRndm) r=(*externalRndm);
  else r=dummy->Uniform(0., 1.);
  if (r<= val) {
    if (_makeCheckSmearingPlots) {
      _histos->Fill1D("h_TriggerEff_Pt_Numerator",pT);
      _histos->Fill1D("h_TriggerEff_DetEta_Numerator",part.deteta());
      _histos->Fill2D("h_TriggerEff_PtVDetEta_Numerator",part.deteta(),part.ppt());
    }
    return true;
  } else {
    return false;
  }
}//passesTriggerEff()


//Preselection efficiency (vs deteta)
bool EfficiencySmear::passesPreselEff(PMCSEMObj part, TRandom3 *dummy, double* externalRndm, PMCSVtx *vtx, double* externalRndmtrk, bool neverUseTrack) {
  
  double deteta=part.deteta();   

  double val=1., err=0.;
  Bool_t status = PHistoTools::getBinValues(_hPreselEff, deteta, val, err);  

  if (_makeCheckSmearingPlots) {
    _histos->Fill1D("h_PreselEff_DetEta_Denominator",part.deteta());
  }

  // check preselection efficiency
  double r;
  if (externalRndm) r=(*externalRndm);
  else r=dummy->Uniform(0., 1.);
  if (r <= val) {
    if (_makeCheckSmearingPlots) {
      _histos->Fill1D("h_PreselEff_DetEta_Numerator",part.deteta());
    }
    
    bool passesloosetrack = true;
    if (_applypreseltrkmatch && ! neverUseTrack){
      passesloosetrack  =  passesLooseTrkEff(part, vtx, dummy, externalRndmtrk);
    }
    return passesloosetrack;
  } else {
    return false;
  }
}//passesPreselEff()


//track matching efficiency (vs eta, primary vertex for CC region, also pT dependence applied if _simulate_pT_dependence=true,
// vs deteta for EC region always)
bool EfficiencySmear::passesLooseTrkEff(PMCSEMObj part, PMCSVtx* vtx, TRandom3 *dummy, double* externalRndm) {

  if(_ApplyLooseTrackMatchEfficiency==false) return true;
  double lumi = part.getLumi();
  double val=1., err=0.;
  if (TMath::Abs(part.ppid()) == 22.){
    return false;
  }
  
  Bool_t status = false;
  if(fabs(part.deteta())<1.1){
    
    if(_run3bool && _run4bool){
      if(_runNumber < _middlerunnumber){//This is set in parameters file.  run2b3 is below ~263000.
	status = PHistoTools::getBinValues(_hlooseTrkEffRun3, vtx->vtxz(), part.eta(), lumi, val, err, true);
      }else{
	status = PHistoTools::getBinValues(_hlooseTrkEffRun4, vtx->vtxz(), part.eta(), lumi, val, err, true);
      }
      // cout<<"loose "<<_runNumber<<"  "<<val<<endl;
    }else if(_run3bool && !_run4bool){
      status = PHistoTools::getBinValues(_hlooseTrkEffRun3, vtx->vtxz(), part.eta(), lumi, val, err, true);
    }else if(!_run3bool && _run4bool){
      status = PHistoTools::getBinValues(_hlooseTrkEffRun4, vtx->vtxz(), part.eta(), lumi, val, err, true);
    }else {
      cout<<"EfficiencySmear: At least one of Run3 and Run4 in parameters file must be set to true"<<endl; 
      exit(0);
    }

    //Note: we reassign val here using interpolation method.
    if(_run3bool) val = PHistoTools::Interpolate(_hlooseTrkEffRun3, vtx->vtxz(), part.eta(), lumi);
    else val = PHistoTools::Interpolate(_hlooseTrkEffRun4, vtx->vtxz(), part.eta(), lumi);
    if(_run3bool && _run4bool) cout<<"Warning in EfficiencySmear::No interpolation for run combination as coded."<<endl;

  }else {//outside central deteta range
    if (_simulateTrkVtxDepEC) {
      status = PHistoTools::getBinValues(_hlooseTrkEff_EC, vtx->vtxz(), part.eta(), val, err, true);
    } else {
      status = PHistoTools::getBinValues(_hlooseTrkEff_deteta, part.deteta(), val, err);
    }
  }
  if (_makeCheckSmearingPlots) {
    _histos->Fill1D("h_looseTrkEff_DetEta_Denominator", part.deteta());
    _histos->Fill1D("h_looseTrkEff_ZVertex_Denominator", vtx->vtxz());
    _histos->Fill2D("h_looseTrkEff_DetEtaVZVertex_Denominator",part.deteta(), vtx->vtxz());
  }

  // check track matching efficiency
  double r;
  if (externalRndm)   r=externalRndm[0];
  else r=dummy->Uniform(0., 1.);
  if (r <= val) {     // passing track matching efficiency
    if (_makeCheckSmearingPlots) {
      _histos->Fill1D("h_looseTrkEff_DetEta_Numerator", part.deteta());
      _histos->Fill1D("h_looseTrkEff_ZVertex_Numerator", vtx->vtxz());
      _histos->Fill2D("h_looseTrkEff_DetEtaVZVertex_Numerator", part.deteta(), vtx->vtxz());
    }
    
    return true;    
  } else {            // not passing track matching efficiency
    return false;
  }
}//passesLooseTrkEff()



//EMID efficiency (vs deteta for CC and EC if _simulate_pT_dependence = false
// vs eta and pT for CC if _simulate_pT_dependence = true)
bool EfficiencySmear::passesEMIDEff(PMCSEMObj part, TRandom3 *dummy, double* externalRndm) {
  double val=1., err=0.;
  Bool_t status = PHistoTools::getBinValues(_hEMIDEff, part.deteta(), val, err); 
  if (_makeCheckSmearingPlots) _histos->Fill1D("h_EMIDEff_DetEta_Denominator",part.deteta());
 
  if(_simulate_pT_dependence && fabs(part.deteta())<1.1) {   // for CC and _simulate_pT_dependence = true
    // overwrite val to use new efficiency for CC region
    int eta_region = wz_utils::PhyEtaRegion_CC(part.eta());    
    val = _CCideff_pTphyEta_ParameterA[eta_region] + _CCideff_pTphyEta_ParameterB[eta_region] * TMath::Log(part.ppt());
  }

  // apply efficiency ratio
  // measured by applying tag-probe method on full MC/data and fast MC and measure the residual ratio of pT dependence
  double val_ratio=1.;
  int index_bin;
  double p0, p1, p2, p3, p4;
  if(fabs(part.deteta())<1.1 && _apply_HMxeff_ratio) {
    if(part.eta()<-1.3)
      index_bin=0;
    else if(part.eta()>1.3)
      index_bin=14;
    else
      index_bin=int((part.eta()+1.3)/0.2)+1;

    p0=_CChmxeffratio_pTphyEta_ParameterA[index_bin];
    p1=_CChmxeffratio_pTphyEta_ParameterB[index_bin];
    p2=_CChmxeffratio_pTphyEta_ParameterC[index_bin];
    p3=_CChmxeffratio_pTphyEta_ParameterD[index_bin];
    p4=_CChmxeffratio_pTphyEta_ParameterE[index_bin];

    if (_eff_ratios_function==0) {
      if(part.ppt()<50.){
	val_ratio=p0 + p1*part.ppt() + p2*(2*part.ppt()*part.ppt()-1) + p3*(4*part.ppt()*part.ppt()*part.ppt()-3*part.ppt()) +
	  p4*(8*part.ppt()*part.ppt()*part.ppt()*part.ppt()-8*part.ppt()*part.ppt()+1);
      }
      else{
	val_ratio=p0 + p1*50. + p2*(2*50.*50.-1) + p3*(4*50.*50.*50.-3*50.) +
	  p4*(8*50.*50.*50.*50.-8*50.*50.+1);
      }
    } else if (_eff_ratios_function==1) {
      if(part.ppt()<60.){
        val_ratio=p0 + p1*log(part.ppt());
      }
      else{
	val_ratio=p0 + p1*log(60.);
      }
    } else {
      assert(0);
    }

    val=val*val_ratio;
  }

  // apply EMID efficiency
  double r;
  if (externalRndm) r=(*externalRndm);
  else r=dummy->Uniform(0., 1.);
  if (r <= val) {
    if (_makeCheckSmearingPlots) _histos->Fill1D("h_EMIDEff_DetEta_Numerator",part.deteta());
    
    return true;
  } else return false;
}//passesEMIDEff()

//track matching efficiency (vs eta, primary vertex for CC region, also pT dependence applied if _simulate_pT_dependence=true,
// vs deteta for EC region always)
bool EfficiencySmear::passesTrkEff(PMCSEMObj part, PMCSVtx vtx, TRandom3 *dummy, double* externalRndm) {

  if(_ApplyTrackMatchEfficiency==false) return true;
  double val=1., err=0.;
  if (TMath::Abs(part.ppid()) == 22.){
    return false;
  }


  Bool_t status = false;
  if(fabs(part.deteta())<1.1){

    if(_run3bool && _run4bool){
      if(_runNumber < _middlerunnumber){//This is set in parameters file.  run2b3 is below ~263000.
	status = PHistoTools::getBinValues(_hTrkEffRun3, vtx.vtxz(), part.eta(), val, err, true);
	//  std::cout << vtx.vtxz() << "   " << part.eta() <<  val << std::endl;
	//std::cout <<  _hTrkEffRun3->GetBinContent(_hTrkEffRun3->FindBin( vtx.vtxz(),  part.eta())) << std::endl;
      }else{
	status = PHistoTools::getBinValues(_hTrkEffRun4, vtx.vtxz(), part.eta(), val, err, true);
	//  std::cout << vtx.vtxz() << "   " << part.eta() <<  val << std::endl;
	//std::cout <<  _hTrkEffRun4->GetBinContent(_hTrkEffRun4->FindBin( vtx.vtxz(),  part.eta())) << std::endl;
      }
      // cout<<"tight "<<_runNumber<<"  "<<val<<endl;
    }else if(_run3bool && !_run4bool){
      status = PHistoTools::getBinValues(_hTrkEffRun3, vtx.vtxz(), part.eta(), val, err, true);
    }else if(!_run3bool && _run4bool){
      status = PHistoTools::getBinValues(_hTrkEffRun4, vtx.vtxz(), part.eta(), val, err, true);
    }else {
      cout<<"EfficiencySmear: At least one of Run3 and Run4 in parameters file must be set to true"<<endl; 
      exit(0);
    }
   
  }else {//outside deteta central region
    if (_simulateTrkVtxDepEC) {
      status = PHistoTools::getBinValues(_hTrkEff_EC, vtx.vtxz(), part.eta(), val, err, true);
    } else {
      status = PHistoTools::getBinValues(_hTrkEff_deteta, part.deteta(), val, err);
    }
  }

  if (_makeCheckSmearingPlots) {
    _histos->Fill1D("h_TrkEff_DetEta_Denominator", part.deteta());
    _histos->Fill1D("h_TrkEff_ZVertex_Denominator", vtx.vtxz());
    _histos->Fill2D("h_TrkEff_DetEtaVZVertex_Denominator",part.deteta(), vtx.vtxz());
  }

  // apply efficiency ratio
  // measured by applying tag-probe method on full MC/data and fast MC and measure the residual ratio of pT dependence
  double val_ratio=1.;
  int index_bin;
  double p0, p1, p2, p3, p4;
  if(fabs(part.deteta())<1.1 && _apply_TRKeff_ratio) {
    if(part.eta()<-1.3)
      index_bin=0;
    else if(part.eta()>1.3)
      index_bin=14;
    else
      index_bin=int((part.eta()+1.3)/0.2)+1;

    p0=_CCtrkeffratio_pTphyEta_ParameterA[index_bin];
    p1=_CCtrkeffratio_pTphyEta_ParameterB[index_bin];
    p2=_CCtrkeffratio_pTphyEta_ParameterC[index_bin];
    p3=_CCtrkeffratio_pTphyEta_ParameterD[index_bin];
    p4=_CCtrkeffratio_pTphyEta_ParameterE[index_bin];

    if (_eff_ratios_function==0) {
      if(part.ppt()<50.){
	val_ratio=p0 + p1*part.ppt() + p2*(2*part.ppt()*part.ppt()-1) + p3*(4*part.ppt()*part.ppt()*part.ppt()-3*part.ppt()) +
	  p4*(8*part.ppt()*part.ppt()*part.ppt()*part.ppt()-8*part.ppt()*part.ppt()+1);
      }
      else{
	val_ratio=p0 + p1*50. + p2*(2*50.*50.-1) + p3*(4*50.*50.*50.-3*50.) +
	  p4*(8*50.*50.*50.*50.-8*50.*50.+1);
      }
    } else if (_eff_ratios_function==1) {
      if(part.ppt()<60.){
	val_ratio=p0 + p1*log(part.ppt());
      }
      else{
	val_ratio=p0 + p1*log(60.);
      }
    } else {
      assert(0);
    }

    val=val*val_ratio;
  }

  // Eta hack for sensitivity studies
  if (_DoEtaHack && fabs(part.deteta())<1.3) {
    int bin = _hEtaHack->GetXaxis()->FindBin(part.eta());
    val=val*_hEtaHack->GetBinContent(bin);
  }

  // check track matching efficiency
  double r;
  if (externalRndm) r=externalRndm[0];
  else r=dummy->Uniform(0., 1.);
  if (r <= val) {     // passing track matching efficiency
    if (_makeCheckSmearingPlots) {
      _histos->Fill1D("h_TrkEff_DetEta_Numerator", part.deteta());
      _histos->Fill1D("h_TrkEff_ZVertex_Numerator", vtx.vtxz());
      _histos->Fill2D("h_TrkEff_DetEtaVZVertex_Numerator", part.deteta(), vtx.vtxz());
    }

    // pT dependent for CC region only
    double pT_dependence = 1.;
    if(_simulate_pT_dependence && fabs(part.deteta())<1.1) {   // for CC region and _simulate_pT_dependence = true
      int eta_region = wz_utils::PhyEtaRegion_CC(part.eta());    
      // make sure we have 98% efficiency for pT=45 GeV for each eta region
      // this is just kind of normalization to avoid double counting inefficiencies
      double eff_45 = _CCtrkeff_pTphyEta_ParameterA[eta_region] + _CCtrkeff_pTphyEta_ParameterB[eta_region] * TMath::Log(45.);
      pT_dependence = (_CCtrkeff_pTphyEta_ParameterA[eta_region] + _CCtrkeff_pTphyEta_ParameterB[eta_region] * TMath::Log(part.ppt())) * 0.98/eff_45;
    } 
    
    // apply pT dependent efficiency
    if (externalRndm) r=externalRndm[1];
    else r=dummy->Uniform(0., 1.);
    if (r <= pT_dependence) return true;
    else return false;    
  } else {            // not passing track matching efficiency
    return false;
  }
}//passesTrkEff()

bool EfficiencySmear::passesClusPtEff(PMCSEMObj part, TRandom3 *dummy, double* externalRndm) {

  float val=1;

  if(_simulate_pT_dependence && fabs(part.deteta())<1.1) {
    int eta_region = wz_utils::PhyEtaRegion_CC(part.eta());
    val = _CCcluseff_pTphyEta_ParameterA[eta_region] + _CCcluseff_pTphyEta_ParameterB[eta_region] * TMath::Log(part.ppt());
  }

  // apply pT dependent efficiency
  float r;
  if (externalRndm) r=*externalRndm;
  else r=dummy->Uniform(0., 1.);
  if (r <= val) return true;
  else return false;

}


bool EfficiencySmear::passesElecPhiEff(PMCSEMObj part, TRandom3 *dummy, bool useDetPhi, double* externalRndm) {

    double val=10.0;//some large number, not expected to be exceeded by measured ratio
    if (fabs(part.deteta())>1.1) return true;// efficiency implemented for CC electrons only
    double phival = part.pphi();
    if (useDetPhi) phival = part.trkphiem3();
    double /* val (already declared ), */ err=0.;    
    Bool_t status = true;
    double UpperBound = -555.;

    if(_run3bool && _run4bool){
      if(_runNumber < _middlerunnumber){//This is set in parameters file.  run2b3 is below ~263000.
	status = PHistoTools::getBinValues(_RatioDataToPMCS, phival, val, err);
	UpperBound = _RatioDataToPMCS->GetMaximum();
      }else{
	status = PHistoTools::getBinValues(_RatioDataToPMCSRun4, phival, val, err);
	UpperBound = _RatioDataToPMCSRun4->GetMaximum();
      }
    }else if(_run3bool && !_run4bool){
      status = PHistoTools::getBinValues(_RatioDataToPMCS, phival, val, err);
      UpperBound = _RatioDataToPMCS->GetMaximum();
    }else if(!_run3bool && _run4bool){
      status = PHistoTools::getBinValues(_RatioDataToPMCSRun4, phival, val, err);
      UpperBound = _RatioDataToPMCSRun4->GetMaximum();
    }else {
      cout<<"EfficiencySmear: At least one of Run3 and Run4 in parameters file must be set to true"<<endl; 
      exit(0);
    }

    if(!status) cout<<"Warning: overflow in "<<_RatioDataToPMCS->GetName() << " Electron Phi="<<phival<<endl;
    double r;
    if (externalRndm) r=(*externalRndm)*UpperBound;
    else r=dummy->Uniform(0.0,UpperBound);
    if (r <= val) return true;
    else return false;

}



bool EfficiencySmear::passesAddOnEff(PMCSEMObj part, bool isW, TRandom3* dummy, int otherpass_flag, double* externalRndm){

  double eff(1.0);

  // Wenu
  if (isW){

    // safty check
    if (!_ApplyAddOnEff_Wen) return eff;

    // TEPT EFF
    if(_AddOnEff_Wen_TEPT_On) {
      // get references
      double TrueEEwFSR = part.GetEnergyGenWFSR();
      double eEta = part.eta();
      double TrueEPTwFSR = TrueEEwFSR/cosh(eEta);

      // get True EPT with FSR efficiency
      double eff_TEPT(0.0);
      int nParTEPT = _AddOnEff_Wen_TEPT_Pars.size();
      for (int i=0; i<nParTEPT; i++){
        eff_TEPT += _AddOnEff_Wen_TEPT_Pars.at(i)*pow(TrueEPTwFSR,i);
      }

      // all efficiency
      eff *= eff_TEPT;      
    } // if(_AddOnEff_Wen_TEPT_On)  ..

    // DetEta Eff
    if (_AddOnEff_Wen_DetEta_On ){
      double deteta = part.deteta();
      if (fabs(deteta)<1.05){
        double deteta_eff = _AddOnEff_Wen_DetEta_Pars->GetBinContent(_AddOnEff_Wen_DetEta_Pars->FindBin(deteta));
        eff *= deteta_eff;
      }
    }  // if (_AddOnEff_Wen_DetEta_On ) ..

    // SET eff
    if (_AddOnEff_Wen_SET_On){
      // reference
      double SET = part.getScalarEt();
      // vectors storing norm, mean and sigma of a series of gaussians
      std::vector<double> norm, mean, sigm;
      int ngaus = int(_AddOnEff_Wen_SET_Pars.size()/3);
      for (int igaus=0; igaus<ngaus; igaus++){
        norm.push_back(_AddOnEff_Wen_SET_Pars.at(igaus*3));
        mean.push_back(_AddOnEff_Wen_SET_Pars.at(igaus*3+1));
        sigm.push_back(_AddOnEff_Wen_SET_Pars.at(igaus*3+2));
      }

      // calculate the efficiency
      double efficiency = 0;
      for (int igaus=0; igaus<norm.size(); igaus++){
        efficiency += norm.at(igaus)*exp( -(SET-mean.at(igaus))*(SET-mean.at(igaus))/(sigm.at(igaus)*sigm.at(igaus)) );
      }

      //        
      eff *= efficiency;

    } //  if (_AddOnEff_Zee_SET_On) ...

  }

  // Zee
  else {

    // safty check
    if (!_ApplyAddOnEff_Zee) return eff;

    // TEPT Eff
    if(_AddOnEff_Zee_TEPT_On){
      // get references
      double TrueEEwFSR = part.GetEnergyGenWFSR();
      double eEta = part.eta();
      double TrueEPTwFSR = TrueEEwFSR/cosh(eEta);
  
      // get True EPT with FSR efficiency
      double eff_TEPT(0.0);
      int nParTEPT = _AddOnEff_Zee_TEPT_Pars.size();
      for (int i=0; i<nParTEPT; i++){
        eff_TEPT += _AddOnEff_Zee_TEPT_Pars.at(i)*pow(TrueEPTwFSR,i);
      }

      // all efficiency
      eff *= eff_TEPT;

    } // if(_AddOnEff_Zee_TEPT_On) ..

    // DetEta Eff
    if (_AddOnEff_Zee_DetEta_On){
      double deteta = part.deteta();
      if (fabs(deteta)<1.05){
        double deteta_eff = _AddOnEff_Zee_DetEta_Pars->GetBinContent(_AddOnEff_Zee_DetEta_Pars->FindBin(deteta));
        eff *= deteta_eff;
      }  
    } // if (_AddOnEff_Zee_DetEta_On) .. 

    // SET eff
    if (_AddOnEff_Zee_SET_On){
      // reference
      double SET = part.getScalarEt();
      // vectors storing norm, mean and sigma of a series of gaussians
      std::vector<double> norm, mean, sigm;
      int ngaus = int(_AddOnEff_Zee_SET_Pars.size()/3);
      for (int igaus=0; igaus<ngaus; igaus++){
        norm.push_back(_AddOnEff_Zee_SET_Pars.at(igaus*3));
        mean.push_back(_AddOnEff_Zee_SET_Pars.at(igaus*3+1));
        sigm.push_back(_AddOnEff_Zee_SET_Pars.at(igaus*3+2));
      }

      // calculate the efficiency
      double efficiency = 0;
      for (int igaus=0; igaus<norm.size(); igaus++){
        efficiency += norm.at(igaus)*exp( -(SET-mean.at(igaus))*(SET-mean.at(igaus))/(sigm.at(igaus)*sigm.at(igaus)) );
      }

      //        
      eff *= efficiency;

    } //  if (_AddOnEff_Zee_SET_On) ...

    // Correlation Eff using TEPT as reference
    if (_AddOnEff_Zee_CorrelTEPT_On) {
      //std::cout << "other pass: " << otherpass_flag << std::endl;
      // consider correlation: 
      //  different treatment in case the other pass or not (1) do not know (2) pass (3) not pass 
      assert(otherpass_flag==0||otherpass_flag==1||otherpass_flag==2);

      // vectors storing norm, mean and sigma of a series of gaussians
      std::vector<double> norm, mean, sigm;
      // case 1: do not know the other pass or not
      if (otherpass_flag==2){
        int ngaus = int(_AddOnEff_Zee_CorrelTEPT_DontKnowPars.size()/3);
        for (int igaus=0; igaus<ngaus; igaus++){
          norm.push_back(_AddOnEff_Zee_CorrelTEPT_DontKnowPars.at(igaus*3));
          mean.push_back(_AddOnEff_Zee_CorrelTEPT_DontKnowPars.at(igaus*3+1));
          sigm.push_back(_AddOnEff_Zee_CorrelTEPT_DontKnowPars.at(igaus*3+2));
        }
      }
      // case 2: the other passes
      else if (otherpass_flag==1) {
        int ngaus = int(_AddOnEff_Zee_CorrelTEPT_OnePassPars.size()/3);
        for (int igaus=0; igaus<ngaus; igaus++){
          norm.push_back(_AddOnEff_Zee_CorrelTEPT_OnePassPars.at(igaus*3));
          mean.push_back(_AddOnEff_Zee_CorrelTEPT_OnePassPars.at(igaus*3+1));
          sigm.push_back(_AddOnEff_Zee_CorrelTEPT_OnePassPars.at(igaus*3+2));
        }
      }
      // case 3: the other not passes
      else if (otherpass_flag==0) {
        int ngaus = int(_AddOnEff_Zee_CorrelTEPT_OneNotPassPars.size()/3);
        for (int igaus=0; igaus<ngaus; igaus++){
          norm.push_back(_AddOnEff_Zee_CorrelTEPT_OneNotPassPars.at(igaus*3));
          mean.push_back(_AddOnEff_Zee_CorrelTEPT_OneNotPassPars.at(igaus*3+1));
          sigm.push_back(_AddOnEff_Zee_CorrelTEPT_OneNotPassPars.at(igaus*3+2));
        }
      }
     
      // get references
      double TrueEEwFSR = part.GetEnergyGenWFSR();
      double eEta = part.eta();
      double TrueEPTwFSR = TrueEEwFSR/cosh(eEta); 

      // calculate the efficiency
      double efficiency = 0;
      for (int igaus=0; igaus<norm.size(); igaus++){
        efficiency += norm.at(igaus)*exp( -(TrueEPTwFSR-mean.at(igaus))*(TrueEPTwFSR-mean.at(igaus))/(sigm.at(igaus)*sigm.at(igaus)) );
      }

      //        
      eff *= efficiency;

    } // if (_AddOnEff_Zee_CorrelTEPT_On) ..   

  }

  //debug
  //std::cout << " AddOn Eff = " << eff << std::endl;
  // protection
  if ( eff>1.0 ) eff = 1.0;
  if ( eff<0.0 ) eff = 0.0;

  double r;
  if (externalRndm) {
    r = (*externalRndm);
  }
  else {
    r = dummy->Uniform(0.0, 1.0);
  }

  bool pass(false);
  if (r <= eff ) {
    pass = true;
  }
  else {
    pass = false;
  }

  // debug
  //std::cout << "Hengne :: passesAddOnEff " << eff << " " << pass << std::endl;

  return pass;
}


