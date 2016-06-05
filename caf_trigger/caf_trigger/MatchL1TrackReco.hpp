#include <iostream>
#include <map>
#include <vector>

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Function.hpp"
#include "cafe/Processor.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "tmb_tree/TMBL1Track.hpp"
#include "tmb_tree/TMBLorentzVector.hpp"

using namespace cafe;

/*! \brief
  This processor matches L1 tracks to reco objects

  Usage:
  add this processor to the controller Run processor, e.g. \n
  cafe.Run: ... MatchL1TrackReco(processor_name) ...
  You can change the default behaviour via the configuration file.

  (Optional) Parameters:
  - .L1Tracks: Name of the branch that contains the L1 tracks for matching. [default: ""]
  - .RecoBranch: Name of the branch that contains the reco objects for matching. [default: ""] 
  - .Result: Name of the object that is made available globally. Accessible through event.get() with this name. The object is of type
  std::multimap< Collection<TMBL1CalTower>::iterator, Collection<TMBLorentzVector>::iterator >
  - .maxdR: Maximal dR that is allowed for a match. [default: 0.5]
  - .nMatches: Minimal number of matches [default: 0]
  - .nMatchesMax: Maximal number of matches

  \author Jens Konrath (jkonrath@fnal.gov)
*/

class MatchL1TrackReco : public cafe::Processor {
public:
    MatchL1TrackReco(const char *name);
    ~MatchL1TrackReco() {};
    bool processEvent(cafe::Event &event);

private:
    std::multimap< Collection<TMBL1Track>::iterator, Collection<TMBLorentzVector>::iterator > _matchmmap;
    std::string _L1Name, _RecoName, _matchname;
    float _maxdphi;
    float _maxdEt;
    int _minItems, _maxItems;

    ClassDef(MatchL1TrackReco,0);
};
