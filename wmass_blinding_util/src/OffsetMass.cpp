#include "wmass_blinding_util/OffsetMass.hpp"

#include <iostream>

using namespace std;

OffsetMass::OffsetMass(char* phrase, double theMin, double theMax) : OffsetEngine(phrase, theMin, theMax){
}

OffsetMass::~OffsetMass() {
}

double OffsetMass::CalculateTrueMassFromBlindedMass(double BlindedMass) {
  return BlindedMass-daOffset();
}

double OffsetMass::CalculateBlindedMassFromTrueMass(double TrueMass) {
  return TrueMass+daOffset();
}

