#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TH1.h"
#include "TMath.h"
#include "TVector2.h"
#include "TFormula.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include "/work/rebel-clued0/jenny/Func.h"

/**
Usage: This code is used to shift the phase of the met (or recoil) phi of the MB library by comparing the ZB and MB library phi distributions.  There are different fitting options.  The current technique is to use a high order polynomial fit and determine the minimum and maximum points for each distribution.  The differences between the mins and maxs are averaged, giving the overall shift.  Once this shift is calculated, you can set dphi to the shift value and the code will output a .txt file which is the MB library with the mex and mey values modified to incorporate the shift.  The SET values are unchanged. 

Another option is to compare the original MB file used to make the library (before reweighting) to the ZB library.  The shift can be calculated as above and then used in Compare2D_run4_v2_shift.C to adjust the original MB library phi phase.  This adjusted phi distribution is then used when the phi correction for the MB library (after reweighting) is determined.  This correction is done in general because there is a small shift of the phi when the reweighting (which only accounts for MB set) is applied.  This is more "natural" in the sense that individual MB library events are not changed.

**/
// author Hengne Li @ LPSC 2010, modified for plotting by Holzbauer 2013
const char *TreeName = "binary_tuple";
const double dphi=0.0; //0.5 for MC in newest runs (2/18/2014) was 0.6 for MC previously, with run12 shift already applied to that library

//-0.845 for run3 data, 0.056 for run4 data, 0.24 for run4 mc (v3 with 0.16), 0.29 for run3 mc (v3 with 0.4)

double applyphishiftMB(TH1D *h1mb);
double applyphishiftZB(TString rootfile, TH1D *h1zb);


void applyphishift_v6(){
TH1::SetDefaultSumw2();
// TString rootfile = "/prj_root/3103/wz2_write/ddboline/RunIIb34/DATA/MBZBLibrary/binary_library_data_Run2b4_all.root";


 TString rootfile = "/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro_v2/binary_library_data_Run2b3_all.root";
// TString rootfile = "/prj_root/7055/wmass2/jenny/libraries/MC/66small/Lib_RunIIb4_21Msinglenu_killcell_dq.root";

 
 //final shift 0.4774
//with another dof par3, -0.661131, with sine
//using sine function, get final shift -0.477064, no better fit for ZB
// TString rootfile = "/work/rebel-clued0/jenny/Winter/epmcs_analysis_p21.26.00_newdefault_May8/wz_epmcs/src/binary_library_MC_runIIb3_killcell_DQ.root";

//same shape issue in all of below
// TString rootfile ="/rooms/wmass/rclsa/ZBLibrary_RunIIb34/FullMC/binary_library_MC_runIIb3_killcell.root";
 //binary_library_MC_runIIb3_killcell_DQ.root
 //binary_library_MC_runIIb3_killcell_noDQ.root
 //binary_library_MC_runIIb3_killcell.root
 //binary_library_MC_runIIb3_nosampling_killcell_DQ.root
 //binary_library_MC_runIIb3_nosampling_killcell_noDQ.root
 //binary_library_MC_runIIb3_nosampling_killcell.root

  //final shift 0.0992007

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
 TH1D *h1mb = new TH1D("h1mb", "", 240, 0., TMath::TwoPi());
 TH1D *h1zb = new TH1D("h1zb", "", 240, 0., TMath::TwoPi());

  double shift = 0;
  shift = applyphishiftZB(rootfile, h1zb);
  shift = TVector2::Phi_0_2pi(shift) - TVector2::Phi_0_2pi(applyphishiftMB(h1mb));
  cout <<"final shift "<< TVector2::Phi_0_2pi(shift)<<endl;

 
  h1mb->Scale(h1zb->Integral()/ h1mb->Integral());
 /**
 TF1* central33 = new TF1("central33", FGausStd, 0.0, 4.0, 5);
  central33->SetParameter(0, 1.07164e+06);
  central33->SetParameter(1, 4.8);
  central33->SetParameter(2, 2.2);
  central33->SetParameter(3, 1.0);
  central33->SetParameter(4, 0.1);
  central33->SetLineColor(2);
 **/

 TF1* central33 = new TF1("central33", "[0] + [1]*x + [2]*TMath::Power(x,2)+ [3]*TMath::Power(x,3)+ [4]*TMath::Power(x,4)+ [5]*TMath::Power(x,5)+ [6]*TMath::Power(x,6) + [7]*TMath::Power(x,7)+ [8]*TMath::Power(x,8)+ [9]*TMath::Power(x,9)+ [10]*TMath::Power(x,10)+ [11]*TMath::Power(x,11)", 0.0, 6.28);
 central33->SetParameter(0, h1mb->GetMinimum() + (h1mb->GetMaximum() - h1mb->GetMinimum())/2);
 central33->SetParameter(1, 1.0);
 central33->SetParameter(2, 0.1);
 central33->SetParameter(3, 0.01);
 central33->SetParameter(4, 0.001);
 central33->SetParameter(5, 0.0001);
 central33->SetParameter(6, 0.00001);
 central33->SetParameter(7, 0.00001);
 central33->SetParameter(8, 0.00001);
 central33->SetParameter(9, 0.00001);
 central33->SetParameter(10, 0.00001);
 central33->SetParameter(11, 0.00001);
 /**
  TF1* central33 = new TF1("central33", "[0] + [1]*cos(x +[2])", 0.0, 6.28);
 central33->SetParameter(0, h1mb->GetMinimum() + (h1mb->GetMaximum() - h1mb->GetMinimum())/2);
 central33->SetParameter(1, (h1mb->GetMaximum() - h1mb->GetMinimum())/2);
 central33->SetParameter(2, 1.0);
 **/
  central33->SetLineColor(2);
  

  h1mb->SetLineColor(2);
  h1mb->SetMarkerColor(2);

 h1mb->Fit(central33, "R+");
 cout<<"Fit chi/ndof "<<central33->GetChisquare() / central33->GetNDF()<<endl;
 std::cout<<"maximum is "<<central33->GetMaximumX()<<endl;
 std::cout<<"minimum is "<<central33->GetMinimumX()<<endl;

 h1zb->Draw("pe");
 h1mb->Draw("pe same");

}


double applyphishiftMB (TH1D *h1mb){


  //    std::ifstream in("/prj_root/7055/wmass2/jenny/libraries/MC/66small/mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06_v2test11.txt");//for all runs, it is the same.  Includes phi shift for run12 already.
  //  std::ifstream in("mblibtest_default_Run3_nozeroset_newmax_PHICORR_setpow0.60_small_smaller_zerofrac0.06_v2test11_shift2_v3.txt");
  // std::ifstream in("/prj_root/7055/wmass2/jenny/libraries/Data/38small/mblibtest_default_Run4_nozeroset_newmax_PHICORR_setpow0.30_small_smaller_zerofrac0.08_v2test11.txt");

  std::ifstream in("/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/mblibtest_default_Run3_nozeroset_origfile_nombset0.txt");
  //std::ifstream in("/work/rebel-clued0/jenny/Winter2013/MBZBsimulacro/mblibtest_default_Run4_nozeroset_origfile_tenth.txt");

  // std::ifstream in("mblibtest_default_Run4_nozeroset_newmax_PHICORR_setpow0.30_small_smaller_zerofrac0.08_v2test11_shift2.txt");
  //std::ifstream in("/prj_root/7055/wmass2/jenny/libraries/Data/PHICORR38/mblibtest_default_Run3_nozeroset_newmax_PHICORRRun2a_setpow0.30_small_smaller_zerofrac0.08_v2test1.txt");
  // std::ifstream in("/work/rebel-clued0/jenny/Winter2013/MBLibraryMaker_fromrafael_run4new/mblibtest_default_Run4_nozeroset_newmax_PHICORRRun2a_setpow0.30_small_smaller_zerofrac0.08_v2testmbzbcaf_amb06.txt");//mblibtest_default_Run4_nozeroset_newmax_PHICORRRun2a_setpow0.30_small_smaller_zerofrac0.08_v2test1_redo.txt");
  //  std::ifstream in("test.txt");
  //  std::ifstream in("Library_MBnvtxLE1_SETfudged5bins_SubtractBifurcate7mod3_phishift_zbphi.txt");

  //to apply shift and get output, be sure to change the const dphi to desired value.
     std::ofstream out("test.txt");//Library_MCMB_SETfudged5bins_SubtractBifurcate7mod3_deKinked_phishift.txt");
    // std::ofstream out("junk.txt");
    // std::ofstream out("Library_MBnvtxLE1_SETfudged5bins_SubtractBifurcate7mod3_phishift_zbphi_mod5.txt");
   if( !in ){
      std::cout << " Input file does not exist!" << std::endl;
      exit(1);
   }

   int runno, evtno, nvtx;
   double instlumi, set, metx, mety, met, phi;
   double metxnw, metynw, phinw;
   Int_t nlines = 0;

  //pmcs binning is 64, 0., TMath::TwoPi(), really don't have enough events for 64 bins, all over the place
   TH1D *h2mb = new TH1D("h2mb", "", 240, 0., TMath::TwoPi());

   std::cout<< "========= start reading and filling =========" << std::endl;
   std::cout<< "(show first 5 entries only) " << std::endl;

   std::string line;
   while (std::getline(in, line)) {
      if ( !in.good() ) {
         runno = 0;
         evtno = 0;
         instlumi = 0;
         nvtx = 0;
         set = 0;
         metx = 0;
         mety = 0;
         break;
      }

      std::istringstream sline;
      sline.str( line );
      sline >> runno >> evtno >> instlumi >> nvtx >> set >> metx >> mety ;
      met = sqrt(metx*metx+mety*mety);
      phi = atan2(mety, metx);
      phinw = phi;
      metxnw = metx;
      metynw = mety;

        if(set != 0){
	phinw = TVector2::Phi_0_2pi(phi+dphi);
	// phinw = fmod(phi+dphi, 2.*TMath::Pi());
	// if (phinw<0) phinw += 2.*TMath::Pi();
	metxnw = met*cos(phinw);
	metynw = met*sin(phinw);
	
	//    h1mb->Fill(TVector2::Phi_0_2pi(phi-2.45));
	//if(set != 0){
	h1mb->Fill(TVector2::Phi_0_2pi(phi));
	h2mb->Fill(phinw);
	h1mb->Fill(TVector2::Phi_0_2pi(phi)+TMath::TwoPi());
	h2mb->Fill(phinw+TMath::TwoPi());
	
	  }
      if (nlines < 5) {
        std::cout << " - entry[" << nlines << "]: " 
                  << "RunNo = " << runno << "; "
                  << "EvtNo = " << evtno << "; "
                  << "instlumi = " << instlumi << "; "
                  << "nvtx = " << nvtx << "; "
                  << "set = " << set << "; "
                  << "metx = " << metx << "; "
                  << "mety = " << mety << "; "
                  << "met = " << met << "; "
                  << "phi = " << phi << "; "
                  << "metxnw = " <<metxnw << "; "
                  << "metynw = " << metynw << "; "
                  << "phinw = " << phinw << "; "
                  << std::endl;

      }
      out << runno << " " << evtno << " " << instlumi << " " << nvtx << " " << set << " " << metxnw << " " << metynw << std::endl;
      nlines++;
   }
   std::cout<< "========= total entries " << nlines << " ==========" << std::endl;

   /**
 TF1* central3 = new TF1("central3", FGausStd, 0.0, 6.28, 5);
 central3->SetParameter(0, 61000);
 central3->SetParameter(1, 4.8);
  central3->SetParameter(2, 2.2);
 central3->SetParameter(3, 1.0);
 central3->SetParameter(4, 0.1);
  central3->SetLineColor(kBlack);
  
 TF1* central4 = new TF1("central4", FGausStd, 0.0, 6.28, 5);
 central4->SetParameter(0, 61000);
 central4->SetParameter(1, 4.9);
  central4->SetParameter(2, 2.2);
 central4->SetParameter(3, 1.0);
 central4->SetParameter(4, 0.1);
  central4->SetLineColor(kRed);
   **/
  /**
 TF1* central3 = new TF1("central3", Sine, 0., 4.0, 3);
  central3->SetParameter(0, 3.11232e+03);
  central3->SetParameter(1, -0.448449);
  central3->SetParameter(2, 4.65224e+02);
  central3->SetLineColor(kBlack);
  
 TF1* central4 = new TF1("central4", Sine, 0., 4.0, 3);
  central4->SetParameter(0, 3.11232e+03);
  central4->SetParameter(1, -0.448449);
  central4->SetParameter(2, 4.65224e+02);
  central4->SetLineColor(kRed);
  **/
 TF1* central3 = new TF1("central3", "[0] + [1]*cos(x +[2])", 0.0, 6.28);
 central3->SetParameter(0, h1mb->GetMinimum() + (h1mb->GetMaximum() - h1mb->GetMinimum())/2);
 central3->SetParameter(1, (h1mb->GetMaximum() - h1mb->GetMinimum())/2);
 central3->SetParameter(2, 1.0);
 
 TF1* central4 = new TF1("central4", "[0] + [1]*cos(x +[2])", 0.0, 6.28);
 central4->SetParameter(0, h2mb->GetMinimum() + (h2mb->GetMaximum() - h2mb->GetMinimum())/2);
 central4->SetParameter(1, (h2mb->GetMaximum() - h2mb->GetMinimum())/2);
 central4->SetParameter(2, 1.0);
 

  h1mb->Fit(central3, "R+");
  h2mb->Fit(central4, "R+");
 cout<<"Fit chi/ndof "<<central3->GetChisquare() / central3->GetNDF()<<endl;


//shift is delta param1 
  std::cout << "shift is "<< central4->GetParameter(2) << " - " << central3->GetParameter(2) << " = "<< central4->GetParameter(2) - central3->GetParameter(2) <<std::endl;
  // std::cout << "or "<<central4->GetParameter(2) - central3->GetParameter(2) + TMath::TwoPi()<<std::endl;
   std::cout<<"maximum is "<<central3->GetMaximumX()<<endl;
 std::cout<<"minimum is "<<central3->GetMinimumX()<<endl;
  h1mb->SetMarkerSize(1);
 h2mb->SetMarkerSize(1);
  h1mb->SetMarkerStyle(20);
 h2mb->SetMarkerStyle(20);
 // h1mb->Draw("pe same");

  // h2->SetLineColor(2);
  // h2->SetMarkerColor(2);
  // h2->Draw("pe same");

   in.close();
   out.close();

  return central3->GetParameter(2);

}

double applyphishiftZB(TString rootfile, TH1D *h1zb){

  //  TString rootfile = "/work/rebel-clued0/jenny/Winter/epmcs_analysis_p21.26.00_newdefault_May8/wz_epmcs/src/binary_library_MC_runIIb4_killcell_DQ.root";
 
   
   float metx, mety, met, phi;
   float metxnw, metynw, phinw;

 //pmcs binning is 64, 0., TMath::TwoPi(), really don't have enough events for 64 bins, all over the place
   TH1D *h2zb = new TH1D("h2zb", "", 240, 0., TMath::TwoPi());

   TH1::SetDefaultSumw2();
 
  //.x /home/jholzbau/rootlogon.C
  // TH1::SetDefaultSumw2();
  // TH1::Sumw2();
 Int_t nentries = 999;
 TTree *tree(0);
 TFile *input1(0);

 if (!gSystem->AccessPathName( rootfile )) {
   cout << "accessing " << rootfile << endl;
   input1 = TFile::Open( rootfile );
 } 
 else{
   cout<< "problem accessing "<<rootfile<< endl;
   exit(0);
 }

 tree = (TTree*)input1->Get(TreeName);
 nentries = tree->GetEntries();
 cout<<nentries<<" in tree"<<endl;
 
 metx = 0;
 mety = 0;
 for (int i = 0; i < nentries; i++){
   tree->GetEntry(i);
   metx = (float)tree->GetLeaf("HKmetx")->GetValue(0);
   mety = (float)tree->GetLeaf("HKmety")->GetValue(0);

   met = sqrt(metx*metx+mety*mety);
   phi = atan2(mety, metx);
   phinw = TVector2::Phi_0_2pi(phi+dphi);
     // phinw = fmod(phi+dphi, 2.*TMath::Pi());
     // if (phinw<0) phinw += 2.*TMath::Pi();
   metxnw = met*cos(phinw);
   metynw = met*sin(phinw);
 
   //h1zb->Fill(TVector2::Phi_0_2pi(phi-2.3));
   //  if(h1zb->FindBin(TVector2::Phi_0_2pi(phi)) <=35 || h1zb->FindBin(TVector2::Phi_0_2pi(phi)) >=60){
     h1zb->Fill(TVector2::Phi_0_2pi(phi));
     h2zb->Fill(phinw);
     h1zb->Fill(TVector2::Phi_0_2pi(phi)+TMath::TwoPi());
     h2zb->Fill(phinw+TMath::TwoPi());
     // }
 }
 /**
 TF1* central3 = new TF1("central3", "[0] + [1]*cos([3]*x +[2]) +x*[4]", 0.0, 6.28);
 central3->SetParameter(0, h1zb->GetMinimum() + (h1zb->GetMaximum() - h1zb->GetMinimum())/2);
 central3->SetParameter(1, (h1zb->GetMaximum() - h1zb->GetMinimum())/2);
 central3->SetParameter(2, 1.0);
  central3->SetParameter(3, 1.0);
   central3->SetParameter(4, 0.0);
 **/
 TF1* central3 = new TF1("central3", "[0] + [1]*x + [2]*TMath::Power(x,2)+ [3]*TMath::Power(x,3)+ [4]*TMath::Power(x,4)+ [5]*TMath::Power(x,5)+ [6]*TMath::Power(x,6) + [7]*TMath::Power(x,7)+ [8]*TMath::Power(x,8)+ [9]*TMath::Power(x,9)+ [10]*TMath::Power(x,10)+ [11]*TMath::Power(x,11)", 0.0, 6.28);
 central3->SetParameter(0, h2zb->GetMinimum() + (h2zb->GetMaximum() - h2zb->GetMinimum())/2);
 central3->SetParameter(1, 1.0);
 central3->SetParameter(2, 0.1);
 central3->SetParameter(3, 0.01);
 central3->SetParameter(4, 0.001);
 central3->SetParameter(5, 0.0001);
 central3->SetParameter(6, 0.00001);
 central3->SetParameter(7, 0.00001);
 central3->SetParameter(8, 0.00001);
 central3->SetParameter(9, 0.00001);
 central3->SetParameter(10, 0.00001);
 central3->SetParameter(11, 0.00001);
  
 TF1* central4 = new TF1("central4", "[0] + [1]*cos(x +[2])", 0.0, 6.28);
 central4->SetParameter(0, h2zb->GetMinimum() + (h2zb->GetMaximum() - h2zb->GetMinimum())/2);
 central4->SetParameter(1, (h2zb->GetMaximum() - h2zb->GetMinimum())/2);
 central4->SetParameter(2, 1.0);
 
 /**

 

 TF1* central3 = new TF1("central3", FGausStd, 0.0, 6.28, 5);
  central3->SetParameter(0, 1.08381e+06);
  central3->SetParameter(1, 6.0);
  central3->SetParameter(2, 2.2);
  central3->SetParameter(3, 1.0);

  central3->SetLineColor(kBlack);
  
  TF1* central4 = new TF1("central4", FGausStd, 0.0, 6.28, 5);
  central4->SetParameter(0, 1.08381e+06);
  central4->SetParameter(1, 6.0);
  central4->SetParameter(2, 2.2);
  central4->SetParameter(3, 1.0);

  
  
  **/

  central4->SetLineColor(kRed);

  h1zb->Fit(central3, "R+");
  h2zb->Fit(central4, "R+");

  cout<<"Fit chi/ndof "<<central3->GetChisquare() / central3->GetNDF()<<endl;

//shift is delta param1 
  std::cout << "shift is "<< central4->GetParameter(2) << " - " << central3->GetParameter(2) << " = "<< central4->GetParameter(2) - central3->GetParameter(2) <<std::endl;
  // std::cout << "or "<<central4->GetParameter(2) - central3->GetParameter(2) + TMath::TwoPi()<<std::endl;
  
  std::cout<<"maximum is "<<central3->GetMaximumX()<<endl;
 std::cout<<"minimum is "<<central3->GetMinimumX()<<endl;
  h1zb->SetMarkerSize(1);
 h2zb->SetMarkerSize(1);
  h1zb->SetMarkerStyle(20);
 h2zb->SetMarkerStyle(20);

 h1zb->Draw("pe");

 // h2->SetLineColor(2);
 //h2->SetMarkerColor(2);
 //h2->Draw("pe same");

  return central3->GetParameter(2);

}
