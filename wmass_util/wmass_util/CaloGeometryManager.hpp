////////////////////////////////////////////////////////////////////////////
///   File: CaloGeometryManager.cpp                                      ///
///   Created: March 24, 2005 by J. Zhu                                  ///
///                                                                      ///
///   Purpose: Read run-dependent calorimeter geometry from files        ///
///                                                                      ///
////////////////////////////////////////////////////////////////////////////

#ifndef CALOGEOMETRYMANAGER_HPP
#define CALOGEOMETRYMANAGER_HPP

#include "wmass_util/TypeDefinitions.hpp"
#include <map>

class CaloGeometryManager {
public:

  /// Singleton.  If no instance exists, create one.  Get pointer to instance.
  static CaloGeometryManager* get_instance();

  /// Just check if an instance already exists.
  static bool check_instance() { return _instance !=0 ; }

  /// get calorimeter geometry file for 2005
  const std::map<int, CELLXYZ_STRUCT>& getCaloGeometry2005Map() {return _calogeometry2005_map;}

  /// initialize
  void initialize();  

private:

  /// map between (ieta, iphi, ilayer) and (cellX, cellY, cellZ)
  std::map<int, CELLXYZ_STRUCT> _calogeometry2005_map;
  
  /// Pointer to singleton
  static CaloGeometryManager* _instance;

  /// This is a singleton, so hide constructor. It gets invoked by calling
  /// get_instance. Constructor does nothing.  
  CaloGeometryManager();

  /// Destructor
  ~CaloGeometryManager();
  
};

#endif //CALOGEOMETRYMANAGER_HPP

