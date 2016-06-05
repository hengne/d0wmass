#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

void drawall2() {

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

  //met, mt and pt are in outpdf_run1raf_fullrangeSV3030_ccecseparate for CC/EC separate
  //sv and svlongunsmear are in outpdf_run1raf_newrangeSV85_ccecseparate for CC/EC separate

  TGraphErrors* mass = new TGraphErrors(4);
  TGraphErrors* masscc = new TGraphErrors(4);

  const char *file[] = {"outpdf_run2raf_newrangeSV685_765_ccectogether/outpdf_trkmatch_15_32_fid_mt.log",
"outpdf_run2raf_newrangeSV685_765_ccectogether/outpdf_trkmatch_15_32_fid_pt.log",
"outpdf_run2raf_newrangeSV685_765_ccectogether/outpdf_trkmatch_15_32_fid_met.log",
"outpdf_run2raf_newrangeSV685_765_ccectogether/outpdf_trkmatch_15_32_fid_sv.log",
};
 

 char * cstr, *p;

 float massn;
 double pdfunct;
 double pdfunctcc;
 
  for (Int_t ifile=0; ifile<4; ifile++) {
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
  masscc->GetXaxis()->SetTitle("Variable");
 masscc->Draw("AP");
  c1->Print("PDFFitsAll2_Pt_CC.eps");
  c1->Print("PDFFitsAll2_Pt_CC.gif");

 TCanvas* c2 = new TCanvas();
 c2->cd();
 mass->SetTitle("CCEC");
mass->GetYaxis()->SetTitle("Best fit and PDF Uncertainty (GeV)");
  mass->GetYaxis()->SetTitleOffset(1.5);
  mass->GetXaxis()->SetTitle("Variable");
 mass->Draw("AP");
  c2->Print("PDFFitsAll2_Pt_CCEC.eps");
  c2->Print("PDFFitsAll2_Pt_CCEC.gif");
 TCanvas* c3 = new TCanvas();

 TLegend* lega = new TLegend(0.1, .1, 0.9, 0.89);
   lega->SetBorderSize(0);
  lega->SetFillColor(0);
 lega->AddEntry(mass, "1 = MT", "");
 lega->AddEntry(mass, "2 = PT", "");
 lega->AddEntry(mass, "3 = MET", "");
 lega->AddEntry(mass, "4 = SV", "");
lega->Draw(); 
  c3->Print("PDFFitsAll2_Legend.eps");
  c3->Print("PDFFitsAll2_Legend.gif");

}
