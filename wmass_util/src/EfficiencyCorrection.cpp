#include "wmass_util/EfficiencyCorrection.hpp"
#include "wmass_util/PHistoTools.hpp"
#include "cafe/Config.hpp"
#include <iostream>
#include <TMath.h>
#include <TROOT.h>

using namespace cafe;
using namespace std;

EfficiencyCorrection::EfficiencyCorrection(const char *name){
  cout << "Efficiency Correction: Started" << endl;
 
  Config config(name);
  
  std::cout << "CAFRatioMethod EfficiencyCorrection: Config(name) passed OK " << std::endl;
  
  _debugLevel = config.get("debugLevel", 16);
  
  // preselection efficiency
  if (!gROOT->FindObject("PreSelEffDetEta")){
    TString preseleff_filename(config.get("preseff_file","file"));
    gROOT->ProcessLine(TString(".x ")+preseleff_filename);
  }
  _hPreselEff = (TH1F *)gROOT->FindObject("PreSelEffDetEta");
    
    
  // EMID efficiency
  TString ideff_filename(config.get("ideff_file","file"));
  if (!gROOT->FindObject("idEffDetEta")){
    gROOT->ProcessLine(TString(".x ")+ideff_filename);
  }
  _hEMIDEff = (TH1F *)gROOT->FindObject("idEffDetEta");
  
  
  // get phi crack efficiency
  if (!gROOT->FindObject("hPhiCrackEff")){
    TString phicrackeff_filename(config.get("phicrackeff_file","file"));
    gROOT->ProcessLine(TString(".x ")+phicrackeff_filename);
  }
  _hPhiCrackEff = (TH1F *)gROOT->FindObject("hPhiCrackEff");  
  
  _simulate_pT_dependence = config.get("simulate_pT_dependence", 0);
  if(_simulate_pT_dependence) cout << "Simulate pT dependence for CC region"<<endl;
  
  _correctE = config.get("correctE",1);
  _correctNu = config.get("correctNu",1);
  _CCideff_pTphyEta_ParameterA = config.getVFloat("CCideff_pTphyEta_ParameterA");
  _CCideff_pTphyEta_ParameterB = config.getVFloat("CCideff_pTphyEta_ParameterB");
  _CCtrkeff_pTphyEta_ParameterA = config.getVFloat("CCtrkeff_pTphyEta_ParameterA");
  _CCtrkeff_pTphyEta_ParameterB = config.getVFloat("CCtrkeff_pTphyEta_ParameterB");
  _CorrectTriggerEff = config.get("CorrectTriggerEff",1);
  _CorrectTrkEff = config.get("CorrectTrkEff",1);
  _CorrectEMIDEff = config.get("CorrectEMIDEff",1);
  _CorrectPreselEff = config.get("CorrectPreselEff",1);


  // uparallel efficiency correction
  
  _ZUparaEffCorrection = config.get("ZUParaEffCorrection", kTRUE);
  _UparaEffCorrOption = config.get("UParaEffCorrOption", 1);
  _ZUparaEffParameters = config.getVFloat("ZUparaEffCorrParameters_CC");

  _Z_u0_CC = config.get("Z_u0_CC", 3.29440);
  _Z_s_CC = config.get("Z_s_CC", 0.001787);
  _Z_u0_EC = config.get("Z_u0_EC", 2.308);
  _Z_s_EC = config.get("Z_s_EC", 0.0046);
  
  // Uparallel efficiency correction
  
  _WUparaEffCorrection = config.get("WUParaEffCorrection", kTRUE);
  _WUparaEffCorrOption = config.get("WUParaEffCorrOption", 1);
  _WUparaEffParameters = config.getVFloat("WUparaEffCorrParameters_CC");
  
  _W_u0_CC = config.get("W_u0_CC", 2.57375);
  _W_s_CC = config.get("W_s_CC", 0.002841);
  _W_u0_EC = config.get("W_u0_EC", 2.308);
  _W_s_EC = config.get("W_s_EC", 0.0046);
  _W_seta_CC =  config.get("W_seta_CC", 0.0046);
  _etaCC = config.get("etaCC", 1.05);
  
  Double_t TrigFrac_ListOne, TrigFrac_ListTwo, TrigFrac_ListThree, TrigFrac_ListFour;
  std::vector<float> TrigEff_P0, TrigEff_P1, TrigEff_P2, TrigEff_P3, TrigEff_P4;
  TrigEff_P0 = config.getVFloat("TrigEff_P0");
  TrigEff_P1 = config.getVFloat("TrigEff_P1");
  TrigEff_P2 = config.getVFloat("TrigEff_P2");
  TrigEff_P3 = config.getVFloat("TrigEff_P3");
  TrigEff_P4 = config.getVFloat("TrigEff_P4");
  
  TrigFrac_ListOne = config.get("TrigFrac_ListOne",0.25);
  TrigFrac_ListTwo = config.get("TrigFrac_ListTwo",0.25);
  TrigFrac_ListThree = config.get("TrigFrac_ListThree",0.25);
  TrigFrac_ListFour = config.get("TrigFrac_ListFour",0.25);

  _TriggerNames.push_back("ListOne");
  _TriggerNames.push_back("ListTwo");
  _TriggerNames.push_back("ListThree");
  _TriggerNames.push_back("ListFour");
  _ApplyPhiModEfficiency = config.get("PhiModEfficiency",1.);
  
  for (Int_t i =0; i < _TriggerNames.size(); i++){
    std::vector<double> TriggerVec;
    TriggerVec.push_back(TrigFrac_ListOne*((double)(i>-1)) +  TrigFrac_ListTwo*((double)(i>0)) + TrigFrac_ListThree*((double)(i>1)));
    TriggerVec.push_back(TrigEff_P0[i]);
    TriggerVec.push_back(TrigEff_P1[i]);
    TriggerVec.push_back(TrigEff_P2[i]); 
    TriggerVec.push_back(TrigEff_P3[i]); 
    TriggerVec.push_back(TrigEff_P4[i]); 
    
    _TriggerParams[_TriggerNames[i]] = TriggerVec;
  }

  if (_debugLevel > 15){
    cout << " Parameters in EfficiencyCorrection: " << endl;
    for (Int_t i =0; i < _TriggerNames.size(); i++){
      std::cout << " Trigger Name " <<  _TriggerNames[i] << std::endl;
      std::cout << " Trigger Fraction Sum   " << _TriggerParams[_TriggerNames[i]].at(0)  <<  std::endl;
      std::cout << " TrigEff_P0  " << _TriggerParams[_TriggerNames[i]].at(1) <<   std::endl;
      std::cout << "TrigEff_P1   " << _TriggerParams[_TriggerNames[i]].at(2) <<    std::endl;
      std::cout << "TrigEff_P2   " << _TriggerParams[_TriggerNames[i]].at(3) <<    std::endl;
      std::cout << "TrigEff_P3   " << _TriggerParams[_TriggerNames[i]].at(4) <<    std::endl;
      std::cout << "TrigEff_P4   " << _TriggerParams[_TriggerNames[i]].at(5) <<    std::endl;
    }
      
    std::cout << "_hPreselEff                      " << _hPreselEff->GetName() << endl; 
    std::cout << "_hEMIDEff                        " << _hEMIDEff->GetName() << endl; 
    std::cout << "_hPhiCrackEff                    " << _hPhiCrackEff->GetName() << endl; 
    std::cout << "_simulate_pT_dependence          " << _simulate_pT_dependence << endl; 
    for (Int_t printi =0; printi <  _CCideff_pTphyEta_ParameterA.size() ; ++printi){
      std::cout << "_CCideff_pTphyEta_ParameterA " << printi << "  " << _CCideff_pTphyEta_ParameterA.at(printi) << endl; 
    }
    for (Int_t printi =0; printi <  _CCideff_pTphyEta_ParameterB.size() ; ++printi){
      std::cout << "_CCideff_pTphyEta_ParameterB " << printi << "  " << _CCideff_pTphyEta_ParameterB.at(printi) << endl;
    } 
    for (Int_t printi =0; printi <  _CCtrkeff_pTphyEta_ParameterA.size() ; ++printi){
      std::cout << " _CCtrkeff_pTphyEta_ParameterA   "  << printi << "  "<<  _CCtrkeff_pTphyEta_ParameterA.at(printi) << endl;
    }
    for (Int_t printi =0; printi <  _CCtrkeff_pTphyEta_ParameterB.size() ; ++printi){
      std::cout << "_CCtrkeff_pTphyEta_ParameterB    "  << printi << "  "<< _CCtrkeff_pTphyEta_ParameterB.at(printi) << endl; 
    }
    std::cout << " _CorrectTriggerEff              " <<  _CorrectTriggerEff << endl; 
    std::cout << " _CorrectTrkEff                  " <<  _CorrectTrkEff << endl; 
    std::cout << " _CorrectEMIDEff                 " <<  _CorrectEMIDEff << endl; 
    std::cout << " _CorrectPreselEff               " <<  _CorrectPreselEff << endl; 
    std::cout << " _ZUparaEffCorrection            " <<  _ZUparaEffCorrection << endl; 
    std::cout << "  _ApplyPhiModEfficiency         " <<    _ApplyPhiModEfficiency << endl; 
    std::cout << " _UparaEffCorrOption             " <<  _UparaEffCorrOption  << endl;  
    for (Int_t printi =0; printi < _ZUparaEffParameters.size() ; ++printi){
      std::cout << " _ZUparaEffParameters            " << printi << "  " << _ZUparaEffParameters.at(printi)  << endl; 
    }
    std::cout << " _Z_u0_CC                        " << _Z_u0_CC << endl; 
    std::cout << " _Z_s_CC                         " << _Z_s_CC << endl; 
    std::cout << " _Z_u0_EC                        " << _Z_u0_EC << endl; 
    std::cout << " _Z_s_EC                         " << _Z_s_EC << endl; 
    std::cout << " _WUparaEffCorrection            " << _WUparaEffCorrection << endl; 
    std::cout << " _UparaEffCorrOption             " << _UparaEffCorrOption << endl; 
    for (Int_t printi =0; printi <  _WUparaEffParameters.size() ; ++printi){
      std::cout << " _WUparaEffParameters          " << printi  << " " << _WUparaEffParameters.at(printi) << endl; 
    }
    std::cout << "  _W_u0_CC                       " << _W_u0_CC << endl; 
    std::cout << " _W_s_CC                         " << _W_s_CC << endl; 
    std::cout << " _W_u0_EC                        " << _W_u0_EC << endl; 
    std::cout << " _W_s_EC                         " << _W_s_EC << endl; 
    std::cout << " _etaCC                        " << _etaCC << endl; 
    std::cout << " _E_seta_CC                         " << _W_seta_CC << endl; 
    std::cout << " _correctE                        " << _correctE << endl; 
    std::cout << " _correctNu                         " << _correctNu << endl; 
  }
    
}

EfficiencyCorrection::~EfficiencyCorrection(){;}



Double_t EfficiencyCorrection::FullEfficiencyCorrection(Double_t TrigVer, Double_t pt_orig_e, Double_t pt_orig_nu, Double_t pt_new_e,  Double_t deteta_e, Double_t deteta_nu, Double_t peta_e, Double_t peta_nu,Double_t detphi_nu,  Double_t upara_e, Double_t upara_nu){
  Double_t effelec = 1.;
  Double_t effnu = 1.;
  if (_correctNu){
    effnu = effnu*passesPreselEff(deteta_nu)*passesEMIDEff(deteta_nu,pt_orig_nu)*ZpassesUParaEff(upara_nu, deteta_nu)* passesPhiCrackEff(detphi_nu, deteta_nu);
    effnu = 1./ effnu;
    
  }
  //std::cout << passesPreselEff(deteta_nu)<< "   " <<passesEMIDEff(deteta_nu,pt_orig_nu)<< "   " <<ZpassesUParaEff(upara_nu, deteta_nu)<< "   " << passesPhiCrackEff(detphi_nu, deteta_nu) << std::endl;
  //std::cout << " effnu = " << effnu << std::endl;
  if (_correctE){
    effelec = effelec*EMIDEffCorrection(deteta_e, pt_orig_e, pt_new_e)*TrigEffCorrection(TrigVer,pt_orig_e,pt_new_e)*TrkEffCorrection(deteta_e, pt_orig_e,pt_new_e)*(WpassesUParaEff(upara_e, deteta_e, peta_e) /   ZpassesUParaEff(upara_e, deteta_e));
  }
  if (_debugLevel > 15)
    std::cout << " effelec = " << effelec << "    " << TrigEffCorrection(TrigVer,pt_orig_e,pt_new_e) << "    " << effelec*effnu <<  std::endl;
  return (effelec*effnu);

  
}


//Preselection efficiency (vs deteta)
Double_t EfficiencyCorrection::passesPreselEff(Double_t  deteta) {  
  if (!_CorrectPreselEff){
    return 1.;
  }
  double val=1., err=0.;
  Bool_t status = PHistoTools::getBinValues(_hPreselEff, deteta, val, err);  
  if (val < 0){
    return 0.;
  }
  else if (val > 1.){
    return 1.;
  }
  else {
    return val;
  }   
}//passesPreselEff(

Double_t EfficiencyCorrection::EMIDEffCorrection(Double_t deteta, Double_t pt_orig, Double_t pt_new) { 
  double val = passesEMIDEff(deteta,pt_new) / passesEMIDEff(deteta,pt_orig);
  if (!(val==1) && !(_simulate_pT_dependence)){
    std::cout << "EMIDeff Correction should be unity" << std::endl;
  }
  return val;
}

Double_t EfficiencyCorrection::passesEMIDEff(Double_t deteta, Double_t pt) {
  if (_debugLevel > 15)
    std::cout << "EMID eff" << std::endl;
  if (!_CorrectEMIDEff){
    return 1.;
  }
  double val=1., err=0.;
  Bool_t status = PHistoTools::getBinValues(_hEMIDEff, deteta, val, err); 
  
  if(_simulate_pT_dependence && fabs(deteta)<1.1) {   // for CC and _simulate_pT_dependence = true
    //cout << " correcting EMIDEFF pT Dependance" << endl;
    // overwrite val to use new efficiency for CC region
    int eta_region = PhyEtaRegion_CC(deteta); 
    val = _CCideff_pTphyEta_ParameterA[eta_region] + _CCideff_pTphyEta_ParameterB[eta_region] * TMath::Log(pt);
  }
  if (val < 0){
    return 0.;
  }
  else if (val > 1.){
    return 1.;
  }
  else {
    return val;
  }  
  
}//passesEMIDEff()


Double_t EfficiencyCorrection::TrigEffCorrection(Double_t TrigVer, Double_t pt_orig, Double_t pt_new) 
{  
  if (_debugLevel > 15)
    std::cout << "Trig Eff" << std::endl;
  
  if (_CorrectTriggerEff && TrigVer > 0.){
    Double_t Prob =-1.;
    for (Int_t i =0; i < _TriggerNames.size(); i++){
      if (Prob == -1.){
	if ( TrigVer < (_TriggerParams[_TriggerNames[i]].at(0))){
	  Prob = (0.5 * _TriggerParams[_TriggerNames[i]].at(3) * (1.+ TMath::Erf(((pt_new)-_TriggerParams[_TriggerNames[i]].at(1))/(TMath::Sqrt(2)*_TriggerParams[_TriggerNames[i]].at(2))))*(1.+ TMath::Erf(((pt_new)-_TriggerParams[_TriggerNames[i]].at(5))/(TMath::Sqrt(2)*_TriggerParams[_TriggerNames[i]].at(4))))) /
	    (0.5 * _TriggerParams[_TriggerNames[i]].at(3) * (1.+ TMath::Erf(((pt_orig)-_TriggerParams[_TriggerNames[i]].at(1))/(TMath::Sqrt(2)*_TriggerParams[_TriggerNames[i]].at(2))))*(1.+ TMath::Erf(((pt_orig)-_TriggerParams[_TriggerNames[i]].at(5))/(TMath::Sqrt(2)*_TriggerParams[_TriggerNames[i]].at(4))))    ); 
	}
      }
    }
    if (Prob == -1){
      return 1.;
    }
    else if ((Prob >= 0.) && (Prob <=1.)){
      return Prob;
    }
    else if (Prob < 0.){
      return 0.;
    }
    else{      
      return 1.;
    }
  }
  else {
    return 1.;
  }
}


Double_t EfficiencyCorrection::TrkEffCorrection(Double_t eta, Double_t pt_orig, Double_t pt_new){ 
  if (_debugLevel > 15)
    std::cout << "Trk Eff" << std::endl;
  if (!_CorrectTrkEff){
    return 1.;
  }
  if(_simulate_pT_dependence && fabs(eta)<1.1) {   // for CC region and _simulate_pT_dependence = true
    int eta_region = PhyEtaRegion_CC(eta);    
    // make sure we have 98% efficiency for pT=45 GeV for each eta region
    // this is just kind of normalization to avoid double counting inefficiencies
    double eff_45 = _CCtrkeff_pTphyEta_ParameterA[eta_region] + _CCtrkeff_pTphyEta_ParameterB[eta_region] * TMath::Log(45.);
    Double_t val = ((_CCtrkeff_pTphyEta_ParameterA[eta_region] + _CCtrkeff_pTphyEta_ParameterB[eta_region] * TMath::Log(pt_orig)) * 0.98/eff_45) / ((_CCtrkeff_pTphyEta_ParameterA[eta_region] + _CCtrkeff_pTphyEta_ParameterB[eta_region] * TMath::Log(pt_new)) * 0.98/eff_45) ; 
    if (val < 0){
      return 0.;
    }
    else if (val > 1.){
      return 1.;
    }
    else {
      return val;
    }
  }
  else{
    return 1.;
  }
}




Double_t EfficiencyCorrection::WpassesUParaEff(Double_t upara, Double_t deteta, Double_t peta ){
  if (_debugLevel > 15)
    std::cout << " PassesW" << std::endl;
  if (!(_ZUparaEffCorrection && _WUparaEffCorrection)){
    return 1.;
  }
  Double_t val =1.;
  // calculate uparallel efficiency for CC and EC regions
    if(_WUparaEffCorrOption == 0) { // for _UparaEffCorrOption==0
      if(upara<_W_u0_CC) val = 1.;	    
      else val = 1. - _W_s_CC*(upara - _W_u0_CC);
    } else if (_WUparaEffCorrOption == 1) { // for _UparaEffCorrOption!=0, use a second order polynomial function
      val = _WUparaEffParameters[0] + _WUparaEffParameters[1] * upara + 
	_WUparaEffParameters[2] * upara * upara;
    } else if (_WUparaEffCorrOption == 2) { //use slope of slope
      if(upara<_W_u0_CC) val = 1.;
      else val = 1. - ( _W_s_CC + _W_seta_CC*fabs(peta) )*(upara - _W_u0_CC);
    } 
   
  if (val < 0){
    return 0.;
  }
  else if (val > 1.){
    return 1.;
  }
  else {
    return val;
  }  
}

Double_t  EfficiencyCorrection::ZpassesUParaEff(Double_t upara, Double_t deteta ){
  if (!(_ZUparaEffCorrection && _WUparaEffCorrection)){
    return 1.;
  }
  double val= 1.;
  // calculate uparallel efficiency for CC and EC regions
  if(TMath::Abs(deteta) < _etaCC){
    if(_UparaEffCorrOption == 0) {
      if(upara<_Z_u0_CC) val = 1.;
      else val = 1. - _Z_s_CC*(upara - _Z_u0_CC);
    } else { // for _ZUparaEffCorrOption!=0, used for real data, two linear functions
      if(upara < _ZUparaEffParameters[0])
	val = 1. - _ZUparaEffParameters[1] * (upara - _ZUparaEffParameters[0]);
      else
	val = 1. - _ZUparaEffParameters[2] * (upara - _ZUparaEffParameters[0]);
    }
  } else{
    if(upara<_Z_u0_EC) val = 1.;
    else val = 1. - _Z_s_EC*(upara - _Z_u0_EC);
  }
  
  if (val < 0){
    return 0.;
  }
  else if (val > 1.){
    return 1.;
  }
  else {
    return val;
  } 
}


Double_t EfficiencyCorrection::passesPhiCrackEff(Double_t detphi, Double_t deteta) {
  if (!_ApplyPhiModEfficiency){
    return 1.;
  }
  if (fabs(deteta) < 1.3){
    //does not currently correct for phimod shift correction
    double val=1., err=0.;
    double phifrac = fmod(detphi*16./TMath::Pi(), 1.0);
    Bool_t status = PHistoTools::getBinValues(_hPhiCrackEff, phifrac, val, err);
    if (val < 0){
      return 0.;
    }
    else if (val > 1.){
      return 1.;
    }
    else {
      return val;
    } 
  }
  else{
    return 1.;
  }
}//passesPhiCrackEff()

int EfficiencyCorrection::PhyEtaRegion_CC(double eta) {
  if(eta<-1.1) return 0;
  else if (eta<-0.9) return 1;
  else if (eta<-0.7) return 2;
  else if (eta<-0.5) return 3;
  else if (eta<-0.3) return 4;
  else if (eta<-0.1) return 5;
  else if (eta<0.1) return 6;
  else if (eta<0.3) return 7;
  else if (eta<0.5) return 8;
  else if (eta<0.7) return 9;
  else if (eta<0.9) return 10;
  else if (eta<1.1) return 11;
  else return 12;
}
