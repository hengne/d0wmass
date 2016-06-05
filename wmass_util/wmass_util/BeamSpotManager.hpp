//////////////////////////////////////////////////////////
///   File: BeamSpotManager.cpp                        ///
///   Created: March 24, 2005 by J. Zhu                ///
///                                                    ///
///   Purpose: Read run-dependent beam spot position   ///
///                                                    ///
//////////////////////////////////////////////////////////

#ifndef BEAMSPOTMANAGER_HPP
#define BEAMSPOTMANAGER_HPP

#include "wmass_util/TypeDefinitions.hpp"
#include <map>

class BeamSpotManager {
public:

  /// Singleton.  If no instance exists, create one.  Get pointer to instance.
  static BeamSpotManager* get_instance();

  /// Just check if an instance already exists.
  static bool check_instance() { return _instance !=0 ; }

  /// initialize
  void initialize();  

  // get beamspot map
  const std::map<int, BEAMSPOT_STRUCT>& BeamSpotMap() { return _beamspot_map; }

private:

  std::map<int, BEAMSPOT_STRUCT> _beamspot_map;
  
  /// Pointer to singleton
  static BeamSpotManager* _instance;

  /// This is a singleton, so hide constructor. It gets invoked by calling
  /// get_instance. Constructor does nothing.  
  BeamSpotManager();

  /// Destructor
  ~BeamSpotManager();  
};

#endif //BEAMSPOTMANAGER_HPP

