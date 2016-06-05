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
#include "hist_files.hpp"
#include "hist_nd.hpp"

// ROOT v5 breaks the previous behaviour of TDirectory, this fixes that behaviour without breaking ROOT v4
#ifdef ROOT_TDirectoryFile
#define TDIRECTORY TDirectoryFile
#else
#define TDIRECTORY TDirectory
#endif

using std::cout;
using std::endl;
using std::flush;
using std::make_pair;
using std::string;
using std::find;
using std::map;
using std::vector;

// constructor
hist_files::hist_files() {
  cout<<"Init hist file lists..."<<endl;
  NormalizeVarBinHistograms_done=false; 
}


// destructor
hist_files::~hist_files() {

  cout<<"Delete hist files..."<<endl;
  for(map<TString, histInfo>::iterator it_1d = hist_files_1d.begin(); 
      it_1d != hist_files_1d.end(); it_1d++) {
    cout<<(*it_1d).first<<endl;
    delete (*it_1d).second.get1DHist();;
  }
  
  for(map<TString, histInfo>::iterator it_2d = hist_files_2d.begin();
      it_2d != hist_files_2d.end(); it_2d++) {
    cout<<(*it_2d).first<<endl;
    delete (*it_2d).second.get2DHist();
  }
  
  for(map<TString, histInfo>::iterator it_profile = hist_files_profile.begin();
      it_profile != hist_files_profile.end(); it_profile++) {
    cout<<(*it_profile).first<<endl;
    delete (*it_profile).second.getProfileHist();
  }
  
  for(map<TString, histInfo>::iterator it_profile_2d = hist_files_profile_2d.begin();
      it_profile_2d != hist_files_profile_2d.end(); it_profile_2d++) {
    cout<<(*it_profile_2d).first<<endl;
    delete (*it_profile_2d).second.get2DProfileHist();
  }
  
}

/////////////////////////////////////////////////
////       Check for duplicate names          ///
/////////////////////////////////////////////////
bool hist_files::check_name(TString hist_name) {
  bool result=false;
  if(hist_files_1d.find(hist_name)==hist_files_1d.end() &&
     hist_files_2d.find(hist_name)==hist_files_2d.end() &&
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
////       Get title from name                ///
/////////////////////////////////////////////////
TString hist_files::get_title(TString hist_name) {
  if(check_name(hist_name)) {
    map<TString, histInfo>::iterator it;
    //    cout << "hist_files::get_title: Name "<<hist_name<<" is in the list"<<endl<<flush;
    if((it=hist_files_1d.find(hist_name))!=hist_files_1d.end() && (*it).second.get1DHist()) {
      //      cout << "hist_files::get_title: TH1D pointer="<<(*it).second.get1DHist()<<endl<<flush;
      //      cout << "hist_files::get_title: TH1D title="<<(*it).second.get1DHist()->GetTitle()<<endl<<flush;
      return TString( (*it).second.get1DHist()->GetTitle() );
    }
    else if((it=hist_files_2d.find(hist_name))!=hist_files_2d.end() && (*it).second.get2DHist()) {
      //      cout << "hist_files::get_title: TH2D pointer="<<(*it).second.get2DHist()<<endl<<flush;
      //      cout << "hist_files::get_title: TH2D title="<<(*it).second.get2DHist()->GetTitle()<<endl<<flush;
      return TString( (*it).second.get2DHist()->GetTitle() );
    }
    else if((it=hist_files_profile.find(hist_name))!=hist_files_profile.end() && (*it).second.getProfileHist()) {
      //      cout << "hist_files::get_title: TProfile pointer="<<(*it).second.getProfileHist()<<endl<<flush;
      //      cout << "hist_files::get_title: TProfile title="<<(*it).second.getProfileHist()->GetTitle()<<endl<<flush;
      return TString( (*it).second.getProfileHist()->GetTitle() );
    }
    else if((it=hist_files_profile_2d.find(hist_name))!=hist_files_profile_2d.end() && (*it).second.get2DProfileHist()) {
      //      cout << "hist_files::get_title: TProfile2D pointer="<<(*it).second.get2DProfileHist()<<endl<<flush;
      //      cout << "hist_files::get_title: TProfile2D title="<<(*it).second.get2DProfileHist()->GetTitle()<<endl<<flush;
      return TString( (*it).second.get2DProfileHist()->GetTitle() );
    }
  }
  cout << "hist_files::get_title: Name "<<hist_name<<" does not exist or histogram pointer is 0."<<endl<<flush;
  return TString("");
}

/////////////////////////////////////////////////
////         Add Histograms or Profiles       ///
/////////////////////////////////////////////////

// deal with 1D histogram
void hist_files::add(HIST_1D hist_1d, 
		     string prefix, string folder) 
{
  hist_1d.name = prefix + hist_1d.name;
  if(hist_1d.name != "" && check_name(hist_1d.name)) {
    cout<<"Name \""<<hist_1d.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TH1D(hist_1d.name,
		       hist_1d.title,
		       hist_1d.nbin,
		       hist_1d.lower,
		       hist_1d.upper), 
	      folder);
  hist_files_1d.insert(make_pair(hist_1d.name, HI));
}
void hist_files::add( HIST_1D* _hist_1d, 
		     string prefix, string folder) 
{
  HIST_1D* hist_1d=_hist_1d;
  while( (*hist_1d).name != "" ) {
    add(*hist_1d, prefix, folder);
    ++hist_1d;
  }
}

// deal with 2D histograms
void hist_files::add(HIST_2D hist_2d, 
		     string prefix, string folder) 
{
  hist_2d.name = prefix + hist_2d.name;
  if(hist_2d.name != "" && check_name(hist_2d.name)) {
    cout<<"Name \""<<hist_2d.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TH2D(hist_2d.name,
		       hist_2d.title,    
		       hist_2d.nbinx,    
		       hist_2d.lowerx,   
		       hist_2d.upperx,   
		       hist_2d.nbiny,    
		       hist_2d.lowery,   
		       hist_2d.uppery),
	      folder);
  hist_files_2d.insert(make_pair(hist_2d.name, HI));
}
void hist_files::add(HIST_2D* _hist_2d, 
		     string prefix, string folder) 
{
  HIST_2D* hist_2d=_hist_2d;
  while( (*hist_2d).name!="" ) {
    add(*hist_2d, prefix, folder);
    ++hist_2d;
  }
}

// deal with Profile
void hist_files::add(HIST_PROFILE hist_profile, 
		     string prefix, string folder) 
{
  hist_profile.name = prefix + hist_profile.name;
  if(hist_profile.name != "" && check_name(hist_profile.name)) {
    cout<<"Name \""<<hist_profile.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TProfile(hist_profile.name,
			   hist_profile.title,    
			   hist_profile.nbinx,    
			   hist_profile.lowerx,   
			   hist_profile.upperx,   
			   hist_profile.lowery,   
			   hist_profile.uppery, 
			   hist_profile.profile_option),
	      folder);
  hist_files_profile.insert(make_pair(hist_profile.name, HI));
}
void hist_files::add(HIST_PROFILE* _hist_profile, 
		     string prefix, string folder)
{
  HIST_PROFILE* hist_profile=_hist_profile;
  while( (*hist_profile).name!="" ) {
    add(*hist_profile, prefix, folder);
    ++hist_profile;
  }
}

// deal with 2D Profile
void hist_files::add(HIST_PROFILE_2D hist_profile_2d, 
		     string prefix, string folder) 
{
  hist_profile_2d.name = prefix + hist_profile_2d.name;
  if(hist_profile_2d.name != "" && check_name(hist_profile_2d.name)) {
    cout<<"Name \""<<hist_profile_2d.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TProfile2D(hist_profile_2d.name, 
			     hist_profile_2d.title,
			     hist_profile_2d.nbinx, 
			     hist_profile_2d.lowerx, 
			     hist_profile_2d.upperx,
			     hist_profile_2d.nbiny, 
			     hist_profile_2d.lowery, 
			     hist_profile_2d.uppery),
	      folder);
  hist_files_profile_2d.insert(make_pair(hist_profile_2d.name, HI));

  if(check_name(hist_profile_2d.name)) 
    hist_files_profile_2d[hist_profile_2d.name].get2DProfileHist()
      ->BuildOptions(hist_profile_2d.lowerz, 
		     hist_profile_2d.upperz, 
		     hist_profile_2d.profile_option);
}
void hist_files::add(HIST_PROFILE_2D* _hist_profile_2d, 
		     string prefix, string folder) 
{
  HIST_PROFILE_2D* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name!="" ) {
    add(*hist_profile_2d, prefix, folder);
    ++hist_profile_2d;
  }
}

// deal with 1D variable-bin-size histogram 
void hist_files::add(HIST_1D_VARBIN hist_1d, 
		     string prefix, string folder) 
{
  hist_1d.name = prefix + hist_1d.name;
  if(hist_1d.name != "" && check_name(hist_1d.name)) {
    cout<<"Name \""<<hist_1d.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TH1D(hist_1d.name, 
		       hist_1d.title,
		       hist_1d.nbin, 
		       hist_1d.binx),
	      folder);
  hist_files_1d.insert(make_pair(hist_1d.name, HI));
}
void hist_files::add(HIST_1D_VARBIN* _hist_1d, 
		     string prefix, string folder) 
{
  HIST_1D_VARBIN* hist_1d=_hist_1d;
  while( (*hist_1d).name != "" ) {
    add(*hist_1d, prefix, folder);
    ++hist_1d;
  }
}

// deal with 2D variable-bin-size histograms 
// (all 3 types: X-only, Y-only, both X&Y)
void hist_files::add(HIST_2D_VARBIN_X hist_2d, 
		     string prefix, string folder) 
{
  hist_2d.name = prefix + hist_2d.name;
  if(hist_2d.name != "" && check_name(hist_2d.name)) {
    cout<<"Name \""<<hist_2d.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TH2D(hist_2d.name, 
		       hist_2d.title,
		       hist_2d.nbinx, 
		       hist_2d.binx,
		       hist_2d.nbiny, 
		       hist_2d.lowery, 
		       hist_2d.uppery),
	      folder);
  hist_files_2d.insert(make_pair(hist_2d.name, HI));
}
void hist_files::add(HIST_2D_VARBIN_X* _hist_2d, 
		     string prefix, string folder) 
{
  HIST_2D_VARBIN_X* hist_2d=_hist_2d;
  while( (*hist_2d).name!="" ) {
    add(*hist_2d, prefix, folder);
    ++hist_2d;
  }
}
void hist_files::add(HIST_2D_VARBIN_Y hist_2d, 
		     string prefix, string folder) 
{
  hist_2d.name = prefix + hist_2d.name;
  if(hist_2d.name != "" && check_name(hist_2d.name)) {
    cout<<"Name \""<<hist_2d.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TH2D(hist_2d.name, 
		       hist_2d.title,
		       hist_2d.nbinx, 
		       hist_2d.lowerx, 
		       hist_2d.upperx,
		       hist_2d.nbiny, 
		       hist_2d.biny),
	      folder);
  hist_files_2d.insert(make_pair(hist_2d.name, HI));
}
void hist_files::add(HIST_2D_VARBIN_Y* _hist_2d, 
		     string prefix, string folder)
{
  HIST_2D_VARBIN_Y* hist_2d=_hist_2d;
  while( (*hist_2d).name!="" ) {
    add(*hist_2d, prefix, folder);
    ++hist_2d;
  }
}
void hist_files::add(HIST_2D_VARBIN_XY hist_2d, 
		     string prefix, string folder)
{
  hist_2d.name = prefix + hist_2d.name;
  if(hist_2d.name != "" && check_name(hist_2d.name)) {
    cout<<"Name \""<<hist_2d.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TH2D(hist_2d.name, 
		       hist_2d.title,
		       hist_2d.nbinx, 
		       hist_2d.binx,
		       hist_2d.nbiny, 
		       hist_2d.biny),
	      folder);
  hist_files_2d.insert(make_pair(hist_2d.name, HI));
}
void hist_files::add(HIST_2D_VARBIN_XY* _hist_2d, 
		     string prefix, string folder)
{
  HIST_2D_VARBIN_XY* hist_2d=_hist_2d;
  while( (*hist_2d).name!="" ) {
    add(*hist_2d, prefix, folder);
    ++hist_2d;
  }
}
// deal with variable-bin-size Profile
void hist_files::add(HIST_PROFILE_VARBIN hist_profile, 
		     string prefix, string folder) 
{
  hist_profile.name = prefix + hist_profile.name;
  if(hist_profile.name != "" && check_name(hist_profile.name)) {
    cout<<"Name \""<<hist_profile.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TProfile(hist_profile.name, 
			   hist_profile.title,
			   hist_profile.nbinx, 
			   hist_profile.binx,
			   hist_profile.lowery, 
			   hist_profile.uppery, 
			   hist_profile.profile_option),
	      folder);
  hist_files_profile.insert(make_pair(hist_profile.name, HI));
}
void hist_files::add(HIST_PROFILE_VARBIN* _hist_profile, 
		     string prefix, string folder) 
{
  HIST_PROFILE_VARBIN* hist_profile=_hist_profile;
  while( (*hist_profile).name!="" ) {
    add(*hist_profile, prefix, folder);
    ++hist_profile;
  }
}

// deal with 2D variable-bin-size Profile 
// (all 3 types: X-only, Y-only, both X&Y)
void hist_files::add(HIST_PROFILE_2D_VARBIN_X hist_profile_2d, 
		     string prefix, string folder) 
{
  hist_profile_2d.name = prefix + hist_profile_2d.name;
  if(hist_profile_2d.name != "" && check_name(hist_profile_2d.name)) {
    cout<<"Name \""<<hist_profile_2d.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TProfile2D(hist_profile_2d.name, 
			     hist_profile_2d.title,
			     hist_profile_2d.nbinx, 
			     hist_profile_2d.binx,
			     hist_profile_2d.nbiny, 
			     hist_profile_2d.lowery, 
			     hist_profile_2d.uppery),
	      folder);
  hist_files_profile_2d.insert(make_pair(hist_profile_2d.name, HI));

  if(check_name(hist_profile_2d.name)) 
    hist_files_profile_2d[hist_profile_2d.name].get2DProfileHist()
      ->BuildOptions(hist_profile_2d.lowerz, 
		     hist_profile_2d.upperz, 
		     hist_profile_2d.profile_option);
}
void hist_files::add(HIST_PROFILE_2D_VARBIN_X* _hist_profile_2d, 
		     string prefix, string folder) 
{
  HIST_PROFILE_2D_VARBIN_X* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name!="" ) {
    add(*hist_profile_2d, prefix, folder);
    ++hist_profile_2d;
  }
}
void hist_files::add(HIST_PROFILE_2D_VARBIN_Y hist_profile_2d, 
		     string prefix, string folder) 
{
  hist_profile_2d.name = prefix + hist_profile_2d.name;
  if(hist_profile_2d.name != "" && check_name(hist_profile_2d.name)) {
    cout<<"Name \""<<hist_profile_2d.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TProfile2D(hist_profile_2d.name, 
			     hist_profile_2d.title,
			     hist_profile_2d.nbinx, 
			     hist_profile_2d.lowerx, 
			     hist_profile_2d.upperx,
			     hist_profile_2d.nbiny, 
			     hist_profile_2d.biny),
	      folder);
  hist_files_profile_2d.insert(make_pair(hist_profile_2d.name, HI));

  if(check_name(hist_profile_2d.name)) 
    hist_files_profile_2d[hist_profile_2d.name].get2DProfileHist()
      ->BuildOptions(hist_profile_2d.lowerz, 
		     hist_profile_2d.upperz, 
		     hist_profile_2d.profile_option);
}
void hist_files::add(HIST_PROFILE_2D_VARBIN_Y* _hist_profile_2d, 
		     string prefix, string folder) 
{
  HIST_PROFILE_2D_VARBIN_Y* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name!="" ) {
    add(*hist_profile_2d, prefix, folder);
    ++hist_profile_2d;
  }
}
void hist_files::add(HIST_PROFILE_2D_VARBIN_XY hist_profile_2d, 
		     string prefix, string folder) 
{
  hist_profile_2d.name = prefix + hist_profile_2d.name;
  if(hist_profile_2d.name != "" && check_name(hist_profile_2d.name)) {
    cout<<"Name \""<<hist_profile_2d.name<<"\" already exists!"<<endl;
    return;
  }
  histInfo HI(new TProfile2D(hist_profile_2d.name, 
			     hist_profile_2d.title,
			     hist_profile_2d.nbinx, 
			     hist_profile_2d.binx,
			     hist_profile_2d.nbiny, 
			     hist_profile_2d.biny),
	      folder);
  hist_files_profile_2d.insert(make_pair(hist_profile_2d.name, HI));

  if(check_name(hist_profile_2d.name)) 
    hist_files_profile_2d[hist_profile_2d.name].get2DProfileHist()
      ->BuildOptions(hist_profile_2d.lowerz, 
		     hist_profile_2d.upperz, 
		     hist_profile_2d.profile_option);
}
void hist_files::add(HIST_PROFILE_2D_VARBIN_XY* _hist_profile_2d, 
		     string prefix, string folder) 
{
  HIST_PROFILE_2D_VARBIN_XY* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name!="" ) {
    add(*hist_profile_2d, prefix, folder);
    ++hist_profile_2d;
  }
}

/////////////////////////////////////////////////
////       Clone Histograms or Profiles       ///
/////////////////////////////////////////////////

// this function will make n copies of a histogram with name hist_name
// the name of each copy is hist_name_i (for i=0, ... n)
void hist_files::clone(TString hist_name, const int n, TString suffix_name) {
  if( !check_name(hist_name) ) {
    cout<<"Can't make clones of non-existing histogram \""<<hist_name
	<<"\""<<endl;
    return;
  }
  // cout<<"Name "<<hist_name<<" exists in the list"<<endl<<flush;

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

    // cout<<"Cloning "<<hist_name<<" into "<<hist_name+SN<<endl<<flush;
    clone(hist_name,hist_name+SN,get_title(hist_name)+" ["+(SN.Data()+1)+"]");

  } // loop over n
}

void hist_files::clone(HIST_1D hist_1d, int n, TString suffix_name) {
  if(hist_files_1d.find(hist_1d.name)==hist_files_1d.end()) {
    cout<<"No such histogram as "<<hist_1d.name<<endl;
    add(hist_1d);
    cout<<"Added "<<hist_1d.name<<" into the hist list.";
  }
  clone(hist_1d.name, n, suffix_name);
}
void hist_files::clone(HIST_1D* _hist_1d, int n, TString suffix_name)
{
  HIST_1D* hist_1d=_hist_1d;
  while( (*hist_1d).name != "" ) {
    clone(*hist_1d, n, suffix_name);
    ++hist_1d;
  }
}

void hist_files::clone(HIST_2D hist_2d, int n, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end()) {
    cout<<"No such histogram as "<<hist_2d.name<<endl;
    add(hist_2d);
    cout<<"Added "<<hist_2d.name<<" into the hist list.";
  }
  clone(hist_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_2D* _hist_2d, int n, TString suffix_name)
{
  HIST_2D* hist_2d=_hist_2d;
  while( (*hist_2d).name != "" ) {
    clone(*hist_2d, n, suffix_name);
    ++hist_2d;
  }
}

void hist_files::clone(HIST_PROFILE hist_profile, int n, TString suffix_name) {
  if(hist_files_profile.find(hist_profile.name)==hist_files_profile.end()) {
    cout<<"No such histogram as "<<hist_profile.name<<endl;
    add(hist_profile);
    cout<<"Added "<<hist_profile.name<<" into the hist list.";
  }
  clone(hist_profile.name, n, suffix_name);
}
void hist_files::clone(HIST_PROFILE* _hist_profile, int n, TString suffix_name)
{
  HIST_PROFILE* hist_profile=_hist_profile;
  while( (*hist_profile).name != "" ) {
    clone(*hist_profile, n, suffix_name);
    ++hist_profile;
  }
}

void hist_files::clone(HIST_PROFILE_2D hist_profile_2d, int n, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end()) {
    cout<<"No such histogram as "<<hist_profile_2d.name<<endl;
    add(hist_profile_2d);
    cout<<"Added "<<hist_profile_2d.name<<" into the hist list.";
  }
  clone(hist_profile_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_PROFILE_2D* _hist_profile_2d, int n, TString suffix_name)
{
  HIST_PROFILE_2D* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name != "" ) {
    clone(*hist_profile_2d, n, suffix_name);
    ++hist_profile_2d;
  }
}

void hist_files::clone(HIST_1D_VARBIN hist_1d, int n, TString suffix_name) {
  if(hist_files_1d.find(hist_1d.name)==hist_files_1d.end()) {
    cout<<"No such histogram as "<<hist_1d.name<<endl;
    add(hist_1d);
    cout<<"Added "<<hist_1d.name<<" into the hist list.";
  }
  clone(hist_1d.name, n, suffix_name);
}
void hist_files::clone(HIST_1D_VARBIN* _hist_1d, int n, TString suffix_name)
{
  HIST_1D_VARBIN* hist_1d=_hist_1d;
  while( (*hist_1d).name != "" ) {
    clone(*hist_1d, n, suffix_name);
    ++hist_1d;
  }
}

void hist_files::clone(HIST_2D_VARBIN_X hist_2d, int n, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end()) {
    cout<<"No such histogram as "<<hist_2d.name<<endl;
    add(hist_2d);
    cout<<"Added "<<hist_2d.name<<" into the hist list.";
  }
  clone(hist_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_2D_VARBIN_X* _hist_2d, int n, TString suffix_name)
{
  HIST_2D_VARBIN_X* hist_2d=_hist_2d;
  while( (*hist_2d).name != "" ) {
    clone(*hist_2d, n, suffix_name);
    ++hist_2d;
  }
}

void hist_files::clone(HIST_2D_VARBIN_Y hist_2d, int n, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end()) {
    cout<<"No such histogram as "<<hist_2d.name<<endl;
    add(hist_2d);
    cout<<"Added "<<hist_2d.name<<" into the hist list.";
  }
  clone(hist_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_2D_VARBIN_Y* _hist_2d, int n, TString suffix_name)
{
  HIST_2D_VARBIN_Y* hist_2d=_hist_2d;
  while( (*hist_2d).name != "" ) {
    clone(*hist_2d, n, suffix_name);
    ++hist_2d;
  }
}

void hist_files::clone(HIST_2D_VARBIN_XY hist_2d, int n, TString suffix_name) {
  if(hist_files_2d.find(hist_2d.name)==hist_files_2d.end()) {
    cout<<"No such histogram as "<<hist_2d.name<<endl;
    add(hist_2d);
    cout<<"Added "<<hist_2d.name<<" into the hist list.";
  }
  clone(hist_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_2D_VARBIN_XY* _hist_2d, int n, TString suffix_name)
{
  HIST_2D_VARBIN_XY* hist_2d=_hist_2d;
  while( (*hist_2d).name != "" ) {
    clone(*hist_2d, n, suffix_name);
    ++hist_2d;
  }
}

void hist_files::clone(HIST_PROFILE_VARBIN hist_profile, int n, TString suffix_name) {
  if(hist_files_profile.find(hist_profile.name)==hist_files_profile.end()) {
    cout<<"No such histogram as "<<hist_profile.name<<endl;
    add(hist_profile);
    cout<<"Added "<<hist_profile.name<<" into the hist list.";
  }
  clone(hist_profile.name, n, suffix_name);
}
void hist_files::clone(HIST_PROFILE_VARBIN* _hist_profile, int n, TString suffix_name)
{
  HIST_PROFILE_VARBIN* hist_profile=_hist_profile;
  while( (*hist_profile).name != "" ) {
    clone(*hist_profile, n, suffix_name);
    ++hist_profile;
  }
}

void hist_files::clone(HIST_PROFILE_2D_VARBIN_X hist_profile_2d, int n, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end()) {
    cout<<"No such histogram as "<<hist_profile_2d.name<<endl;
    add(hist_profile_2d);
    cout<<"Added "<<hist_profile_2d.name<<" into the hist list.";
  }
  clone(hist_profile_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_PROFILE_2D_VARBIN_X* _hist_profile_2d, int n, TString suffix_name)
{
  HIST_PROFILE_2D_VARBIN_X* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name != "" ) {
    clone(*hist_profile_2d, n, suffix_name);
    ++hist_profile_2d;
  }
}

void hist_files::clone(HIST_PROFILE_2D_VARBIN_Y hist_profile_2d, int n, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end()) {
    cout<<"No such histogram as "<<hist_profile_2d.name<<endl;
    add(hist_profile_2d);
    cout<<"Added "<<hist_profile_2d.name<<" into the hist list.";
  }
  clone(hist_profile_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_PROFILE_2D_VARBIN_Y* _hist_profile_2d, int n, TString suffix_name)
{
  HIST_PROFILE_2D_VARBIN_Y* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name != "" ) {
    clone(*hist_profile_2d, n, suffix_name);
    ++hist_profile_2d;
  }
}

void hist_files::clone(HIST_PROFILE_2D_VARBIN_XY hist_profile_2d, int n, TString suffix_name) {
  if(hist_files_profile_2d.find(hist_profile_2d.name)==hist_files_profile_2d.end()) {
    cout<<"No such histogram as "<<hist_profile_2d.name<<endl;
    add(hist_profile_2d);
    cout<<"Added "<<hist_profile_2d.name<<" into the hist list.";
  }
  clone(hist_profile_2d.name, n, suffix_name);
}
void hist_files::clone(HIST_PROFILE_2D_VARBIN_XY* _hist_profile_2d, int n, TString suffix_name)
{
  HIST_PROFILE_2D_VARBIN_XY* hist_profile_2d=_hist_profile_2d;
  while( (*hist_profile_2d).name != "" ) {
    clone(*hist_profile_2d, n, suffix_name);
    ++hist_profile_2d;
  }
}

// This function will make 1 copy of a histogram with name hist_name
// The name and title are of this copy are given by 'hist_name_new'
// and 'hist_title_new' strings respectively. If hist_title_new="", then
// the title will be copied from 'hist_name_new'.
void hist_files::clone(TString hist_name, 
		       TString hist_name_new, 
		       TString hist_title_new) {

  if( !check_name(hist_name) ) {
    cout<<"Can't make clones of non-existing histogram \""
	<<hist_name<<"\""<<endl;
    return;
  }
  if( check_name(hist_name_new) ) {
    cout<<"Name \""<<hist_name_new<<"\" already exists!"<<endl;
    return;
  }
  if( hist_title_new==TString("") ) hist_title_new=hist_name_new;
  
//   cout<<"hist_files::clone:  hist_name="<<hist_name
//       <<", hist_name_new="<<hist_name_new
//       <<", hist_title_new="<<hist_title_new
//       <<endl<<flush;

  if(hist_files_1d.find(hist_name)!=hist_files_1d.end()) {
    
    histInfo HI( (hist_files_1d[hist_name].get1DHist()
		  ->GetXaxis()->GetXbins()->GetSize() ? 
		  /* X axis - variable bin size */
		  new TH1D(hist_name_new, 
			   hist_title_new,
			   hist_files_1d[hist_name].get1DHist()->GetNbinsX(),
			   hist_files_1d[hist_name].get1DHist()->GetXaxis()
			   ->GetXbins()->GetArray()) :
		  /* X axis - same bin size */
		  new TH1D(hist_name_new, 
			   hist_title_new,
			   hist_files_1d[hist_name].get1DHist()->GetNbinsX(),
			   hist_files_1d[hist_name].get1DHist()->GetXaxis()
			   ->GetXmin(),
			   hist_files_1d[hist_name].get1DHist()->GetXaxis()
			   ->GetXmax()) ),
		 hist_files_1d.find(hist_name)->second.getFolder());
    hist_files_1d.insert(make_pair(hist_name_new, HI));
  }
  
  if(hist_files_2d.find(hist_name)!=hist_files_2d.end()) {

    histInfo HI( (hist_files_2d[hist_name].get2DHist()
		  ->GetXaxis()->GetXbins()->GetSize() ?
		  (hist_files_2d[hist_name].get2DHist()
		   ->GetYaxis()->GetXbins()->GetSize() ?
		   /* X axis - variable bin size */
		   /* Y axis - variable bin size */
		   new TH2D(hist_name_new, 
			    hist_title_new,
			    hist_files_2d[hist_name].get2DHist()->GetNbinsX(),
			    hist_files_2d[hist_name].get2DHist()->GetXaxis()
			    ->GetXbins()->GetArray(),
			    hist_files_2d[hist_name].get2DHist()->GetNbinsY(),
			    hist_files_2d[hist_name].get2DHist()->GetYaxis()
			    ->GetXbins()->GetArray()) :
		   /* X axis - variable bin size */
		   /* Y axis - same bin size */
		   new TH2D(hist_name_new, 
			    hist_title_new,
			    hist_files_2d[hist_name].get2DHist()->GetNbinsX(),
			    hist_files_2d[hist_name].get2DHist()->GetXaxis()
			    ->GetXbins()->GetArray(),
			    hist_files_2d[hist_name].get2DHist()->GetNbinsY(),
			    hist_files_2d[hist_name].get2DHist()->GetYaxis()
			    ->GetXmin(),
			    hist_files_2d[hist_name].get2DHist()->GetYaxis()
			    ->GetXmax()) ) :
		  (hist_files_2d[hist_name].get2DHist()
		   ->GetYaxis()->GetXbins()->GetSize() ?
		   /* X axis - same bin size */
		   /* Y axis - variable bin size */
		   new TH2D(hist_name_new, 
			    hist_title_new,
			    hist_files_2d[hist_name].get2DHist()->GetNbinsX(),
			    hist_files_2d[hist_name].get2DHist()->GetXaxis()
			    ->GetXmin(),
			    hist_files_2d[hist_name].get2DHist()->GetXaxis()
			    ->GetXmax(),
			    hist_files_2d[hist_name].get2DHist()->GetNbinsY(),
			    hist_files_2d[hist_name].get2DHist()->GetYaxis()
			    ->GetXbins()->GetArray()) :
		   /* X axis - same bin size */
		   /* Y axis - same bin size */
		   new TH2D(hist_name_new, 
			    hist_title_new,
			    hist_files_2d[hist_name].get2DHist()->GetNbinsX(),
			    hist_files_2d[hist_name].get2DHist()->GetXaxis()
			    ->GetXmin(),
			    hist_files_2d[hist_name].get2DHist()->GetXaxis()
			    ->GetXmax(),
			    hist_files_2d[hist_name].get2DHist()->GetNbinsY(),
			    hist_files_2d[hist_name].get2DHist()->GetYaxis()
			    ->GetXmin(),
			    hist_files_2d[hist_name].get2DHist()->GetYaxis()
			    ->GetXmax()))),
		 hist_files_2d.find(hist_name)->second.getFolder());
    hist_files_2d.insert(make_pair(hist_name_new, HI));
  }
  
  if(hist_files_profile.find(hist_name)!=hist_files_profile.end()) {

    histInfo HI( (hist_files_profile[hist_name].getProfileHist()
		  ->GetXaxis()->GetXbins()->GetSize() ?
		  /* X axis - variable bin size */
		  new TProfile(hist_name_new, 
			       hist_title_new,
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetNbinsX(),
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetXaxis()->GetXbins()->GetArray(),
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetYmin(),
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetYmax(), 
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetErrorOption()) :
		  /* X axis - same bin size */
		  new TProfile(hist_name_new, 
			       hist_title_new,
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetNbinsX(),
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetXaxis()->GetXmin(),
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetXaxis()->GetXmax(),
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetYmin(),
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetYmax(), 
			       hist_files_profile[hist_name].getProfileHist()
			       ->GetErrorOption())),
		 hist_files_profile.find(hist_name)->second.getFolder());
    hist_files_profile.insert(make_pair(hist_name_new, HI));
  }

  if(hist_files_profile_2d.find(hist_name)!=hist_files_profile_2d.end()) {

    histInfo HI((hist_files_profile_2d[hist_name].get2DProfileHist()
		 ->GetXaxis()->GetXbins()->GetSize() ?
		 (hist_files_profile_2d[hist_name].get2DProfileHist()
		  ->GetYaxis()->GetXbins()->GetSize() ?
		  /* X axis - variable bin size */
		  /* Y axis - variable bin size */
		  new TProfile2D
		  (hist_name_new, 
		   hist_title_new,
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetNbinsX(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetXaxis()->GetXbins()->GetArray(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetNbinsY(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetYaxis()->GetXbins()->GetArray()) :
		  /* X axis - variable bin size */
		  /* Y axis - same bin size */
		  new TProfile2D
		  (hist_name_new, 
		   hist_title_new,
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetNbinsX(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetXaxis()->GetXbins()->GetArray(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetNbinsY(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetYaxis()->GetXmin(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetYaxis()->GetXmax()) ) :
		 (hist_files_profile_2d[hist_name].get2DProfileHist()
		  ->GetYaxis()->GetXbins()->GetSize() ?
		  /* X axis - same bin size */
		  /* Y axis - variable bin size */
		  new TProfile2D
		  (hist_name_new, 
		   hist_title_new,
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetNbinsX(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetXaxis()->GetXmin(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetXaxis()->GetXmax(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetNbinsY(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetYaxis()->GetXbins()->GetArray()) :
		  /* X axis - same bin size */
		  /* Y axis - same bin size */
		  new TProfile2D
		  (hist_name_new, 
		   hist_title_new,
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetNbinsX(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetXaxis()->GetXmin(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetXaxis()->GetXmax(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetNbinsY(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetYaxis()->GetXmin(),
		   hist_files_profile_2d[hist_name].get2DProfileHist()
		   ->GetYaxis()->GetXmax()))),
		hist_files_profile_2d.find(hist_name)->second.getFolder());
    hist_files_profile_2d.insert(make_pair(hist_name_new, HI));
    if(check_name(hist_name_new)) 
      hist_files_profile_2d[hist_name_new].get2DProfileHist()
	->BuildOptions(hist_files_profile_2d[hist_name].get2DProfileHist()
		       ->GetZmin(), 
		       hist_files_profile_2d[hist_name].get2DProfileHist()
		       ->GetZmax(), 
		       hist_files_profile_2d[hist_name].get2DProfileHist()
		       ->GetErrorOption());
  }
}

////////////////////////////////////////////////////////////////////////////////
// this function will make nx * ny copies of a histogram with name hist_name
// the name of each copy is hist_name_ij (for i=0, ... nx and j=0, ... ny)
// only works for j<10
////////////////////////////////////////////////////////////////////////////////
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

      clone(hist_name,hist_name+SN,get_title(hist_name)+" ["+(SN.Data()+1)+"]");

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
void hist_files::SumWeight(){
  
  for(map<TString, histInfo>::iterator it_1d = hist_files_1d.begin();
      it_1d != hist_files_1d.end(); it_1d++) 
    (*it_1d).second.get1DHist()->Sumw2();
  
  for(map<TString, histInfo>::iterator it_2d = hist_files_2d.begin();
      it_2d != hist_files_2d.end(); it_2d++) 
    (*it_2d).second.get2DHist()->Sumw2();
 
  /*
  // for profile, need to set error option in order to let root calculate
  // uncertainties correctly 
  for(map<TString, histInfo>::iterator it_profile = hist_files_profile.begin();
      it_profile != hist_files_profile.end(); it_profile++)  
    (*it_profile).second.getProfileHist()->SetErrorOption("i");
  for(map<TString, histInfo>::iterator 
  it_profile_2d = hist_files_profile_2d.begin();
        it_profile_2d != hist_files_profile_2d.end(); it_profile_2d++)  
      (*it_profile_2d).second.get2DProfileHist()->SetErrorOption("i");
  */
  /* Do not change ErrorOption for TProfile nad TProfile2D here.
     Let the user decide about error options he/she prefers during 
     profile histograms declaration in 'histograms.hpp' file.
     MC -- June 7, 2007
  */

}

void hist_files::Fill1D(TString hist_name, double x, double weight) {
  if(hist_files_1d[hist_name].get1DHist()) 
    hist_files_1d[hist_name].get1DHist()->Fill(x, weight);
}

void hist_files::Fill2D(TString hist_name, double x, double y, double weight) {
  if(hist_files_2d[hist_name].get2DHist()) 
    hist_files_2d[hist_name].get2DHist()->Fill(x, y, weight);
}

void hist_files::FillProfile(TString hist_name, double x, double y, double weight) {
  if(hist_files_profile[hist_name].getProfileHist()) 
    hist_files_profile[hist_name].getProfileHist()->Fill(x, y, weight);
}

void hist_files::FillProfile2D(TString hist_name, double x, double y, double z, double weight) {
  if(hist_files_profile_2d[hist_name].get2DProfileHist()) 
    hist_files_profile_2d[hist_name].get2DProfileHist()->Fill(x, y, z, weight);
}

////////////////////////////////////////////////////////////
////  Normalize selected variable-bin-width histograms  ////
////////////////////////////////////////////////////////////
void hist_files::NormalizeVarBinHistograms() {

  if(NormalizeVarBinHistograms_done) return;

  cout<<"hist_files::NormalizeVarBinHistograms: "
      <<"Calculating # evts per bin width for variable-bin-histograms" << endl;
  NormalizeVarBinHistograms_done=true;
  
  // deal with 1D histograms
  for(map<TString, histInfo>::iterator it_1d = hist_files_1d.begin(); 
      it_1d != hist_files_1d.end(); it_1d++) 
    if (it_1d->first != "" && it_1d->second.get1DHist() != NULL) {
      
      map<TString, const Bool_t>::iterator it_per_bin;
      if((it_per_bin=evts_per_bin_width_hist_1d.find(it_1d->first)) != evts_per_bin_width_hist_1d.end() &&
	 it_per_bin->second ) {
	
	// NOTE: BIN(0) is for UNDEFRLOWS, BIN(NBINS+1) is for OVERFLOWS
	for(Int_t ibinX=1; ibinX<=it_1d->second.get1DHist()->GetNbinsX(); ibinX++) {
	  double widthX = it_1d->second.get1DHist()->GetBinWidth(ibinX);
	  double    val = it_1d->second.get1DHist()->GetBinContent(ibinX);
	  double    err = it_1d->second.get1DHist()->GetBinError(ibinX);
	  if( widthX>0.0 ) {
	    val/=widthX;
	    err/=widthX;
	    it_1d->second.get1DHist()->SetBinContent(ibinX,val);
	    it_1d->second.get1DHist()->SetBinError(ibinX,err);
	  }
	}
	it_1d->second.get1DHist()->Sumw2();	
      }
    } // end of loop through 1D histograms
  
  // deal with 2D histograms
  for(map<TString, histInfo>::iterator it_2d = hist_files_2d.begin(); 
      it_2d != hist_files_2d.end(); it_2d++) 
    if (it_2d->first != "" && it_2d->second.get2DHist() != NULL) {
      
      map<TString, const vector<Bool_t> >::iterator it_per_bin;
      if((it_per_bin=evts_per_bin_width_hist_2d.find(it_2d->first)) != evts_per_bin_width_hist_2d.end() ) {
	
	// check X-axis
	const Bool_t do_X = it_per_bin->second[0];
	const Bool_t do_Y = it_per_bin->second[1];
	if(do_X || do_Y) {	
	  // NOTE: BIN(0) is for UNDEFRLOWS, BIN(NBINS+1) is for OVERFLOWS
	  for(Int_t ibinX=1; ibinX<=it_2d->second.get2DHist()->GetNbinsX(); ibinX++) 
	    for(Int_t ibinY=1; ibinY<=it_2d->second.get2DHist()->GetNbinsY(); ibinY++) {
	      double widthX = it_2d->second.get2DHist()->GetXaxis()->GetBinWidth(ibinX);
	      double widthY = it_2d->second.get2DHist()->GetYaxis()->GetBinWidth(ibinY);
	      double    val = it_2d->second.get2DHist()->GetBinContent(ibinX,ibinY);
	      double    err = it_2d->second.get2DHist()->GetBinError(ibinX,ibinY);
	      if( do_X && widthX>0.0 ) {
		val/=widthX;
		err/=widthX;
	      }
	      if( do_Y && widthY>0.0 ) {
		val/=widthY;
		err/=widthY;
	      }
	      it_2d->second.get2DHist()->SetBinContent(ibinX,ibinY,val);
	      it_2d->second.get2DHist()->SetBinError(ibinX,ibinY,err);
	    } // end of looping through all the bins
	  it_2d->second.get2DHist()->Sumw2();	
	}
      } 
    }  // end of loop through 2D histograms
}

/////////////////////////////////////////////////
////        Save Histograms or Profiles       ///
/////////////////////////////////////////////////
void hist_files::save(const char* root_name, bool ps, bool debug, vector<TObject*>* otherStuff) {

  // skip saving if histograms do not exist!
  if( size()==0 ) return;

  NormalizeVarBinHistograms();

  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetOptStat(111111);

  TCanvas c1;
  TFile *hist = new TFile(root_name, "RECREATE");
  cout << "Saving histograms to file " << hist->GetPath() << endl;

  if (debug) cout << "hist_files::save: 1D_HISTOS=" 
		  << size1D() << endl << flush;
  for(map<TString, histInfo>::iterator it_1d = hist_files_1d.begin(); 
      it_1d != hist_files_1d.end(); it_1d++) { 
    if ((*it_1d).first != "" && (*it_1d).second.get1DHist() != NULL) {
      if (debug) cout << "hist_files::save: 1D_NAME=" 
		      << ((*it_1d).second.get1DHist())->GetName() 
		      << endl << flush;

      string folder = ((*it_1d).second).getFolder();
      if (folder == "") {folder = "default";}
      
      TDIRECTORY *dir = (TDIRECTORY *)gDirectory->Get(folder.c_str());
      if (!dir) {
	dir = new TDIRECTORY(folder.c_str(),folder.c_str());
      }
      //dir->SetDirectory(hist);
      dir->cd();
      
      TString fn = ((*it_1d).second.get1DHist())->GetName(); 
      fn = fn + ".ps";
      ((*it_1d).second).get1DHist()->Draw();
      ((*it_1d).second).get1DHist()->Write();
      if(ps) c1.Print(fn);
      
      dir->Write();
      hist->cd();
    }
  }
  
  if (debug) cout << "hist_files::save: 2D_HISTOS=" 
		  << size2D() << endl << flush;
  for(map<TString, histInfo>::iterator it_2d = hist_files_2d.begin();
      it_2d != hist_files_2d.end(); it_2d++) {
    if ((*it_2d).first != "" && (*it_2d).second.get2DHist() != NULL) {
      if (debug) cout << "hist_files::save: 2D_NAME=" 
		      << ((*it_2d).second).get2DHist()->GetName() 
		      << endl << flush;
      
      string folder = ((*it_2d).second).getFolder();
      if (folder == "") {folder = "default";}
      
      TDIRECTORY *dir = (TDIRECTORY *)gDirectory->Get(folder.c_str());
      if (!dir) {
	dir = new TDIRECTORY(folder.c_str(),folder.c_str());
      }
      dir->cd();

      TString fn = ((*it_2d).second).get2DHist()->GetName(); 
      fn = fn + ".ps";
      ((*it_2d).second).get2DHist()->Draw();
      ((*it_2d).second).get2DHist()->Write();
      if(ps) c1.Print(fn);
      
      dir->Write();
      hist->cd();
    }
  }

  if (debug) cout << "hist_files::save: PROFILE_HISTOS=" 
		  << sizeProfile() << endl << flush;
  for(map<TString, histInfo>::iterator it_profile = hist_files_profile.begin();
      it_profile != hist_files_profile.end(); it_profile++) {
    if ((*it_profile).first != "" && 
	(*it_profile).second.getProfileHist() != NULL) {
      if (debug) cout << "hist_files::save: PROFILE_NAME=" 
		      << ((*it_profile).second).getProfileHist()->GetName() 
		      << endl << flush;

      string folder = ((*it_profile).second).getFolder();
      if (folder == "") {folder = "default";}
      
      TDIRECTORY *dir = (TDIRECTORY *)gDirectory->Get(folder.c_str());
      if (!dir) {
	dir = new TDIRECTORY(folder.c_str(),folder.c_str());
      }
      dir->cd();

      TString fn = ((*it_profile).second).getProfileHist()->GetName(); 
      fn = fn + ".ps";
      ((*it_profile).second).getProfileHist()->Draw();
      ((*it_profile).second).getProfileHist()->Write();
      if(ps) c1.Print(fn);

      dir->Write();
      hist->cd();
    }
  }

  if (debug) cout << "hist_files::save: PROFILE_2D_HISTOS=" 
		  << sizeProfile2D() << endl << flush;
  for(map<TString, histInfo>::iterator it_profile_2d = 
	hist_files_profile_2d.begin();
      it_profile_2d != hist_files_profile_2d.end(); it_profile_2d++) {
    if ((*it_profile_2d).first != "" && 
	(*it_profile_2d).second.get2DProfileHist() != NULL) {
      if (debug) cout << "hist_files::save: PROFILE_2D_NAME=" 
		      << ((*it_profile_2d).second).get2DProfileHist()->GetName() 
		      << endl << flush;

      string folder = ((*it_profile_2d).second).getFolder();
      if (folder == "") {folder = "default";}
      
      TDIRECTORY *dir = (TDIRECTORY *)gDirectory->Get(folder.c_str());
      if (!dir) {
	dir = new TDIRECTORY(folder.c_str(),folder.c_str());
      }
      dir->cd();

      TString fn = ((*it_profile_2d).second).get2DProfileHist()->GetName(); 
      fn = fn + ".ps";
      ((*it_profile_2d).second).get2DProfileHist()->Draw();
      ((*it_profile_2d).second).get2DProfileHist()->Write();
      if(ps) c1.Print(fn);

      dir->Write();
      hist->cd();
    }
  }

  if (otherStuff) {
    if (debug) cout << "hist_files::save: otherStuff=" << otherStuff->size() << endl << flush;
    for (Int_t i=0; i<otherStuff->size(); i++) {
      (*otherStuff)[i]->Write();
    }
  }

  hist->Close();  
  cout << "Done." << endl;
}
