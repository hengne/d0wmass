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
#include <TMath.h>

#include <iostream>
#include <fstream>

using namespace std;
  
// Makes four files from a wmass_analysis recoil file, with each of the four possible corrections for the energy under the electron cones

int main( int argc, char *argv[] )
{

  TString data_recoilname,output_label,UEmap_label,eleakmap_label;
  TString CCoutputname,ECoutputname;

  if( argc < 4) {
    //    std::cout<<" Usage : ./UESeparate <recoil-filenames> <output-label> <UEMapFile> <ElecLeakageMapFile> <0 for Z recoil/1 for W recoil>" << std::endl;
    std::cout<<" Usage : ./UESeparate <recoil-filenames> <output-label> <UEMapFile> <0 for Z recoil/1 for W recoil>" << std::endl;
    return 1;
  }

  std::string in_filename = std::string( argv[argc-4] );
  data_recoilname = in_filename;
  cout<<"Recoil Text File to Unfold: "<<data_recoilname<<endl;

  std::string out_filename = std::string( argv[argc-3] );
  output_label = out_filename;
  cout<<"Output Label: "<<output_label<<endl;

  std::string UEMAPfile_name = std::string( argv[argc-2] );
  UEmap_label =UEMAPfile_name;
  cout<<"UEMapFile : "<<UEmap_label<<endl;
  /*
  std::string EleakMAPfile_name = std::string( argv[argc-2] );
  eleakmap_label = EleakMAPfile_name;
  cout<<"ElecLeakageMapFile: "<<eleakmap_label<<endl;
  */
  int file_type = atoi(argv[argc-1]);
  if( (file_type>1) || (file_type<0) ){ 
    cout<<"file_type must be 1 or 0!"<<endl;
    return 1;
  }

  // Read in UE Library
  
  double UEMAP[13][13][11];
  
  int upb,lb,eb; double UEcorr;
  fstream UEMfile(UEmap_label,ios::in);
  while(!UEMfile.eof()) {
    UEMfile>>upb>>lb>>eb>>UEcorr;
    if(UEMfile.eof()) break;

    UEMAP[upb][lb][eb]=UEcorr;
  }

  // Read in Electron Leakage Library

  /*
  double elecLeakMAP[14];
  
  int leakbin; double eleak;
  fstream eLfile(eleakmap_label,ios::in);
  while(!eLfile.eof()) {
    eLfile>>leakbin>>eleak;
    if(eLfile.eof()) break;

    elecLeakMAP[leakbin]=eleak;
  }
  */

  double zpxgen,zpygen,zpxsmear,zpysmear,Rx_no,Ry_no,Rx_const,Ry_const,Rx_param,Ry_param,Ry_param_cone,Rx_param_cone,theSET,up1,up2,epT1,epT2,theLumi,tZMass,photpT1,photpT2,photDist1,photDist2,elpT1,eEta1,ePhi1,edetEta1,elpT2,eEta2,ePhi2,edetEta2,HMx7_1,HMx8_1,emfrac1,iso1,trk1,HMx7_2,HMx8_2,emfrac2,iso2,trk2;
  
  int dweight,type,isFSR,runno;
  
  int totcount=0;
  int CCCCcount=0;
  
  // FILL SMR AND GEN RECOIL OBJECTS ///////////////////////////////////////////////////////////////////////////////////
  
  fstream rein(data_recoilname,ios::in);
  
  TString routname1,routname2,routname3,routname4;
  
  routname1+=output_label;
  routname1+="_CCCC_nocorr.txt";

  routname2+=output_label;
  routname2+="_CCCC_const.txt";
  
  routname3+=output_label;
  routname3+="_CCCC_param.txt";
  
  routname4+=output_label;
  routname4+="_CCCC_paramcone.txt";
  
  fstream rauss1(routname1,ios::out);
  fstream rauss2(routname2,ios::out);
  fstream rauss3(routname3,ios::out);
  fstream rauss4(routname4,ios::out);
  
  
  while(!rein.eof()) {
    
    if(file_type==0){
      rein>>zpxgen>>zpygen>>zpxsmear>>zpysmear>>Rx_no>>Ry_no>>Rx_const>>Ry_const>>Rx_param>>Ry_param>>Rx_param_cone>>Ry_param_cone>>theSET>>up1>>up2>>epT1>>epT2>>runno>>theLumi>>tZMass>>type>>dweight>>isFSR>>photpT1>>photDist1>>photpT2>>photDist2>>elpT1>>eEta1>>ePhi1>>edetEta1>>elpT2>>eEta2>>ePhi2>>edetEta2>>HMx7_1>>HMx8_1>>emfrac1>>iso1>>trk1>>HMx7_2>>HMx8_2>>emfrac2>>iso2>>trk2;
    }
    else if(file_type == 1){
      rein>>zpxgen>>zpygen>>zpxsmear>>zpysmear>>Rx_no>>Ry_no>>Rx_const>>Ry_const>>Rx_param>>Ry_param>>Rx_param_cone>>Ry_param_cone>>theSET>>up1>>up2>>epT1>>epT2>>runno>>theLumi>>tZMass>>type>>dweight>>isFSR>>photpT1>>photDist1>>photpT2>>photDist2>>elpT1>>eEta1>>ePhi1>>edetEta1>>HMx7_1>>HMx8_1>>emfrac1>>iso1>>trk1;
      
      HMx7_2=0; HMx8_2=0; emfrac2=0; iso2=0; trk2=0; elpT2=0; ePhi2=0; eEta2=0; edetEta2=0;
    }
    
    if(rein.eof()) break;
    
    if(totcount%10000==0) cout<<totcount<<" events.."<<endl;


    if(type==0){
      
      
      //identify the u-parallel, lumi bin
      
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
      
      double elx1=1;
      double ely1=1;
      double elx2=1;
      double ely2=1;
      TVector2 electron1(elx1,ely1);
      TVector2 electron2(elx2,ely2);
      TVector2 recoil_vector_uncorr(Rx_no, Ry_no);
      TVector2 elec_vec[2];
      
      elec_vec[0] = electron1;
      elec_vec[1] = electron2;
      
      // calculate uparallel for both electrons
      double upara_elec[2], uparaCorr_elec[2];
      double deteta[2], energyLeak_elec[2];
      double peta[2];
      
      upara_elec[0] = up1;
      upara_elec[1] = up2;
      
      deteta[0] = edetEta1;
      deteta[1] = edetEta2;

      peta[0] = eEta1;
      peta[1] = eEta2;
      
      for(int iem=0; iem<2; iem++) {
	
	// find the uparallel bin for electron 1
	int UParaBin = -1;
	if(upara_elec[iem]<-15.) UParaBin = 0;
	else if(upara_elec[iem]<-10.) UParaBin = 1;
	else if(upara_elec[iem]<-5.) UParaBin = 2;
	else if(upara_elec[iem]<-3.) UParaBin = 3;
	else if(upara_elec[iem]<-1.5) UParaBin = 4;
	else if(upara_elec[iem]<-0.25) UParaBin = 5;
	else if(upara_elec[iem]<0.25) UParaBin = 6;
	else if(upara_elec[iem]<1.5) UParaBin = 7;
	else if(upara_elec[iem]<3.) UParaBin = 8;
	else if(upara_elec[iem]<5.) UParaBin = 9;
	else if(upara_elec[iem]<10.) UParaBin = 10;
	else if(upara_elec[iem]<15.) UParaBin = 11;
	else UParaBin = 12;
	
	// find the etal bin for electron 
	int etabin = (int)((deteta[iem]+1.1)/0.2);    // 11 bins for detector eta between -1.1 and 1.1 with bin size 0.2
	if(etabin < 0) etabin = 0;
	if(etabin > 10) etabin = 10;

	int LeakBin=(int)(peta[iem]/0.2)+7;
	if (LeakBin<0) LeakBin=0;
	if (LeakBin>13) LeakBin=13;

	uparaCorr_elec[iem] = UEMAP[UParaBin][InstLumiBin][etabin];
	//	energyLeak_elec[iem] = elecLeakMAP[LeakBin];
	energyLeak_elec[iem] = .08;

      } // loop over two electrons
      
      TVector2 recoil_vector_const_corr;
      TVector2 recoil_vector_param_corr;
      TVector2 recoil_vector_pcone_corr;
      
      double theta1 = 2.0*atan(exp(-eEta1));

      if(file_type==0){
	double theta2 = 2.0*atan(exp(-eEta2));
	// add back uparallel corrections from the two electrons
	recoil_vector_const_corr = recoil_vector_uncorr + 0.13*elec_vec[0].Unit() + 0.13*elec_vec[1].Unit();
	recoil_vector_param_corr = recoil_vector_uncorr + sin(theta1)*uparaCorr_elec[0]*elec_vec[0].Unit() + sin(theta2)*uparaCorr_elec[1]*elec_vec[1].Unit();
	recoil_vector_pcone_corr = recoil_vector_uncorr + sin(theta1)*(uparaCorr_elec[0]-energyLeak_elec[0])*elec_vec[0].Unit() 
	  + sin(theta2)*(uparaCorr_elec[1]-energyLeak_elec[1])*elec_vec[1].Unit();
      }
      else if(file_type==1){
	// add back uparallel corrections from the two electrons
	recoil_vector_const_corr = recoil_vector_uncorr + 0.13*elec_vec[0].Unit();
	recoil_vector_param_corr = recoil_vector_uncorr + sin(theta1)*uparaCorr_elec[0]*elec_vec[0].Unit();
	recoil_vector_pcone_corr = recoil_vector_uncorr + sin(theta1)*(uparaCorr_elec[0]-energyLeak_elec[0])*elec_vec[0].Unit();
      }
      
      double RecX_no = Rx_no;
      double RecY_no = Ry_no;
      double RecX_const = recoil_vector_const_corr.X();
      double RecY_const = recoil_vector_const_corr.Y();
      double RecX_param = recoil_vector_param_corr.X();
      double RecY_param = recoil_vector_param_corr.Y();
      double RecX_pcone = recoil_vector_pcone_corr.X();
      double RecY_pcone = recoil_vector_pcone_corr.Y();
      
      rauss1<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<RecX_no<<" "<<RecY_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<runno<<" "<<theLumi<<" "<<tZMass<<" "<<type<<" "<<dweight<<" "<<isFSR<<" "<<photpT1<<" "<<photDist1<<" "<<photpT2<<" "<<photDist2<<endl;
      
      rauss2<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<RecX_const<<" "<<RecY_const<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<runno<<" "<<theLumi<<" "<<tZMass<<" "<<type<<" "<<dweight<<" "<<isFSR<<" "<<photpT1<<" "<<photDist1<<" "<<photpT2<<" "<<photDist2<<endl;
      
      rauss3<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<RecX_param<<" "<<RecY_param<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<runno<<" "<<theLumi<<" "<<tZMass<<" "<<type<<" "<<dweight<<" "<<isFSR<<" "<<photpT1<<" "<<photDist1<<" "<<photpT2<<" "<<photDist2<<endl;
      
      rauss4<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<RecX_pcone<<" "<<RecY_pcone<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<runno<<" "<<theLumi<<" "<<tZMass<<" "<<type<<" "<<dweight<<" "<<isFSR<<" "<<photpT1<<" "<<photDist1<<" "<<photpT2<<" "<<photDist2<<endl;
      
      CCCCcount++;
      
    }
    
    totcount++;
  }
  
  rein.close();
  rauss1.close();
  rauss2.close();
  rauss3.close();
  rauss4.close();
  
  cout<<totcount<<" CCCC: "<< CCCCcount<<endl;
  
  return 0;
  
}


