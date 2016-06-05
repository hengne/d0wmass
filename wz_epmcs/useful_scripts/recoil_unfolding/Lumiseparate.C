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
  

// Binning Variables /////////////////////////////////////////////////////////////////////////
int _num_Lumi_bins;
int size_Lumiedges;

vector<double> _Lumi_bin_edges;
/////////////////////////////////////////////////////////////////////////////////////////


int main( int argc, char *argv[] )
{

  TString data_recoilname,output_label;
  TString CCoutputname,ECoutputname;

  if( argc < 3) {
    std::cout<<" Usage : ./Lumiseparate <recoil-filenames> <output-label>" << std::endl;
    return 1;
  }

  std::string in_filename = std::string( argv[argc-2] );
  data_recoilname = in_filename;
  cout<<"Recoil Text File to Unfold: "<<data_recoilname<<endl;

  std::string out_filename = std::string( argv[argc-1] );
  output_label = out_filename;
  cout<<"Output Label: "<<output_label<<endl;

   _num_Lumi_bins = 4;
  double Lumi_bin_array[3] = {0.5, 1.0, 2.0};

  for(int i=0; i<_num_Lumi_bins-1; i++){
    _Lumi_bin_edges.push_back(Lumi_bin_array[i]);
  }

  size_Lumiedges = _Lumi_bin_edges.size();

  if(_num_Lumi_bins!=(size_Lumiedges+1)) {
    cout <<"_num_delta_phi_bins should equal to _delta_phi_bin_edges.size()+1"<<endl;
  }

  double zpxgen,zpygen,zpxsmear,zpysmear,Exraw_no,Eyraw_no,theSET,up1,up2,epT1,epT2,eleta1,eleta2,theLumi,dweight;
  int type, runno;

  int *Lumibincount = new int[_num_Lumi_bins];
  ofstream *rauss = new ofstream[_num_Lumi_bins];

  // FILL SMR AND GEN RECOIL OBJECTS ///////////////////////////////////////////////////////////////////////////////////
  
  fstream rein(data_recoilname,ios::in);

  for(int i=0; i<_num_Lumi_bins; i++){
    TString routname;
    routname+=output_label;
    routname+=".Lumibin";
    routname+=i;
    routname+=".txt";

    rauss[i].open(routname,ios::out); 
    
    Lumibincount[i] = 0;
  }
  
  int totcount=0;

  TH1D* Lumihist = new TH1D("lumi","lumi",20,0.,6.);

  while(rein>>zpxgen>>zpygen>>zpxsmear>>zpysmear>>Exraw_no>>Eyraw_no>>theSET>>up1>>up2>>epT1>>epT2>>eleta1>>eleta2>>runno>>theLumi>>type>>dweight){

    if(totcount%50000==0) cout << totcount <<" events done..."<<endl;
    
    //    if(totcount>16000) break;

    // determine which Lumi bin to use
    int LumiBin = -1;
    if(theLumi<=_Lumi_bin_edges[0]) LumiBin = 0;
    else if(theLumi>_Lumi_bin_edges[size_Lumiedges-1]) LumiBin = size_Lumiedges;
    else {
      for(int ii=0; ii<size_Lumiedges-1; ii++){
	if((theLumi>_Lumi_bin_edges[ii]) && (theLumi<=_Lumi_bin_edges[ii+1])) LumiBin = ii+1;
      }
    }
    

    Lumihist->Fill(theLumi);

    rauss[LumiBin]<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<< " " <<type<<" "<<dweight<<endl;
    

    
    Lumibincount[LumiBin]++;
    
    totcount++;
    
  }
 
	   
  rein.close();
    
  for(int i=0; i<_num_Lumi_bins; i++){
    rauss[i].close();
  }
    

  cout<<"Done looping over "<<totcount<<" events. "<<endl;;
  
  for(int i=0; i< _num_Lumi_bins; i++){
    cout<<Lumibincount[i]<<" events in bin "<<i<<endl;
  }
  cout<<" "<<endl;
  
  TFile lum("lumidist.root","recreate");
  Lumihist->Write();

  return 0;
}
