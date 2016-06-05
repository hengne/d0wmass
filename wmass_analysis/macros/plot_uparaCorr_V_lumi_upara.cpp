// pol0
Double_t fitf(Double_t *x, Double_t *par) {
  return par[0];
}

void plot_uparaCorr_V_lumi_upara() {
  TFile *f = new TFile("data_wen_cell_noWPtCut_newDataSet.root");
  gDirectory->cd("UE_Hist");

  char name[50];
  const Int_t n_Lumi_Bins = 10;
  double Lumi_Average[n_Lumi_Bins], Lumi_Average_Err[n_Lumi_Bins];
  double UParaCorr_Lumi[n_Lumi_Bins], UParaCorr_Lumi_Err[n_Lumi_Bins];

  const Int_t n_UPara_Bins = 13;
  double UPara_Average[n_UPara_Bins], UPara_Average_Err[n_UPara_Bins];
  double UParaCorr_UPara[n_UPara_Bins], UParaCorr_UPara_Err[n_UPara_Bins];

  for(int i=0; i<n_Lumi_Bins; i++) {
    sprintf(name, "%s%d", "InstLumi_", i);
    TH1F *hLumi = gROOT->FindObject(name);
    Lumi_Average[i] = hLumi->GetMean();
    Lumi_Average_Err[i] = 0.;
    delete hLumi;

    // sum5towEt vs deltaPhi
    sprintf(name, "%s%d", "sum5towEt_Lumi_", i);
    TH1F *hLumi_Upara = gROOT->FindObject(name);
    TF1 *fitfunc = new TF1("fitf", fitf, 0.2, 0.4, 1);
    hLumi_Upara->Fit("fitf", "r");

    double param, param_err;
    fitfunc->GetParameters(&param);
    param_err = fitfunc->GetParError(0);
    
    UParaCorr_Lumi[i] = param;
    UParaCorr_Lumi_Err[i] = param_err;

    delete fitfunc;
    delete hLumi_Upara;
  }

 for(int i=0; i<n_UPara_Bins; i++) {
    sprintf(name, "%s%d", "UPara_", i);
    TH1F *hUPara = gROOT->FindObject(name);
    UPara_Average[i] = hUPara->GetMean();
    UPara_Average_Err[i] = 0.;
    delete hUPara;

    // sum5towEt vs deltaPhi
    sprintf(name, "%s%d", "sum5towEt_UPara_", i);
    TH1F *hUPara_Upara = gROOT->FindObject(name);
    TF1 *fitfunc = new TF1("fitf", fitf, 0.2, 0.4, 1);
    hUPara_Upara->Fit("fitf", "r");

    double param, param_err;
    fitfunc->GetParameters(&param);
    param_err = fitfunc->GetParError(0);
    
    UParaCorr_UPara[i] = param;
    UParaCorr_UPara_Err[i] = param_err;

    delete fitfunc;
    delete hUPara_Upara;
  }

  // uparallel vs luminosity
  TCanvas *c1 = new TCanvas("c1", "canvas");
  TGraphErrors *ge = new TGraphErrors(n_Lumi_Bins, Lumi_Average, UParaCorr_Lumi, Lumi_Average_Err, UParaCorr_Lumi_Err);  
  c1->SetGridx();
  c1->SetGridy();
  ge->Draw("AP");
  c1->Update();
  
  // uparallel vs uparallel
  TCanvas *c2 = new TCanvas("c2", "canvas");
  TGraphErrors *ge2 = new TGraphErrors(n_UPara_Bins, UPara_Average, UParaCorr_UPara, UPara_Average_Err, UParaCorr_UPara_Err);  
  c2->SetGridx();
  c2->SetGridy();
  ge2->Draw("AP");
  c2->Update();
}
