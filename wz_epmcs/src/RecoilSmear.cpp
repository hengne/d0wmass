#include "RecoilSmear.hpp"
#include "histograms.hpp"
#include "AnglesUtil.hpp"
#include "WZ_Utils.hpp"
#include "TH2rclsa.h"
#include "HardRecoil_Manager.hpp"
#include "ZBLibraryClass.h"
#include "MBLibraryClass.h"

#include <fstream>
#include <iostream>

#include "TFile.h"
#include "../geant_RunIIb/MySETFunction.C"
#include <assert.h>

using namespace std;
class ZBLibraryClass;
Double_t fitf(Double_t *x, Double_t *par) {
   Double_t arg1 = 0;
   if (par[1] != 0) arg1 = (x[0] - par[0])/par[1];
   Double_t arg2 = (x[0] - par[0])/3.5;

   Double_t fitval = TMath::Exp(-0.5*arg1*arg1) + 0.2*TMath::Exp(-0.5*arg2*arg2);;
   return fitval;
}

// Met MB
TVector2 RecoilSmear::GetMet_MB() const {
  if(_read_recoil_file) return 0;
  if(_MBEvtIndex<0) return 0;
  return TVector2(_MBmetx[_MBEvtIndex], _MBmety[_MBEvtIndex]);
}

// Met ZB
TVector2 RecoilSmear::GetMet_ZB() const {
  if(_read_recoil_file) return 0;
  if(_ZBEvtIndex<0) return 0;
  return TVector2(_ZBmetx[_ZBEvtIndex], _ZBmety[_ZBEvtIndex]);
}



// get scalar Et for MB overlay
double RecoilSmear::scalarEt_MB() const {
//   //////////////////////////////// DEBUG
//   //
//   cout << "scalarEt_MB: MB_index= " << _MBEvtIndex 
//        << ", alpha_mb=" << _alpha_mb 
//        << ", MBset[" << _MBEvtIndex << "]=" << (_MBEvtIndex<0 ? 0.0 : _MBset[_MBEvtIndex]) << endl;
//   //
//   //////////////////////////////// DEBUG
  if(_read_recoil_file) return 0.;
  if(_MBEvtIndex<0) return 0.;
  return _MBset[_MBEvtIndex];
}

// get scalar Et for ZB overlay
double RecoilSmear::scalarEt_ZB() const {
//   //////////////////////////////// DEBUG
//   //
//   cout << "scalarEt_ZB: ZB_index= " << _ZBEvtIndex 
//        << ", alpha_zb=" << _alpha_zb 
//        << ", ZBset[" << _ZBEvtIndex << "]=" << (_ZBEvtIndex<0 ? 0.0 : _ZBset[_ZBEvtIndex]) << endl;
//   //
//   //////////////////////////////// DEBUG
  if(_read_recoil_file) return 0.;
  if(_ZBEvtIndex<0) return 0.;
  return _alpha_zb*_ZBset[_ZBEvtIndex];
}

// get scalar Et from ZB without _alpha_zb scale 
double RecoilSmear::scalarEt_ZB_NoScale() const {
//   //////////////////////////////// DEBUG
//   //
//   cout << "scalarEt_ZB: ZB_index= " << _ZBEvtIndex
//        << ", alpha_zb=" << _alpha_zb
//        << ", ZBset[" << _ZBEvtIndex << "]=" << (_ZBEvtIndex<0 ? 0.0 : _ZBset[_ZBEvtIndex]) << endl;
//   //
//   //////////////////////////////// DEBUG
  if(_read_recoil_file) return 0.;
  if(_ZBEvtIndex<0) return 0.;
  return _ZBset[_ZBEvtIndex];
}

// get scalar Et for hard recoil jet
double RecoilSmear::scalarEt_hard() {

  if (_Momentum_SmearOption_HAD==3) {
    return hard_recoil->GetSET();
  }
  if((_read_recoil_file)||(_Momentum_SmearOption_HAD!=1)) {
    _Hard_SET_exists=true;
    return(_Hard_SET_smeared=0.0);
  }
  // NOTE: this part of the code should be reached only 
  // when _Momentum_SmearOption_HAD=1 and only
  // after RecoilSmear::SmearHardRecoil_Method_B has been called
  //
  // check if a cached hard SET value already exists
  if(_Hard_SET_exists) {
//     //////////////////////////////// DEBUG
//     //
//     cout << "scalarEt_hard: Buffered hard SET = " << _Hard_SET_from_Znunu
//  	 << " (unfudged)" << endl;
//     //
//     //////////////////////////////// DEBUG
  } else {
//     //////////////////////////////// DEBUG
//     //
//     cout << "scalarEt_hard: Buffered(1): generated_pT=" << _Hard_Recoil_generated_pT
// 	 << ", hard_znunu_pT=" << _Hard_Recoil_from_Znunu_pT
// 	 << ", hard_znunu_SET=" << _Hard_SET_from_Znunu 
// 	 << ", hard_znunu_SET_exp=" << _Hard_SET_expected_from_Znunu << endl; 
//     //
//     //////////////////////////////// DEBUG
    wz_utils::ScalarEt(_Hard_Recoil_generated_pT,
		       _Hard_Recoil_from_Znunu_pT,
		       _Hard_SET_from_Znunu,
		       _Hard_SET_expected_from_Znunu,
		       _SETmodelDatafile);
    
    _Hard_SET_exists=true;
//     //////////////////////////////// DEBUG
//     //
//     cout << "scalarEt_hard: Buffered(2): generated_pT=" << _Hard_Recoil_generated_pT
// 	 << ", hard_znunu_pT=" << _Hard_Recoil_from_Znunu_pT
// 	 << ", hard_znunu_SET=" << _Hard_SET_from_Znunu 
// 	 << ", hard_znunu_SET_exp=" << _Hard_SET_expected_from_Znunu << endl; 
    
//     cout << "scalarEt_hard: Fresh hard SET = " << _Hard_SET_from_Znunu
// 	 << " (unfudged)" << endl;
//     //
//     //////////////////////////////// DEBUG
  }
  // final contribution to SET due to the hard recoil jet
  _Hard_SET_smeared = _Hard_SET_from_Znunu; // no fudging
  if(_Hard_SET_smeared<0.0) _Hard_SET_smeared=0.0;

//   //////////////////////////////// DEBUG
//   //
//   cout << "scalarEt_hard: Hard SET = " << _Hard_SET_smeared 
//        << " (fudged)" << endl;
//   //
//   //////////////////////////////// DEBUG
  return _Hard_SET_smeared;
 
}    

// get total scalar Et
double RecoilSmear::scalarEt() {
//   //////////////////////////////// DEBUG
//   //
//   double scalarEt_All = _alpha_SETresponse*(scalarEt_MB()+scalarEt_ZB()+scalarEt_hard());
//   cout << "scalarEt: Total SET = " << scalarEt_All << endl;
//   return scalarEt_All;
//   //
//   //////////////////////////////// DEBUG
  double scalarEt_All = 0.;
  if(!_read_recoil_file)
  {
  if (_SETresponse_Model==0){
    scalarEt_All = _alpha_SETresponse*(scalarEt_MB()+scalarEt_ZB()+scalarEt_hard());
  }
  else if (_SETresponse_Model==2){
    scalarEt_All = _alpha_SETresponse*scalarEt_hard();
  }
  else {
    double setin[2];
    setin[0] = (scalarEt_MB()+scalarEt_ZB()+scalarEt_hard() -scalarEt_cone());
    if (setin[0] < 1000.){
      if (setin[0] < 0.)
      setin[0] = 0;	
      scalarEt_All =  _setfunction->Evaluate(setin);
    }
    else {
      std::cout << "Scalar Et is beyond Model limits forcing to value at 1000" << std::endl;
      setin[0] = 1000.;
      scalarEt_All =  _setfunction->Evaluate(setin);
    }
  }
  }
  else if(_read_recoil_file) {
    scalarEt_All = _scalarEt_chosen;
  }
  
  return scalarEt_All;
}

// constructor and read in smearing parameters
RecoilSmear::RecoilSmear(TString parameter_filename,hist_files &histos,TRandom3* dummy) {

  PParameterReader parm(parameter_filename.Data());

  cout<<"Start RecoilSmear initialization"<<endl;

  _histos = &histos;

  _run3bool = parm.GetBool("Run3");
  _run4bool = parm.GetBool("Run4");
  // _middlerunnumber = parm.GetInt("MiddleRunNumber"); //not needed here since ZB libraries already divided by run type

  _makeCheckSmearingPlots =  parm.GetBool("makeCheckSmearingPlots");

  if (_makeCheckSmearingPlots) {
    _histos->add(RECOILSMEAR_Hist,"","check_smearing");
    _histos->add(RECOILSMEAR_Hist_2D,"","check_smearing");
  }


  // parameters used for hadronic momentum smearing
  _Momentum_SmearOption_HAD = parm.GetInt("Momentum_SmearOption_HAD", 1);

  if (_Momentum_SmearOption_HAD==3)
    hard_recoil = new HardRecoil_Manager(parameter_filename.Data());

  // only used for Momentum_SmearOption_HAD==0
  _scale_HAD = parm.GetFloat("Scale_HAD", 0.67);
  _offset_HAD = parm.GetFloat("Offset_HAD", 0.);

  // only used for Momentum_SmearOption_HAD==1
  _scale_HAD_bifurcate_A = parm.GetFloat("Scale_HAD_bifurcate_A", 1.);
  _scale_HAD_bifurcate_B = parm.GetFloat("Scale_HAD_bifurcate_B", 0.);
  _scale_HAD_bifurcate_Tau = parm.GetFloat("Scale_HAD_bifurcate_Tau", 7.48405);
  _Relsampling_HAD_bifurcate_A = parm.GetFloat("Relsampling_HAD_bifurcate_A", 1.);
  _Relsampling_HAD_bifurcate_B = parm.GetFloat("Relsampling_HAD_bifurcate_B", 0.);
  _Relconst_HAD_bifurcate = parm.GetFloat("Relconst_HAD_bifurcate", 0.);
  _EtFlowFudge = parm.GetInt("EtFlowFudge", 0);
  cout<<"JAN "<<_EtFlowFudge<<endl;
  _RelRespTrans = parm.GetFloat("RelRespTrans", 1.);
  _RelResnTrans = parm.GetFloat("RelResnTrans", 1.);
  _RelTauTrans = parm.GetFloat("RelTauTrans", 1.);
  _Relphi_HAD_bifurcate_A = parm.GetFloat("Relphi_HAD_bifurcate_A", 1.);
  _Relphi_HAD_bifurcate_B = parm.GetFloat("Relphi_HAD_bifurcate_B", 0.);
  _RelconstPhi_HAD_bifurcate = parm.GetFloat("RelconstPhi_HAD_bifurcate", 0.);

  // only used for Momentum_SmearOption_HAD==2
  _scale_HAD_A = parm.GetFloat("Scale_HAD_A", 1.);  
  _scale_HAD_B = parm.GetFloat("Scale_HAD_B", 0.);  
  _scale_HAD_C = parm.GetFloat("Scale_HAD_C", 0.);  

  // minbias and zerobias library files
  if (getenv("MBLibraryRootPath") == NULL || getenv("ZBLibraryRootPath") == NULL ) {
    cout << "ERROR:  MBLibraryRootPath and ZBLibraryRootPath are not defined" << endl;
    assert(0);
  }
  TString mbLibraryRootPath(getenv("MBLibraryRootPath"));
  TString zbLibraryRootPath(getenv("ZBLibraryRootPath"));
  
  //run3 and 4 bools gotten at top of method, as in EfficiencySmear and EMSmear
  if(_run3bool && _run4bool){ 
    std::cout << "RecoilSmear:: MB library and alpha_mb not currently set up to allow both run3 and run4 true (you must use PMCS for each run separately)" << std::endl;
    exit(0);
  }else if(_run3bool && !_run4bool){
    _mbLibrary = mbLibraryRootPath + '/' + parm.GetChar("MBLibrary_file_Run3");
  }else if(!_run3bool && _run4bool){
    _mbLibrary = mbLibraryRootPath + '/' + parm.GetChar("MBLibrary_file_Run4");
  }else {
    cout<<"RecoilSmear: At least one of Run3 and Run4 in parameters file must be set to true"<<endl; 
    exit(0);
  }

  //run3 and 4 bools gotten at top of method, as in EfficiencySmear and EMSmear
  if(_run3bool && _run4bool){ 
    _zbLibraryvec = parm.GetVString("ZBLibrary_file_Run34");
  }else if(_run3bool && !_run4bool){
    _zbLibraryvec = parm.GetVString("ZBLibrary_file_Run3");
  }else if(!_run3bool && _run4bool){
    _zbLibraryvec = parm.GetVString("ZBLibrary_file_Run4");
  }else {
    cout<<"RecoilSmear: At least one of Run3 and Run4 in parameters file must be set to true"<<endl; 
    exit(0);
  }
 
  // _zbLibraryvec = parm.GetVString("ZBLibrary_file");
  _zbLibrary_is_binary = parm.GetBool("ZBLibrary_file_is_binary");
  _mbLibrary_is_binary = parm.GetBool("MBLibrary_file_is_binary");
  
  // smear true recoil direction based on Jan's studies on 08/30/2006
  _phi_smear_true_recoil_A = parm.GetFloat("phi_smear_true_recoil_A", 3.06);  
  _phi_smear_true_recoil_B = parm.GetFloat("phi_smear_true_recoil_B", 0.015);  

  // for hard recoil resolution
  _sampling_HAD = parm.GetFloat("Sampling_HAD", 0.8);
  _constant_HAD = parm.GetFloat("Constant_HAD_CC", 0.05);

  // underlying event smearing
  _METSmear_Option = parm.GetInt("METSmear_Option", 1);

  // read measured Z recoil file and add this to the Z or W signal
  _IsRecoilpTBinningSmeared = parm.GetBool("IsRecoilpTBinningSmeared", kFALSE);
  _read_recoil_file = parm.GetBool("read_recoil_file", kFALSE);

  // read ZB library file
  std::cout << _zbLibraryvec.size() << " ZBLibrary Files Are Known to this instance of RecoilSmear" << std::endl;
  _zbLibrary = zbLibraryRootPath + '/' +TString(_zbLibraryvec.at((int)(dummy->Rndm()*_zbLibraryvec.size())));

  // traditional method, and writing recoil file, not when using library method
  if( !_read_recoil_file )
  {
  std::cout << _zbLibrary << " will be used " << std::endl;
  if (!_zbLibrary_is_binary){
    ifstream inFile2(_zbLibrary, ios::in);
    _liblines2 = parm.GetInt("ZBLibrary_file_lines", 1000000);
    _ZBmetx = new double[_liblines2];
    _ZBmety = new double[_liblines2];
    _ZBset = new double[_liblines2];
    _ZBrunNo = new int[_liblines2];
    _ZBevtNo = new int[_liblines2];
    _ZBinstLumi = new double[_liblines2];
    
    cout << "Reading met, mety file for zerobias events now from file " << _zbLibrary << " ... " << endl;
    int liblines2 = 0;   
    while(!inFile2.eof()) {
      int runNo = 0, evtNo = 0, nVtx = 0;
      double instlumi = 0., scalarEt = 0., metx = 0., mety = 0.; 
      inFile2 >> runNo >> evtNo >> instlumi >> nVtx >> scalarEt >> metx >> mety;
      if(inFile2.eof()) break;
      if(liblines2>_liblines2-1) cout<<"over size"<<endl;
      _ZBmetx[liblines2] = metx;
      _ZBmety[liblines2] = mety;
      _ZBset[liblines2] = scalarEt;
      _ZBrunNo[liblines2] = runNo;
      _ZBevtNo[liblines2] = evtNo;
      _ZBinstLumi[liblines2] = instlumi;
      liblines2++;
    }
    cout << "Read " << liblines2 << " lines from zerobias file" << endl;
    
  // let liblines agree with each other
    if(_liblines2!=liblines2) {
      cout<<"# of lines for Zerobias in parameters.rc are not correct, this may cause code crash !!!!!!!!!"<<endl;
      _liblines2 = liblines2;
    }
  }
  else{
    TFile *f = new TFile(_zbLibrary);
    TTree *zbtree = (TTree*)gDirectory->Get("binary_tuple");
    std::cout << "zbtree has "<< zbtree->GetEntries() << " entries" << std::endl;
    if (zbtree->GetEntries() < 1){
      std::cerr << " I need a ZBLbrary to function in this mode " << std::endl;
      std::cerr << " You have configured a binary library but the tree has no events " << std::endl;
      abort();
    } 
    _liblines2 = 0;
    _ZBmetx = new double[zbtree->GetEntries()];
    _ZBmety = new double[zbtree->GetEntries()];
    _ZBset = new double[zbtree->GetEntries()];
    _ZBrunNo = new int[zbtree->GetEntries()];
    _ZBevtNo = new int[zbtree->GetEntries()];
    _ZBNumPV = new int[zbtree->GetEntries()];
    _ZBTickNum = new int[zbtree->GetEntries()];
    _ZBTimeLastL1Accept = new int[zbtree->GetEntries()];
    _ZBinstLumi = new double[zbtree->GetEntries()];
    ZBLibraryClass *zblibrary = new ZBLibraryClass(zbtree);
    cout << "Reading met, mety file for zerobias events now from file " << _zbLibrary << " ... " << endl;
    for (Int_t entryi=0; entryi < zbtree->GetEntries(); entryi++){
      zblibrary->GetEntry(entryi);
      if( zblibrary->event_InstLum < 0 ) continue;
      _ZBmetx[_liblines2] = zblibrary->event_HKmetx;
      _ZBmety[_liblines2] = zblibrary->event_HKmety;
      _ZBset[_liblines2] = zblibrary->event_HKset;
      _ZBrunNo[_liblines2] = zblibrary->event_runNum;
      _ZBevtNo[_liblines2] = zblibrary->event_eventNum;
      _ZBNumPV[_liblines2] = zblibrary->event_nPVS;
      _ZBinstLumi[_liblines2] =  zblibrary->event_InstLum;
#ifdef __NEWZBLIB__
      _ZBTickNum[_liblines2] = zblibrary->event_tickNum;
      _ZBTimeLastL1Accept[_liblines2] = zblibrary->event_timeLastL1Accept;
#else
      _ZBTickNum[_liblines2] = -1;
      _ZBTimeLastL1Accept[_liblines2] = -1;
#endif
      _liblines2++;
    }
    f->Close();
  }
  }
  
  if(_read_recoil_file) { // if we read recoil system file, which means we will do hard component and soft component simulation in one step

    _recoilRootFileName = parm.GetChar("recoilRootFileName");
    _num_recoil_pT_bins = parm.GetInt("num_recoil_pT_bins", 142);
    _recoil_pT_bin_edges = parm.GetVDouble("recoil_pT_bin_edges"); 
    _course_pT_bin_edges = parm.GetVDouble("course_pT_bin_edges"); 
    _Lumi_bin_edges = parm.GetVDouble("Lumi_bin_edges"); 

    _isCConly = parm.GetBool("isCConly", true);

    zrecoilmethod = new ZRecoilMethod_Util(_recoilRootFileName, _recoil_pT_bin_edges,_course_pT_bin_edges, _Lumi_bin_edges, _isCConly);
  } else { // if we do not read recoil pT system, which means we are going to smear hard component and soft component separately    
    //remove the warning from ROOT since we will overwrite _hmetxmety
    if(_METSmear_Option == 1) {
      TString metxmety_filename(parm.GetChar("metxmety_file"));
      gROOT->ProcessLine(TString(".x ")+metxmety_filename);
      _hmetxmety = (TH2F *)gROOT->FindObject("hmetxmety");
    } else if (_METSmear_Option == 3) {
      
      // minbias file and zerobias file
      if (!_mbLibrary_is_binary) {
	ifstream inFile1(_mbLibrary, ios::in);    
	
	if(_run3bool && !_run4bool){
	  _liblines1 = parm.GetInt("MBLibrary_file_lines_Run3", 1000000);
	}else if(!_run3bool && _run4bool){
	  _liblines1 = parm.GetInt("MBLibrary_file_lines_Run4", 1000000);
	}else {
	  std::cout << "RecoilSmear:: MB library and alpha_mb not currently set up to allow both run3 and run4 true (you must use PMCS for each run separately)" << std::endl;
	  exit(0);
	}
	
	_MBmetx = new double[_liblines1];
	_MBmety = new double[_liblines1];
	_MBset = new double[_liblines1];
	
	int liblines1 = 0;   
	int runNo = 0, evtNo = 0, nVtx = 0;
	double instlumi = 0., scalarEt = 0., metx = 0., mety = 0.; 
	cout << "Reading met, mety file for minbias events now from file " << _mbLibrary << " ... " << endl;
	while(!inFile1.eof()) {
	  inFile1 >> runNo >> evtNo >> instlumi >> nVtx >> scalarEt >> metx >> mety;
	  if(inFile1.eof()) break;
	  if(liblines1>_liblines1-1) cout<<"over size"<<endl;
	  _MBmetx[liblines1] = metx;
	  _MBmety[liblines1] = mety;
	  _MBset[liblines1] = scalarEt;
	  liblines1++;
	}
	cout << "Read " << liblines1 << " lines from minbias file" << endl;
	
	// let liblines agree with each other
	if(_liblines1!=liblines1) {
	  cout<<"# of lines for Minbias in parameters.rc are not correct, this may cause code crash !!!!!!!!!"<<endl;
	  _liblines1 = liblines1;
	}
      } else {
	MBLibraryClass __mbLibrary(_mbLibrary);
	_liblines1 = __mbLibrary.size();

	_MBmetx = new double[_liblines1];
	_MBmety = new double[_liblines1];
	_MBset = new double[_liblines1];
	
	if (__mbLibrary.copyToArrays(_MBmetx, _MBmety, _MBset) <= 0)
	  cerr << "Could not retrieve MB library... you know that this thing will crash, don't you?" << endl;	
      
      }
    }
    
    // scaling factor eflect the difference between underlying event contribution below electron window 
    // and the real minbias events, only used for METSmear_Option == 0, 1, 2
    _alpha_mb_overlay = parm.GetFloat("alpha_mb_overlay", 1.0);
    
    // scaling factors for minbias and zerobias events, only used for METSmear_Option == 3
    if(_run3bool && !_run4bool){
      _alpha_mb = parm.GetFloat("alpha_mb_Run3", 1.0);
    }else if(!_run3bool && _run4bool){
      _alpha_mb = parm.GetFloat("alpha_mb_Run4", 1.0);
    }else {
      std::cout << "RecoilSmear:: MB library and alpha_mb not currently set up to allow both run3 and run4 true (you must use PMCS for each run separately)" << std::endl;
      exit(0);
    }
    _alpha_mb_trans = parm.GetFloat("alpha_mb_trans", -1.0);
    _alpha_zb = parm.GetFloat("alpha_zb", 1.0);
    _underlying = parm.GetFloat("underlying", 3.0);

    // Luminosity dependent smearing
    Use_RecoilSmear_LumiDep = parm.GetBool("Use_RecoilSmear_LumiDep");
    Use_EtFlowFudge_LumiDep = parm.GetBool("Use_EtFlowFudge_LumiDep");
    RecoilSmear_LumiBins = parm.GetVInt("RecoilSmear_LumiBins");
    Scale_HAD_bifurcate_A_LumiDep = parm.GetVDouble("Scale_HAD_bifurcate_A_LumiDep");
    Scale_HAD_bifurcate_B_LumiDep = parm.GetVDouble("Scale_HAD_bifurcate_B_LumiDep");
    Scale_HAD_bifurcate_Tau_LumiDep = parm.GetVDouble("Scale_HAD_bifurcate_Tau_LumiDep");
    Relsampling_HAD_bifurcate_A_LumiDep = parm.GetVDouble("Relsampling_HAD_bifurcate_A_LumiDep");
    Relsampling_HAD_bifurcate_B_LumiDep = parm.GetVDouble("Relsampling_HAD_bifurcate_B_LumiDep");
    EtFlowFudge_LumiDep = parm.GetVInt("EtFlowFudge_LumiDep");
    Use_alpha_mb_LumiDep = parm.GetBool("Use_alpha_mb_LumiDep");
    alpha_mb_LumiBins = parm.GetVInt("alpha_mb_LumiBins");
    alpha_mb_LumiDep = parm.GetVDouble("alpha_mb_LumiDep");
            
    if (Use_alpha_mb_LumiDep && alpha_mb_LumiDep.size() <= alpha_mb_LumiBins.size()) {
      cout << "You gave less alpha_mb values than luminosity bins." << endl
	   << "Setting luminosity dependence to false" << endl;
      Use_alpha_mb_LumiDep = false;
    }      

    if (Use_RecoilSmear_LumiDep && ( Scale_HAD_bifurcate_A_LumiDep.size() <= RecoilSmear_LumiBins.size()
				     || Scale_HAD_bifurcate_B_LumiDep.size() <= RecoilSmear_LumiBins.size()
				     || Scale_HAD_bifurcate_Tau_LumiDep.size() <= RecoilSmear_LumiBins.size()
				     || Relsampling_HAD_bifurcate_A_LumiDep.size() <= RecoilSmear_LumiBins.size()
				     || Relsampling_HAD_bifurcate_B_LumiDep.size() <= RecoilSmear_LumiBins.size()
				     || EtFlowFudge_LumiDep.size() <= RecoilSmear_LumiBins.size() )) {
      cout << "You gave less hard recoil smearing values than luminosity bins." << endl
	   << "Setting luminosity dependence to false" << endl;
      Use_RecoilSmear_LumiDep = false;
    }

    // For propagation of uncertainty
    WMass_Recoil_Templates_Shift = parm.GetBool("WMass_Recoil_Templates_Shift");
    WMass_Recoil_Templates_Varying_Eigenvector = parm.GetInt("WMass_Recoil_Templates_Varying_Eigenvector");
    WMass_Recoil_Templates_Varying_Lumi_Bin = parm.GetInt("WMass_Recoil_Templates_Varying_Lumi_Bin");
    WMass_Recoil_Templates_Varying_Amplitude = parm.GetDouble("WMass_Recoil_Templates_Varying_Amplitude");
    Scale_Cov_Matrix_1 = parm.GetVDouble("Scale_Cov_Matrix_1");
    Scale_Cov_Matrix_2 = parm.GetVDouble("Scale_Cov_Matrix_2");
    Scale_Cov_Matrix_3 = parm.GetVDouble("Scale_Cov_Matrix_3");
    Resolution_Cov_Matrix_1 = parm.GetVDouble("Resolution_Cov_Matrix_1");
    Resolution_Cov_Matrix_2 = parm.GetVDouble("Resolution_Cov_Matrix_2");

    if(Use_RecoilSmear_LumiDep && WMass_Recoil_Templates_Shift) {	
      
      if (WMass_Recoil_Templates_Varying_Eigenvector >= 1 && WMass_Recoil_Templates_Varying_Eigenvector <= 3) {
	TMatrixD covmatrix(3,3);
	covmatrix[0][0] = Scale_Cov_Matrix_1[0];
	covmatrix[0][1] = Scale_Cov_Matrix_1[1];
	covmatrix[0][2] = Scale_Cov_Matrix_1[2];
	covmatrix[1][0] = Scale_Cov_Matrix_2[0];
	covmatrix[1][1] = Scale_Cov_Matrix_2[1];
	covmatrix[1][2] = Scale_Cov_Matrix_2[2];
	covmatrix[2][0] = Scale_Cov_Matrix_3[0];
	covmatrix[2][1] = Scale_Cov_Matrix_3[1];
	covmatrix[2][2] = Scale_Cov_Matrix_3[2];
	TMatrixD eigenvectors(3,3);
	TVectorD eigenvalues(3);
	eigenvectors = covmatrix.EigenVectors(eigenvalues);	  
	std::cout << "Shifting recoil parameters..." << std::endl;
	covmatrix.Print(); eigenvectors.Print(); eigenvalues.Print();
	Scale_HAD_bifurcate_A_LumiDep[WMass_Recoil_Templates_Varying_Lumi_Bin] += TMath::Sqrt(eigenvalues[WMass_Recoil_Templates_Varying_Eigenvector-1]) *
	  WMass_Recoil_Templates_Varying_Amplitude * eigenvectors[0][WMass_Recoil_Templates_Varying_Eigenvector-1];
	Scale_HAD_bifurcate_B_LumiDep[WMass_Recoil_Templates_Varying_Lumi_Bin] += TMath::Sqrt(eigenvalues[WMass_Recoil_Templates_Varying_Eigenvector-1]) *
	  WMass_Recoil_Templates_Varying_Amplitude * eigenvectors[1][WMass_Recoil_Templates_Varying_Eigenvector-1];
	Scale_HAD_bifurcate_Tau_LumiDep[WMass_Recoil_Templates_Varying_Lumi_Bin] += TMath::Sqrt(eigenvalues[WMass_Recoil_Templates_Varying_Eigenvector-1]) *
	  WMass_Recoil_Templates_Varying_Amplitude * eigenvectors[2][WMass_Recoil_Templates_Varying_Eigenvector-1];
	Relsampling_HAD_bifurcate_A_LumiDep[WMass_Recoil_Templates_Varying_Lumi_Bin] += 0.0;
	alpha_mb_LumiDep[WMass_Recoil_Templates_Varying_Lumi_Bin] += 0.0;
      } else if (WMass_Recoil_Templates_Varying_Eigenvector >= 4 && WMass_Recoil_Templates_Varying_Eigenvector <= 5) {
	TMatrixD covmatrix(2,2);
	covmatrix[0][0] = Resolution_Cov_Matrix_1[0];
	covmatrix[0][1] = Resolution_Cov_Matrix_1[1];
	covmatrix[1][0] = Resolution_Cov_Matrix_2[0];
	covmatrix[1][1] = Resolution_Cov_Matrix_2[1];
	TMatrixD eigenvectors(2,2);
	TVectorD eigenvalues(2);
	eigenvectors = covmatrix.EigenVectors(eigenvalues);	  
	std::cout << "Shifting recoil parameters..." << std::endl;
	covmatrix.Print(); eigenvectors.Print(); eigenvalues.Print();
	Scale_HAD_bifurcate_A_LumiDep[WMass_Recoil_Templates_Varying_Lumi_Bin] += 0.0;
	Scale_HAD_bifurcate_B_LumiDep[WMass_Recoil_Templates_Varying_Lumi_Bin] += 0.0;
	Scale_HAD_bifurcate_Tau_LumiDep[WMass_Recoil_Templates_Varying_Lumi_Bin] += 0.0;
	Relsampling_HAD_bifurcate_A_LumiDep[WMass_Recoil_Templates_Varying_Lumi_Bin] += TMath::Sqrt(eigenvalues[WMass_Recoil_Templates_Varying_Eigenvector-4]) *
	  WMass_Recoil_Templates_Varying_Amplitude * eigenvectors[0][WMass_Recoil_Templates_Varying_Eigenvector-4];
	alpha_mb_LumiDep[WMass_Recoil_Templates_Varying_Lumi_Bin] += TMath::Sqrt(eigenvalues[WMass_Recoil_Templates_Varying_Eigenvector-4]) *
	  WMass_Recoil_Templates_Varying_Amplitude * eigenvectors[1][WMass_Recoil_Templates_Varying_Eigenvector-4];
      }
    }

    if(!Use_RecoilSmear_LumiDep && WMass_Recoil_Templates_Shift) {	
      
      if (WMass_Recoil_Templates_Varying_Eigenvector >= 1 && WMass_Recoil_Templates_Varying_Eigenvector <= 3) {
	TMatrixD covmatrix(3,3);
	covmatrix[0][0] = Scale_Cov_Matrix_1[0];
	covmatrix[0][1] = Scale_Cov_Matrix_1[1];
	covmatrix[0][2] = Scale_Cov_Matrix_1[2];
	covmatrix[1][0] = Scale_Cov_Matrix_2[0];
	covmatrix[1][1] = Scale_Cov_Matrix_2[1];
	covmatrix[1][2] = Scale_Cov_Matrix_2[2];
	covmatrix[2][0] = Scale_Cov_Matrix_3[0];
	covmatrix[2][1] = Scale_Cov_Matrix_3[1];
	covmatrix[2][2] = Scale_Cov_Matrix_3[2];
	TMatrixD eigenvectors(3,3);
	TVectorD eigenvalues(3);
	eigenvectors = covmatrix.EigenVectors(eigenvalues);	  
	std::cout << "Shifting recoil parameters..." << std::endl;
	covmatrix.Print(); eigenvectors.Print(); eigenvalues.Print();
	_scale_HAD_bifurcate_A += TMath::Sqrt(eigenvalues[WMass_Recoil_Templates_Varying_Eigenvector-1]) *
	  WMass_Recoil_Templates_Varying_Amplitude * eigenvectors[0][WMass_Recoil_Templates_Varying_Eigenvector-1];
	_scale_HAD_bifurcate_B += TMath::Sqrt(eigenvalues[WMass_Recoil_Templates_Varying_Eigenvector-1]) *
	  WMass_Recoil_Templates_Varying_Amplitude * eigenvectors[1][WMass_Recoil_Templates_Varying_Eigenvector-1];
	_scale_HAD_bifurcate_Tau += TMath::Sqrt(eigenvalues[WMass_Recoil_Templates_Varying_Eigenvector-1]) *
	  WMass_Recoil_Templates_Varying_Amplitude * eigenvectors[2][WMass_Recoil_Templates_Varying_Eigenvector-1];
	_Relsampling_HAD_bifurcate_A += 0.0;
	_alpha_mb += 0.0;
      } else if (WMass_Recoil_Templates_Varying_Eigenvector >= 4 && WMass_Recoil_Templates_Varying_Eigenvector <= 5) {
	TMatrixD covmatrix(2,2);
	covmatrix[0][0] = Resolution_Cov_Matrix_1[0];
	covmatrix[0][1] = Resolution_Cov_Matrix_1[1];
	covmatrix[1][0] = Resolution_Cov_Matrix_2[0];
	covmatrix[1][1] = Resolution_Cov_Matrix_2[1];
	TMatrixD eigenvectors(2,2);
	TVectorD eigenvalues(2);
	eigenvectors = covmatrix.EigenVectors(eigenvalues);	  
	std::cout << "Shifting recoil parameters..." << std::endl;
	covmatrix.Print(); eigenvectors.Print(); eigenvalues.Print();
	_scale_HAD_bifurcate_A += 0.0;
	_scale_HAD_bifurcate_B += 0.0;
	_scale_HAD_bifurcate_Tau += 0.0;
	_Relsampling_HAD_bifurcate_A += TMath::Sqrt(eigenvalues[WMass_Recoil_Templates_Varying_Eigenvector-4]) *
	  WMass_Recoil_Templates_Varying_Amplitude * eigenvectors[0][WMass_Recoil_Templates_Varying_Eigenvector-4];
	_alpha_mb += TMath::Sqrt(eigenvalues[WMass_Recoil_Templates_Varying_Eigenvector-4]) *
	  WMass_Recoil_Templates_Varying_Amplitude * eigenvectors[1][WMass_Recoil_Templates_Varying_Eigenvector-4];
      }
    }
    
    // fudge factor for "SET response"
    _alpha_SETresponse = parm.GetFloat("alpha_SETresponse", 1.0);
    _SETresponse_Model = parm.GetInt("SETresponse_Model");
    if (_SETresponse_Model==1){
      std::vector<double> _SETresponse_RunIIb_par;
      _SETresponse_RunIIb_par = parm.GetVDouble("SETresponse_RunIIb_par");
      _setfunction = new MySETFunction;
      double p[_SETresponse_RunIIb_par.size()];
      for (Int_t inum=0; inum < _SETresponse_RunIIb_par.size(); ++inum){
	p[inum] = _SETresponse_RunIIb_par.at(inum);
      }
      _setfunction->setp(p);
    }    
    // Data file for Mikolaj's SET model
    _SETmodelDatafile = parm.GetChar("SETmodelDatafile");

    // read instlumi bins
    _instlumi_bins = parm.GetVDouble("InstLumi_Bins");
    
    // parameters used to parameterize metX and metY shapes for different luminosity regions
    _metx_mean = parm.GetVDouble("MetX_mean");
    _mety_mean = parm.GetVDouble("MetY_mean");
    _metx_sigma = parm.GetVDouble("MetX_sigma");
    _mety_sigma = parm.GetVDouble("MetY_sigma");
    
    // index to MB and ZB events
    _MBEvtIndex = -1;
    _ZBEvtIndex = -1;
    
    // parameters used to calculate effective minbias luminosity
    _Factors_Lw_Lmb = parm.GetVDouble("Factors_Lw_Lmb");
    
    // # of luminosity bins
    _NumLumiBins = _metx_mean.size();
    
    for(int i=0; i<_NumLumiBins; i++) {
      TF1 func1("func1", fitf, -10., 10., 2);
      func1.SetParameters(_metx_mean[i], _metx_sigma[i]);
      metx_res_vect.push_back(func1);
      
      TF1 func2("func2", fitf, -10., 10., 2); 
      func2.SetParameters(_mety_mean[i], _mety_sigma[i]);
      mety_res_vect.push_back(func2);
    }
  } // read neccesary files for smearing hard component and soft component separately
  
  // photons with pT > pT_cut and well separated from electrons
  // will be treated as independent EM clusters, energy smearing will be applied
  // and also be included in the final missing Et calculation
  _merge_fsr_photons_met = parm.GetBool("merge_fsr_photons_met", kTRUE);
  _minimum_pT_cut = parm.GetFloat("pT_cut", 5.);

//   //////////////////////////////// DEBUG
//   //
//   cout << "RecoilSmear::Constructor: MB_index= " << _MBEvtIndex 
//        << ", ZB_index=" << _ZBEvtIndex
//        << ", _liblines1=" << _liblines1
//        << ", _liblines2=" << _liblines2 << endl;
//   //
//   //////////////////////////////// DEBUG
  _ScalarEt_cone = 0.;



  // Top Bottom Asym Correction Parameters
  _Top_Bottom_Effect_Correction = parm.GetBool("TBCorrection", kFALSE);
  _TB_Correction_Option = parm.GetInt("TBCorrection_Option", 1);
  
  _Top_Bottom_Apply_Last = parm.GetBool("TBApplyLast", kFALSE);
  _TBPhi_response_Hard_Only = parm.GetBool("TBPhi_response_Hard_Only", kFALSE);
  _TBPhi_response_Soft_Only = parm.GetBool("TBPhi_response_Soft_Only", kFALSE);
    
  // only for _TB_Correction_Option==1 
  _TB_alpha = parm.GetFloat("TBalpha", 0.001);
  _TB_beta = parm.GetFloat("TBbeta", 0.);
  _TBmodel_patrice = parm.GetBool("TBmodel_patrice", false);

  if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_read_recoil_file ){
    if (_Top_Bottom_Apply_Last && (_TBPhi_response_Hard_Only ||  _TBPhi_response_Soft_Only)){
      std::cout << "These Options are incompatible: " << std::endl;
      std::cout << "TBCorrection: " <<  _Top_Bottom_Effect_Correction << std::endl;
      std::cout << "TBApplyLast: " <<  _Top_Bottom_Apply_Last << std::endl;
      std::cout << "TBPhi_response_Hard_Only: " << _TBPhi_response_Hard_Only  << std::endl;
      std::cout << "TBPhi_response_Soft_Only: " <<  _TBPhi_response_Soft_Only << std::endl;
      exit(0);
    }
     if (_TBPhi_response_Hard_Only &&  _TBPhi_response_Soft_Only){
       std::cout << "These Options are incompatible: " << std::endl;
       std::cout << "TBCorrection: " <<  _Top_Bottom_Effect_Correction << std::endl;
       std::cout << "TBPhi_response_Hard_Only: " << _TBPhi_response_Hard_Only  << std::endl;
       std::cout << "TBPhi_response_Soft_Only: " <<  _TBPhi_response_Soft_Only << std::endl;
      exit(0);
    }

  }

  // only for _TB_Correction_Option==2
  _TB_Library = std::string(parm.GetChar("TBLibrary_file", "TBLibrary.root"));
  _pedanticRandomRecoil = parm.GetBool("pedanticRandomRecoil");
  _TB_Library = _TB_Library.substr(_TB_Library.find_first_not_of(" ", 0), _TB_Library.find_last_not_of(" ", _TB_Library.size()) - _TB_Library.find_first_not_of(" ",0)+1);
  if (getenv("TBLibraryRootPath") == NULL) {
    std::cout << " - No $TBLibraryRootPath set: use the current dir." << std::endl;
    _TB_Library = "./" + _TB_Library;
  } else {
    _TB_Library = std::string(getenv("TBLibraryRootPath")) + "/"+ _TB_Library;
  }

  if ( _Top_Bottom_Effect_Correction && _TB_Correction_Option==2 && !_read_recoil_file) {
    for (int itb=0; itb<5; itb++) for (int jtb=0; jtb<10; jtb++) for (int ktb=0; ktb<10; ktb++)_Top_Bottom_exists[itb][jtb][ktb] = false;
    _ftblib = new TFile(_TB_Library.c_str());
    if (!_ftblib->IsZombie()) {
      std::cout << " - TBLibrary_file is opened: " << _TB_Library << std::endl;
      std::stringstream tbhname;
      for (int itb=0; itb<5; itb++){
        for (int jtb=0; jtb<10; jtb++){
          for (int ktb=0; ktb<10; ktb++){
            tbhname.str("");
            tbhname << "hdmet2d_" << itb << "_" << jtb << "_" << ktb;
            TH2D* tbhdmet = (TH2D*)_ftblib->Get(tbhname.str().c_str());
            if (tbhdmet>0) _tblib[tbhname.str()] = tbhdmet;
          }
        }
      }
    }
    else {
      std::cout << " - Failed to open TBLibrary_file :" << _TB_Library << std::endl;
      exit(0);
    }

  }

  cout<<"Finished RecoilSmear initialization"<<endl;
}

// smear the recoil system
PMCSRecoil RecoilSmear::SmearRecoil(PMCSRecoil &recoil_gen, TRandom3 *dummy) {

//   //////////////////////////////// DEBUG
//   //
//   cout << "SmearRecoil(1): MB_index= " << _MBEvtIndex 
//        << ", ZB_index=" << _ZBEvtIndex << endl;
//   //
//   //////////////////////////////// DEBUG

  PMCSRecoil recoil_smear = recoil_gen;
  _ScalarEt_cone=0.;
  _recoilx_beforeTB=0.;
  _recoily_beforeTB=0.;
  // Resets caching of hard scalar Et value for RecoilSmear::ScalarEt_hard(),
  // RecoilSmear::ScalarEt() and RecoilSmear::GetLastHardScalarEt_Method_B() methods.
  // This caching mechanism is only used when 
  // _Momentum_SmearOption_HAD=1 option is selected 
  // (i.e. for "bifurcated" hard recoil model from Z->nunu FULL MC).
  // Otherwise, _scalarEt_hard=0 is taken.
  // Methods RecoilSmear::ScalarEt() and RecoilSmear::ScalarEt_hard() and
  // RecoilSmear::GetLastHardScalarEt_Method_B must be called only
  // AFTER RecoilSmear::SmearHardRecoil_Method_B() or RecoilSmear::SmearRecoil().
  _Hard_SET_exists = false;
  _Hard_Recoil_exists=false;
  if (_Momentum_SmearOption_HAD==3) {
    hard_recoil->unflip();
  }
  //  _Hard_SET_smeared=-1;
  
  // if we just use the recoil system from Z events and apply it on W events
  // we will treat hard component and soft component together
  if(_read_recoil_file) {
    double Rec_pT_smear, Rec_Phi_smear;
    double recoilx_smear, recoily_smear;
    double theSET;

    double Rpx = recoil_gen.Recoilx();
    double Rpy = recoil_gen.Recoily();
    double Rpt = recoil_gen.Recoil();
    
    double genZpx = -Rpx;
    double genZpy = -Rpy;
    double genZpT = Rpt;
    
    _chosen_recoil =0.;
    _gen_Z_pT = genZpT;

    zrecoilmethod -> PickRecoil(genZpx, genZpy, recoilx_smear, recoily_smear, dummy);
    _chosen_recoil = sqrt(recoilx_smear*recoilx_smear + recoily_smear*recoily_smear);    
    _scalarEt_chosen = zrecoilmethod->PickSET(_gen_Z_pT,_chosen_recoil);

    // set the output smeared recoil jet
    recoil_smear.SetRecoil(recoilx_smear, recoily_smear);
  } else {
    //
    // treat the hard component (pT of W and Z bosons) as a single jet and apply energy scaling
    //
    double smear_recoil_pT = 0., smear_recoil_phi = 0., smear_SET = 0.;
    double raw_recoil_phi = recoil_gen.RecoilPhi();
    double raw_recoil_pT = recoil_gen.Recoil();
    double _Lumi = recoil_gen.GetLumi();
    int _HardLumiBin = 0;
    int _SoftLumiBin = 0;

    if (Use_RecoilSmear_LumiDep) {
      for (Int_t ibin=0; ibin < RecoilSmear_LumiBins.size(); ibin++) {
	if (_Lumi > RecoilSmear_LumiBins[ibin]) _HardLumiBin++;
	else break;
      }
    }
    if (Use_alpha_mb_LumiDep) {
      for (Int_t ibin=0; ibin < alpha_mb_LumiBins.size(); ibin++) {
	if (_Lumi > alpha_mb_LumiBins[ibin]) _SoftLumiBin++;
	else break;
      }
    }

    if(_Momentum_SmearOption_HAD == 0)
      SmearHardRecoil_Method_A(raw_recoil_pT, raw_recoil_phi, 
			       _scale_HAD, _offset_HAD, 
			       _phi_smear_true_recoil_A, _phi_smear_true_recoil_B,
			       _constant_HAD, _sampling_HAD, 
			       dummy, smear_recoil_pT, smear_recoil_phi);
    else if(_Momentum_SmearOption_HAD == 1) {

      double eff_scale_HAD_bifurcate_A, eff_scale_HAD_bifurcate_B, eff_scale_HAD_bifurcate_Tau, 
	eff_Relsampling_HAD_bifurcate_A, eff_Relsampling_HAD_bifurcate_B; 
      int eff_EtFlowFudge;
      if (Use_RecoilSmear_LumiDep) {
	eff_scale_HAD_bifurcate_A = Scale_HAD_bifurcate_A_LumiDep[_HardLumiBin];
	eff_scale_HAD_bifurcate_B = Scale_HAD_bifurcate_B_LumiDep[_HardLumiBin];
	eff_scale_HAD_bifurcate_Tau = Scale_HAD_bifurcate_Tau_LumiDep[_HardLumiBin];
	eff_Relsampling_HAD_bifurcate_A = Relsampling_HAD_bifurcate_A_LumiDep[_HardLumiBin];
	eff_Relsampling_HAD_bifurcate_B = Relsampling_HAD_bifurcate_B_LumiDep[_HardLumiBin];
	eff_EtFlowFudge = EtFlowFudge_LumiDep[_HardLumiBin];
      } else {
	eff_scale_HAD_bifurcate_A = _scale_HAD_bifurcate_A;
	eff_scale_HAD_bifurcate_B = _scale_HAD_bifurcate_B;
	eff_scale_HAD_bifurcate_Tau = _scale_HAD_bifurcate_Tau;
	eff_Relsampling_HAD_bifurcate_A = _Relsampling_HAD_bifurcate_A;
	eff_Relsampling_HAD_bifurcate_B = _Relsampling_HAD_bifurcate_B;
	eff_EtFlowFudge = _EtFlowFudge;
      }


      SmearHardRecoil_Method_B(raw_recoil_pT, raw_recoil_phi, 
			       eff_scale_HAD_bifurcate_A, eff_scale_HAD_bifurcate_B, eff_scale_HAD_bifurcate_Tau, 
			       eff_Relsampling_HAD_bifurcate_A, eff_Relsampling_HAD_bifurcate_B, _Relconst_HAD_bifurcate, 
			       _RelRespTrans, _RelResnTrans, _RelTauTrans,
			       _Relphi_HAD_bifurcate_A, _Relphi_HAD_bifurcate_B, _RelconstPhi_HAD_bifurcate,
			       dummy, smear_recoil_pT, smear_recoil_phi, smear_SET, -1, -1, -1, -1, false, false, eff_EtFlowFudge, _Lumi);
    }
    else if(_Momentum_SmearOption_HAD == 2)
      SmearHardRecoil_Method_C(raw_recoil_pT, raw_recoil_phi, 
			       _scale_HAD_A, _scale_HAD_B, _scale_HAD_C, 
			       _phi_smear_true_recoil_A, _phi_smear_true_recoil_B, 
			       _constant_HAD, _sampling_HAD, 
			       dummy, smear_recoil_pT, smear_recoil_phi);
    else if(_Momentum_SmearOption_HAD == 3) {

      double eff_scale_HAD_bifurcate_A, eff_scale_HAD_bifurcate_B, eff_scale_HAD_bifurcate_Tau, 
	eff_Relsampling_HAD_bifurcate_A, eff_Relsampling_HAD_bifurcate_B; 
      int eff_EtFlowFudge;
      if (Use_RecoilSmear_LumiDep) {
	eff_scale_HAD_bifurcate_A = Scale_HAD_bifurcate_A_LumiDep[_HardLumiBin];
	eff_scale_HAD_bifurcate_B = Scale_HAD_bifurcate_B_LumiDep[_HardLumiBin];
	eff_scale_HAD_bifurcate_Tau = Scale_HAD_bifurcate_Tau_LumiDep[_HardLumiBin];
	eff_Relsampling_HAD_bifurcate_A = Relsampling_HAD_bifurcate_A_LumiDep[_HardLumiBin];
	eff_Relsampling_HAD_bifurcate_B = Relsampling_HAD_bifurcate_B_LumiDep[_HardLumiBin];
	eff_EtFlowFudge = EtFlowFudge_LumiDep[_HardLumiBin];
      } else {
	eff_scale_HAD_bifurcate_A = _scale_HAD_bifurcate_A;
	eff_scale_HAD_bifurcate_B = _scale_HAD_bifurcate_B;
	eff_scale_HAD_bifurcate_Tau = _scale_HAD_bifurcate_Tau;
	eff_Relsampling_HAD_bifurcate_A = _Relsampling_HAD_bifurcate_A;
	eff_Relsampling_HAD_bifurcate_B = _Relsampling_HAD_bifurcate_B;
	eff_EtFlowFudge = _EtFlowFudge;
      }


      SmearHardRecoil_Method_D(raw_recoil_pT, raw_recoil_phi, 
			       eff_scale_HAD_bifurcate_A, eff_scale_HAD_bifurcate_B, eff_scale_HAD_bifurcate_Tau, 
			       eff_Relsampling_HAD_bifurcate_A, eff_Relsampling_HAD_bifurcate_B, _Relconst_HAD_bifurcate, 
			       _RelRespTrans, _RelResnTrans, _RelTauTrans,
			       _Relphi_HAD_bifurcate_A, _Relphi_HAD_bifurcate_B, _RelconstPhi_HAD_bifurcate,
			       dummy, smear_recoil_pT, smear_recoil_phi, smear_SET, -1, -1, -1, -1, false, false, eff_EtFlowFudge, _Lumi);

    }
    else cout<<"MomentumSmear_Option should be 0, 1, 2, 3, not "<<_Momentum_SmearOption_HAD<<endl;
    
    // hard component contribution 
    double recoilx_smear = smear_recoil_pT * cos(smear_recoil_phi);
    double recoily_smear = smear_recoil_pT * sin(smear_recoil_phi);
    
    
    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && _TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
      ApplyTopBottomAsym(recoilx_smear, recoily_smear);   
    }
    
    recoil_smear.SetRecoil(recoilx_smear, recoily_smear);

    // keep this information
    _recoilX_HardComponent = recoilx_smear;
    _recoilY_HardComponent = recoily_smear;
    
    //
    // Underlying Event Simulation (spectator quarks contribution from colliding protons and anti-protons,
    // also include contribution from multiple collisions)
    // 
    double smear_Metx_From_ZB=0., smear_Mety_From_ZB=0., smear_Metx_From_MB=0., smear_Mety_From_MB=0.;
    double smear_Metx=0., smear_Mety=0.;

    if(_METSmear_Option == 0)
      SmearSoftRecoil_Method_A(_underlying, _alpha_mb_overlay,
			       dummy, smear_Metx, smear_Mety);
    else if(_METSmear_Option == 1)
      SmearSoftRecoil_Method_B(_hmetxmety, _alpha_mb_overlay,
			       dummy, smear_Metx, smear_Mety);
    else if(_METSmear_Option == 2)
      SmearSoftRecoil_Method_C(_instLumi, _alpha_mb_overlay,
			       dummy, smear_Metx, smear_Mety);
    else if(_METSmear_Option == 3) {
      double eff_alpha_mb;
      
      if (Use_alpha_mb_LumiDep)
	eff_alpha_mb = alpha_mb_LumiDep[_SoftLumiBin];
      else
	eff_alpha_mb = _alpha_mb;

      if (_alpha_mb_trans>0) {
        double Jphi=recoil_gen.RecoilPhi();
        SmearSoftRecoil_Method_D(eff_alpha_mb, _alpha_zb, dummy,
                                 smear_Metx_From_MB, smear_Mety_From_MB,
                                 smear_Metx_From_ZB, smear_Mety_From_ZB,
                                 smear_Metx, smear_Mety,
                                 &Jphi, _alpha_mb_trans);
      } else {
        SmearSoftRecoil_Method_D(eff_alpha_mb, _alpha_zb, dummy,
                                 smear_Metx_From_MB, smear_Mety_From_MB,
                                 smear_Metx_From_ZB, smear_Mety_From_ZB,
                                 smear_Metx, smear_Mety);
      }
    } else cout<<"METSmear_Option should be 0, 1, 2, 3, not "<<_METSmear_Option<<endl;
    


    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only && _TBPhi_response_Soft_Only){
      ApplyTopBottomAsym(smear_Metx, smear_Mety);   
    }

    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==2 && _METSmear_Option==3){    
      // Only works with _METSmear_Option==3
      // apply TB correction.
      ApplyTopBottomAsym_B(smear_Metx, smear_Mety, !_pedanticRandomRecoil);  
      //////////// debug ////////////
      //  std::cout << " -- RecoilSmear::SmearRecoil(): _Top_Bottom_exists=" 
      //            << _Top_Bottom_exists << "; _tbdmetx=" << _tbdmetx << "; _tbdmety=" 
      //            << _tbdmety << std::endl;
      /////////////////////////////// 
    }

    // keep this information and later can be written to a root file
    _recoilX_SoftComponent = smear_Metx;
    _recoilY_SoftComponent = smear_Mety;


    
    // add soft component
    recoilx_smear += smear_Metx;
    recoily_smear += smear_Mety;

    // set the output smeared recoil jet

    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
      ApplyTopBottomAsym(recoilx_smear, recoily_smear);
    }
    
    recoil_smear.SetRecoil(recoilx_smear, recoily_smear);    
  }
    
  // fill some histograms
  if (_makeCheckSmearingPlots)  fillSmearHistograms(recoil_gen,recoil_smear);
  
//   //////////////////////////////// DEBUG
//   //
//   cout << "SmearRecoil(2): MB_index= " << _MBEvtIndex 
//        << ", ZB_index=" << _ZBEvtIndex << endl;
//   //
//   //////////////////////////////// DEBUG
  return recoil_smear;
}

// smear hard component
void RecoilSmear::SmearHardRecoil_Method_A(double raw_recoil_pT, double raw_recoil_phi, 
					   double scale_HAD, double offset_HAD, 
					   double phi_smear_true_recoil_A, double phi_smear_true_recoil_B,
					   double constant_HAD, double sampling_HAD, 
					   TRandom3 *dummy, double& smear_recoil_pT, double& smear_recoil_phi) {
  double smear_recoil_pT_tmp = raw_recoil_pT * scale_HAD + offset_HAD;
  
  // smearing true recoil direction and make sure smeared recoil phi between 0 and 2pi
  double phi_sigma = phi_smear_true_recoil_A/raw_recoil_pT + phi_smear_true_recoil_B;
  double phi_tmp = raw_recoil_phi + phi_sigma * dummy->Gaus(0., 1.);
  phi_tmp = fmod(phi_tmp, 2*TMath::Pi());
  if(phi_tmp > 2*TMath::Pi()) phi_tmp -= 2*TMath::Pi();
  else if(phi_tmp < 0.) phi_tmp += 2*TMath::Pi();
  smear_recoil_phi = phi_tmp;
  
  // smear the recoil system resolution
  double jetres = sqrt(constant_HAD*constant_HAD*raw_recoil_pT*raw_recoil_pT + 
		       sampling_HAD*sampling_HAD*raw_recoil_pT);  
  double pT_tmp = smear_recoil_pT_tmp + jetres * dummy->Gaus(0., 1.);
  //while(pT_tmp < 0.) pT_tmp = smear_recoil_pT_tmp + jetres * dummy->Gaus(0., 1.);
  smear_recoil_pT = pT_tmp;

  // if smeared recoil pT is negative, then take the absolute value and change recoil phi direction
  if(pT_tmp < 0.) {
    smear_recoil_pT = -pT_tmp;
    
    smear_recoil_phi += TMath::Pi();
    if(smear_recoil_phi < 0.) smear_recoil_phi += 2 * TMath::Pi();
    else if(smear_recoil_phi > 2.*TMath::Pi()) smear_recoil_phi -= 2 * TMath::Pi();
  }
} 

// smear hard component
void RecoilSmear::SmearHardRecoil_Method_B(double raw_recoil_pT, 
					   double raw_recoil_phi, 
					   double Relscale_HAD_bifurcate_A, 
					   double Relscale_HAD_bifurcate_B,
                                           double Relscale_HAD_bifurcate_Tau,
					   double Relsampling_HAD_bifurcate_A, 
					   double Relsampling_HAD_bifurcate_B, 
					   double Relconst_HAD_bifurcate, 
					   double Reltrans_HAD_RelRespTrans, 
					   double Reltrans_HAD_RelResnTrans, 
					   double Reltrans_HAD_RelTauTrans,
					   double Relphi_HAD_bifurcate_A, 
					   double Relphi_HAD_bifurcate_B, 
					   double RelconstPhi_HAD_bifurcate,
					   TRandom3 *dummy, 
					   double& smear_recoil_pT, 
					   double& smear_recoil_phi,
					   double& smear_SET,
					   double pt_resol_external,  // effective only when skip_Znunu_randomization=TRUE
					   double delta_phi_external, // effective only when skip_Znunu_randomization=TRUE
					   double znunu_SET_Hard_external, // effective only when skip_Znunu_randomization=TRUE
					   double znunu_SET_Hard_expected_external, // effective only when skip_Znunu_randomization=TRUE
					   bool skip_Znunu_randomization,
					   bool skip_Znunu_fudging,
					   int EtFlowFudge,
					   double instlum) {
  // NOTE: needs to read WZ_Utils.hpp to see which model is really used as default
  /*
  // do everything in one step
  wz_utils::FlipARecoil2(raw_recoil_pT, raw_recoil_phi, smear_recoil_pT, smear_recoil_phi, 
			 Relscale_HAD_bifurcate_A, Relscale_HAD_bifurcate_B, 
			 Relsampling_HAD_bifurcate_A, Relsampling_HAD_bifurcate_B, Relconst_HAD_bifurcate, 
			 Reltrans_HAD_RelRespTrans, Reltrans_HAD_RelResnTrans, Reltrans_HAD_RelTauTrans,
			 Relphi_HAD_bifurcate_A, Relphi_HAD_bifurcate_B, RelconstPhi_HAD_bifurcate,
			 pt_resol_external,  // effective only when skip_Znunu_randomization=TRUE
			 delta_phi_external, // effective only when skip_Znunu_randomization=TRUE  
			 skip_Znunu_randomization,
			 skip_Znunu_fudging  );
			 
  */
  // RECOIL JET -- smearing split into 2 steps:

//   ///////////////////////////// DEBUG
//   //
//   cout << "SmearHardRecoil_Method_B(1): DUMMY_RND=" << dummy->Uniform(0.,1.) << endl;
//   //
//   ///////////////////////////// DEBUG

  // 1. get "unfudged" pT and phi from Z->nunu model
  double znunu_recoil_pT = 0., znunu_recoil_phi = 0.;
  wz_utils::FlipARecoil2(raw_recoil_pT, 
			 raw_recoil_phi, 
			 znunu_recoil_pT, 
			 znunu_recoil_phi,
			 0,      // does not apply
			 0,      // does not apply
			 _scale_HAD_bifurcate_Tau,
			 0,      // does not apply
			 0,      // does not apply
			 0,      // does not apply
			 0,      // does not apply
			 0,      // does not apply
			 0,      // does not apply
			 0,      // does not apply
                         0,      // does not apply
                         0,      // does not apply
			 pt_resol_external,  // effective only when skip_Znunu_randomization=TRUE
			 delta_phi_external, // effective only when skip_Znunu_randomization=TRUE  
			 skip_Znunu_randomization, // do hard recoil randomization (when requested)
			 true );                   // but skip the fudging part
  double znunu_pt_resol = 1.0 - znunu_recoil_pT/raw_recoil_pT;
  double znunu_delta_phi = znunu_recoil_phi - raw_recoil_phi;  

//   ///////////////////////////// DEBUG
//   //
//   cout << "SmearHardRecoil_Method_B(2): generated_pT=" << raw_recoil_pT
//        << ", znunu_pT=" << znunu_recoil_pT << endl;
//   //
//   ///////////////////////////// DEBUG

  // 2. get "fudged" pT and phi
  wz_utils::FlipARecoil2(raw_recoil_pT, 
			 raw_recoil_phi, 
			 smear_recoil_pT, 
			 smear_recoil_phi,
			 Relscale_HAD_bifurcate_A, Relscale_HAD_bifurcate_B, Relscale_HAD_bifurcate_Tau, 
			 Relsampling_HAD_bifurcate_A, Relsampling_HAD_bifurcate_B, Relconst_HAD_bifurcate, 
			 Reltrans_HAD_RelRespTrans, Reltrans_HAD_RelResnTrans, Reltrans_HAD_RelTauTrans,
			 Relphi_HAD_bifurcate_A, Relphi_HAD_bifurcate_B, RelconstPhi_HAD_bifurcate,
			 znunu_pt_resol,      // use this ONE instead of random value
			 znunu_delta_phi,     // use this ONE instead of random value
			 true,                // skip hard recoil randomization
			 skip_Znunu_fudging, EtFlowFudge, instlum); // and proceed with the fudging as usual (when requested)

//   ///////////////////////////// DEBUG
//   //
//   cout << "SmearHardRecoil_Method_B(3): generated_pT=" << raw_recoil_pT
//        << ", znunu_pT=" << znunu_recoil_pT
//        << ", fudged_pT=" << smear_recoil_pT << endl;
//   //
//   ///////////////////////////// DEBUG

  _Hard_Recoil_exists=true;
  // store intermediate hard recoil vector from "Z->nu+nu" model
  _Hard_Recoil_from_Znunu_pT  = znunu_recoil_pT;
  _Hard_Recoil_from_Znunu_phi = znunu_recoil_phi;
  // store generated hard recoil vector
  _Hard_Recoil_generated_pT  = raw_recoil_pT;
  _Hard_Recoil_generated_phi = raw_recoil_phi;
  // store smeared hard recoil vector
  _Hard_Recoil_smeared_pT  = smear_recoil_pT;
  _Hard_Recoil_smeared_phi = smear_recoil_phi;

  // SCALAR ET -- smearing split into 2 steps:
  // Corresponding hard SET will be generated upon request
  // during first call to Recoil::ScalarEt_hard().
  // Here we store only paramters needed for SET fudging. 
 
  // 1. recall "unfudged" hard SET or set a flag to force
  //    generation of "unfudged" SET during next call of Recoil::ScalarEt_hard().
  _Hard_SET_expected_from_Znunu = 0.0;
  _Hard_SET_from_Znunu  = 0.0;
  if(!skip_Znunu_randomization) {
    _Hard_SET_exists = false;
//     //////////////////////////////// DEBUG
//     //
//     cout << "SmearHardRecoil_Method_B: Hard SET(unfudged) will be generated on demand later" << endl;
//     //
//     //////////////////////////////// DEBUG
  } else {
    _Hard_SET_exists = true;
    _Hard_SET_expected_from_Znunu = znunu_SET_Hard_expected_external;
    _Hard_SET_from_Znunu  = znunu_SET_Hard_external;
//     //////////////////////////////// DEBUG
//     //
//     cout << "SmearHardRecoil_Method_B: External, buffered hard SET(unfudged) = " << znunu_SET_Hard_external
//  	 << " (unfudged)" << endl;
//     //
//     //////////////////////////////// DEBUG
  }
  // 2. calculate fudging parameters for hard SET
  // response and resolution parameters are identical to that of the
  // hard recoil
  _Hard_SET_Relscale_bifurcate_A = 1.0;
  _Hard_SET_Relscale_bifurcate_B = 0.0;
  _Hard_SET_Relsampling_bifurcate_A = 1.0;
  _Hard_SET_Relsampling_bifurcate_B = 0.0;
  if(!skip_Znunu_fudging) {
    _Hard_SET_Relscale_bifurcate_A = Relscale_HAD_bifurcate_A;
    _Hard_SET_Relscale_bifurcate_B = Relscale_HAD_bifurcate_B;
    _Hard_SET_Relsampling_bifurcate_A = Relsampling_HAD_bifurcate_A;
    _Hard_SET_Relsampling_bifurcate_B = Relsampling_HAD_bifurcate_B;
  }
//   //////////////////////////////// DEBUG
//   //
//   cout << "SmearHardRecoil_Method_B: SET fudging params are now: "
//        << _Hard_SET_Relscale_bifurcate_A << ", "
//        << _Hard_SET_Relscale_bifurcate_B << ", "
//        << _Hard_SET_Relsampling_bifurcate_A << ", "
//        << _Hard_SET_Relsampling_bifurcate_B << endl;
//   //
//   //////////////////////////////// DEBUG
}

void RecoilSmear::SmearHardRecoil_Method_D(double raw_recoil_pT, 
					   double raw_recoil_phi, 
					   double Relscale_HAD_bifurcate_A, 
					   double Relscale_HAD_bifurcate_B,
                                           double Relscale_HAD_bifurcate_Tau,
					   double Relsampling_HAD_bifurcate_A, 
					   double Relsampling_HAD_bifurcate_B, 
					   double Relconst_HAD_bifurcate, 
					   double Reltrans_HAD_RelRespTrans, 
					   double Reltrans_HAD_RelResnTrans, 
					   double Reltrans_HAD_RelTauTrans,
					   double Relphi_HAD_bifurcate_A, 
					   double Relphi_HAD_bifurcate_B, 
					   double RelconstPhi_HAD_bifurcate,
					   TRandom3 *dummy, 
					   double& smear_recoil_pT, 
					   double& smear_recoil_phi,
					   double& smear_SET,
					   double pt_resol_external,  // effective only when skip_Znunu_randomization=TRUE
					   double delta_phi_external, // effective only when skip_Znunu_randomization=TRUE
					   double znunu_SET_Hard_external, // effective only when skip_Znunu_randomization=TRUE
					   double znunu_SET_Hard_expected_external, // effective only when skip_Znunu_randomization=TRUE
					   bool skip_Znunu_randomization,
					   bool skip_Znunu_fudging,
					   int EtFlowFudge,
					   double instlum) {

  if(!skip_Znunu_randomization || !hard_recoil->isFlipped()) 
    hard_recoil->FlipRecoil(raw_recoil_pT, raw_recoil_phi, RecoilSmear::scalarEt_ZB_NoScale(), _instLumi, dummy);
  if(!skip_Znunu_fudging) 
    hard_recoil->SmearRecoil(raw_recoil_pT, raw_recoil_phi, RecoilSmear::scalarEt_ZB_NoScale(), _instLumi, 
			     Relscale_HAD_bifurcate_A, 
			     Relscale_HAD_bifurcate_B,
			     Relscale_HAD_bifurcate_Tau,
			     Relsampling_HAD_bifurcate_A, 
			     Relsampling_HAD_bifurcate_B,
			     Reltrans_HAD_RelRespTrans, 
			     Reltrans_HAD_RelResnTrans, 
			     Reltrans_HAD_RelTauTrans,
			     Relphi_HAD_bifurcate_A, 
			     Relphi_HAD_bifurcate_B,
			     EtFlowFudge);
  
  smear_recoil_pT = hard_recoil->GetSmearedRecoil().Recoil();
  smear_recoil_phi = hard_recoil->GetSmearedRecoil().RecoilPhi();
  smear_SET = hard_recoil->GetSET();

  // Fill global variables - backward compatibility
  _Hard_SET_exists = true;
  _Hard_Recoil_exists=true;
  _Hard_Recoil_from_Znunu_pT  = hard_recoil->GetZnunuRecoil().Recoil();
  _Hard_Recoil_from_Znunu_phi = hard_recoil->GetZnunuRecoil().RecoilPhi();
  _Hard_Recoil_generated_pT  = raw_recoil_pT;
  _Hard_Recoil_generated_phi = raw_recoil_phi;
  _Hard_Recoil_smeared_pT  = smear_recoil_pT;
  _Hard_Recoil_smeared_phi = smear_recoil_phi;
  _Hard_SET_expected_from_Znunu = hard_recoil->GetSETexpected();
  _Hard_SET_from_Znunu  = hard_recoil->GetSET();
    
}


// retrive SET (inlucding intermediate steps)
// from the last call of SmearHardRecoil_Method_B
void RecoilSmear::GetLastHardScalarEt_Method_B(double *znunu_SET_Hard,
					       double *znunu_SET_Hard_expected,
					       double *smear_SET_Hard) {
//   ///////////////////// DEBUG
//   //
//   cout << "GetLastHardScalarEt_Method_B: Before scalarEt_hard():"
//        << " SET_exists=" << _Hard_SET_exists 
//        << ", Buffered SET(unfudged)=" << _Hard_SET_from_Znunu << endl;
//   //
//   ///////////////////// DEBUG
  // generate a fresh hard SET when necessary
  if(!_Hard_SET_exists) scalarEt_hard();
  if(znunu_SET_Hard) *znunu_SET_Hard = _Hard_SET_from_Znunu;
  if(znunu_SET_Hard_expected) *znunu_SET_Hard_expected = _Hard_SET_expected_from_Znunu;
  if(smear_SET_Hard) *smear_SET_Hard = _Hard_SET_smeared;
//   ///////////////////// DEBUG
//   //
//   cout << "GetLastHardScalarEt_Method_B: After scalarEt_hard():"
//        << " SET_exists=" << _Hard_SET_exists 
//        << ", Buffered SET(unfudged)=" << _Hard_SET_from_Znunu << endl;
//   //
//   ///////////////////// DEBUG
}
// retrive recoil vectors (inlucding generator and intermediate steps)
// from the last call of SmearHardRecoil_Method_B
void RecoilSmear::GetLastHardRecoil_Method_B(double *gen_pt,
					     double *gen_phi,
					     double *znunu_pt,
					     double *znunu_phi,
					     double *smear_pt,
					     double *smear_phi) {
  if(!_Hard_Recoil_exists) {
    cout << "GetLastHardRecoil_Method_B: Hard recoil hasn't been generated yet. Call SmearHardRecoil_Method_B first !!!" << endl;
    return;
  }
  if(gen_pt)  *gen_pt = _Hard_Recoil_generated_pT;
  if(gen_phi) *gen_phi = _Hard_Recoil_generated_phi;
  if(znunu_pt)  *znunu_pt = _Hard_Recoil_from_Znunu_pT;
  if(znunu_phi) *znunu_phi = _Hard_Recoil_from_Znunu_phi;
  if(smear_pt)  *smear_pt = _Hard_Recoil_smeared_pT;
  if(smear_phi) *smear_phi = _Hard_Recoil_smeared_phi;
}

// smear hard component
void RecoilSmear::SmearHardRecoil_Method_C(double raw_recoil_pT, double raw_recoil_phi, 
					   double scale_HAD_A, double scale_HAD_B, double scale_HAD_C, 
					   double phi_smear_true_recoil_A, double phi_smear_true_recoil_B, 
					   double constant_HAD, double sampling_HAD, 
					   TRandom3 *dummy, double& smear_recoil_pT, double& smear_recoil_phi) {
  double smear_recoil_pT_tmp = (scale_HAD_A + scale_HAD_B * TMath::Log(raw_recoil_pT) + 
	         	        scale_HAD_C * TMath::Log(raw_recoil_pT) * TMath::Log(raw_recoil_pT)) * raw_recoil_pT;
  
  // smearing true recoil direction and make sure smeared recoil phi between 0 and 2pi
  double phi_sigma = phi_smear_true_recoil_A/raw_recoil_pT + phi_smear_true_recoil_B;
  double phi_tmp = raw_recoil_phi + phi_sigma * dummy->Gaus(0., 1.);
  phi_tmp = fmod(phi_tmp, 2*TMath::Pi());
  if(phi_tmp > 2*TMath::Pi()) phi_tmp -= 2*TMath::Pi();
  else if(phi_tmp < 0.) phi_tmp += 2*TMath::Pi();
  smear_recoil_phi = phi_tmp;
  
  // smear the recoil system resolution
  double jetres = sqrt(constant_HAD*constant_HAD*raw_recoil_pT*raw_recoil_pT + 
		       sampling_HAD*sampling_HAD*raw_recoil_pT);
  double pT_tmp = smear_recoil_pT_tmp + jetres * dummy->Gaus(0., 1.);
  //while(pT_tmp < 0.) pT_tmp = smear_recoil_pT_tmp + jetres * dummy->Gaus(0., 1.);
  smear_recoil_pT = pT_tmp;

  // if smeared recoil pT is negative, then take the absolute value and change recoil phi direction
  if(pT_tmp < 0.) {
    smear_recoil_pT = -pT_tmp;

    smear_recoil_phi += TMath::Pi();
    if(smear_recoil_phi < 0.) smear_recoil_phi += 2 * TMath::Pi();
    else if(smear_recoil_phi > 2.*TMath::Pi()) smear_recoil_phi -= 2 * TMath::Pi();
  }

}

// smear soft component
void RecoilSmear::SmearSoftRecoil_Method_A(double underlying, double alpha_mb,
					   TRandom3 *dummy, double& smear_Metx, double& smear_Mety){
    smear_Metx = -1*alpha_mb*dummy->Gaus(0., 1.)*underlying;
    smear_Mety = -1*alpha_mb*dummy->Gaus(0., 1.)*underlying;
} 

// smear soft component
// read the metx vs mety distribution from minbias data, the minbias data 
// and the W/Z events have the same instantaneous luminosity profile
void RecoilSmear::SmearSoftRecoil_Method_B(TH2F *hmetxmety, double alpha_mb,
					   TRandom3 *dummy, double& smear_Metx, double& smear_Mety){
  Double_t pick_metx=0., pick_mety=0.;
  hmetxmety -> GetRandom2(pick_metx, pick_mety);
  
  smear_Metx = -1 * alpha_mb * pick_metx;
  smear_Mety = -1 * alpha_mb * pick_mety;
}

// smear soft component
// we need to make sure that W/Z events and minbias events have the same event multiplity
// not just instantaneous luminosity profile
// which means sigma*t*L_mb/(1-e^{-sigma*t*L_mb)) = 1 + sigma*t*L_w
// the effective minbias luminosity is calculated below
void RecoilSmear::SmearSoftRecoil_Method_C(double luminosity, double alpha_mb,
					   TRandom3 *dummy, double& smear_Metx, double& smear_Mety){
  double effective_mb_luminosity = _Factors_Lw_Lmb[0] + _Factors_Lw_Lmb[1]*luminosity + _Factors_Lw_Lmb[2]*pow(luminosity, 2) +
    _Factors_Lw_Lmb[3]*pow(luminosity, 3) +_Factors_Lw_Lmb[4]*pow(luminosity, 4);
    
  // determine which luminosity bin to use
  int LumiBin = -1;
  if(effective_mb_luminosity<_instlumi_bins[0]) LumiBin = 0;
  else if(effective_mb_luminosity>_instlumi_bins[_NumLumiBins-2]) LumiBin = _NumLumiBins-1;
  else {
    for(int ii=0; ii<_NumLumiBins-2; ii++){
      if((effective_mb_luminosity>_instlumi_bins[ii]) && (effective_mb_luminosity<=_instlumi_bins[ii+1])) LumiBin = ii+1;
    }
  }
  
  // randomly pick up metX and metY from the functions
  double pick_metx = metx_res_vect[LumiBin].GetRandom();
  double pick_mety = mety_res_vect[LumiBin].GetRandom();
     
  smear_Metx = -1 * alpha_mb * pick_metx;
  smear_Mety = -1 * alpha_mb * pick_mety;
} 

// smear soft component
// add minbias event and zerobias event separately
void RecoilSmear::SmearSoftRecoil_Method_D(double alpha_mb, double alpha_zb, 
					   TRandom3 *dummy, 
					   double& smear_Metx_From_MB, double& smear_Mety_From_MB, 
					   double& smear_Metx_From_ZB, double& smear_Mety_From_ZB, 	
					   double& smear_Metx, double& smear_Mety,
					   double* trueHardPhi, double alpha_mb_trans){
//   //////////////////////////////// DEBUG
//   //
//   std::cout << "SmearSoftRecoil_Method_D(1): _MBEvtIndex= " << _MBEvtIndex 
// 	    << ", ZBEvtIndex=" << _ZBEvtIndex << std::endl;
   
//   //
//   //////////////////////////////// DEBUG

  _MB_MetX = - _MBmetx[_MBEvtIndex];
  _MB_MetY = - _MBmety[_MBEvtIndex];

  // add minimum bias contribution, scaled by _alpha_mb
  smear_Metx_From_MB = -1 * sqrt(alpha_mb) * _MBmetx[_MBEvtIndex];
  smear_Mety_From_MB = -1 * sqrt(alpha_mb) * _MBmety[_MBEvtIndex];
  if (trueHardPhi) {
    double Jphi=atan2(smear_Mety_From_MB,smear_Metx_From_MB);
    if (Jphi<0) Jphi+=(2*TMath::Pi());
    double Jdphi=fabs(Jphi-*trueHardPhi);
    if (Jdphi>TMath::Pi()) Jdphi=2*TMath::Pi()-Jdphi;
    double Jlen=sqrt(smear_Metx_From_MB*smear_Metx_From_MB+smear_Mety_From_MB*smear_Mety_From_MB);
    double Jmbx=Jlen*cos(Jdphi);
    double Jmby=Jlen*sin(Jdphi);
    smear_Metx_From_MB-=(Jmbx*cos(*trueHardPhi));
    smear_Mety_From_MB-=(Jmbx*sin(*trueHardPhi));
    smear_Metx_From_MB*=alpha_mb_trans;
    smear_Mety_From_MB*=alpha_mb_trans;
    smear_Metx_From_MB+=(Jmbx*cos(*trueHardPhi));
    smear_Mety_From_MB+=(Jmbx*sin(*trueHardPhi));
  }

  // add zero bias contribution, scaled by _alpha_zb
  smear_Metx_From_ZB = -1 * sqrt(alpha_zb) * _ZBmetx[_ZBEvtIndex];
  smear_Mety_From_ZB = -1 * sqrt(alpha_zb) * _ZBmety[_ZBEvtIndex];
  
  // add minbias and zerobias contribution together
  smear_Metx = smear_Metx_From_MB + smear_Metx_From_ZB;
  smear_Mety = smear_Mety_From_MB + smear_Mety_From_ZB;
  
//   //////////////////////////////// DEBUG
//   //
//   std::cout << "SmearSoftRecoil_Method_D(2): _MBEvtIndex= " << _MBEvtIndex 
// 	    << ", ZBEvtIndex=" << _ZBEvtIndex << std::endl;
//   //
//   //////////////////////////////// DEBUG
} 

void RecoilSmear::applyUparaCorrection(vector<PMCSEMObj> &emobjs, PMCSRecoil &recoil_smear_beforeUparaCorr, 
                                       PMCSRecoil &recoil_smear_afterUparaCorr, int option) {

  // treat each EM objects as separate EM cluster and get UE+noise+pileup contributions (uparallel corrections)
  // else only take the highest pT or the two highest pT electrons
  double sum_UparaCorrX=0., sum_UparaCorrY=0.;  
  _ScalarEt_cone=0.;

  if(_merge_fsr_photons_met) {  // used as default one
    for(int iem=0; iem<emobjs.size(); iem++) {
       if(emobjs[iem].ppt() > _minimum_pT_cut) {  // only deal with em objects above some pT cut
	 // since emobjs[iem].EnergyLeakage() is the energy leakage out of the electron cone, needs to convert it to energy in the transverse plane
         // we need to subtract the underlying event contribution to EM objects first and then ADD energy leakage
         sum_UparaCorrX += (emobjs[iem].UParaCorr() - emobjs[iem].EnergyLeakage()/cosh(emobjs[iem].peta()))* cos(emobjs[iem].pphi());
         sum_UparaCorrY += (emobjs[iem].UParaCorr() - emobjs[iem].EnergyLeakage()/cosh(emobjs[iem].peta()))* sin(emobjs[iem].pphi());
	 _ScalarEt_cone += emobjs[iem].UParaCorr()  - emobjs[iem].EnergyLeakage()/cosh(emobjs[iem].peta())  ;
       }
    }
  } else {
   
    // otherwise we will only correct for the high pT electron(s) for W and Z events
    // there are some Z events without two high pT electrons and will be throw away later anyway
    // there are some W events without one high pT electron and will be throw away later anyway
    if(option == 0) {  // for Z bosons, need to deal with two electrons
      if(emobjs.size()>=2) {
	sum_UparaCorrX += (emobjs[0].UParaCorr() - emobjs[0].EnergyLeakage()/cosh(emobjs[0].peta()))* cos(emobjs[0].pphi());
	sum_UparaCorrX += (emobjs[1].UParaCorr() - emobjs[1].EnergyLeakage()/cosh(emobjs[1].peta()))* cos(emobjs[1].pphi());
	sum_UparaCorrY += (emobjs[0].UParaCorr() - emobjs[0].EnergyLeakage()/cosh(emobjs[0].peta()))* sin(emobjs[0].pphi());
	sum_UparaCorrY += (emobjs[1].UParaCorr() - emobjs[1].EnergyLeakage()/cosh(emobjs[1].peta()))* sin(emobjs[1].pphi());
	_ScalarEt_cone += emobjs[0].UParaCorr()  - emobjs[0].EnergyLeakage()/cosh(emobjs[0].peta())  ;
	_ScalarEt_cone += emobjs[1].UParaCorr()  - emobjs[1].EnergyLeakage()/cosh(emobjs[1].peta()) ;
	if (emobjs[0].UParaCorr() < 0)
	  std::cout << " RecoilSmear::applyUparaCorrection this should be positive:emobjs[0].UParaCorr() " <<  emobjs[0].UParaCorr() << std::endl;
	if (emobjs[1].UParaCorr() < 0)
	  std::cout << " RecoilSmear::applyUparaCorrection this should be positive:emobjs[0].UParaCorr() " <<  emobjs[0].UParaCorr() << std::endl;
	if (emobjs[0].EnergyLeakage()/cosh(emobjs[0].peta()) < 0)
	  std::cout << " RecoilSmear::applyUparaCorrection this should be positive:emobjs[0].EnergyLeakage()/cosh(emobjs[0].peta()) " << emobjs[0].EnergyLeakage()<< " / " << cosh(emobjs[0].peta()) << std::endl;
	if (emobjs[0].EnergyLeakage()/cosh(emobjs[0].peta()) < 0)
	  std::cout << " RecoilSmear::applyUparaCorrection this should be positive:emobjs[0].EnergyLeakage()/cosh(emobjs[0].peta()) " << emobjs[0].EnergyLeakage()<< " / " << cosh(emobjs[0].peta()) << std::endl;
	
      }
    } else if(option == 1) {  // for W bosons, need to deal with only one electron
      if(emobjs.size()>=1) {
	sum_UparaCorrX += (emobjs[0].UParaCorr() - emobjs[0].EnergyLeakage()/cosh(emobjs[0].peta()))* cos(emobjs[0].pphi());
	sum_UparaCorrY += (emobjs[0].UParaCorr() - emobjs[0].EnergyLeakage()/cosh(emobjs[0].peta()))* sin(emobjs[0].pphi());
	_ScalarEt_cone += emobjs[0].UParaCorr()  - emobjs[0].EnergyLeakage()/cosh(emobjs[0].peta())  ;
      }
    } else {
      cout<<"No such option for UparaCorrection"<<endl;
    }
  } // merge_fsr_photons_met
  
  // correct for uparallel 
  double new_recoilX = recoil_smear_beforeUparaCorr.Recoilx() - sum_UparaCorrX;
  double new_recoilY = recoil_smear_beforeUparaCorr.Recoily() - sum_UparaCorrY;
  // get recoil system vector after uparallel correction
  recoil_smear_afterUparaCorr.SetRecoil(new_recoilX, new_recoilY);

  // update the UPara and UPerp assigned to each EMObj
  TVector2 v2ut(new_recoilX, new_recoilY);
  for (int iem=0; iem<emobjs.size(); iem++){
    TVector2 v2el(emobjs[iem].ppx(), emobjs[iem].ppy());
    double upara = v2ut*v2el.Unit();
    double uperp = v2ut*(v2el.Unit().Rotate(TMath::Pi()/2.0));
    emobjs[iem].SetUPara(upara);
    emobjs[iem].SetUPerp(uperp);
  }
  return;
}

void RecoilSmear::fillSmearHistograms(PMCSRecoil &gen, PMCSRecoil &smear) {
  _histos->Fill1D("h_smearedRecoil_DeltaX", smear.Recoilx() - gen.Recoilx());
  _histos->Fill1D("h_smearedRecoil_DeltaY",smear.Recoily() - gen.Recoily());
  _histos->Fill1D("h_smearedRecoil_DeltaPhi",kinem::delta_phi(smear.RecoilPhi(),gen.RecoilPhi()));

  _histos->Fill2D("h_smearedRecoil_DeltaX_v_X",gen.Recoilx(),smear.Recoilx() - gen.Recoilx());
  _histos->Fill2D("h_smearedRecoil_DeltaY_v_Y",gen.Recoily(),smear.Recoily() - gen.Recoily());
  _histos->Fill2D("h_smearedRecoil_DeltaPhi_v_Phi",gen.RecoilPhi(),kinem::delta_phi(smear.RecoilPhi(),gen.RecoilPhi()));

  _histos->Fill2D("h_smearedRecoil_GenX_v_SmearX",gen.Recoilx(),smear.Recoilx());
  _histos->Fill2D("h_smearedRecoil_GenY_v_SmearY",gen.Recoily(),smear.Recoily());
  _histos->Fill2D("h_smearedRecoil_GenPhi_v_SmearPhi",gen.RecoilPhi(),smear.RecoilPhi());
}

void RecoilSmear::ApplyTopBottomAsym(double& recoilx, double& recoily){
  // debug
  //std::cout << " -- TB Previous : comes here " << std::endl;
  _recoilx_beforeTB=recoilx;
  _recoily_beforeTB=recoily;
  TVector2 RecoilVec(recoilx,recoily);
  TVector2 DistortionVec;
  DistortionVec.SetMagPhi(_TB_alpha*RecoilVec.Mod(),_TB_beta+TMath::Pi()/2.);
  RecoilVec+=DistortionVec;
  recoilx = RecoilVec.Px();
  recoily = RecoilVec.Py();
}

void RecoilSmear::ApplyTopBottomAsym_B(double& recoilx, double& recoily, bool save /*=true*/)
{
  ///////////// debug ///////////
  // std::cout << " -- RecoilSmear::ApplyTopBottomAsym_B() : comes here " << std::endl;
  ///////////////////////////////

  double given_tbdmetx, given_tbdmety;

  // store recoilx and recoily before TB correction.
  _recoilx_beforeTB=recoilx;
  _recoily_beforeTB=recoily;

  // define TB correction vector tbdmetx:tbdmety
  double tbdmetx(0), tbdmety(0);
  // flag: if TB correction vector is sucessfully got from from TB Library
  bool gotfromtblib(false);

  // reference SET, Phi and Met to get the corresponding 2D-Hist 
  // of TB correction vector (dmetx, dmety)
  double tbrefset(0), tbrefphi(0), tbrefmet(0);
  
  // Note: binning in reference SET, Phi and Met are hardcoded below!
  // nbins in reference SET, Phi, and Met
  const int tbnbinsset(5), tbnbinsphi(10), tbnbinsmet(10);
  // binning range in reference SET, Phi, and Met
  const double tbrefsetmin(0.), tbrefsetmax(200.),
    tbrefphimin(0.), tbrefphimax(2.*TMath::Pi()),
    tbrefmetmin(0.), tbrefmetmax(20.);
  
  // calculate the 3 reference variables
  tbrefset = scalarEt_MB() + scalarEt_ZB();
  tbrefphi = TVector2(-recoilx, -recoily).Phi(); // Phi is of Met (not recoil), thus I flip the sign.  
  tbrefmet = sqrt(recoilx*recoilx+recoily*recoily);
  
  // get the 3 reference flags
  int itb = int(tbrefset/((tbrefsetmax-tbrefsetmin)/tbnbinsset));
  int jtb = int(tbrefphi/((tbrefphimax-tbrefphimin)/tbnbinsphi));
  int ktb = int(tbrefmet/((tbrefmetmax-tbrefmetmin)/tbnbinsmet));

  if (itb > 4) {
    //    std::cout << "ERROR: SET index too large, setting to maximum " << itb << " " << tbrefset << std::endl;
    itb = 4;
  }

  if (jtb > 9) {
    //    std::cout << "ERROR: PHI index too large, setting to maximum " << jtb << " " << tbrefphi << std::endl;
    jtb = 9;
  }

  if (ktb > 9) {
    //    std::cout << "ERROR: MET index too large, setting to maximum " << ktb << " " << tbrefmet << std::endl;
    ktb = 9;
  }

  if (itb < 0) {
    //    std::cout << "ERROR: SET index too small, setting to minimum " << itb << " " << tbrefset << std::endl;
    itb = 0;
  }

  if (jtb < 0) {
    //    std::cout << "ERROR: PHI index too small, setting to minimum " << jtb << " " << tbrefphi << std::endl;
    jtb = 0;
  }

  if (ktb < 0) {
    //    std::cout << "ERROR: MET index too small, setting to minimum " << ktb << " " << tbrefmet << std::endl;
    ktb = 0;
  }
  
  // get the 2D-Hist of TB correction vector
  std::stringstream tbhname;
  tbhname << "hdmet2d_" << itb << "_" << jtb << "_" << ktb;
  TH2D* tbhdmet = _tblib[tbhname.str()];
  
  // randomly get the TB correction vector from the corresponding 2D-Hist
  if (tbhdmet>0) {
    tbhdmet->GetRandom2(tbdmetx, tbdmety);
    // write TB correction to the given_tbdmetx:given_tbdmety
    given_tbdmetx = tbdmetx;
    given_tbdmety = tbdmety;   
  } 
  else {
    given_tbdmetx = 0;
    given_tbdmety = 0;
  }

  if(save){
    _tbdmetx[itb][jtb][ktb] = given_tbdmetx;
    _tbdmety[itb][jtb][ktb] = given_tbdmety;
    _Top_Bottom_exists[itb][jtb][ktb] = true;
    _last_tb_exists = true;
    _last_tbdmetx = given_tbdmetx;
    _last_tbdmety = given_tbdmety;
  }

  recoilx-=given_tbdmetx;
  recoily-=given_tbdmety;

}

// To be called in ZAnalysis::ZHadronicRecoilBifurcateStudy()
// for templates generation of Hardronic parameters fitting.
void RecoilSmear::GetLastTopBottomAsym_B(double& recoilx, double& recoily){

  // reference SET, Phi and Met to get the corresponding 2D-Hist 
  // of TB correction vector (dmetx, dmety)
  double tbrefset(0), tbrefphi(0), tbrefmet(0);
  
  // Note: binning in reference SET, Phi and Met are hardcoded below!
  // nbins in reference SET, Phi, and Met
  const int tbnbinsset(5), tbnbinsphi(10), tbnbinsmet(10);
  // binning range in reference SET, Phi, and Met
  const double tbrefsetmin(0.), tbrefsetmax(200.),
    tbrefphimin(0.), tbrefphimax(2.*TMath::Pi()),
    tbrefmetmin(0.), tbrefmetmax(20.);
  
  // calculate the 3 reference variables
  tbrefset = scalarEt_MB() + scalarEt_ZB();
  tbrefphi = TVector2(-recoilx, -recoily).Phi(); // Phi is of Met (not recoil), thus I flip the sign.  
  tbrefmet = sqrt(recoilx*recoilx+recoily*recoily);
  
  // get the 3 reference flags
  int itb = int(tbrefset/((tbrefsetmax-tbrefsetmin)/tbnbinsset));
  int jtb = int(tbrefphi/((tbrefphimax-tbrefphimin)/tbnbinsphi));
  int ktb = int(tbrefmet/((tbrefmetmax-tbrefmetmin)/tbnbinsmet));

  if (itb > 4) {
    //    std::cout << "ERROR: SET index too large, setting to maximum " << itb << " " << tbrefset << std::endl;
    itb = 4;
  }

  if (jtb > 9) {
    //    std::cout << "ERROR: PHI index too large, setting to maximum " << jtb << " " << tbrefphi << std::endl;
    jtb = 9;
  }

  if (ktb > 9) {
    //    std::cout << "ERROR: MET index too large, setting to maximum " << ktb << " " << tbrefmet << std::endl;
    ktb = 9;
  }

  if (itb < 0) {
    //    std::cout << "ERROR: SET index too small, setting to minimum " << itb << " " << tbrefset << std::endl;
    itb = 0;
  }

  if (jtb < 0) {
    //    std::cout << "ERROR: PHI index too small, setting to minimum " << jtb << " " << tbrefphi << std::endl;
    jtb = 0;
  }

  if (ktb < 0) {
    //    std::cout << "ERROR: MET index too small, setting to minimum " << ktb << " " << tbrefmet << std::endl;
    ktb = 0;
  }

  if(!_Top_Bottom_exists[itb][jtb][ktb]){
    ApplyTopBottomAsym_B(recoilx, recoily);    
  } else {
    recoilx -= _tbdmetx[itb][jtb][ktb];
    recoily -= _tbdmety[itb][jtb][ktb];
  }

}
