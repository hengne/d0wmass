#ifndef INC_PMCSMET
#define INC_PMCSMET

#include "PMCSEMObj.hpp"
#include "PMCSRecoil.hpp"

#include <iostream>
#include <math.h>
#include <vector>

class PMCSMet {

public:
  // default constructor
  PMCSMet();

  // simple constructor
  PMCSMet(double met_x, double met_y);

  // complete constructor
  PMCSMet(double met_x, double met_y, double met_met, double met_metphi, double met_scalarEt);

  // constructor from EMObjects and Recoil system
  PMCSMet(std::vector<PMCSEMObj> &emobjs, PMCSRecoil &recoil);

  // destructor
   ~PMCSMet() {;}

  // get some interesting variables in one function
  void getProperties(double& met, double& metphi) const;

  // print
  void Print();
  
  // set metx, mety
  void SetMet(double metx_x, double met_y);
  double metx() const;
  double mety() const;
  double met() const;
  double metphi() const;
  double scalarEt() const;
  
private:
  double _metx;
  double _mety;
  double _met;
  double _metphi;
  double _scalarEt;
};

inline double PMCSMet::metx() const {return _metx;}
inline double PMCSMet::mety() const {return _mety;}
inline double PMCSMet::met() const {return _met;}
inline double PMCSMet::metphi() const {return _metphi;}
inline double PMCSMet::scalarEt() const {return _scalarEt;}
inline void PMCSMet::Print() {std::cout<<"(metx="<<_metx<<",mety="<<_mety<<",met="<<_met<<")"<<std::endl;}
inline void PMCSMet::getProperties(double& met, double& metphi) const {
  met = _met;
  metphi = _metphi;
}
#endif
