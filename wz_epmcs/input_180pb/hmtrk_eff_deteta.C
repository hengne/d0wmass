{
const int n_idEffDetEta_xbins = 56;
float idEffDetEta_xbins[n_idEffDetEta_xbins+1] = {-3.200000 ,-3.100000 ,-3.000000 ,-2.900000 ,-2.800000 ,-2.700000 ,-2.600000 ,-2.500000 ,-2.400000 ,-2.300000 ,-2.000000 ,-1.800000 ,-1.600000 ,-1.500000 ,-1.400000 ,-1.300000 ,-1.200000 ,-1.100000 ,-1.000000 ,-0.900000 ,-0.800000 ,-0.700000 ,-0.600000 ,-0.500000 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.400000 ,0.500000 ,0.600000 ,0.700000 ,0.800000 ,0.900000 ,1.000000 ,1.100000 ,1.200000 ,1.300000 ,1.400000 ,1.500000 ,1.600000 ,1.800000 ,2.000000 ,2.300000 ,2.400000 ,2.500000 ,2.600000 ,2.700000 ,2.800000 ,2.900000 ,3.000000 ,3.100000 ,3.200000  };

TH1F *idEffDetEta = new TH1F("idEffDetEta","hmtrk efficiency vs deteta, pt > 25GeV", n_idEffDetEta_xbins, idEffDetEta_xbins);

// -2.300000 to -2.000000
idEffDetEta->SetBinContent(10,0.963726);
idEffDetEta->SetBinError(10,0.019907);

// -2.000000 to -1.800000
idEffDetEta->SetBinContent(11,0.928428);
idEffDetEta->SetBinError(11,0.019743);

// -1.800000 to -1.600000
idEffDetEta->SetBinContent(12,0.930123);
idEffDetEta->SetBinError(12,0.014421);

// -1.600000 to -1.500000
idEffDetEta->SetBinContent(13,0.959993);
idEffDetEta->SetBinError(13,0.013955);

// -1.100000 to -1.000000
idEffDetEta->SetBinContent(18,0.953970);
idEffDetEta->SetBinError(18,0.016080);

// -1.000000 to -0.900000
idEffDetEta->SetBinContent(19,0.912377);
idEffDetEta->SetBinError(19,0.014287);

// -0.900000 to -0.800000
idEffDetEta->SetBinContent(20,0.932281);
idEffDetEta->SetBinError(20,0.012543);

// -0.800000 to -0.700000
idEffDetEta->SetBinContent(21,0.936744);
idEffDetEta->SetBinError(21,0.011705);

// -0.700000 to -0.600000
idEffDetEta->SetBinContent(22,0.924827);
idEffDetEta->SetBinError(22,0.012299);

// -0.600000 to -0.500000
idEffDetEta->SetBinContent(23,0.936730);
idEffDetEta->SetBinError(23,0.010902);

// -0.500000 to -0.400000
idEffDetEta->SetBinContent(24,0.921204);
idEffDetEta->SetBinError(24,0.012000);

// -0.400000 to -0.300000
idEffDetEta->SetBinContent(25,0.932866);
idEffDetEta->SetBinError(25,0.011515);

// -0.300000 to -0.200000
idEffDetEta->SetBinContent(26,0.881315);
idEffDetEta->SetBinError(26,0.014904);

// -0.200000 to -0.100000
idEffDetEta->SetBinContent(27,0.909513);
idEffDetEta->SetBinError(27,0.012220);

// -0.100000 to 0.000000
idEffDetEta->SetBinContent(28,0.938980);
idEffDetEta->SetBinError(28,0.010338);

// 0.000000 to 0.100000
idEffDetEta->SetBinContent(29,0.902761);
idEffDetEta->SetBinError(29,0.013504);

// 0.100000 to 0.200000
idEffDetEta->SetBinContent(30,0.928582);
idEffDetEta->SetBinError(30,0.010921);

// 0.200000 to 0.300000
idEffDetEta->SetBinContent(31,0.905571);
idEffDetEta->SetBinError(31,0.013276);

// 0.300000 to 0.400000
idEffDetEta->SetBinContent(32,0.945185);
idEffDetEta->SetBinError(32,0.010518);

// 0.400000 to 0.500000
idEffDetEta->SetBinContent(33,0.934597);
idEffDetEta->SetBinError(33,0.011605);

// 0.500000 to 0.600000
idEffDetEta->SetBinContent(34,0.931821);
idEffDetEta->SetBinError(34,0.011200);

// 0.600000 to 0.700000
idEffDetEta->SetBinContent(35,0.931067);
idEffDetEta->SetBinError(35,0.011841);

// 0.700000 to 0.800000
idEffDetEta->SetBinContent(36,0.940781);
idEffDetEta->SetBinError(36,0.010988);

// 0.800000 to 0.900000
idEffDetEta->SetBinContent(37,0.929027);
idEffDetEta->SetBinError(37,0.011675);

// 0.900000 to 1.000000
idEffDetEta->SetBinContent(38,0.939192);
idEffDetEta->SetBinError(38,0.011746);

// 1.000000 to 1.100000
idEffDetEta->SetBinContent(39,0.984429);
idEffDetEta->SetBinError(39,0.009397);

// 1.500000 to 1.600000
idEffDetEta->SetBinContent(44,0.954160);
idEffDetEta->SetBinError(44,0.011336);

// 1.600000 to 1.800000
idEffDetEta->SetBinContent(45,0.962200);
idEffDetEta->SetBinError(45,0.009489);

// 1.800000 to 2.000000
idEffDetEta->SetBinContent(46,0.985177);
idEffDetEta->SetBinError(46,0.007540);

// 2.000000 to 2.300000
idEffDetEta->SetBinContent(47,0.973186);
idEffDetEta->SetBinError(47,0.010854);
}
