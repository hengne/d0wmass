#include "BeamWeight.hpp"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <TMath.h>

using std::map; 
using std::cout;
using std::endl;


 BeamWeight::BeamWeight(std::string inputfile){
   const int nvars = 11;
   std::string dummy;
   std::ifstream input(inputfile.c_str());

   // skip the header row

   for (int i = 0; i < nvars; i++){
     input >> dummy;
   }
   int irange = 0;
   int runmin;
   int runmax;
   double lummin;
   double lummax;
   double chi2;
   double sigmaz;
   double betax;
   double betay;
   double z0x;
   double z0y;
   double z0z;
   _debug = 0;
   int inputcount = 0;
   while(input >> runmin){
     inputcount++;
     input >> runmax >> lummin >> lummax >> chi2 >> sigmaz >> betax >> betay >> z0x >> z0y >> z0z;
     bool found = false;
     
     for(int i = 0; i < _runmin.size(); i++){
       if(runmin == _runmin[i]){
	 found = true;
	 break;
       }
     }
     if(!found){
       //cout << " read in " << runmin << " " << lummin << " " << lummax << endl;
       _runmin.push_back(runmin);
       _runmax.push_back(runmax);
       _betax[runmin] = fabs(betax);
       _betay[runmin] = fabs(betay);
       _z0x[runmin] = z0x;
       _z0y[runmin] = z0y;
     }
     
     _lummin[runmin][lummin] = lummin;
     _lummax[runmin][lummin] = lummax;
     _sigmaz[runmin][lummin] = fabs(sigmaz);
     _z0z[runmin][lummin] = z0z;
     _norm[runmin][lummin] = 1.0;

     // make certain it is normalized

     double dz = 0.01;
     double norm = 0.0;
     for (double z = -200; z < 200.; z = z + dz){
       norm = norm + beamshape(runmin,lummin+0.1,z).second;
     }
     if(norm> 0.0) _norm[runmin][lummin] = 1./norm/dz;
  
   }
   
   // make certain ranges are contiguous
   for(int i = 1; i < _runmin.size(); i++){
     _runmax[i-1] = _runmin[i]-1;
     cout << " run ranges " << _runmin[i-1] << " " << _runmax[i-1] << endl;
   }
   _runmax[_runmin.size()-1]=1000000;
    cout << " run ranges " << _runmin[_runmin.size()-1] << " " << _runmax[_runmin.size()-1] << endl;

   if(inputcount == 0) std::cerr << " BeamWeight did not read any data from " << inputfile << endl; 
 }

relinfo BeamWeight::beamshape(int run, double instlum, double z){
  int runindex = 0;
  double lum;
  for (int irun = 0; irun < _runmin.size(); irun++){
    if(run >= _runmin[irun] && run <= _runmax[irun]){
      runindex = _runmin[irun];
      lummap lumbins = _lummin[runindex];
      for(lummap_iterator plum = lumbins.begin(); plum != lumbins.end();plum++ ){
        lum = plum->first;
	if(_debug) cout << "lum " <<  instlum << " " << lum << endl;

	if(instlum < _lummin[runindex][lum] || instlum > _lummax[runindex][lum] ) continue;

	double s = _sigmaz[runindex][lum];
	double a = _norm[runindex][lum]/std::sqrt(TMath::TwoPi())/s;
	
	relinfo retval(a*Gaussian(s,0.,0.),
		       a*Gaussian(s,_z0z[runindex][lum],z)/
		       (std::sqrt(1 + (z-_z0x[runindex])*(z-_z0x[runindex])/_betax[runindex]/_betax[runindex])*
			std::sqrt(1 + (z-_z0y[runindex])*(z-_z0y[runindex])/_betay[runindex]/_betay[runindex])));
	return retval;

      }
    }
  }
  std::cerr << "BeamWeight::beamshape() -- I could not find the beam profile for this run and luminosity." << std::endl;
  relinfo didnotfind(1., 0.);
  return didnotfind;
  
}

double BeamWeight::Gaussian(double width, double z0, double z){
  return 1./std::sqrt(TMath::TwoPi()*width*width) *std::exp(-(z-z0)*(z-z0)/width/width/2.);
}
