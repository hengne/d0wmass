{
const int n_idEffEtaZvtx_xbins = 64;
float idEffEtaZvtx_xbins[n_idEffEtaZvtx_xbins+1] = {-3.200000 ,-3.100000 ,-3.000000 ,-2.900000 ,-2.800000 ,-2.700000 ,-2.600000 ,-2.500000 ,-2.400000 ,-2.300000 ,-2.200000 ,-2.100000 ,-2.000000 ,-1.900000 ,-1.800000 ,-1.700000 ,-1.600000 ,-1.500000 ,-1.400000 ,-1.300000 ,-1.200000 ,-1.100000 ,-1.000000 ,-0.900000 ,-0.800000 ,-0.700000 ,-0.600000 ,-0.500000 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.400000 ,0.500000 ,0.600000 ,0.700000 ,0.800000 ,0.900000 ,1.000000 ,1.100000 ,1.200000 ,1.300000 ,1.400000 ,1.500000 ,1.600000 ,1.700000 ,1.800000 ,1.900000 ,2.000000 ,2.100000 ,2.200000 ,2.300000 ,2.400000 ,2.500000 ,2.600000 ,2.700000 ,2.800000 ,2.900000 ,3.000000 ,3.100000 ,3.200000  };

const int n_idEffEtaZvtx_ybins = 10;
float idEffEtaZvtx_ybins[n_idEffEtaZvtx_ybins+1] = {-100.000000 ,-39.000000 ,-30.000000 ,-23.000000 ,-10.000000 ,0.000000 ,10.000000 ,23.000000 ,30.000000 ,39.000000 ,100.000000  };

TH2F *idEffEtaZvtx = new TH2F("idEffEtaZvtx","like efficiency vs detector eta and zvtx", n_idEffEtaZvtx_xbins, idEffEtaZvtx_xbins, n_idEffEtaZvtx_ybins, idEffEtaZvtx_ybins);

////////////////////////////////////////////////////
// ybin: under -100.000000

////////////////////////////////////////////////////
// ybin: -100.000000 to -39.000000

// xbin: -1.600000 to -1.500000
idEffEtaZvtx->SetBinContent(17,1,1.000000);
idEffEtaZvtx->SetBinError(17,1,0.235702);

// xbin: -1.100000 to -1.000000
idEffEtaZvtx->SetBinContent(22,1,0.333333);
idEffEtaZvtx->SetBinError(22,1,0.161374);

// xbin: -1.000000 to -0.900000
idEffEtaZvtx->SetBinContent(23,1,0.700000);
idEffEtaZvtx->SetBinError(23,1,0.097120);

// xbin: -0.900000 to -0.800000
idEffEtaZvtx->SetBinContent(24,1,0.750000);
idEffEtaZvtx->SetBinError(24,1,0.102756);

// xbin: -0.800000 to -0.700000
idEffEtaZvtx->SetBinContent(25,1,0.588235);
idEffEtaZvtx->SetBinError(25,1,0.110401);

// xbin: -0.700000 to -0.600000
idEffEtaZvtx->SetBinContent(26,1,0.708333);
idEffEtaZvtx->SetBinError(26,1,0.088823);

// xbin: -0.600000 to -0.500000
idEffEtaZvtx->SetBinContent(27,1,0.700000);
idEffEtaZvtx->SetBinError(27,1,0.097120);

// xbin: -0.500000 to -0.400000
idEffEtaZvtx->SetBinContent(28,1,0.636364);
idEffEtaZvtx->SetBinError(28,1,0.130024);

// xbin: -0.400000 to -0.300000
idEffEtaZvtx->SetBinContent(29,1,0.764706);
idEffEtaZvtx->SetBinError(29,1,0.098465);

// xbin: -0.300000 to -0.200000
idEffEtaZvtx->SetBinContent(30,1,0.785714);
idEffEtaZvtx->SetBinError(30,1,0.105021);

// xbin: -0.200000 to -0.100000
idEffEtaZvtx->SetBinContent(31,1,0.666667);
idEffEtaZvtx->SetBinError(31,1,0.097220);

// xbin: -0.100000 to 0.000000
idEffEtaZvtx->SetBinContent(32,1,0.666667);
idEffEtaZvtx->SetBinError(32,1,0.091557);

// xbin: 0.000000 to 0.100000
idEffEtaZvtx->SetBinContent(33,1,0.642857);
idEffEtaZvtx->SetBinError(33,1,0.117417);

// xbin: 0.100000 to 0.200000
idEffEtaZvtx->SetBinContent(34,1,0.764706);
idEffEtaZvtx->SetBinError(34,1,0.098465);

// xbin: 0.200000 to 0.300000
idEffEtaZvtx->SetBinContent(35,1,0.571429);
idEffEtaZvtx->SetBinError(35,1,0.120317);

// xbin: 0.300000 to 0.400000
idEffEtaZvtx->SetBinContent(36,1,0.923077);
idEffEtaZvtx->SetBinError(36,1,0.084984);

// xbin: 0.400000 to 0.500000
idEffEtaZvtx->SetBinContent(37,1,0.833333);
idEffEtaZvtx->SetBinError(37,1,0.087287);

// xbin: 0.500000 to 0.600000
idEffEtaZvtx->SetBinContent(38,1,0.882353);
idEffEtaZvtx->SetBinError(38,1,0.081536);

// xbin: 0.600000 to 0.700000
idEffEtaZvtx->SetBinContent(39,1,0.869565);
idEffEtaZvtx->SetBinError(39,1,0.071897);

// xbin: 0.700000 to 0.800000
idEffEtaZvtx->SetBinContent(40,1,1.000000);
idEffEtaZvtx->SetBinError(40,1,0.082988);

// xbin: 0.800000 to 0.900000
idEffEtaZvtx->SetBinContent(41,1,0.842105);
idEffEtaZvtx->SetBinError(41,1,0.083719);

// xbin: 0.900000 to 1.000000
idEffEtaZvtx->SetBinContent(42,1,0.857143);
idEffEtaZvtx->SetBinError(42,1,0.094665);

// xbin: 1.000000 to 1.100000
idEffEtaZvtx->SetBinContent(43,1,0.875000);
idEffEtaZvtx->SetBinError(43,1,0.120605);

// xbin: 1.500000 to 1.600000
idEffEtaZvtx->SetBinContent(48,1,0.677419);
idEffEtaZvtx->SetBinError(48,1,0.080845);

// xbin: 1.600000 to 1.700000
idEffEtaZvtx->SetBinContent(49,1,0.916667);
idEffEtaZvtx->SetBinError(49,1,0.061485);

// xbin: 1.700000 to 1.800000
idEffEtaZvtx->SetBinContent(50,1,0.666667);
idEffEtaZvtx->SetBinError(50,1,0.123718);

// xbin: 1.800000 to 1.900000
idEffEtaZvtx->SetBinContent(51,1,0.882353);
idEffEtaZvtx->SetBinError(51,1,0.081536);

// xbin: 1.900000 to 2.000000
idEffEtaZvtx->SetBinContent(52,1,0.933333);
idEffEtaZvtx->SetBinError(52,1,0.075941);

// xbin: 2.000000 to 2.100000
idEffEtaZvtx->SetBinContent(53,1,1.000000);
idEffEtaZvtx->SetBinError(53,1,0.071217);

// xbin: 2.100000 to 2.200000
idEffEtaZvtx->SetBinContent(54,1,0.923077);
idEffEtaZvtx->SetBinError(54,1,0.084984);

// xbin: 2.200000 to 2.300000
idEffEtaZvtx->SetBinContent(55,1,0.625000);
idEffEtaZvtx->SetBinError(55,1,0.147710);

////////////////////////////////////////////////////
// ybin: -39.000000 to -30.000000

// xbin: -1.800000 to -1.700000
idEffEtaZvtx->SetBinContent(15,2,1.000000);
idEffEtaZvtx->SetBinError(15,2,0.163299);

// xbin: -1.700000 to -1.600000
idEffEtaZvtx->SetBinContent(16,2,1.000000);
idEffEtaZvtx->SetBinError(16,2,0.163299);

// xbin: -1.600000 to -1.500000
idEffEtaZvtx->SetBinContent(17,2,0.833333);
idEffEtaZvtx->SetBinError(17,2,0.144338);

// xbin: -1.100000 to -1.000000
idEffEtaZvtx->SetBinContent(22,2,0.818182);
idEffEtaZvtx->SetBinError(22,2,0.112604);

// xbin: -1.000000 to -0.900000
idEffEtaZvtx->SetBinContent(23,2,0.894737);
idEffEtaZvtx->SetBinError(23,2,0.074605);

// xbin: -0.900000 to -0.800000
idEffEtaZvtx->SetBinContent(24,2,0.642857);
idEffEtaZvtx->SetBinError(24,2,0.117417);

// xbin: -0.800000 to -0.700000
idEffEtaZvtx->SetBinContent(25,2,0.826087);
idEffEtaZvtx->SetBinError(25,2,0.078446);

// xbin: -0.700000 to -0.600000
idEffEtaZvtx->SetBinContent(26,2,0.777778);
idEffEtaZvtx->SetBinError(26,2,0.094491);

// xbin: -0.600000 to -0.500000
idEffEtaZvtx->SetBinContent(27,2,0.680000);
idEffEtaZvtx->SetBinError(27,2,0.089087);

// xbin: -0.500000 to -0.400000
idEffEtaZvtx->SetBinContent(28,2,0.866667);
idEffEtaZvtx->SetBinError(28,2,0.063206);

// xbin: -0.400000 to -0.300000
idEffEtaZvtx->SetBinContent(29,2,0.875000);
idEffEtaZvtx->SetBinError(29,2,0.085498);

// xbin: -0.300000 to -0.200000
idEffEtaZvtx->SetBinContent(30,2,0.947368);
idEffEtaZvtx->SetBinError(30,2,0.062584);

// xbin: -0.200000 to -0.100000
idEffEtaZvtx->SetBinContent(31,2,0.875000);
idEffEtaZvtx->SetBinError(31,2,0.069436);

// xbin: -0.100000 to 0.000000
idEffEtaZvtx->SetBinContent(32,2,0.960000);
idEffEtaZvtx->SetBinError(32,2,0.049493);

// xbin: 0.000000 to 0.100000
idEffEtaZvtx->SetBinContent(33,2,0.888889);
idEffEtaZvtx->SetBinError(33,2,0.077919);

// xbin: 0.100000 to 0.200000
idEffEtaZvtx->SetBinContent(34,2,0.944444);
idEffEtaZvtx->SetBinError(34,2,0.043180);

// xbin: 0.200000 to 0.300000
idEffEtaZvtx->SetBinContent(35,2,0.818182);
idEffEtaZvtx->SetBinError(35,2,0.081223);

// xbin: 0.300000 to 0.400000
idEffEtaZvtx->SetBinContent(36,2,0.961538);
idEffEtaZvtx->SetBinError(36,2,0.047824);

// xbin: 0.400000 to 0.500000
idEffEtaZvtx->SetBinContent(37,2,1.000000);
idEffEtaZvtx->SetBinError(37,2,0.039965);

// xbin: 0.500000 to 0.600000
idEffEtaZvtx->SetBinContent(38,2,1.000000);
idEffEtaZvtx->SetBinError(38,2,0.039965);

// xbin: 0.600000 to 0.700000
idEffEtaZvtx->SetBinContent(39,2,0.937500);
idEffEtaZvtx->SetBinError(39,2,0.072098);

// xbin: 0.700000 to 0.800000
idEffEtaZvtx->SetBinContent(40,2,0.956522);
idEffEtaZvtx->SetBinError(40,2,0.053205);

// xbin: 0.800000 to 0.900000
idEffEtaZvtx->SetBinContent(41,2,0.944444);
idEffEtaZvtx->SetBinError(41,2,0.065465);

// xbin: 0.900000 to 1.000000
idEffEtaZvtx->SetBinContent(42,2,0.785714);
idEffEtaZvtx->SetBinError(42,2,0.105021);

// xbin: 1.000000 to 1.100000
idEffEtaZvtx->SetBinContent(43,2,1.000000);
idEffEtaZvtx->SetBinError(43,2,0.082988);

// xbin: 1.500000 to 1.600000
idEffEtaZvtx->SetBinContent(48,2,0.818182);
idEffEtaZvtx->SetBinError(48,2,0.081223);

// xbin: 1.600000 to 1.700000
idEffEtaZvtx->SetBinContent(49,2,0.821429);
idEffEtaZvtx->SetBinError(49,2,0.071842);

// xbin: 1.700000 to 1.800000
idEffEtaZvtx->SetBinContent(50,2,0.933333);
idEffEtaZvtx->SetBinError(50,2,0.075941);

// xbin: 1.800000 to 1.900000
idEffEtaZvtx->SetBinContent(51,2,0.941176);
idEffEtaZvtx->SetBinError(51,2,0.068623);

// xbin: 1.900000 to 2.000000
idEffEtaZvtx->SetBinContent(52,2,0.875000);
idEffEtaZvtx->SetBinError(52,2,0.120605);

// xbin: 2.000000 to 2.100000
idEffEtaZvtx->SetBinContent(53,2,1.000000);
idEffEtaZvtx->SetBinError(53,2,0.055459);

// xbin: 2.100000 to 2.200000
idEffEtaZvtx->SetBinContent(54,2,0.750000);
idEffEtaZvtx->SetBinError(54,2,0.178174);

// xbin: 2.200000 to 2.300000
idEffEtaZvtx->SetBinContent(55,2,0.833333);
idEffEtaZvtx->SetBinError(55,2,0.144338);

////////////////////////////////////////////////////
// ybin: -30.000000 to -23.000000

// xbin: -2.300000 to -2.200000
idEffEtaZvtx->SetBinContent(10,3,1.000000);
idEffEtaZvtx->SetBinError(10,3,0.235702);

// xbin: -2.200000 to -2.100000
idEffEtaZvtx->SetBinContent(11,3,0.666667);
idEffEtaZvtx->SetBinError(11,3,0.200000);

// xbin: -2.100000 to -2.000000
idEffEtaZvtx->SetBinContent(12,3,0.750000);
idEffEtaZvtx->SetBinError(12,3,0.178174);

// xbin: -1.900000 to -1.800000
idEffEtaZvtx->SetBinContent(14,3,1.000000);
idEffEtaZvtx->SetBinError(14,3,0.140859);

// xbin: -1.800000 to -1.700000
idEffEtaZvtx->SetBinContent(15,3,1.000000);
idEffEtaZvtx->SetBinError(15,3,0.123718);

// xbin: -1.700000 to -1.600000
idEffEtaZvtx->SetBinContent(16,3,0.818182);
idEffEtaZvtx->SetBinError(16,3,0.112604);

// xbin: -1.600000 to -1.500000
idEffEtaZvtx->SetBinContent(17,3,0.882353);
idEffEtaZvtx->SetBinError(17,3,0.081536);

// xbin: -1.100000 to -1.000000
idEffEtaZvtx->SetBinContent(22,3,1.000000);
idEffEtaZvtx->SetBinError(22,3,0.082988);

// xbin: -1.000000 to -0.900000
idEffEtaZvtx->SetBinContent(23,3,0.833333);
idEffEtaZvtx->SetBinError(23,3,0.075847);

// xbin: -0.900000 to -0.800000
idEffEtaZvtx->SetBinContent(24,3,0.850000);
idEffEtaZvtx->SetBinError(24,3,0.080423);

// xbin: -0.800000 to -0.700000
idEffEtaZvtx->SetBinContent(25,3,0.958333);
idEffEtaZvtx->SetBinError(25,3,0.051282);

// xbin: -0.700000 to -0.600000
idEffEtaZvtx->SetBinContent(26,3,0.888889);
idEffEtaZvtx->SetBinError(26,3,0.062957);

// xbin: -0.600000 to -0.500000
idEffEtaZvtx->SetBinContent(27,3,0.900000);
idEffEtaZvtx->SetBinError(27,3,0.057571);

// xbin: -0.500000 to -0.400000
idEffEtaZvtx->SetBinContent(28,3,0.892857);
idEffEtaZvtx->SetBinError(28,3,0.061054);

// xbin: -0.400000 to -0.300000
idEffEtaZvtx->SetBinContent(29,3,0.846154);
idEffEtaZvtx->SetBinError(29,3,0.071120);

// xbin: -0.300000 to -0.200000
idEffEtaZvtx->SetBinContent(30,3,0.888889);
idEffEtaZvtx->SetBinError(30,3,0.062957);

// xbin: -0.200000 to -0.100000
idEffEtaZvtx->SetBinContent(31,3,0.903226);
idEffEtaZvtx->SetBinError(31,3,0.055973);

// xbin: -0.100000 to 0.000000
idEffEtaZvtx->SetBinContent(32,3,0.966667);
idEffEtaZvtx->SetBinError(32,3,0.042137);

// xbin: 0.000000 to 0.100000
idEffEtaZvtx->SetBinContent(33,3,0.833333);
idEffEtaZvtx->SetBinError(33,3,0.075847);

// xbin: 0.100000 to 0.200000
idEffEtaZvtx->SetBinContent(34,3,0.964286);
idEffEtaZvtx->SetBinError(34,3,0.044801);

// xbin: 0.200000 to 0.300000
idEffEtaZvtx->SetBinContent(35,3,1.000000);
idEffEtaZvtx->SetBinError(35,3,0.037010);

// xbin: 0.300000 to 0.400000
idEffEtaZvtx->SetBinContent(36,3,1.000000);
idEffEtaZvtx->SetBinError(36,3,0.033314);

// xbin: 0.400000 to 0.500000
idEffEtaZvtx->SetBinContent(37,3,1.000000);
idEffEtaZvtx->SetBinError(37,3,0.039965);

// xbin: 0.500000 to 0.600000
idEffEtaZvtx->SetBinContent(38,3,0.947368);
idEffEtaZvtx->SetBinError(38,3,0.062584);

// xbin: 0.600000 to 0.700000
idEffEtaZvtx->SetBinContent(39,3,0.888889);
idEffEtaZvtx->SetBinError(39,3,0.077919);

// xbin: 0.700000 to 0.800000
idEffEtaZvtx->SetBinContent(40,3,0.851852);
idEffEtaZvtx->SetBinError(40,3,0.068966);

// xbin: 0.800000 to 0.900000
idEffEtaZvtx->SetBinContent(41,3,0.954545);
idEffEtaZvtx->SetBinError(41,3,0.055277);

// xbin: 0.900000 to 1.000000
idEffEtaZvtx->SetBinContent(42,3,0.833333);
idEffEtaZvtx->SetBinError(42,3,0.087287);

// xbin: 1.000000 to 1.100000
idEffEtaZvtx->SetBinContent(43,3,1.000000);
idEffEtaZvtx->SetBinError(43,3,0.041627);

// xbin: 1.500000 to 1.600000
idEffEtaZvtx->SetBinContent(48,3,0.869565);
idEffEtaZvtx->SetBinError(48,3,0.071897);

// xbin: 1.600000 to 1.700000
idEffEtaZvtx->SetBinContent(49,3,0.727273);
idEffEtaZvtx->SetBinError(49,3,0.090906);

// xbin: 1.700000 to 1.800000
idEffEtaZvtx->SetBinContent(50,3,0.928571);
idEffEtaZvtx->SetBinError(50,3,0.080211);

// xbin: 1.800000 to 1.900000
idEffEtaZvtx->SetBinContent(51,3,0.923077);
idEffEtaZvtx->SetBinError(51,3,0.084984);

// xbin: 1.900000 to 2.000000
idEffEtaZvtx->SetBinContent(52,3,0.866667);
idEffEtaZvtx->SetBinError(52,3,0.089854);

// xbin: 2.000000 to 2.100000
idEffEtaZvtx->SetBinContent(53,3,0.916667);
idEffEtaZvtx->SetBinError(53,3,0.090351);

// xbin: 2.100000 to 2.200000
idEffEtaZvtx->SetBinContent(54,3,0.923077);
idEffEtaZvtx->SetBinError(54,3,0.084984);

// xbin: 2.200000 to 2.300000
idEffEtaZvtx->SetBinContent(55,3,0.909091);
idEffEtaZvtx->SetBinError(55,3,0.096428);

////////////////////////////////////////////////////
// ybin: -23.000000 to -10.000000

// xbin: -2.300000 to -2.200000
idEffEtaZvtx->SetBinContent(10,4,1.000000);
idEffEtaZvtx->SetBinError(10,4,0.082988);

// xbin: -2.200000 to -2.100000
idEffEtaZvtx->SetBinContent(11,4,0.800000);
idEffEtaZvtx->SetBinError(11,4,0.120096);

// xbin: -2.100000 to -2.000000
idEffEtaZvtx->SetBinContent(12,4,0.888889);
idEffEtaZvtx->SetBinError(12,4,0.111340);

// xbin: -2.000000 to -1.900000
idEffEtaZvtx->SetBinContent(13,4,1.000000);
idEffEtaZvtx->SetBinError(13,4,0.076656);

// xbin: -1.900000 to -1.800000
idEffEtaZvtx->SetBinContent(14,4,0.842105);
idEffEtaZvtx->SetBinError(14,4,0.083719);

// xbin: -1.800000 to -1.700000
idEffEtaZvtx->SetBinContent(15,4,0.760000);
idEffEtaZvtx->SetBinError(15,4,0.082817);

// xbin: -1.700000 to -1.600000
idEffEtaZvtx->SetBinContent(16,4,0.884615);
idEffEtaZvtx->SetBinError(16,4,0.064980);

// xbin: -1.600000 to -1.500000
idEffEtaZvtx->SetBinContent(17,4,0.844444);
idEffEtaZvtx->SetBinError(17,4,0.054245);

// xbin: -1.100000 to -1.000000
idEffEtaZvtx->SetBinContent(22,4,0.956522);
idEffEtaZvtx->SetBinError(22,4,0.053205);

// xbin: -1.000000 to -0.900000
idEffEtaZvtx->SetBinContent(23,4,0.857143);
idEffEtaZvtx->SetBinError(23,4,0.047137);

// xbin: -0.900000 to -0.800000
idEffEtaZvtx->SetBinContent(24,4,0.898305);
idEffEtaZvtx->SetBinError(24,4,0.040478);

// xbin: -0.800000 to -0.700000
idEffEtaZvtx->SetBinContent(25,4,0.904110);
idEffEtaZvtx->SetBinError(25,4,0.035409);

// xbin: -0.700000 to -0.600000
idEffEtaZvtx->SetBinContent(26,4,0.923077);
idEffEtaZvtx->SetBinError(26,4,0.034627);

// xbin: -0.600000 to -0.500000
idEffEtaZvtx->SetBinContent(27,4,0.890411);
idEffEtaZvtx->SetBinError(27,4,0.037276);

// xbin: -0.500000 to -0.400000
idEffEtaZvtx->SetBinContent(28,4,0.935065);
idEffEtaZvtx->SetBinError(28,4,0.029619);

// xbin: -0.400000 to -0.300000
idEffEtaZvtx->SetBinContent(29,4,0.909091);
idEffEtaZvtx->SetBinError(29,4,0.033729);

// xbin: -0.300000 to -0.200000
idEffEtaZvtx->SetBinContent(30,4,0.893939);
idEffEtaZvtx->SetBinError(30,4,0.038787);

// xbin: -0.200000 to -0.100000
idEffEtaZvtx->SetBinContent(31,4,0.863636);
idEffEtaZvtx->SetBinError(31,4,0.036851);

// xbin: -0.100000 to 0.000000
idEffEtaZvtx->SetBinContent(32,4,0.926829);
idEffEtaZvtx->SetBinError(32,4,0.029978);

// xbin: 0.000000 to 0.100000
idEffEtaZvtx->SetBinContent(33,4,0.875000);
idEffEtaZvtx->SetBinError(33,4,0.039476);

// xbin: 0.100000 to 0.200000
idEffEtaZvtx->SetBinContent(34,4,0.940298);
idEffEtaZvtx->SetBinError(34,4,0.030987);

// xbin: 0.200000 to 0.300000
idEffEtaZvtx->SetBinContent(35,4,1.000000);
idEffEtaZvtx->SetBinError(35,4,0.015871);

// xbin: 0.300000 to 0.400000
idEffEtaZvtx->SetBinContent(36,4,0.951613);
idEffEtaZvtx->SetBinError(36,4,0.030024);

// xbin: 0.400000 to 0.500000
idEffEtaZvtx->SetBinContent(37,4,0.902778);
idEffEtaZvtx->SetBinError(37,4,0.035855);

// xbin: 0.500000 to 0.600000
idEffEtaZvtx->SetBinContent(38,4,0.943662);
idEffEtaZvtx->SetBinError(38,4,0.029363);

// xbin: 0.600000 to 0.700000
idEffEtaZvtx->SetBinContent(39,4,0.875000);
idEffEtaZvtx->SetBinError(39,4,0.044893);

// xbin: 0.700000 to 0.800000
idEffEtaZvtx->SetBinContent(40,4,0.954545);
idEffEtaZvtx->SetBinError(40,4,0.036015);

// xbin: 0.800000 to 0.900000
idEffEtaZvtx->SetBinContent(41,4,0.970588);
idEffEtaZvtx->SetBinError(41,4,0.024036);

// xbin: 0.900000 to 1.000000
idEffEtaZvtx->SetBinContent(42,4,0.898305);
idEffEtaZvtx->SetBinError(42,4,0.040478);

// xbin: 1.000000 to 1.100000
idEffEtaZvtx->SetBinContent(43,4,0.962963);
idEffEtaZvtx->SetBinError(43,4,0.046263);

// xbin: 1.500000 to 1.600000
idEffEtaZvtx->SetBinContent(48,4,0.862500);
idEffEtaZvtx->SetBinError(48,4,0.038796);

// xbin: 1.600000 to 1.700000
idEffEtaZvtx->SetBinContent(49,4,0.875000);
idEffEtaZvtx->SetBinError(49,4,0.044893);

// xbin: 1.700000 to 1.800000
idEffEtaZvtx->SetBinContent(50,4,0.875000);
idEffEtaZvtx->SetBinError(50,4,0.044893);

// xbin: 1.800000 to 1.900000
idEffEtaZvtx->SetBinContent(51,4,0.954545);
idEffEtaZvtx->SetBinError(51,4,0.036015);

// xbin: 1.900000 to 2.000000
idEffEtaZvtx->SetBinContent(52,4,0.875000);
idEffEtaZvtx->SetBinError(52,4,0.053363);

// xbin: 2.000000 to 2.100000
idEffEtaZvtx->SetBinContent(53,4,0.826087);
idEffEtaZvtx->SetBinError(53,4,0.078446);

// xbin: 2.100000 to 2.200000
idEffEtaZvtx->SetBinContent(54,4,0.730769);
idEffEtaZvtx->SetBinError(54,4,0.083889);

// xbin: 2.200000 to 2.300000
idEffEtaZvtx->SetBinContent(55,4,0.846154);
idEffEtaZvtx->SetBinError(55,4,0.071120);

////////////////////////////////////////////////////
// ybin: -10.000000 to 0.000000

// xbin: -2.300000 to -2.200000
idEffEtaZvtx->SetBinContent(10,5,0.700000);
idEffEtaZvtx->SetBinError(10,5,0.130744);

// xbin: -2.200000 to -2.100000
idEffEtaZvtx->SetBinContent(11,5,0.777778);
idEffEtaZvtx->SetBinError(11,5,0.128565);

// xbin: -2.100000 to -2.000000
idEffEtaZvtx->SetBinContent(12,5,0.875000);
idEffEtaZvtx->SetBinError(12,5,0.120605);

// xbin: -2.000000 to -1.900000
idEffEtaZvtx->SetBinContent(13,5,0.941176);
idEffEtaZvtx->SetBinError(13,5,0.068623);

// xbin: -1.900000 to -1.800000
idEffEtaZvtx->SetBinContent(14,5,0.875000);
idEffEtaZvtx->SetBinError(14,5,0.069436);

// xbin: -1.800000 to -1.700000
idEffEtaZvtx->SetBinContent(15,5,0.806452);
idEffEtaZvtx->SetBinError(15,5,0.070110);

// xbin: -1.700000 to -1.600000
idEffEtaZvtx->SetBinContent(16,5,0.978261);
idEffEtaZvtx->SetBinError(16,5,0.028547);

// xbin: -1.600000 to -1.500000
idEffEtaZvtx->SetBinContent(17,5,0.735294);
idEffEtaZvtx->SetBinError(17,5,0.073635);

// xbin: -1.100000 to -1.000000
idEffEtaZvtx->SetBinContent(22,5,1.000000);
idEffEtaZvtx->SetBinError(22,5,0.058709);

// xbin: -1.000000 to -0.900000
idEffEtaZvtx->SetBinContent(23,5,0.901961);
idEffEtaZvtx->SetBinError(23,5,0.043117);

// xbin: -0.900000 to -0.800000
idEffEtaZvtx->SetBinContent(24,5,0.967742);
idEffEtaZvtx->SetBinError(24,5,0.026217);

// xbin: -0.800000 to -0.700000
idEffEtaZvtx->SetBinContent(25,5,0.929825);
idEffEtaZvtx->SetBinError(25,5,0.035955);

// xbin: -0.700000 to -0.600000
idEffEtaZvtx->SetBinContent(26,5,0.892857);
idEffEtaZvtx->SetBinError(26,5,0.042411);

// xbin: -0.600000 to -0.500000
idEffEtaZvtx->SetBinContent(27,5,0.926471);
idEffEtaZvtx->SetBinError(27,5,0.033223);

// xbin: -0.500000 to -0.400000
idEffEtaZvtx->SetBinContent(28,5,0.971429);
idEffEtaZvtx->SetBinError(28,5,0.023388);

// xbin: -0.400000 to -0.300000
idEffEtaZvtx->SetBinContent(29,5,0.915493);
idEffEtaZvtx->SetBinError(29,5,0.034228);

// xbin: -0.300000 to -0.200000
idEffEtaZvtx->SetBinContent(30,5,0.930556);
idEffEtaZvtx->SetBinError(30,5,0.031519);

// xbin: -0.200000 to -0.100000
idEffEtaZvtx->SetBinContent(31,5,0.893333);
idEffEtaZvtx->SetBinError(31,5,0.036378);

// xbin: -0.100000 to 0.000000
idEffEtaZvtx->SetBinContent(32,5,0.948718);
idEffEtaZvtx->SetBinError(32,5,0.026896);

// xbin: 0.000000 to 0.100000
idEffEtaZvtx->SetBinContent(33,5,0.941176);
idEffEtaZvtx->SetBinError(33,5,0.030564);

// xbin: 0.100000 to 0.200000
idEffEtaZvtx->SetBinContent(34,5,0.965909);
idEffEtaZvtx->SetBinError(34,5,0.021603);

// xbin: 0.200000 to 0.300000
idEffEtaZvtx->SetBinContent(35,5,0.974026);
idEffEtaZvtx->SetBinError(35,5,0.021370);

// xbin: 0.300000 to 0.400000
idEffEtaZvtx->SetBinContent(36,5,0.959459);
idEffEtaZvtx->SetBinError(36,5,0.025447);

// xbin: 0.400000 to 0.500000
idEffEtaZvtx->SetBinContent(37,5,0.971014);
idEffEtaZvtx->SetBinError(37,5,0.023708);

// xbin: 0.500000 to 0.600000
idEffEtaZvtx->SetBinContent(38,5,0.928571);
idEffEtaZvtx->SetBinError(38,5,0.032348);

// xbin: 0.600000 to 0.700000
idEffEtaZvtx->SetBinContent(39,5,0.918919);
idEffEtaZvtx->SetBinError(39,5,0.032954);

// xbin: 0.700000 to 0.800000
idEffEtaZvtx->SetBinContent(40,5,0.973333);
idEffEtaZvtx->SetBinError(40,5,0.021910);

// xbin: 0.800000 to 0.900000
idEffEtaZvtx->SetBinContent(41,5,0.981481);
idEffEtaZvtx->SetBinError(41,5,0.024580);

// xbin: 0.900000 to 1.000000
idEffEtaZvtx->SetBinContent(42,5,0.923077);
idEffEtaZvtx->SetBinError(42,5,0.039085);

// xbin: 1.000000 to 1.100000
idEffEtaZvtx->SetBinContent(43,5,0.814815);
idEffEtaZvtx->SetBinError(43,5,0.073957);

// xbin: 1.500000 to 1.600000
idEffEtaZvtx->SetBinContent(48,5,0.718750);
idEffEtaZvtx->SetBinError(48,5,0.055315);

// xbin: 1.600000 to 1.700000
idEffEtaZvtx->SetBinContent(49,5,0.895833);
idEffEtaZvtx->SetBinError(49,5,0.045504);

// xbin: 1.700000 to 1.800000
idEffEtaZvtx->SetBinContent(50,5,0.894737);
idEffEtaZvtx->SetBinError(50,5,0.051650);

// xbin: 1.800000 to 1.900000
idEffEtaZvtx->SetBinContent(51,5,0.904762);
idEffEtaZvtx->SetBinError(51,5,0.047311);

// xbin: 1.900000 to 2.000000
idEffEtaZvtx->SetBinContent(52,5,0.926829);
idEffEtaZvtx->SetBinError(52,5,0.043789);

// xbin: 2.000000 to 2.100000
idEffEtaZvtx->SetBinContent(53,5,0.967742);
idEffEtaZvtx->SetBinError(53,5,0.040921);

// xbin: 2.100000 to 2.200000
idEffEtaZvtx->SetBinContent(54,5,0.800000);
idEffEtaZvtx->SetBinError(54,5,0.078567);

// xbin: 2.200000 to 2.300000
idEffEtaZvtx->SetBinContent(55,5,0.827586);
idEffEtaZvtx->SetBinError(55,5,0.069841);

////////////////////////////////////////////////////
// ybin: 0.000000 to 10.000000

// xbin: -2.300000 to -2.200000
idEffEtaZvtx->SetBinContent(10,6,0.933333);
idEffEtaZvtx->SetBinError(10,6,0.075941);

// xbin: -2.200000 to -2.100000
idEffEtaZvtx->SetBinContent(11,6,0.823529);
idEffEtaZvtx->SetBinError(11,6,0.091161);

// xbin: -2.100000 to -2.000000
idEffEtaZvtx->SetBinContent(12,6,0.875000);
idEffEtaZvtx->SetBinError(12,6,0.069436);

// xbin: -2.000000 to -1.900000
idEffEtaZvtx->SetBinContent(13,6,0.842105);
idEffEtaZvtx->SetBinError(13,6,0.083719);

// xbin: -1.900000 to -1.800000
idEffEtaZvtx->SetBinContent(14,6,0.944444);
idEffEtaZvtx->SetBinError(14,6,0.043180);

// xbin: -1.800000 to -1.700000
idEffEtaZvtx->SetBinContent(15,6,0.823529);
idEffEtaZvtx->SetBinError(15,6,0.065065);

// xbin: -1.700000 to -1.600000
idEffEtaZvtx->SetBinContent(16,6,0.826087);
idEffEtaZvtx->SetBinError(16,6,0.055759);

// xbin: -1.600000 to -1.500000
idEffEtaZvtx->SetBinContent(17,6,0.977778);
idEffEtaZvtx->SetBinError(17,6,0.029134);

// xbin: -1.100000 to -1.000000
idEffEtaZvtx->SetBinContent(22,6,0.967742);
idEffEtaZvtx->SetBinError(22,6,0.040921);

// xbin: -1.000000 to -0.900000
idEffEtaZvtx->SetBinContent(23,6,0.893617);
idEffEtaZvtx->SetBinError(23,6,0.046358);

// xbin: -0.900000 to -0.800000
idEffEtaZvtx->SetBinContent(24,6,0.932203);
idEffEtaZvtx->SetBinError(24,6,0.034838);

// xbin: -0.800000 to -0.700000
idEffEtaZvtx->SetBinContent(25,6,0.870968);
idEffEtaZvtx->SetBinError(25,6,0.043119);

// xbin: -0.700000 to -0.600000
idEffEtaZvtx->SetBinContent(26,6,0.970149);
idEffEtaZvtx->SetBinError(26,6,0.024374);

// xbin: -0.600000 to -0.500000
idEffEtaZvtx->SetBinContent(27,6,0.957747);
idEffEtaZvtx->SetBinError(27,6,0.026455);

// xbin: -0.500000 to -0.400000
idEffEtaZvtx->SetBinContent(28,6,0.962963);
idEffEtaZvtx->SetBinError(28,6,0.023368);

// xbin: -0.400000 to -0.300000
idEffEtaZvtx->SetBinContent(29,6,0.932432);
idEffEtaZvtx->SetBinError(29,6,0.030730);

// xbin: -0.300000 to -0.200000
idEffEtaZvtx->SetBinContent(30,6,0.950000);
idEffEtaZvtx->SetBinError(30,6,0.030952);

// xbin: -0.200000 to -0.100000
idEffEtaZvtx->SetBinContent(31,6,0.946667);
idEffEtaZvtx->SetBinError(31,6,0.027901);

// xbin: -0.100000 to 0.000000
idEffEtaZvtx->SetBinContent(32,6,0.970588);
idEffEtaZvtx->SetBinError(32,6,0.024036);

// xbin: 0.000000 to 0.100000
idEffEtaZvtx->SetBinContent(33,6,0.961538);
idEffEtaZvtx->SetBinError(33,6,0.024216);

// xbin: 0.100000 to 0.200000
idEffEtaZvtx->SetBinContent(34,6,0.948052);
idEffEtaZvtx->SetBinError(34,6,0.027223);

// xbin: 0.200000 to 0.300000
idEffEtaZvtx->SetBinContent(35,6,0.934211);
idEffEtaZvtx->SetBinError(35,6,0.029980);

// xbin: 0.300000 to 0.400000
idEffEtaZvtx->SetBinContent(36,6,0.961039);
idEffEtaZvtx->SetBinError(36,6,0.024513);

// xbin: 0.400000 to 0.500000
idEffEtaZvtx->SetBinContent(37,6,0.953846);
idEffEtaZvtx->SetBinError(37,6,0.028732);

// xbin: 0.500000 to 0.600000
idEffEtaZvtx->SetBinContent(38,6,0.873418);
idEffEtaZvtx->SetBinError(38,6,0.037831);

// xbin: 0.600000 to 0.700000
idEffEtaZvtx->SetBinContent(39,6,0.939759);
idEffEtaZvtx->SetBinError(39,6,0.027620);

// xbin: 0.700000 to 0.800000
idEffEtaZvtx->SetBinContent(40,6,0.982759);
idEffEtaZvtx->SetBinError(40,6,0.022983);

// xbin: 0.800000 to 0.900000
idEffEtaZvtx->SetBinContent(41,6,0.916667);
idEffEtaZvtx->SetBinError(41,6,0.037248);

// xbin: 0.900000 to 1.000000
idEffEtaZvtx->SetBinContent(42,6,0.893939);
idEffEtaZvtx->SetBinError(42,6,0.038787);

// xbin: 1.000000 to 1.100000
idEffEtaZvtx->SetBinContent(43,6,0.878788);
idEffEtaZvtx->SetBinError(43,6,0.058321);

// xbin: 1.500000 to 1.600000
idEffEtaZvtx->SetBinContent(48,6,0.920000);
idEffEtaZvtx->SetBinError(48,6,0.032551);

// xbin: 1.600000 to 1.700000
idEffEtaZvtx->SetBinContent(49,6,0.933333);
idEffEtaZvtx->SetBinError(49,6,0.040276);

// xbin: 1.700000 to 1.800000
idEffEtaZvtx->SetBinContent(50,6,0.878049);
idEffEtaZvtx->SetBinError(50,6,0.052237);

// xbin: 1.800000 to 1.900000
idEffEtaZvtx->SetBinContent(51,6,0.972222);
idEffEtaZvtx->SetBinError(51,6,0.035756);

// xbin: 1.900000 to 2.000000
idEffEtaZvtx->SetBinContent(52,6,0.970588);
idEffEtaZvtx->SetBinError(52,6,0.037657);

// xbin: 2.000000 to 2.100000
idEffEtaZvtx->SetBinContent(53,6,0.966667);
idEffEtaZvtx->SetBinError(53,6,0.042137);

// xbin: 2.100000 to 2.200000
idEffEtaZvtx->SetBinContent(54,6,0.920000);
idEffEtaZvtx->SetBinError(54,6,0.059391);

// xbin: 2.200000 to 2.300000
idEffEtaZvtx->SetBinContent(55,6,0.920000);
idEffEtaZvtx->SetBinError(55,6,0.059391);

////////////////////////////////////////////////////
// ybin: 10.000000 to 23.000000

// xbin: -2.300000 to -2.200000
idEffEtaZvtx->SetBinContent(10,7,0.727273);
idEffEtaZvtx->SetBinError(10,7,0.123351);

// xbin: -2.200000 to -2.100000
idEffEtaZvtx->SetBinContent(11,7,0.933333);
idEffEtaZvtx->SetBinError(11,7,0.075941);

// xbin: -2.100000 to -2.000000
idEffEtaZvtx->SetBinContent(12,7,1.000000);
idEffEtaZvtx->SetBinError(12,7,0.043433);

// xbin: -2.000000 to -1.900000
idEffEtaZvtx->SetBinContent(13,7,0.750000);
idEffEtaZvtx->SetBinError(13,7,0.116642);

// xbin: -1.900000 to -1.800000
idEffEtaZvtx->SetBinContent(14,7,0.925926);
idEffEtaZvtx->SetBinError(14,7,0.055602);

// xbin: -1.800000 to -1.700000
idEffEtaZvtx->SetBinContent(15,7,0.793103);
idEffEtaZvtx->SetBinError(15,7,0.073913);

// xbin: -1.700000 to -1.600000
idEffEtaZvtx->SetBinContent(16,7,0.796296);
idEffEtaZvtx->SetBinError(16,7,0.054349);

// xbin: -1.600000 to -1.500000
idEffEtaZvtx->SetBinContent(17,7,0.811321);
idEffEtaZvtx->SetBinError(17,7,0.053452);

// xbin: -1.100000 to -1.000000
idEffEtaZvtx->SetBinContent(22,7,0.896552);
idEffEtaZvtx->SetBinError(22,7,0.059262);

// xbin: -1.000000 to -0.900000
idEffEtaZvtx->SetBinContent(23,7,0.937500);
idEffEtaZvtx->SetBinError(23,7,0.032327);

// xbin: -0.900000 to -0.800000
idEffEtaZvtx->SetBinContent(24,7,0.965517);
idEffEtaZvtx->SetBinError(24,7,0.027905);

// xbin: -0.800000 to -0.700000
idEffEtaZvtx->SetBinContent(25,7,0.910714);
idEffEtaZvtx->SetBinError(25,7,0.039648);

// xbin: -0.700000 to -0.600000
idEffEtaZvtx->SetBinContent(26,7,0.902778);
idEffEtaZvtx->SetBinError(26,7,0.035855);

// xbin: -0.600000 to -0.500000
idEffEtaZvtx->SetBinContent(27,7,0.957747);
idEffEtaZvtx->SetBinError(27,7,0.026455);

// xbin: -0.500000 to -0.400000
idEffEtaZvtx->SetBinContent(28,7,0.954545);
idEffEtaZvtx->SetBinError(28,7,0.028326);

// xbin: -0.400000 to -0.300000
idEffEtaZvtx->SetBinContent(29,7,0.967742);
idEffEtaZvtx->SetBinError(29,7,0.026217);

// xbin: -0.300000 to -0.200000
idEffEtaZvtx->SetBinContent(30,7,0.934426);
idEffEtaZvtx->SetBinError(30,7,0.033788);

// xbin: -0.200000 to -0.100000
idEffEtaZvtx->SetBinContent(31,7,0.957747);
idEffEtaZvtx->SetBinError(31,7,0.026455);

// xbin: -0.100000 to 0.000000
idEffEtaZvtx->SetBinContent(32,7,0.975000);
idEffEtaZvtx->SetBinError(32,7,0.020607);

// xbin: 0.000000 to 0.100000
idEffEtaZvtx->SetBinContent(33,7,0.930556);
idEffEtaZvtx->SetBinError(33,7,0.031519);

// xbin: 0.100000 to 0.200000
idEffEtaZvtx->SetBinContent(34,7,0.949367);
idEffEtaZvtx->SetBinError(34,7,0.026577);

// xbin: 0.200000 to 0.300000
idEffEtaZvtx->SetBinContent(35,7,0.906250);
idEffEtaZvtx->SetBinError(35,7,0.037618);

// xbin: 0.300000 to 0.400000
idEffEtaZvtx->SetBinContent(36,7,0.950820);
idEffEtaZvtx->SetBinError(36,7,0.030481);

// xbin: 0.400000 to 0.500000
idEffEtaZvtx->SetBinContent(37,7,0.835821);
idEffEtaZvtx->SetBinError(37,7,0.045303);

// xbin: 0.500000 to 0.600000
idEffEtaZvtx->SetBinContent(38,7,0.920635);
idEffEtaZvtx->SetBinError(38,7,0.035630);

// xbin: 0.600000 to 0.700000
idEffEtaZvtx->SetBinContent(39,7,0.928571);
idEffEtaZvtx->SetBinError(39,7,0.032348);

// xbin: 0.700000 to 0.800000
idEffEtaZvtx->SetBinContent(40,7,0.957143);
idEffEtaZvtx->SetBinError(40,7,0.026810);

// xbin: 0.800000 to 0.900000
idEffEtaZvtx->SetBinContent(41,7,0.828571);
idEffEtaZvtx->SetBinError(41,7,0.045020);

// xbin: 0.900000 to 1.000000
idEffEtaZvtx->SetBinContent(42,7,0.934426);
idEffEtaZvtx->SetBinError(42,7,0.033788);

// xbin: 1.000000 to 1.100000
idEffEtaZvtx->SetBinContent(43,7,0.962963);
idEffEtaZvtx->SetBinError(43,7,0.046263);

// xbin: 1.500000 to 1.600000
idEffEtaZvtx->SetBinContent(48,7,0.864407);
idEffEtaZvtx->SetBinError(48,7,0.045040);

// xbin: 1.600000 to 1.700000
idEffEtaZvtx->SetBinContent(49,7,0.941176);
idEffEtaZvtx->SetBinError(49,7,0.045437);

// xbin: 1.700000 to 1.800000
idEffEtaZvtx->SetBinContent(50,7,0.878049);
idEffEtaZvtx->SetBinError(50,7,0.052237);

// xbin: 1.800000 to 1.900000
idEffEtaZvtx->SetBinContent(51,7,0.961538);
idEffEtaZvtx->SetBinError(51,7,0.047824);

// xbin: 1.900000 to 2.000000
idEffEtaZvtx->SetBinContent(52,7,0.961538);
idEffEtaZvtx->SetBinError(52,7,0.047824);

// xbin: 2.000000 to 2.100000
idEffEtaZvtx->SetBinContent(53,7,0.960000);
idEffEtaZvtx->SetBinError(53,7,0.049493);

// xbin: 2.100000 to 2.200000
idEffEtaZvtx->SetBinContent(54,7,0.916667);
idEffEtaZvtx->SetBinError(54,7,0.061485);

// xbin: 2.200000 to 2.300000
idEffEtaZvtx->SetBinContent(55,7,0.933333);
idEffEtaZvtx->SetBinError(55,7,0.075941);

////////////////////////////////////////////////////
// ybin: 23.000000 to 30.000000

// xbin: -2.300000 to -2.200000
idEffEtaZvtx->SetBinContent(10,8,0.600000);
idEffEtaZvtx->SetBinError(10,8,0.174964);

// xbin: -2.200000 to -2.100000
idEffEtaZvtx->SetBinContent(11,8,1.000000);
idEffEtaZvtx->SetBinError(11,8,0.140859);

// xbin: -2.100000 to -2.000000
idEffEtaZvtx->SetBinContent(12,8,1.000000);
idEffEtaZvtx->SetBinError(12,8,0.123718);

// xbin: -2.000000 to -1.900000
idEffEtaZvtx->SetBinContent(13,8,1.000000);
idEffEtaZvtx->SetBinError(13,8,0.082988);

// xbin: -1.900000 to -1.800000
idEffEtaZvtx->SetBinContent(14,8,0.636364);
idEffEtaZvtx->SetBinError(14,8,0.130024);

// xbin: -1.800000 to -1.700000
idEffEtaZvtx->SetBinContent(15,8,0.818182);
idEffEtaZvtx->SetBinError(15,8,0.112604);

// xbin: -1.700000 to -1.600000
idEffEtaZvtx->SetBinContent(16,8,0.733333);
idEffEtaZvtx->SetBinError(16,8,0.107397);

// xbin: -1.600000 to -1.500000
idEffEtaZvtx->SetBinContent(17,8,0.952381);
idEffEtaZvtx->SetBinError(17,8,0.057516);

// xbin: -1.100000 to -1.000000
idEffEtaZvtx->SetBinContent(22,8,0.916667);
idEffEtaZvtx->SetBinError(22,8,0.090351);

// xbin: -1.000000 to -0.900000
idEffEtaZvtx->SetBinContent(23,8,0.909091);
idEffEtaZvtx->SetBinError(23,8,0.096428);

// xbin: -0.900000 to -0.800000
idEffEtaZvtx->SetBinContent(24,8,0.933333);
idEffEtaZvtx->SetBinError(24,8,0.075941);

// xbin: -0.800000 to -0.700000
idEffEtaZvtx->SetBinContent(25,8,1.000000);
idEffEtaZvtx->SetBinError(25,8,0.038431);

// xbin: -0.700000 to -0.600000
idEffEtaZvtx->SetBinContent(26,8,0.947368);
idEffEtaZvtx->SetBinError(26,8,0.062584);

// xbin: -0.600000 to -0.500000
idEffEtaZvtx->SetBinContent(27,8,0.952381);
idEffEtaZvtx->SetBinError(27,8,0.057516);

// xbin: -0.500000 to -0.400000
idEffEtaZvtx->SetBinContent(28,8,1.000000);
idEffEtaZvtx->SetBinError(28,8,0.034461);

// xbin: -0.400000 to -0.300000
idEffEtaZvtx->SetBinContent(29,8,0.931035);
idEffEtaZvtx->SetBinError(29,8,0.052264);

// xbin: -0.300000 to -0.200000
idEffEtaZvtx->SetBinContent(30,8,0.961538);
idEffEtaZvtx->SetBinError(30,8,0.047824);

// xbin: -0.200000 to -0.100000
idEffEtaZvtx->SetBinContent(31,8,0.966667);
idEffEtaZvtx->SetBinError(31,8,0.042137);

// xbin: -0.100000 to 0.000000
idEffEtaZvtx->SetBinContent(32,8,0.923077);
idEffEtaZvtx->SetBinError(32,8,0.057435);

// xbin: 0.000000 to 0.100000
idEffEtaZvtx->SetBinContent(33,8,0.923077);
idEffEtaZvtx->SetBinError(33,8,0.057435);

// xbin: 0.100000 to 0.200000
idEffEtaZvtx->SetBinContent(34,8,0.850000);
idEffEtaZvtx->SetBinError(34,8,0.080423);

// xbin: 0.200000 to 0.300000
idEffEtaZvtx->SetBinContent(35,8,0.818182);
idEffEtaZvtx->SetBinError(35,8,0.081223);

// xbin: 0.300000 to 0.400000
idEffEtaZvtx->SetBinContent(36,8,0.826087);
idEffEtaZvtx->SetBinError(36,8,0.078446);

// xbin: 0.400000 to 0.500000
idEffEtaZvtx->SetBinContent(37,8,0.880000);
idEffEtaZvtx->SetBinError(37,8,0.067135);

// xbin: 0.500000 to 0.600000
idEffEtaZvtx->SetBinContent(38,8,0.928571);
idEffEtaZvtx->SetBinError(38,8,0.053882);

// xbin: 0.600000 to 0.700000
idEffEtaZvtx->SetBinContent(39,8,1.000000);
idEffEtaZvtx->SetBinError(39,8,0.035690);

// xbin: 0.700000 to 0.800000
idEffEtaZvtx->SetBinContent(40,8,0.857143);
idEffEtaZvtx->SetBinError(40,8,0.066935);

// xbin: 0.800000 to 0.900000
idEffEtaZvtx->SetBinContent(41,8,0.769231);
idEffEtaZvtx->SetBinError(41,8,0.080408);

// xbin: 0.900000 to 1.000000
idEffEtaZvtx->SetBinContent(42,8,0.857143);
idEffEtaZvtx->SetBinError(42,8,0.066935);

// xbin: 1.000000 to 1.100000
idEffEtaZvtx->SetBinContent(43,8,0.928571);
idEffEtaZvtx->SetBinError(43,8,0.080211);

// xbin: 1.500000 to 1.600000
idEffEtaZvtx->SetBinContent(48,8,0.826087);
idEffEtaZvtx->SetBinError(48,8,0.078446);

// xbin: 1.600000 to 1.700000
idEffEtaZvtx->SetBinContent(49,8,1.000000);
idEffEtaZvtx->SetBinError(49,8,0.066496);

// xbin: 1.700000 to 1.800000
idEffEtaZvtx->SetBinContent(50,8,0.900000);
idEffEtaZvtx->SetBinError(50,8,0.103362);

// xbin: 1.800000 to 1.900000
idEffEtaZvtx->SetBinContent(51,8,1.000000);
idEffEtaZvtx->SetBinError(51,8,0.163299);

// xbin: 1.900000 to 2.000000
idEffEtaZvtx->SetBinContent(52,8,1.000000);
idEffEtaZvtx->SetBinError(52,8,0.140859);

// xbin: 2.000000 to 2.100000
idEffEtaZvtx->SetBinContent(53,8,1.000000);
idEffEtaZvtx->SetBinError(53,8,0.082988);

// xbin: 2.100000 to 2.200000
idEffEtaZvtx->SetBinContent(54,8,0.500000);
idEffEtaZvtx->SetBinError(54,8,0.223607);

// xbin: 2.200000 to 2.300000
idEffEtaZvtx->SetBinContent(55,8,1.000000);
idEffEtaZvtx->SetBinError(55,8,0.235702);

////////////////////////////////////////////////////
// ybin: 30.000000 to 39.000000

// xbin: -2.300000 to -2.200000
idEffEtaZvtx->SetBinContent(10,9,0.600000);
idEffEtaZvtx->SetBinError(10,9,0.174964);

// xbin: -2.200000 to -2.100000
idEffEtaZvtx->SetBinContent(11,9,1.000000);
idEffEtaZvtx->SetBinError(11,9,0.163299);

// xbin: -2.100000 to -2.000000
idEffEtaZvtx->SetBinContent(12,9,0.500000);
idEffEtaZvtx->SetBinError(12,9,0.223607);

// xbin: -2.000000 to -1.900000
idEffEtaZvtx->SetBinContent(13,9,0.818182);
idEffEtaZvtx->SetBinError(13,9,0.112604);

// xbin: -1.900000 to -1.800000
idEffEtaZvtx->SetBinContent(14,9,0.909091);
idEffEtaZvtx->SetBinError(14,9,0.096428);

// xbin: -1.800000 to -1.700000
idEffEtaZvtx->SetBinContent(15,9,1.000000);
idEffEtaZvtx->SetBinError(15,9,0.058709);

// xbin: -1.700000 to -1.600000
idEffEtaZvtx->SetBinContent(16,9,0.769231);
idEffEtaZvtx->SetBinError(16,9,0.110554);

// xbin: -1.600000 to -1.500000
idEffEtaZvtx->SetBinContent(17,9,0.812500);
idEffEtaZvtx->SetBinError(17,9,0.095377);

// xbin: -1.100000 to -1.000000
idEffEtaZvtx->SetBinContent(22,9,0.888889);
idEffEtaZvtx->SetBinError(22,9,0.111340);

// xbin: -1.000000 to -0.900000
idEffEtaZvtx->SetBinContent(23,9,0.636364);
idEffEtaZvtx->SetBinError(23,9,0.130024);

// xbin: -0.900000 to -0.800000
idEffEtaZvtx->SetBinContent(24,9,1.000000);
idEffEtaZvtx->SetBinError(24,9,0.055459);

// xbin: -0.800000 to -0.700000
idEffEtaZvtx->SetBinContent(25,9,0.941176);
idEffEtaZvtx->SetBinError(25,9,0.068623);

// xbin: -0.700000 to -0.600000
idEffEtaZvtx->SetBinContent(26,9,0.928571);
idEffEtaZvtx->SetBinError(26,9,0.080211);

// xbin: -0.600000 to -0.500000
idEffEtaZvtx->SetBinContent(27,9,0.880000);
idEffEtaZvtx->SetBinError(27,9,0.067135);

// xbin: -0.500000 to -0.400000
idEffEtaZvtx->SetBinContent(28,9,1.000000);
idEffEtaZvtx->SetBinError(28,9,0.066496);

// xbin: -0.400000 to -0.300000
idEffEtaZvtx->SetBinContent(29,9,1.000000);
idEffEtaZvtx->SetBinError(29,9,0.045403);

// xbin: -0.300000 to -0.200000
idEffEtaZvtx->SetBinContent(30,9,0.913043);
idEffEtaZvtx->SetBinError(30,9,0.063730);

// xbin: -0.200000 to -0.100000
idEffEtaZvtx->SetBinContent(31,9,0.916667);
idEffEtaZvtx->SetBinError(31,9,0.061485);

// xbin: -0.100000 to 0.000000
idEffEtaZvtx->SetBinContent(32,9,0.933333);
idEffEtaZvtx->SetBinError(32,9,0.050740);

// xbin: 0.000000 to 0.100000
idEffEtaZvtx->SetBinContent(33,9,0.954545);
idEffEtaZvtx->SetBinError(33,9,0.055277);

// xbin: 0.100000 to 0.200000
idEffEtaZvtx->SetBinContent(34,9,0.944444);
idEffEtaZvtx->SetBinError(34,9,0.065465);

// xbin: 0.200000 to 0.300000
idEffEtaZvtx->SetBinContent(35,9,1.000000);
idEffEtaZvtx->SetBinError(35,9,0.052550);

// xbin: 0.300000 to 0.400000
idEffEtaZvtx->SetBinContent(36,9,0.863636);
idEffEtaZvtx->SetBinError(36,9,0.074536);

// xbin: 0.400000 to 0.500000
idEffEtaZvtx->SetBinContent(37,9,0.964286);
idEffEtaZvtx->SetBinError(37,9,0.044801);

// xbin: 0.500000 to 0.600000
idEffEtaZvtx->SetBinContent(38,9,0.761905);
idEffEtaZvtx->SetBinError(38,9,0.089633);

// xbin: 0.600000 to 0.700000
idEffEtaZvtx->SetBinContent(39,9,0.727273);
idEffEtaZvtx->SetBinError(39,9,0.090906);

// xbin: 0.700000 to 0.800000
idEffEtaZvtx->SetBinContent(40,9,0.851852);
idEffEtaZvtx->SetBinError(40,9,0.068966);

// xbin: 0.800000 to 0.900000
idEffEtaZvtx->SetBinContent(41,9,0.925926);
idEffEtaZvtx->SetBinError(41,9,0.055602);

// xbin: 0.900000 to 1.000000
idEffEtaZvtx->SetBinContent(42,9,0.684211);
idEffEtaZvtx->SetBinError(42,9,0.100504);

// xbin: 1.000000 to 1.100000
idEffEtaZvtx->SetBinContent(43,9,0.846154);
idEffEtaZvtx->SetBinError(43,9,0.100000);

// xbin: 1.500000 to 1.600000
idEffEtaZvtx->SetBinContent(48,9,0.857143);
idEffEtaZvtx->SetBinError(48,9,0.131468);

// xbin: 1.600000 to 1.700000
idEffEtaZvtx->SetBinContent(49,9,1.000000);
idEffEtaZvtx->SetBinError(49,9,0.193649);

// xbin: 1.700000 to 1.800000
idEffEtaZvtx->SetBinContent(50,9,1.000000);
idEffEtaZvtx->SetBinError(50,9,0.123718);

// xbin: 1.800000 to 1.900000
idEffEtaZvtx->SetBinContent(51,9,1.000000);
idEffEtaZvtx->SetBinError(51,9,0.235702);

// xbin: 2.000000 to 2.100000
idEffEtaZvtx->SetBinContent(53,9,1.000000);
idEffEtaZvtx->SetBinError(53,9,0.235702);

////////////////////////////////////////////////////
// ybin: 39.000000 to 100.000000

// xbin: -2.300000 to -2.200000
idEffEtaZvtx->SetBinContent(10,10,1.000000);
idEffEtaZvtx->SetBinError(10,10,0.123718);

// xbin: -2.200000 to -2.100000
idEffEtaZvtx->SetBinContent(11,10,0.750000);
idEffEtaZvtx->SetBinError(11,10,0.138170);

// xbin: -2.100000 to -2.000000
idEffEtaZvtx->SetBinContent(12,10,0.857143);
idEffEtaZvtx->SetBinError(12,10,0.131468);

// xbin: -2.000000 to -1.900000
idEffEtaZvtx->SetBinContent(13,10,0.416667);
idEffEtaZvtx->SetBinError(13,10,0.127775);

// xbin: -1.900000 to -1.800000
idEffEtaZvtx->SetBinContent(14,10,0.916667);
idEffEtaZvtx->SetBinError(14,10,0.090351);

// xbin: -1.800000 to -1.700000
idEffEtaZvtx->SetBinContent(15,10,0.684211);
idEffEtaZvtx->SetBinError(15,10,0.100504);

// xbin: -1.700000 to -1.600000
idEffEtaZvtx->SetBinContent(16,10,0.850000);
idEffEtaZvtx->SetBinError(16,10,0.080423);

// xbin: -1.600000 to -1.500000
idEffEtaZvtx->SetBinContent(17,10,0.866667);
idEffEtaZvtx->SetBinError(17,10,0.089854);

// xbin: -1.100000 to -1.000000
idEffEtaZvtx->SetBinContent(22,10,1.000000);
idEffEtaZvtx->SetBinError(22,10,0.123718);

// xbin: -1.000000 to -0.900000
idEffEtaZvtx->SetBinContent(23,10,0.833333);
idEffEtaZvtx->SetBinError(23,10,0.087287);

// xbin: -0.900000 to -0.800000
idEffEtaZvtx->SetBinContent(24,10,0.850000);
idEffEtaZvtx->SetBinError(24,10,0.080423);

// xbin: -0.800000 to -0.700000
idEffEtaZvtx->SetBinContent(25,10,0.722222);
idEffEtaZvtx->SetBinError(25,10,0.100000);

// xbin: -0.700000 to -0.600000
idEffEtaZvtx->SetBinContent(26,10,0.600000);
idEffEtaZvtx->SetBinError(26,10,0.116002);

// xbin: -0.600000 to -0.500000
idEffEtaZvtx->SetBinContent(27,10,0.750000);
idEffEtaZvtx->SetBinError(27,10,0.138170);

// xbin: -0.500000 to -0.400000
idEffEtaZvtx->SetBinContent(28,10,0.782609);
idEffEtaZvtx->SetBinError(28,10,0.083758);

// xbin: -0.400000 to -0.300000
idEffEtaZvtx->SetBinContent(29,10,0.812500);
idEffEtaZvtx->SetBinError(29,10,0.095377);

// xbin: -0.300000 to -0.200000
idEffEtaZvtx->SetBinContent(30,10,0.812500);
idEffEtaZvtx->SetBinError(30,10,0.095377);

// xbin: -0.200000 to -0.100000
idEffEtaZvtx->SetBinContent(31,10,0.714286);
idEffEtaZvtx->SetBinError(31,10,0.112418);

// xbin: -0.100000 to 0.000000
idEffEtaZvtx->SetBinContent(32,10,0.705882);
idEffEtaZvtx->SetBinError(32,10,0.103939);

// xbin: 0.000000 to 0.100000
idEffEtaZvtx->SetBinContent(33,10,0.708333);
idEffEtaZvtx->SetBinError(33,10,0.088823);

// xbin: 0.100000 to 0.200000
idEffEtaZvtx->SetBinContent(34,10,0.450000);
idEffEtaZvtx->SetBinError(34,10,0.103825);

// xbin: 0.200000 to 0.300000
idEffEtaZvtx->SetBinContent(35,10,0.764706);
idEffEtaZvtx->SetBinError(35,10,0.098465);

// xbin: 0.300000 to 0.400000
idEffEtaZvtx->SetBinContent(36,10,0.684211);
idEffEtaZvtx->SetBinError(36,10,0.100504);

// xbin: 0.400000 to 0.500000
idEffEtaZvtx->SetBinContent(37,10,0.636364);
idEffEtaZvtx->SetBinError(37,10,0.130024);

// xbin: 0.500000 to 0.600000
idEffEtaZvtx->SetBinContent(38,10,0.695652);
idEffEtaZvtx->SetBinError(38,10,0.091483);

// xbin: 0.600000 to 0.700000
idEffEtaZvtx->SetBinContent(39,10,0.615385);
idEffEtaZvtx->SetBinError(39,10,0.090691);

// xbin: 0.700000 to 0.800000
idEffEtaZvtx->SetBinContent(40,10,0.692308);
idEffEtaZvtx->SetBinError(40,10,0.086724);

// xbin: 0.800000 to 0.900000
idEffEtaZvtx->SetBinContent(41,10,0.769231);
idEffEtaZvtx->SetBinError(41,10,0.080408);

// xbin: 0.900000 to 1.000000
idEffEtaZvtx->SetBinContent(42,10,0.545455);
idEffEtaZvtx->SetBinError(42,10,0.133235);

// xbin: 1.000000 to 1.100000
idEffEtaZvtx->SetBinContent(43,10,0.600000);
idEffEtaZvtx->SetBinError(43,10,0.136735);

// xbin: 1.500000 to 1.600000
idEffEtaZvtx->SetBinContent(48,10,0.500000);
idEffEtaZvtx->SetBinError(48,10,0.166667);

////////////////////////////////////////////////////
// ybin: over 100.000000
}
