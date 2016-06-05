#include <TApplication.h>
#include <fstream>
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"

Int_t NSET = 7;
Int_t NLUM = 6;
Int_t NPT  = 4;

TH1D *zMassdata[NSET][NPT][4][NLUM];
TH2D *heff = new TH2D("heff","Efficiency",4,0.5,4.5,7,0.5,7.5);
TH1D *heff1dpt[NSET][2][NLUM];
TH2D *heff2 = new TH2D("heff2","Efficiency 2",4,0.5,4.5,7,0.5,7.5);
TH1D *heff1dpt2[NSET][2][NLUM];


Double_t setbins[] = {0, 20., 50., 80., 110., 140., 200., 300.};
Double_t ptbins[] = {25.,35.,45.5,55.,100.};
Double_t lumibins[] = {0, 1.5, 3.0, 4.5, 6.0, 7.5, 10. };

char name[50];

TFile *datafile = new TFile("./LumStudy_BigLumi.root");

void FullMCEffLumi() {
  for (Int_t ihist=0; ihist < 4; ++ihist){
    for (Int_t iset=0; iset < NSET; ++iset){
      for (Int_t ilumi=0; ilumi < NLUM; ++ilumi){
	sprintf(name,"eff1dpt_%1.0f_%1.0f_%1.0f",iset, ihist,ilumi);
	if (ihist < 2)
	  heff1dpt[iset][ihist][ilumi] = new TH1D(name,"",NSET,ptbins[iset]);
	else
	  heff1dpt2[iset][ihist-2][ilumi] = new TH1D(name,"",NSET,ptbins[iset]);
      }
    }
  }
  for (Int_t iset=0; iset < NSET; ++iset){
    for (Int_t ihist=0; ihist < 4; ++ihist){
      for (Int_t ipt=0; ipt <NPT; ++ipt){
	for (Int_t ilumi=0; ilumi < NLUM; ++ilumi){
	  sprintf(name,"zMass_%i_%i_%i_%i",iset,ipt,ihist,ilumi);
	  zMassdata[iset][ipt][ihist][ilumi] = (TH1D*)datafile->Get(name);
	}
      }
    }
  }
  std::cout << " Gets here" << std::endl;
  for (Int_t ilumi=0; ilumi < NLUM; ++ilumi){ 
    for (Int_t iset=0; iset < NSET; ++iset){
      for (Int_t ipt=0; ipt <NPT; ++ipt){
      heff->SetBinContent(iset+1,ipt+1,zMassdata[iset][ipt][1][ilumi]->Integral() / zMassdata[iset][ipt][0][ilumi]->Integral());
      heff1dpt[iset][0][ilumi]->SetBinContent(ipt+1,zMassdata[iset][ipt][1][ilumi]->Integral());
      heff1dpt[iset][0][ilumi]->SetBinError(ipt+1,sqrt(zMassdata[iset][ipt][1][ilumi]->Integral()));
      heff1dpt[iset][1][ilumi]->SetBinContent(ipt+1,zMassdata[iset][ipt][0][ilumi]->Integral());
      heff1dpt[iset][1][ilumi]->SetBinError(ipt+1,sqrt(zMassdata[iset][ipt][0][ilumi]->Integral()));
      			  
      heff2->SetBinContent(iset+1,ipt+1,zMassdata[iset][ipt][3][ilumi]->Integral() / zMassdata[iset][ipt][2][ilumi]->Integral());
      heff1dpt2[iset][0][ilumi]->SetBinContent(ipt+1,zMassdata[iset][ipt][3][ilumi]->Integral());
      heff1dpt2[iset][0][ilumi]->SetBinError(ipt+1,sqrt(zMassdata[iset][ipt][3][ilumi]->Integral()));
      heff1dpt2[iset][1][ilumi]->SetBinContent(ipt+1,zMassdata[iset][ipt][2][ilumi]->Integral());
      heff1dpt2[iset][1][ilumi]->SetBinError(ipt+1,sqrt(zMassdata[iset][ipt][2][ilumi]->Integral()));
    }
    heff1dpt[iset][0][ilumi]->Divide(heff1dpt[iset][0][ilumi],heff1dpt[iset][1][ilumi],1,1,"B");
    heff->SetBinContent(iset+1,ipt+1,heff1dpt[iset][0][ilumi]->GetBinContent(ipt+1));
    heff->SetBinError(iset+1,ipt+1,heff1dpt[iset][0][ilumi]->GetBinError(ipt+1));
    
    heff1dpt2[iset][0][ilumi]->Divide(heff1dpt2[iset][0][ilumi],heff1dpt2[iset][1][ilumi],1,1,"B");
    heff2->SetBinContent(iset+1,ipt+1,heff1dpt2[iset][0][ilumi]->GetBinContent(ipt+1));
    heff2->SetBinError(iset+1,ipt+1,heff1dpt2[iset][0][ilumi]->GetBinError(ipt+1));
  }
  }
  std::cout << " Gets here" << std::endl;
  TFile *file2 = new TFile("LumoutEff_Big3.root","RECREATE");
  heff->Write();
  heff2->Write();
  for (Int_t ilumi=0; ilumi < NLUM; ++ilumi){ 
  for (Int_t iset=0; iset < NSET; ++iset){
    heff1dpt[iset][0][ilumi]->Write();
    heff1dpt2[iset][0][ilumi]->Write();
  }
  }
}

