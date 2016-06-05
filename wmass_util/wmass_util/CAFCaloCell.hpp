/////////////////////////////////////////////////////
///     File: CAFCaloCell.hpp                     ///
///     Created: J. Zhu  March 5, 2005            ///
///     Purpose: inherited from TMBCaloCell       ///
///              Used for min-bias analysis       ///
///              and re-calculate MET             ///
///                                               ///
///              Will read calorimeter geometry   ///
///              file later                       ///
/////////////////////////////////////////////////////

#ifndef CAFCALOCELL_HPP__
#define CAFCALOCELL_HPP__
#include <iostream>

#include "tmb_tree/TMBCaloCell.hpp"

class CAFCaloCell : public TMBCaloCell {
    
  public:
   CAFCaloCell(const TMBCaloCell& p);
   virtual ~CAFCaloCell();

   //cells in coarse hadronic calorimeter
   bool CHCell() const;
   bool IsEM() const;
   bool IsFH1() const;
   bool IsCC() const;
   bool IsEC() const;
   
   void Print() const;
   
  private:
    
  public:
    ClassDef(CAFCaloCell, 0);
};
 
inline bool CAFCaloCell::CHCell() const {return (layer()>=15);}
inline bool CAFCaloCell::IsEM() const {
  return ( (layer()>=1) && (layer()<=7) );
}
inline bool CAFCaloCell::IsFH1() const {return (layer()==11);}
inline bool CAFCaloCell::IsCC() const {return (abs(ieta())<=13);}
inline bool CAFCaloCell::IsEC() const {return (abs(ieta())>13);}

inline void CAFCaloCell::Print() const {
  std::cout<<"cell ieta="<<ieta()<<",iphi="<<iphi()<<",ilyr="<<layer()
           <<",E="<<E()<<std::endl;
}
#endif // CAFCALOCELL_HPP__
