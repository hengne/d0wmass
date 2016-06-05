//
// $Id: error_ellipse.hpp,v 1.1 2010/01/26 21:35:23 rclsa Exp $
//
// File: example08.cpp
// Purpose: Plot the 1sigma and 2 sigma error ellipses for from a fit to 
//   a 2-parameter function in the parabolic approximation.
//
//   This is pretty straightforward code, except two choices can be made for
//   the ploting:
//        1. invert the chi^2 into y(x;sigma's,chi2) and plot curves
//        2. Make a function from chi^2, and allow root to determine the
//             contours
//

#include <iostream>
#include "TF1.h"
#include "TF2.h"
#include "TMatrixD.h"

using  namespace std;

void print(const char *tag, const TMatrixD &m)
{
  cout << "Matrix " << tag << endl;
  for( int r=0 ; r<2 ; r++ ) {
    for( int c=0 ; c<2 ; c++ ) cout << "   " << m[r][c];
    cout << endl;
  }
}

// Compute the curvature matrix
TMatrixD get_curvature_matrix(double sx, double sy, double correlation)
{
  TMatrixD errMat(2,2);
  errMat[0][0] = sx*sx;              errMat[0][1] = sx*sy*correlation;
  errMat[1][0] = sx*sy*correlation;  errMat[1][1] = sy*sy;
  return errMat.Invert();
}

// y-value for mimimum and maximum x
double* yForxMinMax(double dChi2, double x0, double y0, TMatrixD &curvMat)
{
  double cxx = curvMat[0][0];
  double cxy = curvMat[0][1];
  double cyy = curvMat[1][1];
  //print("curvMat",curvMat);
  //cout << " cxx = " << cxx << ", cxy = " << cxy << ", cyy = " << cyy << endl;

  double numer = cyy*dChi2;
  double denom = (cxx*cyy-cxy*cxy);
  double discrim = numer/denom;
  //cout << discrim << endl;

  double *ym = new double[2];
  ym[0] = y0 - (cxy/cyy)*sqrt(discrim);
  ym[1] = y0 + (cxy/cyy)*sqrt(discrim);
  if( ym[0]>ym[1] ) {
    double tmp = ym[1];
    ym[1] = ym[0];
    ym[0] = tmp;
  }
  cout << "y(x_min) = " << ym[0] << ", y(x_max) = " << ym[1] << endl;
  return ym;
}

double error_ellipse_dx=0.0025;

// Minimum x or maximum x
double* xMinMax(double dChi2, double x0, double y0, TMatrixD &curvMat)
{
  // Set up
  double *yM = yForxMinMax(dChi2, x0, y0, curvMat);
  double cxx = curvMat[0][0];
  double cxy = curvMat[0][1];
  double cyy = curvMat[1][1];

  // Compute.  NB: Because this depends only on (yM-y0)^2, can use either
  //   value yM[0] or yM[1].
  double disc = cxx*dChi2 + (cxy*cxy-cxx*cyy)*(yM[0]-y0)*(yM[0]-y0);
  if( disc<0 ) cout << "Error: discrminant<0." << endl;

  // and more
  double *xM = new double[2];
  if( cxy>=0 ) {
    xM[0] = x0 - cxy/cxx*(yM[0]-y0) + sqrt(disc)/cxx;
    xM[1] = x0 - cxy/cxx*(yM[1]-y0) - sqrt(disc)/cxx;
  }
  else {
    xM[0] = x0 - cxy/cxx*(yM[0]-y0) - sqrt(disc)/cxx;
    xM[1] = x0 - cxy/cxx*(yM[1]-y0) + sqrt(disc)/cxx;
  }

  // just add a little bit to the range so that root closes the ellipses.
  // Be careful to make sure that one adjusts in the proper direction!  The
  // factor is impirical, from looking at the curves.  THIS IS A KLUDGE.
  double dx = error_ellipse_dx;
  if( xM[1]>xM[0] ) { 
    xM[0] = xM[0] - dx*(xM[1]-xM[0]);
    xM[1] = xM[1] + dx*(xM[1]-xM[0]);
  }
  else {
    xM[0] = xM[0] + dx*(xM[0]-xM[1]);
    xM[1] = xM[1] - dx*(xM[0]-xM[1]);
  }
  //cout << "xMin = " << xM[0] << ", xMax = " << xM[1] << endl;

  // Clean up
  delete[] yM;
  return xM;
}

TObject* error_ellipse(double dChi2, double x0, double y0, 
		       TMatrixD &curMat, bool useInversion=true) 
{
  if( useInversion ) { // Solve chi2 as y(x), and plot it this way
    // This results from solving
    //   dChi^2 = cxx*(y-y0)^2 + cyy*(y-y0)^2 + 2*cxy*(x-x0)*(y-y0)
    // as y(x;x0,y0,cxx,cxy,cyy,chi2,sign).  The parameter "sign"
    // determines the sign on the discriminant.
    //   par[0] = x0
    //   par[1] = y0
    //   par[2] = cxx
    //   par[3] = cxy
    //   par[4] = cyy
    //   par[5] = dChi2
    //   par[6] = sign
    // 
    double *xM = xMinMax(dChi2,x0,y0,curMat);
    char *fdef = "[1]-[3]/[4]*(x-[0])+[6]*sqrt(([3]*[3]-[2]*[4])*(x-[0])*(x-[0])+[4]*[5])/[4]";
    TF1* fcn = new TF1("fcn",fdef);
    fcn->SetRange(xM[0],xM[1]);
    fcn->SetNpx(1000);
    // Draw the 2 sigma contour (twice).  Use a separate function for the
    // first one so that we can change the axes despite Root's idiosyncracies.
    fcn->SetLineColor(4);
    fcn->SetParameter(0,x0);             fcn->SetParName(0,"x0");
    fcn->SetParameter(1,y0);             fcn->SetParName(1,"y0");
    fcn->SetParameter(2,curMat[0][0]);   fcn->SetParName(2,"cxx");
    fcn->SetParameter(3,curMat[0][1]);   fcn->SetParName(3,"cxy");
    fcn->SetParameter(4,curMat[1][1]);   fcn->SetParName(4,"cyy");
    fcn->SetParameter(5,dChi2);          fcn->SetParName(5,"DeltaChi2");
    fcn->SetParameter(6,1);              fcn->SetParName(6,"Sign = +-1");
    return fcn;
  }
  else { // Fill a TH2 and make a surface
    double *xM = xMinMax(dChi2,x0,y0,curMat);
    char *fdef2 = "(x-[0])*(x-[0])*[2] + 2*(x-[0])*(y-[1])*[3]+(y-[1])*(y-[1])*[4]";
    TF2 *fcn2 = new TF2("fcn2",fdef2);
    fcn2->SetRange(2*sqrt(dChi2)*xM[0],2*sqrt(dChi2)*xM[1]);
    fcn2->SetNpx(1000);
    // Draw the 2 sigma contour (twice).  Use a separate function for the
    // first one so that we can change the axes despite Root's idiosyncracies.
    fcn2->SetParameter(0,x0);             fcn2->SetParName(0,"x0");
    fcn2->SetParameter(1,y0);             fcn2->SetParName(1,"y0");
    fcn2->SetParameter(2,curMat[0][0]);   fcn2->SetParName(2,"cxx");
    fcn2->SetParameter(3,curMat[0][1]);   fcn2->SetParName(3,"cxy");
    fcn2->SetParameter(4,curMat[1][1]);   fcn2->SetParName(4,"cyy");
    return fcn2;
  }
  return 0;
}

TObject* error_ellipse(double dChi2, double x0, double y0, 
		       double sx, double sy, double correlation=0.0, 
		       bool useInversion) 
{
  // Meaningless for a high correlation.  It's just a straight line, but for
  // now just bail out.
  if( correlation==1.0 || correlation==(-1) ) {    
    return 0;
  }

  // Get the curvature matrix for use in the chi^2 calculation
  TMatrixD curMat = get_curvature_matrix(sx,sy,correlation);

  // and then do the usual call
  return error_ellipse(dChi2, x0, y0, curMat, useInversion);
}
