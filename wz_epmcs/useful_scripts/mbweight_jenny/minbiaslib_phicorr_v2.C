#define minbiaslib_phicorr_cxx
#include "minbiaslib_phicorr.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TF1.h>
#include <iostream>
#include <fstream>
#include <TString.h>
#include <TRandom.h>
#include <iomanip>
#include <TVector2.h>
#include "TSystem.h"

using namespace std;

// g++ `root-config --libs` `root-config --cflags` minbiaslib_phicorr.C -o minbiaslib_phicorr
//./minbiaslib_phicorr filetest.list
void minbiaslib_phicorr::Loop(TString name, double rmspow, double zerofrac, TString rootfile1)
{
   if (fChain == 0) return;
   Long64_t _nentries = fChain->GetEntriesFast();

   int mbfilelines = 0;

  for (int i=0; i<setbins; i++) {
    recoilx[i] = 0.;
    recoilx2[i] = 0.;
    recoily[i] = 0.;
    recoily2[i] = 0.;
    recoilxy[i] = 0.;
    nentries[i] = 0;
  }

  tp_weight = new TProfile("tp_weight", "", 50, 0., 100., 0., 50.);
  hset = new TH1D("hset", "", 50, 0., 100.);
  hsetnew = new TH1D("hsetnew", "", 50, 0., 100.);
  hweight = new TH1D("hweight", "", 500, 0., 50.);
   //  double rmspow =  0.336;//default is 0.4
   // double zerofrac = 0.07; //default is 0.0
  cout<<"new code"<<endl;
  TFile *input1(0);
  // TString rootfile1 = "compout.root";//is compout8

  if (!gSystem->AccessPathName( rootfile1 )) {
    cout << "accessing " << rootfile1 << endl;
    input1 = TFile::Open( rootfile1 );
  } 
  else{
    cout<< "problem accessing "<<rootfile1<< endl;
    exit(0);
  }

  // TH1D* EFFHist = (TH1D*) input1->Get("PMCSbin1eff;1");
  // EFFHist->SetDirectory(0);
  
    std::vector <TH1D*>  eff_hist1;
 std::vector<double> mbsetbins;
 int mbsetnbins = 1;
 double mbsetlow = 0;
 double mbsethigh = 1000;
 double binsize = (mbsethigh - mbsetlow)/mbsetnbins;
 
 mbsetbins.push_back(mbsetlow);
  for (int bin = 1; bin <= mbsetnbins; bin++){
    //cout<<TString::Format("PMCSbin%deff", bin)<<endl;
    TH1D* EFFHist = (TH1D*) input1->Get(TString::Format("PMCSbin%deff;1", bin));
    // cout<<"got histo"<<endl;
    eff_hist1.push_back(EFFHist);
    // cout<<"set dir"<<endl;
    eff_hist1[bin-1]->SetDirectory(0);
    //  cout<<mbsetlow + (bin*binsize)<<endl;
    mbsetbins.push_back(mbsetlow + (bin*binsize));
  }

  
   nameps = name + ".ps";
   nameroot = name + ".root";
   nameps2 = name + "_lib2.ps";
   nameroot2 = name + "_lib2.root";
   name += ".txt";

   mbfile.open (name);
   double overweight = 0;
   double all = 0;
   Long64_t nbytes = 0, nb = 0;
  double all2 = 0;
   double setzero = 0;
   double setzeroprint = 0;
   double setnonzeroprint = 0;
   double maxmbset = 0;

   //Maximum MB set 246.379
   double maxrand = TMath::Power(300, rmspow);

   for (Long64_t jentry=0; jentry<_nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      int mbsetbin = 0;
      for (int i=0; i<mbsetnbins; i++) {
	if (SET > mbsetbins[i])
	  mbsetbin++;
	else
	  break;
      }
      if (mbsetbin > mbsetnbins) mbsetbin = mbsetnbins;
      if (mbsetbin < 0) mbsetbin = 0;
      


 all2++;
 hset->Fill(SET);
      // if(jentry > 1000000) break;
      if (jentry%5000000==0) std::cout << "Entries " << jentry << "  overweight "<<overweight<<"  "<<overweight/mbfilelines<<std::endl;
      if(SET == 0 && (urecopx != 0 ||urecopy != 0 ) ) cout<<urecopx<<"  "<<urecopy<<endl;
    if(SET == 0) setzero++;
    if(SET == 0 && gRandom->Rndm() > zerofrac) continue;
    //if(SET == 0) continue;
      //  if(gRandom->Rndm() > 0.1) continue;
    
      if(SET > maxmbset) maxmbset = SET;
      double weight = 0;
      weight = TMath::Power(SET, rmspow);
     
      all++;

      //Maximum MB set 246.379
      int test = 1;

      if(weight > maxrand) overweight++;

      // hset->Fill(SET);
      if( (weight > gRandom->Rndm()*maxrand || SET == 0)){ //&& gRandom->Rndm() < 0.3){// && gRandom->Rndm() < 0.35 ) { //adjust number of lines with random write, here to preserve 0 SET proportion
      //  if(weight > gRandom->Rndm()*maxrand || SET == 0) {
	//inFile1 >> runNo >> evtNo >> instlumi >> nVtx >> scalarEt >> metx >> mety;

	if(SET != 0){
	  TVector2 vec(-1*urecopx,-1*urecopy);
	  double UpperBound = -555.;
	  UpperBound = eff_hist1[mbsetbin-1]->GetMaximum();//EFFHist->GetMaximum();
	  double LowerBound = UpperBound - 1.0;
	  if(LowerBound < 0) LowerBound = 0.0;
	  double r = gRandom->Uniform(LowerBound, UpperBound);

	  //double val = EFFHist->GetBinContent(EFFHist->FindBin(TVector2::Phi_0_2pi(vec.Phi())));
	  double val = eff_hist1[mbsetbin-1]->GetBinContent(eff_hist1[mbsetbin-1]->FindBin(TVector2::Phi_0_2pi(vec.Phi())));
	  //  cout<<SET<<"  "<<mbsetbin-1<<" "<<eff_hist1[mbsetbin-1]->GetBinContent(eff_hist1[mbsetbin-1]->FindBin(TVector2::Phi_0_2pi(vec.Phi())))<<endl;
	  if (val == 0) cout<<-1*urecopx<<"  "<<-1*urecopy<<"  "<<SET<<endl;
	  //  cout<<" r "<<r<<" val "<<val<<" up "<<UpperBound<<endl;
	  if (r > val){
	    test = 0;
	    //  cout<<"fail"<<endl;
	    continue;
	  } 
	}
	if(test != 1) cout<<test<<endl;

	if( gRandom->Rndm() < 0.8) continue; //using 0.5 for MC and 0.8 for data

	mbfile<<runNum<<" "<<eventNum<<" "<<lumi<<" "<<"999"<<" "<<SET<<" "<<-1*urecopx<<" "<<-1*urecopy<<endl;
	mbfilelines++;
	hsetnew->Fill(SET);

	if(SET == 0) setzeroprint++;
	else setnonzeroprint++;

	int ii = ((int) setbins*(SET-setmin)/(setmax-setmin));
     
	recoilx[ii] += urecopx;
	recoilx2[ii] += urecopx*urecopx;
	recoily[ii] += urecopy;
	recoily2[ii] += urecopy*urecopy;
	recoilxy[ii] += urecopx*urecopy;
	nentries[ii]++;

      }else{
	continue;
      }

    
      tp_weight->Fill(SET, weight);
      hweight->Fill(weight);
   }
   //  int rrr = (int) (mbfilelines*zerofrac);
   // for (int i = 0; i < rrr; i++){
   //   mbfile<<"9999 9999 1 999 0 0 0"<<endl;
   //   mbfilelines++;
   //   setzeroprint++;
   //  }
   //   cout<<"Maximum MB set "<<maxmbset<<endl;

   // cout<<setzero<<"  "<<setnonzeroprint<<"  "<<setzeroprint<<endl;
   cout.precision(10);
   cout<<"Zerofrac "<<setzeroprint/(setnonzeroprint + setzeroprint)<<endl;

   // cout<<all/all2<<"  "<<all<<"  "<<all2<<endl;

  cout.precision(0);
   cout<<"lines in MB file are "<<fixed<<mbfilelines<<endl;
   cout<<"overweight are "<<overweight/all<<"  "<<overweight/mbfilelines<<"  aka "<<overweight<<"  "<<all<<endl;
  cout<<"Total lines "<<all2<<endl;



   meanx = new TGraphErrors(setbins);
   meany = new TGraphErrors(setbins);
   rmsx = new TGraphErrors(setbins);
   rmsy = new TGraphErrors(setbins);
   corr = new TGraphErrors(setbins);
   
   for(int i=0; i<setbins; i++) {
     double mux = recoilx[i]/nentries[i];
     double muy = recoily[i]/nentries[i];
     double sigmax2 = recoilx2[i]/nentries[i] - (recoilx[i]/nentries[i])*(recoilx[i]/nentries[i]);
     double sigmay2 = recoily2[i]/nentries[i] - (recoily[i]/nentries[i])*(recoily[i]/nentries[i]);
     double cov = recoilxy[i]/nentries[i] - recoilx[i]*recoily[i]/(nentries[i]*nentries[i]);
     double rho = cov/TMath::Sqrt(sigmax2*sigmay2);
    
     meanx->SetPoint(i, (((double) i) + 0.5)*(setmax-setmin)/((double) setbins) + setmin, mux);
     meanx->SetPointError(i, 0.0, TMath::Sqrt(sigmax2/nentries[i]));
     rmsx->SetPoint(i, (((double) i) + 0.5)*(setmax-setmin)/((double) setbins) + setmin, TMath::Sqrt(sigmax2));
     rmsx->SetPointError(i, 0.0, sigmax2/(2*nentries[i]));
     meany->SetPoint(i, (((double) i) + 0.5)*(setmax-setmin)/((double) setbins) + setmin, muy);
     meany->SetPointError(i, 0.0, TMath::Sqrt(sigmay2/nentries[i]));
     rmsy->SetPoint(i, (((double) i) + 0.5)*(setmax-setmin)/((double) setbins) + setmin, TMath::Sqrt(sigmay2));
     rmsy->SetPointError(i, 0.0, sigmay2/(2*nentries[i]));
     corr->SetPoint(i, (((double) i) + 0.5)*(setmax-setmin)/((double) setbins) + setmin, rho);
     corr->SetPointError(i, 0.0, (1-rho*rho)/TMath::Sqrt(nentries[i]));
     
   }

   mbfile.close();
}

void minbiaslib_phicorr::runmain(TString name, double rmscoeff, double zerofrac, TString rootfile1) {

  Loop(name, rmscoeff, zerofrac, rootfile1);
  TFile* outfile = new TFile(nameroot, "recreate");
  
  hset->Write();
  hsetnew->Write();
  tp_weight->Write();

  hweight->Write();

TCanvas* c1 = new TCanvas();
 
 hset->Draw();
 hsetnew->SetLineColor(2);
 hsetnew->Scale(hset->Integral()/hsetnew->Integral());
 hsetnew->Draw("same");
 c1->Print(nameps);

  outfile->Close();

  TFile* outfile2 = new TFile(nameroot2, "recreate");
  hset->Write();
  hsetnew->Write();
  meanx->Write("meanx");
  meany->Write("meany");
  rmsx->Write("rmsx");
  rmsy->Write("rmsy");
  corr->Write("corr");
  outfile2->Close();
  /**
  //can also make these plots separately using minbias_fit.C
  TCanvas* c2 = new TCanvas();

TF1 *meanx_f = new TF1("meanx_f", "[0]*TMath::Power(x, [1])");
TF1 *meany_f = new TF1("meany_f", "[0]*TMath::Power(x, [1])");
TF1 *rms_f = new TF1("rms_f", "[0]*TMath::Power(x, [1])");

 meanx_f->FixParameter(0, 0.00115502);
 meanx_f->FixParameter(1, 0.772636);

 meany_f->FixParameter(0, 0.00714599);
 meany_f->FixParameter(1, 0.878154);

 rms_f->FixParameter(0, 0.34);
 rms_f->FixParameter(1, 0.55);

  meanx_f->SetLineColor(2);
  meany_f->SetLineColor(2);
  rms_f->SetLineColor(2);

  meanx->Fit("meanx_f", "+");
  meany->Fit("meany_f", "+");
  rmsx->Fit("rms_f", "+");
  rmsy->Fit("rms_f", "+");
  
  c2->Divide(2,2);
  c2->cd(1);
  rmsx->Draw("AP");
  c2->cd(2);
  rmsy->Draw("AP");
  c2->cd(3);
  meanx->Draw("AP");
  c2->cd(4);
  meany->Draw("AP");
  c2->Print(nameps2);

  **/

}

int main(int argc, char** argv){
  minbiaslib_phicorr m(argv[1]);

  // m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORRRun2a_setpow0.30_small_smaller_zerofrac0.08_v2testmbzbcaf_amb06", 0.30, 0.08, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_mbzbcaf_run3.root");
  // m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORRRun2a_setpow0.30_small_smaller_zerofrac0.08_v2testmbzbcaf_amb10", 0.30, 0.08, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_mbzbcaf_amb10_run3.root");
  m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06_v2test11_shiftorig011", 0.60, 0.06, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_v2_run3_66_shift011.root");
  m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.30_small_smaller_zerofrac0.08_v2test11_shiftorig071", 0.30, 0.08, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_v2_run3_38_shift071.root");

  //m.runmain("mblibtest_default_Run4_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06_v2test11", 0.60, 0.06, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_v2_test11.root");
  // m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06_v2test11", 0.60, 0.06, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run3_v2_test1.root");
  // m.runmain("mblibtest_default_Run4_nozeroset_newmax_PHICORR_setpow0.30_small_smaller_zerofrac0.08_v2test11", 0.30, 0.08, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run4_20.root");

  //  m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORRRun2a_setpow0.30_small_smaller_zerofrac0.08_v2test1", 0.30, 0.08, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run3_v2_1bin_0_1000_dataoldvsnew.root");
  // m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORRRun2a_setpow0.30_small_smaller_zerofrac0.08_v2test8", 0.30, 0.08, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run3_v2_8bin_0_50_dataoldvsnew.root");
  // m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORRRun2a_setpow0.30_small_smaller_zerofrac0.08_v2test3", 0.30, 0.08, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run3_v2_3bin_0_30_dataoldvsnew.root");
  
  //m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORRRun2a_setpow0.60_small_smaller_zerofrac0.06_v2test1", 0.60, 0.06, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run3_v2_3bin_0_30_dataoldvsnew_66.root");
  // m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORRRun2a_setpow0.60_small_smaller_zerofrac0.06_v2test8", 0.60, 0.06, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run3_v2_8bin_0_50_dataoldvsnew_66.root");
  // m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORRRun2a_setpow0.60_small_smaller_zerofrac0.06_v2test3", 0.60, 0.06, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run3_v2_1bin_0_1000_dataoldvsnew_66.root");

  //    m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06_v2test2_8bins_0_50", 0.60, 0.06, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run3_v2_test2_8bins_0_50.root");
  //  m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06_v2test1", 0.60, 0.06, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run3_v2_test1.root");
  // m.runmain("mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.70_small_smaller_zerofrac0.09", 0.70, 0.09, "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/compout_run3_79.root");

  m.mbfilelines.close();
}

/**
Error in <TFile::Open>: no url specified
Zerofrac 0.1119562245
lines in MB file are 2201414
overweight are 0  0  aka 0  27331985
Total lines 35031111
Info in <TCanvas::Print>: ps file mblibtest_default_Run4_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06_v2test11.ps has been created

Error in <TFile::Open>: no url specified
Zerofrac 0.1137025242
lines in MB file are 2925045
overweight are 0  0  aka 0  36879899
Total lines 47290251
Info in <TCanvas::Print>: ps file mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06_v2test11.ps has been created

Zerofrac 0.06363996914
lines in MB file are 2773540
overweight are 0  0  aka 0  37100490
Total lines 47290251
Info in <TCanvas::Print>: ps file mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.30_small_smaller_zerofrac0.08_v2test11.ps has been created

Error in <TFile::Open>: no url specified
Zerofrac 0.06308730603
lines in MB file are 2070258
overweight are 0  0  aka 0  27494340
Total lines 35031111
Info in <TCanvas::Print>: ps file mblibtest_default_Run4_nozeroset_newmax_PHICORR_setpow0.30_small_smaller_zerofrac0.08_v2test11.ps has been created

Zerofrac 0.0633853427
lines in MB file are 13978626
overweight are 0  0  aka 0  37101178
mblibtest_default_Run3_nozeroset_newmax_setpow0.30_small_zerofrac0.08.txt
mblibtest_default_Run3_nozeroset_newmax_setpow0.30_small_zerofrac0.08_lib2.txt


Zerofrac 0.0624426537
lines in MB file are 10466019
overweight are 0  0  aka 0  27493111
mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.08.txt
mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.08_lib2.txt


**/
