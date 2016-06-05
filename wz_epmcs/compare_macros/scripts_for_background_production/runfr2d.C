{
gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");

TH1::SetDefaultSumw2();
TH2::SetDefaultSumw2();

Int_t nbins = 25;
Double_t xmin = 25.0;
Double_t xmax = 100.0;

// Int_t nbins = 30;
// Double_t xmin = 20.0;
// Double_t xmax = 80.0;

Int_t nbinseta = 10;
Double_t ymineta = -1.5;
Double_t ymaxeta = 1.5;


TCut met15("evtmet<15");
TCut met10("evtmet<10");
TCut met8("evtmet<8");
TCut met5("evtmet<5");
TCut met25("evtmet<25");
TCut met8meticd8("evtmet<8 && evtmeticd<8");


TCut ejdeltaphi("ej_deltaphi>2.8");
TCut jgood("j_pt>20 && j_n90> 1 && j_emf>0.05 && j_emf<0.95 && j_chf<0.4 && j_hcr<10 && j_trks>=1 && (abs(j_deta)<0.8 || (abs(j_deta)>1.5 && abs(j_deta)<2.5))");
TCut jgoodCC("j_pt>20 && j_n90> 1 && j_emf>0.05 && j_emf<0.95 && j_chf<0.4 && j_hcr<10 && j_trks>=1 && (abs(j_deta)<0.8)");

TCut jgoodnoptcut("j_n90> 1 && j_emf>0.05 && j_emf<0.95 && j_chf<0.4 && j_hcr<10 && j_trks>=1 && (abs(j_deta)<0.8 || (abs(j_deta)>1.5 && abs(j_deta)<2.5))");
TCut jgoodnoptnoetacut("j_n90> 1 && j_emf>0.05 && j_emf<0.95 && j_chf<0.4 && j_hcr<10 && j_trks>=1");

 TCut eleceta("abs(e_deta)<1.05");


 TCut goodspatialmatch("etrk_pt>10 && etrk_nsmt>=1 && etrk_prob>0.01");

 TCut trkpttrkprob("etrk_pt>10 && etrk_prob>0.01");
 TCut trkpttrksmt("etrk_pt>10 && etrk_nsmt>=1");
 TCut trksmttrkprob("etrk_nsmt>=1 && etrk_prob>0.01");

 TCut onlysmt("etrk_nsmt>=1");
TCut onlyprob("etrk_prob>0.01");
 TCut onlypt ("etrk_pt>10");


  TCut lumi("e_phimod>0.125 && e_phimod<0.875");

TH2D *nummet10zmassveto2d = new TH2D("nummet10zmassveto2d","nummet10zmassveto2d",nbinseta,ymineta,ymaxeta,nbins,xmin,xmax);

 TH2D *denmet10zmassveto2d = new TH2D("denmet10zmassveto2d","denmet10zmassveto2d",nbinseta,ymineta,ymaxeta,nbins,xmin,xmax);

TH2D *fr_2d = new TH2D("fr_2d","fr_2d",nbinseta,ymineta,ymaxeta,nbins,xmin,xmax);

 ej->Draw("e_pt:e_eta>>denmet10zmassveto2d", met10 && jgood && ejdeltaphi					  &&  "!(ej_m>60 && ej_m<110)" && eleceta,lumi);
 ej->Draw("e_pt:e_eta>>nummet10zmassveto2d", met10 && jgood && ejdeltaphi && "e_goodspmtch==1" &&  "!(ej_m>60 && ej_m<110)" && eleceta,lumi);

 //rtomet10zmassveto2d->Divide(nummet10zmassveto2d,denmet10zmassveto2d,1,1);

 //TH2D fr_2d = (TH2D*)nummet10zmassveto2d->Clone("fr_2d");
 int nbinsX = fr_2d->GetNbinsX();
 int nbinsY = fr_2d->GetNbinsY();
 for(int i = 0; i < nbinsX+1; i++){
   for(int j = 0 ; j< nbinsY+1;j++){
     double num, den, num_err,den_err,fakerate, fr_err;

     num = nummet10zmassveto2d->GetBinContent(i,j);
     num_err = nummet10zmassveto2d->GetBinError(i,j);
     den = denmet10zmassveto2d->GetBinContent(i,j);
     den_err = denmet10zmassveto2d->GetBinError(i,j);

     if (den != 0) fakerate = num/den;
     else fakerate = 0.1;
     if( den != 0) fr_err = sqrt( pow(num_err,2.)*pow(den,2.)/pow((den+num), 4.) + pow(den_err,2.)*pow(num,2.)/pow((den+num), 4.) );
     else fr_err = 0.1;

     fr_2d->SetBinContent(i,j,fakerate);

     cout<<" i "<< i <<" j "<<j<<" fakerate "<< fakerate<<endl;
     fr_2d->SetBinError(i,j,fr_err);
   }
 }
 
     

TCanvas *canv = new TCanvas("canv", "canv",8,8,600,400);
fHistFile = new TFile("hist_fr_pteta_run2b4_phimod75.root","RECREATE");
 fr_2d->Write("fr_2d");
 // rtomet10zmassveto2d_p
 fHistFile->cd();
  fHistFile->Write();
  fHistFile->Close();
  cout << "Output file written" << endl;

}
