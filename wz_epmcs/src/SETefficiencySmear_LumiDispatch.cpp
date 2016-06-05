#include "SETefficiencySmear_LumiDispatch.hpp"
#include <iostream>
#include <cassert>

using namespace std;

// constructor
SETefficiencySmear_LumiDispatch::SETefficiencySmear_LumiDispatch(TString parameter_filename, bool isW, std::vector<float>* lumibins, std::vector<float>* luminorm, std::vector<float>* luminorm2, std::vector<float>* luminorm3) {

  _isW=isW;

  assert((lumibins->size()+1)==luminorm->size());
  for (int i=0; i<lumibins->size(); i++) _lumibins.push_back(lumibins->at(i));
  if (_isW) {
    for (int i=0; i<luminorm->size(); i++) _luminorm.push_back(luminorm->at(i));
  } else {
    for (int i=0; i<luminorm->size(); i++) _luminormCCCC.push_back(luminorm->at(i));
    for (int i=0; i<luminorm2->size(); i++) _luminormCCEC.push_back(luminorm2->at(i));
    for (int i=0; i<luminorm3->size(); i++) _luminormECEC.push_back(luminorm3->at(i));
  }

  PParameterReader parm(parameter_filename.Data());

  if (_isW) {
    // lumi-independent part
    bool WSETEffCorrScaled = parm.GetBool("WSETEffCorrScaled", kFALSE);
    bool WSETEffCorrRelative = parm.GetBool("WSETEffCorrRelative", kFALSE);
    float WSETEffCorrScale=200.;
    if (WSETEffCorrRelative) WSETEffCorrScale=20.;
    bool WSETEffCorrInterpolate = parm.GetBool("WSETEffCorrInterpolate", kFALSE);
    int WSETEffCorrPTEpert = parm.GetInt("WSETEffCorrPTEpert", 0);
    // parameters for the data hack (also lumi-independent in the sense that we give the same set of parameter values to all workers)
    std::vector< std::vector< std::vector<float> > > WSETEffCorrDataRatioParameters;
    std::vector< std::vector< std::vector<float> > > WSETEffCorrDataRatioParameters2;
    std::vector< std::vector<float> > WSETEffDataHackParameters;
    std::vector<float> WSETEffCorrDataRatioPTFit;
    std::vector<float> WSETEffCorrDataRatioLumiFit;
    int useHack = parm.GetInt("SETuseHack");
    bool useLumiBins = parm.GetBool("SETuseLumiBins");
    char name[100];
    if (useHack) {
      if (useHack<=2) {
	for (Int_t tv=0; tv<7; ++tv){
	  std::vector< std::vector<float> > tempvec;
	  std::vector< std::vector<float> > tempvec2;
	  for (Int_t tg=0; tg<7; ++tg){
	    sprintf(name,"SETEffCorrDataRatioParametersBin%1d_%1d",tv, tg);
	    if (tv==6)
	      sprintf(name,"SETEffCorrDataRatioParametersBin_%1d",tg);
	    tempvec.push_back(parm.GetVFloat(name));
	    //not used -- but required for SETefficiencysmear constructor
	    sprintf(name,"SETEffCorrDataRatioParameters2Bin%1d_%1d",tv,tg);
	    if (tv==6)
	      sprintf(name,"SETEffCorrDataRatioParameters2Bin_%1d",tg);
	    tempvec2.push_back(parm.GetVFloat(name));
	  }
	  WSETEffCorrDataRatioParameters.push_back(tempvec);
	  tempvec.clear();
	  WSETEffCorrDataRatioParameters2.push_back(tempvec2);
	  tempvec2.clear();
	  //
	  if (useHack==2) {
	    WSETEffCorrDataRatioPTFit = parm.GetVFloat("WSETEffCorrDataRatioPTFit");
	    WSETEffCorrDataRatioLumiFit = parm.GetVFloat("WSETEffCorrDataRatioLumiFit");
	  }
	}
      } else if (useHack==3) {
	WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackPtDepParameters"));

	if(parm.GetBool("Run3")) {
	  WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackSETDepParameters3"));
	  WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackLumiDepParameters3"));
	} else if(parm.GetBool("Run4")) {
	  WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackSETDepParameters4"));
	  WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackLumiDepParameters4"));
	}

	WSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackDetEtaDepParameters"));
      }
    }
    // lumi-dependent part
    for (int jj=0; jj<=lumibins->size(); jj++) {
      TString n;
      n="WSETEffCorrParameters_Lumi"; n+=jj;
      std::vector<float> WSETEffCorrParameters = parm.GetVFloat(n.Data());
      //
      std::vector<float> WSETEffCorrPTEpertBase;
      std::vector<float> WSETEffCorrPTEpertA;
      std::vector<float> WSETEffCorrPTEpertB;
      std::vector<float> WSETEffCorrPTEpertC;
      std::vector<float> WSETEffCorrPTEpertD;
      std::vector<float> WSETEffCorrPTEpertE;
      std::vector<float> WSETEffCorrPTEpertF;
      std::vector<float> WSETEffCorrPTEpertG;
      std::vector<float> WSETEffCorrPTEpertH;
      std::vector<float> WSETEffCorrPTEpertNorm;
      float WSETEffCorrPTEpertRelGlobNorm;
      //
      int WSETEffCorrPTEupara;
      //
      std::vector< std::vector<float> > WSETEffCorrEPTEpertBase;
      std::vector< std::vector<float> > WSETEffCorrEPTEpertA;
      std::vector< std::vector<float> > WSETEffCorrEPTEpertB;
      std::vector< std::vector<float> > WSETEffCorrEPTEpertC;
      std::vector< std::vector<float> > WSETEffCorrEPTEpertD;
      std::vector< std::vector<float> > WSETEffCorrEPTEpertE;
      std::vector< std::vector<float> > WSETEffCorrEPTEpertF;
      std::vector< std::vector<float> > WSETEffCorrEPTEpertG;
      std::vector< std::vector<float> > WSETEffCorrEPTEpertH;
      std::vector< std::vector<float> > WSETEffCorrEPTEpertNorm;
      //
      if (WSETEffCorrPTEpert==1 || WSETEffCorrPTEpert==2) {
	n="WSETEffCorrPTEpertBase_Lumi"; n+=jj;
	WSETEffCorrPTEpertBase = parm.GetVFloat(n.Data());
	n="WSETEffCorrPTEpertA_Lumi"; n+=jj;
	WSETEffCorrPTEpertA = parm.GetVFloat(n.Data());
	n="WSETEffCorrPTEpertB_Lumi"; n+=jj;
	WSETEffCorrPTEpertB = parm.GetVFloat(n.Data());
	n="WSETEffCorrPTEpertC_Lumi"; n+=jj;
	WSETEffCorrPTEpertC = parm.GetVFloat(n.Data());
	n="WSETEffCorrPTEpertD_Lumi"; n+=jj;
	WSETEffCorrPTEpertD = parm.GetVFloat(n.Data());
	n="WSETEffCorrPTEpertE_Lumi"; n+=jj;
	WSETEffCorrPTEpertE = parm.GetVFloat(n.Data());
	n="WSETEffCorrPTEpertF_Lumi"; n+=jj;
	WSETEffCorrPTEpertF = parm.GetVFloat(n.Data());
	n="WSETEffCorrPTEpertG_Lumi"; n+=jj;
	WSETEffCorrPTEpertG = parm.GetVFloat(n.Data());
	n="WSETEffCorrPTEpertH_Lumi"; n+=jj;
	WSETEffCorrPTEpertH = parm.GetVFloat(n.Data());
	n="WSETEffCorrPTEpertNorm_Lumi"; n+=jj;
	WSETEffCorrPTEpertNorm = parm.GetVFloat(n.Data());
      } else if (WSETEffCorrPTEpert==3) {
	WSETEffCorrPTEupara = parm.GetInt("WSETEffCorrPTEupara", 0);
	for (int i=0; i<5; i++) {
	  TString n;
	  n="WSETEffCorrPTEpertBase_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  WSETEffCorrEPTEpertBase.push_back(parm.GetVFloat(n.Data()));
	  n="WSETEffCorrPTEpertA_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  WSETEffCorrEPTEpertA.push_back(parm.GetVFloat(n.Data()));
	  n="WSETEffCorrPTEpertB_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  WSETEffCorrEPTEpertB.push_back(parm.GetVFloat(n.Data()));
	  n="WSETEffCorrPTEpertC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  WSETEffCorrEPTEpertC.push_back(parm.GetVFloat(n.Data()));
	  n="WSETEffCorrPTEpertD_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  WSETEffCorrEPTEpertD.push_back(parm.GetVFloat(n.Data()));
	  n="WSETEffCorrPTEpertE_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  WSETEffCorrEPTEpertE.push_back(parm.GetVFloat(n.Data()));
	  n="WSETEffCorrPTEpertF_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  WSETEffCorrEPTEpertF.push_back(parm.GetVFloat(n.Data()));
	  n="WSETEffCorrPTEpertG_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  WSETEffCorrEPTEpertG.push_back(parm.GetVFloat(n.Data()));
	  n="WSETEffCorrPTEpertH_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  WSETEffCorrEPTEpertH.push_back(parm.GetVFloat(n.Data()));
	  n="WSETEffCorrPTEpertNorm_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  WSETEffCorrEPTEpertNorm.push_back(parm.GetVFloat(n.Data()));
	}
	if (WSETEffCorrPTEupara==1) {
	  for (int i=0; i<5; i++) {
	    TString n;
	    n="WSETEffCorrPTEpertBase_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    WSETEffCorrEPTEpertBase.push_back(parm.GetVFloat(n.Data()));
	    n="WSETEffCorrPTEpertA_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    WSETEffCorrEPTEpertA.push_back(parm.GetVFloat(n.Data()));
	    n="WSETEffCorrPTEpertB_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    WSETEffCorrEPTEpertB.push_back(parm.GetVFloat(n.Data()));
	    n="WSETEffCorrPTEpertC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    WSETEffCorrEPTEpertC.push_back(parm.GetVFloat(n.Data()));
	    n="WSETEffCorrPTEpertD_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    WSETEffCorrEPTEpertD.push_back(parm.GetVFloat(n.Data()));
	    n="WSETEffCorrPTEpertE_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    WSETEffCorrEPTEpertE.push_back(parm.GetVFloat(n.Data()));
	    n="WSETEffCorrPTEpertF_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    WSETEffCorrEPTEpertF.push_back(parm.GetVFloat(n.Data()));
	    n="WSETEffCorrPTEpertG_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    WSETEffCorrEPTEpertG.push_back(parm.GetVFloat(n.Data()));
	    n="WSETEffCorrPTEpertH_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    WSETEffCorrEPTEpertH.push_back(parm.GetVFloat(n.Data()));
	    n="WSETEffCorrPTEpertNorm_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    WSETEffCorrEPTEpertNorm.push_back(parm.GetVFloat(n.Data()));
	  }
	  //
	  n="WSETEffCorrPTEpertRelGlobNorm_Lumi"; n+=jj;
	  WSETEffCorrPTEpertRelGlobNorm=parm.GetFloat(n.Data());
	}
      }
      // multiply in the relative normalisation between lumi bins
      if (WSETEffCorrParameters.size()==5) {
	WSETEffCorrParameters.push_back((*luminorm)[jj]);
	for (int i=0; i<4; i++) WSETEffCorrParameters.push_back(0);
      } else {
	for (int i=5; i<10; i++) (WSETEffCorrParameters[i])*=(*luminorm)[jj];
      }
      //
      if (WSETEffCorrPTEpert) {
	if (WSETEffCorrPTEpert==3) {
	  _workers[jj] = new SETefficiencySmear(WSETEffCorrParameters, WSETEffCorrParameters, // no dedicated EC values here
						WSETEffCorrScaled, WSETEffCorrScale, WSETEffCorrRelative, WSETEffCorrInterpolate,
						WSETEffCorrPTEupara, WSETEffCorrPTEpert,
						&WSETEffCorrEPTEpertBase,
						&WSETEffCorrEPTEpertA, &WSETEffCorrEPTEpertB,
						&WSETEffCorrEPTEpertC, &WSETEffCorrEPTEpertD,
						&WSETEffCorrEPTEpertE, &WSETEffCorrEPTEpertF,
						&WSETEffCorrEPTEpertG, &WSETEffCorrEPTEpertH,
						&WSETEffCorrEPTEpertNorm, WSETEffCorrPTEpertRelGlobNorm,
						&WSETEffCorrDataRatioParameters, &WSETEffCorrDataRatioParameters2,
						&WSETEffDataHackParameters,
						&WSETEffCorrDataRatioPTFit, &WSETEffCorrDataRatioLumiFit,
						useHack, useLumiBins);
	} else {
	  _workers[jj] = new SETefficiencySmear(WSETEffCorrParameters, WSETEffCorrScaled, WSETEffCorrScale, WSETEffCorrRelative, WSETEffCorrInterpolate,
						WSETEffCorrPTEpert, &WSETEffCorrPTEpertBase,
						&WSETEffCorrPTEpertA, &WSETEffCorrPTEpertB,
						&WSETEffCorrPTEpertC, &WSETEffCorrPTEpertD,
						&WSETEffCorrPTEpertE, &WSETEffCorrPTEpertF,
						&WSETEffCorrPTEpertG, &WSETEffCorrPTEpertH,
						&WSETEffCorrPTEpertNorm,
						&WSETEffCorrDataRatioParameters, &WSETEffCorrDataRatioParameters2,
						&WSETEffDataHackParameters,
						&WSETEffCorrDataRatioPTFit, &WSETEffCorrDataRatioLumiFit,
						useHack, useLumiBins );
	}
      } else {
	_workers[jj] = new SETefficiencySmear(WSETEffCorrParameters, WSETEffCorrScaled, WSETEffCorrScale);
      }
    }
  } else {
    // lumi-independent part
    bool ZSETEffCorrScaled = parm.GetBool("ZSETEffCorrScaled", kFALSE);
    bool ZSETEffCorrRelative = parm.GetBool("ZSETEffCorrRelative", kFALSE);
    float ZSETEffCorrScale=200.;
    if (ZSETEffCorrRelative) ZSETEffCorrScale=20.;
    bool ZSETEffCorrInterpolate = parm.GetBool("ZSETEffCorrInterpolate", kFALSE);
    int ZSETEffCorrPTEpert = parm.GetInt("ZSETEffCorrPTEpert", 0);
    // parameters for the data hack (also lumi-independent in the sense that we give the same set of parameter values to all workers)
    std::vector< std::vector< std::vector<float> > > ZSETEffCorrDataRatioParameters;
    std::vector< std::vector< std::vector<float> > > ZSETEffCorrDataRatioParameters2;
    std::vector< std::vector<float> > ZSETEffDataHackParameters;
    std::vector<float> ZSETEffCorrDataRatioPTFit;
    std::vector<float> ZSETEffCorrDataRatioLumiFit;
    int useHack = parm.GetInt("SETuseHack");
    bool useLumiBins = parm.GetBool("SETuseLumiBins");
    char name[100];
    if (useHack) {
      if (useHack<=2) {
	for (Int_t tv=0; tv<7; ++tv){
	  std::vector< std::vector<float> >  tempvec1;
	  std::vector< std::vector<float> >  tempvec2;
	  for (Int_t tg=0; tg<7; ++tg){
	    sprintf(name,"SETEffCorrDataRatioParametersBin%1d_%1d",tv,tg);
	    if (tv==6)
	      sprintf(name,"SETEffCorrDataRatioParametersBin_%1d",tg);
	    tempvec1.push_back(parm.GetVFloat(name));
	    sprintf(name,"SETEffCorrDataRatioParameters2Bin%1d_%1d",tv,tg);
	    if (tv==6)
	      sprintf(name,"SETEffCorrDataRatioParameters2Bin_%1d",tg);
	    tempvec2.push_back(parm.GetVFloat(name));
	  }
	  ZSETEffCorrDataRatioParameters.push_back(tempvec1);
	  ZSETEffCorrDataRatioParameters2.push_back(tempvec2);
	  tempvec1.clear();
	  tempvec2.clear();
	  //
	  if (useHack==2) {
	    ZSETEffCorrDataRatioPTFit = parm.GetVFloat("ZSETEffCorrDataRatioPTFit");
	    ZSETEffCorrDataRatioLumiFit = parm.GetVFloat("ZSETEffCorrDataRatioLumiFit");
	  }
	}
      } else if (useHack==3){
	ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackPtDepParameters"));


	if(parm.GetBool("Run3")) {
	  ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackSETDepParameters3"));
	  ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackLumiDepParameters3"));
	} else if(parm.GetBool("Run4")) {
	  ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackSETDepParameters4"));
	  ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackLumiDepParameters4"));
	}

	ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackDetEtaDepParameters"));
      }
    }
    // lumi-dependent part
    for (int jj=0; jj<=lumibins->size(); jj++) {
      TString n;
      n="ZSETEffCorrParametersCCCC_Lumi"; n+=jj;
      std::vector<float> ZSETEffCorrParametersCCCC = parm.GetVFloat(n.Data());
      n="ZSETEffCorrParametersCCEC_Lumi"; n+=jj;
      std::vector<float> ZSETEffCorrParametersCCEC = parm.GetVFloat(n.Data());
      n="ZSETEffCorrParametersECEC_Lumi"; n+=jj;
      std::vector<float> ZSETEffCorrParametersECEC = parm.GetVFloat(n.Data());
      //
      std::vector<float> ZSETEffCorrPTEpertBase;
      std::vector<float> ZSETEffCorrPTEpertA;
      std::vector<float> ZSETEffCorrPTEpertB;
      std::vector<float> ZSETEffCorrPTEpertC;
      std::vector<float> ZSETEffCorrPTEpertD;
      std::vector<float> ZSETEffCorrPTEpertE;
      std::vector<float> ZSETEffCorrPTEpertF;
      std::vector<float> ZSETEffCorrPTEpertG;
      std::vector<float> ZSETEffCorrPTEpertH;
      std::vector<float> ZSETEffCorrPTEpertNorm;
      float ZSETEffCorrPTEpertRelGlobNorm;
      //
      int ZSETEffCorrPTEupara;
      //
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertBase;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertA;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertB;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertD;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertE;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertF;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertG;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertH;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertNorm;
      std::vector<float> ZSETEffCorrEPTEparamsNorm_CommonMultiplier;
      //
      std::vector<float> ZSETEffCorrPTEpertBase_EC;
      std::vector<float> ZSETEffCorrPTEpertA_EC;
      std::vector<float> ZSETEffCorrPTEpertB_EC;
      std::vector<float> ZSETEffCorrPTEpertC_EC;
      std::vector<float> ZSETEffCorrPTEpertD_EC;
      std::vector<float> ZSETEffCorrPTEpertE_EC;
      std::vector<float> ZSETEffCorrPTEpertF_EC;
      std::vector<float> ZSETEffCorrPTEpertG_EC;
      std::vector<float> ZSETEffCorrPTEpertH_EC;
      std::vector<float> ZSETEffCorrPTEpertNorm_EC;
      //                                                                                                            
      float ZSETEffCorrPTEpertRelGlobNorm_EC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertBase_EC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertA_EC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertB_EC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertC_EC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertD_EC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertE_EC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertF_EC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertG_EC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertH_EC;
      std::vector< std::vector<float> > ZSETEffCorrEPTEpertNorm_EC;
      //
      if (ZSETEffCorrPTEpert==1 || ZSETEffCorrPTEpert==2) {
	n="ZSETEffCorrPTEpertBase_Lumi"; n+=jj;
	ZSETEffCorrPTEpertBase = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertA_Lumi"; n+=jj;
	ZSETEffCorrPTEpertA = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertB_Lumi"; n+=jj;
	ZSETEffCorrPTEpertB = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertC = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertD_Lumi"; n+=jj;
	ZSETEffCorrPTEpertD = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertE_Lumi"; n+=jj;
	ZSETEffCorrPTEpertE = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertF_Lumi"; n+=jj;
	ZSETEffCorrPTEpertF = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertG_Lumi"; n+=jj;
	ZSETEffCorrPTEpertG = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertH_Lumi"; n+=jj;
	ZSETEffCorrPTEpertH = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertNorm_Lumi"; n+=jj;
	ZSETEffCorrPTEpertNorm = parm.GetVFloat(n.Data());
      } else if (ZSETEffCorrPTEpert==3) {
	ZSETEffCorrPTEupara = parm.GetInt("ZSETEffCorrPTEupara", 0);
	for (int i=0; i<5; i++) {
	  TString n;
	  n="ZSETEffCorrPTEpertBase_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertBase.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertA_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertA.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertB_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertB.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertC.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertD_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertD.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertE_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertE.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertF_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertF.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertG_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertG.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertH_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertH.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertNorm_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertNorm.push_back(parm.GetVFloat(n.Data()));
	}
	if (ZSETEffCorrPTEupara==1) {
	  for (int i=0; i<5; i++) {
	    TString n;
	    n="ZSETEffCorrPTEpertBase_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertBase.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertA_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertA.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertB_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertB.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertC.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertD_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertD.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertE_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertE.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertF_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertF.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertG_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertG.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertH_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertH.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertNorm_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertNorm.push_back(parm.GetVFloat(n.Data()));
	  }
	  //                                                                                                                                 
	  n="ZSETEffCorrEPTEparamsNorm_CommonMultiplier_Lumi"; n+=jj;
	  ZSETEffCorrEPTEparamsNorm_CommonMultiplier=parm.GetVFloat(n.Data());
	  n="ZSETEffCorrPTEpertRelGlobNorm_Lumi"; n+=jj;
	  ZSETEffCorrPTEpertRelGlobNorm=parm.GetFloat(n.Data());
	}
      }
      //
      if (ZSETEffCorrPTEpert==1 || ZSETEffCorrPTEpert==2) {
	n="ZSETEffCorrPTEpertBase_EC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertBase_EC = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertA_EC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertA_EC = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertB_EC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertB_EC = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertC_EC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertC_EC = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertD_EC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertD_EC = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertE_EC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertE_EC = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertF_EC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertF_EC = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertG_EC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertG_EC = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertH_EC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertH_EC = parm.GetVFloat(n.Data());
	n="ZSETEffCorrPTEpertNorm_EC_Lumi"; n+=jj;
	ZSETEffCorrPTEpertNorm_EC = parm.GetVFloat(n.Data());
      } else if (ZSETEffCorrPTEpert==3) {
	for (int i=0; i<5; i++) {
	  TString n;
	  n="ZSETEffCorrPTEpertBase_EC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertBase_EC.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertA_EC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertA_EC.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertB_EC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertB_EC.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertC_EC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertC_EC.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertD_EC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertD_EC.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertE_EC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertE_EC.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertF_EC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertF_EC.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertG_EC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertG_EC.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertH_EC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertH_EC.push_back(parm.GetVFloat(n.Data()));
	  n="ZSETEffCorrPTEpertNorm_EC_"; n+=i;
	  n+="_Lumi"; n+=jj;
	  ZSETEffCorrEPTEpertNorm_EC.push_back(parm.GetVFloat(n.Data()));
	}
	if (ZSETEffCorrPTEupara==1) {
	  for (int i=0; i<5; i++) {
	    TString n;
	    n="ZSETEffCorrPTEpertBase_EC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertBase_EC.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertA_EC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertA_EC.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertB_EC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertB_EC.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertC_EC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertC_EC.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertD_EC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertD_EC.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertE_EC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertE_EC.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertF_EC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertF_EC.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertG_EC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertG_EC.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertH_EC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertH_EC.push_back(parm.GetVFloat(n.Data()));
	    n="ZSETEffCorrPTEpertNorm_EC_"; n+=i; n+="b";
	    n+="_Lumi"; n+=jj;
	    ZSETEffCorrEPTEpertNorm_EC.push_back(parm.GetVFloat(n.Data()));
	  }
	  //                                                                                                                                                                     
	  n="ZSETEffCorrPTEpertRelGlobNorm_EC_Lumi"; n+=jj;
	  ZSETEffCorrPTEpertRelGlobNorm_EC=parm.GetFloat(n.Data());
	}
      }
      // multiply in the relative normalisation between lumi bins
      if (ZSETEffCorrParametersCCCC.size()==5) {
        ZSETEffCorrParametersCCCC.push_back(_luminormCCCC[jj]);
        for (int i=0; i<4; i++) ZSETEffCorrParametersCCCC.push_back(0);
      } else {
        for (int i=5; i<10; i++) (ZSETEffCorrParametersCCCC[i])*=_luminormCCCC[jj];
      }
      if (ZSETEffCorrParametersCCEC.size()==5) {
        ZSETEffCorrParametersCCEC.push_back(_luminormCCEC[jj]);
        for (int i=0; i<4; i++) ZSETEffCorrParametersCCEC.push_back(0);
      } else {
        for (int i=5; i<10; i++) (ZSETEffCorrParametersCCEC[i])*=_luminormCCEC[jj];
      }
      if (ZSETEffCorrParametersECEC.size()==5) {
        ZSETEffCorrParametersECEC.push_back(_luminormECEC[jj]);
        for (int i=0; i<4; i++) ZSETEffCorrParametersECEC.push_back(0);
      } else {
        for (int i=5; i<10; i++) (ZSETEffCorrParametersECEC[i])*=_luminormECEC[jj];
      }
      //
      if (ZSETEffCorrPTEpert) {
	if (ZSETEffCorrPTEpert==3) {
	  _workers[jj] = new SETefficiencySmear(ZSETEffCorrParametersCCCC,ZSETEffCorrParametersCCEC,ZSETEffCorrParametersECEC,
						ZSETEffCorrScaled,ZSETEffCorrScale,ZSETEffCorrRelative,ZSETEffCorrInterpolate,
						ZSETEffCorrPTEupara, ZSETEffCorrPTEpert,
						&ZSETEffCorrEPTEpertBase,
						&ZSETEffCorrEPTEpertA, &ZSETEffCorrEPTEpertB,
						&ZSETEffCorrEPTEpertC, &ZSETEffCorrEPTEpertD,
						&ZSETEffCorrEPTEpertE, &ZSETEffCorrEPTEpertF,
						&ZSETEffCorrEPTEpertG, &ZSETEffCorrEPTEpertH,
						&ZSETEffCorrEPTEpertNorm, &ZSETEffCorrEPTEparamsNorm_CommonMultiplier, ZSETEffCorrPTEpertRelGlobNorm,
						&ZSETEffCorrDataRatioParameters, &ZSETEffCorrDataRatioParameters2,
						&ZSETEffDataHackParameters,
						&ZSETEffCorrDataRatioPTFit, &ZSETEffCorrDataRatioLumiFit,
						&ZSETEffCorrEPTEpertBase_EC,
						&ZSETEffCorrEPTEpertA_EC, &ZSETEffCorrEPTEpertB_EC,
						&ZSETEffCorrEPTEpertC_EC, &ZSETEffCorrEPTEpertD_EC,
						&ZSETEffCorrEPTEpertE_EC, &ZSETEffCorrEPTEpertF_EC,
						&ZSETEffCorrEPTEpertG_EC, &ZSETEffCorrEPTEpertH_EC,
						&ZSETEffCorrEPTEpertNorm_EC, ZSETEffCorrPTEpertRelGlobNorm_EC,
						useHack, useLumiBins);
	} else {
	  _workers[jj] = new SETefficiencySmear(ZSETEffCorrParametersCCCC,ZSETEffCorrParametersCCEC,ZSETEffCorrParametersECEC,
						ZSETEffCorrScaled,ZSETEffCorrScale,ZSETEffCorrRelative,ZSETEffCorrInterpolate,
						ZSETEffCorrPTEpert,
						&ZSETEffCorrPTEpertBase,
						&ZSETEffCorrPTEpertA, &ZSETEffCorrPTEpertB,
						&ZSETEffCorrPTEpertC, &ZSETEffCorrPTEpertD,
						&ZSETEffCorrPTEpertE, &ZSETEffCorrPTEpertF,
						&ZSETEffCorrPTEpertG, &ZSETEffCorrPTEpertH,
						&ZSETEffCorrPTEpertNorm,
						&ZSETEffCorrDataRatioParameters, &ZSETEffCorrDataRatioParameters2,
						&ZSETEffDataHackParameters,
						&ZSETEffCorrDataRatioPTFit, &ZSETEffCorrDataRatioLumiFit,
						&ZSETEffCorrPTEpertBase_EC,
						&ZSETEffCorrPTEpertA_EC, &ZSETEffCorrPTEpertB_EC,
						&ZSETEffCorrPTEpertC_EC, &ZSETEffCorrPTEpertD_EC,
						&ZSETEffCorrPTEpertE_EC, &ZSETEffCorrPTEpertF_EC,
						&ZSETEffCorrPTEpertG_EC, &ZSETEffCorrPTEpertH_EC,
						&ZSETEffCorrPTEpertNorm_EC, useHack, useLumiBins);
	}
      } else {
	_workers[jj] = new SETefficiencySmear(ZSETEffCorrParametersCCCC,ZSETEffCorrParametersCCEC,ZSETEffCorrParametersECEC,ZSETEffCorrScaled,ZSETEffCorrScale,false,false,0,(std::vector<float>*)NULL);
      }
    }
  }

}


// calculates the SET efficiency
double SETefficiencySmear_LumiDispatch::getSETeff(float SET, float lumi, float pTe, float pTe2, bool isEC, bool isEC2, float eta1, float eta2, float upara1, float upara2, TRandom3 *dummy, double *external_rnd2) {

  // figure out which worker is appropriate
  int theBin=0;
  while (lumi>_lumibins[theBin]) {
    theBin++;
    if (theBin==_lumibins.size()) break;
  }

  // call the appropriate worker
  double result = _workers[theBin]->getSETeff(SET, lumi, pTe, pTe2, isEC, isEC2, eta1, eta2, upara1, upara2, dummy, external_rnd2);

  // in the case of Z -> e e, buffer results for the individual electrons
  if (!_isW) {
    _pass1 = _workers[theBin]->passesFirst();
    _pass2 = _workers[theBin]->passesSecond();
  }

  return result;

}


void SETefficiencySmear_LumiDispatch::InterpBinner(float pTe, int& bin1, int& bin2, float& d) {

  // simply use the first worker
  _workers[0]->InterpBinner(pTe, bin1, bin2, d);
  return;

}


// flip an efficiency
// optional: external_rnd is a pointer to the external random number value
bool SETefficiencySmear_LumiDispatch::passesSETeff(float SET, float lumi, TRandom3 *dummy, double *external_rnd, float pTe, float pTe2, bool isEC, bool isEC2, float eta1, float eta2, float upara1, float upara2) {

  // figure out which worker is appropriate
  int theBin=0;
  while (lumi>_lumibins[theBin]) {
    theBin++;
    if (theBin==_lumibins.size()) break;
  }

  // call the appropriate worker
  bool result = _workers[theBin]->passesSETeff(SET, lumi, dummy, external_rnd, pTe, pTe2, isEC, isEC2, eta1, eta2, upara1, upara2);

  // in the case of Z -> e e, buffer results for the individual electrons
  if (!_isW) {
    _pass1 = _workers[theBin]->passesFirst();
    _pass2 = _workers[theBin]->passesSecond();
  }

  return result;

}


bool SETefficiencySmear_LumiDispatch::passesFirst() {
  assert(!_isW);
  return _pass1;
}


bool SETefficiencySmear_LumiDispatch::passesSecond() {
  assert(!_isW);
  return _pass2;
}

