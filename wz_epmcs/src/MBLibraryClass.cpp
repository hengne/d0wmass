#include "MBLibraryClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <iostream>

using namespace std;

MBLibraryClass::MBLibraryClass() : fChain(0) {}

MBLibraryClass::MBLibraryClass(const char* filename)
{
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*) f->Get("binary_tuple");
  Init(tree);
}

MBLibraryClass::~MBLibraryClass()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t MBLibraryClass::GetEntry(Long64_t entry)
{
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t MBLibraryClass::LoadTree(Long64_t entry)
{
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MBLibraryClass::Init(TTree *tree)
{
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("runNo", &runNo, &b_runNo);
  fChain->SetBranchAddress("evtNo", &evtNo, &b_evtNo);
  fChain->SetBranchAddress("instlumi", &instlumi, &b_instlumi);
  fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
  fChain->SetBranchAddress("scalarEt", &scalarEt, &b_scalarEt);
  fChain->SetBranchAddress("metx", &metx, &b_metx);
  fChain->SetBranchAddress("mety", &mety, &b_mety);
  Notify();
}

Bool_t MBLibraryClass::Notify()
{

   return kTRUE;
}

Long64_t MBLibraryClass::copyToArrays(Int_t* runNo_array, Int_t* evtNo_array, Double_t* instlumi_array,
				      Int_t* nVtx_array, Double_t* scalarEt_array, 
				      Double_t* metx_array, Double_t* mety_array) {
  
  if (fChain == 0) return 0;

  // Avoid memory leakage
  if (runNo_array != 0) delete runNo_array; 
  if (evtNo_array != 0) delete evtNo_array; 
  if (instlumi_array != 0) delete instlumi_array;
  if (nVtx_array != 0) delete nVtx_array;
  if (scalarEt_array != 0) delete scalarEt_array;
  if (metx_array != 0) delete metx_array;
  if (mety_array != 0) delete mety_array;
   
  const Long64_t nentries(fChain->GetEntriesFast());

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    runNo_array[jentry] = runNo;
    evtNo_array[jentry] = evtNo;
    instlumi_array[jentry] = instlumi;
    nVtx_array[jentry] = nVtx;
    scalarEt_array[jentry] = scalarEt;
    metx_array[jentry] = metx;
    mety_array[jentry] = mety;

  }

  return nbytes;
}

Long64_t MBLibraryClass::copyToArrays(Double_t* metx_array, Double_t* mety_array, Double_t* scalarEt_array) {
  
  if (fChain == 0) return 0;
   
  const Long64_t nentries(fChain->GetEntriesFast());

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    scalarEt_array[jentry] = scalarEt;
    metx_array[jentry] = metx;
    mety_array[jentry] = mety;

  }

  return nbytes;
}
   
Int_t MBLibraryClass::size() {

  if (fChain == 0) return -1;
  return fChain->GetEntriesFast();

}
