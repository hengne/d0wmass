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
#include "tmb_tree/TMBLorentzVector.hpp"

#include "caf_trigger/MatchObjectsL2Reco.hpp"

using namespace cafe;

class L2RecoMatchTest : public cafe::Processor 
{
 public:
	L2RecoMatchTest(const char *name);
	~L2RecoMatchTest() {};
	bool processEvent(cafe::Event &event);

 private:
  std::string _matchname, _toolname;

	ClassDef(L2RecoMatchTest,0)
};
