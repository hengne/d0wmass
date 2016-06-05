

{
  //d0Style->cd();

  TFile* flos = new TFile("rootfiles/effratio_npnm_loose_setlumi_effrange_nout_ec_tg.root");  
  TFile* ftig = new TFile("rootfiles/effratio_npnm_tight_setlumi_effrange_nout_ec_tg.root");  
  TFile* fout = new TFile("rootfiles/compare_npnm_tight_loose_setlumi_effrange_nout_ec_tg.root", "recreate");

  TH2D* hlos = (TH2D*)flos->Get("hrt_eff_2d");
  TH2D* htig = (TH2D*)ftig->Get("hrt_eff_2d");

  TH1D* hall = (TH1D*)hlos->Clone("hall");
  hall->Multiply(htig);


  hall->GetXaxis()->SetTitle("SET (GeV)");
  hall->GetYaxis()->SetTitle("InstLumi");
  hall->GetXaxis()->SetTitleOffset(1.5);
  hall->GetYaxis()->SetTitleOffset(1.5);

  //TF2* fcall = new TF2("fcall", "[0]*(1+[1]*x+[3]*x**2+[5]*x**3+[7]*x**4+[9]*x**5)*(1+[2]*y+[4]*y**2+[6]*y**3+[8]*y**4+[10]*y**5)", 0, 300, 0,10); 
  //fcall->SetParameters(1., 0,0,0,0,0, 0,0,0,0,0);
  TF2* fcall = new TF2("fcall", "[0]*(1+[1]*x+[3]*x**2+[5]*x**3)*(1+[2]*y+[4]*y**2+[6]*y**3)", 0, 300, 0,10); 
  fcall->SetParameters(1., 0,0,0,0,0,0);

  TCanvas* call = new TCanvas("call");
  hall->Sumw2();
  hall->Fit(fcall, "R 0");

  TH2D* hfcall = (TH2D*)hall->Clone("hfcall");
  hfcall->Reset();
  hfcall->SetLineColor(kRed);
  
  hall->GetZaxis()->SetRangeUser(0.6, 1.2);
  hfcall->GetZaxis()->SetRangeUser(0.6, 1.2);

  for (int i=0; i<(int)hfcall->GetNbinsX(); i++){
    double binx = hfcall->GetXaxis()->GetBinCenter(i+1);
    for (int j=0; j<(int)hfcall->GetNbinsY(); j++){
      double biny = hfcall->GetYaxis()->GetBinCenter(j+1);
      double content = fcall->Eval(binx, biny);
      hfcall->SetBinContent(i+1, j+1, content);
    }
  }

  hall->Draw("lego err");
  hfcall->Draw("same surf");
  //hall->Sumw2();
  hfcall->Sumw2();
  double chi2ndf = hall->Chi2Test(hfcall, "WW CHI2/NDF");
  std::cout << "Ch2/Ndf = " << chi2ndf << std::endl; 


  TH2D* hratio = (TH2D*)hfcall->Clone("hratio");
  hratio->Divide(hall);

  TCanvas* c3 = new TCanvas("c3");
  hratio->Draw("colz");
 
  double max = fcall->GetMaximum();
  std::cout << "max = "<< max << std::endl; 


  std::cout << "SETEffDataHackSETDepParameters: 1. " ;
  for (int i=1; i<=6; i=i+2){
    std::cout << fcall->GetParameter(i) << " " ;
  }
  std::cout << std::endl;

  std::cout << "SETEffDataHackLumiDepParameters: 1. " ;
  for (int i=2; i<=6; i=i+2){
    std::cout << fcall->GetParameter(i) << " " ;
  }
  std::cout << std::endl;


  fcall->SetParameter(0,1.);

  //-2.28234e-06 -3.59438e-06 1.99387e-09
  // -0.0121579 0.00450792 -0.00093395
  double maxbin = hall->GetMaximum();
  TF2* fcall2 = new TF2("fcall2", "[0]*(1+[1]*x+[3]*x**2+[5]*x**3)*(1+[2]*y+[4]*y**2+[6]*y**3)", 0, 300, 0,10);
  fcall2->SetParameters(1,-2.28234e-06, -0.0121579, -3.59438e-06, 0.00450792, 1.99387e-09, -0.00093395);

  for (int i=1; i<7; i++){
    fcall2->FixParameter(i, fcall2->GetParameter(i));
  }
  
  hall->Fit(fcall2, "R 0"); 

  TH2D* hfcall2 = (TH2D*)hall->Clone("hfcall2");
  hfcall2->Reset();
  hfcall2->SetLineColor(kRed);

  hfcall2->GetZaxis()->SetRangeUser(0.6, 1.2);

  for (int i=0; i<(int)hfcall2->GetNbinsX(); i++){
    double binx = hfcall2->GetXaxis()->GetBinCenter(i+1);
    for (int j=0; j<(int)hfcall2->GetNbinsY(); j++){
      double biny = hfcall2->GetYaxis()->GetBinCenter(j+1);
      double content = fcall2->Eval(binx, biny);
      hfcall2->SetBinContent(i+1, j+1, content);
    }
  }
  
  double maxfcall2 = fcall2->GetMaximum();
  std::cout << "max_fcall2 = " << maxfcall2 << std::endl;

  hfcall2->Sumw2();
  double chi2ndf2 = hall->Chi2Test(hfcall2, "WW CHI2/NDF");
  std::cout << "Ch2/Ndf 2 = " << chi2ndf2 << std::endl;
   
  TH2D* hratio2 = (TH2D*)hfcall2->Clone("hratio2");
  hratio2->Divide(hall);
  TCanvas* c5 = new TCanvas("c5");
  hratio2->Draw("colz");
/*
  fout->cd();
  hlos->Write("hrt_loose_2d");
  htig->Write("hrt_tight_2d");
  hall->Write("hrt_all_2d");
  //fout->Close();

  TF1* fcall = new TF1("fcall", "pol3", 0, 300);
  fcall->SetLineColor(kBlue);

  hall->Fit(fcall, "R");

  double par[4];
  for (int i=0; i<=3; i++){
    par[i] = fcall->GetParameter(i);
  }  

  std::cout << "SETEffDataHackSETDepParameters: " ;
  for (int i=0; i<=3; i++){
    std::cout << par[i]/par[0] << " " ;
  }
  std::cout << std::endl;


  TCanvas* c1 = new TCanvas("c1");
  hlos->Draw();
  htig->Draw("same");
  hall->Draw("same");
  lg->Draw("same");
*/
}
