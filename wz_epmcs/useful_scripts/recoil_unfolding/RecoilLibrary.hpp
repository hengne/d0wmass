#ifndef recoillibrary_hpp
#define recoillibrary_hpp

#include <vector>

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TRandom3.h"

#include "RecoilFile.hpp"
#include "RecoilMap.hpp"

using namespace std;

class RecoilLibrary {
  public:
    RecoilLibrary(int _do_ux_uy=0 , bool _use_set_upar_wgts=false , TRandom3 * _dummy = 0) {
      ux_uy_flag=_do_ux_uy; 
      use_set_upar_wgts=_use_set_upar_wgts;
      if( _dummy )
        dummy = _dummy;
      else
        dummy = new TRandom3();
    };
    
    ~RecoilLibrary(){};

    TRandom3 * dummy;
    
    // contents of recoil file
    TH1F * InstLumi_WZ , * InstLumi_WZ_orig;
    TH1F * RunNo_WZ;
    TH1F * SET_WZ , * SET_WZ_orig;
    
    vector<vector<TH2F*> > recoil_unf_hists;
    vector<TH1F*> set_gen_hists , set_unf_hists , set_smr_hists;
    
    // control distributions
    TH1F *zpt_gen_hist , *zpt_unf_hist , *zpt_smr_hist;
    vector<TH1F*> zdphi_gen_smr_hist;
    TH1F *ut_gen_hist , *ut_unf_hist , *ut_smr_hist;
    TH1F *uphi_gen_hist , *uphi_unf_hist , *uphi_smr_hist;
    vector<TH1F*> ut_gen_hists , ut_unf_hists , ut_smr_hists;
    vector<TH1F*> uphi_gen_hists , uphi_unf_hists , uphi_smr_hists;
    vector<TH1F*> udphi_gen_hists , udphi_unf_hists , udphi_smr_hists;

    vector<TH1F*> uparaz_gen_hists , uparaz_unf_hists , uparaz_smr_hists;
    vector<TH1F*> uperpz_gen_hists , uperpz_unf_hists , uperpz_smr_hists;
    
    TGraphErrors *zdphi_means , *zdphi_widths;
    TGraphErrors *zpt_residuals , *ut_residuals , *uphi_residuals;
    TGraph *ut_means , *uparaz_means , *zpt_means;
    TGraphErrors *ut_means_gen , *ut_means_unf , *ut_means_smr;
    TGraphErrors *ut_widths_gen , *ut_widths_unf , *ut_widths_smr;
    TGraphErrors *ut_means_residuals , *ut_widths_residuals;

    TGraphErrors *uparaz_means_gen , *uparaz_means_unf , *uparaz_means_smr;
    TGraphErrors *uparaz_widths_gen , *uparaz_widths_unf , *uparaz_widths_smr;
    TGraphErrors *uparaz_means_residuals , *uparaz_widths_residuals;
    TGraphErrors *uperpz_means_gen , *uperpz_means_unf , *uperpz_means_smr;
    TGraphErrors *uperpz_widths_gen , *uperpz_widths_unf , *uperpz_widths_smr;
    TGraphErrors *uperpz_means_residuals , *uperpz_widths_residuals;
    
    TGraphErrors *uphi_means_gen , *uphi_means_unf , *uphi_means_smr;
    TGraphErrors *uphi_widths_gen , *uphi_widths_unf , *uphi_widths_smr;
    TGraphErrors *uphi_means_residuals , *uphi_widths_residuals;
    TGraphErrors *udphi_means_gen , *udphi_means_unf , *udphi_means_smr;
    TGraphErrors *udphi_widths_gen , *udphi_widths_unf , *udphi_widths_smr;
    TGraphErrors *udphi_means_residuals , *udphi_widths_residuals;

    TGraphErrors *psi_means_gen , *psi_means_unf , *psi_means_smr;
    TGraphErrors *psi_widths_gen , *psi_widths_unf , *psi_widths_smr;
    TGraphErrors *psi_means_residuals , *psi_widths_residuals;

    TFile * recoil_file;
    
    TFile * control_file;
    
    int ux_uy_flag;
    bool use_set_upar_wgts;
    
    void InitHistograms( RecoilMap & genmap , bool do_control_test = false );
    
    void FillHistograms( RecoilFile & inp , RecoilMap & genmap , bool do_control_test = false );
    
    inline void normalize_hist( TH1F* hist ) {
      double norm = hist->Integral();
      if( norm > 0 )
        hist->Scale( 1/norm );
    };
    
    inline void normalize_hist( TH2F* hist ) {
      double norm = hist->Integral();
      if( norm > 0 )
        hist->Scale( 1/norm );
    };
    
    inline void normalize_hist_var_bin( TH1F * hist ) {
      normalize_hist( hist );
      for( int i = 1 ; i <= hist->GetNbinsX() ; i++ )
      {
        double val = hist->GetBinContent( i );
        double width = hist->GetXaxis()->GetBinWidth( i );
        hist->SetBinContent( i , val / width );
      }
    };
    
    inline void SetGraphNameTitle( TGraph * graph , TString name , TString title ) {
      if( graph )
      {
        graph->SetName( name );
        graph->SetTitle( title );
      }
    };
    
    inline void DeleteHistos() {
      recoil_unf_hists.clear();
      set_gen_hists.clear(); set_unf_hists.clear(); set_smr_hists.clear(); 
    
      zdphi_gen_smr_hist.clear(); 
      ut_gen_hists , ut_unf_hists , ut_smr_hists;

      uparaz_gen_hists.clear(); uparaz_unf_hists.clear(); uparaz_smr_hists.clear(); 
      uperpz_gen_hists.clear(); uperpz_unf_hists.clear(); uperpz_smr_hists.clear(); 
      
      uphi_gen_hists.clear(); uphi_unf_hists.clear(); uphi_smr_hists.clear(); 
      udphi_gen_hists.clear(); udphi_unf_hists.clear(); udphi_smr_hists.clear(); 
    };

    inline void InitTH1F( vector<TH1F*> & vec , int nbinsx )
    {
      for( int i = 0 ; i < nbinsx ; i++ )
      {
        TH1F * temp = 0;
        vec.push_back( temp );
      }
    };
    
    inline void InitTH2F( vector<TH2F*> & vec , int nbinsx ) 
    {
      for( int i = 0 ; i < nbinsx ; i++ )
      {
        TH2F * temp = 0;
        vec.push_back( temp );
      }
    };

    inline void InitTH2F( vector<vector<TH2F*> > & vec , int nbinsx , int nbinsy ) 
    {
      for( int i = 0 ; i < nbinsx ; i++ )
      {
        vector<TH2F*> temp_vec;
        InitTH2F( temp_vec , nbinsy );
        vec.push_back( temp_vec );
      }
    };

    void GetGraphs( RecoilMap & genmap );

    const static bool use_inverse_probs = true;
};

#endif
