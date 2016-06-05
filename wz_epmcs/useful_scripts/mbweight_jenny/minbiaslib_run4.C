#define minbiaslib_cxx
#include "minbiaslib.h"
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

using namespace std;

// g++ `root-config --libs` `root-config --cflags` minbiaslib.C -o minbiaslib
//./minbiaslib filetest.list
void minbiaslib::Loop(TString name, double rmspow, double zerofrac)
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

   //   TString name = "mblibtest_default_nozeroset_setpow0.336_small_zerofrac0.07";
   
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
//Maximum MB set 278.206
double maxrand = TMath::Power(300, rmspow);
   for (Long64_t jentry=0; jentry<_nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      all2++;
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

      if(weight > maxrand) overweight++;

      hset->Fill(SET);
      if( (weight > gRandom->Rndm()*maxrand || SET == 0) && gRandom->Rndm() < 0.5 ) { //adjust number of lines with random write, here to preserve 0 SET proportion
	//inFile1 >> runNo >> evtNo >> instlumi >> nVtx >> scalarEt >> metx >> mety;
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
   // cout<<"Maximum MB set "<<maxmbset<<endl;
   // int rrr = (int) (mbfilelines*zerofrac);
   // for (int i = 0; i < rrr; i++){
   //  mbfile<<"9999 9999 1 999 0 0 0"<<endl;
   //  mbfilelines++;
   //  setzeroprint++;
   // }
 
   // cout<<setzero<<"  "<<setnonzeroprint<<"  "<<setzeroprint<<endl;
   cout.precision(10);
   cout<<"Zerofrac "<<setzeroprint/(setnonzeroprint + setzeroprint)<<endl;

   //  cout<<all/all2<<"  "<<all<<"  "<<all2<<endl;

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

void minbiaslib::runmain(TString name, double rmscoeff, double zerofrac) {

  Loop(name, rmscoeff, zerofrac);
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

  //can also make these plots separately using minbias_fit.C
  TCanvas* c2 = new TCanvas();

TF1 *meanx_f = new TF1("meanx_f", "[0]*TMath::Power(x, [1])");
TF1 *meany_f = new TF1("meany_f", "[0]*TMath::Power(x, [1])");
TF1 *rms_f = new TF1("rms_f", "[0]*TMath::Power(x, [1])");

 meanx_f->FixParameter(0, -0.00209789);
 meanx_f->FixParameter(1, 0.915749);

 meany_f->FixParameter(0, 0.00759873);
 meany_f->FixParameter(1, 0.908687);

 rms_f->FixParameter(0, 0.33);
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



  tp_weight->Delete();
  hset->Delete();
  hsetnew->Delete();
  hweight->Delete();

}

int main(int argc, char** argv){
  minbiaslib m(argv[1]);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.60_small_smaller_zerofrac0.06", 0.60, 0.06);
  /**
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.04", 0.30, 0.04);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.50_small_zerofrac0.04", 0.50, 0.04);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.70_small_zerofrac0.04", 0.70, 0.04);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.90_small_zerofrac0.04", 0.90, 0.04);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow1.10_small_zerofrac0.04", 1.10, 0.04);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.06", 0.30, 0.06);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.50_small_zerofrac0.06", 0.50, 0.06);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.70_small_zerofrac0.06", 0.70, 0.06);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.90_small_zerofrac0.06", 0.90, 0.06);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow1.10_small_zerofrac0.06", 1.10, 0.06);
 
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.08", 0.30, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.50_small_zerofrac0.08", 0.50, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.70_small_zerofrac0.08", 0.70, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.90_small_zerofrac0.08", 0.90, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow1.10_small_zerofrac0.08", 1.10, 0.08);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.60_small_zerofrac0.03", 0.60, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.60_small_zerofrac0.04", 0.60, 0.04);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.60_small_zerofrac0.05", 0.60, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.60_small_zerofrac0.06", 0.60, 0.06);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.60_small_zerofrac0.07", 0.60, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.60_small_zerofrac0.08", 0.60, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.60_small_zerofrac0.09", 0.60, 0.09);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.60_small_zerofrac0.11", 0.60, 0.11);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.40_small_zerofrac0.03", 0.40, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.40_small_zerofrac0.04", 0.40, 0.04);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.40_small_zerofrac0.05", 0.40, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.40_small_zerofrac0.06", 0.40, 0.06);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.40_small_zerofrac0.07", 0.40, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.40_small_zerofrac0.08", 0.40, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.40_small_zerofrac0.09", 0.40, 0.09);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.40_small_zerofrac0.11", 0.40, 0.11);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.80_small_zerofrac0.03", 0.80, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.80_small_zerofrac0.04", 0.80, 0.04);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.80_small_zerofrac0.05", 0.80, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.80_small_zerofrac0.06", 0.80, 0.06);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.80_small_zerofrac0.07", 0.80, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.80_small_zerofrac0.08", 0.80, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.80_small_zerofrac0.09", 0.80, 0.09);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.80_small_zerofrac0.11", 0.80, 0.11);
  **/

  /**
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.30_small_zerofrac0.05", 0.30, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.50_small_zerofrac0.05", 0.50, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.70_small_zerofrac0.05", 0.70, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.90_small_zerofrac0.05", 0.90, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow1.10_small_zerofrac0.05", 1.10, 0.05);
 
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.30_small_zerofrac0.1", 0.30, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.50_small_zerofrac0.1", 0.50, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.70_small_zerofrac0.1", 0.70, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.90_small_zerofrac0.1", 0.90, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow1.10_small_zerofrac0.1", 1.10, 0.1);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.30_small_zerofrac0.15", 0.30, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.50_small_zerofrac0.15", 0.50, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.70_small_zerofrac0.15", 0.70, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.90_small_zerofrac0.15", 0.90, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow1.10_small_zerofrac0.15", 1.10, 0.15);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.30_small_zerofrac0.2", 0.30, 0.2);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.50_small_zerofrac0.2", 0.50, 0.2);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.70_small_zerofrac0.2", 0.70, 0.2);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.90_small_zerofrac0.2", 0.90, 0.2);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow1.10_small_zerofrac0.2", 1.10, 0.2);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.30_small_zerofrac0.0", 0.30, 0.0);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.50_small_zerofrac0.0", 0.50, 0.0);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.70_small_zerofrac0.0", 0.70, 0.0);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow0.90_small_zerofrac0.0", 0.90, 0.0);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_zfracfile_setpow1.10_small_zerofrac0.0", 1.10, 0.0);
  **/

  /**
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.03", 0.30, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.50_small_zerofrac0.03", 0.50, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.70_small_zerofrac0.03", 0.70, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.90_small_zerofrac0.03", 0.90, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow1.10_small_zerofrac0.03", 1.10, 0.03);
 
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.05", 0.30, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.50_small_zerofrac0.05", 0.50, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.70_small_zerofrac0.05", 0.70, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.90_small_zerofrac0.05", 0.90, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow1.10_small_zerofrac0.05", 1.10, 0.05);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.07", 0.30, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.50_small_zerofrac0.07", 0.50, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.70_small_zerofrac0.07", 0.70, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.90_small_zerofrac0.07", 0.90, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow1.10_small_zerofrac0.07", 1.10, 0.07);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.09", 0.30, 0.09);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.50_small_zerofrac0.09", 0.50, 0.09);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.70_small_zerofrac0.09", 0.70, 0.09);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.90_small_zerofrac0.09", 0.90, 0.09);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow1.10_small_zerofrac0.09", 1.10, 0.09);

  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.30_small_zerofrac0.11", 0.30, 0.11);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.50_small_zerofrac0.11", 0.50, 0.11);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.70_small_zerofrac0.11", 0.70, 0.11);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow0.90_small_zerofrac0.11", 0.90, 0.11);
  m.runmain("mblibtest_default_Run4_nozeroset_newmax_setpow1.10_small_zerofrac0.11", 1.10, 0.11);

  **/
  //  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.0", 0.40, 0.0);
  //  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.07_TEST", 0.60, 0.07);
  // m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.0", 0.40, 0.0);
  //  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.05_TEST", 0.55, 0.05);
  // m.runmain("mblibtest_default_Run4_nozeroset_setpow0.7_small_zerofrac0.1_TEST", 0.7, 0.1);
  /**
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.45_small_zerofrac0.04", 0.45, 0.04);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.04", 0.50, 0.04);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.04", 0.55, 0.04);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.04", 0.60, 0.04);

  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.65_small_zerofrac0.05", 0.65, 0.05);
 
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.06", 0.50, 0.06);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.06", 0.55, 0.06);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.06", 0.60, 0.06);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.65_small_zerofrac0.06", 0.65, 0.06);

  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.65_small_zerofrac0.07", 0.65, 0.07);

  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.08", 0.55, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.08", 0.60, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.65_small_zerofrac0.08", 0.65, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.70_small_zerofrac0.08", 0.70, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.08", 0.80, 0.08);

  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.90_small_zerofrac0.08", 0.90, 0.08);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.90_small_zerofrac0.09", 0.90, 0.09);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.90_small_zerofrac0.10", 0.90, 0.10);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.90_small_zerofrac0.11", 0.90, 0.11);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.11", 0.80, 0.11);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.90_small_zerofrac0.12", 0.90, 0.12);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.12", 0.80, 0.12);

  **/
  /**
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.10_small_zerofrac0.01", 0.10, 0.01);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.20_small_zerofrac0.01", 0.20, 0.01);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.30_small_zerofrac0.01", 0.30, 0.01);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.35_small_zerofrac0.01", 0.35, 0.01);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.01", 0.40, 0.01);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.45_small_zerofrac0.01", 0.45, 0.01);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.01", 0.50, 0.01);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.01", 0.55, 0.01);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.01", 0.60, 0.01);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.70_small_zerofrac0.01", 0.70, 0.01);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.01", 0.80, 0.01);

  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.10_small_zerofrac0.03", 0.10, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.20_small_zerofrac0.03", 0.20, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.30_small_zerofrac0.03", 0.30, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.35_small_zerofrac0.03", 0.35, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.03", 0.40, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.45_small_zerofrac0.03", 0.45, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.03", 0.50, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.03", 0.55, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.03", 0.60, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.70_small_zerofrac0.03", 0.70, 0.03);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.03", 0.80, 0.03);
 
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.10_small_zerofrac0.05", 0.10, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.20_small_zerofrac0.05", 0.20, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.30_small_zerofrac0.05", 0.30, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.35_small_zerofrac0.05", 0.35, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.05", 0.40, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.45_small_zerofrac0.05", 0.45, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.05", 0.50, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.05", 0.55, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.05", 0.60, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.70_small_zerofrac0.05", 0.70, 0.05);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.05", 0.80, 0.05);
 
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.10_small_zerofrac0.07", 0.10, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.20_small_zerofrac0.07", 0.20, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.30_small_zerofrac0.07", 0.30, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.35_small_zerofrac0.07", 0.35, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.07", 0.40, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.45_small_zerofrac0.07", 0.45, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.07", 0.50, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.07", 0.55, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.07", 0.60, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.70_small_zerofrac0.07", 0.70, 0.07);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.07", 0.80, 0.07);

  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.10_small_zerofrac0.1", 0.10, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.20_small_zerofrac0.1", 0.20, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.30_small_zerofrac0.1", 0.30, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.35_small_zerofrac0.1", 0.35, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.1", 0.40, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.45_small_zerofrac0.1", 0.45, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.1", 0.50, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.1", 0.55, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.1", 0.60, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.70_small_zerofrac0.1", 0.70, 0.1);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.1", 0.80, 0.1);
 
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.10_small_zerofrac0.005", 0.10, 0.005);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.20_small_zerofrac0.005", 0.20, 0.005);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.30_small_zerofrac0.005", 0.30, 0.005);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.35_small_zerofrac0.005", 0.35, 0.005);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.005", 0.40, 0.005);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.45_small_zerofrac0.005", 0.45, 0.005);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.005", 0.50, 0.005);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.005", 0.55, 0.005);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.005", 0.60, 0.005);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.70_small_zerofrac0.005", 0.70, 0.005);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.005", 0.80, 0.005);
 
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.10_small_zerofrac0.13", 0.10, 0.13);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.20_small_zerofrac0.13", 0.20, 0.13);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.30_small_zerofrac0.13", 0.30, 0.13);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.35_small_zerofrac0.13", 0.35, 0.13);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.13", 0.40, 0.13);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.45_small_zerofrac0.13", 0.45, 0.13);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.13", 0.50, 0.13);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.13", 0.55, 0.13);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.13", 0.60, 0.13);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.70_small_zerofrac0.13", 0.70, 0.13);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.13", 0.80, 0.13);

  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.10_small_zerofrac0.15", 0.10, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.20_small_zerofrac0.15", 0.20, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.30_small_zerofrac0.15", 0.30, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.35_small_zerofrac0.15", 0.35, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.15", 0.40, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.45_small_zerofrac0.15", 0.45, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.15", 0.50, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.15", 0.55, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.15", 0.60, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.70_small_zerofrac0.15", 0.70, 0.15);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.15", 0.80, 0.15);
 
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.10_small_zerofrac0.007", 0.10, 0.007);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.20_small_zerofrac0.007", 0.20, 0.007);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.30_small_zerofrac0.007", 0.30, 0.007);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.35_small_zerofrac0.007", 0.35, 0.007);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.40_small_zerofrac0.007", 0.40, 0.007);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.45_small_zerofrac0.007", 0.45, 0.007);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.50_small_zerofrac0.007", 0.50, 0.007);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.55_small_zerofrac0.007", 0.55, 0.007);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.60_small_zerofrac0.007", 0.60, 0.007);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.70_small_zerofrac0.007", 0.70, 0.007);
  m.runmain("mblibtest_default_Run4_nozeroset_setpow0.80_small_zerofrac0.007", 0.80, 0.007);
  **/
  m.mbfilelines.close();
}

