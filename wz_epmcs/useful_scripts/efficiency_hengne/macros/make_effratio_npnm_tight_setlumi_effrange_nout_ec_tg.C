
{
  //d0Style->cd();

  TFile* fdt = new TFile("rootfiles/fiteff_npnm_data_tight_setlumi_effrange_nout_ec_tg.root");
  TFile* fmc = new TFile("rootfiles/effhists_npnm_fullmc_tight_setlumi_effrange_nout_ec_tg.root");
  TFile* fout = new TFile("rootfiles/effratio_npnm_tight_setlumi_effrange_nout_ec_tg.root", "recreate");

  TH2D* hmc_np = (TH2D*)fmc->Get("hnp");
  TH2D* hmc_nm = (TH2D*)fmc->Get("hnm");

  TH2D* hdt_np = (TH2D*)fdt->Get("hnp");
  TH2D* hdt_nm = (TH2D*)fdt->Get("hnm");


  const int nbinsx = hmc_np->GetNbinsX();
  const int nbinsy = hmc_np->GetNbinsY();
  double* binsx = hmc_np->GetXaxis()->GetXbins()->GetArray();
  double* binsy = hmc_np->GetYaxis()->GetXbins()->GetArray();

  // project to 1D
  TH1D* hmc_np_set = hmc_np->ProjectionX("hmc_np_set", 1, nbinsx, "e");
  TH1D* hmc_nm_set = hmc_nm->ProjectionX("hmc_nm_set", 1, nbinsx, "e");
  TH1D* hdt_np_set = hdt_np->ProjectionX("hdt_np_set", 1, nbinsx, "e");
  TH1D* hdt_nm_set = hdt_nm->ProjectionX("hdt_nm_set", 1, nbinsx, "e");
  TH1D* hmc_np_lumi = hmc_np->ProjectionY("hmc_np_lumi", 1, nbinsy, "e");
  TH1D* hmc_nm_lumi = hmc_nm->ProjectionY("hmc_nm_lumi", 1, nbinsy, "e");
  TH1D* hdt_np_lumi = hdt_np->ProjectionY("hdt_np_lumi", 1, nbinsy, "e");
  TH1D* hdt_nm_lumi = hdt_nm->ProjectionY("hdt_nm_lumi", 1, nbinsy, "e");

  // 2D efficiencies and ratios
  TH2D* hmc_eff_2d = new TH2D("hmc_eff_2d", "hmc_eff_2d", nbinsx, binsx, nbinsy, binsy);
  TH2D* hdt_eff_2d = new TH2D("hdt_eff_2d", "hdt_eff_2d", nbinsx, binsx, nbinsy, binsy);
  TH2D* hrt_eff_2d = new TH2D("hrt_eff_2d", "hrt_eff_2d", nbinsx, binsx, nbinsy, binsy);

  // 1D efficiencies and ratios
  TH1D* hmc_eff_set[nbinsy];
  TH1D* hdt_eff_set[nbinsy];
  TH1D* hrt_eff_set[nbinsy];
  TH1D* hmc_eff_lumi[nbinsx];
  TH1D* hdt_eff_lumi[nbinsx];
  TH1D* hrt_eff_lumi[nbinsx];
 

  for (int i=0; i<nbinsy; i++){
    char hname[100];
    sprintf(hname, "hmc_eff_set_%d", i);
    hmc_eff_set[i] = new TH1D(hname, hname, nbinsx, binsx);
    sprintf(hname, "hdt_eff_set_%d", i);
    hdt_eff_set[i] = new TH1D(hname, hname, nbinsx, binsx);
    sprintf(hname, "hrt_eff_set_%d", i);
    hrt_eff_set[i] = new TH1D(hname, hname, nbinsx, binsx);
  }

  for (int i=0; i<nbinsx; i++){
    char hname[100];
    sprintf(hname, "hmc_eff_lumi_%d", i);
    hmc_eff_lumi[i] = new TH1D(hname, hname, nbinsy, binsy);
    sprintf(hname, "hdt_eff_lumi_%d", i);
    hdt_eff_lumi[i] = new TH1D(hname, hname, nbinsy, binsy);
    sprintf(hname, "hrt_eff_lumi_%d", i);
    hrt_eff_lumi[i] = new TH1D(hname, hname, nbinsy, binsy);
  }

  // 1D total efficiencies and ratios
  TH1D* hmc_eff_set_1d = new TH1D("hmc_eff_set_1d", "hmc_eff_set_1d", nbinsx, binsx);
  TH1D* hdt_eff_set_1d = new TH1D("hdt_eff_set_1d", "hdt_eff_set_1d", nbinsx, binsx);
  TH1D* hrt_eff_set_1d = new TH1D("hrt_eff_set_1d", "hrt_eff_set_1d", nbinsx, binsx);
  TH1D* hmc_eff_lumi_1d = new TH1D("hmc_eff_lumi_1d", "hmc_eff_lumi_1d", nbinsy, binsy);
  TH1D* hdt_eff_lumi_1d = new TH1D("hdt_eff_lumi_1d", "hdt_eff_lumi_1d", nbinsy, binsy);
  TH1D* hrt_eff_lumi_1d = new TH1D("hrt_eff_lumi_1d", "hrt_eff_lumi_1d", nbinsy, binsy);

  // fill efficiencies
  // set&lumi correlated
  for (int i=0; i<nbinsx; i++){
    for (int j=0; j<nbinsy; j++){
      double np, nm, np_err, nm_err, eff, eff_err, eff_mc, eff_mc_err, eff_dt, eff_dt_err;
      // mc eff
      np = hmc_np->GetBinContent(i+1, j+1);
      np_err = hmc_np->GetBinError(i+1, j+1);
      nm = hmc_nm->GetBinContent(i+1, j+1);
      nm_err = hmc_nm->GetBinError(i+1, j+1);
      if (np+nm!=0) eff = np/(np+nm);
      else eff = 0.;
      if (np+nm!=0) eff_err = sqrt( pow(np_err,2.)*pow(nm,2.)/pow((np+nm), 4.) + pow(nm_err,2.)*pow(np,2.)/pow((np+nm), 4.) );
      else eff_err = 0.;
      eff_mc = eff;
      eff_mc_err = eff_err;  

      // dt eff
      np = hdt_np->GetBinContent(i+1, j+1);
      np_err = hdt_np->GetBinError(i+1, j+1);
      nm = hdt_nm->GetBinContent(i+1, j+1);
      nm_err = hdt_nm->GetBinError(i+1, j+1);
      if (np+nm!=0) eff = np/(np+nm);
      else eff = 0.;
      if (np+nm!=0) eff_err = sqrt( pow(np_err,2.)*pow(nm,2.)/pow((np+nm), 4.) + pow(nm_err,2.)*pow(np,2.)/pow((np+nm), 4.) );
      else eff_err = 0.;
      eff_dt = eff;
      eff_dt_err = eff_err;

      // ratio
      double ratio(0), ratio_err(0);
      if (eff_mc>0) {
        ratio = eff_dt/eff_mc;
        ratio_err = sqrt(eff_dt_err*eff_dt_err/(eff_mc*eff_mc) + eff_mc_err*eff_mc_err*eff_dt*eff_dt/pow(eff_mc, 4));
      }

      // fill hists
      // 2d
      hmc_eff_2d->SetBinContent(i+1, j+1, eff_mc);
      hmc_eff_2d->SetBinError(i+1, j+1, eff_mc_err);
      hdt_eff_2d->SetBinContent(i+1, j+1, eff_dt);
      hdt_eff_2d->SetBinError(i+1, j+1, eff_dt_err);
      hrt_eff_2d->SetBinContent(i+1, j+1, ratio);
      hrt_eff_2d->SetBinError(i+1, j+1, ratio_err);
      // 1d
      hmc_eff_set[j]->SetBinContent(i+1, eff_mc);
      hmc_eff_set[j]->SetBinError(i+1, eff_mc_err);
      hdt_eff_set[j]->SetBinContent(i+1, eff_dt);
      hdt_eff_set[j]->SetBinError(i+1, eff_dt_err);
      hrt_eff_set[j]->SetBinContent(i+1, ratio);
      hrt_eff_set[j]->SetBinError(i+1, ratio_err);
      hmc_eff_lumi[i]->SetBinContent(j+1, eff_mc);
      hmc_eff_lumi[i]->SetBinError(j+1, eff_mc_err);
      hdt_eff_lumi[i]->SetBinContent(j+1, eff_dt);
      hdt_eff_lumi[i]->SetBinError(j+1, eff_dt_err);
      hrt_eff_lumi[i]->SetBinContent(j+1, ratio);
      hrt_eff_lumi[i]->SetBinError(j+1, ratio_err);
  
    }
  }
  
  // fill total efficiencies
  // set
  for (int i=0; i<nbinsx; i++){
    double np, nm, np_err, nm_err, eff, eff_err, eff_mc, eff_mc_err, eff_dt, eff_dt_err;
    // mc eff
    np = hmc_np_set->GetBinContent(i+1);
    np_err = hmc_np_set->GetBinError(i+1);
    nm = hmc_nm_set->GetBinContent(i+1);
    nm_err = hmc_nm_set->GetBinError(i+1);
    if (np+nm!=0) eff = np/(np+nm);
    else eff = 0.;
    if (np+nm!=0) eff_err = sqrt( pow(np_err,2.)*pow(nm,2.)/pow((np+nm), 4.) + pow(nm_err,2.)*pow(np,2.)/pow((np+nm), 4.) );
    else eff_err = 0.;
    eff_mc = eff;
    eff_mc_err = eff_err;

    // dt eff
    np = hdt_np_set->GetBinContent(i+1);
    np_err = hdt_np_set->GetBinError(i+1);
    nm = hdt_nm_set->GetBinContent(i+1);
    nm_err = hdt_nm_set->GetBinError(i+1);
    if (np+nm!=0) eff = np/(np+nm);
    else eff = 0.;
    if (np+nm!=0) eff_err = sqrt( pow(np_err,2.)*pow(nm,2.)/pow((np+nm), 4.) + pow(nm_err,2.)*pow(np,2.)/pow((np+nm), 4.) );
    else eff_err = 0.;
    eff_dt = eff;
    eff_dt_err = eff_err;

    // ratio
    double ratio(0), ratio_err(0);
    if (eff_mc>0) {
      ratio = eff_dt/eff_mc;
      ratio_err = sqrt(eff_dt_err*eff_dt_err/(eff_mc*eff_mc) + eff_mc_err*eff_mc_err*eff_dt*eff_dt/pow(eff_mc, 4));
    }    
     
    // fill hists
    hmc_eff_set_1d->SetBinContent(i+1, eff_mc);
    hmc_eff_set_1d->SetBinError(i+1, eff_mc_err);
    hdt_eff_set_1d->SetBinContent(i+1, eff_dt);
    hdt_eff_set_1d->SetBinError(i+1, eff_dt_err);
    hrt_eff_set_1d->SetBinContent(i+1, ratio);
    hrt_eff_set_1d->SetBinError(i+1, ratio_err);

  }

  // lumi
  for (int i=0; i<nbinsy; i++){
    double np, nm, np_err, nm_err, eff, eff_err, eff_mc, eff_mc_err, eff_dt, eff_dt_err;
    // mc eff
    np = hmc_np_lumi->GetBinContent(i+1);
    np_err = hmc_np_lumi->GetBinError(i+1);
    nm = hmc_nm_lumi->GetBinContent(i+1);
    nm_err = hmc_nm_lumi->GetBinError(i+1);
    if (np+nm!=0) eff = np/(np+nm);
    else eff = 0.;
    if (np+nm!=0) eff_err = sqrt( pow(np_err,2.)*pow(nm,2.)/pow((np+nm), 4.) + pow(nm_err,2.)*pow(np,2.)/pow((np+nm), 4.) );
    else eff_err = 0.;
    eff_mc = eff;
    eff_mc_err = eff_err;

    // dt eff
    np = hdt_np_lumi->GetBinContent(i+1);
    np_err = hdt_np_lumi->GetBinError(i+1);
    nm = hdt_nm_lumi->GetBinContent(i+1);
    nm_err = hdt_nm_lumi->GetBinError(i+1);
    if (np+nm!=0) eff = np/(np+nm);
    else eff = 0.;
    if (np+nm!=0) eff_err = sqrt( pow(np_err,2.)*pow(nm,2.)/pow((np+nm), 4.) + pow(nm_err,2.)*pow(np,2.)/pow((np+nm), 4.) );
    else eff_err = 0.;
    eff_dt = eff;
    eff_dt_err = eff_err;

    // ratio
    double ratio(0), ratio_err(0);
    if (eff_mc>0) {
      ratio = eff_dt/eff_mc;
      ratio_err = sqrt(eff_dt_err*eff_dt_err/(eff_mc*eff_mc) + eff_mc_err*eff_mc_err*eff_dt*eff_dt/pow(eff_mc, 4));
    }

    // fill hists
    hmc_eff_lumi_1d->SetBinContent(i+1, eff_mc);
    hmc_eff_lumi_1d->SetBinError(i+1, eff_mc_err);
    hdt_eff_lumi_1d->SetBinContent(i+1, eff_dt);
    hdt_eff_lumi_1d->SetBinError(i+1, eff_dt_err);
    hrt_eff_lumi_1d->SetBinContent(i+1, ratio);
    hrt_eff_lumi_1d->SetBinError(i+1, ratio_err);

  }

  // makeups

  hrt_eff_lumi_1d->GetXaxis()->SetTitle("Lumi");
  hrt_eff_lumi_1d->GetYaxis()->SetTitle("Ratio Data/MC");
  hrt_eff_lumi_1d->GetYaxis()->SetRangeUser(0.5,1.2);
  hrt_eff_lumi_1d->SetMarkerStyle(20);
  hrt_eff_lumi_1d->SetMarkerSize(1);
  hrt_eff_lumi_1d->SetLineColor(1);
  hrt_eff_lumi_1d->SetMarkerColor(1);

  hrt_eff_set_1d->GetXaxis()->SetTitle("SET");
  hrt_eff_set_1d->GetYaxis()->SetTitle("Ratio Data/MC");
  hrt_eff_set_1d->GetYaxis()->SetRangeUser(0.5,1.2);
  hrt_eff_set_1d->SetMarkerStyle(20);
  hrt_eff_set_1d->SetMarkerSize(1);
  hrt_eff_set_1d->SetLineColor(1);
  hrt_eff_set_1d->SetMarkerColor(1);

  for (int i=0; i<nbinsx; i++){
    hrt_eff_lumi[i]->GetXaxis()->SetTitle("Lumi");
    hrt_eff_lumi[i]->GetYaxis()->SetTitle("Ratio Data/MC");
    hrt_eff_lumi[i]->GetYaxis()->SetRangeUser(0.5,1.2);
    hrt_eff_lumi[i]->SetMarkerStyle(20);
    hrt_eff_lumi[i]->SetMarkerSize(1);
    hrt_eff_lumi[i]->SetLineColor(i+2);
    hrt_eff_lumi[i]->SetMarkerColor(i+2);
  }

  for (int i=0; i<nbinsy; i++){
    hrt_eff_set[i]->GetXaxis()->SetTitle("SET");
    hrt_eff_set[i]->GetYaxis()->SetTitle("Ratio Data/MC");
    hrt_eff_set[i]->GetYaxis()->SetRangeUser(0.5,1.2);
    hrt_eff_set[i]->SetMarkerStyle(20);
    hrt_eff_set[i]->SetMarkerSize(1);
    hrt_eff_set[i]->SetLineColor(i+2);
    hrt_eff_set[i]->SetMarkerColor(i+2);
  }


  //
  TLegend* lg_rt_set = new TLegend(0.5, 0.5, 0.9, 0.9);
  lg_rt_set->AddEntry(hrt_eff_set_1d, "All", "pl");
  for (int i=0; i<nbinsy; i++){
    char name[50];
    sprintf(name, "Lumi: (%.1f,%.1f)", binsy[i], binsy[i+1]);
    lg_rt_set->AddEntry(hrt_eff_set[i], name, "pl"); 
  } 

  TLegend* lg_rt_lumi = new TLegend(0.5, 0.5, 0.9, 0.9);
  lg_rt_lumi->AddEntry(hrt_eff_lumi_1d, "All", "pl");
  for (int i=0; i<nbinsx; i++){
    char name[50]; 
    sprintf(name, "SET: (%.1f,%.1f)", binsx[i], binsx[i+1]);
    lg_rt_lumi->AddEntry(hrt_eff_lumi[i], name, "pl");
  } 

  // draw
  TCanvas* cset = new TCanvas("cset");
  hrt_eff_set_1d->Draw("PE");
  for (int i=0; i<nbinsy; i++){
    hrt_eff_set[i]->Draw("PESAME");
  }
  lg_rt_set->Draw("SAME");

  TCanvas* clumi = new TCanvas("clumi");
  hrt_eff_lumi_1d->Draw("PE");
  for (int i=0; i<nbinsx; i++){
    hrt_eff_lumi[i]->Draw("PESAME");
  }
  lg_rt_lumi->Draw("SAME");

  TCanvas* c2d = new TCanvas("c2d");
  hrt_eff_2d->Draw("colz");

//////
  fout->cd();
  fout->Write();  

}
