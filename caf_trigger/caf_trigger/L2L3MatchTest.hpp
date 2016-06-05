#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Function.hpp"
#include "cafe/Processor.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "tmb_tree/TMBL2Base.hpp"
#include "tmb_tree/TMBL3Base.hpp"

#include "caf_trigger/MatchObjectsL2L3.hpp"

using namespace cafe;

class L2L3MatchTest : public cafe::Processor 
{
 public:
	L2L3MatchTest(const char *name);
	~L2L3MatchTest() {};
	bool processEvent(cafe::Event &event);

 private:
  std::string _matchname, _toolname;

	ClassDef(L2L3MatchTest,0)
};
