//////////////////////////////////////////////////////////////////////////
///     File: OffsetWidth.hpp                                          ///
///     Created: J. Stark  May 2009                                    ///
///     Purpose: Abstract base class for the different offsets used    ///        
///              for the different Run II W width measurements         ///
//////////////////////////////////////////////////////////////////////////

#ifndef OFFSETWIDTH_HPP__
#define OFFSETWIDTH_HPP__

#include "wmass_blinding_util/OffsetEngine.hpp"

class OffsetWidth : public OffsetEngine {

  private:

   OffsetWidth(char* phrase, double theMin, double theMax);

   friend class OffsetExampleWidth;
   friend class OffsetWidthP0;
   friend class OffsetWidthP1;
   friend class OffsetWidthP2;

  public:

   ~OffsetWidth();

   double CalculateTrueWidthFromBlindedWidth(double BlindedWidth);
   double CalculateBlindedWidthFromTrueWidth(double TrueWidth);

};

#endif // OFFSETWIDTH_HPP__
