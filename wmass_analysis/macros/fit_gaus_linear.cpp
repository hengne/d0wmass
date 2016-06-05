Double_t GausLinearFit(Double_t *x, Double_t *par){
  Double_t arg=0.;

  if(par[2]!=0) arg=(x[0]-par[1])/par[2];

  Double_t gaus = par[0]*TMath::Exp(-0.5*arg*arg);

  Double_t linear = par[3]*x[0] + par[4];

  fitval = gaus + linear;
  return fitval;
}



