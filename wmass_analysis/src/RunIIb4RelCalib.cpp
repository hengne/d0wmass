#include "wmass_analysis/RunIIb4RelCalib.hpp"
#include <iostream>
#include <fstream>

RunIIb4RelCalib::RunIIb4RelCalib() {

  // Read channel->phys table
  std::map<int,struct CellAddressJ> channel2phys;
  int n=0;
  int chan;
  int ieta, iphi, layer;
  std::fstream rein("Calib_RunIIb4/channeltophys.txt",std::ios::in);
  while (rein.good()) {
    rein>>chan>>ieta>>iphi>>layer;
    if (rein.eof()) break;
    //
    n++;
    struct CellAddressJ a;
    a.ieta=ieta;
    a.iphi=iphi;
    a.layer=layer;
    channel2phys.insert(std::pair<int,struct CellAddressJ>(chan,a));
  }
  rein.close();
  assert(n==47416);

  // Read reference calibration (Run IIb4a)
  std::map<struct CellAddressJ,float> RunIIb4a;
  n=0;
  float c;
  std::fstream rein2("Calib_RunIIb4/cor29_runIIb4a_264054_266375.txt",std::ios::in);
  while (rein2.good()) {
    rein2>>chan>>c;
    if (rein2.eof()) break;
    //
    n++;
    std::map<int,struct CellAddressJ>::iterator it=channel2phys.find(chan);
    if (it!=channel2phys.end()) RunIIb4a.insert(std::pair<struct CellAddressJ,float>(it->second,c));
  }
  rein2.close();
  assert(n==55296);
  assert(RunIIb4a.size()==47416);

  // Fill tables with correction factors
  FillOne(&_Fact_RunIIb4ab,"Calib_RunIIb4/cor46_runIIb4ab_266376_268157.txt",
	  &RunIIb4a,&channel2phys);
  FillOne(&_Fact_RunIIb4b,"Calib_RunIIb4/cor47_runIIb4b_268158_269873.txt",
	  &RunIIb4a,&channel2phys);
  FillOne(&_Fact_RunIIb4c,"Calib_RunIIb4/cor48_runIIb4c_269874_272574.txt",
	  &RunIIb4a,&channel2phys);
  FillOne(&_Fact_RunIIb4d,"Calib_RunIIb4/cor49_runIIb4d_272575_1000000.txt",
	  &RunIIb4a,&channel2phys);

}


float RunIIb4RelCalib::EnergyCorrection(int ieta, int iphi, int layer, int run_number) {

  if (run_number>=266376) {

    struct CellAddressJ adr;
    adr.ieta=ieta;
    adr.iphi=iphi;
    adr.layer=layer;

    if (run_number<=268157) {
      return _Fact_RunIIb4ab[adr];
    } else if (run_number<=269873) {
      return _Fact_RunIIb4b[adr];
    } else if (run_number<=272574) {
      return _Fact_RunIIb4c[adr];
    } else {
      return _Fact_RunIIb4d[adr];
    }

  } else {
    return 1.;
  }

}

void RunIIb4RelCalib::FillOne(std::map<struct CellAddressJ,float>* Target,
			      char* filename,
			      std::map<struct CellAddressJ,float>* RunIIb4a,
			      std::map<int,struct CellAddressJ>* channel2phys) {

  int n=0;
  int chan;
  float c;
  std::fstream rein(filename,std::ios::in);
  while (rein.good()) {
    rein>>chan>>c;
    if (rein.eof()) break;
    //
    n++;
    std::map<int,struct CellAddressJ>::iterator it=channel2phys->find(chan);
    if (it!=channel2phys->end()) Target->insert(std::pair<struct CellAddressJ,float>(it->second,c/((*RunIIb4a)[it->second])));
  }
  rein.close();
  assert(n==55296);
  assert(Target->size()==47416);

}


RunIIb4RelCalib::~RunIIb4RelCalib(){}


