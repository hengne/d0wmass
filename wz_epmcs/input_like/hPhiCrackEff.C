{
const int n_hPhiCrackEff_xbins = 50;
float hPhiCrackEff_xbins[n_hPhiCrackEff_xbins+1] = {0.000000 ,0.020000 ,0.040000 ,0.060000 ,0.080000 ,0.100000 ,0.120000 ,0.140000 ,0.160000 ,0.180000 ,0.200000 ,0.220000 ,0.240000 ,0.260000 ,0.280000 ,0.300000 ,0.320000 ,0.340000 ,0.360000 ,0.380000 ,0.400000 ,0.420000 ,0.440000 ,0.460000 ,0.480000 ,0.500000 ,0.520000 ,0.540000 ,0.560000 ,0.580000 ,0.600000 ,0.620000 ,0.640000 ,0.660000 ,0.680000 ,0.700000 ,0.720000 ,0.740000 ,0.760000 ,0.780000 ,0.800000 ,0.820000 ,0.840000 ,0.860000 ,0.880000 ,0.900000 ,0.920000 ,0.940000 ,0.960000 ,0.980000 ,1.000000  };

TH1F *hPhiCrackEff = new TH1F("hPhiCrackEff","preselection efficiency vs phimod, no fiducial cut, CC", n_hPhiCrackEff_xbins, hPhiCrackEff_xbins);

// 0.000000 to 0.020000
hPhiCrackEff->SetBinContent(1,0.527950);
hPhiCrackEff->SetBinError(1,0.039515);

// 0.020000 to 0.040000
hPhiCrackEff->SetBinContent(2,0.627329);
hPhiCrackEff->SetBinError(2,0.038934);

// 0.040000 to 0.060000
hPhiCrackEff->SetBinContent(3,0.830409);
hPhiCrackEff->SetBinError(3,0.030983);

// 0.060000 to 0.080000
hPhiCrackEff->SetBinContent(4,0.983425);
hPhiCrackEff->SetBinError(4,0.015161);

// 0.080000 to 0.100000
hPhiCrackEff->SetBinContent(5,0.976190);
hPhiCrackEff->SetBinError(5,0.015955);

// 0.100000 to 0.120000
hPhiCrackEff->SetBinContent(6,1.011173);
hPhiCrackEff->SetBinError(6,0.012395);

// 0.120000 to 0.140000
hPhiCrackEff->SetBinContent(7,0.989305);
hPhiCrackEff->SetBinError(7,0.011669);

// 0.140000 to 0.160000
hPhiCrackEff->SetBinContent(8,0.994444);
hPhiCrackEff->SetBinError(8,0.013299);

// 0.160000 to 0.180000
hPhiCrackEff->SetBinContent(9,0.981250);
hPhiCrackEff->SetBinError(9,0.017083);

// 0.180000 to 0.200000
hPhiCrackEff->SetBinContent(10,0.993902);
hPhiCrackEff->SetBinError(10,0.014564);

// 0.200000 to 0.220000
hPhiCrackEff->SetBinContent(11,0.983516);
hPhiCrackEff->SetBinError(11,0.010722);

// 0.220000 to 0.240000
hPhiCrackEff->SetBinContent(12,0.977143);
hPhiCrackEff->SetBinError(12,0.016556);

// 0.240000 to 0.260000
hPhiCrackEff->SetBinContent(13,1.013423);
hPhiCrackEff->SetBinError(13,0.017588);

// 0.260000 to 0.280000
hPhiCrackEff->SetBinContent(14,0.977528);
hPhiCrackEff->SetBinError(14,0.017980);

// 0.280000 to 0.300000
hPhiCrackEff->SetBinContent(15,1.000000);
hPhiCrackEff->SetBinError(15,0.010833);

// 0.300000 to 0.320000
hPhiCrackEff->SetBinContent(16,0.974359);
hPhiCrackEff->SetBinError(16,0.014048);

// 0.320000 to 0.340000
hPhiCrackEff->SetBinContent(17,0.994898);
hPhiCrackEff->SetBinError(17,0.009999);

// 0.340000 to 0.360000
hPhiCrackEff->SetBinContent(18,0.994898);
hPhiCrackEff->SetBinError(18,0.009999);

// 0.360000 to 0.380000
hPhiCrackEff->SetBinContent(19,1.005747);
hPhiCrackEff->SetBinError(19,0.013878);

// 0.380000 to 0.400000
hPhiCrackEff->SetBinContent(20,1.005747);
hPhiCrackEff->SetBinError(20,0.013878);

// 0.400000 to 0.420000
hPhiCrackEff->SetBinContent(21,1.011429);
hPhiCrackEff->SetBinError(21,0.017002);

// 0.420000 to 0.440000
hPhiCrackEff->SetBinContent(22,1.000000);
hPhiCrackEff->SetBinError(22,0.010109);

// 0.440000 to 0.460000
hPhiCrackEff->SetBinContent(23,0.981928);
hPhiCrackEff->SetBinError(23,0.018410);

// 0.460000 to 0.480000
hPhiCrackEff->SetBinContent(24,0.983696);
hPhiCrackEff->SetBinError(24,0.012945);

// 0.480000 to 0.500000
hPhiCrackEff->SetBinContent(25,0.994536);
hPhiCrackEff->SetBinError(25,0.010694);

// 0.500000 to 0.520000
hPhiCrackEff->SetBinContent(26,1.000000);
hPhiCrackEff->SetBinError(26,0.016004);

// 0.520000 to 0.540000
hPhiCrackEff->SetBinContent(27,0.986301);
hPhiCrackEff->SetBinError(27,0.010925);

// 0.540000 to 0.560000
hPhiCrackEff->SetBinContent(28,0.994350);
hPhiCrackEff->SetBinError(28,0.013519);

// 0.560000 to 0.580000
hPhiCrackEff->SetBinContent(29,0.989583);
hPhiCrackEff->SetBinError(29,0.013438);

// 0.580000 to 0.600000
hPhiCrackEff->SetBinContent(30,0.994872);
hPhiCrackEff->SetBinError(30,0.007124);

// 0.600000 to 0.620000
hPhiCrackEff->SetBinContent(31,0.988889);
hPhiCrackEff->SetBinError(31,0.012111);

// 0.620000 to 0.640000
hPhiCrackEff->SetBinContent(32,0.984375);
hPhiCrackEff->SetBinError(32,0.010176);

// 0.640000 to 0.660000
hPhiCrackEff->SetBinContent(33,0.977528);
hPhiCrackEff->SetBinError(33,0.016287);

// 0.660000 to 0.680000
hPhiCrackEff->SetBinContent(34,0.989011);
hPhiCrackEff->SetBinError(34,0.014156);

// 0.680000 to 0.700000
hPhiCrackEff->SetBinContent(35,0.988372);
hPhiCrackEff->SetBinError(35,0.012659);

// 0.700000 to 0.720000
hPhiCrackEff->SetBinContent(36,1.010471);
hPhiCrackEff->SetBinError(36,0.013749);

// 0.720000 to 0.740000
hPhiCrackEff->SetBinContent(37,0.983957);
hPhiCrackEff->SetBinError(37,0.010442);

// 0.740000 to 0.760000
hPhiCrackEff->SetBinContent(38,0.994595);
hPhiCrackEff->SetBinError(38,0.016703);

// 0.760000 to 0.780000
hPhiCrackEff->SetBinContent(39,1.000000);
hPhiCrackEff->SetBinError(39,0.012534);

// 0.780000 to 0.800000
hPhiCrackEff->SetBinContent(40,1.000000);
hPhiCrackEff->SetBinError(40,0.013135);

// 0.800000 to 0.820000
hPhiCrackEff->SetBinContent(41,0.981481);
hPhiCrackEff->SetBinError(41,0.014648);

// 0.820000 to 0.840000
hPhiCrackEff->SetBinContent(42,0.980892);
hPhiCrackEff->SetBinError(42,0.017398);

// 0.840000 to 0.860000
hPhiCrackEff->SetBinContent(43,0.983696);
hPhiCrackEff->SetBinError(43,0.016664);

// 0.860000 to 0.880000
hPhiCrackEff->SetBinContent(44,0.985782);
hPhiCrackEff->SetBinError(44,0.014589);

// 0.880000 to 0.900000
hPhiCrackEff->SetBinContent(45,0.989474);
hPhiCrackEff->SetBinError(45,0.013575);

// 0.900000 to 0.920000
hPhiCrackEff->SetBinContent(46,1.006061);
hPhiCrackEff->SetBinError(46,0.020681);

// 0.920000 to 0.940000
hPhiCrackEff->SetBinContent(47,0.910112);
hPhiCrackEff->SetBinError(47,0.026911);

// 0.940000 to 0.960000
hPhiCrackEff->SetBinContent(48,0.793970);
hPhiCrackEff->SetBinError(48,0.029139);

// 0.960000 to 0.980000
hPhiCrackEff->SetBinContent(49,0.597315);
hPhiCrackEff->SetBinError(49,0.039800);

// 0.980000 to 1.000000
hPhiCrackEff->SetBinContent(50,0.503067);
hPhiCrackEff->SetBinError(50,0.039515);
}
