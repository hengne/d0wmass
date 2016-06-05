void drawvar() {

  gROOT->SetStyle("Plain");
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleColor();
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetFillStyle(1001);
  gStyle->SetStatColor(0);
  gStyle->SetStatX(0.5);
  gStyle->SetStatY(0.9);
  gStyle->SetOptStat(000000);
  gStyle->SetOptFit(0000);
  gStyle->SetPadTopMargin(0.1);  
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.15);

  TFile* mtf = new TFile("/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_newvar2/mt.root");
  TGraph* mt_ll = (TGraph*) mtf->Get("scan");
  mt_ll->SetLineColor(kRed);
  mt_ll->SetLineWidth(2);

  TFile* ptf = new TFile("/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_newvar2/pt.root");
  TGraph* pt_ll = (TGraph*) ptf->Get("scan");
  pt_ll->SetLineColor(kGreen);
  pt_ll->SetLineWidth(2);

  TFile* metf = new TFile("/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_newvar2/met.root");
  TGraph* met_ll = (TGraph*) metf->Get("scan");
  met_ll->SetLineColor(kMagenta);
  met_ll->SetLineWidth(2);
 
  TFile* file = new TFile("/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_newvar2/sv.root");
  TGraph* sv_ll = (TGraph*) file->Get("likelihood");
  sv_ll->SetLineColor(kBlue);
  sv_ll->SetLineWidth(2);
  file->Close();

  TCanvas* c2 = new TCanvas();
  mt_ll->Draw();
  mt_ll->GetYaxis()->SetTitle("LLR");
  mt_ll->GetYaxis()->SetTitleOffset(1.5);
  mt_ll->GetXaxis()->SetTitle("Template mass (GeV)");
  mt_ll->GetXaxis()->SetRangeUser(76, 84);
  mt_ll->Draw("ALP");

 pt_ll->Draw("PL");
 met_ll->Draw("PL");
  sv_ll->Draw("PL");
  
TLegend* leg = new TLegend(0.4, 0.7, 0.7, 0.89);
  //  leg->SetTextSize(0.05);
  leg->AddEntry(mt_ll, "Trans. mass", "l");
  leg->AddEntry(pt_ll, "Electron Pt", "l");
  leg->AddEntry(met_ll, "Missing Et", "l");
  leg->AddEntry(sv_ll, "SV (M = trial M)", "l");
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->Draw();


  c2->Print("singvar2_vars_reco.eps");
  c2->Print("singvar2_vars_reco.gif");
  //--------------------------------------------

  TFile* mtf = new TFile("/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_newvar2/mtgen.root");
  TGraph* mt_ll = (TGraph*) mtf->Get("scan");
  mt_ll->SetLineColor(kRed);
  mt_ll->SetLineWidth(2);

  TFile* ptf = new TFile("/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_newvar2/ptgen.root");
  TGraph* pt_ll = (TGraph*) ptf->Get("scan");
  pt_ll->SetLineColor(kGreen);
  pt_ll->SetLineWidth(2);

  TFile* metf = new TFile("/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_newvar2/metgen.root");
  TGraph* met_ll = (TGraph*) metf->Get("scan");
  met_ll->SetLineColor(kMagenta);
  met_ll->SetLineWidth(2);
 
  TFile* file = new TFile("/work/rebel-clued0/jenny/SpringNewBlinding/epmcs_analysis_newvar2/svgen.root");
  TGraph* sv_ll = (TGraph*) file->Get("likelihood");
  sv_ll->SetLineColor(kBlue);
  sv_ll->SetLineWidth(2);
  file->Close();

  TCanvas* c3 = new TCanvas();
  mt_ll->Draw();
  mt_ll->GetYaxis()->SetTitle("LLR");
  mt_ll->GetYaxis()->SetTitleOffset(1.5);
  mt_ll->GetXaxis()->SetTitle("Template mass (GeV)");
  mt_ll->GetXaxis()->SetRangeUser(76, 84);
  mt_ll->Draw("ALP");

 pt_ll->Draw("PL");
 met_ll->Draw("PL");
  sv_ll->Draw("PL");
  
TLegend* leg = new TLegend(0.4, 0.7, 0.7, 0.89);
  //  leg->SetTextSize(0.05);
  leg->AddEntry(mt_ll, "Trans. mass (Gen)", "l");
  leg->AddEntry(pt_ll, "Electron Pt (Gen)", "l");
  leg->AddEntry(met_ll, "Missing Et (Gen)", "l");
  leg->AddEntry(sv_ll, "SV (M = trial M) (Gen)", "l");
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->Draw();


  c3->Print("singvar2_vars_gen.eps");
  c3->Print("singvar2_vars_gen.gif");




  /**
  TCanvas* c3 = new TCanvas();
  mt_ll->Draw();
  mt_ll->GetYaxis()->SetTitle("LLR");
  mt_ll->GetYaxis()->SetTitleOffset(1.5);
  mt_ll->GetXaxis()->SetTitle("Template mass (GeV)");
  mt_ll->Draw("ALP");
  likelihood[50]->SetLineWidth(2);
  likelihood[50]->Draw("PL");
  TLegend* leg = new TLegend(0.4, 0.75, 0.7, 0.89);
  //  leg->SetTextSize(0.05);
  leg->AddEntry(mt_ll, "Trans. mass", "l");
  leg->AddEntry(likelihood[50], "SV (M = trial M)", "l");
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->Draw();
 
  c1->Print("singvar1.eps");
  c2->Print("singvar2.eps");
  c3->Print("singvar3.eps");
  **/
}
