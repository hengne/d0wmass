// ////////////////////////////////////////////////////////////////////////////
// File: EMScaleChangerJan.cpp
//
// Purpose:  Class with a lookup table and code to change a given EMparticle 
//           from one eta-dependent scale calibration to another one
//
// Created:  02-AUG-2007  Jan Stark
//
// ////////////////////////////////////////////////////////////////////////////


#include <iostream.h>
#include "wmass_analysis/EMScaleChangerRunIIbJan.hpp"
#include "wmass_analysis/RunIIb4RelCalib.hpp"

EMScaleChangerRunIIbJan::EMScaleChangerRunIIbJan()
{

  // Fill look-up tables
  //

  _firstRun[0]=220000;
  _lastRun[0]=234999;
  _firstRun[1]=235000;
  _lastRun[1]=255321;
  _firstRun[2]=255322;
  _lastRun[2]=264053;
  _firstRun[3]=264054;
  _lastRun[3]=999999;

  // start with ones everywhere
  for (int i=1; i<=37; i++) {
    _correctionNorth[0][i]=1;
    _correctionSouth[0][i]=1;
    _correctionNorth[1][i]=1;
    _correctionSouth[1][i]=1;
    _correctionNorth[2][i]=1;
    _correctionSouth[2][i]=1;
    _correctionNorth[3][i]=1;
    _correctionSouth[3][i]=1;
  }
  //
  _correctionNorth[0][11]=9.84265e-01;
  _correctionNorth[0][10]=9.94412e-01;
  _correctionNorth[0][9]=9.93371e-01;
  _correctionNorth[0][8]=9.81506e-01;
  _correctionNorth[0][7]=9.86749e-01;
  _correctionNorth[0][6]=9.83713e-01;
  _correctionNorth[0][5]=9.95042e-01;
  _correctionNorth[0][4]=1.00001e+00;
  _correctionNorth[0][3]=9.91373e-01;
  _correctionNorth[0][2]=9.93699e-01;
  _correctionNorth[0][1]=9.90715e-01;
  _correctionSouth[0][1]=1.00144e+00;
  _correctionSouth[0][2]=9.98156e-01;
  _correctionSouth[0][3]=9.90965e-01;
  _correctionSouth[0][4]=9.92550e-01;
  _correctionSouth[0][5]=9.96919e-01;
  _correctionSouth[0][6]=9.89016e-01;
  _correctionSouth[0][7]=9.86544e-01;
  _correctionSouth[0][8]=9.84080e-01;
  _correctionSouth[0][9]=9.81089e-01;
  _correctionSouth[0][10]=9.78427e-01;
  _correctionSouth[0][11]=9.80762e-01;
  //
  _correctionNorth[1][11]=9.85089e-01;
  _correctionNorth[1][10]=9.98593e-01;
  _correctionNorth[1][9]=9.97969e-01;
  _correctionNorth[1][8]=9.89069e-01;
  _correctionNorth[1][7]=9.94951e-01;
  _correctionNorth[1][6]=9.87831e-01;
  _correctionNorth[1][5]=9.98956e-01;
  _correctionNorth[1][4]=1.00392e+00;
  _correctionNorth[1][3]=9.97656e-01;
  _correctionNorth[1][2]=9.99491e-01;
  _correctionNorth[1][1]=9.98412e-01;
  _correctionSouth[1][1]=1.00801e+00;
  _correctionSouth[1][2]=1.00094e+00;
  _correctionSouth[1][3]=9.97237e-01;
  _correctionSouth[1][4]=9.96719e-01;
  _correctionSouth[1][5]=1.00493e+00;
  _correctionSouth[1][6]=9.96008e-01;
  _correctionSouth[1][7]=9.87787e-01;
  _correctionSouth[1][8]=9.90594e-01;
  _correctionSouth[1][9]=9.82159e-01;
  _correctionSouth[1][10]=9.80160e-01;
  _correctionSouth[1][11]=9.85961e-01;
  //
  _correctionNorth[2][11]=9.78747e-01;
  _correctionNorth[2][10]=9.93635e-01;
  _correctionNorth[2][9]=9.84137e-01;
  _correctionNorth[2][8]=9.89050e-01;
  _correctionNorth[2][7]=9.86209e-01;
  _correctionNorth[2][6]=9.87214e-01;
  _correctionNorth[2][5]=9.95424e-01;
  _correctionNorth[2][4]=9.93264e-01;
  _correctionNorth[2][3]=9.90693e-01;
  _correctionNorth[2][2]=9.94613e-01;
  _correctionNorth[2][1]=9.90653e-01;
  _correctionSouth[2][1]=9.96189e-01;
  _correctionSouth[2][2]=9.91931e-01;
  _correctionSouth[2][3]=9.92653e-01;
  _correctionSouth[2][4]=9.96754e-01;
  _correctionSouth[2][5]=9.96105e-01;
  _correctionSouth[2][6]=9.90567e-01;
  _correctionSouth[2][7]=9.95823e-01;
  _correctionSouth[2][8]=9.84303e-01;
  _correctionSouth[2][9]=9.88695e-01;
  _correctionSouth[2][10]=9.88011e-01;
  _correctionSouth[2][11]=9.80809e-01;
  //
  _correctionNorth[3][11]=9.84372e-01;
  _correctionNorth[3][10]=9.81823e-01;
  _correctionNorth[3][9]=9.85060e-01;
  _correctionNorth[3][8]=9.88146e-01;
  _correctionNorth[3][7]=9.88032e-01;
  _correctionNorth[3][6]=9.90453e-01;
  _correctionNorth[3][5]=9.89717e-01;
  _correctionNorth[3][4]=9.91472e-01;
  _correctionNorth[3][3]=9.92819e-01;
  _correctionNorth[3][2]=9.94931e-01;
  _correctionNorth[3][1]=9.95582e-01;
  _correctionSouth[3][1]=9.96772e-01;
  _correctionSouth[3][2]=9.95708e-01;
  _correctionSouth[3][3]=9.93611e-01;
  _correctionSouth[3][4]=9.91772e-01;
  _correctionSouth[3][5]=9.91153e-01;
  _correctionSouth[3][6]=9.89483e-01;
  _correctionSouth[3][7]=9.91356e-01;
  _correctionSouth[3][8]=9.88981e-01;
  _correctionSouth[3][9]=9.86407e-01;
  _correctionSouth[3][10]=9.77295e-01;
  _correctionSouth[3][11]=9.81537e-01;

  _layfact[0][0]=-1e40;
  _layfact[0][1]=9.93601e-01;
  _layfact[0][2]=9.99940e-01;
  _layfact[0][3]=1.01700e+00;
  _layfact[0][4]=9.52381e-01;
  _layfact[0][5]=1;
  //
  _layfact[1][0]=-1e40;
  _layfact[1][1]=9.93601e-01;
  _layfact[1][2]=9.99940e-01;
  _layfact[1][3]=1.01700e+00;
  _layfact[1][4]=9.52381e-01;
  _layfact[1][5]=1;
  //
  _layfact[2][0]=-1e40;
  _layfact[2][1]=9.93601e-01;
  _layfact[2][2]=9.99940e-01;
  _layfact[2][3]=1.01700e+00;
  _layfact[2][4]=9.52381e-01;
  _layfact[2][5]=1;
  //
  _layfact[3][0]=-1e40;
  _layfact[3][1]=9.93601e-01;
  _layfact[3][2]=9.99940e-01;
  _layfact[3][3]=1.01700e+00;
  _layfact[3][4]=9.52381e-01;
  _layfact[3][5]=1;

  _layertrans[0]=0;
  _layertrans[1]=1;
  _layertrans[2]=2;
  _layertrans[3]=3;
  _layertrans[4]=3;
  _layertrans[5]=3;
  _layertrans[6]=3;
  _layertrans[7]=4;
  _layertrans[8]=0;
  _layertrans[9]=0;
  _layertrans[10]=0;
  _layertrans[11]=5;
  _layertrans[12]=0;
  _layertrans[13]=0;
  _layertrans[14]=0;
  _layertrans[15]=0;
  _layertrans[16]=0;
  _layertrans[15]=0;
  _layertrans[16]=0;
  _layertrans[17]=0;

  _runIIb4_calib = new RunIIb4RelCalib();

}


double EMScaleChangerRunIIbJan::NewScale(TMBEMCluster* empart, int runNum, bool debug)
{

  // figure out the index for this run
  int index=-1;
  for (int i=0; i<4; i++) {
    if ((runNum>=_firstRun[i])&&(runNum<=_lastRun[i])) {
      index=i;
      break;
    }
  }
  if (index<0) {
    cout<<endl<<endl;
    cout<<"EMScaleChangerRunIIbJan: Was asked to provide correction for run number "<<runNum<<"."<<endl;
    cout<<"                         I do not know how to deal with this run, and I will abort."<<endl;
    cout<<endl<<endl;
    assert(0);
  }

  // Get cells and loop over them
  if (!(empart->ncells()>0)) {
    cout<<endl<<endl;
    cout<<"EMScaleChangerRunIIbJan: Trying to change EM scale, but no cell-level information"<<endl;
    cout<<"                         is available."<<endl;
    cout<<"                         Will abort."<<endl;
    cout<<endl<<endl;
    assert(0);
  }
  double cellsum=0;
  double cellsumOld=0;
  double energy;
  double energyCorrected;
  int ieta;
  int layer;
  const TMBCaloCell* it;
  for(int i=0; i<empart->ncells(); i++){
    it=empart->GetCaloCell(i);
    energy=it->E();
    ieta=it->ieta();
    layer=it->layer();
    //
    if (runNum>=266376) {
      energy*=_runIIb4_calib->EnergyCorrection(ieta,it->iphi(),layer,runNum);
    }
    //
    if (ieta<0) {
      energyCorrected=_correctionNorth[index][abs(ieta)]*energy;
    } else {
      energyCorrected=_correctionSouth[index][ieta]*energy;
    }
    energyCorrected*=_layfact[index][_layertrans[layer]];
    cellsumOld+=energy;
    cellsum+=energyCorrected;
    if (debug) cout<<"     "<<ieta<<" "<<it->iphi()<<" "<<it->layer()<<" : "<<energy<<" -> "<<energyCorrected<<endl;
  }
  if (debug) cout<<"     Sum: "<<cellsumOld<<" -> "<<cellsum<<endl;
  return cellsum;

}


EMScaleChangerRunIIbJan::~EMScaleChangerRunIIbJan() {
}

