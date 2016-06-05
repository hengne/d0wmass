///////////////////////////////////////////////////////////////
//                                                           //
// Parabola2D.cpp - Class to fit a n-dimensional quadratic   //
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
// 3.   TMatrixdSym b = r.GetCovMatrix();                    //
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
#include "Parabola2D.hpp"

using namespace std;

Parabola2D::Parabola2D(int n, double* x, double* y, double* z) : Parabola() {

  // Prepare the members
  vector<double> entry_x;
  vector<double> entry_y;
  vector<double> entry_z;
  for(int i=0; i<n; i++){
    entry_x.push_back(x[i]);
    entry_y.push_back(y[i]);
    entry_z.push_back(z[i]);
  }
  entries.push_back(entry_z); // _Has_ to be the first.
  entries.push_back(entry_x);
  entries.push_back(entry_y);

  // And do the magic
  FillMatrix();    // Do the fitting...
  FindMinimum();   // Find the Minimum...
  
  // Write out the information. The order that the coefficients appear has to be in increasing key,
  // as explained above. THIS IS IMPORTANT.
  FitFunction = new TF2("FitFnc","[5]*y*y+[4]*y*x+[3]*y+[2]*x*x+[1]*x+[0]");
  for (int i = 0; i<6; i++) FitFunction->SetParameter(i,fit_coef_vec[i]);
  FitGraph = new TGraph2D(n,x,y,z);

}

Parabola2D::Parabola2D(vector<double> x, vector<double> y, vector<double> z) : Parabola() {

  // Prepare the members
  entries.push_back(z); // _Has_ to be the first.
  entries.push_back(x);
  entries.push_back(y);

  // And do the magic
  FillMatrix();    // Do the fitting...
  FindMinimum();   // Find the Minimum...
  
  // Write out the information. The order that the coefficients appear has to be in increasing key,
  // as explained above. THIS IS IMPORTANT.
  FitFunction = new TF2("FitFnc","[5]*y*y+[4]*y*x+[3]*y+[2]*x*x+[1]*x+[0]");
  for (int i = 0; i<6; i++) FitFunction->SetParameter(i,fit_coef_vec[i]);
  int n = x.size();
  double entry_x[n];
  double entry_y[n];
  double entry_z[n];
  for(int i=0; i<n; i++) {
    entry_x[n]=x[n];
    entry_y[n]=y[n];
    entry_z[n]=z[n];
  }
  FitGraph = new TGraph2D(n,entry_x,entry_y,entry_z);

}


Parabola2D::Parabola2D(TVectorD x, TVectorD y, TVectorD z) : Parabola() {

  // Prepare the members
  int n = x.GetNoElements();
  double* vx = x.GetMatrixArray();
  double* vy = y.GetMatrixArray();
  double* vz = z.GetMatrixArray();
  vector<double> entry_x;
  vector<double> entry_y;
  vector<double> entry_z;
  for(int i=0; i<n; i++){
    entry_x.push_back(vx[i]);
    entry_y.push_back(vy[i]);
    entry_z.push_back(vz[i]);
  }
  entries.push_back(entry_z); // _Has_ to be the first.
  entries.push_back(entry_x);
  entries.push_back(entry_y);

  // And do the magic
  FillMatrix();    // Do the fitting...
  FindMinimum();   // Find the Minimum...
  
  // Write out the information. The order that the coefficients appear has to be in increasing key,
  // as explained above. THIS IS IMPORTANT.
  FitFunction = new TF2("FitFnc","[5]*y*y+[4]*y*x+[3]*y+[2]*x*x+[1]*x+[0]");
  for (int i = 0; i<6; i++) FitFunction->SetParameter(i,fit_coef_vec[i]);
  FitGraph = new TGraph2D(n,vx,vy,vz);

}


Parabola2D::~Parabola2D() {

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
//                   Separated in smaller files                       //
//                                                                    //
////////////////////////////////////////////////////////////////////////



