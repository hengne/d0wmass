#ifndef Parabola2D_HPP
#define Parabola2D_HPP

///////////////////////////////////////////////////////////////
//                                                           //
// Parabola2D.hpp - Class to fit a n-dimensional quadratic   //
//                  form using a chi2 method.                //
//                  Parabola 2D : Parabola                   //
//                  Wrapper class for 2D fittings            //
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

class Parabola2D : public Parabola {

private:

  TF2* FitFunction;
  TGraph2D* FitGraph;

public:

  Parabola2D(int n, double* x, double* y, double* z);
  Parabola2D(std::vector<double> x, std::vector<double> y, std::vector<double> z);
  Parabola2D(TVectorD x, TVectorD y, TVectorD z);
  ~Parabola2D();

  // Accessors
  TF2* GetFunction() const { return FitFunction; }
  TGraph2D* GetGraph() const { return FitGraph; }

};

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


#endif