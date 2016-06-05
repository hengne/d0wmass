#include <vector>
#include <string>
#include "TH1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TMath.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TCanvas.h"
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
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TObject.h>

void ContLumiPlot(){
  TString rootfile = "/work/rebel-clued0/jenny/workshop/devel_p21.21.00/findEsEo_rebin_x_out_run2b4_lumi02_002step_new.root";
  TString rootfile2 = "/work/rebel-clued0/jenny/workshop/devel_p21.21.00/findEsEo_rebin_x_out_run2b4_lumi24_002step_new.root";
  TString rootfile3 = "/work/rebel-clued0/jenny/workshop/devel_p21.21.00/findEsEo_rebin_x_out_run2b4_lumi46_002step_new.root";
  TString rootfile4 = "/work/rebel-clued0/jenny/workshop/devel_p21.21.00/findEsEo_rebin_x_out_run2b4_lumi6999_002step_new.root";
  TString rootfile5 = "/work/rebel-clued0/jenny/workshop/devel_p21.21.00/findEsEo_rebin_x_out_run2b4_lumiall_002step_new.root";
  

   TCanvas *c1 = new TCanvas("c1","c1",800,800);
  //.x /home/jholzbau/rootlogon.C

 TH1 *frame = new TH1F("frame","",100,1.0,1.1);
 frame->SetMinimum(-0.1);
   frame->SetMaximum(0.9);
   frame->SetDirectory(0);
   frame->SetStats(0);
   frame->Draw(" ");

 TFile *input1(0);

 if (!gSystem->AccessPathName( rootfile )) {
   cout << "accessing " << rootfile << endl;
   input1 = TFile::Open( rootfile );
 } 
 else{
   cout<< "problem accessing "<<rootfile<< endl;
   exit(0);
 }
 TF1 *g1 = (TF1*)input1->Get("contout");

 TFile *input2(0);

 if (!gSystem->AccessPathName( rootfile2 )) {
   cout << "accessing " << rootfile2 << endl;
   input2 = TFile::Open( rootfile2 );
 } 
 else{
   cout<< "problem accessing "<<rootfile2<< endl;
   exit(0);
 }
 TF1 *g2 = (TF1*)input2->Get("contout");

 TFile *input3(0);

 if (!gSystem->AccessPathName( rootfile3 )) {
   cout << "accessing " << rootfile3 << endl;
   input3 = TFile::Open( rootfile3 );
 } 
 else{
   cout<< "problem accessing "<<rootfile3<< endl;
   exit(0);
 }
 TF1 *g3 = (TF1*)input3->Get("contout");


 TFile *input4(0);

 if (!gSystem->AccessPathName( rootfile4 )) {
   cout << "accessing " << rootfile4 << endl;
   input4 = TFile::Open( rootfile4 );
 } 
 else{
   cout<< "problem accessing "<<rootfile4<< endl;
   exit(0);
 }
 TF1 *g4 = (TF1*)input4->Get("contout");


 TFile *input5(0);

 if (!gSystem->AccessPathName( rootfile5 )) {
   cout << "accessing " << rootfile5 << endl;
   input5 = TFile::Open( rootfile5 );
 } 
 else{
   cout<< "problem accessing "<<rootfile5<< endl;
   exit(0);
 }
 TF1 *g5 = (TF1*)input5->Get("contout");

 TLegend *legend = new TLegend(0.75,0.75,0.94,0.90);
 legend->SetBorderSize(0);
 legend->SetFillColor(0);
 legend->SetHeader("Luminosity Range");
 legend->AddEntry(g1,"0 to 2", "lp");
 legend->AddEntry(g2,"2 to 4", "lp");
 legend->AddEntry(g3,"4 to 6", "lp");
 legend->AddEntry(g4,"6 and higher", "lp");
 legend->AddEntry(g5,"all events", "lp");

 g1->SetName("g1");
 g2->SetName("g2");
 g3->SetName("g3");
 g4->SetName("g4");
 g5->SetName("g5");

  g1->Draw("Cp");
  g2->Draw("Cp");
  g3->Draw("Cp");
  g4->Draw("Cp");
  g5->Draw("Cp");
 
  /**
//THIS SECTION MUST BE RUN BY HAND AFTERWARDS OR GET CRASH
  g1->SetLineColor(1);
  g2->SetLineColor(2);
  g3->SetLineColor(3);
  g4->SetLineColor(4);
  g5->SetLineColor(7);

  g1->Draw("Cp");
  g2->Draw("Cp");
  g3->Draw("Cp");
  g4->Draw("Cp");
  g5->Draw("Cp");
  **/
  legend->Draw("SAME");

gPad->Update();
c1->Update();

//c1->Print("PlotMee_probept_nocut.eps");
//c1->Print("PlotMee_probept_nocut.gif");

c1->Print("PlotContLumi_02step.eps");
c1->Print("PlotContLumi_02step.gif");

}
