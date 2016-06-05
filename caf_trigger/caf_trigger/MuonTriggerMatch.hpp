#ifndef MuonTriggerMatch_h
#define MuonTriggerMatch_h
////////////////////////////////////////////////////////////////////////
// $Id: MuonTriggerMatch.hpp
// 
// File:    MuonTriggerMatch.hpp
// Purpose: CAF processor to enforce offline muon matching to triggers
// Author:  Kristian Harder, 5 May 2006
////////////////////////////////////////////////////////////////////////


#include "cafe/Event.hpp"
#include "cafe/Processor.hpp"
#include "cafe/Config.hpp"

#include "tmb_tree/TMBMuon.hpp"

#include "caf_trigger/TriggerMap.hpp"

#include <iostream>
#include <string>
#include <vector>

class MuonTriggerMatch : public cafe::Processor
{
 public:
  MuonTriggerMatch(const char *name);
  bool processEvent(cafe::Event& event);
  void finish();
  std::map<std::string, bool> getMuonTermTestResults(); //pcal 
  std::map<std::string, bool> getTrackTermTestResults(); //pcal 
  std::map<std::string, bool> getIsoTermTestResults(); //pcal 
  std::map<std::string, bool> getCMTermTestResults(); //pcal 
  double getDR_l3trk_jets() ; //pcal
  ClassDef(MuonTriggerMatch, 0);
 
 private:

  enum {level1=0,level2,level3};

  std::string _muonBranch;

  static const int _max_matchconds=10;
  std::vector<std::vector<int> > _matchconds;
  bool _check_muon[3];
  bool _check_track[3];
  bool _check_iso[3]; //pcal
  bool _check_cm[3]; //pcal
  int _n_used_conds[3];

  bool _use_run_range;
  std::vector<float> _applied_trigger_version;
  bool _exclude_bad_run_range ; //pcal, (05/29/07)

  std::string _trigcond_muon[3];
  std::string _trigcond_track[3];
  std::string _trigcond_iso[3]; //pcal
  std::string _trigcond_cm[3]; //pcal

  bool _found_muon[3],_found_track[3],_found_iso[3],_found_cm[3]; //pcal

  std::string _l1muon_name;
  int         _l2muon_quality;
  int         _l2muon_ptthreshold;
  int         _l2muon_prompt;
  int         _l3muon_quality;
  int         _l3cm_quality; //pcal
  int         _l3muon_ptthreshold;
  int         _l3cm_ptthreshold; //pcal
  int         _l1track_ptthreshold;
  int         _l1track_iso; //pcal
  int         _l2track_ptthreshold;
  int         _l3track_ptthreshold;
  int         _l3track_nhits;
  std::string _l3iso_toolname; //pcal

  // cuts that are hardcoded in wzreco
  double _dphi_l1trk;
  double _dR_l2muon;
  double _dphi_l3muon;
  double _dphi_l3trk;
  double _dphi_l3iso; //pcal
  double _dphi_l3cm; //pcal

  double _dR_l3trk_jets; //pcal

  // event counter
  int _n_events;
  int _n_matched_events;

  // number of events not processed because of trigger list selection
  int _n_wrong_triglist;

  // number of rejected events because of missing/empty chunk
  int _n_no_l1muon;
  int _n_no_l1track;
  int _n_no_l2muon;
  int _n_no_l2track;
  int _n_no_l3muon;
  int _n_no_l3track;
  int _n_no_l3iso; //pcal 

  // maps to keep track of run numbers where this happened
  std::map<int,int> _allruns;
  std::map<int,int> _runs_no_l1muon;
  std::map<int,int> _runs_no_l2muon;
  std::map<int,int> _runs_no_l3muon;
  std::map<int,int> _runs_no_l1track;
  std::map<int,int> _runs_no_l2track;
  std::map<int,int> _runs_no_l3track;
  std::map<int,int> _runs_no_l3iso; //pcal

  // number of rejected events because no match found
  int _n_nomatch_l1muon;
  int _n_nomatch_l1track;
  int _n_nomatch_l2muon;
  int _n_nomatch_l2track;
  int _n_nomatch_l3muon;
  int _n_nomatch_l3track;


  TriggerMap *_runnum_to_triggerversion;
};

#endif
