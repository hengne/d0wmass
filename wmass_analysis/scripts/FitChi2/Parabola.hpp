#ifndef Parabola_HPP
#define Parabola_HPP

///////////////////////////////////////////////////////////////
//                                                           //
// Parabola.hpp - Class to fit a n-dimensional quadratic     //
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
#include <TObjArray.h>

// C++ stuff

#include <iostream>
#include <map>
#include <vector>

class Parabola {

protected:

  std::vector< std::vector<double> > entries;  // Value of the bins... the number of entries determine the dimensions. 
                                                 // Each vector of the vector contain the values of the bins and the 0th vector contains the function
  std::map<int,double> partial_sum;              // Partial sums
  TMatrixDSym coef_matrix;                       // Variable minimization matrix
  TVectorD coef_vector;                          // Variable minimization vector

  TVectorD param_vector;                         // Parameters minimization vector
  std::map<int, double> fit_coef;                // Coefficients of the quadratic form
  TVectorD fit_coef_vec;                         // Same thing, more convenient sometimes
  std::map<int, double>::iterator p;             // Iterator for the maps above
  TVectorD min_point;                            // Value of the parameters at the minimum
  double min_chi2;                               // Value of chi2 at the minimum
  TMatrixDSym cov_matrix;                        // Covariance matrix of the parameters
  double filter;                                 // Maximum value of chi^2 around which to fit. The value 0 means do not filter.

  void FillMatrix();          // Does the fitting
  void FindMinimum();         // Finds the minimum

  // Some useful functions to handle the maps:
  static int convert5(int num10);   // Converts a number in base10 to base5 
  static Bool_t IsValidCoef(int num); // Checks if the partialsum will be needed in the map 


public:

  // Accessors

  // The order of the parameters are determined by the the other given in the constructor.
  // For instance Parabola2D(x,y,z) sets x as parameter 0, y as parameter 1.

  TObjArray* MakeEllipse(int sigma, int param1, int param2, Bool_t UseSameCanvas=0, int ecolor=1);        
                                                                       // Draw contour for param1 and param2
  TMatrixDSym GetCovMatrix() const{ return cov_matrix; }               // Get covariance matrix for the parameters
  TVectorD GetMinimum() const { return min_point; }                    // Get the fitted value of parameters
  double GetUncertainty(int param1) const;                             // Returns uncertainty for param1 
  double GetCorrelation(int param1, int param2) const;                 // Returns correlation between param1 and param2

  Parabola() { filter=0; }                 // Default constructor. Do nothing.
  Parabola(std::vector<std::vector<double> > data); // General constructor.
  Parabola(const char* filename);          // This reads a file with data separated by a space
                                           // the file should be x_1i ... x_ni z_i in each line.
  virtual ~Parabola();                     // Destructor. The wrapper classes have more objects on the heap
                                           // so the destructor has to be specified.

  void SetChi2Filter(double filterval) { filter=filterval; }        // Define the chi2 filter.
  void Filter() { FillMatrix(); FindMinimum(); }                       // Apply the filter
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
//                   Separated in smaller files.                      //
//                                                                    //
////////////////////////////////////////////////////////////////////////


#endif
