#include "RecoilMap.hpp"
#include "RecoilFile.hpp"
#include "TMath.h"
#include "TMatrixD.h"

using namespace std;

void RecoilMap::InitBinEdges()
{
    n_zpt_bins_fine = n_pT_bin_array;
    zpt_bin_edges_fine.clear();
    zpt_bin_deltas_fine.clear();
    for( int i = 0 ; i < n_zpt_bins_fine ; i++ )
    {
      zpt_bin_edges_fine.push_back( pT_bin_array[i] );
      if( i < n_zpt_bins_fine - 1 )
        zpt_bin_deltas_fine.push_back( pT_bin_array[i+1] - pT_bin_array[i] );
      else
        zpt_bin_deltas_fine.push_back( 1.0 );
    }
  
    n_zpt_bins = 34;
    if( use_fine_zpt_bins ) n_zpt_bins = n_zpt_bins_fine;
    zpt_bin_edges.clear();
    if( use_fine_zpt_bins ) 
    {
      zpt_bin_edges = zpt_bin_edges_fine;
      zpt_bin_deltas = zpt_bin_deltas_fine;
    }
    else
    {
      for( int i = 0 ; i < n_zpt_bins ; i++ )
      {
        zpt_bin_edges.push_back( course_pT_bin_array[i] );
        if( i < n_zpt_bins - 1 )
          zpt_bin_deltas.push_back( course_pT_bin_array[i+1] - course_pT_bin_array[i] );
        else
          zpt_bin_deltas.push_back( 1.0 );
      }
    }
    
    n_zphi_bins = 60;
    zphi_bin_edges.clear();
    for( int i = 0 ; i < n_zphi_bins ; i++ )
    {
      zphi_bin_edges.push_back( 2.*TMath::Pi() * i / n_zphi_bins );
      zphi_bin_deltas.push_back( 2.*TMath::Pi() / n_zphi_bins );
    }
    
    n_recoil_bins = n_RpT_bin_array;
    recoil_bin_edges.clear();
    for( int i = 0 ; i < n_recoil_bins ; i++ )
    {
      recoil_bin_edges.push_back( RpT_bin_array[i] );
      if( i < n_zpt_bins - 1 )
        recoil_bin_deltas.push_back( RpT_bin_array[i+1] - RpT_bin_array[i] );
      else
        recoil_bin_deltas.push_back( 1.0 );
    }

    n_psi_bins = 60;
    psi_bin_edges.clear();
    for( int i = 0 ; i < n_psi_bins ; i++ )
    {
      psi_bin_edges.push_back( 2.*TMath::Pi() * i / n_psi_bins - TMath::Pi());
      psi_bin_deltas.push_back( 2.*TMath::Pi() / n_psi_bins );
    }
    
    mean_uparaz_array.clear();
    mean_uparaz_norms.clear();
    mean_ut_array.clear();
    mean_zpt_array.clear();
    uparaz_correction.clear();
    ut_correction.clear();
    zpt_correction.clear();
    
    InitArray( mean_uparaz_array , n_zpt_bins_fine );
    InitArray( mean_uparaz_norms , n_zpt_bins_fine );
    InitArray( mean_ut_array , n_zpt_bins_fine );
    InitArray( mean_zpt_array , n_zpt_bins_fine );
    InitArray( uparaz_correction , n_zpt_bins_fine );
    InitArray( ut_correction , n_zpt_bins_fine );
    InitArray( zpt_correction , n_zpt_bins_fine );
}

void RecoilMap::InitArrays()
{
  zpt_true_array.clear();
  zpt_smeared_array.clear();
  zpt_unfolded_array.clear();
  zpt_test_array.clear();
  eff_zpt.clear();
  InitArray( zpt_true_array , n_zpt_bins_fine );
  InitArray( zpt_smeared_array , n_zpt_bins_fine );
  InitArray( zpt_unfolded_array , n_zpt_bins_fine );
  InitArray( zpt_test_array , n_zpt_bins_fine );
  InitArray( eff_zpt , n_zpt_bins_fine );

  zpt_zphi_true_array.clear();
  zpt_zphi_smeared_array.clear();
  zpt_zphi_unfolded_array.clear();
  zpt_zphi_test_array.clear();
  eff_zpt_zphi.clear();
  InitArray( zpt_zphi_true_array , n_zpt_bins , n_zphi_bins );
  InitArray( zpt_zphi_smeared_array , n_zpt_bins , n_zphi_bins );
  InitArray( zpt_zphi_unfolded_array , n_zpt_bins , n_zphi_bins );
  InitArray( zpt_zphi_test_array , n_zpt_bins , n_zphi_bins );
  InitArray( eff_zpt_zphi , n_zpt_bins , n_zphi_bins );
}

void RecoilMap::InitMap()
{
  zpt_map.clear();
  zpt_zphi_map.clear();
  InitArray( zpt_map , n_zpt_bins_fine , n_zpt_bins_fine );
  InitArray( zpt_zphi_map , n_zpt_bins , n_zphi_bins , n_zpt_bins , n_zphi_bins );
  InitInvMap();
}

void RecoilMap::InitInvMap()
{
  zpt_inv_map.clear();
  zpt_zphi_inv_map.clear();
  InitArray( zpt_inv_map , n_zpt_bins_fine , n_zpt_bins_fine );
  InitArray( zpt_zphi_inv_map , n_zpt_bins , n_zphi_bins , n_zpt_bins , n_zphi_bins );
}

bool RecoilMap::FillZPTArray( RecoilFile & inp )
{
  if( zpt_true_array.size() == 0 || zpt_zphi_true_array.size() == 0 )
  {
    InitArrays();
  }

  float smr_norm = 0;
  float gen_norm = 0;
  while( inp.GetNextEvent() )
  {
    int zpt_gen_bin = GetZPT_true_bin( inp );
    int zpt_smr_bin = GetZPT_smeared_bin( inp );

    int zpt_gen_bin_fine = GetZPT_true_bin( inp , true );
    int zpt_smr_bin_fine = GetZPT_smeared_bin( inp , true );
    
    int zphi_gen_bin = GetZPhi_gen_bin( inp );
    int zphi_smr_bin = GetZPhi_smeared_bin( inp );
    
    double evtwgt = inp.recoil_data.eventweight;
    
    if( zpt_smr_bin_fine >= 0 && zpt_smr_bin_fine < n_zpt_bins_fine 
       && zpt_smr_bin >= 0 && zpt_smr_bin < n_zpt_bins
       && zphi_smr_bin >= 0 && zphi_smr_bin < n_zphi_bins )
    {
      zpt_smeared_array[zpt_gen_bin_fine] += evtwgt;
      zpt_zphi_smeared_array[zpt_smr_bin][zphi_smr_bin] += evtwgt;
      smr_norm += inp.recoil_data.eventweight;
      if( zpt_gen_bin_fine >= 0 && zpt_gen_bin_fine < n_zpt_bins_fine 
          && zpt_gen_bin >= 0 && zpt_gen_bin < n_zpt_bins 
          && zphi_gen_bin >= 0 && zphi_gen_bin < n_zphi_bins )
      {
        zpt_true_array[zpt_gen_bin_fine] += evtwgt;
        zpt_zphi_true_array[zpt_gen_bin][zphi_gen_bin] += evtwgt;
        gen_norm += inp.recoil_data.eventweight;
      }
    }
  }

  normalize_vec( zpt_smeared_array , smr_norm );
  normalize_vec( zpt_zphi_smeared_array , smr_norm );
  normalize_vec( zpt_true_array , gen_norm );
  normalize_vec( zpt_zphi_true_array , gen_norm );

  return true;
}

bool RecoilMap::FillZPTMap( RecoilFile & inp )
{
  if( zpt_map.size() == 0 || zpt_zphi_map.size() == 0 )
    InitMap();

  int number_of_events = 0;
  while( inp.GetNextEvent() )
  {
    int zdphi_bin = GetDPhi_gen_smeared_bin( inp );

    int zphi_gen_bin = GetZPhi_gen_bin( inp );
    int zphi_smr_bin = GetZPhi_smeared_bin( inp );

    int zpt_gen_bin = GetZPT_true_bin( inp );
    int zpt_smr_bin = GetZPT_smeared_bin( inp );

    int zpt_gen_bin_fine = GetZPT_true_bin( inp , true );
    int zpt_smr_bin_fine = GetZPT_smeared_bin( inp , true );

    double evtwgt = inp.recoil_data.eventweight;

    if( zpt_gen_bin_fine >= 0 && zpt_gen_bin_fine < n_zpt_bins_fine 
       && zpt_smr_bin_fine >= 0 && zpt_smr_bin_fine < n_zpt_bins_fine
       && zpt_gen_bin >= 0 && zpt_gen_bin < n_zpt_bins 
       && zpt_smr_bin >= 0 && zpt_smr_bin < n_zpt_bins
       && zphi_gen_bin >= 0 && zphi_gen_bin < n_zphi_bins
       && zphi_smr_bin >= 0 && zphi_smr_bin < n_zphi_bins )
    {
      mean_uparaz_array[zpt_gen_bin] += ( inp.Recoil * inp.ZpT_gen / inp.ZpT_gen.Mod() ) * evtwgt;
      mean_uparaz_norms[zpt_gen_bin] += evtwgt;
      mean_ut_array[zpt_gen_bin] += inp.Recoil.Mod() * evtwgt;
      zpt_map[zpt_smr_bin_fine][zpt_gen_bin_fine] += evtwgt;
      zpt_inv_map[zpt_gen_bin_fine][zpt_smr_bin_fine] += evtwgt;
      /// Z Phi
      zpt_zphi_map[zpt_smr_bin][zphi_smr_bin][zpt_gen_bin][zphi_gen_bin] += evtwgt;
      zpt_zphi_inv_map[zpt_gen_bin][zphi_gen_bin][zpt_smr_bin][zphi_smr_bin] += evtwgt;
//       zpt_zphi_map[zpt_smr_bin][zdphi_bin][zpt_gen_bin][0] += evtwgt;
//       zpt_zphi_inv_map[zpt_gen_bin][zdphi_bin][zpt_smr_bin][0] += evtwgt;
      if( number_of_events % 100000 == 0 )
        cout << " number map events " << number_of_events << endl;
      number_of_events++;
    }
    else
    {
      cout << " no bin "  << n_zpt_bins << " " << n_zphi_bins << " " << zpt_gen_bin << " " << zpt_smr_bin << " " << zphi_gen_bin << " " << zphi_smr_bin << endl;
    }
  }
  cout << " number of events " << number_of_events << endl;

  return true;
}

bool RecoilMap::NormalizeZPTMap()
{
  if( zpt_true_array.size() == 0 || zpt_zphi_true_array.size() == 0 )
    InitArrays();

  float zpt_norm = 0;
  for( int i = 0 ; i < n_zpt_bins_fine ; i++ )
  {
    if( fabs(mean_uparaz_norms[i]) > 0 )
    {
      mean_uparaz_array[i] /= mean_uparaz_norms[i];
      mean_ut_array[i] /= mean_uparaz_norms[i];
    }
    else
    {
      mean_uparaz_array[i] = 0;
    }
    zpt_true_array[i] = 0;
    zpt_smeared_array[i] = 0;
    for( int j = 0 ; j < n_zpt_bins_fine ; j++ )
    {
      zpt_true_array[i] += zpt_inv_map[i][j];
      zpt_smeared_array[i] += zpt_map[i][j];
      zpt_norm += zpt_map[i][j];
    }
  }
  for( int i = 0 ; i < n_zpt_bins_fine ; i++ )
  {
    for( int j = 0 ; j < n_zpt_bins_fine ; j++ )
    {
      if( zpt_true_array[j] > 0 )
        zpt_map[i][j] /= zpt_true_array[j];
      else
        zpt_map[i][j] = 0;
      if( zpt_smeared_array[i] > 0 )
        zpt_inv_map[j][i] /= zpt_smeared_array[i];
      else
        zpt_inv_map[j][i] = 0;
    }
  }

  for( int i = 0 ; i < n_zpt_bins ; i++ )
  {
    for( int j = 0 ; j < n_zphi_bins ; j++ )
    {
      zpt_zphi_true_array[i][j] = 0;
      zpt_zphi_smeared_array[i][j] = 0;
      for( int k = 0 ; k < n_zpt_bins ; k++ )
      {
        for( int l = 0 ; l < n_zphi_bins ; l++ )
        {
          zpt_zphi_true_array[i][j] += zpt_zphi_inv_map[i][j][k][l];
          zpt_zphi_smeared_array[i][j] += zpt_zphi_map[i][j][k][l];
        }
      }
    }
  }
  for( int i = 0 ; i < n_zpt_bins ; i++ )
  {
    for( int j = 0 ; j < n_zphi_bins ; j++ )
    {
      for( int k = 0 ; k < n_zpt_bins ; k++ )
      {
        for( int l = 0 ; l < n_zphi_bins ; l++ )
        {
          if( zpt_zphi_true_array[k][l] > 0 )
            zpt_zphi_map[i][j][k][l] /= zpt_zphi_true_array[k][l];
          else
            zpt_zphi_map[i][j][k][l] = 0;
          if( zpt_zphi_smeared_array[i][j] > 0 )
            zpt_zphi_inv_map[k][l][i][j] /= zpt_zphi_smeared_array[i][j];
          else
            zpt_zphi_inv_map[k][l][i][j] = 0;
        }
      }
    }
  }

  normalize_vec( zpt_true_array , zpt_norm );
  normalize_vec( zpt_smeared_array , zpt_norm );
  normalize_vec( zpt_zphi_true_array , zpt_norm );
  normalize_vec( zpt_zphi_smeared_array , zpt_norm );

  for( int i = 0 ; i < n_zpt_bins_fine ; i++ )
  {
    double zpt_center = zpt_bin_edges[i];
    if( i != n_zpt_bins_fine - 1 && fabs( zpt_true_array[i+1] - zpt_true_array[i] ) > 0)
    {
      double a = ( zpt_true_array[i+1] - zpt_true_array[i] ) / zpt_bin_deltas[i];
      double b = zpt_true_array[i] - a * zpt_center;
      double dbar = ( zpt_true_array[i+1] + zpt_true_array[i] ) / 2.;
      zpt_center = ( dbar - b ) / a;
    }
    mean_zpt_array[i] = zpt_center;
  }

  return true;
}

bool RecoilMap::GetZPTUnf()
{
  if( zpt_smeared_array.size() == 0 || zpt_inv_map.size() == 0 )
  {
    cout << " no smeared array! " << endl;
    return false;
  }
  for( int i = 0 ; i < n_zpt_bins_fine ; i++ )
  {
    zpt_unfolded_array[i] = 0;
  }
  for( int i = 0 ; i < n_zpt_bins ; i++ )
  {
    for( int j = 0 ; j < n_zphi_bins ; j++ )
      zpt_zphi_unfolded_array[i][j] = 0;
  }
  for( int i = 0 ; i < n_zpt_bins_fine ; i++ )
  {
    for( int j = 0 ; j < n_zpt_bins_fine ; j++ )
    {
      zpt_unfolded_array[i] += zpt_inv_map[i][j] * zpt_smeared_array[j];
    }
  }
  for( int i = 0 ; i < n_zpt_bins ; i++ )
  {
    for( int j = 0 ; j < n_zphi_bins ; j++ )
    {
      for( int k = 0 ; k < n_zpt_bins ; k++ )
      {
        for( int l = 0 ; l < n_zphi_bins ; l++ )
        {
          zpt_zphi_unfolded_array[i][j] += zpt_zphi_inv_map[i][j][k][l] * zpt_zphi_smeared_array[k][l];
//           zpt_zphi_unfolded_array[i][j] += zpt_zphi_inv_map[i][j][k][0] * zpt_zphi_smeared_array[k][l];
        }
      }
    }
  }
  return true;
}

bool RecoilMap::GetBayesInv()
{
  for( int i = 0 ; i < n_zpt_bins_fine ; i++ )
  {
    zpt_test_array[i] = 0;
    for( int k = 0 ; k < n_zpt_bins_fine ; k++ )
    {
      zpt_test_array[i] += zpt_map[i][k] * zpt_unfolded_array[k];
    }
  }
  for( int i = 0 ; i < n_zpt_bins_fine ; i++ )
  {
    for( int j = 0 ; j < n_zpt_bins_fine ; j++ )
    {
      if( zpt_test_array[i] > 0 )
        zpt_inv_map[j][i] = zpt_map[i][j] * zpt_unfolded_array[j] / zpt_test_array[i];
      else
      {
        cout << " zpt_test_array[" << i << "] " << zpt_test_array[i] << endl;
        zpt_inv_map[j][i] = 0;
      }
    }
  }
  for( int j = 0 ; j < n_zpt_bins_fine ; j++ )
  {
    zpt_test_array[j] = 0;
    for( int i = 0 ; i < n_zpt_bins_fine ; i++ )
    {
      zpt_test_array[j] += zpt_inv_map[j][i] * zpt_smeared_array[i];
    }
  }
  cout << " test distribution " << endl;
  for( int i = 0 ; i < n_zpt_bins_fine ; i++ )
  {
    cout << i << " " << zpt_smeared_array[i] << " " << zpt_test_array[i] << " " << zpt_unfolded_array[i] << " " << zpt_test_array[i] - zpt_unfolded_array[i] << endl;
  }
  
  for( int i = 0 ; i < n_zpt_bins ; i++ )
  {
    for( int j = 0 ; j < n_zphi_bins ; j++ )
    {
      zpt_zphi_test_array[i][j] = 0;
      for( int m = 0 ; m < n_zpt_bins ; m++ )
      {
        for( int n = 0 ; n < n_zphi_bins ; n++ )
        {
          zpt_zphi_test_array[i][j] += zpt_zphi_map[i][j][m][n] * zpt_zphi_unfolded_array[m][n];
        }
      }
    }
  }
  for( int i = 0 ; i < n_zpt_bins ; i++ )
  {
    for( int j = 0 ; j < n_zphi_bins ; j++ )
    {
      for( int k = 0 ; k < n_zpt_bins ; k++ )
      {
        for( int l = 0 ; l < n_zphi_bins ; l++ )
        {
          if( zpt_zphi_test_array[i][j] > 0 )
            zpt_zphi_inv_map[k][l][i][j] = zpt_zphi_map[i][j][k][l] * zpt_zphi_unfolded_array[k][l] / zpt_zphi_test_array[i][j];
          else
            zpt_zphi_inv_map[k][l][i][j] = 0;
        }
      }
    }
  }
  for( int k = 0 ; k < n_zpt_bins ; k++ )
  {
    for( int l = 0 ; l < n_zphi_bins ; l++ )
    {
      zpt_zphi_test_array[k][l] = 0;
      for( int i = 0 ; i < n_zpt_bins ; i++ )
      {
        for( int j = 0 ; j < n_zphi_bins ; j++ )
        {
          zpt_zphi_test_array[k][l] += zpt_zphi_inv_map[k][l][i][j] * zpt_zphi_smeared_array[i][j];
        }
      }
    }
  }
  cout << " test distribution " << endl;
  for( int i = 0 ; i < n_zpt_bins ; i++ )
  {
    for( int j = 0 ; j < n_zphi_bins ; j++ )
    {
      cout << i << " " << j << " " << zpt_zphi_smeared_array[i][j] << " " << zpt_zphi_test_array[i][j] << " " << zpt_zphi_unfolded_array[i][j] << " " << zpt_zphi_test_array[i][j] - zpt_zphi_unfolded_array[i][j] << endl;
    }
  }
}

bool RecoilMap::RunClosureTest()
{
    float total = 0 , total_true = 0 , total_unfolded = 0 , total_closure = 0;
  for( int i = 0 ; i < zpt_smeared_array.size() ; i++ )
  {
    float smeared_closure = 0;
    for( int j = 0 ; j < n_zpt_bins ; j++ )
    {
       smeared_closure += zpt_map[i][j] * zpt_true_array[j];
    }
    float phi_map_closure = 0;
    float phi_map_unfolded = 0;

    cout << " bin " << i << " " << zpt_bin_edges[i] << " " << zpt_smeared_array[i] << " " << zpt_true_array[i] << " ";
    cout << "closure " << smeared_closure << " " << zpt_unfolded_array[i] << " " ;
    cout << phi_map_closure << " " << phi_map_unfolded << " ";
    cout << "f_badness " << ( smeared_closure - zpt_smeared_array[i] ) / zpt_smeared_array[i] << " ";
    cout << ( zpt_unfolded_array[i] - zpt_true_array[i] ) / zpt_true_array[i] << " ";
    cout << ( phi_map_closure - zpt_smeared_array[i] ) / zpt_smeared_array[i] << " ";
    cout << ( phi_map_unfolded - zpt_true_array[i] ) / zpt_true_array[i] << " ";
    cout << endl;
    total += zpt_smeared_array[i];
    
    total_true += zpt_true_array[i];
    total_closure += smeared_closure;
    total_unfolded += zpt_unfolded_array[i];
  }
  cout << " total " << total << " " << total_true << " " << total_closure << " " << total_unfolded << endl;
  return true;
}

bool RecoilMap::WriteMap( vector<float> & vec , TString filename ) {
  ofstream outfile( filename.Data() );
  for( int i = 0 ; i < vec.size() ; i++ )
  {
    float value = vec[i];
    if( fabs(value) > 0 )
      outfile << i << " " << value << endl;
  }
}

bool RecoilMap::WriteMap( vector<vector<float> > & vec , TString filename ) {
  ofstream outfile( filename.Data() );
  for( int i = 0 ; i < vec.size() ; i++ )
  {
    for( int j = 0 ; j < vec[i].size() ; j++ )
    {
      float value = vec[i][j];
      if( fabs(value) > 0 )
        outfile << i << " " << j << " " << value << endl;
    }
  }
}

bool RecoilMap::WriteMap( vector<vector<vector<vector<float> > > > & vec , TString filename ) {
  ofstream outfile( filename.Data() );
  for( int i = 0 ; i < vec.size() ; i++ )
  {
    for( int j = 0 ; j < vec[i].size() ; j++ )
    {
      for( int k = 0 ; k < vec[i][j].size() ; k++ )
      {
        for( int l = 0 ; l < vec[i][j][k].size() ; l++ )
        {
          float value = vec[i][j][k][l];
          if( fabs(value) > 0 )
            outfile << i << " " << j << " " << k << " " << l << " " << value << endl;
        }
      }
    }
  }
  outfile.close();
}

bool RecoilMap::WriteMap( vector<vector<vector<vector<vector<vector<vector<vector<float> > > > > > > > & vec , TString filename ) {
  ofstream outfile( filename.Data() );
  for( int i = 0 ; i < vec.size() ; i++ )
  {
    for( int j = 0 ; j < vec[i].size() ; j++ )
    {
      for( int k = 0 ; k < vec[i][j].size() ; k++ )
      {
        for( int l = 0 ; l < vec[i][j][k].size() ; l++ )
        {
          for( int a = 0 ; a < vec[i][j][k][l].size() ; a++ )
          {
            for( int b = 0 ; b < vec[i][j][k][l][a].size() ; b++ )
            {
              for( int c = 0 ; c < vec[i][j][k][l][a][b].size() ; c++ )
              {
                for( int d = 0 ; d < vec[i][j][k][l][a][b][c].size() ; d++ )
                {
                  float value = vec[i][j][k][l][a][b][c][d];
                  if( fabs(value) > 0 )
                    outfile << i << " " << j << " " << k << " " << l << " " << a << " " << b << " " << c << " " << d << " " << value << endl;
                }
              }
            }
          }
        }
      }
    }
  }
  outfile.close();
}

bool RecoilMap::WriteZPTMap() {
  WriteMap( zpt_map );
  return WriteMap( zpt_zphi_map );
}

bool RecoilMap::WriteZPTInvMap() {
  WriteMap( mean_uparaz_array , "uparaz_means.txt" );
  WriteMap( mean_ut_array , "ut_means.txt" );
  WriteMap( mean_zpt_array , "zpt_means.txt" );
  WriteMap( zpt_inv_map , "zpt_map_matrix_inv.txt" );
  return WriteMap( zpt_zphi_inv_map , "map_matrix_inv.txt" );
}

bool RecoilMap::ReadMap( vector<float> & vec , TString filename ) {
  ifstream infile( filename.Data() );
  int i;
  float value;
  string s;

  while(getline(infile,s))
  {
    istringstream line(s);
    line >> i >> value;
    if( i < vec.size() && fabs(value) > 0 )
    {
      vec[i] = value;
    }
    else
    {
      TString output;
      output.Form( "%i %i %i" , i , vec.size() , value );
      cout << output << endl;
      return false;
    }
  }
  return true;
}

bool RecoilMap::ReadMap( vector<vector<float> > & vec , TString filename ) {
  ifstream infile( filename.Data() );
  int i , j;
  float value;
  string s;

  while(getline(infile,s))
  {
    istringstream line(s);
    line >> i >> j >> value;
    if( i < vec.size() && j < vec[i].size() && fabs(value) > 0 )
    {
      vec[i][j] = value;
    }
    else
    {
      TString output;
      output.Form( "%i %i %i %i %i" , i , vec.size() , j , vec[i].size() , value );
      cout << output << endl;
      return false;
    }
  }
  return true;
}

bool RecoilMap::ReadMap( vector<vector<vector<vector<float> > > > & vec , TString filename ) {
  ifstream infile( filename.Data() );
  int i , j , k , l;
  float value;
  string s;

  while(getline(infile,s))
  {
    istringstream line(s);
    line >> i >> j >> k >> l >> value;
    if( i < vec.size() && j < vec[i].size() && k < vec[i][j].size() && l < vec[i][j][k].size() && fabs(value) > 0 )
    {
      vec[i][j][k][l] = value;
    }
    else
    {
      TString output;
      output.Form( "%i %i %i %i %i %i %i %i %i" , i , vec.size() , j , vec[i].size() , k , vec[i][j].size() , l , vec[i][j][k].size() , value );
      cout << output << endl;
      return false;
    }
  }
  return true;
}

bool RecoilMap::ReadMap( vector<vector<vector<vector<vector<vector<vector<vector<float> > > > > > > > & vec , TString filename ) {
  ifstream infile( filename.Data() );
  int i , j , k , l , a , b, c , d;
  float value;
  string s;

  while(getline(infile,s))
  {
    istringstream line(s);
    line >> i >> j >> k >> l >> a >> b >> c >> d >> value;
    if( i < vec.size() && j < vec[i].size() 
      && k < vec[i][j].size() && l < vec[i][j][k].size() 
      && a < vec[i][j][k][l].size() && b < vec[i][j][k][l][a].size()
      && c < vec[i][j][k][l][a][b].size() && d < vec[i][j][k][l][a][b][c].size()
      && fabs(value) > 0 )
    {
      vec[i][j][k][l][a][b][c][d] = value;
    }
    else
    {
      TString output;
      output.Form( "%i %i %i %i %i %i %i %i %i" , i , vec.size() , j , vec[i].size() , k , vec[i][j].size() , l , vec[i][j][k].size() , value );
      cout << output << endl;
      return false;
    }
  }
  return true;
}

bool RecoilMap::ReadZPTMap() {
  ReadMap( zpt_map , "zpt_map_matrix.txt" );
  return ReadMap( zpt_zphi_map , "map_matrix.txt" );
}

bool RecoilMap::ReadZPTInvMap() {
  ReadMap( mean_uparaz_array , "uparaz_means.txt" );
  ReadMap( mean_ut_array , "ut_means.txt" );
  ReadMap( mean_zpt_array , "zpt_means.txt" );
  ReadMap( zpt_inv_map , "zpt_map_matrix_inv.txt" );
  return ReadMap( zpt_zphi_inv_map , "map_matrix_inv.txt" );
}

bool RecoilMap::ReadCorrection() {
  ReadMap( uparaz_correction , "uparaz_correction.txt" );
  ReadMap( ut_correction , "ut_correction.txt" );
  return ReadMap( zpt_correction , "zpt_correction.txt" );
}
