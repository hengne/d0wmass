#ifndef recoilmap_hpp
#define recoilmap_hpp

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>  //atoi
#include <vector>
#include "TTree.h"
#include "TFile.h"
#include "TVector2.h"
#include "RecoilFile.hpp"
#include "TMath.h"

using namespace std;

const int n_pT_bin_array = 156;
const float pT_bin_array[n_pT_bin_array] = {0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0, 5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25, 8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25, 11.5, 11.75, 12.0, 12.33, 12.66, 13.0, 13.33, 13.66, 14.0, 14.5, 15.0, 15.5, 16.0, 16.5, 17.0, 17.5, 18.0, 18.5, 19.0, 19.5, 20.0, 20.5, 21.0, 21.5, 22.0, 22.5, 23.0, 23.5, 24.0, 24.5, 25.0,25.5, 26.0, 26.5, 27.0, 27.5, 28.0, 28.5, 29.0, 29.5, 30.0, 30.5, 31.0, 31.5, 32.0, 32.5, 33.0, 33.5, 34.0, 34.5, 35.0,35.5, 36.0, 36.5, 37.0, 37.5, 38.0, 38.5, 39.0, 39.5, 40.0, 40.5, 41.0, 41.5, 42.0, 42.5, 43.0, 43.5, 44.0, 44.5, 45.0, 45.5, 46.0, 46.5, 47.0, 47.5, 48.0, 48.5, 49.0, 49.5, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0, 57.0, 58.0, 59.0, 60.0, 62.0, 64.0, 66.0, 68.0, 70.0, 72.0, 74.0, 76.0, 78.0, 80.0, 84.0, 88.0, 92.0, 96.0, 100.0, 105.0, 110.0, 120.0, 160.0};

const int n_RpT_bin_array = 54;
const float RpT_bin_array[n_RpT_bin_array] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0, 34.0, 36.0, 38.0, 42.0, 46.0, 50.0, 55.0, 60.0, 62.0, 64.0, 66.0, 68.0, 70.0};

const int n_course_pT_bin_array = 34;
const float course_pT_bin_array[34] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 34.0, 38.0, 42.0, 46.0, 50.0, 55.0, 60.0, 70.0};

const int n_recoil_bin_array = 90;
const float recoil_bin_array[n_recoil_bin_array] = { -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14.5, -14.0, -13.5, -13.0, -12.5, -12.0, -11.5, -11.0, -10.5, -10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0, 14.5, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };

class RecoilMap {
  public:
    RecoilMap(bool _use_fine_zpt_bins = false){ use_fine_zpt_bins = _use_fine_zpt_bins ; InitBinEdges(); };
    
    ~RecoilMap(){};
    
    int n_zpt_bins_fine , n_zpt_bins;
    vector<float> zpt_bin_edges_fine , zpt_bin_deltas_fine , zpt_bin_edges , zpt_bin_deltas;
    
    int n_zphi_bins;
    vector<float> zphi_bin_edges , zphi_bin_deltas;
    
    int n_recoil_bins;
    vector<float> recoil_bin_edges , recoil_bin_deltas;
    
    int n_psi_bins;
    vector<float> psi_bin_edges , psi_bin_deltas;

    /// Helpful for later:
    vector<float> mean_uparaz_array , mean_uparaz_norms , mean_ut_array , mean_zpt_array;
    vector<float> uparaz_correction , ut_correction , zpt_correction ;
    /// ZPT only
    vector<float> zpt_true_array;
    vector<float> zpt_smeared_array;
    vector<float> zpt_unfolded_array;
    vector<float> zpt_test_array;
    vector<float> eff_zpt;
    vector<vector<float> > zpt_map;
    vector<vector<float> > zpt_inv_map;
    /// Z Phi
    vector<vector<float> > zpt_zphi_true_array;
    vector<vector<float> > zpt_zphi_smeared_array;
    vector<vector<float> > zpt_zphi_unfolded_array;
    vector<vector<float> > zpt_zphi_test_array;
    vector<vector<float> > eff_zpt_zphi;
    vector<vector<vector<vector<float> > > > zpt_zphi_map;
    vector<vector<vector<vector<float> > > > zpt_zphi_inv_map;
    vector<vector<vector<vector<float> > > > zpt_zphi_ut_uphi_array;
    vector<vector<vector<vector<vector<vector<float> > > > > > zpt_zphi_ut_uphi_map , zpt_zphi_ut_uphi_inv_map;
    
    
    bool use_fine_zpt_bins;
    
    void InitBinEdges();
    void InitArrays();
    void InitMap();
    void InitInvMap();
    
    bool FillZPTArray( RecoilFile & inp );
    bool FillZPTMap( RecoilFile & inp );
    bool NormalizeZPTMap();
    
    bool GetZPTUnf();
    bool GetBayesInv();
  
    bool WriteMap( vector<float> & vec , TString filename = "zpt_array.txt" );
    bool WriteMap( vector<vector<float> > & vec , TString filename = "zpt_map_matrix.txt" );
    bool WriteMap( vector<vector<vector<vector<float> > > > & vec , TString filename = "map_matrix.txt" );
    bool WriteMap( vector<vector<vector<vector<vector<vector<vector<vector<float> > > > > > > > & vec , TString filename = "zpt_zphi_ut_uphi_matrix.txt" );
    bool WriteZPTMap();
    bool WriteZPTInvMap();
    
    bool ReadMap( vector<float> & vec , TString filename = "zpt_array.txt" );
    bool ReadMap( vector<vector<float> > & vec , TString filename = "zpt_map_matrix.txt" );
    bool ReadMap( vector<vector<vector<vector<float> > > > & vec , TString filename = "map_matrix.txt" );
    bool ReadMap( vector<vector<vector<vector<vector<vector<vector<vector<float> > > > > > > > & vec , TString filename = "zpt_zphi_ut_uphi_matrix.txt" );
    bool ReadZPTMap();
    bool ReadZPTInvMap();
    bool ReadCorrection();
    
    bool RunClosureTest();
    
    inline int get_bin( float value , vector<float> & edges ) 
    {
      int n_edges = edges.size();
      if( value < edges[0] ) return -1;
      if( value >= edges[n_edges-1] ) return n_edges-1;
      for( int i = 0 ; i < (n_edges-1) ; i++ )
      {
        if( value >= edges[i] && value < edges[i+1] )
          return i;
      }
      return -1;
    }
    
    inline int GetZPT_true_bin( RecoilFile & inp , bool fine = false ) 
    {
      float zpt_gen_mag = inp.ZpT_gen.Mod();
      if( fine )
        return get_bin( zpt_gen_mag , zpt_bin_edges_fine );
      else
        return get_bin( zpt_gen_mag , zpt_bin_edges );
    };
    
    inline int GetZPT_smeared_bin( RecoilFile & inp , bool fine = false ) 
    {
      float zpt_smr_mag = inp.ZpT_smeared.Mod();
      if( fine )
        return get_bin( zpt_smr_mag , zpt_bin_edges_fine );
      else
        return get_bin( zpt_smr_mag , zpt_bin_edges );
    };
    
    inline int GetUT_bin(  RecoilFile & inp ) 
    {
      float recoil_mag = inp.Recoil.Mod();
      return get_bin( recoil_mag , recoil_bin_edges );
    };

    inline int GetDPhi_gen_smeared_bin( RecoilFile & inp ) 
    {
      float dphi_gen_smeared = inp.ZpT_gen.Phi_0_2pi( inp.ZpT_gen.DeltaPhi( inp.ZpT_smeared ) );
      return get_bin( dphi_gen_smeared , zphi_bin_edges );
    };
    
    inline int GetZPhi_gen_bin(  RecoilFile & inp ) 
    {
      float zphi_gen = inp.Zphi_gen();
      return get_bin( zphi_gen , zphi_bin_edges );
    };

    inline int GetZPhi_smeared_bin(  RecoilFile & inp ) 
    {
      float zphi_smeared = inp.Zphi_smeared();
      return get_bin( zphi_smeared , zphi_bin_edges );
    };
    
 
    inline int GetPsi_gen_bin(  RecoilFile & inp ) 
    {
      float psi_gen = inp.Psi_gen();
      return get_bin( psi_gen , psi_bin_edges );
    };

    inline int GetPsi_smeared_bin( RecoilFile & inp ) 
    {
      float psi_smeared = inp.Psi_smeared();
      return get_bin( psi_smeared , psi_bin_edges );
    };
    
    inline bool normalize_vec( vector<float> & vec , float norm = -1 ) 
    {
      if( norm <= 0 )
      {
        norm = 0;
        for( int i = 0 ; i < vec.size() ; i++ )
          norm += vec[i];
      }
      if( norm <= 0 ) 
        return false;
      else
      {
        for( int i = 0 ; i < vec.size() ; i++ )
          vec[i] /= norm;
      }
      return true;
    };
    
    inline bool normalize_vec( vector<vector<float> > & vec , float norm = -1 ) 
    {
      if( norm <= 0 )
      {
        norm = 0;
        for( int i = 0 ; i < vec.size() ; i++ )
        {
          for( int j = 0 ; j < vec[i].size() ; j++ )
          {
          norm += vec[i][j];
          }
        }
      }
      if( norm <= 0 ) 
        return false;
      else
      {
        for( int i = 0 ; i < vec.size() ; i++ )
        {
          for( int j = 0 ; j < vec[i].size() ; j++ )
          {
            vec[i][j] /= norm;
          }  
        }
      }
      return true;
    };
    
    inline bool normalize_vec( vector<vector<vector<float> > > & vec , float norm = -1 ) 
    {
      if( norm <= 0 )
      {
      norm = 0;
        for( int i = 0 ; i < vec.size() ; i++ )
        {
          for( int j = 0 ; j < vec[i].size() ; j++ )
          {
            for( int k = 0 ; k < vec[i][j].size() ; k++ )
            {
              norm += vec[i][j][k];
            }
          }
        }
      }
      if( norm <= 0 ) 
        return false;
      else
      {
        for( int i = 0 ; i < vec.size() ; i++ )
        {
          for( int j = 0 ; j < vec[i].size() ; j++ )
          {
            for( int k = 0 ; k < vec[i][j].size() ; k++ )
            {
              vec[i][j][k] /= norm;
            }
          }
        }
      }
      return true;
    };

    inline bool normalize_vec( vector<vector<vector<vector<float> > > > & vec , float norm = -1 ) 
    {
      if( norm <= 0 )
      {
        norm = 0;
        for( int i = 0 ; i < vec.size() ; i++ )
        {
          for( int j = 0 ; j < vec[i].size() ; j++ )
          {
            for( int k = 0 ; k < vec[i][j].size() ; k++ )
            {
              for( int l = 0 ; l < vec[i][j][k].size() ; l++ )
              {
                norm += vec[i][j][k][l];
              }
            }
          }
        }
      }
      if( norm <= 0 ) 
        return false;
      else
      {
        for( int i = 0 ; i < vec.size() ; i++ )
        {
          for( int j = 0 ; j < vec[i].size() ; j++ )
          {
            for( int k = 0 ; k < vec[i][j].size() ; k++ )
            {
              for( int l = 0 ; l < vec[i][j][k].size() ; l++ )
              { 
                vec[i][j][k][l] /= norm;
              }
            }
          }
        }
      }
      return true;
   };
   
   inline void InitArray(vector<float> & vec , int nbins0 ) 
   {
      for( int i = 0 ; i < nbins0 ; i++ )
        vec.push_back( 0 );
   };
   
   inline void InitArray( vector<vector<float> > & vec , int nbins0 , int nbins1 ) 
   {
     for( int i = 0 ; i < nbins0 ; i++ )
     {
       vector<float> temp_vec;
       InitArray( temp_vec , nbins1 );
       vec.push_back( temp_vec );
     }
   };
   
   inline void InitArray( vector<vector<vector<float> > > & vec , int nbins0 , int nbins1 , int nbins2 ) 
   {
     for( int i = 0 ; i < nbins0 ; i++ )
     {
       vector<vector<float> > temp_vec;
       InitArray( temp_vec , nbins1 , nbins2 );
       vec.push_back( temp_vec );
     }
   };
   
   inline void InitArray( vector<vector<vector<vector<float> > > > & vec , int nbins0 , int nbins1 , int nbins2  , int nbins3 ) 
   {
     for( int i = 0 ; i < nbins0 ; i++ )
     {
       vector<vector<vector<float> > > temp_vec;
       InitArray( temp_vec , nbins1 , nbins2 , nbins3 );
       vec.push_back( temp_vec );
     }
   };

   inline void InitArray( vector<vector<vector<vector<vector<float> > > > > & vec , int nbins0 , int nbins1 , int nbins2  , int nbins3 , int nbins4 ) 
   {
     for( int i = 0 ; i < nbins0 ; i++ )
     {
       vector<vector<vector<vector<float> > > > temp_vec;
       InitArray( temp_vec , nbins1 , nbins2 , nbins3 , nbins4 );
       vec.push_back( temp_vec );
     }
   };

   inline void InitArray( vector<vector<vector<vector<vector<vector<float> > > > > > & vec , int nbins0 , int nbins1 , int nbins2  , int nbins3 , int nbins4 , int nbins5 ) 
   {
     for( int i = 0 ; i < nbins0 ; i++ )
     {
       vector<vector<vector<vector<vector<float> > > > > temp_vec;
       InitArray( temp_vec , nbins1 , nbins2 , nbins3 , nbins4 , nbins5 );
       vec.push_back( temp_vec );
     }
   };

   inline void InitArray( vector<vector<vector<vector<vector<vector<vector<float> > > > > > > & vec , int nbins0 , int nbins1 , int nbins2  , int nbins3 , int nbins4 , int nbins5 , int nbins6 ) 
   {
     for( int i = 0 ; i < nbins0 ; i++ )
     {
       vector<vector<vector<vector<vector<vector<float> > > > > > temp_vec;
       InitArray( temp_vec , nbins1 , nbins2 , nbins3 , nbins4 , nbins5 , nbins6 );
       vec.push_back( temp_vec );
     }
   };

   inline void InitArray( vector<vector<vector<vector<vector<vector<vector<vector<float> > > > > > > > & vec , int nbins0 , int nbins1 , int nbins2  , int nbins3 , int nbins4 , int nbins5 , int nbins6 , int nbins7 ) 
   {
     for( int i = 0 ; i < nbins0 ; i++ )
     {
       vector<vector<vector<vector<vector<vector<vector<float> > > > > > > temp_vec;
       InitArray( temp_vec , nbins1 , nbins2 , nbins3 , nbins4 , nbins5 , nbins6 , nbins7 );
       vec.push_back( temp_vec );
     }
   };

   double * get_pt_bins_fine() 
   {
     double * _pt_bins_fine = new double[n_pT_bin_array+1];
     for( int i = 0 ; i < n_pT_bin_array ; i++ )
       _pt_bins_fine[i] = pT_bin_array[i];
     _pt_bins_fine[n_pT_bin_array] = 300;
     return _pt_bins_fine;
   }
   
   double * get_recoil_bins()
   {
     double * _recoil_bins = new double[n_recoil_bin_array+1];
     for( int i = 0 ; i < n_recoil_bin_array ; i++ )
       _recoil_bins[i] = recoil_bin_array[i];
     _recoil_bins[n_recoil_bin_array] = 30;
     return _recoil_bins;
   }
};

#endif
