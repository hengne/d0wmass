#include "wmass_blinding_util/BlindingAuthority.hpp"

#include "wmass_blinding_util/OffsetMass.hpp"
#include "wmass_blinding_util/OffsetMassP0.hpp"
#include "wmass_blinding_util/OffsetMassP1.hpp"
#include "wmass_blinding_util/OffsetMassP2.hpp"
#include "wmass_blinding_util/OffsetWidth.hpp"
#include "wmass_blinding_util/OffsetWidthP0.hpp"
#include "wmass_blinding_util/OffsetWidthP1.hpp"
#include "wmass_blinding_util/OffsetWidthP2.hpp"

#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TAxis.h"
#include "TRandom3.h"
#include "TDirectory.h"
#include "TDirectoryFile.h"

#include <iostream>
#include <cassert>
#include <math.h>

using namespace std;

BlindingAuthority::BlindingAuthority(int IntendedPeriod) {
  VerifySeeding();
  //
  _IntendedPeriod=IntendedPeriod;
  //
  _f1=0;
  _f2=0;
  _compmode=-1;
  _BlindMass=-1;
  //
  _origin1=-1;
  _BMhist1=0;
  _origin2=-1;
  _BMhist2=0;
  //
  _TreatFastMCblind=false;
  //
  _debug=false;
  //
  if (IntendedPeriod==0) {
    _theMassOffset = new OffsetMassP0;
    _theWidthOffset = new OffsetWidthP0;
  } else if (IntendedPeriod==1) {
    _theMassOffset = new OffsetMassP1;
    _theWidthOffset = new OffsetWidthP1;
  } else if (IntendedPeriod==2) {
    _theMassOffset = new OffsetMassP2;
    _theWidthOffset = new OffsetWidthP2;
  } else {
    cout<<"BlindingAuthority: do not know how to build blinding offsets for the intended data period."<<endl;
    assert(0);
  }
}


BlindingAuthority::~BlindingAuthority() {
  delete _theMassOffset;
  delete _theWidthOffset;
}


void BlindingAuthority::SetConfiguration(TFile* f1, TFile* f2, int compmode) {
  _f1=f1;
  _f2=f2;
  _compmode=compmode;
  assert(isConfigured());
  CheckConsistency();
}


void BlindingAuthority::SetDebug(bool debug) {
  _debug=debug;
}


void BlindingAuthority::SetBlindMass(double m) {
  if ((m<75.)||(m>85.)) {
    cout<<"BlindingAuthority: Blind m(W) is outside expected range."<<endl;
    cout<<"                   You need to provide a valid value of the "<<endl;
    cout<<"                   blind m(W) in order to compare data and fast MC."<<endl;
    assert(0);
  }
  _BlindMass=m;
}


void BlindingAuthority::CheckConsistency() {

  // What kind of files are we dealing with ?
  //

  // first file
  _origin1=-1;
  TObject* da=_f1->Get("WCand_Hist");
  TObject* db=_f1->Get("default");
  if (da) {
    if (da->IsA()==TDirectory::Class() || da->IsA()==TDirectoryFile::Class()) {
      // wmass_analysis
      _origin1=1;
      _BMhist1=(TH1F*)_f1->Get("BlindingManagerData");
    }
  } else if (db) {
    if (db->IsA()==TDirectory::Class() || db->IsA()==TDirectoryFile::Class()) {
      // wz_epmcs
      _origin1=2;
      _BMhist1=(TH1F*)_f1->Get("BlindingManagerPMCS");
    }
  }
  if (_origin1<1) {
    cout<<"BlindingAuthority: do not understand origin of first file."<<endl;
    assert(0);
  }

  // second file
  _origin2=-1;
  da=_f2->Get("WCand_Hist");
  db=_f2->Get("default");
  if (da) {
    if (da->IsA()==TDirectory::Class() || da->IsA()==TDirectoryFile::Class()) {
      // wmass_analysis
      _origin2=1;
      _BMhist2=(TH1F*)_f2->Get("BlindingManagerData");
    }
  } else if (db) {
    if (db->IsA()==TDirectory::Class() || db->IsA()==TDirectoryFile::Class()) {
      // wz_epmcs
      _origin2=2;
      _BMhist2=(TH1F*)_f2->Get("BlindingManagerPMCS");
    }
  }
  if (_origin2<1) {
    cout<<"BlindingAuthority: do not understand origin of second file."<<endl;
    assert(0);
  }

  // print out summary, if requested
  if (_debug) {
    cout<<" File 1: "<<_origin1<<" "<<_BMhist1<<endl;
    cout<<" File 2: "<<_origin2<<" "<<_BMhist2<<endl;
  }


  // does this match our blinding scenario ?
  //
  switch(_compmode)
    {
    case 0:  // data vs fast MC
      _TreatFastMCblind=true;
      if (_origin1!=1) {
	cout<<"BlindingAuthority: first file not from wmass_analysis - abort."<<endl;
	assert(0);
      }
      if (!_BMhist1) {
	cout<<"BlindingAuthority: wmass_analysis output without blinding management - abort."<<endl;
        assert(0);
      }
      int version, isThisData, isRunIIb, isRunIIb34;
      _BMP.ParseAVerdictData(_BMhist1,version,isThisData,isRunIIb,isRunIIb34);
      if (!isThisData) {
        cout<<"BlindingAuthority: got full MC when I expected data - abort."<<endl;
        assert(0);
      }
      if (_IntendedPeriod==0) {
	if (isRunIIb!=0) {
	  cout<<"BlindingAuthority: expected to get Run IIa data, but got other data."<<endl;  
	  assert(0);
	}
      } else if (_IntendedPeriod==1) {
	if (isRunIIb!=1) { 
          cout<<"BlindingAuthority: expected to get Run IIb data, but got other data."<<endl;   
          assert(0); 
        }
      } else if (_IntendedPeriod==2) {
        if (isRunIIb34!=1) {
          cout<<"BlindingAuthority: expected to get Run IIb3,4 data, but got other data."<<endl;
          assert(0);
        }
      } else {
	cout<<"BlindingAuthority: do not know how to deal with your intended data period."<<endl; 
        assert(0);
      }
      //
      if (_origin2!=2) {
        cout<<"BlindingAuthority: second file not from wz_epmcs - abort."<<endl;
        assert(0);
      }
      if (!_BMhist2) {
        cout<<"BlindingAuthority: wz_epmcs output without blinding management - abort."<<endl;
        assert(0);
      }
      bool variedMass, enoughRangeMass;
      _BMP.ParseAVerdictPMCS(_BMhist2,version,variedMass,enoughRangeMass);
      if (!variedMass) {
        cout<<"BlindingAuthority: wz_epmcs did was not run with mass reweighting - abort."<<endl;
        assert(0);
      }
      if (!enoughRangeMass) {
        cout<<"BlindingAuthority: mass range in wz_epmcs too small for proper blinding - abort."<<endl;
        assert(0);
      }
      break;
    case 1:  // data vs data
      _TreatFastMCblind=false;
      if (_origin1!=1) {
        cout<<"BlindingAuthority: first file not from wmass_analysis - abort."<<endl;
        assert(0);
      }
      if (!_BMhist1) {
        cout<<"BlindingAuthority: wmass_analysis output without blinding management - abort."<<endl;
        assert(0);
      }
      _BMP.ParseAVerdictData(_BMhist1,version,isThisData,isRunIIb,isRunIIb34);
      if (!isThisData) {
        cout<<"BlindingAuthority: got full MC when I expected data - abort."<<endl;
        assert(0);
      }
      //
      if (_origin2!=1) {
        cout<<"BlindingAuthority: second file not from wmass_analysis - abort."<<endl;
        assert(0);
      }
      if (!_BMhist2) {
        cout<<"BlindingAuthority: wmass_analysis output without blinding management - abort."<<endl;
        assert(0);
      }
      _BMP.ParseAVerdictData(_BMhist2,version,isThisData,isRunIIb,isRunIIb34);
      if (!isThisData) {
        cout<<"BlindingAuthority: got full MC when I expected data - abort."<<endl;
        assert(0);
      }
      break;
    case 2:  // fast MC vs. fast MC
      _TreatFastMCblind=false;
      if (_origin1!=2) {
        cout<<"BlindingAuthority: first file not from wz_epmcs - abort."<<endl;
        assert(0);
      }
      if (_origin2!=2) {
        cout<<"BlindingAuthority: second file not from wz_epmcs - abort."<<endl;
        assert(0);
      }
      break;
    case 3:  // full MC vs. fast MC
      _TreatFastMCblind=false;
      if (_origin1!=1) {
        cout<<"BlindingAuthority: first file not from wmass_analysis - abort."<<endl;
        assert(0);
      }
      if (!_BMhist1) {
        cout<<"BlindingAuthority: wmass_analysis output without blinding management - abort."<<endl;
        assert(0);
      }
      _BMP.ParseAVerdictData(_BMhist1,version,isThisData,isRunIIb,isRunIIb34);
      if (isThisData) {
        cout<<"BlindingAuthority: got data when I expected full MC - abort."<<endl;
        assert(0);
      }
      //
      if (_origin2!=2) {
        cout<<"BlindingAuthority: second file not from wz_epmcs - abort."<<endl;
        assert(0);
      }
      break;
    case 4:  // full MC vs. full MC
      _TreatFastMCblind=false;
      if (_origin1!=1) {
        cout<<"BlindingAuthority: first file not from wmass_analysis - abort."<<endl;
        assert(0);
      }
      if (!_BMhist1) {
        cout<<"BlindingAuthority: wmass_analysis output without blinding management - abort."<<endl;
        assert(0);
      }
      _BMP.ParseAVerdictData(_BMhist1,version,isThisData,isRunIIb,isRunIIb34);
      if (isThisData) {
        cout<<"BlindingAuthority: got data when I expected full MC - abort."<<endl;
        assert(0);
      }
      //
      if (_origin2!=1) {
        cout<<"BlindingAuthority: second file not from wmass_analysis - abort."<<endl;
        assert(0);
      }
      if (!_BMhist2) {
        cout<<"BlindingAuthority: wmass_analysis output without blinding management - abort."<<endl;
        assert(0);
      }
      _BMP.ParseAVerdictData(_BMhist2,version,isThisData,isRunIIb,isRunIIb34);
      if (isThisData) {
        cout<<"BlindingAuthority: got data when I expected full MC - abort."<<endl;
        assert(0);
      }
      break;
    case 5:  // data vs. full MC
      _TreatFastMCblind=false;
      cout<<"BlindingAuthority: comparing data to full MC is inappropriate while"<<endl;
      cout<<"                   the analysis is still blind - abort."<<endl;
      assert(0);
      break;
    default:
      cout<<"BlindingAuthority: unknown comparison mode - abort."<<endl;
      assert(0);
      break;
    }

}


bool BlindingAuthority::isConfigured() {
  return ((_f1!=0)&&(_f2!=0)&&(_compmode>=0));
}


bool BlindingAuthority::knowMass() {
  return (_BlindMass>0);
}


TH1F* BlindingAuthority::Get_mass(TFile* f, const char* wo) {
  return Get_TH1F(f,wo,"hWcandMt_CC_","default/hWcandMt_");
}


TH1F* BlindingAuthority::Get_elecpt(TFile* f, const char* wo) {
  return Get_TH1F(f,wo,"hWcandElecPt_CC_","default/hWcandElecPt_");
}


TH1F* BlindingAuthority::Get_met(TFile* f, const char* wo) {
  return Get_TH1F(f,wo,"hWcandMet_CC_","default/hWcandMet_");
}


TH1* BlindingAuthority::Get_hWcandMtUpara(TFile* f, const char* wo) {
  return Get_TProfile(f,wo,"hWcandMtUpara_CC_","default/hWcandMtUpara_");
}


TH1* BlindingAuthority::Get_hWcandElecPtUpara(TFile* f, const char* wo) {
  return Get_TProfile(f,wo,"hWcandElecPtUpara_CC_","default/hWcandElecPtUpara_");
}


TH1* BlindingAuthority::Get_hWcandMetUpara(TFile* f, const char* wo) {
  return Get_TProfile(f,wo,"hWcandMetUpara_CC_","default/hWcandMetUpara_");
}


TH1F* BlindingAuthority::Get_mtoverlay(TFile* f, int bin, const char* wo) {
  TString basename;
  basename="hWcandMtUpara";
  basename+=bin;
  basename+="_";
  basename+=wo;
  basename+="_";
  TString nominal;
  nominal="default/hWcandMtUpara";
  nominal+=bin;
  nominal+="_";
  return Get_TH1F(f,wo,basename.Data(),nominal.Data());
}


TH1F* BlindingAuthority::Get_eptoverlay(TFile* f, int bin, const char* wo) {
  TString basename;
  basename="hWcandElecPtUpara";
  basename+=bin;
  basename+="_";
  basename+=wo;
  basename+="_";
  TString nominal;
  nominal="default/hWcandElecPtUpara";
  nominal+=bin;
  nominal+="_";
  return Get_TH1F(f,wo,basename.Data(),nominal.Data());
}


TH1F* BlindingAuthority::Get_metoverlay(TFile* f, int bin, const char* wo) {
  TString basename;
  basename="hWcandMetUpara";
  basename+=bin;
  basename+="_";
  basename+=wo;
  basename+="_";
  TString nominal;
  nominal="default/hWcandMetUpara";
  nominal+=bin;
  nominal+="_";
  return Get_TH1F(f,wo,basename.Data(),nominal.Data());
}


TH1F* BlindingAuthority::Get_utbinoverlay(TFile* f, int bin, const char* wo) {
  TString basename;
  basename="hWcandMt_UtBin";
  basename+=bin;
  basename+="_";
  basename+=wo;
  basename+="_";
  TString nominal;
  nominal="default/hWcandMt_UtBin";
  nominal+=bin;
  nominal+="_";
  return Get_TH1F(f,wo,basename.Data(),nominal.Data());
}


TH1F* BlindingAuthority::Get_TH1F(TFile* f, const char* wo, const char* basename, const char* nominal) {

  assert((f==_f1)||(f==_f2));

  if (_TreatFastMCblind) {
    double masses[100];
    BuildTemplateMasses(f,masses);
    if (_debug) {
      cout<<"Got template masses from "<<masses[0]<<" to "<<masses[99]<<endl;
    }
    TObject* temps[100];
    GrabTemplates(f,basename,temps);
    if (_debug) {
      cout<<"Got these templates: "<<endl;
      for (int i=0; i<100; i++) {
	cout<<" "<<temps[i]->GetTitle()<<endl;
      }
    }
    TH1F* erg=InterpolateTemplatesTH1F(_BlindMass,masses,temps);
    return erg;
  } else {
    char name[50];
    sprintf(name, "%s%s", nominal, wo);
    f->cd("default");
    return (TH1F *)f->Get(name);
  }

}


TH1* BlindingAuthority::Get_TProfile(TFile* f, const char* wo, const char* basename, const char* nominal) {

  assert((f==_f1)||(f==_f2));

  if (_TreatFastMCblind) {
    double masses[100];
    BuildTemplateMasses(f,masses);
    if (_debug) {
      cout<<"Got template masses from "<<masses[0]<<" to "<<masses[99]<<endl;
    }
    TObject* temps[100];
    GrabTemplates(f,basename,temps);
    if (_debug) {
      cout<<"Got these templates (profiles): "<<endl;
      for (int i=0; i<100; i++) {
        cout<<" "<<temps[i]->GetTitle()<<endl;
      }
    }
    TH1F* erg=InterpolateTemplatesTProfile(_BlindMass,masses,temps);
    return erg;
  } else {
    char name[50];
    sprintf(name, "%s%s", nominal, wo);
    f->cd("default");
    return (TProfile *)f->Get(name);
  }

}


void BlindingAuthority::BuildTemplateMasses(TFile* f, double masses[100]) {

  TH1D* massmap = (TH1D*)f->Get("default/histd1map_WMassTemplates");
  TAxis* a = massmap->GetXaxis();
  double anfang = a->GetXmin();
  double schritt = (a->GetXmax() - a->GetXmin())/99.;
  for (int i=0; i<100; i++) {
    masses[i]=anfang+i*schritt;
  }

  if (_debug) {
    cout<<"BuildTemplateMasses ("<<anfang<<" "<<schritt<<"):"<<endl;
    for (int i=0; i<100; i++) {
      cout<<" "<<masses[i]<<endl;
    }
  }

  return;

}


void BlindingAuthority::GrabTemplates(TFile* f, const char* basename, TObject* temps[100]) {

  for (int i=0; i<100; i++) {
    TString n;
    n="default/";
    n+=basename;
    n+=i;
    temps[i]=f->Get(n);
  }

  return;

}


TH1F* BlindingAuthority::InterpolateTemplatesTH1F(double theBlindMass, double masses[100], TObject* temps[100]) {

  double theTrueMass=Get_Offset_Mass()->CalculateTrueMassFromBlindedMass(theBlindMass);

  if ((theTrueMass<masses[0])||(theTrueMass>masses[99])) {
    cout<<"BlindingAuthority: cannot deal with the requested value of blind mass; it is out of range - abort."<<endl;
    assert(0);
  }

  int theDownIndex=-1;
  int theUpIndex=-1;
  TH1F* theDown=0;
  TH1F* theUp=0;
  double dist=-1;
  for (int i=0; i<99; i++) {
    if ((masses[i]<=theTrueMass)&&(masses[i+1]>theTrueMass)) {
      theDownIndex=i;
      theUpIndex=i+1;
    }
  }
  theDown=(TH1F*)temps[theDownIndex];
  theUp=(TH1F*)temps[theUpIndex];
  dist=(theTrueMass-masses[theDownIndex])/(masses[theUpIndex]-masses[theDownIndex]);

  TString n;
  n=((TH1F*)temps[0])->GetTitle();
  n+="_hidden";
  TAxis* a=((TH1F*)temps[0])->GetXaxis();
  TH1F* interp = new TH1F(n,n,a->GetNbins(),a->GetXmin(),a->GetXmax());
  for (int i=0; i<=a->GetNbins()+1; i++) {
    interp->SetBinContent(i,theDown->GetBinContent(i)+dist*(theUp->GetBinContent(i)-theDown->GetBinContent(i)));
    interp->SetBinError(i,theDown->GetBinError(i));
  }

  return interp;

}


TH1F* BlindingAuthority::InterpolateTemplatesTProfile(double theBlindMass, double masses[100], TObject* temps[100]) {

  double theTrueMass=Get_Offset_Mass()->CalculateTrueMassFromBlindedMass(theBlindMass);

  if ((theTrueMass<masses[0])||(theTrueMass>masses[99])) {
    cout<<"BlindingAuthority: cannot deal with the requested value of blind mass; it is out of range - abort."<<endl;
    assert(0);
  }

  int theDownIndex=-1;
  int theUpIndex=-1;
  TProfile* theDown=0;
  TProfile* theUp=0;
  double dist=-1;
  for (int i=0; i<99; i++) {
    if ((masses[i]<=theTrueMass)&&(masses[i+1]>theTrueMass)) {
      theDownIndex=i;
      theUpIndex=i+1;
    }
  }
  theDown=(TProfile*)temps[theDownIndex];
  theUp=(TProfile*)temps[theUpIndex];
  dist=(theTrueMass-masses[theDownIndex])/(masses[theUpIndex]-masses[theDownIndex]);

  TString n;
  n=((TProfile*)temps[0])->GetTitle();
  n+="_hidden";
  TAxis* a=((TProfile*)temps[0])->GetXaxis();
  TH1F* interp = new TH1F(n,n,a->GetNbins(),a->GetXmin(),a->GetXmax());
  for (int i=0; i<=a->GetNbins()+1; i++) {
    interp->SetBinContent(i,theDown->GetBinContent(i)+dist*(theUp->GetBinContent(i)-theDown->GetBinContent(i)));
    interp->SetBinError(i,theDown->GetBinError(i));
  }

  return interp;

}


OffsetMass* BlindingAuthority::Get_Offset_Mass() {
  return _theMassOffset;
}


OffsetWidth* BlindingAuthority::Get_Offset_Width() {
  return _theWidthOffset;
}


void BlindingAuthority::VerifySeeding() {

  TRandom3 Gen(666);
  Double_t ref=7.00437123887240887e-01;
  Double_t erg=Gen.Rndm();

  if (fabs(ref-erg)>1e-8) {
    cout<<endl<<endl<<endl;
    cout<<"BlindingAuthority: The definition of random seeds in your version of TRandom3 does not match my expectations."<<endl;
    cout<<"                   Check the Root version that you are using."<<endl;
    cout<<endl<<endl<<endl;
    assert(0);
    Int_t* a=0;
    Int_t b=(*a);
  }

  return;

}

