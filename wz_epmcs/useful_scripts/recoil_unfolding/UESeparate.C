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

  TString data_recoilname,output_label;
  TString CCoutputname,ECoutputname;

  if( argc < 2) {
    std::cout<<" Usage : ./UESeparate <recoil-filenames> <output-label>" << std::endl;
    return 1;
  }

  std::string in_filename = std::string( argv[argc-2] );
  data_recoilname = in_filename;
  cout<<"Recoil Text File to Unfold: "<<data_recoilname<<endl;

  std::string out_filename = std::string( argv[argc-1] );
  output_label = out_filename;
  cout<<"Output Label: "<<output_label<<endl;


  double zpxgen,zpygen,zpxsmear,zpysmear, Rx_no, Ry_no, Rx_const, Ry_const, Rx_param, Ry_param, Ry_param_cone, Rx_param_cone, theSET, up1, up2, epT1, epT2,eleta1,eleta2,theLumi,tZMass,photpT1,photpT2,photDist1,photDist2;

  int dweight, type, isFSR, runno;

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

  while(rein>>zpxgen>>zpygen>>zpxsmear>>zpysmear>>Rx_no>>Ry_no>>Rx_const>>Ry_const>>Rx_param>>Ry_param>>Rx_param_cone>>Ry_param_cone>>theSET>>up1>>up2>>epT1>>epT2>>eleta1>>eleta2>>runno>>theLumi>>tZMass>>type>>dweight>>isFSR>>photpT1>>photDist1>>photpT2>>photDist2)
    {
      
      if(type==0){

	rauss1<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Rx_no<<" "<<Ry_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<<" "<<tZMass<<" "<<type<<" "<<dweight<<" "<<isFSR<<" "<<photpT1<<" "<<photDist1<<" "<<photpT2<<" "<<photDist2<<endl;
	
	rauss2<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Rx_const<<" "<<Ry_const<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<eleta1<<" "<<eleta2<<" "<<epT2<<" "<<runno<<" "<<theLumi<<" "<<tZMass<<" "<<type<<" "<<dweight<<" "<<isFSR<<" "<<photpT1<<" "<<photDist1<<" "<<photpT2<<" "<<photDist2<<endl;
	
	rauss3<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Rx_param<<" "<<Ry_param<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<<" "<<tZMass<<" "<<type<<" "<<dweight<<" "<<isFSR<<" "<<photpT1<<" "<<photDist1<<" "<<photpT2<<" "<<photDist2<<endl;
	
	rauss4<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Rx_param_cone<<" "<<Ry_param_cone<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<<" "<<tZMass<<" "<<type<<" "<<dweight<<" "<<isFSR<<" "<<photpT1<<" "<<photDist1<<" "<<photpT2<<" "<<photDist2<<endl;
	
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



