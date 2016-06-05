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
  
int main( int argc, char *argv[] )
{

  TString data_recoilname,output_label;
  TString CCoutputname,ECoutputname;

  if( argc < 2) {
    std::cout<<" Usage : ./CCSeparate <recoil-filenames> <output-label>" << std::endl;
    return 1;
  }

  std::string in_filename = std::string( argv[argc-2] );
  data_recoilname = in_filename;
  cout<<"Recoil Text File to Unfold: "<<data_recoilname<<endl;

  std::string out_filename = std::string( argv[argc-1] );
  output_label = out_filename;
  cout<<"Output Label: "<<output_label<<endl;


  double zpxgen,zpygen,zpxsmear,zpysmear,Exraw_no,Eyraw_no,theSET,up1,up2,epT1,epT2,eleta1,eleta2,theLumi,tZMass,photpT1,photpT2,photDist1,photDist2, dweight;
  int type, isFSR, runno;

  int totcount=0;
  int CCCCcount=0;
  int CCECcount=0;

  // FILL SMR AND GEN RECOIL OBJECTS ///////////////////////////////////////////////////////////////////////////////////

   
  fstream rein(data_recoilname,ios::in);

  CCoutputname += output_label;
  CCoutputname += "_CCCC.RAW.txt";

  ECoutputname += output_label;
  ECoutputname += "_ECCC.RAW.txt";

  fstream rauss1(CCoutputname,ios::out);
  fstream rauss2(ECoutputname,ios::out);
    
  // DB Added electron eta to ascii file, should really replace ascii file by nice tree, but I'm not there yet...
  while(rein>>zpxgen>>zpygen>>zpxsmear>>zpysmear>>Exraw_no>>Eyraw_no>>theSET>>up1>>up2>>epT1>>epT2>>eleta1>>eleta2>>runno>>theLumi>>tZMass>>type>>dweight>>isFSR>>photpT1>>photDist1>>photpT2>>photDist2)
    {

      if(type==0){

	rauss1<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<<" "<<tZMass<<" "<<type<<" "<<dweight<<" "<<isFSR<<" "<<photpT1<<" "<<photDist1<<" "<<photpT2<<" "<<photDist2<<endl;

	if(CCCCcount%10000==0) cout << CCCCcount <<" events done..."<<endl;

	CCCCcount++;
      }


      else if(type==1){
       
	rauss2<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<<" "<<tZMass<<" "<<type<<" "<<dweight<<" "<<isFSR<<" "<<photpT1<<" "<<photDist1<<" "<<photpT2<<" "<<photDist2<<endl;

	CCECcount++;
       
      }
      else{
	cout<<"WHAT THE HECK"<<endl;
      }

      totcount++;
    }
  
  rein.close();
  rauss1.close();
  rauss2.close();

  cout<<totcount<<" CCCC: "<<CCCCcount<<" CCEC: "<<CCECcount<<endl;

  return 0;
}



