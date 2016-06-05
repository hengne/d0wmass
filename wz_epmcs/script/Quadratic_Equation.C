/////////////////////////////////////////////////////////////
// Code used to solve cubic equatuion
//    a*x**2 + b*x + c = 0
// translated from web: http://www.1728.com/quartic.htm
/////////////////////////////////////////////////////////////

#include <iomanip>
#include <iostream>

using namespace std;

void Quadratic_Equation(double a, double b, double c, 
			double& x1, double& x2) {
  
  double tmp = b*b - 4*a*c;

  if(tmp >= 0) {
    x1 = (-b+sqrt(tmp))/(2*a);
    x2 = (-b-sqrt(tmp))/(2*a);
  } else {
    cout << "Image values, will implement later" << endl;
  }
}






