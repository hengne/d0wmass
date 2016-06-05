///
/// EventMultiSplitter.hpp
///
///  Use this version of a controller when you want to run a single event multiple times.
///
#ifndef __EventMultiSplitter__
#define __EventMultiSplitter__


#include "cafe/Controller.hpp"

namespace cafe {
  class Stat;
  class PermuterBase;

  class EventMultiSplitter  : public cafe::Controller  {
  public:

	EventMultiSplitter (const char *name);
	~EventMultiSplitter (void);

	bool processEvent (cafe::Event &event);

	void finish (void);

	/// Passed to the permuter to effect a callback.
	class callback {
	  friend class EventMultiSplitter;
	public:
	  void operator() (double weight);
	  inline Event &event() {return _event;};
	private:
	  cafe::Event &_event;
	  callback (cafe::EventMultiSplitter &splitter, Event &event);
	  cafe::EventMultiSplitter &_splitter;
	};

  private:
	  ClassDef (EventMultiSplitter,1);

	  cafe::PermuterBase *_perm;
	  cafe::Stat *_local_stat;

	  void processPermutation (double weight, Event &event);
  };
}

#endif
