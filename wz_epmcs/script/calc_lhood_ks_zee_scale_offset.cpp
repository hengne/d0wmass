////////////////////////////////////////////////////////////////////////
//Compare zee events with MC (normalize to mass window)
//change enegy scale, energy resolution parameters etc
//to find the uncertainty and calculate the log likelihood
//also calculate the KS value
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
using namespace std;

#include "TCanvas.h"
#include "TGraph.h"
#include "TH3.h"
#include "TH2.h"
#include "TF1.h"
#include "TLine.h"

#include "Entries_Calc.C"
#include "Quadratic_Equation.C"
#include "log_likelihood.C"

void calc_lhood_ks_zee_scale_offset() {

  ofstream out("likelihood.out");
  
  gROOT -> ProcessLine(".x style.C");
  gROOT -> ProcessLine("gStyle -> SetOptStat(0)");
  
  double min_masswindow = 75.;
  double max_masswindow = 105.;

  //plot CC or EC  
  bool CC = true;

  //KS test
  bool KS_Test = false;

  //ten points
  static const Int_t N_scale = 10;
  static const Int_t N_offset = 10;

  double central_scale = 0., central_offset = 0.;
  double scale_step = 0., offset_step = 0.;

  if(CC) {
    central_scale = 1.005;
    central_offset = 0.3;
    scale_step = 0.0005;
    offset_step = 0.1;
  } else {
    central_scale = 0.9990;
    central_offset = 0.5744;
    scale_step = 0.0002;
    offset_step = 0.2;
  }

  /////////////////////////////////////////////////////////////////
  //get invariant mass shape for zee with two track match
  /////////////////////////////////////////////////////////////////
  TFile::Open("data.root", "READ");
  TH1F *data;
  TH1F *data_signal;

  if(CC) {
    gDirectory->cd("ZCand_Hist");
    data = (TH1F *)gDirectory-> Get("ZCandMass_0");
    data_signal = (TH1F *)((TH1F *)gDirectory -> Get("ZCandMass_0"))->Clone("data_signal");
  } else {
    gDirectory->cd("ZCand_Hist");
    data = (TH1F *)gDirectory-> Get("hZcandMass_2");
    data_signal = (TH1F *)((TH1F *)gDirectory -> Get("hZcandMass_2"))->Clone("data_signal");
  }
  gDirectory->cd("");

  TCanvas *canv_mass = new TCanvas("canv_mass", "mass",10,10,476,323);
  data -> SetMarkerColor(4);
  data -> SetMarkerStyle(8);
  data -> Draw("pe");
  
  double num_data = Entries_Calc(data, min_masswindow, max_masswindow);
  cout << "Mass Window [" << min_masswindow << ", " << max_masswindow << "]" << endl;
  cout << "Events in mass window (Data): " << num_data << endl;

  ////////////////////////////////////////////////////////////////////
  //get MC events
  ////////////////////////////////////////////////////////////////////
  TFile::Open("result_zee4.root", "READ");
  TH1F *mc;
  TH1F *mc_signal;

  if(CC) {
    gDirectory->cd("smeared");
    mc = (TH1F *)gDirectory -> Get("smeared_hZcandMass_CCCC");
    mc_signal = (TH1F *)((TH1F *)gDirectory -> Get("smeared_hZcandMass_CCCC"))->Clone("mc_signal");
  } else {
    gDirectory->cd("smeared");
    mc = (TH1F *)gDirectory -> Get("smeared_hZcandMass_ECEC");
    mc_signal = (TH1F *)((TH1F *)gDirectory -> Get("smeared_hZcandMass_ECEC"))->Clone("mc_signal");
  }
  //gDirectory->cd("");

  double num_mc = Entries_Calc(mc, min_masswindow, max_masswindow);
  cout << "Events in mass window (MC): " << num_mc << endl;
  cout << endl;

  //scale MC events
  mc -> Scale(num_data/num_mc);
  mc -> SetLineColor(2);
  mc -> Draw("same");
  canv_mass -> Update();

  //calculate log_likelihood
  gROOT -> LoadMacro("log_likelihood.C");
  Log_Likelihood(data, mc, min_masswindow, max_masswindow );

  ////////////////////////////////////////////////////////////////////////
  //Log likelihood method for different energy scale and energy offset
  ////////////////////////////////////////////////////////////////////////
  TH1F *mc_scale_offset[N_scale*N_offset];
  char name[50];
  double likelihood[N_scale*N_offset], min_likelihood = 9999.;
  int index_min = -1;

  TH3F *h3f;
  TH2F *h2f;
  if(CC) {
    h3f = new TH3F("h3f", "Likelihood vs energy scale and offset", 10, 0.996, 1.014, 
			 10, -0.9, 0.9, 10000, 0., 10000.);
    h2f = new TH2F("h2f", "Likelihood vs energy scale and offset", 
 		   N_scale, 
		   central_scale - (N_scale/2)*scale_step -0.5*scale_step, 
		   central_scale + (N_scale/2)*scale_step -0.5*scale_step,
 		   N_offset, 
		   central_offset - (N_offset/2)*offset_step - 0.5*offset_step, 
		   central_offset + (N_offset/2)*offset_step - 0.5*offset_step);

//     h2f = new TH2F("h2f", "Likelihood vs energy scale and offset", 
// 		   100,0.97975 ,1.02975 ,
// 		   20, -0.75 ,1.25);

  } else {
    h3f = new TH3F("h3f", "Likelihood vs energy scale and offset", 10, 1.0135, 1.027, 
			 10, 0.55, 1.45, 200, 40., 50.);
  }

  //use two arrays to store the scale values and offset values
  double scale_value[N_scale], offset_value[N_offset];
  for(int i=0; i<N_offset; i++) {
    offset_value[i] = central_offset + ((double)i - (double)(N_offset)/2.0) * offset_step;
  }
  for(int i=0; i<N_scale; i++) {
    scale_value[i] = central_scale + ((double)i - (double)(N_scale)/2.0) * scale_step;
  }

  int ihist = 0;
  double scale_fix_offset[N_scale] = {0.}, offset_fix_scale[N_offset] = {0.};
  double likelihood_scale[N_scale] = {0.}, likelihood_offset[N_offset] = {0.};

  for(int ii=0; ii<N_scale; ++ii) { //loop over scale
    for(int jj=0; jj<N_offset; ++jj) { //loop over offset
      double scale = central_scale + ((double)ii - (double)(N_scale)/2.0) * scale_step;
      double offset = central_offset + ((double)jj - (double)(N_offset)/2.0) * offset_step;

      if(CC) sprintf(name, "%s%d%s", "smeared_hZcandMass_Scale_CCCC_",  ihist, ";1");    
      else sprintf(name, "%s%d%s", "smeared_hZcandMass_Scale_ECEC_",  ihist, ";1");    
//       if(CC) sprintf(name, "%s%d%s", "hZcandMass_CCCC_Scale_Offset ", ihist, ";1");    
//       else sprintf(name, "%s%d%s", "hZcandMass_ECEC_Scale_Offset ", ihist, ";1");    

      mc_scale_offset[ihist] = (TH1F *)gROOT -> FindObject(name);      


      double mc_event = Entries_Calc(mc_scale_offset[ihist], min_masswindow, max_masswindow);
      mc_scale_offset[ihist] -> Scale(num_data/mc_event);
      mc_scale_offset[ihist] -> SetLineColor(2);
      //calculate log likelihood
      likelihood[ihist] = Log_Likelihood(data, mc_scale_offset[ihist], min_masswindow, max_masswindow);

      h2f -> Fill(scale, offset, likelihood[ihist]);

      h3f -> Fill(scale, offset, likelihood[ihist]);
      h3f -> GetXaxis() -> SetLabelSize(0.02);
      h3f -> GetXaxis() -> SetTitleOffset(2);
      h3f -> GetXaxis() -> SetTitle("Energy Scale");
      h3f -> GetYaxis() -> SetLabelSize(0.02);
      h3f -> GetYaxis() -> SetTitleOffset(2);
      h3f -> GetYaxis() -> SetTitle("Energy Offset");
      h3f -> GetZaxis() -> SetLabelSize(0.02);
      h3f -> GetZaxis() -> SetTitleOffset(1);
      h3f -> GetZaxis() -> SetTitle("Likelihood");
      out << scale << " " << offset << " " << likelihood[ihist] << endl;

      //fix offset and see how likelihood vary with energy scale     
      if(jj == N_offset/2) {
	scale_fix_offset[ii] = scale;
	likelihood_scale[ii] = likelihood[ihist];
      }
      //fix scale and see how likelihood vary with energy offset
      if(ii == N_scale/2) {
	offset_fix_scale[jj] = offset;
	likelihood_offset[jj] = likelihood[ihist];
      }
      
      //get the one with the minimum likelihood
      if(likelihood[ihist] < min_likelihood) {
	min_likelihood = likelihood[ihist];
	index_min = ihist;
      }

      ihist ++;
    }//offset
  }//scale
  
  //////////////////////////////////////////////////////
  //likelihood vs energy scale and energy offset
  //////////////////////////////////////////////////////
  TCanvas *canv_scale_offset = new TCanvas("canv_scale_offset", "canvas", 10, 420, 456, 334);
  h3f -> Draw();
  canv_scale_offset -> Update();
  
  //likelihood vs energy scale (fix energy offset)
  TCanvas *canv_scale = new TCanvas("canv_scale", "canvas", 521, 15, 546, 314);
  TGraph *h_scale = new TGraph(N_scale, scale_fix_offset, likelihood_scale);
  h_scale -> SetMarkerColor(kBlue);
  h_scale -> SetMarkerStyle(21);
  h_scale -> SetTitle(0);
  h_scale -> GetHistogram() -> SetXTitle("Energy Scale");
  h_scale -> GetHistogram() -> SetYTitle("Log Likelihood");
  h_scale -> Draw("AP");
  h_scale -> Fit("pol2");
  canv_scale -> Update();
  
  //Get the fitted function and fitting variables
  TF1 *fitfunc1 = h_scale -> GetFunction("pol2");
  double p0 =  fitfunc1 -> GetParameter(0);
  double p1 =  fitfunc1 -> GetParameter(1);
  double p2 =  fitfunc1 -> GetParameter(2);

  double scale_calc = -p1/(2*p2);
  double like_calc = p2*scale_calc*scale_calc + p1*scale_calc + p0;
  double x1 = 0., x2 = 0.;
  Quadratic_Equation(p2, p1, p0-like_calc-5, x1, x2);
  cout << "Scale = " << x1 << " " << scale_calc << " " << x2 << endl;

  ///////////////////////////////////////////////////////////
  //likelihood vs energy offset (fix energy scale)
  ///////////////////////////////////////////////////////////
  TCanvas *canv_offset = new TCanvas("canv_offset", "canvas", 500, 419, 569, 334);
  TGraph *h_offset = new TGraph(N_offset, offset_fix_scale, likelihood_offset);
  h_offset -> SetMarkerColor(kBlue);
  h_offset -> SetMarkerStyle(21);
  h_offset -> SetTitle(0);
  h_offset -> GetHistogram() -> SetXTitle("Energy Offset");
  h_offset -> GetHistogram() -> SetYTitle("Log Likelihood");
  h_offset -> Draw("AP");
  h_offset -> Fit("pol2");
  canv_offset -> Update();

  TF1 *fitfunc2 = h_offset -> GetFunction("pol2");
  double p02 =  fitfunc2 -> GetParameter(0);
  double p12 =  fitfunc2 -> GetParameter(1);
  double p22 =  fitfunc2 -> GetParameter(2);

  double offset_calc = -p12/(2*p22);
  double like_calc2 = p22*offset_calc*offset_calc + p12*offset_calc + p02;
  double x12 = 0., x22 = 0.;
  Quadratic_Equation(p22, p12, p02-like_calc2-0.5, x12, x22);
  cout << "Offset = " << x12 << " " << offset_calc << " " << x22 << endl;

  //Data/MC comparison with the minimum likelihood
  TCanvas *canv_best = new TCanvas("canv_best", "Data/MC comparison with Minimum Likelihood", 377, 312, 452, 250);
  data -> SetXTitle("M_{ee} (GeV)");
  data -> SetYTitle("# of Events/1.5 GeV");
  data -> Draw("pe");  
  TH1F *mc_new_test =  dynamic_cast< TH1F* >(mc_scale_offset[index_min]->Clone("mc_new_test"));
  mc_new_test -> Draw("same");
  canv_best -> Update();

  ////////////////////////////////////////////////////
  //KS test
  ///////////////////////////////////////////////////
  TH1F *his1 =  dynamic_cast< TH1F* >(data_signal->Clone());
  TH1F *his2 =  dynamic_cast< TH1F* >(data_signal->Clone());
  
  double entries_data_signal = data_signal -> GetEntries();
  double entries_mc_signal = mc_signal -> GetEntries();  
  double integral_data = 0;
  double integral_mc = 0;
  double max_diff = 0;

  for(int ibin=0; ibin<=data_signal->GetNbinsX(); ++ibin) {
    integral_data += data_signal -> GetBinContent(ibin);
    integral_mc += mc_signal -> GetBinContent(ibin);

    double frac_data = integral_data/entries_data_signal;
    double frac_mc = integral_mc/entries_mc_signal;
    double diff = fabs(frac_data - frac_mc);

    if(max_diff < diff) max_diff = diff;
    his1 -> SetBinContent(ibin, frac_data);
    his2 -> SetBinContent(ibin, frac_mc);
  }

  //plot the integrated distribution for data and MC
  TCanvas *canv_ks = new TCanvas("canv_ks", "canvas", 10, 420, 456, 334);
  his1 -> SetLineColor(2);
  his1 -> SetTitle(0);
  his1 -> SetXTitle("M_{ee}(GeV)");
  his1 -> SetYTitle("Integrated Distribution");
  his1 -> Draw();
  his2 -> SetLineColor(4);
  his2 -> Draw("same");
  canv_ks -> Update();

  cout << "KS Value: " << max_diff << endl;

  if(KS_Test) {
    /////////////////////////////////////////////////////////
    //loop over all histograms to calculate KS value
    ////////////////////////////////////////////////////////
    TH1F *mc_ks[N_scale*N_offset];
    //look at KS value vs energy scale and energy offset
    double scale_ks[N_scale], offset_ks[N_offset];

    int ihist_ks = 0;
    cout << "Calculating ks value for all histograms, please wait......" << endl;

    for(int ii=0; ii<N_scale; ++ii) { //loop over scale
      for(int jj=0; jj<N_offset; ++jj) { //loop over offset
// 	double scale = central_scale + (ii - 5.) * scale_step;
// 	double offset = central_offset + (jj - 5.) * offset_step;

	if(CC) sprintf(name, "%s%d%s", "smeared_hZcandMass_Scale_CCCC_", ihist_ks, ";1");
	else sprintf(name, "%s%d%s", "smeared_hZcandMass_Scale_ECEC_", ihist_ks, ";1");
	mc_ks[ihist_ks] = (TH1F *)gROOT -> FindObject(name);

	double data_entries = 0;
	double mc_entries = 0;
	double diff_max_ks = 0.;
	//get the total entries for MC sample
	//for data, it is the same

	double entries_mc_signal_ks = mc_ks[ihist_ks] -> GetEntries();  

	for(int ibin=0; ibin<=data_signal->GetNbinsX(); ++ibin) {
	  data_entries += data_signal -> GetBinContent(ibin);
	  mc_entries += mc_ks[ihist_ks] -> GetBinContent(ibin);

	  double frac_data = data_entries/entries_data_signal;
	  double frac_mc = mc_entries/entries_mc_signal_ks;
	  double diff = fabs(frac_data - frac_mc);	

	  if(diff_max_ks < diff) diff_max_ks = diff;	
	}//loop over 40000 bins

	cout << "histogram " << ihist_ks << " , KS value = " << diff_max_ks << endl;

	//fix energy scale or energy offset and see the ks value vs the other variable
	if(jj == (N_offset/2+1)) scale_ks[ii] = diff_max_ks;
	if(ii == (N_scale/2+1)) offset_ks[jj] = diff_max_ks;

	ihist_ks ++;
      }//offset
    }//scale

    TCanvas *canv_scale_ks = new TCanvas("canv_scale_ks", "KS value for Fix energy offset, vary energy scale", 
					 10, 420, 456, 334);
    TGraph *gr1_ks = new TGraph(N_scale, scale_value, scale_ks);
    gr1_ks -> SetMarkerColor(kBlue);
    gr1_ks -> SetMarkerStyle(20);
    gr1_ks -> SetTitle(0);
    gr1_ks -> GetHistogram() -> SetXTitle("Energy Scale");
    gr1_ks -> GetHistogram() -> SetYTitle("KS value");
    gr1_ks -> Draw("ALP");
    canv_scale_ks -> Update();

    //mean value of Z mass distribution vs energy offset (fix energy scale)
    TCanvas *canv_offset_ks = new TCanvas("canv_offset_ks", "KS value for Fix energy scale, vary energy offset", 
					  10, 420, 456, 334);
    TGraph *gr2_ks = new TGraph(N_offset, offset_value, offset_ks);
    gr2_ks -> SetMarkerColor(kBlue);
    gr2_ks -> SetMarkerStyle(20);
    gr2_ks -> SetTitle(0);
    gr2_ks -> GetHistogram() -> SetXTitle("Energy Offset");
    gr2_ks -> GetHistogram() -> SetYTitle("KS value");
    gr2_ks -> Draw("ALP");
    canv_offset_ks -> Update();
    
  }//KS_Test    

  //////////////////////////////////////////////////////////////////////
  //count the mean value of invariant mass for very good Z candidates
  /////////////////////////////////////////////////////////////////////
  TH1F *data_new =  dynamic_cast< TH1F* >(data->Clone());
  TH1F *mc_new =  dynamic_cast< TH1F* >(mc->Clone());

  //bin from [50, 70] corresponding mass from [75, 105]
  data_new->GetXaxis()->SetRange(50, 70);
  mc_new->GetXaxis()->SetRange(50, 70);

  //fit mass distribution with a guassian distribution and 
  //only look at the mean value and the uncertainty for data
  TCanvas *canv_mass_fit = new TCanvas("canv_mass_fit", "fit the mass distribution with a gaussian function", 
				       10, 420, 456, 334);
  TF1 *f=new TF1("f", "gaus", 75, 105);
  double par[3];
  double parerror[3];
  data_new->Fit("f", "R");
  f -> GetParameters(&par[0]);
  parerror[0] = f -> GetParError(0);
  parerror[1] = f -> GetParError(1);
  parerror[2] = f -> GetParError(2);  
  canv_mass_fit -> Update();

  double data_mean = data_new -> GetMean();
  double data_mean_error = parerror[1];

  cout << "Data Mean [75, 105]: " << data_mean << " +- " << data_mean_error << endl;

  TH1F *mc_latest[N_scale*N_offset];
  //look at mean value vs energy scale and energy offset
  double scale_mean[N_scale], offset_mean[N_offset];

  int ihist_new = 0;
  for(int ii=0; ii<N_scale; ++ii) { //loop over scale
    for(int jj=0; jj<N_offset; ++jj) { //loop over offset
//       double scale = central_scale + (ii - 5.) * scale_step;
//       double offset = central_offset + (jj - 5.) * offset_step;

      if(CC) sprintf(name, "%s%d%s", "smeared_hZcandMass_Scale_CCCC_", ihist_new, ";1");
      else sprintf(name, "%s%d%s", "smeared_hZcandMass_Scale_ECEC_", ihist_new, ";1");
//       if(CC) sprintf(name, "%s%d%s", "hZcandMass_CCCC_Scale_Offset ", ihist_new, ";1");    
//       else sprintf(name, "%s%d%s", "hZcandMass_ECEC_Scale_Offset ", ihist_new, ";1");    
      
      mc_latest[ihist_new] = (TH1F *)gROOT -> FindObject(name);      
      mc_latest[ihist_new]->GetXaxis()->SetRange(50, 70);

      //get the mean value for mc
      double tmp = mc_latest[ihist_new] -> GetMean();

      //fix energy scale or energy offset and see the mean vs the other variable
      if(jj == (N_offset/2+1)) scale_mean[ii] = tmp;
      if(ii == (N_scale/2+1)) offset_mean[jj] = tmp;
      
      ihist_new ++;
    }
  }//scale

  //mean value of Z mass distribution vs energy scale (fix energy offset)
  TCanvas *canv_scale2 = new TCanvas("canv_scale2", "Fix energy offset, vary energy scale", 
				    10, 420, 456, 334);
  TGraph *gr1 = new TGraph(N_scale, scale_value, scale_mean);
  gr1 -> SetMarkerColor(kBlue);
  gr1 -> SetMarkerStyle(20);
  gr1 -> SetTitle(0);
  gr1 -> GetHistogram() -> SetXTitle("Energy Scale");
  gr1 -> GetHistogram() -> SetYTitle("Log Likelihood");
  gr1 -> Draw("ALP");

  TLine *l1_scale = new TLine(scale_value[0], data_mean,  scale_value[9], data_mean);
  TLine *l1_scale_Up = new TLine(scale_value[0], data_mean+data_mean_error,  scale_value[9], data_mean+data_mean_error);
  TLine *l1_scale_Down = new TLine(scale_value[0], data_mean-data_mean_error,  scale_value[9], data_mean-data_mean_error);
  l1_scale -> SetLineColor(2);
  l1_scale_Up -> SetLineColor(2);
  l1_scale_Down -> SetLineColor(2);
  l1_scale -> Draw();
  l1_scale_Up -> Draw();
  l1_scale_Down -> Draw();

  canv_scale2 -> Update();

  //mean value of Z mass distribution vs energy offset (fix energy scale)
  TCanvas *canv_offset2 = new TCanvas("canv_offset2", "Fix energy scale, vary energy offset", 
				     10, 420, 456, 334);
  TGraph *gr2 = new TGraph(N_offset, offset_value, offset_mean);
  gr2 -> SetMarkerColor(kBlue);
  gr2 -> SetMarkerStyle(20);
  gr2 -> SetTitle(0);
  gr2 -> GetHistogram() -> SetXTitle("Energy Offset");
  gr2 -> GetHistogram() -> SetYTitle("Log Likelihood");
  gr2 -> Draw("ALP");

  TLine *l1_offset = new TLine(offset_value[0], data_mean,  offset_value[9], data_mean);
  TLine *l1_offset_Up = new TLine(offset_value[0], data_mean+data_mean_error,  offset_value[9], data_mean+data_mean_error);
  TLine *l1_offset_Down = new TLine(offset_value[0], data_mean-data_mean_error,  offset_value[9], data_mean-data_mean_error);
  l1_offset -> SetLineColor(2);
  l1_offset_Up -> SetLineColor(2);
  l1_offset_Down -> SetLineColor(2);
  l1_offset -> Draw();
  l1_offset_Up -> Draw();
  l1_offset_Down -> Draw();

  canv_offset2 -> Update();

  cout << endl;
  cout << "###################################################################" << endl;
  cout << "WARNING: make sure to change the central_scale_cc, central_scale_ec" << endl;  
  cout << "###################################################################" << endl;
}
