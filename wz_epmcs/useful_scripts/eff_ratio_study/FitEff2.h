//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Apr 16 13:36:15 2010 by ROOT version 5.22/00a
// from TTree ZTree2/
// found on file: ZRootTree2.root
//////////////////////////////////////////////////////////

#ifndef FitEff_h
#define FitEff_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class FitEff {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           ZBrunNum;
   Int_t           ZBeventNum;
   Int_t           runNum;
   Int_t           eventNum;
   Float_t         Mz;
   Float_t         Ptz;
   Float_t         Luminosity;
   Float_t         ScalarEt;
   Float_t         ZUt;
   Float_t         em_e[2];
   Float_t         em_pt[2];
   Float_t         em_eta[2];
   Float_t         em_phi[2];
   Float_t         em_deteta[2];
   Float_t         em_detphi[2];
   Float_t         em_upara[2];
   Float_t         em_trk_prob[2];
   Int_t           em_trk_nsmt[2];
   Float_t         em_trk_pt[2];
   Float_t         em_hmX[2];
   Float_t         weight;

   // List of branches
   TBranch        *b_ZBrunNum;   //!
   TBranch        *b_ZBeventNum;   //!
   TBranch        *b_runNum;   //!
   TBranch        *b_eventNum;   //!
   TBranch        *b_Mz;   //!
   TBranch        *b_Ptz;   //!
   TBranch        *b_Luminosity;   //!
   TBranch        *b_ScalarEt;   //!
   TBranch        *b_ZUt;   //!
   TBranch        *b_em_e;   //!
   TBranch        *b_em_pt;   //!
   TBranch        *b_em_eta;   //!
   TBranch        *b_em_phi;   //!
   TBranch        *b_em_deteta;   //!
   TBranch        *b_em_detphi;   //!
   TBranch        *b_em_upara;   //!
   TBranch        *b_em_trk_prob;   //!
   TBranch        *b_em_trk_nsmt;   //!
   TBranch        *b_em_trk_pt;   //!
   TBranch        *b_em_hmX;   //!
   TBranch        *b_weight;   //!

   FitEff(TTree *tree=0);
   virtual ~FitEff();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(const bool BKG=kFALSE, const bool MC=kFALSE);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef FitEff_cxx
FitEff::FitEff(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ZRootTree2.root");
      if (!f) {
         f = new TFile("ZRootTree2.root");
      }
      tree = (TTree*)gDirectory->Get("ZTree2");

   }
   Init(tree);
}

FitEff::~FitEff()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FitEff::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FitEff::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
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

void FitEff::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ZBrunNum", &ZBrunNum, &b_ZBrunNum);
   fChain->SetBranchAddress("ZBeventNum", &ZBeventNum, &b_ZBeventNum);
   fChain->SetBranchAddress("runNum", &runNum, &b_runNum);
   fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
   fChain->SetBranchAddress("Mz", &Mz, &b_Mz);
   fChain->SetBranchAddress("Ptz", &Ptz, &b_Ptz);
   fChain->SetBranchAddress("Luminosity", &Luminosity, &b_Luminosity);
   fChain->SetBranchAddress("ScalarEt", &ScalarEt, &b_ScalarEt);
   fChain->SetBranchAddress("ZUt", &ZUt, &b_ZUt);
   fChain->SetBranchAddress("em_e", em_e, &b_em_e);
   fChain->SetBranchAddress("em_pt", em_pt, &b_em_pt);
   fChain->SetBranchAddress("em_eta", em_eta, &b_em_eta);
   fChain->SetBranchAddress("em_phi", em_phi, &b_em_phi);
   fChain->SetBranchAddress("em_deteta", em_deteta, &b_em_deteta);
   fChain->SetBranchAddress("em_detphi", em_detphi, &b_em_detphi);
   fChain->SetBranchAddress("em_upara", em_upara, &b_em_upara);
   fChain->SetBranchAddress("em_trk_prob", em_trk_prob, &b_em_trk_prob);
   fChain->SetBranchAddress("em_trk_nsmt", em_trk_nsmt, &b_em_trk_nsmt);
   fChain->SetBranchAddress("em_trk_pt", em_trk_pt, &b_em_trk_pt);
   fChain->SetBranchAddress("em_hmX", em_hmX, &b_em_hmX);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   Notify();
}

Bool_t FitEff::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void FitEff::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t FitEff::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef FitEff_cxx
