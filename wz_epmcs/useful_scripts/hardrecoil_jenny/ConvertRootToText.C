#include <TVector2.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile2D.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <TTree.h>
#include <TLeaf.h>

using namespace std;
const char *TreeName1 = "hardrecoil";

void ConvertRootToText(){
  //from /prj_root/2673/wz2_write/rclsa/recoil_investigation_wa/HRfiltered
  TFile *f = new TFile("Znunu_RCLSA_newkillcell_runiib3.root");//Znunu_Znunurun_Final.root");//znunu_killcell_20131003_All.root");//Znunu_simple_Znunurun.root");
  TTree *tree = (TTree*)f->Get(TreeName1);
  
  ofstream myfile;
  //myfile.open ("exampleAllkillcellALLFinal.txt");
  myfile.open ("exampleAllkillcellALLFinalupdatedkillcellRun3.txt");
  //   file >> runno >> evtno >> z_px >> z_py >> z_pz >> z_E >> gen_rec_px >> gen_rec_py >> gen_rec_pz >> gen_rec_E >> rec_px >> rec_py >> set;
  int nentries = tree->GetEntries();
  for (int i = 0; i < nentries; i++){
    tree->GetEntry(i);

    myfile <<(int)tree->GetLeaf("ZBrunNum")->GetValue(0)<<" ";
    myfile <<(int)tree->GetLeaf("ZBeventNum")->GetValue(0)<<" ";

    myfile <<(double)tree->GetLeaf("Ztruepx")->GetValue(0)<<" ";
    myfile <<(double)tree->GetLeaf("Ztruepy")->GetValue(0)<<" ";
    myfile <<(double)tree->GetLeaf("Ztruepz")->GetValue(0)<<" ";
    myfile <<(double)tree->GetLeaf("ZtrueE")->GetValue(0)<<" ";
    
    myfile <<(double)tree->GetLeaf("utruepx")->GetValue(0)<<" ";
    myfile <<(double)tree->GetLeaf("utruepy")->GetValue(0)<<" ";
    myfile <<(double)tree->GetLeaf("utruepz")->GetValue(0)<<" ";
    myfile <<(double)tree->GetLeaf("utrueE")->GetValue(0)<<" ";
    
    myfile <<(double)tree->GetLeaf("urecopx")->GetValue(0)<<" ";
    myfile <<(double)tree->GetLeaf("urecopy")->GetValue(0)<<" ";
    
    // myfile <<(double)tree->GetLeaf("SET")->GetValue(0)<<endl;

     myfile <<(double)tree->GetLeaf("SET")->GetValue(0)<<" ";
     myfile <<(double)tree->GetLeaf("lumi")->GetValue(0)<<" ";
    myfile <<(double)tree->GetLeaf("ZBSET")->GetValue(0)<<endl;

    //Other variables:
    //ZBSET, eventNum, runNum, lumi, nPVS, tickNum, urecopT, urecophi

  }
  myfile.close();
}
