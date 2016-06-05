#ifndef INC_SETEFFICIENCYSMEAR
#define INC_SETEFFICIENCYSMEAR

#include "SETefficiencySmear_base.hpp"

#include <vector>
#include <TH1D.h>

class TRandom3;

class SETefficiencySmear: public SETefficiencySmear_base {
  
 public:

  // constructor
  SETefficiencySmear(std::vector<float> params, bool isScaled=false, float Scale=200., bool isRelative=false, bool doInterpolate=false,
		     int doPTEperturbation=0, std::vector<float>* PTEparamsBase=0,
		     std::vector<float>* PTEparamsA=0, std::vector<float>* PTEparamsB=0,
		     std::vector<float>* PTEparamsC=0, std::vector<float>* PTEparamsD=0,
		     std::vector<float>* PTEparamsE=0, std::vector<float>* PTEparamsF=0,
		     std::vector<float>* PTEparamsG=0, std::vector<float>* PTEparamsH=0,
		     std::vector<float>* PTEparamsNorm=0,
		     std::vector< std::vector< std::vector<float> > >* DataRatioparams=0, std::vector< std::vector< std::vector<float> > >* DataRatioparams2=0,
                     std::vector< std::vector<float> >* DataHackPars=0,
		     std::vector<float>* DataRatioPTFit=0, std::vector<float>* DataRatioLumiFit=0,		     
		     int useHack=0, bool useLumiBins=false);

  // constructor with CC/EC separation - for W events
  SETefficiencySmear(std::vector<float> paramsCC, std::vector<float> paramsEC, 
		     bool isScaled=false, float Scale=200., bool isRelative=false, bool doInterpolate=false,
                     int doPTEperturbation=0, 
		     std::vector<float>* PTEparamsBase=0,
                     std::vector<float>* PTEparamsA=0, std::vector<float>* PTEparamsB=0,
                     std::vector<float>* PTEparamsC=0, std::vector<float>* PTEparamsD=0,
                     std::vector<float>* PTEparamsE=0, std::vector<float>* PTEparamsF=0,
                     std::vector<float>* PTEparamsG=0, std::vector<float>* PTEparamsH=0,
                     std::vector<float>* PTEparamsNorm=0,
		     std::vector< std::vector< std::vector<float> > >* DataRatioparams=0,
		     std::vector< std::vector< std::vector<float> > >* DataRatioparams2=0,
                     std::vector< std::vector<float> >* DataHackPars=0,
		     std::vector<float>* DataRatioPTFit=0, std::vector<float>* DataRatioLumiFit=0,
		     std::vector<float>* PTEparamsBase_EC=0,
                     std::vector<float>* PTEparamsA_EC=0, std::vector<float>* PTEparamsB_EC=0,
                     std::vector<float>* PTEparamsC_EC=0, std::vector<float>* PTEparamsD_EC=0,
                     std::vector<float>* PTEparamsE_EC=0, std::vector<float>* PTEparamsF_EC=0,
                     std::vector<float>* PTEparamsG_EC=0, std::vector<float>* PTEparamsH_EC=0,
                     std::vector<float>* PTEparamsNorm_EC=0, int useHack=0, bool useLumiBins=false);

  // constructor with CC/EC separation and eta binning - for W events
  SETefficiencySmear(std::vector<float> paramsCC, std::vector<float> paramsEC,
                     bool isScaled=false, float Scale=200., bool isRelative=false, bool doInterpolate=false,
                     int uparaSplit=0, int doPTEperturbation=0,
                     std::vector< std::vector<float> >* EPTEparamsBase=0,
                     std::vector< std::vector<float> >* EPTEparamsA=0, std::vector< std::vector<float> >* EPTEparamsB=0,
                     std::vector< std::vector<float> >* EPTEparamsC=0, std::vector< std::vector<float> >* EPTEparamsD=0,
                     std::vector< std::vector<float> >* EPTEparamsE=0, std::vector< std::vector<float> >* EPTEparamsF=0,
                     std::vector< std::vector<float> >* EPTEparamsG=0, std::vector< std::vector<float> >* EPTEparamsH=0,
                     std::vector< std::vector<float> >* EPTEparamsNorm=0, float EPTEparamsRelGlobNorm=1,
                     std::vector< std::vector< std::vector<float> > >* DataRatioparams=0,
                     std::vector< std::vector< std::vector<float> > >* DataRatioparams2=0,
                     std::vector< std::vector<float> >* DataHackPars=0,
		     std::vector<float>* DataRatioPTFit=0, std::vector<float>* DataRatioLumiFit=0,
		     int useHack=0, bool useLumiBins=false,
                     std::vector< std::vector<float> >* EPTEparamsBase_EC=0,
                     std::vector< std::vector<float> >* EPTEparamsA_EC=0, std::vector< std::vector<float> >* EPTEparamsB_EC=0,
                     std::vector< std::vector<float> >* EPTEparamsC_EC=0, std::vector< std::vector<float> >* EPTEparamsD_EC=0,
                     std::vector< std::vector<float> >* EPTEparamsE_EC=0, std::vector< std::vector<float> >* EPTEparamsF_EC=0,
                     std::vector< std::vector<float> >* EPTEparamsG_EC=0, std::vector< std::vector<float> >* EPTEparamsH_EC=0,
                     std::vector< std::vector<float> >* EPTEparamsNorm_EC=0, float EPTEparamsRelGlobNorm_EC=1);

  // constructor with CC/EC separation - for Z events
  SETefficiencySmear(std::vector<float> paramsCCCC, std::vector<float> paramsCCEC, std::vector<float> paramsECEC, 
		     bool isScaled=false, float Scale=200., bool isRelative=false, bool doInterpolate=false,
		     int doPTEperturbation=0,
                     std::vector<float>* PTEparamsBase=0,
                     std::vector<float>* PTEparamsA=0, std::vector<float>* PTEparamsB=0,
                     std::vector<float>* PTEparamsC=0, std::vector<float>* PTEparamsD=0,
                     std::vector<float>* PTEparamsE=0, std::vector<float>* PTEparamsF=0,
                     std::vector<float>* PTEparamsG=0, std::vector<float>* PTEparamsH=0,
                     std::vector<float>* PTEparamsNorm=0, 
		     std::vector< std::vector< std::vector<float> > >* DataRatioparams=0,
		     std::vector< std::vector< std::vector<float> > >* DataRatioparams2=0,
                     std::vector< std::vector<float> >* DataHackPars=0,
		     std::vector<float>* DataRatioPTFit=0, std::vector<float>* DataRatioLumiFit=0,
                     std::vector<float>* PTEparamsBase_EC=0,
                     std::vector<float>* PTEparamsA_EC=0, std::vector<float>* PTEparamsB_EC=0,
                     std::vector<float>* PTEparamsC_EC=0, std::vector<float>* PTEparamsD_EC=0,
                     std::vector<float>* PTEparamsE_EC=0, std::vector<float>* PTEparamsF_EC=0,
                     std::vector<float>* PTEparamsG_EC=0, std::vector<float>* PTEparamsH_EC=0,
                     std::vector<float>* PTEparamsNorm_EC=0, int useHack=0, bool useLumiBins=false);

  // constructor with CC/EC separation and eta binning - for Z events
  SETefficiencySmear(std::vector<float> paramsCCCC, std::vector<float> paramsCCEC, std::vector<float> paramsECEC,
                     bool isScaled=false, float Scale=200., bool isRelative=false, bool doInterpolate=false,
                     int uparaSplit=0, int doPTEperturbation=0,
		     std::vector< std::vector<float> >* EPTEparamsBase=0,
                     std::vector< std::vector<float> >* EPTEparamsA=0, std::vector< std::vector<float> >* EPTEparamsB=0,
                     std::vector< std::vector<float> >* EPTEparamsC=0, std::vector< std::vector<float> >* EPTEparamsD=0,
                     std::vector< std::vector<float> >* EPTEparamsE=0, std::vector< std::vector<float> >* EPTEparamsF=0,
                     std::vector< std::vector<float> >* EPTEparamsG=0, std::vector< std::vector<float> >* EPTEparamsH=0,
                     std::vector< std::vector<float> >* EPTEparamsNorm=0, std::vector<float>* EPTEparamsNorm_CommonMultiplier=0, float EPTEparamsRelGlobNorm=1,
                     std::vector< std::vector< std::vector<float> > >* DataRatioparams=0,
                     std::vector< std::vector< std::vector<float> > >* DataRatioparams2=0,
                     std::vector< std::vector<float> >* DataHackPars=0,
                     std::vector<float>* DataRatioPTFit=0, std::vector<float>* DataRatioLumiFit=0,
                     std::vector< std::vector<float> >* EPTEparamsBase_EC=0,
                     std::vector< std::vector<float> >* EPTEparamsA_EC=0, std::vector< std::vector<float> >* EPTEparamsB_EC=0,
                     std::vector< std::vector<float> >* EPTEparamsC_EC=0, std::vector< std::vector<float> >* EPTEparamsD_EC=0,
                     std::vector< std::vector<float> >* EPTEparamsE_EC=0, std::vector< std::vector<float> >* EPTEparamsF_EC=0,
                     std::vector< std::vector<float> >* EPTEparamsG_EC=0, std::vector< std::vector<float> >* EPTEparamsH_EC=0,
                     std::vector< std::vector<float> >* EPTEparamsNorm_EC=0, float EPTEparamsRelGlobNorm_EC=1,
                     int useHack=0, bool useLumiBins=false);

  // destructor
  ~SETefficiencySmear(){;}

  // flip an efficiency
  // (optional) external_rnd is a pointer to the external random number value
  bool passesSETeff(float SET, float lumi, TRandom3 *dummy, double *external_rnd=NULL, float pTe=-10, float pTe2=-10, bool isEC=false, bool isEC2=false, float eta1=-10, float eta2=-10, float upara1=-1, float upara2=-1);

  // calculates the SET efficiency. I separated this function from the passesSETeff() function, so that an external program                                                      // could access this class and use it to get the efficiency value.                                                                                                             //MW
  double getSETeff(float SET, float lumi, float pTe=-10, float pTe2=-10, bool isEC=false, bool isEC2=false, float eta1=-10, float eta2=-10, float upara1=-1, float upara2=-1, TRandom3 *dummy=0, double *external_rnd2=0);

  // special accessors for those who would like to interpret the SET efficiency as a per-electron efficiency
  bool passesFirst();
  bool passesSecond();
 private:
  double DataHack(float SET, float lumi,  float ept, float deteta);
  double DataHack(float SET, float lumi, float ept2, float ept, float pick1);
  void Init(std::vector<float> params, bool isScaled, float Scale, bool isRelative, bool doInterpolate,
            int doPTEperturbation, std::vector<float>* PTEparamsBase,
            std::vector<float>* PTEparamsA, std::vector<float>* PTEparamsB,
            std::vector<float>* PTEparamsC, std::vector<float>* PTEparamsD,
            std::vector<float>* PTEparamsE, std::vector<float>* PTEparamsF,
            std::vector<float>* PTEparamsG, std::vector<float>* PTEparamsH,
            std::vector<float>* PTEparamsNorm,
	    std::vector< std::vector< std::vector<float> > >* DataRatioparams, std::vector< std::vector< std::vector<float> > >* DataRatioparams2,
            std::vector< std::vector<float> >* DataHackPars,
	    std::vector<float>* DataRatioPTFit, std::vector<float>* DataRatioLumiFit,
	    int useHack, bool useLumiBins);
  void Init(std::vector<float> params, bool isScaled, float Scale, bool isRelative, bool doInterpolate,
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
	    std::vector<float>* paramsEC=0,
	    std::vector< std::vector<float> >* EPTEparamsBase_EC=0,
            std::vector< std::vector<float> >* EPTEparamsA_EC=0, std::vector< std::vector<float> >* EPTEparamsB_EC=0,
            std::vector< std::vector<float> >* EPTEparamsC_EC=0, std::vector< std::vector<float> >* EPTEparamsD_EC=0,
            std::vector< std::vector<float> >* EPTEparamsE_EC=0, std::vector< std::vector<float> >* EPTEparamsF_EC=0,
            std::vector< std::vector<float> >* EPTEparamsG_EC=0, std::vector< std::vector<float> >* EPTEparamsH_EC=0,
            std::vector< std::vector<float> >* EPTEparamsNorm_EC=0);

  void flipIndividual();

  float PertLookup(float pTe, bool isEC, float SET, int bin);
  float PertLookup(float pTe, float eta, float upara, bool isEC, float SET, int bin);
  float PertCalc(float pTe, float SET, int bin, std::vector<float>* PTEparams, std::vector<float>* PTEparamsBase, std::vector<float>* PTEparamsNorm);

public:
  void InterpBinner(float pTe, int& bin1, int& bin2, float& d);

private:

  int _myConfig;
  int _uparaSplit;

  bool _isScaled;
  float _Scale;
  bool _isRelative;
  bool _doInterpolate;

  int _useDataMCRatioHack;
  bool _useLumiBins;

  std::vector<float> _params;
  //
  std::vector<float> _paramsEC;
  //
  std::vector<float> _paramsCCEC;
  std::vector<float> _paramsECEC;

  int _doPTEperturbation;
  //
  //
  std::vector<float> _PTEparamsBase;
  std::vector<float> _PTEparamsA;
  std::vector<float> _PTEparamsB;
  std::vector<float> _PTEparamsC;
  std::vector<float> _PTEparamsD;
  std::vector<float> _PTEparamsE;
  std::vector<float> _PTEparamsF;
  std::vector<float> _PTEparamsG;
  std::vector<float> _PTEparamsH;
  std::vector<float> _PTEparamsNorm;
  //
  std::vector<float> _PTEparamsBase_EC;
  std::vector<float> _PTEparamsA_EC;
  std::vector<float> _PTEparamsB_EC;
  std::vector<float> _PTEparamsC_EC;
  std::vector<float> _PTEparamsD_EC;
  std::vector<float> _PTEparamsE_EC;
  std::vector<float> _PTEparamsF_EC;
  std::vector<float> _PTEparamsG_EC;
  std::vector<float> _PTEparamsH_EC;
  std::vector<float> _PTEparamsNorm_EC;
  //
  //
  std::vector< std::vector<float> > _EPTEparamsBase;
  std::vector< std::vector<float> > _EPTEparamsA;
  std::vector< std::vector<float> > _EPTEparamsB;
  std::vector< std::vector<float> > _EPTEparamsC;
  std::vector< std::vector<float> > _EPTEparamsD;
  std::vector< std::vector<float> > _EPTEparamsE;
  std::vector< std::vector<float> > _EPTEparamsF;
  std::vector< std::vector<float> > _EPTEparamsG;
  std::vector< std::vector<float> > _EPTEparamsH;
  std::vector< std::vector<float> > _EPTEparamsNorm;
  std::vector<float> _EPTEparamsNorm_CommonMultiplier;
  float _EPTEparamsRelGlobNorm;
  //
  std::vector< std::vector<float> > _EPTEparamsBase_EC;
  std::vector< std::vector<float> > _EPTEparamsA_EC;
  std::vector< std::vector<float> > _EPTEparamsB_EC;
  std::vector< std::vector<float> > _EPTEparamsC_EC;
  std::vector< std::vector<float> > _EPTEparamsD_EC;
  std::vector< std::vector<float> > _EPTEparamsE_EC;
  std::vector< std::vector<float> > _EPTEparamsF_EC;
  std::vector< std::vector<float> > _EPTEparamsG_EC;
  std::vector< std::vector<float> > _EPTEparamsH_EC;
  std::vector< std::vector<float> > _EPTEparamsNorm_EC;
  float _EPTEparamsRelGlobNorm_EC;

  std::vector< std::vector< std::vector<float> > >_DataRatioParams;
  std::vector< std::vector< std::vector<float> > >_DataRatioParams2;

  std::vector< std::vector<float> > _DataHackPars;

  std::vector<float> _DataRatioPTFit;
  std::vector<float> _DataRatioLumiFit;

  TH1D* _hsetEff;
  bool _pass1;
  bool _pass2;
  float _probRaw;
  float _probCorr1;
  float _probCorr2;
  float _theRnd;

};



#endif
 
