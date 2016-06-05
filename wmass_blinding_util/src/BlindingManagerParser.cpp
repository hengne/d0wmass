#include "wmass_blinding_util/BlindingManagerParser.hpp"

#include "TH1F.h"

#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>

using namespace std;

BlindingManagerParser::BlindingManagerParser() {
}


BlindingManagerParser::~BlindingManagerParser() {
}


void BlindingManagerParser::ParseAVerdictData(TH1F* verdict, int& version, int& isThisData, int& isThisRunIIb, int& isThisRunIIb34) {

  // basic checks
  assert(verdict);
  if (strcmp(verdict->GetTitle(),"BlindingManagerData")!=0) {
    cout<<"Histogram confusion in blinding management - abort."<<endl;
    assert(0);
  }
  if (verdict->GetBinContent(6)<0.5) {
    cout<<"Only understand wmass_analysis output processed with "<<endl;
    cout<<"BlindingManagerData version 2 or higher - abort."<<endl;
    assert(0);
  }
 
  // does this file come out of 'hadd' or not ?
  if (fabs(verdict->GetBinContent(6)-1)<0.01) {
    // we did not go through 'hadd'
    version=lrintf(verdict->GetBinContent(1));
    isThisData=lrintf(verdict->GetBinContent(2));
    if (version>=3) {
      isThisRunIIb=lrintf(verdict->GetBinContent(7));
    } else {
      isThisRunIIb=-1;
    }
    if (version>=4) {
      isThisRunIIb34=lrintf(verdict->GetBinContent(8));
    } else {
      isThisRunIIb34=-1;
    }
  } else {
    // we did go through 'hadd'
    version=lrintf(verdict->GetBinContent(1)/verdict->GetBinContent(6));
    isThisData=lrintf(verdict->GetBinContent(2)/verdict->GetBinContent(6));
    if (version>=3) { 
      isThisRunIIb=lrintf(verdict->GetBinContent(7)/verdict->GetBinContent(6));
    } else { 
      isThisRunIIb=-1; 
    }
    if (version>=4) {
      isThisRunIIb34=lrintf(verdict->GetBinContent(8)/verdict->GetBinContent(6));
    } else {
      isThisRunIIb34=-1;
    }
  }
 
  return;

}


void BlindingManagerParser::ParseAVerdictPMCS(TH1F* verdict, int& version, bool& variedMass, bool& enoughRangeMass) {

  // basic checks
  assert(verdict);
  if (strcmp(verdict->GetTitle(),"BlindingManagerPMCS")!=0) {
    cout<<"Histogram confusion in blinding management - abort."<<endl;
    assert(0);
  }
  if (verdict->GetBinContent(10)<0.5) {
    cout<<"Only understand wz_epmcs output processed with "<<endl;
    cout<<"BlindingManagerPMCS version 2 or higher - abort."<<endl;
    assert(0);
  }

  // does this file come out of 'hadd' or not ?
  if (fabs(verdict->GetBinContent(10)-1)<0) {
    // we did not go through 'hadd'
    version=lrintf(verdict->GetBinContent(1));
    variedMass=false;
    if (verdict->GetBinContent(2)>0.5) variedMass=true;
    enoughRangeMass=false;
    if ((verdict->GetBinContent(4)*verdict->GetBinContent(5))>=0.9999999) enoughRangeMass=true;
  } else {
    // we did go through 'hadd'
    version=lrintf(verdict->GetBinContent(1)/verdict->GetBinContent(10));
    variedMass=false;
    if (fabs(verdict->GetBinContent(2)-verdict->GetBinContent(10))<0.1) variedMass=true;
    enoughRangeMass=false;
    if ((verdict->GetBinContent(4)/verdict->GetBinContent(10)*verdict->GetBinContent(5)/verdict->GetBinContent(10))>=0.9999999) enoughRangeMass=true;
  }

  return;

}

