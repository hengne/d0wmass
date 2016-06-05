#include "wmass_analysis/CorrEemcaloJan.hpp"

#include <math.h>
#include <iostream>

using namespace std;

float EMCORR_EMIN_Jan=0.5;


CorrEemcaloJan::CorrEemcaloJan()
{

  _params000[0]=1.2254;
  _params000[1]=0.046038;
  _params000[2]=0.605529;
  _params000[3]=-0.253255;
  _params000[4]=-0.721217;
  _params000[5]=0.303569;
  _params000[6]=1.11732;
  _params000[7]=-0.103816;
  _params000[8]=-0.466605;
  _params000[9]=-0.14828;
  _params000[10]=-0.0301565;
  _params000[11]=-0.433023;
  _params000[12]=0.191805;
  _params000[13]=0.672689;
  _params000[14]=-0.241273;
  _params000[15]=-0.899203;
  _params000[16]=0.0879364;
  _params000[17]=0.376112;
  _params000[18]=0.0275024;
  _params000[19]=0.00665187;
  _params000[20]=0.0972294;
  _params000[21]=-0.0476215;
  _params000[22]=-0.184578;
  _params000[23]=0.0614075;
  _params000[24]=0.232488;
  _params000[25]=-0.0234103;
  _params000[26]=-0.0954414;
  _params000[27]=-0.00172186;
  _params000[28]=-0.000489994;
  _params000[29]=-0.00698569;
  _params000[30]=0.00383117;
  _params000[31]=0.0153447;
  _params000[32]=-0.00497098;
  _params000[33]=-0.0191635;
  _params000[34]=0.00195666;
  _params000[35]=0.00773338;
  //
  _params017[0]=1.23455;
  _params017[1]=0.0436528;
  _params017[2]=0.621673;
  _params017[3]=-0.252117;
  _params017[4]=-0.69045;
  _params017[5]=0.301016;
  _params017[6]=1.12795;
  _params017[7]=-0.106073;
  _params017[8]=-0.45841;
  _params017[9]=-0.148777;
  _params017[10]=-0.030839;
  _params017[11]=-0.435282;
  _params017[12]=0.194242;
  _params017[13]=0.670554;
  _params017[14]=-0.242104;
  _params017[15]=-0.902676;
  _params017[16]=0.088912;
  _params017[17]=0.372641;
  _params017[18]=0.0273834;
  _params017[19]=0.00679581;
  _params017[20]=0.0966328;
  _params017[21]=-0.0475503;
  _params017[22]=-0.185108;
  _params017[23]=0.0611355;
  _params017[24]=0.231916;
  _params017[25]=-0.0233203;
  _params017[26]=-0.0957594;
  _params017[27]=-0.00175139;
  _params017[28]=-0.00048167;
  _params017[29]=-0.00694755;
  _params017[30]=0.00379761;
  _params017[31]=0.0154494;
  _params017[32]=-0.00499375;
  _params017[33]=-0.0190622;
  _params017[34]=0.00198094;
  _params017[35]=0.00789251;
  //
  _params036[0]=1.25788;
  _params036[1]=0.0426646;
  _params036[2]=0.657184;
  _params036[3]=-0.260222;
  _params036[4]=-0.647311;
  _params036[5]=0.300456;
  _params036[6]=1.14116;
  _params036[7]=-0.0964851;
  _params036[8]=-0.458891;
  _params036[9]=-0.152559;
  _params036[10]=-0.027534;
  _params036[11]=-0.441589;
  _params036[12]=0.189914;
  _params036[13]=0.66469;
  _params036[14]=-0.240577;
  _params036[15]=-0.905992;
  _params036[16]=0.0866072;
  _params036[17]=0.371596;
  _params036[18]=0.0269319;
  _params036[19]=0.00614965;
  _params036[20]=0.0957782;
  _params036[21]=-0.0466819;
  _params036[22]=-0.18631;
  _params036[23]=0.0620109;
  _params036[24]=0.231101;
  _params036[25]=-0.023623;
  _params036[26]=-0.0958679;
  _params036[27]=-0.00169246;
  _params036[28]=-0.000479158;
  _params036[29]=-0.00675508;
  _params036[30]=0.00380534;
  _params036[31]=0.0156338;
  _params036[32]=-0.00509213;
  _params036[33]=-0.0189626;
  _params036[34]=0.00197209;
  _params036[35]=0.00804932;
  //
  _nX0=0.1633;

}


// ======> Scone Phi corrections
double CorrEemcaloJan::correvsphi_S(float E0, const float phid, const float etad, bool is_data)
{
  // As measured by Oleg K. Mar 7, 2003

  float E=E0;

  if (fabs(etad)<1.3) {
    float phim=fmod(phid+0.1,acos(-1.0)/16.);
    float eloss;
    float crack_size;
    if (is_data) {
      eloss=0.20;
      crack_size=0.013;
    } else {
      eloss=0.17;
      crack_size=0.010;
    }
    E=E0*(1.0+eloss*exp(-0.5*pow(((phim-0.1)/crack_size),2)));
  }

  return E;

}


// ======> Scone Eta corrections
// Correction function
double CorrEemcaloJan::correvseta_S(float E0, const float etap, const float etad)
{

  float E=E0;

  // Energy corrections have been studied above 2 GeV
  if (E0<EMCORR_EMIN_Jan) E=EMCORR_EMIN_Jan;

  double coreta;
  double Ecor;

  // Where are we ?

  double Jan_calc=0;
  if (_nX0<0) {
    Jan_calc=Jan_Eloss(E,etap,_params000);
  } else if (_nX0<0.17) {
    double J1=Jan_Eloss(E,etap,_params000);
    double J2=Jan_Eloss(E,etap,_params017);
    Jan_calc=J1+((_nX0-0)/0.17)*(J2-J1);
  } else if (_nX0<0.36) {
    double J1=Jan_Eloss(E,etap,_params017);
    double J2=Jan_Eloss(E,etap,_params036);
    Jan_calc=J1+((_nX0-0.17)/(0.36-0.17))*(J2-J1);
  } else {
    Jan_calc=Jan_Eloss(E,etap,_params036);
  }

  // Global correction

  if (fabs(etad) <= 1.3) //CC
    {
      coreta=Jan_calc;
      E*=coreta;
      Ecor=E;
      //coreta=exp(12*etad+corretaga_IC_S(Ecor)); 
      //E+=coreta;
    }
  else
    {
      cout<<endl<<endl
	  <<"CorrEemcaloJan: I don't know anything anout the ECs."<<endl
	  <<"                Will bail."<<endl<<endl;
      assert(0);
    }	

  if (E0<EMCORR_EMIN_Jan) E=E/EMCORR_EMIN_Jan*E0;

  return E;
}
    

double CorrEemcaloJan::corretaga_IC_S(const float e) //stable
{
  //double p0 =0.00289265; 
  //double p1 =-11.9711;
  //double p2 =0.0873971;
  //double p3 =-0.514562;
  if (e <= 200)
    {
      double p0 = -13.94;
      double p1 = 0.02961;
      double p2 = -9.546e-05;
      
      return  p0+p1*e+p2*e*e;
    }
  
  else return -11.84;
  
}

// Jan's central 2D function - version December 2006
double CorrEemcaloJan::Jan_Eloss(double e, double etap, const double params[36]) {

  // four parameters in the fit at given eta,
  // nine parameters in the fit as function of eta

  double etapX = etap;
  double etapX2 = etap*etap;
  double etapX3 = etapX2*etapX;
  double etapX4 = etapX3*etapX;
  double etapX5 = etapX4*etapX;
  double etapX6 = etapX5*etapX;
  double etapX7 = etapX6*etapX;
  double etapX8 = etapX7*etapX;

  double p0 = params[0];
  double p1 = params[1];
  double p2 = params[2];
  double p3 = params[3];
  double p4 = params[4];
  double p5 = params[5];
  double p6 = params[6];
  double p7 = params[7];
  double p8 = params[8];
  double corrA =
    p0
    + p1*etapX
    + p2*etapX2
    + p3*etapX3
    + p4*etapX4
    + p5*etapX5
    + p6*etapX6
    + p7*etapX7
    + p8*etapX8;

  p0 = params[9];
  p1 = params[10];
  p2 = params[11];
  p3 = params[12];
  p4 = params[13];
  p5 = params[14];
  p6 = params[15];
  p7 = params[16];
  p8 = params[17];
  double corrB =
    p0
    + p1*etapX
    + p2*etapX2
    + p3*etapX3
    + p4*etapX4
    + p5*etapX5
    + p6*etapX6
    + p7*etapX7
    + p8*etapX8;
  p0 = params[18];
  p1 = params[19];
  p2 = params[20];
  p3 = params[21];
  p4 = params[22];
  p5 = params[23];
  p6 = params[24];
  p7 = params[25];
  p8 = params[26];
  double corrC =
    p0
    + p1*etapX
    + p2*etapX2
    + p3*etapX3
    + p4*etapX4
    + p5*etapX5
    + p6*etapX6
    + p7*etapX7
    + p8*etapX8;

  p0 = params[27];
  p1 = params[28];
  p2 = params[29];
  p3 = params[30];
  p4 = params[31];
  p5 = params[32];
  p6 = params[33];
  p7 = params[34];
  p8 = params[35];
  double corrD =
    p0
    + p1*etapX
    + p2*etapX2
    + p3*etapX3
    + p4*etapX4
    + p5*etapX5
    + p6*etapX6
    + p7*etapX7
    + p8*etapX8;

  double arg=log(e);
  double corr=
    corrA+corrB*arg+corrC*arg*arg+corrD*arg*arg*arg;

  return corr;

}

