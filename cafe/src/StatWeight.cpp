#include "cafe/StatWeight.hpp"
#include <iostream> 
#include <math.h> 

using namespace std ;

namespace cafe {
  
  StatSelection::StatSelection(const std::string& name, unsigned long events, bool weight) : 
    _name(name), _events(events)
  {
    if (events==0) 
      _updated = false ;
    else 
      _updated = true ;
    _weight = weight ;
  }

  double StatSelection::err(const StatSelection& selection) const {
    if (selection.nevents() < _events ) {
      cout << "cafe::StatSelection: error in the events sample order! "
	   << "Number of events in the preciding selection " << selection.nevents() 
	   << " less than in the following one " << _events << "!"  
	   << endl ;
      return 0 ;
    }   
    double eff = ((double)_events) / selection.nevents() ;    
    return sqrt(eff*(1-eff)/selection.nevents()) ;
  }

  unsigned long StatSelection::addEvent() {    
    if (!_updated) { 
      _events++; 
      _updated = true ;
    } 
    return _events;
  }


  StatWeight::StatWeight(const std::string& name, bool event_selection) : StatSelection(name, 0, !event_selection), 
						    _weight_average(1.0),_weight(1.0),
						    _rms2(0), _weight_old(0), _rms2_old(0),
						    _weight_average_pos(-1.0),_weight_pos(1.0),
						    _rms2_pos(0), _weight_old_pos(0), _rms2_old_pos(0),
						    _weight_average_neg(-1.0),_weight_neg(1.0),
						    _rms2_neg(0), _weight_old_neg(0), _rms2_old_neg(0)
  { }

  void StatWeight::Clear() {
    StatSelection::Clear() ;
    _weight = 1.0 ;
    _weight_old = 0 ;
    _weight_pos = 1.0 ;
    _weight_old_pos = 0 ;
    _weight_neg = 1.0 ;
    _weight_old_neg = 0 ;
  }

  double StatWeight::applyWeight(double weight, double weight_pos,  double weight_neg ) {

    // negative weights are allowed. weight_pos and weight_neg (sytematics) 
    // are still can used only as positive weights

    if (isUpdated() && !isWeight() ) return _weight ;

    if (!isUpdated())  {
      _weight_old = _weight_average ;
      _rms2_old = _rms2 ;
      _weight_old_pos = _weight_average_pos ;
      _rms2_old_pos = _rms2_pos ;
      _weight_old_neg = _weight_average_neg ;
      _rms2_old_neg = _rms2_neg ;
    }

    addEvent() ;
    _weight *= weight ;
    
    if (weight_pos >= 0) 
      _weight_pos *= weight_pos ;
    if (weight_neg >= 0) 
      _weight_neg *= weight_neg ;

    if (nevents() == 1) {
      _weight_average = _weight ;
      if (weight_pos >= 0) 
	_weight_average_pos = _weight_pos ;
      if (weight_neg >= 0) 
	_weight_average_neg = _weight_neg ;
      _rms2 = 0 ;
      _rms2_pos = 0 ;
      _rms2_neg = 0 ;
    } else {
      _rms2 = ((double) nevents()-2)/(nevents()-1)*_rms2_old + pow(_weight-_weight_old,2)/nevents() ;
      if (weight_pos >= 0) 
	_rms2_pos = ((double) nevents()-2)/(nevents()-1)*_rms2_old_pos + 
	  pow(_weight_pos-_weight_old_pos,2)/nevents() ;
      if (weight_neg >= 0) 
	_rms2_neg = ((double) nevents()-2)/(nevents()-1)*_rms2_old_neg + 
	  pow(_weight_neg-_weight_old_neg,2)/nevents() ;

      _weight_average = _weight_old*(((double)nevents()-1)/nevents()) + _weight/nevents() ;
      if (weight_pos >= 0) 
	_weight_average_pos = _weight_old_pos*(((double)nevents()-1)/nevents()) + _weight_pos/nevents() ;
      if (weight_neg >= 0) 
	_weight_average_neg = _weight_old_neg*(((double)nevents()-1)/nevents()) + _weight_neg/nevents() ;
    }

    return _weight ;
  }

  double StatWeight::err() const {
    if (nevents() <= 1 || _rms2 <= 0) return 0.0 ;
    return sqrt(_rms2/nevents()) ;
  }

  double StatWeight::err_pos() const {
    if (nevents() <= 1 || _rms2_pos <= 0) return 0.0 ;
    return sqrt(_rms2_pos/nevents()) ;
  }

  double StatWeight::err_neg() const {
    if (nevents() <= 1 || _rms2_neg <= 0) return 0.0 ;
    return sqrt(_rms2_neg/nevents()) ;
  }


  double StatWeight::rms() const {
    return _rms2 >0 ? sqrt(_rms2) : 0.0 ;
  }

  double StatWeight::rms_pos() const {
    return _rms2_pos >0 ? sqrt(_rms2_pos) : 0.0 ;
  }

  double StatWeight::rms_neg() const {
    return _rms2_neg >0 ? sqrt(_rms2_neg) : 0.0 ;
  }

}

ClassImp(cafe::StatSelection);
ClassImp(cafe::StatWeight);
