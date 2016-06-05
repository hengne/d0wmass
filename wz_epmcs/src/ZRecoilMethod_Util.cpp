#include "ZRecoilMethod_Util.hpp"
#include <TROOT.h>
#include <TH2.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <TString.h>
#include <TVector2.h>
#include <map>
#include <cmath>
#include <cstdlib>

using namespace std;

bool binary_search( TH2F * the_hist , double value , int & binx , int & biny , bool invprob = false )
{
  int nbinsx = the_hist->GetNbinsX();
  int nbinsy = the_hist->GetNbinsY();
  int ntotal = nbinsx * nbinsy;
  int nabove , nbelow , middle;
  nabove = ntotal + 1;
  nbelow = 0;
  while( nabove - nbelow > 1 ) {
    middle = ( nabove + nbelow ) / 2;
    if( !invprob )
    {
      binx = int( middle / nbinsy ) + 1;
      biny = int( middle % nbinsy ) + 1;
    }
    else
    {
      binx = int( middle % nbinsx ) + 1;
      biny = int( middle / nbinsx ) + 1;
    }
    double binval = the_hist->GetBinContent( binx , biny );
    if( value == binval ) return true;
    if( value < binval ) nabove = middle;
    else nbelow = middle;
  }
  return true;
}

ZRecoilMethod_Util::~ZRecoilMethod_Util() {;}

// simple constructor
ZRecoilMethod_Util::ZRecoilMethod_Util(TString data_recoilname, std::vector<double> recoil_pT_bin_edges, 
				       std::vector<double> course_pT_bin_edges, std::vector<double> Lumi_bin_edges, 
				       bool CConly) {

  _recoil_pT_bin_edges = recoil_pT_bin_edges;
  int _num_recoil_pT_bins = recoil_pT_bin_edges.size();
  
  int _num_recoil_phi_bins = 60;
  _recoil_Phi_bin_edges.clear();
  for( int i = 0 ; i < _num_recoil_phi_bins ; i++ )
    _recoil_Phi_bin_edges.push_back( 2.*TMath::Pi() * i / _num_recoil_phi_bins );
  
  _course_pT_bin_edges = course_pT_bin_edges;
  int _num_course_pT_bins = _course_pT_bin_edges.size();

  _Lumi_bin_edges = Lumi_bin_edges;
  int _num_Lumi_bins = _Lumi_bin_edges.size();

  _isCConly = CConly;

  cout << " opening recoil file " << data_recoilname << endl;
  therecoilFile = new TFile(data_recoilname,"read");

  for( int i = 0 ; i < _num_recoil_pT_bins ; i++ )
  {
    vector<TH2F*> temp_rec_zphi;
    vector<TH2F*> temp_int_rec_zphi;
    vector<TH1F*> temp_set_ut;
    for( int j = 0 ; j < _num_recoil_phi_bins ; j++ )
    {
      TString rechistname , int_rechistname;
      rechistname.Form( "rec_unf_hist_%i_%i" , i , j );
      if( !use_inverse_probs )
        int_rechistname.Form( "int_%s" , rechistname.Data() );
      else
        int_rechistname.Form( "int2_%s" , rechistname.Data() );
      TH2F* graph = (TH2F*) therecoilFile->Get(int_rechistname);
      if( graph )
      {
        temp_int_rec_zphi.push_back( graph );
        temp_rec_zphi.push_back( 0 );
      }
      else
      {
        temp_int_rec_zphi.push_back( 0 );
        temp_rec_zphi.push_back( (TH2F*) therecoilFile->Get(rechistname) );
      }
    }
    TString sethistname;
    sethistname.Form( "set_unf_hist_%i" , i );
    _SEThist.push_back( (TH1F*) therecoilFile->Get(sethistname) );
    _recoilhist.push_back( temp_rec_zphi );
    _int_recoilhist.push_back( temp_int_rec_zphi );
  }

  SETdist = (TH1F*) therecoilFile->Get( "SET_WZ" );
  ut_means = (TGraph*) therecoilFile->Get( "ut_means" );
  uparaz_means = (TGraph*) therecoilFile->Get( "uparaz_means" );
  
  InstLumi_WZ = (TH1F*) therecoilFile->Get("InstLumi_WZ");
  RunNo_WZ = (TH1F*) therecoilFile->Get("RunNo_WZ");

  cout<<"Done Initializing ZRecoilMethod_Util"<<endl;
}



//--------------------------------------------------------------------------- 
// this is the function we finally want 
// this is the final mapping from gen ZpT, ZPhi in the first PMCS table to recoilX and recoilY in the second data table
//--------------------------------------------------------------------------- 
// DB -- Modified to use Zphi bins in addition to zpt
void ZRecoilMethod_Util::PickRecoil(double gen_ZpX, double gen_ZpY, double& data_RecoilPx, double& data_RecoilPy, TRandom3 * dummy) {

  TVector2 genzpt( gen_ZpX , gen_ZpY );
  double gen_ZpT = genzpt.Mod();
  double gen_Zphi = genzpt.Phi_0_2pi(genzpt.Phi());

  int pTBin = FindPtBin( gen_ZpT );
  int phiBin = FindPhiBin( gen_Zphi );

// randomly pick up one event from the corresponding 2D histogram
//   double recoilx_smear, recoily_smear;
  
  double temprecx = -gen_ZpX , temprecy = -gen_ZpY;
  if( _int_recoilhist[pTBin][phiBin] )
  {
    double rand0 = dummy->Rndm();
    double rand1 = dummy->Rndm();
    double rand2 = dummy->Rndm();
    int binx , biny;
    binary_search( _int_recoilhist[pTBin][phiBin] , rand0 , binx , biny , use_inverse_probs );
    double x0 = _int_recoilhist[pTBin][phiBin]->GetXaxis()->GetBinLowEdge( binx );
    double x1 = x0+_int_recoilhist[pTBin][phiBin]->GetXaxis()->GetBinWidth( binx );
    double y0 = _int_recoilhist[pTBin][phiBin]->GetYaxis()->GetBinLowEdge( biny );
    double y1 = y0+_int_recoilhist[pTBin][phiBin]->GetYaxis()->GetBinWidth( biny );
    double d0 = _int_recoilhist[pTBin][phiBin]->GetBinContent( binx , biny );
    temprecx = x0;
    temprecy = y0;
    if( !use_inverse_probs )
    {
      if( biny != _int_recoilhist[pTBin][phiBin]->GetNbinsY() )
        biny += 1;
      double d1 = _int_recoilhist[pTBin][phiBin]->GetBinContent( binx , biny );
      temprecx += rand1 * ( x1 - x0 );
      if( d1 - d0 > 0 )
        temprecy += ( rand0 - d0 ) / ( d1 - d0 ) * ( y1 - y0 );
      else
        temprecy += rand2 * ( y1 - y0 );
    }
    else
    {
      if( binx != _int_recoilhist[pTBin][phiBin]->GetNbinsX() )
        binx += 1;
      double d1 = _int_recoilhist[pTBin][phiBin]->GetBinContent( binx , biny );
      if( d1 - d0 > 0 )
        temprecx += ( rand0 - d0 ) / ( d1 - d0 ) * ( x1 - x0 );
      else
        temprecx += rand2 * ( y1 - y0 );
      temprecy += rand1 * ( y1 - y0 );
    }
  }
  else if( _recoilhist[pTBin][phiBin] -> GetIntegral() > 0 )
    _recoilhist[pTBin][phiBin] -> GetRandom2(temprecx, temprecy);    
  else
     cout << "no recoil " << temprecx << " " << temprecy << endl;
  
  if( ux_uy_flag == 0 )
  {
    /// ux uy
    data_RecoilPx = temprecx ;
    data_RecoilPy = temprecy ;
  }
  else if( ux_uy_flag == 1 )
  {
    /// uparaz, uperpz
    temprecx += uparaz_means->GetY()[pTBin];
    data_RecoilPx = (temprecx * gen_ZpX + temprecy * gen_ZpY)/gen_ZpT;
    data_RecoilPy = (temprecx * gen_ZpY - temprecy * gen_ZpX)/gen_ZpT;
  }
  else if( ux_uy_flag == 2 )
  {
    /// ut uphi
    double ut_val = temprecx + ut_means->GetY()[pTBin];
    int _num_recoil_phi_bins = _recoil_Phi_bin_edges.size();
    double uphi_val = temprecy + _recoil_Phi_bin_edges[phiBin] + TMath::Pi() / _num_recoil_phi_bins;
    data_RecoilPx = ut_val * cos( uphi_val );
    data_RecoilPy = ut_val * sin( uphi_val );  
  }
  else if( ux_uy_flag == 3 )
  {
    /// uparaz, uperpz
    temprecx += uparaz_means->GetY()[pTBin];
    int _num_recoil_phi_bins = _recoil_Phi_bin_edges.size();
    double uphi_val = temprecy + _recoil_Phi_bin_edges[phiBin] + TMath::Pi() / _num_recoil_phi_bins;
    double ut_val = temprecx / cos( uphi_val );
    data_RecoilPx = ut_val * cos( uphi_val );
    data_RecoilPy = ut_val * sin( uphi_val );  
  }
}


double ZRecoilMethod_Util::PickSET(double gen_ZpT, double theRecoil) {

  double outSET;

  int PtBin = FindCoursePtBin(gen_ZpT);
  int RecBin = FindCoursePtBin(theRecoil);

//   for( int i = 0 ; i < _course_pT_bin_edges.size() ; i++ )
//     cout << " course pt bs " << i << " " << _course_pT_bin_edges[i] << endl;

  if( _SEThist[PtBin]->Integral() > 0 )
      outSET = _SEThist[PtBin]->GetRandom();
  else
      outSET = SETdist->GetRandom();

  return outSET;
}

int ZRecoilMethod_Util::findbin( double value , vector<double> & vec ) {
  int nedges = vec.size();
  if( value < vec[0] ) return -1;
  if( value >= vec[nedges-1] ) return nedges-1;
  for( int i = 0 ; i < (nedges-1) ; i++ )
  {
    if( value >= vec[i] && value < vec[i+1] )
    {
      return i;
    }
  }
  return -1;
}

int ZRecoilMethod_Util::FindPtBin(double thePt) {
  // determine recoil pT bin number
  return findbin( thePt , _recoil_pT_bin_edges );
}

int ZRecoilMethod_Util::FindPhiBin(double thePhi) {
  // determine recoil Phi bin number
  return findbin( thePhi , _recoil_Phi_bin_edges );
}

int ZRecoilMethod_Util::FindCoursePtBin(double thePt) {
  // determine recoil pT bin number
  return findbin( thePt , _course_pT_bin_edges );
}

int ZRecoilMethod_Util::FindLumiBin(double theLumi) {
  // determine recoil pT bin number
  return findbin( theLumi , _Lumi_bin_edges );
}
