{


  gROOT->ProcessLine(".x DataTrackMatchEff_tighteff_run34_etapt_forhengne.C");
  
  TH2D* hdt_eff = (TH2D*)gDirectory->Get("hdt_eff_2d");
  gStyle->SetOptFit(11111);
  char out[1000] = "hdt_eff_2d";
  char pout[1000];
  sprintf(pout, "%s.ps", out);

  char name[1000];
  int colors[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 21, 31, 41};

  int nbinsX = hdt_eff->GetNbinsX();
  int nbinsY = hdt_eff->GetNbinsY();

  // projection to 1D
  TH1D* hdt_eff_X[100];
  TH1D* hdt_eff_Y[100]; 

  TLegend* lgY = new TLegend(0.2, 0.75, 0.45, 0.9);
  for (int i=1; i<=nbinsX; i++){
    sprintf(name, "hdt_eff_Y_%d", i);  
    hdt_eff_Y[i] = (TH1D*)hdt_eff->ProjectionY(name, i, i, "e");
    
    hdt_eff_Y[i]->GetXaxis()->SetTitle("PhysEta");
    hdt_eff_Y[i]->GetYaxis()->SetTitle("Eff");
    hdt_eff_Y[i]->SetLineColor(colors[i]);
    hdt_eff_Y[i]->SetMarkerColor(colors[i]);
    hdt_eff_Y[i]->GetYaxis()->SetRangeUser(0.3, 1.1);
    sprintf(name, "hdt_eff_PhysEta_ElecPt_Bin%d", i);
    hdt_eff_Y[i]->SetTitle(name);
    sprintf(name, "ElecPt_%d", i);
    lgY->AddEntry(hdt_eff_Y[i], name, "pl");
  }

  TLegend* lgX = new TLegend(0.2, 0.75, 0.45, 0.9);
  for (int i=1; i<=nbinsY; i++){
    sprintf(name, "hdt_eff_X_%d", i);
    hdt_eff_X[i] = (TH1D*)hdt_eff->ProjectionX(name, i, i, "e");
    hdt_eff_X[i]->GetXaxis()->SetTitle("ElecPt (GeV)");
    hdt_eff_X[i]->GetYaxis()->SetTitle("Eff");
    hdt_eff_X[i]->SetLineColor(colors[i]);
    hdt_eff_X[i]->SetMarkerColor(colors[i]);
    hdt_eff_X[i]->GetYaxis()->SetRangeUser(0.3, 1.1);
    sprintf(name, "hdt_eff_ElecPt_PhysEta_Bin%d", i);
    hdt_eff_X[i]->SetTitle(name);
    sprintf(name, "PhysEta_%d", i);
    lgX->AddEntry(hdt_eff_X[i], name, "pl");
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
  hdt_eff_X[1]->Draw();
  for (int i=2; i<=nbinsY; i++){
    hdt_eff_X[i]->Draw("same");
  } 
  lgX->Draw("same");
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

  for (int i=1; i<=nbinsY; i++){
    plots->Clear();
    fXptr[i] = hdt_eff_X[i]->Fit(fX, "RSF", "", 25, 100);
    fXptr[i]->Print("V");
    //heff_X->Draw();
    //fX->Draw("same");
    plots->Print(pout);
    plots->Clear(); 
  }

  // print fit results
  for (int i=0; i<5; i++){
    std::cout << "double EFF_par" << i << "[10] = {" ;
    std::cout << fXptr[1]->Value(i) ;
    for (int j=2; j<=nbinsY; j++){
      std::cout << ", " << fXptr[j]->Value(i); 
    }
    std::cout << "};" << std::endl;
  }
  for (int i=0; i<5; i++){
    for(int k=0; k<5; k++){
       std::cout << "double EFF_C" << i <<k<< "[10] = {" ;
      std::cout << fXptr[1]->CovMatrix(i,k) ;
      for (int j=2; j<=nbinsY; j++){
	std::cout << ", " << fXptr[j]->CovMatrix(i,k); 
      }
      std::cout << "};" << std::endl;
    }
  }
/*
  // fit 2D
  TF2* fXY = new TF2("fXY", "([0]+[1]*x+[2]*x**2+[3]*x**3+[4]*x**4)*([5]+[6]*y+[7]*y**2+[8]*y**3+[9]*y**4)", 25, 70, -1.5, 1.5);
 
  for (int i=0; i<5; i++){
    fXY->SetParameter(i, fX->GetParameter(i));
    //fXY->SetParameter(i+5, fY->GetParameter(i));
  }
 
  plots->Clear();
  TFitResultPtr fXYptr = hdt_eff->Fit(fXY, "S0R");
  fXYptr->Print("V");

  TH2D* hdt_eff_fit = (TH2D*)fXY->GetHistogram();
  hdt_eff_fit->GetZaxis()->SetRangeUser(0.5, 1.);

  hdt_eff->GetZaxis()->SetRangeUser(0.5, 1);
  hdt_eff->GetXaxis()->SetRangeUser(25, 69);

  plots->Clear();
  hdt_eff->Draw("colz");
  plots->Print(pout);
  plots->Clear();

  plots->Clear();
  hdt_eff_fit->Draw("colz");
  plots->Print(pout);
  plots->Clear();
*/  

  sprintf(name, "%s]", pout);
  plots->Print(name);
  sprintf(name, ".! ps2pdf %s.ps %s.pdf", out, out);
  gROOT->ProcessLine(name);
  

}
