{
//=========Macro generated from canvas: c2/1
//=========  (Fri Aug  3 19:11:20 2007) by ROOT version4.04/02b
   TCanvas *c2 = new TCanvas("c2", "1",54,31,700,500);
   gStyle->SetOptStat(0);
   c2->Range(-5.6,0.86,5.06667,1.12667);
   c2->SetFillColor(10);
   c2->SetBorderSize(2);
   c2->SetLeftMargin(0.15);
   c2->SetBottomMargin(0.15);
   c2->SetFrameFillColor(0);
   
   TH1 *PreID_EC_a_DetEta_scale_factor = new TH1D("PreID_EC_a_DetEta_scale_factor","Scale_factor: PreID_EC_a_DetEta factor",80,-4,4);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(16,0.998427);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(17,0.971416);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(18,0.960021);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(19,0.95491);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(20,0.97072);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(21,0.984246);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(22,0.963571);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(23,0.961062);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(24,0.951581);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(25,0.955519);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(56,0.933962);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(57,0.94587);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(58,0.961143);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(59,0.9749);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(60,0.974889);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(61,0.970265);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(62,0.97766);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(63,0.964969);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(64,1.00481);
   PreID_EC_a_DetEta_scale_factor->SetBinContent(65,0.971354);
   PreID_EC_a_DetEta_scale_factor->SetBinError(16,0.0124433);
   PreID_EC_a_DetEta_scale_factor->SetBinError(17,0.0149471);
   PreID_EC_a_DetEta_scale_factor->SetBinError(18,0.0134304);
   PreID_EC_a_DetEta_scale_factor->SetBinError(19,0.0130786);
   PreID_EC_a_DetEta_scale_factor->SetBinError(20,0.0097143);
   PreID_EC_a_DetEta_scale_factor->SetBinError(21,0.00809639);
   PreID_EC_a_DetEta_scale_factor->SetBinError(22,0.00980492);
   PreID_EC_a_DetEta_scale_factor->SetBinError(23,0.0103354);
   PreID_EC_a_DetEta_scale_factor->SetBinError(24,0.0104184);
   PreID_EC_a_DetEta_scale_factor->SetBinError(25,0.0106043);
   PreID_EC_a_DetEta_scale_factor->SetBinError(56,0.0119675);
   PreID_EC_a_DetEta_scale_factor->SetBinError(57,0.0113101);
   PreID_EC_a_DetEta_scale_factor->SetBinError(58,0.0105322);
   PreID_EC_a_DetEta_scale_factor->SetBinError(59,0.00843092);
   PreID_EC_a_DetEta_scale_factor->SetBinError(60,0.00901033);
   PreID_EC_a_DetEta_scale_factor->SetBinError(61,0.0100839);
   PreID_EC_a_DetEta_scale_factor->SetBinError(62,0.00961605);
   PreID_EC_a_DetEta_scale_factor->SetBinError(63,0.0122953);
   PreID_EC_a_DetEta_scale_factor->SetBinError(64,0.00927865);
   PreID_EC_a_DetEta_scale_factor->SetBinError(65,0.0175477);
   PreID_EC_a_DetEta_scale_factor->SetMinimum(0.9);
   PreID_EC_a_DetEta_scale_factor->SetMaximum(1.1);
   PreID_EC_a_DetEta_scale_factor->SetEntries(80);
   PreID_EC_a_DetEta_scale_factor->SetStats(0);
   PreID_EC_a_DetEta_scale_factor->SetLineWidth(3);
   PreID_EC_a_DetEta_scale_factor->SetMarkerStyle(20);
   PreID_EC_a_DetEta_scale_factor->SetMarkerSize(0.9);
   PreID_EC_a_DetEta_scale_factor->GetXaxis()->SetTitle("PreID_EC_a_DetEta");
   PreID_EC_a_DetEta_scale_factor->GetXaxis()->SetTitleSize(0.06);
   PreID_EC_a_DetEta_scale_factor->GetYaxis()->SetTitle("efficiency data/MC");
   PreID_EC_a_DetEta_scale_factor->GetYaxis()->SetTitleSize(0.06);
   PreID_EC_a_DetEta_scale_factor->GetYaxis()->SetTitleOffset(0.8);
   PreID_EC_a_DetEta_scale_factor->GetZaxis()->SetTitleSize(0.06);
   PreID_EC_a_DetEta_scale_factor->Draw("");
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}