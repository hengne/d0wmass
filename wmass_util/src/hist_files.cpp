#include <iostream>
#include <utility>
#include <string.h>
#include <vector>    // for std::vector
#include <map>       // for std::map
#include <algorithm> // for std::find

#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"

#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "cafe/Processor.hpp"

#include "wmass_util/hist_files.hpp"

using std::cout;
using std::endl;
using std::flush;
using std::make_pair;
using std::string;
using std::find;
using std::map;
using std::vector;
using namespace histfiles;
using namespace cafe;

// constructor
hist_files::hist_files() {}

// destructor
hist_files::~hist_files() {

  for(map<TString, TH1D*>::iterator it_1d = hist_files_1d.begin(); 
      it_1d != hist_files_1d.end(); it_1d++) {
    delete (*it_1d).second;
  }
  
  for(map<TString, TH2D*>::iterator it_2d = hist_files_2d.begin();
      it_2d != hist_files_2d.end(); it_2d++) {
    delete (*it_2d).second;
  }

  for(map<TString, TH3D*>::iterator it_3d = hist_files_3d.begin();
      it_3d != hist_files_3d.end(); it_3d++) {
    delete (*it_3d).second;
  }
  
  for(map<TString, TProfile*>::iterator it_profile = hist_files_profile.begin();
      it_profile != hist_files_profile.end(); it_profile++) {
    delete (*it_profile).second;
  }
  
  for(map<TString, TProfile2D*>::iterator it_profile_2d = hist_files_profile_2d.begin();
      it_profile_2d != hist_files_profile_2d.end(); it_profile_2d++) {
    delete (*it_profile_2d).second;
  }
  
}

/////////////////////////////////////////////////
////       Check for duplicate names          ///
/////////////////////////////////////////////////
bool hist_files::check_name(TString hist_name) {
  bool result=false;
  if(hist_files_1d.find(hist_name)==hist_files_1d.end() &&
     hist_files_2d.find(hist_name)==hist_files_2d.end() &&
     hist_files_3d.find(hist_name)==hist_files_3d.end() &&
     hist_files_profile.find(hist_name)==hist_files_profile.end() &&
     hist_files_profile_2d.find(hist_name)==hist_files_profile_2d.end() ) {
    //    cout<<"No such histogram as "<<hist_name<<endl;
    result=false;
  } else {
    //    cout<<"Histogram name "<<hist_name<<" already exists"<<endl;
    result=true;
  }
  return result;
}

/////////////////////////////////////////////////
////         Add Histograms or Profiles       ///
/////////////////////////////////////////////////

// deal with 1D histogram
void hist_files::add(HIST_1D hist_1d) {
  if(hist_1d.name != "" && check_name(hist_1d.name)) {
    cout<<"Name \""<<hist_1d.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_1d.insert(make_pair(hist_1d.name, 
				 new TH1D(hist_1d.name, hist_1d.name,
					  hist_1d.nbin, hist_1d.lower, hist_1d.upper)));
  hist_files_1d[hist_1d.name]->Sumw2();
  hist_files_1d[hist_1d.name]->SetDirectory(0);
}
void hist_files::add( HIST_1D* _hist_1d,TString suffix_name) {
  HIST_1D* hist_1d=_hist_1d;
  while( (*hist_1d).name != "" ) {
    TString holder = (*hist_1d).name;
    (*hist_1d).name+=suffix_name;
    add(*hist_1d);
    (*hist_1d).name=holder;
    ++hist_1d;
  }
}

// deal with 2D histograms
void hist_files::add(HIST_2D hist_2d) {
  if(hist_2d.name != "" && check_name(hist_2d.name)) {
    cout<<"Name \""<<hist_2d.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_2d.insert(make_pair(hist_2d.name,
				 new TH2D(hist_2d.name, hist_2d.name,
					  hist_2d.nbinx, hist_2d.lowerx, hist_2d.upperx,
					  hist_2d.nbiny, hist_2d.lowery, hist_2d.uppery)));
  hist_files_2d[hist_2d.name]->Sumw2();
}
void hist_files::add(HIST_2D* _hist_2d,TString suffix_name) {
  HIST_2D* hist_2d=_hist_2d;
  while( (*hist_2d).name!="" ) {
     TString holder = (*hist_2d).name;
    (*hist_2d).name+=suffix_name;
    add(*hist_2d);
    (*hist_2d).name=holder;
    ++hist_2d;
  }
}

// deal with 3D histograms
void hist_files::add(HIST_3D hist_3d) {
  if(hist_3d.name != "" && check_name(hist_3d.name)) {
    cout<<"Name \""<<hist_3d.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_3d.insert(make_pair(hist_3d.name,
				 new TH3D(hist_3d.name, hist_3d.name,
					  hist_3d.nbinx, hist_3d.lowerx, hist_3d.upperx,
					  hist_3d.nbiny, hist_3d.lowery, hist_3d.uppery,
					  hist_3d.nbinz, hist_3d.lowerz, hist_3d.upperz)));
  hist_files_3d[hist_3d.name]->Sumw2();
}
void hist_files::add(HIST_3D* _hist_3d) {
  HIST_3D* hist_3d=_hist_3d;
  while( (*hist_3d).name!="" ) {
    add(*hist_3d);
    ++hist_3d;
  }
}

// deal with Profile
void hist_files::add(HIST_PROFILE hist_profile) {
  if(hist_profile.name != "" && check_name(hist_profile.name)) {
    cout<<"Name \""<<hist_profile.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_profile.insert(make_pair(hist_profile.name,
				      new TProfile(hist_profile.name, hist_profile.name,
						   hist_profile.nbinx, hist_profile.lowerx, hist_profile.upperx,
						   hist_profile.lowery, hist_profile.uppery, hist_profile.profile_option)));
  hist_files_profile[hist_profile.name]->Sumw2();
}
void hist_files::add(HIST_PROFILE* _hist_profile) {
  HIST_PROFILE* hist_profile=_hist_profile;
  while( (*hist_profile).name!="" ) {
    add(*hist_profile);
    ++hist_profile;
  }
}

// deal with 2D Profile
void hist_files::add(HIST_PROFILE_2D hist_profile_2d) {
  if(hist_profile_2d.name != "" && check_name(hist_profile_2d.name)) {
    cout<<"Name \""<<hist_profile_2d.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_profile_2d.insert(make_pair(hist_profile_2d.name,
					 new TProfile2D(hist_profile_2d.name, hist_profile_2d.name,
							hist_profile_2d.nbinx, hist_profile_2d.lowerx, hist_profile_2d.upperx,
							hist_profile_2d.nbiny, hist_profile_2d.lowery, hist_profile_2d.uppery)));
  if(check_name(hist_profile_2d.name)) {
    hist_files_profile_2d[hist_profile_2d.name]->BuildOptions(hist_profile_2d.lowerz, hist_profile_2d.upperz, hist_profile_2d.profile_option);
    hist_files_profile_2d[hist_profile_2d.name]->Sumw2();
  }
}
void hist_files::add(HIST_PROFILE_2D* _hist_profile_2d) {
  HIST_PROFILE_2D* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name!="" ) {
    add(*hist_profile_2d);
    ++hist_profile_2d;
  }
}

// deal with 1D variable-bin-size histogram 
void hist_files::add(HIST_1D_VARBIN hist_1d) {
  if(hist_1d.name != "" && check_name(hist_1d.name)) {
    cout<<"Name \""<<hist_1d.name<<"\" already exists!"<<endl;
    return;
  }
//   cout << "Adding 1D variable-bin histogram NBINS=" << hist_1d.nbin << ", NAME=" << hist_1d.name << endl;
//   for(Int_t i=0; i<hist_1d.nbin; i++) {
//     cout << "Bin-" << i << " is [" << hist_1d.binx[i] << "," <<  hist_1d.binx[i+1] << "]" << endl;
//   }
  hist_files_1d.insert(make_pair(hist_1d.name, 
				 new TH1D(hist_1d.name, hist_1d.name,
					  hist_1d.nbin, hist_1d.binx)));
  hist_files_1d[hist_1d.name]->Sumw2();
}
void hist_files::add( HIST_1D_VARBIN* _hist_1d) {
  HIST_1D_VARBIN* hist_1d=_hist_1d;
  while( (*hist_1d).name != "" ) {
    add(*hist_1d);
    ++hist_1d;
  }
}
// deal with 2D variable-bin-size histograms (all 3 types: X-only, Y-only, both X&Y)
void hist_files::add(HIST_2D_VARBIN_X hist_2d) {
  if(hist_2d.name != "" && check_name(hist_2d.name)) {
    cout<<"Name \""<<hist_2d.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_2d.insert(make_pair(hist_2d.name,
				 new TH2D(hist_2d.name, hist_2d.name,
					  hist_2d.nbinx, hist_2d.binx,
					  hist_2d.nbiny, hist_2d.lowery, hist_2d.uppery)));
  hist_files_2d[hist_2d.name]->Sumw2();
}
void hist_files::add(HIST_2D_VARBIN_X* _hist_2d) {
  HIST_2D_VARBIN_X* hist_2d=_hist_2d;
  while( (*hist_2d).name!="" ) {
    add(*hist_2d);
    ++hist_2d;
  }
}
void hist_files::add(HIST_2D_VARBIN_Y hist_2d) {
  if(hist_2d.name != "" && check_name(hist_2d.name)) {
    cout<<"Name \""<<hist_2d.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_2d.insert(make_pair(hist_2d.name,
				 new TH2D(hist_2d.name, hist_2d.name,
					  hist_2d.nbinx, hist_2d.lowerx, hist_2d.upperx,
					  hist_2d.nbiny, hist_2d.biny)));
}
void hist_files::add(HIST_2D_VARBIN_Y* _hist_2d) {
  HIST_2D_VARBIN_Y* hist_2d=_hist_2d;
  while( (*hist_2d).name!="" ) {
    add(*hist_2d);
    ++hist_2d;
  }
}
void hist_files::add(HIST_2D_VARBIN_XY hist_2d) {
  if(hist_2d.name != "" && check_name(hist_2d.name)) {
    cout<<"Name \""<<hist_2d.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_2d.insert(make_pair(hist_2d.name,
				 new TH2D(hist_2d.name, hist_2d.name,
					  hist_2d.nbinx, hist_2d.binx,
					  hist_2d.nbiny, hist_2d.biny)));
  hist_files_2d[hist_2d.name]->Sumw2();
}
void hist_files::add(HIST_2D_VARBIN_XY* _hist_2d) {
  HIST_2D_VARBIN_XY* hist_2d=_hist_2d;
  while( (*hist_2d).name!="" ) {
    add(*hist_2d);
    ++hist_2d;
  }
}
// deal with variable-bin-size Profile
void hist_files::add(HIST_PROFILE_VARBIN hist_profile) {
  if(hist_profile.name != "" && check_name(hist_profile.name)) {
    cout<<"Name \""<<hist_profile.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_profile.insert(make_pair(hist_profile.name,
				      new TProfile(hist_profile.name, hist_profile.name,
						   hist_profile.nbinx, hist_profile.binx,
						   hist_profile.lowery, hist_profile.uppery, hist_profile.profile_option)));
  hist_files_profile[hist_profile.name]->Sumw2();
}
void hist_files::add(HIST_PROFILE_VARBIN* _hist_profile) {
  HIST_PROFILE_VARBIN* hist_profile=_hist_profile;
  while( (*hist_profile).name!="" ) {
    add(*hist_profile);
    ++hist_profile;
  }
}

// deal with 2D variable-bin-size Profile (all 3 types: X-only, Y-only, both X&Y)
void hist_files::add(HIST_PROFILE_2D_VARBIN_X hist_profile_2d) {
  if(hist_profile_2d.name != "" && check_name(hist_profile_2d.name)) {
    cout<<"Name \""<<hist_profile_2d.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_profile_2d.insert(make_pair(hist_profile_2d.name,
					 new TProfile2D(hist_profile_2d.name, hist_profile_2d.name,
							hist_profile_2d.nbinx, hist_profile_2d.binx,
							hist_profile_2d.nbiny, hist_profile_2d.lowery, hist_profile_2d.uppery)));
  if(check_name(hist_profile_2d.name)) {
    hist_files_profile_2d[hist_profile_2d.name]->BuildOptions(hist_profile_2d.lowerz, hist_profile_2d.upperz, hist_profile_2d.profile_option);
    hist_files_profile_2d[hist_profile_2d.name]->Sumw2();
  }
}
void hist_files::add(HIST_PROFILE_2D_VARBIN_X* _hist_profile_2d) {
  HIST_PROFILE_2D_VARBIN_X* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name!="" ) {
    add(*hist_profile_2d);
    ++hist_profile_2d;
  }
}
void hist_files::add(HIST_PROFILE_2D_VARBIN_Y hist_profile_2d) {
  if(hist_profile_2d.name != "" && check_name(hist_profile_2d.name)) {
    cout<<"Name \""<<hist_profile_2d.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_profile_2d.insert(make_pair(hist_profile_2d.name,
					 new TProfile2D(hist_profile_2d.name, hist_profile_2d.name,
							hist_profile_2d.nbinx, hist_profile_2d.lowerx, hist_profile_2d.upperx,
							hist_profile_2d.nbiny, hist_profile_2d.biny)));
  if(check_name(hist_profile_2d.name)) {
    hist_files_profile_2d[hist_profile_2d.name]->BuildOptions(hist_profile_2d.lowerz, hist_profile_2d.upperz, hist_profile_2d.profile_option);
    hist_files_profile_2d[hist_profile_2d.name]->Sumw2();
  }
}
void hist_files::add(HIST_PROFILE_2D_VARBIN_Y* _hist_profile_2d) {
  HIST_PROFILE_2D_VARBIN_Y* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name!="" ) {
    add(*hist_profile_2d);
    ++hist_profile_2d;
  }
}
void hist_files::add(HIST_PROFILE_2D_VARBIN_XY hist_profile_2d) {
  if(hist_profile_2d.name != "" && check_name(hist_profile_2d.name)) {
    cout<<"Name \""<<hist_profile_2d.name<<"\" already exists!"<<endl;
    return;
  }
  hist_files_profile_2d.insert(make_pair(hist_profile_2d.name,
					 new TProfile2D(hist_profile_2d.name, hist_profile_2d.name,
							hist_profile_2d.nbinx, hist_profile_2d.binx,
							hist_profile_2d.nbiny, hist_profile_2d.biny)));
  if(check_name(hist_profile_2d.name)) {
    hist_files_profile_2d[hist_profile_2d.name]->BuildOptions(hist_profile_2d.lowerz, hist_profile_2d.upperz, hist_profile_2d.profile_option);
    hist_files_profile_2d[hist_profile_2d.name]->Sumw2();
  }
}
void hist_files::add(HIST_PROFILE_2D_VARBIN_XY* _hist_profile_2d) {
  HIST_PROFILE_2D_VARBIN_XY* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name!="" ) {
    add(*hist_profile_2d);
    ++hist_profile_2d;
  }
}

/////////////////////////////////////////////////
////       Clone Histograms or Profiles       ///
/////////////////////////////////////////////////

// this function will make n copies of a histogram with name hist_name
// the name of each copy is hist_name_i (for i=0, ... n)
// inline void hist_files::clone(TString hist_name, const int n, const char *suffix_name) {
//   clone(hist_name, n, TString(suffix_name));
// }
void hist_files::clone(TString hist_name, const int n, TString suffix_name) {
//   if(hist_files_1d.find(hist_name)==hist_files_1d.end() &&
//      hist_files_2d.find(hist_name)==hist_files_2d.end() &&
//      hist_files_profile.find(hist_name)==hist_files_profile.end() ) {
  if( !check_name(hist_name) ) {
    cout<<"Can't make clones of non-existing histogram \""<<hist_name<<"\""<<endl;
    return;
  }
  
  TString SN;
  char sn[10];
  
  //should check if the "hist_name+SN" is already in the list or not.
  //but for now for simplicity we don't check it.
  for(int i=0; i!=n; ++i){
    sprintf(sn,"%d", i); 
    SN=suffix_name+TString("_")+sn;  
    if(check_name(hist_name+SN)) {
      cout<<"Name \""<<hist_name<<SN<<"\" already exists!"<<endl;
      continue;
    }
    clone(hist_name,hist_name+SN);

  } // loop over n
}

void hist_files::clone(HIST_1D hist_1d, int n, TString suffix_name) {
  if(hist_files_1d.find(hist_1d.name)==hist_files_1d.end())
    add(hist_1d);
  clone(hist_1d.name, n, suffix_name);
}

void hist_files::clone(HIST_2D hist_2d, int n, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end()) 
    add(hist_2d);
  clone(hist_2d.name, n, suffix_name);
}

void hist_files::clone(HIST_3D hist_3d, int n, TString suffix_name) {
  if(hist_files_3d.find(hist_3d.name)==hist_files_3d.end()) 
    add(hist_3d);
  clone(hist_3d.name, n, suffix_name);
}

void hist_files::clone(HIST_PROFILE hist_profile, int n, TString suffix_name) {
  if(hist_files_profile.find(hist_profile.name)==hist_files_profile.end())  add(hist_profile);
  clone(hist_profile.name, n, suffix_name);
}

void hist_files::clone(HIST_PROFILE_2D hist_profile_2d, int n, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end())  add(hist_profile_2d);
  clone(hist_profile_2d.name, n, suffix_name);
}

void hist_files::clone(HIST_1D_VARBIN hist_1d, int n, TString suffix_name) {
  if(hist_files_1d.find(hist_1d.name)==hist_files_1d.end())
    add(hist_1d);
  clone(hist_1d.name, n, suffix_name);
}

void hist_files::clone(HIST_2D_VARBIN_X hist_2d, int n, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end()) 
    add(hist_2d);
  clone(hist_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_2D_VARBIN_Y hist_2d, int n, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end()) 
    add(hist_2d);
  clone(hist_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_2D_VARBIN_XY hist_2d, int n, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end()) 
    add(hist_2d);
  clone(hist_2d.name, n, suffix_name);
}

void hist_files::clone(HIST_PROFILE_VARBIN hist_profile, int n, TString suffix_name) {
  if(hist_files_profile.find(hist_profile.name)==hist_files_profile.end())  add(hist_profile);
  clone(hist_profile.name, n, suffix_name);
}

void hist_files::clone(HIST_PROFILE_2D_VARBIN_X hist_profile_2d, int n, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end())  add(hist_profile_2d);
  clone(hist_profile_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_PROFILE_2D_VARBIN_Y hist_profile_2d, int n, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end())  add(hist_profile_2d);
  clone(hist_profile_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_PROFILE_2D_VARBIN_XY hist_profile_2d, int n, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end())  add(hist_profile_2d);
  clone(hist_profile_2d.name, n, suffix_name);
}

// this function will make 1 copy of a histogram with name hist_name
// the name of a copy is hist_name_new
void hist_files::clone(TString hist_name, TString hist_name_new) {

  if( !check_name(hist_name) ) {
    cout<<"Can't make clones of non-existing histogram \""<<hist_name<<"\""<<endl;
    return;
  }
  if( check_name(hist_name_new) ) {
    cout<<"Name \""<<hist_name_new<<"\" already exists!"<<endl;
    return;
  }
  
  if(hist_files_1d.find(hist_name)!=hist_files_1d.end()) {    
    hist_files_1d.insert(make_pair(hist_name_new,
				   (hist_files_1d[hist_name]->GetXaxis()->GetXbins()->GetSize() ?
				    /* X axis - variable bin size */
				    new TH1D(hist_name_new, hist_name_new,
					     hist_files_1d[hist_name]->GetNbinsX(),
					     hist_files_1d[hist_name]->GetXaxis()->GetXbins()->GetArray()) :
				    /* X axis - same bin size */
				    new TH1D(hist_name_new, hist_name_new,
					     hist_files_1d[hist_name]->GetNbinsX(),
					     hist_files_1d[hist_name]->GetXaxis()->GetXmin(),
					     hist_files_1d[hist_name]->GetXaxis()->GetXmax()) )));
    hist_files_1d[hist_name_new]->Sumw2();
  }
  if(hist_files_2d.find(hist_name)!=hist_files_2d.end()) {
    hist_files_2d.insert(make_pair(hist_name_new,
				   (hist_files_2d[hist_name]->GetXaxis()->GetXbins()->GetSize() ?
				    (hist_files_2d[hist_name]->GetYaxis()->GetXbins()->GetSize() ?
				     /* X axis - variable bin size */
				     /* Y axis - variable bin size */
				     new TH2D(hist_name_new, hist_name_new,
					      hist_files_2d[hist_name]->GetNbinsX(),
					      hist_files_2d[hist_name]->GetXaxis()->GetXbins()->GetArray(),
					      hist_files_2d[hist_name]->GetNbinsY(),
					      hist_files_2d[hist_name]->GetYaxis()->GetXbins()->GetArray()) :
				     /* X axis - variable bin size */
				     /* Y axis - same bin size */
				     new TH2D(hist_name_new, hist_name_new,
					      hist_files_2d[hist_name]->GetNbinsX(),
					      hist_files_2d[hist_name]->GetXaxis()->GetXbins()->GetArray(),
					      hist_files_2d[hist_name]->GetNbinsY(),
					      hist_files_2d[hist_name]->GetYaxis()->GetXmin(),
					      hist_files_2d[hist_name]->GetYaxis()->GetXmax()) ) :
				    (hist_files_2d[hist_name]->GetYaxis()->GetXbins()->GetSize() ?
				     /* X axis - same bin size */
				     /* Y axis - variable bin size */
				     new TH2D(hist_name_new, hist_name_new,
					      hist_files_2d[hist_name]->GetNbinsX(),
					      hist_files_2d[hist_name]->GetXaxis()->GetXmin(),
					      hist_files_2d[hist_name]->GetXaxis()->GetXmax(),
					      hist_files_2d[hist_name]->GetNbinsY(),
					      hist_files_2d[hist_name]->GetYaxis()->GetXbins()->GetArray()) :
				     /* X axis - same bin size */
				     /* Y axis - same bin size */
				     new TH2D(hist_name_new, hist_name_new,
					      hist_files_2d[hist_name]->GetNbinsX(),
					      hist_files_2d[hist_name]->GetXaxis()->GetXmin(),
					      hist_files_2d[hist_name]->GetXaxis()->GetXmax(),
					      hist_files_2d[hist_name]->GetNbinsY(),
					      hist_files_2d[hist_name]->GetYaxis()->GetXmin(),
					      hist_files_2d[hist_name]->GetYaxis()->GetXmax())))));
    hist_files_2d[hist_name_new]->Sumw2();
  }
  if(hist_files_3d.find(hist_name)!=hist_files_3d.end()) {    
    hist_files_3d.insert(make_pair(hist_name_new,
				   /* X axis - same bin size */
				   new TH3D(hist_name_new, hist_name_new,
					    hist_files_3d[hist_name]->GetNbinsX(),
					    hist_files_3d[hist_name]->GetXaxis()->GetXmin(),
					    hist_files_3d[hist_name]->GetXaxis()->GetXmax(),
					    hist_files_3d[hist_name]->GetNbinsY(),
					    hist_files_3d[hist_name]->GetYaxis()->GetXmin(),
					    hist_files_3d[hist_name]->GetYaxis()->GetXmax(),
					    hist_files_3d[hist_name]->GetNbinsZ(),
					    hist_files_3d[hist_name]->GetZaxis()->GetXmin(),
					    hist_files_3d[hist_name]->GetZaxis()->GetXmax())));
    hist_files_3d[hist_name_new]->Sumw2();
  }
  if(hist_files_profile.find(hist_name)!=hist_files_profile.end()) {
    hist_files_profile.insert(make_pair(hist_name_new,
					(hist_files_profile[hist_name]->GetXaxis()->GetXbins()->GetSize() ?
					 /* X axis - variable bin size */
					 new TProfile(hist_name_new, hist_name_new,
						      hist_files_profile[hist_name]->GetNbinsX(),
						      hist_files_profile[hist_name]->GetXaxis()->GetXbins()->GetArray(),
						      hist_files_profile[hist_name]->GetYmin(),
						      hist_files_profile[hist_name]->GetYmax(), 
						      hist_files_profile[hist_name]->GetErrorOption()) :
					 /* X axis - same bin size */
					 new TProfile(hist_name_new, hist_name_new,
						      hist_files_profile[hist_name]->GetNbinsX(),
						      hist_files_profile[hist_name]->GetXaxis()->GetXmin(),
						      hist_files_profile[hist_name]->GetXaxis()->GetXmax(),
						      hist_files_profile[hist_name]->GetYmin(),
						      hist_files_profile[hist_name]->GetYmax(), 
						      hist_files_profile[hist_name]->GetErrorOption()))));
    hist_files_profile[hist_name_new]->Sumw2();
  }
  if(hist_files_profile_2d.find(hist_name)!=hist_files_profile_2d.end()) {
    hist_files_profile_2d.insert(make_pair(hist_name_new,
					   (hist_files_profile_2d[hist_name]->GetXaxis()->GetXbins()->GetSize() ?
					    (hist_files_profile_2d[hist_name]->GetYaxis()->GetXbins()->GetSize() ?
					     /* X axis - variable bin size */
					     /* Y axis - variable bin size */
					     new TProfile2D(hist_name_new, hist_name_new,
							    hist_files_profile_2d[hist_name]->GetNbinsX(),
						      hist_files_profile_2d[hist_name]->GetXaxis()->GetXbins()->GetArray(),
						      hist_files_profile_2d[hist_name]->GetNbinsY(),
						      hist_files_profile_2d[hist_name]->GetYaxis()->GetXbins()->GetArray()) :
					     /* X axis - variable bin size */
					     /* Y axis - same bin size */
					     new TProfile2D(hist_name_new, hist_name_new,
						      hist_files_profile_2d[hist_name]->GetNbinsX(),
						      hist_files_profile_2d[hist_name]->GetXaxis()->GetXbins()->GetArray(),
						      hist_files_profile_2d[hist_name]->GetNbinsY(),
						      hist_files_profile_2d[hist_name]->GetYaxis()->GetXmin(),
						      hist_files_profile_2d[hist_name]->GetYaxis()->GetXmax()) ) :
					    (hist_files_profile_2d[hist_name]->GetYaxis()->GetXbins()->GetSize() ?
					     /* X axis - same bin size */
					     /* Y axis - variable bin size */
					     new TProfile2D(hist_name_new, hist_name_new,
						      hist_files_profile_2d[hist_name]->GetNbinsX(),
						      hist_files_profile_2d[hist_name]->GetXaxis()->GetXmin(),
						      hist_files_profile_2d[hist_name]->GetXaxis()->GetXmax(),
						      hist_files_profile_2d[hist_name]->GetNbinsY(),
						      hist_files_profile_2d[hist_name]->GetYaxis()->GetXbins()->GetArray()) :
					     /* X axis - same bin size */
					     /* Y axis - same bin size */
					     new TProfile2D(hist_name_new, hist_name_new,
						      hist_files_profile_2d[hist_name]->GetNbinsX(),
							    hist_files_profile_2d[hist_name]->GetXaxis()->GetXmin(),
						      hist_files_profile_2d[hist_name]->GetXaxis()->GetXmax(),
						      hist_files_profile_2d[hist_name]->GetNbinsY(),
						      hist_files_profile_2d[hist_name]->GetYaxis()->GetXmin(),
						      hist_files_profile_2d[hist_name]->GetYaxis()->GetXmax()) ) ) ));
    if(check_name(hist_name_new)) {
      hist_files_profile_2d[hist_name_new]->BuildOptions(hist_files_profile_2d[hist_name]->GetZmin(), 
							 hist_files_profile_2d[hist_name]->GetZmax(), 
							 hist_files_profile_2d[hist_name]->GetErrorOption());
      hist_files_profile_2d[hist_name_new]->Sumw2();
    }
  }  
}

////////////////////////////////////////////////////////////////////////////////
// this function will make nx * ny copies of a histogram with name hist_name
// the name of each copy is hist_name_ij (for i=0, ... nx and j=0, ... ny)
// only works for j<10
////////////////////////////////////////////////////////////////////////////////
// inline void hist_files::cloneArray(TString hist_name, const int nx, const int ny, const char *suffix_name) {
//   cloneArray(hist_name, nx, ny, TString(suffix_name));
// }
void hist_files::cloneArray(TString hist_name, const int nx, const int ny, TString suffix_name) {

//   if(hist_files_1d.find(hist_name)==hist_files_1d.end() &&
//      hist_files_2d.find(hist_name)==hist_files_2d.end() &&
//      hist_files_profile.find(hist_name)==hist_files_profile.end()) {
//     cout<<"No such histogram as "<<hist_name<<endl;
//     return;
//   }
  if( !check_name(hist_name) ) {
    cout<<"Can't make clones of non-existing histogram \""<<hist_name<<"\""<<endl;
    return;
  }
  
  TString SN;
  char sn1[10], sn2[10];

  //should check if the "hist_name+SN" is already in the list or not.
  //but for now for simplicity we don't check it.
  for(int ix=0; ix!=nx; ++ix){
    for(int iy=0; iy!=ny; ++iy){
      sprintf(sn1,"%d", ix); 
      sprintf(sn2,"%d", iy); 
      SN=suffix_name+TString("_")+sn1+TString("_")+sn2;
      
      if(check_name(hist_name+SN)) {
	cout<<"Name \""<<hist_name<<SN<<"\" already exists!"<<endl;
	continue;
      }

      clone(hist_name,hist_name+SN);

    } // loop over ny
  } // loop over nx  
}

void hist_files::cloneArray(HIST_1D hist_1d, int nx, int ny, TString suffix_name) {
  if(hist_files_1d.find(hist_1d.name)==hist_files_1d.end())
    add(hist_1d);
  cloneArray(hist_1d.name, nx, ny, suffix_name);
}

void hist_files::cloneArray(HIST_2D hist_2d, int nx, int ny, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end())
    add(hist_2d);
  cloneArray(hist_2d.name, nx, ny, suffix_name);
}

void hist_files::cloneArray(HIST_3D hist_3d, int nx, int ny, TString suffix_name) {
  if(hist_files_3d.find(hist_3d.name)==hist_files_3d.end())
    add(hist_3d);
  cloneArray(hist_3d.name, nx, ny, suffix_name);
}

void hist_files::cloneArray(HIST_PROFILE hist_profile, int nx, int ny, TString suffix_name) {
  if(hist_files_profile.find(hist_profile.name)==hist_files_profile.end())
    add(hist_profile);
  cloneArray(hist_profile.name, nx, ny, suffix_name);
}

void hist_files::cloneArray(HIST_PROFILE_2D hist_profile_2d, int nx, int ny, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end())
    add(hist_profile_2d);
  cloneArray(hist_profile_2d.name, nx, ny, suffix_name);
}

void hist_files::cloneArray(HIST_1D_VARBIN hist_1d, int nx, int ny, TString suffix_name) {
  if(hist_files_1d.find(hist_1d.name)==hist_files_1d.end())
    add(hist_1d);
  cloneArray(hist_1d.name, nx, ny, suffix_name);
}

void hist_files::cloneArray(HIST_2D_VARBIN_X hist_2d, int nx, int ny, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end())
    add(hist_2d);
  cloneArray(hist_2d.name, nx, ny, suffix_name);
}
void hist_files::cloneArray(HIST_2D_VARBIN_Y hist_2d, int nx, int ny, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end())
    add(hist_2d);
  cloneArray(hist_2d.name, nx, ny, suffix_name);
}
void hist_files::cloneArray(HIST_2D_VARBIN_XY hist_2d, int nx, int ny, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end())
    add(hist_2d);
  cloneArray(hist_2d.name, nx, ny, suffix_name);
}

void hist_files::cloneArray(HIST_PROFILE_VARBIN hist_profile, int nx, int ny, TString suffix_name) {
  if(hist_files_profile.find(hist_profile.name)==hist_files_profile.end())
    add(hist_profile);
  cloneArray(hist_profile.name, nx, ny, suffix_name);
}
void hist_files::cloneArray(HIST_PROFILE_2D_VARBIN_X hist_profile_2d, int nx, int ny, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end())
    add(hist_profile_2d);
  cloneArray(hist_profile_2d.name, nx, ny, suffix_name);
}
void hist_files::cloneArray(HIST_PROFILE_2D_VARBIN_Y hist_profile_2d, int nx, int ny, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end())
    add(hist_profile_2d);
  cloneArray(hist_profile_2d.name, nx, ny, suffix_name);
}
void hist_files::cloneArray(HIST_PROFILE_2D_VARBIN_XY hist_profile_2d, int nx, int ny, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end())
    add(hist_profile_2d);
  cloneArray(hist_profile_2d.name, nx, ny, suffix_name);
}

/////////////////////////////////////////////////
////        Fill Histograms or Profiles       ///
/////////////////////////////////////////////////
//void hist_files::fill(TString hist_name, Float_t x) {
//  hist_files_1d[hist_name]->Fill(x);
//}

void hist_files::Fill1D(TString hist_name, Float_t x, Float_t weight) {
  if(hist_files_1d[hist_name]) 
    hist_files_1d[hist_name]->Fill(x, weight);
}

void hist_files::Fill2D(TString hist_name, Float_t x, Float_t y, Float_t weight) {
  if(hist_files_2d[hist_name]) 
    hist_files_2d[hist_name]->Fill(x, y, weight);
}

void hist_files::Fill3D(TString hist_name, Float_t x, Float_t y, Float_t z, Float_t weight) {
  if(hist_files_3d[hist_name]) 
    hist_files_3d[hist_name]->Fill(x, y, z, weight);
}

void hist_files::FillProfile(TString hist_name, Float_t x, Float_t y, Float_t weight) {
  if(hist_files_profile[hist_name]) 
    hist_files_profile[hist_name]->Fill(x, y, weight);
}

void hist_files::FillProfile2D(TString hist_name, Float_t x, Float_t y, Float_t z, Float_t weight) {
  if(hist_files_profile_2d[hist_name]) 
    hist_files_profile_2d[hist_name]->Fill(x, y, z, weight);
}

/////////////////////////////////////////////////
////        Save Histograms or Profiles       ///
/////////////////////////////////////////////////
void hist_files::save(const char* root_name, bool ps, bool debug) {

  // skip saving if histograms do not exist!
  if( size()==0 ) return;

  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetOptStat(111111);

  TCanvas c1;
  TFile *hist = new TFile(root_name);
 
  cout << "Saving histograms to file to " << hist->GetPath() << endl;

  if (debug) cout << "hist_files::save: 1D_HISTOS=" << size1D() << endl << flush;
  for(map<TString, TH1D*>::iterator it_1d = hist_files_1d.begin(); 
      it_1d != hist_files_1d.end(); it_1d++) 
    if ((*it_1d).first != "" && (*it_1d).second != NULL) {
      if (debug) cout << "hist_files::save: 1D_NAME=" << ((*it_1d).second)->GetName() << endl << flush;
      TString fn = ((*it_1d).second)->GetName(); fn = fn + ".ps";
      ((*it_1d).second)->Draw();
      ((*it_1d).second)->Write();
      if(ps) c1.Print(fn);
    }
  
  if (debug) cout << "hist_files::save: 2D_HISTOS=" << size2D() << endl << flush;
  for(map<TString, TH2D*>::iterator it_2d = hist_files_2d.begin();
      it_2d != hist_files_2d.end(); it_2d++) 
    if ((*it_2d).first != "" && (*it_2d).second != NULL) {
      if (debug) cout << "hist_files::save: 2D_NAME=" << ((*it_2d).second)->GetName() << endl << flush;
      TString fn = ((*it_2d).second)->GetName(); fn = fn + ".ps";
      ((*it_2d).second)->Draw();
      ((*it_2d).second)->Write();
      if(ps) c1.Print(fn);
    }

  if (debug) cout << "hist_files::save: 3D_HISTOS=" << size3D() << endl << flush;
  for(map<TString, TH3D*>::iterator it_3d = hist_files_3d.begin();
      it_3d != hist_files_3d.end(); it_3d++) 
    if ((*it_3d).first != "" && (*it_3d).second != NULL) {
      if (debug) cout << "hist_files::save: 3D_NAME=" << ((*it_3d).second)->GetName() << endl << flush;
      TString fn = ((*it_3d).second)->GetName(); fn = fn + ".ps";
      ((*it_3d).second)->Draw();
      ((*it_3d).second)->Write();
      if(ps) c1.Print(fn);
    }

  if (debug) cout << "hist_files::save: PROFILE_HISTOS=" << sizeProfile() << endl << flush;
  for(map<TString, TProfile*>::iterator it_profile = hist_files_profile.begin();
      it_profile != hist_files_profile.end(); it_profile++) 
    if ((*it_profile).first != "" && (*it_profile).second != NULL) {
      if (debug) cout << "hist_files::save: PROFILE_NAME=" << ((*it_profile).second)->GetName() << endl << flush;
      TString fn = ((*it_profile).second)->GetName(); fn = fn + ".ps";
      ((*it_profile).second)->Draw();
      ((*it_profile).second)->Write();
      if(ps) c1.Print(fn);
    }

  if (debug) cout << "hist_files::save: PROFILE_2D_HISTOS=" << sizeProfile2D() << endl << flush;
  for(map<TString, TProfile2D*>::iterator it_profile_2d = hist_files_profile_2d.begin();
      it_profile_2d != hist_files_profile_2d.end(); it_profile_2d++) 
    if ((*it_profile_2d).first != "" && (*it_profile_2d).second != NULL) {
      if (debug) cout << "hist_files::save: PROFILE_2D_NAME=" << ((*it_profile_2d).second)->GetName() << endl << flush;
      TString fn = ((*it_profile_2d).second)->GetName(); fn = fn + ".ps";
      ((*it_profile_2d).second)->Draw();
      ((*it_profile_2d).second)->Write();
      if(ps) c1.Print(fn);
    }

  hist->Close();  
  cout << "Done." << endl;
}

void hist_files::save(TFile* root_file, string directory_name, bool debug) {

  // skip saving if histograms do not exist!
  if( size()==0 || root_file==NULL ) return;

  root_file->cd(directory_name.c_str());

  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetOptStat(111111);

  cout << "hist_files::save: Saving histograms to " << root_file->GetPath() 
       << directory_name << endl;
    
  if (debug) cout << "hist_files::save: 1D_HISTOS=" << size1D() << endl << flush;
  for(map<TString, TH1D*>::iterator it_1d = hist_files_1d.begin(); 
      it_1d != hist_files_1d.end(); it_1d++) 
    if ((*it_1d).first != "" && (*it_1d).second != NULL) {
      if (debug) cout << "hist_files::save: 1D_NAME=" << ((*it_1d).second)->GetName() << endl << flush;
      ((*it_1d).second)->Write();
    }
  
  if (debug) cout << "hist_files::save: 2D_HISTOS=" << size2D() << endl << flush;
  for(map<TString, TH2D*>::iterator it_2d = hist_files_2d.begin();
      it_2d != hist_files_2d.end(); it_2d++)
    if ((*it_2d).first != "" && (*it_2d).second != NULL) {
      if (debug) cout << "hist_files::save: 2D_NAME=" << ((*it_2d).second)->GetName() << endl << flush;
      ((*it_2d).second)->Write();
    }

 if (debug) cout << "hist_files::save: 3D_HISTOS=" << size3D() << endl << flush;
  for(map<TString, TH3D*>::iterator it_3d = hist_files_3d.begin();
      it_3d != hist_files_3d.end(); it_3d++)
    if ((*it_3d).first != "" && (*it_3d).second != NULL) {
      if (debug) cout << "hist_files::save: 3D_NAME=" << ((*it_3d).second)->GetName() << endl << flush;
      ((*it_3d).second)->Write();
    }
  
  if (debug) cout << "hist_files::save: PROFILE_HISTOS=" << sizeProfile() << endl << flush;
  for(map<TString, TProfile*>::iterator it_profile = hist_files_profile.begin();
      it_profile != hist_files_profile.end(); it_profile++) 
    if ((*it_profile).first != "" && (*it_profile).second != NULL) {
      if (debug) cout << "hist_files::save: PROFILE_NAME=" << ((*it_profile).second)->GetName() << endl << flush;
      ((*it_profile).second)->Write();
    }
  
  if (debug) cout << "hist_files::save: PROFILE_2D_HISTOS=" << sizeProfile2D() << endl << flush;
  for(map<TString, TProfile2D*>::iterator it_profile_2d = hist_files_profile_2d.begin();
      it_profile_2d != hist_files_profile_2d.end(); it_profile_2d++) 
    if ((*it_profile_2d).first != "" && (*it_profile_2d).second != NULL) {
      if (debug) cout << "hist_files::save: PROFILE_2D_NAME=" << ((*it_profile_2d).second)->GetName() << endl << flush;
      ((*it_profile_2d).second)->Write();
    }
  
  root_file->cd();
  cout << "hist_files::save: Done." << endl;
}


TFile* histfiles::initializeTFile(const char *processor_name, bool debug) {

  stringstream _name;
  _name << processor_name;
  if(_name.str()=="") _name.str("cafe"); 
  Config config(_name.str().c_str());
  string _output = config.get("Output", "result.root");

  if(debug) cout << "histfiles::initializeTFile:"
		 << " PROCESSOR_NAME=" << _name.str()
		 << " OUTPUT_FILE=" << _output
		 << endl;

  if (_output=="") return NULL;

  // keep track of rootuples that have been already created during this session 
  TFile *f = NULL;
  if (find(_histfiles_created.begin(),
	   _histfiles_created.end(),
	   _output) == _histfiles_created.end()) {
    
    if(debug) cout << "histfiles::initializeTFile: Output file has not been opened yet" << endl;
    f = new TFile(_output.c_str(),"RECREATE");
    if (f!=NULL) { 
      _histfiles_created.push_back(_output);
    }
  } else {
    if(debug) cout << "histfiles::initializeTFile: Output file has been already created" << endl;
    f = new TFile(_output.c_str(),"UPDATE");
  }
  return f; 
}

TFile* histfiles::initializeTFile(cafe::Processor *processor, bool debug) {

  if(debug) cout << "histfiles::initializeTFile:"
		 << " PROCESSOR_PTR=" << processor << endl;

  if (processor==NULL) return histfiles::initializeTFile("cafe",debug);

  // in case one wants parent processor only
  // string _name( histfiles::getParentProcessorName(processor) );

  // in case one wants "cafe" environment
  // string _name("cafe");

  // in case one wants processor's name (default)
  const TString _name( processor->name() );
  return histfiles::initializeTFile(_name,debug);
}

const char* histfiles::getParentProcessorName(const cafe::Processor *processor, bool debug) {

  if (processor==NULL) return "cafe";

  // is this a child processor?
  cafe::Processor *parent = const_cast<cafe::Processor*>(processor);
  while( parent!=NULL ) {
    cafe::Processor *new_parent = parent->getParent();
    if (new_parent!=NULL && new_parent->name()!="cafe" ) parent=new_parent;
    else break;
  };

  if(debug) 
    cout << "histfiles::getParentProcessorName: PROCESSOR_PTR=" << processor
	 << " PROCESSOR(name=" << processor->name() << ", fullname=" << processor->fullName()
	 << ") PARENT_NAME=" << parent->name() << endl;
  
  return parent->name().c_str();
}

