#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TSystem.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <fstream>

double Calc(TString swenu, TString swtaunu);

void CalcWtaubkgdfrac(){

   TString wenudirstart = "/prj_root/7055/wmass2/jenny/newdefaultjuly/wenu_backgroundsplit_newtrigfsr_jul30_clean/DEFAULT_JUL30_data_wenu_newtriggercode_modbinedge_";
  TString wtaunudirstart = "/prj_root/7055/wmass2/jenny/newdefaultjuly/wtaunu_backgroundsplit_newtrigfsr_jul30_clean/DEFAULT_AUG01_data_wtaunu_newtriggercode_modbinedge_";
  TString start2 = "";

   //   TString wenudirstart = "/prj_root/7055/wmass2/jenny/newdefaultjuly/wenu_backgroundsplit_newtrigfsr_jul30/DEFAULT_NEWFSR_JUL3014_data_wenu_newtriggercode_modbinedge_";
  //  TString wtaunudirstart = "/prj_root/7055/wmass2/jenny/newdefaultjuly/wtaunu_backgroundsplit_newtrigfsr_jul30/DEFAULT_NEWFSR_AUG0114_data_wtaunu_newtriggercode_modbinedge_";
  //  TString start2 = "may13area_default_";

  ifstream myReadFile;
  std::vector<std::string> options;
  myReadFile.open("../background_options.txt");
  char output[100];
  if (myReadFile.is_open()) {
    while (!myReadFile.eof()) {
      myReadFile >> output;
      options.push_back(output);
    }
  }

  std::vector<std::string> runs;
  runs.push_back("run3");
  runs.push_back("run4");

  for(uint i = 0; i < runs.size(); i++){
  for(uint j = 0; j < options.size(); j++){
    TString swenu = wenudirstart;
    swenu += runs[i];
    swenu += "_";
    swenu += start2;
    swenu += options[j];
    swenu += ".root";
    
    TString swtaunu = wtaunudirstart;
    swtaunu += runs[i];
    swtaunu += "_";
    swtaunu += start2;
    swtaunu += options[j];
    swtaunu += ".root";
    
    cout<<"wtaunu_bkg_fraction_"<<runs[i]<<"_"<<options[j]<<": "<<Calc(swenu, swtaunu)<<endl;;
 
    // if(runs[i] == "run3") cout<<"wtaunufile_"<<runs[i]<<"_"<<options[j]<<": "<<"wtaunubackgroundfiles/bkgd_shape_wtaunu_run3_"<<options[j]<<".root"<<endl;
    // if(runs[i] == "run4") cout<<"wtaunufile_"<<runs[i]<<"_"<<options[j]<<": "<<"wtaunubackgroundfiles/bkgd_shape_wtaunu_run4_"<<options[j]<<".root"<<endl;

    //  if(runs[i] == "run3") cout<<"zee_bkg_fraction_"<<runs[i]<<"_"<<options[j]<<": 0.00963"<<endl;;
    //  if(runs[i] == "run4") cout<<"zee_bkg_fraction_"<<runs[i]<<"_"<<options[j]<<": 0.00963"<<endl;;

    // if(runs[i] == "run3") cout<<"zeefile_"<<runs[i]<<"_"<<options[j]<<": "<<"zeebackgroundfiles/bkgd_shape_zee_run2b3_"<<options[j]<<".root"<<endl;;
    // if(runs[i] == "run4") cout<<"zeefile_"<<runs[i]<<"_"<<options[j]<<": "<<"zeebackgroundfiles/bkgd_shape_zee_run2b4_"<<options[j]<<".root"<<endl;;

      //if(runs[i] == "run3") cout<<"qcdfile_"<<runs[i]<<"_"<<options[j]<<": "<<"qcdbackgroundfiles/bkgd_qcd_run2b3_"<<options[j]<<".txt"<<endl;;
      //if(runs[i] == "run4") cout<<"qcdfile_"<<runs[i]<<"_"<<options[j]<<": "<<"qcdbackgroundfiles/bkgd_qcd_run2b4_"<<options[j]<<".txt"<<endl;;

    //  if(runs[i] == "run3") cout<<"qcdfile_"<<runs[i]<<"_"<<options[j]<<": "<<"qcdbackgroundfiles/bkgd_qcd_run2b3_all.txt"<<endl;;
    // if(runs[i] == "run4") cout<<"qcdfile_"<<runs[i]<<"_"<<options[j]<<": "<<"qcdbackgroundfiles/bkgd_qcd_run2b4_all.txt"<<endl;;

    /**
       //to make lines for .sh script to convert the wtaunu files
    TString stuff = "bkgd_shape_wtaunu";
    stuff += runs[i];
    stuff += "_";
    stuff += options[j];
    stuff += ".root";
    cout<<"python convert_pmcs_to_background_file.py  "<<swtaunu<<" "<<stuff<<endl;
    **/
  }
  }
}

double Calc(TString swenu, TString swtaunu){
  if (gSystem->AccessPathName( swenu )) return 0;
  if (gSystem->AccessPathName( swtaunu )) return 0;
  

  TFile fwenu (swenu);
  TFile fwtaunu (swtaunu);
  TH1D *hwenu = (TH1D*)fwenu.Get("default/hWcandMt_CC_50");
  TH1D *hwtaunu = (TH1D*)fwtaunu.Get("default/hWcandMt_CC_50");
  
  double nwenu = hwenu->Integral();
  double nwtaunu = hwtaunu->Integral();

  // cout<<nwenu<<"  "<<nwtaunu<<endl;

  const double nwtaunugen = 651239819;
  const double nwenugen = 1000000000;
  const double br = 0.186593;

  double frac1 = nwenu/nwenugen;
  double frac2 = nwtaunu/nwtaunugen;
  double bkgdfrac = ((frac2/frac1)*br);
  // cout<< bkgdfrac<<endl;

  fwenu.Close();
  fwtaunu.Close();
  return  bkgdfrac;
}
