#ifndef CAFE_STATSAMPLE_HPP__
#define CAFE_STATSAMPLE_HPP__

#include "cafe/Event.hpp" 
#include "cafe/StatWeight.hpp" 

#include <string>
#include <vector>

namespace cafe {
  
  struct  StatWeightNotFoundException {
    std::string _weight_name ;
    StatWeightNotFoundException(std::string weight_name): _weight_name(weight_name) {}
  };

  /* \brief
     Class to collect number of events for the one sample of statistics.
     This class is used internally by the Stat class.
     
     \authors  Viatcheslav Shary (shary@fnal.gov), Yann Coadou (yann@fnal.gov)
     
  */
  class StatSample {
    
    std::string _name ; //< sample name
    std::vector<std::string> _tags ; //< tags used to add events to the sample (ANY)
    std::vector<std::string> _tags_and ; //< tags requiered with AND 
    std::vector<StatWeight*> _events; //< selected events and associated global events weight for each selection 
    StatWeight* _weight ; //< the global event weight is a product of all weight applied to the event up to the current selection 

  public: 
    
    StatSample(const std::string& sample="data") ;
    virtual ~StatSample() ;
    
    const std::string& name() const {return _name ;}
    const std::vector<std::string>& tags() const {return _tags ;}
    const std::vector<std::string>& tagsAnd() const {return _tags_and ;}
    
    /// add tag required for this sample with ANY logic
    void AddTags(const std::string& tag) {_tags.push_back(tag);}
    
    /// add tags required for this sample with ANY logic
    void AddTags(const std::vector<std::string>& tags) ;
    
    /// add tags required for this sample with AND logic
    void AddAndTags(const std::vector<std::string>& tags) ;
    
    /// add tag required for this sample with AND logic
    void AddAndTags(const std::string& tag) {_tags_and.push_back(tag);}
    
    //return false if events does not have tags used for this sample
    bool tagged(const cafe::Event* event) const  ;
    
    /// return number of selections for this sample (The initial selection always exist)
    unsigned int size() const { return _events.size();} 
    
    /// return number of events for the selection n 
    unsigned long nevents(unsigned int n = 0) const ;
    
    /// return number of events for the selection with specified name 
    unsigned long nevents(const std::string& name) const ;
    
    /// return event selection efficiency or the average weight for a weight by number 
    double eff(unsigned int n = 0) const ;
    
    /// return the event selection efficiency by name 
    double eff(const std::string& name) const ;
    
    /// return global event selection efficiency  (relative to the initial number of events)
    /// (n = 0 means last selection / first one)
    double effGlob(unsigned int n = 0) const ;
    
    /// return global event selection efficiency  (relative to the initial number of events)
    double effGlob(const std::string& name) const ;

    /// return global event selection efficiency  (relative to the initial number of events)
    /// corrected by the global event weight 
    /// (n = 0 means last selection / first one)
    double correctedEfficiency(unsigned int n = 0) const ;
    
    /// return global event selection efficiency  (relative to the initial number of events)
    /// corrected by the global event weight 
    double correctedEfficiency(const std::string& name) const ;
    
    /// return event selection efficiency error or the average weight for a weight by number
    double effErr(unsigned int n = 0) const ;
    
    /// return event selection efficiency error by name
    double effErr(const std::string& name) const ;
    
    /// return global event selection efficiency error (n = 0 means last selection / first one)
    double effErrGlob(unsigned int n = 0) const ;
    
    /// return global event selection efficiency error (n = 0 means last selection / first one)
    double effErrGlob(const std::string& name) const ;
    
    /// return global event selection efficiency error (n = 0 means last selection / first one)
    /// corrected by the global event weight
    double correctedEffErr(unsigned int n = 0) const ;
    
    /// return global event selection efficiency error (n = 0 means last selection / first one)
    /// corrected by the global event weight
    double correctedEffErr(const std::string& name) const ;
    
    /// return event selection by number
    const StatWeight* eventSelection(unsigned int n = 0) const ;
    
    /// return event selection by name
    const StatWeight* eventSelection(const std::string& name) const ;
    
    /// return event weight by number in the selection vector
    const StatWeight* eventWeight(unsigned int n) const ;

    /// return event weight by name. Return global event weight by default
    const StatWeight*  eventWeight(const std::string& name="global") const ;
    
    /// return a Collection of event weights available. The global event weight comes first
    Collection<EventWeight> ListEventWeights() const ;

    /// return true if all selection names in both samples are equal
    bool compareNames(const StatSample& sample) const ;

    /// increase event number for the selection by 1 
    unsigned long add(cafe::Event* event, const std::string& name="Initial") ;
    
    /// apply event weight 
    double applyWeight(cafe::Event* event, const std::string& name, 
		       double weight, double weight_pos, double weight_neg) ;

    /// reset selection flags _selected
    void Clear() ; 

    /// Print sample as a html table 
    ostream& HtmlTable(ostream& os) const ;

    /// Print sample as a tex table
    ostream& print_tex (ostream& os, const std::string title) const ;

    /// Convert string to the tex usable format
    static std::string tex(const std::string& init) ;

  public:
       ClassDef(StatSample, 0);     

   } ;
  
}

#endif // CAFE_STATSAMPLE_HPP__
