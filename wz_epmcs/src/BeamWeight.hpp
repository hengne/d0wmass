#ifndef beamweight_h
#define beamweight_h
#include <map>
#include <vector>
#include <string>
#include <utility>

typedef std::map<double, double>  lummap;
typedef std::map<double, double>::const_iterator lummap_iterator;
typedef std::map<int, lummap> bigmap;
typedef std::pair<double, double> relinfo;

// function to return the relative weight for MC events with 25 cm gaussian and 'correct' beam weighting.

class BeamWeight{

 public:

  BeamWeight(std::string inputfile="wzcross_sample/data/beamshape.txt");
  relinfo beamshape(int run, double instlum, double z);
  double Gaussian(double wid, double z0,  double z);
  inline void setdebug(bool debug){_debug = debug;};
 private:
  bool _debug;
  std::vector<int> _runmin;
  std::vector<int> _runmax;
  bigmap _lummin;
  std::map<int, lummap > _lummax;
  
  std::map<int, std::map<double, double> > _sigmaz;
  std::map<int, double>  _betax;
  std::map<int, double>  _betay;
  std::map<int, double>  _z0x;
  std::map<int, double>  _z0y;
  std::map<int, lummap > _z0z;
  std::map<int, lummap > _norm;
};

#endif
