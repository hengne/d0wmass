{

  // TFile* fin = new TFile("/prj_root/7010/wz_write/rominsky/sam_analysis/run2b34_EMJET_qcd_bkgd/hist_fr_pteta1.root");

  TFile* fin = new TFile("hist_fr_pteta_run2b3_phimod5.root");

  gStyle->SetOptFit(111111);
   TH2D* hdt_eff = (TH2D*)gDirectory->Get("fr_2d");


  char out[1000] = "hdt_fr_2d_run2b3_phimod5";
  char pout[1000];
  sprintf(pout, "%s.ps", out);

  char name[1000];
  int colors[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 21, 31, 41};

  int nbinsX = hdt_eff->GetNbinsX();

  // projection to 1D
  TH1D* hdt_eff_Y[100]; 

  TLegend* lgY = new TLegend(0.2, 0.75, 0.45, 0.9);
  for (int i=1; i<=nbinsX; i++){
    sprintf(name, "hdt_eff_Y_%d", i);
    hdt_eff_Y[i] = (TH1D*)hdt_eff->ProjectionY(name, i, i, "e");
    hdt_eff_Y[i]->GetXaxis()->SetTitle("ElecPt (GeV)");
    hdt_eff_Y[i]->GetYaxis()->SetTitle("Eff");
    hdt_eff_Y[i]->SetLineColor(colors[i]);
    hdt_eff_Y[i]->SetMarkerColor(colors[i]);
    hdt_eff_Y[i]->GetYaxis()->SetRangeUser(0.0, 0.5);
    sprintf(name, "hdt_eff_ElecPt_PhysEta_Bin%d", i);
    hdt_eff_Y[i]->SetTitle(name);
    sprintf(name, "PhysEta_%d", i);
    lgY->AddEntry(hdt_eff_Y[i], name, "pl");
  }

  
  
  TCanvas* plots = new TCanvas("plots", "plots");
  sprintf(name, "%s[", pout);
  plots->Print(name);

  // 
  plots->Clear(); 
  hdt_eff->Draw("colz");
  plots->Print(pout);
  plots->Clear();
  
  //
  plots->Clear();
  hdt_eff_Y[1]->Draw();
  for (int i=2; i<=nbinsX; i++){
    hdt_eff_Y[i]->Draw("same");
  } 
  lgY->Draw("same");
  plots->Print(pout);
  plots->Clear();


  // fit ElecPt
  
  TF1* fX = new TF1("fX", "pol4", 25, 80);
  
  TFitResultPtr fXptr[100];

  for (int i=1; i<=nbinsX; i++){
    plots->Clear();
    //hdt_eff_Y[i]->Rebin(2);
    fXptr[i] = hdt_eff_Y[i]->Fit(fX, "RSF", "", 25, 100);
    fXptr[i]->Print("V");
    //heff_X->Draw();
    //fX->Draw("same");
    plots->Print(pout);
    plots->Clear(); 
  }

  // print fit results
  for (int i=0; i<5; i++){
    std::cout << "double FR_par" << i << "[10] = {" ;
    std::cout << fXptr[1]->Value(i) ;
    for (int j=2; j<=nbinsX; j++){
      std::cout << ", " << fXptr[j]->Value(i); 
    }
    std::cout << "};" << std::endl;
  } 
  for (int i=0; i<5; i++){
    for(int k=0; k<5; k++){
      std::cout << "double FR_C" << i <<k<< "[10] = {" ;
      std::cout << fXptr[1]->CovMatrix(i,k) ;
      for (int j=2; j<=nbinsX; j++){
	std::cout << ", " << fXptr[j]->CovMatrix(i,k); 
      }
      std::cout << "};" << std::endl;
    }
  }



 
  sprintf(name, "%s]", pout);
  plots->Print(name);
  sprintf(name, ".! ps2pdf %s.ps %s.pdf", out, out);
  gROOT->ProcessLine(name);
  

}
