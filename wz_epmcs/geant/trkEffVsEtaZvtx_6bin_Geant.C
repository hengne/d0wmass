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
 trkEffVsEtaZvtx->SetBinContent(18,1,0.204641);
 trkEffVsEtaZvtx->SetBinContent(19,1,0.402);
 trkEffVsEtaZvtx->SetBinContent(20,1,0.628283);
 trkEffVsEtaZvtx->SetBinContent(21,1,0.779762);
 trkEffVsEtaZvtx->SetBinContent(22,1,0.804819);
 trkEffVsEtaZvtx->SetBinContent(23,1,0.666667);
 trkEffVsEtaZvtx->SetBinError(10,1,0.02);
 trkEffVsEtaZvtx->SetBinError(11,1,0.137545);
 trkEffVsEtaZvtx->SetBinError(12,1,0.0605109);
 trkEffVsEtaZvtx->SetBinError(13,1,0.0237015);
 trkEffVsEtaZvtx->SetBinError(14,1,0.0213628);
 trkEffVsEtaZvtx->SetBinError(15,1,0.0210472);
 trkEffVsEtaZvtx->SetBinError(16,1,0.0218926);
 trkEffVsEtaZvtx->SetBinError(17,1,0.0214721);
 trkEffVsEtaZvtx->SetBinError(18,1,0.027265);
 trkEffVsEtaZvtx->SetBinError(19,1,0.0296781);
 trkEffVsEtaZvtx->SetBinError(20,1,0.0295263);
 trkEffVsEtaZvtx->SetBinError(21,1,0.0272166);
 trkEffVsEtaZvtx->SetBinError(22,1,0.0279019);
 trkEffVsEtaZvtx->SetBinError(23,1,0.0754388);
 
////////////////////////////////////////////////////
// ybin: -40.000000 to -20.000000
 trkEffVsEtaZvtx->SetBinContent(10,2,0.8);
 trkEffVsEtaZvtx->SetBinContent(11,2,0.888889);
 trkEffVsEtaZvtx->SetBinContent(12,2,0.808419);
 trkEffVsEtaZvtx->SetBinContent(13,2,0.774436);
 trkEffVsEtaZvtx->SetBinContent(14,2,0.805861);
 trkEffVsEtaZvtx->SetBinContent(15,2,0.818626);
 trkEffVsEtaZvtx->SetBinContent(16,2,0.81209);
 trkEffVsEtaZvtx->SetBinContent(17,2,0.873314);
 trkEffVsEtaZvtx->SetBinContent(18,2,0.897208);
 trkEffVsEtaZvtx->SetBinContent(19,2,0.909439);
 trkEffVsEtaZvtx->SetBinContent(20,2,0.903562);
 trkEffVsEtaZvtx->SetBinContent(21,2,0.884146);
 trkEffVsEtaZvtx->SetBinContent(22,2,0.861633);
 trkEffVsEtaZvtx->SetBinError(10,2,0.18);
 trkEffVsEtaZvtx->SetBinError(11,2,0.036256);
 trkEffVsEtaZvtx->SetBinError(12,2,0.0209533);
 trkEffVsEtaZvtx->SetBinError(13,2,0.0208249);
 trkEffVsEtaZvtx->SetBinError(14,2,0.020704);
 trkEffVsEtaZvtx->SetBinError(15,2,0.0206603);
 trkEffVsEtaZvtx->SetBinError(16,2,0.0206652);
 trkEffVsEtaZvtx->SetBinError(17,2,0.020498);
 trkEffVsEtaZvtx->SetBinError(18,2,0.0204137);
 trkEffVsEtaZvtx->SetBinError(19,2,0.0203725);
 trkEffVsEtaZvtx->SetBinError(20,2,0.0204086);
 trkEffVsEtaZvtx->SetBinError(21,2,0.0204975);
 trkEffVsEtaZvtx->SetBinError(22,2,0.0210493);
 
////////////////////////////////////////////////////
// ybin: -20.000000 to 0.000000
 trkEffVsEtaZvtx->SetBinContent(10,3,0.666667);
 trkEffVsEtaZvtx->SetBinContent(11,3,0.880314);
 trkEffVsEtaZvtx->SetBinContent(12,3,0.890891);
 trkEffVsEtaZvtx->SetBinContent(13,3,0.889153);
 trkEffVsEtaZvtx->SetBinContent(14,3,0.894499);
 trkEffVsEtaZvtx->SetBinContent(15,3,0.878321);
 trkEffVsEtaZvtx->SetBinContent(16,3,0.844844);
 trkEffVsEtaZvtx->SetBinContent(17,3,0.862773);
 trkEffVsEtaZvtx->SetBinContent(18,3,0.880108);
 trkEffVsEtaZvtx->SetBinContent(19,3,0.879239);
 trkEffVsEtaZvtx->SetBinContent(20,3,0.882341);
 trkEffVsEtaZvtx->SetBinContent(21,3,0.877441);
 trkEffVsEtaZvtx->SetBinContent(22,3,0.830189);
 trkEffVsEtaZvtx->SetBinError(10,3,0.272899);
 trkEffVsEtaZvtx->SetBinError(11,3,0.0205364);
 trkEffVsEtaZvtx->SetBinError(12,3,0.0202445);
 trkEffVsEtaZvtx->SetBinError(13,3,0.0202327);
 trkEffVsEtaZvtx->SetBinError(14,3,0.0202206);
 trkEffVsEtaZvtx->SetBinError(15,3,0.0202433);
 trkEffVsEtaZvtx->SetBinError(16,3,0.0203027);
 trkEffVsEtaZvtx->SetBinError(17,3,0.0202739);
 trkEffVsEtaZvtx->SetBinError(18,3,0.0202441);
 trkEffVsEtaZvtx->SetBinError(19,3,0.0202534);
 trkEffVsEtaZvtx->SetBinError(20,3,0.0202615);
 trkEffVsEtaZvtx->SetBinError(21,3,0.0203138);
 trkEffVsEtaZvtx->SetBinError(22,3,0.025334);
 trkEffVsEtaZvtx->SetBinError(24,3,0.02);
 
////////////////////////////////////////////////////
// ybin: 0.000000 to 20.000000
 trkEffVsEtaZvtx->SetBinContent(10,4,0.855786);
 trkEffVsEtaZvtx->SetBinContent(11,4,0.877177);
 trkEffVsEtaZvtx->SetBinContent(12,4,0.897737);
 trkEffVsEtaZvtx->SetBinContent(13,4,0.89436);
 trkEffVsEtaZvtx->SetBinContent(14,4,0.888759);
 trkEffVsEtaZvtx->SetBinContent(15,4,0.879676);
 trkEffVsEtaZvtx->SetBinContent(16,4,0.86616);
 trkEffVsEtaZvtx->SetBinContent(17,4,0.893838);
 trkEffVsEtaZvtx->SetBinContent(18,4,0.904091);
 trkEffVsEtaZvtx->SetBinContent(19,4,0.895747);
 trkEffVsEtaZvtx->SetBinContent(20,4,0.892064);
 trkEffVsEtaZvtx->SetBinContent(21,4,0.883464);
 trkEffVsEtaZvtx->SetBinContent(22,4,0.666667);
 trkEffVsEtaZvtx->SetBinError(10,4,0.0217542);
 trkEffVsEtaZvtx->SetBinError(11,4,0.0202756);
 trkEffVsEtaZvtx->SetBinError(12,4,0.0202198);
 trkEffVsEtaZvtx->SetBinError(13,4,0.0202241);
 trkEffVsEtaZvtx->SetBinError(14,4,0.0202207);
 trkEffVsEtaZvtx->SetBinError(15,4,0.0202394);
 trkEffVsEtaZvtx->SetBinError(16,4,0.0202634);
 trkEffVsEtaZvtx->SetBinError(17,4,0.0202189);
 trkEffVsEtaZvtx->SetBinError(18,4,0.0202081);
 trkEffVsEtaZvtx->SetBinError(19,4,0.0202229);
 trkEffVsEtaZvtx->SetBinError(20,4,0.0202383);
 trkEffVsEtaZvtx->SetBinError(21,4,0.0208972);
 trkEffVsEtaZvtx->SetBinError(22,4,0.272899);
 
////////////////////////////////////////////////////
// ybin: 20.000000 to 40.000000
 trkEffVsEtaZvtx->SetBinContent(9,5,0.75);
 trkEffVsEtaZvtx->SetBinContent(10,5,0.854001);
 trkEffVsEtaZvtx->SetBinContent(11,5,0.891636);
 trkEffVsEtaZvtx->SetBinContent(12,5,0.890201);
 trkEffVsEtaZvtx->SetBinContent(13,5,0.88031);
 trkEffVsEtaZvtx->SetBinContent(14,5,0.879037);
 trkEffVsEtaZvtx->SetBinContent(15,5,0.841044);
 trkEffVsEtaZvtx->SetBinContent(16,5,0.792336);
 trkEffVsEtaZvtx->SetBinContent(17,5,0.785836);
 trkEffVsEtaZvtx->SetBinContent(18,5,0.785462);
 trkEffVsEtaZvtx->SetBinContent(19,5,0.767547);
 trkEffVsEtaZvtx->SetBinContent(20,5,0.830813);
 trkEffVsEtaZvtx->SetBinContent(21,5,0.75);
 trkEffVsEtaZvtx->SetBinError(9,5,0.0988686);
 trkEffVsEtaZvtx->SetBinError(10,5,0.0208394);
 trkEffVsEtaZvtx->SetBinError(11,5,0.0204613);
 trkEffVsEtaZvtx->SetBinError(12,5,0.0204677);
 trkEffVsEtaZvtx->SetBinError(13,5,0.0204913);
 trkEffVsEtaZvtx->SetBinError(14,5,0.0204793);
 trkEffVsEtaZvtx->SetBinError(15,5,0.0205929);
 trkEffVsEtaZvtx->SetBinError(16,5,0.0207371);
 trkEffVsEtaZvtx->SetBinError(17,5,0.0207835);
 trkEffVsEtaZvtx->SetBinError(18,5,0.0208112);
 trkEffVsEtaZvtx->SetBinError(19,5,0.0208609);
 trkEffVsEtaZvtx->SetBinError(20,5,0.0212);
 trkEffVsEtaZvtx->SetBinError(21,5,0.0906228);
 
////////////////////////////////////////////////////
// ybin: 40.000000 to 60.000000
 trkEffVsEtaZvtx->SetBinContent(9,6,0.595041);
 trkEffVsEtaZvtx->SetBinContent(10,6,0.760396);
 trkEffVsEtaZvtx->SetBinContent(11,6,0.722);
 trkEffVsEtaZvtx->SetBinContent(12,6,0.634146);
 trkEffVsEtaZvtx->SetBinContent(13,6,0.436326);
 trkEffVsEtaZvtx->SetBinContent(14,6,0.231855);
 trkEffVsEtaZvtx->SetBinContent(15,6,0.0220884);
 trkEffVsEtaZvtx->SetBinContent(16,6,0.0105708);
 trkEffVsEtaZvtx->SetBinContent(17,6,0.0277778);
 trkEffVsEtaZvtx->SetBinContent(18,6,0.026738);
 trkEffVsEtaZvtx->SetBinContent(19,6,0.0512048);
 trkEffVsEtaZvtx->SetBinContent(20,6,0.6875);
 trkEffVsEtaZvtx->SetBinContent(21,6,0.714286);
 trkEffVsEtaZvtx->SetBinError(9,6,0.0489026);
 trkEffVsEtaZvtx->SetBinError(10,6,0.0275822);
 trkEffVsEtaZvtx->SetBinError(11,6,0.0283096);
 trkEffVsEtaZvtx->SetBinError(12,6,0.0295221);
 trkEffVsEtaZvtx->SetBinError(13,6,0.0302234);
 trkEffVsEtaZvtx->SetBinError(14,6,0.0275512);
 trkEffVsEtaZvtx->SetBinError(15,6,0.0210565);
 trkEffVsEtaZvtx->SetBinError(16,6,0.0205454);
 trkEffVsEtaZvtx->SetBinError(17,6,0.0215061);
 trkEffVsEtaZvtx->SetBinError(18,6,0.0216698);
 trkEffVsEtaZvtx->SetBinError(19,6,0.0233738);
 trkEffVsEtaZvtx->SetBinError(20,6,0.117591);
 trkEffVsEtaZvtx->SetBinError(21,6,0.171914);
 trkEffVsEtaZvtx->SetBinError(22,6,0.02);
 
////////////////////////////////////////////////////
// ybin: over 60.000000
}
