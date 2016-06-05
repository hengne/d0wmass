/********************************************************************************** 
 *
 *  Authors : Sabine Crepe-Renaudin (LPSC Grenoble)
 *            Jan Stark (LPSC Grenoble)
 *
 *  Please see header file for documentation.
 *
 **********************************************************************************/

#include "wmass_analysis/CorrEemcalo.hpp"

#include <math.h>
#include <iostream>

float EMCORR_EMIN=0.5;


CorrEemcalo::CorrEemcalo()
{

  // Initialise tables with coefficients
  //
  // p17 (Run IIa)
  //
  // EC
  _params_North[0]=6.51986;
  _params_North[1]=0.0416874;
  _params_North[2]=-86.1455;
  _params_North[3]=494.105;
  _params_North[4]=0.821285;
  _params_North[5]=0.00864744;
  _params_North[6]=-0.199969;
  _params_North[7]=-21.3416;
  _params_North[8]=0.97278;
  _params_North[9]=0.00873544;
  _params_North[10]=-10.6131;
  _params_North[11]=61.0158;
  _params_North[12]=0.369224;
  _params_North[13]=0.00462566;
  _params_North[14]=-1.97363;
  _params_North[15]=7.0345;
  _params_North[16]=0.324488;
  _params_North[17]=0.00385624;
  _params_North[18]=-3.04428;
  _params_North[19]=17.2013;
  _params_North[20]=0.188245;
  _params_North[21]=0.00270772;
  _params_North[22]=-1.49776;
  _params_North[23]=8.08409;
  _params_North[24]=0.14937;
  _params_North[25]=0.00220405;
  _params_North[26]=-1.48275;
  _params_North[27]=8.9988;
  //
  _params_South[0]=7.32878;
  _params_South[1]=0.0406626;
  _params_South[2]=-93.4016;
  _params_South[3]=479.742;
  _params_South[4]=1.18022;
  _params_South[5]=0.00840656;
  _params_South[6]=-7.10599;
  _params_South[7]=26.3245;
  _params_South[8]=1.14464;
  _params_South[9]=0.00863229;
  _params_South[10]=-11.359;
  _params_South[11]=52.2993;
  _params_South[12]=0.483752;
  _params_South[13]=0.00458107;
  _params_South[14]=-3.09036;
  _params_South[15]=10.921;
  _params_South[16]=0.388478;
  _params_South[17]=0.00385773;
  _params_South[18]=-2.79057;
  _params_South[19]=9.68541;
  _params_South[20]=0.229733;
  _params_South[21]=0.00272505;
  _params_South[22]=-1.12348;
  _params_South[23]=1.97446;
  _params_South[24]=0.172339;
  _params_South[25]=0.00223694;
  _params_South[26]=-0.719756;
  _params_South[27]=0.111394;

  // p20 data (Run IIb)
  //
  // CC
  _params_p20fulljan[0]=1.22787;
  _params_p20fulljan[1]=0.0446077;
  _params_p20fulljan[2]=0.608506;
  _params_p20fulljan[3]=-0.245865;
  _params_p20fulljan[4]=-0.719262;
  _params_p20fulljan[5]=0.308144;
  _params_p20fulljan[6]=1.1198;
  _params_p20fulljan[7]=-0.109522;
  _params_p20fulljan[8]=-0.466363;
  _params_p20fulljan[9]=-0.148952;
  _params_p20fulljan[10]=-0.0302059;
  _params_p20fulljan[11]=-0.433073;
  _params_p20fulljan[12]=0.191203;
  _params_p20fulljan[13]=0.672574;
  _params_p20fulljan[14]=-0.242232;
  _params_p20fulljan[15]=-0.899711;
  _params_p20fulljan[16]=0.0881496;
  _params_p20fulljan[17]=0.375751;
  _params_p20fulljan[18]=0.0275086;
  _params_p20fulljan[19]=0.00664165;
  _params_p20fulljan[20]=0.0968432;
  _params_p20fulljan[21]=-0.0476748;
  _params_p20fulljan[22]=-0.184827;
  _params_p20fulljan[23]=0.0614296;
  _params_p20fulljan[24]=0.232538;
  _params_p20fulljan[25]=-0.0233794;
  _params_p20fulljan[26]=-0.095643;
  _params_p20fulljan[27]=-0.00172035;
  _params_p20fulljan[28]=-0.000469182;
  _params_p20fulljan[29]=-0.00694727;
  _params_p20fulljan[30]=0.00380024;
  _params_p20fulljan[31]=0.0154037;
  _params_p20fulljan[32]=-0.00504777;
  _params_p20fulljan[33]=-0.0191057;
  _params_p20fulljan[34]=0.0020364;
  _params_p20fulljan[35]=0.00775076;
  // EC
  double lookup_p20ECNfulljan_init[80]={
    0.930831 , 0.145716 , -0.0465489 , 0.00393141 ,
    1.40397 , -0.242149 , 0.0456429 , -0.00288697 ,
    1.50817 , -0.269584 , 0.0452074 , -0.00254852 ,
    1.61636 , -0.312068 , 0.0504926 , -0.00275353 ,
    1.6823 , -0.360521 , 0.0620913 , -0.00366015 ,
    1.6929 , -0.341767 , 0.0542255 , -0.00290501 ,
    1.60782 , -0.262013 , 0.0344074 , -0.00140979 ,
    1.73864 , -0.344624 , 0.052675 , -0.00275087 ,
    1.74054 , -0.354703 , 0.0560135 , -0.00303816 ,
    1.70863 , -0.331793 , 0.0509117 , -0.00268884 ,
    1.76609 , -0.358778 , 0.0551353 , -0.00290635 ,
    1.48535 , -0.215189 , 0.0309259 , -0.00155468 ,
    1.15776 , -0.0472609 , 0.00202969 , 0.000117935 ,
    1.10747 , -0.0279649 , 0.00042023 , 8.88199e-05 ,
    1.12546 , -0.0294168 , -0.00109233 , 0.00031209 ,
    1.49049 , -0.219336 , 0.0321342 , -0.00166498 ,
    1.2315 , -0.0778402 , 0.00607466 , -4.52999e-05 ,
    1.12118 , -0.0322318 , 0.000612758 , 0.000108389 ,
    0.809288 , 0.165976 , -0.0408907 , 0.0029759 ,
    0.83534 , 0.129405 , -0.0301769 , 0.00208943
  };
  double lookup_p20ECSfulljan_init[80]={
    2.12048 , -0.60066 , 0.109203 , -0.00680625 ,
    1.37072 , -0.193972 , 0.0313574 , -0.0016729 ,
    1.72949 , -0.391151 , 0.0688633 , -0.0041326 ,
    1.81407 , -0.423994 , 0.0724516 , -0.00421172 ,
    1.76732 , -0.385098 , 0.0629359 , -0.00350345 ,
    1.65341 , -0.299956 , 0.0446286 , -0.00226556 ,
    1.80601 , -0.38783 , 0.0615168 , -0.00334998 ,
    1.94106 , -0.454996 , 0.0736436 , -0.00412515 ,
    1.89499 , -0.43328 , 0.0705302 , -0.00399266 ,
    1.7352 , -0.34004 , 0.0517268 , -0.00271071 ,
    1.71999 , -0.316433 , 0.0452566 , -0.00221851 ,
    1.52792 , -0.241167 , 0.0361886 , -0.00188688 ,
    1.3114 , -0.147345 , 0.0234061 , -0.00137487 ,
    1.19531 , -0.080969 , 0.0110377 , -0.000617912 ,
    1.0727 , 0.0135372 , -0.0114045 , 0.0010729 ,
    1.33695 , -0.12529 , 0.013701 , -0.00048069 ,
    1.38874 , -0.190236 , 0.0321889 , -0.0019968 ,
    1.49591 , -0.26615 , 0.0492372 , -0.00321921 ,
    1.07194 , 0.0109451 , -0.0103472 , 0.000980239 ,
    1.37181 , -0.195043 , 0.0353584 , -0.00231643
  };
  //
  for (int i=0; i<80; i++) {
    _lookup_p20ECNfulljan[i]=lookup_p20ECNfulljan_init[i];
    _lookup_p20ECSfulljan[i]=lookup_p20ECSfulljan_init[i];
  }

  // p20 plain d0g Monte Carlo (Run IIb)
  //
  // CC
  _params_p20plaind0g[0]=1.3266;
  _params_p20plaind0g[1]=-0.00245635;
  _params_p20plaind0g[2]=0.484058;
  _params_p20plaind0g[3]=0.0258695;
  _params_p20plaind0g[4]=-0.0312033;
  _params_p20plaind0g[5]=-0.0464689;
  _params_p20plaind0g[6]=0.0682192;
  _params_p20plaind0g[7]=0.00925722;
  _params_p20plaind0g[8]=-0.0188482;
  _params_p20plaind0g[9]=-1.78098;
  _params_p20plaind0g[10]=0.0132309;
  _params_p20plaind0g[11]=-3.03478;
  _params_p20plaind0g[12]=-0.173948;
  _params_p20plaind0g[13]=1.40064;
  _params_p20plaind0g[14]=0.289077;
  _params_p20plaind0g[15]=-0.621079;
  _params_p20plaind0g[16]=-0.0236645;
  _params_p20plaind0g[17]=0.135154;
  _params_p20plaind0g[18]=3.58231;
  _params_p20plaind0g[19]=-0.0263658;
  _params_p20plaind0g[20]=6.6348;
  _params_p20plaind0g[21]=0.403703;
  _params_p20plaind0g[22]=-6.03568;
  _params_p20plaind0g[23]=-0.64682;
  _params_p20plaind0g[24]=2.77703;
  _params_p20plaind0g[25]=-0.0202942;
  _params_p20plaind0g[26]=-0.532984;
  _params_p20plaind0g[27]=-0.251089;
  _params_p20plaind0g[28]=0.00135192;
  _params_p20plaind0g[29]=-0.475956;
  _params_p20plaind0g[30]=-0.0301068;
  _params_p20plaind0g[31]=0.647318;
  _params_p20plaind0g[32]=0.0483108;
  _params_p20plaind0g[33]=-0.358608;
  _params_p20plaind0g[34]=0.00765452;
  _params_p20plaind0g[35]=0.0753395;
  // EC
  double lookup_p20ECNplaind0g_init[80]={
    1.64888 , -0.261043 , 0.0394013 , -0.00207407 , 
    1.34794 , -0.154607 , 0.0261644 , -0.00147183 , 
    1.59207 , -0.271886 , 0.044978 , -0.00251185 , 
    1.65971 , -0.292047 , 0.0462941 , -0.00249437 , 
    1.67845 , -0.29865 , 0.0467714 , -0.00248524 , 
    1.77707 , -0.349418 , 0.0562114 , -0.00310066 , 
    1.83761 , -0.371488 , 0.0589634 , -0.00321864 , 
    1.79503 , -0.320276 , 0.0451393 , -0.00212332 , 
    1.90127 , -0.401395 , 0.0642756 , -0.00355998 , 
    1.84629 , -0.358813 , 0.0539828 , -0.00277893 , 
    1.80883 , -0.337736 , 0.0504195 , -0.00260238 , 
    1.52112 , -0.198875 , 0.0279949 , -0.00138626 , 
    1.35271 , -0.122775 , 0.01661 , -0.000811033 , 
    1.24103 , -0.0631532 , 0.00656841 , -0.000270586 , 
    1.30975 , -0.097422 , 0.0123678 , -0.000603801 , 
    1.56166 , -0.208259 , 0.0278277 , -0.00127595 , 
    1.44277 , -0.160654 , 0.0220055 , -0.00107597 , 
    1.27771 , -0.0724412 , 0.00643134 , -0.000167102 , 
    0.594974 , 0.342965 , -0.0771038 , 0.00538301 , 
    1.11009 , 0.0184826 , -0.0101982 , 0.000863598
  };
  double lookup_p20ECSplaind0g_init[80]={
    1.91434 , -0.418178 , 0.0730656 , -0.00451541 , 
    1.44464 , -0.192325 , 0.0310324 , -0.00167771 , 
    1.73362 , -0.340738 , 0.0573849 , -0.00330739 , 
    1.75987 , -0.337679 , 0.0538037 , -0.00292943 , 
    1.77152 , -0.348313 , 0.0566505 , -0.0031765 , 
    1.89598 , -0.412868 , 0.069379 , -0.00406393 , 
    1.90146 , -0.397273 , 0.06278 , -0.00342287 , 
    2.04306 , -0.47105 , 0.0764098 , -0.00429046 , 
    1.98491 , -0.431042 , 0.0676688 , -0.00367726 , 
    1.82813 , -0.34502 , 0.0516049 , -0.00267523 , 
    1.72625 , -0.271065 , 0.0350344 , -0.00148087 , 
    1.59874 , -0.25316 , 0.040717 , -0.00234667 , 
    1.35472 , -0.121426 , 0.0161972 , -0.000791159 , 
    1.26825 , -0.0789732 , 0.00958651 , -0.000465641 , 
    1.2824 , -0.0780465 , 0.0081768 , -0.000316887 , 
    1.43942 , -0.123695 , 0.00967017 , -2.42539e-05 , 
    1.52386 , -0.210134 , 0.0320713 , -0.00174141 , 
    1.25259 , -0.0526832 , 0.00230613 , 0.000102189 , 
    1.20012 , -0.0298174 , -0.00104077 , 0.000263715 , 
    1.26998 , -0.0830711 , 0.0113629 , -0.000647486
  };
  //
  for (int i=0; i<80; i++) {
    _lookup_p20ECNplaind0g[i]=lookup_p20ECNplaind0g_init[i];
    _lookup_p20ECSplaind0g[i]=lookup_p20ECSplaind0g_init[i];
  }

}


// ======> Scone Phi corrections
double CorrEemcalo::correvsphi_S(float E0, const float phid, const float etad, bool is_data)
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

// ======> CellNN Phi corrections
double CorrEemcalo::correvsphi_Z(float E0, const float phid, const float etad, bool is_data)
{
  // for now just take the SCone corrections

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
double CorrEemcalo::correvseta_S(float E0, const float etap, const float etad, bool isRunIIb, bool isMC)
{

  float E=E0;

  // Energy corrections have been studied above 2 GeV
  if (E0<EMCORR_EMIN) E=EMCORR_EMIN;

  double coreta;
  double Ecor;

  // Global correction

  if ((etad >= 0) &&  (etad <= 1.3)) //CC
    {
      if (!isRunIIb) {
	coreta=corretaa_CC_S(E)+corretab_CC_S(E)*etap*etap+corretac_CC_S(E)*etap*etap*etap*etap;
	E+=coreta;
	//if (etad >= 1.) Ecor=E+diffic(E);
      } else {
	if (!isMC) {
	  E*=Eloss_Jan_CC(E,etap,_params_p20fulljan);
	} else {
	  E*=Eloss_Jan_CC_regularised(E,etap,_params_p20plaind0g);
	}
      }
      if (!isMC) {
	Ecor=E;
	coreta=exp(12*etad+corretaga_IC_S(Ecor)); 
	E+=coreta;
      }
    }
  else if ((etad >= -1.3) &&  (etad <= 0)) //CC
    {
      if (!isRunIIb) {
	coreta=corretaa_CC_S(E)+corretab_CC_S(E)*etap*etap+corretac_CC_S(E)*etap*etap*etap*etap;
	E+=coreta;
	//if (etad <= -1.) Ecor=E+diffic(E);
      } else {
	if (!isMC) {
	  E*=Eloss_Jan_CC(E,etap,_params_p20fulljan);
	} else {
	  E*=Eloss_Jan_CC_regularised(E,etap,_params_p20plaind0g);
	}
      }
      if (!isMC) {
	Ecor=E;
	coreta=exp(-12*etad+corretaga_IC_S(Ecor)); 
	E+=coreta;
      }
    }	
	else if (etad >= 1.3) //EC
	  {
	    if (!isRunIIb) {
	      coreta=Tim_Eloss(E, -etap, _params_South);
	      E+=coreta;
	      if (etad <= 1.5) Ecor=E+diffic(E);
	      else Ecor=E;
	      coreta=exp(-21*etad+corretada_IC_S(Ecor))-0.005*etad; 
	      E+=coreta;
	    } else {
	      if (!isMC) {
		E*=Eloss_Jan_EC(E,etad,_lookup_p20ECSfulljan);
	      } else {
		E*=Eloss_Jan_EC(E,etad,_lookup_p20ECSplaind0g);
	      }
	    }
	  }
	else if (etad <= -1.3) //EC
	  {
	    if (!isRunIIb) {
	      coreta=Tim_Eloss(E, etap, _params_North);
	      E+=coreta;
	      if (etad >= -1.5) Ecor=E+diffic(E);
	      else Ecor=E;
	      coreta=exp(21*etad+corretada_IC_S(Ecor))+0.005*etad; 
	      E+=coreta;
	    } else {
	      if (!isMC) {
		E*=Eloss_Jan_EC(E,etad,_lookup_p20ECNfulljan);
	      } else {
		E*=Eloss_Jan_EC(E,etad,_lookup_p20ECNplaind0g);
	      }
	    }
	  }

  if (E0<EMCORR_EMIN) E=E/EMCORR_EMIN*E0;

  return E;
}
    
// Correction parameters CC
double CorrEemcalo::corretaa_CC_S(const float e)
{
  if(e >= 2.6368 && e <= 800) //increased range (should probably also be only for above 5GeV too)
    {
      double p0 = 0.3354;
      double p1 = 0.006269;
      double p2 = 2.075e-06;
      
      return  2*p0+2*p1*e+p2*e*e;
    }

  else if (e >= 1.125 && e < 2.6368) return -0.36+0.32*e;
  else return 0;  
}
    
double CorrEemcalo::corretab_CC_S(const float e)
{
  if (e >= 2.0 && e <= 800)  // need to review the lower part (below 10)
    {
      double p0 = 0.7656;
      double p1 = -0.006525;
      double p2 = 0.0002219;
      double p3 = -3.644e-07;
      double p4 = 1.533e-10;
      
      return  1/e + p0 + p1*e + p2*e*e + p3*e*e*e + p4*e*e*e*e;
    }
  else return 0;  
}
    
double CorrEemcalo::corretac_CC_S(const float e)
{
  if (e >= 0 && e <= 800)
    {
      double p0 = 0.377;
      double p1 = 0.02637;
      double p2 = -0.0003499;
      double p3 = 6.584e-07;
      double p4 = -3.514e-10;
      
      
      return  p0 + p1*e + p2*e*e + p3*e*e*e + p4*e*e*e*e;
    }
  
  else return 0;
}


// Jan's central 2D function - version December 2006
double CorrEemcalo::Eloss_Jan_CC(float e, float etap, const double params[36]) {

  // four parameters in the fit at given eta,
  // nine parameters in the fit as function of eta

  double etapX = (double)etap;
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

// Jan's central 2D function - version December 2006 - regularised for more stable fitting
double CorrEemcalo::Eloss_Jan_CC_regularised(float e, float etap, const double params[36]) {

  // four parameters in the fit at given eta,
  // nine parameters in the fit as function of eta

  double etapX = (double)etap;
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
    corrA+corrB*arg/10+corrC*arg*arg/100+corrD*arg*arg*arg/100;

  return corr;

}


// Correction parameters EC
// Tim's 2D function
double CorrEemcalo::Tim_Eloss(const float e, const float etap, const double params[28]) {

  float physicseta=etap;
  float energy=e;
  if (physicseta<-3) physicseta=-3;
  if (physicseta>-1.5) physicseta=-1.5;
  if (energy<8) energy=8;

  double p0 = params[0];
  double p1 = params[1];
  double p2 = params[2];
  double p3 = params[3];
  double corretaa_EC_S = p0 + p1*energy + p2/energy + p3/(energy*energy);

  p0 = params[4];
  p1 = params[5];
  p2 = params[6];
  p3 = params[7];
  double corretab_EC_S = p0 + p1*energy + p2/energy + p3/(energy*energy);

  p0 = params[8];
  p1 = params[9];
  p2 = params[10];
  p3 = params[11];
  double corretac_EC_S = p0 + p1*energy + p2/energy + p3/(energy*energy);

  p0 = params[12];
  p1 = params[13];
  p2 = params[14];
  p3 = params[15];
  double corretad_EC_S = p0 + p1*energy + p2/energy + p3/(energy*energy);

  p0 = params[16];
  p1 = params[17];
  p2 = params[18];
  p3 = params[19];
  double corretae_EC_S = p0 + p1*energy + p2/energy + p3/(energy*energy);

  p0 = params[20];
  p1 = params[21];
  p2 = params[22];
  p3 = params[23];
  double corretaf_EC_S = p0 + p1*energy + p2/energy + p3/(energy*energy);

  p0 = params[24];
  p1 = params[25];
  p2 = params[26];
  p3 = params[27];
  double corretag_EC_S = p0 + p1*energy + p2/energy + p3/(energy*energy);

  float coretap = 
    2.283*corretaa_EC_S + -0.2672*corretab_EC_S + -28.96*corretac_EC_S 
    + 19.99*corretad_EC_S + 76.28*corretae_EC_S + -96.44*corretaf_EC_S  + 26.24*corretag_EC_S 
    + (-0.2672*corretaa_EC_S + 60.74*corretab_EC_S + -27.95*corretac_EC_S + -436.6*corretad_EC_S
       + 334.8*corretae_EC_S + 623.3*corretaf_EC_S + -562.6*corretag_EC_S)*(physicseta+2.5) 
    + (-28.96*corretaa_EC_S + -27.95*corretab_EC_S +  750* corretac_EC_S
       + -456.5*corretad_EC_S + -2612*corretae_EC_S + 3573*corretaf_EC_S 
       + -1171*corretag_EC_S)*(physicseta+2.5)*(physicseta+2.5) 
    + ( 19.99*corretaa_EC_S + -436.6*corretab_EC_S + -456.5*corretac_EC_S + 4801*corretad_EC_S
	+ -501 *corretae_EC_S + -1.198e+04*corretaf_EC_S 
	+ 8682*corretag_EC_S)*(physicseta+2.5)*(physicseta+2.5)*(physicseta+2.5) 
    + ( 76.28*corretaa_EC_S + 334.8*corretab_EC_S + -2612*corretac_EC_S + -501*corretad_EC_S 
	+ 1.137e+04*corretae_EC_S + -1.062e+04*corretaf_EC_S 
	+ 1782*corretag_EC_S)* (physicseta+2.5)*(physicseta+2.5)*(physicseta+2.5)*(physicseta+2.5) 
    + ( -96.44*corretaa_EC_S + 623.3*corretab_EC_S + 3573*corretac_EC_S 
	+ -1.198e+04*corretad_EC_S +  -1.062e+04*corretae_EC_S + 4.723e+04*corretaf_EC_S
	+ -2.908e+04*corretag_EC_S)* (physicseta+2.5)*(physicseta+2.5)*(physicseta+2.5)*(physicseta+2.5)*(physicseta+2.5) 
    + ( 26.24*corretaa_EC_S  + -562.6*corretab_EC_S + -1171*corretac_EC_S 
	+ 8682*corretad_EC_S + 1782*corretae_EC_S + -2.908e+04*corretaf_EC_S 
	+ 2.074e+04*corretag_EC_S)*(physicseta+2.5)*(physicseta+2.5)*(physicseta+2.5)*(physicseta+2.5)*(physicseta+2.5)*(physicseta+2.5);

  return coretap;

}


// Correction parameters EC
// Jan's binned 2D function
double CorrEemcalo::Eloss_Jan_EC(float e, float etad, const double lookup[80]) {

  // Figure out bin
  float theetad=fabs(etad);
  int theBin=(int)(10*(theetad-1.40));
  if (theBin>19) theBin=19;
  if (theBin<0) theBin=0;

  // calculate E-loss factor
  float arg=log(e);
  float eloss=
    lookup[theBin*4]+
    lookup[theBin*4+1]*arg+
    lookup[theBin*4+2]*arg*arg+
    lookup[theBin*4+3]*arg*arg*arg;
  return eloss;

}

    
    // Correction parameters IC

    double CorrEemcalo::diffic(const float e)
      {
	//double p0 =-0.461801;
	//double p1 =0.116937;
	if (e <= 200)
	  {
	    double p0 = 0.435691;
	    double p1 = 0.176865;

	    return  p0+p1*e;
	  }

	else return 35.8;

      }

double CorrEemcalo::corretaga_IC_S(const float e) //stable
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

    double CorrEemcalo::corretada_IC_S(const float e)
      {
	//double p0 =20.966; 
	//double p1 =0.721714;
	//double p2 =-1.36376;
	if (e <= 200) 
	  {
	    if (e >= 10)
	      {
		double p0 = 28.97;
		double p1 = 0.8351;
		double p2 = -1.668;

		return  p0+p1*log(e+p2);
	      }
	    else return 30.74;
	  }

	else return 33.39;

      }



// ======> CellNN Eta correction

// Correction function
double CorrEemcalo::correvseta_Z(float E0, const float etap)
{

  float E=E0;
  if (E0<EMCORR_EMIN) E=EMCORR_EMIN;

  double coreta;

  if ((etap >= -1.) &&  (etap <= 1.))
    {
      coreta=corretaa_CC_Z(E)+corretab_CC_Z(E)*etap+corretac_CC_Z(E)*etap*etap;
      E+=coreta;
    }
  
  if (E0<EMCORR_EMIN) E=E/EMCORR_EMIN*E0;

  return E;
}
    
// Correction parameters 
double CorrEemcalo::corretaa_CC_Z(const float e)
{
  double p0 = 0.392223; 
  double p1 = 0.00422481;
  double p2 = 5.90179e-05;
  double p3 =-1.4268e-07;
	
  return  p0+p1*e+p2*e*e+p3*e*e*e;
}
    
double CorrEemcalo::corretab_CC_Z(const float e)
{
  double p0 = 0.00766449;
  double p1 = 0.000547225;
  double p2 = 4.14497e-06;
	
  return  p0+p1*e+p2*e*e;
}
    
double CorrEemcalo::corretac_CC_Z(const float e)
{
  double p0 = 0.868658;
  double p1 = -0.00127147;
  double p2 = 2.01766e-05;

  return  p0+p1*e+p2*e*e;
}
