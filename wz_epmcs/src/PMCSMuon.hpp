#ifndef INC_PMCSMUON
#define INC_PMCSMUON

#include "PMCSParticle.hpp"
#include "PMCSVtx.hpp"

#include "TH2.h"
#include "TVector3.h"

#include <iostream>

class PMCSMuon:public PMCSParticle {
  
 public:
  PMCSMuon() {;}

 // simple constructor
  PMCSMuon(double ppid, double pE, double peta, double pphi);

  ~PMCSMuon();

  void Print() const;

  void SetEnergyEtaPhi(double pE, double peta, double pphi);

 private:
};

inline void PMCSMuon::Print() const {
   std::cout<<"(pid="<<_ppid<<",pE="<<_pE<<",pT="<<_ppt
	    <<",eta="<<_peta<<",phi="<<_pphi<<")"<<std::endl;
   std::cout<<"(px="<<_ppx<<",py="<<_ppy<<",_pz="<<_ppz<<")"<<std::endl;}

#endif
