#ifndef INC_PMCSEVENT
#define INC_PMCSEVENT

#include "PMCSParticle.hpp"
#include "PMCSEMObj.hpp"
#include "PMCSRecoil.hpp"
#include "PMCSMet.hpp"
#include "PMCSVtx.hpp"
#include "PMCSMuon.hpp"

#include <vector>
#include <algorithm>

class PMCSEvent{
 public:

  PMCSEvent(){;}
  PMCSEvent(int runNo, int evtNo, int MBEvtIndex, int ZBEvtIndex, double evtweight, double instlumi, PMCSParticle& wzboson, std::vector<PMCSEMObj>& emobjs_raw, 
           std::vector<PMCSEMObj>& emobjs_raw_wfsr, std::vector<PMCSEMObj>& emobjs, PMCSMet& met, PMCSRecoil& recoil, PMCSVtx& vtx, std::vector<PMCSMuon>& muons);
  ~PMCSEvent();

  double GetEvtWeight() const;

  // get information for the zerobias event used for the overlay
  // also keep the index to the minbias event
  double GetInstLumi() const;
  int GetRunNo() const;
  int GetEvtNo() const;
  int GetZBEvtIndex() const; 
  int GetMBEvtIndex() const; 

  PMCSParticle GetWZBoson() const;
  std::vector<PMCSEMObj> GetEMObjs() const;
  std::vector<PMCSEMObj> GetRawEMObjs() const;  // No photon merging
  std::vector<PMCSEMObj> GetRawEMObjsWFSR() const;  // simple photon merging
  std::vector<PMCSMuon> GetMuons() const;
  PMCSRecoil GetRecoil() const;
  PMCSMet GetMet() const;
  PMCSVtx GetVtx() const;
  
  double pdfreweights[45];

 private:

  // run number for the zerobias events used for the overlay
  int _runNo;
  
  // event number for the zerobias events used for the overlay
  int _evtNo;

  // instantaneous luminosity for the zerobias event used for the overaly 
  double _instlumi;
  // array index for the zerobias event used for the overlay
  int _ZBEvtIndex;
  // array index for the minbias event used for the overlay
  int _MBEvtIndex;
 
  double _evtweight;
  PMCSParticle _wzboson;
  std::vector<PMCSEMObj> _emobjs;
  std::vector<PMCSEMObj> _raw_emobjs;
  std::vector<PMCSEMObj> _raw_emobjs_wfsr;
  std::vector<PMCSMuon> _muons;
  PMCSRecoil _recoil;
  PMCSMet _met;
  PMCSVtx _vtx;
};

#endif  //INC_PMCSEVENT




