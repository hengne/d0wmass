// delta Uparallel dependence on the instantaneous luminosity
// I have to use TH1F in order to use it in wz_epmcs
// but the real plot should be made with TGraphErrors with x[n], y[n], ex[n], ey[n]

{
  const int n_Lumi_bins = 10;
  float UParaCorr_Lumi_bins[n_Lumi_bins+1] = {0., 0.225, 0.45, 0.6, 0.75, 0.9, 1.075, 1.325, 1.65, 2.225, 5.};
  
  TH1F *UParaCorr_V_Lumi = new TH1F("UParaCorr_V_Lumi","Uparallel correction vs luminosity", n_Lumi_bins, UParaCorr_Lumi_bins);
  
  Int_t n = 10;
  Float_t x[n]  = {-11.76, -6.98, -3.9, -2.2, -0.86, 0.37, 1.71, 3.51, 7.27, 12.25};
  Float_t y[n]  = {0.00457, 0.00647, 0.00711, 0.00762, 0.0076, 0.00868, 0.00914, 0.00971, 0.01022, 0.01251};
  
  Float_t ex[n] = {};
  Float_t ey[n] = {0.00094, 0.00041, 0.00033, 0.00036, 0.00035, 0.0004, 0.00037, 0.00034, 0.00031, 0.00042};
 
  for(int i=1; i<=n; i++) {
    UParaCorr_V_Lumi->SetBinContent(i, y[i-1]);
    UParaCorr_V_Lumi->SetBinError(i, ey[i-1]);
  }
  UParaCorr_V_Lumi->Draw();
}
