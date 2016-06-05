#ifndef CAFE_STATWEIGHT_HPP__
#define CAFE_STATWEIGHT_HPP__

#include <string>
#include <TROOT.h>

namespace cafe {

 /* \brief
    Class to encapsulated information about events selected. Will be overwritten for the 
    event weights. This class is used internally by the StatSample class

    \author  Viatcheslav Shary (shary@fnal.gov)

   */
  class StatSelection {
    
    std::string _name ;
    unsigned long _events ; //< number of selected events
    bool _updated ; //< flag to verify that selections was done only once per event               
    bool _weight ; //< if "true" should be interpreted as "pure" event weigth and not number of events with weight
    
  public:
    StatSelection(const std::string& name, unsigned long events=1, bool weight=false) ;
    virtual ~StatSelection() {}
    
    const std::string& name() const {return _name ;}
    unsigned long addEvent() ; 
    unsigned long nevents() const {return _events ;} 
    bool isUpdated() const {return _updated ;} 
    bool isWeight() const {return _weight ;}
    
    /// return errors calculated relative to the previous selection
    double err(const StatSelection& selection) const ;

    /// Clear the _updated flag in the beginning of the event processing
    virtual void Clear() {_updated = false ;}
    
    bool operator== (const std::string& name) const {return name == _name ;} 

    ClassDef(StatSelection, 0) ;
    
  } ;
  
 /* \brief
    Class to collect different event weights
    This class is used internally by the Stat class

    \author  Viatcheslav Shary (shary@fnal.gov)

   */

  class StatWeight : public StatSelection {

     double  _weight_average ; //< event weight averaged over all previous events
     double _weight; //< the current event weight, must be cleared in the beginnin of the event
     double  _rms2 ; //< weight rms
     double _weight_old ; //< internal bookkeeping variable
     double _rms2_old ; //< internal bookkeeping variable

     double  _weight_average_pos ; //< event weight shifted by +1 sigma averaged over all previous events
     double _weight_pos; //< the current event weight shifted by +1 sigma, must be cleared in the beginnin of the event
     double  _rms2_pos ; //< weight shifted by +1 sigma rms
     double _weight_old_pos ; //< internal bookkeeping variable
     double _rms2_old_pos ; //< internal bookkeeping variable


     double  _weight_average_neg  ; //< event weight shifted by -1 sigma averaged over all previous events
     double _weight_neg; //< the current event weight shifted by -1 sigma , must be cleared in the beginnin of the event
     double  _rms2_neg ; //< weight shifted by -1 sigma  rms
     double _weight_old_neg ; //< internal bookkeeping variable
     double _rms2_old_neg ; //< internal bookkeeping variable


   public: 
     
    StatWeight(const std::string& name="NoName", bool event_selection=false) ;
     ~StatWeight() {}

     /// return average event weight
     double weight_average() const {return _weight_average ;} 

     /// return average event weight (+1sigma)
     double weight_average_pos() const {return _weight_average_pos ;} 

     /// return average event weight (-1sigma)
     double weight_average_neg() const {return _weight_average_neg ;} 

     /// return current event weight
     double weight() const {return _weight ;} 

     /// return current event weight shifted by +1 sigma
     double weight_pos() const {return _weight_pos ;} 

     /// return current event weight shifted by -1 sigma
     double weight_neg() const {return _weight_neg ;} 

     /// return weight rms
     double rms() const ; 

     /// return weight rms/Sqrt(N)
     double err() const ;

    /// return efficiencies errors calculated relative to the previous selection
     double err(const StatWeight& selection) const {return  StatSelection::err((StatSelection) selection) ;}

     /// return weight (shifted by +1 sigma) rms
     double rms_pos() const ; 

     /// return weight (shifted by +1 sigma) rms/Sqrt(N)
     double err_pos() const ;

     /// return weight (shifted by -1 sigma) rms
     double rms_neg() const ; 

     /// return weight (shifted by -1 sigma) rms/Sqrt(N)
     double err_neg() const ;

     /// Clear the weight claclutaion in the beginning of the event processing
     void Clear() ;

    double applyWeight(double weight, double weight_pos=-1.0,  double weight_neg=-1.0) ; 
     
    ClassDef(StatWeight, 0)

   } ;
  
}

#endif // CAFE_STATWEIGHT_HPP__
