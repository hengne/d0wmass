#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

void draw() {

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
  TCanvas* c1 = new TCanvas();

  //met, mt and pt are in outpdf_run1raf_fullrangeSV3030_ccecseparate for CC/EC separate FOR SV (others CC+EC)
  //sv and svlongunsmear are in outpdf_run1raf_newrangeSV85_ccecseparate for CC/EC separate FOR SV (others CC+EC)
  //all varaibles in outpdf_run2raf_newrangeSV85_ccectogether with CC+EC rather than EC alone.  CC still separate

  TGraphErrors* mass = new TGraphErrors(9);
  TGraphErrors* masscc = new TGraphErrors(9);
 
  const char *file[] = {"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_2_15_32_fid_sv.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_3_15_32_fid_sv.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_4_15_32_fid_sv.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_5_15_32_fid_sv.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_6_15_32_fid_sv.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_7_15_32_fid_sv.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_trkmatch_15_25_sv.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_trkmatch_15_32_sv.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_trkmatch_15_32_fid_sv.log",
};
  
  /**

  const char *file[] = {"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_2_15_32_fid_pt.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_3_15_32_fid_pt.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_4_15_32_fid_pt.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_5_15_32_fid_pt.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_6_15_32_fid_pt.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_hor_7_15_32_fid_pt.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_trkmatch_15_25_pt.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_trkmatch_15_32_pt.log",
"outpdf_run2raf_newrangeSV85_ccectogether/outpdf_trkmatch_15_32_fid_pt.log",
};
  **/
 char * cstr, *p;

 float massn;
 double pdfunct;
 double pdfunctcc;
 
  for (Int_t ifile=0; ifile<9; ifile++) {
    cout<<file[ifile]<<endl;
    ifstream inf(file[ifile]);
    
    if (!inf){
      exit(1);
    }
    while (inf)
      {
	std::string strInput;
        getline(inf, strInput);
	//cout << strInput << endl;
	if( ! strInput.find("W mass: ", 0)){
	  //  cout << strInput << endl;
	   cstr = new char [strInput.size()+1];
	   strcpy (cstr, strInput.c_str());
	   p=strtok (cstr,"W mass: ");
	   //cout<<p<<endl;
	   massn = atof (p);
	}
	if( !strInput.find("PDF error: ", 0)){
	  //cout << strInput << endl;
	   cstr = new char [strInput.size()+1];
	   strcpy (cstr, strInput.c_str());
	   p=strtok (cstr,"PDF error: ");
	   //cout<<p<<endl;
	   pdfunct = atof (p);
	}
	if( ! strInput.find("PDF error (CC): ", 0)){
	  //cout << strInput << endl;
	   cstr = new char [strInput.size()+1];
	   strcpy (cstr, strInput.c_str());
	   p=strtok (cstr,"PDF error (CC): ");
	   // cout<<p<<endl;
	   pdfunctcc = atof (p);
	}
      }
    cout<<massn<<"  "<<pdfunct<<"  "<<pdfunctcc<<endl;
    mass->SetPoint(ifile, ifile+1, massn);
    mass->SetPointError(ifile, 0, pdfunct);
    masscc->SetPoint(ifile, ifile+1, massn);
    masscc->SetPointError(ifile, 0, pdfunctcc);
  }
  

  mass->SetMarkerStyle(7);
  mass->SetMarkerColor(kBlue);
  masscc->SetMarkerStyle(7);
  masscc->SetMarkerColor(kBlue);
 
  masscc->SetTitle("CC");
masscc->GetYaxis()->SetTitle("Best fit and PDF Uncertainty (GeV)");
  masscc->GetYaxis()->SetTitleOffset(1.5);
  masscc->GetXaxis()->SetTitle("File Used, Sv");
 masscc->Draw("AP");
  c1->Print("PDFFits_Sv_CC2.eps");
  c1->Print("PDFFits_Sv_CC2.gif");

 TCanvas* c2 = new TCanvas();
 c2->cd();
 mass->SetTitle("CCEC");
mass->GetYaxis()->SetTitle("Best fit and PDF Uncertainty (GeV)");
  mass->GetYaxis()->SetTitleOffset(1.5);
  mass->GetXaxis()->SetTitle("File Used, Sv");
 mass->Draw("AP");
  c2->Print("PDFFits_Sv_CCEC2.eps");
  c2->Print("PDFFits_Sv_CCEC2.gif");
 TCanvas* c3 = new TCanvas();

 TLegend* lega = new TLegend(0.1, .1, 0.9, 0.89);
   lega->SetBorderSize(0);
  lega->SetFillColor(0);
 lega->AddEntry(mass, "1 = hor_2_15_32_fid", "");
 lega->AddEntry(mass, "2 = hor_3_15_32_fid", "");
 lega->AddEntry(mass, "3 = hor_4_15_32_fid", "");
 lega->AddEntry(mass, "4 = hor_5_15_32_fid", "");
 lega->AddEntry(mass, "5 = hor_6_15_32_fid", "");
 lega->AddEntry(mass, "6 = hor_7_15_32_fid", "");
 lega->AddEntry(mass, "7 = trkmatch_15_25", "");
 lega->AddEntry(mass, "8 = trkmatch_15_32", "");
 lega->AddEntry(mass, "9 = trkmatch_15_32_fid", "");
lega->Draw(); 
  c3->Print("PDFFits_Legend.eps");
  c3->Print("PDFFits_Legend.gif");

}
