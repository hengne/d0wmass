#include <iostream>
#include <vector>
#include "wmass_util/CAFCaloTower.hpp"

using namespace std;
  
  CAFCaloTower::CAFCaloTower(int ieta, int iphi, double E, double EME, double FH1E,
                             double Et, double EMEt, double FH1Et) {
    _ieta = ieta;
    _iphi = iphi;
    _E = E;
    _EME = EME;
    _FH1E = FH1E;
    _Et = Et;
    _EMEt = EMEt;
    _FH1Et = FH1Et;
  }
  
  CAFCaloTower::~CAFCaloTower() {}
  
ClassImp(CAFCaloTower)
