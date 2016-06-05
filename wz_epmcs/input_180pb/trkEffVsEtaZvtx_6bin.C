{
const int n_trkEffVsEtaZvtx_xbins = 64;
float trkEffVsEtaZvtx_xbins[n_trkEffVsEtaZvtx_xbins+1] = {-3.200000 ,-3.100000 ,-3.000000 ,-2.900000 ,-2.800000 ,-2.700000 ,-2.600000 ,-2.500000 ,-2.400000 ,-2.300000 ,-2.200000 ,-2.100000 ,-2.000000 ,-1.900000 ,-1.800000 ,-1.700000 ,-1.600000 ,-1.500000 ,-1.400000 ,-1.300000 ,-1.200000 ,-1.100000 ,-1.000000 ,-0.900000 ,-0.800000 ,-0.700000 ,-0.600000 ,-0.500000 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.400000 ,0.500000 ,0.600000 ,0.700000 ,0.800000 ,0.900000 ,1.000000 ,1.100000 ,1.200000 ,1.300000 ,1.400000 ,1.500000 ,1.600000 ,1.700000 ,1.800000 ,1.900000 ,2.000000 ,2.100000 ,2.200000 ,2.300000 ,2.400000 ,2.500000 ,2.600000 ,2.700000 ,2.800000 ,2.900000 ,3.000000 ,3.100000 ,3.200000  };

const int n_trkEffVsEtaZvtx_ybins = 6;
float trkEffVsEtaZvtx_ybins[n_trkEffVsEtaZvtx_ybins+1] = {-100.000000 ,-30.000000 ,-10.000000 ,0.000000 ,10.000000 ,30.000000 ,100.000000  };

TH2F *trkEffVsEtaZvtx = new TH2F("trkEffVsEtaZvtx","track efficiency vs detector eta and zvtx", n_trkEffVsEtaZvtx_xbins, trkEffVsEtaZvtx_xbins, n_trkEffVsEtaZvtx_ybins, trkEffVsEtaZvtx_ybins);

////////////////////////////////////////////////////
// ybin: under -100.000000

////////////////////////////////////////////////////
// ybin: -100.000000 to -30.000000

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,1,0.117741);
trkEffVsEtaZvtx->SetBinError(15,1,0.081588);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,1,0.142935);
trkEffVsEtaZvtx->SetBinError(16,1,0.077404);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,1,0.444780);
trkEffVsEtaZvtx->SetBinError(17,1,0.108604);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,1,0.772799);
trkEffVsEtaZvtx->SetBinError(22,1,0.086599);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,1,0.685231);
trkEffVsEtaZvtx->SetBinError(23,1,0.061859);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,1,0.767508);
trkEffVsEtaZvtx->SetBinError(24,1,0.063361);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,1,0.704601);
trkEffVsEtaZvtx->SetBinError(25,1,0.067116);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,1,0.771973);
trkEffVsEtaZvtx->SetBinError(26,1,0.054920);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,1,0.693367);
trkEffVsEtaZvtx->SetBinError(27,1,0.052445);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,1,0.681848);
trkEffVsEtaZvtx->SetBinError(28,1,0.056319);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,1,0.679290);
trkEffVsEtaZvtx->SetBinError(29,1,0.062702);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,1,0.733395);
trkEffVsEtaZvtx->SetBinError(30,1,0.064563);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,1,0.734744);
trkEffVsEtaZvtx->SetBinError(31,1,0.061885);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,1,0.788773);
trkEffVsEtaZvtx->SetBinError(32,1,0.048089);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,1,0.878145);
trkEffVsEtaZvtx->SetBinError(33,1,0.052226);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,1,0.802865);
trkEffVsEtaZvtx->SetBinError(34,1,0.046968);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,1,0.603487);
trkEffVsEtaZvtx->SetBinError(35,1,0.062726);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,1,0.860060);
trkEffVsEtaZvtx->SetBinError(36,1,0.049554);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,1,0.816378);
trkEffVsEtaZvtx->SetBinError(37,1,0.055054);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,1,0.803629);
trkEffVsEtaZvtx->SetBinError(38,1,0.052734);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,1,0.761970);
trkEffVsEtaZvtx->SetBinError(39,1,0.064547);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,1,0.808578);
trkEffVsEtaZvtx->SetBinError(40,1,0.056993);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,1,0.807756);
trkEffVsEtaZvtx->SetBinError(41,1,0.054303);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,1,0.684287);
trkEffVsEtaZvtx->SetBinError(42,1,0.073148);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,1,0.769278);
trkEffVsEtaZvtx->SetBinError(43,1,0.080406);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,1,0.874410);
trkEffVsEtaZvtx->SetBinError(48,1,0.045925);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,1,0.884404);
trkEffVsEtaZvtx->SetBinError(49,1,0.040204);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,1,0.844950);
trkEffVsEtaZvtx->SetBinError(50,1,0.060024);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,1,0.773831);
trkEffVsEtaZvtx->SetBinError(51,1,0.059669);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,1,0.716200);
trkEffVsEtaZvtx->SetBinError(52,1,0.082267);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,1,0.708511);
trkEffVsEtaZvtx->SetBinError(53,1,0.075688);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,1,0.631036);
trkEffVsEtaZvtx->SetBinError(54,1,0.088618);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,1,0.593103);
trkEffVsEtaZvtx->SetBinError(55,1,0.098694);

////////////////////////////////////////////////////
// ybin: -30.000000 to -10.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,2,0.369970);
trkEffVsEtaZvtx->SetBinError(10,2,0.103798);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,2,0.525527);
trkEffVsEtaZvtx->SetBinError(11,2,0.102097);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,2,0.393844);
trkEffVsEtaZvtx->SetBinError(12,2,0.088122);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,2,0.349136);
trkEffVsEtaZvtx->SetBinError(13,2,0.094363);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,2,0.379917);
trkEffVsEtaZvtx->SetBinError(14,2,0.077123);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,2,0.616630);
trkEffVsEtaZvtx->SetBinError(15,2,0.083898);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,2,0.639005);
trkEffVsEtaZvtx->SetBinError(16,2,0.072942);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,2,0.841870);
trkEffVsEtaZvtx->SetBinError(17,2,0.044852);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,2,0.680361);
trkEffVsEtaZvtx->SetBinError(22,2,0.064433);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,2,0.711797);
trkEffVsEtaZvtx->SetBinError(23,2,0.039728);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,2,0.744194);
trkEffVsEtaZvtx->SetBinError(24,2,0.041487);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,2,0.766767);
trkEffVsEtaZvtx->SetBinError(25,2,0.035454);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,2,0.807651);
trkEffVsEtaZvtx->SetBinError(26,2,0.036060);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,2,0.766446);
trkEffVsEtaZvtx->SetBinError(27,2,0.036658);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,2,0.798717);
trkEffVsEtaZvtx->SetBinError(28,2,0.034066);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,2,0.777376);
trkEffVsEtaZvtx->SetBinError(29,2,0.034664);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,2,0.799925);
trkEffVsEtaZvtx->SetBinError(30,2,0.035846);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,2,0.797481);
trkEffVsEtaZvtx->SetBinError(31,2,0.032536);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,2,0.809941);
trkEffVsEtaZvtx->SetBinError(32,2,0.033007);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,2,0.768870);
trkEffVsEtaZvtx->SetBinError(33,2,0.038315);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,2,0.774663);
trkEffVsEtaZvtx->SetBinError(34,2,0.035062);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,2,0.764096);
trkEffVsEtaZvtx->SetBinError(35,2,0.038253);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,2,0.837562);
trkEffVsEtaZvtx->SetBinError(36,2,0.032668);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,2,0.782612);
trkEffVsEtaZvtx->SetBinError(37,2,0.036326);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,2,0.751303);
trkEffVsEtaZvtx->SetBinError(38,2,0.036349);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,2,0.736408);
trkEffVsEtaZvtx->SetBinError(39,2,0.040449);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,2,0.693680);
trkEffVsEtaZvtx->SetBinError(40,2,0.044753);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,2,0.809940);
trkEffVsEtaZvtx->SetBinError(41,2,0.036527);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,2,0.746895);
trkEffVsEtaZvtx->SetBinError(42,2,0.041936);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,2,0.735930);
trkEffVsEtaZvtx->SetBinError(43,2,0.052760);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,2,0.937046);
trkEffVsEtaZvtx->SetBinError(48,2,0.023410);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,2,0.881163);
trkEffVsEtaZvtx->SetBinError(49,2,0.033542);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,2,0.863779);
trkEffVsEtaZvtx->SetBinError(50,2,0.037599);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,2,0.872559);
trkEffVsEtaZvtx->SetBinError(51,2,0.041421);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,2,0.841976);
trkEffVsEtaZvtx->SetBinError(52,2,0.044447);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,2,0.656281);
trkEffVsEtaZvtx->SetBinError(53,2,0.064408);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,2,0.786446);
trkEffVsEtaZvtx->SetBinError(54,2,0.056844);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,2,0.798062);
trkEffVsEtaZvtx->SetBinError(55,2,0.056913);

////////////////////////////////////////////////////
// ybin: -10.000000 to 0.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,3,0.454593);
trkEffVsEtaZvtx->SetBinError(10,3,0.133241);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,3,0.333353);
trkEffVsEtaZvtx->SetBinError(11,3,0.123722);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,3,0.400020);
trkEffVsEtaZvtx->SetBinError(12,3,0.116005);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,3,0.500024);
trkEffVsEtaZvtx->SetBinError(13,3,0.100002);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,3,0.800055);
trkEffVsEtaZvtx->SetBinError(14,3,0.087378);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,3,0.769309);
trkEffVsEtaZvtx->SetBinError(15,3,0.080405);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,3,0.863703);
trkEffVsEtaZvtx->SetBinError(16,3,0.052386);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,3,0.961709);
trkEffVsEtaZvtx->SetBinError(17,3,0.047780);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,3,0.691260);
trkEffVsEtaZvtx->SetBinError(22,3,0.082624);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,3,0.722420);
trkEffVsEtaZvtx->SetBinError(23,3,0.053579);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,3,0.774023);
trkEffVsEtaZvtx->SetBinError(24,3,0.044290);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,3,0.809911);
trkEffVsEtaZvtx->SetBinError(25,3,0.045788);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,3,0.760213);
trkEffVsEtaZvtx->SetBinError(26,3,0.046471);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,3,0.836123);
trkEffVsEtaZvtx->SetBinError(27,3,0.038866);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,3,0.784352);
trkEffVsEtaZvtx->SetBinError(28,3,0.041541);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,3,0.803057);
trkEffVsEtaZvtx->SetBinError(29,3,0.042721);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,3,0.783393);
trkEffVsEtaZvtx->SetBinError(30,3,0.042703);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,3,0.853188);
trkEffVsEtaZvtx->SetBinError(31,3,0.037925);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,3,0.792678);
trkEffVsEtaZvtx->SetBinError(32,3,0.040163);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,3,0.840534);
trkEffVsEtaZvtx->SetBinError(33,3,0.040785);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,3,0.808905);
trkEffVsEtaZvtx->SetBinError(34,3,0.035817);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,3,0.865655);
trkEffVsEtaZvtx->SetBinError(35,3,0.035083);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,3,0.872968);
trkEffVsEtaZvtx->SetBinError(36,3,0.036299);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,3,0.871208);
trkEffVsEtaZvtx->SetBinError(37,3,0.038608);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,3,0.902181);
trkEffVsEtaZvtx->SetBinError(38,3,0.033816);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,3,0.851569);
trkEffVsEtaZvtx->SetBinError(39,3,0.038304);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,3,0.908380);
trkEffVsEtaZvtx->SetBinError(40,3,0.031953);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,3,0.732986);
trkEffVsEtaZvtx->SetBinError(41,3,0.048338);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,3,0.781156);
trkEffVsEtaZvtx->SetBinError(42,3,0.049759);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,3,0.807221);
trkEffVsEtaZvtx->SetBinError(43,3,0.065167);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,3,0.927607);
trkEffVsEtaZvtx->SetBinError(48,3,0.032769);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,3,0.945541);
trkEffVsEtaZvtx->SetBinError(49,3,0.033525);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,3,0.816391);
trkEffVsEtaZvtx->SetBinError(50,3,0.055054);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,3,0.775905);
trkEffVsEtaZvtx->SetBinError(51,3,0.054152);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,3,0.875028);
trkEffVsEtaZvtx->SetBinError(52,3,0.048585);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,3,0.739156);
trkEffVsEtaZvtx->SetBinError(53,3,0.063484);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,3,0.714316);
trkEffVsEtaZvtx->SetBinError(54,3,0.074146);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,3,0.690494);
trkEffVsEtaZvtx->SetBinError(55,3,0.069433);

////////////////////////////////////////////////////
// ybin: 0.000000 to 10.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,4,0.571779);
trkEffVsEtaZvtx->SetBinError(10,4,0.089018);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,4,0.593888);
trkEffVsEtaZvtx->SetBinError(11,4,0.089970);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,4,0.736673);
trkEffVsEtaZvtx->SetBinError(12,4,0.073593);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,4,0.764318);
trkEffVsEtaZvtx->SetBinError(13,4,0.082617);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,4,0.884824);
trkEffVsEtaZvtx->SetBinError(14,4,0.049985);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,4,0.949438);
trkEffVsEtaZvtx->SetBinError(15,4,0.041381);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,4,0.801527);
trkEffVsEtaZvtx->SetBinError(16,4,0.051736);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,4,0.856386);
trkEffVsEtaZvtx->SetBinError(17,4,0.047712);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,4,0.871824);
trkEffVsEtaZvtx->SetBinError(22,4,0.054535);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,4,0.800043);
trkEffVsEtaZvtx->SetBinError(23,4,0.049301);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,4,0.840625);
trkEffVsEtaZvtx->SetBinError(24,4,0.044163);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,4,0.753116);
trkEffVsEtaZvtx->SetBinError(25,4,0.047433);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,4,0.868161);
trkEffVsEtaZvtx->SetBinError(26,4,0.035763);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,4,0.867498);
trkEffVsEtaZvtx->SetBinError(27,4,0.037545);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,4,0.821803);
trkEffVsEtaZvtx->SetBinError(28,4,0.038032);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,4,0.833364);
trkEffVsEtaZvtx->SetBinError(29,4,0.039302);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,4,0.815831);
trkEffVsEtaZvtx->SetBinError(30,4,0.044339);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,4,0.822941);
trkEffVsEtaZvtx->SetBinError(31,4,0.038915);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,4,0.770854);
trkEffVsEtaZvtx->SetBinError(32,4,0.042594);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,4,0.916701);
trkEffVsEtaZvtx->SetBinError(33,4,0.029021);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,4,0.815241);
trkEffVsEtaZvtx->SetBinError(34,4,0.040368);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,4,0.811349);
trkEffVsEtaZvtx->SetBinError(35,4,0.037907);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,4,0.787059);
trkEffVsEtaZvtx->SetBinError(36,4,0.039200);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,4,0.785738);
trkEffVsEtaZvtx->SetBinError(37,4,0.041218);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,4,0.777805);
trkEffVsEtaZvtx->SetBinError(38,4,0.039775);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,4,0.852667);
trkEffVsEtaZvtx->SetBinError(39,4,0.036521);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,4,0.729200);
trkEffVsEtaZvtx->SetBinError(40,4,0.044902);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,4,0.715938);
trkEffVsEtaZvtx->SetBinError(41,4,0.047513);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,4,0.747161);
trkEffVsEtaZvtx->SetBinError(42,4,0.046144);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,4,0.857178);
trkEffVsEtaZvtx->SetBinError(43,4,0.054521);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,4,0.989801);
trkEffVsEtaZvtx->SetBinError(48,4,0.024412);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,4,0.957874);
trkEffVsEtaZvtx->SetBinError(49,4,0.040171);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,4,0.734121);
trkEffVsEtaZvtx->SetBinError(50,4,0.065502);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,4,0.766657);
trkEffVsEtaZvtx->SetBinError(51,4,0.082504);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,4,0.643681);
trkEffVsEtaZvtx->SetBinError(52,4,0.071720);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,4,0.630621);
trkEffVsEtaZvtx->SetBinError(53,4,0.078714);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,4,0.653096);
trkEffVsEtaZvtx->SetBinError(54,4,0.100347);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,4,0.505195);
trkEffVsEtaZvtx->SetBinError(55,4,0.100451);

////////////////////////////////////////////////////
// ybin: 10.000000 to 30.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,5,0.670401);
trkEffVsEtaZvtx->SetBinError(10,5,0.091571);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,5,0.747412);
trkEffVsEtaZvtx->SetBinError(11,5,0.076187);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,5,0.708362);
trkEffVsEtaZvtx->SetBinError(12,5,0.072892);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,5,0.593403);
trkEffVsEtaZvtx->SetBinError(13,5,0.087513);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,5,0.848491);
trkEffVsEtaZvtx->SetBinError(14,5,0.051233);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,5,0.745931);
trkEffVsEtaZvtx->SetBinError(15,5,0.057135);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,5,0.927968);
trkEffVsEtaZvtx->SetBinError(16,5,0.032995);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,5,0.974078);
trkEffVsEtaZvtx->SetBinError(17,5,0.022308);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,5,0.817229);
trkEffVsEtaZvtx->SetBinError(22,5,0.054996);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,5,0.769319);
trkEffVsEtaZvtx->SetBinError(23,5,0.042089);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,5,0.780847);
trkEffVsEtaZvtx->SetBinError(24,5,0.040385);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,5,0.826584);
trkEffVsEtaZvtx->SetBinError(25,5,0.038463);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,5,0.905661);
trkEffVsEtaZvtx->SetBinError(26,5,0.027933);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,5,0.818733);
trkEffVsEtaZvtx->SetBinError(27,5,0.035165);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,5,0.754348);
trkEffVsEtaZvtx->SetBinError(28,5,0.039582);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,5,0.736130);
trkEffVsEtaZvtx->SetBinError(29,5,0.039344);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,5,0.799270);
trkEffVsEtaZvtx->SetBinError(30,5,0.036809);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,5,0.782020);
trkEffVsEtaZvtx->SetBinError(31,5,0.034670);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,5,0.810489);
trkEffVsEtaZvtx->SetBinError(32,5,0.032983);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,5,0.761049);
trkEffVsEtaZvtx->SetBinError(33,5,0.035772);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,5,0.780415);
trkEffVsEtaZvtx->SetBinError(34,5,0.035532);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,5,0.810882);
trkEffVsEtaZvtx->SetBinError(35,5,0.036482);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,5,0.765491);
trkEffVsEtaZvtx->SetBinError(36,5,0.040182);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,5,0.810590);
trkEffVsEtaZvtx->SetBinError(37,5,0.036496);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,5,0.693100);
trkEffVsEtaZvtx->SetBinError(38,5,0.039271);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,5,0.814349);
trkEffVsEtaZvtx->SetBinError(39,5,0.035932);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,5,0.782925);
trkEffVsEtaZvtx->SetBinError(40,5,0.036315);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,5,0.814156);
trkEffVsEtaZvtx->SetBinError(41,5,0.034357);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,5,0.783838);
trkEffVsEtaZvtx->SetBinError(42,5,0.036835);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,5,0.743189);
trkEffVsEtaZvtx->SetBinError(43,5,0.056568);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,5,0.891904);
trkEffVsEtaZvtx->SetBinError(48,5,0.036535);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,5,0.787796);
trkEffVsEtaZvtx->SetBinError(49,5,0.056093);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,5,0.601918);
trkEffVsEtaZvtx->SetBinError(50,5,0.065418);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,5,0.447280);
trkEffVsEtaZvtx->SetBinError(51,5,0.067427);

// xbin: 1.900000 to 2.000000
trkEffVsEtaZvtx->SetBinContent(52,5,0.505483);
trkEffVsEtaZvtx->SetBinError(52,5,0.084933);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,5,0.529765);
trkEffVsEtaZvtx->SetBinError(53,5,0.076447);

// xbin: 2.100000 to 2.200000
trkEffVsEtaZvtx->SetBinContent(54,5,0.467727);
trkEffVsEtaZvtx->SetBinError(54,5,0.093236);

// xbin: 2.200000 to 2.300000
trkEffVsEtaZvtx->SetBinContent(55,5,0.351282);
trkEffVsEtaZvtx->SetBinError(55,5,0.089834);

////////////////////////////////////////////////////
// ybin: 30.000000 to 100.000000

// xbin: -2.300000 to -2.200000
trkEffVsEtaZvtx->SetBinContent(10,6,0.581940);
trkEffVsEtaZvtx->SetBinError(10,6,0.105665);

// xbin: -2.200000 to -2.100000
trkEffVsEtaZvtx->SetBinContent(11,6,0.558336);
trkEffVsEtaZvtx->SetBinError(11,6,0.108749);

// xbin: -2.100000 to -2.000000
trkEffVsEtaZvtx->SetBinContent(12,6,0.594408);
trkEffVsEtaZvtx->SetBinError(12,6,0.128420);

// xbin: -2.000000 to -1.900000
trkEffVsEtaZvtx->SetBinContent(13,6,0.704991);
trkEffVsEtaZvtx->SetBinError(13,6,0.077296);

// xbin: -1.900000 to -1.800000
trkEffVsEtaZvtx->SetBinContent(14,6,0.750644);
trkEffVsEtaZvtx->SetBinError(14,6,0.071781);

// xbin: -1.800000 to -1.700000
trkEffVsEtaZvtx->SetBinContent(15,6,0.981434);
trkEffVsEtaZvtx->SetBinError(15,6,0.039918);

// xbin: -1.700000 to -1.600000
trkEffVsEtaZvtx->SetBinContent(16,6,0.892674);
trkEffVsEtaZvtx->SetBinError(16,6,0.051173);

// xbin: -1.600000 to -1.500000
trkEffVsEtaZvtx->SetBinContent(17,6,0.922347);
trkEffVsEtaZvtx->SetBinError(17,6,0.052831);

// xbin: -1.100000 to -1.000000
trkEffVsEtaZvtx->SetBinContent(22,6,0.625467);
trkEffVsEtaZvtx->SetBinError(22,6,0.093640);

// xbin: -1.000000 to -0.900000
trkEffVsEtaZvtx->SetBinContent(23,6,0.744519);
trkEffVsEtaZvtx->SetBinError(23,6,0.071986);

// xbin: -0.900000 to -0.800000
trkEffVsEtaZvtx->SetBinContent(24,6,0.738397);
trkEffVsEtaZvtx->SetBinError(24,6,0.069687);

// xbin: -0.800000 to -0.700000
trkEffVsEtaZvtx->SetBinContent(25,6,0.741850);
trkEffVsEtaZvtx->SetBinError(25,6,0.058624);

// xbin: -0.700000 to -0.600000
trkEffVsEtaZvtx->SetBinContent(26,6,0.737079);
trkEffVsEtaZvtx->SetBinError(26,6,0.073581);

// xbin: -0.600000 to -0.500000
trkEffVsEtaZvtx->SetBinContent(27,6,0.751535);
trkEffVsEtaZvtx->SetBinError(27,6,0.063996);

// xbin: -0.500000 to -0.400000
trkEffVsEtaZvtx->SetBinContent(28,6,0.635767);
trkEffVsEtaZvtx->SetBinError(28,6,0.065131);

// xbin: -0.400000 to -0.300000
trkEffVsEtaZvtx->SetBinContent(29,6,0.699688);
trkEffVsEtaZvtx->SetBinError(29,6,0.068235);

// xbin: -0.300000 to -0.200000
trkEffVsEtaZvtx->SetBinContent(30,6,0.866384);
trkEffVsEtaZvtx->SetBinError(30,6,0.052104);

// xbin: -0.200000 to -0.100000
trkEffVsEtaZvtx->SetBinContent(31,6,0.783289);
trkEffVsEtaZvtx->SetBinError(31,6,0.055024);

// xbin: -0.100000 to 0.000000
trkEffVsEtaZvtx->SetBinContent(32,6,0.837457);
trkEffVsEtaZvtx->SetBinError(32,6,0.047348);

// xbin: 0.000000 to 0.100000
trkEffVsEtaZvtx->SetBinContent(33,6,0.816319);
trkEffVsEtaZvtx->SetBinError(33,6,0.058809);

// xbin: 0.100000 to 0.200000
trkEffVsEtaZvtx->SetBinContent(34,6,0.656510);
trkEffVsEtaZvtx->SetBinError(34,6,0.062677);

// xbin: 0.200000 to 0.300000
trkEffVsEtaZvtx->SetBinContent(35,6,0.675117);
trkEffVsEtaZvtx->SetBinError(35,6,0.065370);

// xbin: 0.300000 to 0.400000
trkEffVsEtaZvtx->SetBinContent(36,6,0.508891);
trkEffVsEtaZvtx->SetBinError(36,6,0.061592);

// xbin: 0.400000 to 0.500000
trkEffVsEtaZvtx->SetBinContent(37,6,0.692456);
trkEffVsEtaZvtx->SetBinError(37,6,0.061023);

// xbin: 0.500000 to 0.600000
trkEffVsEtaZvtx->SetBinContent(38,6,0.639439);
trkEffVsEtaZvtx->SetBinError(38,6,0.061718);

// xbin: 0.600000 to 0.700000
trkEffVsEtaZvtx->SetBinContent(39,6,0.742766);
trkEffVsEtaZvtx->SetBinError(39,6,0.056580);

// xbin: 0.700000 to 0.800000
trkEffVsEtaZvtx->SetBinContent(40,6,0.800755);
trkEffVsEtaZvtx->SetBinError(40,6,0.049262);

// xbin: 0.800000 to 0.900000
trkEffVsEtaZvtx->SetBinContent(41,6,0.792370);
trkEffVsEtaZvtx->SetBinError(41,6,0.047501);

// xbin: 0.900000 to 1.000000
trkEffVsEtaZvtx->SetBinContent(42,6,0.647762);
trkEffVsEtaZvtx->SetBinError(42,6,0.065266);

// xbin: 1.000000 to 1.100000
trkEffVsEtaZvtx->SetBinContent(43,6,0.730470);
trkEffVsEtaZvtx->SetBinError(43,6,0.071131);

// xbin: 1.500000 to 1.600000
trkEffVsEtaZvtx->SetBinContent(48,6,0.626707);
trkEffVsEtaZvtx->SetBinError(48,6,0.099835);

// xbin: 1.600000 to 1.700000
trkEffVsEtaZvtx->SetBinContent(49,6,0.182463);
trkEffVsEtaZvtx->SetBinError(49,6,0.081449);

// xbin: 1.700000 to 1.800000
trkEffVsEtaZvtx->SetBinContent(50,6,0.177394);
trkEffVsEtaZvtx->SetBinError(50,6,0.091523);

// xbin: 1.800000 to 1.900000
trkEffVsEtaZvtx->SetBinContent(51,6,0.047723);
trkEffVsEtaZvtx->SetBinError(51,6,0.057625);

// xbin: 2.000000 to 2.100000
trkEffVsEtaZvtx->SetBinContent(53,6,0.167833);
trkEffVsEtaZvtx->SetBinError(53,6,0.144926);

////////////////////////////////////////////////////
// ybin: over 100.000000
}
