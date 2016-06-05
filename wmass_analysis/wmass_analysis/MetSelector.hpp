///////////////////////////////////////////////////////////////////
///    File: MetSelector.hpp                                    ///
///    Created: J. Zhu March 3, 2005                            ///
///                                                             ///
///    Purpose: code used to extract missingET and              ///
///             recalculate missingET for different vertex      ///
///                                                             ///
///////////////////////////////////////////////////////////////////
#ifndef METSELECTOR_HPP
#define METSELECTOR_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "cafe/Event.hpp"
#include "wmass_util/CAFMet.hpp"
#include "wmass_util/CAFEMObj.hpp"

class MetSelector:public cafe::Processor {

 public:
  
  MetSelector(const char *name);
  virtual ~MetSelector();
  
  // extract missingET
  void extract(cafe::Event& event, std::vector<CAFEMObj*> emobjs);
  
  // recalculate missingET for different primary vertex
  void applyCorrection(cafe::Event& event, std::vector<CAFEMObj*> emobjs, float vtx_old[3], float vtx_new[3], std::map<std::pair<int,int>,int>* liste);

  // make EM corrected MET
  void make_EMCorr(cafe::Event& event, std::vector<CAFEMObj*> emobjs, float metX_raw, float metY_raw, float met_raw, float scalarEt_raw,
		   float& metX_new, float& metY_new, float& met_new, float& scalarEt_new); 
 
  // put pointers to event
  void putPointers(cafe::Event& event);
 
  // get raw met
  CAFMet getRawMet() const;
  
  // get Met with electron energy correction applied
  CAFMet getCorrEMMet() const;
  
 private:
 
  // debug level
  int _debugLevel;

  bool _met_only_use_Selected_emobjs;

  // raw missingET
  CAFMet _rawMet;
  
  // raw missingET + EM correction
  CAFMet _corrEMMet;
  
  cafe::Variables _metex_vars;
  
 public:
  ClassDef(MetSelector, 0);
};

inline CAFMet MetSelector::getRawMet() const {return _rawMet;}
inline CAFMet MetSelector::getCorrEMMet() const {return _corrEMMet;}

#endif // METSELECTOR_HPP
