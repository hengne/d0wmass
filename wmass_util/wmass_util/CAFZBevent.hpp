/////////
//

#ifndef CAFZBevent_HPP
#define CAFZBevent_HPP

#include "TTree.h"
#include "TTreeIndex.h"
#include "TFile.h"

class CAFZBevent {

  struct ZBMBevent {
    Int_t runNum;
    Int_t eventNum;
    Float_t InstLum;
    Int_t nPVS;
    Float_t HKset;
    Float_t HKmetx;
    Float_t HKmety;
    Int_t tickNum;
    Int_t timeLastL1Accept;
  };

  TFile* ZBfile;
  TTree* ZBlibrary;
  TTreeIndex* ZBindex;
  ZBMBevent ZBevent;
  
public:

  CAFZBevent();
  CAFZBevent(const char* ZBlibrary_name, const char* tree_name = 0);      
  virtual ~CAFZBevent();
  
  Int_t getZBevent(Int_t runNum, Int_t evtNum);
  Bool_t isOpen() const { return (!ZBfile->IsZombie() && ZBlibrary && ZBindex); } ;

  Int_t getRunNum() const { return ZBevent.runNum; } ;
  Int_t getEventNum() const { return ZBevent.eventNum; } ;
  Float_t getInstLum() const { return ZBevent.InstLum; } ;
  Int_t getnPVS() const { return ZBevent.nPVS; } ;
  Float_t getHKset() const { return ZBevent.HKset; } ;
  Float_t getHKmetx() const { return ZBevent.HKmetx; } ;
  Float_t getHKmety() const { return ZBevent.HKmety; } ;
  Int_t getTickNum() const { return ZBevent.tickNum; } ;
  Int_t getTimeLastL1Accept() const { return ZBevent.timeLastL1Accept; } ;

  ClassDef(CAFZBevent, 0);

};

#endif
