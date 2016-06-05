#include <iostream>
#include <stdlib.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TROOT.h>

// dump histograms from wenucomp and zeecomp outputs
// author Hengne Li @ UVA - 2013

int main (int argc, char *argv[]) {

  if (argc < 3) {
    std::cout << "Dump histograms from wenucomp and zeecomp outputs." << std::endl;
    std::cout << "E.g. for Zee,\n"  
              << " > dumpHist.exe zeecomp.root zeecomp_dumpHist.root\n" 
              << "  - zeecomp.root is the zeecomp output, \n"
              << "  - zeecomp_dumpHist.root is the new root file contains all histograms.\n" 
              << "Same for Wenu, e.g. \n"        
              << " > dumpHist.exe wenucomp.root wenucomp_dumpHist.root\n" << std::endl;
    return 0;
  }

  const char *in, *out;
  in = argv[1];
  out = argv[2];

  TFile* f = new TFile(in);
  TFile* fout = new TFile(out, "RECREATE");

  TIter ican(f->GetListOfKeys());
  TCanvas *can;

  char name[1000];

  while (can=(TCanvas*)ican()) {
    TCanvas* acan = (TCanvas*)f->Get(can->GetName());
    std::cout << "Canvas Name : " << acan->GetName() << std::endl;
    fout->cd();
    acan->Clone()->Write();
    TIter ipad(acan->GetListOfPrimitives());
    TPad* pad;
    while (pad=(TPad*)ipad()) {
      TPad* apad = (TPad*)acan->FindObject(pad->GetName());
      TIter iobj(apad->GetListOfPrimitives());
      TObject *obj;
      while (obj=iobj()) {
        TObject* aobj = (TObject*)acan->FindObject(obj->GetName());
        sprintf(name, "%s_%s_%s", acan->GetName(), apad->GetName(), aobj->GetName());
        std::cout << "Object Name : " << name << std::endl;
        fout->cd();
        aobj->Clone(name)->Write();
      }
    }
  }

  f->Close();
  fout->Close();

}
