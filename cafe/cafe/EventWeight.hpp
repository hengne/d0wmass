#ifndef CAFE_EVENTWEIGHT_HPP_
#define CAFE_EVENTWEIGHT_HPP_

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// EventWeight class to save weights in CAF trees                       //
//                                                                      // 
// Yann Coadou (yann@fnal.gov) 3 March 2006                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOT_TObject
#include "TObject.h"
#endif
#include <string>

/**
 * Store an event weight with its associated name and errors
 *
 * Branch: EventWeight
 *
 * \ingroup eventweight
 */
class EventWeight : public TObject {

private:
  std::string _name;        // Event weight name
  double      _weight;      // Event weight
  double      _weight_pos;  // +1sigma event weight
  double      _weight_neg;  // -1sigma event weight

public:
  EventWeight();

  EventWeight(std::string name, double weight, double weight_pos, double weight_neg);

  void Set(std::string name, double weight, double weight_pos, double weight_neg);

  ~EventWeight();
 
  /// Event weight name
  std::string Name() const {return _name;}

  /// Event weight
  double Weight() const {return _weight;}

  /// Event weight + sigma
  double WeightPos() const {return _weight_pos;}

  /// Event weight - sigma
  double WeightNeg() const {return _weight_neg;}


  ClassDef(EventWeight, 1);
};

#endif // CAFE_EVENTWEIGHT_HPP_
