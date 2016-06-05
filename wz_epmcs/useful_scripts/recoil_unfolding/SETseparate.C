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
int _num_SET_bins;
int size_SETedges;

vector<double> _SET_bin_edges;
/////////////////////////////////////////////////////////////////////////////////////////


int main( int argc, char *argv[] )
{

  TString data_recoilname,output_label;
  TString CCoutputname,ECoutputname;

  if( argc < 3) {
    std::cout<<" Usage : ./SETseparate <recoil-filenames> <output-label>" << std::endl;
    return 1;
  }

  std::string in_filename = std::string( argv[argc-2] );
  data_recoilname = in_filename;
  cout<<"Recoil Text File to Unfold: "<<data_recoilname<<endl;

  std::string out_filename = std::string( argv[argc-1] );
  output_label = out_filename;
  cout<<"Output Label: "<<output_label<<endl;

   _num_SET_bins = 8;
  double SET_bin_array[7] = {15.,25.,35.,45.,65.,80.,125.};
  /*
1 _num_SET_bins = 15;
  double SET_bin_array[14] = {10.,15.,20.,25.,30.,35.,40.,45.,55.,65.,80.,100.,125.,150.};
  */
  for(int i=0; i<_num_SET_bins-1; i++){
    _SET_bin_edges.push_back(SET_bin_array[i]);
  }

  size_SETedges = _SET_bin_edges.size();

  if(_num_SET_bins!=(size_SETedges+1)) {
    cout <<"_num_delta_phi_bins should equal to _delta_phi_bin_edges.size()+1"<<endl;
  }

  double zpxgen,zpygen,zpxsmear,zpysmear,Exraw_no,Eyraw_no,theSET,up1,up2,epT1,epT2,eleta1,eleta2,theLumi,dweight;
  int type, runno;

  int *SETbincount = new int[_num_SET_bins];
  ofstream *rauss = new ofstream[_num_SET_bins];

  // FILL SMR AND GEN RECOIL OBJECTS ///////////////////////////////////////////////////////////////////////////////////
  
  fstream rein(data_recoilname,ios::in);

  for(int i=0; i<_num_SET_bins; i++){
    TString routname;
    routname+=output_label;
    routname+=".SETbin";
    routname+=i;
    routname+=".txt";

    rauss[i].open(routname,ios::out); 
    
    SETbincount[i] = 0;
  }
  
  int totcount=0;

  while(rein>>zpxgen>>zpygen>>zpxsmear>>zpysmear>>Exraw_no>>Eyraw_no>>theSET>>up1>>up2>>epT1>>epT2>>eleta1>>eleta2>>runno>>theLumi>>type>>dweight){

    if(totcount%50000==0) cout << totcount <<" events done..."<<endl;
    
    if(totcount>16000) break;

    // determine which SET bin to use
    int SETBin = -1;
    if(theSET<=_SET_bin_edges[0]) SETBin = 0;
    else if(theSET>_SET_bin_edges[size_SETedges-1]) SETBin = size_SETedges;
    else {
      for(int ii=0; ii<size_SETedges-1; ii++){
	if((theSET>_SET_bin_edges[ii]) && (theSET<=_SET_bin_edges[ii+1])) SETBin = ii+1;
      }
    }
    

    rauss[SETBin]<<zpxgen<<" "<<zpygen<<" "<<zpxsmear<<" "<<zpysmear<<" "<<Exraw_no<<" "<<Eyraw_no<<" "<<theSET<<" "<<up1<<" "<<up2<<" "<<epT1<<" "<<epT2<<" "<<eleta1<<" "<<eleta2<<" "<<runno<<" "<<theLumi<< " " <<type<<" "<<dweight<<endl;
    

    
    SETbincount[SETBin]++;
    
    totcount++;
    
  }
 
	   
  rein.close();
    
  for(int i=0; i<_num_SET_bins; i++){
    rauss[i].close();
  }
    

  cout<<"Done looping over "<<totcount<<" events. "<<endl;;
  
  for(int i=0; i< _num_SET_bins; i++){
    cout<<SETbincount[i]<<" events in bin "<<i<<endl;
  }
  cout<<" "<<endl;
  


  return 0;
}
