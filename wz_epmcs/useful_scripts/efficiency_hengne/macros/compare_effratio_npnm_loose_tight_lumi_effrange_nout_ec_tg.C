

{
  d0Style->cd();

  TFile* flos = new TFile("rootfiles/effratio_npnm_loose_lumi_effrange_nout_ec_tg.root");  
  TFile* ftig = new TFile("rootfiles/effratio_npnm_tight_lumi_effrange_nout_ec_tg.root");  
  TFile* fout = new TFile("rootfiles/compare_npnm_tight_loose_lumi_effrange_nout_ec_tg.root", "recreate");

  TH1D* hlos = (TH1D*)flos->Get("hratio_dt_mc");
  TH1D* htig = (TH1D*)ftig->Get("hratio_dt_mc");

  TH1D* hall = (TH1D*)hlos->Clone("hall");
  hall->Multiply(htig);

  hlos->SetLineColor(kRed);
  htig->SetLineColor(kMagenta);
  hall->SetLineColor(kBlue);
  hlos->SetMarkerColor(kRed);
  htig->SetMarkerColor(kMagenta);
  hall->SetMarkerColor(kBlue);
  hlos->SetMarkerStyle(20);
  htig->SetMarkerStyle(20);
  hall->SetMarkerStyle(20);
  hlos->SetMarkerSize(1);
  htig->SetMarkerSize(1);
  hall->SetMarkerSize(1);

  hall->GetXaxis()->SetTitle("InstLumi");
  hall->GetYaxis()->SetTitle("Eff Ratio");

  TLegend* lg = new TLegend(0.6,0.6,0.9,0.9);
  lg->AddEntry(hlos, "Loose", "pl");
  lg->AddEntry(htig, "Tight", "pl");
  lg->AddEntry(hall, "Loose*Tight", "pl");


  fout->cd();
  hlos->Write("hratio_loose_pt");
  htig->Write("hratio_tight_pt");
  hall->Write("hratio_pt");
  //fout->Close();

  TF1* fcall = new TF1("fcall", "pol3", 0, 10);
  fcall->SetLineColor(kBlue);

  hall->Fit(fcall, "R");

  double par[4];
  for (int i=0; i<=3; i++){
    par[i] = fcall->GetParameter(i);
  }  

  std::cout << "SETEffDataHackLumiDepParameters: " ;
  for (int i=0; i<=3; i++){
    std::cout << par[i]/par[0] << " " ;
  }
  std::cout << std::endl;
  TCanvas* c1 = new TCanvas("c1");
  hlos->Draw();
  htig->Draw("same");
  hall->Draw("same");
  lg->Draw("same");

}
