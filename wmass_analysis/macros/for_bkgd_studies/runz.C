{
gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");

TFile fz("~/samples/ztree_geant072710.root");
Int_t nbins =  30;	 //100;  //80;
Double_t xmin =20.0; //50;   //20.0;
Double_t xmax =80.0;//150;  //100.0;

TH1F *h = new TH1F("h","",nbins,xmin,xmax);
TH1F *h0 = new TH1F("h0","",nbins,xmin,xmax);
TH1F *h1 = new TH1F("h1","",nbins,xmin,xmax);
TH1F *h2 = new TH1F("h2","",nbins,xmin,xmax);

TH1F *h_e0 = new TH1F("h_e0","",nbins,xmin,xmax);
TH1F *h0_e0 = new TH1F("h0_e0","",nbins,xmin,xmax);
TH1F *h1_e0 = new TH1F("h1_e0","",nbins,xmin,xmax);
TH1F *h2_e0 = new TH1F("h2_e0","",nbins,xmin,xmax);

TH1F *h_e1 = new TH1F("h_e1","",nbins,xmin,xmax);
TH1F *h0_e1 = new TH1F("h0_e1","",nbins,xmin,xmax);
TH1F *h1_e1 = new TH1F("h1_e1","",nbins,xmin,xmax);
TH1F *h2_e1 = new TH1F("h2_e1","",nbins,xmin,xmax);

TH1F *hnum = new TH1F("hnum","",nbins,xmin,xmax);
TH1F *hden = new TH1F("hden","",nbins,xmin,xmax);
TH1F *heff = new TH1F("heff","",nbins,xmin,xmax);


TCut ept("pt[0]>25 && pt[1]>25");
TCut ecc("cc[0]==1 && cc[1]==1");
TCut eccfid("(ccphifidcal[0]==1 || (trkspat[0]==1 && ccphifidtrk[0]==1)) && (ccphifidcal[1]==1 || (trkspat[1]==1 && ccphifidtrk[1]==1))");
TCut emid("iso[0]<0.15 && iso[1]<0.15 && hm7[0]<12 && hm7[1]<12");
TCut etrkspat("trkspat[0]==1 && ccphifidtrk[0]==1 && trkspat[1]==1 && ccphifidtrk[1]==1");
TCut zmee("mee>70. && mee<110.");
TCut zut("zut<15");

TCut base(ept && ecc && eccfid && emid && etrkspat && zmee && zut);
/*
z->Draw("mee>>h",base);
z->Draw("mee>>h0", base && "trkgood[0]==0 && trkgood[1]==0");
z->Draw("mee>>h1", base && "((trkgood[0]==1 && trkgood[1]==0) || (trkgood[0]==0 && trkgood[1]==1))");
z->Draw("mee>>h2", base && "trkgood[0]==1 && trkgood[1]==1");
cout<<h0->Integral()<<endl;
cout<<h1->Integral()<<endl;
cout<<h2->Integral()<<endl;
cout<<h->Integral()<<endl;

67286
203466
672313
943065
*/
z->Draw("pt[0]>>h_e0",base);
z->Draw("pt[0]>>h0_e0", base && "trkgood[0]==0 && trkgood[1]==0");
z->Draw("pt[0]>>h1_e0", base && "((trkgood[0]==1 && trkgood[1]==0) || (trkgood[0]==0 && trkgood[1]==1))");
z->Draw("pt[0]>>h2_e0", base && "trkgood[0]==1 && trkgood[1]==1");
z->Draw("pt[1]>>h_e1",base);
z->Draw("pt[1]>>h0_e1", base && "trkgood[0]==0 && trkgood[1]==0");
z->Draw("pt[1]>>h1_e1", base && "((trkgood[0]==1 && trkgood[1]==0) || (trkgood[0]==0 && trkgood[1]==1))");
z->Draw("pt[1]>>h2_e1", base && "trkgood[0]==1 && trkgood[1]==1");

h->Add(h_e0,h_e1,1,1);
h0->Add(h0_e0,h0_e1,1,1);
h1->Add(h1_e0,h1_e1,1,1);
h2->Add(h2_e0,h2_e1,1,1);

hden = (TH1F *)h->Clone();//(N2+N1+N0)
hden->Scale(2.0);//x2

hnum = (TH1F *)h1->Clone();//N1
hnum->Add(h2,2);//+2N2

hnum->SetName("Numerator");
hden->SetName("Denominator");

heff = (TH1F *)hnum->Clone();
heff->SetName("Efficiency");

heff->Divide(hnum,hden,1,1);
SetBinomialErrors(nbins , (TH1F*)hnum, (TH1F*)hden, (TH1F*) heff);
heff->Draw();

}
