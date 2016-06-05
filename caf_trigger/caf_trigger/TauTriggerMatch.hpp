#ifndef TauTriggerMatch_HPP_
#define TauTriggerMatch_HPP_

#include "cafe/Processor.hpp"
#include "cafe/Collection.hpp"
#include "cafe/Variables.hpp"
#include "tmb_tree/TMBL1Cal2bTau.hpp"
#include "tmb_tree/TMBL1Cal2bJet.hpp"
#include "tmb_tree/TMBL1Cal2bBase.hpp"
#include "tmb_tree/TMBL2Jet.hpp"
#include "tmb_tree/TMBL2Track.hpp"
#include "tmb_tree/TMBL3Track.hpp"
#include "tmb_tree/TMBL3Tau.hpp"
#include "tmb_tree/TMBTau.hpp"
#include "caf_trigger/TriggerMap.hpp"
#include<vector>
#include <map>

class TauTriggerMatch : public cafe::Processor {
public:
  TauTriggerMatch(const char *name);
  bool processEvent(cafe::Event& event);
  void begin();
  void finish();
  
  bool jetPassL1(cafe::Collection<TMBL1Cal2bJet>& l1jets, const TMBTau& offtau);
  bool tauPassL1(cafe::Collection<TMBL1Cal2bTau>& l1taus, const TMBTau& offtau);
  bool tauPassL2(cafe::Collection<TMBL2Jet>& l2taus, cafe::Collection<TMBL2Track>& stt, const TMBTau& offtau);
  bool tauPassL3(cafe::Collection<TMBL3Tau>& l3taus, cafe::Collection<TMBL3Track>& l3tracks,const TMBTau& offtau);
  
private:
  
  bool do_muon; 
  bool  do_jet; 
  bool  do_tau; 
  bool  do_l2stt; 
  bool  tau_at_l2; 
  bool  do_l1track; 
  bool  do_tau_stt; 
  bool  track_term_passed; 
  bool  _check_trigger ; 
  float _l3taunn; 
  float _l3taueta; 
  float _match_cut; 
  float _l3taupt; 
  float  jet_et; 
  float tau_et; 
  float jet_eta; 
  float tau_eta; 
  float tau_ratio; 
  float  l2tau_et; 
  float _l2tau_eta; 
  float tau_core; 
  float l2tau_ratio; 
  float l2stt_pt; 
  float tau_sttpt; 
  float l1track_pt; 
  float _phi_cut;
  int l2stt_sttfit; 
  int l2stt_quality; 
  int tau_sttiso;
  int _l3tau_ntracks;
  
  std::vector<float> vec_l3taunn; 
  std::vector<float> vec_l3taueta; 
  std::vector<float> vec_match_cut; 
  std::vector<float> vec_l3taupt; 
  std::vector<float> vec_muon_pt; 
  std::vector<float> vec_jet_et; 
  std::vector<float> vec_tau_et; 
  std::vector<float> vec_muon_eta; 
  std::vector<float> vec_jet_eta; 
  std::vector<float> vec_tau_eta; 
  std::vector<float> vec_tau_ratio; 
  std::vector<float> vec_l2muon_et; 
  std::vector<float> vec_l2tau_et; 
  std::vector<float> vec_l2tau_eta; 
  std::vector<float> vec_tau_core; 
  std::vector<float> vec_l2tau_ratio; 
  std::vector<float> vec_l2stt_pt; 
  std::vector<float> vec_tau_sttpt; 
  std::vector<float> vec_l1track_pt; 
  std::vector<float> vec_trackjet_pt;
  
  std::vector<int> vec_do_muon; 
  std::vector<int> vec_do_jet; 
  std::vector<int> vec_do_tau; 
  std::vector<int> vec_do_l2stt; 
  std::vector<int> vec_tau_term_passed; 
  std::vector<int> vec_jet_term_passed; 
  std::vector<int> vec_muon_term_passed; 
  std::vector<int> vec_tau_at_l2; 
  std::vector<int> vec_do_l1track; 
  std::vector<int> vec_do_tau_stt;
  std::vector<int> vec_l3tau_ntracks;  
  std::vector<int> vec_track_term_passed; 
  std::vector<int> vec_is_a_tau_trigger ; 
  
  std::vector<std::string> trigname;
  
  cafe::Variables _vars;
  
  std::string _offline_tau; 
  std::string _offline_muon; 
  std::string _offline_jet;

  std::map<std::string,const char*> _l1cal_trig_to_andor_v15;
  std::map<std::string,const char*> _l1cal_trig_to_andor_v16;

char trigbuilder[128];
  std::string termstring;
  
  int _runnumber; 
  bool _matchseeds; 
  bool _trkonlytau;
  
  int _n_events;
  int _n_matched_events;
  int _n_wrong_triglist;
  
  // number of rejected events because of missing/empty chunk
  int _n_no_l1tau;
  int _n_no_l1track;
  int _n_no_l2tau;
  int _n_no_l2track;
  int _n_no_l3track;
  int _n_no_l3tau; 
  // number of rejected events because of missing/empty chunk
  int _n_nomatch_l1tau;
  int _n_nomatch_l1track;
  int _n_nomatch_l2tau;
  int _n_nomatch_l2track;
  int _n_nomatch_l3track;
  int _n_nomatch_l3tau; 

  bool _exclude_bad_run_range;
  bool _use_run_range;
 TriggerMap *_runnum_to_triggerversion;
 std::vector<float> _applied_trigger_version;
  char track_andorterm[32];
  float trackjet_pt;


public:
    ClassDef(TauTriggerMatch,0);
};

#endif 
