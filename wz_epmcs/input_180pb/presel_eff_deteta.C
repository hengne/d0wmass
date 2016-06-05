{
const int n_PreSelEffDetEta_xbins = 34;
float PreSelEffDetEta_xbins[n_PreSelEffDetEta_xbins+1] = {-3.200000 ,-2.700000 ,-2.320000 ,-1.800000 ,-1.600000 ,-1.480000 ,-1.070000 ,-1.000000 ,-0.900000 ,-0.800000 ,-0.700000 ,-0.600000 ,-0.500000 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.400000 ,0.500000 ,0.600000 ,0.700000 ,0.800000 ,0.900000 ,1.000000 ,1.070000 ,1.480000 ,1.600000 ,1.800000 ,2.320000 ,2.700000 ,3.200000  };

TH1F *PreSelEffDetEta = new TH1F("PreSelEffDetEta","preselection efficiency vs deteta", n_PreSelEffDetEta_xbins, PreSelEffDetEta_xbins);

// -2.320000 to -1.800000
PreSelEffDetEta->SetBinContent(3,1.030675);
PreSelEffDetEta->SetBinError(3,0.043803);

// -1.800000 to -1.600000
PreSelEffDetEta->SetBinContent(4,0.986364);
PreSelEffDetEta->SetBinError(4,0.027938);

// -1.600000 to -1.480000
PreSelEffDetEta->SetBinContent(5,0.993421);
PreSelEffDetEta->SetBinError(5,0.031314);

// -1.070000 to -1.000000
PreSelEffDetEta->SetBinContent(7,0.967480);
PreSelEffDetEta->SetBinError(7,0.027801);

// -1.000000 to -0.900000
PreSelEffDetEta->SetBinContent(8,0.964169);
PreSelEffDetEta->SetBinError(8,0.018758);

// -0.900000 to -0.800000
PreSelEffDetEta->SetBinContent(9,0.975309);
PreSelEffDetEta->SetBinError(9,0.017175);

// -0.800000 to -0.700000
PreSelEffDetEta->SetBinContent(10,0.985207);
PreSelEffDetEta->SetBinError(10,0.015296);

// -0.700000 to -0.600000
PreSelEffDetEta->SetBinContent(11,1.002778);
PreSelEffDetEta->SetBinError(11,0.017005);

// -0.600000 to -0.500000
PreSelEffDetEta->SetBinContent(12,1.000000);
PreSelEffDetEta->SetBinError(12,0.012270);

// -0.500000 to -0.400000
PreSelEffDetEta->SetBinContent(13,0.985755);
PreSelEffDetEta->SetBinError(13,0.012468);

// -0.400000 to -0.300000
PreSelEffDetEta->SetBinContent(14,0.994318);
PreSelEffDetEta->SetBinError(14,0.013992);

// -0.300000 to -0.200000
PreSelEffDetEta->SetBinContent(15,1.012121);
PreSelEffDetEta->SetBinError(15,0.013237);

// -0.200000 to -0.100000
PreSelEffDetEta->SetBinContent(16,0.990172);
PreSelEffDetEta->SetBinError(16,0.014685);

// -0.100000 to 0.000000
PreSelEffDetEta->SetBinContent(17,0.977387);
PreSelEffDetEta->SetBinError(17,0.012474);

// 0.000000 to 0.100000
PreSelEffDetEta->SetBinContent(18,1.034682);
PreSelEffDetEta->SetBinError(18,0.016571);

// 0.100000 to 0.200000
PreSelEffDetEta->SetBinContent(19,1.002481);
PreSelEffDetEta->SetBinError(19,0.013507);

// 0.200000 to 0.300000
PreSelEffDetEta->SetBinContent(20,0.981233);
PreSelEffDetEta->SetBinError(20,0.014317);

// 0.300000 to 0.400000
PreSelEffDetEta->SetBinContent(21,0.975806);
PreSelEffDetEta->SetBinError(21,0.015652);

// 0.400000 to 0.500000
PreSelEffDetEta->SetBinContent(22,0.977591);
PreSelEffDetEta->SetBinError(22,0.015156);

// 0.500000 to 0.600000
PreSelEffDetEta->SetBinContent(23,0.968992);
PreSelEffDetEta->SetBinError(23,0.013917);

// 0.600000 to 0.700000
PreSelEffDetEta->SetBinContent(24,0.988732);
PreSelEffDetEta->SetBinError(24,0.015861);

// 0.700000 to 0.800000
PreSelEffDetEta->SetBinContent(25,1.002793);
PreSelEffDetEta->SetBinError(25,0.014144);

// 0.800000 to 0.900000
PreSelEffDetEta->SetBinContent(26,1.002674);
PreSelEffDetEta->SetBinError(26,0.014548);

// 0.900000 to 1.000000
PreSelEffDetEta->SetBinContent(27,0.952247);
PreSelEffDetEta->SetBinError(27,0.017762);

// 1.000000 to 1.070000
PreSelEffDetEta->SetBinContent(28,0.954545);
PreSelEffDetEta->SetBinError(28,0.027402);

// 1.480000 to 1.600000
PreSelEffDetEta->SetBinContent(30,0.996139);
PreSelEffDetEta->SetBinError(30,0.020086);

// 1.600000 to 1.800000
PreSelEffDetEta->SetBinContent(31,0.984472);
PreSelEffDetEta->SetBinError(31,0.018673);

// 1.800000 to 2.320000
PreSelEffDetEta->SetBinContent(32,0.994220);
PreSelEffDetEta->SetBinError(32,0.028874);
}
