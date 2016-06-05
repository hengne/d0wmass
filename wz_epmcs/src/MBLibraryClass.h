//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Feb  4 09:05:32 2014 by ROOT version 5.22/00a
// from TTree MBLibraryClass/MBLibraryClass
// found on file: mblibtest_default_Run3_nozeroset_newmax_setpow0.60_small_smaller_zerofrac0.06.root
//////////////////////////////////////////////////////////

#ifndef MBLibraryClass_h
#define MBLibraryClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class MBLibraryClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runNo;
   Int_t           evtNo;
   Double_t        instlumi;
   Int_t           nVtx;
   Double_t        scalarEt;
   Double_t        metx;
   Double_t        mety;

   // List of branches
   TBranch        *b_runNo;   //!
   TBranch        *b_evtNo;   //!
   TBranch        *b_instlumi;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_scalarEt;   //!
   TBranch        *b_metx;   //!
   TBranch        *b_mety;   //!

   MBLibraryClass();
   MBLibraryClass(const char* filename);
   virtual ~MBLibraryClass();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual Long64_t copyToArrays(Int_t* runNo_array, Int_t* evtNo_array, Double_t* instlumi_array,
				 Int_t* nVtx_array, Double_t* scalarEt_array, 
				 Double_t* metx_array, Double_t* mety_array);
   virtual Long64_t copyToArrays(Double_t* metx_array, Double_t* mety_array, Double_t* scalarEt_array);
   virtual Int_t    size();
};

#endif
