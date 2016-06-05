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
    dataVal[i] = h->GetMean();
    dataValErr[i] = h->GetMeanError();
  }
  ref->Close();
  }

  // Output file
  ofstream scale("scale.txt");

  // Get fastmc
  TFile* fastmc = new TFile("recoil_tree.root","READ");
  TTree* t = (TTree*) gROOT->FindObject("OutputTree");
  const int nentries = t->GetEntries();
  double eta_imbalance_mean, eta_imbalance_mean_error, scale_a, scale_b, tau_had;
  int zpt;

  t->SetBranchAddress("zpt",&zpt);
  t->SetBranchAddress("eta_imbalance_mean",&eta_imbalance_mean);
  t->SetBranchAddress("eta_imbalance_mean_error",&eta_imbalance_mean_error);
  t->SetBranchAddress("scale_a",&scale_a);
  t->SetBranchAddress("scale_b",&scale_b);
  t->SetBranchAddress("tau_had",&tau_had);

  double chisquare;
  bool used[nentries];
  for (int i=0; i<nentries; i++) used[i]=false;
  double temp_scale_a, temp_scale_b, temp_tau_had;

  if(mode==1) {
  temp_scale_a = 1.005; // Center values used for closure test
  temp_scale_b = 0.315; // Should be a value of the grid 
  temp_tau_had = 1.040;     // I got really the center value
  chisquare=0.0;
  for(int j=0; j<nentries; j++){
    t->GetEntry(j);
//     if((j>5550)&&(j<5561)) {
//       cout << "Read params : " << scale_a << " " << scale_b << " " << tau_had << endl;
//       cout << "Input params: " << temp_scale_a << " " << temp_scale_b << " " << temp_tau_had << endl;
//       cout << " ------ " << endl;
//       cout << (scale_a == temp_scale_a) << endl;
//       cout << closeto(scale_a,temp_scale_a) << endl;
//       cout << (scale_b == temp_scale_b) << endl;
//       cout << closeto(scale_b,temp_scale_b) << endl;
//       cout << (tau_had == temp_tau_had) << endl;
//       cout << closeto(tau_had,temp_tau_had) << endl;
//       cout << " ------ " << endl;
//       cout << scale_a - temp_scale_a << endl;
//       cout << scale_b - temp_scale_b << endl;
//       cout << tau_had - temp_tau_had << endl;
//     }
    if(closeto(scale_a,temp_scale_a) && closeto(scale_b,temp_scale_b) && closeto(tau_had,temp_tau_had)) {
      dataVal[zpt] = eta_imbalance_mean;
      dataValErr[zpt] = eta_imbalance_mean_error;
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
    dataVal[i] = h->GetMean();
    dataValErr[i] = h->GetMeanError();
    cout << "Eta Imbalance mean for ZpT bin " << i << " " << dataVal[i] << "+-" << dataValErr[i] << endl;

  }
  epmcsfile->Close();
  }

  for(int i=0; i<nentries; i++){
    if (!used[i]) {
      t->GetEntry(i);
      temp_scale_a = scale_a;
      temp_scale_b = scale_b;
      temp_tau_had = tau_had;
      //      cout << temp_scale_a << " " << temp_scale_b << " " << tau_had << endl; 
      chisquare=0.0;
      for(int j=0; j<nentries; j++){
	t->GetEntry(j);      
	if(closeto(scale_a, temp_scale_a) && closeto(scale_b, temp_scale_b) && closeto(tau_had, temp_tau_had)) {

	  chisquare+=((eta_imbalance_mean - dataVal[zpt])*(eta_imbalance_mean - dataVal[zpt]))/((eta_imbalance_mean_error*eta_imbalance_mean_error)+(dataValErr[zpt]*dataValErr[zpt]));
	  used[j]=true;
	  if (closeto(temp_scale_a,0.93) && closeto(temp_scale_b,0.24) && closeto(temp_tau_had,0.99)) {
	    if (zpt==0) cout << "Epmcs - template :" << endl << "-------------" << endl;
	    cout << "Eta Imbalance mean for ZpT bin " << zpt << " " << eta_imbalance_mean << "+-" << eta_imbalance_mean_error << endl;
	  }

	}
      }
      if (closeto(temp_scale_a,0.93) && closeto(temp_scale_b,0.24) && closeto(temp_tau_had,0.99)) {
	cout << " ----------- " << endl;
	cout << "Chi2: " << chisquare << endl;
      }
      scale << temp_scale_a << " " << temp_scale_b << " " << temp_tau_had << " " << chisquare << endl;
    }
  }
  fastmc->Close();
  
}
