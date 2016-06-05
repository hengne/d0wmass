#include "Fitter.hpp"

Double_t fitf(Double_t *x,Double_t *par)
{
  double fitval=0.0;
  if (x[0]<par[0]) {
    fitval = par[2];
    //fitval = par[2]*(1 - par[3]*(x[0]));
  } else {
    fitval = par[2]*(1 - par[1]*(x[0] - par[0]));
  }

  return fitval;
}
  
void run_alt_smooth(){
  gROOT->LoadMacro("Fitter.cpp");
  TPostScript *myps = new TPostScript("upara_eff_check022008_check.ps",111);
  // mass range
  double xmin = 50., xmax = 130.;
  
  // data
  TFile *data=new TFile("result_0221.root");
  gDirectory->cd("ZCand_Hist");
  
  const Int_t NBins = 15; //2 gev upara bins
  const Int_t NBinsX = 100; //1 gev mass bins
   
  TH2D *before = (TH2D *)gROOT->FindObject("ZCandUPara_V_Mass_NoCuts");
  TH2D *after = (TH2D *)gROOT->FindObject("ZCandUPara_V_Mass_BothWithGoodSpatialMatch_IsoHMxCut");
  
  //these x bins are mass
  int rbinpt = 4;
  before->RebinX(rbinpt);

  after->RebinX(rbinpt);
 
  //y bins are upara:
  int rbinupara = 8;
  before->RebinY(rbinupara);
  after->RebinY(rbinupara);
    
  Int_t NBins_X = before->GetNbinsX();
  Double_t Axis_XMin = before->GetXaxis()->GetXmin();
  Double_t Axis_XMax = before->GetXaxis()->GetXmax();
  
  if(NBins_X != NBinsX) {
    cout<<"NBins="<<NBinsX<<" while NBins_X="<<NBins_X<<" make sure they are the same"<<endl;
    exit;
  }
  
  Int_t NBins_Y = before->GetNbinsY();
  Double_t Axis_YMin = before->GetYaxis()->GetXmin();
  Double_t Axis_YMax = before->GetYaxis()->GetXmax();
  cout<<"Mass bin "<<NBins_Y<<" from "<<Axis_YMin<<" to "<<Axis_YMax<<endl;
  
  // 1D histogram
  TH1D *before_mass[NBins], *after_mass[NBins], *diff_mass[NBins], *bkgnd_mass[NBins];
  double variable[NBins], variable_err[NBins];
  
  char name[50];
  for (int ybin = 0; ybin <NBins_Y; ybin ++){   //include underflow, but doesnt go to upper limit. 
                                                 //not really a problem because there are few events there
                                                 //and we know the correct position anyway. 
    sprintf(name, "%s%d", "before_", ybin);
    before_mass[ybin] = new TH1D(name, name, NBins_X, Axis_XMin, Axis_XMax);
    sprintf(name, "%s%d", "after_", ybin);
    after_mass[ybin] = new TH1D(name, name, NBins_X, Axis_XMin, Axis_XMax);
    sprintf(name, "%s%d", "diff_", ybin);
    diff_mass[ybin] =  new TH1D(name, name, NBins_X, Axis_XMin, Axis_XMax);
    
    variable[ybin] = before->GetYaxis()->GetBinCenter(ybin);
    variable_err[ybin] = 1.0;
    
    for(int xbin=0; xbin < NBins_X; xbin ++) {
      
      cout<<"x,y: "<<xbin<<","<<ybin<<" before "<<before->GetBinContent(xbin, ybin)<<" after "<<after->GetBinContent(xbin, ybin)<<" diff " << (before->GetBinContent(xbin, ybin) - after->GetBinContent(xbin, ybin))<< endl;
      before_mass[ybin] -> SetBinContent(xbin, before->GetBinContent(xbin, ybin));
      after_mass[ybin] -> SetBinContent(xbin, after->GetBinContent(xbin, ybin));
      diff_mass[ybin]-> SetBinContent(xbin, (before->GetBinContent(xbin, ybin) - after->GetBinContent(xbin, ybin)) );
    }
   before_mass[ybin]->Draw();
  }
  
  // signal
  TFile *mc = new TFile("signal.root");
  gDirectory->cd("smeared");

  TH2D *sig2 = (TH2D *)gROOT->FindObject("smeared_hZcandMass_V_UPara_CCCC");
  sig2->RebinY(rbinupara);  //here x is the mass, y is upara
  //sig2->RebinX(rbinpt);  //here x is the mass, y is upara
  
  Int_t NBins_X = sig2->GetNbinsX();
  Double_t Axis_XMin = sig2->GetXaxis()->GetXmin();
  Double_t Axis_XMax = sig2->GetXaxis()->GetXmax();
   
  Int_t NBins_Y = sig2->GetNbinsY();
  Double_t Axis_YMin = sig2->GetYaxis()->GetXmin();
  Double_t Axis_YMax = sig2->GetYaxis()->GetXmax();
  cout<<"upara bin "<<NBins_Y<<" from "<<Axis_YMin<<" to "<<Axis_YMax<<endl;
  
  if(NBins_Y != NBins) {
    cout<<"NBins="<<NBins<<" while NBins_Y="<<NBins_Y<<" make sure they are the same"<<endl;
    exit;
  }
   
  cout<<"NBinsx="<<NBinsX<<" while NBins_X="<<NBins_X<<" make sure they are the same"<<endl;
  NBins_X = NBinsX;
  Axis_XMin = 50.;

  // 1D histogram
  TH1D *Sig_All[NBins];
  double variable[NBins], variable_err[NBins];
  TH1D *QCDBkg_All[NBins];
  
  //now for the bkg histogram:
  TFile *data=new TFile("result_bkg.root");
  gDirectory->cd("ZCand_Hist");
  TH2D *bkgnd = (TH2D *)gROOT->FindObject("ZCandUPara_V_Mass_0");
  bkgnd->RebinX(rbinupara); //upara is x
  bkgnd->RebinY(4); //mass is y. great
  //bkgnd->Draw("colz");

  char name[50];
  for (int ybin = 0; ybin < NBins_Y; ybin ++){
    sprintf(name, "%s%d", "sig_", ybin);
    Sig_All[ybin] = new TH1D(name, name, NBins_X, Axis_XMin, Axis_XMax); //note range
    //now is consistent with wmass analysis
    
    // variable[ybin] = sig2->GetYaxis()->GetBinCenter(ybin);
    //variable_err[ybin] = 0.;
    
    for(int xbin=50; xbin < 150; xbin ++) { //now is consistent with wmass analysis
      Sig_All[ybin] -> SetBinContent(xbin-50, sig2->GetBinContent(xbin,ybin)); //note order
    }  //pmcs ranges is from 0 to 150 instead of 50 to 150
    // Sig_All[ybin] -> Draw();

    sprintf(name, "%s%d", "bkgnd_", ybin);
    QCDBkg_All[ybin] = new TH1D(name, name, NBins_X, Axis_XMin, Axis_XMax);
    sprintf(name, "%s%d", "bkgnd_orig_", ybin);
    bkgnd_mass[ybin] = new TH1D(name, name, NBins_X, Axis_XMin, Axis_XMax);
    
    for(int xbin=0; xbin < NBins_X; xbin ++) {
      bkgnd_mass[ybin] -> SetBinContent((xbin), bkgnd->GetBinContent(ybin, xbin)); //note order
    }
    bkgnd_mass[ybin]->Sumw2();
    // bkgnd_mass[ybin]->Draw("pe");
    //TF1 *func = new TF1("func","[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x", Axis_YMin, Axis_YMax);
    //func -> SetParameters(-28900.202091,1544.3,-31.665,0.3172,0.00000305);
    TF1 *func = new TF1("func","landau", Axis_XMin, Axis_XMax);
    if (bkgnd_mass[ybin]->Integral()>10){
      bkgnd_mass[ybin]->Fit(func,"QN");//QN
    } else {
      cout<< " not enough events for bkgnd determination "<<endl;
      func -> SetParameters(3.93055e+02,5.64712e+01,3.26891e+00); 
      //this is for the bins < 25 GeV (for now) the parameters are from the 25-26 gev bin. 
    }
    //bkgnd_mass[xbin]->Draw();
    //QCDBkg_All[xbin] = (TH1D *)Sig_All[xbin]->Clone();
    
    for(int i=1; i<=QCDBkg_All[ybin]->GetNbinsX(); i++) {
      double center = QCDBkg_All[ybin]->GetBinCenter(i);
      
      QCDBkg_All[ybin] -> SetBinContent(i, 0);
      QCDBkg_All[ybin] -> SetBinError(i, 0);
      
      if(center>xmin && center<xmax) {
	double bin_min = QCDBkg_All[ybin]->GetBinLowEdge(i);
	double bin_max = bin_min + QCDBkg_All[ybin]->GetBinWidth(i);
	
	double integral = func->Integral(bin_min, bin_max);
	QCDBkg_All[ybin] -> SetBinContent(i, integral);
	QCDBkg_All[ybin] -> SetBinError(i, TMath::Sqrt(integral));
      }
    } // for all bins
    
    QCDBkg_All[ybin]->Sumw2();
    //  QCDBkg_All[ybin]->Draw();
     //Sig_All[ybin]->Draw();  
  }
  //bkgnd->Draw("colz");
  //TH1D *Sig_All = (TH1D *)gROOT->FindObject("smeared_hZcandMass_CCCC");
  
  //
  // fitter
  //
  Fitter fitter;
  double data_entry_before[NBins], mc_entry_before[NBins], mc_entry_diff[NBins], bkg_entry_before[NBins], mc_error_before[NBins], mc_error_diff[NBins];
  double data_entry_after[NBins], mc_entry_after[NBins], bkg_entry_after[NBins], mc_error_after[NBins];
  double eff[NBins], eff_err[NBins], deff[NBins], deff_err[NBins] ,reff[NBins], reff_err[NBins];
  double chisq1[NBins], chisq2[NBins];
  
  TCanvas *ctemp;
  int npad = 1;
  cout<< " nbins upara now "<<NBins<<endl;
  for(int i=0; i<NBins; i++) {  
    int cbin = 2;
    /*before_mass[i]->Rebin(cbin);
    after_mass[i]->Rebin(cbin);
    diff_mass[i]->Rebin(cbin);
    Sig_All[i]->Rebin(cbin);
    QCDBkg_All[i]->Rebin(cbin);
    */

    if (!(i%2)) {
      myps->NewPage();
      ctemp = new TCanvas("ctemp","ctemp",600,800);
      ctemp->Divide(2,2); 
      npad = 1;
      cout<<"NEWPAGE!!!"<<endl;
    }
    cout<<"=================================Starting number "<<i<<" =============================="<<endl;
    ctemp->cd(npad); 
    // before becomes diff 
    double sb = Sig_All[i]->Integral();
    double bb = QCDBkg_All[i]->Integral();
    cout<<diff_mass[i]->Integral()<<" "<< Sig_All[i]->Integral()<<" "<<QCDBkg_All[i]->Integral()<<endl;
    if(diff_mass[i]->Integral()>1. && Sig_All[i]->Integral()>2. && QCDBkg_All[i]->Integral()>1.) {
      cout<<"b mass "<<diff_mass[i]->Integral()<<endl;
      fitter.Update(diff_mass[i], Sig_All[i], QCDBkg_All[i], xmin, xmax);
      fitter.FitMass();
      fitter.Compare(ctemp);
      fitter.GetDataSignalBkg(data_entry_before[i], mc_entry_before[i], bkg_entry_before[i], mc_error_before[i], chisq1[i]);
    } else {
      diff_mass[i]->SetTitle("no fit");
      diff_mass[i]->Draw("pe");
      //Sig_All[i]->Scale(diff_mass[i]->Integral()/Sig_All[i]->Integral());
      Sig_All[i]->SetLineColor(kRed);
      Sig_All[i]->SetTitle("no fit");
      Sig_All[i]->Draw("hist && same");
      data_entry_before[i]=0.;
      mc_entry_before[i]=0.;
      bkg_entry_before[i]=0.;
      mc_error_before[i]=0.;
      
    }
    npad++;
    ctemp->cd(npad);
    if (Sig_All[i]->Integral()>0){
      Sig_All[i]->Scale(sb/Sig_All[i]->Integral());
    }
    if(QCDBkg_All[i]->Integral()>0){
      QCDBkg_All[i]->Scale(bb/QCDBkg_All[i]->Integral());
    }
    cout<<"---------------------------------------------------------------------------------here i am"<<endl;
    cout<<after_mass[i]->Integral()<<" "<< Sig_All[i]->Integral()<<" "<<QCDBkg_All[i]->Integral()<<endl;
    if(after_mass[i]->Integral()>1. && Sig_All[i]->Integral()>2. && QCDBkg_All[i]->Integral()>1.) {
      cout<<"---------------------------------------------------------------------------------here i am 2"<<endl;
      fitter.Update(after_mass[i], Sig_All[i], QCDBkg_All[i], xmin, xmax);
      fitter.FitMass();
      //ctemp->cd(npad);
      fitter.Compare(ctemp);
      fitter.GetDataSignalBkg(data_entry_after[i], mc_entry_after[i], bkg_entry_after[i], mc_error_after[i], chisq2[i]);
    } else {
      cout<<"-----------------------------------------------------------------------------------here i am 3"<<endl;
      after_mass[i]->SetTitle("no fit");
      after_mass[i]->Draw("pe");
      //Sig_All[i]->Scale(after_mass[i]->Integral()/Sig_All[i]->Integral());
      Sig_All[i]->SetLineColor(kRed);
      Sig_All[i]->SetTitle("no fit");
      Sig_All[i]->Draw("hist && same");
      data_entry_after[i]=0.;
      mc_entry_after[i]=0.;
      bkg_entry_after[i]=0.;
      mc_error_after[i]=0.;
      
    }
    npad++;

  } // for each histogram

  // plot efficiency

 myps->NewPage();
  TCanvas *eff_canvas = new TCanvas("eff","eff",600,600);


  eff_canvas->Divide(1,1);
    eff_canvas->cd(1);

  cout<<"double cccc_mc_entry_after["<<NBins<<"]={";
  for(int i=0; i<NBins; i++) {
    cout<<mc_entry_after[i]<<",";
  }
  cout<<"}"<<endl;
  cout<<"double cccc_mc_error_after["<<NBins<<"]={";
  for(int i=0; i<NBins; i++) {
    cout<<mc_error_after[i]<<",";
  }
  cout<<"}"<<endl;
  cout<<"double cccc_mc_entry_before["<<NBins<<"]={";
  for(int i=0; i<NBins; i++) {
    cout<<mc_entry_before[i]<<",";
  }
  cout<<"}"<<endl;
  cout<<"double cccc_mc_error_before["<<NBins<<"]={";
  for(int i=0; i<NBins; i++) {
    cout<<mc_error_before[i]<<",";
  }
  cout<<"}"<<endl;
  cout<<"double variable[NBins]={";
  for(int i=0; i<NBins; i++) {
    cout<<variable[i]<<",";
  }
  cout<<"}"<<endl;
  
  for(int i=0; i<NBins; i++) {
    if(mc_entry_before[i]>1.&&  mc_entry_after[i]>1.) {  // at least >one entry
      
      eff[i] = mc_entry_after[i]/(mc_entry_before[i] + mc_entry_after[i]);
      eff_err[i] = sqrt(mc_entry_before[i]*mc_entry_before[i]*mc_error_after[i]*mc_error_after[i]+ mc_entry_after[i]*mc_entry_after[i]*mc_error_before[i]*mc_error_before[i])/(mc_entry_before[i]+mc_entry_after[i])/(mc_entry_before[i]+mc_entry_after[i]);
      cout<<"what "<<i << " b "<<mc_entry_before[i]<<" a "<<mc_entry_after[i]<<" eff i "<<eff[i]<<" err i "<<eff_err[i] << " be "<<mc_error_before[i]<<" ae "<<mc_error_after[i]<<endl;    
      
    } else {
      eff[i] = 0;
      eff_err[i] = 0.05;
    }
  }
  
  TF1 *afunc = new TF1("afunc",fitf,-15,15,3);
  afunc->SetParameters(-1.0,0.010,0.74);
  
  //  TF1 *efffit2 = new TF1("efffit2","0.5 * [2] * (1. + TMath::Erf((x-[0])/(sqrt(2)*[1])))*(1. + TMath::Erf((x-[4])/(sqrt(2)*[3])))",15,55 );
  //  efffit2->SetParameters(23.,2.0,0.4,2.0,20.);
  TGraphErrors *ge = new TGraphErrors(NBins, variable, eff, variable_err, eff_err);
  ge->GetYaxis()->SetRangeUser(0.4,0.9);
  ge->SetMarkerColor(kRed);
  ge->SetMarkerSize(2);
  ge->SetLineColor(kRed);
  ge->GetXaxis()->SetTitle("Electron U_{||} [GeV]");
  ge->GetYaxis()->SetTitle("Efficiency");
  ge->GetYaxis()->SetTitleOffset(1.4);
  ge->SetTitle("Z->ee Candidates, U_{||} Eff."); 
  
  ge->Fit("afunc","R");
  
  TF1 *apol1 = new TF1("apol1","[0] + [1]*x", -20. ,0.);
  ge -> Draw("AP");
  //  ge->Fit("apol1","R");
  // apol1->Draw("same");
  TF1 *bpol1 = new TF1("bpol1","[0] + [1]*x", 0. ,20.);
  // ge->Fit("bpol1","R");
  //bpol1->Draw("same");
  

  // eff_canvas->Update();
  
  // eff_canvas->cd(2);
  eff_canvas->SaveAs("upara_out_new.eps");


  for(int i=0; i<NBins; i++) {
    if(data_entry_before[i]>1. && data_entry_after[i]>1.) {// at least one entry
      cout<<"what 2 "<<data_entry_before[i]<<" "<<data_entry_after[i]<< " "<<i<<endl;
      deff[i] = data_entry_after[i]/(data_entry_before[i]+data_entry_after[i]);
      deff_err[i] = sqrt(data_entry_before[i]*data_entry_before[i]*mc_error_after[i]*mc_error_after[i]
			 + data_entry_after[i]*data_entry_after[i]*mc_error_before[i]*mc_error_before[i])
	/(data_entry_before[i]+data_entry_after[i])/(data_entry_before[i]+data_entry_after[i]);
      //for this you really should have plain binominal errors (no background subtraction here)
    } else {
      deff[i] = 0;
      deff_err[i] = 0.05;
    }
  }
  
  
  TGraphErrors *de = new TGraphErrors(NBins, variable, deff, variable_err, deff_err);
  de->GetYaxis()->SetRangeUser(0.4,0.9);
  de->SetMarkerColor(kBlue);
  de->SetMarkerSize(2);
  de->SetLineColor(kBlue);
  //de->Fit("efffit2","RME");
  //de -> Draw("SAME");
  
  //eff_canvas->Update();
  
  //now get full MC "answer":
  /*
  TFile *data=new TFile("/rooms/porcelain/tandeen/WMASS/output/FULL/Zee/UPARAEFF/result_MCzee_upara_1.root");
  gDirectory->cd("ZCand_Hist");
  TH1D *before2 = (TH1D *)gROOT->FindObject("ZCandUPara_NoCuts");
  TH1D *after2 = (TH1D *)gROOT->FindObject("ZCandUPara_BothWithGoodSpatialMatch_IsoHMxCut");  
  before2->Rebin(8);
  after2->Rebin(8);
  
  TGraphAsymmErrors *effb = new TGraphAsymmErrors();
  effb->BayesDivide(after2,before2,""); //"debug"
  // effb->Fit("pol1","","",0,15);
  
  effb->Draw("same");
  effb->Fit("pol1","","",-20,0);
  double thep0 = pol1->GetParameter(0);
  double thep1 = pol1->GetParameter(1);
  cout<<"p0 "<<thep0<<" p1 "<<thep0<<endl;
  effb->Fit("pol1","","",0,20);
  //TF1 *cpol1 = new TF1("cpol1","[0] + [1]*x", -20. ,0.);
  //cout<<"cpol"<<endl;
  //effb->Fit("cpol1","R");
  //cpol1->Draw("same");
  TF1 *dpol1 = new TF1("dpol1","[0] + [1]*x", -20. , 0.);
  dpol1->SetParameters(thep0,thep1);
  //cout<<"dpol"<<endl;
  //effb->Fit("dpol1","R");
  dpol1->Draw("same");

  //effb->SetTitle(ZCandUPara_BothWithGoodSpatialMatch_IsoHMxCut->GetTitle());
  //effb->GetXaxis()->SetTitle("trk deteta");
  */
  /*
  eff_canvas->cd(3);
  
  for(int i=0; i<NBins; i++) {
    if(eff[i]>0. && deff[i]>0.) {// at least one entry
      reff[i] = eff[i]/deff[i]; 
      //reff_err[i] = sqrt(data_entry_before[i]*data_entry_before[i]*mc_error_after[i]*mc_error_after[i]+ data_entry_after[i]*data_entry_after[i]*mc_error_before[i]*mc_error_before[i])/(data_entry_before[i]+data_entry_after[i])/(data_entry_before[i]+data_entry_after[i]);
    } else {
      reff[i] = 1.0;
      //reff_err[i] = 0.1;
    }
  }

  TGraphErrors *erat = new TGraphErrors(NBins, variable, reff, variable_err, eff_err);
  erat->GetXaxis()->SetRangeUser(10,70);
  erat->SetMarkerColor(kRed);
  erat->SetMarkerSize(2);
  erat->SetLineColor(kRed);
  erat -> Draw("AP");
  */


  eff_canvas->Update();

  myps->NewPage();
  TCanvas *chi_canvas = new TCanvas("eff","eff",600,800);
  

  chi_canvas->Divide(1,2);
  chi_canvas->cd(1);
  
  TGraph *chi1 = new TGraph(NBins, variable, chisq1);
  // de->GetYaxis()->SetRangeUser(0.4,0.9);
  //de->SetMarkerColor(kBlue);
  //de->SetMarkerSize(2);
  //de->SetLineColor(kBlue);
  //de->Fit("efffit2","RME");
  chi1-> Draw("A*");
   

  chi_canvas->cd(2);

  TGraph *chi2 = new TGraphErrors(NBins, variable, chisq2);
  //de->GetYaxis()->SetRangeUser(0.4,0.9);
  
  //de->SetMarkerColor(kBlue);
  //de->SetMarkerSize(2);
  //de->SetLineColor(kBlue);
  //de->Fit("efffit2","RME");
  chi2 -> Draw("A*");
  
  chi_canvas->Update();


  myps->Close();
}
