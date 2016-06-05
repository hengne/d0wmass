#include "wmass_blinding_util/BlindingManagerData.hpp"

#include "tmb_tree/TMBL1AndOr.hpp"
#include "tmb_tree/TMBMCevtInfo.hpp"

#include "TH1F.h"
#include "TFile.h"

#include <iostream>

using namespace std;

BlindingManagerData::BlindingManagerData() {
  _nSeen=0;
  _nMClike=0;
  _nDATAlike=0;
  _nRunIIblike=0;
  _nRunIIb34like=0;
}


BlindingManagerData::~BlindingManagerData() {
}


void BlindingManagerData::ExamineEvent(cafe::Event* evt) {

  _nSeen++;

  bool gotAO=false;
  int gotAOnbits=-1;
  const TMBL1AndOr* AO = evt->getL1AndOr();
  if (AO) {
    gotAO=true;
    gotAOnbits=AO->allAndOr().GetEntries();
  }

  bool gotMCEVTI=false;
  int gotMCchunks=-1;
  const TMBMCevtInfo* MCEVTI = evt->getMCEventInfo();
  if (MCEVTI) {
    gotMCEVTI=true;
    gotMCchunks=MCEVTI->nchunks();
  }

  if ((gotMCchunks>0)&&(gotAOnbits==0)) {
    _nMClike++;
  } else if ((gotMCchunks==0)&&(gotAOnbits>0)) {
    _nDATAlike++;
  }

  //cout<<"  "<<gotAO<<" "<<gotAOnbits<<" "<<gotMCEVTI<<" "<<gotMCchunks<<"  "<<_nSeen<<" "<<_nMClike<<" "<<_nDATAlike<<endl;

  if (evt->isRun2b()) _nRunIIblike++;
  if (evt->isRun2b3() || evt->isRun2b4()) _nRunIIb34like++;

  return;

}


void BlindingManagerData::WriteVerdict(TFile* file) {

  TH1F* th1BM = new TH1F("BlindingManagerData","BlindingManagerData",10,0,1);
  th1BM->SetBinContent(1,4);  // version number

  int isThisData=-1;
  if (_nSeen>0) {
    if (_nSeen<10) {
      if (_nDATAlike>_nMClike) isThisData=1;
      else if (_nDATAlike<_nMClike) isThisData=0;
    } else {
      if (_nDATAlike>_nMClike) {
	float r=(float)_nDATAlike/(float)_nSeen;
	if (r>0.79) isThisData=1;
      } else {
	float r=(float)_nMClike/(float)_nSeen;
	if (r>0.79) isThisData=0;
      }
    }
  }
  th1BM->SetBinContent(2,isThisData);

  th1BM->SetBinContent(3,_nSeen);
  th1BM->SetBinContent(4,_nDATAlike);
  th1BM->SetBinContent(5,_nMClike);

  th1BM->SetBinContent(6,1);  // trick to detect 'hadd'

  int isThisRunIIb=-1;
  if (_nSeen>0) {
    if (_nSeen==_nRunIIblike) isThisRunIIb=1;
    else if (_nRunIIblike==0) isThisRunIIb=0;
  }
  th1BM->SetBinContent(7,isThisRunIIb);

  int isThisRunIIb34=-1;
  if (_nSeen>0) {
    if (_nSeen==_nRunIIb34like) isThisRunIIb34=1;
    else if (_nRunIIb34like==0) isThisRunIIb34=0;
  }
  th1BM->SetBinContent(8,isThisRunIIb34);

  file->cd("/");
  th1BM->Write();

  return;

}



