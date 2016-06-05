{
const int n_trkEffVsEtaZvtx_xbins = 64;
float trkEffVsEtaZvtx_xbins[n_trkEffVsEtaZvtx_xbins+1] = {-3.200000 ,-3.100000 ,-3.000000 ,-2.900000 ,-2.800000 ,-2.700000 ,-2.600000 ,-2.500000 ,-2.400000 ,-2.300000 ,-2.200000 ,-2.100000 ,-2.000000 ,-1.900000 ,-1.800000 ,-1.700000 ,-1.600000 ,-1.500000 ,-1.400000 ,-1.300000 ,-1.200000 ,-1.100000 ,-1.000000 ,-0.900000 ,-0.800000 ,-0.700000 ,-0.600000 ,-0.500000 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.400000 ,0.500000 ,0.600000 ,0.700000 ,0.800000 ,0.900000 ,1.000000 ,1.100000 ,1.200000 ,1.300000 ,1.400000 ,1.500000 ,1.600000 ,1.700000 ,1.800000 ,1.900000 ,2.000000 ,2.100000 ,2.200000 ,2.300000 ,2.400000 ,2.500000 ,2.600000 ,2.700000 ,2.800000 ,2.900000 ,3.000000 ,3.100000 ,3.200000  };

const int n_trkEffVsEtaZvtx_ybins = 5;
float trkEffVsEtaZvtx_ybins[n_trkEffVsEtaZvtx_ybins+1] = {-100.000000 ,-39.000000 ,-10.000000 ,10.000000 ,39.000000 ,100.000000  };

TH2F *trkEffVsEtaZvtx = new TH2F("trkEffVsEtaZvtx","track efficiency vs detector eta and zvtx", n_trkEffVsEtaZvtx_xbins, trkEffVsEtaZvtx_xbins, n_trkEffVsEtaZvtx_ybins, trkEffVsEtaZvtx_ybins);

////////////////////////////////////////////////////
// ybin: under -100.000000

////////////////////////////////////////////////////
// ybin: -100.000000 to -39.000000

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,1,0.188412);
trkEffVsEtaZvtx->SetBinError(16,1,0.135468);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,1,0.188412);
trkEffVsEtaZvtx->SetBinError(17,1,0.135468);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,1,0.637931);
trkEffVsEtaZvtx->SetBinError(22,1,0.113936);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,1,0.637931);
trkEffVsEtaZvtx->SetBinError(23,1,0.113936);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,1,0.732025);
trkEffVsEtaZvtx->SetBinError(24,1,0.100549);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,1,0.732025);
trkEffVsEtaZvtx->SetBinError(25,1,0.100549);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,1,0.711470);
trkEffVsEtaZvtx->SetBinError(26,1,0.080115);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,1,0.711470);
trkEffVsEtaZvtx->SetBinError(27,1,0.080115);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,1,0.594957);
trkEffVsEtaZvtx->SetBinError(28,1,0.096685);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,1,0.594957);
trkEffVsEtaZvtx->SetBinError(29,1,0.096685);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,1,0.704083);
trkEffVsEtaZvtx->SetBinError(30,1,0.099650);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,1,0.704083);
trkEffVsEtaZvtx->SetBinError(31,1,0.099650);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,1,0.835138);
trkEffVsEtaZvtx->SetBinError(32,1,0.076875);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,1,0.835138);
trkEffVsEtaZvtx->SetBinError(33,1,0.076875);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,1,0.596477);
trkEffVsEtaZvtx->SetBinError(34,1,0.092351);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,1,0.596477);
trkEffVsEtaZvtx->SetBinError(35,1,0.092351);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,1,0.761785);
trkEffVsEtaZvtx->SetBinError(36,1,0.097386);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,1,0.761785);
trkEffVsEtaZvtx->SetBinError(37,1,0.097386);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,1,0.816164);
trkEffVsEtaZvtx->SetBinError(38,1,0.078889);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,1,0.816164);
trkEffVsEtaZvtx->SetBinError(39,1,0.078889);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,1,0.908199);
trkEffVsEtaZvtx->SetBinError(40,1,0.066205);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,1,0.908199);
trkEffVsEtaZvtx->SetBinError(41,1,0.066205);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,1,0.857122);
trkEffVsEtaZvtx->SetBinError(42,1,0.096774);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,1,0.857122);
trkEffVsEtaZvtx->SetBinError(43,1,0.096774);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,1,0.837901);
trkEffVsEtaZvtx->SetBinError(48,1,0.063915);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,1,0.837901);
trkEffVsEtaZvtx->SetBinError(49,1,0.063915);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,1,0.840133);
trkEffVsEtaZvtx->SetBinError(50,1,0.082971);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,1,0.840133);
trkEffVsEtaZvtx->SetBinError(51,1,0.082971);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,1,0.752339);
trkEffVsEtaZvtx->SetBinError(52,1,0.107851);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,1,0.752339);
trkEffVsEtaZvtx->SetBinError(53,1,0.107851);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,1,0.752339);
trkEffVsEtaZvtx->SetBinError(54,1,0.107851);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,1,0.752339);
trkEffVsEtaZvtx->SetBinError(55,1,0.107851);

////////////////////////////////////////////////////
// ybin: -39.000000 to -10.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,2,0.334723);
trkEffVsEtaZvtx->SetBinError(10,2,0.097484);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,2,0.408652);
trkEffVsEtaZvtx->SetBinError(11,2,0.090081);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,2,0.315091);
trkEffVsEtaZvtx->SetBinError(12,2,0.076077);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,2,0.267594);
trkEffVsEtaZvtx->SetBinError(13,2,0.078468);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,2,0.305480);
trkEffVsEtaZvtx->SetBinError(14,2,0.066396);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,2,0.555955);
trkEffVsEtaZvtx->SetBinError(15,2,0.077861);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,2,0.561429);
trkEffVsEtaZvtx->SetBinError(16,2,0.067158);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,2,0.777799);
trkEffVsEtaZvtx->SetBinError(17,2,0.046573);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,2,0.719225);
trkEffVsEtaZvtx->SetBinError(22,2,0.055307);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,2,0.714197);
trkEffVsEtaZvtx->SetBinError(23,2,0.035838);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,2,0.747410);
trkEffVsEtaZvtx->SetBinError(24,2,0.037890);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,2,0.759692);
trkEffVsEtaZvtx->SetBinError(25,2,0.032642);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,2,0.792598);
trkEffVsEtaZvtx->SetBinError(26,2,0.033696);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,2,0.763994);
trkEffVsEtaZvtx->SetBinError(27,2,0.031812);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,2,0.798120);
trkEffVsEtaZvtx->SetBinError(28,2,0.029713);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,2,0.758669);
trkEffVsEtaZvtx->SetBinError(29,2,0.032792);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,2,0.781546);
trkEffVsEtaZvtx->SetBinError(30,2,0.033640);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,2,0.801570);
trkEffVsEtaZvtx->SetBinError(31,2,0.029694);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,2,0.810424);
trkEffVsEtaZvtx->SetBinError(32,2,0.029362);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,2,0.779582);
trkEffVsEtaZvtx->SetBinError(33,2,0.033992);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,2,0.799440);
trkEffVsEtaZvtx->SetBinError(34,2,0.029566);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,2,0.750147);
trkEffVsEtaZvtx->SetBinError(35,2,0.034627);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,2,0.841161);
trkEffVsEtaZvtx->SetBinError(36,2,0.028783);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,2,0.809049);
trkEffVsEtaZvtx->SetBinError(37,2,0.031439);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,2,0.751478);
trkEffVsEtaZvtx->SetBinError(38,2,0.033211);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,2,0.742492);
trkEffVsEtaZvtx->SetBinError(39,2,0.036889);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,2,0.712449);
trkEffVsEtaZvtx->SetBinError(40,2,0.038688);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,2,0.788583);
trkEffVsEtaZvtx->SetBinError(41,2,0.034291);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,2,0.712601);
trkEffVsEtaZvtx->SetBinError(42,2,0.039718);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,2,0.735628);
trkEffVsEtaZvtx->SetBinError(43,2,0.047891);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,2,0.948342);
trkEffVsEtaZvtx->SetBinError(48,2,0.019766);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,2,0.888232);
trkEffVsEtaZvtx->SetBinError(49,2,0.028376);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,2,0.870696);
trkEffVsEtaZvtx->SetBinError(50,2,0.033272);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,2,0.823185);
trkEffVsEtaZvtx->SetBinError(51,2,0.039660);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,2,0.801624);
trkEffVsEtaZvtx->SetBinError(52,2,0.044763);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,2,0.674046);
trkEffVsEtaZvtx->SetBinError(53,2,0.055171);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,2,0.735701);
trkEffVsEtaZvtx->SetBinError(54,2,0.056145);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,2,0.731125);
trkEffVsEtaZvtx->SetBinError(55,2,0.056887);

////////////////////////////////////////////////////
// ybin: -10.000000 to 10.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,3,0.538486);
trkEffVsEtaZvtx->SetBinError(10,3,0.076946);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,3,0.512839);
trkEffVsEtaZvtx->SetBinError(11,3,0.077130);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,3,0.632675);
trkEffVsEtaZvtx->SetBinError(12,3,0.067047);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,3,0.638336);
trkEffVsEtaZvtx->SetBinError(13,3,0.068177);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,3,0.857188);
trkEffVsEtaZvtx->SetBinError(14,3,0.044408);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,3,0.873084);
trkEffVsEtaZvtx->SetBinError(15,3,0.042507);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,3,0.825298);
trkEffVsEtaZvtx->SetBinError(16,3,0.037389);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,3,0.888981);
trkEffVsEtaZvtx->SetBinError(17,3,0.035508);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,3,0.794151);
trkEffVsEtaZvtx->SetBinError(22,3,0.048695);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,3,0.759439);
trkEffVsEtaZvtx->SetBinError(23,3,0.036850);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,3,0.802584);
trkEffVsEtaZvtx->SetBinError(24,3,0.031696);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,3,0.779256);
trkEffVsEtaZvtx->SetBinError(25,3,0.033292);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,3,0.816125);
trkEffVsEtaZvtx->SetBinError(26,3,0.029336);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,3,0.850604);
trkEffVsEtaZvtx->SetBinError(27,3,0.027086);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,3,0.803055);
trkEffVsEtaZvtx->SetBinError(28,3,0.028213);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,3,0.818209);
trkEffVsEtaZvtx->SetBinError(29,3,0.029045);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,3,0.797652);
trkEffVsEtaZvtx->SetBinError(30,3,0.030920);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,3,0.836984);
trkEffVsEtaZvtx->SetBinError(31,3,0.027252);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,3,0.781748);
trkEffVsEtaZvtx->SetBinError(32,3,0.029344);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,3,0.881391);
trkEffVsEtaZvtx->SetBinError(33,3,0.024470);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,3,0.811344);
trkEffVsEtaZvtx->SetBinError(34,3,0.026839);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,3,0.836666);
trkEffVsEtaZvtx->SetBinError(35,3,0.026027);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,3,0.824770);
trkEffVsEtaZvtx->SetBinError(36,3,0.027286);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,3,0.822887);
trkEffVsEtaZvtx->SetBinError(37,3,0.028844);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,3,0.830717);
trkEffVsEtaZvtx->SetBinError(38,3,0.027282);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,3,0.851682);
trkEffVsEtaZvtx->SetBinError(39,3,0.026406);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,3,0.813223);
trkEffVsEtaZvtx->SetBinError(40,3,0.028854);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,3,0.723561);
trkEffVsEtaZvtx->SetBinError(41,3,0.034102);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,3,0.761329);
trkEffVsEtaZvtx->SetBinError(42,3,0.034074);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,3,0.833370);
trkEffVsEtaZvtx->SetBinError(43,3,0.042216);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,3,0.948380);
trkEffVsEtaZvtx->SetBinError(48,3,0.021639);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,3,0.945151);
trkEffVsEtaZvtx->SetBinError(49,3,0.025323);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,3,0.774263);
trkEffVsEtaZvtx->SetBinError(50,3,0.043052);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,3,0.771137);
trkEffVsEtaZvtx->SetBinError(51,3,0.045739);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,3,0.766692);
trkEffVsEtaZvtx->SetBinError(52,3,0.044231);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,3,0.691382);
trkEffVsEtaZvtx->SetBinError(53,3,0.050606);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,3,0.690941);
trkEffVsEtaZvtx->SetBinError(54,3,0.061035);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,3,0.625025);
trkEffVsEtaZvtx->SetBinError(55,3,0.059263);

////////////////////////////////////////////////////
// ybin: 10.000000 to 39.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,4,0.602895);
trkEffVsEtaZvtx->SetBinError(10,4,0.079736);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,4,0.714979);
trkEffVsEtaZvtx->SetBinError(11,4,0.071487);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,4,0.664131);
trkEffVsEtaZvtx->SetBinError(12,4,0.071876);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,4,0.619900);
trkEffVsEtaZvtx->SetBinError(13,4,0.071328);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,4,0.818429);
trkEffVsEtaZvtx->SetBinError(14,4,0.046477);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,4,0.794945);
trkEffVsEtaZvtx->SetBinError(15,4,0.048217);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,4,0.899179);
trkEffVsEtaZvtx->SetBinError(16,4,0.033226);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,4,0.960340);
trkEffVsEtaZvtx->SetBinError(17,4,0.022443);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,4,0.766197);
trkEffVsEtaZvtx->SetBinError(22,4,0.052334);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,4,0.741008);
trkEffVsEtaZvtx->SetBinError(23,4,0.039898);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,4,0.767856);
trkEffVsEtaZvtx->SetBinError(24,4,0.037743);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,4,0.777401);
trkEffVsEtaZvtx->SetBinError(25,4,0.037056);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,4,0.887540);
trkEffVsEtaZvtx->SetBinError(26,4,0.027931);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,4,0.822917);
trkEffVsEtaZvtx->SetBinError(27,4,0.031078);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,4,0.721228);
trkEffVsEtaZvtx->SetBinError(28,4,0.037804);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,4,0.741752);
trkEffVsEtaZvtx->SetBinError(29,4,0.036051);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,4,0.827624);
trkEffVsEtaZvtx->SetBinError(30,4,0.031627);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,4,0.786587);
trkEffVsEtaZvtx->SetBinError(31,4,0.031178);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,4,0.813715);
trkEffVsEtaZvtx->SetBinError(32,4,0.028932);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,4,0.764985);
trkEffVsEtaZvtx->SetBinError(33,4,0.032512);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,4,0.775491);
trkEffVsEtaZvtx->SetBinError(34,4,0.032607);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,4,0.771173);
trkEffVsEtaZvtx->SetBinError(35,4,0.035007);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,4,0.702008);
trkEffVsEtaZvtx->SetBinError(36,4,0.037477);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,4,0.813732);
trkEffVsEtaZvtx->SetBinError(37,4,0.031879);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,4,0.666323);
trkEffVsEtaZvtx->SetBinError(38,4,0.035944);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,4,0.818227);
trkEffVsEtaZvtx->SetBinError(39,4,0.031810);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,4,0.792832);
trkEffVsEtaZvtx->SetBinError(40,4,0.031681);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,4,0.787847);
trkEffVsEtaZvtx->SetBinError(41,4,0.031849);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,4,0.759272);
trkEffVsEtaZvtx->SetBinError(42,4,0.033983);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,4,0.728775);
trkEffVsEtaZvtx->SetBinError(43,4,0.050085);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,4,0.861038);
trkEffVsEtaZvtx->SetBinError(48,4,0.037311);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,4,0.697291);
trkEffVsEtaZvtx->SetBinError(49,4,0.056823);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,4,0.572050);
trkEffVsEtaZvtx->SetBinError(50,4,0.061800);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,4,0.384346);
trkEffVsEtaZvtx->SetBinError(51,4,0.060234);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,4,0.414350);
trkEffVsEtaZvtx->SetBinError(52,4,0.076473);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,4,0.504033);
trkEffVsEtaZvtx->SetBinError(53,4,0.073205);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,4,0.419066);
trkEffVsEtaZvtx->SetBinError(54,4,0.087873);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,4,0.337519);
trkEffVsEtaZvtx->SetBinError(55,4,0.087506);

////////////////////////////////////////////////////
// ybin: 39.000000 to 100.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,5,0.694943);
trkEffVsEtaZvtx->SetBinError(10,5,0.134567);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,5,0.694943);
trkEffVsEtaZvtx->SetBinError(11,5,0.134567);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,5,0.694943);
trkEffVsEtaZvtx->SetBinError(12,5,0.134567);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,5,0.694943);
trkEffVsEtaZvtx->SetBinError(13,5,0.134567);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,5,0.852433);
trkEffVsEtaZvtx->SetBinError(14,5,0.091770);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,5,0.852433);
trkEffVsEtaZvtx->SetBinError(15,5,0.091770);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,5,0.961593);
trkEffVsEtaZvtx->SetBinError(16,5,0.057856);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,5,0.961593);
trkEffVsEtaZvtx->SetBinError(17,5,0.057856);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,5,0.840182);
trkEffVsEtaZvtx->SetBinError(22,5,0.106365);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,5,0.840182);
trkEffVsEtaZvtx->SetBinError(23,5,0.106365);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,5,0.846869);
trkEffVsEtaZvtx->SetBinError(24,5,0.077461);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,5,0.846869);
trkEffVsEtaZvtx->SetBinError(25,5,0.077461);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,5,0.639473);
trkEffVsEtaZvtx->SetBinError(26,5,0.119391);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,5,0.639473);
trkEffVsEtaZvtx->SetBinError(27,5,0.119391);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,5,0.670502);
trkEffVsEtaZvtx->SetBinError(28,5,0.091181);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,5,0.670502);
trkEffVsEtaZvtx->SetBinError(29,5,0.091181);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,5,0.749617);
trkEffVsEtaZvtx->SetBinError(30,5,0.091986);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,5,0.749617);
trkEffVsEtaZvtx->SetBinError(31,5,0.091986);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,5,0.868578);
trkEffVsEtaZvtx->SetBinError(32,5,0.081434);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,5,0.868578);
trkEffVsEtaZvtx->SetBinError(33,5,0.081434);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,5,0.650102);
trkEffVsEtaZvtx->SetBinError(34,5,0.095145);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,5,0.650102);
trkEffVsEtaZvtx->SetBinError(35,5,0.095145);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,5,0.492491);
trkEffVsEtaZvtx->SetBinError(36,5,0.100332);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,5,0.492491);
trkEffVsEtaZvtx->SetBinError(37,5,0.100332);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,5,0.696875);
trkEffVsEtaZvtx->SetBinError(38,5,0.088527);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,5,0.696875);
trkEffVsEtaZvtx->SetBinError(39,5,0.088527);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,5,0.836958);
trkEffVsEtaZvtx->SetBinError(40,5,0.064535);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,5,0.836958);
trkEffVsEtaZvtx->SetBinError(41,5,0.064535);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,5,0.699482);
trkEffVsEtaZvtx->SetBinError(42,5,0.105196);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,5,0.699482);
trkEffVsEtaZvtx->SetBinError(43,5,0.105196);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,5,0.301556);
trkEffVsEtaZvtx->SetBinError(48,5,0.137908);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,5,0.301556);
trkEffVsEtaZvtx->SetBinError(49,5,0.137908);

////////////////////////////////////////////////////
// ybin: over 100.000000
}
