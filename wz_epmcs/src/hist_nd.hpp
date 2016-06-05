//////////////////////////////////////////////////
///   File: hist_nd.hpp                        ///
///   Created: J.Zhu, M.Cwiok -- June 7, 2007  ///
///   Purpose: define 1d, 2d histograms        ///
///            profile, etc                    ///
///            based on H. Dong's Code         ///
//////////////////////////////////////////////////

#ifndef HIST_ND_HPP
#define HIST_ND_HPP

#include "TString.h"

typedef struct __hist_1d__ {
  TString name;
  TString title;
  Int_t nbin;
  Float_t lower;
  Float_t upper;
} HIST_1D;

typedef struct __hist_2d__ {
  TString name;
  TString title;
  Int_t nbinx;
  Float_t lowerx;
  Float_t upperx;
  Int_t nbiny;
  Float_t lowery;
  Float_t uppery;
} HIST_2D;

typedef struct __hist_profile__ {
  TString name;
  TString title;
  Int_t nbinx;
  Float_t lowerx;
  Float_t upperx;
  Float_t lowery;
  Float_t uppery;
  const char profile_option[2];
} HIST_PROFILE;

typedef struct __hist_profile_2d__ {
  TString name;
  TString title;
  Int_t nbinx;
  Double_t lowerx;
  Double_t upperx;
  Int_t nbiny;
  Double_t lowery;
  Double_t uppery;
  Double_t lowerz;
  Double_t upperz;
  const char profile_option[2];
} HIST_PROFILE_2D;

// variable bin size histograms
typedef struct __hist_1d_varbin_x__ {
  TString name;
  TString title;
  Int_t nbin;
  Float_t binx[50];
} HIST_1D_VARBIN;

typedef struct __hist_2d_varbin_x__ {
  TString name;
  TString title;
  Int_t nbinx;
  Double_t binx[50];
  Int_t nbiny;
  Double_t lowery;
  Double_t uppery;
} HIST_2D_VARBIN_X;

typedef struct __hist_2d_varbin_y__ {
  TString name;
  TString title;
  Int_t nbinx;
  Double_t lowerx;
  Double_t upperx;
  Int_t nbiny;
  Double_t biny[50];
} HIST_2D_VARBIN_Y;

typedef struct __hist_2d_varbin_xy__ {
  TString name;
  TString title;
  Int_t nbinx;
  Double_t binx[100];
  Int_t nbiny;
  Double_t biny[100];
} HIST_2D_VARBIN_XY;

typedef struct __hist_profile_varbin_x__ {
  TString name;
  TString title;
  Int_t nbinx;
  Double_t binx[50];
  Double_t lowery;
  Double_t uppery;
  const char profile_option[2];
} HIST_PROFILE_VARBIN;

typedef struct __hist_profile_2d_varbin_x__ {
  TString name;
  TString title;
  Int_t nbinx;
  Double_t binx[50];
  Int_t nbiny;
  Double_t lowery;
  Double_t uppery;
  Double_t lowerz;
  Double_t upperz;
  const char profile_option[2];
} HIST_PROFILE_2D_VARBIN_X;

typedef struct __hist_profile_2d_varbin_y__ {
  TString name;
  TString title;
  Int_t nbinx;
  Double_t lowerx;
  Double_t upperx;
  Int_t nbiny;
  Double_t biny[50];
  Double_t lowerz;
  Double_t upperz;
  const char profile_option[2];
} HIST_PROFILE_2D_VARBIN_Y;

typedef struct __hist_profile_2d_varbin_xy__ {
  TString name;
  TString title;
  Int_t nbinx;
  Double_t binx[50];
  Int_t nbiny;
  Double_t biny[50];
  Double_t lowerz;
  Double_t upperz;
  const char profile_option[2];
} HIST_PROFILE_2D_VARBIN_XY;

#endif
