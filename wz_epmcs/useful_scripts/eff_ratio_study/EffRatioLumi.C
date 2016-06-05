#include <TApplication.h>
#include <fstream>
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TCanvas.h"

Int_t NSET = 7;
Int_t NLUM = 6;
Int_t NPT  = 4;


gStyle->SetOptStat("0000000");
gStyle->SetOptFit("0000000");
void EffRatioLumi(){
  TH1D *heff1dpt[NSET][3][NLUM+1];
  std::cout << "test" << std::endl;
  TFile *mcfile = new TFile("/prj_root/5007/wz2_write/sahal/wmass_analysis/Full_MC/zee_tree2/LumoutEff_Big3_a.root");
  TFile *datafile = new TFile("/rooms/surete/sahal/RunIIb/wz_epmcs/wz_epmcs/useful_scripts/eff_bkg_study/SET_eff_sahal/Lumi2/eff_plots.root");
  TFile *datafile2 = new TFile("/rooms/surete/sahal/RunIIb/wz_epmcs/wz_epmcs/useful_scripts/eff_bkg_study/SET_eff_sahal/Lumi2/eff_plots2.root");
  char name[50];
  
Double_t setbins[] = {0, 20., 50., 80., 110., 140., 200., 300.};
Double_t ptbins[] = {25.,35.,45.5,55.,100.};
Double_t lumibins[] = {0, 1.5, 3.0, 4.5, 6.0, 7.5, 10. };

  TH3D *heffsetlumipt = new TH3D("heffsetlumipt","heffsetlumipt",NSET,setbins,NLUM,lumibins,NPT,ptbins);
  TH2D *heffsetlumi = new TH2D("heffsetlumi","heffsetlumi",NSET,setbins,NLUM,lumibins);
  TH2D *heffsetpt = new TH2D("heffsetpt","hefflumiset",NSET,setbins,NPT,ptbins);
  TH2D *hefflumipt = new TH2D("hefflumipt","hefflumipt",NLUM,lumibins,NPT,ptbins);

  
  Double_t max =0;	
  for (Int_t iset=0; iset < NSET; ++iset){
    for (Int_t ilumi=0; ilumi < NLUM+1; ++ilumi){
      sprintf(name,"eff1dpt_%1.0f_%1.0f_%1.0f",iset, 0,ilumi);
      heff1dpt[iset][0][ilumi] = (TH1D*)mcfile->Get(name);
      sprintf(name,"eff1dpt_%2.0f_%2.0f",iset,ilumi);
      heff1dpt[iset][1][ilumi] = (TH1D*)datafile->Get(name);
      std::cout << name << std::endl;
      heff1dpt[iset][2][ilumi] = (TH1D*)(datafile->Get(name)->Clone());
      std::cout << " before " << std::endl;	
      heff1dpt[iset][1][ilumi]->Divide(heff1dpt[iset][0][ilumi]);
      for (Int_t ipt=0; ipt <NPT; ++ipt){
	std::cout <<  heff1dpt[iset][1][ilumi]->GetBinContent(ipt+1) << ", " <<std::flush;
	if (heff1dpt[iset][1][ilumi]->GetBinContent(ipt+1) > max)
	  max = heff1dpt[iset][1][ilumi]->GetBinContent(ipt+1);
	if (heff1dpt[iset][1][ilumi]->GetBinContent(ipt+1) < 1e-03){
         heff1dpt[iset][1][ilumi]->SetBinContent(ipt+1,1.) ;
      }
      }
      std::cout << std::endl;

    }
  }
  std::cout << std::endl;
  char outname[100];
  for (Int_t ilumi=0; ilumi < NLUM+1; ++ilumi){
    for (Int_t iset=0; iset < NSET; ++iset){
      heff1dpt[iset][1][ilumi]->Scale(1./max);
      if (ilumi==NLUM){
	sprintf(outname,"ZSETEffCorrDataRatioParametersBin_%1d: ",iset);
      }
      else{
	sprintf(outname,"ZSETEffCorrDataRatioParametersBin%1d_%1d: ", ilumi,iset);
      }
      std::cout << outname << std::flush ;
      for (Int_t ipt=0; ipt <7; ++ipt){
	std::cout <<  heff1dpt[iset][1][ilumi]->GetBinContent(ipt+1) <<std::flush;
	if (ipt < 6)
	  std::cout << ", " <<std::flush;
      }
      std::cout << std::endl;
      
    }
  }
  std::cout << std::endl;

  for (Int_t ilumi=0; ilumi < NLUM+1; ++ilumi){
    for (Int_t iset=0; iset < NSET; ++iset){      
      for (Int_t ipt=0; ipt <NPT; ++ipt){
	heffsetlumipt->SetBinContent(iset+1,ilumi+1,ipt+1,heff1dpt[iset][1][ilumi]->GetBinContent(ipt+1)) ;
	heffsetlumipt->SetBinError(iset+1,ilumi+1,ipt+1,heff1dpt[iset][1][ilumi]->GetBinError(ipt+1)) ;

	heffsetlumi->SetBinContent(iset+1,ilumi+1,ipt+1,heff1dpt[iset][1][ilumi]->GetBinContent(ipt+1));
	heffsetlumi->SetBinError(iset+1,ilumi+1,ipt+1,heff1dpt[iset][1][ilumi]->GetBinError(ipt+1));

	heffsetpt;
	heffsetpt;

	hefflumipt;
	hefflumipt;
	
	std::cout <<  heff1dpt[iset][1][ilumi]->GetBinError(ipt+1) << std::flush;
	if (ipt < NPT-1)
	  std::cout << ", " <<std::flush;
      }
      std::cout << std::endl;
      
    }

  }

  // for (Int_t ilumi=0; ilumi < 5; ++ilumi){
  //   for (Int_t iset=0; iset < 4; ++iset){
  //     heff1dpt[iset][1][ilumi]->Fit("pol1","","",34.,60.);
  //   }
  // }
 
  for (Int_t iset=0; iset < NSET; ++iset){
    TCanvas *c1 = new TCanvas();
    c1->Divide(1,5);
    for (Int_t ilumi=0; ilumi < NLUM+1; ++ilumi){
      c1->cd(ilumi+1);
      heff1dpt[iset][0][ilumi]->SetTitle(heff1dpt[iset][1][ilumi]->GetTitle() );
      heff1dpt[iset][0][ilumi]->GetYaxis()->SetRangeUser(0.6,max+0.1);
      heff1dpt[iset][0][ilumi]->GetYaxis()->SetTitle("Efficiency");
      heff1dpt[iset][0][ilumi]->GetXaxis()->SetTitle("e Pt (GeV)");
      heff1dpt[iset][0][ilumi]->Draw();
      heff1dpt[iset][1][ilumi]->SetLineColor(3);
      heff1dpt[iset][1][ilumi]->Draw("SAME");
      heff1dpt[iset][2][ilumi]->SetLineColor(2);
      heff1dpt[iset][2][ilumi]->Draw("SAME");
    }
  }
}
