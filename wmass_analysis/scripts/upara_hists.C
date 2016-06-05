#include <TApplication.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <strstream>
#include "TRandom.h"
#include "TH1D.h";
#include "TGraph.h";
#include <iomanip>

using namespace std;


gStyle->SetOptFit(1111);


TH1* eff_plot;
TF1* fit_fnc;
TKey* key_file;
TKey* key_fnc;
ofstream myfile;
Double_t* params;
Double_t* err;

void upara_hists() {

TPostScript myps("hist_file.ps",111);
myps.Range(16,24);
TCanvas c1("c1","canvas",800,600);
myfile.open("table.tex");
TFile f("uparaeff_plots.root");
TIter next(f.GetListOfKeys());

myfile << "\\documentclass{article}" << endl;
myfile << "\\begin{document}" << endl;
myfile << "\\begin{center}" << endl;

// Run over histograms

while ((key_file=(TKey*)next())) {
     f.GetObject(key_file->GetName(),eff_plot);
          
// Write the PS file //

//          eff_plot->Draw();
//          c1.Update();

          TIter next_fnc(eff_plot->GetListOfFunctions());

// Write in the LaTeX file //
          myfile << eff_plot->GetTitle() << "\\\\" << endl;
          myfile << "\\begin{tabular}{|c|c|c|}\\hline" << endl;
          myfile << "Kink ($GeV$) & Slope ($Gev^{-1}$) & Efficiency\\\\\\hline" << endl;


          while(key_fnc=(TKey*)next_fnc()) {
                fit_fnc = eff_plot->GetFunction(key_fnc->GetName());
                if (fit_fnc->GetNumberFreeParameters() == 3){
                      params = fit_fnc->GetParameters();
               	      err = fit_fnc ->GetParErrors();
                      myfile << params[0] << " $\\pm$ " << err[0] << " & " << params[1] << " $\\pm$ " << err[1] << " & " << params[2] << " $\\pm$ " << err[2] << "\\\\\\hline " << endl;;
                }
                if (fit_fnc->GetNumberFreeParameters() == 2){
                      params = fit_fnc->GetParameters();
               	      err = fit_fnc ->GetParErrors();
                      myfile << " Fixed " << " & " << params[1] << " $\\pm$ " << err[1] << " & " << params[2] << " $\\pm$ " << err[2] << "\\\\\\hline " << endl;
                }
          }
      myfile << "\\end{tabular}" << endl << endl;
}
myfile << "\\end{center}" << endl;
myfile << "\\end{document}";

myps.Close();
myfile.close();
f.Close();

}     
