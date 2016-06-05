#ifndef INC_EMSCALECHANGERRUNIIBJAN
#define INC_EMSCALECHANGERRUNIIBJAN

// ////////////////////////////////////////////////////////////////////////////
// File: EMScaleChangerRunIIbJan.hpp
//
// Purpose:  Class with a lookup table and code to change a given EMparticle 
//           from one eta-dependent scale calibration to another one
//
// Created:  09-NOV-2008  Jan Stark
//
// ////////////////////////////////////////////////////////////////////////////

#include "tmb_tree/TMBEMCluster.hpp"

class RunIIb4RelCalib;

class EMScaleChangerRunIIbJan
{
  
 public:

  // Constructor/Destructor
  EMScaleChangerRunIIbJan();
  ~EMScaleChangerRunIIbJan();

  // Accessor
  double NewScale(TMBEMCluster* empart, int runNum, bool debug=false);

 private:

  int _firstRun[4];
  int _lastRun[4];

  double _correctionNorth[4][38];
  double _correctionSouth[4][38];
  //
  double _layfact[4][6];

  int _layertrans[18];

  //
  RunIIb4RelCalib* _runIIb4_calib;

};

#endif

