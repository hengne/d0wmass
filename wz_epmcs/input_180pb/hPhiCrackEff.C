{
const int n_hPhiCrackEff_xbins = 50;
float hPhiCrackEff_xbins[n_hPhiCrackEff_xbins+1] = {0.000000 ,0.020000 ,0.040000 ,0.060000 ,0.080000 ,0.100000 ,0.120000 ,0.140000 ,0.160000 ,0.180000 ,0.200000 ,0.220000 ,0.240000 ,0.260000 ,0.280000 ,0.300000 ,0.320000 ,0.340000 ,0.360000 ,0.380000 ,0.400000 ,0.420000 ,0.440000 ,0.460000 ,0.480000 ,0.500000 ,0.520000 ,0.540000 ,0.560000 ,0.580000 ,0.600000 ,0.620000 ,0.640000 ,0.660000 ,0.680000 ,0.700000 ,0.720000 ,0.740000 ,0.760000 ,0.780000 ,0.800000 ,0.820000 ,0.840000 ,0.860000 ,0.880000 ,0.900000 ,0.920000 ,0.940000 ,0.960000 ,0.980000 ,1.000000  };

TH1F *hPhiCrackEff = new TH1F("hPhiCrackEff","preselection efficiency vs phimod, no fiducial cut, CC", n_hPhiCrackEff_xbins, hPhiCrackEff_xbins);

// 0.000000 to 0.020000
hPhiCrackEff->SetBinContent(1,0.510989);
hPhiCrackEff->SetBinError(1,0.037781);

// 0.020000 to 0.040000
hPhiCrackEff->SetBinContent(2,0.633880);
hPhiCrackEff->SetBinError(2,0.037892);

// 0.040000 to 0.060000
hPhiCrackEff->SetBinContent(3,0.846561);
hPhiCrackEff->SetBinError(3,0.030366);

// 0.060000 to 0.080000
hPhiCrackEff->SetBinContent(4,0.990291);
hPhiCrackEff->SetBinError(4,0.020628);

// 0.080000 to 0.100000
hPhiCrackEff->SetBinContent(5,0.978448);
hPhiCrackEff->SetBinError(5,0.019559);

// 0.100000 to 0.120000
hPhiCrackEff->SetBinContent(6,1.015464);
hPhiCrackEff->SetBinError(6,0.023003);

// 0.120000 to 0.140000
hPhiCrackEff->SetBinContent(7,1.000000);
hPhiCrackEff->SetBinError(7,0.017213);

// 0.140000 to 0.160000
hPhiCrackEff->SetBinContent(8,1.000000);
hPhiCrackEff->SetBinError(8,0.020363);

// 0.160000 to 0.180000
hPhiCrackEff->SetBinContent(9,1.005682);
hPhiCrackEff->SetBinError(9,0.028566);

// 0.180000 to 0.200000
hPhiCrackEff->SetBinContent(10,0.988636);
hPhiCrackEff->SetBinError(10,0.022744);

// 0.200000 to 0.220000
hPhiCrackEff->SetBinContent(11,0.994975);
hPhiCrackEff->SetBinError(11,0.017035);

// 0.220000 to 0.240000
hPhiCrackEff->SetBinContent(12,0.989583);
hPhiCrackEff->SetBinError(12,0.023223);

// 0.240000 to 0.260000
hPhiCrackEff->SetBinContent(13,1.018072);
hPhiCrackEff->SetBinError(13,0.019013);

// 0.260000 to 0.280000
hPhiCrackEff->SetBinContent(14,1.005494);
hPhiCrackEff->SetBinError(14,0.028680);

// 0.280000 to 0.300000
hPhiCrackEff->SetBinContent(15,0.986425);
hPhiCrackEff->SetBinError(15,0.015268);

// 0.300000 to 0.320000
hPhiCrackEff->SetBinContent(16,0.962963);
hPhiCrackEff->SetBinError(16,0.020292);

// 0.320000 to 0.340000
hPhiCrackEff->SetBinContent(17,0.974138);
hPhiCrackEff->SetBinError(17,0.016137);

// 0.340000 to 0.360000
hPhiCrackEff->SetBinContent(18,0.981132);
hPhiCrackEff->SetBinError(18,0.017704);

// 0.360000 to 0.380000
hPhiCrackEff->SetBinContent(19,0.984925);
hPhiCrackEff->SetBinError(19,0.018252);

// 0.380000 to 0.400000
hPhiCrackEff->SetBinContent(20,0.973958);
hPhiCrackEff->SetBinError(20,0.020048);

// 0.400000 to 0.420000
hPhiCrackEff->SetBinContent(21,1.000000);
hPhiCrackEff->SetBinError(21,0.019223);

// 0.420000 to 0.440000
hPhiCrackEff->SetBinContent(22,0.967742);
hPhiCrackEff->SetBinError(22,0.022421);

// 0.440000 to 0.460000
hPhiCrackEff->SetBinContent(23,0.973118);
hPhiCrackEff->SetBinError(23,0.020670);

// 0.460000 to 0.480000
hPhiCrackEff->SetBinContent(24,0.985075);
hPhiCrackEff->SetBinError(24,0.018076);

// 0.480000 to 0.500000
hPhiCrackEff->SetBinContent(25,0.989744);
hPhiCrackEff->SetBinError(25,0.018010);

// 0.500000 to 0.520000
hPhiCrackEff->SetBinContent(26,0.990148);
hPhiCrackEff->SetBinError(26,0.018598);

// 0.520000 to 0.540000
hPhiCrackEff->SetBinContent(27,0.956175);
hPhiCrackEff->SetBinError(27,0.016205);

// 0.540000 to 0.560000
hPhiCrackEff->SetBinContent(28,0.990244);
hPhiCrackEff->SetBinError(28,0.020726);

// 0.560000 to 0.580000
hPhiCrackEff->SetBinContent(29,0.981481);
hPhiCrackEff->SetBinError(29,0.018501);

// 0.580000 to 0.600000
hPhiCrackEff->SetBinContent(30,1.004808);
hPhiCrackEff->SetBinError(30,0.016457);

// 0.600000 to 0.620000
hPhiCrackEff->SetBinContent(31,0.975845);
hPhiCrackEff->SetBinError(31,0.019767);

// 0.620000 to 0.640000
hPhiCrackEff->SetBinContent(32,0.942857);
hPhiCrackEff->SetBinError(32,0.018662);

// 0.640000 to 0.660000
hPhiCrackEff->SetBinContent(33,0.975962);
hPhiCrackEff->SetBinError(33,0.020729);

// 0.660000 to 0.680000
hPhiCrackEff->SetBinContent(34,1.031579);
hPhiCrackEff->SetBinError(34,0.025633);

// 0.680000 to 0.700000
hPhiCrackEff->SetBinContent(35,0.984211);
hPhiCrackEff->SetBinError(35,0.017683);

// 0.700000 to 0.720000
hPhiCrackEff->SetBinContent(36,1.009479);
hPhiCrackEff->SetBinError(36,0.019405);

// 0.720000 to 0.740000
hPhiCrackEff->SetBinContent(37,0.985148);
hPhiCrackEff->SetBinError(37,0.016663);

// 0.740000 to 0.760000
hPhiCrackEff->SetBinContent(38,1.009756);
hPhiCrackEff->SetBinError(38,0.023227);

// 0.760000 to 0.780000
hPhiCrackEff->SetBinContent(39,0.980198);
hPhiCrackEff->SetBinError(39,0.017282);

// 0.780000 to 0.800000
hPhiCrackEff->SetBinContent(40,0.990099);
hPhiCrackEff->SetBinError(40,0.025966);

// 0.800000 to 0.820000
hPhiCrackEff->SetBinContent(41,1.016575);
hPhiCrackEff->SetBinError(41,0.023387);

// 0.820000 to 0.840000
hPhiCrackEff->SetBinContent(42,1.012121);
hPhiCrackEff->SetBinError(42,0.026183);

// 0.840000 to 0.860000
hPhiCrackEff->SetBinContent(43,0.980952);
hPhiCrackEff->SetBinError(43,0.022094);

// 0.860000 to 0.880000
hPhiCrackEff->SetBinContent(44,0.977778);
hPhiCrackEff->SetBinError(44,0.021889);

// 0.880000 to 0.900000
hPhiCrackEff->SetBinContent(45,0.990783);
hPhiCrackEff->SetBinError(45,0.017427);

// 0.900000 to 0.920000
hPhiCrackEff->SetBinContent(46,0.978836);
hPhiCrackEff->SetBinError(46,0.023378);

// 0.920000 to 0.940000
hPhiCrackEff->SetBinContent(47,0.870000);
hPhiCrackEff->SetBinError(47,0.029382);

// 0.940000 to 0.960000
hPhiCrackEff->SetBinContent(48,0.796209);
hPhiCrackEff->SetBinError(48,0.032282);

// 0.960000 to 0.980000
hPhiCrackEff->SetBinContent(49,0.613497);
hPhiCrackEff->SetBinError(49,0.040272);

// 0.980000 to 1.000000
hPhiCrackEff->SetBinContent(50,0.486772);
hPhiCrackEff->SetBinError(50,0.037650);
}
