//////////////////////////////////////////////////////////
///   File: TriggerManager.cpp                         ///
///   Created: April 15, 2005 by J. Zhu                ///
///                                                    ///
///   Purpose: Deal with trigger map                   ///
///                                                    ///
//////////////////////////////////////////////////////////

#ifndef TRIGGERMANAGER_HPP
#define TRIGGERMANAGER_HPP

#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Variables.hpp"

#include <string>
#include <map>

class TriggerManager {
 public:
  
  /// Singleton.  If no instance exists, create one.  Get pointer to instance.
  static TriggerManager* get_instance();
  
  /// Just check if an instance already exists.
  static bool check_instance() { return _instance !=0 ; }
  
  /// initialize
  void LoadTriggers();  
  
  /// reset all flags
  void ResetFlags();
  
  /// used triggers for each run
  void TrigsUsed(cafe::Event& event);
  
  /// triggers fired for this event
  void TrigsFired(cafe::Event& event);
  
  /// configure triggers for this event
  /// only need to do it once per event
  void SetTrigs(cafe::Event& event);
  
  /// check whether this EVENT passes trigger pre-requirement
  /// does not mean the electron matches with trigger objects
  bool Passes_Trig(std::string trigname);


  /// check whether this EVENT used trigger pre-requirement
  /// does not mean the electron matches with trigger objects
  bool Uses_Trig(std::string trigname);


  
  /// check whether this EVENT passes any trigger pre-requirements
  /// does not mean the electron matches with trigger objects
  bool Passes_Trig_CMB();
  
  /// get trigger map
  const std::map<int, std::vector<std::string> >& TriggerMap() { return _trigger_map; }
  
 private:
  
  std::map<int, std::vector<std::string> > _trigger_map;

  bool _using_any_trig;
  // mainly for v8-10 and v11
  bool _using_EM_HI_SH, _using_EM_MX_SH, _using_EM_HI_2EM5_SH, _using_EM_HI, _using_EM_MX;
  // mainly for v12
  bool _using_E1_SHT20, _using_E2_SHT20, _using_E3_SHT20, _using_E1_SH30;
  // mainly for v13, E1_SH30 also used 
  bool _using_E1_SHT22, _using_E2_SHT22, _using_E3_SHT22;
  // mainly for v14
  bool _using_E1_ISHT22, _using_E3_ISHT22, _using_E4_ISHT22;
 // mainly for v15 /v16
  bool _using_E1_SHT25, _using_E1_SHT27;

  bool _trig_fired;
  // mainly for v8-10 and v11
  bool _EM_HI_SH_fired, _EM_MX_SH_fired, _EM_HI_2EM5_SH_fired, _EM_HI_fired, _EM_MX_fired;
  // mainly for v12
  bool _E1_SHT20_fired, _E2_SHT20_fired, _E3_SHT20_fired, _E1_SH30_fired;
  // mainly for v13
  bool _E1_SHT22_fired, _E2_SHT22_fired, _E3_SHT22_fired;
  // mainly for v14
  bool _E1_ISHT22_fired, _E3_ISHT22_fired, _E4_ISHT22_fired;
  // mainly for v14
  bool _E1_SHT25_fired, _E1_SHT27_fired;
  /// Pointer to singleton
  static TriggerManager* _instance;

  cafe::Variables _global_vars;

  /// This is a singleton, so hide constructor. It gets invoked by calling
  /// get_instance. Constructor does nothing.  
  TriggerManager();
  
  /// Destructor
  ~TriggerManager();  

  /// flags

};

#endif //TRIGGERMANAGER_HPP

