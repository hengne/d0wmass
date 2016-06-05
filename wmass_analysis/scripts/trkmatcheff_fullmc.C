void divide_hist(TH1D& reth, TString num, TString den) {
  TH1D* numh = (TH1D*) gROOT->FindObject(num);
  cout << num << " " << numh << endl;
  TH1D* denh = (TH1D*) gROOT->FindObject(den);
  cout << den << " " << denh << endl;

  for(int i=0; i<numh->GetNbinsX(); i++){
    double content1=numh->GetBinContent(i+1);
    double content2=denh->GetBinContent(i+1);
    
    if(content2 > 0. && content1 > 0.){
      double p=content1/content2;
      double error=sqrt(p*(1-p)/content2);

      reth.SetBinContent(i+1, p);
      reth.SetBinError(i+1, error);
    }
  }

}

void divide_hist2(TH2D& reth, TString num, TString den) {
  TH2D* numh = (TH2D*) gROOT->FindObject(num);
  cout << num << " " << numh << endl;
  TH2D* denh = (TH2D*) gROOT->FindObject(den);
  cout << den << " " << denh << endl;

  for(int i=0; i<numh->GetNbinsX(); i++){
    for(int j=0; j<numh->GetNbinsY(); j++){
      double content1=numh->GetBinContent(i+1, j+1);
      double content2=denh->GetBinContent(i+1, j+1);
      
      if(content2 > 0. && content1 > 0.){
	double p=content1/content2;
	double error=sqrt(p*(1-p)/content2);
	
	reth.SetBinContent(i+1, j+1, p);
	reth.SetBinError(i+1, j+1, error);
      }
    }
  }
}

void divide_hist3(TH3D& reth, TString num, TString den) {
  TH3D* numh = (TH3D*) gROOT->FindObject(num);
  cout << num << " " << numh << endl;
  TH3D* denh = (TH3D*) gROOT->FindObject(den);
  cout << den << " " << denh << endl;

  for(int i=0; i<numh->GetNbinsX(); i++){
    for(int j=0; j<numh->GetNbinsY(); j++){
      for(int k=0; k<numh->GetNbinsZ(); k++){
	double content1=numh->GetBinContent(i+1, j+1, k+1);
	double content2=denh->GetBinContent(i+1, j+1, k+1);
	
	if(content2 > 0. && content1 > 0.){
	  double p=content1/content2;
	  double error=sqrt(p*(1-p)/content2);
	  
	  reth.SetBinContent(i+1, j+1, k+1, p);
	  reth.SetBinError(i+1, j+1, k+1, error);
	}
      }
    }
  }
}

void trkmatcheff_fullmc(TString filename) {
  
  // Opens the file
  TFile* fullmc = new TFile(filename,"UPDATE");
  
  // Go to the right directory
  fullmc->cd("ZCand_Hist");
  
  // Set some style
  gROOT->SetStyle("Plain");

  // 2D Tag and Probe
  TH2D* ZCandTrkMatchEff_Loose_vtxz_eta_coarse[6];
  TH2D* ZCandTrkMatchEff_Tight_vtxz_eta_coarse[6];

  TH2D* ZCandTrkMatchEff_Loose_vtxz_eta_coarse[0] = new TH2D("ZCandTrkMatchEff_Loose_vtxz_eta_coarse_0","Loose Track Match Eff - vtxz x eta x pT - CCCC", 36, -60., 60., 32, -3.2, 3.2);
  TH2D* ZCandTrkMatchEff_Loose_vtxz_eta_coarse[1] = new TH2D("ZCandTrkMatchEff_Loose_vtxz_eta_coarse_1","Loose Track Match Eff - vtxz x eta x pT - CCEC", 36, -60., 60., 32, -3.2, 3.2);
  TH2D* ZCandTrkMatchEff_Loose_vtxz_eta_coarse[2] = new TH2D("ZCandTrkMatchEff_Loose_vtxz_eta_coarse_2","Loose Track Match Eff - vtxz x eta x pT - ECCC", 36, -60., 60., 32, -3.2, 3.2);
  TH2D* ZCandTrkMatchEff_Loose_vtxz_eta_coarse[3] = new TH2D("ZCandTrkMatchEff_Loose_vtxz_eta_coarse_3","Loose Track Match Eff - vtxz x eta x pT - ECEC", 36, -60., 60., 32, -3.2, 3.2);
  TH2D* ZCandTrkMatchEff_Loose_vtxz_eta_coarse[4] = new TH2D("ZCandTrkMatchEff_Loose_vtxz_eta_coarse_4","Loose Track Match Eff - vtxz x eta x pT - CC", 36, -60., 60., 32, -3.2, 3.2);
  TH2D* ZCandTrkMatchEff_Loose_vtxz_eta_coarse[5] = new TH2D("ZCandTrkMatchEff_Loose_vtxz_eta_coarse_5","Loose Track Match Eff - vtxz x eta x pT - EC", 36, -60., 60., 32, -3.2, 3.2);

  TH2D* ZCandTrkMatchEff_Tight_vtxz_eta_coarse[0] = new TH2D("ZCandTrkMatchEff_Tight_vtxz_eta_coarse_0","Tight Track Match Eff - vtxz x eta x pT - CCCC", 36, -60., 60., 32, -3.2, 3.2);
  TH2D* ZCandTrkMatchEff_Tight_vtxz_eta_coarse[1] = new TH2D("ZCandTrkMatchEff_Tight_vtxz_eta_coarse_1","Tight Track Match Eff - vtxz x eta x pT - CCEC", 36, -60., 60., 32, -3.2, 3.2);
  TH2D* ZCandTrkMatchEff_Tight_vtxz_eta_coarse[2] = new TH2D("ZCandTrkMatchEff_Tight_vtxz_eta_coarse_2","Tight Track Match Eff - vtxz x eta x pT - ECCC", 36, -60., 60., 32, -3.2, 3.2);
  TH2D* ZCandTrkMatchEff_Tight_vtxz_eta_coarse[3] = new TH2D("ZCandTrkMatchEff_Tight_vtxz_eta_coarse_3","Tight Track Match Eff - vtxz x eta x pT - ECEC", 36, -60., 60., 32, -3.2, 3.2);
  TH2D* ZCandTrkMatchEff_Tight_vtxz_eta_coarse[4] = new TH2D("ZCandTrkMatchEff_Tight_vtxz_eta_coarse_4","Tight Track Match Eff - vtxz x eta x pT - CC", 36, -60., 60., 32, -3.2, 3.2);
  TH2D* ZCandTrkMatchEff_Tight_vtxz_eta_coarse[5] = new TH2D("ZCandTrkMatchEff_Tight_vtxz_eta_coarse_5","Tight Track Match Eff - vtxz x eta x pT - EC", 36, -60., 60., 32, -3.2, 3.2);

  divide_hist2(*ZCandTrkMatchEff_Loose_vtxz_eta_coarse[0],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_0", "ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse_0");
  divide_hist2(*ZCandTrkMatchEff_Loose_vtxz_eta_coarse[1],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_1", "ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse_1");
  divide_hist2(*ZCandTrkMatchEff_Loose_vtxz_eta_coarse[2],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_2", "ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse_2");
  divide_hist2(*ZCandTrkMatchEff_Loose_vtxz_eta_coarse[3],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_3", "ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse_3");
  divide_hist2(*ZCandTrkMatchEff_Loose_vtxz_eta_coarse[4],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_4", "ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse_4");
  divide_hist2(*ZCandTrkMatchEff_Loose_vtxz_eta_coarse[5],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_5", "ZCandTrkMatchEff_NoTrkMatch_vtxz_eta_coarse_5");

  divide_hist2(*ZCandTrkMatchEff_Tight_vtxz_eta_coarse[0],"ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse_0", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_0");
  divide_hist2(*ZCandTrkMatchEff_Tight_vtxz_eta_coarse[1],"ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse_1", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_1");
  divide_hist2(*ZCandTrkMatchEff_Tight_vtxz_eta_coarse[2],"ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse_2", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_2");
  divide_hist2(*ZCandTrkMatchEff_Tight_vtxz_eta_coarse[3],"ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse_3", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_3");
  divide_hist2(*ZCandTrkMatchEff_Tight_vtxz_eta_coarse[4],"ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse_4", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_4");
  divide_hist2(*ZCandTrkMatchEff_Tight_vtxz_eta_coarse[5],"ZCandTrkMatchEff_TightTrkMatch_vtxz_eta_coarse_5", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_eta_coarse_5");

  // 1D Tag and Probe Loose Track Match Efficiency

  TH1D* ZCandTrkMatchEff_Loose_eta[6];
  TH1D* ZCandTrkMatchEff_Loose_caleta[6];
  TH1D* ZCandTrkMatchEff_Loose_pT[6];
  TH1D* ZCandTrkMatchEff_Loose_upara[6];
  TH1D* ZCandTrkMatchEff_Loose_vtxz[6];

  TH1D* ZCandTrkMatchEff_Loose_eta[0] = new TH1D("ZCandTrkMatchEff_Loose_eta_0","Loose Track Match Eff - eta - CCCC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_caleta[0] = new TH1D("ZCandTrkMatchEff_Loose_caleta_0","Loose Track Match Eff - Cal eta - CCCC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_pT[0] = new TH1D("ZCandTrkMatchEff_Loose_pT_0","Loose Track Match Eff - pT - CCCC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Loose_upara[0] = new TH1D("ZCandTrkMatchEff_Loose_upara_0","Loose Track Match Eff - upara - CCCC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Loose_vtxz[0] = new TH1D("ZCandTrkMatchEff_Loose_vtxz_0","Loose Track Match Eff - vtxz - CCCC", 320, -80., 80.);

  TH1D* ZCandTrkMatchEff_Loose_eta[1] = new TH1D("ZCandTrkMatchEff_Loose_eta_1","Loose Track Match Eff - eta - CCEC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_caleta[1] = new TH1D("ZCandTrkMatchEff_Loose_caleta_1","Loose Track Match Eff - Cal eta - CCEC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_pT[1] = new TH1D("ZCandTrkMatchEff_Loose_pT_1","Loose Track Match Eff - pT - CCEC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Loose_upara[1] = new TH1D("ZCandTrkMatchEff_Loose_upara_1","Loose Track Match Eff - upara - CCEC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Loose_vtxz[1] = new TH1D("ZCandTrkMatchEff_Loose_vtxz_1","Loose Track Match Eff - vtxz - CCEC", 320, -80., 80.);

  TH1D* ZCandTrkMatchEff_Loose_eta[2] = new TH1D("ZCandTrkMatchEff_Loose_eta_2","Loose Track Match Eff - eta - ECCC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_caleta[2] = new TH1D("ZCandTrkMatchEff_Loose_caleta_2","Loose Track Match Eff - Cal eta - ECCC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_pT[2] = new TH1D("ZCandTrkMatchEff_Loose_pT_2","Loose Track Match Eff - pT - ECCC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Loose_upara[2] = new TH1D("ZCandTrkMatchEff_Loose_upara_2","Loose Track Match Eff - upara - ECCC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Loose_vtxz[2] = new TH1D("ZCandTrkMatchEff_Loose_vtxz_2","Loose Track Match Eff - vtxz - ECCC", 320, -80., 80.);

  TH1D* ZCandTrkMatchEff_Loose_eta[3] = new TH1D("ZCandTrkMatchEff_Loose_eta_3","Loose Track Match Eff - eta - ECEC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_caleta[3] = new TH1D("ZCandTrkMatchEff_Loose_caleta_3","Loose Track Match Eff - Cal eta - ECEC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_pT[3] = new TH1D("ZCandTrkMatchEff_Loose_pT_3","Loose Track Match Eff - pT - ECEC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Loose_upara[3] = new TH1D("ZCandTrkMatchEff_Loose_upara_3","Loose Track Match Eff - upara - ECEC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Loose_vtxz[3] = new TH1D("ZCandTrkMatchEff_Loose_vtxz_3","Loose Track Match Eff - vtxz - ECEC", 320, -80., 80.);

  TH1D* ZCandTrkMatchEff_Loose_eta[4] = new TH1D("ZCandTrkMatchEff_Loose_eta_4","Loose Track Match Eff - eta - CC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_caleta[4] = new TH1D("ZCandTrkMatchEff_Loose_caleta_4","Loose Track Match Eff - Cal eta - CC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_pT[4] = new TH1D("ZCandTrkMatchEff_Loose_pT_4","Loose Track Match Eff - pT - CC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Loose_upara[4] = new TH1D("ZCandTrkMatchEff_Loose_upara_4","Loose Track Match Eff - upara - CC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Loose_vtxz[4] = new TH1D("ZCandTrkMatchEff_Loose_vtxz_4","Loose Track Match Eff - vtxz - CC", 320, -80., 80.);

  TH1D* ZCandTrkMatchEff_Loose_eta[5] = new TH1D("ZCandTrkMatchEff_Loose_eta_5","Loose Track Match Eff - eta - EC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_caleta[5] = new TH1D("ZCandTrkMatchEff_Loose_caleta_5","Loose Track Match Eff - Cal eta - EC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Loose_pT[5] = new TH1D("ZCandTrkMatchEff_Loose_pT_5","Loose Track Match Eff - pT - EC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Loose_upara[5] = new TH1D("ZCandTrkMatchEff_Loose_upara_5","Loose Track Match Eff - upara - EC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Loose_vtxz[5] = new TH1D("ZCandTrkMatchEff_Loose_vtxz_5","Loose Track Match Eff - vtxz - EC", 320, -80., 80.);

  divide_hist(*ZCandTrkMatchEff_Loose_eta[0],"ZCandTrkMatchEff_LooseTrkMatch_eta_0", "ZCandTrkMatchEff_NoTrkMatch_eta_0");
  divide_hist(*ZCandTrkMatchEff_Loose_caleta[0],"ZCandTrkMatchEff_LooseTrkMatch_caleta_0", "ZCandTrkMatchEff_NoTrkMatch_caleta_0");
  divide_hist(*ZCandTrkMatchEff_Loose_pT[0],"ZCandTrkMatchEff_LooseTrkMatch_pT_0", "ZCandTrkMatchEff_NoTrkMatch_pT_0");
  divide_hist(*ZCandTrkMatchEff_Loose_upara[0],"ZCandTrkMatchEff_LooseTrkMatch_upara_0", "ZCandTrkMatchEff_NoTrkMatch_upara_0");
  divide_hist(*ZCandTrkMatchEff_Loose_vtxz[0],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_0", "ZCandTrkMatchEff_NoTrkMatch_vtxz_0");

  divide_hist(*ZCandTrkMatchEff_Loose_eta[1],"ZCandTrkMatchEff_LooseTrkMatch_eta_1", "ZCandTrkMatchEff_NoTrkMatch_eta_1");
  divide_hist(*ZCandTrkMatchEff_Loose_caleta[1],"ZCandTrkMatchEff_LooseTrkMatch_caleta_1", "ZCandTrkMatchEff_NoTrkMatch_caleta_1");
  divide_hist(*ZCandTrkMatchEff_Loose_pT[1],"ZCandTrkMatchEff_LooseTrkMatch_pT_1", "ZCandTrkMatchEff_NoTrkMatch_pT_1");
  divide_hist(*ZCandTrkMatchEff_Loose_upara[1],"ZCandTrkMatchEff_LooseTrkMatch_upara_1", "ZCandTrkMatchEff_NoTrkMatch_upara_1");
  divide_hist(*ZCandTrkMatchEff_Loose_vtxz[1],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_1", "ZCandTrkMatchEff_NoTrkMatch_vtxz_1");

  divide_hist(*ZCandTrkMatchEff_Loose_eta[2],"ZCandTrkMatchEff_LooseTrkMatch_eta_2", "ZCandTrkMatchEff_NoTrkMatch_eta_2");
  divide_hist(*ZCandTrkMatchEff_Loose_caleta[2],"ZCandTrkMatchEff_LooseTrkMatch_caleta_2", "ZCandTrkMatchEff_NoTrkMatch_caleta_2");
  divide_hist(*ZCandTrkMatchEff_Loose_pT[2],"ZCandTrkMatchEff_LooseTrkMatch_pT_2", "ZCandTrkMatchEff_NoTrkMatch_pT_2");
  divide_hist(*ZCandTrkMatchEff_Loose_upara[2],"ZCandTrkMatchEff_LooseTrkMatch_upara_2", "ZCandTrkMatchEff_NoTrkMatch_upara_2");
  divide_hist(*ZCandTrkMatchEff_Loose_vtxz[2],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_2", "ZCandTrkMatchEff_NoTrkMatch_vtxz_2");

  divide_hist(*ZCandTrkMatchEff_Loose_eta[3],"ZCandTrkMatchEff_LooseTrkMatch_eta_3", "ZCandTrkMatchEff_NoTrkMatch_eta_3");
  divide_hist(*ZCandTrkMatchEff_Loose_caleta[3],"ZCandTrkMatchEff_LooseTrkMatch_caleta_3", "ZCandTrkMatchEff_NoTrkMatch_caleta_3");
  divide_hist(*ZCandTrkMatchEff_Loose_pT[3],"ZCandTrkMatchEff_LooseTrkMatch_pT_3", "ZCandTrkMatchEff_NoTrkMatch_pT_3");
  divide_hist(*ZCandTrkMatchEff_Loose_upara[3],"ZCandTrkMatchEff_LooseTrkMatch_upara_3", "ZCandTrkMatchEff_NoTrkMatch_upara_3");
  divide_hist(*ZCandTrkMatchEff_Loose_vtxz[3],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_3", "ZCandTrkMatchEff_NoTrkMatch_vtxz_3");

  divide_hist(*ZCandTrkMatchEff_Loose_eta[4],"ZCandTrkMatchEff_LooseTrkMatch_eta_4", "ZCandTrkMatchEff_NoTrkMatch_eta_4");
  divide_hist(*ZCandTrkMatchEff_Loose_caleta[4],"ZCandTrkMatchEff_LooseTrkMatch_caleta_4", "ZCandTrkMatchEff_NoTrkMatch_caleta_4");
  divide_hist(*ZCandTrkMatchEff_Loose_pT[4],"ZCandTrkMatchEff_LooseTrkMatch_pT_4", "ZCandTrkMatchEff_NoTrkMatch_pT_4");
  divide_hist(*ZCandTrkMatchEff_Loose_upara[4],"ZCandTrkMatchEff_LooseTrkMatch_upara_4", "ZCandTrkMatchEff_NoTrkMatch_upara_4");
  divide_hist(*ZCandTrkMatchEff_Loose_vtxz[4],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_4", "ZCandTrkMatchEff_NoTrkMatch_vtxz_4");

  divide_hist(*ZCandTrkMatchEff_Loose_eta[5],"ZCandTrkMatchEff_LooseTrkMatch_eta_5", "ZCandTrkMatchEff_NoTrkMatch_eta_5");
  divide_hist(*ZCandTrkMatchEff_Loose_caleta[5],"ZCandTrkMatchEff_LooseTrkMatch_caleta_5", "ZCandTrkMatchEff_NoTrkMatch_caleta_5");
  divide_hist(*ZCandTrkMatchEff_Loose_pT[5],"ZCandTrkMatchEff_LooseTrkMatch_pT_5", "ZCandTrkMatchEff_NoTrkMatch_pT_5");
  divide_hist(*ZCandTrkMatchEff_Loose_upara[5],"ZCandTrkMatchEff_LooseTrkMatch_upara_5", "ZCandTrkMatchEff_NoTrkMatch_upara_5");
  divide_hist(*ZCandTrkMatchEff_Loose_vtxz[5],"ZCandTrkMatchEff_LooseTrkMatch_vtxz_5", "ZCandTrkMatchEff_NoTrkMatch_vtxz_5");

  // 1D Truth Loose Track Match Efficiency

  TH1D* ZCandTrueTrkMatchEff_Loose_eta[6];
  TH1D* ZCandTrueTrkMatchEff_Loose_caleta[6];
  TH1D* ZCandTrueTrkMatchEff_Loose_pT[6];
  TH1D* ZCandTrueTrkMatchEff_Loose_upara[6];
  TH1D* ZCandTrueTrkMatchEff_Loose_vtxz[6];

  TH1D* ZCandTrueTrkMatchEff_Loose_eta[0] = new TH1D("ZCandTrueTrkMatchEff_Loose_eta_0","Loose Track Match Eff - eta - CCCC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_caleta[0] = new TH1D("ZCandTrueTrkMatchEff_Loose_caleta_0","Loose Track Match Eff - Cal eta - CCCC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_pT[0] = new TH1D("ZCandTrueTrkMatchEff_Loose_pT_0","Loose Track Match Eff - pT - CCCC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Loose_upara[0] = new TH1D("ZCandTrueTrkMatchEff_Loose_upara_0","Loose Track Match Eff - upara - CCCC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Loose_vtxz[0] = new TH1D("ZCandTrueTrkMatchEff_Loose_vtxz_0","Loose Track Match Eff - vtxz - CCCC", 320, -80., 80.);

  TH1D* ZCandTrueTrkMatchEff_Loose_eta[1] = new TH1D("ZCandTrueTrkMatchEff_Loose_eta_1","Loose Track Match Eff - eta - CCEC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_caleta[1] = new TH1D("ZCandTrueTrkMatchEff_Loose_caleta_1","Loose Track Match Eff - Cal eta - CCEC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_pT[1] = new TH1D("ZCandTrueTrkMatchEff_Loose_pT_1","Loose Track Match Eff - pT - CCEC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Loose_upara[1] = new TH1D("ZCandTrueTrkMatchEff_Loose_upara_1","Loose Track Match Eff - upara - CCEC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Loose_vtxz[1] = new TH1D("ZCandTrueTrkMatchEff_Loose_vtxz_1","Loose Track Match Eff - vtxz - CCEC", 320, -80., 80.);

  TH1D* ZCandTrueTrkMatchEff_Loose_eta[2] = new TH1D("ZCandTrueTrkMatchEff_Loose_eta_2","Loose Track Match Eff - eta - ECCC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_caleta[2] = new TH1D("ZCandTrueTrkMatchEff_Loose_caleta_2","Loose Track Match Eff - Cal eta - ECCC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_pT[2] = new TH1D("ZCandTrueTrkMatchEff_Loose_pT_2","Loose Track Match Eff - pT - ECCC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Loose_upara[2] = new TH1D("ZCandTrueTrkMatchEff_Loose_upara_2","Loose Track Match Eff - upara - ECCC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Loose_vtxz[2] = new TH1D("ZCandTrueTrkMatchEff_Loose_vtxz_2","Loose Track Match Eff - vtxz - ECCC", 320, -80., 80.);

  TH1D* ZCandTrueTrkMatchEff_Loose_eta[3] = new TH1D("ZCandTrueTrkMatchEff_Loose_eta_3","Loose Track Match Eff - eta - ECEC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_caleta[3] = new TH1D("ZCandTrueTrkMatchEff_Loose_caleta_3","Loose Track Match Eff - Cal eta - ECEC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_pT[3] = new TH1D("ZCandTrueTrkMatchEff_Loose_pT_3","Loose Track Match Eff - pT - ECEC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Loose_upara[3] = new TH1D("ZCandTrueTrkMatchEff_Loose_upara_3","Loose Track Match Eff - upara - ECEC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Loose_vtxz[3] = new TH1D("ZCandTrueTrkMatchEff_Loose_vtxz_3","Loose Track Match Eff - vtxz - ECEC", 320, -80., 80.);

  TH1D* ZCandTrueTrkMatchEff_Loose_eta[4] = new TH1D("ZCandTrueTrkMatchEff_Loose_eta_4","Loose Track Match Eff - eta - CC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_caleta[4] = new TH1D("ZCandTrueTrkMatchEff_Loose_caleta_4","Loose Track Match Eff - Cal eta - CC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_pT[4] = new TH1D("ZCandTrueTrkMatchEff_Loose_pT_4","Loose Track Match Eff - pT - CC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Loose_upara[4] = new TH1D("ZCandTrueTrkMatchEff_Loose_upara_4","Loose Track Match Eff - upara - CC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Loose_vtxz[4] = new TH1D("ZCandTrueTrkMatchEff_Loose_vtxz_4","Loose Track Match Eff - vtxz - CC", 320, -80., 80.);

  TH1D* ZCandTrueTrkMatchEff_Loose_eta[5] = new TH1D("ZCandTrueTrkMatchEff_Loose_eta_5","Loose Track Match Eff - eta - EC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_caleta[5] = new TH1D("ZCandTrueTrkMatchEff_Loose_caleta_5","Loose Track Match Eff - Cal eta - EC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Loose_pT[5] = new TH1D("ZCandTrueTrkMatchEff_Loose_pT_5","Loose Track Match Eff - pT - EC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Loose_upara[5] = new TH1D("ZCandTrueTrkMatchEff_Loose_upara_5","Loose Track Match Eff - upara - EC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Loose_vtxz[5] = new TH1D("ZCandTrueTrkMatchEff_Loose_vtxz_5","Loose Track Match Eff - vtxz - EC", 320, -80., 80.);

  divide_hist(*ZCandTrueTrkMatchEff_Loose_eta[0],"ZCandTrueTrkMatchEff_LooseTrkMatch_eta_0", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_0");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_caleta[0],"ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_0", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_0");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_pT[0],"ZCandTrueTrkMatchEff_LooseTrkMatch_pT_0", "ZCandTrueTrkMatchEff_NoTrkMatch_pT_0");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_upara[0],"ZCandTrueTrkMatchEff_LooseTrkMatch_upara_0", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_0");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_vtxz[0],"ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_0", "ZCandTrueTrkMatchEff_NoTrkMatch_vtxz_0");

  divide_hist(*ZCandTrueTrkMatchEff_Loose_eta[1],"ZCandTrueTrkMatchEff_LooseTrkMatch_eta_1", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_1");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_caleta[1],"ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_1", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_1");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_pT[1],"ZCandTrueTrkMatchEff_LooseTrkMatch_pT_1", "ZCandTrueTrkMatchEff_NoTrkMatch_pT_1");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_upara[1],"ZCandTrueTrkMatchEff_LooseTrkMatch_upara_1", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_1");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_vtxz[1],"ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_1", "ZCandTrueTrkMatchEff_NoTrkMatch_vtxz_1");

  divide_hist(*ZCandTrueTrkMatchEff_Loose_eta[2],"ZCandTrueTrkMatchEff_LooseTrkMatch_eta_2", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_2");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_caleta[2],"ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_2", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_2");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_pT[2],"ZCandTrueTrkMatchEff_LooseTrkMatch_pT_2", "ZCandTrueTrkMatchEff_NoTrkMatch_pT_2");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_upara[2],"ZCandTrueTrkMatchEff_LooseTrkMatch_upara_2", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_2");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_vtxz[2],"ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_2", "ZCandTrueTrkMatchEff_NoTrkMatch_vtxz_2");

  divide_hist(*ZCandTrueTrkMatchEff_Loose_eta[3],"ZCandTrueTrkMatchEff_LooseTrkMatch_eta_3", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_3");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_caleta[3],"ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_3", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_3");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_pT[3],"ZCandTrueTrkMatchEff_LooseTrkMatch_pT_3", "ZCandTrueTrkMatchEff_NoTrkMatch_pT_3");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_upara[3],"ZCandTrueTrkMatchEff_LooseTrkMatch_upara_3", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_3");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_vtxz[3],"ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_3", "ZCandTrueTrkMatchEff_NoTrkMatch_vtxz_3");

  divide_hist(*ZCandTrueTrkMatchEff_Loose_eta[4],"ZCandTrueTrkMatchEff_LooseTrkMatch_eta_4", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_4");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_caleta[4],"ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_4", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_4");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_pT[4],"ZCandTrueTrkMatchEff_LooseTrkMatch_pT_4", "ZCandTrueTrkMatchEff_NoTrkMatch_pT_4");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_upara[4],"ZCandTrueTrkMatchEff_LooseTrkMatch_upara_4", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_4");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_vtxz[4],"ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_4", "ZCandTrueTrkMatchEff_NoTrkMatch_vtxz_4");

  divide_hist(*ZCandTrueTrkMatchEff_Loose_eta[5],"ZCandTrueTrkMatchEff_LooseTrkMatch_eta_5", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_5");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_caleta[5],"ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_5", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_5");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_pT[5],"ZCandTrueTrkMatchEff_LooseTrkMatch_pT_5", "ZCandTrueTrkMatchEff_NoTrkMatch_pT_5");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_upara[5],"ZCandTrueTrkMatchEff_LooseTrkMatch_upara_5", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_5");
  divide_hist(*ZCandTrueTrkMatchEff_Loose_vtxz[5],"ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_5", "ZCandTrueTrkMatchEff_NoTrkMatch_vtxz_5");

  // 1D Tag and Probe Tight Track Match Efficiency

  TH1D* ZCandTrkMatchEff_Tight_eta[6];
  TH1D* ZCandTrkMatchEff_Tight_caleta[6];
  TH1D* ZCandTrkMatchEff_Tight_pT[6];
  TH1D* ZCandTrkMatchEff_Tight_upara[6];
  TH1D* ZCandTrkMatchEff_Tight_vtxz[6];

  TH1D* ZCandTrkMatchEff_Tight_eta[0] = new TH1D("ZCandTrkMatchEff_Tight_eta_0","Tight Track Match Eff - eta - CCCC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_caleta[0] = new TH1D("ZCandTrkMatchEff_Tight_caleta_0","Tight Track Match Eff - Cal eta - CCCC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_pT[0] = new TH1D("ZCandTrkMatchEff_Tight_pT_0","Tight Track Match Eff - pT - CCCC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Tight_upara[0] = new TH1D("ZCandTrkMatchEff_Tight_upara_0","Tight Track Match Eff - upara - CCCC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Tight_vtxz[0] = new TH1D("ZCandTrkMatchEff_Tight_vtxz_0","Tight Track Match Eff - vtxz - CCCC", 320, -80., 80.);

  TH1D* ZCandTrkMatchEff_Tight_eta[1] = new TH1D("ZCandTrkMatchEff_Tight_eta_1","Tight Track Match Eff - eta - CCEC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_caleta[1] = new TH1D("ZCandTrkMatchEff_Tight_caleta_1","Tight Track Match Eff - Cal eta - CCEC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_pT[1] = new TH1D("ZCandTrkMatchEff_Tight_pT_1","Tight Track Match Eff - pT - CCEC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Tight_upara[1] = new TH1D("ZCandTrkMatchEff_Tight_upara_1","Tight Track Match Eff - upara - CCEC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Tight_vtxz[1] = new TH1D("ZCandTrkMatchEff_Tight_vtxz_1","Tight Track Match Eff - vtxz - CCEC", 320, -80., 80.);

  TH1D* ZCandTrkMatchEff_Tight_eta[2] = new TH1D("ZCandTrkMatchEff_Tight_eta_2","Tight Track Match Eff - eta - ECCC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_caleta[2] = new TH1D("ZCandTrkMatchEff_Tight_caleta_2","Tight Track Match Eff - Cal eta - ECCC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_pT[2] = new TH1D("ZCandTrkMatchEff_Tight_pT_2","Tight Track Match Eff - pT - ECCC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Tight_upara[2] = new TH1D("ZCandTrkMatchEff_Tight_upara_2","Tight Track Match Eff - upara - ECCC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Tight_vtxz[2] = new TH1D("ZCandTrkMatchEff_Tight_vtxz_2","Tight Track Match Eff - vtxz - ECCC", 320, -80., 80.);

  TH1D* ZCandTrkMatchEff_Tight_eta[3] = new TH1D("ZCandTrkMatchEff_Tight_eta_3","Tight Track Match Eff - eta - ECEC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_caleta[3] = new TH1D("ZCandTrkMatchEff_Tight_caleta_3","Tight Track Match Eff - Cal eta - ECEC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_pT[3] = new TH1D("ZCandTrkMatchEff_Tight_pT_3","Tight Track Match Eff - pT - ECEC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Tight_upara[3] = new TH1D("ZCandTrkMatchEff_Tight_upara_3","Tight Track Match Eff - upara - ECEC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Tight_vtxz[3] = new TH1D("ZCandTrkMatchEff_Tight_vtxz_3","Tight Track Match Eff - vtxz - ECEC", 320, -80., 80.);

  TH1D* ZCandTrkMatchEff_Tight_eta[4] = new TH1D("ZCandTrkMatchEff_Tight_eta_4","Tight Track Match Eff - eta - CC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_caleta[4] = new TH1D("ZCandTrkMatchEff_Tight_caleta_4","Tight Track Match Eff - Cal eta - CC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_pT[4] = new TH1D("ZCandTrkMatchEff_Tight_pT_4","Tight Track Match Eff - pT - CC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Tight_upara[4] = new TH1D("ZCandTrkMatchEff_Tight_upara_4","Tight Track Match Eff - upara - CC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Tight_vtxz[4] = new TH1D("ZCandTrkMatchEff_Tight_vtxz_4","Tight Track Match Eff - vtxz - CC", 320, -80., 80.);

  TH1D* ZCandTrkMatchEff_Tight_eta[5] = new TH1D("ZCandTrkMatchEff_Tight_eta_5","Tight Track Match Eff - eta - EC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_caleta[5] = new TH1D("ZCandTrkMatchEff_Tight_caleta_5","Tight Track Match Eff - Cal eta - EC", 80, -4., 4.);
  TH1D* ZCandTrkMatchEff_Tight_pT[5] = new TH1D("ZCandTrkMatchEff_Tight_pT_5","Tight Track Match Eff - pT - EC", 100, 0., 100.);
  TH1D* ZCandTrkMatchEff_Tight_upara[5] = new TH1D("ZCandTrkMatchEff_Tight_upara_5","Tight Track Match Eff - upara - EC", 120, -30., 30.);  
  TH1D* ZCandTrkMatchEff_Tight_vtxz[5] = new TH1D("ZCandTrkMatchEff_Tight_vtxz_5","Tight Track Match Eff - vtxz - EC", 320, -80., 80.);

  divide_hist(*ZCandTrkMatchEff_Tight_eta[0],"ZCandTrkMatchEff_TightTrkMatch_eta_0", "ZCandTrkMatchEff_LooseTrkMatch_eta_0");
  divide_hist(*ZCandTrkMatchEff_Tight_caleta[0],"ZCandTrkMatchEff_TightTrkMatch_caleta_0", "ZCandTrkMatchEff_LooseTrkMatch_caleta_0");
  divide_hist(*ZCandTrkMatchEff_Tight_pT[0],"ZCandTrkMatchEff_TightTrkMatch_pT_0", "ZCandTrkMatchEff_LooseTrkMatch_pT_0");
  divide_hist(*ZCandTrkMatchEff_Tight_upara[0],"ZCandTrkMatchEff_TightTrkMatch_upara_0", "ZCandTrkMatchEff_LooseTrkMatch_upara_0");
  divide_hist(*ZCandTrkMatchEff_Tight_vtxz[0],"ZCandTrkMatchEff_TightTrkMatch_vtxz_0", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_0");

  divide_hist(*ZCandTrkMatchEff_Tight_eta[1],"ZCandTrkMatchEff_TightTrkMatch_eta_1", "ZCandTrkMatchEff_LooseTrkMatch_eta_1");
  divide_hist(*ZCandTrkMatchEff_Tight_caleta[1],"ZCandTrkMatchEff_TightTrkMatch_caleta_1", "ZCandTrkMatchEff_LooseTrkMatch_caleta_1");
  divide_hist(*ZCandTrkMatchEff_Tight_pT[1],"ZCandTrkMatchEff_TightTrkMatch_pT_1", "ZCandTrkMatchEff_LooseTrkMatch_pT_1");
  divide_hist(*ZCandTrkMatchEff_Tight_upara[1],"ZCandTrkMatchEff_TightTrkMatch_upara_1", "ZCandTrkMatchEff_LooseTrkMatch_upara_1");
  divide_hist(*ZCandTrkMatchEff_Tight_vtxz[1],"ZCandTrkMatchEff_TightTrkMatch_vtxz_1", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_1");

  divide_hist(*ZCandTrkMatchEff_Tight_eta[2],"ZCandTrkMatchEff_TightTrkMatch_eta_2", "ZCandTrkMatchEff_LooseTrkMatch_eta_2");
  divide_hist(*ZCandTrkMatchEff_Tight_caleta[2],"ZCandTrkMatchEff_TightTrkMatch_caleta_2", "ZCandTrkMatchEff_LooseTrkMatch_caleta_2");
  divide_hist(*ZCandTrkMatchEff_Tight_pT[2],"ZCandTrkMatchEff_TightTrkMatch_pT_2", "ZCandTrkMatchEff_LooseTrkMatch_pT_2");
  divide_hist(*ZCandTrkMatchEff_Tight_upara[2],"ZCandTrkMatchEff_TightTrkMatch_upara_2", "ZCandTrkMatchEff_LooseTrkMatch_upara_2");
  divide_hist(*ZCandTrkMatchEff_Tight_vtxz[2],"ZCandTrkMatchEff_TightTrkMatch_vtxz_2", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_2");

  divide_hist(*ZCandTrkMatchEff_Tight_eta[3],"ZCandTrkMatchEff_TightTrkMatch_eta_3", "ZCandTrkMatchEff_LooseTrkMatch_eta_3");
  divide_hist(*ZCandTrkMatchEff_Tight_caleta[3],"ZCandTrkMatchEff_TightTrkMatch_caleta_3", "ZCandTrkMatchEff_LooseTrkMatch_caleta_3");
  divide_hist(*ZCandTrkMatchEff_Tight_pT[3],"ZCandTrkMatchEff_TightTrkMatch_pT_3", "ZCandTrkMatchEff_LooseTrkMatch_pT_3");
  divide_hist(*ZCandTrkMatchEff_Tight_upara[3],"ZCandTrkMatchEff_TightTrkMatch_upara_3", "ZCandTrkMatchEff_LooseTrkMatch_upara_3");
  divide_hist(*ZCandTrkMatchEff_Tight_vtxz[3],"ZCandTrkMatchEff_TightTrkMatch_vtxz_3", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_3");

  divide_hist(*ZCandTrkMatchEff_Tight_eta[4],"ZCandTrkMatchEff_TightTrkMatch_eta_4", "ZCandTrkMatchEff_LooseTrkMatch_eta_4");
  divide_hist(*ZCandTrkMatchEff_Tight_caleta[4],"ZCandTrkMatchEff_TightTrkMatch_caleta_4", "ZCandTrkMatchEff_LooseTrkMatch_caleta_4");
  divide_hist(*ZCandTrkMatchEff_Tight_pT[4],"ZCandTrkMatchEff_TightTrkMatch_pT_4", "ZCandTrkMatchEff_LooseTrkMatch_pT_4");
  divide_hist(*ZCandTrkMatchEff_Tight_upara[4],"ZCandTrkMatchEff_TightTrkMatch_upara_4", "ZCandTrkMatchEff_LooseTrkMatch_upara_4");
  divide_hist(*ZCandTrkMatchEff_Tight_vtxz[4],"ZCandTrkMatchEff_TightTrkMatch_vtxz_4", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_4");

  divide_hist(*ZCandTrkMatchEff_Tight_eta[5],"ZCandTrkMatchEff_TightTrkMatch_eta_5", "ZCandTrkMatchEff_LooseTrkMatch_eta_5");
  divide_hist(*ZCandTrkMatchEff_Tight_caleta[5],"ZCandTrkMatchEff_TightTrkMatch_caleta_5", "ZCandTrkMatchEff_LooseTrkMatch_caleta_5");
  divide_hist(*ZCandTrkMatchEff_Tight_pT[5],"ZCandTrkMatchEff_TightTrkMatch_pT_5", "ZCandTrkMatchEff_LooseTrkMatch_pT_5");
  divide_hist(*ZCandTrkMatchEff_Tight_upara[5],"ZCandTrkMatchEff_TightTrkMatch_upara_5", "ZCandTrkMatchEff_LooseTrkMatch_upara_5");
  divide_hist(*ZCandTrkMatchEff_Tight_vtxz[5],"ZCandTrkMatchEff_TightTrkMatch_vtxz_5", "ZCandTrkMatchEff_LooseTrkMatch_vtxz_5");

  // 1D Truth Tight Track Match Efficiency

  TH1D* ZCandTrueTrkMatchEff_Tight_eta[6];
  TH1D* ZCandTrueTrkMatchEff_Tight_caleta[6];
  TH1D* ZCandTrueTrkMatchEff_Tight_pT[6];
  TH1D* ZCandTrueTrkMatchEff_Tight_upara[6];
  TH1D* ZCandTrueTrkMatchEff_Tight_vtxz[6];

  TH1D* ZCandTrueTrkMatchEff_Tight_eta[0] = new TH1D("ZCandTrueTrkMatchEff_Tight_eta_0","Tight Track Match Eff - eta - CCCC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_caleta[0] = new TH1D("ZCandTrueTrkMatchEff_Tight_caleta_0","Tight Track Match Eff - Cal eta - CCCC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_pT[0] = new TH1D("ZCandTrueTrkMatchEff_Tight_pT_0","Tight Track Match Eff - pT - CCCC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Tight_upara[0] = new TH1D("ZCandTrueTrkMatchEff_Tight_upara_0","Tight Track Match Eff - upara - CCCC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Tight_vtxz[0] = new TH1D("ZCandTrueTrkMatchEff_Tight_vtxz_0","Tight Track Match Eff - vtxz - CCCC", 320, -80., 80.);

  TH1D* ZCandTrueTrkMatchEff_Tight_eta[1] = new TH1D("ZCandTrueTrkMatchEff_Tight_eta_1","Tight Track Match Eff - eta - CCEC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_caleta[1] = new TH1D("ZCandTrueTrkMatchEff_Tight_caleta_1","Tight Track Match Eff - Cal eta - CCEC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_pT[1] = new TH1D("ZCandTrueTrkMatchEff_Tight_pT_1","Tight Track Match Eff - pT - CCEC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Tight_upara[1] = new TH1D("ZCandTrueTrkMatchEff_Tight_upara_1","Tight Track Match Eff - upara - CCEC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Tight_vtxz[1] = new TH1D("ZCandTrueTrkMatchEff_Tight_vtxz_1","Tight Track Match Eff - vtxz - CCEC", 320, -80., 80.);

  TH1D* ZCandTrueTrkMatchEff_Tight_eta[2] = new TH1D("ZCandTrueTrkMatchEff_Tight_eta_2","Tight Track Match Eff - eta - ECCC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_caleta[2] = new TH1D("ZCandTrueTrkMatchEff_Tight_caleta_2","Tight Track Match Eff - Cal eta - ECCC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_pT[2] = new TH1D("ZCandTrueTrkMatchEff_Tight_pT_2","Tight Track Match Eff - pT - ECCC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Tight_upara[2] = new TH1D("ZCandTrueTrkMatchEff_Tight_upara_2","Tight Track Match Eff - upara - ECCC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Tight_vtxz[2] = new TH1D("ZCandTrueTrkMatchEff_Tight_vtxz_2","Tight Track Match Eff - vtxz - ECCC", 320, -80., 80.);

  TH1D* ZCandTrueTrkMatchEff_Tight_eta[3] = new TH1D("ZCandTrueTrkMatchEff_Tight_eta_3","Tight Track Match Eff - eta - ECEC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_caleta[3] = new TH1D("ZCandTrueTrkMatchEff_Tight_caleta_3","Tight Track Match Eff - Cal eta - ECEC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_pT[3] = new TH1D("ZCandTrueTrkMatchEff_Tight_pT_3","Tight Track Match Eff - pT - ECEC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Tight_upara[3] = new TH1D("ZCandTrueTrkMatchEff_Tight_upara_3","Tight Track Match Eff - upara - ECEC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Tight_vtxz[3] = new TH1D("ZCandTrueTrkMatchEff_Tight_vtxz_3","Tight Track Match Eff - vtxz - ECEC", 320, -80., 80.);

  TH1D* ZCandTrueTrkMatchEff_Tight_eta[4] = new TH1D("ZCandTrueTrkMatchEff_Tight_eta_4","Tight Track Match Eff - eta - CC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_caleta[4] = new TH1D("ZCandTrueTrkMatchEff_Tight_caleta_4","Tight Track Match Eff - Cal eta - CC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_pT[4] = new TH1D("ZCandTrueTrkMatchEff_Tight_pT_4","Tight Track Match Eff - pT - CC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Tight_upara[4] = new TH1D("ZCandTrueTrkMatchEff_Tight_upara_4","Tight Track Match Eff - upara - CC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Tight_vtxz[4] = new TH1D("ZCandTrueTrkMatchEff_Tight_vtxz_4","Tight Track Match Eff - vtxz - CC", 320, -80., 80.);

  TH1D* ZCandTrueTrkMatchEff_Tight_eta[5] = new TH1D("ZCandTrueTrkMatchEff_Tight_eta_5","Tight Track Match Eff - eta - EC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_caleta[5] = new TH1D("ZCandTrueTrkMatchEff_Tight_caleta_5","Tight Track Match Eff - Cal eta - EC", 80, -4., 4.);
  TH1D* ZCandTrueTrkMatchEff_Tight_pT[5] = new TH1D("ZCandTrueTrkMatchEff_Tight_pT_5","Tight Track Match Eff - pT - EC", 100, 0., 100.);
  TH1D* ZCandTrueTrkMatchEff_Tight_upara[5] = new TH1D("ZCandTrueTrkMatchEff_Tight_upara_5","Tight Track Match Eff - upara - EC", 120, -30., 30.);  
  TH1D* ZCandTrueTrkMatchEff_Tight_vtxz[5] = new TH1D("ZCandTrueTrkMatchEff_Tight_vtxz_5","Tight Track Match Eff - vtxz - EC", 320, -80., 80.);

  divide_hist(*ZCandTrueTrkMatchEff_Tight_eta[0],"ZCandTrueTrkMatchEff_TightTrkMatch_eta_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_0");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_caleta[0],"ZCandTrueTrkMatchEff_TightTrkMatch_caleta_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_0");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_pT[0],"ZCandTrueTrkMatchEff_TightTrkMatch_pT_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_pT_0");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_upara[0],"ZCandTrueTrkMatchEff_TightTrkMatch_upara_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_0");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_vtxz[0],"ZCandTrueTrkMatchEff_TightTrkMatch_vtxz_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_0");

  divide_hist(*ZCandTrueTrkMatchEff_Tight_eta[1],"ZCandTrueTrkMatchEff_TightTrkMatch_eta_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_1");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_caleta[1],"ZCandTrueTrkMatchEff_TightTrkMatch_caleta_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_1");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_pT[1],"ZCandTrueTrkMatchEff_TightTrkMatch_pT_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_pT_1");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_upara[1],"ZCandTrueTrkMatchEff_TightTrkMatch_upara_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_1");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_vtxz[1],"ZCandTrueTrkMatchEff_TightTrkMatch_vtxz_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_1");

  divide_hist(*ZCandTrueTrkMatchEff_Tight_eta[2],"ZCandTrueTrkMatchEff_TightTrkMatch_eta_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_2");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_caleta[2],"ZCandTrueTrkMatchEff_TightTrkMatch_caleta_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_2");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_pT[2],"ZCandTrueTrkMatchEff_TightTrkMatch_pT_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_pT_2");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_upara[2],"ZCandTrueTrkMatchEff_TightTrkMatch_upara_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_2");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_vtxz[2],"ZCandTrueTrkMatchEff_TightTrkMatch_vtxz_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_2");

  divide_hist(*ZCandTrueTrkMatchEff_Tight_eta[3],"ZCandTrueTrkMatchEff_TightTrkMatch_eta_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_3");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_caleta[3],"ZCandTrueTrkMatchEff_TightTrkMatch_caleta_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_3");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_pT[3],"ZCandTrueTrkMatchEff_TightTrkMatch_pT_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_pT_3");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_upara[3],"ZCandTrueTrkMatchEff_TightTrkMatch_upara_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_3");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_vtxz[3],"ZCandTrueTrkMatchEff_TightTrkMatch_vtxz_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_3");

  divide_hist(*ZCandTrueTrkMatchEff_Tight_eta[4],"ZCandTrueTrkMatchEff_TightTrkMatch_eta_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_4");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_caleta[4],"ZCandTrueTrkMatchEff_TightTrkMatch_caleta_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_4");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_pT[4],"ZCandTrueTrkMatchEff_TightTrkMatch_pT_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_pT_4");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_upara[4],"ZCandTrueTrkMatchEff_TightTrkMatch_upara_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_4");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_vtxz[4],"ZCandTrueTrkMatchEff_TightTrkMatch_vtxz_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_4");

  divide_hist(*ZCandTrueTrkMatchEff_Tight_eta[5],"ZCandTrueTrkMatchEff_TightTrkMatch_eta_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_5");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_caleta[5],"ZCandTrueTrkMatchEff_TightTrkMatch_caleta_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_5");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_pT[5],"ZCandTrueTrkMatchEff_TightTrkMatch_pT_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_pT_5");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_upara[5],"ZCandTrueTrkMatchEff_TightTrkMatch_upara_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_5");
  divide_hist(*ZCandTrueTrkMatchEff_Tight_vtxz[5],"ZCandTrueTrkMatchEff_TightTrkMatch_vtxz_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_vtxz_5");

  // 2D Tag and Probe Loose Track Match Efficiency

  TH2D* ZCandTrkMatchEff_Loose_eta_pT[6];
  TH2D* ZCandTrkMatchEff_Loose_eta_vtxz[6];
  TH2D* ZCandTrkMatchEff_Loose_caleta_pT[6];
  TH2D* ZCandTrkMatchEff_Loose_caleta_vtxz[6];
  TH2D* ZCandTrkMatchEff_Loose_etam_vtxz[6];
  TH2D* ZCandTrkMatchEff_Loose_etap_vtxz[6];
  TH2D* ZCandTrkMatchEff_Loose_etam_etap[6];
  TH2D* ZCandTrkMatchEff_Loose_etap_etam[6];
  TH2D* ZCandTrkMatchEff_Loose_upara_pz[6];

  TH2D* ZCandTrkMatchEff_Loose_eta_pT[0] = new TH2D("ZCandTrkMatchEff_Loose_eta_pT_0", "Loose Track Match Eff - eta vs pT - CCCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_eta_vtxz[0] = new TH2D("ZCandTrkMatchEff_Loose_eta_vtxz_0", "Loose Track Match Eff - eta vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_pT[0] = new TH2D("ZCandTrkMatchEff_Loose_caleta_pT_0", "Loose Track Match Eff - Cal eta vs pT - CCCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_vtxz[0] = new TH2D("ZCandTrkMatchEff_Loose_caleta_vtxz_0", "Loose Track Match Eff - Cal eta vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_vtxz[0] = new TH2D("ZCandTrkMatchEff_Loose_etam_vtxz_0", "Loose Track Match Eff - eta(-) vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etap_vtxz[0] = new TH2D("ZCandTrkMatchEff_Loose_etap_vtxz_0", "Loose Track Match Eff - eta(+) vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_etap[0] = new TH2D("ZCandTrkMatchEff_Loose_etam_etap_0", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - CCCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_etap_etam[0] = new TH2D("ZCandTrkMatchEff_Loose_etap_etam_0", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - CCCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_upara_pz[0] = new TH2D("ZCandTrkMatchEff_Loose_upara_pz_0", "Loose Track Match Eff - upara vs pz - CCCC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrkMatchEff_Loose_eta_pT[1] = new TH2D("ZCandTrkMatchEff_Loose_eta_pT_1", "Loose Track Match Eff - eta vs pT - CCEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_eta_vtxz[1] = new TH2D("ZCandTrkMatchEff_Loose_eta_vtxz_1", "Loose Track Match Eff - eta vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_pT[1] = new TH2D("ZCandTrkMatchEff_Loose_caleta_pT_1", "Loose Track Match Eff - Cal eta vs pT - CCEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_vtxz[1] = new TH2D("ZCandTrkMatchEff_Loose_caleta_vtxz_1", "Loose Track Match Eff - Cal eta vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_vtxz[1] = new TH2D("ZCandTrkMatchEff_Loose_etam_vtxz_1", "Loose Track Match Eff - eta(-) vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etap_vtxz[1] = new TH2D("ZCandTrkMatchEff_Loose_etap_vtxz_1", "Loose Track Match Eff - eta(+) vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_etap[1] = new TH2D("ZCandTrkMatchEff_Loose_etam_etap_1", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - CCEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_etap_etam[1] = new TH2D("ZCandTrkMatchEff_Loose_etap_etam_1", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - CCEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_upara_pz[1] = new TH2D("ZCandTrkMatchEff_Loose_upara_pz_1", "Loose Track Match Eff - upara vs pz - CCEC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrkMatchEff_Loose_eta_pT[2] = new TH2D("ZCandTrkMatchEff_Loose_eta_pT_2", "Loose Track Match Eff - eta vs pT - ECCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_eta_vtxz[2] = new TH2D("ZCandTrkMatchEff_Loose_eta_vtxz_2", "Loose Track Match Eff - eta vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_pT[2] = new TH2D("ZCandTrkMatchEff_Loose_caleta_pT_2", "Loose Track Match Eff - Cal eta vs pT - ECCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_vtxz[2] = new TH2D("ZCandTrkMatchEff_Loose_caleta_vtxz_2", "Loose Track Match Eff - Cal eta vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_vtxz[2] = new TH2D("ZCandTrkMatchEff_Loose_etam_vtxz_2", "Loose Track Match Eff - eta(-) vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etap_vtxz[2] = new TH2D("ZCandTrkMatchEff_Loose_etap_vtxz_2", "Loose Track Match Eff - eta(+) vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_etap[2] = new TH2D("ZCandTrkMatchEff_Loose_etam_etap_2", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - ECCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_etap_etam[2] = new TH2D("ZCandTrkMatchEff_Loose_etap_etam_2", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - ECCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_upara_pz[2] = new TH2D("ZCandTrkMatchEff_Loose_upara_pz_2", "Loose Track Match Eff - upara vs pz - ECCC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrkMatchEff_Loose_eta_pT[3] = new TH2D("ZCandTrkMatchEff_Loose_eta_pT_3", "Loose Track Match Eff - eta vs pT - ECEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_eta_vtxz[3] = new TH2D("ZCandTrkMatchEff_Loose_eta_vtxz_3", "Loose Track Match Eff - eta vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_pT[3] = new TH2D("ZCandTrkMatchEff_Loose_caleta_pT_3", "Loose Track Match Eff - Cal eta vs pT - ECEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_vtxz[3] = new TH2D("ZCandTrkMatchEff_Loose_caleta_vtxz_3", "Loose Track Match Eff - Cal eta vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_vtxz[3] = new TH2D("ZCandTrkMatchEff_Loose_etam_vtxz_3", "Loose Track Match Eff - eta(-) vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etap_vtxz[3] = new TH2D("ZCandTrkMatchEff_Loose_etap_vtxz_3", "Loose Track Match Eff - eta(+) vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_etap[3] = new TH2D("ZCandTrkMatchEff_Loose_etam_etap_3", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - ECEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_etap_etam[3] = new TH2D("ZCandTrkMatchEff_Loose_etap_etam_3", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - ECEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_upara_pz[3] = new TH2D("ZCandTrkMatchEff_Loose_upara_pz_3", "Loose Track Match Eff - upara vs pz - ECEC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrkMatchEff_Loose_eta_pT[4] = new TH2D("ZCandTrkMatchEff_Loose_eta_pT_4", "Loose Track Match Eff - eta vs pT - CC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_eta_vtxz[4] = new TH2D("ZCandTrkMatchEff_Loose_eta_vtxz_4", "Loose Track Match Eff - eta vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_pT[4] = new TH2D("ZCandTrkMatchEff_Loose_caleta_pT_4", "Loose Track Match Eff - Cal eta vs pT - CC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_vtxz[4] = new TH2D("ZCandTrkMatchEff_Loose_caleta_vtxz_4", "Loose Track Match Eff - Cal eta vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_vtxz[4] = new TH2D("ZCandTrkMatchEff_Loose_etam_vtxz_4", "Loose Track Match Eff - eta(-) vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etap_vtxz[4] = new TH2D("ZCandTrkMatchEff_Loose_etap_vtxz_4", "Loose Track Match Eff - eta(+) vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_etap[4] = new TH2D("ZCandTrkMatchEff_Loose_etam_etap_4", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - CC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_etap_etam[4] = new TH2D("ZCandTrkMatchEff_Loose_etap_etam_4", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - CC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_upara_pz[4] = new TH2D("ZCandTrkMatchEff_Loose_upara_pz_4", "Loose Track Match Eff - upara vs pz - CC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrkMatchEff_Loose_eta_pT[5] = new TH2D("ZCandTrkMatchEff_Loose_eta_pT_5", "Loose Track Match Eff - eta vs pT - EC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_eta_vtxz[5] = new TH2D("ZCandTrkMatchEff_Loose_eta_vtxz_5", "Loose Track Match Eff - eta vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_pT[5] = new TH2D("ZCandTrkMatchEff_Loose_caleta_pT_5", "Loose Track Match Eff - Cal eta vs pT - EC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Loose_caleta_vtxz[5] = new TH2D("ZCandTrkMatchEff_Loose_caleta_vtxz_5", "Loose Track Match Eff - Cal eta vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_vtxz[5] = new TH2D("ZCandTrkMatchEff_Loose_etam_vtxz_5", "Loose Track Match Eff - eta(-) vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etap_vtxz[5] = new TH2D("ZCandTrkMatchEff_Loose_etap_vtxz_5", "Loose Track Match Eff - eta(+) vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Loose_etam_etap[5] = new TH2D("ZCandTrkMatchEff_Loose_etam_etap_5", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - EC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_etap_etam[5] = new TH2D("ZCandTrkMatchEff_Loose_etap_etam_5", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - EC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Loose_upara_pz[5] = new TH2D("ZCandTrkMatchEff_Loose_upara_pz_5", "Loose Track Match Eff - upara vs pz - EC", 120, -30., 30., 400, -200., 200.);

  divide_hist2(*ZCandTrkMatchEff_Loose_eta_pT[0], "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_0", "ZCandTrkMatchEff_NoTrkMatch_eta_pT_0");
  divide_hist2(*ZCandTrkMatchEff_Loose_eta_vtxz[0], "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_0", "ZCandTrkMatchEff_NoTrkMatch_eta_vtxz_0");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_pT[0], "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_0", "ZCandTrkMatchEff_NoTrkMatch_caleta_pT_0");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_vtxz[0], "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_0", "ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz_0");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_vtxz[0], "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_0", "ZCandTrkMatchEff_NoTrkMatch_etam_vtxz_0");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_vtxz[0], "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_0", "ZCandTrkMatchEff_NoTrkMatch_etap_vtxz_0");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_etap[0], "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_0", "ZCandTrkMatchEff_NoTrkMatch_etam_etap_0");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_etam[0], "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_0", "ZCandTrkMatchEff_NoTrkMatch_etap_etam_0");
  divide_hist2(*ZCandTrkMatchEff_Loose_upara_pz[0], "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_0", "ZCandTrkMatchEff_NoTrkMatch_upara_pz_0");

  divide_hist2(*ZCandTrkMatchEff_Loose_eta_pT[1], "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_1", "ZCandTrkMatchEff_NoTrkMatch_eta_pT_1");
  divide_hist2(*ZCandTrkMatchEff_Loose_eta_vtxz[1], "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_1", "ZCandTrkMatchEff_NoTrkMatch_eta_vtxz_1");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_pT[1], "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_1", "ZCandTrkMatchEff_NoTrkMatch_caleta_pT_1");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_vtxz[1], "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_1", "ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz_1");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_vtxz[1], "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_1", "ZCandTrkMatchEff_NoTrkMatch_etam_vtxz_1");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_vtxz[1], "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_1", "ZCandTrkMatchEff_NoTrkMatch_etap_vtxz_1");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_etap[1], "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_1", "ZCandTrkMatchEff_NoTrkMatch_etam_etap_1");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_etam[1], "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_1", "ZCandTrkMatchEff_NoTrkMatch_etap_etam_1");
  divide_hist2(*ZCandTrkMatchEff_Loose_upara_pz[1], "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_1", "ZCandTrkMatchEff_NoTrkMatch_upara_pz_1");

  divide_hist2(*ZCandTrkMatchEff_Loose_eta_pT[2], "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_2", "ZCandTrkMatchEff_NoTrkMatch_eta_pT_2");
  divide_hist2(*ZCandTrkMatchEff_Loose_eta_vtxz[2], "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_2", "ZCandTrkMatchEff_NoTrkMatch_eta_vtxz_2");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_pT[2], "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_2", "ZCandTrkMatchEff_NoTrkMatch_caleta_pT_2");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_vtxz[2], "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_2", "ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz_2");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_vtxz[2], "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_2", "ZCandTrkMatchEff_NoTrkMatch_etam_vtxz_2");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_vtxz[2], "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_2", "ZCandTrkMatchEff_NoTrkMatch_etap_vtxz_2");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_etap[2], "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_2", "ZCandTrkMatchEff_NoTrkMatch_etam_etap_2");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_etam[2], "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_2", "ZCandTrkMatchEff_NoTrkMatch_etap_etam_2");
  divide_hist2(*ZCandTrkMatchEff_Loose_upara_pz[2], "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_2", "ZCandTrkMatchEff_NoTrkMatch_upara_pz_2");

  divide_hist2(*ZCandTrkMatchEff_Loose_eta_pT[3], "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_3", "ZCandTrkMatchEff_NoTrkMatch_eta_pT_3");
  divide_hist2(*ZCandTrkMatchEff_Loose_eta_vtxz[3], "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_3", "ZCandTrkMatchEff_NoTrkMatch_eta_vtxz_3");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_pT[3], "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_3", "ZCandTrkMatchEff_NoTrkMatch_caleta_pT_3");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_vtxz[3], "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_3", "ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz_3");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_vtxz[3], "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_3", "ZCandTrkMatchEff_NoTrkMatch_etam_vtxz_3");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_vtxz[3], "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_3", "ZCandTrkMatchEff_NoTrkMatch_etap_vtxz_3");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_etap[3], "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_3", "ZCandTrkMatchEff_NoTrkMatch_etam_etap_3");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_etam[3], "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_3", "ZCandTrkMatchEff_NoTrkMatch_etap_etam_3");
  divide_hist2(*ZCandTrkMatchEff_Loose_upara_pz[3], "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_3", "ZCandTrkMatchEff_NoTrkMatch_upara_pz_3");

  divide_hist2(*ZCandTrkMatchEff_Loose_eta_pT[4], "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_4", "ZCandTrkMatchEff_NoTrkMatch_eta_pT_4");
  divide_hist2(*ZCandTrkMatchEff_Loose_eta_vtxz[4], "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_4", "ZCandTrkMatchEff_NoTrkMatch_eta_vtxz_4");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_pT[4], "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_4", "ZCandTrkMatchEff_NoTrkMatch_caleta_pT_4");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_vtxz[4], "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_4", "ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz_4");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_vtxz[4], "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_4", "ZCandTrkMatchEff_NoTrkMatch_etam_vtxz_4");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_vtxz[4], "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_4", "ZCandTrkMatchEff_NoTrkMatch_etap_vtxz_4");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_etap[4], "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_4", "ZCandTrkMatchEff_NoTrkMatch_etam_etap_4");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_etam[4], "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_4", "ZCandTrkMatchEff_NoTrkMatch_etap_etam_4");
  divide_hist2(*ZCandTrkMatchEff_Loose_upara_pz[4], "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_4", "ZCandTrkMatchEff_NoTrkMatch_upara_pz_4");

  divide_hist2(*ZCandTrkMatchEff_Loose_eta_pT[5], "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_5", "ZCandTrkMatchEff_NoTrkMatch_eta_pT_5");
  divide_hist2(*ZCandTrkMatchEff_Loose_eta_vtxz[5], "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_5", "ZCandTrkMatchEff_NoTrkMatch_eta_vtxz_5");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_pT[5], "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_5", "ZCandTrkMatchEff_NoTrkMatch_caleta_pT_5");
  divide_hist2(*ZCandTrkMatchEff_Loose_caleta_vtxz[5], "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_5", "ZCandTrkMatchEff_NoTrkMatch_caleta_vtxz_5");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_vtxz[5], "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_5", "ZCandTrkMatchEff_NoTrkMatch_etam_vtxz_5");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_vtxz[5], "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_5", "ZCandTrkMatchEff_NoTrkMatch_etap_vtxz_5");
  divide_hist2(*ZCandTrkMatchEff_Loose_etam_etap[5], "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_5", "ZCandTrkMatchEff_NoTrkMatch_etam_etap_5");
  divide_hist2(*ZCandTrkMatchEff_Loose_etap_etam[5], "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_5", "ZCandTrkMatchEff_NoTrkMatch_etap_etam_5");
  divide_hist2(*ZCandTrkMatchEff_Loose_upara_pz[5], "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_5", "ZCandTrkMatchEff_NoTrkMatch_upara_pz_5");

  // 2D Truth Loose Track Match Efficiency

  TH2D* ZCandTrueTrkMatchEff_Loose_eta_pT[6];
  TH2D* ZCandTrueTrkMatchEff_Loose_eta_vtxz[6];
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_pT[6];
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_vtxz[6];
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_vtxz[6];
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_vtxz[6];
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_etap[6];
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_etam[6];
  TH2D* ZCandTrueTrkMatchEff_Loose_upara_pz[6];

  TH2D* ZCandTrueTrkMatchEff_Loose_eta_pT[0] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_pT_0", "Loose Track Match Eff - eta vs pT - CCCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_eta_vtxz[0] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_vtxz_0", "Loose Track Match Eff - eta vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_pT[0] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_pT_0", "Loose Track Match Eff - Cal eta vs pT - CCCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_vtxz[0] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_vtxz_0", "Loose Track Match Eff - Cal eta vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_vtxz[0] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_vtxz_0", "Loose Track Match Eff - eta(-) vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_vtxz[0] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_vtxz_0", "Loose Track Match Eff - eta(+) vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_etap[0] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_etap_0", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - CCCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_etam[0] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_etam_0", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - CCCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_upara_pz[0] = new TH2D("ZCandTrueTrkMatchEff_Loose_upara_pz_0", "Loose Track Match Eff - upara vs pz - CCCC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrueTrkMatchEff_Loose_eta_pT[1] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_pT_1", "Loose Track Match Eff - eta vs pT - CCEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_eta_vtxz[1] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_vtxz_1", "Loose Track Match Eff - eta vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_pT[1] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_pT_1", "Loose Track Match Eff - Cal eta vs pT - CCEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_vtxz[1] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_vtxz_1", "Loose Track Match Eff - Cal eta vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_vtxz[1] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_vtxz_1", "Loose Track Match Eff - eta(-) vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_vtxz[1] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_vtxz_1", "Loose Track Match Eff - eta(+) vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_etap[1] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_etap_1", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - CCEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_etam[1] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_etam_1", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - CCEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_upara_pz[1] = new TH2D("ZCandTrueTrkMatchEff_Loose_upara_pz_1", "Loose Track Match Eff - upara vs pz - CCEC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrueTrkMatchEff_Loose_eta_pT[2] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_pT_2", "Loose Track Match Eff - eta vs pT - ECCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_eta_vtxz[2] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_vtxz_2", "Loose Track Match Eff - eta vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_pT[2] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_pT_2", "Loose Track Match Eff - Cal eta vs pT - ECCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_vtxz[2] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_vtxz_2", "Loose Track Match Eff - Cal eta vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_vtxz[2] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_vtxz_2", "Loose Track Match Eff - eta(-) vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_vtxz[2] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_vtxz_2", "Loose Track Match Eff - eta(+) vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_etap[2] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_etap_2", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - ECCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_etam[2] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_etam_2", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - ECCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_upara_pz[2] = new TH2D("ZCandTrueTrkMatchEff_Loose_upara_pz_2", "Loose Track Match Eff - upara vs pz - ECCC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrueTrkMatchEff_Loose_eta_pT[3] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_pT_3", "Loose Track Match Eff - eta vs pT - ECEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_eta_vtxz[3] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_vtxz_3", "Loose Track Match Eff - eta vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_pT[3] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_pT_3", "Loose Track Match Eff - Cal eta vs pT - ECEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_vtxz[3] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_vtxz_3", "Loose Track Match Eff - Cal eta vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_vtxz[3] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_vtxz_3", "Loose Track Match Eff - eta(-) vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_vtxz[3] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_vtxz_3", "Loose Track Match Eff - eta(+) vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_etap[3] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_etap_3", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - ECEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_etam[3] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_etam_3", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - ECEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_upara_pz[3] = new TH2D("ZCandTrueTrkMatchEff_Loose_upara_pz_3", "Loose Track Match Eff - upara vs pz - ECEC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrueTrkMatchEff_Loose_eta_pT[4] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_pT_4", "Loose Track Match Eff - eta vs pT - CC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_eta_vtxz[4] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_vtxz_4", "Loose Track Match Eff - eta vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_pT[4] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_pT_4", "Loose Track Match Eff - Cal eta vs pT - CC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_vtxz[4] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_vtxz_4", "Loose Track Match Eff - Cal eta vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_vtxz[4] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_vtxz_4", "Loose Track Match Eff - eta(-) vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_vtxz[4] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_vtxz_4", "Loose Track Match Eff - eta(+) vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_etap[4] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_etap_4", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - CC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_etam[4] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_etam_4", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - CC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_upara_pz[4] = new TH2D("ZCandTrueTrkMatchEff_Loose_upara_pz_4", "Loose Track Match Eff - upara vs pz - CC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrueTrkMatchEff_Loose_eta_pT[5] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_pT_5", "Loose Track Match Eff - eta vs pT - EC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_eta_vtxz[5] = new TH2D("ZCandTrueTrkMatchEff_Loose_eta_vtxz_5", "Loose Track Match Eff - eta vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_pT[5] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_pT_5", "Loose Track Match Eff - Cal eta vs pT - EC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Loose_caleta_vtxz[5] = new TH2D("ZCandTrueTrkMatchEff_Loose_caleta_vtxz_5", "Loose Track Match Eff - Cal eta vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_vtxz[5] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_vtxz_5", "Loose Track Match Eff - eta(-) vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_vtxz[5] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_vtxz_5", "Loose Track Match Eff - eta(+) vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etam_etap[5] = new TH2D("ZCandTrueTrkMatchEff_Loose_etam_etap_5", "Loose Track Match Eff - eta tag(-) vs eta probe(+) - EC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_etap_etam[5] = new TH2D("ZCandTrueTrkMatchEff_Loose_etap_etam_5", "Loose Track Match Eff - eta tag(+) vs eta probe(-) - EC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Loose_upara_pz[5] = new TH2D("ZCandTrueTrkMatchEff_Loose_upara_pz_5", "Loose Track Match Eff - upara vs pz - EC", 120, -30., 30., 400, -200., 200.);

  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_pT[0], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_0", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_vtxz[0], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_0", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_pT[0], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_0", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_vtxz[0], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_0", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_vtxz[0], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_0", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_vtxz[0], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_0", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_etap[0], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_0", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_etam[0], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_0", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_upara_pz[0], "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_0", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz_0");

  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_pT[1], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_1", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_vtxz[1], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_1", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_pT[1], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_1", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_vtxz[1], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_1", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_vtxz[1], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_1", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_vtxz[1], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_1", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_etap[1], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_1", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_etam[1], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_1", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_upara_pz[1], "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_1", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz_1");

  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_pT[2], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_2", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_vtxz[2], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_2", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_pT[2], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_2", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_vtxz[2], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_2", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_vtxz[2], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_2", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_vtxz[2], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_2", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_etap[2], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_2", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_etam[2], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_2", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_upara_pz[2], "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_2", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz_2");

  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_pT[3], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_3", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_vtxz[3], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_3", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_pT[3], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_3", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_vtxz[3], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_3", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_vtxz[3], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_3", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_vtxz[3], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_3", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_etap[3], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_3", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_etam[3], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_3", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_upara_pz[3], "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_3", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz_3");

  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_pT[4], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_4", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_vtxz[4], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_4", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_pT[4], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_4", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_vtxz[4], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_4", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_vtxz[4], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_4", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_vtxz[4], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_4", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_etap[4], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_4", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_etam[4], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_4", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_upara_pz[4], "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_4", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz_4");

  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_pT[5], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_5", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_pT_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_eta_vtxz[5], "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_5", "ZCandTrueTrkMatchEff_NoTrkMatch_eta_vtxz_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_pT[5], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_5", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_pT_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_caleta_vtxz[5], "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_5", "ZCandTrueTrkMatchEff_NoTrkMatch_caleta_vtxz_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_vtxz[5], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_5", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_vtxz_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_vtxz[5], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_5", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_vtxz_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etam_etap[5], "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_5", "ZCandTrueTrkMatchEff_NoTrkMatch_etam_etap_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_etap_etam[5], "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_5", "ZCandTrueTrkMatchEff_NoTrkMatch_etap_etam_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Loose_upara_pz[5], "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_5", "ZCandTrueTrkMatchEff_NoTrkMatch_upara_pz_5");

  // 2D Tag and Probe Tight Track Match Efficiency

  TH2D* ZCandTrkMatchEff_Tight_eta_pT[6];
  TH2D* ZCandTrkMatchEff_Tight_eta_vtxz[6];
  TH2D* ZCandTrkMatchEff_Tight_caleta_pT[6];
  TH2D* ZCandTrkMatchEff_Tight_caleta_vtxz[6];
  TH2D* ZCandTrkMatchEff_Tight_etam_vtxz[6];
  TH2D* ZCandTrkMatchEff_Tight_etap_vtxz[6];
  TH2D* ZCandTrkMatchEff_Tight_etam_etap[6];
  TH2D* ZCandTrkMatchEff_Tight_etap_etam[6];
  TH2D* ZCandTrkMatchEff_Tight_upara_pz[6];

  TH2D* ZCandTrkMatchEff_Tight_eta_pT[0] = new TH2D("ZCandTrkMatchEff_Tight_eta_pT_0", "Tight Track Match Eff - eta vs pT - CCCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_eta_vtxz[0] = new TH2D("ZCandTrkMatchEff_Tight_eta_vtxz_0", "Tight Track Match Eff - eta vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_pT[0] = new TH2D("ZCandTrkMatchEff_Tight_caleta_pT_0", "Tight Track Match Eff - Cal eta vs pT - CCCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_vtxz[0] = new TH2D("ZCandTrkMatchEff_Tight_caleta_vtxz_0", "Tight Track Match Eff - Cal eta vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_vtxz[0] = new TH2D("ZCandTrkMatchEff_Tight_etam_vtxz_0", "Tight Track Match Eff - eta(-) vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etap_vtxz[0] = new TH2D("ZCandTrkMatchEff_Tight_etap_vtxz_0", "Tight Track Match Eff - eta(+) vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_etap[0] = new TH2D("ZCandTrkMatchEff_Tight_etam_etap_0", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - CCCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_etap_etam[0] = new TH2D("ZCandTrkMatchEff_Tight_etap_etam_0", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - CCCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_upara_pz[0] = new TH2D("ZCandTrkMatchEff_Tight_upara_pz_0", "Tight Track Match Eff - upara vs pz - CCCC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrkMatchEff_Tight_eta_pT[1] = new TH2D("ZCandTrkMatchEff_Tight_eta_pT_1", "Tight Track Match Eff - eta vs pT - CCEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_eta_vtxz[1] = new TH2D("ZCandTrkMatchEff_Tight_eta_vtxz_1", "Tight Track Match Eff - eta vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_pT[1] = new TH2D("ZCandTrkMatchEff_Tight_caleta_pT_1", "Tight Track Match Eff - Cal eta vs pT - CCEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_vtxz[1] = new TH2D("ZCandTrkMatchEff_Tight_caleta_vtxz_1", "Tight Track Match Eff - Cal eta vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_vtxz[1] = new TH2D("ZCandTrkMatchEff_Tight_etam_vtxz_1", "Tight Track Match Eff - eta(-) vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etap_vtxz[1] = new TH2D("ZCandTrkMatchEff_Tight_etap_vtxz_1", "Tight Track Match Eff - eta(+) vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_etap[1] = new TH2D("ZCandTrkMatchEff_Tight_etam_etap_1", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - CCEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_etap_etam[1] = new TH2D("ZCandTrkMatchEff_Tight_etap_etam_1", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - CCEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_upara_pz[1] = new TH2D("ZCandTrkMatchEff_Tight_upara_pz_1", "Tight Track Match Eff - upara vs pz - CCEC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrkMatchEff_Tight_eta_pT[2] = new TH2D("ZCandTrkMatchEff_Tight_eta_pT_2", "Tight Track Match Eff - eta vs pT - ECCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_eta_vtxz[2] = new TH2D("ZCandTrkMatchEff_Tight_eta_vtxz_2", "Tight Track Match Eff - eta vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_pT[2] = new TH2D("ZCandTrkMatchEff_Tight_caleta_pT_2", "Tight Track Match Eff - Cal eta vs pT - ECCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_vtxz[2] = new TH2D("ZCandTrkMatchEff_Tight_caleta_vtxz_2", "Tight Track Match Eff - Cal eta vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_vtxz[2] = new TH2D("ZCandTrkMatchEff_Tight_etam_vtxz_2", "Tight Track Match Eff - eta(-) vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etap_vtxz[2] = new TH2D("ZCandTrkMatchEff_Tight_etap_vtxz_2", "Tight Track Match Eff - eta(+) vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_etap[2] = new TH2D("ZCandTrkMatchEff_Tight_etam_etap_2", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - ECCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_etap_etam[2] = new TH2D("ZCandTrkMatchEff_Tight_etap_etam_2", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - ECCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_upara_pz[2] = new TH2D("ZCandTrkMatchEff_Tight_upara_pz_2", "Tight Track Match Eff - upara vs pz - ECCC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrkMatchEff_Tight_eta_pT[3] = new TH2D("ZCandTrkMatchEff_Tight_eta_pT_3", "Tight Track Match Eff - eta vs pT - ECEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_eta_vtxz[3] = new TH2D("ZCandTrkMatchEff_Tight_eta_vtxz_3", "Tight Track Match Eff - eta vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_pT[3] = new TH2D("ZCandTrkMatchEff_Tight_caleta_pT_3", "Tight Track Match Eff - Cal eta vs pT - ECEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_vtxz[3] = new TH2D("ZCandTrkMatchEff_Tight_caleta_vtxz_3", "Tight Track Match Eff - Cal eta vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_vtxz[3] = new TH2D("ZCandTrkMatchEff_Tight_etam_vtxz_3", "Tight Track Match Eff - eta(-) vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etap_vtxz[3] = new TH2D("ZCandTrkMatchEff_Tight_etap_vtxz_3", "Tight Track Match Eff - eta(+) vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_etap[3] = new TH2D("ZCandTrkMatchEff_Tight_etam_etap_3", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - ECEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_etap_etam[3] = new TH2D("ZCandTrkMatchEff_Tight_etap_etam_3", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - ECEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_upara_pz[3] = new TH2D("ZCandTrkMatchEff_Tight_upara_pz_3", "Tight Track Match Eff - upara vs pz - ECEC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrkMatchEff_Tight_eta_pT[4] = new TH2D("ZCandTrkMatchEff_Tight_eta_pT_4", "Tight Track Match Eff - eta vs pT - CC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_eta_vtxz[4] = new TH2D("ZCandTrkMatchEff_Tight_eta_vtxz_4", "Tight Track Match Eff - eta vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_pT[4] = new TH2D("ZCandTrkMatchEff_Tight_caleta_pT_4", "Tight Track Match Eff - Cal eta vs pT - CC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_vtxz[4] = new TH2D("ZCandTrkMatchEff_Tight_caleta_vtxz_4", "Tight Track Match Eff - Cal eta vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_vtxz[4] = new TH2D("ZCandTrkMatchEff_Tight_etam_vtxz_4", "Tight Track Match Eff - eta(-) vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etap_vtxz[4] = new TH2D("ZCandTrkMatchEff_Tight_etap_vtxz_4", "Tight Track Match Eff - eta(+) vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_etap[4] = new TH2D("ZCandTrkMatchEff_Tight_etam_etap_4", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - CC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_etap_etam[4] = new TH2D("ZCandTrkMatchEff_Tight_etap_etam_4", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - CC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_upara_pz[4] = new TH2D("ZCandTrkMatchEff_Tight_upara_pz_4", "Tight Track Match Eff - upara vs pz - CC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrkMatchEff_Tight_eta_pT[5] = new TH2D("ZCandTrkMatchEff_Tight_eta_pT_5", "Tight Track Match Eff - eta vs pT - EC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_eta_vtxz[5] = new TH2D("ZCandTrkMatchEff_Tight_eta_vtxz_5", "Tight Track Match Eff - eta vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_pT[5] = new TH2D("ZCandTrkMatchEff_Tight_caleta_pT_5", "Tight Track Match Eff - Cal eta vs pT - EC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrkMatchEff_Tight_caleta_vtxz[5] = new TH2D("ZCandTrkMatchEff_Tight_caleta_vtxz_5", "Tight Track Match Eff - Cal eta vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_vtxz[5] = new TH2D("ZCandTrkMatchEff_Tight_etam_vtxz_5", "Tight Track Match Eff - eta(-) vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etap_vtxz[5] = new TH2D("ZCandTrkMatchEff_Tight_etap_vtxz_5", "Tight Track Match Eff - eta(+) vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrkMatchEff_Tight_etam_etap[5] = new TH2D("ZCandTrkMatchEff_Tight_etam_etap_5", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - EC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_etap_etam[5] = new TH2D("ZCandTrkMatchEff_Tight_etap_etam_5", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - EC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrkMatchEff_Tight_upara_pz[5] = new TH2D("ZCandTrkMatchEff_Tight_upara_pz_5", "Tight Track Match Eff - upara vs pz - EC", 120, -30., 30., 400, -200., 200.);

  divide_hist2(*ZCandTrkMatchEff_Tight_eta_pT[0], "ZCandTrkMatchEff_TightTrkMatch_eta_pT_0", "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_0");
  divide_hist2(*ZCandTrkMatchEff_Tight_eta_vtxz[0], "ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_0", "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_0");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_pT[0], "ZCandTrkMatchEff_TightTrkMatch_caleta_pT_0", "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_0");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_vtxz[0], "ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz_0", "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_0");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_vtxz[0], "ZCandTrkMatchEff_TightTrkMatch_etam_vtxz_0", "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_0");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_vtxz[0], "ZCandTrkMatchEff_TightTrkMatch_etap_vtxz_0", "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_0");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_etap[0], "ZCandTrkMatchEff_TightTrkMatch_etam_etap_0", "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_0");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_etam[0], "ZCandTrkMatchEff_TightTrkMatch_etap_etam_0", "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_0");
  divide_hist2(*ZCandTrkMatchEff_Tight_upara_pz[0], "ZCandTrkMatchEff_TightTrkMatch_upara_pz_0", "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_0");

  divide_hist2(*ZCandTrkMatchEff_Tight_eta_pT[1], "ZCandTrkMatchEff_TightTrkMatch_eta_pT_1", "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_1");
  divide_hist2(*ZCandTrkMatchEff_Tight_eta_vtxz[1], "ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_1", "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_1");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_pT[1], "ZCandTrkMatchEff_TightTrkMatch_caleta_pT_1", "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_1");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_vtxz[1], "ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz_1", "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_1");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_vtxz[1], "ZCandTrkMatchEff_TightTrkMatch_etam_vtxz_1", "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_1");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_vtxz[1], "ZCandTrkMatchEff_TightTrkMatch_etap_vtxz_1", "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_1");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_etap[1], "ZCandTrkMatchEff_TightTrkMatch_etam_etap_1", "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_1");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_etam[1], "ZCandTrkMatchEff_TightTrkMatch_etap_etam_1", "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_1");
  divide_hist2(*ZCandTrkMatchEff_Tight_upara_pz[1], "ZCandTrkMatchEff_TightTrkMatch_upara_pz_1", "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_1");

  divide_hist2(*ZCandTrkMatchEff_Tight_eta_pT[2], "ZCandTrkMatchEff_TightTrkMatch_eta_pT_2", "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_2");
  divide_hist2(*ZCandTrkMatchEff_Tight_eta_vtxz[2], "ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_2", "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_2");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_pT[2], "ZCandTrkMatchEff_TightTrkMatch_caleta_pT_2", "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_2");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_vtxz[2], "ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz_2", "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_2");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_vtxz[2], "ZCandTrkMatchEff_TightTrkMatch_etam_vtxz_2", "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_2");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_vtxz[2], "ZCandTrkMatchEff_TightTrkMatch_etap_vtxz_2", "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_2");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_etap[2], "ZCandTrkMatchEff_TightTrkMatch_etam_etap_2", "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_2");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_etam[2], "ZCandTrkMatchEff_TightTrkMatch_etap_etam_2", "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_2");
  divide_hist2(*ZCandTrkMatchEff_Tight_upara_pz[2], "ZCandTrkMatchEff_TightTrkMatch_upara_pz_2", "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_2");

  divide_hist2(*ZCandTrkMatchEff_Tight_eta_pT[3], "ZCandTrkMatchEff_TightTrkMatch_eta_pT_3", "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_3");
  divide_hist2(*ZCandTrkMatchEff_Tight_eta_vtxz[3], "ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_3", "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_3");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_pT[3], "ZCandTrkMatchEff_TightTrkMatch_caleta_pT_3", "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_3");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_vtxz[3], "ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz_3", "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_3");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_vtxz[3], "ZCandTrkMatchEff_TightTrkMatch_etam_vtxz_3", "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_3");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_vtxz[3], "ZCandTrkMatchEff_TightTrkMatch_etap_vtxz_3", "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_3");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_etap[3], "ZCandTrkMatchEff_TightTrkMatch_etam_etap_3", "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_3");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_etam[3], "ZCandTrkMatchEff_TightTrkMatch_etap_etam_3", "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_3");
  divide_hist2(*ZCandTrkMatchEff_Tight_upara_pz[3], "ZCandTrkMatchEff_TightTrkMatch_upara_pz_3", "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_3");

  divide_hist2(*ZCandTrkMatchEff_Tight_eta_pT[4], "ZCandTrkMatchEff_TightTrkMatch_eta_pT_4", "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_4");
  divide_hist2(*ZCandTrkMatchEff_Tight_eta_vtxz[4], "ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_4", "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_4");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_pT[4], "ZCandTrkMatchEff_TightTrkMatch_caleta_pT_4", "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_4");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_vtxz[4], "ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz_4", "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_4");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_vtxz[4], "ZCandTrkMatchEff_TightTrkMatch_etam_vtxz_4", "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_4");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_vtxz[4], "ZCandTrkMatchEff_TightTrkMatch_etap_vtxz_4", "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_4");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_etap[4], "ZCandTrkMatchEff_TightTrkMatch_etam_etap_4", "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_4");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_etam[4], "ZCandTrkMatchEff_TightTrkMatch_etap_etam_4", "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_4");
  divide_hist2(*ZCandTrkMatchEff_Tight_upara_pz[4], "ZCandTrkMatchEff_TightTrkMatch_upara_pz_4", "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_4");

  divide_hist2(*ZCandTrkMatchEff_Tight_eta_pT[5], "ZCandTrkMatchEff_TightTrkMatch_eta_pT_5", "ZCandTrkMatchEff_LooseTrkMatch_eta_pT_5");
  divide_hist2(*ZCandTrkMatchEff_Tight_eta_vtxz[5], "ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_5", "ZCandTrkMatchEff_LooseTrkMatch_eta_vtxz_5");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_pT[5], "ZCandTrkMatchEff_TightTrkMatch_caleta_pT_5", "ZCandTrkMatchEff_LooseTrkMatch_caleta_pT_5");
  divide_hist2(*ZCandTrkMatchEff_Tight_caleta_vtxz[5], "ZCandTrkMatchEff_TightTrkMatch_caleta_vtxz_5", "ZCandTrkMatchEff_LooseTrkMatch_caleta_vtxz_5");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_vtxz[5], "ZCandTrkMatchEff_TightTrkMatch_etam_vtxz_5", "ZCandTrkMatchEff_LooseTrkMatch_etam_vtxz_5");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_vtxz[5], "ZCandTrkMatchEff_TightTrkMatch_etap_vtxz_5", "ZCandTrkMatchEff_LooseTrkMatch_etap_vtxz_5");
  divide_hist2(*ZCandTrkMatchEff_Tight_etam_etap[5], "ZCandTrkMatchEff_TightTrkMatch_etam_etap_5", "ZCandTrkMatchEff_LooseTrkMatch_etam_etap_5");
  divide_hist2(*ZCandTrkMatchEff_Tight_etap_etam[5], "ZCandTrkMatchEff_TightTrkMatch_etap_etam_5", "ZCandTrkMatchEff_LooseTrkMatch_etap_etam_5");
  divide_hist2(*ZCandTrkMatchEff_Tight_upara_pz[5], "ZCandTrkMatchEff_TightTrkMatch_upara_pz_5", "ZCandTrkMatchEff_LooseTrkMatch_upara_pz_5");

  // 2D Truth Tight Track Match Efficiency

  TH2D* ZCandTrueTrkMatchEff_Tight_eta_pT[6];
  TH2D* ZCandTrueTrkMatchEff_Tight_eta_vtxz[6];
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_pT[6];
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_vtxz[6];
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_vtxz[6];
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_vtxz[6];
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_etap[6];
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_etam[6];
  TH2D* ZCandTrueTrkMatchEff_Tight_upara_pz[6];

  TH2D* ZCandTrueTrkMatchEff_Tight_eta_pT[0] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_pT_0", "Tight Track Match Eff - eta vs pT - CCCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_eta_vtxz[0] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_vtxz_0", "Tight Track Match Eff - eta vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_pT[0] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_pT_0", "Tight Track Match Eff - Cal eta vs pT - CCCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_vtxz[0] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_vtxz_0", "Tight Track Match Eff - Cal eta vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_vtxz[0] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_vtxz_0", "Tight Track Match Eff - eta(-) vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_vtxz[0] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_vtxz_0", "Tight Track Match Eff - eta(+) vs vtxz - CCCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_etap[0] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_etap_0", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - CCCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_etam[0] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_etam_0", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - CCCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_upara_pz[0] = new TH2D("ZCandTrueTrkMatchEff_Tight_upara_pz_0", "Tight Track Match Eff - upara vs pz - CCCC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrueTrkMatchEff_Tight_eta_pT[1] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_pT_1", "Tight Track Match Eff - eta vs pT - CCEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_eta_vtxz[1] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_vtxz_1", "Tight Track Match Eff - eta vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_pT[1] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_pT_1", "Tight Track Match Eff - Cal eta vs pT - CCEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_vtxz[1] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_vtxz_1", "Tight Track Match Eff - Cal eta vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_vtxz[1] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_vtxz_1", "Tight Track Match Eff - eta(-) vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_vtxz[1] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_vtxz_1", "Tight Track Match Eff - eta(+) vs vtxz - CCEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_etap[1] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_etap_1", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - CCEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_etam[1] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_etam_1", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - CCEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_upara_pz[1] = new TH2D("ZCandTrueTrkMatchEff_Tight_upara_pz_1", "Tight Track Match Eff - upara vs pz - CCEC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrueTrkMatchEff_Tight_eta_pT[2] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_pT_2", "Tight Track Match Eff - eta vs pT - ECCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_eta_vtxz[2] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_vtxz_2", "Tight Track Match Eff - eta vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_pT[2] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_pT_2", "Tight Track Match Eff - Cal eta vs pT - ECCC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_vtxz[2] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_vtxz_2", "Tight Track Match Eff - Cal eta vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_vtxz[2] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_vtxz_2", "Tight Track Match Eff - eta(-) vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_vtxz[2] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_vtxz_2", "Tight Track Match Eff - eta(+) vs vtxz - ECCC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_etap[2] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_etap_2", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - ECCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_etam[2] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_etam_2", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - ECCC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_upara_pz[2] = new TH2D("ZCandTrueTrkMatchEff_Tight_upara_pz_2", "Tight Track Match Eff - upara vs pz - ECCC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrueTrkMatchEff_Tight_eta_pT[3] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_pT_3", "Tight Track Match Eff - eta vs pT - ECEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_eta_vtxz[3] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_vtxz_3", "Tight Track Match Eff - eta vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_pT[3] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_pT_3", "Tight Track Match Eff - Cal eta vs pT - ECEC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_vtxz[3] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_vtxz_3", "Tight Track Match Eff - Cal eta vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_vtxz[3] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_vtxz_3", "Tight Track Match Eff - eta(-) vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_vtxz[3] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_vtxz_3", "Tight Track Match Eff - eta(+) vs vtxz - ECEC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_etap[3] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_etap_3", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - ECEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_etam[3] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_etam_3", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - ECEC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_upara_pz[3] = new TH2D("ZCandTrueTrkMatchEff_Tight_upara_pz_3", "Tight Track Match Eff - upara vs pz - ECEC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrueTrkMatchEff_Tight_eta_pT[4] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_pT_4", "Tight Track Match Eff - eta vs pT - CC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_eta_vtxz[4] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_vtxz_4", "Tight Track Match Eff - eta vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_pT[4] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_pT_4", "Tight Track Match Eff - Cal eta vs pT - CC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_vtxz[4] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_vtxz_4", "Tight Track Match Eff - Cal eta vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_vtxz[4] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_vtxz_4", "Tight Track Match Eff - eta(-) vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_vtxz[4] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_vtxz_4", "Tight Track Match Eff - eta(+) vs vtxz - CC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_etap[4] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_etap_4", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - CC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_etam[4] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_etam_4", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - CC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_upara_pz[4] = new TH2D("ZCandTrueTrkMatchEff_Tight_upara_pz_4", "Tight Track Match Eff - upara vs pz - CC", 120, -30., 30., 400, -200., 200.);

  TH2D* ZCandTrueTrkMatchEff_Tight_eta_pT[5] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_pT_5", "Tight Track Match Eff - eta vs pT - EC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_eta_vtxz[5] = new TH2D("ZCandTrueTrkMatchEff_Tight_eta_vtxz_5", "Tight Track Match Eff - eta vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_pT[5] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_pT_5", "Tight Track Match Eff - Cal eta vs pT - EC", 80, -4., 4., 100, 0., 100.);
  TH2D* ZCandTrueTrkMatchEff_Tight_caleta_vtxz[5] = new TH2D("ZCandTrueTrkMatchEff_Tight_caleta_vtxz_5", "Tight Track Match Eff - Cal eta vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_vtxz[5] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_vtxz_5", "Tight Track Match Eff - eta(-) vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_vtxz[5] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_vtxz_5", "Tight Track Match Eff - eta(+) vs vtxz - EC", 80, -4., 4., 320, -80., 80.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etam_etap[5] = new TH2D("ZCandTrueTrkMatchEff_Tight_etam_etap_5", "Tight Track Match Eff - eta tag(-) vs eta probe(+) - EC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_etap_etam[5] = new TH2D("ZCandTrueTrkMatchEff_Tight_etap_etam_5", "Tight Track Match Eff - eta tag(+) vs eta probe(-) - EC", 80, -4., 4., 80, -4., 4.);
  TH2D* ZCandTrueTrkMatchEff_Tight_upara_pz[5] = new TH2D("ZCandTrueTrkMatchEff_Tight_upara_pz_5", "Tight Track Match Eff - upara vs pz - EC", 120, -30., 30., 400, -200., 200.);

  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_pT[0], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_pT_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_vtxz[0], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_vtxz_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_pT[0], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_vtxz[0], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_vtxz[0], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_vtxz[0], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_etap[0], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_etam[0], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_0");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_upara_pz[0], "ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz_0", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_0");

  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_pT[1], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_pT_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_vtxz[1], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_vtxz_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_pT[1], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_vtxz[1], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_vtxz[1], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_vtxz[1], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_etap[1], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_etam[1], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_1");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_upara_pz[1], "ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz_1", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_1");

  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_pT[2], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_pT_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_vtxz[2], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_vtxz_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_pT[2], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_vtxz[2], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_vtxz[2], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_vtxz[2], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_etap[2], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_etam[2], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_2");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_upara_pz[2], "ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz_2", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_2");

  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_pT[3], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_pT_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_vtxz[3], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_vtxz_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_pT[3], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_vtxz[3], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_vtxz[3], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_vtxz[3], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_etap[3], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_etam[3], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_3");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_upara_pz[3], "ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz_3", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_3");

  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_pT[4], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_pT_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_vtxz[4], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_vtxz_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_pT[4], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_vtxz[4], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_vtxz[4], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_vtxz[4], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_etap[4], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_etam[4], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_4");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_upara_pz[4], "ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz_4", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_4");

  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_pT[5], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_pT_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_pT_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_eta_vtxz[5], "ZCandTrueTrkMatchEff_TightTrkMatch_eta_vtxz_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_eta_vtxz_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_pT[5], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_pT_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_pT_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_caleta_vtxz[5], "ZCandTrueTrkMatchEff_TightTrkMatch_caleta_vtxz_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_caleta_vtxz_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_vtxz[5], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_vtxz_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_vtxz_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_vtxz[5], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_vtxz_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_vtxz_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etam_etap[5], "ZCandTrueTrkMatchEff_TightTrkMatch_etam_etap_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_etam_etap_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_etap_etam[5], "ZCandTrueTrkMatchEff_TightTrkMatch_etap_etam_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_etap_etam_5");
  divide_hist2(*ZCandTrueTrkMatchEff_Tight_upara_pz[5], "ZCandTrueTrkMatchEff_TightTrkMatch_upara_pz_5", "ZCandTrueTrkMatchEff_LooseTrkMatch_upara_pz_5");

  // Now saves the histograms
  fullmc->Write();
  fullmc->Close();
}

void draw(TString filename) {

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(1,0);
  TFile* result = new TFile(filename,"read");
  result->cd("ZCand_Hist");
  TH1D *h1, *h2, *h3, *h4;
  TH2D *h5, *h6, *h7;
  TLegend *leg1 = new TLegend(0.7,0.83,0.95,0.93);
  leg1->SetFillColor(kWhite);

  /*
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h3->SetLineColor(6);
  h4->SetLineColor(8);
  */

  TCanvas* loose_eta = new TCanvas("loose_eta", "Loose TME - #eta", 595, 842);
  loose_eta->Divide(2,2);
  loose_eta->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_0");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_eta_0");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("#eta");
  h2->GetXaxis()->SetTitle("#eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_eta->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_eta_1");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("#eta");
  h2->GetXaxis()->SetTitle("#eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_eta->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_2");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_eta_2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("#eta");
  h2->GetXaxis()->SetTitle("#eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_eta->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_eta_3");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("#eta");
  h2->GetXaxis()->SetTitle("#eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_eta->Print("trkmatcheff.ps(");

  TCanvas* tight_eta = new TCanvas("tight_eta", "Tight TME - #eta", 595, 842);
  tight_eta->Divide(2,2);
  tight_eta->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_0");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_eta_0");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("#eta");
  h2->GetXaxis()->SetTitle("#eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_eta->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_eta_1");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("#eta");
  h2->GetXaxis()->SetTitle("#eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_eta->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_2");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_eta_2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("#eta");
  h2->GetXaxis()->SetTitle("#eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_eta->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_eta_3");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("#eta");
  h2->GetXaxis()->SetTitle("#eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_eta->Print("trkmatcheff.ps");

  TCanvas* loose_caleta = new TCanvas("loose_caleta", "Loose TME - Cal #eta", 595, 842);
  loose_caleta->Divide(2,2);
  loose_caleta->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_0");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_caleta_0");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Cal #eta");
  h2->GetXaxis()->SetTitle("Cal #eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_caleta->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_caleta_1");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Cal #eta");
  h2->GetXaxis()->SetTitle("Cal #eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_caleta->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_2");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_caleta_2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Cal #eta");
  h2->GetXaxis()->SetTitle("Cal #eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_caleta->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_caleta_3");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Cal #eta");
  h2->GetXaxis()->SetTitle("Cal #eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_caleta->Print("trkmatcheff.ps");

  TCanvas* tight_caleta = new TCanvas("tight_caleta", "Tight TME - Cal #eta", 595, 842);
  tight_caleta->Divide(2,2);
  tight_caleta->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_0");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_caleta_0");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Cal #eta");
  h2->GetXaxis()->SetTitle("Cal #eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_caleta->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_caleta_1");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Cal #eta");
  h2->GetXaxis()->SetTitle("Cal #eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_caleta->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_2");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_caleta_2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Cal #eta");
  h2->GetXaxis()->SetTitle("Cal #eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_caleta->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_caleta_3");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("Cal #eta");
  h2->GetXaxis()->SetTitle("Cal #eta");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_caleta->Print("trkmatcheff.ps");

  TCanvas* loose_pT = new TCanvas("loose_pT", "Loose TME - p_{T}", 595, 842);
  loose_pT->Divide(2,2);
  loose_pT->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_pT_0");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_pT_0");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("p_{T}");
  h2->GetXaxis()->SetTitle("p_{T}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_pT->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_pT_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_pT_1");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("p_{T}");
  h2->GetXaxis()->SetTitle("p_{T}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_pT->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_pT_2");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_pT_2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("p_{T}");
  h2->GetXaxis()->SetTitle("p_{T}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_pT->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_pT_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_pT_3");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("p_{T}");
  h2->GetXaxis()->SetTitle("p_{T}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_pT->Print("trkmatcheff.ps");

  TCanvas* tight_pT = new TCanvas("tight_pT", "Tight TME - p_{T}", 595, 842);
  tight_pT->Divide(2,2);
  tight_pT->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_pT_0");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_pT_0");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("p_{T}");
  h2->GetXaxis()->SetTitle("p_{T}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_pT->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_pT_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_pT_1");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("p_{T}");
  h2->GetXaxis()->SetTitle("p_{T}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_pT->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_pT_2");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_pT_2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("p_{T}");
  h2->GetXaxis()->SetTitle("p_{T}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_pT->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_pT_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_pT_3");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("p_{T}");
  h2->GetXaxis()->SetTitle("p_{T}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_pT->Print("trkmatcheff.ps");

  TCanvas* loose_upara = new TCanvas("loose_upara", "Loose TME - u_{#parallel}", 595, 842);
  loose_upara->Divide(2,2);
  loose_upara->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_upara_0");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_upara_0");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h2->GetXaxis()->SetTitle("u_{#parallel}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_upara->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_upara_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_upara_1");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h2->GetXaxis()->SetTitle("u_{#parallel}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_upara->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_upara_2");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_upara_2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h2->GetXaxis()->SetTitle("u_{#parallel}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_upara->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_upara_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_upara_3");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h2->GetXaxis()->SetTitle("u_{#parallel}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_upara->Print("trkmatcheff.ps");

  TCanvas* tight_upara = new TCanvas("tight_upara", "Tight TME - u_{#parallel}", 595, 842);
  tight_upara->Divide(2,2);
  tight_upara->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_upara_0");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_upara_0");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h2->GetXaxis()->SetTitle("u_{#parallel}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_upara->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_upara_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_upara_1");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h2->GetXaxis()->SetTitle("u_{#parallel}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_upara->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_upara_2");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_upara_2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h2->GetXaxis()->SetTitle("u_{#parallel}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_upara->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_upara_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_upara_3");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h2->GetXaxis()->SetTitle("u_{#parallel}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_upara->Print("trkmatcheff.ps");

  TCanvas* loose_vtxz = new TCanvas("loose_vtxz", "Loose TME - vtx_{z}", 595, 842);
  loose_vtxz->Divide(2,2);
  loose_vtxz->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_vtxz_0");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_vtxz_0");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("vtx_{z}");
  h2->GetXaxis()->SetTitle("vtx_{z}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_vtxz->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_vtxz_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_vtxz_1");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("vtx_{z}");
  h2->GetXaxis()->SetTitle("vtx_{z}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_vtxz->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_vtxz_2");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_vtxz_2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("vtx_{z}");
  h2->GetXaxis()->SetTitle("vtx_{z}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_vtxz->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_vtxz_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_vtxz_3");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("vtx_{z}");
  h2->GetXaxis()->SetTitle("vtx_{z}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  loose_vtxz->Print("trkmatcheff.ps");

  TCanvas* tight_vtxz = new TCanvas("tight_vtxz", "Tight TME - vtx_{z}", 595, 842);
  tight_vtxz->Divide(2,2);
  tight_vtxz->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_vtxz_0");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_vtxz_0");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("vtx_{z}");
  h2->GetXaxis()->SetTitle("vtx_{z}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_vtxz->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_vtxz_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_vtxz_1");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("vtx_{z}");
  h2->GetXaxis()->SetTitle("vtx_{z}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_vtxz->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_vtxz_2");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_vtxz_2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("vtx_{z}");
  h2->GetXaxis()->SetTitle("vtx_{z}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_vtxz->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_vtxz_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_vtxz_3");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->GetXaxis()->SetTitle("vtx_{z}");
  h2->GetXaxis()->SetTitle("vtx_{z}");
  h1->Draw();
  h2->Draw("same");
  leg1->Clear();
  leg1->AddEntry(h1,"Tag and Probe", "l");
  leg1->AddEntry(h2,"Truth", "l");
  leg1->Draw();
  tight_vtxz->Print("trkmatcheff.ps");

  TCanvas* vtxz_ratio = new TCanvas("vtxz_ratio", "vtxz ratio", 595, 842);
  vtxz_ratio->Divide(2,2);
  vtxz_ratio->cd(1)->SetGridx();
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_vtxz_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_vtxz_1");
  h3 = (TH1D*) h1->Clone();
  h3->Clear();
  h3->SetTitle("vtx_{z} truth/tag and probe ratio - Loose - CCEC");
  h3->GetXaxis()->SetTitle("vtx_{z}");
  h3->GetXaxis()->SetNdivisions(520);
  h3->GetXaxis()->SetLabelSize(0.03);
  h3->Divide(h2,h1);
  h3->Draw();
  vtxz_ratio->cd(2)->SetGridx();
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_vtxz_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_vtxz_3");
  h3 = (TH1D*) h1->Clone();
  h3->Clear();
  h3->SetTitle("vtx_{z} truth/tag and probe ratio - Loose - ECEC");
  h3->GetXaxis()->SetTitle("vtx_{z}");
  h3->GetXaxis()->SetNdivisions(520);
  h3->GetXaxis()->SetLabelSize(0.03);
  h3->Divide(h2,h1);
  h3->Draw();
  vtxz_ratio->cd(3)->SetGridx();
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_vtxz_1");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_vtxz_1");
  h3 = (TH1D*) h1->Clone();
  h3->Clear();
  h3->SetTitle("vtx_{z} truth/tag and probe ratio - Tight - CCEC");
  h3->GetXaxis()->SetTitle("vtx_{z}");
  h3->GetXaxis()->SetNdivisions(520);
  h3->GetXaxis()->SetLabelSize(0.03);
  h3->Divide(h2,h1);
  h3->Draw();
  vtxz_ratio->cd(4)->SetGridx();
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_vtxz_3");
  h2 = (TH1D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_vtxz_3");
  h3 = (TH1D*) h1->Clone();
  h3->Clear();
  h3->SetTitle("vtx_{z} truth/tag and probe ratio - Tight - ECEC");
  h3->GetXaxis()->SetTitle("vtx_{z}");
  h3->GetXaxis()->SetNdivisions(520);
  h3->GetXaxis()->SetLabelSize(0.03);
  h3->Divide(h2,h1);
  h3->Draw();
  vtxz_ratio->Print("trkmatcheff.ps");

  TCanvas* loose_eta_pT = new TCanvas("loose_eta_pT", "Loose TME - #eta x p_{T}", 595, 842);
  loose_eta_pT->Divide(2,2);
  loose_eta_pT->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_pT_0");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  loose_eta_pT->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_pT_1");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  loose_eta_pT->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_pT_2");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  loose_eta_pT->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_pT_3");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  loose_eta_pT->Print("trkmatcheff.ps");

  TCanvas* tight_eta_pT = new TCanvas("tight_eta_pT", "Tight TME - #eta x p_{T}", 595, 842);
  tight_eta_pT->Divide(2,2);
  tight_eta_pT->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_pT_0");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  tight_eta_pT->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_pT_1");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  tight_eta_pT->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_pT_2");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  tight_eta_pT->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_pT_3");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  tight_eta_pT->Print("trkmatcheff.ps");

  TCanvas* loose_eta_vtxz = new TCanvas("loose_eta_vtxz", "Loose TME - #eta x vtx_{z}", 595, 842);
  loose_eta_vtxz->Divide(2,2);
  loose_eta_vtxz->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_vtxz_0");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  loose_eta_vtxz->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_vtxz_1");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  loose_eta_vtxz->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_vtxz_2");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  loose_eta_vtxz->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_vtxz_3");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  loose_eta_vtxz->Print("trkmatcheff.ps");

  TCanvas* tight_eta_vtxz = new TCanvas("tight_eta_vtxz", "Tight TME - #eta x vtx_{z}", 595, 842);
  tight_eta_vtxz->Divide(2,2);
  tight_eta_vtxz->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_vtxz_0");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  tight_eta_vtxz->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_vtxz_1");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  tight_eta_vtxz->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_vtxz_2");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  tight_eta_vtxz->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_vtxz_3");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  tight_eta_vtxz->Print("trkmatcheff.ps");

  TCanvas* eta_vtxz_raio = new TCanvas("eta_vtxz_ratio", "Ratio truth/tag and probe - #eta x vtx_{z}", 595, 842);
  eta_vtxz_ratio->Divide(2,2);
  eta_vtxz_ratio->cd(1)->SetGrid();
  h5 = (TH2D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_vtxz_1");
  h6 = (TH2D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_eta_vtxz_1");
  h7 = (TH2D*) h5->Clone();
  h7->Clear();
  h7->SetTitle("#eta x vtx_{z} truth/tag and probe ratio - Loose - CCEC");
  h7->GetXaxis()->SetTitle("#eta");
  h7->GetYaxis()->SetTitle("vtx_{z}");
  h7->GetYaxis()->SetNdivisions(520);
  h7->GetYaxis()->SetLabelSize(0.03);
  h7->Divide(h6,h5);
  h7->Draw("colz");
  eta_vtxz_ratio->cd(2)->SetGrid();
  h5 = (TH2D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_vtxz_3");
  h6 = (TH2D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_eta_vtxz_3");
  h7 = (TH2D*) h5->Clone();
  h7->Clear();
  h7->SetTitle("#eta x vtx_{z} truth/tag and probe ratio - Loose - ECEC");
  h7->GetXaxis()->SetTitle("#eta");
  h7->GetYaxis()->SetTitle("vtx_{z}");
  h7->GetYaxis()->SetNdivisions(520);
  h7->GetYaxis()->SetLabelSize(0.03);
  h7->Divide(h6,h5);
  h7->Draw("colz");
  eta_vtxz_ratio->cd(3)->SetGrid();
  h5 = (TH2D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_vtxz_1");
  h6 = (TH2D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_eta_vtxz_1");
  h7 = (TH2D*) h5->Clone();
  h7->Clear();
  h7->SetTitle("#eta x vtx_{z} truth/tag and probe ratio - Tight - CCEC");
  h7->GetXaxis()->SetTitle("#eta");
  h7->GetYaxis()->SetTitle("vtx_{z}");
  h7->GetYaxis()->SetNdivisions(520);
  h7->GetYaxis()->SetLabelSize(0.03);
  h7->Divide(h6,h5);
  h7->Draw("colz");
  eta_vtxz_ratio->cd(4)->SetGrid();
  h5 = (TH2D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_vtxz_3");
  h6 = (TH2D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_eta_vtxz_3");
  h7 = (TH2D*) h5->Clone();
  h7->Clear();
  h7->SetTitle("#eta x vtx_{z} truth/tag and probe ratio - Tight - ECEC");
  h7->GetXaxis()->SetTitle("#eta");
  h7->GetYaxis()->SetTitle("vtx_{z}");
  h7->GetYaxis()->SetNdivisions(520);
  h7->GetYaxis()->SetLabelSize(0.03);
  h7->Divide(h6,h5);
  h7->Draw("colz");
  eta_vtxz_ratio->Print("trkmatcheff.ps");


  TCanvas* loose_caleta_pT = new TCanvas("loose_caleta_pT", "Loose TME - Cal #eta x p_{T}", 595, 842);
  loose_caleta_pT->Divide(2,2);
  loose_caleta_pT->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_pT_0");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  loose_caleta_pT->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_pT_1");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  loose_caleta_pT->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_pT_2");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  loose_caleta_pT->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_pT_3");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  loose_caleta_pT->Print("trkmatcheff.ps");

  TCanvas* tight_caleta_pT = new TCanvas("tight_caleta_pT", "Tight TME - Cal #eta x p_{T}", 595, 842);
  tight_caleta_pT->Divide(2,2);
  tight_caleta_pT->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_pT_0");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  tight_caleta_pT->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_pT_1");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  tight_caleta_pT->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_pT_2");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  tight_caleta_pT->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_pT_3");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("p_{T}");
  h1->Draw("colz");
  tight_caleta_pT->Print("trkmatcheff.ps");

  TCanvas* loose_caleta_vtxz = new TCanvas("loose_caleta_vtxz", "Loose TME - Cal #eta x vtx_{z}", 595, 842);
  loose_caleta_vtxz->Divide(2,2);
  loose_caleta_vtxz->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_vtxz_0");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  loose_caleta_vtxz->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_vtxz_1");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  loose_caleta_vtxz->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_vtxz_2");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  loose_caleta_vtxz->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_caleta_vtxz_3");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  loose_caleta_vtxz->Print("trkmatcheff.ps");

  TCanvas* tight_caleta_vtxz = new TCanvas("tight_caleta_vtxz", "Tight TME - Cal #eta x vtx_{z}", 595, 842);
  tight_caleta_vtxz->Divide(2,2);
  tight_caleta_vtxz->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_vtxz_0");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  tight_caleta_vtxz->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_vtxz_1");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  tight_caleta_vtxz->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_vtxz_2");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  tight_caleta_vtxz->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_caleta_vtxz_3");
  h1->GetXaxis()->SetTitle("Cal #eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  tight_caleta_vtxz->Print("trkmatcheff.ps");

  TCanvas* loose_upara_pz = new TCanvas("loose_upara_pz", "Loose TME - u_{#parallel} x W p_{z}", 595, 842);
  loose_upara_pz->Divide(2,2);
  loose_upara_pz->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_upara_pz_0");
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h1->GetYaxis()->SetTitle("W p_{z}");
  h1->Draw("colz");
  loose_upara_pz->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_upara_pz_1");
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h1->GetYaxis()->SetTitle("W p_{z}");
  h1->Draw("colz");
  loose_upara_pz->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_upara_pz_2");
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h1->GetYaxis()->SetTitle("W p_{z}");
  h1->Draw("colz");
  loose_upara_pz->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_upara_pz_3");
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h1->GetYaxis()->SetTitle("W p_{z}");
  h1->Draw("colz");
  loose_upara_pz->Print("trkmatcheff.ps");

  TCanvas* tight_upara_pz = new TCanvas("tight_upara_pz", "Tight TME - u_{#parallel} x W p_{z}", 595, 842);
  tight_upara_pz->Divide(2,2);
  tight_upara_pz->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_upara_pz_0");
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h1->GetYaxis()->SetTitle("W p_{z}");
  h1->Draw("colz");
  tight_upara_pz->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_upara_pz_1");
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h1->GetYaxis()->SetTitle("W p_{z}");
  h1->Draw("colz");
  tight_upara_pz->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_upara_pz_2");
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h1->GetYaxis()->SetTitle("W p_{z}");
  h1->Draw("colz");
  tight_upara_pz->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_upara_pz_3");
  h1->GetXaxis()->SetTitle("u_{#parallel}");
  h1->GetYaxis()->SetTitle("W p_{z}");
  h1->Draw("colz");
  tight_upara_pz->Print("trkmatcheff.ps");

  TCanvas* eta_vtxz = new TCanvas("eta_vtxz", "Loose and Tight TME - #eta x vtx_{z}", 595, 842);
  eta_vtxz->Divide(2,2);
  eta_vtxz->cd(1);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_vtxz_4");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  eta_vtxz->cd(2);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_vtxz_5");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  eta_vtxz->cd(3);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_vtxz_4");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  eta_vtxz->cd(4);
  h1 = (TH1D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_vtxz_5");
  h1->GetXaxis()->SetTitle("#eta");
  h1->GetYaxis()->SetTitle("vtx_{z}");
  h1->Draw("colz");
  eta_vtxz->Print("trkmatcheff.ps");

  TCanvas* eta_vtxz_raio = new TCanvas("eta_vtxz_ratio_total", "Ratio truth/tag and probe - #eta x vtx_{z}", 595, 842);
  eta_vtxz_ratio_total->Divide(2,2);
  eta_vtxz_ratio_total->cd(1)->SetGrid();
  h5 = (TH2D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_vtxz_4");
  h6 = (TH2D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_eta_vtxz_4");
  h7 = (TH2D*) h5->Clone();
  h7->Clear();
  h7->SetTitle("#eta x vtx_{z} truth/tag and probe ratio_total - Loose - CC");
  h7->GetXaxis()->SetTitle("#eta");
  h7->GetYaxis()->SetTitle("vtx_{z}");
  h7->GetYaxis()->SetNdivisions(520);
  h7->GetYaxis()->SetLabelSize(0.03);
  h7->Divide(h6,h5,1,4);
  h7->RebinX(2);
  h7->RebinY(2);
  h7->Draw("colz");
  eta_vtxz_ratio_total->cd(2)->SetGrid();
  h5 = (TH2D*) gROOT->FindObject("ZCandTrkMatchEff_Loose_eta_vtxz_5");
  h6 = (TH2D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Loose_eta_vtxz_5");
  h7 = (TH2D*) h5->Clone();
  h7->Clear();
  h7->SetTitle("#eta x vtx_{z} truth/tag and probe ratio_total - Loose - EC");
  h7->GetXaxis()->SetTitle("#eta");
  h7->GetYaxis()->SetTitle("vtx_{z}");
  h7->GetYaxis()->SetNdivisions(520);
  h7->GetYaxis()->SetLabelSize(0.03);
  h7->Divide(h6,h5,1,4);
  h7->RebinX(2);
  h7->RebinY(2);
  h7->Draw("colz");
  eta_vtxz_ratio_total->cd(3)->SetGrid();
  h5 = (TH2D*) gROOT->FindObject("ZCandTrkMatchEff_Tight_eta_vtxz_4");
  h6 = (TH2D*) gROOT->FindObject("ZCandTrueTrkMatchEff_Tight_eta_vtxz_4");
  h7 = (TH2D*) h5->Clone();
  h7->Clear();
  h7->SetTitle("#eta x vtx_{z} truth/tag and probe ratio_total - Tight - CC");
  h7->GetXaxis()->SetTitle("#eta");
  h7->GetYaxis()->SetTitle("vtx_{z}");
  h7->GetYaxis()->SetNdivisions(520);
  h7->GetYaxis()->SetLabelSize(0.03);
  h7->Divide(h6,h5,1,4);
  h7->RebinX(2);
  h7->RebinY(2);
  h7->Draw("colz");
  eta_vtxz_ratio_total->cd(4)->SetGrid();
  h5 = (TH2D*) gROOT->FindObject("ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_4");
  h6 = (TH2D*) gROOT->FindObject("ZCandTrkMatchEff_TightTrkMatch_eta_vtxz_5");
  h7 = (TH2D*) h5->Clone();
  h7->Clear();
  h7->SetTitle("#eta x vtx_{z} Total evt number");
  h7->GetXaxis()->SetTitle("#eta");
  h7->GetYaxis()->SetTitle("vtx_{z}");
  h7->GetYaxis()->SetNdivisions(520);
  h7->GetYaxis()->SetLabelSize(0.03);
  h7->Add(h6,h5,1,1);
  h7->Draw("colz");
  eta_vtxz_ratio_total->Print("trkmatcheff.ps)");

}
