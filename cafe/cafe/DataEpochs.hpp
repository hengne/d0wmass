#ifndef CAFE_DATAEPOCHS_HPP__
#define CAFE_DATAEPOCHS_HPP__

#include <string>
#include <map>

namespace cafe {

    /**
     * return run number corresponding to the specified data epoch name
     * according to the CSG definitions. The most recent epoch (current) 
     * return 999999 as run number.
     * see: http://www-d0.fnal.gov/Run2Physics/cs/skimming/run2_overview.html
     * available names: RunII, RunIIa, RunIIb, RunIIb1, RunIIb2, RunIIb3, RunIIb4
     *                  runII, runIIa, runIIb, runIIb1, runIIb2, runIIb3, runIIb4
     *                  Run2,  Run2a,  Run2b,  Run2b1,  Run2b2,  Run2b3,  Run2b4
     *                  run2,  run2a,  run2b,  run2b1,  run2b2,  run2b3,  run2b4
     * 
     * Author: V. Shary 
     * date: April 2010
     *
     * \ingroup cafe
     */
  class DataEpochs { 

    enum Epoch {RunIIa, RunIIb1, RunIIb2, RunIIb3, RunIIb4, RunIIb, RunII, UNKNOWN} ;

    // for data: epoch name and min/max runs    
    std::map<Epoch, std::pair<unsigned int, unsigned int> > _epoch ;

    // convert string to enum for epoch
    Epoch str_enum(const std::string& epoch) const  ;

  public:

    DataEpochs();

    unsigned int firstRun(const std::string& epoch) const ;
    unsigned int lastRun(const std::string& epoch) const ;
    
    // verify if the epoch name  exist
    bool epochExist(const std::string& epoch) const ;


  };
  
}

#endif // CAFE_DATAEPOCHS_HPP__
