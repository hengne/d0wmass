#include "wmass_util/CaloGeometryManager.hpp"
#include <fstream>
#include <iostream>

using namespace std;

// Global definitions
CaloGeometryManager* CaloGeometryManager::_instance=(CaloGeometryManager*)0;

//Singleton.  If no instance exists, create one.  Get pointer to instance.
CaloGeometryManager* CaloGeometryManager::get_instance() {
  if (_instance == 0) _instance = new CaloGeometryManager();
  return _instance;
}

void CaloGeometryManager::initialize() {

  // read calorimeter geometry file
  //  ifstream inputfile_2005("calogeometry_2005.dat");
  //  if(!inputfile_2005) cout<<"Please provide a file called calogeometry_2005.dat (often located in wmass_analysis/config directory, need to copy to the directory where you run cafe executable"<<endl;

  ifstream inputfile_2005("CalGeom_p17mc.txt");
  if(!inputfile_2005) cout<<"Please provide a file called CalGeom_p17mc.txt (often located in wmass_analysis/config directory, need to copy to the directory where you run cafe executable"<<endl;
  
  cout<<"Initialize CaloGeometryManager:"<<endl;
  while (!inputfile_2005.eof()) {
    int cell_index;
    float cellx, celly, cellz;
    inputfile_2005>>cell_index>>cellx>>celly>>cellz;
  
    CELLXYZ_STRUCT temp;
    temp.x = cellx;
    temp.y = celly;
    temp.z = cellz;
    _calogeometry2005_map.insert(pair<int, CELLXYZ_STRUCT>(cell_index, temp));
  }

  inputfile_2005.close();

}

// Constructor initializes pointers to zero
CaloGeometryManager::CaloGeometryManager() {
  initialize();
}

// Destructor 
CaloGeometryManager::~CaloGeometryManager() { }
  

