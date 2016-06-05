#include <TApplication.h>
#include <fstream>
#include <iostream>
#include <stdio>
#include <strstream>
#include "TRandom.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TMath.h"
#include "Fitter.hpp"


Int_t NSET = 7;
Int_t NLUM = 6;
Int_t NPT  = 4;
double xmin = 70., xmax = 110.;
const double limit1=60., limit2=70., limit3=110., limit4=120.;

TH1D *zMassdata[NSET][NPT][4][NLUM+1];
TH1D *zMassbkg[NSET][NPT][4][NLUM+1];
TH1D *zMasssig[NSET][NPT][4][NLUM+1];
Double_t eff[NSET][NPT][NLUM+1];
Double_t efferr[NSET][NPT][NLUM+1];
TH2D *heff = new TH2D("heff","Efficiency",4,0.5,4.5,7,0.5,7.5);
TH1D *heff1dpt[NSET][NLUM+1];

Double_t setbins[] = {0, 20., 50., 80., 110., 140., 200., 300.};
Double_t ptbins[] = {25.,35.,45.5,55.,100.};
Double_t lumibins[] = {0, 1.5, 3.0, 4.5, 6.0, 7.5, 10. };

char name[50];
char title[50];

void FitScalarBkgEff() {
  gROOT->LoadMacro("Fitter.cpp");
  
  for (Int_t ilumi=0; ilumi < NLUM+1; ++ilumi){
    for (Int_t iset=0; iset < NSET; ++iset){
      if (ilumi==NLUM){
	sprintf(name,"eff1dpt_%2.0f_%2.0f",iset,ilumi);
	sprintf(title,"e Pt Eff (%2.0f < SET < %2.0f) All Lumi ",setbins[iset],setbins[iset+1]);
      }
      else{
	sprintf(name,"eff1dpt_%2.0f_%2.0f",iset,ilumi);
	sprintf(title,"e Pt Eff (%2.0f < SET < %2.0f)  (%2.0f < Lumi < %2.0f) ",setbins[iset],setbins[iset+1], lumibins[ilumi], lumibins[ilumi+1]);
      }
      heff1dpt[iset][ilumi] = new TH1D(name,title,NPT,ptbins);
    }
  }
  
  //Get Data, and Bkg Histograms;
  
  TFile *datafile = new TFile("/prj_root/5007/wz2_write/sahal/wmass_analysis/DATA/zee_tree2/LumStudy_BigLumi_a.root");
  TFile *bkgfile = new TFile("/prj_root/5007/wz2_write/sahal/wmass_analysis/DATA/zee_bgtree/LumStudy_BigLumi_a.root");
    TFile *sigfileall = new TFile("/prj_root/2672/wmass2/sahal/WZEPMCS_OUTPUT/tree3/LumStudy_BigLumi_a.root");
  std::cout << "Files Loaded" << std::endl;
  
//TFile *datafile = new TFile("/prj_root/5007/wz2_write/sahal/wmass_analysis/DATA/zee_tree2/LumStudy_BigLumi.root");
//  TFile *bkgfile = new TFile("/prj_root/5007/wz2_write/sahal/wmass_analysis/DATA/zee_bgtree/LumStudy_BigLumi.root");
// TFile *sigfileall = new TFile("/prj_root/2672/wmass2/sahal/WZEPMCS_OUTPUT/trees/LumStudy_BigLumi_notrk.root");
  // TFile *sigfiletrk = new TFile("/prj_root/2672/wmass2/sahal/WZEPMCS_OUTPUT/trees/LumStudy_BigLumi_1trk.root");
  //  TFile *sigfile2trk = new TFile("/prj_root/2672/wmass2/sahal/WZEPMCS_OUTPUT/trees/LumStudy_BigLumi_2trk.root");


for (Int_t iset=0; iset < NSET; ++iset){
    for (Int_t ihist=0; ihist < 4; ++ihist){
      for (Int_t ipt=0; ipt <NPT; ++ipt){
	for (Int_t ilumi=0; ilumi < NLUM+1; ++ilumi){
	  sprintf(name,"zMass_%i_%i_%i_%i",iset,ipt,ihist,ilumi);
	  zMassdata[iset][ipt][ihist][ilumi] = (TH1D*)datafile->Get(name);
	  zMassbkg[iset][ipt][ihist][ilumi] =  (TH1D*)bkgfile->Get(name);
	  zMasssig[iset][ipt][ihist][ilumi] = (TH1D*)sigfileall->Get(name);
	  eff[iset][ipt][ilumi] = 0.;
	}
      }
    }
  }
  
  
  
  
  std::cout << " Making Clones " << std::endl;

  //make Data and Background clones tmp


  TH1D *zMassdata_tmp[NSET][NPT][4][NLUM+1];
  TH1D *zMassbkg_tmp[NSET][NPT][4][NLUM+1];
  TH1D *zMasssig_tmp[NSET][NPT][4][NLUM+1];
  TH1D *zMassdatadiff_tmp[NSET][NPT][NLUM+1];
  TH1D *zMassbkgdiff_tmp[NSET][NPT][NLUM+1];
  TH1D *zMasssigdiff_tmp[NSET][NPT][NLUM+1];
  TH1D *zMassdatadiff2_tmp[NSET][NPT][NLUM+1];
  TH1D *zMassbkgdiff2_tmp[NSET][NPT][NLUM+1];
  TH1D *zMasssigdiff2_tmp[NSET][NPT][NLUM+1];

  for (Int_t iset=0; iset < NSET; ++iset){
    for (Int_t ihist=0; ihist < 4; ++ihist){
      for (Int_t ipt=0; ipt <NPT; ++ipt){
	for (Int_t ilumi=0; ilumi < NLUM+1; ++ilumi){
	  std::cout << ilumi << "  " << ipt << "   " << ihist << "   " << iset << std::endl;
	zMassdata_tmp[iset][ipt][ihist][ilumi] = (TH1D*)(zMassdata[iset][ipt][ihist][ilumi]->Clone());
	zMassbkg_tmp[iset][ipt][ihist][ilumi] = (TH1D*)(zMassbkg[iset][ipt][ihist][ilumi]->Clone());
	zMasssig_tmp[iset][ipt][ihist][ilumi] = (TH1D*)(zMasssig[iset][ipt][ihist][ilumi]->Clone());
	if (ihist==0){
	  zMassdatadiff_tmp[iset][ipt][ilumi]=(TH1D*)(zMassdata[iset][ipt][ihist][ilumi]->Clone());
	  zMassbkgdiff_tmp[iset][ipt][ilumi]=(TH1D*)(zMassbkg[iset][ipt][ihist][ilumi]->Clone()); 
	  zMasssigdiff_tmp[iset][ipt][ilumi]=(TH1D*)(zMasssig[iset][ipt][ihist][ilumi]->Clone()); 
	}
	if (ihist==1){
	  zMassdatadiff_tmp[iset][ipt][ilumi]->Add(zMassdata[iset][ipt][ihist][ilumi],-1.);
	  zMassbkgdiff_tmp[iset][ipt][ilumi]->Add(zMassbkg[iset][ipt][ihist][ilumi],-1.);
	  zMasssigdiff_tmp[iset][ipt][ilumi]->Add(zMasssig[iset][ipt][ihist][ilumi],-1.);
	}
	if (ihist==2){
	  zMassdatadiff2_tmp[iset][ipt][ilumi]=(TH1D*)(zMassdata[iset][ipt][ihist][ilumi]->Clone());
	  zMassbkgdiff2_tmp[iset][ipt][ilumi]=(TH1D*)(zMassbkg[iset][ipt][ihist][ilumi]->Clone()); 
	  zMasssigdiff2_tmp[iset][ipt][ilumi]=(TH1D*)(zMasssig[iset][ipt][ihist][ilumi]->Clone()); 
	}
	if (ihist==3){
	  zMassdatadiff2_tmp[iset][ipt][ilumi]->Add(zMassdata[iset][ipt][ihist][ilumi],-1.);
	  zMassbkgdiff2_tmp[iset][ipt][ilumi]->Add(zMassbkg[iset][ipt][ihist][ilumi],-1.);
	  zMasssigdiff2_tmp[iset][ipt][ilumi]->Add(zMasssig[iset][ipt][ihist][ilumi],-1.);
	}
	}
      }
    }
  }
  
  
  //Get Signal histograms from fast mc
  
  double data_entry_before_all[NSET][NPT][NLUM+1], mc_entry_before_all[NSET][NPT][NLUM+1], bkg_entry_before_all[NSET][NPT][NLUM+1], mc_error_before_all[NSET][NPT][NLUM+1];
  double data_entry_after_all[NSET][NPT][NLUM+1], mc_entry_after_all[NSET][NPT][NLUM+1], bkg_entry_after_all[NSET][NPT][NLUM+1], mc_error_after_all[NSET][NPT][NLUM+1];
  double chisq1_all[NSET][NPT][NLUM+1], chisq2_all[NSET][NPT][NLUM+1];
 

  TCanvas *ctemp=new TCanvas;
  int npad = 1;
  ctemp->Divide(1,1); 
  ctemp->cd(npad); 

  std::cout << " Fitting " << std::endl;
  Fitter fitter;
  for (int ilumi=0; ilumi < NLUM+1; ++ilumi){
    for (int iset=0; iset < NSET; ++iset){
      for(int ipt=0; ipt<NPT; ipt++){   
	
      double eff_tmp_all=1, efferr_tmp_all=0.;
      if(zMassdatadiff_tmp[iset][ipt][ilumi]->Integral()>0. && zMasssigdiff_tmp[iset][ipt][ilumi]->Integral()>0. && zMassbkgdiff_tmp[iset][ipt][ilumi]->Integral()>0.) {
	fitter.Update(zMassdatadiff_tmp[iset][ipt][ilumi],zMasssigdiff_tmp[iset][ipt][ilumi] ,zMassbkgdiff_tmp[iset][ipt][ilumi], xmin, xmax);
	fitter.FitMass();
	fitter.Compare(ctemp);   
	fitter.GetDataSignalBkg(data_entry_before_all[iset][ipt][ilumi], mc_entry_before_all[iset][ipt][ilumi], bkg_entry_before_all[iset][ipt][ilumi], mc_error_before_all[iset][ipt][ilumi], chisq1_all[iset][ipt][ilumi]);
      }
      else {
      std:cout << "no bkg " << ilumi << " " << iset << " " << ipt <<  "  " << zMassdatadiff_tmp[iset][ipt][ilumi]->Integral() << "  " <<  zMasssigdiff_tmp[iset][ipt][ilumi]->Integral() << "   " << zMassbkgdiff_tmp[iset][ipt][ilumi]->Integral() << std::endl;
	
      }
      
      if(zMassdata_tmp[iset][ipt][1][ilumi]->Integral()>0. && zMasssig_tmp[iset][ipt][1][ilumi]->Integral()>0. && zMassbkg_tmp[iset][ipt][1][ilumi]->Integral()>0.) {
	fitter.Update(zMassdata_tmp[iset][ipt][1][ilumi],zMasssig_tmp[iset][ipt][1][ilumi] ,zMassbkgdiff_tmp[iset][ipt][ilumi] , xmin, xmax);
	fitter.FitMass();
	fitter.Compare(ctemp);   
	fitter.GetDataSignalBkg(data_entry_after_all[iset][ipt][ilumi], mc_entry_after_all[iset][ipt][ilumi], bkg_entry_after_all[iset][ipt][ilumi], mc_error_after_all[iset][ipt][ilumi], chisq2_all[iset][ipt][ilumi]);
      }
      
      int bin_low=zMasssig_tmp[iset][ipt][0][ilumi]->FindBin(limit2);
      int bin_high=zMasssig_tmp[iset][ipt][0][ilumi]->FindBin(limit3);
      
      if(mc_entry_before_all[iset][ipt][ilumi]>0.) { /// &&  mc_entry_after_all[iset][ipt][ilumi]>1.) {       
	eff_tmp_all= mc_entry_after_all[iset][ipt][ilumi]/(mc_entry_before_all[iset][ipt][ilumi]+ mc_entry_after_all[iset][ipt][ilumi]);	
	efferr_tmp_all=sqrt(mc_entry_before_all[iset][ipt][ilumi]*mc_entry_before_all[iset][ipt][ilumi]*mc_error_after_all[iset][ipt][ilumi]*mc_error_after_all[iset][ipt][ilumi]+ mc_entry_after_all[iset][ipt][ilumi]*mc_entry_after_all[iset][ipt][ilumi]*mc_error_before_all[iset][ipt][ilumi]*mc_error_before_all[iset][ipt][ilumi])/(mc_entry_before_all[iset][ipt][ilumi]+mc_entry_after_all[iset][ipt][ilumi])/(mc_entry_before_all[iset][ipt][ilumi]+mc_entry_after_all[iset][ipt][ilumi]);
	
	cout<<"efferr_tmp_all="<<efferr_tmp_all<<endl;
      }
      else {
	eff_tmp_all=0.;
	efferr_tmp_all=0.;
      }
      
      if(eff_tmp_all>1){
	eff_tmp_all=1.;
	efferr_tmp_all=1.;
      }
      eff[iset][ipt][ilumi] = eff_tmp_all;
      efferr[iset][ipt][ilumi] = efferr_tmp_all;
      heff->Fill(iset+1,ipt+1,eff_tmp_all);
      heff->SetBinError(iset+1,ipt+1,efferr_tmp_all);
      heff1dpt[iset][ilumi]->SetBinContent(ipt+1,eff_tmp_all);
      heff1dpt[iset][ilumi]->SetBinError(ipt+1,efferr_tmp_all);
      }
    }
  }


/////end all-events


  TFile *file1 = new TFile("eff_plots.root", "recreate");
  TString name_plot;
  name_plot+="eff_data";

  
  ////Draw plots
  TCanvas *canv3= new TCanvas;
  canv3->Divide(1,1);
  canv3->cd(1);
  heff->Draw();
  heff->Write("eff_data_all");
  //   //  Eff2->Draw("same");
  for (int iset=0; iset < NSET; ++iset){
    for (int ilumi=0; ilumi < NLUM+1; ++ilumi){
      heff1dpt[iset][ilumi]->Write();
      for(int ipt=0; ipt<NPT; ipt++){
	std::cout << "eff[iset][ipt][ilumi] " << iset << "  " << ipt << "  " << ilumi << "   " << eff[iset][ipt][ilumi] << std::endl;
      }
    }
  }
  

}


