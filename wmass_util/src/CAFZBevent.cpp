#include "wmass_util/CAFZBevent.hpp"

CAFZBevent::CAFZBevent() : ZBfile(0), ZBlibrary(0), ZBindex(0) {};
CAFZBevent::CAFZBevent(const char* ZBlibrary_name, const char* tree_name /*=0*/) {
  
  ZBfile = new TFile(ZBlibrary_name);
  if (ZBfile->IsZombie()) return;
  if (tree_name)
    ZBlibrary = (TTree*) ZBfile->Get(tree_name);
  else 
    ZBlibrary = (TTree*) ZBfile->Get("binary_tuple");
  if (!ZBlibrary) return;
  ZBlibrary->SetBranchAddress("event", &ZBevent);
  ZBindex = new TTreeIndex(ZBlibrary, "event.runNum", "event.eventNum");
  
}

CAFZBevent::~CAFZBevent() {
  
  if (ZBindex) delete ZBindex;
  if (ZBfile) ZBfile->Close();
  
}

Int_t CAFZBevent::getZBevent(Int_t runNum, Int_t evtNum) {
  
  Long64_t index = ZBindex->GetEntryNumberWithIndex(runNum, evtNum);
  return ZBlibrary->GetEntry(index);
  
}

ClassImp(CAFZBevent)


