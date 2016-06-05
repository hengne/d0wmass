{
const int n_trkEffVsEtaZvtx_xbins = 64;
float trkEffVsEtaZvtx_xbins[n_trkEffVsEtaZvtx_xbins+1] = {-3.200000 ,-3.100000 ,-3.000000 ,-2.900000 ,-2.800000 ,-2.700000 ,-2.600000 ,-2.500000 ,-2.400000 ,-2.300000 ,-2.200000 ,-2.100000 ,-2.000000 ,-1.900000 ,-1.800000 ,-1.700000 ,-1.600000 ,-1.500000 ,-1.400000 ,-1.300000 ,-1.200000 ,-1.100000 ,-1.000000 ,-0.900000 ,-0.800000 ,-0.700000 ,-0.600000 ,-0.500000 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.400000 ,0.500000 ,0.600000 ,0.700000 ,0.800000 ,0.900000 ,1.000000 ,1.100000 ,1.200000 ,1.300000 ,1.400000 ,1.500000 ,1.600000 ,1.700000 ,1.800000 ,1.900000 ,2.000000 ,2.100000 ,2.200000 ,2.300000 ,2.400000 ,2.500000 ,2.600000 ,2.700000 ,2.800000 ,2.900000 ,3.000000 ,3.100000 ,3.200000  };

const int n_trkEffVsEtaZvtx_ybins = 10;
float trkEffVsEtaZvtx_ybins[n_trkEffVsEtaZvtx_ybins+1] = {-100.000000 ,-39.000000 ,-30.000000 ,-23.000000 ,-10.000000 ,0.000000 ,10.000000 ,23.000000 ,30.000000 ,39.000000 ,100.000000  };

TH2F *trkEffVsEtaZvtx = new TH2F("trkEffVsEtaZvtx","track efficiency vs detector eta and zvtx", n_trkEffVsEtaZvtx_xbins, trkEffVsEtaZvtx_xbins, n_trkEffVsEtaZvtx_ybins, trkEffVsEtaZvtx_ybins);

////////////////////////////////////////////////////
// ybin: under -100.000000

////////////////////////////////////////////////////
// ybin: -100.000000 to -39.000000

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,1,0.066370);
trkEffVsEtaZvtx->SetBinError(16,1,0.108349);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,1,0.066370);
trkEffVsEtaZvtx->SetBinError(17,1,0.108349);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,1,0.712010);
trkEffVsEtaZvtx->SetBinError(22,1,0.099484);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,1,0.712010);
trkEffVsEtaZvtx->SetBinError(23,1,0.099484);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,1,0.653881);
trkEffVsEtaZvtx->SetBinError(24,1,0.089818);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,1,0.653881);
trkEffVsEtaZvtx->SetBinError(25,1,0.089818);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,1,0.642919);
trkEffVsEtaZvtx->SetBinError(26,1,0.080408);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,1,0.642919);
trkEffVsEtaZvtx->SetBinError(27,1,0.080408);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,1,0.551107);
trkEffVsEtaZvtx->SetBinError(28,1,0.095932);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,1,0.551107);
trkEffVsEtaZvtx->SetBinError(29,1,0.095932);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,1,0.686062);
trkEffVsEtaZvtx->SetBinError(30,1,0.089936);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,1,0.686062);
trkEffVsEtaZvtx->SetBinError(31,1,0.089936);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,1,0.732686);
trkEffVsEtaZvtx->SetBinError(32,1,0.085344);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,1,0.732686);
trkEffVsEtaZvtx->SetBinError(33,1,0.085344);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,1,0.582078);
trkEffVsEtaZvtx->SetBinError(34,1,0.093150);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,1,0.582078);
trkEffVsEtaZvtx->SetBinError(35,1,0.093150);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,1,0.709240);
trkEffVsEtaZvtx->SetBinError(36,1,0.094910);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,1,0.709240);
trkEffVsEtaZvtx->SetBinError(37,1,0.094910);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,1,0.761586);
trkEffVsEtaZvtx->SetBinError(38,1,0.081965);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,1,0.761586);
trkEffVsEtaZvtx->SetBinError(39,1,0.081965);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,1,0.884143);
trkEffVsEtaZvtx->SetBinError(40,1,0.083043);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,1,0.884143);
trkEffVsEtaZvtx->SetBinError(41,1,0.083043);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,1,0.790147);
trkEffVsEtaZvtx->SetBinError(42,1,0.107353);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,1,0.790147);
trkEffVsEtaZvtx->SetBinError(43,1,0.107353);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,1,0.854444);
trkEffVsEtaZvtx->SetBinError(48,1,0.062125);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,1,0.854444);
trkEffVsEtaZvtx->SetBinError(49,1,0.062125);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,1,0.794597);
trkEffVsEtaZvtx->SetBinError(50,1,0.093360);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,1,0.794597);
trkEffVsEtaZvtx->SetBinError(51,1,0.093360);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,1,0.700931);
trkEffVsEtaZvtx->SetBinError(52,1,0.109030);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,1,0.700931);
trkEffVsEtaZvtx->SetBinError(53,1,0.109030);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,1,0.700931);
trkEffVsEtaZvtx->SetBinError(54,1,0.109030);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,1,0.700931);
trkEffVsEtaZvtx->SetBinError(55,1,0.109030);

////////////////////////////////////////////////////
// ybin: -39.000000 to -30.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,2,0.040588);
trkEffVsEtaZvtx->SetBinError(10,2,0.100252);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,2,0.040588);
trkEffVsEtaZvtx->SetBinError(11,2,0.100252);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,2,0.040588);
trkEffVsEtaZvtx->SetBinError(12,2,0.100252);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,2,0.040588);
trkEffVsEtaZvtx->SetBinError(13,2,0.100252);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,2,0.127207);
trkEffVsEtaZvtx->SetBinError(14,2,0.122564);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,2,0.127207);
trkEffVsEtaZvtx->SetBinError(15,2,0.122564);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,2,0.397110);
trkEffVsEtaZvtx->SetBinError(16,2,0.137362);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,2,0.397110);
trkEffVsEtaZvtx->SetBinError(17,2,0.137362);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,2,0.738225);
trkEffVsEtaZvtx->SetBinError(22,2,0.093885);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,2,0.738225);
trkEffVsEtaZvtx->SetBinError(23,2,0.093885);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,2,0.750506);
trkEffVsEtaZvtx->SetBinError(24,2,0.083567);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,2,0.750506);
trkEffVsEtaZvtx->SetBinError(25,2,0.083567);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,2,0.693580);
trkEffVsEtaZvtx->SetBinError(26,2,0.081325);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,2,0.693580);
trkEffVsEtaZvtx->SetBinError(27,2,0.081325);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,2,0.685324);
trkEffVsEtaZvtx->SetBinError(28,2,0.078784);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,2,0.685324);
trkEffVsEtaZvtx->SetBinError(29,2,0.078784);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,2,0.766753);
trkEffVsEtaZvtx->SetBinError(30,2,0.077123);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,2,0.766753);
trkEffVsEtaZvtx->SetBinError(31,2,0.077123);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,2,0.764454);
trkEffVsEtaZvtx->SetBinError(32,2,0.079016);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,2,0.764454);
trkEffVsEtaZvtx->SetBinError(33,2,0.079016);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,2,0.788062);
trkEffVsEtaZvtx->SetBinError(34,2,0.066888);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,2,0.788062);
trkEffVsEtaZvtx->SetBinError(35,2,0.066888);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,2,0.909565);
trkEffVsEtaZvtx->SetBinError(36,2,0.058174);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,2,0.909565);
trkEffVsEtaZvtx->SetBinError(37,2,0.058174);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,2,0.811834);
trkEffVsEtaZvtx->SetBinError(38,2,0.080340);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,2,0.811834);
trkEffVsEtaZvtx->SetBinError(39,2,0.080340);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,2,0.759800);
trkEffVsEtaZvtx->SetBinError(40,2,0.081145);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,2,0.759800);
trkEffVsEtaZvtx->SetBinError(41,2,0.081145);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,2,0.689719);
trkEffVsEtaZvtx->SetBinError(42,2,0.109707);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,2,0.689719);
trkEffVsEtaZvtx->SetBinError(43,2,0.109707);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,2,0.967941);
trkEffVsEtaZvtx->SetBinError(48,2,0.040065);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,2,0.967941);
trkEffVsEtaZvtx->SetBinError(49,2,0.040065);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,2,0.768631);
trkEffVsEtaZvtx->SetBinError(50,2,0.090992);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,2,0.768631);
trkEffVsEtaZvtx->SetBinError(51,2,0.090992);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,2,0.653105);
trkEffVsEtaZvtx->SetBinError(52,2,0.130697);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,2,0.653105);
trkEffVsEtaZvtx->SetBinError(53,2,0.130697);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,2,0.653105);
trkEffVsEtaZvtx->SetBinError(54,2,0.130697);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,2,0.653105);
trkEffVsEtaZvtx->SetBinError(55,2,0.130697);

////////////////////////////////////////////////////
// ybin: -30.000000 to -23.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,3,0.272855);
trkEffVsEtaZvtx->SetBinError(10,3,0.169648);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,3,0.272855);
trkEffVsEtaZvtx->SetBinError(11,3,0.169648);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,3,0.272855);
trkEffVsEtaZvtx->SetBinError(12,3,0.169648);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,3,0.272855);
trkEffVsEtaZvtx->SetBinError(13,3,0.169648);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,3,0.350341);
trkEffVsEtaZvtx->SetBinError(14,3,0.133903);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,3,0.350341);
trkEffVsEtaZvtx->SetBinError(15,3,0.133903);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,3,0.745913);
trkEffVsEtaZvtx->SetBinError(16,3,0.107961);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,3,0.745913);
trkEffVsEtaZvtx->SetBinError(17,3,0.107961);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,3,0.733579);
trkEffVsEtaZvtx->SetBinError(22,3,0.091300);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,3,0.733579);
trkEffVsEtaZvtx->SetBinError(23,3,0.091300);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,3,0.688325);
trkEffVsEtaZvtx->SetBinError(24,3,0.078776);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,3,0.688325);
trkEffVsEtaZvtx->SetBinError(25,3,0.078776);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,3,0.752850);
trkEffVsEtaZvtx->SetBinError(26,3,0.069369);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,3,0.752850);
trkEffVsEtaZvtx->SetBinError(27,3,0.069369);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,3,0.777834);
trkEffVsEtaZvtx->SetBinError(28,3,0.069327);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,3,0.777834);
trkEffVsEtaZvtx->SetBinError(29,3,0.069327);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,3,0.775190);
trkEffVsEtaZvtx->SetBinError(30,3,0.067113);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,3,0.775190);
trkEffVsEtaZvtx->SetBinError(31,3,0.067113);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,3,0.728421);
trkEffVsEtaZvtx->SetBinError(32,3,0.070867);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,3,0.728421);
trkEffVsEtaZvtx->SetBinError(33,3,0.070867);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,3,0.724234);
trkEffVsEtaZvtx->SetBinError(34,3,0.073582);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,3,0.724234);
trkEffVsEtaZvtx->SetBinError(35,3,0.073582);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,3,0.801864);
trkEffVsEtaZvtx->SetBinError(36,3,0.071652);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,3,0.801864);
trkEffVsEtaZvtx->SetBinError(37,3,0.071652);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,3,0.789149);
trkEffVsEtaZvtx->SetBinError(38,3,0.083307);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,3,0.789149);
trkEffVsEtaZvtx->SetBinError(39,3,0.083307);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,3,0.781977);
trkEffVsEtaZvtx->SetBinError(40,3,0.073095);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,3,0.781977);
trkEffVsEtaZvtx->SetBinError(41,3,0.073095);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,3,0.862657);
trkEffVsEtaZvtx->SetBinError(42,3,0.073366);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,3,0.862657);
trkEffVsEtaZvtx->SetBinError(43,3,0.073366);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,3,0.888880);
trkEffVsEtaZvtx->SetBinError(48,3,0.064116);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,3,0.888880);
trkEffVsEtaZvtx->SetBinError(49,3,0.064116);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,3,0.910739);
trkEffVsEtaZvtx->SetBinError(50,3,0.079164);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,3,0.910739);
trkEffVsEtaZvtx->SetBinError(51,3,0.079164);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,3,0.758274);
trkEffVsEtaZvtx->SetBinError(52,3,0.102274);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,3,0.758274);
trkEffVsEtaZvtx->SetBinError(53,3,0.102274);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,3,0.758274);
trkEffVsEtaZvtx->SetBinError(54,3,0.102274);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,3,0.758274);
trkEffVsEtaZvtx->SetBinError(55,3,0.102274);

////////////////////////////////////////////////////
// ybin: -23.000000 to -10.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,4,0.433954);
trkEffVsEtaZvtx->SetBinError(10,4,0.121253);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,4,0.579557);
trkEffVsEtaZvtx->SetBinError(11,4,0.120791);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,4,0.354482);
trkEffVsEtaZvtx->SetBinError(12,4,0.101108);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,4,0.321323);
trkEffVsEtaZvtx->SetBinError(13,4,0.095036);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,4,0.505791);
trkEffVsEtaZvtx->SetBinError(14,4,0.100502);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,4,0.737528);
trkEffVsEtaZvtx->SetBinError(15,4,0.090711);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,4,0.574971);
trkEffVsEtaZvtx->SetBinError(16,4,0.089491);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,4,0.890475);
trkEffVsEtaZvtx->SetBinError(17,4,0.048635);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,4,0.709017);
trkEffVsEtaZvtx->SetBinError(22,4,0.077241);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,4,0.681319);
trkEffVsEtaZvtx->SetBinError(23,4,0.050238);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,4,0.784051);
trkEffVsEtaZvtx->SetBinError(24,4,0.046329);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,4,0.792868);
trkEffVsEtaZvtx->SetBinError(25,4,0.041747);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,4,0.826716);
trkEffVsEtaZvtx->SetBinError(26,4,0.042659);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,4,0.802384);
trkEffVsEtaZvtx->SetBinError(27,4,0.041298);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,4,0.813721);
trkEffVsEtaZvtx->SetBinError(28,4,0.039946);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,4,0.820120);
trkEffVsEtaZvtx->SetBinError(29,4,0.039587);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,4,0.798972);
trkEffVsEtaZvtx->SetBinError(30,4,0.043550);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,4,0.802780);
trkEffVsEtaZvtx->SetBinError(31,4,0.037458);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,4,0.816930);
trkEffVsEtaZvtx->SetBinError(32,4,0.038527);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,4,0.772280);
trkEffVsEtaZvtx->SetBinError(33,4,0.042855);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,4,0.773849);
trkEffVsEtaZvtx->SetBinError(34,4,0.044635);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,4,0.787518);
trkEffVsEtaZvtx->SetBinError(35,4,0.046554);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,4,0.807465);
trkEffVsEtaZvtx->SetBinError(36,4,0.044479);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,4,0.768680);
trkEffVsEtaZvtx->SetBinError(37,4,0.043278);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,4,0.698980);
trkEffVsEtaZvtx->SetBinError(38,4,0.045030);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,4,0.741121);
trkEffVsEtaZvtx->SetBinError(39,4,0.049826);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,4,0.670113);
trkEffVsEtaZvtx->SetBinError(40,4,0.056985);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,4,0.779620);
trkEffVsEtaZvtx->SetBinError(41,4,0.044097);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,4,0.772376);
trkEffVsEtaZvtx->SetBinError(42,4,0.047592);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,4,0.710083);
trkEffVsEtaZvtx->SetBinError(43,4,0.071580);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,4,0.923712);
trkEffVsEtaZvtx->SetBinError(48,4,0.029637);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,4,0.899037);
trkEffVsEtaZvtx->SetBinError(49,4,0.037856);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,4,0.807420);
trkEffVsEtaZvtx->SetBinError(50,4,0.046762);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,4,0.885750);
trkEffVsEtaZvtx->SetBinError(51,4,0.045744);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,4,0.807648);
trkEffVsEtaZvtx->SetBinError(52,4,0.055000);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,4,0.725730);
trkEffVsEtaZvtx->SetBinError(53,4,0.076954);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,4,0.803431);
trkEffVsEtaZvtx->SetBinError(54,4,0.067797);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,4,0.775862);
trkEffVsEtaZvtx->SetBinError(55,4,0.069405);

////////////////////////////////////////////////////
// ybin: -10.000000 to 0.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,5,0.550541);
trkEffVsEtaZvtx->SetBinError(10,5,0.133813);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,5,0.335145);
trkEffVsEtaZvtx->SetBinError(11,5,0.113219);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,5,0.439310);
trkEffVsEtaZvtx->SetBinError(12,5,0.114389);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,5,0.545911);
trkEffVsEtaZvtx->SetBinError(13,5,0.096281);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,5,0.794474);
trkEffVsEtaZvtx->SetBinError(14,5,0.080948);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,5,0.793290);
trkEffVsEtaZvtx->SetBinError(15,5,0.069658);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,5,0.893950);
trkEffVsEtaZvtx->SetBinError(16,5,0.047531);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,5,0.935073);
trkEffVsEtaZvtx->SetBinError(17,5,0.055264);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,5,0.674973);
trkEffVsEtaZvtx->SetBinError(22,5,0.094295);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,5,0.711095);
trkEffVsEtaZvtx->SetBinError(23,5,0.052771);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,5,0.773887);
trkEffVsEtaZvtx->SetBinError(24,5,0.045993);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,5,0.787430);
trkEffVsEtaZvtx->SetBinError(25,5,0.047743);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,5,0.781720);
trkEffVsEtaZvtx->SetBinError(26,5,0.048407);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,5,0.822774);
trkEffVsEtaZvtx->SetBinError(27,5,0.041666);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,5,0.798370);
trkEffVsEtaZvtx->SetBinError(28,5,0.042657);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,5,0.809440);
trkEffVsEtaZvtx->SetBinError(29,5,0.041802);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,5,0.833784);
trkEffVsEtaZvtx->SetBinError(30,5,0.040091);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,5,0.821235);
trkEffVsEtaZvtx->SetBinError(31,5,0.040035);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,5,0.807610);
trkEffVsEtaZvtx->SetBinError(32,5,0.039986);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,5,0.835964);
trkEffVsEtaZvtx->SetBinError(33,5,0.040821);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,5,0.774219);
trkEffVsEtaZvtx->SetBinError(34,5,0.039007);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,5,0.886347);
trkEffVsEtaZvtx->SetBinError(35,5,0.034338);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,5,0.904364);
trkEffVsEtaZvtx->SetBinError(36,5,0.032641);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,5,0.901149);
trkEffVsEtaZvtx->SetBinError(37,5,0.034951);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,5,0.883182);
trkEffVsEtaZvtx->SetBinError(38,5,0.036620);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,5,0.884479);
trkEffVsEtaZvtx->SetBinError(39,5,0.035464);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,5,0.908198);
trkEffVsEtaZvtx->SetBinError(40,5,0.032647);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,5,0.743854);
trkEffVsEtaZvtx->SetBinError(41,5,0.049746);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,5,0.810184);
trkEffVsEtaZvtx->SetBinError(42,5,0.048747);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,5,0.857713);
trkEffVsEtaZvtx->SetBinError(43,5,0.063057);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,5,0.905374);
trkEffVsEtaZvtx->SetBinError(48,5,0.035552);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,5,0.946972);
trkEffVsEtaZvtx->SetBinError(49,5,0.034443);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,5,0.879687);
trkEffVsEtaZvtx->SetBinError(50,5,0.048727);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,5,0.846537);
trkEffVsEtaZvtx->SetBinError(51,5,0.050828);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,5,0.878835);
trkEffVsEtaZvtx->SetBinError(52,5,0.048195);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,5,0.716896);
trkEffVsEtaZvtx->SetBinError(53,5,0.065906);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,5,0.709184);
trkEffVsEtaZvtx->SetBinError(54,5,0.072878);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,5,0.677092);
trkEffVsEtaZvtx->SetBinError(55,5,0.069525);

////////////////////////////////////////////////////
// ybin: 0.000000 to 10.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,6,0.656917);
trkEffVsEtaZvtx->SetBinError(10,6,0.094191);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,6,0.623740);
trkEffVsEtaZvtx->SetBinError(11,6,0.086180);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,6,0.702283);
trkEffVsEtaZvtx->SetBinError(12,6,0.077340);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,6,0.796339);
trkEffVsEtaZvtx->SetBinError(13,6,0.080774);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,6,0.859515);
trkEffVsEtaZvtx->SetBinError(14,6,0.054285);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,6,0.883775);
trkEffVsEtaZvtx->SetBinError(15,6,0.051589);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,6,0.860999);
trkEffVsEtaZvtx->SetBinError(16,6,0.047334);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,6,0.884534);
trkEffVsEtaZvtx->SetBinError(17,6,0.045855);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,6,0.903709);
trkEffVsEtaZvtx->SetBinError(22,6,0.052924);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,6,0.799402);
trkEffVsEtaZvtx->SetBinError(23,6,0.051866);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,6,0.874659);
trkEffVsEtaZvtx->SetBinError(24,6,0.040871);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,6,0.820928);
trkEffVsEtaZvtx->SetBinError(25,6,0.044041);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,6,0.843974);
trkEffVsEtaZvtx->SetBinError(26,6,0.040553);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,6,0.879002);
trkEffVsEtaZvtx->SetBinError(27,6,0.036768);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,6,0.865820);
trkEffVsEtaZvtx->SetBinError(28,6,0.035506);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,6,0.826611);
trkEffVsEtaZvtx->SetBinError(29,6,0.039725);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,6,0.751007);
trkEffVsEtaZvtx->SetBinError(30,6,0.047913);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,6,0.824033);
trkEffVsEtaZvtx->SetBinError(31,6,0.040140);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,6,0.720562);
trkEffVsEtaZvtx->SetBinError(32,6,0.045387);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,6,0.857811);
trkEffVsEtaZvtx->SetBinError(33,6,0.036832);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,6,0.844309);
trkEffVsEtaZvtx->SetBinError(34,6,0.037578);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,6,0.805146);
trkEffVsEtaZvtx->SetBinError(35,6,0.040633);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,6,0.779098);
trkEffVsEtaZvtx->SetBinError(36,6,0.041486);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,6,0.758858);
trkEffVsEtaZvtx->SetBinError(37,6,0.045821);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,6,0.805548);
trkEffVsEtaZvtx->SetBinError(38,6,0.039830);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,6,0.839265);
trkEffVsEtaZvtx->SetBinError(39,6,0.036999);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,6,0.749790);
trkEffVsEtaZvtx->SetBinError(40,6,0.048727);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,6,0.709870);
trkEffVsEtaZvtx->SetBinError(41,6,0.048754);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,6,0.739110);
trkEffVsEtaZvtx->SetBinError(42,6,0.045684);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,6,0.844876);
trkEffVsEtaZvtx->SetBinError(43,6,0.058220);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,6,0.927717);
trkEffVsEtaZvtx->SetBinError(48,6,0.038389);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,6,0.947332);
trkEffVsEtaZvtx->SetBinError(49,6,0.044188);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,6,0.787042);
trkEffVsEtaZvtx->SetBinError(50,6,0.063383);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,6,0.770533);
trkEffVsEtaZvtx->SetBinError(51,6,0.082359);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,6,0.567798);
trkEffVsEtaZvtx->SetBinError(52,6,0.076842);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,6,0.690204);
trkEffVsEtaZvtx->SetBinError(53,6,0.075910);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,6,0.708015);
trkEffVsEtaZvtx->SetBinError(54,6,0.097146);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,6,0.436395);
trkEffVsEtaZvtx->SetBinError(55,6,0.097549);

////////////////////////////////////////////////////
// ybin: 10.000000 to 23.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,7,0.668667);
trkEffVsEtaZvtx->SetBinError(10,7,0.104176);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,7,0.769122);
trkEffVsEtaZvtx->SetBinError(11,7,0.089280);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,7,0.745395);
trkEffVsEtaZvtx->SetBinError(12,7,0.081438);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,7,0.598849);
trkEffVsEtaZvtx->SetBinError(13,7,0.099069);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,7,0.763084);
trkEffVsEtaZvtx->SetBinError(14,7,0.068826);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,7,0.694180);
trkEffVsEtaZvtx->SetBinError(15,7,0.069401);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,7,0.890536);
trkEffVsEtaZvtx->SetBinError(16,7,0.040653);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,7,0.969303);
trkEffVsEtaZvtx->SetBinError(17,7,0.027953);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,7,0.795243);
trkEffVsEtaZvtx->SetBinError(22,7,0.066000);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,7,0.804700);
trkEffVsEtaZvtx->SetBinError(23,7,0.044265);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,7,0.739404);
trkEffVsEtaZvtx->SetBinError(24,7,0.048995);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,7,0.868018);
trkEffVsEtaZvtx->SetBinError(25,7,0.042229);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,7,0.891317);
trkEffVsEtaZvtx->SetBinError(26,7,0.035270);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,7,0.861838);
trkEffVsEtaZvtx->SetBinError(27,7,0.038047);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,7,0.752724);
trkEffVsEtaZvtx->SetBinError(28,7,0.045655);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,7,0.743500);
trkEffVsEtaZvtx->SetBinError(29,7,0.047322);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,7,0.831259);
trkEffVsEtaZvtx->SetBinError(30,7,0.043738);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,7,0.766647);
trkEffVsEtaZvtx->SetBinError(31,7,0.043634);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,7,0.838034);
trkEffVsEtaZvtx->SetBinError(32,7,0.037539);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,7,0.778847);
trkEffVsEtaZvtx->SetBinError(33,7,0.042609);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,7,0.816026);
trkEffVsEtaZvtx->SetBinError(34,7,0.039557);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,7,0.786645);
trkEffVsEtaZvtx->SetBinError(35,7,0.044775);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,7,0.767439);
trkEffVsEtaZvtx->SetBinError(36,7,0.046966);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,7,0.771821);
trkEffVsEtaZvtx->SetBinError(37,7,0.044053);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,7,0.710240);
trkEffVsEtaZvtx->SetBinError(38,7,0.047618);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,7,0.773452);
trkEffVsEtaZvtx->SetBinError(39,7,0.043703);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,7,0.741993);
trkEffVsEtaZvtx->SetBinError(40,7,0.044020);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,7,0.818964);
trkEffVsEtaZvtx->SetBinError(41,7,0.041567);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,7,0.742783);
trkEffVsEtaZvtx->SetBinError(42,7,0.047348);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,7,0.676281);
trkEffVsEtaZvtx->SetBinError(43,7,0.071941);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,7,0.896060);
trkEffVsEtaZvtx->SetBinError(48,7,0.042543);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,7,0.809215);
trkEffVsEtaZvtx->SetBinError(49,7,0.066228);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,7,0.643827);
trkEffVsEtaZvtx->SetBinError(50,7,0.074420);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,7,0.515835);
trkEffVsEtaZvtx->SetBinError(51,7,0.077404);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,7,0.619891);
trkEffVsEtaZvtx->SetBinError(52,7,0.084110);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,7,0.639376);
trkEffVsEtaZvtx->SetBinError(53,7,0.084424);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,7,0.589054);
trkEffVsEtaZvtx->SetBinError(54,7,0.095522);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,7,0.411802);
trkEffVsEtaZvtx->SetBinError(55,7,0.098973);

////////////////////////////////////////////////////
// ybin: 23.000000 to 30.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,8,0.672078);
trkEffVsEtaZvtx->SetBinError(10,8,0.141336);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,8,0.672078);
trkEffVsEtaZvtx->SetBinError(11,8,0.141336);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,8,0.672078);
trkEffVsEtaZvtx->SetBinError(12,8,0.141336);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,8,0.672078);
trkEffVsEtaZvtx->SetBinError(13,8,0.141336);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,8,0.929054);
trkEffVsEtaZvtx->SetBinError(14,8,0.081770);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,8,0.929054);
trkEffVsEtaZvtx->SetBinError(15,8,0.081770);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,8,0.977732);
trkEffVsEtaZvtx->SetBinError(16,8,0.047412);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,8,0.977732);
trkEffVsEtaZvtx->SetBinError(17,8,0.047412);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,8,0.789414);
trkEffVsEtaZvtx->SetBinError(22,8,0.104902);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,8,0.789414);
trkEffVsEtaZvtx->SetBinError(23,8,0.104902);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,8,0.794696);
trkEffVsEtaZvtx->SetBinError(24,8,0.081799);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,8,0.794696);
trkEffVsEtaZvtx->SetBinError(25,8,0.081799);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,8,0.728554);
trkEffVsEtaZvtx->SetBinError(26,8,0.083421);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,8,0.728554);
trkEffVsEtaZvtx->SetBinError(27,8,0.083421);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,8,0.783929);
trkEffVsEtaZvtx->SetBinError(28,8,0.068941);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,8,0.783929);
trkEffVsEtaZvtx->SetBinError(29,8,0.068941);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,8,0.746808);
trkEffVsEtaZvtx->SetBinError(30,8,0.070223);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,8,0.746808);
trkEffVsEtaZvtx->SetBinError(31,8,0.070223);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,8,0.650433);
trkEffVsEtaZvtx->SetBinError(32,8,0.074249);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,8,0.650433);
trkEffVsEtaZvtx->SetBinError(33,8,0.074249);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,8,0.711884);
trkEffVsEtaZvtx->SetBinError(34,8,0.081934);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,8,0.711884);
trkEffVsEtaZvtx->SetBinError(35,8,0.081934);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,8,0.748798);
trkEffVsEtaZvtx->SetBinError(36,8,0.075607);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,8,0.748798);
trkEffVsEtaZvtx->SetBinError(37,8,0.075607);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,8,0.822481);
trkEffVsEtaZvtx->SetBinError(38,8,0.067192);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,8,0.822481);
trkEffVsEtaZvtx->SetBinError(39,8,0.067192);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,8,0.754939);
trkEffVsEtaZvtx->SetBinError(40,8,0.070488);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,8,0.754939);
trkEffVsEtaZvtx->SetBinError(41,8,0.070488);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,8,0.830688);
trkEffVsEtaZvtx->SetBinError(42,8,0.073675);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,8,0.830688);
trkEffVsEtaZvtx->SetBinError(43,8,0.073675);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,8,0.851231);
trkEffVsEtaZvtx->SetBinError(48,8,0.091876);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,8,0.851231);
trkEffVsEtaZvtx->SetBinError(49,8,0.091876);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,8,0.326498);
trkEffVsEtaZvtx->SetBinError(50,8,0.115286);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,8,0.326498);
trkEffVsEtaZvtx->SetBinError(51,8,0.115286);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,8,0.293791);
trkEffVsEtaZvtx->SetBinError(52,8,0.158983);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,8,0.293791);
trkEffVsEtaZvtx->SetBinError(53,8,0.158983);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,8,0.293791);
trkEffVsEtaZvtx->SetBinError(54,8,0.158983);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,8,0.293791);
trkEffVsEtaZvtx->SetBinError(55,8,0.158983);

////////////////////////////////////////////////////
// ybin: 30.000000 to 39.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,9,0.601489);
trkEffVsEtaZvtx->SetBinError(10,9,0.159389);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,9,0.601489);
trkEffVsEtaZvtx->SetBinError(11,9,0.159389);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,9,0.601489);
trkEffVsEtaZvtx->SetBinError(12,9,0.159389);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,9,0.601489);
trkEffVsEtaZvtx->SetBinError(13,9,0.159389);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,9,0.872698);
trkEffVsEtaZvtx->SetBinError(14,9,0.088473);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,9,0.872698);
trkEffVsEtaZvtx->SetBinError(15,9,0.088473);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,9,0.864012);
trkEffVsEtaZvtx->SetBinError(16,9,0.083691);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,9,0.864012);
trkEffVsEtaZvtx->SetBinError(17,9,0.083691);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,9,0.579010);
trkEffVsEtaZvtx->SetBinError(22,9,0.114222);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,9,0.579010);
trkEffVsEtaZvtx->SetBinError(23,9,0.114222);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,9,0.605188);
trkEffVsEtaZvtx->SetBinError(24,9,0.092694);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,9,0.605188);
trkEffVsEtaZvtx->SetBinError(25,9,0.092694);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,9,0.856249);
trkEffVsEtaZvtx->SetBinError(26,9,0.073266);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,9,0.856249);
trkEffVsEtaZvtx->SetBinError(27,9,0.073266);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,9,0.647528);
trkEffVsEtaZvtx->SetBinError(28,9,0.095108);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,9,0.647528);
trkEffVsEtaZvtx->SetBinError(29,9,0.095108);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,9,0.800903);
trkEffVsEtaZvtx->SetBinError(30,9,0.073234);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,9,0.800903);
trkEffVsEtaZvtx->SetBinError(31,9,0.073234);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,9,0.773529);
trkEffVsEtaZvtx->SetBinError(32,9,0.071502);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,9,0.773529);
trkEffVsEtaZvtx->SetBinError(33,9,0.071502);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,9,0.656639);
trkEffVsEtaZvtx->SetBinError(34,9,0.088664);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,9,0.656639);
trkEffVsEtaZvtx->SetBinError(35,9,0.088664);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,9,0.697655);
trkEffVsEtaZvtx->SetBinError(36,9,0.073432);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,9,0.697655);
trkEffVsEtaZvtx->SetBinError(37,9,0.073432);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,9,0.653435);
trkEffVsEtaZvtx->SetBinError(38,9,0.081396);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,9,0.653435);
trkEffVsEtaZvtx->SetBinError(39,9,0.081396);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,9,0.762463);
trkEffVsEtaZvtx->SetBinError(40,9,0.070134);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,9,0.762463);
trkEffVsEtaZvtx->SetBinError(41,9,0.070134);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,9,0.661799);
trkEffVsEtaZvtx->SetBinError(42,9,0.092455);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,9,0.661799);
trkEffVsEtaZvtx->SetBinError(43,9,0.092455);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,9,0.445517);
trkEffVsEtaZvtx->SetBinError(48,9,0.134035);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,9,0.445517);
trkEffVsEtaZvtx->SetBinError(49,9,0.134035);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,9,0.276592);
trkEffVsEtaZvtx->SetBinError(50,9,0.129846);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,9,0.276592);
trkEffVsEtaZvtx->SetBinError(51,9,0.129846);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,9,0.040410);
trkEffVsEtaZvtx->SetBinError(52,9,0.099870);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,9,0.040410);
trkEffVsEtaZvtx->SetBinError(53,9,0.099870);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,9,0.040410);
trkEffVsEtaZvtx->SetBinError(54,9,0.099870);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,9,0.040410);
trkEffVsEtaZvtx->SetBinError(55,9,0.099870);

////////////////////////////////////////////////////
// ybin: 39.000000 to 100.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,10,0.686490);
trkEffVsEtaZvtx->SetBinError(10,10,0.132705);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,10,0.686490);
trkEffVsEtaZvtx->SetBinError(11,10,0.132705);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,10,0.686490);
trkEffVsEtaZvtx->SetBinError(12,10,0.132705);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,10,0.686490);
trkEffVsEtaZvtx->SetBinError(13,10,0.132705);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,10,0.818969);
trkEffVsEtaZvtx->SetBinError(14,10,0.084221);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,10,0.818969);
trkEffVsEtaZvtx->SetBinError(15,10,0.084221);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,10,0.935928);
trkEffVsEtaZvtx->SetBinError(16,10,0.058870);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,10,0.935928);
trkEffVsEtaZvtx->SetBinError(17,10,0.058870);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,10,0.735867);
trkEffVsEtaZvtx->SetBinError(22,10,0.108387);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,10,0.735867);
trkEffVsEtaZvtx->SetBinError(23,10,0.108387);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,10,0.819596);
trkEffVsEtaZvtx->SetBinError(24,10,0.078561);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,10,0.819596);
trkEffVsEtaZvtx->SetBinError(25,10,0.078561);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,10,0.609126);
trkEffVsEtaZvtx->SetBinError(26,10,0.108403);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,10,0.609126);
trkEffVsEtaZvtx->SetBinError(27,10,0.108403);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,10,0.603770);
trkEffVsEtaZvtx->SetBinError(28,10,0.084293);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,10,0.603770);
trkEffVsEtaZvtx->SetBinError(29,10,0.084293);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,10,0.689525);
trkEffVsEtaZvtx->SetBinError(30,10,0.096641);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,10,0.689525);
trkEffVsEtaZvtx->SetBinError(31,10,0.096641);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,10,0.796957);
trkEffVsEtaZvtx->SetBinError(32,10,0.078685);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,10,0.796957);
trkEffVsEtaZvtx->SetBinError(33,10,0.078685);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,10,0.675556);
trkEffVsEtaZvtx->SetBinError(34,10,0.084322);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,10,0.675556);
trkEffVsEtaZvtx->SetBinError(35,10,0.084322);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,10,0.566939);
trkEffVsEtaZvtx->SetBinError(36,10,0.093928);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,10,0.566939);
trkEffVsEtaZvtx->SetBinError(37,10,0.093928);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,10,0.697301);
trkEffVsEtaZvtx->SetBinError(38,10,0.073467);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,10,0.697301);
trkEffVsEtaZvtx->SetBinError(39,10,0.073467);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,10,0.729181);
trkEffVsEtaZvtx->SetBinError(40,10,0.069630);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,10,0.729181);
trkEffVsEtaZvtx->SetBinError(41,10,0.069630);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,10,0.645616);
trkEffVsEtaZvtx->SetBinError(42,10,0.109374);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,10,0.645616);
trkEffVsEtaZvtx->SetBinError(43,10,0.109374);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,10,0.218526);
trkEffVsEtaZvtx->SetBinError(48,10,0.109254);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,10,0.218526);
trkEffVsEtaZvtx->SetBinError(49,10,0.109254);

////////////////////////////////////////////////////
// ybin: over 100.000000
}
