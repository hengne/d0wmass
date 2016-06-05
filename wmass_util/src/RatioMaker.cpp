#include "wmass_util/RatioMaker.hpp" 
#include <iostream>
RatioMaker::RatioMaker( TFile *Ratiofile, Float_t start, Float_t step, Int_t nstep){
  _outfile = Ratiofile;
  _start = start;
  _step = step;
  _nstep = nstep;
  _outfile->cd();

}  

std::vector<TDirectory *> RatioMaker::MakeRatioHistos(std::vector<TDirectory *>& Zdir, TDirectory* Wdir,char * dirname){
  std::vector<TDirectory *> dir;
  for (Int_t i =0; i < Zdir.size(); i++){
    TString name(dirname);
    name+= "_";
    name+=  Form("%2.5g",_start + i*_step);
    dir.push_back(_outfile->mkdir(name));
    dir[i]->cd();
    TH1D* _h_m_ratio = (TH1D*)((Wdir->Get("wmass_full"))->Clone("m_ratio"));
    _h_m_ratio->SetDirectory(dir[i]);
    TH1D* _h_y_ratio = (TH1D*)((Wdir->Get("_h_wy"))->Clone("y_ratio"));
    _h_y_ratio->SetDirectory(dir[i]);
    TH1D* _h_pt_ratio = (TH1D*)((Wdir->Get("wPt"))->Clone("pt_ratio"));
     _h_pt_ratio->SetDirectory(dir[i]);
    TH1D* _h_tstar1_ratio = (TH1D*)((Wdir->Get("_h_wcoststar"))->Clone("tstar1_ratio"));
    _h_tstar1_ratio->SetDirectory(dir[i]);
     TH1D* _h_tstar2_ratio = (TH1D*)((Wdir->Get("_h_wcoststar2"))->Clone("tstar2_ratio"));
    _h_tstar2_ratio->SetDirectory(dir[i]);
    TH2D* _h_ypt_ratio = (TH2D*)((Wdir->Get("_h_wy_pt"))->Clone("ypt_ratio"));
    _h_ypt_ratio->SetDirectory(dir[i]);
    TH2D* _h_ycost_ratio2 = (TH2D*)((Wdir->Get("_h_wy_cost2"))->Clone("ycost_ratio2"));
    _h_ycost_ratio2->SetDirectory(dir[i]);
    TH2D* _h_ycost_ratio = (TH2D*)((Wdir->Get("_h_wy_cost"))->Clone("ycost_ratio"));
    _h_ycost_ratio->SetDirectory(dir[i]);
    TH2D* _h_ym_ratio = (TH2D*)((Wdir->Get("_h_wy_m"))->Clone("ym_ratio"));
    _h_ym_ratio->SetDirectory(dir[i]);
    TH2D* _h_ptcost_ratio = (TH2D*)((Wdir->Get("_h_wpt_cost"))->Clone("ptcost_ratio"));
    _h_ptcost_ratio->SetDirectory(dir[i]);
    TH2D* _h_ptm_ratio = (TH2D*)((Wdir->Get("_h_wpt_m"))->Clone("ptm_ratio"));
    _h_ptm_ratio->SetDirectory(dir[i]);
    TH2D* _h_costm_ratio = (TH2D*)((Wdir->Get("_h_wcost_m"))->Clone("costm_ratio"));
    _h_costm_ratio->SetDirectory(dir[i]);
    
    
    ScaledRatio(_h_y_ratio, (TH1D*)(Zdir[i]->Get("_h_wy")));
    ScaledRatio(_h_m_ratio, (TH1D*)(Zdir[i]->Get("wmassf")));
    ScaledRatio(_h_pt_ratio, (TH1D*)(Zdir[i]->Get("wPt")));
    ScaledRatio(_h_tstar1_ratio, (TH1D*)(Zdir[i]->Get("_h_wcoststar")));
    ScaledRatio(_h_tstar2_ratio, (TH1D*)(Zdir[i]->Get("_h_wcoststar2")));
    Scaled2DRatio(_h_ypt_ratio, (TH2D*)(Zdir[i]->Get("_h_zy_pt")));
    Scaled2DRatio(_h_ycost_ratio, (TH2D*)(Zdir[i]->Get("_h_zy_cost")));
    Scaled2DRatio(_h_ycost_ratio2, (TH2D*)(Zdir[i]->Get("_h_zy_cost2")));
    Scaled2DRatio(_h_ym_ratio, (TH2D*)(Zdir[i]->Get("_h_zy_m")));
    Scaled2DRatio(_h_ptcost_ratio, (TH2D*)(Zdir[i]->Get("_h_zpt_cost")));
    Scaled2DRatio(_h_ptm_ratio, (TH2D*)(Zdir[i]->Get("_h_zpt_m")));
    Scaled2DRatio(_h_costm_ratio, (TH2D*)(Zdir[i]->Get("_h_zcost_m")));
    
    dir[i]->Write();

    
  }
 return dir;

}

std::vector<TDirectory *> RatioMaker::GetRatioHistos(const char * dirname){
  std::vector<TDirectory *> dir;  
  for (Int_t i =0; i < _nstep; i++){
    TString name(dirname);
    name+= "_";
    name+=  Form("%2.5g",_start + i*_step);
    dir.push_back((TDirectory*)(_outfile->Get(name)));
    // std::cout << "GetRatioHistos " << dir.at(i)->GetName() << std::endl;
  } 
  //   for (Int_t i =0; i < dirname.size(); i++){
  //     dir.push_back((TDirectory*)(_outfile->Get(dirname[i])));
  //     std::cout << dirname[i] << std::endl;
  //   }
  return dir;
}


void RatioMaker::ScaledRatio(TH1D *whist, TH1D*  zhist){
  
  for (Int_t testtt = 0; testtt < (zhist->GetNbinsX()+1.); testtt++){
    if (!(zhist->GetBinContent(testtt) > 0.)){
      // std::cout << " this is actually doing something" << std::endl;
      whist->SetBinContent(testtt,0.);
      zhist->SetBinContent(testtt,0.);
    }
  }
  Double_t zint = 0.;
  Double_t wint=0.;
  //  if (TString(whist->GetName())=="m_ratio"){
  //  std::cout << " Correctly identified histogram: " << whist->GetName() << std::endl;
  //  zint = zhist->Integral(7,395); //integral between 60 and 100 GeV
  //  wint = whist->Integral(7,395); // so less sensitive to tails.
  // }
  if (TString(whist->GetName())=="pt_ratio"){
    std::cout << " Correctly identified histogram: " << whist->GetName() << std::endl;
    zint = zhist->Integral(0,zhist->GetNbinsX()+1); //integral must include 0 bin for log Pt
    wint = whist->Integral(0,zhist->GetNbinsX()+1); // 
  }
  else {
    zint = zhist->Integral();
    wint = whist->Integral();
  }
//   for (Int_t bin=1; bin < zhist->GetNbinsX(); ++bin){
//     if (zhist->GetBinContent(bin) < 0.5 ){
//       zhist->SetBinContent(bin,0.);
//     } 
//   }
  zhist->Scale(wint/zint);
  whist->Divide(zhist);
  while (whist->GetMaximum() > 20.){
    whist->SetBinContent(whist->GetMaximumBin(),20.);
  }
}

void RatioMaker::Scaled2DRatio(TH2D *whist, TH2D*  zhist){
  
  //  zhist->Scale(whist->Integral()/zhist->Integral());
//   while (zhist->GetMinimum() < 0.){
//     zhist->SetBinContent(zhist->GetMinimumBin(),0.);
//   }
 std::cout << whist->Integral() << std::endl;
  for (Int_t testtt = 0; testtt < (zhist->GetBin(zhist->GetNbinsX()+1,zhist->GetNbinsY()+1)); testtt++){
    if (!(zhist->GetBinContent(testtt) > 0.)){
      // std::cout << " this is actually doing something" << std::endl;
      whist->SetBinContent(testtt,0.);
      zhist->SetBinContent(testtt,0.);
    }
  }
//   // std::cout << whist->Integral() << std::endl;
  zhist->Scale(whist->Integral() /  zhist->Integral());
  
  whist->Divide(zhist);
//   while (whist->GetBinContent(whist->GetMaximumBin()) > 10.){ //was 100
//     whist->SetBinContent(whist->GetMaximumBin(),10.);
//   }
//   while (whist->GetBinContent(whist->GetMinimumBin()) < -10.){ //was 0
//     whist->SetBinContent(whist->GetMinimumBin(),-10);
//   }
  //if (whist->GetMaximum() == 1000.){
  //  whist->SetMaximum(1010);
  // }
  
  //if (whist->GetMinimum()==0.){
  //  whist->SetMinimum(0.);
  // }
  
}


    
