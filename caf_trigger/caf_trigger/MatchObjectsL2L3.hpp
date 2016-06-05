#include <iostream>
#include <map>
#include <vector>

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Function.hpp"
#include "cafe/Processor.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "tmb_tree/TMBL2Base.hpp"
#include "tmb_tree/TMBL3Base.hpp"
#include "tmb_tree/TMBLorentzVector.hpp"

#include "caf_trigger/Match.hpp"

using namespace cafe;

/*! \brief
  This processor matches L2 to L3 objects

  Usage:
  add this processor to the controller Run processor, e.g. \n
  cafe.Run: ... MatchObjectsL2L3(processor_name) ...
  You can change the default behaviour via the configuration file.

  (Optional) Parameters:
  - .L2Branch: Name of the branch that contains the L2 objects for matching. [default: ""]
  - .L3Branch: Name of the branch that contains the L3 objects for matching. [default: ""] 
  - .Result: Name of the object that is made available globally. Accessible through event.get() with this name. The object is of type 
  std::multimap< Collection<TMBL2Base>::iterator, Collection<TMBL3Base>::iterator >
  - .maxdR: Maximal dR that is allowed for a match. [default: 0.5]
  - .nMatches: Minimal number of matches [default: 0]
  - .nMatchesMax: Maximal number of matches

  \author Jens Konrath (jkonrath@fnal.gov)
*/

class MatchObjectsL2L3 : public cafe::Processor {
public:
    MatchObjectsL2L3() {};
    MatchObjectsL2L3(const char *name);
    virtual ~MatchObjectsL2L3() {};
    bool processEvent(cafe::Event &event);
  
private:
    std::string _l2branch, _l3branch, _matchname;
    std::vector< Match<TMBL2Base, TMBL3Base> > _matches;
    std::multimap< Collection<TMBL2Base>::iterator, Collection<TMBL3Base>::iterator > _matchmap;
    double _maxdR; 
    int _minItems, _maxItems;
  
    ClassDef(MatchObjectsL2L3, 0);
};
