#ifndef INC_GLOBALPARAMETERS
#define INC_GLOBALPARAMETERS

#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include <vector>

class GlobalParameters {

public:
  // constructor
  GlobalParameters(TString parameter_filename);

  // destructor
  ~GlobalParameters() {;}

  bool reweight() const;

  bool debug() const;
  double pT_Cut() const;
  
  bool dump_mctruth() const;

  bool smearVertex() const;
  int VtxSmear_Option() const;
  double VtxResolution() const;
  bool VtxApplyAsWeight() const;
  TString BeamSpotShape_file() const;

  bool do_zvtx_cut() const;
  double zvtx_cut() const;

  int rand_seed() const;
  int update_frequency() const;

  bool cutOnLeadingFSR() const;
  double LeadingFSR_ETmin() const;
  double LeadingFSR_ETmax() const;
  double LeadingFSR_dRmin() const;
  double LeadingFSR_dRmax() const;
  double LeadingFSR_xmin() const;
  double LeadingFSR_xmax() const;
  //
  bool cutOnTrailingFSR() const;
  double TrailingFSR_ETmin() const;
  double TrailingFSR_ETmax() const;
  //
  bool cutOnFSRnPhot() const;
  int FSR_nPhot_min() const;
  int FSR_nPhot_max() const;
  int FSR_nInConePhot_min() const;
  int FSR_nInConePhot_max() const;
  int FSR_nOutConePhot_min() const;
  int FSR_nOutConePhot_max() const;

  bool merge_fsr_photons() const;
  int merge_fsr_photons_model() const;
  TString merge_fsr_photons_model_file() const;
  TString merge_fsr_photons_model_file2() const;
  double merge_fsr_radius_CC() const;
  double merge_fsr_radius_EC() const;
  bool simulate_merge_fsr_photons_in_cone_prob() const;
  bool simulate_merge_fsr_photons_in_cone_response() const;
  std::vector<float> merge_fsr_photons_in_cone_prob_p0() const;
  std::vector<float> merge_fsr_photons_in_cone_prob_p1() const;
  std::vector<float> merge_fsr_photons_in_cone_prob_p2() const;
  std::vector<float> merge_fsr_photons_in_cone_prob_p3() const;
  std::vector<float> merge_fsr_photons_in_cone_response_p0() const;
  std::vector<float> merge_fsr_photons_in_cone_response_p1() const;
  std::vector<float> merge_fsr_photons_in_cone_response_p2() const;
  std::vector<float> merge_fsr_photons_in_cone_response_p3() const;
  std::vector<float> merge_fsr_photons_in_cone_response_p4() const;
  std::vector<float> merge_fsr_photons_in_cone_response_p5() const;

  bool simulate_merge_fsr_photons_out_cone_prob() const;
  bool simulate_merge_fsr_photons_out_cone_response() const;
  std::vector<float> merge_fsr_photons_out_cone_prob_p0() const;
  std::vector<float> merge_fsr_photons_out_cone_prob_p1() const;
  std::vector<float> merge_fsr_photons_out_cone_prob_p2() const;
  std::vector<float> merge_fsr_photons_out_cone_prob_p3() const;
  std::vector<float> merge_fsr_photons_out_cone_prob_p4() const;
  std::vector<float> merge_fsr_photons_out_cone_response_p0() const;
  std::vector<float> merge_fsr_photons_out_cone_response_p1() const;
  std::vector<float> merge_fsr_photons_out_cone_response_p2() const;
  std::vector<float> merge_fsr_photons_out_cone_response_p3() const;
  std::vector<float> merge_fsr_photons_out_cone_response_p4() const;
  std::vector<float> merge_fsr_photons_out_cone_response_p5() const;


  std::vector<float> fsrmodel7_ebins() const;
  std::vector<float> fsrmodel7_etabins() const;
  std::vector<float> fsrmodel7_drbins() const;
  std::vector<float> fsrmodel7_lumibins() const;
  float fsrmodel7_norm() const;
  bool fsrmodel7_interpolate() const;
  
  bool merge_fsr_photons_recoil() const;

  // luminosity profile
  TH1F *instlumi_profile() const;
  TH2F *instlumi_runNo_profile() const;

  // PDF reweight
  bool pdfreweight() const;
  std::string pdfori() const;
  int pdfori_subset() const;
//  std::vector<std::string> vpdfnew() const;
//  std::vector<int> vpdfnew_subset() const;

  // phi star reweighting
  bool phistarreweight() const;
  std::string phistarreweight_File() const;

 private:

  // debug flag  
  bool _debug;
 
  // reweighting or not
  bool _reweight;

  // only apply energy smearing to electrons with pT>pT_Cut
  double _pT_Cut;   

  // dump mc truth in pmcsana.cpp
  bool _dump_mctruth;

  // vertex smearing 
  bool _smearVertex;
  int _VtxSmear_Option;
  double _VtxResolution; 
  bool _VtxApplyAsWeight;
  TString _BeamSpotShape_file;

  // vertex cut
  bool _do_zvtx_cut;
  double _zvtx_cut;

  // random seed
  int _rand_seed;
  int _update_frequency;

  // Merge electrons and photons if they are close to each other
  bool _merge_fsr_photons;
  int _merge_fsr_photons_model;
  TString  _merge_fsr_photons_model_file;
  TString  _merge_fsr_photons_model_file2;
  double _merge_fsr_radius_CC;
  double _merge_fsr_radius_EC;

  // Leading FSR selection
  int _cutOnLeadingFSR;
  double _LeadingFSR_ETmin;
  double _LeadingFSR_ETmax;
  double _LeadingFSR_dRmin;
  double _LeadingFSR_dRmax;
  double _LeadingFSR_xmin;
  double _LeadingFSR_xmax;
  // Trailing FSR slection
  int _cutOnTrailingFSR;
  double _TrailingFSR_ETmin;
  double _TrailingFSR_ETmax;
  // Number of FSR photons
  bool _cutOnFSRnPhot;
  int _FSR_nPhot_min;
  int _FSR_nPhot_max;
  int _FSR_nInConePhot_min;
  int _FSR_nInConePhot_max;
  int _FSR_nOutConePhot_min;
  int _FSR_nOutConePhot_max;

  // photon merging probability and merged photon response
  bool _simulate_merge_fsr_photons_in_cone_prob, _simulate_merge_fsr_photons_in_cone_response;
  std::vector<float> _merge_fsr_photons_in_cone_prob_p0, _merge_fsr_photons_in_cone_prob_p1, 
    _merge_fsr_photons_in_cone_prob_p2, _merge_fsr_photons_in_cone_prob_p3;
  std::vector<float> _merge_fsr_photons_in_cone_response_p0, _merge_fsr_photons_in_cone_response_p1,
    _merge_fsr_photons_in_cone_response_p2, _merge_fsr_photons_in_cone_response_p3, 
    _merge_fsr_photons_in_cone_response_p4, _merge_fsr_photons_in_cone_response_p5;

  bool _simulate_merge_fsr_photons_out_cone_prob, _simulate_merge_fsr_photons_out_cone_response;
  std::vector<float> _merge_fsr_photons_out_cone_prob_p0, _merge_fsr_photons_out_cone_prob_p1, 
    _merge_fsr_photons_out_cone_prob_p2, _merge_fsr_photons_out_cone_prob_p3, _merge_fsr_photons_out_cone_prob_p4;
  std::vector<float> _merge_fsr_photons_out_cone_response_p0, _merge_fsr_photons_out_cone_response_p1,
    _merge_fsr_photons_out_cone_response_p2, _merge_fsr_photons_out_cone_response_p3, 
    _merge_fsr_photons_out_cone_response_p4, _merge_fsr_photons_out_cone_response_p5;
  
  std::vector<float> _fsrmodel7_etabins;
  std::vector<float> _fsrmodel7_ebins;
  std::vector<float> _fsrmodel7_lumibins;
  std::vector<float> _fsrmodel7_drbins;
  float _fsrmodel7_norm;
  bool _fsrmodel7_interpolate;


  // photons with pT<pT_Cut and well separated from electrons will 
  // be included as part of the recoil system
  bool _merge_fsr_photons_recoil;

  // Instantaneous luminosity profile
  TH1F *_hInstLumi_Profile;
  TH2F *_hInstLumi_runNo_Profile;

  // for PDF reweighting, code stolen from caf_pdfreweight
  // Initial PDF
  bool _pdfreweight;
  std::string _pdfori;
  int _pdfori_subset;
 
  // PDF for reweighting
//  std::vector<std::string> _vpdfnew;
//  std::vector<int> _vpdfnew_subset;

  bool _phistarreweight;
  std::string _phistarreweight_File;

};

inline bool GlobalParameters::reweight() const {return _reweight;}
inline bool GlobalParameters::pdfreweight() const {return _pdfreweight;}
inline std::string GlobalParameters::pdfori() const {return _pdfori;}
inline int GlobalParameters::pdfori_subset() const {return _pdfori_subset;}
//inline std::vector<std::string> GlobalParameters::vpdfnew() const {return _vpdfnew;}
//inline std::vector<int> GlobalParameters::vpdfnew_subset() const {return _vpdfnew_subset;}

inline bool GlobalParameters::phistarreweight() const {return _phistarreweight;}
inline std::string GlobalParameters::phistarreweight_File() const {return _phistarreweight_File;}

inline bool GlobalParameters::debug() const {return _debug;}
inline double GlobalParameters::pT_Cut() const {return _pT_Cut;}

inline bool GlobalParameters::dump_mctruth() const {return _dump_mctruth;}

inline bool GlobalParameters::smearVertex() const {return _smearVertex;}
inline int GlobalParameters::VtxSmear_Option() const {return _VtxSmear_Option;}
inline double GlobalParameters::VtxResolution() const {return _VtxResolution;}
inline bool GlobalParameters::VtxApplyAsWeight() const {return _VtxApplyAsWeight;}
inline TString GlobalParameters::BeamSpotShape_file() const {return _BeamSpotShape_file;}

inline bool GlobalParameters::do_zvtx_cut() const {return _do_zvtx_cut;}
inline double GlobalParameters::zvtx_cut() const {return _zvtx_cut;}

inline int GlobalParameters::rand_seed() const {return _rand_seed;}
inline int GlobalParameters::update_frequency() const {return _update_frequency;}

inline bool GlobalParameters::cutOnLeadingFSR() const {return _cutOnLeadingFSR;}
inline double GlobalParameters::LeadingFSR_ETmin() const {return _LeadingFSR_ETmin;}
inline double GlobalParameters::LeadingFSR_ETmax() const {return _LeadingFSR_ETmax;}
inline double GlobalParameters::LeadingFSR_dRmin() const {return _LeadingFSR_dRmin;}
inline double GlobalParameters::LeadingFSR_dRmax() const {return _LeadingFSR_dRmax;}
inline double GlobalParameters::LeadingFSR_xmin() const {return _LeadingFSR_xmin;}
inline double GlobalParameters::LeadingFSR_xmax() const {return _LeadingFSR_xmax;}
//
inline bool GlobalParameters::cutOnTrailingFSR() const {return _cutOnTrailingFSR;}
inline double GlobalParameters::TrailingFSR_ETmin() const {return _TrailingFSR_ETmin;}
inline double GlobalParameters::TrailingFSR_ETmax() const {return _TrailingFSR_ETmax;}
//
inline bool GlobalParameters::cutOnFSRnPhot() const {return _cutOnFSRnPhot;}
inline int GlobalParameters::FSR_nPhot_min() const {return _FSR_nPhot_min;}
inline int GlobalParameters::FSR_nPhot_max() const {return _FSR_nPhot_max;}
inline int GlobalParameters::FSR_nInConePhot_min() const {return _FSR_nInConePhot_min;}
inline int GlobalParameters::FSR_nInConePhot_max() const {return _FSR_nInConePhot_max;}
inline int GlobalParameters::FSR_nOutConePhot_min() const {return _FSR_nOutConePhot_min;}
inline int GlobalParameters::FSR_nOutConePhot_max() const {return _FSR_nOutConePhot_max;}

inline bool GlobalParameters::merge_fsr_photons() const {return _merge_fsr_photons;}
inline int GlobalParameters::merge_fsr_photons_model() const {return _merge_fsr_photons_model;}
inline TString GlobalParameters::merge_fsr_photons_model_file() const {return _merge_fsr_photons_model_file;}
inline TString GlobalParameters::merge_fsr_photons_model_file2() const {return _merge_fsr_photons_model_file2;}
inline double GlobalParameters::merge_fsr_radius_CC() const {return _merge_fsr_radius_CC;}
inline double GlobalParameters::merge_fsr_radius_EC() const {return _merge_fsr_radius_EC;}

// in cone
inline bool GlobalParameters::simulate_merge_fsr_photons_in_cone_prob() const {return _simulate_merge_fsr_photons_in_cone_prob;}
inline bool GlobalParameters::simulate_merge_fsr_photons_in_cone_response() const {return _simulate_merge_fsr_photons_in_cone_response;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_in_cone_prob_p0() const {return _merge_fsr_photons_in_cone_prob_p0;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_in_cone_prob_p1() const {return _merge_fsr_photons_in_cone_prob_p1;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_in_cone_prob_p2() const {return _merge_fsr_photons_in_cone_prob_p2;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_in_cone_prob_p3() const {return _merge_fsr_photons_in_cone_prob_p3;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_in_cone_response_p0() const {return _merge_fsr_photons_in_cone_response_p0;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_in_cone_response_p1() const {return _merge_fsr_photons_in_cone_response_p1;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_in_cone_response_p2() const {return _merge_fsr_photons_in_cone_response_p2;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_in_cone_response_p3() const {return _merge_fsr_photons_in_cone_response_p3;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_in_cone_response_p4() const {return _merge_fsr_photons_in_cone_response_p4;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_in_cone_response_p5() const {return _merge_fsr_photons_in_cone_response_p5;}

// out cone
inline bool GlobalParameters::simulate_merge_fsr_photons_out_cone_prob() const {return _simulate_merge_fsr_photons_out_cone_prob;}
inline bool GlobalParameters::simulate_merge_fsr_photons_out_cone_response() const {return _simulate_merge_fsr_photons_out_cone_response;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_prob_p0() const {return _merge_fsr_photons_out_cone_prob_p0;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_prob_p1() const {return _merge_fsr_photons_out_cone_prob_p1;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_prob_p2() const {return _merge_fsr_photons_out_cone_prob_p2;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_prob_p3() const {return _merge_fsr_photons_out_cone_prob_p3;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_prob_p4() const {return _merge_fsr_photons_out_cone_prob_p4;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_response_p0() const {return _merge_fsr_photons_out_cone_response_p0;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_response_p1() const {return _merge_fsr_photons_out_cone_response_p1;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_response_p2() const {return _merge_fsr_photons_out_cone_response_p2;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_response_p3() const {return _merge_fsr_photons_out_cone_response_p3;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_response_p4() const {return _merge_fsr_photons_out_cone_response_p4;}
inline std::vector<float> GlobalParameters::merge_fsr_photons_out_cone_response_p5() const {return _merge_fsr_photons_out_cone_response_p5;}

inline  std::vector<float> GlobalParameters::fsrmodel7_etabins() const {return _fsrmodel7_etabins;}
inline  std::vector<float> GlobalParameters::fsrmodel7_ebins() const {return _fsrmodel7_ebins;}
inline  std::vector<float> GlobalParameters::fsrmodel7_lumibins() const {return _fsrmodel7_lumibins;}
inline  std::vector<float> GlobalParameters::fsrmodel7_drbins() const {return _fsrmodel7_drbins;}
inline  float GlobalParameters::fsrmodel7_norm() const {return _fsrmodel7_norm;}
inline  bool GlobalParameters::fsrmodel7_interpolate() const {return _fsrmodel7_interpolate;}

inline bool GlobalParameters::merge_fsr_photons_recoil() const {return _merge_fsr_photons_recoil;}

inline TH1F* GlobalParameters::instlumi_profile() const {return _hInstLumi_Profile;}
inline TH2F* GlobalParameters::instlumi_runNo_profile() const {return _hInstLumi_runNo_Profile;}

#endif
