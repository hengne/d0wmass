/*

-rw-r--r--  1 melnit wmass1 7260082 May 14 11:48 zeefullmc_ZA0trksEffLOOSETRKtag.root
-rw-r--r--  1 melnit wmass1 6813990 May 14 11:52 zeefullmc_ZA0trksEffDEFAULTTIGHTTRKtagUT15.root
-rw-r--r--  1 melnit wmass1 7260186 May 14 11:52 ???zeefullmc_ZA0trksEffDEFAULTTIGHTTRKtag.root
-rw-r--r--  1 melnit wmass1 7209912 May 18 20:56 zeefullmc_ZA0trksEffDEFAULTTIGHTTRKtagAGAIN051810.root

-rw-r--r--  1 melnit wmass1 7221565 May 14 11:52 zeefullmc_ZA0trksEffCALOtag.root
-rw-r--r--  1 melnit wmass1 5870024 May 14 11:53 zeedata_ZA0trksEffDEFAULTTIGHTTRKtagUT15.root
-rw-r--r--  1 melnit wmass1 7321632 May 14 12:09 zeefullmc_ZA0trksDROPUT15EffDEFAULTTIGHTTRKtag.root

*/


																															 																																 
{

TH1 *hVar0;
TH1 *hVar1;
TH1 *hVar2;
TH1 *hVar012;
TH1 *hVar2x2;
TH1 *hVar012x2;
TH1 *hnum;
TH1 *hden;

TH1 *hratio;

TH1 *hnumTP;
TH1 *hdenTP;
TH1 *hratioTP;

TH1 *hnumTPWITHUTCUT;
TH1 *hdenTPWITHUTCUT;
TH1 *hratioTPWITHUTCUT;

TH1 *hdenTLOOSETRKP;
TH1 *hnumTLOOSETRKP;
TH1 *hratioTLOOSETRKP;

TH1 *hnumTLOOSETRKANDCALP;
TH1 *hdenTLOOSETRKANDCALP;
TH1 *hratioTLOOSETRKANDCALP;

TH2 *hdenTCALP_tmp_2D;
TH2 *hnumTCALP_tmp_2D;
TH1 *hdenTCALP;
TH1 *hnumTCALP;
TH1 *hratioTCALP;

TH1 *hnumTCCONLYPNOTRIG;
TH1 *hdenTCCONLYPNOTRIG;
TH1 *hratioTCCONLYPNOTRIG;

TH1 *hdenTCCONLYPTAGTRIGMATCH;
TH1 *hnumTCCONLYPTAGTRIGMATCH;
TH1 *hratioTCCONLYPTAGTRIGMATCH;

TH1 *hdenTCCONLYPEITHERTRIGMATCH;
TH1 *hnumTCCONLYPEITHERTRIGMATCH;
TH1 *hratioTCCONLYPEITHERTRIGMATCH;



gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");


TCanvas *canv = new TCanvas("canv", "canv",8,8,400, 400);



//TFile fTP("/prj_root/5670/wmass1/alex/samples/MAY5_default.root");
//TFile fTP("/prj_root/5670/wmass1/alex/samples/MAY5_nozutcut_rev_inclectag_tgmatcheither.root");
TFile fTP("/prj_root/5670/wmass1/alex/samples/zeefullmc_ZA0trksEffDEFAULTTIGHTTRKtagAGAIN051810.root");




gDirectory->cd("Eff_Hist");

hdenTP=ZMass_vs_Pt_Before_Trk_CC->ProjectionX();
hnumTP=ZMass_vs_Pt_After_Trk_CC->ProjectionX();
hdenTP->Rebin(2);
hnumTP->Rebin(2);
hratioTP = (TH1F *)hnumTP->Clone();
hratioTP->SetName("EfficiencyTP");

hratioTP->Divide(hnumTP,hdenTP,1,1);
SetBinomialErrors(50/*100*//*400*/ , (TH1F*)hnumTP, (TH1F*)hdenTP, (TH1F*) hratioTP);

TFile fTPWITHUTCUT("/prj_root/5670/wmass1/alex/samples/zeefullmc_ZA0trksEffDEFAULTTIGHTTRKtagUT15.root");
gDirectory->cd("Eff_Hist");
hdenTPWITHUTCUT=ZMass_vs_Pt_Before_Trk_CC->ProjectionX();
hnumTPWITHUTCUT=ZMass_vs_Pt_After_Trk_CC->ProjectionX();
hdenTPWITHUTCUT->Rebin(2);
hnumTPWITHUTCUT->Rebin(2);
hratioTPWITHUTCUT = (TH1F *)hnumTPWITHUTCUT->Clone();
hratioTPWITHUTCUT->SetName("EfficiencyTPWITHUTCUT");
hratioTPWITHUTCUT->Divide(hnumTPWITHUTCUT,hdenTPWITHUTCUT,1,1);
SetBinomialErrors(50/*100*//*400*/ , (TH1F*)hnumTPWITHUTCUT, (TH1F*)hdenTPWITHUTCUT, (TH1F*) hratioTPWITHUTCUT);
 
// TFile fTCCONLYPNOTRIG("/prj_root/5670/wmass1/alex/samples/MAY5_nozutcut_rev_cctagonly_no_trigger.root");
// gDirectory->cd("Eff_Hist");
// hdenTCCONLYPNOTRIG=ZMass_vs_Pt_Before_Trk_CC->ProjectionX();
// hnumTCCONLYPNOTRIG=ZMass_vs_Pt_After_Trk_CC->ProjectionX();
// hdenTCCONLYPNOTRIG->Rebin(2);
// hnumTCCONLYPNOTRIG->Rebin(2);
// hratioTCCONLYPNOTRIG = (TH1F *)hnumTCCONLYPNOTRIG->Clone();
// hratioTCCONLYPNOTRIG->SetName("EfficiencyTCCONLYPNOTRIG");
// hratioTCCONLYPNOTRIG->Divide(hnumTCCONLYPNOTRIG,hdenTCCONLYPNOTRIG,1,1);
// SetBinomialErrors(50/*100*//*400*/ , (TH1F*)hnumTCCONLYPNOTRIG, (TH1F*)hdenTCCONLYPNOTRIG, (TH1F*) hratioTCCONLYPNOTRIG);
// 
// TFile fTCCONLYPTAGTRIGMATCH("/prj_root/5670/wmass1/alex/samples/MAY5_nozutcut_rev_cctagonly_tgmatchtag.root");
// gDirectory->cd("Eff_Hist");
// hdenTCCONLYPTAGTRIGMATCH=ZMass_vs_Pt_Before_Trk_CC->ProjectionX();
// hnumTCCONLYPTAGTRIGMATCH=ZMass_vs_Pt_After_Trk_CC->ProjectionX();
// hdenTCCONLYPTAGTRIGMATCH->Rebin(2);
// hnumTCCONLYPTAGTRIGMATCH->Rebin(2);
// hratioTCCONLYPTAGTRIGMATCH = (TH1F *)hnumTCCONLYPTAGTRIGMATCH->Clone();
// hratioTCCONLYPTAGTRIGMATCH->SetName("EfficiencyTCCONLYPTAGTRIGMATCH");
// hratioTCCONLYPTAGTRIGMATCH->Divide(hnumTCCONLYPTAGTRIGMATCH,hdenTCCONLYPTAGTRIGMATCH,1,1);
// SetBinomialErrors(50/*100*//*400*/ , (TH1F*)hnumTCCONLYPTAGTRIGMATCH, (TH1F*)hdenTCCONLYPTAGTRIGMATCH, (TH1F*) hratioTCCONLYPTAGTRIGMATCH);
// 
// 
// TFile fTCCONLYPEITHERTRIGMATCH("/prj_root/5670/wmass1/alex/samples/MAY5_nozutcut_rev_cctagonly_tgmatcheither.root");
// gDirectory->cd("Eff_Hist");
// hdenTCCONLYPEITHERTRIGMATCH=ZMass_vs_Pt_Before_Trk_CC->ProjectionX();
// hnumTCCONLYPEITHERTRIGMATCH=ZMass_vs_Pt_After_Trk_CC->ProjectionX();
// hdenTCCONLYPEITHERTRIGMATCH->Rebin(2);
// hnumTCCONLYPEITHERTRIGMATCH->Rebin(2);
// hratioTCCONLYPEITHERTRIGMATCH = (TH1F *)hnumTCCONLYPEITHERTRIGMATCH->Clone();
// hratioTCCONLYPEITHERTRIGMATCH->SetName("EfficiencyTCCONLYPEITHERTRIGMATCH");
// hratioTCCONLYPEITHERTRIGMATCH->Divide(hnumTCCONLYPEITHERTRIGMATCH,hdenTCCONLYPEITHERTRIGMATCH,1,1);
// SetBinomialErrors(50/*100*//*400*/ , (TH1F*)hnumTCCONLYPEITHERTRIGMATCH, (TH1F*)hdenTCCONLYPEITHERTRIGMATCH, (TH1F*) hratioTCCONLYPEITHERTRIGMATCH);
// 
// 
// 



// TFile fTLOOSETRKANDCALP("/prj_root/5670/wmass1/alex/samples/MAY5_default_tagiscalobased.root");
// gDirectory->cd("Eff_Hist");
// hdenTLOOSETRKANDCALP=ZMass_vs_Pt_Before_Trk_CC->ProjectionX();
// hnumTLOOSETRKANDCALP=ZMass_vs_Pt_After_Trk_CC->ProjectionX();
// hdenTLOOSETRKANDCALP->Rebin(2);
// hnumTLOOSETRKANDCALP->Rebin(2);
// hratioTLOOSETRKANDCALP = (TH1F *)hnumTLOOSETRKANDCALP->Clone();
// hratioTLOOSETRKANDCALP->SetName("EfficiencyTLOOSETRKANDCALP");
// hratioTLOOSETRKANDCALP->Divide(hnumTLOOSETRKANDCALP,hdenTLOOSETRKANDCALP,1,1);
// SetBinomialErrors(50/*100*//*400*/ , (TH1F*)hnumTLOOSETRKANDCALP, (TH1F*)hdenTLOOSETRKANDCALP, (TH1F*) hratioTLOOSETRKANDCALP);

//TFile fTLOOSETRKP("/prj_root/5670/wmass1/alex/samples/MAY5_default_tagisloosetrk.root");
TFile fTLOOSETRKP("/prj_root/5670/wmass1/alex/samples/zeefullmc_ZA0trksEffLOOSETRKtag.root");

gDirectory->cd("Eff_Hist");
hdenTLOOSETRKP=ZMass_vs_Pt_Before_Trk_CC->ProjectionX();
hnumTLOOSETRKP=ZMass_vs_Pt_After_Trk_CC->ProjectionX();
hdenTLOOSETRKP->Rebin(2);
hnumTLOOSETRKP->Rebin(2);
hratioTLOOSETRKP = (TH1F *)hnumTLOOSETRKP->Clone();
hratioTLOOSETRKP->SetName("EfficiencyTLOOSETRKP");
hratioTLOOSETRKP->Divide(hnumTLOOSETRKP,hdenTLOOSETRKP,1,1);
SetBinomialErrors(50/*100*//*400*/ , (TH1F*)hnumTLOOSETRKP, (TH1F*)hdenTLOOSETRKP, (TH1F*) hratioTLOOSETRKP);

//TFile fTCALP("/prj_root/5670/wmass1/alex/samples/MAY5_default_loosetrkeff_tagiscalobased.root");
TFile fTCALP("/prj_root/5670/wmass1/alex/samples/zeefullmc_ZA0trksEffCALOtag.root");

gDirectory->cd("Eff_Hist");
//need some postprocessing of histograms
//before projecting to PT axis to remove m<70 and m>110
//events which were allowed in this sample
//hdenTCALP=ZMass_vs_Pt_Before_Trk_CC->ProjectionX();
//hnumTCALP=ZMass_vs_Pt_After_Trk_CC->ProjectionX();
hdenTCALP_tmp_2D=ZMass_vs_Pt_Before_Trk_CC;
hnumTCALP_tmp_2D=ZMass_vs_Pt_After_Trk_CC;

for(Int_t i=0; i<=hdenTCALP_tmp_2D->GetXaxis()->GetNbins(); i++){
for(Int_t j=0; j<=hdenTCALP_tmp_2D->GetYaxis()->GetNbins(); j++){
	//float upedgeX =  hdenTCALP_tmp_2D/*->ProjectionX()*/->GetXaxis()->GetBinUpEdge(i);
	//float lowedgeX = hdenTCALP_tmp_2D/*->ProjectionX()*/->GetXaxis()->GetBinLowEdge(i);
	float upedgeY =  hdenTCALP_tmp_2D->ProjectionY()->GetYaxis()->GetBinUpEdge(j);
	float lowedgeY = hdenTCALP_tmp_2D->ProjectionY()->GetYaxis()->GetBinLowEdge(j);
    //cout<<" lowY upY "<<lowedgeY<<"  "<<upedgeY<<endl;
	if(upedgeY>110. || lowedgeY<70.){
		hdenTCALP_tmp_2D->SetBinContent(i,j,0.);
		hdenTCALP_tmp_2D->SetBinContent(i,j,0.);
		hdenTCALP_tmp_2D->SetBinError(i,j,0.);
		hdenTCALP_tmp_2D->SetBinError(i,j,0.);
		hnumTCALP_tmp_2D->SetBinContent(i,j,0.);
		hnumTCALP_tmp_2D->SetBinContent(i,j,0.);
		hnumTCALP_tmp_2D->SetBinError(i,j,0.);
		hnumTCALP_tmp_2D->SetBinError(i,j,0.);
	}
}
}

hdenTCALP=hdenTCALP_tmp_2D->ProjectionX();;
hnumTCALP=hnumTCALP_tmp_2D->ProjectionX();;

hdenTCALP->Rebin(2);
hnumTCALP->Rebin(2);
hratioTCALP = (TH1F *)hnumTCALP->Clone();
hratioTCALP->SetName("EfficiencyTCALP");
hratioTCALP->Divide(hnumTCALP,hdenTCALP,1,1);
SetBinomialErrors(50/*100*//*400*/ , (TH1F*)hnumTCALP, (TH1F*)hdenTCALP, (TH1F*) hratioTCALP);



                


//hratioTP;
hratioTPWITHUTCUT->SetLineColor(44);
//hratioTCCONLYPNOTRIG->SetLineColor(34);
//hratioTCCONLYPEITHERTRIGMATCH->SetLineColor(24);
//hratioTCCONLYPTAGTRIGMATCH->SetLineColor(14);
hratioTP->SetLineColor(12);
hratioTLOOSETRKP->SetLineColor(2);
//hratioTLOOSETRKANDCALP->SetLineColor(3);
hratioTCALP->SetLineColor(3);

hratioTP->Draw();
hratioTPWITHUTCUT->Draw("Sames");
//hratioTCCONLYPNOTRIG->Draw("Sames");
//hratioTCCONLYPEITHERTRIGMATCH->Draw("Sames");
//hratioTCCONLYPTAGTRIGMATCH->Draw("Sames");
hratioTLOOSETRKP->Draw("Sames");
//hratioTLOOSETRKANDCALP->Draw("Sames");
hratioTCALP->Draw("Sames");

}
