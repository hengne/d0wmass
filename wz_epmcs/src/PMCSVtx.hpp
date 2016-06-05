#ifndef INC_PMCSVTX
#define INC_PMCSVTX

#include "TRandom3.h"
#include <iostream>
#include <math.h>

class PMCSVtx {

public:
  // default constructor
  PMCSVtx();

  // simple constructor
  PMCSVtx(double xvtx, double yvtx, double zvtx);

  // destructor
   ~PMCSVtx() {;}

  // print
  void Print();
  
  // set vtx 
  void SetVtx(double xvtx, double yvtx, double zvtx);

  // smear vertex
  void SmearVtx(double vtx_res, TRandom3 *dummy);

  double vtxx() const;
  double vtxy() const;
  double vtxz() const;
  
private:
  double _xvtx;
  double _yvtx;
  double _zvtx;
};

inline double PMCSVtx::vtxx() const {return _xvtx;}
inline double PMCSVtx::vtxy() const {return _yvtx;}
inline double PMCSVtx::vtxz() const {return _zvtx;}
inline void PMCSVtx::Print() {std::cout<<"(xvtx="<<_xvtx<<",yvtx="<<_yvtx<<",zvtx="<<_zvtx<<")"<<std::endl;}

#endif
