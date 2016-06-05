#ifndef TYPEDEFINITIONS_HPP
#define TYPEDEFINITIONS_HPP

// beam spot position
typedef struct {
  float xoffset;
  float yoffset;
  float xslope;
  float yslope;
} BEAMSPOT_STRUCT;

// met struct used to determine average met, metx, mety per run
typedef struct {
  int num;
  float met_all;
  float metx_all;
  float mety_all;
  float scalarEt_all;
  float average_met;
  float average_metx;
  float average_mety;
  float average_scalarEt;
} MET_STRUCT;

// calorimeter cell position
typedef struct {
  float x;
  float y;
  float z;
} CELLXYZ_STRUCT;

#endif  //TYPEDEFINITIONS
