#include <iostream>
#include <fstream>
#include <stdlib.h>  //atoi
#include <unistd.h>  //getopt

#include "RecoilFile.hpp"
#include "RecoilMap.hpp"
#include "RecoilLibrary.hpp"
#include "TString.h"

int main( int argc , char** argv ) {

  TString recoil_filename( "file.list" );
  int events_to_run_over = -1;
  bool convert_ascii_file = false;
  bool make_map = false;
  bool iterate_map = false;
  bool run_unfolding = false;
  bool do_selections = true;
  int ux_uy_flag = 0;
  bool use_fine_zpt_bins = true;
  bool use_set_upar_wgts = false;
  bool do_control_test = false;
  
  int c;
  while( (c=getopt(argc,argv,"hn:f:c:s:t:w:")) != -1 ){
    switch(c){
    case 'h':
      std::cout << "Usage: " << argv[0] << 
        " [-h] [-f <recoil_file_list>] [-n <number_of_events>] [-c <command>] [-s <do event selections>] [-t 0=uxuy, 1=uparuperp, 2=utuphi] [-w do set/upar wgts]" << std::endl;
      exit(0);
      break;
    case 'f':
      recoil_filename = optarg;
      break;
    case 'n':
      events_to_run_over = atoi(optarg);
      break;
    case 'c':
      if( TString(optarg) == "convert" )
        convert_ascii_file = true;
      if( TString(optarg).Contains( "map" ) )
        make_map = true;
      if( TString(optarg) == "iterate" )
        iterate_map = true;
      if( TString(optarg) == "unfold" )
        run_unfolding = true;
      if( TString(optarg) == "control_test" )
        do_control_test = true;
      break;
    case 's':
      if( atoi(optarg) == 1 ) do_selections = false;
      break;
    case 't':
      ux_uy_flag = atoi(optarg);
      break;
    case 'w':
      if( atoi(optarg) == 1 ) use_set_upar_wgts = true;
      break;
    }
  }

  if( convert_ascii_file )
  {
    cout << " convert ascii file " << recoil_filename << endl;
    RecoilFile recfile;
    recfile.DoSelections( do_selections );
    
    recfile.ConvertAsciiFile( recoil_filename , "temp_recoil.root" , 1 );
    
    return 1;
  }

  RecoilFile recfile( recoil_filename );
  recfile.DoSelections( do_selections );
  recfile.SetNumberOfEvents( events_to_run_over );

  RecoilMap recmap(use_fine_zpt_bins);

  if( make_map )
  {
    cout << " creating map, map file  " << recoil_filename << endl;
    recmap.FillZPTMap( recfile );
    cout << " normalize maps " << endl;
    recmap.NormalizeZPTMap();  
    cout << " writing map file " << endl;
    recmap.WriteZPTMap();
    cout << " writing inverted map " << endl;
    recmap.WriteZPTInvMap();
    return 1;
  }

  cout << " run unfolding, recoil file " << recoil_filename << endl;

  RecoilLibrary reclib(ux_uy_flag,use_set_upar_wgts);

  cout << " init histograms " << endl;
  if( iterate_map )
  {
    cout << " init arrays " << endl;
    recmap.InitArrays();
    recmap.FillZPTArray(recfile);
    cout << " init map " << endl;
    recmap.InitMap();
    cout << " read map " << endl;
    recmap.ReadZPTMap();
    cout << " read inv map " << endl;
    recmap.ReadZPTInvMap();
    cout << " get initial unf dist " << endl;
    recmap.GetZPTUnf();
    cout << " get iterated dist " << endl;
    recmap.GetBayesInv();
    return 1;
  }
  if( run_unfolding )
  {
    cout << " init map " << endl;
    recmap.InitInvMap();
    cout << " read inv matrix " << endl;
    recmap.ReadZPTInvMap();
    cout << " fill histograms " << endl;
    reclib.InitHistograms( recmap );
    reclib.FillHistograms( recfile , recmap );
  }
  if( do_control_test )
  {
    cout << " fill histograms " << endl;
    reclib.InitHistograms( recmap , do_control_test);
    reclib.FillHistograms( recfile , recmap , do_control_test );
  }
  
  return 1;
};

