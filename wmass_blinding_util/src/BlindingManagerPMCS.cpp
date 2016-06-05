#include "wmass_blinding_util/BlindingManagerPMCS.hpp"

#include "TH1F.h"

#include <iostream>
#include <cassert>

using namespace std;

BlindingManagerPMCS::BlindingManagerPMCS() {

  _wmass_reweight=false;
  _wmass_default=-1e10;
  _wmass_step=-1;
  _wmass_nstep=-1;
  _wwidth_reweight=false;
  _wwidth_default=-1;
  _wwidth_step=-1;
  _wwidth_nstep=-1;

}


BlindingManagerPMCS::~BlindingManagerPMCS() {
}


void BlindingManagerPMCS::SetInfo(bool wmass_reweight,
				  float wmass_default, float wmass_step, int wmass_nstep,
				  bool wwidth_reweight,
				  float wwidth_default, float wwidth_step, int wwidth_nstep) {

  _wmass_reweight=wmass_reweight;
  _wmass_default=wmass_default;
  _wmass_step=wmass_step;
  _wmass_nstep=wmass_nstep;
  _wwidth_reweight=wwidth_reweight;
  _wwidth_default=wwidth_default;
  _wwidth_step=wwidth_step;
  _wwidth_nstep=wwidth_nstep;
  //
  if (!_wmass_reweight) {
    _wmass_default=-1;
    _wmass_step=-1;
    _wmass_nstep=-1;
  }
  if (!_wwidth_reweight) {
    _wwidth_default=-1;
    _wwidth_step=-1;
    _wwidth_nstep=-1;
  }
  //
  return;

}


TH1F* BlindingManagerPMCS::GetVerdict() {

  if (_wmass_default<-1e9) {
    cout<<"Asking for verdict from uninitialised BlindingManagerPMCS - will bail."<<endl;
    assert(0);
  }

  TH1F* th1BM = new TH1F("BlindingManagerPMCS","BlindingManagerPMCS",20,0,1);
  th1BM->SetBinContent(1,2);   // version

  int dummy=(int)_wmass_reweight;
  th1BM->SetBinContent(2,(float)dummy);
  th1BM->SetBinContent(3,_wmass_default);
  th1BM->SetBinContent(4,_wmass_step);
  th1BM->SetBinContent(5,(float)_wmass_nstep);

  dummy=(int)_wwidth_reweight;
  th1BM->SetBinContent(6,(float)dummy);
  th1BM->SetBinContent(7,_wwidth_default);
  th1BM->SetBinContent(8,_wwidth_step);
  th1BM->SetBinContent(9,(float)_wwidth_nstep);

  th1BM->SetBinContent(10,1);  // trick to detect the use of 'hadd'

  return th1BM;

}



