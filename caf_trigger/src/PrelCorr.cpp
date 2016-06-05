//file: PrelCorr.cpp {PrelCorr.hpp}
//
//Author:   Alexander Kupco <kupco@fzu.cz>
//
//Purpose:  Provide a correction factor ("C" factor) between preliminary and final JES, defined as 
//          C = kJES_MC(prelim)/kJES_MC(final) 
//          in terms of raw pT and deteta
//
//History:  Liang Li: changed original function (which is in terms of raw energy) to be in terms of raw pT

#include "caf_trigger/PrelCorr.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

PrelCorr::PrelCorr(char* table) : _nPT(), _nEta(), _table() {
  using namespace std;

  ifstream f(table);
  if ( f ) {
    string s;
    unsigned int n;
    double a;
    double b;

    f >> s >> n >> a >> b;
    _nPT = n;
    _logptmin = log(a);
    _logptmax = log(b);

    //cout << "s = " << s << ", n = " << n << ", a = " << a << ", b =" << b << endl;

    f >> s >> n >> a >> b;
    _nEta = n;
    _etamin = a;
    _etamax = b;

    //cout << "s = " << s << ", n = " << n << ", a = " << a << ", b =" << b << endl;

    f >> s;
    if (s != "#") {
	cerr << table << " format error at line 3" << endl;
	exit(1);
    }	
  }
  else {
    cerr << "Unable to open file "<< table << endl;
    exit(1);
  }

  _deltalogpt = (_logptmax - _logptmin) / (_nPT - 1);
  _deltaeta = (_etamax - _etamin) / (_nEta - 1);

  _table = new double*[_nPT];
  for(unsigned int iPT = 0; iPT < _nPT; iPT++) {
    _table[iPT] = new double[_nEta];
  }

  for(unsigned int iPT = 0; iPT < _nPT; iPT++) {
    for(unsigned int iEta = 0; iEta < _nEta; iEta++) {
      f >> _table[iPT][iEta];
    }
  }

}

double PrelCorr::operator()(double raw_pt, double eta) {
  using namespace std;
  
  double logpt = log(raw_pt);
  if (logpt < _logptmin) logpt = _logptmin;
  if (logpt > _logptmax) logpt = _logptmax;

  double d_idxpt = (logpt - _logptmin) / _deltalogpt;
  int idxpt = (int) d_idxpt;
  if (idxpt < 0) idxpt = 0;
  if (idxpt >= (_nPT - 1)) idxpt = _nPT - 2;
  double f_pt = d_idxpt - idxpt;

  if (eta < _etamin) eta = _etamin;
  if (eta > _etamax) eta = _etamax;
  double d_eta = (eta - _etamin) / _deltaeta;

  int idxeta = (int) d_eta;
  if (idxeta < 0)  idxeta = 0;
  if (idxeta >= (_nEta - 1))  idxeta = _nEta - 2;
  double f_eta = d_eta - idxeta;

  /*  
  cout << "Eta = " << eta << ", ieta = " << idxeta << ", f_eta = " << f_eta << endl
       << "PT  = " << exp(logpt) << ", ipt = " << idxpt << ", f_pt = " << f_pt << endl
    ;
  */

  return _linear2(f_pt, f_eta, _table[idxpt][idxeta], _table[idxpt + 1][idxeta],
		  _table[idxpt][idxeta + 1], _table[idxpt + 1][idxeta + 1]);
}

PrelCorr::~PrelCorr() {
  if (_table) {
    for(unsigned int iPT = 0; iPT < _nPT; iPT++) {
      if (_table[iPT]) delete [] _table[iPT];
    }
    delete [] _table;
  }
}

double PrelCorr::_linear2(double p, double q, double f00, double f20, double f02, 
		 double f22){
    double f1 = _linear1(p, f00, f20);
    double f2 = _linear1(p, f02, f22);
    return _linear1(q, f1, f2);
  }
