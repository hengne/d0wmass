{
const int n_Upara_shift_CC_phi_deteta_xbins = 32;
float Upara_shift_CC_phi_deteta_xbins[n_Upara_shift_CC_phi_deteta_xbins+1] = {0.000000 ,0.196350 ,0.392699 ,0.589049 ,0.785398 ,0.981748 ,1.178097 ,1.374447 ,1.570796 ,1.767146 ,1.963495 ,2.159845 ,2.356194 ,2.552544 ,2.748894 ,2.945243 ,3.141593 ,3.337942 ,3.534292 ,3.730641 ,3.926991 ,4.123340 ,4.319690 ,4.516039 ,4.712389 ,4.908739 ,5.105088 ,5.301438 ,5.497787 ,5.694137 ,5.890486 ,6.086836 ,6.283185  };

const int n_Upara_shift_CC_phi_deteta_ybins = 2;
float Upara_shift_CC_phi_deteta_ybins[n_Upara_shift_CC_phi_deteta_ybins+1] = {-1.300000 ,0.000000 ,1.300000  };

TH2F *Upara_shift_CC_phi_deteta = new TH2F("Upara_shift_CC_phi_deteta","Upara shift vs phi and deteta", n_Upara_shift_CC_phi_deteta_xbins, Upara_shift_CC_phi_deteta_xbins, n_Upara_shift_CC_phi_deteta_ybins, Upara_shift_CC_phi_deteta_ybins);

////////////////////////////////////////////////////
// ybin: under -1.300000

////////////////////////////////////////////////////
// ybin: -1.300000 to 0.000000

// xbin: 0.000000 to 0.196350
Upara_shift_CC_phi_deteta->SetBinContent(1,1,-0.116863);
Upara_shift_CC_phi_deteta->SetBinError(1,1,0.341852);

// xbin: 0.196350 to 0.392699
Upara_shift_CC_phi_deteta->SetBinContent(2,1,0.222423);
Upara_shift_CC_phi_deteta->SetBinError(2,1,0.471618);

// xbin: 0.392699 to 0.589049
Upara_shift_CC_phi_deteta->SetBinContent(3,1,0.067478);
Upara_shift_CC_phi_deteta->SetBinError(3,1,0.259766);

// xbin: 0.589049 to 0.785398
Upara_shift_CC_phi_deteta->SetBinContent(4,1,0.424209);
Upara_shift_CC_phi_deteta->SetBinError(4,1,0.651313);

// xbin: 0.785398 to 0.981748
Upara_shift_CC_phi_deteta->SetBinContent(5,1,0.173551);
Upara_shift_CC_phi_deteta->SetBinError(5,1,0.416595);

// xbin: 0.981748 to 1.178097
Upara_shift_CC_phi_deteta->SetBinContent(6,1,0.340280);
Upara_shift_CC_phi_deteta->SetBinError(6,1,0.583336);

// xbin: 1.178097 to 1.374447
Upara_shift_CC_phi_deteta->SetBinContent(7,1,-0.029958);
Upara_shift_CC_phi_deteta->SetBinError(7,1,0.173083);

// xbin: 1.374447 to 1.570796
Upara_shift_CC_phi_deteta->SetBinContent(8,1,0.003376);
Upara_shift_CC_phi_deteta->SetBinError(8,1,0.058099);

// xbin: 1.570796 to 1.767146
Upara_shift_CC_phi_deteta->SetBinContent(9,1,0.058931);
Upara_shift_CC_phi_deteta->SetBinError(9,1,0.242757);

// xbin: 1.767146 to 1.963495
Upara_shift_CC_phi_deteta->SetBinContent(10,1,-0.225360);
Upara_shift_CC_phi_deteta->SetBinError(10,1,0.474721);

// xbin: 1.963495 to 2.159845
Upara_shift_CC_phi_deteta->SetBinContent(11,1,-0.195434);
Upara_shift_CC_phi_deteta->SetBinError(11,1,0.442079);

// xbin: 2.159845 to 2.356194
Upara_shift_CC_phi_deteta->SetBinContent(12,1,-0.186368);
Upara_shift_CC_phi_deteta->SetBinError(12,1,0.431704);

// xbin: 2.356194 to 2.552544
Upara_shift_CC_phi_deteta->SetBinContent(13,1,-0.068053);
Upara_shift_CC_phi_deteta->SetBinError(13,1,0.260870);

// xbin: 2.552544 to 2.748894
Upara_shift_CC_phi_deteta->SetBinContent(14,1,-0.163291);
Upara_shift_CC_phi_deteta->SetBinError(14,1,0.404093);

// xbin: 2.748894 to 2.945243
Upara_shift_CC_phi_deteta->SetBinContent(15,1,-0.095291);
Upara_shift_CC_phi_deteta->SetBinError(15,1,0.308693);

// xbin: 2.945243 to 3.141593
Upara_shift_CC_phi_deteta->SetBinContent(16,1,-0.110910);
Upara_shift_CC_phi_deteta->SetBinError(16,1,0.333032);

// xbin: 3.141593 to 3.337942
Upara_shift_CC_phi_deteta->SetBinContent(17,1,0.175995);
Upara_shift_CC_phi_deteta->SetBinError(17,1,0.419517);

// xbin: 3.337942 to 3.534292
Upara_shift_CC_phi_deteta->SetBinContent(18,1,-0.413291);
Upara_shift_CC_phi_deteta->SetBinError(18,1,0.642877);

// xbin: 3.534292 to 3.730641
Upara_shift_CC_phi_deteta->SetBinContent(19,1,-0.279291);
Upara_shift_CC_phi_deteta->SetBinError(19,1,0.528480);

// xbin: 3.730641 to 3.926991
Upara_shift_CC_phi_deteta->SetBinContent(20,1,-0.291862);
Upara_shift_CC_phi_deteta->SetBinError(20,1,0.540243);

// xbin: 3.926991 to 4.123340
Upara_shift_CC_phi_deteta->SetBinContent(21,1,-0.384913);
Upara_shift_CC_phi_deteta->SetBinError(21,1,0.620413);

// xbin: 4.123340 to 4.319690
Upara_shift_CC_phi_deteta->SetBinContent(22,1,-0.496624);
Upara_shift_CC_phi_deteta->SetBinError(22,1,0.704716);

// xbin: 4.319690 to 4.516039
Upara_shift_CC_phi_deteta->SetBinContent(23,1,-0.321624);
Upara_shift_CC_phi_deteta->SetBinError(23,1,0.567119);

// xbin: 4.516039 to 4.712389
Upara_shift_CC_phi_deteta->SetBinContent(24,1,-0.046624);
Upara_shift_CC_phi_deteta->SetBinError(24,1,0.215927);

// xbin: 4.712389 to 4.908739
Upara_shift_CC_phi_deteta->SetBinContent(25,1,-0.063291);
Upara_shift_CC_phi_deteta->SetBinError(25,1,0.251577);

// xbin: 4.908739 to 5.105088
Upara_shift_CC_phi_deteta->SetBinContent(26,1,0.203376);
Upara_shift_CC_phi_deteta->SetBinError(26,1,0.450972);

// xbin: 5.105088 to 5.301438
Upara_shift_CC_phi_deteta->SetBinContent(27,1,-0.063291);
Upara_shift_CC_phi_deteta->SetBinError(27,1,0.251577);

// xbin: 5.301438 to 5.497787
Upara_shift_CC_phi_deteta->SetBinContent(28,1,-0.153291);
Upara_shift_CC_phi_deteta->SetBinError(28,1,0.391524);

// xbin: 5.497787 to 5.694137
Upara_shift_CC_phi_deteta->SetBinContent(29,1,0.006274);
Upara_shift_CC_phi_deteta->SetBinError(29,1,0.079210);

// xbin: 5.694137 to 5.890486
Upara_shift_CC_phi_deteta->SetBinContent(30,1,-0.463291);
Upara_shift_CC_phi_deteta->SetBinError(30,1,0.680655);

// xbin: 5.890486 to 6.086836
Upara_shift_CC_phi_deteta->SetBinContent(31,1,-0.066416);
Upara_shift_CC_phi_deteta->SetBinError(31,1,0.257713);

// xbin: 6.086836 to 6.283185
Upara_shift_CC_phi_deteta->SetBinContent(32,1,-0.260261);
Upara_shift_CC_phi_deteta->SetBinError(32,1,0.510158);

////////////////////////////////////////////////////
// ybin: 0.000000 to 1.300000

// xbin: 0.000000 to 0.196350
Upara_shift_CC_phi_deteta->SetBinContent(1,2,-0.409720);
Upara_shift_CC_phi_deteta->SetBinError(1,2,0.640094);

// xbin: 0.196350 to 0.392699
Upara_shift_CC_phi_deteta->SetBinContent(2,2,-0.532257);
Upara_shift_CC_phi_deteta->SetBinError(2,2,0.729559);

// xbin: 0.392699 to 0.589049
Upara_shift_CC_phi_deteta->SetBinContent(3,2,-0.433291);
Upara_shift_CC_phi_deteta->SetBinError(3,2,0.658248);

// xbin: 0.589049 to 0.785398
Upara_shift_CC_phi_deteta->SetBinContent(4,2,-0.203291);
Upara_shift_CC_phi_deteta->SetBinError(4,2,0.450878);

// xbin: 0.785398 to 0.981748
Upara_shift_CC_phi_deteta->SetBinContent(5,2,-0.501222);
Upara_shift_CC_phi_deteta->SetBinError(5,2,0.707970);

// xbin: 0.981748 to 1.178097
Upara_shift_CC_phi_deteta->SetBinContent(6,2,-0.051170);
Upara_shift_CC_phi_deteta->SetBinError(6,2,0.226208);

// xbin: 1.178097 to 1.374447
Upara_shift_CC_phi_deteta->SetBinContent(7,2,-0.157409);
Upara_shift_CC_phi_deteta->SetBinError(7,2,0.396748);

// xbin: 1.374447 to 1.570796
Upara_shift_CC_phi_deteta->SetBinContent(8,2,-0.063291);
Upara_shift_CC_phi_deteta->SetBinError(8,2,0.251577);

// xbin: 1.570796 to 1.767146
Upara_shift_CC_phi_deteta->SetBinContent(9,2,1.067743);
Upara_shift_CC_phi_deteta->SetBinError(9,2,1.033317);

// xbin: 1.767146 to 1.963495
Upara_shift_CC_phi_deteta->SetBinContent(10,2,0.825280);
Upara_shift_CC_phi_deteta->SetBinError(10,2,0.908449);

// xbin: 1.963495 to 2.159845
Upara_shift_CC_phi_deteta->SetBinContent(11,2,0.825171);
Upara_shift_CC_phi_deteta->SetBinError(11,2,0.908389);

// xbin: 2.159845 to 2.356194
Upara_shift_CC_phi_deteta->SetBinContent(12,2,0.839650);
Upara_shift_CC_phi_deteta->SetBinError(12,2,0.916324);

// xbin: 2.356194 to 2.552544
Upara_shift_CC_phi_deteta->SetBinContent(13,2,0.593852);
Upara_shift_CC_phi_deteta->SetBinError(13,2,0.770618);

// xbin: 2.552544 to 2.748894
Upara_shift_CC_phi_deteta->SetBinContent(14,2,0.755628);
Upara_shift_CC_phi_deteta->SetBinError(14,2,0.869269);

// xbin: 2.748894 to 2.945243
Upara_shift_CC_phi_deteta->SetBinContent(15,2,0.729566);
Upara_shift_CC_phi_deteta->SetBinError(15,2,0.854146);

// xbin: 2.945243 to 3.141593
Upara_shift_CC_phi_deteta->SetBinContent(16,2,0.545042);
Upara_shift_CC_phi_deteta->SetBinError(16,2,0.738270);

// xbin: 3.141593 to 3.337942
Upara_shift_CC_phi_deteta->SetBinContent(17,2,0.508138);
Upara_shift_CC_phi_deteta->SetBinError(17,2,0.712838);

// xbin: 3.337942 to 3.534292
Upara_shift_CC_phi_deteta->SetBinContent(18,2,0.516709);
Upara_shift_CC_phi_deteta->SetBinError(18,2,0.718825);

// xbin: 3.534292 to 3.730641
Upara_shift_CC_phi_deteta->SetBinContent(19,2,0.536709);
Upara_shift_CC_phi_deteta->SetBinError(19,2,0.732604);

// xbin: 3.730641 to 3.926991
Upara_shift_CC_phi_deteta->SetBinContent(20,2,0.472606);
Upara_shift_CC_phi_deteta->SetBinError(20,2,0.687464);

// xbin: 3.926991 to 4.123340
Upara_shift_CC_phi_deteta->SetBinContent(21,2,0.572423);
Upara_shift_CC_phi_deteta->SetBinError(21,2,0.756587);

// xbin: 4.123340 to 4.319690
Upara_shift_CC_phi_deteta->SetBinContent(22,2,0.460709);
Upara_shift_CC_phi_deteta->SetBinError(22,2,0.678755);

// xbin: 4.319690 to 4.516039
Upara_shift_CC_phi_deteta->SetBinContent(23,2,0.306274);
Upara_shift_CC_phi_deteta->SetBinError(23,2,0.553420);

// xbin: 4.516039 to 4.712389
Upara_shift_CC_phi_deteta->SetBinContent(24,2,0.332709);
Upara_shift_CC_phi_deteta->SetBinError(24,2,0.576809);

// xbin: 4.712389 to 4.908739
Upara_shift_CC_phi_deteta->SetBinContent(25,2,-0.757735);
Upara_shift_CC_phi_deteta->SetBinError(25,2,0.870480);

// xbin: 4.908739 to 5.105088
Upara_shift_CC_phi_deteta->SetBinContent(26,2,-0.624402);
Upara_shift_CC_phi_deteta->SetBinError(26,2,0.790191);

// xbin: 5.105088 to 5.301438
Upara_shift_CC_phi_deteta->SetBinContent(27,2,-0.541069);
Upara_shift_CC_phi_deteta->SetBinError(27,2,0.735574);

// xbin: 5.301438 to 5.497787
Upara_shift_CC_phi_deteta->SetBinContent(28,2,-1.002421);
Upara_shift_CC_phi_deteta->SetBinError(28,2,1.001210);

// xbin: 5.497787 to 5.694137
Upara_shift_CC_phi_deteta->SetBinContent(29,2,-0.825791);
Upara_shift_CC_phi_deteta->SetBinError(29,2,0.908730);

// xbin: 5.694137 to 5.890486
Upara_shift_CC_phi_deteta->SetBinContent(30,2,-0.866995);
Upara_shift_CC_phi_deteta->SetBinError(30,2,0.931125);

// xbin: 5.890486 to 6.086836
Upara_shift_CC_phi_deteta->SetBinContent(31,2,-0.725791);
Upara_shift_CC_phi_deteta->SetBinError(31,2,0.851934);

// xbin: 6.086836 to 6.283185
Upara_shift_CC_phi_deteta->SetBinContent(32,2,-0.439958);
Upara_shift_CC_phi_deteta->SetBinError(32,2,0.663293);

////////////////////////////////////////////////////
// ybin: over 1.300000
}
