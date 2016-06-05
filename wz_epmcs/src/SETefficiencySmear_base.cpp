#include "SETefficiencySmear_base.hpp"

// constructor
SETefficiencySmear_base::SETefficiencySmear_base() {
}

// calculates the SET efficiency
double SETefficiencySmear_base::getSETeff(float SET, float lumi, float pTe, float pTe2, bool isEC, bool isEC2, float eta1, float eta2, float upara1, float upara2, TRandom3 *dummy, double *external_rnd2) {
  return 1.;
}

void SETefficiencySmear_base::InterpBinner(float pTe, int& bin1, int& bin2, float& d) {
  bin1=-1;
  bin2=-1;
  d=0;
  return;
}

// flip an efficiency
// optional: external_rnd is a pointer to the external random number value
bool SETefficiencySmear_base::passesSETeff(float SET, float lumi, TRandom3 *dummy, double *external_rnd, float pTe, float pTe2, bool isEC, bool isEC2, float eta1, float eta2, float upara1, float upara2) {
  return true;
}

bool SETefficiencySmear_base::passesFirst() {
  return true;
}

bool SETefficiencySmear_base::passesSecond() {
  return true;
}

