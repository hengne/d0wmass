//
// $Id: draw_ellipse.hpp,v 1.1 2010/01/26 21:35:23 rclsa Exp $
//
// File: draw_ellipse.cpp
// Purpose: 
// Created: 26-FEB-2009   
//
// $Revision: 1.1 $
//
//

// Include files
#include "TCanvas.h"
#include "TMarker.h"

// Global definitions

TObject* error_ellipse(double dChi2, double x0, double y0, 
		       double sx, double sy, double correlation, 
		       bool useInversion=true);



// Constructors/Destructors
TObjArray* draw_ellipse(double dChi2, double x0, double y0,
			double sx, double sy, double correlation,
			bool useCurrentCanvas=false, int eColor=1)
{
  TF1 *f = (TF1*)error_ellipse(dChi2,x0,y0,sx,sy,correlation);
  if( !useCurrentCanvas ) {
    double scale = 1.5*sqrt(dChi2);
    TCanvas *tc = new TCanvas();
    tc->DrawFrame(x0-scale*sx,y0-scale*sy,x0+scale*sx,y0+scale*sy);
  }
  f->SetLineColor(eColor);
  f->SetParameter(6,1);
  f->DrawCopy("same");
  f->SetParameter(6,-1);
  f->DrawCopy("same");
  TMarker *x0y0 = new TMarker(x0,y0,20);
  x0y0->SetMarkerColor(eColor);
  x0y0->Draw();
  return 0;
}
/*
// Make these settable trivially from the command line
double dchi2=1.0;
double x0=0,y0=0;
double sx=1.0, sy=2.0, correlation = 0.95;

test_draw_ellipse()
{
  cout << "------------" << endl;
  draw_ellipse(dchi2,x0,y0,sx,sy,0);
  cout << "------------" << endl;
  draw_ellipse(dchi2,x0,y0,sx,sy,correlation,true,2);
  cout << "------------" << endl;
  draw_ellipse(dchi2,x0,y0,sx,sy,-correlation,true,4);
  cout << "------------" << endl;
}
// Accessors
*/

