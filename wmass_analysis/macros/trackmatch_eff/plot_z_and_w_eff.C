{

//#define EFFICIENCY_9VAR
//#define LABELS

#define EFFICIENCYANDRATIO

gStyle->SetOptStat(0);

gStyle->SetTitleW(0.5);
gStyle->SetTitleH(0.07);
gStyle->SetTitleX(0.25);
	
Int_t N_variables=9;
TString zfile[9],zfilehistoname[9];
// zfile[0]= "ZLoose_092710_vs_PT.root";
// zfile[1]= "ZLoose_092710_vs_PhysEta.root"; 					   
// zfile[2]= "ZLoose_092710_vs_VTXZ.root";
// zfile[3]= "ZLoose_092710_vs_trkpt.root";					
// zfile[4]= "ZLoose_092710_vs_SET.root"; 					   
// zfile[5]= "ZLoose_092710_vs_LUMI.root";					
// zfile[6]= "ZLoose_092710_vs_UPARA.root";					
// zfile[7]= "ZLoose_092710_vs_UT.root";
// zfile[8]= "ZLoose_092710_vs_delphi.root"; 
// zeedata efficiency
//zfile[0]="~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/plotout.ptedefault.root";  zfilehistoname[0]= "h_eff";
//zfile[1]="~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/plotout.lumidefault.root"; zfilehistoname[1]= "h_eff";  				 
//zfile[2]="~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/plotout.set_default.root"; zfilehistoname[2]= "h_eff";
// zfile[0]="/work/bhatia-clued0/melnit/public/next/plotout.finebin.root"; 		 zfilehistoname[0]= "h_eff";
// zfile[1]="/work/bhatia-clued0/melnit/public/next/plotout.Loose.Data.lummi.root"; zfilehistoname[1]= "h_eff";				  
// zfile[2]="/work/bhatia-clued0/melnit/public/next/plotout.Loose.Data.set.root";   zfilehistoname[2]= "h_eff";
zfile[0]="~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/plotout.NUMERBUGFIXED.Loose_vs_PT.root";   zfilehistoname[0]= "h_eff";
zfile[1]="~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/plotout.NUMERBUGFIXED.Loose_vs_LUMI.root"; zfilehistoname[1]= "h_eff";  		   
zfile[2]="~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/plotout.NUMERBUGFIXED.Loose_vs_SET.root";  zfilehistoname[2]= "h_eff";
 

TString wfile[9],wfilehistoname[9];
// wfile[0]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WLoose_vs_PT.root";
// wfile[1]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WLoose_vs_PhysEta.root"; 						
// wfile[2]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WLoose_vs_VTXZ.root";
// wfile[3]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WLoose_vs_trkpt.root";		
// wfile[4]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WLoose_vs_SET.root"; 		
// wfile[5]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WLoose_vs_LUMI.root";		
// wfile[6]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WLoose_vs_UPARA.root";		
// wfile[7]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WLoose_vs_UT.root";
// wfile[8]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WLoose_vs_delphi.root"; 
//wenfullmc efficiency
//wfile[0]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/WTightVarBin_vs_PT.root";   wfilehistoname[0]= "heff";
//wfile[1]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/WTightVarBin_vs_LUMI.root"; wfilehistoname[1]= "heff";					  
//wfile[2]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/WTightVarBin_vs_SET.root";  wfilehistoname[2]= "heff";
wfile[0]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/WLooseVarBin_vs_PT.root";   wfilehistoname[0]= "heff";
wfile[1]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/WLooseVarBin_vs_LUMI.root"; wfilehistoname[1]= "heff";					   
wfile[2]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/WLooseVarBin_vs_SET.root";  wfilehistoname[2]= "heff";

TString zfile2[9],zfile2histoname[9];
// zfile2[0]= "ZEffAnaLoose_092710_vs_PT.root";
// zfile2[1]= "ZEffAnaLoose_092710_vs_PhysEta.root"; 					   
// zfile2[2]= "ZEffAnaLoose_092710_vs_VTXZ.root";
// zfile2[3]= "ZEffAnaLoose_092710_vs_trkpt.root";					
// zfile2[4]= "ZEffAnaLoose_092710_vs_SET.root"; 					   
// zfile2[5]= "ZEffAnaLoose_092710_vs_LUMI.root";					
// zfile2[6]= "ZEffAnaLoose_092710_vs_UPARA.root";					
// zfile2[7]= "ZEffAnaLoose_092710_vs_UT.root";
// zfile2[8]= "ZEffAnaLoose_092710_vs_delphi.root"; 
// zfile2[0]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/ZTight_vs_PT.root";
// zfile2[1]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/ZTight_vs_PhysEta.root"; 					   
// zfile2[2]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/ZTight_vs_VTXZ.root";
// zfile2[3]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/ZTight_vs_trkpt.root";					
// zfile2[4]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/ZTight_vs_SET.root"; 					   
// zfile2[5]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/ZTight_vs_LUMI.root";					
// zfile2[6]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/ZTight_vs_UPARA.root";					
// zfile2[7]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/ZTight_vs_UT.root";
// zfile2[8]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/ZTight_vs_delphi.root"; 
//zeefullmc efficiency
//zfile2[0]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/ZTightHengneVarBin_vs_PT.root";   zfile2histoname[0]= "heff";
//zfile2[1]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/ZTightVarBin_vs_LUMI.root"; zfile2histoname[1]= "heff";  					
//zfile2[2]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/ZTightVarBin_vs_SET.root";  zfile2histoname[2]= "heff";
// zfile2[0]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/ZLoose_092710VarBin_vs_PT.root";   zfile2histoname[0]= "heff";
// zfile2[1]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/ZLoose_092710VarBin_vs_LUMI.root"; zfile2histoname[1]= "heff";						  
// zfile2[2]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/ZLoose_092710VarBin_vs_SET.root";  zfile2histoname[2]= "heff";
zfile2[0]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/ZLooseHengneVarBin_vs_PT.root";   zfile2histoname[0]= "heff";
zfile2[1]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/ZLoose_092710VarBin_vs_LUMI.root"; zfile2histoname[1]= "heff";						
zfile2[2]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/ZLoose_092710VarBin_vs_SET.root";  zfile2histoname[2]= "heff";


TString wfile2[9],wfile2histoname[9];
// wfile2[0]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WEffAnaLoose_vs_PT.root";
// wfile2[1]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WEffAnaLoose_vs_PhysEta.root"; 						
// wfile2[2]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WEffAnaLoose_vs_VTXZ.root";
// wfile2[3]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WEffAnaLoose_vs_trkpt.root";		
// wfile2[4]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WEffAnaLoose_vs_SET.root"; 		
// wfile2[5]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WEffAnaLoose_vs_LUMI.root";		
// wfile2[6]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WEffAnaLoose_vs_UPARA.root";		
// wfile2[7]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WEffAnaLoose_vs_UT.root";
// wfile2[8]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WEffAnaLoose_vs_delphi.root"; 
// wfile2[0]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WTight_vs_PT.root";
// wfile2[1]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WTight_vs_PhysEta.root"; 						
// wfile2[2]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WTight_vs_VTXZ.root";
// wfile2[3]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WTight_vs_trkpt.root";		
// wfile2[4]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WTight_vs_SET.root"; 		
// wfile2[5]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WTight_vs_LUMI.root";		
// wfile2[6]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WTight_vs_UPARA.root";		
// wfile2[7]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WTight_vs_UT.root";
// wfile2[8]= "/scratch/work/melnit/RUN2BWMASS/loosetrkeff/WTight_vs_delphi.root"; 
// //wtoz fullmc ratio
// wfile2[0]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/WToZTight_FullMCRatio_vs____PT.root"; wfile2histoname[0]="hwtoz_tight_fullmchratio_vs____pt";   
// wfile2[1]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/WToZTight_FullMCRatio_vs__LUMI.root"; wfile2histoname[1]="hwtoz_tight_fullmchratio_vs__lumi";
// wfile2[2]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/WToZTight_FullMCRatio_vs___SET.root"; wfile2histoname[2]="hwtoz_tight_fullmchratio_vs___set"; 
wfile2[0]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/WToZLoose_FullMCRatio_vs____PT.root"; wfile2histoname[0]="hwtoz_loose_fullmchratio_vs____pt";  
wfile2[1]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/WToZLoose_FullMCRatio_vs__LUMI.root"; wfile2histoname[1]="hwtoz_loose_fullmchratio_vs__lumi";
wfile2[2]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/WToZLoose_FullMCRatio_vs___SET.root"; wfile2histoname[2]="hwtoz_loose_fullmchratio_vs___set"; 


TString zfile3[9],zfile3histoname[9];
zfile3[0]= "ZLooseWlike_092710_vs_PT.root";
zfile3[1]= "ZLooseWlike_092710_vs_PhysEta.root"; 					   
zfile3[2]= "ZLooseWlike_092710_vs_VTXZ.root";
zfile3[3]= "ZLooseWlike_092710_vs_trkpt.root";					
zfile3[4]= "ZLooseWlike_092710_vs_SET.root"; 					   
zfile3[5]= "ZLooseWlike_092710_vs_LUMI.root";					
zfile3[6]= "ZLooseWlike_092710_vs_UPARA.root";					
zfile3[7]= "ZLooseWlike_092710_vs_UT.root";
zfile3[8]= "ZLooseWlike_092710_vs_delphi.root"; 
//zee datatomc ratio
//zfile3[0]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/ZTight_DataToMC_Ratio_vs____PT.root"; zfile3histoname[0]="hratio_ztight_datatomc_vs____pt";
//zfile3[1]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/ZTight_DataToMC_Ratio_vs__LUMI.root"; zfile3histoname[1]="hratio_ztight_datatomc_vs__lumi";					  
//zfile3[2]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/ZTight_DataToMC_Ratio_vs___SET.root"; zfile3histoname[2]="hratio_ztight_datatomc_vs___set";
zfile3[0]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/ZLoose_DataToMC_Ratio_vs____PT.root"; zfile3histoname[0]="hratio_zloose_datatomc_vs____pt";
zfile3[1]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/ZLoose_DataToMC_Ratio_vs__LUMI.root"; zfile3histoname[1]="hratio_zloose_datatomc_vs__lumi";				  
zfile3[2]= "~/2b/wzfitter_area_062510/wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/ZLoose_DataToMC_Ratio_vs___SET.root"; zfile3histoname[2]="hratio_zloose_datatomc_vs___set";

//file with pol3 TF1s from the fit
// (made by running wmass_analysis/macros/trackmatch_eff/fitwithpol3_and_save_fitresults.C
//  in which eff.C code produced by this macro ran first time
//  to produce the ratios to be fitted with TF1s was inserted
//  according to instructions in wmass_analysis/macros/trackmatch_eff/fitwithpol3_and_save_fitresults.C)
TString tf1file[9];
//tf1file[0]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/TighTrkMatchEff_fits_of_ratios_vs____pt.root"; 
//tf1file[1]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/TighTrkMatchEff_fits_of_ratios_vs__lumi.root";  			   
//tf1file[2]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/TighTrkMatchEff_fits_of_ratios_vs___set.root"; 
tf1file[0]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/LooseTrkMatchEff_fits_of_ratios_vs____pt.root"; 
tf1file[1]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/LooseTrkMatchEff_fits_of_ratios_vs__lumi.root"; 				 
tf1file[2]= "~/2b/analysis/wmass_analysis/macros/trackmatch_eff/LooseTrkMatchEff_fits_of_ratios_vs___set.root"; 


TH1 *hnum_z[9];
TH1 *hden_z[9];
TH1 *heff_z[9];
TH1 *heff_z2[9];
TH1 *heff_z3[9];

TH1 *hnum_w[9];
TH1 *hden_w[9];
TH1 *heff_w[9];
TH1 *heff_w2[9];

TF1 *central_1[9];
TF1 *plus____1[9];
TF1 *minus___1[9];
TF1 *central_2[9];
TF1 *plus____2[9];
TF1 *minus___2[9];

#ifdef EFFICIENCY_9VAR
TCanvas *c = new TCanvas("c", "c",8,8,900,750);
c->Divide(3,3);

for (Int_t i=0; i<N_variables; i++){

    TFile *fz = new TFile(zfile[i]);

	hnum_z[i]=(TH1*)gDirectory->Get("hnum");
	hden_z[i]=(TH1*)gDirectory->Get("hden");
	heff_z[i]=(TH1*)gDirectory->Get("heff");
	//----heff_z[i]->SetLineWidth(2);

    cout<<i<<"  "<<heff_z[i]<<endl;

    TFile *fw = new TFile(wfile[i]);

	hnum_w[i]=(TH1*)gDirectory->Get("hnum");
	hden_w[i]=(TH1*)gDirectory->Get("hden");
	heff_w[i]=(TH1*)gDirectory->Get("heff");
	hnum_w[i]->SetLineColor(4);
	hden_w[i]->SetLineColor(4);
	heff_w[i]->SetLineColor(4);
	//----heff_w[i]->SetLineWidth(2);

    TFile *fz2 = new TFile(zfile2[i]);
	heff_z2[i]=(TH1*)gDirectory->Get("heff");
	//heff_z2[i]->SetLineColor(12);

    TFile *fw2 = new TFile(wfile2[i]);
	heff_w2[i]=(TH1*)gDirectory->Get("heff");
	//heff_w2[i]->SetLineColor(7);
	heff_w2[i]->SetLineColor(4);

    TFile *fz3 = new TFile(zfile3[i]);
	heff_z3[i]=(TH1*)gDirectory->Get("heff");
	heff_z3[i]->SetLineColor(9);


    c->cd(i+1);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.2);

//     hden_w[i]->GetXaxis()->SetLabelSize(0.07);
//     hden_w[i]->GetYaxis()->SetLabelSize(0.07);
// 	hden_w[i]->Draw();
// 	Double_t normSample = hden_w[i]->Integral(); 
// 	hden_z[i]->DrawNormalized("Same",normSample);
// }
// c->Print("den.C");


//  hnum_w[i]->GetXaxis()->SetLabelSize(0.07);
//  hnum_w[i]->GetYaxis()->SetLabelSize(0.07);
// 	hnum_w[i]->Draw();
// 	Double_t normSample = hnum_w[i]->Integral(); 
// 	hnum_z[i]->DrawNormalized("Same",normSample);
// }
// c->Print("num.C");

  
 heff_w[i]->GetXaxis()->SetLabelSize(0.07);
 heff_w[i]->GetYaxis()->SetLabelSize(0.07);
 heff_w[i]->SetMinimum(0.7);
 heff_w[i]->SetMaximum(1.0);

 // make products of histograms product
 //heff_w[i]->Sumw2();
 //heff_z[i]->Sumw2();
 //heff_w2[i]->Sumw2();
 //heff_z2[i]->Sumw2();
 heff_w[i]->Multiply(heff_w2[i]);
 heff_z[i]->Multiply(heff_z2[i]);


 //plot several
 heff_w[i]->Draw();
 heff_z[i]->Draw("Same");
 //heff_w2[i]->Draw("Same");
 //heff_z2[i]->Draw("Same");
 //heff_z3[i]->Draw("Same");
}
#endif 

#ifdef EFFICIENCYANDRATIO
TCanvas *c = new TCanvas("c", "c",8,8,430,950);
c->Divide(1,3);

N_variables=3;
for (Int_t i=0; i<N_variables; i++){

    TFile *fz = new TFile(zfile[i]);
	heff_z[i]=(TH1*)gDirectory->Get(zfilehistoname[i]);
	heff_z[i]->SetLineWidth(1);
	heff_z[i]->SetLineColor(12);

    TFile *fw = new TFile(wfile[i]);
	heff_w[i]=(TH1*)gDirectory->Get(wfilehistoname[i]);
	heff_w[i]->SetLineWidth(1);
	heff_w[i]->SetLineColor(7);

    TFile *fz2 = new TFile(zfile2[i]);
	heff_z2[i]=(TH1*)gDirectory->Get(zfile2histoname[i]);
	heff_z2[i]->SetLineWidth(1);
	heff_z2[i]->SetLineColor(1);heff_z2[i]->SetMarkerStyle(8);heff_z2[i]->SetMarkerSize(0.05);

    TFile *fw2 = new TFile(wfile2[i]);
	heff_w2[i]=(TH1*)gDirectory->Get(wfile2histoname[i]);
	heff_w2[i]->SetLineWidth(1);
	heff_w2[i]->SetLineColor(4);

    TFile *fz3 = new TFile(zfile3[i]);
	heff_z3[i]=(TH1*)gDirectory->Get(zfile3histoname[i]);
	heff_z3[i]->SetLineWidth(1);
	heff_z3[i]->SetLineColor(28);
    //---------------------------

    c->cd(i+1);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.2);
  
    heff_w[i]->GetXaxis()->SetLabelSize(0.07);
    heff_w[i]->GetYaxis()->SetLabelSize(0.07);
	if (i==0) heff_w[i]->GetXaxis()->SetRange(2,20);
    heff_w[i]->SetMinimum(0.5);
    heff_w[i]->SetMaximum(1.2);

    heff_w[i]->Draw();
    heff_z[i]->Draw("Same");
    heff_w2[i]->Draw("Same");
    heff_z2[i]->Draw("Same");
    heff_z3[i]->Draw("Same");

    //comment out drawing of polynomials when you run first time,
    //i.e. to produce the ratios to be fit with polynomials 
    //--------- plot also fit results ---------------
    TFile *tf1 = new TFile(tf1file[i]);
	central_1[i]=(TF1*)gDirectory->Get("fpol3_zdatatozmc");
	plus____1[i]=(TF1*)gDirectory->Get("fpol3_zdatatozmcpluserror");
	minus___1[i]=(TF1*)gDirectory->Get("fpol3_zdatatozmcminuserror");
	central_2[i]=(TF1*)gDirectory->Get("fpol3_wtozmc");
	plus____2[i]=(TF1*)gDirectory->Get("fwmcpluserror");
	minus___2[i]=(TF1*)gDirectory->Get("fpol3_wtozmcminuserror");

	central_1[i]->Draw("Same");
	plus____1[i]->Draw("Same");
	minus___1[i]->Draw("Same");
	central_2[i]->Draw("Same");
	plus____2[i]->Draw("Same");
	minus___2[i]->Draw("Same");
}
Float_t x0,y0,textsize;
x0=0.4;
y0=0.04;
textsize=0.08;
TString text1="Electron PT, GeV";
TString text2="Inst. Lumi / 36";
TString text3="Scalar ET, GeV";
//------------------
TString textextraA="Blue: Wenu-To-Zee FullMC Ratio";
TString textextraB="Brown: Zee DATA-To-FullMC Ratio";
TString textextraC="Cyan: Wenu-Measured FullMC Efficiency";
TString textextraD="Black: Zee-Measured FullMC Efficiency";
TString textextraE="Gray: Zee-Measured DATA Efficiency";

c_1->cd();TLatex t1; t1.SetNDC();t1.SetTextSize(textsize);t1.DrawLatex(x0,y0,text1);
c_2->cd();TLatex t2; t2.SetNDC();t2.SetTextSize(textsize);t2.DrawLatex(x0,y0,text2);
c_3->cd();TLatex t3; t3.SetNDC();t3.SetTextSize(textsize);t3.DrawLatex(x0-0.1,y0,text3);
//extra
c_1->cd();TLatex t1extraA; t1extraA.SetNDC();t1extraA.SetTextSize(0.05);t1extraA.SetTextColor(4) ;t1extraA.DrawLatex(0.17,0.84,textextraA);
c_1->cd();TLatex t1extraB; t1extraB.SetNDC();t1extraB.SetTextSize(0.05);t1extraB.SetTextColor(28);t1extraB.DrawLatex(0.17,0.78,textextraB);
c_1->cd();TLatex t1extraC; t1extraC.SetNDC();t1extraC.SetTextSize(0.05);t1extraC.SetTextColor(7) ;t1extraC.DrawLatex(0.17,0.55,textextraC);
c_1->cd();TLatex t1extraD; t1extraD.SetNDC();t1extraD.SetTextSize(0.05);t1extraD.SetTextColor(1) ;t1extraD.DrawLatex(0.17,0.30,textextraD);
c_1->cd();TLatex t1extraE; t1extraE.SetNDC();t1extraE.SetTextSize(0.05);t1extraE.SetTextColor(12);t1extraE.DrawLatex(0.17,0.24,textextraE);
#endif

#ifdef LABELS
Float_t x0,y0,textsize;
x0=0.4;
y0=0.04;
textsize=0.08;
TString text1="Electron PT, GeV";
TString text2="Electron Physics #eta";
TString text3="Primary Vertex Z, cm";
TString text4="Electron Track PT, GeV";
TString text5="Scalar ET, GeV";
TString text6="Inst. Lumi / 36";
TString text7="Upara, GeV";
TString text8="u_{T}, GeV";
TString text9="#Delta#phi(e,u_{T})";
//------------------
TString textextra2A="Black: Z#rightarrowee";
TString textextra2B="Blue: W#rightarrowe#nu";
TString textextra2C="Tight #times Loose Track Match Eff.";

c_1->cd();TLatex t1; t1.SetNDC();t1.SetTextSize(textsize);t1.DrawLatex(x0,y0,text1);
c_2->cd();TLatex t2; t2.SetNDC();t2.SetTextSize(textsize);t2.DrawLatex(x0,y0,text2);
c_3->cd();TLatex t3; t3.SetNDC();t3.SetTextSize(textsize);t3.DrawLatex(x0-0.1,y0,text3);
c_4->cd();TLatex t4; t4.SetNDC();t4.SetTextSize(textsize);t4.DrawLatex(x0-0.2,y0,text4);
c_5->cd();TLatex t5; t5.SetNDC();t5.SetTextSize(textsize);t5.DrawLatex(x0,y0,text5);
c_6->cd();TLatex t6; t6.SetNDC();t6.SetTextSize(textsize);t6.DrawLatex(x0,y0,text6);
c_7->cd();TLatex t7; t7.SetNDC();t7.SetTextSize(textsize);t7.DrawLatex(x0,y0,text7);
c_8->cd();TLatex t8; t8.SetNDC();t8.SetTextSize(textsize);t8.DrawLatex(x0,y0,text8);
c_9->cd();TLatex t9; t9.SetNDC();t9.SetTextSize(textsize);t9.DrawLatex(x0,y0,text9);
//extra
c_2->cd();TLatex t2extraA; t2extraA.SetNDC();t2extraA.SetTextSize(0.09);t2extraA.SetTextColor(4);t2extraA.DrawLatex(x0,0.5,    textextra2A);
c_2->cd();TLatex t2extraB; t2extraB.SetNDC();t2extraB.SetTextSize(0.09);t2extraB.SetTextColor(1);t2extraB.DrawLatex(x0,0.4,    textextra2B);
c_2->cd();TLatex t2extraC; t2extraC.SetNDC();t2extraC.SetTextSize(0.12);t2extraC.SetTextColor(1);t2extraB.DrawLatex(x0-0.4,0.9,textextra2C);
#endif


//c->Print("eff.C");
c->Print("effwithfits.C");

//cout<<"TString ts = \"z_and_w_looseeff_9var\";"<<endl;
//cout<<"TString ts = \"z_and_w_looseeff_and_tighteff_9var\";"<<endl;
cout<<"TString ts = \"something\";"<<endl;

cout<<"c->Print(ts+\".C\"); c->Print(ts+\".eps\"); c->Print(ts+\".gif\");"<<endl;

}
