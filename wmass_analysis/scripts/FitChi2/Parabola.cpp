///////////////////////////////////////////////////////////////
//                                                           //
// Parabola.cpp - Class to fit a n-dimensional quadratic     //
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

// JH's routine

#include "draw_ellipse.hpp"
#include "error_ellipse.hpp"

// RCLSA's routine

#include "Parabola.hpp"


using namespace std;

Parabola::~Parabola() {}

void Parabola::FillMatrix() {

  // To fit a quadratic function we need sums up to the fourth power. 
  int nsums = (int) TMath::Power(5,entries.size()); 

  // Number of accepted and filtered data points
  double acc = 0.0;
  double rej = 0.0;

  // The entries in partial sum will be mapped to the powers of the parameters, the first number being the measured value. For instante, 321 means the sum x^3y^2z^1
  for(int i=0; i<nsums; i++) {
    int key = convert5(i);

    partial_sum[key]=0;

    // Fill the vector as described above
    for(int k=0; k<entries[0].size(); k++) {

      // The idea hereis to define an possibility of filtering the data above certain range of min_chi2
      // Of course this has to be a late call (this.Filter()) since in the constructor it will calculate min_chi2
      // for the first time
      if (filter && min_chi2 && entries[0][k] > (filter+min_chi2)) { rej++; continue; }
      acc++;

      double temp_sum = 1.0;
      for(int j=0; j<entries.size(); j++) {

	temp_sum*=TMath::Power(entries[j][k],(((int)(key/TMath::Power(10,j)))%10));
      }

      partial_sum[key]+=temp_sum;
    }

  }

  // Print a warn message if the filtering was too harsh
  if (rej/(acc+rej) > 0.6) {
    cout << "Warning: Only " << acc*100/(rej+acc) << "% of the events were taken into account." << endl;
    cout << "Warning: You should consider making a the grid with a more restricted range." << endl;
  }

  // Now that we have all the partial sums, we fill the derivative matrix of the d\chi^2/da_j=\sum_i (z_i-f(x_i,a_i))^2x^j where j is the same mapping as above.
  // For instance, in the 2D case, the function is (a_{200}x^2 + a_{020}y^2 + a_{110}xy + a_{100}x + a_{010}y + a_{000})
  // So, (half of) the derivative with respect to a_{200} will involve the sums ps_{201} ps_{400} ps_{220} ps_{310} ps_{300} ps_{210} ps_{200}

  // The terms in the function are those whose sum are up to 2, including 2. To determine the order, I'll assume increasing ordering.
  // For instante, for the 2D case, a_{000}, a_{010}, a_{020}, a_{100}, a_{110}, a_{200}
  // There are 2n+1+n(n-1)/2 coefficients for a n dimensional quadratic form

  int dimension = 2*(entries.size()-1)+1+(entries.size()-1)*(entries.size()-2)/2;


  coef_matrix.ResizeTo(dimension,dimension);
  coef_vector.ResizeTo(dimension);
  fit_coef_vec.ResizeTo(dimension);

  int c1=0;
  int c2=0; // Just counters

  for(int i=0; i<nsums; i++){
    if(IsValidCoef(i)) {
      c2=0;
      int deriv=convert5(i);

      for(int j=0; j<nsums; j++){
	if(IsValidCoef(j)) {
	  int param=convert5(j);
	  double matrixelem = partial_sum[deriv+param];

	  coef_matrix[c1][c2] = matrixelem;
	  c2++;
	}
      }
      coef_vector[c1]=partial_sum[deriv+1];

      c1++;
    }
  }

  // Now it's easy to calculate the coefficients of the fit
  TMatrixDSym m(coef_matrix);
  m.Invert();
  fit_coef_vec=m*coef_vector;

  // And uses the same idea to stash the values into a map
  c1=0;
  for(int i=0; i<nsums; i++){
    if(IsValidCoef(i)) {
      int coef_key=convert5(i);
      fit_coef[coef_key]=fit_coef_vec[c1];

      c1++;
    }
  }

}

/*static*/ int Parabola::convert5(int num10) {
  
  int key = 0;
  int base10 = 1;
  int base5 = num10;
  
  // Convert to base 5 to make the key
  while(base5>4) {
    key+=(base5%5)*base10;
    base10*=10;
    base5/=5;
  }
  key+=base5*base10;
  return key;
}

/*static*/ Bool_t Parabola::IsValidCoef(int num) { 

  // Convert to base 5
  // Verify if first number is 0
  // Sum numbers and verify if it is less of equal to 2

  int base5 = convert5(num);
  if (base5%10 != 0) return false;
  
  int j=1;
  int sum = 0;
  sum+=base5%10;
  while(base5>4) {
    base5/=10;
    sum+=base5%10;
  }

  if(sum > 2) return false;
  
  return true;

}
  
void Parabola::FindMinimum() {
  
  // The idea here is simple: Derive the functions found using an iterator.
  // Prepare matrices to solve the linear algebra problem d\chi^2/dx = 0
  // Solve it and find the minimum
  // Derive again and fill the covariance matrix.

  int paramnum = entries.size()-1;

  cov_matrix.ResizeTo(paramnum,paramnum);
  param_vector.ResizeTo(paramnum);
  min_point.ResizeTo(paramnum);
  

  // Fill the error matrix by taking the derivative and then invert to find the covariance matrix
  for(p = fit_coef.begin(); p != fit_coef.end(); p++){
    int key = p->first;
    if(key == 0) continue;
    double val = p->second;

    int c1=0;
    int c2=0;
    int factor=1;

    int i=1;
    key/=10; // In the coefficients the first digit is always 0

    while(key>0) {
      int digit = key%10;

      if(c1 != 0) {
	if (digit == 1) {
	  c2=i;

	  break;
	}
      }
      if(c1 == 0) {
	if(digit == 1) c1=i;
	if(digit == 2) {
	  c1=i;
	  c2=i;
	  factor=2;

	  break;
	}
      }
      i++;
      key/=10;
    }

    if((c2 != 0)&&(c1 != 0)) {
      cov_matrix[c1-1][c2-1]=factor*val;

    }
    if((c2 == 0)&&(c1 != 0)) {
      param_vector[c1-1]=-val;

    }
  }

  cov_matrix.Invert();

  min_point = cov_matrix*param_vector;
  //  cout << "The minimum point is" << endl;
  // min_point.Print();
  cov_matrix*=2; // The covariance matrix is defined as (1/2 d\chi^2/dx_id_xj)^{-1}. The inverse of 1/2 is taken into account here.
  
  //   cout << "The covariance matrix is" << endl;
  //   cov_matrix.Print();
  // Now scan the coefficients again to fill the minimum value of chi2
  min_chi2 = 0.0;
  for(p = fit_coef.begin(); p != fit_coef.end(); p++){
    int key = p->first;
    double val = p->second;
    int coefpos = 0;
    double temp_sum = 1.0;
    key/=10; // In the coefficients the first digit is always 0
    while(key>0) {
      int digit = key%10;
      temp_sum*=TMath::Power(min_point[coefpos],digit);
      key/=10;
      coefpos++;
    }
    min_chi2+=val*temp_sum;
  }
  
}

TObjArray* Parabola::MakeEllipse(int sigma, int param1, int param2, Bool_t UseSameCanvas, int ecolor) {

  // Just use JH's routine

  return  draw_ellipse(sigma, min_point[param1], min_point[param2], TMath::Sqrt(cov_matrix[param1][param1]), TMath::Sqrt(cov_matrix[param2][param2]),
		       cov_matrix[param1][param2]/(TMath::Sqrt(cov_matrix[param1][param1]*cov_matrix[param2][param2])),
		       UseSameCanvas, ecolor);
  
}

double Parabola::GetUncertainty(int param1) const {

  return TMath::Sqrt(cov_matrix[param1][param1]);

}

double Parabola::GetCorrelation(int param1, int param2) const {

  return (cov_matrix[param1][param2]/TMath::Sqrt(cov_matrix[param1][param1]*cov_matrix[param2][param2]));

}

Parabola::Parabola(vector< vector<double> > data) : entries(data), filter(0) {

  // Really simple constructor
  // Has to be provided in the right order
  // data[0] ... z
  // data[1] ... x_1 and so on...
  FillMatrix();
  FindMinimum();

}

Parabola::Parabola(const char* filename) : filter(0){

  // Opens the file for input
  ifstream file;
  file.open(filename, ifstream::in);

  // Vector in the inverted order to get the values from file. Here the vector
  // will be something like ((x y w ... z), ...)
  vector< vector<double> > inv_entries;

  // Read the file in the format x y w ... z 
  TString a;
  vector<double> temp_entries;
  while(file.good()) {
    char b;
    b = file.get();
    if(b != '\n') {
      file.putback(b);
      a.ReadToken(file);
      temp_entries.push_back(a.Atof());

    } 
    else {
      inv_entries.push_back(temp_entries);
      temp_entries.clear();
    }
  }

  int n = inv_entries[0].size();
  int m = inv_entries.size();

  temp_entries.clear();
  for (int j=0; j < m; j++) {
    temp_entries.push_back(inv_entries[j][n-1]);
  }
  entries.push_back(temp_entries); // There is something wrong with my brain.

  for (int i = 0; i < n-1; i++) {
    temp_entries.clear();
    for(int j = 0; j < m; j++) {
      temp_entries.push_back(inv_entries[j][i]);
    }
    entries.push_back(temp_entries);    
  }

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
// As of 01/24/2010: Destructors rewritten due to compilation/linking // 
// RCLSA             errors (there is no really virtual destructor).  //
//                                                                    //
////////////////////////////////////////////////////////////////////////

