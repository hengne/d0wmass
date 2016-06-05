{
gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");
gStyle->SetOptStat(0);

TFile fz("~/samples/ztree_geant072710.root");

TCut ept("pt[0]>25 && pt[1]>25");
//--- standard cc and ccphifid cuts
TCut ecc("cc[0]==1 && cc[1]==1");
TCut eccfid("((ccphifidtrk[0]==1 && trkspat[0]==1) || ccphifidcal[0]==1) && ((ccphifidtrk[1]==1 && trkspat[1]==1) || ccphifidcal[1]==1)");
//---------------------------------
////--- W->enu-like cc and ccphifid cuts
//TCut ecc("cc[0]==1");
//TCut eccfid("((ccphifidtrk[0]==1 && trkspat[0]==1) || ccphifidcal[0]==1)");
////-------------------------------
TCut emid("iso[0]<0.15 && iso[1]<0.15 && hm7[0]<12 && hm7[1]<12");
TCut etrkspat("trkspat[0]==1 && ccphifidtrk[0]==1 && trkspat[1]==1 && ccphifidtrk[1]==1");
TCut etrkgood(etrkspat && "trkgood[0]==1 && trkgood[1]==1");
TCut zmee("mee>70. && mee<110.");
TCut zut("zut<15");

Int_t nbins = 80;
Double_t xmin = 20.0;
Double_t xmax = 100.0;

TH1F *h________________________________ = new TH1F("h________________________________","",nbins,xmin,xmax);
TH1F *h_pt_____________________________ = new TH1F("h_pt_____________________________","",nbins,xmin,xmax);
TH1F *h_pt_cc__________________________ = new TH1F("h_pt_cc__________________________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid______________________ = new TH1F("h_pt_cc_fid______________________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mee__________________ = new TH1F("h_pt_cc_fid_mee__________________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mee_ut_______________ = new TH1F("h_pt_cc_fid_mee_ut_______________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mee_ut_emid__________ = new TH1F("h_pt_cc_fid_mee_ut_emid__________","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mee_ut_emid_spat_____ = new TH1F("h_pt_cc_fid_mee_ut_emid_spat_____","",nbins,xmin,xmax);
TH1F *h_pt_cc_fid_mee_ut_emid_spat_good = new TH1F("h_pt_cc_fid_mee_ut_emid_spat_good","",nbins,xmin,xmax);
TH2F *h_pt_vs_eta= new TH2F("h_pt_vs_eta","",200,-1.5,1.5,200,25,65);
TH2F *h_e__vs_eta= new TH2F("h_e__vs_eta","",200,-1.5,1.5,200,30,80);


z->Draw("pt[0]>>h________________________________");																			  
z->Draw("pt[0]>>h_pt_____________________________",ept);
z->Draw("pt[0]>>h_pt_cc__________________________",ept && ecc);
z->Draw("pt[0]>>h_pt_cc_fid______________________",ept && ecc && eccfid);
z->Draw("pt[0]>>h_pt_cc_fid_mee__________________",ept && ecc && eccfid && zmee);
//---for wenulike selection
//z->Draw("pt[0]>>h_pt_cc_fid_mee_ut_______________",ept && ecc && eccfid && /*zmee &&*/ zut);
z->Draw("pt[0]>>h_pt_cc_fid_mee_ut_______________",ept && ecc && eccfid && zmee && zut);
z->Draw("pt[0]>>h_pt_cc_fid_mee_ut_emid__________",ept && ecc && eccfid && zmee && zut && emid);
z->Draw("pt[0]>>h_pt_cc_fid_mee_ut_emid_spat_____",ept && ecc && eccfid && zmee && zut && emid && etrkspat);
z->Draw("pt[0]>>h_pt_cc_fid_mee_ut_emid_spat_good",ept && ecc && eccfid && zmee && zut && emid && etrkspat && etrkgood);
z->Draw("pt[0]:eta[0]>>h_pt_vs_eta",ept && ecc && eccfid && zmee && zut && emid && etrkspat && etrkgood);
z->Draw("e[0]:eta[0]>>h_e__vs_eta" ,ept && ecc && eccfid && zmee && zut && emid && etrkspat && etrkgood);

z->Draw("pt[1]>>+h________________________________");																					 
z->Draw("pt[1]>>+h_pt_____________________________",ept);
z->Draw("pt[1]>>+h_pt_cc__________________________",ept && ecc);
z->Draw("pt[1]>>+h_pt_cc_fid______________________",ept && ecc && eccfid);
z->Draw("pt[1]>>+h_pt_cc_fid_mee__________________",ept && ecc && eccfid && zmee);
z->Draw("pt[1]>>+h_pt_cc_fid_mee_ut_______________",ept && ecc && eccfid && zmee && zut);
z->Draw("pt[1]>>+h_pt_cc_fid_mee_ut_emid__________",ept && ecc && eccfid && zmee && zut && emid);
z->Draw("pt[1]>>+h_pt_cc_fid_mee_ut_emid_spat_____",ept && ecc && eccfid && zmee && zut && emid && etrkspat);
z->Draw("pt[1]>>+h_pt_cc_fid_mee_ut_emid_spat_good",ept && ecc && eccfid && zmee && zut && emid && etrkspat && etrkgood);
z->Draw("pt[1]:eta[1]>>+h_pt_vs_eta",ept && ecc && eccfid && zmee && zut && emid && etrkspat && etrkgood);
z->Draw("e[1]:eta[1]>>+h_e__vs_eta" ,ept && ecc && eccfid && zmee && zut && emid && etrkspat && etrkgood);


h________________________________->SetLineColor(1);
h_pt_____________________________->SetLineColor(2);
h_pt_cc__________________________->SetLineColor(3);
h_pt_cc_fid______________________->SetLineColor(4);
h_pt_cc_fid_mee__________________->SetLineColor(5);
h_pt_cc_fid_mee_ut_______________->SetLineColor(6);
h_pt_cc_fid_mee_ut_emid__________->SetLineColor(7);
h_pt_cc_fid_mee_ut_emid_spat_____->SetLineColor(8);
h_pt_cc_fid_mee_ut_emid_spat_good->SetLineColor(9);

////--- for wenu-like case
//h_pt_cc_fid_mee_ut_______________->SetMinimum(0.5);
//h_pt_cc_fid_mee_ut_______________->Draw();

h________________________________->SetMinimum(0.5);
h________________________________->Draw();
h_pt_____________________________->Draw("Same");
h_pt_cc__________________________->Draw("Same");
h_pt_cc_fid______________________->Draw("Same");
h_pt_cc_fid_mee__________________->Draw("Same");
h_pt_cc_fid_mee_ut_______________->Draw("Same");
h_pt_cc_fid_mee_ut_emid__________->Draw("Same");
h_pt_cc_fid_mee_ut_emid_spat_____->Draw("Same");
h_pt_cc_fid_mee_ut_emid_spat_good->Draw("Same");

TLegend *leg1 = new TLegend(0.7,0.6,0.95,0.95,NULL,"brNDC");
leg1->SetBorderSize(0);
leg1->SetTextSize(0.035);

leg1->AddEntry(h________________________________,"all","l");
leg1->AddEntry(h_pt_____________________________,"pt","l");
leg1->AddEntry(h_pt_cc__________________________,"pt_cc","l");
leg1->AddEntry(h_pt_cc_fid______________________,"pt_cc_fid","l");
leg1->AddEntry(h_pt_cc_fid_mee__________________,"pt_cc_fid_mee","l");
leg1->AddEntry(h_pt_cc_fid_mee_ut_______________,"pt_cc_fid_mee_ut","l");
leg1->AddEntry(h_pt_cc_fid_mee_ut_emid__________,"pt_cc_fid_mee_ut_emid","l");
leg1->AddEntry(h_pt_cc_fid_mee_ut_emid_spat_____,"pt_cc_fid_mee_ut_emid_spat","l");
leg1->AddEntry(h_pt_cc_fid_mee_ut_emid_spat_good,"pt_cc_fid_mee_ut_emid_spat_good","l");
leg1->Draw();

cout<<"*fid=fiducial* for CC events means:"<<endl;
cout<<"trkphiem3(in case of loose track match) or calphi outside phi-crack"<<endl;

}
