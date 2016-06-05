////////////////////////////////////////////////////////////////
///     File: CAFCaloTower.hpp                               ///
///     Created: J. Zhu  March 5, 2005                       ///
///     Purpose: Used for min-bias analysis to               ///
///                find average energy flow per tower        ///
///              Also can be used in W->enu events to check  ///
///                energy flow per tower                     ///
///                                                          ///
////////////////////////////////////////////////////////////////

#ifndef CAFCALOTOWER_HPP__
#define CAFCALOTOWER_HPP__

#include <iostream>
#include "wmass_util/CAFCaloCell.hpp"

class CAFCaloTower {
    
  public:
   CAFCaloTower(int ieta, int iphi, double E, double EME, double FH1E, double Et, double EMEt, double FH1Et);
   virtual ~CAFCaloTower();

   int ieta() const;
   int iphi() const;
   double E() const;
   double EME() const;
   double FH1E() const;
   double Et() const;
   double EMEt() const;
   double FH1Et() const;

   void Print() const;
   
  private:
   int _ieta;
   int _iphi;
   double _E;
   double _Et;
   double _EME;
   double _FH1E;
   double _EMEt;
   double _FH1Et;
   
  public:
    ClassDef(CAFCaloTower, 0);
};

inline int CAFCaloTower::ieta() const {return _ieta;}
inline int CAFCaloTower::iphi() const {return _iphi;}
inline double CAFCaloTower::E() const {return _E;}
inline double CAFCaloTower::EME() const {return _EME;}
inline double CAFCaloTower::FH1E() const {return _FH1E;}
inline double CAFCaloTower::Et() const {return _Et;}
inline double CAFCaloTower::EMEt() const {return _EMEt;}
inline double CAFCaloTower::FH1Et() const {return _FH1Et;}

inline void CAFCaloTower::Print() const {
  std::cout<<"tower ieta="<<_ieta<<",iphi="<<_iphi<<",E="<<_E
           <<",Et="<<_Et<<std::endl;
}
#endif // CAFCALOTOWER_HPP__
