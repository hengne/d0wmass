{
gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");

TH1::SetDefaultSumw2();
TH2::SetDefaultSumw2();

 TFile* fin1 = new TFile("/work/eddie-clued0/rominsky/run2b34_analysis/pmcs_output/20130308_1mev_taunu_cteq66_v1/result_wen.root");

 

 TFile* fin2 = new TFile("/work/eddie-clued0/rominsky/run2b34_analysis/pmcs_output/20130308_1mev_wenu_resbos_v1/result_wen.root");
 fin2->cd();
 fin2->cd("default");


 //define generator level numbers: 

 double tau_generated = 651239819;
 double electron_generated = 1000000000;

 double br_fraction = 0.1865; 
 TH1F *h_variation_up = new TH1F("h_variation_up","h_variation_up",100,80.33,80.44);
TH1F *h_variation_down = new TH1F("h_variation_down","h_variation_down",100,80.33,80.44);
 TH1F *h_wtaunu_pass;
 TH1F *h_wenu_pass;

 //read in the histograms for each mass point and get the integral 
 // define the integral as a variable
 // calculate tau_passed/tau_generated * wenu_generated/wenu_pass * br_fraction // plot for all mass points 0 - 100 (save to histogram)
 // add the uncertainty from the branching fraction uncertainty to plot
 //double wenu_pass[100];
 //double tau_pass[100];
 double bkgd_percent[100];
 double wmass_point[100];

 char name[1000];
 for(int i=0; i<100; i++){
   
   wmass_point[i] = 80.385 + (i-50)*0.001;
   cout<<"wmass_point "<<wmass_point[i]<<endl;
   fin1->cd();
   fin1->cd("default");
   sprintf(name,"hWcandMt_CC_%d",i);
   h_wtaunu_pass = (TH1F*) gDirectory->Get(name);
   double tau_pass = h_wtaunu_pass->Integral();
   cout<<"tau_pass "<<tau_pass<<endl;

   fin2->cd();
   fin2->cd("default");
   h_wenu_pass = (TH1F*) gDirectory->Get(name);
   double wenu_pass = h_wenu_pass->Integral();
   cout<<" wenu_pass "<<wenu_pass<<endl;

   double tau_fraction = tau_pass/tau_generated;
   double enu_fraction = wenu_pass/electron_generated;

   bkgd_percent[i] = (tau_fraction/enu_fraction)*br_fraction;
   
   cout<<"bkgd_faction "<<bkgd_percent[i]*100<<endl;
   h_variation_up->SetBinContent(i,bkgd_percent[i]+0.0004);
   h_variation_down->SetBinContent(i,bkgd_percent[i]-0.0004);

   
 }
 int i = 100;
 h1 = new TGraph(i,wmass_point,bkgd_percent);
 h1->SetMarkerStyle(20);
 h_variation_up->GetYaxis()->SetRangeUser(0.0167,0.0177);
 h_variation_up->SetMarkerColor(2);
 h_variation_up->SetMarkerStyle(20);
 h_variation_down->SetMarkerColor(2);
 h_variation_down->SetMarkerStyle(20);
 h_variation_up->Draw("p");
 h1->Draw("Psame");
 h_variation_down->Draw("samep");
}
 
