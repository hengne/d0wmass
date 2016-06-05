#include "RecoilLibrary.hpp"

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

void RecoilLibrary::InitHistograms( RecoilMap & genmap , bool do_control_test )
{
  if( !do_control_test )
  {
    recoil_file = new TFile( "recoil_file.root" , "recreate" );

    InstLumi_WZ_orig = new TH1F( "InstLumi_WZ_orig" , "InstLumi_WZ_orig", 150 , 0. , 15.0 );
    SET_WZ_orig = new TH1F( "SET_WZ_orig" , "SET_WZ_orig" , 600 , 0 , 600 );

    InstLumi_WZ = new TH1F( "InstLumi_WZ" , "InstLumi_WZ", 150 , 0. , 15.0 );
    RunNo_WZ = new TH1F( "RunNo_WZ" , "RunNo_WZ" , 30890 , 222027.5 , 252918.5 );
    SET_WZ = new TH1F( "SET_WZ" , "SET_WZ" , 600 , 0 , 600 );

    ut_means = new TGraph();
    uparaz_means = new TGraph();
    zpt_means = new TGraph();
    SetGraphNameTitle( ut_means , "ut_means" , "Mean of UT per zpt bin" );
    SetGraphNameTitle( uparaz_means , "uparaz_means" , "Mean of UparaZ per zpt bin" );
    SetGraphNameTitle( zpt_means , "zpt_means" , "Mean of ZPT per bin" );
    for( int i = 0 ; i < genmap.n_zpt_bins_fine ; i++ )
    {
      double zpt_center = genmap.zpt_bin_edges_fine[i] + genmap.zpt_bin_deltas_fine[i]/2.;
      ut_means->SetPoint( i , zpt_center , genmap.mean_ut_array[i] );
      uparaz_means->SetPoint( i , zpt_center , genmap.mean_uparaz_array[i] );
      zpt_means->SetPoint( i , genmap.zpt_bin_edges_fine[i] , genmap.mean_zpt_array[i] );
    }
    ut_means->Write();
    uparaz_means->Write();
  }
  else
  {
    recoil_file = new TFile( "recoil_file.root" , "read" );

    InstLumi_WZ_orig = (TH1F*) recoil_file->Get( "InstLumi_WZ_orig" );
    SET_WZ_orig = (TH1F*) recoil_file->Get( "SET_WZ_orig" );

    InstLumi_WZ = (TH1F*) recoil_file->Get( "InstLumi_WZ" );
    RunNo_WZ = (TH1F*) recoil_file->Get( "RunNo_WZ" );
    SET_WZ = (TH1F*) recoil_file->Get( "SET_WZ" );

    ut_means = (TGraph*) recoil_file->Get( "ut_means" );
    uparaz_means = (TGraph*) recoil_file->Get( "uparaz_means" );
    zpt_means = (TGraph*) recoil_file->Get( "zpt_means" );
  }

  control_file = new TFile( "control_file.root" , "recreate" );

  zpt_gen_hist = new TH1F( "zpt_gen_hist" , "zpt_gen_hist" , genmap.n_zpt_bins_fine , genmap.get_pt_bins_fine() );
  zpt_unf_hist = new TH1F( "zpt_unf_hist" , "zpt_unf_hist" , genmap.n_zpt_bins_fine , genmap.get_pt_bins_fine() );
  zpt_smr_hist = new TH1F( "zpt_smr_hist" , "zpt_smr_hist" , genmap.n_zpt_bins_fine , genmap.get_pt_bins_fine() );
  zpt_gen_hist->Sumw2();
  zpt_unf_hist->Sumw2();
  zpt_smr_hist->Sumw2();
  
  ut_gen_hist = new TH1F( "ut_gen_hist" , "ut_gen_hist" , genmap.n_zpt_bins_fine , genmap.get_pt_bins_fine() );
  ut_unf_hist = new TH1F( "ut_unf_hist" , "ut_unf_hist" , genmap.n_zpt_bins_fine , genmap.get_pt_bins_fine() );
  ut_smr_hist = new TH1F( "ut_smr_hist" , "ut_smr_hist" , genmap.n_zpt_bins_fine , genmap.get_pt_bins_fine() );
  ut_gen_hist->Sumw2();
  ut_unf_hist->Sumw2();
  ut_smr_hist->Sumw2();

  uphi_gen_hist = new TH1F( "uphi_gen_hist" , "uphi_gen_hist" , 64 , 0 , 2*TMath::Pi() );
  uphi_unf_hist = new TH1F( "uphi_unf_hist" , "uphi_unf_hist" , 64 , 0 , 2*TMath::Pi() );
  uphi_smr_hist = new TH1F( "uphi_smr_hist" , "uphi_smr_hist" , 64 , 0 , 2*TMath::Pi() );
  uphi_gen_hist->Sumw2();
  uphi_unf_hist->Sumw2();
  uphi_smr_hist->Sumw2();
  
  int nzpt = genmap.n_zpt_bins;
  int nzphi = genmap.n_zphi_bins;
  for( int i = 0 ; i < nzpt ; i++ )
  {
    TString zdphi_gen_smr_hist_name;
    zdphi_gen_smr_hist_name.Form( "zdphi_gen_smr_hist_%i" , i );
    zdphi_gen_smr_hist.push_back( new TH1F( zdphi_gen_smr_hist_name , zdphi_gen_smr_hist_name , 64 , -TMath::Pi() , TMath::Pi() ) );
    
    TString ut_gen_hists_name , ut_unf_hists_name , ut_smr_hists_name;
    ut_gen_hists_name.Form( "ut_gen_hist_%i" , i );
    ut_unf_hists_name.Form( "ut_unf_hist_%i" , i );
    ut_smr_hists_name.Form( "ut_smr_hist_%i" , i );
    ut_gen_hists.push_back( new TH1F( ut_gen_hists_name , ut_gen_hists_name , n_recoil_bin_array , genmap.get_recoil_bins() ) );
    ut_unf_hists.push_back( new TH1F( ut_unf_hists_name , ut_unf_hists_name , n_recoil_bin_array , genmap.get_recoil_bins() ) );
    ut_smr_hists.push_back( new TH1F( ut_smr_hists_name , ut_smr_hists_name , n_recoil_bin_array , genmap.get_recoil_bins() ) );

    TString uparaz_gen_hists_name , uparaz_unf_hists_name , uparaz_smr_hists_name;
    uparaz_gen_hists_name.Form( "uparaz_gen_hist_%i" , i );
    uparaz_unf_hists_name.Form( "uparaz_unf_hist_%i" , i );
    uparaz_smr_hists_name.Form( "uparaz_smr_hist_%i" , i );
    uparaz_gen_hists.push_back( new TH1F( uparaz_gen_hists_name , uparaz_gen_hists_name , n_recoil_bin_array , genmap.get_recoil_bins() ) );
    uparaz_unf_hists.push_back( new TH1F( uparaz_unf_hists_name , uparaz_unf_hists_name , n_recoil_bin_array , genmap.get_recoil_bins() ) );
    uparaz_smr_hists.push_back( new TH1F( uparaz_smr_hists_name , uparaz_smr_hists_name , n_recoil_bin_array , genmap.get_recoil_bins() ) );

    TString uperpz_gen_hists_name , uperpz_unf_hists_name , uperpz_smr_hists_name;
    uperpz_gen_hists_name.Form( "uperpz_gen_hist_%i" , i );
    uperpz_unf_hists_name.Form( "uperpz_unf_hist_%i" , i );
    uperpz_smr_hists_name.Form( "uperpz_smr_hist_%i" , i );
    uperpz_gen_hists.push_back( new TH1F( uperpz_gen_hists_name , uperpz_gen_hists_name , n_recoil_bin_array , genmap.get_recoil_bins() ) );
    uperpz_unf_hists.push_back( new TH1F( uperpz_unf_hists_name , uperpz_unf_hists_name , n_recoil_bin_array , genmap.get_recoil_bins() ) );
    uperpz_smr_hists.push_back( new TH1F( uperpz_smr_hists_name , uperpz_smr_hists_name , n_recoil_bin_array , genmap.get_recoil_bins() ) );
    
    TString udphi_gen_hists_name , udphi_unf_hists_name , udphi_smr_hists_name;
    udphi_gen_hists_name.Form( "udphi_gen_hist_%i" , i );
    udphi_unf_hists_name.Form( "udphi_unf_hist_%i" , i );
    udphi_smr_hists_name.Form( "udphi_smr_hist_%i" , i );
    udphi_gen_hists.push_back( new TH1F( udphi_gen_hists_name , udphi_gen_hists_name , 64 , 0 , 2*TMath::Pi() ) );
    udphi_unf_hists.push_back( new TH1F( udphi_unf_hists_name , udphi_unf_hists_name , 64 , 0 , 2*TMath::Pi() ) );
    udphi_smr_hists.push_back( new TH1F( udphi_smr_hists_name , udphi_smr_hists_name , 64 , 0 , 2*TMath::Pi() ) );    
  }
  
  for( int i = 0 ; i < nzphi ; i++ )
  {
    TString uphi_gen_hists_name , uphi_unf_hists_name , uphi_smr_hists_name;
    uphi_gen_hists_name.Form( "uphi_gen_hist_%i" , i );
    uphi_unf_hists_name.Form( "uphi_unf_hist_%i" , i );
    uphi_smr_hists_name.Form( "uphi_smr_hist_%i" , i );
    uphi_gen_hists.push_back( new TH1F( uphi_gen_hists_name , uphi_gen_hists_name , 64 , 0 , 2*TMath::Pi() ) );
    uphi_unf_hists.push_back( new TH1F( uphi_unf_hists_name , uphi_unf_hists_name , 64 , 0 , 2*TMath::Pi() ) );
    uphi_smr_hists.push_back( new TH1F( uphi_smr_hists_name , uphi_smr_hists_name , 64 , 0 , 2*TMath::Pi() ) );    
  }
  
  if( !do_control_test )
  {
    for( int i = 0 ; i < nzpt ; i++ )
    {
      vector<TH2F*> temp_recoil_unf_hists;
      for( int j = 0 ; j < nzphi ; j++ )
      {
        TString recoil_unf_hist_name;
        recoil_unf_hist_name.Form( "rec_unf_hist_%i_%i" , i , j );
        int nx = 100 , ny = 100;
        double xmin = -30 , xmax = 30;
        double ymin = -30 , ymax = 30;
        if( ux_uy_flag == 0 )
          temp_recoil_unf_hists.push_back( new TH2F( recoil_unf_hist_name , recoil_unf_hist_name , nx , xmin , xmax , ny , ymin , ymax ) );
        if( ux_uy_flag == 1 )
        {
          nx = 100 ; xmin = -30 ; xmax = 30;
          ny = 100 ; ymin = -30 ; ymax = 30;
          temp_recoil_unf_hists.push_back( new TH2F( recoil_unf_hist_name , recoil_unf_hist_name , n_recoil_bin_array , genmap.get_recoil_bins() , n_recoil_bin_array , genmap.get_recoil_bins() ) );
        }
        else if( ux_uy_flag == 2 )
        {
          nx = 150 ; xmin = -30 ; xmax = 30;
          ny = genmap.n_zphi_bins ; ymin = 0 ; ymax = 2 * TMath::Pi();
          temp_recoil_unf_hists.push_back( new TH2F( recoil_unf_hist_name , recoil_unf_hist_name , n_recoil_bin_array , genmap.get_recoil_bins() , ny , ymin , ymax ) );
        }
        else if( ux_uy_flag == 3 )
        {
          nx = 150 ; xmin = -30 ; xmax = 30;
          ny = genmap.n_zphi_bins ; ymin = 0 ; ymax = 2 * TMath::Pi();
          temp_recoil_unf_hists.push_back( new TH2F( recoil_unf_hist_name , recoil_unf_hist_name , n_recoil_bin_array , genmap.get_recoil_bins() , ny , ymin , ymax ) );        
        }
      }
      recoil_unf_hists.push_back( temp_recoil_unf_hists );
    }
    recoil_file->cd();
    for( int i = 0 ; i < nzpt ; i++ )
    {
      TString set_gen_hist_name , set_unf_hist_name , set_smr_hist_name;
      set_gen_hist_name.Form( "set_gen_hist_%i" , i );
      set_unf_hist_name.Form( "set_unf_hist_%i" , i );
      set_smr_hist_name.Form( "set_smr_hist_%i" , i );
      set_gen_hists.push_back( new TH1F( set_gen_hist_name , set_gen_hist_name , 600 , 0 , 600 ) );
      set_unf_hists.push_back( new TH1F( set_unf_hist_name , set_unf_hist_name , 600 , 0 , 600 ) );
      set_smr_hists.push_back( new TH1F( set_smr_hist_name , set_smr_hist_name , 600 , 0 , 600 ) );
    }
  }
  else
  {
    recoil_file->cd();
    InitTH2F( recoil_unf_hists , nzpt , nzphi );
    InitTH1F( set_gen_hists , nzpt );
    InitTH1F( set_unf_hists , nzpt );
    InitTH1F( set_smr_hists , nzpt );
    for( int i = 0 ; i < nzpt ; i++ )
    {
      for( int j = 0 ; j < nzphi ; j++ )
      {
        TString recoil_unf_hist_name;
        if( !use_inverse_probs )
          recoil_unf_hist_name.Form( "int_rec_unf_hist_%i_%i" , i , j );
        else
          recoil_unf_hist_name.Form( "int2_rec_unf_hist_%i_%i" , i , j );
        recoil_unf_hists[i][j] = (TH2F*) recoil_file->Get( recoil_unf_hist_name );
      }
      TString set_gen_hist_name , set_unf_hist_name , set_smr_hist_name;
      set_gen_hist_name.Form( "set_gen_hist_%i" , i );
      set_unf_hist_name.Form( "set_unf_hist_%i" , i );
      set_smr_hist_name.Form( "set_smr_hist_%i" , i );
      set_gen_hists[i] = (TH1F*) recoil_file->Get( set_gen_hist_name );
      set_unf_hists[i] = (TH1F*) recoil_file->Get( set_unf_hist_name );
      set_smr_hists[i] = (TH1F*) recoil_file->Get( set_smr_hist_name );
    }
  }
}

void RecoilLibrary::FillHistograms( RecoilFile & inp , RecoilMap & genmap , bool do_control_test )
{
  int number_of_events = 0;
  
  while( inp.GetNextEvent() )
  {
    int zpt_gen_bin = genmap.GetZPT_true_bin( inp );
    int zphi_gen_bin = genmap.GetZPhi_gen_bin( inp );
    int zpt_smr_bin = genmap.GetZPT_smeared_bin( inp );
    int zphi_smr_bin = genmap.GetZPhi_smeared_bin( inp );
    
    double evtwgt = inp.recoil_data.eventweight;

    double recx = inp.recoil_data.recoil_x;
    double recy = inp.recoil_data.recoil_y;
    double set = inp.recoil_data.scalarET;

    double ut = inp.Recoil.Mod();
    double uphi = inp.Recoil.Phi_0_2pi( inp.Recoil.Phi() );

    double ptz_gen = inp.ZpT_gen.Mod() , ptz_smr = inp.ZpT_smeared.Mod();
    double ptz_x_gen_hat = inp.ZpT_gen.X()/ptz_gen , ptz_y_gen_hat = inp.ZpT_gen.Y()/ptz_gen;
    double ptz_x_smr_hat = inp.ZpT_smeared.X()/ptz_smr , ptz_y_smr_hat = inp.ZpT_smeared.Y()/ptz_smr;
    
    double uparaz_gen = recx * ptz_x_gen_hat + recy * ptz_y_gen_hat;
    double uperpz_gen = recx * ptz_y_gen_hat - recy * ptz_x_gen_hat;

    double uparaz_smr = recx * ptz_x_smr_hat + recy * ptz_y_smr_hat;
    double uperpz_smr = recx * ptz_y_smr_hat - recy * ptz_x_smr_hat;
    
//     double uphi_center_gen = genmap.zphi_bin_edges[zphi_gen_bin] + genmap.zphi_bin_deltas[zphi_gen_bin]/2.;
//     uphi_center_gen = inp.Recoil.Phi_0_2pi( uphi - uphi_center_gen );
//     double uphi_center_smr = genmap.zphi_bin_edges[zphi_smr_bin] + genmap.zphi_bin_deltas[zphi_smr_bin]/2.;
//     uphi_center_smr = inp.Recoil.Phi_0_2pi( uphi - uphi_center_smr );
    
    double uphi_center_gen = inp.Recoil.Phi_0_2pi( uphi - inp.ZpT_gen.Phi() );
    double uphi_center_smr = inp.Recoil.Phi_0_2pi( uphi - inp.ZpT_smeared.Phi() );
    
    int rec_bin = genmap.GetUT_bin( inp );
    int rphi_gen_bin = genmap.get_bin( uphi_center_gen , genmap.zphi_bin_edges );
    int rphi_smr_bin = genmap.get_bin( uphi_center_smr , genmap.zphi_bin_edges );
    
    double setwgt = inp.CalcSETEfficiency( set , inp.recoil_data.lumi , inp.recoil_data.pT_e1 , inp.recoil_data.pT_e2 , inp.recoil_data.eta_e1 , inp.recoil_data.eta_e2 );
    double uparwgt = inp.CalcUparaEfficiency( inp.recoil_data.upara_e1 , inp.recoil_data.upara_e2 );
    
//     use_set_upar_wgts = false;
    if( !use_set_upar_wgts ) {
    setwgt = 1 ; uparwgt = 1;
    }
    if( setwgt < 0.2 ) setwgt = 0.2;
    if( uparwgt < 0.2 ) uparwgt = 0.2;
    
    ut_gen_hists[zpt_gen_bin]->Fill( ut - ut_means->GetY()[zpt_gen_bin] , evtwgt );
    ut_smr_hists[zpt_smr_bin]->Fill( ut - ut_means->GetY()[zpt_smr_bin] , evtwgt );

    ut_gen_hist->Fill( ut , evtwgt );
    ut_smr_hist->Fill( ut , evtwgt );
    
    uphi_gen_hist->Fill( uphi_center_gen , evtwgt );
    uphi_smr_hist->Fill( uphi_center_smr , evtwgt );
    
    uparaz_gen_hists[zpt_gen_bin]->Fill( uparaz_gen - uparaz_means->GetY()[zpt_gen_bin] , evtwgt );
    uparaz_smr_hists[zpt_smr_bin]->Fill( uparaz_smr - uparaz_means->GetY()[zpt_smr_bin] , evtwgt );

    uperpz_gen_hists[zpt_gen_bin]->Fill( uperpz_gen , evtwgt );
    uperpz_smr_hists[zpt_smr_bin]->Fill( uperpz_smr , evtwgt );

    uphi_gen_hists[zphi_gen_bin]->Fill( uphi_center_gen , evtwgt );
    uphi_smr_hists[zphi_smr_bin]->Fill( uphi_center_smr , evtwgt );

    udphi_gen_hists[zpt_gen_bin]->Fill( uphi_center_gen , evtwgt );
    udphi_smr_hists[zpt_smr_bin]->Fill( uphi_center_smr , evtwgt );
    
    set_gen_hists[zpt_gen_bin]->Fill( set , evtwgt );
    set_smr_hists[zpt_smr_bin]->Fill( set , evtwgt );

    zpt_gen_hist->Fill( inp.ZpT_gen.Mod() , evtwgt );
    zpt_smr_hist->Fill( inp.ZpT_smeared.Mod() , evtwgt );
    
    zdphi_gen_smr_hist[zpt_gen_bin]->Fill( inp.ZpT_gen.DeltaPhi( inp.ZpT_smeared ) );
    
    if( !do_control_test )
    {
      if( genmap.zpt_zphi_inv_map.size() > 0 )
      {
        for( int k = 0 ; k < genmap.n_zpt_bins ; k++ )
        {
          double zpt_center = zpt_means->GetX()[k];
          for( int l = 0 ; l < genmap.n_zphi_bins ; l++ )
          {
            double unfold_wgt = genmap.zpt_zphi_inv_map[k][l][zpt_smr_bin][zphi_smr_bin] * evtwgt / setwgt / uparwgt;
            if( unfold_wgt > 0 )
            {
              double zphi_center = genmap.zphi_bin_edges[l] + genmap.zphi_bin_deltas[l]/2.;
              double ptz_x_unf_hat = cos( zphi_center );
              double ptz_y_unf_hat = sin( zphi_center );
              
              double uparaz_unf = recx * ptz_x_unf_hat + recy * ptz_y_unf_hat;
              double uperpz_unf = recx * ptz_y_unf_hat - recy * ptz_x_unf_hat;

              double uphi_center_unf = inp.Recoil.Phi_0_2pi( uphi - zphi_center );
              
              double ut_residual_val = 0.1305 - 0.0357 * zpt_center;
              if( zpt_center > 40. ) ut_residual_val = 0;

              if( ux_uy_flag == 0 )
                recoil_unf_hists[k][l]->Fill( recx , recy , unfold_wgt );
              else if( ux_uy_flag == 1 )
                recoil_unf_hists[k][l]->Fill( uparaz_unf - uparaz_means->GetY()[k] , uperpz_unf , unfold_wgt );
              else if( ux_uy_flag == 2 )
                recoil_unf_hists[k][l]->Fill( ut - ut_means->GetY()[k] - ut_residual_val , uphi_center_unf , unfold_wgt );            
              else if( ux_uy_flag == 3 )
                recoil_unf_hists[k][l]->Fill( ut - ut_means->GetY()[k] , uphi , unfold_wgt );
              
              set_unf_hists[k]->Fill( set , unfold_wgt );
              zpt_unf_hist->Fill( zpt_center , unfold_wgt );
              ut_unf_hists[k]->Fill( ut - ut_means->GetY()[k] , unfold_wgt );
              
              ut_unf_hist->Fill( ut , unfold_wgt );
              
              uphi_unf_hist->Fill( uphi_center_unf , unfold_wgt );
              
              uparaz_unf_hists[k]->Fill( uparaz_unf - uparaz_means->GetY()[k] , unfold_wgt );
              uperpz_unf_hists[k]->Fill( uperpz_unf , unfold_wgt );
              
              uphi_unf_hists[l]->Fill( uphi_center_unf , unfold_wgt );
              udphi_unf_hists[k]->Fill( uphi_center_unf , unfold_wgt );
              
              InstLumi_WZ->Fill( inp.recoil_data.lumi , unfold_wgt );
              RunNo_WZ->Fill( inp.recoil_data.runno , unfold_wgt );
              SET_WZ->Fill( inp.recoil_data.scalarET , unfold_wgt );
            }
          }
        }
      }
    }
    else
    {
      double zpt_center = inp.ZpT_gen.Mod();
      double zphi_center = inp.ZpT_gen.Phi();
      double ptz_x_unf_hat = cos( zphi_center );
      double ptz_y_unf_hat = sin( zphi_center );
      
      double ux_unf , uy_unf;
      double ut_unf , uphi_unf;
      
      double temprecx , temprecy;
      if( recoil_unf_hists[zpt_gen_bin][zphi_gen_bin] )
      {
        double rand0 = dummy->Rndm();
        double rand1 = dummy->Rndm();
        double rand2 = dummy->Rndm();
        int binx , biny;
        binary_search( recoil_unf_hists[zpt_gen_bin][zphi_gen_bin] , rand0 , binx , biny , use_inverse_probs );
        double x0 = recoil_unf_hists[zpt_gen_bin][zphi_gen_bin]->GetXaxis()->GetBinLowEdge( binx );
        double x1 = x0+recoil_unf_hists[zpt_gen_bin][zphi_gen_bin]->GetXaxis()->GetBinWidth( binx );
        double y0 = recoil_unf_hists[zpt_gen_bin][zphi_gen_bin]->GetYaxis()->GetBinLowEdge( biny );
        double y1 = y0+recoil_unf_hists[zpt_gen_bin][zphi_gen_bin]->GetYaxis()->GetBinWidth( biny );
        double d0 = recoil_unf_hists[zpt_gen_bin][zphi_gen_bin]->GetBinContent( binx , biny );
        temprecx = x0;
        temprecy = y0;
        if( !use_inverse_probs )
        {
          if( biny < recoil_unf_hists[zpt_gen_bin][zphi_gen_bin]->GetNbinsY() )
            biny += 1;
          double d1 = recoil_unf_hists[zpt_gen_bin][zphi_gen_bin]->GetBinContent( binx , biny );
          temprecx += rand1 * ( x1 - x0 );
          if( d1 - d0 > 0 )
            temprecy += ( rand0 - d0 ) / ( d1 - d0 ) * ( y1 - y0 );
          else
            temprecy += rand2 * ( y1 - y0 );
        }
        else
        {
          if( binx < recoil_unf_hists[zpt_gen_bin][zphi_gen_bin]->GetNbinsX() )
            binx += 1;
          double d1 = recoil_unf_hists[zpt_gen_bin][zphi_gen_bin]->GetBinContent( binx , biny );
          if( d1 - d0 > 0 )
            temprecx += ( rand0 - d0 ) / ( d1 - d0 ) * ( x1 - x0 );
          else
            temprecx += rand2 * ( y1 - y0 );
          temprecy += rand1 * ( y1 - y0 );
        }
      }
      else
        cout << "no recoil " << temprecx << " " << temprecy << endl;
      
      if( ux_uy_flag == 0 )
      {
        /// ux uy
        ux_unf = temprecx ;
        uy_unf = temprecy ;
        ut_unf = sqrt( ux_unf*ux_unf + uy_unf*uy_unf );
        uphi_unf = atan2( uy_unf , ux_unf );
      }
      else if( ux_uy_flag == 1 )
      {
        /// uparaz, uperpz
        temprecx += uparaz_means->GetY()[zpt_gen_bin];
        ux_unf = (temprecx * inp.ZpT_gen.X() + temprecy * inp.ZpT_gen.Y())/inp.ZpT_gen.Mod();
        uy_unf = (temprecx * inp.ZpT_gen.Y() - temprecy * inp.ZpT_gen.X())/inp.ZpT_gen.Mod();
        ut_unf = sqrt( ux_unf*ux_unf + uy_unf*uy_unf );
        uphi_unf = atan2( uy_unf , ux_unf );
      }
      else if( ux_uy_flag == 2 )
      {
        /// ut uphi
        double ut_val = temprecx + ut_means->GetY()[zpt_gen_bin];
        int _num_recoil_phi_bins = genmap.zphi_bin_edges.size();
        double uphi_val = temprecy + genmap.zphi_bin_edges[zphi_gen_bin] + TMath::Pi() / _num_recoil_phi_bins;
        ux_unf = ut_val * cos( uphi_val );
        uy_unf = ut_val * sin( uphi_val );  
        ut_unf = sqrt( ux_unf*ux_unf + uy_unf*uy_unf );
        uphi_unf = atan2( uy_unf , ux_unf );
      }
      else if( ux_uy_flag == 3 )
      {
        /// ut uphi
        double ut_val = temprecx + ut_means->GetY()[zpt_gen_bin];
        int _num_recoil_phi_bins = genmap.zphi_bin_edges.size();
        double uphi_val = temprecy;
        ux_unf = ut_val * cos( uphi_val );
        uy_unf = ut_val * sin( uphi_val );  
        ut_unf = sqrt( ux_unf*ux_unf + uy_unf*uy_unf );
        uphi_unf = atan2( uy_unf , ux_unf );
      }

      double uparaz_unf = ux_unf * ptz_x_unf_hat + uy_unf * ptz_y_unf_hat;
      double uperpz_unf = ux_unf * ptz_y_unf_hat - uy_unf * ptz_x_unf_hat;

      double uphi_center_unf = inp.Recoil.Phi_0_2pi( uphi_unf - zphi_center );
      
      set_unf_hists[zpt_gen_bin]->Fill( set , evtwgt );
      zpt_unf_hist->Fill( zpt_center , evtwgt );
      ut_unf_hists[zpt_gen_bin]->Fill( ut_unf - ut_means->GetY()[zpt_gen_bin] , evtwgt );
      
      ut_unf_hist->Fill( ut_unf , evtwgt );
      
      uphi_unf_hist->Fill( uphi_center_unf , evtwgt );
      
      uparaz_unf_hists[zpt_gen_bin]->Fill( uparaz_unf - uparaz_means->GetY()[zpt_gen_bin] , evtwgt );
      uperpz_unf_hists[zpt_gen_bin]->Fill( uperpz_unf , evtwgt );
      
      uphi_unf_hists[zphi_gen_bin]->Fill( uphi_center_unf , evtwgt );
      udphi_unf_hists[zpt_gen_bin]->Fill( uphi_center_unf , evtwgt );
      
      InstLumi_WZ->Fill( inp.recoil_data.lumi , evtwgt );
      RunNo_WZ->Fill( inp.recoil_data.runno , evtwgt );
      SET_WZ->Fill( inp.recoil_data.scalarET , evtwgt );
    }

    InstLumi_WZ_orig->Fill( inp.recoil_data.lumi , evtwgt );
    SET_WZ_orig->Fill( inp.recoil_data.scalarET , evtwgt );

    if( ( number_of_events % 10000 ) == 0 )
      cout << " processed " << number_of_events << endl;
    number_of_events++;
  }
  cout << " number of events " << number_of_events << endl;
  
  normalize_hist_var_bin( zpt_gen_hist );
  normalize_hist_var_bin( zpt_unf_hist );
  normalize_hist_var_bin( zpt_smr_hist );

  normalize_hist_var_bin( ut_gen_hist );
  normalize_hist_var_bin( ut_unf_hist );
  normalize_hist_var_bin( ut_smr_hist );

  GetGraphs( genmap );
  
  for( int i = 0 ; i < genmap.n_zpt_bins ; i++ )
  {
    normalize_hist( zdphi_gen_smr_hist[i] );
    normalize_hist_var_bin( ut_gen_hists[i] );
    normalize_hist_var_bin( ut_unf_hists[i] );
    normalize_hist_var_bin( ut_smr_hists[i] );
    normalize_hist( udphi_gen_hists[i] );
    normalize_hist( udphi_unf_hists[i] );
    normalize_hist( udphi_smr_hists[i] );

    normalize_hist_var_bin( uparaz_gen_hists[i] ); 
    normalize_hist_var_bin( uparaz_unf_hists[i] );
    normalize_hist_var_bin( uparaz_smr_hists[i] );
    normalize_hist_var_bin( uperpz_gen_hists[i] );
    normalize_hist_var_bin( uperpz_unf_hists[i] ); 
    normalize_hist_var_bin( uperpz_smr_hists[i] );
  }
  for( int i = 0 ; i < genmap.n_zphi_bins ; i++ )
  {
    normalize_hist( uphi_gen_hists[i] );
    normalize_hist( uphi_unf_hists[i] ); 
    normalize_hist( uphi_smr_hists[i] );
  }

  if( !do_control_test )
  {
    recoil_file->cd();
    
    for( int i = 0 ; i < genmap.n_zpt_bins ; i++ )
    {
      for( int j = 0 ; j < genmap.n_zphi_bins ; j++ )
      {
        normalize_hist( recoil_unf_hists[i][j] );
        
        TString temp_name;
        float hist_integral = 0;
        if( !use_inverse_probs )
        {
          temp_name.Form( "%s_%s" , "int" , recoil_unf_hists[i][j]->GetName() );
          TH2F * recoil_unf_integrals = (TH2F*) recoil_unf_hists[i][j]->Clone( temp_name.Data() );      
          recoil_unf_integrals->SetBinContent( 0 , 0 , hist_integral );
          for( int k = 0 ; k <= recoil_unf_integrals->GetNbinsX() ; k++ )
          {
            for( int l = 0 ; l <= recoil_unf_integrals->GetNbinsY() ; l++ )
            {
              recoil_unf_integrals->SetBinContent( k+1 , l+1 , hist_integral );
              hist_integral += recoil_unf_hists[i][j]->GetBinContent( k+1 , l+1 );
            }
          }
          recoil_unf_integrals->Write();
          delete recoil_unf_integrals;
        }
        else
        {
          temp_name.Form( "%s_%s" , "int2" , recoil_unf_hists[i][j]->GetName() );
          TH2F * recoil_unf_integrals2 = (TH2F*) recoil_unf_hists[i][j]->Clone( temp_name.Data() );      
          hist_integral = 0;
          recoil_unf_integrals2->SetBinContent( 0 , 0 , hist_integral );
          for( int l = 0 ; l <= recoil_unf_integrals2->GetNbinsY() ; l++ )
          {
            for( int k = 0 ; k <= recoil_unf_integrals2->GetNbinsX() ; k++ )
            {
              recoil_unf_integrals2->SetBinContent( k+1 , l+1 , hist_integral );
              hist_integral += recoil_unf_hists[i][j]->GetBinContent( k+1 , l+1 );
            }
          }
          recoil_unf_integrals2->Write();
          delete recoil_unf_integrals2;
        }
      }
    }

    for( int i = 0 ; i < genmap.n_zpt_bins ; i++ ) // zpt bins 
    {
      for( int u = 0 ; u < genmap.n_zpt_bins ; u++ ) // ut bins
      {
        normalize_hist( set_gen_hists[i] );
        normalize_hist( set_unf_hists[i] );
        normalize_hist( set_smr_hists[i] );     
      }
    }  
    recoil_file->Write();
  }

  control_file->cd();
  control_file->Write();
  DeleteHistos();
}

void RecoilLibrary::GetGraphs( RecoilMap & genmap )
{
  control_file->cd();

  zdphi_means = new TGraphErrors();
  zdphi_widths = new TGraphErrors();
  zpt_residuals = new TGraphErrors();
  ut_residuals = new TGraphErrors();
  uphi_residuals = new TGraphErrors();
  ut_means_gen = new TGraphErrors();
  ut_means_unf = new TGraphErrors();
  ut_means_smr = new TGraphErrors();
  ut_widths_gen = new TGraphErrors();
  ut_widths_unf = new TGraphErrors();
  ut_widths_smr = new TGraphErrors();
  ut_means_residuals = new TGraphErrors();
  ut_widths_residuals = new TGraphErrors();
  uparaz_means_gen = new TGraphErrors();
  uparaz_means_unf = new TGraphErrors();
  uparaz_means_smr = new TGraphErrors();
  uparaz_widths_gen = new TGraphErrors();
  uparaz_widths_unf = new TGraphErrors();
  uparaz_widths_smr = new TGraphErrors();
  uparaz_means_residuals = new TGraphErrors();
  uparaz_widths_residuals = new TGraphErrors();
  uperpz_means_gen = new TGraphErrors();
  uperpz_means_unf = new TGraphErrors();
  uperpz_means_smr = new TGraphErrors();
  uperpz_widths_gen = new TGraphErrors();
  uperpz_widths_unf = new TGraphErrors();
  uperpz_widths_smr = new TGraphErrors();
  uperpz_means_residuals = new TGraphErrors();
  uperpz_widths_residuals = new TGraphErrors();
  uphi_means_gen = new TGraphErrors();
  uphi_means_unf = new TGraphErrors();
  uphi_means_smr = new TGraphErrors();
  uphi_widths_gen = new TGraphErrors();
  uphi_widths_unf = new TGraphErrors();
  uphi_widths_smr = new TGraphErrors();
  uphi_means_residuals = new TGraphErrors();
  uphi_widths_residuals = new TGraphErrors();
  udphi_means_gen = new TGraphErrors();
  udphi_means_unf = new TGraphErrors();
  udphi_means_smr = new TGraphErrors();
  udphi_widths_gen = new TGraphErrors();
  udphi_widths_unf = new TGraphErrors();
  udphi_widths_smr = new TGraphErrors();
  udphi_means_residuals = new TGraphErrors();
  udphi_widths_residuals = new TGraphErrors();
  
  SetGraphNameTitle( zdphi_means , "zdphi_means" , "#Delta#phi_{Z} Means" );
  SetGraphNameTitle( zdphi_widths , "zdphi_widths" , "#Delta#phi_{Z} Widths" );
  SetGraphNameTitle( zpt_residuals , "zpt_residuals" , "p_{T}^{Z}" );
  SetGraphNameTitle( ut_residuals , "ut_residuals" , "U_{T}" );
  SetGraphNameTitle( uphi_residuals , "uphi_residuals" , "#phi_{R}" );
  SetGraphNameTitle( ut_means_gen , "ut_means_gen" , "UT Means" ); 
  SetGraphNameTitle( ut_means_unf , "ut_means_unf" , "UT Means" ); 
  SetGraphNameTitle( ut_means_smr , "ut_means_smr" , "UT Means" ); 
  SetGraphNameTitle( ut_widths_gen , "ut_widths_gen" , "UT Widths" ); 
  SetGraphNameTitle( ut_widths_unf , "ut_widths_unf" , "UT Widths" ); 
  SetGraphNameTitle( ut_widths_smr , "ut_widths_smr" , "UT Widths" ); 
  SetGraphNameTitle( ut_means_residuals , "ut_means_residuals" , "UT Means Residuals" ); 
  SetGraphNameTitle( ut_widths_residuals , "ut_widths_residuals" , "UT Widths Residuals" ); 
  SetGraphNameTitle( uparaz_means_gen , "uparaz_means_gen" , "uparaz Means" ); 
  SetGraphNameTitle( uparaz_means_unf , "uparaz_means_unf" , "uparaz Means" ); 
  SetGraphNameTitle( uparaz_means_smr , "uparaz_means_smr" , "uparaz Means" ); 
  SetGraphNameTitle( uparaz_widths_gen , "uparaz_widths_gen" , "uparaz Widths" ); 
  SetGraphNameTitle( uparaz_widths_unf , "uparaz_widths_unf" , "uparaz Widths" ); 
  SetGraphNameTitle( uparaz_widths_smr , "uparaz_widths_smr" , "uparaz Widths" ); 
  SetGraphNameTitle( uparaz_means_residuals , "uparaz_means_residuals" , "uparaz Means Residuals" ); 
  SetGraphNameTitle( uparaz_widths_residuals , "uparaz_widths_residuals" , "uparaz Widths Residuals" ); 
  SetGraphNameTitle( uperpz_means_gen , "uperpz_means_gen" , "uperpz Means" ); 
  SetGraphNameTitle( uperpz_means_unf , "uperpz_means_unf" , "uperpz Means" ); 
  SetGraphNameTitle( uperpz_means_smr , "uperpz_means_smr" , "uperpz Means" ); 
  SetGraphNameTitle( uperpz_widths_gen , "uperpz_widths_gen" , "uperpz Widths" ); 
  SetGraphNameTitle( uperpz_widths_unf , "uperpz_widths_unf" , "uperpz Widths" ); 
  SetGraphNameTitle( uperpz_widths_smr , "uperpz_widths_smr" , "uperpz Widths" ); 
  SetGraphNameTitle( uperpz_means_residuals , "uperpz_means_residuals" , "uperpz Means Residuals" ); 
  SetGraphNameTitle( uperpz_widths_residuals , "uperpz_widths_residuals" , "uperpz Widths Residuals" ); 
  SetGraphNameTitle( uphi_means_gen , "uphi_means_gen" , "U#phi Means" ); 
  SetGraphNameTitle( uphi_means_unf , "uphi_means_unf" , "U#phi Means" ); 
  SetGraphNameTitle( uphi_means_smr , "uphi_means_smr" , "U#phi Means" ); 
  SetGraphNameTitle( uphi_widths_gen , "uphi_widths_gen" , "U#phi Widths" ); 
  SetGraphNameTitle( uphi_widths_unf , "uphi_widths_unf" , "U#phi Widths" ); 
  SetGraphNameTitle( uphi_widths_smr , "uphi_widths_smr" , "U#phi Widths" ); 
  SetGraphNameTitle( uphi_means_residuals , "uphi_means_residuals" , "uphi Means Residuals" ); 
  SetGraphNameTitle( uphi_widths_residuals , "uphi_widths_residuals" , "uphi Widths Residuals" ); 
  SetGraphNameTitle( udphi_means_gen , "udphi_means_gen" , "U#Delta#phi Means" ); 
  SetGraphNameTitle( udphi_means_unf , "udphi_means_unf" , "U#Delta#phi Means" ); 
  SetGraphNameTitle( udphi_means_smr , "udphi_means_smr" , "U#Delta#phi Means" ); 
  SetGraphNameTitle( udphi_widths_gen , "udphi_widths_gen" , "U#Delta#phi Widths" ); 
  SetGraphNameTitle( udphi_widths_unf , "udphi_widths_unf" , "U#Delta#phi Widths" ); 
  SetGraphNameTitle( udphi_widths_smr , "udphi_widths_smr" , "U#Delta#phi Widths" ); 
  SetGraphNameTitle( udphi_means_residuals , "udphi_means_residuals" , "udphi Means Residuals" ); 
  SetGraphNameTitle( udphi_widths_residuals , "udphi_widths_residuals" , "udphi Widths Residuals" ); 
  
  for( int i = 0 ; i < genmap.n_zpt_bins ; i++ )
  {
    double bin_center = genmap.zpt_bin_edges[i] + genmap.zpt_bin_deltas[i]/2.;
    double bin_width = genmap.zpt_bin_deltas[i]/2.;

    zpt_residuals->SetPoint( i , bin_center , zpt_unf_hist->GetBinContent( i+1 ) - zpt_gen_hist->GetBinContent( i+1 ) );
    zpt_residuals->SetPointError( i , bin_width , zpt_gen_hist->GetBinError( i+1) ); 

    ut_residuals->SetPoint( i , bin_center , ut_unf_hist->GetBinContent( i+1 ) - ut_gen_hist->GetBinContent( i+1 ) );
    ut_residuals->SetPointError( i , bin_width , ut_gen_hist->GetBinError( i+1) );
    
    uphi_residuals->SetPoint( i , bin_center , uphi_unf_hist->GetBinContent( i+1 ) - uphi_gen_hist->GetBinContent( i+1 ) );
    uphi_residuals->SetPointError( i , bin_width , uphi_gen_hist->GetBinError( i+1) );
    
    zdphi_means->SetPoint( i , bin_center , zdphi_gen_smr_hist[i]->GetMean() );
    zdphi_means->SetPointError( i , bin_width , zdphi_gen_smr_hist[i]->GetMeanError() );
    
    zdphi_widths->SetPoint( i , bin_center , zdphi_gen_smr_hist[i]->GetRMS() );
    zdphi_widths->SetPointError( i , bin_width , zdphi_gen_smr_hist[i]->GetRMSError() );
    
    ut_means_gen->SetPoint( i , bin_center , ut_gen_hists[i]->GetMean() );
    ut_means_gen->SetPointError( i , bin_width , ut_gen_hists[i]->GetMeanError() );
    ut_means_unf->SetPoint( i , bin_center , ut_unf_hists[i]->GetMean() );
    ut_means_unf->SetPointError( i , bin_width , ut_unf_hists[i]->GetMeanError() );
    ut_means_smr->SetPoint( i , bin_center , ut_smr_hists[i]->GetMean() );
    ut_means_smr->SetPointError( i , bin_width , ut_smr_hists[i]->GetMeanError() );
    ut_means_residuals->SetPoint( i , bin_center , ut_unf_hists[i]->GetMean() - ut_gen_hists[i]->GetMean() );
    ut_means_residuals->SetPointError( i , bin_width , ut_gen_hists[i]->GetMeanError() );
    
    ut_widths_gen->SetPoint( i , bin_center , ut_gen_hists[i]->GetRMS() );
    ut_widths_gen->SetPointError( i , bin_width , ut_gen_hists[i]->GetRMSError() );
    ut_widths_unf->SetPoint( i , bin_center , ut_unf_hists[i]->GetRMS() );
    ut_widths_unf->SetPointError( i , bin_width , ut_unf_hists[i]->GetRMSError() );
    ut_widths_smr->SetPoint( i , bin_center , ut_smr_hists[i]->GetRMS() );
    ut_widths_smr->SetPointError( i , bin_width , ut_smr_hists[i]->GetRMSError() );    
    ut_widths_residuals->SetPoint( i , bin_center , ut_unf_hists[i]->GetRMS() - ut_gen_hists[i]->GetRMS() );
    ut_widths_residuals->SetPointError( i , bin_width , ut_gen_hists[i]->GetRMSError() );
    
    uparaz_means_gen->SetPoint( i , bin_center , uparaz_gen_hists[i]->GetMean() );
    uparaz_means_gen->SetPointError( i , bin_width , uparaz_gen_hists[i]->GetMeanError() );
    uparaz_means_unf->SetPoint( i , bin_center , uparaz_unf_hists[i]->GetMean() );
    uparaz_means_unf->SetPointError( i , bin_width , uparaz_unf_hists[i]->GetMeanError() );
    uparaz_means_smr->SetPoint( i , bin_center , uparaz_smr_hists[i]->GetMean() );
    uparaz_means_smr->SetPointError( i , bin_width , uparaz_smr_hists[i]->GetMeanError() );
    uparaz_means_residuals->SetPoint( i , bin_center , uparaz_unf_hists[i]->GetMean() - uparaz_gen_hists[i]->GetMean() );
    uparaz_means_residuals->SetPointError( i , bin_width , uparaz_gen_hists[i]->GetMeanError() );
    
    uparaz_widths_gen->SetPoint( i , bin_center , uparaz_gen_hists[i]->GetRMS() );
    uparaz_widths_gen->SetPointError( i , bin_width , uparaz_gen_hists[i]->GetRMSError() );
    uparaz_widths_unf->SetPoint( i , bin_center , uparaz_unf_hists[i]->GetRMS() );
    uparaz_widths_unf->SetPointError( i , bin_width , uparaz_unf_hists[i]->GetRMSError() );
    uparaz_widths_smr->SetPoint( i , bin_center , uparaz_smr_hists[i]->GetRMS() );
    uparaz_widths_smr->SetPointError( i , bin_width , uparaz_smr_hists[i]->GetRMSError() );    
    uparaz_widths_residuals->SetPoint( i , bin_center , uparaz_unf_hists[i]->GetRMS() - uparaz_gen_hists[i]->GetRMS() );
    uparaz_widths_residuals->SetPointError( i , bin_width , uparaz_gen_hists[i]->GetRMSError() );

    uperpz_means_gen->SetPoint( i , bin_center , uperpz_gen_hists[i]->GetMean() );
    uperpz_means_gen->SetPointError( i , bin_width , uperpz_gen_hists[i]->GetMeanError() );
    uperpz_means_unf->SetPoint( i , bin_center , uperpz_unf_hists[i]->GetMean() );
    uperpz_means_unf->SetPointError( i , bin_width , uperpz_unf_hists[i]->GetMeanError() );
    uperpz_means_smr->SetPoint( i , bin_center , uperpz_smr_hists[i]->GetMean() );
    uperpz_means_smr->SetPointError( i , bin_width , uperpz_smr_hists[i]->GetMeanError() );
    uperpz_means_residuals->SetPoint( i , bin_center , uperpz_unf_hists[i]->GetMean() - uperpz_gen_hists[i]->GetMean() );
    uperpz_means_residuals->SetPointError( i , bin_width , uperpz_gen_hists[i]->GetMeanError() );
    
    uperpz_widths_gen->SetPoint( i , bin_center , uperpz_gen_hists[i]->GetRMS() );
    uperpz_widths_gen->SetPointError( i , bin_width , uperpz_gen_hists[i]->GetRMSError() );
    uperpz_widths_unf->SetPoint( i , bin_center , uperpz_unf_hists[i]->GetRMS() );
    uperpz_widths_unf->SetPointError( i , bin_width , uperpz_unf_hists[i]->GetRMSError() );
    uperpz_widths_smr->SetPoint( i , bin_center , uperpz_smr_hists[i]->GetRMS() );
    uperpz_widths_smr->SetPointError( i , bin_width , uperpz_smr_hists[i]->GetRMSError() );    
    uperpz_widths_residuals->SetPoint( i , bin_center , uperpz_unf_hists[i]->GetRMS() - uperpz_gen_hists[i]->GetRMS() );
    uperpz_widths_residuals->SetPointError( i , bin_width , uperpz_gen_hists[i]->GetRMSError() );

    udphi_means_gen->SetPoint( i , bin_center , udphi_gen_hists[i]->GetMean() );
    udphi_means_gen->SetPointError( i , bin_width , udphi_gen_hists[i]->GetMeanError() );
    udphi_means_unf->SetPoint( i , bin_center , udphi_unf_hists[i]->GetMean() );
    udphi_means_unf->SetPointError( i , bin_width , udphi_unf_hists[i]->GetMeanError() );
    udphi_means_smr->SetPoint( i , bin_center , udphi_smr_hists[i]->GetMean() );
    udphi_means_smr->SetPointError( i , bin_width , udphi_smr_hists[i]->GetMeanError() );
    udphi_means_residuals->SetPoint( i , bin_center , udphi_unf_hists[i]->GetMean() - udphi_gen_hists[i]->GetMean() );
    udphi_means_residuals->SetPointError( i , bin_width , udphi_gen_hists[i]->GetMeanError() );

    udphi_widths_gen->SetPoint( i , bin_center , udphi_gen_hists[i]->GetRMS() );
    udphi_widths_gen->SetPointError( i , bin_width , udphi_gen_hists[i]->GetRMSError() );
    udphi_widths_unf->SetPoint( i , bin_center , udphi_unf_hists[i]->GetRMS() );
    udphi_widths_unf->SetPointError( i , bin_width , udphi_unf_hists[i]->GetRMSError() );
    udphi_widths_smr->SetPoint( i , bin_center , udphi_smr_hists[i]->GetRMS() );
    udphi_widths_smr->SetPointError( i , bin_width , udphi_smr_hists[i]->GetRMSError() );
    udphi_widths_residuals->SetPoint( i , bin_center , udphi_unf_hists[i]->GetRMS() - udphi_gen_hists[i]->GetRMS() );
    udphi_widths_residuals->SetPointError( i , bin_width , udphi_gen_hists[i]->GetRMSError() );
  }
  zpt_residuals->Write();

  ut_residuals->Write();
  uphi_residuals->Write();

  zdphi_means->Write();
  zdphi_widths->Write();
  
  ut_means_gen->Write();
  ut_means_unf->Write();
  ut_means_smr->Write();
  ut_means_residuals->Write();
  
  ut_widths_gen->Write();
  ut_widths_unf->Write();
  ut_widths_smr->Write();
  ut_widths_residuals->Write();
  
  uparaz_means_gen->Write();
  uparaz_means_unf->Write();
  uparaz_means_smr->Write();
  uparaz_means_residuals->Write();

  uparaz_widths_gen->Write();
  uparaz_widths_unf->Write();
  uparaz_widths_smr->Write();
  uparaz_widths_residuals->Write();

  uperpz_means_gen->Write();
  uperpz_means_unf->Write();
  uperpz_means_smr->Write();
  uperpz_means_residuals->Write();

  uperpz_widths_gen->Write();
  uperpz_widths_unf->Write();
  uperpz_widths_smr->Write();
  uperpz_widths_residuals->Write();

  udphi_means_gen->Write();
  udphi_means_unf->Write();
  udphi_means_smr->Write();
  udphi_means_residuals->Write();

  udphi_widths_gen->Write();
  udphi_widths_unf->Write();
  udphi_widths_smr->Write();
  udphi_widths_residuals->Write();

  for( int i = 0 ; i < genmap.n_zphi_bins ; i++ )
  {
    double bin_center = genmap.zphi_bin_edges[i] + genmap.zphi_bin_deltas[i]/2.;
    double bin_width = genmap.zphi_bin_deltas[i]/2.;
    
    uphi_means_gen->SetPoint( i , bin_center , uphi_gen_hists[i]->GetMean() );
    uphi_means_gen->SetPointError( i , bin_width , uphi_gen_hists[i]->GetMeanError() );
    uphi_means_unf->SetPoint( i , bin_center , uphi_unf_hists[i]->GetMean() );
    uphi_means_unf->SetPointError( i , bin_width , uphi_unf_hists[i]->GetMeanError() );
    uphi_means_smr->SetPoint( i , bin_center , uphi_smr_hists[i]->GetMean() );
    uphi_means_smr->SetPointError( i , bin_width , uphi_smr_hists[i]->GetMeanError() );
    uphi_means_residuals->SetPoint( i , bin_center , uphi_unf_hists[i]->GetMean() - uphi_gen_hists[i]->GetMean() );
    uphi_means_residuals->SetPointError( i , bin_width , uphi_gen_hists[i]->GetMeanError() );

    uphi_widths_gen->SetPoint( i , bin_center , uphi_gen_hists[i]->GetRMS() );
    uphi_widths_gen->SetPointError( i , bin_width , uphi_gen_hists[i]->GetRMSError() );
    uphi_widths_unf->SetPoint( i , bin_center , uphi_unf_hists[i]->GetRMS() );
    uphi_widths_unf->SetPointError( i , bin_width , uphi_unf_hists[i]->GetRMSError() );
    uphi_widths_smr->SetPoint( i , bin_center , uphi_smr_hists[i]->GetRMS() );
    uphi_widths_smr->SetPointError( i , bin_width , uphi_smr_hists[i]->GetRMSError() );
    uphi_widths_residuals->SetPoint( i , bin_center , uphi_unf_hists[i]->GetRMS() - uphi_gen_hists[i]->GetRMS() );
    uphi_widths_residuals->SetPointError( i , bin_width , uphi_gen_hists[i]->GetRMSError() );
  }
  uphi_means_gen->Write();
  uphi_means_unf->Write();
  uphi_means_smr->Write();
  uphi_means_residuals->Write();

  uphi_widths_gen->Write();
  uphi_widths_unf->Write();
  uphi_widths_smr->Write();
  uphi_widths_residuals->Write();
  
  recoil_file->cd();
}
