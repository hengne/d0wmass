{
const int n_trkEffVsEtaZvtx_xbins = 64;
float trkEffVsEtaZvtx_xbins[n_trkEffVsEtaZvtx_xbins+1] = {-3.200000 ,-3.100000 ,-3.000000 ,-2.900000 ,-2.800000 ,-2.700000 ,-2.600000 ,-2.500000 ,-2.400000 ,-2.300000 ,-2.200000 ,-2.100000 ,-2.000000 ,-1.900000 ,-1.800000 ,-1.700000 ,-1.600000 ,-1.500000 ,-1.400000 ,-1.300000 ,-1.200000 ,-1.100000 ,-1.000000 ,-0.900000 ,-0.800000 ,-0.700000 ,-0.600000 ,-0.500000 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.400000 ,0.500000 ,0.600000 ,0.700000 ,0.800000 ,0.900000 ,1.000000 ,1.100000 ,1.200000 ,1.300000 ,1.400000 ,1.500000 ,1.600000 ,1.700000 ,1.800000 ,1.900000 ,2.000000 ,2.100000 ,2.200000 ,2.300000 ,2.400000 ,2.500000 ,2.600000 ,2.700000 ,2.800000 ,2.900000 ,3.000000 ,3.100000 ,3.200000  };

const int n_trkEffVsEtaZvtx_ybins = 10;
float trkEffVsEtaZvtx_ybins[n_trkEffVsEtaZvtx_ybins+1] = {-100.000000 ,-39.000000 ,-30.000000 ,-23.000000 ,-10.000000 ,0.000000 ,10.000000 ,23.000000 ,30.000000 ,39.000000 ,100.000000  };

TH2F *trkEffVsEtaZvtx = new TH2F("trkEffVsEtaZvtx","track efficiency vs detector eta and zvtx", n_trkEffVsEtaZvtx_xbins, trkEffVsEtaZvtx_xbins, n_trkEffVsEtaZvtx_ybins, trkEffVsEtaZvtx_ybins);

////////////////////////////////////////////////////
// ybin: under -100.000000

////////////////////////////////////////////////////
// ybin: -100.000000 to -39.000000

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,1,0.188420);
trkEffVsEtaZvtx->SetBinError(16,1,0.135471);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,1,0.188420);
trkEffVsEtaZvtx->SetBinError(17,1,0.135471);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,1,0.637892);
trkEffVsEtaZvtx->SetBinError(22,1,0.113934);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,1,0.637892);
trkEffVsEtaZvtx->SetBinError(23,1,0.113934);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,1,0.732061);
trkEffVsEtaZvtx->SetBinError(24,1,0.100549);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,1,0.732061);
trkEffVsEtaZvtx->SetBinError(25,1,0.100549);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,1,0.711466);
trkEffVsEtaZvtx->SetBinError(26,1,0.080114);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,1,0.711466);
trkEffVsEtaZvtx->SetBinError(27,1,0.080114);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,1,0.594925);
trkEffVsEtaZvtx->SetBinError(28,1,0.096680);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,1,0.594925);
trkEffVsEtaZvtx->SetBinError(29,1,0.096680);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,1,0.704188);
trkEffVsEtaZvtx->SetBinError(30,1,0.099653);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,1,0.704188);
trkEffVsEtaZvtx->SetBinError(31,1,0.099653);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,1,0.835101);
trkEffVsEtaZvtx->SetBinError(32,1,0.076878);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,1,0.835101);
trkEffVsEtaZvtx->SetBinError(33,1,0.076878);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,1,0.596470);
trkEffVsEtaZvtx->SetBinError(34,1,0.092351);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,1,0.596470);
trkEffVsEtaZvtx->SetBinError(35,1,0.092351);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,1,0.761809);
trkEffVsEtaZvtx->SetBinError(36,1,0.097389);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,1,0.761809);
trkEffVsEtaZvtx->SetBinError(37,1,0.097389);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,1,0.816171);
trkEffVsEtaZvtx->SetBinError(38,1,0.078888);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,1,0.816171);
trkEffVsEtaZvtx->SetBinError(39,1,0.078888);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,1,0.908227);
trkEffVsEtaZvtx->SetBinError(40,1,0.066200);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,1,0.908227);
trkEffVsEtaZvtx->SetBinError(41,1,0.066200);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,1,0.857142);
trkEffVsEtaZvtx->SetBinError(42,1,0.096772);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,1,0.857142);
trkEffVsEtaZvtx->SetBinError(43,1,0.096772);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,1,0.837734);
trkEffVsEtaZvtx->SetBinError(48,1,0.063933);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,1,0.837734);
trkEffVsEtaZvtx->SetBinError(49,1,0.063933);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,1,0.840315);
trkEffVsEtaZvtx->SetBinError(50,1,0.082950);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,1,0.840315);
trkEffVsEtaZvtx->SetBinError(51,1,0.082950);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,1,0.752485);
trkEffVsEtaZvtx->SetBinError(52,1,0.107844);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,1,0.752485);
trkEffVsEtaZvtx->SetBinError(53,1,0.107844);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,1,0.752485);
trkEffVsEtaZvtx->SetBinError(54,1,0.107844);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,1,0.752485);
trkEffVsEtaZvtx->SetBinError(55,1,0.107844);

////////////////////////////////////////////////////
// ybin: -39.000000 to -30.000000

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,2,0.125004);
trkEffVsEtaZvtx->SetBinError(14,2,0.120916);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,2,0.125004);
trkEffVsEtaZvtx->SetBinError(15,2,0.120916);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,2,0.347841);
trkEffVsEtaZvtx->SetBinError(16,2,0.133132);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,2,0.347841);
trkEffVsEtaZvtx->SetBinError(17,2,0.133132);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,2,0.767480);
trkEffVsEtaZvtx->SetBinError(22,2,0.089608);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,2,0.767480);
trkEffVsEtaZvtx->SetBinError(23,2,0.089608);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,2,0.740049);
trkEffVsEtaZvtx->SetBinError(24,2,0.086163);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,2,0.740049);
trkEffVsEtaZvtx->SetBinError(25,2,0.086163);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,2,0.742887);
trkEffVsEtaZvtx->SetBinError(26,2,0.072951);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,2,0.742887);
trkEffVsEtaZvtx->SetBinError(27,2,0.072951);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,2,0.742884);
trkEffVsEtaZvtx->SetBinError(28,2,0.072951);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,2,0.742884);
trkEffVsEtaZvtx->SetBinError(29,2,0.072951);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,2,0.759304);
trkEffVsEtaZvtx->SetBinError(30,2,0.081108);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,2,0.759304);
trkEffVsEtaZvtx->SetBinError(31,2,0.081108);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,2,0.815428);
trkEffVsEtaZvtx->SetBinError(32,2,0.067816);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,2,0.815428);
trkEffVsEtaZvtx->SetBinError(33,2,0.067816);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,2,0.800032);
trkEffVsEtaZvtx->SetBinError(34,2,0.064966);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,2,0.800032);
trkEffVsEtaZvtx->SetBinError(35,2,0.064966);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,2,0.887127);
trkEffVsEtaZvtx->SetBinError(36,2,0.058007);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,2,0.887127);
trkEffVsEtaZvtx->SetBinError(37,2,0.058007);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,2,0.760053);
trkEffVsEtaZvtx->SetBinError(38,2,0.084113);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,2,0.760053);
trkEffVsEtaZvtx->SetBinError(39,2,0.084113);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,2,0.736888);
trkEffVsEtaZvtx->SetBinError(40,2,0.081166);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,2,0.736888);
trkEffVsEtaZvtx->SetBinError(41,2,0.081166);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,2,0.621657);
trkEffVsEtaZvtx->SetBinError(42,2,0.108787);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,2,0.621657);
trkEffVsEtaZvtx->SetBinError(43,2,0.108787);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,2,0.942392);
trkEffVsEtaZvtx->SetBinError(48,2,0.049918);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,2,0.942392);
trkEffVsEtaZvtx->SetBinError(49,2,0.049918);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,2,0.777831);
trkEffVsEtaZvtx->SetBinError(50,2,0.086422);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,2,0.777831);
trkEffVsEtaZvtx->SetBinError(51,2,0.086422);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,2,0.562542);
trkEffVsEtaZvtx->SetBinError(52,2,0.139020);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,2,0.562542);
trkEffVsEtaZvtx->SetBinError(53,2,0.139020);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,2,0.562542);
trkEffVsEtaZvtx->SetBinError(54,2,0.139020);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,2,0.562542);
trkEffVsEtaZvtx->SetBinError(55,2,0.139020);

////////////////////////////////////////////////////
// ybin: -30.000000 to -23.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,3,0.268269);
trkEffVsEtaZvtx->SetBinError(10,3,0.179772);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,3,0.268269);
trkEffVsEtaZvtx->SetBinError(11,3,0.179772);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,3,0.268269);
trkEffVsEtaZvtx->SetBinError(12,3,0.179772);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,3,0.268269);
trkEffVsEtaZvtx->SetBinError(13,3,0.179772);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,3,0.342472);
trkEffVsEtaZvtx->SetBinError(14,3,0.131861);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,3,0.342472);
trkEffVsEtaZvtx->SetBinError(15,3,0.131861);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,3,0.747382);
trkEffVsEtaZvtx->SetBinError(16,3,0.107790);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,3,0.747382);
trkEffVsEtaZvtx->SetBinError(17,3,0.107790);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,3,0.753028);
trkEffVsEtaZvtx->SetBinError(22,3,0.090432);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,3,0.753028);
trkEffVsEtaZvtx->SetBinError(23,3,0.090432);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,3,0.700294);
trkEffVsEtaZvtx->SetBinError(24,3,0.077014);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,3,0.700294);
trkEffVsEtaZvtx->SetBinError(25,3,0.077014);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,3,0.759829);
trkEffVsEtaZvtx->SetBinError(26,3,0.068463);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,3,0.759829);
trkEffVsEtaZvtx->SetBinError(27,3,0.068463);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,3,0.770925);
trkEffVsEtaZvtx->SetBinError(28,3,0.070334);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,3,0.770925);
trkEffVsEtaZvtx->SetBinError(29,3,0.070334);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,3,0.826206);
trkEffVsEtaZvtx->SetBinError(30,3,0.059915);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,3,0.826206);
trkEffVsEtaZvtx->SetBinError(31,3,0.059915);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,3,0.747972);
trkEffVsEtaZvtx->SetBinError(32,3,0.076437);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,3,0.747972);
trkEffVsEtaZvtx->SetBinError(33,3,0.076437);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,3,0.717921);
trkEffVsEtaZvtx->SetBinError(34,3,0.069927);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,3,0.717921);
trkEffVsEtaZvtx->SetBinError(35,3,0.069927);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,3,0.847246);
trkEffVsEtaZvtx->SetBinError(36,3,0.062846);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,3,0.847246);
trkEffVsEtaZvtx->SetBinError(37,3,0.062846);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,3,0.761423);
trkEffVsEtaZvtx->SetBinError(38,3,0.077429);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,3,0.761423);
trkEffVsEtaZvtx->SetBinError(39,3,0.077429);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,3,0.816585);
trkEffVsEtaZvtx->SetBinError(40,3,0.069711);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,3,0.816585);
trkEffVsEtaZvtx->SetBinError(41,3,0.069711);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,3,0.827428);
trkEffVsEtaZvtx->SetBinError(42,3,0.076747);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,3,0.827428);
trkEffVsEtaZvtx->SetBinError(43,3,0.076747);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,3,0.939107);
trkEffVsEtaZvtx->SetBinError(48,3,0.050854);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,3,0.939107);
trkEffVsEtaZvtx->SetBinError(49,3,0.050854);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,3,0.930346);
trkEffVsEtaZvtx->SetBinError(50,3,0.066166);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,3,0.930346);
trkEffVsEtaZvtx->SetBinError(51,3,0.066166);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,3,0.834519);
trkEffVsEtaZvtx->SetBinError(52,3,0.095176);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,3,0.834519);
trkEffVsEtaZvtx->SetBinError(53,3,0.095176);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,3,0.834519);
trkEffVsEtaZvtx->SetBinError(54,3,0.095176);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,3,0.834519);
trkEffVsEtaZvtx->SetBinError(55,3,0.095176);

////////////////////////////////////////////////////
// ybin: -23.000000 to -10.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,4,0.428592);
trkEffVsEtaZvtx->SetBinError(10,4,0.120320);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,4,0.625025);
trkEffVsEtaZvtx->SetBinError(11,4,0.111840);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,4,0.368436);
trkEffVsEtaZvtx->SetBinError(12,4,0.103537);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,4,0.421072);
trkEffVsEtaZvtx->SetBinError(13,4,0.105510);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,4,0.416690);
trkEffVsEtaZvtx->SetBinError(14,4,0.095083);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,4,0.750068);
trkEffVsEtaZvtx->SetBinError(15,4,0.092862);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,4,0.612957);
trkEffVsEtaZvtx->SetBinError(16,4,0.083799);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,4,0.888974);
trkEffVsEtaZvtx->SetBinError(17,4,0.048156);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,4,0.666694);
trkEffVsEtaZvtx->SetBinError(22,4,0.075967);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,4,0.693914);
trkEffVsEtaZvtx->SetBinError(23,4,0.046020);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,4,0.769275);
trkEffVsEtaZvtx->SetBinError(24,4,0.047282);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,4,0.786438);
trkEffVsEtaZvtx->SetBinError(25,4,0.040171);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,4,0.827195);
trkEffVsEtaZvtx->SetBinError(26,4,0.041982);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,4,0.774224);
trkEffVsEtaZvtx->SetBinError(27,4,0.043053);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,4,0.805857);
trkEffVsEtaZvtx->SetBinError(28,4,0.038850);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,4,0.785069);
trkEffVsEtaZvtx->SetBinError(29,4,0.039508);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,4,0.811798);
trkEffVsEtaZvtx->SetBinError(30,4,0.042266);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,4,0.772754);
trkEffVsEtaZvtx->SetBinError(31,4,0.039716);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,4,0.809551);
trkEffVsEtaZvtx->SetBinError(32,4,0.038216);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,4,0.804386);
trkEffVsEtaZvtx->SetBinError(33,4,0.041200);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,4,0.791699);
trkEffVsEtaZvtx->SetBinError(34,4,0.041238);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,4,0.800039);
trkEffVsEtaZvtx->SetBinError(35,4,0.043180);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,4,0.831492);
trkEffVsEtaZvtx->SetBinError(36,4,0.039686);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,4,0.770027);
trkEffVsEtaZvtx->SetBinError(37,4,0.041795);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,4,0.747776);
trkEffVsEtaZvtx->SetBinError(38,4,0.040907);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,4,0.732592);
trkEffVsEtaZvtx->SetBinError(39,4,0.047208);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,4,0.625032);
trkEffVsEtaZvtx->SetBinError(40,4,0.056001);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,4,0.823571);
trkEffVsEtaZvtx->SetBinError(41,4,0.041295);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,4,0.762544);
trkEffVsEtaZvtx->SetBinError(42,4,0.047135);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,4,0.622242);
trkEffVsEtaZvtx->SetBinError(43,4,0.070165);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,4,0.933396);
trkEffVsEtaZvtx->SetBinError(48,4,0.027484);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,4,0.895604);
trkEffVsEtaZvtx->SetBinError(49,4,0.038256);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,4,0.835870);
trkEffVsEtaZvtx->SetBinError(50,4,0.045300);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,4,0.893701);
trkEffVsEtaZvtx->SetBinError(51,4,0.046348);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,4,0.795967);
trkEffVsEtaZvtx->SetBinError(52,4,0.057034);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,4,0.657172);
trkEffVsEtaZvtx->SetBinError(53,4,0.077444);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,4,0.783811);
trkEffVsEtaZvtx->SetBinError(54,4,0.066616);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,4,0.777806);
trkEffVsEtaZvtx->SetBinError(55,4,0.068076);

////////////////////////////////////////////////////
// ybin: -10.000000 to 0.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,5,0.454593);
trkEffVsEtaZvtx->SetBinError(10,5,0.133241);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,5,0.333353);
trkEffVsEtaZvtx->SetBinError(11,5,0.123722);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,5,0.400020);
trkEffVsEtaZvtx->SetBinError(12,5,0.116005);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,5,0.500024);
trkEffVsEtaZvtx->SetBinError(13,5,0.100002);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,5,0.800055);
trkEffVsEtaZvtx->SetBinError(14,5,0.087378);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,5,0.769309);
trkEffVsEtaZvtx->SetBinError(15,5,0.080405);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,5,0.863703);
trkEffVsEtaZvtx->SetBinError(16,5,0.052386);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,5,0.961709);
trkEffVsEtaZvtx->SetBinError(17,5,0.047780);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,5,0.691260);
trkEffVsEtaZvtx->SetBinError(22,5,0.082624);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,5,0.722420);
trkEffVsEtaZvtx->SetBinError(23,5,0.053579);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,5,0.774023);
trkEffVsEtaZvtx->SetBinError(24,5,0.044290);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,5,0.809911);
trkEffVsEtaZvtx->SetBinError(25,5,0.045788);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,5,0.760213);
trkEffVsEtaZvtx->SetBinError(26,5,0.046471);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,5,0.836123);
trkEffVsEtaZvtx->SetBinError(27,5,0.038866);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,5,0.784352);
trkEffVsEtaZvtx->SetBinError(28,5,0.041541);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,5,0.803057);
trkEffVsEtaZvtx->SetBinError(29,5,0.042721);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,5,0.783393);
trkEffVsEtaZvtx->SetBinError(30,5,0.042703);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,5,0.853188);
trkEffVsEtaZvtx->SetBinError(31,5,0.037925);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,5,0.792678);
trkEffVsEtaZvtx->SetBinError(32,5,0.040163);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,5,0.840534);
trkEffVsEtaZvtx->SetBinError(33,5,0.040785);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,5,0.808905);
trkEffVsEtaZvtx->SetBinError(34,5,0.035817);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,5,0.865655);
trkEffVsEtaZvtx->SetBinError(35,5,0.035083);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,5,0.872968);
trkEffVsEtaZvtx->SetBinError(36,5,0.036299);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,5,0.871208);
trkEffVsEtaZvtx->SetBinError(37,5,0.038608);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,5,0.902181);
trkEffVsEtaZvtx->SetBinError(38,5,0.033816);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,5,0.851569);
trkEffVsEtaZvtx->SetBinError(39,5,0.038304);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,5,0.908380);
trkEffVsEtaZvtx->SetBinError(40,5,0.031953);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,5,0.732986);
trkEffVsEtaZvtx->SetBinError(41,5,0.048338);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,5,0.781156);
trkEffVsEtaZvtx->SetBinError(42,5,0.049759);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,5,0.807220);
trkEffVsEtaZvtx->SetBinError(43,5,0.065167);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,5,0.927607);
trkEffVsEtaZvtx->SetBinError(48,5,0.032769);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,5,0.945541);
trkEffVsEtaZvtx->SetBinError(49,5,0.033525);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,5,0.816391);
trkEffVsEtaZvtx->SetBinError(50,5,0.055054);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,5,0.775905);
trkEffVsEtaZvtx->SetBinError(51,5,0.054152);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,5,0.875028);
trkEffVsEtaZvtx->SetBinError(52,5,0.048585);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,5,0.739156);
trkEffVsEtaZvtx->SetBinError(53,5,0.063484);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,5,0.714316);
trkEffVsEtaZvtx->SetBinError(54,5,0.074146);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,5,0.690494);
trkEffVsEtaZvtx->SetBinError(55,5,0.069433);

////////////////////////////////////////////////////
// ybin: 0.000000 to 10.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,6,0.571779);
trkEffVsEtaZvtx->SetBinError(10,6,0.089018);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,6,0.593888);
trkEffVsEtaZvtx->SetBinError(11,6,0.089970);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,6,0.736673);
trkEffVsEtaZvtx->SetBinError(12,6,0.073593);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,6,0.764318);
trkEffVsEtaZvtx->SetBinError(13,6,0.082617);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,6,0.884824);
trkEffVsEtaZvtx->SetBinError(14,6,0.049985);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,6,0.949438);
trkEffVsEtaZvtx->SetBinError(15,6,0.041380);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,6,0.801527);
trkEffVsEtaZvtx->SetBinError(16,6,0.051736);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,6,0.856386);
trkEffVsEtaZvtx->SetBinError(17,6,0.047712);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,6,0.871824);
trkEffVsEtaZvtx->SetBinError(22,6,0.054535);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,6,0.800043);
trkEffVsEtaZvtx->SetBinError(23,6,0.049301);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,6,0.840625);
trkEffVsEtaZvtx->SetBinError(24,6,0.044163);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,6,0.753116);
trkEffVsEtaZvtx->SetBinError(25,6,0.047433);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,6,0.868161);
trkEffVsEtaZvtx->SetBinError(26,6,0.035763);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,6,0.867498);
trkEffVsEtaZvtx->SetBinError(27,6,0.037545);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,6,0.821803);
trkEffVsEtaZvtx->SetBinError(28,6,0.038032);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,6,0.833364);
trkEffVsEtaZvtx->SetBinError(29,6,0.039302);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,6,0.815831);
trkEffVsEtaZvtx->SetBinError(30,6,0.044339);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,6,0.822941);
trkEffVsEtaZvtx->SetBinError(31,6,0.038915);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,6,0.770854);
trkEffVsEtaZvtx->SetBinError(32,6,0.042594);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,6,0.916701);
trkEffVsEtaZvtx->SetBinError(33,6,0.029021);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,6,0.815241);
trkEffVsEtaZvtx->SetBinError(34,6,0.040368);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,6,0.811349);
trkEffVsEtaZvtx->SetBinError(35,6,0.037907);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,6,0.787059);
trkEffVsEtaZvtx->SetBinError(36,6,0.039200);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,6,0.785738);
trkEffVsEtaZvtx->SetBinError(37,6,0.041218);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,6,0.777805);
trkEffVsEtaZvtx->SetBinError(38,6,0.039775);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,6,0.852667);
trkEffVsEtaZvtx->SetBinError(39,6,0.036521);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,6,0.729200);
trkEffVsEtaZvtx->SetBinError(40,6,0.044902);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,6,0.715938);
trkEffVsEtaZvtx->SetBinError(41,6,0.047513);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,6,0.747161);
trkEffVsEtaZvtx->SetBinError(42,6,0.046144);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,6,0.857178);
trkEffVsEtaZvtx->SetBinError(43,6,0.054521);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,6,0.989801);
trkEffVsEtaZvtx->SetBinError(48,6,0.024412);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,6,0.957874);
trkEffVsEtaZvtx->SetBinError(49,6,0.040171);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,6,0.734121);
trkEffVsEtaZvtx->SetBinError(50,6,0.065502);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,6,0.766657);
trkEffVsEtaZvtx->SetBinError(51,6,0.082504);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,6,0.643681);
trkEffVsEtaZvtx->SetBinError(52,6,0.071720);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,6,0.630621);
trkEffVsEtaZvtx->SetBinError(53,6,0.078714);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,6,0.653096);
trkEffVsEtaZvtx->SetBinError(54,6,0.100347);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,6,0.505195);
trkEffVsEtaZvtx->SetBinError(55,6,0.100451);

////////////////////////////////////////////////////
// ybin: 10.000000 to 23.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,7,0.691033);
trkEffVsEtaZvtx->SetBinError(10,7,0.108136);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,7,0.786386);
trkEffVsEtaZvtx->SetBinError(11,7,0.083534);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,7,0.739559);
trkEffVsEtaZvtx->SetBinError(12,7,0.078086);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,7,0.415514);
trkEffVsEtaZvtx->SetBinError(13,7,0.110958);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,7,0.814227);
trkEffVsEtaZvtx->SetBinError(14,7,0.063600);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,7,0.705316);
trkEffVsEtaZvtx->SetBinError(15,7,0.070435);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,7,0.903502);
trkEffVsEtaZvtx->SetBinError(16,7,0.041069);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,7,0.974496);
trkEffVsEtaZvtx->SetBinError(17,7,0.028008);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,7,0.778263);
trkEffVsEtaZvtx->SetBinError(22,7,0.068052);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,7,0.768845);
trkEffVsEtaZvtx->SetBinError(23,7,0.046178);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,7,0.771947);
trkEffVsEtaZvtx->SetBinError(24,7,0.045709);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,7,0.836740);
trkEffVsEtaZvtx->SetBinError(25,7,0.045236);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,7,0.929640);
trkEffVsEtaZvtx->SetBinError(26,7,0.029162);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,7,0.841394);
trkEffVsEtaZvtx->SetBinError(27,7,0.037775);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,7,0.730450);
trkEffVsEtaZvtx->SetBinError(28,7,0.047624);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,7,0.732768);
trkEffVsEtaZvtx->SetBinError(29,7,0.048343);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,7,0.817215);
trkEffVsEtaZvtx->SetBinError(30,7,0.044257);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,7,0.777434);
trkEffVsEtaZvtx->SetBinError(31,7,0.040759);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,7,0.859446);
trkEffVsEtaZvtx->SetBinError(32,7,0.033956);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,7,0.788974);
trkEffVsEtaZvtx->SetBinError(33,7,0.040825);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,7,0.832909);
trkEffVsEtaZvtx->SetBinError(34,7,0.037165);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,7,0.817068);
trkEffVsEtaZvtx->SetBinError(35,7,0.041382);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,7,0.795857);
trkEffVsEtaZvtx->SetBinError(36,7,0.045406);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,7,0.816944);
trkEffVsEtaZvtx->SetBinError(37,7,0.041388);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,7,0.688466);
trkEffVsEtaZvtx->SetBinError(38,7,0.046733);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,7,0.805824);
trkEffVsEtaZvtx->SetBinError(39,7,0.042278);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,7,0.748064);
trkEffVsEtaZvtx->SetBinError(40,7,0.045111);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,7,0.850192);
trkEffVsEtaZvtx->SetBinError(41,7,0.037164);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,7,0.770772);
trkEffVsEtaZvtx->SetBinError(42,7,0.044733);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,7,0.708350);
trkEffVsEtaZvtx->SetBinError(43,7,0.069221);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,7,0.850786);
trkEffVsEtaZvtx->SetBinError(48,7,0.047244);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,7,0.859527);
trkEffVsEtaZvtx->SetBinError(49,7,0.056745);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,7,0.644181);
trkEffVsEtaZvtx->SetBinError(50,7,0.075821);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,7,0.531797);
trkEffVsEtaZvtx->SetBinError(51,7,0.076586);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,7,0.572190);
trkEffVsEtaZvtx->SetBinError(52,7,0.097736);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,7,0.628524);
trkEffVsEtaZvtx->SetBinError(53,7,0.086305);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,7,0.579305);
trkEffVsEtaZvtx->SetBinError(54,7,0.101615);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,7,0.415606);
trkEffVsEtaZvtx->SetBinError(55,7,0.099537);

////////////////////////////////////////////////////
// ybin: 23.000000 to 30.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,8,0.690745);
trkEffVsEtaZvtx->SetBinError(10,8,0.151809);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,8,0.690745);
trkEffVsEtaZvtx->SetBinError(11,8,0.151809);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,8,0.690745);
trkEffVsEtaZvtx->SetBinError(12,8,0.151809);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,8,0.690745);
trkEffVsEtaZvtx->SetBinError(13,8,0.151809);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,8,0.880528);
trkEffVsEtaZvtx->SetBinError(14,8,0.086960);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,8,0.880528);
trkEffVsEtaZvtx->SetBinError(15,8,0.086960);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,8,0.988417);
trkEffVsEtaZvtx->SetBinError(16,8,0.044449);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,8,0.988417);
trkEffVsEtaZvtx->SetBinError(17,8,0.044449);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,8,0.836670);
trkEffVsEtaZvtx->SetBinError(22,8,0.095656);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,8,0.836670);
trkEffVsEtaZvtx->SetBinError(23,8,0.095656);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,8,0.806553);
trkEffVsEtaZvtx->SetBinError(24,8,0.077820);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,8,0.806553);
trkEffVsEtaZvtx->SetBinError(25,8,0.077820);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,8,0.788128);
trkEffVsEtaZvtx->SetBinError(26,8,0.076608);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,8,0.788128);
trkEffVsEtaZvtx->SetBinError(27,8,0.076608);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,8,0.773092);
trkEffVsEtaZvtx->SetBinError(28,8,0.068365);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,8,0.773092);
trkEffVsEtaZvtx->SetBinError(29,8,0.068365);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,8,0.777907);
trkEffVsEtaZvtx->SetBinError(30,8,0.065333);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,8,0.777907);
trkEffVsEtaZvtx->SetBinError(31,8,0.065333);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,8,0.677486);
trkEffVsEtaZvtx->SetBinError(32,8,0.074289);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,8,0.677486);
trkEffVsEtaZvtx->SetBinError(33,8,0.074289);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,8,0.696663);
trkEffVsEtaZvtx->SetBinError(34,8,0.081265);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,8,0.696663);
trkEffVsEtaZvtx->SetBinError(35,8,0.081265);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,8,0.735411);
trkEffVsEtaZvtx->SetBinError(36,8,0.079411);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,8,0.735411);
trkEffVsEtaZvtx->SetBinError(37,8,0.079411);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,8,0.759224);
trkEffVsEtaZvtx->SetBinError(38,8,0.071574);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,8,0.759224);
trkEffVsEtaZvtx->SetBinError(39,8,0.071574);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,8,0.793627);
trkEffVsEtaZvtx->SetBinError(40,8,0.067090);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,8,0.793627);
trkEffVsEtaZvtx->SetBinError(41,8,0.067090);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,8,0.816794);
trkEffVsEtaZvtx->SetBinError(42,8,0.074235);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,8,0.816794);
trkEffVsEtaZvtx->SetBinError(43,8,0.074235);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,8,0.824893);
trkEffVsEtaZvtx->SetBinError(48,8,0.095273);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,8,0.824893);
trkEffVsEtaZvtx->SetBinError(49,8,0.095273);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,8,0.359666);
trkEffVsEtaZvtx->SetBinError(50,8,0.122960);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,8,0.359666);
trkEffVsEtaZvtx->SetBinError(51,8,0.122960);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,8,0.208291);
trkEffVsEtaZvtx->SetBinError(52,8,0.148605);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,8,0.208291);
trkEffVsEtaZvtx->SetBinError(53,8,0.148605);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,8,0.208291);
trkEffVsEtaZvtx->SetBinError(54,8,0.148605);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,8,0.208291);
trkEffVsEtaZvtx->SetBinError(55,8,0.148605);

////////////////////////////////////////////////////
// ybin: 30.000000 to 39.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,9,0.545095);
trkEffVsEtaZvtx->SetBinError(10,9,0.158191);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,9,0.545095);
trkEffVsEtaZvtx->SetBinError(11,9,0.158191);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,9,0.545095);
trkEffVsEtaZvtx->SetBinError(12,9,0.158191);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,9,0.545095);
trkEffVsEtaZvtx->SetBinError(13,9,0.158191);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,9,0.850072);
trkEffVsEtaZvtx->SetBinError(14,9,0.090258);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,9,0.850072);
trkEffVsEtaZvtx->SetBinError(15,9,0.090258);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,9,0.852243);
trkEffVsEtaZvtx->SetBinError(16,9,0.083936);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,9,0.852243);
trkEffVsEtaZvtx->SetBinError(17,9,0.083936);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,9,0.600034);
trkEffVsEtaZvtx->SetBinError(22,9,0.112638);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,9,0.600034);
trkEffVsEtaZvtx->SetBinError(23,9,0.112638);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,9,0.645880);
trkEffVsEtaZvtx->SetBinError(24,9,0.095055);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,9,0.645880);
trkEffVsEtaZvtx->SetBinError(25,9,0.095055);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,9,0.812550);
trkEffVsEtaZvtx->SetBinError(26,9,0.079207);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,9,0.812550);
trkEffVsEtaZvtx->SetBinError(27,9,0.079207);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,9,0.659129);
trkEffVsEtaZvtx->SetBinError(28,9,0.098249);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,9,0.659129);
trkEffVsEtaZvtx->SetBinError(29,9,0.098249);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,9,0.875046);
trkEffVsEtaZvtx->SetBinError(30,9,0.063481);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,9,0.875046);
trkEffVsEtaZvtx->SetBinError(31,9,0.063481);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,9,0.808852);
trkEffVsEtaZvtx->SetBinError(32,9,0.067132);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,9,0.808852);
trkEffVsEtaZvtx->SetBinError(33,9,0.067132);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,9,0.678615);
trkEffVsEtaZvtx->SetBinError(34,9,0.086411);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,9,0.678615);
trkEffVsEtaZvtx->SetBinError(35,9,0.086411);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,9,0.661996);
trkEffVsEtaZvtx->SetBinError(36,9,0.078013);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,9,0.661996);
trkEffVsEtaZvtx->SetBinError(37,9,0.078013);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,9,0.687535);
trkEffVsEtaZvtx->SetBinError(38,9,0.080473);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,9,0.687535);
trkEffVsEtaZvtx->SetBinError(39,9,0.080473);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,9,0.760592);
trkEffVsEtaZvtx->SetBinError(40,9,0.070857);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,9,0.760592);
trkEffVsEtaZvtx->SetBinError(41,9,0.070857);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,9,0.673116);
trkEffVsEtaZvtx->SetBinError(42,9,0.089893);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,9,0.673116);
trkEffVsEtaZvtx->SetBinError(43,9,0.089893);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,9,0.481508);
trkEffVsEtaZvtx->SetBinError(48,9,0.139016);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,9,0.481508);
trkEffVsEtaZvtx->SetBinError(49,9,0.139016);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,9,0.211168);
trkEffVsEtaZvtx->SetBinError(50,9,0.128714);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,9,0.211168);
trkEffVsEtaZvtx->SetBinError(51,9,0.128714);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,9,0.067055);
trkEffVsEtaZvtx->SetBinError(52,9,0.152595);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,9,0.067055);
trkEffVsEtaZvtx->SetBinError(53,9,0.152595);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,9,0.067055);
trkEffVsEtaZvtx->SetBinError(54,9,0.152595);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,9,0.067055);
trkEffVsEtaZvtx->SetBinError(55,9,0.152595);

////////////////////////////////////////////////////
// ybin: 39.000000 to 100.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,10,0.695101);
trkEffVsEtaZvtx->SetBinError(10,10,0.134559);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,10,0.695101);
trkEffVsEtaZvtx->SetBinError(11,10,0.134559);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,10,0.695101);
trkEffVsEtaZvtx->SetBinError(12,10,0.134559);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,10,0.695101);
trkEffVsEtaZvtx->SetBinError(13,10,0.134559);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,10,0.852685);
trkEffVsEtaZvtx->SetBinError(14,10,0.091723);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,10,0.852685);
trkEffVsEtaZvtx->SetBinError(15,10,0.091723);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,10,0.961855);
trkEffVsEtaZvtx->SetBinError(16,10,0.057752);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,10,0.961855);
trkEffVsEtaZvtx->SetBinError(17,10,0.057752);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,10,0.840373);
trkEffVsEtaZvtx->SetBinError(22,10,0.106339);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,10,0.840373);
trkEffVsEtaZvtx->SetBinError(23,10,0.106339);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,10,0.846843);
trkEffVsEtaZvtx->SetBinError(24,10,0.077462);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,10,0.846843);
trkEffVsEtaZvtx->SetBinError(25,10,0.077462);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,10,0.639412);
trkEffVsEtaZvtx->SetBinError(26,10,0.119386);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,10,0.639412);
trkEffVsEtaZvtx->SetBinError(27,10,0.119386);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,10,0.670496);
trkEffVsEtaZvtx->SetBinError(28,10,0.091178);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,10,0.670496);
trkEffVsEtaZvtx->SetBinError(29,10,0.091178);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,10,0.749681);
trkEffVsEtaZvtx->SetBinError(30,10,0.091980);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,10,0.749681);
trkEffVsEtaZvtx->SetBinError(31,10,0.091980);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,10,0.868566);
trkEffVsEtaZvtx->SetBinError(32,10,0.081433);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,10,0.868566);
trkEffVsEtaZvtx->SetBinError(33,10,0.081433);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,10,0.650090);
trkEffVsEtaZvtx->SetBinError(34,10,0.095142);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,10,0.650090);
trkEffVsEtaZvtx->SetBinError(35,10,0.095142);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,10,0.492559);
trkEffVsEtaZvtx->SetBinError(36,10,0.100337);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,10,0.492559);
trkEffVsEtaZvtx->SetBinError(37,10,0.100337);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,10,0.696852);
trkEffVsEtaZvtx->SetBinError(38,10,0.088525);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,10,0.696852);
trkEffVsEtaZvtx->SetBinError(39,10,0.088525);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,10,0.836963);
trkEffVsEtaZvtx->SetBinError(40,10,0.064534);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,10,0.836963);
trkEffVsEtaZvtx->SetBinError(41,10,0.064534);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,10,0.699316);
trkEffVsEtaZvtx->SetBinError(42,10,0.105197);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,10,0.699316);
trkEffVsEtaZvtx->SetBinError(43,10,0.105197);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,10,0.301562);
trkEffVsEtaZvtx->SetBinError(48,10,0.137900);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,10,0.301562);
trkEffVsEtaZvtx->SetBinError(49,10,0.137900);

////////////////////////////////////////////////////
// ybin: over 100.000000
}
