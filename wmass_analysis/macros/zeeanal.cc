#include "TH1F.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TVector2.h"
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>

#define maxT 1000

#define doOverlay true
#define theFudge 1.

#define doPrints false

using namespace std;

void zeeanal() {

  // Book histograms
  TH1F* th1Mass = new TH1F("Mass","Mass",40,60,120);
  //
  TH1F* th1PT = new TH1F("PT","PT",40,25,90);
  TH1F* th1MT = new TH1F("MT","MT",40,50,120);
  TH1F* th1Met = new TH1F("Met","Met",40,25,90);
  TH1F* th1UT = new TH1F("UT","UT",40,0,15);
  TH1F* th1Upara = new TH1F("Upara","Upara",40,-15,15);
  TH1F* th1Uperp = new TH1F("Uperp","Uperp",40,-15,15);

  // Read plots for overlay, if requested
  TH1D* th1OffiPT;
  TH1D* th1OffiMT;
  TH1D* th1OffiMet;
  TH1D* th1OffiUT;
  TH1D* th1OffiUpara;
  TH1D* th1OffiUperp;
  if (doOverlay) {
    TFile* f = new TFile("/home/stark/dummy/BkgStudy/bkgd_shape_zee_new.root");
    th1OffiPT=(TH1D*)f->Get("WCandElecPt_Spatial_Match_0");
    th1OffiMT=(TH1D*)f->Get("WCandMt_Spatial_Match_0");
    th1OffiMet=(TH1D*)f->Get("WCandMet_Spatial_Match_0");
    th1OffiUT=(TH1D*)f->Get("WCandRecoilPt_Spatial_Match_0");
    th1OffiUpara=(TH1D*)f->Get("WCandUPara_Spatial_Match_0");
    th1OffiUperp=(TH1D*)f->Get("WCandUPerp_Spatial_Match_0");
  }

  // Buffer for one file
  Int_t runNo, evtNo;
  Float_t instlumi, WScalarEt;
  Float_t wPt, wPhi, wUt, wUPhi;
  Float_t emPt, emEta, emPhi;
  Int_t emCharge;
  Float_t vtx_x,vtx_y,vtx_z;
  Int_t nT;
  Float_t TPt[maxT], TEta[maxT], TPhi[maxT];
  Int_t TCharge[maxT];
  Float_t Trdca[maxT], Tz[maxT];
  Int_t Tnhit[maxT], Tncft[maxT], Tnsmt[maxT];
  unsigned long int Tmask0[maxT], Tmask1[maxT], Tmask2[maxT];
  Int_t Tisoflag[maxT];
  Float_t Tmtc[maxT][14], Te33[maxT][3], Te55[maxT][3];

  // Loop through events
  Int_t nEvt=0;
  fstream rein("ZEEovl_bkg_file_wenu.txt",ios::in);
  //fstream rein("WENUovl_bkg_file_wenu.txt",ios::in);
  //fstream rein("Wdata_bkg_file_wenu.txt",ios::in);
  while (rein.good()) {
    rein>>runNo>>evtNo>>instlumi>>WScalarEt>>wPt>>wPhi>>wUt>>wUPhi>>emPt>>emEta>>emPhi>>emCharge;
    if (rein.eof()) break;
    rein>>vtx_x>>vtx_y>>vtx_z;
    rein>>nT;
    for (Int_t i=0; i<nT; i++) {
      rein>>TPt[i]>>TEta[i]>>TPhi[i]>>TCharge[i]>>Trdca[i]>>Tz[i]>>Tnhit[i]>>Tncft[i]>>Tnsmt[i]>>Tmask0[i]>>Tmask1[i]>>Tmask2[i];
      rein>>Tisoflag[i];
      if (Tisoflag[i]) {
	rein>>Tmtc[i][0]>>Tmtc[i][1]>>Tmtc[i][2]>>Tmtc[i][3]>>Tmtc[i][4]>>Tmtc[i][5]>>Tmtc[i][6]>>Tmtc[i][7]>>Tmtc[i][8]>>Tmtc[i][9]>>Tmtc[i][10]>>Tmtc[i][11]>>Tmtc[i][12]>>Tmtc[i][13];
	rein>>Te33[i][0]>>Te33[i][1]>>Te33[i][2];
	rein>>Te55[i][0]>>Te55[i][1]>>Te55[i][2];
      }
    }
    nEvt++;
    // analysis
    Int_t nCand=0;
    for (Int_t i=0; i<nT; i++) {
      if (TPt[i]<25) continue;
      if ((fabs(TEta[i])>1.5)||(fabs(TEta[i])<1.0)) continue;
      if (emCharge==-2) continue;
      if ((emCharge*TCharge[i])==0) continue;
      if ((emCharge*TCharge[i])>0) continue;
      if (!Tnsmt[i]) continue;
      if (fabs(Tz[i]-vtx_z)>1) continue;
      //
      if (doPrints) cout<<TPt[i]<<" " <<Tnhit[i]<<" "<<Tncft[i]<<" "<<Tnsmt[i]<<"  "<<Tisoflag[i]<<"  "<<Trdca[i]<<" "<<Tz[i]<<"  "<<vtx_z<<endl;
      TLorentzVector tr;
      tr.SetPtEtaPhiM(TPt[i],TEta[i],TPhi[i],0.);
      Int_t nIsoTrk=0;
      Float_t pTIsoTrk=0;
      for (Int_t ii=0; ii<nT; ii++) {
	if (i==ii) continue;
	TLorentzVector tr2;
	tr2.SetPtEtaPhiM(TPt[ii],TEta[ii],TPhi[ii],0.);
	Float_t dR=tr2.DeltaR(tr);
	if (dR<0.4) {
	  if (doPrints) cout<<dR<<"  "<<TPt[ii]<<" "<<Tnhit[ii]<<" "<<Tncft[ii]<<" "<<Tnsmt[ii]<<endl;
	  nIsoTrk++;
	  pTIsoTrk+=TPt[ii];
	}
      }
      if (doPrints) cout<<" => "<<nIsoTrk<<" "<<pTIsoTrk<<endl;
      if (pTIsoTrk>4) continue;
      //
      nCand++;
      TLorentzVector e;
      e.SetPtEtaPhiM(emPt,emEta,emPhi,0.);
      TLorentzVector Z=tr+e;
      th1Mass->Fill(Z.M());
      if (Z.M()>70 && Z.M()<110) {
	TVector2 Etwo(e.Px(),e.Py());
	TLorentzVector udummy;
	udummy.SetPtEtaPhiM(wUt,0,wUPhi,0.);
	TVector2 Utwo(udummy.Px(),udummy.Py());
	th1Upara->Fill(Utwo * Etwo.Unit());
	TVector2 perp_direction = Etwo.Rotate(TMath::Pi()/2.);
	th1Uperp->Fill(Utwo * perp_direction.Unit());
	//
	th1PT->Fill(emPt);
	TVector2 Met=-1*(Etwo+Utwo);
	double dphi = Etwo.DeltaPhi(Met);
	double tmass = sqrt(2.0*emPt*Met.Mod()*(1-cos(dphi)));
	th1MT->Fill(tmass);
	
	th1Met->Fill(Met.Mod());
	th1UT->Fill(wUt);
      }
    }
    //cout<<nCand<<endl;
  }
  rein.close();
  cout<<"Read "<<nEvt<<" events."<<endl;

  // Draw
  TCanvas* cM = new TCanvas("cM","cM",800,600);
  th1Mass->Draw();
  TCanvas* cU = new TCanvas("cU","cU",600,800);
  cU->Divide(1,2);
  cU->cd(1);
  th1Upara->Draw();
th1OffiUpara->Scale(theFudge*th1Upara->GetXaxis()->GetBinWidth(1)/th1OffiUpara->GetXaxis()->GetBinWidth(1)*th1Upara->Integral()/th1OffiUpara->Integral());
  th1OffiUpara->SetLineColor(2);
  th1OffiUpara->Draw("same");
  cU->cd(2);
  th1Uperp->Draw();
  th1OffiUperp->Scale(theFudge*th1Uperp->GetXaxis()->GetBinWidth(1)/th1OffiUperp->GetXaxis()->GetBinWidth(1)*th1Uperp->Integral()/th1OffiUperp->Integral());
  th1OffiUperp->SetLineColor(2);
  th1OffiUperp->Draw("same");
  cU->cd();
  TCanvas* cMisc = new TCanvas("cMisc","cMisc",800,800);
  cMisc->Divide(2,2);
  cMisc->cd(1);
  th1PT->Draw();
  th1OffiPT->Scale(theFudge*th1PT->GetXaxis()->GetBinWidth(1)/th1OffiPT->GetXaxis()->GetBinWidth(1)*th1PT->Integral()/th1OffiPT->Integral());
  th1OffiPT->SetLineColor(2);
  th1OffiPT->Draw("same");
  cMisc->cd(2);
  th1MT->Draw();
  th1OffiMT->Scale(theFudge*th1MT->GetXaxis()->GetBinWidth(1)/th1OffiMT->GetXaxis()->GetBinWidth(1)*th1MT->Integral()/th1OffiMT->Integral());
  th1OffiMT->SetLineColor(2);
  th1OffiMT->Draw("same");
  cMisc->cd(3);
  th1Met->Draw();
  th1OffiMet->Scale(theFudge*th1Met->GetXaxis()->GetBinWidth(1)/th1OffiMet->GetXaxis()->GetBinWidth(1)*th1Met->Integral()/th1OffiMet->Integral());
  th1OffiMet->SetLineColor(2);
  th1OffiMet->Draw("same");
  cMisc->cd(4);
  th1UT->Draw();
  th1OffiUT->Scale(theFudge*th1UT->GetXaxis()->GetBinWidth(1)/th1OffiUT->GetXaxis()->GetBinWidth(1)*th1UT->Integral()/th1OffiUT->Integral());
  th1OffiUT->SetLineColor(2);
  th1OffiUT->Draw("same");
  cMisc->cd();

}

