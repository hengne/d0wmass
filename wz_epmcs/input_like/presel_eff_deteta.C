{
const int n_PreSelEffDetEta_xbins = 34;
float PreSelEffDetEta_xbins[n_PreSelEffDetEta_xbins+1] = {-3.200000 ,-2.700000 ,-2.320000 ,-1.800000 ,-1.600000 ,-1.480000 ,-1.070000 ,-1.000000 ,-0.900000 ,-0.800000 ,-0.700000 ,-0.600000 ,-0.500000 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.400000 ,0.500000 ,0.600000 ,0.700000 ,0.800000 ,0.900000 ,1.000000 ,1.070000 ,1.480000 ,1.600000 ,1.800000 ,2.320000 ,2.700000 ,3.200000  };

TH1F *PreSelEffDetEta = new TH1F("PreSelEffDetEta","preselection efficiency vs deteta", n_PreSelEffDetEta_xbins, PreSelEffDetEta_xbins);

// -2.320000 to -1.800000
PreSelEffDetEta->SetBinContent(3,1.089655);
PreSelEffDetEta->SetBinError(3,0.038038);

// -1.800000 to -1.600000
PreSelEffDetEta->SetBinContent(4,0.971429);
PreSelEffDetEta->SetBinError(4,0.016557);

// -1.600000 to -1.480000
PreSelEffDetEta->SetBinContent(5,0.972414);
PreSelEffDetEta->SetBinError(5,0.017544);

// -1.070000 to -1.000000
PreSelEffDetEta->SetBinContent(7,0.973684);
PreSelEffDetEta->SetBinError(7,0.020541);

// -1.000000 to -0.900000
PreSelEffDetEta->SetBinContent(8,0.981685);
PreSelEffDetEta->SetBinError(8,0.015120);

// -0.900000 to -0.800000
PreSelEffDetEta->SetBinContent(9,0.996667);
PreSelEffDetEta->SetBinError(9,0.011382);

// -0.800000 to -0.700000
PreSelEffDetEta->SetBinContent(10,0.996785);
PreSelEffDetEta->SetBinError(10,0.008972);

// -0.700000 to -0.600000
PreSelEffDetEta->SetBinContent(11,0.996835);
PreSelEffDetEta->SetBinError(11,0.010814);

// -0.600000 to -0.500000
PreSelEffDetEta->SetBinContent(12,0.997319);
PreSelEffDetEta->SetBinError(12,0.008381);

// -0.500000 to -0.400000
PreSelEffDetEta->SetBinContent(13,0.987500);
PreSelEffDetEta->SetBinError(13,0.008122);

// -0.400000 to -0.300000
PreSelEffDetEta->SetBinContent(14,0.988270);
PreSelEffDetEta->SetBinError(14,0.008642);

// -0.300000 to -0.200000
PreSelEffDetEta->SetBinContent(15,1.013559);
PreSelEffDetEta->SetBinError(15,0.010203);

// -0.200000 to -0.100000
PreSelEffDetEta->SetBinContent(16,0.997207);
PreSelEffDetEta->SetBinError(16,0.008728);

// -0.100000 to 0.000000
PreSelEffDetEta->SetBinContent(17,0.988796);
PreSelEffDetEta->SetBinError(17,0.008261);

// 0.000000 to 0.100000
PreSelEffDetEta->SetBinContent(18,1.000000);
PreSelEffDetEta->SetBinError(18,0.007935);

// 0.100000 to 0.200000
PreSelEffDetEta->SetBinContent(19,1.000000);
PreSelEffDetEta->SetBinError(19,0.008209);

// 0.200000 to 0.300000
PreSelEffDetEta->SetBinContent(20,1.003175);
PreSelEffDetEta->SetBinError(20,0.010911);

// 0.300000 to 0.400000
PreSelEffDetEta->SetBinContent(21,0.988060);
PreSelEffDetEta->SetBinError(21,0.010555);

// 0.400000 to 0.500000
PreSelEffDetEta->SetBinContent(22,0.981481);
PreSelEffDetEta->SetBinError(22,0.008016);

// 0.500000 to 0.600000
PreSelEffDetEta->SetBinContent(23,0.979943);
PreSelEffDetEta->SetBinError(23,0.011185);

// 0.600000 to 0.700000
PreSelEffDetEta->SetBinContent(24,0.979532);
PreSelEffDetEta->SetBinError(24,0.009899);

// 0.700000 to 0.800000
PreSelEffDetEta->SetBinContent(25,0.990826);
PreSelEffDetEta->SetBinError(25,0.008506);

// 0.800000 to 0.900000
PreSelEffDetEta->SetBinContent(26,1.009202);
PreSelEffDetEta->SetBinError(26,0.009691);

// 0.900000 to 1.000000
PreSelEffDetEta->SetBinContent(27,0.974522);
PreSelEffDetEta->SetBinError(27,0.011993);

// 1.000000 to 1.070000
PreSelEffDetEta->SetBinContent(28,0.964539);
PreSelEffDetEta->SetBinError(28,0.021388);

// 1.480000 to 1.600000
PreSelEffDetEta->SetBinContent(30,1.000000);
PreSelEffDetEta->SetBinError(30,0.013967);

// 1.600000 to 1.800000
PreSelEffDetEta->SetBinContent(31,0.976589);
PreSelEffDetEta->SetBinError(31,0.011286);

// 1.800000 to 2.320000
PreSelEffDetEta->SetBinContent(32,0.975758);
PreSelEffDetEta->SetBinError(32,0.017858);
}
