#ifndef CAFMET_HPP
#define CAFMET_HPP

#include "cafe/Event.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include <iostream>
#include <map>

class CAFMet {
  
 public:
  CAFMet();
  CAFMet(double metx, double mety, double met, double scalarEt);
  CAFMet(double metx, double mety);
  virtual ~CAFMet();
  
  void SetMet(double metx, double mety, double met, double scalarEt);

  // recalculate missingEt from all calorimeter cells
  void SetMet(cafe::Event& event, float vtx[3], std::map<std::pair<int,int>,int>* liste = 0);
  
  double metx() const;
  double mety() const;
  double met() const;
  double scalarEt() const;
  double metphi() const;
  
  void print() const;
  
 private:
  double _metx;
  double _mety;
  double _met;
  double _scalarEt;
  
 public:
  ClassDef(CAFMet, 0);
};

inline double CAFMet::metx() const {return _metx;}
inline double CAFMet::mety() const {return _mety;}
inline double CAFMet::met() const {return _met;}
inline double CAFMet::scalarEt() const {return _scalarEt;}
inline double CAFMet::metphi() const {return (kinem::phi(_metx, _mety)); }

inline void CAFMet::print() const {
  std::cout<<"metx="<<_metx<<",mety="<<_mety<<",met="<<_met<<",scalarEt="<<_scalarEt<<std::endl;
}

#endif // CAFMET_HPP
