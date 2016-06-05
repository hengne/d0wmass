
#ifndef INC_PMCSRECOIL
#define INC_PMCSRECOIL

#include <iostream>
#include "AnglesUtil.hpp"
#include <math.h>

class PMCSRecoil {
  
 public:
  PMCSRecoil();
  PMCSRecoil(double recoilx, double recoily);
  ~PMCSRecoil() {;}
  
  void SetRecoil(double recoilx, double recoily);
  void SetLumi(double lumi);
  void Print();
  
  double Recoilx() const;
  double Recoily() const;
  double Recoil() const;
  double RecoilPhi() const;
  double GetLumi() const;

 private:
  double _lumi;
  double _recoilx;
  double _recoily;
};


inline double PMCSRecoil::GetLumi() const { return _lumi; }
inline double PMCSRecoil::Recoilx() const {return _recoilx;}
inline double PMCSRecoil::Recoily() const {return _recoily;}
inline double PMCSRecoil::Recoil() const {return sqrt(_recoilx*_recoilx+_recoily*_recoily);}

inline double PMCSRecoil::RecoilPhi() const {
  return kinem::phi(_recoilx, _recoily);
}

inline void PMCSRecoil::Print() {std::cout<<"(recoilx="<<_recoilx<<",recoily="
                                          <<_recoily<<",recoil="<<Recoil()<<")"<<std::endl;}

#endif
