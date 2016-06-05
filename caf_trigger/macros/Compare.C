#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;

void Compare()
{
  cout << endl;
  cout << "----------------------------------------" << endl;
  cout << "--                                    --" << endl;
  cout << "--         Comparison Plots           --" << endl;
  cout << "--                                    --" << endl;
  cout << "----------------------------------------" << endl;
  cout << endl;

  cout << "Running Aran's ROOT logon macro." << endl;
  gROOT->ProcessLine(".x ~/rootlogon_aran.C");
  cout << endl;

  //  TString toptrigger_filename = "TopTriggerEff_Emu.root";
  TString toptrigger_filename = "TopTriggerEff_MuJets.root";
  std::string filename = toptrigger_filename;

  std::string channel;
  std::string channel_file;
  
  if ( filename.find("Emu") != string::npos || filename.find("EMu") != string::npos ) {
    channel = "t#bar{t}#rightarrow e+#mu";
    channel_file = "EMu";
  }
  else if ( filename.find("MuJets") != string::npos ) {
    channel = "tb #rightarrow #mu+Jets";
    channel_file = "MuJets";
  }
  else if ( filename.find("EJets") != string::npos ) {
    channel = "tqb #rightarrow e+Jets";
    channel_file = "EJets";
  }
  else {
    cout << "Channel not recognized" << endl;
    cout << "Setting Channel to `unknown`" << endl;
    channel = "Unknown";
  }

  TH1F *h_normal, *h_trigger;
  bool rms = false;
  int rebin = 1;

  Float_t l1x1;
  Float_t l1x2;
  Float_t l1y1;
  Float_t l1y2;

  for ( int plot = 0; plot < 8; plot++ ) {
    std::stringstream title;
    std::stringstream xtitle;
    std::stringstream c1_name;

    if ( channel_file == "EJets" && ( plot == 4 || plot == 5 ) ) { continue; }
    if ( channel_file == "MuJets" && ( plot == 6 || plot == 7 ) ) { continue; }

    if ( plot == 0 ) {
      TFile *toptrigger_file_file = TFile::Open(toptrigger_filename);
      h_normal = (TH1F*)LeadingJetPt;
      h_trigger = (TH1F*)LeadingJetPtTrigger;
      rebin = 3;
      c1_name << channel_file << "_" << "LeadingJetPt.eps";
      title << "Leading Jet P_{T}  --  Channel: " << channel;
      xtitle << "Leading Jet P_{T} [GeV]";
      l1x1 = 0.50;
      if ( rms ) {
	l1x1 = 0.15;
      }
      l1x2 = l1x1 + 0.15;
      l1y1 = 0.60;
      l1y2 = l1y1 + 0.25;
    }
    else if ( plot == 1 ) {
      TFile *toptrigger_file_file = TFile::Open(toptrigger_filename);
      h_normal = (TH1F*)SecondJetPt;
      h_trigger = (TH1F*)SecondJetPtTrigger;
      rebin = 2;
      c1_name << channel_file << "_" << "SecondJetPt.eps";
      title << "Second Jet P_{T}  --  Channel: " << channel;
      xtitle << "Second Jet P_{T} [GeV]";
      l1x1 = 0.50;
      if ( rms ) {
	l1x1 = 0.15;
      }
      l1x2 = l1x1 + 0.15;
      l1y1 = 0.60;
      l1y2 = l1y1 + 0.25;
    }
    else if ( plot == 2 ) {
      TFile *toptrigger_file_file = TFile::Open(toptrigger_filename);
      h_normal = (TH1F*)LeadingJetEta;
      h_trigger = (TH1F*)LeadingJetEtaTrigger;
      rebin = 3;
      c1_name << channel_file << "_" << "LeadingJetEta.eps";
      title << "Leading Jet #eta  --  Channel: " << channel;
      xtitle << "Leading Jet #eta";
      l1x1 = 0.65;
      if ( rms ) {
	l1x1 = 0.15;
      }
      l1x2 = l1x1 + 0.15;
      l1y1 = 0.60;
      l1y2 = l1y1 + 0.25;
    }
    else if ( plot == 3 ) {
      TFile *toptrigger_file_file = TFile::Open(toptrigger_filename);
      h_normal = (TH1F*)SecondJetEta;
      h_trigger = (TH1F*)SecondJetEtaTrigger;
      rebin = 3;
      c1_name << channel_file << "_" << "SecondJetEta.eps";
      title << "Second Jet #eta  --  Channel: " << channel;
      xtitle << "Second Jet #eta";
      l1x1 = 0.65;
      if ( rms ) {
	l1x1 = 0.15;
      }
      l1x2 = l1x1 + 0.15;
      l1y1 = 0.60;
      l1y2 = l1y1 + 0.25;
    }
    else if ( plot == 4 ) {
      TFile *toptrigger_file_file = TFile::Open(toptrigger_filename);
      h_normal = (TH1F*)MediumMuonPt;
      h_trigger = (TH1F*)MediumMuonPtTrigger;
      rebin = 3;
      c1_name << channel_file << "_" << "MediumMuonPt.eps";
      title << "Medium Muon P_{T}  --  Channel: " << channel;
      xtitle << "Medium Muon P_{T} [GeV]";
      l1x1 = 0.50;
      if ( rms ) {
	l1x1 = 0.15;
      }
      l1x2 = l1x1 + 0.15;
      l1y1 = 0.60;
      l1y2 = l1y1 + 0.25;
    }
    else if ( plot == 5 ) {
      TFile *toptrigger_file_file = TFile::Open(toptrigger_filename);
      h_normal = (TH1F*)MediumMuonEta;
      h_trigger = (TH1F*)MediumMuonEtaTrigger;
      rebin = 3;
      c1_name << channel_file << "_" << "MediumMuonEta.eps";
      title << "Medium Muon #eta  --  Channel: " << channel;
      xtitle << "Medium Muon #eta";
      l1x1 = 0.65;
      if ( rms ) {
	l1x1 = 0.15;
      }
      l1x2 = l1x1 + 0.15;
      l1y1 = 0.60;
      l1y2 = l1y1 + 0.25;
    }
    else if ( plot == 6 ) {
      TFile *toptrigger_file_file = TFile::Open(toptrigger_filename);
      h_normal = (TH1F*)GoodElectronPt;
      h_trigger = (TH1F*)GoodElectronPtTrigger;
      rebin = 3;
      c1_name << channel_file << "_" << "GoodElectronPt.eps";
      title << "Good Electron P_{T}  --  Channel: " << channel;
      xtitle << "Good Electron P_{T} [GeV]";
      l1x1 = 0.50;
      if ( rms ) {
	l1x1 = 0.15;
      }
      l1x2 = l1x1 + 0.15;
      l1y1 = 0.60;
      l1y2 = l1y1 + 0.25;
    }
    else if ( plot == 7 ) {
      TFile *toptrigger_file_file = TFile::Open(toptrigger_filename);
      h_normal = (TH1F*)GoodElectronEta;
      h_trigger = (TH1F*)GoodElectronEtaTrigger;
      rebin = 3;
      c1_name << channel_file << "_" << "GoodElectronEta.eps";
      title << "Good Electron #eta  --  Channel: " << channel;
      xtitle << "Good Electron #eta";
      l1x1 = 0.65;
      if ( rms ) {
	l1x1 = 0.15;
      }
      l1x2 = l1x1 + 0.15;
      l1y1 = 0.60;
      l1y2 = l1y1 + 0.25;
    }

    h_normal->Rebin(rebin);
//     cout << h_normal->Integral() << endl;
//     h_normal->Scale(1.0/h_normal->Integral());
//     cout << h_normal->GetMaximum() << endl;

    h_trigger->Rebin(rebin);
//     cout << h_trigger->Integral() << endl;
//     h_trigger->Scale(1.0/h_trigger->Integral());
//     cout << h_trigger->GetMaximum() << endl;

    //    exit(1);

    int max = TMath::Max(h_normal->GetMaximum(), h_trigger->GetMaximum());
    h_normal->SetMaximum(max*1.1);
    h_normal->SetMinimum(0.0);
    h_normal->SetLineColor(kBlue);
    h_normal->SetLineWidth(3);
    h_normal->SetTitle(title.str().c_str());
    h_normal->SetXTitle(xtitle.str().c_str());
    h_normal->Draw();
    float normal_mean = h_normal->GetMean();
    float normal_rms = h_normal->GetRMS();

    h_trigger->SetMaximum(max*1.1);  
    h_trigger->SetMinimum(0.0);
    h_trigger->SetLineColor(kRed);
    h_trigger->SetLineWidth(3);
    h_trigger->SetTitle(title.str().c_str());
    h_trigger->SetXTitle(xtitle.str().c_str());
    h_trigger->Draw("SAME");
    float trigger_mean = h_trigger->GetMean();
    float trigger_rms = h_trigger->GetRMS();
  
    l = new TLegend(l1x1,l1y1,l1x2,l1y2);
    l->SetBorderSize(0);
    l->SetTextSize(0.04);
    l->SetTextFont(62);
    l->SetFillColor(0); // make it transparent

  
    bool normal = false;

    std::stringstream normal_string;
    normal_string.precision(3);
    if ( normal ) {
      normal_string << "Normal: <x> = " << normal_mean;
    }
    else {
      normal_string << "Normal";
    }
    
    if ( rms ) {
      normal_string << ",  RMS = " << normal_rms;
    }
    std::stringstream trigger_string;
    trigger_string.precision(3);
    if ( normal ) {
      trigger_string << "Trigger: <x> = " << trigger_mean;
    }
    else {
      trigger_string << "Trigger";
    }
    if ( rms ) {
      trigger_string << ",  RMS = " << trigger_rms;
    }
    l->AddEntry(h_normal, normal_string.str().c_str(), "F");
    l->AddEntry(h_trigger, trigger_string.str().c_str(), "F");
    l->Draw("SAME");
  
    c1->SaveAs(c1_name.str().c_str());

    title.clear();
    xtitle.clear();
  }

}
