#ifndef cal_regions_h
#define cal_regions_h

#include <algorithm>
#include "TCanvas.h"
#include "TRandom.h"
#include <vector>
#include "TBox.h"
#include "TText.h"
#include <map>

class CAL_REGIONS;
class CAL_CELL_BOX;

using namespace std;

class CAL_REGIONS
{public:
  // for data 

  CAL_REGIONS();
  // uses default (Ioption = 0)

  CAL_REGIONS(int Ioption);
  // always remove tower2, cable swap, crate 9, hot cells and checkerboard
  // 0 = remove unknown, large boxes for checkerboard       
  // 1 = remove unknown, small boxes for checkerboard
  // 2 = large boxes for checkerboard
  // 3 = small boxes for checkerboard
  // 4 = remove unknown and phi module 17, large boxes for checkerboard

  // for acceptance
  // input: run luminosity map file, run range

  CAL_REGIONS(const char *runlumi_file, int FirstRun, int LastRun);
  // uses default

  CAL_REGIONS(const char *runlumi_file, int FirstRun, int LastRun, int Ioption);

// acceptance only ///////////////////////////////////////////////////////////
  // get a random run number weighted by luminosity in the run range
  int random_run();
  
  // get fraction of luminosity in the region
  float bad_lumi_frac(float eta, float phi);

  // get info
  float luminosity() { return total_lumi; }
  int first_run() { return firstrun; }
  int last_run() { return lastrun; }

// acceptance or data ////////////////////////////////////////////////////////
  // check if (eta,phi,run) is in a bad cal region
  bool in_region(float eta, float phi, int run);

  // check if (eta,phi) is in a bad cal region, no run cut
  bool in_region(float eta, float phi);

  // draw boxes for all regions for a phi vs eta histogram
  void draw(TCanvas *can);
  void draw();

  // number the boxes
  void draw_numbers(TCanvas *can);
  void draw_numbers();

  // draw boxes on a 1D phi projection, run dependent
  void draw_phi_proj(float phi1, float phi2, float eta, 
                     float y1, float y2, int run1, int run2);

  // draw boxes on a 1D eta projection, run dependent
  void draw_eta_proj(float eta1, float eta2, float phi, 
                     float y1, float y2, int run1, int run2);

 private:
  // list of all calorimeter regions
  vector<CAL_CELL_BOX> box_list;

  int ioption;

  // deta and dphi are the amount to extend boxes beyond cell boundaries
  float deta, dphi; 

  // color to draw boxes
  int color;

  // for run luminosity;
  map<int,float> runlumi;
  float total_lumi;
  TRandom rand;

  // the run range
  int firstrun, lastrun;

  // called by constructers
  void init(const char *runlumi_file, int FirstRun, int LastRun, int Ioption);

  // add to box_list ONLY if its run range overlaps the CAL_REGIONS range
  void add_cell_box(int ieta1, int ieta2, int iphi1, int iphi2, 
                    int box_firstrun, int box_lastrun);

  // add tower2 to box_list ONLY if its run range overlaps the CAL_REGIONS range
  void add_tower2(int ieta, int iphi, bool tower3_bad, 
                  int box_firstrun, int box_lastrun);

  // add bad calorimeter regions
  void add_all_tower2();
  void add_all_cable_swap();
  void add_all_crate9();
  void add_small_cb_boxes();
  void add_large_cb_boxes();
  void add_all_unknown();
  void add_hotcells();
  void add_module17();
  void add_all_bad();

};

class CAL_CELL_BOX
{public:
  float eta_min, phi_min, eta_max, phi_max;
  int color, firstrun, lastrun;
  float lumi_frac;

  CAL_CELL_BOX(float eta1, float eta2, float phi1, float phi2, int Color,
               int FirstRun, int LastRun);

  bool in_cell_box(float eta, float phi);
  bool in_cell_box(float eta, float phi, int run);

  void draw();
  void draw_number();
};

#endif
