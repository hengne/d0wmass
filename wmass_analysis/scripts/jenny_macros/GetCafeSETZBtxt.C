#include <TFile.h>
#include <TH1.h>
#include <TMath.h>
#include <TF1.h>
#include <TProfile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TTree.h"
#include "TStyle.h"
#include <TLeaf.h>
#include <TBranch.h> 
#include "THStack.h"
#include <iomanip>
#include "TROOT.h"
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include "TGraph.h"
#include <vector>

//**********************************************************
//Change this line if your TTree has a different name
const char *TreeName = "binary_tuple;1";
//**********************************************************

void GetCafeSETZBtxt(){
  
  //   TCanvas *c1 = new TCanvas("c1","c1",800,800);
  //.x /home/jholzbau/rootlogon.C
  TH1::SetDefaultSumw2();
  //  TString rootfile = "/work/yantze-clued0/ddboline/mbzb_p20.17.02/binary_library_MCZB_nodq_Run2b3.root";
  TString rootfile = "/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_tree/wz_epmcs/src/DATA/MBZBLibrary/binary_library_newOVL_shot1.root";

  TTree *tree(0);
  TFile *input(0);
  
  
  if (!gSystem->AccessPathName( rootfile )) {
    cout << "accessing " << rootfile << endl;
    input = TFile::Open( rootfile );
  } 
  else{
    cout<< "problem accessing "<<rootfile<< endl;
    exit(0);
  }
  
  tree = (TTree*)input->Get(TreeName);
  
  int nentries = tree->GetEntries();
  cout<<nentries<<" in tree"<<endl;
    
  ofstream file;
  // file.open ("binary_library_MCZB_nodq_Run2b3.txt");
  file.open ("binary_library_MCZB_Run2b12.txt");

  for (int j = 0; j < nentries; j++){
    if ( j % 100000 == 0 ) cout<<"ZBL "<<j<<endl;
    tree->GetEntry(j);
    //inFile1 >> runNo >> evtNo >> instlumi >> nVtx >> scalarEt >> metx >> mety;
    file <<(int)tree->GetLeaf("runNum")->GetValue(0)<<" "<<(int)tree->GetLeaf("eventNum")->GetValue(0)<<" "<<tree->GetLeaf("InstLum")->GetValue(0)<<" "<<tree->GetLeaf("nPVS")->GetValue(0)<<" "<<tree->GetLeaf("HKset")->GetValue(0)<<" "<<tree->GetLeaf("HKmetx")->GetValue(0)<<" "<<tree->GetLeaf("HKmety")->GetValue(0)<<endl;
  }

  file.close();
  
}
