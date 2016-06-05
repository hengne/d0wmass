#ifndef Functions_hpp
#define Functions_hpp

#include <cmath>
#include <iostream>
#include <iostream>
#include "TStyle.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include <iomanip>

float DeltaPhi(float phi1, float phi2)
{
  const Float_t Pi=3.1416;
  float dphi=phi1-phi2;

  if(dphi> Pi) dphi -= 2*Pi;
  if(dphi<-Pi) dphi += 2*Pi;

  return dphi;
}

bool HotRegion(float eta, float phi, float eta_low, float eta_high, float phi_low, float phi_high)
{
  bool hot=false;
  if (eta>=eta_low && eta<=eta_high && phi>=phi_low && phi<=phi_high) hot=true; 
  return hot;
}

float DETECTOR_ETA(Float_t ZVTX_, Float_t ETA_)
{
const float RCC=91.6,ZCC_MAX=135.85,ZEC=178.9; // EM3,eta=1.2@90cm,EM3
      float THETA,DTHETA,Z1,R,Z,ETAD;
      float ETA = ETA_;
      float ZVTX =  ZVTX_ ;
//-------------------------------------------------------------
// Assume in CC
   
   THETA = 2*atan(exp(-ETA));
   DTHETA = tan(THETA);

   if (DTHETA == 0.0) {
       if (THETA == 0.0) ETAD = 10.0;
       if (THETA != 0.0) ETAD =-10.0;
       return ETAD;
   }

   Z1 = ZVTX + RCC/DTHETA;

   if (fabs(Z1) <= ZCC_MAX) { //in CC
       R = RCC;
       Z = Z1;
   }
   if (fabs(Z1)  > ZCC_MAX) { //in EC
       if(cos(THETA)>0) {
	  R = (ZEC - ZVTX)*DTHETA;
	  Z = ZEC;
       }
       if(cos(THETA)<=0) {
	  R = -(ZEC + ZVTX)*DTHETA;
	  Z = -ZEC;
       }
   }

   ETAD = Z/R + sqrt(1.0+(Z/R)*(Z/R));

   if (ETAD <= 0) ETAD = -10;
   if (ETAD > 0 ) ETAD = log(ETAD);

   return ETAD;
}

float Distance(float eta1, float phi1, float eta2, float phi2)
{
  float D_eta=eta1-eta2;
  float D_phi=DeltaPhi(phi1,phi2);
  float dR=sqrt(D_eta*D_eta + D_phi*D_phi);
  return dR;
}

float Mass(Float_t px1, Float_t py1, Float_t pz1, Float_t px2, Float_t py2, Float_t pz2)
{
    float p1 = sqrt(px1*px1+py1*py1+pz1*pz1);    
    float p2 = sqrt(px2*px2+py2*py2+pz2*pz2);	 
    float dotproduct = px1*px2+py1*py2+pz1*pz2; 
    float mass = 2*(p1*p2 - dotproduct);    
	  mass = sqrt(mass);
    return mass;
}

void SetBinomialErrors(Int_t N_of_bins, TH1F* num, TH1F* den, TH1F* eff)
{
   for (Int_t i_bin=1; i_bin <= N_of_bins; i_bin++) 
   {
        Float_t x = num->GetBinContent(i_bin);
        Float_t n = den->GetBinContent(i_bin);
        Float_t Binomial_Error;
        if(n==0)  Binomial_Error=0;
        if(n!=0){  
        	if (x>n){
        	   std::cout<<"WARNING from void SetBinomialErrors():  num > den: "<<x<<" > "<<n<<" in bin "<<i_bin<<std::endl;
        	   std::cout<<"error is calculated differently (uncorrelated)"<<std::endl;
        	   Binomial_Error=(x/n)*sqrt(1/x+1/n);
        	   //std::cout<<"num and den are swapped"<<std::endl;
        	   //Binomial_Error=(1/x)*sqrt(n*(1-n/x));
        	}
            else{
        	   Binomial_Error=(1/n)*sqrt(x*(1-x/n));
            }
        }
        eff->SetBinError(i_bin,Binomial_Error);
   }
}

void SetBinomialErrors(Int_t N_of_bins, TH1* num, TH1* den, TH1* eff)
{
   for (Int_t i_bin=1; i_bin <= N_of_bins; i_bin++) 
   {
        Float_t x = num->GetBinContent(i_bin);
        Float_t n = den->GetBinContent(i_bin);
        Float_t Binomial_Error;
        if(n==0)  Binomial_Error=0;
        if(n!=0){  
        	if (x>n){
        	   std::cout<<"WARNING from void SetBinomialErrors():  num > den: "<<x<<" > "<<n<<" in bin "<<i_bin<<std::endl;
        	   std::cout<<"error is calculated differently (as uncorrelated)"<<std::endl;
        	   Binomial_Error=(x/n)*sqrt(1/x+1/n);
        	   //std::cout<<"error is calculated differently (num,den flipped)"<<std::endl;
               //Binomial_Error=(1/x)*sqrt(n*(1-n/x));


        	}
            else{
        	   Binomial_Error=(1/n)*sqrt(x*(1-x/n));
            }
        }
        eff->SetBinError(i_bin,Binomial_Error);
   }
}
//h->gammagamma 2007 logbook, page 92
void SetErrorsOnTH2Kfactor(Int_t N_of_bins_X, Int_t N_of_bins_Y, TH2* num_unweighted, TH2* den_unweighted, TH2* corr_weighted){
   for (Int_t i_bin=1; i_bin <= N_of_bins_X; i_bin++) 
   {
	   for (Int_t j_bin=1; j_bin <= N_of_bins_Y; j_bin++) 
	   {
        	Float_t x = num_unweighted->GetBinContent(i_bin,j_bin);
        	Float_t n = den_unweighted->GetBinContent(i_bin,j_bin);
        	Float_t kfactor = corr_weighted->GetBinContent(i_bin,j_bin);

            Float_t dx = sqrt(x);
            Float_t dn = sqrt(n);

     	    Float_t Error;
        	if(n==0)  Error=0;
        	if(n!=0)  Error=kfactor*sqrt(dx*dx/x/x+dn*dn/n/n);
        	corr_weighted->SetBinError(i_bin,j_bin,Error);
            //std::cout<<i_bin<<"  ";
            //std::cout<<j_bin<<"  ";
            //std::cout<<x<<"+-"<<dx<<"  ";
            //std::cout<<n<<"+-"<<dn<<"  ***  ";
            //std::cout<<Error<<"  ";
            //std::cout<<corr_weighted->GetBinContent(i_bin,j_bin)<<" +- "<<corr_weighted->GetBinError(i_bin,j_bin)<<std::endl;
	   }
   }
}

void BErrors(Float_t num, Float_t den)
{
float eff=num/den; 
float error=(1.0/den)*sqrt(num*(1-num/den));
//std::cout<<" Eff +/- Error  =  "<<100*eff<<" +/- "<<100*error<<" %";
std::cout<<" Eff +/- Error  =  "<<100*eff<<" +/- "<<100*error<<" %"<<std::endl;

}

void BErrorsSimple(Float_t num, Float_t den)
{
float eff=num/den; 
float error=(1.0/den)*sqrt(num*(1-num/den));
std::cout<<setprecision(2)<<100*eff<<" +- "<<100*error<<" %"<<std::endl;
}

double Efficiency(Double_t num, Double_t den)
{
double eff=num/den;
return eff;
}

double ErrorStatEfficiency(Double_t num, Double_t den)
{
double error=(1.0/den)*sqrt(num*(1-num/den));
return error;
}

bool is_in_phi_fiducial(float Phi)
{
  float PHI_CRACK_WIDTH=0.02;
  bool off_phi_crack=true;  
  float phimod=fmod(Phi+0.1,TMath::Pi()/16.);
  off_phi_crack=(phimod<0.1-PHI_CRACK_WIDTH) || (phimod>0.1+PHI_CRACK_WIDTH);
  return off_phi_crack;
}

double error_X1X2(double dX1, double dX2, double rho, double dFdX1, double dFdX2){
double error = -555.;
error=sqrt(dFdX1*dFdX1*dX1*dX1 + dFdX2*dFdX2*dX2*dX2 + 2*rho*dFdX1*dFdX2*dX1*dX2);
return error;
}

double error_Nxfrac(double N, double frac, double dfrac){
double error = -555.;
//assuming N Poisson distributed
error=N*frac*sqrt(1./N + dfrac*dfrac/frac/frac);
return error;
}

double error_AdivB(double A, double dA, double rho, double B, double dB){
double error = -555.;
//assuming A and B statistically independent
error=(A/B)*sqrt(dA*dA/A/A + dB*dB/B/B + 2*rho*dA*dB/A/B );
return error;
}

void ApplyScaleOffset(double E_true, double scale, double scale_error, double offset , double offset_error, double rho, double &E, double &E_error){
E=0.;
E_error = 0.;
E = E_true*scale + offset;
E_error  = scale_error*scale_error*E_true*E_true;
E_error += offset_error*offset_error;
E_error += 2*rho*scale_error*offset_error*E_true;
E_error = sqrt(E_error);
}

#endif
