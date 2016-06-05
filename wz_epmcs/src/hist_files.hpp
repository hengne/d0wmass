////////////////////////////////////////////////////////////////
///   File: Hist_file.hpp                                    ///
///   Created: J.Zhu. M.Cwiok -- June 7, 2007                ///
///            based on H. Dong's Code                       ///
///   Purpose: Define some functions for adding histograms   ///
///                                                          ///
////////////////////////////////////////////////////////////////

#ifndef HIST_FILES_HPP
#define HIST_FILES_HPP

#include <vector>
#include <map>
#include <string>
#include <sstream>
using std::map;
using std::vector;
using std::string;
using std::stringstream;

#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TString.h"
#include "TObject.h"

#include "hist_nd.hpp"

class histInfo {
 public:
  histInfo(TH1 *hist, std::string folder) : _hist(hist) , _folder(folder) {;}
  ~histInfo() {;}
  histInfo() {;}

  TH1D *get1DHist() {return (TH1D *)_hist;}
  TH2D *get2DHist() {return (TH2D *)_hist;}
  TProfile *getProfileHist() {return (TProfile *)_hist;}
  TProfile2D *get2DProfileHist() {return (TProfile2D *)_hist;}
  std::string getFolder() {return _folder;}

 private:
  TH1* _hist;
  std::string _folder;
};

class hist_files {
  
 public:
  hist_files();
  ~hist_files();
  
  bool check_name(TString hist_name);
  inline bool check_name(const char *hist_name) 
  { return check_name(TString(hist_name)); }
  inline bool check_name(const std::string hist_name) 
  { return check_name(TString(hist_name.c_str())); }

  TString get_title(TString hist_name);
  inline std::string get_title(std::string hist_name)
  { return static_cast<std::string>(get_title(TString(hist_name)).Data()); }
  inline const char* get_title(const char *hist_name) 
  { return get_title(TString(hist_name)).Data(); }
  
  // for same bin-size histograms
  void add(HIST_1D, 
	   std::string prefix = "", std::string folder = "");
  void add(HIST_1D*, 
	   std::string prefix = "", std::string folder = "");
  // for variable bin-size histograms
  void add(HIST_1D_VARBIN, 
	   std::string prefix = "", std::string folder = "");
  void add(HIST_1D_VARBIN*, 
	   std::string prefix = "", std::string folder = "");
  // for same bin-size 2D histograms
  void add(HIST_2D, 
	   std::string prefix = "", std::string folder = "");
  void add(HIST_2D*, 
	   std::string prefix = "", std::string folder = "");
  // for variable bin-size (X-axis only) 2D histograms 
  void add(HIST_2D_VARBIN_X, 
	   std::string prefix = "", std::string folder = "");
  void add(HIST_2D_VARBIN_X*, 
	   std::string prefix = "", std::string folder = "");
  // for variable bin-size (Y-axis only) 2D histograms 
  void add(HIST_2D_VARBIN_Y, 
	   std::string prefix = "", std::string folder = "");
  void add(HIST_2D_VARBIN_Y*, 
	   std::string prefix = "", std::string folder = "");
  // for variable bin-size (both axes) 2D histograms 
  void add(HIST_2D_VARBIN_XY, 
	   std::string prefix = "", std::string folder = "");
  void add(HIST_2D_VARBIN_XY*, 
	   std::string prefix = "", std::string folder = "");
  // for same bin-size profile histograms
  void add(HIST_PROFILE, 
	   std::string prefix = "", std::string folder = "");
  void add(HIST_PROFILE*, 
	   std::string prefix = "", std::string folder = "");
  // for variable bin-size profile histograms
  void add(HIST_PROFILE_VARBIN, 
	   std::string prefix = "", std::string folder = "");
  void add(HIST_PROFILE_VARBIN*, 
	   std::string prefix = "", std::string folder = "");
  // for same bin-size 2D profile histograms
  void add(HIST_PROFILE_2D, 
	   std::string prefix = "", std::string folder = "");           
  void add(HIST_PROFILE_2D*, 
	   std::string prefix = "", std::string folder = "");
  // for variable bin-size (X-axis only) 2D profile histograms 
  void add(HIST_PROFILE_2D_VARBIN_X, 
	   std::string prefix = "", std::string folder = "");  
  void add(HIST_PROFILE_2D_VARBIN_X*, 
	   std::string prefix = "", std::string folder = "");
  // for variable bin-size (Y-axis only) 2D profile histograms 
  void add(HIST_PROFILE_2D_VARBIN_Y, 
	   std::string prefix = "", std::string folder = "");
  void add(HIST_PROFILE_2D_VARBIN_Y*, 
	   std::string prefix = "", std::string folder = "");
  // for variable bin-size (both axes) 2D profile histograms 
  void add(HIST_PROFILE_2D_VARBIN_XY, 
	   std::string prefix = "", std::string folder = ""); 
  void add(HIST_PROFILE_2D_VARBIN_XY*, 
	   std::string prefix = "", std::string folder = "");

  // make one copy of a histogram specified by the 1st argument
  // name of the destination histogram is given by the 2nd argument
  void clone(TString hist_name, 
	     TString hist_name_new, 
	     TString hist_title_new="");
  // make n copies of a histogram (name hist_name)
  // each copy is names as hist_name_i (i from 1 to n)
  void clone(TString, int, TString suffix_name="");
  void clone(HIST_1D, int, TString suffix_name="");
  void clone(HIST_1D*, int, TString suffix_name="");
  void clone(HIST_1D_VARBIN, int, TString suffix_name="");
  void clone(HIST_1D_VARBIN*, int, TString suffix_name="");
  void clone(HIST_2D, int, TString suffix_name="");
  void clone(HIST_2D*, int, TString suffix_name="");
  void clone(HIST_2D_VARBIN_X, int, TString suffix_name="");
  void clone(HIST_2D_VARBIN_X*, int, TString suffix_name="");
  void clone(HIST_2D_VARBIN_Y, int, TString suffix_name="");
  void clone(HIST_2D_VARBIN_Y*, int, TString suffix_name="");
  void clone(HIST_2D_VARBIN_XY, int, TString suffix_name="");
  void clone(HIST_2D_VARBIN_XY*, int, TString suffix_name="");
  void clone(HIST_PROFILE, int, TString suffix_name="");
  void clone(HIST_PROFILE*, int, TString suffix_name="");
  void clone(HIST_PROFILE_VARBIN, int, TString suffix_name="");
  void clone(HIST_PROFILE_VARBIN*, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D*, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D_VARBIN_X, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D_VARBIN_X*, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D_VARBIN_Y, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D_VARBIN_Y*, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D_VARBIN_XY, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D_VARBIN_XY*, int, TString suffix_name="");
  
  // make nx*ny copies of a histogram (name hist_name)
  // each copy is names as hist_name_i_j (i from 0 to nx, j from 0 to ny)
  void cloneArray(TString, int, int, TString suffix_name="");
  void cloneArray(HIST_1D, int, int, TString suffix_name="");
  void cloneArray(HIST_1D_VARBIN, int, int, TString suffix_name="");
  void cloneArray(HIST_2D, int, int, TString suffix_name="");
  void cloneArray(HIST_2D_VARBIN_X, int, int, TString suffix_name="");
  void cloneArray(HIST_2D_VARBIN_Y, int, int, TString suffix_name="");
  void cloneArray(HIST_2D_VARBIN_XY, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE_VARBIN, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE_2D, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE_2D_VARBIN_X, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE_2D_VARBIN_Y, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE_2D_VARBIN_XY, int, int, TString suffix_name="");
  
  void SumWeight();  
  //  void fill(TString, Double_t);

  void Fill1D(TString, double x, double weight=1.); // fill 1D histogram with weight
  void Fill2D(TString, double x, double y, double weight=1.); // fill 2D histogram with weight
  void FillProfile(TString, double x, double y, double weight=1.); // fill profile with weight
  void FillProfile2D(TString, double x, double y, double z, double weight=1.); // fill 2D profile with weight
  
  void save(const char* root_name="hist.root", 
	    bool ps=false, bool debug=false, vector<TObject*>* otherStuff=0);
  inline long size1D() {      // # of 1D histograms
    return hist_files_1d.size();
  }
  inline long size2D() {      // # of 2D histograms
    return hist_files_2d.size();
  }
  inline long sizeProfile() { // # of PROFILE histograms
    return hist_files_profile.size();
  }
  inline long sizeProfile2D() { // # of 2D-PROFILE histograms
    return hist_files_profile_2d.size();
  }
  inline long size() {        // # of 1D + 2D + PROFILE + 2D-Profile histograms
    return size1D()+size2D()+sizeProfile()+sizeProfile2D();
  }

  TH1D* th1d(TString hist_name) {return hist_files_1d[hist_name].get1DHist();};
  TH2D* th2d(TString hist_name) {return hist_files_2d[hist_name].get2DHist();};
  TProfile*   tprofile(TString hist_name)   {return hist_files_profile[hist_name].getProfileHist();};
  TProfile2D* tprofile2d(TString hist_name) {return hist_files_profile_2d[hist_name].get2DProfileHist();};
  
 private:
  map<TString, histInfo> hist_files_1d;
  map<TString, histInfo> hist_files_2d;
  map<TString, histInfo> hist_files_profile;
  map<TString, histInfo> hist_files_profile_2d;
  map<TString, const Bool_t> evts_per_bin_width_hist_1d;
  map<TString, const vector<Bool_t> > evts_per_bin_width_hist_2d;
  void NormalizeVarBinHistograms();
  Bool_t NormalizeVarBinHistograms_done;
};

#endif
