// delta Uparallel dependence on the instantaneous luminosity
// I have to use TH1F in order to use it in wz_epmcs
// but the real plot should be made with TGraphErrors with x[n], y[n], ex[n], ey[n]

{
  const int n_Lumi_bins = 10;
  float UParaCorr_Lumi_bins[n_Lumi_bins+1] = {0., 0.225, 0.45, 0.6, 0.75, 0.9, 1.075, 1.325, 1.65, 2.225, 5.};
  
  TH1F *UParaCorr_V_Lumi = new TH1F("UParaCorr_V_Lumi","Uparallel correction vs luminosity", n_Lumi_bins, UParaCorr_Lumi_bins);
  
  Int_t n = 10;
  Float_t x[n]  = {0.1711, 0.359,  0.5242, 0.6702, 0.816, 0.986, 1.188, 1.473, 1.864, 2.578};
  Float_t y[n]  = {0.00662, 0.00766, 0.00773, 0.00842, 0.00953, 0.00891, 0.01063, 0.01102, 0.01148, 0.01546};

  Float_t ex[n] = {};
  Float_t ey[n] = {0.00057, 0.00023, 0.00028, 0.00028, 0.00042, 0.0004, 0.00045, 0.00052, 0.00086, 0.00189};
 
  for(int i=1; i<=n; i++) {
    UParaCorr_V_Lumi->SetBinContent(i, y[i-1]);
    UParaCorr_V_Lumi->SetBinError(i, ey[i-1]);
  }
  UParaCorr_V_Lumi->Draw();
}
