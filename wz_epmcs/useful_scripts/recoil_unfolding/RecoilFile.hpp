#ifndef recoilfile_hpp
#define recoilfile_hpp

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>  //atoi
#include <vector>
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "TVector2.h"

#include "SETefficiencySmear.hpp"
#include "PParameterReader.hpp"

using namespace std;

class RecoilFile {
  public:
    RecoilFile( TString filelist = 0 ){
      if( filelist )
        OpenFileList( filelist );
      _cc_flag = true;
      _mz_flag = true;
      number_of_entries = 0;
      total_number_of_entries = -1;
      number_processed = 0;
      _RecoilFile = 0;
      staging_host = getenv( "STAGING_HOST" );
      scp_command = getenv( "SCP_COMMAND" );
      if( scp_command == "" )
        scp_command = "scp";
      InitSetEff(); 
    };
    
    ~RecoilFile(){close_files();};
    
    vector<TString> recoil_file_list;
    TString staging_host;
    TString scp_command;
    TFile * _RecoilFile;
    TTree * _RecoilTree;

    struct recoil_struct {
      double pTZ_gen_x , pTZ_gen_y;
      double pTZ_smear_x , pTZ_smear_y;
      double recoil_x , recoil_y;
      double recoil_uncorr_x , recoil_uncorr_y;
      double recoil_constcorr_x , recoil_constcorr_y;
      double recoil_paramcorr_x , recoil_paramcorr_y;
      double recoil_paramconecorr_x , recoil_paramconecorr_y;
      double scalarET;
      double upara_e1 , upara_e2;
      double pT_e1 , pT_e2;
      double eta_e1 , eta_e2;
      int runno;
      double lumi;
      double MZ;
      int type;
      double eventweight;
      int isFSR;
      double photpT1;
      double photpT2;
      double photdist2;
    } recoil_data;

    TVector2 ZpT_gen , ZpT_smeared , Recoil;
        
    double Zphi_gen() { return ZpT_gen.Phi_0_2pi(ZpT_gen.Phi()); };
    
    double Zphi_smeared() { return ZpT_smeared.Phi_0_2pi(ZpT_smeared.Phi()); };
    
    double Psi_gen() { return ZpT_gen.DeltaPhi( Recoil ); };
    
    double Psi_smeared() { return ZpT_smeared.DeltaPhi( Recoil ); };

    bool ReadRecoilFile( fstream & inasciifile , int type = 0 );
                     
    void ConvertAsciiFile( TString asciifilename , TString rootfilename , int type = 0 );
    
    void MakeNewTree();
    
    bool OpenTree( TFile * recoilfile );
    bool OpenFileList( TString filelist );
    
    bool SelectCCevents() {
      if( !_cc_flag ) 
        return true;
      else if( recoil_data.type == 0 )
        return true;
      else
        return false;
    };
       
    bool SelectEvent() {
      if( !SelectCCevents() )
        return false;
      else if( !_mz_flag )
        return true;
      else if( recoil_data.MZ >= 85 )
        return true;
      else
        return false;
    };
    
    bool GetNextEvent();
    bool GetNextFile();
    
    void DoSelections( bool set = true ) { _cc_flag = set; _mz_flag = set; };
    
    void SetNumberOfEvents( int num ) { total_number_of_entries = num; };
    
    void InitSetEff();

  private:
    int number_of_entries;
    int total_number_of_entries;
    int current_entry;
    int current_offset;
    int current_file_idx;
    int number_processed;

    bool _cc_flag;
    bool _mz_flag;
    
    vector<string> _localFiles;
    
    TString open_file( const TString & filename );
    
    void close_files();

    // SET and Upara Efficiency Parameters ////////////////////////////////////////////////
    SETefficiencySmear *_SETeffic; 

    bool _ZSETEffCorrScaled;
    std::vector<float> _ZSETEffCorrParameters;

    std::vector<float> _ZSETEffCorrParametersCCCC;
    std::vector<float> _ZSETEffCorrParametersCCEC;
    std::vector<float> _ZSETEffCorrParametersECEC;

    //
    int _ZSETEffCorrPTEpert;
    std::vector<float> _ZSETEffCorrPTEpertBase;
    std::vector<float> _ZSETEffCorrPTEpertA;
    std::vector<float> _ZSETEffCorrPTEpertB;
    std::vector<float> _ZSETEffCorrPTEpertC;
    std::vector<float> _ZSETEffCorrPTEpertD;
    std::vector<float> _ZSETEffCorrPTEpertE;
    std::vector<float> _ZSETEffCorrPTEpertF;
    std::vector<float> _ZSETEffCorrPTEpertG;
    std::vector<float> _ZSETEffCorrPTEpertH;
    std::vector<float> _ZSETEffCorrPTEpertNorm;

    std::vector< std::vector< std::vector<float> > > _ZSETEffCorrDataRatioParameters;
    std::vector< std::vector< std::vector<float> > > _ZSETEffCorrDataRatioParameters2;
    std::vector<float> _ZSETEffCorrDataRatioPTFit;
    std::vector<float> _ZSETEffCorrDataRatioLumiFit;
    int _useHack;
    bool _useLumiBins;

    std::vector<float> _ZSETEffCorrPTEpertBase_EC;
    std::vector<float> _ZSETEffCorrPTEpertA_EC;
    std::vector<float> _ZSETEffCorrPTEpertB_EC;
    std::vector<float> _ZSETEffCorrPTEpertC_EC;
    std::vector<float> _ZSETEffCorrPTEpertD_EC;
    std::vector<float> _ZSETEffCorrPTEpertE_EC;
    std::vector<float> _ZSETEffCorrPTEpertF_EC;
    std::vector<float> _ZSETEffCorrPTEpertG_EC;
    std::vector<float> _ZSETEffCorrPTEpertH_EC;
    std::vector<float> _ZSETEffCorrPTEpertNorm_EC;

    int _UparaEffCorrOption;
    std::vector<double> _ZUparaEffParameters;
    double _Z_u0_CC, _Z_s_CC, _Z_u0_EC, _Z_s_EC;
    ///////////////////////////////////////////////////////////////////////////////////////

  public:
    double CalcSETEfficiency(float scalarEt_All, float lumi, float epT1, float epT2, float eta1, float eta2);
    double CalcUparaEfficiency(float upara1, float upara2);
};

#endif
