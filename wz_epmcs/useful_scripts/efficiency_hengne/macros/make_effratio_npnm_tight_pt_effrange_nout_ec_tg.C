
{
  d0Style->cd();

  TFile* fdt = new TFile("rootfiles/fiteff_npnm_data_tight_pt_effrange_nout_ec_tg.root");
  TFile* fmc = new TFile("rootfiles/effhists_npnm_fullmc_tight_pt_effrange_nout_ec_tg.root");
  TFile* fout = new TFile("rootfiles/effratio_npnm_tight_pt_effrange_nout_ec_tg.root", "recreate");

  TH1D* hmc_np = (TH1D*)fmc->Get("hnp");
  TH1D* hmc_nm = (TH1D*)fmc->Get("hnm");

  TH1D* hdt_np = (TH1D*)fdt->Get("hnp");
  TH1D* hdt_nm = (TH1D*)fdt->Get("hnm");
  
  TH1D* hmc_eff = (TH1D*)hmc_np->Clone("hmc_eff");
  TH1D* hdt_eff = (TH1D*)hdt_np->Clone("hdt_eff");

  hmc_eff->Reset();
  hdt_eff->Reset();

  int nbins = hmc_eff->GetNbinsX();

  // calculate eff and eff_err
  for (int i=0; i<=nbins; i++){
    double np, nm, np_err, nm_err, eff, eff_err;
    // mc
    np = hmc_np->GetBinContent(i);
    np_err = hmc_np->GetBinError(i);
    nm = hmc_nm->GetBinContent(i);
    nm_err = hmc_nm->GetBinError(i);
    if (np+nm!=0) eff = np/(np+nm);
    else eff = 0.;
    if (np+nm!=0) eff_err = sqrt( pow(np_err,2.)*pow(nm,2.)/pow((np+nm), 4.) + pow(nm_err,2.)*pow(np,2.)/pow((np+nm), 4.) );
    else eff_err = 0.;
    hmc_eff->SetBinContent(i, eff);
    hmc_eff->SetBinError(i, eff_err);
    // dt
    np = hdt_np->GetBinContent(i);
    np_err = hdt_np->GetBinError(i);
    nm = hdt_nm->GetBinContent(i);
    nm_err = hdt_nm->GetBinError(i);
    if (np+nm!=0) eff = np/(np+nm);
    else eff = 0.;
    if (np+nm!=0) eff_err = sqrt( pow(np_err,2.)*pow(nm,2.)/pow((np+nm), 4.) + pow(nm_err,2.)*pow(np,2.)/pow((np+nm), 4.) );
    else eff_err = 0.;
    hdt_eff->SetBinContent(i, eff);
    hdt_eff->SetBinError(i, eff_err);
  }

  TH1D* hratio_dt_mc = (TH1D*)hdt_eff->Clone("hratio_dt_mc");
  hratio_dt_mc->Divide(hmc_eff);
  hratio_dt_mc->SetMarkerColor(kBlack);
  hratio_dt_mc->SetLineColor(kBlack);
  hratio_dt_mc->SetMarkerStyle(20);
  hratio_dt_mc->SetMarkerSize(1);
  
   
 
  hdt_eff->SetLineColor(kRed);
  hdt_eff->SetMarkerColor(kRed);
  hdt_eff->SetMarkerStyle(20);
  hdt_eff->SetMarkerSize(1);

  hmc_eff->SetLineColor(kBlue);
  hmc_eff->SetMarkerColor(kBlue);
  hmc_eff->SetMarkerStyle(20);
  hmc_eff->SetMarkerSize(1);

  TF1* fratio_dt_mc = new TF1("fratio_dt_mc", "pol19", 25, 70);

  TCanvas* c0 = new TCanvas("c0");

  //hratio_dt_mc->Fit(fratio_dt_mc, "R");

  hratio_dt_mc->GetXaxis()->SetTitle("ElecPt (GeV)");
  hratio_dt_mc->GetYaxis()->SetTitle("Eff");
  hratio_dt_mc->GetYaxis()->SetRangeUser(0.6, 1.1);
  TLegend* lg = new TLegend(0.6, 0.6, 0.9, 0.9);
  lg->AddEntry(hdt_eff, "Eff Data", "pl");
  lg->AddEntry(hmc_eff, "Eff FullMC", "pl");
  lg->AddEntry(hratio_dt_mc, "Ratio Data/FullMC", "pl");
  
  hratio_dt_mc->Draw();
  hdt_eff->Draw("same");
  hmc_eff->Draw("same");
  lg->Draw("same"); 
 
  fratio_dt_mc->SetLineColor(kBlue);
  fout->cd();
  hratio_dt_mc->Write();
  hdt_eff->Write();
  hmc_eff->Write();
}
