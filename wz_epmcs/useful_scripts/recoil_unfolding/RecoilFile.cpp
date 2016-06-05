#include "RecoilFile.hpp"

using namespace std;

void RecoilFile::MakeNewTree()
{
  _RecoilTree = new TTree( "RecoilTree" , "RecoilTree" );
  string recoil_block = "pTZ_gen_x/D:pTZ_gen_y/D:pTZ_smear_x/D:pTZ_smear_y/D:recoil_x/D:recoil_y/D:recoil_uncorr_x/D:recoil_uncorr_y/D:recoil_constcorr_x/D:recoil_constcorr_y/D:recoil_paramcorr_x/D:recoil_paramcorr_y/D:recoil_paramconecorr_x/D:recoil_paramconecorr_y/D:scalarET/D:upara_e1/D:upara_e2/D:pT_e1/D:pT_e2/D:eta_e1/D:eta_e2/D:runno/I:lumi/D:MZ/D:type/I:eventweight/D:isFSR/I:photpT1/D:photpT2/D";
  _RecoilTree->Branch( "RecoilData" , &recoil_data.pTZ_gen_x , recoil_block.c_str() );
}

bool RecoilFile::OpenTree( TFile * recoilfile )
{
  _RecoilFile = recoilfile;
  _RecoilTree = (TTree*) _RecoilFile->Get( "RecoilTree" );
  if( !_RecoilTree ) return false;
  number_of_entries = _RecoilTree->GetEntries();
  if( number_of_entries == 0 ) return false;
  current_entry = -1;
  current_offset = 0;
  _RecoilTree->SetBranchAddress( "RecoilData" , &recoil_data.pTZ_gen_x );
  return true;
}

bool RecoilFile::OpenFileList( TString filelist )
{
  current_entry = -1;
  current_offset = 0;
  current_file_idx = -1;
  fstream inpfile( filelist.Data() );
  TString s;
  while( inpfile >> s )
  {
    recoil_file_list.push_back( TString( s ) );
    
/*    TFile * temp_file = new TFile( s , "read" );
    if( temp_file )
    {
      recoil_file_list.push_back( TString( s ) );
      temp_file->Close();
    }
    else if( staging_host != "" )
    {
      recoil_file_list.push_back( TString( s ) );
    }*/
  }
  return GetNextFile();
}

bool RecoilFile::ReadRecoilFile( fstream & inasciifile , int type )
{
  string s;

  if(getline(inasciifile,s))
  {
    istringstream line(s);
    double ignore;
    line >> recoil_data.pTZ_gen_x >> recoil_data.pTZ_gen_y
         >> recoil_data.pTZ_smear_x >> recoil_data.pTZ_smear_x
         >> recoil_data.recoil_x >> recoil_data.recoil_y
         >> recoil_data.scalarET
         >> recoil_data.upara_e1 >> recoil_data.upara_e2
         >> recoil_data.pT_e1 >> recoil_data.pT_e2
         >> recoil_data.eta_e1 >> recoil_data.eta_e2
         >> recoil_data.runno >> recoil_data.lumi;
    if( type == 0 ) {
    line >> recoil_data.MZ >> recoil_data.type
         >> recoil_data.eventweight;
    line >> recoil_data.isFSR 
         >> recoil_data.photpT1 >> recoil_data.photpT2;
    }
    else if( type == 1 ) {
    line >> recoil_data.type
         >> recoil_data.eventweight;
    recoil_data.MZ = 90.0;
    }
    _RecoilTree->Fill();
    return true;
  }
  else
    return false;
}

void RecoilFile::ConvertAsciiFile( TString asciifilename , TString rootfilename , int type )
{
  fstream infile( asciifilename );
  TFile * outfile = new TFile( rootfilename.Data() , "recreate" );
  MakeNewTree();
  
  int nevts = 0;
  while( ReadRecoilFile( infile , type ) )
    nevts++;

  _RecoilTree->Write();
}

bool RecoilFile::GetNextFile()
{
  if( recoil_file_list.size() == 0 ) return false;
  current_offset = number_of_entries;
  current_file_idx++;
  if( current_file_idx >= recoil_file_list.size() ) return false;
  if( current_file_idx == 0 )
  {
//     cout << " _RecoilFile " << _RecoilFile << " " << recoil_file_list[current_file_idx] << endl;
    _RecoilFile = new TFile( open_file( recoil_file_list[current_file_idx] ) , "read" );
  }
  else
  {
//     cout << " _RecoilFile " << _RecoilFile << " " << recoil_file_list[current_file_idx] << endl;
    if( !_RecoilFile )
      _RecoilFile = new TFile( open_file( recoil_file_list[current_file_idx] ) , "read" );
    else
    {
      _RecoilFile->Close();
      _RecoilFile = new TFile( open_file( recoil_file_list[current_file_idx] ) , "read" );
    }
  }
  if( !_RecoilFile ) 
  {
    cout << " no file " << endl;
    return false;
  }
  _RecoilTree = (TTree*) _RecoilFile->Get( "RecoilTree" );
  if( !_RecoilTree ) 
  {
    cout << " no tree " << endl;
    return false;
  }
  number_of_entries += _RecoilTree->GetEntries();
  _RecoilTree->SetBranchAddress( "RecoilData" , &recoil_data.pTZ_gen_x );
  return true;
}

bool RecoilFile::GetNextEvent()
{
  if( total_number_of_entries > 0 && number_processed >= total_number_of_entries )
     return false;
  
  bool selectevent = false;
  if( !_RecoilTree ) return false;
  while( !selectevent )
  {
    current_entry++;
    
    if( current_entry > number_of_entries ) {
      if( !GetNextFile() )
        return false;
    }
    
    _RecoilTree->GetEntry( current_entry - current_offset );
    
    selectevent = SelectEvent();
  };

  ZpT_gen.Set( recoil_data.pTZ_gen_x , recoil_data.pTZ_gen_y );
  ZpT_smeared.Set( recoil_data.pTZ_smear_x , recoil_data.pTZ_smear_y );
  Recoil.Set( recoil_data.recoil_x , recoil_data.recoil_y );

  number_processed++;
  
  return true;
}

TString RecoilFile::open_file( const TString & filename )
{
  ifstream file( filename.Data() );
  bool result = file.good() && file.is_open();
  if( result )
    return filename;
  else
  {
    string url = filename.Data();
    string _stageinDirectory = ".";
    string::size_type n = url.find(':');
    string _localFile , remote_path = "";
    if (n != string::npos ) remote_path = url.substr(n+1);
    else remote_path = url;
    if( remote_path.size() == 0 ) cout << " filename " << filename.Data() << endl;
    assert(remote_path.size() > 0);
    string::size_type m = remote_path.rfind('/');
    if(m < string::npos) 
    {
        ++m;
    }
    else
    {
        m = 0;
    }
    _localFile = _stageinDirectory + '/' + remote_path.substr(m);

    /// if local file is already there, then use it!
    ifstream file1( _localFile.c_str() );
    result = file1.good() && file1.is_open();
    if( result )
      return _localFile;
  
    if( staging_host != "" )
      staging_host += ":";
    TString cmd;
    cmd.Form( "%s %s%s %s" , scp_command.Data() , staging_host.Data() , url.c_str() , _localFile.c_str() );
//     string cmd = scp_command.Data() + ' ' + staging_host.Data() + ':' + url + ' ' + _localFile;
    cout << cmd << endl;

    int ok = system(cmd.Data());
    if ( ok != 0 )
    {
        string msg("StageinlistExpander: cannot find ");
        msg+=_localFile;
        cout << msg << endl;
        return TString( "/dev/null" );
    }
    _localFiles.push_back( _localFile );
    return TString(_localFile);
  }
}

void RecoilFile::close_files()
{
  for( int i = 0 ; i < int( _localFiles.size() ) ; i++ )
  {
    if( _localFiles[i].size() > 0 ) remove(_localFiles[i].c_str());
  }
  _localFiles.resize(0);
}

void RecoilFile::InitSetEff()
{
  PParameterReader parm("parameters.rc"); 

  _ZSETEffCorrScaled = parm.GetBool("ZSETEffCorrScaled", kFALSE);
  bool _ZSETEffCorrRelative = parm.GetBool("ZSETEffCorrRelative", kFALSE);
  bool _ZSETEffCorrInterpolate = parm.GetBool("ZSETEffCorrInterpolate", kFALSE);
  double _ZSETEffCorrScale=200.;
  if (_ZSETEffCorrRelative) _ZSETEffCorrScale=20.;
  _ZSETEffCorrParameters = parm.GetVFloat("ZSETEffCorrParameters");

  _ZSETEffCorrParametersCCCC = parm.GetVFloat("ZSETEffCorrParametersCCCC");
  _ZSETEffCorrParametersCCEC = parm.GetVFloat("ZSETEffCorrParametersCCEC");
  _ZSETEffCorrParametersECEC = parm.GetVFloat("ZSETEffCorrParametersECEC");
  
  _ZSETEffCorrPTEpert = parm.GetInt("ZSETEffCorrPTEpert", 0);
  _ZSETEffCorrPTEpertBase = parm.GetVFloat("ZSETEffCorrPTEpertBase");
  _ZSETEffCorrPTEpertA = parm.GetVFloat("ZSETEffCorrPTEpertA");
  _ZSETEffCorrPTEpertB = parm.GetVFloat("ZSETEffCorrPTEpertB");
  _ZSETEffCorrPTEpertC = parm.GetVFloat("ZSETEffCorrPTEpertC");
  _ZSETEffCorrPTEpertD = parm.GetVFloat("ZSETEffCorrPTEpertD");
  _ZSETEffCorrPTEpertE = parm.GetVFloat("ZSETEffCorrPTEpertE");
  _ZSETEffCorrPTEpertF = parm.GetVFloat("ZSETEffCorrPTEpertF");
  _ZSETEffCorrPTEpertG = parm.GetVFloat("ZSETEffCorrPTEpertG");
  _ZSETEffCorrPTEpertH = parm.GetVFloat("ZSETEffCorrPTEpertH");
  _ZSETEffCorrPTEpertNorm = parm.GetVFloat("ZSETEffCorrPTEpertNorm");

  _useHack = parm.GetInt("SETuseHack");
  _useLumiBins = parm.GetBool("SETuseLumiBins");
  if (_useHack){
    char name[100];
    for (Int_t tv=0; tv<7; ++tv){
      std::vector< std::vector<float> >  _tempvec1;
      std::vector< std::vector<float> >  _tempvec2;
      for (Int_t tg=0; tg<7; ++tg){
        
        sprintf(name,"SETEffCorrDataRatioParametersBin%1d_%1d",tv,tg);
        if (tv==6)
          sprintf(name,"SETEffCorrDataRatioParametersBin_%1d",tg);
        _tempvec1.push_back(parm.GetVFloat(name));
        sprintf(name,"SETEffCorrDataRatioParameters2Bin%1d_%1d",tv,tg);
        if (tv==6)
          sprintf(name,"SETEffCorrDataRatioParameters2Bin_%1d",tg);
        _tempvec2.push_back(parm.GetVFloat(name));
      }
      _ZSETEffCorrDataRatioParameters.push_back(_tempvec1);
      _ZSETEffCorrDataRatioParameters2.push_back(_tempvec2);
      _tempvec1.clear();
      _tempvec2.clear();
    }
  }
  
  _ZSETEffCorrPTEpertBase_EC = parm.GetVFloat("ZSETEffCorrPTEpertBase_EC");
  _ZSETEffCorrPTEpertA_EC = parm.GetVFloat("ZSETEffCorrPTEpertA_EC");
  _ZSETEffCorrPTEpertB_EC = parm.GetVFloat("ZSETEffCorrPTEpertB_EC");
  _ZSETEffCorrPTEpertC_EC = parm.GetVFloat("ZSETEffCorrPTEpertC_EC");
  _ZSETEffCorrPTEpertD_EC = parm.GetVFloat("ZSETEffCorrPTEpertD_EC");
  _ZSETEffCorrPTEpertE_EC = parm.GetVFloat("ZSETEffCorrPTEpertE_EC");
  _ZSETEffCorrPTEpertF_EC = parm.GetVFloat("ZSETEffCorrPTEpertF_EC");
  _ZSETEffCorrPTEpertG_EC = parm.GetVFloat("ZSETEffCorrPTEpertG_EC");
  _ZSETEffCorrPTEpertH_EC = parm.GetVFloat("ZSETEffCorrPTEpertH_EC");
  _ZSETEffCorrPTEpertNorm_EC = parm.GetVFloat("ZSETEffCorrPTEpertNorm_EC");

  cout << " _ZSETEffCorrPTEpert " << _ZSETEffCorrPTEpert << endl;
  _SETeffic=0;
/*  if (_ZSETEffCorrPTEpert) {
    _SETeffic = new SETefficiencySmear(_ZSETEffCorrParametersCCCC,_ZSETEffCorrParametersCCEC,_ZSETEffCorrParametersECEC,
                        _ZSETEffCorrScaled,_ZSETEffCorrScale,_ZSETEffCorrRelative,_ZSETEffCorrInterpolate,
                        _ZSETEffCorrPTEpert,
                        &_ZSETEffCorrPTEpertBase,
                        &_ZSETEffCorrPTEpertA, &_ZSETEffCorrPTEpertB,
                        &_ZSETEffCorrPTEpertC, &_ZSETEffCorrPTEpertD,
                        &_ZSETEffCorrPTEpertE, &_ZSETEffCorrPTEpertF,
                        &_ZSETEffCorrPTEpertG, &_ZSETEffCorrPTEpertH,

                        &_ZSETEffCorrPTEpertNorm,
                        &_ZSETEffCorrDataRatioParameters, &_ZSETEffCorrDataRatioParameters2,
                        &_ZSETEffCorrDataRatioPTFit, &_ZSETEffCorrDataRatioLumiFit,
                        &_ZSETEffCorrPTEpertBase_EC,
                        &_ZSETEffCorrPTEpertA_EC, &_ZSETEffCorrPTEpertB_EC,
                        &_ZSETEffCorrPTEpertC_EC, &_ZSETEffCorrPTEpertD_EC,
                        &_ZSETEffCorrPTEpertE_EC, &_ZSETEffCorrPTEpertF_EC,
                        &_ZSETEffCorrPTEpertG_EC, &_ZSETEffCorrPTEpertH_EC,
                        &_ZSETEffCorrPTEpertNorm_EC, _useHack, _useLumiBins);
                        

                        
  } else {
    _SETeffic = new SETefficiencySmear(_ZSETEffCorrParameters,_ZSETEffCorrScaled);
  }*/
 
  _UparaEffCorrOption = parm.GetInt("UparaEffCorrOption", 1);
  _ZUparaEffParameters = parm.GetVDouble("ZUparaEffCorrParameters_CC");

  _Z_u0_CC = parm.GetFloat("Z_u0_CC", 3.29440);
  _Z_s_CC = parm.GetFloat("Z_s_CC", 0.001787);
  _Z_u0_EC = parm.GetFloat("Z_u0_EC", 2.308);
  _Z_s_EC = parm.GetFloat("Z_s_EC", 0.0046);
}

double RecoilFile::CalcSETEfficiency( float scalarEt_All, float lumi, float epT1, float epT2, float eta1, float eta2 )
{
  float eff=1;
  if( !_SETeffic ) return eff;

  if (_ZSETEffCorrPTEpert) {
    eff=_SETeffic->getSETeff(scalarEt_All, lumi, epT1, epT2, false, false, eta1, eta2);
  } else {
    eff=_SETeffic->getSETeff(scalarEt_All, lumi);
  }

  return eff;
}

double RecoilFile::CalcUparaEfficiency(float upara1, float upara2)
{
  float eff=1;
 
  double the_upar[2];
  double upara_eff[2];
  
  the_upar[0]=upara1;
  the_upar[1]=upara2;

  // calculate uparallel efficiency for CC and EC regions

  for(int i=0; i<2; i++){

    if(_UparaEffCorrOption == 0) {
      if(the_upar[i]<_Z_u0_CC) upara_eff[i] = 1.;
      else upara_eff[i] = 1. - _Z_s_CC*(the_upar[i] - _Z_u0_CC);
    } else { // for _ZUparaEffCorrOption!=0, used for real data, two linear functions
      if(the_upar[i] < _ZUparaEffParameters[0])
  upara_eff[i] = 1. - _ZUparaEffParameters[1] * (the_upar[i] - _ZUparaEffParameters[0]);
      else
  upara_eff[i] = 1. - _ZUparaEffParameters[2] * (the_upar[i] - _ZUparaEffParameters[0]);
    }
  }
    
  eff = upara_eff[0]*upara_eff[1];

  return eff;
}
