{
gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");

Int_t nbins = 50;
Double_t xmin = 0.0;
Double_t xmax = 100.0;

TH1F *den = new TH1F("den","den",nbins,xmin,xmax);
TH1F *num = new TH1F("num","num",nbins,xmin,xmax);
TH1F *rto = new TH1F("rto","rto",nbins,xmin,xmax);

TH1F *denmet15 = new TH1F("denmet15","denmet15",nbins,xmin,xmax);
TH1F *nummet15 = new TH1F("nummet15","nummet15",nbins,xmin,xmax);
TH1F *rtomet15 = new TH1F("rtomet15","rtomet15",nbins,xmin,xmax);

TH1F *denmet10 = new TH1F("denmet10","denmet10",nbins,xmin,xmax);
TH1F *nummet10 = new TH1F("nummet10","nummet10",nbins,xmin,xmax);
TH1F *rtomet10 = new TH1F("rtomet10","rtomet10",nbins,xmin,xmax);

TH1F *denmet8 = new TH1F("denmet8","denmet8",nbins,xmin,xmax);
TH1F *nummet8 = new TH1F("nummet8","nummet8",nbins,xmin,xmax);
TH1F *rtomet8 = new TH1F("rtomet8","rtomet8",nbins,xmin,xmax);

TH1F *denmet8ut35 = new TH1F("denmet8ut35","denmet8ut35",nbins,xmin,xmax);
TH1F *nummet8ut35 = new TH1F("nummet8ut35","nummet8ut35",nbins,xmin,xmax);
TH1F *rtomet8ut35 = new TH1F("rtomet8ut35","rtomet8ut35",nbins,xmin,xmax);

TH1F *denmet8meticd8 = new TH1F("denmet8meticd8","denmet8meticd8",nbins,xmin,xmax);
TH1F *nummet8meticd8 = new TH1F("nummet8meticd8","nummet8meticd8",nbins,xmin,xmax);
TH1F *rtomet8meticd8 = new TH1F("rtomet8meticd8","rtomet8meticd8",nbins,xmin,xmax);

TH1F *denmet5 = new TH1F("denmet5","denmet5",nbins,xmin,xmax);
TH1F *nummet5 = new TH1F("nummet5","nummet5",nbins,xmin,xmax);
TH1F *rtomet5 = new TH1F("rtomet5","rtomet5",nbins,xmin,xmax);

TH1F *denmet10zmassveto = new TH1F("denmet10zmassveto","denmet10zmassveto",nbins,xmin,xmax);
TH1F *nummet10zmassveto = new TH1F("nummet10zmassveto","nummet10zmassveto",nbins,xmin,xmax);
TH1F *rtomet10zmassveto = new TH1F("rtomet10zmassveto","rtomet10zmassveto",nbins,xmin,xmax);

TH1F *denmetgt25 = new TH1F("denmetgt25","denmetgt25",nbins,xmin,xmax);
TH1F *nummetgt25 = new TH1F("nummetgt25","nummetgt25",nbins,xmin,xmax);
TH1F *rtometgt25 = new TH1F("rtometgt25","rtometgt25",nbins,xmin,xmax);

rtometgt25->SetLineColor(2);
//rtomet10zmassveto->SetLineColor(2);

// TH1F *denmet10setlt200 = new TH1F("denmet10setlt200","denmet10setlt200",nbins,xmin,xmax);
// TH1F *nummet10setlt200 = new TH1F("nummet10setlt200","nummet10setlt200",nbins,xmin,xmax);
// TH1F *rtomet10setlt200 = new TH1F("rtomet10setlt200","rtomet10setlt200",nbins,xmin,xmax);
// 
// TH1F *denmet10setgt200 = new TH1F("denmet10setgt200","denmet10setgt200",nbins,xmin,xmax);
// TH1F *nummet10setgt200 = new TH1F("nummet10setgt200","nummet10setgt200",nbins,xmin,xmax);
// TH1F *rtomet10setgt200 = new TH1F("rtomet10setgt200","rtomet10setgt200",nbins,xmin,xmax);
// 
// TH1F *denmet10lumilt150 = new TH1F("denmet10lumilt150","denmet10lumilt150",nbins,xmin,xmax);
// TH1F *nummet10lumilt150 = new TH1F("nummet10lumilt150","nummet10lumilt150",nbins,xmin,xmax);
// TH1F *rtomet10lumilt150 = new TH1F("rtomet10lumilt150","rtomet10lumilt150",nbins,xmin,xmax);
// 
// TH1F *denmet10lumigt150 = new TH1F("denmet10lumigt150","denmet10lumigt150",nbins,xmin,xmax);
// TH1F *nummet10lumigt150 = new TH1F("nummet10lumigt150","nummet10lumigt150",nbins,xmin,xmax);
// TH1F *rtomet10lumigt150 = new TH1F("rtomet10lumigt150","rtomet10lumigt150",nbins,xmin,xmax);

// 
// rtomet10setlt200->SetLineColor(2);
// rtomet10setgt200->SetLineColor(3); 
// rtomet10lumilt150->SetLineColor(4); 
// rtomet10lumigt150->SetLineColor(9);

// denmet15->SetLineColor(2);
// nummet15->SetLineColor(2);
// rtomet15->SetLineColor(2);
// 
// denmet10->SetLineColor(3);
// nummet10->SetLineColor(3);
// rtomet10->SetLineColor(3);
// 
// denmet8->SetLineColor(4);
// nummet8->SetLineColor(4);
// rtomet8->SetLineColor(4);
// 
// nummet8ut35->SetLineColor(8);
// rtomet8ut35->SetLineColor(8);
// 
// denmet5->SetLineColor(5);
// nummet5->SetLineColor(5);
// rtomet5->SetLineColor(5);


//TCut met15("evtmeticd<15");
//TCut met10("evtmeticd<10");
//TCut met8("evtmeticd<8");
//TCut met5("evtmeticd<5");

TCut met15("evtmet<15");
TCut met10("evtmet<10");
TCut met8("evtmet<8");
TCut met5("evtmet<5");

TCut met8meticd8("evtmet<8 && evtmeticd<8");


TCut ejdeltaphi("ej_deltaphi>2.8");
TCut jgood("j_pt>20 && j_n90> 1 && j_emf>0.05 && j_emf<0.95 && j_chf<0.4 && j_hcr<10 && j_trks>=1 && (abs(j_deta)<0.8 || (abs(j_deta)>1.5 && abs(j_deta)<2.5))");
TCut jgoodnoptcut("j_n90> 1 && j_emf>0.05 && j_emf<0.95 && j_chf<0.4 && j_hcr<10 && j_trks>=1 && (abs(j_deta)<0.8 || (abs(j_deta)>1.5 && abs(j_deta)<2.5))");
TCut jgoodnoptnoetacut("j_n90> 1 && j_emf>0.05 && j_emf<0.95 && j_chf<0.4 && j_hcr<10 && j_trks>=1");


// 
// ej->Draw("e_pt>>denmet10setlt200", met10 && jgood && ejdeltaphi                      && "evtset<200.");
// ej->Draw("e_pt>>nummet10setlt200", met10 && jgood && ejdeltaphi && "e_goodspmtch==1" && "evtset<200.");
// 
// ej->Draw("e_pt>>denmet10setgt200", met10 && jgood && ejdeltaphi                      && "evtset>200.");
// ej->Draw("e_pt>>nummet10setgt200", met10 && jgood && ejdeltaphi && "e_goodspmtch==1" && "evtset>200.");
// 
// ej->Draw("e_pt>>denmet10lumilt150", met10 && jgood && ejdeltaphi                       && "lumi<150.");
// ej->Draw("e_pt>>nummet10lumilt150", met10 && jgood && ejdeltaphi && "e_goodspmtch==1"  && "lumi<150.");
// 
// ej->Draw("e_pt>>denmet10lumigt150", met10 && jgood && ejdeltaphi                      &&  "lumi>150.");
// ej->Draw("e_pt>>nummet10lumigt150", met10 && jgood && ejdeltaphi && "e_goodspmtch==1" &&  "lumi>150.");

//ej->Draw("e_pt>>denmet10zmassveto", met10 && jgood && ejdeltaphi					  &&  "!(ej_m>60 && ej_m<110)");
//ej->Draw("e_pt>>nummet10zmassveto", met10 && jgood && ejdeltaphi && "e_goodspmtch==1" &&  "!(ej_m>60 && ej_m<110)");

ej->Draw("e_pt>>denmetgt25", jgood && ejdeltaphi                      && "evtmet>25"  );
ej->Draw("e_pt>>nummetgt25", jgood && ejdeltaphi && "e_goodspmtch==1" && "evtmet>25"  );


ej->Draw("e_pt>>denmet10", met10 && jgood && ejdeltaphi );
ej->Draw("e_pt>>nummet10", met10 && jgood && ejdeltaphi && "e_goodspmtch==1");

// ej->Draw("e_pt>>den", jgood && ejdeltaphi );
// //1660648 entries
// ej->Draw("e_pt>>num", jgood && ejdeltaphi && "e_goodspmtch==1");
// //214852 entries
// 
// ej->Draw("e_pt>>denmet15", met15 && jgood && ejdeltaphi );
// ej->Draw("e_pt>>nummet15", met15 && jgood && ejdeltaphi && "e_goodspmtch==1");
// 
// 
// ej->Draw("e_pt>>denmet8", met8 && jgood && ejdeltaphi );
// ej->Draw("e_pt>>nummet8", met8 && jgood && ejdeltaphi && "e_goodspmtch==1");
// 
// ej->Draw("e_pt>>denmet8ut35", met8 && jgood && ejdeltaphi &&  "wcandut<35.");
// ej->Draw("e_pt>>nummet8ut35", met8 && jgood && ejdeltaphi && "e_goodspmtch==1" && "wcandut<35.");
// 
// ej->Draw("e_pt>>denmet8meticd8", met8meticd8 && jgood && ejdeltaphi );
// ej->Draw("e_pt>>nummet8meticd8", met8meticd8 && jgood && ejdeltaphi && "e_goodspmtch==1");
// 
// ej->Draw("e_pt>>denmet5", met5 && jgood && ejdeltaphi );
// ej->Draw("e_pt>>nummet5", met5 && jgood && ejdeltaphi && "e_goodspmtch==1");
// 
// // rto->Divide(num,den,1,1);
// // SetBinomialErrors(nbins , num, den,  rto);
// // 
// // rtomet15->Divide(nummet15,denmet15,1,1);
// // SetBinomialErrors(nbins , nummet15, denmet15,  rtomet15);
// // 


rtomet10->Divide(nummet10,denmet10,1,1);
SetBinomialErrors(nbins , nummet10, denmet10,  rtomet10);
rtometgt25->Divide(nummetgt25,denmetgt25,1,1);
SetBinomialErrors(nbins , nummetgt25, denmetgt25,  rtometgt25);

//rtomet10zmassveto->Divide(nummet10zmassveto,denmet10zmassveto,1,1);
//SetBinomialErrors(nbins , nummet10zmassveto, denmet10zmassveto,  rtomet10zmassveto);

// 
// rtomet10setlt200->Divide(nummet10setlt200,denmet10setlt200,1,1);
// SetBinomialErrors(nbins , nummet10setlt200, denmet10setlt200,  rtomet10setlt200);
// 
// rtomet10setgt200->Divide(nummet10setgt200,denmet10setgt200,1,1);
// SetBinomialErrors(nbins , nummet10setgt200, denmet10setgt200,  rtomet10setgt200);
// 
// rtomet10lumilt150->Divide(nummet10lumilt150,denmet10lumilt150,1,1);
// SetBinomialErrors(nbins , nummet10lumilt150, denmet10lumilt150,  rtomet10lumilt150);
// 
// rtomet10lumigt150->Divide(nummet10lumigt150,denmet10lumigt150,1,1);
// SetBinomialErrors(nbins , nummet10lumigt150, denmet10lumigt150,  rtomet10lumigt150);

// rtomet8->Divide(nummet8, denmet8,1,1);
// SetBinomialErrors(nbins, nummet8, denmet8,  rtomet8);
// rtomet8ut35->Divide(nummet8ut35, denmet8ut35,1,1);
// SetBinomialErrors(nbins, nummet8ut35, denmet8ut35,  rtomet8ut35);
// 
// 
// rtomet8meticd8->Divide(nummet8meticd8, denmet8meticd8,1,1);
// SetBinomialErrors(nbins, nummet8, denmet8meticd8,  rtomet8meticd8);
// 
// // rtomet5->Divide(nummet5,denmet5,1,1);
// // SetBinomialErrors(nbins , nummet5, denmet5,  rtomet5);

TCanvas *canv = new TCanvas("canv", "canv",8,8,600,400);
rtomet10->Draw(); 
rtometgt25->Draw("Sames"); 


//rtomet10zmassveto->Draw("Sames");

// rtomet10setlt200->Draw("Sames");
// rtomet10setgt200->Draw("Sames");
// rtomet10lumilt150->Draw("Sames");
// rtomet10lumigt150->Draw("Sames");

// TCanvas *canv = new TCanvas("canv", "canv",8,8,600,800);
// canv->Divide(1,3);
// 
// canv->cd(1);gPad->cd();
// rtomet8->Draw(); 
// rtomet8meticd8->Draw("Sames"); 
// rtomet8ut35->Draw("Sames"); 
// den->Draw(); denmet15->Draw("Sames"); denmet10->Draw("Sames"); denmet8->Draw("Sames"); denmet5->Draw("Sames");
// canv->cd(2);gPad->cd();
// num->Draw(); nummet15->Draw("Sames"); nummet10->Draw("Sames"); nummet8->Draw("Sames"); nummet5->Draw("Sames");
// canv->cd(3);gPad->cd();
// rto->Draw(); rtomet15->Draw("Sames"); rtomet10->Draw("Sames"); rtomet8->Draw("Sames"); rtomet5->Draw("Sames");

}
/*
TLegend *leg = new TLegend(0.5,0.2,0.7,0.4,NULL,"brNDC");
leg->AddEntry(rtomet10,"default","l");
leg->AddEntry(rtomet10setlt200,"SET < 200 GeV","l");
leg->AddEntry(rtomet10setgt200,"SET > 200 GeV","l");
leg->AddEntry(rtomet10lumilt150,"lumi < 150","l");
leg->AddEntry(rtomet10lumigt150,"lumi > 150","l");

leg->Draw("Sames");





*/
