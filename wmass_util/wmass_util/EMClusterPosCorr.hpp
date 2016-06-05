#ifndef _EMCLUSTERPOSCOR_HPP
#define _EMCLUSTERPOSCOR_HPP

// TODO: implement constructors
// TODO: check differences between old, new data and new MC
// TODO: implement different RCPs
#include "cafe/Config.hpp"

class EMClusterPosCorr {
public:
  EMClusterPosCorr(bool debug=false) : _debug(debug){
    _correctionVersion = 2;
    _Zlimit = 150.;

    _rShiftCor = true;
    _rShift[0] = -0.2;
    _rShift[1] = +0.2;
    _rShift[2] = +0.0;
    _rShift[3] = +0.0;

    _rShiftN[0] = +0.5;
    _rShiftN[1] = +0.0;
    _rShiftN[2] = +0.06;
    _rShiftN[3] = +0.2;

    _rShiftS[0] = +0.4;
    _rShiftS[1] = +0.4;
    _rShiftS[2] = +0.05;
    _rShiftS[3] = +0.3;
    _zShiftCor = 0.25;
    _phiShift = -0.0025;

    _zTwistCor = true;
    _zTwistFactor = 0.38;
    _zTwistOffset = 0.2;
    _zTwistECFactorPos = 0.25;
    _zTwistECOffsetPos = 0.;
    _zTwistECFactorNeg = -0.25;
    _zTwistECOffsetNeg = 0.;

    _etaPhiModCor = true;
    _ccEtaCor = -1.0E-3;
    _ccPhiCorAmp[0] = -14.E-3;
    _ccPhiCorAmp[1] = -12.E-3;
    _ccPhiCorAmp[2] = -3.2E-3;
    _ccPhiCorAmp[3] = 7.E-3;
    _ccPhiCorP1[0] = -1.8E-3;
    _ccPhiCorP1[1] = -1.6E-3;
    _ccPhiCorP1[2] = -1.1E-3;
    _ccPhiCorP1[3] = 1.8E-3;
    _ecEtaCorPos = 1.4E-3;
    _ecEtaCorNeg = 1.2E-3;
    _ecPhiCorFactor = -1.E-3;
    _ecPhiCorOffset = 1.E-3;

    _correctZ = true;
    _zCentre = -2.9;
    _zCentreN[0] = 5.1;
    _zCentreN[1] = 5.2;
    _zCentreN[2] = 4.2;
    _zCentreN[3] = 5.3;
    _zCentreS[0] = 1.4;
    _zCentreS[1] = 1.3;
    _zCentreS[2] = 0.6;
    _zCentreS[3] = 1.7;
    _xCentre = -0.35;
    _yCentre = -0.5;
    _xCentreN = 0.38;
    _xCentreS = 0.0;
    _yCentreN = 0.0;
    _yCentreS = 0.07;
    _alphaCorr = true;
    _xCorAlpha = -0.003;
    _yCorAlpha = 0.0015;

    _correctEC_XYPhi = true;
    _xFacN = 0.148;
    _xFacS = 0.233;
    _xOffN = -0.05;
    _xOffS = -0.02;
    _yFacN = 0.214;
    _yFacS = 0.265;
    _yOffN = 0.34;
    _yOffS = 0.01;
    //
    _correctRZ = true;
    _rLimit = 90.;
    _rCorrECInnerNeg[0] = 3.98945E-6;
    _rCorrECInnerNeg[1] = -8.54101E-4;
    _rCorrECInnerNeg[2] = 5.79129E-2;
    _rCorrECInnerNeg[3] = -1.30649;

    _rCorrECInnerPos[0] = 2.3671E-6;
    _rCorrECInnerPos[1] = -5.77257E-4;
    _rCorrECInnerPos[2] = 4.29052E-2;
    _rCorrECInnerPos[3] = -1.0855;

    _rCorrECOuterNeg[0] = 0.;
    _rCorrECOuterNeg[1] = 0.;
    _rCorrECOuterPos[0] = 0.;
    _rCorrECOuterPos[1] = 0.;
    _zCorrCC[0] = -5.91207E-10;
    _zCorrCC[1] = -3.65135E-7;
    _zCorrCC[2] = 7.06602E-7;
    _zCorrCC[3] = 3.03332E-4;
    _zCorrCC[4] = 2.44001E-3;
    _zCorrZLim = 1.1;
    _zCorrFactorPos = 1.54;
    _zCorrOffsetPos = -0.217;
    _zCorrFactorNeg = 2.13;
    _zCorrOffsetNeg = 0.262;

    _correctTilt = false;
    _ccCorFactor = 0.;
    _ccCorOffset = 0.;
    _ecPhiCor = 0.;
  }
  ~EMClusterPosCorr() {;}
  EMClusterPosCorr(cafe::Config config);

  void CorrectClusterPosition( double xcal, double ycal, double zcal,
			       double &xcor, double &ycor, double &zcor,
			       int floor) const;
  void CorrectClusterPosition( const double *xyzlocal, double *xyzcorrected, int floor) const;
private:
  bool _debug;
  int _correctionVersion;
  double _Zlimit;
  
  bool _rShiftCor; // correct5
  double _rShift[4];
  double _rShiftN[4];
  double _rShiftS[4];
  double _zShiftCor;
  double _phiShift;
  
  bool _zTwistCor; // correct8
  double _zTwistFactor;
  double _zTwistOffset;
  double _zTwistECFactorPos;
  double _zTwistECOffsetPos;
  double _zTwistECFactorNeg;
  double _zTwistECOffsetNeg;
  
  bool _etaPhiModCor; // correct4
  double _ccEtaCor;
  double _ccPhiCorAmp[4];
  double _ccPhiCorP1[4];
  double _ecEtaCorPos;
  double _ecEtaCorNeg;
  double _ecPhiCorFactor;
  double _ecPhiCorOffset;
  
  bool _correctZ; //correctz
  double _zCentre; // CC
  double _zCentreN[4]; // ECN
  double _zCentreS[4]; // ECS
  
  bool _correctXY; // correctxy
  double _xCentre;
  double _xCentreN; // ECN
  double _xCentreS; // ECS
  double _yCentre;
  double _yCentreN; // ECN
  double _yCentreS; // ECS

  bool _alphaCorr;
  double _xCorAlpha;
  double _yCorAlpha;
  
  bool _correctEC_XYPhi; // correct6
  double _xFacN;
  double _yFacN;
  double _xFacS;
  double _yFacS;
  double _xOffN;
  double _yOffN;
  double _xOffS;
  double _yOffS;
  
  bool _correctRZ; // correct7
  double _rLimit;
  double _rCorrECInnerNeg[4];
  double _rCorrECInnerPos[4];
  double _rCorrECOuterNeg[2];
  double _rCorrECOuterPos[2];
  double _zCorrCC[5];
  double _zCorrZLim;
  double _zCorrFactorPos;
  double _zCorrOffsetPos;
  double _zCorrFactorNeg;
  double _zCorrOffsetNeg;

  bool _correctTilt; // old tilt (CC) and rotation (EC) correction from p14
  double  _ccCorFactor;
  double  _ccCorOffset;
  double  _ecPhiCor;
  
};
#endif //_EMCLUSTERPOSCOR_HPP
