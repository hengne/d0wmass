{
const int n_track_eff_deteta_xbins = 64;
float track_eff_deteta_xbins[n_track_eff_deteta_xbins+1] = {-3.200000 ,-3.100000 ,-3.000000 ,-2.900000 ,-2.800000 ,-2.700000 ,-2.600000 ,-2.500000 ,-2.400000 ,-2.300000 ,-2.200000 ,-2.100000 ,-2.000000 ,-1.900000 ,-1.800000 ,-1.700000 ,-1.600000 ,-1.500000 ,-1.400000 ,-1.300000 ,-1.200000 ,-1.100000 ,-1.000000 ,-0.900000 ,-0.800000 ,-0.700000 ,-0.600000 ,-0.500000 ,-0.400000 ,-0.300000 ,-0.200000 ,-0.100000 ,0.000000 ,0.100000 ,0.200000 ,0.300000 ,0.400000 ,0.500000 ,0.600000 ,0.700000 ,0.800000 ,0.900000 ,1.000000 ,1.100000 ,1.200000 ,1.300000 ,1.400000 ,1.500000 ,1.600000 ,1.700000 ,1.800000 ,1.900000 ,2.000000 ,2.100000 ,2.200000 ,2.300000 ,2.400000 ,2.500000 ,2.600000 ,2.700000 ,2.800000 ,2.900000 ,3.000000 ,3.100000 ,3.200000  };

TH1F *track_eff_deteta = new TH1F("track_eff_deteta","track efficiency vs deteta, pt > 25GeV", n_track_eff_deteta_xbins, track_eff_deteta_xbins);

// -2.300000 to -2.200000
track_eff_deteta->SetBinContent(10,0.500093);
track_eff_deteta->SetBinError(10,0.046629);

// -2.200000 to -2.100000
track_eff_deteta->SetBinContent(11,0.545368);
track_eff_deteta->SetBinError(11,0.044719);

// -2.100000 to -2.000000
track_eff_deteta->SetBinContent(12,0.569543);
track_eff_deteta->SetBinError(12,0.041866);

// -2.000000 to -1.900000
track_eff_deteta->SetBinContent(13,0.523928);
track_eff_deteta->SetBinError(13,0.040274);

// -1.900000 to -1.800000
track_eff_deteta->SetBinContent(14,0.692418);
track_eff_deteta->SetBinError(14,0.032386);

// -1.800000 to -1.700000
track_eff_deteta->SetBinContent(15,0.762936);
track_eff_deteta->SetBinError(15,0.029729);

// -1.700000 to -1.600000
track_eff_deteta->SetBinContent(16,0.807543);
track_eff_deteta->SetBinError(16,0.023913);

// -1.600000 to -1.500000
track_eff_deteta->SetBinContent(17,0.895819);
track_eff_deteta->SetBinError(17,0.018950);

// -1.100000 to -1.000000
track_eff_deteta->SetBinContent(22,0.756985);
track_eff_deteta->SetBinError(22,0.029302);

// -1.000000 to -0.900000
track_eff_deteta->SetBinContent(23,0.745757);
track_eff_deteta->SetBinError(23,0.020536);

// -0.900000 to -0.800000
track_eff_deteta->SetBinContent(24,0.783819);
track_eff_deteta->SetBinError(24,0.019265);

// -0.800000 to -0.700000
track_eff_deteta->SetBinContent(25,0.777836);
track_eff_deteta->SetBinError(25,0.018662);

// -0.700000 to -0.600000
track_eff_deteta->SetBinContent(26,0.832088);
track_eff_deteta->SetBinError(26,0.016800);

// -0.600000 to -0.500000
track_eff_deteta->SetBinContent(27,0.800210);
track_eff_deteta->SetBinError(27,0.017118);

// -0.500000 to -0.400000
track_eff_deteta->SetBinContent(28,0.769591);
track_eff_deteta->SetBinError(28,0.017650);

// -0.400000 to -0.300000
track_eff_deteta->SetBinContent(29,0.772564);
track_eff_deteta->SetBinError(29,0.018107);

// -0.300000 to -0.200000
track_eff_deteta->SetBinContent(30,0.803386);
track_eff_deteta->SetBinError(30,0.017799);

// -0.200000 to -0.100000
track_eff_deteta->SetBinContent(31,0.806743);
track_eff_deteta->SetBinError(31,0.016351);

// -0.100000 to 0.000000
track_eff_deteta->SetBinContent(32,0.806471);
track_eff_deteta->SetBinError(32,0.016003);

// 0.000000 to 0.100000
track_eff_deteta->SetBinContent(33,0.825223);
track_eff_deteta->SetBinError(33,0.016617);

// 0.100000 to 0.200000
track_eff_deteta->SetBinContent(34,0.784966);
track_eff_deteta->SetBinError(34,0.016531);

// 0.200000 to 0.300000
track_eff_deteta->SetBinContent(35,0.780159);
track_eff_deteta->SetBinError(35,0.017725);

// 0.300000 to 0.400000
track_eff_deteta->SetBinContent(36,0.790057);
track_eff_deteta->SetBinError(36,0.017401);

// 0.400000 to 0.500000
track_eff_deteta->SetBinContent(37,0.794817);
track_eff_deteta->SetBinError(37,0.017595);

// 0.500000 to 0.600000
track_eff_deteta->SetBinContent(38,0.762666);
track_eff_deteta->SetBinError(38,0.017690);

// 0.600000 to 0.700000
track_eff_deteta->SetBinContent(39,0.799285);
track_eff_deteta->SetBinError(39,0.017650);

// 0.700000 to 0.800000
track_eff_deteta->SetBinContent(40,0.786361);
track_eff_deteta->SetBinError(40,0.017781);

// 0.800000 to 0.900000
track_eff_deteta->SetBinContent(41,0.793074);
track_eff_deteta->SetBinError(41,0.017363);

// 0.900000 to 1.000000
track_eff_deteta->SetBinContent(42,0.745668);
track_eff_deteta->SetBinError(42,0.019784);

// 1.000000 to 1.100000
track_eff_deteta->SetBinContent(43,0.777069);
track_eff_deteta->SetBinError(43,0.025565);

// 1.500000 to 1.600000
track_eff_deteta->SetBinContent(48,0.933190);
track_eff_deteta->SetBinError(48,0.012913);

// 1.600000 to 1.700000
track_eff_deteta->SetBinContent(49,0.857377);
track_eff_deteta->SetBinError(49,0.019315);

// 1.700000 to 1.800000
track_eff_deteta->SetBinContent(50,0.759736);
track_eff_deteta->SetBinError(50,0.025271);

// 1.800000 to 1.900000
track_eff_deteta->SetBinContent(51,0.685223);
track_eff_deteta->SetBinError(51,0.028142);

// 1.900000 to 2.000000
track_eff_deteta->SetBinContent(52,0.697698);
track_eff_deteta->SetBinError(52,0.029545);

// 2.000000 to 2.100000
track_eff_deteta->SetBinContent(53,0.621668);
track_eff_deteta->SetBinError(53,0.032236);

// 2.100000 to 2.200000
track_eff_deteta->SetBinContent(54,0.637416);
track_eff_deteta->SetBinError(54,0.036154);

// 2.200000 to 2.300000
track_eff_deteta->SetBinContent(55,0.611041);
track_eff_deteta->SetBinError(55,0.036892);
}
