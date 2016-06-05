// delta Uparallel dependence on uparallel
// I have to use TH1F in order to use it in wz_epmcs
// but the real plot should be made with TGraphErrors with x[n], y[n], ex[n], ey[n]

{
  const int n_UPara_bins = 10;
  float UParaCorr_UPara_bins[n_UPara_bins+1] = {-30., -10., -5., -3., -1.5, -0.25, 1., 2.5, 4.75, 14.75, 30.};
  
  TH1F *UParaCorr_V_UPara = new TH1F("UParaCorr_V_UPara","Uparallel correction vs u_{#parallel}", n_UPara_bins, UParaCorr_UPara_bins);
  
  Int_t n = 10;
  Float_t x[n]  = {-11.67, -6.93, -3.92, -2.22, -0.85, 0.36, 1.72, 3.50, 7.36, 11.89};
  Float_t y[n]  = {0.00964, 0.00858, 0.00769, 0.00727, 0.00709, 0.00816, 0.00863, 0.00939, 0.01272, 0.0165};
  for(int i=0; i<n; i++) y[i] -= 0.732 * 0.0031;

  Float_t ex[n] = {};
  Float_t ey[n] = {0.00075, 0.00033, 0.00031, 0.00029, 0.00030, 0.00034, 0.00033, 0.00035, 0.00047, 0.0016};
 
  for(int i=1; i<=n; i++) {
    UParaCorr_V_UPara->SetBinContent(i, y[i-1]);
    UParaCorr_V_UPara->SetBinError(i, ey[i-1]);
  }
  UParaCorr_V_UPara->Draw();
}
