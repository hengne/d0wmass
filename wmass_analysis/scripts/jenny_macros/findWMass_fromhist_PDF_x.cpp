////////////////////////////////////////////////////////////////////////
///   findWMass_fromhist_x.cpp
///   Matt Wetstein 06/01/06
///
///   executable used to do the fit WMass from a histogram of data
///
///   added blinding, improved interface/output. -Tim March 14, 2008
///  
//
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
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
bool _iswidth;

// histo dimensions
vector<int> _numbins;
vector<double> _lowb;
vector<double> _highb;

//fit range
vector<Double_t> frange;
vector< vector<Double_t> > myRange;

////////////////////////////////////////////////////////////////////////////////////////////////
// The FCN function minimized by MINUIT

void Thefcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  if (_blinded) {
     BlindingAuthority BA(1);
     if(!_iswidth) par[0] = BA.Get_Offset_Mass()->CalculateTrueMassFromBlindedMass(par[0]);
     else par[0] = BA.Get_Offset_Width()->CalculateTrueWidthFromBlindedWidth(par[0]);
  }
   
  vector<double> d1range;
  d1range.push_back(frange[0]);  //32-48 or 65-95
  d1range.push_back(frange[1]);
  myRange.push_back(d1range);
  
  f=myFitter->doLogLikelihood(par,true,myRange);
  //
}

////////////////////////////////////////////////////////////////////////////////////////////////
// This function does the fit...regardless of what we're fitting 

void doFit()
{

  Double_t amin,edm,errdef;      // MINUIT variables...explained later
  Int_t nvpar,nparx,icstat;      // " " "


  // Initialize TMinuit
  
  TMinuit *gMinuit = new TMinuit(_npar);
  gMinuit->SetFCN(Thefcn);
  Double_t arglist[10];
  Int_t ierflg = 0;
  
  // mnexcm: minuit execute command     ...take 1 parameter from the arglist:-)
  
  arglist[0] = -1.;
  gMinuit -> mnexcm("SET PRINT", arglist, 1, ierflg);
  
  if(_likely) arglist[0] = .5;
  else arglist[0] = 1.;
  
  gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);
  
  // SET ERR initializes the error definition...
  // Sets the value of UP (default value= 1.), defining parameter errors. 
  // Minuit defines parameter errors as the chnge in parameter value 
  // required to change the function value by UP. Normally, for chisquared 
  // fits UP=1, and for negative log likelihood, UP=0.5.
  //   Usage: the above function executes the command, tells it to read the
  //   (one) recquisite parameter from the "arglist" array, tells it only 
  //   to read one argument, and defines ierflag as the error flag.

  // Set starting values and step sizes for parameters


  for(int i=0; i<_npar; i++)
    {
      if(_limits) gMinuit->mnparm(i, "a1", vstart[i], vstep[i], vmin[i], vmax[i],ierflg); // are there upper and lower fit limits?
      else gMinuit->mnparm(i, "a1", vstart[i], vstep[i], 0, 0,ierflg); // or no limits?
      //      cout<<vstart[i]<<" "<<vstep[i]<<endl;
    }


  // tells minuit the starting value and step size for varying the 
  // paramter(s) of the fit  
  
  // Now ready for minimization step
  
  arglist[0] = maxiter;  // the maximum number of iterations
  
  arglist[1] = sensitivity;   // specifies required tolerance on the function value 
  // at the minimum. The default tolerance is 0.1, and 
  // the minimization will stop when the estimated vertical
  // distance to the minimum (EDM) is less than 
  // 0.001*[tolerance]*UP (see SET ERR).
  
  gMinuit->mnexcm("MIGRAD", arglist , 2, ierflg);
  //Notice there are two parameters
  // MIGRAD is the command to commence minimization
  
  // Print results
  
  //   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

  //                mnstat returns amin: the minimum
  //                edm: the estimated vertical distance remaining to minimum
  //                errdef: the value of UP defining parameter uncertainties
  //                nvpar: the number of currently variable parameters
  //                nparx: the highest (ext) parameter number defined by user
  //                icstat: status integer indicating  goodness of covariance
  
   //   gMinuit->mnprin(_npar,amin);
  // Prints the values of the parameters at the time of the call
 

  //Prints the covariance matrix
  //  gMinuit->mnmatu(1);

  // get fit results: parameters and their errors:

  _gpar = new Double_t[_npar];
  _gerr = new Double_t[_npar];

  for(int i=0; i<_npar; i++)
    {
      gMinuit -> GetParameter(i, _gpar[i], _gerr[i]);
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

  fstream textfout("mass.txt",  ios::out ); // This will be a simples text output with masses and uncertainties
  
  // Declare variables

  double paramval, errval; // Stores the final results

  //Parse the command line

  if( argc < 5) {
    cout<< "Usage : ./findWMass_fromhist_x <input-filenames> <output-filename> <template-filename> <Mt-or-Pt-or-MET-or-Width> <compare-option>" << std::endl;
    cout<<" Use <compare_option>=0  for comparing DATA with Fast-MC (PMCS),"<<endl
	<<"     <compare_option>=1  for comparing DATA with DATA,"<<endl
	<<"     <compare_option>=2  for comparing Fast-MC (PMCS) with Fast-MC (PMCS),"<<endl 
	<<"     <compare_option>=3  for comparing Full-MC (GEANT) with Fast-MC (PMCS)," << endl
	<<"     <compare_option>=4  for comparing Full-MC (GEANT) with Full-MC (GEANT)." << endl
	<<"     <compare_option>=5  for comparing DATA with Full-MC (GEANT)." << endl
	<<"     Only 0, 2 and 3 are useful." << endl;
    
    return 1;
  }

  vector<TString> in_files;
  for( int i = 1; i < argc-4;++i)
    in_files.push_back( TString( argv[i] ) );

  TString out_filename = argv[argc-4];
  TFile * fout = new TFile(out_filename,"RECREATE");

  TString pmcstemplates = argv[argc-3];
  
  TString compare_type = argv[argc-2];

  int compare_option = atoi(argv[argc-1]);

  if ((compare_option<0) || (compare_option>5)) {
    cout<<"must choose a valid compare option 0-5"<<endl;
    return 1;
  }

  TGraphErrors* wmass = new TGraphErrors(in_files.size());
  TGraphErrors* wmass_CC = new TGraphErrors(in_files.size());

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


  // Setup some file names

  TString configfile;
  TString histname;
  TString distname;
  TString tempname;
  TString dirname;
  TString templatemapname;

  if ((compare_type=="Mt" || compare_type=="MT" || compare_type=="mt" || compare_type=="mT" )){
    configfile = "runWMassMT.config";
    histname = "hWcandMt";
    tempname = "hWcandMt";
    templatemapname = "histd1map_WMassTemplates";
  } else if ((compare_type=="Pt" || compare_type=="PT" || compare_type=="pt" || compare_type=="pT")){ 
    configfile = "runWMassPT.config";
    histname = "hWcandElecPt";
    tempname = "hWcandElecPt";
    templatemapname = "histd1map_WMassTemplates";
  } else if ((compare_type=="MET" || compare_type=="Met" || compare_type=="met" || compare_type=="MeT")){ 
    configfile = "runWMassMET.config";
    histname = "hWcandMet";
    tempname = "hWcandMet";
    templatemapname = "histd1map_WMassTemplates";
  }else if ( (compare_type=="SVgen" || compare_type=="Svgen" || compare_type=="svgen" )  ){
    configfile = "runWMassSingVariablerafpdf.config";
    histname = "hWcandSingVariable_Gen";
    tempname = "hWcandSingVariable_Gen";
    distname = "tempWSVgenhists.root";
    templatemapname = "histd1map_SingVariableTemplates";
  }else if ( (compare_type=="SVlongunsmear" || compare_type=="Svlongunsmear" || compare_type=="svlongunsmear" )  ){
    configfile = "runWMassSingVariablerafpdf.config";
    histname = "hWcandSingVariable_LongUnSmeared";
    tempname = "hWcandSingVariable_LongUnSmeared";
    distname = "tempWSVlongunsmearhists.root";
    templatemapname = "histd1map_SingVariableTemplates";
  }else if ( (compare_type=="SV" || compare_type=="Sv" || compare_type=="sv" ) ){
    configfile = "runWMassSingVariablerafpdf.config";
    histname = "hWcandSingVariable";
    tempname = "hWcandSingVariable";
    distname = "tempWSVhists.root";
    templatemapname = "histd1map_SingVariableTemplates";
  } else {
    cout<<"Didn't understand the options, or requested option not implimented"<<endl;
    return 1;
  }

  if (compare_option == 2)
    dirname = "default";
  else
    dirname = "WCand_Hist";
 
  // Read the config file...Obtain global parameters....

  config runconfig(configfile.Data());

  _npar = runconfig.getInt("numparam");  // number of parameters in the fit (e.g M(W) is a single parameter)
  _ndim= runconfig.getInt("ndimensions");// dimensionality of the histograms being fit (e.g. 1D histogram of MT variable)
  _numbins = runconfig.getIntArray("numbins");// number of bins in the histogram mentioned on the previous line, this number is set in wz_epmcs when templates are made
  _lowb = runconfig.getDoubleArray("lowrange");// low edge of the histogram referred to on the previous line, this number is set in wz_epmcs when templates are made
  _highb = runconfig.getDoubleArray("highrange");// high edge of the histogram referred to on the previous line, this number is set in wz_epmcs when templates are made
  frange = runconfig.getDoubleArray("fit_range");// fitting range that is used when the histogram referred on the previous line is being fit, fit range cannot extend beyond lowrange nor highrange values
  vstart = runconfig.getDoubleArray("start_value"); // MINUIT starting values for each parameter
  vstep = runconfig.getDoubleArray("vstep"); // MINUIT step size in each parameter (in each dimension of parameter space), typically we're talking about one parameter only, M_W or Gamma_W
  maxiter = runconfig.getInt("numiter"); // maximum number of iterations before MINUIT gives an answer
  sensitivity = (double) runconfig.getFloat("sensitivity"); // sensitivity of MINUIT fit (how close MINUIT needs to get to a minimum before it stops)  // at the minimum. The default tolerance is 0.1, and  the minimization will stop when the estimated vertical distance to the minimum (EDM) is less than 0.001*[tolerance]*UP (see SET ERR).
  _limits = runconfig.getBool("limits"); // constraining the allowed parameter range during fitting
  vmin = runconfig.getDoubleArray("vmin"); // if it is a constrained fit (_limits==true), this is lower limit, again this is an array, i.e. a limit for each parameter can be specified here, if there is more than one parameter
  vmax = runconfig.getDoubleArray("vmax"); // if it is a constrained fit (_limits==true), this is upper limit, again this is an array, i.e. a limit for each parameter can be specified here, if there is more than one parameter
  _likely = runconfig.getBool("likelihood");// this flag is used for defining error in MINUIT, specifically "arglist[0] = .5;" (this is NOT a switch between loglikelihood fit and chi2 fit)
  _blinded = runconfig.getBool("blinded");// flag for blinding the output of the fit
  
  // instatiate blinding authority
  BlindingAuthority BA(1);
  
  // Loop over a number toys

  double sum, inv_unc;
  sum = 0;
  inv_unc = 0;

  TFile * tf;
  TH1D* hdataout;

  bool bad = false; // Check if there is a minimal acceptable of files

  double central_value, central_unc; // Stores the central value and uncertainty for PDF calculation
  double total_pdf_err, total_pdf_err_CC;
  double temp_pdf_err;
  total_pdf_err = 0;
  total_pdf_err_CC = 0;

  TString histname_full;
  TString tempname_full;

  for( int i = 0; i < in_files.size(); ++i ) {

    TString filename = in_files[i];
    tf = new TFile(filename,"READ");

    for (int jrun=0; jrun<2; jrun++) {   // First run: everything, second run: just CC

	if (jrun==0)
	  tempname_full.Form("%s_", tempname.Data());
	else 
	  tempname_full.Form("%s_CC_", tempname.Data());

      for (int ihist=0; ihist<45; ihist++) {

	tf->cd(dirname);

	if (jrun==0) {
	  histname_full.Form("%s_PDF_%d", histname.Data(), ihist); 
	}else{
	  if((compare_type=="SV" || compare_type=="Sv" || compare_type=="sv" )||(compare_type=="SVgen" || compare_type=="Svgen" || compare_type=="svgen" ) || (compare_type=="SVlongunsmear" || compare_type=="Svlongunsmear" || compare_type=="svlongunsmear" )){
	    histname_full.Form("%s_PDF_CC_%d", histname.Data(), ihist); 
	  }else{
	    histname_full.Form("%s_CC_PDF_%d", histname.Data(), ihist); 
	  }
	}
	
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
	  char* templatemapname_char;
	  templatemapname_char = const_cast<char *>(templatemapname.Data());

	  cout<<pmcstemplates<<"  "<<tempname_char<<"  "<<templatemapname_char<<endl;
	  // Construct the template and fitter
	  myDist = new gen1Dspline(pmcstemplates
				   ,tempname_char
				   ,templatemapname_char, 1, 2
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
	  	  
	  cout<<paramval<<"  "<<errval<<endl;

	  if(jrun==0) {
	    wmass->SetPoint(i,i,paramval);
	    wmass->SetPointError(i,0.,errval);
	  } else {
	    wmass->SetPoint(i,i,paramval);
	    wmass->SetPointError(i,0.,errval);
	  }
	  
	  if(ihist==0) {
	    central_value = paramval;
	    central_unc = errval;
	    cout<<"ihist 0"<<endl;
	    if (jrun==0) {
	      sum += paramval/(errval*errval);
	      inv_unc += 1/(errval*errval);
	      textfout << paramval << " " << errval << endl;
	    }
	  } else {
	    cout<<"ihist "<<ihist<<endl;
	    if(jrun==0){
	      error_hist->SetBinContent(ihist,paramval-central_value);
	      error_hist->SetBinError(ihist, errval);
	      if (ihist%2==1)
		temp_pdf_err = paramval;
	      else {
		cout<<"total pdf err "<<total_pdf_err<<endl;
		total_pdf_err += (paramval-temp_pdf_err)*(paramval-temp_pdf_err);
		cout<<"total pdf err "<<total_pdf_err<<endl;
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
    }
    tf->Close();
  }
  

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

}
