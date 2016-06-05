#ifndef INC_SETEFFICIENCYSMEAR_LUMIDISPATCH
#define INC_SETEFFICIENCYSMEAR_LUMIDISPATCH

#include "SETefficiencySmear_base.hpp"
#include "SETefficiencySmear.hpp"
#include "PParameterReader.hpp"

class SETefficiencySmear_LumiDispatch : public SETefficiencySmear_base {
  
 public:

  // constructor
  SETefficiencySmear_LumiDispatch(TString parameter_filename, bool isW, std::vector<float>* lumibins, std::vector<float>* luminorm, std::vector<float>* luminorm2 = 0, std::vector<float>* luminorm3 = 0);

  // destructor
  ~SETefficiencySmear_LumiDispatch(){;}

  // flip an efficiency
  // (optional) external_rnd is a pointer to the external random number value
  bool passesSETeff(float SET, float lumi, TRandom3 *dummy, double *external_rnd=0, float pTe=-10, float pTe2=-10, bool isEC=false, bool isEC2=false, float eta1=-10, float eta2=-10, float upara1=-1, float upara2=-1);

  // calculates the SET efficiency.
  double getSETeff(float SET, float lumi, float pTe=-10, float pTe2=-10, bool isEC=false, bool isEC2=false, float eta1=-10, float eta2=-10, float upara1=-1, float upara2=-1, TRandom3 *dummy=0, double *external_rnd2=0);

  // special accessors for those who would like to interpret the SET efficiency as a per-electron efficiency
  bool passesFirst();
  bool passesSecond();

  void InterpBinner(float pTe, int& bin1, int& bin2, float& d);

private:

  bool _isW;

  std::vector<float> _lumibins;
  std::vector<float> _luminorm;
  std::vector<float> _luminormCCCC;
  std::vector<float> _luminormCCEC;
  std::vector<float> _luminormECEC;
  SETefficiencySmear* _workers[10];

  bool _pass1;
  bool _pass2;

};

#endif
 
