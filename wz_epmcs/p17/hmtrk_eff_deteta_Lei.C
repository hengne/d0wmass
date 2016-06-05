{
const int n_idEffDetEta_xbins = 52;
float idEffDetEta_xbins[n_idEffDetEta_xbins+1] = { -3.2 ,-3.0 ,-2.8, -2.6,-2.4,-2.3,-2.2,-2.1,-2.0,-1.9,-1.8,-1.7,-1.6 ,-1.50 ,-1.4 ,-1.30 ,-1.200000 ,-1.1,-0.9, -0.7 ,-0.6 ,-0.5 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.400000 ,0.500000 ,0.600000 ,0.700000 ,0.900000 ,1.10000 ,1.20000 ,1.3,1.4,1.5,1.600000 ,1.7,1.800000 ,1.9,2.0,2.1,2.2,2.30000 ,2.4,2.6,2.8,3.0,3.2 };

TH1F *idEffDetEta = new TH1F("idEffDetEta","hmtrk efficiency vs deteta, pt > 25GeV", n_idEffDetEta_xbins, idEffDetEta_xbins);

idEffDetEta->SetBinContent(2,0.666667);
idEffDetEta->SetBinContent(3,0.883333);
idEffDetEta->SetBinContent(4,0.956303);
idEffDetEta->SetBinContent(5,0.945283);
idEffDetEta->SetBinContent(6,0.966102);
idEffDetEta->SetBinContent(7,0.965847);
idEffDetEta->SetBinContent(8,0.959821);
idEffDetEta->SetBinContent(9,0.968391);
idEffDetEta->SetBinContent(10,0.969628);
idEffDetEta->SetBinContent(11,0.963578);
idEffDetEta->SetBinContent(12,0.967693);
idEffDetEta->SetBinContent(13,0.973009);


idEffDetEta->SetBinContent(18,0.959618);
idEffDetEta->SetBinContent(19,0.97091);
idEffDetEta->SetBinContent(20,0.968218);
idEffDetEta->SetBinContent(21,0.973206);
idEffDetEta->SetBinContent(22,0.972899);
idEffDetEta->SetBinContent(23,0.976283);
idEffDetEta->SetBinContent(24,0.973489);
idEffDetEta->SetBinContent(25,0.971466);
idEffDetEta->SetBinContent(26,0.97088);
idEffDetEta->SetBinContent(27,0.971028);
idEffDetEta->SetBinContent(28,0.971376);
idEffDetEta->SetBinContent(29,0.971193);
idEffDetEta->SetBinContent(30,0.976474);
idEffDetEta->SetBinContent(31,0.975772);
idEffDetEta->SetBinContent(32,0.969246);
idEffDetEta->SetBinContent(33,0.972878);
idEffDetEta->SetBinContent(34,0.970856);
idEffDetEta->SetBinContent(35,0.970569);

idEffDetEta->SetBinContent(40,0.966538);
idEffDetEta->SetBinContent(41,0.97555);
idEffDetEta->SetBinContent(42,0.97497);
idEffDetEta->SetBinContent(43,0.978708);
idEffDetEta->SetBinContent(44,0.97533);
idEffDetEta->SetBinContent(45,0.967975);
idEffDetEta->SetBinContent(46,0.966507);
idEffDetEta->SetBinContent(47,0.97027);
idEffDetEta->SetBinContent(48,0.969106);
idEffDetEta->SetBinContent(49,0.965847);
idEffDetEta->SetBinContent(50,0.968085);
idEffDetEta->SetBinContent(51,0.96875);
idEffDetEta->SetBinContent(52,1);


idEffDetEta->SetBinError(2,0.157135);
idEffDetEta->SetBinError(3,0.0414438);
idEffDetEta->SetBinError(4,0.00838045);
idEffDetEta->SetBinError(5,0.0098788);
idEffDetEta->SetBinError(6,0.00710359);
idEffDetEta->SetBinError(7,0.00671295);
idEffDetEta->SetBinError(8,0.00656052);
idEffDetEta->SetBinError(9,0.00541479);
idEffDetEta->SetBinError(10,0.00472875);
idEffDetEta->SetBinError(11,0.00473551);
idEffDetEta->SetBinError(12,0.0039726);
idEffDetEta->SetBinError(13,0.00343712);


idEffDetEta->SetBinError(18,0.00304297);
idEffDetEta->SetBinError(19,0.00217929);
idEffDetEta->SetBinError(20,0.00314301);
idEffDetEta->SetBinError(21,0.00288406);
idEffDetEta->SetBinError(22,0.00283352);
idEffDetEta->SetBinError(23,0.00274272);
idEffDetEta->SetBinError(24,0.00288863);
idEffDetEta->SetBinError(25,0.00299806);
idEffDetEta->SetBinError(26,0.00295946);
idEffDetEta->SetBinError(27,0.00296041);
idEffDetEta->SetBinError(28,0.0029254);
idEffDetEta->SetBinError(29,0.00297594);
idEffDetEta->SetBinError(30,0.00268437);
idEffDetEta->SetBinError(31,0.00267573);
idEffDetEta->SetBinError(32,0.00313962);
idEffDetEta->SetBinError(33,0.00290161);
idEffDetEta->SetBinError(34,0.00214632);
idEffDetEta->SetBinError(35,0.00251418);


idEffDetEta->SetBinError(40,0.0037249);
idEffDetEta->SetBinError(41,0.0034152);
idEffDetEta->SetBinError(42,0.00381354);
idEffDetEta->SetBinError(43,0.00384571);
idEffDetEta->SetBinError(44,0.00460425);
idEffDetEta->SetBinError(45,0.00565897);
idEffDetEta->SetBinError(46,0.00622265);
idEffDetEta->SetBinError(47,0.00624347);
idEffDetEta->SetBinError(48,0.0069773);
idEffDetEta->SetBinError(49,0.00671295);
idEffDetEta->SetBinError(50,0.0181297);
idEffDetEta->SetBinError(51,0.0307578);
idEffDetEta->SetBinError(52,0.218486);


}
