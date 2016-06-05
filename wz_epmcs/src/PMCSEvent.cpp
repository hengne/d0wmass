#include "PMCSEvent.hpp"

#include <iostream>
using namespace std;

PMCSEvent::PMCSEvent(int runNo, int evtNo, int MBEvtIndex, int ZBEvtIndex, double evtweight, double instlumi, PMCSParticle& wzboson, vector<PMCSEMObj>& raw_emobjs, 
                     vector<PMCSEMObj>& raw_emobjs_wfsr, vector<PMCSEMObj>& emobjs, 
		     PMCSMet& met, PMCSRecoil& recoil, PMCSVtx& vtx, vector<PMCSMuon>& muons) {
  _runNo = runNo;
  _evtNo = evtNo;
  _evtweight=evtweight;
  _instlumi = instlumi;
  _ZBEvtIndex = ZBEvtIndex;
  _MBEvtIndex = MBEvtIndex;

  _wzboson = wzboson;
  _raw_emobjs = raw_emobjs;
  _raw_emobjs_wfsr = raw_emobjs_wfsr;
  _emobjs = emobjs;
  _muons = muons;
  _met = met;
  _recoil = recoil;
  _vtx = vtx;
  for( int i = 0 ; i < 45 ; i++ )
     pdfreweights[i] = 1.0;
}

// get information for the run number, instantaneous luminosity and also index for the overlay zerobias event
// also keep the index for the minbias events
int PMCSEvent::GetRunNo() const {return _runNo;}
int PMCSEvent::GetEvtNo() const {return _evtNo;}
double PMCSEvent::GetEvtWeight() const {return _evtweight;}
double PMCSEvent::GetInstLumi() const {return _instlumi;}
int PMCSEvent::GetZBEvtIndex() const {return _ZBEvtIndex;}
int PMCSEvent::GetMBEvtIndex() const {return _MBEvtIndex;}

PMCSParticle PMCSEvent::GetWZBoson() const {return _wzboson;}
vector<PMCSEMObj> PMCSEvent::GetRawEMObjs() const {return _raw_emobjs;}
vector<PMCSEMObj> PMCSEvent::GetRawEMObjsWFSR() const {return _raw_emobjs_wfsr;}
vector<PMCSEMObj> PMCSEvent::GetEMObjs() const {return _emobjs;}
vector<PMCSMuon> PMCSEvent::GetMuons() const {return _muons;}
PMCSRecoil PMCSEvent::GetRecoil() const {return _recoil;}
PMCSMet PMCSEvent::GetMet() const {return _met;}
PMCSVtx PMCSEvent::GetVtx() const {return _vtx;}

PMCSEvent::~PMCSEvent() {
}
