#include <TVector2.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile2D.h>
#include <TFile.h>

#include <RooNDKeysPdf.h>
#include <RooKeysPdf.h>
#include <RooAddPdf.h>
#include <RooVoigtian.h>
#include <RooChebychev.h>
#include <RooPolynomial.h>
#include <RooCBShape.h>
#include <RooWorkspace.h>
#include <RooPlot.h>
#include <RooRealVar.h>
#include <RooArgSet.h>
#include <RooDataSet.h>
#include <RooDataHist.h>
#include <RooGaussian.h>
#include <RooFormulaVar.h>
#include <RooProdPdf.h>
#include <RooConstVar.h>
#include <RooGlobalFunc.h>
#include <RooLandau.h>
#include <RooFFTConvPdf.h>
#include <RooUniformBinning.h>
#include <fstream>
#include <iostream>
#include <vector>

#define debug 0
#define uselandau


using namespace std;
using namespace RooFit;

RooDataSet** importRecoilRespData(ifstream& file, RooRealVar& resp, RooRealVar& ZBset, RooRealVar& dphi_norm, RooRealVar& lumi, RooRealVar& zphi, int ptnbins, double* ptbins) {

  int runno, evtno;
  double z_px, z_py, z_pz, z_E;
  double gen_rec_px, gen_rec_py, gen_rec_pz, gen_rec_E;
  double rec_px, rec_py, set;
  double lumiz, zbset;

  RooDataSet** retval;
  retval= new RooDataSet*[ptnbins];
  for (int i=0; i<ptnbins; i++) {
    retval[i] = new RooDataSet(TString::Format("RecoilData_bin_%d", i), TString::Format("RecoilData_bin_%d", i), RooArgSet(resp, ZBset, dphi_norm, lumi, zphi));
  }

  while (!file.eof()) {
    file >> runno >> evtno >> z_px >> z_py >> z_pz >> z_E >> gen_rec_px >> gen_rec_py >> gen_rec_pz >> gen_rec_E >> rec_px >> rec_py >> set >> lumiz >> zbset;

    if (debug) {
      cout << runno << " " << evtno << " " << z_px << " " << z_py << " " << z_pz << " " << z_E
	   << " " << gen_rec_px << " " << gen_rec_py << " " << gen_rec_pz << " " << gen_rec_E
	   << " " << rec_px << " " << rec_py << " " << set << " " << lumiz << " " << zbset << endl;
    }

    TVector2 z_vec(z_px, z_py);
    TVector2 rec_vec(rec_px, rec_py);
    TVector2 utrue_vec(gen_rec_px, gen_rec_py);

    int ptbin = -1;
    for (int i=0; i<ptnbins; i++) {
      if (z_vec.Mod() > ptbins[i])
	ptbin++;
      else
	break;
    }
    if (ptbin > ptnbins-1 || ptbin < 0) continue;
      
    // Sets the variables

    ZBset.setVal(TMath::Sqrt(zbset));
    resp.setVal(rec_vec.Mod()/z_vec.Mod());
    dphi_norm.setVal(rec_vec.DeltaPhi(utrue_vec)/TMath::Pi()); 
    lumi.setVal(lumiz);
    zphi.setVal(TVector2::Phi_0_2pi(utrue_vec.Phi())); //to be consistent with PMCS, which also runs 0 to 2phi for true phi

    // adds the entry
    retval[ptbin]->add(RooArgSet(resp, ZBset, dphi_norm, lumi, zphi));

  }
  return retval;
}   


RooDataSet** importSETData(ifstream& file, RooRealVar& set_ut, RooRealVar& ut, int ptnbins, double* ptbins) {
  
  int runno, evtno;
  double z_px, z_py, z_pz, z_E;
  double gen_rec_px, gen_rec_py, gen_rec_pz, gen_rec_E;
  double rec_px, rec_py, set;
  double lumi, zbset;

  RooDataSet** retval  = new RooDataSet*[ptnbins];
  for (int i=0; i<ptnbins; i++) {
    retval[i] = new RooDataSet(TString::Format("SETData_bin_%d", i), TString::Format("SETData_bin_%d", i), RooArgSet(set_ut, ut));
  }

  while (!file.eof()) {
    file >> runno >> evtno >> z_px >> z_py >> z_pz >> z_E >> gen_rec_px >> gen_rec_py >> gen_rec_pz >> gen_rec_E >> rec_px >> rec_py >> set >> lumi >> zbset;
    
    TVector2 z_vec(z_px, z_py);
    TVector2 rec_vec(rec_px, rec_py);
    
    int ptbin = -1;
    for (int i=0; i<ptnbins; i++) {
      if (z_vec.Mod() > ptbins[i])
	ptbin++;
      else
	break;
    }

    if (ptbin < 0 || ptbin > ptnbins-1) continue;

    set_ut.setVal(set - rec_vec.Mod());
    ut.setVal(rec_vec.Mod());
    retval[ptbin]->add(RooArgSet(set_ut, ut));
  }
  return retval;
}   

int recoil_analysis(TString inputz, TString rootoutput, char* psoutput, int binz) {

  ifstream inputResp(inputz);
  ifstream inputSET(inputz);
  TFile* ROOTout = new TFile(rootoutput, "update");

  int theBin = -1;
  theBin = binz;


 int ptnbins = 46;
 double ptbins[] = {0.0, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.5, 5.0, 5.5, 6.0, 7.0, 8.0, 9.0, 
		   10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 
		    30.0, 33.0, 36.0, 39.0, 42.0, 45.0, 49.0, 55.0, 70.0, 100.0, 500.0};


  // Defines the variables  
  RooRealVar resp("resp", "u_{T}/q_{T}", 0., 30.);
  RooRealVar ZBset("ZBset", "ZB SET", 0., 40.);//was 20
  RooRealVar dphi_norm("dphi_norm", "#Delta#phi / #pi", -1., 1.);
  RooRealVar lumi("lumi", "lumi", 0., 20.);
  RooRealVar zphi("zphi", "Z #phi", 0., 2*TMath::Pi());
  RooRealVar set_ut("set_ut", "SET - u_{T}", 0., 100.);
  RooRealVar ut("ut", "u_{T}", 0., 200.); //was 200
 
  double resp_bdr[] = {20., 15., 15., 10.,10.,10., 5., 5.,5., 5.,5.,5.,3., 3., 3., 3., 3., 3., 3., 3., 3., 3., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 2., 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5};
  double dphi_bdr[] = { 1.,  1.,  1., 1., 1., 1., 1., 1., 1., 1.,  1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., .5, .5, .5, .5, .5, .5, .5, .5, .3, .3, .3, .3,.3,.3,.3,.3, .2, .2, .2, .2, .2, .2, .1, .1};


 int ptnbinszphi = 16;
 double ptbinszphi[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 15.0, 20.0, 30., 500.0};


 int ptnbinsset = 15;
 double ptbinsset[] = {0.0, 1.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 15.0, 20.0, 25.0, 30., 40.0, 50.0, 70.0, 500.0};
 double set_ut_bdr[]= {20., 30., 40., 40., 50., 50., 60., 60., 60., 60., 70.,70.,70., 70., 90.};
 double ut_bdr[]=    {10., 10., 15., 15.,15., 20., 20., 25., 30., 40.,40., 60.,60.,90., 200.}; //250

  // Import the recoil (response x delta phi) from dump file 
  RooDataSet** RecoilRespData;
  RooDataSet** SETData;

  cout<<"importing data response"<<endl;
  if (theBin == -1 || theBin == -3) RecoilRespData = importRecoilRespData(inputResp, resp, ZBset, dphi_norm, lumi, zphi, ptnbins, ptbins);

  if (theBin == -2) SETData = importSETData(inputSET, set_ut, ut, ptnbinsset, ptbinsset);
  if (theBin == -4) RecoilRespData = importRecoilRespData(inputResp, resp, ZBset, dphi_norm, lumi, zphi, ptnbinszphi, ptbinszphi);
  
  inputResp.close();
  inputSET.close();
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(1,0);
  TCanvas* c1 = new TCanvas("c1","c1");
  c1->Print(TString::Format("%s[", psoutput));



   for (int i=0; i<ptnbins; i++) {
     //this is dphi and response in bins of true phi
    if (i!=theBin && theBin != -1) continue;

    if (RecoilRespData[i]->numEntries() < 5) continue;
     cout<<"RESP bin "<<i<<endl;

    RecoilRespData[i]->printMultiline(cout, 1);
    TH2D* genHist0(0);
    TH2D* genHist1(0);
    TH2D* genHist2(0);
    TH2D* genHist3(0);
    TH2D* genHist4(0);
    TH2D* genHist5(0);

    //slightly different binning than 0-1, etc on 0 to 2pi scale to be more even on the sides (2 larger bins, rather than one)
    RooDataSet* RecoilRespData_phi0 = (RooDataSet*) RecoilRespData[i]->reduce("zphi>=0.&&zphi<1.");
    RooDataSet* RecoilRespData_phi1 = (RooDataSet*) RecoilRespData[i]->reduce("zphi>=1.&&zphi<2.");
    RooDataSet* RecoilRespData_phi2 = (RooDataSet*) RecoilRespData[i]->reduce("zphi>=2.&&zphi<3.");
    RooDataSet* RecoilRespData_phi3 = (RooDataSet*) RecoilRespData[i]->reduce("zphi>=3.&&zphi<4.");
    RooDataSet* RecoilRespData_phi4 = (RooDataSet*) RecoilRespData[i]->reduce("zphi>=4.&&zphi<5.");
    RooDataSet* RecoilRespData_phi5 = (RooDataSet*) RecoilRespData[i]->reduce("zphi>=5.");

    RecoilRespData_phi0->printMultiline(cout, 1);
    RecoilRespData_phi1->printMultiline(cout, 1);
    RecoilRespData_phi2->printMultiline(cout, 1);
    RecoilRespData_phi3->printMultiline(cout, 1);
    RecoilRespData_phi4->printMultiline(cout, 1);
    RecoilRespData_phi5->printMultiline(cout, 1);


    cout<<"RESP bin start HIST "<<i<<endl;
    genHist0 = (TH2D*) RecoilRespData_phi0->createHistogram(TString::Format("recoil_resp_hist_truephi0_bin_%d", i).Data(), 
							 resp, Binning(250, 0., resp_bdr[i]),
							 YVar(dphi_norm, Binning(128, -1*dphi_bdr[i], dphi_bdr[i])));
    genHist1 = (TH2D*) RecoilRespData_phi1->createHistogram(TString::Format("recoil_resp_hist_truephi1_bin_%d", i).Data(), 
							 resp, Binning(250, 0., resp_bdr[i]),
							 YVar(dphi_norm, Binning(128, -1*dphi_bdr[i], dphi_bdr[i])));
    genHist2 = (TH2D*) RecoilRespData_phi2->createHistogram(TString::Format("recoil_resp_hist_truephi2_bin_%d", i).Data(), 
							 resp, Binning(250, 0., resp_bdr[i]),
							 YVar(dphi_norm, Binning(128, -1*dphi_bdr[i], dphi_bdr[i])));
    genHist3 = (TH2D*) RecoilRespData_phi3->createHistogram(TString::Format("recoil_resp_hist_truephi3_bin_%d", i).Data(), 
							 resp, Binning(250, 0., resp_bdr[i]),
							 YVar(dphi_norm, Binning(128, -1*dphi_bdr[i], dphi_bdr[i])));
    genHist4 = (TH2D*) RecoilRespData_phi4->createHistogram(TString::Format("recoil_resp_hist_truephi4_bin_%d", i).Data(), 
							 resp, Binning(250, 0., resp_bdr[i]),
							 YVar(dphi_norm, Binning(128, -1*dphi_bdr[i], dphi_bdr[i])));
    genHist5 = (TH2D*) RecoilRespData_phi5->createHistogram(TString::Format("recoil_resp_hist_truephi5_bin_%d", i).Data(), 
							 resp, Binning(250, 0., resp_bdr[i]),
							 YVar(dphi_norm, Binning(128, -1*dphi_bdr[i], dphi_bdr[i])));
      
  
    cout<<"RESP bin start Write "<<i<<endl;
 
     genHist0->Smooth(1);
    genHist0->SetName(TString::Format("recoil_resp_hist_truephi0_bin_%d", i));
    genHist0->SetTitle(TString::Format("recoil_resp_hist_truephi0_bin_%d", i));      
    double integral0 = genHist0->Integral();
    genHist0->Scale(1/integral0);

     genHist1->Smooth(1);
    genHist1->SetName(TString::Format("recoil_resp_hist_truephi1_bin_%d", i));
    genHist1->SetTitle(TString::Format("recoil_resp_hist_truephi1_bin_%d", i));      
    double integral1 = genHist1->Integral();
    genHist1->Scale(1/integral1);

     genHist2->Smooth(1);
    genHist2->SetName(TString::Format("recoil_resp_hist_truephi2_bin_%d", i));
    genHist2->SetTitle(TString::Format("recoil_resp_hist_truephi2_bin_%d", i));      
    double integral2 = genHist2->Integral();
    genHist2->Scale(1/integral2);

     genHist3->Smooth(1);
    genHist3->SetName(TString::Format("recoil_resp_hist_truephi3_bin_%d", i));
    genHist3->SetTitle(TString::Format("recoil_resp_hist_truephi3_bin_%d", i));      
    double integral3 = genHist3->Integral();
    genHist3->Scale(1/integral3);

     genHist4->Smooth(1);
    genHist4->SetName(TString::Format("recoil_resp_hist_truephi4_bin_%d", i));
    genHist4->SetTitle(TString::Format("recoil_resp_hist_truephi4_bin_%d", i));      
    double integral4 = genHist4->Integral();
    genHist4->Scale(1/integral4);

     genHist5->Smooth(1);
    genHist5->SetName(TString::Format("recoil_resp_hist_truephi5_bin_%d", i));
    genHist5->SetTitle(TString::Format("recoil_resp_hist_truephi5_bin_%d", i));      
    double integral5 = genHist5->Integral();
    genHist5->Scale(1/integral5);



    ROOTout->cd();
    genHist0->Write(TString::Format("recoil_resp_hist_truephi0_bin_%d", i),TObject::kOverwrite);
    genHist0->Draw("colz");      
    c1->Print(psoutput);

    genHist1->Write(TString::Format("recoil_resp_hist_truephi1_bin_%d", i),TObject::kOverwrite);
    genHist1->Draw("colz");      
    c1->Print(psoutput);

    genHist2->Write(TString::Format("recoil_resp_hist_truephi2_bin_%d", i),TObject::kOverwrite);
    genHist2->Draw("colz");      
    c1->Print(psoutput);

    genHist3->Write(TString::Format("recoil_resp_hist_truephi3_bin_%d", i),TObject::kOverwrite);
    genHist3->Draw("colz");      
    c1->Print(psoutput);

    genHist4->Write(TString::Format("recoil_resp_hist_truephi4_bin_%d", i),TObject::kOverwrite);
    genHist4->Draw("colz");      
    c1->Print(psoutput);

    genHist5->Write(TString::Format("recoil_resp_hist_truephi5_bin_%d", i),TObject::kOverwrite);
    genHist5->Draw("colz");      
    c1->Print(psoutput);
  }

   for (int i=0; i<ptnbins; i++) {
     //this is zbset and response, in bins of luminosity
     if (i!=theBin && theBin != -3) continue;

    if (RecoilRespData[i]->numEntries() < 5) continue;
     cout<<"RESP bin "<<i<<endl;

    RecoilRespData[i]->printMultiline(cout, 1);
    TH2D* genHist0(0);
    TH2D* genHist1(0);
    TH2D* genHist2(0);
    TH2D* genHist3(0);
    TH2D* genHist4(0);
    TH2D* genHist5(0);
    RooDataSet* RecoilRespData_lumi0 = (RooDataSet*) RecoilRespData[i]->reduce("lumi>=0.&&lumi<2.");
    RooDataSet* RecoilRespData_lumi1 = (RooDataSet*) RecoilRespData[i]->reduce("lumi>=2.&&lumi<3.");
    RooDataSet* RecoilRespData_lumi2 = (RooDataSet*) RecoilRespData[i]->reduce("lumi>=3.&&lumi<4.");
    RooDataSet* RecoilRespData_lumi3 = (RooDataSet*) RecoilRespData[i]->reduce("lumi>=4.&&lumi<5.");
    RooDataSet* RecoilRespData_lumi4 = (RooDataSet*) RecoilRespData[i]->reduce("lumi>=5.&&lumi<6.");
    RooDataSet* RecoilRespData_lumi5 = (RooDataSet*) RecoilRespData[i]->reduce("lumi>=6.");

    RecoilRespData_lumi0->printMultiline(cout, 1);
    RecoilRespData_lumi1->printMultiline(cout, 1);
    RecoilRespData_lumi2->printMultiline(cout, 1);
    RecoilRespData_lumi3->printMultiline(cout, 1);
    RecoilRespData_lumi4->printMultiline(cout, 1);
    RecoilRespData_lumi5->printMultiline(cout, 1);


    cout<<"RESP bin start HIST "<<i<<endl;
    genHist0 = (TH2D*) RecoilRespData_lumi0->createHistogram(TString::Format("recoil_resp_zbset_hist_lumibin0_bin_%d", i).Data(), 
							 resp, Binning(500, 0., resp_bdr[i]),
							 YVar(ZBset, Binning(25, 0.,25.)));//was 40 0 20    
    genHist1 = (TH2D*) RecoilRespData_lumi1->createHistogram(TString::Format("recoil_resp_zbset_hist_lumibin1_bin_%d", i).Data(), 
							 resp, Binning(500, 0., resp_bdr[i]),
							 YVar(ZBset, Binning(25, 0.,25.)));//was 40 0 20    
    genHist2 = (TH2D*) RecoilRespData_lumi2->createHistogram(TString::Format("recoil_resp_zbset_hist_lumibin2_bin_%d", i).Data(), 
							 resp, Binning(500, 0., resp_bdr[i]),
							 YVar(ZBset, Binning(25, 0.,25.)));//was 40 0 20    
    genHist3 = (TH2D*) RecoilRespData_lumi3->createHistogram(TString::Format("recoil_resp_zbset_hist_lumibin3_bin_%d", i).Data(), 
							 resp, Binning(500, 0., resp_bdr[i]),
							 YVar(ZBset, Binning(25, 0.,25.)));//was 40 0 20    
    genHist4 = (TH2D*) RecoilRespData_lumi4->createHistogram(TString::Format("recoil_resp_zbset_hist_lumibin4_bin_%d", i).Data(), 
							 resp, Binning(500, 0., resp_bdr[i]),
							 YVar(ZBset, Binning(25, 0.,25.)));//was 40 0 20    
    genHist5 = (TH2D*) RecoilRespData_lumi5->createHistogram(TString::Format("recoil_resp_zbset_hist_lumibin5_bin_%d", i).Data(), 
							 resp, Binning(500, 0., resp_bdr[i]),
							 YVar(ZBset, Binning(25, 0.,25.)));//was 40 0 20
    
   
    cout<<"RESP bin start Write "<<i<<endl;

     genHist0->Smooth(1);
    genHist0->SetName(TString::Format("recoil_resp_zbset_hist_lumibin0_bin_%d", i));
    genHist0->SetTitle(TString::Format("recoil_resp_zbset_hist_lumibin0_bin_%d", i));      
    double integral0 = genHist0->Integral();
    genHist0->Scale(1/integral0);

    genHist1->Smooth(1);
    genHist1->SetName(TString::Format("recoil_resp_zbset_hist_lumibin1_bin_%d", i));
    genHist1->SetTitle(TString::Format("recoil_resp_zbset_hist_lumibin1_bin_%d", i));      
    double integral1 = genHist1->Integral();
    genHist1->Scale(1/integral1);

    genHist2->Smooth(1);
    genHist2->SetName(TString::Format("recoil_resp_zbset_hist_lumibin2_bin_%d", i));
    genHist2->SetTitle(TString::Format("recoil_resp_zbset_hist_lumibin2_bin_%d", i));      
    double integral2 = genHist2->Integral();
    genHist2->Scale(1/integral2);

    genHist3->Smooth(1);
    genHist3->SetName(TString::Format("recoil_resp_zbset_hist_lumibin3_bin_%d", i));
    genHist3->SetTitle(TString::Format("recoil_resp_zbset_hist_lumibin3_bin_%d", i));      
    double integral3 = genHist3->Integral();
    genHist3->Scale(1/integral3);

     genHist4->Smooth(1);
    genHist4->SetName(TString::Format("recoil_resp_zbset_hist_lumibin4_bin_%d", i));
    genHist4->SetTitle(TString::Format("recoil_resp_zbset_hist_lumibin4_bin_%d", i));      
    double integral4 = genHist4->Integral();
    genHist4->Scale(1/integral4);

     genHist5->Smooth(1);
    genHist5->SetName(TString::Format("recoil_resp_zbset_hist_lumibin5_bin_%d", i));
    genHist5->SetTitle(TString::Format("recoil_resp_zbset_hist_lumibin5_bin_%d", i));      
    double integral5 = genHist5->Integral();
    genHist5->Scale(1/integral5);

    ROOTout->cd();
    genHist0->Write(TString::Format("recoil_resp_zbset_hist_lumibin0_bin_%d", i),TObject::kOverwrite);
    genHist0->Draw("colz");      
    c1->Print(psoutput);

    genHist1->Write(TString::Format("recoil_resp_zbset_hist_lumibin1_bin_%d", i),TObject::kOverwrite);
    genHist1->Draw("colz");      
    c1->Print(psoutput);

    genHist2->Write(TString::Format("recoil_resp_zbset_hist_lumibin2_bin_%d", i),TObject::kOverwrite);
    genHist2->Draw("colz");      
    c1->Print(psoutput);

    genHist3->Write(TString::Format("recoil_resp_zbset_hist_lumibin3_bin_%d", i),TObject::kOverwrite);
    genHist3->Draw("colz");      
    c1->Print(psoutput);

    genHist4->Write(TString::Format("recoil_resp_zbset_hist_lumibin4_bin_%d", i),TObject::kOverwrite);
    genHist4->Draw("colz");      
    c1->Print(psoutput);

    genHist5->Write(TString::Format("recoil_resp_zbset_hist_lumibin5_bin_%d", i),TObject::kOverwrite);
    genHist5->Draw("colz");      
    c1->Print(psoutput);

  }
   std::vector <double>  parmMean;
   std::vector <double>  parmA;
   std::vector <double>  parmB;
   std::vector <double>  parmC;
   std::vector <double>  parmD;
   
   parmMean.clear();
   parmA.clear();
   parmB.clear();
   parmC.clear();
   parmD.clear();

  for (int i=0; i<ptnbinszphi; i++) {
     //this is zbset and response, in bins of luminosity
     if (i!=theBin && theBin != -4) continue;

    if (RecoilRespData[i]->numEntries() < 5) continue;
     cout<<"RESP bin "<<i<<endl;

    RecoilRespData[i]->printMultiline(cout, 1);
    TH2D* genHist(0);
  
    double twopi = 2*TMath::Pi();
    cout<<"RESP bin start HIST "<<i<<endl;
    genHist = (TH2D*) RecoilRespData[i]->createHistogram(TString::Format("recoil_resp_zphi_hist_bin_%d", i).Data(), 
							 resp, Binning(500, 0., resp_bdr[i]),
							    YVar(zphi, Binning(64, 0., twopi)));//was 40 0 20    
  
   
    cout<<"RESP bin start Write "<<i<<endl;
   
    genHist->SetName(TString::Format("recoil_resp_zphi_hist_bin_%d", i));
    genHist->SetTitle(TString::Format("recoil_resp_zphi_hist_bin_%d", i));      
    TProfile *myhisty = genHist->ProfileY();

    ROOTout->cd();
    myhisty->Write(TString::Format("recoil_resp_zphi_hist_bin_%d", i),TObject::kOverwrite);
    TF1 *pol3 = new TF1("pol3", "pol3");
    myhisty->Fit("pol3");
    double stats[7];
    myhisty->GetStats(stats); 
    parmMean.push_back(myhisty->GetMean(2));
    parmA.push_back(pol3->GetParameter(0));
    parmB.push_back(pol3->GetParameter(1));
    parmC.push_back(pol3->GetParameter(2));
    parmD.push_back(pol3->GetParameter(3));

    myhisty->Draw();  
    c1->Print(psoutput); 
  }

  if (theBin == -4){
    
      cout<<"HardRecoil_zphiresp_Mean:       ";
    for (int i=0; i<ptnbinszphi-1; i++) {
      cout<<parmMean[i]<<" ";
    }
    cout<<parmMean[ptnbinszphi-1]<<endl;;

      cout<<"HardRecoil_zphiresp_ParameterA: ";
    for (int i=0; i<ptnbinszphi-1; i++) {
      cout<<parmA[i]<<" ";
    }
    cout<<parmA[ptnbinszphi-1]<<endl;;

      cout<<"HardRecoil_zphiresp_ParameterB: ";
    for (int i=0; i<ptnbinszphi-1; i++) {
      cout<<parmB[i]<<" ";
    }
    cout<<parmB[ptnbinszphi-1]<<endl;;

      cout<<"HardRecoil_zphiresp_ParameterC: ";
    for (int i=0; i<ptnbinszphi-1; i++) {
      cout<<parmC[i]<<" ";
    }
    cout<<parmC[ptnbinszphi-1]<<endl;;

      cout<<"HardRecoil_zphiresp_ParameterD: ";
    for (int i=0; i<ptnbinszphi-1; i++) {
      cout<<parmD[i]<<" ";
    }
    cout<<parmD[ptnbinszphi-1]<<endl;;
  }



  for (int i=0; i<ptnbinsset; i++) {      

    if (theBin != -2) continue;      
    if (SETData[i]->numEntries() < 5) continue;
    cout<<"SET bin "<<i<<endl;
    SETData[i]->printMultiline(cout, 1);
    TH2D* genHist(0);
  
    cout<<"SET bin start HIST "<<i<<endl;
    genHist = (TH2D*) SETData[i]->createHistogram(TString::Format("set_ut_kde_bin_%d", i).Data(), 
						  set_ut, Binning(500, 0., set_ut_bdr[i]),
						  YVar(ut, Binning(500, 0., ut_bdr[i]))); 
    genHist->Smooth(1);
    genHist->SetName(TString::Format("set_ut_hist_bin_%d", i));
    genHist->SetTitle(TString::Format("set_ut_hist_bin_%d", i));      
    double integral = genHist->Integral();
    genHist->Scale(1/integral);
    ROOTout->cd();
    genHist->Write(TString::Format("set_ut_hist_bin_%d", i),TObject::kOverwrite);
    genHist->Draw("colz");      
    c1->Print(psoutput);
    
  }

  c1->Print(TString::Format("%s]", psoutput));

  ROOTout->Close();

  return(0);
}
int recoil_analysis_FINAL2_lessbins5_FINAL(){
  
  //NOTE: Throughout this code, recoil manager, and other recoil processing scripts, zphi and true recoil phi are used interchangably.  
  //However, we always mean true recoil phi for applications that are used in PMCS.

  recoil_analysis("exampleAllkillcellALLFinalupdatedkillcellRun3.txt", "testNEWFinalnew_updatedkillcellRun3_lessbins5_lessset_final.root", "testNEWFinalnew_updatedkillcellRun3_lessbins5_lessset_final_1.ps", -1);
  recoil_analysis("exampleAllkillcellALLFinalupdatedkillcellRun3.txt", "testNEWFinalnew_updatedkillcellRun3_lessbins5_lessset_final.root", "testNEWFinalnew_updatedkillcellRun3_lessbins5_lessset_final_2.ps", -2);
  recoil_analysis("exampleAllkillcellALLFinalupdatedkillcellRun3.txt", "testNEWFinalnew_updatedkillcellRun3_lessbins5_lessset_final.root", "testNEWFinalnew_updatedkillcellRun3_lessbins5_lessset_final_3.ps", -3);
  recoil_analysis("exampleAllkillcellALLFinalupdatedkillcellRun3.txt", "testNEWFinalnew_updatedkillcellRun3_lessbins5_lessset_final.root", "testNEWFinalnew_updatedkillcellRun3_lessbins5_lessset_final_4.ps", -4);
  
  return(0);
}
