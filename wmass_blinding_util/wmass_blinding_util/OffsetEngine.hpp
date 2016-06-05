///////////////////////////////////////////////////////////////////////
///     File: OffsetEngine.hpp                                      ///
///     Created: J. Stark  September 2007                           ///
///     Purpose: Turn (visible) strings into (invisible) offsets.   ///
///////////////////////////////////////////////////////////////////////

#ifndef OFFSETENGINE_HPP__
#define OFFSETENGINE_HPP__

#include "TRandom3.h"

class OffsetEngine {

  public:

   OffsetEngine();
   ~OffsetEngine();

   OffsetEngine(char* phrase, double theMin, double theMax);

  protected:

   double daOffset();

  private:

   char _phrase[1000];
   double _theMin;
   double _theMax;
   //
   UInt_t _seed;
   double _offset; 

};

#endif // OFFSETENGINE_HPP__
