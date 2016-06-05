
{
  d0Style->cd();

  TFile* fdt = new TFile("rootfiles/hists_data_trig_pt_effrange_nout_ec.root");
  TFile* fout = new TFile("rootfiles/eff_data_trig_pt_effrange_nout_ec.root", "recreate");

  // define hists
  // trigflg: 5 -  E1_SHT25&&!E1_SHT27
  //          6 -  E1_SHT25&& E1_SHT27
  //          7 - !E1_SHT25&& E1_SHT27
  TH1D* hnp[3];
  TH1D* hnm[3];
  TH1D* heff[3];
 
  hnp[0]= (TH1D*)fdt->Get("hnp5");
  hnm[0]= (TH1D*)fdt->Get("hnm5");
  hnp[1]= (TH1D*)fdt->Get("hnp6");
  hnm[1]= (TH1D*)fdt->Get("hnm6");
  hnp[2]= (TH1D*)fdt->Get("hnp7");
  hnm[2]= (TH1D*)fdt->Get("hnm7");
  
  heff[0] = (TH1D*)hnp[0]->Clone("heff5");
  heff[1] = (TH1D*)hnp[1]->Clone("heff6");
  heff[2] = (TH1D*)hnp[2]->Clone("heff7");

  heff[0]->Reset();
  heff[1]->Reset();
  heff[2]->Reset();

  int nbins = hnp[0]->GetNbinsX();

  // calculate eff and eff_err
  for (int j=0; j<3; j++){
    for (int i=0; i<=nbins; i++){
      double np, nm, np_err, nm_err, eff, eff_err;
      np = hnp[j]->GetBinContent(i);
      np_err = hnp[j]->GetBinError(i);
      nm = hnm[j]->GetBinContent(i);
      nm_err = hnm[j]->GetBinError(i);
      if (np+nm!=0) eff = np/(np+nm);
      else eff = 0.;
      if (np+nm!=0) eff_err = sqrt( pow(np_err,2.)*pow(nm,2.)/pow((np+nm), 4.) + pow(nm_err,2.)*pow(np,2.)/pow((np+nm), 4.) );
      else eff_err = 0.;
      heff[j]->SetBinContent(i, eff);
      heff[j]->SetBinError(i, eff_err);
    }
  }

  heff[0]->SetLineColor(kRed);
  heff[0]->SetMarkerColor(kRed);
  heff[0]->SetMarkerStyle(20);
  heff[0]->SetMarkerSize(1);

  heff[1]->SetLineColor(kBlue);
  heff[1]->SetMarkerColor(kBlue);
  heff[1]->SetMarkerStyle(20);
  heff[1]->SetMarkerSize(1);


  heff[2]->SetLineColor(kGreen+3);
  heff[2]->SetMarkerColor(kGreen+3);
  heff[2]->SetMarkerStyle(20);
  heff[2]->SetMarkerSize(1);



  heff[0]->GetXaxis()->SetTitle("ElecPt (GeV)");
  heff[0]->GetYaxis()->SetTitle("Eff");
  heff[0]->GetYaxis()->SetRangeUser(0.6, 1.1);
  heff[1]->GetXaxis()->SetTitle("ElecPt (GeV)");
  heff[1]->GetYaxis()->SetTitle("Eff");
  heff[1]->GetYaxis()->SetRangeUser(0.6, 1.1);
  heff[2]->GetXaxis()->SetTitle("ElecPt (GeV)");
  heff[2]->GetYaxis()->SetTitle("Eff");
  heff[2]->GetYaxis()->SetRangeUser(0.6, 1.1);

  // do fits
  TF1* fceff[3];
  fceff[0] = new TF1("fceff0","0.5 * [2] * (1. + TMath::Erf((x-[0])/(sqrt(2)*[1])))*(1. + TMath::Erf((x-[4])/(sqrt(2)*[3])))", 25, 100);
  fceff[1] = new TF1("fceff1","0.5 * [2] * (1. + TMath::Erf((x-[0])/(sqrt(2)*[1])))*(1. + TMath::Erf((x-[4])/(sqrt(2)*[3])))", 25, 100);
  fceff[2] = new TF1("fceff2","0.5 * [2] * (1. + TMath::Erf((x-[0])/(sqrt(2)*[1])))*(1. + TMath::Erf((x-[4])/(sqrt(2)*[3])))", 25, 100);

  fceff[0]->SetNpx(300);
  fceff[1]->SetNpx(300);
  fceff[2]->SetNpx(300);

  fceff[0]->SetParameters(24.,0.6.,0.5.,18.9.,-7.);
  fceff[1]->SetParameters(24.,0.6.,0.5.,18.9.,-7.);
  fceff[2]->SetParameters(24.,0.6.,0.5.,18.9.,-7.);
  
  fceff[0]->SetLineColor(kRed);
  fceff[1]->SetLineColor(kBlue);
  fceff[2]->SetLineColor(kGreen+3);

  heff[0]->Fit(fceff[0], "R");
  heff[1]->Fit(fceff[1], "R");
  heff[2]->Fit(fceff[2], "R");

  // print parameters 
  std::cout << "TrigEff_P0:   23.61, 20.74, 23.74, 24.91, " 
       << fceff[0]->GetParameter(0) << ", " << fceff[1]->GetParameter(0) << ", "<< fceff[2]->GetParameter(0) << std::endl;
  std::cout << "TrigEff_P1:   2.208, 0.5023, 1.266, 1.61, "
       << fceff[0]->GetParameter(1) << ", " << fceff[1]->GetParameter(1) << ", "<< fceff[2]->GetParameter(1) << std::endl;
  std::cout << "TrigEff_P2:   2.273, 0.4874, 1.261, 2.306, "
       << fceff[0]->GetParameter(2) << ", " << fceff[1]->GetParameter(2) << ", "<< fceff[2]->GetParameter(2) << std::endl;
  std::cout << "TrigEff_P3:   1795, 23.65, 635.7, 970.5, "
       << fceff[0]->GetParameter(3) << ", " << fceff[1]->GetParameter(3) << ", "<< fceff[2]->GetParameter(3) << std::endl;
  std::cout << "TrigEff_P4:   1455, -7.366, 222, 821.8, "
       << fceff[0]->GetParameter(4) << ", " << fceff[1]->GetParameter(4) << ", "<< fceff[2]->GetParameter(4) << std::endl;


  TLegend* lg = new TLegend(0.6, 0.6, 0.9, 0.9);
  lg->AddEntry(heff[0], " E1_SHT25_v15", "pl");
  lg->AddEntry(heff[1], " E1_SHT25_v16", "pl");
  lg->AddEntry(heff[2], " E1_SHT27", "pl");


  
  TCanvas* c0 = new TCanvas("c0");
  heff[0]->Draw("");
  heff[1]->Draw("same");
  heff[2]->Draw("same");
  lg->Draw("same"); 
 
  fout->cd();
  heff[0]->Write();
  heff[1]->Write();
  heff[2]->Write();
}
