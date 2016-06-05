#include <TROOT.h>
#include <TApplication.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <vector>
#include <iostream>
#include <sstream>
#include "PParameterReader.hpp"

#include "matrix.cpp"

// Two options for the chi plots (need to gmake clean; gmake to activate these)
//#define RATIO
//#define ZEROLINE

using namespace std;

namespace plot {

const double eff_data=0.75;//Run2A .778;
const double eff_error_data=0.05;//Run2A .021;
const double fake_data=0.11; //Run2A .022;
const double fake_error_data=0.01;//Run2A .001;

  //fractions for zee and wtanu are passed from wenucomp now for each method.

char data_label[100]="DATA";  // first file,  upper label
char mc_label[100]="PMCS";    // second file, bottom label
int data_color=kRed;          // first file,  upper label
int mc_color=kBlue;           // second file, bottom label
int data_marker=kRed;         // first file,  upper label
int mc_marker=kBlue;          // second file, bottom label

inline void set_MC_label(const char *label=NULL, int color=kBlue, int marker=25 ) {
  if(label) sprintf(mc_label,label);
  mc_color=color;
  mc_marker=marker; 
}
inline void set_DATA_label(const char *label=NULL, int color=kRed, int marker=21 ) {
  if(label) sprintf(data_label,label);
  data_color=color;
  data_marker=marker;
}

// write out each plot into a separate eps file
// this will make histogramszee.ps and histogramswen.ps empty
const bool write_out_each_plot = false;
const bool not_show_chi2 = false;

// used for wencomp, need to subtract background
void plot_util(TString cname, //TCanvas *c, 
	       vector<TH1 *> datahistos, 
	       vector<TH1 *> datahistos_spatial, 
	       vector<TH1 *> mchistos, 
	       vector<TH1 *> bkgdhistos, 
	       bool make_chi2, 
	       bool if_mc=kTRUE, 
	       double xmin=-1E30, 
	       double xmax=1E30, 
	       TPostScript *ps=NULL,      // optional output PS file
	       int max_plots_per_page=10, // optional max. num. of rows per canvas
	       TFile *file=NULL,         // optional output ROOT file
	       int qcd_option=0,         //qcd bkgd matrix method or from file
	       bool outputbkg=false, double zee_bkg_fraction=-1, double wtaunu_bkg_fraction=-1, TString qcdfile="");          //write out background hists to a file

// used for zeecomp and znunucomp, no need to subtract background
void plot_util(TString cname, // TCanvas *c, 
	       vector<TH1 *> datahistos, 
	       vector<TH1 *> mchistos, 
	       bool make_chi2, 
	       double xmin=-1E30, 
	       double xmax=1E30, 
	       TPostScript *ps=NULL,      // optional output PS file
	       int max_plots_per_page=10, // optional max. num. of rows per canvas
	       TFile *file=NULL,          // optional output ROOT file
	       double externalScale=-1);  // optional external normalisation factor

// used for zeecomp
void plot_MeanSigma_pTeeBin(TString cname, // TCanvas *c, 
			    vector<TH1 *> a1, 
			    vector<TH1 *> b1, 
			    vector<TH1 *> c1, 
			    TGraphErrors *ge1, 
			    TGraphErrors *ge2, 
			    TGraphErrors *ge_chi, 
			    TGraphErrors *ge1_fitted, 
			    TGraphErrors *ge2_fitted, 
			    TGraphErrors *ge_fitted_chi, 
			    int value_option, // 0=MEAN, 1=RMS
			    int plot_option,  // 0=Eta Imbalance, 1=Xi Imbalance
			    bool make_chi2, 
			    double& chi2, 
			    double& chi2_fitted, 
			    TPostScript *ps=NULL,      // optional output PS file
			    int max_plots_per_page=10, // optional max. num. of rows per canvas
			    TFile *file=NULL);         // optional output ROOT file

// used for zeecomp
void plot_SigmaDeltaPhiZRecoil_pTeeBin(TString cname, // TCanvas *c, 
				       vector<TH1 *> a1, 
				       vector<TH1 *> b1, 
				       vector<TH1 *> c1, 
				       TGraphErrors *ge1, 
				       TGraphErrors *ge2, 
				       TGraphErrors *ge_chi, 
				       TGraphErrors *ge1_fitted, 
				       TGraphErrors *ge2_fitted, 
				       TGraphErrors *ge_fitted_chi, 
				       bool make_chi2, 
				       double& chi2, 
				       double& chi2_fitted, 
				       TPostScript *ps=NULL,     // optional output PS file
				       int max_plots_per_page=10,// optional max. num. of rows per canvas
				       TFile *file=NULL);        // optional output ROOT file  
// used for zeecomp and znunucomp
void plot_without_background(bool if_mc, 
			     TH1 *hist, 
			     TH1 *hist_spatial, 
			     TH1* hist_signal,
			     TH1* bkg_signal);

// used for zeecomp and znunucomp                        
void plot_without_background_3d(bool if_mc,                
				TH1 *hist,                  
				TH1 *hist_spatial,        
				TH1* hist_signal,     
                                TH1* bkg_signal,       
                                TH2F *fake,            
                                TH2F *eff, TString qcdfile);         

// calculate chi2/dof shown on the legend
void find_chi2(TH1 *a1, 
	       TH1 *b1, 
	       Double_t xmin, 
	       Double_t xmax, 
	       Double_t &chisq, 
	       Int_t &NBin);
// make chi distribution plot
void plot_with_chi2(TH1 *a1, 
		    TH1 *b1, 
		    Double_t xmin=-1E30, 
		    Double_t xmax=1E30);

// special function for plotting Mt, electron pT, 
// MET and Z pT for Upara<0 and Upara>0
void plot2overlay_without_background(TString cname, // TCanvas *c, 
				     vector<TH1 *> datahistos, 
				     vector<TH1 *> datahistos_spatial, 
				     vector<TH1 *> mchistos, 
				     bool if_mc=kTRUE, 
				     double xmin=-1E30, 
				     double xmax=1E30,
				     TPostScript *ps=NULL, // optional output PS file
				     TFile *file=NULL);    // optional output ROOT file

void plot2overlay_with_background(TString cname, // TCanvas *c, 
                                 vector<TH1 *> datahistos, 
                                 vector<TH1 *> datahistos_spatial, 
                                 vector<TH1 *> bkgdhistos_spatial,
                                 vector<TH1 *> mchistos, 
                                 bool if_mc=kTRUE, 
                                 double xmin=-1E30, 
                                 double xmax=1E30,
                                 int qcd_option = 1,
                                 TPostScript *ps=NULL, // optional output PS file
                                 TFile *file=NULL, double zee_bkg_fraction=-1, double wtaunu_bkg_fraction=-1, TString qcdfile="");    // optional output ROOT file

}; // end of plot:: namespace
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// This plot_util is mainly used for obtaining plots for zeecomp and znunucomp
// since we don't need to worry about background subtraction here
///////////////////////////////////////////////////////////////////////////////////////
void plot::plot_util(TString cname, // TCanvas *c, 
		     vector<TH1 *> datahistos_inp, 
		     vector<TH1 *> mchistos_inp, 
		     bool make_chi2, 
		     double xmin, 
		     double xmax, 
		     TPostScript *ps,         // optional output PS file
		     int max_plots_per_page,  // optional max. num. of rows per canvas
		     TFile *file,             // optional output ROOT file
		     double externalScale) {  // optional external scale factor

  if(datahistos_inp.size()!=mchistos_inp.size()) {
    cout<<"Different number of histograms for data and MC"<<endl;
    return;
  }
  if(datahistos_inp.size()==0) {
    cout<<"No hist in data_spatial to compare"<<endl;
    return;
  }
  // exclude NULL pointers from histogram lists
  vector<TH1 *> datahistos;
  vector<TH1 *> mchistos;
  for(int i=0; i<datahistos_inp.size(); i++) {
    if(datahistos_inp[i] && mchistos_inp[i]) {
      datahistos.push_back(datahistos_inp[i]);
      mchistos.push_back(mchistos_inp[i]);
      }
  }

  int vec_size = datahistos.size();
  if (vec_size==0) {
    cout<<"No histograms to plot !!! (at least one pair of non-NULL pointers must exist)"<<endl;
    return;
  }
  int NPages = 1;
  int NPads = 0;
  int NPads_last = 0;

  if(vec_size>max_plots_per_page) {
    if(vec_size%max_plots_per_page==0) {
      NPages     = vec_size / max_plots_per_page;
      NPads_last = max_plots_per_page; 
      NPads      = max_plots_per_page;
    } else {
      NPages     = vec_size / max_plots_per_page + 1;
      NPads_last = vec_size%max_plots_per_page;
      NPads      = max_plots_per_page;
    }
  } else {
    NPads=vec_size;
    NPads_last=vec_size;
  }

  // loop thru pages
  for(int ipage=0; ipage<NPages; ipage++) {

    if(ps) ps->Off(); // temporarily disable printing to PS file
    stringstream name;
    name << cname;
    if(NPages>1) name << " (page "<<ipage<<")"; 
    TCanvas *c = new TCanvas(name.str().c_str(), "c", 50,10,700,800);

    int istart=0, iend=vec_size;
    if(vec_size==1) { 
      if(make_chi2) c->Divide(1, 2);
      else c->Divide(1, 1);
    } else {
      if(NPages==1 || ipage==NPages-1) {
	if(make_chi2) c->Divide(2, NPads);
	else          c->Divide(1, NPads);
	istart=ipage*NPads;
	iend=istart+NPads_last;
      } else {
	if(make_chi2) c->Divide(2, NPads);
        else          c->Divide(1, NPads);
	istart=ipage*NPads;
	iend=istart+NPads;
      }
    }
  
    int ipad = 1;
    double chisq = 0.0;
    int nbins = 0;
    char word[50];
    bool plot_ok=false;

    // loop thru distributions for a given page
    for(int i=istart; i<iend; i++) {
    // "h*" histograms are copies of data histograms
    // "k*" histograms are copies of  pmcs histograms
    // "k*"s are normalized to "h*"s in SetRangeUser(xmin, xmax);
    //           where xmin, xmax are passed to this function;
    //           can also be normalized by external scale which is passed to this function
    // "a*"s are pointers to "h*"s
    // "b*"s are pointers to "k*"s
    // "*1" are histograms
    // "*2" are profiles
      // cout << "ipage="<<ipage<<", iplot="<<i<<", ipad="<<ipad<<endl<<flush;

      TH1F *h1 = (TH1F *)datahistos[i];
      TH1F *k1 = (TH1F *)mchistos[i];

      // need to deal with TProfile differently
      TProfile *h2 = dynamic_cast<TProfile *>(datahistos[i]);
      TProfile *k2 = dynamic_cast<TProfile *>(mchistos[i]);
      
      ///////////////////////////////////////////////////////////////
      // Substitute h1 with a TH1F copy and normalize this copy later
      // No need to normalzie TProfile histograms
      if(h2==0 && h1!=0) {
	TH1F *hist_new=(TH1F*)h1->Clone();;
	char new_name[1000];
	sprintf(new_name,"%s_copy",h1->GetName());
	hist_new->SetName(new_name);
	h1=hist_new;
      }
      // Substitute k1 with a TH1F copy and normalize this copy later
      // No need to normalzie TProfile histograms
      if(k2==0 && k1!=0) {
	TH1F *hist_new=(TH1F*)k1->Clone();
	char new_name[1000];
	sprintf(new_name,"%s_copy",k1->GetName());
	hist_new->SetName(new_name);
	k1=hist_new;
      }
      ///////////////////////////////////////////////////////////////

      TH1 *a1;
      TH1 *b1;

      if(h1==0 && h2==0) continue;
      if(k1==0 && k2==0) continue; 
      plot_ok=true; // both histograms exist

      if(h2 != 0 || k2 != 0) {     
	// For profiles you do not need to scale
	if (h2) a1 = h2;
	else a1=h1;
	if (k2) b1 = k2;
	else b1=k1;
      } else {
	// set user range
	h1->GetXaxis()->SetRangeUser(xmin, xmax);
	k1->GetXaxis()->SetRangeUser(xmin, xmax);

	// integrate for the given range
	Double_t entries_h1 = h1->Integral(h1->GetXaxis()->FindBin(xmin), h1->GetXaxis()->FindBin(xmax));
	Double_t entries_k1 = k1->Integral(k1->GetXaxis()->FindBin(xmin), k1->GetXaxis()->FindBin(xmax));
        if (externalScale<0) {
          k1->Scale(entries_h1/entries_k1);
        } else {
          k1->Scale(externalScale);
        }

	a1 = h1; // h1->Rebin(2, h1->GetName());
	b1 = k1; // k1->Rebin(2, k1->GetName());
      } 
      
      //make comparison plots
      c -> cd(ipad);
      a1->SetMarkerStyle(plot::data_marker);
      a1->SetMarkerColor(plot::data_color);
      a1->SetLineColor(plot::data_color);
      a1->SetMarkerSize(0.4);
      a1->Draw("pe");
      b1->SetName(TString(TString(a1->GetName())+"_hidden").Data());
      b1->SetMarkerStyle(plot::mc_marker);
      b1->SetMarkerColor(plot::mc_color);
      b1->SetLineColor(plot::mc_color);
      b1->SetMarkerSize(0.4);
      b1->SetLineWidth(2);
      b1->Draw("hist,same");
      
      plot::find_chi2(a1, b1, xmin, xmax, chisq, nbins);

      TLegend *leg1 = new TLegend(0.55,0.7,0.8,0.88,NULL,"brNDC");
      leg1->SetTextSize(0.05);
      leg1->SetLineColor(0);
      leg1->SetLineStyle(1);
      leg1->SetLineWidth(1);
      leg1->SetFillColor(0);
      leg1->SetFillStyle(0);
      leg1->SetBorderSize(0);
      leg1->SetFillColor(0);
      leg1->SetTextSize(0.035);
      
      if(!not_show_chi2) {
	sprintf(word, "#chi^{2}/ndf = %.1f/%d", chisq, nbins);
	leg1->SetHeader(word);
      }
      TLegendEntry *dataentry=leg1->AddEntry(a1, plot::data_label, "pl");
      if(dataentry) {
	dataentry->SetTextColor(plot::data_color);
	dataentry->SetMarkerSize(3);
      }
      TLegendEntry *mcentry=leg1->AddEntry(b1, plot::mc_label, "pl");
      if(mcentry) {
	mcentry->SetTextColor(plot::mc_color);
	mcentry->SetMarkerSize(3);
      }
      leg1->Draw();

      // if we want to write out each plot into a eps file
      if(write_out_each_plot) {
        gStyle->SetTitleFillColor(0);
	gStyle->SetPadLeftMargin(.16);
	TCanvas *c_temp = new TCanvas("c_temp", "canvas", 100, 200, 700, 800);
	a1->Draw("pe");
        b1->SetLineWidth(2);
	b1->Draw("hist,same");
	leg1->Draw();
	c_temp->Update();
	
        gROOT->ProcessLine(".! mkdir plots/");
	string eps_file_name = "plots/" + (string)(a1->GetName()) + ".eps";
	c_temp->Print(eps_file_name.c_str());
        string macro_file_name = "plots/" +  (string)(a1->GetName()) + ".C";
        c_temp->Print(macro_file_name.c_str());
	delete c_temp;
      }
      
      if(make_chi2) {
	ipad ++;
	c -> cd(ipad);
	plot::plot_with_chi2(a1, b1, xmin, xmax);
      }
      
      ipad++;     
    } // end of for(i=... loop

    // start a new page only if at least one histogram exists
    if(plot_ok) {
      if(ps) { ps->On(); ps->NewPage(); }
      c->Update();
      if(file) file->Append(c);
    }
  } // end of for(ipage=... loop

  // enable printing to PS file again
  if(ps) ps->On(); 
}

//////////////////////////////////////////////////////////////////////////////////
// This plot_util is mainly used for obtaining plots for wenucomp
// need to consider background subtraction here
///////////////////////////////////////////////////////////////////////////////////
void plot::plot_util(TString cname, // TCanvas *c, 
		     vector<TH1 *> datahistos_inp, 
		     vector<TH1 *> datahistos_spatial_inp, 
		     vector<TH1 *> mchistos_inp, 
		     vector<TH1 *> bkgdhistos_inp, 
		     bool make_chi2, 
		     bool if_mc, 
		     double xmin, 
		     double xmax, 
		     TPostScript *ps,       // optional output PS file
		     int max_plots_per_page,// optional max. num. of rows per canvas
		     TFile *file,
		     int qcd_option,
		     bool outputbkg, double zee_bkg_fraction, double wtaunu_bkg_fraction, TString qcdfile) {         // optional output ROOT file
  bool not_subtract_QCDbkgd=true;

  //  if(datahistos_inp.size()!=mchistos_inp.size()) {
  //    cout<<"Different number of histograms for data and MC"<<endl;
  //    return;
  //  }
  if(datahistos_inp.size()!=datahistos_spatial_inp.size()) {
    cout<<"Different number of histograms for data and data_spatial"<<endl;
    cout<<"the vect size is "<<datahistos_inp.size()<<endl;
    cout<<"the vect spatial size is "<<datahistos_spatial_inp.size()<<endl;
    return;
  }
  if(datahistos_spatial_inp.size()==0) {
    cout<<"No hist in data_spatial to compare"<<endl;
    return;
  }

  // exclude NULL pointers from histogram lists
  vector<TH1 *> datahistos;
  vector<TH1 *> datahistos_spatial;
  vector<TH1 *> mchistos;
  for(int i=0; i<datahistos_inp.size(); i++) {
    if(datahistos_inp[i] && datahistos_spatial_inp[i] && mchistos_inp[i]) {
      datahistos.push_back(datahistos_inp[i]);
      datahistos_spatial.push_back(datahistos_spatial_inp[i]);
      mchistos.push_back(mchistos_inp[i]);
    }
  }

  // 3d                                                    
  TH1 *histo_3d;                                            
  TH1 *histo_spatial_3d;                                    
  if(qcd_option==1){   // use 3D histogram for matrix method                         
    histo_3d=(TH1 *)datahistos_inp[1]->Clone();             
    histo_spatial_3d=(TH1 *)datahistos_spatial_inp[1]->Clone(); 
  }                       

  //get background plots
  TH1 *bkgd_zee, *bkgd_wtaunu, *bkgd_zee_wtaunu, *bkgd_wen_qcd;
  vector<TH1 *> bkgdhistos;
  Double_t entries_bkgd_zee, entries_bkgd_wtaunu, entries_bkgd_wen_qcd;
  if((!if_mc) && (bkgdhistos_inp.size()>0)){
    not_subtract_QCDbkgd=false;
    for(int i=0;  i<bkgdhistos_inp.size(); i++){
      bkgdhistos.push_back(bkgdhistos_inp[i]);
    }
    bkgd_zee=(TH1F *) bkgdhistos[0]->Clone();
    bkgd_wtaunu=(TH1F *) bkgdhistos[1]->Clone();

    bkgd_zee->GetXaxis()->SetRangeUser(xmin, xmax);
    bkgd_wtaunu->GetXaxis()->SetRangeUser(xmin, xmax);
    
    entries_bkgd_zee = bkgd_zee->Integral(bkgd_zee->GetXaxis()->FindBin(xmin), bkgd_zee->GetXaxis()->FindBin(xmax));
    entries_bkgd_wtaunu = bkgd_wtaunu->Integral(bkgd_wtaunu->GetXaxis()->FindBin(xmin), bkgd_wtaunu->GetXaxis()->FindBin(xmax));

  
  
    if (qcd_option==2) {  // use Jan's file
      bkgd_wen_qcd=(TH1F *) bkgdhistos[2]->Clone();
      bkgd_wen_qcd->GetXaxis()->SetRangeUser(xmin, xmax);
      entries_bkgd_wen_qcd= bkgd_wtaunu->Integral(bkgd_wen_qcd->GetXaxis()->FindBin(xmin), bkgd_wen_qcd->GetXaxis()->FindBin(xmax));
    }
  }

  //int vec_size = datahistos.size();
  int vec_size = 1;
  if (vec_size==0) {
    cout<<"No histograms to plot !!! (at least one pair of non-NULL pointers must exist)"<<endl;
    return;
  }
  int NPages = 1;
  int NPads = 0;
  int NPads_last = 0;

  if(vec_size>max_plots_per_page) {
    if(vec_size%max_plots_per_page==0) {
      NPages     = vec_size / max_plots_per_page;
      NPads_last = max_plots_per_page; 
      NPads      = max_plots_per_page;
    } else {
      NPages     = vec_size / max_plots_per_page + 1;
      NPads_last = vec_size%max_plots_per_page;
      NPads      = max_plots_per_page;
    }
  } else {
    NPads=vec_size;
    NPads_last=vec_size;
  }
//   cout << "Canvas "<<c->GetTitle()<<":  Nplots="<<vec_size
//        <<", NPages="<<NPages<<", Plots/page="<<NPads
//        <<" ("<<NPads_last<<")"<<endl;

  // loop thru pages
  for(int ipage=0; ipage<NPages; ipage++) {

    if(ps) ps->Off(); // temporarily disable printing to PS file
    stringstream name;
    name << cname;
    if(NPages>1) name << " (page "<<ipage<<")"; 
    TCanvas *c = new TCanvas(name.str().c_str(), "c", 50,10,700,800);
    //   cout << "Canvas "<<c->GetTitle()<<":  Nplots="<<vec_size
    //        <<", NPages="<<NPages<<", Plots/page="<<NPads
    //        <<" ("<<NPads_last<<")"<<endl;

    int istart=0, iend=vec_size;
    if(vec_size==1) { 
      if(make_chi2) c->Divide(1, 2);
      else c->Divide(1, 1);
    } else {
      if(NPages==1 || ipage==NPages-1) {
	if(make_chi2) c->Divide(2, NPads);
	else          c->Divide(1, NPads);
	istart=ipage*NPads;
	iend=istart+NPads_last;
      } else {
	if(make_chi2) c->Divide(2, NPads);
        else          c->Divide(1, NPads);
	istart=ipage*NPads;
	iend=istart+NPads;
      }
    }
  
    int ipad = 1;
    double chisq = 0.0;
    int nbins = 0;
    char word[50];
    bool plot_ok=false;

    // loop thru distributions for a given page
    for(int i=istart; i<iend; i++) {

    TH1 *h1 = (TH1F *)datahistos[i];
    TH1 *k1 = (TH1F *)mchistos[i];
    TProfile *h2 = dynamic_cast<TProfile *>(datahistos[i]);
    TProfile *k2 = dynamic_cast<TProfile *>(mchistos[i]);

    ///////////////////////////////////////////////////////////////
    // Substitute h1 with a TH1F copy and normalize this copy later
    // No need to normalzie TProfile histograms
    if(h2==0 && h1!=0) {
      TH1F *hist_new=(TH1F*)h1->Clone();;
      char new_name[1000];
      sprintf(new_name,"%s_copy",h1->GetName());
      hist_new->SetName(new_name);
      h1=hist_new;
    }
    // Substitute k1 with a TH1F copy and normalize this copy later
    // No need to normalzie TProfile histograms
    if(k2==0 && k1!=0) {
      TH1F *hist_new=(TH1F*)k1->Clone();
      char new_name[1000];
      sprintf(new_name,"%s_copy",k1->GetName());
      hist_new->SetName(new_name);
      k1=hist_new;
    }
    ///////////////////////////////////////////////////////////////
    
    if(h1==0 && h2==0) continue;
    if(k1==0 && k2==0) continue; 
    plot_ok=true; // both histograms exist

    TH1 *a1;
    TH1 *b1;
    TH1 *bkg_signal;

    if(h2 != 0 && k2 != 0) {

      // For profiles you DO NOT need to scale
      a1 = h2;
      b1 = k2;
    } else {
      TH1* h1_signal = (TH1F *)h1->Clone();
      bkg_signal = (TH1F *)h1->Clone();
      bkg_signal->Reset();

      string newname = (string)(h1->GetName());
      h1_signal->SetName(newname.c_str());
      h1_signal->Reset();

      if(qcd_option==1) {  // use eff and fake rate vs detector eta and pT
	TFile *file_fake_eff = TFile::Open("./fake_eff.root");
	TH2F *hist_fake=(TH2F *)gROOT->FindObject("fake");
	TH2F *hist_eff=(TH2F *)gROOT->FindObject("eff");
	plot::plot_without_background_3d(if_mc, histo_3d, histo_spatial_3d, h1_signal, bkg_signal, hist_fake, hist_eff, qcdfile);	
      } else 
      plot::plot_without_background(if_mc, h1, datahistos_spatial[i], h1_signal, bkg_signal);
      
//       // begin test code
//       {
//        
//       	// h1 = data (loose ?)
// 	// datahistos_spatial[i] = data (tight ?) why this one is an array while h1 is not ? 
// 	// h1_signal = has same binning/range as h1 but is empty so far
// 	//                     will become  Ntight from W (eff * N_W)
// 	// bkg_signal = has same binning/range as h1 but is empty so far
// 	//                    will become  Ntight  from background (fr * N_QCD)
// 	//plot::plot_without_background(if_mc, h1, datahistos_spatial[i], h1_signal, bkg_signal);
//         // instead do it by hand:
// 	//f/(e-f)  *  ( e * Nloose - Ntight)
// 	
//         double eff_temp;
// 	double eff_error_temp, fake_temp, fake_error_temp;
//         eff_temp=plot::eff_data;
//         eff_error_temp=plot::eff_error_data;
//         fake_temp=plot::fake_data;
//         fake_error_temp=plot::fake_error_data;
// 
// 	TCanvas c1("ctestcode");
// 	h1->Draw();
// 	               c1.Print("ctestcode.ps(");  // write canvas and keep the ps file open
// 	datahistos_spatial[i]->Draw();
// 	                c1.Print("ctestcode.ps");   // canvas is added to "c1.ps"
// 	bkg_signal->Draw();
// 	               c1.Print("ctestcode.ps");   // canvas is added to "c1.ps"
// 
// 
// 	bkg_signal=h1;
// 	bkg_signal->Draw();
// 	               c1.Print("ctestcode.ps");   // canvas is added to "c1.ps"
// 
// 	bkg_signal->Scale(eff_temp);
// 	bkg_signal->Draw();
// 	               c1.Print("ctestcode.ps");   // canvas is added to "c1.ps"
// 
// 	bkg_signal->Add(datahistos_spatial[i],-1);
// 	bkg_signal->Draw();
// 	               c1.Print("ctestcode.ps");   // canvas is added to "c1.ps"
// 
// 	bkg_signal->Scale(eff_temp/(eff_temp-fake_temp));
// 	bkg_signal->Draw();
// 	               c1.Print("ctestcode.ps");   // canvas is added to "c1.ps"
// 
// 	h1_signal->Draw();
// 	               c1.Print("ctestcode.ps");   // canvas is added to "c1.ps"
// 
// 	h1_signal = datahistos_spatial[i];
// 	h1_signal->Draw();
// 	               c1.Print("ctestcode.ps");   // canvas is added to "c1.ps"
// 
// 	h1_signal->Add(bkg_signal,-1);
// 
// 	h1_signal->Draw();
// 
// 	c1.Print("ctestcode.ps)");  // canvas is added to "c1.ps" and ps file is closed
// 
// 	} //end test code

      // set user range
      h1_signal->GetXaxis()->SetRangeUser(xmin, xmax);
      k1->GetXaxis()->SetRangeUser(xmin, xmax);


      // integrate for the given range
      Double_t entries_h1 = h1_signal->Integral(h1_signal->GetXaxis()->FindBin(xmin), h1_signal->GetXaxis()->FindBin(xmax));
      Double_t entries_k1 = k1->Integral(k1->GetXaxis()->FindBin(xmin), k1->GetXaxis()->FindBin(xmax));
      
      // add Z->ee & W->taunu bkgds
      TH1D* bkgd_zee_ns;
      TH1D* bkgd_wtaunu_ns;
      TH1D* bkgd_signal_ns;
      //cout<<zee_bkg_fraction<<"  "<<wtaunu_bkg_fraction<<endl;
      if(i==0 && !if_mc && (bkgdhistos_inp.size()>0)){
	bkgd_zee->Scale(zee_bkg_fraction*entries_k1/entries_bkgd_zee);
	bkgd_wtaunu->Scale(wtaunu_bkg_fraction*entries_k1/entries_bkgd_wtaunu);

	bkgd_zee_ns = (TH1D*)bkgd_zee->Clone();
	bkgd_wtaunu_ns = (TH1D*)bkgd_wtaunu->Clone();


    //cout<<"now will add from bkgd_wtaunu" <<bkgd_wtaunu->GetName()<<endl;
	k1->Add(bkgd_wtaunu,1);

    //cout<<"now will add from    bkgd_zee" <<bkgd_zee->GetName()<<endl;
	k1->Add(bkgd_zee,1);

	bkgd_zee_wtaunu=(TH1F *)bkgd_zee->Clone();
	bkgd_zee_wtaunu->Add(bkgd_wtaunu,1);
	entries_k1 = k1->Integral(k1->GetXaxis()->FindBin(xmin), k1->GetXaxis()->FindBin(xmax));
      }
      k1->Scale((entries_h1)/entries_k1); //where the PMCS scaling is done
      if (!if_mc) {
	bkgd_zee_wtaunu->Scale(entries_h1/entries_k1);
	bkgd_zee->Scale(entries_h1/entries_k1);

	if (qcd_option!=2){   // for background subtraction using matrix method
	  bkgd_zee->Add(bkg_signal);
	  bkgd_zee_wtaunu->Add(bkg_signal);
	  
	  bkgd_signal_ns = (TH1D*)bkg_signal->Clone();//(TH1D*)bkgd_wen_qcd->Clone();
	  bkgd_signal_ns->Scale(entries_k1/entries_h1);
          // set QCD bkgd errors to zero for the purpose of chi plots
          // as discussed at M(W) meeting 10/13/10
          // and then add it to k1	 
          for(int i=0; i<=bkg_signal->GetEntries(); i++){
             bkg_signal->SetBinError(i,0.0);
          }
          k1->Add(bkg_signal);
	}
	else if (qcd_option==2) {
	  double entries_bkg_signal = bkg_signal->Integral(bkg_signal->GetXaxis()->FindBin(xmin), bkg_signal->GetXaxis()->FindBin(xmax));
	  bkgd_wen_qcd->Scale(entries_bkg_signal/entries_bkgd_wen_qcd);
	  bkgd_zee->Add(bkgd_wen_qcd);
	  bkgd_zee_wtaunu->Add(bkgd_wen_qcd);
	  k1->Add(bkgd_wen_qcd);
	
	  bkgd_signal_ns = (TH1D*)bkgd_wen_qcd->Clone();
	  bkgd_signal_ns->Scale(entries_k1/entries_h1);
	}
      }     

      a1 = datahistos_spatial[i];
      b1 = k1;
      
      
      if (outputbkg && (cname=="wmass" || cname == "elecpT" || cname=="Met")) { 
	TFile *tempbackout = new TFile("fitter_backgrounds.root","update");
	bkgd_signal_ns->Write("bkgd_signal_"+cname);
	bkgd_zee_ns->Write("bkgd_zee_"+cname);
	bkgd_wtaunu_ns->Write("bkgd_wtaunu_"+cname); 
	tempbackout->Close();
      }
    }
    
    //make comparison plots
    c -> cd(ipad);
    a1->SetLineColor(plot::data_color);
    a1->SetMarkerColor(plot::data_color);
    a1->SetMarkerStyle(plot::data_marker);
    a1->SetMarkerSize(0.4);
    a1->GetXaxis()->SetRangeUser(xmin, xmax);
    a1->Draw("pe");//red (data) histogram
   
    b1->SetName(TString(TString(a1->GetName())+"_hidden").Data()); 
    b1->SetLineColor(plot::mc_color);
    b1->SetMarkerColor(plot::mc_color);
    b1->SetMarkerStyle(plot::mc_marker);
    b1->SetMarkerSize(0.4);
    b1->SetLineWidth(2);
    b1->Draw("hist,same");//blue histogram (MC/PMCS)

    if(i==0 && !if_mc && (bkgdhistos_inp.size()>1)){
      bkgd_zee_wtaunu->SetName(TString(TString(a1->GetName())+"_bkgd_zee_wtaunu").Data());
      bkgd_zee_wtaunu->SetFillColor(22); //3
      bkgd_zee_wtaunu->Draw("same & histo");
      bkgd_zee->SetName(TString(TString(a1->GetName())+"_bkgd_zee").Data());
      bkgd_zee->SetFillColor(32);  //6
      bkgd_zee->Draw("same & histo");

      if(qcd_option!=2) {    // for background subtraction using matrix method
        bkg_signal->SetName(TString(TString(a1->GetName())+"_bkg_signal").Data());
	bkg_signal->SetFillColor(42);
	bkg_signal->Draw("same & histo");
      } else if (qcd_option==2) {
        bkgd_wen_qcd->SetName(TString(TString(a1->GetName())+"_bkgd_wen_qcd").Data());
	bkgd_wen_qcd->SetFillColor(42);
       	bkgd_wen_qcd->Draw("same & histo");
      }
    }
    plot::find_chi2(a1, b1, xmin, xmax, chisq, nbins);

    TLegend *leg1 = new TLegend(0.55,0.7,0.8,0.88,NULL,"brNDC");
    leg1->SetTextSize(0.05);
    leg1->SetLineColor(0);
    leg1->SetLineStyle(1);
    leg1->SetLineWidth(1);
    leg1->SetFillColor(0);
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetFillColor(0);
    leg1->SetTextSize(0.035);

    if(!not_show_chi2) {
      sprintf(word, "#chi^{2}/ndf = %.1f/%d", chisq, nbins);
      leg1->SetHeader(word);
    }
    TLegendEntry *dataentry=leg1->AddEntry(a1, plot::data_label, "pl");
    if(dataentry) {
      dataentry->SetTextColor(plot::data_color);
      dataentry->SetMarkerSize(3);
    }
    TLegendEntry *mcentry=leg1->AddEntry(b1, plot::mc_label, "pl");
    if(mcentry) {
      mcentry->SetTextColor(plot::mc_color);
      mcentry->SetMarkerSize(3);
    }
    if(i==0 && !if_mc && (bkgdhistos_inp.size()>1)){
      TLegendEntry *bkgd_zee_wtaunu_entry=leg1->AddEntry(bkgd_zee_wtaunu, "W->#tau#nu", "f");
      if(bkgd_zee_wtaunu_entry) {
	bkgd_zee_wtaunu_entry->SetTextColor(22);
	bkgd_zee_wtaunu_entry->SetMarkerColor(22);
	bkgd_zee_wtaunu_entry->SetMarkerSize(22);
      }
      TLegendEntry *bkgd_zee_entry=leg1->AddEntry(bkgd_zee, "Z->ee", "f");
      if(bkgd_zee_entry) {
	bkgd_zee_entry->SetTextColor(32);
	bkgd_zee_entry->SetMarkerColor(32);
	bkgd_zee_entry->SetMarkerSize(32);
      }
      TLegendEntry *bkg_signal_entry;
      if (qcd_option != 2){  // for background subtraction using matrix method
	bkg_signal_entry=leg1->AddEntry(bkg_signal, "QCD", "f");
      } else if (qcd_option ==2 ){
	bkg_signal_entry=leg1->AddEntry(bkgd_wen_qcd, "QCD", "f");
      }
      if(bkg_signal_entry) {
        bkg_signal_entry->SetTextColor(42);
        bkg_signal_entry->SetMarkerColor(42);
        bkg_signal_entry->SetMarkerSize(42);
      }
    }
    leg1->Draw();
    
    // if we want to write out each plot into a eps file
    if(write_out_each_plot) {
      gStyle->SetTitleFillColor(0);
      gStyle->SetPadLeftMargin(.16);
      TCanvas *c_temp = new TCanvas("c_temp", "canvas", 100, 200, 700, 800);
      a1->Draw("pe");
      b1->SetLineWidth(2);
      b1->Draw("hist,same");
      if(i==0 && !if_mc && (bkgdhistos_inp.size()>1)){
        bkgd_zee_wtaunu->SetFillColor(22); //3
        bkgd_zee_wtaunu->Draw("same & histo");
        bkgd_zee->SetFillColor(32);  //6
        bkgd_zee->Draw("same & histo");

        if(qcd_option!=2) {    // for background subtraction using matrix method
          bkg_signal->SetFillColor(42);
          bkg_signal->Draw("same & histo");
        } else if (qcd_option==2) {
          bkgd_wen_qcd->SetFillColor(42);
          bkgd_wen_qcd->Draw("same & histo");
        }
      }
      leg1->Draw();
      c_temp->Update();

      gROOT->ProcessLine(".! mkdir plots/");
     
      string eps_file_name = "plots/" + (string)(a1->GetName()) + ".eps";
      c_temp->Print(eps_file_name.c_str());
      string macro_file_name = "plots/" + (string)(a1->GetName()) + ".C";
      c_temp->Print(macro_file_name.c_str());
      delete c_temp;
    }

      if(make_chi2) {
	ipad ++;
	c -> cd(ipad);
	plot::plot_with_chi2(a1, b1, xmin, xmax);
      }
      
      ipad++;     
    } // end of for(i=... loop

    // start a new page only if at least one histogram exists
    if(plot_ok) {
      if(ps) { ps->On(); ps->NewPage(); }
      c->Update();
      if(file) file->Append(c);
    }
  } // end of for(ipage=... loop

  // enable printing to PS file again
  if(ps) ps->On(); 
}

// special function for plotting mean or width of eta-imbalance (xi-imbalance) for different pT regions
// where a1 and b1 are vectors of eta-imbalance or xi-imbalance histograms for data or MC
// c1 is vector of Z pT distribution for given range
// value_option to control for mean or sigma
// plot_option to control for eta-imbalance or xi-imbalance
void plot::plot_MeanSigma_pTeeBin(TString cname, 
				  vector<TH1 *> a1, 
				  vector<TH1 *> b1, 
				  vector<TH1 *> c1, 
				  TGraphErrors *ge1, 
				  TGraphErrors *ge2, 
				  TGraphErrors *ge_chi, 
				  TGraphErrors *ge1_fitted, 
				  TGraphErrors *ge2_fitted, 
				  TGraphErrors *ge_fitted_chi, 
				  int value_option, // 0=MEAN, 1=RMS
				  int plot_option,  // 0=Eta Imbalance, 1=Xi Imbalance
				  bool make_chi2, 
				  double& chi2, 
				  double& chi2_fitted, 
				  TPostScript *ps,       // optional output PS file
				  int max_plots_per_page,// optional max. num. of rows per canvas
				  TFile *file) {         // optional output ROOT file
  if(a1.size()>b1.size() || a1.size()>c1.size()) {
    cout << "Vectors a1 ,b1, c1 have incompatible sizes !!!" << endl;
    return;
  }
  //  double pT_center[10] = {0.5, 1.5, 2.5, 3.5, 4.5, 6., 8.5, 12., 17., 25.};
  double pT_center[10];
  double pT_err[10];
  double mean_Data[10], mean_err_Data[10], mean_MC[10], mean_err_MC[10], mean_diff_chi[10], mean_err_diff_chi[10];
  double fitted_mean_Data[10], fitted_mean_err_Data[10], fitted_mean_MC[10], fitted_mean_err_MC[10], fitted_mean_diff_chi[10], fitted_mean_err_diff_chi[10];
  int NBins;

  NBins=0;
  chi2 = 0.;
  chi2_fitted = 0.;
  for(int i=0; i<a1.size(); i++) {

    if( a1[i]==0 || b1[i]==0 || c1[i]==0 ) continue;

    pT_center[NBins] = c1[i]->GetMean();
    pT_err[NBins] = c1[i]->GetMeanError();

    TF1 *g1 = new TF1("g1","gaus", -25., 25.);
    a1[i]->Fit(g1,"QR0");
    TF1 *g2 = new TF1("g2","gaus", -25., 25.);
    b1[i]->Fit(g2,"QR0");

    if(value_option==0) {  // for mean
      mean_Data[NBins] = a1[i]->GetMean();
      mean_MC[NBins] = b1[i]->GetMean();
      mean_err_Data[NBins] = a1[i]->GetMeanError();
      mean_err_MC[NBins] = b1[i]->GetMeanError();
      fitted_mean_Data[NBins] = g1->GetParameter(1);
      fitted_mean_MC[NBins] = g2->GetParameter(1);
      fitted_mean_err_Data[NBins] = g1->GetParError(1);
      fitted_mean_err_MC[NBins] = g2->GetParError(1);
    } else {  // for width
      mean_Data[NBins] = a1[i]->GetRMS();
      mean_MC[NBins] = b1[i]->GetRMS();
      mean_err_Data[NBins] = a1[i]->GetRMSError();
      mean_err_MC[NBins] = b1[i]->GetRMSError();
      fitted_mean_Data[NBins] = g1->GetParameter(2);
      fitted_mean_MC[NBins] = g2->GetParameter(2);
      fitted_mean_err_Data[NBins] = g1->GetParError(2);
      fitted_mean_err_MC[NBins] = g2->GetParError(2);
    }

    chi2 += pow((mean_Data[NBins]-mean_MC[NBins])/sqrt(mean_err_Data[NBins]*mean_err_Data[NBins]+mean_err_MC[NBins]*mean_err_MC[NBins]), 2);
    chi2_fitted += pow((fitted_mean_Data[NBins]-fitted_mean_MC[NBins])/sqrt(fitted_mean_err_Data[NBins]*fitted_mean_err_Data[NBins]+fitted_mean_err_MC[NBins]*fitted_mean_err_MC[NBins]), 2);
    
    mean_diff_chi[NBins] = (mean_Data[NBins]-mean_MC[NBins])/sqrt(mean_err_Data[NBins]*mean_err_Data[NBins]+mean_err_MC[NBins]*mean_err_MC[NBins]);
    mean_err_diff_chi[NBins] = 1.; // error on chi is always 1

    fitted_mean_diff_chi[NBins] = (fitted_mean_Data[NBins]-
				   fitted_mean_MC[NBins])/
      sqrt(fitted_mean_err_Data[NBins]*fitted_mean_err_Data[NBins]+
	   fitted_mean_err_MC[NBins]*fitted_mean_err_MC[NBins]);
    fitted_mean_err_diff_chi[NBins] = 1.; // error on chi is always 1
    delete g1;
    delete g2;

    NBins++;

  } // loop over all histograms

  if(NBins==0) return; // nothing to plot
 
  ge1 = new TGraphErrors(NBins, pT_center, mean_Data, pT_err, mean_err_Data);
  ge2 = new TGraphErrors(NBins, pT_center, mean_MC, pT_err, mean_err_MC);
  ge_chi = new TGraphErrors(NBins, pT_center, mean_diff_chi, pT_err, mean_err_diff_chi);
  ge1_fitted = new TGraphErrors(NBins, pT_center, fitted_mean_Data, pT_err, fitted_mean_err_Data);
  ge2_fitted = new TGraphErrors(NBins, pT_center, fitted_mean_MC, pT_err, fitted_mean_err_MC);
  ge_fitted_chi = new TGraphErrors(NBins, pT_center, fitted_mean_diff_chi, pT_err, fitted_mean_err_diff_chi);

  // set title
  if(plot_option==0) {
    if(value_option==0) {
      ge1->SetTitle("Mean of Eta-Imbalance");
      ge1_fitted->SetTitle("Fitted Mean of Eta-Imbalance");
    } else {
      ge1->SetTitle("Width of Eta-Imbalance");
      ge1_fitted->SetTitle("Fitted Width of Eta-Imbalance");
    }
  } else {
    if(value_option==0) {
      ge1->SetTitle("Mean of Xi-Imbalance");
      ge1_fitted->SetTitle("Fitted Mean of Xi-Imbalance");
    } else {
      ge1->SetTitle("Width of Xi-Imbalance");
      ge1_fitted->SetTitle("Fitted Width of Xi-Imbalance");
    }
  }

  int NPages = 1;
  int NPads = 0;
  int NPads_last = 0;
  int vec_size = 2;  // Just 2 plots: index=0 --> Non-fitted, index=1 --> Fitted

  if(vec_size>max_plots_per_page) {
    if(vec_size%max_plots_per_page==0) {
      NPages     = vec_size / max_plots_per_page;
      NPads_last = max_plots_per_page; 
      NPads      = max_plots_per_page;
    } else {
      NPages     = vec_size / max_plots_per_page + 1;
      NPads_last = vec_size%max_plots_per_page;
      NPads      = max_plots_per_page;
    }
  } else {
    NPads=vec_size;
    NPads_last=vec_size;
  }

  // loop thru pages 
  for(int ipage=0; ipage<NPages; ipage++) {

    if(ps) ps->Off(); // temporarily disable printing to PS file
    stringstream name;
    name << cname;
    if(NPages>1) name << " (page "<<ipage<<")"; 
    TCanvas *c = new TCanvas(name.str().c_str(), "c", 50,10,700,800);
    //   cout << "Canvas "<<c->GetTitle()<<":  Nplots="<<vec_size
    //        <<", NPages="<<NPages<<", Plots/page="<<NPads
    //        <<" ("<<NPads_last<<")"<<endl;

    int istart=0, iend=vec_size;
    if(vec_size==1) { 
      if(make_chi2) c->Divide(1, 2);
      else c->Divide(1, 1);
    } else {
      if(NPages==1 || ipage==NPages-1) {
	if(make_chi2) c->Divide(2, NPads);
	else          c->Divide(1, NPads);
	istart=ipage*NPads;
	iend=istart+NPads_last;
      } else {
	if(make_chi2) c->Divide(2, NPads);
        else          c->Divide(1, NPads);
	istart=ipage*NPads;
	iend=istart+NPads;
      }
    }
  
    int ipad = 1;

    // loop thru distributions for a given page
    for(int i=istart; i<iend; i++) {

      //      cout << "ipage="<<ipage<<", iplot="<<i<<", ipad="<<ipad<<endl<<flush;

      switch(i) {
      case 0: { // Mean or Width of eta(xi)-imbalance
	c->cd(ipad);
	ge1->SetLineColor(kRed);
	ge1->SetMarkerColor(kRed);
	ge1->SetMarkerStyle(21);   // filled square
	ge1->SetMarkerSize(0.4);
	ge1->Draw("AP");
	ge2->SetLineColor(kBlue);
	ge2->SetMarkerColor(kBlue);
	ge2->SetMarkerStyle(25);   // open square
	ge2->SetMarkerSize(0.4);
	ge2->Draw("P");
	
 	TLegend *leg1 = new TLegend(0.55,0.7,0.8,0.88,NULL,"brNDC");
	leg1->SetTextSize(0.05);
	leg1->SetLineColor(1);
	leg1->SetLineStyle(1);
	leg1->SetLineWidth(1);
	leg1->SetFillColor(0);
	leg1->SetFillStyle(0);
	leg1->SetBorderSize(0);
	leg1->SetFillColor(0);
	leg1->SetTextSize(0.035);
  
	char word[50];
	if(!not_show_chi2) {
	  sprintf(word, "#chi^{2}/ndf = %.1f/%d", chi2, NBins);
	  leg1->SetHeader(word);
	}
	TLegendEntry *dataentry=leg1->AddEntry(ge1, plot::data_label, "pl");
	if(dataentry) {
	  dataentry->SetTextColor(plot::data_color);
	  dataentry->SetMarkerSize(3);
	}
	TLegendEntry *mcentry=leg1->AddEntry(ge2, plot::mc_label, "pl");
	if(mcentry) {
	  mcentry->SetTextColor(plot::mc_color);
	  mcentry->SetMarkerSize(3);
	}
	leg1->Draw();

	// make chi distribution
	if(make_chi2) {
	  ipad ++;
	  c->cd(ipad);
	  ge_chi->SetTitle("#chi distribution");
	  ge_chi->SetLineColor(kBlack);
	  ge_chi->SetMarkerColor(kRed);
	  ge_chi->SetMarkerStyle(20);   // filled circle
	  ge_chi->SetMarkerSize(0.4);
	  ge_chi->Draw("AP");
	}
	break;
      }
      case 1: { // Fitted Mean or Fitted Width of eta(xi)-imbalance
	c->cd(ipad);
	ge1_fitted->SetLineColor(kRed);
	ge1_fitted->SetMarkerColor(kRed);
	ge1_fitted->SetMarkerStyle(21);    // filled square
	ge1_fitted->SetMarkerSize(0.4);
	ge1_fitted->Draw("AP");
	ge2_fitted->SetLineColor(kBlue);
	ge2_fitted->SetMarkerColor(kBlue);
	ge2_fitted->SetMarkerStyle(25);    // open square
	ge2_fitted->SetMarkerSize(0.4);
	ge2_fitted->Draw("P");
	
	TLegend *leg2 = new TLegend(0.55,0.7,0.8,0.88,NULL,"brNDC");
	leg2->SetTextSize(0.05);
	leg2->SetLineColor(1);
	leg2->SetLineStyle(1);
	leg2->SetLineWidth(1);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->SetBorderSize(0);
	leg2->SetFillColor(0);
	leg2->SetTextSize(0.035);
	
	char word[50];
	if(!not_show_chi2) {
	  sprintf(word, "#chi^{2}/ndf = %.1f/%d", chi2_fitted, NBins);
	  leg2->SetHeader(word);
	}
	TLegendEntry *dataentry=leg2->AddEntry(ge1_fitted, plot::data_label, "pl");
	if(dataentry) {
	  dataentry->SetTextColor(plot::data_color);
	  dataentry->SetMarkerSize(3);
	}
	TLegendEntry *mcentry=leg2->AddEntry(ge2_fitted, plot::mc_label, "pl");
	if(mcentry) {
	  mcentry->SetTextColor(plot::mc_color);
	  mcentry->SetMarkerSize(3);
	}
	leg2->Draw();
	
	// make chi distribution
	if(make_chi2) {
	  ipad ++;
	  c -> cd(ipad);
	  ge_fitted_chi->SetTitle("#chi distribution");
	  ge_fitted_chi->SetLineColor(kBlack);
	  ge_fitted_chi->SetMarkerColor(kRed);
	  ge_fitted_chi->SetMarkerStyle(20);   // filled circle
	  ge_fitted_chi->SetMarkerSize(0.4);
	  ge_fitted_chi->Draw("AP");
	}
	break;
      }
      }; // end of switch(...)
      
      ipad++;     
    } // end of for(istart=... loop

    // start a new page
    if(ps) { ps->On(); ps->NewPage(); }
    c->Update();
    if(file) file->Append(c);
  } // end of for(ipage=... loop

  // enable printing to PS file again
  if(ps) ps->On(); 

  TString plot_string = "Eta-Imbalance";
  if(plot_option==1) plot_string = "Xi-Imbalance";
  TString value_string1 = "Chi2 for Mean of ";
  if(value_option==1) value_string1 = "Chi2 for Width of ";
  TString value_string2 = "Chi2 for Fitted Mean of ";
  if(value_option==1) value_string2 = "Chi2 for Fitted Width of ";

  cout<<"============================================="<<endl;
  cout<<value_string1<<plot_string<<endl;
  for(int i=0; i<a1.size(); i++) {
    cout<<"  Data: "<<mean_Data[i]<<" +- "<<mean_err_Data[i]<<" MC: "<<mean_MC[i]<<" +- "<<mean_err_MC[i]<<" chi2="<<pow((mean_Data[i]-mean_MC[i])/sqrt(mean_err_Data[i]*mean_err_Data[i]+mean_err_MC[i]*mean_err_MC[i]), 2)<<endl;
  }
  cout<<"Overall chi2 = "<<chi2<<endl;
  cout<<value_string2<<plot_string<<endl;
  for(int i=0; i<a1.size(); i++) {
    cout<<"  Data: "<<fitted_mean_Data[i]<<" +- "<<fitted_mean_err_Data[i]<<" MC: "<<fitted_mean_MC[i]<<" +- "<<fitted_mean_err_MC[i]<<" chi2="<<pow((fitted_mean_Data[i]-fitted_mean_MC[i])/sqrt(fitted_mean_err_Data[i]*fitted_mean_err_Data[i]+fitted_mean_err_MC[i]*fitted_mean_err_MC[i]), 2)<<endl;
  }
  cout<<"Overall chi2 = "<<chi2_fitted<<endl;
}

// special function for plotting sigma of Phi(Z)-Phi(Recoil)
// (distribution centered at PI) from histogramo of |Phi(Z)-Phi(Recoil)|, 
// where a1 and b1 are vectors of |Phi(Z)-Phi(Recoil)| histograms for data or MC
// c1 is vector of Z pT distribution for given range.
void plot::plot_SigmaDeltaPhiZRecoil_pTeeBin(TString cname,
					     vector<TH1 *> a1, 
					     vector<TH1 *> b1, 
					     vector<TH1 *> c1, 
					     TGraphErrors *ge1, 
					     TGraphErrors *ge2, 
					     TGraphErrors *ge_chi, 
					     TGraphErrors *ge1_fitted, 
					     TGraphErrors *ge2_fitted, 
					     TGraphErrors *ge_fitted_chi, 
					     bool make_chi2, 
					     double& chi2, 
					     double& chi2_fitted, 
					     TPostScript *ps,       // optional output PS file
					     int max_plots_per_page,// optional max. num. of rows per canvas
					     TFile *file) {         // optional output ROOT file
  const Int_t NBins = a1.size();
  //  double pT_center[10] = {0.5, 1.5, 2.5, 3.5, 4.5, 6., 8.5, 12., 17., 25.};
  double pT_center[10] = {0.};
  double pT_err[10] = {0.};
  for(int i=0; i<NBins; i++) {
    pT_center[i] = c1[i]->GetMean();
    pT_err[i] = c1[i]->GetMeanError();
  }

  double sigma_Data[10], sigma_err_Data[10], sigma_MC[10], sigma_err_MC[10], sigma_diff_chi[10], sigma_err_diff_chi[10];
  double fitted_sigma_Data[10], fitted_sigma_err_Data[10], fitted_sigma_MC[10], fitted_sigma_err_MC[10], fitted_sigma_diff_chi[10], fitted_sigma_err_diff_chi[10];
  chi2 = 0., chi2_fitted = 0.;

  for(int i=0; i<a1.size(); i++) { // loop over all histograms

    // for fitted width
    TF1 *g1 = new TF1("g1","gaus", 0., TMath::Pi());
    g1->FixParameter(1, TMath::Pi()); // distribution centered at PI
    a1[i]->Fit(g1,"QR0");
    TF1 *g2 = new TF1("g2","gaus", 0., TMath::Pi());
    g2->FixParameter(1, TMath::Pi()); // distribution centered at PI
    b1[i]->Fit(g2,"QR0");

    fitted_sigma_Data[i] = g1->GetParameter(2);
    fitted_sigma_MC[i] = g2->GetParameter(2);
    fitted_sigma_err_Data[i] = g1->GetParError(2);
    fitted_sigma_err_MC[i] = g2->GetParError(2);

    double contri, totalentries;

    // for unfolded histogram width - DATA (skip underflows and overflows)
    contri=0.0;
    totalentries=0.0;
    for(int k=1; k<=a1[i]->GetNbinsX(); k++) {
        double bin_contri = a1[i]->GetBinContent(k)* pow(a1[i]->GetBinCenter(k) - TMath::Pi(), 2);
        contri += bin_contri;
        totalentries += a1[i]->GetBinContent(k);
    }
    sigma_Data[i] = 0.0;
    sigma_err_Data[i] = 0.0;
    if(totalentries>0) {
      sigma_Data[i] = sqrt(contri/totalentries);
      sigma_err_Data[i] = sigma_Data[i]/sqrt(2*totalentries);
    }

    // for unfolded histogram width - MC (skip underflows and overflows)
    contri=0.0;
    totalentries=0.0;
    for(int k=1; k<=b1[i]->GetNbinsX(); k++) {
        double bin_contri = b1[i]->GetBinContent(k)* pow(b1[i]->GetBinCenter(k) - TMath::Pi(), 2);
        contri += bin_contri;
        totalentries += b1[i]->GetBinContent(k);
    }
    sigma_MC[i] = 0.0;
    sigma_err_MC[i] = 0.0;
    if(totalentries>0) {
      sigma_MC[i] = sqrt(contri/totalentries);
      sigma_err_MC[i] = sigma_MC[i]/sqrt(2*totalentries);
    }

    // calculate CHI2
    sigma_diff_chi[i] = 0.0;
    sigma_err_diff_chi[i] = 1.; // error on chi is always 1
    fitted_sigma_diff_chi[i] = 0.0;
    fitted_sigma_err_diff_chi[i] = 1.; // error on chi is always 1
    if(sigma_err_Data[i]>0 && sigma_err_MC[i]>0) {
      chi2 += pow((sigma_Data[i]-sigma_MC[i])/sqrt(sigma_err_Data[i]*sigma_err_Data[i]+sigma_err_MC[i]*sigma_err_MC[i]), 2);
      sigma_diff_chi[i] = (sigma_Data[i]-sigma_MC[i])/sqrt(sigma_err_Data[i]*sigma_err_Data[i]+sigma_err_MC[i]*sigma_err_MC[i]);
    }

    if(fitted_sigma_err_Data[i]>0 && fitted_sigma_err_MC[i]) {
      chi2_fitted += pow((fitted_sigma_Data[i]-fitted_sigma_MC[i])/sqrt(fitted_sigma_err_Data[i]*fitted_sigma_err_Data[i]+fitted_sigma_err_MC[i]*fitted_sigma_err_MC[i]), 2);
      fitted_sigma_diff_chi[i] = (fitted_sigma_Data[i]-fitted_sigma_MC[i])/sqrt(fitted_sigma_err_Data[i]*fitted_sigma_err_Data[i]+fitted_sigma_err_MC[i]*fitted_sigma_err_MC[i]);
    }
      
    delete g1;
    delete g2;
  } // loop over all histograms
  
  ge1 = new TGraphErrors(NBins, pT_center, sigma_Data, pT_err, sigma_err_Data);
  ge2 = new TGraphErrors(NBins, pT_center, sigma_MC, pT_err, sigma_err_MC);
  ge_chi = new TGraphErrors(NBins, pT_center, sigma_diff_chi, pT_err, sigma_err_diff_chi);
  ge1_fitted = new TGraphErrors(NBins, pT_center, fitted_sigma_Data, pT_err, fitted_sigma_err_Data);
  ge2_fitted = new TGraphErrors(NBins, pT_center, fitted_sigma_MC, pT_err, fitted_sigma_err_MC);
  ge_fitted_chi = new TGraphErrors(NBins, pT_center, fitted_sigma_diff_chi, pT_err, fitted_sigma_err_diff_chi);

  // set title
  ge1->SetTitle("Width of Phi-Imbalance");
  ge1_fitted->SetTitle("Fitted Width of Phi-Imbalance");

  int NPages = 1;
  int NPads = 0;
  int NPads_last = 0;
  int vec_size = 2;  // Just 2 plots

  if(vec_size>max_plots_per_page) {
    if(vec_size%max_plots_per_page==0) {
      NPages     = vec_size / max_plots_per_page;
      NPads_last = max_plots_per_page; 
      NPads      = max_plots_per_page;
    } else {
      NPages     = vec_size / max_plots_per_page + 1;
      NPads_last = vec_size%max_plots_per_page;
      NPads      = max_plots_per_page;
    }
  } else {
    NPads=vec_size;
    NPads_last=vec_size;
  }
//   cout << "Canvas "<<c->GetTitle()<<":  Nplots="<<vec_size
//        <<", Npages="<<NPages<<", Plots/page="<<NPads
//        <<" ("<<NPads_last<<")"<<endl;

  // loop thru pages 
  for(int ipage=0; ipage<NPages; ipage++) {

    if(ps) ps->Off(); // temporarily disable printing to PS file
    stringstream name;
    name << cname;
    if(NPages>1) name << " (page "<<ipage<<")"; 
    TCanvas *c = new TCanvas(name.str().c_str(), "c", 50,10,700,800);
    //   cout << "Canvas "<<c->GetTitle()<<":  Nplots="<<vec_size
    //        <<", NPages="<<NPages<<", Plots/page="<<NPads
    //        <<" ("<<NPads_last<<")"<<endl;

    int istart=0, iend=vec_size;
    if(ipage>0 && ps) ps->NewPage();
    if(vec_size==1) { 
      if(make_chi2) c->Divide(1, 2);
      else c->Divide(1, 1);
    } else {
      if(NPages==1 || ipage==NPages-1) {
	if(make_chi2) c->Divide(2, NPads);
	else          c->Divide(1, NPads);
	istart=ipage*NPads;
	iend=istart+NPads_last;
      } else {
	if(make_chi2) c->Divide(2, NPads);
        else          c->Divide(1, NPads);
	istart=ipage*NPads;
	iend=istart+NPads;
      }
    }
  
    int ipad = 1;

    // loop thru distributions for a given page
    for(int i=istart; i<iend; i++) {

      //      cout << "ipage="<<ipage<<", iplot="<<i<<", ipad="<<ipad<<endl<<flush;
      switch(i) {
      case 0: { // Width of Phi-imbalance
	c->cd(ipad);
	ge1->SetLineColor(plot::data_color);
	ge1->SetMarkerColor(plot::data_color);
	ge1->SetMarkerStyle(plot::data_marker);
	ge1->SetMarkerSize(0.4);
	ge1->Draw("AP");
	ge2->SetLineColor(plot::mc_color);
	ge2->SetMarkerColor(plot::mc_color);
	ge2->SetMarkerStyle(plot::mc_marker);
	ge2->SetMarkerSize(0.4);
	ge2->Draw("P");
	
 	TLegend *leg1 = new TLegend(0.55,0.7,0.8,0.88,NULL,"brNDC");
	leg1->SetTextSize(0.05);
	leg1->SetLineColor(1);
	leg1->SetLineStyle(1);
	leg1->SetLineWidth(1);
	leg1->SetFillColor(0);
	leg1->SetFillStyle(0);
	leg1->SetBorderSize(0);
	leg1->SetFillColor(0);
	leg1->SetTextSize(0.035);
  
	char word[50];
	if(!not_show_chi2) {
	  sprintf(word, "#chi^{2}/ndf = %.1f/%d", chi2, NBins);
	  leg1->SetHeader(word);
	}
	TLegendEntry *dataentry=leg1->AddEntry(ge1, plot::data_label, "pl");
	if(dataentry) {
	  dataentry->SetTextColor(plot::data_color);
	  dataentry->SetMarkerSize(3);
	}
	TLegendEntry *mcentry=leg1->AddEntry(ge2, plot::mc_label, "pl");
	if(mcentry) {
	  mcentry->SetTextColor(plot::mc_color);
	  mcentry->SetMarkerSize(3);
	}
	leg1->Draw();

	// make chi distribution
	if(make_chi2) {
	  ipad ++;
	  c->cd(ipad);
	  ge_chi->SetTitle("#chi distribution");
	  ge_chi->SetLineColor(kBlack);
	  ge_chi->SetMarkerColor(kRed);
	  ge_chi->SetMarkerStyle(20);   // filled circle
	  ge_chi->SetMarkerSize(0.4);
	  ge_chi->Draw("AP");
	}
	break;
      }
      case 1: { // Fitted Width of Phi-imbalance
	c->cd(ipad);
	ge1_fitted->SetLineColor(plot::data_color);
	ge1_fitted->SetMarkerColor(plot::data_color);
	ge1_fitted->SetMarkerStyle(plot::data_marker);    // filled square
	ge1_fitted->SetMarkerSize(0.4);
	ge1_fitted->Draw("AP");
	ge2_fitted->SetLineColor(plot::mc_color);
	ge2_fitted->SetMarkerColor(plot::mc_color);
	ge2_fitted->SetMarkerStyle(plot::mc_marker);    // open square
	ge2_fitted->SetMarkerSize(0.4);
	ge2_fitted->Draw("P");
	
	TLegend *leg2 = new TLegend(0.55,0.7,0.8,0.88,NULL,"brNDC");
	leg2->SetTextSize(0.05);
	leg2->SetLineColor(1);
	leg2->SetLineStyle(1);
	leg2->SetLineWidth(1);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->SetBorderSize(0);
	leg2->SetFillColor(0);
	leg2->SetTextSize(0.035);
	
	char word[50];
	if(!not_show_chi2) {
	  sprintf(word, "#chi^{2}/ndf = %.1f/%d", chi2_fitted, NBins);
	  leg2->SetHeader(word);
	}
	TLegendEntry *dataentry=leg2->AddEntry(ge1_fitted, plot::data_label, "pl");
	if(dataentry) {
	  dataentry->SetTextColor(plot::data_color);
	  dataentry->SetMarkerSize(3);
	}
	TLegendEntry *mcentry=leg2->AddEntry(ge2_fitted, plot::mc_label, "pl");
	if(mcentry) {
	  mcentry->SetTextColor(plot::mc_color);
	  mcentry->SetMarkerSize(3);
	}
	leg2->Draw();
	
	// make chi distribution
	if(make_chi2) {
	  ipad ++;
	  c -> cd(ipad);
	  ge_fitted_chi->SetTitle("#chi distribution");
	  ge_fitted_chi->SetLineColor(kBlack);
	  ge_fitted_chi->SetMarkerColor(kRed);
	  ge_fitted_chi->SetMarkerStyle(20);   // filled circle
	  ge_fitted_chi->SetMarkerSize(0.4);
	  ge_fitted_chi->Draw("AP");
	}
	break;
      }
      }; // end of switch(...)
      
      ipad++;     
    } // end of for(istart=... loop
    // start a new page
    if(ps) { ps->On(); ps->NewPage(); }
    c->Update();
    if(file) file->Append(c);
  } // end of for(ipage=... loop

  // enable printing to PS file again
  if(ps) ps->On(); 

  TString plot_string = "Phi-Imbalance";
  TString value_string1 = "Chi2 for Width of ";
  TString value_string2 = "Chi2 for Fitted Width of ";

  cout<<"============================================="<<endl;
  cout<<value_string1<<plot_string<<endl;
  for(int i=0; i<a1.size(); i++) {
    cout<<"  Data: "<<sigma_Data[i]<<" +- "<<sigma_err_Data[i]<<" MC: "<<sigma_MC[i]<<" +- "<<sigma_err_MC[i]<<" chi2="<<pow((sigma_Data[i]-sigma_MC[i])/sqrt(sigma_err_Data[i]*sigma_err_Data[i]+sigma_err_MC[i]*sigma_err_MC[i]), 2)<<endl;
  }
  cout<<"Overall chi2 = "<<chi2<<endl;
  cout<<value_string2<<plot_string<<endl;
  for(int i=0; i<a1.size(); i++) {
    cout<<"  Data: "<<fitted_sigma_Data[i]<<" +- "<<fitted_sigma_err_Data[i]<<" MC: "<<fitted_sigma_MC[i]<<" +- "<<fitted_sigma_err_MC[i]<<" chi2="<<pow((fitted_sigma_Data[i]-fitted_sigma_MC[i])/sqrt(fitted_sigma_err_Data[i]*fitted_sigma_err_Data[i]+fitted_sigma_err_MC[i]*fitted_sigma_err_MC[i]), 2)<<endl;
  }
  cout<<"Overall chi2 = "<<chi2_fitted<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////
// use matrix method to subtract background
///////////////////////////////////////////////////////////////////////////////////////////
void plot::plot_without_background(bool if_mc, TH1 *hist, TH1 *hist_spatial, TH1* hist_signal, TH1* bkg_signal) {

  double eff_temp, eff_error_temp, fake_temp, fake_error_temp;

  if(if_mc) { // no background subtraction and use hist_spatial as data histogram
    for(int i=0; i<hist_spatial->GetNbinsX()+2; i++){
      double N_trk=hist_spatial->GetBinContent(i);
      double err_trk=hist_spatial->GetBinError(i);
      
      hist_signal->SetBinContent(i, N_trk);
      hist_signal->SetBinError(i, err_trk);      
    }    
  } else {  // use matrix method to subtract background

    eff_temp=plot::eff_data;
    eff_error_temp=plot::eff_error_data;
    fake_temp=plot::fake_data;
    fake_error_temp=plot::fake_error_data;

    for(int i=0; i<hist->GetNbinsX()+2; i++){
      double bkgd_ElecPt=0., error_bkgd=0.;
      double N_trk=hist_spatial->GetBinContent(i);
      double N_tot=hist->GetBinContent(i);
      
      double  N_sig,N_sigtrk,N_bg,N_bgtrk,N_sigErr,N_sigtrkErr,N_bgErr,N_bgtrkErr;
      
	   	     
      matrix(eff_temp,eff_error_temp,fake_temp,fake_error_temp,
                	  N_tot,     //Nloose (all)
			 N_trk, 	//Ntight (all)
			 N_sig, 	//Nloose from W (N_W)
			 N_sigtrk,	//Ntight from W (eff * N_W)
			 N_bg,		//Nloose  from background (N_QCD)
			 N_bgtrk,	//Ntight  from background (fr * N_QCD)
			 N_sigErr,N_sigtrkErr,N_bgErr,N_bgtrkErr);
      
      double x_coor=hist->GetXaxis()->GetBinCenter(i);

      hist_signal->Fill(x_coor, N_sigtrk);
      hist_signal->SetBinError(i, N_sigtrkErr);      
      bkg_signal->Fill(x_coor, N_bgtrk);
      bkg_signal->SetBinError(i, N_bgtrkErr);
    }    
  }
}


///////////////////////////////////////////////////////////////////////////////////////////
// use matrix method to subtract background 3d
///////////////////////////////////////////////////////////////////////////////////////////

void plot::plot_without_background_3d(bool if_mc, TH1 *hist, TH1 *hist_spatial, TH1* hist_signal, TH1* bkg_signal, TH2F *fake, TH2F *eff, TString qcdfile) {

  // TString qcdfile = "qcdfile_default.txt"; //will switch to passed tstring after validation.

  PParameterReader parmqcd(qcdfile.Data());  
  //parmqcd.Print();
  std::vector<double> FR_par0 =  parmqcd.GetVDouble("FR_par0");

  if(FR_par0.size() != 10){
    cout<<"ERROR in plot_util, qcdfile parameter has wrong name or wrong number of parameters per line"<<endl;
    cout<<"file "<<qcdfile<<endl;
    exit(0);
  }

  std::vector<double> FR_par1 =  parmqcd.GetVDouble("FR_par1");
  std::vector<double> FR_par2 =  parmqcd.GetVDouble("FR_par2");
  std::vector<double> FR_par3 =  parmqcd.GetVDouble("FR_par3");
  std::vector<double> FR_par4 =  parmqcd.GetVDouble("FR_par4");

  std::vector<double> FR_C00 = parmqcd.GetVDouble("FR_C00");
  std::vector<double> FR_C01 = parmqcd.GetVDouble("FR_C01");
  std::vector<double> FR_C02 = parmqcd.GetVDouble("FR_C02");
  std::vector<double> FR_C03 = parmqcd.GetVDouble("FR_C03");
  std::vector<double> FR_C04 = parmqcd.GetVDouble("FR_C04");
  std::vector<double> FR_C11 = parmqcd.GetVDouble("FR_C11");
  std::vector<double> FR_C12 = parmqcd.GetVDouble("FR_C12");
  std::vector<double> FR_C13 = parmqcd.GetVDouble("FR_C13");
  std::vector<double> FR_C14 = parmqcd.GetVDouble("FR_C14");
  std::vector<double> FR_C22 = parmqcd.GetVDouble("FR_C22");
  std::vector<double> FR_C23 = parmqcd.GetVDouble("FR_C23");
  std::vector<double> FR_C24 = parmqcd.GetVDouble("FR_C24");
  std::vector<double> FR_C33 = parmqcd.GetVDouble("FR_C33");
  std::vector<double> FR_C34 = parmqcd.GetVDouble("FR_C34");
  std::vector<double> FR_C44 = parmqcd.GetVDouble("FR_C44");

  std::vector<double> EFF_par0 =  parmqcd.GetVDouble("EFF_par0");
  std::vector<double> EFF_par1 =  parmqcd.GetVDouble("EFF_par1");
  std::vector<double> EFF_par2 =  parmqcd.GetVDouble("EFF_par2");
  std::vector<double> EFF_par3 =  parmqcd.GetVDouble("EFF_par3");
  std::vector<double> EFF_par4 =  parmqcd.GetVDouble("EFF_par4");

  std::vector<double> EFF_C00 = parmqcd.GetVDouble("EFF_C00");
  std::vector<double> EFF_C01 = parmqcd.GetVDouble("EFF_C01");
  std::vector<double> EFF_C02 = parmqcd.GetVDouble("EFF_C02");
  std::vector<double> EFF_C03 = parmqcd.GetVDouble("EFF_C03");
  std::vector<double> EFF_C04 = parmqcd.GetVDouble("EFF_C04");
  std::vector<double> EFF_C11 = parmqcd.GetVDouble("EFF_C11");
  std::vector<double> EFF_C12 = parmqcd.GetVDouble("EFF_C12");
  std::vector<double> EFF_C13 = parmqcd.GetVDouble("EFF_C13");
  std::vector<double> EFF_C14 = parmqcd.GetVDouble("EFF_C14");
  std::vector<double> EFF_C22 = parmqcd.GetVDouble("EFF_C22");
  std::vector<double> EFF_C23 = parmqcd.GetVDouble("EFF_C23");
  std::vector<double> EFF_C24 = parmqcd.GetVDouble("EFF_C24");
  std::vector<double> EFF_C33 = parmqcd.GetVDouble("EFF_C33");
  std::vector<double> EFF_C34 = parmqcd.GetVDouble("EFF_C34");
  std::vector<double> EFF_C44 = parmqcd.GetVDouble("EFF_C44");
  
 // Fake Rate Parameterization (W mass meeting material of 062310)
  // double FR_par0   =     0.0966976  ;
  // double FR_par1   =     0.000355489;

  //   double FR_C00 = 2.0075e-06 ;
//     double FR_C11 = 1.20919e-09;
//     double FR_C01 =  -4.52536e-08;
 // Tight Track Match Efficiency Parameterization 
  // Z->ee data derived (after follow up on W mass meeting talk 062310)
//   double EFF_par0=0.667905    ;
//   double EFF_par1=0.00512973  ;
//   double EFF_par2=-4.52526e-05;

//run2b12 error calculation
  
 //  double EFF_C00=0.000436904 ; 
//   double EFF_C01=-2.06247e-05; 
//   double EFF_C02=2.37572e-07 ; 

//   double EFF_C11=9.9091e-07; 
//   double EFF_C22=1.37846e-10; 
    
//   double EFF_C12=-1.15976e-08;


  double eff_temp, eff_error_temp, fake_temp, fake_error_temp;

  if(if_mc) { // no background subtraction and use hist_spatial as data histogram
    for(int i=0; i<hist_spatial->GetNbinsX()+2; i++){
      double N_trk=hist_spatial->GetBinContent(i);
      double err_trk=hist_spatial->GetBinError(i);

      hist_signal->SetBinContent(i, N_trk);
      hist_signal->SetBinError(i, err_trk);
    }
  } else {  // use matrix method to subtract background

    hist_signal->Reset();
    bkg_signal->Reset();
    cout<<"Apply matrix method for histogram: "<<hist_signal->GetName()<<endl;
//    cout<<"number bins of hist_signal "<<hist_signal->GetNbinsX()<<endl;
//    cout<<"number bins of bkg_signal "<<bkg_signal->GetNbinsX()<<endl;
    TH3 *hist_3d=(TH3 *)hist->Clone();
    TH3 *hist_spatial_3d=(TH3 *)hist_spatial->Clone();
    //cout<<"number of bins X="<<hist_3d->GetNbinsX()<<endl;
    //cout<<"number of bins Y="<<hist_3d->GetNbinsY()<<endl;
    
    //cout<<"number of bins Z="<<hist_3d->GetNbinsZ()<<endl;
    double sum_bkgd=0.;
    double sum_signal=0.;
    // comment out loop over elec. eta bins (i loop) // ////////////////////////
   
    //cout<<"number of eta bins"<<hist->GetNbinsX()<<endl;
    for(int i=0; i<hist->GetNbinsX(); i++){// SUM OVER ELEC. DET.ETA BINS
      // Int_t NDETETABINS = hist->GetNbinsX(); // Add back the eta dependence
      for(int j=0; j<hist->GetNbinsY(); j++){// SUM OVER ELEC. PT BINS

        //PT-dependent Efficiency and Fake Rate:      
	//testing bin content 
       
        double x = hist->GetYaxis()->GetBinCenter(j+1);// x = electron PT
        double y = hist->GetXaxis()->GetBinCenter(i+1); //y = phys eta

	//cout<<"x "<<x<<" y "<<y<<endl;

        double Zbased_epsilon, err_Zbased_epsilon, ZtoW_corr, err_ZtoW_corr, epsilon, err_epsilon, f, err_f;
        Zbased_epsilon=err_Zbased_epsilon=ZtoW_corr=err_ZtoW_corr=epsilon=err_epsilon=f=err_f=-555.;

        Zbased_epsilon = EFF_par0[i] 
                       + EFF_par1[i]*x 
                       + EFF_par2[i]*x*x 
                       + EFF_par3[i]*x*x*x 
                       + EFF_par4[i]*x*x*x*x;
       
	//err_Zbased_epsilon = sqrt(EFF_C00 + EFF_C11*x*x + EFF_C22*x*x*x*x /*+ EFF_C33*x*x*x*x*x*x*/ + 
	//		                                 2*EFF_C01*x + 2*EFF_C02*x*x /*+ 2*EFF_C03*x*x*x*/ +
	//	                                2*EFF_C12*x*x*x /*+2*EFF_C13*x*x*x*x+2*EFF_C23*x*x*x*x*x*/);
				 
       
	  err_Zbased_epsilon=sqrt(EFF_C00[i] + EFF_C11[i]*x*x + EFF_C22[i]*x*x*x*x + EFF_C33[i]*x*x*x*x*x*x 
		 + EFF_C44[i]*x*x*x*x*x*x*x*x + EFF_C01[i]*2*x + EFF_C02[i]*2*x*x 
		 + EFF_C03[i]*2*x*x*x + EFF_C04[i]*2*x*x*x*x + EFF_C12[i]*2*x*x*x 
		 + EFF_C13[i]*2*x*x*x*x + EFF_C14[i]*2*x*x*x*x*x 
		 + EFF_C23[i]*2*x*x*x*x*x + EFF_C24[i]*2*x*x*x*x*x*x 
		 + EFF_C34[i]*2*x*x*x*x*x*x*x);  

       
      epsilon = Zbased_epsilon;
      err_epsilon =err_Zbased_epsilon;  
      
      // next line is protection from negative efficiency at high PT which can happen with 
      // latest (committed to CVS 062610) Efficiency vs PT parameterization.
      // always positive correctin (commited to CVS 062810) would keep corrected efficiency negative as well
      if (epsilon<0.) epsilon=0.;
      
      f= FR_par0[i] + FR_par1[i]*x + FR_par2[i]*x*x + FR_par3[i]*x*x*x + FR_par4[i]*x*x*x*x;
      //err_f=sqrt(FR_C00[i] + FR_C11[i]*x*x + 2*x*FR_C01[i]);
        err_f=sqrt(FR_C00[i] + FR_C11[i]*x*x + FR_C22[i]*x*x*x*x + FR_C33[i]*x*x*x*x*x*x + FR_C44[i]*x*x*x*x*x*x*x*x + FR_C01[i]*2*x + FR_C02[i]*2*x*x + FR_C03[i]*2*x*x*x + FR_C04[i]*2*x*x*x*x + FR_C12[i]*2*x*x*x + FR_C13[i]*2*x*x*x*x + FR_C14[i]*2*x*x*x*x*x + FR_C23[i]*2*x*x*x*x*x + FR_C24[i]*2*x*x*x*x*x*x + FR_C34[i]*2*x*x*x*x*x*x*x);  
      


      //---- moving efficiency and fake rate up and down by one sigma
      //---- to produce fitter_backgrounds.root files to estimate MW error due to QCD
      //-- up-up      
      //if (epsilon>0.1) epsilon+=err_epsilon;f+=err_f;
      //-- down-down      
      //if (epsilon>0.1) epsilon-=err_epsilon;f-=err_f;
      //-- up-down      
      //if (epsilon>0.1) epsilon+=err_epsilon;f-=err_f;
      //-- down-up      
      //if (epsilon>0.1) epsilon-=err_epsilon;f+=err_f;
      
      //--------------------------------------PT-dependent Efficiency and Fake Rate:      
      
      // make pointers to 1D histograms for "PLOTTED VARIABLE (e.g. MT)" 
      // corresponding to (i=ELEC.DET.ETA, j=ELEC.PT) bin
      // *hist_1   = Loose track matched
      // *hist_2   = Tight track matched
      // *hist_tmp = auxiliary histogram with the same dimensions as the two above
      //  and *hist_signal, bkg_signal which are passed to this function and filled
      // by this function
      TString name1="hist11_";
      ////////////// comment out loop over elec. eta bins (i loop) //////
      name1+=i;
      name1+="_";
      name1+=j;
      
      TString name2="hist22_";
      ////////////// comment out loop over elec. eta bins (i loop) //////
      name2+=i;
      name2+="_";
      name2+=j;
      
      //TH1 *hist_1=hist_3d->ProjectionZ(name1,1,NDETETABINS,j+1,j+1);//i=ELEC.DET.ETA bin
      //TH1 *hist_2=hist_spatial_3d->ProjectionZ(name2,1,NDETETABINS,j+1,j+1);//j=ELEC.PT bin
      TH1 *hist_1=hist_3d->ProjectionZ(name1,i+1,i+1,j+1,j+1);//i=ELEC.DET.ETA bin
      TH1 *hist_2=hist_spatial_3d->ProjectionZ(name2,i+1,i+1,j+1,j+1);//j=ELEC.PT bin

      TH1 *hist_tmp=(TH1 *)hist_1->Clone();
      hist_tmp->Reset();
      //------------------------------------------ make pointers to 1D histograms for "PLOTTED VARIABLE (e.g. MT)" 
      for(int k=0; k<hist_tmp->GetNbinsX();k++){// SUM OVER "PLOTTED VARIABLE (e.g. MT)" BINS
        if(hist_1->GetBinContent(k+1)!=0){
	
          double n_before=hist_1->GetBinContent(k+1);
          double n_after=hist_2->GetBinContent(k+1);
          double num_bkgd;
	  
          // solve matrix equations (code in ./matrix.cpp)
          // for current (j=ELEC.PT, k="PLOTTED VARIABLE (e.g. MT)") 2D bin
          double num_sig, num_sig_trk,num_bg, num_bg_trk, err_num_sig, err_num_sig_trk,err_num_bg, err_num_bg_trk;
          matrix(epsilon,err_epsilon,f,err_f,n_before,n_after, num_sig, num_sig_trk,num_bg, num_bg_trk, err_num_sig, err_num_sig_trk, err_num_bg, err_num_bg_trk);
          num_bkgd=num_bg_trk;

          // set background in (j=ELEC.PT, k="PLOTTED VARIABLE (e.g. MT)") 2D bin to zero
          // if it was found to be negative
          // (it can go negative if Efficincy*N_Loose < N_tight,
          //  and this condition is subject to fluctuations of N_Loose and N_tight)
          if (num_bkgd<0.){
              num_bkgd=0.;
              err_num_bg_trk=0.;
          }

          // add contribution to  k="PLOTTED VARIABLE (e.g. MT)" 1D bin
          // from (j=ELEC.PT, k="PLOTTED VARIABLE (e.g. MT)") 2D bin
          int bin_bkgd=bkg_signal->FindBin(hist_tmp->GetXaxis()->GetBinCenter(k+1));
          double bincontent= bkg_signal->GetBinContent(bin_bkgd);
          double binerror= bkg_signal->GetBinError(bin_bkgd); 
          bincontent+=num_bkgd;
          binerror=sqrt(binerror*binerror+err_num_bg_trk*err_num_bg_trk);
          //---------------------------------------------add contribution to  k="PLOTTED VARIABLE (e.g. MT)" 1D bin

          bkg_signal->SetBinContent(bin_bkgd,bincontent);          
          bkg_signal->SetBinError(bin_bkgd,binerror);

          int bin_signal=hist_signal->FindBin(hist_tmp->GetXaxis()->GetBinCenter(k+1));
          bincontent= hist_signal->GetBinContent(bin_signal);
          binerror= hist_signal->GetBinError(bin_signal);
	  //cout<<"i "<<i<<" x "<<x<<" y "<<y<<" k "<<k<<" bin content "<<bincontent<<" bin error "<<binerror<<endl;
          bincontent+=num_sig_trk;
          binerror=sqrt(binerror*binerror+err_num_sig_trk*err_num_sig_trk);

          hist_signal->SetBinContent(bin_signal,bincontent);
          hist_signal->SetBinError(bin_signal,binerror);
          sum_bkgd+=num_bkgd;
          sum_signal+=num_sig_trk;
        }
      }

      delete hist_1;
      delete hist_2;
      }//loop over pT bins (j)
      
    } //loop for the eta bins (i)
  }
}




// used in wencomp for Mt, electron pT, MET and W pT comparisons for Upara<0 and Upara>0
void plot::plot2overlay_without_background(TString cname, // TCanvas *c, 
					   vector<TH1 *> datahistos, 
					   vector<TH1 *> datahistos_spatial, 
					   vector<TH1 *> mchistos, 
					   bool if_mc, 
					   double xmin, 
					   double xmax,
					   TPostScript *ps,// optional output PS file
					   TFile *file) {  // optional output ROOT file
  TH1 *a_signal[2];
  TH1 *b[2];
  char name[100];
  
  double chisq0 = 0.0, chisq1 = 0.0;
  int nbins0 = 0, nbins1 = 0;
  
  if(datahistos.size()!=mchistos.size()) {
    cout<<"Different number of histograms for data and MC (1)" << datahistos.size() << " " << mchistos.size() <<endl;
  }
  if(datahistos.size()!=datahistos_spatial.size()) {
    cout<<"Different number of histograms for data and data_spatial"<<endl;
  }

  for(int histnum=0; histnum<2; histnum++) {
    TH1 *htemp;
    TH1 *btemp;

    htemp = (TH1 *)datahistos[histnum];
    btemp = (TH1 *)datahistos[histnum]->Clone();

    if(htemp==NULL) return; // empty pointer => something wrong
    a_signal[histnum] = (TH1 *)htemp->Clone();
    sprintf(name, "%s%d", "Signal_", (histnum+1));
    a_signal[histnum]->SetName(name);
     a_signal[histnum]->Reset();
    
    htemp = (TH1 *)mchistos[histnum];
    if(htemp==NULL) return; // empty pointer => something wrong
    b[histnum] = htemp;
    // just calculations, no plots...

    plot::plot_without_background(if_mc, datahistos[histnum], datahistos_spatial[histnum], a_signal[histnum], btemp);

 }

  double entry_a1 = a_signal[0]->Integral();
  double entry_b1 = b[0]->Integral();
  double entry_a2 = a_signal[1]->Integral();
  double entry_b2 = b[1]->Integral();

  if(ps) ps->Off(); // temporarily disable printing to PS file
  TCanvas *c = new TCanvas(cname.Data(), "c", 50,10,700,800);
  c->Divide(1, 1);
  c->cd(1);
  
  a_signal[0]->GetXaxis()->SetRangeUser(xmin, xmax);
  a_signal[0]->SetMarkerStyle(8);
  a_signal[0]->SetMarkerSize(0.4);
  a_signal[0]->SetMarkerColor(2);
  a_signal[0]->Draw("pe");
  b[0]->SetMarkerStyle(8);
  b[0]->SetMarkerSize(0.4);
  b[0]->SetMarkerColor(4);
  b[0]->Scale(entry_a1/entry_b1);
  b[0]->SetLineWidth(2);
  b[0]->SetLineColor(4);
  b[0]->Draw("hist,same");
  
  a_signal[1]->GetXaxis()->SetRangeUser(xmin, xmax);
  a_signal[1]->SetMarkerStyle(8);
  a_signal[1]->SetMarkerSize(0.4);
  a_signal[1]->SetMarkerColor(1);
  a_signal[1]->SetLineColor(1);
  a_signal[1]->Draw("pe,same");
  b[1]->SetMarkerStyle(8);
  b[1]->SetMarkerSize(0.4);
  b[1]->SetMarkerColor(6);
  b[1]->Scale((double)(entry_a1/entry_b1));
  b[1]->SetLineWidth(2);
  b[1]->SetLineColor(6);
  b[1]->Draw("hist,same");
  plot::find_chi2(a_signal[0], b[0], xmin, xmax, chisq0, nbins0);
  plot::find_chi2(a_signal[1], b[1], xmin, xmax, chisq1, nbins1);
  
  TLegend *leg1 = new TLegend(0.55,0.7,0.8,0.88,NULL,"brNDC");
  leg1->SetTextSize(0.05);
  leg1->SetLineColor(1);
  leg1->SetLineStyle(1);
  leg1->SetLineWidth(1);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.02);
  
  if(!not_show_chi2) {
    sprintf(name, "U_{||} < 0 :  #chi^{2}/ndf = %.1f/%d", chisq0, nbins0);
    leg1->AddEntry(a_signal[0], name, " ");
    sprintf(name, "U_{||} > 0 :  #chi^{2}/ndf = %.1f/%d", chisq1, nbins1);
    leg1->AddEntry(a_signal[0], name, " ");
  }

  TLegendEntry *entry=NULL;
  sprintf(name,"U_{||} < 0  -  %s",plot::data_label);  // Full-MC or DATA
  entry=leg1->AddEntry(a_signal[0], name, "pl");
  if(entry) {
    entry->SetTextColor( a_signal[0]->GetMarkerColor() );
    entry->SetMarkerSize(3);
  }
  sprintf(name,"U_{||} < 0  -  %s",plot::mc_label);    // Fast-MC
  entry=leg1->AddEntry(b[0], name, "pl");
  if(entry) {
    entry->SetTextColor( b[0]->GetMarkerColor() );
    entry->SetMarkerSize(3);
  }
  sprintf(name,"U_{||} > 0  -  %s",plot::data_label);  // Full-MC or DATA
  entry=leg1->AddEntry(a_signal[1], name, "pl");
  if(entry) {
    entry->SetTextColor( a_signal[1]->GetMarkerColor() );
    entry->SetMarkerSize(3);
  }
  sprintf(name,"U_{||} > 0  -  %s",plot::mc_label);    // Fast-MC
  entry=leg1->AddEntry(b[1], name, "pl");
  if(entry) {
    entry->SetTextColor( b[1]->GetMarkerColor() );
    entry->SetMarkerSize(3);
  }
  leg1->Draw();

  // enable printing to PS file again
  if(ps) { ps->On(); ps->NewPage(); }
  c->Update();
  if(file) file->Append(c);
}



// used in wencomp for Mt, electron pT, MET and W pT comparisons for Upara<0 and Upara>0
void plot::plot2overlay_with_background(TString cname, // TCanvas *c, 
                                      vector<TH1 *> datahistos, 
                                      vector<TH1 *> datahistos_spatial, 
                                      vector<TH1 *> bkgdhistos_inp, 
                                      vector<TH1 *> mchistos, 
                                      bool if_mc, 
                                      double xmin, 
                                      double xmax,
                                      int qcd_option,
                                      TPostScript *ps,// optional output PS file
                                      TFile *file, double zee_bkg_fraction, double wtaunu_bkg_fraction, TString qcdfile) {  // optional output ROOT file
  TH1 *a_signal[2];
  TH1 *b[2];
  char name[100];
  
  double chisq0 = 0.0, chisq1 = 0.0;
  int nbins0 = 0, nbins1 = 0;
  
  if(datahistos.size()!=mchistos.size()) {
    cout<<"Different number of histograms for data and MC (2)" << datahistos.size() << " " << mchistos.size() <<endl;
  }
  if(datahistos.size()!=datahistos_spatial.size()) {
    cout<<"Different number of histograms for data and data_spatial"<<endl;
  }
  if(bkgdhistos_inp.size()!=0 && bkgdhistos_inp.size()!=mchistos.size()) {
    cout<<"Different number of histograms for bkg and MC (3)" << bkgdhistos_inp.size() << " " << mchistos.size()<<endl;
  }

  for(int histnum=0; histnum<2; histnum++) {    
    TH1 *htemp;
    TH1 *btemp;

    htemp = (TH1 *)datahistos[histnum];
    btemp = (TH1 *)datahistos[histnum]->Clone();

    TH1 *histo_3d;                                            
    TH1 *histo_spatial_3d;                                    
    if(qcd_option==1){   // use 3D histogram for matrix method  
      histo_3d=(TH1 *)datahistos[histnum+2]->Clone();             
      histo_spatial_3d=(TH1 *)datahistos_spatial[histnum+2]->Clone(); 
    }
    
    TH1 *bkgd_zee, *bkgd_wtaunu;
    Double_t entries_bkgd_zee, entries_bkgd_wtaunu;
    
    bkgd_zee=(TH1F *) bkgdhistos_inp[histnum]->Clone();
    bkgd_wtaunu=(TH1F *) bkgdhistos_inp[histnum+2]->Clone();    

    bkgd_zee->GetXaxis()->SetRangeUser(xmin, xmax);
    bkgd_wtaunu->GetXaxis()->SetRangeUser(xmin, xmax);

    if(htemp==NULL) return; // empty pointer => something wrong
    a_signal[histnum] = (TH1 *)htemp->Clone();
    sprintf(name, "%s%d", "Signal_", (histnum+1));
    a_signal[histnum]->SetName(name);
    a_signal[histnum]->Reset();
    
    htemp = (TH1 *)mchistos[histnum];
    if(htemp==NULL) return; // empty pointer => something wrong
    b[histnum] = htemp;
    // just calculations, no plots...

    TH1* h1_signal = (TH1F *)a_signal[histnum]->Clone();
    TH1* bkg_signal = (TH1F *)a_signal[histnum]->Clone();

    bkg_signal->Reset();

    if(qcd_option==1) {  // use eff and fake rate vs detector eta and pT
      //cout<<"qcd opton 1 "<<endl; 

      TFile *file_fake_eff = TFile::Open("./fake_eff.root");
      TH2F *hist_fake=(TH2F *)gROOT->FindObject("fake");
      TH2F *hist_eff=(TH2F *)gROOT->FindObject("eff");
      plot::plot_without_background_3d(if_mc, histo_3d, histo_spatial_3d, a_signal[histnum], bkg_signal, hist_fake, hist_eff, qcdfile);       
    }
    else {
      plot::plot_without_background(if_mc, datahistos[histnum], datahistos_spatial[histnum], a_signal[histnum], btemp);
    }
    
    double number_wenu = b[histnum]->Integral();
    double number_qcd = bkg_signal->Integral();
    double qcd_fraction = bkg_signal->Integral() / a_signal[histnum]->Integral();

    // cout<<" number wenu "<<number_wenu<<" number QCD "<<number_qcd<<" qcd_fraction "<<qcd_fraction<<endl;

    entries_bkgd_zee = bkgd_zee->Integral();
    entries_bkgd_wtaunu = bkgd_wtaunu->Integral();
    bkgd_zee->Scale(zee_bkg_fraction*number_wenu/entries_bkgd_zee);
    bkgd_wtaunu->Scale(wtaunu_bkg_fraction*number_wenu/entries_bkgd_wtaunu);
    bkg_signal->Scale(qcd_fraction*number_wenu/number_qcd);

    b[histnum]->Add(bkgd_zee,1);
    b[histnum]->Add(bkgd_wtaunu,1);
    b[histnum]->Add(bkg_signal,1);
 }
  
  double entry_a1 = a_signal[0]->Integral();
  double entry_b1 = b[0]->Integral();
  double entry_a2 = a_signal[1]->Integral();
  double entry_b2 = b[1]->Integral();

  if(ps) ps->Off(); // temporarily disable printing to PS file
  TCanvas *c = new TCanvas(cname.Data(), "c", 50,10,700,800);
  c->Divide(1, 1);
  c->cd(1);
  
  a_signal[0]->GetXaxis()->SetRangeUser(xmin, xmax);
  a_signal[0]->SetMarkerStyle(8);
  a_signal[0]->SetMarkerSize(0.4);
  a_signal[0]->SetMarkerColor(2);
  a_signal[0]->Draw("pe");
  b[0]->SetMarkerStyle(8);
  b[0]->SetMarkerSize(0.4);
  b[0]->SetMarkerColor(4);
  b[0]->Scale(entry_a1/entry_b1); 

  b[0]->SetLineWidth(2);
  b[0]->SetLineColor(4);
  b[0]->Draw("hist,same");
  
  a_signal[1]->GetXaxis()->SetRangeUser(xmin, xmax);
  a_signal[1]->SetMarkerStyle(8);
  a_signal[1]->SetMarkerSize(0.4);
  a_signal[1]->SetMarkerColor(1);
  a_signal[1]->SetLineColor(1);
  a_signal[1]->Draw("pe,same");
  b[1]->SetMarkerStyle(8);
  b[1]->SetMarkerSize(0.4);
  b[1]->SetMarkerColor(6);
  b[1]->Scale((double)(entry_a1/entry_b1)); 
  
  b[1]->SetLineWidth(2);
  b[1]->SetLineColor(6);
  b[1]->Draw("hist,same");
  plot::find_chi2(a_signal[0], b[0], xmin, xmax, chisq0, nbins0);
  plot::find_chi2(a_signal[1], b[1], xmin, xmax, chisq1, nbins1);
  
  TLegend *leg1 = new TLegend(0.55,0.7,0.8,0.88,NULL,"brNDC");
  leg1->SetTextSize(0.05);
  leg1->SetLineColor(1);
  leg1->SetLineStyle(1);
  leg1->SetLineWidth(1);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.02);
  
  if(!not_show_chi2) {
    sprintf(name, "U_{||} < 0 :  #chi^{2}/ndf = %.1f/%d", chisq0, nbins0);
    leg1->AddEntry(a_signal[0], name, " ");
    sprintf(name, "U_{||} > 0 :  #chi^{2}/ndf = %.1f/%d", chisq1, nbins1);
    leg1->AddEntry(a_signal[0], name, " ");
  }

  TLegendEntry *entry=NULL;
  sprintf(name,"U_{||} < 0  -  %s",plot::data_label);  // Full-MC or DATA
  entry=leg1->AddEntry(a_signal[0], name, "pl");
  if(entry) {
    entry->SetTextColor( a_signal[0]->GetMarkerColor() );
    entry->SetMarkerSize(3);
  }
  sprintf(name,"U_{||} < 0  -  %s",plot::mc_label);    // Fast-MC
  entry=leg1->AddEntry(b[0], name, "pl");
  if(entry) {
    entry->SetTextColor( b[0]->GetMarkerColor() );
    entry->SetMarkerSize(3);
  }
  sprintf(name,"U_{||} > 0  -  %s",plot::data_label);  // Full-MC or DATA
  entry=leg1->AddEntry(a_signal[1], name, "pl");
  if(entry) {
    entry->SetTextColor( a_signal[1]->GetMarkerColor() );
    entry->SetMarkerSize(3);
  }
  sprintf(name,"U_{||} > 0  -  %s",plot::mc_label);    // Fast-MC
  entry=leg1->AddEntry(b[1], name, "pl");
  if(entry) {
    entry->SetTextColor( b[1]->GetMarkerColor() );
    entry->SetMarkerSize(3);
  }
  leg1->Draw();

  // enable printing to PS file again
  if(ps) { ps->On(); ps->NewPage(); }
  c->Update();
  if(file) file->Append(c);
}



////////////////////////////////////////////////////////////////////////////////////////////////
// Calculate chi2
////////////////////////////////////////////////////////////////////////////////////////////////
void plot::find_chi2(TH1 *a1, TH1 *b1, Double_t xmin, Double_t xmax, Double_t &chisq, Int_t &NBin) {

  NBin = 0; //number of bins used to calculate chisq
  chisq = 0;
  Double_t delta=0., n1=0., n2=0., error1=0., error2=0.;
  
  for (Int_t i=0;i<a1->GetNbinsX(); i++) {
    double center = a1->GetXaxis()->GetBinCenter(i+1);
    if((center >= xmin) && (center <= xmax)) {
      n1 = a1->GetBinContent(i+1);
      n2 = b1->GetBinContent(i+1);
      error1=a1->GetBinError(i+1);
      error2=b1->GetBinError(i+1);
      if(fabs(n1)<0.001) error1 = 1.;  // if no entries for data, assign the error to 1

      if(fabs(b1->GetBinContent(i+1))>0.) { // require fast MC bin must have some entries
	NBin ++;    
	delta = n1-n2;
	chisq += delta*delta/(error1*error1+error2*error2);
      }
    } // for given range
  } //loop over all bins

}

////////////////////////////////////////////////////////////////////////////////////////////////
// Make chi distribution (a1 and b1 are supposed to be normalized already)
////////////////////////////////////////////////////////////////////////////////////////////////
void plot::plot_with_chi2(TH1 *a1, TH1 *b1, Double_t xmin, Double_t xmax) {
  
  // histograms for chi2
  TH1 *histo_chi2;
  
  TH1F *temp_chi2 = new TH1F("temp_chi2", "", a1->GetNbinsX(), a1->GetXaxis()->GetXmin(), a1->GetXaxis()->GetXmax());
  TProfile *h2 = dynamic_cast<TProfile *>(a1);
  
  if(h2 != 0) {
    histo_chi2 = (TH1F *)temp_chi2->Clone();
    histo_chi2->SetName("test");
    histo_chi2->Reset();
  } else {
    histo_chi2 = (TH1F *)a1->Clone();
    histo_chi2->SetName("test");
    histo_chi2->Reset();
  }
  
  if(a1->GetNbinsX() != b1->GetNbinsX()) {
    cout<<"**** Chi2 calculation: Different number of bins! ***"<<endl;
    return;
  }

  Int_t NBin = 0; //number of bins used to calculate chi2
  Double_t chisq = 0;
  Double_t delta;
  Double_t n1,n2;
  Double_t error1, error2;

  // do not need to normalize histograms
  for (Int_t i=0;i<a1->GetNbinsX(); i++) {
    double center = a1->GetXaxis()->GetBinCenter(i+1);
    if((center >= xmin) && (center <= xmax)) {
      n1 = a1->GetBinContent(i+1);
      n2 = b1->GetBinContent(i+1);
      error1=a1->GetBinError(i+1);
      error2=b1->GetBinError(i+1);
      if(fabs(n1)<0.001) error1 = 1.;  // if no entries for data, assign the error to 1

      // only look at entries where fast MC distribution have some entries
#ifndef RATIO
      if(fabs(n2)>0.){
#else
      if(fabs(n2)>0. && fabs(n1)>0. ){
#endif
	NBin ++;
#ifndef RATIO
	delta = n1-n2;
#else
	delta = n2/n1;
#endif
	chisq += delta*delta/(error1*error1+error2*error2);
#ifndef RATIO
	histo_chi2->SetBinContent(i+1, delta/sqrt(error1*error1+error2*error2));
	histo_chi2->SetBinError(i+1, 1);
#else
	histo_chi2->SetBinContent(i+1,delta);
	histo_chi2->SetBinError(i+1, delta*sqrt(pow(error1/n1,2)+pow(error2/n2,2)));
#endif
      } else {
	histo_chi2->SetBinContent(i+1, 0.);
#ifndef RATIO
	histo_chi2->SetBinError(i+1, 1);
#else
	histo_chi2->SetBinError(i+1, 0.);
#endif
      }
    } // for given range
  }//loop over all bins
  histo_chi2->SetMarkerStyle(8);
  histo_chi2->SetMarkerSize(0.5);
  histo_chi2->SetMarkerColor(2);
  histo_chi2->SetLineColor(1);

  char name[150]; 
  if(!not_show_chi2) {
    sprintf(name, "#chi distribution with overall #chi^{2} = %.1f for %d bins", chisq, NBin);
  } else {
    sprintf(name, "#chi distribution");
  }

  histo_chi2->SetTitle(name);

#ifdef RATIO
  histo_chi2->SetMinimum(0.85);
#endif
  histo_chi2->Draw("pe");

#ifdef ZEROLINE
  Float_t target=0;
#ifdef RATIO
  target=1;
#endif
  TLine* l = new TLine(histo_chi2->GetXaxis()->GetBinLowEdge(histo_chi2->GetXaxis()->GetFirst()),target,histo_chi2->GetXaxis()->GetBinUpEdge(histo_chi2->GetXaxis()->GetLast()),target);
  l->SetLineColor(3);
  l->Draw();
#endif

/*   
  // AM 122709:
  // this piece of code below allows to write out histograms
  // for mass_zee, pte_zee, mt_wen, pte_wen
  // as well as corresponding signed chi histograms
  // into chi2histo_zee.root ( or chi2histo_wen.root);
  // it works with zeecomp and wenucomp 
  char a1name1zee[200];   
  char a1name2zee[200];   
  char b1name1zee[200];   
  char b1name2zee[200];
  sprintf(a1name1zee,  "ZCandMass_CCCC_Trks_copy");
  sprintf(a1name2zee,  "ZCandElecPt_0_copy");
  sprintf(b1name1zee,  "smeared_hZcandMass_CCCC_copy");
  sprintf(b1name2zee,  "smeared_hZcandElecpT_CCCC_copy");
  char a1name1wenu[200];   
  char a1name2wenu[200];   
  char b1name1wenu[200];   
  char b1name2wenu[200];
  char c1name1wenu[200];   
  char c1name2wenu[200];
  sprintf(a1name1wenu,  "hWcandMt_CC");
  sprintf(a1name2wenu,  "hWcandElecPt_CC");
  sprintf(b1name1wenu,  "hWcandMt_CC_copy");
  sprintf(b1name2wenu,  "hWcandElecPt_CC_copy");
  sprintf(c1name1wenu,  "WcandMt_CC");
  sprintf(c1name2wenu,  "WcandElecPt_CC");
  //////////cout<<a1->GetName()<<"    "<<b1->GetName()<<endl;
  if (strcmp(a1->GetName(),a1name1zee)==0
       || strcmp(a1->GetName(),a1name2zee)==0 
       || strcmp(a1->GetName(),b1name1zee)==0
       || strcmp(a1->GetName(),b1name2zee)==0 ) {

       TFile *chi2histo = new TFile("chi2histo_zee.root", "update");
 
  	   if (strcmp(a1->GetName(),a1name1zee)==0 || strcmp(a1->GetName(),b1name1zee)==0) {
    	  a1->Write("mass_red1st__zee");
    	  b1->Write("mass_blue2nd_zee");
    	  histo_chi2->Write("mass_chi2_zee");
  	   }

  	   if (strcmp(a1->GetName(),a1name2zee)==0 || strcmp(a1->GetName(),b1name2zee)==0) {
    	  a1->Write("pte__red1st__zee");
    	  b1->Write("pte__blue2nd_zee");
    	  histo_chi2->Write("pte__chi2_zee");
  	   }
  	   chi2histo->Close();
  }
    
  if (strcmp(a1->GetName(),a1name1wenu)==0
     || strcmp(a1->GetName(),a1name2wenu)==0
     || strcmp(a1->GetName(),b1name1wenu)==0
     || strcmp(a1->GetName(),b1name2wenu)==0
     || strcmp(a1->GetName(),c1name1wenu)==0
     || strcmp(a1->GetName(),c1name2wenu)==0) {

     TFile *chi2histo = new TFile("chi2histo_wen.root", "update");

     if (strcmp(a1->GetName(),a1name1wenu)==0
    	 || strcmp(a1->GetName(),b1name1wenu)==0
    	 || strcmp(a1->GetName(),c1name1wenu)==0 ){ 
         a1->Write("mt___red1st__wen");
         b1->Write("mt___blue2nd_wen");
         histo_chi2->Write("mt___chi2_wen");
     }
     if (strcmp(a1->GetName(),a1name2wenu)==0
    	 || strcmp(a1->GetName(),b1name2wenu)==0
    	 || strcmp(a1->GetName(),c1name2wenu)==0 ) {
         a1->Write("pte__red1st__wen");
         b1->Write("pte__blue2nd_wen");         
         histo_chi2->Write("pte__chi2_wen");
     }
     chi2histo->Close();
  } 
*/

  // write out each plot into a eps file
  if(write_out_each_plot) {
    gStyle->SetTitleFillColor(0);
    TCanvas *c_temp = new TCanvas("c_temp", "canvas", 100, 200, 700, 800);
    histo_chi2->Draw("pe");
    c_temp->Update();

    gROOT->ProcessLine(".! mkdir plots/");

    string eps_file_name = "plots/" + (string)(a1->GetName()) + "_chi2.eps";
    c_temp->Print(eps_file_name.c_str());
    string macro_file_name = "plots/" + (string)(a1->GetName()) + "_chi2.C";
    c_temp->Print(macro_file_name.c_str());
    delete c_temp;
  }

  // delete temporary histogram
  delete temp_chi2;
}
