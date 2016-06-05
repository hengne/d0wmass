#ifndef INC_PMCSZMUCAND
#define INC_PMCSZMUCAND

#include "PMCSParticle.hpp"
#include "PMCSMuon.hpp"

#include <math.h>
#include "TVector2.h"

class PMCSZMuCand {
 public:
  PMCSZMuCand(PMCSMuon mu1, PMCSMuon mu2);
  ~PMCSZMuCand();

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

inline double PMCSZMuCand::pE() const {return _pE;}
inline double PMCSZMuCand::ppx() const {return _ppx;}
inline double PMCSZMuCand::ppy() const {return _ppy;}
inline double PMCSZMuCand::ppz() const {return _ppz;}
inline double PMCSZMuCand::ppt() const {return _ppt;}
inline double PMCSZMuCand::eta() const {return _eta;}
inline double PMCSZMuCand::phi() const {return _phi;}
inline double PMCSZMuCand::rapidity() const {return (0.5*log((_pE+_ppz)/(_pE-_ppz)));}

inline void PMCSZMuCand::Print() const {
  std::cout<<"(pE="<<_pE<<",pT="<<_ppt<<",px="<<_ppx<<",py="<<_ppy<<",pz="<<_ppz<<")"<<std::endl;
}
    
#endif  //INC_PMCSZMUCAND
