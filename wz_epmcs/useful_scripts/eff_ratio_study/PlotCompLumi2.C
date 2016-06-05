{
  TH1D* data_hist[4][5];
  TH1D* data_histb[4][5];
  TH1D* mc_hist[4][5];
  TH1D* mc_hist2[7][5];
  TH1D* data_hist2[7][5];
  TH1D* data_histb2[7][5];
  TFile *_file0 = TFile::Open("/rooms/surete/sahal/RunIIb/wz_epmcs/wz_epmcs/useful_scripts/eff_bkg_study/SET_eff_sahal/Lumi2/eff_plots.root");
  data_hist[0][0] = (TH1D*)gDirectory->Get("eff1dpt_ 0_ 0");
  data_hist[0][1] = (TH1D*)gDirectory->Get("eff1dpt_ 0_ 1");
  data_hist[0][2] = (TH1D*)gDirectory->Get("eff1dpt_ 0_ 2");
  data_hist[0][3] = (TH1D*)gDirectory->Get("eff1dpt_ 0_ 3");
  data_hist[0][4] = (TH1D*)gDirectory->Get("eff1dpt_ 0_ 4");
  data_hist[1][4] = (TH1D*)gDirectory->Get("eff1dpt_ 1_ 4");
  data_hist[1][3] = (TH1D*)gDirectory->Get("eff1dpt_ 1_ 3");
  data_hist[1][2] = (TH1D*)gDirectory->Get("eff1dpt_ 1_ 2");
  data_hist[1][1] = (TH1D*)gDirectory->Get("eff1dpt_ 1_ 1");
  data_hist[1][0] = (TH1D*)gDirectory->Get("eff1dpt_ 1_ 0");
  data_hist[2][0] = (TH1D*)gDirectory->Get("eff1dpt_ 2_ 0");
  data_hist[2][1] = (TH1D*)gDirectory->Get("eff1dpt_ 2_ 1");
  data_hist[2][2] = (TH1D*)gDirectory->Get("eff1dpt_ 2_ 2");
  data_hist[2][3] = (TH1D*)gDirectory->Get("eff1dpt_ 2_ 3");
  data_hist[2][4] = (TH1D*)gDirectory->Get("eff1dpt_ 2_ 4");
  data_hist[3][4] = (TH1D*)gDirectory->Get("eff1dpt_ 3_ 4");
  data_hist[3][3] = (TH1D*)gDirectory->Get("eff1dpt_ 3_ 3");
  data_hist[3][2] = (TH1D*)gDirectory->Get("eff1dpt_ 3_ 2");
  data_hist[3][1] = (TH1D*)gDirectory->Get("eff1dpt_ 3_ 1");
  data_hist[3][0] = (TH1D*)gDirectory->Get("eff1dpt_ 3_ 0");
  std::cout << "gets here" << std::endl;
  
  TFile *_file1 = TFile::Open("/prj_root/5007/wz2_write/sahal/wmass_analysis/Full_MC/zee_tree2/LumoutEff_Big3_a.root");
  mc_hist[0][0] =  (TH1D*)gDirectory->Get("eff1dpt_0_0_0");
  mc_hist[0][1] =  (TH1D*)gDirectory->Get("eff1dpt_0_0_1");
  mc_hist[0][2] =  (TH1D*)gDirectory->Get("eff1dpt_0_0_2");
  mc_hist[0][3] =  (TH1D*)gDirectory->Get("eff1dpt_0_0_3");
  mc_hist[0][4] =  (TH1D*)gDirectory->Get("eff1dpt_0_0_4");
  mc_hist[1][4] =  (TH1D*)gDirectory->Get("eff1dpt_1_0_4");
  mc_hist[1][3] =  (TH1D*)gDirectory->Get("eff1dpt_1_0_3");
  mc_hist[1][2] =  (TH1D*)gDirectory->Get("eff1dpt_1_0_2");
  mc_hist[1][1] =  (TH1D*)gDirectory->Get("eff1dpt_1_0_1");
  mc_hist[1][0] =  (TH1D*)gDirectory->Get("eff1dpt_1_0_0");
  mc_hist[2][0] =  (TH1D*)gDirectory->Get("eff1dpt_2_0_0");
  mc_hist[2][1] =  (TH1D*)gDirectory->Get("eff1dpt_2_0_1");
  mc_hist[2][2] =  (TH1D*)gDirectory->Get("eff1dpt_2_0_2");
  mc_hist[2][3] =  (TH1D*)gDirectory->Get("eff1dpt_2_0_3");
  mc_hist[2][4] =  (TH1D*)gDirectory->Get("eff1dpt_2_0_4");
  mc_hist[3][4] =  (TH1D*)gDirectory->Get("eff1dpt_3_0_4");
  mc_hist[3][3] =  (TH1D*)gDirectory->Get("eff1dpt_3_0_3");
  mc_hist[3][2] =  (TH1D*)gDirectory->Get("eff1dpt_3_0_2");
  mc_hist[3][1] =  (TH1D*)gDirectory->Get("eff1dpt_3_0_1");
  mc_hist[3][0] =  (TH1D*)gDirectory->Get("eff1dpt_3_0_0");


//   TFile *_file2 = TFile::Open("/rooms/surete/sahal/RunIIb/wz_epmcs/wz_epmcs/useful_scripts/eff_bkg_study/SET_eff_sahal/Lumi2/eff_plots.root");
//   data_histb[0][0] = (TH1D*)gDirectory->Get("eff1dpt_ 0_ 0");
//   data_histb[0][1] = (TH1D*)gDirectory->Get("eff1dpt_ 0_ 1");
//   data_histb[0][2] = (TH1D*)gDirectory->Get("eff1dpt_ 0_ 2");
//   data_histb[0][3] = (TH1D*)gDirectory->Get("eff1dpt_ 0_ 3");
//   data_histb[1][3] = (TH1D*)gDirectory->Get("eff1dpt_ 1_ 3");
//   data_histb[1][2] = (TH1D*)gDirectory->Get("eff1dpt_ 1_ 2");
//   data_histb[1][1] = (TH1D*)gDirectory->Get("eff1dpt_ 1_ 1");
//   data_histb[1][0] = (TH1D*)gDirectory->Get("eff1dpt_ 1_ 0");
//   data_histb[2][0] = (TH1D*)gDirectory->Get("eff1dpt_ 2_ 0");
//   data_histb[2][1] = (TH1D*)gDirectory->Get("eff1dpt_ 2_ 1");
//   data_histb[2][2] = (TH1D*)gDirectory->Get("eff1dpt_ 2_ 2");
//   data_histb[2][3] = (TH1D*)gDirectory->Get("eff1dpt_ 2_ 3");
//   data_histb[3][3] = (TH1D*)gDirectory->Get("eff1dpt_ 3_ 3");
//   data_histb[3][2] = (TH1D*)gDirectory->Get("eff1dpt_ 3_ 2");
//   data_histb[3][1] = (TH1D*)gDirectory->Get("eff1dpt_ 3_ 1");
//   data_histb[3][0] = (TH1D*)gDirectory->Get("eff1dpt_ 3_ 0");
//   std::cout << "gets here" << std::endl;

  char name[80];
  char title[80];

  Double_t setbins[] = {0,59,91,134,500};

  Double_t lumibins[] = {0,2.5,5.0,7.5,10.};
  
  for (Int_t iset =0; iset < 4; ++iset){
    for (Int_t ilum = 0; ilum < 5; ++ilum){
      for (Int_t ipt = 0; ipt < mc_hist[iset][ilum]->GetNbinsX(); ++ipt){
	if (ilum==4){
	  sprintf(name,"mceff1dset_%1.0f_%1.0f",ipt, ilum);
	  sprintf(title,"MC %1.0f < Pt < %1.0f, All Lum ",mc_hist[iset][ilum]->GetBinLowEdge(ipt+1),mc_hist[iset][ilum]->GetBinLowEdge(ipt+2));
	}
	else {
	  sprintf(name,"mceff1dset_%1.0f_%1.0f",ipt, ilum);
	  sprintf(title,"MC %1.0f < Pt < %1.0f, %1.0f < Lum < %1.0f ",mc_hist[iset][ilum]->GetBinLowEdge(ipt+1),mc_hist[iset][ilum]->GetBinLowEdge(ipt+2), lumibins[ilum], lumibins[ilum+1]);
	}
	if ((iset==0)){
	  mc_hist2[ipt][ilum] = new TH1D(name,"",4,setbins);
	  if (ilum==4){
	    sprintf(name,"dataeff1dset_%1.0f_%1.0f",ipt, ilum);
	    sprintf(title,"Data %1.0f < Pt < %1.0f, All Lumi ",mc_hist[iset][ilum]->GetBinLowEdge(ipt+1),mc_hist[iset][ilum]->GetBinLowEdge(ipt+2));
	  }
	  else{
	    sprintf(name,"dataeff1dset_%1.0f_%1.0f",ipt, ilum);
	    sprintf(title,"Data %1.0f < Pt < %1.0f, %1.0f < Lum < %1.0f ",mc_hist[iset][ilum]->GetBinLowEdge(ipt+1),mc_hist[iset][ilum]->GetBinLowEdge(ipt+2), lumibins[ilum], lumibins[ilum+1]);
	  }
	  data_hist2[ipt][ilum] = new TH1D(name,"",4,setbins);	
	  //data_histb2[ipt][ilum] = new TH1D(name,"",4,setbins);	
	}
	mc_hist2[ipt][ilum]->SetBinContent(iset+1,mc_hist[iset][ilum]->GetBinContent(ipt+1));
	mc_hist2[ipt][ilum]->SetBinError(iset+1, mc_hist[iset][ilum]->GetBinError(ipt+1));
	data_hist2[ipt][ilum]->SetBinContent(iset+1, data_hist[iset][ilum]->GetBinContent(ipt+1));
	data_hist2[ipt][ilum]->SetBinError(iset+1, data_hist[iset][ilum]->GetBinError(ipt+1));
	//data_histb2[ipt][ilum]->SetBinContent(iset+1, data_histb[iset][ilum]->GetBinContent(ipt+1));
	//data_histb2[ipt][ilum]->SetBinError(iset+1, data_histb[iset][ilum]->GetBinError(ipt+1));
	
      }
    }
  }

  std::cout << "gets here" << std::endl;
  TCanvas *can;
  for (Int_t iset =0; iset < 7; ++iset){
    can = new TCanvas();
    can->Divide(1,6);
    for (Int_t ilum = 0; ilum < 5; ++ilum){
      can->cd(ilum+1);
      std::cout << iset << "   " << ilum << std::endl;
      mc_hist2[iset][ilum]->GetYaxis()->SetRangeUser(0.4,1.1);
      mc_hist2[iset][ilum]->SetLineColor(2);
      mc_hist2[iset][ilum]->Draw();
      data_hist2[iset][ilum]->Draw("SAME");
      //data_histb2[iset][ilum]->SetLineColor(6);
      //data_histb2[iset][ilum]->Draw("SAME");
    }
    can->cd(5+1);
    for (Int_t ilum = 0; ilum < 5; ++ilum){
      mc_hist2[iset][ilum]->SetLineColor(ilum+2);
      if (ilum==0)
	mc_hist2[iset][ilum]->Draw();
      mc_hist2[iset][ilum]->Draw("SAME");
    }
    
  }


  


}
