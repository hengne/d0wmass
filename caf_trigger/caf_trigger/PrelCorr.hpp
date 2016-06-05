class PrelCorr {
public:
  PrelCorr(char* table);
  ~PrelCorr();

  double operator()(double e_raw, double eta);

private:
  unsigned int _nPT;
  double _logptmin;
  double _logptmax;
  double _deltalogpt;
  unsigned int _nEta;
  double _etamin;
  double _etamax;
  double _deltaeta;
  double** _table;

  inline double _linear1(double p, double f0, double f2){
    return f0 + p * (f2 - f0);
  }
  double _linear2(double p, double q, double f00, double f20, double f02, 
		 double f22);
};
