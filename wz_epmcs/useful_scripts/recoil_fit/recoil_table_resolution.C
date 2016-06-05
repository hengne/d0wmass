#include <TApplication.h>
#include <fstream>
#include <iostream>
#include "TRandom.h"
#include "TH1D.h"
#include "TFile.h"
#include "TCut.h"
#include "TTree.h"
#include "TPad.h"

typedef TH1D* TH1Dptr;
using namespace std;

const double prec = 0.0001;

bool closeto(double a, double b) {
  if ((a<b*(1+prec))&&(a>b*(1-prec))){
    return true;
  } else {
    return false;
  }
}

void recoil_table_resolution(bool makecuts=false, int mode=0){

  double etaLowCuts[10] = {-10., -10., -10., -10., -10., -10., -10., -8., -7., -6.};
  double etaHighCuts[10] = {10., 12., 12., 12., 12., 12., 15., 15., 16., 21.};

  double dataVal[10], dataValErr[10];
  TString dname;

  if (mode==0) {
  // Get data
  TFile* ref = new TFile("result_geant.root","READ");
  ref->cd("ZCand_Hist");
  for( int i=0 ; i<10 ; i++ ) {
    dname.Form("ZCandEtaImBalance_bin_%d", i);
    TH1 *h = (TH1*) gROOT->FindObject(dname);
    if (makecuts) h->GetXaxis()->SetRange(h->FindBin(etaLowCuts[i]),h->FindBin(etaHighCuts[i]));
    dataVal[i] = h->GetRMS();
    dataValErr[i] = h->GetRMSError();
  }
  ref->Close();
  }

  // Output file
  ofstream resolution("resolution.txt");

  // Get fastmc
  TFile* fastmc = new TFile("recoil_tree.root","READ");
  TTree* t = (TTree*) gROOT->FindObject("OutputTree");
  const int nentries = t->GetEntries();
  double eta_imbalance_rms, eta_imbalance_rms_error, resolution_a, resolution_b, alpha_mb;
  int zpt;

  t->SetBranchAddress("zpt",&zpt);
  t->SetBranchAddress("eta_imbalance_rms",&eta_imbalance_rms);
  t->SetBranchAddress("eta_imbalance_rms_error",&eta_imbalance_rms_error);
  t->SetBranchAddress("resolution_a",&resolution_a);
  t->SetBranchAddress("resolution_b",&resolution_b);
  t->SetBranchAddress("alpha_mb",&alpha_mb);

  double chisquare;
  bool used[nentries];
  for (int i=0; i<nentries; i++) used[i]=false;
  double temp_resolution_a, temp_resolution_b, temp_alpha_mb;

  if(mode==1) {
  temp_resolution_a = 1.005; // Center values used for closure test
  temp_resolution_b = 0.315; // Should be a value of the grid 
  temp_alpha_mb = 1.040;     // I got really the center value
  chisquare=0.0;
  for(int j=0; j<nentries; j++){
    t->GetEntry(j);
//     if((j>5550)&&(j<5561)) {
//       cout << "Read params : " << resolution_a << " " << resolution_b << " " << alpha_mb << endl;
//       cout << "Input params: " << temp_resolution_a << " " << temp_resolution_b << " " << temp_alpha_mb << endl;
//       cout << " ------ " << endl;
//       cout << (resolution_a == temp_resolution_a) << endl;
//       cout << closeto(resolution_a,temp_resolution_a) << endl;
//       cout << (resolution_b == temp_resolution_b) << endl;
//       cout << closeto(resolution_b,temp_resolution_b) << endl;
//       cout << (alpha_mb == temp_alpha_mb) << endl;
//       cout << closeto(alpha_mb,temp_alpha_mb) << endl;
//       cout << " ------ " << endl;
//       cout << resolution_a - temp_resolution_a << endl;
//       cout << resolution_b - temp_resolution_b << endl;
//       cout << alpha_mb - temp_alpha_mb << endl;
//     }
    if(closeto(resolution_a,temp_resolution_a) && closeto(resolution_b,temp_resolution_b) && closeto(alpha_mb,temp_alpha_mb)) {
      dataVal[zpt] = eta_imbalance_rms;
      dataValErr[zpt] = eta_imbalance_rms_error;
    }
  }
  }

  if(mode==2) {
  TFile* epmcsfile = new TFile("result_epmcs.root","READ");
  epmcsfile->cd("smeared");
  cout << "EPMCS - Standard" << endl << "--------------" << endl;
  for( int i=0 ; i<10 ; i++ ) {
    dname.Form("smeared_hZcandEtaImBalance_bin_%d", i);
    TH1 *h = (TH1*) gROOT->FindObject(dname);
    dataVal[i] = h->GetRMS();
    dataValErr[i] = h->GetRMSError();
    cout << "Eta Imbalance RMS for ZpT bin " << i << " " << dataVal[i] << "+-" << dataValErr[i] << endl;

  }
  epmcsfile->Close();
  }

  for(int i=0; i<nentries; i++){
    if (!used[i]) {
      t->GetEntry(i);
      temp_resolution_a = resolution_a;
      temp_resolution_b = resolution_b;
      temp_alpha_mb = alpha_mb;
      //      cout << temp_resolution_a << " " << temp_resolution_b << " " << alpha_mb << endl; 
      chisquare=0.0;
      for(int j=0; j<nentries; j++){
	t->GetEntry(j);      
	if(closeto(resolution_a, temp_resolution_a) && closeto(resolution_b, temp_resolution_b) && closeto(alpha_mb, temp_alpha_mb)) {

	  chisquare+=((eta_imbalance_rms - dataVal[zpt])*(eta_imbalance_rms - dataVal[zpt]))/((eta_imbalance_rms_error*eta_imbalance_rms_error)+(dataValErr[zpt]*dataValErr[zpt]));
	  used[j]=true;
	  if (closeto(temp_resolution_a,0.93) && closeto(temp_resolution_b,0.24) && closeto(temp_alpha_mb,0.99)) {
	    if (zpt==0) cout << "Epmcs - template :" << endl << "-------------" << endl;
	    cout << "Eta Imbalance RMS for ZpT bin " << zpt << " " << eta_imbalance_rms << "+-" << eta_imbalance_rms_error << endl;
	  }

	}
      }
      if (closeto(temp_resolution_a,0.93) && closeto(temp_resolution_b,0.24) && closeto(temp_alpha_mb,0.99)) {
	cout << " ----------- " << endl;
	cout << "Chi2: " << chisquare << endl;
      }
      resolution << temp_resolution_a << " " << temp_resolution_b << " " << temp_alpha_mb << " " << chisquare << endl;
    }
  }
  fastmc->Close();
  
}
