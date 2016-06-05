#ifndef INC_PMCSPARTICLE
#define INC_PMCSPARTICLE

#include "TLorentzVector.h"
#include "TVector3.h"
#include <iostream>

#include <math.h>

class PMCSParticle {

 public:

  // default constructor
  PMCSParticle();

  // simple constructor
  // pT for WZ boson is not simple pE*sin(theta)
  PMCSParticle(double ppid, double pE, double peta, double pphi, double ppx, double ppy, double ppz);

  // complete constructor
  PMCSParticle(double pE, double peta, double pphi, double ppid,
	       double ppt, double ppx, double ppy, double ppz);
  ~PMCSParticle() {;}

  // modify energy, px, py, pz for given pT, peta, pphi
  void SetpTEtaPhi(double pT, double peta, double pphi);

  // print out particle information
  void Print() const;
  
  // sort particles accoording to pT
  friend bool ComparePt(const PMCSParticle part1, const PMCSParticle part2);
  // sort particles accoording to E
  friend bool CompareE(const PMCSParticle part1, const PMCSParticle part2);
  
  double pE() const;
  double peta() const;
  double eta() const;
  double theta() const;
  double pphi() const;
  double phi() const;
  double ppid() const;
  double ppt() const;
  double ppx() const;
  double ppy() const;
  double ppz() const;

  TLorentzVector GetLorentzVect() const;
  TVector3 GetVect3() const;
  
  double Mass() const;
  
  bool IsW() const;
  bool IsZ() const;
  bool IsElectron() const;
  bool IsPhoton() const;
  
 protected:
  double _pE;
  double _peta;
  double _pphi;
  double _ppid;
  double _ppt;
  double _ppx;
  double _ppy;
  double _ppz;
};

inline double PMCSParticle::pE() const {return _pE;}
inline double PMCSParticle::peta() const {return _peta;}
inline double PMCSParticle::eta() const {return _peta;}
inline double PMCSParticle::theta() const {return (2.*atan(exp(-_peta)));}
inline double PMCSParticle::pphi() const {return _pphi;}
inline double PMCSParticle::phi() const {return _pphi;}
inline double PMCSParticle::ppid() const {return _ppid;}
inline double PMCSParticle::ppt() const {return _ppt;}
inline double PMCSParticle::ppx() const {return _ppx;}
inline double PMCSParticle::ppy() const {return _ppy;}
inline double PMCSParticle::ppz() const {return _ppz;}

inline TLorentzVector PMCSParticle::GetLorentzVect() const {
  TLorentzVector vect(_ppx, _ppy, _ppz, _pE);
  return vect;
}

inline TVector3 PMCSParticle::GetVect3() const {
  TVector3 vect(_ppx, _ppy, _ppz);
  return vect;
}

inline void PMCSParticle::Print() const {
  std::cout<<"(id="<<_ppid<<",pE="<<_pE<<",pT="<<_ppt<<",eta="<<_peta<<",phi="<<_pphi<<")"<<std::endl;
  std::cout<<"(px="<<_ppx<<",py="<<_ppy<<",_pz="<<_ppz<<")"<<std::endl;
}

#endif
