////////////////////////////////////////////////////////////////////////////
/// code from em_util/EMClusterPosCorr
/// only changed the way to read input parameters from config.rc
/// instead of from rcp
///         J. Zhu   11/07/2007 
////////////////////////////////////////////////////////////////////////////

#include "wmass_util/EMClusterPosCorr.hpp"
#include <cmath>
#include <iostream>

// FIXME define TWOPI // use kinem utils perhaps?
using namespace std;

EMClusterPosCorr::EMClusterPosCorr(cafe::Config config)
{
  _Zlimit = config.get("Zlimit", 0.);
  _correctionVersion = config.get("correctionVersion", 2);
  
  _rShiftCor = config.get("rShiftCor", true);
  if( _rShiftCor ) {
    std::vector<float> rshift = config.getVFloat("rShift");
    std::vector<float> rshiftN = config.getVFloat("rShiftN");
    std::vector<float> rshiftS = config.getVFloat("rShiftS");
    if( rshift.size() != 4 || rshiftN.size() !=4 || rshiftS.size() !=4 ) {
      // throw exception
    }
    for( int i = 0; i <4 ; ++i) {
      _rShift[i] = rshift[i];
      _rShiftN[i] = rshiftN[i];
      _rShiftS[i] = rshiftS[i];
    }
    
    _zShiftCor = config.get("zShiftCor", true);
  }
    _phiShift = config.get("phiShift", 0.);

  //
  _zTwistCor = config.get("zTwistCor", false);
  if( _zTwistCor ) {
    _zTwistFactor = config.get("zTwistFactor", 0.);
    _zTwistOffset = config.get("zTwistOffset", 0.);
    _zTwistECFactorPos = config.get("zTwistECFactorPos", 0.);
    _zTwistECOffsetPos = config.get("zTwistECOffsetPos", 0.);
    _zTwistECFactorNeg = config.get("zTwistECFactorNeg", 0.);
    _zTwistECOffsetNeg = config.get("zTwistECOffsetNeg", 0.);
  }
  //
  _etaPhiModCor = config.get("etaPhiModCor", false);
  if( _etaPhiModCor ) {
    _ccEtaCor = config.get("ccEtaCor", 0.);
    std::vector<float> ccPhiCorAmp = config.getVFloat("ccPhiCorAmp");
    std::vector<float> ccPhiCorP1 = config.getVFloat("ccPhiCorP1");
    if( ccPhiCorAmp.size() != 4 || ccPhiCorP1.size() != 4 ) {
      // throw exception
    }
    for( int i = 0; i <4 ; ++i) {
      _ccPhiCorAmp[i] = ccPhiCorAmp[i];
      _ccPhiCorP1[i] = ccPhiCorP1[i];
    }
    _ecEtaCorPos = config.get("ecEtaCorPos", 0.);
    _ecEtaCorNeg = config.get("ecEtaCorNeg", 0.);
    _ecPhiCorFactor = config.get("ecPhiCorFactor", 0.);
    _ecPhiCorOffset = config.get("ecPhiCorOffset", 0.);
  }
  //
  _correctZ = config.get("correctZ", false);
  if( _correctZ ) {
    _zCentre = config.get("zCentre", 0.);
    std::vector<float> zCentreN = config.getVFloat("zCentreN");
    std::vector<float> zCentreS = config.getVFloat("zCentreS");
    if( zCentreN.size() != 4 || zCentreS.size() != 4) {
      // throw exception
    }
    for( int i =0; i< 4; ++i) {
      _zCentreN[i] = zCentreN[i];
      _zCentreS[i] = zCentreS[i];
    }
  }
  _correctXY = config.get("correctXY", false);
  if( _correctXY ) {
    _xCentre = config.get("xCentre", 0.);
    _yCentre = config.get("yCentre", 0.);
    _xCentreN = config.get("xCentreN", 0.);
    _xCentreS = config.get("xCentreS", 0.);
    _yCentreN = config.get("yCentreN", 0.);
    _yCentreS = config.get("yCentreS", 0.);
    _alphaCorr = config.get("alphaCorr", false);
    if( _alphaCorr ){
      _xCorAlpha = config.get("xCorAlpha", 0.);
      _yCorAlpha = config.get("yCorAlpha", 0.);
    }
  }
  //
  _correctEC_XYPhi = config.get("correctEC_XYPhi", false);
  if( _correctEC_XYPhi ) {
    _xFacN = config.get("xFacN", 0.);
    _xFacS = config.get("xFacS", 0.);
    _xOffN = config.get("xOffN", 0.);
    _xOffS = config.get("xOffS", 0.);
    _yFacN = config.get("yFacN", 0.);
    _yFacS = config.get("yFacS", 0.);
    _yOffN = config.get("yOffN", 0.);
    _yOffS = config.get("yOffS", 0.);
  }
  //
  _correctRZ = config.get("correctRZ", false);
  if ( _correctRZ ) {
    _rLimit = config.get("rLimit", 0.);
    std::vector<float> ecNeg = config.getVFloat("rCorrECInnerNeg");
    std::vector<float> ecPos = config.getVFloat("rCorrECInnerPos");
    std::vector<float> zCorrCC = config.getVFloat("zCorrCC");
    std::vector<float> ecNegO = config.getVFloat("rCorrECOuterNeg");
    std::vector<float> ecPosO = config.getVFloat("rCorrECOuterPos");
    if( ecNeg.size() != 4 ||
	ecPos.size() != 4 ||
	zCorrCC.size() != 5 ||
	ecNegO.size() !=2 ||
	ecPosO.size() != 2) {
      //throw exception
    }

    _rCorrECOuterNeg[0] = ecNegO[0];
    _rCorrECOuterNeg[1] = ecNegO[1];
    _rCorrECOuterPos[0] = ecPosO[0];
    _rCorrECOuterPos[1] = ecPosO[1];
    //
    for( int i = 0; i < 4; ++i) {
      _rCorrECInnerNeg[i] = ecNeg[i];
      _rCorrECInnerPos[i] = ecPos[i];
      _zCorrCC[i] = zCorrCC[i];
    }
    _zCorrCC[4] = zCorrCC[4];
    _zCorrZLim = config.get("zCorrZLim", 0.);
    _zCorrFactorPos = config.get("zCorrFactorPos", 0.);
    _zCorrOffsetPos = config.get("zCorrOffsetPos", 0.);
    _zCorrFactorNeg = config.get("zCorrFactorNeg", 0.);
    _zCorrOffsetNeg = config.get("zCorrOffsetNeg", 0.);
  }
  // old tilt and rotation correction
  if(  _correctionVersion == 1) {
    _correctTilt = config.get("correctTilt", false);
    if( _correctTilt ) {
      _ccCorFactor = config.get("ccCorFactor", 0.);
      _ccCorOffset = config.get("ccCorOffset", 0.);
      _ecPhiCor    = config.get("ecPhiCor", 0.);
    }
  } else {
    _correctTilt = false;
  }
  // done
};

  void EMClusterPosCorr::CorrectClusterPosition( double xcal, double ycal, double zcal,
			       double &xcor, double &ycor, double &zcor,
			       int floor) const 
{
  const double TWOPI = 2.*acos(-1);
  double phiclu = atan2(ycal, xcal); if( phiclu<0 ) phiclu += TWOPI;
  double rclu   = sqrt(xcal*xcal+ycal*ycal);
  // change r and slant cal                 unknown reason
  if( _rShiftCor )
  {

    if( zcal<-_Zlimit ) rclu += _rShiftN[floor-1];
    if( zcal> _Zlimit ) rclu += _rShiftS[floor-1];
    else            rclu += _rShift [floor-1];
    if( fabs(zcal)<_Zlimit ) zcal += 0.5*cos(phiclu+_zShiftCor);  // unknown reason
  }

  if( zcal > _Zlimit ) 
    {  
      phiclu += _phiShift;  if( phiclu<0 ) phiclu += TWOPI;
    }
  
  if( _zTwistCor )
  {    
    if( fabs(zcal)<_Zlimit ) zcal += _zTwistFactor*cos(phiclu+_zTwistOffset);  // unknown reason
    if( zcal <- _Zlimit ) rclu +=   _zTwistECFactorNeg*cos(phiclu+_zTwistECOffsetNeg);
    if( zcal >  _Zlimit ) rclu += _zTwistECFactorPos*cos(phiclu+_zTwistECOffsetPos);
  }
 
  double etaclu = -log(tan(TWOPI/8-0.5*atan(zcal/rclu)));
  // modulations in eta and phi
  int ietaclu = static_cast<int>(fabs(etaclu*10));
  double mod = fabs(etaclu) - (ietaclu+0.5)*0.1;
  double crack = 0.;
  if( fabs(zcal)<_Zlimit )// CC
    crack = phiclu - (int)(phiclu/TWOPI*32+0.5)*TWOPI/32;
  else// EC
    crack = phiclu - (int)(phiclu/TWOPI*64+0.5)*TWOPI/64;

  if( _etaPhiModCor )
  {
    if( fabs(zcal)<_Zlimit )// CC
    {
      // eta correction
      if( floor==3 )
      {
        double ecor = _ccEtaCor*sin(TWOPI/0.05*fabs(mod));
        if( mod*zcal>=0 ) etaclu -= + ecor;
        else              etaclu -= - ecor;
      }
      // phi correction
      double phicor = _ccPhiCorAmp[floor-1]*sin(64*fabs(crack)) + _ccPhiCorP1[floor-1];
      if( crack>0 ) phiclu += phicor;
      else          phiclu -= phicor;
      if( phiclu>TWOPI ) phiclu -= TWOPI;
      if( phiclu<0     ) phiclu += TWOPI;
    }
    else if( floor==3 )// EC only floor 3
      {
        double ecor1 = _ecEtaCorNeg*cos(TWOPI/0.05*mod);
        double ecor2 = _ecEtaCorPos*cos(TWOPI/0.05*mod);
	if( zcal<0 ) etaclu += ecor1;
	else         etaclu -= ecor2;

	double phicor  =0.;
	if( _correctionVersion == 1) {
	  phicor = _ecPhiCorFactor*crack*crack*crack*(1-128/TWOPI*fabs(crack));
	  phiclu -= phicor;
	} else {
	  phicor = _ecPhiCorFactor*sin(128*fabs(crack))+ _ecPhiCorOffset ;
	  if( crack>0 ) 
	    phiclu -= phicor;
	  else 
	    phiclu += phicor;	
	}
	
	//      phiclu -= phicor;
	if( phiclu>TWOPI ) phiclu -= TWOPI;
	if( phiclu<0     ) phiclu += TWOPI;
      }
  }

  // go to xyz
  double zclu = rclu*sinh(etaclu);
  double xclu = rclu*cos(phiclu);
  double yclu = rclu*sin(phiclu);
  //
  //    printf("Before xyz-corrections: %8.1f %8.1f %8.1f \n", xclu, yclu, zclu);
  //if( _debug) std::cout << "**** new EMClusterPosCor (a) : " << xclu << " " << yclu << " " << zclu << std::endl;
  if( _correctZ )// z shift
  {
    if( fabs(zcal)<_Zlimit ) zclu += _zCentre;           // CC
    else if( zclu<0 )         zclu += _zCentreN[floor-1]; // ECN
    else                      zclu += _zCentreS[floor-1]; // ECS
 }
  // EC x-y shift
  if( _correctXY )
  {
    if( fabs(zcal)<_Zlimit ) { xclu += _xCentre;  yclu += _yCentre; } // CC
    else if( zcal<0 )        { xclu += _xCentreN; yclu += _yCentreN; }// ECN
    else                     { xclu += _xCentreS; yclu += _yCentreS; }// ECS
    
	 // printf("After xyz-corrections: %8.1f %8.1f %8.1f \n", xclu, yclu, zclu);
    if( _alphaCorr ) {
      if( fabs(zcal)<_Zlimit )
	{
	  double alphax = atan(_xCorAlpha);
	  double alphay = atan(_yCorAlpha);
	  
	  xclu += alphax*zclu;
	  yclu += alphay*zclu;
	}
    }
  }

  if( _correctEC_XYPhi )
  {
      if( zcal< -_Zlimit ) { xclu += _xFacN*cos(phiclu+_xOffN); yclu += _yFacN*sin(phiclu+_yOffN); }// ECN
      if( zcal> _Zlimit )  { xclu += _xFacS*cos(phiclu+_xOffS); yclu += _yFacS*sin(phiclu+_yOffS); }// ECS
  }
 
  // go back to r, eta, phi
  rclu = sqrt(xclu*xclu + yclu*yclu);
  phiclu = atan2(yclu, xclu); if( phiclu<0 ) phiclu += TWOPI;

  //  if( _debug) std::cout << "**** new EMClusterPosCor (b)"  << rclu << " " << phiclu << std::endl;
  if( _correctRZ ) // CC, EN, ES z- and r- cluster position corrections
  {
    
      if( zcal< -_Zlimit && rclu <=_rLimit ) { 
	rclu += _rCorrECInnerNeg[0]*rclu*rclu*rclu 
	  + _rCorrECInnerNeg[1]*rclu*rclu 
	  + _rCorrECInnerNeg[2]*rclu 
	  + _rCorrECInnerNeg[3]; 
      }// ECN inner

      if( zcal< -_Zlimit && rclu >_rLimit ) { 
	rclu +=  _rCorrECOuterNeg[1]*rclu 
	  + _rCorrECOuterNeg[0]; 
      }// ECN outer
      
      if( zcal> _Zlimit && rclu <=_rLimit)  {  
	rclu += _rCorrECInnerPos[0]*rclu*rclu*rclu 
	  + _rCorrECInnerPos[1]*rclu*rclu 
	  + _rCorrECInnerPos[2]*rclu 
	  + _rCorrECInnerPos[3]; 
      }// ECS

      if( zcal> _Zlimit && rclu >_rLimit)  {  
	rclu +=  _rCorrECOuterPos[1]*rclu 
	  + _rCorrECOuterPos[0]; 
      }// ECS outer 

    if( fabs(zcal)<_Zlimit )
      {
	zclu += _zCorrCC[0]*zclu*zclu*zclu*zclu 
	  + _zCorrCC[1]*zclu*zclu*zclu 
	  + _zCorrCC[2]*zclu*zclu 
	  + _zCorrCC[3]*zclu 
	  + _zCorrCC[4];
	
	etaclu = -log(tan(TWOPI/8-0.5*atan(zclu/rclu)));
        double tanl = sinh(etaclu);
        if( tanl > _zCorrZLim )      { zclu += _zCorrFactorPos*(tanl - _zCorrZLim) + _zCorrOffsetPos; }
        if( tanl <- _zCorrZLim )     { zclu += _zCorrFactorNeg*(tanl + _zCorrZLim) + _zCorrOffsetNeg; }
	
      }
  }
  etaclu = -log(tan(TWOPI/8-0.5*atan(zclu/rclu)));
  //  if(_debug) std::cout << "**** new EMClusterPosCor (c)"  << rclu << " " << zclu << " " << etaclu  << std::endl;
  if( _correctTilt) {
    if( fabs(zcal) < _Zlimit) 
      phiclu += _ccCorFactor*cos(phiclu-_ccCorOffset) * zclu/rclu;
    else if( zcal > 150.) 
      phiclu += _ecPhiCor;
  }
  
 // go to xyz
  zclu = rclu*sinh(etaclu);
  xclu = rclu*cos(phiclu);
  yclu = rclu*sin(phiclu);

  xcor = xclu;
  ycor = yclu;
  zcor = zclu;

  //  if( _debug) std::cout << "**** new cluspos: " << xcor << " " << ycor << " " << zcor << std::endl;
}
  void EMClusterPosCorr::CorrectClusterPosition( const double *xyzlocal, double *xyzcorrected, int floor) const
{
  double xcor, ycor, zcor;
  CorrectClusterPosition( xyzlocal[0], xyzlocal[1], xyzlocal[2],
			  xcor, ycor, zcor, floor);
  xyzcorrected[0] = xcor;
  xyzcorrected[1] = ycor;
  xyzcorrected[2] = zcor;
}
