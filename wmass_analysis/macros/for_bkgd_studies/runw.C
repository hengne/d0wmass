{ 
/*
TFile fW("/prj_root/5670/wmass1/alex/samples/wenu_newoverlay.root");
gDirectory->cd("WCand_Hist");
cout<<WCandElecPt_Spatial_Match_0->Integral()<<endl;
9.79328e+06
cout<<WCandElecPt_0->Integral()<<endl;
1.21963e+07
*/

gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");

gStyle->SetOptStat(0);

TFile fz("~/samples/wtree_geant072710.root");

TCut ept("pt>25");
TCut ecc("cc==1");
MAKE THINGS CAREFULLY
WITH PHIFID REQUIREMENT,
LOOK AT runz.C
TCut eccfid("(ccphifidtrk==1 || ccphifidcal==1)");
TCut emid("iso<0.15 && hm7<12");
TCut etrkspat("trkspat==1");
TCut etrkgood("trkgood==1");
TCut wmt("mt>50. && mt<200.");
TCut wmet("met>25.");
TCut wut("wut<15");

Int_t nbins = 80;
Double_t xmin = 20.0;
Double_t xmax = 100.0;

TH1F *h___________________________________= new TH1F("h___________________________________","",nbins,xmin,xmax);
TH1F *h_pt________________________________= new TH1F("h_pt________________________________","",nbins,xmin,xmax);
TH1F *h_pt_cc_____________________________= new TH1F("h_pt_cc_____________________________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_________________________= new TH1F("h_pt_cc_fid_________________________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mt______________________= new TH1F("h_pt_cc_fid_mt______________________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mt_met__________________= new TH1F("h_pt_cc_fid_mt_met__________________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mt_met_ut_______________= new TH1F("h_pt_cc_fid_mt_met_ut_______________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mt_met_ut_emid__________= new TH1F("h_pt_cc_fid_mt_met_ut_emid__________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mt_met_ut_emid_spat_____= new TH1F("h_pt_cc_fid_mt_met_ut_emid_spat_____","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mt_met_ut_emid_spat_good= new TH1F("h_pt_cc_fid_mt_met_ut_emid_spat_good","",nbins,xmin,xmax);

TH1F *h_loose=new TH1F("h_loose","",nbins,xmin,xmax);
TH1F *h_tight=new TH1F("h_tight","",nbins,xmin,xmax);

w->Draw("pt>>h___________________________________");																				 
w->Draw("pt>>h_pt________________________________",ept);
w->Draw("pt>>h_pt_cc_____________________________",ept && ecc);
w->Draw("pt>>h_pt_cc_fid_________________________",ept && ecc && eccfid);
w->Draw("pt>>h_pt_cc_fid_mt______________________",ept && ecc && eccfid && wmt);
w->Draw("pt>>h_pt_cc_fid_mt_met__________________",ept && ecc && eccfid && wmt && wmet);
w->Draw("pt>>h_pt_cc_fid_mt_met_ut_______________",ept && ecc && eccfid && wmt && wmet && wut);
w->Draw("pt>>h_pt_cc_fid_mt_met_ut_emid__________",ept && ecc && eccfid && wmt && wmet && wut && emid);
w->Draw("pt>>h_pt_cc_fid_mt_met_ut_emid_spat_____",ept && ecc && eccfid && wmt && wmet && wut && emid && etrkspat);
w->Draw("pt>>h_pt_cc_fid_mt_met_ut_emid_spat_good",ept && ecc && eccfid && wmt && wmet && wut && emid && etrkspat && etrkgood);

h_loose->Divide(h_pt_cc_fid_mt_met_ut_emid_spat_____,h_pt_cc_fid_mt_met_ut_emid__________,1,1);
h_tight->Divide(h_pt_cc_fid_mt_met_ut_emid_spat_good,h_pt_cc_fid_mt_met_ut_emid_spat_____,1,1);
SetBinomialErrors(nbins, h_pt_cc_fid_mt_met_ut_emid_spat_____, h_pt_cc_fid_mt_met_ut_emid__________, h_loose);
SetBinomialErrors(nbins, h_pt_cc_fid_mt_met_ut_emid_spat_good, h_pt_cc_fid_mt_met_ut_emid_spat_____, h_tight);

h___________________________________->SetLineColor(1);
h_pt________________________________->SetLineColor(2);
h_pt_cc_____________________________->SetLineColor(3);
h_pt_cc_fid_________________________->SetLineColor(4);
h_pt_cc_fid_mt______________________->SetLineColor(5);
h_pt_cc_fid_mt_met__________________->SetLineColor(6);
h_pt_cc_fid_mt_met_ut_______________->SetLineColor(7);
h_pt_cc_fid_mt_met_ut_emid__________->SetLineColor(8);
h_pt_cc_fid_mt_met_ut_emid_spat_____->SetLineColor(9);
h_pt_cc_fid_mt_met_ut_emid_spat_good->SetLineColor(12);

h___________________________________->SetMinimum(0.9);
h___________________________________->Draw();
h_pt________________________________->Draw("Same");
h_pt_cc_____________________________->Draw("Same");
h_pt_cc_fid_________________________->Draw("Same");
h_pt_cc_fid_mt______________________->Draw("Same");
h_pt_cc_fid_mt_met__________________->Draw("Same");
h_pt_cc_fid_mt_met_ut_______________->Draw("Same");
h_pt_cc_fid_mt_met_ut_emid__________->Draw("Same");
h_pt_cc_fid_mt_met_ut_emid_spat_____->Draw("Same");
h_pt_cc_fid_mt_met_ut_emid_spat_good->Draw("Same");

TLegend *leg1 = new TLegend(0.55,0.55,0.80,0.95,NULL,"brNDC");
leg1->SetBorderSize(0);
leg1->SetTextSize(0.035);

leg1->AddEntry(h___________________________________,"all","l");
leg1->AddEntry(h_pt________________________________,"pt","l");
leg1->AddEntry(h_pt_cc_____________________________,"pt_cc","l");
leg1->AddEntry(h_pt_cc_fid_________________________,"pt_cc_fid","l");
leg1->AddEntry(h_pt_cc_fid_mt______________________,"pt_cc_fid_mt","l");
leg1->AddEntry(h_pt_cc_fid_mt_met__________________,"pt_cc_fid_mt_met","l");
leg1->AddEntry(h_pt_cc_fid_mt_met_ut_______________,"pt_cc_fid_mt_met_ut","l");
leg1->AddEntry(h_pt_cc_fid_mt_met_ut_emid__________,"pt_cc_fid_mt_met_ut_emid","l");
leg1->AddEntry(h_pt_cc_fid_mt_met_ut_emid_spat_____,"pt_cc_fid_mt_met_ut_emid_spat","l");
leg1->AddEntry(h_pt_cc_fid_mt_met_ut_emid_spat_good,"pt_cc_fid_mt_met_ut_emid_spat_good","l");

leg1->Draw();

cout<<"*fid=fiducial* for CC events means: trkphiem3 or calphi outside phi-crack"<<endl;

/*
NEXT: can just divide the histograms made above to
from loosetrk and tighttrk efficiencies
BUT
should also form efficiencies as they are defined in the note
with 0, 1 and 2 trks,
they don't necessarily should agree
*/

}
