//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 20 11:05:42 2005 by ROOT version 4.02/00
// from TTree Global/Global
// found on file: /rooms/salon/dpchapin/wz_mc/cabout_cteq6l/zgamma_cteq6l_1-p17.02.00-maxopt-Linux-692397/global.root.root
//////////////////////////////////////////////////////////

#ifndef pmcsana_h
#define pmcsana_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

#include "PMCSEvent.hpp"
#include "GlobalParameters.hpp"
#include "WAnalysis.hpp"
#include "ZAnalysis.hpp"
#include "ZMuAnalysis.hpp"
#include "ZNuNuAnalysis.hpp"
#include "JPsiMuAnalysis.hpp"
#include "TRandom3.h"
#include "BeamWeight.hpp"
//
// Need to uncomment out pmcs_ana_evflav1, pmcs_ana_evflav2,
// pmcs_ana_evqdq, pmcs_ana_evx1 and pmcs_ana_evx2 for PDF reweighting
//
class pmcsana : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain


   // Declaration of leave types
   Int_t           pmcs_ana_nevtp;
   Int_t           pmcs_ana_npart;
   Int_t           pmcs_ana_nvtx;
   Float_t         pmcs_ana_evnum[1000];   //[nevtp]
   Float_t         pmcs_ana_evrun[1000];   //[nevtp]
   Float_t         pmcs_ana_evwt[1000];   //[nevtp]
   Float_t         pmcs_ana_evxs[1000];   //[nevtp]
   Float_t         pmcs_ana_pE[1000];   //[npart]
   Float_t         pmcs_ana_pcid[1000];   //[npart]
   Float_t         pmcs_ana_pcnum[1000];   //[npart]
   Float_t         pmcs_ana_pdvtx[1000];   //[npart]
   Float_t         pmcs_ana_peta[1000];   //[npart]
   Float_t         pmcs_ana_pidx[1000];   //[npart]
   Float_t         pmcs_ana_pistable[1000];   //[npart]
   Float_t         pmcs_ana_pphi[1000];   //[npart]
   Float_t         pmcs_ana_ppid[1000];   //[npart]
   Float_t         pmcs_ana_ppt[1000];   //[npart]
   Float_t         pmcs_ana_ppvtx[1000];   //[npart]
   Float_t         pmcs_ana_ppx[1000];   //[npart]
   Float_t         pmcs_ana_ppy[1000];   //[npart]
   Float_t         pmcs_ana_ppz[1000];   //[npart]
   Float_t         pmcs_ana_vcid[1000];   //[nvtx]
   Float_t         pmcs_ana_vcnum[1000];   //[nvtx]
   Float_t         pmcs_ana_vct[1000];   //[nvtx]
   Float_t         pmcs_ana_vidx[1000];   //[nvtx]
   Float_t         pmcs_ana_visdisp[1000];   //[nvtx]
   Float_t         pmcs_ana_vpprt[1000];   //[nvtx]
   Float_t         pmcs_ana_vx[1000];   //[nvtx]
   Float_t         pmcs_ana_vy[1000];   //[nvtx]
   Float_t         pmcs_ana_vz[1000];   //[nvtx]
#ifdef __USE_PDFS__
   Float_t         pmcs_ana_evflav1[1000];   //[nevtp]
   Float_t         pmcs_ana_evflav2[1000];   //[nevtp]
   Float_t         pmcs_ana_evqsq[1000];   //[nevtp]
   Float_t         pmcs_ana_evx1[1000];   //[nevtp]
   Float_t         pmcs_ana_evx2[1000];   //[nevtp]
#endif
#ifdef __USE_PDFS_RESBOS__
   Float_t         pmcs_ana_pdf_wgts[45];
#endif
   Int_t           pmcs_em_nelg;
   Int_t           pmcs_em_nels;
   Int_t           pmcs_em_nphg;
   Int_t           pmcs_em_nphs;
   Float_t         pmcs_em_elcalphis[120];   //[nels]
   Float_t         pmcs_em_eleg[120];   //[nelg]
   Float_t         pmcs_em_elelmergedEg[120];   //[nelg]
   Float_t         pmcs_em_eles[120];   //[nels]
   Float_t         pmcs_em_eletads[120];   //[nels]
   Float_t         pmcs_em_eletag[120];   //[nelg]
   Float_t         pmcs_em_eletas[120];   //[nels]
   Float_t         pmcs_em_elfid[120];   //[nelg]
   Int_t           pmcs_em_elhastrack[120];   //[nels]
   Float_t         pmcs_em_eliso[120];   //[nels]
   Int_t           pmcs_em_elmergedg[120];   //[nelg]
   Int_t           pmcs_em_elpasshmtx[120];   //[nels]
   Int_t           pmcs_em_elpassid1011[120];   //[nels]
   Float_t         pmcs_em_elphig[120];   //[nelg]
   Float_t         pmcs_em_elphis[120];   //[nels]
   Float_t         pmcs_em_elphmergedEg[120];   //[nelg]
   Int_t           pmcs_em_elpntg[120];   //[nels]
   Int_t           pmcs_em_elpnts[120];   //[nelg]
   Float_t         pmcs_em_elptg[120];   //[nelg]
   Float_t         pmcs_em_elpts[120];   //[nels]
   Int_t           pmcs_em_elpttr[120];   //[nels]
   Float_t         pmcs_em_elFSRxInCones[120];   //[nels]
   Int_t           pmcs_em_elFSRnInCones[120];   //[nels]
   Float_t         pmcs_em_pheg[120];   //[nphg]
   Float_t         pmcs_em_phes[120];   //[nphs]
   Float_t         pmcs_em_phetads[120];   //[nphs]
   Float_t         pmcs_em_phetag[120];   //[nphg]
   Float_t         pmcs_em_phetas[120];   //[nphs]
   Float_t         pmcs_em_phfid[120];   //[nphg]
   Int_t           pmcs_em_phhastrack[120];   //[nels]
   Float_t         pmcs_em_phiso[120];   //[nphs]
   Int_t           pmcs_em_phpasshmtx[120];   //[nels]
   Float_t         pmcs_em_phphig[120];   //[nphg]
   Float_t         pmcs_em_phphis[120];   //[nphs]
   Int_t           pmcs_em_phpntg[120];   //[nphs]
   Int_t           pmcs_em_phpnts[120];   //[nphg]
   Float_t         pmcs_em_phptg[120];   //[nphg]
   Float_t         pmcs_em_phpts[120];   //[nphs]
   Int_t           pmcs_met_nmetg;
   Int_t           pmcs_met_nmets;
   Float_t         pmcs_met_metg[200];   //[nmetg]
   Float_t         pmcs_met_metphig[200];   //[nmetg]
   Float_t         pmcs_met_metphis[200];   //[nmets]
   Float_t         pmcs_met_mets[200];   //[nmets]
   Float_t         pmcs_met_metxg[200];   //[nmetg]
   Float_t         pmcs_met_metxs[200];   //[nmets]
   Float_t         pmcs_met_metyg[200];   //[nmetg]
   Float_t         pmcs_met_metys[200];   //[nmets]
   Float_t         pmcs_met_scalarg[200];   //[nmetg]
   Float_t         pmcs_met_scalars[200];   //[nmets]
   Int_t           pmcs_vtx_nvtxg;
   Int_t           pmcs_vtx_nvtxs;
   Float_t         pmcs_vtx_vtnds[150];   //[nvtxs]
   Float_t         pmcs_vtx_vtxxs[150];   //[nvtxs]
   Float_t         pmcs_vtx_vtxys[150];   //[nvtxs]
   Float_t         pmcs_vtx_vtxzg[150];   //[nvtxg]
   Float_t         pmcs_vtx_vtxzs[150];   //[nvtxs]

   // List of branches
   TBranch        *b_pmcs_ana;   //!
   TBranch        *b_pmcs_em;   //!
   TBranch        *b_pmcs_met;   //!
   TBranch        *b_pmcs_vtx;   //!

   pmcsana(TTree *tree=0) { }
   ~pmcsana();
   Int_t   Version() const {return 1;}
   void    Begin(TTree *tree);
   void    SlaveBegin(TTree *tree);
   void    Init(TTree *tree);
   Bool_t  Notify();
   Bool_t  Process(Long64_t entry);
   void    SetOption(const char *option) { fOption = option; }
   void    SetObject(TObject *obj) { fObject = obj; }
   void    SetInputList(TList *input) {fInput = input;}
   TList  *GetOutputList() const { return fOutput; }
   void    SlaveTerminate();
   void    Terminate();
   int     WriteOut();
   void    Initialize();

   ClassDef(pmcsana,0);

 // user defined functions
   void    fixEMBlock(Int_t entry, PMCSVtx& vtx, double cut_dR_CC, double cut_dR_EC, double instlumi,
		      bool selectLeadingFSR=false, double* LeadFSR_ET=0, double* LeadFSR_dR=0, double* LeadFSR_x=0, double* TrailFSR_ET=0, int* FSR_nPhot=0, int* FSR_nInConePhot=0, int* FSR_nOutConePhot=0);
   bool    constructPMCSEvent(Int_t entry, int runNo, double instlumi, double& evtweight, PMCSParticle& wzboson,
			      std::vector<PMCSEMObj>& emobjs_raw,  std::vector<PMCSEMObj>& emobjs_raw_wfsr, std::vector<PMCSEMObj>& emobjs, PMCSMet& met, 
			      PMCSRecoil& recoil, PMCSVtx& vtx, 
			      std::vector<PMCSMuon>& muons, 
			      bool selectLeadingFSR, double& LeadFSR_ET, double& LeadFSR_dR, double& LeadFSR_x, double& TrailFSR_ET, int& FSR_nPhot, int& FSR_nInConePhot, int& FSR_nOutConePhot,
			      TRandom3 *dummy);

   Float_t CalculateTruePhiStar(Bool_t* passesCuts=0);

   void setParameterFileName(const char *s){
     _parameter_filename = TString(s);
   }

   void setOutputRootFileName(const char *s){
     _output_root_filename = TString(s);
   }

   // use this flag to indicate whether you want to process Z or W events
   void setRunOption(int runoption) {
     _runoption = runoption;
   }

   void setRandomSeed(int r) {
     _randomseed = r;
   }

   void setNumEvents(int numEvents) {
     _numEvents = numEvents;
   }

 private:
   TString _parameter_filename;
   TString _output_root_filename;

   TFile *_file;
   int _runoption;
   int _randomseed;
   int _numEvents;

   bool _doPdfReweight;

   GlobalParameters *_globalparameters;
   ZAnalysis *_zanalysis;
   WAnalysis *_wanalysis;
   ZMuAnalysis *_zmuanalysis;
   JPsiMuAnalysis *_jpsimuanalysis;
   ZNuNuAnalysis *_znunuanalysis;
   TRandom3 *_dummy;

   // luminosity profile
   TH1F *_instlumi_profile;

   // luminosity vs runNo, only used for recoil library method
   TH2F *_instlumi_runNo_profile;
   TH1F *_instlumi_runNo_profile_X;
   TH1F *_instlumi_runNo_profile_Y;

   // photon merging probability and merged photon response
   bool _simulate_merge_fsr_photons_in_cone_prob, _simulate_merge_fsr_photons_in_cone_response;
   std::vector<float> _merge_fsr_photons_in_cone_prob_p0, _merge_fsr_photons_in_cone_prob_p1,
     _merge_fsr_photons_in_cone_prob_p2, _merge_fsr_photons_in_cone_prob_p3;
   std::vector<float> _merge_fsr_photons_in_cone_response_p0, _merge_fsr_photons_in_cone_response_p1, 
     _merge_fsr_photons_in_cone_response_p2, _merge_fsr_photons_in_cone_response_p3, _merge_fsr_photons_in_cone_response_p4, 
     _merge_fsr_photons_in_cone_response_p5, _merge_fsr_photons_in_cone_response_p6;

   bool _simulate_merge_fsr_photons_out_cone_prob, _simulate_merge_fsr_photons_out_cone_response;
   std::vector<float> _merge_fsr_photons_out_cone_prob_p0, _merge_fsr_photons_out_cone_prob_p1,
     _merge_fsr_photons_out_cone_prob_p2, _merge_fsr_photons_out_cone_prob_p3, _merge_fsr_photons_out_cone_prob_p4;
   std::vector<float> _merge_fsr_photons_out_cone_response_p0, _merge_fsr_photons_out_cone_response_p1, 
     _merge_fsr_photons_out_cone_response_p2, _merge_fsr_photons_out_cone_response_p3, _merge_fsr_photons_out_cone_response_p4, 
     _merge_fsr_photons_out_cone_response_p5, _merge_fsr_photons_out_cone_response_p6;

   // Alternative FSR model(s)
   TH1D* _FSRmodel_eff[12];
   TH1D* _FSRmodel_loss[12];
   //
   TH1D* _FSRmodel_eff_eta[7][12];
   TH1D* _FSRmodel_loss_eta[7][12];
   //
   TH1D* _FSRmodel_eff_eta_e[7][4][12];
   TH1D* _FSRmodel_loss_eta_e[7][4][12];
   double _FSResummary[7][4];

   // RunIIb34 model.
   //   TProfile* _FSRmodel_eff_lumi_eta_e_dr[12][7][8][8];
   //   TProfile* _FSRmodel_loss_lumi_eta_e_dr[12][7][8][8];
   //   double _FSRlumisummary[7][8][8];
   //   double _FSResummary2[7][8][8];
   std::vector < std::vector < std::vector < std::vector < TProfile* > > > > _FSRmodel_eff_lumi_eta_e_dr;
   std::vector < std::vector < std::vector < std::vector < TProfile* > > > > _FSRmodel_loss_lumi_eta_e_dr;
   std::vector < std::vector < std::vector < double > > > _FSRlumisummary;
   std::vector < std::vector < std::vector < double > > > _FSResummary2;
   std::vector < float > fsrmodel7_ebins;
   std::vector < float > fsrmodel7_etabins;
   std::vector < float > fsrmodel7_lumibins;
   std::vector < float > fsrmodel7_drbins;

   // Histograms for phi star reweighting
   TH1D* _phistarDist[3];
   //
   TH1D* _phistarWT[3];

   // beam spot weight
   BeamWeight *_beam;

   // for ZNuNuAnalysis (runoption = 4)
   double _NuLoose_EtaMax;
   double _NuLoose_PtMin;
   double _NuTight_EtaMax;
   double _NuTight_PtMin;
   Int_t _neigen;
};

#endif

#ifdef pmcsana_cxx
void pmcsana::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses of the tree
   // will be set. It is normaly not necessary to make changes to the
   // generated code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running with PROOF.

   // Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("pmcs_ana",&pmcs_ana_nevtp);
   fChain->SetBranchAddress("pmcs_em",&pmcs_em_nelg);
   fChain->SetBranchAddress("pmcs_met",&pmcs_met_nmetg);
   fChain->SetBranchAddress("pmcs_vtx",&pmcs_vtx_nvtxg);
}

Bool_t pmcsana::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_pmcs_ana = fChain->GetBranch("pmcs_ana");
   b_pmcs_em = fChain->GetBranch("pmcs_em");
   b_pmcs_met = fChain->GetBranch("pmcs_met");
   b_pmcs_vtx = fChain->GetBranch("pmcs_vtx");

   return kTRUE;
}

#ifdef __USE_PDFS__
#include "LHAPDF/FortranWrappers.h"
#ifdef FC_DUMMY_MAIN
int FC_DUMMY_MAIN() { return 1; }
#endif
#endif

#endif // #ifdef pmcsana_cxx
