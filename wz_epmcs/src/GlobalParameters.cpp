#include "GlobalParameters.hpp"
#include "PParameterReader.hpp"

// default constructor
GlobalParameters::GlobalParameters(TString parameter_filename) {
  
  PParameterReader parm(parameter_filename.Data());  
  parm.Print();
  
  _debug = parm.GetBool("debug", kFALSE);
  _reweight = parm.GetBool("reweight", kFALSE);
  _pT_Cut = parm.GetFloat("pT_cut", 5.0);

  _dump_mctruth = parm.GetBool("dump_mctruth", kFALSE);

  _smearVertex = parm.GetBool("smearVertex", kTRUE);
  _VtxSmear_Option = parm.GetInt("VtxSmear_Option", 0);
  _VtxResolution = parm.GetFloat("VtxResolution", 25.0);
  _VtxApplyAsWeight = parm.GetBool("VtxApplyAsWeight", kTRUE);
  _BeamSpotShape_file = parm.GetChar("BeamSpotShape_file");

  _rand_seed = parm.GetInt("rand_seed", 0);
  _update_frequency = parm.GetInt("update_frequency", 10000);

  _cutOnLeadingFSR = parm.GetBool("cutOnLeadingFSR", kFALSE);
  _LeadingFSR_ETmin = parm.GetFloat("LeadingFSR_ETmin", -1.0);
  _LeadingFSR_ETmax = parm.GetFloat("LeadingFSR_ETmax", 9999999.0);
  _LeadingFSR_dRmin = parm.GetFloat("LeadingFSR_dRmin", -1.0);
  _LeadingFSR_dRmax = parm.GetFloat("LeadingFSR_dRmax", 9999999.0);
  _LeadingFSR_xmin = parm.GetFloat("LeadingFSR_xmin", -1.0);
  _LeadingFSR_xmax = parm.GetFloat("LeadingFSR_xmax", 2.0);
  //
  _cutOnTrailingFSR = parm.GetBool("cutOnTrailingFSR", kFALSE);
  _TrailingFSR_ETmin = parm.GetFloat("TrailingFSR_ETmin", -1.0);
  _TrailingFSR_ETmax = parm.GetFloat("TrailingFSR_ETmax", 9999999.0);
  //
  _cutOnFSRnPhot = parm.GetBool("cutOnFSRnPhot", kFALSE);
  _FSR_nPhot_min = parm.GetInt("FSR_nPhot_min",-1);
  _FSR_nPhot_max = parm.GetInt("FSR_nPhot_max",9999);
  _FSR_nInConePhot_min = parm.GetInt("FSR_nInConePhot_min",-1);
  _FSR_nInConePhot_max = parm.GetInt("FSR_nInConePhot_max",9999);
  _FSR_nOutConePhot_min = parm.GetInt("FSR_nOutConePhot_min",-1);
  _FSR_nOutConePhot_max = parm.GetInt("FSR_nOutConePhot_max",9999);

  _merge_fsr_photons = parm.GetBool("merge_fsr_photons", kTRUE);
  _merge_fsr_photons_model = parm.GetInt("merge_fsr_photons_model", 1);
  _merge_fsr_photons_model_file = parm.GetChar("merge_fsr_photons_model_file");
  _merge_fsr_photons_model_file2 = parm.GetChar("merge_fsr_photons_model_file2");
  _merge_fsr_radius_CC = parm.GetFloat("merge_fsr_radius_CC", 0.4); 
  _merge_fsr_radius_EC = parm.GetFloat("merge_fsr_radius_EC", 10.); 
  _merge_fsr_photons_recoil = parm.GetBool("merge_fsr_photons_recoil", kTRUE);

  // in cone
  _simulate_merge_fsr_photons_in_cone_prob = parm.GetBool("simulate_merge_fsr_photons_in_cone_prob", kTRUE);
  _merge_fsr_photons_in_cone_prob_p0 = parm.GetVFloat("merge_fsr_photons_in_cone_prob_p0");
  _merge_fsr_photons_in_cone_prob_p1 = parm.GetVFloat("merge_fsr_photons_in_cone_prob_p1");
  _merge_fsr_photons_in_cone_prob_p2 = parm.GetVFloat("merge_fsr_photons_in_cone_prob_p2");
  _merge_fsr_photons_in_cone_prob_p3 = parm.GetVFloat("merge_fsr_photons_in_cone_prob_p3");

  _simulate_merge_fsr_photons_in_cone_response = parm.GetBool("simulate_merge_fsr_photons_in_cone_response", kTRUE);
  _merge_fsr_photons_in_cone_response_p0 = parm.GetVFloat("merge_fsr_photons_in_cone_response_p0");
  _merge_fsr_photons_in_cone_response_p1 = parm.GetVFloat("merge_fsr_photons_in_cone_response_p1");
  _merge_fsr_photons_in_cone_response_p2 = parm.GetVFloat("merge_fsr_photons_in_cone_response_p2");
  _merge_fsr_photons_in_cone_response_p3 = parm.GetVFloat("merge_fsr_photons_in_cone_response_p3");
  _merge_fsr_photons_in_cone_response_p4 = parm.GetVFloat("merge_fsr_photons_in_cone_response_p4");
  _merge_fsr_photons_in_cone_response_p5 = parm.GetVFloat("merge_fsr_photons_in_cone_response_p5");

  // out cone
  _simulate_merge_fsr_photons_out_cone_prob = parm.GetBool("simulate_merge_fsr_photons_out_cone_prob", kTRUE);
  _merge_fsr_photons_out_cone_prob_p0 = parm.GetVFloat("merge_fsr_photons_out_cone_prob_p0");
  _merge_fsr_photons_out_cone_prob_p1 = parm.GetVFloat("merge_fsr_photons_out_cone_prob_p1");
  _merge_fsr_photons_out_cone_prob_p2 = parm.GetVFloat("merge_fsr_photons_out_cone_prob_p2");
  _merge_fsr_photons_out_cone_prob_p3 = parm.GetVFloat("merge_fsr_photons_out_cone_prob_p3");
  _merge_fsr_photons_out_cone_prob_p4 = parm.GetVFloat("merge_fsr_photons_out_cone_prob_p4");

  _simulate_merge_fsr_photons_out_cone_response = parm.GetBool("simulate_merge_fsr_photons_out_cone_response", kTRUE);
  _merge_fsr_photons_out_cone_response_p0 = parm.GetVFloat("merge_fsr_photons_out_cone_response_p0");
  _merge_fsr_photons_out_cone_response_p1 = parm.GetVFloat("merge_fsr_photons_out_cone_response_p1");
  _merge_fsr_photons_out_cone_response_p2 = parm.GetVFloat("merge_fsr_photons_out_cone_response_p2");
  _merge_fsr_photons_out_cone_response_p3 = parm.GetVFloat("merge_fsr_photons_out_cone_response_p3");
  _merge_fsr_photons_out_cone_response_p4 = parm.GetVFloat("merge_fsr_photons_out_cone_response_p4");
  _merge_fsr_photons_out_cone_response_p5 = parm.GetVFloat("merge_fsr_photons_out_cone_response_p5");

  if (_merge_fsr_photons_model==7) {
    _fsrmodel7_ebins = parm.GetVFloat("fsrmodel7_ebins"); 
    _fsrmodel7_etabins = parm.GetVFloat("fsrmodel7_etabins"); 
    _fsrmodel7_lumibins = parm.GetVFloat("fsrmodel7_lumibins"); 
    _fsrmodel7_drbins = parm.GetVFloat("fsrmodel7_drbins"); 
    _fsrmodel7_norm = parm.GetFloat("fsrmodel7_norm"); 
    _fsrmodel7_interpolate = parm.GetBool("fsrmodel7_interpolate"); 
  }
  _do_zvtx_cut = parm.GetBool("do_zvtx_cut", kFALSE);
  _zvtx_cut = parm.GetFloat("zvtx_cut", 30.);

  // instantaneous luminosity profile
  TString instlumi_filename(parm.GetChar("instlumi_file"));
  gROOT->ProcessLine(TString(".x ")+instlumi_filename);
  _hInstLumi_Profile = (TH1F *)gROOT->FindObject("InstLumi_WZ");

  // instantaneous luminosity-Run Number  profile
  TString instlumi_runNo_filename(parm.GetChar("instlumi_runNo_file"));
  gROOT->ProcessLine(TString(".x ")+instlumi_runNo_filename);
  _hInstLumi_runNo_Profile = (TH2F *)gROOT->FindObject("InstLumi_runNo_WZ");
  
  // for PDF reweighting
  _pdfreweight = parm.GetBool("PDFReweight", kFALSE);
  _pdfori = parm.get("PDFori", "");
  _pdfori_subset = parm.GetInt("PDForiSubSet",0);
//  for (int i=0; i<41; ++i) {
//    _vpdfnew.push_back("cteq61.LHgrid");
//    _vpdfnew_subset.push_back(i);
//  }

  _phistarreweight = parm.GetBool("phistarReweight", kFALSE);
  if (_phistarreweight) _phistarreweight_File = parm.GetChar("phistarReweight_File");

}
