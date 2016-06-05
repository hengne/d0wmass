void style(){
  
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetFrameBorderMode(0);

/*
  gStyle->SetTitleColor(0);
  gStyle->SetTitleBorderSize(1);
  gStyle->SetTitleX(0.10); // 0.05
  gStyle->SetTitleY(0.94); // 0.97
  gStyle->SetTitleW(0.5);
  gStyle->SetTitleH(0.06); // 0.08

  gStyle->SetLabelOffset(1e-04);
  gStyle->SetLabelSize(0.2);
  
  gStyle->SetStatColor(0);
  gStyle->SetStatBorderSize(1);
  gStyle->SetStatX(0.90);
  gStyle->SetStatY(0.90); // 0.97
  gStyle->SetStatW(0.30);
  gStyle->SetStatH(0.10); // 0.15
  
  */

  gStyle->SetOptStat(0); // 11111111
  //gStyle->SetOptStat(0); // 11111111
  
  gStyle->SetOptTitle(kTRUE);
  
  gStyle->SetMarkerStyle(8);
  gStyle->SetMarkerColor(4);
  gStyle->SetMarkerSize(0.85);
  //   gStyle->SetOptFit(0);
}

void hstyle(TH1F *h, char *xtitle="", char *ytitle="", int lwidth=3, int lcolor=1, int lstyle=1, 
	    int fstyle=1001,int fcolor=32, double min=-1111.,double max=-1111.,
	    int ndivx=510, int ndivy=510, int optstat=110){
  h->SetLineWidth(lwidth);
  h->SetLineColor(lcolor);
  h->SetLineStyle(lstyle);
//  h->SetFillColor(fcolor);
  h->SetFillStyle(fstyle);
  h->SetMaximum(max);
  h->SetMinimum(min);
  h->GetXaxis()->SetNdivisions(ndivx);
  h->GetYaxis()->SetNdivisions(ndivy);
  h->SetLabelFont(62,"X");       // 42
  h->SetLabelFont(62,"Y");       // 42
  h->SetLabelOffset(0.0001,"X"); // D=0.005
  h->SetLabelOffset(0.005,"Y");  // D=0.005
  h->SetLabelSize(0.03,"X");    // 0.038
  h->SetLabelSize(0.03,"Y");    // 0.038
  h->SetTitleOffset(0.60,"X");   // 0.9
  h->SetTitleOffset(0.60,"Y");   // 0.9
  h->SetTitleSize(0.06,"X");
  h->SetTitleSize(0.06,"Y");
  h->SetTitle(0);
  h->SetStats(optstat);
  if(xtitle) h->GetXaxis()->SetTitle(xtitle);
  if(ytitle) h->GetYaxis()->SetTitle(ytitle);
}

void hstyle2(TH2F *h,int lwidth=3, int lcolor=1, int lstyle=1, 
	     int fstyle=1001,int fcolor=32, double min=-1111.,double max=-1111.,
	     int ndivx=510, int ndivy=510, int optstat=0){
  h->SetLineWidth(lwidth);
  h->SetLineColor(lcolor);
  h->SetLineStyle(lstyle);
  h->SetFillColor(fcolor);
  h->SetFillStyle(fstyle);
  h->SetMaximum(max);
  h->SetMinimum(min);
  h->GetXaxis()->SetNdivisions(ndivx);
  h->GetYaxis()->SetNdivisions(ndivy);
  h->SetLabelFont(62,"X");       // 42
  h->SetLabelFont(62,"Y");       // 42
  h->SetLabelOffset(0.0001,"X"); // D=0.005
  h->SetLabelOffset(0.005,"Y");  // D=0.005
  h->SetLabelSize(0.03,"X");    // 0.038
  h->SetLabelSize(0.03,"Y");    // 0.038
  h->SetTitleOffset(0.90,"X");   // 0.9
  h->SetTitleOffset(1.10,"Y");   // 0.9
  h->SetTitleSize(0.04,"X");
  h->SetTitleSize(0.04,"Y");
  h->SetTitle(0);
  h->SetStats(optstat);
}
