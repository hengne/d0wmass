#include <string.h>
class  MySETFunction {
  
public: 
  
  MySETFunction(){
    double q[] = {0.301921, 0.720158, 0.0998661, -0.0119716, 0.000485981, 1.04286, 3.78046e-05, 1.04208, -4.92831e-05, 1.02651, 0.287561, 0.027304, -0.000261361, 9.88089e-07, -1.61813e-09, 9.58581e-13, 9.00124, 78.5431, 180, 409.135};
    memcpy(p, q, sizeof(p)); 
  }
  
  void setp(double *q, int start=0, int stop = 20){
    for (int i = 0; i < (stop-start); ++i){
      p[i+start] =  q[i];
    };
  }
  double Evaluate(double *x) {
    if (x[0] <= p[16]){
      return region1(x[0],p);
    }
    else if (x[0]  <= p[17]){
      return region2(x[0]-p[16],p);
      }
    else if (x[0]  <= p[18]){
      return region3(x[0]-p[17],p);
      }
    else if (x[0]  <= p[19]){
      return region4(x[0]-p[18],p);
    }
    else {
      return region5(x[0]-p[19],p);
    }
    
  }
  
  

private:
  double region1(double x, double *p){
    return (p[0] + p[1]*x + p[2]*x*x + p[3]*x*x*x + p[4]*x*x*x*x);
  }
  double region2(double x, double *p){
    return (p[5]*(x) + p[6]*x*x + region1(p[16],p) );
  }
  double region3(double x, double *p){
    return (p[7]*x + p[8]*x*x + region2(p[17]-p[16],p) );
  }
  double region4(double x, double *p){
    return (p[9]*x + region3(p[18]-p[17],p) );
  }
  double region5(double x, double *p){
    return (p[10]*x + p[11]*x*x + p[12]*x*x*x + p[13]*x*x*x*x  + p[14]*x*x*x*x*x  +  p[15]*x*x*x*x*x*x  + region4(p[19]-p[18],p) );
  }
  double p[20]; // = {0.301921, 0.720158, 0.0998661, -0.0119716, 0.000485981, 1.04286, 3.78046e-05, 1.04208, -4.92831e-05, 1.02651, 0.287561, 0.027304, -0.000261361, 9.88089e-07, -1.61813e-09, 9.58581e-13, 9.00124, 78.5431, 180, 409.135};
  // (0-1000)
  //x^2 / ndf = 1848 / 1262
  // prob = 6 e-25  
};
