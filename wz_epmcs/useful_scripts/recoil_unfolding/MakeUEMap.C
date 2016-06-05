#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TApplication.h>
#include <TVector2.h>
#include <vector>
#include <map>
#include <TRandom.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraphErrors.h>
#include <TRandom3.h>
#include <iostream>
#include <fstream>
#include <TMath.h>

#include "../../src/histograms.hpp"
#include "../../src/PMCSEMObj.hpp"
#include "../../src/EMSmear.hpp"
#include "../../src/hist_files.hpp"

using namespace std;

// Makes four files from a wmass_analysis recoil file, with each of the four possible corrections for the energy under the electron cones

int main( int argc, char *argv[] )
{
  hist_files _histos;

  double UEMAP[13][13][11];
  double UEsum[13][13][11];
  double UEcount[13][13][11];


    for(int i=0; i<13; i++){
      for(int j=0; j<13; j++){
	for(int k=0; k<11; k++){
	  UEMAP[i][j][k]=0;
	  UEsum[i][j][k]=0;
	  UEcount[i][j][k]=0;
	}
      }
    }
  
  
  TRandom3 dummy_rand;
  TRandom3 *dummy;

  EMSmear* _emsmear = new EMSmear("parameters.rc", _histos);

  int totcount=0;
  double totsum=0;

  for(int i=0; i<10000000; i++){

    if((i%10000)==0) cout<<"Event :"<<i<<endl;

    double upara_elec = 40.*(dummy_rand.Rndm() - 0.5);
    double theLumi = 5.5*dummy_rand.Rndm();
    double deteta = 2.2*(dummy_rand.Rndm()-0.5);

    PMCSEMObj fakeelectron(11,5.,deteta,1.0);
    fakeelectron.SetLumi(theLumi);
    fakeelectron.SetDetEtaDetPhi(deteta, 1.0);
    
    //    vector<PMCSEMObj> fakeelectron;
    //    fakeelectron.push_back(fakeelec);

    //    _emsmear->Set_EnergySim_ElecWindow(false);
    //    vector<PMCSEMObj> fakeelectron_smear = _emsmear->SmearEMObjs(fakeelectron, dummy);

    //    fakeelectron_smear[0].SetUPara(upara_elec);
    fakeelectron.SetUPara(upara_elec);
    _emsmear->SmearEnergyUnderElecWindow(fakeelectron);

    //    cout<<upara_elec<<" "<<theLumi<<" "<<deteta<<endl;

    int InstLumiBin = -1;
    if(theLumi<0.225) InstLumiBin = 0;
    else if(theLumi<0.45) InstLumiBin = 1;
    else if(theLumi<0.6) InstLumiBin = 2;
    else if(theLumi<0.75) InstLumiBin = 3;
    else if(theLumi<0.9) InstLumiBin = 4;
    else if(theLumi<1.075) InstLumiBin = 5;
    else if(theLumi<1.3) InstLumiBin = 6;
    else if(theLumi<1.5) InstLumiBin = 7;
    else if(theLumi<1.8) InstLumiBin = 8;
    else if(theLumi<2.) InstLumiBin = 9;
    else if(theLumi<2.5) InstLumiBin = 10;
    else if(theLumi<3.) InstLumiBin = 11;
    else InstLumiBin = 12;
    
    int UParaBin = -1;
    if(upara_elec<-15.) UParaBin = 0;
    else if(upara_elec<-10.) UParaBin = 1;
    else if(upara_elec<-5.) UParaBin = 2;
    else if(upara_elec<-3.) UParaBin = 3;
    else if(upara_elec<-1.5) UParaBin = 4;
    else if(upara_elec<-0.25) UParaBin = 5;
    else if(upara_elec<0.25) UParaBin = 6;
    else if(upara_elec<1.5) UParaBin = 7;
    else if(upara_elec<3.) UParaBin = 8;
    else if(upara_elec<5.) UParaBin = 9;
    else if(upara_elec<10.) UParaBin = 10;
    else if(upara_elec<15.) UParaBin = 11;
    else UParaBin = 12;
    
    // find the etal bin for electron 
    int etabin = (int)((deteta+1.1)/0.2);    // 11 bins for detector eta between -1.1 and 1.1 with bin size 0.2
    if(etabin < 0) etabin = 0;
    if(etabin > 10) etabin = 10;
 

    double UEcorr = _emsmear->energyDiffElec();

    //    cout<<InstLumiBin<<" "<<UParaBin<<" "<<etabin<<" "<<UEcorr<<endl;

    UEsum[UParaBin][InstLumiBin][etabin]+=UEcorr;
    UEcount[UParaBin][InstLumiBin][etabin]++;

    totcount++;
    totsum+=UEcorr;
  }

  fstream UEMfile("UEMap.txt",ios::out);  

  
  
  for(int upi=0; upi<13; upi++){
    for(int ili=0; ili<13; ili++){
      for(int ei=0; ei<11; ei++){

	// cout<<upi<<" "<<ili<<" "<<ei<<" "<<UEcount[upi][ili][ei]<<endl;

	if(UEcount[upi][ili][ei]!=0) {UEMAP[upi][ili][ei]=UEsum[upi][ili][ei]/(double)UEcount[upi][ili][ei];}
	else{ UEMAP[upi][ili][ei]=0; cout<<"WTF"<<endl;}

	UEMfile<<upi<<" "<<ili<<" "<<ei<<" "<<UEMAP[upi][ili][ei]<<endl;
      }
    }
  }
  
  double overavg =0;
  if(totcount!=0) overavg = totsum/(double)totcount;

  cout<<"DONE...Overall avg UE correction: "<<overavg<<endl;

  UEMfile.close();

}

