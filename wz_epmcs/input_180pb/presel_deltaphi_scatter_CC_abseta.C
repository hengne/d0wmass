{
const int n_presel_deltaphi_scatter_CC_xbins = 50;
float presel_deltaphi_scatter_CC_xbins[n_presel_deltaphi_scatter_CC_xbins+1] = {0.000000 ,0.020000 ,0.040000 ,0.060000 ,0.080000 ,0.100000 ,0.120000 ,0.140000 ,0.160000 ,0.180000 ,0.200000 ,0.220000 ,0.240000 ,0.260000 ,0.280000 ,0.300000 ,0.320000 ,0.340000 ,0.360000 ,0.380000 ,0.400000 ,0.420000 ,0.440000 ,0.460000 ,0.480000 ,0.500000 ,0.520000 ,0.540000 ,0.560000 ,0.580000 ,0.600000 ,0.620000 ,0.640000 ,0.660000 ,0.680000 ,0.700000 ,0.720000 ,0.740000 ,0.760000 ,0.780000 ,0.800000 ,0.820000 ,0.840000 ,0.860000 ,0.880000 ,0.900000 ,0.920000 ,0.940000 ,0.960000 ,0.980000 ,1.000000  };

const int n_presel_deltaphi_scatter_CC_ybins = 25;
float presel_deltaphi_scatter_CC_ybins[n_presel_deltaphi_scatter_CC_ybins+1] = {-0.200000 ,-0.184000 ,-0.168000 ,-0.152000 ,-0.136000 ,-0.120000 ,-0.104000 ,-0.088000 ,-0.072000 ,-0.056000 ,-0.040000 ,-0.024000 ,-0.008000 ,0.008000 ,0.024000 ,0.040000 ,0.056000 ,0.072000 ,0.088000 ,0.104000 ,0.120000 ,0.136000 ,0.152000 ,0.168000 ,0.184000 ,0.200000  };

const int n_presel_deltaphi_scatter_CC_zbins = 2;
float presel_deltaphi_scatter_CC_zbins[n_presel_deltaphi_scatter_CC_zbins+1] = {0.250000 ,0.500000 ,0.750000  };

TH3F *presel_deltaphi_scatter_CC = new TH3F("presel_deltaphi_scatter_CC","presel deltaphi scatter vs fabs(eta)", n_presel_deltaphi_scatter_CC_xbins, presel_deltaphi_scatter_CC_xbins, n_presel_deltaphi_scatter_CC_ybins, presel_deltaphi_scatter_CC_ybins, n_presel_deltaphi_scatter_CC_zbins, presel_deltaphi_scatter_CC_zbins);

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: under 0.250000

////////////////////////////////////////////////////
// ybin: under -0.200000

////////////////////////////////////////////////////
// ybin: -0.200000 to -0.184000

////////////////////////////////////////////////////
// ybin: -0.184000 to -0.168000

////////////////////////////////////////////////////
// ybin: -0.168000 to -0.152000

////////////////////////////////////////////////////
// ybin: -0.152000 to -0.136000

////////////////////////////////////////////////////
// ybin: -0.136000 to -0.120000

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,5,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(16,5,0,1.000000);

////////////////////////////////////////////////////
// ybin: -0.120000 to -0.104000

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,6,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(28,6,0,1.000000);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,6,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(41,6,0,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,6,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,6,0,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,6,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,6,0,1.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,6,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(47,6,0,1.000000);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,6,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(48,6,0,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,7,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(9,7,0,1.000000);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,7,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(13,7,0,1.000000);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,7,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(20,7,0,1.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,7,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,7,0,1.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,7,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,7,0,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,7,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,7,0,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,7,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(45,7,0,2.000000);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,7,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(48,7,0,2.000000);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,8,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(17,8,0,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,8,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(24,8,0,1.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,8,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(25,8,0,1.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,8,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,8,0,1.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,8,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(43,8,0,1.414214);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,8,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(44,8,0,1.414214);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,8,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(45,8,0,2.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,8,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(46,8,0,1.732051);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,8,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(47,8,0,1.732051);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,8,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(48,8,0,1.000000);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,9,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,9,0,1.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,9,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(8,9,0,1.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,9,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(18,9,0,1.414214);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,9,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(19,9,0,1.414214);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,9,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(20,9,0,1.732051);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,9,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(21,9,0,1.414214);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,9,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(22,9,0,1.732051);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,9,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(24,9,0,2.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,9,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(25,9,0,1.414214);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,9,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(26,9,0,1.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,9,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,9,0,1.000000);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,9,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(35,9,0,1.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,9,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(38,9,0,1.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,9,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(42,9,0,1.732051);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,9,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(43,9,0,1.732051);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,9,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,9,0,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,9,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(45,9,0,2.236068);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,9,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(46,9,0,2.449490);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,9,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(47,9,0,1.732051);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,9,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(48,9,0,1.732051);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,9,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(49,9,0,2.236068);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,10,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(3,10,0,1.000000);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,10,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(6,10,0,1.414214);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,10,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(16,10,0,2.236068);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,10,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(17,10,0,1.732051);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,10,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(18,10,0,1.732051);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,10,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(19,10,0,2.449490);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,10,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(20,10,0,1.732051);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,10,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(21,10,0,2.000000);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,10,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(22,10,0,1.732051);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,10,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(23,10,0,2.236068);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,10,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(24,10,0,1.414214);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,10,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(25,10,0,2.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,10,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(26,10,0,1.732051);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,10,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(27,10,0,1.732051);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,10,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(29,10,0,1.414214);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,10,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(30,10,0,1.000000);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,10,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(32,10,0,1.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,10,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(33,10,0,1.414214);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,10,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(35,10,0,1.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,10,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(37,10,0,1.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,10,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(38,10,0,1.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,10,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(39,10,0,1.414214);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,10,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(40,10,0,1.414214);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,10,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(41,10,0,2.645751);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,10,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(42,10,0,3.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,10,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(43,10,0,2.449490);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,10,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(44,10,0,3.162278);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,10,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(45,10,0,2.645751);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,10,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(46,10,0,2.449490);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,10,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(47,10,0,2.645751);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,10,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(48,10,0,2.236068);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,10,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(49,10,0,1.732051);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,10,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(50,10,0,1.732051);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,11,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,11,0,1.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,11,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(4,11,0,1.732051);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,11,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(6,11,0,1.414214);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,11,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(11,11,0,1.000000);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,11,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(13,11,0,2.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,11,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(14,11,0,1.732051);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,11,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(15,11,0,1.732051);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,11,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(16,11,0,2.645751);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,11,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(17,11,0,2.449490);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,11,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(18,11,0,2.645751);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,11,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(19,11,0,2.236068);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,11,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(20,11,0,2.449490);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,11,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(21,11,0,3.162278);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,11,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(22,11,0,2.236068);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,11,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(23,11,0,2.236068);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,11,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(24,11,0,2.449490);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,11,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(25,11,0,1.414214);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,11,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(26,11,0,1.414214);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,11,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(27,11,0,1.414214);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,11,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(28,11,0,2.449490);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,11,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(29,11,0,2.449490);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,11,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(30,11,0,2.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,11,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(31,11,0,1.732051);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,11,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(32,11,0,1.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,11,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(33,11,0,1.732051);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,11,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(34,11,0,1.414214);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,11,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(35,11,0,1.732051);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,11,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,11,0,1.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,11,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(37,11,0,2.828427);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,11,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(38,11,0,2.236068);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,11,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(39,11,0,2.236068);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,11,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(40,11,0,3.162278);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,11,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(41,11,0,2.828427);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,11,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(42,11,0,2.645751);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,11,0,12.000000);
presel_deltaphi_scatter_CC->SetBinError(43,11,0,3.464102);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,11,0,12.000000);
presel_deltaphi_scatter_CC->SetBinError(44,11,0,3.464102);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,11,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(45,11,0,3.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,11,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(46,11,0,2.645751);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,11,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(47,11,0,2.236068);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,11,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(48,11,0,2.645751);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,11,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,11,0,1.000000);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,12,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(2,12,0,1.414214);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,12,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(3,12,0,2.236068);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,12,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(5,12,0,1.414214);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,12,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(6,12,0,1.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,12,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(8,12,0,2.236068);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,12,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(9,12,0,2.000000);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,12,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(10,12,0,1.000000);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,12,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(11,12,0,2.236068);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,12,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(12,12,0,2.236068);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,12,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(13,12,0,2.449490);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,12,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(14,12,0,2.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,12,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(15,12,0,2.828427);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,12,0,17.000000);
presel_deltaphi_scatter_CC->SetBinError(16,12,0,4.123106);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,12,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(17,12,0,3.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,12,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(18,12,0,3.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,12,0,12.000000);
presel_deltaphi_scatter_CC->SetBinError(19,12,0,3.464102);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,12,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(20,12,0,3.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,12,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(21,12,0,3.000000);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,12,0,12.000000);
presel_deltaphi_scatter_CC->SetBinError(22,12,0,3.464102);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,12,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(23,12,0,2.645751);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,12,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(24,12,0,1.732051);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,12,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(25,12,0,2.645751);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,12,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(26,12,0,1.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,12,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(27,12,0,2.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,12,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(28,12,0,2.449490);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,12,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(29,12,0,3.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,12,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(30,12,0,2.449490);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,12,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(31,12,0,2.000000);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,12,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(32,12,0,2.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,12,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(33,12,0,1.732051);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,12,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(34,12,0,2.000000);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,12,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(35,12,0,2.449490);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,12,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(36,12,0,1.732051);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,12,0,14.000000);
presel_deltaphi_scatter_CC->SetBinError(37,12,0,3.741657);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,12,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(38,12,0,2.449490);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,12,0,14.000000);
presel_deltaphi_scatter_CC->SetBinError(39,12,0,3.741657);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,12,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(40,12,0,2.449490);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,12,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(41,12,0,3.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,12,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(42,12,0,2.449490);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,12,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(43,12,0,2.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,12,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(44,12,0,2.645751);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,12,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(45,12,0,2.828427);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,12,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(46,12,0,2.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,12,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(47,12,0,2.236068);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,12,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(48,12,0,2.236068);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,12,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(49,12,0,2.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,12,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,12,0,1.000000);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,13,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,13,0,1.000000);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,13,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(2,13,0,1.414214);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,13,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(4,13,0,2.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,13,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(5,13,0,2.000000);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,13,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(6,13,0,2.449490);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,13,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(7,13,0,2.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,13,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(8,13,0,1.732051);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,13,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(9,13,0,1.732051);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,13,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(10,13,0,2.449490);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,13,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(11,13,0,2.449490);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,13,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(12,13,0,2.645751);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,13,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(13,13,0,3.162278);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,13,0,11.000000);
presel_deltaphi_scatter_CC->SetBinError(14,13,0,3.316625);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,13,0,12.000000);
presel_deltaphi_scatter_CC->SetBinError(15,13,0,3.464102);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,13,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(16,13,0,3.162278);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,13,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(17,13,0,3.162278);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,13,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(18,13,0,3.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,13,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(19,13,0,3.000000);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,13,0,13.000000);
presel_deltaphi_scatter_CC->SetBinError(20,13,0,3.605551);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,13,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(21,13,0,2.645751);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,13,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(22,13,0,2.236068);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,13,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(23,13,0,2.236068);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,13,0,11.000000);
presel_deltaphi_scatter_CC->SetBinError(24,13,0,3.316625);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,13,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,13,0,1.732051);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,13,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(26,13,0,2.645751);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,13,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,13,0,1.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,13,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(28,13,0,2.645751);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,13,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(29,13,0,2.236068);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,13,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(30,13,0,3.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,13,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(31,13,0,2.236068);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,13,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(32,13,0,2.449490);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,13,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(33,13,0,1.732051);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,13,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(34,13,0,2.449490);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,13,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(35,13,0,2.236068);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,13,0,12.000000);
presel_deltaphi_scatter_CC->SetBinError(36,13,0,3.464102);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,13,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(37,13,0,2.828427);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,13,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(38,13,0,2.828427);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,13,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(39,13,0,3.162278);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,13,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(40,13,0,2.449490);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,13,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(41,13,0,2.236068);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,13,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(42,13,0,2.449490);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,13,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(43,13,0,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,13,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,13,0,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,13,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(45,13,0,2.236068);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,13,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(46,13,0,2.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,13,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(47,13,0,2.000000);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,13,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(48,13,0,1.732051);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,14,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(2,14,0,2.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,14,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(3,14,0,1.732051);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,14,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(4,14,0,2.449490);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,14,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(5,14,0,2.449490);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,14,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(6,14,0,2.828427);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,14,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(7,14,0,2.449490);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,14,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(8,14,0,2.236068);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,14,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(9,14,0,2.236068);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,14,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(10,14,0,2.236068);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,14,0,11.000000);
presel_deltaphi_scatter_CC->SetBinError(11,14,0,3.316625);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,14,0,12.000000);
presel_deltaphi_scatter_CC->SetBinError(12,14,0,3.464102);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,14,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(13,14,0,2.645751);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,14,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(14,14,0,2.645751);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,14,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(15,14,0,2.645751);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,14,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(16,14,0,1.732051);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,14,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(17,14,0,1.414214);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,14,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(18,14,0,2.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,14,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(19,14,0,1.414214);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,14,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(20,14,0,2.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,14,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(21,14,0,2.449490);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,14,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(22,14,0,2.449490);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,14,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(23,14,0,2.236068);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,14,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(24,14,0,2.236068);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,14,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,14,0,1.732051);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,14,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(26,14,0,3.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,14,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(27,14,0,3.162278);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,14,0,12.000000);
presel_deltaphi_scatter_CC->SetBinError(28,14,0,3.464102);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,14,0,11.000000);
presel_deltaphi_scatter_CC->SetBinError(29,14,0,3.316625);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,14,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(30,14,0,2.828427);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,14,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(31,14,0,2.645751);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,14,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(32,14,0,2.236068);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,14,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(33,14,0,3.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,14,0,12.000000);
presel_deltaphi_scatter_CC->SetBinError(34,14,0,3.464102);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,14,0,14.000000);
presel_deltaphi_scatter_CC->SetBinError(35,14,0,3.741657);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,14,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(36,14,0,3.162278);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,14,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(37,14,0,2.236068);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,14,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(38,14,0,2.828427);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,14,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(39,14,0,2.000000);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,14,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(40,14,0,1.732051);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,14,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(41,14,0,1.732051);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,14,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(42,14,0,1.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,14,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(43,14,0,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,14,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(44,14,0,2.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,14,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(45,14,0,1.414214);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,14,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(46,14,0,1.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,14,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(47,14,0,1.414214);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,14,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(48,14,0,1.000000);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,15,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,15,0,1.000000);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,15,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(2,15,0,1.732051);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,15,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(3,15,0,2.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,15,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(4,15,0,2.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,15,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(5,15,0,2.645751);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,15,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(6,15,0,2.449490);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,15,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(7,15,0,3.162278);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,15,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(8,15,0,2.645751);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,15,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(9,15,0,2.828427);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,15,0,11.000000);
presel_deltaphi_scatter_CC->SetBinError(10,15,0,3.316625);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,15,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(11,15,0,2.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,15,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(12,15,0,2.645751);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,15,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(13,15,0,2.449490);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,15,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(14,15,0,2.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,15,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(15,15,0,1.732051);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,15,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(16,15,0,2.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,15,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(17,15,0,1.732051);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,15,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(18,15,0,1.414214);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,15,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(20,15,0,1.414214);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,15,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,15,0,1.000000);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,15,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(23,15,0,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,15,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(24,15,0,1.414214);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,15,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(25,15,0,2.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,15,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(26,15,0,2.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,15,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(27,15,0,2.828427);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,15,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(28,15,0,2.236068);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,15,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(29,15,0,2.645751);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,15,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(30,15,0,3.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,15,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(31,15,0,3.162278);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,15,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(32,15,0,2.645751);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,15,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(33,15,0,2.828427);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,15,0,10.000000);
presel_deltaphi_scatter_CC->SetBinError(34,15,0,3.162278);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,15,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(35,15,0,2.449490);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,15,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(36,15,0,2.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,15,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(37,15,0,2.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,15,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(38,15,0,1.732051);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,15,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(39,15,0,1.000000);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,15,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(40,15,0,1.000000);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,15,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(41,15,0,1.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,15,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(43,15,0,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,15,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(44,15,0,1.414214);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,15,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,15,0,1.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,15,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(46,15,0,1.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,15,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(47,15,0,1.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,15,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(50,15,0,1.414214);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,16,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(1,16,0,1.414214);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,16,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(2,16,0,2.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,16,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(3,16,0,2.236068);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,16,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(4,16,0,2.449490);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,16,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(5,16,0,2.449490);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,16,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(6,16,0,2.236068);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,16,0,8.000000);
presel_deltaphi_scatter_CC->SetBinError(7,16,0,2.828427);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,16,0,13.000000);
presel_deltaphi_scatter_CC->SetBinError(8,16,0,3.605551);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,16,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(9,16,0,3.000000);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,16,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(10,16,0,2.449490);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,16,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(11,16,0,2.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,16,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(12,16,0,2.000000);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,16,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(13,16,0,2.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,16,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(14,16,0,1.414214);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,16,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(16,16,0,1.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,16,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(17,16,0,1.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,16,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(18,16,0,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,16,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(24,16,0,1.414214);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,16,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,16,0,1.732051);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,16,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(26,16,0,1.414214);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,16,0,9.000000);
presel_deltaphi_scatter_CC->SetBinError(27,16,0,3.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,16,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(28,16,0,2.645751);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,16,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(29,16,0,2.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,16,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(30,16,0,1.732051);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,16,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(31,16,0,1.732051);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,16,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(32,16,0,1.732051);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,16,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(33,16,0,1.732051);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,16,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(34,16,0,1.732051);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,16,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(35,16,0,1.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,16,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,16,0,1.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,16,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(37,16,0,1.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,16,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(38,16,0,1.000000);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,16,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(40,16,0,1.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,16,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(43,16,0,1.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,16,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(49,16,0,1.000000);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,17,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,17,0,1.000000);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,17,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(2,17,0,1.732051);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,17,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(3,17,0,2.236068);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,17,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(4,17,0,2.449490);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,17,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(5,17,0,2.645751);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,17,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(6,17,0,2.236068);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,17,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(7,17,0,2.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,17,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(8,17,0,2.645751);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,17,0,6.000000);
presel_deltaphi_scatter_CC->SetBinError(9,17,0,2.449490);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,17,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(17,17,0,1.414214);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,17,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(18,17,0,1.000000);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,17,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(23,17,0,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,17,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(24,17,0,1.414214);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,17,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,17,0,1.732051);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,17,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(26,17,0,1.414214);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,17,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,17,0,1.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,17,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(28,17,0,1.414214);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,17,0,5.000000);
presel_deltaphi_scatter_CC->SetBinError(29,17,0,2.236068);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,17,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(30,17,0,1.732051);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,17,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(31,17,0,1.414214);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,17,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(32,17,0,1.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,17,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(33,17,0,1.732051);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,17,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(34,17,0,1.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,17,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,17,0,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,17,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,17,0,1.000000);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,18,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,18,0,1.000000);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,18,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(2,18,0,1.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,18,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(3,18,0,1.414214);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,18,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(4,18,0,1.414214);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,18,0,4.000000);
presel_deltaphi_scatter_CC->SetBinError(5,18,0,2.000000);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,18,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(6,18,0,1.732051);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,18,0,7.000000);
presel_deltaphi_scatter_CC->SetBinError(7,18,0,2.645751);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,18,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(25,18,0,1.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,18,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(26,18,0,1.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,18,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,18,0,1.000000);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,18,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(29,18,0,1.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,18,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(30,18,0,1.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,18,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(31,18,0,1.000000);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,18,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(35,18,0,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,19,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(3,19,0,1.732051);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,19,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(4,19,0,1.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,19,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(5,19,0,1.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,19,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(17,19,0,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,19,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,19,0,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,20,0,3.000000);
presel_deltaphi_scatter_CC->SetBinError(3,20,0,1.732051);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,20,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(4,20,0,1.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,20,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(28,20,0,1.000000);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,20,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(29,20,0,1.000000);

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,21,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(3,21,0,1.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,21,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(4,21,0,1.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,21,0,2.000000);
presel_deltaphi_scatter_CC->SetBinError(5,21,0,1.414214);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,21,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(10,21,0,1.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,21,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(25,21,0,1.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,21,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(30,21,0,1.000000);

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,24,0,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,24,0,1.000000);

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 0.250000 to 0.500000

////////////////////////////////////////////////////
// ybin: under -0.200000

////////////////////////////////////////////////////
// ybin: -0.200000 to -0.184000

////////////////////////////////////////////////////
// ybin: -0.184000 to -0.168000

////////////////////////////////////////////////////
// ybin: -0.168000 to -0.152000

////////////////////////////////////////////////////
// ybin: -0.152000 to -0.136000

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,4,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(28,4,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.136000 to -0.120000

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,5,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(38,5,1,1.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,5,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,5,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.120000 to -0.104000

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,6,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(14,6,1,1.000000);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,6,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(23,6,1,1.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,6,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(25,6,1,1.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,6,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(26,6,1,1.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,6,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,6,1,1.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,6,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(39,6,1,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,6,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,6,1,1.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,6,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(47,6,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,7,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,7,1,1.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,7,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(31,7,1,1.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,7,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,7,1,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,7,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,7,1,1.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,7,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(49,7,1,1.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,7,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(50,7,1,1.414214);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,8,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,8,1,1.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,8,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(4,8,1,1.000000);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,8,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(9,8,1,1.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,8,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(19,8,1,1.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,8,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(25,8,1,1.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,8,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(26,8,1,1.414214);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,8,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(28,8,1,1.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,8,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(34,8,1,1.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,8,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(39,8,1,1.414214);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,8,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(44,8,1,2.449490);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,8,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(45,8,1,2.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,8,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(46,8,1,2.236068);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,8,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(47,8,1,2.000000);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,8,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(48,8,1,2.645751);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,8,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,8,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,9,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(8,9,1,1.414214);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(15,9,1,1.000000);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(16,9,1,1.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,9,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(17,9,1,1.732051);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,9,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(19,9,1,1.414214);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,9,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(20,9,1,1.732051);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,9,1,1.000000);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,9,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(22,9,1,1.414214);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,9,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(23,9,1,2.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,9,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(24,9,1,1.732051);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,9,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,9,1,1.732051);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(29,9,1,1.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(30,9,1,1.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(31,9,1,1.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(33,9,1,1.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,9,1,1.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(37,9,1,1.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,9,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(39,9,1,1.414214);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(40,9,1,1.000000);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,9,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(41,9,1,1.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,9,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(42,9,1,2.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,9,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(43,9,1,2.449490);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,9,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(44,9,1,2.828427);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,9,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(45,9,1,3.605551);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,9,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(46,9,1,2.449490);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,9,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(47,9,1,2.828427);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,9,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(48,9,1,2.449490);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,9,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(49,9,1,2.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,9,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(50,9,1,2.449490);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,10,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,10,1,1.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,10,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(3,10,1,1.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,10,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(5,10,1,1.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,10,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(7,10,1,1.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,10,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(12,10,1,1.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,10,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(15,10,1,1.732051);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,10,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(16,10,1,2.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,10,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(17,10,1,1.414214);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,10,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(18,10,1,3.162278);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,10,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(19,10,1,2.449490);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,10,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(20,10,1,2.449490);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,10,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(21,10,1,1.414214);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,10,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(22,10,1,2.236068);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,10,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(23,10,1,2.236068);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,10,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(24,10,1,2.236068);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,10,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(25,10,1,2.645751);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,10,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(26,10,1,3.162278);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,10,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(27,10,1,1.732051);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,10,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(28,10,1,1.732051);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,10,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(29,10,1,1.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,10,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(31,10,1,1.000000);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,10,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(32,10,1,1.414214);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,10,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(33,10,1,1.414214);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,10,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(35,10,1,1.414214);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,10,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,10,1,1.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,10,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(37,10,1,1.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,10,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(38,10,1,2.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,10,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(39,10,1,2.000000);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,10,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(40,10,1,2.000000);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,10,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(41,10,1,2.449490);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,10,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(42,10,1,3.316625);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,10,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(43,10,1,3.162278);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,10,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(44,10,1,3.316625);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,10,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(45,10,1,3.316625);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,10,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(46,10,1,3.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,10,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(47,10,1,3.162278);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,10,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(48,10,1,3.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,10,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(49,10,1,1.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,10,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(50,10,1,2.449490);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,11,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(2,11,1,1.414214);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,11,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(3,11,1,1.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,11,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(4,11,1,1.414214);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,11,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(5,11,1,1.414214);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,11,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(6,11,1,1.414214);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,11,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(7,11,1,1.000000);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,11,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(9,11,1,1.414214);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,11,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(10,11,1,1.414214);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,11,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(11,11,1,1.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,11,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(12,11,1,1.732051);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,11,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(13,11,1,1.414214);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,11,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(14,11,1,1.732051);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,11,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(15,11,1,3.605551);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,11,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(16,11,1,2.645751);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,11,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(17,11,1,3.605551);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,11,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(18,11,1,3.464102);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,11,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(19,11,1,3.605551);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,11,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(20,11,1,3.605551);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,11,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(21,11,1,2.449490);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,11,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(22,11,1,2.828427);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,11,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(23,11,1,3.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,11,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(24,11,1,3.316625);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,11,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(25,11,1,3.162278);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,11,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(26,11,1,2.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,11,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(27,11,1,2.449490);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,11,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(28,11,1,1.414214);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,11,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(29,11,1,1.732051);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,11,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(30,11,1,2.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,11,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(31,11,1,2.645751);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,11,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(32,11,1,2.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,11,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(33,11,1,2.236068);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,11,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(34,11,1,2.236068);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,11,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(35,11,1,1.414214);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,11,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(36,11,1,2.449490);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,11,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(37,11,1,2.449490);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,11,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(38,11,1,2.236068);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,11,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(39,11,1,1.414214);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,11,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(40,11,1,2.828427);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,11,1,16.000000);
presel_deltaphi_scatter_CC->SetBinError(41,11,1,4.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,11,1,15.000000);
presel_deltaphi_scatter_CC->SetBinError(42,11,1,3.872983);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,11,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(43,11,1,3.605551);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,11,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(44,11,1,3.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,11,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(45,11,1,2.828427);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,11,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(46,11,1,2.645751);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,11,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(47,11,1,3.316625);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,11,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(48,11,1,3.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,11,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(49,11,1,1.732051);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,11,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,11,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,12,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(2,12,1,1.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,12,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(3,12,1,1.414214);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,12,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(4,12,1,1.732051);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,12,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(6,12,1,2.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,12,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(7,12,1,1.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,12,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(8,12,1,1.414214);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,12,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(9,12,1,1.000000);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,12,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(10,12,1,1.000000);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,12,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(11,12,1,2.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,12,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(12,12,1,3.464102);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,12,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(13,12,1,3.162278);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,12,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(14,12,1,2.449490);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,12,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(15,12,1,3.162278);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,12,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(16,12,1,3.316625);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,12,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(17,12,1,3.316625);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,12,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(18,12,1,3.316625);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,12,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(19,12,1,3.000000);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,12,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(20,12,1,3.464102);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,12,1,17.000000);
presel_deltaphi_scatter_CC->SetBinError(21,12,1,4.123106);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,12,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(22,12,1,3.605551);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,12,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(23,12,1,2.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,12,1,15.000000);
presel_deltaphi_scatter_CC->SetBinError(24,12,1,3.872983);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,12,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(25,12,1,3.605551);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,12,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(26,12,1,2.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,12,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(27,12,1,3.162278);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,12,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(28,12,1,2.000000);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,12,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(29,12,1,1.414214);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,12,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(30,12,1,1.414214);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,12,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(31,12,1,3.162278);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,12,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(32,12,1,2.645751);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,12,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(33,12,1,2.645751);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,12,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(34,12,1,3.000000);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,12,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(35,12,1,3.316625);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,12,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(36,12,1,3.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,12,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(37,12,1,2.449490);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,12,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(38,12,1,3.605551);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,12,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(39,12,1,3.464102);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,12,1,17.000000);
presel_deltaphi_scatter_CC->SetBinError(40,12,1,4.123106);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,12,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(41,12,1,3.605551);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,12,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(42,12,1,3.316625);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,12,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(43,12,1,3.464102);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,12,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(44,12,1,3.605551);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,12,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(45,12,1,3.162278);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,12,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(46,12,1,2.828427);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,12,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(47,12,1,2.449490);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,12,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(48,12,1,2.828427);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,12,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(49,12,1,1.414214);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,12,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,12,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,13,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(2,13,1,1.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,13,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(3,13,1,1.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,13,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(4,13,1,2.449490);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,13,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(5,13,1,2.645751);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,13,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(6,13,1,2.236068);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,13,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(7,13,1,2.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,13,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(8,13,1,2.449490);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,13,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(9,13,1,2.236068);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,13,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(10,13,1,2.449490);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,13,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(11,13,1,3.162278);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,13,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(12,13,1,3.464102);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,13,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(13,13,1,3.316625);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,13,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(14,13,1,3.316625);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,13,1,21.000000);
presel_deltaphi_scatter_CC->SetBinError(15,13,1,4.582576);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,13,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(16,13,1,3.316625);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,13,1,19.000000);
presel_deltaphi_scatter_CC->SetBinError(17,13,1,4.358899);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,13,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(18,13,1,3.464102);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,13,1,17.000000);
presel_deltaphi_scatter_CC->SetBinError(19,13,1,4.123106);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,13,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(20,13,1,2.645751);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,13,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(21,13,1,3.162278);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,13,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(22,13,1,3.000000);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,13,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(23,13,1,3.162278);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,13,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(24,13,1,3.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,13,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(25,13,1,2.236068);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,13,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(26,13,1,3.162278);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,13,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(27,13,1,2.828427);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,13,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(28,13,1,3.162278);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,13,1,14.000000);
presel_deltaphi_scatter_CC->SetBinError(29,13,1,3.741657);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,13,1,15.000000);
presel_deltaphi_scatter_CC->SetBinError(30,13,1,3.872983);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,13,1,14.000000);
presel_deltaphi_scatter_CC->SetBinError(31,13,1,3.741657);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,13,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(32,13,1,2.645751);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,13,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(33,13,1,3.316625);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,13,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(34,13,1,3.162278);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,13,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(35,13,1,3.316625);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,13,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(36,13,1,3.162278);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,13,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(37,13,1,3.605551);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,13,1,16.000000);
presel_deltaphi_scatter_CC->SetBinError(38,13,1,4.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,13,1,14.000000);
presel_deltaphi_scatter_CC->SetBinError(39,13,1,3.741657);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,13,1,16.000000);
presel_deltaphi_scatter_CC->SetBinError(40,13,1,4.000000);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,13,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(41,13,1,2.828427);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,13,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(42,13,1,2.449490);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,13,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(43,13,1,2.645751);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,13,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(44,13,1,3.316625);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,13,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(45,13,1,2.449490);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,13,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(46,13,1,2.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,13,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(47,13,1,1.732051);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,13,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(48,13,1,2.236068);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,13,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(49,13,1,1.732051);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,13,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,13,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,14,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(1,14,1,1.732051);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,14,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(2,14,1,3.162278);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,14,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(3,14,1,1.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,14,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(4,14,1,2.449490);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,14,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(5,14,1,3.000000);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,14,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(6,14,1,2.645751);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,14,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(7,14,1,2.449490);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,14,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(8,14,1,3.162278);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,14,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(9,14,1,2.828427);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,14,1,19.000000);
presel_deltaphi_scatter_CC->SetBinError(10,14,1,4.358899);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,14,1,16.000000);
presel_deltaphi_scatter_CC->SetBinError(11,14,1,4.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,14,1,15.000000);
presel_deltaphi_scatter_CC->SetBinError(12,14,1,3.872983);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,14,1,16.000000);
presel_deltaphi_scatter_CC->SetBinError(13,14,1,4.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,14,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(14,14,1,2.828427);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,14,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(15,14,1,2.828427);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,14,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(16,14,1,3.316625);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,14,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(17,14,1,2.449490);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,14,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(18,14,1,2.828427);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,14,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(19,14,1,2.645751);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,14,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(20,14,1,3.162278);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,14,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(21,14,1,2.645751);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,14,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(22,14,1,3.162278);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,14,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(23,14,1,2.449490);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,14,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(24,14,1,2.645751);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,14,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(25,14,1,2.236068);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,14,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(26,14,1,2.449490);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,14,1,19.000000);
presel_deltaphi_scatter_CC->SetBinError(27,14,1,4.358899);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,14,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(28,14,1,3.464102);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,14,1,16.000000);
presel_deltaphi_scatter_CC->SetBinError(29,14,1,4.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,14,1,14.000000);
presel_deltaphi_scatter_CC->SetBinError(30,14,1,3.741657);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,14,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(31,14,1,3.605551);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,14,1,20.000000);
presel_deltaphi_scatter_CC->SetBinError(32,14,1,4.472136);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,14,1,16.000000);
presel_deltaphi_scatter_CC->SetBinError(33,14,1,4.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,14,1,18.000000);
presel_deltaphi_scatter_CC->SetBinError(34,14,1,4.242641);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,14,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(35,14,1,3.162278);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,14,1,14.000000);
presel_deltaphi_scatter_CC->SetBinError(36,14,1,3.741657);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,14,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(37,14,1,3.605551);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,14,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(38,14,1,3.605551);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,14,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(39,14,1,3.605551);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,14,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(40,14,1,2.236068);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,14,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(41,14,1,2.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,14,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(42,14,1,1.732051);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,14,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(43,14,1,2.645751);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,14,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(44,14,1,2.236068);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,14,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(45,14,1,2.236068);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,14,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(46,14,1,1.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,14,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(47,14,1,2.000000);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,14,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(48,14,1,1.732051);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,14,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(49,14,1,2.236068);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,15,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(1,15,1,1.732051);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,15,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(2,15,1,1.414214);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,15,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(3,15,1,2.828427);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,15,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(4,15,1,2.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,15,1,15.000000);
presel_deltaphi_scatter_CC->SetBinError(5,15,1,3.872983);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,15,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(6,15,1,2.645751);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,15,1,17.000000);
presel_deltaphi_scatter_CC->SetBinError(7,15,1,4.123106);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,15,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(8,15,1,3.162278);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,15,1,14.000000);
presel_deltaphi_scatter_CC->SetBinError(9,15,1,3.741657);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,15,1,15.000000);
presel_deltaphi_scatter_CC->SetBinError(10,15,1,3.872983);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,15,1,15.000000);
presel_deltaphi_scatter_CC->SetBinError(11,15,1,3.872983);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,15,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(12,15,1,3.000000);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,15,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(13,15,1,2.449490);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,15,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(14,15,1,3.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,15,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(15,15,1,2.449490);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,15,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(16,15,1,1.732051);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,15,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(17,15,1,2.236068);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,15,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(18,15,1,2.828427);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,15,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(19,15,1,2.645751);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,15,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(20,15,1,1.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,15,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,15,1,1.000000);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,15,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(22,15,1,1.732051);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,15,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(23,15,1,2.236068);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,15,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(24,15,1,1.732051);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,15,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(25,15,1,2.645751);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,15,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(26,15,1,3.464102);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,15,1,16.000000);
presel_deltaphi_scatter_CC->SetBinError(27,15,1,4.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,15,1,15.000000);
presel_deltaphi_scatter_CC->SetBinError(28,15,1,3.872983);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,15,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(29,15,1,3.464102);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,15,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(30,15,1,3.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,15,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(31,15,1,3.316625);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,15,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(32,15,1,3.162278);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,15,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(33,15,1,3.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,15,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(34,15,1,2.828427);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,15,1,12.000000);
presel_deltaphi_scatter_CC->SetBinError(35,15,1,3.464102);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,15,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(36,15,1,2.828427);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,15,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(37,15,1,2.645751);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,15,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(38,15,1,2.828427);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,15,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(39,15,1,2.449490);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,15,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(41,15,1,1.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,15,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(42,15,1,1.732051);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,15,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(43,15,1,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,15,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(44,15,1,1.414214);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,15,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(45,15,1,2.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,15,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(46,15,1,1.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,15,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(47,15,1,1.414214);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,16,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(1,16,1,1.414214);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,16,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(2,16,1,2.236068);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,16,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(3,16,1,1.414214);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,16,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(4,16,1,2.645751);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,16,1,16.000000);
presel_deltaphi_scatter_CC->SetBinError(5,16,1,4.000000);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,16,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(6,16,1,3.605551);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,16,1,14.000000);
presel_deltaphi_scatter_CC->SetBinError(7,16,1,3.741657);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,16,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(8,16,1,3.000000);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,16,1,8.000000);
presel_deltaphi_scatter_CC->SetBinError(9,16,1,2.828427);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,16,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(10,16,1,2.645751);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,16,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(11,16,1,2.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,16,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(12,16,1,2.236068);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,16,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(13,16,1,2.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,16,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(14,16,1,1.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,16,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(15,16,1,1.414214);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,16,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(19,16,1,1.000000);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,16,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(20,16,1,2.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,16,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(21,16,1,1.414214);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,16,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(22,16,1,1.000000);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,16,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(23,16,1,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,16,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(24,16,1,1.732051);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,16,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(25,16,1,2.236068);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,16,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(26,16,1,1.414214);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,16,1,9.000000);
presel_deltaphi_scatter_CC->SetBinError(27,16,1,3.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,16,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(28,16,1,3.162278);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,16,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(29,16,1,1.732051);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,16,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(30,16,1,2.236068);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,16,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(31,16,1,1.414214);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,16,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(32,16,1,2.645751);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,16,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(33,16,1,2.449490);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,16,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(34,16,1,1.732051);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,16,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(35,16,1,1.732051);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,16,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(36,16,1,2.236068);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,16,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(37,16,1,1.732051);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,16,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(38,16,1,1.000000);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,16,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(40,16,1,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,16,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,16,1,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,16,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,16,1,1.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,16,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(50,16,1,1.414214);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,17,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(1,17,1,1.414214);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,17,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(2,17,1,1.732051);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,17,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(3,17,1,1.732051);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,17,1,11.000000);
presel_deltaphi_scatter_CC->SetBinError(4,17,1,3.316625);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,17,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(5,17,1,2.645751);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,17,1,13.000000);
presel_deltaphi_scatter_CC->SetBinError(6,17,1,3.605551);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,17,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(7,17,1,2.645751);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,17,1,10.000000);
presel_deltaphi_scatter_CC->SetBinError(8,17,1,3.162278);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,17,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(9,17,1,2.645751);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,17,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(10,17,1,1.414214);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,17,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(11,17,1,1.732051);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,17,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(14,17,1,1.414214);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,17,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(16,17,1,1.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,17,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(17,17,1,2.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,17,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(19,17,1,1.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,17,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,17,1,1.000000);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,17,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(22,17,1,1.000000);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,17,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(23,17,1,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,17,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(24,17,1,1.414214);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,17,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(25,17,1,2.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,17,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(26,17,1,2.449490);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,17,1,6.000000);
presel_deltaphi_scatter_CC->SetBinError(27,17,1,2.449490);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,17,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(28,17,1,2.236068);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,17,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(29,17,1,2.236068);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,17,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(30,17,1,1.732051);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,17,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(31,17,1,1.732051);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,17,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(33,17,1,2.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,17,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(36,17,1,1.414214);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,17,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(37,17,1,1.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,17,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(39,17,1,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,17,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,17,1,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,17,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,17,1,1.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,17,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(50,17,1,1.732051);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,18,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(1,18,1,1.732051);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,18,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(2,18,1,1.414214);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,18,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(3,18,1,1.732051);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,18,1,7.000000);
presel_deltaphi_scatter_CC->SetBinError(4,18,1,2.645751);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,18,1,5.000000);
presel_deltaphi_scatter_CC->SetBinError(5,18,1,2.236068);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,18,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(6,18,1,2.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,18,1,4.000000);
presel_deltaphi_scatter_CC->SetBinError(7,18,1,2.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(8,18,1,1.000000);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,18,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(9,18,1,1.414214);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(11,18,1,1.000000);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(13,18,1,1.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(19,18,1,1.000000);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(22,18,1,1.000000);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(23,18,1,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,18,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(24,18,1,1.414214);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,18,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(26,18,1,1.414214);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,18,1,1.000000);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(29,18,1,1.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(30,18,1,1.000000);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(48,18,1,1.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,18,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,18,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,19,1,3.000000);
presel_deltaphi_scatter_CC->SetBinError(3,19,1,1.732051);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,19,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(4,19,1,1.414214);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,19,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(5,19,1,1.414214);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,19,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(10,19,1,1.000000);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,19,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(20,19,1,1.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,19,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(28,19,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,20,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,20,1,1.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,20,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(5,20,1,1.000000);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,20,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(29,20,1,1.000000);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,20,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(35,20,1,1.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,20,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,20,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,21,1,2.000000);
presel_deltaphi_scatter_CC->SetBinError(32,21,1,1.414214);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,21,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(40,21,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,22,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(8,22,1,1.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,22,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(30,22,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,23,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(8,23,1,1.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,23,1,1.000000);
presel_deltaphi_scatter_CC->SetBinError(30,23,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 0.500000 to 0.750000

////////////////////////////////////////////////////
// ybin: under -0.200000

////////////////////////////////////////////////////
// ybin: -0.200000 to -0.184000

////////////////////////////////////////////////////
// ybin: -0.184000 to -0.168000

////////////////////////////////////////////////////
// ybin: -0.168000 to -0.152000

////////////////////////////////////////////////////
// ybin: -0.152000 to -0.136000

////////////////////////////////////////////////////
// ybin: -0.136000 to -0.120000

////////////////////////////////////////////////////
// ybin: -0.120000 to -0.104000

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,6,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(19,6,2,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,6,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,6,2,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,7,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(26,7,2,1.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,7,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(34,7,2,1.000000);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,7,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(48,7,2,1.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,7,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(49,7,2,1.000000);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,8,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(15,8,2,1.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,8,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(17,8,2,1.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,8,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,8,2,1.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,8,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(33,8,2,1.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,8,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(38,8,2,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,8,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,8,2,1.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,8,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(46,8,2,1.732051);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,8,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(47,8,2,1.414214);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,8,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(48,8,2,1.732051);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,9,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(1,9,2,1.414214);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,9,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(17,9,2,1.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,9,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(18,9,2,1.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,9,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,9,2,1.000000);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,9,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(23,9,2,1.414214);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,9,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(24,9,2,1.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,9,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(26,9,2,1.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,9,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(27,9,2,1.414214);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,9,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(29,9,2,1.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,9,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(30,9,2,1.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,9,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(34,9,2,1.000000);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,9,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(41,9,2,1.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,9,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(42,9,2,1.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,9,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(43,9,2,2.236068);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,9,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(44,9,2,1.732051);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,9,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(45,9,2,1.732051);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,9,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(46,9,2,2.236068);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,9,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(47,9,2,2.449490);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,9,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(48,9,2,2.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,9,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(49,9,2,2.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,9,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(50,9,2,1.414214);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,10,2,1.000000);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,10,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(2,10,2,1.414214);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(5,10,2,1.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(8,10,2,1.000000);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(10,10,2,1.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(14,10,2,1.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,10,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(15,10,2,1.732051);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(16,10,2,1.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,10,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(17,10,2,1.732051);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,10,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(18,10,2,2.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,10,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(19,10,2,1.414214);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,10,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(20,10,2,2.449490);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,10,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(21,10,2,2.449490);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,10,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(22,10,2,2.000000);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,10,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(23,10,2,2.236068);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,10,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(24,10,2,1.414214);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,10,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(25,10,2,1.414214);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(28,10,2,1.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(30,10,2,1.000000);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(32,10,2,1.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(33,10,2,1.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(37,10,2,1.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,10,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(38,10,2,2.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,10,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(39,10,2,1.414214);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,10,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(40,10,2,1.414214);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,10,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(41,10,2,2.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,10,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(42,10,2,1.732051);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,10,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(43,10,2,3.162278);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,10,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(44,10,2,2.645751);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,10,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(45,10,2,1.414214);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,10,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(46,10,2,2.236068);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,10,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(47,10,2,2.236068);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,10,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(48,10,2,1.732051);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(49,10,2,1.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,10,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,10,2,1.000000);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,11,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,11,2,1.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,11,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(3,11,2,1.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,11,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(4,11,2,1.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,11,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(5,11,2,1.000000);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,11,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(6,11,2,1.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,11,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(7,11,2,1.000000);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,11,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(11,11,2,1.732051);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,11,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(12,11,2,1.000000);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,11,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(13,11,2,1.414214);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,11,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(14,11,2,1.732051);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,11,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(15,11,2,1.000000);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,11,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(16,11,2,2.645751);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,11,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(17,11,2,2.645751);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,11,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(18,11,2,2.236068);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,11,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(19,11,2,2.236068);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,11,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(20,11,2,2.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,11,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(21,11,2,3.000000);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,11,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(22,11,2,2.449490);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,11,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(23,11,2,2.645751);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,11,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(24,11,2,2.645751);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,11,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(25,11,2,2.236068);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,11,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(26,11,2,2.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,11,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(27,11,2,1.732051);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,11,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(28,11,2,1.414214);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,11,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(30,11,2,1.414214);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,11,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(31,11,2,1.414214);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,11,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(32,11,2,2.645751);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,11,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(33,11,2,1.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,11,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(34,11,2,1.414214);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,11,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(35,11,2,2.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,11,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(36,11,2,2.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,11,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(37,11,2,2.449490);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,11,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(38,11,2,1.732051);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,11,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(39,11,2,2.645751);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,11,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(40,11,2,2.449490);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,11,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(41,11,2,1.414214);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,11,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(42,11,2,1.732051);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,11,2,12.000000);
presel_deltaphi_scatter_CC->SetBinError(43,11,2,3.464102);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,11,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(44,11,2,2.828427);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,11,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(45,11,2,2.236068);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,11,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(46,11,2,2.645751);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,11,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(47,11,2,2.236068);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,11,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(48,11,2,3.316625);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,11,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(49,11,2,2.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,11,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(50,11,2,1.414214);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,12,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(2,12,2,1.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,12,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(4,12,2,1.414214);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,12,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(5,12,2,1.732051);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,12,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(7,12,2,2.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,12,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(8,12,2,1.732051);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,12,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(9,12,2,1.414214);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,12,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(11,12,2,1.732051);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,12,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(12,12,2,2.828427);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,12,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(13,12,2,3.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,12,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(14,12,2,2.236068);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,12,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(15,12,2,3.162278);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,12,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(16,12,2,2.449490);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,12,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(17,12,2,2.645751);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,12,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(18,12,2,3.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,12,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(19,12,2,2.000000);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,12,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(20,12,2,2.449490);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,12,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(21,12,2,2.645751);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,12,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(22,12,2,2.449490);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,12,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(23,12,2,3.316625);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,12,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(24,12,2,3.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,12,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,12,2,1.732051);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,12,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(26,12,2,2.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,12,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(27,12,2,1.414214);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,12,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(28,12,2,1.732051);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,12,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(29,12,2,2.645751);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,12,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(30,12,2,2.236068);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,12,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(31,12,2,2.000000);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,12,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(32,12,2,1.732051);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,12,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(33,12,2,3.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,12,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(34,12,2,2.236068);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,12,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(35,12,2,2.236068);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,12,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(36,12,2,2.236068);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,12,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(37,12,2,3.162278);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,12,2,12.000000);
presel_deltaphi_scatter_CC->SetBinError(38,12,2,3.464102);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,12,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(39,12,2,2.000000);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,12,2,17.000000);
presel_deltaphi_scatter_CC->SetBinError(40,12,2,4.123106);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,12,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(41,12,2,3.162278);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,12,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(42,12,2,2.645751);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,12,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(43,12,2,2.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,12,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(44,12,2,2.449490);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,12,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(45,12,2,2.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,12,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(46,12,2,1.414214);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,12,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(47,12,2,2.236068);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,12,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(48,12,2,3.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,12,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(49,12,2,1.000000);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,13,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(1,13,2,1.414214);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,13,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(2,13,2,1.732051);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,13,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(3,13,2,2.236068);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,13,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(4,13,2,2.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,13,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(5,13,2,2.000000);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,13,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(6,13,2,2.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,13,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(7,13,2,2.236068);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,13,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(8,13,2,2.449490);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,13,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(9,13,2,1.732051);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,13,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(10,13,2,3.000000);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,13,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(11,13,2,3.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,13,2,14.000000);
presel_deltaphi_scatter_CC->SetBinError(12,13,2,3.741657);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,13,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(13,13,2,2.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,13,2,13.000000);
presel_deltaphi_scatter_CC->SetBinError(14,13,2,3.605551);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,13,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(15,13,2,3.162278);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,13,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(16,13,2,3.316625);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,13,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(17,13,2,3.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,13,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(18,13,2,3.316625);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,13,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(19,13,2,2.236068);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,13,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(20,13,2,2.645751);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,13,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(21,13,2,3.316625);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,13,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(22,13,2,3.162278);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,13,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(23,13,2,1.414214);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,13,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(24,13,2,1.732051);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,13,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(25,13,2,2.449490);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,13,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(26,13,2,2.828427);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,13,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(27,13,2,2.236068);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,13,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(28,13,2,2.645751);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,13,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(29,13,2,2.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,13,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(30,13,2,3.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,13,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(31,13,2,2.236068);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,13,2,13.000000);
presel_deltaphi_scatter_CC->SetBinError(32,13,2,3.605551);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,13,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(33,13,2,3.316625);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,13,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(34,13,2,2.828427);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,13,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(35,13,2,3.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,13,2,19.000000);
presel_deltaphi_scatter_CC->SetBinError(36,13,2,4.358899);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,13,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(37,13,2,3.316625);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,13,2,12.000000);
presel_deltaphi_scatter_CC->SetBinError(38,13,2,3.464102);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,13,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(39,13,2,2.000000);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,13,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(40,13,2,2.645751);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,13,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(41,13,2,3.162278);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,13,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(42,13,2,2.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,13,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(43,13,2,2.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,13,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(44,13,2,2.645751);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,13,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(45,13,2,2.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,13,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(46,13,2,2.449490);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,13,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(47,13,2,2.236068);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,13,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(48,13,2,1.732051);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,13,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(49,13,2,1.414214);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,14,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(1,14,2,2.236068);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,14,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(2,14,2,2.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,14,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(3,14,2,2.828427);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,14,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(4,14,2,3.162278);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,14,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(5,14,2,2.449490);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,14,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(6,14,2,3.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,14,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(7,14,2,2.828427);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,14,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(8,14,2,2.236068);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,14,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(9,14,2,2.449490);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,14,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(10,14,2,3.000000);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,14,2,13.000000);
presel_deltaphi_scatter_CC->SetBinError(11,14,2,3.605551);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,14,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(12,14,2,2.645751);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,14,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(13,14,2,2.645751);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,14,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(14,14,2,2.645751);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,14,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(15,14,2,3.000000);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,14,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(16,14,2,2.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,14,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(17,14,2,2.449490);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,14,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(18,14,2,3.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,14,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(19,14,2,2.236068);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,14,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(20,14,2,2.449490);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,14,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(21,14,2,2.645751);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,14,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(22,14,2,2.645751);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,14,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(23,14,2,2.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,14,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(24,14,2,2.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,14,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,14,2,1.732051);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,14,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(26,14,2,2.449490);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,14,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(27,14,2,2.828427);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,14,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(28,14,2,2.645751);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,14,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(29,14,2,3.316625);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,14,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(30,14,2,2.828427);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,14,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(31,14,2,3.162278);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,14,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(32,14,2,3.316625);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,14,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(33,14,2,2.449490);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,14,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(34,14,2,3.162278);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,14,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(35,14,2,2.645751);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,14,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(36,14,2,3.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,14,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(37,14,2,2.449490);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,14,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(38,14,2,2.645751);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,14,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(39,14,2,3.316625);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,14,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(40,14,2,2.236068);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,14,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(41,14,2,2.236068);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,14,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(42,14,2,1.414214);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,14,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(43,14,2,1.732051);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,14,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(44,14,2,1.732051);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,14,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,14,2,1.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,14,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(46,14,2,2.236068);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,14,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(47,14,2,2.236068);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,14,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(48,14,2,1.414214);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,14,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(49,14,2,1.414214);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,14,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(50,14,2,1.732051);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,15,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(1,15,2,1.414214);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,15,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(2,15,2,1.732051);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,15,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(3,15,2,3.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,15,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(4,15,2,2.236068);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,15,2,13.000000);
presel_deltaphi_scatter_CC->SetBinError(5,15,2,3.605551);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,15,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(6,15,2,3.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,15,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(7,15,2,2.236068);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,15,2,15.000000);
presel_deltaphi_scatter_CC->SetBinError(8,15,2,3.872983);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,15,2,14.000000);
presel_deltaphi_scatter_CC->SetBinError(9,15,2,3.741657);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,15,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(10,15,2,2.449490);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,15,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(11,15,2,2.449490);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,15,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(12,15,2,2.828427);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,15,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(13,15,2,2.449490);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,15,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(14,15,2,2.828427);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,15,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(15,15,2,2.000000);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,15,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(16,15,2,2.449490);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,15,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(17,15,2,3.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,15,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(18,15,2,2.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,15,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(19,15,2,2.236068);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,15,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(20,15,2,1.414214);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,15,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(21,15,2,2.645751);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,15,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(22,15,2,1.414214);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,15,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(23,15,2,1.732051);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,15,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(24,15,2,2.236068);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,15,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(25,15,2,2.449490);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,15,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(26,15,2,2.449490);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,15,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(27,15,2,2.828427);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,15,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(28,15,2,2.236068);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,15,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(29,15,2,2.449490);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,15,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(30,15,2,3.162278);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,15,2,10.000000);
presel_deltaphi_scatter_CC->SetBinError(31,15,2,3.162278);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,15,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(32,15,2,2.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,15,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(33,15,2,2.449490);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,15,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(34,15,2,2.000000);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,15,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(35,15,2,2.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,15,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(36,15,2,2.828427);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,15,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(37,15,2,1.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,15,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(38,15,2,1.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,15,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(39,15,2,1.414214);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,15,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(40,15,2,1.732051);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,15,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(41,15,2,1.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,15,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(42,15,2,1.414214);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,15,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(43,15,2,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,15,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,15,2,1.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,15,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(46,15,2,1.414214);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,15,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(47,15,2,1.414214);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,15,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,15,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,16,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(1,16,2,1.732051);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,16,2,8.000000);
presel_deltaphi_scatter_CC->SetBinError(2,16,2,2.828427);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,16,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(3,16,2,2.236068);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,16,2,11.000000);
presel_deltaphi_scatter_CC->SetBinError(4,16,2,3.316625);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,16,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(5,16,2,2.236068);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,16,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(6,16,2,2.236068);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,16,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(7,16,2,2.449490);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,16,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(8,16,2,2.645751);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,16,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(9,16,2,3.000000);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,16,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(10,16,2,2.645751);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,16,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(11,16,2,1.414214);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,16,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(12,16,2,1.000000);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,16,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(13,16,2,1.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,16,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(14,16,2,1.414214);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,16,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(15,16,2,1.732051);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,16,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(16,16,2,2.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,16,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(17,16,2,1.414214);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,16,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(22,16,2,1.414214);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,16,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(23,16,2,1.414214);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,16,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(24,16,2,1.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,16,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,16,2,1.732051);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,16,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(26,16,2,1.732051);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,16,2,7.000000);
presel_deltaphi_scatter_CC->SetBinError(27,16,2,2.645751);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,16,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(28,16,2,1.732051);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,16,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(29,16,2,1.732051);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,16,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(30,16,2,1.732051);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,16,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(31,16,2,2.000000);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,16,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(32,16,2,1.414214);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,16,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(33,16,2,2.236068);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,16,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(34,16,2,1.414214);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,16,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(35,16,2,1.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,16,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(36,16,2,2.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,16,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(37,16,2,2.236068);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,16,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(38,16,2,1.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,16,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(39,16,2,1.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,16,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(42,16,2,1.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,16,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(46,16,2,1.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,16,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(47,16,2,1.414214);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,17,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(1,17,2,1.732051);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,17,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(2,17,2,2.236068);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,17,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(3,17,2,2.236068);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,17,2,5.000000);
presel_deltaphi_scatter_CC->SetBinError(4,17,2,2.236068);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,17,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(5,17,2,1.732051);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,17,2,9.000000);
presel_deltaphi_scatter_CC->SetBinError(6,17,2,3.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,17,2,6.000000);
presel_deltaphi_scatter_CC->SetBinError(7,17,2,2.449490);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,17,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(8,17,2,1.732051);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,17,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(9,17,2,2.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(12,17,2,1.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(14,17,2,1.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(15,17,2,1.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,17,2,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,17,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(24,17,2,1.732051);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(25,17,2,1.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,17,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(26,17,2,1.414214);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,17,2,1.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,17,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(28,17,2,1.414214);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,17,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(29,17,2,1.732051);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,17,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(30,17,2,1.414214);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(31,17,2,1.000000);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,17,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(32,17,2,1.732051);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(35,17,2,1.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,17,2,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,17,2,1.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(46,17,2,1.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,17,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,17,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,18,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(3,18,2,2.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,18,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(4,18,2,1.732051);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,18,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(5,18,2,1.414214);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,18,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(6,18,2,1.732051);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,18,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(7,18,2,1.732051);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,18,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(9,18,2,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,18,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(24,18,2,1.414214);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,18,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(26,18,2,1.414214);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,18,2,3.000000);
presel_deltaphi_scatter_CC->SetBinError(29,18,2,1.732051);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,18,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(31,18,2,1.000000);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,18,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(40,18,2,1.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,18,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(49,18,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,19,2,4.000000);
presel_deltaphi_scatter_CC->SetBinError(3,19,2,2.000000);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,19,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(4,19,2,1.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,19,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(5,19,2,1.000000);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,19,2,2.000000);
presel_deltaphi_scatter_CC->SetBinError(6,19,2,1.414214);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,19,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(8,19,2,1.000000);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,19,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(16,19,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,20,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(6,20,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,21,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(17,21,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,22,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(25,22,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,25,2,1.000000);
presel_deltaphi_scatter_CC->SetBinError(26,25,2,1.000000);

////////////////////////////////////////////////////
// ybin: over 0.200000

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: over 0.750000

////////////////////////////////////////////////////
// ybin: under -0.200000

////////////////////////////////////////////////////
// ybin: -0.200000 to -0.184000

////////////////////////////////////////////////////
// ybin: -0.184000 to -0.168000

////////////////////////////////////////////////////
// ybin: -0.168000 to -0.152000

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,3,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(49,3,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.152000 to -0.136000

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,4,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(11,4,3,1.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,4,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(42,4,3,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,4,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,4,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.136000 to -0.120000

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,5,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(35,5,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.120000 to -0.104000

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,6,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(18,6,3,1.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,6,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(26,6,3,1.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,6,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,6,3,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,6,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,6,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,7,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(16,7,3,1.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,7,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(18,7,3,1.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,7,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(19,7,3,1.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,7,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,7,3,1.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,7,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(26,7,3,1.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,7,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(43,7,3,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,7,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(44,7,3,1.414214);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,7,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(48,7,3,1.414214);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,7,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(50,7,3,1.414214);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(6,8,3,1.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(7,8,3,1.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(8,8,3,1.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(18,8,3,1.000000);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(19,8,3,1.000000);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,8,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(20,8,3,1.414214);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(22,8,3,1.000000);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(23,8,3,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(24,8,3,1.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(25,8,3,1.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,8,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(26,8,3,2.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,8,3,1.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(28,8,3,1.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(33,8,3,1.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(36,8,3,1.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(39,8,3,1.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(42,8,3,1.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,8,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(46,8,3,1.414214);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(47,8,3,1.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,8,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(49,8,3,1.732051);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,8,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,8,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,9,3,1.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(3,9,3,1.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,9,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(5,9,3,1.732051);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,9,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(6,9,3,1.414214);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(12,9,3,1.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,9,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(15,9,3,1.414214);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(16,9,3,1.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(18,9,3,1.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,9,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(21,9,3,1.414214);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,9,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(22,9,3,1.732051);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,9,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(23,9,3,2.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,9,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(24,9,3,1.414214);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,9,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,9,3,1.732051);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,9,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(26,9,3,2.828427);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,9,3,1.000000);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(32,9,3,1.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(34,9,3,1.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(37,9,3,1.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(38,9,3,1.000000);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(40,9,3,1.000000);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,9,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(41,9,3,1.732051);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,9,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(42,9,3,1.732051);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,9,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(43,9,3,2.449490);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,9,3,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,9,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(45,9,3,2.645751);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,9,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(46,9,3,2.449490);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,9,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(47,9,3,2.236068);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,9,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(48,9,3,1.732051);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,9,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(49,9,3,1.732051);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,9,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(50,9,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,10,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(1,10,3,2.449490);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(2,10,3,1.414214);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(3,10,3,1.414214);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,10,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(4,10,3,2.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,10,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(5,10,3,1.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,10,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(8,10,3,1.000000);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(9,10,3,1.414214);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,10,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(10,10,3,1.000000);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,10,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(11,10,3,2.236068);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(12,10,3,1.414214);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,10,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(13,10,3,1.732051);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,10,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(14,10,3,1.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,10,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(15,10,3,1.000000);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(16,10,3,1.414214);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,10,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(17,10,3,2.449490);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,10,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(18,10,3,2.236068);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(19,10,3,1.414214);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,10,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(20,10,3,1.732051);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,10,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(21,10,3,2.236068);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,10,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(22,10,3,1.732051);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,10,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(23,10,3,2.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,10,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(24,10,3,1.732051);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,10,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(25,10,3,1.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,10,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(26,10,3,2.236068);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(27,10,3,1.414214);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,10,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(28,10,3,1.732051);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(29,10,3,1.414214);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,10,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(31,10,3,1.000000);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(32,10,3,1.414214);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(33,10,3,1.414214);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(34,10,3,1.414214);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,10,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(35,10,3,2.236068);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,10,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(36,10,3,2.000000);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,10,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(37,10,3,1.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,10,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(38,10,3,1.732051);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,10,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(39,10,3,2.000000);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,10,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(40,10,3,2.645751);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,10,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(41,10,3,1.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,10,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(42,10,3,3.162278);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,10,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(43,10,3,3.316625);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,10,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(44,10,3,3.162278);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,10,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(45,10,3,3.316625);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,10,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(46,10,3,3.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,10,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(47,10,3,2.828427);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(48,10,3,1.414214);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,10,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(49,10,3,1.732051);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,10,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(50,10,3,1.414214);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,11,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(1,11,3,1.732051);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,11,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(2,11,3,2.236068);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,11,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(3,11,3,1.414214);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,11,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(5,11,3,2.236068);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,11,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(6,11,3,1.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,11,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(7,11,3,1.414214);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,11,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(8,11,3,1.000000);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,11,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(9,11,3,1.732051);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,11,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(10,11,3,1.732051);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,11,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(11,11,3,2.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,11,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(12,11,3,1.414214);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,11,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(13,11,3,2.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,11,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(14,11,3,2.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,11,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(15,11,3,2.449490);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,11,3,13.000000);
presel_deltaphi_scatter_CC->SetBinError(16,11,3,3.605551);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,11,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(17,11,3,3.162278);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,11,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(18,11,3,2.828427);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,11,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(19,11,3,3.162278);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,11,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(20,11,3,2.449490);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,11,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(21,11,3,2.645751);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,11,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(22,11,3,1.414214);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,11,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(23,11,3,2.449490);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,11,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(24,11,3,3.464102);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,11,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(25,11,3,3.316625);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,11,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(26,11,3,1.732051);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,11,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(27,11,3,2.645751);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,11,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(28,11,3,2.449490);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,11,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(29,11,3,2.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,11,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(30,11,3,2.236068);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,11,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(31,11,3,1.732051);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,11,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(32,11,3,2.449490);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,11,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(33,11,3,2.236068);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,11,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(34,11,3,2.449490);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,11,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(35,11,3,2.449490);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,11,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(36,11,3,2.828427);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,11,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(37,11,3,2.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,11,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(38,11,3,2.236068);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,11,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(39,11,3,3.162278);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,11,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(40,11,3,3.464102);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,11,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(41,11,3,3.316625);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,11,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(42,11,3,3.464102);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,11,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(43,11,3,3.464102);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,11,3,15.000000);
presel_deltaphi_scatter_CC->SetBinError(44,11,3,3.872983);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,11,3,15.000000);
presel_deltaphi_scatter_CC->SetBinError(45,11,3,3.872983);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,11,3,17.000000);
presel_deltaphi_scatter_CC->SetBinError(46,11,3,4.123106);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,11,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(47,11,3,2.449490);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,11,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(48,11,3,3.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,11,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(49,11,3,2.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,11,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(50,11,3,2.828427);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,12,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(1,12,3,2.828427);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,12,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(2,12,3,1.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,12,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(3,12,3,2.236068);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,12,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(4,12,3,2.000000);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,12,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(5,12,3,2.236068);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,12,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(6,12,3,2.645751);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,12,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(7,12,3,2.449490);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,12,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(8,12,3,1.732051);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,12,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(9,12,3,3.000000);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,12,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(10,12,3,3.000000);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,12,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(11,12,3,2.828427);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,12,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(12,12,3,2.449490);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,12,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(13,12,3,1.732051);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,12,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(14,12,3,3.741657);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,12,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(15,12,3,3.741657);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,12,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(16,12,3,3.162278);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,12,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(17,12,3,3.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,12,3,13.000000);
presel_deltaphi_scatter_CC->SetBinError(18,12,3,3.605551);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,12,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(19,12,3,2.828427);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,12,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(20,12,3,1.732051);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,12,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(21,12,3,3.741657);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,12,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(22,12,3,3.162278);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,12,3,15.000000);
presel_deltaphi_scatter_CC->SetBinError(23,12,3,3.872983);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,12,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(24,12,3,2.645751);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,12,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(25,12,3,3.316625);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,12,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(26,12,3,2.828427);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,12,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(27,12,3,2.236068);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,12,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(28,12,3,2.645751);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,12,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(29,12,3,2.449490);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,12,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(30,12,3,2.828427);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,12,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(31,12,3,3.162278);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,12,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(32,12,3,2.449490);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,12,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(33,12,3,2.645751);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,12,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(34,12,3,3.316625);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,12,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(35,12,3,3.464102);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,12,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(36,12,3,3.464102);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,12,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(37,12,3,3.741657);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,12,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(38,12,3,2.828427);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,12,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(39,12,3,3.316625);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,12,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(40,12,3,3.316625);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,12,3,13.000000);
presel_deltaphi_scatter_CC->SetBinError(41,12,3,3.605551);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,12,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(42,12,3,3.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,12,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(43,12,3,3.162278);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,12,3,13.000000);
presel_deltaphi_scatter_CC->SetBinError(44,12,3,3.605551);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,12,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(45,12,3,3.162278);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,12,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(46,12,3,2.645751);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,12,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(47,12,3,1.000000);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,12,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(48,12,3,1.732051);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,12,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(49,12,3,3.162278);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,12,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(50,12,3,2.236068);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,13,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,13,3,1.000000);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,13,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(2,13,3,2.645751);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,13,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(3,13,3,2.449490);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,13,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(4,13,3,3.464102);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,13,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(5,13,3,2.645751);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,13,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(6,13,3,3.000000);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,13,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(7,13,3,3.741657);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,13,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(8,13,3,2.828427);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,13,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(9,13,3,2.449490);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,13,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(10,13,3,3.464102);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,13,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(11,13,3,3.316625);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,13,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(12,13,3,2.236068);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,13,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(13,13,3,2.645751);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,13,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(14,13,3,3.464102);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,13,3,18.000000);
presel_deltaphi_scatter_CC->SetBinError(15,13,3,4.242641);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,13,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(16,13,3,3.741657);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,13,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(17,13,3,3.741657);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,13,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(18,13,3,2.449490);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,13,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(19,13,3,3.000000);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,13,3,18.000000);
presel_deltaphi_scatter_CC->SetBinError(20,13,3,4.242641);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,13,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(21,13,3,2.645751);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,13,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(22,13,3,2.645751);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,13,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(23,13,3,2.828427);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,13,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(24,13,3,3.162278);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,13,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(25,13,3,2.449490);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,13,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(26,13,3,2.645751);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,13,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(27,13,3,3.162278);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,13,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(28,13,3,2.828427);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,13,3,13.000000);
presel_deltaphi_scatter_CC->SetBinError(29,13,3,3.605551);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,13,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(30,13,3,3.316625);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,13,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(31,13,3,3.741657);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,13,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(32,13,3,3.162278);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,13,3,17.000000);
presel_deltaphi_scatter_CC->SetBinError(33,13,3,4.123106);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,13,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(34,13,3,3.316625);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,13,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(35,13,3,3.000000);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,13,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(36,13,3,3.464102);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,13,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(37,13,3,3.464102);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,13,3,16.000000);
presel_deltaphi_scatter_CC->SetBinError(38,13,3,4.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,13,3,17.000000);
presel_deltaphi_scatter_CC->SetBinError(39,13,3,4.123106);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,13,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(40,13,3,3.741657);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,13,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(41,13,3,3.464102);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,13,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(42,13,3,3.316625);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,13,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(43,13,3,3.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,13,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(44,13,3,2.828427);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,13,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(45,13,3,3.464102);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,13,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(46,13,3,2.828427);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,13,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(47,13,3,2.828427);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,13,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(48,13,3,3.162278);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,13,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(49,13,3,2.236068);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,13,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(50,13,3,2.236068);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,14,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(1,14,3,2.236068);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,14,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(2,14,3,2.236068);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,14,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(3,14,3,2.828427);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,14,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(4,14,3,3.316625);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,14,3,19.000000);
presel_deltaphi_scatter_CC->SetBinError(5,14,3,4.358899);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,14,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(6,14,3,2.828427);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,14,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(7,14,3,2.828427);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,14,3,13.000000);
presel_deltaphi_scatter_CC->SetBinError(8,14,3,3.605551);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,14,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(9,14,3,3.000000);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,14,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(10,14,3,2.449490);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,14,3,17.000000);
presel_deltaphi_scatter_CC->SetBinError(11,14,3,4.123106);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,14,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(12,14,3,3.162278);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,14,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(13,14,3,2.828427);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,14,3,13.000000);
presel_deltaphi_scatter_CC->SetBinError(14,14,3,3.605551);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,14,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(15,14,3,3.162278);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,14,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(16,14,3,3.316625);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,14,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(17,14,3,3.741657);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,14,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(18,14,3,2.828427);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,14,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(19,14,3,3.464102);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,14,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(20,14,3,3.316625);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,14,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(21,14,3,3.000000);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,14,3,13.000000);
presel_deltaphi_scatter_CC->SetBinError(22,14,3,3.605551);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,14,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(23,14,3,3.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,14,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(24,14,3,2.828427);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,14,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(25,14,3,2.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,14,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(26,14,3,2.449490);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,14,3,17.000000);
presel_deltaphi_scatter_CC->SetBinError(27,14,3,4.123106);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,14,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(28,14,3,3.316625);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,14,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(29,14,3,3.000000);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,14,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(30,14,3,3.316625);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,14,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(31,14,3,2.645751);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,14,3,17.000000);
presel_deltaphi_scatter_CC->SetBinError(32,14,3,4.123106);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,14,3,19.000000);
presel_deltaphi_scatter_CC->SetBinError(33,14,3,4.358899);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,14,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(34,14,3,3.000000);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,14,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(35,14,3,3.162278);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,14,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(36,14,3,3.162278);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,14,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(37,14,3,2.449490);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,14,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(38,14,3,3.316625);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,14,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(39,14,3,2.828427);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,14,3,14.000000);
presel_deltaphi_scatter_CC->SetBinError(40,14,3,3.741657);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,14,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(41,14,3,3.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,14,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(42,14,3,1.414214);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,14,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(43,14,3,2.449490);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,14,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(44,14,3,3.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,14,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(45,14,3,1.414214);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,14,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(46,14,3,1.732051);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,14,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(47,14,3,2.828427);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,14,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(48,14,3,3.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,14,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(49,14,3,1.414214);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,14,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(50,14,3,2.000000);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,15,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(1,15,3,2.645751);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,15,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(2,15,3,2.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,15,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(3,15,3,2.828427);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,15,3,20.000000);
presel_deltaphi_scatter_CC->SetBinError(4,15,3,4.472136);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,15,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(5,15,3,3.000000);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,15,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(6,15,3,2.449490);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,15,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(7,15,3,3.464102);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,15,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(8,15,3,3.000000);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,15,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(9,15,3,2.645751);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,15,3,13.000000);
presel_deltaphi_scatter_CC->SetBinError(10,15,3,3.605551);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,15,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(11,15,3,1.732051);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,15,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(12,15,3,3.162278);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,15,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(13,15,3,2.828427);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,15,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(14,15,3,2.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,15,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(15,15,3,2.236068);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,15,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(16,15,3,2.449490);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,15,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(17,15,3,3.162278);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,15,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(18,15,3,1.732051);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,15,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(19,15,3,3.000000);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,15,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(20,15,3,2.449490);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,15,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(21,15,3,1.732051);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,15,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(22,15,3,2.236068);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,15,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(23,15,3,3.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,15,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(24,15,3,1.732051);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,15,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(25,15,3,2.645751);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,15,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(26,15,3,2.449490);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,15,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(27,15,3,3.316625);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,15,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(28,15,3,2.645751);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,15,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(29,15,3,3.316625);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,15,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(30,15,3,3.162278);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,15,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(31,15,3,3.000000);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,15,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(32,15,3,3.162278);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,15,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(33,15,3,2.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,15,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(34,15,3,3.464102);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,15,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(35,15,3,2.645751);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,15,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(36,15,3,2.449490);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,15,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(37,15,3,2.828427);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,15,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(38,15,3,3.162278);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,15,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(39,15,3,3.162278);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,15,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(40,15,3,2.828427);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,15,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(41,15,3,2.000000);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,15,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(42,15,3,1.732051);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,15,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(43,15,3,1.414214);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,15,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(44,15,3,1.732051);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,15,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(45,15,3,2.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,15,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(46,15,3,2.000000);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,15,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(47,15,3,2.236068);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,15,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(48,15,3,1.414214);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,15,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(49,15,3,1.732051);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,15,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(50,15,3,1.732051);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,16,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(1,16,3,2.000000);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,16,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(2,16,3,2.449490);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,16,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(3,16,3,2.236068);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,16,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(4,16,3,2.645751);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,16,3,11.000000);
presel_deltaphi_scatter_CC->SetBinError(5,16,3,3.316625);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,16,3,12.000000);
presel_deltaphi_scatter_CC->SetBinError(6,16,3,3.464102);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,16,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(7,16,3,3.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,16,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(8,16,3,2.236068);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,16,3,10.000000);
presel_deltaphi_scatter_CC->SetBinError(9,16,3,3.162278);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,16,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(10,16,3,2.645751);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,16,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(11,16,3,2.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,16,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(12,16,3,2.449490);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,16,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(13,16,3,2.449490);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,16,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(14,16,3,2.236068);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,16,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(15,16,3,2.000000);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,16,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(16,16,3,2.449490);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,16,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(17,16,3,1.414214);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,16,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(18,16,3,2.236068);

// xbin: 0.360000 to 0.380000
presel_deltaphi_scatter_CC->SetBinContent(19,16,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(19,16,3,1.732051);

// xbin: 0.380000 to 0.400000
presel_deltaphi_scatter_CC->SetBinContent(20,16,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(20,16,3,1.414214);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,16,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,16,3,1.000000);

// xbin: 0.420000 to 0.440000
presel_deltaphi_scatter_CC->SetBinContent(22,16,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(22,16,3,1.414214);

// xbin: 0.440000 to 0.460000
presel_deltaphi_scatter_CC->SetBinContent(23,16,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(23,16,3,1.414214);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,16,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(24,16,3,2.449490);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,16,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(25,16,3,3.000000);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,16,3,9.000000);
presel_deltaphi_scatter_CC->SetBinError(26,16,3,3.000000);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,16,3,15.000000);
presel_deltaphi_scatter_CC->SetBinError(27,16,3,3.872983);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,16,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(28,16,3,2.645751);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,16,3,7.000000);
presel_deltaphi_scatter_CC->SetBinError(29,16,3,2.645751);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,16,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(30,16,3,2.449490);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,16,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(31,16,3,2.449490);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,16,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(32,16,3,2.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,16,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(33,16,3,2.000000);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,16,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(34,16,3,2.828427);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,16,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(35,16,3,1.732051);

// xbin: 0.700000 to 0.720000
presel_deltaphi_scatter_CC->SetBinContent(36,16,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(36,16,3,1.414214);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,16,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(37,16,3,2.000000);

// xbin: 0.760000 to 0.780000
presel_deltaphi_scatter_CC->SetBinContent(39,16,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(39,16,3,1.732051);

// xbin: 0.780000 to 0.800000
presel_deltaphi_scatter_CC->SetBinContent(40,16,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(40,16,3,2.000000);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,16,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(41,16,3,1.732051);

// xbin: 0.820000 to 0.840000
presel_deltaphi_scatter_CC->SetBinContent(42,16,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(42,16,3,1.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,16,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(43,16,3,1.000000);

// xbin: 0.860000 to 0.880000
presel_deltaphi_scatter_CC->SetBinContent(44,16,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(44,16,3,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,16,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,16,3,1.000000);

// xbin: 0.940000 to 0.960000
presel_deltaphi_scatter_CC->SetBinContent(48,16,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(48,16,3,1.000000);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,16,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(49,16,3,1.414214);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,16,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(50,16,3,1.414214);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(1,17,3,1.414214);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,17,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(2,17,3,1.732051);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,17,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(3,17,3,2.449490);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,17,3,5.000000);
presel_deltaphi_scatter_CC->SetBinError(4,17,3,2.236068);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(6,17,3,1.414214);

// xbin: 0.120000 to 0.140000
presel_deltaphi_scatter_CC->SetBinContent(7,17,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(7,17,3,1.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,17,3,8.000000);
presel_deltaphi_scatter_CC->SetBinError(8,17,3,2.828427);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,17,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(9,17,3,1.000000);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,17,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(11,17,3,1.732051);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(12,17,3,1.414214);

// xbin: 0.240000 to 0.260000
presel_deltaphi_scatter_CC->SetBinContent(13,17,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(13,17,3,1.000000);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,17,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(14,17,3,1.000000);

// xbin: 0.280000 to 0.300000
presel_deltaphi_scatter_CC->SetBinContent(15,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(15,17,3,1.414214);

// xbin: 0.300000 to 0.320000
presel_deltaphi_scatter_CC->SetBinContent(16,17,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(16,17,3,1.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,17,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(17,17,3,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(24,17,3,1.414214);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,17,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,17,3,1.732051);

// xbin: 0.500000 to 0.520000
presel_deltaphi_scatter_CC->SetBinContent(26,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(26,17,3,1.414214);

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,17,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(27,17,3,2.000000);

// xbin: 0.540000 to 0.560000
presel_deltaphi_scatter_CC->SetBinContent(28,17,3,4.000000);
presel_deltaphi_scatter_CC->SetBinError(28,17,3,2.000000);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(29,17,3,1.414214);

// xbin: 0.580000 to 0.600000
presel_deltaphi_scatter_CC->SetBinContent(30,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(30,17,3,1.414214);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,17,3,6.000000);
presel_deltaphi_scatter_CC->SetBinError(31,17,3,2.449490);

// xbin: 0.620000 to 0.640000
presel_deltaphi_scatter_CC->SetBinContent(32,17,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(32,17,3,1.000000);

// xbin: 0.640000 to 0.660000
presel_deltaphi_scatter_CC->SetBinContent(33,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(33,17,3,1.414214);

// xbin: 0.660000 to 0.680000
presel_deltaphi_scatter_CC->SetBinContent(34,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(34,17,3,1.414214);

// xbin: 0.680000 to 0.700000
presel_deltaphi_scatter_CC->SetBinContent(35,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(35,17,3,1.414214);

// xbin: 0.720000 to 0.740000
presel_deltaphi_scatter_CC->SetBinContent(37,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(37,17,3,1.414214);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(38,17,3,1.414214);

// xbin: 0.800000 to 0.820000
presel_deltaphi_scatter_CC->SetBinContent(41,17,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(41,17,3,1.000000);

// xbin: 0.840000 to 0.860000
presel_deltaphi_scatter_CC->SetBinContent(43,17,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(43,17,3,1.732051);

// xbin: 0.920000 to 0.940000
presel_deltaphi_scatter_CC->SetBinContent(47,17,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(47,17,3,1.414214);

// xbin: 0.960000 to 0.980000
presel_deltaphi_scatter_CC->SetBinContent(49,17,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(49,17,3,1.000000);

// xbin: 0.980000 to 1.000000
presel_deltaphi_scatter_CC->SetBinContent(50,17,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(50,17,3,1.732051);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,18,3,1.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,18,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(3,18,3,1.414214);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,18,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(4,18,3,1.414214);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(5,18,3,1.000000);

// xbin: 0.140000 to 0.160000
presel_deltaphi_scatter_CC->SetBinContent(8,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(8,18,3,1.000000);

// xbin: 0.160000 to 0.180000
presel_deltaphi_scatter_CC->SetBinContent(9,18,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(9,18,3,1.414214);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(10,18,3,1.000000);

// xbin: 0.220000 to 0.240000
presel_deltaphi_scatter_CC->SetBinContent(12,18,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(12,18,3,1.414214);

// xbin: 0.260000 to 0.280000
presel_deltaphi_scatter_CC->SetBinContent(14,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(14,18,3,1.000000);

// xbin: 0.320000 to 0.340000
presel_deltaphi_scatter_CC->SetBinContent(17,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(17,18,3,1.000000);

// xbin: 0.340000 to 0.360000
presel_deltaphi_scatter_CC->SetBinContent(18,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(18,18,3,1.000000);

// xbin: 0.400000 to 0.420000
presel_deltaphi_scatter_CC->SetBinContent(21,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(21,18,3,1.000000);

// xbin: 0.460000 to 0.480000
presel_deltaphi_scatter_CC->SetBinContent(24,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(24,18,3,1.000000);

// xbin: 0.480000 to 0.500000
presel_deltaphi_scatter_CC->SetBinContent(25,18,3,3.000000);
presel_deltaphi_scatter_CC->SetBinError(25,18,3,1.732051);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(29,18,3,1.000000);

// xbin: 0.600000 to 0.620000
presel_deltaphi_scatter_CC->SetBinContent(31,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(31,18,3,1.000000);

// xbin: 0.740000 to 0.760000
presel_deltaphi_scatter_CC->SetBinContent(38,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(38,18,3,1.000000);

// xbin: 0.880000 to 0.900000
presel_deltaphi_scatter_CC->SetBinContent(45,18,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(45,18,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,19,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,19,3,1.000000);

// xbin: 0.020000 to 0.040000
presel_deltaphi_scatter_CC->SetBinContent(2,19,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(2,19,3,1.000000);

// xbin: 0.040000 to 0.060000
presel_deltaphi_scatter_CC->SetBinContent(3,19,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(3,19,3,1.414214);

// xbin: 0.060000 to 0.080000
presel_deltaphi_scatter_CC->SetBinContent(4,19,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(4,19,3,1.414214);

// xbin: 0.080000 to 0.100000
presel_deltaphi_scatter_CC->SetBinContent(5,19,3,2.000000);
presel_deltaphi_scatter_CC->SetBinError(5,19,3,1.414214);

// xbin: 0.100000 to 0.120000
presel_deltaphi_scatter_CC->SetBinContent(6,19,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(6,19,3,1.000000);

// xbin: 0.180000 to 0.200000
presel_deltaphi_scatter_CC->SetBinContent(10,19,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(10,19,3,1.000000);

// xbin: 0.200000 to 0.220000
presel_deltaphi_scatter_CC->SetBinContent(11,19,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(11,19,3,1.000000);

// xbin: 0.560000 to 0.580000
presel_deltaphi_scatter_CC->SetBinContent(29,19,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(29,19,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,20,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,20,3,1.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,20,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(46,20,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

// xbin: 0.000000 to 0.020000
presel_deltaphi_scatter_CC->SetBinContent(1,21,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(1,21,3,1.000000);

// xbin: 0.900000 to 0.920000
presel_deltaphi_scatter_CC->SetBinContent(46,21,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(46,21,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,22,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,22,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

// xbin: 0.520000 to 0.540000
presel_deltaphi_scatter_CC->SetBinContent(27,25,3,1.000000);
presel_deltaphi_scatter_CC->SetBinError(27,25,3,1.000000);

////////////////////////////////////////////////////
// ybin: over 0.200000
}
