{
  TH1D* denominator[3];
  TH1D* numerator[3];
  TH1D* numerator_all[3];
  TH1D* denominator_all;
  TH1D* denominator_both;

  int checks=0;

  TFile *data=new TFile("/prj_root/5007/wz2_write/sahal/wmass_analysis/DATA/EffAna_fix2/result.root");
  Eff_Hist->cd();
  denominator_both = (TH1D*)(gDirectory->Get("Pt_EM_Probe_Trig_All_Both"));
  char name[50]; 
  for (int i=5; i < 8; ++ i){
    sprintf(name,"Pt_EM_Probe_Trig_All_Triglist_%i",i);
    denominator[i-5] = (TH1D*)(gDirectory->Get(name));
  }
  denominator_all = (TH1D*)(gDirectory->Get("Pt_EM_Probe_Trig_All"));
 

  for (int i=5; i < 8; ++ i){
    sprintf(name,"Pt_EM_Probe_Trig_Matched_Triglist_%i",i);
    std::cout << "Getting " << name << std::endl;
    numerator[i-5] = (TH1D*)(gDirectory->Get(name));
    sprintf(name,"Pt_EM_Probe_Trig_Matched_%i_0",i);
    std::cout << "Getting " << name << std::endl;
    numerator_all[i-5] = (TH1D*)(gDirectory->Get(name));
  }
  TH1D*  v15all = (TH1D*)(gDirectory->Get("Pt_EM_Probe_Trig_Matched_v15")); // same as Pt_EM_Probe_Trig_Matched_5
  TH1D* v15only =   (TH1D*)(gDirectory->Get("Pt_EM_Probe_Trig_Matched_v15_0"));  // Require denominator_5
  TH1D*  v16_25all  =  (TH1D*)(gDirectory->Get("Pt_EM_Probe_Trig_Matched_v16_25")); // same as Pt_EM_Probe_Trig_Matched_6
  TH1D*  v16_25only = (TH1D*)(gDirectory->Get("Pt_EM_Probe_Trig_Matched_v16_25_0")); // Require denominator_6
  TH1D*  v16_27all = (TH1D*)(gDirectory->Get("Pt_EM_Probe_Trig_Matched_v16_27")); // same as Pt_EM_Probe_Trig_Matched_7
  TH1D*  v16_27only =  (TH1D*)(gDirectory->Get("Pt_EM_Probe_Trig_Matched_v16_27_0")); // Require denominator_6 + denominator_7
  TH1D*  num_both = (TH1D*)(gDirectory->Get("Pt_EM_Probe_Trig_Matched_v16_Both_0")); // use both_denominator
  
std::cout <<  checks << std::endl;
  if (checks){
    v15all->SetLineColor(2);
    v15all->Draw();
    numerator_all[0]->Draw("SAME");

    new TCanvas();
    
    v16_25all->SetLineColor(2);
    v16_25all->Draw();
    numerator_all[1]->Draw("SAME");

    new TCanvas();
    v16_27all->SetLineColor(2);
    v16_27all->Draw();
    numerator_all[2]->Draw("SAME");

    new TCanvas();
    v15only->SetLineColor(2);
    v15only->Draw();
    numerator[0]->Draw("SAME");

    new TCanvas();
    
    v16_25only->SetLineColor(2);
    v16_25only->Draw();
    numerator[1]->Draw("SAME");

    //  new TCanvas();
    // v16_27only->SetLineColor(2);
    //v16_27only->Draw();
    //numerator[2]->Draw("SAME");
  }
  else {
    TH1D *eff_v15all = (TH1D*)(v15only->Clone("eff_v15all"));
    eff_v15all->Clear();
    eff_v15all->SetName("eff_v15all");
    eff_v15all->SetName("v15 e1sht25 Efficiency using all events");

    TH1D *eff_v16_25all = (TH1D*)(v15only->Clone("eff_v16_25all"));
    eff_v16_25all->Clear();
    eff_v16_25all->SetName("eff_v16_25all");
    eff_v16_25all->SetName("v16 e1sht25 Efficiency using all events");


    TH1D *eff_v16_27all = (TH1D*)(v15only->Clone("eff_v16_27all"));
    eff_v16_27all->Clear();
    eff_v16_27all->SetName("eff_v16_27all");
    eff_v16_27all->SetName("v16 e1sht27 Efficiency using all events");


     TH1D *eff_v15 = (TH1D*)(v15only->Clone("eff_v15"));
    eff_v15->Clear();
    eff_v15->SetName("eff_v15all");
    eff_v15->SetName("v15 e1sht25 Efficiency");
    eff_v15->SetLineColor(2);
    TH1D *eff_v16_25 = (TH1D*)(v15only->Clone("eff_v16_25"));
    eff_v16_25->Clear();
    eff_v16_25->SetName("eff_v16_25");
    eff_v16_25->SetName("v16 e1sht25 Efficiency");
    eff_v16_25->SetLineColor(2);

    TH1D *eff_v16_27 = (TH1D*)(v15only->Clone("eff_v16_27"));
    eff_v16_27->Clear();
    eff_v16_27->SetName("eff_v16_27");
    eff_v16_27->SetName("v16 e1sht27 Efficiency");
    eff_v16_27->SetLineColor(2);
    std::cout << "Gets here" << std::endl;


    TF1 *func = new TF1("func","0.5 * [2] * (1. + TMath::Erf((x-[0])/(sqrt(2)*[1])))*(1. + TMath::Erf((x-[4])/(sqrt(2)*[3])))");
    
    

eff_v15all->Divide(numerator_all[0],denominator_all,1,1,"b");
    eff_v15->Divide(numerator[0],denominator[0],1,1,"b");
    eff_v15all->GetXaxis()->SetRangeUser(20.,60.);
    eff_v15->GetXaxis()->SetRangeUser(20.,60.);
    func->SetParameters(24.,0.6.,0.5.,18.9.,-7.);
    eff_v15->Fit(func,"GIM");
    eff_v15all->Draw();
    eff_v15->Draw("SAME");

    new TCanvas();
    eff_v16_25all->Divide(numerator_all[1],denominator_all,1,1,"b");
    eff_v16_25->Divide(numerator[1],denominator[1],1,1,"b");
    eff_v16_25all->GetXaxis()->SetRangeUser(20.,60.);
    eff_v16_25->GetXaxis()->SetRangeUser(20.,60.);
    func->SetParameters(24.,0.6.,0.5.,18.9.,-7.);
    eff_v16_25->Fit(func,"GIM");
    eff_v16_25all->Draw();
    eff_v16_25->Draw("SAME");

    new TCanvas();
    eff_v16_27all->Divide(numerator_all[2],denominator_all,1,1,"b");
    eff_v16_27->Divide(numerator[2],denominator[2],1,1,"b");
    eff_v16_27all->GetXaxis()->SetRangeUser(20.,60.);
    eff_v16_27->GetXaxis()->SetRangeUser(20.,60.);
    func->SetParameters(24.,0.6.,0.5.,18.9.,-7.);
    eff_v16_27->Fit(func,"GIM");
    eff_v16_27all->Draw();
    eff_v16_27->Draw("SAME");

  }

    
  
  // data->Close();
}
