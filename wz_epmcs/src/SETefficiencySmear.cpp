#include "TROOT.h"
#include "SETefficiencySmear.hpp"
#include "TRandom3.h"
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

// constructor
SETefficiencySmear::SETefficiencySmear(std::vector<float> params, bool isScaled, float Scale, bool isRelative, bool doInterpolate,
				       int doPTEperturbation, std::vector<float>* PTEparamsBase,
				       std::vector<float>* PTEparamsA, std::vector<float>* PTEparamsB,
				       std::vector<float>* PTEparamsC, std::vector<float>* PTEparamsD,
				       std::vector<float>* PTEparamsE, std::vector<float>* PTEparamsF,
				       std::vector<float>* PTEparamsG, std::vector<float>* PTEparamsH,
				       std::vector<float>* PTEparamsNorm,
                                       std::vector< std::vector< std::vector<float> > >* DataRatioparams,
                                       std::vector< std::vector< std::vector<float> > >* DataRatioparams2,
                                       std::vector< std::vector<float> >* DataHackPars,
				       std::vector<float>* DataRatioPTFit, std::vector<float>* DataRatioLumiFit,
				       int useHack, bool useLumiBins) {

  _uparaSplit=0;
  Init(params, isScaled, Scale, isRelative, doInterpolate,
       doPTEperturbation, PTEparamsBase,
       PTEparamsA, PTEparamsB, PTEparamsC, PTEparamsD, PTEparamsE, PTEparamsF, PTEparamsG, PTEparamsH,
       PTEparamsNorm, DataRatioparams, DataRatioparams2, DataHackPars,
       DataRatioPTFit, DataRatioLumiFit, useHack, useLumiBins );
  _myConfig=0;

  std::cout<<"Finished SETefficiencySmear initialisation"<<std::endl;

}

void SETefficiencySmear::Init(std::vector<float> params, bool isScaled, float Scale, bool isRelative, bool doInterpolate,
			      int doPTEperturbation, std::vector<float>* PTEparamsBase,
			      std::vector<float>* PTEparamsA, std::vector<float>* PTEparamsB,
			      std::vector<float>* PTEparamsC, std::vector<float>* PTEparamsD,
			      std::vector<float>* PTEparamsE, std::vector<float>* PTEparamsF,
			      std::vector<float>* PTEparamsG, std::vector<float>* PTEparamsH,
			      std::vector<float>* PTEparamsNorm,
			      std::vector< std::vector< std::vector<float> > >* DataRatioparams, 
                              std::vector <std::vector< std::vector<float> > >* DataRatioparams2,
                              std::vector< std::vector<float> >* DataHackPars,
			      std::vector<float>* DataRatioPTFit, std::vector<float>* DataRatioLumiFit,
			      int useHack, bool useLumiBins) {
  if ((params.size()!=5)&&(params.size()!=10)) {
    std::cout<<"SETefficiencySmear initialised with wrong number of parameters."<<std::endl;
    assert(0);
  }
  _params=params;
  _isScaled=isScaled;
  _Scale=Scale;
  _isRelative=isRelative;
  _doInterpolate=doInterpolate;
  _useDataMCRatioHack=useHack;
  _useLumiBins=useLumiBins;
  assert((_params.size()==5)||(_params.size()==10));
  //
  _doPTEperturbation=doPTEperturbation;
  if (_doPTEperturbation==1) {
    assert(PTEparamsBase->size()==5);
    assert(PTEparamsA->size()==5);
    assert(PTEparamsB->size()==5);
    assert(PTEparamsC->size()==5);
    assert(PTEparamsD->size()==5);
    assert(PTEparamsE->size()==5);
    assert(PTEparamsF->size()==5);
    assert(PTEparamsNorm->size()==6);
    if (_useDataMCRatioHack==1){
      assert (DataRatioparams->size()==7);
      for (Int_t j=0; j <4; ++j){
	assert(DataRatioparams->at(j).size()==7);
	for (Int_t k=0; k <4; ++k)
	  assert(DataRatioparams->at(j).at(k).size()==4);
      }
      assert (DataRatioparams2->size()==7);
      for (Int_t j=0; j <4; ++j){
	assert(DataRatioparams2->at(j).size()==7);
	for (Int_t k=0; k <4; ++k)
	  assert(DataRatioparams2->at(j).at(k).size()==4);
      }
    }
    _PTEparamsBase=(*PTEparamsBase);
    _PTEparamsA=(*PTEparamsA);
    _PTEparamsB=(*PTEparamsB);
    _PTEparamsC=(*PTEparamsC);
    _PTEparamsD=(*PTEparamsD);
    _PTEparamsE=(*PTEparamsE);
    _PTEparamsF=(*PTEparamsF);
    _PTEparamsNorm=(*PTEparamsNorm);
    _DataRatioParams=(*DataRatioparams);
    _DataRatioParams2=(*DataRatioparams2);
    _DataRatioPTFit=(*DataRatioPTFit);
    _DataRatioLumiFit=(*DataRatioLumiFit);
    _DataHackPars=(*DataHackPars);
  } else if (_doPTEperturbation==2) {
    assert((PTEparamsBase->size()==5)||(PTEparamsBase->size()==10));
    assert((PTEparamsA->size()==5)||(PTEparamsA->size()==10));
    assert((PTEparamsB->size()==5)||(PTEparamsB->size()==10));
    assert((PTEparamsC->size()==5)||(PTEparamsC->size()==10));
    assert((PTEparamsD->size()==5)||(PTEparamsD->size()==10));
    assert((PTEparamsE->size()==5)||(PTEparamsE->size()==10));
    assert((PTEparamsF->size()==5)||(PTEparamsF->size()==10));
    assert((PTEparamsG->size()==5)||(PTEparamsG->size()==10));
    assert((PTEparamsH->size()==5)||(PTEparamsH->size()==10));
    assert(PTEparamsNorm->size()==8);
    if (_useDataMCRatioHack==1){
      assert (DataRatioparams->size()==7);
      for (Int_t j=0; j <7; ++j){
	assert(DataRatioparams->at(j).size()==7);
	for (Int_t k=0; k <7; ++k){
	  assert(DataRatioparams->at(j).at(k).size()==4);
	}
      }
      assert (DataRatioparams2->size()==7);
      for (Int_t j=0; j <4; ++j){
	assert(DataRatioparams2->at(j).size()==7);
	for (Int_t k=0; k <4; ++k)
	  assert(DataRatioparams2->at(j).at(k).size()==4);
      }
    }
    _PTEparamsBase=(*PTEparamsBase);
    _PTEparamsA=(*PTEparamsA);
    _PTEparamsB=(*PTEparamsB);
    _PTEparamsC=(*PTEparamsC);
    _PTEparamsD=(*PTEparamsD);
    _PTEparamsE=(*PTEparamsE);
    _PTEparamsF=(*PTEparamsF);
    _PTEparamsG=(*PTEparamsG);
    _PTEparamsH=(*PTEparamsH);
    _PTEparamsNorm=(*PTEparamsNorm);
    _DataRatioParams=(*DataRatioparams);
    _DataRatioParams2=(*DataRatioparams2);
    _DataRatioPTFit=(*DataRatioPTFit);
    _DataRatioLumiFit=(*DataRatioLumiFit);
    _DataHackPars=(*DataHackPars);
  }

}


// constructor with CC/EC separation - for W events
SETefficiencySmear::SETefficiencySmear(std::vector<float> paramsCC, std::vector<float> paramsEC, 
				       bool isScaled, float Scale, bool isRelative, bool doInterpolate,
				       int doPTEperturbation,
				       std::vector<float>* PTEparamsBase,
				       std::vector<float>* PTEparamsA, std::vector<float>* PTEparamsB,
				       std::vector<float>* PTEparamsC, std::vector<float>* PTEparamsD,
				       std::vector<float>* PTEparamsE, std::vector<float>* PTEparamsF,
				       std::vector<float>* PTEparamsG, std::vector<float>* PTEparamsH,
				       std::vector<float>* PTEparamsNorm,
				       std::vector< std::vector< std::vector<float> > >* DataRatioparams,
				       std::vector< std::vector< std::vector<float> > >* DataRatioparams2,
                                       std::vector< std::vector<float> >* DataHackPars,
				       std::vector<float>* DataRatioPTFit, std::vector<float>* DataRatioLumiFit,
				       std::vector<float>* PTEparamsBase_EC,
				       std::vector<float>* PTEparamsA_EC, std::vector<float>* PTEparamsB_EC,
				       std::vector<float>* PTEparamsC_EC, std::vector<float>* PTEparamsD_EC,
				       std::vector<float>* PTEparamsE_EC, std::vector<float>* PTEparamsF_EC,
				       std::vector<float>* PTEparamsG_EC, std::vector<float>* PTEparamsH_EC,
				       std::vector<float>* PTEparamsNorm_EC, int useHack, bool useLumiBins) {

  _uparaSplit=0;
  Init(paramsCC, isScaled, Scale, isRelative, doInterpolate,
       doPTEperturbation, PTEparamsBase,
       PTEparamsA, PTEparamsB, PTEparamsC, PTEparamsD, PTEparamsE, PTEparamsF, PTEparamsG, PTEparamsH,
       PTEparamsNorm, DataRatioparams, DataRatioparams2, DataHackPars,
       DataRatioPTFit, DataRatioLumiFit, useHack, useLumiBins);
  _myConfig=1;
  //
  if ((paramsEC.size()!=5)&&(paramsEC.size()!=10)) {
    std::cout<<"SETefficiencySmear initialised with wrong number of parameters (EC)."<<std::endl;
    assert(0);
  }
  _paramsEC=paramsEC;
  assert((_paramsEC.size()==5)||(_paramsEC.size()==10));
  //
  if (_doPTEperturbation==1) {
    assert(PTEparamsBase_EC->size()==5);
    assert(PTEparamsA_EC->size()==5);
    assert(PTEparamsB_EC->size()==5);
    assert(PTEparamsC_EC->size()==5);
    assert(PTEparamsD_EC->size()==5);
    assert(PTEparamsE_EC->size()==5);
    assert(PTEparamsF_EC->size()==5);
    assert(PTEparamsNorm_EC->size()==6);
    _PTEparamsBase_EC=(*PTEparamsBase_EC);
    _PTEparamsA_EC=(*PTEparamsA_EC);
    _PTEparamsB_EC=(*PTEparamsB_EC);
    _PTEparamsC_EC=(*PTEparamsC_EC);
    _PTEparamsD_EC=(*PTEparamsD_EC);
    _PTEparamsE_EC=(*PTEparamsE_EC);
    _PTEparamsF_EC=(*PTEparamsF_EC);
    _PTEparamsNorm_EC=(*PTEparamsNorm_EC);
  } else if (_doPTEperturbation==2) {
    assert((PTEparamsBase_EC->size()==5)||(PTEparamsBase_EC->size()==10));
    assert((PTEparamsA_EC->size()==5)||(PTEparamsA_EC->size()==10));
    assert((PTEparamsB_EC->size()==5)||(PTEparamsB_EC->size()==10));
    assert((PTEparamsC_EC->size()==5)||(PTEparamsC_EC->size()==10));
    assert((PTEparamsD_EC->size()==5)||(PTEparamsD_EC->size()==10));
    assert((PTEparamsE_EC->size()==5)||(PTEparamsE_EC->size()==10));
    assert((PTEparamsF_EC->size()==5)||(PTEparamsF_EC->size()==10));
    assert((PTEparamsG_EC->size()==5)||(PTEparamsG_EC->size()==10));
    assert((PTEparamsH_EC->size()==5)||(PTEparamsH_EC->size()==10));
    assert(PTEparamsNorm_EC->size()==8);
    _PTEparamsBase_EC=(*PTEparamsBase_EC);
    _PTEparamsA_EC=(*PTEparamsA_EC);
    _PTEparamsB_EC=(*PTEparamsB_EC);
    _PTEparamsC_EC=(*PTEparamsC_EC);
    _PTEparamsD_EC=(*PTEparamsD_EC);
    _PTEparamsE_EC=(*PTEparamsE_EC);
    _PTEparamsF_EC=(*PTEparamsF_EC);
    _PTEparamsG_EC=(*PTEparamsG_EC);
    _PTEparamsH_EC=(*PTEparamsH_EC);
    _PTEparamsNorm_EC=(*PTEparamsNorm_EC);
  }

  std::cout<<"Finished SETefficiencySmear initialisation W CC/EC"<<std::endl;

}


// constructor with CC/EC separation and eta binning - for W events
SETefficiencySmear::SETefficiencySmear(std::vector<float> paramsCC, std::vector<float> paramsEC,
                                       bool isScaled, float Scale, bool isRelative, bool doInterpolate,
                                       int uparaSplit, int doPTEperturbation,
                                       std::vector< std::vector<float> >* EPTEparamsBase,
                                       std::vector< std::vector<float> >* EPTEparamsA, std::vector< std::vector<float> >* EPTEparamsB,
                                       std::vector< std::vector<float> >* EPTEparamsC, std::vector< std::vector<float> >* EPTEparamsD,
                                       std::vector< std::vector<float> >* EPTEparamsE, std::vector< std::vector<float> >* EPTEparamsF,
                                       std::vector< std::vector<float> >* EPTEparamsG, std::vector< std::vector<float> >* EPTEparamsH,
                                       std::vector< std::vector<float> >* EPTEparamsNorm, float EPTEparamsRelGlobNorm,
                                       std::vector< std::vector< std::vector<float> > >* DataRatioparams,
                                       std::vector< std::vector< std::vector<float> > >* DataRatioparams2,
                                       std::vector< std::vector<float> >* DataHackPars,
				       std::vector<float>* DataRatioPTFit, std::vector<float>* DataRatioLumiFit,
                                       int useHack, bool useLumiBins,
                                       std::vector< std::vector<float> >* EPTEparamsBase_EC,
                                       std::vector< std::vector<float> >* EPTEparamsA_EC, std::vector< std::vector<float> >* EPTEparamsB_EC,
                                       std::vector< std::vector<float> >* EPTEparamsC_EC, std::vector< std::vector<float> >* EPTEparamsD_EC,
                                       std::vector< std::vector<float> >* EPTEparamsE_EC, std::vector< std::vector<float> >* EPTEparamsF_EC,
                                       std::vector< std::vector<float> >* EPTEparamsG_EC, std::vector< std::vector<float> >* EPTEparamsH_EC,
                                       std::vector< std::vector<float> >* EPTEparamsNorm_EC, float EPTEparamsRelGlobNorm_EC) {

  _uparaSplit=uparaSplit;
  _EPTEparamsRelGlobNorm=EPTEparamsRelGlobNorm;
  _EPTEparamsRelGlobNorm_EC=EPTEparamsRelGlobNorm_EC;
  Init(paramsCC, isScaled, Scale, isRelative, doInterpolate,
       doPTEperturbation,
       EPTEparamsBase,
       EPTEparamsA, EPTEparamsB, EPTEparamsC, EPTEparamsD, EPTEparamsE, EPTEparamsF, EPTEparamsG, EPTEparamsH,
       EPTEparamsNorm, 0,
       DataRatioparams, DataRatioparams2, DataHackPars,
       DataRatioPTFit, DataRatioLumiFit, useHack, useLumiBins,
       &paramsEC,
       EPTEparamsBase_EC,
       EPTEparamsA_EC, EPTEparamsB_EC, EPTEparamsC_EC, EPTEparamsD_EC, EPTEparamsE_EC, EPTEparamsF_EC, EPTEparamsG_EC, EPTEparamsH_EC,
       EPTEparamsNorm_EC);
  _myConfig=1;

}


void SETefficiencySmear::Init(std::vector<float> params, bool isScaled, float Scale, bool isRelative, bool doInterpolate,
                              int doPTEperturbation,
                              std::vector< std::vector<float> >* EPTEparamsBase,
                              std::vector< std::vector<float> >* EPTEparamsA, std::vector< std::vector<float> >* EPTEparamsB,
                              std::vector< std::vector<float> >* EPTEparamsC, std::vector< std::vector<float> >* EPTEparamsD,
                              std::vector< std::vector<float> >* EPTEparamsE, std::vector< std::vector<float> >* EPTEparamsF,
                              std::vector< std::vector<float> >* EPTEparamsG, std::vector< std::vector<float> >* EPTEparamsH,
                              std::vector< std::vector<float> >* EPTEparamsNorm, std::vector<float>* EPTEparamsNorm_CommonMultiplier,
                              std::vector< std::vector< std::vector<float> > >* DataRatioparams, std::vector< std::vector< std::vector<float> > >* DataRatioparams2,
                              std::vector< std::vector<float> >* DataHackPars,
			      std::vector<float>* DataRatioPTFit, std::vector<float>* DataRatioLumiFit,
			      int useHack, bool useLumiBins,
                              std::vector<float>* paramsEC,
                              std::vector< std::vector<float> >* EPTEparamsBase_EC,
                              std::vector< std::vector<float> >* EPTEparamsA_EC, std::vector< std::vector<float> >* EPTEparamsB_EC,
                              std::vector< std::vector<float> >* EPTEparamsC_EC, std::vector< std::vector<float> >* EPTEparamsD_EC,
                              std::vector< std::vector<float> >* EPTEparamsE_EC, std::vector< std::vector<float> >* EPTEparamsF_EC,
                              std::vector< std::vector<float> >* EPTEparamsG_EC, std::vector< std::vector<float> >* EPTEparamsH_EC,
                              std::vector< std::vector<float> >* EPTEparamsNorm_EC) {

  if ((params.size()!=5)&&(params.size()!=10)) {
    std::cout<<"SETefficiencySmear initialised with wrong number of parameters."<<std::endl;
    assert(0);
  }
  _params=params;
  _isScaled=isScaled;
  _Scale=Scale;
  _isRelative=isRelative;
  _doInterpolate=doInterpolate;
  _useDataMCRatioHack=useHack;
  _useLumiBins=useLumiBins;
  assert((_params.size()==5)||(_params.size()==10));
  //
  _doPTEperturbation=doPTEperturbation;
  assert(_doPTEperturbation==3);
  //
  if (_uparaSplit==0) {
    assert(EPTEparamsBase->size()==5);
    for (int i=0; i<5; i++) assert((EPTEparamsBase->at(i).size()==5)||(EPTEparamsBase->at(i).size()==10));
    assert(EPTEparamsA->size()==5);
    for (int i=0; i<5; i++) assert((EPTEparamsA->at(i).size()==5)||(EPTEparamsA->at(i).size()==10));
    assert(EPTEparamsB->size()==5);
    for (int i=0; i<5; i++) assert((EPTEparamsB->at(i).size()==5)||(EPTEparamsB->at(i).size()==10));
    assert(EPTEparamsC->size()==5);
    for (int i=0; i<5; i++) assert((EPTEparamsC->at(i).size()==5)||(EPTEparamsC->at(i).size()==10));
    assert(EPTEparamsD->size()==5);
    for (int i=0; i<5; i++) assert((EPTEparamsD->at(i).size()==5)||(EPTEparamsD->at(i).size()==10));
    assert(EPTEparamsE->size()==5);
    for (int i=0; i<5; i++) assert((EPTEparamsE->at(i).size()==5)||(EPTEparamsE->at(i).size()==10));
    assert(EPTEparamsF->size()==5);
    for (int i=0; i<5; i++) assert((EPTEparamsF->at(i).size()==5)||(EPTEparamsF->at(i).size()==10));
    assert(EPTEparamsG->size()==5);
    for (int i=0; i<5; i++) assert((EPTEparamsG->at(i).size()==5)||(EPTEparamsG->at(i).size()==10));
    assert(EPTEparamsH->size()==5);
    for (int i=0; i<5; i++) assert((EPTEparamsH->at(i).size()==5)||(EPTEparamsH->at(i).size()==10));
    assert(EPTEparamsNorm->size()==5);
    for (int i=0; i<5; i++) assert(EPTEparamsNorm->at(i).size()==8);
  } else if (_uparaSplit==1) {
    assert(EPTEparamsBase->size()==10);
    for (int i=0; i<10; i++) assert((EPTEparamsBase->at(i).size()==5)||(EPTEparamsBase->at(i).size()==10));
    assert(EPTEparamsA->size()==10);
    for (int i=0; i<10; i++) assert((EPTEparamsA->at(i).size()==5)||(EPTEparamsA->at(i).size()==10));
    assert(EPTEparamsB->size()==10);
    for (int i=0; i<10; i++) assert((EPTEparamsB->at(i).size()==5)||(EPTEparamsB->at(i).size()==10));
    assert(EPTEparamsC->size()==10);
    for (int i=0; i<10; i++) assert((EPTEparamsC->at(i).size()==5)||(EPTEparamsC->at(i).size()==10));
    assert(EPTEparamsD->size()==10);
    for (int i=0; i<10; i++) assert((EPTEparamsD->at(i).size()==5)||(EPTEparamsD->at(i).size()==10));
    assert(EPTEparamsE->size()==10);
    for (int i=0; i<10; i++) assert((EPTEparamsE->at(i).size()==5)||(EPTEparamsE->at(i).size()==10));
    assert(EPTEparamsF->size()==10);
    for (int i=0; i<10; i++) assert((EPTEparamsF->at(i).size()==5)||(EPTEparamsF->at(i).size()==10));
    assert(EPTEparamsG->size()==10);
    for (int i=0; i<10; i++) assert((EPTEparamsG->at(i).size()==5)||(EPTEparamsG->at(i).size()==10));
    assert(EPTEparamsH->size()==10);
    for (int i=0; i<10; i++) assert((EPTEparamsH->at(i).size()==5)||(EPTEparamsH->at(i).size()==10));
    assert(EPTEparamsNorm->size()==10);
    for (int i=0; i<10; i++) assert(EPTEparamsNorm->at(i).size()==8);
    //
    for (int i=5; i<10; i++) {
      for (int ii=0; ii<8; ii++) {
	(EPTEparamsNorm->at(i).at(ii))*=_EPTEparamsRelGlobNorm;
      }
    }
    if (EPTEparamsNorm_CommonMultiplier) _EPTEparamsNorm_CommonMultiplier=*EPTEparamsNorm_CommonMultiplier;
    if (_EPTEparamsNorm_CommonMultiplier.size()) {
      for (int i=0; i<10; i++) {
	for (int ii=0; ii<8; ii++) {
	  (EPTEparamsNorm->at(i).at(ii))*=_EPTEparamsNorm_CommonMultiplier.at(ii);
	}
      }
    }
  }
  if (_useDataMCRatioHack==1){
    assert (DataRatioparams->size()==5);
    for (Int_t j=0; j <4; ++j){
      assert(DataRatioparams->at(j).size()==4);
      for (Int_t k=0; k <4; ++k)
        assert(DataRatioparams->at(j).at(k).size()==7);
    }
    assert (DataRatioparams2->size()==5);
    for (Int_t j=0; j <4; ++j){
      assert(DataRatioparams2->at(j).size()==4);
      for (Int_t k=0; k <4; ++k)
        assert(DataRatioparams2->at(j).at(k).size()==7);
    }
  }
  _EPTEparamsBase=(*EPTEparamsBase);
  _EPTEparamsA=(*EPTEparamsA);
  _EPTEparamsB=(*EPTEparamsB);
  _EPTEparamsC=(*EPTEparamsC);
  _EPTEparamsD=(*EPTEparamsD);
  _EPTEparamsE=(*EPTEparamsE);
  _EPTEparamsF=(*EPTEparamsF);
  _EPTEparamsG=(*EPTEparamsG);
  _EPTEparamsH=(*EPTEparamsH);
  _EPTEparamsNorm=(*EPTEparamsNorm);
  _DataRatioParams=(*DataRatioparams);
  _DataRatioParams2=(*DataRatioparams2);
  _DataRatioPTFit=(*DataRatioPTFit);
  _DataRatioLumiFit=(*DataRatioLumiFit);
  _DataHackPars=(*DataHackPars);
  // EC
  if (paramsEC&&EPTEparamsBase_EC) {
    if ((paramsEC->size()!=5)&&(paramsEC->size()!=10)) {
      std::cout<<"SETefficiencySmear initialised with wrong number of parameters (EC)."<<std::endl;
      assert(0);
    }
    _paramsEC=(*paramsEC);
    if (_uparaSplit==0) {
      assert(EPTEparamsBase_EC->size()==5);
      for (int i=0; i<5; i++) assert((EPTEparamsBase_EC->at(i).size()==5)||(EPTEparamsBase_EC->at(i).size()==10));
      assert(EPTEparamsA_EC->size()==5);
      for (int i=0; i<5; i++) assert((EPTEparamsA_EC->at(i).size()==5)||(EPTEparamsA_EC->at(i).size()==10));
      assert(EPTEparamsB_EC->size()==5);
      for (int i=0; i<5; i++) assert((EPTEparamsB_EC->at(i).size()==5)||(EPTEparamsB_EC->at(i).size()==10));
      assert(EPTEparamsC_EC->size()==5);
      for (int i=0; i<5; i++) assert((EPTEparamsC_EC->at(i).size()==5)||(EPTEparamsC_EC->at(i).size()==10));
      assert(EPTEparamsD_EC->size()==5);
      for (int i=0; i<5; i++) assert((EPTEparamsD_EC->at(i).size()==5)||(EPTEparamsD_EC->at(i).size()==10));
      assert(EPTEparamsE_EC->size()==5);
      for (int i=0; i<5; i++) assert((EPTEparamsE_EC->at(i).size()==5)||(EPTEparamsE_EC->at(i).size()==10));
      assert(EPTEparamsF_EC->size()==5);
      for (int i=0; i<5; i++) assert((EPTEparamsF_EC->at(i).size()==5)||(EPTEparamsF_EC->at(i).size()==10));
      assert(EPTEparamsG_EC->size()==5);
      for (int i=0; i<5; i++) assert((EPTEparamsG_EC->at(i).size()==5)||(EPTEparamsG_EC->at(i).size()==10));
      assert(EPTEparamsH_EC->size()==5);
      for (int i=0; i<5; i++) assert((EPTEparamsH_EC->at(i).size()==5)||(EPTEparamsH_EC->at(i).size()==10));
      assert(EPTEparamsNorm_EC->size()==5);
      for (int i=0; i<5; i++) assert(EPTEparamsNorm_EC->at(i).size()==8);
    } else if (_uparaSplit==1) {
      assert(EPTEparamsBase_EC->size()==10);
      for (int i=0; i<10; i++) assert((EPTEparamsBase_EC->at(i).size()==5)||(EPTEparamsBase_EC->at(i).size()==10));
      assert(EPTEparamsA_EC->size()==10);
      for (int i=0; i<10; i++) assert((EPTEparamsA_EC->at(i).size()==5)||(EPTEparamsA_EC->at(i).size()==10));
      assert(EPTEparamsB_EC->size()==10);
      for (int i=0; i<10; i++) assert((EPTEparamsB_EC->at(i).size()==5)||(EPTEparamsB_EC->at(i).size()==10));
      assert(EPTEparamsC_EC->size()==10);
      for (int i=0; i<10; i++) assert((EPTEparamsC_EC->at(i).size()==5)||(EPTEparamsC_EC->at(i).size()==10));
      assert(EPTEparamsD_EC->size()==10);
      for (int i=0; i<10; i++) assert((EPTEparamsD_EC->at(i).size()==5)||(EPTEparamsD_EC->at(i).size()==10));
      assert(EPTEparamsE_EC->size()==10);
      for (int i=0; i<10; i++) assert((EPTEparamsE_EC->at(i).size()==5)||(EPTEparamsE_EC->at(i).size()==10));
      assert(EPTEparamsF_EC->size()==10);
      for (int i=0; i<10; i++) assert((EPTEparamsF_EC->at(i).size()==5)||(EPTEparamsF_EC->at(i).size()==10));
      assert(EPTEparamsG_EC->size()==10);
      for (int i=0; i<10; i++) assert((EPTEparamsG_EC->at(i).size()==5)||(EPTEparamsG_EC->at(i).size()==10));
      assert(EPTEparamsH_EC->size()==10);
      for (int i=0; i<10; i++) assert((EPTEparamsH_EC->at(i).size()==5)||(EPTEparamsH_EC->at(i).size()==10));
      assert(EPTEparamsNorm_EC->size()==10);
      for (int i=0; i<10; i++) assert(EPTEparamsNorm_EC->at(i).size()==8);
      //
      for (int i=5; i<10; i++) {
	for (int ii=0; ii<8; ii++) {
	  (EPTEparamsNorm_EC->at(i).at(ii))*=_EPTEparamsRelGlobNorm_EC;
	}
      }
    }
    _EPTEparamsBase_EC=(*EPTEparamsBase_EC);
    _EPTEparamsA_EC=(*EPTEparamsA_EC);
    _EPTEparamsB_EC=(*EPTEparamsB_EC);
    _EPTEparamsC_EC=(*EPTEparamsC_EC);
    _EPTEparamsD_EC=(*EPTEparamsD_EC);
    _EPTEparamsE_EC=(*EPTEparamsE_EC);
    _EPTEparamsF_EC=(*EPTEparamsF_EC);
    _EPTEparamsG_EC=(*EPTEparamsG_EC);
    _EPTEparamsH_EC=(*EPTEparamsH_EC);
    _EPTEparamsNorm_EC=(*EPTEparamsNorm_EC);
  }

}


// constructor with CC/EC separation - for Z events
SETefficiencySmear::SETefficiencySmear(std::vector<float> paramsCCCC, std::vector<float> paramsCCEC, std::vector<float> paramsECEC, 
				       bool isScaled, float Scale, bool isRelative, bool doInterpolate,
				       int doPTEperturbation,
				       std::vector<float>* PTEparamsBase,
				       std::vector<float>* PTEparamsA, std::vector<float>* PTEparamsB,
				       std::vector<float>* PTEparamsC, std::vector<float>* PTEparamsD,
				       std::vector<float>* PTEparamsE, std::vector<float>* PTEparamsF,
				       std::vector<float>* PTEparamsG, std::vector<float>* PTEparamsH,
				       std::vector<float>* PTEparamsNorm,
				       std::vector< std::vector< std::vector<float> > >* DataRatioparams,
				       std::vector< std::vector< std::vector<float> > >* DataRatioparams2,
                                       std::vector< std::vector<float> >* DataHackPars,
				       std::vector<float>* DataRatioPTFit, std::vector<float>* DataRatioLumiFit,
				       std::vector<float>* PTEparamsBase_EC,
				       std::vector<float>* PTEparamsA_EC, std::vector<float>* PTEparamsB_EC,
				       std::vector<float>* PTEparamsC_EC, std::vector<float>* PTEparamsD_EC,
				       std::vector<float>* PTEparamsE_EC, std::vector<float>* PTEparamsF_EC,
				       std::vector<float>* PTEparamsG_EC, std::vector<float>* PTEparamsH_EC,
				       std::vector<float>* PTEparamsNorm_EC, int useHack, bool useLumiBins) {

  _uparaSplit=0;
  Init(paramsCCCC, isScaled, Scale, isRelative, doInterpolate,
       doPTEperturbation, PTEparamsBase,
       PTEparamsA, PTEparamsB, PTEparamsC, PTEparamsD, PTEparamsE, PTEparamsF, PTEparamsG, PTEparamsH,
       PTEparamsNorm, DataRatioparams, DataRatioparams2, DataHackPars, 
       DataRatioPTFit, DataRatioLumiFit, useHack, useLumiBins);
  _myConfig=2;
  //
  if ((paramsCCEC.size()!=5)&&(paramsCCEC.size()!=10)) {
    std::cout<<"SETefficiencySmear initialised with wrong number of parameters (CCEC)."<<std::endl;
    assert(0);
  }
  _paramsCCEC=paramsCCEC;
  assert((_paramsCCEC.size()==5)||(_paramsCCEC.size()==10));
  //
  if ((paramsECEC.size()!=5)&&(paramsECEC.size()!=10)) {
    std::cout<<"SETefficiencySmear initialised with wrong number of parameters (ECEC)."<<std::endl;
    assert(0);
  }
  _paramsECEC=paramsECEC;
  assert((_paramsECEC.size()==5)||(_paramsECEC.size()==10));
  //
  if (_doPTEperturbation==1) {
    assert(PTEparamsBase_EC->size()==5);
    assert(PTEparamsA_EC->size()==5);
    assert(PTEparamsB_EC->size()==5);
    assert(PTEparamsC_EC->size()==5);
    assert(PTEparamsD_EC->size()==5);
    assert(PTEparamsE_EC->size()==5);
    assert(PTEparamsF_EC->size()==5);
    assert(PTEparamsNorm_EC->size()==6);
    _PTEparamsBase_EC=(*PTEparamsBase_EC);
    _PTEparamsA_EC=(*PTEparamsA_EC);
    _PTEparamsB_EC=(*PTEparamsB_EC);
    _PTEparamsC_EC=(*PTEparamsC_EC);
    _PTEparamsD_EC=(*PTEparamsD_EC);
    _PTEparamsE_EC=(*PTEparamsE_EC);
    _PTEparamsF_EC=(*PTEparamsF_EC);
    _PTEparamsNorm_EC=(*PTEparamsNorm_EC);
  } else if (_doPTEperturbation==2) {
    assert((PTEparamsBase_EC->size()==5)||(PTEparamsBase_EC->size()==10));
    assert((PTEparamsA_EC->size()==5)||(PTEparamsA_EC->size()==10));
    assert((PTEparamsB_EC->size()==5)||(PTEparamsB_EC->size()==10));
    assert((PTEparamsC_EC->size()==5)||(PTEparamsC_EC->size()==10));
    assert((PTEparamsD_EC->size()==5)||(PTEparamsD_EC->size()==10));
    assert((PTEparamsE_EC->size()==5)||(PTEparamsE_EC->size()==10));
    assert((PTEparamsF_EC->size()==5)||(PTEparamsF_EC->size()==10));
    assert((PTEparamsG_EC->size()==5)||(PTEparamsG_EC->size()==10));
    assert((PTEparamsH_EC->size()==5)||(PTEparamsH_EC->size()==10));
    assert(PTEparamsNorm_EC->size()==8);
    _PTEparamsBase_EC=(*PTEparamsBase_EC);
    _PTEparamsA_EC=(*PTEparamsA_EC);
    _PTEparamsB_EC=(*PTEparamsB_EC);
    _PTEparamsC_EC=(*PTEparamsC_EC);
    _PTEparamsD_EC=(*PTEparamsD_EC);
    _PTEparamsE_EC=(*PTEparamsE_EC);
    _PTEparamsF_EC=(*PTEparamsF_EC);
    _PTEparamsG_EC=(*PTEparamsG_EC);
    _PTEparamsH_EC=(*PTEparamsH_EC);
    _PTEparamsNorm_EC=(*PTEparamsNorm_EC);
  }

  //gROOT->ProcessLine(TString(".x ../p20/seteff2.C"));
  //_hsetEff = (TH1D *)gROOT->FindObject("seteff2");
  //_hsetEff->Integral();	
  std::cout<<"Finished SETefficiencySmear initialisation Z CC/EC"<<std::endl;

}


// constructor with CC/EC separation and eta binning - for Z events
SETefficiencySmear::SETefficiencySmear(std::vector<float> paramsCCCC, std::vector<float> paramsCCEC, std::vector<float> paramsECEC,
                                       bool isScaled, float Scale, bool isRelative, bool doInterpolate,
                                       int uparaSplit, int doPTEperturbation,
                                       std::vector< std::vector<float> >* EPTEparamsBase,
                                       std::vector< std::vector<float> >* EPTEparamsA, std::vector< std::vector<float> >* EPTEparamsB,
                                       std::vector< std::vector<float> >* EPTEparamsC, std::vector< std::vector<float> >* EPTEparamsD,
                                       std::vector< std::vector<float> >* EPTEparamsE, std::vector< std::vector<float> >* EPTEparamsF,
                                       std::vector< std::vector<float> >* EPTEparamsG, std::vector< std::vector<float> >* EPTEparamsH,
                                       std::vector< std::vector<float> >* EPTEparamsNorm, std::vector<float>* EPTEparamsNorm_CommonMultiplier, float EPTEparamsRelGlobNorm,
                                       std::vector< std::vector< std::vector<float> > >* DataRatioparams,
                                       std::vector< std::vector< std::vector<float> > >* DataRatioparams2,
                                       std::vector< std::vector<float> >* DataHackPars,
                                       std::vector<float>* DataRatioPTFit, std::vector<float>* DataRatioLumiFit,
                                       std::vector< std::vector<float> >* EPTEparamsBase_EC,
                                       std::vector< std::vector<float> >* EPTEparamsA_EC, std::vector< std::vector<float> >* EPTEparamsB_EC,
                                       std::vector< std::vector<float> >* EPTEparamsC_EC, std::vector< std::vector<float> >* EPTEparamsD_EC,
                                       std::vector< std::vector<float> >* EPTEparamsE_EC, std::vector< std::vector<float> >* EPTEparamsF_EC,
                                       std::vector< std::vector<float> >* EPTEparamsG_EC, std::vector< std::vector<float> >* EPTEparamsH_EC,
                                       std::vector< std::vector<float> >* EPTEparamsNorm_EC, float EPTEparamsRelGlobNorm_EC,
				       int useHack, bool useLumiBins) {

  _uparaSplit=uparaSplit;
  _EPTEparamsRelGlobNorm=EPTEparamsRelGlobNorm;
  _EPTEparamsRelGlobNorm_EC=EPTEparamsRelGlobNorm_EC;
  Init(paramsCCCC, isScaled, Scale, isRelative, doInterpolate,
       doPTEperturbation,
       EPTEparamsBase,
       EPTEparamsA, EPTEparamsB, EPTEparamsC, EPTEparamsD, EPTEparamsE, EPTEparamsF, EPTEparamsG, EPTEparamsH,
       EPTEparamsNorm, EPTEparamsNorm_CommonMultiplier,
       DataRatioparams, DataRatioparams2, DataHackPars,
       DataRatioPTFit, DataRatioLumiFit, useHack, useLumiBins,
       &paramsCCCC, // hack
       EPTEparamsBase_EC,
       EPTEparamsA_EC, EPTEparamsB_EC, EPTEparamsC_EC, EPTEparamsD_EC, EPTEparamsE_EC, EPTEparamsF_EC, EPTEparamsG_EC, EPTEparamsH_EC,
       EPTEparamsNorm_EC);
  _myConfig=2;
  //
  if ((paramsCCEC.size()!=5)&&(paramsCCEC.size()!=10)) {
    std::cout<<"SETefficiencySmear initialised with wrong number of parameters (CCEC)."<<std::endl;
    assert(0);
  }
  _paramsCCEC=paramsCCEC;
  assert((_paramsCCEC.size()==5)||(_paramsCCEC.size()==10));
  //
  if ((paramsECEC.size()!=5)&&(paramsECEC.size()!=10)) {
    std::cout<<"SETefficiencySmear initialised with wrong number of parameters (ECEC)."<<std::endl;
    assert(0);
  }
  _paramsECEC=paramsECEC;
  assert((_paramsECEC.size()==5)||(_paramsECEC.size()==10));

}


// calculates the SET efficiency
double SETefficiencySmear::getSETeff(float SET, float lumi, float pTe, float pTe2, bool isEC, bool isEC2, float eta1, float eta2, float upara1, float upara2, TRandom3 *dummy, double *external_rnd2) {
  Float_t pick1 = 0.;
  if (dummy)
    pick1 = dummy->Uniform(0.,1.);
  if (external_rnd2){
    pick1 = external_rnd2[0];
  }
  std::vector<float>* params;
  if (_myConfig==0) {
    params=&_params;
  } else if (_myConfig==1) {
    if (isEC) params=&_paramsEC;
    else params=&_params;
  } else {
    if (isEC&&isEC2) {
      params=&_paramsECEC;
    } else if ((!isEC)&&(!isEC2)) {
      params=&_params;
    } else {
      params=&_paramsCCEC;
    }
  }

  float eff=1;
  if (!_isScaled) {
    float setX=SET;
    for (int i=0; i<5; i++) {
      eff+=(*params)[i]*setX;
      setX*=SET;
    }
    if (params->size()==10) {
      float eff2=(*params)[5];
      setX=SET;
      for (int i=6; i<10; i++) {
        eff2+=(*params)[i]*setX;
        setX*=SET;
      }
      eff*=eff2;
    }
  } else {
    float X=SET/_Scale;
    float setX=X;
    for (int i=0; i<5; i++) {
      eff+=(*params)[i]*setX;
      setX*=X;
    }
    if (params->size()==10) {
      float eff2=(*params)[5];
      setX=X;
      for (int i=6; i<10; i++) {
        eff2+=(*params)[i]*setX;
        setX*=X;
      }
      eff*=eff2;
    }
  }
  _probRaw=eff;
  if (_probRaw<0) _probRaw=0;
  _probCorr1=-10;
  _probCorr2=-10;

  if (_doPTEperturbation) {
    float effpert=1;
    if (!_doInterpolate) {
      int bin=(int)((pTe-25)/5);
      if (bin<0) bin=0;
      if (bin>5) {
	bin=5;
	if (_doPTEperturbation==2||_doPTEperturbation==3) {
	  if (pTe>60) bin=6;
	  if (pTe>70) bin=7;
	}
      }
      if (_doPTEperturbation==3) effpert=PertLookup(pTe,eta1,upara1,isEC,SET,bin);
      else effpert=PertLookup(pTe,isEC,SET,bin);
    } else {
      int bin1=0;
      int bin2=0;
      float d=0;
      InterpBinner(pTe,bin1,bin2,d);
      float effpert1;
      float effpert2;
      if (_doPTEperturbation==3) {
	effpert1=PertLookup(pTe,eta1,upara1,isEC,SET,bin1);
	effpert2=PertLookup(pTe,eta1,upara1,isEC,SET,bin2);
      } else {
	effpert1=PertLookup(pTe,isEC,SET,bin1);
	effpert2=PertLookup(pTe,isEC,SET,bin2);
      }
      effpert=effpert1+d*(effpert2-effpert1);
    }
    eff*=effpert;
    _probCorr1=effpert;
    if (!isEC && _useDataMCRatioHack && _useDataMCRatioHack<3){
      eff*=DataHack(SET, lumi, pTe, eta1);
      _probCorr1*=DataHack(SET, lumi, pTe, eta1);
    }
    else if (_useDataMCRatioHack==3){
      eff*=DataHack(SET, lumi, pTe, eta1);
      _probCorr1*=DataHack(SET, lumi, pTe, eta1);
    }
    if (_probCorr1<0) _probCorr1=0;
    //
    if (pTe2>0) {
      assert(_myConfig!=1);
      effpert=1;
      if (!_doInterpolate) {
	int bin2=(int)((pTe2-25)/5);
	if (bin2<0) bin2=0;
	if (bin2>5) {
	  bin2=5;
	  if (_doPTEperturbation==2||_doPTEperturbation==3) {
	    if (pTe2>60) bin2=6;
	    if (pTe2>70) bin2=7;
	  }
	}
	if (_doPTEperturbation==3) effpert=PertLookup(pTe2,eta2,upara2,isEC2,SET,bin2);
	else effpert=PertLookup(pTe2,isEC2,SET,bin2);
      } else {
	int bin1=0;
	int bin2=0;
	float d=0;
	InterpBinner(pTe2,bin1,bin2,d);
	float effpert1;
	float effpert2;
	if (_doPTEperturbation==3) {
	  effpert1=PertLookup(pTe2,eta2,upara2,isEC2,SET,bin1);
	  effpert2=PertLookup(pTe2,eta2,upara2,isEC2,SET,bin2);
	} else {
	  effpert1=PertLookup(pTe2,isEC2,SET,bin1);
	  effpert2=PertLookup(pTe2,isEC2,SET,bin2);
	}
	effpert=effpert1+d*(effpert2-effpert1);
      }
      eff*=effpert;
      _probCorr2=effpert;
      if (!isEC2 && _useDataMCRatioHack && _useDataMCRatioHack<3){
        if (!isEC){
          eff*=DataHack(SET, lumi,  pTe2,pTe, pick1);
          _probCorr2*=DataHack(SET, lumi, pTe2, pTe, pick1);
        }
        else{
          eff*=DataHack(SET, lumi,  pTe2, eta2);
          _probCorr2*=DataHack(SET, lumi, pTe2, eta2);
        }
      }
      else if (_useDataMCRatioHack==3){
        eff*=DataHack(SET, lumi, pTe2, eta2);
        _probCorr2*=DataHack(SET, lumi, pTe2, eta2);
      }
      
      if (_probCorr2<0) _probCorr2=0;
    }
  }

//   ////////////////////////// DEBUG
//   //
//   cout << "passesSETeff: SET=" << SET 
//        << ", &external_rnd=" << external_rnd
//        << " (val=" << (external_rnd ? *external_rnd : -1 )
//        << ")" << endl;
//   //
//   ////////////////////////// DEBUG
   
  return eff;
}

float SETefficiencySmear::PertLookup(float pTe, bool isEC, float SET, int bin) {

  std::vector<float>* PTEparams;
  std::vector<float>* PTEparamsBase;
  std::vector<float>* PTEparamsNorm;
  if (!isEC) {
    if (bin==0) {
      PTEparams=&_PTEparamsA;
    } else if (bin==1) {
      PTEparams=&_PTEparamsB;
    } else if (bin==2) {
      PTEparams=&_PTEparamsC;
    } else if (bin==3) {
      PTEparams=&_PTEparamsD;
    } else if (bin==4) {
      PTEparams=&_PTEparamsE;
    } else if (bin==5) {
      PTEparams=&_PTEparamsF;
    } else if (bin==6) {
      PTEparams=&_PTEparamsG;
    } else if (bin==7) {
      PTEparams=&_PTEparamsH;
    } else {
      assert(0);
    }
    PTEparamsBase=&_PTEparamsBase;
    PTEparamsNorm=&_PTEparamsNorm;
  } else {
    if (bin==0) {
      PTEparams=&_PTEparamsA_EC;
    } else if (bin==1) {
      PTEparams=&_PTEparamsB_EC;
    } else if (bin==2) {
      PTEparams=&_PTEparamsC_EC;
    } else if (bin==3) {
      PTEparams=&_PTEparamsD_EC;
    } else if (bin==4) {
      PTEparams=&_PTEparamsE_EC;
    } else if (bin==5) {
      PTEparams=&_PTEparamsF_EC;
    } else if (bin==6) {
      PTEparams=&_PTEparamsG_EC;
    } else if (bin==7) {
      PTEparams=&_PTEparamsH_EC;
    } else {
      assert(0);
    }
    PTEparamsBase=&_PTEparamsBase_EC;
    PTEparamsNorm=&_PTEparamsNorm_EC;
  }

  return PertCalc(pTe,SET,bin,PTEparams,PTEparamsBase,PTEparamsNorm);

}


float SETefficiencySmear::PertLookup(float pTe, float eta, float upara, bool isEC, float SET, int bin) {

  std::vector< std::vector<float> >* EPTEparams;
  std::vector< std::vector<float> >* EPTEparamsBase;
  std::vector< std::vector<float> >* EPTEparamsNorm;
  if (!isEC) {
    if (bin==0) {
      EPTEparams=&_EPTEparamsA;
    } else if (bin==1) {
      EPTEparams=&_EPTEparamsB;
    } else if (bin==2) {
      EPTEparams=&_EPTEparamsC;
    } else if (bin==3) {
      EPTEparams=&_EPTEparamsD;
    } else if (bin==4) {
      EPTEparams=&_EPTEparamsE;
    } else if (bin==5) {
      EPTEparams=&_EPTEparamsF;
    } else if (bin==6) {
      EPTEparams=&_EPTEparamsG;
    } else if (bin==7) {
      EPTEparams=&_EPTEparamsH;
    } else {
      assert(0);
    }
    EPTEparamsBase=&_EPTEparamsBase;
    EPTEparamsNorm=&_EPTEparamsNorm;
  } else {
    if (bin==0) {
      EPTEparams=&_EPTEparamsA_EC;
    } else if (bin==1) {
      EPTEparams=&_EPTEparamsB_EC;
    } else if (bin==2) {
      EPTEparams=&_EPTEparamsC_EC;
    } else if (bin==3) {
      EPTEparams=&_EPTEparamsD_EC;
    } else if (bin==4) {
      EPTEparams=&_EPTEparamsE_EC;
    } else if (bin==5) {
      EPTEparams=&_EPTEparamsF_EC;
    } else if (bin==6) {
      EPTEparams=&_EPTEparamsG_EC;
    } else if (bin==7) {
      EPTEparams=&_EPTEparamsH_EC;
    } else {
      assert(0);
    }
    EPTEparamsBase=&_EPTEparamsBase_EC;
    EPTEparamsNorm=&_EPTEparamsNorm_EC;
  }

  int theBin=(Int_t)(fabs(eta)/0.2);
  if (theBin>4) theBin=4;
  if (_uparaSplit==1) {
    if (upara>0) theBin+=5;
  }
  return PertCalc(pTe,SET,bin,&(EPTEparams->at(theBin)),&(EPTEparamsBase->at(theBin)),&(EPTEparamsNorm->at(theBin)));

}


float SETefficiencySmear::PertCalc(float pTe, float SET, int bin,
                                   std::vector<float>* PTEparams, std::vector<float>* PTEparamsBase, std::vector<float>* PTEparamsNorm) {

  float base=1;
  float here=1;
  float X=SET/_Scale;
  if (_isRelative) X/=pTe;
  float setX=X;
  for (int i=0; i<5; i++) {
    base+=(*PTEparamsBase)[i]*setX;
    here+=(*PTEparams)[i]*setX;
    setX*=X;
  }
  if (PTEparamsBase->size()==10) {
    assert(PTEparams->size()==10);
    float baseB=1;
    float hereB=1;
    float XB=SET/_Scale;
    if (_isRelative) XB/=pTe;
    float setXB=X;
    for (int i=5; i<10; i++) {
      baseB+=(*PTEparamsBase)[i]*setXB;
      hereB+=(*PTEparams)[i]*setXB;
      setXB*=XB;
    }
    base*=baseB;
    here*=hereB;
  }
  float effcorr=(here/base*(*PTEparamsNorm)[bin]);

  return effcorr;

}

void SETefficiencySmear::InterpBinner(float pTe, int& bin1, int& bin2, float& d) {
  if (pTe<25) {
    bin1=0;
    bin2=0;
    d=0;
  } else if (pTe<32.5) {
    bin1=0;
    bin2=1;
    d=(pTe-27.5)/5;
  } else if (pTe<37.5) {
    bin1=1;
    bin2=2;
    d=(pTe-32.5)/5;
  } else if (pTe<42.5) {
    bin1=2;
    bin2=3;
    d=(pTe-37.5)/5;
  } else if (pTe<47.5) {
    bin1=3;
    bin2=4;
    d=(pTe-42.5)/5;
  } else {
    if (_doPTEperturbation==2||_doPTEperturbation==3) {
      if (pTe<55) {
        bin1=4;
        bin2=5;
        d=(pTe-47.5)/7.5;
      } else if (pTe<65) {
        bin1=5;
        bin2=6;
        d=(pTe-55)/10;
      } else if (pTe<70) {
        bin1=6;
        bin2=7;
        d=(pTe-65)/5;
      } else {
        bin1=7;
        bin2=7;
        d=0;
      }
    } else {
      if (pTe<50) {
        bin1=4;
        bin2=5;
        d=(pTe-47.5)/2.5;
      } else {
        bin1=5;
        bin2=5;
        d=0;
      }
    }
  }
  return;
}

// flip an efficiency
// optional: external_rnd is a pointer to the external random number value
bool SETefficiencySmear::passesSETeff(float SET, float lumi, TRandom3 *dummy, double *external_rnd, float pTe, float pTe2, bool isEC, bool isEC2, float eta1, float eta2, float upara1, float upara2) {
  double *extrnd2 =0;
  if (external_rnd)
    extrnd2 = &external_rnd[1];
  double eff = getSETeff(SET, lumi,  pTe, pTe2, isEC, isEC2, eta1, eta2, upara1, upara2, dummy, extrnd2);
  if (external_rnd) {
    _theRnd=external_rnd[0];
    if(external_rnd[0]<(eff)) return true;
  } else {
    _theRnd=dummy->Uniform(0.,1.);
    if(_theRnd<(eff)) return true;
  }
  return false;
}

double SETefficiencySmear::DataHack(float SET, float lumi,  float ept, float deteta){

  if (_useDataMCRatioHack==1) {

    if (SET > 300.)
      return DataHack(299.,lumi, ept, deteta);
    const Int_t NSET = 7;
    const Int_t NLUM = 6; 
    const Int_t NPT  = 4;
  
    Double_t setbins[] = {0, 30., 50., 80., 110., 140., 200., 300.};
    Double_t ptbins[] = {25.,35.,45.5,55.,100.};
    Double_t lumibins[] = {0, 1.5, 3.0, 4.5, 6.0, 7.5, 10. };
    Int_t setbin =0;
    Int_t ptbin=0;
  
    Int_t lumibin=0;
  
    while (lumi > lumibins[lumibin+1]){
      ++lumibin;
      if (lumibin==(NLUM-1))
	break;
    }
  
    while (SET > setbins[setbin+1]){
      ++setbin;
      if (setbin==(NSET-1))
	break;
    }
    while (ept > ptbins[ptbin+1]){
      //std::cout << setbin << "   " << ptbin << "   " << ptbinhigh[setbin][ptbin] << std::endl;
      ++ptbin;
      if (ptbin==(NPT-1))
	break;
    }
    if (!_useLumiBins)
      lumibin=NLUM;
    return _DataRatioParams.at(lumibin).at(setbin).at(ptbin);

  } 
  else if (_useDataMCRatioHack==2) {

    const Int_t NLUM = 6;
    Double_t lumibins[] = {0, 1.5, 3.0, 4.5, 6.0, 7.5, 10. };

    Int_t lumibin=0;
    while (lumi > lumibins[lumibin+1]){
      ++lumibin;
      if (lumibin==(NLUM-1))
        break;
    }

    double Addtl=1;
    if (lumi>1.4) {
      Addtl=1+_DataRatioLumiFit.at(0)*(lumi/20.)+_DataRatioLumiFit.at(1)*pow(lumi/20.,2)+_DataRatioLumiFit.at(2)*pow(lumi/20.,3)+_DataRatioLumiFit.at(3)*pow(lumi/20.,4)+_DataRatioLumiFit.at(4)*pow(lumi/20.,5);
    }

    return Addtl*_DataRatioPTFit.at(2*lumibin)+_DataRatioPTFit.at(2*lumibin+1)*log(ept);

  }
  else if (_useDataMCRatioHack==3){
    double ratio_pt=0., ratio_set=0., ratio_lumi=0., ratio_deteta=0.;

    if (ept<25.) ept = 25.5;
    if (ept>65.) ept = 64.9;


    int nParPt = _DataHackPars.at(0).size();
    for (int i=0; i<nParPt; i++){
      ratio_pt += _DataHackPars.at(0).at(i)*pow(ept,i);
    }
   
    int nParSET = _DataHackPars.at(1).size();
    for (int i=0; i<nParSET; i++){
      ratio_set += _DataHackPars.at(1).at(i)*pow(SET,i);
    }

    int nParLumi = _DataHackPars.at(2).size();
    for (int i=0; i<nParLumi; i++){
      ratio_lumi += _DataHackPars.at(2).at(i)*pow(lumi,i);
    }

    int nParDetEta = _DataHackPars.at(3).size();
    for (int i=0; i<nParDetEta; i++){
      ratio_deteta += _DataHackPars.at(3).at(i)*pow(deteta,i);
    }

    //std::cout << " -- Hengne :: ept=" << ept << "; ratio_pt=" << ratio_pt<< "; SET=" << SET << "; ratio_set=" << ratio_set << "; lumi=" << lumi << "; ratio_lumi=" << ratio_lumi << std::endl;
    double ratio = ratio_pt*ratio_set*ratio_lumi*ratio_deteta;
    if (ratio>1.0) ratio = 1.0;
    return ratio;
  }
  return 1;
}

double SETefficiencySmear::DataHack(float SET, float lumi, float ept2, float ept, float pick1){
  
  if (SET > 300.)
    return DataHack(299., lumi, ept2, ept, pick1);
  const Int_t NSET = 7;
  const Int_t NLUM = 6; 
  const Int_t NPT  = 4;
  
  Double_t setbins[] = {0, 30., 50., 80., 110., 140., 200., 300.};
  Double_t ptbins[] = {25.,35.,45.5,55.,100.};
  Double_t lumibins[] = {0, 1.5, 3.0, 4.5, 6.0, 7.5, 10. };
  

  Int_t setbin =0;
  Int_t ptbin=0;
  Int_t ptbin2=0;
  Int_t lumibin=0;

  while (lumi > lumibins[lumibin+1]){
    ++lumibin;
    if (lumibin==(NLUM-1))
      break;
  }
  

  while (SET > setbins[setbin+1]){
    ++setbin;
    if (setbin==NSET-1)
      break;
  }
  while (ept > ptbins[ptbin+1]){
    //std::cout << setbin << "   " << ptbin << "   " << ptbinhigh[setbin][ptbin] << std::endl;
    ++ptbin;
    if (ptbin==(NPT-1))
      break;
  }
  
  while (ept2 > ptbins[ptbin2+1]){
    //std::cout << setbin << "   " << ptbin << "   " << ptbinhigh[setbin][ptbin] << std::endl;
    ++ptbin2;
    if (ptbin2==(NPT-1))
      break;
  }
  
  // std::cout << " Lumi = " << lumi << " pt2 = " << ept2 << " SET = " << SET << std::endl;
  // std::cout << " Lumibin = " << lumibin << " ptbin2 = " << ptbin2 << " SET bin = " << setbin << std::endl;
  if (!_useLumiBins)
    lumibin=NLUM;
  float eff1 = _DataRatioParams.at(lumibin).at(setbin).at(ptbin)*_DataRatioParams2.at(lumibin).at(setbin).at(ptbin2);
  float eff2 =  _DataRatioParams.at(lumibin).at(setbin).at(ptbin2)*_DataRatioParams2.at(lumibin).at(setbin).at(ptbin);
  
  if (_DataRatioParams.at(lumibin).at(setbin).at(ptbin) == 0.)
    return _DataRatioParams.at(lumibin).at(setbin).at(ptbin2);
      
  if (pick1 > 0.5)
    return (eff1 /_DataRatioParams.at(lumibin).at(setbin).at(ptbin)) ;
  else
    return (eff2/_DataRatioParams.at(lumibin).at(setbin).at(ptbin)) ;
}


bool SETefficiencySmear::passesFirst() {

  assert(_doPTEperturbation&&(_probCorr2>-9.5));
  if (_probRaw>-100) flipIndividual();

  return _pass1;

}

bool SETefficiencySmear::passesSecond() {

  assert(_doPTEperturbation&&(_probCorr2>-9.5));
  if (_probRaw>-100) flipIndividual();

  return _pass2;

}

void SETefficiencySmear::flipIndividual() {

  assert(_doPTEperturbation&&(_probCorr2>-9.5));

  if (_probRaw<0) {
    _pass1=false;
    _pass2=false;
    return;
  }

  float Eff=_probRaw*_probCorr1*_probCorr2;
  if (_theRnd<Eff) {
    _pass1=true;
    _pass2=true;
  } else {
    float Config01=(1-sqrt(_probRaw)*_probCorr1)*sqrt(_probRaw)*_probCorr2;
    if ((_theRnd-Eff)<Config01) {
      _pass1=false;
      _pass2=true;
    } else {
      float Config10=(1-sqrt(_probRaw)*_probCorr2)*sqrt(_probRaw)*_probCorr1;
      if ((_theRnd-Eff-Config01)<Config10) {
	_pass1=true;
	_pass2=false;
      } else {
	_pass1=false;
	_pass2=false;
      }
    }
  }

  if (_probCorr1<0) _pass1=false;
  if (_probCorr2<0) _pass2=false;

  _probRaw=-1000;
  return;

}


