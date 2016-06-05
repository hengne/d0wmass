///////////////////////////////////////////////////////////////
//                                                           //
// Parabola1D.cpp - Class to fit a n-dimensional quadratic   //
//                  form using a chi2 method.                //
//                                                           //
// RCLSA. Created: 25 - Nov - 2009                           //
//                                                           //
// Revision: 1.0                                             //
//                                                           //
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//                                                           //
// The basic usage I have in mind is the following:          //
//                                                           //
// 1.   Parabola2D r(10, x, y, z);                           //
// 2.   TVectorD a = r.GetMinimum();                         //
// 3.   TMatrixDSym b = r.GetCovMatrix();                    //
// 4.   TF2* c = r.GetFunction();                            //
// 5.   TGraph2D* d = r.GetGraph();                          //
//                                                           //
// I think that's all the user needs.                        //
//                                                           //
///////////////////////////////////////////////////////////////

// ROOT stuff

#include <TROOT.h>
#include <TMath.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TString.h>
#include <TApplication.h>
#include <TVectorD.h>
#include <TMatrixDSym.h>
#include <TF1.h>
#include <TF2.h>
#include <TF3.h>
#include <TGraph.h>
#include <TGraph2D.h>

// C++ stuff

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

// RCLSA's routine

#include "Parabola.hpp"
#include "Parabola1D.hpp"

using namespace std;

Parabola1D::Parabola1D(int n, double* x, double* z) : Parabola() {

  // Prepare the members
  vector<double> entry_x;
  vector<double> entry_z;
  for(int i=0; i<n; i++){
    entry_z.push_back(z[i]);
    entry_x.push_back(x[i]);
  }
  entries.push_back(entry_z); // This is important for the logic of the code. The first vector
  entries.push_back(entry_x); // to be push back has to be "z".

  // And do the magic
  FillMatrix();    // Do the fitting...
  FindMinimum();   // Find the Minimum...
  
  // Write out the information. The order that the coefficients appear has to be in increasing key,
  // as explained above. THIS IS IMPORTANT.
  FitFunction = new TF1("FitFnc","[2]*x*x+[1]*x+[0]");
  for (int i = 0; i<3; i++) FitFunction->SetParameter(i,fit_coef_vec[i]);
  FitGraph = new TGraph(n,x,z);

}

Parabola1D::Parabola1D(vector<double> x, vector<double> z) : Parabola() {

  // Prepare the members
  entries.push_back(z);
  entries.push_back(x);

  // And do the magic
  FillMatrix();    // Do the fitting...
  FindMinimum();   // Find the Minimum...
  
  // Write out the information. The order that the coefficients appear has to be in increasing key,
  // as explained above. THIS IS IMPORTANT.
  FitFunction = new TF1("FitFnc","[2]*x*x+[1]*x+[0]");
  for (int i = 0; i<3; i++) FitFunction->SetParameter(i,fit_coef_vec[i]);
  int n = x.size();
  double entry_x[n];
  double entry_z[n];
  for(int i=0; i<n; i++) {
    entry_x[n]=x[n];
    entry_z[n]=z[n];
  }
  FitGraph = new TGraph(n,entry_x,entry_z);

}

Parabola1D::Parabola1D(TVectorD x, TVectorD z) : Parabola() {

  // Prepare the members
  int n = x.GetNoElements();
  double* vx = x.GetMatrixArray();
  double* vz = z.GetMatrixArray();
  vector<double> entry_x;
  vector<double> entry_z;
  for(int i=0; i<n; i++){
    entry_z.push_back(vz[i]);
    entry_x.push_back(vx[i]);
  }
  entries.push_back(entry_z); // _Has_ to be the first.
  entries.push_back(entry_x);

  // And do the magic
  FillMatrix();    // Do the fitting...
  FindMinimum();   // Find the Minimum...
  
  // Write out the information. The order that the coefficients appear has to be in increasing key,
  // as explained above. THIS IS IMPORTANT.
  FitFunction = new TF1("FitFnc","[2]*x*x+[1]*x+[0]");
  for (int i = 0; i<3; i++) FitFunction->SetParameter(i,fit_coef_vec[i]);
  FitGraph = new TGraph(n,vx,vz);

}

Parabola1D::Parabola1D(TGraph* data) : Parabola() {

  int n = data->GetN();
  Double_t x, z;
  // Prepare the members
  vector<double> entry_x;
  vector<double> entry_z;
  for(Int_t i=0; i<n; i++){
    data->GetPoint(i,x,z);
    entry_z.push_back(z);
    entry_x.push_back(x);
  }
  entries.push_back(entry_z); // _Has_ to be the first.
  entries.push_back(entry_x);

  // And do the magic
  FillMatrix();    // Do the fitting...
  FindMinimum();   // Find the Minimum...
  
  // Write out the information. The order that the coefficients appear has to be in increasing key,
  // as explained above. THIS IS IMPORTANT.
  FitFunction = new TF1("FitFnc","[2]*x*x+[1]*x+[0]");
  for (int i = 0; i<3; i++) FitFunction->SetParameter(i,fit_coef_vec[i]);
  FitGraph = (TGraph*)data->Clone();

}

Parabola1D::~Parabola1D() {

  delete FitFunction, FitGraph;

}

////////////////////////////////////////////////////////////////////////
//                                                                    //
// -- History --                                                      //
//                                                                    //
// As of 11/30/2009: Still have to write all the other constructors   //
// RCLSA             and debug. Check the order of the coefficients.  //
//                                                                    //
// As of 12/02/2009: Wrote some constructors and checked the order.   //
// RCLSA             Have to think about source of errors.            //
//                   Could have constructors to read from files.      //
//                                                                    //
// As of 12/03/2009: Fixed the derived constructors                   //
// RCLSA             Implemented LinkDef Makefile                     //
//                                                                    //
// As of 12/07/2009: Implemented the filter function                  //
// RCLSA             and the accessors to get the min chi2.           //
//                   Have to begin dbging soon.                       //
//                   Separated in smaller files.                      //
//                                                                    //
////////////////////////////////////////////////////////////////////////


