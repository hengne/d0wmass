#include "PMCSRecoil.hpp"

PMCSRecoil::PMCSRecoil() {
  _recoilx = 0.;
  _recoily = 0.;
  _lumi = -1.;
}

PMCSRecoil::PMCSRecoil(double recoilx, double recoily) {
  _recoilx = recoilx;
  _recoily = recoily;
  _lumi = -1.;
}

void PMCSRecoil::SetRecoil(double recoilx, double recoily) {
  _recoilx = recoilx;
  _recoily = recoily;
  _lumi = -1.;
}

void PMCSRecoil::SetLumi(double lumi) { 

  _lumi = lumi; 

}

