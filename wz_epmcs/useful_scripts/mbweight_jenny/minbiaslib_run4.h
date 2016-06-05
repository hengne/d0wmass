//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec  4 20:33:33 2013 by ROOT version 5.22/00a
// from TTree minbiaslib/minbiaslib
// found on file: ../results/mb/mb_newkillcell__0_20131115114218-16756220.d0cabsrv1.fnal.gov/MBAnalysis.root
//////////////////////////////////////////////////////////

#ifndef minbiaslib_h
#define minbiaslib_h

#include <TH3D.h>
#include <TH1D.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <fstream>
#include <TGraphErrors.h>
#include <TF1.h>
#include <iostream>
#include <fstream>
#include <TProfile.h>

class minbiaslib {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runNum;
   Int_t           eventNum;
   Int_t           ZBrunNum;
   Int_t           ZBeventNum;
   Double_t        lumi;
   Double_t        SET;
   Double_t        ZBSET;
   Double_t        bothSET;
   Double_t        tickNum;
   Double_t        urecopx;
   Double_t        urecopy;
   Double_t        urecopT;
   Double_t        urecophi;
   Double_t        uzbpx;
   Double_t        uzbpy;
   Double_t        uzbpT;
   Double_t        uzbphi;
   Double_t        ubothpx;
   Double_t        ubothpy;
   Double_t        ubothpT;
   Double_t        ubothphi;

   // List of branches
   TBranch        *b_runNum;   //!
   TBranch        *b_eventNum;   //!
   TBranch        *b_ZBrunNum;   //!
   TBranch        *b_ZBeventNum;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_SET;   //!
   TBranch        *b_ZBSET;   //!
   TBranch        *b_bothSET;   //!
   TBranch        *b_tickNum;   //!
   TBranch        *b_urecopx;   //!
   TBranch        *b_urecopy;   //!
   TBranch        *b_urecopT;   //!
   TBranch        *b_urecophi;   //!
   TBranch        *b_uzbpx;   //!
   TBranch        *b_uzbpy;   //!
   TBranch        *b_uzbpT;   //!
   TBranch        *b_uzbphi;   //!
   TBranch        *b_ubothpx;   //!
   TBranch        *b_ubothpy;   //!
   TBranch        *b_ubothpT;   //!
   TBranch        *b_ubothphi;   //!

   minbiaslib(const char* filelist);
   virtual ~minbiaslib();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString name, double rmspow, double zerofrac);
   virtual void     runmain(TString name, double rmspow, double zerofrac);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
  
 const int setbins;
   double setmax;
   double setmin;
   double recoilx[1000], recoilx2[1000], recoily[1000], recoily2[1000], recoilxy[1000];
   int nentries[1000];

   TGraphErrors* meanx;
   TGraphErrors* meany;
   TGraphErrors* rmsx;
   TGraphErrors* rmsy;
   TGraphErrors* corr;

   TF1* meanx_f;
   TF1* meany_f;
   TF1* rmsx_f;
   TF1* rmsy_f;

   ofstream mbfile;
   ofstream mbfilelines;
 
   TProfile* tp_weight;

   TH1D* hset;
   TH1D* hsetnew;


 TH1D* hweight;
 TString nameps;
 TString nameroot;
 TString nameps2;
 TString nameroot2;

 TString name;
  double rmspow;
  double zerofrac;   

};

#endif

#ifdef minbiaslib_cxx
minbiaslib::minbiaslib(const char* filelist) : setbins(50), setmax(100.), setmin(0.)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
 
  for (int i=0; i<setbins; i++) {
    recoilx[i] = 0.;
    recoilx2[i] = 0.;
    recoily[i] = 0.;
    recoily2[i] = 0.;
    recoilxy[i] = 0.;
    nentries[i] = 0;
  }

  tp_weight = new TProfile("tp_weight", "", 50, 0., 100., 0., 50.);
  hset = new TH1D("hset", "", 50, 0., 100.);
  hsetnew = new TH1D("hsetnew", "", 50, 0., 100.);
  hweight = new TH1D("hweight", "", 500, 0., 50.);

  nameps = "test.ps";
  nameroot = "test.root";
  TChain* tree = new TChain("minbias");
  TString reader;
  ifstream list(filelist);
  while (!list.eof()) {
    reader.ReadLine(list);
    tree->Add(reader);
  }
  Init(tree);

 }

minbiaslib::~minbiaslib()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t minbiaslib::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t minbiaslib::LoadTree(Long64_t entry)
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

void minbiaslib::Init(TTree *tree)
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

   fChain->SetBranchAddress("runNum", &runNum, &b_runNum);
   fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
   fChain->SetBranchAddress("ZBrunNum", &ZBrunNum, &b_ZBrunNum);
   fChain->SetBranchAddress("ZBeventNum", &ZBeventNum, &b_ZBeventNum);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("SET", &SET, &b_SET);
   fChain->SetBranchAddress("ZBSET", &ZBSET, &b_ZBSET);
   fChain->SetBranchAddress("bothSET", &bothSET, &b_bothSET);
   fChain->SetBranchAddress("tickNum", &tickNum, &b_tickNum);
   fChain->SetBranchAddress("urecopx", &urecopx, &b_urecopx);
   fChain->SetBranchAddress("urecopy", &urecopy, &b_urecopy);
   fChain->SetBranchAddress("urecopT", &urecopT, &b_urecopT);
   fChain->SetBranchAddress("urecophi", &urecophi, &b_urecophi);
   fChain->SetBranchAddress("uzbpx", &uzbpx, &b_uzbpx);
   fChain->SetBranchAddress("uzbpy", &uzbpy, &b_uzbpy);
   fChain->SetBranchAddress("uzbpT", &uzbpT, &b_uzbpT);
   fChain->SetBranchAddress("uzbphi", &uzbphi, &b_uzbphi);
   fChain->SetBranchAddress("ubothpx", &ubothpx, &b_ubothpx);
   fChain->SetBranchAddress("ubothpy", &ubothpy, &b_ubothpy);
   fChain->SetBranchAddress("ubothpT", &ubothpT, &b_ubothpT);
   fChain->SetBranchAddress("ubothphi", &ubothphi, &b_ubothphi);
   Notify();
}

Bool_t minbiaslib::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void minbiaslib::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t minbiaslib::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef minbiaslib_cxx
