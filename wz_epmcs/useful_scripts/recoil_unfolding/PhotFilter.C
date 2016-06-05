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

  if( argc < 3) {
    std::cout<<" Usage : ./PhotFilter <recoil-filenames> <output-label> <phot_mode>" << std::endl;
    std::cout<<" Use <phot_mode>=0   to only make a recoil file with Z Mass>85GeV (data),"<<endl
	     <<"     <phot_mode>=1   to make recoil files for different cuts on photon pT as well as Zmass>85GeV (MC)"<<endl;
    return 1;
  }

  std::string in_filename = std::string( argv[argc-3] );
  data_recoilname = in_filename;
  cout<<"Recoil Text File to Unfold: "<<data_recoilname<<endl;

  std::string out_filename = std::string( argv[argc-2] );
  output_label = out_filename;
  cout<<"Output Label: "<<output_label<<endl;

  int phot_mode = atoi(argv[argc-1]);
  if(phot_mode>1){ 
    cout<<"phot_mode must be 1 or 0!"<<endl;
    return 1;
  }
  cout<<"photmode: "<<phot_mode<<endl;

  double zpxgen,zpygen,zpxsmear,zpysmear,Exraw_no,Eyraw_no,theSET,up1,up2,epT1,epT2,eleta1,eleta2,theLumi,tZMass,photpT1,photpT2,photDist1,photDist2, dweight;
  int type, isFSR, runno;

  int totcount=0;
  int pt5count=0;
  int pt10count=0;
  int pt15count=0;
  int nophotcount=0;
  int Zcutcount=0;

  // FILL SMR AND GEN RECOIL OBJECTS ///////////////////////////////////////////////////////////////////////////////////

  
  fstream rein(data_recoilname,ios::in);

  TString routname1,routname2,routname3,routname4,routname5,routname6;

  routname1+=output_label;
  routname1+=".NoPhots.txt";

  routname2+=output_label;
  routname2+=".NoPhots.GT5.txt";

  routname3+=output_label;
  routname3+=".NoPhots.GT10.txt";

  routname4+=output_label;
  routname4+=".NoPhots.GT15.txt";

  routname5+=output_label;
  routname5+=".ZMass.GT85.txt";

  routname6+=output_label;
  routname6+=".AllPhots.txt";

  //  fstream rein("Zrecoil_toy_CCCC_0703_HYBRID.RAW.txt",ios::in);

  fstream rauss5(routname5,ios::out);
  fstream rauss6(routname6,ios::out);

  TH1D* HighestPhotPt_nocuts = new TH1D("HighestPhotPt_nocuts","HighestPhotPt_nocuts",240,0.,60.);
  TH1D* HighestPhotPt_Zmasscut = new TH1D("HighestPhotPt_Zmasscut","HighestPhotPt_Zmasscut",240,0.,60.);


  if(phot_mode==1){
    fstream rauss1(routname1,ios::out);
    fstream rauss2(routname2,ios::out);
    fstream rauss3(routname3,ios::out);
    fstream rauss4(routname4,ios::out);
  
    while(rein>>zpxgen>>zpygen>>zpxsmear>>zpysmear>>Exraw_no>>Eyraw_no>>theSET>>up1>>up2>>epT1>>epT2>>eleta1>>eleta2>>runno>>theLumi>>tZMass>>type>>dweight>>isFSR>>photpT1>>photDist1>>photpT2>>photDist2)
      {
	
	if(totcount%50000==0) cout << totcount <<" events done..."<<endl;
	
	if(isFSR) HighestPhotPt_nocuts->Fill(photpT1);
	
	if(!isFSR){
	  
	  rauss1<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<< " " <<type<<" "<<dweight<<endl;
	  
	  nophotcount++;
	}
	
	if(photpT1<5){
	  
	  rauss2<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<< " " <<type<<" "<<dweight<<endl;
	  
	  pt5count++;
	}
	
	if(photpT1<10){
	  
	  rauss3<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<< " " <<type<<" "<<dweight<<endl;
	  
	  pt10count++;
	}
	
	if(photpT1<15){
	  
	  rauss4<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<< " " <<type<<" "<<dweight<<endl;
	  
	  pt15count++;
	}
	
	if(tZMass>85.){
	  
	  rauss5<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<< " " <<type<<" "<<dweight<<endl;


	  if(isFSR) HighestPhotPt_Zmasscut->Fill(photpT1);
	  
	  Zcutcount++;
	}
	
	rauss6<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<< " " <<type<<" "<<dweight<<endl;

	totcount++;
      }
    
    rein.close();
    
    rauss1.close();
    rauss2.close();
    rauss3.close();
    rauss4.close();
    rauss5.close();
    rauss6.close();
    
    
    TFile bb("photpT.root","recreate");
    HighestPhotPt_Zmasscut->Write();
    HighestPhotPt_nocuts->Write();
    bb.Close();
    
    cout<<totcount<<" nophots: "<<nophotcount<<" no phots GT5: "<<pt5count<<" no phots GT10: "<< pt10count <<" no phots GT15: "<<pt15count << " pass Z cut: "<<Zcutcount<< endl;
  }
  else{

    while(rein>>zpxgen>>zpygen>>zpxsmear>>zpysmear>>Exraw_no>>Eyraw_no>>theSET>>up1>>up2>>epT1>>epT2>>eleta1>>eleta2>>runno>>theLumi>>tZMass>>type>>dweight>>isFSR>>photpT1>>photDist1>>photpT2>>photDist2)
      {
	
	if(totcount%50000==0) cout << totcount <<" events done..."<<endl;
	
	if(isFSR) HighestPhotPt_nocuts->Fill(photpT1);
	
	if(tZMass>85.){
	  
	  rauss5<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<< " " <<type<<" "<<dweight<<endl;
	  
	  if(isFSR) HighestPhotPt_Zmasscut->Fill(photpT1);
	  
	  Zcutcount++;
	}

	  rauss6<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<< " " <<type<<" "<<dweight<<endl;	
	  
	totcount++;
      }
    
    rein.close();
    
    rauss5.close();
    rauss6.close();
    
    
    TFile bb("photpT.root","recreate");
    HighestPhotPt_Zmasscut->Write();
    HighestPhotPt_nocuts->Write();
    bb.Close();
    
    cout<<totcount<<" nophots: "<<nophotcount<<" no phots GT5: "<<pt5count<<" no phots GT10: "<< pt10count <<" no phots GT15: "<<pt15count << " pass Z cut: "<<Zcutcount<< endl;
  }
  return 0;
}



