{
const int n_shift_pt_bins = 1;
const float shift_pt_bins[n_shift_pt_bins+1] = { 36, 43 };

const int n_shift_abseta_bins = 1;
const float shift_abseta_bins[n_shift_abseta_bins+1] = { 0.35, 0.65 };

TH2F *ptetabins = new TH2F("ptetabins","ptetabins", 
  n_shift_pt_bins, shift_pt_bins, 
  n_shift_abseta_bins, shift_abseta_bins);

const int n_em_shift_vs_phimod_ptetabin_xbins = 50;
float em_shift_vs_phimod_ptetabin_xbins[n_em_shift_vs_phimod_ptetabin_xbins+1] = {0.000000 ,0.020000 ,0.040000 ,0.060000 ,0.080000 ,0.100000 ,0.120000 ,0.140000 ,0.160000 ,0.180000 ,0.200000 ,0.220000 ,0.240000 ,0.260000 ,0.280000 ,0.300000 ,0.320000 ,0.340000 ,0.360000 ,0.380000 ,0.400000 ,0.420000 ,0.440000 ,0.460000 ,0.480000 ,0.500000 ,0.520000 ,0.540000 ,0.560000 ,0.580000 ,0.600000 ,0.620000 ,0.640000 ,0.660000 ,0.680000 ,0.700000 ,0.720000 ,0.740000 ,0.760000 ,0.780000 ,0.800000 ,0.820000 ,0.840000 ,0.860000 ,0.880000 ,0.900000 ,0.920000 ,0.940000 ,0.960000 ,0.980000 ,1.000000  };

const int n_em_shift_vs_phimod_ptetabin_ybins = 25;
float em_shift_vs_phimod_ptetabin_ybins[n_em_shift_vs_phimod_ptetabin_ybins+1] = {-0.200000 ,-0.184000 ,-0.168000 ,-0.152000 ,-0.136000 ,-0.120000 ,-0.104000 ,-0.088000 ,-0.072000 ,-0.056000 ,-0.040000 ,-0.024000 ,-0.008000 ,0.008000 ,0.024000 ,0.040000 ,0.056000 ,0.072000 ,0.088000 ,0.104000 ,0.120000 ,0.136000 ,0.152000 ,0.168000 ,0.184000 ,0.200000  };

const int n_em_shift_vs_phimod_ptetabin_zbins = 9;
float em_shift_vs_phimod_ptetabin_zbins[n_em_shift_vs_phimod_ptetabin_zbins+1] = {0.500000 ,1.500000 ,2.500000 ,3.500000 ,4.500000 ,5.500000 ,6.500000 ,7.500000 ,8.500000 ,9.500000  };

TH3F *em_shift_vs_phimod_ptetabin = new TH3F("em_shift_vs_phimod_ptetabin","presel, cal phi - trk phi vs phimod and pteta bin", n_em_shift_vs_phimod_ptetabin_xbins, em_shift_vs_phimod_ptetabin_xbins, n_em_shift_vs_phimod_ptetabin_ybins, em_shift_vs_phimod_ptetabin_ybins, n_em_shift_vs_phimod_ptetabin_zbins, em_shift_vs_phimod_ptetabin_zbins);

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: under 0.500000

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

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 0.500000 to 1.500000

////////////////////////////////////////////////////
// ybin: under -0.200000

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,0,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,0,1,1.000000);

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

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,6,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,6,1,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,6,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,6,1,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,6,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,6,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,7,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,7,1,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,7,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,7,1,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,7,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,7,1,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,7,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,7,1,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,7,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,7,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,8,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,8,1,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,8,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,8,1,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,8,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,8,1,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,8,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,8,1,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,8,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,8,1,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,8,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,8,1,2.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,8,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,8,1,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,8,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,8,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,9,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,9,1,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,9,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,9,1,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,9,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,9,1,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,9,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,9,1,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,9,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,9,1,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,9,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,9,1,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,9,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,9,1,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,9,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,9,1,1.414214);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,9,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,9,1,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,9,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,9,1,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,9,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,9,1,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,9,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,9,1,1.732051);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,9,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,9,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,10,1,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,10,1,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,10,1,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,10,1,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,10,1,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,10,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,10,1,1.414214);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,10,1,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,10,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,10,1,1.732051);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,10,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,10,1,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,10,1,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,10,1,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,10,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,10,1,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,10,1,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,10,1,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,10,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,10,1,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,10,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,10,1,1.732051);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,10,1,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,10,1,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,10,1,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,10,1,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,10,1,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,10,1,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,10,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,10,1,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,10,1,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,10,1,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,10,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,10,1,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,10,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,10,1,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,10,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,10,1,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,10,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,10,1,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,10,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,10,1,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,10,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,10,1,1.414214);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,11,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,11,1,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,11,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,11,1,1.414214);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,11,1,1.732051);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,11,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,11,1,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,11,1,1.732051);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,11,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,11,1,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,11,1,1.732051);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,11,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,11,1,2.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,11,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,11,1,2.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,11,1,1.732051);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,11,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,11,1,1.414214);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,11,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,11,1,2.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,11,1,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,11,1,1.732051);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,11,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,11,1,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,11,1,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,11,1,2.236068);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,11,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,11,1,2.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,11,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,11,1,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,11,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,11,1,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,11,1,1.732051);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,11,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,11,1,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,11,1,1.732051);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,11,1,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,11,1,1.732051);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,11,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,11,1,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,11,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,11,1,2.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,11,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,11,1,1.732051);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,11,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,11,1,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,11,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,11,1,1.414214);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,11,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,11,1,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,11,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,11,1,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,11,1,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,11,1,2.236068);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,11,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,11,1,1.414214);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,11,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,11,1,1.000000);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,12,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,12,1,1.732051);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,12,1,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,12,1,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,12,1,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,12,1,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,12,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,12,1,2.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,12,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,12,1,1.414214);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,12,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,12,1,1.732051);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,12,1,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,12,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,12,1,2.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,12,1,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,12,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,12,1,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,12,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,12,1,2.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,12,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,12,1,1.732051);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,12,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,12,1,2.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,12,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,12,1,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,12,1,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,12,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,12,1,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,12,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,12,1,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,12,1,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,12,1,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,12,1,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,12,1,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,12,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,12,1,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,12,1,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,12,1,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,12,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,12,1,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,12,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,12,1,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,12,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,12,1,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,12,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,12,1,1.732051);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,12,1,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,12,1,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,12,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,12,1,1.732051);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,12,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,12,1,2.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,12,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,12,1,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,12,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,12,1,1.414214);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,12,1,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,12,1,2.645751);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,12,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,12,1,1.414214);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,12,1,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,12,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,12,1,2.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,12,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,12,1,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,12,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,12,1,2.000000);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,13,1,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,13,1,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,13,1,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,13,1,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,13,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,13,1,2.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,13,1,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,13,1,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,13,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,13,1,1.414214);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,13,1,1.732051);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,13,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,13,1,2.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,13,1,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,13,1,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,13,1,2.236068);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,13,1,1.732051);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,13,1,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,13,1,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,13,1,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,13,1,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,13,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,13,1,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,13,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,13,1,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,13,1,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,13,1,1.732051);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,13,1,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,13,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,13,1,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,13,1,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,13,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,13,1,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,13,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,13,1,2.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,13,1,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,13,1,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,13,1,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,13,1,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,13,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,13,1,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,13,1,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,13,1,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,13,1,2.449490);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,13,1,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,13,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,13,1,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,13,1,1.732051);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,13,1,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,13,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,13,1,2.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,13,1,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,13,1,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,13,1,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,13,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,13,1,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,13,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,13,1,1.732051);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,13,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,13,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,14,1,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,14,1,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,14,1,2.645751);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,14,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,14,1,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,14,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,14,1,2.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,14,1,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,14,1,2.236068);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,14,1,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,14,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,14,1,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,14,1,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,14,1,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,14,1,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,14,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,14,1,1.732051);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,14,1,1.414214);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,14,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,14,1,1.732051);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,14,1,1.414214);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,14,1,1.414214);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,14,1,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,14,1,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,14,1,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,14,1,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,14,1,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,14,1,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,14,1,2.236068);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,14,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,14,1,2.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,14,1,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,14,1,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,14,1,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,14,1,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,14,1,2.449490);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,14,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,14,1,2.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,14,1,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,14,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,14,1,1.732051);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,14,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,14,1,1.732051);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,14,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,14,1,1.732051);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,14,1,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,14,1,2.449490);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,14,1,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,14,1,2.828427);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,14,1,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,14,1,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,14,1,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,14,1,1.414214);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,14,1,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,14,1,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,14,1,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,14,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,14,1,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,14,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,14,1,2.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,14,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,14,1,1.414214);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,15,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,15,1,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,15,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,15,1,2.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,15,1,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,15,1,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,15,1,2.236068);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,15,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,15,1,2.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,15,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,15,1,1.414214);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,15,1,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,15,1,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,15,1,2.645751);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,15,1,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,15,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,15,1,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,15,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,15,1,1.732051);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,15,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,15,1,1.414214);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,15,1,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,15,1,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,15,1,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,15,1,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,15,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,15,1,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,15,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,15,1,2.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,15,1,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,15,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,15,1,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,15,1,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,15,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,15,1,2.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,15,1,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,15,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,15,1,1.732051);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,15,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,15,1,1.732051);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,15,1,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,15,1,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,15,1,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,15,1,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,15,1,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,15,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,15,1,1.414214);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,15,1,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,15,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,15,1,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,15,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,15,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,16,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,16,1,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,16,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,16,1,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,16,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,16,1,1.732051);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,16,1,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,16,1,2.645751);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,16,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,16,1,2.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,16,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,16,1,1.732051);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,16,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,16,1,2.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,16,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,16,1,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,16,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,16,1,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,16,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,16,1,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,16,1,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,16,1,2.236068);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,16,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,16,1,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,16,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,16,1,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,16,1,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,16,1,2.236068);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,16,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,16,1,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,16,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,16,1,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,16,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,16,1,1.414214);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,16,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,16,1,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,16,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,16,1,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,16,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,16,1,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,16,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,16,1,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,16,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,16,1,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,16,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,16,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,17,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,17,1,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,17,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,17,1,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,17,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,17,1,1.414214);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,17,1,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,17,1,2.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,17,1,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,17,1,2.449490);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,17,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,17,1,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,17,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,17,1,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,17,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,17,1,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,17,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,17,1,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,17,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,17,1,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,17,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,17,1,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,17,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,17,1,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,17,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,17,1,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,17,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,17,1,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,17,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,17,1,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,17,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,17,1,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,17,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,17,1,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,17,1,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,17,1,1.414214);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,17,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,17,1,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,17,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,17,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,18,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,18,1,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,18,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,18,1,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,18,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,18,1,1.732051);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,18,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,18,1,1.732051);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,18,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,18,1,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,18,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,18,1,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,18,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,18,1,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,18,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,18,1,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,18,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,18,1,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,18,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,18,1,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,18,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,18,1,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,18,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,18,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,19,1,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,19,1,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,19,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,19,1,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,19,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,19,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,20,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,20,1,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,20,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,20,1,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,20,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,20,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,21,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,21,1,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,21,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,21,1,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,21,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,21,1,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,21,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,21,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,22,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,22,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,23,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,23,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,24,1,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,24,1,1.000000);

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 1.500000 to 2.500000

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

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,5,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,5,2,1.000000);

////////////////////////////////////////////////////
// ybin: -0.120000 to -0.104000

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,6,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,6,2,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,6,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,6,2,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,6,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,6,2,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,6,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,6,2,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,6,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,6,2,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,7,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,7,2,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,7,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,7,2,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,7,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,7,2,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,7,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,7,2,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,7,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,7,2,1.414214);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,8,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,8,2,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,8,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,8,2,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,8,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,8,2,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,8,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,8,2,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,8,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,8,2,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,8,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,8,2,1.414214);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,8,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,8,2,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,8,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,8,2,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,8,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,8,2,1.000000);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,9,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,9,2,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,9,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,9,2,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,9,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,9,2,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,9,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,9,2,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,9,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,9,2,1.414214);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,9,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,9,2,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,9,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,9,2,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,9,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,9,2,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,9,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,9,2,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,9,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,9,2,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,9,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,9,2,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,9,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,9,2,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,9,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,9,2,2.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,9,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,9,2,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,9,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,9,2,2.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,9,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,9,2,2.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,9,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,9,2,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,9,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,9,2,1.414214);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,10,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,10,2,1.414214);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,10,2,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,10,2,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,10,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,10,2,2.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,10,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,10,2,2.236068);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,10,2,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,10,2,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,10,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,10,2,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,10,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,10,2,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,10,2,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,10,2,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,10,2,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,10,2,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,10,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,10,2,1.732051);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,10,2,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,10,2,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,10,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,10,2,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,10,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,10,2,1.414214);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,10,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,10,2,2.449490);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,10,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,10,2,2.236068);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,10,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,10,2,2.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,10,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,10,2,2.449490);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,10,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,10,2,2.236068);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,10,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,10,2,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,10,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,10,2,2.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,10,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,10,2,2.236068);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,10,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,10,2,1.732051);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,10,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,10,2,1.414214);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,11,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,11,2,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,11,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,11,2,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,11,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,11,2,1.414214);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,11,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,11,2,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,11,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,11,2,1.414214);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,11,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,11,2,1.732051);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,11,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,11,2,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,11,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,11,2,1.414214);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,11,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,11,2,2.645751);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,11,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,11,2,2.645751);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,11,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,11,2,2.236068);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,11,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,11,2,1.732051);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,11,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,11,2,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,11,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,11,2,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,11,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,11,2,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,11,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,11,2,2.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,11,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,11,2,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,11,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,11,2,2.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,11,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,11,2,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,11,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,11,2,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,11,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,11,2,1.732051);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,11,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,11,2,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,11,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,11,2,1.414214);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,11,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,11,2,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,11,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,11,2,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,11,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,11,2,2.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,11,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,11,2,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,11,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,11,2,1.732051);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,11,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,11,2,2.236068);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,11,2,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,11,2,3.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,11,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,11,2,1.732051);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,11,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,11,2,2.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,11,2,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,11,2,3.162278);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,11,2,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,11,2,2.828427);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,11,2,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,11,2,2.828427);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,11,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,11,2,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,11,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,11,2,1.732051);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,12,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,12,2,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,12,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,12,2,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,12,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,12,2,1.414214);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,12,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,12,2,1.732051);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,12,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,12,2,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,12,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,12,2,1.414214);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,12,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,12,2,2.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,12,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,12,2,1.414214);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,12,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,12,2,2.645751);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,12,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,12,2,1.732051);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,12,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,12,2,2.236068);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,12,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,12,2,2.449490);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,12,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,12,2,2.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,12,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,12,2,2.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,12,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,12,2,2.236068);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,12,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,12,2,2.236068);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,12,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,12,2,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,12,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,12,2,2.236068);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,12,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,12,2,2.449490);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,12,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,12,2,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,12,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,12,2,1.414214);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,12,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,12,2,1.732051);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,12,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,12,2,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,12,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,12,2,2.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,12,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,12,2,2.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,12,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,12,2,2.236068);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,12,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,12,2,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,12,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,12,2,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,12,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,12,2,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,12,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,12,2,2.449490);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,12,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,12,2,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,12,2,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,12,2,3.162278);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,12,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,12,2,2.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,12,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,12,2,2.236068);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,12,2,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,12,2,3.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,12,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,12,2,1.732051);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,12,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,12,2,2.449490);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,12,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,12,2,1.414214);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,12,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,12,2,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,12,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,12,2,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,12,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,12,2,1.414214);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,12,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,12,2,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,12,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,12,2,1.414214);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,13,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,13,2,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,13,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,13,2,1.732051);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,13,2,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,13,2,2.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,13,2,2.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,13,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,13,2,1.414214);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,13,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,13,2,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,13,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,13,2,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,13,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,13,2,1.414214);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,13,2,2.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,13,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,13,2,2.645751);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,13,2,2.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,13,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,13,2,2.645751);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,13,2,2.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,13,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,13,2,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,13,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,13,2,2.236068);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,13,2,2.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,13,2,2.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,13,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,13,2,1.414214);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,13,2,2.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,13,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,13,2,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,13,2,2.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,13,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,13,2,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,13,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,13,2,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,13,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,13,2,1.414214);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,13,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,13,2,1.732051);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,13,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,13,2,2.236068);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,13,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,13,2,2.645751);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,13,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,13,2,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,13,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,13,2,1.414214);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,13,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,13,2,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,13,2,2.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,13,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,13,2,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,13,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,13,2,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,13,2,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,13,2,2.828427);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,13,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,13,2,2.449490);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,13,2,2.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,13,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,13,2,2.236068);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,13,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,13,2,2.236068);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,13,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,13,2,2.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,13,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,13,2,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,13,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,13,2,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,13,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,13,2,2.449490);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,13,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,13,2,1.732051);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,14,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,14,2,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,14,2,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,14,2,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,14,2,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,14,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,14,2,2.236068);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,14,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,14,2,2.236068);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,14,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,14,2,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,14,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,14,2,2.236068);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,14,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,14,2,2.236068);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,14,2,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,14,2,3.162278);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,14,2,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,14,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,14,2,1.732051);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,14,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,14,2,2.236068);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,14,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,14,2,1.732051);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,14,2,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,14,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,14,2,1.732051);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,14,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,14,2,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,14,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,14,2,2.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,14,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,14,2,2.236068);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,14,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,14,2,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,14,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,14,2,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,14,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,14,2,2.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,14,2,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,14,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,14,2,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,14,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,14,2,2.449490);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,14,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,14,2,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,14,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,14,2,2.449490);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,14,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,14,2,2.236068);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,14,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,14,2,2.645751);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,14,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,14,2,2.645751);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,14,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,14,2,2.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,14,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,14,2,2.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,14,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,14,2,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,14,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,14,2,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,14,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,14,2,2.236068);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,14,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,14,2,2.449490);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,14,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,14,2,2.449490);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,14,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,14,2,1.414214);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,14,2,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,14,2,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,14,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,14,2,1.732051);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,14,2,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,14,2,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,14,2,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,14,2,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,14,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,14,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,15,2,1.414214);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,15,2,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,15,2,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,15,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,15,2,2.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,15,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,15,2,2.645751);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,15,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,15,2,1.732051);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,15,2,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,15,2,2.828427);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,15,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,15,2,2.449490);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,15,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,15,2,2.236068);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,15,2,1.414214);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,15,2,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,15,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,15,2,2.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,15,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,15,2,1.732051);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,15,2,1.414214);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,15,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,15,2,1.732051);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,15,2,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,15,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,15,2,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,15,2,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,15,2,1.414214);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,15,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,15,2,1.732051);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,15,2,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,15,2,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,15,2,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,15,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,15,2,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,15,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,15,2,2.645751);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,15,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,15,2,2.236068);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,15,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,15,2,2.236068);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,15,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,15,2,2.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,15,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,15,2,2.236068);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,15,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,15,2,2.236068);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,15,2,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,15,2,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,15,2,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,15,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,15,2,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,15,2,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,15,2,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,15,2,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,15,2,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,15,2,1.414214);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,15,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,15,2,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,15,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,15,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,16,2,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,16,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,16,2,2.236068);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,16,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,16,2,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,16,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,16,2,2.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,16,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,16,2,2.449490);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,16,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,16,2,2.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,16,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,16,2,1.414214);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,16,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,16,2,2.236068);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,16,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,16,2,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,16,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,16,2,1.732051);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,16,2,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,16,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,16,2,1.732051);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,16,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,16,2,1.414214);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,16,2,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,16,2,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,16,2,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,16,2,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,16,2,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,16,2,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,16,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,16,2,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,16,2,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,16,2,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,16,2,2.645751);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,16,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,16,2,2.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,16,2,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,16,2,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,16,2,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,16,2,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,16,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,16,2,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,16,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,16,2,1.414214);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,17,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,17,2,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,17,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,17,2,2.236068);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,17,2,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,17,2,2.828427);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,17,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,17,2,2.449490);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,17,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,17,2,2.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,17,2,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,17,2,2.236068);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,17,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,17,2,2.449490);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,17,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,17,2,1.414214);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,17,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,17,2,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,17,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,17,2,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,17,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,17,2,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,17,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,17,2,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,17,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,17,2,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,17,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,17,2,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,17,2,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,17,2,2.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,17,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,17,2,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,17,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,17,2,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,17,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,17,2,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,17,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,17,2,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,17,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,17,2,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,17,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,17,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,18,2,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,18,2,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,18,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,18,2,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,18,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,18,2,1.414214);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,18,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,18,2,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,18,2,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,18,2,2.449490);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,18,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,18,2,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,18,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,18,2,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,18,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,18,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,19,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,19,2,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,19,2,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,19,2,1.414214);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,19,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,19,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,20,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,20,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,21,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,21,2,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,21,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,21,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,22,2,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,22,2,1.000000);

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 2.500000 to 3.500000

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
em_shift_vs_phimod_ptetabin->SetBinContent(16,5,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,5,3,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,5,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,5,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.120000 to -0.104000

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,6,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,6,3,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,6,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,6,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,7,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,7,3,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,7,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,7,3,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,7,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,7,3,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,7,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,7,3,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,7,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,7,3,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,7,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,7,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,8,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,8,3,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,8,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,8,3,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,8,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,8,3,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,8,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,8,3,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,8,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,8,3,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,8,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,8,3,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,8,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,8,3,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,8,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,8,3,1.732051);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,9,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,9,3,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,9,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,9,3,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,9,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,9,3,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,9,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,9,3,1.732051);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,9,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,9,3,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,9,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,9,3,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,9,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,9,3,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,9,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,9,3,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,9,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,9,3,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,9,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,9,3,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,9,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,9,3,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,9,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,9,3,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,9,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,9,3,1.414214);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,9,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,9,3,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,9,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,9,3,1.414214);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,9,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,9,3,2.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,9,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,9,3,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,9,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,9,3,1.414214);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,9,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,9,3,2.000000);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,10,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,10,3,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,10,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,10,3,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,10,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,10,3,1.732051);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,10,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,10,3,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,10,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,10,3,2.236068);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,10,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,10,3,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,10,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,10,3,1.732051);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,10,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,10,3,1.732051);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,10,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,10,3,1.732051);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,10,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,10,3,2.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,10,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,10,3,2.449490);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,10,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,10,3,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,10,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,10,3,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,10,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,10,3,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,10,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,10,3,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,10,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,10,3,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,10,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,10,3,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,10,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,10,3,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,10,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,10,3,2.449490);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,10,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,10,3,2.449490);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,10,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,10,3,2.236068);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,10,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,10,3,2.236068);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,10,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,10,3,2.449490);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,10,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,10,3,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,10,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,10,3,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,10,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,10,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,11,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,11,3,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,11,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,11,3,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,11,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,11,3,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,11,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,11,3,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,11,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,11,3,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,11,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,11,3,2.236068);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,11,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,11,3,2.236068);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,11,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,11,3,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,11,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,11,3,3.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,11,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,11,3,2.236068);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,11,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,11,3,2.449490);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,11,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,11,3,1.732051);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,11,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,11,3,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,11,3,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,11,3,2.645751);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,11,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,11,3,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,11,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,11,3,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,11,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,11,3,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,11,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,11,3,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,11,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,11,3,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,11,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,11,3,1.732051);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,11,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,11,3,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,11,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,11,3,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,11,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,11,3,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,11,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,11,3,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,11,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,11,3,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,11,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,11,3,2.236068);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,11,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,11,3,2.236068);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,11,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,11,3,2.828427);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,11,3,12.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,11,3,3.464102);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,11,3,13.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,11,3,3.605551);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,11,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,11,3,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,11,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,11,3,1.414214);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,11,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,11,3,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,11,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,11,3,2.236068);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,11,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,11,3,2.449490);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,11,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,11,3,1.732051);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,11,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,11,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,12,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,12,3,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,12,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,12,3,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,12,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,12,3,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,12,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,12,3,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,12,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,12,3,2.236068);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,12,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,12,3,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,12,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,12,3,2.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,12,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,12,3,2.236068);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,12,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,12,3,3.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,12,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,12,3,2.449490);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,12,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,12,3,2.449490);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,12,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,12,3,2.449490);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,12,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,12,3,3.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,12,3,12.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,12,3,3.464102);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,12,3,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,12,3,3.316625);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,12,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,12,3,2.236068);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,12,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,12,3,2.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,12,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,12,3,2.449490);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,12,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,12,3,1.732051);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,12,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,12,3,2.236068);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,12,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,12,3,2.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,12,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,12,3,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,12,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,12,3,2.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,12,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,12,3,1.732051);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,12,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,12,3,1.732051);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,12,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,12,3,2.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,12,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,12,3,2.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,12,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,12,3,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,12,3,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,12,3,2.645751);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,12,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,12,3,2.828427);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,12,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,12,3,3.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,12,3,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,12,3,3.162278);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,12,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,12,3,2.828427);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,12,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,12,3,1.732051);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,12,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,12,3,2.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,12,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,12,3,2.449490);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,12,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,12,3,2.236068);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,12,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,12,3,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,12,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,12,3,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,12,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,12,3,2.449490);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,12,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,12,3,1.000000);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,13,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,13,3,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,13,3,1.732051);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,13,3,1.732051);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,13,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,13,3,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,13,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,13,3,1.414214);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,13,3,1.732051);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,13,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,13,3,2.236068);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,13,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,13,3,2.236068);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,13,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,13,3,2.236068);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,13,3,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,13,3,3.162278);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,13,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,13,3,3.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,13,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,13,3,3.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,13,3,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,13,3,3.162278);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,13,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,13,3,2.828427);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,13,3,12.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,13,3,3.464102);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,13,3,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,13,3,3.316625);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,13,3,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,13,3,3.162278);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,13,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,13,3,2.828427);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,13,3,1.732051);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,13,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,13,3,2.449490);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,13,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,13,3,2.828427);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,13,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,13,3,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,13,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,13,3,2.828427);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,13,3,1.732051);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,13,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,13,3,2.449490);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,13,3,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,13,3,2.645751);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,13,3,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,13,3,2.645751);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,13,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,13,3,2.449490);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,13,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,13,3,2.449490);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,13,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,13,3,2.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,13,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,13,3,2.449490);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,13,3,1.732051);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,13,3,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,13,3,3.162278);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,13,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,13,3,2.236068);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,13,3,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,13,3,3.162278);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,13,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,13,3,2.828427);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,13,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,13,3,2.449490);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,13,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,13,3,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,13,3,1.732051);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,13,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,13,3,2.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,13,3,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,13,3,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,13,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,13,3,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,13,3,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,13,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,13,3,1.732051);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,13,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,13,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,14,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,14,3,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,14,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,14,3,2.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,14,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,14,3,1.732051);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,14,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,14,3,2.236068);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,14,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,14,3,3.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,14,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,14,3,1.414214);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,14,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,14,3,2.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,14,3,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,14,3,3.162278);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,14,3,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,14,3,3.316625);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,14,3,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,14,3,3.316625);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,14,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,14,3,2.828427);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,14,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,14,3,2.449490);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,14,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,14,3,2.236068);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,14,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,14,3,1.414214);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,14,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,14,3,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,14,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,14,3,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,14,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,14,3,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,14,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,14,3,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,14,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,14,3,2.236068);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,14,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,14,3,1.732051);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,14,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,14,3,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,14,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,14,3,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,14,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,14,3,2.449490);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,14,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,14,3,2.828427);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,14,3,12.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,14,3,3.464102);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,14,3,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,14,3,3.162278);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,14,3,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,14,3,2.645751);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,14,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,14,3,2.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,14,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,14,3,2.236068);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,14,3,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,14,3,3.316625);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,14,3,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,14,3,3.316625);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,14,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,14,3,3.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,14,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,14,3,2.449490);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,14,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,14,3,1.732051);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,14,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,14,3,2.449490);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,14,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,14,3,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,14,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,14,3,1.732051);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,14,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,14,3,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,14,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,14,3,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,14,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,14,3,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,14,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,14,3,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,14,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,14,3,1.414214);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,15,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,15,3,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,15,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,15,3,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,15,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,15,3,3.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,15,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,15,3,2.449490);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,15,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,15,3,2.236068);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,15,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,15,3,2.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,15,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,15,3,2.236068);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,15,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,15,3,2.828427);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,15,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,15,3,2.828427);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,15,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,15,3,2.236068);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,15,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,15,3,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,15,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,15,3,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,15,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,15,3,2.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,15,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,15,3,2.449490);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,15,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,15,3,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,15,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,15,3,2.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,15,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,15,3,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,15,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,15,3,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,15,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,15,3,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,15,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,15,3,2.449490);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,15,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,15,3,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,15,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,15,3,2.828427);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,15,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,15,3,2.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,15,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,15,3,2.449490);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,15,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,15,3,2.236068);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,15,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,15,3,2.828427);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,15,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,15,3,3.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,15,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,15,3,2.236068);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,15,3,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,15,3,2.828427);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,15,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,15,3,2.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,15,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,15,3,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,15,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,15,3,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,15,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,15,3,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,15,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,15,3,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,15,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,15,3,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,15,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,15,3,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,15,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,15,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,16,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,16,3,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,16,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,16,3,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,16,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,16,3,2.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,16,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,16,3,2.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,16,3,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,16,3,2.449490);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,16,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,16,3,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,16,3,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,16,3,3.316625);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,16,3,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,16,3,3.162278);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,16,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,16,3,2.236068);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,16,3,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,16,3,2.645751);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,16,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,16,3,1.414214);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,16,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,16,3,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,16,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,16,3,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,16,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,16,3,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,16,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,16,3,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,16,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,16,3,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,16,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,16,3,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,16,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,16,3,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,16,3,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,16,3,3.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,16,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,16,3,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,16,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,16,3,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,16,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,16,3,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,16,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,16,3,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,16,3,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,16,3,2.236068);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,16,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,16,3,1.732051);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,16,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,16,3,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,16,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,16,3,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,16,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,16,3,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,16,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,16,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,17,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,17,3,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,17,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,17,3,2.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,17,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,17,3,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,17,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,17,3,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,17,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,17,3,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,17,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,17,3,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,17,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,17,3,1.414214);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,17,3,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,17,3,2.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,17,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,17,3,1.732051);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,17,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,17,3,1.414214);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,17,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,17,3,1.414214);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,17,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,17,3,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,17,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,17,3,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,17,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,17,3,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,17,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,17,3,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,17,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,17,3,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,17,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,17,3,1.732051);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,17,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,17,3,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,17,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,17,3,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,17,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,17,3,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,17,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,17,3,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,17,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,17,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,18,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,18,3,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,18,3,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,18,3,1.732051);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,18,3,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,18,3,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,18,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,18,3,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,18,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,18,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,19,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,19,3,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,19,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,19,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,20,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,20,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,21,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,21,3,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,21,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,21,3,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,21,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,21,3,1.000000);

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,26,3,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,26,3,1.000000);

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 3.500000 to 4.500000

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
em_shift_vs_phimod_ptetabin->SetBinContent(19,6,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,6,4,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,6,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,6,4,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,7,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,7,4,1.000000);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,8,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,8,4,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,8,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,8,4,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,8,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,8,4,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,8,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,8,4,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,8,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,8,4,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,8,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,8,4,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,8,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,8,4,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,8,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,8,4,1.000000);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,9,4,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,9,4,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,9,4,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,9,4,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,9,4,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,9,4,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,9,4,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,9,4,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,9,4,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,9,4,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,9,4,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,9,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,9,4,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,9,4,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,9,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,9,4,1.414214);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,9,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,9,4,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,9,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,9,4,1.732051);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,10,4,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,10,4,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,10,4,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,10,4,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,10,4,1.414214);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,10,4,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,10,4,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,10,4,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,10,4,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,10,4,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,10,4,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,10,4,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,10,4,1.414214);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,10,4,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,10,4,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,10,4,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,10,4,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,10,4,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,10,4,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,10,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,10,4,1.732051);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,10,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,10,4,1.732051);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,10,4,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,10,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,10,4,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,10,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,10,4,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,10,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,10,4,1.732051);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,10,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,10,4,2.000000);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,11,4,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,11,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,11,4,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,11,4,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,11,4,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,11,4,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,11,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,11,4,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,11,4,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,11,4,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,11,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,11,4,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,11,4,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,11,4,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,11,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,11,4,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,11,4,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,11,4,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,11,4,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,11,4,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,11,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,11,4,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,11,4,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,11,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,11,4,1.732051);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,11,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,11,4,2.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,11,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,11,4,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,11,4,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,11,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,11,4,1.732051);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,11,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,11,4,1.000000);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,12,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,12,4,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,12,4,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,12,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,12,4,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,12,4,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,12,4,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,12,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,12,4,2.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,12,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,12,4,1.414214);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,12,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,12,4,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,12,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,12,4,1.732051);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,12,4,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,12,4,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,12,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,12,4,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,12,4,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,12,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,12,4,1.732051);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,12,4,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,12,4,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,12,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,12,4,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,12,4,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,12,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,12,4,2.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,12,4,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,12,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,12,4,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,12,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,12,4,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,12,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,12,4,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,12,4,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,12,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,12,4,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,12,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,12,4,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,12,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,12,4,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,12,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,12,4,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,12,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,12,4,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,12,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,12,4,1.732051);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,12,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,12,4,2.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,12,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,12,4,2.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,12,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,12,4,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,12,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,12,4,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,12,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,12,4,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,12,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,12,4,2.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,12,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,12,4,1.414214);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,13,4,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,13,4,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,13,4,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,13,4,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,13,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,13,4,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,13,4,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,13,4,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,13,4,1.414214);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,13,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,13,4,1.732051);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,13,4,1.414214);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,13,4,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,13,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,13,4,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,13,4,1.414214);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,13,4,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,13,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,13,4,1.732051);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,13,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,13,4,2.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,13,4,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,13,4,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,13,4,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,13,4,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,13,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,13,4,1.732051);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,13,4,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,13,4,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,13,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,13,4,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,13,4,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,13,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,13,4,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,13,4,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,13,4,1.414214);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,13,4,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,13,4,1.414214);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,13,4,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,13,4,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,13,4,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,13,4,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,13,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,13,4,1.414214);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,13,4,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,13,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,13,4,1.000000);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,14,4,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,14,4,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,14,4,2.236068);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,14,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,14,4,2.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,14,4,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,14,4,2.236068);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,14,4,1.414214);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,14,4,1.414214);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,14,4,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,14,4,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,14,4,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,14,4,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,14,4,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,14,4,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,14,4,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,14,4,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,14,4,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,14,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,14,4,1.732051);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,14,4,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,14,4,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,14,4,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,14,4,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,14,4,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,14,4,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,14,4,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,14,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,14,4,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,14,4,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,14,4,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,14,4,2.236068);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,14,4,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,14,4,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,14,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,14,4,1.732051);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,14,4,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,14,4,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,14,4,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,14,4,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,14,4,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,14,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,14,4,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,14,4,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,14,4,1.414214);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,14,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,14,4,2.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,14,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,14,4,1.414214);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,15,4,1.414214);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,15,4,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,15,4,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,15,4,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,15,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,15,4,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,15,4,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,15,4,1.414214);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,15,4,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,15,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,15,4,1.732051);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,15,4,1.414214);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,15,4,1.414214);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,15,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,15,4,2.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,15,4,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,15,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,15,4,1.732051);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,15,4,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,15,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,15,4,1.732051);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,15,4,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,15,4,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,15,4,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,15,4,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,15,4,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,15,4,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,15,4,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,15,4,1.414214);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,15,4,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,15,4,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,15,4,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,15,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,15,4,2.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,15,4,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,15,4,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,15,4,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,15,4,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,15,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,15,4,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,15,4,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,15,4,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,15,4,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,15,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,15,4,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,15,4,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,15,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,15,4,1.000000);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,16,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,16,4,1.414214);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,16,4,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,16,4,2.449490);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,16,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,16,4,2.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,16,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,16,4,1.732051);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,16,4,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,16,4,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,16,4,2.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,16,4,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,16,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,16,4,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,16,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,16,4,1.732051);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,16,4,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,16,4,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,16,4,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,16,4,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,16,4,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,16,4,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,16,4,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,16,4,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,16,4,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,16,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,16,4,1.732051);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,16,4,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,16,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,16,4,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,16,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,16,4,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,16,4,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,16,4,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,16,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,16,4,1.000000);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,17,4,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,17,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,17,4,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,17,4,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,17,4,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,17,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,17,4,1.414214);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,17,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,17,4,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,17,4,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,17,4,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,17,4,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,17,4,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,17,4,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,17,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,17,4,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,17,4,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,17,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,17,4,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,17,4,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,17,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,17,4,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,17,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,17,4,1.414214);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,18,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,18,4,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,18,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,18,4,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,18,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,18,4,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,18,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,18,4,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,18,4,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,18,4,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,18,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,18,4,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,19,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,19,4,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,19,4,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,19,4,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,19,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,19,4,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,19,4,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,19,4,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 4.500000 to 5.500000

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

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,6,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,6,5,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,6,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,6,5,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,7,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,7,5,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,7,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,7,5,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,7,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,7,5,1.414214);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,8,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,8,5,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,8,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,8,5,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,8,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,8,5,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,8,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,8,5,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,8,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,8,5,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,8,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,8,5,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,8,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,8,5,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,8,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,8,5,1.414214);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,9,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,9,5,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,9,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,9,5,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,9,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,9,5,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,9,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,9,5,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,9,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,9,5,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,9,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,9,5,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,9,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,9,5,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,9,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,9,5,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,9,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,9,5,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,9,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,9,5,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,9,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,9,5,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,9,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,9,5,2.449490);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,9,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,9,5,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,9,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,9,5,2.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,9,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,9,5,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,9,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,9,5,2.236068);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,9,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,9,5,2.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,9,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,9,5,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,9,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,9,5,1.414214);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,10,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,10,5,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,10,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,10,5,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,10,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,10,5,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,10,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,10,5,1.732051);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,10,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,10,5,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,10,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,10,5,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,10,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,10,5,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,10,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,10,5,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,10,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,10,5,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,10,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,10,5,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,10,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,10,5,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,10,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,10,5,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,10,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,10,5,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,10,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,10,5,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,10,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,10,5,1.414214);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,10,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,10,5,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,10,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,10,5,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,10,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,10,5,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,10,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,10,5,2.236068);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,10,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,10,5,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,10,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,10,5,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,10,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,10,5,2.236068);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,10,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,10,5,1.414214);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,11,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,11,5,1.414214);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,11,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,11,5,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,11,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,11,5,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,11,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,11,5,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,11,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,11,5,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,11,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,11,5,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,11,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,11,5,1.732051);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,11,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,11,5,1.414214);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,11,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,11,5,2.236068);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,11,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,11,5,1.732051);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,11,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,11,5,2.449490);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,11,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,11,5,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,11,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,11,5,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,11,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,11,5,2.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,11,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,11,5,1.732051);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,11,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,11,5,2.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,11,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,11,5,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,11,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,11,5,2.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,11,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,11,5,2.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,11,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,11,5,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,11,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,11,5,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,11,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,11,5,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,11,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,11,5,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,11,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,11,5,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,11,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,11,5,2.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,11,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,11,5,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,11,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,11,5,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,11,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,11,5,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,11,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,11,5,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,11,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,11,5,1.732051);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,11,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,11,5,2.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,11,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,11,5,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,11,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,11,5,2.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,11,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,11,5,2.645751);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,11,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,11,5,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,11,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,11,5,2.236068);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,11,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,11,5,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,11,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,11,5,2.236068);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,11,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,11,5,2.449490);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,11,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,11,5,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,11,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,11,5,1.000000);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,12,5,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,12,5,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,12,5,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,12,5,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,12,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,12,5,2.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,12,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,12,5,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,12,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,12,5,1.732051);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,12,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,12,5,2.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,12,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,12,5,2.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,12,5,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,12,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,12,5,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,12,5,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,12,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,12,5,2.449490);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,12,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,12,5,2.645751);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,12,5,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,12,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,12,5,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,12,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,12,5,1.732051);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,12,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,12,5,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,12,5,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,12,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,12,5,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,12,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,12,5,2.449490);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,12,5,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,12,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,12,5,2.449490);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,12,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,12,5,2.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,12,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,12,5,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,12,5,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,12,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,12,5,1.732051);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,12,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,12,5,2.236068);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,12,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,12,5,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,12,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,12,5,2.449490);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,12,5,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,12,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,12,5,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,12,5,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,12,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,12,5,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,12,5,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,12,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,12,5,2.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,12,5,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,12,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,12,5,1.732051);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,12,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,12,5,1.000000);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,13,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,13,5,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,13,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,13,5,1.414214);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,13,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,13,5,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,13,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,13,5,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,13,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,13,5,1.414214);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,13,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,13,5,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,13,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,13,5,1.732051);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,13,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,13,5,2.645751);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,13,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,13,5,2.236068);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,13,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,13,5,1.732051);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,13,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,13,5,1.732051);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,13,5,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,13,5,3.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,13,5,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,13,5,2.828427);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,13,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,13,5,2.236068);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,13,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,13,5,2.449490);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,13,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,13,5,2.449490);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,13,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,13,5,2.236068);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,13,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,13,5,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,13,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,13,5,2.449490);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,13,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,13,5,1.732051);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,13,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,13,5,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,13,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,13,5,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,13,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,13,5,2.236068);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,13,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,13,5,2.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,13,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,13,5,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,13,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,13,5,2.236068);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,13,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,13,5,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,13,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,13,5,1.414214);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,13,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,13,5,2.645751);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,13,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,13,5,2.236068);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,13,5,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,13,5,2.828427);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,13,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,13,5,2.645751);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,13,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,13,5,2.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,13,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,13,5,2.449490);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,13,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,13,5,2.449490);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,13,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,13,5,2.449490);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,13,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,13,5,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,13,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,13,5,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,13,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,13,5,2.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,13,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,13,5,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,13,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,13,5,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,13,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,13,5,1.414214);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,14,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,14,5,1.414214);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,14,5,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,14,5,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,14,5,1.732051);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,14,5,1.732051);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,14,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,14,5,2.236068);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,14,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,14,5,2.449490);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,14,5,1.732051);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,14,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,14,5,2.449490);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,14,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,14,5,2.645751);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,14,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,14,5,2.645751);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,14,5,1.732051);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,14,5,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,14,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,14,5,2.645751);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,14,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,14,5,1.414214);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,14,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,14,5,2.236068);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,14,5,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,14,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,14,5,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,14,5,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,14,5,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,14,5,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,14,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,14,5,2.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,14,5,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,14,5,1.732051);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,14,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,14,5,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,14,5,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,14,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,14,5,2.449490);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,14,5,1.732051);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,14,5,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,14,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,14,5,2.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,14,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,14,5,2.449490);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,14,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,14,5,2.645751);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,14,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,14,5,2.449490);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,14,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,14,5,2.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,14,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,14,5,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,14,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,14,5,2.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,14,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,14,5,1.732051);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,14,5,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,14,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,14,5,2.236068);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,14,5,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,14,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,14,5,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,14,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,14,5,2.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,14,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,14,5,2.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,14,5,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,14,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,14,5,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,14,5,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,14,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,14,5,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,14,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,14,5,1.000000);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,15,5,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,15,5,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,15,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,15,5,2.449490);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,15,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,15,5,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,15,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,15,5,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,15,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,15,5,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,15,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,15,5,1.414214);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,15,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,15,5,2.236068);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,15,5,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,15,5,3.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,15,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,15,5,2.449490);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,15,5,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,15,5,2.828427);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,15,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,15,5,1.732051);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,15,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,15,5,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,15,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,15,5,2.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,15,5,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,15,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,15,5,1.732051);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,15,5,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,15,5,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,15,5,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,15,5,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,15,5,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,15,5,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,15,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,15,5,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,15,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,15,5,2.449490);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,15,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,15,5,2.449490);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,15,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,15,5,2.236068);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,15,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,15,5,2.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,15,5,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,15,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,15,5,2.645751);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,15,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,15,5,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,15,5,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,15,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,15,5,2.236068);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,15,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,15,5,1.732051);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,15,5,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,15,5,2.645751);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,15,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,15,5,2.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,15,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,15,5,1.732051);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,15,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,15,5,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,15,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,15,5,1.732051);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,15,5,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,15,5,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,15,5,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,15,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,15,5,1.000000);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,16,5,1.414214);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,16,5,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,16,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,16,5,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,16,5,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,16,5,2.236068);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,16,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,16,5,2.449490);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,16,5,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,16,5,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,16,5,2.449490);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,16,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,16,5,2.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,16,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,16,5,2.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,16,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,16,5,2.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,16,5,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,16,5,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,16,5,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,16,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,16,5,1.732051);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,16,5,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,16,5,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,16,5,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,16,5,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,16,5,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,16,5,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,16,5,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,16,5,1.414214);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,16,5,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,16,5,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,16,5,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,16,5,1.414214);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,16,5,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,16,5,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,16,5,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,16,5,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,16,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,16,5,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,16,5,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,16,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,16,5,1.000000);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,17,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,17,5,1.414214);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,17,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,17,5,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,17,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,17,5,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,17,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,17,5,1.732051);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,17,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,17,5,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,17,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,17,5,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,17,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,17,5,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,17,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,17,5,1.414214);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,17,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,17,5,1.414214);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,17,5,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,17,5,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,17,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,17,5,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,17,5,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,17,5,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,17,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,17,5,1.732051);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,17,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,17,5,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,17,5,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,17,5,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,17,5,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,17,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,17,5,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,17,5,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,17,5,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,17,5,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,17,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,17,5,1.000000);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,18,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,18,5,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,18,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,18,5,2.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,18,5,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,18,5,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,18,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,18,5,1.732051);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,18,5,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,18,5,1.732051);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,18,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,18,5,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,18,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,18,5,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,18,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,18,5,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,18,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,18,5,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,18,5,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,18,5,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,18,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,18,5,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,18,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,18,5,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,19,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,19,5,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,19,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,19,5,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,19,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,19,5,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,19,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,19,5,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,20,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,20,5,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,20,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,20,5,1.000000);

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,21,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,21,5,1.000000);

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,25,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,25,5,1.000000);

////////////////////////////////////////////////////
// ybin: over 0.200000

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,26,5,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,26,5,1.000000);

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 5.500000 to 6.500000

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
em_shift_vs_phimod_ptetabin->SetBinContent(28,4,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,4,6,1.000000);

////////////////////////////////////////////////////
// ybin: -0.136000 to -0.120000

////////////////////////////////////////////////////
// ybin: -0.120000 to -0.104000

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,6,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,6,6,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,6,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,6,6,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,8,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,8,6,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,8,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,8,6,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,8,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,8,6,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,8,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,8,6,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,8,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,8,6,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,8,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,8,6,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,8,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,8,6,1.414214);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,9,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,9,6,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,9,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,9,6,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,9,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,9,6,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,9,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,9,6,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,9,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,9,6,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,9,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,9,6,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,9,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,9,6,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,9,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,9,6,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,9,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,9,6,1.414214);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,9,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,9,6,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,9,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,9,6,2.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,9,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,9,6,2.236068);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,9,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,9,6,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,9,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,9,6,1.732051);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,9,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,9,6,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,9,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,9,6,1.000000);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,10,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,10,6,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,10,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,10,6,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,10,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,10,6,1.414214);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,10,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,10,6,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,10,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,10,6,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,10,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,10,6,1.732051);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,10,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,10,6,1.414214);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,10,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,10,6,1.732051);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,10,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,10,6,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,10,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,10,6,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,10,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,10,6,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,10,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,10,6,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,10,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,10,6,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,10,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,10,6,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,10,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,10,6,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,10,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,10,6,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,10,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,10,6,1.732051);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,10,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,10,6,1.414214);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,10,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,10,6,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,10,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,10,6,2.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,10,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,10,6,2.236068);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,10,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,10,6,2.449490);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,10,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,10,6,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,10,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,10,6,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,10,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,10,6,2.236068);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,10,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,10,6,2.000000);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,11,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,11,6,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,11,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,11,6,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,11,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,11,6,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,11,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,11,6,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,11,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,11,6,2.236068);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,11,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,11,6,2.645751);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,11,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,11,6,2.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,11,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,11,6,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,11,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,11,6,1.414214);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,11,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,11,6,2.236068);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,11,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,11,6,2.236068);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,11,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,11,6,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,11,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,11,6,2.645751);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,11,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,11,6,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,11,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,11,6,2.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,11,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,11,6,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,11,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,11,6,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,11,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,11,6,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,11,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,11,6,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,11,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,11,6,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,11,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,11,6,2.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,11,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,11,6,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,11,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,11,6,1.732051);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,11,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,11,6,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,11,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,11,6,2.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,11,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,11,6,1.732051);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,11,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,11,6,2.236068);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,11,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,11,6,2.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,11,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,11,6,2.645751);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,11,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,11,6,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,11,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,11,6,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,11,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,11,6,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,11,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,11,6,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,11,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,11,6,2.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,11,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,11,6,1.000000);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,12,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,12,6,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,12,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,12,6,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,12,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,12,6,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,12,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,12,6,1.414214);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,12,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,12,6,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,12,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,12,6,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,12,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,12,6,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,12,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,12,6,2.236068);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,12,6,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,12,6,3.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,12,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,12,6,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,12,6,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,12,6,2.828427);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,12,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,12,6,2.449490);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,12,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,12,6,2.645751);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,12,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,12,6,2.236068);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,12,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,12,6,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,12,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,12,6,1.732051);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,12,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,12,6,2.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,12,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,12,6,2.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,12,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,12,6,2.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,12,6,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,12,6,2.828427);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,12,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,12,6,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,12,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,12,6,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,12,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,12,6,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,12,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,12,6,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,12,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,12,6,1.732051);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,12,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,12,6,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,12,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,12,6,1.732051);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,12,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,12,6,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,12,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,12,6,2.236068);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,12,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,12,6,2.449490);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,12,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,12,6,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,12,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,12,6,2.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,12,6,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,12,6,2.828427);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,12,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,12,6,1.732051);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,12,6,12.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,12,6,3.464102);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,12,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,12,6,2.236068);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,12,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,12,6,2.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,12,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,12,6,2.645751);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,12,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,12,6,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,12,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,12,6,2.449490);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,12,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,12,6,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,12,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,12,6,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,12,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,12,6,2.000000);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,13,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,13,6,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,13,6,1.732051);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,13,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,13,6,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,13,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,13,6,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,13,6,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,13,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,13,6,2.449490);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,13,6,1.732051);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,13,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,13,6,2.449490);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,13,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,13,6,2.236068);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,13,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,13,6,2.449490);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,13,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,13,6,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,13,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,13,6,2.645751);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,13,6,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,13,6,3.316625);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,13,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,13,6,2.645751);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,13,6,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,13,6,3.162278);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,13,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,13,6,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,13,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,13,6,1.414214);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,13,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,13,6,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,13,6,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,13,6,2.828427);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,13,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,13,6,2.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,13,6,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,13,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,13,6,2.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,13,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,13,6,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,13,6,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,13,6,2.828427);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,13,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,13,6,1.414214);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,13,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,13,6,2.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,13,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,13,6,2.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,13,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,13,6,2.645751);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,13,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,13,6,2.236068);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,13,6,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,13,6,2.828427);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,13,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,13,6,2.449490);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,13,6,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,13,6,3.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,13,6,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,13,6,3.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,13,6,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,13,6,3.316625);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,13,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,13,6,2.449490);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,13,6,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,13,6,2.828427);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,13,6,1.732051);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,13,6,1.732051);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,13,6,1.732051);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,13,6,1.732051);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,13,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,13,6,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,13,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,13,6,2.236068);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,13,6,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,13,6,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,13,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,13,6,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,13,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,13,6,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,13,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,13,6,1.000000);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,14,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,14,6,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,14,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,14,6,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,14,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,14,6,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,14,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,14,6,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,14,6,2.236068);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,14,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,14,6,2.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,14,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,14,6,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,14,6,2.236068);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,14,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,14,6,1.732051);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,14,6,2.236068);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,14,6,2.236068);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,14,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,14,6,1.732051);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,14,6,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,14,6,3.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,14,6,2.236068);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,14,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,14,6,2.449490);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,14,6,2.236068);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,14,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,14,6,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,14,6,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,14,6,3.162278);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,14,6,2.236068);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,14,6,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,14,6,2.828427);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,14,6,2.236068);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,14,6,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,14,6,2.828427);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,14,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,14,6,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,14,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,14,6,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,14,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,14,6,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,14,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,14,6,2.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,14,6,2.236068);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,14,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,14,6,2.449490);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,14,6,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,14,6,2.828427);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,14,6,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,14,6,3.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,14,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,14,6,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,14,6,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,14,6,3.316625);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,14,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,14,6,1.732051);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,14,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,14,6,2.645751);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,14,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,14,6,2.645751);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,14,6,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,14,6,3.162278);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,14,6,2.236068);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,14,6,2.236068);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,14,6,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,14,6,3.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,14,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,14,6,2.236068);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,14,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,14,6,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,14,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,14,6,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,14,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,14,6,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,14,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,14,6,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,14,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,14,6,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,14,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,14,6,1.414214);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,15,6,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,15,6,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,15,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,15,6,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,15,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,15,6,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,15,6,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,15,6,2.645751);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,15,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,15,6,2.449490);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,15,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,15,6,2.236068);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,15,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,15,6,2.449490);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,15,6,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,15,6,3.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,15,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,15,6,2.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,15,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,15,6,2.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,15,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,15,6,2.449490);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,15,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,15,6,1.732051);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,15,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,15,6,2.449490);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,15,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,15,6,1.414214);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,15,6,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,15,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,15,6,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,15,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,15,6,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,15,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,15,6,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,15,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,15,6,2.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,15,6,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,15,6,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,15,6,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,15,6,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,15,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,15,6,2.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,15,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,15,6,2.236068);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,15,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,15,6,2.236068);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,15,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,15,6,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,15,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,15,6,2.449490);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,15,6,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,15,6,2.449490);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,15,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,15,6,1.732051);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,15,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,15,6,2.236068);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,15,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,15,6,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,15,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,15,6,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,15,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,15,6,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,15,6,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,15,6,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,15,6,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,15,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,15,6,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,15,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,15,6,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,15,6,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,15,6,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,15,6,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,15,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,15,6,1.000000);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,16,6,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,16,6,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,16,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,16,6,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,16,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,16,6,1.732051);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,16,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,16,6,2.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,16,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,16,6,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,16,6,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,16,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,16,6,2.236068);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,16,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,16,6,1.414214);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,16,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,16,6,1.732051);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,16,6,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,16,6,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,16,6,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,16,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,16,6,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,16,6,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,16,6,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,16,6,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,16,6,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,16,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,16,6,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,16,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,16,6,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,16,6,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,16,6,2.236068);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,16,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,16,6,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,16,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,16,6,1.732051);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,16,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,16,6,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,16,6,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,16,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,16,6,1.732051);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,16,6,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,16,6,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,16,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,16,6,1.000000);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,17,6,1.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,17,6,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,17,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,17,6,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,17,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,17,6,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,17,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,17,6,1.414214);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,17,6,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,17,6,3.162278);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,17,6,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,17,6,2.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,17,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,17,6,1.414214);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,17,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,17,6,1.414214);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,17,6,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,17,6,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,17,6,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,17,6,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,17,6,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,17,6,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,17,6,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,17,6,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,17,6,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,17,6,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,17,6,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,17,6,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,17,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,17,6,1.000000);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,18,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,18,6,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,18,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,18,6,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,18,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,18,6,1.414214);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,18,6,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,18,6,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,18,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,18,6,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,18,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,18,6,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,18,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,18,6,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,18,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,18,6,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,19,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,19,6,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,19,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,19,6,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,20,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,20,6,1.000000);

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,21,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,21,6,1.000000);

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,23,6,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,23,6,1.000000);

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 6.500000 to 7.500000

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

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,6,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,6,7,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,6,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,6,7,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,6,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,6,7,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,7,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,7,7,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,7,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,7,7,1.000000);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,8,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,8,7,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,8,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,8,7,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,8,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,8,7,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,8,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,8,7,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,8,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,8,7,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,8,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,8,7,1.000000);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,9,7,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,9,7,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,9,7,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,9,7,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,9,7,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,9,7,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,9,7,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,9,7,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,9,7,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,9,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,9,7,1.732051);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,9,7,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,9,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,9,7,1.732051);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,9,7,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,9,7,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,9,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,9,7,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,9,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,9,7,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,9,7,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,9,7,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,9,7,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,9,7,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,9,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,9,7,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,9,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,9,7,1.000000);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,10,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,10,7,2.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,10,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,10,7,1.732051);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,10,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,10,7,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,10,7,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,10,7,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,10,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,10,7,1.414214);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,10,7,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,10,7,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,10,7,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,10,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,10,7,1.414214);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,10,7,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,10,7,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,10,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,10,7,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,10,7,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,10,7,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,10,7,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,10,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,10,7,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,10,7,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,10,7,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,10,7,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,10,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,10,7,1.414214);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,10,7,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,10,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,10,7,1.732051);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,10,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,10,7,1.414214);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,10,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,10,7,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,10,7,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,10,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,10,7,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,10,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,10,7,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,10,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,10,7,1.000000);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,11,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,11,7,1.732051);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,11,7,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,11,7,2.449490);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,11,7,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,11,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,11,7,1.732051);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,11,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,11,7,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,11,7,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,11,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,11,7,1.732051);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,11,7,1.414214);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,11,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,11,7,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,11,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,11,7,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,11,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,11,7,1.732051);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,11,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,11,7,2.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,11,7,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,11,7,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,11,7,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,11,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,11,7,2.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,11,7,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,11,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,11,7,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,11,7,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,11,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,11,7,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,11,7,1.414214);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,11,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,11,7,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,11,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,11,7,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,11,7,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,11,7,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,11,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,11,7,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,11,7,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,11,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,11,7,2.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,11,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,11,7,1.732051);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,11,7,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,11,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,11,7,1.732051);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,11,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,11,7,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,11,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,11,7,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,11,7,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,11,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,11,7,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,11,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,11,7,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,11,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,11,7,2.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,11,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,11,7,1.414214);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,12,7,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,12,7,2.828427);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,12,7,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,12,7,1.414214);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,12,7,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,12,7,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,12,7,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,12,7,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,12,7,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,12,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,12,7,1.732051);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,12,7,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,12,7,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,12,7,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,12,7,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,12,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,12,7,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,12,7,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,12,7,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,12,7,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,12,7,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,12,7,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,12,7,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,12,7,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,12,7,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,12,7,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,12,7,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,12,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,12,7,1.732051);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,12,7,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,12,7,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,12,7,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,12,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,12,7,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,12,7,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,12,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,12,7,1.732051);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,12,7,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,12,7,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,12,7,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,12,7,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,12,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,12,7,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,12,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,12,7,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,12,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,12,7,1.414214);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,12,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,12,7,1.732051);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,12,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,12,7,1.732051);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,13,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,13,7,1.732051);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,13,7,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,13,7,2.236068);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,13,7,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,13,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,13,7,1.732051);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,13,7,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,13,7,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,13,7,1.414214);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,13,7,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,13,7,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,13,7,1.414214);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,13,7,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,13,7,2.449490);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,13,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,13,7,2.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,13,7,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,13,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,13,7,2.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,13,7,1.414214);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,13,7,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,13,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,13,7,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,13,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,13,7,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,13,7,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,13,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,13,7,1.732051);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,13,7,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,13,7,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,13,7,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,13,7,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,13,7,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,13,7,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,13,7,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,13,7,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,13,7,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,13,7,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,13,7,2.449490);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,13,7,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,13,7,1.414214);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,13,7,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,13,7,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,13,7,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,13,7,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,13,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,13,7,1.732051);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,13,7,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,13,7,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,13,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,13,7,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,13,7,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,13,7,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,13,7,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,13,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,13,7,1.732051);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,13,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,13,7,1.732051);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,13,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,13,7,1.414214);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,14,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,14,7,1.732051);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,14,7,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,14,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,14,7,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,14,7,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,14,7,2.236068);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,14,7,1.414214);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,14,7,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,14,7,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,14,7,1.414214);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,14,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,14,7,1.732051);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,14,7,1.414214);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,14,7,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,14,7,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,14,7,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,14,7,1.414214);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,14,7,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,14,7,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,14,7,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,14,7,2.236068);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,14,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,14,7,1.732051);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,14,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,14,7,2.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,14,7,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,14,7,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,14,7,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,14,7,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,14,7,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,14,7,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,14,7,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,14,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,14,7,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,14,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,14,7,2.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,14,7,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,14,7,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,14,7,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,14,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,14,7,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,14,7,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,14,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,14,7,1.732051);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,14,7,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,14,7,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,14,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,14,7,1.732051);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,14,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,14,7,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,14,7,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,14,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,14,7,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,14,7,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,14,7,2.449490);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,14,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,14,7,1.732051);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,14,7,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,14,7,2.449490);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,15,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,15,7,2.000000);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,15,7,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,15,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,15,7,2.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,15,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,15,7,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,15,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,15,7,1.732051);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,15,7,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,15,7,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,15,7,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,15,7,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,15,7,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,15,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,15,7,1.414214);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,15,7,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,15,7,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,15,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,15,7,2.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,15,7,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,15,7,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,15,7,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,15,7,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,15,7,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,15,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,15,7,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,15,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,15,7,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,15,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,15,7,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,15,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,15,7,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,15,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,15,7,2.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,15,7,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,15,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,15,7,1.414214);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,15,7,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,15,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,15,7,1.732051);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,15,7,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,15,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,15,7,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,15,7,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,15,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,15,7,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,15,7,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,15,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,15,7,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,15,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,15,7,1.000000);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,16,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,16,7,1.732051);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,16,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,16,7,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,16,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,16,7,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,16,7,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,16,7,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,16,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,16,7,1.414214);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,16,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,16,7,1.414214);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,16,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,16,7,1.414214);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,16,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,16,7,1.414214);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,16,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,16,7,1.732051);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,16,7,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,16,7,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,16,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,16,7,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,16,7,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,16,7,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,16,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,16,7,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,16,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,16,7,2.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,16,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,16,7,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,16,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,16,7,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,16,7,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,16,7,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,16,7,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,16,7,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,16,7,2.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,16,7,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,16,7,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,16,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,16,7,1.414214);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,16,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,16,7,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,16,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,16,7,1.414214);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,16,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,16,7,1.732051);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,16,7,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,16,7,1.732051);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,17,7,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,17,7,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,17,7,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,17,7,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,17,7,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,17,7,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,17,7,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,17,7,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,17,7,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,17,7,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,17,7,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,17,7,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,17,7,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,17,7,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,17,7,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,17,7,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,17,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,17,7,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,17,7,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,17,7,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,17,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,17,7,1.000000);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,18,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,18,7,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,18,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,18,7,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,18,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,18,7,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,18,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,18,7,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,18,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,18,7,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,18,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,18,7,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,18,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,18,7,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,18,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,18,7,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,19,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,19,7,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,19,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,19,7,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,19,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,19,7,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,19,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,19,7,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,19,7,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,19,7,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,19,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,19,7,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,19,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,19,7,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,20,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,20,7,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,20,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,20,7,1.000000);

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,26,7,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,26,7,1.000000);

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 7.500000 to 8.500000

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

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,4,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,4,8,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,4,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,4,8,1.000000);

////////////////////////////////////////////////////
// ybin: -0.136000 to -0.120000

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,5,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,5,8,1.000000);

////////////////////////////////////////////////////
// ybin: -0.120000 to -0.104000

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,6,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,6,8,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,6,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,6,8,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,6,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,6,8,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,7,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,7,8,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,7,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,7,8,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,7,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,7,8,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,7,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,7,8,1.414214);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,8,8,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,8,8,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,8,8,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,8,8,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,8,8,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,8,8,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,8,8,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,8,8,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,8,8,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,8,8,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,8,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,8,8,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,8,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,8,8,1.732051);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,9,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,9,8,1.414214);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,9,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,9,8,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,9,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,9,8,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,9,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,9,8,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,9,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,9,8,1.732051);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,9,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,9,8,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,9,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,9,8,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,9,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,9,8,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,9,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,9,8,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,9,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,9,8,2.449490);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,9,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,9,8,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,9,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,9,8,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,9,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,9,8,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,9,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,9,8,1.000000);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,10,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,10,8,1.414214);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,10,8,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,10,8,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,10,8,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,10,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,10,8,1.732051);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,10,8,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,10,8,1.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,10,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,10,8,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,10,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,10,8,1.732051);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,10,8,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,10,8,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,10,8,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,10,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,10,8,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,10,8,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,10,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,10,8,1.732051);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,10,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,10,8,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,10,8,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,10,8,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,10,8,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,10,8,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,10,8,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,10,8,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,10,8,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,10,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,10,8,2.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,10,8,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,10,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,10,8,1.732051);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,10,8,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,10,8,3.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,10,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,10,8,2.449490);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,10,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,10,8,1.414214);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,10,8,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,10,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,10,8,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,10,8,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,10,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,10,8,1.414214);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,10,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,10,8,1.000000);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,11,8,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,11,8,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,11,8,1.414214);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,11,8,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,11,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,11,8,2.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,11,8,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,11,8,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,11,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,11,8,2.449490);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,11,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,11,8,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,11,8,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,11,8,1.414214);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,11,8,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,11,8,1.414214);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,11,8,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,11,8,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,11,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,11,8,2.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,11,8,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,11,8,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,11,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,11,8,1.732051);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,11,8,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,11,8,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,11,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,11,8,2.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,11,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,11,8,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,11,8,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,11,8,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,11,8,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,11,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,11,8,1.732051);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,11,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,11,8,2.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,11,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,11,8,1.732051);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,11,8,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,11,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,11,8,1.732051);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,11,8,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,11,8,3.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,11,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,11,8,2.236068);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,11,8,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,11,8,3.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,11,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,11,8,2.645751);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,11,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,11,8,2.449490);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,11,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,11,8,1.414214);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,11,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,11,8,2.645751);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,11,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,11,8,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,11,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,11,8,1.732051);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,11,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,11,8,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,11,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,11,8,1.732051);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,12,8,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,12,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,12,8,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,12,8,1.732051);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,12,8,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,12,8,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,12,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,12,8,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,12,8,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,12,8,1.414214);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,12,8,1.732051);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,12,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,12,8,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,12,8,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,12,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,12,8,2.449490);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,12,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,12,8,2.645751);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,12,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,12,8,2.449490);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,12,8,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,12,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,12,8,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,12,8,1.414214);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,12,8,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,12,8,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,12,8,3.162278);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,12,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,12,8,2.449490);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,12,8,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,12,8,2.828427);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,12,8,1.732051);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,12,8,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,12,8,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,12,8,1.732051);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,12,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,12,8,2.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,12,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,12,8,2.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,12,8,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,12,8,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,12,8,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,12,8,1.732051);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,12,8,1.732051);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,12,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,12,8,2.449490);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,12,8,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,12,8,2.828427);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,12,8,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,12,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,12,8,1.414214);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,12,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,12,8,2.236068);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,12,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,12,8,2.645751);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,12,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,12,8,2.449490);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,12,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,12,8,2.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,12,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,12,8,2.449490);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,12,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,12,8,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,12,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,12,8,2.449490);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,12,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,12,8,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,12,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,12,8,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,12,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,12,8,2.236068);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,12,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,12,8,1.732051);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,13,8,2.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,13,8,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,13,8,2.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,13,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,13,8,2.236068);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,13,8,2.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,13,8,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,13,8,2.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,13,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,13,8,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,13,8,2.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,13,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,13,8,2.236068);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,13,8,2.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,13,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,13,8,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,13,8,2.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,13,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,13,8,2.449490);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,13,8,1.732051);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,13,8,2.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,13,8,1.732051);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,13,8,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,13,8,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,13,8,2.828427);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,13,8,2.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,13,8,1.732051);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,13,8,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,13,8,1.732051);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,13,8,2.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,13,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,13,8,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,13,8,1.732051);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,13,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,13,8,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,13,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,13,8,2.449490);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,13,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,13,8,2.449490);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,13,8,2.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,13,8,2.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,13,8,1.732051);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,13,8,1.732051);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,13,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,13,8,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,13,8,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,13,8,2.828427);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,13,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,13,8,2.645751);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,13,8,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,13,8,2.828427);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,13,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,13,8,2.645751);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,13,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,13,8,2.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,13,8,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,13,8,2.828427);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,13,8,1.732051);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,13,8,1.732051);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,13,8,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,13,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,13,8,2.449490);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,13,8,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,13,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,13,8,1.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,13,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,13,8,1.732051);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,13,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,13,8,1.000000);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,14,8,1.732051);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,14,8,1.732051);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,14,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,14,8,2.236068);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,14,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,14,8,2.449490);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,14,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,14,8,2.236068);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,14,8,2.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,14,8,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,14,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,14,8,2.449490);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,14,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,14,8,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,14,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,14,8,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,14,8,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,14,8,3.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,14,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,14,8,2.645751);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,14,8,2.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,14,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,14,8,2.236068);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,14,8,2.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,14,8,2.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,14,8,2.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,14,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,14,8,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,14,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,14,8,2.236068);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,14,8,1.732051);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,14,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,14,8,2.449490);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,14,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,14,8,2.645751);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,14,8,2.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,14,8,2.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,14,8,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,14,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,14,8,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,14,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,14,8,2.236068);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,14,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,14,8,2.449490);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,14,8,2.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,14,8,1.732051);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,14,8,2.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,14,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,14,8,2.236068);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,14,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,14,8,2.236068);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,14,8,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,14,8,3.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,14,8,2.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,14,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,14,8,2.236068);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,14,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,14,8,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,14,8,2.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,14,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,14,8,2.645751);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,14,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,14,8,2.645751);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,14,8,1.732051);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,14,8,1.732051);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,14,8,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,14,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,14,8,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,14,8,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,14,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,14,8,2.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,14,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,14,8,1.732051);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,14,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,14,8,1.000000);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,15,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,15,8,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,15,8,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,15,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,15,8,2.645751);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,15,8,1.732051);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,15,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,15,8,1.414214);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,15,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,15,8,2.449490);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,15,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,15,8,2.236068);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,15,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,15,8,1.414214);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,15,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,15,8,2.236068);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,15,8,1.732051);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,15,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,15,8,1.414214);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,15,8,1.732051);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,15,8,1.732051);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,15,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,15,8,2.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,15,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,15,8,2.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,15,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,15,8,2.449490);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,15,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,15,8,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,15,8,1.732051);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,15,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,15,8,2.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,15,8,1.732051);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,15,8,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,15,8,2.645751);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,15,8,1.732051);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,15,8,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,15,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,15,8,2.449490);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,15,8,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,15,8,3.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,15,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,15,8,2.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,15,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,15,8,2.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,15,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,15,8,2.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,15,8,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,15,8,1.732051);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,15,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,15,8,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,15,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,15,8,2.236068);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,15,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,15,8,2.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,15,8,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,15,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,15,8,1.414214);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,15,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,15,8,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,15,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,15,8,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,15,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,15,8,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,15,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,15,8,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,15,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,15,8,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,15,8,1.732051);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,15,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,15,8,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,15,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,15,8,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,15,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,15,8,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,15,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,15,8,1.000000);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,16,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,16,8,1.732051);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,16,8,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,16,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,16,8,2.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,16,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,16,8,2.449490);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,16,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,16,8,2.449490);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,16,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,16,8,2.449490);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,16,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,16,8,2.449490);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,16,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,16,8,2.449490);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,16,8,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,16,8,2.449490);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,16,8,1.414214);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,16,8,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,16,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,16,8,1.732051);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,16,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,16,8,1.732051);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,16,8,1.414214);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,16,8,1.414214);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,16,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,16,8,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,16,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,16,8,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,16,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,16,8,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,16,8,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,16,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,16,8,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,16,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,16,8,2.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,16,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,16,8,2.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,16,8,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,16,8,2.236068);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,16,8,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,16,8,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,16,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,16,8,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,16,8,1.414214);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,16,8,1.414214);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,16,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,16,8,1.732051);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,16,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,16,8,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,16,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,16,8,2.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,16,8,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,16,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,16,8,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,16,8,1.414214);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,16,8,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,16,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,16,8,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,16,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,16,8,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,16,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,16,8,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,16,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,16,8,1.000000);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,17,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,17,8,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,17,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,17,8,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,17,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,17,8,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,17,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,17,8,1.414214);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,17,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,17,8,1.732051);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,17,8,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,17,8,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,17,8,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,17,8,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,17,8,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,17,8,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,17,8,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,17,8,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,17,8,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,17,8,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,17,8,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,17,8,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,17,8,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,17,8,2.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,17,8,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,17,8,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,17,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,17,8,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,17,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,17,8,1.414214);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,18,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,18,8,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,18,8,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,18,8,1.414214);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,18,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,18,8,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,18,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,18,8,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,18,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,18,8,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,18,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,18,8,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,18,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,18,8,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,18,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,18,8,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,19,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,19,8,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,19,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,19,8,1.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,19,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,19,8,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,22,8,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,22,8,1.000000);

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: 8.500000 to 9.500000

////////////////////////////////////////////////////
// ybin: under -0.200000

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,0,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,0,9,1.000000);

////////////////////////////////////////////////////
// ybin: -0.200000 to -0.184000

////////////////////////////////////////////////////
// ybin: -0.184000 to -0.168000

////////////////////////////////////////////////////
// ybin: -0.168000 to -0.152000

////////////////////////////////////////////////////
// ybin: -0.152000 to -0.136000

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,4,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,4,9,1.000000);

////////////////////////////////////////////////////
// ybin: -0.136000 to -0.120000

////////////////////////////////////////////////////
// ybin: -0.120000 to -0.104000

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,6,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,6,9,1.000000);

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,7,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,7,9,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,7,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,7,9,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,7,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,7,9,1.000000);

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,8,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,8,9,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,8,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,8,9,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,8,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,8,9,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,8,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,8,9,1.414214);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,8,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,8,9,1.000000);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,8,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,8,9,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,8,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,8,9,1.000000);

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,9,9,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,9,9,1.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,9,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,9,9,1.414214);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,9,9,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,9,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,9,9,1.414214);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,9,9,1.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,9,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,9,9,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,9,9,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,9,9,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,9,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,9,9,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,9,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,9,9,1.414214);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,9,9,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,9,9,1.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,9,9,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,9,9,1.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,9,9,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,9,9,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,9,9,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,9,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,9,9,1.732051);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,9,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,9,9,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,9,9,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,9,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,9,9,1.000000);

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,10,9,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,10,9,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,10,9,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,10,9,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,10,9,1.414214);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,10,9,1.414214);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,10,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,10,9,2.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,10,9,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,10,9,1.414214);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,10,9,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,10,9,1.414214);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,10,9,1.414214);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,10,9,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,10,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,10,9,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,10,9,1.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,10,9,1.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,10,9,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,10,9,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,10,9,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,10,9,1.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,10,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,10,9,1.732051);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,10,9,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,10,9,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,10,9,1.000000);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,10,9,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,10,9,1.414214);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,10,9,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,10,9,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,10,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,10,9,2.449490);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,10,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,10,9,2.449490);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,10,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,10,9,2.645751);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,10,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,10,9,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,10,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,10,9,1.732051);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,10,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,10,9,1.000000);

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,11,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,11,9,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,11,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,11,9,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,11,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,11,9,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,11,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,11,9,1.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,11,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,11,9,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,11,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,11,9,2.236068);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,11,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,11,9,2.236068);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,11,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,11,9,2.449490);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,11,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,11,9,2.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,11,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,11,9,2.449490);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,11,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,11,9,2.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,11,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,11,9,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,11,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,11,9,2.449490);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,11,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,11,9,2.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,11,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,11,9,2.449490);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,11,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,11,9,2.449490);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,11,9,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,11,9,3.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,11,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,11,9,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,11,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,11,9,2.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,11,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,11,9,2.000000);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,11,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,11,9,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,11,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,11,9,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,11,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,11,9,1.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,11,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,11,9,2.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,11,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,11,9,1.000000);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,11,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,11,9,2.236068);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,11,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,11,9,1.732051);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,11,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,11,9,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,11,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,11,9,2.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,11,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,11,9,1.414214);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,11,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,11,9,2.645751);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,11,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,11,9,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,11,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,11,9,2.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,11,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,11,9,1.414214);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,11,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,11,9,1.732051);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,11,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,11,9,2.828427);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,11,9,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,11,9,3.162278);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,11,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,11,9,2.828427);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,11,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,11,9,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,11,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,11,9,2.236068);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,11,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,11,9,1.000000);

// xbin: 0.980000 to 1.000000
em_shift_vs_phimod_ptetabin->SetBinContent(50,11,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(50,11,9,1.732051);

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,12,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,12,9,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,12,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,12,9,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,12,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,12,9,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,12,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,12,9,2.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,12,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,12,9,2.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,12,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,12,9,1.732051);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,12,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,12,9,2.449490);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,12,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,12,9,2.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,12,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,12,9,2.449490);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,12,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,12,9,2.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,12,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,12,9,1.732051);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,12,9,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,12,9,3.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,12,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,12,9,2.449490);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,12,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,12,9,2.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,12,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,12,9,2.236068);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,12,9,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,12,9,3.316625);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,12,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,12,9,2.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,12,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,12,9,1.414214);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,12,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,12,9,2.449490);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,12,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,12,9,2.236068);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,12,9,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,12,9,3.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,12,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,12,9,2.236068);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,12,9,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,12,9,3.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,12,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,12,9,1.414214);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,12,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,12,9,1.414214);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,12,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,12,9,2.236068);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,12,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,12,9,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,12,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,12,9,2.236068);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,12,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,12,9,2.645751);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,12,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,12,9,2.236068);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,12,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,12,9,2.449490);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,12,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,12,9,2.828427);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,12,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,12,9,2.645751);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,12,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,12,9,2.449490);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,12,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,12,9,2.828427);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,12,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,12,9,2.449490);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,12,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,12,9,2.828427);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,12,9,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,12,9,3.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,12,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,12,9,2.236068);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,12,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,12,9,2.236068);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,12,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,12,9,2.449490);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,12,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,12,9,2.828427);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,12,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,12,9,2.828427);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,12,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,12,9,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,12,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,12,9,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,12,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,12,9,1.000000);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,12,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,12,9,1.414214);

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,13,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,13,9,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,13,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,13,9,2.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,13,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,13,9,1.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,13,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,13,9,2.449490);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,13,9,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,13,9,3.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,13,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,13,9,1.732051);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,13,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,13,9,2.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,13,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,13,9,2.828427);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,13,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,13,9,2.236068);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,13,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,13,9,2.449490);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,13,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,13,9,2.236068);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,13,9,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,13,9,3.000000);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,13,9,16.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,13,9,4.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,13,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,13,9,2.645751);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,13,9,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,13,9,3.162278);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,13,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,13,9,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,13,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,13,9,2.449490);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,13,9,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,13,9,3.316625);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,13,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,13,9,1.732051);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,13,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,13,9,2.645751);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,13,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,13,9,2.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,13,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,13,9,2.645751);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,13,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,13,9,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,13,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,13,9,2.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,13,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,13,9,2.236068);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,13,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,13,9,1.732051);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,13,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,13,9,2.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,13,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,13,9,2.828427);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,13,9,11.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,13,9,3.316625);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,13,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,13,9,2.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,13,9,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,13,9,3.162278);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,13,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,13,9,2.828427);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,13,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,13,9,2.645751);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,13,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,13,9,2.645751);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,13,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,13,9,2.645751);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,13,9,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,13,9,3.162278);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,13,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,13,9,2.828427);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,13,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,13,9,2.828427);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,13,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,13,9,2.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,13,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,13,9,2.828427);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,13,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,13,9,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,13,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,13,9,2.236068);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,13,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,13,9,2.449490);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,13,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,13,9,2.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,13,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,13,9,2.000000);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,13,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,13,9,1.732051);

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,14,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,14,9,1.732051);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,14,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,14,9,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,14,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,14,9,2.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,14,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,14,9,1.000000);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,14,9,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,14,9,3.162278);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,14,9,2.236068);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,14,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,14,9,2.449490);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,14,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,14,9,2.449490);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,14,9,2.236068);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,14,9,2.236068);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,14,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,14,9,2.828427);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,14,9,2.236068);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,14,9,2.236068);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,14,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,14,9,2.645751);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,14,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,14,9,2.645751);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,14,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,14,9,2.645751);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,14,9,2.236068);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,14,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,14,9,2.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,14,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,14,9,2.449490);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,14,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,14,9,2.449490);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,14,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,14,9,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,14,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,14,9,2.000000);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,14,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,14,9,1.732051);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,14,9,2.236068);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,14,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,14,9,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,14,9,2.236068);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,14,9,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,14,9,3.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,14,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,14,9,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,14,9,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,14,9,3.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,14,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,14,9,2.828427);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,14,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,14,9,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,14,9,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,14,9,3.162278);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,14,9,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,14,9,3.162278);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,14,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,14,9,2.000000);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,14,9,8.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,14,9,2.828427);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,14,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,14,9,1.732051);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,14,9,2.236068);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,14,9,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,14,9,3.162278);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,14,9,2.236068);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,14,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,14,9,2.236068);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,14,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,14,9,2.000000);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,14,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,14,9,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,14,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,14,9,1.414214);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,14,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,14,9,1.414214);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,14,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,14,9,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,14,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,14,9,1.414214);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,14,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,14,9,1.732051);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,14,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,14,9,1.732051);

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,15,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,15,9,1.414214);

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,15,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,15,9,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,15,9,2.236068);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,15,9,10.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,15,9,3.162278);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,15,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,15,9,2.449490);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,15,9,1.732051);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,15,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,15,9,2.449490);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,15,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,15,9,2.645751);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,15,9,2.236068);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,15,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,15,9,2.645751);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,15,9,1.732051);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,15,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,15,9,2.000000);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,15,9,2.236068);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,15,9,1.732051);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,15,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,15,9,1.000000);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,15,9,1.732051);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,15,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,15,9,2.645751);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,15,9,1.732051);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,15,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,15,9,2.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,15,9,1.732051);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,15,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,15,9,1.414214);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,15,9,1.732051);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,15,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,15,9,2.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,15,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,15,9,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,15,9,2.236068);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,15,9,1.732051);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,15,9,2.236068);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,15,9,2.236068);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,15,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,15,9,2.000000);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,15,9,1.732051);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,15,9,1.732051);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,15,9,7.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,15,9,2.645751);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,15,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,15,9,2.449490);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,15,9,2.236068);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,15,9,1.732051);

// xbin: 0.700000 to 0.720000
em_shift_vs_phimod_ptetabin->SetBinContent(36,15,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(36,15,9,2.000000);

// xbin: 0.720000 to 0.740000
em_shift_vs_phimod_ptetabin->SetBinContent(37,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(37,15,9,2.236068);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,15,9,2.236068);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,15,9,2.236068);

// xbin: 0.780000 to 0.800000
em_shift_vs_phimod_ptetabin->SetBinContent(40,15,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(40,15,9,2.236068);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,15,9,1.732051);

// xbin: 0.820000 to 0.840000
em_shift_vs_phimod_ptetabin->SetBinContent(42,15,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(42,15,9,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,15,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,15,9,1.000000);

// xbin: 0.860000 to 0.880000
em_shift_vs_phimod_ptetabin->SetBinContent(44,15,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(44,15,9,1.000000);

// xbin: 0.880000 to 0.900000
em_shift_vs_phimod_ptetabin->SetBinContent(45,15,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(45,15,9,1.732051);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,15,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,15,9,1.000000);

// xbin: 0.920000 to 0.940000
em_shift_vs_phimod_ptetabin->SetBinContent(47,15,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(47,15,9,1.414214);

// xbin: 0.940000 to 0.960000
em_shift_vs_phimod_ptetabin->SetBinContent(48,15,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(48,15,9,1.000000);

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

// xbin: 0.020000 to 0.040000
em_shift_vs_phimod_ptetabin->SetBinContent(2,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(2,16,9,1.414214);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,16,9,1.414214);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,16,9,6.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,16,9,2.449490);

// xbin: 0.080000 to 0.100000
em_shift_vs_phimod_ptetabin->SetBinContent(5,16,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(5,16,9,2.000000);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,16,9,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,16,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,16,9,2.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,16,9,1.414214);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,16,9,1.000000);

// xbin: 0.180000 to 0.200000
em_shift_vs_phimod_ptetabin->SetBinContent(10,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(10,16,9,1.000000);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,16,9,1.414214);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,16,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,16,9,2.236068);

// xbin: 0.240000 to 0.260000
em_shift_vs_phimod_ptetabin->SetBinContent(13,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(13,16,9,1.414214);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,16,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,16,9,1.732051);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,16,9,1.414214);

// xbin: 0.300000 to 0.320000
em_shift_vs_phimod_ptetabin->SetBinContent(16,16,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(16,16,9,2.000000);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,16,9,1.000000);

// xbin: 0.340000 to 0.360000
em_shift_vs_phimod_ptetabin->SetBinContent(18,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(18,16,9,1.000000);

// xbin: 0.360000 to 0.380000
em_shift_vs_phimod_ptetabin->SetBinContent(19,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(19,16,9,1.000000);

// xbin: 0.380000 to 0.400000
em_shift_vs_phimod_ptetabin->SetBinContent(20,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(20,16,9,1.000000);

// xbin: 0.420000 to 0.440000
em_shift_vs_phimod_ptetabin->SetBinContent(22,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(22,16,9,1.414214);

// xbin: 0.440000 to 0.460000
em_shift_vs_phimod_ptetabin->SetBinContent(23,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(23,16,9,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,16,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,16,9,1.732051);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,16,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,16,9,1.732051);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,16,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,16,9,2.236068);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,16,9,9.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,16,9,3.000000);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,16,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,16,9,1.732051);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,16,9,1.414214);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,16,9,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,16,9,4.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,16,9,2.000000);

// xbin: 0.620000 to 0.640000
em_shift_vs_phimod_ptetabin->SetBinContent(32,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(32,16,9,1.000000);

// xbin: 0.640000 to 0.660000
em_shift_vs_phimod_ptetabin->SetBinContent(33,16,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(33,16,9,1.732051);

// xbin: 0.660000 to 0.680000
em_shift_vs_phimod_ptetabin->SetBinContent(34,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(34,16,9,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,16,9,1.000000);

// xbin: 0.760000 to 0.780000
em_shift_vs_phimod_ptetabin->SetBinContent(39,16,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(39,16,9,1.414214);

// xbin: 0.960000 to 0.980000
em_shift_vs_phimod_ptetabin->SetBinContent(49,16,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(49,16,9,1.000000);

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,17,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,17,9,1.000000);

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,17,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,17,9,1.732051);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,17,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,17,9,1.414214);

// xbin: 0.100000 to 0.120000
em_shift_vs_phimod_ptetabin->SetBinContent(6,17,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(6,17,9,1.000000);

// xbin: 0.120000 to 0.140000
em_shift_vs_phimod_ptetabin->SetBinContent(7,17,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(7,17,9,1.732051);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,17,9,5.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,17,9,2.236068);

// xbin: 0.200000 to 0.220000
em_shift_vs_phimod_ptetabin->SetBinContent(11,17,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(11,17,9,1.732051);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,17,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,17,9,1.000000);

// xbin: 0.260000 to 0.280000
em_shift_vs_phimod_ptetabin->SetBinContent(14,17,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(14,17,9,1.414214);

// xbin: 0.280000 to 0.300000
em_shift_vs_phimod_ptetabin->SetBinContent(15,17,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(15,17,9,1.000000);

// xbin: 0.460000 to 0.480000
em_shift_vs_phimod_ptetabin->SetBinContent(24,17,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(24,17,9,1.000000);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,17,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,17,9,1.000000);

// xbin: 0.520000 to 0.540000
em_shift_vs_phimod_ptetabin->SetBinContent(27,17,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(27,17,9,1.414214);

// xbin: 0.540000 to 0.560000
em_shift_vs_phimod_ptetabin->SetBinContent(28,17,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(28,17,9,1.414214);

// xbin: 0.560000 to 0.580000
em_shift_vs_phimod_ptetabin->SetBinContent(29,17,9,3.000000);
em_shift_vs_phimod_ptetabin->SetBinError(29,17,9,1.732051);

// xbin: 0.580000 to 0.600000
em_shift_vs_phimod_ptetabin->SetBinContent(30,17,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(30,17,9,1.414214);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,17,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,17,9,1.414214);

// xbin: 0.680000 to 0.700000
em_shift_vs_phimod_ptetabin->SetBinContent(35,17,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(35,17,9,1.000000);

// xbin: 0.740000 to 0.760000
em_shift_vs_phimod_ptetabin->SetBinContent(38,17,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(38,17,9,1.000000);

// xbin: 0.800000 to 0.820000
em_shift_vs_phimod_ptetabin->SetBinContent(41,17,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(41,17,9,1.000000);

// xbin: 0.840000 to 0.860000
em_shift_vs_phimod_ptetabin->SetBinContent(43,17,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(43,17,9,1.000000);

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,18,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,18,9,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,18,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,18,9,1.000000);

// xbin: 0.140000 to 0.160000
em_shift_vs_phimod_ptetabin->SetBinContent(8,18,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(8,18,9,1.000000);

// xbin: 0.160000 to 0.180000
em_shift_vs_phimod_ptetabin->SetBinContent(9,18,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(9,18,9,1.000000);

// xbin: 0.220000 to 0.240000
em_shift_vs_phimod_ptetabin->SetBinContent(12,18,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(12,18,9,1.414214);

// xbin: 0.320000 to 0.340000
em_shift_vs_phimod_ptetabin->SetBinContent(17,18,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(17,18,9,1.000000);

// xbin: 0.400000 to 0.420000
em_shift_vs_phimod_ptetabin->SetBinContent(21,18,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(21,18,9,1.000000);

// xbin: 0.480000 to 0.500000
em_shift_vs_phimod_ptetabin->SetBinContent(25,18,9,2.000000);
em_shift_vs_phimod_ptetabin->SetBinError(25,18,9,1.414214);

// xbin: 0.500000 to 0.520000
em_shift_vs_phimod_ptetabin->SetBinContent(26,18,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(26,18,9,1.000000);

// xbin: 0.600000 to 0.620000
em_shift_vs_phimod_ptetabin->SetBinContent(31,18,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(31,18,9,1.000000);

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

// xbin: 0.040000 to 0.060000
em_shift_vs_phimod_ptetabin->SetBinContent(3,19,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(3,19,9,1.000000);

// xbin: 0.060000 to 0.080000
em_shift_vs_phimod_ptetabin->SetBinContent(4,19,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(4,19,9,1.000000);

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

// xbin: 0.000000 to 0.020000
em_shift_vs_phimod_ptetabin->SetBinContent(1,21,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(1,21,9,1.000000);

// xbin: 0.900000 to 0.920000
em_shift_vs_phimod_ptetabin->SetBinContent(46,21,9,1.000000);
em_shift_vs_phimod_ptetabin->SetBinError(46,21,9,1.000000);

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000

////////////////////////////////////////////////////
////////////////////////////////////////////////////
// zbin: over 9.500000

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

////////////////////////////////////////////////////
// ybin: -0.104000 to -0.088000

////////////////////////////////////////////////////
// ybin: -0.088000 to -0.072000

////////////////////////////////////////////////////
// ybin: -0.072000 to -0.056000

////////////////////////////////////////////////////
// ybin: -0.056000 to -0.040000

////////////////////////////////////////////////////
// ybin: -0.040000 to -0.024000

////////////////////////////////////////////////////
// ybin: -0.024000 to -0.008000

////////////////////////////////////////////////////
// ybin: -0.008000 to 0.008000

////////////////////////////////////////////////////
// ybin: 0.008000 to 0.024000

////////////////////////////////////////////////////
// ybin: 0.024000 to 0.040000

////////////////////////////////////////////////////
// ybin: 0.040000 to 0.056000

////////////////////////////////////////////////////
// ybin: 0.056000 to 0.072000

////////////////////////////////////////////////////
// ybin: 0.072000 to 0.088000

////////////////////////////////////////////////////
// ybin: 0.088000 to 0.104000

////////////////////////////////////////////////////
// ybin: 0.104000 to 0.120000

////////////////////////////////////////////////////
// ybin: 0.120000 to 0.136000

////////////////////////////////////////////////////
// ybin: 0.136000 to 0.152000

////////////////////////////////////////////////////
// ybin: 0.152000 to 0.168000

////////////////////////////////////////////////////
// ybin: 0.168000 to 0.184000

////////////////////////////////////////////////////
// ybin: 0.184000 to 0.200000

////////////////////////////////////////////////////
// ybin: over 0.200000
}
