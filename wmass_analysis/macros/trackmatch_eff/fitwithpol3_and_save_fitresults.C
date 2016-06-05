/*

to run:

/d0usr/products/root/Linux-2-4/v5_26_00-GCC_3_4_6/bin/root -l fitwithpol3_and_save_fitresults.C      

*/
{

gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Fit_Functions.C");
 
gStyle->SetOptStat(0);

//--------------------------------------------
//--- cut and paste here code e.g. from eff.C
//--- which was generated with wmass_analysis/macros/trackmatch_eff/plot_z_and_w_eff.C
//---- (easier to do one pad at a time in case of several pads)----
//-------------------------------------------- 



//-------------------------------------------------
//-------------- end of copy and paste ------------
//-------------------------------------------------

//-- this code fragment depends on the code above (names could be different)
TH1 *hwtoz_tight_fullmchratio_vs____pt_clone = new TH1F("hwtoz_tight_fullmchratio_vs____pt_clone","",23, xAxis);
hwtoz_tight_fullmchratio_vs____pt_clone= (TH1F*) hwtoz_tight_fullmchratio_vs____pt->Clone();
TH1 *hratio_ztight_datatomc_vs____pt_clone = new TH1F("hratio_ztight_datatomc_vs____pt_clone","",23, xAxis);
hratio_ztight_datatomc_vs____pt_clone= (TH1F*) hratio_ztight_datatomc_vs____pt->Clone();

TH1 *hwtoz_tight_fullmchratio_vs__lumi_clone = new TH1F("hwtoz_tight_fullmchratio_vs__lumi_clone","",23, xAxis);
hwtoz_tight_fullmchratio_vs__lumi_clone= (TH1F*) hwtoz_tight_fullmchratio_vs__lumi->Clone();
TH1 *hratio_ztight_datatomc_vs__lumi_clone = new TH1F("hratio_ztight_datatomc_vs__lumi_clone","",23, xAxis);
hratio_ztight_datatomc_vs__lumi_clone= (TH1F*) hratio_ztight_datatomc_vs__lumi->Clone();

TH1 *hwtoz_tight_fullmchratio_vs___set_clone = new TH1F("hwtoz_tight_fullmchratio_vs___set_clone","",23, xAxis);
hwtoz_tight_fullmchratio_vs___set_clone= (TH1F*) hwtoz_tight_fullmchratio_vs___set->Clone();
TH1 *hratio_ztight_datatomc_vs___set_clone = new TH1F("hratio_ztight_datatomc_vs___set_clone","",23, xAxis);
hratio_ztight_datatomc_vs___set_clone= (TH1F*) hratio_ztight_datatomc_vs___set->Clone();
//END OF -- this code fragment depends on the code above (names could be different)

//pick just one pad at time
c_1->cd();
//c_2->cd();
//c_3->cd();
//---------
//when moving to another pad, change histo names to be fitted
//inside the code below
// e.g. replace
// hratio_zloose_datatomc_vs____pt with   hratio_zloose_datatomc_vs__lumi
// and									  
// hwtoz_loose_fullmchratio_vs____pt with hwtoz_loose_fullmchratio_vs__lumi
//------------
//-- also change the name of the outputfile accordingly ---------
TString outputfilename = "TighTrkMatchEff_fits_of_ratios_vs____pt.root";
//TString outputfilename = "TighTrkMatchEff_fits_of_ratios_vs__lumi.root";
//TString outputfilename = "TighTrkMatchEff_fits_of_ratios_vs___set.root";
//--
//TString outputfilename = "LooseTrkMatchEff_fits_of_ratios_vs____pt.root";
//TString outputfilename = "LooseTrkMatchEff_fits_of_ratios_vs__lumi.root";
//TString outputfilename = "LooseTrkMatchEff_fits_of_ratios_vs___set.root";

//------------
//-- also change the range of interest specific to a given variable ---------
Float_t Rxmin=25.;Float_t Rxmax=75.;
//Float_t Rxmin=0.;Float_t Rxmax=10.;
//Float_t Rxmin=0.;Float_t Rxmax=300.;
//-------------------------------------------------------

//-------------------------------------------------------
//--------------- READY TO FIT --------------------------
//-------------------------------------------------------

// code from wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/FitHistoWithPol_CovMatrix_plotErrorBand_ApplyCorrection.C
TF1 *fpol3_zdatatozmc = new TF1("fpol3_zdatatozmc","pol3",Rxmin,Rxmax);
fpol3_zdatatozmc->SetRange(Rxmin,Rxmax);
cout<<" p0 + p1*x + p1*x*x + p2*x*x*x fit:"<<endl;

TFitResultPtr r3 =hratio_ztight_datatomc_vs____pt->Fit(fpol3_zdatatozmc,"RS"); 
if ( int(r3) == 0) {
  TMatrixTSym<double> matrix3 = r3->GetCovarianceMatrix();
  matrix3.Print();
}
cout<<"( C00 C01 C02 C03 ) "<<matrix3[0][0]<<"  "<<matrix3[0][1]<<"  "<<matrix3[0][2]<<"  "<<matrix3[0][3]<<endl;
cout<<"( C10 C11 C12 C13 ) "<<matrix3[1][0]<<"  "<<matrix3[1][1]<<"  "<<matrix3[1][2]<<"  "<<matrix3[1][3]<<endl;
cout<<"( C20 C21 C22 C23 ) "<<matrix3[2][0]<<"  "<<matrix3[2][1]<<"  "<<matrix3[2][2]<<"  "<<matrix3[2][3]<<endl;
cout<<"( C30 C31 C32 C33 ) "<<matrix3[3][0]<<"  "<<matrix3[3][1]<<"  "<<matrix3[3][2]<<"  "<<matrix3[3][3]<<endl;

double pol3_C00=matrix3[0][0];
double pol3_C11=matrix3[1][1];
double pol3_C22=matrix3[2][2];
double pol3_C33=matrix3[3][3];

double pol3_C01=matrix3[0][1];
double pol3_C02=matrix3[0][2];
double pol3_C03=matrix3[0][3];

double pol3_C12=matrix3[1][2];
double pol3_C13=matrix3[1][3];

double pol3_C23=matrix3[2][3];

Int_t NumPar3 = 15;
TF1 *fpol3_zdatatozmcpluserror = new TF1("fpol3_zdatatozmcpluserror",Pol3PlusMinusError,Rxmin,Rxmax,NumPar3);
TF1 *fpol3_zdatatozmcminuserror = new TF1("fpol3_zdatatozmcminuserror",Pol3PlusMinusError,Rxmin,Rxmax,NumPar3);
Double_t params15plus[15];
params15plus[0]=r3->Value(0);
params15plus[1]=r3->Value(1);
params15plus[2]=r3->Value(2);
params15plus[3]=r3->Value(3);
params15plus[4]=pol3_C00; 
params15plus[5]=pol3_C11; 
params15plus[6]=pol3_C22; 
params15plus[7]=pol3_C33; 
params15plus[8]=pol3_C01; 
params15plus[9]=pol3_C02; 
params15plus[10]=pol3_C03; 
params15plus[11]=pol3_C12; 
params15plus[12]=pol3_C13; 
params15plus[13]=pol3_C23;  
params15plus[14]=1.0;

Double_t params15minus[15];
params15minus[0]=r3->Value(0);
params15minus[1]=r3->Value(1);
params15minus[2]=r3->Value(2);
params15minus[3]=r3->Value(3);
params15minus[4]=pol3_C00; 
params15minus[5]=pol3_C11; 
params15minus[6]=pol3_C22; 
params15minus[7]=pol3_C33; 
params15minus[8]=pol3_C01; 
params15minus[9]=pol3_C02; 
params15minus[10]=pol3_C03; 
params15minus[11]=pol3_C12; 
params15minus[12]=pol3_C13; 
params15minus[13]=pol3_C23;  
params15minus[14]=-1.0;

fpol3_zdatatozmcpluserror->SetParameters(params15plus);
fpol3_zdatatozmcminuserror->SetParameters(params15minus);

fpol3_zdatatozmc->SetLineWidth(1);
fpol3_zdatatozmcpluserror->SetLineWidth(1);
fpol3_zdatatozmcpluserror->SetLineStyle(2);
fpol3_zdatatozmcminuserror->SetLineWidth(1);
fpol3_zdatatozmcminuserror->SetLineStyle(2);
fpol3_zdatatozmc->SetLineColor(28);
fpol3_zdatatozmcpluserror->SetLineColor(28);
fpol3_zdatatozmcminuserror->SetLineColor(28);


// code from wzfitter/updates20082009/ptdependent_bkgsubtrackted_trkmatcheff/FitHistoWithPol_CovMatrix_plotErrorBand_ApplyCorrection.C
TF1 *fpol3_wtozmc = new TF1("fpol3_wtozmc","pol3_wtozmc",Rxmin,Rxmax);
fpol3_wtozmc->SetRange(Rxmin,Rxmax);
cout<<" p0 + p1*x + p1*x*x + p2*x*x*x fit:"<<endl;

TFitResultPtr r3_wtozmc =hwtoz_tight_fullmchratio_vs____pt->Fit(fpol3_wtozmc,"RS"); 
if ( int(r3_wtozmc) == 0) {
  TMatrixTSym<double> matrix3_wtozmc = r3_wtozmc->GetCovarianceMatrix();
  matrix3_wtozmc.Print();
}
cout<<"( C00 C01 C02 C03 ) "<<matrix3_wtozmc[0][0]<<"  "<<matrix3_wtozmc[0][1]<<"  "<<matrix3_wtozmc[0][2]<<"  "<<matrix3_wtozmc[0][3]<<endl;
cout<<"( C10 C11 C12 C13 ) "<<matrix3_wtozmc[1][0]<<"  "<<matrix3_wtozmc[1][1]<<"  "<<matrix3_wtozmc[1][2]<<"  "<<matrix3_wtozmc[1][3]<<endl;
cout<<"( C20 C21 C22 C23 ) "<<matrix3_wtozmc[2][0]<<"  "<<matrix3_wtozmc[2][1]<<"  "<<matrix3_wtozmc[2][2]<<"  "<<matrix3_wtozmc[2][3]<<endl;
cout<<"( C30 C31 C32 C33 ) "<<matrix3_wtozmc[3][0]<<"  "<<matrix3_wtozmc[3][1]<<"  "<<matrix3_wtozmc[3][2]<<"  "<<matrix3_wtozmc[3][3]<<endl;

double pol3_wtozmc_C00=matrix3_wtozmc[0][0];
double pol3_wtozmc_C11=matrix3_wtozmc[1][1];
double pol3_wtozmc_C22=matrix3_wtozmc[2][2];
double pol3_wtozmc_C33=matrix3_wtozmc[3][3];

double pol3_wtozmc_C01=matrix3_wtozmc[0][1];
double pol3_wtozmc_C02=matrix3_wtozmc[0][2];
double pol3_wtozmc_C03=matrix3_wtozmc[0][3];

double pol3_wtozmc_C12=matrix3_wtozmc[1][2];
double pol3_wtozmc_C13=matrix3_wtozmc[1][3];

double pol3_wtozmc_C23=matrix3_wtozmc[2][3];

TF1 *fpol3_wtozmcpluserror = new TF1("fwmcpluserror",Pol3PlusMinusError,Rxmin,Rxmax,NumPar3);
TF1 *fpol3_wtozmcminuserror = new TF1("fpol3_wtozmcminuserror",Pol3PlusMinusError,Rxmin,Rxmax,NumPar3);
Double_t params15_ztowmcplus[15];
params15_ztowmcplus[0]=r3_wtozmc->Value(0);
params15_ztowmcplus[1]=r3_wtozmc->Value(1);
params15_ztowmcplus[2]=r3_wtozmc->Value(2);
params15_ztowmcplus[3]=r3_wtozmc->Value(3);
params15_ztowmcplus[4]=pol3_wtozmc_C00; 
params15_ztowmcplus[5]=pol3_wtozmc_C11; 
params15_ztowmcplus[6]=pol3_wtozmc_C22; 
params15_ztowmcplus[7]=pol3_wtozmc_C33; 
params15_ztowmcplus[8]=pol3_wtozmc_C01; 
params15_ztowmcplus[9]=pol3_wtozmc_C02; 
params15_ztowmcplus[10]=pol3_wtozmc_C03; 
params15_ztowmcplus[11]=pol3_wtozmc_C12; 
params15_ztowmcplus[12]=pol3_wtozmc_C13; 
params15_ztowmcplus[13]=pol3_wtozmc_C23;  
params15_ztowmcplus[14]=1.0;

Double_t params15_ztowmcminus[15];
params15_ztowmcminus[0]=r3_wtozmc->Value(0);
params15_ztowmcminus[1]=r3_wtozmc->Value(1);
params15_ztowmcminus[2]=r3_wtozmc->Value(2);
params15_ztowmcminus[3]=r3_wtozmc->Value(3);
params15_ztowmcminus[4]=pol3_wtozmc_C00; 
params15_ztowmcminus[5]=pol3_wtozmc_C11; 
params15_ztowmcminus[6]=pol3_wtozmc_C22; 
params15_ztowmcminus[7]=pol3_wtozmc_C33; 
params15_ztowmcminus[8]=pol3_wtozmc_C01; 
params15_ztowmcminus[9]=pol3_wtozmc_C02; 
params15_ztowmcminus[10]=pol3_wtozmc_C03; 
params15_ztowmcminus[11]=pol3_wtozmc_C12; 
params15_ztowmcminus[12]=pol3_wtozmc_C13; 
params15_ztowmcminus[13]=pol3_wtozmc_C23;  
params15_ztowmcminus[14]=-1.0;

fpol3_wtozmcpluserror->SetParameters(params15_ztowmcplus);
fpol3_wtozmcminuserror->SetParameters(params15_ztowmcminus);

fpol3_wtozmc->SetLineWidth(1);
fpol3_wtozmcpluserror->SetLineWidth(1);
fpol3_wtozmcpluserror->SetLineStyle(2);
fpol3_wtozmcminuserror->SetLineWidth(1);
fpol3_wtozmcminuserror->SetLineStyle(2);
fpol3_wtozmc->SetLineColor(4);
fpol3_wtozmcpluserror->SetLineColor(4);
fpol3_wtozmcminuserror->SetLineColor(4);



TFile *out = new TFile(outputfilename,"RECREATE");
 
fpol3_zdatatozmc->Write();;
fpol3_zdatatozmcpluserror->Write();;
fpol3_zdatatozmcminuserror->Write();;

fpol3_wtozmc->Write();;
fpol3_wtozmcpluserror->Write();;
fpol3_wtozmcminuserror->Write();;

out->Close();


}
