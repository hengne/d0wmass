{
//=========Macro generated from canvas: c2/1
//=========  (Fri Aug  3 19:11:17 2007) by ROOT version4.04/02b
   TCanvas *c2 = new TCanvas("c2", "1",54,31,700,500);
   gStyle->SetOptStat(0);
   c2->Range(-1.68,0.86,1.52,1.12667);
   c2->SetFillColor(10);
   c2->SetBorderSize(2);
   c2->SetLeftMargin(0.15);
   c2->SetBottomMargin(0.15);
   c2->SetFrameFillColor(0);
   
   TH1 *PreID_CC_a_DetEta_scale_factor = new TH1D("PreID_CC_a_DetEta_scale_factor","Scale_factor: PreID_CC_a_DetEta factor",24,-1.2,1.2);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(2,0.996785);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(3,0.9878);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(4,0.998806);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(5,0.990131);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(6,0.991628);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(7,0.991387);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(8,0.989417);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(9,0.996549);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(10,0.987264);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(11,0.989435);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(12,0.989238);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(13,0.987259);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(14,0.994859);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(15,0.98379);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(16,0.985029);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(17,0.981169);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(18,0.97737);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(19,0.983118);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(20,0.99261);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(21,0.997288);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(22,0.993419);
   PreID_CC_a_DetEta_scale_factor->SetBinContent(23,0.999196);
   PreID_CC_a_DetEta_scale_factor->SetBinError(2,0.00876004);
   PreID_CC_a_DetEta_scale_factor->SetBinError(3,0.00749489);
   PreID_CC_a_DetEta_scale_factor->SetBinError(4,0.00577387);
   PreID_CC_a_DetEta_scale_factor->SetBinError(5,0.005828);
   PreID_CC_a_DetEta_scale_factor->SetBinError(6,0.0059416);
   PreID_CC_a_DetEta_scale_factor->SetBinError(7,0.00544831);
   PreID_CC_a_DetEta_scale_factor->SetBinError(8,0.00558086);
   PreID_CC_a_DetEta_scale_factor->SetBinError(9,0.00558297);
   PreID_CC_a_DetEta_scale_factor->SetBinError(10,0.00546237);
   PreID_CC_a_DetEta_scale_factor->SetBinError(11,0.00565028);
   PreID_CC_a_DetEta_scale_factor->SetBinError(12,0.00536642);
   PreID_CC_a_DetEta_scale_factor->SetBinError(13,0.0056661);
   PreID_CC_a_DetEta_scale_factor->SetBinError(14,0.00479241);
   PreID_CC_a_DetEta_scale_factor->SetBinError(15,0.00575352);
   PreID_CC_a_DetEta_scale_factor->SetBinError(16,0.00574399);
   PreID_CC_a_DetEta_scale_factor->SetBinError(17,0.00653888);
   PreID_CC_a_DetEta_scale_factor->SetBinError(18,0.00670211);
   PreID_CC_a_DetEta_scale_factor->SetBinError(19,0.00638909);
   PreID_CC_a_DetEta_scale_factor->SetBinError(20,0.00574156);
   PreID_CC_a_DetEta_scale_factor->SetBinError(21,0.00577077);
   PreID_CC_a_DetEta_scale_factor->SetBinError(22,0.00538398);
   PreID_CC_a_DetEta_scale_factor->SetBinError(23,0.00841959);
   PreID_CC_a_DetEta_scale_factor->SetMinimum(0.9);
   PreID_CC_a_DetEta_scale_factor->SetMaximum(1.1);
   PreID_CC_a_DetEta_scale_factor->SetEntries(24);
   PreID_CC_a_DetEta_scale_factor->SetStats(0);
   PreID_CC_a_DetEta_scale_factor->SetLineWidth(3);
   PreID_CC_a_DetEta_scale_factor->SetMarkerStyle(20);
   PreID_CC_a_DetEta_scale_factor->SetMarkerSize(0.9);
   PreID_CC_a_DetEta_scale_factor->GetXaxis()->SetTitle("PreID_CC_a_DetEta");
   PreID_CC_a_DetEta_scale_factor->GetXaxis()->SetTitleSize(0.06);
   PreID_CC_a_DetEta_scale_factor->GetYaxis()->SetTitle("efficiency data/MC");
   PreID_CC_a_DetEta_scale_factor->GetYaxis()->SetTitleSize(0.06);
   PreID_CC_a_DetEta_scale_factor->GetYaxis()->SetTitleOffset(0.8);
   PreID_CC_a_DetEta_scale_factor->GetZaxis()->SetTitleSize(0.06);
   PreID_CC_a_DetEta_scale_factor->Draw("");
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}