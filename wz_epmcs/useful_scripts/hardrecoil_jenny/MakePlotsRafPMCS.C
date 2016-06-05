#include "TProfile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TChain.h"
#include "TString.h"
#include "TVector2.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TMath.h"

#include <fstream>
#include <iostream>

using namespace std;

void profileRMS(TH2D* hist, TH1D* prof, Bool_t resol = false, TString tag="_temp") {

  // Check if they are compatible
  if (!hist || !prof) return;
  if (hist->GetXaxis()->GetNbins() != prof->GetXaxis()->GetNbins()) return;
  if (hist->GetXaxis()->GetXmin() != prof->GetXaxis()->GetXmin()) return;
  if (hist->GetXaxis()->GetXmax() != prof->GetXaxis()->GetXmax()) return;

  for (Int_t i=1; i<=hist->GetXaxis()->GetNbins(); i++) {
    tag += i;
    TH1D* _temp = hist->ProjectionY(tag, i, i, "e");
    if (!resol) {
      prof->SetBinContent(i, _temp->GetRMS());
      prof->SetBinError(i, _temp->GetRMSError());
    } else {
      if (_temp->GetMean() != 0 && _temp->GetRMS() > 0) {
	prof->SetBinContent(i, _temp->GetRMS()/_temp->GetMean());
	prof->SetBinError(i, (_temp->GetRMS()/_temp->GetMean())*TMath::Sqrt(_temp->GetRMSError()*_temp->GetRMSError()/(_temp->GetRMS()*_temp->GetRMS())+_temp->GetMeanError()*_temp->GetMeanError()/(_temp->GetMean()*_temp->GetMean())));
      } else {
	prof->SetBinContent(i, 0.0);
	prof->SetBinError(i, 0.0);
      }
    }
  }

  return;
}

int MakePlotsRafPMCS(TString file="Znunu_Znunurun_PostPMCS_Converted.root", double minlumi = -1., double maxlumi= 9999., double minupt = -1, double maxupt= 9999.) {

  Int_t zptbins=44;
  Double_t zptbounds[] = {0., 0.5, 1., 1.5, 2., 2.5, 3., 3.5, 4., 4.5, 5., 5.5, 6., 6.5, 7., 7.5, 8., 8.5, 9., 9.5, 10., 11., 12., 13., 14., 15., 16., 17., 18., 19., 20., 22., 24., 26., 28., 30., 35., 40., 45., 50., 60., 70., 80., 90., 100.};

   
  TProfile* response_zpt[zptbins+1];
  TProfile* response_zphi[zptbins+1];
  TProfile* response_uphi[zptbins+1];
  TProfile* response_lumi[zptbins+1];
  TProfile* response_zbset[zptbins+1];

  TProfile* response_proj_zpt[zptbins+1];
  TProfile* response_proj_zphi[zptbins+1];
  TProfile* response_proj_uphi[zptbins+1];
  TProfile* response_proj_lumi[zptbins+1];
  TProfile* response_proj_zbset[zptbins+1];

  TH1D* lumi_zpt[zptbins+1];
  TH1D* set_zpt[zptbins+1];
  TH1D* zbset_zpt[zptbins+1];

  TH1D* chargeratio_uphi[zptbins+1];
  TH1D* chargeratio_uphim[zptbins+1];
  

  TH1D* set_lumi[zptbins+1];
  TH1D* zbset_lumi[zptbins+1];
  TH1D* uphi_lumi[zptbins+1];
  TH1D* zphi_lumi[zptbins+1];
  TH1D* zphi_uphi[zptbins+1];

  TH1D* delta_phi_zpt[zptbins+1];
  TH1D* delta_phi_zphi[zptbins+1];
  TH1D* delta_phi_uphi[zptbins+1];
  TH1D* delta_phi_lumi[zptbins+1];
  TH1D* delta_phi_zbset[zptbins+1];

  TH2D* lumi_zpt_hist[zptbins+1];
  TH2D* set_zpt_hist[zptbins+1];
  TH2D* zbset_zpt_hist[zptbins+1];

  TH2D* set_lumi_hist[zptbins+1];
  TH2D* zbset_lumi_hist[zptbins+1];
  TH2D* uphi_lumi_hist[zptbins+1];
  TH2D* zphi_lumi_hist[zptbins+1];
  TH2D* zphi_uphi_hist[zptbins+1];

  TH2D* delta_phi_zpt_hist[zptbins+1];
  TH2D* delta_phi_zphi_hist[zptbins+1];
  TH2D* delta_phi_uphi_hist[zptbins+1];
  TH2D* delta_phi_lumi_hist[zptbins+1];
  TH2D* delta_phi_zbset_hist[zptbins+1];

  TH1D* resolution_zpt[zptbins+1];
  TH1D* resolution_zphi[zptbins+1];
  TH1D* resolution_uphi[zptbins+1];
  TH1D* resolution_lumi[zptbins+1];
  TH1D* resolution_zbset[zptbins+1];

  TH2D* resolution_zpt_hist[zptbins+1];
  TH2D* resolution_zphi_hist[zptbins+1];
  TH2D* resolution_uphi_hist[zptbins+1];
  TH2D* resolution_lumi_hist[zptbins+1];
  TH2D* resolution_zbset_hist[zptbins+1];
  
  response_zpt[0] = new TProfile(TString::Format("response_zpt_%d", 0), TString::Format("response_zpt_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1]);
  response_zphi[0] = new TProfile(TString::Format("response_zphi_%d", 0), TString::Format("response_zphi_%d", 0), 64, 0., TMath::TwoPi());
  response_uphi[0] = new TProfile(TString::Format("response_uphi_%d", 0), TString::Format("response_uphi_%d", 0), 64, 0., TMath::TwoPi());
  response_lumi[0] = new TProfile(TString::Format("response_lumi_%d", 0), TString::Format("response_lumi_%d", 0), 20, 0., 10.);
  response_zbset[0] = new TProfile(TString::Format("response_zbset_%d", 0), TString::Format("response_zbset_%d", 0), 200, 0., 20.);
  
  response_proj_zpt[0] = new TProfile(TString::Format("response_proj_zpt_%d", 0), TString::Format("response_proj_zpt_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1]);
  response_proj_zphi[0] = new TProfile(TString::Format("response_proj_zphi_%d", 0), TString::Format("response_proj_zphi_%d", 0), 64, 0., TMath::TwoPi());
  response_proj_uphi[0] = new TProfile(TString::Format("response_proj_uphi_%d", 0), TString::Format("response_proj_uphi_%d", 0), 64, 0., TMath::TwoPi());
  response_proj_lumi[0] = new TProfile(TString::Format("response_proj_lumi_%d", 0), TString::Format("response_proj_lumi_%d", 0), 20, 0., 10.);
  response_proj_zbset[0] = new TProfile(TString::Format("response_proj_zbset_%d", 0), TString::Format("response_proj_zbset_%d", 0), 200, 0., 20.);
  
  delta_phi_zpt_hist[0] = new TH2D(TString::Format("delta_phi_zpt_hist_%d", 0), TString::Format("delta_phi_zpt_hist_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1], 64, 0., TMath::Pi());
  delta_phi_zphi_hist[0] = new TH2D(TString::Format("delta_phi_zphi_hist_%d", 0), TString::Format("delta_phi_zphi_hist_%d", 0), 64, 0., TMath::TwoPi(), 64, 0., TMath::Pi());
  delta_phi_uphi_hist[0] = new TH2D(TString::Format("delta_phi_uphi_hist_%d", 0), TString::Format("delta_phi_uphi_hist_%d", 0), 64, 0., TMath::TwoPi(), 64, 0., TMath::Pi());
  delta_phi_lumi_hist[0] = new TH2D(TString::Format("delta_phi_lumi_hist_%d", 0), TString::Format("delta_phi_lumi_hist_%d", 0), 20, 0., 10., 64, 0., TMath::Pi());
  delta_phi_zbset_hist[0] = new TH2D(TString::Format("delta_phi_zbset_hist_%d", 0), TString::Format("delta_phi_zbset_hist_%d", 0), 200, 0., 20., 64, 0., TMath::Pi());

lumi_zpt_hist[0] = new TH2D(TString::Format("lumi_zpt_hist_%d", 0), TString::Format("lumi_zpt_hist_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1],  20, 0., 10.);
set_zpt_hist[0] = new TH2D(TString::Format("set_zpt_hist_%d", 0), TString::Format("set_zpt_hist_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1], 200, 0., 200.);
zbset_zpt_hist[0] = new TH2D(TString::Format("zbset_zpt_hist_%d", 0), TString::Format("zbset_zpt_hist_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1], 200, 0., 20.);
  chargeratio_uphi[0] = new TH1D(TString::Format("chargeratio_uphi_%d", 0), TString::Format("chargeratio_uphi_%d", 0), 64, 0., TMath::TwoPi());
chargeratio_uphim[0] = new TH1D(TString::Format("chargeratio_uphim_%d", 0), TString::Format("chargeratio_uphim_%d", 0), 64, 0., TMath::TwoPi());


set_lumi_hist[0] = new TH2D(TString::Format("set_lumi_hist_%d", 0), TString::Format("set_lumi_hist_%d", 0), 20, 0., 10., 200, 0., 200.);
zbset_lumi_hist[0] = new TH2D(TString::Format("zbset_lumi_hist_%d", 0), TString::Format("zbset_lumi_hist_%d", 0), 20, 0., 10.,  200, 0., 20.);
uphi_lumi_hist[0] = new TH2D(TString::Format("uphi_lumi_hist_%d", 0), TString::Format("uphi_lumi_hist_%d", 0), 20, 0., 10., 64, 0., TMath::TwoPi());
zphi_lumi_hist[0] = new TH2D(TString::Format("zphi_lumi_hist_%d", 0), TString::Format("zphi_lumi_hist_%d", 0), 20, 0., 10., 64, 0., TMath::TwoPi());
zphi_uphi_hist[0] = new TH2D(TString::Format("zphi_uphi_hist_%d", 0), TString::Format("zphi_uphi_hist_%d", 0), 64, 0., TMath::TwoPi(), 64, 0., TMath::TwoPi());

 lumi_zpt[0] = new TH1D(TString::Format("lumi_zpt_%d", 0), TString::Format("lumi_zpt_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1]);
 set_zpt[0] = new TH1D(TString::Format("set_zpt_%d", 0), TString::Format("set_zpt_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1]);
 zbset_zpt[0] = new TH1D(TString::Format("zbset_zpt_%d", 0), TString::Format("zbset_zpt_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1]);


set_lumi[0] = new TH1D(TString::Format("set_lumi_%d", 0), TString::Format("set_lumi_%d", 0), 20, 0., 10.);
zbset_lumi[0] = new TH1D(TString::Format("zbset_lumi_%d", 0), TString::Format("zbset_lumi_%d", 0), 20, 0., 10.);
uphi_lumi[0] = new TH1D(TString::Format("uphi_lumi_%d", 0), TString::Format("uphi_lumi_%d", 0), 20, 0., 10.);
zphi_lumi[0] = new TH1D(TString::Format("zphi_lumi_%d", 0), TString::Format("zphi_lumi_%d", 0), 20, 0., 10.);
zphi_uphi[0] = new TH1D(TString::Format("zphi_uphi_%d", 0), TString::Format("zphi_uphi_%d", 0), 64, 0., TMath::TwoPi());


  delta_phi_zpt[0] = new TH1D(TString::Format("delta_phi_zpt_%d", 0), TString::Format("delta_phi_zpt_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1]);
  delta_phi_zphi[0] = new TH1D(TString::Format("delta_phi_zphi_%d", 0), TString::Format("delta_phi_zphi_%d", 0), 64, 0., TMath::TwoPi());
  delta_phi_uphi[0] = new TH1D(TString::Format("delta_phi_uphi_%d", 0), TString::Format("delta_phi_uphi_%d", 0), 64, 0., TMath::TwoPi());
  delta_phi_lumi[0] = new TH1D(TString::Format("delta_phi_lumi_%d", 0), TString::Format("delta_phi_lumi_%d", 0), 20, 0., 10.);
  delta_phi_zbset[0] = new TH1D(TString::Format("delta_phi_zbset_%d", 0), TString::Format("delta_phi_zbset_%d", 0), 200, 0., 20.);

  resolution_zpt_hist[0] = new TH2D(TString::Format("resolution_zpt_hist_%d", 0), TString::Format("resolution_zpt_hist_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1], 400, 0., 200.);
  resolution_zphi_hist[0] = new TH2D(TString::Format("resolution_zphi_hist_%d", 0), TString::Format("resolution_zphi_hist_%d", 0), 64, 0., TMath::TwoPi(), 400, 0., 200.);
  resolution_uphi_hist[0] = new TH2D(TString::Format("resolution_uphi_hist_%d", 0), TString::Format("resolution_uphi_hist_%d", 0), 64, 0., TMath::TwoPi(), 400, 0., 200.);
  resolution_lumi_hist[0] = new TH2D(TString::Format("resolution_lumi_hist_%d", 0), TString::Format("resolution_lumi_hist_%d", 0), 20, 0., 10., 400, 0., 200.);
  resolution_zbset_hist[0] = new TH2D(TString::Format("resolution_zbset_hist_%d", 0), TString::Format("resolution_zbset_hist_%d", 0), 200, 0., 20., 400, 0., 200.);

  resolution_zpt[0] = new TH1D(TString::Format("resolution_zpt_%d", 0), TString::Format("resolution_zpt_%d", 0), 500, zptbounds[0], zptbounds[zptbins-1]);
  resolution_zphi[0] = new TH1D(TString::Format("resolution_zphi_%d", 0), TString::Format("resolution_zphi_%d", 0), 64, 0., TMath::TwoPi());
  resolution_uphi[0] = new TH1D(TString::Format("resolution_uphi_%d", 0), TString::Format("resolution_uphi_%d", 0), 64, 0., TMath::TwoPi());
  resolution_lumi[0] = new TH1D(TString::Format("resolution_lumi_%d", 0), TString::Format("resolution_lumi_%d", 0), 20, 0., 10.);
  resolution_zbset[0] = new TH1D(TString::Format("resolution_zbset_%d", 0), TString::Format("resolution_zbset_%d", 0), 200, 0., 20.);
  
  for (Int_t i=1; i<zptbins+1; i++) {
    
    response_zpt[i] = new TProfile(TString::Format("response_zpt_%d", i), TString::Format("response_zpt_%d", i), 20, zptbounds[i-1], zptbounds[i]);
    response_zphi[i] = new TProfile(TString::Format("response_zphi_%d", i), TString::Format("response_zphi_%d", i), 64, 0., TMath::TwoPi());
    response_uphi[i] = new TProfile(TString::Format("response_uphi_%d", i), TString::Format("response_uphi_%d", i), 64, 0., TMath::TwoPi());
    response_lumi[i] = new TProfile(TString::Format("response_lumi_%d", i), TString::Format("response_lumi_%d", i), 20, 0., 10.);
    response_zbset[i] = new TProfile(TString::Format("response_zbset_%d", i), TString::Format("response_zbset_%d", i), 200, 0., 20.);

    response_proj_zpt[i] = new TProfile(TString::Format("response_proj_zpt_%d", i), TString::Format("response_proj_zpt_%d", i), 20, zptbounds[i-1], zptbounds[i]);
    response_proj_zphi[i] = new TProfile(TString::Format("response_proj_zphi_%d", i), TString::Format("response_proj_zphi_%d", i), 64, 0., TMath::TwoPi());
    response_proj_uphi[i] = new TProfile(TString::Format("response_proj_uphi_%d", i), TString::Format("response_proj_uphi_%d", i), 64, 0., TMath::TwoPi());
    response_proj_lumi[i] = new TProfile(TString::Format("response_proj_lumi_%d", i), TString::Format("response_proj_lumi_%d", i), 20, 0., 10.);
    response_proj_zbset[i] = new TProfile(TString::Format("response_proj_zbset_%d", i), TString::Format("response_proj_zbset_%d", i), 200, 0., 20.);
  
    lumi_zpt[i] = new TH1D(TString::Format("lumi_zpt_%d", i), TString::Format("lumi_zpt_%d", i), 20, zptbounds[i-1], zptbounds[i]);
    set_zpt[i] = new TH1D(TString::Format("set_zpt_%d", i), TString::Format("set_zpt_%d", i), 20, zptbounds[i-1], zptbounds[i]);
    zbset_zpt[i] = new TH1D(TString::Format("zbset_zpt_%d", i), TString::Format("zbset_zpt_%d", i), 20, zptbounds[i-1], zptbounds[i]);

set_lumi_hist[i] = new TH2D(TString::Format("set_lumi_hist_%d", i), TString::Format("set_lumi_hist_%d", i), 20, 0., 10., 200, 0., 200.);
zbset_lumi_hist[i] = new TH2D(TString::Format("zbset_lumi_hist_%d", i), TString::Format("zbset_lumi_hist_%d", i), 20, 0., 10.,  200, 0., 20.);
uphi_lumi_hist[i] = new TH2D(TString::Format("uphi_lumi_hist_%d", i), TString::Format("uphi_lumi_hist_%d", i), 20, 0., 10., 64, 0., TMath::TwoPi());
zphi_lumi_hist[i] = new TH2D(TString::Format("zphi_lumi_hist_%d", i), TString::Format("zphi_lumi_hist_%d", i), 20, 0., 10., 64, 0., TMath::TwoPi());
zphi_uphi_hist[i] = new TH2D(TString::Format("zphi_uphi_hist_%d", i), TString::Format("zphi_uphi_hist_%d", i), 64, 0., TMath::TwoPi(), 64, 0., TMath::TwoPi());


set_lumi[i] = new TH1D(TString::Format("set_lumi_%d", i), TString::Format("set_lumi_%d", i), 20, 0., 10.);
zbset_lumi[i] = new TH1D(TString::Format("zbset_lumi_%d", i), TString::Format("zbset_lumi_%d", i), 20, 0., 10.);
uphi_lumi[i] = new TH1D(TString::Format("uphi_lumi_%d", i), TString::Format("uphi_lumi_%d", i), 20, 0., 10.);
zphi_lumi[i] = new TH1D(TString::Format("zphi_lumi_%d", i), TString::Format("zphi_lumi_%d", i), 20, 0., 10.);
zphi_uphi[i] = new TH1D(TString::Format("zphi_uphi_%d", i), TString::Format("zphi_uphi_%d", i), 64, 0., TMath::TwoPi());

chargeratio_uphi[i] = new TH1D(TString::Format("chargeratio_uphi_%d", i), TString::Format("chargeratio_uphi_%d", i), 64, 0., TMath::TwoPi());
chargeratio_uphim[i] = new TH1D(TString::Format("chargeratio_uphim_%d", i), TString::Format("chargeratio_uphim_%d", i), 64, 0., TMath::TwoPi());

    delta_phi_zpt[i] = new TH1D(TString::Format("delta_phi_zpt_%d", i), TString::Format("delta_phi_zpt_%d", i), 20, zptbounds[i-1], zptbounds[i]);
    delta_phi_zphi[i] = new TH1D(TString::Format("delta_phi_zphi_%d", i), TString::Format("delta_phi_zphi_%d", i), 64, 0., TMath::TwoPi());
    delta_phi_uphi[i] = new TH1D(TString::Format("delta_phi_uphi_%d", i), TString::Format("delta_phi_uphi_%d", i), 64, 0., TMath::TwoPi());
    delta_phi_lumi[i] = new TH1D(TString::Format("delta_phi_lumi_%d", i), TString::Format("delta_phi_lumi_%d", i), 20, 0., 10.);
    delta_phi_zbset[i] = new TH1D(TString::Format("delta_phi_zbset_%d", i), TString::Format("delta_phi_zbset_%d", i), 200, 0., 20.);

lumi_zpt_hist[i] = new TH2D(TString::Format("lumi_zpt_hist_%d", i), TString::Format("lumi_zpt_hist_%d", i), 20, zptbounds[i-1], zptbounds[i],20, 0., 10.); 
set_zpt_hist[i] = new TH2D(TString::Format("set_zpt_hist_%d", i), TString::Format("set_zpt_hist_%d", i), 20, zptbounds[i-1], zptbounds[i], 200, 0., 200.);
zbset_zpt_hist[i] = new TH2D(TString::Format("zbset_zpt_hist_%d", i), TString::Format("zbset_zpt_hist_%d", i), 20, zptbounds[i-1], zptbounds[i], 200, 0., 20.);

    delta_phi_zpt_hist[i] = new TH2D(TString::Format("delta_phi_zpt_hist_%d", i), TString::Format("delta_phi_zpt_hist_%d", i), 20, zptbounds[i-1], zptbounds[i], 64, 0., TMath::Pi());
    delta_phi_zphi_hist[i] = new TH2D(TString::Format("delta_phi_zphi_hist_%d", i), TString::Format("delta_phi_zphi_hist_%d", i), 64, 0., TMath::TwoPi(), 64, 0., TMath::Pi());
    delta_phi_uphi_hist[i] = new TH2D(TString::Format("delta_phi_uphi_hist_%d", i), TString::Format("delta_phi_uphi_hist_%d", i), 64, 0., TMath::TwoPi(), 64, 0., TMath::Pi());
    delta_phi_lumi_hist[i] = new TH2D(TString::Format("delta_phi_lumi_hist_%d", i), TString::Format("delta_phi_lumi_hist_%d", i), 20, 0., 10., 64, 0., TMath::Pi());
    delta_phi_zbset_hist[i] = new TH2D(TString::Format("delta_phi_zbset_hist_%d", i), TString::Format("delta_phi_zbset_hist_%d", i), 200, 0., 20., 64, 0., TMath::Pi());

    resolution_zpt_hist[i] = new TH2D(TString::Format("resolution_zpt_hist_%d", i), TString::Format("resolution_zpt_hist_%d", i), 20, zptbounds[i-1], zptbounds[i], 400, 0., 200.);
    resolution_zphi_hist[i] = new TH2D(TString::Format("resolution_zphi_hist_%d", i), TString::Format("resolution_zphi_hist_%d", i), 64, 0., TMath::TwoPi(), 400, 0., 200.);
    resolution_uphi_hist[i] = new TH2D(TString::Format("resolution_uphi_hist_%d", i), TString::Format("resolution_uphi_hist_%d", i), 64, 0., TMath::TwoPi(), 400, 0., 200.);
    resolution_lumi_hist[i] = new TH2D(TString::Format("resolution_lumi_hist_%d", i), TString::Format("resolution_lumi_hist_%d", i), 20, 0., 10., 400, 0., 200.);
    resolution_zbset_hist[i] = new TH2D(TString::Format("resolution_zbset_hist_%d", i), TString::Format("resolution_zbset_hist_%d", i), 200, 0., 20., 400, 0., 200.);
    
    resolution_zpt[i] = new TH1D(TString::Format("resolution_zpt_%d", i), TString::Format("resolution_zpt_%d", i), 20, zptbounds[i-1], zptbounds[i]);
    resolution_zphi[i] = new TH1D(TString::Format("resolution_zphi_%d", i), TString::Format("resolution_zphi_%d", i), 64, 0., TMath::TwoPi());
    resolution_uphi[i] = new TH1D(TString::Format("resolution_uphi_%d", i), TString::Format("resolution_uphi_%d", i), 64, 0., TMath::TwoPi());
    resolution_lumi[i] = new TH1D(TString::Format("resolution_lumi_%d", i), TString::Format("resolution_lumi_%d", i), 20, 0., 10.);
    resolution_zbset[i] = new TH1D(TString::Format("resolution_zbset_%d", i), TString::Format("resolution_zbset_%d", i), 200, 0., 20.);

  }

  TChain data("hardrecoilPMCS");
data.Add(file);
  /**
  ifstream inputList(argv[1]);
  TString reader;
  TChain data("hardrecoil");

  while (!inputList.eof()) {
    reader.ReadLine(inputList);
    data.Add(reader);
  }
  inputList.close();
  **/
// Int_t runNum;
//data.SetBranchAddress("runNum",&runNum);
// Int_t eventNum;
// data.SetBranchAddress("eventNum",&eventNum);  
// Int_t ZBrunNum;
// data.SetBranchAddress("ZBrunNum",&ZBrunNum);
// Int_t ZBeventNum;
// data.SetBranchAddress("ZBeventNum",&ZBeventNum);
  Float_t lumi;
  data.SetBranchAddress("lumi", &lumi);
  Float_t SET;
  data.SetBranchAddress("SET", &SET);
  Float_t ZBSET;
  data.SetBranchAddress("ZBSET", &ZBSET);
  //  Float_t tickNum;
  //  data.SetBranchAddress("tickNum", &tickNum);
  Float_t Ztruepx;
  data.SetBranchAddress("Ztruepx", &Ztruepx);
  Float_t Ztruepy;
  data.SetBranchAddress("Ztruepy", &Ztruepy);
  Float_t Ztruepz;
  data.SetBranchAddress("Ztruepz", &Ztruepz);
  Float_t ZtrueE;
  data.SetBranchAddress("ZtrueE", &ZtrueE);
  Float_t utruepx;
  data.SetBranchAddress("utruepx", &utruepx);
  Float_t utruepy;
  data.SetBranchAddress("utruepy", &utruepy);
  Float_t utruepz;
  data.SetBranchAddress("utruepz", &utruepz);
  Float_t utrueE;
  data.SetBranchAddress("utrueE", &utrueE);
  Float_t urecopx;
  data.SetBranchAddress("urecopx", &urecopx);
  Float_t urecopy;
  data.SetBranchAddress("urecopy", &urecopy);
  Float_t urecopT;
  // data.SetBranchAddress("urecopT", &urecopT);
  Float_t urecophi;
  // data.SetBranchAddress("urecophi", &urecophi);
  
  for (Long64_t ientry=0; ientry <= data.GetEntries(); ientry++) {
    data.GetEntry(ientry);
   
    TLorentzVector z_vec(Ztruepx, Ztruepy, Ztruepz, ZtrueE);
    TLorentzVector utrue_vec(utruepx, utruepy, utruepz, utrueE);
    TVector2 utrue_vec2(utruepx, utruepy);
    TVector2 u_vec(urecopx, urecopy);
    urecopT = u_vec.Mod();
    urecophi = TVector2::Phi_0_2pi(u_vec.Phi());
  
    if (lumi < minlumi || lumi > maxlumi){ continue;}
    if (urecopT < minupt || urecopT > maxupt){ continue;}
  
    Int_t zptbin = 0;
    for (Int_t i=0; i < zptbins; i++) {
      if (z_vec.Pt() > zptbounds[i])
	zptbin++;
      else
	break;
    }
  
    if (zptbin > zptbins || zptbin < 1){ continue;}
  
    Double_t response = u_vec.Mod()/utrue_vec2.Mod();
    Double_t resolution = u_vec.Mod();
    Double_t response_proj = (u_vec*utrue_vec2)/(utrue_vec2*utrue_vec2);
    Double_t delta_phi = TMath::Abs(u_vec.DeltaPhi(utrue_vec2));
    ZBSET = TMath::Sqrt(ZBSET);

    response_zpt[zptbin]->Fill(utrue_vec2.Mod(), response);
    response_zphi[zptbin]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), response);
    response_uphi[zptbin]->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), response);
    response_lumi[zptbin]->Fill(lumi, response);
    response_zbset[zptbin]->Fill(ZBSET, response);

    response_proj_zpt[zptbin]->Fill(utrue_vec2.Mod(), response_proj);
    response_proj_zphi[zptbin]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), response_proj);
    response_proj_uphi[zptbin]->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), response_proj);
    response_proj_lumi[zptbin]->Fill(lumi, response_proj);
    response_proj_zbset[zptbin]->Fill(ZBSET, response_proj);

    lumi_zpt_hist[zptbin]->Fill(utrue_vec2.Mod(), lumi);
    set_zpt_hist[zptbin]->Fill(utrue_vec2.Mod(), SET);
    zbset_zpt_hist[zptbin]->Fill(utrue_vec2.Mod(), ZBSET);


   if(u_vec.DeltaPhi(utrue_vec2) > 0) chargeratio_uphi[zptbin]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), 1);
    if(u_vec.DeltaPhi(utrue_vec2) < 0) chargeratio_uphim[zptbin]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), 1);

    if(u_vec.DeltaPhi(utrue_vec2) > 0) chargeratio_uphi[0]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), 1);
    if(u_vec.DeltaPhi(utrue_vec2) < 0) chargeratio_uphim[0]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), 1);


    delta_phi_zpt_hist[zptbin]->Fill(utrue_vec2.Mod(), delta_phi);
    delta_phi_zphi_hist[zptbin]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), delta_phi);
    delta_phi_uphi_hist[zptbin]->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), delta_phi);
    delta_phi_lumi_hist[zptbin]->Fill(lumi, delta_phi);
    delta_phi_zbset_hist[zptbin]->Fill(ZBSET, delta_phi);

    resolution_zpt_hist[zptbin]->Fill(utrue_vec2.Mod(), resolution);
    resolution_zphi_hist[zptbin]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), resolution);
    resolution_uphi_hist[zptbin]->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), resolution);
    resolution_lumi_hist[zptbin]->Fill(lumi, resolution);
    resolution_zbset_hist[zptbin]->Fill(ZBSET, resolution);

    response_zpt[0]->Fill(utrue_vec2.Mod(), response);
    response_zphi[0]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), response);
    response_uphi[0]->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), response);
    response_lumi[0]->Fill(lumi, response);
    response_zbset[0]->Fill(ZBSET, response);

    response_proj_zpt[0]->Fill(utrue_vec2.Mod(), response_proj);
    response_proj_zphi[0]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), response_proj);
    response_proj_uphi[0]->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), response_proj);
    response_proj_lumi[0]->Fill(lumi, response_proj);
    response_proj_zbset[0]->Fill(ZBSET, response_proj);

    lumi_zpt_hist[0]->Fill(utrue_vec2.Mod(), lumi);
    set_zpt_hist[0]->Fill(utrue_vec2.Mod(), SET);
    zbset_zpt_hist[0]->Fill(utrue_vec2.Mod(), ZBSET);
    
    set_lumi[0]->Fill(lumi,SET );
    zbset_lumi[0]->Fill(lumi,ZBSET );
    uphi_lumi[0]->Fill(lumi,TVector2::Phi_0_2pi(u_vec.Phi()));
    zphi_lumi[0]->Fill(lumi,utrue_vec2.Phi());
    zphi_uphi[0]->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), utrue_vec2.Phi());
    
  set_lumi_hist[0]->Fill(lumi,SET );
    zbset_lumi_hist[0]->Fill(lumi,ZBSET );
    uphi_lumi_hist[0]->Fill(lumi,TVector2::Phi_0_2pi(u_vec.Phi()));
    zphi_lumi_hist[0]->Fill(lumi,utrue_vec2.Phi());
    zphi_uphi_hist[0]->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), utrue_vec2.Phi());
    

    delta_phi_zpt_hist[0]->Fill(utrue_vec2.Mod(), delta_phi);
    delta_phi_zphi_hist[0]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), delta_phi);
    delta_phi_uphi_hist[0]->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), delta_phi);
    delta_phi_lumi_hist[0]->Fill(lumi, delta_phi);
    delta_phi_zbset_hist[0]->Fill(ZBSET, delta_phi);

    resolution_zpt_hist[0]->Fill(utrue_vec2.Mod(), resolution);
    resolution_zphi_hist[0]->Fill(TVector2::Phi_0_2pi(utrue_vec2.Phi()), resolution);
    resolution_uphi_hist[0]->Fill(TVector2::Phi_0_2pi(u_vec.Phi()), resolution);
    resolution_lumi_hist[0]->Fill(lumi, resolution);
    resolution_zbset_hist[0]->Fill(ZBSET, resolution);
   
    
  }
 
  profileRMS(set_lumi_hist[0], set_lumi[0],  false, "set_lumi_hist_tmp");
    profileRMS(zbset_lumi_hist[0], zbset_lumi[0], false, "zbset_lumi_hist_tmp");
    profileRMS(uphi_lumi_hist[0], uphi_lumi[0],  false, "uphi_lumi_hist_tmp");
    profileRMS(zphi_lumi_hist[0], zphi_lumi[0],  false, "zphi_lumi_hist_tmp");
    profileRMS(zphi_uphi_hist[0], zphi_uphi[0],  false, "zphi_uphi_hist_tmp");
    

  for (Int_t i=0; i<zptbins+1; i++) {
    profileRMS(lumi_zpt_hist[i], lumi_zpt[i], false, "lumi_zpt_hist_tmp");
    profileRMS(set_zpt_hist[i], set_zpt[i], false, "set_zpt_hist_tmp");
    profileRMS(zbset_zpt_hist[i], zbset_zpt[i], false, "zbset_zpt_hist_tmp");

    profileRMS(delta_phi_zpt_hist[i], delta_phi_zpt[i], false, "delta_phi_zpt_hist_tmp");
    profileRMS(delta_phi_zphi_hist[i], delta_phi_zphi[i], false, "delta_phi_zphi_hist_tmp");
    profileRMS(delta_phi_uphi_hist[i], delta_phi_uphi[i], false, "delta_phi_uphi_hist_tmp");
    profileRMS(delta_phi_lumi_hist[i], delta_phi_lumi[i], false, "delta_phi_lumi_hist_tmp");
    profileRMS(delta_phi_zbset_hist[i], delta_phi_zbset[i], false, "delta_phi_zbset_hist_tmp");

    profileRMS(resolution_zpt_hist[i], resolution_zpt[i], true, "delta_phi_zpt_hist_tmp2");
    profileRMS(resolution_zphi_hist[i], resolution_zphi[i], true, "delta_phi_zphi_hist_tmp2");
    profileRMS(resolution_uphi_hist[i], resolution_uphi[i], true, "delta_phi_uphi_hist_tmp2");
    profileRMS(resolution_lumi_hist[i], resolution_lumi[i], true, "delta_phi_lumi_hist_tmp2");
    profileRMS(resolution_zbset_hist[i], resolution_zbset[i], true, "delta_phi_zbset_hist_tmp2");
  }

  TFile* output = new TFile("plotsPMCSNEW.root", "RECREATE");
  chargeratio_uphi[0]->Write();
chargeratio_uphim[0]->Write();

chargeratio_uphi[0]->Divide(chargeratio_uphim[0]);
 chargeratio_uphi[0]->Write();

  set_lumi[0]->Write();
  zbset_lumi[0]->Write();
  uphi_lumi[0]->Write();
  zphi_lumi[0]->Write();
  zphi_uphi[0]->Write();
    
 set_lumi_hist[0]->Write();
  zbset_lumi_hist[0]->Write();
  uphi_lumi_hist[0]->Write();
  zphi_lumi_hist[0]->Write();
  zphi_uphi_hist[0]->Write();
    


  for (Int_t i=0; i<zptbins+1; i++) {  
    response_zpt[i]->Write();
    resolution_zpt[i]->Write();
    response_proj_zpt[i]->Write();
    delta_phi_zpt[i]->Write();
lumi_zpt[i]->Write();
set_zpt[i]->Write();
zbset_zpt[i]->Write();
  }

  for (Int_t i=0; i<zptbins+1; i++) {  
    response_zphi[i]->Write();
    resolution_zphi[i]->Write();
    response_proj_zphi[i]->Write();
    delta_phi_zphi[i]->Write();
  }

  for (Int_t i=0; i<zptbins+1; i++) {  
    response_uphi[i]->Write();
    resolution_uphi[i]->Write();
    response_proj_uphi[i]->Write();
    delta_phi_uphi[i]->Write();
  }

  for (Int_t i=0; i<zptbins+1; i++) {  
    response_lumi[i]->Write();
    resolution_lumi[i]->Write();
    response_proj_lumi[i]->Write();
    delta_phi_lumi[i]->Write();
  }

  for (Int_t i=0; i<zptbins+1; i++) {  
    response_zbset[i]->Write();
    resolution_zbset[i]->Write();
    response_proj_zbset[i]->Write();
    delta_phi_zbset[i]->Write();
  }

  output->Close();
  return (0);
}

