{
const int n_hPhiCrackEff_xbins = 50;
float hPhiCrackEff_xbins[n_hPhiCrackEff_xbins+1] = {0.000000 ,0.020000 ,0.040000 ,0.060000 ,0.080000 ,0.100000 ,0.120000 ,0.140000 ,0.160000 ,0.180000 ,0.200000 ,0.220000 ,0.240000 ,0.260000 ,0.280000 ,0.300000 ,0.320000 ,0.340000 ,0.360000 ,0.380000 ,0.400000 ,0.420000 ,0.440000 ,0.460000 ,0.480000 ,0.500000 ,0.520000 ,0.540000 ,0.560000 ,0.580000 ,0.600000 ,0.620000 ,0.640000 ,0.660000 ,0.680000 ,0.700000 ,0.720000 ,0.740000 ,0.760000 ,0.780000 ,0.800000 ,0.820000 ,0.840000 ,0.860000 ,0.880000 ,0.900000 ,0.920000 ,0.940000 ,0.960000 ,0.980000 ,1.000000  };

const int n_hPhiCrackEff_ybins = 4;
float hPhiCrackEff_ybins[n_hPhiCrackEff_ybins+1] = {-1.300000 ,-0.500000 ,0.000000 ,0.500000 ,1.300000  };

TH2F *hPhiCrackEff = new TH2F("hPhiCrackEff","presel eff vs phimod and deteta", n_hPhiCrackEff_xbins, hPhiCrackEff_xbins, n_hPhiCrackEff_ybins, hPhiCrackEff_ybins);

////////////////////////////////////////////////////
// ybin: under -1.300000

////////////////////////////////////////////////////
// ybin: -1.300000 to -0.500000

// xbin: 0.000000 to 0.020000
hPhiCrackEff->SetBinContent(1,1,0.666667);
hPhiCrackEff->SetBinError(1,1,0.079111);

// xbin: 0.020000 to 0.040000
hPhiCrackEff->SetBinContent(2,1,0.780000);
hPhiCrackEff->SetBinError(2,1,0.068099);

// xbin: 0.040000 to 0.060000
hPhiCrackEff->SetBinContent(3,1,0.948718);
hPhiCrackEff->SetBinError(3,1,0.060084);

// xbin: 0.060000 to 0.080000
hPhiCrackEff->SetBinContent(4,1,0.944444);
hPhiCrackEff->SetBinError(4,1,0.034112);

// xbin: 0.080000 to 0.100000
hPhiCrackEff->SetBinContent(5,1,0.982759);
hPhiCrackEff->SetBinError(5,1,0.039363);

// xbin: 0.100000 to 0.120000
hPhiCrackEff->SetBinContent(6,1,1.022222);
hPhiCrackEff->SetBinError(6,1,0.042108);

// xbin: 0.120000 to 0.140000
hPhiCrackEff->SetBinContent(7,1,1.022222);
hPhiCrackEff->SetBinError(7,1,0.029775);

// xbin: 0.140000 to 0.160000
hPhiCrackEff->SetBinContent(8,1,1.075000);
hPhiCrackEff->SetBinError(8,1,0.049860);

// xbin: 0.160000 to 0.180000
hPhiCrackEff->SetBinContent(9,1,1.000000);
hPhiCrackEff->SetBinError(9,1,0.065391);

// xbin: 0.180000 to 0.200000
hPhiCrackEff->SetBinContent(10,1,0.921053);
hPhiCrackEff->SetBinError(10,1,0.064581);

// xbin: 0.200000 to 0.220000
hPhiCrackEff->SetBinContent(11,1,1.037736);
hPhiCrackEff->SetBinError(11,1,0.031871);

// xbin: 0.220000 to 0.240000
hPhiCrackEff->SetBinContent(12,1,0.978261);
hPhiCrackEff->SetBinError(12,1,0.039948);

// xbin: 0.240000 to 0.260000
hPhiCrackEff->SetBinContent(13,1,1.023810);
hPhiCrackEff->SetBinError(13,1,0.031782);

// xbin: 0.260000 to 0.280000
hPhiCrackEff->SetBinContent(14,1,0.943396);
hPhiCrackEff->SetBinError(14,1,0.048176);

// xbin: 0.280000 to 0.300000
hPhiCrackEff->SetBinContent(15,1,0.981481);
hPhiCrackEff->SetBinError(15,1,0.034450);

// xbin: 0.300000 to 0.320000
hPhiCrackEff->SetBinContent(16,1,0.949153);
hPhiCrackEff->SetBinError(16,1,0.043724);

// xbin: 0.320000 to 0.340000
hPhiCrackEff->SetBinContent(17,1,0.954545);
hPhiCrackEff->SetBinError(17,1,0.039466);

// xbin: 0.340000 to 0.360000
hPhiCrackEff->SetBinContent(18,1,1.000000);
hPhiCrackEff->SetBinError(18,1,0.049498);

// xbin: 0.360000 to 0.380000
hPhiCrackEff->SetBinContent(19,1,1.024390);
hPhiCrackEff->SetBinError(19,1,0.045980);

// xbin: 0.380000 to 0.400000
hPhiCrackEff->SetBinContent(20,1,1.000000);
hPhiCrackEff->SetBinError(20,1,0.065391);

// xbin: 0.400000 to 0.420000
hPhiCrackEff->SetBinContent(21,1,0.979592);
hPhiCrackEff->SetBinError(21,1,0.026918);

// xbin: 0.420000 to 0.440000
hPhiCrackEff->SetBinContent(22,1,0.888889);
hPhiCrackEff->SetBinError(22,1,0.048975);

// xbin: 0.440000 to 0.460000
hPhiCrackEff->SetBinContent(23,1,1.021277);
hPhiCrackEff->SetBinError(23,1,0.049487);

// xbin: 0.460000 to 0.480000
hPhiCrackEff->SetBinContent(24,1,0.980392);
hPhiCrackEff->SetBinError(24,1,0.036325);

// xbin: 0.480000 to 0.500000
hPhiCrackEff->SetBinContent(25,1,0.978723);
hPhiCrackEff->SetBinError(25,1,0.047803);

// xbin: 0.500000 to 0.520000
hPhiCrackEff->SetBinContent(26,1,1.000000);
hPhiCrackEff->SetBinError(26,1,0.046176);

// xbin: 0.520000 to 0.540000
hPhiCrackEff->SetBinContent(27,1,0.985075);
hPhiCrackEff->SetBinError(27,1,0.028151);

// xbin: 0.540000 to 0.560000
hPhiCrackEff->SetBinContent(28,1,0.958333);
hPhiCrackEff->SetBinError(28,1,0.042413);

// xbin: 0.560000 to 0.580000
hPhiCrackEff->SetBinContent(29,1,1.000000);
hPhiCrackEff->SetBinError(29,1,0.045242);

// xbin: 0.580000 to 0.600000
hPhiCrackEff->SetBinContent(30,1,1.041667);
hPhiCrackEff->SetBinError(30,1,0.035100);

// xbin: 0.600000 to 0.620000
hPhiCrackEff->SetBinContent(31,1,0.967742);
hPhiCrackEff->SetBinError(31,1,0.033528);

// xbin: 0.620000 to 0.640000
hPhiCrackEff->SetBinContent(32,1,0.945455);
hPhiCrackEff->SetBinError(32,1,0.046595);

// xbin: 0.640000 to 0.660000
hPhiCrackEff->SetBinContent(33,1,0.981132);
hPhiCrackEff->SetBinError(33,1,0.049343);

// xbin: 0.660000 to 0.680000
hPhiCrackEff->SetBinContent(34,1,1.000000);
hPhiCrackEff->SetBinError(34,1,0.043768);

// xbin: 0.680000 to 0.700000
hPhiCrackEff->SetBinContent(35,1,0.943396);
hPhiCrackEff->SetBinError(35,1,0.041983);

// xbin: 0.700000 to 0.720000
hPhiCrackEff->SetBinContent(36,1,1.000000);
hPhiCrackEff->SetBinError(36,1,0.049224);

// xbin: 0.720000 to 0.740000
hPhiCrackEff->SetBinContent(37,1,1.018868);
hPhiCrackEff->SetBinError(37,1,0.025482);

// xbin: 0.740000 to 0.760000
hPhiCrackEff->SetBinContent(38,1,0.924528);
hPhiCrackEff->SetBinError(38,1,0.038416);

// xbin: 0.760000 to 0.780000
hPhiCrackEff->SetBinContent(39,1,0.957447);
hPhiCrackEff->SetBinError(39,1,0.043231);

// xbin: 0.780000 to 0.800000
hPhiCrackEff->SetBinContent(40,1,0.962963);
hPhiCrackEff->SetBinError(40,1,0.055986);

// xbin: 0.800000 to 0.820000
hPhiCrackEff->SetBinContent(41,1,1.050000);
hPhiCrackEff->SetBinError(41,1,0.041889);

// xbin: 0.820000 to 0.840000
hPhiCrackEff->SetBinContent(42,1,1.050000);
hPhiCrackEff->SetBinError(42,1,0.053995);

// xbin: 0.840000 to 0.860000
hPhiCrackEff->SetBinContent(43,1,1.000000);
hPhiCrackEff->SetBinError(43,1,0.046053);

// xbin: 0.860000 to 0.880000
hPhiCrackEff->SetBinContent(44,1,1.018868);
hPhiCrackEff->SetBinError(44,1,0.044137);

// xbin: 0.880000 to 0.900000
hPhiCrackEff->SetBinContent(45,1,0.977778);
hPhiCrackEff->SetBinError(45,1,0.040761);

// xbin: 0.900000 to 0.920000
hPhiCrackEff->SetBinContent(46,1,1.066667);
hPhiCrackEff->SetBinError(46,1,0.054130);

// xbin: 0.920000 to 0.940000
hPhiCrackEff->SetBinContent(47,1,0.906977);
hPhiCrackEff->SetBinError(47,1,0.072116);

// xbin: 0.940000 to 0.960000
hPhiCrackEff->SetBinContent(48,1,0.750000);
hPhiCrackEff->SetBinError(48,1,0.059758);

// xbin: 0.960000 to 0.980000
hPhiCrackEff->SetBinContent(49,1,0.800000);
hPhiCrackEff->SetBinError(49,1,0.067737);

// xbin: 0.980000 to 1.000000
hPhiCrackEff->SetBinContent(50,1,0.645833);
hPhiCrackEff->SetBinError(50,1,0.071834);

////////////////////////////////////////////////////
// ybin: -0.500000 to 0.000000

// xbin: 0.000000 to 0.020000
hPhiCrackEff->SetBinContent(1,2,0.575000);
hPhiCrackEff->SetBinError(1,2,0.082341);

// xbin: 0.020000 to 0.040000
hPhiCrackEff->SetBinContent(2,2,0.622222);
hPhiCrackEff->SetBinError(2,2,0.077043);

// xbin: 0.040000 to 0.060000
hPhiCrackEff->SetBinContent(3,2,0.837838);
hPhiCrackEff->SetBinError(3,2,0.073539);

// xbin: 0.060000 to 0.080000
hPhiCrackEff->SetBinContent(4,2,0.942308);
hPhiCrackEff->SetBinError(4,2,0.049007);

// xbin: 0.080000 to 0.100000
hPhiCrackEff->SetBinContent(5,2,1.000000);
hPhiCrackEff->SetBinError(5,2,0.035824);

// xbin: 0.100000 to 0.120000
hPhiCrackEff->SetBinContent(6,2,1.039216);
hPhiCrackEff->SetBinError(6,2,0.042665);

// xbin: 0.120000 to 0.140000
hPhiCrackEff->SetBinContent(7,2,0.935484);
hPhiCrackEff->SetBinError(7,2,0.033287);

// xbin: 0.140000 to 0.160000
hPhiCrackEff->SetBinContent(8,2,0.981481);
hPhiCrackEff->SetBinError(8,2,0.034450);

// xbin: 0.160000 to 0.180000
hPhiCrackEff->SetBinContent(9,2,0.928571);
hPhiCrackEff->SetBinError(9,2,0.042855);

// xbin: 0.180000 to 0.200000
hPhiCrackEff->SetBinContent(10,2,1.000000);
hPhiCrackEff->SetBinError(10,2,0.046359);

// xbin: 0.200000 to 0.220000
hPhiCrackEff->SetBinContent(11,2,0.978723);
hPhiCrackEff->SetBinError(11,2,0.047803);

// xbin: 0.220000 to 0.240000
hPhiCrackEff->SetBinContent(12,2,1.000000);
hPhiCrackEff->SetBinError(12,2,0.042655);

// xbin: 0.240000 to 0.260000
hPhiCrackEff->SetBinContent(13,2,0.975610);
hPhiCrackEff->SetBinError(13,2,0.031748);

// xbin: 0.260000 to 0.280000
hPhiCrackEff->SetBinContent(14,2,1.057143);
hPhiCrackEff->SetBinError(14,2,0.061406);

// xbin: 0.280000 to 0.300000
hPhiCrackEff->SetBinContent(15,2,0.979167);
hPhiCrackEff->SetBinError(15,2,0.027440);

// xbin: 0.300000 to 0.320000
hPhiCrackEff->SetBinContent(16,2,1.000000);
hPhiCrackEff->SetBinError(16,2,0.055307);

// xbin: 0.320000 to 0.340000
hPhiCrackEff->SetBinContent(17,2,0.955556);
hPhiCrackEff->SetBinError(17,2,0.035283);

// xbin: 0.340000 to 0.360000
hPhiCrackEff->SetBinContent(18,2,0.981132);
hPhiCrackEff->SetBinError(18,2,0.035053);

// xbin: 0.360000 to 0.380000
hPhiCrackEff->SetBinContent(19,2,1.000000);
hPhiCrackEff->SetBinError(19,2,0.035819);

// xbin: 0.380000 to 0.400000
hPhiCrackEff->SetBinContent(20,2,0.959184);
hPhiCrackEff->SetBinError(20,2,0.032629);

// xbin: 0.400000 to 0.420000
hPhiCrackEff->SetBinContent(21,2,1.021739);
hPhiCrackEff->SetBinError(21,2,0.050508);

// xbin: 0.420000 to 0.440000
hPhiCrackEff->SetBinContent(22,2,1.055556);
hPhiCrackEff->SetBinError(22,2,0.059766);

// xbin: 0.440000 to 0.460000
hPhiCrackEff->SetBinContent(23,2,0.975610);
hPhiCrackEff->SetBinError(23,2,0.031748);

// xbin: 0.460000 to 0.480000
hPhiCrackEff->SetBinContent(24,2,0.983607);
hPhiCrackEff->SetBinError(24,2,0.030746);

// xbin: 0.480000 to 0.500000
hPhiCrackEff->SetBinContent(25,2,0.976744);
hPhiCrackEff->SetBinError(25,2,0.030385);

// xbin: 0.500000 to 0.520000
hPhiCrackEff->SetBinContent(26,2,0.979167);
hPhiCrackEff->SetBinError(26,2,0.038416);

// xbin: 0.520000 to 0.540000
hPhiCrackEff->SetBinContent(27,2,0.935484);
hPhiCrackEff->SetBinError(27,2,0.033287);

// xbin: 0.540000 to 0.560000
hPhiCrackEff->SetBinContent(28,2,1.000000);
hPhiCrackEff->SetBinError(28,2,0.028700);

// xbin: 0.560000 to 0.580000
hPhiCrackEff->SetBinContent(29,2,0.970588);
hPhiCrackEff->SetBinError(29,2,0.024036);

// xbin: 0.580000 to 0.600000
hPhiCrackEff->SetBinContent(30,2,1.000000);
hPhiCrackEff->SetBinError(30,2,0.038276);

// xbin: 0.600000 to 0.620000
hPhiCrackEff->SetBinContent(31,2,1.000000);
hPhiCrackEff->SetBinError(31,2,0.034397);

// xbin: 0.620000 to 0.640000
hPhiCrackEff->SetBinContent(32,2,0.980769);
hPhiCrackEff->SetBinError(32,2,0.025465);

// xbin: 0.640000 to 0.660000
hPhiCrackEff->SetBinContent(33,2,0.978261);
hPhiCrackEff->SetBinError(33,2,0.048753);

// xbin: 0.660000 to 0.680000
hPhiCrackEff->SetBinContent(34,2,1.026316);
hPhiCrackEff->SetBinError(34,2,0.060486);

// xbin: 0.680000 to 0.700000
hPhiCrackEff->SetBinContent(35,2,0.981818);
hPhiCrackEff->SetBinError(35,2,0.033867);

// xbin: 0.700000 to 0.720000
hPhiCrackEff->SetBinContent(36,2,1.000000);
hPhiCrackEff->SetBinError(36,2,0.037632);

// xbin: 0.720000 to 0.740000
hPhiCrackEff->SetBinContent(37,2,0.944444);
hPhiCrackEff->SetBinError(37,2,0.047372);

// xbin: 0.740000 to 0.760000
hPhiCrackEff->SetBinContent(38,2,1.125000);
hPhiCrackEff->SetBinError(38,2,0.055197);

// xbin: 0.760000 to 0.780000
hPhiCrackEff->SetBinContent(39,2,1.000000);
hPhiCrackEff->SetBinError(39,2,0.027779);

// xbin: 0.780000 to 0.800000
hPhiCrackEff->SetBinContent(40,2,1.047619);
hPhiCrackEff->SetBinError(40,2,0.039957);

// xbin: 0.800000 to 0.820000
hPhiCrackEff->SetBinContent(41,2,1.021739);
hPhiCrackEff->SetBinError(41,2,0.041239);

// xbin: 0.820000 to 0.840000
hPhiCrackEff->SetBinContent(42,2,1.076923);
hPhiCrackEff->SetBinError(42,2,0.062386);

// xbin: 0.840000 to 0.860000
hPhiCrackEff->SetBinContent(43,2,0.951613);
hPhiCrackEff->SetBinError(43,2,0.036387);

// xbin: 0.860000 to 0.880000
hPhiCrackEff->SetBinContent(44,2,0.981818);
hPhiCrackEff->SetBinError(44,2,0.033867);

// xbin: 0.880000 to 0.900000
hPhiCrackEff->SetBinContent(45,2,1.000000);
hPhiCrackEff->SetBinError(45,2,0.023941);

// xbin: 0.900000 to 0.920000
hPhiCrackEff->SetBinContent(46,2,0.959184);
hPhiCrackEff->SetBinError(46,2,0.055397);

// xbin: 0.920000 to 0.940000
hPhiCrackEff->SetBinContent(47,2,0.887097);
hPhiCrackEff->SetBinError(47,2,0.049182);

// xbin: 0.940000 to 0.960000
hPhiCrackEff->SetBinContent(48,2,0.813559);
hPhiCrackEff->SetBinError(48,2,0.062559);

// xbin: 0.960000 to 0.980000
hPhiCrackEff->SetBinContent(49,2,0.464286);
hPhiCrackEff->SetBinError(49,2,0.094686);

// xbin: 0.980000 to 1.000000
hPhiCrackEff->SetBinContent(50,2,0.369565);
hPhiCrackEff->SetBinError(50,2,0.070868);

////////////////////////////////////////////////////
// ybin: 0.000000 to 0.500000

// xbin: 0.000000 to 0.020000
hPhiCrackEff->SetBinContent(1,3,0.280000);
hPhiCrackEff->SetBinError(1,3,0.062714);

// xbin: 0.020000 to 0.040000
hPhiCrackEff->SetBinContent(2,3,0.458333);
hPhiCrackEff->SetBinError(2,3,0.070969);

// xbin: 0.040000 to 0.060000
hPhiCrackEff->SetBinContent(3,3,0.727273);
hPhiCrackEff->SetBinError(3,3,0.064087);

// xbin: 0.060000 to 0.080000
hPhiCrackEff->SetBinContent(4,3,1.047619);
hPhiCrackEff->SetBinError(4,3,0.060907);

// xbin: 0.080000 to 0.100000
hPhiCrackEff->SetBinContent(5,3,0.961538);
hPhiCrackEff->SetBinError(5,3,0.039429);

// xbin: 0.100000 to 0.120000
hPhiCrackEff->SetBinContent(6,3,0.913043);
hPhiCrackEff->SetBinError(6,3,0.050861);

// xbin: 0.120000 to 0.140000
hPhiCrackEff->SetBinContent(7,3,1.022727);
hPhiCrackEff->SetBinError(7,3,0.043013);

// xbin: 0.140000 to 0.160000
hPhiCrackEff->SetBinContent(8,3,0.964286);
hPhiCrackEff->SetBinError(8,3,0.049071);

// xbin: 0.160000 to 0.180000
hPhiCrackEff->SetBinContent(9,3,1.076923);
hPhiCrackEff->SetBinError(9,3,0.080293);

// xbin: 0.180000 to 0.200000
hPhiCrackEff->SetBinContent(10,3,0.981818);
hPhiCrackEff->SetBinError(10,3,0.033867);

// xbin: 0.200000 to 0.220000
hPhiCrackEff->SetBinContent(11,3,0.957447);
hPhiCrackEff->SetBinError(11,3,0.033905);

// xbin: 0.220000 to 0.240000
hPhiCrackEff->SetBinContent(12,3,1.000000);
hPhiCrackEff->SetBinError(12,3,0.050441);

// xbin: 0.240000 to 0.260000
hPhiCrackEff->SetBinContent(13,3,1.066667);
hPhiCrackEff->SetBinError(13,3,0.054130);

// xbin: 0.260000 to 0.280000
hPhiCrackEff->SetBinContent(14,3,1.065217);
hPhiCrackEff->SetBinError(14,3,0.061054);

// xbin: 0.280000 to 0.300000
hPhiCrackEff->SetBinContent(15,3,1.000000);
hPhiCrackEff->SetBinError(15,3,0.034712);

// xbin: 0.300000 to 0.320000
hPhiCrackEff->SetBinContent(16,3,0.968254);
hPhiCrackEff->SetBinError(16,3,0.033033);

// xbin: 0.320000 to 0.340000
hPhiCrackEff->SetBinContent(17,3,0.982759);
hPhiCrackEff->SetBinError(17,3,0.022983);

// xbin: 0.340000 to 0.360000
hPhiCrackEff->SetBinContent(18,3,0.982759);
hPhiCrackEff->SetBinError(18,3,0.022983);

// xbin: 0.360000 to 0.380000
hPhiCrackEff->SetBinContent(19,3,1.000000);
hPhiCrackEff->SetBinError(19,3,0.030201);

// xbin: 0.380000 to 0.400000
hPhiCrackEff->SetBinContent(20,3,1.000000);
hPhiCrackEff->SetBinError(20,3,0.039632);

// xbin: 0.400000 to 0.420000
hPhiCrackEff->SetBinContent(21,3,1.039216);
hPhiCrackEff->SetBinError(21,3,0.042665);

// xbin: 0.420000 to 0.440000
hPhiCrackEff->SetBinContent(22,3,1.000000);
hPhiCrackEff->SetBinError(22,3,0.045242);

// xbin: 0.440000 to 0.460000
hPhiCrackEff->SetBinContent(23,3,0.950000);
hPhiCrackEff->SetBinError(23,3,0.039274);

// xbin: 0.460000 to 0.480000
hPhiCrackEff->SetBinContent(24,3,0.977273);
hPhiCrackEff->SetBinError(24,3,0.029746);

// xbin: 0.480000 to 0.500000
hPhiCrackEff->SetBinContent(25,3,1.019231);
hPhiCrackEff->SetBinError(25,3,0.025950);

// xbin: 0.500000 to 0.520000
hPhiCrackEff->SetBinContent(26,3,0.981818);
hPhiCrackEff->SetBinError(26,3,0.033867);

// xbin: 0.520000 to 0.540000
hPhiCrackEff->SetBinContent(27,3,0.983607);
hPhiCrackEff->SetBinError(27,3,0.030746);

// xbin: 0.540000 to 0.560000
hPhiCrackEff->SetBinContent(28,3,1.038462);
hPhiCrackEff->SetBinError(28,3,0.056124);

// xbin: 0.560000 to 0.580000
hPhiCrackEff->SetBinContent(29,3,0.960000);
hPhiCrackEff->SetBinError(29,3,0.040867);

// xbin: 0.580000 to 0.600000
hPhiCrackEff->SetBinContent(30,3,1.000000);
hPhiCrackEff->SetBinError(30,3,0.033728);

// xbin: 0.600000 to 0.620000
hPhiCrackEff->SetBinContent(31,3,0.980769);
hPhiCrackEff->SetBinError(31,3,0.035678);

// xbin: 0.620000 to 0.640000
hPhiCrackEff->SetBinContent(32,3,0.854167);
hPhiCrackEff->SetBinError(32,3,0.051335);

// xbin: 0.640000 to 0.660000
hPhiCrackEff->SetBinContent(33,3,1.020000);
hPhiCrackEff->SetBinError(33,3,0.038097);

// xbin: 0.660000 to 0.680000
hPhiCrackEff->SetBinContent(34,3,1.066667);
hPhiCrackEff->SetBinError(34,3,0.044345);

// xbin: 0.680000 to 0.700000
hPhiCrackEff->SetBinContent(35,3,1.050000);
hPhiCrackEff->SetBinError(35,3,0.041889);

// xbin: 0.700000 to 0.720000
hPhiCrackEff->SetBinContent(36,3,1.037037);
hPhiCrackEff->SetBinError(36,3,0.040355);

// xbin: 0.720000 to 0.740000
hPhiCrackEff->SetBinContent(37,3,1.000000);
hPhiCrackEff->SetBinError(37,3,0.036575);

// xbin: 0.740000 to 0.760000
hPhiCrackEff->SetBinContent(38,3,1.000000);
hPhiCrackEff->SetBinError(38,3,0.069006);

// xbin: 0.760000 to 0.780000
hPhiCrackEff->SetBinContent(39,3,1.027027);
hPhiCrackEff->SetBinError(39,3,0.050637);

// xbin: 0.780000 to 0.800000
hPhiCrackEff->SetBinContent(40,3,0.975610);
hPhiCrackEff->SetBinError(40,3,0.044373);

// xbin: 0.800000 to 0.820000
hPhiCrackEff->SetBinContent(41,3,0.956522);
hPhiCrackEff->SetBinError(41,3,0.051870);

// xbin: 0.820000 to 0.840000
hPhiCrackEff->SetBinContent(42,3,0.958333);
hPhiCrackEff->SetBinError(42,3,0.042413);

// xbin: 0.840000 to 0.860000
hPhiCrackEff->SetBinContent(43,3,0.952381);
hPhiCrackEff->SetBinError(43,3,0.047842);

// xbin: 0.860000 to 0.880000
hPhiCrackEff->SetBinContent(44,3,0.918033);
hPhiCrackEff->SetBinError(44,3,0.050641);

// xbin: 0.880000 to 0.900000
hPhiCrackEff->SetBinContent(45,3,1.000000);
hPhiCrackEff->SetBinError(45,3,0.041856);

// xbin: 0.900000 to 0.920000
hPhiCrackEff->SetBinContent(46,3,0.972973);
hPhiCrackEff->SetBinError(46,3,0.048685);

// xbin: 0.920000 to 0.940000
hPhiCrackEff->SetBinContent(47,3,0.808511);
hPhiCrackEff->SetBinError(47,3,0.056997);

// xbin: 0.940000 to 0.960000
hPhiCrackEff->SetBinContent(48,3,0.777778);
hPhiCrackEff->SetBinError(48,3,0.072767);

// xbin: 0.960000 to 0.980000
hPhiCrackEff->SetBinContent(49,3,0.463415);
hPhiCrackEff->SetBinError(49,3,0.079625);

// xbin: 0.980000 to 1.000000
hPhiCrackEff->SetBinContent(50,3,0.395833);
hPhiCrackEff->SetBinError(50,3,0.070405);

////////////////////////////////////////////////////
// ybin: 0.500000 to 1.300000

// xbin: 0.000000 to 0.020000
hPhiCrackEff->SetBinContent(1,4,0.576271);
hPhiCrackEff->SetBinError(1,4,0.064176);

// xbin: 0.020000 to 0.040000
hPhiCrackEff->SetBinContent(2,4,0.675000);
hPhiCrackEff->SetBinError(2,4,0.075234);

// xbin: 0.040000 to 0.060000
hPhiCrackEff->SetBinContent(3,4,0.896552);
hPhiCrackEff->SetBinError(3,4,0.041103);

// xbin: 0.060000 to 0.080000
hPhiCrackEff->SetBinContent(4,4,1.034483);
hPhiCrackEff->SetBinError(4,4,0.029187);

// xbin: 0.080000 to 0.100000
hPhiCrackEff->SetBinContent(5,4,0.968254);
hPhiCrackEff->SetBinError(5,4,0.044040);

// xbin: 0.100000 to 0.120000
hPhiCrackEff->SetBinContent(6,4,1.076923);
hPhiCrackEff->SetBinError(6,4,0.051820);

// xbin: 0.120000 to 0.140000
hPhiCrackEff->SetBinContent(7,4,1.036364);
hPhiCrackEff->SetBinError(7,4,0.039640);

// xbin: 0.140000 to 0.160000
hPhiCrackEff->SetBinContent(8,4,1.000000);
hPhiCrackEff->SetBinError(8,4,0.033084);

// xbin: 0.160000 to 0.180000
hPhiCrackEff->SetBinContent(9,4,1.017241);
hPhiCrackEff->SetBinError(9,4,0.046752);

// xbin: 0.180000 to 0.200000
hPhiCrackEff->SetBinContent(10,4,1.040816);
hPhiCrackEff->SetBinError(10,4,0.044357);

// xbin: 0.200000 to 0.220000
hPhiCrackEff->SetBinContent(11,4,1.000000);
hPhiCrackEff->SetBinError(11,4,0.031291);

// xbin: 0.220000 to 0.240000
hPhiCrackEff->SetBinContent(12,4,0.979167);
hPhiCrackEff->SetBinError(12,4,0.054050);

// xbin: 0.240000 to 0.260000
hPhiCrackEff->SetBinContent(13,4,1.000000);
hPhiCrackEff->SetBinError(13,4,0.041879);

// xbin: 0.260000 to 0.280000
hPhiCrackEff->SetBinContent(14,4,0.979167);
hPhiCrackEff->SetBinError(14,4,0.060368);

// xbin: 0.280000 to 0.300000
hPhiCrackEff->SetBinContent(15,4,0.982759);
hPhiCrackEff->SetBinError(15,4,0.032231);

// xbin: 0.300000 to 0.320000
hPhiCrackEff->SetBinContent(16,4,0.947368);
hPhiCrackEff->SetBinError(16,4,0.039298);

// xbin: 0.320000 to 0.340000
hPhiCrackEff->SetBinContent(17,4,1.000000);
hPhiCrackEff->SetBinError(17,4,0.033667);

// xbin: 0.340000 to 0.360000
hPhiCrackEff->SetBinContent(18,4,0.960784);
hPhiCrackEff->SetBinError(18,4,0.040135);

// xbin: 0.360000 to 0.380000
hPhiCrackEff->SetBinContent(19,4,0.932203);
hPhiCrackEff->SetBinError(19,4,0.040735);

// xbin: 0.380000 to 0.400000
hPhiCrackEff->SetBinContent(20,4,0.943396);
hPhiCrackEff->SetBinError(20,4,0.034702);

// xbin: 0.400000 to 0.420000
hPhiCrackEff->SetBinContent(21,4,0.961538);
hPhiCrackEff->SetBinError(21,4,0.039429);

// xbin: 0.420000 to 0.440000
hPhiCrackEff->SetBinContent(22,4,0.960000);
hPhiCrackEff->SetBinError(22,4,0.032027);

// xbin: 0.440000 to 0.460000
hPhiCrackEff->SetBinContent(23,4,0.948276);
hPhiCrackEff->SetBinError(23,4,0.044408);

// xbin: 0.460000 to 0.480000
hPhiCrackEff->SetBinContent(24,4,1.000000);
hPhiCrackEff->SetBinError(24,4,0.054603);

// xbin: 0.480000 to 0.500000
hPhiCrackEff->SetBinContent(25,4,0.981132);
hPhiCrackEff->SetBinError(25,4,0.042798);

// xbin: 0.500000 to 0.520000
hPhiCrackEff->SetBinContent(26,4,1.000000);
hPhiCrackEff->SetBinError(26,4,0.038276);

// xbin: 0.520000 to 0.540000
hPhiCrackEff->SetBinContent(27,4,0.918033);
hPhiCrackEff->SetBinError(27,4,0.041862);

// xbin: 0.540000 to 0.560000
hPhiCrackEff->SetBinContent(28,4,0.958333);
hPhiCrackEff->SetBinError(28,4,0.042413);

// xbin: 0.560000 to 0.580000
hPhiCrackEff->SetBinContent(29,4,1.000000);
hPhiCrackEff->SetBinError(29,4,0.047713);

// xbin: 0.580000 to 0.600000
hPhiCrackEff->SetBinContent(30,4,0.982456);
hPhiCrackEff->SetBinError(30,4,0.032759);

// xbin: 0.600000 to 0.620000
hPhiCrackEff->SetBinContent(31,4,0.956522);
hPhiCrackEff->SetBinError(31,4,0.058634);

// xbin: 0.620000 to 0.640000
hPhiCrackEff->SetBinContent(32,4,0.981818);
hPhiCrackEff->SetBinError(32,4,0.024161);

// xbin: 0.640000 to 0.660000
hPhiCrackEff->SetBinContent(33,4,0.932203);
hPhiCrackEff->SetBinError(33,4,0.034838);

// xbin: 0.660000 to 0.680000
hPhiCrackEff->SetBinContent(34,4,1.040000);
hPhiCrackEff->SetBinError(34,4,0.058305);

// xbin: 0.680000 to 0.700000
hPhiCrackEff->SetBinContent(35,4,0.976190);
hPhiCrackEff->SetBinError(35,4,0.031051);

// xbin: 0.700000 to 0.720000
hPhiCrackEff->SetBinContent(36,4,1.000000);
hPhiCrackEff->SetBinError(36,4,0.035824);

// xbin: 0.720000 to 0.740000
hPhiCrackEff->SetBinContent(37,4,0.980392);
hPhiCrackEff->SetBinError(37,4,0.025931);

// xbin: 0.740000 to 0.760000
hPhiCrackEff->SetBinContent(38,4,0.982143);
hPhiCrackEff->SetBinError(38,4,0.033304);

// xbin: 0.760000 to 0.780000
hPhiCrackEff->SetBinContent(39,4,0.949153);
hPhiCrackEff->SetBinError(39,4,0.031437);

// xbin: 0.780000 to 0.800000
hPhiCrackEff->SetBinContent(40,4,0.984615);
hPhiCrackEff->SetBinError(40,4,0.053897);

// xbin: 0.800000 to 0.820000
hPhiCrackEff->SetBinContent(41,4,1.040816);
hPhiCrackEff->SetBinError(41,4,0.052456);

// xbin: 0.820000 to 0.840000
hPhiCrackEff->SetBinContent(42,4,0.973684);
hPhiCrackEff->SetBinError(42,4,0.057963);

// xbin: 0.840000 to 0.860000
hPhiCrackEff->SetBinContent(43,4,1.019231);
hPhiCrackEff->SetBinError(43,4,0.051900);

// xbin: 0.860000 to 0.880000
hPhiCrackEff->SetBinContent(44,4,1.000000);
hPhiCrackEff->SetBinError(44,4,0.044504);

// xbin: 0.880000 to 0.900000
hPhiCrackEff->SetBinContent(45,4,0.981132);
hPhiCrackEff->SetBinError(45,4,0.042798);

// xbin: 0.900000 to 0.920000
hPhiCrackEff->SetBinContent(46,4,0.931035);
hPhiCrackEff->SetBinError(46,4,0.035388);

// xbin: 0.920000 to 0.940000
hPhiCrackEff->SetBinContent(47,4,0.875000);
hPhiCrackEff->SetBinError(47,4,0.059338);

// xbin: 0.940000 to 0.960000
hPhiCrackEff->SetBinContent(48,4,0.843137);
hPhiCrackEff->SetBinError(48,4,0.059782);

// xbin: 0.960000 to 0.980000
hPhiCrackEff->SetBinContent(49,4,0.653061);
hPhiCrackEff->SetBinError(49,4,0.066271);

// xbin: 0.980000 to 1.000000
hPhiCrackEff->SetBinContent(50,4,0.531915);
hPhiCrackEff->SetBinError(50,4,0.075304);

////////////////////////////////////////////////////
// ybin: over 1.300000
}
