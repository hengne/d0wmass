///////////////////////////////////////////////////////////////////
///    File: TrigObjSelector.hpp                                ///
///    Created: J. Zhu March 3, 2005                            ///
///                                                             ///
///    Purpose: code used to select L1/L2/L3 trigger objects    ///
///                                                             ///
///////////////////////////////////////////////////////////////////
#ifndef TRIGOBJSELECTOR_HPP
#define TRIGOBJSELECTOR_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"

#include "cafe/Event.hpp"
#include "tmb_tree/TMBL1CalTower.hpp"
#include "tmb_tree/TMBL1Cal2bEM.hpp"
#include "tmb_tree/TMBL2GblEM.hpp"
#include "tmb_tree/TMBL3Ele.hpp"

class TrigObjSelector:public cafe::Processor {
  
 public:
  
  TrigObjSelector(const char *name);
  virtual ~TrigObjSelector();
  
  // extract L1/L2/L3 trigger objects
  void extract(cafe::Event& event);

  // put pointers to event
  void putPointers(cafe::Event& event);
  std::vector<const TMBL1CalTower*> getL1TrigObjs() const;
  std::vector<const TMBL1Cal2bEM*> getL12bTrigObjs() const;
  std::vector<const TMBL2GblEM*> getL2TrigObjs() const;
  std::vector<const TMBL3Ele*> getL3TrigObjs() const;
  
 private:
  // debug level
  int _debugLevel;

  // minimum pT cut
  float _TrigObjPtCut_L1, _TrigObjPtCut_L2, _TrigObjPtCut_L3;
  
  // L1 trigger objects
  std::vector<const TMBL1CalTower*> _l1_trigobjs;  
  
  // L1 RunIIb trigger objects
  std::vector<const TMBL1Cal2bEM*> _l12b_trigobjs;

  // L2 trigger objects
  std::vector<const TMBL2GblEM*> _l2_trigobjs;

  // L3 trigger objects
  std::vector<const TMBL3Ele*> _l3_trigobjs;  

  cafe::Variables _l1_vars;
  cafe::Variables _l2_vars;
  cafe::Variables _l3_vars;

 public:
  ClassDef(TrigObjSelector, 1);
};

inline std::vector<const TMBL1CalTower*> TrigObjSelector::getL1TrigObjs() const {return _l1_trigobjs;}
inline std::vector<const TMBL1Cal2bEM*> TrigObjSelector::getL12bTrigObjs() const {return _l12b_trigobjs;}
inline std::vector<const TMBL2GblEM*> TrigObjSelector::getL2TrigObjs() const {return _l2_trigobjs;}
inline std::vector<const TMBL3Ele*> TrigObjSelector::getL3TrigObjs() const {return _l3_trigobjs;}

#endif // TRIGOBJSELECTOR_HPP
