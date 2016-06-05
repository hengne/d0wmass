#ifndef INC_PMCSWCAND
#define INC_PMCSWCAND

#include "PMCSParticle.hpp"
#include "PMCSEMObj.hpp"
#include "PMCSMet.hpp"

#include "TVector2.h"
#include <math.h>

class PMCSWCand{
 public:

  PMCSWCand() {;}
  PMCSWCand(PMCSEMObj &emobj, PMCSRecoil &recoil, PMCSMet &met);
  ~PMCSWCand();

  int Type(double CutEtaCC, double CutEtaEC1, double CutEtaEC2, bool trkphimodcut=true) const;
  double TMass() const;
  double ppx() const;
  double ppy() const;
  double ppt() const;

  TVector2 GetRecoilVec() const;  
  double DeltaPhi_EM_MET() const;
  double DeltaPhi_EM_Recoil() const;
  double UPara() const; //calculate u_para (the projection of the recoil along electron direction)
  double UPerp() const; //calculate u_perp
  double UT() const; //calculate U_t
  double MagRecoil() const;

  // return most interesting properties in one function
  void getProperties(double& mt, double& wpt, double& wupara, double& wuperp) const;

  PMCSEMObj GetElec() const;
  PMCSRecoil GetRecoil() const;
  PMCSMet GetMet() const;

 protected:
 
  double _ppx;
  double _ppy;
  double _ppt;

  PMCSEMObj _elec;
  PMCSRecoil _recoil;
  PMCSMet _met;
};

inline double PMCSWCand::ppx() const {return _ppx;}
inline double PMCSWCand::ppy() const {return _ppy;}
inline double PMCSWCand::ppt() const {return _ppt;}
inline void PMCSWCand::getProperties(double& mt, double& wpt, double& wupara, double& wuperp) const {
  mt = TMass();
  wpt = sqrt(_ppx*_ppx + _ppy*_ppy);
  wupara = UPara();
  wuperp = UPerp();
}

#endif  //INC_PMCSWCAND




