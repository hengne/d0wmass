#include "cal_regions.h"
#include "TH2F.h"
#include "TRandom.h"
#include <iostream>
#include "TLine.h"
using namespace std;

// to determine whether electron is in bad calorimeter region in data
// CAL_REGIONS badcal(4);  // initialize to ioption = 4, cut all bad cal
// bool in_bad_cal = badcal.in_region(eta, phi, run);

// to model in MC
int main(){  
TCanvas *can = new TCanvas("can","can",0,0,640, 640);
can->SetFillColor(10);

TH2F *range1_scatter = new TH2F("range1_scatter",
  "eta vs phi distribution of electrons in range1",
  640,-3.2,3.2, 640, 0, 2*M_PI);

// to calc acceptance for 2 different run ranges, cut out everything
CAL_REGIONS range1("runlumi_180pb.map", 161973, 178721, 4);
CAL_REGIONS range2("runlumi_180pb.map", 178722, 180956, 4);

// dump lumi
printf ("\nlumi range1: %8.2f, range2: %8.2f, total: %8.2f\n", 
  range1.luminosity(), range2.luminosity(), 
  range1.luminosity() + range2.luminosity());

// generate # of random runs equal total luminosity for range1
map <int,float> testmap;
TRandom rnd;
for (int i = 0; i < int(range1.luminosity()); i++){

  // luminosity weighted random run
  int run = range1.random_run();

  // keep track of number of events generated per run 
  // as a check number of events per run should be close to run lumi
  testmap[run]++;

  // random eta and phi
  float eta = rnd.Rndm()*6.4 - 3.2;
  float phi = rnd.Rndm()*2*M_PI;

  // only plot if not in bad cal region
  if (!range1.in_region(eta, phi, run)) range1_scatter->Fill(eta, phi);
}

// verify random runs generated correctly
printf("creating testmap.map\n");
FILE *fout = fopen("testmap.map","w");
for (map<int,float>::iterator i = testmap.begin(); i != testmap.end(); i++)
  fprintf(fout,"%i %8.0f\n", (*i).first, (*i).second);
fclose(fout);

// verify regions in boxes are cut (some boxes are only present for part of the range)
can->cd();
range1_scatter->SetStats(false);
range1_scatter->Draw();
range1.draw(can);
can->Print("range1_scatter.eps");
}
