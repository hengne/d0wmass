///////////////////////////////////////////////////////////////////////
///     File: OffsetExample.hpp                                     ///
///     Created: J. Stark  September 2007                           ///
///     Purpose: An example blinding offset for testing purposes    ///
///              (not used in any D0 analysis).                     ///
///     Modified: J.Stark  May 2009                                 ///  
///               Adapted to new Run IIb features                   ///  
///////////////////////////////////////////////////////////////////////

#ifndef OFFSETEXAMPLE_HPP__
#define OFFSETEXAMPLE_HPP__

#include "wmass_blinding_util/OffsetMass.hpp"

class OffsetExample : public OffsetMass {

  public:

   OffsetExample();
   ~OffsetExample();

};

#endif // OFFSETEXAMPLE_HPP__
