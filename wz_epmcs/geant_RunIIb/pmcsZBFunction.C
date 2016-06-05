#include <vector>
class  pmcsZBFunction {
  
public: 
  pmcsZBFunction(){;}
  void setp(double *q, int start=0, int stop = 4){
    for (int i = 0; i < (stop-start); ++i){
      p[i+start] =  q[i];
    };
  }
  
  void setp(std::vector<double> q, int start=0, int stop = 4){
    for (int i = 0; i < (stop-start); ++i){
      p[i+start] =  q.at(i);
    };
  }
  
  double Evaluate(double *x) {
    if (x[0] <= p[3]){
      return region1(x[0],p);
    }
    else {
      return region2(x[0]-p[3],p);
    }
  }
  
  
  
private:
  double region1(double x, double *p){
    return (p[0] + p[1]*x );
  }
  double region2(double x, double *p){
    return (p[2]*x + region1(p[3],p) );
  }
  double p[4];
  };
