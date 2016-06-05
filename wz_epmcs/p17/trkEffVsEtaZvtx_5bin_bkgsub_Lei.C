{
const int n_trkEffVsEtaZvtx_xbins = 64;
float trkEffVsEtaZvtx_xbins[n_trkEffVsEtaZvtx_xbins+1] = {-3.2,-3.1,-3.0000 ,-2.900000 ,-2.8,-2.7,-2.6,-2.5,-2.4,-2.3,-2.2,-2.1,-2.0,-1.9,-1.8,-1.7,-1.6 ,-1.50000 ,-1.4 ,-1.30 ,-1.200000 ,-1.1,-1.0,-0.9,-0.80 ,-0.7 ,-0.6 ,-0.5 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.4000,0.500000 ,0.600000 ,0.700000 ,0.800000 ,0.900000 ,1.000000 ,1.10000 ,1.20000 ,1.3,1.4,1.5,1.600000 ,1.7,1.800000 ,1.9,2.0,2.1,2.2,2.30000 ,2.4,2.5,2.6,2.700000 ,2.8,2.9,3.0,3.1,3.2};

const int n_trkEffVsEtaZvtx_ybins = 5;
float trkEffVsEtaZvtx_ybins[n_trkEffVsEtaZvtx_ybins+1] = {-100.000000 ,-40.000000 ,-10.000000 ,10.000000 ,40.000000 ,100.000000 };

TH2F *trkEffVsEtaZvtx = new TH2F("trkEffVsEtaZvtx","track efficiency vs detector eta and zvtx", n_trkEffVsEtaZvtx_xbins, trkEffVsEtaZvtx_xbins, n_trkEffVsEtaZvtx_ybins, trkEffVsEtaZvtx_ybins);


// ybin: -100.000000 to -40.000000

trkEffVsEtaZvtx->SetBinContent(17,1,0.13684);
trkEffVsEtaZvtx->SetBinContent(22,1,0.762378);
trkEffVsEtaZvtx->SetBinContent(23,1,0.763589);
trkEffVsEtaZvtx->SetBinContent(24,1,0.802532);
trkEffVsEtaZvtx->SetBinContent(25,1,0.755664);
trkEffVsEtaZvtx->SetBinContent(26,1,0.777037);
trkEffVsEtaZvtx->SetBinContent(27,1,0.683467);
trkEffVsEtaZvtx->SetBinContent(28,1,0.699259);
trkEffVsEtaZvtx->SetBinContent(29,1,0.717954);
trkEffVsEtaZvtx->SetBinContent(30,1,0.75719);
trkEffVsEtaZvtx->SetBinContent(31,1,0.742866);
trkEffVsEtaZvtx->SetBinContent(32,1,0.740705);
trkEffVsEtaZvtx->SetBinContent(33,1,0.76687);
trkEffVsEtaZvtx->SetBinContent(34,1,0.802333);
trkEffVsEtaZvtx->SetBinContent(35,1,0.798308);
trkEffVsEtaZvtx->SetBinContent(36,1,0.825552);
trkEffVsEtaZvtx->SetBinContent(37,1,0.827143);
trkEffVsEtaZvtx->SetBinContent(38,1,0.808874);
trkEffVsEtaZvtx->SetBinContent(39,1,0.852991);
trkEffVsEtaZvtx->SetBinContent(40,1,0.800043);
trkEffVsEtaZvtx->SetBinContent(41,1,0.728365);
trkEffVsEtaZvtx->SetBinContent(42,1,0.705457);
trkEffVsEtaZvtx->SetBinContent(43,1,0.654166);

trkEffVsEtaZvtx->SetBinContent(48,1,0.880215);
trkEffVsEtaZvtx->SetBinContent(49,1,0.849438);
trkEffVsEtaZvtx->SetBinContent(50,1,0.887191);
trkEffVsEtaZvtx->SetBinContent(51,1,0.783675);
trkEffVsEtaZvtx->SetBinContent(52,1,0.802997);
trkEffVsEtaZvtx->SetBinContent(53,1,0.603784);
trkEffVsEtaZvtx->SetBinContent(54,1,0.697706);
trkEffVsEtaZvtx->SetBinContent(55,1,0.65718);
trkEffVsEtaZvtx->SetBinContent(56,1,0.686694);
trkEffVsEtaZvtx->SetBinContent(57,1,0.681142);
trkEffVsEtaZvtx->SetBinContent(58,1,0.401117);
trkEffVsEtaZvtx->SetBinContent(60,1,0.131704);
trkEffVsEtaZvtx->SetBinContent(61,1,0.0658519);
trkEffVsEtaZvtx->SetBinContent(63,1,0.197556);


trkEffVsEtaZvtx->SetBinError(17,1,0.0369848);
trkEffVsEtaZvtx->SetBinError(22,1,0.0465462);
trkEffVsEtaZvtx->SetBinError(23,1,0.030523);
trkEffVsEtaZvtx->SetBinError(24,1,0.02866);
trkEffVsEtaZvtx->SetBinError(25,1,0.0315109);
trkEffVsEtaZvtx->SetBinError(26,1,0.0280627);
trkEffVsEtaZvtx->SetBinError(27,1,0.0315472);
trkEffVsEtaZvtx->SetBinError(28,1,0.0279709);
trkEffVsEtaZvtx->SetBinError(29,1,0.0285089);
trkEffVsEtaZvtx->SetBinError(30,1,0.029599);
trkEffVsEtaZvtx->SetBinError(31,1,0.0312527);
trkEffVsEtaZvtx->SetBinError(32,1,0.0293726);
trkEffVsEtaZvtx->SetBinError(33,1,0.0301022);
trkEffVsEtaZvtx->SetBinError(34,1,0.0276279);
trkEffVsEtaZvtx->SetBinError(35,1,0.0288886);
trkEffVsEtaZvtx->SetBinError(36,1,0.0272279);
trkEffVsEtaZvtx->SetBinError(37,1,0.0282374);
trkEffVsEtaZvtx->SetBinError(38,1,0.0292195);
trkEffVsEtaZvtx->SetBinError(39,1,0.0264444);
trkEffVsEtaZvtx->SetBinError(40,1,0.0329532);
trkEffVsEtaZvtx->SetBinError(41,1,0.0365453);
trkEffVsEtaZvtx->SetBinError(42,1,0.0352664);
trkEffVsEtaZvtx->SetBinError(43,1,0.0497641);


trkEffVsEtaZvtx->SetBinError(48,1,0.0253742);
trkEffVsEtaZvtx->SetBinError(49,1,0.0277209);
trkEffVsEtaZvtx->SetBinError(50,1,0.0261062);
trkEffVsEtaZvtx->SetBinError(51,1,0.0350558);
trkEffVsEtaZvtx->SetBinError(52,1,0.0372134);
trkEffVsEtaZvtx->SetBinError(53,1,0.046296);
trkEffVsEtaZvtx->SetBinError(54,1,0.0491805);
trkEffVsEtaZvtx->SetBinError(55,1,0.0513457);
trkEffVsEtaZvtx->SetBinError(56,1,0.0625871);
trkEffVsEtaZvtx->SetBinError(57,1,0.0717502);
trkEffVsEtaZvtx->SetBinError(58,1,0.0818924);
trkEffVsEtaZvtx->SetBinError(60,1,0.0920378);
trkEffVsEtaZvtx->SetBinError(61,1,0.0675033);
trkEffVsEtaZvtx->SetBinError(63,1,0.187692);


// ybin: -40.000000 to -10.000000


trkEffVsEtaZvtx->SetBinContent(4,2,0.0191397);
trkEffVsEtaZvtx->SetBinContent(5,2,0.0725769);
trkEffVsEtaZvtx->SetBinContent(6,2,0.00515119);
trkEffVsEtaZvtx->SetBinContent(7,2,0.13598);
trkEffVsEtaZvtx->SetBinContent(8,2,0.374079);
trkEffVsEtaZvtx->SetBinContent(9,2,0.349525);
trkEffVsEtaZvtx->SetBinContent(10,2,0.337485);
trkEffVsEtaZvtx->SetBinContent(11,2,0.373375);
trkEffVsEtaZvtx->SetBinContent(12,2,0.40248);
trkEffVsEtaZvtx->SetBinContent(13,2,0.340755);
trkEffVsEtaZvtx->SetBinContent(14,2,0.448059);
trkEffVsEtaZvtx->SetBinContent(15,2,0.572085);
trkEffVsEtaZvtx->SetBinContent(16,2,0.712874);
trkEffVsEtaZvtx->SetBinContent(17,2,0.823756);

trkEffVsEtaZvtx->SetBinContent(22,2,0.936472);
trkEffVsEtaZvtx->SetBinContent(23,2,0.955965);
trkEffVsEtaZvtx->SetBinContent(24,2,0.939844);
trkEffVsEtaZvtx->SetBinContent(25,2,0.953928);
trkEffVsEtaZvtx->SetBinContent(26,2,0.922748);
trkEffVsEtaZvtx->SetBinContent(27,2,0.925065);
trkEffVsEtaZvtx->SetBinContent(28,2,0.90402);
trkEffVsEtaZvtx->SetBinContent(29,2,0.874891);
trkEffVsEtaZvtx->SetBinContent(30,2,0.882472);
trkEffVsEtaZvtx->SetBinContent(31,2,0.889701);
trkEffVsEtaZvtx->SetBinContent(32,2,0.878889);
trkEffVsEtaZvtx->SetBinContent(33,2,0.884218);
trkEffVsEtaZvtx->SetBinContent(34,2,0.884482);
trkEffVsEtaZvtx->SetBinContent(35,2,0.893175);
trkEffVsEtaZvtx->SetBinContent(36,2,0.958754);
trkEffVsEtaZvtx->SetBinContent(37,2,0.957587);
trkEffVsEtaZvtx->SetBinContent(38,2,0.940839);
trkEffVsEtaZvtx->SetBinContent(39,2,0.964267);
trkEffVsEtaZvtx->SetBinContent(40,2,0.963819);
trkEffVsEtaZvtx->SetBinContent(41,2,0.958102);
trkEffVsEtaZvtx->SetBinContent(42,2,0.936877);
trkEffVsEtaZvtx->SetBinContent(43,2,0.927529);


trkEffVsEtaZvtx->SetBinContent(48,2,0.937126);
trkEffVsEtaZvtx->SetBinContent(49,2,0.906815);
trkEffVsEtaZvtx->SetBinContent(50,2,0.879719);
trkEffVsEtaZvtx->SetBinContent(51,2,0.792868);
trkEffVsEtaZvtx->SetBinContent(52,2,0.753915);
trkEffVsEtaZvtx->SetBinContent(53,2,0.757989);
trkEffVsEtaZvtx->SetBinContent(54,2,0.685703);
trkEffVsEtaZvtx->SetBinContent(55,2,0.662515);
trkEffVsEtaZvtx->SetBinContent(56,2,0.681668);
trkEffVsEtaZvtx->SetBinContent(57,2,0.642677);
trkEffVsEtaZvtx->SetBinContent(58,2,0.348829);
trkEffVsEtaZvtx->SetBinContent(59,2,0.0335956);
trkEffVsEtaZvtx->SetBinContent(60,2,0.258083);
trkEffVsEtaZvtx->SetBinContent(61,2,0.142209);
trkEffVsEtaZvtx->SetBinContent(62,2,0.017334);

trkEffVsEtaZvtx->SetBinError(4,2,0.013899);
trkEffVsEtaZvtx->SetBinError(5,2,0.022919);
trkEffVsEtaZvtx->SetBinError(6,2,0.00523704);
trkEffVsEtaZvtx->SetBinError(7,2,0.0268641);
trkEffVsEtaZvtx->SetBinError(8,2,0.0323417);
trkEffVsEtaZvtx->SetBinError(9,2,0.0308059);
trkEffVsEtaZvtx->SetBinError(10,2,0.0273165);
trkEffVsEtaZvtx->SetBinError(11,2,0.0266428);
trkEffVsEtaZvtx->SetBinError(12,2,0.0242875);
trkEffVsEtaZvtx->SetBinError(13,2,0.0226793);
trkEffVsEtaZvtx->SetBinError(14,2,0.0218293);
trkEffVsEtaZvtx->SetBinError(15,2,0.0217377);
trkEffVsEtaZvtx->SetBinError(16,2,0.0182244);
trkEffVsEtaZvtx->SetBinError(17,2,0.014609);

trkEffVsEtaZvtx->SetBinError(22,2,0.0109036);
trkEffVsEtaZvtx->SetBinError(23,2,0.00704769);
trkEffVsEtaZvtx->SetBinError(24,2,0.00789068);
trkEffVsEtaZvtx->SetBinError(25,2,0.00667866);
trkEffVsEtaZvtx->SetBinError(26,2,0.00846232);
trkEffVsEtaZvtx->SetBinError(27,2,0.00833335);
trkEffVsEtaZvtx->SetBinError(28,2,0.00918808);
trkEffVsEtaZvtx->SetBinError(29,2,0.0106613);
trkEffVsEtaZvtx->SetBinError(30,2,0.0103876);
trkEffVsEtaZvtx->SetBinError(31,2,0.0101856);
trkEffVsEtaZvtx->SetBinError(32,2,0.00999205);
trkEffVsEtaZvtx->SetBinError(33,2,0.00987992);
trkEffVsEtaZvtx->SetBinError(34,2,0.0100239);
trkEffVsEtaZvtx->SetBinError(35,2,0.00962632);
trkEffVsEtaZvtx->SetBinError(36,2,0.00656265);
trkEffVsEtaZvtx->SetBinError(37,2,0.00654406);
trkEffVsEtaZvtx->SetBinError(38,2,0.00800163);
trkEffVsEtaZvtx->SetBinError(39,2,0.00628915);
trkEffVsEtaZvtx->SetBinError(40,2,0.00648196);
trkEffVsEtaZvtx->SetBinError(41,2,0.00706808);
trkEffVsEtaZvtx->SetBinError(42,2,0.00877196);
trkEffVsEtaZvtx->SetBinError(43,2,0.0125667);

trkEffVsEtaZvtx->SetBinError(48,2,0.0088288);
trkEffVsEtaZvtx->SetBinError(49,2,0.0108087);
trkEffVsEtaZvtx->SetBinError(50,2,0.0130988);
trkEffVsEtaZvtx->SetBinError(51,2,0.0167553);
trkEffVsEtaZvtx->SetBinError(52,2,0.0191707);
trkEffVsEtaZvtx->SetBinError(53,2,0.0200106);
trkEffVsEtaZvtx->SetBinError(54,2,0.0241338);
trkEffVsEtaZvtx->SetBinError(55,2,0.0259802);
trkEffVsEtaZvtx->SetBinError(56,2,0.0276574);
trkEffVsEtaZvtx->SetBinError(57,2,0.0315419);
trkEffVsEtaZvtx->SetBinError(58,2,0.0355509);
trkEffVsEtaZvtx->SetBinError(59,2,0.0143485);
trkEffVsEtaZvtx->SetBinError(60,2,0.0448344);
trkEffVsEtaZvtx->SetBinError(61,2,0.0405771);
trkEffVsEtaZvtx->SetBinError(62,2,0.0183381);


// ybin: -10.000000 to 10.000000

trkEffVsEtaZvtx->SetBinContent(4,3,0.0205887);
trkEffVsEtaZvtx->SetBinContent(5,3,0.12839);
trkEffVsEtaZvtx->SetBinContent(6,3,0.039049);
trkEffVsEtaZvtx->SetBinContent(7,3,0.339217);
trkEffVsEtaZvtx->SetBinContent(8,3,0.664682);
trkEffVsEtaZvtx->SetBinContent(9,3,0.741601);
trkEffVsEtaZvtx->SetBinContent(10,3,0.657924);
trkEffVsEtaZvtx->SetBinContent(11,3,0.596412);
trkEffVsEtaZvtx->SetBinContent(12,3,0.602622);
trkEffVsEtaZvtx->SetBinContent(13,3,0.739572);
trkEffVsEtaZvtx->SetBinContent(14,3,0.779029);
trkEffVsEtaZvtx->SetBinContent(15,3,0.874697);
trkEffVsEtaZvtx->SetBinContent(16,3,0.920721);
trkEffVsEtaZvtx->SetBinContent(17,3,0.959807);

trkEffVsEtaZvtx->SetBinContent(22,3,0.960626);
trkEffVsEtaZvtx->SetBinContent(23,3,0.962531);
trkEffVsEtaZvtx->SetBinContent(24,3,0.963439);
trkEffVsEtaZvtx->SetBinContent(25,3,0.957532);
trkEffVsEtaZvtx->SetBinContent(26,3,0.96008);
trkEffVsEtaZvtx->SetBinContent(27,3,0.955785);
trkEffVsEtaZvtx->SetBinContent(28,3,0.924899);
trkEffVsEtaZvtx->SetBinContent(29,3,0.913287);
trkEffVsEtaZvtx->SetBinContent(30,3,0.898476);
trkEffVsEtaZvtx->SetBinContent(31,3,0.897047);
trkEffVsEtaZvtx->SetBinContent(32,3,0.896608);
trkEffVsEtaZvtx->SetBinContent(33,3,0.875322);
trkEffVsEtaZvtx->SetBinContent(34,3,0.893966);
trkEffVsEtaZvtx->SetBinContent(35,3,0.890246);
trkEffVsEtaZvtx->SetBinContent(36,3,0.91983);
trkEffVsEtaZvtx->SetBinContent(37,3,0.933109);
trkEffVsEtaZvtx->SetBinContent(38,3,0.905528);
trkEffVsEtaZvtx->SetBinContent(39,3,0.940459);
trkEffVsEtaZvtx->SetBinContent(40,3,0.968336);
trkEffVsEtaZvtx->SetBinContent(41,3,0.954572);
trkEffVsEtaZvtx->SetBinContent(42,3,0.970997);
trkEffVsEtaZvtx->SetBinContent(43,3,0.932342);


trkEffVsEtaZvtx->SetBinContent(48,3,0.948098);
trkEffVsEtaZvtx->SetBinContent(49,3,0.891723);
trkEffVsEtaZvtx->SetBinContent(50,3,0.88113);
trkEffVsEtaZvtx->SetBinContent(51,3,0.810869);
trkEffVsEtaZvtx->SetBinContent(52,3,0.714793);
trkEffVsEtaZvtx->SetBinContent(53,3,0.619836);
trkEffVsEtaZvtx->SetBinContent(54,3,0.641158);
trkEffVsEtaZvtx->SetBinContent(55,3,0.645583);
trkEffVsEtaZvtx->SetBinContent(56,3,0.715984);
trkEffVsEtaZvtx->SetBinContent(57,3,0.713077);
trkEffVsEtaZvtx->SetBinContent(58,3,0.448642);
trkEffVsEtaZvtx->SetBinContent(59,3,0.0642123);
trkEffVsEtaZvtx->SetBinContent(60,3,0.232928);
trkEffVsEtaZvtx->SetBinContent(61,3,0.106088);
trkEffVsEtaZvtx->SetBinContent(62,3,0.0109078);

   trkEffVsEtaZvtx->SetBinError(4,3,0.0152808);
   trkEffVsEtaZvtx->SetBinError(5,3,0.0284268);
   trkEffVsEtaZvtx->SetBinError(6,3,0.0124128);
   trkEffVsEtaZvtx->SetBinError(7,3,0.0328701);
   trkEffVsEtaZvtx->SetBinError(8,3,0.0277016);
   trkEffVsEtaZvtx->SetBinError(9,3,0.0244977);
   trkEffVsEtaZvtx->SetBinError(10,3,0.0243804);
   trkEffVsEtaZvtx->SetBinError(11,3,0.0235262);
   trkEffVsEtaZvtx->SetBinError(12,3,0.0218829);
   trkEffVsEtaZvtx->SetBinError(13,3,0.0186065);
   trkEffVsEtaZvtx->SetBinError(14,3,0.0161963);
   trkEffVsEtaZvtx->SetBinError(15,3,0.0127858);
   trkEffVsEtaZvtx->SetBinError(16,3,0.00983395);
   trkEffVsEtaZvtx->SetBinError(17,3,0.00707053);
trkEffVsEtaZvtx->SetBinError(22,3,0.00877703);
trkEffVsEtaZvtx->SetBinError(23,3,0.00651422);
trkEffVsEtaZvtx->SetBinError(24,3,0.00586212);
trkEffVsEtaZvtx->SetBinError(25,3,0.00633464);
trkEffVsEtaZvtx->SetBinError(26,3,0.00613087);
trkEffVsEtaZvtx->SetBinError(27,3,0.00629562);
trkEffVsEtaZvtx->SetBinError(28,3,0.00775198);
trkEffVsEtaZvtx->SetBinError(29,3,0.00851826);
trkEffVsEtaZvtx->SetBinError(30,3,0.0091611);
trkEffVsEtaZvtx->SetBinError(31,3,0.00897036);
trkEffVsEtaZvtx->SetBinError(32,3,0.00899734);
trkEffVsEtaZvtx->SetBinError(33,3,0.00966862);
trkEffVsEtaZvtx->SetBinError(34,3,0.00886417);
trkEffVsEtaZvtx->SetBinError(35,3,0.00919987);
trkEffVsEtaZvtx->SetBinError(36,3,0.00804425);
trkEffVsEtaZvtx->SetBinError(37,3,0.00711134);
trkEffVsEtaZvtx->SetBinError(38,3,0.00881257);
trkEffVsEtaZvtx->SetBinError(39,3,0.00711786);
trkEffVsEtaZvtx->SetBinError(40,3,0.00538889);
trkEffVsEtaZvtx->SetBinError(41,3,0.00657971);
trkEffVsEtaZvtx->SetBinError(42,3,0.00525367);
trkEffVsEtaZvtx->SetBinError(43,3,0.0109174);


trkEffVsEtaZvtx->SetBinError(48,3,0.00777719);
trkEffVsEtaZvtx->SetBinError(49,3,0.0111939);
trkEffVsEtaZvtx->SetBinError(50,3,0.0125941);
trkEffVsEtaZvtx->SetBinError(51,3,0.0152602);
trkEffVsEtaZvtx->SetBinError(52,3,0.0186452);
trkEffVsEtaZvtx->SetBinError(53,3,0.0203649);
trkEffVsEtaZvtx->SetBinError(54,3,0.0215149);
trkEffVsEtaZvtx->SetBinError(55,3,0.0227205);
trkEffVsEtaZvtx->SetBinError(56,3,0.0258352);
trkEffVsEtaZvtx->SetBinError(57,3,0.0271128);
trkEffVsEtaZvtx->SetBinError(58,3,0.0328548);
trkEffVsEtaZvtx->SetBinError(59,3,0.017558);
trkEffVsEtaZvtx->SetBinError(60,3,0.0350517);
trkEffVsEtaZvtx->SetBinError(61,3,0.0290746);
trkEffVsEtaZvtx->SetBinError(62,3,0.0113377);



// ybin: 10.000000 to 40.000000

trkEffVsEtaZvtx->SetBinContent(4,4,0.0197203);
trkEffVsEtaZvtx->SetBinContent(5,4,0.100916);
trkEffVsEtaZvtx->SetBinContent(6,4,0.0468444);
trkEffVsEtaZvtx->SetBinContent(7,4,0.23715);
trkEffVsEtaZvtx->SetBinContent(8,4,0.650467);
trkEffVsEtaZvtx->SetBinContent(9,4,0.615307);
trkEffVsEtaZvtx->SetBinContent(10,4,0.631667);
trkEffVsEtaZvtx->SetBinContent(11,4,0.679612);
trkEffVsEtaZvtx->SetBinContent(12,4,0.683941);
trkEffVsEtaZvtx->SetBinContent(13,4,0.747325);
trkEffVsEtaZvtx->SetBinContent(14,4,0.844986);
trkEffVsEtaZvtx->SetBinContent(15,4,0.860728);
trkEffVsEtaZvtx->SetBinContent(16,4,0.940952);
trkEffVsEtaZvtx->SetBinContent(17,4,0.966293);

trkEffVsEtaZvtx->SetBinContent(22,4,0.974524);
trkEffVsEtaZvtx->SetBinContent(23,4,0.998259);
trkEffVsEtaZvtx->SetBinContent(24,4,0.982456);
trkEffVsEtaZvtx->SetBinContent(25,4,0.977259);
trkEffVsEtaZvtx->SetBinContent(26,4,0.975278);
trkEffVsEtaZvtx->SetBinContent(27,4,0.981828);
trkEffVsEtaZvtx->SetBinContent(28,4,0.95544);
trkEffVsEtaZvtx->SetBinContent(29,4,0.957637);
trkEffVsEtaZvtx->SetBinContent(30,4,0.941004);
trkEffVsEtaZvtx->SetBinContent(31,4,0.923267);
trkEffVsEtaZvtx->SetBinContent(32,4,0.896669);
trkEffVsEtaZvtx->SetBinContent(33,4,0.879313);
trkEffVsEtaZvtx->SetBinContent(34,4,0.855095);
trkEffVsEtaZvtx->SetBinContent(35,4,0.851391);
trkEffVsEtaZvtx->SetBinContent(36,4,0.879645);
trkEffVsEtaZvtx->SetBinContent(37,4,0.862729);
trkEffVsEtaZvtx->SetBinContent(38,4,0.894189);
trkEffVsEtaZvtx->SetBinContent(39,4,0.906552);
trkEffVsEtaZvtx->SetBinContent(40,4,0.92854);
trkEffVsEtaZvtx->SetBinContent(41,4,0.925592);
trkEffVsEtaZvtx->SetBinContent(42,4,0.943585);
trkEffVsEtaZvtx->SetBinContent(43,4,0.938521);


trkEffVsEtaZvtx->SetBinContent(48,4,0.825474);
trkEffVsEtaZvtx->SetBinContent(49,4,0.714126);
trkEffVsEtaZvtx->SetBinContent(50,4,0.556889);
trkEffVsEtaZvtx->SetBinContent(51,4,0.400936);
trkEffVsEtaZvtx->SetBinContent(52,4,0.357683);
trkEffVsEtaZvtx->SetBinContent(53,4,0.328532);
trkEffVsEtaZvtx->SetBinContent(54,4,0.377149);
trkEffVsEtaZvtx->SetBinContent(55,4,0.370525);
trkEffVsEtaZvtx->SetBinContent(56,4,0.380518);
trkEffVsEtaZvtx->SetBinContent(57,4,0.318679);
trkEffVsEtaZvtx->SetBinContent(58,4,0.223978);
trkEffVsEtaZvtx->SetBinContent(59,4,0.0468956);
trkEffVsEtaZvtx->SetBinContent(60,4,0.0931098);
trkEffVsEtaZvtx->SetBinContent(61,4,0.071102);
trkEffVsEtaZvtx->SetBinContent(62,4,0.0170573);

trkEffVsEtaZvtx->SetBinError(4,4,0.0155726);
trkEffVsEtaZvtx->SetBinError(5,4,0.0325427);
trkEffVsEtaZvtx->SetBinError(6,4,0.0179439);
trkEffVsEtaZvtx->SetBinError(7,4,0.0363441);
trkEffVsEtaZvtx->SetBinError(8,4,0.0339825);
trkEffVsEtaZvtx->SetBinError(9,4,0.0326751);
trkEffVsEtaZvtx->SetBinError(10,4,0.0264159);
trkEffVsEtaZvtx->SetBinError(11,4,0.0252784);
trkEffVsEtaZvtx->SetBinError(12,4,0.0224795);
trkEffVsEtaZvtx->SetBinError(13,4,0.0203662);
trkEffVsEtaZvtx->SetBinError(14,4,0.0170629);
trkEffVsEtaZvtx->SetBinError(15,4,0.0151061);
trkEffVsEtaZvtx->SetBinError(16,4,0.00952706);
trkEffVsEtaZvtx->SetBinError(17,4,0.00707473);

trkEffVsEtaZvtx->SetBinError(22,4,0.00882073);
trkEffVsEtaZvtx->SetBinError(23,4,0.00173075);
trkEffVsEtaZvtx->SetBinError(24,4,0.00494301);
trkEffVsEtaZvtx->SetBinError(25,4,0.00568449);
trkEffVsEtaZvtx->SetBinError(26,4,0.00570844);
trkEffVsEtaZvtx->SetBinError(27,4,0.00481102);
trkEffVsEtaZvtx->SetBinError(28,4,0.0072585);
trkEffVsEtaZvtx->SetBinError(29,4,0.00716457);
trkEffVsEtaZvtx->SetBinError(30,4,0.0080825);
trkEffVsEtaZvtx->SetBinError(31,4,0.0091592);
trkEffVsEtaZvtx->SetBinError(32,4,0.0102145);
trkEffVsEtaZvtx->SetBinError(33,4,0.0107412);
trkEffVsEtaZvtx->SetBinError(34,4,0.0114936);
trkEffVsEtaZvtx->SetBinError(35,4,0.0116031);
trkEffVsEtaZvtx->SetBinError(36,4,0.0104322);
trkEffVsEtaZvtx->SetBinError(37,4,0.0110336);
trkEffVsEtaZvtx->SetBinError(38,4,0.0102248);
trkEffVsEtaZvtx->SetBinError(39,4,0.00958815);
trkEffVsEtaZvtx->SetBinError(40,4,0.00842785);
trkEffVsEtaZvtx->SetBinError(41,4,0.00894184);
trkEffVsEtaZvtx->SetBinError(42,4,0.0078492);
trkEffVsEtaZvtx->SetBinError(43,4,0.0109089);


trkEffVsEtaZvtx->SetBinError(48,4,0.0155965);
trkEffVsEtaZvtx->SetBinError(49,4,0.0190628);
trkEffVsEtaZvtx->SetBinError(50,4,0.0216236);
trkEffVsEtaZvtx->SetBinError(51,4,0.0221172);
trkEffVsEtaZvtx->SetBinError(52,4,0.0234858);
trkEffVsEtaZvtx->SetBinError(53,4,0.0242354);
trkEffVsEtaZvtx->SetBinError(54,4,0.0255918);
trkEffVsEtaZvtx->SetBinError(55,4,0.0272855);
trkEffVsEtaZvtx->SetBinError(56,4,0.0319207);
trkEffVsEtaZvtx->SetBinError(57,4,0.0322587);
trkEffVsEtaZvtx->SetBinError(58,4,0.0330748);
trkEffVsEtaZvtx->SetBinError(59,4,0.0167265);
trkEffVsEtaZvtx->SetBinError(60,4,0.0281888);
trkEffVsEtaZvtx->SetBinError(61,4,0.0294978);
trkEffVsEtaZvtx->SetBinError(62,4,0.0178309);


// ybin: 40.000000 to 100.000000

trkEffVsEtaZvtx->SetBinContent(5,5,0.157493);
trkEffVsEtaZvtx->SetBinContent(6,5,0.0416033);
trkEffVsEtaZvtx->SetBinContent(7,5,0.102785);
trkEffVsEtaZvtx->SetBinContent(8,5,0.616708);
trkEffVsEtaZvtx->SetBinContent(9,5,0.555972);
trkEffVsEtaZvtx->SetBinContent(10,5,0.577458);
trkEffVsEtaZvtx->SetBinContent(11,5,0.653691);
trkEffVsEtaZvtx->SetBinContent(12,5,0.749799);
trkEffVsEtaZvtx->SetBinContent(13,5,0.784903);
trkEffVsEtaZvtx->SetBinContent(14,5,0.828976);
trkEffVsEtaZvtx->SetBinContent(15,5,0.834204);
trkEffVsEtaZvtx->SetBinContent(16,5,0.870757);
trkEffVsEtaZvtx->SetBinContent(17,5,0.903508);

trkEffVsEtaZvtx->SetBinContent(22,5,0.580279);
trkEffVsEtaZvtx->SetBinContent(23,5,0.612396);
trkEffVsEtaZvtx->SetBinContent(24,5,0.682903);
trkEffVsEtaZvtx->SetBinContent(25,5,0.764005);
trkEffVsEtaZvtx->SetBinContent(26,5,0.734709);
trkEffVsEtaZvtx->SetBinContent(27,5,0.796178);
trkEffVsEtaZvtx->SetBinContent(28,5,0.812018);
trkEffVsEtaZvtx->SetBinContent(29,5,0.832381);
trkEffVsEtaZvtx->SetBinContent(30,5,0.825351);
trkEffVsEtaZvtx->SetBinContent(31,5,0.803711);
trkEffVsEtaZvtx->SetBinContent(32,5,0.783506);
trkEffVsEtaZvtx->SetBinContent(33,5,0.759412);
trkEffVsEtaZvtx->SetBinContent(34,5,0.723609);
trkEffVsEtaZvtx->SetBinContent(35,5,0.749018);
trkEffVsEtaZvtx->SetBinContent(36,5,0.708092);
trkEffVsEtaZvtx->SetBinContent(37,5,0.665888);
trkEffVsEtaZvtx->SetBinContent(38,5,0.662269);
trkEffVsEtaZvtx->SetBinContent(39,5,0.701015);
trkEffVsEtaZvtx->SetBinContent(40,5,0.68557);
trkEffVsEtaZvtx->SetBinContent(41,5,0.763421);
trkEffVsEtaZvtx->SetBinContent(42,5,0.703143);
trkEffVsEtaZvtx->SetBinContent(43,5,0.701226);


trkEffVsEtaZvtx->SetBinContent(48,5,0.225505);
trkEffVsEtaZvtx->SetBinContent(49,5,0.0593434);


trkEffVsEtaZvtx->SetBinError(6,5,0.043516);
trkEffVsEtaZvtx->SetBinError(7,5,0.0600571);
trkEffVsEtaZvtx->SetBinError(8,5,0.0961515);
trkEffVsEtaZvtx->SetBinError(9,5,0.0863767);
trkEffVsEtaZvtx->SetBinError(10,5,0.0646991);
trkEffVsEtaZvtx->SetBinError(11,5,0.0517932);
trkEffVsEtaZvtx->SetBinError(12,5,0.0500735);
trkEffVsEtaZvtx->SetBinError(13,5,0.0466951);
trkEffVsEtaZvtx->SetBinError(14,5,0.0349246);
trkEffVsEtaZvtx->SetBinError(15,5,0.0333995);
trkEffVsEtaZvtx->SetBinError(16,5,0.0287622);
trkEffVsEtaZvtx->SetBinError(17,5,0.0259816);


trkEffVsEtaZvtx->SetBinError(22,5,0.0624901);
trkEffVsEtaZvtx->SetBinError(23,5,0.0527705);
trkEffVsEtaZvtx->SetBinError(24,5,0.0410939);
trkEffVsEtaZvtx->SetBinError(25,5,0.0363504);
trkEffVsEtaZvtx->SetBinError(26,5,0.0369155);
trkEffVsEtaZvtx->SetBinError(27,5,0.0370266);
trkEffVsEtaZvtx->SetBinError(28,5,0.0322554);
trkEffVsEtaZvtx->SetBinError(29,5,0.0293408);
trkEffVsEtaZvtx->SetBinError(30,5,0.0321984);
trkEffVsEtaZvtx->SetBinError(31,5,0.0338931);
trkEffVsEtaZvtx->SetBinError(32,5,0.0321077);
trkEffVsEtaZvtx->SetBinError(33,5,0.0331487);
trkEffVsEtaZvtx->SetBinError(34,5,0.0326231);
trkEffVsEtaZvtx->SetBinError(35,5,0.0320751);
trkEffVsEtaZvtx->SetBinError(36,5,0.0336698);
trkEffVsEtaZvtx->SetBinError(37,5,0.035694);
trkEffVsEtaZvtx->SetBinError(38,5,0.037684);
trkEffVsEtaZvtx->SetBinError(39,5,0.0335138);
trkEffVsEtaZvtx->SetBinError(40,5,0.0336441);
trkEffVsEtaZvtx->SetBinError(41,5,0.0320011);
trkEffVsEtaZvtx->SetBinError(42,5,0.0376331);
trkEffVsEtaZvtx->SetBinError(43,5,0.0493252);



trkEffVsEtaZvtx->SetBinError(48,5,0.0469596);
trkEffVsEtaZvtx->SetBinError(49,5,0.0265485);


}
