////////////////////////////////////////////////////////////////
///   File: Hist_file.hpp                                    ///
///   Created: J. Zhu March 3, 2005                          ///
///            based on H. Dong's Code                       ///
///   Purpose: Define some functions for add histograms      ///
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
#include "TH3.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TString.h"

#include "wmass_util/hist_nd.hpp"
#include "cafe/Processor.hpp"

class hist_files {
  
 public:
  hist_files();
  ~hist_files();
  
  bool check_name(TString hist_name);
  inline bool check_name(const char *hist_name) {
    return check_name(TString(hist_name));
  }
  inline bool check_name(const std::string hist_name) {
    return check_name(TString(hist_name.c_str()));
  }
  
  void add(HIST_1D);
  void add(HIST_1D*,TString suffix_name="");
  void add(HIST_1D_VARBIN);    // for variable bin-size histograms
  void add(HIST_1D_VARBIN*);   // for variable bin-size histograms
  
  void add(HIST_2D);
  void add(HIST_2D*,TString suffix_name="");
  void add(HIST_2D_VARBIN_X);   // for variable bin-size histograms (X-axis only)
  void add(HIST_2D_VARBIN_X*);  // for variable bin-size histograms (X-axis only)
  void add(HIST_2D_VARBIN_Y);   // for variable bin-size histograms (Y-axis only)
  void add(HIST_2D_VARBIN_Y*);  // for variable bin-size histograms (Y-axis only)
  void add(HIST_2D_VARBIN_XY);  // for variable bin-size histograms (both axes)
  void add(HIST_2D_VARBIN_XY*); // for variable bin-size histograms (both axes)

  void add(HIST_3D);
  void add(HIST_3D*);

  void add(HIST_PROFILE);
  void add(HIST_PROFILE*);
  void add(HIST_PROFILE_VARBIN);  // for variable bin-size profile histograms
  void add(HIST_PROFILE_VARBIN*); // for variable bin-size profile histograms

  void add(HIST_PROFILE_2D);           // for 2D profile histograms
  void add(HIST_PROFILE_2D*);          // for 2D profile histograms
  void add(HIST_PROFILE_2D_VARBIN_X);  // for variable bin-size 2D profile histograms (X-axis only)
  void add(HIST_PROFILE_2D_VARBIN_X*); // for variable bin-size 2D profile histograms (X-axis only)
  void add(HIST_PROFILE_2D_VARBIN_Y);  // for variable bin-size 2D profile histograms (Y-axis only)
  void add(HIST_PROFILE_2D_VARBIN_Y*); // for variable bin-size 2D profile histograms (Y-axis only)
  void add(HIST_PROFILE_2D_VARBIN_XY); // for variable bin-size 2D profile histograms (both axes)
  void add(HIST_PROFILE_2D_VARBIN_XY*);// for variable bin-size 2D profile histograms (both axes)

  // make one copy of a histogram specified by the 1st argument
  // name of the destination histogram is given by the 2nd argument
  void clone(TString, TString);

  // make n copies of a histogram (name hist_name)
  // each copy is names as hist_name_i (i from 1 to n)
  void clone(TString, int, TString suffix_name="");
  //  void clone(TString, int, const char *suffix_name="");
  void clone(HIST_1D, int, TString suffix_name="");
  void clone(HIST_1D_VARBIN, int, TString suffix_name="");
  void clone(HIST_2D, int, TString suffix_name="");
  void clone(HIST_2D_VARBIN_X, int, TString suffix_name="");
  void clone(HIST_2D_VARBIN_Y, int, TString suffix_name="");
  void clone(HIST_2D_VARBIN_XY, int, TString suffix_name="");
  void clone(HIST_3D, int, TString suffix_name="");
  void clone(HIST_PROFILE, int, TString suffix_name="");
  void clone(HIST_PROFILE_VARBIN, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D_VARBIN_X, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D_VARBIN_Y, int, TString suffix_name="");
  void clone(HIST_PROFILE_2D_VARBIN_XY, int, TString suffix_name="");
  
  // make nx*ny copies of a histogram (name hist_name)
  // each copy is names as hist_name_i_j (i from 0 to nx, j from 0 to ny)
  void cloneArray(TString, int, int, TString suffix_name="");
  void cloneArray(HIST_1D, int, int, TString suffix_name="");
  void cloneArray(HIST_1D_VARBIN, int, int, TString suffix_name="");
  void cloneArray(HIST_2D, int, int, TString suffix_name="");
  void cloneArray(HIST_2D_VARBIN_X, int, int, TString suffix_name="");
  void cloneArray(HIST_2D_VARBIN_Y, int, int, TString suffix_name="");
  void cloneArray(HIST_2D_VARBIN_XY, int, int, TString suffix_name="");
  void cloneArray(HIST_3D, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE_VARBIN, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE_2D, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE_2D_VARBIN_X, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE_2D_VARBIN_Y, int, int, TString suffix_name="");
  void cloneArray(HIST_PROFILE_2D_VARBIN_XY, int, int, TString suffix_name="");
  
  //void fill(TString, Float_t);
  
  void Fill1D(TString, Float_t x, Float_t weight=1.); // fill 1D histogram with weight
  void Fill2D(TString, Float_t x, Float_t y, Float_t weight=1.); // fill 2D histogram with weight
  void Fill3D(TString, Float_t x, Float_t y, Float_t z, Float_t weight=1.); // fill 3D histogram 
  void FillProfile(TString, Float_t x, Float_t y, Float_t weight=1.); // fill profile with weight
  void FillProfile2D(TString, Float_t x, Float_t y, Float_t z, Float_t weight=1.); // fill 2D profile with weight
  
  void save(const char* root_name, bool ps=false, bool debug=false);
  void save(TFile* root_file, string directory_name="", bool debug=false);
  
  inline long size1D() {      // # of 1D histograms
    return hist_files_1d.size();
  }
  inline long size2D() {      // # of 2D histograms
    return hist_files_2d.size();
  }
  inline long size3D() {      // # of 3D histograms
    return hist_files_3d.size();
  }
  inline long sizeProfile() { // # of PROFILE histograms
    return hist_files_profile.size();
  }
  inline long sizeProfile2D() { // # of 2D-PROFILE histograms
    return hist_files_profile_2d.size();
  }
  inline long size() {        // # of 1D + 2D + 3D + PROFILE + 2D-Profile histograms
    return size1D()+size2D()+size3D()+sizeProfile()+sizeProfile2D();
  }

  TH1D* th1d(TString hist_name) {return hist_files_1d[hist_name];};
  TH2D* th2d(TString hist_name) {return hist_files_2d[hist_name];};
  TH3D* th3d(TString hist_name) {return hist_files_3d[hist_name];};
  TProfile*   tprofile(TString hist_name)   {return hist_files_profile[hist_name];};
  TProfile2D* tprofile2d(TString hist_name) {return hist_files_profile_2d[hist_name];};
  
 private:
  map<TString, TH1D*> hist_files_1d;
  map<TString, TH2D*> hist_files_2d;
  map<TString, TH3D*> hist_files_3d;
  map<TString, TProfile*> hist_files_profile;
  map<TString, TProfile2D*> hist_files_profile_2d;
};

namespace histfiles {

  // A family of histfiles::initializeTFile() methods allows multiple processors
  // to access same ROOTuples. It will either create or update
  // a given ROOTuple and will keep track of already 
  // opened ones troughout running of the 'cafe' program. 
  // The name of ROOTuple to be created/updated can be specified by "<processor_name>.Output"
  // field in the "cafe.config" file (the default name is "results.root").
  //
  // For example to write all histograms after processing all the events simply use:
  //
  // class MY_PROCESSOR : public cafe::Processor {
  //   ...
  //   hist_files my_histograms;
  // };
  //
  // void MY_PROCESSOR::finish() {
  //     TFile *file=initializeTFile( this );
  //     file->mkdir("my_directory");
  //     my_histograms.save(file,"my_directory");
  //     file->Close();
  // }
  //  
  TFile *initializeTFile(const char *processor_name="", bool debug=false);
  inline TFile *initializeTFile(const TString processor_name=TString(""), bool debug=false) {
    stringstream _processor_name;
    _processor_name << processor_name;
    return histfiles::initializeTFile(_processor_name.str().c_str(), debug);
  }
  TFile *initializeTFile(cafe::Processor *processor, bool debug=false);

  // array of ROOT-uple names created so far needed by initializeTFile methods
  static vector<string> _histfiles_created;

  // Extracts grandparent's name of a given processor. For example:
  // "/cafe/PARENT/PARENT1/PARENT2/THIS_NAME" => returns "PARENT"
  // "/cafe/THIS_NAME"                        => returns "THIS_NAME" 
  // "/cafe" or ""                            => returns "cafe"
  //
  // For instance it can be used inside MY_PROCESSOR::finish() method 
  // in conjunction with initializeTFile() method as follows: 
  //    ...
  //    TFile *file=initializeTFile( getParentProcessorName(this) );    
  //    ...
  const char* getParentProcessorName(const cafe::Processor *processor, bool debug=false);
};
#endif
