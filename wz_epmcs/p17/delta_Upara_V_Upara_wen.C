// delta Uparallel dependence on uparallel itself
// I have to use TH1F in order to use it in wz_epmcs
// but the real plot should be made with TGraphErrors with x[n], y[n], ex[n], ey[n]

{
  const int n_UPara_bins = 10;
  float UParaCorr_UPara_bins[n_UPara_bins+1] = {-30., -10., -5., -3., -1.5, -0.25, 1., 2.5, 4.75, 14.75, 30.};

  TH1F *UParaCorr_V_UPara = new TH1F("UParaCorr_V_UPara","Uparallel correction vs u_{#parallel}", n_UPara_bins, UParaCorr_UPara_bins);
  
  Int_t n = 10;
  Float_t x[n]  = {-11.76, -6.98, -3.9, -2.2, -0.86, 0.37, 1.71, 3.51, 7.27, 12.25};
  Float_t y[n]  = {11.57, 9.38, 8.31, 7.61, 7.05, 7.76, 8.62, 10.95, 14.08, 18.};
  
  for(int i=0; i<n; i++) y[i] = y[i]*0.001 - 0.00254 * 1.288;
  
  Float_t ex[n] = {};
  Float_t ey[n] = {0.94, 0.36, 0.34, 0.27, 0.26, 0.28, 0.31, 0.45, 0.57, 1.2};
  for(int i=0; i<n; i++) ey[i] = ey[i]*0.001;
 
  for(int i=1; i<=n; i++) {
    UParaCorr_V_UPara->SetBinContent(i, y[i-1]);
    UParaCorr_V_UPara->SetBinError(i, ey[i-1]);
  }
  UParaCorr_V_UPara->Draw();
}
