#include <iostream>
#include <map>
#include <vector>

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Function.hpp"
#include "cafe/Processor.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "tmb_tree/TMBL1CalTile.hpp"
#include "tmb_tree/TMBLorentzVector.hpp"

using namespace cafe;

/*! \brief
  This processor matches L1 cal tiles to reco objects

  Usage:
  add this processor to the controller Run processor, e.g. \n
  cafe.Run: ... MatchObjectsL3Reco(processor_name) ...
  You can change the default behaviour via the configuration file.

  (Optional) Parameters:
  - .CalTiles: Name of the branch that contains the L1 cal towers for matching. [default: "L1CalTile"]
  - .RecoBranch: Name of the branch that contains the reco objects for matching. [default: "EMscone"] 
  - .Result: Name of the object that is made available globally. Accessible through event.get() with this name. The object is of type
  std::multimap< Collection<TMBL1CalTile>::iterator, Collection<TMBLorentzVector>::iterator >
  - .maxdR: Maximal dR that is allowed for a match. [default: 0.5]
  - .nMatches: Minimal number of matches [default: 0]
  - .nMatchesMax: Maximal number of matches

  \author Jens Konrath (jkonrath@fnal.gov)
*/

class MatchL1CalTileReco : public cafe::Processor {
public:
    MatchL1CalTileReco(const char *name);
    ~MatchL1CalTileReco() {};
    bool processEvent(cafe::Event &event);

private:
    std::multimap< Collection<TMBL1CalTile>::iterator, Collection<TMBLorentzVector>::iterator > _matchmmap;
    std::string _L1Name, _RecoName, _matchname;
    float _maxdR;
    float _maxdEt;
    int _minItems, _maxItems;

    ClassDef(MatchL1CalTileReco,0);
};
