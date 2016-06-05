{
const int n_trkEffVsEtaZvtx_xbins = 31;

float trkEffVsEtaZvtx_xbins[n_trkEffVsEtaZvtx_xbins+1] = {-3.100000 ,-2.900000 ,-2.700000 ,-2.500000 ,-2.300000 ,-2.100000 ,-1.900000 ,-1.700000 ,-1.500000 ,-1.300000 ,-1.100000 ,-0.900000 ,-0.700000 ,-0.500000 ,-0.300000 ,-0.100000 ,0.100000 ,0.300000 ,0.500000 ,0.700000 ,0.900000 ,1.100000 ,1.300000 ,1.500000 ,1.700000 ,1.900000 ,2.100000 ,2.300000 ,2.500000 ,2.700000 ,2.900000 ,3.100000};

const int n_trkEffVsEtaZvtx_ybins = 6;
float trkEffVsEtaZvtx_ybins[n_trkEffVsEtaZvtx_ybins+1] = {-60.000000, -40.000000, -20.000000, 0.000000, 20.000000, 40.000000, 60.000000  };

TH2F *trkEffVsEtaZvtx = new TH2F("trkEffVsEtaZvtx","track efficiency vs physics eta and zvtx", n_trkEffVsEtaZvtx_xbins, trkEffVsEtaZvtx_xbins, n_trkEffVsEtaZvtx_ybins, trkEffVsEtaZvtx_ybins);

////////////////////////////////////////////////////
// ybin: under -60.000000

////////////////////////////////////////////////////
// ybin: -60.000000 to -40.000000
 trkEffVsEtaZvtx->SetBinContent(11,1,0.666667);
 trkEffVsEtaZvtx->SetBinContent(12,1,0.296875);
 trkEffVsEtaZvtx->SetBinContent(13,1,0.0630137);
 trkEffVsEtaZvtx->SetBinContent(14,1,0.0227848);
 trkEffVsEtaZvtx->SetBinContent(15,1,0.0175);
 trkEffVsEtaZvtx->SetBinContent(16,1,0.0362812);
 trkEffVsEtaZvtx->SetBinContent(17,1,0.0307377);
 trkEffVsEtaZvtx->SetBinContent(18,1,0.208861);
 trkEffVsEtaZvtx->SetBinContent(19,1,0.402);
 trkEffVsEtaZvtx->SetBinContent(20,1,0.636364);
 trkEffVsEtaZvtx->SetBinContent(21,1,0.781746);
 trkEffVsEtaZvtx->SetBinContent(22,1,0.816867);
 trkEffVsEtaZvtx->SetBinContent(23,1,0.690476);
 trkEffVsEtaZvtx->SetBinError(10,1,0.02);
 trkEffVsEtaZvtx->SetBinError(11,1,0.137545);
 trkEffVsEtaZvtx->SetBinError(12,1,0.0605109);
 trkEffVsEtaZvtx->SetBinError(13,1,0.0237015);
 trkEffVsEtaZvtx->SetBinError(14,1,0.0213628);
 trkEffVsEtaZvtx->SetBinError(15,1,0.0210472);
 trkEffVsEtaZvtx->SetBinError(16,1,0.0218926);
 trkEffVsEtaZvtx->SetBinError(17,1,0.0214721);
 trkEffVsEtaZvtx->SetBinError(18,1,0.0273606);
 trkEffVsEtaZvtx->SetBinError(19,1,0.0296781);
 trkEffVsEtaZvtx->SetBinError(20,1,0.0294531);
 trkEffVsEtaZvtx->SetBinError(21,1,0.0271759);
 trkEffVsEtaZvtx->SetBinError(22,1,0.0275766);
 trkEffVsEtaZvtx->SetBinError(23,1,0.0740847);

 ////////////////////////////////////////////////////
// ybin: -40.000000 to -20.000000
 trkEffVsEtaZvtx->SetBinContent(10,2,0.8);
 trkEffVsEtaZvtx->SetBinContent(11,2,0.907407);
 trkEffVsEtaZvtx->SetBinContent(12,2,0.823292);
 trkEffVsEtaZvtx->SetBinContent(13,2,0.786003);
 trkEffVsEtaZvtx->SetBinContent(14,2,0.818132);
 trkEffVsEtaZvtx->SetBinContent(15,2,0.828752);
 trkEffVsEtaZvtx->SetBinContent(16,2,0.820954);
 trkEffVsEtaZvtx->SetBinContent(17,2,0.881334);
 trkEffVsEtaZvtx->SetBinContent(18,2,0.906635);
 trkEffVsEtaZvtx->SetBinContent(19,2,0.919847);
 trkEffVsEtaZvtx->SetBinContent(20,2,0.91493);
 trkEffVsEtaZvtx->SetBinContent(21,2,0.902046);
 trkEffVsEtaZvtx->SetBinContent(22,2,0.882225);
 trkEffVsEtaZvtx->SetBinError(10,2,0.18);
 trkEffVsEtaZvtx->SetBinError(11,2,0.0343214);
 trkEffVsEtaZvtx->SetBinError(12,2,0.0208967);
 trkEffVsEtaZvtx->SetBinError(13,2,0.0207949);
 trkEffVsEtaZvtx->SetBinError(14,2,0.0206701);
 trkEffVsEtaZvtx->SetBinError(15,2,0.0206316);
 trkEffVsEtaZvtx->SetBinError(16,2,0.0206412);
 trkEffVsEtaZvtx->SetBinError(17,2,0.020471);
 trkEffVsEtaZvtx->SetBinError(18,2,0.02038);
 trkEffVsEtaZvtx->SetBinError(19,2,0.0203338);
 trkEffVsEtaZvtx->SetBinError(20,2,0.0203653);
 trkEffVsEtaZvtx->SetBinError(21,2,0.0204299);
 trkEffVsEtaZvtx->SetBinError(22,2,0.0209174);
 
////////////////////////////////////////////////////
// ybin: -20.000000 to 0.000000
 trkEffVsEtaZvtx->SetBinContent(10,3,0.666667);
 trkEffVsEtaZvtx->SetBinContent(11,3,0.903219);
 trkEffVsEtaZvtx->SetBinContent(12,3,0.905972);
 trkEffVsEtaZvtx->SetBinContent(13,3,0.902831);
 trkEffVsEtaZvtx->SetBinContent(14,3,0.903056);
 trkEffVsEtaZvtx->SetBinContent(15,3,0.88611);
 trkEffVsEtaZvtx->SetBinContent(16,3,0.853034);
 trkEffVsEtaZvtx->SetBinContent(17,3,0.868828);
 trkEffVsEtaZvtx->SetBinContent(18,3,0.887741);
 trkEffVsEtaZvtx->SetBinContent(19,3,0.890287);
 trkEffVsEtaZvtx->SetBinContent(20,3,0.89431);
 trkEffVsEtaZvtx->SetBinContent(21,3,0.891437);
 trkEffVsEtaZvtx->SetBinContent(22,3,0.843911);
 trkEffVsEtaZvtx->SetBinError(10,3,0.272899);
 trkEffVsEtaZvtx->SetBinError(11,3,0.020446);
 trkEffVsEtaZvtx->SetBinError(12,3,0.0202144);
 trkEffVsEtaZvtx->SetBinError(13,3,0.0202072);
 trkEffVsEtaZvtx->SetBinError(14,3,0.0202047);
 trkEffVsEtaZvtx->SetBinError(15,3,0.0202298);
 trkEffVsEtaZvtx->SetBinError(16,3,0.0202896);
 trkEffVsEtaZvtx->SetBinError(17,3,0.0202637);
 trkEffVsEtaZvtx->SetBinError(18,3,0.0202306);
 trkEffVsEtaZvtx->SetBinError(19,3,0.0202332);
 trkEffVsEtaZvtx->SetBinError(20,3,0.0202383);
 trkEffVsEtaZvtx->SetBinError(21,3,0.0202826);
 trkEffVsEtaZvtx->SetBinError(22,3,0.0250189);
 trkEffVsEtaZvtx->SetBinError(24,3,0.02);

////////////////////////////////////////////////////
// ybin: 0.000000 to 20.000000
 trkEffVsEtaZvtx->SetBinContent(10,4,0.877151);
 trkEffVsEtaZvtx->SetBinContent(11,4,0.890572);
 trkEffVsEtaZvtx->SetBinContent(12,4,0.906692);
 trkEffVsEtaZvtx->SetBinContent(13,4,0.905525);
 trkEffVsEtaZvtx->SetBinContent(14,4,0.89675);
 trkEffVsEtaZvtx->SetBinContent(15,4,0.886593);
 trkEffVsEtaZvtx->SetBinContent(16,4,0.873388);
 trkEffVsEtaZvtx->SetBinContent(17,4,0.902561);
 trkEffVsEtaZvtx->SetBinContent(18,4,0.91567);
 trkEffVsEtaZvtx->SetBinContent(19,4,0.908899);
 trkEffVsEtaZvtx->SetBinContent(20,4,0.910087);
 trkEffVsEtaZvtx->SetBinContent(21,4,0.908767);
 trkEffVsEtaZvtx->SetBinContent(22,4,0.666667);
 trkEffVsEtaZvtx->SetBinError(10,4,0.0215395);
 trkEffVsEtaZvtx->SetBinError(11,4,0.0202495);
 trkEffVsEtaZvtx->SetBinError(12,4,0.0202026);
 trkEffVsEtaZvtx->SetBinError(13,4,0.0202031);
 trkEffVsEtaZvtx->SetBinError(14,4,0.0202068);
 trkEffVsEtaZvtx->SetBinError(15,4,0.0202275);
 trkEffVsEtaZvtx->SetBinError(16,4,0.0202513);
 trkEffVsEtaZvtx->SetBinError(17,4,0.020203);
 trkEffVsEtaZvtx->SetBinError(18,4,0.0201854);
 trkEffVsEtaZvtx->SetBinError(19,4,0.0201977);
 trkEffVsEtaZvtx->SetBinError(20,4,0.0202027);
 trkEffVsEtaZvtx->SetBinError(21,4,0.0207255);
 trkEffVsEtaZvtx->SetBinError(22,4,0.272899);

////////////////////////////////////////////////////
// ybin: 20.000000 to 40.000000
 trkEffVsEtaZvtx->SetBinContent(9,5,0.75);
 trkEffVsEtaZvtx->SetBinContent(10,5,0.881496);
 trkEffVsEtaZvtx->SetBinContent(11,5,0.907862);
 trkEffVsEtaZvtx->SetBinContent(12,5,0.906081);
 trkEffVsEtaZvtx->SetBinContent(13,5,0.89107);
 trkEffVsEtaZvtx->SetBinContent(14,5,0.889984);
 trkEffVsEtaZvtx->SetBinContent(15,5,0.847885);
 trkEffVsEtaZvtx->SetBinContent(16,5,0.802555);
 trkEffVsEtaZvtx->SetBinContent(17,5,0.798557);
 trkEffVsEtaZvtx->SetBinContent(18,5,0.793517);
 trkEffVsEtaZvtx->SetBinContent(19,5,0.780757);
 trkEffVsEtaZvtx->SetBinContent(20,5,0.846641);
 trkEffVsEtaZvtx->SetBinContent(21,5,0.75);
 trkEffVsEtaZvtx->SetBinError(9,5,0.0988686);
 trkEffVsEtaZvtx->SetBinError(10,5,0.0207056);
 trkEffVsEtaZvtx->SetBinError(11,5,0.0203999);
 trkEffVsEtaZvtx->SetBinError(12,5,0.0204078);
 trkEffVsEtaZvtx->SetBinError(13,5,0.020453);
 trkEffVsEtaZvtx->SetBinError(14,5,0.0204417);
 trkEffVsEtaZvtx->SetBinError(15,5,0.0205723);
 trkEffVsEtaZvtx->SetBinError(16,5,0.0207103);
 trkEffVsEtaZvtx->SetBinError(17,5,0.0207495);
 trkEffVsEtaZvtx->SetBinError(18,5,0.0207892);
 trkEffVsEtaZvtx->SetBinError(19,5,0.0208266);
 trkEffVsEtaZvtx->SetBinError(20,5,0.0211109);
 trkEffVsEtaZvtx->SetBinError(21,5,0.0906228);

////////////////////////////////////////////////////
// ybin: 40.000000 to 60.000000
 trkEffVsEtaZvtx->SetBinContent(9,6,0.603306);
 trkEffVsEtaZvtx->SetBinContent(10,6,0.778218);
 trkEffVsEtaZvtx->SetBinContent(11,6,0.728);
 trkEffVsEtaZvtx->SetBinContent(12,6,0.638211);
 trkEffVsEtaZvtx->SetBinContent(13,6,0.440501);
 trkEffVsEtaZvtx->SetBinContent(14,6,0.235887);
 trkEffVsEtaZvtx->SetBinContent(15,6,0.0220884);
 trkEffVsEtaZvtx->SetBinContent(16,6,0.0105708);
 trkEffVsEtaZvtx->SetBinContent(17,6,0.0277778);
 trkEffVsEtaZvtx->SetBinContent(18,6,0.026738);
 trkEffVsEtaZvtx->SetBinContent(19,6,0.0542169);
 trkEffVsEtaZvtx->SetBinContent(20,6,0.6875);
 trkEffVsEtaZvtx->SetBinContent(21,6,0.714286);
 trkEffVsEtaZvtx->SetBinError(9,6,0.0487639);
 trkEffVsEtaZvtx->SetBinError(10,6,0.0272355);
 trkEffVsEtaZvtx->SetBinError(11,6,0.028214);
 trkEffVsEtaZvtx->SetBinError(12,6,0.029484);
 trkEffVsEtaZvtx->SetBinError(13,6,0.0302412);
 trkEffVsEtaZvtx->SetBinError(14,6,0.0276296);
 trkEffVsEtaZvtx->SetBinError(15,6,0.0210565);
 trkEffVsEtaZvtx->SetBinError(16,6,0.0205454);
 trkEffVsEtaZvtx->SetBinError(17,6,0.0215061);
 trkEffVsEtaZvtx->SetBinError(18,6,0.0216698);
 trkEffVsEtaZvtx->SetBinError(19,6,0.0235468);
 trkEffVsEtaZvtx->SetBinError(20,6,0.117591);
 trkEffVsEtaZvtx->SetBinError(21,6,0.171914);
 trkEffVsEtaZvtx->SetBinError(22,6,0.02);

////////////////////////////////////////////////////
// ybin: over 60.000000
}
