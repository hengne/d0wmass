#ifndef INC_SETEFFICIENCYSMEAR_BASE
#define INC_SETEFFICIENCYSMEAR_BASE

class TRandom3;

class SETefficiencySmear_base {
  
 public:

  // constructor
  SETefficiencySmear_base();

  // destructor
  ~SETefficiencySmear_base(){;}

  // flip an efficiency
  // (optional) external_rnd is a pointer to the external random number value
  virtual bool passesSETeff(float SET, float lumi, TRandom3 *dummy, double *external_rnd=0, float pTe=-10, float pTe2=-10, bool isEC=false, bool isEC2=false, float eta1=-10, float eta2=-10, float upara1=-1, float upara2=-1);

  // calculates the SET efficiency.
  virtual double getSETeff(float SET, float lumi, float pTe=-10, float pTe2=-10, bool isEC=false, bool isEC2=false, float eta1=-10, float eta2=-10, float upara1=-1, float upara2=-1, TRandom3 *dummy=0, double *external_rnd2=0);

  // special accessors for those who would like to interpret the SET efficiency as a per-electron efficiency
  virtual bool passesFirst();
  virtual bool passesSecond();

  virtual void InterpBinner(float pTe, int& bin1, int& bin2, float& d);

};

#endif
 
