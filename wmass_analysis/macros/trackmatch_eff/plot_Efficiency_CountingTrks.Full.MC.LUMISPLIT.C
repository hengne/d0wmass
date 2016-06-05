
/*
-rw-r--r--  1 melnit wmass1 6670219 May 23 22:33 MAY23geantlumGT150.root
-rw-r--r--  1 melnit wmass1 7133223 May 23 22:39 MAY23NOUT15geantlumGT150.root

-rw-r--r--  1 melnit wmass1 7260082 May 14 11:48 zeefullmc_ZA0trksEffLOOSETRKtag.root
-rw-r--r--  1 melnit wmass1 6813990 May 14 11:52 zeefullmc_ZA0trksEffDEFAULTTIGHTTRKtagUT15.root
-rw-r--r--  1 melnit wmass1 7260186 May 14 11:52 zeefullmc_ZA0trksEffDEFAULTTIGHTTRKtag.root
-rw-r--r--  1 melnit wmass1 7221565 May 14 11:52 zeefullmc_ZA0trksEffCALOtag.root
-rw-r--r--  1 melnit wmass1 5870024 May 14 11:53 zeedata_ZA0trksEffDEFAULTTIGHTTRKtagUT15.root
-rw-r--r--  1 melnit wmass1 7321632 May 14 12:09 zeefullmc_ZA0trksDROPUT15EffDEFAULTTIGHTTRKtag.root
/home/melnit/samples/wenu_newoverlay.root 
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

TH1 *hnumW;
TH1 *hdenW;
TH1 *hratioW;

TH1 *hnumNOTRIG;
TH1 *hdenNOTRIG;
TH1 *hratioNOTRIG;

TH1 *hnumNOUTCUT;
TH1 *hdenNOUTCUT;
TH1 *hratioNOUTCUT;

TH1 *hnumNOUTCUTNOTRIG;
TH1 *hdenNOUTCUTNOTRIG;
TH1 *hratioNOUTCUTNOTRIG;

gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");


TCanvas *canv = new TCanvas("canv", "canv",8,8,400, 400);


// 
// //--------------- DEFAULT ------------------------
TFile f("/prj_root/5670/wmass1/alex/samples/MAY23geantlumGT150.root");
gDirectory->cd("ZCand_Hist");
hVar0=ZCandMass_vs_Pt_____CCCC_Trks_0->ProjectionX();
hVar1=ZCandMass_vs_Pt_____CCCC_Trks_1->ProjectionX();
hVar2=ZCandMass_vs_Pt_____CCCC_Trks_2->ProjectionX();

hVar012 = (TH1F *)hVar0->Clone();
hVar012->SetName("ZCandElecPt_012");
hVar012->Add(hVar1,1);
hVar012->Add(hVar2,1);

hVar2x2 = (TH1F *)hVar2->Clone();
hVar012x2 = (TH1F *)hVar012->Clone();
hVar012x2->SetName("2xZCandElecPt_0_012trks");
hVar2x2->SetName("2xZCandElecPt_0_2trks");

hVar012x2->Scale(2.0);
hVar2x2->Scale(2.0);

hnum = (TH1F *)hVar1->Clone();
hden = (TH1F *)hVar012x2->Clone();
hnum->SetName("Numerator");
hden->SetName("Denominator");

hnum->Add(hVar2x2,1);


hden->Rebin(3);
hnum->Rebin(3);

hratio = (TH1F *)hnum->Clone();
hratio->SetName("Efficiency");

hratio->Divide(hnum,hden,1,1);
SetBinomialErrors(100/*300*//*400*/ , (TH1F*)hnum, (TH1F*)hden, (TH1F*) hratio);
hratio->SetMarkerStyle(8);

hratio->DrawCopy();
//hden->SetMaximum(1.2*hden->GetMaximum());
//hden->DrawCopy("PE");
//hnum->SetMaximum(1.2*hden->GetMaximum());
//hnum->DrawCopy("PE");

// //---------- NO TRIGGER ----------------------
// TFile fnotrig("/prj_root/5670/wmass1/alex/samples/MAY5_default_no_trigger_trks012.root");
// gDirectory->cd("ZCand_Hist");
// hVar0=ZCandMass_vs_Pt_____CCCC_Trks_0->ProjectionX();
// hVar1=ZCandMass_vs_Pt_____CCCC_Trks_1->ProjectionX();
// hVar2=ZCandMass_vs_Pt_____CCCC_Trks_2->ProjectionX();
// 
// hVar012 = (TH1F *)hVar0->Clone();
// hVar012->SetName("ZCandElecPt_012");
// hVar012->Add(hVar1,1);
// hVar012->Add(hVar2,1);
// 
// hVar2x2 = (TH1F *)hVar2->Clone();
// hVar012x2 = (TH1F *)hVar012->Clone();
// hVar012x2->SetName("2xZCandElecPt_0_012trks");
// hVar2x2->SetName("2xZCandElecPt_0_2trks");
// 
// hVar012x2->Scale(2.0);
// hVar2x2->Scale(2.0);
// 
// hnum = (TH1F *)hVar1->Clone();
// hden = (TH1F *)hVar012x2->Clone();
// hnum->SetName("Numerator");
// hden->SetName("Denominator");
// 
// hnum->Add(hVar2x2,1);
// 
// 
// hden->Rebin(3);
// hnum->Rebin(3);
// 
// hratio = (TH1F *)hnum->Clone();
// hratio->SetName("Efficiency");
// 
// hratio->Divide(hnum,hden,1,1);
// SetBinomialErrors(100/*300*//*400*/ , (TH1F*)hnum, (TH1F*)hden, (TH1F*) hratio);
// 
// //hratio->SetLineColor(2);
// //hratio->DrawCopy("Sames");
// //hden->SetLineColor(2);
// //hden->DrawCopy("PESames");
// hnum->SetLineColor(2);
// hnum->DrawCopy("PESames");
// 
// 
// 
// //------------NO ZUT CUT ---------
// 
// TFile fnozutcut("/prj_root/5670/wmass1/alex/samples/MAY5_nozutcut_rev_cctagonly_tgmatchtag.root");
// gDirectory->cd("ZCand_Hist");
// hVar0=ZCandMass_vs_Pt_____CCCC_Trks_0->ProjectionX();
// hVar1=ZCandMass_vs_Pt_____CCCC_Trks_1->ProjectionX();
// hVar2=ZCandMass_vs_Pt_____CCCC_Trks_2->ProjectionX();
// 
// hVar012 = (TH1F *)hVar0->Clone();
// hVar012->SetName("ZCandElecPt_012");
// hVar012->Add(hVar1,1);
// hVar012->Add(hVar2,1);
// 
// hVar2x2 = (TH1F *)hVar2->Clone();
// hVar012x2 = (TH1F *)hVar012->Clone();
// hVar012x2->SetName("2xZCandElecPt_0_012trks");
// hVar2x2->SetName("2xZCandElecPt_0_2trks");
// 
// hVar012x2->Scale(2.0);
// hVar2x2->Scale(2.0);
// 
// hnum = (TH1F *)hVar1->Clone();
// hden = (TH1F *)hVar012x2->Clone();
// hnum->SetName("Numerator");
// hden->SetName("Denominator");
// 
// hnum->Add(hVar2x2,1);
// 
// 
// hden->Rebin(3);
// hnum->Rebin(3);
// 
// hratio = (TH1F *)hnum->Clone();
// hratio->SetName("Efficiency");
// 
// hratio->Divide(hnum,hden,1,1);
// SetBinomialErrors(100/*300*//*400*/ , (TH1F*)hnum, (TH1F*)hden, (TH1F*) hratio);
// 
// //hratio->SetLineColor(3);
// //hratio->DrawCopy("Sames");
// //hden->SetLineColor(3);
// //hden->DrawCopy("PESames");
// hnum->SetLineColor(3);
// hnum->DrawCopy("PESames");


//------------NO ZUT CUT 

TFile fnotrignozutcut("/prj_root/5670/wmass1/alex/samples/MAY23NOUT15geantlumGT150.root");
gDirectory->cd("ZCand_Hist");
hVar0=ZCandMass_vs_Pt_____CCCC_Trks_0->ProjectionX();
hVar1=ZCandMass_vs_Pt_____CCCC_Trks_1->ProjectionX();
hVar2=ZCandMass_vs_Pt_____CCCC_Trks_2->ProjectionX();

hVar012 = (TH1F *)hVar0->Clone();
hVar012->SetName("ZCandElecPt_012");
hVar012->Add(hVar1,1);
hVar012->Add(hVar2,1);

hVar2x2 = (TH1F *)hVar2->Clone();
hVar012x2 = (TH1F *)hVar012->Clone();
hVar012x2->SetName("2xZCandElecPt_0_012trks");
hVar2x2->SetName("2xZCandElecPt_0_2trks");

hVar012x2->Scale(2.0);
hVar2x2->Scale(2.0);

hnum = (TH1F *)hVar1->Clone();
hden = (TH1F *)hVar012x2->Clone();
hnum->SetName("Numerator");
hden->SetName("Denominator");

hnum->Add(hVar2x2,1);


hden->Rebin(3);
hnum->Rebin(3);

hratio = (TH1F *)hnum->Clone();
hratio->SetName("Efficiency");

hratio->Divide(hnum,hden,1,1);
SetBinomialErrors(100/*300*//*400*/ , (TH1F*)hnum, (TH1F*)hden, (TH1F*) hratio);

hratio->SetMarkerStyle(4);
hratio->DrawCopy("Sames");
//hden->SetLineColor(4);
//hden->DrawCopy("PESames");
//hnum->SetLineColor(4);
//hnum->DrawCopy("PESames");



TFile fW("/prj_root/5670/wmass1/alex/samples/wenfullmc_newoverlay.lumigt150.root");


gDirectory->cd("WCand_Hist");

hdenW=WCandElecPt_0;
hnumW=WCandElecPt_Spatial_Match_0;
hdenW->Rebin(2);
hnumW->Rebin(2);
hratioW = (TH1F *)hnumW->Clone();
hratioW->SetName("EfficiencyW");

hratioW->Divide(hnumW,hdenW,1,1);
SetBinomialErrors(200/*400*/ , (TH1F*)hnumW, (TH1F*)hdenW, (TH1F*) hratioW);

hratioW->SetLineColor(7);
hratioW->DrawCopy("Sames");

// 
// TFile fNOTRIG("/prj_root/5670/wmass1/alex/samples/ZAEff_nozutcut_rev_cctagonly_tgmatchtag.root");
// gDirectory->cd("Eff_Hist");
// 
// hdenNOTRIG=ZMass_vs_Pt_Before_Trk_CC->ProjectionX();
// hnumNOTRIG=ZMass_vs_Pt_After_Trk_CC->ProjectionX();
// hratioNOTRIG = (TH1F *)hnumNOTRIG->Clone();
// hratioNOTRIG->SetName("EfficiencyNOTRIG");
// 
// hratioNOTRIG->Divide(hnumNOTRIG,hdenNOTRIG,1,1);
// SetBinomialErrors(100/*400*/ , (TH1F*)hnumNOTRIG, (TH1F*)hdenNOTRIG, (TH1F*) hratioNOTRIG);
// 
// 
// TFile fNOUTCUT("/prj_root/5670/wmass1/alex/samples/MAY5_default_tagiscalobased.root");
// gDirectory->cd("Eff_Hist");
// 
// hdenNOUTCUT=ZMass_vs_Pt_Before_Trk_CC->ProjectionX();
// hnumNOUTCUT=ZMass_vs_Pt_After_Trk_CC->ProjectionX();
// hratioNOUTCUT = (TH1F *)hnumNOUTCUT->Clone();
// hratioNOUTCUT->SetName("EfficiencyNOUTCUT");
// 
// hratioNOUTCUT->Divide(hnumNOUTCUT,hdenNOUTCUT,1,1);
// SetBinomialErrors(100/*400*/ , (TH1F*)hnumNOUTCUT, (TH1F*)hdenNOUTCUT, (TH1F*) hratioNOUTCUT);
// 
// 
// hVar012 = (TH1F *)hVar0->Clone();
// //hVar012->SetName("ZCandMass_CCCC_Trks_012");
// hVar012->SetName("ZCandElecPt_012");
// hVar012->Add(hVar1,1);
// hVar012->Add(hVar2,1);
// 
// hVar2x2 = (TH1F *)hVar2->Clone();
// hVar012x2 = (TH1F *)hVar012->Clone();
// //hVar012x2->SetName("2xZCandMass_CCCC_Trks_012");
// //hVar2x2->SetName("2xZCandMass_CCCC_Trks_2");
// hVar012x2->SetName("2xZCandElecPt_0_012trks");
// hVar2x2->SetName("2xZCandElecPt_0_2trks");
// 
// hVar012x2->Scale(2.0);
// hVar2x2->Scale(2.0);
// hnum = (TH1F *)hVar1->Clone();
// hden = (TH1F *)hVar012x2->Clone();
// hnum->SetName("Numerator");
// hden->SetName("Denominator");
// 
// hnum->Add(hVar2x2,1);
// 
// 
// hden->Rebin(3);
// hnum->Rebin(3);
// 
// hratio = (TH1F *)hnum->Clone();
// hratio->SetName("Efficiency");
// 
// hratio->Divide(hnum,hden,1,1);
// SetBinomialErrors(100/*300*//*400*/ , (TH1F*)hnum, (TH1F*)hden, (TH1F*) hratio);

}
