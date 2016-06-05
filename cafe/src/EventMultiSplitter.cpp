///
/// EventMultiSplitter.cpp
///
///  
///
#include "cafe/EventMultiSplitter.hpp"
#include "cafe/Config.hpp"
#include "cafe/Stat.hpp"
#include "cafe/PermuterBase.hpp"

#include <stdexcept>

#include "TClass.h"
#include "TMethodCall.h"
#include "TROOT.h"

ClassImp(cafe::EventMultiSplitter)

using namespace std;

namespace cafe {
  ///
  /// EventMultiSplitter
  ///
  ///  Load in the objects that are going to do all the work
  ///
  EventMultiSplitter::EventMultiSplitter (const char *name)
  : Controller (name), _perm(0), _local_stat(0)
  {
	Config cfg (name);

	///
	/// Grab the permuter object and name.
	///

	std::string permClassName (cfg.get("PermuterObject", "bogus"));
	std::string permName (cfg.get("PermuterName", "bogus"));

	if (permClassName == "bogus") {
	  throw runtime_error ("EventMultiSplitter's parameter permClassName wasn't set!");
	}

	if(TClass *cl = gROOT->GetClass (permClassName.c_str())) {
	  if(cl->GetMethodWithPrototype(permClassName.c_str(),"const char *") != 0) {
		TMethodCall call;
		call.InitWithPrototype(cl, permClassName.c_str(), "const char *");
		call.ResetParam();
		call.SetParam((Long_t )permName.c_str());
		Long_t ret (0);
		call.Execute(ret);
		_perm = reinterpret_cast<PermuterBase*> (ret);
	  } else {
		throw runtime_error ("Class " + permClassName + " doesn't have a ctor with a string argument!");
	  }
	} else {
	  throw runtime_error ("ROOT doesn't know about class " + permClassName + "! EventMultiSplitter can't make it!");
	}

	///
	/// Create the new stat object that we will be using!
	///

	_local_stat = new Stat (name, true);
	_local_stat->begin();
  }

  ///
  /// ~EventMultiSplitter
  ///
  ///  Get rid of the permuter object.
  ///
  EventMultiSplitter::~EventMultiSplitter (void)
  {
	delete _perm;
	delete _local_stat;
  }

  ///
  /// processEvent
  ///
  ///  For each possible permutation of the event, run our sub processors.
  ///
  bool EventMultiSplitter::processEvent (Event &event)
  {
	///
	/// Hook up our stat guy!
	///

	_local_stat->chain();

	///
	/// Build the callback and do the permutations!
	///

	EventMultiSplitter::callback cb (*this, event);
	_perm->permuteEvent (cb);

	///
	/// Unhook our local guy!
	///

	_local_stat->unchain();

	return true;
  }

  ///
  /// finish
  ///
  ///  Make sure the stat processor gets a chance!
  ///
  void EventMultiSplitter::finish(void)
  {
	_local_stat->finish();
	Controller::finish();
  }

  ///
  /// processPermutation
  ///
  ///  Do one of the permutations!
  ///
  void EventMultiSplitter::processPermutation (double weight, Event &event)
  {
	///
	/// Get the statics set up
	///

	event.clear ("StatPointer");
	_local_stat->processEvent (event);
	_local_stat->inheritWeights();

	///
	/// Put in our weight
	///

	_local_stat->applyWeight (name(), weight);

	///
	/// Call the sub processors!
	///

	Controller::processEvent (event);

	///
	/// Let the statistics know it is end of event!
	///

	_local_stat->eventEnd();
  }

  /////////////////////////////

  ///
  /// callback
  ///
  ///  Save variables for later use in our simple callback guy!
  ///
  EventMultiSplitter::callback::callback (EventMultiSplitter &splitter, Event &event)
	: _event (event), _splitter (splitter)
  {
  }

  ///
  /// operator()
  ///
  ///  Actually execute a single permutation!
  ///
  void EventMultiSplitter::callback::operator () (double weight)
  {
	_splitter.processPermutation (weight, _event);
  }
}
