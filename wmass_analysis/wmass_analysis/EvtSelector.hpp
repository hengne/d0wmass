///////////////////////////////////////////////////////////////////
///    File: EvtSelector.hpp                                    ///
///    Created: J. Zhu March 3, 2005                            ///
///                                                             ///
///    Purpose: code used to select good events                 ///
///             remove duplicated events                        ///
///                                                             ///
///////////////////////////////////////////////////////////////////
#ifndef EVTSELECTOR_HPP
#define EVTSELECTOR_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "wmass_util/hist_files.hpp"
#include "wmass_util/TypeDefinitions.hpp"
#include "wmass_util/CAFZBevent.hpp"

#include <set>

class EvtSelector : public cafe::Processor {
  
 public:
  EvtSelector(const char *name);
  ~EvtSelector();
  
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();
  
  ClassDef(EvtSelector, 0);
  
 private:

  // debug Level
  int _debugLevel;
  
  // histograms
  hist_files _histos;

  // remove duplicated events
  bool _Remove_Duplicated_Events;

  // event counter
  int _events;

  // MC study
  bool _MCStudy;

  // Cut on Trigger Type in v16
  bool _Use_v16_E1SHT27_Only;
  bool _Use_v16_E1SHT25_Only;
  

  // # of events throw away since they are not in the trigger list
  int _events_not_in_triggerlists;

  // # of duplicated events
  int _duplicated_events;

// Use MC/Data inst lumi ratio
  bool _MCLumiReweight;

  // ZB event (for MC studies)
  CAFZBevent* _ZBevent;
  Bool_t _doZBevent;
  TString _ZBfile;
  TString _ZBtree;

  // MC/Data inst lumi ratio
  TH1F *_lumiRatio;

  // for remove duplicated events
  std::set<std::pair<int, int> > _event_set;

  cafe::Variables _global_vars;
};

#endif
