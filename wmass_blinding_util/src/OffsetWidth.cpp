#include "wmass_blinding_util/OffsetWidth.hpp"

#include <iostream>

using namespace std;

OffsetWidth::OffsetWidth(char* phrase, double theMin, double theMax) : OffsetEngine(phrase, theMin, theMax){
}

OffsetWidth::~OffsetWidth() {
}

double OffsetWidth::CalculateTrueWidthFromBlindedWidth(double BlindedWidth) {
  return BlindedWidth-daOffset();
}

double OffsetWidth::CalculateBlindedWidthFromTrueWidth(double TrueWidth) {
  return TrueWidth+daOffset();
}

