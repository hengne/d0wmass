#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TSystem.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <fstream>
#include <Functions.hpp>
#include <TROOT.h>
#include <TCut.h>
#include"TTree.h"
#include"TLeaf.h"
#include"TBranch.h"

//NOTE:Trees have actual lumi spectrum, So the x-axis is "normal" numbers *36. (2*36 = 72).  So lumi bins are: 0 to 72, 72 to 144, 144 to 216, 216 to 1000

//root -b -l CAFTREES_blah.root
//TH1D *h1 = _file0.Get("WCand_Hist/WCandMt_Spatial_Match_0")
//(int) h1->GetEntries()

//The input tree files can be found here /rooms/wmass/jenny/zeebackgroundfiles/

double Calc(TString cut, TString zeefile, TString option, int wenufromcafe, bool makeplots);

void CalcZeebkgdfrac(){

  //NOTE: run each run separately
   TString run = "run3";
   TString treefile = "run3_bkgd_zee_tree.root";
   TString optionfile = "backgroundoptionszee_run3.txt";

  // TString run = "run4";
  // TString treefile = "run4_bkgd_zee_tree.root";
  // TString optionfile = "backgroundoptionszee_run4.txt";

  ifstream myReadFile;
  std::vector<std::string> options;
  std::vector<std::string> cuts;
  std::vector<int> wenufromcafe;
 
  myReadFile.open(optionfile);
  char output[100];
  char cutstring[500];
  int wenufromcafestring;//[500];
  if (myReadFile.is_open()) {
    while (!myReadFile.eof()) {
      myReadFile >> output >> cutstring >> wenufromcafestring;
      options.push_back(output);
      cuts.push_back(cutstring);
      wenufromcafe.push_back(wenufromcafestring);
    }
  }

  for(uint j = 0; j < options.size(); j++){
    cout<<"zee_bkg_fraction_"<<run<<"_"<<options[j]<<": "<<Calc(cuts[j], treefile, options[j], wenufromcafe[j], false)<<endl;;
  }
}

double Calc(TString cut, TString zeefile, TString option, int wenufromcafe, bool makeplots){
  gROOT->Reset();
  
 TFile *zeefilez = new TFile(zeefile);

 TTree *et;
 zeefilez->GetObject("et",et);

//Define histograms

 Int_t nbins = 100; 
 Int_t xmin = 0;
 Int_t xmax = 400;

 TH1F *ejmass = new TH1F("ejmass","",nbins,xmin,xmax);
 TH1F* etmass = new TH1F("etmass","",nbins,xmin,xmax);
 TH1F* ejmass_final = new TH1F("ejmass_final","",nbins,xmin,xmax);
 TH1F* etmass_final = new TH1F("etmass_final","",nbins,xmin,xmax);

 // TH1D *ejmass_wenu = new TH1D("ejmass_wenu","",nbins,xmin,xmax);
 // TH1F *dr = new TH1F("dr","",100,0,0.6);


  TCut jquality("j_n90>2 && j_n90<25 && j_emf<0.5 && j_chf<0.15 && j_trks<10 && (abs(j_deta)>11 && abs(j_deta)<15) && j_hcr<6 && j_n>0 && j_n<4"); 
 // TCut jquality("j_n90>2 && j_n90<25 && j_emf<0.5 && j_chf<0.15  && (abs(j_deta)>11 && abs(j_deta)<15) && j_hcr<6 && j_n>0 && j_n<4");

 TCut jtrkdr("sqrt((j_eta-t_eta)*(j_eta-t_eta)+(j_phi-t_phi)*(j_phi-t_phi))<0.3");

 TCut wenu("wcandut<15 && wcandmt<200 && wcandmt>50  && abs(e_deta)<1.05 && e_goodspmtch==1");
 // TCut wenu("wcandmt>0 && wcandmt<200");

 TCut trackselection("t_pt>25 && abs(t_deta)>1.1 && abs(t_deta)<1.5");
 TCut vertex("abs(t_z-vtxz)<1");
 TCut charge("(t_charge*e_charge)<0");
 // TCanvas *myCanvas = new TCanvas();
 // et->Draw("ej_m>>ejmass_wenu");

 et->Draw("ej_m>>ejmass_final",wenu && "ej_m>60 && ej_m<110 && ej_deltaphi>2.5 " && jquality && "j_pt >20" && trackselection && vertex && charge && "et_m<110 && et_m>70" && cut && jtrkdr);
 et->Draw("et_m>>etmass_final",wenu && trackselection && vertex && charge && " et_m<110 && et_m>70 && et_deltaphi>2.5" && cut); 
 et->Draw("ej_m>>ejmass",wenu && "ej_m<110 && ej_m>60 &&  ej_deltaphi>2.5 " && jquality && "j_pt >20" && cut );
 et->Draw("et_m>>etmass",wenu && trackselection && vertex && charge && "et_deltaphi>2.5" && cut);

 // et->Draw("sqrt((j_eta-t_eta)*(j_eta-t_eta)+(j_phi-t_phi)*(j_phi-t_phi)) >> dr",wenu && trackselection && vertex && charge && jquality  &&"j_pt>20  && ej_m<110 && ej_m>60 && et_m<110 && et_m>70 && et_deltaphi>2.5 && abs(j_deta)>11 && abs(j_deta)<15 && ej_deltaphi>2.5" && cut );
 
 if(makeplots){
 etmass->Draw();
 ejmass->SetLineColor(2);
 ejmass->Draw("Same");

 TCanvas* plots = new TCanvas("plots", "plots");
 plots->Divide(2,2);
 plots->cd(1);
 ejmass->Draw();
 plots->cd(2);
 ejmass_final->Draw();
 plots->cd(3);
 etmass->Draw();
 plots->cd(4);
 etmass_final->Draw();

 TString filenameis = "hist_calculation_" + option +".root";

 TFile *fHistFile = new TFile(filenameis,"RECREATE");
 etmass->Write("etmass");
 etmass_final->Write("etmass_final");
 ejmass->Write();
 ejmass_final->Write();

 fHistFile->cd();
  fHistFile->Write();
  fHistFile->Close();
 }

  //cout <<" etmass = " <<etmass->GetEntries() <<endl; 
  // cout <<" ejmass = " <<ejmass->GetEntries() <<endl;
  // cout <<" etmass_final = " <<etmass_final->GetEntries() <<endl; 
  //cout <<" ejmass_final = " <<ejmass_final->GetEntries() <<endl;

 double eff = ejmass->GetEntries()/((ejmass_final->GetEntries()/etmass_final->GetEntries()) * (etmass_final->GetEntries()/etmass->GetEntries()));//num z events

  double eff_tot = eff/wenufromcafe;
  // cout <<" nb evet sample = "<<wenufromcafe<<"   efficiency = "<<eff <<"  total efficiency ="<<eff_tot<<endl; 


 zeefilez->Close();
   return  eff_tot;
}
