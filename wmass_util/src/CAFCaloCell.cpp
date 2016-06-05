#include <iostream>
#include <vector>
#include "wmass_util/CAFCaloCell.hpp"

using namespace std;
  
  CAFCaloCell::CAFCaloCell(const TMBCaloCell& p):TMBCaloCell(p) {
  }
  
  CAFCaloCell::~CAFCaloCell() {}
  
ClassImp(CAFCaloCell)
