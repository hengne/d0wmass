#include <iostream>
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
  This processor matches L3 to reco objects

  Usage:
  add this processor to the controller Run processor, e.g. \n
  cafe.Run: ... MatchObjectsL3Reco(processor_name) ...
  You can change the default behaviour via the configuration file.

  (Optional) Parameters:
  - .L3Branch: Name of the branch that contains the L2 objects for matching. [default: ""]
  - .RecoBranch: Name of the branch that contains the reco objects for matching. [default: ""] 
  - .Result: Name of the object that is made available globally. Accessible through event.get() with this name. The object is of type 
  std::multimap< Collection<TMBL3Base>::iterator, Collection<TMBLorentzVector>::iterator >
  - .maxdR: Maximal dR that is allowed for a match. [default: 0.5]
  - .dPhiMatchOnly: Use matching only in dphi. In that case maxdR will be used as matching paarameter in dPhi [default: false]
  - .nMatches: Minimal number of matches [default: 0]
  - .nMatchesMax: Maximal number of matches

  \author Jens Konrath (jkonrath@fnal.gov)
*/

class MatchObjectsL3Reco : public cafe::Processor {
public:
    MatchObjectsL3Reco() {};
    MatchObjectsL3Reco(const char *name);
    virtual ~MatchObjectsL3Reco() {};
    bool processEvent(cafe::Event &event);

private:
    std::string _l3branch, _recobranch, _matchname;
    std::vector< Match<TMBL3Base, TMBLorentzVector> > _matches;
    std::multimap< Collection<TMBL3Base>::iterator, Collection<TMBLorentzVector>::iterator > _matchmap;
    double _maxdR; 
    int _minItems, _maxItems;
    bool _dphionly ;

    ClassDef(MatchObjectsL3Reco, 0);
};
