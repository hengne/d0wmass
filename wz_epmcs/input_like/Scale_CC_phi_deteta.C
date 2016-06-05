{
const int n_Scale_CC_phi_deteta_xbins = 32;
float Scale_CC_phi_deteta_xbins[n_Scale_CC_phi_deteta_xbins+1] = {0.000000 ,0.196350 ,0.392699 ,0.589049 ,0.785398 ,0.981748 ,1.178097 ,1.374447 ,1.570796 ,1.767146 ,1.963495 ,2.159845 ,2.356194 ,2.552544 ,2.748894 ,2.945243 ,3.141593 ,3.337942 ,3.534292 ,3.730641 ,3.926991 ,4.123340 ,4.319690 ,4.516039 ,4.712389 ,4.908739 ,5.105088 ,5.301438 ,5.497787 ,5.694137 ,5.890486 ,6.086836 ,6.283185  };

const int n_Scale_CC_phi_deteta_ybins = 2;
float Scale_CC_phi_deteta_ybins[n_Scale_CC_phi_deteta_ybins+1] = {-1.300000 ,0.000000 ,1.300000  };

TH2F *Scale_CC_phi_deteta = new TH2F("Scale_CC_phi_deteta","Relative energy scale vs phi and deteta", n_Scale_CC_phi_deteta_xbins, Scale_CC_phi_deteta_xbins, n_Scale_CC_phi_deteta_ybins, Scale_CC_phi_deteta_ybins);

////////////////////////////////////////////////////
// ybin: under -1.300000

////////////////////////////////////////////////////
// ybin: -1.300000 to 0.000000

// xbin: 0.000000 to 0.196350
Scale_CC_phi_deteta->SetBinContent(1,1,1.021100);
Scale_CC_phi_deteta->SetBinError(1,1,1.010495);

// xbin: 0.196350 to 0.392699
Scale_CC_phi_deteta->SetBinContent(2,1,1.018402);
Scale_CC_phi_deteta->SetBinError(2,1,1.009159);

// xbin: 0.392699 to 0.589049
Scale_CC_phi_deteta->SetBinContent(3,1,1.000776);
Scale_CC_phi_deteta->SetBinError(3,1,1.000388);

// xbin: 0.589049 to 0.785398
Scale_CC_phi_deteta->SetBinContent(4,1,1.001592);
Scale_CC_phi_deteta->SetBinError(4,1,1.000795);

// xbin: 0.785398 to 0.981748
Scale_CC_phi_deteta->SetBinContent(5,1,0.999469);
Scale_CC_phi_deteta->SetBinError(5,1,0.999735);

// xbin: 0.981748 to 1.178097
Scale_CC_phi_deteta->SetBinContent(6,1,1.000765);
Scale_CC_phi_deteta->SetBinError(6,1,1.000382);

// xbin: 1.178097 to 1.374447
Scale_CC_phi_deteta->SetBinContent(7,1,1.035377);
Scale_CC_phi_deteta->SetBinError(7,1,1.017535);

// xbin: 1.374447 to 1.570796
Scale_CC_phi_deteta->SetBinContent(8,1,0.961995);
Scale_CC_phi_deteta->SetBinError(8,1,0.980814);

// xbin: 1.570796 to 1.767146
Scale_CC_phi_deteta->SetBinContent(9,1,0.999283);
Scale_CC_phi_deteta->SetBinError(9,1,0.999642);

// xbin: 1.767146 to 1.963495
Scale_CC_phi_deteta->SetBinContent(10,1,0.998529);
Scale_CC_phi_deteta->SetBinError(10,1,0.999264);

// xbin: 1.963495 to 2.159845
Scale_CC_phi_deteta->SetBinContent(11,1,1.019229);
Scale_CC_phi_deteta->SetBinError(11,1,1.009569);

// xbin: 2.159845 to 2.356194
Scale_CC_phi_deteta->SetBinContent(12,1,1.018438);
Scale_CC_phi_deteta->SetBinError(12,1,1.009177);

// xbin: 2.356194 to 2.552544
Scale_CC_phi_deteta->SetBinContent(13,1,1.002800);
Scale_CC_phi_deteta->SetBinError(13,1,1.001399);

// xbin: 2.552544 to 2.748894
Scale_CC_phi_deteta->SetBinContent(14,1,0.984308);
Scale_CC_phi_deteta->SetBinError(14,1,0.992123);

// xbin: 2.748894 to 2.945243
Scale_CC_phi_deteta->SetBinContent(15,1,0.979627);
Scale_CC_phi_deteta->SetBinError(15,1,0.989761);

// xbin: 2.945243 to 3.141593
Scale_CC_phi_deteta->SetBinContent(16,1,1.002636);
Scale_CC_phi_deteta->SetBinError(16,1,1.001317);

// xbin: 3.141593 to 3.337942
Scale_CC_phi_deteta->SetBinContent(17,1,0.939728);
Scale_CC_phi_deteta->SetBinError(17,1,0.969396);

// xbin: 3.337942 to 3.534292
Scale_CC_phi_deteta->SetBinContent(18,1,1.014657);
Scale_CC_phi_deteta->SetBinError(18,1,1.007302);

// xbin: 3.534292 to 3.730641
Scale_CC_phi_deteta->SetBinContent(19,1,0.981126);
Scale_CC_phi_deteta->SetBinError(19,1,0.990518);

// xbin: 3.730641 to 3.926991
Scale_CC_phi_deteta->SetBinContent(20,1,1.001266);
Scale_CC_phi_deteta->SetBinError(20,1,1.000633);

// xbin: 3.926991 to 4.123340
Scale_CC_phi_deteta->SetBinContent(21,1,0.979600);
Scale_CC_phi_deteta->SetBinError(21,1,0.989747);

// xbin: 4.123340 to 4.319690
Scale_CC_phi_deteta->SetBinContent(22,1,0.999989);
Scale_CC_phi_deteta->SetBinError(22,1,0.999994);

// xbin: 4.319690 to 4.516039
Scale_CC_phi_deteta->SetBinContent(23,1,0.999584);
Scale_CC_phi_deteta->SetBinError(23,1,0.999792);

// xbin: 4.516039 to 4.712389
Scale_CC_phi_deteta->SetBinContent(24,1,0.982492);
Scale_CC_phi_deteta->SetBinError(24,1,0.991208);

// xbin: 4.712389 to 4.908739
Scale_CC_phi_deteta->SetBinContent(25,1,0.999730);
Scale_CC_phi_deteta->SetBinError(25,1,0.999865);

// xbin: 4.908739 to 5.105088
Scale_CC_phi_deteta->SetBinContent(26,1,0.978214);
Scale_CC_phi_deteta->SetBinError(26,1,0.989047);

// xbin: 5.105088 to 5.301438
Scale_CC_phi_deteta->SetBinContent(27,1,0.981428);
Scale_CC_phi_deteta->SetBinError(27,1,0.990670);

// xbin: 5.301438 to 5.497787
Scale_CC_phi_deteta->SetBinContent(28,1,1.029009);
Scale_CC_phi_deteta->SetBinError(28,1,1.014401);

// xbin: 5.497787 to 5.694137
Scale_CC_phi_deteta->SetBinContent(29,1,1.001307);
Scale_CC_phi_deteta->SetBinError(29,1,1.000654);

// xbin: 5.694137 to 5.890486
Scale_CC_phi_deteta->SetBinContent(30,1,0.984232);
Scale_CC_phi_deteta->SetBinError(30,1,0.992085);

// xbin: 5.890486 to 6.086836
Scale_CC_phi_deteta->SetBinContent(31,1,1.039175);
Scale_CC_phi_deteta->SetBinError(31,1,1.019399);

// xbin: 6.086836 to 6.283185
Scale_CC_phi_deteta->SetBinContent(32,1,1.036051);
Scale_CC_phi_deteta->SetBinError(32,1,1.017866);

////////////////////////////////////////////////////
// ybin: 0.000000 to 1.300000

// xbin: 0.000000 to 0.196350
Scale_CC_phi_deteta->SetBinContent(1,2,1.015844);
Scale_CC_phi_deteta->SetBinError(1,2,1.007891);

// xbin: 0.196350 to 0.392699
Scale_CC_phi_deteta->SetBinContent(2,2,0.999909);
Scale_CC_phi_deteta->SetBinError(2,2,0.999955);

// xbin: 0.392699 to 0.589049
Scale_CC_phi_deteta->SetBinContent(3,2,1.019166);
Scale_CC_phi_deteta->SetBinError(3,2,1.009537);

// xbin: 0.589049 to 0.785398
Scale_CC_phi_deteta->SetBinContent(4,2,1.000818);
Scale_CC_phi_deteta->SetBinError(4,2,1.000409);

// xbin: 0.785398 to 0.981748
Scale_CC_phi_deteta->SetBinContent(5,2,1.016706);
Scale_CC_phi_deteta->SetBinError(5,2,1.008319);

// xbin: 0.981748 to 1.178097
Scale_CC_phi_deteta->SetBinContent(6,2,0.985722);
Scale_CC_phi_deteta->SetBinError(6,2,0.992835);

// xbin: 1.178097 to 1.374447
Scale_CC_phi_deteta->SetBinContent(7,2,1.019633);
Scale_CC_phi_deteta->SetBinError(7,2,1.009769);

// xbin: 1.374447 to 1.570796
Scale_CC_phi_deteta->SetBinContent(8,2,0.961402);
Scale_CC_phi_deteta->SetBinError(8,2,0.980511);

// xbin: 1.570796 to 1.767146
Scale_CC_phi_deteta->SetBinContent(9,2,1.009775);
Scale_CC_phi_deteta->SetBinError(9,2,1.004875);

// xbin: 1.767146 to 1.963495
Scale_CC_phi_deteta->SetBinContent(10,2,0.984182);
Scale_CC_phi_deteta->SetBinError(10,2,0.992059);

// xbin: 1.963495 to 2.159845
Scale_CC_phi_deteta->SetBinContent(11,2,1.006395);
Scale_CC_phi_deteta->SetBinError(11,2,1.003193);

// xbin: 2.159845 to 2.356194
Scale_CC_phi_deteta->SetBinContent(12,2,0.998024);
Scale_CC_phi_deteta->SetBinError(12,2,0.999012);

// xbin: 2.356194 to 2.552544
Scale_CC_phi_deteta->SetBinContent(13,2,1.017427);
Scale_CC_phi_deteta->SetBinError(13,2,1.008676);

// xbin: 2.552544 to 2.748894
Scale_CC_phi_deteta->SetBinContent(14,2,0.985845);
Scale_CC_phi_deteta->SetBinError(14,2,0.992897);

// xbin: 2.748894 to 2.945243
Scale_CC_phi_deteta->SetBinContent(15,2,0.997294);
Scale_CC_phi_deteta->SetBinError(15,2,0.998646);

// xbin: 2.945243 to 3.141593
Scale_CC_phi_deteta->SetBinContent(16,2,0.979494);
Scale_CC_phi_deteta->SetBinError(16,2,0.989694);

// xbin: 3.141593 to 3.337942
Scale_CC_phi_deteta->SetBinContent(17,2,0.920290);
Scale_CC_phi_deteta->SetBinError(17,2,0.959318);

// xbin: 3.337942 to 3.534292
Scale_CC_phi_deteta->SetBinContent(18,2,0.996932);
Scale_CC_phi_deteta->SetBinError(18,2,0.998465);

// xbin: 3.534292 to 3.730641
Scale_CC_phi_deteta->SetBinContent(19,2,1.000816);
Scale_CC_phi_deteta->SetBinError(19,2,1.000408);

// xbin: 3.730641 to 3.926991
Scale_CC_phi_deteta->SetBinContent(20,2,0.986309);
Scale_CC_phi_deteta->SetBinError(20,2,0.993131);

// xbin: 3.926991 to 4.123340
Scale_CC_phi_deteta->SetBinContent(21,2,0.977489);
Scale_CC_phi_deteta->SetBinError(21,2,0.988680);

// xbin: 4.123340 to 4.319690
Scale_CC_phi_deteta->SetBinContent(22,2,0.981553);
Scale_CC_phi_deteta->SetBinError(22,2,0.990734);

// xbin: 4.319690 to 4.516039
Scale_CC_phi_deteta->SetBinContent(23,2,0.982624);
Scale_CC_phi_deteta->SetBinError(23,2,0.991274);

// xbin: 4.516039 to 4.712389
Scale_CC_phi_deteta->SetBinContent(24,2,0.981054);
Scale_CC_phi_deteta->SetBinError(24,2,0.990482);

// xbin: 4.712389 to 4.908739
Scale_CC_phi_deteta->SetBinContent(25,2,1.018259);
Scale_CC_phi_deteta->SetBinError(25,2,1.009088);

// xbin: 4.908739 to 5.105088
Scale_CC_phi_deteta->SetBinContent(26,2,0.976499);
Scale_CC_phi_deteta->SetBinError(26,2,0.988180);

// xbin: 5.105088 to 5.301438
Scale_CC_phi_deteta->SetBinContent(27,2,1.018676);
Scale_CC_phi_deteta->SetBinError(27,2,1.009295);

// xbin: 5.301438 to 5.497787
Scale_CC_phi_deteta->SetBinContent(28,2,1.031803);
Scale_CC_phi_deteta->SetBinError(28,2,1.015777);

// xbin: 5.497787 to 5.694137
Scale_CC_phi_deteta->SetBinContent(29,2,1.018227);
Scale_CC_phi_deteta->SetBinError(29,2,1.009072);

// xbin: 5.694137 to 5.890486
Scale_CC_phi_deteta->SetBinContent(30,2,1.002651);
Scale_CC_phi_deteta->SetBinError(30,2,1.001325);

// xbin: 5.890486 to 6.086836
Scale_CC_phi_deteta->SetBinContent(31,2,1.040099);
Scale_CC_phi_deteta->SetBinError(31,2,1.019853);

// xbin: 6.086836 to 6.283185
Scale_CC_phi_deteta->SetBinContent(32,2,1.021696);
Scale_CC_phi_deteta->SetBinError(32,2,1.010790);

////////////////////////////////////////////////////
// ybin: over 1.300000
}
