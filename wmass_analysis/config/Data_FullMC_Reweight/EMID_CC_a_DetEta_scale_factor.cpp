{
//=========Macro generated from canvas: c2/1
//=========  (Fri Aug  3 19:11:35 2007) by ROOT version4.04/02b
   TCanvas *c2 = new TCanvas("c2", "1",54,31,700,500);
   gStyle->SetOptStat(0);
   c2->Range(-1.68,0.86,1.52,1.12667);
   c2->SetFillColor(10);
   c2->SetBorderSize(2);
   c2->SetLeftMargin(0.15);
   c2->SetBottomMargin(0.15);
   c2->SetFrameFillColor(0);
   
   TH1 *EMID_CC_a_DetEta_scale_factor = new TH1D("EMID_CC_a_DetEta_scale_factor","Scale_factor: EMID_CC_a_DetEta factor",24,-1.2,1.2);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(2,0.97861);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(3,0.981141);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(4,0.985134);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(5,0.988767);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(6,0.967078);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(7,0.996852);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(8,0.974487);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(9,0.979208);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(10,0.974022);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(11,0.982059);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(12,0.963773);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(13,0.983978);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(14,0.978371);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(15,0.981966);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(16,0.987881);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(17,1.00225);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(18,0.989335);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(19,0.993982);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(20,0.992199);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(21,0.990533);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(22,0.97488);
   EMID_CC_a_DetEta_scale_factor->SetBinContent(23,0.995259);
   EMID_CC_a_DetEta_scale_factor->SetBinError(2,0.0122554);
   EMID_CC_a_DetEta_scale_factor->SetBinError(3,0.00821127);
   EMID_CC_a_DetEta_scale_factor->SetBinError(4,0.00680127);
   EMID_CC_a_DetEta_scale_factor->SetBinError(5,0.00679049);
   EMID_CC_a_DetEta_scale_factor->SetBinError(6,0.00839826);
   EMID_CC_a_DetEta_scale_factor->SetBinError(7,0.00655065);
   EMID_CC_a_DetEta_scale_factor->SetBinError(8,0.00756381);
   EMID_CC_a_DetEta_scale_factor->SetBinError(9,0.00781012);
   EMID_CC_a_DetEta_scale_factor->SetBinError(10,0.00776137);
   EMID_CC_a_DetEta_scale_factor->SetBinError(11,0.00748663);
   EMID_CC_a_DetEta_scale_factor->SetBinError(12,0.00853637);
   EMID_CC_a_DetEta_scale_factor->SetBinError(13,0.00766265);
   EMID_CC_a_DetEta_scale_factor->SetBinError(14,0.00767436);
   EMID_CC_a_DetEta_scale_factor->SetBinError(15,0.00732688);
   EMID_CC_a_DetEta_scale_factor->SetBinError(16,0.00657333);
   EMID_CC_a_DetEta_scale_factor->SetBinError(17,0.00608426);
   EMID_CC_a_DetEta_scale_factor->SetBinError(18,0.00693677);
   EMID_CC_a_DetEta_scale_factor->SetBinError(19,0.00623327);
   EMID_CC_a_DetEta_scale_factor->SetBinError(20,0.00640004);
   EMID_CC_a_DetEta_scale_factor->SetBinError(21,0.00718712);
   EMID_CC_a_DetEta_scale_factor->SetBinError(22,0.0081154);
   EMID_CC_a_DetEta_scale_factor->SetBinError(23,0.00999266);
   EMID_CC_a_DetEta_scale_factor->SetMinimum(0.9);
   EMID_CC_a_DetEta_scale_factor->SetMaximum(1.1);
   EMID_CC_a_DetEta_scale_factor->SetEntries(24);
   EMID_CC_a_DetEta_scale_factor->SetStats(0);
   EMID_CC_a_DetEta_scale_factor->SetLineWidth(3);
   EMID_CC_a_DetEta_scale_factor->SetMarkerStyle(20);
   EMID_CC_a_DetEta_scale_factor->SetMarkerSize(0.9);
   EMID_CC_a_DetEta_scale_factor->GetXaxis()->SetTitle("EMID_CC_a_DetEta");
   EMID_CC_a_DetEta_scale_factor->GetXaxis()->SetTitleSize(0.06);
   EMID_CC_a_DetEta_scale_factor->GetYaxis()->SetTitle("efficiency data/MC");
   EMID_CC_a_DetEta_scale_factor->GetYaxis()->SetTitleSize(0.06);
   EMID_CC_a_DetEta_scale_factor->GetYaxis()->SetTitleOffset(0.8);
   EMID_CC_a_DetEta_scale_factor->GetZaxis()->SetTitleSize(0.06);
   EMID_CC_a_DetEta_scale_factor->Draw("");
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
