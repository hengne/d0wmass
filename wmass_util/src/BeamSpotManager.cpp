#include "wmass_util/BeamSpotManager.hpp"
#include <fstream>
#include <iostream>

using namespace std;

// Global definitions
BeamSpotManager* BeamSpotManager::_instance=(BeamSpotManager*)0;

//Singleton.  If no instance exists, create one.  Get pointer to instance.
BeamSpotManager* BeamSpotManager::get_instance() {
  if (_instance == 0) _instance = new BeamSpotManager();
  return _instance;
}

// initialize beam spot manager
void BeamSpotManager::initialize() {

  // read beam spot file
  ifstream inputfile("beamspot.dat");
  
  if(!inputfile) cout<<"Please provide a file called beamspot.dat"<<endl;
  int line = 0;

  cout<<"Initialize BeamSpotManager:"<<endl;
  while(!inputfile.eof()) {
    float xoffset, yoffset, xslope, yslope;
    int run, nev;
    double errx, erry, errz;
    inputfile>>run>>nev>>xoffset>>yoffset>>errx>>erry>>errz>>xslope>>yslope;

    BEAMSPOT_STRUCT temp;
    temp.xoffset = xoffset;
    temp.yoffset = yoffset;
    temp.xslope = xslope;
    temp.yslope = yslope;
    _beamspot_map.insert(pair<int, BEAMSPOT_STRUCT>(run, temp));
    line++;
  }

  inputfile.close();
  cout<<"Read beamspot position for "<<line<<" runs"<<endl;
  cout<<"BeamSpotManager initialized"<<endl;
}

// Constructor initializes pointers to zero
BeamSpotManager::BeamSpotManager() {
  initialize();
}

// Destructor 
BeamSpotManager::~BeamSpotManager() { }


