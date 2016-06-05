#ifndef caf_trigger_JetTriggerMatch_HPP_
#define caf_trigger_JetTriggerMatch_HPP_

#include <map>
#include <vector>
#include <set>
#include <string>

#include "cafe/Processor.hpp"

#include "caf_trigger/L1JetTerms.hpp"
#include "caf_trigger/L2JetTerms.hpp"
#include "caf_trigger/L3JetTerms.hpp"

#include "caf_trigger/TriggerMap.hpp"
#include "caf_trigger/TriggerTermMap.hpp"

namespace caf_trigger {

  /*! \brief 
    This processor returns a list of triggers matched and confirmed for
    each reco jet. Only triggers that actually fired are considered.
    The code is partially modeled after EMTriggerMatch.cpp and relies
    heavily on use of trigeff_caf L1Term, L2Term and L3Term (now ported
    as L1JetTerms, L2JetTerms and L3JetTerms in caf_trigger). Mappings from
    run to trigger list and from trigger list to L1L2L3 terms are done
    through TriggerMap and TriggerTermMap.

    Required parameters:
    --------------------
    - .Triggers: vector of string [default: all triggers in TriggerTermMap]
      Names of the triggers to consider for matching. Only ones that actually
      fire are considered for matching.

    - .JetBranch: string [default: "JCCB"]
      The reco jets to consider for matching. The returned map will
      contain a list of confirmed triggers for iterators in this branch.

    - .L1CalTowerBranch: string [default L1CalTotalTowers]
      The L1 cal towers for matching.

    - .L2JetBranch: string [default L2Jet]
      The L2 jets for matching.

    - .L3JetBranch: string [default L3Jet]
      The L3 jets for matching.

    - .ConfirmL1: bool [default: true]
    - .ConfirmL2: bool [default: true]
    - .ConfirmL3: bool [default: true]

    - .L1DeltaR: double [default: 0.5]
    - .L2DeltaR: double [default: 0.5]
    - .L3DeltaR: double [default: 0.5]
      The maximum distance between the reco jet and the trigger object to 
      consider it a match.

    \authors Mikko Voutilainen (mavoutil()fnal.gov)

  */

class JetTriggerMatch : public cafe::Processor {

public:
  JetTriggerMatch(const char *name);
  void begin();
  bool processEvent(cafe::Event& event);
  void inputFileOpened(TFile *file);
  void inputFileClosing(TFile *file);
  void finish();
  void dumpConfig();

private:
  
  L1JetTerms _l1term;
  L2JetTerms _l2term;
  L3JetTerms _l3term;
  char _cut_buf[20]; // helper for transforming float to string

  std::set<std::string> _triggerNames;
  cafe::Variables       _varsGlobal;
  cafe::Variables       _varsTrig;
  cafe::Variables       _varsJet;
  cafe::Variables       _varsL1;
  cafe::Variables       _varsL2;
  cafe::Variables       _varsL3;
  
  TriggerMap _trigMap; // use the default file location
  TriggerTermMap _trigTerms; // use the default file location

  typedef cafe::Collection<TMBJet>::iterator jet_it; 
  std::map<jet_it, std::set<std::string> > _mapConfirmed;

  std::string _jetBranch;
  std::string _L1CalTowerBranch;
  std::string _L2JetBranch;
  std::string _L3JetBranch;

  bool _confirmL1;
  bool _confirmL2;
  bool _confirmL3;

  double _L1DeltaR;
  double _L2DeltaR;
  double _L3DeltaR;
  
public:
    ClassDef(JetTriggerMatch,0);
};

} // namespace caf_trigger

#endif // caf_trigger_JetTriggerMatch_HPP_
