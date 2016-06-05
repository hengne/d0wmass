#include "TString.h"
#include "TFile.h"
#include "TH2D.h"
#include "TMath.h"
#include "TVector2.h"

#include "HardRecoil_Manager.hpp"

#include <iostream>

HardRecoil_Manager::HardRecoil_Manager() {}

HardRecoil_Manager::HardRecoil_Manager(const char* parameter_filename) {

  PParameterReader parm(parameter_filename);
  std::cout << "HardRecoil_Manager Initialization" << std::endl;

  ptnbins = parm.GetInt("HardRecoil_pTbins");
  ptbins = parm.GetVDouble("HardRecoil_pTbins_edges");
  zbsetmodel = parm.GetBool("HardRecoil_zbsetmodel", kFALSE);
  run3bool = parm.GetBool("Run3");
  run4bool = parm.GetBool("Run4");

 if (run3bool == run4bool && zbsetmodel) {
    std::cout << "ERROR:  HardRecoil_Manager can only process Run3 or Run4 at a time.  Set only one of the Run3 and Run4 parameters at top of parameters file to true." << std::endl;
    exit(0);
  }

  if(zbsetmodel){
    ptnbinsset = parm.GetInt("HardRecoil_pTbinsSET");
    ptbinsset = parm.GetVDouble("HardRecoil_pTbinsSET_edges");
    luminbins = parm.GetInt("HardRecoil_lumibins");
    lumibins = parm.GetVDouble("HardRecoil_lumibins_edges");
    dphinbins = parm.GetInt("HardRecoil_dphibins");
    dphibins = parm.GetVDouble("HardRecoil_dphibins_edges");

    zphirespnbins = parm.GetInt("HardRecoil_zphirespbins");
    zphirespbins = parm.GetVDouble("HardRecoil_zphirespbins_edges");
    if(run3bool){
      zphirespA = parm.GetVDouble("HardRecoil_zphiresp_ParameterA");
      zphirespB = parm.GetVDouble("HardRecoil_zphiresp_ParameterB");
      zphirespC = parm.GetVDouble("HardRecoil_zphiresp_ParameterC");
      zphirespD = parm.GetVDouble("HardRecoil_zphiresp_ParameterD");
      zphirespMean = parm.GetVDouble("HardRecoil_zphiresp_Mean");
    }else{
      zphirespA = parm.GetVDouble("HardRecoil_zphiresp_ParameterA_run4");
      zphirespB = parm.GetVDouble("HardRecoil_zphiresp_ParameterB_run4");
      zphirespC = parm.GetVDouble("HardRecoil_zphiresp_ParameterC_run4");
      zphirespD = parm.GetVDouble("HardRecoil_zphiresp_ParameterD_run4");
      zphirespMean = parm.GetVDouble("HardRecoil_zphiresp_Mean_run4");
    }
  }else{
    ptnbinsset = ptnbins;
    ptbinsset = ptbins;
  }

  flipped = false;

  if(parm.GetInt("EtFlowFudge")==8){//so don't grab file for old versions of etflow, like option 3
    TString etflow_fname(parm.GetChar("EtFlowFile"));
    TFile* etflow_binned_file = new TFile(etflow_fname);
    etflow_binned3 = (TH1D*) etflow_binned_file->Get("etflow_run2b3");
    etflow_binned4 = (TH1D*) etflow_binned_file->Get("etflow_run2b4");
    etflow_binned3->SetDirectory(0);
    etflow_binned4->SetDirectory(0);
    etflow_binned_file->Close();
  }


  // hard recoil library file
  if (getenv("HRLibraryRootPath") == NULL ) {
    std::cout << "ERROR:  HRLibraryRootPath is not defined" << std::endl;
    exit(0);
  }
 
  TString hrLibraryRootPath(getenv("HRLibraryRootPath"));
  TString model_filename = "";
  if(run3bool) model_filename = hrLibraryRootPath + '/' + parm.GetChar("HardRecoil_FileName"); 
  else{
    if (zbsetmodel) model_filename = hrLibraryRootPath + '/' + parm.GetChar("HardRecoil_FileName_run4"); 
    else model_filename = hrLibraryRootPath + '/' + parm.GetChar("HardRecoil_FileName"); //backwards compatibility
  }
  std::cout << model_filename << " will be used for hard recoil model" << std::endl;
  TFile* tf = new TFile(model_filename);
    
  for (Int_t j=0; j<ptnbins; j++) {
    
    if(! zbsetmodel){
      TH2D* HRHist = (TH2D*) tf->Get(TString::Format("recoil_resp_hist_bin_%d", j));
      resp_pdf.push_back(new TH2rclsa(*HRHist));
      HRHist->Delete();
      resp_pdf[j]->SetDirectory(0);
      resp_pdf[j]->ComputeYIntegral();
      resp_pdf[j]->ComputeIntegral();  
     
    }else{ //we will assign histograms below to be resp_pdf and resp_zbset_pdf later in the code
      //dphi model is in true phi bins, other two in true zpt bins (and others)
     
      if(luminbins !=7 || dphinbins !=6) {
	std::cout<<"settings for number of lumi or dphi bins is not correct.  HardRecoil_Manager code must be altered for other binning."<<std::endl;
	exit(0);
      }

      TH2D* HRHist0 = (TH2D*) tf->Get(TString::Format("recoil_resp_hist_truephi0_bin_%d", j)); //0th
      resp_pdf0.push_back(new TH2rclsa(*HRHist0));
      HRHist0->Delete();
      resp_pdf0[j]->SetDirectory(0);
      
      TH2D* HRHist1 = (TH2D*) tf->Get(TString::Format("recoil_resp_hist_truephi1_bin_%d", j));
      resp_pdf1.push_back(new TH2rclsa(*HRHist1));
      HRHist1->Delete();
      resp_pdf1[j]->SetDirectory(0);
      
      TH2D* HRHist2 = (TH2D*) tf->Get(TString::Format("recoil_resp_hist_truephi2_bin_%d", j));
      resp_pdf2.push_back(new TH2rclsa(*HRHist2));
      HRHist2->Delete();
      resp_pdf2[j]->SetDirectory(0);
       
      TH2D* HRHist3 = (TH2D*) tf->Get(TString::Format("recoil_resp_hist_truephi3_bin_%d", j));
      resp_pdf3.push_back(new TH2rclsa(*HRHist3));
      HRHist3->Delete();
      resp_pdf3[j]->SetDirectory(0);
 
      TH2D* HRHist4 = (TH2D*) tf->Get(TString::Format("recoil_resp_hist_truephi4_bin_%d", j));
      resp_pdf4.push_back(new TH2rclsa(*HRHist4));
      HRHist4->Delete();
      resp_pdf4[j]->SetDirectory(0);
        
      TH2D* HRHist5 = (TH2D*) tf->Get(TString::Format("recoil_resp_hist_truephi5_bin_%d", j));
      resp_pdf5.push_back(new TH2rclsa(*HRHist5));
      HRHist5->Delete();
      resp_pdf5[j]->SetDirectory(0);
        
      TH2D* HRZBHist0 = (TH2D*) tf->Get(TString::Format("recoil_resp_zbset_hist_lumibin0_bin_%d", j));
      resp_zbset_pdf0.push_back(new TH2rclsa(*HRZBHist0));
      HRZBHist0->Delete();
      resp_zbset_pdf0[j]->SetDirectory(0);
            
      TH2D* HRZBHist1 = (TH2D*) tf->Get(TString::Format("recoil_resp_zbset_hist_lumibin1_bin_%d", j));
      resp_zbset_pdf1.push_back(new TH2rclsa(*HRZBHist1));
      HRZBHist1->Delete();
      resp_zbset_pdf1[j]->SetDirectory(0);
     
      TH2D* HRZBHist2 = (TH2D*) tf->Get(TString::Format("recoil_resp_zbset_hist_lumibin2_bin_%d", j));
      resp_zbset_pdf2.push_back(new TH2rclsa(*HRZBHist2));
      HRZBHist2->Delete();
      resp_zbset_pdf2[j]->SetDirectory(0);
        
      TH2D* HRZBHist3 = (TH2D*) tf->Get(TString::Format("recoil_resp_zbset_hist_lumibin3_bin_%d", j));
      resp_zbset_pdf3.push_back(new TH2rclsa(*HRZBHist3));
      HRZBHist3->Delete();
      resp_zbset_pdf3[j]->SetDirectory(0);
      
      TH2D* HRZBHist4 = (TH2D*) tf->Get(TString::Format("recoil_resp_zbset_hist_lumibin4_bin_%d", j));
      resp_zbset_pdf4.push_back(new TH2rclsa(*HRZBHist4));
      HRZBHist4->Delete();
      resp_zbset_pdf4[j]->SetDirectory(0);
      
      TH2D* HRZBHist5 = (TH2D*) tf->Get(TString::Format("recoil_resp_zbset_hist_lumibin5_bin_%d", j));
      resp_zbset_pdf5.push_back(new TH2rclsa(*HRZBHist5));
      HRZBHist5->Delete();
      resp_zbset_pdf5[j]->SetDirectory(0);

      TH2D* HRZBHist6 = (TH2D*) tf->Get(TString::Format("recoil_resp_zbset_hist_lumibin6_bin_%d", j));
      resp_zbset_pdf6.push_back(new TH2rclsa(*HRZBHist6));
      HRZBHist6->Delete();
      resp_zbset_pdf6[j]->SetDirectory(0);
    }//IF ZBSET MODEL
  }//PTBINS
  
  for (Int_t j=0; j<ptnbinsset; j++) {
    TH2D* SETHist = (TH2D*) tf->Get(TString::Format("set_ut_hist_bin_%d", j));
    set_ut_pdf.push_back(new TH2rclsa(*SETHist));
    SETHist->Delete();
    set_ut_pdf[j]->SetDirectory(0);
  }//PTBINS FOR SET
  
  if(!zbsetmodel){
    TH2D* PhiHist = (TH2D*) tf->Get("phi_hist");     
    phi_pdf = new TH2rclsa(*PhiHist);
    phi_pdf->SetDirectory(0);
    phi_pdf->ComputeYMaximum();
  }
  
  
  tf->Close();
  
  std::cout << "HardRecoil_Manager initialization: DONE" << std::endl;
  
}    

HardRecoil_Manager::~HardRecoil_Manager() {
  
  if (phi_pdf) delete phi_pdf;

  for (int i=0; i<set_ut_pdf.size(); i++) 
    if (set_ut_pdf[i]) delete set_ut_pdf[i];
  
  for (int i=0; i<resp_zbset_pdf.size(); i++) 
    if (resp_zbset_pdf[i]) delete resp_zbset_pdf[i];    
 for (int i=0; i<resp_zbset_pdf0.size(); i++) 
   if (resp_zbset_pdf0[i]) delete resp_zbset_pdf0[i];    
  for (int i=0; i<resp_zbset_pdf1.size(); i++) 
    if (resp_zbset_pdf1[i]) delete resp_zbset_pdf1[i];  
  for (int i=0; i<resp_zbset_pdf2.size(); i++) 
    if (resp_zbset_pdf2[i]) delete resp_zbset_pdf2[i];  
  for (int i=0; i<resp_zbset_pdf3.size(); i++) 
    if (resp_zbset_pdf3[i]) delete resp_zbset_pdf3[i];
  for (int i=0; i<resp_zbset_pdf4.size(); i++) 
    if (resp_zbset_pdf4[i]) delete resp_zbset_pdf4[i];  
  for (int i=0; i<resp_zbset_pdf5.size(); i++) 
    if (resp_zbset_pdf5[i]) delete resp_zbset_pdf5[i];  
  for (int i=0; i<resp_zbset_pdf6.size(); i++) 
    if (resp_zbset_pdf6[i]) delete resp_zbset_pdf6[i];  
  
  for (int i=0; i<resp_pdf.size(); i++) 
    if (resp_pdf[i]) delete resp_pdf[i];  
  for (int i=0; i<resp_pdf0.size(); i++) 
    if (resp_pdf0[i]) delete resp_pdf0[i];  
  for (int i=0; i<resp_pdf1.size(); i++) 
    if (resp_pdf1[i]) delete resp_pdf1[i];  
  for (int i=0; i<resp_pdf2.size(); i++) 
    if (resp_pdf2[i]) delete resp_pdf2[i];  
  for (int i=0; i<resp_pdf3.size(); i++) 
    if (resp_pdf3[i]) delete resp_pdf3[i];  
  for (int i=0; i<resp_pdf4.size(); i++) 
    if (resp_pdf4[i]) delete resp_pdf4[i];  
  for (int i=0; i<resp_pdf5.size(); i++) 
    if (resp_pdf5[i]) delete resp_pdf5[i];
  
}

  
void HardRecoil_Manager::FlipRecoil(double truepT, double truePhi, double ZBset, double lumi, TRandom* dummy/*=0*/) {

    if (!dummy) dummy = gRandom;
  
   int ptbin = -1;
   for (int i=0; i<ptnbins; i++) {
     if (truepT > ptbins[i])
       ptbin++;
     else
       break;
   }
   if (ptbin > ptnbins-1) ptbin = ptnbins-1;
   if (ptbin < 0) ptbin = 0;

 int ptbinset = -1;
   for (int i=0; i<ptnbinsset; i++) {
     if (truepT > ptbinsset[i])
       ptbinset++;
     else
       break;
   }
   if (ptbinset > ptnbinsset-1) ptbinset = ptnbinsset-1;
   if (ptbinset < 0) ptbinset = 0;


   if(zbsetmodel){  
     //catch correct number of bins for the below in initialization earlier
      if(lumi >= lumibins[0] && lumi < lumibins[1]) resp_zbset_pdf = resp_zbset_pdf0; 
      else if(lumi >= lumibins[1] && lumi < lumibins[2]) resp_zbset_pdf = resp_zbset_pdf1; 
      else if(lumi >= lumibins[2] && lumi < lumibins[3]) resp_zbset_pdf = resp_zbset_pdf2; 
      else if(lumi >= lumibins[3] && lumi < lumibins[4]) resp_zbset_pdf = resp_zbset_pdf3; 
      else if(lumi >= lumibins[4] && lumi < lumibins[5]) resp_zbset_pdf = resp_zbset_pdf4; 
      else if(lumi >= lumibins[5] && lumi < lumibins[6]) resp_zbset_pdf = resp_zbset_pdf5; 
      else if(lumi >= lumibins[6] && lumi < lumibins[7]) resp_zbset_pdf = resp_zbset_pdf6; 
      else {  std::cout<< "Hard recoil Manager has luminosity problem with lumi "<<lumi<<std::endl;  exit(0);}
  
      if(TVector2::Phi_0_2pi(truePhi) >= dphibins[0] && TVector2::Phi_0_2pi(truePhi) < dphibins[1]) resp_pdf = resp_pdf0; 
      else if(TVector2::Phi_0_2pi(truePhi) >= dphibins[1] && TVector2::Phi_0_2pi(truePhi) < dphibins[2]) resp_pdf = resp_pdf1; 
      else if(TVector2::Phi_0_2pi(truePhi) >= dphibins[2] && TVector2::Phi_0_2pi(truePhi) < dphibins[3]) resp_pdf = resp_pdf2; 
      else if(TVector2::Phi_0_2pi(truePhi) >= dphibins[3] && TVector2::Phi_0_2pi(truePhi) < dphibins[4]) resp_pdf = resp_pdf3; 
      else if(TVector2::Phi_0_2pi(truePhi) >= dphibins[4] && TVector2::Phi_0_2pi(truePhi) < dphibins[5]) resp_pdf = resp_pdf4; 
      else if(TVector2::Phi_0_2pi(truePhi) >= dphibins[5] && TVector2::Phi_0_2pi(truePhi) < dphibins[6]) resp_pdf = resp_pdf5; 
      else { std::cout<< "Hard recoil Manager has phi problem with true phi "<<TVector2::Phi_0_2pi(truePhi)<<std::endl;  exit(0);}   
   }

   bool good = false;
   int attempts = 0;
   while (!good && attempts < 100 ) {
  
     if(! zbsetmodel){
       resp_pdf[ptbin]->GetRandom2(response, deltaPhi, dummy); //adjusted resp, but need to adjust deltaphi since prob changed in new resp bin?
       expected = resp_pdf[ptbin]->getMeanInX(deltaPhi);
     }
     else{
       response = resp_zbset_pdf[ptbin]->getRandomInX( TMath::Sqrt(ZBset), dummy);

       //correct for unphysical values due to imperfections in modelling histogram (rare)
       if(attempts > 80) response = resp_zbset_pdf[ptbin]->getRandomInX( 12, dummy); //some high but more likely not to be 0 value.  This is an approximation for a small number of cases.
   
       //correct for the (small) zphi dependence of the response
       //some default values
       double  mean = 1.0;
       double  resp1 = 0.0;  
       double dev = 0.0;
       for (int i=0; i<zphirespnbins; i++) {
	 if(truepT >= zphirespbins[i] && truepT < zphirespbins[i+1] ){
	   mean = zphirespMean[i];
	   resp1 = zphirespA[i] + zphirespB[i]*truePhi + zphirespC[i]*truePhi*truePhi + zphirespD[i]*truePhi*truePhi*truePhi; 
	   break;
	 }
       }      
       dev = (resp1 - mean) / mean;
       response = response + response*dev;
   
       deltaPhi = resp_pdf[ptbin]->getRandomInY(response, dummy); 
       expected = resp_zbset_pdf[ptbin]->getMeanInX(TMath::Sqrt(ZBset));
     }
    
     if(! zbsetmodel){
       if(dummy->Rndm()>0.5) deltaPhi *= -1;
       double maxval = phi_pdf->getMaximumInX(truepT*response);
       double rndm = maxval*dummy->Rndm();
       double val = phi_pdf->GetBinContent(phi_pdf->FindBin(TVector2::Phi_0_2pi(truePhi + deltaPhi*TMath::Pi())/TMath::TwoPi(), truepT*response));
       good = rndm < val;

     }else{
       // double expected2 = resp_zbset_pdf[ptbin]->getMeanInX(TMath::Sqrt(ZBset));
      double expected2 = resp_pdf[ptbin]->getMeanInX(deltaPhi); 
      good = true;
      //get unphysical spike of 0 response values in this high ZBset region without this sort of catch.
      //if redraw doesn't work after 80 tries, we get a value from the high side of zbset (12) that should have reasonable values.  Note once we do this, good is true.
      if( attempts < 81 && TMath::Sqrt(ZBset) > 15 && response < 0.1 && fabs((expected - expected2)/expected2) > 0.2 ) good = false;
     }
     
     attempts++;
   }
   if (!good) {
     //note this section should only be called for !zbsetmodel because of assignment of good
     resp_pdf[ptbin]->GetRandom2(response, deltaPhi, dummy);
     expected = resp_pdf[ptbin]->getMeanInX(deltaPhi);
     if(dummy->Rndm()>0.5) deltaPhi *= -1;
     std::cout<<"Hard Recoil Manager:: Not enough attempts"<<std::endl;
   }
   
   deltaPhi *= TMath::Pi();

   set = set_ut_pdf[ptbinset]->getRandomInX(truepT*response, dummy) + truepT*response;
   set_expected = set_ut_pdf[ptbinset]->getMeanInX(truepT*response) + truepT*response;
   
   znunu_recoil.SetRecoil(response*truepT*TMath::Cos(truePhi + deltaPhi), response*truepT*TMath::Sin(truePhi + deltaPhi));
   smeared_recoil.SetRecoil(response*truepT*TMath::Cos(truePhi + deltaPhi), response*truepT*TMath::Sin(truePhi + deltaPhi));

   flipped = true;
}


 
void HardRecoil_Manager::SmearRecoil(double truepT, double truePhi, double ZBset, double lumi,
				     double Relscale_HAD_bifurcate_A, 
				     double Relscale_HAD_bifurcate_B,
				     double Relscale_HAD_bifurcate_Tau,
				     double Relsampling_HAD_bifurcate_A, 
				     double Relsampling_HAD_bifurcate_B,
				     double Reltrans_HAD_RelRespTrans, 
				     double Reltrans_HAD_RelResnTrans, 
				     double Reltrans_HAD_RelTauTrans,
				     double Relphi_HAD_bifurcate_A, 
				     double Relphi_HAD_bifurcate_B,
				     int EtFlowCorrection,
				     bool use_external_information,
				     double external_resolution,
				     double external_deltaphi) { 

  double _response;
  double _deltaPhi;
  double _expected;
  if (use_external_information) {
    _deltaPhi = external_deltaphi;
    _response = 1-external_resolution;
    int ptbin = -1;
    for (int i=0; i<ptnbins; i++) {
      if (truepT > ptbins[i])
	ptbin++;
      else
	break;
    }
    if (ptbin > ptnbins-1) ptbin = ptnbins-1;
    if (ptbin < 0) ptbin = 0;
     if(!zbsetmodel) _expected = resp_pdf[ptbin]->getMeanInX(_deltaPhi/TMath::Pi());    
     else _expected = resp_zbset_pdf[ptbin]->getMeanInX(TMath::Sqrt(ZBset));
  } else {
    _deltaPhi = deltaPhi;
    _expected = expected;
    _response = response;
  }

  double delta_phi = _deltaPhi * (Relphi_HAD_bifurcate_A + Relphi_HAD_bifurcate_B/TMath::Sqrt(truepT));

  double RelResp = applyEtFlow(EtFlowCorrection, truepT, lumi, truePhi + delta_phi);

  if(EtFlowCorrection == 800){
    double phir =  TVector2::Phi_0_2pi(truePhi + _deltaPhi*TMath::Pi());
    if(run3bool){
      Relscale_HAD_bifurcate_A += 0.0315407*TMath::Sin(phir - 0.724795);
    }else{
      Relscale_HAD_bifurcate_A += 0.0215646*TMath::Sin(phir + 1.07503); 
    }
  }

  double RelResn = 1.;

  double smpTErwartungswert=truepT*_expected*RelResp;
  double smpTZittern=truepT*(_response-_expected)*RelResn;

  double spx_true = smpTErwartungswert * cos(delta_phi);
  double spy_true = smpTErwartungswert * sin(delta_phi);
  double smpTZittern_x_true=smpTZittern * cos(delta_phi);
  double smpTZittern_y_true=smpTZittern * sin(delta_phi);

  RelResp *= (Relscale_HAD_bifurcate_A + Relscale_HAD_bifurcate_B*TMath::Exp(-truepT/Relscale_HAD_bifurcate_Tau));
 

  spx_true = RelResp*spx_true;
  if (Reltrans_HAD_RelRespTrans > 0) spy_true = Reltrans_HAD_RelRespTrans*spy_true;
  else if (Reltrans_HAD_RelRespTrans < -10) spy_true = (1-(Reltrans_HAD_RelRespTrans+10)*exp(-truepT/(Reltrans_HAD_RelTauTrans*Relscale_HAD_bifurcate_Tau)))*spy_true;
  else spy_true = (1+Reltrans_HAD_RelRespTrans*exp(-truepT/(Reltrans_HAD_RelTauTrans*Relscale_HAD_bifurcate_Tau)))*spy_true;
  RelResn=Relsampling_HAD_bifurcate_A + Relsampling_HAD_bifurcate_B/TMath::Sqrt(truepT);
  
  spx_true+=RelResn*smpTZittern_x_true;
  spy_true+=Reltrans_HAD_RelResnTrans*smpTZittern_y_true;

  double smpT = TMath::Sqrt(spx_true*spx_true + spy_true*spy_true);

  smeared_recoil.SetRecoil(smpT*TMath::Cos(truePhi + delta_phi), smpT*TMath::Sin(truePhi + delta_phi));
}

double HardRecoil_Manager::applyEtFlow(int option, double truepT, double lumi, double sm_phi, double ResResp) {

  double retval = ResResp;

  if (option) {
    if (option==400) {
      if ((truepT>12)&&(lumi<2)&&(sm_phi>3.140)&&(sm_phi<5.495)) {
	retval*=1.07;
      }
    } else if (option==1) {
      // This is from the data/MC ratio in Z -> e e
      Double_t theFudge[6] = {
	2.23337e+00,
	1.02567e+00,
	2.37743e+00,
	-1.29922e+00,
	1.58845e+02,
	-5.70017e-03};   
      retval*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT);
    } else if (option==2) {
      // This is from the data/Znunu(IIa) ratio
      Double_t theFudge[6] = {
	-1.27258e+00,
	8.22150e-01,
	2.34385e+00,
	2.36753e+00,
	2.20601e+02,
	8.43940e-03};
      retval*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT);
    } else if (option==3) {
      // This is the Zee(FullMC)/Znunu ratio for RunIIb3
      Double_t theFudge[4] = {-1.80377e-01, 2.13833e-01, 1.69053e+00, 1.00781e+00};
      retval*=((theFudge[0]+theFudge[1]*truepT)*TMath::Exp(-truepT/theFudge[2])+theFudge[3]);
    } else if (option==7) {
      // This is from the Zee(FullMC)/Znunu(IIb) ratio
      Double_t theFudge[6] = {
	1.24318e+00,
	4.91889e+00,
	5.20096e+00,
	5.08244e+01,
	1.37849e+00,
	-2.84578e-03};
      retval*=(theFudge[0]+theFudge[1]*exp(-truepT/theFudge[2])+theFudge[3]*exp(-truepT/theFudge[4])+theFudge[5]*truepT);
    } else if (option==8) {
      if (run3bool)
	retval*=etflow_binned3->Interpolate(truepT);
      else if (run4bool)
	retval*=etflow_binned4->Interpolate(truepT);
    } else if (option==9) { //Newest for Run 3 and 4 MC, histograms.
      double theFudge[4];
      if (run3bool) {
	theFudge[0] = 1.37095e-01; theFudge[1] = 0.; theFudge[2] = 4.22069e-01; theFudge[3] = 9.99516e-01;
      } else if (run4bool) {
	theFudge[0] = 1.07501e-01; theFudge[1] = 0.; theFudge[2] = 3.45783e-01; theFudge[3] = 9.98684e-01;
      }
      retval*=((theFudge[0]+(theFudge[0]*theFudge[2]-theFudge[1])*truepT)*TMath::Exp(-theFudge[2]*truepT)+theFudge[3]);  
    }  else if (option==101) { //Newest for Run 3 and 4 data, same function for both runs
      double theFudge[5];
      theFudge[0] = 3.02081e-01; theFudge[1] = 2.39741e-01; theFudge[2] = 4.41602e-01; theFudge[3] = 1.97779e-01; theFudge[4] = 9.82999e-01;
      
      retval*=((theFudge[0]+theFudge[1])*(1+theFudge[2]*truepT)*TMath::Exp(-theFudge[2]*truepT) - (theFudge[1])*(1+theFudge[3]*truepT)*TMath::Exp(-theFudge[3]*truepT) + theFudge[4]);
    } else if(option == 800){
      //in this case, application takes part in main code, SmearRecoil().  
      //Want to prevent unintentional double use of this option number.
    }
  }
  return retval;

}
