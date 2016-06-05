////////////////////////////////////////////////////////////////////////
///
///   WZfitter code: findWMass_fromSingVariablehist_x.cpp
///   Author:        Rafael Lopes de Sa  
///   Date:          Apr/2012
///
///   For singularity variable study
///
///////////////////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TString.h>
#include <TApplication.h>
#include <vector>
#include <TRandom.h>
#include <TMinuit.h>
#include <TMath.h>

#include "wzfitter/genDist.hpp"
#include "wzfitter/genGaussMean.hpp" 
#include "wzfitter/genGauss.hpp"
#include "wzfitter/gen1Dspline.hpp"
#include "wzfitter/wzfitter.hpp"
#include "wzfitter/TNHist.hpp"
#include "wzfitter/config.hpp"

#include "wmass_blinding_util/OffsetMass.hpp"
#include "wmass_blinding_util/OffsetWidth.hpp"
#include "wmass_blinding_util/OffsetMassP0.hpp"
#include "wmass_blinding_util/OffsetWidthP0.hpp"
#include "wmass_blinding_util/OffsetMassP1.hpp"
#include "wmass_blinding_util/OffsetWidthP1.hpp"

#include "wmass_blinding_util/BlindingAuthority.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ostream>
#include <sstream>

using namespace std;

void DumpUsage();

/////////////////////////////////////////////////////////////////////////////////////////////////
// Global variables...

// fit classes
gen1Dspline *myDist;
wzfitter *myFitter;

// fit parameters
int maxiter;
double sensitivity;
vector<Double_t> vstart;
vector<Double_t> vstep;
vector<Double_t> vmin;
vector<Double_t> vmax;
double *_gpar,*_gerr;
bool _limits;
bool _likely;
int _npar;
int _ndim;
bool _blinded;

// Histo dimensions
vector<int> _numbins;
vector<double> _lowb;
vector<double> _highb;

// Fit range
vector<Double_t> frange;
vector< vector<Double_t> > myRange;

////////////////////////////////////////////////////////////////////////////////////////////////
// The FCN function minimized by MINUIT

void Thefcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  if (_blinded) {
     BlindingAuthority BA(1);
     par[0] = BA.Get_Offset_Mass()->CalculateTrueMassFromBlindedMass(par[0]);
  }
   
  vector<double> d1range;
  d1range.push_back(frange[0]);
  d1range.push_back(frange[1]);
  myRange.push_back(d1range);
  
  f=myFitter->doLogLikelihood(par,true,myRange);

}

////////////////////////////////////////////////////////////////////////////////////////////////
// This function does the fit...regardless of what we're fitting 

void doFit() {

  // MINUIT variables...explained later
  Double_t amin,edm,errdef;      
  Int_t nvpar,nparx,icstat;      


  // Initialize TMinuit  
  TMinuit *gMinuit = new TMinuit(_npar);
  gMinuit->SetFCN(Thefcn);
  Double_t arglist[10];
  Int_t ierflg = 0;
    
  arglist[0] = -1.;
  gMinuit -> mnexcm("SET PRINT", arglist, 1, ierflg);
  
  if(_likely) arglist[0] = .5;
  else arglist[0] = 1.;
  
  gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
  
  for(int i=0; i<_npar; i++) {
    if(_limits) gMinuit->mnparm(i, "a1", vstart[i], vstep[i], vmin[i], vmax[i], ierflg);  // Are there upper and lower fit limits?
    else gMinuit->mnparm(i, "a1", vstart[i], vstep[i], 0, 0, ierflg);                     // ... or no limits?
  }

  
  // Now ready for minimization step
  
  arglist[0] = maxiter;       // the maximum number of iterations 
  arglist[1] = sensitivity;   // specifies required tolerance on the function value 
  
  gMinuit->mnexcm("MIGRAD", arglist , 2, ierflg);
  
  // Print results
  
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
  gMinuit->mnprin(_npar,amin);
  gMinuit->mnmatu(1);
  
  // Get fit results: parameters and their errors
  _gpar = new Double_t[_npar];
  _gerr = new Double_t[_npar];

  for(int i=0; i<_npar; i++) {
      gMinuit->GetParameter(i, _gpar[i], _gerr[i]);
  }

  delete gMinuit; 
}



// The main function...Opens and fills data, calls fit classes, does fit, output's results...


int main( int argc, char *argv[] )
{
  
  cout << "+--------------------------------------------------------------------------------+" << endl;  
  cout << "|                   Running the executable fitter_x                              |" << endl;
  cout << "|                   For more help type: fitter_x -help                           |" << endl;
  cout << "+--------------------------------------------------------------------------------+" << endl;  
  
  //parse the command line
  if( argc < 5) {
    std::cout<< "Usage : ./findWMass_fromhist_x <input-filenames> <output-filename> <template-filename> <compare-option> <sv> <ccec, ec, or cc>" << std::endl;
    std::cout<<" Use <compare_option>=0  for comparing DATA with Fast-MC (PMCS),"<<endl
	     <<"     <compare_option>=1  for comparing DATA with DATA,"<<endl
	     <<"     <compare_option>=2  for comparing Fast-MC (PMCS) with Fast-MC (PMCS),"<<endl 
	     <<"     <compare_option>=3  for comparing Full-MC (GEANT) with Fast-MC (PMCS)," << endl
	     <<"     <compare_option>=4  for comparing Full-MC (GEANT) with Full-MC (GEANT)." << endl
	     <<"     <compare_option>=5  for comparing DATA with Full-MC (GEANT)." << endl
	     <<"     Only 0, 2 and 3 are useful." << endl;

    return 1;
  }
  std::string datafile = std::string(argv[argc-6]);

  std::string out_filename = std::string(argv[argc-5]);

  // Opens the output file
  TString pfilename = out_filename;
  TFile* fout = new TFile(pfilename,"RECREATE");
 double paramval,errval;
double tot_err = 0;

  std::string pmcstemplates = std::string( argv[argc-4] );
  
  int compare_option = atoi(argv[argc-3]);

  std::string mtpt = std::string( argv[argc-2] );

  std::string ccec = std::string( argv[argc-1] ); //not used right now

  // double trialmass = atof(argv[argc-1]);//used to shift the template map
   //NOT NEEDED.  Should be added in if template map formed without the trial mass = central W mass value
 
  if ((compare_option<0) || (compare_option>5)) {
    cout<< "Hey you, please choose a valid compare option 0-5" << endl;
    return 1;
  }
 TGraphErrors* wmass = new TGraphErrors(1);
  TGraphErrors* wmass_CC = new TGraphErrors(1);

  TH1D* error_hist = new TH1D("error_hist", "PDF error", 44, 0., 44.); 
  error_hist->SetFillColor(4);
  error_hist->SetBarWidth(0.4);
  error_hist->SetBarOffset(0.1);
  error_hist->SetStats(0);

  TH1D* pdf_error = new TH1D("pdf_error", "PDF uncertainty", 22, 0., 22.); 
  pdf_error->SetFillColor(4);
  pdf_error->SetBarWidth(0.4);
  pdf_error->SetBarOffset(0.1);
  pdf_error->SetStats(0);
  pdf_error->GetYaxis()->SetTitle("#sigma_{MW}^{2}");

  TH1D* error_hist_CC = new TH1D("error_hist_CC", "PDF error (CC)", 44, 0., 44.); 
  error_hist->SetFillColor(2);
  error_hist->SetBarWidth(0.4);
  error_hist->SetBarOffset(0.5);
  error_hist->SetStats(0);

  TH1D* pdf_error_CC = new TH1D("pdf_error_CC", "PDF uncertainty (CC)", 22, 0., 22.); 
  pdf_error_CC->SetFillColor(2);
  pdf_error_CC->SetBarWidth(0.4);
  pdf_error_CC->SetBarOffset(0.5);
  pdf_error_CC->SetStats(0);
  pdf_error_CC->GetYaxis()->SetTitle("#sigma_{MW}^{2}");


  //setup some file names for pt or mt method
  char* configfile;
  char* histname;
  char* distname;
  char* tempname;
  char* trialmapname;
  char* templatemapname;
  char* dirname;

  configfile = "runWMassSingVariablerafpdf.config";
  //5100 for 100 bins, 60 for 10 bins

  if ( (mtpt=="SVgen" || mtpt=="Svgen" || mtpt=="svgen" ) && (compare_option==2) ){
    histname = "hWcandSingVariable_Gen_CC";
    tempname = "hWcandSingVariable_Gen_CC_";
    distname = "tempWSVgenhists.root";
    templatemapname = "histd1map_SingVariableTemplates";
  }else if ( (mtpt=="SV" || mtpt=="Sv" || mtpt=="sv" ) && (compare_option==2) ){
    histname = "hWcandSingVariable_CC_50";
    tempname = "hWcandSingVariable_CC_";
    distname = "tempWSVhists.root";
    templatemapname = "histd1map_SingVariableTemplates";
  }

  if (compare_option == 2)
    dirname = "default";
  else
    dirname = "WCand_Hist";

  // Read the config file...Obtain global parameters....

  string cpath = "./wzfitter/config/";
  // config runconfig((cpath+configfile));
  config runconfig((cpath+configfile).Data());

  _npar = runconfig.getInt("numparam");  
  _numbins = runconfig.getIntArray("numbins");
  _lowb = runconfig.getDoubleArray("lowrange");
  _highb = runconfig.getDoubleArray("highrange");
  frange = runconfig.getDoubleArray("fit_range");
  vstart = runconfig.getDoubleArray("start_value"); 
  vstep = runconfig.getDoubleArray("vstep"); 
  maxiter = runconfig.getInt("numiter"); 
  sensitivity = (double) runconfig.getFloat("sensitivity"); 
  _limits = runconfig.getBool("limits"); 
  vmin = runconfig.getDoubleArray("vmin"); 
  vmax = runconfig.getDoubleArray("vmax"); 
  _likely = runconfig.getBool("likelihood");
  _blinded = runconfig.getBool("blinded");

  // instatiate blinding authority
  BlindingAuthority BA(1);
  
  TFile* df = new TFile(datafile.c_str(),"READ");
  df->cd(dirname);
  
  // Get the central distribution
  TH1D *myHist = (TH1D*) df->Get(TString::Format("%s/%s", dirname, histname));
   
  cout << "Got data histograms " << myHist << endl;
  if (!myHist) return 1;

  // Check if it has enough events
  if (myHist->GetEntries()<100000.) return 1;

  TFile* tf = new TFile(pmcstemplates.c_str(), "READ");  
  TH1D* templatemap = (TH1D*) tf->Get(TString::Format("default/%s", templatemapname));

  cout << "Got template maps " << templatemap << endl;
  if (!templatemap) return 1;

  // Before doFit always check with the BA
  BA.SetConfiguration(df,tf,compare_option);
  if ((compare_option == 0) && (_blinded == false)) {
    cout << "Blinding must be turned on to study data." << endl;
    return 1;
  } else if ((compare_option != 0) && (_blinded == true)){
    cout << "Blinding must be turned off to study Fast/Full MC." << endl;
    return 1;
  }
  cout << "Checked with bliding manager, you are good to go!" << endl;
  
  // Without background so far
  bool dobackground = false;
  if (compare_option==0) dobackground=true;
  
  // Calculate boundaries
   Int_t templatebins = templatemap->GetXaxis()->GetNbins();
  Double_t templatemin = templatemap->GetXaxis()->GetXmin();
  Double_t templatemax = templatemap->GetXaxis()->GetXmax();
  Double_t templatestep = (templatemax - templatemin)/((Double_t) templatebins);
  Double_t templatemid = (templatemax + templatemin)/2.;

  TString textout;
  cout << "I've found " << templatebins + 1 << " template mass points." << endl;
  textout = TString::Format("Template mass limits %.3f - %.3f", templatemin, templatemax);
  cout << textout.Data() << endl;
  
  // Book histograms
  fout->cd();
  TGraph* likelihood;

    likelihood = new TGraph(templatebins+1);
    likelihood->SetName("likelihood");
    likelihood->SetTitle("Likelihood");

  cout << "Booked histograms" << endl;

  double sum, inv_unc;
  sum = 0;
  inv_unc = 0;
  
  //TFile * tf;
  TH1D* hdataout;
  
  bool bad = false; // Check if there is a minimal acceptable of files
  
  double central_value, central_unc; // Stores the central value and uncertainty for PDF calculation
  double total_pdf_err, total_pdf_err_CC;
  double temp_pdf_err;

  TString histname_full;
  TString tempname_full;

    tempname_full.Form("%s_", tempname.Data());
    for (int ihist=0; ihist<45; ihist++) {
      tf->cd(dirname);
      histname_full.Form("%s_PDF_%d", histname.Data(), ihist); 
      cout << jrun << " " << ihist << " " << histname_full << endl;
	TH1D *myHist = (TH1D*)gROOT->FindObject(histname_full);
		
	if (myHist->GetEntries()>100000.) {
	  bad = false;
	  hdataout = (TH1D *)myHist->Clone("hdataout");
	  
	  //Initialize fit class	  
	  bool dobackground = false;
	  if (compare_option==0) dobackground=true;
	  
	  // Here we have to do some cumbersome recasting since
	  // gen1Dspline and wzfitter const accept char* and not const char*
	  //
	  char* tempname_char;
	  tempname_char = const_cast<char *>(tempname_full.Data());
	  char* configfile_char;
	  configfile_char = const_cast<char *>(configfile.Data());


	  // Construct the template and fitter
	  myDist = new gen1Dspline(pmcstemplates
				   ,tempname_char
				   ,"histd1map_WMassTemplates", 1, 2
				   ,"fitter_backgrounds.root"
				   ,dobackground);	  	  

	  myFitter = new wzfitter(myDist,myHist,configfile_char,true); 
	  
	  /////////////////////////////////////////
	  // Before doFit always check with the BA
	  /////////////////////////////////////////

	  TFile * fpmcs = new TFile(pmcstemplates,"READ");
	  BA.SetConfiguration(tf,fpmcs,compare_option);

	  if ((compare_option == 0) && (_blinded == false)) {
	    cerr << "Blinding must be turned on to study data." << endl;
	    return 1;
	  }
	  else if ((_blinded==true) && (compare_option!=0) ){
	    cerr << "Blinding must be turned off to study fast/full MC." << endl;
	    return 1;
	  }

	  
	  // Perform the actual fit
	  doFit();
  // Print the fit results...Make pull plots 
	  paramval = _gpar[0];
	  errval = _gerr[0];
	  	  
	  if(jrun==0) {
	    wmass->SetPoint(0,0,paramval);
	    wmass->SetPointError(0,0.,errval);
	  } else {
	    wmass->SetPoint(0,0,paramval);
	    wmass->SetPointError(0,0.,errval);
	  }
	  
	  if(ihist==0) {
	    central_value = paramval;
	    central_unc = errval;
	    if (jrun==0) {
	      sum += paramval/(errval*errval);
	      inv_unc += 1/(errval*errval);
	      textfout << paramval << " " << errval << endl;
	    }
	  } else {
	    if(jrun==0){
	      error_hist->SetBinContent(ihist,paramval-central_value);
	      error_hist->SetBinError(ihist, errval);
	      if (ihist%2==1)
		temp_pdf_err = paramval;
	      else {
		total_pdf_err += (paramval-temp_pdf_err)*(paramval-temp_pdf_err);
		pdf_error->SetBinContent(ihist/2 + 1, (paramval-temp_pdf_err)*(paramval-temp_pdf_err)/10.82);
	      }
	    }
	    else {
	      error_hist_CC->SetBinContent(ihist,paramval-central_value);
	      error_hist_CC->SetBinError(ihist, errval);
	      if (ihist%2==1)
		temp_pdf_err = paramval;
	      else
		total_pdf_err_CC += (paramval-temp_pdf_err)*(paramval-temp_pdf_err);
		pdf_error_CC->SetBinContent(ihist/2 + 1, (paramval-temp_pdf_err)*(paramval-temp_pdf_err)/10.82);
	    }
	  }
	  
	}else { 
	  cerr << " Not enough entries in " << filename << endl;
	  bad = true;
	}
      }
    tf->Close();
  

  fout->cd();
  wmass->Write("wmass");
  wmass_CC->Write("wmass");
  error_hist->Write();
  error_hist_CC->Write();
  pdf_error->Write();
  pdf_error_CC->Write();

  cout << endl << " ---- Summary ---- " << endl << endl
       << "W mass: " << sum/inv_unc << " " << TMath::Sqrt(1/inv_unc) << endl
       << "PDF error: " << TMath::Sqrt(total_pdf_err/10.82) << endl
       << "PDF error (CC): " << TMath::Sqrt(total_pdf_err_CC/10.82) << endl;


	  /**
    // Separate the right templates for a specific trial mass
    TFile* template_temp = new TFile("template_temp.root", "RECREATE");
    TDirectory* template_dir = template_temp->mkdir("default");
    template_dir->cd();

    TH1D* template_map = (TH1D*) templatemap->Clone();
    template_map->GetXaxis()->Set(templatebins,
    				  templatemin + (templatemid - trialmass),
    				  templatemax + (templatemid - trialmass));
    template_map->Write();
    TH1D* template_hist[templatebins+1];
    for (Int_t itemplate = 0; itemplate <= templatebins; itemplate++) {
      TH1D* hptr = (TH1D*) tf->Get(TString::Format("default/%s%d", tempname, itemplate));
      template_hist[itemplate] = (TH1D*) hptr->Clone();
      template_hist[itemplate]->SetName(TString::Format("trial_template_%d", itemplate));
      template_hist[itemplate]->Write();
    }
    template_temp->Close();

    // Do a spline interpolation for singularity variable histogram
    cout << "Making the spline interpolation... ";
    myDist = new gen1Dspline("template_temp.root", "trial_template_", templatemapname, 1, 2 ,"fitter_backgrounds.root" ,dobackground);
    cout << "gen1Dspline done " << myDist << endl;

    // Creates the fitter
    myFitter = new wzfitter(myDist,myHist,configfile,true); 
        
    // Perform the actual fit
    doFit();
	 
    //  mass->SetPoint(itrial-tmin, trialmass, _gpar[0]);
    // uncertainty->SetPoint(itrial-tmin, trialmass, _gerr[0]);
    paramval = _gpar[0];
    errval = _gerr[0];
    tot_err+=errval;
      
      cout<<"the value of the parameters are... "<<paramval<<endl;
      cout<<"the errors of the parameters are... "<<errval<<endl;

    // Do blinded likelihood scan
    double *apar = new Double_t[_npar];
    apar[0] = _gpar[0];
    double llmin = myFitter->doLogLikelihood(apar,true,myRange);
    for (Int_t itemplate = 0; itemplate <= templatebins; itemplate++) {
      Double_t templatemass = templatemin + ((Double_t) itemplate) * templatestep;
      apar[0] = templatemass;
      Double_t ll = myFitter->doLogLikelihood(apar,true,myRange);
      likelihood->SetPoint(itemplate, templatemass + (templatemid - trialmass), ll-llmin);
    }



  fout->cd();
  // mass->Write("mass");
  // uncertainty->Write("uncertainty");
  likelihood->Write();

  fout->Write();
  fout->Close();
  df->Close();
  tf->Close();
	  **/
}
