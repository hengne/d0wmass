#include "cafe/DataEpochs.hpp"
#include <stdexcept>

using namespace std;

namespace cafe {
  
  DataEpochs::DataEpochs() {
    _epoch[RunII] = pair<unsigned int, unsigned int>(151817,999999) ;
    _epoch[RunIIa] = pair<unsigned int, unsigned int>(151817,215670) ;
    _epoch[RunIIb] = pair<unsigned int, unsigned int>(221698,999999) ;
    _epoch[RunIIb1] = pair<unsigned int, unsigned int>(221698,234999) ;
    _epoch[RunIIb2] = pair<unsigned int, unsigned int>(237342,254962) ;
    _epoch[RunIIb3] = pair<unsigned int, unsigned int>(255329,262856) ;
    _epoch[RunIIb4] = pair<unsigned int, unsigned int>(262857,999999) ;
  }
  
  DataEpochs::Epoch  DataEpochs::str_enum(const std::string& epoch) const {

    if (epoch == "RunII" || epoch == "runII" || epoch == "Run2" || epoch == "run2") return RunII ;
    if (epoch == "RunIIb" || epoch == "runIIb" || epoch == "Run2b" || epoch == "run2b") return RunIIb ;
    if (epoch == "RunIIa" || epoch == "runIIa" || epoch == "Run2a" || epoch == "run2a") return RunIIa ;
    if (epoch == "RunIIb1" || epoch == "runIIb1" || epoch == "Run2b1" || epoch == "run2b1") return RunIIb1 ;
    if (epoch == "RunIIb2" || epoch == "runIIb2" || epoch == "Run2b2" || epoch == "run2b2") return RunIIb2 ;
    if (epoch == "RunIIb3" || epoch == "runIIb3" || epoch == "Run2b3" || epoch == "run2b3") return RunIIb3 ;
    if (epoch == "RunIIb4" || epoch == "runIIb4" || epoch == "Run2b4" || epoch == "run2b4") return RunIIb4 ;
    return UNKNOWN ;
  }
  
  unsigned int DataEpochs::firstRun(const std::string& epoch) const {

    Epoch e = str_enum(epoch) ;
    if (e == UNKNOWN) 
      throw runtime_error("cafe::DataEpochs ERROR: couldn't find epoch for the name [" + epoch + "]") ;

    map<Epoch, pair<unsigned int, unsigned int> >::const_iterator it =  _epoch.find(e) ;
    if (it == _epoch.end())
      throw runtime_error("cafe::DataEpochs ERROR: epoch [" + epoch + "] is not configurated") ;
    return  it->second.first ;
  }

  unsigned int DataEpochs::lastRun(const std::string& epoch) const {
    Epoch e = str_enum(epoch) ;
    if (e == UNKNOWN) 
      throw runtime_error("cafe::DataEpochs ERROR: couldn't find epoch for the name [" + epoch + "]") ;

    map<Epoch, pair<unsigned int, unsigned int> >::const_iterator it =  _epoch.find(e) ;
    if (it == _epoch.end())
      throw runtime_error("cafe::DataEpochs ERROR: epoch [" + epoch + "] is not configurated") ;
    return  it->second.second ;
  }

  bool DataEpochs::epochExist(const string& epoch) const {

    Epoch e = str_enum(epoch) ;
    if (e == UNKNOWN) return false ;      

    map<Epoch, pair<unsigned int, unsigned int> >::const_iterator it =  _epoch.find(e) ;
    if (it == _epoch.end()) 
      throw runtime_error("cafe::DataEpochs ERROR: mismatch between str_enum and epoch list for [" + epoch + "]") ; 
    return true ;
  }

}

