#include <iostream>
#include <map>
#include <vector>

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Function.hpp"
#include "cafe/Processor.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include "tmb_tree/TMBL1Muon.hpp"
#include "tmb_tree/TMBLorentzVector.hpp"
#include "tmb_tree/TMBMuon.hpp"

#include <TMath.h>

using namespace cafe;

/*! \brief
  This processor matches L1 muons to reco objects

  Usage:
  add this processor to the controller Run processor, e.g. \n
  cafe.Run: ... MatchObjectsL3Reco(processor_name) ...
  You can change the default behaviour via the configuration file.

  (Optional) Parameters:
  - .RecoBranch: Name of the branch that contains the reco objects for matching. [default: "Muon"] 
  - .Result: Name of the object that is made available globally. Accessible through event.get() with this name. The object is of type
  std::multimap< CONST TMBL1Muon*, Collection<TMBMuon>::iterator >
  - .nMatches: Minimal number of matches [default: 0]
  - .nMatchesMax: Maximal number of matches

  \author Jens Konrath (jkonrath@fnal.gov)
*/

class MatchL1MuonReco : public cafe::Processor {
public:
    MatchL1MuonReco(const char *name);
    ~MatchL1MuonReco() {};
    bool processEvent(cafe::Event &event);

private:
    std::multimap< const TMBL1Muon*, Collection<TMBMuon>::iterator > _matchmmap;
    std::string _L1Name, _RecoName, _matchname;
    int _minItems, _maxItems;

    ClassDef(MatchL1MuonReco,0);
};
