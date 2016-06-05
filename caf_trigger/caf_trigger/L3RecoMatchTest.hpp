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
#include "tmb_tree/TMBL3Base.hpp"
#include "tmb_tree/TMBLorentzVector.hpp"

#include "caf_trigger/MatchObjectsL3Reco.hpp"

using namespace cafe;

class L3RecoMatchTest : public cafe::Processor {
 public:
	L3RecoMatchTest(const char *name);
	~L3RecoMatchTest() {};
	bool processEvent(cafe::Event &event);

 private:
  std::string _matchname, _toolname;

	ClassDef(L3RecoMatchTest,0)
};
