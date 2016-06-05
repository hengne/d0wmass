#include "cafe/Config.hpp"
#include "wmass_util/CAFRatioMethod.hpp"
#include <TH1D.h>
#include <TH2D.h>
#include <TH1F.h>
#include <TF1.h>
#include <TDirectory.h>
#include <TString.h>
#include "wmass_util/EfficiencyCorrection.hpp"
#include "wmass_util/RatioMaker.hpp"
#include "wmass_analysis/histograms.hpp"
#include "wmass_util/CAFEMObj.hpp"
#include "wmass_util/CAFZCand.hpp"
#include "wmass_util/CAFTrack.hpp"
#include "wmass_util/CAFMet.hpp"
#include <TROOT.h>

using namespace std;
using namespace cafe;
using std::string;
CAFRatioMethod::CAFRatioMethod(const char *name){
  cout << "CAFRatioMethod: Started" << endl;
  Config config(name);
  cout << "CAFRatioMethod: Config(name) passed OK" << endl;
  
  _debugLevel = config.get("debugLevel", 0);
  
  _PtCut = config.get("electronPtCut",12.);
  _METCut =  config.get("METCut",25.);
  _etaCC = config.get("etaCC",1.05);
  _etaECLow = config.get("etaECLow",1.5);
  _etaECHigh = config.get("etaECHigh",2.3);
  _ZMassCutHigh = config.get("ZMassCutHigh",110.);
  _MtCutHigh = config.get("MtCutHigh",300.);
  _ZMassCutLow = config.get("ZMassCutLow",70.);
  _MtCutLow = config.get("MtCutLow",40.);
  _WMassCutLow = config.get("ZMassCutLow",60.);
  _WMassCutHigh = config.get("ZMassCutHigh",200.);
  _ELCorr= config.get("ELeakageCorr",0);
  _UParaCorr = config.get("UParaCorr", 0.);  
  _BosonPtCut = config.get("BosonPtCut", 0.);  
  _alpha = config.get("alpha",1.);
  _beta = config.get("beta",0.);
  _betaW = config.get("betaW",0.); 
  _sigma = config.get("sigma",0.); 
  _Delta_ZSUP_CC = config.get("Delta_ZSUP_CC", 0.);
  _Delta_ZSUP_EC = config.get("Delta_ZSUP_EC", 0.);  
  // real electron energy that is outside of the electron cone
  _EnergyLeakage_CC = config.get("ENERGY_OUTCONE_Elec_CC", 0.);
  _EnergyLeakage_EC = config.get("ENERGY_OUTCONE_Elec_EC", 0.);
  _Mw_smooth = config.get("Mw_smooth",80.419);
  _smooth_reweight = config.get("Smooth_reweight",0);
  _DoPositive = config.get("DoPositiveZ",1);
  _DoNegative = config.get("DoNegativeZ",1);
  _MixCharge = config.get("MixCharge",0);
  TString uparacorr_filename;
  uparacorr_filename = config.get("UPC_filename","");
  Double_t stepsize = config.get("stepsize",0.05);
  Double_t central = config.get("central_W_Mass",80.419);
  Int_t _npoints = config.get("nTemplates",40);
  for (Int_t i =0; i < 2*_npoints +1; i++){
    _Mw.push_back(central-((Double_t)_npoints)*stepsize + i*stepsize);
  }
  Bool_t reweight = config.get("reweight",0);
  std::vector<TDirectory*> emptyvector;
  emptyvector.clear();
 
  if (reweight){
    std::cout << "Reweighting " << std::endl;
    TString RMakerName1(config.get("YRatios","-"));
    TString RMakerName2(config.get("MRatios","-"));
    TString RMakerName3(config.get("PTRatios","-"));
    TString ratio2(config.get("RatiofileInput","-"));
    if (!(ratio2.EndsWith(".root"))){
      ratio2=ratio2+".root";
      std::cout << "Appending .root to ratio file name. Ratiofile2 = " << ratio2.Data() << std::endl;
    }
    
    Ratiofile2 = new TFile(ratio2,"READ");
    _RMaker = new RatioMaker(Ratiofile2,_Mw.at(0),stepsize,_Mw.size());
    if (RMakerName1.Length() > 3.){
       _reweightDir_y = _RMaker->GetRatioHistos(RMakerName1.Data());
    }
    else {
      _reweightDir_y = emptyvector;
    }
    if (RMakerName2.Length() > 3.){
      _reweightDir_m = _RMaker->GetRatioHistos(RMakerName2.Data());
    }
    else {
      _reweightDir_m = emptyvector;
    }
    if (RMakerName3.Length() > 3.){
      _reweightDir_pt = _RMaker->GetRatioHistos(RMakerName3.Data());
    }
    else {
      _reweightDir_pt = emptyvector;
    }
    Init();
  }
  else {
    _reweightDir_y = emptyvector;
    _reweightDir_m = emptyvector;
    _reweightDir_pt = emptyvector;
  }
  
  _fc5 = new TF1("fc5", "TMath::Voigt(x*x-[0]*[0],[1],[2])", 50, 150);
  _Mz = 91.188202;
  
  //std::cout << "*****" << _first << " " << _firstFile << std::endl;
  
  TFile *fupara = new TFile(uparacorr_filename);
  if(fupara->IsZombie()) {
    cout<<"   Please provide "<<uparacorr_filename<<endl;
    exit(-1);
  }
  fupara->cd("UE_Hist");
    for(int ilumi=0; ilumi<13; ilumi++) {
      for(int iupara=0; iupara<13; iupara++) {
	char name_hist[50]; 
	sprintf(name_hist, "%s%d%s%d", "sum13towEt_Lumi_", ilumi, "_Upara_", iupara);
	_hEt_ThirteenTowers[ilumi][iupara]= (TH1F *)gROOT->FindObject(name_hist)->Clone();
	_hEt_ThirteenTowers[ilumi][iupara]->SetDirectory(Ratiofile2);
        double x = _hEt_ThirteenTowers[ilumi][iupara]->GetRandom();
      }
    }
    fupara->Close();
    delete fupara;
    cout << "  Finished reading average 13 tower Et histograms" << endl;
    _effcor = new EfficiencyCorrection(name);
    cout << "  Finished Efficiency Correction Initialization " << endl;
    //_histos.clear();
    
    for (Int_t i =0 ;i<_Mw.size() ; i++){
      TString suffix("_");
      char csuf[10];
      sprintf(csuf, "%2.5g",_Mw.at(i));
      suffix+= csuf;
      suffix.ReplaceAll(" ","");
      _histos.push_back(new hist_files());
      _histos.at(i)->add(RatioMethod_Hist,suffix);
      _histos.at(i)->add(RatioMethod_2D,suffix);
    }
}

CAFRatioMethod::~CAFRatioMethod() {}


void CAFRatioMethod::Init()
{
  std::cout << "About to find the W mass to greater precision than ever before..." << std::endl;
  //  std::cout << "+++++" << _first << " " << _firstFile << std::endl;
  
      std::cout << "Loading Ratio histograms for reweighting" << std::endl;
      if (_reweightDir_pt.size() > 0){
	std::cout << "Reweighting in pT" << std::endl;
      }
      
      if (_reweightDir_m.size() > 0){
	std::cout << "Reweighting in width" << std::endl;
      }
      
      if (_reweightDir_y.size() > 0){
	  std::cout << "Reweighting in Rapidity and tstar" << std::endl;
      }
     

      for (Int_t i =0;i<_Mw.size();i++){
	if (_reweightDir_pt.size() > 0){
	  pt_ratio.push_back((TH1D*)(_reweightDir_pt.at(i)->Get("pt_ratio")));
	  char hname[20];
	  sprintf(hname, "ptfunc_%i",i);
	  _ptfunc.push_back( new TF1(hname,"pol3"));
	  _ptfunc[i]->SetParameters(1.04,-0.06);
	  pt_ratio[i]->Fit(_ptfunc[i],"N:Q","",0.,1.3);
	  
	}
	if (_reweightDir_m.size() > 0){
	  m_ratio.push_back((TH1D*)((_reweightDir_m.at(i)->Get("m_ratio"))));
	}
	if (_reweightDir_y.size() > 0){
	  y_ratio2.push_back((TH2D*)(_reweightDir_y.at(i)->Get("ycost_ratio2")));
	  y_ratio.push_back((TH2D*)(_reweightDir_y.at(i)->Get("ycost_ratio")));
	}
	
      }
}




int CAFRatioMethod::MakeW(const CAFEMObj *elec1, const CAFEMObj *elec2, const TMBTrack*trk1, const TMBTrack *trk2, Double_t instlumi,TVector2 &recoil_vect, CAFMet &met, int Trigger_flag)
{
  Double_t qpt1 = trk1->charge();
  if ((!_DoPositive) && (qpt1 >0)){
    for (Int_t counter =0; counter < _Mw.size(); counter++){
    }
    return 0;
  }
  if ((!_DoNegative) && (qpt1 <0)){
    for (Int_t counter =0; counter < _Mw.size(); counter++){
    }
    return 0;
  }
  
  Double_t px1 = elec1->Px();
  Double_t py1 = elec1->Py();
  Double_t pz1 = elec1->Pz();
  Double_t E1 = elec1->E();
  Double_t deteta1 = elec1->CalDetectorEta();
  Double_t theta1 = trk1->Theta();
  Double_t physeta1 = trk1->Eta();
  
  Double_t px2 = elec2->Px();
  Double_t py2 = elec2->Py();
  Double_t pz2 = elec2->Pz();
  Double_t E2 = elec2->E();
  Double_t deteta2 = elec2->CalDetectorEta();
  Double_t theta2 = elec2->Theta();
  Double_t physeta2 = elec2->Eta();
  if (trk2){
    theta2 = trk2->Theta();
    physeta2 = trk2->Eta();
  }
  else{
    
  }
  Double_t Delta_ZS2 = 0.;
  Double_t Delta_EL2 =0.;
  TVector2 em_vect1(px1, py1);
  TVector2 em_vect2(px2, py2);
  Double_t upara2 = recoil_vect * em_vect2.Unit();
  Double_t upara1 = recoil_vect * em_vect1.Unit();
 
  Double_t metx = met.metx();
  Double_t mety = met.mety();
  if (_UParaCorr){
    if (TMath::Abs(deteta2) < 1.1){

 // read uparallel correction from 169 histograms with 13 luminosity bins and 13 uparallel bins
      // divided into instantaneous luminosity bins
      int InstLumiBin = -1;
      if(instlumi<0.225) InstLumiBin = 0;
      else if(instlumi<0.45) InstLumiBin = 1;
      else if(instlumi<0.6) InstLumiBin = 2;
      else if(instlumi<0.75) InstLumiBin = 3;
      else if(instlumi<0.9) InstLumiBin = 4;
      else if(instlumi<1.075) InstLumiBin = 5;
      else if(instlumi<1.3) InstLumiBin = 6;
      else if(instlumi<1.5) InstLumiBin = 7;
      else if(instlumi<1.8) InstLumiBin = 8;
      else if(instlumi<2.) InstLumiBin = 9;
      else if(instlumi<2.5) InstLumiBin = 10;
      else if(instlumi<3.) InstLumiBin = 11;
      else InstLumiBin = 12;
      
      // divided into uparallel bins
      int UParaBin = -1;
      if(upara2<-15.) UParaBin = 0;
      else if(upara2<-10.) UParaBin = 1;
      else if(upara2<-5.) UParaBin = 2;
      else if(upara2<-3.) UParaBin = 3;
      else if(upara2<-1.5) UParaBin = 4;
      else if(upara2<-0.25) UParaBin = 5;
      else if(upara2<0.25) UParaBin = 6;
      else if(upara2<1.5) UParaBin = 7;
      else if(upara2<3.) UParaBin = 8;
      else if(upara2<5.) UParaBin = 9;
      else if(upara2<10.) UParaBin = 10;
      else if(upara2<15.) UParaBin = 11;
      else UParaBin = 12;

      // histograms with InstLumiBin>=10 and UParaBin>=10 are empty
      if(InstLumiBin>=10 && UParaBin>=10) {
	InstLumiBin=9;   
	UParaBin=9;   
      }
     Double_t  UParaCorr = _hEt_ThirteenTowers[InstLumiBin][UParaBin]->GetMean();
     Double_t UParaCorrE = UParaCorr / sin(theta2);
    
    Delta_ZS2 =UParaCorr;
    } 
    else{
      Delta_ZS2 = 0.;
    }
  }
  if (_ELCorr){
    if (TMath::Abs(deteta2) < 1.1){
      Delta_EL2 = _EnergyLeakage_CC/cosh(physeta2) ;  
    }
    else{
      Delta_EL2 = (_EnergyLeakage_EC)/cosh(physeta2) ;  
    }
  }
  TVector3 Correc3Vec2(px2,py2,0.);
  Correc3Vec2.SetMag(Delta_ZS2 - Delta_EL2);
 
  TLorentzVector CorrecVec2(Correc3Vec2,Correc3Vec2.Mag());
  
  TLorentzVector e1(px1,py1,pz1,E1);
  TLorentzVector e2(px2,py2,pz2,E2);
  
  
  TLorentzVector zp = e1+e2;
  if ((TMath::Abs(deteta1) < _etaCC) && ((TMath::Abs(deteta2) < _etaCC) || ((TMath::Abs(deteta2) > _etaECLow) && (TMath::Abs(deteta2) < _etaECHigh)))){
    e1.Boost(-(zp.BoostVector()));
    e2.Boost(-(zp.BoostVector()));
    Double_t  z_pT = zp.Pt();
    TVector3 pp1 = e1.Vect();
    TVector3 pp2 = e2.Vect();
    Double_t weight = 1;

    Double_t wcosthetastar = -666;
    
    
    TLorentzVector zaxis1(0,0,980.,980.);
    TLorentzVector zaxis2(0,0,-980.,980.);
    zaxis1.Boost(-(zp.BoostVector()));
    zaxis2.Boost(-(zp.BoostVector()));
    TVector3 zaxis = (zaxis1.Vect().Unit()) - (zaxis2.Vect().Unit());
   
    
    wcosthetastar = ((-pp1.Dot(zaxis))/(pp1.Mag()*zaxis.Mag()));
    
    for (Int_t i =0; i< _Mw.size(); i++){
      Double_t Wm=0;
      weight = 1.;
      if (_smooth_reweight)	{ //  ! (_reweightDir_m.size() > 0 )
	_fc5->SetParameters(_alpha*_Mz+_beta,509.,2.*_alpha*_Mz*_alpha*2.49); // _Mz^2 with Gamma = 2.4952. and sigma = 503 assume sigma scales proportional to (M)
	Double_t fake1 = _fc5->Eval(zp.M());
	Double_t fakemz =  (_Mw[i] / _Mw_smooth * _Mz);
	_fc5->SetParameters(_alpha*fakemz+_beta,509 ,2.*_alpha*fakemz*_alpha*2.49 );
	Double_t fake2 = _fc5->Eval(zp.M());
	
	weight = weight * fake2/fake1; 
	Wm = (zp.M()-_beta)/_Mz* _Mw_smooth + _betaW;
      }
      
      if (!_smooth_reweight){
	Wm = (zp.M()-_beta)/_Mz *_Mw[i] + _betaW ;
      }
      TLorentzVector zp2(0.,0.,0.,Wm);
      pp1.SetMag(Wm/2.); // TMath::Sqrt(((Wm+_Em*_Em/Wm)*(Wm+_Em*_Em/Wm)/4.)-_Em*_Em));
      pp2.SetMag(Wm/2.); //TMath::Sqrt(((Wm+_Em*_Em/Wm)*(Wm+_Em*_Em/Wm)/4.)-_Em*_Em));
      TLorentzVector e1p(pp1,Wm/2.);
      TLorentzVector e2p(pp2,Wm/2.);
      TVector3 bb = zp.Vect();
      bb.SetMag(bb.Mag()/(TMath::Sqrt(zp2.M2()+bb.Mag2())));
      e1p.Boost(bb);
      e2p.Boost(bb);
      zp2.Boost(bb);
      Double_t nu_ex = (e2p.Vect().X()); 
      Double_t nu_ey = (e2p.Vect().Y());
      Double_t nu_ez = (e2p.Vect().Z());
      TLorentzVector nu1(nu_ex,nu_ey,nu_ez,TMath::Sqrt(nu_ey*nu_ey+nu_ex*nu_ex + nu_ez*nu_ez));
      TLorentzVector newW = e1p+nu1;
      nu_ex += metx;
      nu_ey += mety;
      TLorentzVector nu(nu_ex,nu_ey,nu_ez,TMath::Sqrt(nu_ey*nu_ey+nu_ex*nu_ex + nu_ez*nu_ez));
      //  std::cout << nu.Pt() << std::endl;
      if (_UParaCorr || _ELCorr){
      	nu-= CorrecVec2;
      }
      Double_t e1_x = e1p.Vect().X();
      Double_t e1_y = e1p.Vect().Y();
      Double_t cosphi = (nu.Vect().X()*e1_x+nu.Vect().Y()*e1_y)/((nu.Pt())*(e1p.Pt()));
      
      Double_t ept = e1p.Pt();
      Double_t nupt = nu.Pt();
      Double_t w_pT = newW.Pt();
      Double_t m = TMath::Sqrt(ept*nupt*2*(1-cosphi));
      Double_t zy = zp.Rapidity();
      Double_t heidi = (1/TMath::Pi())*TMath::ATan(2*(Wm*Wm-_Mw[i]*_Mw[i])/(3.8 * _Mw[i]))+0.5;
	if (_reweightDir_y.size() > 0){
	  if (qpt1 > 0.){
	    weight = weight*(y_ratio[i]->GetBinContent((y_ratio[i]->FindBin(zy,wcosthetastar))));
	  }
	  else if (qpt1 < 0.){
	    weight = weight* (y_ratio2[i]->GetBinContent((y_ratio2[i]->FindBin(zy,wcosthetastar))));
	  }
	  else {
	    std::cout << " error" << std::endl;
	  }
	}
	if (_reweightDir_m.size() > 0 ){
	  weight= weight* (m_ratio[i]->GetBinContent((m_ratio[i]->FindBin(heidi))));
	}
	if (_reweightDir_pt.size() > 0){ 
	  weight = weight* _ptfunc[i]->Eval(w_pT); // (pt_ratio[i]->GetBinContent((pt_ratio[i]->FindBin(TMath::Log10(w_pT))))); 
	}

  
	if ((Wm>_WMassCutLow) && (Wm < _WMassCutHigh) && (w_pT < _BosonPtCut)){ 
	  if ((ept >_PtCut) && (nupt > _METCut)) { 
	    if (_debugLevel > 15)
	      std::cout << "I'm guessing It's an efficiency thing" << std::endl;
	    weight = weight * _effcor->FullEfficiencyCorrection(Trigger_flag, elec1->Pt(),elec2->Pt(), ept,deteta1, deteta2, physeta1, physeta2, elec2->Phi(),upara1, upara2 );
	    if (_debugLevel > 15)
	      std::cout << "Efficiency Done" << std::endl;
	  }
	 
	  TString suffix("_");
	  char csuf[10];
	  sprintf(csuf, "%2.5g",_Mw.at(i));
	  suffix+=csuf;
	  suffix.ReplaceAll(" ","");
	  _histos.at(i)->Fill1D("WCandInstLumi"+suffix,instlumi,weight);
	  _histos.at(i)->Fill1D("WCandElecPt"+suffix,ept,weight);
	  _histos.at(i)->Fill1D("WCandMet"+suffix,nupt,weight);
	  _histos.at(i)->Fill1D("WCandMt"+suffix,m,weight);
	  _histos.at(i)->Fill1D("WCandPt"+suffix,w_pT,weight);
	  _histos.at(i)->Fill1D("WCandElecEta"+suffix,physeta1,weight);
	  _histos.at(i)->Fill1D("WCandElecDetEta"+suffix,deteta1,weight);
	  _histos.at(i)->Fill1D("WCandnuEta"+suffix,physeta2,weight);
	  _histos.at(i)->Fill1D("WCandnuDetEta"+suffix,deteta2,weight);
	  _histos.at(i)->Fill1D("WCandEta"+suffix,zy,weight);
	  if (qpt1 < 0.){
	    _histos.at(i)->Fill1D("ElecThetaStar"+suffix,wcosthetastar,weight);
	    _histos.at(i)->Fill2D("BosonRapidity_V_costhetastar2"+suffix,zy,wcosthetastar,weight);
	  }
	  if (qpt1 > 0) {
	    _histos.at(i)->Fill2D("BosonRapidity_V_costhetastar1"+suffix,zy,wcosthetastar,weight);
	    _histos.at(i)->Fill1D("PosiThetaStar"+suffix,wcosthetastar,weight);
	  }
	  _histos.at(i)->Fill1D("ThetaStar"+suffix,wcosthetastar,weight);
	  _histos.at(i)->Fill1D("WCandMass"+suffix,zp.M(),weight);
	}
	   }
  }
  if (_debugLevel > 15)
    std::cout << "W Made " << std::endl;
  return 0;
}

void CAFRatioMethod::Analyze(CAFZCand &ZCand, CAFMet &met, int Triglist, Double_t instlumi ,TVector2 recoil_vect, Int_t Selector){
  const CAFEMObj *e1 = ZCand.EM(0);
  const CAFEMObj *e2 = ZCand.EM(1);
  const TMBTrack *trk1 = (ZCand.EM(0)->getPtrSpatialChp());
  const TMBTrack *trk2 = (ZCand.EM(1)->getPtrSpatialChp());
  if (Selector ==0){
    return;
  }
  if (!(Selector ==2)){    
    MakeW(e1, e2, trk1,trk2, instlumi,recoil_vect,met, Triglist);
  }
  if (Selector > 1){
    MakeW(e2, e1, trk2,trk1, instlumi,recoil_vect,met, Triglist);
  } 
  
}
void CAFRatioMethod::terminate(TFile* root_file, string directory_name, bool debug){
  std::cout<< "Calling CAFRatioMethod Terminate" << std::endl;
  if(root_file==NULL) return;
  char mass_n[10];
  for (Int_t i =0;i<_Mw.size();i++){
    string dname = directory_name;
    sprintf(mass_n,"_%2.5g", _Mw.at(i));
    dname+=mass_n;
    root_file->mkdir(dname.c_str()); 
    _histos.at(i)->save(root_file, dname);
  }
}
