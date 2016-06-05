///
/// PermuterBase.hpp
///
///
///
#ifndef __PermuterBase__
#define __PermuterBase__


#include "TObject.h"

#include "cafe/EventMultiSplitter.hpp"

namespace cafe {
  class Event;

  class PermuterBase  : public TObject  {
  public:
	/// Force one to use the proper ctor.
	inline PermuterBase (const char *name)
	{
	}

	inline ~PermuterBase (void)
	{
	}

	/// Implement this, and for each permutation call the callback with the weight.
	virtual void permuteEvent (cafe::EventMultiSplitter::callback &callback) = 0;

  private:
	  ClassDef (PermuterBase,1);

  };
}

#endif
