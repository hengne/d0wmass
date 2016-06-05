////////////////////////////////////////////////////////////////////////
///     File: OffsetMass.hpp                                         ///
///     Created: J. Stark  May 2009                                  ///
///     Purpose: Abstract base class for the different offsets used  ///
///              for the different Run II m(W) measurements          ///
////////////////////////////////////////////////////////////////////////

#ifndef OFFSETMASS_HPP__
#define OFFSETMASS_HPP__

#include "wmass_blinding_util/OffsetEngine.hpp"

class OffsetMass : public OffsetEngine {

  private:

   OffsetMass(char* phrase, double theMin, double theMax);
 
   friend class OffsetExample;
   friend class OffsetMassP0;
   friend class OffsetMassP1;
   friend class OffsetMassP2;

  public:

   ~OffsetMass();

   double CalculateTrueMassFromBlindedMass(double BlindedMass);
   double CalculateBlindedMassFromTrueMass(double TrueMass);

};

#endif // OFFSETMASS_HPP__
