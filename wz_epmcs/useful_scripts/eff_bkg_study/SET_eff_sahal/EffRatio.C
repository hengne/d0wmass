#include <TApplication.h>
#include <fstream>
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"

void EffRatio(){
TH1D *heff1dpt[4][2];
 std::cout << "test" << std::endl;
TFile *mcfile = new TFile("./LumoutEff_Big.root");
TFile *datafile = new TFile("/rooms/surete/sahal/RunIIb/wz_epmcs/wz_epmcs/useful_scripts/eff_bkg_study/upara_eff_Jun/Fit2/eff_plotskeep.root");
 char name[50];
Double_t max =0;	
  for (Int_t iset=0; iset < 4; ++iset){
    sprintf(name,"eff1dpt_%1.0f_%1.0f",iset, 0);
    heff1dpt[iset][0] = (TH1D*)mcfile->Get(name);
    sprintf(name,"eff1dpt_%2.0f",iset);
    heff1dpt[iset][1] = (TH1D*)datafile->Get(name);
    heff1dpt[iset][1]->Divide(heff1dpt[iset][0]);
    for (Int_t ipt=0; ipt <7; ++ipt){
      std::cout <<  heff1dpt[iset][1]->GetBinContent(ipt+1) << ", " <<std::flush;
      if (heff1dpt[iset][1]->GetBinContent(ipt+1) > max)
	max = heff1dpt[iset][1]->GetBinContent(ipt+1);
    }
    std::cout << std::endl;

}
std::cout << std::endl;
for (Int_t iset=0; iset < 4; ++iset){
 heff1dpt[iset][1]->Scale(1./max);		
for (Int_t ipt=0; ipt <7; ++ipt){
std::cout <<  heff1dpt[iset][1]->GetBinContent(ipt+1) << ", " <<std::flush;
}
std::cout << std::endl;

}
std::cout << std::endl;


 for (Int_t iset=0; iset < 4; ++iset){

for (Int_t ipt=0; ipt <7; ++ipt){
      std::cout <<  heff1dpt[iset][1]->GetBinError(ipt+1) << ", " <<std::flush;
     
    }
 std::cout << std::endl;

  }



}
