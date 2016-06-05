#include <TApplication.h>
#include <fstream>
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"

TH1D *zMassdata[4][7][2];
TH2D *heff = new TH2D("heff","Efficiency",4,0.5,4.5,7,0.5,7.5);
TH1D *heff1dpt[4][2];
TH1D *efferr[4];


// Double_t setbins[] = {0,42,59,75,92,111,136,176,500};
// Double_t ptbins[][17] = {
//   {25,31,33.5,35.5,37.5,39.5,41,41.5,43,43.5,45,45.5,47,49,51.5,59.0,200.},
//   {25,31,33.5,35.5,37.5,39.5,41,41.5,43,43.5,45,45.5,47,49,51.5,59.5,200.},
//   {25,29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47,49,51.5,57.5,200.},
//   {25,29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,61,200.}, 
//   {25,29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,59.5,200.},
//   {25,29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,59,200.},
//   {25,29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,59,200.},
//   {25,29.5,33,35,37,39,41,41.5,43,43.5,45,47,49,51.5,55.5,65,200.}
// };


Double_t setbins[] = {0,59,91,134,500};
Double_t ptbins[][8] = {
  {25,35,39,41.5,43.5,45.5,49,200.},
  {25,33.5,37.5,41,43.5,47,51.5,200.},
  {25,33.5,37.5,41,43.5,47,51.5,200.},
  {25,33.5,37.5,41,43.5,47,51.5,200.}
};


char name[50];

TFile *datafile = new TFile("./LumStudy_Big.root");

void FullMCEff() {
  for (Int_t ihist=0; ihist < 2; ++ihist){
    for (Int_t iset=0; iset < 4; ++iset){
      sprintf(name,"eff1dpt_%1.0f_%1.0f",iset, ihist);
      heff1dpt[iset][ihist] = new TH1D(name,"",7,ptbins[iset]);
    }
  }
  for (Int_t iset=0; iset < 4; ++iset){
    for (Int_t ihist=0; ihist < 2; ++ihist){
      for (Int_t ipt=0; ipt <7; ++ipt){
	sprintf(name,"zMass_%i_%i_%i",iset,ipt,ihist);
	zMassdata[iset][ipt][ihist] = (TH1D*)datafile->Get(name);
      }
    }
  }
  std::cout << " Gets here" << std::endl;
  for (Int_t iset=0; iset < 4; ++iset){
    for (Int_t ipt=0; ipt <7; ++ipt){
      heff->SetBinContent(iset+1,ipt+1,zMassdata[iset][ipt][1]->Integral() / zMassdata[iset][ipt][0]->Integral());
      heff1dpt[iset][0]->SetBinContent(ipt+1,zMassdata[iset][ipt][1]->Integral());
      heff1dpt[iset][0]->SetBinError(ipt+1,sqrt(zMassdata[iset][ipt][1]->Integral()));
      heff1dpt[iset][1]->SetBinContent(ipt+1,zMassdata[iset][ipt][0]->Integral());
      heff1dpt[iset][0]->SetBinError(ipt+1,sqrt(zMassdata[iset][ipt][0]->Integral()));
      			  
 
    }
    heff1dpt[iset][0]->Divide(heff1dpt[iset][0],heff1dpt[iset][1],1,1,"B");
    heff->SetBinContent(iset+1,ipt+1,heff1dpt[iset][0]->GetBinContent(ipt+1));
    heff->SetBinError(iset+1,ipt+1,heff1dpt[iset][0]->GetBinError(ipt+1));
  }
  std::cout << " Gets here" << std::endl;
  TFile *file2 = new TFile("LumoutEff_Big.root","RECREATE");
  heff->Write();
  for (Int_t iset=0; iset < 4; ++iset){
    heff1dpt[iset][0]->Write();
  }
}
