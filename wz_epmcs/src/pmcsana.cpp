#define pmcsana_cxx
#include "pmcsana.h"
#include <TH2.h>
#include <TStyle.h>
#include <TFile.h>
#include <TTree.h>
#include "PCalTools.hpp"
#include "WZ_Utils.hpp"
#ifdef __USE_PDFS__
#include "LHAPDF/LHAPDF.h"
#endif

#include <iterator>
#include <iostream>
#include <cstdlib>

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

static double PDFWeightFactor[45];

bool ComparePt(const PMCSParticle part1, const PMCSParticle part2);


void pmcsana::Initialize() {

   TString option = GetOption();
   cout<<"Start pmcsana::Initialize"<<endl;

   cout<<"Initialize some global parameters:"<<endl;
   _globalparameters = new GlobalParameters(_parameter_filename);

   // some parameters for photon merging
   // for photon merging probability
   _simulate_merge_fsr_photons_in_cone_prob = _globalparameters->simulate_merge_fsr_photons_in_cone_prob();
   _merge_fsr_photons_in_cone_prob_p0 = _globalparameters->merge_fsr_photons_in_cone_prob_p0();
   _merge_fsr_photons_in_cone_prob_p1 = _globalparameters->merge_fsr_photons_in_cone_prob_p1();
   _merge_fsr_photons_in_cone_prob_p2 = _globalparameters->merge_fsr_photons_in_cone_prob_p2();
   _merge_fsr_photons_in_cone_prob_p3 = _globalparameters->merge_fsr_photons_in_cone_prob_p3();
   _simulate_merge_fsr_photons_out_cone_prob = _globalparameters->simulate_merge_fsr_photons_out_cone_prob();
   _merge_fsr_photons_out_cone_prob_p0 = _globalparameters->merge_fsr_photons_out_cone_prob_p0();
   _merge_fsr_photons_out_cone_prob_p1 = _globalparameters->merge_fsr_photons_out_cone_prob_p1();
   _merge_fsr_photons_out_cone_prob_p2 = _globalparameters->merge_fsr_photons_out_cone_prob_p2();
   _merge_fsr_photons_out_cone_prob_p3 = _globalparameters->merge_fsr_photons_out_cone_prob_p3();
   _merge_fsr_photons_out_cone_prob_p4 = _globalparameters->merge_fsr_photons_out_cone_prob_p4();
   // for merged photon response
   _simulate_merge_fsr_photons_in_cone_response = _globalparameters->simulate_merge_fsr_photons_in_cone_response();
   _merge_fsr_photons_in_cone_response_p0 = _globalparameters->merge_fsr_photons_in_cone_response_p0();
   _merge_fsr_photons_in_cone_response_p1 = _globalparameters->merge_fsr_photons_in_cone_response_p1();
   _merge_fsr_photons_in_cone_response_p2 = _globalparameters->merge_fsr_photons_in_cone_response_p2();
   _merge_fsr_photons_in_cone_response_p3 = _globalparameters->merge_fsr_photons_in_cone_response_p3();
   _merge_fsr_photons_in_cone_response_p4 = _globalparameters->merge_fsr_photons_in_cone_response_p4();
   _merge_fsr_photons_in_cone_response_p5 = _globalparameters->merge_fsr_photons_in_cone_response_p5();
   _simulate_merge_fsr_photons_out_cone_response = _globalparameters->simulate_merge_fsr_photons_out_cone_response();
   _merge_fsr_photons_out_cone_response_p0 = _globalparameters->merge_fsr_photons_out_cone_response_p0();
   _merge_fsr_photons_out_cone_response_p1 = _globalparameters->merge_fsr_photons_out_cone_response_p1();
   _merge_fsr_photons_out_cone_response_p2 = _globalparameters->merge_fsr_photons_out_cone_response_p2();
   _merge_fsr_photons_out_cone_response_p3 = _globalparameters->merge_fsr_photons_out_cone_response_p3();
   _merge_fsr_photons_out_cone_response_p4 = _globalparameters->merge_fsr_photons_out_cone_response_p4();
   _merge_fsr_photons_out_cone_response_p5 = _globalparameters->merge_fsr_photons_out_cone_response_p5();

   if (_globalparameters->merge_fsr_photons_model() == 7) {

     fsrmodel7_ebins = _globalparameters->fsrmodel7_ebins();
     fsrmodel7_etabins = _globalparameters->fsrmodel7_etabins();
     fsrmodel7_lumibins = _globalparameters->fsrmodel7_lumibins();
     fsrmodel7_drbins = _globalparameters->fsrmodel7_drbins();

//      cout << "Initializing FSR model 7 with " << endl
// 	  << fsrmodel7_ebins.size()-1 << " energy bins" << endl
// 	  << fsrmodel7_etabins.size()-1 << " eta bins" << endl
// 	  << fsrmodel7_lumibins.size()-1 << " luminosity bins" << endl
// 	  << fsrmodel7_drbins.size()-1 << " dR bins" << endl;

     TFile* reinFSRmodel = TFile::Open(_globalparameters->merge_fsr_photons_model_file2());
     TH3D* lumisummary = (TH3D*) reinFSRmodel->Get("lumisummary");
     TH3D* esummary = (TH3D*) reinFSRmodel->Get("esummary");

     TProfile* space_holder = (TProfile*) reinFSRmodel->Get("FSRmodel_eff_1_1_1_1");

     _FSRmodel_eff_lumi_eta_e_dr.resize(fsrmodel7_drbins.size()-1);
     _FSRmodel_loss_lumi_eta_e_dr.resize(fsrmodel7_drbins.size()-1);
     for (int i=0; i<fsrmodel7_drbins.size()-1; i++) {
       _FSRmodel_eff_lumi_eta_e_dr[i].resize(fsrmodel7_etabins.size()-1);
       _FSRmodel_loss_lumi_eta_e_dr[i].resize(fsrmodel7_etabins.size()-1);
       for (int j=0; j<fsrmodel7_etabins.size()-1; j++) {
	 _FSRmodel_eff_lumi_eta_e_dr[i][j].resize(fsrmodel7_lumibins.size()-1);
	 _FSRmodel_loss_lumi_eta_e_dr[i][j].resize(fsrmodel7_lumibins.size()-1);
	 for (int k=0; k<fsrmodel7_lumibins.size()-1; k++) {
	   _FSRmodel_eff_lumi_eta_e_dr[i][j][k].resize(fsrmodel7_ebins.size()-1, space_holder);
	   _FSRmodel_loss_lumi_eta_e_dr[i][j][k].resize(fsrmodel7_ebins.size()-1, space_holder);
	 }
       }
     }
     _FSRlumisummary.resize(fsrmodel7_etabins.size()-1);
     _FSResummary2.resize(fsrmodel7_etabins.size()-1);
     for (int j=0; j<fsrmodel7_etabins.size()-1; j++) {
       _FSRlumisummary[j].resize(fsrmodel7_lumibins.size()-1);
       _FSResummary2[j].resize(fsrmodel7_lumibins.size()-1);
       for (int k=0; k<fsrmodel7_lumibins.size()-1; k++) {
	 _FSRlumisummary[j][k].resize(fsrmodel7_ebins.size()-1);
	 _FSResummary2[j][k].resize(fsrmodel7_ebins.size()-1);
       }
     }

     for(int lumibin = 0; lumibin != fsrmodel7_lumibins.size()-1; ++lumibin) {
       for(int etabin = 0; etabin != fsrmodel7_etabins.size()-1; ++etabin) {
         for(int ebin = 0; ebin != fsrmodel7_ebins.size()-1; ++ebin) {
           _FSRlumisummary[etabin][lumibin][ebin] = lumisummary->GetBinContent(lumibin+1, etabin+1, ebin+1);
           _FSResummary2[etabin][lumibin][ebin] = esummary->GetBinContent(lumibin+1, etabin+1, ebin+1);
           for(int dRbin = 0; dRbin != 12; ++dRbin) {
             _FSRmodel_eff_lumi_eta_e_dr[dRbin][etabin][lumibin][ebin] = (TProfile*) reinFSRmodel->Get(TString::Format("FSRmodel_eff_%d_%d_%d_%d", lumibin, etabin, ebin, dRbin));
             _FSRmodel_loss_lumi_eta_e_dr[dRbin][etabin][lumibin][ebin] = (TProfile*) reinFSRmodel->Get(TString::Format("FSRmodel_loss_%d_%d_%d_%d", lumibin, etabin, ebin, dRbin));
             _FSRmodel_eff_lumi_eta_e_dr[dRbin][etabin][lumibin][ebin]->SetDirectory(0);
             _FSRmodel_loss_lumi_eta_e_dr[dRbin][etabin][lumibin][ebin]->SetDirectory(0);
           }
         }
       }
     }
     reinFSRmodel->Close();
   }

   // Initialise the alternative FSR model, if requested
   if (_globalparameters->merge_fsr_photons_model()==2 || _globalparameters->merge_fsr_photons_model()==3 || _globalparameters->merge_fsr_photons_model()==4
       || _globalparameters->merge_fsr_photons_model()==6 || _globalparameters->merge_fsr_photons_model()==7) {
     TFile* reinFSRmodel = new TFile(_globalparameters->merge_fsr_photons_model_file());
     for (Int_t i=0; i<12; i++) {
       TString n;
       n="FSRmodel_eff_";
       n+=(i+1);
       _FSRmodel_eff[i]=(TH1D*)reinFSRmodel->Get(n);
     }
     for (Int_t i=0; i<12; i++) {
       TString n;
       n="FSRmodel_loss_";
       n+=(i+1);
       _FSRmodel_loss[i]=(TH1D*)reinFSRmodel->Get(n);
     }
     if (_globalparameters->merge_fsr_photons_model()==3) {
       reinFSRmodel = new TFile(_globalparameters->merge_fsr_photons_model_file2());
       for (Int_t j=0; j<7; j++) {
	 for (Int_t i=0; i<12; i++) {
	   TString n;
	   n="FSRmodel_eff_";
	   n+=j;
	   n+="_";
	   n+=(i+1);
	   _FSRmodel_eff_eta[j][i]=(TH1D*)reinFSRmodel->Get(n);
	 }
	 for (Int_t i=0; i<12; i++) {
	   TString n;
	   n="FSRmodel_loss_";
	   n+=j;
	   n+="_";
	   n+=(i+1);
	   _FSRmodel_loss_eta[j][i]=(TH1D*)reinFSRmodel->Get(n);
	 }
       }
     } else if (_globalparameters->merge_fsr_photons_model()==4 || _globalparameters->merge_fsr_photons_model()==6) {
       reinFSRmodel = new TFile(_globalparameters->merge_fsr_photons_model_file2());
       for (Int_t j=0; j<7; j++) {
	 for (Int_t jj=0; jj<4; jj++) {
	   for (Int_t i=0; i<12; i++) {
	     TString n;
	     n="FSRmodel_eff_";
	     n+=j;
	     n+="_";
	     n+=jj;
	     n+="_";
	     n+=(i+1);
	     _FSRmodel_eff_eta_e[j][jj][i]=(TH1D*)reinFSRmodel->Get(n);
	   }
	   for (Int_t i=0; i<12; i++) {
	     TString n;
	     n="FSRmodel_loss_";
	     n+=j;
	     n+="_";
	     n+=jj;
	     n+="_";
	     n+=(i+1);
	     _FSRmodel_loss_eta_e[j][jj][i]=(TH1D*)reinFSRmodel->Get(n);
	   }
	 }
       }
       TH2D* Esummary=(TH2D*)reinFSRmodel->Get("esummary");
       for (Int_t j=0; j<7; j++) {
	 for (Int_t jj=0; jj<4; jj++) {
	   _FSResummary[j][jj]=Esummary->GetBinContent(j+1,jj+1);
	 }
       }
     }
   }

   // if we want to do PDF reweight
   // will calculate weight for all 45 PDFs, hardcoded
   _doPdfReweight = _globalparameters->pdfreweight();
   if(_doPdfReweight) {
     // Initialize PDF sets
     const int PDFSET= _globalparameters->pdfori_subset();
     const string NAME = _globalparameters->pdfori();
#ifdef __USE_PDFS_RESBOS__
     _neigen = 22;
     for( int i = 0 ; i < 2*_neigen+1 ; i++ )
       pmcs_ana_pdf_wgts[i] = 1.0;
#endif
#ifdef __USE_PDFS__
     LHAPDF::initPDFSetM(1, NAME,  LHAPDF::LHGRID);
     LHAPDF::initPDFSetM(2, NAME,  LHAPDF::LHGRID);
     _neigen =  LHAPDF::numberPDFM(2)/2;
     if (2*_neigen+1 > 45){
	std::cout <<" pmcsana:: PDFWeightFactor[] has size 45, and you have asked for " << std::flush;
        std::cout << 2*_neigen+1 <<  " variations, please change the size of the vector and pdfreweights[] in PMCSEvent" << std::endl;	  
     }
     cout << "Number of eigensets in this fit = " << _neigen << endl;
     cout << "alphas(mz) = " << LHAPDF::alphasPDFM(91.188) << endl;
     cout << "qcdlam4    = " << LHAPDF::getLam4M(1,PDFSET) << endl;
     cout << "qcdlam5    = " << LHAPDF::getLam5M(1,PDFSET) << endl;
     cout << "orderPDF   = " << LHAPDF::getOrderPDFM(1) << endl;
     cout << "xmin       = " << LHAPDF::getXminM(1,PDFSET) << endl;
     cout << "xmax       = " << LHAPDF::getXmaxM(1,PDFSET) << endl;
     cout << "q2min      = " << LHAPDF::getQ2minM(1,PDFSET) << endl;
     cout << "q2max      = " << LHAPDF::getQ2maxM(1,PDFSET) << endl;
     cout << "orderalfas = " << LHAPDF::getOrderAlphaSM(1) << endl;
     cout << "name       = " << NAME << endl;
     cout << "number     = " << LHAPDF::numberPDFM(2) << endl;
     cout << endl;
   LHAPDF::initPDFM(1,PDFSET);
#endif
   } // initialize all PDFs

   // histograms for phi star reweighting
   if (_globalparameters->phistarreweight()) {
     Double_t lowboundt2[30] = {
       0.000, 0.010, 0.020, 0.030, 0.040,
       0.050, 0.060, 0.071, 0.081, 0.093,
       0.106, 0.121, 0.139, 0.162, 0.190,
       0.227, 0.275, 0.337, 0.418, 0.523,
       0.657, 0.827, 1.041, 1.309, 1.640,
       2.049, 2.547, 3.151, 3.878, 4.749 };
     _phistarDist[0] = new TH1D("truePhiStarEtabin_1", "truePhiStarEtabin_1", 29, lowboundt2);
     Double_t lowboundt3[30] = {
       0.000,  0.010,  0.020,  0.030,  0.040, 
       0.050,  0.060,  0.071,  0.081,  0.093, 
       0.106,  0.121,  0.139,  0.162,  0.190,
       0.227,  0.275,  0.337,  0.418,  0.523, 
       0.657,  0.827,  1.041,  1.309,  1.640,
       2.049,  2.547,  3.151,  3.878,  4.749 };
     _phistarDist[1] = new TH1D("truePhiStarEtabin_2", "truePhiStarEtabin_2", 29, lowboundt3);
     Float_t lowboundt4[26] = {
       0.000,  0.010,  0.020,   0.030,   0.040,   
       0.050,  0.060,  0.071,   0.081,   0.093,   
       0.106,  0.121,  0.139,   0.162,   0.190,   
       0.227,  0.275,  0.337,   0.418,   0.523,   
       0.657,  0.827,  1.041,   1.309,   1.640,
       2.049 };
     _phistarDist[2] = new TH1D("truePhiStarEtabin_3", "truePhiStarEtabin_3", 25, lowboundt4);
     //
     _phistarWT[0]=0; _phistarWT[1]=0; _phistarWT[2]=0;
     if (_globalparameters->phistarreweight_File().length()>4) {
       TFile* fWTphistar = new TFile(_globalparameters->phistarreweight_File().c_str());
       _phistarWT[0]=(TH1D*)fWTphistar->Get("ratioPhiStarEtabin_1");
       _phistarWT[1]=(TH1D*)fWTphistar->Get("ratioPhiStarEtabin_2");
       _phistarWT[2]=(TH1D*)fWTphistar->Get("ratioPhiStarEtabin_3");
     }
   }

   // initialize random number generator
   if (_randomseed==0) {
     _dummy = new TRandom3(_globalparameters->rand_seed());
     cout << "pmcsana: Using random seed = " << _globalparameters->rand_seed() << endl;
   }
   else {
     _dummy = new TRandom3(_randomseed);
     cout << "pmcsana: Using random seed = " << _randomseed << endl;
   }

   // also set gRandom points to the instance of TRandom3
   gRandom = _dummy;

   // initialize analysis object
   if(_runoption == 0) {
     cout<<"Initialize ZAnalysis"<<endl;
     _zanalysis = new ZAnalysis(_parameter_filename,_dummy);
   } else if(_runoption == 1) {
     cout<<"Initialize WAnalysis"<<endl;
     _wanalysis = new WAnalysis(_parameter_filename,_dummy);
   } else if(_runoption == 2) {
     cout<<"Initialize ZMuAnalysis"<<endl;
     _zmuanalysis = new ZMuAnalysis(_parameter_filename);
   } else if(_runoption == 3) {
     cout<<"Initialize JPsiMuAnalysis"<<endl;
     _jpsimuanalysis = new JPsiMuAnalysis(_parameter_filename);
   } else if(_runoption == 4) {
     cout<<"Initialize ZNuNuAnalysis"<<endl;
     _znunuanalysis = new ZNuNuAnalysis(_parameter_filename,_dummy);
     // also need to read parameters for ZNuNuAnalysis to count Loos and Tight neutrinos
     PParameterReader parm(_parameter_filename.Data());  
     _NuLoose_EtaMax = parm.GetDouble("ZNuNu_NuLoose_EtaMax", 1000.0);  // no cut
     _NuLoose_PtMin  = parm.GetDouble("ZNuNu_NuLoose_PtMin",  0.0);     // no cut
     _NuTight_EtaMax = parm.GetDouble("ZNuNu_NuTight_EtaMax", 1000.0);  // no cut
     _NuTight_PtMin  = parm.GetDouble("ZNuNu_NuTight_PtMin",  0.0);     // no cut
     if(( _NuTight_PtMin < _NuLoose_PtMin ) || 
	( _NuTight_EtaMax > _NuLoose_EtaMax )) {
       cerr << "pmcsana: Wrong specification of Loose and Tight cuts!!!" << endl
	    << "         pT(Loose nu)>=" << _NuLoose_PtMin 
	    << " GeV, |eta(Loose nu)|<" << _NuLoose_EtaMax << endl
	    << "         pT(Tight nu)>=" << _NuTight_PtMin 
	    << " GeV, |eta(Tight nu)|<" << _NuTight_EtaMax << endl;
       throw;
     }
   } 

   // initialize beam spot 
   if(_globalparameters->VtxSmear_Option()==1) {
     cout<<"Initializing beamspot dependence on the run ranges and instantaneous luminosity now ..."<<endl;
     _beam = new BeamWeight((string)(_globalparameters->BeamSpotShape_file()));
     cout<<"Finished beamspot"<<endl;
   }

   // read instantaneous luminosity profile
   _instlumi_profile = _globalparameters->instlumi_profile();
   _instlumi_runNo_profile = _globalparameters->instlumi_runNo_profile();
   if( _instlumi_runNo_profile )
   {
     _instlumi_runNo_profile_X = (TH1F*)_instlumi_runNo_profile->ProjectionX();
     _instlumi_runNo_profile_Y = (TH1F*)_instlumi_runNo_profile->ProjectionY();
   }
  if( _runoption == 0 && _zanalysis->getRecoilSmear()->read_recoil_file()) {
    _instlumi_runNo_profile_X = _zanalysis->getRecoilSmear()->InstLumiHist();
    _instlumi_runNo_profile_Y = _zanalysis->getRecoilSmear()->RunNoHist();
  }
  else if( _runoption == 1 && _wanalysis->getRecoilSmear()->read_recoil_file() ) {
    _instlumi_runNo_profile_X = _wanalysis->getRecoilSmear()->InstLumiHist();
    _instlumi_runNo_profile_Y = _wanalysis->getRecoilSmear()->RunNoHist();    
  }
    
   cout<<"End pmcsana::Initialize"<<endl;
}

void pmcsana::Begin(TTree *tree) {};

void pmcsana::SlaveBegin(TTree *tree) {
  Init(tree);
  TString option = GetOption();
}

pmcsana::~pmcsana() {
  if(_zanalysis!=NULL) delete _zanalysis;
  if(_wanalysis!=NULL) delete _wanalysis;
  if(_zmuanalysis!=NULL) delete _zmuanalysis;
  if(_jpsimuanalysis!=NULL) delete _jpsimuanalysis;
  if(_znunuanalysis!=NULL) delete _znunuanalysis;
  if(_dummy!=NULL) delete _dummy;
}

// process event
Bool_t pmcsana::Process(Long64_t entry) {

  //skip this part if doing ZAnalysis in a MINUIT mode with event selection disabled
  if(_runoption==0 && _zanalysis->MINUIT_skipPreselection()) return false;
 
  //how often do we print out the number of events processed?
  static int update_frequency = _globalparameters->update_frequency();
  static int eventsProcessed = 0; 
  if(eventsProcessed%update_frequency==0) cout<<"Processing event number: "<< eventsProcessed 
				    << " / " << _numEvents << endl;
  eventsProcessed++;
  
  //  
  // construct PMCS event information and put all information into PMCSEvent class
  //
  double evtweight;
  PMCSParticle wzboson_gen;
  vector<PMCSEMObj> emobjs_gen;
  vector<PMCSEMObj> emobjs_gen_raw;
  vector<PMCSEMObj> emobjs_gen_raw_wfsr;
  vector<PMCSMuon> muons_gen;
  PMCSMet met_gen;
  PMCSRecoil recoil_gen;
  PMCSVtx vtx_gen;

  // run number and instantaneous luminosity for this zerobias event
  // also keep the index so that we will use the same event for overlay
  int runNo = 1, evtNo = -1, ZBEvtIndex = -1, MBEvtIndex = -1;
  double instlumi = 0.;
  
  //
  // get run number and instantaneous luminosity from zerobias overlay
  // also keep the indices for the overlaid zerobias and minbias events
  // only need for ZAnalysis and WAnalysis, not relevant for ZMuAnalysis and JPsiMuAnalysis
  // if we read recoil file, then we do not need to get the indices to the overlaid Minbias and Zerobias events
  //
  if(_runoption == 0) {
    // only read the zerobias library for the traditional method, and when making recoil library file
    
    if( _zanalysis->getRecoilSmear()->read_recoil_file() )
    {
      double drunNo;
//       _instlumi_runNo_profile->GetRandom2(instlumi, drunNo);
      instlumi = _instlumi_runNo_profile_X->GetRandom();
//       instlumi = _instlumi_profile->GetRandom();
      drunNo = _instlumi_runNo_profile_Y->GetRandom();
      runNo = (int) drunNo;
      if( _zanalysis->getEfficiencySmear()->run_has_triggers(runNo) == 0 && _zanalysis->getEfficiencySmear()->run_has_triggers(runNo+1) > 0 )
          runNo++;
    }
    else if(_zanalysis->getRecoilSmear()->METSmear_Option()==3){
      _zanalysis->getRecoilSmear()->setRunNoInstLumiMBZBEvtIndex(_dummy); 
      _zanalysis->getRecoilSmear()->getRunNoEvtNoInstLumiMBZBEvtIndex(runNo, evtNo, instlumi, MBEvtIndex, ZBEvtIndex);
      int selector = _zanalysis->getTrigSelector();
	if (selector){
	int flag = _zanalysis->getEfficiencySmear()->TriggerType(runNo);
	while (!(flag==selector)){
	  _zanalysis->getRecoilSmear()->setRunNoInstLumiMBZBEvtIndex(_dummy);
	  _zanalysis->getRecoilSmear()->getRunNoEvtNoInstLumiMBZBEvtIndex(runNo, evtNo, instlumi, MBEvtIndex, ZBEvtIndex);
	  flag = _zanalysis->getEfficiencySmear()->TriggerType(runNo);
	}
      }
    }
    
    // if we do not read the mb and zb library files, will get the luminosity from a histogram
    if(_zanalysis->getRecoilSmear()->METSmear_Option()!=3)  
      instlumi =_instlumi_profile->GetRandom();
  } else if(_runoption == 1) {

    // If recoil library method, get luminosity and run Number from appropriate 2D histogram 
    // of the lumi/runNo spectrum of  the recoil file
    // need them for the primary vertex reweighting for real data analysis
    //    cout << "RCLSA RCLSA RCLSA " << _wanalysis->getRecoilSmear()->read_recoil_file() << endl;
      // read the zerobias library no matter for the traditional method
    if(_wanalysis->getRecoilSmear()->METSmear_Option()==3){
      _wanalysis->getRecoilSmear()->setRunNoInstLumiMBZBEvtIndex(_dummy);  
      _wanalysis->getRecoilSmear()->getRunNoEvtNoInstLumiMBZBEvtIndex(runNo, evtNo, instlumi, MBEvtIndex, ZBEvtIndex); 
      int selector = _wanalysis->getTrigSelector();
      if (selector){
	int flag = _wanalysis->getEfficiencySmear()->TriggerType(runNo);
	while (!(flag==selector)){
	  _wanalysis->getRecoilSmear()->setRunNoInstLumiMBZBEvtIndex(_dummy);
	  _wanalysis->getRecoilSmear()->getRunNoEvtNoInstLumiMBZBEvtIndex(runNo, evtNo, instlumi, MBEvtIndex, ZBEvtIndex);
	  flag = _wanalysis->getEfficiencySmear()->TriggerType(runNo);
	}
      }
    }
    
  } else if(_runoption == 4) {
    if (_znunuanalysis->getRecoilSmear()->METSmear_Option()==3){
      _znunuanalysis->getRecoilSmear()->setRunNoInstLumiMBZBEvtIndex(_dummy);
    }
  }
  
  // read all generator level information from pmcs_ana branch
  double LeadingFSR_ET;
  double LeadingFSR_dR;
  double LeadingFSR_x;
  double TrailingFSR_ET;
  int FSR_nPhot, FSR_nInConePhot, FSR_nOutConePhot;
  if (!_globalparameters->cutOnLeadingFSR() && !_globalparameters->cutOnTrailingFSR() && !_globalparameters->cutOnFSRnPhot()) {
    if (!constructPMCSEvent(entry, runNo, instlumi, evtweight, wzboson_gen, emobjs_gen_raw,  emobjs_gen_raw_wfsr, emobjs_gen,
			    met_gen, recoil_gen, vtx_gen, muons_gen, false, LeadingFSR_ET, LeadingFSR_dR, LeadingFSR_x, TrailingFSR_ET, FSR_nPhot, FSR_nInConePhot, FSR_nOutConePhot, _dummy))
      return false;
  } else {
    if (!constructPMCSEvent(entry, runNo ,instlumi, evtweight, wzboson_gen, emobjs_gen_raw,  emobjs_gen_raw_wfsr, emobjs_gen, 
			    met_gen, recoil_gen, vtx_gen, muons_gen, true, LeadingFSR_ET, LeadingFSR_dR, LeadingFSR_x, TrailingFSR_ET, FSR_nPhot, FSR_nInConePhot, FSR_nOutConePhot, _dummy))
      return false;
    if (_globalparameters->cutOnLeadingFSR()) {
      if (LeadingFSR_ET<_globalparameters->LeadingFSR_ETmin()) return kFALSE;
      if (LeadingFSR_ET>_globalparameters->LeadingFSR_ETmax()) return kFALSE;
      if (LeadingFSR_dR<_globalparameters->LeadingFSR_dRmin()) return kFALSE;
      if (LeadingFSR_dR>_globalparameters->LeadingFSR_dRmax()) return kFALSE;
      if (LeadingFSR_x<_globalparameters->LeadingFSR_xmin()) return kFALSE;
      if (LeadingFSR_x>_globalparameters->LeadingFSR_xmax()) return kFALSE;
    }
    if (_globalparameters->cutOnTrailingFSR()) {
      if (TrailingFSR_ET<_globalparameters->TrailingFSR_ETmin()) return kFALSE;
      if (TrailingFSR_ET>_globalparameters->TrailingFSR_ETmax()) return kFALSE;
    }
    if (_globalparameters->cutOnFSRnPhot()) {
      if (FSR_nPhot<_globalparameters->FSR_nPhot_min()) return kFALSE;
      if (FSR_nPhot>_globalparameters->FSR_nPhot_max()) return kFALSE;
      if (FSR_nInConePhot<_globalparameters->FSR_nInConePhot_min()) return kFALSE;
      if (FSR_nInConePhot>_globalparameters->FSR_nInConePhot_max()) return kFALSE;
      if (FSR_nOutConePhot<_globalparameters->FSR_nOutConePhot_min()) return kFALSE;
      if (FSR_nOutConePhot>_globalparameters->FSR_nOutConePhot_max()) return kFALSE;
    }
  }

  // construct pmcsEvent for future use
  PMCSEvent pmcsevent(runNo, evtNo, MBEvtIndex, ZBEvtIndex, evtweight, instlumi, wzboson_gen, emobjs_gen_raw, emobjs_gen_raw_wfsr, emobjs_gen, 
		      met_gen, recoil_gen, vtx_gen, muons_gen);

#ifdef __USE_PDFS__
  for( int n = 0 ; n < _neigen*2+1; n++ ) {
     pmcsevent.pdfreweights[n] = PDFWeightFactor[n];
  }
#endif

#ifdef __USE_PDFS_RESBOS__
  for( int n = 0 ; n < _neigen*2+1; n++ ) {
     pmcsevent.pdfreweights[n] = PDFWeightFactor[n];
  }
#endif

  // dump_mctruth
  if (_globalparameters->dump_mctruth()){
        PMCSEMObj atpart;
        std::cout << "DT " << eventsProcessed << " " << "WZ " << wzboson_gen.ppid() << " " << wzboson_gen.pE() << " " << wzboson_gen.ppx() << " " << wzboson_gen.ppy() << " " << wzboson_gen.ppz() << " "
                  << vtx_gen.vtxz() << " " << std::endl;
        for (int ipart=0; ipart<emobjs_gen_raw.size(); ipart++){
          atpart = emobjs_gen_raw.at(ipart);
          std::cout << "DT " << eventsProcessed << " " << "RawEle " << atpart.ppid() << " " << atpart.pE() << " " << atpart.ppx() << " " << atpart.ppy() << " " << atpart.ppz() << " "
                    << vtx_gen.vtxz() << " " << std::endl;
        }
        for (int ipart=0; ipart<emobjs_gen.size(); ipart++){
          atpart = emobjs_gen.at(ipart);
          std::cout << "DT " << eventsProcessed << " " << "GoodEM " << atpart.ppid() << " " << atpart.pE() << " " << atpart.ppx() << " " << atpart.ppy() << " " << atpart.ppz() << " "
                    << vtx_gen.vtxz() << " " << std::endl;
        }
  }

  // whether we want t  do vertex cut
  if(_globalparameters->do_zvtx_cut() && 
     fabs(vtx_gen.vtxz()) > _globalparameters->zvtx_cut()) {  
    return kFALSE;               // skip this event
  } else{                        // analyze this event
    if(_runoption == 0) _zanalysis->analyzeEvent(pmcsevent, _dummy);  
    if(_runoption == 1) _wanalysis->analyzeEvent(pmcsevent, _dummy);    
    if(_runoption == 2) _zmuanalysis->analyzeEvent(pmcsevent, _dummy);    
    if(_runoption == 3) _jpsimuanalysis->analyzeEvent(pmcsevent, _dummy);        
    if(_runoption == 4) {
      // used for Z->nunu analysis, need to apply cuts on generator level neutrinos
      b_pmcs_ana->GetEntry(entry);
      int nLooseNeutrinos = 0, nTightNeutrinos = 0;
      for(int ipart=0; ipart<pmcs_ana_npart; ipart++) {
        double pid = pmcs_ana_ppid[ipart];
        if(abs(pid)==12 || abs(pid)==14 || abs(pid)==16) {
          double eta = pmcs_ana_peta[ipart];
	  double pt  = pmcs_ana_ppt[ipart];
	  if( fabs(eta)<_NuLoose_EtaMax && pt>_NuLoose_PtMin) nLooseNeutrinos++;
	  if( fabs(eta)<_NuTight_EtaMax && pt>_NuTight_PtMin) nTightNeutrinos++;
        }
      } // loop over all particles to find neutrinos
      _znunuanalysis->analyzeEvent(pmcsevent, nLooseNeutrinos, nTightNeutrinos, _dummy);        
    }
    return kTRUE;
  }

}

// SlaveTerminate
void pmcsana::SlaveTerminate() {};

// Terminate
void pmcsana::Terminate() {};

int pmcsana::WriteOut() {
  if(_runoption == 0) _zanalysis -> jobSummary(_dummy, _numEvents);  
  if(_runoption == 1) _wanalysis -> jobSummary();
  if(_runoption == 2) _zmuanalysis -> jobSummary();  
  if(_runoption == 3) _jpsimuanalysis -> jobSummary();
  if(_runoption == 4) _znunuanalysis -> jobSummary();
  // histograms for phi star reweighting
  if (_globalparameters->phistarreweight()) {
    TFile* fPhiStar = new TFile("phistar.root","RECREATE");
    for (Int_t i=0; i<3; i++) _phistarDist[i]->Write();
    fPhiStar->Close();
  }
  return 0;
}

// construct PMCSEvent
bool pmcsana::constructPMCSEvent(Int_t entry, int runNo, double instlumi, double& evtweight, PMCSParticle& wzboson, vector<PMCSEMObj>& emobjs_raw, 
                                 vector<PMCSEMObj>& emobjs_raw_wfsr, vector<PMCSEMObj>& emobjs,
				 PMCSMet& met, PMCSRecoil& recoil, PMCSVtx& vtx, vector<PMCSMuon>& muons, 
				 bool selectLeadingFSR, double& LeadFSR_ET, double& LeadFSR_dR, double& LeadFSR_x, double& TrailFSR_ET, int& FSR_nPhot, int& FSR_nInConePhot, int& FSR_nOutConePhot,
				 TRandom3 *dummy) {
  b_pmcs_ana->GetEntry(entry);
  b_pmcs_vtx->GetEntry(entry);

  // Event Weight, if we do not want to read event weight, set all of them to 1
  evtweight = pmcs_ana_evwt[0];
  if(!(_globalparameters->reweight())) evtweight = 1.;

  // calculate PDF weight factor
  if(_doPdfReweight) {
#ifdef __USE_PDFS__
    double x1 = pmcs_ana_evx1[0];
    double x2 = pmcs_ana_evx2[0];
    int flav1 = (int)(pmcs_ana_evflav1[0]);
    int flav2 = -(int)(pmcs_ana_evflav2[0]); //ubar distribution in pbar is the u distribution in the p

    double q = sqrt(pmcs_ana_evqsq[0]);

    double rpdfini1 = LHAPDF::xfxM(1, x1, q, flav1);
    double rpdfini2 = LHAPDF::xfxM(1, x2, q, flav2);

    for(int i=0; i< 2*_neigen+1; ++i) {
      LHAPDF::initPDFM(2,  i);
      double rpdfnew1 = LHAPDF::xfxM(2, x1, q, flav1);
      double rpdfnew2 = LHAPDF::xfxM(2, x2, q, flav2);
      
      double rpdfweight = 1.;
      if(rpdfini1!=0 && rpdfnew1!=0) rpdfweight *= rpdfnew1/rpdfini1;
      if(rpdfini2!=0 && rpdfnew2!=0) rpdfweight *= rpdfnew2/rpdfini2;
      // fill the static variables
      PDFWeightFactor[i] = rpdfweight;
      
    } // 41 PDF sets
#endif
#ifdef __USE_PDFS_RESBOS__
    for( int i = 0 ; i < _neigen*2+1 ; i++ )
    {
      PDFWeightFactor[i] = pmcs_ana_pdf_wgts[i];
    }
#endif
  } // PDF reweight

  // phi star reweighting
  if (_globalparameters->phistarreweight()) {
    Bool_t passesCuts=false;
    Float_t phistar=CalculateTruePhiStar(&passesCuts);
    Int_t theWZ=-1;
    for(int ipart=0; ipart<pmcs_ana_npart; ipart++) {
      if (abs(pmcs_ana_ppid[ipart]==23) || (abs(pmcs_ana_ppid[ipart]==24))) theWZ=ipart;
    }
    if (theWZ>=0) {
      TLorentzVector theWZvec = TLorentzVector(pmcs_ana_ppx[theWZ],pmcs_ana_ppy[theWZ],pmcs_ana_ppz[theWZ],pmcs_ana_pE[theWZ]);
      //cout<<"boson: "<<theWZvec.Pt()<<" "<<theWZvec.Rapidity()<<endl;
      Float_t absY=fabs(theWZvec.Rapidity());
      if (passesCuts) {
	if (absY<1) {
	  _phistarDist[0]->Fill(phistar,evtweight);
	} else if (absY<2) {
	  _phistarDist[1]->Fill(phistar,evtweight);
	} else {
	  _phistarDist[2]->Fill(phistar,evtweight);
	}
	if (_phistarWT[0]) {
	  TH1D* wt=0;
	  if (absY<1) {
	    wt=_phistarWT[0];
	  } else if (absY<2) {
	    wt=_phistarWT[1];
	  } else {
	    wt=_phistarWT[2];
	  }
	  if (phistar>wt->GetXaxis()->GetXmin() && phistar<wt->GetXaxis()->GetXmax()) {
	    evtweight*=(wt->GetBinContent(wt->GetXaxis()->FindBin(phistar)));
	    //cout<<"Weight: "<<(wt->GetBinContent(wt->GetXaxis()->FindBin(phistar)))<<endl;
	  }
	}
      }
    }
  }

  // primary vertex
  vtx = PMCSVtx(0., 0., pmcs_vtx_vtxzg[0]);

  // need to smear vertex here because I need to 
  // calculate electron detector eta and phi
  bool smearVertex = _globalparameters->smearVertex();
  double vtx_res = _globalparameters->VtxResolution();
  int vtxSmearOption = _globalparameters->VtxSmear_Option();
  if(smearVertex) {
    if(vtxSmearOption == 0) vtx.SmearVtx(vtx_res, dummy);
    else {
      if(_globalparameters->VtxApplyAsWeight()){
	// first smear primary vertex using a 40 cm gaussian function
	vtx.SmearVtx(40., dummy);
	// then calculate the event weight that is relative to this 40 cm gaussian
	double z = vtx.vtxz();
	std::pair<double, double> beamshape = _beam->beamshape(runNo, instlumi, z);
	double gaus = _beam->Gaussian(40, 0., z);
	// now we modify event weight
	evtweight *= beamshape.second/gaus;
      }else{
	bool good = false;
	int attempts = 0;

	//attempts typically < 10 or 20, 1000 is more than high enough.
	while (!good && attempts < 1000 ) {
	  Double_t z = _dummy->Gaus(0, 40.);
	  vtx.SetVtx(vtx.vtxx(), vtx.vtxy(), z);
	  Double_t gaus = TMath::Gaus(z, 0., 40.);
	  std::pair<double, double> beamshape = _beam->beamshape(runNo, instlumi, z);
	  Double_t rndm = dummy->Rndm()*gaus*beamshape.first;
	  if (rndm > beamshape.second) attempts++;
	  else good = true;
	}
	if( attempts >= 1000){ cout<<"PMCSANA: VTX REJECTION attempts fail"<<endl; return false;}
      }
    }
  }
  
  // Merge electron and photons
  if( _globalparameters->merge_fsr_photons() ) {
    if (selectLeadingFSR) {
      fixEMBlock(entry, vtx, _globalparameters->merge_fsr_radius_CC(), _globalparameters->merge_fsr_radius_EC(),instlumi,true,&LeadFSR_ET,&LeadFSR_dR,&LeadFSR_x,&TrailFSR_ET,&FSR_nPhot,&FSR_nInConePhot,&FSR_nOutConePhot);
    } else {
      fixEMBlock(entry, vtx, _globalparameters->merge_fsr_radius_CC(), _globalparameters->merge_fsr_radius_EC(),instlumi);
    }
  } else {
    if (selectLeadingFSR) {
      fixEMBlock(entry, vtx, -1.0, -1.0,true,instlumi,&LeadFSR_ET,&LeadFSR_dR,&LeadFSR_x,&TrailFSR_ET,&FSR_nPhot,&FSR_nInConePhot,&FSR_nOutConePhot);
    } else {
      fixEMBlock(entry, vtx, -1.0, -1.0,instlumi);
    }
  }

  // clear emobjs vector first  
  emobjs_raw.clear();
  emobjs_raw_wfsr.clear();
  emobjs.clear();

  // calculate W and Z boson ppx, ppy, ppz as the sum of ppx, ppy, ppz from electrons, photons and neutrinos
  // will do all loops, should not take much time since not many particles in the initial state
  double energy_WZ = 0., ppx_WZ = 0., ppy_WZ = 0., ppz_WZ = 0.;
  double eta_WZ = 0., phi_WZ = 0.;
  for(int ipart=0; ipart<pmcs_ana_npart; ipart++) {
    double pid = pmcs_ana_ppid[ipart];
    double pstable = pmcs_ana_pistable[ipart];
    
    // electrons and photons are treated differently since
    // we have to do electron-photon merging
    double energy = pmcs_ana_pE[ipart];
    double ppx = pmcs_ana_ppx[ipart];
    double ppy = pmcs_ana_ppy[ipart];
    double ppz = pmcs_ana_ppz[ipart];
    
    // in principle, any particle that is not W or Z boson or a TAU
    if(abs(pid)==11 || abs(pid)==22 ||   // electrons or photons
       abs(pid)==13 || ( abs(pid)==15 && pstable>0 ) ||   // muons or taus
       abs(pid)==12 || abs(pid)==14 || abs(pid)==16) {  // neutrinos
      energy_WZ += energy;
      ppx_WZ += ppx;
      ppy_WZ += ppy;
      ppz_WZ += ppz;
    }
  }
  
  eta_WZ = kinem::eta(ppx_WZ, ppy_WZ, ppz_WZ);
  phi_WZ = kinem::phi(ppx_WZ, ppy_WZ);
  
  double metx_raw = 0., mety_raw = 0., metz_raw = 0., met_E = 0.;
  // loop over all generator level particles
  for(int ipart=0; ipart<pmcs_ana_npart; ipart++) {
    double pid = pmcs_ana_ppid[ipart];

    // electrons and photons are treated differently since
    // we have to do electron-photon merging
    double eta = pmcs_ana_peta[ipart];
    double phi = pmcs_ana_pphi[ipart];
    double energy = pmcs_ana_pE[ipart];
    double pt = pmcs_ana_ppt[ipart];
    double ppx = pmcs_ana_ppx[ipart];
    double ppy = pmcs_ana_ppy[ipart];
    double ppz = pmcs_ana_ppz[ipart];
     
    if(abs(pid)==24 || abs(pid)==23) 
      //      wzboson = PMCSParticle(pid, energy, eta, phi, ppx, ppy, ppz);
      wzboson = PMCSParticle(pid, energy_WZ, eta_WZ, phi_WZ, ppx_WZ, ppy_WZ, ppz_WZ);

    if(abs(pid)==13) {
      PMCSMuon muon(pid, energy, eta, phi);
      muons.push_back(muon);
    } //muons

    // calculate raw missing Et using neutrino information
    if(abs(pid)==12 || abs(pid)==14 || abs(pid)==16) {
      metx_raw += ppx;
      mety_raw += ppy;
      metz_raw += ppz;
      met_E    += energy;     
    }
  } // loop over all particles

  // Missing energy
  met = PMCSMet(metx_raw, mety_raw);
  
  // for electrons, track pT and real pT may be different since 
  // electron and photons may merged (pmcs_em_elfid, pmcs_em_elpts are two unused variables in pmcs_em, 
  // I just use them to pass electron ID and track pT information)
  for(int j=0;j<pmcs_em_nelg;j++){ 
    PMCSEMObj emobj(pmcs_em_elfid[j], pmcs_em_eleg[j], pmcs_em_eletag[j], 
		    pmcs_em_elphig[j], pmcs_em_elpts[j], emobjs.size(),vtx.vtxz() );
    emobj.SetFSRxInCone(pmcs_em_elFSRxInCones[j]);
    emobj.SetFSRnInCone(pmcs_em_elFSRnInCones[j]);

    if(pmcs_em_elptg[j]>_globalparameters->pT_Cut()) {
      emobjs.push_back(emobj);
    }//pt cut
  }//electrons

  // electrons and photons are already merged here since I use pmcs_em branch information
  // for photons, track pT is the same as photon pTset to 0
  // so that later we will not calculate E/p for EMobjs that are really photons
  // all photons are treated as EMObjects
  for(int j=0;j<pmcs_em_nphg;j++){ 
    //    if(pmcs_em_phptg[j]>_globalparameters->pT_Cut()) {
    PMCSEMObj emobj(22, pmcs_em_pheg[j], pmcs_em_phetag[j], pmcs_em_phphig[j], 0.,emobjs.size(),vtx.vtxz());
    emobjs.push_back(emobj);
    //    }//pt cut
  }//photons
 
  // mainly used for Sahal's ratio method to pass generator level neutrino information
  if(_runoption == 1){
    TLorentzVector e(metx_raw, mety_raw,metz_raw, met_E);
    PMCSEMObj Nugen(12,e.E(),e.Eta(),e.Phi(),e.Pt(),-1,vtx.vtxz());
    emobjs.push_back(Nugen);
  }
 
  // have to loop over all EMObjs and calculate detector eta, phi in global and local coordinate systems  
  for(int iem=0; iem<emobjs.size(); iem++) {
    emobjs[iem].SetDetEtaDetPhi(vtx);
    emobjs[iem].SetDetEtaDetPhiGlobal(vtx);
  }

  int isMerged[pmcs_ana_npart];
  for(int j=0; j<pmcs_ana_npart; j++) isMerged[j]=0;
  //emobjs_raw_wfsr, with FSR photon merging but without FSR efficiency and response correction
  for(int j=0;j<pmcs_ana_npart;j++){
    if (TMath::Abs(pmcs_ana_ppid[j])==11) {
      TLorentzVector e(pmcs_ana_ppx[j],pmcs_ana_ppy[j], pmcs_ana_ppz[j],pmcs_ana_pE[j]);
      for(int jph=0;jph<pmcs_ana_npart;jph++){
        if (TMath::Abs(pmcs_ana_ppid[jph])==22 && pmcs_ana_pE[jph]>0.001) {
          TLorentzVector ph(pmcs_ana_ppx[jph],pmcs_ana_ppy[jph], pmcs_ana_ppz[jph],pmcs_ana_pE[jph]);

          if(fabs(e.Eta())<1.3 && (e.DeltaR(ph)<_globalparameters->merge_fsr_radius_CC()) && !isMerged[jph]) {
            double newE = e.E() + ph.E();
            double newPx = e.Px() + ph.E()*TMath::Sin(e.Theta())*TMath::Cos(e.Phi());
            double newPy = e.Py() + ph.E()*TMath::Sin(e.Theta())*TMath::Sin(e.Phi());
            double newPz = e.Pz() + ph.E()*TMath::Cos(e.Theta());
            e.SetPxPyPzE(newPx, newPy, newPz, newE);
            isMerged[jph] = 1;
          }
        } // if photon
      }// for all parts
      PMCSEMObj emobj(pmcs_ana_ppid[j], e.E(), e.Eta(),
                    e.Phi(), e.Pt(), emobjs_raw_wfsr.size(), vtx.vtxz()); 
      emobjs_raw_wfsr.push_back(emobj); 
    }// if electron
  } // emobjs_raw_wfsr

  // loop over all EMObjs and assign gen energy without FSR efficiency and response modeling
  for(int iem=0; iem<emobjs.size(); iem++) {
    double appid = emobjs[iem].ppid();
    TVector3 emobjvt = emobjs[iem].GetVect3();
    double energy_gen_wfsr = emobjs[iem].pE();
    // for electrons 
    if ( fabs(appid)<11.1 && fabs(appid)>10.9 ) {
      double mindR = 99999999.0;
      // loop over emobjs_raw_wfsr
      for (int iwfsr=0; iwfsr<emobjs_raw_wfsr.size(); iwfsr++){
        TVector3 wfsrvt = emobjs_raw_wfsr[iwfsr].GetVect3();
        double adR = wfsrvt.DeltaR(emobjvt);
        if (adR<mindR){
          mindR = adR;
          energy_gen_wfsr = emobjs_raw_wfsr[iwfsr].pE();
        }
      }
    }
    emobjs[iem].SetEnergyGenWFSR(energy_gen_wfsr);
  }


  for(int j=0;j<pmcs_ana_npart;j++){
    double elec_E = 0;
    double elec_pX = 0;
    double elec_pY = 0;
    double elec_pZ = 0;

    if( TMath::Abs(pmcs_ana_ppid[j])==11 )
    {
      TLorentzVector e(pmcs_ana_ppx[j],pmcs_ana_ppy[j], pmcs_ana_ppz[j],pmcs_ana_pE[j]);
      double eme = e.E();
      double empt = e.Pt();
      double emeta = e.Eta();
      double emphi = e.Phi();
      if(emphi<0.0) emphi += 2*TMath::Pi();
      elec_E = eme;
      elec_pX = empt*cos(emphi);
      elec_pY = empt*sin(emphi);
      elec_pZ = eme*cos(2*atan(exp(-emeta)));
      
      TLorentzVector ele( elec_pX , elec_pY , elec_pZ , elec_E );
      PMCSEMObj emobj( pmcs_ana_ppid[j] , elec_E , ele.Eta() , ele.Phi() , ele.Pt() , emobjs.size() , vtx.vtxz() );
      emobjs_raw.push_back( emobj );
    }
  }
  
  for(int iem=0; iem<emobjs_raw.size(); iem++) {
    emobjs_raw[iem].SetDetEtaDetPhi(vtx);
    emobjs_raw[iem].SetDetEtaDetPhiGlobal(vtx);
  }

  for(int iem=0; iem<emobjs_raw_wfsr.size(); iem++) {
    emobjs_raw_wfsr[iem].SetDetEtaDetPhi(vtx);
    emobjs_raw_wfsr[iem].SetDetEtaDetPhiGlobal(vtx);
  }

  // sort generator level electrons according to pT
  sort(emobjs.begin(), emobjs.end(), ComparePt);
  sort(emobjs_raw.begin(), emobjs_raw.end(), ComparePt);
  sort(emobjs_raw_wfsr.begin(), emobjs_raw_wfsr.end(), ComparePt);

  // recoil jet, same as WZ boson, except opposite direction
  double recoilx_system = -wzboson.ppx();
  double recoily_system = -wzboson.ppy();

  // the following code is commented out on 04/23/2007
  // we decided to treat fsr photons differently than the raw recoil
  // photons will always be assumed as an EM cluster, the energy response will be different
  // no UE simulation below electron window, and the photons will be added back to the smeared recoil system later

  // for photons that have very low pT and well separated from electrons
  // they should be treated as part of the recoil system 
  //  if(_globalparameters->merge_fsr_photons_recoil()) {
  //    for(int iph=0; iph<pmcs_em_nphg; iph++) {
  //      if(pmcs_em_phptg[iph] < _globalparameters->pT_Cut()) {
  //	recoilx_system += pmcs_em_phptg[iph] * cos(pmcs_em_phphig[iph]); 
  //	recoily_system += pmcs_em_phptg[iph] * sin(pmcs_em_phphig[iph]); 
  //      }
  //    } // loop over all photons
  //  } 
  
  // create vector for the recoil system
  recoil = PMCSRecoil(recoilx_system, recoily_system);

  //
  // print out information
  //
  if(_globalparameters->debug()) {
    cout<<"raw event weight: "<<evtweight<<endl;
    cout<<"    event vertex: ";
    vtx.Print();
    cout<<"    boson:        ";
    wzboson.Print();
    cout<<"    electrons:    ";
    for(int iem=0; iem<emobjs.size(); iem++) emobjs[iem].Print();
    cout<<"    muons:    ";
    for(int imu=0; imu<muons.size(); imu++) muons[imu].Print();
    cout<<"    event recoil: ";
    recoil.Print();
    cout<<"    event met:    ";
    met.Print();
  }
  return true;
}

// merge electron and photon if they are close to each other
void pmcsana::fixEMBlock(Int_t entry, PMCSVtx& vtx, double cut_dR_CC, double cut_dR_EC, double instlumi,
			 bool selectLeadingFSR, double* LeadFSR_ET, double* LeadFSR_dR, double* LeadFSR_x, double* TrailFSR_ET, int* FSR_nPhot, int* FSR_nInConePhot, int* FSR_nOutConePhot) {
  //Recreate pmcs_em from the pmcs_ana block.
  //Include FSR photon merging.
  
  // Shortcomings:
  //   * the electron-photon matching is too simple. it is possible
  //     that a photon is not assigned to the closest electron. i
  //     think the effect is incredibly tiny, though.
  //   * photon-electron merging is by four-vector addition. This should
  //     probably be changed to something resembling the EM clustering
  //     algorithm in the data.
  // 
  b_pmcs_ana->GetEntry(entry);

  // get primary vertex
  double vtxZ = vtx.vtxz();
  
  const Bool_t FDBG = kFALSE;

  Int_t nphi=0, neli=0;
  Int_t ph_indices[50];
  Int_t el_indices[50];
  Int_t nphiJ=0;
  Int_t ph_indicesJ[50];
  for(int i=0; i<50; i++) {
    ph_indices[i]=-1;
    el_indices[i]=-1;
    ph_indicesJ[i]=-1;
  }

  if(FDBG) printf("\n");
  
  //index all photons and electrons in the pmcs_ana block
  //if there are many particles in this event, this will save some time
  for(int ip = 0; ip < pmcs_ana_npart; ip++) {    
    if(TMath::Abs(pmcs_ana_ppid[ip])==22){ //photon w/o energy cut                                                                                       
      ph_indicesJ[nphiJ]=ip;
      nphiJ++;
    }
    if(TMath::Abs(pmcs_ana_ppid[ip])==22 && pmcs_ana_pE[ip]>0.001){ //photon      
      TLorentzVector ph(pmcs_ana_ppx[ip],pmcs_ana_ppy[ip], pmcs_ana_ppz[ip],pmcs_ana_pE[ip]);      
      if(FDBG) printf("Original photon: E=%.3f pT=%.3f eta=%0.3f phi=%0.3f ",
                      ph.E(),ph.Pt(),ph.Eta(),ph.Phi());
      
      ph_indices[nphi]=ip;
      nphi++;
      if(FDBG) cout<<endl;
    } else if(TMath::Abs(pmcs_ana_ppid[ip])==11){ //electron
      el_indices[neli]=ip;
      neli++;
    } 
  }//loop over all generator-level particles
  
  // Leading FSR analysis, if requested
  if (FSR_nPhot) *FSR_nPhot=0;
  if (FSR_nInConePhot) *FSR_nInConePhot=0;
  if (FSR_nOutConePhot) *FSR_nOutConePhot=0;
  if (selectLeadingFSR) {
    *LeadFSR_ET=-1;
    *LeadFSR_dR=9999;
    *LeadFSR_x=-1;
    *TrailFSR_ET=9999;
    for(int j=0;j<nphiJ;j++){
      if(ph_indicesJ[j] < 0) continue; //unused entry in ph_indices                                                                                      
      if (FSR_nPhot) (*FSR_nPhot)++;
      Int_t ip = ph_indicesJ[j];
      TLorentzVector ph(pmcs_ana_ppx[ip],pmcs_ana_ppy[ip], pmcs_ana_ppz[ip],pmcs_ana_pE[ip]); 
      double __mindR = 9999;
      for(int ke=0;ke<neli;ke++){
	Int_t ie = el_indices[ke];
	TLorentzVector e(pmcs_ana_ppx[ie],pmcs_ana_ppy[ie], pmcs_ana_ppz[ie],pmcs_ana_pE[ie]);	
	double dR=e.DeltaR(ph);
	__mindR = dR < __mindR ? dR : __mindR;
      }
      if (__mindR <= 0.3 && FSR_nInConePhot) (*FSR_nInConePhot)++;
      if (__mindR > 0.3 && FSR_nOutConePhot) (*FSR_nOutConePhot)++;
      if (ph.Pt()>*LeadFSR_ET) {
        *LeadFSR_ET=ph.Pt();
        *LeadFSR_dR=9999;
        *LeadFSR_x=-1;
        for(int ke=0;ke<neli;ke++){
          Int_t ie = el_indices[ke];
          TLorentzVector e(pmcs_ana_ppx[ie],pmcs_ana_ppy[ie], pmcs_ana_ppz[ie],pmcs_ana_pE[ie]);
          double dR=e.DeltaR(ph);
          if (dR<*LeadFSR_dR) {
            *LeadFSR_dR=dR;
            *LeadFSR_x=ph.E()/(ph.E()+e.E());
          }
        }
      }
      if (ph.Pt()<*TrailFSR_ET) {
	*TrailFSR_ET=ph.Pt();
      }
    }
  }

  pmcs_em_nelg=0;
  
  //loop over electrons
  for(int ke=0;ke<neli;ke++){
    Int_t ie = el_indices[ke];
    
    TLorentzVector e(pmcs_ana_ppx[ie],pmcs_ana_ppy[ie], pmcs_ana_ppz[ie],pmcs_ana_pE[ie]);
    TLorentzVector e_before(e);
    if(FDBG) printf("Electron: E=%.2f pT=%.2f eta=%0.2f phi=%0.2f\n",
                    e.E(),e.Pt(),e.Eta(),e.Phi());
    
    // track pT is the raw electron pT before it is merged with photons
    double trkpT = e_before.Pt();

    // counter for FSR x
    double FSRxInCone=0;
    int FSRnInCone=0;

    // does this electron survive the effect of FSR ?
    bool e_killed=false;
    
    if (_globalparameters->merge_fsr_photons_model()==1) {

      // merge closest photons
      for(int j=0;j<nphi;j++){ 
	if(ph_indices[j] < 0) continue; //unused entry in ph_indices
	Int_t ip = ph_indices[j];
      
	// use a simple cone (deltaR in CC and fixed radius in EC) to merge electrons and photons
	TLorentzVector ph(pmcs_ana_ppx[ip],pmcs_ana_ppy[ip], pmcs_ana_ppz[ip],pmcs_ana_pE[ip]);
	TVector3 calp_e=PCalTools::floorXYZ(vtxZ, e_before.Eta(), e_before.Phi());
	TVector3 calp_ph=PCalTools::floorXYZ(vtxZ, ph.Eta(), ph.Phi());
	bool isCC = false;
	if(fabs(calp_e.Eta())<1.3) isCC = true;
	
	if(isCC && FDBG) printf("    ph: eta=%.3f phi=%.3f E=%.3f R_CC=%.3f",
				ph.Eta(), ph.Phi(), ph.E(), ph.DeltaR(e));
	
	if(!isCC && FDBG) printf("    ph: eta=%.3f phi=%.3f E=%.3f R_EC=%.3f",
				 ph.Eta(), ph.Phi(), ph.E(), PCalTools::Deltar(calp_e, calp_ph));
	
	// decide whether to merge photons with the electron or not      
	bool merge = false;
	if(isCC) merge = (e_before.DeltaR(ph) < cut_dR_CC);
	else merge = (PCalTools::Deltar(calp_e, calp_ph) < cut_dR_EC);
	
	//
	// assume CC and EC photons have the same probability to reach the calorimetr
	// and the same response
	//
	if(merge) {
	  // probability for photons to reach the calorimeter
	  double prob_photon = 1.;
	  if(_simulate_merge_fsr_photons_in_cone_prob)      
	    prob_photon = wz_utils::photon_prob_in_cone(ph.Pt(), _merge_fsr_photons_in_cone_prob_p0, 
							_merge_fsr_photons_in_cone_prob_p1, _merge_fsr_photons_in_cone_prob_p2, 
							_merge_fsr_photons_in_cone_prob_p3);
	  
	  // remove the photons that are not supposed to reach the calorimeter permanently
	  double prob = _dummy->Uniform(0., 1.);
	  if(prob < prob_photon) {	  
	    
	    // calculate the fraction of photon energy merged with the EM cluster
	    double fraction = 1.;
	    if(_simulate_merge_fsr_photons_in_cone_response) 
	      fraction = wz_utils::photon_response_in_cone(ph.Eta(), ph.Pt(), _merge_fsr_photons_in_cone_response_p0,
							   _merge_fsr_photons_in_cone_response_p1, _merge_fsr_photons_in_cone_response_p2,
							   _merge_fsr_photons_in_cone_response_p3, _merge_fsr_photons_in_cone_response_p4,
							   _merge_fsr_photons_in_cone_response_p5);
	    
	    if(FDBG) printf(" ==> MERGED energy fraction=%.3f ", fraction);
	    ph_indices[j]=-1; //mark as found, remove this partially merged photons, is this the best way ???
	    e += fraction * ph;  //Merge. Is this the best way?
	  } else { // only a fraction of photons can reach the calorimeter
	    ph_indices[j] = -1;
	  } // throw away the photon that will not reach the calorimeter
	} // merged

      }

      if(FDBG) printf("\n");

    } else if (_globalparameters->merge_fsr_photons_model()==2 || _globalparameters->merge_fsr_photons_model()==3 || _globalparameters->merge_fsr_photons_model()==4
	       || _globalparameters->merge_fsr_photons_model()==6 || _globalparameters->merge_fsr_photons_model()==7 ) {

      if (FDBG) cout<<"======================================================================================"<<endl;

      // first loop to determine total photon energy
      Double_t totalPhotE=0;
      TLorentzVector e_merged=e_before;
      for(int j=0;j<nphi;j++){ 
	if(ph_indices[j] < 0) continue; //unused entry in ph_indices
	Int_t ip = ph_indices[j];
	TLorentzVector ph(pmcs_ana_ppx[ip],pmcs_ana_ppy[ip], pmcs_ana_ppz[ip],pmcs_ana_pE[ip]);
	if (FDBG) cout<<" "<<ph.Pt()<<" "<<ph.Eta()<<" "<<ph.Phi()<<" "<<ph.E()<<" "<<e_before.DeltaR(ph)<<endl;
	if (e_before.DeltaR(ph)<cut_dR_CC) {
	  totalPhotE+=ph.E();
	  e_merged+=ph;
	  FSRnInCone++;
	}
      }

      if (FDBG) cout<<"Total: "<<totalPhotE<<"    "<<e_merged.E()<<" "<<e_merged.Eta()<<endl;

      // second loop to actually do our work
      TLorentzVector e_probe(e_before);
      Int_t nphoz = 1;
      for(int j=0;j<nphi;j++){ 
	if(ph_indices[j] < 0) continue; //unused entry in ph_indices
	Int_t ip = ph_indices[j];
	TLorentzVector ph(pmcs_ana_ppx[ip],pmcs_ana_ppy[ip], pmcs_ana_ppz[ip],pmcs_ana_pE[ip]);
	if (e_before.DeltaR(ph)<cut_dR_CC) {	  
	  if (FDBG) cout<<" "<<ph.Pt()<<" "<<ph.Eta()<<" "<<ph.Phi()<<" "<<ph.E()<<" "<<e_before.DeltaR(ph)<<endl;
	  ph_indices[j] = -1;   // remove this photon from the list, no matter how we will ultimately treat it
	  //
	  Int_t dRbin=(Int_t)(e_before.DeltaR(ph)/0.05);
	  Double_t dum=fabs(e_merged.Eta());
	  Int_t etabin;
	  if (dum<0.1) {
	    etabin=0;
	  } else if (dum>1.4) {
	    etabin=-1;
	  } else {
	    etabin=(Int_t)((dum-0.1)/0.2)+1;
	    if (etabin>6) etabin=6;
	  }
	  Int_t ebin1=-1;
	  Int_t ebin2=-1;
	  if ((_globalparameters->merge_fsr_photons_model()==4 || _globalparameters->merge_fsr_photons_model()==6) && etabin>=0) {
	    ebin1=0;
	    while (ebin1<3 && e_merged.E()>_FSResummary[etabin][ebin1+1]) ebin1++;
	    ebin2=ebin1+1;
	    if (ebin2>3) ebin2=3;
	  }
	  Double_t X=ph.E()/(e_before.E()+totalPhotE);
	  FSRxInCone+=X;
	  // treat efficiency
	  Double_t theEff=0;
	  if (_globalparameters->merge_fsr_photons_model()==2 || fabs(e_merged.Eta())>1.4) {
	    Int_t Xbin=_FSRmodel_eff[dRbin]->FindBin(X);
	    theEff=_FSRmodel_eff[dRbin]->GetBinContent(Xbin);
	  } else if (_globalparameters->merge_fsr_photons_model()==3) {
	    Int_t Xbin=_FSRmodel_eff_eta[etabin][dRbin]->FindBin(X);
            theEff=_FSRmodel_eff_eta[etabin][dRbin]->GetBinContent(Xbin);
	  } else if (_globalparameters->merge_fsr_photons_model()==4 || _globalparameters->merge_fsr_photons_model()==6 ) {
	    Int_t Xbin1=_FSRmodel_eff_eta_e[etabin][ebin1][dRbin]->FindBin(X);
            Double_t theEff1=_FSRmodel_eff_eta_e[etabin][ebin1][dRbin]->GetBinContent(Xbin1);
	    Int_t Xbin2=_FSRmodel_eff_eta_e[etabin][ebin2][dRbin]->FindBin(X);
	    Double_t theEff2=_FSRmodel_eff_eta_e[etabin][ebin2][dRbin]->GetBinContent(Xbin2);
	    if (e_merged.E()<_FSResummary[etabin][0]) {
	      theEff=theEff1;
	    } else if (e_merged.E()>_FSResummary[etabin][3]) {
	      theEff=theEff2;
	    } else {
	      Double_t d=(e_merged.E()-_FSResummary[etabin][ebin1])/(_FSResummary[etabin][ebin2]-_FSResummary[etabin][ebin1]);
	      theEff=theEff1+d*(theEff2-theEff1);
	      if (FDBG) cout<<"interp "<<d<<" "<<theEff1<<" "<<theEff2<<endl;
	    }
	  } else if (_globalparameters->merge_fsr_photons_model()==7) {
	    etabin = wz_utils::getbin(fsrmodel7_etabins, TMath::Abs(e_probe.Eta()));
	    dRbin = wz_utils::getbin(fsrmodel7_drbins, e_probe.DeltaR(ph));
	    Double_t X_ = ph.E()/(e_probe.E()+ph.E());
	    if (_globalparameters->fsrmodel7_interpolate()) {
	      wz_utils::interpolate2d(_FSRmodel_eff_lumi_eta_e_dr[dRbin][etabin], fsrmodel7_lumibins, fsrmodel7_ebins, _FSRlumisummary[etabin], _FSResummary2[etabin], instlumi, e_probe.E()+ph.E(), X_, theEff);
	    } else {
	      Int_t ebin_ = wz_utils::getbin(fsrmodel7_ebins, e_probe.E()+ph.E());
	      Int_t lumibin_ = wz_utils::getbin(fsrmodel7_lumibins, instlumi);
	      Int_t Xbin_ = _FSRmodel_eff_lumi_eta_e_dr[dRbin][etabin][lumibin_][ebin_]->FindBin(X_);
	      theEff = _FSRmodel_eff_lumi_eta_e_dr[dRbin][etabin][lumibin_][ebin_]->GetBinContent(Xbin_);
	    }

	  }

	  if (_globalparameters->merge_fsr_photons_model()!=7) {	    
	    Double_t prob = _dummy->Uniform(0., 1.);
	    if(prob > theEff) e_killed=true;
	    
	  } else if (_globalparameters->merge_fsr_photons_model()==7) {	    
	    Double_t prob = _dummy->Uniform(0., 1.);
	    theEff *= (1- ( (nphoz-1) * _globalparameters->fsrmodel7_norm() ) );
	    if(prob > theEff) e_killed=true;
	    nphoz++;
 	  }	  
	 
	  //	  if (FDBG) cout<<"  "<<dRbin<<" "<<etabin<<" "<<ebin1<<" "<<ebin2<<"  "<<X<<" "<<theEff<<" "<<prob<<endl;


	  if (!e_killed) {
	    // treat energy
	    Double_t theKappa;
	    if (_globalparameters->merge_fsr_photons_model()==2 || fabs(e_merged.Eta())>1.4) {
	      Int_t Xbin=_FSRmodel_loss[dRbin]->FindBin(X);
	      theKappa=_FSRmodel_loss[dRbin]->GetBinContent(Xbin);
	    } else if (_globalparameters->merge_fsr_photons_model()==3) {
	      Int_t Xbin=_FSRmodel_loss_eta[etabin][dRbin]->FindBin(X);
              theKappa=_FSRmodel_loss_eta[etabin][dRbin]->GetBinContent(Xbin);
	    } else if (_globalparameters->merge_fsr_photons_model()==4|| _globalparameters->merge_fsr_photons_model()==6  ) {
	      Int_t Xbin1=_FSRmodel_loss_eta_e[etabin][ebin1][dRbin]->FindBin(X);
              Double_t theKappa1=_FSRmodel_loss_eta_e[etabin][ebin1][dRbin]->GetBinContent(Xbin1);
	      Int_t Xbin2=_FSRmodel_loss_eta_e[etabin][ebin2][dRbin]->FindBin(X);
	      Double_t theKappa2=_FSRmodel_loss_eta_e[etabin][ebin2][dRbin]->GetBinContent(Xbin2);
	      if (e_merged.E()<_FSResummary[etabin][0]) {
		theKappa=theKappa1;
	      } else if (e_merged.E()>_FSResummary[etabin][3]) {
		theKappa=theKappa2;
	      } else {
		Double_t d=(e_merged.E()-_FSResummary[etabin][ebin1])/(_FSResummary[etabin][ebin2]-_FSResummary[etabin][ebin1]);
		theKappa=theKappa1+d*(theKappa2-theKappa1);
	      }
	    
	    } else if (_globalparameters->merge_fsr_photons_model()==7) {
	      etabin = wz_utils::getbin(fsrmodel7_etabins, TMath::Abs(e_probe.Eta()));
	      dRbin = wz_utils::getbin(fsrmodel7_drbins, e_probe.DeltaR(ph));
	      Double_t X_ = ph.E()/(e_probe.E()+ph.E());

	      //update July 02 2014: interpolate option applies only to efficiency.
	      // if (_globalparameters->fsrmodel7_interpolate()) {
	      //	wz_utils::interpolate2d(_FSRmodel_loss_lumi_eta_e_dr[dRbin][etabin], fsrmodel7_lumibins, fsrmodel7_ebins, _FSRlumisummary[etabin], _FSResummary2[etabin], instlumi, e_probe.E()+ph.E(), X_, theKappa);
	      // } else {
		Int_t ebin_ = wz_utils::getbin(fsrmodel7_ebins, e_probe.E()+ph.E());
		Int_t lumibin_ = wz_utils::getbin(fsrmodel7_lumibins, instlumi);
		Int_t Xbin_ = _FSRmodel_loss_lumi_eta_e_dr[dRbin][etabin][lumibin_][ebin_]->FindBin(X_);
		theKappa = _FSRmodel_loss_lumi_eta_e_dr[dRbin][etabin][lumibin_][ebin_]->GetBinContent(Xbin_);
		// }
	    }
	    e_probe *= (e_probe.E()+ph.E())/e_probe.E();
	    Double_t theE=ph.E()*(1+theKappa);
	    Double_t newE=e.E()+theE;
	    Double_t newPt=newE*sin(e.Theta());
	    if (FDBG) cout<<"  "<<theKappa<<" "<<theE<<" "<<newE<<" "<<newPt<<endl;
	    e.SetPtEtaPhiM(newPt,e.Eta(),e.Phi(),0.000510);
	  }
	}
      }

    }
    
    //If we have survived FSR, create pmcs_em object (generated quantities only)
    if (!e_killed) {
      if(FDBG){
	printf("    pmcs_em entry: %.2f->%.2f  Pt: %.2f->%.2f  "
	       "Eta: %.2f->%.2f  Phi: %.2f->%.2f\n",
	       e_before.E(),e.E(),
	       e_before.Pt(),e.Pt(),
	       e_before.Eta(),e.Eta(),
	       e_before.Phi()>0.0?e_before.Phi():e_before.Phi()+2*TMath::Pi(),
	       e.Phi()>0.0?e.Phi():e.Phi()+2*TMath::Pi());
      }
    
      pmcs_em_eleg[ke]=e.E();
      pmcs_em_elptg[ke]=e.Pt();
      pmcs_em_eletag[ke]=e.Eta();
      pmcs_em_elphig[ke]=e.Phi();
      if(pmcs_em_elphig[ke]<0.0) pmcs_em_elphig[ke] += 2*TMath::Pi();
    
      // need to keep track pT and particle ID
      // currently choose to use two unused variables pmcs_em_elpts, pmcs_em_elfid
      // which means these two variables can not be used for other purposes
    
      pmcs_em_elpts[ke] = trkpT;                // track pT before electron/photon merging
      pmcs_em_elfid[ke] = pmcs_ana_ppid[ie];    // use this as pid
    
      pmcs_em_elFSRxInCones[ke] = FSRxInCone;
      pmcs_em_elFSRnInCones[ke] = FSRnInCone;

      pmcs_em_nelg++;
    }
  }
  
  //Recreate the list of photons, excluding those that are collinear
  //to electrons. 
  int NPhotonAfterMerging = 0;
  
  for(int j=0;j<nphi;j++) {
    if(ph_indices[j] < 0) continue;    
    Int_t iph=ph_indices[j];
    
    TLorentzVector photon(pmcs_ana_ppx[iph],pmcs_ana_ppy[iph],
                          pmcs_ana_ppz[iph],pmcs_ana_pE[iph]);
    
    // require photon with pT at least 1 MeV 
    if(ph_indices[j]!=-1 && photon.Pt()>0.001){

      if (_globalparameters->merge_fsr_photons_model()==1 || _globalparameters->merge_fsr_photons_model()==2 || _globalparameters->merge_fsr_photons_model()==3 || _globalparameters->merge_fsr_photons_model()==4)
	{
	  // these photons will be included in the recoil system
	  // and I will apply the fraction of photons that can reach the calorimeter
	  // and the fraction of energy deposited in the calorimeter
	  double prob_photon = 1.;
	  if(_simulate_merge_fsr_photons_out_cone_prob)      // assume CC and EC photons have the same probability
	    prob_photon = wz_utils::photon_prob_out_cone(photon.Pt(), _merge_fsr_photons_out_cone_prob_p0, 
							 _merge_fsr_photons_out_cone_prob_p1, _merge_fsr_photons_out_cone_prob_p2, 
							 _merge_fsr_photons_out_cone_prob_p3, _merge_fsr_photons_out_cone_prob_p4);
	  
	  // remove the photons that are not supposed to reach the calorimeter permanently
	  double prob = _dummy->Uniform(0., 1.);
	  if(prob < prob_photon) {	  
	    // calculate the fraction of photon energy merged with the EM cluster
	    double fraction = 1.;
	    if(_simulate_merge_fsr_photons_out_cone_response) 
	      fraction = wz_utils::photon_response_out_cone(photon.Eta(), photon.Pt(), _merge_fsr_photons_out_cone_response_p0,
							    _merge_fsr_photons_out_cone_response_p1, _merge_fsr_photons_out_cone_response_p2,
							    _merge_fsr_photons_out_cone_response_p3, _merge_fsr_photons_out_cone_response_p4,
							    _merge_fsr_photons_out_cone_response_p5);
	    
	    if(FDBG) printf(" ==> MERGED energy fraction=%.3f ", fraction);
	    ph_indices[j]=-1; //mark as found, remove this partially merged photons, is this the best way ???
	    
	    if(fraction > 0.) { // due to the fitted function, fraction can be negative for very small energy photons
	      // only look at photons with fraction>0
	      photon = fraction * photon;  // change photon energy that will be included in the recoil system
	      
	      pmcs_em_phptg[NPhotonAfterMerging]  = photon.Pt();
	      pmcs_em_phetag[NPhotonAfterMerging] = photon.Eta();
	      pmcs_em_phphig[NPhotonAfterMerging] = photon.Phi(); 
	      if (pmcs_em_phphig[NPhotonAfterMerging]<0.0) pmcs_em_phphig[NPhotonAfterMerging]+=2*3.141592654;
	      pmcs_em_pheg[NPhotonAfterMerging]   = photon.E();
	      pmcs_em_phfid[NPhotonAfterMerging]  = 0; // this variable does not matter
	    }
	  NPhotonAfterMerging += 1;	
	  }
	}
      if (_globalparameters->merge_fsr_photons_model()== 6 || _globalparameters->merge_fsr_photons_model()== 7)
	{

	  // these photons will be included in the recoil system
	  // and I will apply the fraction of photons that can reach the calorimeter
	  // and the fraction of energy deposited in the calorimeter
	  double prob_photon = 1.;
          double deteta = PCalTools::eta_extrap_Local(vtx.vtxz(), photon.Eta());
          if(_simulate_merge_fsr_photons_out_cone_prob)    
            prob_photon = wz_utils::photon_prob_out_cone_test( photon.Pt(), deteta);
	  
	  // remove the photons that are not supposed to reach the calorimeter permanently
	  double prob = _dummy->Uniform(0., 1.);
	  if(prob < prob_photon) {	  
	    // calculate the fraction of photon energy merged with the EM cluster
	    double fraction = 1.;
            double dphi = 0.001;
	    if(_simulate_merge_fsr_photons_out_cone_response)
               {
                float dphi = wz_utils::calculate_dphi(photon.Pt(), deteta,_dummy);
                if(dphi < -0.5)
                  {
                    cout<<"Something is wrong in dphi calculator!!!"<<endl;
                  }
                fraction = wz_utils::photon_response_out_cone_test2(photon.Pt(), deteta, dphi);
                if( fabs(deteta) < 1.0 )
                  {
                    float usephi = photon.Phi();
                    if(usephi < 0) usephi += TMath::TwoPi();
                    float phi_mod2 = fabs( 0.5 - fmod(16.*usephi/TMath::Pi(), 1.0) );
                    fraction *= TMath::Erf( (0.5943-phi_mod2)/0.1406 );
                  }

               } 
	    
	    if(FDBG) printf(" ==> MERGED energy fraction=%.3f ", fraction);
	    ph_indices[j]=-1; //mark as found, remove this partially merged photons, is this the best way ???
	    
	    if(fraction > 0.) { // due to the fitted function, fraction can be negative for very small energy photons
	      // only look at photons with fraction>0
	      //photon = fraction * photon;  // change photon energy that will be included in the recoil system

              pmcs_em_phptg[NPhotonAfterMerging]  = fraction*photon.Pt();
              pmcs_em_phetag[NPhotonAfterMerging] = photon.Eta();
              pmcs_em_phphig[NPhotonAfterMerging] = photon.Phi() + dphi;
              while (pmcs_em_phphig[NPhotonAfterMerging] > 2*3.141592654) pmcs_em_phphig[NPhotonAfterMerging]-=2*3.141592654;
              while (pmcs_em_phphig[NPhotonAfterMerging]<0.0) pmcs_em_phphig[NPhotonAfterMerging]+=2*3.141592654;
              pmcs_em_pheg[NPhotonAfterMerging]   = fraction*photon.E();
              pmcs_em_phfid[NPhotonAfterMerging]  = 0; // this variable does not matter
	    }
	  NPhotonAfterMerging += 1;	
	  } // only a fraction of photon can reach the calorimeter
	}
      if(NPhotonAfterMerging>=120){
	printf("Warning: Too many photons (%d)!\n",nphi);
	break;
      }
    }//get rid of merged photons and photon with pT at least 1 MeV
  } // loop over all photons
  
  pmcs_em_nphg = NPhotonAfterMerging;
  
  return;
}


Float_t pmcsana::CalculateTruePhiStar(Bool_t* passesCuts) {

  Int_t nphi=0, neli=0;
  Int_t ph_indices[50];
  Int_t el_indices[50];
  Int_t nnu=0;
  Int_t nu_indices[50];
  for(int i=0; i<50; i++) {
    ph_indices[i]=-1;
    el_indices[i]=-1;
    nu_indices[i]=-1;
  }

  for(int ip = 0; ip < pmcs_ana_npart; ip++) {
    if(TMath::Abs(pmcs_ana_ppid[ip])==22){ //photon
      ph_indices[nphi]=ip;
      nphi++;
    } else if(TMath::Abs(pmcs_ana_ppid[ip])==11){ //electron
      el_indices[neli]=ip;
      neli++;
    } else if (TMath::Abs(pmcs_ana_ppid[ip])==12){ // neutrino
      nu_indices[nnu]=ip;
      nnu++;
    }
  }

  TLorentzVector Obj1, Obj2;
  Float_t DeltaEta=0;
  if (nnu==1 && neli==1) {
    Obj1.SetPxPyPzE(pmcs_ana_ppx[nu_indices[0]],pmcs_ana_ppy[nu_indices[0]],pmcs_ana_ppz[nu_indices[0]],pmcs_ana_pE[nu_indices[0]]);
    Obj2.SetPxPyPzE(pmcs_ana_ppx[el_indices[0]],pmcs_ana_ppy[el_indices[0]],pmcs_ana_ppz[el_indices[0]],pmcs_ana_pE[el_indices[0]]);
    for (Int_t i=0; i<nphi; i++) {
      TLorentzVector ph(pmcs_ana_ppx[ph_indices[i]],pmcs_ana_ppy[ph_indices[i]], pmcs_ana_ppz[ph_indices[i]],pmcs_ana_pE[ph_indices[i]]);
      if (Obj2.DeltaR(ph)<0.2) Obj2+=ph;
    }
    if (pmcs_ana_ppid[el_indices[0]]<0) DeltaEta=DeltaEta=Obj1.Eta()-Obj2.Eta();  // e+
    else DeltaEta=Obj2.Eta()-Obj1.Eta();
    //
    if (passesCuts) {
      (*passesCuts)=((Obj2.Pt()>20 && (fabs(Obj2.Eta())<1.1 || (fabs(Obj2.Eta())>1.5 && fabs(Obj2.Eta())<3))) &&
		     (Obj1.Pt()>20 && fabs(Obj1.Eta())<3));
    }
  } else if (nnu==0 && neli==2) {
    Obj1.SetPxPyPzE(pmcs_ana_ppx[el_indices[0]],pmcs_ana_ppy[el_indices[0]],pmcs_ana_ppz[el_indices[0]],pmcs_ana_pE[el_indices[0]]);
    Obj2.SetPxPyPzE(pmcs_ana_ppx[el_indices[1]],pmcs_ana_ppy[el_indices[1]],pmcs_ana_ppz[el_indices[1]],pmcs_ana_pE[el_indices[1]]);
    for (Int_t i=0; i<nphi; i++) {
      TLorentzVector ph(pmcs_ana_ppx[ph_indices[i]],pmcs_ana_ppy[ph_indices[i]], pmcs_ana_ppz[ph_indices[i]],pmcs_ana_pE[ph_indices[i]]);
      if (Obj1.DeltaR(ph)<0.2) Obj1+=ph;
      else if (Obj2.DeltaR(ph)<0.2) Obj2+=ph;
    }
    if (pmcs_ana_ppid[el_indices[0]]<0) DeltaEta=DeltaEta=Obj2.Eta()-Obj1.Eta();  // the leading electron is an e+
    else DeltaEta=Obj1.Eta()-Obj2.Eta();
    //
    if (passesCuts) {
      TLorentzVector Z=Obj1+Obj2;
      (*passesCuts)=((Obj1.Pt()>20 && (fabs(Obj1.Eta())<1.1 || (fabs(Obj1.Eta())>1.5 && fabs(Obj1.Eta())<3))) &&
		     (Obj2.Pt()>20 && (fabs(Obj2.Eta())<1.1 || (fabs(Obj2.Eta())>1.5 && fabs(Obj2.Eta())<3))) &&
		     (Z.M()>70 && Z.M()<110));
    }
  } else {
    cout<<"Do not know what to do"<<endl;
  }

  Float_t phiacop=TMath::Pi()-fabs(Obj1.DeltaPhi(Obj2));
  Float_t costheta=tanh(0.5*(DeltaEta));
  Float_t sintheta=sin(acos(costheta));
  Float_t phistar=tan(phiacop/2)*sintheta;
  //cout<<phiacop<<" "<<costheta<<" "<<sintheta<<"  "<<phistar<<endl;

  return phistar;

}


