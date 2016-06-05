#ifndef INC_PMCSJPSIMUCAND
#define INC_PMCSJPSIMUCAND

#include "PMCSParticle.hpp"
#include "PMCSMuon.hpp"

#include <math.h>
#include "TVector2.h"

class PMCSJPsiMuCand {
 public:
  PMCSJPsiMuCand(PMCSMuon mu1, PMCSMuon mu2);
  ~PMCSJPsiMuCand();

  double mass() const; //invariant mass
  double ppt() const;
  double ppx() const;
  double ppy() const;
  double ppz() const;
  double pE() const;
  double eta() const;
  double phi() const;
  double rapidity() const;

  void Print() const;

  PMCSMuon GetMuon1() const;
  PMCSMuon GetMuon2() const;

 private:
  double _ppx;
  double _ppy;
  double _ppz;
  double _ppt;
  double _pE;
  double _eta;
  double _phi;

  PMCSMuon _mu1;
  PMCSMuon _mu2;
};

inline double PMCSJPsiMuCand::pE() const {return _pE;}
inline double PMCSJPsiMuCand::ppx() const {return _ppx;}
inline double PMCSJPsiMuCand::ppy() const {return _ppy;}
inline double PMCSJPsiMuCand::ppz() const {return _ppz;}
inline double PMCSJPsiMuCand::ppt() const {return _ppt;}
inline double PMCSJPsiMuCand::eta() const {return _eta;}
inline double PMCSJPsiMuCand::phi() const {return _phi;}
inline double PMCSJPsiMuCand::rapidity() const {return (0.5*log((_pE+_ppz)/(_pE-_ppz)));}

inline void PMCSJPsiMuCand::Print() const {
  std::cout<<"(pE="<<_pE<<",pT="<<_ppt<<",px="<<_ppx<<",py="<<_ppy<<",pz="<<_ppz<<")"<<std::endl;
}
    
#endif  //INC_PMCSJPSIMUCAND
