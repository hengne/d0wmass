#include "ZAnalysis.hpp"
#include "PMCSZCand.hpp"
#include "histograms.hpp"
#include "WZ_Utils.hpp"
#include "SETefficiencySmear.hpp"
#include "SETefficiencySmear_LumiDispatch.hpp"

#include <TROOT.h>
#include <TFile.h>
#include <TObject.h>
#include <TMinuit.h>
#include <TRandom3.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sstream>

using namespace std;

bool ComparePt(const PMCSParticle part1, const PMCSParticle part2);
bool CompareE(const PMCSParticle part1, const PMCSParticle part2);

#define _USE_SINGLE_GAUSSIAN_ETAIMBAL_ true // false
#if ( _USE_SINGLE_GAUSSIAN_ETAIMBAL_ )
Double_t fcn_eta(Double_t *x, Double_t *par) {
  return par[0]*TMath::Gaus(x[0],par[1],par[2],kTRUE);
}
#else
Double_t fcn_eta(Double_t *x, Double_t *par) {
  return par[0]*(par[4]*TMath::Gaus(x[0],par[1],par[2],kTRUE)
		 +(1-par[4])*TMath::Gaus(x[0],par[1],par[2]+par[3],kTRUE));
}
#endif
Double_t fcn_phi(Double_t *x, Double_t *par) {
  return par[0]*TMath::Gaus(x[0],TMath::Pi(),par[1],kTRUE)+par[2];
}
Double_t fcn_signedphi(Double_t *x, Double_t *par) {
  return par[0]*TMath::Gaus(x[0],0,par[1],kTRUE)+par[2];
}
Double_t fcn_xi(Double_t *x, Double_t *par) {
  if(fabs(x[0]-par[1])<fabs(par[2])) return par[0]/sqrt(TMath::TwoPi())/par[3];
  else if(x[0]>par[1]+fabs(par[2])) return par[0]*TMath::Gaus(x[0], par[1]+fabs(par[2]), par[3], kTRUE);
  else return par[0]*TMath::Gaus(x[0], par[1]-fabs(par[2]), par[3], kTRUE);     
}

// Double_t fcn_phi(Double_t *x, Double_t *par) {
//   return par[0]*(par[3]*TMath::Gaus(x[0],TMath::Pi(),par[1],kTRUE)
// 		 +(1-par[3])*TMath::Gaus(x[0],TMath::Pi(),par[2]+par[1],kTRUE))
//          +par[4];
// }
// Double_t fcn_signedphi(Double_t *x, Double_t *par) {
//   return par[0]*(par[3]*TMath::Gaus(x[0],0,par[1],kTRUE)
// 		 +(1-par[3])*TMath::Gaus(x[0],0,par[2]+par[1],kTRUE))
//          +par[4];
// }
// Double_t fcn_xi(Double_t *x, Double_t *par) {
//   if(fabs(x[0]-par[1])<fabs(par[2])) return par[0]/sqrt(TMath::TwoPi())/par[3];
//   else if(x[0]>par[1]+fabs(par[2])) return par[0]*TMath::Gaus(x[0], par[1]+fabs(par[2]), par[3], kTRUE);
//   else return par[0]*TMath::Gaus(x[0], par[1]-fabs(par[2]), par[3], kTRUE);     
// }

void ZAnalysis::MakeU_parControlPlot(std::vector<PMCSEMObj>& emobjs_smear,
                                     PMCSRecoil& recoil_smear,
                                     PMCSMet& met_smear,
                                     PMCSVtx& vtx_gen,
                                     double evtweight,
                                     TRandom3 *dummy) {
  // Event simulation
  bool neverUseTrack=false;
  bool withCutTrkPt=false;
  //bool withCutTrkPt=true;

  bool tagAndProbe=_StudyEfficiencies;

  bool CCtag=true;
  bool CCECtag=false;
  bool ECtag=false;

  bool RequestBothPtCut = _makeU_parControlPlot_RequestBothPtCut;

  bool CutFid1 = !(emobjs_smear[0].IsLostInAcrack());
  bool CutFid2 = !(emobjs_smear[1].IsLostInAcrack());

  bool CutEMpt1=((emobjs_smear[0].ppt()>_CutEPT1_lo)&&(emobjs_smear[0].ppt()<_CutEPT1_hi));
  bool CutEMpt2=((emobjs_smear[1].ppt()>_CutEPT2_lo)&&(emobjs_smear[1].ppt()<_CutEPT2_hi));
  bool CutTrkpt1=(emobjs_smear[0].trkpT()>_trkpTCut);
  bool CutTrkpt2=(emobjs_smear[1].trkpT()>_trkpTCut);
  PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);
  double mass = zcand.mass();
  int Type=zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);
  bool CutZmass=(mass>_ZMassCut1 && mass<_ZMassCut2);
  double Trigger_Version = dummy->Uniform(0., 1.);

 
  
  bool passesTrigEff1=true, passesTrigEff2=true;
  if(_ZtrigEffCorrection) {
    passesTrigEff1 = _efficiencysmear->passesTriggerEff(emobjs_smear[0], dummy, Trigger_Version, _ZBrunNum);
    passesTrigEff2 = _efficiencysmear->passesTriggerEff(emobjs_smear[1], dummy, Trigger_Version, _ZBrunNum);
  }
  bool passesPreselEff1=true, passesPreselEff2=true;
  if(_ZpreselEffCorrection) {
    passesPreselEff1 = _efficiencysmear->passesPreselEff(emobjs_smear[0], dummy, 0, &vtx_gen, 0, neverUseTrack);
    passesPreselEff2 = _efficiencysmear->passesPreselEff(emobjs_smear[1], dummy, 0, &vtx_gen, 0, neverUseTrack);
  }

  bool passesEMIDEff1=true, passesEMIDEff2=true;
  if(_ZIDEffCorrection) {
    passesEMIDEff1 = _efficiencysmear->passesEMIDEff(emobjs_smear[0], dummy);
    passesEMIDEff2 = _efficiencysmear->passesEMIDEff(emobjs_smear[1], dummy);
  }
  bool passesTrkEff1=true, passesTrkEff2=true, passesloosetrack1=true, passesloosetrack2=true;
  passesTrkEff1 = _efficiencysmear->passesTrkEff(emobjs_smear[0], vtx_gen, dummy);
  passesTrkEff2 = _efficiencysmear->passesTrkEff(emobjs_smear[1], vtx_gen, dummy);

  if(_ZElecPhiEffCorrection) {
      bool passesElecPhiEff1=true, passesElecPhiEff2=true;
      passesElecPhiEff1 = _efficiencysmear->passesElecPhiEff(emobjs_smear[0], dummy, _ZElecPhiEffCorrectionUseDetPhi);
      passesElecPhiEff2 = _efficiencysmear->passesElecPhiEff(emobjs_smear[1], dummy, _ZElecPhiEffCorrectionUseDetPhi);
      passesTrkEff1 = passesTrkEff1 && passesElecPhiEff1; 
      passesTrkEff2 = passesTrkEff2 && passesElecPhiEff2; 
  }

  if (neverUseTrack) {
    passesloosetrack1  =  _efficiencysmear->passesLooseTrkEff(emobjs_smear[0], &vtx_gen, dummy);
    passesloosetrack2  =  _efficiencysmear->passesLooseTrkEff(emobjs_smear[1], &vtx_gen, dummy);
    passesTrkEff1 = passesTrkEff1 && passesloosetrack1;
    passesTrkEff2 = passesTrkEff2 && passesloosetrack2;
  }

  

  //
  double Ut=recoil_smear.Recoil();
  bool CutUT=(Ut<_CutZUT && Ut>=_CutZUT_lower);
  bool passesUParaCorrection1=true;
  bool passesUParaCorrection2=true;
  if(_ZUparaEffCorrection) {
    double upara1, upara2;
    if ( _UseUparaOverPte) {
      upara1 = zcand.UPara1()/zcand.GetElec1().ppt();
      upara2 = zcand.UPara2()/zcand.GetElec2().ppt();
    }
    else if ( _UseCosUphi ) {
      upara1 = zcand.UPara1()/sqrt(zcand.UPara1()*zcand.UPara1() + zcand.UPerp1()*zcand.UPerp1());
      upara2 = zcand.UPara2()/sqrt(zcand.UPara2()*zcand.UPara2() + zcand.UPerp2()*zcand.UPerp2());
    }
    else {
      upara1 = zcand.UPara1();
      upara2 = zcand.UPara2();
    };
   
    // randomize the order of the two electrons
    if (dummy->Rndm()>0.5) {
      passesUParaCorrection1 = passesUParaEff(emobjs_smear[0], upara1, dummy, 2);
      passesUParaCorrection2 = passesUParaEff(emobjs_smear[1], upara2, dummy, int(passesUParaCorrection1));
    }
    else {
      passesUParaCorrection2 = passesUParaEff(emobjs_smear[1], upara2, dummy, 2);
      passesUParaCorrection1 = passesUParaEff(emobjs_smear[0], upara1, dummy, int(passesUParaCorrection2));
    } 

  }

  // AddOn Efficiency
  bool passesAddOnEff1 = true;
  bool passesAddOnEff2 = true;
  if (_ApplyAddOnEff_Zee){
    // randomize the order of the two electrons
    /*
    if (dummy->Rndm()>0.5) {
      //passesAddOnEff1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, 2);
      //passesAddOnEff2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(passesAddOnEff1));
      //passesAddOnEff1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(passesAddOnEff2));
      bool pass1, pass2, pdf1, pdf2;
      pass1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, 2);
      pdf2 = pass1;
      pass2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(pdf2));
      pdf1 = pass2;
      pass1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(pdf1));
      if (pdf2!=pass1) {
        pdf2 = pass1;
        pass2 =  _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(pdf2));
        if (pdf1!=pass2){
          pdf1 = pass2;
          pass1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(pdf1));
          if (pdf2!=pass1){
            pdf2 = pass1;
            pass2 =  _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(pdf2));
            if (pdf1!=pass2){
              pdf1 = pass2;
              pass1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(pdf1));
              if (pdf2!=pass1){
                pdf2 = pass1;
                pass2 =  _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(pdf2));
                if (pdf1!=pass2){
                  pdf1 = pass2;
                  pass1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(pdf1));
                  if (pdf2!=pass1){
                    pdf2 = pass1;
                    pass2 =  _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(pdf2));
                    if (pdf1!=pass2){
                      pdf1 = pass2;
                      pass1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(pdf1));
                    }
                  }
                }
              }
            }    
          }
        }
      }
      passesAddOnEff1 = pass1;
      passesAddOnEff2 = pass2;
    }
    else {
      //passesAddOnEff2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, 2);
      //passesAddOnEff1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(passesAddOnEff2));
      //passesAddOnEff2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(passesAddOnEff1));
      bool pass1, pass2, pdf1, pdf2;
      pass2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, 2);
      pdf1 = pass2;
      pass1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(pdf1));
      pdf2 = pass1;
      pass2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(pdf2));
      if (pdf1!=pass2) {
        pdf1 = pass2;
        pass1 =  _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(pdf1));
        if (pdf2!=pass1){
          pdf2 = pass1;
          pass2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(pdf2));
          if (pdf1!=pass2){
            pdf1 = pass2;
            pass1 =  _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(pdf1));
            if (pdf2!=pass1){
              pdf2 = pass1;
              pass2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(pdf2));
              if (pdf1!=pass2){
                pdf1 = pass2;
                pass1 =  _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(pdf1));
                if (pdf2!=pass1){
                  pdf2 = pass1;
                  pass2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(pdf2));
                  if (pdf1!=pass2){
                    pdf1 = pass2;
                    pass1 =  _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, int(pdf1));
                    if (pdf2!=pass1){
                      pdf2 = pass1;
                      pass2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, int(pdf2));
                    }
                  }
                }
              }
            }
          }
        }
      }
      passesAddOnEff1 = pass1;
      passesAddOnEff2 = pass2;      
    }
    */
    // Oct7v3
    passesAddOnEff1 = _efficiencysmear->passesAddOnEff(emobjs_smear[0], false, dummy, 2);
    passesAddOnEff2 = _efficiencysmear->passesAddOnEff(emobjs_smear[1], false, dummy, 2);
  }

  // Event analysis
  bool passBaseCut = (CutZmass&&CutUT);
  //if (RequestBothPtCut) passBaseCut = (CutFid1&&CutFid2&&CutEMpt1&&CutEMpt2&&CutZmass&&passesPreselEff1&&passesPreselEff2&&CutUT);
  if (RequestBothPtCut) passBaseCut = (CutFid1&&CutFid2&&CutEMpt1&&CutEMpt2&&CutZmass&&CutUT);

  double scalarEt_All = _recoilsmear->scalarEt();
  double Lumi = emobjs_smear[0].getLumi();

  if (passBaseCut) {

    /// MOVED HERE for protection
    bool passSETeff=true;
    bool passSETeff1=true;
    bool passSETeff2=true;
    if (_ZSETEffCorrection) {
      if (_ZSETEffCorrPTEpert) {
        passSETeff=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),
                                                     dummy, NULL, emobjs_smear[0].ppt(), emobjs_smear[1].ppt(), 
						     emobjs_smear[0].IsEC(_CutEtaEC1,_CutEtaEC2), emobjs_smear[1].IsEC(_CutEtaEC1,_CutEtaEC2),
						     emobjs_smear[0].deteta(), emobjs_smear[1].deteta(), zcand.UPara1(), zcand.UPara2());
        passSETeff1=_SETefficiencysmear->passesFirst();
        passSETeff2=_SETefficiencysmear->passesSecond();
        //assert((passSETeff&&passSETeff1&&passSETeff2)||((!passSETeff)&&(!(passSETeff1&&passSETeff2))));
      } else {
        passSETeff=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),
                                                     dummy, NULL);
        passSETeff1=passSETeff;    //
        passSETeff2=passSETeff;    // reproduce previous approximation
      }
    }
    ///
    if (! withCutTrkPt) {
      CutTrkpt1=true;
      CutTrkpt2=true;
    }
    //type 0 : CCCC; 1 CCEC; 2 : ECEC;
    int type = zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);

    bool EC1=false, EC2=false;
    bool CC1=emobjs_smear[0].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);
    bool CC2=emobjs_smear[1].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);

    if ( ! CC1) EC1=true;
    if ( ! CC2) EC2-true;

    bool Elec1=false, Elec2=false;
    if (CCtag) {
      Elec1 = (CC1&&CutFid1&&CutEMpt1);
      Elec2 = (CC2&&CutFid2&&CutEMpt2);
    }
    if (ECtag) {
      Elec1=EC1;
      Elec2=EC2;
    }
    if (CCECtag) {
      if (CC1) Elec1=CC1;
      if (CC2) Elec2=CC2;
      if (EC1) Elec1=EC1;
      if (EC2) Elec2=EC2;
    }


    bool tag1= ! tagAndProbe || (Elec1 && passesEMIDEff1&&passesTrkEff1&&CutTrkpt1 && passesUParaCorrection1 && passSETeff1 && passesAddOnEff1 && CutEMpt1 && CutFid1 && passesPreselEff1);
    bool tag2= ! tagAndProbe || (Elec2 && passesEMIDEff2&&passesTrkEff2&&CutTrkpt2 && passesUParaCorrection2 && passSETeff2 && passesAddOnEff2 && CutEMpt2 && CutFid2 && passesPreselEff2);

    double UPara1, UPara2;
    double UPerp1, UPerp2;
    double ElecPt1, ElecPt2;
    double TrueElecPt1, TrueElecPt2;
    double Ptee;

    ElecPt1 = zcand.GetElec1().ppt();
    ElecPt2 = zcand.GetElec2().ppt();
    TrueElecPt1 = zcand.GetElec1().GetEnergyGenWFSR()/cosh(zcand.GetElec1().peta());
    TrueElecPt2 = zcand.GetElec2().GetEnergyGenWFSR()/cosh(zcand.GetElec2().peta());
    Ptee = zcand.ppt(); 

    if (Elec1 && tag2) {
      if (_PlotUparaOverPte) {
	UPara1=zcand.UPara1()/zcand.GetElec1().ppt();
      }
      else if (_PlotCosUphi) {
	UPara1 = zcand.UPara1()/sqrt(zcand.UPara1()*zcand.UPara1() +zcand.UPerp1()*zcand.UPerp1());
      }
      else
        UPara1=zcand.UPara1();
        UPerp1=zcand.UPerp1();

      //cout<<"JAN 1 "<<emobjs_smear[0].ppid()<<" "<<emobjs_smear[0].ppt()<<" "<<emobjs_smear[0].peta()<<" "<<emobjs_smear[0].deteta()<<" "<<vtx_gen.vtxz()<<" "<<zcand.UPara1()<<"  "<<passesEMIDEff1<<" "<<passesTrkEff1<<endl;
      _histos.Fill1D("smeared_hZcandUpara_noEff_CC", UPara1, evtweight);
      _histos.Fill2D("smeared_hZcandUparaUperp_noEff_CC", UPara1, UPerp1, evtweight);
      _histos.Fill1D("smeared_hZcandElecPt_noEff_CC", ElecPt1, evtweight);
      _histos.Fill1D("smeared_hZcandTrueElecPt_noEff_CC", TrueElecPt1, evtweight);
      _histos.Fill1D("smeared_hZcandPtee_noEff_CC", Ptee, evtweight);
      _histos.Fill1D("smeared_hZcandSET_noEff_CC", scalarEt_All, evtweight);
      _histos.Fill1D("smeared_hZcandLumi_noEff_CC", Lumi, evtweight);
      _histos.Fill2D("smeared_hZcandSETLumi_noEff_CC", scalarEt_All, Lumi, evtweight);
      if (passesEMIDEff1&&passesTrkEff1&&CutTrkpt1&&passesPreselEff1) {
        _histos.Fill1D("smeared_hZcandUpara_emEff_CC", UPara1, evtweight);
        _histos.Fill2D("smeared_hZcandUparaUperp_emEff_CC", UPara1, UPerp1, evtweight);
        if (passesUParaCorrection1) {
          _histos.Fill1D("smeared_hZcandUpara_emuparaEff_CC", UPara1, evtweight);
          _histos.Fill2D("smeared_hZcandUparaUperp_emuparaEff_CC", UPara1, UPerp1, evtweight);
          if (passSETeff1&&passesAddOnEff1) {
            _histos.Fill1D("smeared_hZcandUpara_emuparasetEff_CC", UPara1, evtweight);
            _histos.Fill2D("smeared_hZcandUparaUperp_emuparasetEff_CC", UPara1, UPerp1, evtweight);
            _histos.Fill1D("smeared_hZcandElecPt_emuparasetEff_CC", ElecPt1, evtweight);
            _histos.Fill1D("smeared_hZcandTrueElecPt_emuparasetEff_CC", TrueElecPt1, evtweight);
            _histos.Fill1D("smeared_hZcandPtee_emuparasetEff_CC", Ptee, evtweight);
            _histos.Fill1D("smeared_hZcandSET_emuparasetEff_CC", scalarEt_All, evtweight);
            _histos.Fill1D("smeared_hZcandLumi_emuparasetEff_CC", Lumi, evtweight);
            _histos.Fill2D("smeared_hZcandSETLumi_emuparasetEff_CC", scalarEt_All, Lumi, evtweight);
          }
        }
      }
    }

    if (Elec2 && tag1) {
      if (_PlotUparaOverPte) {
        UPara1=zcand.UPara2()/zcand.GetElec2().ppt();
      }
      else if (_PlotCosUphi) {
        UPara2 = zcand.UPara2()/sqrt(zcand.UPara2()*zcand.UPara2() +zcand.UPerp2()*zcand.UPerp2());
      }
      else
        UPara2=zcand.UPara2();
        UPerp2=zcand.UPerp2();

      //cout<<"JAN 2 "<<emobjs_smear[1].ppid()<<" "<<emobjs_smear[1].ppt()<<" "<<emobjs_smear[1].peta()<<" "<<emobjs_smear[1].deteta()<<" "<<vtx_gen.vtxz()<<" "<<zcand.UPara2()<<"  "<<passesEMIDEff2<<" "<<passesTrkEff2<<endl;
      _histos.Fill1D("smeared_hZcandUpara_noEff_CC", UPara2, evtweight);
      _histos.Fill2D("smeared_hZcandUparaUperp_noEff_CC", UPara2, UPerp2, evtweight);
      _histos.Fill1D("smeared_hZcandElecPt_noEff_CC", ElecPt2, evtweight);
      _histos.Fill1D("smeared_hZcandTrueElecPt_noEff_CC", TrueElecPt2, evtweight);
      _histos.Fill1D("smeared_hZcandPtee_noEff_CC", Ptee, evtweight);
      _histos.Fill1D("smeared_hZcandSET_noEff_CC", scalarEt_All, evtweight);
      _histos.Fill1D("smeared_hZcandLumi_noEff_CC", Lumi, evtweight);
      _histos.Fill2D("smeared_hZcandSETLumi_noEff_CC", scalarEt_All, Lumi, evtweight);
      if (passesEMIDEff2&&passesTrkEff2&&CutTrkpt2&&passesPreselEff2) {
        _histos.Fill1D("smeared_hZcandUpara_emEff_CC", UPara2, evtweight);
        _histos.Fill2D("smeared_hZcandUparaUperp_emEff_CC", UPara2, UPerp2, evtweight);
        if (passesUParaCorrection2) {
          _histos.Fill1D("smeared_hZcandUpara_emuparaEff_CC", UPara2, evtweight);
          _histos.Fill2D("smeared_hZcandUparaUperp_emuparaEff_CC", UPara2, UPerp2, evtweight);
          if (passSETeff2&&passesAddOnEff2) {
            _histos.Fill1D("smeared_hZcandUpara_emuparasetEff_CC", UPara2, evtweight);
            _histos.Fill2D("smeared_hZcandUparaUperp_emuparasetEff_CC", UPara2, UPerp2, evtweight);
            _histos.Fill1D("smeared_hZcandElecPt_emuparasetEff_CC", ElecPt2, evtweight);
            _histos.Fill1D("smeared_hZcandTrueElecPt_emuparasetEff_CC", TrueElecPt2, evtweight);
            _histos.Fill1D("smeared_hZcandPtee_emuparasetEff_CC", Ptee, evtweight);
            _histos.Fill1D("smeared_hZcandSET_emuparasetEff_CC", scalarEt_All, evtweight);
            _histos.Fill1D("smeared_hZcandLumi_emuparasetEff_CC", Lumi, evtweight);
            _histos.Fill2D("smeared_hZcandSETLumi_emuparasetEff_CC", scalarEt_All, Lumi, evtweight);
          }
        }
      }
    }

    // correlation study

    // tag on 1st electron, look at 2nd electron, 
    // only consider electrons pass CCFID and ElecPT cuts
    if (Elec1){

      UPara2=zcand.UPara2();

      // in case 1st pass, check the 2nd one
      if (passesEMIDEff1&&passesTrkEff1&&CutTrkpt1&&passesPreselEff1&&passesUParaCorrection1&&passSETeff1&&passesAddOnEff1) {
        // look at the 2nd elec., 
        // only consider electrons pass CCFID and ElecPT cuts
        if (Elec2){
          // denominator 
          _histos.Fill1D("smeared_hZcandUparaOnePass_noEff_CC", UPara2, evtweight);      
          _histos.Fill1D("smeared_hZcandElecPtOnePass_noEff_CC", ElecPt2, evtweight);      
          _histos.Fill1D("smeared_hZcandTrueElecPtOnePass_noEff_CC", TrueElecPt2, evtweight);      
          _histos.Fill1D("smeared_hZcandPteeOnePass_noEff_CC", Ptee, evtweight);      
          // numerator
          if (passesEMIDEff2&&passesTrkEff2&&CutTrkpt2&&passesPreselEff2&&passesUParaCorrection2&&passSETeff2&&passesAddOnEff2){
            _histos.Fill1D("smeared_hZcandUparaOnePass_emuparasetEff_CC", UPara2, evtweight);
            _histos.Fill1D("smeared_hZcandElecPtOnePass_emuparasetEff_CC", ElecPt2, evtweight);
            _histos.Fill1D("smeared_hZcandTrueElecPtOnePass_emuparasetEff_CC", TrueElecPt2, evtweight);
            _histos.Fill1D("smeared_hZcandPteeOnePass_emuparasetEff_CC", Ptee, evtweight);
          }
        }
      }
      // in case 1st not pass, check the 2nd one
      else {
        // look at the 2nd elec., 
        // only consider electrons pass CCFID and ElecPT cuts
        if (Elec2){
          // denominator 
          _histos.Fill1D("smeared_hZcandUparaOneNotPass_noEff_CC", UPara2, evtweight);
          _histos.Fill1D("smeared_hZcandElecPtOneNotPass_noEff_CC", ElecPt2, evtweight);
          _histos.Fill1D("smeared_hZcandTrueElecPtOneNotPass_noEff_CC", TrueElecPt2, evtweight);
          _histos.Fill1D("smeared_hZcandPteeOneNotPass_noEff_CC", Ptee, evtweight); 
          // numerator
          if (passesEMIDEff2&&passesTrkEff2&&CutTrkpt2&&passesPreselEff2&&passesUParaCorrection2&&passSETeff2&&passesAddOnEff2){
            _histos.Fill1D("smeared_hZcandUparaOneNotPass_emuparasetEff_CC", UPara2, evtweight);
            _histos.Fill1D("smeared_hZcandElecPtOneNotPass_emuparasetEff_CC", ElecPt2, evtweight);
            _histos.Fill1D("smeared_hZcandTrueElecPtOneNotPass_emuparasetEff_CC", TrueElecPt2, evtweight);
            _histos.Fill1D("smeared_hZcandPteeOneNotPass_emuparasetEff_CC", Ptee, evtweight);
          }
        } // if (Elec2) ..
      } // if (1st pass) else (1st not pass) ...
    } // if (Elec1) ..

    // tag on 2nd electron, look at 1st electron, 
    // only consider electrons pass CCFID and ElecPT cuts
    if (Elec2){

      UPara1=zcand.UPara1();
      
      // in case 2nd pass, check the 1st one
      if (passesEMIDEff2&&passesTrkEff2&&CutTrkpt2&&passesPreselEff2&&passesUParaCorrection2&&passSETeff2&&passesAddOnEff2) {
        // look at the 1st elec., 
        // only consider electrons pass CCFID and ElecPT cuts
        if (Elec1){
          // denominator 
          _histos.Fill1D("smeared_hZcandUparaOnePass_noEff_CC", UPara1, evtweight);
          _histos.Fill1D("smeared_hZcandElecPtOnePass_noEff_CC", ElecPt1, evtweight);
          _histos.Fill1D("smeared_hZcandTrueElecPtOnePass_noEff_CC", TrueElecPt1, evtweight);
          _histos.Fill1D("smeared_hZcandPteeOnePass_noEff_CC", Ptee, evtweight);
          // numerator
          if (passesEMIDEff1&&passesTrkEff1&&CutTrkpt1&&passesPreselEff1&&passesUParaCorrection1&&passSETeff1&&passesAddOnEff1){
            _histos.Fill1D("smeared_hZcandUparaOnePass_emuparasetEff_CC", UPara1, evtweight);
            _histos.Fill1D("smeared_hZcandElecPtOnePass_emuparasetEff_CC", ElecPt1, evtweight);
            _histos.Fill1D("smeared_hZcandTrueElecPtOnePass_emuparasetEff_CC", TrueElecPt1, evtweight);
            _histos.Fill1D("smeared_hZcandPteeOnePass_emuparasetEff_CC", Ptee, evtweight);
          }
        }
      }
      // in case 2nd not pass, check the 1st one
      else {
        // look at the 1st elec., 
        // only consider electrons pass CCFID and ElecPT cuts
        if (Elec1){
          // denominator 
          _histos.Fill1D("smeared_hZcandUparaOneNotPass_noEff_CC", UPara1, evtweight);
          _histos.Fill1D("smeared_hZcandElecPtOneNotPass_noEff_CC", ElecPt1, evtweight);
          _histos.Fill1D("smeared_hZcandTrueElecPtOneNotPass_noEff_CC", TrueElecPt1, evtweight);
          _histos.Fill1D("smeared_hZcandPteeOneNotPass_noEff_CC", Ptee, evtweight);
          // numerator
          if (passesEMIDEff1&&passesTrkEff1&&CutTrkpt1&&passesPreselEff1&&passesUParaCorrection1&&passSETeff1&&passesAddOnEff1){
            _histos.Fill1D("smeared_hZcandUparaOneNotPass_emuparasetEff_CC", UPara1, evtweight);
            _histos.Fill1D("smeared_hZcandElecPtOneNotPass_emuparasetEff_CC", ElecPt1, evtweight);
            _histos.Fill1D("smeared_hZcandTrueElecPtOneNotPass_emuparasetEff_CC", TrueElecPt1, evtweight);
            _histos.Fill1D("smeared_hZcandPteeOneNotPass_emuparasetEff_CC", Ptee, evtweight);
          }
        } // if (Elec1) ..
      } // if (2nd pass) else (2nd not pass) ...
    } // if (Elec2) ..


    // check both electron pass
    // only consider both electrons pass CCFID and ElecPT cuts
    if (Elec1&&Elec2){
      UPara1=zcand.UPara1();
      UPara2=zcand.UPara2();
      // denominator
      _histos.Fill1D("smeared_hZcandUparaBothPass_noEff_CC", UPara1, evtweight);
      _histos.Fill1D("smeared_hZcandUparaBothPass_noEff_CC", UPara2, evtweight);
      _histos.Fill1D("smeared_hZcandElecPtBothPass_noEff_CC", ElecPt1, evtweight);
      _histos.Fill1D("smeared_hZcandElecPtBothPass_noEff_CC", ElecPt2, evtweight);
      _histos.Fill1D("smeared_hZcandTrueElecPtBothPass_noEff_CC", TrueElecPt1, evtweight);
      _histos.Fill1D("smeared_hZcandTrueElecPtBothPass_noEff_CC", TrueElecPt2, evtweight);
      _histos.Fill1D("smeared_hZcandPteeBothPass_noEff_CC", Ptee, evtweight);
      // numerator
      if (passesEMIDEff1&&passesTrkEff1&&CutTrkpt1&&passesPreselEff1&&passesUParaCorrection1&&passSETeff1&&passesAddOnEff1&&
          passesEMIDEff2&&passesTrkEff2&&CutTrkpt2&&passesPreselEff2&&passesUParaCorrection2&&passSETeff2&&passesAddOnEff2 ) {
        _histos.Fill1D("smeared_hZcandUparaBothPass_emuparasetEff_CC", UPara1, evtweight);
        _histos.Fill1D("smeared_hZcandUparaBothPass_emuparasetEff_CC", UPara2, evtweight);
        _histos.Fill1D("smeared_hZcandElecPtBothPass_emuparasetEff_CC", ElecPt1, evtweight);
        _histos.Fill1D("smeared_hZcandElecPtBothPass_emuparasetEff_CC", ElecPt2, evtweight);
        _histos.Fill1D("smeared_hZcandTrueElecPtBothPass_emuparasetEff_CC", TrueElecPt1, evtweight);
        _histos.Fill1D("smeared_hZcandTrueElecPtBothPass_emuparasetEff_CC", TrueElecPt2, evtweight);
        _histos.Fill1D("smeared_hZcandPteeBothPass_emuparasetEff_CC", Ptee, evtweight);
      }
    } // if (Elec1&&Elec2) ..

  }
}
// END U_par control plots

// Constructor
ZAnalysis::ZAnalysis(TString parameter_filename,TRandom3* dummy):_ntotal(0) {

  // Read control flags
  ReadParameters(parameter_filename);
 
  // initialize EMSmear, EfficiencySmear, RecoilSmear and SETefficiencySmear
  _emsmear = new EMSmear(parameter_filename, _histos);
  _efficiencysmear = new EfficiencySmear(parameter_filename, _histos, _eff_ratios_Z_includeECtag);
  _recoilsmear = new RecoilSmear(parameter_filename, _histos, dummy);
  _SETefficiencysmear=0;
  if (_ZSETEffCorrection || _createRootTree2) {
    if (_ZSETEffCorrLumiSplit) {
      _SETefficiencysmear = new SETefficiencySmear_LumiDispatch(parameter_filename, false, &_ZSETEffCorrLumiSplit_Bins, &_ZSETEffCorrLumiSplit_NormCCCC, &_ZSETEffCorrLumiSplit_NormCCEC, &_ZSETEffCorrLumiSplit_NormECEC);
    } else {
      if (_ZSETEffCorrPTEpert) {
	if (_ZSETEffCorrPTEpert==3) {
	  _SETefficiencysmear = new SETefficiencySmear(_ZSETEffCorrParametersCCCC,_ZSETEffCorrParametersCCEC,_ZSETEffCorrParametersECEC,
						       _ZSETEffCorrScaled,_ZSETEffCorrScale,_ZSETEffCorrRelative,_ZSETEffCorrInterpolate,
						       _ZSETEffCorrPTEupara, _ZSETEffCorrPTEpert,
						       &_ZSETEffCorrEPTEpertBase,
						       &_ZSETEffCorrEPTEpertA, &_ZSETEffCorrEPTEpertB,
						       &_ZSETEffCorrEPTEpertC, &_ZSETEffCorrEPTEpertD,
						       &_ZSETEffCorrEPTEpertE, &_ZSETEffCorrEPTEpertF,
						       &_ZSETEffCorrEPTEpertG, &_ZSETEffCorrEPTEpertH,
						       &_ZSETEffCorrEPTEpertNorm, &_ZSETEffCorrEPTEparamsNorm_CommonMultiplier, _ZSETEffCorrPTEpertRelGlobNorm,
						       &_ZSETEffCorrDataRatioParameters, &_ZSETEffCorrDataRatioParameters2,
						       &_ZSETEffDataHackParameters,
						       &_ZSETEffCorrDataRatioPTFit, &_ZSETEffCorrDataRatioLumiFit,
						       &_ZSETEffCorrEPTEpertBase_EC,
						       &_ZSETEffCorrEPTEpertA_EC, &_ZSETEffCorrEPTEpertB_EC,
						       &_ZSETEffCorrEPTEpertC_EC, &_ZSETEffCorrEPTEpertD_EC,
						       &_ZSETEffCorrEPTEpertE_EC, &_ZSETEffCorrEPTEpertF_EC,
						       &_ZSETEffCorrEPTEpertG_EC, &_ZSETEffCorrEPTEpertH_EC,
						       &_ZSETEffCorrEPTEpertNorm_EC, _ZSETEffCorrPTEpertRelGlobNorm_EC,
						       _useHack, _useLumiBins);
	} else {
	  _SETefficiencysmear = new SETefficiencySmear(_ZSETEffCorrParametersCCCC,_ZSETEffCorrParametersCCEC,_ZSETEffCorrParametersECEC,
						       _ZSETEffCorrScaled,_ZSETEffCorrScale,_ZSETEffCorrRelative,_ZSETEffCorrInterpolate,
						       _ZSETEffCorrPTEpert, 
						       &_ZSETEffCorrPTEpertBase,
						       &_ZSETEffCorrPTEpertA, &_ZSETEffCorrPTEpertB,
						       &_ZSETEffCorrPTEpertC, &_ZSETEffCorrPTEpertD,
						       &_ZSETEffCorrPTEpertE, &_ZSETEffCorrPTEpertF,
						       &_ZSETEffCorrPTEpertG, &_ZSETEffCorrPTEpertH,
						       &_ZSETEffCorrPTEpertNorm,
						       &_ZSETEffCorrDataRatioParameters, &_ZSETEffCorrDataRatioParameters2,
						       &_ZSETEffDataHackParameters,
						       &_ZSETEffCorrDataRatioPTFit, &_ZSETEffCorrDataRatioLumiFit,
						       &_ZSETEffCorrPTEpertBase_EC,
						       &_ZSETEffCorrPTEpertA_EC, &_ZSETEffCorrPTEpertB_EC,
						       &_ZSETEffCorrPTEpertC_EC, &_ZSETEffCorrPTEpertD_EC,
						       &_ZSETEffCorrPTEpertE_EC, &_ZSETEffCorrPTEpertF_EC,
						       &_ZSETEffCorrPTEpertG_EC, &_ZSETEffCorrPTEpertH_EC,
						       &_ZSETEffCorrPTEpertNorm_EC, _useHack, _useLumiBins);
	}
      } else {
	_SETefficiencysmear = new SETefficiencySmear(_ZSETEffCorrParametersCCCC,_ZSETEffCorrParametersCCEC,_ZSETEffCorrParametersECEC,_ZSETEffCorrScaled,_ZSETEffCorrScale,false,false,0,(std::vector<float>*)NULL);
      }
    }
  }
  // RCLSA: Initialization of Recoil Fit

  if(_ZHadronicRecoilBifurcateStudy) {
    cout << "Recoil Smearing Template Initialization..." << endl;
    cout << _ZRecoilBifurcateBins[0]+1 << " bins of RelScale A" << endl;
    cout << _ZRecoilBifurcateBins[1]+1 << " bins of RelScale B" << endl;
    cout << _ZRecoilBifurcateBins[2]+1 << " bins of Tau_HAD" << endl;
    cout << _ZRecoilBifurcateBins[3]+1 << " bins of RelSamp A" << endl;
    cout << _ZRecoilBifurcateBins[4]+1 << " bins of RelSamp B" << endl;
    cout << _ZRecoilBifurcateBins[5]+1 << " bins of alpha_mb" << endl;
    cout << _ZRecoilBifurcateBins[6]+1 << " bins of RelPhi A" << endl;
    cout << _ZRecoilBifurcateBins[7]+1 << " bins of RelPhi B" << endl;
    cout << "10 bins of Z pT... reserving memory." << endl;

    eta_imbalance_x = new double********[_ZRecoilBifurcateBins[0]+1];
    
    eta_imbalance_x_1 = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_2 = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_3 = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_4 = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_5 = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_6 = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_7 = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_8 = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_9 = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_10 = new double********[_ZRecoilBifurcateBins[0]+1];
    
    eta_imbalance_x_1_evtsq = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_2_evtsq = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_3_evtsq = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_4_evtsq = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_5_evtsq = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_6_evtsq = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_7_evtsq = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_8_evtsq = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_9_evtsq = new double********[_ZRecoilBifurcateBins[0]+1];
    eta_imbalance_x_10_evtsq = new double********[_ZRecoilBifurcateBins[0]+1];
    
    eta_imbalance_x2 = new double********[_ZRecoilBifurcateBins[0]+1];
    delta_phi_x = new double********[_ZRecoilBifurcateBins[0]+1];
    delta_phi_x2 = new double********[_ZRecoilBifurcateBins[0]+1];
    evt_weight = new double********[_ZRecoilBifurcateBins[0]+1];
    evt_weight_2 = new double********[_ZRecoilBifurcateBins[0]+1];
    for (int iHAD=0; iHAD<=_ZRecoilBifurcateBins[0]; iHAD++){
      eta_imbalance_x[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];

      eta_imbalance_x_1[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_2[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_3[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_4[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_5[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_6[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_7[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_8[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_9[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_10[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];

      eta_imbalance_x_1_evtsq[iHAD] =  new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_2_evtsq[iHAD] =  new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_3_evtsq[iHAD] =  new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_4_evtsq[iHAD] =  new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_5_evtsq[iHAD] =  new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_6_evtsq[iHAD] =  new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_7_evtsq[iHAD] =  new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_8_evtsq[iHAD] =  new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_9_evtsq[iHAD] =  new double*******[_ZRecoilBifurcateBins[1]+1];
      eta_imbalance_x_10_evtsq[iHAD] =  new double*******[_ZRecoilBifurcateBins[1]+1];

      eta_imbalance_x2[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      delta_phi_x[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      delta_phi_x2[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      evt_weight[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      evt_weight_2[iHAD] = new double*******[_ZRecoilBifurcateBins[1]+1];
      for (int jHAD=0; jHAD<=_ZRecoilBifurcateBins[1]; jHAD++){
	eta_imbalance_x[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];

	eta_imbalance_x_1[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_2[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_3[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_4[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_5[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_6[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_7[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_8[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_9[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_10[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];

	eta_imbalance_x_1_evtsq[iHAD][jHAD] =  new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_2_evtsq[iHAD][jHAD] =  new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_3_evtsq[iHAD][jHAD] =  new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_4_evtsq[iHAD][jHAD] =  new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_5_evtsq[iHAD][jHAD] =  new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_6_evtsq[iHAD][jHAD] =  new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_7_evtsq[iHAD][jHAD] =  new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_8_evtsq[iHAD][jHAD] =  new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_9_evtsq[iHAD][jHAD] =  new double******[_ZRecoilBifurcateBins[2]+1];
	eta_imbalance_x_10_evtsq[iHAD][jHAD] =  new double******[_ZRecoilBifurcateBins[2]+1];


	eta_imbalance_x2[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	delta_phi_x[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	delta_phi_x2[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	evt_weight[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	evt_weight_2[iHAD][jHAD] = new double******[_ZRecoilBifurcateBins[2]+1];
	for (int kHAD=0; kHAD<=_ZRecoilBifurcateBins[2]; kHAD++){
	  eta_imbalance_x[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];

	  eta_imbalance_x_1[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_2[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_3[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_4[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_5[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_6[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_7[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_8[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_9[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_10[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];

	  eta_imbalance_x_1_evtsq[iHAD][jHAD][kHAD] =  new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_2_evtsq[iHAD][jHAD][kHAD] =  new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_3_evtsq[iHAD][jHAD][kHAD] =  new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_4_evtsq[iHAD][jHAD][kHAD] =  new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_5_evtsq[iHAD][jHAD][kHAD] =  new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_6_evtsq[iHAD][jHAD][kHAD] =  new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_7_evtsq[iHAD][jHAD][kHAD] =  new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_8_evtsq[iHAD][jHAD][kHAD] =  new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_9_evtsq[iHAD][jHAD][kHAD] =  new double*****[_ZRecoilBifurcateBins[3]+1];
	  eta_imbalance_x_10_evtsq[iHAD][jHAD][kHAD] =  new double*****[_ZRecoilBifurcateBins[3]+1];

	  eta_imbalance_x2[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  delta_phi_x[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  delta_phi_x2[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  evt_weight[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  evt_weight_2[iHAD][jHAD][kHAD] = new double*****[_ZRecoilBifurcateBins[3]+1];
	  for (int mHAD=0; mHAD<=_ZRecoilBifurcateBins[3]; mHAD++){
	    eta_imbalance_x[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];

	    eta_imbalance_x_1[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_2[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_3[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_4[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_5[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_6[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_7[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_8[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_9[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_10[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];

	    eta_imbalance_x_1_evtsq[iHAD][jHAD][kHAD][mHAD] =  new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_2_evtsq[iHAD][jHAD][kHAD][mHAD] =  new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_3_evtsq[iHAD][jHAD][kHAD][mHAD] =  new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_4_evtsq[iHAD][jHAD][kHAD][mHAD] =  new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_5_evtsq[iHAD][jHAD][kHAD][mHAD] =  new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_6_evtsq[iHAD][jHAD][kHAD][mHAD] =  new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_7_evtsq[iHAD][jHAD][kHAD][mHAD] =  new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_8_evtsq[iHAD][jHAD][kHAD][mHAD] =  new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_9_evtsq[iHAD][jHAD][kHAD][mHAD] =  new double****[_ZRecoilBifurcateBins[4]+1];
	    eta_imbalance_x_10_evtsq[iHAD][jHAD][kHAD][mHAD] =  new double****[_ZRecoilBifurcateBins[4]+1];


	    eta_imbalance_x2[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    delta_phi_x[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    delta_phi_x2[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    evt_weight[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    evt_weight_2[iHAD][jHAD][kHAD][mHAD] = new double****[_ZRecoilBifurcateBins[4]+1];
	    for (int nHAD=0; nHAD<=_ZRecoilBifurcateBins[4]; nHAD++){
	      eta_imbalance_x[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];

	      eta_imbalance_x_1[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_2[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_3[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_4[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_5[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_6[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_7[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_8[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_9[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_10[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];

	      eta_imbalance_x_1_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD] =  new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_2_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD] =  new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_3_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD] =  new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_4_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD] =  new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_5_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD] =  new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_6_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD] =  new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_7_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD] =  new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_8_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD] =  new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_9_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD] =  new double***[_ZRecoilBifurcateBins[5]+1];
	      eta_imbalance_x_10_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD] =  new double***[_ZRecoilBifurcateBins[5]+1];

	      eta_imbalance_x2[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      delta_phi_x[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      delta_phi_x2[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      evt_weight[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      evt_weight_2[iHAD][jHAD][kHAD][mHAD][nHAD] = new double***[_ZRecoilBifurcateBins[5]+1];
	      for (int pHAD=0; pHAD<=_ZRecoilBifurcateBins[5]; pHAD++){
		eta_imbalance_x[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];

		eta_imbalance_x_1[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_3[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_4[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_5[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_6[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_7[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_8[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_9[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_10[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];

		eta_imbalance_x_1_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] =  new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_2_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] =  new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_3_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] =  new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_4_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] =  new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_5_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] =  new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_6_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] =  new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_7_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] =  new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_8_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] =  new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_9_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] =  new double**[_ZRecoilBifurcateBins[6]+1];
		eta_imbalance_x_10_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] =  new double**[_ZRecoilBifurcateBins[6]+1];

		eta_imbalance_x2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		delta_phi_x[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		delta_phi_x2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		evt_weight[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		evt_weight_2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD] = new double**[_ZRecoilBifurcateBins[6]+1];
		for (int qHAD=0; qHAD<=_ZRecoilBifurcateBins[6]; qHAD++){
		  eta_imbalance_x[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];

		  eta_imbalance_x_1[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_3[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_4[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_5[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_6[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_7[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_8[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_9[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_10[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];

		  eta_imbalance_x_1_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] =  new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_2_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] =  new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_3_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] =  new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_4_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] =  new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_5_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] =  new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_6_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] =  new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_7_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] =  new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_8_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] =  new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_9_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] =  new double*[_ZRecoilBifurcateBins[7]+1];
		  eta_imbalance_x_10_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] =  new double*[_ZRecoilBifurcateBins[7]+1];

		  eta_imbalance_x2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  delta_phi_x[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  delta_phi_x2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  evt_weight[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  evt_weight_2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD] = new double*[_ZRecoilBifurcateBins[7]+1];
		  for (int rHAD=0; rHAD<=_ZRecoilBifurcateBins[7]; rHAD++){
		    eta_imbalance_x[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];

		    eta_imbalance_x_1[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    eta_imbalance_x_2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    eta_imbalance_x_3[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    eta_imbalance_x_4[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    eta_imbalance_x_5[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    eta_imbalance_x_6[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    eta_imbalance_x_7[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    eta_imbalance_x_8[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    eta_imbalance_x_9[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    eta_imbalance_x_10[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];

		    eta_imbalance_x_1_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] =  new double[10];
		    eta_imbalance_x_2_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] =  new double[10];
		    eta_imbalance_x_3_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] =  new double[10];
		    eta_imbalance_x_4_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] =  new double[10];
		    eta_imbalance_x_5_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] =  new double[10];
		    eta_imbalance_x_6_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] =  new double[10];
		    eta_imbalance_x_7_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] =  new double[10];
		    eta_imbalance_x_8_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] =  new double[10];
		    eta_imbalance_x_9_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] =  new double[10];
		    eta_imbalance_x_10_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] =  new double[10];
		    
		    eta_imbalance_x2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    delta_phi_x[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    delta_phi_x2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    evt_weight[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    evt_weight_2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD] = new double[10];
		    for (int hHAD=0; hHAD<10; hHAD++){
		      eta_imbalance_x[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;

		      eta_imbalance_x_1[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      eta_imbalance_x_2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      eta_imbalance_x_3[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      eta_imbalance_x_4[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      eta_imbalance_x_5[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      eta_imbalance_x_6[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      eta_imbalance_x_7[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      eta_imbalance_x_8[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      eta_imbalance_x_9[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      eta_imbalance_x_10[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;

		      eta_imbalance_x_1_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] =  0.0;
		      eta_imbalance_x_2_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] =  0.0;
		      eta_imbalance_x_3_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] =  0.0;
		      eta_imbalance_x_4_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] =  0.0;
		      eta_imbalance_x_5_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] =  0.0;
		      eta_imbalance_x_6_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] =  0.0;
		      eta_imbalance_x_7_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] =  0.0;
		      eta_imbalance_x_8_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] =  0.0;
		      eta_imbalance_x_9_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] =  0.0;
		      eta_imbalance_x_10_evtsq[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;

		      eta_imbalance_x2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      delta_phi_x[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      delta_phi_x2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      evt_weight[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		      evt_weight_2[iHAD][jHAD][kHAD][mHAD][nHAD][pHAD][qHAD][rHAD][hHAD] = 0.0;
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    cout << "Done" << endl;
    return;
  }

  if(_TransZHadronicRecoilBifurcateStudy) {

    cout << "Recoil Smearing Template Initialization..." << endl;
    cout << _TransZRecoilBifurcateBins[0]+1 << " bins of RelRespTrans" << endl;
    cout << _TransZRecoilBifurcateBins[1]+1 << " bins of RelResnTrans" << endl;
    cout << _TransZRecoilBifurcateBins[2]+1 << " bins of TauTrans" << endl;
    cout << _TransZRecoilBifurcateBins[3]+1 << " bins of alpha_mb_trans" << endl;
    cout << "10 bins of Z pT... reserving memory." << endl;

    trans_eta_imbalance_x = new double****[_TransZRecoilBifurcateBins[0]+1];
    trans_eta_imbalance_x2 = new double****[_TransZRecoilBifurcateBins[0]+1];
    trans_evt_weight = new double****[_TransZRecoilBifurcateBins[0]+1];
    trans_evt_weight_2 = new double****[_TransZRecoilBifurcateBins[0]+1];
    for (int iHAD=0; iHAD<=_TransZRecoilBifurcateBins[0]; iHAD++){
      trans_eta_imbalance_x[iHAD] = new double***[_TransZRecoilBifurcateBins[1]+1];
      trans_eta_imbalance_x2[iHAD] = new double***[_TransZRecoilBifurcateBins[1]+1];
      trans_evt_weight[iHAD] = new double***[_TransZRecoilBifurcateBins[1]+1];
      trans_evt_weight_2[iHAD] = new double***[_TransZRecoilBifurcateBins[1]+1];
      for (int jHAD=0; jHAD<=_TransZRecoilBifurcateBins[1]; jHAD++){
	trans_eta_imbalance_x[iHAD][jHAD] = new double**[_TransZRecoilBifurcateBins[2]+1];
	trans_eta_imbalance_x2[iHAD][jHAD] = new double**[_TransZRecoilBifurcateBins[2]+1];
	trans_evt_weight[iHAD][jHAD] = new double**[_TransZRecoilBifurcateBins[2]+1];
	trans_evt_weight_2[iHAD][jHAD] = new double**[_TransZRecoilBifurcateBins[2]+1];
	for (int kHAD=0; kHAD<=_TransZRecoilBifurcateBins[2]; kHAD++){
	  trans_eta_imbalance_x[iHAD][jHAD][kHAD] = new double*[_TransZRecoilBifurcateBins[3]+1];
	  trans_eta_imbalance_x2[iHAD][jHAD][kHAD] = new double*[_TransZRecoilBifurcateBins[3]+1];
	  trans_evt_weight[iHAD][jHAD][kHAD] = new double*[_TransZRecoilBifurcateBins[3]+1];
	  trans_evt_weight_2[iHAD][jHAD][kHAD] = new double*[_TransZRecoilBifurcateBins[3]+1];
	  for (int mHAD=0; mHAD<=_TransZRecoilBifurcateBins[3]; mHAD++){
	    trans_eta_imbalance_x[iHAD][jHAD][kHAD][mHAD] = new double[10];
	    trans_eta_imbalance_x2[iHAD][jHAD][kHAD][mHAD] = new double[10];
	    trans_evt_weight[iHAD][jHAD][kHAD][mHAD] = new double[10];
	    trans_evt_weight_2[iHAD][jHAD][kHAD][mHAD] = new double[10];
	    for (int nHAD=0; nHAD<10; nHAD++){
	      trans_eta_imbalance_x[iHAD][jHAD][kHAD][mHAD][nHAD] = 0.0;
	      trans_eta_imbalance_x2[iHAD][jHAD][kHAD][mHAD][nHAD] = 0.0;
	      trans_evt_weight[iHAD][jHAD][kHAD][mHAD][nHAD] = 0.0;
	      trans_evt_weight_2[iHAD][jHAD][kHAD][mHAD][nHAD] = 0.0;
	    }
	  }
	}
      }
    }
    cout << "Done" << endl;
    return;
  }


  // select only one option at a time for the hadronic studies
  _HadronicTemplateNumber = _NONE_;
  if( (int)_HadronicMomentumScaleStudy +
      (int)_HadronicMomentumResolutionStudy +
      (int)_HadronicMomentumScaleBifurcateStudy + 
      (int)_HadronicMomentumScale2BifurcateStudy + 
      (int)_HadronicMomentumResolutionBifurcateStudy +
      (int)_HadronicMomentumResolution2BifurcateStudy +
      (int)_HadronicMomentumResolution3BifurcateStudy +
      (int)_HadronicPhiSmearingBifurcateStudy +
      (int)_HadronicMomentum_AllAtOnce_BifurcateStudy > 1 ) {
    cout << endl
	 << "ZAnalysis: Only one hadronic study is allowed at a time!!!" << endl
	 << " HadronicMomentumScaleStudy                = " 
	 << _HadronicMomentumScaleStudy << endl
	 << " HadronicMomentumResolutionStudy           = " 
	 << _HadronicMomentumResolutionStudy << endl
	 << " HadronicMomentumScaleBifurcateStudy       = " 
	 << _HadronicMomentumScaleBifurcateStudy << endl
	 << " HadronicMomentumScale2BifurcateStudy       = " 
	 << _HadronicMomentumScale2BifurcateStudy << endl
	 << " HadronicMomentumResolutionBifurcateStudy  = " 
	 << _HadronicMomentumResolutionBifurcateStudy << endl
	 << " HadronicMomentumResolution2BifurcateStudy = " 
	 << _HadronicMomentumResolution2BifurcateStudy << endl
	 << " HadronicMomentumResolution3BifurcateStudy = " 
	 << _HadronicMomentumResolution3BifurcateStudy << endl
	 << " HadronicPhiSmearingBifurcateStudy         = " 
	 << _HadronicPhiSmearingBifurcateStudy << endl
	 << " HadronicMomentum_AllAtOnce_BifurcateStudy = " 
	 << _HadronicMomentum_AllAtOnce_BifurcateStudy << endl;
    throw;
  }
  // check that correct recoil smear option is selected for "bifurcated" recoil studies
  if( (_HadronicMomentumScaleBifurcateStudy       || 
       _HadronicMomentumScale2BifurcateStudy  ||
       _HadronicMomentumResolutionBifurcateStudy  ||
       _HadronicMomentumResolution2BifurcateStudy ||
       _HadronicMomentumResolution3BifurcateStudy ||
       _HadronicPhiSmearingBifurcateStudy         ||
       _HadronicMomentum_AllAtOnce_BifurcateStudy  ) &&
      (_recoilsmear->Momentum_SmearOption_HAD()!=1)         ) {
    cout << "ZAnalysis: Momentum smearing option must be 1 (not " 
	 << _recoilsmear->Momentum_SmearOption_HAD() <<") for all \"bifurcated\" studies !!!" << endl;
    throw;
  }

  // Book histograms
  
  _histos.add(ZCand_Hist,"smeared_","smeared");
  _histos.add(ZCand_Hist_2D,"smeared_","smeared");
  _histos.add(ZCand_Hist_2D_VARBIN_Y,"smeared_","smeared");
  _histos.add(ZCand_Profile,"smeared_","smeared");
  _histos.add(RECOIL_Hist,"smeared_","smeared");
  _histos.add(RECOIL_Hist_2D,"smeared_","smeared");
  _histos.add(RECOIL_Hist_2D_VARBIN_XY,"smeared_","smeared");
  _histos.add(RECOIL_Hist_Profile,"smeared_","smeared");

  if (_PlotUparaOverPte) {
    cout << "Add ZCand_Hist_UparaOverPte to Histos ..." << endl;
    _histos.add(ZCand_Hist_UparaOverPte,"smeared_","smeared");
  } else if ( _PlotCosUphi ) {
    cout << "Add ZCand_Hist_CosUphi to Histos ..." << endl;
    _histos.add(ZCand_Hist_CosUphi,"smeared_","smeared");
  } else {
    cout << "Add WCand_Hist_Upara to Histos ..." << endl;
    _histos.add(ZCand_Hist_Upara,"smeared_","smeared");
    _histos.add(ZCand_Hist_UparaUperp,"smeared_","smeared");
  };


  //_histos.add(EMSMEAR_Profile,"","check_zbdiff");
  //_histos.clone("ZBDiffvUparaCorr",11); 

  // Z mass for different eta categories
  _histos.clone("smeared_hZcandMass_Category", 15);
  _histos.clone("smeared_hZcandElecPt_Category", 15);
  _histos.clone("smeared_hZcandMass_Category_DetEta", 15);
  _histos.clone("smeared_hZcandElecPt_Category_DetEta", 15);
  _histos.clone("smeared_hZcandMass_V_fZ_CCCC_Category", 15);
  _histos.clone("smeared_hZcandMass_V_fZ_CCCC_Category_DetEta", 15);

  // Z mass for different eta categories
  _histos.clone("smeared_hZcandMass_Category_PhiMod", 15);
  _histos.clone("smeared_hZcandMass_Category_TruePhiMod", 15);
  _histos.clone("smeared_hZcandMass_V_fZ_CCCC_Category_PhiMod", 15);
  _histos.clone("smeared_hZcandMass_CrackCBTemplates_Category_PhiMod", 15);
  _histos.clone("smeared_ZMass_vs_Eta_Before_Trig_CC",4);
  _histos.clone("smeared_ZMass_vs_DetEta_Before_Trig_CC",4);
  _histos.clone("smeared_ZMass_vs_Pt_Before_Trig_CC",4);
  _histos.clone("smeared_ZMass_vs_Vtx_Before_Trig_CC",4);
  _histos.clone("smeared_ZMass_vs_Eta_After_Trig_CC",4);
  _histos.clone("smeared_ZMass_vs_DetEta_After_Trig_CC",4);
  _histos.clone("smeared_ZMass_vs_Pt_After_Trig_CC",4);
  _histos.clone("smeared_ZMass_vs_Vtx_After_Trig_CC",4);

  if (_doFzStudy){
    //energy categories
    _histos.clone("smeared_hZcandMass_V_fZ_CCCC_ElecPt2",10);
    _histos.clone("smeared_hZcandMass_V_fZ_CCCC_ElecPt",10);
    _histos.clone("smeared_hZcandMass_V_fZ_CCCC_ElecPt1",10);
    
    // fz categories
    _histos.clone("smeared_hZcandElecPt_fz", 24);
    _histos.clone("smeared_hZcandElec1Pt_fz", 24);
    _histos.clone("smeared_hZcandElec2Pt_fz", 24);
    _histos.clone("smeared_hZcandElecE_fz", 24);
    _histos.clone("smeared_hZcandElec1E_fz", 24);
    _histos.clone("smeared_hZcandElec2E_fz", 24);
    _histos.clone("smeared_hZcandElecEta_fz", 24);
    _histos.clone("smeared_hZcandElec1Eta_fz", 24);
    _histos.clone("smeared_hZcandElec2Eta_fz", 24);
    _histos.clone("smeared_hZcandElecDetEta_fz", 24);
    _histos.clone("smeared_hZcandElec1DetEta_fz", 24);
    _histos.clone("smeared_hZcandElec2DetEta_fz", 24);
    _histos.clone("smeared_hZcandMass_CCCC_fz", 24);
    _histos.clone("smeared_hZcandMass_CCCC_fz_Coarse", 6);
  }

  // for scalar Et
  _histos.clone("smeared_hZcandScalarEt_CCCC_bin", 10);
  _histos.clone("smeared_hZcandSqrtScalarEt_CCCC_bin", 10);
  _histos.clone("smeared_hZcandScalarEt_CCCC_genZPt_bin", 10);
  _histos.clone("smeared_hZcandSqrtScalarEt_CCCC_genZPt_bin", 10);
  
  //MW
  // for CC events, divided into different electron Pt regions
  _histos.clone("smeared_hZcandScalarEt_ElecPtBin", 7);
  _histos.clone("smeared_hZcandSEToverEpt_ElecPtBin", 7);
    
  // for tag-probe method
  if(_StudyEfficiencies) {

    _histos.clone("smeared_elecpT", 15);
    _histos.clone("smeared_elecpT_after", 15);

    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx", 14);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx", 14);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_0", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_1", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_2", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_3", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_4", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_5", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_6", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_7", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_8", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_9", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_10", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_11", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_12", 31);
    _histos.clone("smeared_ZMass_vs_Eta_Before_Trk_Vtx_13", 31);
    
    
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_0", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_1", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_2", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_3", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_4", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_5", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_6", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_7", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_8", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_9", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_10", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_11", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_12", 31);
    _histos.clone("smeared_ZMass_vs_Eta_After_Trk_Vtx_13", 31);

    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx", 12);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx", 12);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_0", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_1", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_2", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_3", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_4", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_5", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_6", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_7", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_8", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_9", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_10", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_11", 31);
    
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_0", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_1", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_2", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_3", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_4", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_5", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_6", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_7", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_8", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_9", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_10", 31);
    _histos.clone("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_11", 31);



    _histos.clone("smeared_ZMass_vs_Pt_Before_HMx_CC_Etabin", 15);
    _histos.clone("smeared_ZMass_vs_Pt_After_HMx_CC_Etabin", 15);
    _histos.clone("smeared_ZMass_vs_Pt_Before_Trk_CC_Etabin", 15);
    _histos.clone("smeared_ZMass_vs_Pt_After_Trk_CC_Etabin", 15);
    _histos.clone("smeared_ZMass_vs_Pt_Before_HMx_CC_SETbin", 5);
    _histos.clone("smeared_ZMass_vs_Pt_After_HMx_CC_SETbin", 5);
    _histos.clone("smeared_ZMass_vs_Pt_Before_Trk_CC_SETbin", 5);
    _histos.clone("smeared_ZMass_vs_Pt_After_Trk_CC_SETbin", 5);
    _histos.clone("smeared_ZMass_vs_Vtx_Before_Trk_CC_Etabin", 15);
    _histos.clone("smeared_ZMass_vs_Vtx_After_Trk_CC_Etabin", 15);

    _histos.clone("smeared_loose_ZMass_vs_Pt_Before_HMx_CC_Etabin", 15);
    _histos.clone("smeared_loose_ZMass_vs_Pt_After_HMx_CC_Etabin", 15);
    _histos.clone("smeared_loose_ZMass_vs_Pt_Before_Trk_CC_Etabin", 15);
    _histos.clone("smeared_loose_ZMass_vs_Pt_After_Trk_CC_Etabin", 15);
    _histos.clone("smeared_loose_ZMass_vs_Pt_Before_HMx_CC_SETbin", 5);
    _histos.clone("smeared_loose_ZMass_vs_Pt_After_HMx_CC_SETbin", 5);
    _histos.clone("smeared_loose_ZMass_vs_Pt_Before_Trk_CC_SETbin", 5);
    _histos.clone("smeared_loose_ZMass_vs_Pt_After_Trk_CC_SETbin", 5);
    _histos.clone("smeared_loose_ZMass_vs_Vtx_Before_Trk_CC_Etabin", 15);
    _histos.clone("smeared_loose_ZMass_vs_Vtx_After_Trk_CC_Etabin", 15);

  }
 
  if(_StudyEfficienciesTruth) {
    _histos.clone("smeared_EffTruth_EMPt_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_upara_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_upara_set_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_set_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set__cluscorr_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_set_CC", 15);
    _histos.clone("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set_trkpt_CC", 15);
  }

  // eta/xi (im)balance, recoil and met for different pT regions
  _histos.clone("smeared_hZcandEtaBalance_bin", 10);
  _histos.clone("smeared_hZcandXiBalance_bin", 10);
  _histos.clone("smeared_hZcandEtaImBalance_bin", 10);
  _histos.clone("smeared_hZcandXiImBalance_bin", 10);
  _histos.clone("smeared_hZcandMCPtDiff_bin", 10);
  _histos.clone("smeared_hZcandMCPhiDiff_bin", 10);
  _histos.clone("smeared_hZcandMass_bin", 10);
  _histos.clone("smeared_hZcandDiffMass_bin", 10);  
  _histos.clone("smeared_hZcandElecpT_bin", 10);
  _histos.clone("smeared_hZcandElec0pT_bin", 10);
  _histos.clone("smeared_hZcandElec1pT_bin", 10);
  _histos.clone("smeared_hZcandElecGenpT_bin", 10);
  _histos.clone("smeared_hZcandElecGen0pT_bin", 10);
  _histos.clone("smeared_hZcandElecGen1pT_bin", 10);
  _histos.clone("smeared_hZcandElecRawGenpT_bin", 10);
  _histos.clone("smeared_hZcandElecRawGen0pT_bin", 10);
  _histos.clone("smeared_hZcandElecRawGen1pT_bin", 10);
  _histos.clone("smeared_hZcandDiffElecpT_bin", 10);
  _histos.clone("smeared_hZcandDiffElec0pT_bin", 10);
  _histos.clone("smeared_hZcandDiffElec1pT_bin", 10);

  _histos.clone("smeared_hZcandElecE_bin", 10);
  _histos.clone("smeared_hZcandElec0E_bin", 10);
  _histos.clone("smeared_hZcandElec1E_bin", 10);
  _histos.clone("smeared_hZcandElecGenE_bin", 10);
  _histos.clone("smeared_hZcandElecGen0E_bin", 10);
  _histos.clone("smeared_hZcandElecGen1E_bin", 10);
  _histos.clone("smeared_hZcandElecRawGenE_bin", 10);
  _histos.clone("smeared_hZcandElecRawGen0E_bin", 10);
  _histos.clone("smeared_hZcandElecRawGen1E_bin", 10);
  _histos.clone("smeared_hZcandDiffElecE_bin", 10);
  _histos.clone("smeared_hZcandDiffElec0E_bin", 10);
  _histos.clone("smeared_hZcandDiffElec1E_bin", 10);

  _histos.clone("smeared_hZcandEtaImBalance_ZPt_Projected_bin", 10);
  _histos.clone("smeared_hZcandXiImBalance_ZPt_Projected_bin", 10);
  _histos.clone("smeared_hZcandEtaImBalance_genZPt_bin", 10);
  _histos.clone("smeared_hZcandXiImBalance_genZPt_bin", 10);
  _histos.clone("smeared_hZcandRecoilPt_genZPt_bin", 10);  
  _histos.clone("smeared_hZcandMCPtDiff_genZPt_bin", 10);

  _histos.clone("smeared_hZcandPt_bin", 10);
  _histos.clone("smeared_hZcandPt_Projected_bin", 10);
  _histos.clone("smeared_hZcandRecoilPt_bin", 10);
  _histos.clone("smeared_hZcandRecoilPhi_bin", 10);
  _histos.clone("smeared_hZcandPhi_bin", 10);
  _histos.clone("smeared_hZcandRecoilPx_bin", 10);
  _histos.clone("smeared_hZcandRecoilPy_bin", 10);
  _histos.clone("smeared_hZcandMET_bin", 10);
  _histos.clone("smeared_hZcandMETPhi_bin", 10);
  _histos.clone("smeared_hZcandMETx_bin", 10);
  _histos.clone("smeared_hZcandMETy_bin", 10);
  _histos.clone("smeared_hZcandDeltaPhi_EM_Recoil_bin", 10);
  _histos.clone("smeared_hZcandDeltaPhi_EM_Met_bin", 10);
  _histos.clone("smeared_hZcandCosDeltaPhi_EM1_EM2_bin", 10);
  _histos.clone("smeared_hZcandDiffCosDeltaPhi_EM1_EM2_bin", 10);
  _histos.clone("smeared_hZcandDeltaEta_EM1_EM2_bin", 10);
  _histos.clone("smeared_hZcandDiffDeltaEta_EM1_EM2_bin", 10);
  _histos.clone("smeared_hZcandDeltaPhi_Recoil_Met_bin", 10);
  _histos.clone("smeared_hZcandDeltaPhi_Z_Recoil_bin", 10);
  _histos.clone("smeared_hZcandDeltaPhiUnfolded_Z_Recoil_bin", 10);
  _histos.clone("smeared_hZcandDeltaPhi_Z_Met_bin", 10);
  _histos.clone("smeared_hZcandPee_eta_bin", 10);

  _histos.clone("smeared_hZcandOpeningAngle_bin", 10);
  _histos.clone("smeared_hZcandEtaImBalancePt1_bin", 10);
  _histos.clone("smeared_hZcandEtaImBalancePt2_bin", 10);

  if (_makeZGenPlots) {
    _histos.add(MCZBOSON_Hist,"gen_","generated");
    _histos.add(ZCand_Hist,"gen_","generated");
    _histos.add(ZCand_Hist_2D,"gen_","generated");
    _histos.add(RECOIL_Hist,"gen_","generated");
    _histos.add(RECOIL_Hist_2D,"gen_","generated");
    _histos.add(RECOIL_Hist_Profile,"gen_","generated");
    _histos.clone("gen_hZcandEtaBalance_bin", 10);
    _histos.clone("gen_hZcandXiBalance_bin", 10);
    _histos.clone("gen_hZcandEtaImBalance_bin", 10);
    _histos.clone("gen_hZcandXiImBalance_bin", 10);
    _histos.clone("gen_hZcandRecoilPt_bin", 10);
    _histos.clone("gen_hZcandRecoilPhi_bin", 10);
    _histos.clone("gen_hZcandRecoilPx_bin", 10);
    _histos.clone("gen_hZcandRecoilPy_bin", 10);
    _histos.clone("gen_hZcandMET_bin", 10);
    _histos.clone("gen_hZcandMETPhi_bin", 10);
    _histos.clone("gen_hZcandMETx_bin", 10);
    _histos.clone("gen_hZcandMETy_bin", 10);
    _histos.clone("gen_hZcandDeltaPhi_EM_Recoil_bin", 10);
    _histos.clone("gen_hZcandDeltaPhi_EM_Met_bin", 10);
    _histos.clone("gen_hZcandCosDeltaPhi_EM1_EM2_bin", 10);
    _histos.clone("gen_hZcandDiffCosDeltaPhi_EM1_EM2_bin", 10);
    _histos.clone("gen_hZcandDeltaEta_EM1_EM2_bin", 10);
    _histos.clone("gen_hZcandDiffDeltaEta_EM1_EM2_bin", 10);
    _histos.clone("gen_hZcandDeltaPhi_Recoil_Met_bin", 10);
    _histos.clone("gen_hZcandDeltaPhi_Z_Recoil_bin", 10);
    _histos.clone("gen_hZcandDeltaPhiUnfolded_Z_Recoil_bin", 10);
    _histos.clone("gen_hZcandDeltaPhi_Z_Met_bin", 10);
    _histos.clone("gen_hZcandPee_eta_bin", 10);
  }


  if( _TB_Correction_Option==1 && _TBStudy){

   
    _histos.clone("smeared_hZcandRecoilPhi_CCCC", (_Bins_TBStudy+1)*(_Bins_TBStudy+1));
    _histos.clone("smeared_hZcandMETPhi_CCCC", (_Bins_TBStudy+1)*(_Bins_TBStudy+1));
    _histos.th1d("smeared_histd1map_TBalphaTemplates")->GetXaxis()->Set(_Bins_TBStudy, 
									     _tbalpha_center-(_Bins_TBStudy/2)*_tbalpha_step, 
									     _tbalpha_center+(_Bins_TBStudy/2)*_tbalpha_step);
    _histos.th1d("smeared_histd2map_TBbetaTemplates")->GetXaxis()->Set(_Bins_TBStudy, 
									     _tbbeta_center-(_Bins_TBStudy/2)*_tbbeta_step, 
									     _tbbeta_center+(_Bins_TBStudy/2)*_tbbeta_step);
  }

  if (_radLengthStudy){
    _histos.clone("smeared_hZcandElecTrkPtOvE_All", (_Bins_radLengthStudy_CC+1)*(_Bins_radLengthStudy_CC+1) );
    _histos.clone("smeared_hZcandElecTrkPtOvE_CC", (_Bins_radLengthStudy_CC+1)*(_Bins_radLengthStudy_CC+1) );
    _histos.clone("smeared_hZcandElecTrkPtOvE_CCCC", (_Bins_radLengthStudy_CC+1)*(_Bins_radLengthStudy_CC+1) );
    _histos.clone("smeared_hZcandElecTrkPt_CCCC", (_Bins_radLengthStudy_CC+1)*(_Bins_radLengthStudy_CC+1) );
    _histos.clone("smeared_hZcandElecTrkPtOvE_EC", (_Bins_radLengthStudy_CC+1)*(_Bins_radLengthStudy_CC+1) );
    _histos.th1d("smeared_histd1map_RADTemplates")->GetXaxis()->Set(_Bins_radLengthStudy_CC, _radLengthcenter_CC  -_Bins_radLengthStudy_CC /2 * _radLengthstep_CC, _radLengthcenter_CC+_Bins_radLengthStudy_CC /2 * _radLengthstep_CC );
    _histos.th1d("smeared_histd2map_RADTemplates2")->GetXaxis()->Set(_Bins_radLengthStudy_CC, _CCMScenterC  -_Bins_radLengthStudy_CC/2 * _CCMSstepC, _CCMScenterC+_Bins_radLengthStudy_CC/2 * _CCMSstepC );

  }


  if(_momentumScaleStudy){
  
    _histos.clone("smeared_hZcandElecTrkCalMass_All_CC", (_Bins_CCMSStudy+1)*(_Bins_CCMSStudy+1));
    _histos.clone("smeared_hZcandElecTrkCalMass_All", (_Bins_CCMSStudy+1)*(_Bins_CCMSStudy+1));

    
    _histos.clone("smeared_hZcandElecTrkCalMass_CC_CC", (_Bins_CCMSStudy+1)*(_Bins_CCMSStudy+1));
    _histos.clone("smeared_hZcandElecTrkCalMass_CC_EC", (_Bins_CCMSStudy+1)*(_Bins_CCMSStudy+1));
    _histos.clone("smeared_hZcandElecTrkCalMass_CC", (_Bins_CCMSStudy+1)*(_Bins_CCMSStudy+1));

    
    _histos.th1d("smeared_histd2map_CCMSTemplates")->GetXaxis()->Set(_Bins_CCMSStudy, _CCMScenterB - _Bins_CCMSStudy/2 * _CCMSstepB,_CCMScenterB+ _Bins_CCMSStudy/2 * _CCMSstepB );
    
    if (_study_AB)
      _histos.th1d("smeared_histd1map_CCMSTemplates")->GetXaxis()->Set(_Bins_CCMSStudy, _CCMScenterA - _Bins_CCMSStudy/2 * _CCMSstepA,_CCMScenterA+ _Bins_CCMSStudy/2 * _CCMSstepA );
    else
      _histos.th1d("smeared_histd1map_CCMSTemplates")->GetXaxis()->Set(_Bins_CCMSStudy, _CCMScenterC - _Bins_CCMSStudy/2 * _CCMSstepC,_CCMScenterC+ _Bins_CCMSStudy/2 * _CCMSstepC );

      _histos.th1d("smeared_histd1map_ECMSTemplates")->GetXaxis()->Set(_Bins_ECMSStudy, _ECMScenterA - _Bins_ECMSStudy/2 * _ECMSstepA,_ECMScenterA+ _Bins_ECMSStudy/2 * _ECMSstepA );
    _histos.th1d("smeared_histd2map_ECMSTemplates")->GetXaxis()->Set(_Bins_ECMSStudy, _ECMScenterB - _Bins_ECMSStudy/2 * _ECMSstepB,_ECMScenterB+ _Bins_ECMSStudy/2 * _ECMSstepB );


  }


  
  // histograms for electron energy scale study
  if (_EnergyScaleStudy) {
    if(_StudyCCScale) {
      _histos.clone("smeared_hZcandMass_Scale_CCCC", (_Bins_ScaleStudy+1)*(_Bins_ScaleStudy+1));
      _histos.clone("smeared_hZcandMass_V_fZ_CCCC", (_Bins_ScaleStudy+1)*(_Bins_ScaleStudy+1));
      _histos.clone("smeared_hZcandMass_V_fZ_CCCC_pro", (_Bins_ScaleStudy+1)*(_Bins_ScaleStudy+1));
    } else{
      _histos.clone("smeared_hZcandMass_Scale_ECEC", (_Bins_ScaleStudy+1)*(_Bins_ScaleStudy+1));
      _histos.clone("smeared_hZcandMass_V_fZ_ECEC", (_Bins_ScaleStudy+1)*(_Bins_ScaleStudy+1));
      _histos.clone("smeared_hZcandMass_V_fZ_ECEC_pro",  (_Bins_ScaleStudy+1)*(_Bins_ScaleStudy+1));
    }
    
    // define map histograms, often number of bins is sqrt(# of grids)
    _histos.th1d("smeared_histd1map_EScaleOffsetTemplates")->GetXaxis()->Set(_Bins_ScaleStudy, 
									     _scale_center-(_Bins_ScaleStudy/2)*_scale_step, 
									     _scale_center+(_Bins_ScaleStudy/2)*_scale_step);
    _histos.th1d("smeared_histd2map_EScaleOffsetTemplates")->GetXaxis()->Set(_Bins_ScaleStudy, 
									     _offset_center-(_Bins_ScaleStudy/2)*_offset_step, 
									     _offset_center+(_Bins_ScaleStudy/2)*_offset_step);    
  }

  // histograms for electron energy resolution study
  if (_EnergyResolutionStudy) {
    if (!_SkipSampling) {
      if(_StudyCCResolution) _histos.clone("smeared_hZcandMass_Resolution_CCCC", (_Bins_ResolutionStudy+1)*(_Bins_ResolutionStudy+1));
      else _histos.clone("smeared_hZcandMass_Resolution_ECEC", (_Bins_ResolutionStudy+1)*(_Bins_ResolutionStudy+1));
    } 
    else if (!(_SkipeNoise && _SkipConstant)){
      if(_StudyCCResolution) _histos.clone("smeared_hZcandMass_Resolution_CCCC", (_Bins_ResolutionStudy+1)*(_Bins_ResolutionStudy+1));
      else _histos.clone("smeared_hZcandMass_Resolution_ECEC", (_Bins_ResolutionStudy+1)*(_Bins_ResolutionStudy+1));
    }
    else {
      if(_StudyCCResolution) _histos.clone("smeared_hZcandMass_Resolution_CCCC", (_Bins_ResolutionStudy+1));
      else _histos.clone("smeared_hZcandMass_Resolution_ECEC", (_Bins_ResolutionStudy+1));
    }

    // define map histograms, often number of bins is sqrt(# of grids)
    if (!_SkipSampling) {
      _histos.th1d("smeared_histd1map_SamplingConstantTemplates")->GetXaxis()->Set(_Bins_ResolutionStudy, 
										   _sampling_center-(_Bins_ResolutionStudy/2)*_sampling_step, 
										   _sampling_center+(_Bins_ResolutionStudy/2)*_sampling_step);
    } else {
      _histos.th1d("smeared_histd1map_SamplingConstantTemplates")->GetXaxis()->Set(1, _sampling_center-_sampling_step, _sampling_center+_sampling_step);
    }
    if (!_SkipeNoise) {
      _histos.th1d("smeared_histd1map_eNoiseTemplates")->GetXaxis()->Set(_Bins_ResolutionStudy, 
										   _enoise_center-(_Bins_ResolutionStudy/2)*_enoise_step, 
										   _enoise_center+(_Bins_ResolutionStudy/2)*_enoise_step);
    } else {
      _histos.th1d("smeared_histd1map_eNoiseTemplates")->GetXaxis()->Set(1, _enoise_center-_enoise_step, _enoise_center+_enoise_step);
    }
    _histos.th1d("smeared_histd2map_SamplingConstantTemplates")->GetXaxis()->Set(_Bins_ResolutionStudy, 
										 _constant_center-(_Bins_ResolutionStudy/2)*_constant_step, 
										 _constant_center+(_Bins_ResolutionStudy/2)*_constant_step);
  }

  // Crystal Ball parameter templates (or PeakShift parameter templates)
  if(_MakeCrackCBtemplates){
      char name[50];
      for(int ibin=0; ibin<15; ibin++) {
          sprintf(name, "%s%d", "smeared_hZcandMass_CrackCBTemplates_Category_PhiMod_", ibin);
          _histos.clone(name, (_Bins_MakeCrackCBtemplates+1)*(_Bins_MakeCrackCBtemplates+1));
      }
       // define map histograms, often number of bins is sqrt(# of grids)
      _histos.th1d("smeared_histd1map_CrackCB_alphaOffsetSlopeTemplates")->GetXaxis()->Set(_Bins_MakeCrackCBtemplates, 
									     _CrackCB_alphaOffset_center-(_Bins_MakeCrackCBtemplates/2)*_CrackCB_alphaOffset_step, 
									     _CrackCB_alphaOffset_center+(_Bins_MakeCrackCBtemplates/2)*_CrackCB_alphaOffset_step);
      _histos.th1d("smeared_histd2map_CrackCB_alphaOffsetSlopeTemplates")->GetXaxis()->Set(_Bins_MakeCrackCBtemplates, 
									     _CrackCB_alphaSlope_center-(_Bins_MakeCrackCBtemplates/2)*_CrackCB_alphaSlope_step, 
									     _CrackCB_alphaSlope_center+(_Bins_MakeCrackCBtemplates/2)*_CrackCB_alphaSlope_step);    
  }
  

 
  // histograms for hadronic momentum scale study
  if(_HadronicMomentumScaleStudy) {
    _HadronicTemplateNumber=_MOMENTUM_SCALE_;
    char name[50];
    for(int ibin=0; ibin<10; ibin++) {
      sprintf(name, "%s%d", "smeared_hZcandEtaImBalance_bin_", ibin);
      _histos.clone(name, (_Bins_HadronicScaleStudy+1)*(_Bins_HadronicScaleStudy+1));
    }
    
    // define map histograms, often number of bins is sqrt(# of grids)
    _histos.th1d("smeared_histd1map_HadronicScaleTemplates")->GetXaxis()->Set(_Bins_HadronicScaleStudy, 
									      _scale_HAD_A_center-(_Bins_HadronicScaleStudy/2)*_scale_HAD_A_step, 
									      _scale_HAD_A_center+(_Bins_HadronicScaleStudy/2)*_scale_HAD_A_step );
    _histos.th1d("smeared_histd2map_HadronicScaleTemplates")->GetXaxis()->Set(_Bins_HadronicScaleStudy, 
									      _scale_HAD_B_center-(_Bins_HadronicScaleStudy/2)*_scale_HAD_B_step, 
									      _scale_HAD_B_center+(_Bins_HadronicScaleStudy/2)*_scale_HAD_B_step );
  }

  // histograms for hadronic momentum scale sampling term and # of minbias events to overlay
  if(_HadronicMomentumResolutionStudy) {
    _HadronicTemplateNumber=_MOMENTUM_RESOLUTION_;
    char name[50];
    for(int ibin=0; ibin<10; ibin++) {
      sprintf(name, "%s%d", "smeared_hZcandEtaImBalance_bin_", ibin);
      _histos.clone(name, (_Bins_HadronicResolutionStudy+1)*(_Bins_HadronicResolutionStudy+1));
    }
    
    // define map histograms, often number of bins is sqrt(# of grids)
    _histos.th1d("smeared_histd1map_HadronicResolutionTemplates")->GetXaxis()->Set(_Bins_HadronicResolutionStudy, 
									      _sampling_HAD_center-(_Bins_HadronicResolutionStudy/2)*_sampling_HAD_step, 
									      _sampling_HAD_center+(_Bins_HadronicResolutionStudy/2)*_sampling_HAD_step );
    _histos.th1d("smeared_histd2map_HadronicResolutionTemplates")->GetXaxis()->Set(_Bins_HadronicResolutionStudy, 
									      _alpha_mb_center-(_Bins_HadronicResolutionStudy/2)*_alpha_mb_step, 
									      _alpha_mb_center+(_Bins_HadronicResolutionStudy/2)*_alpha_mb_step );
  }

  // histograms for hadronic momentum scale study for bifurcate method
  if(_HadronicMomentumScaleBifurcateStudy) {
    _HadronicTemplateNumber=_MOMENTUM_SCALE_BIFURCATE_;
    char name[50];
    for(int ibin=0; ibin<10; ibin++) {
      sprintf(name, "%s%d", "smeared_hZcandEtaImBalance_bin_", ibin);
      _histos.clone(name, (_Bins_HadronicScaleBifurcateStudy+1)*(_Bins_HadronicScaleBifurcateStudy+1));
    }
    
    // define map histograms, often number of bins is sqrt(# of grids)
    _histos.th1d("smeared_histd1map_HadronicScaleBifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicScaleBifurcateStudy, 
										       _scale_HAD_bifurcate_A_center-(_Bins_HadronicScaleBifurcateStudy/2)*_scale_HAD_bifurcate_A_step, 
										       _scale_HAD_bifurcate_A_center+(_Bins_HadronicScaleBifurcateStudy/2)*_scale_HAD_bifurcate_A_step );
    _histos.th1d("smeared_histd2map_HadronicScaleBifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicScaleBifurcateStudy, 
										       _scale_HAD_bifurcate_B_center-(_Bins_HadronicScaleBifurcateStudy/2)*_scale_HAD_bifurcate_B_step, 
										       _scale_HAD_bifurcate_B_center+(_Bins_HadronicScaleBifurcateStudy/2)*_scale_HAD_bifurcate_B_step );
  }

  // histograms for hadronic momentum scale study for bifurcate method
  if(_HadronicMomentumScale2BifurcateStudy) {
    _HadronicTemplateNumber=_MOMENTUM_SCALE_BIFURCATE2_;
    char name[50];
    for(int ibin=0; ibin<10; ibin++) {
      sprintf(name, "%s%d", "smeared_hZcandEtaImBalance_bin_", ibin);
      _histos.clone(name, (_Bins_HadronicScale2BifurcateStudy+1)*(_Bins_HadronicScale2BifurcateStudy+1)*(_Bins_HadronicScale2BifurcateStudy+1));
    }
    
    // define map histograms, often number of bins is sqrt(# of grids)
    _histos.th1d("smeared_histd1map_HadronicScale2BifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicScale2BifurcateStudy, 
										        _scale_HAD_bifurcate2_A_center-(_Bins_HadronicScale2BifurcateStudy/2)*_scale_HAD_bifurcate2_A_step, 
										        _scale_HAD_bifurcate2_A_center+(_Bins_HadronicScale2BifurcateStudy/2)*_scale_HAD_bifurcate2_A_step );
    _histos.th1d("smeared_histd2map_HadronicScale2BifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicScale2BifurcateStudy, 
										        _scale_HAD_bifurcate2_B_center-(_Bins_HadronicScale2BifurcateStudy/2)*_scale_HAD_bifurcate2_B_step, 
										        _scale_HAD_bifurcate2_B_center+(_Bins_HadronicScale2BifurcateStudy/2)*_scale_HAD_bifurcate2_B_step );
    _histos.th1d("smeared_histd3map_HadronicScale2BifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicScale2BifurcateStudy, 
										        _scale_HAD_bifurcate2_Tau_center-(_Bins_HadronicScale2BifurcateStudy/2)*_scale_HAD_bifurcate2_Tau_step, 
										        _scale_HAD_bifurcate2_Tau_center+(_Bins_HadronicScale2BifurcateStudy/2)*_scale_HAD_bifurcate2_Tau_step );
  }

  // histograms for hadronic momentum resolution study for bifurcate method (for hard component)
  if(_HadronicMomentumResolutionBifurcateStudy) {
    _HadronicTemplateNumber=_MOMENTUM_RESOLUTION_BIFURCATE_;
    char name[50];
    for(int ibin=0; ibin<10; ibin++) {
      sprintf(name, "%s%d", "smeared_hZcandEtaImBalance_bin_", ibin);
      _histos.clone(name, (_Bins_HadronicResolutionBifurcateStudy+1)*(_Bins_HadronicResolutionBifurcateStudy+1));
    }
    
    // define map histograms, often number of bins is sqrt(# of grids)
    _histos.th1d("smeared_histd1map_HadronicResolutionBifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicResolutionBifurcateStudy, 
										       _Relsampling_HAD_bifurcate_A_center-(_Bins_HadronicResolutionBifurcateStudy/2)*_Relsampling_HAD_bifurcate_A_step, 
										       _Relsampling_HAD_bifurcate_A_center+(_Bins_HadronicResolutionBifurcateStudy/2)*_Relsampling_HAD_bifurcate_A_step );
    _histos.th1d("smeared_histd2map_HadronicResolutionBifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicResolutionBifurcateStudy, 
										       _Relsampling_HAD_bifurcate_B_center-(_Bins_HadronicResolutionBifurcateStudy/2)*_Relsampling_HAD_bifurcate_B_step, 
										       _Relsampling_HAD_bifurcate_B_center+(_Bins_HadronicResolutionBifurcateStudy/2)*_Relsampling_HAD_bifurcate_B_step );
  }

  // histograms for hadronic momentum resolution study for bifurcate method (for hard and soft components)
  if(_HadronicMomentumResolution2BifurcateStudy) {
    _HadronicTemplateNumber=_MOMENTUM_RESOLUTION_BIFURCATE2_;
    char name[50];
    for(int ibin=0; ibin<10; ibin++) {
      sprintf(name, "%s%d", "smeared_hZcandEtaImBalance_bin_", ibin);
      _histos.clone(name, (_Bins_HadronicResolution2BifurcateStudy+1)*(_Bins_HadronicResolution2BifurcateStudy+1));
    }
    
    // define map histograms, often number of bins is sqrt(# of grids)
    _histos.th1d("smeared_histd1map_HadronicResolution2BifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicResolution2BifurcateStudy, 
											     _Relsampling_HAD_bifurcate2_A_center-(_Bins_HadronicResolution2BifurcateStudy/2)*_Relsampling_HAD_bifurcate2_A_step, 
											     _Relsampling_HAD_bifurcate2_A_center+(_Bins_HadronicResolution2BifurcateStudy/2)*_Relsampling_HAD_bifurcate2_A_step );
    _histos.th1d("smeared_histd2map_HadronicResolution2BifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicResolution2BifurcateStudy, 
											     _alpha_mb2_center-(_Bins_HadronicResolution2BifurcateStudy/2)*_alpha_mb2_step, 
											     _alpha_mb2_center+(_Bins_HadronicResolution2BifurcateStudy/2)*_alpha_mb2_step );
  }


  // histograms for hadronic momentum resolution study for bifurcate method (for hard and soft components)
  if(_HadronicMomentumResolution3BifurcateStudy) {
    _HadronicTemplateNumber=_MOMENTUM_RESOLUTION_BIFURCATE3_;
    char name[50];
    for(int ibin=0; ibin<10; ibin++) {
      sprintf(name, "%s%d", "smeared_hZcandEtaImBalance_bin_", ibin);
      _histos.clone(name, (_Bins_HadronicResolution3BifurcateStudy+1)*(_Bins_HadronicResolution3BifurcateStudy+1)*(_Bins_HadronicResolution3BifurcateStudy+1));
    }
    
    // define map histograms, often number of bins is sqrt(# of grids)
    _histos.th1d("smeared_histd1map_HadronicResolution3BifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicResolution3BifurcateStudy, 
											     _Relsampling_HAD_bifurcate3_A_center-(_Bins_HadronicResolution3BifurcateStudy/2)*_Relsampling_HAD_bifurcate3_A_step, 
											     _Relsampling_HAD_bifurcate3_A_center+(_Bins_HadronicResolution3BifurcateStudy/2)*_Relsampling_HAD_bifurcate3_A_step );
    _histos.th1d("smeared_histd2map_HadronicResolution3BifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicResolution3BifurcateStudy, 
											     _Relsampling_HAD_bifurcate3_B_center-(_Bins_HadronicResolution3BifurcateStudy/2)*_Relsampling_HAD_bifurcate3_B_step, 
											     _Relsampling_HAD_bifurcate3_B_center+(_Bins_HadronicResolution3BifurcateStudy/2)*_Relsampling_HAD_bifurcate3_B_step );
    _histos.th1d("smeared_histd3map_HadronicResolution3BifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicResolution3BifurcateStudy, 
											     _alpha_mb3_center-(_Bins_HadronicResolution3BifurcateStudy/2)*_alpha_mb3_step, 
											     _alpha_mb3_center+(_Bins_HadronicResolution3BifurcateStudy/2)*_alpha_mb3_step );
  }
  
  // histograms for hadronic phi smearing study for bifurcate method
  if(_HadronicPhiSmearingBifurcateStudy) {
    _HadronicTemplateNumber=_PHI_SMEARING_BIFURCATE_;
    char name[50];
    for(int ibin=0; ibin<10; ibin++) {
      sprintf(name, "%s%d", "smeared_hZcandDeltaPhi_Z_Recoil_bin_", ibin);
      _histos.clone(name, (_Bins_HadronicPhiSmearingBifurcateStudy+1)*(_Bins_HadronicPhiSmearingBifurcateStudy+1));
    }
    
    // define map histograms, often number of bins is sqrt(# of grids)
    _histos.th1d("smeared_histd1map_HadronicPhiSmearingBifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicPhiSmearingBifurcateStudy, 
											     _Relphi_HAD_bifurcate_A_center-(_Bins_HadronicPhiSmearingBifurcateStudy/2)*_Relphi_HAD_bifurcate_A_step, 
											     _Relphi_HAD_bifurcate_A_center+(_Bins_HadronicPhiSmearingBifurcateStudy/2)*_Relphi_HAD_bifurcate_A_step );
    _histos.th1d("smeared_histd2map_HadronicPhiSmearingBifurcateTemplates")->GetXaxis()->Set(_Bins_HadronicPhiSmearingBifurcateStudy, 
											     _Relphi_HAD_bifurcate_B_center-(_Bins_HadronicPhiSmearingBifurcateStudy/2)*_Relphi_HAD_bifurcate_B_step, 
											     _Relphi_HAD_bifurcate_B_center+(_Bins_HadronicPhiSmearingBifurcateStudy/2)*_Relphi_HAD_bifurcate_B_step );
  }
  //
  // pre-select events fot MINUIT fit
  //
  if(_HadronicMomentum_AllAtOnce_BifurcateStudy) {
    _HadronicTemplateNumber=_MOMENTUM_ALL_AT_ONCE_BIFURCATE_;

    // check if reference histograms do exist
    TFile *file_ref= new TFile(_Zminuit_Reference_FileName.Data(), "OLD");
    if(!file_ref) {
      cout<<"ZAnalysis: Can't open reference file named: " << _Zminuit_Reference_FileName << endl;
      throw;
    }
    file_ref->cd(_Zminuit_Reference_Dir.Data());
    for(int ibin=0; ibin<10; ibin++) {
      char name1[50], name2[50], name3[50];
      sprintf(name1,"%s%d", _Zminuit_Reference_Prefix_Phi.Data(), ibin);
      sprintf(name2,"%s%d", _Zminuit_Reference_Prefix_EtaImbalance.Data(), ibin);
      sprintf(name3,"%s%d", _Zminuit_Reference_Prefix_XiImbalance.Data(), ibin);
      if ( (TH1D*)gROOT->FindObject(name1) == NULL ||
	   (TH1D*)gROOT->FindObject(name2) == NULL ||
	   (TH1D*)gROOT->FindObject(name3) == NULL  ) {
 	cout<<"ZAnalysis: At least one reference histogram for MINUIT is missing for PT-bin "<< ibin << " !!!" << endl;
	throw;
      }
    }
    if(_Zminuit_ChiSquare_Method <0 || _Zminuit_ChiSquare_Method>10) {
      cout<<"ZAnalysis: CHI2 method for MINUIT must be between 0 and 10 !!!" << endl;
      throw;
    }
    file_ref->Close();
    delete file_ref;

    // create a new binary file for event buffering
    if(!_Zminuit_Skip_Event_Preselection) {
      _Zminuit_EventBuffer_File = fopen(_Zminuit_EventBuffer_FileName.Data(), "wb");
      if(!_Zminuit_EventBuffer_File) {
	cout<<"ZAnalysis: Can't open event buffer file named: " << _Zminuit_EventBuffer_FileName << endl;
	throw;
      }
    }
    _Zminuit_EventBuffer_Nevts=0;
    _Zminuit_RAMBuffer = NULL;
    _Zminuit_RAMBuffer_Nevts = 0;
    _Zminuit_RAMBuffer_Ready = false;

    // clone some histograms
    char name1[50];
    char name2[50];
    for(int ibin=0; ibin<10; ibin++) {
      sprintf(name1, "%s%d", "smeared_hZcandEtaImBalance_bin_", ibin);
      sprintf(name2, "%s%d", "minuit_hZcandEtaImBalance_bin_", ibin);
      _histos.clone(name1, name2);
      sprintf(name1, "%s%d", "smeared_hZcandXiImBalance_bin_", ibin);
      sprintf(name2, "%s%d", "minuit_hZcandXiImBalance_bin_", ibin);
      _histos.clone(name1, name2);
      sprintf(name1, "%s%d", "smeared_hZcandDeltaPhi_Z_Recoil_bin_", ibin);
      sprintf(name2, "%s%d", "minuit_hZcandDeltaPhi_Z_Recoil_bin_", ibin);
      _histos.clone(name1, name2);
    }
  }
  //
  // generate invariant mass distributions for different mass points
  //
  if(_zmass_reweight) {
    _histos.clone("smeared_hZcandMass_All_Mass", 100);
    _histos.clone("smeared_hZcandMass_CCCC_Mass", 100);
    _histos.clone("smeared_hZcandMass_CCEC_Mass", 100);
    _histos.clone("smeared_hZcandMass_ECEC_Mass", 100);
    if(_zmass_elecpt_reweight){
      _histos.clone("smeared_hZcandElecPtBoth_CCCC_Mass", 100);
      _histos.clone("smeared_hZcandElecPt1_CCCC_Mass", 100);
      _histos.clone("smeared_hZcandElecPt2_CCCC_Mass", 100);
      
      _histos.clone("smeared_hZcandMtBoth_CC_Mass", 100);
      _histos.clone("smeared_hZcandMt1_CC_Mass", 100);
      _histos.clone("smeared_hZcandMt2_CC_Mass", 100);
      
    }
    // define map histograms, often number of bins is sqrt(# of grids)
    _histos.th1d("smeared_histd1map_ZMassTemplates")->GetXaxis()->Set(99, _zmass_default-50*_zmass_step, _zmass_default+49*_zmass_step );
  }

  // use square root of sum of weights
  _histos.SumWeight();


  if (_makeROOTfile_for_ZFIT || _makegenROOTfile_for_ZFIT) {
    Zfitfile = new TFile("Zfittree.root","recreate");
    Zfittree = new TTree("Zfittree","Z fit tree");
    
    Zfittree->Branch("Zfitdata",&zfit_data.mass_Z_gen,"mass_Z_gen/D:mass_Z_smear/D:elec_E[2]/D:elec_px[2]/D:elec_py[2]/D:elec_pz[2]/D:elec_deteta[2]/D:elec_id[2]/D:gen_elec_E[2]/D:gen_elec_px[2]/D:gen_elec_py[2]/D:gen_elec_pz[2]/D:event_weight/D:RecoilX_gen/D:RecoilY_gen/D:metX_FromMB/D:metY_FromMB/D:met_x/D:met_y/D:Trig_Ver/D:RecoilX/D:RecoilY/D:effFlag/D:lumi/D:elec_upara[2]/D:elec_leakage[2]/D:elec_ZBdiff[2]/D:elec_peta[2]/D:vtxZ/D:elec_detphi[2]/D:ScalarEt/D");
  }//if make Z fit file

  if (_makeASCIIfile_for_detector) {
    _theASCIIfile = new std::fstream("ascii_for_detector.txt",std::ios::out);
  }

  //MW
  // for making a table of average leakage outside electron cone as a function of eta (for recoil library method)
  if(_MakeEleakTable){

    _LeakSum = new double[_NleakBins];
    _LeakCount = new double[_NleakBins];

    _overallLeakSum=0; _overallLeakCount=0;

    for(int i=0; i<_NleakBins; i++){ _LeakSum[i]=0; _LeakCount[i]=0; }
  }
 
  if(_createRootTree2) {
  _roottupleFile2 = new TFile("ZRootTree2.root", "recreate");
    _tree2 = new TTree("ZTree2", "");
    _tree2->Branch("ZBrunNum", &tree2_ZBrunnum, "ZBrunNum/I");
    _tree2->Branch("ZBeventNum", &tree2_ZBeventnum, "ZBeventNum/I");
    _tree2->Branch("Mz", &tree2_Mz, "Mz/F");
    _tree2->Branch("Ptz", &tree2_Ptz, "Ptz/F");
    _tree2->Branch("Luminosity", &tree2_lumi, "Luminosity/F");
    _tree2->Branch("ScalarEt", &tree2_set, "ScalarEt/F");
    _tree2->Branch("ZUt", &tree2_ZUt, "ZUt/F");
    _tree2->Branch("em_e", &tree2em_e[0], "em_e[2]/F");
    _tree2->Branch("em_pt", &tree2em_pt[0], "em_pt[2]/F");
    _tree2->Branch("em_eta", &tree2em_eta[0], "em_eta[2]/F");
    _tree2->Branch("em_phi", &tree2em_phi[0], "em_phi[2]/F");
    _tree2->Branch("em_deteta", &tree2em_deteta[0], "em_deteta[2]/F");
    _tree2->Branch("em_detphi", &tree2em_detphi[0], "em_detphi[2]/F");
    _tree2->Branch("em_upara", &tree2em_upara[0], "em_upara[2]/F");
    _tree2->Branch("em_trk_prob", &tree2em_trk_prob[0], "em_trk_prob[2]/I");
    _tree2->Branch("em_trk_nsmt", &tree2em_nsmt[0], "em_trk_nsmt[2]/I");
    _tree2->Branch("em_trk_pt", &tree2em_trk_pt[0], "em_trk_pt[2]/F");
    _tree2->Branch("em_hmX", &tree2em_hmX[0], "em_hmX[2]/I");
    _tree2->Branch("weight", &tree2_weight, "weight/F");

    _tree2->Branch("type", &tree2_type, "type/I");
    _tree2->Branch("vtxz", &tree2_vtxz, "vtxz/F");

    _tree2->Branch("em_trkphiem3", &tree2em_trkphiem3[0], "em_trkphiem3[2]/F");

    _tree2->Branch("em_trk_probtight", &tree2em_trk_probtight[0], "em_trk_probtight[2]/I");
    _tree2->Branch("em_trk_set", &tree2em_trk_set[0], "em_trk_set[2]/I");
    _tree2->Branch("em_trk_upara", &tree2em_trk_upara[0], "em_trk_upara[2]/I");
    _tree2->Branch("passesnonuparaeff", &tree2_passesnonuparaeff, "passesnonuparaeff/I");
    _tree2->Branch("em_trk_trig", &tree2em_trk_trig[0], "em_trk_trig[2]/I");
    
    _tree2->Branch("em_trk_presel", &tree2em_trk_presel[0], "em_trk_presel[2]/I");
    _tree2->Branch("em_trk_addon", &tree2em_trk_addon[0], "em_trk_addon[2]/I");
    _tree2->Branch("em_cc", &tree2em_cc[0], "em_cc[2]/I");
    _tree2->Branch("em_fid", &tree2em_fid[0], "em_fid[2]/I");
  }


}

// read parameters
void ZAnalysis::ReadParameters(TString parameter_filename) {


  PParameterReader parm(parameter_filename.Data());  

  _createRootTree2 = parm.GetBool("createRootTree2", false);
  _debug = parm.GetBool("debug", kFALSE);
  _makeU_parControlPlot = parm.GetBool("MakeU_parControlPlot", kFALSE); 
  _makeU_parControlPlot_RequestBothPtCut = true;
  if (_makeU_parControlPlot) {
    _makeU_parControlPlot_RequestBothPtCut = parm.GetBool("MakeU_parControlPlot_RequestBothPtCut", kTRUE); 
  }
  _Top_Bottom_Effect_Correction = parm.GetBool("TBCorrection", kFALSE);
  _TB_Correction_Option = parm.GetInt("TBCorrection_Option", 2);
  _Top_Bottom_Apply_Last = parm.GetBool("TBApplyLast", kFALSE);
  _TBPhi_response_Hard_Only = parm.GetBool("TBPhi_response_Hard_Only", kFALSE);
  _TBPhi_response_Soft_Only = parm.GetBool("TBPhi_response_Soft_Only", kFALSE);
  // use tag probe method to study efficiency
  _StudyEfficiencies = parm.GetBool("StudyEfficiencies", kFALSE);
  _StudyEfficiencyBIASES = parm.GetBool("StudyEfficiencyBIASES", kFALSE);

  //
  _StudyEfficienciesTruth = parm.GetBool("StudyEfficienciesTruth", kFALSE);
  _TruthMode = parm.GetInt("TruthMode", 2);
  if (_StudyEfficienciesTruth) cout<<"Truth mode: "<<_TruthMode<<endl;
  //use to bin in phimod without phimod cuts
  _StudyPhiMod =  parm.GetBool("StudyPhiMod", kFALSE);
  _phimodcut=true;
  _ApplyTrkPhiModCut = parm.GetBool("TrkPhiModEfficiency");
  if (_StudyPhiMod) _phimodcut = false;
  // optional output file containing 
  _makeROOTfile_for_ZFIT = parm.GetBool("makeROOTfile_for_ZFIT");
  _makegenROOTfile_for_ZFIT = parm.GetBool("makegenROOTfile_for_ZFIT");

  // optional output file for detector studies
  _makeASCIIfile_for_detector = parm.GetBool("makeASCIIfile_for_detector");

  // optional ASCII printouts
  _makeASCIIfile_LumiEff = parm.GetBool("makeASCIIfile_LumiEff");
  _makeASCIIfile_Eresponse = parm.GetBool("makeASCIIfile_Eresponse");

  // output file
  _zeefilename = parm.GetChar("output_file_zee");

  //whether to make generator-level plots
  _makeZGenPlots = parm.GetBool("makeZGenPlots", kFALSE);

  // track pT cut
  _trkpTCut = parm.GetFloat("trkpTCut", 10.);

  //fz study 
  _doFzStudy = parm.GetBool("doFzStudy", kFALSE);
  
  //Overlay Eventlist
  _MakeOverlayEventList = parm.GetBool("MakeOverlayEventList", kFALSE);

  // for reweighting
  _zmass_reweight = parm.GetBool("zmass_reweight", kTRUE);
  _zmass_elecpt_reweight = parm.GetBool("zmass_elecpt_reweight", kTRUE);
  _zmass_default = parm.GetFloat("zmass_default", 91.0);
  _zwidth_default = parm.GetFloat("zwidth_default", 2.1);
  _zmass_step = parm.GetFloat("zmass_step", 0.050);

  // Efficiency correction
  _ZtrigEffCorrection = parm.GetBool("ZtrigEffCorrection", kFALSE);
  _ZpreselEffCorrection = parm.GetBool("ZpreselEffCorrection", kFALSE);
  _ZIDEffCorrection = parm.GetBool("ZIDEffCorrection", kFALSE);
 
  //Cut on ZB Triggers 'Turned On'
  _TrigSelector = parm.GetInt("TriggerSelector", 0);

  // uparallel correction
  _ZUparaCorrection = parm.GetBool("ZUparaCorrection", kFALSE);
  _PlotUparaOverPte = parm.GetBool("PlotUparaOverPte", kFALSE);
  _PlotCosUphi = parm.GetBool("PlotCosUphi", kFALSE);



  // uparallel efficiency correction
  _UseUparaOverPte  = parm.GetBool("UseUparaOverPte", kFALSE);
  _UseCosUphi  = parm.GetBool("UseCosUphi", kFALSE);
  _ZUparaEffCorrection = parm.GetBool("ZUparaEffCorrection", kTRUE);
  _UparaEffCorrOption = parm.GetInt("UparaEffCorrOption", 1);
  _ZUparaEffParameters = parm.GetVDouble("ZUparaEffCorrParameters_CC");

  // Hengne's tests
  _ZUparaEffCorrHengne = parm.GetBool("ZUparaEffCorrHengne", kFALSE);
  if (_ZUparaEffCorrHengne){
    _ZUparaEffCorrHengneOption = parm.GetInt("ZUparaEffCorrHengneOption", 0);
    if (_ZUparaEffCorrHengneOption==0||_ZUparaEffCorrHengneOption==1) { 
      TFile* fupeHengne = new TFile(parm.GetChar("ZUparaEffCorrHengneFile"));
      if (_ZUparaEffCorrHengneOption==0) {
        _ZUparaEffCorrHengne_hUParaUPerpEFRT = (TH1D*)fupeHengne->Get("hUParaUPerpEFRT");
      }
      else if (_ZUparaEffCorrHengneOption==1){
        _ZUparaEffCorrHengne_hUTUPhiEFRT = (TH1D*)fupeHengne->Get("hUTUPhiEFRT");
      }
    }
    else if (_ZUparaEffCorrHengneOption==2){
      _ZUparaEffCorrHengne_Opt2Pars = parm.GetVDouble("ZUparaEffCorrHengne_Opt2Pars");
    }
    
  }

  _Z_u0_CC = parm.GetFloat("Z_u0_CC", 3.29440);
  _Z_s_CC = parm.GetFloat("Z_s_CC", 0.001787);
  _Z_u0_EC = parm.GetFloat("Z_u0_EC", 2.308);
  _Z_s_EC = parm.GetFloat("Z_s_EC", 0.0046);

  _Z_u0pte_CC = parm.GetFloat("Z_u0pte_CC", 0.0185);
  _Z_spte_CC = parm.GetFloat("Z_spte_CC", 0.0244);
  _Z_u1pte_CC = parm.GetFloat("Z_u1pte_CC", 0.43);
  _Z_u0pte_EC = parm.GetFloat("Z_u0pte_EC", 0.0185);
  _Z_spte_EC = parm.GetFloat("Z_spte_EC", 0.0244);

  _Z_u0phi_CC = parm.GetFloat("Z_u0phi_CC", 0.0185);
  _Z_sphi_CC = parm.GetFloat("Z_sphi_CC", 0.0244);
  _Z_u1phi_CC = parm.GetFloat("Z_u1phi_CC", 0.43);
  _Z_u0phi_EC = parm.GetFloat("Z_u0phi_EC", 0.0185);
  _Z_sphi_EC = parm.GetFloat("Z_sphi_EC", 0.0244);

  // FSR photons in cracks
  _ZsimuFSRcracks = parm.GetBool("ZsimuFSRcracks", kFALSE);
  _ZsimuFSRcracksWidth = parm.GetFloat("ZsimuFSRcracksWidth", 0.05);

  // SET efficiency
  _ZSETEffCorrection = parm.GetBool("ZSETEffCorrection", kFALSE);
  _ZSETEffCorrLumiSplit = parm.GetBool("ZSETEffCorrLumiSplit", kFALSE);
  if (_ZSETEffCorrLumiSplit) {
    _ZSETEffCorrLumiSplit_Bins = parm.GetVFloat("ZSETEffCorrLumiSplit_Bins");
    _ZSETEffCorrLumiSplit_NormCCCC = parm.GetVFloat("ZSETEffCorrLumiSplit_NormCCCC");
    _ZSETEffCorrLumiSplit_NormCCEC = parm.GetVFloat("ZSETEffCorrLumiSplit_NormCCEC");
    _ZSETEffCorrLumiSplit_NormECEC = parm.GetVFloat("ZSETEffCorrLumiSplit_NormECEC");
    assert((_ZSETEffCorrLumiSplit_Bins.size()+1)==_ZSETEffCorrLumiSplit_NormCCCC.size());
    assert((_ZSETEffCorrLumiSplit_Bins.size()+1)==_ZSETEffCorrLumiSplit_NormCCEC.size());
    assert((_ZSETEffCorrLumiSplit_Bins.size()+1)==_ZSETEffCorrLumiSplit_NormECEC.size());
  }
  _ZSETEffCorrScaled = parm.GetBool("ZSETEffCorrScaled", kFALSE);
  _ZSETEffCorrRelative = parm.GetBool("ZSETEffCorrRelative", kFALSE);
  _ZSETEffCorrScale=200.;
  if (_ZSETEffCorrRelative) _ZSETEffCorrScale=20.;
  _ZSETEffCorrInterpolate = parm.GetBool("ZSETEffCorrInterpolate", kFALSE);
  _ZSETEffCorrParametersCCCC = parm.GetVFloat("ZSETEffCorrParametersCCCC");
  _ZSETEffCorrParametersCCEC = parm.GetVFloat("ZSETEffCorrParametersCCEC");
  _ZSETEffCorrParametersECEC = parm.GetVFloat("ZSETEffCorrParametersECEC");
  //
  _ZSETEffCorrPTEpert = parm.GetInt("ZSETEffCorrPTEpert", 0);
  //
  if (_ZSETEffCorrPTEpert==1||_ZSETEffCorrPTEpert==2) {
    _ZSETEffCorrPTEpertBase = parm.GetVFloat("ZSETEffCorrPTEpertBase");
    _ZSETEffCorrPTEpertA = parm.GetVFloat("ZSETEffCorrPTEpertA");
    _ZSETEffCorrPTEpertB = parm.GetVFloat("ZSETEffCorrPTEpertB");
    _ZSETEffCorrPTEpertC = parm.GetVFloat("ZSETEffCorrPTEpertC");
    _ZSETEffCorrPTEpertD = parm.GetVFloat("ZSETEffCorrPTEpertD");
    _ZSETEffCorrPTEpertE = parm.GetVFloat("ZSETEffCorrPTEpertE");
    _ZSETEffCorrPTEpertF = parm.GetVFloat("ZSETEffCorrPTEpertF");
    _ZSETEffCorrPTEpertG = parm.GetVFloat("ZSETEffCorrPTEpertG");
    _ZSETEffCorrPTEpertH = parm.GetVFloat("ZSETEffCorrPTEpertH");
    _ZSETEffCorrPTEpertNorm = parm.GetVFloat("ZSETEffCorrPTEpertNorm");
  } else if (_ZSETEffCorrPTEpert==3) {
    _ZSETEffCorrPTEupara = parm.GetInt("ZSETEffCorrPTEupara", 0);
    for (int i=0; i<5; i++) {
      TString n;
      n="ZSETEffCorrPTEpertBase_";
      n+=i;
      _ZSETEffCorrEPTEpertBase.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertA_";
      n+=i;
      _ZSETEffCorrEPTEpertA.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertB_";
      n+=i;
      _ZSETEffCorrEPTEpertB.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertC_";
      n+=i;
      _ZSETEffCorrEPTEpertC.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertD_";
      n+=i;
      _ZSETEffCorrEPTEpertD.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertE_";
      n+=i;
      _ZSETEffCorrEPTEpertE.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertF_";
      n+=i;
      _ZSETEffCorrEPTEpertF.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertG_";
      n+=i;
      _ZSETEffCorrEPTEpertG.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertH_";
      n+=i;
      _ZSETEffCorrEPTEpertH.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertNorm_";
      n+=i;
      _ZSETEffCorrEPTEpertNorm.push_back(parm.GetVFloat(n.Data()));
    }
    if (_ZSETEffCorrPTEupara==1) {
      for (int i=0; i<5; i++) {
        TString n;
        n="ZSETEffCorrPTEpertBase_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertBase.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertA_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertA.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertB_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertB.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertC.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertD_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertD.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertE_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertE.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertF_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertF.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertG_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertG.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertH_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertH.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertNorm_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertNorm.push_back(parm.GetVFloat(n.Data()));
      }
      //
      _ZSETEffCorrEPTEparamsNorm_CommonMultiplier=parm.GetVFloat("ZSETEffCorrEPTEparamsNorm_CommonMultiplier");
      _ZSETEffCorrPTEpertRelGlobNorm=parm.GetFloat("ZSETEffCorrPTEpertRelGlobNorm");
    }
  }
  _useHack = parm.GetInt("SETuseHack");
  _useLumiBins = parm.GetBool("SETuseLumiBins");
  if (_useHack && _useHack<=2){
    char name[100];
    for (Int_t tv=0; tv<7; ++tv){
      std::vector< std::vector<float> >  _tempvec1;
      std::vector< std::vector<float> >  _tempvec2;
      for (Int_t tg=0; tg<7; ++tg){
	
	sprintf(name,"SETEffCorrDataRatioParametersBin%1d_%1d",tv,tg);
	if (tv==6)
	  sprintf(name,"SETEffCorrDataRatioParametersBin_%1d",tg);
	_tempvec1.push_back(parm.GetVFloat(name));
	sprintf(name,"SETEffCorrDataRatioParameters2Bin%1d_%1d",tv,tg);
	if (tv==6)
	  sprintf(name,"SETEffCorrDataRatioParameters2Bin_%1d",tg);
	_tempvec2.push_back(parm.GetVFloat(name));
      }
      _ZSETEffCorrDataRatioParameters.push_back(_tempvec1);
      _ZSETEffCorrDataRatioParameters2.push_back(_tempvec2);
      _tempvec1.clear();
      _tempvec2.clear();
      //
      if (_useHack==2) {
	_ZSETEffCorrDataRatioPTFit = parm.GetVFloat("ZSETEffCorrDataRatioPTFit");
	_ZSETEffCorrDataRatioLumiFit = parm.GetVFloat("ZSETEffCorrDataRatioLumiFit");
      }
    }
  }
  if (_useHack==3){
    _ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackPtDepParameters"));

    if(parm.GetBool("Run3")) {
      _ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackSETDepParameters3"));
      _ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackLumiDepParameters3"));
    } else if(parm.GetBool("Run4")) {
      _ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackSETDepParameters4"));
      _ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackLumiDepParameters4"));
    }

    _ZSETEffDataHackParameters.push_back(parm.GetVFloat("SETEffDataHackDetEtaDepParameters"));
  }
  //
  if (_ZSETEffCorrPTEpert==1||_ZSETEffCorrPTEpert==2) {
    _ZSETEffCorrPTEpertBase_EC = parm.GetVFloat("ZSETEffCorrPTEpertBase_EC");
    _ZSETEffCorrPTEpertA_EC = parm.GetVFloat("ZSETEffCorrPTEpertA_EC");
    _ZSETEffCorrPTEpertB_EC = parm.GetVFloat("ZSETEffCorrPTEpertB_EC");
    _ZSETEffCorrPTEpertC_EC = parm.GetVFloat("ZSETEffCorrPTEpertC_EC");
    _ZSETEffCorrPTEpertD_EC = parm.GetVFloat("ZSETEffCorrPTEpertD_EC");
    _ZSETEffCorrPTEpertE_EC = parm.GetVFloat("ZSETEffCorrPTEpertE_EC");
    _ZSETEffCorrPTEpertF_EC = parm.GetVFloat("ZSETEffCorrPTEpertF_EC");
    _ZSETEffCorrPTEpertG_EC = parm.GetVFloat("ZSETEffCorrPTEpertG_EC");
    _ZSETEffCorrPTEpertH_EC = parm.GetVFloat("ZSETEffCorrPTEpertH_EC");
    _ZSETEffCorrPTEpertNorm_EC = parm.GetVFloat("ZSETEffCorrPTEpertNorm_EC");
  } else if (_ZSETEffCorrPTEpert==3) {
    for (int i=0; i<5; i++) {
      TString n;
      n="ZSETEffCorrPTEpertBase_EC_";
      n+=i;
      _ZSETEffCorrEPTEpertBase_EC.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertA_EC_";
      n+=i;
      _ZSETEffCorrEPTEpertA_EC.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertB_EC_";
      n+=i;
      _ZSETEffCorrEPTEpertB_EC.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertC_EC_";
      n+=i;
      _ZSETEffCorrEPTEpertC_EC.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertD_EC_";
      n+=i;
      _ZSETEffCorrEPTEpertD_EC.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertE_EC_";
      n+=i;
      _ZSETEffCorrEPTEpertE_EC.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertF_EC_";
      n+=i;
      _ZSETEffCorrEPTEpertF_EC.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertG_EC_";
      n+=i;
      _ZSETEffCorrEPTEpertG_EC.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertH_EC_";
      n+=i;
      _ZSETEffCorrEPTEpertH_EC.push_back(parm.GetVFloat(n.Data()));
      n="ZSETEffCorrPTEpertNorm_EC_";
      n+=i;
      _ZSETEffCorrEPTEpertNorm_EC.push_back(parm.GetVFloat(n.Data()));
    }
    if (_ZSETEffCorrPTEupara==1) {
      for (int i=0; i<5; i++) {
        TString n;
        n="ZSETEffCorrPTEpertBase_EC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertBase_EC.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertA_EC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertA_EC.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertB_EC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertB_EC.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertC_EC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertC_EC.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertD_EC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertD_EC.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertE_EC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertE_EC.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertF_EC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertF_EC.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertG_EC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertG_EC.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertH_EC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertH_EC.push_back(parm.GetVFloat(n.Data()));
        n="ZSETEffCorrPTEpertNorm_EC_";
        n+=i;
        n+="b";
        _ZSETEffCorrEPTEpertNorm_EC.push_back(parm.GetVFloat(n.Data()));
      }
      //
      _ZSETEffCorrPTEpertRelGlobNorm_EC=parm.GetFloat("ZSETEffCorrPTEpertRelGlobNorm_EC");  
    }
  }

  // for pT-dependent efficiencies
  _eff_ratios_Z_includeECtag = parm.GetBool("eff_ratios_Z_includeECtag", kFALSE);

  //Cut out tails of EtaImBalance Distributions
  _etaImbalance_perbincuts  = parm.GetBool("etaImbalance_perbincuts", kFALSE);
  _InvertetaImbalance_perbincuts  = parm.GetBool("InvertetaImbalance_perbincuts", kFALSE);
  _EtaImbalanceCutLow = parm.GetVFloat("EtaImbalanceCutLow");
  _EtaImbalanceCutHigh = parm.GetVFloat("EtaImbalanceCutHigh");
  
  // # of electrons with track matching
  _NZTrkMatch = parm.GetInt("NZTrkMatch", 1);
  _NZpreselTrkMatch = parm.GetInt("NZpreselTrkMatch", 1);
  _ZElecPhiEffCorrection = parm.GetBool("ZElecPhiEffCorrection", kFALSE);
  _ZElecPhiEffCorrectionUseDetPhi = parm.GetBool("ZElecPhiEffCorrectionUseDetPhi", kFALSE);

  // Apply AddOnEff for Zee
  _ApplyAddOnEff_Zee = parm.GetBool("ApplyAddOnEff_Zee", false);
  
  // electron and Z boson pT cut
  _CutEPT1_lo = parm.GetFloat("CutEPT1_LO", 25.);
  _CutEPT2_lo = parm.GetFloat("CutEPT2_LO", 25.);
  _CutEPT1_hi = parm.GetFloat("CutEPT1_HI", 1000.);
  _CutEPT2_hi = parm.GetFloat("CutEPT2_HI", 1000.);

  // if we set make_recoil_file to true, _CutZUT will be set to very large value, means no Ut cut applied
  _CutZUT = parm.GetFloat("CutZUT", 15.);
  _CutZUT_lower = parm.GetFloat("CutZUT_lower", 0.);
  _CutZPT = parm.GetFloat("CutZPT", 9999999.);
  _CutZPT_lower = parm.GetFloat("CutZPT_lower", 0.);
  _CutZPhi = parm.GetFloat("CutZPhi", 7.);
  _CutZPhi_lower = parm.GetFloat("CutZPhi_lower", 0.);
  _CutZScalarEt = parm.GetFloat("CutZScalarEt", 100000.);
  _CutZScalarEt_lower = parm.GetFloat("CutZScalarEt_lower", 0.);
  if(_CutZUT<_CutZUT_lower) {
     cout<<"ZAnalysis: CutZUT="<<_CutZUT<<" < "
             <<"Cut_ZUT_lower="<<_CutZUT_lower<<" !!! "<<endl;
    throw;
  }
  if(_CutZScalarEt<_CutZScalarEt_lower) {
     cout<<"ZAnalysis: CutZScalarEt="<<_CutZScalarEt<<" < "
             <<"CutZScalarEt_lower="<<_CutZScalarEt_lower<<" !!! "<<endl;
    throw;
  }

  // eta cut
  _CutEtaCC = parm.GetFloat("CutEtaCC", 1.05);
  _CutEtaEC1 = parm.GetFloat("CutEtaECLow", 1.5);
  _CutEtaEC2 = parm.GetFloat("CutEtaECHigh", 2.5);

  // vary cut values and check the consistency of W mass
  _consistency_check = parm.GetBool("consistency_check", kFALSE);
  _invert_cut = parm.GetBool("invert_cut", kFALSE);
  _cut_under_study = (TString)(parm.GetChar("cut_under_study", ""));
  
  _runNo_lowcut = parm.GetInt("runNo_lowcut", 0);
  _runNo_highcut = parm.GetInt("runNo_highcut", 0);
  _InstLumi_lowcut = parm.GetFloat("InstLumi_lowcut", 0.);
  _InstLumi_highcut = parm.GetFloat("InstLumi_highcut", 0.);
  _ScalarEt_lowcut = parm.GetFloat("ScalarEt_lowcut", 0.);
  _ScalarEt_highcut = parm.GetFloat("ScalarEt_highcut", 0.);
  _UPara_lowcut = parm.GetFloat("UPara_lowcut", 0.);
  _UPara_highcut = parm.GetFloat("UPara_highcut", 0.);
  _ElecEta_cut = parm.GetFloat("ElecEta_cut", 0.);
  _ElecDetEta_lowcut = parm.GetFloat("ElecDetEta_lowcut", 0.);
  _ElecDetEta_highcut = parm.GetFloat("ElecDetEta_highcut", 0.);
  _ElecPhiMod_cut = parm.GetFloat("ElecPhiMod_cut", 0.);
  _ElecPt_lowcut = parm.GetFloat("ElecPt_lowcut", 0.);
  _ElecPt_highcut = parm.GetFloat("ElecPt_highcut", 0.);
  _ElecPhi_lowcut = parm.GetFloat("ElecPhi_lowcut", 0.);
  _ElecPhi_highcut = parm.GetFloat("ElecPhi_highcut", 0.);
  _RecoilPhi_lowcut = parm.GetFloat("RecoilPhi_lowcut", 0.);
  _RecoilPhi_highcut = parm.GetFloat("RecoilPhi_highcut", 0.);
  _DetEtaCateg_cut = parm.GetInt("DetEtaCateg_cut", 0);

  // Z mass cut
  _ZMassCut1 = parm.GetFloat("ZMassCut1", 70.);
  _ZMassCut2 = parm.GetFloat("ZMassCut2", 110.);

  // writeout Z boson recoil pT into a text file
  _make_recoil_file = parm.GetBool("make_recoil_file", kFALSE);
  if(_make_recoil_file) {
    _CutZUT = 100000.;
    _CutZUT_lower = 0.;
    _CutZScalarEt = 100000.;
    _CutZScalarEt_lower = 0.;
    cout<<"ZAnalysis: Since make_recoil_file=TRUE "
             <<"all cuts on UT are void"<<endl;
    if( use_old_ascii_files ) {
       _RecoilPtASCIIfile = new std::fstream("ascii_recoil_file.txt",std::ios::out);
    }
    else {
      TDirectory * curdir = gDirectory;
      _RecoilFile = new TFile( "recoil_file_zee.root","recreate");
      _RecoilTree = new TTree( "RecoilTree" , "RecoilTree" );
      std::string recoil_block = "pTZ_gen_x/D:pTZ_gen_y/D:pTZ_smear_x/D:pTZ_smear_y/D:recoil_x/D:recoil_y/D:recoil_uncorr_x/D:recoil_uncorr_y/D:recoil_constcorr_x/D:recoil_constcorr_y/D:recoil_paramcorr_x/D:recoil_paramcorr_y/D:recoil_paramconecorr_x/D:recoil_paramconecorr_y/D:scalarET/D:upara_e1/D:upara_e2/D:pT_e1/D:pT_e2/D:eta_e1/D:eta_e2/D:runno/I:lumi/D:MZ/D:type/I:eventweight/D:isFSR/I:photpT1/D:photpT2/D";
      _RecoilTree->Branch( "RecoilData" , &recoil_data.pTZ_gen_x , recoil_block.c_str() );
      curdir->cd();
    }
  }

  // MW
  // make a table of energy leakage versus eta bin (for unfolding)
  _MakeEleakTable = parm.GetBool("MakeEleakTable", kFALSE);
  _NleakBins = parm.GetInt("NleakBins", 14);


  //determine the Top-Bottom Asymmetry
  _TBStudy =  parm.GetBool("TBStudy", kFALSE);
  _tbalpha_center = parm.GetFloat("tb_alpha_center", 1.0);
  _tbbeta_center = parm.GetFloat("tb_beta_center", 0.0);
  _tbalpha_step = parm.GetFloat("tbalpha_step", 0.0002);
  _tbbeta_step = parm.GetFloat("tbbeta_step", 0.2);
  _Bins_TBStudy = parm.GetInt("Bins_TBStudy", 20);


  //determine tracking momentum scale
  _momentumScaleStudy = parm.GetBool("trkmomStudy", kFALSE);
  _Bins_CCMSStudy = parm.GetInt("Bins_CCMSStudy",1);
  _CCMScenterA    = parm.GetFloat("CCMScenterA", 0.);
  _CCMScenterB    = parm.GetFloat("CCMScenterB", 0.);
  _CCMScenterC    = parm.GetFloat("CCMScenterC", 0.);
  _CCMSstepA      = parm.GetFloat("CCMSstepA", 0.);
  _CCMSstepB      = parm.GetFloat("CCMSstepB", 0.);
  _CCMSstepC      = parm.GetFloat("CCMSstepC", 0.);

  _Bins_ECMSStudy = parm.GetInt("Bins_ECMSStudy",1);
  _ECMScenterA    = parm.GetFloat("ECMScenterA", 0.);
  _ECMScenterB    = parm.GetFloat("ECMScenterB", 0.);
  _ECMScenterB    = parm.GetFloat("ECMScenterC", 0.);
  _ECMSstepA      = parm.GetFloat("ECMSstepA", 0.);
  _ECMSstepB      = parm.GetFloat("ECMSstepB", 0.);
  _ECMSstepC      = parm.GetFloat("ECMSstepC", 0.);
  
  _study_AB = parm.GetBool("StudyAB", kTRUE);
  
  _radLengthStudy = parm.GetBool("radLengthStudy", kFALSE);
  _Bins_radLengthStudy_CC = parm.GetInt("Bins_radLengthStudy_CC", 1);
  _radLengthcenter_CC     = parm.GetFloat("radLengthcenter_CC", 1);
  _radLengthstep_CC      = parm.GetFloat("radLengthstep_CC", 1);
  
  _radLengthStudy_EC = parm.GetBool("radLengthStudy_EC", kFALSE);
  _Bins_radLengthStudy_EC = parm.GetInt("Bins_radLengthStudy_EC", 1);
  _radLengthcenter_EC = parm.GetFloat("radLengthcenter_EC", 1);
  _radLengthstep_EC = parm.GetFloat("radLengthstep_EC", 1);

  //
  _pedanticRandomRecoil = parm.GetBool("pedanticRandomRecoil");
  _pedanticRandomEM = parm.GetBool("pedanticRandomEM");
  // determine electron energy scale
  _EnergyScaleStudy = parm.GetBool("EnergyScaleStudy", kFALSE);
  _EnergyScaleStudyJan = parm.GetBool("EnergyScaleStudyJan", kFALSE);
  _EnergyScaleStudyJanPedantic = parm.GetBool("EnergyScaleStudyJanPedantic", kFALSE);
  _StudyCCScale = parm.GetBool("StudyCCScale", kTRUE);
  _scale_center = parm.GetFloat("scale_center", 1.0);
  _offset_center = parm.GetFloat("offset_center", 0.0);
  _scale_step = parm.GetFloat("scale_step", 0.0002);
  _offset_step = parm.GetFloat("offset_step", 0.2);
  _Bins_ScaleStudy = parm.GetInt("Bins_ScaleStudy", 20);

  // determine electron energy resolution 
  _EnergyResolutionStudy = parm.GetBool("EnergyResolutionStudy", kFALSE);
  _EnergyResolutionStudyJan = parm.GetBool("EnergyResolutionStudyJan", kFALSE);
  _EnergyResolutionStudyJanPedantic = parm.GetBool("EnergyResolutionStudyJanPedantic", kFALSE);
  _StudyCCResolution = parm.GetBool("StudyCCResolution", kTRUE);
  _SkipSampling = parm.GetBool("SkipSampling", kTRUE);
  _SkipConstant = parm.GetBool("SkipConstant", kTRUE);
  _sampling_center = parm.GetFloat("sampling_center", 0.15);
  _constant_center = parm.GetFloat("constant_center", 0.042);
  _sampling_step = parm.GetFloat("sampling_step", 0.005);
  _constant_step = parm.GetFloat("constant_step", 0.01);
  _Bins_ResolutionStudy = parm.GetInt("Bins_ResolutionStudy", 20);
  _SkipeNoise = parm.GetBool("SkipeNoise", kTRUE);
  _enoise_center = parm.GetDouble("enoise_center", 0.15);
  _enoise_step = parm.GetDouble("enoise_step", 0.005);

 
  // determine Crystal Ball parameters for electron energy resolution near phi-cracks
  // (or PeakShift parameters for response near phi-cracks)
  _MakeCrackCBtemplates = parm.GetBool("MakeCrackCBtemplates", kFALSE);
  _CrackCB_alphaOffset_center = parm.GetFloat("CrackCB_alphaOffset_center", 1.5);
  _CrackCB_alphaSlope_center = parm.GetFloat("CrackCB_alphaSlope_center", 7.0);
  _CrackCB_alphaOffset_step = parm.GetFloat("CrackCB_alphaOffset_step",0.05);
  _CrackCB_alphaSlope_step = parm.GetFloat("CrackCB_alphaSlope_step", 0.2);
  _Bins_MakeCrackCBtemplates = parm.GetInt("Bins_MakeCrackCBtemplates", 20);



  // determine hadronic momentum scale
  _HadronicMomentumScaleStudy = parm.GetBool("HadronicMomentumScaleStudy", kFALSE);
  _scale_HAD_A_center = parm.GetFloat("scale_HAD_A_center", 0.7);
  _scale_HAD_B_center = parm.GetFloat("scale_HAD_B_center", 0.);
  _scale_HAD_A_step = parm.GetFloat("scale_HAD_A_step", 0.01);
  _scale_HAD_B_step = parm.GetFloat("scale_HAD_B_step", 0.01);
  _Bins_HadronicScaleStudy = parm.GetInt("Bins_HadronicScaleStudy", 10);

  // determine hadronic momentum sampling term and number of minibas events to overlay
  _HadronicMomentumResolutionStudy = parm.GetBool("HadronicMomentumResolutionStudy", kFALSE);
  _sampling_HAD_center = parm.GetFloat("sampling_HAD_center", 0.8);
  _alpha_mb_center = parm.GetFloat("alpha_mb_center", 0.64);
  _sampling_HAD_step = parm.GetFloat("sampling_HAD_step", 0.1);
  _alpha_mb_step = parm.GetFloat("alpha_mb_step", 0.1);
  _Bins_HadronicResolutionStudy = parm.GetInt("Bins_HadronicResolutionStudy", 10);

  // determine hadronic momentum scale for bifurcate method
  _HadronicMomentumScaleBifurcateStudy = parm.GetBool("HadronicMomentumScaleBifurcateStudy", kFALSE);
  _scale_HAD_bifurcate_A_center = parm.GetFloat("scale_HAD_bifurcate_A_center", 1.);
  _scale_HAD_bifurcate_B_center = parm.GetFloat("scale_HAD_bifurcate_B_center", 0.);
  _scale_HAD_bifurcate_A_step = parm.GetFloat("scale_HAD_bifurcate_A_step", 0.01);
  _scale_HAD_bifurcate_B_step = parm.GetFloat("scale_HAD_bifurcate_B_step", 0.01);
  _Bins_HadronicScaleBifurcateStudy = parm.GetInt("Bins_HadronicScaleBifurcateStudy", 10);

  // determine hadronic momentum scale for bifurcate method
  _HadronicMomentumScale2BifurcateStudy = parm.GetBool("HadronicMomentumScale2BifurcateStudy", kFALSE);
  _scale_HAD_bifurcate2_A_center = parm.GetFloat("scale_HAD_bifurcate2_A_center", 1.);
  _scale_HAD_bifurcate2_B_center = parm.GetFloat("scale_HAD_bifurcate2_B_center", 0.);
  _scale_HAD_bifurcate2_Tau_center = parm.GetFloat("scale_HAD_bifurcate2_Tau_center", 0.);
  _scale_HAD_bifurcate2_A_step = parm.GetFloat("scale_HAD_bifurcate2_A_step", 0.01);
  _scale_HAD_bifurcate2_B_step = parm.GetFloat("scale_HAD_bifurcate2_B_step", 0.01);
  _scale_HAD_bifurcate2_Tau_step = parm.GetFloat("scale_HAD_bifurcate2_Tau_step", 0.01);
  _Bins_HadronicScale2BifurcateStudy = parm.GetInt("Bins_HadronicScale2BifurcateStudy", 10);

  // determine hadronic momentum resolution for bifurcate method (for hard component only)
  _HadronicMomentumResolutionBifurcateStudy = parm.GetBool("HadronicMomentumResolutionBifurcateStudy", kFALSE);
  _Relsampling_HAD_bifurcate_A_center = parm.GetFloat("Relsampling_HAD_bifurcate_A_center", 1.);
  _Relsampling_HAD_bifurcate_B_center = parm.GetFloat("Relsampling_HAD_bifurcate_B_center", 0.);
  _Relsampling_HAD_bifurcate_A_step = parm.GetFloat("Relsampling_HAD_bifurcate_A_step", 0.01);
  _Relsampling_HAD_bifurcate_B_step = parm.GetFloat("Relsampling_HAD_bifurcate_B_step", 0.01);
  _Bins_HadronicResolutionBifurcateStudy = parm.GetInt("Bins_HadronicResolutionBifurcateStudy", 10);

  // determine hadronic momentum resolution for bifurcate method (for hard and soft components)
  _HadronicMomentumResolution2BifurcateStudy = parm.GetBool("HadronicMomentumResolution2BifurcateStudy", kFALSE);
  _Relsampling_HAD_bifurcate2_A_center = parm.GetFloat("Relsampling_HAD_bifurcate2_A_center", 1.);
  _alpha_mb2_center = parm.GetFloat("alpha_mb2_center", 0.);
  _Relsampling_HAD_bifurcate2_A_step = parm.GetFloat("Relsampling_HAD_bifurcate2_A_step", 0.01);
  _alpha_mb2_step = parm.GetFloat("alpha_mb2_step", 0.01);
  _Bins_HadronicResolution2BifurcateStudy = parm.GetInt("Bins_HadronicResolution2BifurcateStudy", 10);

  // determine hadronic momentum resolution for bifurcate method (for hard and soft components)
  _HadronicMomentumResolution3BifurcateStudy = parm.GetBool("HadronicMomentumResolution3BifurcateStudy", kFALSE);
  _Relsampling_HAD_bifurcate3_A_center = parm.GetFloat("Relsampling_HAD_bifurcate3_A_center", 1.);
  _Relsampling_HAD_bifurcate3_B_center = parm.GetFloat("Relsampling_HAD_bifurcate3_B_center", 0.72);
  _alpha_mb3_center = parm.GetFloat("alpha_mb3_center", 0.);
  _Relsampling_HAD_bifurcate3_A_step = parm.GetFloat("Relsampling_HAD_bifurcate3_A_step", 0.01);
  _Relsampling_HAD_bifurcate3_B_step = parm.GetFloat("Relsampling_HAD_bifurcate3_B_step", 0.01);
  _alpha_mb3_step = parm.GetFloat("alpha_mb3_step", 0.01);
  _Bins_HadronicResolution3BifurcateStudy = parm.GetInt("Bins_HadronicResolution3BifurcateStudy", 10);

  // determine hadronic phi smearing for bifurcate method
  _HadronicPhiSmearingBifurcateStudy = parm.GetBool("HadronicPhiSmearingBifurcateStudy", kFALSE);
  _Relphi_HAD_bifurcate_A_center = parm.GetFloat("Relphi_HAD_bifurcate_A_center", 1.);
  _Relphi_HAD_bifurcate_B_center = parm.GetFloat("Relphi_HAD_bifurcate_B_center", 0.);
  _Relphi_HAD_bifurcate_A_step = parm.GetFloat("Relphi_HAD_bifurcate_A_step", 0.01);
  _Relphi_HAD_bifurcate_B_step = parm.GetFloat("Relphi_HAD_bifurcate_B_step", 0.01);
  _Bins_HadronicPhiSmearingBifurcateStudy = parm.GetInt("Bins_HadronicPhiSmearingBifurcateStudy", 10);

  //
  // Pre-select events fot MINUIT fit and store them in output file
  // for later re-processing. During re-processing will compare
  // current Eta Imbalance and Phi Resolution histograms to
  // the user-supplied reference histograms and calculate a total Chi**2
  // for the MINUIT. There are 2 methods of calculating such total Chi**2: 
  // method #0 :  calculate CHI2 as a sum of 3 components:
  //              * sum of differences of MEAN values from 10 eta imbalance histograms,
  //              * sum of differences of RMS values from 10 eta imbalance histograms,
  //              * sum of differences of standard deviations from the expected opening angle
  //              * between true Z and the recoil (Pi) from 10 phi resolution histograms.
  // method #1 :  calculate CHI2 bin-by-bin for all 20 histograms:
  //              * 10 histograms of eta imbalances,
  //              * 10 histograms of phi resolutions.
  //
  _HadronicMomentum_AllAtOnce_BifurcateStudy = parm.GetBool("HadronicMomentum_AllAtOnce_BifurcateStudy", kFALSE);
  //  _Zminuit_maxRAM = parm.GetInt("Zminuit_maxRAM", 1000);
  _Zminuit_Reference_FileName = parm.GetChar("Zminuit_Reference_FileName", "");
  _Zminuit_Reference_Dir = parm.GetChar("Zminuit_Reference_Dir", "ZCand_Hist"); 
  _Zminuit_Reference_Prefix_Phi = parm.GetChar("Zminuit_Reference_Prefix_Phi", "ZCandDeltaPhi_Z_Recoil_bin_"); 
  _Zminuit_Reference_Prefix_EtaImbalance = parm.GetChar("Zminuit_Reference_Prefix_EtaImbalance", "ZCandEtaImBalance_bin_"); 
  _Zminuit_Reference_Prefix_XiImbalance = parm.GetChar("Zminuit_Reference_Prefix_XiImbalance", "ZCandXiImBalance_bin_"); 
  _Zminuit_ChiSquare_Method = parm.GetInt("Zminuit_ChiSquare_Method", 0);
  _Zminuit_Skip_Znunu_Randomization = parm.GetBool("Zminuit_Skip_Znunu_Randomization", kFALSE);
  _Zminuit_Skip_Event_Preselection = parm.GetBool("Zminuit_Skip_Event_Preselection", kFALSE);
  _Zminuit_Skip_Event_Reprocessing = parm.GetBool("Zminuit_Skip_Event_Reprocessing", kFALSE);
  _Zminuit_Skip_UParaEfficiency = parm.GetBool("Zminuit_Skip_UParaEfficiency", kFALSE);
  _Zminuit_Skip_UParaEfficiency_Randomization = parm.GetBool("Zminuit_Skip_UParaEfficiency_Randomization", kFALSE);
  _Zminuit_UseRAM = parm.GetBool("Zminuit_UseRAM", kFALSE);
  _Zminuit_UseGradient = parm.GetBool("Zminuit_UseGradient", kFALSE);
  _Zminuit_EventBuffer_FileName = parm.GetChar("Zminuit_EventBuffer_FileName", "");
  _Zminuit_ProgressReport_FileName = parm.GetChar("Zminuit_ProgressReport_FileName", "");
  _Zminuit_UseMasterSlaveMode = parm.GetBool("Zminuit_UseMasterSlaveMode", kFALSE);
  _Zminuit_MasterSlave_Njobs = parm.GetInt("Zminuit_MasterSlave_Njobs", 1);
  _Zminuit_MasterSlave_Job = parm.GetInt("Zminuit_MasterSlave_Job", 1);
  _Zminuit_MasterSlave_REQ = parm.GetChar("Zminuit_MasterSlave_REQ", "");
  _Zminuit_MasterSlave_ACK_prefix = parm.GetChar("Zminuit_MasterSlave_ACK_prefix", "");
  _Zminuit_MasterSlave_START = parm.GetChar("Zminuit_MasterSlave_START", "");
  _Zminuit_MasterSlave_QUIT = parm.GetChar("Zminuit_MasterSlave_QUIT", "");
  _Zminuit_MasterSlave_DONE_prefix = parm.GetChar("Zminuit_MasterSlave_DONE_prefix", "");
  _Zminuit_MasterSlave_RESULT_prefix = parm.GetChar("Zminuit_MasterSlave_RESULT_prefix" , "");
  _Zminuit_START_Relscale_A = parm.GetDouble("Zminuit_START_Relscale_A", 1.0);
  _Zminuit_START_Relscale_B = parm.GetDouble("Zminuit_START_Relscale_B", 0.1);
  _Zminuit_START_Relsampling_A = parm.GetDouble("Zminuit_START_Relsampling_A", 1.0);
  _Zminuit_START_Relsampling_B = parm.GetDouble("Zminuit_START_Relsampling_B", 0.0);
  _Zminuit_START_Relphi_A = parm.GetDouble("Zminuit_START_Relphi_A", 1.0);
  _Zminuit_START_Relphi_B = parm.GetDouble("Zminuit_START_Relphi_B", 0.0);
  _Zminuit_START_Alpha_MB = parm.GetDouble("Zminuit_START_Alpha_MB", 1.0);
  _Zminuit_RANGE_Unlimited = parm.GetBool("Zminuit_RANGE_Unlimited", kTRUE);
  _Zminuit_RANGE_Relscale_A = parm.GetVDouble("Zminuit_RANGE_Relscale_A");
  _Zminuit_RANGE_Relscale_B = parm.GetVDouble("Zminuit_RANGE_Relscale_B");
  _Zminuit_RANGE_Relsampling_A = parm.GetVDouble("Zminuit_RANGE_Relsampling_A");
  _Zminuit_RANGE_Relsampling_B = parm.GetVDouble("Zminuit_RANGE_Relsampling_B");
  _Zminuit_RANGE_Relphi_A = parm.GetVDouble("Zminuit_RANGE_Relphi_A");
  _Zminuit_RANGE_Relphi_B = parm.GetVDouble("Zminuit_RANGE_Relphi_B");
  _Zminuit_RANGE_Alpha_MB = parm.GetVDouble("Zminuit_RANGE_Alpha_MB");
  _Zminuit_STEP_Relscale_A = parm.GetDouble("Zminuit_STEP_Relscale_A", 0.01);
  _Zminuit_STEP_Relscale_B = parm.GetDouble("Zminuit_STEP_Relscale_B", 0.01);
  _Zminuit_STEP_Relsampling_A = parm.GetDouble("Zminuit_STEP_Relsampling_A", 0.01);
  _Zminuit_STEP_Relsampling_B = parm.GetDouble("Zminuit_STEP_Relsampling_B", 0.01);
  _Zminuit_STEP_Relphi_A = parm.GetDouble("Zminuit_STEP_Relphi_A", 0.01);
  _Zminuit_STEP_Relphi_B = parm.GetDouble("Zminuit_STEP_Relphi_B", 0.01);
  _Zminuit_STEP_Alpha_MB = parm.GetDouble("Zminuit_STEP_Alpha_MB", 0.01);
  _Zminuit_do_SCAN = parm.GetBool("Zminuit_do_SCAN", false);               // Perform scan of a single parameter ?
  _Zminuit_do_SCAN_IPAR = parm.GetInt("Zminuit_do_SCAN_IPAR", -1);     // Parameter to be scanned: 0=RelScaleA, 1=RelScaleB, ...
  _Zminuit_do_SCAN_NSTEPS = parm.GetInt("Zminuit_do_SCAN_NSTEPS", -1); // Number of steps (>1)
  if(_Zminuit_do_SCAN) {
    if(_Zminuit_do_SCAN_IPAR<0) {
      cout<<"ZAnalysis: Zminuit_do_SCAN_IPAR="<<_Zminuit_do_SCAN_IPAR<<" < 0 !!!"<<endl;
      throw;
    }
    if(_Zminuit_do_SCAN_NSTEPS<2) {
      cout<<"ZAnalysis: Zminuit_do_SCAN_NSTEPS="<<_Zminuit_do_SCAN_NSTEPS<<" < 2 !!!"<<endl;
      throw;
    }
  }
  _Zminuit_do_SEEK = parm.GetBool("Zminuit_do_SEEK", false);                  // perform random seek inside the hypercube?
  _Zminuit_do_SEEK_RndStart = parm.GetBool("Zminuit_do_SEEK_RndStart", true); // use a random starting point rather than START value?
  _Zminuit_do_SEEK_NITER = parm.GetInt("Zminuit_do_SEEK_NITER", 50000);   // approximate number of steps for this random seek
  _Zminuit_do_SEEK_NEVENTS = parm.GetInt("Zminuit_do_SEEK_NEVENTS", -1);  // max. number of events to be used during this random seek
  if(_Zminuit_do_SEEK) {
    if(_Zminuit_do_SEEK_NITER<1) {
      cout<<"ZAnalysis: Zminuit_do_SEEK_NITER="<<_Zminuit_do_SEEK_NITER<<" <1 !!!"<<endl;
      throw;
    }
  }
  _Zminuit_do_SIMPLEX = parm.GetBool("Zminuit_do_SIMPLEX", false);               // use SIMPLEX method? 
  _Zminuit_do_SIMPLEX_NITER = parm.GetInt("Zminuit_do_SIMPLEX_NITER", 5000); // approximate number of steps for the SIMPLEX method
  _Zminuit_do_SIMPLEX_TOLER = parm.GetDouble("Zminuit_do_SIMPLEX_TOLER", 0.01);  // tolerance parameter of the SIMPLEX method
  if(_Zminuit_do_SIMPLEX) {
    if(_Zminuit_do_SIMPLEX_NITER<1) {
      cout<<"ZAnalysis: Zminuit_do_SIMPLEX_NITER="<<_Zminuit_do_SIMPLEX_NITER<<" <1 !!!"<<endl;
      throw;
    }
    if(_Zminuit_do_SIMPLEX_TOLER<=0.0) {
      cout<<"ZAnalysis: Zminuit_do_SIMPLEX_TOLER="<<_Zminuit_do_SIMPLEX_TOLER<<" <=0 !!!"<<endl;
      throw;
    }
  }
  _Zminuit_do_MINIMIZE = parm.GetBool("Zminuit_do_MINIMIZE", false);              // use MINIMIZE (MIGRAD+SIMPLEX) method?
  _Zminuit_do_MINIMIZE_NITER = parm.GetInt("Zminuit_do_MINIMIZE_NITER", 5000);// approximate number of steps for the MINIMIZE method
  _Zminuit_do_MINIMIZE_TOLER = parm.GetDouble("Zminuit_do_MINIMIZE_TOLER", 0.1);  // tolerance parameter of the MINIMIZE method
  _Zminuit_do_MINIMIZE_EPS = parm.GetDouble("Zminuit_do_MINIMIZE_EPS", 1.0e-5);  // (machine) precision for FCN
  if(_Zminuit_do_MINIMIZE) {
    if(_Zminuit_do_MINIMIZE_NITER<1) {
      cout<<"ZAnalysis: Zminuit_do_MINIMIZE_NITER="<<_Zminuit_do_MINIMIZE_NITER<<" <1 !!!"<<endl;
      throw;
    }
    if(_Zminuit_do_MINIMIZE_TOLER<=0.0) {
      cout<<"ZAnalysis: Zminuit_do_MINIMIZE_TOLER="<<_Zminuit_do_MINIMIZE_TOLER<<" <=0 !!!"<<endl;
      throw;
    }
    if(_Zminuit_do_MINIMIZE_EPS<=0.0 || _Zminuit_do_MINIMIZE_EPS>=0.1) {
      cout<<"ZAnalysis: Zminuit_do_MINIMIZE_EPS must be between 0 and 0.1, not "<<_Zminuit_do_MINIMIZE_EPS<<" !!!"<<endl;
      throw;
    }
  }
  _Zminuit_do_MINOS = parm.GetBool("Zminuit_do_MINOS", false); // call MINOS after MIGRAD?
  _Zminuit_do_MINOS_NITER = parm.GetInt("Zminuit_do_MINOS_NITER", 5000);// approximate number of steps for MINOS
  if(_Zminuit_do_MINOS) {
    if(_Zminuit_do_MINOS_NITER<1) {
      cout<<"ZAnalysis: Zminuit_do_MINOS_NITER="<<_Zminuit_do_MINOS_NITER<<" <1 !!!"<<endl;
      throw;
    }
  }
  _Zminuit_UseFittedMeanWidth  = parm.GetBool("Zminuit_UseFittedMeanWidth", true);
  _Zminuit_UseAbsDeltaPhiImbal = parm.GetBool("Zminuit_UseAbsDeltaPhiImbal", true);


  // RCLSA: Get parameters for the Recoil Smearing Template Generation
  _ZHadronicRecoilBifurcateStudy = parm.GetBool("ZHadronicRecoilBifurcateStudy", false);
  _ZRecoilBifurcateBins = parm.GetVInt("ZRecoilBifurcateBins");
  _ZRecoilBifurcateStep = parm.GetVDouble("ZRecoilBifurcateStep");
  _ZRecoilEtaCuts = parm.GetBool("etaImbalance_perbincuts");
  _ZRecoilEtaCutLow = parm.GetVDouble("EtaImbalanceCutLow");
  _ZRecoilEtaCutHigh = parm.GetVDouble("EtaImbalanceCutHigh");
  _ZRecoilBifurcateFile = parm.GetChar("ZRecoilBifurcateFile");
  _ZRecoilDebugLevel = parm.GetInt("ZRecoilDebugLevel", 0);

  _TransZHadronicRecoilBifurcateStudy = parm.GetBool("TransZHadronicRecoilBifurcateStudy", false);
  _TransZRecoilBifurcateBins = parm.GetVInt("TransZRecoilBifurcateBins");
  _TransZRecoilBifurcateStep = parm.GetVDouble("TransZRecoilBifurcateStep");


  // ZB RunNum and EvtNum Tree
  _FillZBRunNumTree = parm.GetBool("FillZBRunNumTree", false);
  if (_FillZBRunNumTree){
    _ZBRunNumFile = new TFile("ZBRunNum.root", "recreate");
    _ZBRunNumTree = new TTree("zbrunnum", "zbrunnum");
    _ZBRunNumTree->Branch("ZBRunNum", &_ZBrunNum, "ZBRunNum/I");
    _ZBRunNumTree->Branch("ZBEvtNum", &_ZBevtNum, "ZBEvtNum/I");
  }

} 

// return the event weight for given Z mass point
// the weight should be very close to 1
vector<double> ZAnalysis::BreitWignerReweight(PMCSEvent& pmcsevent){

  vector<double> mass_weightfactor;
  mass_weightfactor.clear();
  
  double zmass_event = pmcsevent.GetWZBoson().Mass();
  double bw_default = pow(zmass_event*_zwidth_default/_zmass_default,2)/( pow(zmass_event*zmass_event-_zmass_default*_zmass_default,2) + 
									  pow(zmass_event*zmass_event*_zwidth_default/_zmass_default,2));
  
  double zmass_point=0., bw_reweight=0., factor=1.;

  for(int iloop=0; iloop<100; iloop++) {
    zmass_point = _zmass_default + (iloop-50)*_zmass_step;
    bw_reweight = pow(zmass_event*_zwidth_default/zmass_point,2)/( pow(zmass_event*zmass_event-zmass_point*zmass_point,2) + 
								   pow(zmass_event*zmass_event*_zwidth_default/zmass_point,2));
    if(bw_default!=0) factor=bw_reweight/bw_default;
    
    mass_weightfactor.push_back(factor);
  }
  
  return mass_weightfactor;
}

// pass uparallel efficiency
Int_t ZAnalysis::passesUParaEff(PMCSEMObj& emobj, 
				double upara,
				TRandom3 *dummy, 
                                int otherpass_flag, 
				double *external_upara_rnd){
  bool passesUParaCorrection=true;
  double upara_eff= 1.;

  if (!_ZUparaEffCorrHengne){
    double u0_CC, u1_CC, s_CC, u0_EC, s_EC;
    if ( _UseUparaOverPte) {
      _UparaEffCorrOption = 0;
      u0_CC = _Z_u0pte_CC;
      u1_CC = _Z_u1pte_CC;
      s_CC  = _Z_spte_CC;
      u0_EC = _Z_u0pte_EC;
      s_EC  = _Z_spte_EC;
    }
    else if ( _UseCosUphi ) {
      _UparaEffCorrOption = 0;
      u0_CC = _Z_u0phi_CC;
      u1_CC = _Z_u1phi_CC;
      s_CC  = _Z_sphi_CC;
      u0_EC = _Z_u0phi_EC;
      s_EC  = _Z_sphi_EC;
    }
    else {
      u0_CC = _Z_u0_CC;
      s_CC  = _Z_s_CC;
      u0_EC = _Z_u0_EC;
      s_EC  = _Z_s_EC;
    }

    // calculate uparallel efficiency for CC and EC regions
    if(emobj.IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut )){
      if(_UparaEffCorrOption == 0) {
        if(upara<u0_CC) upara_eff = 1.;
        else if ( (_UseUparaOverPte || _UseCosUphi) && upara > u1_CC) upara_eff = 1. - s_CC*(u1_CC - u0_CC);
        else upara_eff = 1. - s_CC*(upara - u0_CC);
      } else { // for _ZUparaEffCorrOption!=0, used for real data, two linear functions
        if(upara < _ZUparaEffParameters[0])
  	upara_eff = 1. - _ZUparaEffParameters[1] * (upara - _ZUparaEffParameters[0]);
        else
  	upara_eff = 1. - _ZUparaEffParameters[2] * (upara - _ZUparaEffParameters[0]);
      }
    } else if((emobj.IsEC(_CutEtaEC1, _CutEtaEC2)))  {
      if(upara<u0_EC) upara_eff = 1.;
      else upara_eff = 1. - s_EC*(upara - u0_EC);
    }
  }
  // Hengne's tests
  else {
    double UPara = emobj.getUPara();
    double UPerp = emobj.getUPerp();
    double UT = sqrt(UPara*UPara+UPerp*UPerp);
    double UPhi = TVector2::Phi_0_2pi(atan2(UPerp, UPara));
    if ( UT>_CutZUT){
      upara_eff = 1.0;
    }
    else if (_ZUparaEffCorrHengneOption==0){
      // upara, uperp
      upara_eff = _ZUparaEffCorrHengne_hUParaUPerpEFRT->GetBinContent(_ZUparaEffCorrHengne_hUParaUPerpEFRT->FindBin(UPara, UPerp));
    }
    else if (_ZUparaEffCorrHengneOption==1) {
      // ut=x, uphi=y
      upara_eff = _ZUparaEffCorrHengne_hUTUPhiEFRT->GetBinContent(_ZUparaEffCorrHengne_hUTUPhiEFRT->FindBin(UT, UPhi));
    }
    else if (_ZUparaEffCorrHengneOption==2) {
      //std::cout << "other pass: " << otherpass_flag << std::endl;
      // consider correlation: 
      //  different treatment in case the other pass or not (1) do not know (2) pass (3) not pass 
      assert(otherpass_flag==0||otherpass_flag==1||otherpass_flag==2);
      double u0, sl, sr;
      // case 1: do not know the other pass or not
      if (otherpass_flag==2){
        u0 = _ZUparaEffCorrHengne_Opt2Pars.at(0);
        sl = _ZUparaEffCorrHengne_Opt2Pars.at(1);
        sr = _ZUparaEffCorrHengne_Opt2Pars.at(2);
      }  
      // case 2: the other passes
      else if (otherpass_flag==1) {
        u0 = _ZUparaEffCorrHengne_Opt2Pars.at(3);
        sl = _ZUparaEffCorrHengne_Opt2Pars.at(4);
        sr = _ZUparaEffCorrHengne_Opt2Pars.at(5);
      } 
      // case 3: the other not passes
      else if (otherpass_flag==0) {
        u0 = _ZUparaEffCorrHengne_Opt2Pars.at(6);
        sl = _ZUparaEffCorrHengne_Opt2Pars.at(7);
        sr = _ZUparaEffCorrHengne_Opt2Pars.at(8);
      }
      // decide normalization, so as the efficiency maximum at 1.0 for UPara range (-30, 30)
      // function value when UPara=-30
      double value_m30 = 1.0+sl*(-30.0-u0);
      // function value when UPara=30
      double value_p30 = 1.0+sr*( 30.0-u0);
      // compare the above 2 function values together with 1 (the function value when UPara=u0), find the maximum to calculate the norm
      double norm = 1./max(1.0, max(value_m30, value_p30));
      // caluclate effiency
      upara_eff = (UPara<u0) ? norm*(1.0+sl*(UPara-u0)) : norm*(1.0+sr*(UPara-u0));
    }
    else {
      std::cout << "Warning:: No UparaEff is applied! _ZUparaEffCorrHengneOption must be 0, 1, or 2." << std::endl;
    }


  }
  // apply uparallel efficiency correction for an electron
  double rnd;
  if(external_upara_rnd) rnd = *external_upara_rnd;
  else                   rnd = dummy->Uniform(0., 1.);
  if(rnd > upara_eff) passesUParaCorrection = false;
  
  if(passesUParaCorrection) return 1;
  else return 0;
}


// pass uparallel efficiency
Int_t ZAnalysis::passesUParaEff(PMCSZCand& zcand, 
				TRandom3 *dummy, 
				double *external_upara_rnd1,
				double *external_upara_rnd2){
  bool passesUParaCorrection1=true,  passesUParaCorrection2=true;
  PMCSEMObj  emobj1 = zcand.GetElec1();
  PMCSEMObj  emobj2 = zcand.GetElec2();

  if(_ZUparaEffCorrection || _createRootTree2) {
    double upara1, upara2;
    if ( _UseUparaOverPte) {
      upara1 = zcand.UPara1()/zcand.GetElec1().ppt();
      upara2 = zcand.UPara2()/zcand.GetElec2().ppt();
    } 
    else if ( _UseCosUphi ) {
      upara1 = zcand.UPara1()/sqrt(zcand.UPara1()*zcand.UPara1() +zcand.UPerp1()*zcand.UPerp1());
      upara2 = zcand.UPara2()/sqrt(zcand.UPara2()*zcand.UPara2() + zcand.UPerp2()*zcand.UPerp2());
    }
    else {
      upara1 = zcand.UPara1();
      upara2 = zcand.UPara2();
    };

    // randomize the order of the two electrons
    // if use external random number, use external_upara_rnd1 to decide
    double rnd;
    if (external_upara_rnd1) rnd = *external_upara_rnd1;
    else rnd = dummy->Rndm();
    if (rnd>0.5) {
      passesUParaCorrection1 = passesUParaEff(emobj1, upara1, dummy, 2, external_upara_rnd1);
      passesUParaCorrection2 = passesUParaEff(emobj2, upara2, dummy, int(passesUParaCorrection1), external_upara_rnd2);
    }
    else {
      passesUParaCorrection2 = passesUParaEff(emobj2, upara2, dummy, 2, external_upara_rnd2);
      passesUParaCorrection1 = passesUParaEff(emobj1, upara1, dummy, int(passesUParaCorrection2), external_upara_rnd1);
    }

    tree2em_trk_upara[0] =passesUParaCorrection1;
    tree2em_trk_upara[1] =passesUParaCorrection2;

    if (!_ZUparaEffCorrection){
      passesUParaCorrection1 = passesUParaCorrection2 = true;
    }
  }//Uparallel correction
  
  bool passesUParaCorrection = (passesUParaCorrection1 && passesUParaCorrection2); // both electron pass isolation cut

  if (passesUParaCorrection) return 1;
  else return 0;
}



// the whole event passes efficiency cuts
Int_t ZAnalysis::passesAllEffs(PMCSZCand& zcand, PMCSVtx& vtx_gen, TRandom3 *dummy, double TrigVer){
  PMCSEMObj  emobj1 = zcand.GetElec1();
  PMCSEMObj  emobj2 = zcand.GetElec2();
  
  // both electron passes uparallel efficiency
  bool passesUParaCorrection = passesUParaEff(zcand, dummy);

  if (passesUParaCorrection) return (passesAllNonUParaEffs(emobj1,emobj2,vtx_gen,dummy,TrigVer));
  else return 0;
}

// The following comment is from S. Yacoob
// this function will return an integer from 1-3, (if the event passes all effs), this is particularly useful for me 
// because I try to make Z's into W's. The idea is that for a W event we get a CC electron, and require that CC 
// electron to have a track match, and be the electron that fired the trigger (TrkMatchEff, TriggEff).
// For Z CC-CC, and CC-EC electrons, I want to have the same condition on at least one of my electrons,
// passesAllNonUParaEffs will pass a 1, or a 2, to tell me which of the two electrons is CC, and passed all the 
// efficiencies to be basically  a 'tight' electron. (so it tells me more than the deteta of the electron)
// a Three tells me that both electrons are 'tight' electrons and so I can make 2 W candidates from them.
Int_t ZAnalysis::passesAllNonUParaEffs(PMCSEMObj& emobj1, PMCSEMObj& emobj2, PMCSVtx& vtx_gen, TRandom3 *dummy, double TrigVer, double* externalRndm) {
  
  bool passesAllNonUParaEffs = true;
  
  bool passesTrigEff1=true, passesTrigEff2=true;
  bool passesPreselEff1=true, passesPreselEff2=true;
  bool passesEMIDEff1=true, passesEMIDEff2=true;
  bool passesTrkEff1=true, passesTrkEff2=true;
  bool passesLooseTrkEff1=true, passesLooseTrkEff2=true;
  bool passesElecPhiEff1=true, passesElecPhiEff2=true;
  bool passesAddOnEff1=true, passesAddOnEff2=true;

  if (externalRndm) {

    if(_ZtrigEffCorrection) {
      passesTrigEff1= _efficiencysmear->passesTriggerEff(emobj1, dummy, TrigVer, _ZBrunNum, &(externalRndm[0]));
      passesTrigEff2 = _efficiencysmear->passesTriggerEff(emobj2, dummy, TrigVer, _ZBrunNum, &(externalRndm[1]));
    }

    if(_ZpreselEffCorrection) {
      passesPreselEff1 = _efficiencysmear->passesPreselEff(emobj1, dummy, &(externalRndm[2]), &vtx_gen, &(externalRndm[14]),1);
      passesPreselEff2 = _efficiencysmear->passesPreselEff(emobj2, dummy, &(externalRndm[3]), &vtx_gen, &(externalRndm[15]),1);
    }
    
    passesLooseTrkEff1 =  _efficiencysmear->passesLooseTrkEff(emobj1, &vtx_gen, dummy, &(externalRndm[12]));
    passesLooseTrkEff2 =  _efficiencysmear->passesLooseTrkEff(emobj2, &vtx_gen, dummy, &(externalRndm[13]));
    
    if(_ZIDEffCorrection || _createRootTree2) {
      passesEMIDEff1 = _efficiencysmear->passesEMIDEff(emobj1, dummy, &(externalRndm[4]));
      passesEMIDEff2 = _efficiencysmear->passesEMIDEff(emobj2, dummy, &(externalRndm[5]));
      
    }
    
    if(_NZTrkMatch != 0) {
      passesTrkEff1 = _efficiencysmear->passesTrkEff(emobj1, vtx_gen, dummy, &(externalRndm[6]))&&  passesLooseTrkEff1 ;
      passesTrkEff2 = _efficiencysmear->passesTrkEff(emobj2, vtx_gen, dummy, &(externalRndm[8]))&& passesLooseTrkEff2 ;
      if(_ZElecPhiEffCorrection) {
	passesElecPhiEff1 = _efficiencysmear->passesElecPhiEff(emobj1, dummy, _ZElecPhiEffCorrectionUseDetPhi, &(externalRndm[10]));
	passesElecPhiEff2 = _efficiencysmear->passesElecPhiEff(emobj2, dummy, _ZElecPhiEffCorrectionUseDetPhi, &(externalRndm[11]));
	passesTrkEff1 = passesTrkEff1 && passesElecPhiEff1; 
	passesTrkEff2 = passesTrkEff2 && passesElecPhiEff2; 
      }
    }
   
    if (_ApplyAddOnEff_Zee){
      // randomize the order of the two electrons
      if (externalRndm[16]>0.5) {
        passesAddOnEff1 = _efficiencysmear->passesAddOnEff(emobj1, false, dummy, 2, &(externalRndm[16]));
        passesAddOnEff2 = _efficiencysmear->passesAddOnEff(emobj2, false, dummy, int(passesAddOnEff1), &(externalRndm[17]));
        passesAddOnEff1 = _efficiencysmear->passesAddOnEff(emobj1, false, dummy, int(passesAddOnEff2), &(externalRndm[16]));
      }
      else {
        passesAddOnEff2 = _efficiencysmear->passesAddOnEff(emobj2, false, dummy, 2, &(externalRndm[17]));
        passesAddOnEff1 = _efficiencysmear->passesAddOnEff(emobj1, false, dummy, int(passesAddOnEff2), &(externalRndm[16]));
        passesAddOnEff2 = _efficiencysmear->passesAddOnEff(emobj2, false, dummy, int(passesAddOnEff1), &(externalRndm[17]));
      }
    }
 
  } else {
    
    if(_ZtrigEffCorrection) {
      passesTrigEff1= _efficiencysmear->passesTriggerEff(emobj1, dummy, TrigVer, _ZBrunNum);
      passesTrigEff2 = _efficiencysmear->passesTriggerEff(emobj2, dummy, TrigVer, _ZBrunNum);
    }
    
    if(_ZpreselEffCorrection) {
      passesPreselEff1 = _efficiencysmear->passesPreselEff(emobj1, dummy, 0, &vtx_gen,0,1);
      passesPreselEff2 = _efficiencysmear->passesPreselEff(emobj2, dummy, 0, &vtx_gen,0,1);
    }
    
    passesLooseTrkEff1 =  _efficiencysmear->passesLooseTrkEff(emobj1, &vtx_gen, dummy);
    passesLooseTrkEff2 =  _efficiencysmear->passesLooseTrkEff(emobj2, &vtx_gen, dummy);
    
    if(_ZIDEffCorrection || _createRootTree2) {
      passesEMIDEff1 = _efficiencysmear->passesEMIDEff(emobj1, dummy);
      passesEMIDEff2 = _efficiencysmear->passesEMIDEff(emobj2, dummy);
    }


    if(_NZTrkMatch != 0) {
      passesTrkEff1 = _efficiencysmear->passesTrkEff(emobj1, vtx_gen, dummy) && passesLooseTrkEff1;
      passesTrkEff2 = _efficiencysmear->passesTrkEff(emobj2, vtx_gen, dummy) && passesLooseTrkEff2;
      if(_ZElecPhiEffCorrection) {
          passesElecPhiEff1 = _efficiencysmear->passesElecPhiEff(emobj1, dummy, _ZElecPhiEffCorrectionUseDetPhi);
          passesElecPhiEff2 = _efficiencysmear->passesElecPhiEff(emobj2, dummy, _ZElecPhiEffCorrectionUseDetPhi);
          passesTrkEff1 = passesTrkEff1 && passesElecPhiEff1; 
          passesTrkEff2 = passesTrkEff2 && passesElecPhiEff2; 
      }
    }

    if (_ApplyAddOnEff_Zee){
      // randomize the order of the two electrons
      if (dummy->Rndm()>0.5) {
        passesAddOnEff1 = _efficiencysmear->passesAddOnEff(emobj1, false, dummy, 2);
        passesAddOnEff2 = _efficiencysmear->passesAddOnEff(emobj2, false, dummy, int(passesAddOnEff1));
        passesAddOnEff1 = _efficiencysmear->passesAddOnEff(emobj1, false, dummy, int(passesAddOnEff2));
      }
      else {
        passesAddOnEff2 = _efficiencysmear->passesAddOnEff(emobj2, false, dummy, 2);
        passesAddOnEff1 = _efficiencysmear->passesAddOnEff(emobj1, false, dummy, int(passesAddOnEff2));
        passesAddOnEff2 = _efficiencysmear->passesAddOnEff(emobj2, false, dummy, int(passesAddOnEff1));
      }
    }

  }

   
  bool passesTrig = (passesTrigEff1 || passesTrigEff2); //at least one electron passes trigger requirement
  bool passesPresel = (passesPreselEff1 && passesPreselEff2); //both electrons should pass preselection requirement
  bool passesLooseTrkEff = false;
  if (_NZpreselTrkMatch == 1)
    passesLooseTrkEff = (passesLooseTrkEff1 || passesLooseTrkEff2);
  else if (_NZpreselTrkMatch == 2)
    passesLooseTrkEff = (passesLooseTrkEff1 && passesLooseTrkEff2);
  else
    passesLooseTrkEff = true;

  bool passesEMID=true;
  if (_ZIDEffCorrection)
    passesEMID = (passesEMIDEff1 && passesEMIDEff2); //both electrons should pass EMID requirement
  
  bool passesTrk = false;
  if(_NZTrkMatch == 1) passesTrk = (passesTrkEff1  || passesTrkEff2); //at least one electron passes track requirement
  else if(_NZTrkMatch == 2) passesTrk = (passesTrkEff1 && passesTrkEff2); //both electrons pass track requirement
  else passesTrk = true;  //no track match requirement

  bool passesAddOnEff = (passesAddOnEff1 &&passesAddOnEff2);
 
  //std::cout << "passAddOnEff " << passesAddOnEff << std::endl;

  passesAllNonUParaEffs = (passesTrig && passesPresel && passesEMID && passesTrk && passesLooseTrkEff && passesAddOnEff);

  if(_createRootTree2) {
   tree2em_trk_prob[0]=passesLooseTrkEff1;
   tree2em_trk_prob[1]=passesLooseTrkEff2; 
   tree2em_hmX[0] = passesEMIDEff1;
   tree2em_hmX[1] = passesEMIDEff2;
   tree2em_trk_presel[0] = passesPreselEff1;
   tree2em_trk_presel[1] = passesPreselEff2;
   tree2em_trk_addon[0] = passesAddOnEff1;
   tree2em_trk_addon[1] = passesAddOnEff2;
   
   tree2em_trk_probtight[0]=passesTrkEff1;
   tree2em_trk_probtight[1]=passesTrkEff2;
   tree2em_trk_trig[0]=passesTrigEff1;
   tree2em_trk_trig[1]=passesTrigEff2;
   tree2_passesnonuparaeff = passesAllNonUParaEffs;

   tree2em_cc[0] = emobj1.IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);
   tree2em_cc[1] = emobj2.IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);
  }

  bool passesEM2 = (passesTrigEff2 && passesTrkEff2 && emobj2.IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut)); // Ensure that the same electron passed the trackmatch, and trigger requirement
  bool passesEM1 = (passesTrigEff1 && passesTrkEff1 && emobj1.IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut)); //
  if(emobj1.IsEC(_CutEtaEC1, _CutEtaEC2) && emobj2.IsEC(_CutEtaEC1, _CutEtaEC2)) 
    return passesAllNonUParaEffs;
  else   
    return (passesAllNonUParaEffs)*(1*passesEM1 + 2*passesEM2);
}

//
// Cuts that DO NOT depend on the hadronic recoil
// (Z candidate mass, Z candidate type, cuts on EM objects, most EM efficiencies)
//
// This function returns TRUE when all 5 cuts are satisfied.
//     
// While making hadronic recoil template histograms
// please make sure that you put cuts dependent on the 
// smeared EM objects first. Only then use cuts on the smeared 
// RECOIL and/or smeared MET and/or parameterized efficiency.
//
// Options:
// 1. When Ncuts_OUT<>NULL:
//    Will return the number of cuts passed by this event.
// 2. When Trigger_Version_OUT<>NULL:
//    Will return back a Trigger_Version value used as an input to passAllNonUParaEffs().
// 3. When passAllNonUParaEffs_OUT<>NULL:
//    Will return back the result of passAllNonUParaEffs().
//




bool ZAnalysis::passesEMCuts(vector<PMCSEMObj>& emobjs_smear, 
			     PMCSVtx& vtx_gen,
			     TRandom3 *dummy, 
			     int *Ncuts_OUT,
			     double *Trigger_Version_OUT,    // reads back Trigger_Version (0..1)
			     int *passAllNonUParaEffs_OUT,   // reads back passesAllNonUParaEffs() result
			     bool doNotEnforceMassCut,
			     double* externalRndm) {
  int _counter;
  // switch between local/remote pointer to the # of passed cuts
  int *counter=(Ncuts_OUT ? Ncuts_OUT : &_counter);
  if(Trigger_Version_OUT) *Trigger_Version_OUT=-1;
  if(passAllNonUParaEffs_OUT) *passAllNonUParaEffs_OUT=-1;
  (*counter)=0;
  // 
  // CUT #0: At least two EM Objects
  // NOTE: it depends only on EM smeared objects, not the recoil!
  //
  if((emobjs_smear.size() >= 2)&&(!emobjs_smear[0].IsLostInAcrack())&&(!emobjs_smear[1].IsLostInAcrack())) {
    (*counter)++;
    // 
    // CUT #1: Smeared EM objs PTs
    // NOTE: it depends only on EM smeared objects, not the recoil!
    //
    if( (emobjs_smear[0].ppt()>_CutEPT1_lo) && (emobjs_smear[1].ppt()>_CutEPT2_lo) && (emobjs_smear[0].ppt()<_CutEPT1_hi) && (emobjs_smear[1].ppt()<_CutEPT2_hi) )  {
      (*counter)++;
      //
      // CUT #2: Require track match and cut on PT of the track(s)
      // NOTE: it depends only on EM smeared objects, not the recoil!
      //
      bool passTrkpT = false;
      if(_NZTrkMatch == 2) 
	passTrkpT = (emobjs_smear[0].trkpT()>_trkpTCut) && (emobjs_smear[1].trkpT()>_trkpTCut);
      else if(_NZTrkMatch == 1) 
	passTrkpT = (emobjs_smear[0].trkpT()>_trkpTCut) || (emobjs_smear[1].trkpT()>_trkpTCut);
      else passTrkpT = true;
      if( passTrkpT || _momentumScaleStudy || _radLengthStudy) {
	(*counter)++;
        //
	// CUT #3: Kinematical cuts on Z candidate  
	// NOTE: it depends only on EM smeared objects, not the recoil!
	//
	PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1]);
	double mass = zcand.mass();
	if(mass>_ZMassCut1 && 
	   mass<_ZMassCut2 && zcand.ppt() < _CutZPT && zcand.ppt() >= _CutZPT_lower && zcand.phi() < _CutZPhi && zcand.phi() >= _CutZPhi_lower &&
	   zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut)>=0) {
	  (*counter)++;
	  //
	  // CUT #4: Efficiency cuts on smeared EM objects that 
	  //         DO NOT depend on the recoil.
	  //
	  double Trigger_Version = dummy->Uniform(0., 1.);
	  if(Trigger_Version_OUT) *Trigger_Version_OUT=Trigger_Version;
	  //
	  // Check all efficiencies but U_parallel corr. effs. 
	  // The result is an integer 0...3 (not bool) because Sahal wants to keep
	  // information whether or not individual electrons passed their efficiency cuts. 
	  // NOTE: U_parallel corr. effs. will be checked later by passesRecoilCuts()
	  int passAllNonUParaEffs = passesAllNonUParaEffs(emobjs_smear[0], emobjs_smear[1], vtx_gen, dummy, Trigger_Version, externalRndm);
	  if(passAllNonUParaEffs_OUT) *passAllNonUParaEffs_OUT=passAllNonUParaEffs;
	  if(_NZTrkMatch == 1) {
	    passTrkpT = (((emobjs_smear[0].trkpT()>_trkpTCut)* (passAllNonUParaEffs!=2)) || ((emobjs_smear[1].trkpT()>_trkpTCut)* (passAllNonUParaEffs > 1)));
	  }
	  if(passAllNonUParaEffs && passTrkpT){
	    (*counter)++;
	    
	    return true; 
	    
	  } //   end of CUT #4
	} //     end of CUT #3
      } //       end of CUT #2
    } //         end of CUT #1
  } //           end of CUT #0
  return false;
}
//
// Cuts that DO DEPEND on the hadronic recoil 
// (e.g. UT, MET, U_parallel corr. effs.)
//
// This function returns TRUE when all 3 cuts are satisfied.
//
// Options:
// 1. When Ncuts_OUT<>NULL:
//    Will return the number of cuts passed by this event.
// 2. When passUParaEffs_OUT<>NULL:
//    Will return back the result of passUParaEffs().
// 3. When skip_UParaEffs=TRUE:
//    Will not call passesUParaEff() at all.
// 4. When skip_UParaEffs=FALSE and 
//    (external_upara_rnd1<>NULL or external_upara_rnd2<>NULL)
//    Will use a user-supplied random number to call
//    passesUParaEff() for one or both electrons. 
//    This option is particularly useful while creating
//    many templates from the same generated Z boson. 
bool ZAnalysis::passesRecoilCuts(vector<PMCSEMObj>& emobjs_smear,
				 PMCSRecoil& recoil_smear,
				 PMCSMet& met_smear,
				 TRandom3 *dummy, 
				 int *Ncuts_OUT,              // reads back the number of cuts passed
				 bool *passUParaEffs_OUT,     // reads back passesUParaEff() result
				 bool skip_UParaEffs,         // do not check U_parallel corr. eff. at all?
                                 double *external_upara_rnd1, // use one ore both random numbers while calling 
				 double *external_upara_rnd2, // passesUParaEff() for individual electrons
                                 double *external_SET_rnd) {  // used for SET efficiency
//   //////////////////////////////// DEBUG
//   //
//   cout << "passesRecoilCuts: STARTED" << endl;
//   //
//   //////////////////////////////// DEBUG
  int _counter;
  // switch between local/remote pointer to the # of passed cuts
  int *counter=(Ncuts_OUT ? Ncuts_OUT : &_counter);
  (*counter)=0;
  if(passUParaEffs_OUT) *passUParaEffs_OUT=false;
  // 
  // CUT #0: At least two EM Objects
  // because we need to construct a Z candidate
  //
  if(emobjs_smear.size() >= 2) {
    (*counter)++;
    //
    // CUT #1: Kinematical cuts on the smeared recoil
    //
    double Ut=recoil_smear.Recoil();
    if(Ut<_CutZUT && Ut>=_CutZUT_lower) {
      (*counter)++;
      //
      // CUT #2 U_parallel correction efficiencies that do depend
      //        on the recoil.
      //
      if(skip_UParaEffs) return true;
      PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);
      bool passUParaEffs = passesUParaEff(zcand, dummy, external_upara_rnd1, external_upara_rnd2);
      //std::cout << passUParaEffs << "    " << external_upara_rnd1   << "     " <<external_upara_rnd2 <<   std::endl;
      if(passUParaEffs_OUT) *passUParaEffs_OUT=passUParaEffs;
      if(passUParaEffs) {
	(*counter)++;
	//
	// CUT #3 SET cut that do depend
	//        on the recoil.
	double scalarEt_All = _recoilsmear->scalarEt();
	if(scalarEt_All>_CutZScalarEt_lower && scalarEt_All<_CutZScalarEt) {
	  (*counter)++;
	  //
	  // CUT #4 SET efficiency cut that do depend
	  //        on the recoil.
	  //
	  bool passSETeff=true;
	  if (_ZSETEffCorrection ||_createRootTree2 ) {
	    if (_ZSETEffCorrPTEpert) {
	      passSETeff=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),
                                                           dummy, external_SET_rnd, emobjs_smear[0].ppt(), emobjs_smear[1].ppt(), 
							   emobjs_smear[0].IsEC(_CutEtaEC1,_CutEtaEC2), emobjs_smear[1].IsEC(_CutEtaEC1,_CutEtaEC2),
							   emobjs_smear[0].deteta(), emobjs_smear[1].deteta(), zcand.UPara1(), zcand.UPara2());
	      if(_createRootTree2){
		tree2em_trk_set[0] =_SETefficiencysmear->passesFirst();
		tree2em_trk_set[1] =_SETefficiencysmear->passesSecond();
		if (!_ZSETEffCorrection){
		  passSETeff=true;
		}
	      }
	    } else {
	      passSETeff=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),
							   dummy, external_SET_rnd);
	    }
	  }
	  if(passSETeff) {
	    (*counter)++;
// 	    //////////////////////////////// DEBUG
// 	    //
// 	    cout << "passesRecoilCuts: ENDED ==> EVENT PASSED" << endl;
// 	    //
// 	    //////////////////////////////// DEBUG
	    
	    if (_etaImbalance_perbincuts) {
	      Int_t pTeeEtaCutBin = wz_utils::pTee_Eta_Bin(zcand.ppt());
	      if (pTeeEtaCutBin < 0){
		if (!_InvertetaImbalance_perbincuts){
		  return false;
		}
		else {
		  (*counter)++;
		  return true;
		}
		
	      }	
	      if (_InvertetaImbalance_perbincuts){
		if (!((zcand.p_ee()+zcand.recoil() < _EtaImbalanceCutHigh.at(pTeeEtaCutBin) ) && (zcand.p_ee()+zcand.recoil() >  _EtaImbalanceCutLow.at(pTeeEtaCutBin) ))){
		  (*counter)++;
		  return true;
		}
	      }
	      else{
		if ((zcand.p_ee()+zcand.recoil() < _EtaImbalanceCutHigh.at(pTeeEtaCutBin) ) && (zcand.p_ee()+zcand.recoil() >  _EtaImbalanceCutLow.at(pTeeEtaCutBin) )){
		  (*counter)++;
		  return true;
		  
		}
	      }
	    } // end of CUT #5
	    else
	      return true;
	  } //   end of CUT #4
	} //     end of CUT #3
      } //       end of CUT #2
    } //         end of CUT #1
  } //           end of CUT #0
//   //////////////////////////////// DEBUG
//   //
//   cout << "passesRecoilCuts: ENDED ==> EVENT REJECTED" << endl;
//   //
//   //////////////////////////////// DEBUG
  return false;
}

// Analyze an event
void ZAnalysis::analyzeEvent(PMCSEvent& pmcsevent, TRandom3 *dummy) {

  // this weight will be 1 if you set Reweight=false in the configuration file
  double evtweight = pmcsevent.GetEvtWeight();
  //  cout<<"pmcs start evtweight "<<evtweight<<endl;
  // generator-level electron and vertex information
  vector<PMCSEMObj> emobjs_gen = pmcsevent.GetEMObjs();
  vector<PMCSEMObj> emobjs_raw_gen = pmcsevent.GetRawEMObjs();
  vector<PMCSEMObj> emobjs_raw_gen_wfsr = pmcsevent.GetRawEMObjsWFSR();
  PMCSVtx vtx_gen = pmcsevent.GetVtx();


  // generator level Z pT
  double zpT_gen = pmcsevent.GetWZBoson().ppt();
  double zphi_gen = pmcsevent.GetWZBoson().phi();
  double zmass_gen = pmcsevent.GetWZBoson().Mass();

  //ZBRunNo for Trigger
  _ZBrunNum  = pmcsevent.GetRunNo();
  _ZBevtNum  = pmcsevent.GetEvtNo();

  // generator-level met and recoil system information
  PMCSMet met_gen = pmcsevent.GetMet();
  PMCSRecoil recoil_gen = pmcsevent.GetRecoil();
  double recoilpT_gen = recoil_gen.Recoil();

  // Get instantaneous luminosity
  double luminosity = pmcsevent.GetInstLumi();
  recoil_gen.SetLumi(luminosity);

  // first smear recoil system and then apply uparallel corrections
  // this will also initialize fudging parameters for SET
  PMCSRecoil recoil_smear_beforeUparaCorr = _recoilsmear->SmearRecoil(recoil_gen, dummy);
  TVector2 recoil_vec_beforeUparaCorr(recoil_smear_beforeUparaCorr.Recoilx(), recoil_smear_beforeUparaCorr.Recoily());

  // Set Luminosity and RecoilVec to _emsmear, to be used for Lumi/UPara dependent Scale/Offset
  _emsmear->SetLuminosity(luminosity);
  _emsmear->SetRunNumber(_ZBrunNum);
  _emsmear->SetRecoilVec(recoil_vec_beforeUparaCorr);

  //Set run number for run3, 4 dependent efficiency application
  _efficiencysmear->SetRunNumber(_ZBrunNum);
  
  // smear EMObjects and Recoil System and calculate smeared MET
  // do not simulate energies below electron window first since it depends on uparallel 
  // which will be calculated later
  _emsmear->Set_EnergySim_ElecWindow(false);
  vector<PMCSEMObj> emobjs_smear = _emsmear->SmearEMObjs(emobjs_gen, dummy);
  
  // First set luminosity and uparallel for electron in order to do simulation of energies below electron window
  // which is luminosity and uparallel dependent
  // Then add energies below electron window
  Double_t **extrndm = new Double_t*[emobjs_smear.size()];
  for (Int_t iecounter=0; iecounter < emobjs_smear.size(); ++iecounter){
    extrndm[iecounter] = new Double_t[4];
    for (Int_t icounter=0; icounter < 4; ++icounter){
      extrndm[iecounter][icounter] = dummy->Rndm(); 
    }
  }

  Double_t extrndm_duparaeff[10000];
  for (Int_t icounter=0; icounter < 10000; ++icounter){
    extrndm_duparaeff[icounter] = dummy->Rndm();
  }


  double external_upara_rnd1 = dummy->Uniform(0., 1.);
  double external_upara_rnd2 = dummy->Uniform(0., 1.);
  double external_SET_rnd[2];
  
  for (int isetrndm = 0; isetrndm < 2; ++isetrndm){
    external_SET_rnd[isetrndm]= dummy->Uniform(0., 1.);
  }
  

  double externalRndm[18];
  for (int i=0; i<18; i++) externalRndm[i]=dummy->Uniform(0., 1.);

  std::vector<PMCSEMObj> emobjs_noupara = emobjs_smear;

  //  Recoil Smearing Template Generator
  if(_ZHadronicRecoilBifurcateStudy) {
    ZHadronicRecoilBifurcateStudy(emobjs_noupara, recoil_gen, vtx_gen, dummy, evtweight, luminosity,
				  &external_upara_rnd1, &external_upara_rnd2,
				  external_SET_rnd, extrndm, extrndm_duparaeff, externalRndm);
    return;
  }
  
  if(_TransZHadronicRecoilBifurcateStudy) {
    TransZHadronicRecoilBifurcateStudy(emobjs_noupara, recoil_gen, vtx_gen, dummy, evtweight, luminosity,
				       &external_upara_rnd1, &external_upara_rnd2,
				       external_SET_rnd, extrndm, extrndm_duparaeff, externalRndm);
    return;
  }

  PMCSRecoil recoil_smear = recoil_smear_beforeUparaCorr;
  TVector2 recoil_vec(recoil_smear.Recoilx(), recoil_smear.Recoily());
  double ScalarEt = _recoilsmear->scalarEt();
  for(int ielec=0; ielec<emobjs_smear.size(); ielec++) {
    // new requirement, only do this for electron, similar already included in EMSmear
    // here I want to make sure that we only do this for real electrons
    //moved ppt requirement two lines down 5/18/2012 for EnergyScale to run
    emobjs_smear[ielec].SetLumi(luminosity);
    emobjs_smear[ielec].SetScalarEt(ScalarEt);
    
     if(abs(emobjs_smear[ielec].ppt()) > 15.) {
      
      TVector2 elec_vec(emobjs_smear[ielec].ppx(), emobjs_smear[ielec].ppy());
      double upara_elec = recoil_vec*elec_vec.Unit();
      double uperp_elec = recoil_vec*elec_vec.Unit().Rotate(TMath::Pi()/2.0);
      emobjs_smear[ielec].SetUPara(upara_elec);
      emobjs_smear[ielec].SetUPerp(uperp_elec);
      if(_pedanticRandomRecoil) {
	_emsmear->SmearEnergyUnderElecWindow(emobjs_smear[ielec], dummy, false);
      } else {
	_emsmear->SmearEnergyUnderElecWindow(emobjs_smear[ielec], dummy, false, extrndm[ielec]);
      }
     }
  }

  for (Int_t iecounter=0; iecounter < emobjs_smear.size(); ++iecounter){
    delete[] extrndm[iecounter];
  }
  delete[] extrndm;

  // sort smeared electrons according to pT
  sort(emobjs_smear.begin(), emobjs_smear.end(), ComparePt);
  sort(emobjs_gen.begin(), emobjs_gen.end(), ComparePt);
  sort(emobjs_raw_gen.begin(), emobjs_raw_gen.end(), ComparePt);
  sort(emobjs_raw_gen_wfsr.begin(), emobjs_raw_gen_wfsr.end(), ComparePt);

  double ptee_gen , dphi_ee_gen , deta_ee_gen;
  if( emobjs_raw_gen.size() >= 2 )
  {
    ptee_gen = ( emobjs_raw_gen[0].GetVect3() + emobjs_raw_gen[1].GetVect3() ).Pt();
    dphi_ee_gen = emobjs_raw_gen[0].GetVect3().DeltaPhi( emobjs_raw_gen[1].GetVect3() );
    deta_ee_gen = emobjs_raw_gen[0].peta() - emobjs_raw_gen[1].peta();
  }
  
  // will only apply uparallel corrections for the two highest electrons since we set merge_fsr_photons_met = false
  if(_ZUparaCorrection)
    _recoilsmear -> applyUparaCorrection(emobjs_smear, recoil_smear_beforeUparaCorr, recoil_smear, 0);

  //
  // include photons in the smeared recoil system
  // the photon response is described in EMSmear::SmearPhotonEnergy
  //
  double recoilX_orig = recoil_gen.Recoilx();
  double recoilY_orig = recoil_gen.Recoily();
  double recoilX_component = recoil_smear.Recoilx();
  double recoilY_component = recoil_smear.Recoily();

  for(int i=0; i<emobjs_smear.size(); i++) {
    if ((!(emobjs_gen[i].getIndex() == emobjs_smear[0].getIndex())) && (!(emobjs_gen[i].getIndex() == emobjs_smear[1].getIndex()))){
      recoilX_orig += emobjs_gen[i].ppx();
      recoilY_orig += emobjs_gen[i].ppy();
    }
    if (i > 1){
      if (!_ZsimuFSRcracks) {
	recoilX_component += emobjs_smear[i].ppx();
	recoilY_component += emobjs_smear[i].ppy();
      } else {
	float deteta=emobjs_smear[i].deteta();
	float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
	  recoilX_component += emobjs_smear[i].ppx();
	  recoilY_component += emobjs_smear[i].ppy();
	}
      }
    }
  }
  // reset smeared recoil
  recoil_smear.SetRecoil(recoilX_component, recoilY_component);
  
  double metXFromMBZB = _recoilsmear->recoilX_SoftComponent();
  double metYFromMBZB = _recoilsmear->recoilY_SoftComponent();

  // generator level histograms
  if (_makeZGenPlots) {
    PMCSParticle MCZ = pmcsevent.GetWZBoson();
    fillMCZHistograms(MCZ, "gen_", evtweight);
    if( passesEMCuts(emobjs_gen, vtx_gen, dummy) &&
        passesRecoilCuts(emobjs_gen, recoil_gen, met_gen, dummy) ) {
      PMCSZCand zcand_gen(emobjs_gen[0], emobjs_gen[1], recoil_gen, met_gen);
      fillZCandHistograms(zcand_gen, vtx_gen, "gen_", evtweight, zcand_gen.PhiModCategory());
      fillZCandRecoilHistograms(zpT_gen, zphi_gen, ptee_gen , dphi_ee_gen, zmass_gen , deta_ee_gen , emobjs_smear, emobjs_gen, emobjs_raw_gen, recoil_gen, zcand_gen, "gen_", evtweight, dummy);
    }//same event selection criteria as for smeared objects
  }//make plots if requested

  if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
    _recoilsmear->ApplyTopBottomAsym(recoilX_component, recoilY_component);
    recoil_smear.SetRecoil(recoilX_component, recoilY_component);
  }
  // met before corrections for the two highest pT electrons
  PMCSMet met_smear = PMCSMet(emobjs_smear, recoil_smear);
  // will overwrite met_smear if there are at least 2 EM objects
  if( emobjs_smear.size()>=2 ) {
    double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
    double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
    met_smear.SetMet(metX_component, metY_component);
  }

  
  // make generator level root file for events with at least two EM Objects, no offline selection cuts
  // here met should be already corrected for the two highest pT electrons
  if (_makegenROOTfile_for_ZFIT  && (emobjs_gen.size() >= 2)  ) {
    PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);
    fillZFitFile(pmcsevent.GetEvtWeight(),pmcsevent.GetWZBoson().Mass(), zcand,emobjs_gen,recoilX_orig, recoilY_orig, metXFromMBZB, metYFromMBZB,0., 3, luminosity, vtx_gen.vtxz(),_recoilsmear->scalarEt() );
    Zfittree->Fill();
  }

  if(_makeU_parControlPlot) {
    //if ((emobjs_smear.size() >= 2)&&(!emobjs_smear[0].IsLostInAcrack())&&(!emobjs_smear[1].IsLostInAcrack())) {
    // move the Fiducial cuts inside MakeU_parControlPlot() for 2-elec correlation study.  (by Hengne)
    if (emobjs_smear.size() >= 2) {
      ZAnalysis::MakeU_parControlPlot(emobjs_smear, recoil_smear, met_smear, vtx_gen, evtweight, dummy);
      return;
    }
  }
  double Trigger_Version; 
  int passNonUParaEffs;
  int ncuts=0;

  bool passEM = kFALSE;
  if (!_pedanticRandomEM){

    passEM=passesEMCuts(emobjs_smear,
			vtx_gen,
			dummy,
			&ncuts,
			&Trigger_Version,
			&passNonUParaEffs, false,externalRndm);
  }
  else{

    passEM=passesEMCuts(emobjs_smear,
			vtx_gen,
			dummy,
			&ncuts,
			&Trigger_Version,
			&passNonUParaEffs);
  }
  bool CUT_two_electrons = (ncuts>0);
  // at least two EM Objects

  int type = -1; 
  if( CUT_two_electrons) {
    PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);

    // the following line is mistakely removed in version 1.225 and added back in version 1.229
    type = zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);
        
    // use tag probe method to test pT dependence of all selection criteria
    if(_StudyEfficiencies) TagProbeEffStudies(emobjs_smear, vtx_gen, recoil_smear, met_smear, dummy, evtweight);
    if(_StudyEfficiencyBIASES) TagProbeEffBIASESStudies(emobjs_smear, vtx_gen, recoil_smear, met_smear, dummy, evtweight);


    if(_StudyEfficienciesTruth) TruthEffStudies(emobjs_smear, vtx_gen, recoil_smear, met_smear, dummy);

    // study electron system
    // electron pT and recoil pT cut applied on each function
    // determine electron energy scale
    if(_EnergyScaleStudy) {
      bool doIt = true;
      if(_consistency_check) {
        int runNo = pmcsevent.GetRunNo();
        double scalarEt_All = _recoilsmear->scalarEt();
        doIt = wz_utils::passCutEvent(_cut_under_study, _invert_cut,
                                      runNo, _runNo_lowcut, _runNo_highcut,
                                      luminosity, _InstLumi_lowcut, _InstLumi_highcut,
                                      scalarEt_All, _ScalarEt_lowcut, _ScalarEt_highcut,
				      recoil_smear.RecoilPhi(), _RecoilPhi_lowcut, _RecoilPhi_highcut);
	if (_cut_under_study.Contains("DetEtaCateg_cut")) {
          doIt = doIt && (zcand.DetEtaCategory(emobjs_smear[0].deteta(), emobjs_smear[1].deteta(), _CutEtaCC, _phimodcut, _ApplyTrkPhiModCut) == _DetEtaCateg_cut);
        }
      }
      if (doIt) {
	if (_EnergyScaleStudyJan) energyScaleStudyJan(emobjs_gen, vtx_gen, emobjs_smear, met_smear, recoil_smear, dummy, &external_upara_rnd1, &external_upara_rnd2, &external_SET_rnd[0],  evtweight,externalRndm);
	else energyScaleStudy(emobjs_gen, vtx_gen, emobjs_smear, met_smear, recoil_smear, dummy, evtweight);
      }
    }
    if ((_momentumScaleStudy || _radLengthStudy)) {
      if (passNonUParaEffs && (passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy)) &&  (ncuts> 3 )) {
	if(_momentumScaleStudy){
	  momentumScaleStudy(emobjs_gen,emobjs_smear,dummy, evtweight);	
	}
	if(_radLengthStudy){
	  radLengthStudy(emobjs_gen,emobjs_smear, dummy, evtweight );
	}
      }
    }
    // determine electron energy resolution
    if(_EnergyResolutionStudy) {
      if (_emsmear->doCCscale_dep()) {
	cout<<"You are trying to run a fit for EM scale and offset with lumi- and/or upara- dependence enabled in the EMSmear object. This will not work."<<endl;
	assert(0);
      }
      if (_EnergyResolutionStudyJan) energyResolutionStudyJan(emobjs_gen, vtx_gen, emobjs_smear, met_smear, recoil_smear, dummy,&external_upara_rnd1, &external_upara_rnd2, &external_SET_rnd[0],  evtweight,externalRndm);
      else energyResolutionStudy(emobjs_gen, vtx_gen, emobjs_smear, met_smear, dummy, evtweight);
    }

    // templates for parameters describing electron resolution and response
    // near phi-cracks (Crystal Ball tail parameters or PeakShift parameters)
    if(_MakeCrackCBtemplates ) {
       PMCSZCand zcand_gen(emobjs_gen[0], emobjs_gen[1], recoil_gen, met_gen);
       MakeCrystalBallParameterTemplates(emobjs_gen, vtx_gen, emobjs_smear, met_smear, recoil_smear, dummy, evtweight, externalRndm);
    }


    if(passEM) {


      ////////////////////////////////////////
      //
      // Now fill histograms for CC-CC recoil templates.
      //
      ////////////////////////////////////////

      if( _HadronicTemplateNumber && type==0 ) {
	
	// sort(emobjs_smear.begin(), emobjs_smear.end(), ComparePt);
	// fillTemplateRecoilHistograms(emobjs_smear, recoil_gen, vtx_gen, zcand, dummy, "smeared_", evtweight);  
	fillTemplateRecoilHistograms(emobjs_smear, recoil_gen, vtx_gen, dummy, "smeared_", evtweight,
				     pmcsevent, &external_upara_rnd1, &external_upara_rnd2, &external_SET_rnd[0]);  
      }


      if( _TB_Correction_Option==1 && _TBStudy) {
	if (type==0){
	  if (!_Top_Bottom_Apply_Last){
	    TBStudy(emobjs_noupara, recoil_smear, dummy, &external_upara_rnd1, &external_upara_rnd2, &external_SET_rnd[0], evtweight, luminosity, vtx_gen ,externalRndm  ); 
	  }	
	  else{
	    TBStudy(emobjs_smear, recoil_smear, dummy, &external_upara_rnd1, &external_upara_rnd2, &external_SET_rnd[0], evtweight, luminosity, vtx_gen,externalRndm); 
	  }
	}
      }
      
      if (_pedanticRandomRecoil){ 
	// pedanticRandomRecoil uses diferent random numbers for the standard and template pathways
	external_upara_rnd1 = dummy->Uniform(0., 1.);
	external_upara_rnd2 = dummy->Uniform(0., 1.);
	for (int isetrndm = 0; isetrndm < 2; ++isetrndm){
	  external_SET_rnd[isetrndm]= dummy->Uniform(0., 1.);
	}
      }
      bool passUparaEff=false;
      bool passRECOIL=passesRecoilCuts(emobjs_smear,
				       recoil_smear,
				       met_smear,
				       dummy,
				       &ncuts,
				       &passUparaEff, // NULL,
				       false,
				       &external_upara_rnd1, 
				       &external_upara_rnd2,
				       &external_SET_rnd[0]);

//             ///////////////////// DEBUG //////////////////////////
//             //
//             if(type==0) {
//       	double znunu_hard_recoil_pT, znunu_hard_recoil_phi;
//       	double smeared_hard_recoil_pT, smeared_hard_recoil_phi;
//       	double generated_hard_recoil_pT, generated_hard_recoil_phi;
//       	_recoilsmear->GetLastHardRecoil_Method_B(&generated_hard_recoil_pT,
//       						&generated_hard_recoil_phi,
//       						&znunu_hard_recoil_pT, 
//       						&znunu_hard_recoil_phi,
//       						&smeared_hard_recoil_pT, 
//       						&smeared_hard_recoil_phi);
//       	cout << "++++ EVENT=" << counter << "PASSED DEFAULT RECOIL CUTS:" << endl;
//       	cout << "++++ U_parallel Eff:   PASSED=" << passUparaEff 
//       	     << ", RND1=" << external_upara_rnd1 
//       	     << ", RND2=" << external_upara_rnd2 << endl;
//       	cout << "++++ Smeared RECOIL:   PASSED=" << passRECOIL 
//       	     << ", Px=" << recoil_smear.Recoilx() 
//       	     << ", Py=" << recoil_smear.Recoily() << endl;
//       	cout << "++++ GEN HARD RECOIL:          Pt=" << generated_hard_recoil_pT
//       	     << ", Phi=" << generated_hard_recoil_phi << endl;  
//       	cout << "++++ ZNUNU HARD RECOIL:        Pt=" << znunu_hard_recoil_pT
//       	     << ", Phi=" << znunu_hard_recoil_phi << endl;  
//       	cout << "++++ ZEE HARD RECOIL:          Pt=" << smeared_hard_recoil_pT
//       	     << ", Phi=" << smeared_hard_recoil_phi << endl;  
//             }
//             //
//             ///////////////////// DEBUG //////////////////////////

      // get scalar Et
      double scalarEt_All = _recoilsmear->scalarEt();
      double scalarEt_ZB = _recoilsmear->scalarEt_ZB();
      double scalarEt_ZB_NoScale = _recoilsmear->scalarEt_ZB_NoScale();

      if( passRECOIL ) {

	//
	// now we can do some systematic studies by varying the cuts
	//
	if(_consistency_check) {
	  int runNo = pmcsevent.GetRunNo();
	  double UPara1 = zcand.UPara1();
	  double UPara2 = zcand.UPara2();
	  double ZElecEta1 = zcand.GetElec1().eta();
	  double ZElecEta2 = zcand.GetElec2().eta();
	  double ZElecDetEta1 = zcand.GetElec1().deteta();
	  double ZElecDetEta2 = zcand.GetElec2().deteta();
	  double ZElecPhiMod1 = fmod(16.*(zcand.GetElec1()).detphi()/TMath::Pi(), 1.0);
	  double ZElecPhiMod2 = fmod(16.*(zcand.GetElec2()).detphi()/TMath::Pi(), 1.0);
	  double ZElectrkPhiMod1 = fmod(16.*(zcand.GetElec1()).trkphiem3()/TMath::Pi(), 1.0);
	  double ZElectrkPhiMod2 = fmod(16.*(zcand.GetElec2()).trkphiem3()/TMath::Pi(), 1.0);
	  double ZElecPt1 = zcand.GetElec1().ppt();
	  double ZElecPt2 = zcand.GetElec2().ppt();

	  bool passCut_under_study_Elec1 =  wz_utils::passCut(_cut_under_study, _invert_cut,
							      runNo, _runNo_lowcut, _runNo_highcut,
							      luminosity, _InstLumi_lowcut, _InstLumi_highcut,
							      scalarEt_All, _ScalarEt_lowcut, _ScalarEt_highcut,
							      ZElecEta1, _ElecEta_cut,
							      ZElecDetEta1, _ElecDetEta_lowcut, _ElecDetEta_highcut,
							      ZElectrkPhiMod1, _ElecPhiMod_cut,
							      UPara1, _UPara_lowcut, _UPara_highcut,
							      ZElecPt1, _ElecPt_lowcut, _ElecPt_highcut,
							      zcand.GetElec1().phi(), _ElecPhi_lowcut, _ElecPhi_highcut,
							      recoil_smear.RecoilPhi(), _RecoilPhi_lowcut, _RecoilPhi_highcut);
	  bool passCut_under_study_Elec2 =  wz_utils::passCut(_cut_under_study, _invert_cut,
							      runNo, _runNo_lowcut, _runNo_highcut,
							      luminosity, _InstLumi_lowcut, _InstLumi_highcut,
							      scalarEt_All, _ScalarEt_lowcut, _ScalarEt_highcut,
							      ZElecEta2, _ElecEta_cut,
							      ZElecDetEta2, _ElecDetEta_lowcut, _ElecDetEta_highcut,
							      ZElectrkPhiMod2, _ElecPhiMod_cut,
							      UPara2, _UPara_lowcut, _UPara_highcut,
							      ZElecPt2, _ElecPt_lowcut, _ElecPt_highcut,
							      zcand.GetElec2().phi(), _ElecPhi_lowcut, _ElecPhi_highcut,
							      recoil_smear.RecoilPhi(), _RecoilPhi_lowcut, _RecoilPhi_highcut);

	  bool passCut_DetEtaCateg = true;
	  if (_cut_under_study.Contains("DetEtaCateg_cut")) {
	    passCut_DetEtaCateg = (zcand.DetEtaCategory(emobjs_smear[0].deteta(), emobjs_smear[1].deteta(), _CutEtaCC, _phimodcut, _ApplyTrkPhiModCut) == _DetEtaCateg_cut);
	  }

	  if(!((passCut_under_study_Elec1 || passCut_under_study_Elec2) && passCut_DetEtaCateg)) return;
	}		
	
// 	///////////////////// DEBUG //////////////////////////
// 	//
// 	cout << "++++ EVENT=" << counter << ": AFTER passesRecoilCuts:"
// 	     << " Total SET=" << scalarEt_All 
// 	     << ", passRECOIL=" << passRECOIL << ", ZCand_type=" << type << endl;
// 	//
// 	///////////////////// DEBUG //////////////////////////

	////////////////////////////////////////
	//
	// Fill histograms for this event using 
	// default recoil parameters.
	//
	////////////////////////////////////////


	// MW
	if(_MakeEleakTable && (type==0)){
	  
	  double eleak = emobjs_smear[0].EnergyLeakage();
	  int LeakBin = (int)((emobjs_smear[0].peta())/0.2)+7;
	  if (LeakBin<0) LeakBin=0;
	  if (LeakBin>13) LeakBin=13;
	  _LeakSum[LeakBin]+=eleak;
	  _LeakCount[LeakBin]++;
	  _overallLeakSum+=eleak;
	  _overallLeakCount++;

	  eleak = emobjs_smear[1].EnergyLeakage();
	  LeakBin = (int)((emobjs_smear[1].peta())/0.2)+7;
	  if (LeakBin<0) LeakBin=0;
	  if (LeakBin>13) LeakBin=13;
	  _LeakSum[LeakBin]+=eleak;
	  _LeakCount[LeakBin]++;
	  _overallLeakSum+=eleak;
	  _overallLeakCount++;

	}
	
	_histos.Fill1D("smeared_ZCandpT_gen_selected", zpT_gen);
	if(type==0) _histos.Fill1D("smeared_ZCandpT_gen_selected_CCCC", zpT_gen);
	if(type==1) _histos.Fill1D("smeared_ZCandpT_gen_selected_CCEC", zpT_gen);
	if(type==2) _histos.Fill1D("smeared_ZCandpT_gen_selected_ECEC", zpT_gen);

	// fill scalar Et histograms
	_histos.Fill1D("smeared_hZcandScalarEt_All", scalarEt_All, evtweight);
	if(type==0) _histos.Fill1D("smeared_hZcandScalarEt_CCCC", scalarEt_All, evtweight);
	if(type==1) _histos.Fill1D("smeared_hZcandScalarEt_CCEC", scalarEt_All, evtweight);
	if(type==2) _histos.Fill1D("smeared_hZcandScalarEt_ECEC", scalarEt_All, evtweight);

        // fill scalar Et of ZB histograms
        _histos.Fill1D("smeared_hZcandScalarEtZB_All", scalarEt_ZB, evtweight);
        if(type==0) _histos.Fill1D("smeared_hZcandScalarEtZB_CCCC", scalarEt_ZB, evtweight);
        if(type==1) _histos.Fill1D("smeared_hZcandScalarEtZB_CCEC", scalarEt_ZB, evtweight);
        if(type==2) _histos.Fill1D("smeared_hZcandScalarEtZB_ECEC", scalarEt_ZB, evtweight);

        // fill scalar Et of ZB no _scale_zb histograms
        _histos.Fill1D("smeared_hZcandScalarEtZBNoScale_All", scalarEt_ZB_NoScale, evtweight);
        if(type==0) _histos.Fill1D("smeared_hZcandScalarEtZBNoScale_CCCC", scalarEt_ZB_NoScale, evtweight);
        if(type==1) _histos.Fill1D("smeared_hZcandScalarEtZBNoScale_CCEC", scalarEt_ZB_NoScale, evtweight);
        if(type==2) _histos.Fill1D("smeared_hZcandScalarEtZBNoScale_ECEC", scalarEt_ZB_NoScale, evtweight);

	_histos.Fill1D("smeared_hZcandSqrtScalarEt_All", sqrt(scalarEt_All), evtweight);
	if(type==0) _histos.Fill1D("smeared_hZcandSqrtScalarEt_CCCC", sqrt(scalarEt_All), evtweight);
	if(type==1) _histos.Fill1D("smeared_hZcandSqrtScalarEt_CCEC", sqrt(scalarEt_All), evtweight);
	if(type==2) _histos.Fill1D("smeared_hZcandSqrtScalarEt_ECEC", sqrt(scalarEt_All), evtweight);
	
	// fill scalar Et for different generator level Z pT bins and smeared Z pT bins
	if(type == 0) {

	  int bin_zpT = wz_utils::pTee_Eta_Bin(zcand.ppt());
	  char zpT_bin_sn[10]; sprintf(zpT_bin_sn, "%d", bin_zpT);
	  
	  int bin_zpT_gen = wz_utils::pTee_Eta_Bin(zpT_gen);
          char zpT_gen_bin_sn[10]; sprintf(zpT_gen_bin_sn, "%d", bin_zpT_gen);

	  // MW
 	  // fill SET histograms for different electron pTs...
 	  // calculate electron pT bin for electron 1
 	  double pTe = emobjs_smear[0].ppt(); 
 	  double EpToverSET = 0;
 	  if(scalarEt_All>0) EpToverSET = pTe/scalarEt_All;
 	  int pTebin=(int)((pTe-25)/5);
 	  if( (pTe>50) && (pTe<60) ) pTebin=5;
 	  if(pTe>60) pTebin=6;
 	  char pTebin_sn[10]; sprintf(pTebin_sn, "%d", pTebin);

          if (pTebin>=0){
 	    _histos.Fill1D(string("smeared_hZcandScalarEt_ElecPtBin_")+pTebin_sn, scalarEt_All, evtweight);
 	    _histos.Fill1D(string("smeared_hZcandSEToverEpt_ElecPtBin_")+pTebin_sn, EpToverSET, evtweight);
          }
 	  if(pTe>50) _histos.Fill1D("smeared_hZcandScalarEt_Tail", scalarEt_All, evtweight);
 	  if(pTe>50) _histos.Fill1D("smeared_hZcandSEToverEpt_Tail", EpToverSET, evtweight);
 
 	  // calculate electron pT bin for electron 2
 	  pTe = emobjs_smear[1].ppt(); 
 	  EpToverSET = 0;
 	  if(scalarEt_All>0) EpToverSET = pTe/scalarEt_All;
 	  pTebin=(int)((pTe-25)/5);
 	  if( (pTe>50) && (pTe<60) ) pTebin=5;
 	  if(pTe>60) pTebin=6;  
 	  sprintf(pTebin_sn, "%d", pTebin);
 
          if (pTebin>=0){
             _histos.Fill1D(string("smeared_hZcandScalarEt_ElecPtBin_")+pTebin_sn, scalarEt_All, evtweight);
             _histos.Fill1D(string("smeared_hZcandSEToverEpt_ElecPtBin_")+pTebin_sn, EpToverSET, evtweight);
          }
 	  if(pTe>50) _histos.Fill1D("smeared_hZcandScalarEt_Tail", scalarEt_All, evtweight);
 	  if(pTe>50) _histos.Fill1D("smeared_hZcandSEToverEpt_Tail", EpToverSET, evtweight);
 	  //MW

          if(bin_zpT>=0 && bin_zpT<10) {
	    _histos.Fill1D(string("smeared_hZcandScalarEt_CCCC_bin_")+zpT_bin_sn, scalarEt_All, evtweight);
            _histos.Fill1D(string("smeared_hZcandSqrtScalarEt_CCCC_bin_")+zpT_bin_sn, sqrt(scalarEt_All), evtweight);
          }
        
          if(bin_zpT_gen>=0 && bin_zpT_gen<10) {
	    _histos.Fill1D(string("smeared_hZcandScalarEt_CCCC_genZPt_bin_")+zpT_gen_bin_sn, scalarEt_All, evtweight);
            _histos.Fill1D(string("smeared_hZcandSqrtScalarEt_CCCC_genZPt_bin_")+zpT_gen_bin_sn, sqrt(scalarEt_All), evtweight); 	  
          }
	}

	// fill luminosity histograms
	_histos.Fill1D("smeared_hZcandLumi_All", luminosity, evtweight);
	if(type==0) {_histos.Fill1D("smeared_hZcandLumi_CCCC", luminosity, evtweight);
	  _histos.Fill2D("smeared_hZcandScalarEt_V_Lumi2D_CCCC",luminosity,scalarEt_All, evtweight);
	  _histos.FillProfile("smeared_hZcandScalarEt_V_Lumi_CCCC",luminosity, scalarEt_All, evtweight );
	}
	if(type==1) _histos.Fill1D("smeared_hZcandLumi_CCEC", luminosity, evtweight);
	if(type==2) _histos.Fill1D("smeared_hZcandLumi_ECEC", luminosity, evtweight);
	PMCSZCand zcand_gen(emobjs_gen[0], emobjs_gen[1], recoil_gen, met_gen);
	int ZBRunno =  pmcsevent.GetRunNo();
	int ZBEvtno =  pmcsevent.GetEvtNo();
	if 	(_MakeOverlayEventList){
	  std::ofstream olistfile("ZMC_overlay_events.txt",ios::app);
	  olistfile << ZBRunno << "  " << ZBEvtno << std::endl;
	  olistfile.close();
	}
	
	//	if (wz_utils::pTee_Eta_Bin(zcand.ppt()) ==0)
//	  if ((abs(zcand.p_ee()+zcand.recoil()) < 15.) && (abs(zcand.p_ee()+zcand.recoil()) > 10.))
//	    if (type==0){
	fillZCandHistograms(zcand, vtx_gen, "smeared_", evtweight, zcand_gen.PhiModCategory());
	
	//hack is over
	// 	///////////////////// DEBUG //////////////////////////
	// 	//
// 	if(type == 0) {
// 	  counterCCCC++;
// 	  double eta_imbalance = zcand.p_ee()+zcand.recoil();
// 	  double xi_imbalance = zcand.p_ee2()+zcand.recoil2();
// 	  double hard_SET=_recoilsmear->scalarEt_hard();
// 	  double smear_SET=_recoilsmear->scalarEt();
// 	  double gen_pt,gen_phi,znunu_pt,znunu_phi,smear_pt,smear_phi;
// 	  _recoilsmear->GetLastHardRecoil_Method_B(&gen_pt,&gen_phi,&znunu_pt,&znunu_phi,&smear_pt,&smear_phi);
// 	  cout << "++++ Z candidate CCCC EVENT=" << counterCCCC << endl
// 	       << "     Generated:     pT="<<gen_pt  <<", Dphi="<<0.0<<endl
// 	       << "     Hard:          pT="<<znunu_pt<<", Dphi="<<kinem::delta_phi(znunu_phi, gen_phi)<<", SET="<<hard_SET<<endl
// 	       << "     Smear:         pT="<<smear_pt<<", Dphi="<<kinem::delta_phi(smear_phi, gen_phi)<<", SET="<<smear_SET<<endl
// 	       << "     Before U||:    pT="<<recoil_smear_beforeUparaCorr.Recoil()<<endl
// 	       << "     Aft.U||:       pT="<<recoil_smear_afterUparaCorr_beforePhotonMerge.Recoil()<<endl
// 	       << "     Aft.U||+gamma: pT="<<recoil_smear.Recoil()
// 	       << ", (from zcand: pT="<<zcand.MagRecoil()<<", Dphi="<<kinem::delta_phi(TMath::Pi(), zcand.DeltaPhi_Z_Recoil())<<")"<<endl
// 	       << "     Eta-imb="<<eta_imbalance<<", Xi-imb="<<xi_imbalance<<endl;
// 	}
// 	//
// 	///////////////////// DEBUG //////////////////////////

	//if (ZPt_Projected_bin == 0)
	//  if (abs(zcand.p_ee()+zcand.recoil()) > 15.)
	//    if (type==0)
              fillZCandRecoilHistograms(zpT_gen, zphi_gen, ptee_gen , dphi_ee_gen, zmass_gen , deta_ee_gen ,  emobjs_smear, emobjs_gen, emobjs_raw_gen, recoil_gen, zcand, "smeared_", evtweight, dummy);
//	    }

        if (_FillZBRunNumTree){
          _ZBRunNumTree->Fill();
        }

	// optional ASCII printouts
	if (_makeASCIIfile_LumiEff) {
	  if (type==0) {
	    cout<<"Lumi1 "<<_recoilsmear->GetEvtIDrun()<<" "<<_recoilsmear->GetEvtIDevent()<<" "
		<<luminosity<<" "<<scalarEt_All<<" "<<zcand.GetElec1().ppt()<<" "<<zcand.GetElec1().deteta()<<" "<<zcand.GetElec1().peta()<<" "
		<<zcand.UPara1()<<" "<<zcand.GetRecoil().Recoil()<<endl;
	    cout<<"Lumi2 "<<_recoilsmear->GetEvtIDrun()<<" "<<_recoilsmear->GetEvtIDevent()<<" "
		<<luminosity<<" "<<scalarEt_All<<" "<<zcand.GetElec2().ppt()<<" "<<zcand.GetElec2().deteta()<<" "<<zcand.GetElec2().peta()<<" "
		<<zcand.UPara2()<<" "<<zcand.GetRecoil().Recoil()<<endl;
	  }
	}
	//
	if (_makeASCIIfile_Eresponse) {
	  if (type==0) {
            PMCSEMObj h_emobj[2], h_emobj_gen[2], h_emobj_gen_raw[2], h_emobj_gen_raw_wfsr[2];
            h_emobj[0] = zcand.GetElec1();
            h_emobj[1] = zcand.GetElec2();
            for (int hh=0; hh<emobjs_gen.size(); hh++){
              if (emobjs_gen[hh].getIndex() == h_emobj[0].getIndex()) h_emobj_gen[0] = emobjs_gen[hh];
              if (emobjs_gen[hh].getIndex() == h_emobj[1].getIndex()) h_emobj_gen[1] = emobjs_gen[hh];
            }
            double dRmin1(1000.), dRmin2(1000.);
            for (int hh=0; hh<emobjs_raw_gen.size(); hh++){
              double dR1 = emobjs_raw_gen[hh].GetLorentzVect().DeltaR(h_emobj_gen[0].GetLorentzVect());
              double dR2 = emobjs_raw_gen[hh].GetLorentzVect().DeltaR(h_emobj_gen[1].GetLorentzVect());
              if (dR1< dRmin1){
                dRmin1 = dR1;
                h_emobj_gen_raw[0] = emobjs_raw_gen.at(hh);
              }
              if (dR2< dRmin2){
                dRmin2 = dR2;
                h_emobj_gen_raw[1] = emobjs_raw_gen.at(hh);
              }
            }
            dRmin1 = 1000.; dRmin2 = 1000.;
            for (int hh=0; hh<emobjs_raw_gen_wfsr.size(); hh++){
              double dR1 = emobjs_raw_gen_wfsr[hh].GetLorentzVect().DeltaR(h_emobj_gen[0].GetLorentzVect());
              double dR2 = emobjs_raw_gen_wfsr[hh].GetLorentzVect().DeltaR(h_emobj_gen[1].GetLorentzVect());
              if (dR1< dRmin1){
                dRmin1 = dR1;
                h_emobj_gen_raw_wfsr[0] = emobjs_raw_gen_wfsr.at(hh);
              }
              if (dR2< dRmin2){
                dRmin2 = dR2;
                h_emobj_gen_raw_wfsr[1] = emobjs_raw_gen_wfsr.at(hh);
              }
            }
            cout<<"Eresponse1 "<<_recoilsmear->GetEvtIDrun()<<" "<<_recoilsmear->GetEvtIDevent()<<" "
                <<luminosity<<" "<<scalarEt_All<<" "<<evtweight<<" "
                <<h_emobj[0].pE()<<" "<<h_emobj[0].ppx()<<" "<<h_emobj[0].ppy()<<" "<<h_emobj[0].ppz()<<" "
                <<h_emobj[0].deteta()<<" "<<h_emobj[0].trkphiem3()<<" "<<h_emobj[0].ppid()<<" "
                <<h_emobj_gen_raw[0].pE()<<" "<<h_emobj_gen_raw[0].ppx()<<" "<<h_emobj_gen_raw[0].ppy()<<" "<<h_emobj_gen_raw[0].ppz()<<" "
                <<h_emobj_gen[0].pE()<<" "<<h_emobj_gen[0].ppx()<<" "<<h_emobj_gen[0].ppy()<<" "<<h_emobj_gen[0].ppz()<<" "
                <<h_emobj_gen_raw_wfsr[0].pE()<<" "<<h_emobj_gen_raw_wfsr[0].ppx()<<" "<<h_emobj_gen_raw_wfsr[0].ppy()<<" "<<h_emobj_gen_raw_wfsr[
0].ppz()<<" "
                <<zcand.GetRecoil().Recoilx()<<" "<<zcand.GetRecoil().Recoily()<<" "
                <<recoil_gen.Recoilx()<<" "<<recoil_gen.Recoily()<<" "
                <<_recoilsmear->GetMet_MB().Px()<<" "<<_recoilsmear->GetMet_MB().Py()<<" "<<_recoilsmear->scalarEt_MB()<<" "
                <<_recoilsmear->GetMet_ZB().Px()<<" "<<_recoilsmear->GetMet_ZB().Py()<<" "<<_recoilsmear->scalarEt_ZB()<<" "
                <<h_emobj[0].UParaCorr() <<" "<< h_emobj[0].getEnergyDiffElecWithWithoutZBOverlay()<<" "<<h_emobj[0].EnergyLeakage()<< " "
                <<endl;

            cout<<"Eresponse2 "<<_recoilsmear->GetEvtIDrun()<<" "<<_recoilsmear->GetEvtIDevent()<<" "
                <<luminosity<<" "<<scalarEt_All<<" "<<evtweight<<" "
                <<h_emobj[1].pE()<<" "<<h_emobj[1].ppx()<<" "<<h_emobj[1].ppy()<<" "<<h_emobj[1].ppz()<<" "
                <<h_emobj[1].deteta()<<" "<<h_emobj[1].trkphiem3()<<" "<<h_emobj[1].ppid()<<" "
                <<h_emobj_gen_raw[1].pE()<<" "<<h_emobj_gen_raw[1].ppx()<<" "<<h_emobj_gen_raw[1].ppy()<<" "<<h_emobj_gen_raw[1].ppz()<<" "
                <<h_emobj_gen[1].pE()<<" "<<h_emobj_gen[1].ppx()<<" "<<h_emobj_gen[1].ppy()<<" "<<h_emobj_gen[1].ppz()<<" "
                <<h_emobj_gen_raw_wfsr[1].pE()<<" "<<h_emobj_gen_raw_wfsr[1].ppx()<<" "<<h_emobj_gen_raw_wfsr[1].ppy()<<" "<<h_emobj_gen_raw_wfsr[1].ppz()<<" "
                <<zcand.GetRecoil().Recoilx()<<" "<<zcand.GetRecoil().Recoily()<<" "
                <<recoil_gen.Recoilx()<<" "<<recoil_gen.Recoily()<<" "
                <<_recoilsmear->GetMet_MB().Px()<<" "<<_recoilsmear->GetMet_MB().Py()<<" "<<_recoilsmear->scalarEt_MB()<<" "
                <<_recoilsmear->GetMet_ZB().Px()<<" "<<_recoilsmear->GetMet_ZB().Py()<<" "<<_recoilsmear->scalarEt_ZB()<<" "
                <<h_emobj[1].UParaCorr() <<" "<< h_emobj[1].getEnergyDiffElecWithWithoutZBOverlay()<<" "<<h_emobj[1].EnergyLeakage()<< " "
                <<endl;

	  }
	}

	// fill root tuples for CC-CC, and CC-EC Z candidates
	if (type==0 || type ==1) {
	  if (emobjs_smear[0].ppid()==22. || emobjs_smear[1].ppid()==22.){
	    if ((emobjs_smear[0].ppt() > 25.)  ||(emobjs_smear[1].ppt() > 25.) ){
	      _histos.Fill1D("smeared_h_FMass",zcand.mass(),pmcsevent.GetEvtWeight());
	    } 
	  }
	  
	  // make root tree
	  if (_makeROOTfile_for_ZFIT && !_makegenROOTfile_for_ZFIT) {
	    fillZFitFile(evtweight,pmcsevent.GetWZBoson().Mass(), 
			 zcand,emobjs_gen, recoilX_orig, recoilY_orig, 
			 metXFromMBZB, metYFromMBZB, Trigger_Version, passNonUParaEffs, luminosity, vtx_gen.vtxz(), _recoilsmear->scalarEt());
	    Zfittree->Fill();
	  }//fill optional Z fit file
	  
	  // make ASCII file for detector studies
	  if (_makeASCIIfile_for_detector) {
	    fillDetectorStudyFile(evtweight, luminosity, pmcsevent.GetWZBoson(), zcand,
				  emobjs_gen, emobjs_smear,
				  met_gen, met_smear, recoil_gen, recoil_smear, vtx_gen);
	  }
	  
	  // fill some histograms for CCCC events
	  if (type==0) {
	    sort(emobjs_smear.begin(), emobjs_smear.end(), CompareE);
	    sort(emobjs_gen.begin(), emobjs_gen.end(), CompareE);
       sort(emobjs_raw_gen.begin(), emobjs_raw_gen.end(), CompareE);
	    _histos.Fill2D(string("smeared_hZcandElecEGen_V_Smear"),emobjs_gen[0].pE(), emobjs_smear[0].pE());
	    _histos.Fill2D(string("smeared_hZcandElecEGen_V_Smear"),emobjs_gen[1].pE(), emobjs_smear[1].pE()); 
	    sort(emobjs_smear.begin(), emobjs_smear.end(), ComparePt);
	    sort(emobjs_gen.begin(), emobjs_gen.end(), ComparePt);
       sort(emobjs_raw_gen.begin(), emobjs_raw_gen.end(), ComparePt);
	  }// only for CCCC events
	  
	  //
	  // create Z pT recoil file and later just add this recoil to W boson
	  // 
	  if(_make_recoil_file) {
	    // Determine pT and distance from the nearest electon of the two highest pT photons
	    double photpT1=0., photpT2=0., photdist1=0., photdist2=0.;
            int nPhotons=0, nElectrons=0;

	    bool isPhot = false;
            for(int ii=0; ii<emobjs_gen.size(); ii++) {
              if((emobjs_gen[ii].ppid())==22) nPhotons++;
              if(fabs(emobjs_gen[ii].ppid())==11) nElectrons++;
            }
	    
	    if( (nPhotons>0) ){
	      isPhot = true;
              double mindist;

	      for(int ip=0; ip<emobjs_gen.size(); ip++) {
                mindist=10.0;

		// for each photon
                if((emobjs_gen[ip].ppid())==22) {
                  TLorentzVector phvec(emobjs_gen[ip].ppx(), emobjs_gen[ip].ppy(), emobjs_gen[ip].ppz(), emobjs_gen[ip].pE());
                  TVector2 photpTV(emobjs_gen[ip].ppx(),emobjs_gen[ip].ppy());

		  // for each electron
                  for(int ie=0; ie<emobjs_gen.size(); ie++) {
                    if(fabs(emobjs_gen[ie].ppid())==11) {

                      TLorentzVector elvec(emobjs_gen[ie].ppx(), emobjs_gen[ie].ppy(), emobjs_gen[ie].ppz(), emobjs_gen[ie].pE());
                      double tdist = phvec.DeltaR(elvec);

                      if(tdist<mindist) mindist=tdist;
                    }
                  }
		  
                  if(emobjs_gen[ip].ppt() > photpT1){
                    photpT2=photpT1;
                    photpT1= emobjs_gen[ip].ppt();
                    photdist2=photdist1;
                    photdist1=mindist;
                  }
                  else if(emobjs_gen[ip].ppt() > photpT2) {
                    photpT2=emobjs_gen[ip].ppt();
                    photdist2=mindist;
                  }
                }
              }
	      
	    } // only for events with photon radiation 
	    
	    // calculate interesting variables
	    double Zpx_gen, Zpy_gen, Zpx_smear, Zpy_smear, recoilEx, recoilEy, Zmass;
	    Zmass = zcand.mass();
	    Zpx_smear = zcand.ppx();
	    Zpy_smear = zcand.ppy();
	    Zpx_gen = pmcsevent.GetWZBoson().ppx();
	    Zpy_gen = pmcsevent.GetWZBoson().ppy();	    
	  
	    int runno = pmcsevent.GetRunNo();
	    double upara1 = zcand.UPara1();
            double upara2 = zcand.UPara2();

	    // recoil Ex and Ey
	    recoilEx = recoil_smear_beforeUparaCorr.Recoilx();
	    recoilEy = recoil_smear_beforeUparaCorr.Recoily();
            if( use_old_ascii_files )
            {            	   
 
	    // write out generator level and smeared level Z px, py and recoil Ex, Ey
              if(isPhot){
                (*_RecoilPtASCIIfile)<<Zpx_gen<<" "<<Zpy_gen<<" "<<Zpx_smear<<" "<<Zpy_smear<<" "
                                     <<recoilEx<<" "<<recoilEy<<" "<<(_recoilsmear->scalarEt())<<" "
                                     <<upara1<<" "<<upara2<<" "<<zcand.GetElec1().ppt()<<" "
                                     <<zcand.GetElec2().ppt()<<" "<<runno<<" "
                                     <<luminosity<<" "<<Zmass<<" "<<type<<" "<<evtweight<<" "<< isPhot <<" "
                                     <<photpT1<<" "<<photdist1<<" "<<photpT2<<" "<<photdist2<<endl;
              }
              else{
                (*_RecoilPtASCIIfile)<<Zpx_gen<<" "<<Zpy_gen<<" "<<Zpx_smear<<" "<<Zpy_smear<<" "
                                     <<recoilEx<<" "<<recoilEy<<" "<<(_recoilsmear->scalarEt())<<" "
                                     <<upara1<<" "<<upara2<<" "<<zcand.GetElec1().ppt()<<" "
                                     <<zcand.GetElec2().ppt()<<" "<<runno<<" "
                                     <<luminosity<<" "<<Zmass<<" "<<type<<" "<<evtweight<<" "<< isPhot <<" 0 "
                                     <<"0 "<<"0 "<<"0"<<endl;
              }
            } // if use_old_ascii_file
            else {
              recoil_data.pTZ_gen_x = Zpx_gen ; recoil_data.pTZ_gen_y = Zpy_gen ;
              recoil_data.pTZ_smear_x = Zpx_smear ; recoil_data.pTZ_smear_y = Zpy_smear ;
              recoil_data.recoil_x = recoilEx ; recoil_data.recoil_y = recoilEy ;
              recoil_data.recoil_uncorr_x = recoil_data.recoil_x ; recoil_data.recoil_uncorr_y = recoil_data.recoil_y ;
              recoil_data.recoil_constcorr_x = recoil_data.recoil_x ; recoil_data.recoil_constcorr_y = recoil_data.recoil_y ;
              recoil_data.recoil_paramcorr_x = recoil_data.recoil_x ; recoil_data.recoil_paramcorr_y = recoil_data.recoil_y ;
              recoil_data.recoil_paramconecorr_x = recoil_data.recoil_x ; recoil_data.recoil_paramconecorr_y = recoil_data.recoil_y ;
              recoil_data.scalarET = _recoilsmear->scalarEt() ;
              recoil_data.upara_e1 = upara1 ; recoil_data.upara_e2 = upara2 ;
              recoil_data.pT_e1 = zcand.GetElec1().ppt() ; recoil_data.pT_e2 = zcand.GetElec2().ppt() ;
              recoil_data.eta_e1 = zcand.GetElec1().deteta() ; recoil_data.eta_e2 = zcand.GetElec2().deteta() ;
              recoil_data.runno = runno ; recoil_data.lumi = luminosity ; recoil_data.MZ = Zmass ;
              recoil_data.type = type ; recoil_data.eventweight = evtweight;
              recoil_data.isFSR = isPhot ;
              if(isPhot) {
                recoil_data.photpT1 = photpT1 ;
                recoil_data.photpT2 = photpT2 ;
              }
              else {
                recoil_data.photpT1 = 0 ;
                recoil_data.photpT2 = 0 ;
              }
  
              _RecoilTree->Fill();
            }
          } // create Z recoil pT file
	} // for CC-CC and CC-EC events
	
	//
	// fill weighted histogram for CCCC, CCEC and ECEC mass distributions to determine Z mass
	//
	if(_zmass_reweight) {
	  double mass=zcand.mass();
	  double elecpt1=zcand.GetElec1().ppt();
	  double elecpt2=zcand.GetElec2().ppt();
	  double Mt1 = zcand.GetMt1();
	  double Mt2 = zcand.GetMt2(); 
	  // Get Breit-Wigner Weight
	  vector<double> ReweightFactor = BreitWignerReweight(pmcsevent);
	  
	  char sn[10];
	  double massweight = evtweight;
	  
	  for(int i=0; i<ReweightFactor.size(); i++) {
	    massweight = evtweight * ReweightFactor[i];   //also include the whole event weight
	    sprintf(sn,"%d", i);
	    _histos.Fill1D(string("smeared_hZcandMass_All_Mass_")+sn, mass, massweight);
	    if(type==0){
	      _histos.Fill1D(string("smeared_hZcandMass_CCCC_Mass_")+sn, mass, massweight);
	      if(_zmass_elecpt_reweight) {
	      _histos.Fill1D(string("smeared_hZcandElecPtBoth_CCCC_Mass_")+sn, elecpt1, massweight);
	      _histos.Fill1D(string("smeared_hZcandElecPtBoth_CCCC_Mass_")+sn, elecpt2, massweight);
	      _histos.Fill1D(string("smeared_hZcandElecPt1_CCCC_Mass_")+sn, elecpt1, massweight);
	      _histos.Fill1D(string("smeared_hZcandElecPt2_CCCC_Mass_")+sn, elecpt2, massweight);
	      
	      }
	    }
	    if(type==1) _histos.Fill1D(string("smeared_hZcandMass_CCEC_Mass_")+sn, mass, massweight);
	    if(_zmass_elecpt_reweight) {	      
	      if (zcand.GetElec1().IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut)){
		_histos.Fill1D(string("smeared_hZcandMtBoth_CC_Mass_")+sn, Mt1, massweight);
		_histos.Fill1D(string("smeared_hZcandMt1_CC_Mass_")+sn, Mt1, massweight);
	      }
	      if (zcand.GetElec2().IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut)){
		_histos.Fill1D(string("smeared_hZcandMtBoth_CC_Mass_")+sn, Mt2, massweight);
		_histos.Fill1D(string("smeared_hZcandMt2_CC_Mass_")+sn, Mt2, massweight);
	      }
	    }	
	    if(type==2) _histos.Fill1D(string("smeared_hZcandMass_ECEC_Mass_")+sn, mass, massweight);
	  }
	} // Z mass reweight
	      
      } // RECOIL CUTS 
    } // EM CUTS
  } // At least 2 EM objects

  // Increase the counter for the number of events processed
  _ntotal++;
} 

void ZAnalysis::fillZFitFile(double event_weight, double gen_mass, PMCSZCand &zcand, vector<PMCSEMObj> &emobjs_gen, 
			     double recoilX_orig, double recoilY_orig, double metXFromMB, double metYFromMB, double TrigVer, Int_t effs, double luminosity, double vtxZ, double scalaret ) {
  zfit_data.mass_Z_gen = gen_mass;
  zfit_data.mass_Z_smear = zcand.mass();

  zfit_data.elec_E[0] = zcand.GetElec1().pE();
  zfit_data.elec_px[0] = zcand.GetElec1().ppx();
  zfit_data.elec_py[0] = zcand.GetElec1().ppy();
  zfit_data.elec_pz[0] = zcand.GetElec1().ppz();
  zfit_data.elec_deteta[0] = zcand.GetElec1().deteta();
  zfit_data.elec_id[0] = zcand.GetElec1().ppid();
  zfit_data.elec_upara[0] = zcand.GetElec1().UParaCorr();
  zfit_data.elec_leakage[0] = zcand.GetElec1().EnergyLeakage();
  zfit_data.elec_ZBdiff[0] = zcand.GetElec1().getEnergyDiffElecWithWithoutZBOverlay();
  zfit_data.elec_peta[0] = zcand.GetElec1().peta();
 zfit_data.elec_detphi[0] = zcand.GetElec1().detphi();
  zfit_data.RecoilX_gen = recoilX_orig;
  zfit_data.RecoilY_gen = recoilY_orig;
  zfit_data.metX_FromMB = metXFromMB;
  zfit_data.metY_FromMB = metYFromMB;

  zfit_data.elec_E[1] = zcand.GetElec2().pE();
  zfit_data.elec_px[1] = zcand.GetElec2().ppx();
  zfit_data.elec_py[1] = zcand.GetElec2().ppy();
  zfit_data.elec_pz[1] = zcand.GetElec2().ppz();
  zfit_data.elec_deteta[1] = zcand.GetElec2().deteta();
  zfit_data.elec_id[1] = zcand.GetElec2().ppid();
  zfit_data.elec_upara[1] = zcand.GetElec2().UParaCorr();
  zfit_data.elec_leakage[1] = zcand.GetElec2().EnergyLeakage();
  zfit_data.elec_ZBdiff[1] = zcand.GetElec2().getEnergyDiffElecWithWithoutZBOverlay();
  zfit_data.elec_peta[1] = zcand.GetElec2().peta();
  zfit_data.elec_detphi[1] = zcand.GetElec2().detphi();
  zfit_data.gen_elec_E[0] = 0.;
  zfit_data.gen_elec_E[1] = 0.;
  
  for(int inu=0;inu < emobjs_gen.size(); inu++){
    PMCSEMObj test_em = (emobjs_gen.at(inu));
    if (test_em.getIndex() == zcand.GetElec1().getIndex() ) {
      zfit_data.gen_elec_E[0] = test_em.pE();
      zfit_data.gen_elec_px[0] = test_em.ppx();
      zfit_data.gen_elec_py[0] = test_em.ppy();
      zfit_data.gen_elec_pz[0] = test_em.ppz();
    }
    
    if ( test_em.getIndex() == zcand.GetElec2().getIndex() )  {
      
      zfit_data.gen_elec_E[1] = test_em.pE();
      zfit_data.gen_elec_px[1] = test_em.ppx();
      zfit_data.gen_elec_py[1] = test_em.ppy();
      zfit_data.gen_elec_pz[1] = test_em.ppz();
    }
    
  }
  zfit_data.met_x = zcand.GetMet().metx();
  zfit_data.met_y = zcand.GetMet().mety();

  zfit_data.event_weight = event_weight;
  zfit_data.effFlag = (double)(effs);

  zfit_data.Trig_Ver = TrigVer;
  zfit_data.RecoilX = zcand.GetRecoilVec().Px();
  zfit_data.RecoilY = zcand.GetRecoilVec().Py();
  zfit_data.lumi = luminosity;
  zfit_data.vtxZ = vtxZ;
  zfit_data.ScalarEt = scalaret;
}

void ZAnalysis::fillDetectorStudyFile(double event_weight, double luminosity,
				      const PMCSParticle& genZ, const PMCSZCand& zcand,
				      const std::vector<PMCSEMObj>& emobjs_gen, const std::vector<PMCSEMObj>& emobjs_smear,
				      const PMCSMet& met_gen, const PMCSMet& met_smear,
				      const PMCSRecoil& recoil_gen, const PMCSRecoil& recoil_smear,
				      const PMCSVtx& vtx_gen) {
  
  (*_theASCIIfile)<<event_weight<<" "<<luminosity<<endl;
  (*_theASCIIfile)<<vtx_gen.vtxx()<<" "<<vtx_gen.vtxy()<<" "<<vtx_gen.vtxz()<<endl;
  (*_theASCIIfile)<<genZ.ppt()<<" "<<genZ.peta()<<" "<<genZ.pphi()<<" "<<genZ.pE()<<endl;
  (*_theASCIIfile)<<zcand.ppt()<<" "<<zcand.eta()<<" "<<zcand.phi()<<" "<<zcand.pE()<<" "<<zcand.mass()<<endl;
  (*_theASCIIfile)<<emobjs_gen[0].ppt()<<" "<<emobjs_gen[0].peta()<<" "<<emobjs_gen[0].pphi()<<endl;
  (*_theASCIIfile)<<emobjs_gen[1].ppt()<<" "<<emobjs_gen[1].peta()<<" "<<emobjs_gen[1].pphi()<<endl;
  (*_theASCIIfile)<<emobjs_smear[0].ppt()<<" "<<emobjs_smear[0].peta()<<" "<<emobjs_smear[0].pphi()<<" "
		  <<emobjs_smear[0].deteta()<<" "<<emobjs_smear[0].detphi()<<endl;
  (*_theASCIIfile)<<emobjs_smear[1].ppt()<<" "<<emobjs_smear[1].peta()<<" "<<emobjs_smear[1].pphi()<<" "
		  <<emobjs_smear[1].deteta()<<" "<<emobjs_smear[1].detphi()<<endl;
  (*_theASCIIfile)<<recoil_gen.Recoilx()<<" "<<recoil_gen.Recoily()<<endl;
  (*_theASCIIfile)<<recoil_smear.Recoilx()<<" "<<recoil_smear.Recoily()<<endl;
  (*_theASCIIfile)<<met_gen.metx()<<" "<<met_gen.mety()<<" "<<met_gen.scalarEt()<<endl;
  (*_theASCIIfile)<<met_smear.metx()<<" "<<met_smear.mety()<<" "<<met_smear.scalarEt()<<endl;
  
}

void ZAnalysis::fillMCZHistograms(PMCSParticle &MCZ, std::string prefix, double evtweight) {
  _histos.Fill1D((prefix + string("hMCZ_Pt")).c_str(), MCZ.ppt(), evtweight);
  _histos.Fill1D((prefix + string("hMCZ_Eta")).c_str(), MCZ.peta(), evtweight);
  _histos.Fill1D((prefix + string("hMCZ_Phi")).c_str(), MCZ.pphi(), evtweight);
  _histos.Fill1D((prefix + string("hMCZ_Mass")).c_str(), MCZ.Mass(), evtweight);
}


void ZAnalysis::fillZCandHistograms(PMCSZCand &zcand, PMCSVtx &vtx_gen, std::string prefix, double evtweight, int truephimodcat) {  
  _histos.Fill1D((prefix + string("hZcandPt")).c_str(), zcand.ppt(), evtweight);      
  _histos.Fill1D((prefix + string("hZcandEta")).c_str(), zcand.rapidity(), evtweight);
  _histos.Fill1D((prefix + string("hZcandPhi")).c_str(), zcand.phi(), evtweight);
  _histos.Fill1D((prefix + string("hZcandMass")).c_str(), zcand.mass(), evtweight);
  _histos.Fill2D((prefix + string("hZcandPt_V_Mass")).c_str(),zcand.mass(),zcand.ppt(), evtweight);
  _histos.Fill2D((prefix + string("hZcandEta_V_Mass")).c_str(),zcand.mass(),zcand.rapidity(), evtweight);

  string temp;
  bool goodCombination = true;
  int type = zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);
  if (type == 0)       temp = string("CCCC");
  else if (type == 1)  temp = string("CCEC");
  else if (type == 2)  temp = string("ECEC");
  else {
    temp = string("NULL");
    goodCombination = false;
  }

  double mass = zcand.mass();
  double phi_em_recoil0 = zcand.DeltaPhi_EM_Recoil(0);
  double phi_em_recoil1 = zcand.DeltaPhi_EM_Recoil(1);
  double phi_em_met0 = zcand.DeltaPhi_EM_Met(0);
  double phi_em_met1 = zcand.DeltaPhi_EM_Met(1);
  double phi_em1_em2 = zcand.DeltaPhi_EM_EM();
  double deta_em1_em2 = zcand.DeltaEta_EM_EM();
  double upara1 = zcand.UPara1();
  double upara2 = zcand.UPara2();

  double phi_elec_1 = zcand.GetElec1().pphi();
  double phi_elec_2 = zcand.GetElec2().pphi();
  double dphi_em1_em2 = phi_elec_2 - phi_elec_1;
  dphi_em1_em2 = dphi_em1_em2 < 0 ? dphi_em1_em2 + TMath::TwoPi() : dphi_em1_em2;


  //   std::cout << phi_elec_1 << " " << phi_elec_2 << " " << dphi_em1_em2 << std::endl;

  if (_createRootTree2 && (type==0||type==1||type==2)) {
    filltree2(zcand, vtx_gen.vtxz(), _recoilsmear->scalarEt(),_ZBrunNum,_ZBevtNum,evtweight,type);
  }
  // divide electrons into different eta and deteta categories (CC only)
  if(type==0) {
    _histos.Fill2D((prefix + string("hZcandMass_V_fZ_CCCC")).c_str(), zcand.f_CCCC(), mass, evtweight);  
    
    _histos.FillProfile((prefix + (string("hZcandMass_V_fZ_CCCC_pro"))), zcand.f_CCCC(), zcand.mass(), evtweight);

    _histos.Fill2D((prefix + string("hZcandMass_V_ElecPt_CCCC")).c_str(), mass, zcand.GetElec1().ppt(),evtweight); 
    _histos.Fill2D((prefix + string("hZcandMass_V_ElecPt_CCCC")).c_str(), mass, zcand.GetElec2().ppt(),evtweight); 
    _histos.Fill2D((prefix + string("hZcandMass_V_ElecPt2_CCCC")).c_str(), mass, zcand.GetElec2().ppt(),evtweight);  
    _histos.Fill2D((prefix + string("hZcandMass_V_ElecPt1_CCCC")).c_str(), mass, zcand.GetElec1().ppt(),evtweight); 
    
    _histos.Fill2D((prefix + string("hZcandMass_V_UPara_CCCC")).c_str(), mass, upara1,evtweight); 
    _histos.Fill2D((prefix + string("hZcandMass_V_UPara_CCCC")).c_str(), mass, upara2,evtweight); 
    _histos.Fill2D((prefix + string("hZcandMass_V_UPara2_CCCC")).c_str(), mass,upara2 ,evtweight);  
    _histos.Fill2D((prefix + string("hZcandMass_V_UPara1_CCCC")).c_str(), mass, upara1,evtweight); 

    _histos.Fill2D((prefix + string("dPhi_vs_ZPt_CCCC")).c_str(), dphi_em1_em2, zcand.ppt(), evtweight);
    
    int z_elec_eta_category = zcand.EtaCategory(zcand.GetElec1().eta(), zcand.GetElec2().eta(), _CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);
    char z_elec_eta_category_char[10];
    sprintf(z_elec_eta_category_char, "%d", z_elec_eta_category);
    
    if(z_elec_eta_category>-1) {
      _histos.Fill1D((prefix + string("hZcandMass_Category_")+z_elec_eta_category_char).c_str(), mass, evtweight);
      _histos.Fill1D((prefix + string("hZcandElecPt_Category_")+z_elec_eta_category_char).c_str(), zcand.GetElec1().ppt(), evtweight);
      _histos.Fill1D((prefix + string("hZcandElecPt_Category_")+z_elec_eta_category_char).c_str(), zcand.GetElec2().ppt(), evtweight);
      _histos.Fill1D((prefix + string("hZcandElecPt_Category_all")).c_str(), zcand.GetElec1().ppt(), evtweight);
      _histos.Fill1D((prefix + string("hZcandElecPt_Category_all")).c_str(), zcand.GetElec2().ppt(), evtweight);
      _histos.Fill1D((prefix + string("hZcandMass_Category_all")).c_str(), mass, evtweight);
      _histos.Fill2D((prefix + string("hZcandMass_V_fZ_CCCC_Category_")+z_elec_eta_category_char).c_str(), zcand.f_CCCC(), mass, evtweight);
    } // for physics eta

    int z_elec_deteta_category= zcand.EtaCategory(zcand.GetElec1().deteta(), zcand.GetElec2().deteta(), _CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);
    char z_elec_deteta_category_char[10];
    sprintf(z_elec_deteta_category_char, "%d", z_elec_deteta_category);
    if(z_elec_eta_category>-1) {
      _histos.Fill1D((prefix + string("hZcandMass_Category_DetEta_")+z_elec_deteta_category_char).c_str(), mass, evtweight);
      _histos.Fill1D((prefix + string("hZcandElecPt_Category_DetEta_")+z_elec_deteta_category_char).c_str(), zcand.GetElec1().ppt(), evtweight);
      _histos.Fill1D((prefix + string("hZcandElecPt_Category_DetEta_")+z_elec_deteta_category_char).c_str(), zcand.GetElec2().ppt(), evtweight);
      _histos.Fill2D((prefix + string("hZcandMass_V_fZ_CCCC_Category_DetEta_")+z_elec_deteta_category_char).c_str(), zcand.f_CCCC(), mass, evtweight);
    } // for detector eta
    
    int z_elec_phimod_category = zcand.PhiModCategory();
    char z_elec_phimod_category_char[10];
    sprintf(z_elec_phimod_category_char, "%d", z_elec_phimod_category);
    if(z_elec_phimod_category>-1) {
      _histos.Fill1D((prefix + string("hZcandMass_Category_PhiMod_")+z_elec_phimod_category_char).c_str(), mass, evtweight);
      _histos.Fill2D((prefix + string("hZcandMass_V_fZ_CCCC_Category_PhiMod_")+z_elec_phimod_category_char).c_str(), zcand.f_CCCC(), mass, evtweight);
    } // for phimod category 

    char z_elec_truephimod_category_char[10];
    sprintf(z_elec_truephimod_category_char, "%d", truephimodcat);
    if(truephimodcat>-1) {
      _histos.Fill1D((prefix + string("hZcandMass_Category_TruePhiMod_")+z_elec_truephimod_category_char).c_str(), mass, evtweight);
    } // for true phimod category

    if (_doFzStudy){
      //fz categories:
      int z_fz_category_coarse= zcand.FzCategory( zcand.f_CCCC());
      char z_fz_category_coarse_char[10];
      sprintf(z_fz_category_coarse_char, "%d", z_fz_category_coarse);

      int z_fz_category= zcand.FzCategoryFine( zcand.f_CCCC());
      char z_fz_category_char[10];
      sprintf(z_fz_category_char, "%d", z_fz_category);

      if(z_fz_category>-1) {
        _histos.Fill1D((prefix + string("hZcandMass_CCCC_fz_")+z_fz_category_char).c_str(), mass, evtweight);
        _histos.Fill1D((prefix + string("hZcandMass_CCCC_fz_Coarse_")+z_fz_category_coarse_char).c_str(), mass, evtweight);
        _histos.Fill1D((prefix + string("hZcandElecPt_fz_")+z_fz_category_char).c_str(), zcand.GetElec1().ppt(), evtweight);
	_histos.Fill1D((prefix + string("hZcandElecPt_fz_")+z_fz_category_char).c_str(), zcand.GetElec2().ppt(), evtweight);
	_histos.Fill1D((prefix + string("hZcandElec1Pt_fz_")+z_fz_category_char).c_str(), zcand.GetElec1().ppt(), evtweight);
	_histos.Fill1D((prefix + string("hZcandElec2Pt_fz_")+z_fz_category_char).c_str(), zcand.GetElec2().ppt(), evtweight);
	_histos.Fill1D((prefix + string("hZcandElecE_fz_")+z_fz_category_char).c_str(), zcand.GetElec1().pE(), evtweight);
	_histos.Fill1D((prefix + string("hZcandElecE_fz_")+z_fz_category_char).c_str(), zcand.GetElec2().pE(), evtweight);
	_histos.Fill1D((prefix + string("hZcandElec1E_fz_")+z_fz_category_char).c_str(), zcand.GetElec1().pE(), evtweight);
	_histos.Fill1D((prefix + string("hZcandElec2E_fz_")+z_fz_category_char).c_str(), zcand.GetElec2().pE(), evtweight);
	_histos.Fill1D((prefix + string("hZcandElecEta_fz_")+z_fz_category_char).c_str(), zcand.GetElec1().eta(), evtweight);
        _histos.Fill1D((prefix + string("hZcandElecEta_fz_")+z_fz_category_char).c_str(), zcand.GetElec2().eta(), evtweight);
        _histos.Fill1D((prefix + string("hZcandElec1Eta_fz_")+z_fz_category_char).c_str(), zcand.GetElec1().eta(), evtweight);
        _histos.Fill1D((prefix + string("hZcandElec2Eta_fz_")+z_fz_category_char).c_str(), zcand.GetElec2().eta(), evtweight);
        _histos.Fill1D((prefix + (string("hZcandElecDetEta_fz_")+z_fz_category_char)).c_str(), zcand.GetElec1().deteta(), evtweight);
        _histos.Fill1D((prefix + (string("hZcandElecDetEta_fz_")+z_fz_category_char)).c_str(), zcand.GetElec2().deteta(), evtweight);
        _histos.Fill1D((prefix + (string("hZcandElec1DetEta_fz_")+z_fz_category_char)).c_str(), zcand.GetElec1().deteta(), evtweight);
        _histos.Fill1D((prefix + (string("hZcandElec2DetEta_fz_")+z_fz_category_char)).c_str(), zcand.GetElec2().deteta(), evtweight);
      } // for fz
      
      //Energy bins for fz
      int e1_category = int(zcand.GetElec1().ppt()/5)-4;
      int e2_category = int(zcand.GetElec2().ppt()/5)-4;
      char e1_category_char[10];
      char e2_category_char[10];
      sprintf(e1_category_char, "%d", e1_category);
      sprintf(e2_category_char, "%d", e2_category);
      
      if ((e1_category>-1) && (e1_category<10)){
        _histos.Fill2D((prefix + string("hZcandMass_V_fZ_CCCC_ElecPt1_")+e1_category_char).c_str(), zcand.f_CCCC(), mass, evtweight);
	_histos.Fill2D((prefix + string("hZcandMass_V_fZ_CCCC_ElecPt_")+e1_category_char).c_str(), zcand.f_CCCC(), mass, evtweight);//either elec
      }
      if ((e2_category>-1) && (e2_category<10)){
        _histos.Fill2D((prefix + string("hZcandMass_V_fZ_CCCC_ElecPt2_")+e2_category_char).c_str(), zcand.f_CCCC(), mass, evtweight);
	_histos.Fill2D((prefix + string("hZcandMass_V_fZ_CCCC_ElecPt_")+e2_category_char).c_str(), zcand.f_CCCC(), mass, evtweight); //either elec
      }
    }        
  } // for CC-CC events
 
  if(type == 1) { // for CC-EC events
    _histos.Fill2D((prefix + string("hZcandMass_V_ElecPt_CCEC")).c_str(), mass, zcand.GetElec1().ppt(),evtweight); 
    _histos.Fill2D((prefix + string("hZcandMass_V_ElecPt_CCEC")).c_str(), mass, zcand.GetElec2().ppt(),evtweight); 
    _histos.Fill2D((prefix + string("hZcandMass_V_ElecPt2_CCEC")).c_str(), mass, zcand.GetElec2().ppt(),evtweight);  
    _histos.Fill2D((prefix + string("hZcandMass_V_ElecPt1_CCEC")).c_str(), mass, zcand.GetElec1().ppt(),evtweight);  
    
    _histos.Fill2D((prefix + string("hZcandMass_V_UPara_CCEC")).c_str(), mass, upara1,evtweight); 
    _histos.Fill2D((prefix + string("hZcandMass_V_UPara_CCEC")).c_str(), mass, upara2,evtweight); 
    _histos.Fill2D((prefix + string("hZcandMass_V_UPara2_CCEC")).c_str(), mass, upara2,evtweight);  
    _histos.Fill2D((prefix + string("hZcandMass_V_UPara1_CCEC")).c_str(), mass, upara1,evtweight);  
  } // for CC-EC events
  
  //loop twice, first time for whatever combination of electrons we have
  //second time to make "All" histograms
  for (int i=0;i<2;i++) {

    if (i==0 && goodCombination==false) {continue;}
    if (i==1) {temp = string("All");}
    _histos.Fill1D((prefix + (string("hZcandMass_")+temp)).c_str(), zcand.mass(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandPt_")+temp)).c_str(), zcand.ppt(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandPx_")+temp)).c_str(), zcand.ppx(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandPy_")+temp)).c_str(), zcand.ppy(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandPz_")+temp)).c_str(), zcand.ppz(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandAt_")+temp)).c_str(), zcand.pat(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandAl_")+temp)).c_str(), zcand.pal(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandVtx_")+temp)).c_str(),vtx_gen.vtxz(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandEta_")+temp)).c_str(),zcand.rapidity(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecTrkPt_")+temp)).c_str(), zcand.GetElec1().trkpT(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecTrkPt_")+temp)).c_str(), zcand.GetElec2().trkpT(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecTrkCalMass_")+temp)).c_str(), zcand.trkcalmass(1), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecTrkCalMass_")+temp)).c_str(), zcand.trkcalmass(2), evtweight);
    if((type == 0) && (i==0)) {
      std::stringstream out;
      out << ((int)((zcand.GetElec1().deteta()+1.1)/0.2));
      string tempbin = out.str();
      //_histos.FillProfile((string("ZBDiffvUparaCorr_")+tempbin).c_str() ,abs(zcand.GetElec1().UParaCorr() /sin(zcand.GetElec1().theta())),zcand.GetElec1().getEnergyDiffElecWithWithoutZBOverlay(),evtweight); 
      std::stringstream out2; 
      out2 << ((int)((zcand.GetElec2().deteta()+1.1)/0.2));
      tempbin = out2.str();
      //_histos.FillProfile((string("ZBDiffvUparaCorr_")+tempbin).c_str() ,abs(zcand.GetElec2().UParaCorr() /sin(zcand.GetElec2().theta())),zcand.GetElec2().getEnergyDiffElecWithWithoutZBOverlay(),evtweight); 
  }
  if (zcand.trkcalmass(1) > 70. && zcand.trkcalmass(1) < 110) {
      _histos.Fill1D((prefix + (string("hZcandElecTrkPtOvETight_")+temp)).c_str(), zcand.GetElec2().trkpT() / zcand.GetElec2().ppt(), evtweight);
      _histos.Fill1D((prefix + (string("hZcandElecTrkPtTight_")+temp)).c_str(), zcand.GetElec2().trkpT(), evtweight);
    }
    if (zcand.trkcalmass(2) > 70. && zcand.trkcalmass(2) < 110) {
      _histos.Fill1D((prefix + (string("hZcandElecTrkPtOvETight_")+temp)).c_str(), zcand.GetElec1().trkpT() / zcand.GetElec1().ppt(), evtweight);
      _histos.Fill1D((prefix + (string("hZcandElecTrkPtTight_")+temp)).c_str(), zcand.GetElec1().trkpT(), evtweight);
    }
    _histos.Fill1D((prefix + (string("hZcandElecTrkPtOvE_")+temp)).c_str(), zcand.GetElec1().trkpT() / zcand.GetElec1().ppt(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecTrkPtOvE_")+temp)).c_str(), zcand.GetElec2().trkpT() / zcand.GetElec2().ppt(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecpT_")+temp)).c_str(), zcand.GetElec1().ppt(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecpT_")+temp)).c_str(), zcand.GetElec2().ppt(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElec0pT_")+temp)).c_str(), zcand.GetElec1().ppt(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElec1pT_")+temp)).c_str(), zcand.GetElec2().ppt(), evtweight);

    _histos.Fill1D((prefix + (string("hZcandElecpX_")+temp)).c_str(), zcand.GetElec1().ppx(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecpX_")+temp)).c_str(), zcand.GetElec2().ppx(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElec0pX_")+temp)).c_str(), zcand.GetElec1().ppx(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElec1pX_")+temp)).c_str(), zcand.GetElec2().ppx(), evtweight);

    _histos.Fill1D((prefix + (string("hZcandElecpY_")+temp)).c_str(), zcand.GetElec1().ppy(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecpY_")+temp)).c_str(), zcand.GetElec2().ppy(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElec0pY_")+temp)).c_str(), zcand.GetElec1().ppy(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElec1pY_")+temp)).c_str(), zcand.GetElec2().ppy(), evtweight);

    _histos.Fill1D((prefix + (string("hZcandElecpZ_")+temp)).c_str(), zcand.GetElec1().ppz(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecpZ_")+temp)).c_str(), zcand.GetElec2().ppz(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElec0pZ_")+temp)).c_str(), zcand.GetElec1().ppz(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElec1pZ_")+temp)).c_str(), zcand.GetElec2().ppz(), evtweight);

    _histos.Fill1D((prefix + (string("hZcandElecE_")+temp)).c_str(), zcand.GetElec1().pE(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecE_")+temp)).c_str(), zcand.GetElec2().pE(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElec0E_")+temp)).c_str(), zcand.GetElec1().pE(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElec1E_")+temp)).c_str(), zcand.GetElec2().pE(), evtweight);

    _histos.Fill1D((prefix + (string("hZcandElecEta_")+temp)).c_str(), zcand.GetElec1().eta(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecEta_")+temp)).c_str(), zcand.GetElec2().eta(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecDetEta_")+temp)).c_str(), zcand.GetElec1().deteta(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecDetEta_")+temp)).c_str(), zcand.GetElec2().deteta(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecPhi_")+temp)).c_str(), zcand.GetElec1().phi(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecPhi_")+temp)).c_str(), zcand.GetElec2().phi(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecTrkPhiModEM3_")+temp)).c_str(), zcand.GetElec1().PhiMod(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecTrkPhiModEM3_")+temp)).c_str(), zcand.GetElec2().PhiMod(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecPhiTrkAtDCA_")+temp)).c_str(), zcand.GetElec1().phi(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecPhiTrkAtDCA_")+temp)).c_str(), zcand.GetElec2().phi(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecPhiTrkAtEM3_")+temp)).c_str(), zcand.GetElec1().trkphiem3(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecPhiTrkAtEM3_")+temp)).c_str(), zcand.GetElec2().trkphiem3(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecDetPhiCALO_")+temp)).c_str(), zcand.GetElec1().detphi(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecDetPhiCALO_")+temp)).c_str(), zcand.GetElec2().detphi(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecPhiMod_")+temp)).c_str(), zcand.GetElec1().PhiMod(false), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecPhiMod_")+temp)).c_str(), zcand.GetElec2().PhiMod(false), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecE_")+temp)).c_str(), zcand.GetElec1().pE(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecE_")+temp)).c_str(), zcand.GetElec2().pE(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecOpenAngle_")+temp)).c_str(), cos(zcand.Angle_EM_EM()), evtweight);
    _histos.Fill1D((prefix + (string("hZcandRecoilPt_")+temp)).c_str(), zcand.GetRecoil().Recoil(), evtweight);
   //  if (temp=="CCCC" && prefix=="smeared_"){
//       std::cout << "Recoil Phi standard: " <<  zcand.GetRecoil().RecoilPhi() << std::endl;
//       std::cout << "Met Phi standard: " <<  zcand.GetMet().metphi() << std::endl;
//       std::cout << "ZCand Phi standard: " <<  zcand.phi()<< std::endl;
//       std::cout << " Type = " << type << std::endl;


//       std::cout << "New event +++++++++++++++++++++++++++++++++++++++++" << std::endl;
//     }
    _histos.Fill1D((prefix + (string("hZcandRecoilPhi_")+temp)).c_str(), zcand.GetRecoil().RecoilPhi(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandPhi_")+temp)).c_str(), zcand.phi(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandRecoilPx_")+temp)).c_str(), zcand.GetRecoil().Recoilx(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandRecoilPy_")+temp)).c_str(), zcand.GetRecoil().Recoily(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandMET_")+temp)).c_str(), zcand.GetMet().met(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandMETx_")+temp)).c_str(), zcand.GetMet().metx(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandMETy_")+temp)).c_str(), zcand.GetMet().mety(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandMETPhi_")+temp)).c_str(), zcand.GetMet().metphi(), evtweight);

    _histos.Fill1D((prefix + (string("hZcandDeltaPhi_EM_Recoil_")+temp)).c_str(), fabs(phi_em_recoil0), evtweight);
    _histos.Fill1D((prefix + (string("hZcandDeltaPhi_EM_Recoil_")+temp)).c_str(), fabs(phi_em_recoil1), evtweight);
    _histos.Fill1D((prefix + (string("hZcandDeltaPhi_EM_Met_")+temp)).c_str(), fabs(phi_em_met0), evtweight);
    _histos.Fill1D((prefix + (string("hZcandDeltaPhi_EM_Met_")+temp)).c_str(), fabs(phi_em_met1), evtweight);
    _histos.Fill1D((prefix + (string("hZcandCosDeltaPhi_EM1_EM2_")+temp)).c_str(), cos(phi_em1_em2), evtweight);
    _histos.Fill1D((prefix + (string("hZcandDeltaEta_EM1_EM2_")+temp)).c_str(), deta_em1_em2, evtweight);

    _histos.Fill1D((prefix + (string("hZcandDeltaPhi_Recoil_Met_")+temp)).c_str(), fabs(zcand.DeltaPhi_Recoil_Met()), evtweight);
    _histos.Fill1D((prefix + (string("hZcandDeltaPhi_Z_Recoil_")+temp)).c_str(), fabs(zcand.DeltaPhi_Z_Recoil()), evtweight);
    _histos.Fill1D((prefix + (string("hZcandDeltaPhi_Z_Met_")+temp)).c_str(), fabs(zcand.DeltaPhi_Z_Met()), evtweight);

  }//end loop
}//end fillZCandHistograms()

void ZAnalysis::fillZCandRecoilHistograms(double zpT_gen, double zphi_gen, double ptee_gen , double dphi_ee_gen , double zmass_gen , double deta_ee_gen , vector<PMCSEMObj> &emobjs_smear, vector<PMCSEMObj> &emobjs_gen, vector<PMCSEMObj> &emobjs_raw_gen, PMCSRecoil &recoil_gen, PMCSZCand &zcand, std::string prefix, double evtweight, TRandom3 *dummy) {
  double m3_1 = zcand.p_ee()*zcand.p_ee() + zcand.p_ee2()*zcand.p_ee2();
  double m3_2 = (zcand.GetElec1().ppx()+zcand.GetElec2().ppx()+zcand.GetMet().metx()) * 
                (zcand.GetElec1().ppx()+zcand.GetElec2().ppx()+zcand.GetMet().metx())
              + (zcand.GetElec1().ppy()+zcand.GetElec2().ppy()+zcand.GetMet().mety()) * 
                (zcand.GetElec1().ppy()+zcand.GetElec2().ppy()+zcand.GetMet().mety());
  double Kappa = 0.507;

  double mass = zcand.mass();
  
  string temp;
  bool goodCombination = true;
  if (zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut) == 0) {
    temp = string("CCCC");
  }
  else if (zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut) == 1) {
    temp = string("CCEC");
  }
  else if (zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut) == 2) {
    temp = string("ECEC");
  }
  else {
    temp = string("NULL");
    goodCombination = false;
  }  

  double eta_balance = zcand.p_ee()+zcand.recoil()/Kappa;
  double xi_balance = zcand.p_ee2()+zcand.recoil2()/Kappa;
  double eta_imbalance = zcand.p_ee()+zcand.recoil();
  double xi_imbalance = zcand.p_ee2()+zcand.recoil2();

  double upara1 = zcand.UPara1();
  double upara2 = zcand.UPara2();
  double uperp1 = zcand.UPerp1();
  double uperp2 = zcand.UPerp2();

  //////////////////////////////////////////////////////////////////
  // Fill histograms for the default recoil smearing paramters
  //////////////////////////////////////////////////////////////////
  
  double diffelec0pt = emobjs_smear[0].ppt() - emobjs_raw_gen[0].ppt();
  double diffelec1pt = emobjs_smear[1].ppt() - emobjs_raw_gen[1].ppt();
  double diffelec0E = emobjs_smear[0].pE() - emobjs_raw_gen[0].pE();
  double diffelec1E = emobjs_smear[1].pE() - emobjs_raw_gen[1].pE();
  if( fabs( TVector2::Phi_mpi_pi( emobjs_smear[0].pphi() - emobjs_raw_gen[0].pphi() ) ) > fabs( TVector2::Phi_mpi_pi( emobjs_smear[0].pphi() - emobjs_raw_gen[1].pphi() ) ) )
  {
    diffelec0pt = emobjs_smear[0].ppt() - emobjs_raw_gen[1].ppt();
    diffelec1pt = emobjs_smear[1].ppt() - emobjs_raw_gen[0].ppt();
    diffelec0E = emobjs_smear[0].pE() - emobjs_raw_gen[1].pE();
    diffelec1E = emobjs_smear[1].pE() - emobjs_raw_gen[0].pE();
  }
  
  //loop twice, first time for whatever combination of electrons we have
  //second time to make "All" histograms
  for (int i=0;i<2;i++) {
    
    if (i==0 && goodCombination==false) {continue;}
    if (i==1) {temp = string("All");}
    
    _histos.Fill1D((prefix + (string("hZcandMCPt_")+temp)).c_str(), zpT_gen, evtweight);
    _histos.Fill1D((prefix + (string("hZcandMCPtDiff_")+temp)).c_str(), zpT_gen-zcand.ppt(), evtweight);
//     _histos.Fill1D((prefix + (string("hZcandMCPtDiff_")+temp)).c_str(), ptee_gen-zcand.ppt(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandMCPhiDiff_")+temp)).c_str(), TVector2::Phi_mpi_pi(zphi_gen-zcand.phi()), evtweight);
    _histos.Fill1D((prefix + (string("hZcandDiffMass_")+temp)).c_str(), mass-zmass_gen, evtweight);

    _histos.Fill1D((prefix + (string("hZcandDiffElecpT_")+temp)).c_str(), diffelec0pt, evtweight);
    _histos.Fill1D((prefix + (string("hZcandDiffElecpT_")+temp)).c_str(), diffelec1pt, evtweight);
    _histos.Fill1D((prefix + (string("hZcandDiffElec0pT_")+temp)).c_str(), diffelec0pt, evtweight);
    _histos.Fill1D((prefix + (string("hZcandDiffElec1pT_")+temp)).c_str(), diffelec1pt, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecGenpT_")+temp)).c_str(), emobjs_smear[0].ppt() - diffelec0pt, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecGenpT_")+temp)).c_str(), emobjs_smear[1].ppt() - diffelec1pt, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecGen0pT_")+temp)).c_str(), emobjs_smear[0].ppt() - diffelec0pt, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecGen1pT_")+temp)).c_str(), emobjs_smear[1].ppt() - diffelec1pt, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecRawGenpT_")+temp)).c_str(), emobjs_raw_gen[0].ppt(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecRawGenpT_")+temp)).c_str(), emobjs_raw_gen[1].ppt(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecRawGen0pT_")+temp)).c_str(), emobjs_raw_gen[0].ppt(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecRawGen1pT_")+temp)).c_str(), emobjs_raw_gen[1].ppt(), evtweight);

    _histos.Fill1D((prefix + (string("hZcandDiffElecE_")+temp)).c_str(), diffelec0E, evtweight);
    _histos.Fill1D((prefix + (string("hZcandDiffElecE_")+temp)).c_str(), diffelec1E, evtweight);
    _histos.Fill1D((prefix + (string("hZcandDiffElec0E_")+temp)).c_str(), diffelec0E, evtweight);
    _histos.Fill1D((prefix + (string("hZcandDiffElec1E_")+temp)).c_str(), diffelec1E, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecGenE_")+temp)).c_str(), emobjs_smear[0].pE() - diffelec0E, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecGenE_")+temp)).c_str(), emobjs_smear[1].pE() - diffelec1E, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecGen0E_")+temp)).c_str(), emobjs_smear[0].pE() - diffelec0E, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecGen1E_")+temp)).c_str(), emobjs_smear[1].pE() - diffelec1E, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecRawGenE_")+temp)).c_str(), emobjs_raw_gen[0].pE(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecRawGenE_")+temp)).c_str(), emobjs_raw_gen[1].pE(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecRawGen0E_")+temp)).c_str(), emobjs_raw_gen[0].pE(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecRawGen1E_")+temp)).c_str(), emobjs_raw_gen[1].pE(), evtweight);

    
    _histos.Fill1D((prefix + (string("hZcandDiffCosDeltaPhi_EM1_EM2_")+temp)).c_str(), cos(zcand.DeltaPhi_EM_EM()) - cos(dphi_ee_gen) , evtweight);

    _histos.Fill1D((prefix + (string("hZcandDiffDeltaEta_EM1_EM2_")+temp)).c_str(), zcand.DeltaEta_EM_EM() - deta_ee_gen , evtweight);

    _histos.Fill2D((prefix + (string("hZcandPeeReco_")+temp)).c_str(),fabs(zcand.p_ee()), zcand.recoil(), evtweight);
    _histos.Fill2D((prefix + (string("hZcandPeeBalance_")+temp)).c_str(),fabs(zcand.p_ee()), zcand.Eta_Balance(Kappa), evtweight);
    _histos.Fill2D((prefix + (string("hZcandPeeImBalance_")+temp)).c_str(),fabs(zcand.p_ee()), zcand.Eta_ImBalance(), evtweight);
    _histos.Fill2D((prefix + (string("hZcandKappa3_")+temp)).c_str(),m3_1, m3_2, evtweight);
    
    // fill eta and xi balance and imbalance histograms
    _histos.Fill1D((prefix + (string("hZcandEtaBalance_")+temp)).c_str(),zcand.p_ee() + zcand.recoil()/Kappa, evtweight);
    _histos.Fill1D((prefix + (string("hZcandXiBalance_")+temp)).c_str(),zcand.p_ee2() + zcand.recoil2()/Kappa, evtweight);
    _histos.Fill1D((prefix + (string("hZcandEtaImBalance_")+temp)).c_str(),zcand.p_ee() + zcand.recoil(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandXiImBalance_")+temp)).c_str(),zcand.p_ee2() + zcand.recoil2(), evtweight);
    
    // fill uparallel and uperpendicular
    _histos.Fill1D((prefix + (string("hZcandElecUpara_")+temp)).c_str(), upara1, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecUpara_")+temp)).c_str(), upara2, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecUperp_")+temp)).c_str(), uperp1, evtweight);
    _histos.Fill1D((prefix + (string("hZcandElecUperp_")+temp)).c_str(), uperp2, evtweight);
    
    //method 1 to determine kappa
    _histos.FillProfile((prefix + (string("hZcandPeeBalanceProfile_")+temp)).c_str(),fabs(zcand.p_ee()), zcand.Eta_Balance(Kappa), evtweight);
    
    //method 2 to determine kappa
    _histos.FillProfile((prefix + (string("hZcandPeeRecoProfile_")+temp)).c_str(), fabs(zcand.p_ee()), zcand.recoil(), evtweight);
    // _histos.FillProfile((prefix + (string("hZcandPeeRecoProfile_")+temp)).c_str(), fabs(zcand.p_ee()), zcand.recoil());
    //method 3 to determine kappa and the contribution of underlying events
    _histos.FillProfile((prefix + (string("hZcandKappa3Profile_")+temp)).c_str(), m3_1, m3_2, evtweight);
    
    _histos.FillProfile((prefix + (string("hZcand_Recoil_pT_Profile_")+temp)).c_str(), zcand.ppt(), zcand.response(), evtweight);
    _histos.Fill2D((prefix + (string("hZcand_Recoil_pT_")+temp)).c_str(), zcand.ppt(), zcand.response(), evtweight);
 
    //cuts should already be applied in main method, as with other plots
    //use this formula to be consistent with efficiency smear method and formula used in run2b1+2
    double phi_elec_1 = zcand.GetElec1().pphi();
    double phi_elec_2 = zcand.GetElec2().pphi();
    double dphi_em1_em2 = phi_elec_2 - phi_elec_1;
    dphi_em1_em2 = dphi_em1_em2 < 0 ? dphi_em1_em2 + TMath::TwoPi() : dphi_em1_em2;

    _histos.Fill1D((prefix + (string("hZcandPee_eta_")+temp)).c_str(), zcand.p_ee(), evtweight);
    _histos.Fill1D((prefix + (string("hZcandDeltaPhi_EM1_EM2_")+temp)).c_str(), dphi_em1_em2, evtweight);
    
    _histos.Fill2D((prefix + (string("hZcandDeltaPhi_EM1_EM2_Zpt_2pi_varbin_")+temp)).c_str(), dphi_em1_em2, zcand.ppt(), evtweight);
    //to run with luminosity bins, also uncomment histograms.hpp lines
    //double luminosity = emobjs_smear[0].getLumi();
    //if(luminosity < 2) _histos.Fill2D((prefix + (string("hZcandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi02_varbin_")+temp)).c_str(), dphi_em1_em2, zcand.ppt(), evtweight);
    //if(luminosity >= 2 && luminosity < 4) _histos.Fill2D((prefix + (string("hZcandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi24_varbin_")+temp)).c_str(), dphi_em1_em2, zcand.ppt(), evtweight);
    //if(luminosity >= 4 && luminosity < 6) _histos.Fill2D((prefix + (string("hZcandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi46_varbin_")+temp)).c_str(), dphi_em1_em2, zcand.ppt(), evtweight);
    //if(luminosity >= 6) _histos.Fill2D((prefix + (string("hZcandDeltaPhi_EM1_EM2_Zpt_2pi_Lumi6999_varbin_")+temp)).c_str(), dphi_em1_em2, zcand.ppt(), evtweight);
  
  }//end of for(i=... loop


  // fill eta and xi balance and imbalance, 
  // recoil and met histograms for different pT_ee bins     

  // CC-CC region only 
  if (zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut) == 0) { 

    // at least 2 EM objects
    if(emobjs_smear.size()>=2) {
      
      // PT cuts on EM objects
      if(emobjs_smear[0].ppt()>_CutEPT1_lo && 
	 emobjs_smear[1].ppt()>_CutEPT2_lo &&
	 emobjs_smear[0].ppt()<_CutEPT1_hi && 
	 emobjs_smear[1].ppt()<_CutEPT2_hi) {

	// smeared Zpt bin
	int bin = wz_utils::pTee_Eta_Bin(zcand.ppt());
	char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);
	
	// smeared ZPt projected along eta axis
	double pee_eta = zcand.p_ee();
	int ZPt_Projected_bin = wz_utils::pTee_Eta_Bin(pee_eta);
	char ZPt_Projected_bin_sn[10]; sprintf(ZPt_Projected_bin_sn, "%d", ZPt_Projected_bin);
	
	// generator level ZPt bin
	int genZPt_bin = wz_utils::pTee_Eta_Bin(zpT_gen);
	char genZPt_bin_sn[10]; sprintf(genZPt_bin_sn, "%d", genZPt_bin);
	
	// binned in smeared Z pT projected along eta axis
	if(bin >= 0) {
          _histos.Fill1D((prefix + (string("hZcandMCPtDiff_bin_")+pee_bin_sn)).c_str(), zpT_gen-zcand.ppt(), evtweight);
//           _histos.Fill1D((prefix + (string("hZcandMCPtDiff_bin_")+pee_bin_sn)).c_str(), ptee_gen-zcand.ppt(), evtweight);          
          _histos.Fill1D((prefix + (string("hZcandMCPhiDiff_bin_")+pee_bin_sn)).c_str(), TVector2::Phi_mpi_pi(zphi_gen-zcand.phi()), evtweight);
          _histos.Fill1D((prefix + (string("hZcandMass_bin_")+pee_bin_sn)).c_str(), mass , evtweight);
          _histos.Fill1D((prefix + (string("hZcandDiffMass_bin_")+pee_bin_sn)).c_str(), mass-zmass_gen , evtweight);

          _histos.Fill1D((prefix + (string("hZcandElecpT_bin_")+pee_bin_sn)).c_str(), emobjs_smear[0].ppt() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecpT_bin_")+pee_bin_sn)).c_str(), emobjs_smear[1].ppt() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElec0pT_bin_")+pee_bin_sn)).c_str(), emobjs_smear[0].ppt() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElec1pT_bin_")+pee_bin_sn)).c_str(), emobjs_smear[1].ppt() , evtweight);

          _histos.Fill1D((prefix + (string("hZcandDiffElecpT_bin_")+pee_bin_sn)).c_str(), diffelec0pt , evtweight);
          _histos.Fill1D((prefix + (string("hZcandDiffElecpT_bin_")+pee_bin_sn)).c_str(), diffelec1pt , evtweight);
          _histos.Fill1D((prefix + (string("hZcandDiffElec0pT_bin_")+pee_bin_sn)).c_str(), diffelec0pt , evtweight);
          _histos.Fill1D((prefix + (string("hZcandDiffElec1pT_bin_")+pee_bin_sn)).c_str(), diffelec1pt , evtweight);

          _histos.Fill1D((prefix + (string("hZcandElecGenpT_bin_")+pee_bin_sn)).c_str(), emobjs_smear[0].ppt() - diffelec0pt , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecGenpT_bin_")+pee_bin_sn)).c_str(), emobjs_smear[1].ppt() - diffelec1pt , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecGen0pT_bin_")+pee_bin_sn)).c_str(), emobjs_smear[0].ppt() - diffelec0pt , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecGen1pT_bin_")+pee_bin_sn)).c_str(), emobjs_smear[1].ppt() - diffelec1pt , evtweight);

          _histos.Fill1D((prefix + (string("hZcandElecRawGenpT_bin_")+pee_bin_sn)).c_str(), emobjs_raw_gen[0].ppt() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecRawGenpT_bin_")+pee_bin_sn)).c_str(), emobjs_raw_gen[1].ppt() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecRawGen0pT_bin_")+pee_bin_sn)).c_str(), emobjs_raw_gen[0].ppt() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecRawGen1pT_bin_")+pee_bin_sn)).c_str(), emobjs_raw_gen[1].ppt() , evtweight);

          _histos.Fill1D((prefix + (string("hZcandElecE_bin_")+pee_bin_sn)).c_str(), emobjs_smear[0].pE() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecE_bin_")+pee_bin_sn)).c_str(), emobjs_smear[1].pE() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElec0E_bin_")+pee_bin_sn)).c_str(), emobjs_smear[0].pE() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElec1E_bin_")+pee_bin_sn)).c_str(), emobjs_smear[1].pE() , evtweight);

          _histos.Fill1D((prefix + (string("hZcandDiffElecE_bin_")+pee_bin_sn)).c_str(), diffelec0E , evtweight);
          _histos.Fill1D((prefix + (string("hZcandDiffElecE_bin_")+pee_bin_sn)).c_str(), diffelec1E , evtweight);
          _histos.Fill1D((prefix + (string("hZcandDiffElec0E_bin_")+pee_bin_sn)).c_str(), diffelec0E , evtweight);
          _histos.Fill1D((prefix + (string("hZcandDiffElec1E_bin_")+pee_bin_sn)).c_str(), diffelec1E , evtweight);

          _histos.Fill1D((prefix + (string("hZcandElecGenE_bin_")+pee_bin_sn)).c_str(), emobjs_smear[0].pE() - diffelec0E , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecGenE_bin_")+pee_bin_sn)).c_str(), emobjs_smear[1].pE() - diffelec1E , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecGen0E_bin_")+pee_bin_sn)).c_str(), emobjs_smear[0].pE() - diffelec0E , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecGen1E_bin_")+pee_bin_sn)).c_str(), emobjs_smear[1].pE() - diffelec1E , evtweight);

          _histos.Fill1D((prefix + (string("hZcandElecRawGenE_bin_")+pee_bin_sn)).c_str(), emobjs_raw_gen[0].pE() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecRawGenE_bin_")+pee_bin_sn)).c_str(), emobjs_raw_gen[1].pE() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecRawGen0E_bin_")+pee_bin_sn)).c_str(), emobjs_raw_gen[0].pE() , evtweight);
          _histos.Fill1D((prefix + (string("hZcandElecRawGen1E_bin_")+pee_bin_sn)).c_str(), emobjs_raw_gen[1].pE() , evtweight);

          
	  _histos.Fill1D((prefix + string("hZcandEtaBalance_bin_")+pee_bin_sn).c_str(), eta_balance, evtweight);
	  _histos.Fill1D((prefix + string("hZcandXiBalance_bin_")+pee_bin_sn).c_str(), xi_balance, evtweight);
	  _histos.Fill1D((prefix + string("hZcandEtaImBalance_bin_")+pee_bin_sn).c_str(), eta_imbalance, evtweight);
	  _histos.Fill1D((prefix + string("hZcandXiImBalance_bin_")+pee_bin_sn).c_str(), xi_imbalance, evtweight);
	  _histos.Fill1D((prefix + string("hZcandPee_eta_bin_")+pee_bin_sn).c_str(), pee_eta, evtweight);
	  _histos.Fill1D((prefix + string("hZcandPt_bin_")+pee_bin_sn).c_str(), zcand.ppt(), evtweight);
	  _histos.Fill1D((prefix + string("hZcandRecoilPt_bin_")+pee_bin_sn).c_str(), zcand.GetRecoil().Recoil(), evtweight);
	  _histos.Fill1D((prefix + string("hZcandRecoilPhi_bin_")+pee_bin_sn).c_str(), zcand.GetRecoil().RecoilPhi(), evtweight);
	  _histos.Fill1D((prefix + string("hZcandPhi_bin_")+pee_bin_sn).c_str(), zcand.phi(), evtweight);
	  _histos.Fill1D((prefix + string("hZcandRecoilPx_bin_")+pee_bin_sn).c_str(), zcand.GetRecoil().Recoilx(), evtweight);
	  _histos.Fill1D((prefix + string("hZcandRecoilPy_bin_")+pee_bin_sn).c_str(), zcand.GetRecoil().Recoily(), evtweight);
	  _histos.Fill1D((prefix + string("hZcandMET_bin_")+pee_bin_sn).c_str(), zcand.GetMet().met(), evtweight);
	  _histos.Fill1D((prefix + string("hZcandMETPhi_bin_")+pee_bin_sn).c_str(), zcand.GetMet().metphi(), evtweight);
	  _histos.Fill1D((prefix + string("hZcandMETx_bin_")+pee_bin_sn).c_str(), zcand.GetMet().metx(), evtweight);
	  _histos.Fill1D((prefix + string("hZcandMETy_bin_")+pee_bin_sn).c_str(), zcand.GetMet().mety(), evtweight);
	  
	  _histos.Fill1D((prefix + string("hZcandDeltaPhi_EM_Recoil_bin_")+pee_bin_sn).c_str(), fabs(zcand.DeltaPhi_EM_Recoil(0)), evtweight);
	  _histos.Fill1D((prefix + string("hZcandDeltaPhi_EM_Recoil_bin_")+pee_bin_sn).c_str(), fabs(zcand.DeltaPhi_EM_Recoil(1)), evtweight);
	  _histos.Fill1D((prefix + string("hZcandDeltaPhi_EM_Met_bin_")+pee_bin_sn).c_str(), fabs(zcand.DeltaPhi_EM_Met(0)), evtweight);
	  _histos.Fill1D((prefix + string("hZcandDeltaPhi_EM_Met_bin_")+pee_bin_sn).c_str(), fabs(zcand.DeltaPhi_EM_Met(1)), evtweight);
     _histos.Fill1D((prefix + string("hZcandCosDeltaPhi_EM1_EM2_bin_")+pee_bin_sn).c_str(), cos(zcand.DeltaPhi_EM_EM()), evtweight);

     _histos.Fill1D((prefix + string("hZcandDeltaEta_EM1_EM2_bin_")+pee_bin_sn).c_str(), zcand.DeltaEta_EM_EM(), evtweight);
     
     _histos.Fill1D((prefix + string("hZcandDeltaPhi_Recoil_Met_bin_")+pee_bin_sn).c_str(), fabs(zcand.DeltaPhi_Recoil_Met()), evtweight);
	  _histos.Fill1D((prefix + string("hZcandDeltaPhi_Z_Recoil_bin_")+pee_bin_sn).c_str(), fabs(zcand.DeltaPhi_Z_Recoil()), evtweight);

	  // Compactify Delta Phi
	  double DeltaPhiUnfolded_Z_Recoil;
	  if (zcand.DeltaPhi_Z_Recoil(false) > 0){
	    DeltaPhiUnfolded_Z_Recoil = zcand.DeltaPhi_Z_Recoil(false) - TMath::Pi();
	  } else {
	    DeltaPhiUnfolded_Z_Recoil = zcand.DeltaPhi_Z_Recoil(false) + TMath::Pi();
	  }
	  //cout << "Filling bin " << bin << " with dphi " << DeltaPhiUnfolded_Z_Recoil << endl;

      	  _histos.Fill1D((prefix + string("hZcandDeltaPhiUnfolded_Z_Recoil_bin_")+pee_bin_sn).c_str(), DeltaPhiUnfolded_Z_Recoil, evtweight);

	  _histos.Fill1D((prefix + string("hZcandDeltaPhi_Z_Met_bin_")+pee_bin_sn).c_str(), fabs(zcand.DeltaPhi_Z_Met()), evtweight);

	  _histos.Fill1D((prefix + string("hZcandEtaImBalancePt1_bin_")+pee_bin_sn).c_str(), zcand.p_ee(), evtweight);
	  _histos.Fill1D((prefix + string("hZcandEtaImBalancePt2_bin_")+pee_bin_sn).c_str(), zcand.recoil(), evtweight);

	  _histos.Fill1D((prefix + string("hZcandOpeningAngle_bin_")+pee_bin_sn).c_str(), zcand.DeltaPhi_EM_EM(), evtweight);

	}
	
	// binned in smeared Z pT
	if(ZPt_Projected_bin >= 0) {
	  _histos.Fill1D((prefix + string("hZcandEtaImBalance_ZPt_Projected_bin_")+ZPt_Projected_bin_sn).c_str(), eta_imbalance, evtweight);
	  _histos.Fill1D((prefix + string("hZcandXiImBalance_ZPt_Projected_bin_")+ZPt_Projected_bin_sn).c_str(), xi_imbalance, evtweight);
	  _histos.Fill1D((prefix + string("hZcandPt_Projected_bin_")+ZPt_Projected_bin_sn).c_str(), pee_eta, evtweight);
	}
	
	// binned in generator level Z pT
	
	if(genZPt_bin >= 0) {
	  _histos.Fill1D((prefix + (string("hZcandMCPtDiff_genZPt_bin_")+genZPt_bin_sn)).c_str(), zpT_gen-zcand.ppt(), evtweight);
//      _histos.Fill1D((prefix + (string("hZcandMCPtDiff_genZPt_bin_")+genZPt_bin_sn)).c_str(), ptee_gen-zcand.ppt(), evtweight);

     _histos.Fill1D((prefix + string("hZcandDiffCosDeltaPhi_EM1_EM2_bin_")+genZPt_bin_sn).c_str(), cos(zcand.DeltaPhi_EM_EM()) - cos(dphi_ee_gen) , evtweight);

     _histos.Fill1D((prefix + string("hZcandDiffDeltaEta_EM1_EM2_bin_")+genZPt_bin_sn).c_str(), zcand.DeltaEta_EM_EM() - deta_ee_gen , evtweight);

	  _histos.Fill1D((prefix + string("hZcandEtaImBalance_genZPt_bin_")+genZPt_bin_sn).c_str(), eta_imbalance, evtweight);
	  _histos.Fill1D((prefix + string("hZcandXiImBalance_genZPt_bin_")+genZPt_bin_sn).c_str(), xi_imbalance, evtweight);
	  _histos.Fill1D((prefix + string("hZcandRecoilPt_genZPt_bin_")+genZPt_bin_sn).c_str(), zcand.GetRecoil().Recoil(), evtweight);
	}

      } // PT cuts on EM objects
    } // at least 2 EM objects
  } // CC-CC region only

}//end fillZCandRecoilHistograms()

////////////////////////////////////////////////////////
// Fill the template histograms 
// using same smeared electrons but different recoil 
// smearing parameters from a grid of points
////////////////////////////////////////////////////////
void ZAnalysis::fillTemplateRecoilHistograms(std::vector<PMCSEMObj> &emobjs_smear,
					     PMCSRecoil &recoil_gen,
					     PMCSVtx& vtx_gen, 
					     TRandom3 *dummy,
					     std::string prefix,
					     double evtweight,
					     PMCSEvent& pmcsevent,
					     double *external_upara_rnd1,  // use one or both random numbers while calling
					     double *external_upara_rnd2,  // passesUParaEff() for individual electrons.
					     double *external_SET_rnd) {   // used for SET efficiency
  switch(_HadronicTemplateNumber) {
  case _MOMENTUM_SCALE_:
    // determine hadronic momentum scale using Run I method
    HadronicMomentumScaleStudy(emobjs_smear, recoil_gen, vtx_gen, dummy, prefix, evtweight,
			       external_upara_rnd1, external_upara_rnd2,
			       external_SET_rnd);
    break;
  case _MOMENTUM_RESOLUTION_:
    // determine hadronic momentum sampling term and number of minbias events to overlay using Run I method
    HadronicMomentumResolutionStudy(emobjs_smear, recoil_gen, vtx_gen, dummy, prefix, evtweight,
				    external_upara_rnd1, external_upara_rnd2,
				    external_SET_rnd);
    break;
  case _MOMENTUM_SCALE_BIFURCATE_:
    // determine hadronic momentum scale for bifurcate method
    HadronicMomentumScaleBifurcateStudy(emobjs_smear, recoil_gen, vtx_gen, dummy, prefix, evtweight,
					external_upara_rnd1, external_upara_rnd2,
					external_SET_rnd);
    break;
  case _MOMENTUM_SCALE_BIFURCATE2_:
    // determine hadronic momentum scale for bifurcate method
    HadronicMomentumScale2BifurcateStudy(emobjs_smear, recoil_gen, vtx_gen, dummy, prefix, evtweight,
				 	 external_upara_rnd1, external_upara_rnd2,
					 external_SET_rnd);
    break;
  case _MOMENTUM_RESOLUTION_BIFURCATE_:
    // determine hadronic momentum resolution for bifurcate method (only for hard component)
    HadronicMomentumResolutionBifurcateStudy(emobjs_smear, recoil_gen, vtx_gen, dummy, prefix, evtweight,
					     external_upara_rnd1, external_upara_rnd2,
					     external_SET_rnd);
    break;
  case _MOMENTUM_RESOLUTION_BIFURCATE2_:
    // determine hadronic momentum resolution for bifurcate method (for hard and soft components)
    HadronicMomentumResolution2BifurcateStudy(emobjs_smear, recoil_gen, vtx_gen, dummy, prefix, evtweight,
					      external_upara_rnd1, external_upara_rnd2,
					      external_SET_rnd);
    break;
  case _MOMENTUM_RESOLUTION_BIFURCATE3_:
    // determine hadronic momentum resolution for bifurcate method (for hard and soft components)
    HadronicMomentumResolution3BifurcateStudy(emobjs_smear, recoil_gen, vtx_gen, dummy, prefix, evtweight,
					      external_upara_rnd1, external_upara_rnd2,
					      external_SET_rnd);
    break;
  case _PHI_SMEARING_BIFURCATE_:
    // determine hadronic phi smearing for bifurcate method
    HadronicPhiSmearingBifurcateStudy(emobjs_smear, recoil_gen, vtx_gen, dummy, prefix, evtweight,
				      external_upara_rnd1, external_upara_rnd2,
				      external_SET_rnd);
    break;
  case _MOMENTUM_ALL_AT_ONCE_BIFURCATE_:
    // pre-select events fot MINUIT fit
    double luminosity = pmcsevent.GetInstLumi();
    int runno = pmcsevent.GetRunNo();
    int zbindex = pmcsevent.GetZBEvtIndex(); 
    int mbindex = pmcsevent.GetMBEvtIndex();
    int nem=emobjs_smear.size();
    //
    // Write pre-smeared hard recoil component from pure Z->nu+nu full MC without any fudging applied.
    // This vector is used later if option Zminuit_Skip_Znunu_Randomization=TRUE. 
    double gen_recoil_pT = recoil_gen.Recoil();
    double gen_recoil_phi = recoil_gen.RecoilPhi();
    double znunu_recoil_pT = 0.0;
    double znunu_recoil_phi = 0.0; 
    double znunu_SET_Hard = 0.0;
    double znunu_SET_Hard_expected = 0.0;
    // use hard recoil from last call to SmearHardRecoil_Method_B
    _recoilsmear->GetLastHardRecoil_Method_B(NULL,
					     NULL,
					     &znunu_recoil_pT,
					     &znunu_recoil_phi,
					     NULL,
					     NULL);
    // use hard scalar Et from last call to SmearHardRecoil_Method_B
    _recoilsmear->GetLastHardScalarEt_Method_B(&znunu_SET_Hard, 
					       &znunu_SET_Hard_expected,
					       NULL);

//     cout << "TEMPLATE: gen_recoil_pT=" << gen_recoil_pT
// 	 << ", gen_recoil_phi=" << gen_recoil_phi << endl;
//     cout << "TEMPLATE: znunu_recoil_pT=" << znunu_recoil_pT
// 	 << ", znunu_recoil_phi=" << znunu_recoil_phi << endl;
//     cout << "TEMPLATE: znunu_SET_Hard=" << znunu_SET_Hard
// 	 << ", znunu_SET_Hard_expected=" << znunu_SET_Hard_expected << endl;

    double pt_resol = 1.0 - znunu_recoil_pT/gen_recoil_pT;
    double delta_phi = znunu_recoil_phi - gen_recoil_phi;  

//     cout << "TEMPLATE: pt_resol=" << pt_resol
// 	 << ", delta_phi=" << delta_phi << endl;
    // 
    // Write a pair of random numbers for U_parallel corr. eff. 
    // This pair is used later if option Zminuit_Skip_UParaEfficiency_Randomization=TRUE. 
    double upara_rnd1, upara_rnd2;
    double SET_rnd[2];
    if(external_upara_rnd1) upara_rnd1 = *external_upara_rnd1;
    else                    upara_rnd1 = dummy->Uniform(0., 1.);
    if(external_upara_rnd2) upara_rnd2 = *external_upara_rnd2;
    else                    upara_rnd2 = dummy->Uniform(0., 1.);
    if(external_SET_rnd){
      SET_rnd[0]    = external_SET_rnd[0];
      SET_rnd[1]    = external_SET_rnd[1];
    }
    else {
      for (int isetrnd =0; isetrnd < 2; ++isetrnd)
	SET_rnd[isetrnd]    = dummy->Uniform(0., 1.);
    }

    // Read TB correction vector
    double given_tbdmetx = _recoilsmear->getTBdmetx();
    double given_tbdmety = _recoilsmear->getTBdmety();

    int bytes=MINUIT_WriteFile(emobjs_smear, recoil_gen, vtx_gen, evtweight,
			       luminosity, runno, zbindex, mbindex, pt_resol, delta_phi,
			       upara_rnd1, upara_rnd2, SET_rnd[0], znunu_SET_Hard, znunu_SET_Hard_expected, 
                               given_tbdmetx, given_tbdmety);
    _Zminuit_EventBuffer_Nevts++;
    break;
  };
}// end of fillTemplateRecoilHistograms()


// use truth method to study pT dependence of all selection criteria
void ZAnalysis::TruthEffStudies(std::vector<PMCSEMObj>& emobjs_smear, PMCSVtx& vtx_gen, PMCSRecoil& recoil_smear, PMCSMet& met_smear, TRandom3* dummy) {

  bool executeTruth=false;
  if (_TruthMode==0) {
    executeTruth=((emobjs_smear.size() >= 2)&&
		  (emobjs_smear[0].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut)||emobjs_smear[0].IsEC(_CutEtaEC1, _CutEtaEC2))&&(emobjs_smear[0].ppt()>15)&&
		  (emobjs_smear[1].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut)||emobjs_smear[1].IsEC(_CutEtaEC1, _CutEtaEC2))&&(emobjs_smear[1].ppt()>15));
  } else if (_TruthMode==1) {
    executeTruth=(emobjs_smear.size() >= 1);
  } else if (_TruthMode==2) {
    executeTruth=((emobjs_smear.size() >= 2)&&
                  emobjs_smear[0].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut)&&(emobjs_smear[0].ppt()>25)&&
                  emobjs_smear[1].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut)&&(emobjs_smear[1].ppt()>25));
  }
  if (!executeTruth) return;

  PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);

  double TrigVer = dummy->Uniform(0., 1.);
  bool passesTrigEff[2], passesPreselEff[2], passesEMIDEff[2], passesTrkEff[2], passesElecUParaEff[2],  passesElecPhiEff[2], passesLooseTrkEff[2] ;
  bool passesAllEMEff[2], passesAllEMEffUParaEff[2];
  bool passesSETeff[2];
  bool InCC[2], InEC[2];

  for(int ielec=0; ielec<2; ielec++) {
    // calorimeter region
    InCC[ielec] = emobjs_smear[ielec].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);
    InEC[ielec] = emobjs_smear[ielec].IsEC(_CutEtaEC1, _CutEtaEC2);

    // efficiencies
    passesTrigEff[ielec] = true;
    if(_ZtrigEffCorrection) passesTrigEff[ielec] = _efficiencysmear->passesTriggerEff(emobjs_smear[ielec], dummy, TrigVer, _ZBrunNum);

    passesPreselEff[ielec] = true;
    if(_ZpreselEffCorrection) passesPreselEff[ielec] = _efficiencysmear->passesPreselEff(emobjs_smear[ielec], dummy, 0, &vtx_gen,0,1);

    passesEMIDEff[ielec] = true;
    if(_ZIDEffCorrection) passesEMIDEff[ielec] = _efficiencysmear->passesEMIDEff(emobjs_smear[ielec], dummy);

    passesLooseTrkEff[ielec] = _efficiencysmear->passesLooseTrkEff(emobjs_smear[ielec], &vtx_gen, dummy);
    passesTrkEff[ielec] = _efficiencysmear->passesTrkEff(emobjs_smear[ielec], vtx_gen, dummy);
    if (!(_NZpreselTrkMatch > 0)){
      passesTrkEff[ielec] = (passesTrkEff[ielec]&& passesLooseTrkEff[ielec]); 
    }
    if(_ZElecPhiEffCorrection) {
      passesElecPhiEff[ielec] = true; 
      passesElecPhiEff[ielec] = _efficiencysmear->passesElecPhiEff(emobjs_smear[ielec], dummy, _ZElecPhiEffCorrectionUseDetPhi);
      passesTrkEff[ielec] = passesTrkEff[ielec] && passesElecPhiEff[ielec];
    }
    // uparallel efficiency
    passesElecUParaEff[ielec] = true;
    double upara = 0.;
    if(ielec==0) upara = zcand.UPara1();
    else upara = zcand.UPara2();
    passesElecUParaEff[ielec] = passesUParaEff(emobjs_smear[ielec], upara, dummy);

    // all EM identification efficiency
    passesAllEMEff[ielec] = passesTrigEff[ielec] && passesPreselEff[ielec] && passesEMIDEff[ielec] && passesTrkEff[ielec] && passesLooseTrkEff[ielec];

    // all EM identification efficiency and uparallel efficiency
    passesAllEMEffUParaEff[ielec] = passesAllEMEff[ielec] && passesElecUParaEff[ielec];
  }

  

  // SET efficiency
  double scalarEt_All=_recoilsmear->scalarEt();
  double claimpT1,claimpT2;
  claimpT1=emobjs_smear[0].ppt();
  if (claimpT1<25) claimpT1=25.5;
  claimpT2=emobjs_smear[1].ppt();
  if (claimpT2<25) claimpT2=25.5;
  bool evtSETeff=true;
  passesSETeff[0]=kTRUE;
  passesSETeff[0]=kTRUE;
  if (_ZSETEffCorrection) {
    evtSETeff=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),
						dummy, NULL, claimpT1, claimpT2, InEC[0], InEC[1], emobjs_smear[0].deteta(), emobjs_smear[1].deteta(), zcand.UPara1(), zcand.UPara2());
    passesSETeff[0]=_SETefficiencysmear->passesFirst();
    passesSETeff[1]=_SETefficiencysmear->passesSecond();
  }
  
  
  

  // Fill plots
  for(int ielec=0; ielec<2; ielec++) {

    if (!InCC[ielec]) continue;

    char bins_Eta[10];
    int bin_Eta_number;
    if(emobjs_smear[ielec].peta()<-1.3)
      bin_Eta_number=0;
    else if(emobjs_smear[ielec].peta()>1.3)
      bin_Eta_number=14;
    else
      bin_Eta_number=int((emobjs_smear[ielec].peta()+1.3)/0.2)+1;
    sprintf(bins_Eta, "%d", bin_Eta_number);

    if (emobjs_smear[ielec].ppt()>25) {
      _histos.Fill1D("smeared_EffTruth_EMPt_CC", emobjs_smear[ielec].ppt());
      _histos.Fill1D(string("smeared_EffTruth_EMPt_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
      // so far do not have a model of pT-dependence of preselection
      if (passesPreselEff[ielec]) {
	_histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_CC", emobjs_smear[ielec].ppt());
	if (passesLooseTrkEff[ielec]){
	  _histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_ltrk_CC", emobjs_smear[ielec].ppt());
	  _histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_ltrk_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
	  _histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
	  if (passesEMIDEff[ielec]) {
	    _histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_CC", emobjs_smear[ielec].ppt());
	    _histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
	    if (passesElecUParaEff[ielec]) {
	      _histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_upara_CC", emobjs_smear[ielec].ppt());
	      _histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_upara_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
	      if (passesSETeff[ielec]) {
		_histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_upara_set_CC", emobjs_smear[ielec].ppt());
		_histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_upara_set_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
	      }
	    }
	    if (passesSETeff[ielec]) {
	      _histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_set_CC", emobjs_smear[ielec].ppt());
	      _histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_set_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
	    }
	    if (passesTrkEff[ielec]) {
	      _histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_CC", emobjs_smear[ielec].ppt());
	      _histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
	      if (passesElecUParaEff[ielec]) {
		_histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_CC", emobjs_smear[ielec].ppt());
		_histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
		if (passesSETeff[ielec]) {
		  _histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set_CC", emobjs_smear[ielec].ppt());
		  _histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
		  if (emobjs_smear[ielec].trkpT()>10) {
		    _histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set_trkpt_CC", emobjs_smear[ielec].ppt());
		    _histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set_trkpt_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
		  }
		  //
		  if (_efficiencysmear->passesClusPtEff(emobjs_smear[ielec], dummy)) {
		    _histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set__cluscorr_CC", emobjs_smear[ielec].ppt());
		    _histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_upara_set__cluscorr_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
		  }
		}
	      }
	      if (passesSETeff[ielec]) {
		_histos.Fill1D("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_set_CC", emobjs_smear[ielec].ppt());
		_histos.Fill1D(string("smeared_EffTruth_EMPt_clus_emfrac_iso_hmx_trk_set_CC_")+bins_Eta, emobjs_smear[ielec].ppt());
	      }
	    }
	  }
	}
      }
    }
  }
}


// use tag-probe method to study pT dependence of all selection criteria
void ZAnalysis::TagProbeEffStudies(std::vector<PMCSEMObj>& emobjs_smear, PMCSVtx& vtx_gen, PMCSRecoil& recoil_smear, PMCSMet& met_smear, TRandom3* dummy, double evtweight) {
  
  if( (emobjs_smear[0].ppt()>20.) && (emobjs_smear[1].ppt()>20.) ) {
    PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);
    
    double mass = zcand.mass();
    int type = zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);
    double v_z = vtx_gen.vtxz();

    double zScalarEt = _recoilsmear->scalarEt();
    
    char bins_SET[10];
    int bin_SET_number;
    if(zScalarEt<30.)
      bin_SET_number=0;
    else if(zScalarEt<50.)
      bin_SET_number=1;
    else if(zScalarEt<80.)
      bin_SET_number=2;
    else if(zScalarEt<120.)
      bin_SET_number=3;
    else 
        bin_SET_number=4;
    sprintf(bins_SET, "%d", bin_SET_number);
    
    // select Z events
    //if((type==0)) {
    if((type==0 || type==1 || type==2 )) { //use cccc, ccec and ecec in some cases
    //if(type==0 && mass>_ZMassCut1 && mass<_ZMassCut2) {

      double TrigVer = dummy->Uniform(0., 1.);
      bool passesTrigEff[2], passesPreselEff[2], passesEMIDEff[2], passesTrkEff[2], passesElecUParaEff[2], passesLooseTrkEff[2],passesElecPhiEff[2];
      bool passesAllEMEff[2], passesAllEMEffUParaEff[2];
      bool passesSETeff[2];
      bool InCC[2], InEC[2];
      bool passesTrigEffT[2][3];
      for(int ielec=0; ielec<2; ielec++) {
	// calorimeter region
	InCC[ielec] = emobjs_smear[ielec].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);
	InEC[ielec] = emobjs_smear[ielec].IsEC(_CutEtaEC1, _CutEtaEC2);

	// efficiencies
	passesTrigEff[ielec] = true;
	if(_ZtrigEffCorrection) passesTrigEff[ielec] = _efficiencysmear->passesTriggerEff(emobjs_smear[ielec], dummy, TrigVer, _ZBrunNum);
	for (int forcet=0;forcet<3;++forcet){
	  passesTrigEffT[ielec][forcet] = _efficiencysmear->passesTriggerEff(emobjs_smear[ielec], dummy, TrigVer, _ZBrunNum,0,forcet+1);
	}
	passesPreselEff[ielec] = true;
	if(_ZpreselEffCorrection) passesPreselEff[ielec] = _efficiencysmear->passesPreselEff(emobjs_smear[ielec], dummy, 0, &vtx_gen,0,1);

	passesEMIDEff[ielec] = true;
	if(_ZIDEffCorrection) passesEMIDEff[ielec] = _efficiencysmear->passesEMIDEff(emobjs_smear[ielec], dummy);

	
	passesTrkEff[ielec] = _efficiencysmear->passesTrkEff(emobjs_smear[ielec], vtx_gen, dummy);
	passesLooseTrkEff[ielec] = _efficiencysmear->passesLooseTrkEff(emobjs_smear[ielec], &vtx_gen, dummy);
	
	passesTrkEff[ielec] = (passesTrkEff[ielec]&& passesLooseTrkEff[ielec]); 
        
	if(_ZElecPhiEffCorrection) {
          passesElecPhiEff[ielec] = true; 
          passesElecPhiEff[ielec] = _efficiencysmear->passesElecPhiEff(emobjs_smear[ielec], dummy, _ZElecPhiEffCorrectionUseDetPhi);
          passesTrkEff[ielec] = passesTrkEff[ielec] && passesElecPhiEff[ielec]; 
	}
	
	// uparallel efficiency
	passesElecUParaEff[ielec] = true;
	double upara = 0.;
	if(ielec==0) upara = zcand.UPara1();
	else upara = zcand.UPara2();
	passesElecUParaEff[ielec] = passesUParaEff(emobjs_smear[ielec], upara, dummy);
	
	// all EM identification efficiency
	passesAllEMEff[ielec] = passesTrigEff[ielec] && passesPreselEff[ielec] && passesEMIDEff[ielec] && passesTrkEff[ielec] && passesLooseTrkEff[ielec] && (emobjs_smear[ielec].trkpT()>_trkpTCut) ;

	// all EM identification efficiency and uparallel efficiency
	passesAllEMEffUParaEff[ielec] = passesAllEMEff[ielec] && passesElecUParaEff[ielec];

      }

      // SET efficiency
      double scalarEt_All=_recoilsmear->scalarEt();
      bool evtSETeff=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),
						       dummy, NULL, emobjs_smear[0].ppt(), emobjs_smear[1].ppt(), InEC[0], InEC[1], emobjs_smear[0].deteta(), emobjs_smear[1].deteta(), zcand.UPara1(), zcand.UPara2());
      passesSETeff[0]=_SETefficiencysmear->passesFirst();
      passesSETeff[1]=_SETefficiencysmear->passesSecond();

      // for trigger efficiency analysis, following code in wmass_analysis/EffAnalysis.cpp
      // loop over two electrons and use each one as the tag and use the other one as the probe
      for(int ielec_tag=0; ielec_tag<2; ielec_tag++) {
	if(passesAllEMEffUParaEff[ielec_tag] &&  passesSETeff[ielec_tag] &&
	   emobjs_smear[ielec_tag].ppt()>25. && (InCC[ielec_tag]) && 
	   mass>_ZMassCut1 && mass<_ZMassCut2) {
	  
	  // get the other electron as the probe electron
	  int ielec_probe = 0;
	  if(ielec_tag == 0) ielec_probe = 1;
	  
	  // probe electron must pass presel, EMID, all cuts as well
	  if(passesAllEMEffUParaEff[ielec_probe] && passesSETeff[ielec_probe] &&
	     emobjs_smear[ielec_probe].ppt()>25. && InCC[ielec_probe]) {
	    for (int flag = 0; flag <3;++flag){
	      char sn1[10]; sprintf(sn1,"%d", flag);
	      TString SN_Triglist=TString("_")+sn1;
	      
	      _histos.Fill2D( TString("smeared_ZMass_vs_DetEta_Before_Trig_CC")+SN_Triglist, emobjs_smear[ielec_probe].deteta(), mass, evtweight);
	      _histos.Fill2D( TString("smeared_ZMass_vs_Eta_Before_Trig_CC")+SN_Triglist, emobjs_smear[ielec_probe].eta(), mass, evtweight);
	      _histos.Fill2D( TString("smeared_ZMass_vs_Pt_Before_Trig_CC")+SN_Triglist, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      _histos.Fill2D( TString("smeared_ZMass_vs_Vtx_Before_Trig_CC")+SN_Triglist, v_z, mass, evtweight);
	      
	      _histos.Fill2D("smeared_ZMass_vs_DetEta_Before_Trig_CC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Eta_Before_Trig_CC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Pt_Before_Trig_CC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Vtx_Before_Trig_CC", v_z, mass, evtweight);
	      
	    
	      
	      
	      
	      if(passesTrigEffT[ielec_probe][flag]) {
		
		_histos.Fill2D( TString("smeared_ZMass_vs_DetEta_After_Trig_CC")+SN_Triglist, emobjs_smear[ielec_probe].deteta(), mass, evtweight);
		_histos.Fill2D( TString("smeared_ZMass_vs_Eta_After_Trig_CC")+SN_Triglist, emobjs_smear[ielec_probe].eta(), mass, evtweight);
		_histos.Fill2D( TString("smeared_ZMass_vs_Pt_After_Trig_CC")+SN_Triglist, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D( TString("smeared_ZMass_vs_Vtx_After_Trig_CC")+SN_Triglist, v_z, mass, evtweight);
		
		_histos.Fill2D("smeared_ZMass_vs_DetEta_After_Trig_CC_0", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Eta_After_Trig_CC_0", emobjs_smear[ielec_probe].eta(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Pt_After_Trig_CC_0", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Vtx_After_Trig_CC_0", v_z, mass, evtweight);
	      }
	    }
	  } // probe electron
	} // tag electron
      } // use each electron as a tag electron and use the other as the probe electron

      // for presel efficiency analysis, following code in wmass_analysis/EffAnalysis.cpp
      // loop over two electrons and use each one as the tag and use the other one as the probe
      // here I need to use EM-track mass instead of EM-EM mass
      for(int ielec_tag=0; ielec_tag<2; ielec_tag++) {
	if(passesAllEMEffUParaEff[ielec_tag] &&  passesSETeff[ielec_tag] && 
	   emobjs_smear[ielec_tag].ppt()>25. && (InCC[ielec_tag] )) {
	  
	  // get the other electron as the probe electron
	  int ielec_probe = 0;
	  if(ielec_tag == 0) ielec_probe = 1;

	  // we only have smeared track pT available, no pZ available
	  // here we assume pZ can also be scaled 
	  double pT_probeTrk = emobjs_smear[ielec_probe].trkpT();
	  double pT_probeEM = emobjs_smear[ielec_probe].ppt();

	  double pX_TagEM = emobjs_smear[ielec_tag].ppx();
	  double pY_TagEM = emobjs_smear[ielec_tag].ppy();
	  double pZ_TagEM = emobjs_smear[ielec_tag].ppz();
	  double E_TagEM = sqrt(pX_TagEM*pX_TagEM + pY_TagEM*pY_TagEM + pZ_TagEM*pZ_TagEM);

	  double pX_probeTrk = pT_probeTrk * cos(emobjs_smear[ielec_probe].pphi());
	  double pY_probeTrk = pT_probeTrk * sin(emobjs_smear[ielec_probe].pphi());
	  double p_probeTrk  = abs(pT_probeTrk / sin(emobjs_smear[ielec_probe].theta()));
	  double pZ_probeTrk  = p_probeTrk *  cos(emobjs_smear[ielec_probe].theta());
	  

	  double mass_EM_trk = sqrt((E_TagEM+p_probeTrk)*(E_TagEM+p_probeTrk) - (pX_TagEM+pX_probeTrk)*(pX_TagEM+pX_probeTrk) -
				    (pY_TagEM+pY_probeTrk)*(pY_TagEM+pY_probeTrk) - (pZ_TagEM+pZ_probeTrk)*(pZ_TagEM+pZ_probeTrk));
	  
	  //work here
	  // probe electron must pass presel, EMID, TrkEff except HMatrix
	  if(  passesTrkEff[ielec_probe]  &&  (pT_probeTrk > 10.) && (kinem::delta_R(emobjs_smear[ielec_probe].peta(), emobjs_smear[ielec_probe].pphi(),emobjs_smear[ielec_probe].deteta() , emobjs_smear[ielec_probe].detphi() ) < 0.2) &&   passesElecUParaEff[ielec_probe] &&  passesSETeff[ielec_probe] &&
	       mass_EM_trk>_ZMassCut1 && mass_EM_trk<_ZMassCut2   ) {
	    if (InCC[ielec_probe]) { 
	      _histos.Fill2D("smeared_ZMass_vs_DetEta_Before_Presel_CC", emobjs_smear[ielec_probe].deteta(), mass_EM_trk, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Eta_Before_Presel_CC", emobjs_smear[ielec_probe].eta(), mass_EM_trk, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Pt_Before_Presel_CC", emobjs_smear[ielec_probe].ppt(), mass_EM_trk, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Vtx_Before_Presel_CC", v_z, mass_EM_trk, evtweight);
	      
	      if( passesPreselEff[ielec_probe]) {
		_histos.Fill2D("smeared_ZMass_vs_DetEta_After_Presel_CC", emobjs_smear[ielec_probe].deteta(), mass_EM_trk, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Eta_After_Presel_CC", emobjs_smear[ielec_probe].eta(), mass_EM_trk, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Pt_After_Presel_CC", emobjs_smear[ielec_probe].ppt(), mass_EM_trk, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Vtx_After_Presel_CC", v_z, mass_EM_trk, evtweight);
	      }
	    }else if (InEC[ielec_probe]) { 
	      _histos.Fill2D("smeared_ZMass_vs_DetEta_Before_Presel_EC", emobjs_smear[ielec_probe].deteta(), mass_EM_trk, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Eta_Before_Presel_EC", emobjs_smear[ielec_probe].eta(), mass_EM_trk, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Pt_Before_Presel_EC", emobjs_smear[ielec_probe].ppt(), mass_EM_trk, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Vtx_Before_Presel_EC", v_z, mass_EM_trk, evtweight);
	      
	      if( passesPreselEff[ielec_probe]) {
		_histos.Fill2D("smeared_ZMass_vs_DetEta_After_Presel_EC", emobjs_smear[ielec_probe].deteta(), mass_EM_trk, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Eta_After_Presel_EC", emobjs_smear[ielec_probe].eta(), mass_EM_trk, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Pt_After_Presel_EC", emobjs_smear[ielec_probe].ppt(), mass_EM_trk, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Vtx_After_Presel_EC", v_z, mass_EM_trk, evtweight);
	      }
	    }
	  } // probe electron
	} // tag electron
      } // use each electron as a tag electron and use the other as the probe electron

      // for HMx efficiency analysis, following code in wmass_analysis/EffAnalysis.cpp
      // loop over two electrons and use each one as the tag and use the other one as the probe
      for(int ielec_tag=0; ielec_tag<2; ielec_tag++) {
	if(passesAllEMEffUParaEff[ielec_tag]  &&  passesSETeff[ielec_tag] && 
	   emobjs_smear[ielec_tag].ppt()>25. && (InCC[ielec_tag] || InEC[ielec_tag]) && 
	   mass>50. && mass<150.) { 
	  
	  // get the other electron as the probe electron
	  int ielec_probe = 0;
	  if(ielec_tag == 0) ielec_probe = 1;

	  // probe electron must pass Trig, presel, TrkEff except HMatrix
	  if(passesPreselEff[ielec_probe] && passesElecUParaEff[ielec_probe] &&  (emobjs_smear[ielec_probe].ppt()>25.) ){// &&  passesTrkEff[ielec_probe ] && passesSETeff[ielec_probe]  && (emobjs_smear[ielec_probe].trkpT()>_trkpTCut)  ) {
	    double elec_eta = emobjs_smear[ielec_probe].peta();
	    char bins_Eta[10];
	    int bin_Eta_number;
	    if(elec_eta<-1.3)
	      bin_Eta_number=0;
	    else if(elec_eta>1.3)
	      bin_Eta_number=14;
	    else
	      bin_Eta_number=int((elec_eta+1.3)/0.2)+1;
	    sprintf(bins_Eta, "%d", bin_Eta_number);

	    if (InCC[ielec_probe]){
	      _histos.Fill2D("smeared_ZMass_vs_DetEta_Before_HMx_CC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Eta_Before_HMx_CC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Pt_Before_HMx_CC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Vtx_Before_HMx_CC", v_z, mass, evtweight);
	      _histos.Fill2D("smeared_Eta_vs_Pt_Before_HMx_CC", emobjs_smear[ielec_probe].ppt(), emobjs_smear[ielec_probe].eta(), evtweight);
              _histos.Fill2D("smeared_Eta_vs_Vtx_Before_HMx_CC", v_z, emobjs_smear[ielec_probe].eta(), evtweight);
	      _histos.Fill2D(string("smeared_ZMass_vs_Pt_Before_HMx_CC_Etabin_")+bins_Eta, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      _histos.Fill2D(string("smeared_ZMass_vs_Pt_Before_HMx_CC_SETbin_")+bins_SET, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      if(passesEMIDEff[ielec_probe]) {
		_histos.Fill2D("smeared_ZMass_vs_DetEta_After_HMx_CC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Eta_After_HMx_CC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Pt_After_HMx_CC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Vtx_After_HMx_CC", v_z, mass, evtweight);
		_histos.Fill2D("smeared_Eta_vs_Pt_After_HMx_CC", emobjs_smear[ielec_probe].ppt(), emobjs_smear[ielec_probe].eta(), evtweight);
                _histos.Fill2D("smeared_Eta_vs_Vtx_After_HMx_CC", v_z, emobjs_smear[ielec_probe].eta(), evtweight);
		_histos.Fill2D(string("smeared_ZMass_vs_Pt_After_HMx_CC_Etabin_")+bins_Eta, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D(string("smeared_ZMass_vs_Pt_After_HMx_CC_SETbin_")+bins_SET, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      }
	    } else if (InEC[ielec_probe]) {
	      _histos.Fill2D("smeared_ZMass_vs_DetEta_Before_HMx_EC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Eta_Before_HMx_EC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Pt_Before_HMx_EC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Vtx_Before_HMx_EC", v_z, mass, evtweight);
	      
	      if(passesEMIDEff[ielec_probe]) {
		_histos.Fill2D("smeared_ZMass_vs_DetEta_After_HMx_EC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Eta_After_HMx_EC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Pt_After_HMx_EC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Vtx_After_HMx_EC", v_z, mass, evtweight);
	      }
	    }
	  } // probe electron
	} // tag electron
      } // use each electron as a tag electron and use the other as the probe electron
      
      // for Track matching efficiency analysis, following code in wmass_analysis/EffAnalysis.cpp
      // loop over two electrons and use each one as the tag and use the other one as the probe
      for(int ielec_tag=0; ielec_tag<2; ielec_tag++) {
       	if(passesAllEMEffUParaEff[ielec_tag] && emobjs_smear[ielec_tag].trkpT()>_trkpTCut && passesSETeff[ielec_tag] &&
	   emobjs_smear[ielec_tag].ppt()>25. && (InCC[ielec_tag] || InEC[ielec_tag]) &&  
	   mass>50. && mass<150.) { 
	  //tag electron is in CC!
	  
	  // get the other electron as the probe electron
	  int ielec_probe = 0;
	  if(ielec_tag == 0) ielec_probe = 1;
	  
	  // probe electron must pass Trig, presel, EMIDEff except TrkEff
	  if (passesPreselEff[ielec_probe] && passesEMIDEff[ielec_probe] &&  passesLooseTrkEff[ielec_probe] && passesSETeff[ielec_tag] &&
	      emobjs_smear[ielec_probe].ppt()>25.) {
	       
	    double elec_eta = emobjs_smear[ielec_probe].peta();
	    char bins_Eta[10];
	    int bin_Eta_number;
	    if(elec_eta<-1.3)
	      bin_Eta_number=0;
	    else if(elec_eta>1.3)
	      bin_Eta_number=14;
	    else
	      bin_Eta_number=int((elec_eta+1.3)/0.2)+1;
	    sprintf(bins_Eta, "%d", bin_Eta_number);
	       
	    if (InCC[ielec_probe]){
	      _histos.Fill2D("smeared_ZMass_vs_DetEta_Before_Trk_CC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Eta_Before_Trk_CC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Pt_Before_Trk_CC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Vtx_Before_Trk_CC", v_z, mass, evtweight);
	      _histos.Fill2D("smeared_Eta_vs_Pt_Before_Trk_CC", emobjs_smear[ielec_probe].ppt(), emobjs_smear[ielec_probe].eta(), evtweight);
	      _histos.Fill2D("smeared_Eta_vs_Vtx_Before_Trk_CC", v_z, emobjs_smear[ielec_probe].eta(), evtweight);
	      _histos.Fill2D(string("smeared_ZMass_vs_Pt_Before_Trk_CC_Etabin_")+bins_Eta, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      _histos.Fill2D(string("smeared_ZMass_vs_Vtx_Before_Trk_CC_Etabin_")+bins_Eta, v_z, mass, evtweight);
	      _histos.Fill2D(string("smeared_ZMass_vs_Pt_Before_Trk_CC_SETbin_")+bins_SET, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	    } else if (InEC[ielec_probe]){
	      _histos.Fill2D("smeared_ZMass_vs_DetEta_Before_Trk_EC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Eta_Before_Trk_EC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Pt_Before_Trk_EC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_Vtx_Before_Trk_EC", v_z, mass, evtweight);
	    }
	       
	    // for different primary vertex region
	    int vtx_region = -1;
	    if(v_z<-50.) vtx_region = 0;
	    //else if (v_z<-45.) vtx_region = 1;
	    else if (v_z<-43.) vtx_region = 1;
	    else if (v_z<-37.) vtx_region = 2;
	    else if (v_z<-30.) vtx_region = 3;
	    else if (v_z<-20.) vtx_region = 4;
	    else if (v_z<-10.) vtx_region = 5;
	    else if (v_z<0.) vtx_region = 6;
	    else if (v_z<10.) vtx_region =7;
	    else if (v_z<20.) vtx_region = 8;
	    else if (v_z<30.) vtx_region = 9;
	    else if (v_z<37.) vtx_region = 10;
	    else if (v_z<43.) vtx_region = 11;
	    //else if (v_z<40.) vtx_region = 13;
	    else if (v_z<50.) vtx_region = 12;
	    else vtx_region = 13;
	    char vtx_region_char[10];  sprintf(vtx_region_char, "%d", vtx_region);	
	       
	    // fill invariant mass distribution for different eta region: 31 regions from -3.1 to 3.1
	    double peta =  emobjs_smear[ielec_probe].eta();
	    int eta_region = -1;
	    if (-3.1<=peta && peta<-2.9) {eta_region = 0;}
	    else if (-2.9<=peta && peta<-2.7) {eta_region = 1;}
	    else if (-2.7<=peta && peta<-2.5) {eta_region = 2;}
	    else if (-2.5<=peta && peta<-2.3) {eta_region = 3;}
	    else if (-2.3<=peta && peta<-2.1) {eta_region = 4;}
	    else if (-2.1<=peta && peta<-1.9) {eta_region = 5;}
	    else if (-1.9<=peta && peta<-1.7) {eta_region = 6;}
	    else if (-1.7<=peta && peta<-1.5) {eta_region = 7;}
	    else if (-1.5<=peta && peta<-1.3) {eta_region = 8;}
	    else if (-1.3<=peta && peta<-1.1) {eta_region = 9;}
	    else if (-1.1<=peta && peta<-0.9) {eta_region = 10;}
	    else if (-0.9<=peta && peta<-0.7) {eta_region = 11;}
	    else if (-0.7<=peta && peta<-0.5) {eta_region = 12;}
	    else if (-0.5<=peta && peta<-0.3) {eta_region = 13;}
	    else if (-0.3<=peta && peta<-0.1) {eta_region = 14;}
	    else if (-0.1<=peta && peta<0.1) {eta_region = 15;}
	    else if (0.1<=peta && peta<0.3) {eta_region = 16;}
	    else if (0.3<=peta && peta<0.5) {eta_region = 17;}
	    else if (0.5<=peta && peta<0.7) {eta_region = 18;}
	    else if (0.7<=peta && peta<0.9) {eta_region = 19;}
	    else if (0.9<=peta && peta<1.1) {eta_region = 20;}
	    else if (1.1<=peta && peta<1.3) {eta_region = 21;}
	    else if (1.3<=peta && peta<1.5) {eta_region = 22;}
	    else if (1.5<=peta && peta<1.7) {eta_region = 23;}
	    else if (1.7<=peta && peta<1.9) {eta_region = 24;}
	    else if (1.9<=peta && peta<2.1) {eta_region = 25;}
	    else if (2.1<=peta && peta<2.3) {eta_region = 26;}
	    else if (2.3<=peta && peta<2.5) {eta_region = 27;}
	    else if (2.5<=peta && peta<2.7) {eta_region = 28;}
	    else if (2.7<=peta && peta<2.9) {eta_region = 29;}
	    else if (2.9<=peta && peta<3.1) {eta_region = 30;}
	    char eta_region_char[10];  sprintf(eta_region_char, "%d", eta_region);
	       
	    _histos.Fill1D(string("smeared_ZMass_vs_Eta_Before_Trk_Vtx_")+vtx_region_char+string("_")+eta_region_char, mass, evtweight);
	    //if(passesTrkEff[ielec_probe]) {	     	      
	    if(passesTrkEff[ielec_probe]&&passesElecUParaEff[ielec_probe]&&passesSETeff[ielec_probe]/*&&passesEMIDEff[ielec_probe]*/) {
	      _histos.Fill1D(string("smeared_ZMass_vs_Eta_After_Trk_Vtx_")+vtx_region_char+string("_")+eta_region_char, mass, evtweight);	      
	      if (InCC[ielec_probe]){
		_histos.Fill2D("smeared_ZMass_vs_DetEta_After_Trk_CC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Eta_After_Trk_CC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Pt_After_Trk_CC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Vtx_After_Trk_CC", v_z, mass, evtweight);
		_histos.Fill2D("smeared_Eta_vs_Pt_After_Trk_CC", emobjs_smear[ielec_probe].ppt(), emobjs_smear[ielec_probe].eta(), evtweight);
		_histos.Fill2D("smeared_Eta_vs_Vtx_After_Trk_CC", v_z, emobjs_smear[ielec_probe].eta(), evtweight);
		_histos.Fill2D(string("smeared_ZMass_vs_Pt_After_Trk_CC_Etabin_")+bins_Eta, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D(string("smeared_ZMass_vs_Vtx_After_Trk_CC_Etabin_")+bins_Eta, v_z, mass, evtweight);
		_histos.Fill2D(string("smeared_ZMass_vs_Pt_After_Trk_CC_SETbin_")+bins_SET, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      } else if (InEC[ielec_probe]){
		_histos.Fill2D("smeared_ZMass_vs_DetEta_After_Trk_EC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Eta_After_Trk_EC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Pt_After_Trk_EC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D("smeared_ZMass_vs_Vtx_After_Trk_EC", v_z, mass, evtweight);
	      }
	    }
	  } // probe electron
	} // tag electron
	   
      } // use each electron as a tag electron and use the other as the probe electron


      // for Loose Track matching efficiency analysis, following code in wmass_analysis/EffAnalysis.cpp
      // loop over two electrons and use each one as the tag and use the other one as the probe
      for(int ielec_tag=0; ielec_tag<2; ielec_tag++) {
       	if(passesAllEMEffUParaEff[ielec_tag] && emobjs_smear[ielec_tag].trkpT()>_trkpTCut && passesSETeff[ielec_tag] &&
	   emobjs_smear[ielec_tag].ppt()>25. && (InCC[ielec_tag] || InEC[ielec_tag]) &&  
	   mass>50. && mass<150.) { 
	  //tag electron is in CC!
	  
	  // get the other electron as the probe electron
	  int ielec_probe = 0;
	  if(ielec_tag == 0) ielec_probe = 1;
	  
	  // probe electron must pass Trig, presel, EMIDEff except TrkEff
	  if (passesPreselEff[ielec_probe] && passesLooseTrkEff[ielec_probe] && passesSETeff[ielec_probe]&&
	      emobjs_smear[ielec_probe].ppt()>25.) {


	       
	    double elec_eta = emobjs_smear[ielec_probe].peta();
	    char bins_Eta[10];
	    int bin_Eta_number;
	    if(elec_eta<-1.3)
	      bin_Eta_number=0;
	    else if(elec_eta>1.3)
	      bin_Eta_number=14;
	    else
	      bin_Eta_number=int((elec_eta+1.3)/0.2)+1;
	    sprintf(bins_Eta, "%d", bin_Eta_number);
	       
	    if (InCC[ielec_probe]){
	      _histos.Fill2D("smeared_loose_ZMass_vs_DetEta_Before_Trk_CC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
	      _histos.Fill2D("smeared_loose_ZMass_vs_Eta_Before_Trk_CC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
	      _histos.Fill2D("smeared_loose_ZMass_vs_Pt_Before_Trk_CC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      _histos.Fill2D("smeared_loose_ZMass_vs_Vtx_Before_Trk_CC", v_z, mass, evtweight);
	      _histos.Fill2D("smeared_loose_Eta_vs_Pt_Before_Trk_CC", emobjs_smear[ielec_probe].ppt(), emobjs_smear[ielec_probe].eta(), evtweight);
	      _histos.Fill2D("smeared_loose_Eta_vs_Vtx_Before_Trk_CC", v_z, emobjs_smear[ielec_probe].eta(), evtweight);
	      _histos.Fill2D(string("smeared_loose_ZMass_vs_Pt_Before_Trk_CC_Etabin_")+bins_Eta, emobjs_smear[ielec_probe].ppt(), mass, evtweight);

	      _histos.Fill2D(string("smeared_loose_ZMass_vs_Vtx_Before_Trk_CC_Etabin_")+bins_Eta, v_z, mass, evtweight);
	      _histos.Fill2D(string("smeared_loose_ZMass_vs_Pt_Before_Trk_CC_SETbin_")+bins_SET, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	    } else if (InEC[ielec_probe]){
	      _histos.Fill2D("smeared_loose_ZMass_vs_DetEta_Before_Trk_EC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
	      _histos.Fill2D("smeared_loose_ZMass_vs_Eta_Before_Trk_EC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
	      _histos.Fill2D("smeared_loose_ZMass_vs_Pt_Before_Trk_EC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      _histos.Fill2D("smeared_loose_ZMass_vs_Vtx_Before_Trk_EC", v_z, mass, evtweight);
	    }
	       
	    // for different primary vertex region
	    int vtx_region = -1;
	    if(v_z<-50.) vtx_region = 0;
	    else if (v_z<-40.) vtx_region = 1;
	    else if (v_z<-30.) vtx_region = 2;
	    else if (v_z<-20.) vtx_region = 3;
	    else if (v_z<-10.) vtx_region = 4;
	    else if (v_z<0.) vtx_region = 5;
	    else if (v_z<10.) vtx_region = 6;
	    else if (v_z<20.) vtx_region = 7;
	    else if (v_z<30.) vtx_region = 8;
	    else if (v_z<40.) vtx_region = 9;
	    else if (v_z<50.) vtx_region = 10;
	    else vtx_region = 11;
	    char vtx_region_char[10];  sprintf(vtx_region_char, "%d", vtx_region);	
	       
	    // fill invariant mass distribution for different eta region: 31 regions from -3.1 to 3.1
	    double peta =  emobjs_smear[ielec_probe].eta();
	    int eta_region = -1;
	    if (-3.1<=peta && peta<-2.9) {eta_region = 0;}
	    else if (-2.9<=peta && peta<-2.7) {eta_region = 1;}
	    else if (-2.7<=peta && peta<-2.5) {eta_region = 2;}
	    else if (-2.5<=peta && peta<-2.3) {eta_region = 3;}
	    else if (-2.3<=peta && peta<-2.1) {eta_region = 4;}
	    else if (-2.1<=peta && peta<-1.9) {eta_region = 5;}
	    else if (-1.9<=peta && peta<-1.7) {eta_region = 6;}
	    else if (-1.7<=peta && peta<-1.5) {eta_region = 7;}
	    else if (-1.5<=peta && peta<-1.3) {eta_region = 8;}
	    else if (-1.3<=peta && peta<-1.1) {eta_region = 9;}
	    else if (-1.1<=peta && peta<-0.9) {eta_region = 10;}
	    else if (-0.9<=peta && peta<-0.7) {eta_region = 11;}
	    else if (-0.7<=peta && peta<-0.5) {eta_region = 12;}
	    else if (-0.5<=peta && peta<-0.3) {eta_region = 13;}
	    else if (-0.3<=peta && peta<-0.1) {eta_region = 14;}
	    else if (-0.1<=peta && peta<0.1) {eta_region = 15;}
	    else if (0.1<=peta && peta<0.3) {eta_region = 16;}
	    else if (0.3<=peta && peta<0.5) {eta_region = 17;}
	    else if (0.5<=peta && peta<0.7) {eta_region = 18;}
	    else if (0.7<=peta && peta<0.9) {eta_region = 19;}
	    else if (0.9<=peta && peta<1.1) {eta_region = 20;}
	    else if (1.1<=peta && peta<1.3) {eta_region = 21;}
	    else if (1.3<=peta && peta<1.5) {eta_region = 22;}
	    else if (1.5<=peta && peta<1.7) {eta_region = 23;}
	    else if (1.7<=peta && peta<1.9) {eta_region = 24;}
	    else if (1.9<=peta && peta<2.1) {eta_region = 25;}
	    else if (2.1<=peta && peta<2.3) {eta_region = 26;}
	    else if (2.3<=peta && peta<2.5) {eta_region = 27;}
	    else if (2.5<=peta && peta<2.7) {eta_region = 28;}
	    else if (2.7<=peta && peta<2.9) {eta_region = 29;}
	    else if (2.9<=peta && peta<3.1) {eta_region = 30;}
	    char eta_region_char[10];  sprintf(eta_region_char, "%d", eta_region);
	       
	    _histos.Fill1D(string("smeared_loose_ZMass_vs_Eta_Before_Trk_Vtx_")+vtx_region_char+string("_")+eta_region_char, mass, evtweight);
	    //if(passesTrkEff[ielec_probe]) {	     	      
	    if(passesLooseTrkEff[ielec_probe]&&passesElecUParaEff[ielec_probe]&&passesSETeff[ielec_probe]/*&&passesEMIDEff[ielec_probe]*/) {
	      _histos.Fill1D(string("smeared_loose_ZMass_vs_Eta_After_Trk_Vtx_")+vtx_region_char+string("_")+eta_region_char, mass, evtweight);	      
	      if (InCC[ielec_probe]){
		_histos.Fill2D("smeared_loose_ZMass_vs_DetEta_After_Trk_CC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
		_histos.Fill2D("smeared_loose_ZMass_vs_Eta_After_Trk_CC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
		_histos.Fill2D("smeared_loose_ZMass_vs_Pt_After_Trk_CC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D("smeared_loose_ZMass_vs_Vtx_After_Trk_CC", v_z, mass, evtweight);
		_histos.Fill2D("smeared_loose_Eta_vs_Pt_After_Trk_CC", emobjs_smear[ielec_probe].ppt(), emobjs_smear[ielec_probe].eta(), evtweight);
		_histos.Fill2D("smeared_loose_Eta_vs_Vtx_After_Trk_CC", v_z, emobjs_smear[ielec_probe].eta(), evtweight);
		_histos.Fill2D(string("smeared_loose_ZMass_vs_Pt_After_Trk_CC_Etabin_")+bins_Eta, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D(string("smeared_loose_ZMass_vs_Vtx_After_Trk_CC_Etabin_")+bins_Eta, v_z, mass, evtweight);
		_histos.Fill2D(string("smeared_loose_ZMass_vs_Pt_After_Trk_CC_SETbin_")+bins_SET, emobjs_smear[ielec_probe].ppt(), mass, evtweight);
	      } else if (InEC[ielec_probe]){
		_histos.Fill2D("smeared_loose_ZMass_vs_DetEta_After_Trk_EC", emobjs_smear[ielec_probe].deteta(), mass, evtweight);
		_histos.Fill2D("smeared_loose_ZMass_vs_Eta_After_Trk_EC", emobjs_smear[ielec_probe].eta(), mass, evtweight);
		_histos.Fill2D("smeared_loose_ZMass_vs_Pt_After_Trk_EC", emobjs_smear[ielec_probe].ppt(), mass, evtweight);
		_histos.Fill2D("smeared_loose_ZMass_vs_Vtx_After_Trk_EC", v_z, mass, evtweight);
	      }
	    }
	  } // probe electron
	} // tag electron
	   
      } // use each electron as a tag electron and use the other as the probe electron



       
      // study pT dependence for uparallel efficiency
      // tag electron can be either in CC or EC, while the probe electron must be in CC
      TVector2 recoil_vect=zcand.GetRecoilVec();

      for(int ielec_tag=0; ielec_tag<2; ielec_tag++) {
	if(passesAllEMEff[ielec_tag] && passesElecUParaEff[ielec_tag] && 
	   //	   emobjs_smear[ielec_tag].ppt()>25. && (InCC[ielec_tag] || InEC[ielec_tag]) && 
	   emobjs_smear[ielec_tag].ppt()>25. && InCC[ielec_tag] && 
	   //	   mass>_ZMassCut1 && mass<_ZMassCut2) { 
	   mass>50. && mass<150.) { 
	  
	  // get the other electron as the probe electron
	  int ielec_probe = 0;
	  if(ielec_tag == 0) ielec_probe = 1;

	  // tag electron can be either in CC or EC, while the probe electron must be in CC
	  if(InCC[ielec_probe]) {
	    double elec_eta = emobjs_smear[ielec_probe].peta();
	    char bins_Eta[10];
	    int bin_Eta_number;
	    if(elec_eta<-1.3)
	      bin_Eta_number=0;
	    else if(elec_eta>1.3)
	      bin_Eta_number=14;
	    else
	      bin_Eta_number=int((elec_eta+1.3)/0.2)+1;
	    sprintf(bins_Eta, "%d", bin_Eta_number);
	    
	    if(passesTrigEff[ielec_probe] && passesPreselEff[ielec_probe]){
	      TVector2 elec_vect(emobjs_smear[ielec_probe].ppx(),emobjs_smear[ielec_probe].ppy());
	      double zupara=recoil_vect*elec_vect.Unit();

	      _histos.Fill1D("smeared_elecpT", emobjs_smear[ielec_probe].ppt(), evtweight);
	      _histos.Fill1D(string("smeared_elecpT_")+bins_Eta, emobjs_smear[ielec_probe].ppt(), evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_UPara_Before_CC", zupara, mass,  evtweight);
	      _histos.Fill2D("smeared_ZMass_vs_UPara_Before_CC_ScaleToW", zupara*80.419/91.188, mass,  evtweight);
	      if(passesAllEMEff[ielec_probe] && passesElecUParaEff[ielec_probe] && passesSETeff[ielec_probe]) {
		_histos.Fill1D("smeared_elecpT_after", emobjs_smear[ielec_probe].ppt(), evtweight);
		_histos.Fill1D(string("smeared_elecpT_after_")+bins_Eta, emobjs_smear[ielec_probe].ppt(), evtweight);
		_histos.Fill2D("smeared_ZMass_vs_UPara_After_CC", zupara, mass,  evtweight);
		_histos.Fill2D("smeared_ZMass_vs_UPara_After_CC_ScaleToW", zupara*80.419/91.188, mass,  evtweight);
	      }
	    }
	  } // probe electron in CC region
	} // tag electron
      } // use each electron as a tag electron and use the other as the probe electron
      
    } // select Z events for CCCC or CCEC
  } // two electrons with pT>20 GeV
}


void ZAnalysis::TagProbeEffBIASESStudies(std::vector<PMCSEMObj>& emobjs_smear, PMCSVtx& vtx_gen, PMCSRecoil& recoil_smear, PMCSMet& met_smear, TRandom3* dummy, double evtweight) {
  
  if( (emobjs_smear[0].ppt()>20.) && (emobjs_smear[1].ppt()>20.) ) {
    PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);
    
    double mass = zcand.mass();
    int type = zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);
    double v_z = vtx_gen.vtxz();
    double zScalarEt = _recoilsmear->scalarEt();

    // select Z events
    //if((type==0)) {
    if((type==0 || type==1 || type==2 )) { 

      double TrigVer = dummy->Uniform(0., 1.);
      bool passesTrigEff[2], passesPreselEff[2], passesEMIDEff[2], passesTrkEff[2], passesElecUParaEff[2], passesLooseTrkEff[2],passesElecPhiEff[2];
      bool passesAllEMEff[2], passesAllEMEffUParaEff[2];
      bool passesSETeff[2];
      bool InCC[2], InEC[2];
      bool passesTrigEffT[2][3];
      for(int ielec=0; ielec<2; ielec++) {
		// calorimeter region
		InCC[ielec] = emobjs_smear[ielec].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);
		InEC[ielec] = emobjs_smear[ielec].IsEC(_CutEtaEC1, _CutEtaEC2);

		// efficiencies
		passesTrigEff[ielec] = true;
		if(_ZtrigEffCorrection) passesTrigEff[ielec] = _efficiencysmear->passesTriggerEff(emobjs_smear[ielec], dummy, TrigVer, _ZBrunNum);
		for (int forcet=0;forcet<3;++forcet){
		  passesTrigEffT[ielec][forcet] = _efficiencysmear->passesTriggerEff(emobjs_smear[ielec], dummy, TrigVer, _ZBrunNum,0,forcet+1);
		}
		passesPreselEff[ielec] = true;
		if(_ZpreselEffCorrection) passesPreselEff[ielec] = _efficiencysmear->passesPreselEff(emobjs_smear[ielec], dummy, 0, &vtx_gen,0,1);
		passesEMIDEff[ielec] = true;
		if(_ZIDEffCorrection) passesEMIDEff[ielec] = _efficiencysmear->passesEMIDEff(emobjs_smear[ielec], dummy);
		passesTrkEff[ielec] = _efficiencysmear->passesTrkEff(emobjs_smear[ielec], vtx_gen, dummy);
		passesLooseTrkEff[ielec] = _efficiencysmear->passesLooseTrkEff(emobjs_smear[ielec], &vtx_gen, dummy);
		passesTrkEff[ielec] = (passesTrkEff[ielec]&& passesLooseTrkEff[ielec]); 
		if(_ZElecPhiEffCorrection) {
        	  passesElecPhiEff[ielec] = true; 
        	  passesElecPhiEff[ielec] = _efficiencysmear->passesElecPhiEff(emobjs_smear[ielec], dummy, _ZElecPhiEffCorrectionUseDetPhi);
        	  passesTrkEff[ielec] = passesTrkEff[ielec] && passesElecPhiEff[ielec]; 
		}
		// uparallel efficiency
		passesElecUParaEff[ielec] = true;
		double upara = 0.;
		if(ielec==0) upara = zcand.UPara1();
		else upara = zcand.UPara2();
		passesElecUParaEff[ielec] = passesUParaEff(emobjs_smear[ielec], upara, dummy);
		// all EM identification efficiency
		passesAllEMEff[ielec] = passesTrigEff[ielec] && passesPreselEff[ielec] && passesEMIDEff[ielec] && passesTrkEff[ielec] && passesLooseTrkEff[ielec] && (emobjs_smear[ielec].trkpT()>_trkpTCut) ;
		// all EM identification efficiency and uparallel efficiency
		passesAllEMEffUParaEff[ielec] = passesAllEMEff[ielec] && passesElecUParaEff[ielec];
      }//for(int ielec=0; ielec<2; ielec++) {
      // SET efficiency
      double scalarEt_All=_recoilsmear->scalarEt();
      bool evtSETeff=_SETefficiencysmear->passesSETeff(scalarEt_All,emobjs_smear[0].getLumi(),
						       dummy, NULL, emobjs_smear[0].ppt(), emobjs_smear[1].ppt(), InEC[0], InEC[1], emobjs_smear[0].deteta(), emobjs_smear[1].deteta(), zcand.UPara1(), zcand.UPara2());
      passesSETeff[0]=_SETefficiencysmear->passesFirst();
      passesSETeff[1]=_SETefficiencysmear->passesSecond();
      // everything up to here is the same as in ZAnalysis::TagProbeEfftudies in this source file

 
      //This code follows the logic of "Track matching efficiency"
      //part of ZAnalysis::TagProbeEfftudies in this source file
      //and of EffAnalysis::LooseTrackMatchEff in wmass_analysis/src/EffAnalysis.cpp
      //

      bool pass_common = false;//common requirement for both tag and probe
      // we require passing SET eff for both objects
      // b/c tag requirement and probe numerator requirement involve tracking
      // and SET eff is mostly tracking efficiency;
      // in principle SETEff requirement on the tag
      // should be dropped if tag requirement is changed to cal-based cuts
      // also i ignored completely UParaEff here
      // this needs to be revisited -> look at UPare Eff determination
      pass_common = emobjs_smear[0].ppt()>25. &&  emobjs_smear[1].ppt()>25. &&   
            		(InCC[0] || InEC[0]) && (InCC[1] || InEC[1]) &&
                    passesSETeff[0] && passesSETeff[1] &&
            		mass>50. && mass<150.;	

					//cout<<"pass pt1 pt2 fid0 fid1 set0 set1 mass   "
					//<<pass_common <<"  "<<  
					//emobjs_smear[0].ppt()<<"  "<<  
					//emobjs_smear[1].ppt()<<"  "<<   
					//(InCC[0] || InEC[0]) <<"  "<< 
					//(InCC[1] || InEC[1]) <<"  "<<
					//passesSETeff[0] <<"  "<< passesSETeff[1] <<"  "<<
					//mass<<endl;		   

      if(pass_common==true){
    	// loop over two electrons and use each one as the tag and use the other one as the probe
    	for(int ielec_tag=0; ielec_tag<2; ielec_tag++) {

          // tag requirement below
          //cout<<"trkpt passtrkeff  "
          //<<emobjs_smear[ielec_tag].trkpT()<<"  "<<
          //passesTrkEff[ielec_tag]<<endl;
       	  if(emobjs_smear[ielec_tag].trkpT()>_trkpTCut  && 		
        	 passesTrkEff[ielec_tag]/*this is the cut to vary*/
            ) { 
	    	// get the other electron as the probe electron
	    	int ielec_probe = 0;
	    	if(ielec_tag == 0) ielec_probe = 1;
	    	if (InCC[ielec_probe]) {
		       _histos.Fill2D("smeared_loose_ZMass_vs_varbinPt_Before_Trk_CC", mass, emobjs_smear[ielec_probe].ppt(), evtweight);
	    	   // probe electron must passesLooseTrkEff
	    	   if (passesLooseTrkEff[ielec_probe]) {
		          _histos.Fill2D("smeared_loose_ZMass_vs_varbinPt_After_Trk_CC", mass, emobjs_smear[ielec_probe].ppt(), evtweight);
	    	   }//probe passesLooseTrkEff
	    	}//probe in CC
	      }//tag
		}//loop over electrons
      }//if(pass_common==true){
    } // select Z events for CCCC or CCEC
  } // two electrons with pT>20 GeV
}

// determine electron energy scale
void ZAnalysis::energyScaleStudy(vector<PMCSEMObj> &emobjs_gen, PMCSVtx &vtx_gen, vector<PMCSEMObj> &emobjs_smear, PMCSMet &met_smear, PMCSRecoil &recoil_smear, TRandom3 *dummy, double evtweight) {

  // get raw energy scale and energy offset smearing parameters first
  double scale_cc_raw = _emsmear->Scale_CC();
  double offset_cc_raw = _emsmear->Offset_CC();
  double scale_ec_raw = _emsmear->Scale_EC();
  double offset_ec_raw = _emsmear->Offset_EC();  

  // get energies below electron window simulation from the smeared electron objects
  double rawpTUnderElecWindow_old[2];
  for(int ielec=0; ielec<2; ielec++) rawpTUnderElecWindow_old[ielec] = emobjs_smear[ielec].RawpTUnderElecWindow();

  // energy difference between single energy electron with and without ZB overlay
  double energyDiffElecWithWithoutZBOverlay[2];
  for(int ielec=0; ielec<2; ielec++) energyDiffElecWithWithoutZBOverlay[ielec] = emobjs_smear[ielec].getEnergyDiffElecWithWithoutZBOverlay();
  
  //
  // generator-level objects
  // here is the strategy we use to determine electron energy scale
  // first check whether GENERATOR-LEVEL electrons passes all efficiencies cuts
  // then smear these two electrons by changing electron energy scale parameters (fix all other parameters)
  // we choose this way because it is slow to check efficiencies for each smeared electrons
  // 

  double scale_new=1., offset_new=0.;
  if(emobjs_gen.size()>=2) {
    int ihist=0;
    char sn[100];

    // passes all selection efficiencies and have pt > 18 GeV
    // this should not affect energy scale and offset determination
    bool passesEffs = passesAllNonUParaEffs(emobjs_gen[0], emobjs_gen[1], vtx_gen, dummy,dummy->Uniform(0.,.1));

    if(passesEffs && emobjs_gen[0].ppt()>18. && emobjs_gen[0].ppt()>18.) {

      // get two electrons generator level information
      double energy_gen[2], eta_gen[2], phi_gen[2], theta_gen[2], deteta_gen[2], detphi_gen[2];
      for(int ielec=0; ielec<2; ielec++) {
	energy_gen[ielec] = emobjs_gen[ielec].pE();
	eta_gen[ielec] = emobjs_gen[ielec].peta();
	theta_gen[ielec] = 2.*atan(exp(-eta_gen[ielec]));
	phi_gen[ielec] = emobjs_gen[ielec].pphi();
	deteta_gen[ielec] = emobjs_gen[ielec].deteta();
	detphi_gen[ielec] = emobjs_gen[ielec].detphi();
      }

      //
      // create scale and offset grids
      //
      for(int iscale=0; iscale<=_Bins_ScaleStudy; iscale++) {
	for(int ioffset=0; ioffset<=_Bins_ScaleStudy; ioffset++) {
 	  scale_new = _scale_center + (iscale-_Bins_ScaleStudy/2)*_scale_step;
 	  offset_new = _offset_center + (ioffset-_Bins_ScaleStudy/2)*_offset_step;

	  // use different energy scale and energy offset values
	  if(_StudyCCScale) _emsmear->SetCCScaleSmearParameters(scale_new, offset_new);
	  else _emsmear->SetECScaleSmearParameters(scale_new, offset_new);
	  
	  // smear two electrons
	  double energy_smear[2], energy_smear_beforeUECorr[2], pT_smear[2], pX_smear[2], pY_smear[2], pZ_smear[2], EMCorrFactor[2], rawpTUnderElecWindow[2];
	  double eta_smear[2], phi_smear[2], deteta_smear[2], detphi_smear[2], theta_smear[2],trkpt[2];
	  bool lost[2];

	  for(int ielec=0; ielec<2; ielec++) {
	    // NOTE: no energies below electron window simulation since I turned it off
	    // so rawpTUnderElecWindow, UParaCorr, Delta_ZSUP, EnergyLeakage are not caluclated, and the information will not be saved to the electron object
	    bool dum;
	    _emsmear->Smear(energy_gen[ielec], eta_gen[ielec], phi_gen[ielec], 
			    deteta_gen[ielec], detphi_gen[ielec], dummy,
                            eta_smear[ielec], phi_smear[ielec], 
			    deteta_smear[ielec], detphi_smear[ielec], energy_smear_beforeUECorr[ielec], dum, 11., vtx_gen.vtxz()); 
	    
	    // now add that contribution calculated before
	    _emsmear->CorrectEnergyUnderElecWindow(energy_smear_beforeUECorr[ielec], eta_smear[ielec], rawpTUnderElecWindow_old[ielec], energyDiffElecWithWithoutZBOverlay[ielec], energy_smear[ielec]);
	    
	    theta_smear[ielec] = 2.*atan(exp(-eta_smear[ielec]));
	    pT_smear[ielec] = energy_smear[ielec] * sin(theta_smear[ielec]);
	    pX_smear[ielec] = pT_smear[ielec] * cos(phi_smear[ielec]);
	    pY_smear[ielec] = pT_smear[ielec] * sin(phi_smear[ielec]);
	    pZ_smear[ielec] = energy_smear[ielec] * cos(theta_smear[ielec]);
	    lost[ielec] = emobjs_smear[ielec].IsLostInAcrack();
	    trkpt[ielec] = emobjs_smear[ielec].trkpT();
	  }
	  
	  // smeared electrons pass pT cut
	  if( (pT_smear[0]>_CutEPT1_lo) && (pT_smear[1]>_CutEPT2_lo)
	      && (pT_smear[0]<_CutEPT1_hi) && (pT_smear[1]<_CutEPT2_hi)
	      && (trkpt[0]>_trkpTCut) && (trkpt[1]>_trkpTCut)
	      && (!lost[0]) && (!lost[1])
	      ) {
	    
	    double energy_Z = energy_smear[0] + energy_smear[1];
	    double pX_Z = pX_smear[0] + pX_smear[1];
	    double pY_Z = pY_smear[0] + pY_smear[1];
	    double pZ_Z = pZ_smear[0] + pZ_smear[1];
	    double pT_Z = sqrt(pX_Z * pX_Z + pY_Z * pY_Z);
	    double pX_met = met_smear.metx();
	    double pY_met = met_smear.mety();
	    double RecoilPt_Z = sqrt((pX_Z+pX_met)*(pX_Z+pX_met)+(pY_Z+pY_met)*(pY_Z+pY_met));

            // Z boson Ut cut, not ZpT cut
            if( passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy)  && (RecoilPt_Z < _CutZUT) && (RecoilPt_Z >= _CutZUT_lower)) {
	    //if(RecoilPt_Z < _CutZUT) {
  	      double mass = sqrt(energy_Z*energy_Z-pX_Z*pX_Z-pY_Z*pY_Z-pZ_Z*pZ_Z);
              sprintf(sn, "%d", ihist);
	      
	      // cosine of the open angle between the two electrons
	      // cos(alpha) = V dot W / (|V| * |W|)
	      double cos_alpha_EM_EM = (pX_smear[0]*pX_smear[1] + pY_smear[0]*pY_smear[1] + pZ_smear[0]*pZ_smear[1])/(energy_smear[0]*energy_smear[1]);

	      // f is calculated as f = 2 *(E1+E2) * sin(alpha/2)/Mass = 2*(E1+E2)*(1-cos(alpha))/2./Mass=(E1+E2)*(1-cos(alpha))/Mass
	      double f = energy_Z * (1-cos_alpha_EM_EM)/mass;

	      // require electron to be in phi fiducial region
	      double phimod0 = fmod(detphi_smear[0]*16./TMath::Pi(), 1.0);
	      double phimod1 = fmod(detphi_smear[1]*16./TMath::Pi(), 1.0);

	      if(_StudyCCScale) {
	        if( (fabs(deteta_smear[0])<_CutEtaCC) && (fabs(deteta_smear[1])<_CutEtaCC) && 
		    phimod0>0.1 && phimod0<0.9 && phimod1>0.1 && phimod1<0.9) { // for CC region
		  _histos.Fill1D(string("smeared_hZcandMass_Scale_CCCC_")+sn, mass, evtweight);
		  _histos.Fill2D(string("smeared_hZcandMass_V_fZ_CCCC_")+sn, f, mass, evtweight);
		  _histos.FillProfile(string("smeared_hZcandMass_V_fZ_CCCC_pro_")+sn, f, mass, evtweight);
	        } // CCCC region
	      } else {  // for EC region
	        if( (fabs(deteta_smear[0])<_CutEtaEC2 && fabs(deteta_smear[0])>_CutEtaEC1) && 
		    (fabs(deteta_smear[1])<_CutEtaEC2 && fabs(deteta_smear[1])>_CutEtaEC1) ) {
		  _histos.Fill1D(string("smeared_hZcandMass_Scale_ECEC_")+sn, mass, evtweight);
		  _histos.Fill2D(string("smeared_hZcandMass_V_fZ_ECEC_")+sn, f, mass, evtweight);
		  _histos.FillProfile(string("smeared_hZcandMass_V_fZ_ECEC_pro_")+sn, f, mass, evtweight);
	        } // ECEC region
	      }
            } // Z boson Ut cut
	  } //pass electron pT cut
	  
	  ihist++;  // for all grid points

	}//ioffset
      }//iscale      
    } // passes all selection efficiencies

  }//at least two electrons
  
  // set back the raw smearing parameters
  // I do not want to mess up the rest code
  if(_StudyCCScale)
    _emsmear->SetCCScaleSmearParameters(scale_cc_raw, offset_cc_raw);
  else 
    _emsmear->SetECScaleSmearParameters(scale_ec_raw, offset_ec_raw);
}

void ZAnalysis::TBStudy(vector<PMCSEMObj>& emobjs_orig,  PMCSRecoil recoil_smear,TRandom3 * dummy, double *external_upara_rnd1, double *external_upara_rnd2, double *external_SET_rnd, double evtweight, double luminosity, PMCSVtx &vtx_gen, double * externalRndmo){
  int ihist=0;
  char sn[100];
  vector<PMCSEMObj> emobjs_smear;
  double recoilx_beforeTB = _recoilsmear->recoilx_beforeTB();
  double recoily_beforeTB = _recoilsmear->recoily_beforeTB();
  
  double alpha_original=0., beta_original=0.;
  _recoilsmear->GetTBAsymmParameters(alpha_original,beta_original);
  double recoilx=0., recoily=0.;

 
  // do not change soft component smearing if rotating Hard Component Only
  double recoilX_SoftComponent = _recoilsmear->recoilX_SoftComponent();
  double recoilY_SoftComponent = _recoilsmear->recoilY_SoftComponent();
  
  // do not change hard component smearing if rotating soft  Component Only
  double recoilX_HardComponent = _recoilsmear->recoilX_HardComponent();
  double recoilY_HardComponent = _recoilsmear->recoilY_HardComponent();
  Double_t extrndm[emobjs_orig.size()][4];
  for (Int_t iecounter=0; iecounter <emobjs_orig.size(); ++iecounter){
    for (Int_t icounter=0; icounter <4; ++icounter){
      extrndm[iecounter][icounter] = dummy->Rndm(); 
    }
  }
  if (!_Top_Bottom_Apply_Last){
    for(int ielec=0; ielec<emobjs_orig.size(); ielec++) {
      if(abs(emobjs_orig[ielec].ppt()) > 15.) {
	emobjs_orig[ielec].SetLumi(luminosity);
      }
    }
  }

  double externalRndm[18];
    if (externalRndmo){
      for (int i=0; i<18; i++) externalRndm[i]=externalRndmo[i];
    }
    else{
      for (int i=0; i<18; i++) externalRndm[i]=dummy->Uniform(0., 1.);
    }
  
    double Trigger_Version = dummy->Uniform(0., 1.);
  emobjs_smear= emobjs_orig;
  for(int iscale=0; iscale<=_Bins_TBStudy; iscale++) {
    for(int ioffset=0; ioffset<=_Bins_TBStudy; ioffset++) {
      
      double scale_new = _tbalpha_center + (iscale-_Bins_TBStudy/2)*_tbalpha_step;
      double offset_new = _tbbeta_center + (ioffset-_Bins_TBStudy/2)*_tbbeta_step;
      sprintf(sn, "%d", ihist);
      recoilx = recoilx_beforeTB;
      recoily = recoily_beforeTB;
      _recoilsmear->SetTBAsymmParameters(scale_new, offset_new);
      _recoilsmear->ApplyTopBottomAsym(recoilx,recoily);

 
	

      if (_TBPhi_response_Hard_Only){
	
	recoilx = recoilx + recoilX_SoftComponent;
	recoily = recoily + recoilY_SoftComponent;
      }

      if (_TBPhi_response_Soft_Only){
	
	recoilx = recoilx + recoilX_HardComponent;
	recoily = recoily + recoilY_HardComponent;
      }
     

    
      PMCSRecoil new_recoil = recoil_smear;
      if (!_Top_Bottom_Apply_Last){
	emobjs_smear= emobjs_orig;
	TVector2 recoil_vec(recoilx, recoily);
        double ScalarEt = _recoilsmear->scalarEt();
	for(int ielec=0; ielec<emobjs_smear.size(); ielec++) {
	  // new requirement, only do this for electron, similar already included in EMSmear
	  // here I want to make sure that we only do this for real electrons
	  if(abs(emobjs_smear[ielec].ppt()) > 15.) {
	    emobjs_smear[ielec].SetLumi(luminosity);
            emobjs_smear[ielec].SetScalarEt(ScalarEt);

	    TVector2 elec_vec(emobjs_smear[ielec].ppx(), emobjs_smear[ielec].ppy());
	    double upara_elec = recoil_vec*elec_vec.Unit();
	    double uperp_elec = recoil_vec*elec_vec.Unit().Rotate(TMath::Pi()/2.0);
	    emobjs_smear[ielec].SetUPara(upara_elec);
	    emobjs_smear[ielec].SetUPerp(uperp_elec);
	    _emsmear->SmearEnergyUnderElecWindow(emobjs_smear[ielec],dummy,kFALSE,extrndm[ielec]);
	  }
	}
      
	sort(emobjs_smear.begin(), emobjs_smear.end(), ComparePt);
	recoil_smear.SetRecoil(recoilx,recoily);
	new_recoil = recoil_smear;
	if(_ZUparaCorrection)
	  _recoilsmear->applyUparaCorrection(emobjs_smear, recoil_smear, new_recoil, 0);
      
	recoilx = new_recoil.Recoilx();
	recoily = new_recoil.Recoily();
	for(int i=0; i<emobjs_smear.size(); i++) {
	  if (i > 1){
	    if (!_ZsimuFSRcracks) {
	      recoilx += emobjs_smear[i].ppx();
	      recoily += emobjs_smear[i].ppy();
	    } else {
	      float deteta=emobjs_smear[i].deteta();
	      float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	      if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
		recoilx += emobjs_smear[i].ppx();
		recoily += emobjs_smear[i].ppy();
	      }
	    }
	  }
	}

      }
//        if ((scale_new == alpha_original) && (offset_new == beta_original)){
// 	 std::cout <<  " recoilx " <<recoilx << "   recoily " << recoily  << std::endl;
// 	 std::cout << recoil_smear.Recoilx() << "  " <<  recoil_smear.Recoily() << std::endl;     ;
//        }

      new_recoil.SetRecoil(recoilx,recoily);
      PMCSMet new_met_smear= PMCSMet(emobjs_smear,new_recoil);
      
      if( emobjs_smear.size()>=2 ) {
	double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+new_recoil.Recoilx());
	double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+new_recoil.Recoily());
	new_met_smear.SetMet(metX_component, metY_component);
      }
      //   int ncuts=0;
      //int passNonUParaEffs;
      //double Trigger_Version;

      if(!passesAllNonUParaEffs(emobjs_smear[0],emobjs_smear[1],vtx_gen,dummy,Trigger_Version,externalRndm)){ 
	continue;
      }


      if (passesRecoilCuts(emobjs_smear,
			   new_recoil,
			   new_met_smear,
			   dummy,
			   NULL,
			   NULL,
			   false,
			   external_upara_rnd1, 
			   external_upara_rnd2,
			   external_SET_rnd) ){ //&&   
	//  	  bool t1 = passesEMCuts(emobjs_smear,
	//  		       vtx_gen,
	//  		       dummy,
	//  		       &ncuts,
	//  		       &Trigger_Version,
	// 				 &passNonUParaEffs); 
	// 	std::cout << "PassEM " << t1 << "  ncuts " << ncuts << " Trigger_version " << Trigger_Version << " onupara " << passNonUParaEffs << std::endl;
	
	
	//	std::cout << "Template Recoil Phi: " << new_recoil.RecoilPhi() << std::endl;
	//	std::cout << "Template MET Phi: " << new_met_smear.metphi() << std::endl;
	_histos.Fill1D(string("smeared_hZcandRecoilPhi_CCCC_")+sn, new_recoil.RecoilPhi(), evtweight);
	_histos.Fill1D(string("smeared_hZcandMETPhi_CCCC_")+sn, new_met_smear.metphi(), evtweight);
      }
      ihist++;
    }
    
  }
  
  _recoilsmear->SetTBAsymmParameters(alpha_original, beta_original);
  
}

void ZAnalysis::radLengthStudy(vector<PMCSEMObj> &emobjs_gen,  vector<PMCSEMObj> &emobjs_smear,TRandom3 *dummy, double evtweight) {
  // get raw Trk  smearing parameters first 
  double A_raw_CC = _emsmear->TrkA_CC();
  double B_raw_CC = _emsmear->TrkB_CC();
  double C_raw_CC = _emsmear->TrkC_CC();

  double radlength_EC = _emsmear->TrkRadLength_EC();
  double A_raw_EC = _emsmear->TrkA_EC();
  double B_raw_EC = _emsmear->TrkB_EC();
  double C_raw_EC = _emsmear->TrkC_EC();

  if(emobjs_smear.size()>=2) {
    int ihist=0;
    char sn[100];    
    // Re-establish correspondence between true and smeared electrons
    PMCSEMObj* CorrespondingTrue[2]={0,0};
    for(int oelec=0; oelec<emobjs_gen.size(); oelec++) {
      if (emobjs_gen[oelec].getIndex() == emobjs_smear[0].getIndex()){
	CorrespondingTrue[0]=&(emobjs_gen[oelec]);
      }
      if (emobjs_gen[oelec].getIndex() == emobjs_smear[1].getIndex()){
	CorrespondingTrue[1]=&(emobjs_gen[oelec]);
      }
    }
    assert(CorrespondingTrue[0]&&CorrespondingTrue[1]);

    // pre-chew random numbers, if needed
    double externalRndm[5];
    double externalRndm2[2][10];
    for (int i=0; i<2; i++) externalRndm[i]=dummy->Gaus(0., 1.);
    for (int i=0; i<10; i++) {externalRndm2[0][i]=dummy->Rndm(); externalRndm2[1][i]=dummy->Rndm();}
    double bremfrac[2];
    double trkpt[2];
    double detetaCal[2];
    double prob_brem[2];
    bool isCC[2];
    for(int ielec=0; ielec<2; ielec++) {
      trkpt[ielec] = CorrespondingTrue[ielec]->trkpT();
      isCC[ielec] = emobjs_smear[ielec].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);
      bremfrac[ielec] =1.;
      prob_brem[ielec] = 0.;
    }
    detetaCal[0] = emobjs_smear[1].deteta();
    detetaCal[1] = emobjs_smear[0].deteta();
    //
    // create  grids
    //
   
    for(int iA=0; iA<=_Bins_radLengthStudy_CC; iA++) {
      double radlength_new_CC = _radLengthcenter_CC + (iA-_Bins_radLengthStudy_CC/2)*_radLengthstep_CC ;
      double radlength_new_EC = _radLengthcenter_EC + (iA-_Bins_radLengthStudy_EC/2)*_radLengthstep_EC ;
      for(int iB=0; iB<=_Bins_radLengthStudy_CC; iB++) {
	double C_new = _CCMScenterC + (iB-_Bins_radLengthStudy_CC/2)*_CCMSstepC ;
	sprintf(sn, "%d", ihist);
	
	ihist++;  // for all grid points (that is, needs to go before any continue statement)
	
	// re-scale two electrons
	double TrkpTrescaled[2];
	for(int ielec=0; ielec<2; ielec++) {
	  double trkpti = trkpt[ielec];
	double A_raw =  A_raw_CC*isCC[ielec] + A_raw_EC*(!isCC[ielec]);
	double B_raw = B_raw_CC*isCC[ielec] + B_raw_EC*(!isCC[ielec]);
	double C_raw = C_new*isCC[ielec] + C_raw_EC*(!isCC[ielec]);
	double radlength_new = radlength_new_CC*isCC[ielec] + radlength_new_EC*(!isCC[ielec]);
	
	//std::cout << " I am in the template loop" << std::endl;
	_emsmear->SmearTrkpT(trkpti, dummy, TrkpTrescaled[ielec], A_raw, B_raw, C_raw, radlength_new ,bremfrac[ielec] , prob_brem[ielec], true, externalRndm[ielec], externalRndm2[ielec]);
	//	if (ielec==0 && isCC[ielec])
	//  std::cout << iA << "  " <<  radlength_new_CC << "  " << radlength_new << "  " << trkpt[ielec] <<  "  " << TrkpTrescaled[ielec] << "  " << prob_brem[ielec] << "   "<< externalRndm[ielec+2] << std::endl;
      }
      
      if ((TrkpTrescaled[0] > _trkpTCut) && (TrkpTrescaled[1] > _trkpTCut) ){
	for(int ielec=0; ielec<2; ielec++) { 
	  int itrk = 1;
	  if (ielec==itrk)
	    itrk = 0;
	  _histos.Fill1D(string("smeared_hZcandElecTrkPtOvE_All_")+sn,(TrkpTrescaled[ielec] / emobjs_smear[ielec].ppt()) , evtweight);
	  if (iA ==0 && iB==0 )
	    _histos.Fill1D("smeared_hZcandElecTrkPtOvE_All_DetEta",detetaCal[ielec], evtweight);
	  if(abs(detetaCal[ielec]) < 1.05 ) {
	    _histos.Fill1D(string("smeared_hZcandElecTrkPtOvE_CC_")+sn,(TrkpTrescaled[ielec] / emobjs_smear[ielec].ppt()) , evtweight);
	    if (abs(detetaCal[itrk]) < 1.05 ) {
	      _histos.Fill1D(string("smeared_hZcandElecTrkPtOvE_CCCC_")+sn,(TrkpTrescaled[ielec] / emobjs_smear[ielec].ppt()) , evtweight);
	      _histos.Fill1D(string("smeared_hZcandElecTrkPt_CCCC_")+sn,(TrkpTrescaled[ielec]) , evtweight);
	    }
	    if (iA ==0)
	      _histos.Fill1D("smeared_hZcandElecTrkPtOvE_CC_DetEta",detetaCal[ielec] , evtweight);
	  }	      
	  else if (abs(detetaCal[ielec]) > 1.5 && abs(detetaCal[ielec]) < 2.3  ) {
	    _histos.Fill1D(string("smeared_hZcandElecTrkPtOvE_CC_")+sn, (TrkpTrescaled[ielec] / emobjs_smear[ielec].ppt()), evtweight);
	    if (iA ==0)
	      _histos.Fill1D("smeared_hZcandElecTrkPtOvE_EC_DetEta",detetaCal[ielec] , evtweight);
	  }
	}
      }
      }
    }
  }
}
void ZAnalysis::momentumScaleStudy(vector<PMCSEMObj> &emobjs_gen,  vector<PMCSEMObj> &emobjs_smear,TRandom3 *dummy, double evtweight) {
  
  // get raw Trk  smearing parameters first 
  double C_raw = _emsmear->TrkC_CC();
  double B_raw = _emsmear->TrkB_CC();
  double A_raw = _emsmear->TrkA_CC();
  double radlength = _emsmear->TrkRadLength_CC();
  
  if(emobjs_smear.size()>=2) {
    int ihist=0;
    char sn[100];    
    // Re-establish correspondence between true and smeared electrons
    PMCSEMObj* CorrespondingTrue[2]={0,0};
    for(int oelec=0; oelec<emobjs_gen.size(); oelec++) {
      if (emobjs_gen[oelec].getIndex() == emobjs_smear[0].getIndex()){
	CorrespondingTrue[0]=&(emobjs_gen[oelec]);
      }
      if (emobjs_gen[oelec].getIndex() == emobjs_smear[1].getIndex()){
	CorrespondingTrue[1]=&(emobjs_gen[oelec]);
      }
    }
    assert(CorrespondingTrue[0]&&CorrespondingTrue[1]);
    
    // pre-chew random numbers, if needed
    double externalRndm[5];
    for (int i=0; i<5; i++) externalRndm[i]=dummy->Gaus(0., 1.);
    double bremfrac[2];
    double trkpt[2];
    double trktheta[2];
    double trketa[2];
    double detetaCal[2];
    double trkphi[2];
    double  pEtrk[2];
    double pxtrk[2];
    double pytrk[2];
    double pztrk[2];
    double proba_brem[2];
    bool   isCC[2];
    
    for(int ielec=0; ielec<2; ielec++) {
      bremfrac[ielec]=emobjs_smear[ielec].getbremfrac();
      trkpt[ielec] = CorrespondingTrue[ielec]->trkpT();
      // std::cout <<  emobjs_smear[ielec].ppt() << "   " << emobjs_smear[ielec].ppz() << "  " << emobjs_smear[ielec].pE() << "   " << emobjs_smear[ielec].ppx() << "  " << emobjs_smear[ielec].ppy() << "  " <<  emobjs_smear[ielec].ppt() / sin(emobjs_smear[ielec].theta()) <<   std::endl;
      trktheta[ielec] = emobjs_smear[ielec].theta();
      trketa[ielec] = emobjs_smear[ielec].peta();
      detetaCal[ielec] = emobjs_smear[ielec].deteta();
      trkphi[ielec] = emobjs_smear[ielec].pphi();
      isCC[ielec] = emobjs_smear[ielec].IsCC(_CutEtaCC, _phimodcut, _ApplyTrkPhiModCut);
      
    }
 
    // create  grids
    //

    for(int iA=0; iA<=_Bins_CCMSStudy; iA++) {
      for(int iB=0; iB<=_Bins_CCMSStudy; iB++) {
	double A_new_CC = _CCMScenterA + (iA-_Bins_CCMSStudy/2)*_CCMSstepA;
	double B_new_CC = _CCMScenterB + (iB-_Bins_CCMSStudy/2)*_CCMSstepB;
	double C_new_CC = _CCMScenterC + (iA-_Bins_CCMSStudy/2)*_CCMSstepC;
	double A_new_EC = _ECMScenterA + (iA-_Bins_ECMSStudy/2)*_ECMSstepA;
	double B_new_EC = _ECMScenterB + (iB-_Bins_ECMSStudy/2)*_ECMSstepB;
	double C_new_EC = _ECMScenterC + (iA-_Bins_ECMSStudy/2)*_ECMSstepC;
	
	sprintf(sn, "%d", ihist);
	ihist++;  // for all grid points (that is, needs to go before any continue statement)
	
	// re-scale two electrons
	double TrkpTrescaled[2];
	for(int ielec=0; ielec<2; ielec++) {
	  TrkpTrescaled[ielec] = trkpt[ielec]*(1. - bremfrac[ielec]) ;
	  double trkpti = TrkpTrescaled[ielec];
	  //void SmearTrkpT(double trkpT_brem, TRandom3 *dummy, double& pT_Smear,double &A, double &B, double &C, double &radlength, double &BremFraction, bool dobrem=true);
	  double A_new =  A_new_CC*isCC[ielec] + A_new_EC*(!isCC[ielec]);
	  double B_new = B_new_CC*isCC[ielec] + B_new_EC*(!isCC[ielec]);
	  double C_new = C_new_CC*isCC[ielec] + C_new_EC*(!isCC[ielec]);
	  if (_study_AB){
	    if (isCC[ielec]){
	      _emsmear->SmearTrkpT(trkpti, dummy, TrkpTrescaled[ielec], A_new, B_new  , C_raw, radlength ,bremfrac[ielec] , proba_brem[ielec], false, externalRndm[ielec]);
	    }
	  }
	  else{
	    if (isCC[ielec])
	      _emsmear->SmearTrkpT(trkpti, dummy, TrkpTrescaled[ielec], A_raw, B_new  , C_new, radlength ,bremfrac[ielec] , proba_brem[ielec], false, externalRndm[ielec]);
	  }
	  // std::cout << "trkpti = " << trkpti << " TrkpTrescaled[ielec] = " << TrkpTrescaled[ielec] << std::endl;
	  if (emobjs_smear[0].ppt() < 25.)
	    std::cout << emobjs_smear[0].ppt() << std::endl;
	  pEtrk[ielec] = TrkpTrescaled[ielec]  / sin(trktheta[ielec]) ;
	  pxtrk[ielec] = TrkpTrescaled[ielec] * cos(trkphi[ielec]);
	  pytrk[ielec] = TrkpTrescaled[ielec] * sin(trkphi[ielec]);
	  pztrk[ielec] =  pEtrk[ielec] * cos(trktheta[ielec]);
	  //pEtrk[ielec] = sqrt(pow(pxtrk[ielec],2) + pow(pytrk[ielec],2)  + pow(pztrk[ielec],2)
	  //	  std::cout <<  TrkpTrescaled[ielec] << "   " <<  pztrk[ielec] << "   " << pEtrk[ielec] << "   " <<  pxtrk[ielec] <<  "   " <<  pytrk[ielec] << "   " << trktheta[ielec] <<  std::endl;
	 
	}
	
	for(int ielec=0; ielec<2; ielec++) {
	  double zcandmass =0.;
	  if (ielec==0 &&  (TrkpTrescaled[0] > _trkpTCut) && (TrkpTrescaled[1] > _trkpTCut) )
	    zcandmass  = pow(emobjs_smear[1].pE() + pEtrk[ielec],2) - pow(emobjs_smear[1].ppx() + pxtrk[ielec],2) - pow(emobjs_smear[1].ppy() + pytrk[ielec],2) - pow(emobjs_smear[1].ppz() + pztrk[ielec],2) ;
	  else if ( ielec==1 &&  (TrkpTrescaled[0] > _trkpTCut) && (TrkpTrescaled[1] > _trkpTCut) )
	    zcandmass  = pow(emobjs_smear[0].pE() + pEtrk[ielec],2) - pow(emobjs_smear[0].ppx() + pxtrk[ielec],2) - pow(emobjs_smear[0].ppy() + pytrk[ielec],2) - pow(emobjs_smear[0].ppz() + pztrk[ielec],2) ;
	  if (zcandmass > 0.)
	    zcandmass=sqrt(zcandmass);
	  else
	    zcandmass=0.;
	  if (zcandmass > 70.  && zcandmass < 110.){
	    if(abs(detetaCal[ielec]) < 1.05 ) {
	      _histos.Fill1D(string("smeared_hZcandElecTrkCalMass_All_CC_")+sn, zcandmass, evtweight);
	    }
	    _histos.Fill1D((string("smeared_hZcandElecTrkCalMass_All_")+sn), zcandmass, evtweight);
	    
	    
	    int itrk = 1;
	    if (ielec==itrk)
	      itrk = 0;
	    if(abs(detetaCal[itrk]) < 1.05 ) {
	      _histos.Fill1D(string("smeared_hZcandElecTrkCalMass_CC_")+sn, zcandmass, evtweight);
	      
	      if(abs(detetaCal[ielec]) < 1.05 ) {
		  _histos.Fill1D(string("smeared_hZcandElecTrkCalMass_CC_CC_")+sn, zcandmass, evtweight);
	      }
	      if( abs(detetaCal[ielec]) > 1.5    && abs(detetaCal[ielec]) < 2.3 ) {
		_histos.Fill1D(string("smeared_hZcandElecTrkCalMass_CC_EC_")+sn, zcandmass, evtweight);
	      }
	    }
	  }
	}
      }//ioffset
    }//iscale      
    
  }//at least two electrons
  
}



void ZAnalysis::energyScaleStudyJan(vector<PMCSEMObj> &emobjs_gen, PMCSVtx &vtx_gen, vector<PMCSEMObj> &emobjs_smear, PMCSMet &met_smear, PMCSRecoil &recoil_smear, TRandom3 *dummy, double *external_upara_rnd1, double *external_upara_rnd2, double *external_SET_rnd,
				double evtweight,
				double *externalRndmo) {

  // There are some cuts that could have been applied before the template loop, but that have not been applied yet.
  // We do them here.
  //
  // track pT
  if(_NZTrkMatch == 2) {
    if (!((emobjs_smear[0].trkpT()>_trkpTCut)&&(emobjs_smear[1].trkpT()>_trkpTCut))) return;
  } else if(_NZTrkMatch == 1) {
    if (!((emobjs_smear[0].trkpT()>_trkpTCut)||(emobjs_smear[1].trkpT()>_trkpTCut))) return;
  }
  // Z type
  PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1]);
  int ztype=zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);
  if (_StudyCCScale) {
    if (ztype!=0) return;
  } else {
    if (ztype!=2) return;
    // Note: what we are doing here is saying that we want to use only EC-EC pairs for E-scale
    //       studies in the EC. This is very stupid, and we only do it for consistency with
    //       the normal ZAnalysis::energyScaleStudy.
  }
  // also, the trigger version has not (necessarily) been flipped yet; do it now
  double Trigger_Version = dummy->Uniform(0., 1.);
  // the EM efficiency simulation  (passesAllNonUParaEffs)
  if (!_EnergyScaleStudyJanPedantic) {
    // strictly speaking, we should evaluate these efficiencies for each re-scaled reco energy
    if (!passesAllNonUParaEffs(emobjs_smear[0], emobjs_smear[1], vtx_gen, dummy, Trigger_Version,externalRndmo)) return;
  }
  // recoil cuts
  int cuts=0;
  if (!passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
			 &cuts,
			 NULL,
			 false,
			 external_upara_rnd1, 
			 external_upara_rnd2,
			 external_SET_rnd)) return;

  // get raw energy scale and energy offset smearing parameters first
  double scale_raw;
  double offset_raw;
  double zelec_avept;
  if (_StudyCCScale) {
    scale_raw = _emsmear->Scale_CC();
    offset_raw = _emsmear->Offset_CC();
    zelec_avept = _emsmear->ZElec_AvePt_CC();
  } else {
    scale_raw = _emsmear->Scale_EC();
    offset_raw = _emsmear->Offset_EC();
    zelec_avept = _emsmear->ZElec_AvePt_EC();
  }

  double scale_new=1., offset_new=0.;

  if(emobjs_smear.size()>=2) {
    int ihist=0;
    char sn[100];

    // Re-establish correspondence between true and smeared electrons
    PMCSEMObj* CorrespondingTrue[2]={0,0};
    for(int oelec=0; oelec<emobjs_gen.size(); oelec++) {
      if (emobjs_gen[oelec].getIndex() == emobjs_smear[0].getIndex()){
	CorrespondingTrue[0]=&(emobjs_gen[oelec]);
      }
      if (emobjs_gen[oelec].getIndex() == emobjs_smear[1].getIndex()){
	CorrespondingTrue[1]=&(emobjs_gen[oelec]);
      }
    }
    assert(CorrespondingTrue[0]&&CorrespondingTrue[1]);

    // pre-chew random numbers, if needed
    double externalRndm[18];
    if (_EnergyScaleStudyJanPedantic) {
      if (externalRndmo){
	for (int i=0; i<18; i++) externalRndm[i]=externalRndmo[i];
      }
      else{
	for (int i=0; i<18; i++) externalRndm[i]=dummy->Uniform(0., 1.);
      }
    }

    //
    // create scale and offset grids
    //
    for(int iscale=0; iscale<=_Bins_ScaleStudy; iscale++) {
      for(int ioffset=0; ioffset<=_Bins_ScaleStudy; ioffset++) {
	scale_new = _scale_center + (iscale-_Bins_ScaleStudy/2)*_scale_step;
	offset_new = _offset_center + (ioffset-_Bins_ScaleStudy/2)*_offset_step;

	sprintf(sn, "%d", ihist);

	ihist++;  // for all grid points (that is, needs to go before any continue statement)

	// re-scale two electrons
	double Erescaled[2];
	double pXrescaled[2];
	double pYrescaled[2];
	double pZrescaled[2];
	double pTrescaled[2];
	for(int ielec=0; ielec<2; ielec++) {
	  double E0 = scale_raw*(CorrespondingTrue[ielec]->pE()-zelec_avept)+offset_raw +zelec_avept ;
	  double Eprime = scale_new*(CorrespondingTrue[ielec]->pE()-zelec_avept)+offset_new+zelec_avept ;
	  if (_emsmear->doCCscale_lumidep()==2 && fabs(CorrespondingTrue[ielec]->deteta())<1.3) {
            double p0=_emsmear->CCscale_lumidepFP_p0_q0()+_emsmear->CCscale_lumidepFP_p0_q1()*_emsmear->theLumi();
            double p2=_emsmear->CCscale_lumidepFP_p2_q0()+_emsmear->CCscale_lumidepFP_p2_q1()*_emsmear->theLumi();
            double loss=p0+p2*pow(CorrespondingTrue[ielec]->deteta(),2)-_emsmear->CCscale_lumidepFP_typical();
            E0*=(1-loss);
            Eprime*=(1-loss);
	    if (_emsmear->CCscale_DetEtaAdjust()) {
              double absdeteta = fabs(CorrespondingTrue[ielec]->deteta());
              int region;
              if(absdeteta<0.2) region = 0;
              else if(absdeteta<0.4) region = 1;
              else if(absdeteta<0.6) region = 2;
              else if(absdeteta<0.8) region = 3;
              else region = 4;
              E0*=_emsmear->CCscale_DetEtaAdjust_factors()[region];
              Eprime*=_emsmear->CCscale_DetEtaAdjust_factors()[region];
            }
          }
	  Erescaled[ielec]=emobjs_smear[ielec].pE()-E0+Eprime;
	  //
	  pXrescaled[ielec]=emobjs_smear[ielec].ppx()*(Erescaled[ielec]/emobjs_smear[ielec].pE());
	  pYrescaled[ielec]=emobjs_smear[ielec].ppy()*(Erescaled[ielec]/emobjs_smear[ielec].pE());
	  pZrescaled[ielec]=emobjs_smear[ielec].ppz()*(Erescaled[ielec]/emobjs_smear[ielec].pE());
	  pTrescaled[ielec]=sqrt(pXrescaled[ielec]*pXrescaled[ielec]+pYrescaled[ielec]*pYrescaled[ielec]);
	}

	// strictly speaking, this is the right place to evaluate EM efficiencies
	if (_EnergyScaleStudyJanPedantic) {
	  // the copied EM objects need correct: pT, det_eta, eta
	  PMCSEMObj emobj1resc=emobjs_smear[0];
	  emobj1resc.SetEnergyEtaPhi(Erescaled[0],emobjs_smear[0].peta(),emobjs_smear[0].pphi());
	  PMCSEMObj emobj2resc=emobjs_smear[1];
          emobj2resc.SetEnergyEtaPhi(Erescaled[1],emobjs_smear[1].peta(),emobjs_smear[1].pphi());
	  if (!passesAllNonUParaEffs(emobj1resc,emobj2resc,vtx_gen,dummy,Trigger_Version,externalRndm)) continue;
	}

	// re-calculate Z properties
	double energy_Z = Erescaled[0] + Erescaled[1];
	double pX_Z = pXrescaled[0] + pXrescaled[1];
	double pY_Z = pYrescaled[0] + pYrescaled[1];
	double pZ_Z = pZrescaled[0] + pZrescaled[1];
	double mass = sqrt(energy_Z*energy_Z-pX_Z*pX_Z-pY_Z*pY_Z-pZ_Z*pZ_Z);

	// Cuts
	//
	// pT(e)
	if ((pTrescaled[0]<_CutEPT1_lo)||(pTrescaled[0]>_CutEPT1_hi)) continue;
	if ((pTrescaled[1]<_CutEPT2_lo)||(pTrescaled[1]>_CutEPT2_hi)) continue;
	// Z mass
	if ((mass<_ZMassCut1)||(mass>_ZMassCut2)||(sqrt(pX_Z*pX_Z+pY_Z*pY_Z)>_CutZPT) || (sqrt(pX_Z*pX_Z+pY_Z*pY_Z)<_CutZPT_lower)) continue;
	//
	if(_consistency_check) {
          PMCSZCand zcandC(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);
          double UPara1 = zcandC.UPara1();
          double UPara2 = zcandC.UPara2();
          double ZElecEta1 = zcandC.GetElec1().eta();
          double ZElecEta2 = zcandC.GetElec2().eta();
          double ZElecDetEta1 = zcandC.GetElec1().deteta();
          double ZElecDetEta2 = zcandC.GetElec2().deteta();
          double ZElecPhiMod1 = fmod(16.*(zcandC.GetElec1()).detphi()/TMath::Pi(), 1.0);
          double ZElecPhiMod2 = fmod(16.*(zcandC.GetElec2()).detphi()/TMath::Pi(), 1.0);
	  double ZElectrkPhiMod1 = fmod(16.*(zcandC.GetElec1()).trkphiem3()/TMath::Pi(), 1.0);
	  double ZElectrkPhiMod2 = fmod(16.*(zcandC.GetElec2()).trkphiem3()/TMath::Pi(), 1.0);
          double ZElecPt1 = zcandC.GetElec1().ppt();
          double ZElecPt2 = zcandC.GetElec2().ppt();
          bool passCut_under_study_Elec1 =  wz_utils::passCutElectron(_cut_under_study, _invert_cut,
                                                                      ZElecEta1, _ElecEta_cut,
								      ZElecDetEta1, _ElecDetEta_lowcut, _ElecDetEta_highcut,
                                                                      ZElectrkPhiMod1, _ElecPhiMod_cut,
                                                                      UPara1, _UPara_lowcut, _UPara_highcut,
                                                                      ZElecPt1, _ElecPt_lowcut, _ElecPt_highcut,
								      zcand.GetElec1().phi(), _ElecPhi_lowcut, _ElecPhi_highcut);
          bool passCut_under_study_Elec2 =  wz_utils::passCutElectron(_cut_under_study, _invert_cut,
                                                                      ZElecEta2, _ElecEta_cut,
								      ZElecDetEta2, _ElecDetEta_lowcut, _ElecDetEta_highcut,
                                                                      ZElectrkPhiMod2, _ElecPhiMod_cut,
                                                                      UPara2, _UPara_lowcut, _UPara_highcut,
                                                                      ZElecPt2, _ElecPt_lowcut, _ElecPt_highcut,
								      zcand.GetElec2().phi(), _ElecPhi_lowcut, _ElecPhi_highcut);
          if(!(passCut_under_study_Elec1 || passCut_under_study_Elec2)) continue;
        }

	// cosine of the open angle between the two electrons
	// cos(alpha) = V dot W / (|V| * |W|)
	double cos_alpha_EM_EM = (pXrescaled[0]*pXrescaled[1] + pYrescaled[0]*pYrescaled[1] + pZrescaled[0]*pZrescaled[1])/(Erescaled[0]*Erescaled[1]);
	
	// f is calculated as f = 2 *(E1+E2) * sin(alpha/2)/Mass = 2*(E1+E2)*(1-cos(alpha))/2./Mass=(E1+E2)*(1-cos(alpha))/Mass
	double f = energy_Z * (1-cos_alpha_EM_EM)/mass;
	
	if(_StudyCCScale) {
	  if(ztype==0) { // for CC region
	    _histos.Fill1D(string("smeared_hZcandMass_Scale_CCCC_")+sn, mass, evtweight);
	    _histos.Fill2D(string("smeared_hZcandMass_V_fZ_CCCC_")+sn, f, mass, evtweight);
	    _histos.FillProfile(string("smeared_hZcandMass_V_fZ_CCCC_pro_")+sn, f, mass, evtweight);
	  } // CCCC region
	} else {
	  if(ztype==2) { // for EC region  
	    _histos.Fill1D(string("smeared_hZcandMass_Scale_ECEC_")+sn, mass, evtweight);
	    _histos.Fill2D(string("smeared_hZcandMass_V_fZ_ECEC_")+sn, f, mass, evtweight);
	    _histos.FillProfile(string("smeared_hZcandMass_V_fZ_ECEC_pro_")+sn, f, mass, evtweight);
	  } // ECEC region
	}

      }//ioffset
    }//iscale      

  }//at least two electrons
  
}

// determine electron energy resolution
void ZAnalysis::energyResolutionStudy(vector<PMCSEMObj> &emobjs_gen, PMCSVtx &vtx_gen, vector<PMCSEMObj> &emobjs_smear, PMCSMet &met_smear, TRandom3 *dummy, double evtweight) {

  // get raw energy resolution smearing parameters first
  double sampling_cc_raw = _emsmear->Sampling_CC();
  double constant_cc_raw = _emsmear->Constant_CC();
  double noise_cc_raw = _emsmear->Noise_CC();
  double sampling_ec_raw = _emsmear->Sampling_EC();
  double constant_ec_raw = _emsmear->Constant_EC();
  double noise_ec_raw = _emsmear->Noise_EC();

  // get energies below electron window simulation from the smeared electron objects
  double rawpTUnderElecWindow_old[2];
  for(int ielec=0; ielec<2; ielec++) rawpTUnderElecWindow_old[ielec] = emobjs_smear[ielec].RawpTUnderElecWindow();
  
  // energy difference between single energy electron with and without ZB overlay
  double energyDiffElecWithWithoutZBOverlay[2];
  for(int ielec=0; ielec<2; ielec++) energyDiffElecWithWithoutZBOverlay[ielec] = emobjs_smear[ielec].getEnergyDiffElecWithWithoutZBOverlay();

  //
  // generator-level objects
  // here is the strategy we use to determine electron energy resolution
  // first check whether GENERATOR-LEVEL electrons passes all efficiencies cuts
  // then smear these two electrons by changing electron energy resolution parameters (fix all other parameters)
  // still use default noise term since its effect is negligible
  // we choose this way because it is slow to check efficiencies for each smeared electrons
  // 

  double sampling_new=0., constant_new=0.;

  if(emobjs_gen.size()>=2) {
    bool passesEffs = passesAllNonUParaEffs(emobjs_gen[0], emobjs_gen[1], vtx_gen, dummy,dummy->Uniform(0.,.1) );
    
    int ihist=0;
    char sn[100];
    
    // passes all selection efficiencies and have pt > 18 GeV
    // this should not affect energy scale and offset determination
    if(passesEffs && emobjs_gen[0].ppt()>18. && emobjs_gen[0].ppt()>18.) {

      // get two electrons generator level information
      double energy_gen[2], eta_gen[2], phi_gen[2], theta_gen[2], deteta_gen[2], detphi_gen[2];
      for(int ielec=0; ielec<2; ielec++) {
	energy_gen[ielec] = emobjs_gen[ielec].pE();
	eta_gen[ielec] = emobjs_gen[ielec].peta();
	theta_gen[ielec] = 2.*atan(exp(-eta_gen[ielec]));
	phi_gen[ielec] = emobjs_gen[ielec].pphi();
	deteta_gen[ielec] = emobjs_gen[ielec].deteta();
	detphi_gen[ielec] = emobjs_gen[ielec].detphi();
      }
      
      // create sampling term and constant term grids
      int nSampMax;
      if (_SkipSampling) nSampMax=0;
      else nSampMax=_Bins_ResolutionStudy;
      //
      for(int isampling=0; isampling<=nSampMax; isampling++) {
	for(int iconstant=0; iconstant<=_Bins_ResolutionStudy; iconstant++) {
	  if (_SkipSampling) sampling_new = _sampling_center;
	  else sampling_new = _sampling_center + (isampling-_Bins_ResolutionStudy/2)*_sampling_step;
	  constant_new = _constant_center + (iconstant-_Bins_ResolutionStudy/2)*_constant_step;
	  
	  if(_StudyCCResolution) _emsmear->SetCCResolutionSmearParameters(sampling_new, constant_new, noise_cc_raw);
	  else _emsmear->SetECResolutionSmearParameters(sampling_new, constant_new, noise_ec_raw);
	  
	  // smear two electrons
	  double energy_smear[2], energy_smear_beforeUECorr[2], pT_smear[2], pX_smear[2], pY_smear[2], pZ_smear[2], EMCorrFactor[2], rawpTUnderElecWindow[2];
	  double eta_smear[2], phi_smear[2], deteta_smear[2], detphi_smear[2], theta_smear[2];
	  
	  for(int ielec=0; ielec<2; ielec++) {
	    bool dum;
	    _emsmear->Smear(energy_gen[ielec], eta_gen[ielec], phi_gen[ielec], 
			    deteta_gen[ielec], detphi_gen[ielec], dummy,
                            eta_smear[ielec], phi_smear[ielec], deteta_smear[ielec], 
			    detphi_smear[ielec], energy_smear_beforeUECorr[ielec], dum, 11., vtx_gen.vtxz());  
	    
	    // now add that contribution calculated before
            _emsmear->CorrectEnergyUnderElecWindow(energy_smear_beforeUECorr[ielec], eta_smear[ielec], rawpTUnderElecWindow_old[ielec], energyDiffElecWithWithoutZBOverlay[ielec], energy_smear[ielec]);
	    
	    theta_smear[ielec] = 2.*atan(exp(-eta_smear[ielec]));
	    pT_smear[ielec] = energy_smear[ielec] * sin(theta_smear[ielec]);
	    pX_smear[ielec] = pT_smear[ielec] * cos(phi_smear[ielec]);
	    pY_smear[ielec] = pT_smear[ielec] * sin(phi_smear[ielec]);
	    pZ_smear[ielec] = energy_smear[ielec] * cos(theta_smear[ielec]);
	  }
	  
	  // smeared electrons pass pT cut
	  if( (pT_smear[0]>_CutEPT1_lo) && (pT_smear[1]>_CutEPT2_lo) && (pT_smear[0]<_CutEPT1_hi) && (pT_smear[1]<_CutEPT2_hi) ) {	    
	    sprintf(sn, "%d", ihist);	    
	    
	    double energy_Z = energy_smear[0] + energy_smear[1];
	    double pX_Z = pX_smear[0] + pX_smear[1];
	    double pY_Z = pY_smear[0] + pY_smear[1];
	    double pZ_Z = pZ_smear[0] + pZ_smear[1];
	    double pT_Z = sqrt(pX_Z * pX_Z + pY_Z * pY_Z);
	    double pX_met = met_smear.metx();
	    double pY_met = met_smear.mety();
	    double RecoilPt_Z = sqrt((pX_Z+pX_met)*(pX_Z+pX_met)+(pY_Z+pY_met)*(pY_Z+pY_met));
	    
	    // Z Ut cut, not Z pT cut
            if(RecoilPt_Z < _CutZUT && RecoilPt_Z >= _CutZUT_lower) {	
              sprintf(sn, "%d", ihist);
	      double mass = sqrt(energy_Z*energy_Z-pX_Z*pX_Z-pY_Z*pY_Z-pZ_Z*pZ_Z);
	      
	      // require electron to be in phi fiducial region
	      double phimod0 = fmod(detphi_smear[0]*16./TMath::Pi(), 1.0);
	      double phimod1 = fmod(detphi_smear[1]*16./TMath::Pi(), 1.0);
	      
	      if(_StudyCCResolution) { 
		if( (fabs(deteta_smear[0])<_CutEtaCC) && (fabs(deteta_smear[1])<_CutEtaCC) && 
		    phimod0>0.1 && phimod0<0.9 && phimod1>0.1 && phimod1<0.9)  // for CC region
		  _histos.Fill1D(string("smeared_hZcandMass_Resolution_CCCC_")+sn, mass, evtweight);
	      } else {
		if( (fabs(deteta_smear[0])<_CutEtaEC2 && fabs(deteta_smear[0])>_CutEtaEC1) &&
		    (fabs(deteta_smear[1])<_CutEtaEC2 && fabs(deteta_smear[1])>_CutEtaEC1) ) 
		  _histos.Fill1D(string("smeared_hZcandMass_Resolution_ECEC_")+sn, mass, evtweight);
	      }
	    } // Z boson Ut cut 
	  } //pass electron pT cut
	  
	  ihist++;  // for all grid points

	}//iconstant
      }//isampling      
    } // passes all selection efficiencies
  }//at least two electrons

  // set back the raw smearing parameters
  // I do not want to mess up the rest code
  if(_StudyCCResolution)
    _emsmear->SetCCResolutionSmearParameters(sampling_cc_raw, constant_cc_raw, noise_cc_raw);
  else 
    _emsmear->SetECResolutionSmearParameters(sampling_ec_raw, constant_ec_raw, noise_ec_raw);
}

void ZAnalysis::energyResolutionStudyJan(vector<PMCSEMObj> &emobjs_gen, PMCSVtx &vtx_gen, vector<PMCSEMObj> &emobjs_smear, PMCSMet &met_smear, PMCSRecoil &recoil_smear, TRandom3 *dummy, double *external_upara_rnd1, double *external_upara_rnd2, double *external_SET_rnd,  double evtweight, double * externalRndmo) {

  // There are some cuts that could have been applied before the template loop, but that have not been applied yet.
  // We do them here.
  //
  // track pT
  if(_NZTrkMatch == 2) {
    if (!((emobjs_smear[0].trkpT()>_trkpTCut)&&(emobjs_smear[1].trkpT()>_trkpTCut))) return;
  } else if(_NZTrkMatch == 1) {
    if (!((emobjs_smear[0].trkpT()>_trkpTCut)||(emobjs_smear[1].trkpT()>_trkpTCut))) return;
  }
  // Z type
  PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1]);
  int ztype=zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);
  if (_StudyCCResolution) {
    if (ztype!=0) return;
  } else {
    if (ztype!=2) return;
    // Note: what we are doing here is saying that we want to use only EC-EC pairs for E-resolution
    //       studies in the EC. This is very stupid, and we only do it for consistency with
    //       the normal ZAnalysis::energyResolutionStudy.
  }
  // also, the trigger version has not (necessarily) been flipped yet; do it now
  double Trigger_Version = dummy->Uniform(0., 1.);
  // the EM efficiency simulation  (passesAllNonUParaEffs)
  if (!_EnergyResolutionStudyJanPedantic) {
    // strictly speaking, we should evaluate these efficiencies for each re-scaled reco energy
    if (!passesAllNonUParaEffs(emobjs_smear[0], emobjs_smear[1], vtx_gen, dummy, Trigger_Version, externalRndmo))      return;
    
  }
 

  if (!_SkipeNoise || !_hZBLibBin0_etabinz){
    _hZBLibBin0_etabinz =  (TH1D**)(_emsmear->getZBLibBin0Pointer());
  }
  
  if (!_SkipeNoise && !_SkipSampling){
    std::cerr<< " Cannot make 3-D templates in Sampling, enoise, and constant please change either skipeNoise, or skipSampling to false"  << std::endl;  
    abort();
  }
  
  // recoil cuts
  int cuts=0;
  if (!(passesRecoilCuts(emobjs_smear,
			 recoil_smear,
			 met_smear,
			 dummy,
			 &cuts,
			 NULL,
			 false,
			 external_upara_rnd1, 
			 external_upara_rnd2,
			 external_SET_rnd))){
    return;
  }
  // get raw energy resolution smearing parameters first
  double sampling_raw;
  double constant_raw;
  double noise_raw;
  double scale_raw;
  double offset_raw;
  double nonlin_raw;
  double avept_raw;
  double enoise_raw;
  struct EMSmear::JSmearPars JSmear_raw;
  if (_StudyCCResolution) {
    sampling_raw = _emsmear->Sampling_CC();
    constant_raw = _emsmear->Constant_CC();
    noise_raw = _emsmear->Noise_CC();
    scale_raw = _emsmear->Scale_CC();
    offset_raw = _emsmear->Offset_CC();
    nonlin_raw = _emsmear->Energy_Nonlinearity_CC();
    avept_raw = _emsmear->ZElec_AvePt_CC();
    JSmear_raw = _emsmear->JSmearing_CC();
    enoise_raw = _emsmear->electronicNoiseFactor();
  } else {
    sampling_raw = _emsmear->Sampling_EC();
    constant_raw = _emsmear->Constant_EC();
    noise_raw = _emsmear->Noise_EC();
    scale_raw = _emsmear->Scale_EC();
    offset_raw = _emsmear->Offset_EC();
    nonlin_raw = _emsmear->Energy_Nonlinearity_EC();
    avept_raw = _emsmear->ZElec_AvePt_EC();
    JSmear_raw = _emsmear->JSmearing_EC();
  }

  double sampling_new=0., constant_new=0., eNoise_new=0.;

  if(emobjs_smear.size()>=2) {
    int ihist=0;
    char sn[100];

    // Re-establish correspondence between true and smeared electrons
    PMCSEMObj* CorrespondingTrue[2]={0,0};
    for(int oelec=0; oelec<emobjs_gen.size(); oelec++) {
      if (emobjs_gen[oelec].getIndex() == emobjs_smear[0].getIndex()){
        CorrespondingTrue[0]=&(emobjs_gen[oelec]);
      }
      if (emobjs_gen[oelec].getIndex() == emobjs_smear[1].getIndex()){
        CorrespondingTrue[1]=&(emobjs_gen[oelec]);
      }
    }
    assert(CorrespondingTrue[0]&&CorrespondingTrue[1]);

    // pre-chew random numbers, if needed
    double externalRndm[18];
    if (_EnergyResolutionStudyJanPedantic) {
      if (externalRndmo){
	for (int i=0; i<18; i++) externalRndm[i]=externalRndmo[i];
      }
      else{
	for (int i=0; i<18; i++) externalRndm[i]=dummy->Uniform(0., 1.);
      }
    }

    // get energies below electron window simulation from the original smeared electron objects
    double rawpTUnderElecWindow_old[2];
    for(int ielec=0; ielec<2; ielec++) rawpTUnderElecWindow_old[ielec] = emobjs_smear[ielec].RawpTUnderElecWindow();
    // energy difference between single energy electron with and without ZB overlay from the original smeared electron objects
    double energyDiffElecWithWithoutZBOverlay_old[2];
    for(int ielec=0; ielec<2; ielec++) energyDiffElecWithWithoutZBOverlay_old[ielec] = emobjs_smear[ielec].getEnergyDiffElecWithWithoutZBOverlay();
    double externalRndm2[2][4];
    for (int ielec = 0; ielec<2; ielec++){
      for (int i=2; i<4; i++) externalRndm2[ielec][i]=dummy->Rndm();
      for (int i=0; i<2; i++) externalRndm2[ielec][i]=dummy->Gaus(0., 1.);
      
    }
    //
    // create sampling term and constant term grids
    //
    int nSampMax;
    if (_SkipSampling) nSampMax=0;
    else nSampMax=_Bins_ResolutionStudy;
    
    int neNoiseMax;
    if (_SkipeNoise) neNoiseMax=0;
    else neNoiseMax=_Bins_ResolutionStudy;
    
    int nConstMax;
    if (_SkipConstant) nConstMax=0;
    else nConstMax=_Bins_ResolutionStudy;


    //
    for(int ieNoise=0; ieNoise<=neNoiseMax; ieNoise++) {
    for(int isampling=0; isampling<=nSampMax; isampling++) {
      for(int iconstant=0; iconstant<=nConstMax; iconstant++) {
	if (_SkipSampling) sampling_new = sampling_raw;
	else sampling_new = _sampling_center + (isampling-_Bins_ResolutionStudy/2)*_sampling_step;
	if (_SkipeNoise) eNoise_new = enoise_raw;
	else eNoise_new = _enoise_center + (ieNoise -_Bins_ResolutionStudy/2)*_enoise_step;
	if (_SkipConstant) constant_new = constant_raw;
	else constant_new = _constant_center + (iconstant-_Bins_ResolutionStudy/2)*_constant_step;
	

        sprintf(sn, "%d", ihist);

        ihist++;  // for all grid points (that is, needs to go before any continue statement)

        // re-smear two electrons
        double Eresmeared[2];
        double pXresmeared[2];
        double pYresmeared[2];
        double pZresmeared[2];
        double pTresmeared[2];
        for(int ielec=0; ielec<2; ielec++) {
	  double detphi_gen=CorrespondingTrue[ielec]->detphi();
	  double deteta_gen=CorrespondingTrue[ielec]->deteta();
	  double phimod_gen=fmod(detphi_gen*16/TMath::Pi(),1.0);
	  bool needCBtailAndPeakShift=(fabs(deteta_gen)<1.3);
	  if ((!_SkipSampling) || (!_SkipConstant)){
	    _emsmear->SmearEnergy(CorrespondingTrue[ielec]->pE(), CorrespondingTrue[ielec]->peta(), CorrespondingTrue[ielec]->pphi(), phimod_gen, deteta_gen,
				  scale_raw, offset_raw, nonlin_raw, avept_raw,
				  sampling_new, constant_new, noise_raw,
				  JSmear_raw.sampling1, JSmear_raw.sampling2, JSmear_raw.sampling_exp0, JSmear_raw.sampling_exp1, JSmear_raw.sampling_exp2,
				  needCBtailAndPeakShift,
				  dummy, Eresmeared[ielec],externalRndm2[ielec]);
	  }
	  else{
	    Eresmeared[ielec] = emobjs_smear[ielec].pE()-energyDiffElecWithWithoutZBOverlay_old[ielec];
	  }
	  
	  // add back the original "under the electron cone" energy
	  double new_energyDiffElecWithWithoutZBOverlay =0.;
	  new_energyDiffElecWithWithoutZBOverlay = energyDiffElecWithWithoutZBOverlay_old[ielec]; 
	  
	  if (!_SkipeNoise){
	    if (eNoise_new < 0.)
	      eNoise_new =0.;
	    if(fabs(emobjs_smear[ielec].UParaCorr()) <=0.01) {
	      int etabin = (int)((emobjs_smear[ielec].deteta()+1.1)/0.2);
	      if(etabin < 0) etabin = 0 ;  
	      if(etabin > 10)  etabin = 10; 
	      new_energyDiffElecWithWithoutZBOverlay = (energyDiffElecWithWithoutZBOverlay_old[ielec] - _hZBLibBin0_etabinz[etabin]->GetMean()) /enoise_raw * eNoise_new  + _hZBLibBin0_etabinz[etabin]->GetMean();
//	      std::cout << Eresmeared[ielec] +  new_energyDiffElecWithWithoutZBOverlay << "     "  << emobjs_smear[ielec].pE() <<  "    " << _hZBLibBin0_etabinz[etabin]->GetMean()  << std::endl;
	    }
	  }
	
	  _emsmear->CorrectEnergyUnderElecWindow(Eresmeared[ielec], emobjs_smear[ielec].peta(), rawpTUnderElecWindow_old[ielec], new_energyDiffElecWithWithoutZBOverlay, Eresmeared[ielec]);
	  
	 

	  //         
	  pXresmeared[ielec]=emobjs_smear[ielec].ppx()*(Eresmeared[ielec]/emobjs_smear[ielec].pE());
          pYresmeared[ielec]=emobjs_smear[ielec].ppy()*(Eresmeared[ielec]/emobjs_smear[ielec].pE());
          pZresmeared[ielec]=emobjs_smear[ielec].ppz()*(Eresmeared[ielec]/emobjs_smear[ielec].pE());
          pTresmeared[ielec]=sqrt(pXresmeared[ielec]*pXresmeared[ielec]+pYresmeared[ielec]*pYresmeared[ielec]);
	  // std::cout << enoise_raw<< "   " << eNoise_new << "       "   <<   (enoise_raw==eNoise_new) << std::endl;
	  if ((constant_new==constant_raw) && (enoise_raw==eNoise_new)){
	    if (!(Eresmeared[ielec]==emobjs_smear[ielec].pE())){
	      std::cout << "template_path : " << Eresmeared[ielec] <<  "  " << pXresmeared[ielec] <<  "  " << pYresmeared[ielec] <<  "  " << pZresmeared[ielec] << std::endl;
	      std::cout << "regular_path : " << emobjs_smear[ielec].pE() <<  "  " << emobjs_smear[ielec].ppx() <<  "   " <<emobjs_smear[ielec].ppy()  <<  "  " <<emobjs_smear[ielec].ppz()  << std::endl;
	    }
	  }
	} 
	//	abort();
// strictly speaking, this is the right place to evaluate EM efficiencies
        if (_EnergyScaleStudyJanPedantic) {
          // the copied EM objects need correct: pT, det_eta, eta
          PMCSEMObj emobj1resm= emobjs_smear[0];
          emobj1resm.SetEnergyEtaPhi(Eresmeared[0],emobjs_smear[0].peta(),emobjs_smear[0].pphi());
	  // emobj1resm.SetDetEtaDetPhi(emobjs_smear[0].deteta(), emobjs_smear[0].detphi());
          PMCSEMObj emobj2resm=emobjs_smear[1];
          emobj2resm.SetEnergyEtaPhi(Eresmeared[1],emobjs_smear[1].peta(),emobjs_smear[1].pphi());
	  // emobj2resm.SetDetEtaDetPhi(emobjs_smear[1].deteta(), emobjs_smear[1].detphi());
	  if(!passesAllNonUParaEffs(emobj1resm,emobj2resm,vtx_gen,dummy,Trigger_Version,externalRndm)){ 
	    continue;
	  }
        }
	
	  
	// re-calculate Z properties
        double energy_Z = Eresmeared[0] + Eresmeared[1];
        double pX_Z = pXresmeared[0] + pXresmeared[1];
        double pY_Z = pYresmeared[0] + pYresmeared[1];
        double pZ_Z = pZresmeared[0] + pZresmeared[1];
        double mass = sqrt(energy_Z*energy_Z-pX_Z*pX_Z-pY_Z*pY_Z-pZ_Z*pZ_Z);

        // Cuts
        //
        // pT(e)
        if ((pTresmeared[0]<_CutEPT1_lo)||(pTresmeared[0]>_CutEPT1_hi)) continue;
        if ((pTresmeared[1]<_CutEPT2_lo)||(pTresmeared[1]>_CutEPT2_hi)) continue;
        // Z mass
        if ((mass<_ZMassCut1)||(mass>_ZMassCut2)||(sqrt(pX_Z*pX_Z+pY_Z*pY_Z)>_CutZPT)|| (sqrt(pX_Z*pX_Z+pY_Z*pY_Z)<_CutZPT_lower)) continue;

	if(_StudyCCResolution) { 
	  if(ztype==0) { // for CC region
	    //std::cout << "Filling Template " << mass << std::endl;
	    _histos.Fill1D(string("smeared_hZcandMass_Resolution_CCCC_")+sn, mass, evtweight);

	  } // CCCC region
	} else {
	  if(ztype==2) { // for EC region
	    _histos.Fill1D(string("smeared_hZcandMass_Resolution_ECEC_")+sn, mass, evtweight);
	  } // ECEC region
	}

      }//iconstant
    }//isampling
    }//ieNoise
  }//at least two electrons
  
}


void ZAnalysis::MakeCrystalBallParameterTemplates(vector<PMCSEMObj> &emobjs_gen, PMCSVtx &vtx_gen, vector<PMCSEMObj> &emobjs_smear, PMCSMet &met_smear, PMCSRecoil &recoil_smear, TRandom3 *dummy, double evtweight, double * externalRndmo) {

  // There are some cuts that could have been applied before the template loop, but that have not been applied yet.
  // We do them here.
  //
  // track pT
  if(_NZTrkMatch == 2) {
    if (!((emobjs_smear[0].trkpT()>_trkpTCut)&&(emobjs_smear[1].trkpT()>_trkpTCut))) return;
  } else if(_NZTrkMatch == 1) {
    if (!((emobjs_smear[0].trkpT()>_trkpTCut)||(emobjs_smear[1].trkpT()>_trkpTCut))) return;
  }
  // Z type
  PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1]);
  int ztype=zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);
 
  // only CCCC events
  if (ztype!=0) return;

  // also, the trigger version has not (necessarily) been flipped yet; do it now
  double Trigger_Version = dummy->Uniform(0., 1.);

  // recoil cuts
  if (!passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy)) return;

  // get raw energy resolution smearing parameters first
  double sampling_raw;
  double constant_raw;
  double noise_raw;
  double scale_raw;
  double offset_raw;
  double nonlin_raw;
  double avept_raw;







  struct EMSmear::JSmearPars  JSmear_raw;


  struct EMSmear::CrackCBPars CrackCB_raw;
// 
//   if (_StudyCCResolution) {
	 sampling_raw = _emsmear->Sampling_CC();
	 constant_raw = _emsmear->Constant_CC();
	 noise_raw = _emsmear->Noise_CC();
	 scale_raw = _emsmear->Scale_CC();
	 offset_raw = _emsmear->Offset_CC();
	 nonlin_raw = _emsmear->Energy_Nonlinearity_CC();
	 avept_raw = _emsmear->ZElec_AvePt_CC();

     JSmear_raw = _emsmear->JSmearing_CC();
     CrackCB_raw = _emsmear->CrackCB_CC();
//   } else {
//     sampling_raw = _emsmear->Sampling_EC();
//     constant_raw = _emsmear->Constant_EC();
//     noise_raw = _emsmear->Noise_EC();
//     scale_raw = _emsmear->Scale_EC();
//     offset_raw = _emsmear->Offset_EC();
//     nonlin_raw = _emsmear->Energy_Nonlinearity_EC();
//     avept_raw = _emsmear->ZElec_AvePt_EC();
//     JSmear_raw = _emsmear->JSmearing_EC();
//   }
//  

  if(emobjs_smear.size()>=2) {
    int ihist=0;
    char sn[100];

    // Re-establish correspondence between true and smeared electrons
    PMCSEMObj* CorrespondingTrue[2]={0,0};
    for(int oelec=0; oelec<emobjs_gen.size(); oelec++) {
      if (emobjs_gen[oelec].getIndex() == emobjs_smear[0].getIndex()){
        CorrespondingTrue[0]=&(emobjs_gen[oelec]);
      }
      if (emobjs_gen[oelec].getIndex() == emobjs_smear[1].getIndex()){
        CorrespondingTrue[1]=&(emobjs_gen[oelec]);
      }
    }
    assert(CorrespondingTrue[0]&&CorrespondingTrue[1]);

    // pre-chew random numbers, if needed
    double externalRndm[18];
    if (externalRndmo){
      for (int i=0; i<18; i++) externalRndm[i]=externalRndmo[i];
    }
    else{
      for (int i=0; i<18; i++) externalRndm[i]=dummy->Uniform(0., 1.);
    }
    double externalRndm2[8];
    for (int i=0; i<8; i++) externalRndm2[i]=dummy->Rndm();
    for (int i=0; i<2; i++) {externalRndm2[4+i]=dummy->Gaus(0., 1.) ;  externalRndm2[i]=dummy->Gaus(0., 1.);}
    // get energies below electron window simulation from the original smeared electron objects
    double rawpTUnderElecWindow_old[2];
    for(int ielec=0; ielec<2; ielec++) rawpTUnderElecWindow_old[ielec] = emobjs_smear[ielec].RawpTUnderElecWindow();
    // energy difference between single energy electron with and without ZB overlay from the original smeared electron objects
    double energyDiffElecWithWithoutZBOverlay_old[2];
    for(int ielec=0; ielec<2; ielec++) energyDiffElecWithWithoutZBOverlay_old[ielec] = emobjs_smear[ielec].getEnergyDiffElecWithWithoutZBOverlay();

    


    //
    // create sampling term and constant term grids
    //
//     int nSampMax;
//     if (_SkipSampling) nSampMax=0;
//     else nSampMax=_Bins_ResolutionStudy;
//     //
//     for(int isampling=0; isampling<=nSampMax; isampling++) {
//       for(int iconstant=0; iconstant<=_Bins_ResolutionStudy; iconstant++) {

    double new_CrackCB_alphaOffset=0., new_CrackCB_alphaSlope=0.;


    for(int i_alphaOffset=0; i_alphaOffset<=_Bins_MakeCrackCBtemplates; i_alphaOffset++) {
      for(int i_alphaSlope=0; i_alphaSlope<=_Bins_MakeCrackCBtemplates; i_alphaSlope++) {

          new_CrackCB_alphaOffset = _CrackCB_alphaOffset_center + (i_alphaOffset-_Bins_MakeCrackCBtemplates/2)*_CrackCB_alphaOffset_step;
	      new_CrackCB_alphaSlope  = _CrackCB_alphaSlope_center  + (i_alphaSlope -_Bins_MakeCrackCBtemplates/2)*_CrackCB_alphaSlope_step;


          //// AM printout
          //double alpha=new_CrackCB_alphaOffset-new_CrackCB_alphaSlope*0.2;
          //cout<<"CB ofset  slope  alpha : "<<new_CrackCB_alphaOffset<<"  "<<new_CrackCB_alphaSlope<<"  "<<alpha<<endl;       
          _emsmear->SetCrystalBallParameters(CrackCB_raw.CrackCB_crlimit, CrackCB_raw.CrackCB_n, new_CrackCB_alphaOffset, new_CrackCB_alphaSlope, CrackCB_raw.CrackCB_PeakShiftOffset, CrackCB_raw.CrackCB_PeakShiftSlope);

          sprintf(sn, "%d", ihist);

          ihist++;  // for all grid points (that is, needs to go before any continue statement)

          // re-smear two electrons
          double Eresmeared[2];
          double pXresmeared[2];
          double pYresmeared[2];
          double pZresmeared[2];
          double pTresmeared[2];
          for(int ielec=0; ielec<2; ielec++) {
	         double detphi_gen=CorrespondingTrue[ielec]->detphi();
	         double deteta_gen=CorrespondingTrue[ielec]->deteta();
	         double phimod_gen=fmod(detphi_gen*16/TMath::Pi(),1.0);
	         bool needCBtail=(fabs(deteta_gen)<1.3);

		 _emsmear->SmearEnergy(CorrespondingTrue[ielec]->pE(), CorrespondingTrue[ielec]->peta(), CorrespondingTrue[ielec]->pphi(), phimod_gen, deteta_gen,
				scale_raw, offset_raw, nonlin_raw, avept_raw,
				sampling_raw, constant_raw, noise_raw,
				JSmear_raw.sampling1, JSmear_raw.sampling2, JSmear_raw.sampling_exp0, JSmear_raw.sampling_exp1, JSmear_raw.sampling_exp2,
				needCBtail,
				dummy, Eresmeared[ielec], &(externalRndm2[ielec*4]));

	         // add back the original "under the electron cone" energy
	         _emsmear->CorrectEnergyUnderElecWindow(Eresmeared[ielec], emobjs_smear[ielec].peta(), rawpTUnderElecWindow_old[ielec], energyDiffElecWithWithoutZBOverlay_old[ielec], Eresmeared[ielec]);
             //
             pXresmeared[ielec]=emobjs_smear[ielec].ppx()*(Eresmeared[ielec]/emobjs_smear[ielec].pE());
             pYresmeared[ielec]=emobjs_smear[ielec].ppy()*(Eresmeared[ielec]/emobjs_smear[ielec].pE());
             pZresmeared[ielec]=emobjs_smear[ielec].ppz()*(Eresmeared[ielec]/emobjs_smear[ielec].pE());
             pTresmeared[ielec]=sqrt(pXresmeared[ielec]*pXresmeared[ielec]+pYresmeared[ielec]*pYresmeared[ielec]);
        }

        // strictly speaking, this is the right place to evaluate EM efficiencies
        // the copied EM objects need correct: pT, det_eta, eta
        PMCSEMObj emobj1resm=emobjs_smear[0];
        emobj1resm.SetEnergyEtaPhi(Eresmeared[0],emobjs_smear[0].peta(),emobjs_smear[0].pphi());
        PMCSEMObj emobj2resm=emobjs_smear[1];
        emobj2resm.SetEnergyEtaPhi(Eresmeared[1],emobjs_smear[1].peta(),emobjs_smear[1].pphi());
        if (!passesAllNonUParaEffs(emobj1resm,emobj2resm,vtx_gen,dummy,Trigger_Version,externalRndm)) continue;



        // re-calculate Z properties
        double energy_Z = Eresmeared[0] + Eresmeared[1];
        double pX_Z = pXresmeared[0] + pXresmeared[1];
        double pY_Z = pYresmeared[0] + pYresmeared[1];
        double pZ_Z = pZresmeared[0] + pZresmeared[1];
        double mass = sqrt(energy_Z*energy_Z-pX_Z*pX_Z-pY_Z*pY_Z-pZ_Z*pZ_Z);

        // Cuts
        //
        // pT(e)
        if ((pTresmeared[0]<_CutEPT1_lo)||(pTresmeared[0]>_CutEPT1_hi)) continue;
        if ((pTresmeared[1]<_CutEPT2_lo)||(pTresmeared[1]>_CutEPT2_hi)) continue;
        // Z mass
        if ((mass<_ZMassCut1)||(mass>_ZMassCut2)||(sqrt(pX_Z*pX_Z+pY_Z*pY_Z)>_CutZPT) || (sqrt(pX_Z*pX_Z+pY_Z*pY_Z)<_CutZPT_lower)) continue;

        int z_elec_phimod_category = zcand.PhiModCategory();
        char z_elec_phimod_category_char[10];// this is trkEM3phimod as of 080909
        sprintf(z_elec_phimod_category_char, "%d", z_elec_phimod_category);
        if(z_elec_phimod_category>-1) {
            _histos.Fill1D((string("smeared_hZcandMass_CrackCBTemplates_Category_PhiMod_")+z_elec_phimod_category_char).c_str()+string("_")+sn, mass, evtweight);
        } // for phimod category 

      }//i_alphaSlope
    }//i_alphaOffset

  }//at least two electrons
  
}



// determine hadronic momentum scale
void ZAnalysis::HadronicMomentumScaleStudy(vector<PMCSEMObj> &emobjs_smear, 
					   PMCSRecoil &recoil_gen, 
					   PMCSVtx &vtx_gen,
					   TRandom3 *dummy, 
					   std::string prefix, 
					   double evtweight,
					   double *external_upara_rnd1,
					   double *external_upara_rnd2,
					   double *external_SET_rnd) {
  // skip if there are less than 2 smeared EM objects in an event
  if( emobjs_smear.size()<2 ) return;
  
  // get two electron uparaCorr, energyLeakage, 
  // eta and phi to calculate uparallel corrections
  double ElecUParaCorr[2], ElecEnergyLeakage[2], ElecEta[2], ElecDetEta[2], 
         ElecPhi[2], ElecDetPhi[2], ElecPx[2], ElecPy[2];
  for(int i=0; i<2; i++) {
    ElecUParaCorr[i] = emobjs_smear[i].UParaCorr();
    ElecEnergyLeakage[i] = emobjs_smear[i].EnergyLeakage();
    ElecEta[i] = emobjs_smear[i].peta();
    ElecDetEta[i] = emobjs_smear[i].deteta();
    ElecPhi[i] = emobjs_smear[i].pphi();
    ElecDetPhi[i] = emobjs_smear[i].detphi();
    ElecPx[i] = emobjs_smear[i].ppx();
    ElecPy[i] = emobjs_smear[i].ppy();
  }

  // Z boson vector
  TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
  TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
  TVector2 z_vect = elec1_vect + elec2_vect;
  
  // divide events into smeared Z pT bins
  int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());
  if(bin<0) return; // out of range
  char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);

  // Z boson bisector of the two electrons
  TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();

  double raw_scale_HAD_A = _recoilsmear->scale_HAD_A();
  double raw_scale_HAD_B = _recoilsmear->scale_HAD_B();
  double raw_scale_HAD_C = _recoilsmear->scale_HAD_C();
  double raw_phi_smear_true_recoil_A = _recoilsmear->phi_smear_true_recoil_A();
  double raw_phi_smear_true_recoil_B = _recoilsmear->phi_smear_true_recoil_B();
  double raw_constant_HAD = _recoilsmear->constant_HAD();
  double raw_sampling_HAD = _recoilsmear->sampling_HAD();

  // recoil pT, phi at generator level
  double raw_recoil_pT = recoil_gen.Recoil();
  double raw_recoil_phi = recoil_gen.RecoilPhi();

  // do not change soft component smearing 
  double recoilX_SoftComponent = _recoilsmear->recoilX_SoftComponent();
  double recoilY_SoftComponent = _recoilsmear->recoilY_SoftComponent();

//   ///////////////////// DEBUG //////////////////////////
//   //
//   double dummy_znunu_SET;
//   double dummy_znunu_SET_expected;
//   _recoilsmear->GetLastHardScalarEt_Method_B(&dummy_znunu_SET, &dummy_znunu_SET_expected, NULL);
//   cout << "++++ TEMPLATE BEFORE LOOP:" << endl
//        << "     Buffered hard SET(unfudged)=" << dummy_znunu_SET 
//        << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
//        << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//   //
//   ///////////////////// DEBUG //////////////////////////

  int ihist = 0;
  for(int iHAD=0; iHAD<=_Bins_HadronicScaleStudy; iHAD++) {
    for(int jHAD=0; jHAD<=_Bins_HadronicScaleStudy; jHAD++) {
      double scale_HAD_A = _scale_HAD_A_center + (iHAD-_Bins_HadronicScaleStudy/2) * _scale_HAD_A_step;
      double scale_HAD_B = _scale_HAD_B_center + (jHAD-_Bins_HadronicScaleStudy/2) * _scale_HAD_B_step;

      // smear hard component
      double smear_recoil_pT = 0., smear_recoil_phi = 0.;
      _recoilsmear->SmearHardRecoil_Method_C(raw_recoil_pT, 
					     raw_recoil_phi, 
					     scale_HAD_A, 
					     scale_HAD_B, 
					     raw_scale_HAD_C, 
					     raw_phi_smear_true_recoil_A, 
					     raw_phi_smear_true_recoil_B, 
					     raw_constant_HAD, 
					     raw_sampling_HAD, 
					     dummy, 
					     smear_recoil_pT, 
					     smear_recoil_phi);
      // add uparallel correction
      double sum_UparaCorrX = 0., sum_UparaCorrY = 0.;
      for(int ielec=0; ielec<2; ielec++) {
	sum_UparaCorrX += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* cos(ElecPhi[ielec]);
	sum_UparaCorrY += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* sin(ElecPhi[ielec]);
      }
      
      double recoilx_smear_template = smear_recoil_pT * cos(smear_recoil_phi);
      double recoily_smear_template = smear_recoil_pT * sin(smear_recoil_phi);
      // smeared recoil system with soft component added
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last){ 
	if (_TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
	  _recoilsmear->ApplyTopBottomAsym(recoilx_smear_template, recoily_smear_template);   
	}
      }
      
      double smear_recoil_X = recoilx_smear_template + recoilX_SoftComponent;
      double smear_recoil_Y = recoily_smear_template + recoilY_SoftComponent;
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
      }
      
      smear_recoil_X = smear_recoil_X - sum_UparaCorrX;
      smear_recoil_Y = smear_recoil_Y - sum_UparaCorrY;
      
      
      // include photons in the smeared recoil system
      // the photon response is described in EMSmear::SmearPhotonEnergy
      //
      for(int i=0; i<emobjs_smear.size(); i++) {
	if (i > 1){
	  if (!_ZsimuFSRcracks) {
	    smear_recoil_X  += emobjs_smear[i].ppx();
	    smear_recoil_Y += emobjs_smear[i].ppy();
	  } else {
	    float deteta=emobjs_smear[i].deteta();
	    float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	    if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
	      smear_recoil_X += emobjs_smear[i].ppx();
	      smear_recoil_Y += emobjs_smear[i].ppy();
	    }
	  }
	}
      }
      
      // recoil after all corrections
      PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
	recoil_smear.SetRecoil(smear_recoil_X, smear_recoil_Y);
      }
      
      

      // met after corrections for the two highest pT electrons
      double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
      double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
      PMCSMet met_smear(metX_component, metY_component);
      
      // skip randomization of U|| efficiency and SET
      if( passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
			   NULL, NULL, false, 
			   external_upara_rnd1, external_upara_rnd2,
			   external_SET_rnd) ) {
	// now we can calculate eta imbalance
	TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);
	double eta_imbalance = (z_vect + recoil_vect) * bisector_vect;	
	char sn[20]; sprintf(sn, "%d", ihist);	
	_histos.Fill1D((prefix+"hZcandEtaImBalance_bin_"+pee_bin_sn+"_"+sn).c_str(), 
		       eta_imbalance, evtweight);
      }	
//       ///////////////////// DEBUG //////////////////////////
//       //
//       double dummyset;
//       _recoilsmear->GetLastHardScalarEt_Method_B(&dummyset, NULL, NULL);
//       cout << "++++ TEMPLATE INSIDE LOOP (iHAD=" << iHAD
// 	   << ", jHAD=" << jHAD << "):" << endl 
// 	   << "     Buffered hard SET (unfudged)=" << dummyset
// 	   << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
// 	   << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//       //
//       ///////////////////// DEBUG //////////////////////////

      ihist ++;
    }// iHAD
  }// jHAD
  
  // set back old smearing parameters
  _recoilsmear->SetHardSmearingParameters_MethodC(raw_scale_HAD_A, 
						  raw_scale_HAD_B, 
						  raw_scale_HAD_C, 
						  raw_phi_smear_true_recoil_A, 
						  raw_phi_smear_true_recoil_B,
						  raw_constant_HAD, 
						  raw_sampling_HAD);
}

// determine hadronic momentum resolution
void ZAnalysis::HadronicMomentumResolutionStudy(vector<PMCSEMObj> &emobjs_smear, 
						PMCSRecoil &recoil_gen, 
						PMCSVtx &vtx_gen,
						TRandom3 *dummy, 
						std::string prefix, 
						double evtweight,
						double *external_upara_rnd1,
						double *external_upara_rnd2,
						double *external_SET_rnd) {
  // skip if there are less than 2 smeared EM objects in an event
  if( emobjs_smear.size()<2 ) return;
  
  // get two electron uparaCorr, energyLeakage, eta and phi to calculate uparallel corrections
  double ElecUParaCorr[2], ElecEnergyLeakage[2], ElecEta[2], ElecDetEta[2], 
         ElecPhi[2], ElecDetPhi[2], ElecPx[2], ElecPy[2];
  for(int i=0; i<2; i++) {
    ElecUParaCorr[i] = emobjs_smear[i].UParaCorr();
    ElecEnergyLeakage[i] = emobjs_smear[i].EnergyLeakage();
    ElecEta[i] = emobjs_smear[i].peta();
    ElecDetEta[i] = emobjs_smear[i].deteta();
    ElecPhi[i] = emobjs_smear[i].pphi();
    ElecDetPhi[i] = emobjs_smear[i].detphi();
    ElecPx[i] = emobjs_smear[i].ppx();
    ElecPy[i] = emobjs_smear[i].ppy();
  }
  
  // Z boson vector
  TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
  TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
  TVector2 z_vect = elec1_vect + elec2_vect;
  
  // divide events into smeared Z pT bins
  int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());
  if(bin<0) return; // out of range
  char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);

  // Z boson bisector of the two electrons
  TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();

  double raw_scale_HAD_A = _recoilsmear->scale_HAD_A();
  double raw_scale_HAD_B = _recoilsmear->scale_HAD_B();
  double raw_scale_HAD_C = _recoilsmear->scale_HAD_C();
  double raw_phi_smear_true_recoil_A = _recoilsmear->phi_smear_true_recoil_A();
  double raw_phi_smear_true_recoil_B = _recoilsmear->phi_smear_true_recoil_B();
  double raw_constant_HAD = _recoilsmear->constant_HAD();
  double raw_sampling_HAD = _recoilsmear->sampling_HAD();
  double raw_alpha_mb = _recoilsmear->alpha_mb();
  double raw_alpha_zb = _recoilsmear->alpha_zb();
  
  // recoil pT, phi at generator level
  double raw_recoil_pT = recoil_gen.Recoil();
  double raw_recoil_phi = recoil_gen.RecoilPhi();

//   ///////////////////// DEBUG //////////////////////////
//   //
//   double dummy_znunu_SET;
//   double dummy_znunu_SET_expected;
//   _recoilsmear->GetLastHardScalarEt_Method_B(&dummy_znunu_SET, &dummy_znunu_SET_expected, NULL);
//   cout << "++++ TEMPLATE BEFORE LOOP:" << endl
//        << "     Buffered hard SET(unfudged)=" << dummy_znunu_SET 
//        << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
//        << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//   //
//   ///////////////////// DEBUG //////////////////////////

  int ihist = 0;
  for(int iSampling=0; iSampling<=_Bins_HadronicResolutionStudy; iSampling++) {
    for(int iAlpha_MB=0; iAlpha_MB<=_Bins_HadronicResolutionStudy; iAlpha_MB++) {
      double sampling_HAD = _sampling_HAD_center + (iSampling-_Bins_HadronicResolutionStudy/2) * _sampling_HAD_step;
      double alpha_mb = _alpha_mb_center + (iAlpha_MB-_Bins_HadronicResolutionStudy/2) * _alpha_mb_step;
      
      // smear hard component using new sampling term
      double smear_recoil_pT = 0., smear_recoil_phi = 0.;
      _recoilsmear->SmearHardRecoil_Method_C(raw_recoil_pT, 
					     raw_recoil_phi, 
					     raw_scale_HAD_A, 
					     raw_scale_HAD_B, 
					     raw_scale_HAD_C, 
					     raw_phi_smear_true_recoil_A, 
					     raw_phi_smear_true_recoil_B, 
					     raw_constant_HAD, 
					     sampling_HAD, 
					     dummy, 
					     smear_recoil_pT, 
					     smear_recoil_phi);
      double recoilX_HardComponent = smear_recoil_pT * cos(smear_recoil_phi);
      double recoilY_HardComponent = smear_recoil_pT * sin(smear_recoil_phi);
            
      // smear soft component using new alpha_mb
      double smear_Metx_From_MB = 0., smear_Mety_From_MB = 0., smear_Metx_From_ZB = 0., smear_Mety_From_ZB = 0.; 	
      double smear_Metx = 0., smear_Mety = 0.;      
      _recoilsmear->SmearSoftRecoil_Method_D(alpha_mb, raw_alpha_zb, dummy, 
					     smear_Metx_From_MB, smear_Mety_From_MB, 
					     smear_Metx_From_ZB, smear_Mety_From_ZB, 	
					     smear_Metx, smear_Mety);

      // add uparallel correction
      double sum_UparaCorrX = 0., sum_UparaCorrY = 0.;
      for(int ielec=0; ielec<2; ielec++) {
	sum_UparaCorrX += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* cos(ElecPhi[ielec]);
	sum_UparaCorrY += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* sin(ElecPhi[ielec]);
      }

      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last){ 
	if (_TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
	  _recoilsmear->ApplyTopBottomAsym(recoilX_HardComponent,recoilX_HardComponent );   
	}
	else if (!_TBPhi_response_Hard_Only && _TBPhi_response_Soft_Only){
	  _recoilsmear->ApplyTopBottomAsym(smear_Metx, smear_Mety);   
	}
      }
      
      // final smeared recoil system (hard component added)
      double smear_recoil_X = recoilX_HardComponent + smear_Metx;
      double smear_recoil_Y = recoilY_HardComponent + smear_Mety;
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
      }
      
      smear_recoil_X = smear_recoil_X - sum_UparaCorrX;
      smear_recoil_Y = smear_recoil_Y - sum_UparaCorrY;
      
      // include photons in the smeared recoil system
      // the photon response is described in EMSmear::SmearPhotonEnergy
      //
      for(int i=0; i<emobjs_smear.size(); i++) {
	if (i > 1){
	  if (!_ZsimuFSRcracks) {
	    smear_recoil_X  += emobjs_smear[i].ppx();
	    smear_recoil_Y += emobjs_smear[i].ppy();
	  } else {
	    float deteta=emobjs_smear[i].deteta();
	    float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	    if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
	    smear_recoil_X += emobjs_smear[i].ppx();
	    smear_recoil_Y += emobjs_smear[i].ppy();
	    }
	  }
	}
      }
      
      PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
	recoil_smear.SetRecoil(smear_recoil_X, smear_recoil_Y);
      }
      
      // met after corrections for the two highest pT electrons
      double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
      double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
      PMCSMet met_smear(metX_component, metY_component);
      
      // skip randomization of U|| efficiency and SET
      if( passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
			   NULL, NULL, false, 
			   external_upara_rnd1, external_upara_rnd2,
			   external_SET_rnd) ) {
	// now we can calculate eta imbalance
	TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);
	double eta_imbalance = (z_vect + recoil_vect) * bisector_vect;
	char sn[20]; sprintf(sn, "%d", ihist);
	_histos.Fill1D((prefix+"hZcandEtaImBalance_bin_"+pee_bin_sn+"_"+sn).c_str(), 
		       eta_imbalance, evtweight);
      }
//       ///////////////////// DEBUG //////////////////////////
//       //
//       double dummyset;
//       _recoilsmear->GetLastHardScalarEt_Method_B(&dummyset, NULL, NULL);
//       cout << "++++ TEMPLATE INSIDE LOOP (iSampling=" << iSampling
// 	   << ", iAlpha_MB=" << iAlpha_MB << "):" << endl 
// 	   << "     Buffered hard SET (unfudged)=" << dummyset
// 	   << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
// 	   << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//       //
//       ///////////////////// DEBUG //////////////////////////
      
      ihist ++;
    }// iAlpha_MB
  }// iSampling
      
  // set back old smearing parameters
  _recoilsmear->SetHardSmearingParameters_MethodC(raw_scale_HAD_A, 
						  raw_scale_HAD_B, 
						  raw_scale_HAD_C, 
						  raw_phi_smear_true_recoil_A, 
						  raw_phi_smear_true_recoil_B,
						  raw_constant_HAD, 
						  raw_sampling_HAD);
  _recoilsmear->SetSoftSmearingParameters_MethodD(raw_alpha_mb, 
						  raw_alpha_zb);
}

// RCLSA: Method to generate the recoil templates.
void ZAnalysis::ZHadronicRecoilBifurcateStudy(vector<PMCSEMObj> &emobjs_orig, 
					      PMCSRecoil &recoil_gen, 
					      PMCSVtx &vtx_gen,
					      TRandom3 *dummy, 
					      double evtweight,
					      double luminosity,
					      double *external_upara_rnd1,
					      double *external_upara_rnd2,
					      double *external_SET_rnd,
					      double **external_elec_window,
					      double *extrndm_duparaeff,
					      double *externalRndm) {


  // skip if there are less than 2 smeared EM objects in an event.. useless, already cut
  if( emobjs_orig.size()<2 ) return;

  vector<PMCSEMObj> emobjs_smear;

  // Set the luminosity for the electrons upara correction
  if (!_Top_Bottom_Apply_Last){
    for(int ielec=0; ielec<emobjs_orig.size(); ielec++) {
	emobjs_orig[ielec].SetLumi(luminosity);
    }
  }

  double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
  double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
  double raw_scale_HAD_bifurcate_Tau = _recoilsmear->scale_HAD_bifurcate_Tau();
  double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
  double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
  double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
  double raw_Reltrans_HAD_bifurcate_RelRespTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelRespTrans();
  double raw_Reltrans_HAD_bifurcate_RelResnTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelResnTrans();
  double raw_Reltrans_HAD_bifurcate_RelTauTrans  = _recoilsmear->Reltrans_HAD_bifurcate_RelTauTrans();
  double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
  double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
  double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();
  double raw_alpha_mb = _recoilsmear->alpha_mb();
  double raw_alpha_mb_trans = _recoilsmear->alpha_mb_trans();
  double raw_alpha_zb = _recoilsmear->alpha_zb();
  int    raw_etflowfudge = _recoilsmear->EtFlowFudge();

  // recoil pT, phi at generator level
  double raw_recoil_pT = recoil_gen.Recoil();
  double raw_recoil_phi = recoil_gen.RecoilPhi();

  // do not change soft component smearing
  double recoilX_SoftComponent = _recoilsmear->recoilX_SoftComponent();
  double recoilY_SoftComponent = _recoilsmear->recoilY_SoftComponent();

  // get unfudged recoil's pT, phi and SET from Z->nunu model
  double znunu_recoil_pT = -1., znunu_recoil_phi = -1.;
  // recall the cached smeared hard recoil component from Z->nu+nu model
  // (it should be common not only for all 11x11 points but for the
  // "default" recoil parameters too!)
  _recoilsmear->GetLastHardRecoil_Method_B(NULL, NULL, &znunu_recoil_pT, &znunu_recoil_phi, NULL, NULL);
  double external_znunu_pt_resol = 1.0 - znunu_recoil_pT/raw_recoil_pT;
  double external_znunu_delta_phi = znunu_recoil_phi - raw_recoil_phi;
  double external_znunu_SET;
  double external_znunu_SET_expected;
  _recoilsmear->GetLastHardScalarEt_Method_B(&external_znunu_SET, &external_znunu_SET_expected, NULL);  

  // now generate templates
  for(int iHAD=0; iHAD<=_ZRecoilBifurcateBins[0]; iHAD++){
  for(int jHAD=0; jHAD<=_ZRecoilBifurcateBins[1]; jHAD++){
  for(int kHAD=0; kHAD<=_ZRecoilBifurcateBins[2]; kHAD++){
  for(int lHAD=0; lHAD<=_ZRecoilBifurcateBins[3]; lHAD++){
  for(int mHAD=0; mHAD<=_ZRecoilBifurcateBins[4]; mHAD++){
  for(int nHAD=0; nHAD<=_ZRecoilBifurcateBins[5]; nHAD++){
  for(int pHAD=0; pHAD<=_ZRecoilBifurcateBins[6]; pHAD++){
  for(int qHAD=0; qHAD<=_ZRecoilBifurcateBins[7]; qHAD++){


    // Start EM object anew
    emobjs_smear = emobjs_orig;


    double scale_HAD_bifurcate_A = raw_scale_HAD_bifurcate_A + (iHAD-_ZRecoilBifurcateBins[0]/2)*_ZRecoilBifurcateStep[0];
    double scale_HAD_bifurcate_B = raw_scale_HAD_bifurcate_B + (jHAD-_ZRecoilBifurcateBins[1]/2)*_ZRecoilBifurcateStep[1];
    double scale_HAD_bifurcate_Tau = raw_scale_HAD_bifurcate_Tau + (kHAD-_ZRecoilBifurcateBins[2]/2)*_ZRecoilBifurcateStep[2];
    double Relsampling_HAD_bifurcate_A = raw_Relsampling_HAD_bifurcate_A + (lHAD-_ZRecoilBifurcateBins[3]/2)*_ZRecoilBifurcateStep[3];
    double Relsampling_HAD_bifurcate_B = raw_Relsampling_HAD_bifurcate_B + (mHAD-_ZRecoilBifurcateBins[4]/2)*_ZRecoilBifurcateStep[4];
    double alpha_mb = raw_alpha_mb + (nHAD-_ZRecoilBifurcateBins[5]/2)*_ZRecoilBifurcateStep[5];
    double Relphi_HAD_bifurcate_A = raw_Relphi_HAD_bifurcate_A + (pHAD-_ZRecoilBifurcateBins[6]/2)*_ZRecoilBifurcateStep[6];
    double Relphi_HAD_bifurcate_B = raw_Relphi_HAD_bifurcate_B + (qHAD-_ZRecoilBifurcateBins[7]/2)*_ZRecoilBifurcateStep[7];


    double smear_recoil_pT = 0., smear_recoil_phi = 0., smear_SET = 0.;
    _recoilsmear->SmearHardRecoil_Method_D(raw_recoil_pT,
					   raw_recoil_phi,
					   scale_HAD_bifurcate_A,
					   scale_HAD_bifurcate_B,
					   scale_HAD_bifurcate_Tau,
					   Relsampling_HAD_bifurcate_A,
					   Relsampling_HAD_bifurcate_B,
					   raw_Relconst_HAD_bifurcate,
					   raw_Reltrans_HAD_bifurcate_RelRespTrans,
					   raw_Reltrans_HAD_bifurcate_RelResnTrans,
					   raw_Reltrans_HAD_bifurcate_RelTauTrans,
					   Relphi_HAD_bifurcate_A,
					   Relphi_HAD_bifurcate_B,
					   raw_RelconstPhi_HAD_bifurcate,
					   dummy,
					   smear_recoil_pT,
					   smear_recoil_phi,
					   smear_SET,
					   external_znunu_pt_resol,  // use this ONE instead of random value
					   external_znunu_delta_phi, // use this ONE instead of random value
					   external_znunu_SET,       // use this ONE instead of random value 
					   external_znunu_SET_expected, // use this ONE instead of random value
					   true,               // ....skip hard recoil randomization
					   false,              // and proceed with the fudging as usual....
					   raw_etflowfudge);


    // change soft component smearing
    double smear_Metx_From_MB = 0., smear_Mety_From_MB = 0., smear_Metx_From_ZB = 0., smear_Mety_From_ZB = 0.;
    double smear_Metx = 0., smear_Mety = 0.;


    double Jphi=recoil_gen.RecoilPhi();
    _recoilsmear->SmearSoftRecoil_Method_D(alpha_mb, raw_alpha_zb, dummy,
					   smear_Metx_From_MB, smear_Mety_From_MB,
					   smear_Metx_From_ZB, smear_Mety_From_ZB,
					   smear_Metx, smear_Mety,
					   &Jphi, raw_alpha_mb_trans);
    
    double recoilx_smear_template = smear_recoil_pT * cos(smear_recoil_phi);
    double recoily_smear_template = smear_recoil_pT * sin(smear_recoil_phi);

    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last){ 
      if (_TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
	_recoilsmear->ApplyTopBottomAsym(recoilx_smear_template, recoily_smear_template);   
      }
      else if (!_TBPhi_response_Hard_Only && _TBPhi_response_Soft_Only){
	_recoilsmear->ApplyTopBottomAsym(smear_Metx, smear_Mety);   
      }
    }
    
    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==2){    
      _recoilsmear->GetLastTopBottomAsym_B(smear_Metx, smear_Mety);      
    }
    
    double smear_recoil_X = recoilx_smear_template + smear_Metx; 
    double smear_recoil_Y = recoily_smear_template + smear_Mety;

    // Save the information and start applying correction: TB, uPara, Cracks and photons.

    PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);

    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
      _recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
    }

    double smear_recoil_X_beforeuParaCorr = smear_recoil_X;
    double smear_recoil_Y_beforeuParaCorr = smear_recoil_Y;

    PMCSRecoil new_recoil;
    TVector2 recoil_vector(smear_recoil_X, smear_recoil_Y);
    double ScalarEt = _recoilsmear->scalarEt();

    // RCLSA: This part is commented because this code takes too long to run.
    // So, basically we are fitting the recoil without cre-doing the delta u para calculation.

    // The recoil part is basically done, now we have to take care of the electron part.
    // Apply dUpara smearing.
    //     for(int ielec=0; ielec<emobjs_smear.size(); ielec++) {
    //       emobjs_smear[ielec].SetScalarEt(ScalarEt);
    //       if(abs(emobjs_smear[ielec].ppt()) > 15.) {
    // 	TVector2 elec_vec(emobjs_smear[ielec].ppx(), emobjs_smear[ielec].ppy());
    // 	double upara_elec = recoil_vector*elec_vec.Unit();
    // 	double uperp_elec = recoil_vector*elec_vec.Unit().Rotate(TMath::Pi()/2.0);
    // 	emobjs_smear[ielec].SetUPara(upara_elec);
    // 	emobjs_smear[ielec].SetUPerp(uperp_elec);
    // 	_emsmear->SmearEnergyUnderElecWindow(emobjs_smear[ielec],dummy,kFALSE,external_elec_window[ielec],extrndm_duparaeff);
    //       }
    //     }
    
    sort(emobjs_smear.begin(), emobjs_smear.end(), ComparePt);
    new_recoil = recoil_smear;
    if(_ZUparaCorrection)
      _recoilsmear->applyUparaCorrection(emobjs_smear, recoil_smear, new_recoil, 0);

    // Corrected recoil with dUpara
    smear_recoil_X = new_recoil.Recoilx();
    smear_recoil_Y = new_recoil.Recoily();   

    double ElecPx[2], ElecPy[2];
    for(int i=0; i<2; i++) {
      ElecPx[i] = emobjs_smear[i].ppx();
      ElecPy[i] = emobjs_smear[i].ppy();
    }
    
    // Z boson vector
    TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
    TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
    TVector2 z_vect = elec1_vect + elec2_vect;
    
    // divide events into smeared Z pT bins
    int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());   
    if(bin<0) {
      continue; // out of range
    }

    // Z boson bisector of the two electrons
    TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();
    
    double smear_recoil_X_beforePhotons = smear_recoil_X;
    double smear_recoil_Y_beforePhotons = smear_recoil_Y;

    //
    // include photons in the smeared recoil system
    // the photon response is described in EMSmear::SmearPhotonEnergy
    //
    for(int i=0; i<emobjs_smear.size(); i++) {
      if (i > 1){
	if (!_ZsimuFSRcracks) {
	  smear_recoil_X  += emobjs_smear[i].ppx();
	  smear_recoil_Y += emobjs_smear[i].ppy();
	} else {
	  float deteta=emobjs_smear[i].deteta();
	  float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	  if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
	    smear_recoil_X += emobjs_smear[i].ppx();
	    smear_recoil_Y += emobjs_smear[i].ppy();
	  }
	}
      }
    }


    // recoil after all corrections
    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
      _recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
    }
    
    recoil_smear.SetRecoil(smear_recoil_X,smear_recoil_Y);      

    // met after corrections for the two highest pT electrons
    double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
    double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
    PMCSMet met_smear(metX_component, metY_component);
     
    double Trigger_Version; 
    int passNonUParaEffs;
    int ncuts=0;     
    bool passEM = false, passRecoil=false;
    
    passEM=passesEMCuts(emobjs_smear,
			vtx_gen,
			dummy,
			&ncuts,
			&Trigger_Version,
			&passNonUParaEffs, false,externalRndm);
    if(!passEM) continue;
    
    passRecoil=passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
				NULL, NULL, false,
				external_upara_rnd1, external_upara_rnd2,
				&external_SET_rnd[0]); 
    if(!passRecoil) continue;
   
    PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);
    double phi_elec_1 = zcand.GetElec1().pphi();
    double phi_elec_2 = zcand.GetElec2().pphi();
    double dphi_em1_em2 = phi_elec_2 - phi_elec_1;
    dphi_em1_em2 = dphi_em1_em2 < 0 ? dphi_em1_em2 + TMath::TwoPi() : dphi_em1_em2;    
    double new_evtweight = evtweight * _efficiencysmear->ApplyRecoilReweight(dphi_em1_em2, zcand.ppt(), luminosity);  
    int type = zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);       
    if (type!=0) continue;

    if(_consistency_check) {
      int runNo, MBEvtIndex, ZBEvtIndex; double instLumi;
      _recoilsmear->getRunNoInstLumiMBZBEvtIndex(runNo, instLumi, MBEvtIndex, ZBEvtIndex);
      double UPara1 = zcand.UPara1();
      double UPara2 = zcand.UPara2();
      double ZElecEta1 = zcand.GetElec1().eta();
      double ZElecEta2 = zcand.GetElec2().eta();
      double ZElecDetEta1 = zcand.GetElec1().deteta();
      double ZElecDetEta2 = zcand.GetElec2().deteta();
      double ZElecPhiMod1 = fmod(16.*(zcand.GetElec1()).detphi()/TMath::Pi(), 1.0);
      double ZElecPhiMod2 = fmod(16.*(zcand.GetElec2()).detphi()/TMath::Pi(), 1.0);
      double ZElectrkPhiMod1 = fmod(16.*(zcand.GetElec1()).trkphiem3()/TMath::Pi(), 1.0);
      double ZElectrkPhiMod2 = fmod(16.*(zcand.GetElec2()).trkphiem3()/TMath::Pi(), 1.0);
      double ZElecPt1 = zcand.GetElec1().ppt();
      double ZElecPt2 = zcand.GetElec2().ppt();
      
      bool passCut_under_study_Elec1 =  wz_utils::passCut(_cut_under_study, _invert_cut,
							  runNo, _runNo_lowcut, _runNo_highcut,
							  luminosity, _InstLumi_lowcut, _InstLumi_highcut,
							  ScalarEt, _ScalarEt_lowcut, _ScalarEt_highcut,
							  ZElecEta1, _ElecEta_cut,
							  ZElecDetEta1, _ElecDetEta_lowcut, _ElecDetEta_highcut,
							  ZElectrkPhiMod1, _ElecPhiMod_cut,
							  UPara1, _UPara_lowcut, _UPara_highcut,
							  ZElecPt1, _ElecPt_lowcut, _ElecPt_highcut,
							  zcand.GetElec1().phi(), _ElecPhi_lowcut, _ElecPhi_highcut,
							  recoil_smear.RecoilPhi(), _RecoilPhi_lowcut, _RecoilPhi_highcut);
      bool passCut_under_study_Elec2 =  wz_utils::passCut(_cut_under_study, _invert_cut,
							  runNo, _runNo_lowcut, _runNo_highcut,
							  luminosity, _InstLumi_lowcut, _InstLumi_highcut,
							  ScalarEt, _ScalarEt_lowcut, _ScalarEt_highcut,
							  ZElecEta2, _ElecEta_cut,
							  ZElecDetEta2, _ElecDetEta_lowcut, _ElecDetEta_highcut,
							  ZElectrkPhiMod2, _ElecPhiMod_cut,
							  UPara2, _UPara_lowcut, _UPara_highcut,
							  ZElecPt2, _ElecPt_lowcut, _ElecPt_highcut,
							  zcand.GetElec2().phi(), _ElecPhi_lowcut, _ElecPhi_highcut,
							  recoil_smear.RecoilPhi(), _RecoilPhi_lowcut, _RecoilPhi_highcut);
      
      bool passCut_DetEtaCateg = true;
      if (_cut_under_study.Contains("DetEtaCateg_cut")) {
	passCut_DetEtaCateg = (zcand.DetEtaCategory(emobjs_smear[0].deteta(), emobjs_smear[1].deteta(), _CutEtaCC, _phimodcut, _ApplyTrkPhiModCut) == _DetEtaCateg_cut);
      }      
      if(!((passCut_under_study_Elec1 || passCut_under_study_Elec2) && passCut_DetEtaCateg)) continue;
    }		


    // now we can calculate the parameters... RCLSA: but! have to do pre processing, this would be huge!)
    TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);    
    double eta_imb = (z_vect + recoil_vect) * bisector_vect;    
    if(!_ZRecoilEtaCuts || (eta_imb > _ZRecoilEtaCutLow[bin] && eta_imb < _ZRecoilEtaCutHigh[bin])) {
      double d_phi;      
      if(z_vect.DeltaPhi(recoil_vect) > 0) { // Compactified distribution
	  d_phi = z_vect.DeltaPhi(recoil_vect) - TMath::Pi();
      } else {
	d_phi = z_vect.DeltaPhi(recoil_vect) + TMath::Pi();
      }

      evt_weight[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;
      evt_weight_2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight * new_evtweight;
      eta_imbalance_x[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += eta_imb * new_evtweight;
      eta_imbalance_x2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += eta_imb * eta_imb * new_evtweight;
      delta_phi_x[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += d_phi * new_evtweight;
      delta_phi_x2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += d_phi * d_phi * new_evtweight;

   
      //range is -25 to 25 with 10 bins so -25/-20, -20/-15, -15/-10, -10/-5, -5/0, 0/5, 5/10, 10/15, 15/20, 20/25
      if(eta_imb >= -25 && eta_imb < -20) eta_imbalance_x_1[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;
      if(eta_imb >= -20 && eta_imb < -15) eta_imbalance_x_2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;
      if(eta_imb >= -15 && eta_imb < -10) eta_imbalance_x_3[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;
      if(eta_imb >= -10 && eta_imb < -5) eta_imbalance_x_4[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;
      if(eta_imb >= -5 && eta_imb < 0) eta_imbalance_x_5[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;
      if(eta_imb >= 0 && eta_imb < 5) eta_imbalance_x_6[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;
      if(eta_imb >= 5 && eta_imb < 10) eta_imbalance_x_7[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;
      if(eta_imb >= 10 && eta_imb < 15) eta_imbalance_x_8[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;
      if(eta_imb >= 15 && eta_imb < 20) eta_imbalance_x_9[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;
      if(eta_imb >= 20 && eta_imb < 25) eta_imbalance_x_10[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight;

      //range is -25 to 25 with 10 bins so -25/-20, -20/-15, -15/-10, -10/-5, -5/0, 0/5, 5/10, 10/15, 15/20, 20/25
      //second set is so we can figure out the uncertainties later
      if(eta_imb >= -25 && eta_imb < -20) eta_imbalance_x_1_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight* new_evtweight;
      if(eta_imb >= -20 && eta_imb < -15) eta_imbalance_x_2_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight* new_evtweight;
      if(eta_imb >= -15 && eta_imb < -10) eta_imbalance_x_3_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight* new_evtweight;
      if(eta_imb >= -10 && eta_imb < -5) eta_imbalance_x_4_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight* new_evtweight;
      if(eta_imb >= -5 && eta_imb < 0) eta_imbalance_x_5_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight* new_evtweight;
      if(eta_imb >= 0 && eta_imb < 5) eta_imbalance_x_6_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight* new_evtweight;
      if(eta_imb >= 5 && eta_imb < 10) eta_imbalance_x_7_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight* new_evtweight;
      if(eta_imb >= 10 && eta_imb < 15) eta_imbalance_x_8_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight* new_evtweight;
      if(eta_imb >= 15 && eta_imb < 20) eta_imbalance_x_9_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight* new_evtweight;
      if(eta_imb >= 20 && eta_imb < 25) eta_imbalance_x_10_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][bin] += new_evtweight* new_evtweight;
    }
    
  }// qHAD
  }// pHAD
  }// nHAD
  }// mHAD
  }// lHAD
  }// kHAD
  }// jHAD
  }// iHAD

}



void ZAnalysis::TransZHadronicRecoilBifurcateStudy(vector<PMCSEMObj> &emobjs_orig, 
						   PMCSRecoil &recoil_gen, 
						   PMCSVtx &vtx_gen,
						   TRandom3 *dummy, 
						   double evtweight,
						   double luminosity,
						   double *external_upara_rnd1,
						   double *external_upara_rnd2,
						   double *external_SET_rnd,
						   double **external_elec_window,
						   double *extrndm_duparaeff,
						   double *externalRndm) {

  // skip if there are less than 2 smeared EM objects in an event.. useless, already cut
  if( emobjs_orig.size()<2 ) return;

  vector<PMCSEMObj> emobjs_smear;

  // Set the luminosity for the electrons upara correction
  if (!_Top_Bottom_Apply_Last){
    for(int ielec=0; ielec<emobjs_orig.size(); ielec++) {
      if(abs(emobjs_orig[ielec].ppt()) > 15.) {
	emobjs_orig[ielec].SetLumi(luminosity);
      }
    }
  }

  double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
  double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
  double raw_scale_HAD_bifurcate_Tau = _recoilsmear->scale_HAD_bifurcate_Tau();
  double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
  double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
  double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
  double raw_Reltrans_HAD_bifurcate_RelRespTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelRespTrans();
  double raw_Reltrans_HAD_bifurcate_RelResnTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelResnTrans();
  double raw_Reltrans_HAD_bifurcate_RelTauTrans  = _recoilsmear->Reltrans_HAD_bifurcate_RelTauTrans();
  double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
  double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
  double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();
  double raw_alpha_mb = _recoilsmear->alpha_mb();
  double raw_alpha_mb_trans = _recoilsmear->alpha_mb_trans();
  double raw_alpha_zb = _recoilsmear->alpha_zb();
  int    raw_etflowfudge = _recoilsmear->EtFlowFudge();
  
  // recoil pT, phi at generator level
  double raw_recoil_pT = recoil_gen.Recoil();
  double raw_recoil_phi = recoil_gen.RecoilPhi();

  // do not change soft component smearing
  double recoilX_SoftComponent = _recoilsmear->recoilX_SoftComponent();
  double recoilY_SoftComponent = _recoilsmear->recoilY_SoftComponent();

  // get unfudged recoil's pT, phi and SET from Z->nunu model
  double znunu_recoil_pT = -1., znunu_recoil_phi = -1.;
  // recall the cached smeared hard recoil component from Z->nu+nu model
  // (it should be common not only for all 11x11 points but for the
  // "default" recoil parameters too!)
  _recoilsmear->GetLastHardRecoil_Method_B(NULL, NULL, &znunu_recoil_pT, &znunu_recoil_phi, NULL, NULL);
  double external_znunu_pt_resol = 1.0 - znunu_recoil_pT/raw_recoil_pT;
  double external_znunu_delta_phi = znunu_recoil_phi - raw_recoil_phi;
  double external_znunu_SET;
  double external_znunu_SET_expected;
  _recoilsmear->GetLastHardScalarEt_Method_B(&external_znunu_SET, &external_znunu_SET_expected, NULL);  

  // now generate templates

  for(int iHAD=0; iHAD<=_TransZRecoilBifurcateBins[0]; iHAD++){
  for(int jHAD=0; jHAD<=_TransZRecoilBifurcateBins[1]; jHAD++){
  for(int kHAD=0; kHAD<=_TransZRecoilBifurcateBins[2]; kHAD++){
  for(int lHAD=0; lHAD<=_TransZRecoilBifurcateBins[3]; lHAD++){

    double Reltrans_HAD_bifurcate_RelRespTrans =  raw_Reltrans_HAD_bifurcate_RelRespTrans + (iHAD-_TransZRecoilBifurcateBins[0]/2)*_TransZRecoilBifurcateStep[0];
    double Reltrans_HAD_bifurcate_RelResnTrans =  raw_Reltrans_HAD_bifurcate_RelResnTrans + (jHAD-_TransZRecoilBifurcateBins[1]/2)*_TransZRecoilBifurcateStep[1];
    double Reltrans_HAD_bifurcate_RelTauTrans =  raw_Reltrans_HAD_bifurcate_RelTauTrans + (kHAD-_TransZRecoilBifurcateBins[2]/2)*_TransZRecoilBifurcateStep[2];
    double alpha_mb_trans = raw_alpha_mb_trans + (lHAD-_TransZRecoilBifurcateBins[3]/2)*_TransZRecoilBifurcateStep[3];

    double smear_recoil_pT = 0., smear_recoil_phi = 0., smear_SET = 0.;
    _recoilsmear->SmearHardRecoil_Method_D(raw_recoil_pT,
					   raw_recoil_phi,
					   raw_scale_HAD_bifurcate_A,
					   raw_scale_HAD_bifurcate_B,
					   raw_scale_HAD_bifurcate_Tau,
					   raw_Relsampling_HAD_bifurcate_A,
					   raw_Relsampling_HAD_bifurcate_B,
					   raw_Relconst_HAD_bifurcate,
					   Reltrans_HAD_bifurcate_RelRespTrans,
					   Reltrans_HAD_bifurcate_RelResnTrans,
					   Reltrans_HAD_bifurcate_RelTauTrans,
					   raw_Relphi_HAD_bifurcate_A,
					   raw_Relphi_HAD_bifurcate_B,
					   raw_RelconstPhi_HAD_bifurcate,
					   dummy,
					   smear_recoil_pT,
					   smear_recoil_phi,
					   smear_SET,
					   external_znunu_pt_resol,  // use this ONE instead of random value
					   external_znunu_delta_phi, // use this ONE instead of random value
					   external_znunu_SET,       // use this ONE instead of random value 
					   external_znunu_SET_expected, // use this ONE instead of random value
					   true,               // ....skip hard recoil randomization
					   false,
					   raw_etflowfudge);

    // change soft component smearing
    double smear_Metx_From_MB = 0., smear_Mety_From_MB = 0., smear_Metx_From_ZB = 0., smear_Mety_From_ZB = 0.;
    double smear_Metx = 0., smear_Mety = 0.;

    double Jphi=recoil_gen.RecoilPhi();
    _recoilsmear->SmearSoftRecoil_Method_D(raw_alpha_mb, raw_alpha_zb, dummy,
					   smear_Metx_From_MB, smear_Mety_From_MB,
					   smear_Metx_From_ZB, smear_Mety_From_ZB,
					   smear_Metx, smear_Mety,
					   &Jphi, alpha_mb_trans);
    
    double recoilx_smear_template = smear_recoil_pT * cos(smear_recoil_phi);
    double recoily_smear_template = smear_recoil_pT * sin(smear_recoil_phi);

    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last){ 
      if (_TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
	_recoilsmear->ApplyTopBottomAsym(recoilx_smear_template, recoily_smear_template);   
      }
      else if (!_TBPhi_response_Hard_Only && _TBPhi_response_Soft_Only){
	_recoilsmear->ApplyTopBottomAsym(smear_Metx, smear_Mety);   
      }
    }
    
    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==2){    
      _recoilsmear->GetLastTopBottomAsym_B(smear_Metx, smear_Mety);      
    }
    
    double smear_recoil_X = recoilx_smear_template + smear_Metx; 
    double smear_recoil_Y = recoily_smear_template + smear_Mety;

    // Save the information and start applying correction: TB, uPara, Cracks and photons.

    PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);

    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
      _recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
    }

    double smear_recoil_X_beforeuParaCorr = smear_recoil_X;
    double smear_recoil_Y_beforeuParaCorr = smear_recoil_Y;

    PMCSRecoil new_recoil;
    TVector2 recoil_vector(smear_recoil_X, smear_recoil_Y);
    double ScalarEt = _recoilsmear->scalarEt();

    // The recoil part is basically done, now we have to take care of the electron part.
    // Apply dUpara smearing.
    for(int ielec=0; ielec<emobjs_smear.size(); ielec++) {
      emobjs_smear[ielec].SetScalarEt(ScalarEt);
      if(abs(emobjs_smear[ielec].ppt()) > 15.) {
	TVector2 elec_vec(emobjs_smear[ielec].ppx(), emobjs_smear[ielec].ppy());
	double upara_elec = recoil_vector*elec_vec.Unit();
	double uperp_elec = recoil_vector*elec_vec.Unit().Rotate(TMath::Pi()/2.0);
	emobjs_smear[ielec].SetUPara(upara_elec);
	emobjs_smear[ielec].SetUPerp(uperp_elec);
	_emsmear->SmearEnergyUnderElecWindow(emobjs_smear[ielec],dummy,kFALSE,external_elec_window[ielec],extrndm_duparaeff);
      }
    }
    
    sort(emobjs_smear.begin(), emobjs_smear.end(), ComparePt);
    new_recoil = recoil_smear;
    if(_ZUparaCorrection)
      _recoilsmear->applyUparaCorrection(emobjs_smear, recoil_smear, new_recoil, 0);

    // Corrected recoil with dUpara
    smear_recoil_X = new_recoil.Recoilx();
    smear_recoil_Y = new_recoil.Recoily();   

    double ElecPx[2], ElecPy[2];
    for(int i=0; i<2; i++) {
      ElecPx[i] = emobjs_smear[i].ppx();
      ElecPy[i] = emobjs_smear[i].ppy();
    }
    
    // Z boson vector
    TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
    TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
    TVector2 z_vect = elec1_vect + elec2_vect;
    
    // divide events into smeared Z pT bins
    int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());
    if(bin<0) continue; // out of range
    
    // Z boson bisector of the two electrons
    TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();
    
    double smear_recoil_X_beforePhotons = smear_recoil_X;
    double smear_recoil_Y_beforePhotons = smear_recoil_Y;

    //
    // include photons in the smeared recoil system
    // the photon response is described in EMSmear::SmearPhotonEnergy
    //
    for(int i=0; i<emobjs_smear.size(); i++) {
      if (i > 1){
	if (!_ZsimuFSRcracks) {
	  smear_recoil_X  += emobjs_smear[i].ppx();
	  smear_recoil_Y += emobjs_smear[i].ppy();
	} else {
	  float deteta=emobjs_smear[i].deteta();
	  float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	  if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
	    smear_recoil_X += emobjs_smear[i].ppx();
	    smear_recoil_Y += emobjs_smear[i].ppy();
	  }
	}
      }
    }


    // recoil after all corrections
    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
      _recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
    }
    
    recoil_smear.SetRecoil(smear_recoil_X,smear_recoil_Y);      

    // met after corrections for the two highest pT electrons
    double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
    double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
    PMCSMet met_smear(metX_component, metY_component);
     
    double Trigger_Version; 
    int passNonUParaEffs;
    int ncuts=0;     
    bool passEM = false, passRecoil=false;
    
    passEM=passesEMCuts(emobjs_smear,
			vtx_gen,
			dummy,
			&ncuts,
			&Trigger_Version,
			&passNonUParaEffs, false,externalRndm);
    passRecoil=passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
				NULL, NULL, false,
				external_upara_rnd1, external_upara_rnd2,
				&external_SET_rnd[0]);
    if(!passRecoil || !passEM) return;
    PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);
    double phi_elec_1 = zcand.GetElec1().pphi();
    double phi_elec_2 = zcand.GetElec2().pphi();
    double dphi_em1_em2 = phi_elec_2 - phi_elec_1;
    dphi_em1_em2 = dphi_em1_em2 < 0 ? dphi_em1_em2 + TMath::TwoPi() : dphi_em1_em2;    
    double new_evtweight = evtweight * _efficiencysmear->ApplyRecoilReweight(dphi_em1_em2, zcand.ppt(), luminosity);    
    int type = zcand.Type(_CutEtaCC, _CutEtaEC1, _CutEtaEC2, _phimodcut, _ApplyTrkPhiModCut);       
    if (type!=0) continue;

    if(_consistency_check) {
      int runNo, MBEvtIndex, ZBEvtIndex; double instLumi;
      _recoilsmear->getRunNoInstLumiMBZBEvtIndex(runNo, instLumi, MBEvtIndex, ZBEvtIndex);
      double UPara1 = zcand.UPara1();
      double UPara2 = zcand.UPara2();
      double ZElecEta1 = zcand.GetElec1().eta();
      double ZElecEta2 = zcand.GetElec2().eta();
      double ZElecDetEta1 = zcand.GetElec1().deteta();
      double ZElecDetEta2 = zcand.GetElec2().deteta();
      double ZElecPhiMod1 = fmod(16.*(zcand.GetElec1()).detphi()/TMath::Pi(), 1.0);
      double ZElecPhiMod2 = fmod(16.*(zcand.GetElec2()).detphi()/TMath::Pi(), 1.0);
      double ZElectrkPhiMod1 = fmod(16.*(zcand.GetElec1()).trkphiem3()/TMath::Pi(), 1.0);
      double ZElectrkPhiMod2 = fmod(16.*(zcand.GetElec2()).trkphiem3()/TMath::Pi(), 1.0);
      double ZElecPt1 = zcand.GetElec1().ppt();
      double ZElecPt2 = zcand.GetElec2().ppt();
      
      bool passCut_under_study_Elec1 =  wz_utils::passCut(_cut_under_study, _invert_cut,
							  runNo, _runNo_lowcut, _runNo_highcut,
							  luminosity, _InstLumi_lowcut, _InstLumi_highcut,
							  ScalarEt, _ScalarEt_lowcut, _ScalarEt_highcut,
							  ZElecEta1, _ElecEta_cut,
							  ZElecDetEta1, _ElecDetEta_lowcut, _ElecDetEta_highcut,
							  ZElectrkPhiMod1, _ElecPhiMod_cut,
							  UPara1, _UPara_lowcut, _UPara_highcut,
							  ZElecPt1, _ElecPt_lowcut, _ElecPt_highcut,
							  zcand.GetElec1().phi(), _ElecPhi_lowcut, _ElecPhi_highcut,
							  recoil_smear.RecoilPhi(), _RecoilPhi_lowcut, _RecoilPhi_highcut);
      bool passCut_under_study_Elec2 =  wz_utils::passCut(_cut_under_study, _invert_cut,
							  runNo, _runNo_lowcut, _runNo_highcut,
							  luminosity, _InstLumi_lowcut, _InstLumi_highcut,
							  ScalarEt, _ScalarEt_lowcut, _ScalarEt_highcut,
							  ZElecEta2, _ElecEta_cut,
							  ZElecDetEta2, _ElecDetEta_lowcut, _ElecDetEta_highcut,
							  ZElectrkPhiMod2, _ElecPhiMod_cut,
							  UPara2, _UPara_lowcut, _UPara_highcut,
							  ZElecPt2, _ElecPt_lowcut, _ElecPt_highcut,
							  zcand.GetElec2().phi(), _ElecPhi_lowcut, _ElecPhi_highcut,
							  recoil_smear.RecoilPhi(), _RecoilPhi_lowcut, _RecoilPhi_highcut);
      
      bool passCut_DetEtaCateg = true;
      if (_cut_under_study.Contains("DetEtaCateg_cut")) {
	passCut_DetEtaCateg = (zcand.DetEtaCategory(emobjs_smear[0].deteta(), emobjs_smear[1].deteta(), _CutEtaCC, _phimodcut, _ApplyTrkPhiModCut) == _DetEtaCateg_cut);
      }      
      if(!((passCut_under_study_Elec1 || passCut_under_study_Elec2) && passCut_DetEtaCateg)) return;
    }		


    // now we can calculate the parameters... RCLSA: but! have to do pre processing, this would be huge!)
    TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);
    
    double eta_imb = (z_vect + recoil_vect) * bisector_vect;
    
    if(!_ZRecoilEtaCuts || (eta_imb > _ZRecoilEtaCutLow[bin] && eta_imb < _ZRecoilEtaCutHigh[bin])) {
      double d_phi;
      
      if(z_vect.DeltaPhi(recoil_vect) > 0) { // Compactified distribution
	d_phi = z_vect.DeltaPhi(recoil_vect) - TMath::Pi();
      } else {
	d_phi = z_vect.DeltaPhi(recoil_vect) + TMath::Pi();
      }
      
      trans_evt_weight[iHAD][jHAD][kHAD][lHAD][bin] += new_evtweight;
      trans_evt_weight_2[iHAD][jHAD][kHAD][lHAD][bin] += new_evtweight * new_evtweight;
      trans_eta_imbalance_x[iHAD][jHAD][kHAD][lHAD][bin] += eta_imb * new_evtweight;
      trans_eta_imbalance_x2[iHAD][jHAD][kHAD][lHAD][bin] += eta_imb * eta_imb * new_evtweight;
    }

  }// lHAD
  }// kHAD
  }// jHAD
  }// iHAD

}

// determine hadronic momentum scale for bifurcate method
void ZAnalysis::HadronicMomentumScaleBifurcateStudy(vector<PMCSEMObj> &emobjs_smear, 
						    PMCSRecoil &recoil_gen, 
						    PMCSVtx &vtx_gen,
 						    TRandom3 *dummy, 
						    std::string prefix, 
						    double evtweight,
						    double *external_upara_rnd1,
						    double *external_upara_rnd2,
						    double *external_SET_rnd) {
  // skip if there are less than 2 smeared EM objects in an event
  if( emobjs_smear.size()<2 ) return;

  // get two electron uparaCorr, energyLeakage, eta and phi to calculate uparallel corrections
  double ElecUParaCorr[2], ElecEnergyLeakage[2], ElecEta[2], ElecDetEta[2], 
         ElecPhi[2], ElecDetPhi[2], ElecPx[2], ElecPy[2];
  for(int i=0; i<2; i++) {
    ElecUParaCorr[i] = emobjs_smear[i].UParaCorr();
    ElecEnergyLeakage[i] = emobjs_smear[i].EnergyLeakage();
    ElecEta[i] = emobjs_smear[i].peta();
    ElecDetEta[i] = emobjs_smear[i].deteta();
    ElecPhi[i] = emobjs_smear[i].pphi();
    ElecDetPhi[i] = emobjs_smear[i].detphi();
    ElecPx[i] = emobjs_smear[i].ppx();
    ElecPy[i] = emobjs_smear[i].ppy();
  }

  // Z boson vector
  TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
  TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
  TVector2 z_vect = elec1_vect + elec2_vect;
  
  // divide events into smeared Z pT bins
  int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());
  if(bin<0) return; // out of range
  char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);

  // Z boson bisector of the two electrons
  TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();

  double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
  double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
  double raw_scale_HAD_bifurcate_Tau = _recoilsmear->scale_HAD_bifurcate_Tau();
  double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
  double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
  double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
  double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
  double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
  double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();
  double raw_Reltrans_HAD_bifurcate_RelRespTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelRespTrans();
  double raw_Reltrans_HAD_bifurcate_RelResnTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelResnTrans();
  double raw_Reltrans_HAD_bifurcate_RelTauTrans  = _recoilsmear->Reltrans_HAD_bifurcate_RelTauTrans();

  // recoil pT, phi at generator level
  double raw_recoil_pT = recoil_gen.Recoil();
  double raw_recoil_phi = recoil_gen.RecoilPhi();

  // do not change soft component smearing
  double recoilX_SoftComponent = _recoilsmear->recoilX_SoftComponent();
  double recoilY_SoftComponent = _recoilsmear->recoilY_SoftComponent();

  // get unfudged recoil's pT, phi and SET from Z->nunu model
  double znunu_recoil_pT = -1., znunu_recoil_phi = -1.;
  // recall the cached smeared hard recoil component from Z->nu+nu model
  // (it should be common not only for all 11x11 points but for the
  // "default" recoil parameters too!)
  _recoilsmear->GetLastHardRecoil_Method_B(NULL, NULL, &znunu_recoil_pT, &znunu_recoil_phi, NULL, NULL);
  double external_znunu_pt_resol = 1.0 - znunu_recoil_pT/raw_recoil_pT;
  double external_znunu_delta_phi = znunu_recoil_phi - raw_recoil_phi;
  double external_znunu_SET;
  double external_znunu_SET_expected;
  _recoilsmear->GetLastHardScalarEt_Method_B(&external_znunu_SET, &external_znunu_SET_expected, NULL);

//   ///////////////////// DEBUG //////////////////////////
//   //
//   cout << "++++ TEMPLATE BEFORE LOOP:" << endl
//        << "     Buffered hard SET(unfudged)=" << external_znunu_SET 
//        << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
//        << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//   //
//   ///////////////////// DEBUG //////////////////////////

  // now generate templates
  int ihist = 0;
  for(int iHAD=0; iHAD<=_Bins_HadronicScaleBifurcateStudy; iHAD++) {
    for(int jHAD=0; jHAD<=_Bins_HadronicScaleBifurcateStudy; jHAD++) {
      double scale_HAD_bifurcate_A = _scale_HAD_bifurcate_A_center + (iHAD-_Bins_HadronicScaleBifurcateStudy/2) * _scale_HAD_bifurcate_A_step;
      double scale_HAD_bifurcate_B = _scale_HAD_bifurcate_B_center + (jHAD-_Bins_HadronicScaleBifurcateStudy/2) * _scale_HAD_bifurcate_B_step;

      // smear hard component
      double smear_recoil_pT = 0., smear_recoil_phi = 0., smear_SET = 0.;
      
      _recoilsmear->SmearHardRecoil_Method_D(raw_recoil_pT,
                                             raw_recoil_phi,
                                             scale_HAD_bifurcate_A,
                                             scale_HAD_bifurcate_B,
					     raw_scale_HAD_bifurcate_Tau,
                                             raw_Relsampling_HAD_bifurcate_A,
                                             raw_Relsampling_HAD_bifurcate_B,
                                             raw_Relconst_HAD_bifurcate,
					     raw_Reltrans_HAD_bifurcate_RelRespTrans,
					     raw_Reltrans_HAD_bifurcate_RelResnTrans,
					     raw_Reltrans_HAD_bifurcate_RelTauTrans,
                                             raw_Relphi_HAD_bifurcate_A,
                                             raw_Relphi_HAD_bifurcate_B,
                                             raw_RelconstPhi_HAD_bifurcate,
                                             dummy,
                                             smear_recoil_pT,
                                             smear_recoil_phi,
					     smear_SET,
                                             external_znunu_pt_resol,  // use this ONE instead of random value
                                             external_znunu_delta_phi, // use this ONE instead of random value
					     external_znunu_SET,       // use this ONE instead of random value 
					     external_znunu_SET_expected, // use this ONE instead of random value
                                             true,               // ....skip hard recoil randomization
                                             false );            // and proceed with the fudging as usual....
      
      // add uparallel correction
      double sum_UparaCorrX = 0., sum_UparaCorrY = 0.;
      for(int ielec=0; ielec<2; ielec++) {
	sum_UparaCorrX += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* cos(ElecPhi[ielec]);
	sum_UparaCorrY += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* sin(ElecPhi[ielec]);
      }
      double recoilx_smear_template = smear_recoil_pT * cos(smear_recoil_phi);
      double recoily_smear_template = smear_recoil_pT * sin(smear_recoil_phi);
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last){ 
	if (_TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
	_recoilsmear->ApplyTopBottomAsym(recoilx_smear_template, recoily_smear_template);   
	}
      }
      
      // final smeared recoil system (soft component added)
      double smear_recoil_X = recoilx_smear_template + recoilX_SoftComponent;
      double smear_recoil_Y = recoily_smear_template + recoilY_SoftComponent;
      
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
      }
      
      smear_recoil_X = smear_recoil_X - sum_UparaCorrX;
      smear_recoil_Y = smear_recoil_Y - sum_UparaCorrY;
      
      //
      // include photons in the smeared recoil system
      // the photon response is described in EMSmear::SmearPhotonEnergy
      //
      for(int i=0; i<emobjs_smear.size(); i++) {
	if (i > 1){
	  if (!_ZsimuFSRcracks) {
	    smear_recoil_X  += emobjs_smear[i].ppx();
	    smear_recoil_Y += emobjs_smear[i].ppy();
	  } else {
	    float deteta=emobjs_smear[i].deteta();
	    float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	    if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
	      smear_recoil_X += emobjs_smear[i].ppx();
	      smear_recoil_Y += emobjs_smear[i].ppy();
	    }
	  }
	}
      }
      
      // recoil after all corrections
      PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
	recoil_smear.SetRecoil(smear_recoil_X, smear_recoil_Y);
      }
      // met after corrections for the two highest pT electrons
      double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
      double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
      PMCSMet met_smear(metX_component, metY_component);

      // skip randomization of U|| efficiency and SET
      if( passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
			   NULL, NULL, false,
			   external_upara_rnd1, external_upara_rnd2,
			   external_SET_rnd) ) {
	// now we can calculate eta imbalance
	TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);
	double eta_imbalance = (z_vect + recoil_vect) * bisector_vect;
 	char sn[20]; sprintf(sn, "%d", ihist);	
	_histos.Fill1D((prefix+"hZcandEtaImBalance_bin_"+pee_bin_sn+"_"+sn).c_str(), 
		       eta_imbalance, evtweight);
      }

//       ///////////////////// DEBUG //////////////////////////
//       //
//       double dummyset;
//       _recoilsmear->GetLastHardScalarEt_Method_B(&dummyset, NULL, NULL);
//       cout << "++++ TEMPLATE INSIDE LOOP (iHAD=" << iHAD
// 	   << ", jHAD=" << jHAD << "):" << endl 
// 	   << "     Buffered hard SET (unfudged)=" << dummyset
// 	   << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
// 	   << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//       //
//       ///////////////////// DEBUG //////////////////////////

      ihist ++;
    }// iHAD
  }// jHAD
  
  // set back old smearing parameters
  _recoilsmear->SetHardSmearingParameters_MethodB(raw_scale_HAD_bifurcate_A, 
						  raw_scale_HAD_bifurcate_B, 
						  raw_scale_HAD_bifurcate_Tau, 
	                                          raw_Relsampling_HAD_bifurcate_A, 
						  raw_Relsampling_HAD_bifurcate_B, 
						  raw_Relconst_HAD_bifurcate,
						  raw_Reltrans_HAD_bifurcate_RelRespTrans,
						  raw_Reltrans_HAD_bifurcate_RelResnTrans,
						  raw_Reltrans_HAD_bifurcate_RelTauTrans,
                                                  raw_Relphi_HAD_bifurcate_A, 
						  raw_Relphi_HAD_bifurcate_B, 
						  raw_RelconstPhi_HAD_bifurcate);
}


// determine hadronic momentum scale for bifurcate method
void ZAnalysis::HadronicMomentumScale2BifurcateStudy(vector<PMCSEMObj> &emobjs_smear, 
						     PMCSRecoil &recoil_gen, 
						     PMCSVtx &vtx_gen,
						     TRandom3 *dummy, 
						     std::string prefix, 
						     double evtweight,
						     double *external_upara_rnd1,
						     double *external_upara_rnd2,
						     double *external_SET_rnd) {
  // skip if there are less than 2 smeared EM objects in an event
  if( emobjs_smear.size()<2 ) return;
  
  // get two electron uparaCorr, energyLeakage, eta and phi to calculate uparallel corrections
  double ElecUParaCorr[2], ElecEnergyLeakage[2], ElecEta[2], ElecDetEta[2], 
    ElecPhi[2], ElecDetPhi[2], ElecPx[2], ElecPy[2];
  for(int i=0; i<2; i++) {
    ElecUParaCorr[i] = emobjs_smear[i].UParaCorr();
    ElecEnergyLeakage[i] = emobjs_smear[i].EnergyLeakage();
    ElecEta[i] = emobjs_smear[i].peta();
    ElecDetEta[i] = emobjs_smear[i].deteta();
    ElecPhi[i] = emobjs_smear[i].pphi();
    ElecDetPhi[i] = emobjs_smear[i].detphi();
    ElecPx[i] = emobjs_smear[i].ppx();
    ElecPy[i] = emobjs_smear[i].ppy();
  }

  // Z boson vector
  TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
  TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
  TVector2 z_vect = elec1_vect + elec2_vect;
  
  // divide events into smeared Z pT bins
  int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());
  if(bin<0) return; // out of range
  char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);

  // Z boson bisector of the two electrons
  TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();

  double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
  double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
  double raw_scale_HAD_bifurcate_Tau = _recoilsmear->scale_HAD_bifurcate_Tau();
  double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
  double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
  double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
  double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
  double raw_Reltrans_HAD_bifurcate_RelRespTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelRespTrans();
  double raw_Reltrans_HAD_bifurcate_RelResnTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelResnTrans();
  double raw_Reltrans_HAD_bifurcate_RelTauTrans  = _recoilsmear->Reltrans_HAD_bifurcate_RelTauTrans();
  double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
  double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();

  // recoil pT, phi at generator level
  double raw_recoil_pT = recoil_gen.Recoil();
  double raw_recoil_phi = recoil_gen.RecoilPhi();

  // do not change soft component smearing
  double recoilX_SoftComponent = _recoilsmear->recoilX_SoftComponent();
  double recoilY_SoftComponent = _recoilsmear->recoilY_SoftComponent();

  // get unfudged recoil's pT, phi and SET from Z->nunu model
  double znunu_recoil_pT = -1., znunu_recoil_phi = -1.;
  // recall the cached smeared hard recoil component from Z->nu+nu model
  // (it should be common not only for all 11x11 points but for the
  // "default" recoil parameters too!)
  _recoilsmear->GetLastHardRecoil_Method_B(NULL, NULL, &znunu_recoil_pT, &znunu_recoil_phi, NULL, NULL);
  double external_znunu_pt_resol = 1.0 - znunu_recoil_pT/raw_recoil_pT;
  double external_znunu_delta_phi = znunu_recoil_phi - raw_recoil_phi;
  double external_znunu_SET;
  double external_znunu_SET_expected;
  _recoilsmear->GetLastHardScalarEt_Method_B(&external_znunu_SET, &external_znunu_SET_expected, NULL);

  // now generate templates
  int ihist = 0;
  for(int iHAD=0; iHAD<=_Bins_HadronicScale2BifurcateStudy; iHAD++) {
    for(int jHAD=0; jHAD<=_Bins_HadronicScale2BifurcateStudy; jHAD++) {
      for(int kHAD=0; kHAD<=_Bins_HadronicScale2BifurcateStudy; kHAD++) {
	double scale_HAD_bifurcate_A = _scale_HAD_bifurcate2_A_center + (iHAD-_Bins_HadronicScale2BifurcateStudy/2) * _scale_HAD_bifurcate2_A_step;
	double scale_HAD_bifurcate_B = _scale_HAD_bifurcate2_B_center + (jHAD-_Bins_HadronicScale2BifurcateStudy/2) * _scale_HAD_bifurcate2_B_step;
	double scale_HAD_bifurcate_Tau = _scale_HAD_bifurcate2_Tau_center + (kHAD-_Bins_HadronicScale2BifurcateStudy/2) * _scale_HAD_bifurcate2_Tau_step;
	
	// smear hard component
	double smear_recoil_pT = 0., smear_recoil_phi = 0., smear_SET = 0.;
	
	_recoilsmear->SmearHardRecoil_Method_D(raw_recoil_pT,
					       raw_recoil_phi,
					       scale_HAD_bifurcate_A,
					       scale_HAD_bifurcate_B,
					       scale_HAD_bifurcate_Tau,
					       raw_Relsampling_HAD_bifurcate_A,
					       raw_Relsampling_HAD_bifurcate_B,
					       raw_Relconst_HAD_bifurcate,
					       raw_Reltrans_HAD_bifurcate_RelRespTrans,
					       raw_Reltrans_HAD_bifurcate_RelResnTrans,
					       raw_Reltrans_HAD_bifurcate_RelTauTrans,
					       raw_Relphi_HAD_bifurcate_A,
					       raw_Relphi_HAD_bifurcate_B,
					       raw_RelconstPhi_HAD_bifurcate,
					       dummy,
					       smear_recoil_pT,
					       smear_recoil_phi,
					       smear_SET,
					       external_znunu_pt_resol,  // use this ONE instead of random value
					       external_znunu_delta_phi, // use this ONE instead of random value
					       external_znunu_SET,       // use this ONE instead of random value 
					       external_znunu_SET_expected, // use this ONE instead of random value
					       true,               // ....skip hard recoil randomization
					       false );            // and proceed with the fudging as usual....
	
	// add uparallel correction
	double sum_UparaCorrX = 0., sum_UparaCorrY = 0.;
	for(int ielec=0; ielec<2; ielec++) {
	  sum_UparaCorrX += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* cos(ElecPhi[ielec]);
	  sum_UparaCorrY += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* sin(ElecPhi[ielec]);
	}
	
	double recoilx_smear_template = smear_recoil_pT * cos(smear_recoil_phi);
	double recoily_smear_template = smear_recoil_pT * sin(smear_recoil_phi);
	if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last){ 
	  if (_TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
	    _recoilsmear->ApplyTopBottomAsym(recoilx_smear_template, recoily_smear_template);   
	  }
	}
	
	// final smeared recoil system (soft component added)
	double smear_recoil_X = recoilx_smear_template + recoilX_SoftComponent;
	double smear_recoil_Y = recoily_smear_template + recoilY_SoftComponent;
	if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
	  _recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
	}
	
	smear_recoil_X = smear_recoil_X - sum_UparaCorrX;
	smear_recoil_Y = smear_recoil_Y - sum_UparaCorrY;
	
	//
	// include photons in the smeared recoil system
	// the photon response is described in EMSmear::SmearPhotonEnergy
	//
	for(int i=0; i<emobjs_smear.size(); i++) {
	  if (i > 1){
	    if (!_ZsimuFSRcracks) {
	      smear_recoil_X  += emobjs_smear[i].ppx();
	      smear_recoil_Y += emobjs_smear[i].ppy();
	    } else {
	      float deteta=emobjs_smear[i].deteta();
	      float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	      if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
		smear_recoil_X += emobjs_smear[i].ppx();
		smear_recoil_Y += emobjs_smear[i].ppy();
	      }
	    }
	  }
	}
	
	// recoil after all corrections
	PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);
	if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
	  _recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
	  recoil_smear.SetRecoil(smear_recoil_X, smear_recoil_Y);
	}
	
	// met after corrections for the two highest pT electrons
	double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
	double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
	PMCSMet met_smear(metX_component, metY_component);
	
	// skip randomization of U|| efficiency and SET
	if( passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
			     NULL, NULL, false,
			     external_upara_rnd1, external_upara_rnd2,
			     external_SET_rnd) ) {
	  // now we can calculate eta imbalance
	  TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);
	  double eta_imbalance = (z_vect + recoil_vect) * bisector_vect;
	  char sn[20]; sprintf(sn, "%d", ihist);	
	  _histos.Fill1D((prefix+"hZcandEtaImBalance_bin_"+pee_bin_sn+"_"+sn).c_str(), 
			 eta_imbalance, evtweight);
	}
	
	ihist ++;
      } // kHAD
    }// jHAD
  }// iHAD
  
  // set back old smearing parameters
  _recoilsmear->SetHardSmearingParameters_MethodB(raw_scale_HAD_bifurcate_A, 
						  raw_scale_HAD_bifurcate_B, 
						  raw_scale_HAD_bifurcate_Tau, 
	                                          raw_Relsampling_HAD_bifurcate_A, 
						  raw_Relsampling_HAD_bifurcate_B, 
						  raw_Relconst_HAD_bifurcate,
						  raw_Reltrans_HAD_bifurcate_RelRespTrans,
						  raw_Reltrans_HAD_bifurcate_RelResnTrans,
						  raw_Reltrans_HAD_bifurcate_RelTauTrans,
                                                  raw_Relphi_HAD_bifurcate_A, 
						  raw_Relphi_HAD_bifurcate_B, 
						  raw_RelconstPhi_HAD_bifurcate);
}

// determine hadronic momentum resolution for bifurcate method
void ZAnalysis::HadronicMomentumResolutionBifurcateStudy(vector<PMCSEMObj> &emobjs_smear, 
							 PMCSRecoil &recoil_gen, 
							 PMCSVtx &vtx_gen,
							 TRandom3 *dummy, 
							 std::string prefix, 
							 double evtweight,
							 double *external_upara_rnd1,
							 double *external_upara_rnd2,
							 double *external_SET_rnd) {
  // skip if there are less than 2 smeared EM objects in an event
  if( emobjs_smear.size()<2 ) return;

  // get two electron uparaCorr, energyLeakage, eta and phi to calculate uparallel corrections
  double ElecUParaCorr[2], ElecEnergyLeakage[2], ElecEta[2], ElecDetEta[2], 
         ElecPhi[2], ElecDetPhi[2], ElecPx[2], ElecPy[2];
  for(int i=0; i<2; i++) {
    ElecUParaCorr[i] = emobjs_smear[i].UParaCorr();
    ElecEnergyLeakage[i] = emobjs_smear[i].EnergyLeakage();
    ElecEta[i] = emobjs_smear[i].peta();
    ElecDetEta[i] = emobjs_smear[i].deteta();
    ElecPhi[i] = emobjs_smear[i].pphi();
    ElecDetPhi[i] = emobjs_smear[i].detphi();
    ElecPx[i] = emobjs_smear[i].ppx();
    ElecPy[i] = emobjs_smear[i].ppy();
  }
  
  // Z boson vector
  TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
  TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
  TVector2 z_vect = elec1_vect + elec2_vect;
  
  // divide events into smeared Z pT bins
  int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());
  if(bin<0) return; // out of range
  char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);

  // Z boson bisector of the two electrons
  TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();

  double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
  double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
  double raw_scale_HAD_bifurcate_Tau = _recoilsmear->scale_HAD_bifurcate_Tau();
  double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
  double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
  double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
  double raw_Reltrans_HAD_bifurcate_RelRespTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelRespTrans();
  double raw_Reltrans_HAD_bifurcate_RelResnTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelResnTrans();
  double raw_Reltrans_HAD_bifurcate_RelTauTrans  = _recoilsmear->Reltrans_HAD_bifurcate_RelTauTrans();
  double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
  double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
  double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();

  // recoil pT, phi at generator level
  double raw_recoil_pT = recoil_gen.Recoil();
  double raw_recoil_phi = recoil_gen.RecoilPhi();

  // do not change soft component smearing
  double recoilX_SoftComponent = _recoilsmear->recoilX_SoftComponent();
  double recoilY_SoftComponent = _recoilsmear->recoilY_SoftComponent();

  // get unfudged recoil's pT, phi and SET from Z->nunu model
  double znunu_recoil_pT = -1., znunu_recoil_phi = -1.;
  // recall the cached smeared hard recoil component from Z->nu+nu model
  // (it should be common not only for all 11x11 points but for the
  // "default" recoil parameters too!)
  _recoilsmear->GetLastHardRecoil_Method_B(NULL, NULL, &znunu_recoil_pT, &znunu_recoil_phi, NULL, NULL);
  double external_znunu_pt_resol = 1.0 - znunu_recoil_pT/raw_recoil_pT;
  double external_znunu_delta_phi = znunu_recoil_phi - raw_recoil_phi;
  double external_znunu_SET;
  double external_znunu_SET_expected;
  _recoilsmear->GetLastHardScalarEt_Method_B(&external_znunu_SET, &external_znunu_SET_expected, NULL);

//   ///////////////////// DEBUG //////////////////////////
//   //
//   cout << "++++ TEMPLATE BEFORE LOOP:" << endl
//        << "     Buffered hard SET(unfudged)=" << external_znunu_SET 
//        << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
//        << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//   //
//   ///////////////////// DEBUG //////////////////////////

  // now generate templates
  int ihist = 0;
  for(int iHAD=0; iHAD<=_Bins_HadronicResolutionBifurcateStudy; iHAD++) {
    for(int jHAD=0; jHAD<=_Bins_HadronicResolutionBifurcateStudy; jHAD++) {
      double Relsampling_HAD_bifurcate_A = _Relsampling_HAD_bifurcate_A_center + (iHAD-_Bins_HadronicResolutionBifurcateStudy/2) * _Relsampling_HAD_bifurcate_A_step;
      double Relsampling_HAD_bifurcate_B = _Relsampling_HAD_bifurcate_B_center + (jHAD-_Bins_HadronicResolutionBifurcateStudy/2) * _Relsampling_HAD_bifurcate_B_step;

      // smear hard component
      double smear_recoil_pT = 0., smear_recoil_phi = 0., smear_SET = 0.;
      _recoilsmear->SmearHardRecoil_Method_D(raw_recoil_pT,
                                             raw_recoil_phi,
                                             raw_scale_HAD_bifurcate_A,
                                             raw_scale_HAD_bifurcate_B,
                                             raw_scale_HAD_bifurcate_Tau,
                                             Relsampling_HAD_bifurcate_A,
                                             Relsampling_HAD_bifurcate_B,
                                             raw_Relconst_HAD_bifurcate,
					     raw_Reltrans_HAD_bifurcate_RelRespTrans,
					     raw_Reltrans_HAD_bifurcate_RelResnTrans,
					     raw_Reltrans_HAD_bifurcate_RelTauTrans, 
                                             raw_Relphi_HAD_bifurcate_A,
                                             raw_Relphi_HAD_bifurcate_B,
                                             raw_RelconstPhi_HAD_bifurcate,
                                             dummy,
                                             smear_recoil_pT,
                                             smear_recoil_phi,
					     smear_SET,
                                             external_znunu_pt_resol,  // use this ONE instead of random value
                                             external_znunu_delta_phi, // use this ONE instead of random value
					     external_znunu_SET,       // use this ONE instead of random value 
					     external_znunu_SET_expected, // use this ONE instead of random value
                                             true,               // ....skip hard recoil randomization
                                             false );            // and proceed with the fudging as usual....

      // add uparallel correction
      double sum_UparaCorrX = 0., sum_UparaCorrY = 0.;
      for(int ielec=0; ielec<2; ielec++) {
	sum_UparaCorrX += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* cos(ElecPhi[ielec]);
	sum_UparaCorrY += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* sin(ElecPhi[ielec]);
      }
      
      double recoilx_smear_template = smear_recoil_pT * cos(smear_recoil_phi);
      double recoily_smear_template = smear_recoil_pT * sin(smear_recoil_phi);
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last){ 
	if (_TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
	  _recoilsmear->ApplyTopBottomAsym(recoilx_smear_template, recoily_smear_template);   
	}
      }
      
      // final smeared recoil system (soft component added)
      double smear_recoil_X = recoilx_smear_template + recoilX_SoftComponent;
      double smear_recoil_Y = recoily_smear_template + recoilY_SoftComponent;
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
      }
      
    smear_recoil_X = smear_recoil_X - sum_UparaCorrX;
    smear_recoil_Y = smear_recoil_Y - sum_UparaCorrY;
    
    //
    // include photons in the smeared recoil system
    // the photon response is described in EMSmear::SmearPhotonEnergy
    //
    for(int i=0; i<emobjs_smear.size(); i++) {
      if (i > 1){
	if (!_ZsimuFSRcracks) {
	  smear_recoil_X  += emobjs_smear[i].ppx();
	  smear_recoil_Y += emobjs_smear[i].ppy();
	} else {
	  float deteta=emobjs_smear[i].deteta();
	  float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	  if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
	    smear_recoil_X += emobjs_smear[i].ppx();
	    smear_recoil_Y += emobjs_smear[i].ppy();
	  }
	}
      }
    }
    
    // recoil after all corrections
    PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);
    if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
      _recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
      recoil_smear.SetRecoil(smear_recoil_X, smear_recoil_Y);
    }
    
      // met after corrections for the two highest pT electrons
      double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
      double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
      PMCSMet met_smear(metX_component, metY_component);

      // skip randomization of U|| efficiency and SET
      if( passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
			   NULL, NULL, false,
			   external_upara_rnd1, external_upara_rnd2,
			   external_SET_rnd) ) {
	// now we can calculate eta imbalance
	TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);
	double eta_imbalance = (z_vect + recoil_vect) * bisector_vect;
	char sn[20]; sprintf(sn, "%d", ihist);
	_histos.Fill1D((prefix+"hZcandEtaImBalance_bin_"+pee_bin_sn+"_"+sn).c_str(), 
		       eta_imbalance, evtweight);
      }
//       ///////////////////// DEBUG //////////////////////////
//       //
//       double dummyset;
//       _recoilsmear->GetLastHardScalarEt_Method_B(&dummyset, NULL, NULL);
//       cout << "++++ TEMPLATE INSIDE LOOP (iHAD=" << iHAD
// 	   << ", jHAD=" << jHAD << "):" << endl 
// 	   << "     Buffered hard SET (unfudged)=" << dummyset
// 	   << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
// 	   << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//       //
//       ///////////////////// DEBUG //////////////////////////

      ihist ++;
    }// iHAD
  }// jHAD

  // set back old smearing parameters
  _recoilsmear->SetHardSmearingParameters_MethodB(raw_scale_HAD_bifurcate_A, 
						  raw_scale_HAD_bifurcate_B, 
						  raw_scale_HAD_bifurcate_Tau, 
	                                          raw_Relsampling_HAD_bifurcate_A, 
						  raw_Relsampling_HAD_bifurcate_B, 
						  raw_Relconst_HAD_bifurcate,
						  raw_Reltrans_HAD_bifurcate_RelRespTrans,
						  raw_Reltrans_HAD_bifurcate_RelResnTrans,
						  raw_Reltrans_HAD_bifurcate_RelTauTrans,
                                                  raw_Relphi_HAD_bifurcate_A, 
						  raw_Relphi_HAD_bifurcate_B, 
						  raw_RelconstPhi_HAD_bifurcate);
}

// determine hadronic momentum resolution for bifurcate method (for hard and soft components)
void ZAnalysis::HadronicMomentumResolution2BifurcateStudy(vector<PMCSEMObj> &emobjs_smear, 
							  PMCSRecoil &recoil_gen, 
							  PMCSVtx &vtx_gen,
							  TRandom3 *dummy, 
							  std::string prefix, 
							  double evtweight,
							  double *external_upara_rnd1,
							  double *external_upara_rnd2,
							  double *external_SET_rnd) {
  // skip if there are less than 2 smeared EM objects in an event
  if( emobjs_smear.size()<2 ) return;

  // get two electron uparaCorr, energyLeakage, eta and phi to calculate uparallel corrections
  double ElecUParaCorr[2], ElecEnergyLeakage[2], ElecEta[2], ElecDetEta[2], 
         ElecPhi[2], ElecDetPhi[2], ElecPx[2], ElecPy[2];
  for(int i=0; i<2; i++) {
    ElecUParaCorr[i] = emobjs_smear[i].UParaCorr();
    ElecEnergyLeakage[i] = emobjs_smear[i].EnergyLeakage();
    ElecEta[i] = emobjs_smear[i].peta();
    ElecDetEta[i] = emobjs_smear[i].deteta();
    ElecPhi[i] = emobjs_smear[i].pphi();
    ElecDetPhi[i] = emobjs_smear[i].detphi();
    ElecPx[i] = emobjs_smear[i].ppx();
    ElecPy[i] = emobjs_smear[i].ppy();
  }

  // Z boson vector
  TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
  TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
  TVector2 z_vect = elec1_vect + elec2_vect;
  
  // divide events into smeared Z pT bins
  int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());
  if(bin<0) return; // out of range
  char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);

  // Z boson bisector of the two electrons
  TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();

  double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
  double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
  double raw_scale_HAD_bifurcate_Tau = _recoilsmear->scale_HAD_bifurcate_Tau();
  double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
  double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
  double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
  double raw_Reltrans_HAD_bifurcate_RelRespTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelRespTrans();
  double raw_Reltrans_HAD_bifurcate_RelResnTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelResnTrans();
  double raw_Reltrans_HAD_bifurcate_RelTauTrans  = _recoilsmear->Reltrans_HAD_bifurcate_RelTauTrans();
  double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
  double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
  double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();
  double raw_alpha_mb = _recoilsmear->alpha_mb();
  double raw_alpha_zb = _recoilsmear->alpha_zb();

  // recoil pT, phi at generator level
  double raw_recoil_pT = recoil_gen.Recoil();
  double raw_recoil_phi = recoil_gen.RecoilPhi();

  // get unfudged recoil's pT, phi and SET from Z->nunu model
  double znunu_recoil_pT = -1., znunu_recoil_phi = -1.;
  // recall the cached smeared hard recoil component from Z->nu+nu model
  // (it should be common not only for all 11x11 points but for the
  // "default" recoil parameters too!)
  _recoilsmear->GetLastHardRecoil_Method_B(NULL, NULL, &znunu_recoil_pT, &znunu_recoil_phi, NULL, NULL);
  double external_znunu_pt_resol = 1.0 - znunu_recoil_pT/raw_recoil_pT;
  double external_znunu_delta_phi = znunu_recoil_phi - raw_recoil_phi;
  double external_znunu_SET;
  double external_znunu_SET_expected;
  _recoilsmear->GetLastHardScalarEt_Method_B(&external_znunu_SET, &external_znunu_SET_expected, NULL);

//   ///////////////////// DEBUG //////////////////////////
//   //
//   cout << "++++ TEMPLATE BEFORE LOOP:" << endl
//        << "     Buffered hard SET(unfudged)=" << external_znunu_SET 
//        << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
//        << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//   //
//   ///////////////////// DEBUG //////////////////////////

  // now generate templates
  int ihist = 0;
  for(int iHAD=0; iHAD<=_Bins_HadronicResolution2BifurcateStudy; iHAD++) {
    for(int jHAD=0; jHAD<=_Bins_HadronicResolution2BifurcateStudy; jHAD++) {
      double Relsampling_HAD_bifurcate_A = _Relsampling_HAD_bifurcate2_A_center + (iHAD-_Bins_HadronicResolution2BifurcateStudy/2) * _Relsampling_HAD_bifurcate2_A_step;
      double alpha_mb = _alpha_mb2_center + (jHAD-_Bins_HadronicResolution2BifurcateStudy/2) * _alpha_mb2_step;

      // smear hard component
      double smear_recoil_pT = 0., smear_recoil_phi = 0., smear_SET = 0.;
      _recoilsmear->SmearHardRecoil_Method_D(raw_recoil_pT,
                                             raw_recoil_phi,
                                             raw_scale_HAD_bifurcate_A,
                                             raw_scale_HAD_bifurcate_B,
                                             raw_scale_HAD_bifurcate_Tau,
                                             Relsampling_HAD_bifurcate_A,
                                             raw_Relsampling_HAD_bifurcate_B,
                                             raw_Relconst_HAD_bifurcate,
					     raw_Reltrans_HAD_bifurcate_RelRespTrans,
					     raw_Reltrans_HAD_bifurcate_RelResnTrans,
					     raw_Reltrans_HAD_bifurcate_RelTauTrans,
                                             raw_Relphi_HAD_bifurcate_A,
                                             raw_Relphi_HAD_bifurcate_B,
                                             raw_RelconstPhi_HAD_bifurcate,
                                             dummy,
                                             smear_recoil_pT,
                                             smear_recoil_phi,
					     smear_SET,
                                             external_znunu_pt_resol,  // use this ONE instead of random value
                                             external_znunu_delta_phi, // use this ONE instead of random value
					     external_znunu_SET,       // use this ONE instead of random value 
					     external_znunu_SET_expected, // use this ONE instead of random value
                                             true,               // ....skip hard recoil randomization
                                             false );            // and proceed with the fudging as usual....

      // add uparallel correction
      
      double sum_UparaCorrX = 0., sum_UparaCorrY = 0.;
      for(int ielec=0; ielec<2; ielec++) {
	sum_UparaCorrX += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* cos(ElecPhi[ielec]);
	sum_UparaCorrY += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* sin(ElecPhi[ielec]);
      }

      // change soft component smearing
      double smear_Metx_From_MB = 0., smear_Mety_From_MB = 0., smear_Metx_From_ZB = 0., smear_Mety_From_ZB = 0.;
      double smear_Metx = 0., smear_Mety = 0.;
      _recoilsmear->SmearSoftRecoil_Method_D(alpha_mb, raw_alpha_zb, dummy,
                                             smear_Metx_From_MB, smear_Mety_From_MB,
                                             smear_Metx_From_ZB, smear_Mety_From_ZB,
                                             smear_Metx, smear_Mety);
      
      
      // final smeared recoil system (soft component added)
      double recoilx_smear_template = smear_recoil_pT * cos(smear_recoil_phi);
      double recoily_smear_template = smear_recoil_pT * sin(smear_recoil_phi);
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last){ 
	if (_TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
	  _recoilsmear->ApplyTopBottomAsym(recoilx_smear_template, recoily_smear_template);   
	}
	else if (!_TBPhi_response_Hard_Only && _TBPhi_response_Soft_Only){
	  _recoilsmear->ApplyTopBottomAsym(smear_Metx, smear_Mety);   
	}
      }
      
      double smear_recoil_X = recoilx_smear_template + smear_Metx; 
      double smear_recoil_Y = recoily_smear_template + smear_Mety;
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
      }
      smear_recoil_X = smear_recoil_X - sum_UparaCorrX;
      smear_recoil_Y = smear_recoil_Y - sum_UparaCorrY;

      //
      // include photons in the smeared recoil system
      // the photon response is described in EMSmear::SmearPhotonEnergy
      //
      for(int i=0; i<emobjs_smear.size(); i++) {
        if (i > 1){
	  if (!_ZsimuFSRcracks) {
	    smear_recoil_X  += emobjs_smear[i].ppx();
	    smear_recoil_Y += emobjs_smear[i].ppy();
	  } else {
	    float deteta=emobjs_smear[i].deteta();
	    float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	    if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
	      smear_recoil_X += emobjs_smear[i].ppx();
	      smear_recoil_Y += emobjs_smear[i].ppy();
	    }
	  }
	}
      }
      
      // recoil after all corrections
      PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
	recoil_smear.SetRecoil(smear_recoil_X, smear_recoil_Y);
      }
      
      // met after corrections for the two highest pT electrons
      double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
      double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
      PMCSMet met_smear(metX_component, metY_component);

      // skip randomization of U|| efficiency and SET
      if( passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
                           NULL, NULL, false,
                           external_upara_rnd1, external_upara_rnd2,
			   external_SET_rnd) ) {
	// now we can calculate eta imbalance
	TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);
	double eta_imbalance = (z_vect + recoil_vect) * bisector_vect;
	char sn[20]; sprintf(sn, "%d", ihist);
	_histos.Fill1D((prefix+"hZcandEtaImBalance_bin_"+pee_bin_sn+"_"+sn).c_str(), 
		       eta_imbalance, evtweight);
      }
//       ///////////////////// DEBUG //////////////////////////
//       //
//       double dummyset;
//       _recoilsmear->GetLastHardScalarEt_Method_B(&dummyset, NULL, NULL);
//       cout << "++++ TEMPLATE INSIDE LOOP (iHAD=" << iHAD
// 	   << ", jHAD=" << jHAD << "):" << endl 
// 	   << "     Buffered hard SET (unfudged)=" << dummyset
// 	   << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
// 	   << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//       //
//       ///////////////////// DEBUG //////////////////////////
      
      ihist ++;
    }// iHAD
  }// jHAD

  // set back old smearing parameters
  _recoilsmear->SetHardSmearingParameters_MethodB(raw_scale_HAD_bifurcate_A, 
						  raw_scale_HAD_bifurcate_B, 
						  raw_scale_HAD_bifurcate_Tau, 
	                                          raw_Relsampling_HAD_bifurcate_A, 
						  raw_Relsampling_HAD_bifurcate_B, 
						  raw_Relconst_HAD_bifurcate,
						  raw_Reltrans_HAD_bifurcate_RelRespTrans,
						  raw_Reltrans_HAD_bifurcate_RelResnTrans,
						  raw_Reltrans_HAD_bifurcate_RelTauTrans,
                                                  raw_Relphi_HAD_bifurcate_A, 
						  raw_Relphi_HAD_bifurcate_B, 
						  raw_RelconstPhi_HAD_bifurcate);
  _recoilsmear->SetSoftSmearingParameters_MethodD(raw_alpha_mb, 
						  raw_alpha_zb);

}

// determine hadronic momentum resolution for bifurcate method (for hard and soft components)
void ZAnalysis::HadronicMomentumResolution3BifurcateStudy(vector<PMCSEMObj> &emobjs_smear, 
							  PMCSRecoil &recoil_gen, 
							  PMCSVtx &vtx_gen,
							  TRandom3 *dummy, 
							  std::string prefix, 
							  double evtweight,
							  double *external_upara_rnd1,
							  double *external_upara_rnd2,
							  double *external_SET_rnd) {
  // skip if there are less than 2 smeared EM objects in an event
  if( emobjs_smear.size()<2 ) return;

  // get two electron uparaCorr, energyLeakage, eta and phi to calculate uparallel corrections
  double ElecUParaCorr[2], ElecEnergyLeakage[2], ElecEta[2], ElecDetEta[2], 
         ElecPhi[2], ElecDetPhi[2], ElecPx[2], ElecPy[2];
  for(int i=0; i<2; i++) {
    ElecUParaCorr[i] = emobjs_smear[i].UParaCorr();
    ElecEnergyLeakage[i] = emobjs_smear[i].EnergyLeakage();
    ElecEta[i] = emobjs_smear[i].peta();
    ElecDetEta[i] = emobjs_smear[i].deteta();
    ElecPhi[i] = emobjs_smear[i].pphi();
    ElecDetPhi[i] = emobjs_smear[i].detphi();
    ElecPx[i] = emobjs_smear[i].ppx();
    ElecPy[i] = emobjs_smear[i].ppy();
  }

  // Z boson vector
  TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
  TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
  TVector2 z_vect = elec1_vect + elec2_vect;
  
  // divide events into smeared Z pT bins
  int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());
  if(bin<0) return; // out of range
  char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);

  // Z boson bisector of the two electrons
  TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();

  double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
  double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
  double raw_scale_HAD_bifurcate_Tau = _recoilsmear->scale_HAD_bifurcate_Tau();
  double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
  double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
  double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
  double raw_Reltrans_HAD_bifurcate_RelRespTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelRespTrans();
  double raw_Reltrans_HAD_bifurcate_RelResnTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelResnTrans();
  double raw_Reltrans_HAD_bifurcate_RelTauTrans  = _recoilsmear->Reltrans_HAD_bifurcate_RelTauTrans();
  double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
  double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
  double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();
  double raw_alpha_mb = _recoilsmear->alpha_mb();
  double raw_alpha_zb = _recoilsmear->alpha_zb();

  // recoil pT, phi at generator level
  double raw_recoil_pT = recoil_gen.Recoil();
  double raw_recoil_phi = recoil_gen.RecoilPhi();

  // get unfudged recoil's pT, phi and SET from Z->nunu model
  double znunu_recoil_pT = -1., znunu_recoil_phi = -1.;
  // recall the cached smeared hard recoil component from Z->nu+nu model
  // (it should be common not only for all 11x11 points but for the
  // "default" recoil parameters too!)
  _recoilsmear->GetLastHardRecoil_Method_B(NULL, NULL, &znunu_recoil_pT, &znunu_recoil_phi, NULL, NULL);
  double external_znunu_pt_resol = 1.0 - znunu_recoil_pT/raw_recoil_pT;
  double external_znunu_delta_phi = znunu_recoil_phi - raw_recoil_phi;
  double external_znunu_SET;
  double external_znunu_SET_expected;
  _recoilsmear->GetLastHardScalarEt_Method_B(&external_znunu_SET, &external_znunu_SET_expected, NULL);

  // now generate templates
  int ihist = 0;
  for(int iHAD=0; iHAD<=_Bins_HadronicResolution3BifurcateStudy; iHAD++) {
    for(int jHAD=0; jHAD<=_Bins_HadronicResolution3BifurcateStudy; jHAD++) {
      for(int kHAD=0; kHAD<=_Bins_HadronicResolution3BifurcateStudy; kHAD++) {

	double Relsampling_HAD_bifurcate_A = _Relsampling_HAD_bifurcate3_A_center + (iHAD-_Bins_HadronicResolution3BifurcateStudy/2) * _Relsampling_HAD_bifurcate3_A_step;
	double Relsampling_HAD_bifurcate_B = _Relsampling_HAD_bifurcate3_B_center + (jHAD-_Bins_HadronicResolution3BifurcateStudy/2) * _Relsampling_HAD_bifurcate3_B_step;
	double alpha_mb = _alpha_mb3_center + (kHAD-_Bins_HadronicResolution3BifurcateStudy/2) * _alpha_mb3_step;

	// smear hard component
	double smear_recoil_pT = 0., smear_recoil_phi = 0., smear_SET = 0.;
	_recoilsmear->SmearHardRecoil_Method_D(raw_recoil_pT,
					       raw_recoil_phi,
					       raw_scale_HAD_bifurcate_A,
					       raw_scale_HAD_bifurcate_B,
					       raw_scale_HAD_bifurcate_Tau,
					       Relsampling_HAD_bifurcate_A,
					       Relsampling_HAD_bifurcate_B,
					       raw_Relconst_HAD_bifurcate,
					       raw_Reltrans_HAD_bifurcate_RelRespTrans,
					       raw_Reltrans_HAD_bifurcate_RelResnTrans,
					       raw_Reltrans_HAD_bifurcate_RelTauTrans,
					       raw_Relphi_HAD_bifurcate_A,
					       raw_Relphi_HAD_bifurcate_B,
					       raw_RelconstPhi_HAD_bifurcate,
					       dummy,
					       smear_recoil_pT,
					       smear_recoil_phi,
					       smear_SET,
					       external_znunu_pt_resol,  // use this ONE instead of random value
					       external_znunu_delta_phi, // use this ONE instead of random value
					       external_znunu_SET,       // use this ONE instead of random value 
					       external_znunu_SET_expected, // use this ONE instead of random value
					       true,               // ....skip hard recoil randomization
					       false );            // and proceed with the fudging as usual....
	
	// add uparallel correction
	double sum_UparaCorrX = 0., sum_UparaCorrY = 0.;
	for(int ielec=0; ielec<2; ielec++) {
	  sum_UparaCorrX += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* cos(ElecPhi[ielec]);
	  sum_UparaCorrY += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* sin(ElecPhi[ielec]);
	}
	
	// change soft component smearing
	double smear_Metx_From_MB = 0., smear_Mety_From_MB = 0., smear_Metx_From_ZB = 0., smear_Mety_From_ZB = 0.;
	double smear_Metx = 0., smear_Mety = 0.;
	_recoilsmear->SmearSoftRecoil_Method_D(alpha_mb, raw_alpha_zb, dummy,
					       smear_Metx_From_MB, smear_Mety_From_MB,
					       smear_Metx_From_ZB, smear_Mety_From_ZB,
					       smear_Metx, smear_Mety);
	
	
	// final smeared recoil system (soft component added)

	
	double recoilx_smear_template = smear_recoil_pT * cos(smear_recoil_phi);
	double recoily_smear_template = smear_recoil_pT * sin(smear_recoil_phi);
	if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last){ 
	  if (_TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
	    _recoilsmear->ApplyTopBottomAsym(recoilx_smear_template, recoily_smear_template);   
	  }
	  else if (!_TBPhi_response_Hard_Only && _TBPhi_response_Soft_Only){
	    _recoilsmear->ApplyTopBottomAsym(smear_Metx, smear_Mety);   
	  }
	}




	double smear_recoil_X = recoilx_smear_template + smear_Metx;
	double smear_recoil_Y = recoily_smear_template + smear_Mety;
	if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
	  _recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
	}
	
	smear_recoil_X = smear_recoil_X - sum_UparaCorrX;
	smear_recoil_Y = smear_recoil_Y - sum_UparaCorrY;
	
	//
	// include photons in the smeared recoil system
	// the photon response is described in EMSmear::SmearPhotonEnergy
	//
	for(int i=0; i<emobjs_smear.size(); i++) {
	  if (i > 1){
	    if (!_ZsimuFSRcracks) {
	      smear_recoil_X  += emobjs_smear[i].ppx();
	      smear_recoil_Y += emobjs_smear[i].ppy();
	    } else {
	      float deteta=emobjs_smear[i].deteta();
	      float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	      if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
		smear_recoil_X += emobjs_smear[i].ppx();
		smear_recoil_Y += emobjs_smear[i].ppy();
	      }
	    }
	  }
	}
	
	// recoil after all corrections
	PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);
	if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
	  _recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
	  recoil_smear.SetRecoil(smear_recoil_X, smear_recoil_Y);
	}
	
	
	// met after corrections for the two highest pT electrons
	double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
	double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
	PMCSMet met_smear(metX_component, metY_component);
	
	// skip randomization of U|| efficiency and SET
	if( passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
			     NULL, NULL, false,
			     external_upara_rnd1, external_upara_rnd2,
			     external_SET_rnd) ) {
	  // now we can calculate eta imbalance
	  TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);
	  //  zcand.Eta_ImBalance()
	  double eta_imbalance = (z_vect + recoil_vect) * bisector_vect;
	  char sn[20]; sprintf(sn, "%d", ihist);
	  _histos.Fill1D((prefix+"hZcandEtaImBalance_bin_"+pee_bin_sn+"_"+sn).c_str(), 
			 eta_imbalance, evtweight);
	}

	ihist ++;
      }// iHAD
    }// jHAD
  } // kHAD

  // set back old smearing parameters
  _recoilsmear->SetHardSmearingParameters_MethodB(raw_scale_HAD_bifurcate_A, 
						  raw_scale_HAD_bifurcate_B, 
						  raw_scale_HAD_bifurcate_Tau, 
	                                          raw_Relsampling_HAD_bifurcate_A, 
						  raw_Relsampling_HAD_bifurcate_B, 
						  raw_Relconst_HAD_bifurcate,
						  raw_Reltrans_HAD_bifurcate_RelRespTrans,
						  raw_Reltrans_HAD_bifurcate_RelResnTrans,
						  raw_Reltrans_HAD_bifurcate_RelTauTrans,
                                                  raw_Relphi_HAD_bifurcate_A, 
						  raw_Relphi_HAD_bifurcate_B, 
						  raw_RelconstPhi_HAD_bifurcate);
  _recoilsmear->SetSoftSmearingParameters_MethodD(raw_alpha_mb, 
						  raw_alpha_zb);

}

// determine hadronic phi smearing parameters for bifurcate method
void ZAnalysis::HadronicPhiSmearingBifurcateStudy(vector<PMCSEMObj> &emobjs_smear, 
						  PMCSRecoil &recoil_gen, 
						  PMCSVtx &vtx_gen,
						  TRandom3 *dummy, 
						  std::string prefix, 
						  double evtweight,
						  double *external_upara_rnd1,
						  double *external_upara_rnd2,
						  double *external_SET_rnd) {
  // skip if there are less than 2 smeared EM objects in an event
  if( emobjs_smear.size()<2 ) return;

  // get two electron uparaCorr, energyLeakage, eta and phi to calculate uparallel corrections
  double ElecUParaCorr[2], ElecEnergyLeakage[2], ElecEta[2], ElecDetEta[2], 
         ElecPhi[2], ElecDetPhi[2], ElecPx[2], ElecPy[2];
  for(int i=0; i<2; i++) {
    ElecUParaCorr[i] = emobjs_smear[i].UParaCorr();
    ElecEnergyLeakage[i] = emobjs_smear[i].EnergyLeakage();
    ElecEta[i] = emobjs_smear[i].peta();
    ElecDetEta[i] = emobjs_smear[i].deteta();
    ElecPhi[i] = emobjs_smear[i].pphi();
    ElecDetPhi[i] = emobjs_smear[i].detphi();
    ElecPx[i] = emobjs_smear[i].ppx();
    ElecPy[i] = emobjs_smear[i].ppy();
  }

  // Z boson vector
  TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
  TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
  TVector2 z_vect = elec1_vect + elec2_vect;
  
  // divide events into smeared Z pT bins
  int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());
  if(bin<0) return; // out of range
  char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);

  // Z boson bisector of the two electrons (not needed for PHI smearinfg studies!)
  // TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();

  double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
  double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
  double raw_scale_HAD_bifurcate_Tau = _recoilsmear->scale_HAD_bifurcate_Tau();
  double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
  double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
  double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
  double raw_Reltrans_HAD_bifurcate_RelRespTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelRespTrans();
  double raw_Reltrans_HAD_bifurcate_RelResnTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelResnTrans();
  double raw_Reltrans_HAD_bifurcate_RelTauTrans  = _recoilsmear->Reltrans_HAD_bifurcate_RelTauTrans();
  double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
  double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
  double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();

  // recoil pT, phi at generator level
  double raw_recoil_pT = recoil_gen.Recoil();
  double raw_recoil_phi = recoil_gen.RecoilPhi();
  
  // do not change soft component smearing
  double recoilX_SoftComponent = _recoilsmear->recoilX_SoftComponent();
  double recoilY_SoftComponent = _recoilsmear->recoilY_SoftComponent();

  // get unfudged recoil's pT, phi and SET from Z->nunu model
  double znunu_recoil_pT = -1., znunu_recoil_phi = -1.;
  // recall the cached smeared hard recoil component from Z->nu+nu model
  // (it should be common not only for all 11x11 points but for the
  // "default" recoil parameters too!)
  _recoilsmear->GetLastHardRecoil_Method_B(NULL, NULL, &znunu_recoil_pT, &znunu_recoil_phi, NULL, NULL);
  double external_znunu_pt_resol = 1.0 - znunu_recoil_pT/raw_recoil_pT;
  double external_znunu_delta_phi = znunu_recoil_phi - raw_recoil_phi;
  double external_znunu_SET;
  double external_znunu_SET_expected;
  _recoilsmear->GetLastHardScalarEt_Method_B(&external_znunu_SET, &external_znunu_SET_expected, NULL);

//   ///////////////////// DEBUG //////////////////////////
//   //
//   cout << "++++ TEMPLATE BEFORE LOOP:" << endl
//        << "     Buffered hard SET(unfudged)=" << external_znunu_SET 
//        << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
//        << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//   //
//   ///////////////////// DEBUG //////////////////////////

  // now generate templates
  int ihist = 0;
  for(int iHAD_PhiA=0; iHAD_PhiA<=_Bins_HadronicPhiSmearingBifurcateStudy; iHAD_PhiA++) {
    for(int jHAD_PhiB=0; jHAD_PhiB<=_Bins_HadronicPhiSmearingBifurcateStudy; jHAD_PhiB++) {
      double Relphi_HAD_bifurcate_A = _Relphi_HAD_bifurcate_A_center + (iHAD_PhiA-_Bins_HadronicPhiSmearingBifurcateStudy/2) * _Relphi_HAD_bifurcate_A_step;
      double Relphi_HAD_bifurcate_B = _Relphi_HAD_bifurcate_B_center + (jHAD_PhiB-_Bins_HadronicPhiSmearingBifurcateStudy/2) * _Relphi_HAD_bifurcate_B_step;

      // smear hard component
      double smear_recoil_pT = 0., smear_recoil_phi = 0., smear_SET = 0.;
      _recoilsmear->SmearHardRecoil_Method_D(raw_recoil_pT,
                                             raw_recoil_phi,
                                             raw_scale_HAD_bifurcate_A,
                                             raw_scale_HAD_bifurcate_B,
                                             raw_scale_HAD_bifurcate_Tau,
                                             raw_Relsampling_HAD_bifurcate_A,
                                             raw_Relsampling_HAD_bifurcate_B,
                                             raw_Relconst_HAD_bifurcate,
					     raw_Reltrans_HAD_bifurcate_RelRespTrans,
					     raw_Reltrans_HAD_bifurcate_RelResnTrans,
					     raw_Reltrans_HAD_bifurcate_RelTauTrans,
                                             Relphi_HAD_bifurcate_A,
                                             Relphi_HAD_bifurcate_B,
                                             raw_RelconstPhi_HAD_bifurcate,
                                             dummy,
                                             smear_recoil_pT,
                                             smear_recoil_phi,
					     smear_SET,
                                             external_znunu_pt_resol,  // use this ONE instead of random value
                                             external_znunu_delta_phi, // use this ONE instead of random value
					     external_znunu_SET,       // use this ONE instead of random value 
					     external_znunu_SET_expected, // use this ONE instead of random value
                                             true,               // ....skip hard recoil randomization
                                             false );            // and proceed with the fudging as usual....

      // add uparallel correction
      double sum_UparaCorrX = 0., sum_UparaCorrY = 0.;
      for(int ielec=0; ielec<2; ielec++) {
	sum_UparaCorrX += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* cos(ElecPhi[ielec]);
	sum_UparaCorrY += (ElecUParaCorr[ielec] - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* sin(ElecPhi[ielec]);
      }
      double recoilx_smear_template = smear_recoil_pT * cos(smear_recoil_phi);
      double recoily_smear_template = smear_recoil_pT * sin(smear_recoil_phi);
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last){ 
	if (_TBPhi_response_Hard_Only && !_TBPhi_response_Soft_Only){
	  _recoilsmear->ApplyTopBottomAsym(recoilx_smear_template, recoily_smear_template);   
	}
      }
      // final smeared recoil system (soft component added)
      double smear_recoil_X = recoilx_smear_template + recoilX_SoftComponent;
      double smear_recoil_Y = recoily_smear_template + recoilY_SoftComponent;
      
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && !_Top_Bottom_Apply_Last && !_TBPhi_response_Hard_Only &&!_TBPhi_response_Soft_Only ){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
      }
      
      smear_recoil_X = smear_recoil_X - sum_UparaCorrX;
      smear_recoil_Y = smear_recoil_Y - sum_UparaCorrY;
      for(int i=0; i<emobjs_smear.size(); i++) {
	if (i > 1){
	  if (!_ZsimuFSRcracks) {
	    smear_recoil_X  += emobjs_smear[i].ppx();
	    smear_recoil_Y += emobjs_smear[i].ppy();
	  } else {
	    float deteta=emobjs_smear[i].deteta();
	    float phimod=emobjs_smear[i].PhiMod(_ApplyTrkPhiModCut);
	    if (((fabs(deteta)<1.1)||(fabs(deteta>1.55)))&&((phimod>_ZsimuFSRcracksWidth)&&(phimod<(1-_ZsimuFSRcracksWidth)))) {
	      smear_recoil_X += emobjs_smear[i].ppx();
	      smear_recoil_Y += emobjs_smear[i].ppy();
	    }
	  }
	}
      }
      
      // recoil after all corrections
      PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);
      if (_Top_Bottom_Effect_Correction && _TB_Correction_Option==1 && _Top_Bottom_Apply_Last){
	_recoilsmear->ApplyTopBottomAsym(smear_recoil_X, smear_recoil_Y);
	recoil_smear.SetRecoil(smear_recoil_X, smear_recoil_Y);
      }
      
      // met after corrections for the two highest pT electrons
      double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
      double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
      PMCSMet met_smear(metX_component, metY_component);
      
      // skip randomization of U|| efficiency and SET      
      if( passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
                           NULL, NULL, false,
                           external_upara_rnd1, external_upara_rnd2,
			   external_SET_rnd) ) {
	// calculate delta phi between Z and the recoil
	TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);
	double deltaphi_Z_recoil = z_vect.DeltaPhi(recoil_vect);
	char sn[20]; sprintf(sn, "%d", ihist);
	_histos.Fill1D((prefix+"hZcandDeltaPhi_Z_Recoil_bin_"+pee_bin_sn+"_"+sn).c_str(), 
		       fabs(deltaphi_Z_recoil), evtweight);
      }
//       ///////////////////// DEBUG //////////////////////////
//       //
//       double dummyset;
//       _recoilsmear->GetLastHardScalarEt_Method_B(&dummyset, NULL, NULL);
//       cout << "++++ TEMPLATE INSIDE LOOP (iHAD_PhiA=" << iHAD_PhiA
// 	   << ", jHAD_PhiB=" << jHAD_PhiB << "):" << endl 
// 	   << "     Buffered hard SET (unfudged)=" << dummyset
// 	   << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
// 	   << ", calc. total SET=" << _recoilsmear->scalarEt() << endl;
//       //
//       ///////////////////// DEBUG //////////////////////////

      ihist ++;
    }// iHAD_PhiA
  }// jHAD_PhiB

  // set back old smearing parameters
  _recoilsmear->SetHardSmearingParameters_MethodB(raw_scale_HAD_bifurcate_A, 
						  raw_scale_HAD_bifurcate_B, 
						  raw_scale_HAD_bifurcate_Tau, 
	                                          raw_Relsampling_HAD_bifurcate_A, 
						  raw_Relsampling_HAD_bifurcate_B, 
						  raw_Relconst_HAD_bifurcate,
						  raw_Reltrans_HAD_bifurcate_RelRespTrans,
						  raw_Reltrans_HAD_bifurcate_RelResnTrans,
						  raw_Reltrans_HAD_bifurcate_RelTauTrans,
                                                  raw_Relphi_HAD_bifurcate_A, 
						  raw_Relphi_HAD_bifurcate_B, 
						  raw_RelconstPhi_HAD_bifurcate);
}

ZAnalysis::~ZAnalysis () {
}

void ZAnalysis::jobSummary(TRandom3 *dummy, long numEvents) {
  cout << "=================================================================="<<endl;
  cout << "ZAnalysis number of events processed = " << _ntotal << endl; 
  cout << "=================================================================="<<endl;

  if (_makeROOTfile_for_ZFIT || _makegenROOTfile_for_ZFIT) {
    cout << "Writing Z fit file Zfittree.root" << endl;
    Zfitfile->Write();
  }  
  if (_createRootTree2){
    cout << "Writing Z Tree2 file ZTree.root" << endl;
    _roottupleFile2->Write();
  }
  if (_makeASCIIfile_for_detector) _theASCIIfile->close();
  if (_make_recoil_file) _RecoilPtASCIIfile->close();
  if (_make_recoil_file) {
    if( use_old_ascii_files )
      _RecoilPtASCIIfile->close();
    else
      _RecoilFile->Write();
  }

  if(_MakeEleakTable){
    double LeakMean=0;
    std::fstream* LeakTableFile = new std::fstream("LeakTable.txt",std::ios::out);

    for(int i=0; i<_NleakBins; i++){

      if(_LeakCount[i]<200) cout<<"Low LeakStats in bin "<<i<<" Num evts is: "<<_LeakCount[i]<<endl;

      if(_LeakCount[i]!=0) LeakMean = _LeakSum[i]/_LeakCount[i];
      (*LeakTableFile) << i <<" "<< LeakMean<<endl;
    }
    
    double overallLeakmean;
    if(_overallLeakCount!=0) overallLeakmean=_overallLeakSum/(double)_overallLeakCount;
     cout<<"Mean electron leakage: "<<overallLeakmean<<endl;

    LeakTableFile->close();
  }

  // RCLSA: Calls function to write out recoil template tree
  if(_ZHadronicRecoilBifurcateStudy) {
    ZHadronicRecoilBifurcateProcess();
    cout << "Pre-processing the hadronic recoil fit tree" << endl;
  }
  if(_TransZHadronicRecoilBifurcateStudy) {
    TransZHadronicRecoilBifurcateProcess();
    cout << "Pre-processing the hadronic recoil fit tree" << endl;
  }

  if (_HadronicMomentum_AllAtOnce_BifurcateStudy) {    // close event buffer file
    if(!_Zminuit_Skip_Event_Preselection) {
      cout << "Writing preselected Z events to file " << _Zminuit_EventBuffer_FileName << endl;
      if(_Zminuit_EventBuffer_File) fclose(_Zminuit_EventBuffer_File);
    }

    // begin reprocessing event buffer file
    // analyze up to 'numEvents' buffered events upon request
    // numEvents=0 means all buffered events
    if(!_Zminuit_Skip_Event_Reprocessing) {
      //      MINUIT_reprocess(_Zminuit_EventBuffer_Nevts, dummy);
      MINUIT_reprocess(numEvents, dummy);
    }
  }
  _histos.save(_zeefilename);
  cout<<"Histograms saved"<<endl;

  if (_FillZBRunNumTree){
    _ZBRunNumFile->cd();
    _ZBRunNumTree->Write();
    _ZBRunNumFile->Close();
  }

}


// RCLSA: Writes out the recoil template tree
void ZAnalysis::ZHadronicRecoilBifurcateProcess() {
    
    ZRecoilBifurcateFile = new TFile(_ZRecoilBifurcateFile,"RECREATE");
    ZRecoilBifurcateOutputTree = new TTree("ZRecoilBifurcateOutputTree","Recoil Study Output");
    ZRecoilBifurcateOutputTree->Branch("zpt",&ZRecoilBifurcateOutputData.zpt,"zpt/I");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_mean",&ZRecoilBifurcateOutputData.eta_imbalance_mean,"eta_imbalance_mean/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_rms",&ZRecoilBifurcateOutputData.eta_imbalance_rms,"eta_imbalance_rms/D");
    ZRecoilBifurcateOutputTree->Branch("delta_phi_mean",&ZRecoilBifurcateOutputData.delta_phi_mean,"delta_phi_mean/D");
    ZRecoilBifurcateOutputTree->Branch("delta_phi_rms",&ZRecoilBifurcateOutputData.delta_phi_rms,"delta_phi_rms/D");
    ZRecoilBifurcateOutputTree->Branch("scale_a",&ZRecoilBifurcateOutputData.scale_a,"scale_a/D");
    ZRecoilBifurcateOutputTree->Branch("scale_b",&ZRecoilBifurcateOutputData.scale_b,"scale_b/D");
    ZRecoilBifurcateOutputTree->Branch("tau_had",&ZRecoilBifurcateOutputData.tau_had,"tau_had/D");
    ZRecoilBifurcateOutputTree->Branch("resolution_a",&ZRecoilBifurcateOutputData.resolution_a,"resolution_a/D");
    ZRecoilBifurcateOutputTree->Branch("resolution_b",&ZRecoilBifurcateOutputData.resolution_b,"resolution_b/D");
    ZRecoilBifurcateOutputTree->Branch("alpha_mb",&ZRecoilBifurcateOutputData.alpha_mb,"alpha_mb/D");
    ZRecoilBifurcateOutputTree->Branch("phi_a",&ZRecoilBifurcateOutputData.phi_a,"phi_a/D");
    ZRecoilBifurcateOutputTree->Branch("phi_b",&ZRecoilBifurcateOutputData.phi_b,"phi_b/D");
    ZRecoilBifurcateOutputTree->Branch("evt_weight",&ZRecoilBifurcateOutputData.evt_weight,"evt_weight/D");
    ZRecoilBifurcateOutputTree->Branch("evt_weight_2",&ZRecoilBifurcateOutputData.evt_weight_2,"evt_weight/D");

    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_bin1",&ZRecoilBifurcateOutputData.eta_imbalance_bin1,"eta_imbalance_bin1/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_bin2",&ZRecoilBifurcateOutputData.eta_imbalance_bin2,"eta_imbalance_bin2/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_bin3",&ZRecoilBifurcateOutputData.eta_imbalance_bin3,"eta_imbalance_bin3/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_bin4",&ZRecoilBifurcateOutputData.eta_imbalance_bin4,"eta_imbalance_bin4/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_bin5",&ZRecoilBifurcateOutputData.eta_imbalance_bin5,"eta_imbalance_bin5/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_bin6",&ZRecoilBifurcateOutputData.eta_imbalance_bin6,"eta_imbalance_bin6/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_bin7",&ZRecoilBifurcateOutputData.eta_imbalance_bin7,"eta_imbalance_bin7/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_bin8",&ZRecoilBifurcateOutputData.eta_imbalance_bin8,"eta_imbalance_bin8/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_bin9",&ZRecoilBifurcateOutputData.eta_imbalance_bin9,"eta_imbalance_bin9/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_bin10",&ZRecoilBifurcateOutputData.eta_imbalance_bin10,"eta_imbalance_bin10/D");

      ZRecoilBifurcateOutputTree->Branch("eta_imbalance_evtsq_bin1",&ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin1,"eta_imbalance_evtsq_bin1/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_evtsq_bin2",&ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin2,"eta_imbalance_evtsq_bin2/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_evtsq_bin3",&ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin3,"eta_imbalance_evtsq_bin3/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_evtsq_bin4",&ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin4,"eta_imbalance_evtsq_bin4/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_evtsq_bin5",&ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin5,"eta_imbalance_evtsq_bin5/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_evtsq_bin6",&ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin6,"eta_imbalance_evtsq_bin6/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_evtsq_bin7",&ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin7,"eta_imbalance_evtsq_bin7/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_evtsq_bin8",&ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin8,"eta_imbalance_evtsq_bin8/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_evtsq_bin9",&ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin9,"eta_imbalance_evtsq_bin9/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_evtsq_bin10",&ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin10,"eta_imbalance_evtsq_bin10/D");

  


    double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
    double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
    double raw_scale_HAD_bifurcate_Tau = _recoilsmear->scale_HAD_bifurcate_Tau();
    double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
    double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
    double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
    double raw_Reltrans_HAD_bifurcate_RelRespTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelRespTrans();
    double raw_Reltrans_HAD_bifurcate_RelResnTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelResnTrans();
    double raw_Reltrans_HAD_bifurcate_RelTauTrans  = _recoilsmear->Reltrans_HAD_bifurcate_RelTauTrans();
    double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
    double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
    double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();
    double raw_alpha_mb = _recoilsmear->alpha_mb();
    double raw_alpha_mb_trans = _recoilsmear->alpha_mb_trans();
    double raw_alpha_zb = _recoilsmear->alpha_zb();

    for(int iHAD=0; iHAD<=_ZRecoilBifurcateBins[0]; iHAD++){
    for(int jHAD=0; jHAD<=_ZRecoilBifurcateBins[1]; jHAD++){
    for(int kHAD=0; kHAD<=_ZRecoilBifurcateBins[2]; kHAD++){
    for(int lHAD=0; lHAD<=_ZRecoilBifurcateBins[3]; lHAD++){
    for(int mHAD=0; mHAD<=_ZRecoilBifurcateBins[4]; mHAD++){
    for(int nHAD=0; nHAD<=_ZRecoilBifurcateBins[5]; nHAD++){
    for(int pHAD=0; pHAD<=_ZRecoilBifurcateBins[6]; pHAD++){
    for(int qHAD=0; qHAD<=_ZRecoilBifurcateBins[7]; qHAD++){
    for(int hHAD=0; hHAD<10; hHAD++){

      double scale_HAD_bifurcate_A = raw_scale_HAD_bifurcate_A + (iHAD-_ZRecoilBifurcateBins[0]/2)*_ZRecoilBifurcateStep[0];
      double scale_HAD_bifurcate_B = raw_scale_HAD_bifurcate_B + (jHAD-_ZRecoilBifurcateBins[1]/2)*_ZRecoilBifurcateStep[1];
      double scale_HAD_bifurcate_Tau = raw_scale_HAD_bifurcate_Tau + (kHAD-_ZRecoilBifurcateBins[2]/2)*_ZRecoilBifurcateStep[2];
      double Relsampling_HAD_bifurcate_A = raw_Relsampling_HAD_bifurcate_A + (lHAD-_ZRecoilBifurcateBins[3]/2)*_ZRecoilBifurcateStep[3];
      double Relsampling_HAD_bifurcate_B = raw_Relsampling_HAD_bifurcate_B + (mHAD-_ZRecoilBifurcateBins[4]/2)*_ZRecoilBifurcateStep[4];
      double alpha_mb = raw_alpha_mb + (nHAD-_ZRecoilBifurcateBins[5]/2)*_ZRecoilBifurcateStep[5];
      double Relphi_HAD_bifurcate_A = raw_Relphi_HAD_bifurcate_A + (pHAD-_ZRecoilBifurcateBins[6]/2)*_ZRecoilBifurcateStep[6];
      double Relphi_HAD_bifurcate_B = raw_Relphi_HAD_bifurcate_B + (qHAD-_ZRecoilBifurcateBins[7]/2)*_ZRecoilBifurcateStep[7];

      double eta_imbalance_mean;
      double eta_imbalance_rms;
      double delta_phi_mean;
      double delta_phi_rms;
      double total_evt_weight;
      double total_evt_weight_2;

      total_evt_weight = evt_weight[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      total_evt_weight_2 = evt_weight_2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];

      if (total_evt_weight == 0){
	//protection against nan's in bins with no events
	eta_imbalance_mean = 0;
	eta_imbalance_rms = 0;
	delta_phi_mean = 0;
	delta_phi_rms = 0;
      }else{
	eta_imbalance_mean = eta_imbalance_x[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD]/total_evt_weight;
	if(fabs(eta_imbalance_x2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD]/total_evt_weight - eta_imbalance_mean*eta_imbalance_mean) < 1.e-10){
	  eta_imbalance_rms = 0; //protection against nan's in bins with only one event
	}else{
	  eta_imbalance_rms = sqrt(eta_imbalance_x2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD]/total_evt_weight - eta_imbalance_mean*eta_imbalance_mean);
	  if( isnan(eta_imbalance_rms) ){
	    cout<<"ZAnalysis:: NAN ETA IMBALANCE RMS"<<endl;
	    cout<<eta_imbalance_x2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD]/total_evt_weight<<"  "<<eta_imbalance_mean*eta_imbalance_mean<<endl;
	    cout<<eta_imbalance_rms<<endl;
	    cout<<total_evt_weight<<"  "<<eta_imbalance_x2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD]<<"  "<<eta_imbalance_mean<<endl;
	  }
	} 
	delta_phi_mean = delta_phi_x[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD]/total_evt_weight;
	delta_phi_rms = sqrt(delta_phi_x2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD]/total_evt_weight - delta_phi_mean*delta_phi_mean);
      }

      

      ZRecoilBifurcateOutputData.zpt = hHAD;
      ZRecoilBifurcateOutputData.eta_imbalance_mean = eta_imbalance_mean;
      ZRecoilBifurcateOutputData.eta_imbalance_rms = eta_imbalance_rms;
      ZRecoilBifurcateOutputData.delta_phi_mean = delta_phi_mean;
      ZRecoilBifurcateOutputData.delta_phi_rms = delta_phi_rms;
      
      ZRecoilBifurcateOutputData.scale_a =  scale_HAD_bifurcate_A;
      ZRecoilBifurcateOutputData.scale_b = scale_HAD_bifurcate_B;
      ZRecoilBifurcateOutputData.tau_had = scale_HAD_bifurcate_Tau;
      ZRecoilBifurcateOutputData.resolution_a = Relsampling_HAD_bifurcate_A;
      ZRecoilBifurcateOutputData.resolution_b = Relsampling_HAD_bifurcate_B;
      ZRecoilBifurcateOutputData.alpha_mb = alpha_mb;
      ZRecoilBifurcateOutputData.phi_a = Relphi_HAD_bifurcate_A;
      ZRecoilBifurcateOutputData.phi_b = Relphi_HAD_bifurcate_B;

      ZRecoilBifurcateOutputData.evt_weight = total_evt_weight;
      ZRecoilBifurcateOutputData.evt_weight_2 = total_evt_weight_2;

      ZRecoilBifurcateOutputData.eta_imbalance_bin1 = eta_imbalance_x_1[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_bin2 = eta_imbalance_x_2[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_bin3 = eta_imbalance_x_3[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_bin4 = eta_imbalance_x_4[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_bin5 = eta_imbalance_x_5[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_bin6 = eta_imbalance_x_6[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_bin7 = eta_imbalance_x_7[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_bin8 = eta_imbalance_x_8[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_bin9 = eta_imbalance_x_9[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_bin10 = eta_imbalance_x_10[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];


      ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin1 = eta_imbalance_x_1_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin2 = eta_imbalance_x_2_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin3 = eta_imbalance_x_3_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin4 = eta_imbalance_x_4_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin5 = eta_imbalance_x_5_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin6 = eta_imbalance_x_6_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin7 = eta_imbalance_x_7_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin8 = eta_imbalance_x_8_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin9 = eta_imbalance_x_9_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];
      ZRecoilBifurcateOutputData.eta_imbalance_evtsq_bin10 = eta_imbalance_x_10_evtsq[iHAD][jHAD][kHAD][lHAD][mHAD][nHAD][pHAD][qHAD][hHAD];

      ZRecoilBifurcateOutputTree->Fill();
      

    }// qHAD
    }// pHAD
    }// nHAD
    }// mHAD
    }// lHAD
    }// kHAD
    }// jHAD
    }// iHAD
    }// hHAD
    ZRecoilBifurcateFile->Write();
    ZRecoilBifurcateFile->Close();    
}


// RCLSA: Writes out the recoil template tree
void ZAnalysis::TransZHadronicRecoilBifurcateProcess() {
    
    ZRecoilBifurcateFile = new TFile(_ZRecoilBifurcateFile,"RECREATE");
    ZRecoilBifurcateOutputTree = new TTree("ZRecoilBifurcateOutputTree","Recoil Study Output");
    ZRecoilBifurcateOutputTree->Branch("zpt",&TransZRecoilBifurcateOutputData.zpt,"zpt/I");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_mean",&TransZRecoilBifurcateOutputData.eta_imbalance_mean,"eta_imbalance_mean/D");
    ZRecoilBifurcateOutputTree->Branch("eta_imbalance_rms",&TransZRecoilBifurcateOutputData.eta_imbalance_rms,"eta_imbalance_rms/D");
    ZRecoilBifurcateOutputTree->Branch("resptrans",&TransZRecoilBifurcateOutputData.resptrans,"resptrans/D");
    ZRecoilBifurcateOutputTree->Branch("resntrans",&TransZRecoilBifurcateOutputData.resntrans,"resntrans/D");
    ZRecoilBifurcateOutputTree->Branch("tautrans",&TransZRecoilBifurcateOutputData.tautrans,"tautrans/D");
    ZRecoilBifurcateOutputTree->Branch("alpha_mb_trans",&TransZRecoilBifurcateOutputData.alpha_mb_trans,"alpha_mb_trans/D");
    ZRecoilBifurcateOutputTree->Branch("evt_weight",&TransZRecoilBifurcateOutputData.evt_weight,"evt_weight/D");
    ZRecoilBifurcateOutputTree->Branch("evt_weight_2",&TransZRecoilBifurcateOutputData.evt_weight_2,"evt_weight/D");

    double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
    double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
    double raw_scale_HAD_bifurcate_Tau = _recoilsmear->scale_HAD_bifurcate_Tau();
    double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
    double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
    double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
    double raw_Reltrans_HAD_bifurcate_RelRespTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelRespTrans();
    double raw_Reltrans_HAD_bifurcate_RelResnTrans = _recoilsmear->Reltrans_HAD_bifurcate_RelResnTrans();
    double raw_Reltrans_HAD_bifurcate_RelTauTrans  = _recoilsmear->Reltrans_HAD_bifurcate_RelTauTrans();
    double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
    double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
    double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();
    double raw_alpha_mb = _recoilsmear->alpha_mb();
    double raw_alpha_mb_trans = _recoilsmear->alpha_mb_trans();
    double raw_alpha_zb = _recoilsmear->alpha_zb();

    for(int iHAD=0; iHAD<=_TransZRecoilBifurcateBins[0]; iHAD++){
    for(int jHAD=0; jHAD<=_TransZRecoilBifurcateBins[1]; jHAD++){
    for(int kHAD=0; kHAD<=_TransZRecoilBifurcateBins[2]; kHAD++){
    for(int lHAD=0; lHAD<=_TransZRecoilBifurcateBins[3]; lHAD++){
    for(int mHAD=0; mHAD<10; mHAD++){

      double Reltrans_HAD_bifurcate_RelRespTrans =  raw_Reltrans_HAD_bifurcate_RelRespTrans + (iHAD-_TransZRecoilBifurcateBins[0]/2)*_TransZRecoilBifurcateStep[0];
      double Reltrans_HAD_bifurcate_RelResnTrans =  raw_Reltrans_HAD_bifurcate_RelResnTrans + (jHAD-_TransZRecoilBifurcateBins[1]/2)*_TransZRecoilBifurcateStep[1];
      double Reltrans_HAD_bifurcate_RelTauTrans =  raw_Reltrans_HAD_bifurcate_RelTauTrans + (kHAD-_TransZRecoilBifurcateBins[2]/2)*_TransZRecoilBifurcateStep[2];
      double alpha_mb_trans = raw_alpha_mb_trans + (lHAD-_TransZRecoilBifurcateBins[3]/2)*_TransZRecoilBifurcateStep[3];
    
      double eta_imbalance_mean;
      double eta_imbalance_rms;
      double total_evt_weight;
      double total_evt_weight_2;

      total_evt_weight = trans_evt_weight[iHAD][jHAD][kHAD][lHAD][mHAD];
      total_evt_weight_2 = trans_evt_weight_2[iHAD][jHAD][kHAD][lHAD][mHAD];
      if (total_evt_weight == 0){
	//protection against nan's in bins with no events
	eta_imbalance_mean = 0;
	eta_imbalance_rms = 0;
      }else{
	eta_imbalance_mean = trans_eta_imbalance_x[iHAD][jHAD][kHAD][lHAD][mHAD]/total_evt_weight;
	if(fabs(trans_eta_imbalance_x2[iHAD][jHAD][kHAD][lHAD][mHAD]/total_evt_weight - eta_imbalance_mean*eta_imbalance_mean) < 1.e-10){
	  eta_imbalance_rms = 0; //protection against nan's in bins with only one event
	}else{
	  eta_imbalance_rms = sqrt(trans_eta_imbalance_x2[iHAD][jHAD][kHAD][lHAD][mHAD]/total_evt_weight - eta_imbalance_mean*eta_imbalance_mean);
	  if( isnan(eta_imbalance_rms) ){
	    cout<<"ZAnalysis:: NAN ETA IMBALANCE RMS"<<endl;
	    cout<<trans_eta_imbalance_x2[iHAD][jHAD][kHAD][lHAD][mHAD]/total_evt_weight<<"  "<<eta_imbalance_mean*eta_imbalance_mean<<endl;
	    cout<<eta_imbalance_rms<<endl;
	    cout<<total_evt_weight<<"  "<<trans_eta_imbalance_x2[iHAD][jHAD][kHAD][lHAD][mHAD]<<"  "<<eta_imbalance_mean<<endl;
	  }
	} 
      }

      TransZRecoilBifurcateOutputData.zpt = mHAD;
      TransZRecoilBifurcateOutputData.eta_imbalance_mean = eta_imbalance_mean;
      TransZRecoilBifurcateOutputData.eta_imbalance_rms = eta_imbalance_rms;
      
      TransZRecoilBifurcateOutputData.resptrans = Reltrans_HAD_bifurcate_RelRespTrans;
      TransZRecoilBifurcateOutputData.resntrans = Reltrans_HAD_bifurcate_RelResnTrans;
      TransZRecoilBifurcateOutputData.tautrans = Reltrans_HAD_bifurcate_RelTauTrans;
      TransZRecoilBifurcateOutputData.alpha_mb_trans = alpha_mb_trans;

      TransZRecoilBifurcateOutputData.evt_weight = total_evt_weight;
      TransZRecoilBifurcateOutputData.evt_weight_2 = total_evt_weight_2;
      ZRecoilBifurcateOutputTree->Fill();
      

    }// mHAD
    }// lHAD
    }// kHAD
    }// jHAD
    }// iHAD
    ZRecoilBifurcateFile->Write();
    ZRecoilBifurcateFile->Close();    
}



double ZAnalysis::MINUIT_calc_chi2( double raw_scale_HAD_bifurcate_A,
				    double raw_scale_HAD_bifurcate_B,
				    double raw_scale_HAD_bifurcate_Tau,
				    double raw_Relsampling_HAD_bifurcate_A,
				    double raw_Relsampling_HAD_bifurcate_B,
				    double raw_Relconst_HAD_bifurcate,
				    double raw_Reltrans_HAD_RelRespTrans,
				    double raw_Reltrans_HAD_RelResnTrans,
				    double raw_Reltrans_HAD_RelTauTrans,
				    double raw_Relphi_HAD_bifurcate_A,
				    double raw_Relphi_HAD_bifurcate_B,
				    double raw_RelconstPhi_HAD_bifurcate,
				    double raw_alpha_mb,
				    double raw_alpha_zb ) {
  Int_t npass = 0;
  Int_t npass_perbin[10]={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
  TRandom3 *dummy = MINUIT_getTRandom3();
  int nevts = MINUIT_getNevts();  // 0 means all events

  static bool need_init=(true && 
                         (!_Zminuit_UseMasterSlaveMode ||
			  (_Zminuit_UseMasterSlaveMode && 
			   _Zminuit_MasterSlave_Job==1)));
  /////////////////////////////
  if(_Zminuit_UseMasterSlaveMode) {
    cout << "MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	 << ": need_init="<<need_init<<endl;
  }
  ///////////////////////////

  // reference histograms
  static double ref_mean_etaimb[10], ref_mean_etaimb_err[10];
  static double ref_rms_etaimb[10], ref_rms_etaimb_err[10];
  static double ref_mean_xiimb[10], ref_mean_xiimb_err[10];
  static double ref_rms_xiimb[10], ref_rms_xiimb_err[10];
  static double ref_rms_phi[10], ref_rms_phi_err[10];
  static double ref_fitted_mean_etaimb[10];
  static double ref_fitted_width_etaimb[10];
  static double ref_fitted_mean_xiimb[10];
  static double ref_fitted_width_xiimb[10];
  static double ref_fitted_width_phi[10];
  static double ref_fitted_width_signedphi[10];
  static TF1 *feta, *fphi, *fsignedphi, *fxi;
  static TH1D *ref_hist_phi[10], *ref_hist_etaimb[10], *ref_hist_xiimb[10];
  if(need_init) {
    //
    // open reference histograms for reading
    //
    TFile *file_ref= new TFile(_Zminuit_Reference_FileName.Data(), "OLD");
    if(!file_ref) {
      cout<<"MINUIT_calc_chi2: Can't open reference file named: " << _Zminuit_Reference_FileName << endl;
      return -1;
    } 
    file_ref->cd(_Zminuit_Reference_Dir.Data());
    for(int ibin=0; ibin<10; ibin++) {
      char name1[50], name2[50], name3[50];
      sprintf(name1,"%s%d", _Zminuit_Reference_Prefix_Phi.Data(), ibin); // signed or unsigned
      sprintf(name2,"%s%d", _Zminuit_Reference_Prefix_EtaImbalance.Data(), ibin);
      sprintf(name3,"%s%d", _Zminuit_Reference_Prefix_XiImbalance.Data(), ibin);
      ref_hist_phi[ibin] = new TH1D( *((TH1D*)gROOT->FindObject(name1) ));    // copy
      ref_hist_etaimb[ibin] = new TH1D( *((TH1D*)gROOT->FindObject(name2) )); // copy
      ref_hist_xiimb[ibin] = new TH1D( *((TH1D*)gROOT->FindObject(name3) ));  // copy
      if( ref_hist_phi[ibin]==NULL || ref_hist_etaimb[ibin]==NULL || ref_hist_xiimb[ibin]==NULL ) {
	cout<<"MINUIT_calc_chi2: At least one reference histogram for MINUIT is missing for PT-bin "<< ibin << " !!!" << endl;
	file_ref->Close();
	delete file_ref; 
	return -1;
      }
      ref_mean_etaimb[ibin]=ref_hist_etaimb[ibin]->GetMean();
      ref_mean_etaimb_err[ibin]=ref_hist_etaimb[ibin]->GetMeanError();
      
      ref_mean_xiimb[ibin]=ref_hist_xiimb[ibin]->GetMean();
      ref_mean_xiimb_err[ibin]=ref_hist_xiimb[ibin]->GetMeanError();
      
      ref_rms_etaimb[ibin]=ref_hist_etaimb[ibin]->GetRMS();
      ref_rms_etaimb_err[ibin]=ref_hist_etaimb[ibin]->GetRMSError();
      
      ref_rms_xiimb[ibin]=ref_hist_xiimb[ibin]->GetRMS();
      ref_rms_xiimb_err[ibin]=ref_hist_xiimb[ibin]->GetRMSError();
  
      if(_Zminuit_UseAbsDeltaPhiImbal) {
	double sumw, contrib;
	ref_rms_phi[ibin]=0.0;
	ref_rms_phi_err[ibin]=0.0;
	contrib = 0.0;
	sumw = 0.0;
	for(int ix=1; ix <= ref_hist_phi[ibin]->GetNbinsX(); ix++) {
	  double val = ref_hist_phi[ibin]->GetBinContent(ix);
	  double err = ref_hist_phi[ibin]->GetBinError(ix);
	  contrib += pow( ref_hist_phi[ibin]->GetBinCenter(ix) - TMath::Pi(), 2)*val;
	  sumw += val;
	}
	if( sumw>0 ) {
	  ref_rms_phi[ibin] = sqrt(contrib/sumw);
	  ref_rms_phi_err[ibin] = ref_rms_phi[ibin]/sqrt(2.*sumw);
	}
      }	else {
	ref_rms_phi[ibin]=ref_hist_phi[ibin]->GetRMS();
	ref_rms_phi_err[ibin]=ref_hist_phi[ibin]->GetRMSError();
      }
      
      if(_Zminuit_UseFittedMeanWidth) {

	// use fitted values instead of TH1::GetMean(), TH1::GetRMS()
#if ( _USE_SINGLE_GAUSSIAN_ETAIMBAL_ )
	feta=new TF1("feta", fcn_eta, -50, 50, 3);
#else
	feta=new TF1("feta", fcn_eta, -50, 50, 5);
#endif
	fphi=new TF1("fphi", fcn_phi, 0, TMath::Pi(), 3);
	fsignedphi=new TF1("fsignedphi", fcn_signedphi, -TMath::Pi(), TMath::Pi(), 3 );
	fxi=new TF1("fxi", fcn_xi, -50, 50, 4);
	
	// eta imbalance fit
	feta->SetParameter(0, ref_hist_etaimb[ibin]->Integral()); 
	feta->SetParameter(1, ref_hist_etaimb[ibin]->GetMean());
	feta->SetParameter(2, ref_hist_etaimb[ibin]->GetRMS());
#if ( _USE_SINGLE_GAUSSIAN_ETAIMBAL_ )
	ref_hist_etaimb[ibin]->Fit(feta,"0R");
	ref_rms_etaimb[ibin] = feta->GetParameter(2);
	ref_rms_etaimb_err[ibin] = feta->GetParError(2);
#else
	feta->FixParameter(3, 0);
	feta->FixParameter(4, 0);
	ref_hist_etaimb[ibin]->Fit(feta,"0RW");
	feta->SetParLimits(3, 0, 1e6);
	feta->SetParLimits(4, 0, 1);
	ref_hist_etaimb[ibin]->Fit(feta,"0R");
	// SIGMA = sqrt( (1-Frac)*Sigma1^2 + Frac*Sigma2^2 )
	// where Frac=P4, Sigma1=P2, Sigma2=P2+P3
	ref_rms_etaimb[ibin] = 
	  sqrt( (1-feta->GetParameter(4))*pow(feta->GetParameter(2), 2) +
		feta->GetParameter(4)*pow(feta->GetParameter(2)+feta->GetParameter(3), 2) );
	ref_rms_etaimb_err[ibin] = 1/ref_rms_etaimb[ibin]*
	  sqrt( pow( feta->GetParameter(3)*
		     (feta->GetParameter(2)+feta->GetParameter(3))*
		     feta->GetParError(4), 2) +
		pow( (feta->GetParameter(2)+feta->GetParameter(4)*feta->GetParameter(3))*
		     feta->GetParError(2), 2) +
		pow( feta->GetParameter(4)*(feta->GetParameter(2)+feta->GetParameter(3))*
		     feta->GetParError(3), 2) );
#endif
	ref_mean_etaimb[ibin] = feta->GetParameter(1);
	ref_mean_etaimb_err[ibin] = feta->GetParError(1);
	cout << "DATA: ETA-IMBAL: PT-bin="<<ibin
	     <<": fitted_mean="<<ref_mean_etaimb[ibin]<<" +- "<<ref_mean_etaimb_err[ibin]
	     << " fitted_width="<<ref_rms_etaimb[ibin]<<" +- "<<ref_rms_etaimb_err[ibin]<<endl;
	cout << "DATA: ETA-IMBAL: PT-bin="<<ibin
	     <<": plain_mean="<<ref_hist_etaimb[ibin]->GetMean()<<" +- "<<ref_hist_etaimb[ibin]->GetMeanError()
	     <<" plain_rms="<<ref_hist_etaimb[ibin]->GetRMS()<<" +- "<<ref_hist_etaimb[ibin]->GetRMSError()<<endl;
	
	// xi imbalance fit
	fxi->FixParameter(2,0); 
	fxi->SetParameter(0, ref_hist_xiimb[ibin]->Integral()); 
	fxi->SetParameter(1, ref_hist_xiimb[ibin]->GetMean());
	fxi->SetParameter(3, ref_hist_xiimb[ibin]->GetRMS());
	fxi->SetParLimits(3, 0, 1e6);
	ref_hist_xiimb[ibin]->Fit(fxi,"0R");   
	fxi->ReleaseParameter(2); 
	fxi->SetParLimits(2, 0, 1e6);
	ref_hist_xiimb[ibin]->Fit(fxi,"0R");
	ref_mean_xiimb[ibin] = fxi->GetParameter(1);
	ref_mean_xiimb_err[ibin] = fxi->GetParError(1);
	ref_rms_xiimb[ibin] = fxi->GetParameter(2)+fxi->GetParameter(3); // this is not a precise std.deviation yet !!!
	ref_rms_xiimb_err[ibin] = sqrt( fxi->GetParError(2)*fxi->GetParError(2) +
					fxi->GetParError(3)*fxi->GetParError(3) );
	cout <<"DATA:  XI-IMBAL: PT-bin="<<ibin
	     <<": fitted_mean="<<ref_mean_xiimb[ibin]<<" +- "<<ref_mean_xiimb_err[ibin]
	     <<" fitted_width="<<ref_rms_xiimb[ibin]<<" +- "<<ref_rms_xiimb_err[ibin]<<endl;
	cout <<"DATA:  XI-IMBAL: PT-bin="<<ibin
	     <<": plain_mean="<<ref_hist_xiimb[ibin]->GetMean()<<" +- "<<ref_hist_xiimb[ibin]->GetMeanError()
	     <<" plain_rms="<<ref_hist_xiimb[ibin]->GetRMS()<<" +- "<<ref_hist_xiimb[ibin]->GetRMSError()<<endl;
	
	if(_Zminuit_UseAbsDeltaPhiImbal) {

	  // absolute phi imbalance fit
	  fphi->FixParameter(2,0); 
	  fphi->SetParameter(0, ref_hist_phi[ibin]->Integral()); 
	  fphi->SetParameter(1, ref_rms_phi[ibin] );
	  ref_hist_phi[ibin]->Fit(fphi,"0R");
	  fphi->ReleaseParameter(2); 
	  fphi->SetParameter(2, ref_hist_phi[ibin]->GetBinContent(1));
	  fphi->SetParLimits(2, 0, 1e6);
	  ref_hist_phi[ibin]->Fit(fphi,"0R");
	  ref_rms_phi[ibin] = fphi->GetParameter(1); // this is not a precise std. deviation yet !!!
	  ref_rms_phi_err[ibin] = fphi->GetParError(1);   

	} else {

	  // signed phi imbalance fit
	  fsignedphi->FixParameter(2,0); 
	  fsignedphi->SetParameter(0, ref_hist_phi[ibin]->Integral()); 
	  fsignedphi->SetParameter(1, ref_hist_phi[ibin]->GetRMS());
	  ref_hist_phi[ibin]->Fit(fsignedphi,"0R");
	  fsignedphi->ReleaseParameter(2); 
	  fsignedphi->SetParameter(2, ref_hist_phi[ibin]->GetBinContent(1));
	  fsignedphi->SetParLimits(2, 0, 1e6);
	  ref_hist_phi[ibin]->Fit(fsignedphi,"0R");
	  ref_rms_phi[ibin] = fsignedphi->GetParameter(1); // this is not a precise std. deviation yet !!!
	  ref_rms_phi_err[ibin] = fsignedphi->GetParError(1);   
	}
	cout << "DATA: PHI-IMBAL: PT-bin="<<ibin
	     << " fitted_width="<<ref_rms_phi[ibin]<<" +- "<<ref_rms_phi_err[ibin]<< endl;
      } // end of if(_Zminuit_UseFittedMeanWidth)
    } // end of for(ibin... loop

    // close ROOT file with reference histograms
    if(file_ref) {
      file_ref->Close();
      delete file_ref; 
      file_ref=NULL;
    }
    
    need_init=false;

  } // end of if(need_int)....

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++ Begin of Master-Slave mode.
  //++ Master broadcasts current recoil parameters and 
  //++ waits for acknowledge signal before proceeding.
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if(_Zminuit_UseMasterSlaveMode) {
    // general cross check
    if(_Zminuit_MasterSlave_REQ=="") {
      cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Wrong name of REQUEST file!!!"<<endl;
      throw;
    }
    if(_Zminuit_MasterSlave_ACK_prefix=="") {
      cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Wrong name of ACKNOWLEDGE file!!!"<<endl;
      throw;
    }
    if(_Zminuit_MasterSlave_DONE_prefix=="") {
      cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Wrong name of DONE file!!!"<<endl;
      throw;
    }
    if(_Zminuit_MasterSlave_RESULT_prefix=="") {
      cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Wrong name of RESULT file!!!"<<endl;
      throw;
    }
    //
    // only for MASTER job: create new REQUEST file.
    //
    if(_Zminuit_MasterSlave_Job==1) {
      // delete old QUIT file
      // check for QUIT signal                                                                                                                                          
      fstream f_QUIT(_Zminuit_MasterSlave_QUIT.Data(), ios::in);
      if(f_QUIT.is_open()) {
	f_QUIT.close();
	if (!remove("Zminuit_MasterSlave_QUIT")) {
	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Master removed old QUIT file."<<endl;
	} else {
	  cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Master can't remove old QUIT file!!!"<<endl;
	  throw;
	}
      }
      // delete old START file
      fstream f_START(_Zminuit_MasterSlave_START.Data(), ios::in);
      if(f_START.is_open()) {
	f_START.close();
	if (!remove(_Zminuit_MasterSlave_START.Data())) {
	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Master removed old START file."<<endl;
	} else {
	  cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Master can't remove old START file!!!"<<endl;
	  throw;
	}
      }
      // delete old ACK, DONE, RESULT files
      for(int ijob=1; ijob<=_Zminuit_MasterSlave_Njobs; ijob++) {
	stringstream ss;
	ss<<"_"<<ijob;
	fstream f_ACK((_Zminuit_MasterSlave_ACK_prefix+ss.str().c_str()).Data(),
		      ios::in);
	fstream f_DONE((_Zminuit_MasterSlave_DONE_prefix+ss.str().c_str()).Data(),
		      ios::in);
	fstream f_RESULT((_Zminuit_MasterSlave_RESULT_prefix+ss.str().c_str()).Data(),
		      ios::in);
	if (f_ACK.is_open()) {
	  f_ACK.close();
	  if(!remove((_Zminuit_MasterSlave_ACK_prefix+ss.str().c_str()).Data())) {
	    cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
		<<": Master removed old ACK_"<<ijob<<" file."<<endl;
	  } else {
	    cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
		<<": Master can't remove old ACK_"<<ijob<<" file."<<endl;
	      throw;
	  }
	}
	if (f_DONE.is_open()) {
	  f_DONE.close();
	  if(!remove((_Zminuit_MasterSlave_DONE_prefix+ss.str().c_str()).Data())) {
	    cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
		<<": Master removed old DONE_"<<ijob<<" file."<<endl;
	  } else {
	    cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
		<<": Master can't remove old DONE_"<<ijob<<" file."<<endl;
	      throw;
	  }
	}
	if (f_RESULT.is_open()) {
	  f_RESULT.close();
	  if(!remove((_Zminuit_MasterSlave_RESULT_prefix+ss.str().c_str()).Data())) {
	    cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
		<<": Master removed old RESULT_"<<ijob<<" file."<<endl;
	  } else {
	    cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
		<<": Master can't remove old RESULT_"<<ijob<<" file."<<endl;
	      throw;
	  }
	}
      }
      // create new REQUEST file
      fstream f_REQ(_Zminuit_MasterSlave_REQ.Data(),
		    ios::out | ios::trunc);
      if (f_REQ.is_open()) {
	f_REQ.precision(5);
	f_REQ << scientific
	      << setw(13) << raw_scale_HAD_bifurcate_A        
	      << setw(13) << raw_scale_HAD_bifurcate_B        
	      << setw(13) << raw_Relsampling_HAD_bifurcate_A  
	      << setw(13) << raw_Relsampling_HAD_bifurcate_B
	      << setw(13) << raw_Relconst_HAD_bifurcate
	      << setw(13) << raw_Reltrans_HAD_RelRespTrans
	      << setw(13) << raw_Reltrans_HAD_RelResnTrans
	      << setw(13) << raw_Reltrans_HAD_RelTauTrans
	      << setw(13) << raw_Relphi_HAD_bifurcate_A
	      << setw(13) << raw_Relphi_HAD_bifurcate_B
	      << setw(13) << raw_RelconstPhi_HAD_bifurcate
	      << setw(13) << raw_alpha_mb
	      << setw(13) << raw_alpha_zb << endl << flush;
	f_REQ.close();
	cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	    <<": Master sent REQUEST signal."<<endl;
      } else {
	cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	    <<": Master can't create new REQUEST file!!!"<<endl;
	throw;
      }
    } // end of MASTER section
    //
    // for all jobs: wait for REQUEST file to show up.
    //
    cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	<<": Job waits for REQUEST signal."<<endl;
    bool do_wait=true;
    do {
      usleep(1000000); // wait 1.0 sec
      raw_scale_HAD_bifurcate_A = -9999;        
      raw_scale_HAD_bifurcate_B = -9999;        
      raw_Relsampling_HAD_bifurcate_A = -9999; 
      raw_Relsampling_HAD_bifurcate_B = -9999;
      raw_Relconst_HAD_bifurcate = -9999;
      raw_Reltrans_HAD_RelRespTrans = -9999;
      raw_Reltrans_HAD_RelResnTrans = -9999;
      raw_Reltrans_HAD_RelTauTrans = -9999;
      raw_Relphi_HAD_bifurcate_A = -9999;
      raw_Relphi_HAD_bifurcate_B = -9999;
      raw_RelconstPhi_HAD_bifurcate = -9999;
      raw_alpha_mb = -9999;
      raw_alpha_zb = -9999;

      fstream f_REQ(_Zminuit_MasterSlave_REQ.Data(), ios::in);
      if(f_REQ.is_open()) {
	f_REQ >> raw_scale_HAD_bifurcate_A        
	      >> raw_scale_HAD_bifurcate_B        
	      >> raw_Relsampling_HAD_bifurcate_A  
	      >> raw_Relsampling_HAD_bifurcate_B
	      >> raw_Relconst_HAD_bifurcate
	      >> raw_Reltrans_HAD_RelRespTrans
	      >> raw_Reltrans_HAD_RelResnTrans
	      >> raw_Reltrans_HAD_RelTauTrans
	      >> raw_Relphi_HAD_bifurcate_A
	      >> raw_Relphi_HAD_bifurcate_B
	      >> raw_RelconstPhi_HAD_bifurcate
	      >> raw_alpha_mb
	      >> raw_alpha_zb;
	f_REQ.close();
      }
      if(raw_alpha_zb!=-9999) do_wait=false;
      else {
	// check for QUIT signal 
	fstream f_QUIT(_Zminuit_MasterSlave_QUIT.Data(), ios::in);
	if(f_QUIT.is_open()) {
	  f_QUIT.close();
	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Job detected QUIT signal."<<endl;
	  return -1.0;
	}
      }
    } while(do_wait);
    cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	<<": Job detected REQUEST signal."<<endl;
    cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	<<":";
    cout.precision(5);
    cout<<scientific
       << setw(13) << raw_scale_HAD_bifurcate_A        
       << setw(13) << raw_scale_HAD_bifurcate_B        
       << setw(13) << raw_Relsampling_HAD_bifurcate_A  
       << setw(13) << raw_Relsampling_HAD_bifurcate_B
       << setw(13) << raw_Relconst_HAD_bifurcate
       << setw(13) << raw_Reltrans_HAD_RelRespTrans
       << setw(13) << raw_Reltrans_HAD_RelResnTrans
       << setw(13) << raw_Reltrans_HAD_RelTauTrans
       << setw(13) << raw_Relphi_HAD_bifurcate_A
       << setw(13) << raw_Relphi_HAD_bifurcate_B
       << setw(13) << raw_RelconstPhi_HAD_bifurcate
       << setw(13) << raw_alpha_mb
       << setw(13) << raw_alpha_zb << endl;

    // delete old DONE file.
    stringstream ss;
    ss<<"_"<<_Zminuit_MasterSlave_Job;
    fstream f_DONE((_Zminuit_MasterSlave_DONE_prefix+ss.str().c_str()).Data(), 
		   ios::in);
    if(f_DONE.is_open()) {
      f_DONE.close();
      if (!remove((_Zminuit_MasterSlave_DONE_prefix+ss.str().c_str()).Data())) {
	cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	    <<": Job removed old DONE file."<<endl;
      } else {
	cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	    <<": Job can't remove old DONE file!!!"<<endl;
	throw;
      }
    }

    // create new ACK file
    ss.str("");
    ss<<"_"<<_Zminuit_MasterSlave_Job;
    fstream f_ACK((_Zminuit_MasterSlave_ACK_prefix+ss.str().c_str()).Data(),
		  ios::out | ios::trunc);
    if (f_ACK.is_open()) {
      f_ACK << endl << flush;
      f_ACK.close();
      cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Job sent ACK signal"<<endl;
    } else {
      cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Job can't create new ACK file!!!"<<endl;
      throw;
    }
    // only for MASTER: wait for ACK from all jobs.
    int Nready=0;
    if(_Zminuit_MasterSlave_Job==1) {
      cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Master waits for ACK signals from all jobs."<<endl;
      do {
	usleep(1000000); // wait 1.0 sec
	Nready=0;
	for(int ijob=1; ijob<=_Zminuit_MasterSlave_Njobs; ijob++) {
	  // check for ACK signal
	  stringstream ss;
	  ss<<"_"<<ijob;
	  fstream f_ACK((_Zminuit_MasterSlave_ACK_prefix+ss.str().c_str()).Data(),
			ios::in);
	  if (f_ACK.is_open()) {
	  f_ACK.close();
	  Nready++;
// 	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
// 	      <<": Master detected ACK from slave no."<<ijob<<endl;
	  }
	}
	// check for QUIT signal 
	fstream f_QUIT(_Zminuit_MasterSlave_QUIT.Data(), ios::in);
	if(f_QUIT.is_open()) {
	  f_QUIT.close();
	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Master detected QUIT signal."<<endl;
	  return -1.0;
	}

      } while(Nready<_Zminuit_MasterSlave_Njobs);
      cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Master detected ACK signals from all jobs."<<endl;
      // deletes REQ file
      fstream f_REQ(_Zminuit_MasterSlave_REQ.Data(), ios::in);
      if(f_REQ.is_open()) {
	f_REQ.close();
	if (!remove(_Zminuit_MasterSlave_REQ.Data())) {
	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Master removed old REQUEST file."<<endl;
	} else {
	  cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Master can't remove old REQUEST file!!!"<<endl;
	  throw;
	}
      }
      // creates START file
      fstream f_START(_Zminuit_MasterSlave_START.Data(), ios::out);
      if(f_START.is_open()) {
	f_START << endl << flush;
	f_START.close();
	cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Master sent START signal."<<endl;
      } else {
	cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	    <<": Master can't create new START file!!!"<<endl;
	throw;
      }
    } // end of MASTER mode 
    //
    // for all jobs: wait for START signal.
    //
    do_wait=true;
    do {
      usleep(1000000); // wait 1.0 sec
      fstream f_START(_Zminuit_MasterSlave_START.Data(), ios::in);
      if(f_START.is_open()) {
	f_START.close();
        do_wait=false;
      }
      // check for QUIT signal 
      fstream f_QUIT(_Zminuit_MasterSlave_QUIT.Data(), ios::in);
      if(f_QUIT.is_open()) {
	f_QUIT.close();
	cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	    <<": Job detected QUIT signal."<<endl;
	return -1.0;
      }
    } while(do_wait);
    cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	<<": Job detected START signal."<<endl;
    if(1) {
      // deletes old ACK, DONE, RESULT files
      stringstream ss;
      ss<<"_"<<_Zminuit_MasterSlave_Job;
      fstream f_ACK((_Zminuit_MasterSlave_ACK_prefix+ss.str().c_str()).Data(), ios::in);
      if(f_ACK.is_open()) {
	f_ACK.close();
	if (!remove((_Zminuit_MasterSlave_ACK_prefix+ss.str().c_str()).Data())) {
	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Job removed old ACK file."<<endl;
	} else {
	  cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Job can't remove old ACK file!!!"<<endl;
	  throw;
	}
      }
      fstream f_DONE((_Zminuit_MasterSlave_DONE_prefix+ss.str().c_str()).Data(), ios::in);
      if(f_DONE.is_open()) {
	f_DONE.close();
	if (!remove((_Zminuit_MasterSlave_DONE_prefix+ss.str().c_str()).Data())) {
	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Job removed old DONE file."<<endl;
	} else {
	  cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Job can't remove old DONE file!!!"<<endl;
	  throw;
	}
      }
      fstream f_RESULT((_Zminuit_MasterSlave_RESULT_prefix+ss.str().c_str()).Data(), ios::in);
      if(f_RESULT.is_open()) {
	f_RESULT.close();
	if (!remove((_Zminuit_MasterSlave_RESULT_prefix+ss.str().c_str()).Data())) {
	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Job removed old RESULT file."<<endl;
	} else {
	  cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Job can't remove old RESULT file!!!"<<endl;
	  throw;
	}
      }
    }
  } // end of Master-Slave mode
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++ End of Master-Slave mode.
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  ////////////////////////////////////////////////////////
  //
  // reset MINUIT histograms
  //
  for(int ibin=0; ibin<10; ibin++) {
    char name[50];
    sprintf(name, "minuit_hZcandDeltaPhi_Z_Recoil_bin_%d", ibin);
    _histos.th1d(name)->Reset();
    //     cout << "PT-bin " << ibin << ": " << name << " after RESET: mean=" 
    //  	 << _histos.th1d(name)->GetMean()
    //  	 << ", rms=" 
    //  	 << _histos.th1d(name)->GetRMS() << endl;
    if(!_Zminuit_UseAbsDeltaPhiImbal) {
      sprintf(name, "minuit_hZcandSignedDeltaPhi_Z_Recoil_bin_%d", ibin);
      _histos.th1d(name)->Reset();
      //         cout << "PT-bin " << ibin << ": " << name << " after RESET: mean=" 
      //      	 << _histos.th1d(name)->GetMean()
      //      	 << ", rms=" 
      //      	 << _histos.th1d(name)->GetRMS() << endl;
    }
    sprintf(name, "minuit_hZcandEtaImBalance_bin_%d", ibin);
    _histos.th1d(name)->Reset();
    //     cout << "PT-bin " << ibin << ": " << name << " after RESET: mean=" 
    //  	 << _histos.th1d(name)->GetMean()
    //  	 << ", rms=" 
    //  	 << _histos.th1d(name)->GetRMS() << endl;
    sprintf(name, "minuit_hZcandXiImBalance_bin_%d", ibin);
    _histos.th1d(name)->Reset();
    //     cout << "PT-bin " << ibin << ": " << name << " after RESET: mean=" 
    //  	 << _histos.th1d(name)->GetMean()
    //  	 << ", rms=" 
    //  	 << _histos.th1d(name)->GetRMS() << endl;
  }
  
  //
  // loop thru preselected events
  //
  int ievt=0;
  long bytes_RAM = 0;
  string prefix("minuit_");
  time_t t0=time(NULL);
  cout << "Time at start of reprocessing: "<<ctime(&t0);

  // open an existing file with buffered events
  if(!_Zminuit_RAMBuffer_Ready) {
    _Zminuit_EventBuffer_File = fopen(_Zminuit_EventBuffer_FileName.Data(), "rb");
    if(!_Zminuit_EventBuffer_File) {
      cerr<<"ZAnalysis::MINUIT_calc_chi2: Event buffer file "
	  <<_Zminuit_EventBuffer_FileName<<" does not exist!!!"<<endl;
      throw;
    }
  }

  // looping starts here
  while(1) {
    
    ievt++;
    if(ievt%100000==0) {
      cout<<"Reprocessing event number: "<<ievt << endl; // <<" / "<<nevts<<endl;
    }
    if(nevts>0 && ievt>nevts) {
      ievt--;
      break;
    } 

    std::vector<PMCSEMObj> emobjs_smear;
    PMCSRecoil recoil_gen;
    PMCSVtx vtx_gen;
    double evtweight;
    double luminosity;
    int runno;
    int zbindex;
    int mbindex;
    double external_pt_resol;
    double external_delta_phi;
    double external_upara_rnd1;
    double external_upara_rnd2;
    double external_SET_rnd;
    double external_znunu_SET_Hard;
    double external_znunu_SET_Hard_expected;
    double given_tbdmetx;
    double given_tbdmety;
    //
    // read from RAM or disk?
    //
    if(_Zminuit_RAMBuffer_Ready) {
      
      // read from RAM 
      if (ievt>_Zminuit_RAMBuffer_Nevts) break;
      int bytes=0;
      int nem=0;
      char *pos = _Zminuit_RAMBuffer + bytes_RAM;
      bytes = MINUIT_ReadRAM(pos, emobjs_smear, recoil_gen, vtx_gen, evtweight, luminosity, 
			     runno, zbindex, mbindex, external_pt_resol, external_delta_phi,
			     external_upara_rnd1, external_upara_rnd2, external_SET_rnd, external_znunu_SET_Hard, external_znunu_SET_Hard_expected,
			     given_tbdmetx, given_tbdmety);
      //      cout<< "Read " << bytes << " bytes from RAM." << endl;
      bytes_RAM += bytes;
    
    } else {

      // read from disk
      if(feof(_Zminuit_EventBuffer_File)) break; 
      int bytes=MINUIT_ReadFile(emobjs_smear, recoil_gen, vtx_gen, evtweight,
				luminosity, runno, zbindex, mbindex, external_pt_resol, external_delta_phi,
				external_upara_rnd1, external_upara_rnd2, external_SET_rnd, external_znunu_SET_Hard, external_znunu_SET_Hard_expected,
                                given_tbdmetx, given_tbdmety);
      //      cout<< "Read " << bytes << " bytes from disk." << endl;
      
      // during first pass store events into RAM if Zminuit_UseRAM=TRUE
      if(_Zminuit_UseRAM && !_Zminuit_RAMBuffer_Ready && bytes>0) {

	// (re)allocate the memory
	char *_Zminuit_RAMBuffer_NEW = (char*)realloc(_Zminuit_RAMBuffer, bytes_RAM + bytes);
	if(_Zminuit_RAMBuffer_NEW) _Zminuit_RAMBuffer = _Zminuit_RAMBuffer_NEW;
	else {
	  ievt--;
	  cout << "MINUIT_calc_chi2: Can't allocate more memory!!! Will analyze " 
	       << ievt << " events only." << endl;
	  break; // exit while(1) loop
	}
	char *pos = _Zminuit_RAMBuffer + bytes_RAM;
	bytes = MINUIT_WriteRAM(pos, emobjs_smear, recoil_gen, vtx_gen, evtweight, luminosity, 
				runno, zbindex, mbindex, external_pt_resol, external_delta_phi,
				external_upara_rnd1, external_upara_rnd2, external_SET_rnd, external_znunu_SET_Hard, external_znunu_SET_Hard_expected,
                                given_tbdmetx, given_tbdmety);
	//	cout<< "Wrote " << bytes << " bytes to RAM." << endl;
	bytes_RAM += bytes;
	_Zminuit_RAMBuffer_Nevts++;
      }
    } // end of RAM or DISK ?

    // skip if there are less than 2 smeared EM objects in an event
    if( emobjs_smear.size()<2 ) continue;
    
    // get two electron uparaCorr, energyLeakage, eta and phi to calculate uparallel corrections
    double ElecUParaCorr[2], ElecEnergyLeakage[2], ElecEta[2], ElecDetEta[2], 
      ElecPhi[2], ElecDetPhi[2], ElecPx[2], ElecPy[2];
    for(int i=0; i<2; i++) {
      ElecUParaCorr[i] = emobjs_smear[i].UParaCorr();
      ElecEnergyLeakage[i] = emobjs_smear[i].EnergyLeakage();
      ElecEta[i] = emobjs_smear[i].peta();
      ElecDetEta[i] = emobjs_smear[i].deteta();
      ElecPhi[i] = emobjs_smear[i].pphi();
      ElecDetPhi[i] = emobjs_smear[i].detphi();
      ElecPx[i] = emobjs_smear[i].ppx();
      ElecPy[i] = emobjs_smear[i].ppy();
    }
    
    // Z boson vector
    TVector2 elec1_vect(ElecPx[0], ElecPy[0]);
    TVector2 elec2_vect(ElecPx[1], ElecPy[1]);
    TVector2 z_vect = elec1_vect + elec2_vect;
    
    // divide events into smeared Z pT bins
    int bin = wz_utils::pTee_Eta_Bin(z_vect.Mod());
    if(bin<0) continue; // out of range
    char pee_bin_sn[10]; sprintf(pee_bin_sn, "%d", bin);
    
    // recoil pT, phi at generator level
    double raw_recoil_pT = recoil_gen.Recoil();
    double raw_recoil_phi = recoil_gen.RecoilPhi();
  
    // smear soft component
    double smear_Metx_From_MB = 0., smear_Mety_From_MB = 0., smear_Metx_From_ZB = 0., smear_Mety_From_ZB = 0.;
    double smear_Metx = 0., smear_Mety = 0.;
    _recoilsmear->setRunNoInstLumiMBZBEvtIndex(runno, luminosity, mbindex, zbindex);
    _recoilsmear->SmearSoftRecoil_Method_D(raw_alpha_mb, raw_alpha_zb, dummy,
					   smear_Metx_From_MB, smear_Mety_From_MB,
					   smear_Metx_From_ZB, smear_Mety_From_ZB,
					   smear_Metx, smear_Mety);

    // apply TB correction
    _recoilsmear->ApplyTopBottomAsym_B(smear_Metx, smear_Mety, false);
    given_tbdmetx = _recoilsmear->getTBdmetx();
    given_tbdmety = _recoilsmear->getTBdmety();

    // smear hard component
    double smear_recoil_pT = 0., smear_recoil_phi = 0., smear_SET = 0.;
    if(_Zminuit_Skip_Znunu_Randomization) {
      _recoilsmear->SmearHardRecoil_Method_D(raw_recoil_pT, 
					     raw_recoil_phi, 
					     raw_scale_HAD_bifurcate_A, 
					     raw_scale_HAD_bifurcate_B,
					     raw_scale_HAD_bifurcate_Tau,
					     raw_Relsampling_HAD_bifurcate_A, 
					     raw_Relsampling_HAD_bifurcate_B, 
					     raw_Relconst_HAD_bifurcate,
					     raw_Reltrans_HAD_RelRespTrans,
					     raw_Reltrans_HAD_RelResnTrans,
					     raw_Reltrans_HAD_RelTauTrans,
					     raw_Relphi_HAD_bifurcate_A, 
					     raw_Relphi_HAD_bifurcate_B, 
					     raw_RelconstPhi_HAD_bifurcate,
					     dummy, 
					     smear_recoil_pT, 
					     smear_recoil_phi,
					     smear_SET,
					     external_pt_resol,  // use this ONE instead of random value
					     external_delta_phi, // use this ONE instead of random value
					     external_znunu_SET_Hard,       // use this ONE instead of random value 
					     external_znunu_SET_Hard_expected, // use this ONE instead of random value
					     true,               // ....skip hard recoil randomization
					     false );            // and proceed with the fudging as usual....
    } else { 
      _recoilsmear->SmearHardRecoil_Method_D(raw_recoil_pT, 
					     raw_recoil_phi, 
					     raw_scale_HAD_bifurcate_A, 
					     raw_scale_HAD_bifurcate_B,
					     raw_scale_HAD_bifurcate_Tau,
					     raw_Relsampling_HAD_bifurcate_A, 
					     raw_Relsampling_HAD_bifurcate_B, 
					     raw_Relconst_HAD_bifurcate,
					     raw_Reltrans_HAD_RelRespTrans,
                                             raw_Reltrans_HAD_RelResnTrans,
                                             raw_Reltrans_HAD_RelTauTrans,
					     raw_Relphi_HAD_bifurcate_A, 
					     raw_Relphi_HAD_bifurcate_B, 
					     raw_RelconstPhi_HAD_bifurcate,
					     dummy, 
					     smear_recoil_pT, 
					     smear_recoil_phi,
					     smear_SET);
    }

//     ///////////////////// DEBUG //////////////////////////
//     //
//     PMCSRecoil recoil_smear_beforeUparaCorr( smear_recoil_pT * cos(smear_recoil_phi) + smear_Metx,
// 					     smear_recoil_pT * sin(smear_recoil_phi) + smear_Mety );
//     //
//     ///////////////////// DEBUG //////////////////////////

    // add uparallel correction
    double sum_UparaCorrX = 0., sum_UparaCorrY = 0.;
    for(int ielec=0; ielec<2; ielec++) {
      sum_UparaCorrX += (ElecUParaCorr[ielec] 
			 - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* cos(ElecPhi[ielec]);
      sum_UparaCorrY += (ElecUParaCorr[ielec] 
			 - ElecEnergyLeakage[ielec]/cosh(ElecEta[ielec]))* sin(ElecPhi[ielec]);
    }
    
    // final smeared recoil system (soft component added)
    double smear_recoil_X = smear_recoil_pT * cos(smear_recoil_phi) + smear_Metx - sum_UparaCorrX;
    double smear_recoil_Y = smear_recoil_pT * sin(smear_recoil_phi) + smear_Mety - sum_UparaCorrY;

//     ///////////////////// DEBUG //////////////////////////
//     //
//     PMCSRecoil recoil_smear_afterUparaCorr_beforePhotonMerge( smear_recoil_X, smear_recoil_Y );
//     //
//     ///////////////////// DEBUG //////////////////////////

    //
    // include photons in the smeared recoil system
    // the photon response is described in EMSmear::SmearPhotonEnergy
    //
    for(int i=0; i<emobjs_smear.size(); i++) {
      if((emobjs_smear[i].ppid())==22) {
	smear_recoil_X += emobjs_smear[i].ppx();
	smear_recoil_Y += emobjs_smear[i].ppy();
      }
    }

    // recoil after all corrections
    PMCSRecoil recoil_smear(smear_recoil_X, smear_recoil_Y);
    
    // met after corrections for the two highest pT electrons
    double metX_component = -(emobjs_smear[0].ppx()+emobjs_smear[1].ppx()+recoil_smear.Recoilx());
    double metY_component = -(emobjs_smear[0].ppy()+emobjs_smear[1].ppy()+recoil_smear.Recoily());
    PMCSMet met_smear(metX_component, metY_component);
    
    bool passUparaEff=false;
    bool passRecoil;
    // skip randomization of U|| efficiency upon request
    // but always skip randomization of hard SET
    if( _Zminuit_Skip_UParaEfficiency_Randomization ) {
      passRecoil = passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
				    NULL, &passUparaEff, // NULL,
				    _Zminuit_Skip_UParaEfficiency, 
				    &external_upara_rnd1, &external_upara_rnd2,
				    &external_SET_rnd);
    } else {
      passRecoil = passesRecoilCuts(emobjs_smear, recoil_smear, met_smear, dummy,
				    NULL, &passUparaEff, // NULL, 
				    _Zminuit_Skip_UParaEfficiency,
				    NULL, NULL, &external_SET_rnd);
    }
    
//     ///////////////////// DEBUG //////////////////////////
//     //
//     double dummyset;
//     cout << "++++ MINUIT REPROCESSING:" << endl
// 	 << " hard SET from RAM (unfudged)=" << external_znunu_SET_Hard
// 	 << ", Buffered hard SET (unfudged)=" << _recoilsmear->scalarEt_hard()
// 	 << ", calc. hard SET(fudged)=" << _recoilsmear->scalarEt_hard()  
// 	 << ", calc. total SET=" << _recoilsmear->scalarEt() 
// 	 << ", passRECOIL=" << passRecoil << endl;
//     //
//     ///////////////////// DEBUG //////////////////////////

    //     ///////////////////// DEBUG //////////////////////////
    //     //
    //     double znunu_hard_recoil_pT, znunu_hard_recoil_phi;
    //     double smeared_hard_recoil_pT, smeared_hard_recoil_phi;
    //     double generated_hard_recoil_pT, generated_hard_recoil_phi;
    //     _recoilsmear->GetLastHardRecoil_Method_B(&generated_hard_recoil_pT,
    // 					    &generated_hard_recoil_phi,
    // 					    &znunu_hard_recoil_pT, 
    // 					    &znunu_hard_recoil_phi,
    // 					    &smeared_hard_recoil_pT, 
    // 					    &smeared_hard_recoil_phi);
    //     cout << "#### EVENT --> MINUIT PARAMS:" << endl;
    //     cout << "#### U_parallel Eff:   PASSED=" << passUparaEff 
    // 	 << ", RND1=" << (_Zminuit_Skip_UParaEfficiency_Randomization ? external_upara_rnd1 : -1) 
    // 	 << ", RND2=" << (_Zminuit_Skip_UParaEfficiency_Randomization ? external_upara_rnd2 : -1) << endl;
    //     cout << "#### Smeared RECOIL:   PASSED=" << passRecoil
    // 	 << ", Px=" << recoil_smear.Recoilx() 
    // 	 << ", Py=" << recoil_smear.Recoily() << endl;
    //     cout << "#### GEN HARD RECOIL:          Pt=" << generated_hard_recoil_pT
    // 	 << ", Phi=" << generated_hard_recoil_phi
    // 	 << " (raw_recoil_pT="<<raw_recoil_pT<<", raw_recoil_phi="<<raw_recoil_phi<<")"<<endl;  
    //     cout << "#### ZNUNU HARD RECOIL:        Pt=" << znunu_hard_recoil_pT
    // 	 << ", Phi=" << znunu_hard_recoil_phi
    // 	 << " (external_pt_resol="<<external_pt_resol<<", external_delta_phi="<<external_delta_phi<<")"<<endl;  
    //     cout << "#### ZEE HARD RECOIL:          Pt=" << smeared_hard_recoil_pT
    // 	 << ", Phi=" << smeared_hard_recoil_phi
    // 	 << " (smear_recoil_pT="<<smear_recoil_pT<<", smear_recoil_phi="<<smear_recoil_phi<<")"<<endl;  
    //     //
    //     ///////////////////// DEBUG //////////////////////////
    
    if(passRecoil) {

      npass++;
      npass_perbin[bin]++;

      // Recoil
      TVector2 recoil_vect(smear_recoil_X, smear_recoil_Y);

      // Z boson bisector of the two electrons (not needed for PHI smearinfg studies!)
      TVector2 bisector_vect = (elec1_vect.Unit() + elec2_vect.Unit()).Unit();
    
      // calculate delta phi between Z and the recoil
      double signed_deltaphi_Z_recoil = z_vect.DeltaPhi(recoil_vect);

      // calculate eta imbalance
      double eta_imbalance = (z_vect + recoil_vect) * bisector_vect;
	
      // calculate xi imbalance
      double xi_imbalance = (z_vect + recoil_vect) * (bisector_vect.Rotate(0.5*TMath::Pi()));

      _histos.Fill1D((prefix+"hZcandDeltaPhi_Z_Recoil_bin_"+pee_bin_sn).c_str(), 
		     fabs(signed_deltaphi_Z_recoil), evtweight);
      if(!_Zminuit_UseAbsDeltaPhiImbal) {
	double signed_deltaphi_Z_recoil_02Pi = (signed_deltaphi_Z_recoil<0. ? signed_deltaphi_Z_recoil+TMath::TwoPi() : signed_deltaphi_Z_recoil);
	_histos.Fill1D((prefix+"hZcandSignedDeltaPhi_Z_Recoil_bin_"+pee_bin_sn).c_str(),
		       signed_deltaphi_Z_recoil_02Pi, evtweight);
      }
      _histos.Fill1D((prefix+"hZcandEtaImBalance_bin_"+pee_bin_sn).c_str(), 
		     eta_imbalance, evtweight);    
      _histos.Fill1D((prefix+"hZcandXiImBalance_bin_"+pee_bin_sn).c_str(), 
		     xi_imbalance, evtweight);    

//       ///////////////////// DEBUG //////////////////////////
//       //
//       {
// 	PMCSZCand zcand(emobjs_smear[0], emobjs_smear[1], recoil_smear, met_smear);
// 	double hard_SET=_recoilsmear->scalarEt_hard();
// 	double smear_SET=_recoilsmear->scalarEt();
// 	double gen_pt,gen_phi,znunu_pt,znunu_phi,smear_pt,smear_phi;
// 	_recoilsmear->GetLastHardRecoil_Method_B(&gen_pt,&gen_phi,&znunu_pt,&znunu_phi,&smear_pt,&smear_phi);
// 	cout << "==== reprocessing Z candidate CCCC EVENT=" << npass << endl
// 	     << "     Generated:     pT="<<gen_pt  <<", Dphi="<<0.0<<endl
// 	     << "     Hard:          pT="<<znunu_pt<<", Dphi="<<kinem::delta_phi(znunu_phi, gen_phi)<<", SET="<<hard_SET<<endl
// 	     << "     Smear:         pT="<<smear_pt<<", Dphi="<<kinem::delta_phi(smear_phi, gen_phi)<<", SET="<<smear_SET<<endl
// 	     << "     Before U||:    pT="<<recoil_smear_beforeUparaCorr.Recoil()<<endl
// 	     << "     Aft.U||:       pT="<<recoil_smear_afterUparaCorr_beforePhotonMerge.Recoil()<<endl
// 	     << "     Aft.U||+gamma: pT="<<recoil_smear.Recoil()
// 	     <<", (from zcand: pT="<<zcand.MagRecoil()<<", Dphi="<<kinem::delta_phi(TMath::Pi(), zcand.DeltaPhi_Z_Recoil())<<")"<<endl
// 	     << "     Eta-imb=" << eta_imbalance << ", Xi-imb=" << xi_imbalance << endl;
//       }
//       //
//       ///////////////////// DEBUG //////////////////////////
    }
  }
  if(_Zminuit_EventBuffer_File) {
    fclose(_Zminuit_EventBuffer_File);
    _Zminuit_EventBuffer_File=NULL;
  }
  nevts = ievt;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++ Begin of Master-Slave mode.
  //++ Master waits for partial results and then adds 
  //++ all the histograms before proceeding.
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if(_Zminuit_UseMasterSlaveMode) {
    // create new RESULT rootuple
    stringstream ss;
    ss<<"_"<<_Zminuit_MasterSlave_Job;
    TFile f_RESULT((_Zminuit_MasterSlave_RESULT_prefix+ss.str().c_str()).Data(),
		   "RECREATE");
    if (f_RESULT.IsOpen()) {
      f_RESULT.cd();
       for(int ibin=0; ibin<10; ibin++) {
 	char name1[50], name2[50], name3[50], name4[50];
 	sprintf(name1, "minuit_hZcandEtaImBalance_bin_%d",ibin);
 	sprintf(name2, "minuit_hZcandXiImBalance_bin_%d",ibin);
 	sprintf(name3, "minuit_hZcandDeltaPhi_Z_Recoil_bin_%d",ibin);
 	sprintf(name4, "minuit_hZcandSignedDeltaPhi_Z_Recoil_bin_%d",ibin);
 	if(_histos.check_name(name1)) _histos.th1d(name1)->Write(name1, TObject::kSingleKey);
 	if(_histos.check_name(name2)) _histos.th1d(name2)->Write(name2, TObject::kSingleKey);
 	if(_histos.check_name(name3)) _histos.th1d(name3)->Write(name3, TObject::kSingleKey);
 	if(_histos.check_name(name4)) _histos.th1d(name4)->Write(name4, TObject::kSingleKey);
       } // end of ijob loop
      f_RESULT.Close("R");
      cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Job created RESULT rootuple."<<endl<<flush;
    } else {
      cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Job can't create new RESULT rootuple!!!"<<endl<<flush;
      throw;
    }
    // create new DONE file.
    ss.str("");
    ss<<"_"<<_Zminuit_MasterSlave_Job;
    fstream f_DONE((_Zminuit_MasterSlave_DONE_prefix+ss.str().c_str()).Data(),
		  ios::out);
    if (f_DONE.is_open()) {
      f_DONE << endl << flush;
      f_DONE.close();
      cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Job sent DONE signal"<<endl;
    } else {
      cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Job can't create new DONE file!!!"<<endl;
      throw;
    }

    // only for MASTER: wait for DONE from all jobs.
    int Nready=0;
    if(_Zminuit_MasterSlave_Job==1) {
      do {
	usleep(1000000); // wait 1.0 sec
	Nready=0;
	for(int ijob=1; ijob<=_Zminuit_MasterSlave_Njobs; ijob++) {
	  // create new DONE file
	  stringstream ss;
	  ss<<"_"<<ijob;
	  fstream f_DONE((_Zminuit_MasterSlave_DONE_prefix+ss.str().c_str()).Data(),
			 ios::in);
	  if (f_DONE.is_open()) {
	  f_DONE.close();
	  Nready++;
// 	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
// 	      <<": Master detected DONE from slave no."<<ijob<<endl;
	  }
	}
      } while(Nready<_Zminuit_MasterSlave_Njobs);
      cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Master detected all DONE signals."<<endl;

      // adding corresponding histograms produced by jobs 2...N to 
      // histograms from job #1.

      cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": NPASS before update: "<<npass<<"=";
      for(int ibin=0; ibin<10; ibin++) cout<<npass_perbin[ibin]<<(ibin==9?" ":"+");
      cout<<endl;

      for(int ijob=2; ijob<=_Zminuit_MasterSlave_Njobs; ijob++) {
	stringstream ss;
	ss<<"_"<<ijob;
	TFile f_RESULT((_Zminuit_MasterSlave_RESULT_prefix+ss.str().c_str()).Data(),
			 "OLD");
	if (f_RESULT.IsOpen()) {
	  f_RESULT.cd();
	  for(int ibin=0; ibin<10; ibin++) {
	    char name1[50], name2[50], name3[50], name4[50];
	    sprintf(name1, "minuit_hZcandEtaImBalance_bin_%d",ibin);
	    sprintf(name2, "minuit_hZcandXiImBalance_bin_%d",ibin);
	    sprintf(name3, "minuit_hZcandDeltaPhi_Z_Recoil_bin_%d",ibin);
	    sprintf(name4, "minuit_hZcandSignedDeltaPhi_Z_Recoil_bin_%d",ibin);
 	    TH1D *hslv1 = (TH1D*)f_RESULT.Get(name1);
 	    TH1D *hslv2 = (TH1D*)f_RESULT.Get(name2);
 	    TH1D *hslv3 = (TH1D*)f_RESULT.Get(name3);
 	    TH1D *hslv4 = (TH1D*)f_RESULT.Get(name4);
	    TH1D *h1=(_histos.check_name(name1) ? _histos.th1d(name1) : NULL);
	    TH1D *h2=(_histos.check_name(name2) ? _histos.th1d(name2) : NULL);
	    TH1D *h3=(_histos.check_name(name3) ? _histos.th1d(name3) : NULL);
	    TH1D *h4=(_histos.check_name(name4) ? _histos.th1d(name4) : NULL);
	    if(h1 && hslv1) { 
	      h1->Sumw2(); h1->Add(hslv1,1.0); 
	      // Since Eta Imbalance histograms are always filled in
	      // it's sufficient to update npass and npass_perbin[] here.
	      npass+=(Int_t)hslv1->GetEntries(); 
	      npass_perbin[ibin]+=(Int_t)hslv1->GetEntries();
	    } 
	    if(h2 && hslv2) { h2->Sumw2(); h2->Add(hslv2,1.0); }
	    if(h3 && hslv3) { h3->Sumw2(); h3->Add(hslv3,1.0); }
	    if(h4 && hslv4) { h4->Sumw2(); h4->Add(hslv4,1.0); } 
	    if(h1) cout <<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
			<<": IBIN="<<ibin
			<<": N(h1)="<<h1->GetEntries()
			<<", mean(h1)="<<h1->GetMean()<<" +- "<<h1->GetMeanError()<<endl;
	    if(h2) cout <<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
			<<": IBIN="<<ibin
			<<": N(h2)="<<h2->GetEntries()
			<<", mean(h2)="<<h2->GetMean()<<" +- "<<h2->GetMeanError()<<endl;
	    if(h3) cout <<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
			<<": IBIN="<<ibin
			<<": N(h3)="<<h3->GetEntries()
			<<", mean(h3)="<<h3->GetMean()<<" +- "<<h3->GetMeanError()<<endl;
	    if(h4) cout <<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
			<<": IBIN="<<ibin
			<<": N(h4)="<<h4->GetEntries()
			<<", mean(h4)="<<h4->GetMean()<<" +- "<<h4->GetMeanError()<<endl;
	  } // end of ibin loop
	  f_RESULT.Close();
	  cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Master added histograms from job "<<ijob<<"."<<endl;
	} else {
	  cerr<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	      <<": Master can't access RESULT rootuple from job "<<ijob<<" !!!"<<endl;
	  throw;
	}
	cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	    <<": Master collected all the histograms for CHI2 calculation."<<endl;
      } // end of ijob loop

      cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": NPASS after update: "<<npass<<"=";
      for(int ibin=0; ibin<10; ibin++) cout<<npass_perbin[ibin]<<(ibin==9?" ":"+");
      cout<<endl;

    } // end of MASTER mode
  } // end of Master-Slave mode

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++ End of Master-Slave mode.
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  //
  // summary of current and reference histograms
  //
  //   for(int ibin=0; ibin<10; ibin++) {
  //     char name[50];
  //     sprintf(name, "minuit_hZcandEtaImBalance_bin_%d", ibin);
  //     cout << "PT-bin " << ibin << ": " << name << " after REPROCESSING: " << endl
  // 	 << "  mean=" << _histos.th1d(name)->GetMean()
  // 	 << " (reference=" << ref_hist_etaimb[ibin]->GetMean()
  // 	 << " +- " << ref_hist_etaimb[ibin]->GetMeanError()
  // 	 << ")" << endl
  // 	 << "  rms=" << _histos.th1d(name)->GetRMS() 
  // 	 << " (reference=" << ref_hist_etaimb[ibin]->GetRMS()
  // 	 << " +- " << ref_hist_etaimb[ibin]->GetRMSError()
  // 	 << ")" << endl;      
  //     sprintf(name, "minuit_hZcandXiImBalance_bin_%d", ibin);
  //     cout << "PT-bin " << ibin << ": " << name << " after REPROCESSING: " << endl
  // 	 << "  mean=" << _histos.th1d(name)->GetMean()
  // 	 << " (reference=" << ref_hist_xiimb[ibin]->GetMean()
  // 	 << " +- " << ref_hist_xiimb[ibin]->GetMeanError()
  // 	 << ")" << endl
  // 	 << "  rms=" << _histos.th1d(name)->GetRMS() 
  // 	 << " (reference=" << ref_hist_xiimb[ibin]->GetRMS()
  // 	 << " +- " << ref_hist_xiimb[ibin]->GetRMSError()
  // 	 << ")" << endl;      
  //     sprintf(name, "minuit_hZcandDeltaPhi_Z_Recoil_bin_%d", ibin);
  //     cout << "PT-bin " << ibin << ": " << name << " after REPROCESSING: " << endl
  // 	 << "  mean=" << _histos.th1d(name)->GetMean()
  // 	 << " (reference=" << ref_hist_phi[ibin]->GetMean()
  // 	 << " +- " << ref_hist_phi[ibin]->GetMeanError()
  // 	 << ")" << endl
  // 	 << "  rms=" << _histos.th1d(name)->GetRMS() 
  // 	 << " (reference=" << ref_hist_phi[ibin]->GetRMS()
  // 	 << " +- " << ref_hist_phi[ibin]->GetRMSError()
  // 	 << ")" << endl;      
  //   }

  // Summary 
  cout << endl
       << "=========================================================================================="<<endl
       << " Reference file: " << _Zminuit_Reference_FileName << endl
       << " Recoil model paramters: " << endl
       << setw(30) << "Scale_HAD_bifurcate_A : " << setw(15) << raw_scale_HAD_bifurcate_A << endl
       << setw(30) << "Scale_HAD_bifurcate_B : " << setw(15) << raw_scale_HAD_bifurcate_B << endl
       << setw(30) << "Relsampling_HAD_bifurcate_A : " << setw(15) << raw_Relsampling_HAD_bifurcate_A << endl
       << setw(30) << "Relsampling_HAD_bifurcate_B : " << setw(15) << raw_Relsampling_HAD_bifurcate_B << endl
       << setw(30) << "Relconst_HAD_bifurcate : " << setw(15) << raw_Relconst_HAD_bifurcate << endl
       << setw(30) << "Relphi_HAD_bifurcate_A : " << setw(15) << raw_Relphi_HAD_bifurcate_A << endl
       << setw(30) << "Relphi_HAD_bifurcate_B : " << setw(15) << raw_Relphi_HAD_bifurcate_B << endl
       << setw(30) << "RelconstPhi_HAD_bifurcate : " << setw(15) << raw_RelconstPhi_HAD_bifurcate << endl
       << setw(30) << "Alpha_mb : " << setw(15) << raw_alpha_mb << endl
       << setw(30) << "Alpha_zb : " << setw(15) << raw_alpha_zb << endl
       << "------------------------------------------------------------------------------------------"<<endl;

  if(_Zminuit_UseMasterSlaveMode && _Zminuit_MasterSlave_Job>1) {
    return -1.0;
  }

  //
  // calculate total CHI2 for MINUIT
  //
  double TotalCHI2 = 0.0;
  switch(_Zminuit_ChiSquare_Method) {

  // require agreement at bin-by-bin level
  case 1: {
    // histograms for current recoil model
    double chi2_etaimb[10], chi2_phi[10];
    int npoints_etaimb[10], npoints_phi[10];
    for(int ibin=0; ibin<10; ibin++) {

      // phi resolution
      chi2_phi[ibin]=0.0;
      npoints_phi[ibin]=0;
      char name[50];
      sprintf(name, "minuit_hZcandDeltaPhi_Z_Recoil_bin_%d",ibin);
      TH1D *h1 = _histos.th1d(name);
      TH1D *h2 = ref_hist_phi[ibin];
      int n1 = h1->GetNbinsX();
      int n2 = h2->GetNbinsX();
      double integral1 = h1->Integral();
      double integral2 = h2->Integral();
      if(n1!=n2) {
	cout << "MINUIT_calc_chi2: Histograms for Phi Resolution have different number of bins for PT-bin " 
	     << ibin << " !!!" << endl;
	break;
      }
      if( integral1>0 && integral2>0 ) {
	for(int ix=1; ix <= n1; ix++) {
	  double val1 = h1->GetBinContent(ix) / integral1;
	  double err1 = h1->GetBinError(ix) / integral1;
	  double val2 = h2->GetBinContent(ix) / integral2;
	  double err2 = h2->GetBinError(ix) / integral2;
	  if( err1>0 || err2>0 ) {
	    chi2_phi[ibin] += pow( val1-val2, 2) / (err1*err1+err2*err2);
	    npoints_phi[ibin]++;
	  }
	} // end of for(ix=... loop
      }
      // eta imbalance
      chi2_etaimb[ibin]=0.0;
      npoints_etaimb[ibin]=0;
      sprintf(name, "minuit_hZcandEtaImBalance_bin_%d",ibin);
      h1 = _histos.th1d(name);
      h2 = ref_hist_etaimb[ibin];
      n1 = h1->GetNbinsX();
      n2 = h2->GetNbinsX();
      integral1 = h1->Integral();
      integral2 = h2->Integral();
      if(n1!=n2) {
	cout << "MINUIT_calc_chi2: Histograms for Eta Imbalance have different number of bins for PT-bin " 
	     << ibin << " !!!" << endl;
	break;
      }
      if( integral1>0 && integral2>0 ) {
	for(int ix=1; ix <= n1; ix++) {
	  double val1 = h1->GetBinContent(ix) / integral1;
	  double err1 = h1->GetBinError(ix) / integral1;
	  double val2 = h2->GetBinContent(ix) / integral2;
	  double err2 = h2->GetBinError(ix) / integral2;
	  if( err1>0 || err2>0 ) {
	    chi2_etaimb[ibin] += pow( val1-val2, 2) / (err1*err1+err2*err2);
	    npoints_etaimb[ibin]++;
	  }
	} // end of for(ix=... loop
      } // end of for(ibin=... loop
    }

    // agreement bewteen current and reference histograms
    double TotalCHI2_etaimb=0.0, TotalCHI2_phi=0.0;
    for(int ibin=0; ibin<10; ibin++) {
      if( npoints_etaimb[ibin]>0 ) {
	TotalCHI2 += chi2_etaimb[ibin] / npoints_etaimb[ibin];
	TotalCHI2_etaimb += chi2_etaimb[ibin] / npoints_etaimb[ibin];
      }
      if( npoints_phi[ibin]>0 ) {
	TotalCHI2 += chi2_phi[ibin] / npoints_phi[ibin];
	TotalCHI2_phi += chi2_phi[ibin] / npoints_phi[ibin];
      }
    }
    // SUMMARY
    cout << setw(15) << "TOTAL CHI2" 
	 << setw(15) << "Eta imb."
	 << setw(15) << "Phi resol." << endl
	 << setw(15) << TotalCHI2
	 << setw(15) << TotalCHI2_etaimb
	 << setw(15) << TotalCHI2_phi << endl
	 << "------------------------------------------------------------------------------------------"<<endl
	 << setw(15) << "CHI2 PER BIN" 
	 << setw(15) << "Eta imb."
	 << setw(15) << "Phi resol." << endl;
    for(int ibin=0; ibin<10; ibin++) {
      cout << setw(14) << "BIN " << setw(1) << ibin
	   << setw(15) << ( npoints_etaimb[ibin] ? chi2_etaimb[ibin] / npoints_etaimb[ibin] : 0 )
	   << setw(15) << ( npoints_phi[ibin] ? chi2_phi[ibin]  / npoints_phi[ibin] : 0 )
	   << endl;
    }
    break;
  }
  case 2: {
    // histograms for current recoil model
    double chi2_etaimb[10], chi2_phi[10];
    int npoints_etaimb[10], npoints_phi[10];
    for(int ibin=0; ibin<10; ibin++) {

      // phi resolution
      chi2_phi[ibin]=0.0;
      npoints_phi[ibin]=0;
      char name[50];
      sprintf(name, "minuit_hZcandDeltaPhi_Z_Recoil_bin_%d",ibin);
      TH1D *h1 = _histos.th1d(name);
      TH1D *h2 = ref_hist_phi[ibin];
      int n1 = h1->GetNbinsX();
      int n2 = h2->GetNbinsX();
      double integral1 = h1->Integral();
      double integral2 = h2->Integral();
      if(n1!=n2) {
	cout << "MINUIT_calc_chi2: Histograms for Phi Resolution have different number of bins for PT-bin " 
	     << ibin << " !!!" << endl;
	break;
      }
      if( integral1>0 && integral2>0 ) {
	for(int ix=1; ix <= n1; ix++) {
	  double val1 = h1->GetBinContent(ix) / integral1;
	  double err1 = h1->GetBinError(ix) / integral1;
	  double val2 = h2->GetBinContent(ix) / integral2;
	  double err2 = h2->GetBinError(ix) / integral2;
	  if( err1>0 || err2>0 ) {
	    chi2_phi[ibin] += pow( val1-val2, 2) / (err1*err1+err2*err2);
	    npoints_phi[ibin]++;
	  }
	} // end of for(ix=... loop
      }
      // eta imbalance
      chi2_etaimb[ibin]=0.0;
      npoints_etaimb[ibin]=0;
      sprintf(name, "minuit_hZcandEtaImBalance_bin_%d",ibin);
      h1 = _histos.th1d(name);
      h2 = ref_hist_etaimb[ibin];
      n1 = h1->GetNbinsX();
      n2 = h2->GetNbinsX();
      integral1 = h1->Integral();
      integral2 = h2->Integral();
      if(n1!=n2) {
	cout << "MINUIT_calc_chi2: Histograms for Eta Imbalance have different number of bins for PT-bin " 
	     << ibin << " !!!" << endl;
	break;
      }
      if( integral1>0 && integral2>0 ) {
	for(int ix=1; ix <= n1; ix++) {
	  double val1 = h1->GetBinContent(ix) / integral1;
	  double err1 = h1->GetBinError(ix) / integral1;
	  double val2 = h2->GetBinContent(ix) / integral2;
	  double err2 = h2->GetBinError(ix) / integral2;
	  if( err1>0 || err2>0 ) {
	    chi2_etaimb[ibin] += pow( val1-val2, 2) / (err1*err1+err2*err2);
	    npoints_etaimb[ibin]++;
	  }
	} // end of for(ix=... loop
      } // end of for(ibin=... loop
    }

    // agreement bewteen current and reference histograms
    double TotalCHI2_etaimb=0.0, TotalCHI2_phi=0.0;
    for(int ibin=0; ibin<10; ibin++) {
      TotalCHI2 += chi2_etaimb[ibin];
      TotalCHI2_etaimb += chi2_etaimb[ibin];
      TotalCHI2 += chi2_phi[ibin];
      TotalCHI2_phi += chi2_phi[ibin];
    }
    // SUMMARY
    cout << setw(15) << "TOTAL CHI2" 
	 << setw(15) << "Eta imb."
	 << setw(15) << "Phi resol." << endl
	 << setw(15) << TotalCHI2
	 << setw(15) << TotalCHI2_etaimb
	 << setw(15) << TotalCHI2_phi << endl
	 << "------------------------------------------------------------------------------------------"<<endl
	 << setw(15) << "CHI2 PER BIN" 
	 << setw(15) << "Eta imb." 
	 << setw(15) << "Phi resol." << endl;
    for(int ibin=0; ibin<10; ibin++) {
      cout << setw(14) << "BIN " << setw(1) << ibin
	   << setw(15) << chi2_etaimb[ibin]
	   << setw(15) << chi2_phi[ibin]
	   << endl;
    }
    break;
  }
    // require agreement at MEAN and RMS level
  case 0:   // ETA-MEAN + ETA-RMS + PHI-RMS
  case 4:   // ETA-MEAN
  case 5:   // ETA-MEAN + XI-MEAN
  case 6:   // ETA-RMS
  case 7:   // ETA-RMS + XI-RMS
  case 8:   // PHI-RMS
  case 9:   // ETA-MEAN + ETA-RMS
  case 10:  // ETA-MEAN + ETA-RMS + XI-MEAN + XI-RMS
  case 3: { // ETA-MEAN + ETA-RMS + XI-MEAN + XI-RMS + PHI-RMS
    // histograms for current recoil model
    double new_mean_etaimb[10], new_mean_etaimb_err[10];
    double new_rms_etaimb[10], new_rms_etaimb_err[10];
    double new_mean_xiimb[10], new_mean_xiimb_err[10];
    double new_rms_xiimb[10], new_rms_xiimb_err[10];
    double new_rms_phi[10], new_rms_phi_err[10];
    // reference histograms
    //     double ref_mean_etaimb[10], ref_mean_etaimb_err[10];
    //     double ref_rms_etaimb[10], ref_rms_etaimb_err[10];
    //     double ref_mean_xiimb[10], ref_mean_xiimb_err[10];
    //     double ref_rms_xiimb[10], ref_rms_xiimb_err[10];
    //     double ref_rms_phi[10], ref_rms_phi_err[10];
    // agreement bewteen current and reference histograms
    double TotalCHI2_mean_etaimb=0.0, TotalCHI2_rms_etaimb=0.0, TotalCHI2_mean_xiimb=0.0, TotalCHI2_rms_xiimb=0.0, TotalCHI2_rms_phi=0.0;
    double chi2_mean_etaimb[10], chi2_rms_etaimb[10], chi2_mean_xiimb[10], chi2_rms_xiimb[10], chi2_rms_phi[10];
    bool print_mean_etaimb=false, print_rms_etaimb=false, print_mean_xiimb=false, print_rms_xiimb=false, print_rms_phiimb=false; 

    for(int ibin=0; ibin<10; ibin++) {
      bool eta_fit_done=false; // caching for eta mean/width
      bool xi_fit_done=false;  // caching for xi mean/width
      TH1D *h;
      char name[50];
	
      // Phi imbalance width
      if(_Zminuit_ChiSquare_Method==0 || _Zminuit_ChiSquare_Method==3 ||
	 _Zminuit_ChiSquare_Method==8 ) {
	print_rms_phiimb=true;

	if(!_Zminuit_UseFittedMeanWidth) { // use plain width of phi imbalance 

	  if(_Zminuit_UseAbsDeltaPhiImbal) { // plain width, absolute delta phi

	    // Calculate standard deviation for an unfolded Delta_Phi histogram
	    // we have to recalculate it from scratch because in PMCS
	    // we fill |Delta_Phi(Z,Recoil)| not signed Delta_Phi(Z,Recoil).
	    //
	    // The way we do it is compatible with ROOT's GetMean() and GetRMS() methods.
	    // We assume here that weight=1 for each event, thus s[0]=s[1]=Nevents.
	    // ROOT's TH1D::GetRMSError() : 
	    //    Double_t x, rms2, s[kNstat];
	    //    GetStats(s);
	    //    x    = s[2]/s[0];// s[3] sum of weight*(x^2), s[2] sum of weight*x, s[0] sum of weights 
	    //    rms2 = TMath::Abs(s[3]/s[0] -x*x);
	    //    Double_t neff = GetEffectiveEntries();
	    //    return TMath::Sqrt(rms2/(2*neff));
	    // ROOT's TH1::GetEffectiveEntries() :
	    //    Stat_t s[kNstat];
	    //    this->GetStats(s);// s[1] sum of squares of weights, s[0] sum of weights
	    //    return s[0]*s[0]/s[1];
	    //
	    double contrib, sumw;
	    new_rms_phi[ibin]=0.0;
	    new_rms_phi_err[ibin]=0.0;
	    sprintf(name, "minuit_hZcandDeltaPhi_Z_Recoil_bin_%d",ibin);
	    h=_histos.th1d(name);
	    contrib = 0.0;
	    sumw = 0.0;
	    for(int ix=1; ix <= h->GetNbinsX(); ix++) {
	      double val = h->GetBinContent(ix);
	      double err = h->GetBinError(ix);
	      contrib += pow( h->GetBinCenter(ix) - TMath::Pi(), 2)*val;
	      sumw += val;
	    }
	    if( sumw>0 ) {
	      new_rms_phi[ibin] = sqrt(contrib/sumw);
	      new_rms_phi_err[ibin] = new_rms_phi[ibin]/sqrt(2.0*sumw);
	    }
	    //       cout << "PMCS: PHI-RESOL: PT-bin "<<ibin<<": chi2_contrib="<< new_rms_phi[ibin]
	    // 	   << ", totalentries="<<sumw<< endl;
	    
	    // 	ref_rms_phi[ibin]=0.0;
	    // 	ref_rms_phi_err[ibin]=0.0;
	    // 	contrib = 0.0;
	    // 	sumw = 0.0;
	    // 	for(int ix=1; ix <= ref_hist_phi[ibin]->GetNbinsX(); ix++) {
	    // 	  double val = ref_hist_phi[ibin]->GetBinContent(ix);
	    // 	  double err = ref_hist_phi[ibin]->GetBinError(ix);
	    // 	  contrib += pow( ref_hist_phi[ibin]->GetBinCenter(ix) - TMath::Pi(), 2)*val;
	    // 	  sumw += val;
	    // 	}
	    // 	if( sumw>0 ) {
	    // 	  ref_rms_phi[ibin] = sqrt(contrib/sumw);
	    // 	  ref_rms_phi_err[ibin] = ref_rms_phi[ibin]/sqrt(2.*sumw);
	    // 	}
	    //       cout << "DATA: PHI-RESOL: PT-bin "<<ibin<<": chi2_contrib="<< ref_rms_phi[ibin]
	    // 	   << ", totalentries="<<sumw<< endl;
	    
	    chi2_rms_phi[ibin] = 0.0;
	    if( ref_rms_phi_err[ibin]>0 || new_rms_phi_err[ibin]>0 ) {
	      chi2_rms_phi[ibin] = pow( new_rms_phi[ibin]-ref_rms_phi[ibin], 2)/
		( new_rms_phi_err[ibin]*new_rms_phi_err[ibin] +
		  ref_rms_phi_err[ibin]*ref_rms_phi_err[ibin] );
	    }
	    TotalCHI2 += chi2_rms_phi[ibin];
	    TotalCHI2_rms_phi += chi2_rms_phi[ibin];

	  } else { // plain width, signed delta phi
	    
	    new_rms_phi[ibin]=0.0;
	    new_rms_phi_err[ibin]=0.0;
	    sprintf(name, "minuit_hZcandSignedDeltaPhi_Z_Recoil_bin_%d",ibin);
	    h=_histos.th1d(name);
	    new_rms_phi[ibin] = h->GetRMS();
	    new_rms_phi_err[ibin] = h->GetRMSError();
	    // 	cout << "PMCS: PHI-RESOL: PT-bin "<<ibin<<": chi2_contrib="<< new_rms_phi[ibin]
	    // 	     << ", totalentries="<<sumw<< endl;
	    
	    // 	ref_rms_phi[ibin]=ref_hist_phi[ibin]->GetRMS();
	    // 	ref_rms_phi_err[ibin]=ref_hist_phi[ibin]->GetRMSError();
	    //       cout << "DATA: PHI-RESOL: PT-bin "<<ibin<<": chi2_contrib="<< ref_rms_phi[ibin]
	    // 	   << ", totalentries="<<sumw<< endl;
	    
	    chi2_rms_phi[ibin] = 0.0;
	    if( ref_rms_phi_err[ibin]>0 || new_rms_phi_err[ibin]>0 ) {
	      chi2_rms_phi[ibin] = pow( new_rms_phi[ibin]-ref_rms_phi[ibin], 2)/
		( new_rms_phi_err[ibin]*new_rms_phi_err[ibin] +
		  ref_rms_phi_err[ibin]*ref_rms_phi_err[ibin] );
	    }
	    TotalCHI2 += chi2_rms_phi[ibin];
	    TotalCHI2_rms_phi += chi2_rms_phi[ibin];
	  }
	  
	} else { // use fitted width of phi imbalance 
	  
	  if (_Zminuit_UseAbsDeltaPhiImbal) { // fitted width, absolute delta phi
	    
	    new_rms_phi[ibin]=0.0;
	    new_rms_phi_err[ibin]=0.0;
	    sprintf(name, "minuit_hZcandDeltaPhi_Z_Recoil_bin_%d",ibin);
	    h=_histos.th1d(name);
	    
	    // phi imbalance fit
	    fphi->FixParameter(2,0); 
	    fphi->SetParameter(0, h->Integral()); 
	    fphi->SetParameter(1, h->GetRMS());
	    h->Fit(fphi,"0R");
	    fphi->ReleaseParameter(2); 
	    fphi->SetParameter(2, h->GetBinContent(1));
	    fphi->SetParLimits(2, 0, 1e6);
	    h->Fit(fphi,"0R");
	    new_rms_phi[ibin] = fphi->GetParameter(1); // this is not a precise std.deviation yet !!!
	    new_rms_phi_err[ibin] = fphi->GetParError(1);   
	    cout << "PMCS: PHI-IMBAL: PT-bin="<<ibin
		 << " fitted_width="<<new_rms_phi[ibin]<<" +- "<<new_rms_phi_err[ibin]<< endl<<flush;
	    
	    // 	ref_rms_phi[ibin]=ref_hist_phi[ibin]->GetRMS();
	    // 	ref_rms_phi_err[ibin]=ref_hist_phi[ibin]->GetRMSError();
	    // 	//       cout << "DATA: PHI-RESOL: PT-bin "<<ibin<<": chi2_contrib="<< ref_rms_phi[ibin]
	    // 	// 	   << ", totalentries="<<sumw<< endl;
	    
	    chi2_rms_phi[ibin] = 0.0;
	    if( ref_rms_phi_err[ibin]>0 || new_rms_phi_err[ibin]>0 ) {
	      chi2_rms_phi[ibin] = pow( new_rms_phi[ibin]-ref_rms_phi[ibin], 2)/
		( new_rms_phi_err[ibin]*new_rms_phi_err[ibin] +
		  ref_rms_phi_err[ibin]*ref_rms_phi_err[ibin] );
	    }
	    TotalCHI2 += chi2_rms_phi[ibin];
	    TotalCHI2_rms_phi += chi2_rms_phi[ibin];
	    
	  } else { // fitted width, signed delta phi
	    
	    new_rms_phi[ibin]=0.0;
	    new_rms_phi_err[ibin]=0.0;
	    sprintf(name, "minuit_hZcandSignedDeltaPhi_Z_Recoil_bin_%d",ibin);
	    h=_histos.th1d(name);
	    
	    // signed phi imbalance fit
	    fsignedphi->FixParameter(2,0); 
	    fsignedphi->SetParameter(0, h->Integral()); 
	    fsignedphi->SetParameter(1, h->GetRMS());
	    h->Fit(fsignedphi,"0R");
	    fsignedphi->ReleaseParameter(2); 
	    fsignedphi->SetParameter(2, h->GetBinContent(1));
	    fsignedphi->SetParLimits(2, 0, 1e6);
	    h->Fit(fsignedphi,"0R");
	    new_rms_phi[ibin] = fsignedphi->GetParameter(1); // this is not a precise std.deviation yet !!!
	    new_rms_phi_err[ibin] = fsignedphi->GetParError(1);   
	    cout << "PMCS: PHI-IMBAL: PT-bin="<<ibin
		 << " fitted_width="<<new_rms_phi[ibin]<<" +- "<<new_rms_phi_err[ibin]<< endl<<flush;
	    
	    // 	ref_rms_phi[ibin]=ref_hist_phi[ibin]->GetRMS();
	    // 	ref_rms_phi_err[ibin]=ref_hist_phi[ibin]->GetRMSError();
	    // 	//       cout << "DATA: PHI-RESOL: PT-bin "<<ibin<<": chi2_contrib="<< ref_rms_phi[ibin]
	    // 	// 	   << ", totalentries="<<sumw<< endl;
	    
	    chi2_rms_phi[ibin] = 0.0;
	    if( ref_rms_phi_err[ibin]>0 || new_rms_phi_err[ibin]>0 ) {
	      chi2_rms_phi[ibin] = pow( new_rms_phi[ibin]-ref_rms_phi[ibin], 2)/
		( new_rms_phi_err[ibin]*new_rms_phi_err[ibin] +
		  ref_rms_phi_err[ibin]*ref_rms_phi_err[ibin] );
	    }
	    TotalCHI2 += chi2_rms_phi[ibin];
	    TotalCHI2_rms_phi += chi2_rms_phi[ibin];
	  }
	}
      }

      // ETA imbalance mean
      if(_Zminuit_ChiSquare_Method==0 || _Zminuit_ChiSquare_Method==3 ||
	 _Zminuit_ChiSquare_Method==4 || _Zminuit_ChiSquare_Method==5 ||
	 _Zminuit_ChiSquare_Method==9 || _Zminuit_ChiSquare_Method==10 ) {
	print_mean_etaimb=true;
	new_mean_etaimb[ibin]=0.0;
	new_mean_etaimb_err[ibin]=0.0;
	sprintf(name, "minuit_hZcandEtaImBalance_bin_%d",ibin);
	h=_histos.th1d(name);
	if(_Zminuit_UseFittedMeanWidth) {
	  cout << "FITTED-ETA-MEAN-BIN:"<<ibin<<": Before fitting feta"<<endl<<flush;
	  if(!eta_fit_done) {
	    // eta imbalance fit
	    feta->SetParameter(0, h->Integral()); 
	    feta->SetParameter(1, h->GetMean());
	    feta->SetParameter(2, h->GetRMS());
#if ( _USE_SINGLE_GAUSSIAN_ETAIMBAL_ )
	    h->Fit(feta,"0R");
#else
	    feta->FixParameter(3, 0);
	    feta->FixParameter(4, 0);
	    h->Fit(feta,"0RW");
	    feta->SetParLimits(3, 0, 1e6);
	    feta->SetParLimits(4, 0, 1);
	    h->Fit(feta,"0R");
#endif
	    eta_fit_done=true;
	  }
	  //	  cout << "FITTED-ETA-MEAN-BIN:"<<ibin<<": Getting fitted mean and width from feta"<<endl<<flush;
	  new_mean_etaimb[ibin] = feta->GetParameter(1);
	  new_mean_etaimb_err[ibin] = feta->GetParError(1);
#if ( _USE_SINGLE_GAUSSIAN_ETAIMBAL_ )
	  new_rms_etaimb[ibin] = feta->GetParameter(2);
	  new_rms_etaimb_err[ibin] = feta->GetParError(2);
#else
	  // SIGMA = sqrt( (1-Frac)*Sigma1^2 + Frac*Sigma2^2 )
	  // where Frac=P4, Sigma1=P2, Sigma2=P2+P3
	  new_rms_etaimb[ibin] = 
	    sqrt( (1-feta->GetParameter(4))*pow(feta->GetParameter(2), 2) +
		  feta->GetParameter(4)*pow(feta->GetParameter(2)+feta->GetParameter(3), 2) );
	  new_rms_etaimb_err[ibin] = 1/new_rms_etaimb[ibin]*
	    sqrt( pow( feta->GetParameter(3)*
		       (feta->GetParameter(2)+feta->GetParameter(3))*
		       feta->GetParError(4), 2) +
		  pow( (feta->GetParameter(2)+feta->GetParameter(4)*feta->GetParameter(3))*
		       feta->GetParError(2), 2) +
		  pow( feta->GetParameter(4)*(feta->GetParameter(2)+feta->GetParameter(3))*
		       feta->GetParError(3), 2) );
#endif
	  //	  cout << "FITTED-ETA-MEAN-BIN:"<<ibin<<": Printing fitted mean and width from feta"<<endl<<flush;
	  cout << "PMCS: ETA-IMBAL: PT-bin="<<ibin
	       <<": fitted_mean="<<new_mean_etaimb[ibin]<<" +- "<<new_mean_etaimb_err[ibin]<<endl<<flush;
	} else {	
	  new_mean_etaimb[ibin] = h->GetMean();
	  new_mean_etaimb_err[ibin] = h->GetMeanError();
	}
	// 	ref_mean_etaimb[ibin] = ref_hist_etaimb[ibin]->GetMean();
	// 	ref_mean_etaimb_err[ibin] = ref_hist_etaimb[ibin]->GetMeanError();

	//	cout << "ETA-MEAN-BIN:"<<ibin<<": calculating CHI2 started"<<endl<<flush;
	chi2_mean_etaimb[ibin] = 0.0;
	if( ref_mean_etaimb_err[ibin]>0 || new_mean_etaimb_err[ibin]>0 ) {
	  chi2_mean_etaimb[ibin] = pow( new_mean_etaimb[ibin]-ref_mean_etaimb[ibin], 2)/
	    ( new_mean_etaimb_err[ibin]*new_mean_etaimb_err[ibin] +
	      ref_mean_etaimb_err[ibin]*ref_mean_etaimb_err[ibin] );
	}
	TotalCHI2 += chi2_mean_etaimb[ibin];
	TotalCHI2_mean_etaimb += chi2_mean_etaimb[ibin];
	//	cout << "ETA-MEAN-BIN:"<<ibin<<": calculating CHI2 ended"<<endl<<flush;
      }

      // ETA imbalance width
      if(_Zminuit_ChiSquare_Method==0 || _Zminuit_ChiSquare_Method==3 ||
	 _Zminuit_ChiSquare_Method==6 || _Zminuit_ChiSquare_Method==7 ||
	 _Zminuit_ChiSquare_Method==9 || _Zminuit_ChiSquare_Method==10 ) {
	print_rms_etaimb=true;
	new_rms_etaimb[ibin]=0.0;
	new_rms_etaimb_err[ibin]=0.0;
	sprintf(name, "minuit_hZcandEtaImBalance_bin_%d",ibin);
	h=_histos.th1d(name);

	if(_Zminuit_UseFittedMeanWidth) {
	  cout << "FITTED-ETA-WIDTH-BIN:"<<ibin<<": Before fitting feta"<<endl<<flush;
	  if(!eta_fit_done) {
	    // eta imbalance fit
	    feta->SetParameter(0, h->Integral()); 
	    feta->SetParameter(1, h->GetMean());
	    feta->SetParameter(2, h->GetRMS());
#if ( _USE_SINGLE_GAUSSIAN_ETAIMBAL_ )
	    h->Fit(feta,"0R");
#else
	    feta->FixParameter(3, 0);
	    feta->FixParameter(4, 0);
	    h->Fit(feta,"0RW");
	    feta->SetParLimits(3, 0, 1e6);
	    feta->SetParLimits(4, 0, 1);
	    h->Fit(feta,"0R");
#endif
	    eta_fit_done=true;
	  }
	  //	  cout << "FITTED-ETA-WIDTH-BIN:"<<ibin<<": Getting fitted mean and width from feta"<<endl<<flush;
	  new_mean_etaimb[ibin] = feta->GetParameter(1);
	  new_mean_etaimb_err[ibin] = feta->GetParError(1);
#if ( _USE_SINGLE_GAUSSIAN_ETAIMBAL_ )
	  new_rms_etaimb[ibin] = feta->GetParameter(2);
	  new_rms_etaimb_err[ibin] = feta->GetParError(2);
#else
	  // SIGMA = sqrt( (1-Frac)*Sigma1^2 + Frac*Sigma2^2 )
	  // where Frac=P4, Sigma1=P2, Sigma2=P2+P3
	  new_rms_etaimb[ibin] = 
	    sqrt( (1-feta->GetParameter(4))*pow(feta->GetParameter(2), 2) +
		  feta->GetParameter(4)*pow(feta->GetParameter(2)+feta->GetParameter(3), 2) );
	  new_rms_etaimb_err[ibin] = 1/new_rms_etaimb[ibin]*
	    sqrt( pow( feta->GetParameter(3)*
		       (feta->GetParameter(2)+feta->GetParameter(3))*
		       feta->GetParError(4), 2) +
		  pow( (feta->GetParameter(2)+feta->GetParameter(4)*feta->GetParameter(3))*
		       feta->GetParError(2), 2) +
		  pow( feta->GetParameter(4)*(feta->GetParameter(2)+feta->GetParameter(3))*
		       feta->GetParError(3), 2) );
#endif
	  //	  cout << "FITTED-ETA-WIDTH-BIN:"<<ibin<<": Printing fitted mean and width from feta"<<endl<<flush;
	  cout << "PMCS: ETA-IMBAL: PT-bin="<<ibin
	       <<": fitted_width="<<new_rms_etaimb[ibin]<<" +- "<<new_rms_etaimb_err[ibin]<<endl<<flush;
	} else {	
	  new_rms_etaimb[ibin] = h->GetRMS();
	  new_rms_etaimb_err[ibin] = h->GetRMSError();
	}
	// 	ref_rms_etaimb[ibin] = ref_hist_etaimb[ibin]->GetRMS();
	// 	ref_rms_etaimb_err[ibin] = ref_hist_etaimb[ibin]->GetRMSError();

	//	cout << "ETA-WIDTH-BIN:"<<ibin<<": calculating CHI2 started"<<endl<<flush;
	chi2_rms_etaimb[ibin] = 0.0;
	if( ref_rms_etaimb_err[ibin]>0 || new_rms_etaimb_err[ibin]>0 ) {
	  chi2_rms_etaimb[ibin] = pow( new_rms_etaimb[ibin]-ref_rms_etaimb[ibin], 2)/
	    ( new_rms_etaimb_err[ibin]*new_rms_etaimb_err[ibin] +
	      ref_rms_etaimb_err[ibin]*ref_rms_etaimb_err[ibin] );
	}
	TotalCHI2 += chi2_rms_etaimb[ibin];
	TotalCHI2_rms_etaimb += chi2_rms_etaimb[ibin];
	//	cout << "ETA-WIDTH-BIN:"<<ibin<<": calculating CHI2 ended"<<endl<<flush;
      }

      // XI imbalance mean
      if(_Zminuit_ChiSquare_Method==3 || _Zminuit_ChiSquare_Method==5 ||
	 _Zminuit_ChiSquare_Method==10 ) {
	print_mean_xiimb=true;
	new_mean_xiimb[ibin]=0.0;
	new_mean_xiimb_err[ibin]=0.0;
	sprintf(name, "minuit_hZcandXiImBalance_bin_%d",ibin);
	h=_histos.th1d(name);

	if(_Zminuit_UseFittedMeanWidth) {
	  if(!xi_fit_done) {
	    // xi imbalance fit
	    fxi->FixParameter(2,0); 
	    fxi->SetParameter(0, h->Integral()); 
	    fxi->SetParameter(1, h->GetMean());
	    fxi->SetParameter(3, h->GetRMS());
	    fxi->SetParLimits(3, 0, 1e6);
	    h->Fit(fxi,"0R");   
	    fxi->ReleaseParameter(2); 
	    fxi->SetParLimits(2, 0, 1e6);
	    h->Fit(fxi,"0R");
	    xi_fit_done=true;
	  }
	  new_mean_xiimb[ibin] = fxi->GetParameter(1);
	  new_mean_xiimb_err[ibin] = fxi->GetParError(1);
	  new_rms_xiimb[ibin] = fxi->GetParameter(2)+fxi->GetParameter(3); // this is not a precise std.deviation yet !!!
	  new_rms_xiimb_err[ibin] = sqrt( fxi->GetParError(2)*fxi->GetParError(2) +
					  fxi->GetParError(3)*fxi->GetParError(3) );
	  cout << "PMCS:  XI-IMBAL: PT-bin="<<ibin
	       <<": fitted_mean="<<new_mean_xiimb[ibin]<<" +- "<<new_mean_xiimb_err[ibin]<<endl<<flush;
	} else {
	  new_mean_xiimb[ibin] = h->GetMean();
	  new_mean_xiimb_err[ibin] = h->GetMeanError();
	}
	//	ref_mean_xiimb[ibin] = ref_hist_xiimb[ibin]->GetMean();
	//	ref_mean_xiimb_err[ibin] = ref_hist_xiimb[ibin]->GetMeanError();

	chi2_mean_xiimb[ibin] = 0.0;
	if( ref_mean_xiimb_err[ibin]>0 || new_mean_xiimb_err[ibin]>0 ) {
	  chi2_mean_xiimb[ibin] = pow( new_mean_xiimb[ibin]-ref_mean_xiimb[ibin], 2)/
	  ( new_mean_xiimb_err[ibin]*new_mean_xiimb_err[ibin] +
	    ref_mean_xiimb_err[ibin]*ref_mean_xiimb_err[ibin] );
	}
	TotalCHI2 += chi2_mean_xiimb[ibin];
	TotalCHI2_mean_xiimb += chi2_mean_xiimb[ibin];
      }

      // XI imbalance width
      if(_Zminuit_ChiSquare_Method==3 || _Zminuit_ChiSquare_Method==7 ||
	 _Zminuit_ChiSquare_Method==10 ) {
	print_rms_xiimb=true;
	new_rms_xiimb[ibin]=0.0;
	new_rms_xiimb_err[ibin]=0.0;
	sprintf(name, "minuit_hZcandXiImBalance_bin_%d",ibin);
	h=_histos.th1d(name);

	if(_Zminuit_UseFittedMeanWidth) {
	  if(!xi_fit_done) {
	    // xi imbalance fit
	    fxi->FixParameter(2,0); 
	    fxi->SetParameter(0, h->Integral()); 
	    fxi->SetParameter(1, h->GetMean());
	    fxi->SetParameter(3, h->GetRMS());
	    fxi->SetParLimits(3, 0, 1e6);
	    h->Fit(fxi,"0R");   
	    fxi->ReleaseParameter(2); 
	    fxi->SetParLimits(2, 0, 1e6);
	    h->Fit(fxi,"0R");
	    xi_fit_done=true;
	  }
	  new_mean_xiimb[ibin] = fxi->GetParameter(1);
	  new_mean_xiimb_err[ibin] = fxi->GetParError(1);
	  new_rms_xiimb[ibin] = fxi->GetParameter(2)+fxi->GetParameter(3); // this is not a precise std.deviation yet !!!
	  new_rms_xiimb_err[ibin] = sqrt( fxi->GetParError(2)*fxi->GetParError(2) +
					  fxi->GetParError(3)*fxi->GetParError(3) );
	  cout << "PMCS:  XI-IMBAL: PT-bin="<<ibin
	       <<": fitted_width="<<new_rms_xiimb[ibin]<<" +- "<<new_rms_xiimb_err[ibin]<<endl<<flush;
	} else {
	  new_rms_xiimb[ibin] = h->GetRMS();
	  new_rms_xiimb_err[ibin] = h->GetRMSError();
	}
	//	ref_rms_xiimb[ibin] = ref_hist_xiimb[ibin]->GetRMS();
	//	ref_rms_xiimb_err[ibin] = ref_hist_xiimb[ibin]->GetRMSError();

	chi2_rms_xiimb[ibin] = 0.0;
	if( ref_rms_xiimb_err[ibin]>0 || new_rms_xiimb_err[ibin]>0 ) {
	  chi2_rms_xiimb[ibin] = pow( new_rms_xiimb[ibin]-ref_rms_xiimb[ibin], 2)/
	    ( new_rms_xiimb_err[ibin]*new_rms_xiimb_err[ibin] +
	      ref_rms_xiimb_err[ibin]*ref_rms_xiimb_err[ibin] );
	}
	TotalCHI2 += chi2_rms_xiimb[ibin];
	TotalCHI2_rms_xiimb += chi2_rms_xiimb[ibin];
      }

    } // end of for (ibin... loop

    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
//     cout<<"============================================="<<endl;
//     cout<<"Chi2 for Mean of Eta-Imbalance"<<endl;
//     for(int ibin=0; ibin<10; ibin++) {
//       cout<<"  Data: "<<ref_mean_etaimb[ibin]<<" +- "<<ref_mean_etaimb_err[ibin]
// 	  <<" MC: "<<new_mean_etaimb[ibin]<<" +- "<<new_mean_etaimb_err[ibin]
// 	  <<" chi2="<<chi2_mean_etaimb[ibin]<<endl;
//     }
//     cout<<"Overall chi2 = "<<TotalCHI2_mean_etaimb<<endl;
//     cout<<"============================================="<<endl;
//     cout<<"Chi2 for Width of Eta-Imbalance"<<endl;
//     for(int ibin=0; ibin<10; ibin++) {
//       cout<<"  Data: "<<ref_rms_etaimb[ibin]<<" +- "<<ref_rms_etaimb_err[ibin]
// 	  <<" MC: "<<new_rms_etaimb[ibin]<<" +- "<<new_rms_etaimb_err[ibin]
// 	  <<" chi2="<<chi2_rms_etaimb[ibin]<<endl;
//     }
//     cout<<"Overall chi2 = "<<TotalCHI2_rms_etaimb<<endl;
//     cout<<"============================================="<<endl;
//     cout<<"Chi2 for Mean of Xi-Imbalance"<<endl;
//     for(int ibin=0; ibin<10; ibin++) {
//       cout<<"  Data: "<<ref_mean_xiimb[ibin]<<" +- "<<ref_mean_xiimb_err[ibin]
// 	  <<" MC: "<<new_mean_xiimb[ibin]<<" +- "<<new_mean_xiimb_err[ibin]
// 	  <<" chi2="<<chi2_mean_xiimb[ibin]<<endl;
//     }
//     cout<<"Overall chi2 = "<<TotalCHI2_mean_xiimb<<endl;
//     cout<<"============================================="<<endl;
//     cout<<"Chi2 for Width of Xi-Imbalance"<<endl;
//     for(int ibin=0; ibin<10; ibin++) {
//       cout<<"  Data: "<<ref_rms_xiimb[ibin]<<" +- "<<ref_rms_xiimb_err[ibin]
// 	  <<" MC: "<<new_rms_xiimb[ibin]<<" +- "<<new_rms_xiimb_err[ibin]
// 	  <<" chi2="<<chi2_rms_xiimb[ibin]<<endl;
//     }
//     cout<<"Overall chi2 = "<<TotalCHI2_rms_xiimb<<endl;
//     cout<<"============================================="<<endl;
//     cout<<"Chi2 for Width of Phi-Imbalance"<<endl;
//     for(int ibin=0; ibin<10; ibin++) {
//       cout<<"  Data: "<<ref_rms_phi[ibin]<<" +- "<<ref_rms_phi_err[ibin]
// 	  <<" MC: "<<new_rms_phi[ibin]<<" +- "<<new_rms_phi_err[ibin]
// 	  <<" chi2="<<chi2_rms_phi[ibin]<<endl;
//     }
//     cout<<"Overall chi2 = "<<TotalCHI2_rms_phi<<endl;
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////

    // SUMMARY
    cout << setw(15) << "TOTAL CHI2"; 
    if(print_mean_etaimb) cout << setw(15) << "Mean(Eta imb)";; 
    if(print_rms_etaimb)  cout << setw(15) << "RMS(Eta imb)"; 
    if(print_mean_xiimb)  cout << setw(15) << "Mean(Xi imb)"; 
    if(print_rms_xiimb)   cout << setw(15) << "RMS(Xi imb)"; 
    if(print_rms_phiimb)  cout << setw(15) << "RMS(DPhi)";
    cout << endl; 
    cout << setw(15) << TotalCHI2; 
    if(print_mean_etaimb) cout << setw(15) << TotalCHI2_mean_etaimb; 
    if(print_rms_etaimb)  cout << setw(15) << TotalCHI2_rms_etaimb; 
    if(print_mean_xiimb)  cout << setw(15) << TotalCHI2_mean_xiimb; 
    if(print_rms_xiimb)   cout << setw(15) << TotalCHI2_rms_xiimb; 
    if(print_rms_phiimb)  cout << setw(15) << TotalCHI2_rms_phi;
    cout << endl;
    cout << "------------------------------------------------------------------------------------------"<<endl
	 << setw(15) << "CHI2 PER BIN"; 
    if(print_mean_etaimb) cout << setw(15) << "Mean(Eta imb)"; 
    if(print_rms_etaimb)  cout << setw(15) << "RMS(Eta imb)"; 
    if(print_mean_xiimb)  cout << setw(15) << "Mean(Xi imb)"; 
    if(print_rms_xiimb)   cout << setw(15) << "RMS(Xi imb)"; 
    if(print_rms_phiimb)  cout << setw(15) << "RMS(DPhi)";
    cout << endl;
    for(int ibin=0; ibin<10; ibin++) {
      cout << setw(14) << "BIN " << setw(1) << ibin; 
      if(print_mean_etaimb) cout << setw(15) << chi2_mean_etaimb[ibin]; 
      if(print_rms_etaimb)  cout << setw(15) << chi2_rms_etaimb[ibin]; 
      if(print_mean_xiimb)  cout << setw(15) << chi2_mean_xiimb[ibin]; 
      if(print_rms_xiimb)   cout << setw(15) << chi2_rms_xiimb[ibin]; 
      if(print_rms_phiimb)  cout << setw(15) << chi2_rms_phi[ibin];
      cout << endl;
    }
    break;
  }
  }; // end of switch(...)

  time_t t1=time(NULL);
  cout << "=========================================================================================="<<endl;
  cout << "Time at end of reprocessing: "<<ctime(&t1);
  cout << "Elapsed time: "<<(t1-t0)<<" sec"<<endl<<endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++ Begin of Master-Slave mode.
  //++ Display how many events reprocesed per job.
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if(_Zminuit_UseMasterSlaveMode) {
    cout << "Reprocessed: "<<nevts<<" events in job "<<_Zminuit_MasterSlave_Job<<endl;
    if(_Zminuit_MasterSlave_Job==1) {
      cout << "After recoil cuts: "<<npass<<" events from "<<_Zminuit_MasterSlave_Njobs<<" jobs"<<endl;
    } 
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++ End of Master-Slave mode.
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  } else {
    cout << "Reprocessed: "<<nevts<<" events"<<endl
	 << "After recoil cuts: "<<npass<<" events"<<endl<<endl; 
  }
  cout << "Total CHI2: "<<TotalCHI2<<endl
       << "=========================================================================================="<<endl
       << "=========================================================================================="<<endl;
  //
  // update progress report file
  //
  if(_Zminuit_ProgressReport_FileName!="") {
    fstream outfile(_Zminuit_ProgressReport_FileName.Data(), 
		    fstream::out | fstream::app);
    if(outfile.is_open()) {
      outfile.precision(5);
      outfile << scientific
	      << setw(13) << TotalCHI2                        
	      << setw(13) << raw_scale_HAD_bifurcate_A        
	      << setw(13) << raw_scale_HAD_bifurcate_B        
	      << setw(13) << raw_Relsampling_HAD_bifurcate_A  
	      << setw(13) << raw_Relsampling_HAD_bifurcate_B
	      << setw(13) << raw_Relphi_HAD_bifurcate_A
	      << setw(13) << raw_Relphi_HAD_bifurcate_B
	      << setw(13) << raw_alpha_mb
              << "  (" << npass << "=";
      for(Int_t ibin=0; ibin<10; ibin++)
        outfile << npass_perbin[ibin] << (ibin<9 ? "+" : ")");
      outfile << endl;
      outfile.close();
    }
  }

  // confirm that during first pass all
  // events have been stored into RAM if Zminuit_UseRAM=TRUE
  if(_Zminuit_UseRAM && !_Zminuit_RAMBuffer_Ready) {
    if(_Zminuit_RAMBuffer && _Zminuit_RAMBuffer_Nevts>0) 
      _Zminuit_RAMBuffer_Ready=true;
  }

  return TotalCHI2;
}

//
// construct standard FCN for MINUIT
//
ZAnalysis *MINUIT_ZAnalysis_ptr=NULL;
void minuit_fcn(Int_t &nvar, Double_t *grad, Double_t &chi2, Double_t *par, Int_t iflag)
{
  //
  // NOTE: NVAR is the number of variable parameters at a given time, not the
  //       total number of parameters. Size of arrays par[], grad[] is equal
  //       to the total number of parameters.
  //
  int ntot=MINUIT_ZAnalysis_ptr->MINUIT_getNpar();
  static int ncount=0;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
  cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag
       <<", NVAR="<<nvar<<", NTOT="<<ntot<<" - Started"<<endl;
    cout << "------------------------------------------------------------------"<<endl;
  switch(iflag) {
  case 0: // initialization
    ncount = 0;
    break;
  case 1: // minimization
  case 2: // post-processing
    break;
  };
  ncount++;
  //
  // substitute some default model parameters with
  // the ones given in par[] array
  //
  chi2 = -1.0;
  //////////////////////// DEBUG
  //
  //   cout << "PARAMS: " 
  //        << par[0] << ", " 
  //        << par[1] << ", " 
  //        << par[2] << ", " 
  //        << par[3] << ", " 
  //        << par[4] << ", " 
  //        << par[5] << ", " 
  //        << par[6] << endl;
  //
  //////////////////////// DEBUG

  if (MINUIT_ZAnalysis_ptr->MINUIT_UseGradient()/* && iflag==2 */) {
    cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag<<" - GRADIENT: " 
	 << "Compute central raw CHI2"<<endl;
  }

  // get parameter values
  double raw_scale_HAD_bifurcate_A = par[0];
  double raw_scale_HAD_bifurcate_B = par[1];
  double raw_scale_HAD_bifurcate_Tau = MINUIT_ZAnalysis_ptr->getRecoilSmear()->scale_HAD_bifurcate_Tau();
  double raw_Relsampling_HAD_bifurcate_A = par[2];
  double raw_Relsampling_HAD_bifurcate_B = par[3];
  double raw_Relconst_HAD_bifurcate = MINUIT_ZAnalysis_ptr->getRecoilSmear()->Relconst_HAD_bifurcate();
  double raw_Reltrans_HAD_bifurcate_RelRespTrans = MINUIT_ZAnalysis_ptr->getRecoilSmear()->Reltrans_HAD_bifurcate_RelRespTrans();
  double raw_Reltrans_HAD_bifurcate_RelResnTrans = MINUIT_ZAnalysis_ptr->getRecoilSmear()->Reltrans_HAD_bifurcate_RelResnTrans();
  double raw_Reltrans_HAD_bifurcate_RelTauTrans  = MINUIT_ZAnalysis_ptr->getRecoilSmear()->Reltrans_HAD_bifurcate_RelTauTrans();
  double raw_Relphi_HAD_bifurcate_A = par[4];
  double raw_Relphi_HAD_bifurcate_B = par[5];
  double raw_RelconstPhi_HAD_bifurcate = MINUIT_ZAnalysis_ptr->getRecoilSmear()->RelconstPhi_HAD_bifurcate();
  double raw_alpha_mb = par[6];
  double raw_alpha_zb = MINUIT_ZAnalysis_ptr->getRecoilSmear()->alpha_zb();
   
  // compute CHI2 at X=X0
  chi2 = MINUIT_ZAnalysis_ptr->MINUIT_calc_chi2
    ( raw_scale_HAD_bifurcate_A,
      raw_scale_HAD_bifurcate_B,
      raw_scale_HAD_bifurcate_Tau,
      raw_Relsampling_HAD_bifurcate_A,
      raw_Relsampling_HAD_bifurcate_B,
      raw_Relconst_HAD_bifurcate,
      raw_Reltrans_HAD_bifurcate_RelRespTrans,
      raw_Reltrans_HAD_bifurcate_RelResnTrans,
      raw_Reltrans_HAD_bifurcate_RelTauTrans,
      raw_Relphi_HAD_bifurcate_A,
      raw_Relphi_HAD_bifurcate_B,
      raw_RelconstPhi_HAD_bifurcate,
      raw_alpha_mb,
      raw_alpha_zb );
  
  cout << "------------------------------------------------------------------"<<endl;
  if (MINUIT_ZAnalysis_ptr->MINUIT_UseGradient()/* && iflag==2 */) {
    ////////////////////////////////////////////////////////////////////////////
    //
    // For gradient method also need to scan CHI2 at: X0-2h, X0-h, X0+h, X0+2h
    // for each dimension (except for fixed parameters).
    //
    double chi2_smooth[ntot];
    double chi2_gradient[ntot];

    // loop over all parameters
    for(int ipar=0; ipar<ntot; ipar++) {

      // initialize gradient to 0 (e.g. fixed parameter)
      chi2_smooth[ipar]=-1.0;
      chi2_gradient[ipar]=0.0;

      // compute first derivative for non-fixed parameters
      if(!MINUIT_ZAnalysis_ptr->MINUIT_ParIsFixed(ipar)) {

	cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag<<" - GRADIENT: " 
	     << "PAR"<<ipar<<": Is not fixed"<<endl;

	// sample CHI2 at nearby points: X0-2h, X0-h, X0, X0+h, X0+2h
	double chi2_point[5];
	double par_step=MINUIT_ZAnalysis_ptr->MINUIT_ParStepSize(ipar);

	cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag<<" - GRADIENT: " 
	     << "PAR"<<ipar<<": Step size is: "<<par_step<<endl;

	// NOTE: CHI2 at X=X0 is already known!
	chi2_point[2] = chi2;

	// compute CHI2 at 4 additional points
	for(int ipoint=0; ipoint<5; ipoint++) if (ipoint!=2) {

	  // initialize all parameters to nominal values X=X0
	  double par_scan[ntot];
	  for(int ipar_X0=0; ipar_X0<ntot; ipar_X0++) par_scan[ipar_X0]=par[ipar_X0];
	  
	  // change only parameter corresponding to IPAR
	  par_scan[ipar] = par[ipar] + (ipoint-2)*par_step;
	  cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag<<" - GRADIENT: " 
	       << "PAR"<<ipar<<": IPOINT="<<ipoint<<", new PAR"<<ipar<<"="<<par_scan[ipar]<<endl;

	  // get parameters
	  double raw_scale_HAD_bifurcate_A = par_scan[0];
	  double raw_scale_HAD_bifurcate_B = par_scan[1];
	  double raw_Relsampling_HAD_bifurcate_A = par_scan[2];
	  double raw_Relsampling_HAD_bifurcate_B = par_scan[3];
	  double raw_Relconst_HAD_bifurcate = MINUIT_ZAnalysis_ptr->getRecoilSmear()->Relconst_HAD_bifurcate();
	  double raw_Reltrans_HAD_bifurcate_RelRespTrans = MINUIT_ZAnalysis_ptr->getRecoilSmear()->Reltrans_HAD_bifurcate_RelRespTrans();
	  double raw_Reltrans_HAD_bifurcate_RelResnTrans = MINUIT_ZAnalysis_ptr->getRecoilSmear()->Reltrans_HAD_bifurcate_RelResnTrans();
	  double raw_Reltrans_HAD_bifurcate_RelTauTrans  = MINUIT_ZAnalysis_ptr->getRecoilSmear()->Reltrans_HAD_bifurcate_RelTauTrans();
	  double raw_Relphi_HAD_bifurcate_A = par_scan[4];
	  double raw_Relphi_HAD_bifurcate_B = par_scan[5];
	  double raw_RelconstPhi_HAD_bifurcate = MINUIT_ZAnalysis_ptr->getRecoilSmear()->RelconstPhi_HAD_bifurcate();
	  double raw_alpha_mb = par_scan[6];
	  double raw_alpha_zb = MINUIT_ZAnalysis_ptr->getRecoilSmear()->alpha_zb();
	  
	  // compute CHI2 at new point
	  cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag<<" - GRADIENT: " 
	       << "PAR"<<ipar<<": IPOINT="<<ipoint<<", Compute neighbor raw CHI2"<<endl;
	  chi2_point[ipoint] = MINUIT_ZAnalysis_ptr->MINUIT_calc_chi2
	    ( raw_scale_HAD_bifurcate_A,
	      raw_scale_HAD_bifurcate_B,
	      raw_scale_HAD_bifurcate_Tau,
	      raw_Relsampling_HAD_bifurcate_A,
	      raw_Relsampling_HAD_bifurcate_B,
	      raw_Relconst_HAD_bifurcate,
	      raw_Reltrans_HAD_bifurcate_RelRespTrans,
	      raw_Reltrans_HAD_bifurcate_RelResnTrans,
	      raw_Reltrans_HAD_bifurcate_RelTauTrans,
	      raw_Relphi_HAD_bifurcate_A,
	      raw_Relphi_HAD_bifurcate_B,
	      raw_RelconstPhi_HAD_bifurcate,
	      raw_alpha_mb,
	      raw_alpha_zb );
	} // end of ipoint loop

	cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag<<" - GRADIENT: " 
	     << "PAR"<<ipar<<": 5 CHI2 points: ";
	for(int ipoint=0; ipoint<5; ipoint++) cout<<chi2_point[ipoint]<<" ";
	cout << endl;

	// use convolution ceofficients for a quadratic polynomial
	// Y(x)  = a0 + a1*z + a2*z^2   (=a0 at   z=0) 
	// dY/dx = (a1 + 2*a2*z)/h      (=a1/h at z=0)
	// where: h = is a step between 5 equally spaced data points along x
	//        z = (x-x0)/h
	//        x0 = central point
	//        a0...a3 = convolution coefficients by Savitzky and Golay (1964).
	double a0 = (  -3.*chi2_point[0] 
		      +12.*chi2_point[1]
		      +17.*chi2_point[2]
		      +12.*chi2_point[3]
		       -3.*chi2_point[4] ) / 35.;
	double a1 = (  -2.*chi2_point[0] 
		       -1.*chi2_point[1]
		       +1.*chi2_point[3]
		       +2.*chi2_point[4] ) / 10.;
 	double a2 = (   2.*chi2_point[0] 
 		       -1.*chi2_point[1]
 		       -2.*chi2_point[2]
 		       -1.*chi2_point[3]
 		       +2.*chi2_point[4] ) / 14.;
	
	cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag<<" - GRADIENT: " 
	     << "PAR"<<ipar<<": a0,a1,a3 convol.coeff: "<<a0<<" "<<a1<<" "<<a2<<endl;

	chi2_gradient[ipar] = a1/par_step;
	chi2_smooth[ipar] = a0;

	cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag<<" - GRADIENT: " 
	     << "PAR"<<ipar<<": GRAD="<<chi2_gradient[ipar]<<", CHI2_SMOOTH="<<chi2_smooth[ipar]<<endl;

	if(grad) grad[ipar] = chi2_gradient[ipar];

      } // end of if(...IsFixed....
    } // end of ipar loop

    // print coordinates of the phase space point X0 alongwith first derivatives
    double chi2_smooth_ave=0.0;
    int nvar_smooth=0;
    for(int ipar=0; ipar<ntot; ipar++) {
      cout 
	<< "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag
	<<" PAR"<<ipar<<"="<<setw(10)<<par[ipar];
      if(!MINUIT_ZAnalysis_ptr->MINUIT_ParIsFixed(ipar)) {
	cout
	<<" dCHI2/dPAR"<<ipar<<"="<<setw(10)<<chi2_gradient[ipar]
	<<" CHI2_SMOOTHED="<<setw(10)<<chi2_smooth[ipar]<<endl;
	chi2_smooth_ave += chi2_smooth[ipar];
	nvar_smooth++;
      } else {
	cout <<" is fixed"<<endl;
      }
    }
    // substitute raw CHI2 with average smooth chi2
    double chi2_raw=chi2;
    if(nvar_smooth>0) {
      chi2_smooth_ave/=nvar_smooth;
      chi2=chi2_smooth_ave;
    }

    // print CHI2 at phase space point X=X0
    cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag
	 <<", CHI2="<<setw(10)<<chi2
	 <<" (CHI2_RAW="<<chi2_raw<<", AVERAGE_SMOOTH_CHI2="<<chi2_smooth_ave<<")"<<endl;
    //
    ////////////////////////////////////////////////////////////////////////////
  } else {
    // print coordinates of the phase space point X0
    for(int ipar=0; ipar<ntot; ipar++) {
      cout 
	<< "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag<<", PAR"<<ipar<<"="<<par[ipar]<<endl;
    }
    // print CHI2 at phase space point X=X0
    cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag<<", CHI2="<<setw(10)<<chi2<<endl;
  }
  cout << "------------------------------------------------------------------"<<endl;
  cout << "minuit_fcn:ITER="<<ncount<<", IFLAG="<<iflag
       <<", NVAR="<<nvar<<", NTOT="<<ntot<<" - Ended"<<endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
}

void ZAnalysis::MINUIT_setTRandom3(TRandom3 *dummy) {
  _Zminuit_TRandom3 = dummy;
}
TRandom3 *ZAnalysis::MINUIT_getTRandom3() {
  return _Zminuit_TRandom3;
}
void ZAnalysis::MINUIT_setNevts(int nevts) {
  _Zminuit_EventBuffer_Nevts = nevts;
}
int ZAnalysis::MINUIT_getNevts() {
  return _Zminuit_EventBuffer_Nevts;
}
void ZAnalysis::MINUIT_getClassPointer(ZAnalysis* &ptr) {
  ptr = this;
}

bool ZAnalysis::MINUIT_skipPreselection() {
  return  _HadronicMomentum_AllAtOnce_BifurcateStudy && _Zminuit_Skip_Event_Preselection;
}

int ZAnalysis::MINUIT_WriteRAM(char *buffer,
			       std::vector<PMCSEMObj> &emobjs_smear, 
			       PMCSRecoil &recoil_gen, 
			       PMCSVtx &vtx_gen, 
			       double &evtweight,
			       double &luminosity, 
			       int &runno, 
			       int &zbindex, 
			       int &mbindex, 
			       double &pt_resol, 
			       double &delta_phi,
			       double &upara_rnd1,
			       double &upara_rnd2,
			       double &SET_rnd, 
			       double &znunu_SET_Hard, 
			       double &znunu_SET_Hard_expected,
                               double &given_tbdmetx,
                               double &given_tbdmety) {
  int bytes=0;
  int nem = emobjs_smear.size();
  memcpy(buffer, &nem, sizeof(nem)); bytes += sizeof(nem); 
  for(int i=0;i<nem; i++) {
    memcpy(buffer+bytes, &emobjs_smear[i], sizeof(emobjs_smear[i])); bytes += sizeof(emobjs_smear[i]); 
  }
  memcpy(buffer+bytes, &recoil_gen, sizeof(recoil_gen)); bytes += sizeof(recoil_gen); 
  memcpy(buffer+bytes, &vtx_gen, sizeof(vtx_gen));       bytes += sizeof(vtx_gen); 
  memcpy(buffer+bytes, &evtweight, sizeof(evtweight));   bytes += sizeof(evtweight); 
  memcpy(buffer+bytes, &luminosity, sizeof(luminosity)); bytes += sizeof(luminosity); 
  memcpy(buffer+bytes, &runno, sizeof(runno));           bytes += sizeof(runno); 
  memcpy(buffer+bytes, &zbindex, sizeof(zbindex));       bytes += sizeof(zbindex); 
  memcpy(buffer+bytes, &mbindex, sizeof(mbindex));       bytes += sizeof(mbindex); 
  // Write pre-smeared hard recoil component from pure Z->nu+nu full MC without any fudging applied.
  // This vector is used later if option Zminuit_Skip_Znunu_Randomization=TRUE. 
  memcpy(buffer+bytes, &pt_resol, sizeof(pt_resol));  bytes += sizeof(pt_resol); 
  memcpy(buffer+bytes, &delta_phi, sizeof(delta_phi));bytes += sizeof(delta_phi); 
  memcpy(buffer+bytes, &upara_rnd1, sizeof(upara_rnd1));bytes += sizeof(upara_rnd1); 
  memcpy(buffer+bytes, &upara_rnd2, sizeof(upara_rnd2));bytes += sizeof(upara_rnd2); 
  memcpy(buffer+bytes, &SET_rnd, sizeof(SET_rnd));bytes += sizeof(SET_rnd); 
  memcpy(buffer+bytes, &znunu_SET_Hard, sizeof(znunu_SET_Hard));bytes += sizeof(znunu_SET_Hard); 
  memcpy(buffer+bytes, &znunu_SET_Hard_expected, sizeof(znunu_SET_Hard_expected));bytes += sizeof(znunu_SET_Hard_expected); 
  memcpy(buffer+bytes, &given_tbdmetx, sizeof(given_tbdmetx));bytes += sizeof(given_tbdmetx); 
  memcpy(buffer+bytes, &given_tbdmety, sizeof(given_tbdmety));bytes += sizeof(given_tbdmety); 
  return bytes;
}
int ZAnalysis::MINUIT_ReadRAM(char *buffer,
			      std::vector<PMCSEMObj> &emobjs_smear, 
			      PMCSRecoil &recoil_gen, 
			      PMCSVtx &vtx_gen, 
			      double &evtweight,
			      double &luminosity, 
			      int &runno, 
			      int &zbindex, 
			      int &mbindex, 
			      double &pt_resol, 
			      double &delta_phi,
			      double &upara_rnd1,
			      double &upara_rnd2,
			      double &SET_rnd, 
			      double &znunu_SET_Hard, 
			      double &znunu_SET_Hard_expected,
                              double &given_tbdmetx,
                              double &given_tbdmety) {
  int bytes=0;
  int nem=0;
  memcpy(&nem, buffer, sizeof(nem)); bytes += sizeof(nem); 
  for(int i=0;i<nem; i++) {
    PMCSEMObj em;
    memcpy(&em, buffer+bytes, sizeof(em)); bytes += sizeof(em); 
    emobjs_smear.push_back(em);
  }
  memcpy(&recoil_gen, buffer+bytes, sizeof(recoil_gen)); bytes += sizeof(recoil_gen); 
  memcpy(&vtx_gen, buffer+bytes, sizeof(vtx_gen));       bytes += sizeof(vtx_gen); 
  memcpy(&evtweight, buffer+bytes, sizeof(evtweight));   bytes += sizeof(evtweight); 
  memcpy(&luminosity, buffer+bytes, sizeof(luminosity)); bytes += sizeof(luminosity); 
  memcpy(&runno, buffer+bytes, sizeof(runno));           bytes += sizeof(runno); 
  memcpy(&zbindex, buffer+bytes, sizeof(zbindex));       bytes += sizeof(zbindex); 
  memcpy(&mbindex, buffer+bytes, sizeof(mbindex));       bytes += sizeof(mbindex); 
  // Read pre-smeared hard recoil component from pure Z->nu+nu full MC without any fudging applied.
  // This vector is used later if option Zminuit_Skip_Znunu_Randomization=TRUE. 
  memcpy(&pt_resol, buffer+bytes, sizeof(pt_resol));  bytes += sizeof(pt_resol); 
  memcpy(&delta_phi, buffer+bytes, sizeof(delta_phi));bytes += sizeof(delta_phi); 
  memcpy(&upara_rnd1, buffer+bytes, sizeof(upara_rnd1));bytes += sizeof(upara_rnd1); 
  memcpy(&upara_rnd2, buffer+bytes, sizeof(upara_rnd2));bytes += sizeof(upara_rnd2); 
  memcpy(&SET_rnd, buffer+bytes, sizeof(SET_rnd));bytes += sizeof(SET_rnd); 
  memcpy(&znunu_SET_Hard, buffer+bytes, sizeof(znunu_SET_Hard));bytes += sizeof(znunu_SET_Hard); 
  memcpy(&znunu_SET_Hard_expected, buffer+bytes, sizeof(znunu_SET_Hard_expected));bytes += sizeof(znunu_SET_Hard_expected); 
  memcpy(&given_tbdmetx, buffer+bytes, sizeof(given_tbdmetx));bytes += sizeof(given_tbdmetx); 
  memcpy(&given_tbdmety, buffer+bytes, sizeof(given_tbdmety));bytes += sizeof(given_tbdmety); 
  return bytes;
}
int ZAnalysis::MINUIT_WriteFile(std::vector<PMCSEMObj> &emobjs_smear, 
				PMCSRecoil &recoil_gen, 
				PMCSVtx &vtx_gen, 
				double &evtweight,
				double &luminosity, 
				int &runno, 
				int &zbindex, 
				int &mbindex, 
				double &pt_resol, 
				double &delta_phi,
				double &upara_rnd1,
				double &upara_rnd2,
				double &SET_rnd, 
				double &znunu_SET_Hard, 
				double &znunu_SET_Hard_expected,
				double &given_tbdmetx,
				double &given_tbdmety) {
  int bytes=0;
  int nem=emobjs_smear.size();
  bytes += sizeof(nem)*fwrite(&nem, sizeof(nem), 1, _Zminuit_EventBuffer_File);
  for(int i=0;i<nem; i++) {
    bytes += sizeof(emobjs_smear[i])*fwrite(&emobjs_smear[i], sizeof(emobjs_smear[i]), 1, _Zminuit_EventBuffer_File);
  }
  bytes += sizeof(recoil_gen)*fwrite(&recoil_gen, sizeof(recoil_gen), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(vtx_gen)*fwrite(&vtx_gen, sizeof(vtx_gen), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(evtweight)*fwrite(&evtweight, sizeof(evtweight), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(luminosity)*fwrite(&luminosity, sizeof(luminosity), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(runno)*fwrite(&runno, sizeof(runno), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(zbindex)*fwrite(&zbindex, sizeof(zbindex), 1, _Zminuit_EventBuffer_File);    
  bytes += sizeof(mbindex)*fwrite(&mbindex, sizeof(mbindex), 1, _Zminuit_EventBuffer_File);
  // Write pre-smeared hard recoil component from pure Z->nu+nu full MC without any fudging applied.
  // This vector is used later if option Zminuit_Skip_Znunu_Randomization=TRUE. 
  bytes += sizeof(pt_resol)*fwrite(&pt_resol, sizeof(pt_resol), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(delta_phi)*fwrite(&delta_phi, sizeof(delta_phi), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(upara_rnd1)*fwrite(&upara_rnd1, sizeof(upara_rnd1), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(upara_rnd2)*fwrite(&upara_rnd2, sizeof(upara_rnd2), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(SET_rnd)*fwrite(&SET_rnd, sizeof(SET_rnd), 2, _Zminuit_EventBuffer_File);
  bytes += sizeof(znunu_SET_Hard)*fwrite(&znunu_SET_Hard, sizeof(znunu_SET_Hard), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(znunu_SET_Hard_expected)*fwrite(&znunu_SET_Hard_expected, sizeof(znunu_SET_Hard_expected), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(given_tbdmetx)*fwrite(&given_tbdmetx, sizeof(given_tbdmetx), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(given_tbdmety)*fwrite(&given_tbdmety, sizeof(given_tbdmety), 1, _Zminuit_EventBuffer_File);
  return bytes;
}
int ZAnalysis::MINUIT_ReadFile(std::vector<PMCSEMObj> &emobjs_smear, 
			       PMCSRecoil &recoil_gen, 
			       PMCSVtx &vtx_gen, 
			       double &evtweight,
			       double &luminosity, 
			       int &runno, 
			       int &zbindex, 
			       int &mbindex, 
			       double &pt_resol, 
			       double &delta_phi,
			       double &upara_rnd1,
			       double &upara_rnd2,
			       double &SET_rnd, 
			       double &znunu_SET_Hard, 
			       double &znunu_SET_Hard_expected,
                               double &given_tbdmetx,
                               double &given_tbdmety) {
  int bytes=0;
  int nem=0;
  bytes += sizeof(nem)*fread(&nem, sizeof(nem), 1, _Zminuit_EventBuffer_File); 
  for(int i=0;i<nem; i++) {
    PMCSEMObj em;
    bytes += sizeof(em)*fread(&em, sizeof(em), 1, _Zminuit_EventBuffer_File); 
    emobjs_smear.push_back(em);
  }
  bytes += sizeof(recoil_gen)*fread(&recoil_gen, sizeof(recoil_gen), 1, _Zminuit_EventBuffer_File); 
  bytes += sizeof(vtx_gen)*fread(&vtx_gen, sizeof(vtx_gen), 1, _Zminuit_EventBuffer_File); 
  bytes += sizeof(evtweight)*fread(&evtweight, sizeof(evtweight), 1, _Zminuit_EventBuffer_File); 
  bytes += sizeof(luminosity)*fread(&luminosity, sizeof(luminosity), 1, _Zminuit_EventBuffer_File); 
  bytes += sizeof(runno)*fread(&runno, sizeof(runno), 1, _Zminuit_EventBuffer_File); 
  bytes += sizeof(zbindex)*fread(&zbindex, sizeof(zbindex), 1, _Zminuit_EventBuffer_File); 
  bytes += sizeof(mbindex)*fread(&mbindex, sizeof(mbindex), 1, _Zminuit_EventBuffer_File); 
  // Read pre-smeared hard recoil component from pure Z->nu+nu full MC without any fudging applied.
  // This vector is used later if option Zminuit_Skip_Znunu_Randomization=TRUE. 
  bytes += sizeof(pt_resol)*fread(&pt_resol, sizeof(pt_resol), 1, _Zminuit_EventBuffer_File); 
  bytes += sizeof(delta_phi)*fread(&delta_phi, sizeof(delta_phi), 1, _Zminuit_EventBuffer_File); 
  bytes += sizeof(upara_rnd1)*fread(&upara_rnd1, sizeof(upara_rnd1), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(upara_rnd2)*fread(&upara_rnd2, sizeof(upara_rnd2), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(SET_rnd)*fread(&SET_rnd, sizeof(SET_rnd), 2, _Zminuit_EventBuffer_File);
  bytes += sizeof(znunu_SET_Hard)*fread(&znunu_SET_Hard, sizeof(znunu_SET_Hard), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(znunu_SET_Hard_expected)*fread(&znunu_SET_Hard_expected, sizeof(znunu_SET_Hard_expected), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(given_tbdmetx)*fread(&given_tbdmetx, sizeof(given_tbdmetx), 1, _Zminuit_EventBuffer_File);
  bytes += sizeof(given_tbdmety)*fread(&given_tbdmety, sizeof(given_tbdmety), 1, _Zminuit_EventBuffer_File);
  return bytes;
}
void ZAnalysis::MINUIT_reprocess(int maxevts, 
				 TRandom3 *dummy) {
  if(maxevts<0) return; // 0 = all events
  //  int nevts = ( _Zminuit_EventBuffer_Nevts<maxevts ? _Zminuit_EventBuffer_Nevts : maxevts );
  int nevts = maxim(0, maxevts);
  bool print_errors=false;

  cout << "=================================================================="<<endl;
  cout << "Started re-processing" << endl;
  cout << "=================================================================="<<endl;

  //
  // get default model parameters and use them as a starting point for
  // MINUIT minimization of the total CHI2 as defined by _Zminuit_ChiSquare_Method.
  //
  double raw_scale_HAD_bifurcate_A = _recoilsmear->scale_HAD_bifurcate_A();
  double raw_scale_HAD_bifurcate_B = _recoilsmear->scale_HAD_bifurcate_B();
  double raw_Relsampling_HAD_bifurcate_A = _recoilsmear->Relsampling_HAD_bifurcate_A();
  double raw_Relsampling_HAD_bifurcate_B = _recoilsmear->Relsampling_HAD_bifurcate_B();
  double raw_Relconst_HAD_bifurcate = _recoilsmear->Relconst_HAD_bifurcate();
  double raw_Relphi_HAD_bifurcate_A = _recoilsmear->Relphi_HAD_bifurcate_A();
  double raw_Relphi_HAD_bifurcate_B = _recoilsmear->Relphi_HAD_bifurcate_B();
  double raw_RelconstPhi_HAD_bifurcate = _recoilsmear->RelconstPhi_HAD_bifurcate();
  double raw_alpha_mb = _recoilsmear->alpha_mb();
  double raw_alpha_zb = _recoilsmear->alpha_zb();  
  MINUIT_setTRandom3(dummy);

  cout << " Will analyze " << nevts << " preselected events"
       << " (internal nevts=" <<nevts
       <<", input maxevts="<<maxevts
       <<" _Zminuit_EventBuffer_Nevts="<<_Zminuit_EventBuffer_Nevts<<")"<<endl;
 
  MINUIT_setNevts(nevts);
  extern ZAnalysis *MINUIT_ZAnalysis_ptr;
  extern void minuit_fcn(Int_t&, Double_t*, Double_t&, Double_t*, Int_t);
  MINUIT_getClassPointer(MINUIT_ZAnalysis_ptr);
  // clear 
  if(_Zminuit_RAMBuffer) free(_Zminuit_RAMBuffer);
  _Zminuit_RAMBuffer = NULL;
  _Zminuit_RAMBuffer_Ready = false;
  _Zminuit_RAMBuffer_Nevts = 0;

  cout << " After MINUIT_getClassPointer: MINUIT_ZAnalysis_ptr=" << MINUIT_ZAnalysis_ptr << endl;
  cout << " After MINUIT_getClassPointer:                 this=" << this << endl;

  //
  // open (truncate) event buffer file for reading 
  //
  if(_Zminuit_ProgressReport_FileName!="") {
    fstream outfile(_Zminuit_ProgressReport_FileName.Data(), 
		    fstream::out | fstream::trunc);
    outfile.close();
  }

  if(!_Zminuit_UseMasterSlaveMode ||
     (_Zminuit_UseMasterSlaveMode && _Zminuit_MasterSlave_Job==1)) {

    //___________________
    // Search for minimum
    //
    const int Npar=7;
    MINUIT_setNpar(Npar);
    TMinuit *gMinuit = new TMinuit(Npar);
    gMinuit->SetFCN(minuit_fcn);                                                        
    
    Double_t amin,edm,errdef;                                                    
    Int_t nvpar,nparx,icstat;                                                    
    Double_t arglist[10];                                                        
    Int_t ierflg = 0;                                                            
    
    arglist[0] = -1.;
    gMinuit -> mnexcm("SET PRINT", arglist, 1, ierflg);
    
    // SET ERR initializes the error definition...
    // Sets the value of UP (default value= 1.), defining parameter errors. 
    // Minuit defines parameter errors as the change in parameter value 
    // required to change the function value by UP. Normally, for chisquared 
    // fits UP=1, and for negative log likelihood, UP=0.5.
    //   Usage: the above function executes the command, tells it to read the
    //   (one) recquisite parameter from the "arglist" array, tells it only 
    //   to read one argument, and defines ierflag as the error flag.
    arglist[0] = 1.0; 
    gMinuit->mnexcm("SET ERR", arglist , 1, ierflg);
    
    // Set starting values and step sizes for 2 parameters
    const char *Parname[Npar]={ 
      "Scale_A",
      "Scale_B",
      "Sampl_A",
      "Sampl_B",
      "RelPhi_A",
      "RelPhi_B",
      "Alpha_MB" };
    
    const double RangeMin[Npar] = {
      _Zminuit_RANGE_Relscale_A[0],
      _Zminuit_RANGE_Relscale_B[0],
      _Zminuit_RANGE_Relsampling_A[0],
      _Zminuit_RANGE_Relsampling_B[0],
      _Zminuit_RANGE_Relphi_A[0],
      _Zminuit_RANGE_Relphi_B[0],
      _Zminuit_RANGE_Alpha_MB[0]
    };
    
    const double RangeMax[Npar] = {
      _Zminuit_RANGE_Relscale_A[1],
      _Zminuit_RANGE_Relscale_B[1],
      _Zminuit_RANGE_Relsampling_A[1],
      _Zminuit_RANGE_Relsampling_B[1],
      _Zminuit_RANGE_Relphi_A[1],
      _Zminuit_RANGE_Relphi_B[1],
      _Zminuit_RANGE_Alpha_MB[1]
    };
    
    const double Start[Npar] = {
      _Zminuit_START_Relscale_A,
      _Zminuit_START_Relscale_B,
      _Zminuit_START_Relsampling_A,
      _Zminuit_START_Relsampling_B,
      _Zminuit_START_Relphi_A,
      _Zminuit_START_Relphi_B,
      _Zminuit_START_Alpha_MB
    };

    const double Step[Npar] = { 
      _Zminuit_STEP_Relscale_A,
      _Zminuit_STEP_Relscale_B,
      _Zminuit_STEP_Relsampling_A,
      _Zminuit_STEP_Relsampling_B,
      _Zminuit_STEP_Relphi_A,
      _Zminuit_STEP_Relphi_B,
      _Zminuit_STEP_Alpha_MB
    };

    arglist[0] = 3; // maximal debugging
    gMinuit->mnexcm("SET PRI", arglist, 1, ierflg);
    
    _Zminuit_ParIsFixed.resize(0);
    _Zminuit_ParStepSize.resize(0);
    for(int ipar=0; ipar<Npar; ipar++) {
      _Zminuit_ParStepSize.push_back(Step[ipar]);
      if(RangeMin[ipar]==RangeMax[ipar]) { // this parameter is fixed
	_Zminuit_ParIsFixed.push_back(true);
	gMinuit->mnparm(ipar,Parname[ipar],Start[ipar],Step[ipar],0,0,ierflg);
	arglist[0] = ipar+1;
	gMinuit->mnexcm("FIX", arglist , 1, ierflg);
      } else { // this parameter is not fixed, but... 
	_Zminuit_ParIsFixed.push_back(false);
	if(_Zminuit_RANGE_Unlimited) {
	  // ...is unlimited
	  gMinuit->mnparm(ipar,Parname[ipar],Start[ipar],Step[ipar],0,0,ierflg);
	} else {
	  // ...is limited
	  gMinuit->mnparm(ipar,Parname[ipar],Start[ipar],Step[ipar],
			  RangeMin[ipar],RangeMax[ipar],ierflg);
	}
      }
    }
    
    if(_Zminuit_do_SCAN) { 
      print_errors=false;
      int ipar=_Zminuit_do_SCAN_IPAR;  // 0=RelScaleA, 1=RelScaleB, etc
      if(ipar>=Npar) {
	cout << "MINUIT_reprocess: Zminuit_do_SCAN_IPAR="<<_Zminuit_do_SCAN_IPAR
	     <<" is not in allowed range of [0, "<<Npar-1<<"] !!!"<<endl;
	throw;
      }
      cout << "=================================================================="<<endl;
      cout << "SCANNING " << Parname[ipar] << " PARAMETER." << endl;
      
      // because MINUIT's 'SCAN' command is limited to 100 iterations per call
      // we will evaluate CHI2 function manually in a loop.
      if(_Zminuit_do_SCAN_NSTEPS>1) 
	for(Int_t iter=0; iter<_Zminuit_do_SCAN_NSTEPS; iter++) {
	  
	  // get parameters
	  Double_t* gpar = new Double_t[Npar];
	  Double_t* gerr = new Double_t[Npar];
	  for(Int_t jpar=0; jpar<Npar; jpar++) {
	    if(jpar!=ipar) {
	      gMinuit -> GetParameter(jpar, gpar[jpar], gerr[jpar]);
	    } else {
	      gpar[ipar]=RangeMin[ipar]+((double)iter)/((double)(_Zminuit_do_SCAN_NSTEPS-1))*(RangeMax[ipar]-RangeMin[ipar]);
	      gerr[ipar]=0.0;
	    }
	  } 
	  // evaluate function
	  Double_t chi2 = 1E30;
	  Int_t n=Npar;
	  minuit_fcn(n, NULL, chi2, gpar, 2);
	  cout << "SCAN: POINT=" << iter << ", " << Parname[ipar] << "=" << gpar[ipar] << ", CHI2=" << chi2 << endl;
	  delete [] gpar;
	  delete [] gerr;
	}
      //     arglist[0] = ipar+1;        // MINUIT's paramter number 1...7
      //     arglist[1] = _Zminuit_do_SCAN_NSTEPS;// Number of points to scan (N<=100)
      //     arglist[2] = RangeMin[ipar]; // start here
      //     arglist[3] = RangeMax[ipar]; // end here  
      //     gMinuit->mnexcm("SCAN", arglist , 4, ierflg);
    } // end of SCAN
    
    if(_Zminuit_do_SEEK) {
      // try with low statistics first
      int nseek=nevts; // _Zminuit_do_SEEK_NEVENTS;
      //      if(nevts>0) nseek=minim(_Zminuit_do_SEEK_NEVENTS,nevts);
      //      MINUIT_setNevts(nseek);
      //      if(_Zminuit_RAMBuffer) free(_Zminuit_RAMBuffer);
      //      _Zminuit_RAMBuffer = NULL;
      //      _Zminuit_RAMBuffer_Ready = false;
      //      _Zminuit_RAMBuffer_Nevts = 0;
      cout << "=================================================================="<<endl;
      cout << "STARTING MONTE CARLO SEEK (using up to "<< nseek << " events only)" << endl;
      // check if want a random starting point
      if(_Zminuit_do_SEEK_RndStart) {
	cout << "USING RANDOM STARTING POINTS FOR " << Npar << " PARAMETERS" << endl;
	for(int ipar=0; ipar<Npar; ipar++) {
	  gMinuit->mnparm(ipar,Parname[ipar],
			  gRandom->Uniform(RangeMin[ipar], RangeMax[ipar]),
			  Step[ipar],
			  RangeMin[ipar], RangeMax[ipar],ierflg);
	}
      } else {
	cout << "USING USER-DEFINED STARTING POINTS FOR " << Npar << " PARAMETERS" << endl;
      }
      // around current best value (default is 3 simga)
      arglist[0] = _Zminuit_do_SEEK_NITER; // how many iterations 
      arglist[1] = 3; // search 3 standard deviations from the centre of a hypercube
      gMinuit->mnexcm("SEEK", arglist , 2, ierflg);
      
      // Display final parameters
      cout << "PARAMETERS AFTER MONTE CARLO SEEK (using up to "<< nseek << " evetns only)" << endl;
      for(int ipar=0; ipar<Npar; ipar++) {
	Double_t gpar, gerr;
	gMinuit->GetParameter(ipar, gpar, gerr);
	cout << setw(1) << ipar 
	     << " :" << setw(10) << Parname[ipar]
	     << " : Value = " << setw(15) << gpar 
	     << " Error = "   << setw(15) << gerr << endl;
      } 
    } // end of SEEK
    
    // switch to full statistics
    //    MINUIT_setNevts(nevts);
    //    if(_Zminuit_RAMBuffer) free(_Zminuit_RAMBuffer);
    //    _Zminuit_RAMBuffer = NULL;
    //    _Zminuit_RAMBuffer_Ready = false;
    //    _Zminuit_RAMBuffer_Nevts = 0;
    
    if (_Zminuit_do_SIMPLEX) {
      cout << "=================================================================="<<endl;
      cout << "STARTING SIMPLEX:" << endl;
      // First argument sets the maximum number of iterations 
      // Second argument specifies required tolerance on the
      // function value at the minimum.  
      // For SIMPLEX the default tolerance is 0.1, 
      // and the minimization will stop when 
      // the estimated vertical distance to the minimum (EDM) is less than
      // 0.1*[tolerance]*UP (see SET ERR). 
      arglist[0] = _Zminuit_do_SIMPLEX_NITER;
      arglist[1] = _Zminuit_do_SIMPLEX_TOLER; 
      // Turns on printing of the covariance matrix
      gMinuit->mnmatu(1);
      gMinuit->mnexcm("HESSE",0,0,ierflg);
      gMinuit->mnexcm("SIMPLEX", arglist , 2, ierflg);
      gMinuit->mnexcm("HESSE",0,0,ierflg);
      print_errors=true;
    } // end of SIMPLEX
    
    if (_Zminuit_do_MINIMIZE) {
      cout << "=================================================================="<<endl;
      cout << "STARTING MINIMIZE:" << endl;

      // Turns on/off user supplied gradient
      if(_Zminuit_UseGradient) {
	// SET GRADIENT [force]
	// Informs Minuit that the user function is prepared to calculate its own first 
	// derivatives and return their values in the array GRAD when IFLAG=2
	// If [force] is not specified, Minuit will calculate the FCN derivatives
	// by finite differences at the current point and compare with the user's 
	// calculation at that point, accepting the user's values only if they agree. 
	// If [force]=1, Minuit does not do its own derivative calculation, 
	// and uses the derivatives calculated in FCN.
	arglist[0] = 1; // force MINUIT to trust user supplied gradients
	gMinuit->mnexcm("SET GRADIENT", arglist , 1, ierflg);
      }

      // SET EPS [epsilon]
      // Artificially lowers machine precision for CHI2 and derivatives
      arglist[0] = _Zminuit_do_MINIMIZE_EPS;
      gMinuit->mnexcm("SET EPS", arglist, 1, ierflg);

      // Turns on printing of the covariance matrix
      gMinuit->mnmatu(1);
      gMinuit->mnexcm("HESSE",0,0,ierflg);
      // MINIMIZE [Niter] [Tolerance]
      // First argument sets the maximum number of iterations 
      // Second argument specifies required tolerance on the
      // function value at the minimum.  
      // For MINIMIZE the default tolerance is 0.1, 
      // and the minimization will stop when 
      // the estimated vertical distance to the minimum (EDM) is less than
      // 0.001*[tolerance]*UP (see SET ERR). 
      arglist[0] = _Zminuit_do_MINIMIZE_NITER;
      arglist[1] = _Zminuit_do_MINIMIZE_TOLER; 
      gMinuit->mnexcm("MINIMIZE", arglist , 2, ierflg);
      gMinuit->mnexcm("HESSE",0,0,ierflg);
      print_errors=true;
    } // end of MINIMIZE
    
    if(print_errors) {
      // Accessing errors
      cout << "=================================================================="<<endl;
      cout << "ERRORS:" << endl;
      cout.precision(5);
      for(int ipar=0; ipar<Npar; ipar++){
	double eplus, eminus, epara, globcc;
	gMinuit->mnerrs(ipar, eplus, eminus, epara, globcc);
	cout << setw(1) << ipar 
	     << " :" << setw(10) << Parname[ipar]
	     << " : +Error = " << scientific << setw(15) << eplus
	     << ", -Error = "  << setw(15) << eminus
	     << ", Parabolic Error = " << setw(15) << epara
	     << ", Global Correlation = " << setw(15) << globcc << endl;  
      }
      cout << endl << endl;
      
      // Accessing covariance matrix
      cout << "=================================================================="<<endl;
      cout << "COVARIANCE MATRIX:" << endl << endl;
      Double_t matrix[Npar][Npar];
      cout.precision(5);
      gMinuit->mnemat(&matrix[0][0],Npar);
      cout << setw(15) << " ";
      for(int ipar=0; ipar<Npar; ipar++) {
	cout << " " << setw(15) << Parname[ipar]; 
      }
      cout << endl;
      for(int ipar=0; ipar<Npar; ipar++) {
	cout << setw(15) << Parname[ipar];
	for(int jpar=0; jpar<=ipar; jpar++) {
	  cout << " " << scientific << setw(15) << matrix[ipar][jpar]; 
	}
	cout << endl;
      }
      cout << setw(15) << " ";
      for(int ipar=0; ipar<Npar; ipar++) {
	cout << " " << setw(15) << Parname[ipar]; 
      }
      cout << endl << endl;
      cout << "------------------------------------------------------------------"<<endl;
      cout << "Result of SHOW COVARIANCE command:" << endl;
      gMinuit->mnexcm("SHOW COV", 0, 0, ierflg);
      cout << "------------------------------------------------------------------"<<endl;
      cout << "Result of SHOW EIGENVALUES command:" << endl;
      gMinuit->mnexcm("SHOW EIG", 0, 0, ierflg);
      cout << "------------------------------------------------------------------"<<endl;
      cout << "Result of SHOW CORRELATION command:" << endl;
      gMinuit->mnexcm("SHOW COR", 0, 0, ierflg);
      print_errors=false;
    }
    
    if (_Zminuit_do_MINOS) {
      cout << "=================================================================="<<endl;
      cout << "STARTING MINOS:" << endl;
      // MINOS error analysis
      arglist[0] = _Zminuit_do_MINOS_NITER;
      int narglist=1;
      for(int ipar=0; ipar<Npar; ipar++) {
	if( _Zminuit_ParIsFixed[ipar] ) {
	  cout << "MINOS: Parameter " << ipar << " : " << Parname[ipar] 
	       << " is fixed." << endl;
	} else {
	  cout << "MINOS: Will calculate NEG and POS errors for parameter " 
	       << ipar << " : " << Parname[ipar] << endl;
	  arglist[narglist] = ipar+1; // convert to numbering scheme: 1...Npar
	  narglist++;
	}
      }
      gMinuit->mnexcm("MINOS", arglist, narglist, ierflg);  
      gMinuit->mnexcm("HESSE",0,0,ierflg);
      print_errors=true;
    } // end of MINOS
    
    if(print_errors) {
      // Accessing errors
      cout << "=================================================================="<<endl;
      cout << "ERRORS:" << endl;
      cout.precision(5);
      for(int ipar=0; ipar<Npar; ipar++) {
	double eplus, eminus, epara, globcc;
	gMinuit->mnerrs(ipar, eplus, eminus, epara, globcc);
	cout << setw(1) << ipar 
	     << " :" << setw(10) << Parname[ipar]
	     << " : +Error = " << scientific << setw(15) << eplus
	     << ", -Error = "  << setw(15) << eminus
	     << ", Parabolic Error = " << setw(15) << epara
	     << ", Global Correlation = " << setw(15) << globcc << endl;  
      }
      cout << endl << endl;
      
      // Accessing covariance matrix
      cout << "=================================================================="<<endl;
      cout << "COVARIANCE MATRIX:" << endl << endl;
      Double_t matrix[Npar][Npar];
      cout.precision(5);
      gMinuit->mnemat(&matrix[0][0],Npar);
      cout << setw(15) << " ";
      for(int ipar=0; ipar<Npar; ipar++) {
	cout << " " << setw(15) << Parname[ipar]; 
      }
      cout << endl;
      for(int ipar=0; ipar<Npar; ipar++) {
	cout << setw(15) << Parname[ipar];
	for(int jpar=0; jpar<=ipar; jpar++) {
	  cout << " " << scientific << setw(15) << matrix[ipar][jpar]; 
	}
	cout << endl;
      }
      cout << setw(15) << " ";
      for(int ipar=0; ipar<Npar; ipar++) {
	cout << " " << setw(15) << Parname[ipar]; 
      }
      cout << endl << endl;
      cout << "------------------------------------------------------------------"<<endl;
      cout << "Result of SHOW COVARIANCE command:" << endl;
      gMinuit->mnexcm("SHOW COV", 0, 0, ierflg);
      cout << "------------------------------------------------------------------"<<endl;
      cout << "Result of SHOW EIGENVALUES command:" << endl;
      gMinuit->mnexcm("SHOW EIG", 0, 0, ierflg);
      cout << "------------------------------------------------------------------"<<endl;
      cout << "Result of SHOW CORRELATION command:" << endl;
      gMinuit->mnexcm("SHOW COR", 0, 0, ierflg);
      print_errors=false;
    }
    
    cout << "=================================================================="<<endl;
    cout << "FINAL PARAMETERS:" << endl;
    // get fit results: parameters and their errors:
    Double_t* gpar = new Double_t[Npar];
    Double_t* gerr = new Double_t[Npar];
    for(Int_t ipar=0; ipar<Npar; ipar++) {
      gMinuit -> GetParameter(ipar, gpar[ipar], gerr[ipar]);
      cout << setw(1) << ipar 
	   << " :" << setw(10) << Parname[ipar]
	   << " : Value = " << setw(15) << gpar[ipar] 
	   << " Error = "   << setw(15) << gerr[ipar] << endl;
    } 
    Double_t chi2_at_min = 1E30;
    Int_t n=Npar;
    minuit_fcn(n, NULL, chi2_at_min, gpar, 2);
    cout << "=================================================================="<<endl;
    cout << "FINAL CHI2: " << chi2_at_min << endl << endl; 
    cout << "=================================================================="<<endl;
    
    delete [] gpar;
    delete [] gerr;
    
    // Print the results
    gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);                         
    
    // mnprin(Int_t inkode, Double_t fval)
    // Prints the values of the parameters at the time of the call
    //       also prints other relevant information such as function value,
    //       estimated distance to minimum, parameter errors, step sizes.
    //       According to the value of IKODE, the printout is:
    //       IKODE=INKODE= 0    only info about function value
    //                     1    parameter values, errors, limits
    //                     2    values, errors, step sizes, internal values
    //                     3    values, errors, step sizes, first derivs.
    //                     4    values, parabolic errors, MINOS errors
    gMinuit->mnprin(4,amin);      

    if(_Zminuit_UseMasterSlaveMode) {
      fstream f_QUIT(_Zminuit_MasterSlave_QUIT.Data(), ios::out);
      f_QUIT << endl << flush;
      cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	  <<": Master job sent QUIT signal."<<endl; 
      f_QUIT.close();
    }

  } 
  // 
  /////////////////////////////// end of ordinary mode or MASTER mode
  //
  else {
    cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	<<": Slave job enters LISTEN mode."<<endl; 
    bool do_QUIT=false;
    do {
      // Execute MINUIT_calc_chi2 with dummy parameters.
      // Actual parametes will be taken from master's request file.
      MINUIT_calc_chi2( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
      fstream f_QUIT(_Zminuit_MasterSlave_QUIT.Data(), ios::in);
      if(f_QUIT.is_open()) {
	f_QUIT.close();
	do_QUIT=true;
	cout<<"MASTER-SLAVE-MODE: JOB="<<_Zminuit_MasterSlave_Job
	    <<": Slave job detected QUIT signal."<<endl; 
      }
    } while (!do_QUIT);
  } 
  //
  /////////////////////////////// end of SLAVE mode

    // free the memory
    if(_Zminuit_UseRAM && _Zminuit_RAMBuffer) {
      free(_Zminuit_RAMBuffer);
      _Zminuit_RAMBuffer=NULL;
      _Zminuit_RAMBuffer_Nevts=0;
      _Zminuit_RAMBuffer_Ready=false;
    }

  cout << "=================================================================="<<endl;
  cout << "Finished re-processing" << endl;
  cout << "=================================================================="<<endl;
}

bool ZAnalysis::filltree2(PMCSZCand& zcand, Double_t vz, Double_t zScalarEt, Int_t runNum, Int_t eventNum, double weight, int type) {
  
   tree2_type = type;
  tree2_vtxz=vz;

  tree2_ZBrunnum = runNum;
  tree2_ZBeventnum = eventNum;
  tree2_Mz = zcand.mass();
  tree2_Ptz = zcand.ppt();
  tree2_lumi = zcand.GetElec1().getLumi();
  tree2_set = zScalarEt;
  tree2_ZUt = zcand.GetRecoil().Recoil();
  tree2_weight = weight;
  PMCSEMObj localemobj;
  for (Int_t y = 0; y < 2; ++y){
    if (y==0)
      localemobj = zcand.GetElec1();
    else
      localemobj = zcand.GetElec2();
    
    tree2em_e[y]= localemobj.pE();
    tree2em_pt[y]= localemobj.ppt();
    tree2em_eta[y]= localemobj.peta();
    tree2em_phi[y]= localemobj.pphi();
    tree2em_deteta[y]= localemobj.deteta();
    tree2em_detphi[y]= localemobj.detphi();
    // tree2em_upara[y]= 0.;
    //tree2em_trk_prob[y]= 0;
    tree2em_trk_pt[y]=localemobj.trkpT();
    tree2em_trkphiem3[y] = localemobj.trkphiem3();  
    tree2em_fid[y] = !localemobj.IsLostInAcrack();


  }
  tree2em_upara[0]=zcand.UPara1();
  tree2em_upara[1]=zcand.UPara2();
  _tree2->Fill();
  return true;
}
