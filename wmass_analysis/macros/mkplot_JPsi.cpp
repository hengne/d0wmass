void mkplot_JPsi() {
  gROOT->LoadMacro("fit_gaus_linear.cpp");

  TFile *file = new TFile("jpsiana.root");
  TH1F *hmass[10], *hvar[10];
  char massname[50], variablename[50];

  char *histname = "hmass_jpsi_pt[";
  char *varname = "hpt_jpsi_bin[";

  TCanvas *canv = new TCanvas("canv", "Canvas", 100, 180, 1050, 750);
  canv->Divide(5,2);

  // variables for TGraph
  double mean_value[10], mean_error[10], varvalue[10], varvalue_error[10];

  for(int ibin=0; ibin<10; ibin++) {
    sprintf(massname, "%s%d%s", histname, ibin, "]");
    sprintf(variablename, "%s%d%s", varname, ibin, "]");

    canv->cd(ibin+1);
    
    hmass[ibin] = (TH1F *)gROOT->FindObject(massname);
    hvar[ibin] = (TH1F *)gROOT->FindObject(variablename);
    varvalue[ibin] = hvar[ibin]->GetMean();
    varvalue_error[ibin] = 0.;

    // use the first bin content as the initial value
    double FirstBincontent = hmass[ibin]->GetBinContent(0);
    
    TF1 *fitfunc = new TF1("GausLinearFit", GausLinearFit, 2.8, 3.2, 5);
    fitfunc->SetParameters(FirstBincontent, 3.1, 0.2, 1., FirstBincontent);        
    hmass[ibin] -> Fit("GausLinearFit");

    //Get the fitted function and fitting variables
    double p0 =  fitfunc -> GetParameter(0);
    double p1 =  fitfunc -> GetParameter(1);
    double p2 =  fitfunc -> GetParameter(2);
    double p3 =  fitfunc -> GetParameter(3);
    double p4 =  fitfunc -> GetParameter(4);
    double p1err = fitfunc -> GetParError(1);

    mean_value[ibin] = p1-3.096916;   // subtract J/Psi mass
    mean_error[ibin] = p1err;

    if(p1err>1.) mean_error[ibin] = 0.;

    delete fitfunc;  
    
  } // for 10 histograms


  // make graph
  TCanvas *canv_gr = new TCanvas("canv_gr", "Canvas", 104, 173, 725, 513);
  TGraphErrors *gr = new TGraphErrors(10, varvalue, mean_value, varvalue_error, mean_error);

  for(int i=0; i<10; i++) 
    cout<<"X value = "<<varvalue[i]<<", Y value (J/Psi mass) = "<<mean_value[i]<<" +- "<<mean_error[i]<<endl;

  gr -> SetTitle(0);
  gr->GetXaxis()->SetTitle("X axis");
  gr->GetYaxis()->SetTitle("#Delta M_{#mu#mu} (GeV)");
  gr -> Draw("AP");
  canv_gr->Update();
}


