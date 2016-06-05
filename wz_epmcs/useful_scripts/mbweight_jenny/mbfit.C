#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TF1.h>
#include <TProfile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TTree.h"
#include "TStyle.h"
#include <TLeaf.h>
#include <TBranch.h> 
#include "THStack.h"
#include <iomanip>
#include "TROOT.h"
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>
#include "TGraph.h"
#include <TF1.h>
#include "TRandom.h"
//**********************************************************
//Change this line if your TTree has a different name
//const char *TreeName1 = "tree;1";
const char *TreeName1 = "ZTree3;1";
const char *TreeName2 = "ZTree2;1";
//const char *TreeName1 = "wgen;1";
//const char *TreeName2 = "w;1";
//const char *TreeName2 = "binary_tuple;1";
//**********************************************************
double GetEff (int lumi, double setoverpt);
Double_t fitf (Double_t *v, Double_t *par);
Double_t fitexp (Double_t *v, Double_t *par);
Double_t langaufun(Double_t *x, Double_t *par) ;

void mbfit(){

  gROOT->ProcessLine(".x /home/jholzbau/rootlogon.C");

  TString var = "setfit";

  TH1::SetDefaultSumw2();

  //Plan is to plot SET for CAFE and PMCS, Then with SET-MBSET for PMCS vs CAFE, Then with scaled MBSET (event by event depending on SET or MBSET value or something)


   //run3 files
  // TString rootfile1 = "/prj_root/7055/wmass2/jenny/pythia_zee_run2b3_default_tree_20130703_152033/pythia_zee_run2b3_default_tree_20130703_152033_20130703_152344_23/ZRootTree3.root"; 
   //   TString rootfile2 = "/prj_root/7055/wmass2/jenny/mbtreecafe2/WMASS_MC_RUN2B3_zee_ovl_12p8M_1372882719_default_tree2_20130703151839-15902467.d0cabsrv1.fnal.gov/ZRootTree2.root";
  //TString rootfile1 = "/prj_root/7055/wmass2/jenny/pythia_zee_run2b3_default_tree_20130703_152033/run3.root";
  //TString rootfile1 = "/prj_root/7055/wmass2/jenny/pythia_zee_run2b3_default_tree_vtxcut_redo_20130716_142720/result.root";


  //  TString rootfile1 = "/prj_root/7055/wmass2/jenny/pythia_zee_run2b3_default_tree_vtxcut_redo_20130726_085527/tree.root";
 TString rootfile1 = "/prj_root/7055/wmass2/jenny/pythia_zee_run2b3_mbtest_inclusiveweight_NEWmblib_pow04mbprob_TREE_20130726_085527/tree.root";
  TString rootfile2 = "/prj_root/7055/wmass2/jenny/mbtreecafe2/run3.root";


 Double_t xmin = 0;
 Double_t xmax = 300;
 Int_t nbin = 250;
 
 TH1D *tcafe = new TH1D("topcafe", "topcafe",  nbin, xmin, xmax);
 TH1D *tpmcs = new TH1D("toppmcs", "toppmcs",  nbin, xmin, xmax);
 TH1D *tpmcsd = new TH1D("toppmcsd", "toppmcsd",  nbin, xmin, xmax);
 TH1D *tpmcsmb = new TH1D("toppmcsmb", "toppmcsmb",  nbin, xmin, xmax);
 TH1D *tpmcsother = new TH1D("toppmcsother", "toppmcsother",  nbin, xmin, xmax);

 TH1D *tcafesum = new TH1D("topcafesum", "topcafesum",  nbin, xmin, xmax);
 TH1D *tpmcssum = new TH1D("toppmcssum", "toppmcssum",  nbin, xmin, xmax);
 TH1D *tpmcsmbsum = new TH1D("toppmcsmbsum", "toppmcsmbsum",  nbin, xmin, xmax);
 TH1D *tpmcsothersum = new TH1D("toppmcsothersum", "toppmcsothersum",  nbin, xmin, xmax);

 TH1D *t = new TH1D("top", "top",  nbin, xmin, xmax);
 TH1D *b = new TH1D("bottom", "bottom",  nbin, xmin, xmax);


 TH2D *mbandset = new TH2D("mbandset", "mbandset", nbin, xmin, xmax, nbin, xmin, xmax);
 TH2D *otherandset = new TH2D("otherandset", "otherandset", nbin, xmin, xmax, nbin, xmin, xmax);


 TH1D *cafemb = new TH1D("cafemb", "cafemb",  500, 0, 125);
 TH1D *pmcsmb = new TH1D("pmcsmb", "pmcsmb",  500, 0, 125);
 TH1D *ratio = new TH1D("ratio", "ratio",   500, 0, 125);

  //TH1D *t = new TH1D("top", "top",  100, 0, 150);
  //TH1D *b = new TH1D("bottom", "bottom",  100, 0, 150);
  
  TTree *tree1(0);
  TFile *input1(0);
  TTree *tree2(0);
  TFile *input2(0);
  

 if (!gSystem->AccessPathName( rootfile1 )) {
   cout << "accessing " << rootfile1 << endl;
   input1 = TFile::Open( rootfile1 );
 } 
 else{
   cout<< "problem accessing "<<rootfile1<< endl;
   exit(0);
 }

 tree1 = (TTree*)input1->Get(TreeName1);

 int nentries = tree1->GetEntries();
 cout<<nentries<<" in tree"<<endl;

if (!gSystem->AccessPathName( rootfile2 )) {
   cout << "accessing " << rootfile2 << endl;
   input2 = TFile::Open( rootfile2 );
 } 
 else{
   cout<< "problem accessing "<<rootfile2<< endl;
   exit(0);
 }

 tree2 = (TTree*)input2->Get(TreeName2);

 int nentries2 = tree2->GetEntries();
 cout<<nentries2<<" in tree"<<endl;

 // if(nentries > 1000000) nentries = 1000000;
 // if(nentries > 630000) nentries = 630000;
 // if(nentries2 > 630000) nentries2 = 630000;
 // if(nentries2 > 1000000) nentries2 = 1000000;
 
 float em_e[10];
 float em_pt[10];
float em_eta[10];
float em_phi[10];
float em_deteta[10];

 tree2->SetBranchAddress("em_pt", em_pt);
 tree2->SetBranchAddress("em_e", em_e);
 tree2->SetBranchAddress("em_eta", em_eta);
 tree2->SetBranchAddress("em_phi", em_phi);
 tree2->SetBranchAddress("em_deteta", em_deteta);


   
   // for (int j = 0; j < nentries2; j++){
   //   tree2->GetEntry(j);
   // tree2->GetLeaf("nelec")->GetValue(0) > 0 && 
   //   if((fabs(em_deteta[0]) < 1.1 ) && (fabs(em_deteta[1]) < 1.1 ) && tree2->GetLeaf("Ptz")->GetValue(0) < 3  && tree2->GetLeaf("Luminosity")->GetValue(0)  < 3){
   //     tcafe->Fill(tree2->GetLeaf("ScalarEt")->GetValue(0));
   //     tcafesum->Fill(tree2->GetLeaf("ScalarEt")->GetValue(0), tree2->GetLeaf("ScalarEt")->GetValue(0));
   //   }
   // }

 float em_e1[10];
 float em_pt1[10];
float em_eta1[10];
float em_phi1[10];
float em_deteta1[10];

 tree1->SetBranchAddress("em_pt", em_pt1);
 tree1->SetBranchAddress("em_e", em_e1);
 tree1->SetBranchAddress("em_eta", em_eta1);
 tree1->SetBranchAddress("em_phi", em_phi1);
 tree1->SetBranchAddress("em_deteta", em_deteta1);

 // cout<<"here"<<endl;
 // nentries = 100000;
 double pmcsmbz = 0;
 double pmcsset = 0;
 double test = 0;
 double test2 = 0;
 double test3 = 0;
 double wgt = 0;
 for (int i = 0; i < nentries; i++){

   //Need to do an iterative correction.  Start with scale, adjust mb.  then apply linear correction, refit. etc.  This way approximation that cafe and pmcs set is the same during subtraction is better

   //Should be able to do cafe-pmcs and use weight on mb to make mb account for difference in shape (neg weight issue? scale first?)

   tree1->GetEntry(i);
   if((fabs(em_deteta1[0]) < 1.1 ) && (fabs(em_deteta1[1]) < 1.1 ) && tree1->GetLeaf("Ptz")->GetValue(0) < 3 && tree1->GetLeaf("Luminosity")->GetValue(0) < 20){
   // cout<<i<<" of "<<nentries<<endl;
   //  cout<<tree1->GetLeaf("ScalarEt")->GetValue(0)<<"  "<<ratiotest->FindBin(tree1->GetLeaf("ScalarEt")->GetValue(0))<<endl;
   //  cout<<ratiotest->GetBinContent(ratiotest->FindBin(tree1->GetLeaf("ScalarEt")->GetValue(0)))<<endl;
     // cout<<ratiotest->GetBinContent(20)<<endl;
     pmcsmbz =  tree1->GetLeaf("MBScalarEt")->GetValue(0);
     wgt =1;
     // if(tree1->GetLeaf("MBScalarEt")->GetValue(0) < 5 ){
     //  if (tree1->GetLeaf("MBScalarEt")->GetValue(0) < 2.5 && tree1->GetLeaf("MBScalarEt")->GetValue(0) > 0.5) wgt = 2.5/tree1->GetLeaf("MBS//calarEt")->GetValue(0);
     // else wgt = tree1->GetLeaf("MBScalarEt")->GetValue(0)/5.0;
     // }
if (tree1->GetLeaf("MBScalarEt")->GetValue(0) > 0.5 && tree1->GetLeaf("MBScalarEt")->GetValue(0) < 5 ){
     wgt =  1.3;
 }
     /**
//fixes 30-50 GeV part of curve
if(tree1->GetLeaf("MBScalarEt")->GetValue(0) < 10 ){
wgt =0.5;
}
     **/

     //  wgt = 0;
     //}else if (tree1->GetLeaf("MBScalarEt")->GetValue(0) < 1 ){
     //  wgt = 1 + int(gRandom->Gaus(1,2));
       //  cout<<gRandom->Gaus(2.5,2)<<endl;
     // }


     // }else if  (tree1->GetLeaf("MBScalarEt")->GetValue(0) < 10 ){
     //   wgt = 2.0;
     // }

     // wgt = TMath::Power(pmcsmbz, 0.5/(10/(TMath::Sqrt(pmcsmbz)))) ;
     // wgt = TMath::Power(pmcsmbz, 0.5/(10/(TMath::Sqrt(pmcsmbz)))) + 0.2*pmcsmbz;// + pmcsmbz - 0.09*pmcsmbz*pmcsmbz;
     //  wgt = (TMath::Power(pmcsmbz, 0.5)* (0.5  * (1. + TMath::Erf((pmcsmbz-.5)/(TMath::Sqrt(2)*5))))) / ((1+TMath::Exp(-1*TMath::Power(pmcsmbz/2, 2.0))));
     //wgt = int( (TMath::Power(pmcsmbz, 0.4)) );
     // wgt = (TMath::Power(pmcsmbz, 0.70 - tree1->GetLeaf("Luminosity")->GetValue(0)/50));
   
       // if(tree1->GetLeaf("MBScalarEt")->GetValue(0) < 15){
       //	 wgt = wgt*2.0/tree1->GetLeaf("MBScalarEt")->GetValue(0);
       //}

     // / (0.5  * (1. + TMath::Erf((pmcsmbz-.5)/(TMath::Sqrt(2)*1.0))));
       
       // + (0.5  * (1. + TMath::Erf((pmcsmbz-.5)/(TMath::Sqrt(2)*5)))); //0.5 is good for upper region, 0.75 for middle
     //cout<<TMath::Power(pmcsmbz, 0.5/(10/(TMath::Sqrt(pmcsmbz))))<<"  "<<(0.01  * (1. + TMath::Erf((pmcsmbz-5)/(TMath::Sqrt(2)))))<<endl;
     //wgt = 0.582  * (1. + TMath::Erf((pmcsmbz-1.0935)/(TMath::Sqrt(2)*4.3111)));
     // wgt = wgt*(0.53  * (1. + TMath::Erf((pmcsmbz-0.288)/(TMath::Sqrt(2)*4.0453))));
     //  wgt = wgt*(0.489  * (1. + TMath::Erf((pmcsmbz+0.305)/(TMath::Sqrt(2)*4.89144))));
     /**
	//works ok-ish but doesn't work as weight (obviously...)
     pmcsmbz =  tree1->GetLeaf("MBScalarEt")->GetValue(0)*1.5;
     pmcsmbz = pmcsmbz*(0.544657  * (1. + TMath::Erf((pmcsmbz-0.6808)/(TMath::Sqrt(2)*3.18052))));
     pmcsmbz = pmcsmbz*(0.530694  * (1. + TMath::Erf((pmcsmbz-0.726896)/(TMath::Sqrt(2)*1.0429))));
     pmcsmbz = pmcsmbz*(0.480563  * (1. + TMath::Erf((pmcsmbz-0.321864)/(TMath::Sqrt(2)*0.536511))));
     **/

     //    pmcsmbz = pmcsmbz*(0.342784  * (1. + TMath::Erf((pmcsmbz-0.167683)/(TMath::Sqrt(2)*0.540161))));
     //pmcsmbz =   pmcsmbz*(0.9587 + 0.00365*pmcsmbz);
     //  pmcsmbz =   pmcsmbz*(0.903 + 0.007296*pmcsmbz + 0.00003*pmcsmbz*pmcsmbz - 0.00000119*pmcsmbz*pmcsmbz*pmcsmbz);//*ratiotest2->FindBin(tree1->GetLeaf("MBScalarEt")->GetValue(0));
     //  if (tree1->GetLeaf("ScalarEt")->GetValue(0) > 30) pmcsmbz =  tree1->GetLeaf("MBScalarEt")->GetValue(0)*1.0*(0.42 + 0.0071*tree1->GetLeaf("ScalarEt")->GetValue(0));//*ratiotest->GetBinContent(ratiotest->FindBin(tree1->GetLeaf("MBScalarEt")->GetValue(0)));//1.4;
     //cout<<pmcsmbz<<endl;
     //  pmcsmbz = pmcsmbz/(-0.00249 - (0.0003136*pmcsmbz) + (0.00121*pmcsmbz*pmcsmbz));
     //  if (pmcsmbz < 50) pmcsmbz = pmcsmbz/(-0.00005 - (0.00196*pmcsmbz) + (0.00132*pmcsmbz*pmcsmbz));
     //cout<<pmcsmbz<<" new "<<endl;
     //below way over corrects...  obviously not compensating for "other" correctly...
     // if (pmcsmbz > 0) pmcsmbz = pmcsmbz* ((0.5  * (1. + TMath::Erf((pmcsmbz-8.36)/(TMath::Sqrt(2)*4.9)))));
     // if (pmcsmbz > 0) pmcsmbz = TMath::Sqrt(pmcsmbz);// * (1/(0.5  * (1. + TMath::Erf((pmcsmbz-8.36)/(sqrt(2)*4.9)))));
     //  else pmcsmbz = 0;

     pmcsset = tree1->GetLeaf("ScalarEt")->GetValue(0) - tree1->GetLeaf("MBScalarEt")->GetValue(0) + pmcsmbz;

     tpmcs->Fill(pmcsset, wgt);//minus mb plus mb
     tpmcsd->Fill(pmcsset);
     tpmcsother->Fill(pmcsset -pmcsmbz, wgt);
     tpmcsmb->Fill(pmcsmbz, wgt);
     pmcsmb->Fill(pmcsmbz, wgt);

     tpmcssum->Fill(pmcsset, pmcsset);//minus mb plus mb
     tpmcsothersum->Fill(pmcsset, pmcsset -pmcsmbz);
     tpmcsmbsum->Fill(pmcsset, pmcsmbz);

     test += pmcsset;
     test2 += pmcsset -pmcsmbz;
     test3 += pmcsmbz;
     //cout<<pmcsset<<"  "<<pmcsset -pmcsmbz<<"  "<<pmcsmbz<<endl;
     b->Fill(pmcsset, pmcsmbz);
     t->Fill(pmcsset, pmcsmbz - pmcsset);

     mbandset->Fill(pmcsset, pmcsmbz, wgt);
     otherandset->Fill(pmcsset, pmcsset -pmcsmbz, wgt);
     //   tpmcs->Fill(pmcsmbz);
       //   tpmcs->Fill((pmcsset - pmcsmbz) + (pmcsmbz*(1.25 + 0.005*pmcsmbz- 0.0002*pmcsmbz*pmcsmbz)));

       // tpmcs->Fill((pmcsset - pmcsmbz)  + (pmcsmbz + (0.052 - 0.019*pmcsmbz+ 0.0018*pmcsmbz*pmcsmbz)));

       // tpmcs->Fill((pmcsset - pmcsmbz)  + (pmcsmbz * (0.052 - 0.019*pmcsmbz+ 0.0018*pmcsmbz*pmcsmbz)));

       // tpmcs->Fill((pmcsset - pmcsmbz)  + (1.6*pmcsmbz + (0.2 - 0.065*pmcsmbz+ 0.0023*pmcsmbz*pmcsmbz)));

       //uncomment top before using
       //  tpmcs->Fill((pmcsset - pmcsmbz)  + (pmcsmbz * (1.018 + 0.0319*pmcsmbz - 0.00228*pmcsmbz*pmcsmbz + 0.00008*pmcsmbz*pmcsmbz*pmcsmbz)));

   }
 }

 TH1D *tmp;
 int binz = 0;
 for (int j = 0; j < nentries2; j++){
   tree2->GetEntry(j);
   // tree2->GetLeaf("nelec")->GetValue(0) > 0 && 
   if((fabs(em_deteta[0]) < 1.1 ) && (fabs(em_deteta[1]) < 1.1 ) && tree2->GetLeaf("Ptz")->GetValue(0) < 3  && tree2->GetLeaf("Luminosity")->GetValue(0)  < 20){
     tcafe->Fill(tree2->GetLeaf("ScalarEt")->GetValue(0));
     tcafesum->Fill(tree2->GetLeaf("ScalarEt")->GetValue(0), tree2->GetLeaf("ScalarEt")->GetValue(0));

     binz = tpmcs->FindBin(tree2->GetLeaf("ScalarEt")->GetValue(0));
     tmp = otherandset->ProjectionY("test"+j, binz, binz, "");
     cafemb->Fill(tree2->GetLeaf("ScalarEt")->GetValue(0) - tmp->GetRandom());
   }
 }
 // for(int i = 0; i < nbin+1; i++){
 //   tmp = otherandset->ProjectionY("test"+i, i, i, "");
 //   cafemb->Fill(tcafe->GetXaxis()->GetBinCenter(i) - tmp->GetRandom());
 // }
 TCanvas *c5 = new TCanvas("c5","c5",800,800);
 cafemb->Draw();
 pmcsmb->Scale(cafemb->Integral()/pmcsmb->Integral());
 pmcsmb->SetLineColor(kBlue);
 pmcsmb->Draw("same");
 c5->Update();

 TCanvas *c4 = new TCanvas("c4","c4",800,800);
 tpmcsmbsum->Scale(tcafesum->Integral()/tpmcssum->Integral());//orget enertries?
 tpmcsothersum->Scale(tcafesum->Integral()/tpmcssum->Integral());
 tpmcssum->Scale(tcafesum->Integral()/tpmcssum->Integral());
 tpmcssum->Draw();
 tcafesum->SetMarkerColor(kRed);
 tcafesum->SetLineColor(kRed);
 tcafesum->Draw("same");
 
 tpmcsmbsum->SetLineColor(kBlue);
 tpmcsmbsum->Draw("same");
 tpmcsothersum->SetLineColor(kGreen);
 tpmcsothersum->Draw("same");

 c4->Update();
 c4->Print("PlotSETPTPMCS_RecoVarAfterFITSUM_"+var+".eps");
 c4->Print("PlotSETPTPMCS_RecoVarAfterFITSUM_"+var+".gif");


 TCanvas *c3 = new TCanvas("c3","c3",800,800);
  tpmcsmb->Scale(tcafe->Integral()/tpmcs->Integral());
  tpmcsother->Scale(tcafe->Integral()/tpmcs->Integral());
   tpmcs->Scale(tcafe->Integral()/tpmcs->Integral());
   tpmcsd->Scale(tcafe->Integral()/tpmcsd->Integral());
 tpmcs->Draw();

 tpmcsd->SetMarkerColor(kMagenta);
 tpmcsd->SetLineColor(kMagenta);
 tpmcsd->Draw("same");

 tcafe->SetMarkerColor(kRed);
 tcafe->SetLineColor(kRed);
 tcafe->Draw("same");
 
 tpmcsmb->SetLineColor(kBlue);
 tpmcsmb->Draw("same");
 tpmcsother->SetLineColor(kGreen);
 tpmcsother->Draw("same");

 cout<<test<<"  "<<test2<<"  "<<test3<<endl;
 cout<<tpmcs->Integral()<<"  "<<tpmcsmb->Integral()<<"  "<<tpmcsother->Integral()<<endl;

 c3->Update();
 c3->Print("PlotSETPTPMCS_RecoVarAfterFIT_"+var+".eps");
 c3->Print("PlotSETPTPMCS_RecoVarAfterFIT_"+var+".gif");

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  t->Scale(tcafe->Integral()/t->Integral());
 //Would have to randomly get a SET value from CAFe distribution (treat it like pdf) and subtract the setother from PMCS to get cafemb, event by event.
 // for(int i = 0; i < nbin+1; i++){
 //  t->SetBinContent(i, tcafe->GetXaxis()->GetBinCenter() - t->GetXaxis()->GetBinCenter()

  t->Add(tcafe);
   b->Scale(t->Integral()/b->Integral());
  b->Draw();
  t->SetMarkerColor(kRed);
  t->SetLineColor(kRed);
  t->Draw("same");

  c1->Update();
  c1->Print("PlotSETPTPMCS_MB_"+var+".eps");
  c1->Print("PlotSETPTPMCS_MB_"+var+".gif");

 TCanvas *c2 = new TCanvas("c2","c2",800,800);
 //for ratio want (cafe(set+mbset) - pmcs(set))/pmcsmb
 // ratio->Divide(t, b,1.0,1.0,"B");
  // ratio->Divide(tpmcs, tcafe,1.0,1.0,"B");
 ratio->Divide(cafemb, pmcsmb,1.0,1.0,"B");
 ratio->Draw();

 TF1 *func = new TF1("func",fitexp,0,125,3);
 // func->SetParameter(0, 0.0);
 // func->SetParameter(1, 30000);
 // func->SetParameter(2, 300000);
 // func->SetParameter(3, 0.1);

  func->SetParameter(0, 10.0);
   func->SetParameter(1, 10.0);
   func->SetParameter(2, 0.6);
   //  func->SetParameter(2, 0.0015);
   //  func->SetParameter(3, 0.0015);

 // func->FixParameter(0, 11);
 //  func->FixParameter(1, 40);
 // func->FixParameter(2, 250000);
 //func->FixParameter(3, 5);
 

// t->Fit("func", "+R");
// t->Draw();

   ratio->Fit("func", "+R");
   ratio->Draw();

 c2->Update();
 c2->Print("PlotSETPTPMCS_Ratio_"+var+".eps");
 c2->Print("PlotSETPTPMCS_Ratio_"+var+".gif");


 TCanvas *c6 = new TCanvas("c6","c6",800,800);
 mbandset->Draw("colz");

  c6->Update();
  c6->Print("PlotSETPTPMCS_MBandSET_"+var+".eps");
  c6->Print("PlotSETPTPMCS_MBandSET_"+var+".gif");



}
Double_t fitexp (Double_t *v, Double_t *par){

  // return par[0]*TMath::Exp(par[1]*v[0]) + par[2]*v[0] + par[3];
  //  return par[0] + par[1]*v[0];// + par[2]*v[0]*v[0] + par[3]*v[0]*v[0]*v[0];
    return par[2]  * (1. + TMath::Erf((v[0]-par[0])/(TMath::Sqrt(2)*par[1])));

  //  Double_t result = par[0] * TMath::Landau(v[0],par[1], par[2]);
  //Double_t result = par[0] * TMath::Poisson(v[0],par[1]);
     // Double_t result = par[0] * TMath::Gaus(v[0],par[1],par[2]);

  //  Double_t result = par[3] + (1 / (v[0]*TMath::Sqrt(2*TMath::Pi())*par[0])) * TMath::Exp((-1*(TMath::Log(v[0]) - par[1])*(TMath::Log(v[0]) - par[1]))/(2*par[0]*par[0]));
    // par[0] * TMath::LogNormal(v[0], par[1]);
    // (1 / (v[0]*TMath::Sqrt(2*TMath::Pi())*par[0])) * TMath::Exp((-1*(TMath::LN(v[0]) - par[1])*(TMath::Ln(v[0]) - par[1]))/(2*par[0]*par[0]));

     //   return result;

}
 Double_t fitf(Double_t *v, Double_t *par)
   {
     //return par[0] + par[1]*v[0] + par[2]*v[0]*v[0];
      return 0.5 * par[0] * (1. + TMath::Erf((v[0]-par[1])/(sqrt(2)*par[2])))*(1. + TMath::Erf((v[0]-par[3])/(sqrt(2)*par[4])));
     // return 0.5 * par[0] * (1. + TMath::Erf((v[0]-par[1])/(sqrt(2)*par[2])));//*(1. + TMath::Erf((v[0]-par[3])/(sqrt(2)*par[4])));

     //return 0.5 * (par[0] + par[5]*v[0] + par[6]*v[0]*v[0]) * (1. + TMath::Erf((v[0]-par[1])/(sqrt(2)*par[2])))*(1. + TMath::Erf((v[0]-par[3])/(sqrt(2)*par[4])));

   }
double GetEff (int lumi, double setoverpt){
  double eff = 0;
  double par0 = 0;
  double par1 = 0;
  double par2 = 0;
  double par3 = 0;
  double par4 = 0;

 par0 = 1.13363;
  par1 = -0.0884468;
  par2 = 0.0377727;
  par3 = -0.00927218;
  par4 = 0.000652768;

  lumi = lumi + 0;


 //setoverpt = 1;
 //eff = 1;// 0.5 * par2 * (1. + TMath::Erf((setoverpt-par0)/(sqrt(2)*par1)));
  //  cout<<setoverpt<<"  "<<eff<<endl;
 eff =  par0 + par1*setoverpt + par2*setoverpt*setoverpt + par3*setoverpt*setoverpt*setoverpt + par4*setoverpt*setoverpt*setoverpt*setoverpt;

  return eff;
}
Double_t langaufun(Double_t *x, Double_t *par) {
  //from http://www.slac.stanford.edu/comp/unix/package/cernroot/30309/htmldoc/examples/langaus.C.html
   //Fit parameters:
   //par[0]=Width (scale) parameter of Landau density
   //par[1]=Most Probable (MP, location) parameter of Landau density
   //par[2]=Total area (integral -inf to inf, normalization constant)
   //par[3]=Width (sigma) of convoluted Gaussian function
   //
   //In the Landau distribution (represented by the CERNLIB approximation), 
   //the maximum is located at x=-0.22278298 with the location parameter=0.
   //This shift is corrected within this function, so that the actual
   //maximum is identical to the MP parameter.

      // Numeric constants
      Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
      Double_t mpshift  = -0.22278298;       // Landau maximum location

      // Control constants
      Double_t np = 100.0;      // number of convolution steps
      Double_t sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

      // Variables
      Double_t xx;
      Double_t mpc;
      Double_t fland;
      Double_t sum = 0.0;
      Double_t xlow,xupp;
      Double_t step;
      Double_t i;


      // MP shift correction
      mpc = par[1] - mpshift * par[0]; 

      // Range of convolution integral
      xlow = x[0] - sc * par[3];
      xupp = x[0] + sc * par[3];

      step = (xupp-xlow) / np;

      // Convolution integral of Landau and Gaussian by sum
      for(i=1.0; i<=np/2; i++) {
         xx = xlow + (i-.5) * step;
         fland = TMath::Landau(xx,mpc,par[0]) / par[0];
         sum += fland * TMath::Gaus(x[0],xx,par[3]);

         xx = xupp - (i-.5) * step;
         fland = TMath::Landau(xx,mpc,par[0]) / par[0];
         sum += fland * TMath::Gaus(x[0],xx,par[3]);
      }

      return (par[2] * step * sum * invsq2pi / par[3]);
}
